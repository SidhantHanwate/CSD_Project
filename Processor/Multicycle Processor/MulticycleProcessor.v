module MulticycleProcessor(
    input clk,
    input rst
);

    reg [31:0] pc = 32'd0;	// Program Counter
    
	wire [31:0] instruction; // 32-bit instruction 
    
    wire [31:0] read_data; // output data from data memory

    wire [31:0] read_data1, read_data2; // output data from registers

    wire [31:0] alu_result; // output from ALU

    wire branch_result; // Branch output from ALU

    wire [3:0] aluCtrl;	// ALU control signal output from ALU control to decide the operation

    // signals
	wire memToReg;
	wire memWrite;
	wire memRead;
	wire branch;
	wire [3:0] ALUOp;	// Input to ALUControl
	wire [1:0]ALUSrcAControl;
	wire [1:0]ALUSrcBControl;
	wire regDst;
	wire regWrite;
	wire jmp;
    wire IorD;
    wire IRWrite;
    wire pcWrite;
    wire [1:0]pcSrc;
    wire MACsrcBsel;

    // temp variables or Ouput from mux
    wire [31:0] IorDaddress;
    wire [31:0] write_data_regfile;
    wire [4:0] write_register;
    wire [31:0] imm_extend;
    wire [31:0] alu_srcA;
    wire [31:0] alu_srcB;
    wire [31:0] final_alu_srcB;
    wire [31:0] pc_dash;
    wire [31:0] pc_jump;
    wire [3:0] state;

    // Registers to store intermediate results
    reg [31:0] AluOut;
    reg [31:0] IR;
    reg [31:0] regRD1;
    reg [31:0] regRD2;
    reg [31:0] DataR;

    // MAC register
    wire [31:0] MACdata;
    reg [31:0] MACreg;

    // combine all the modules to form the datapath
	ControlUnit control_unit (
        .opcode(IR[31:26]),
        .clock(clk),
        .memToReg(memToReg),
        .memWrite(memWrite),
        .memRead(memRead),
        .branch(branch),
        .ALUOp(ALUOp),
        .ALUSrcAControl(ALUSrcAControl),
        .ALUSrcBControl(ALUSrcBControl),
        .regDst(regDst),
        .regWrite(regWrite),
        .jmp(jmp),
        .IorD(IorD),
        .IRWrite(IRWrite),
        .pcWrite(pcWrite),
        .pcSrc(pcSrc),
        .state(state),
        .MACsrcBsel(MACsrcBsel)
    );
    
    ALUControl alu_control (
        .ALUOp(ALUOp),
        .funct(IR[5:0]),
        .aluCtrl(aluCtrl)
    );

    Mux2x1_32bit mux_pc_alures (
        .in1(pc),
        .in2(AluOut),
        .sel(IorD),
        .out(IorDaddress)
    );

    Memory memory(
        .clk(clk),
        .memWrite(memWrite),
        .memRead(memRead),
        .IRWrite(IRWrite),
        .address(IorDaddress),
        .writeData(read_data2),
        .readData(read_data),
        .readInst(instruction)
    );

    Mux2x1_5bit mux_reg_dst (
        .in1(IR[20:16]),
        .in2(IR[15:11]),
        .sel(regDst),
        .out(write_register)
    );

    Mux2x1_32bit mux_mem_to_reg (
        .in1(AluOut),
        .in2(DataR),
        .sel(memToReg),
        .out(write_data_regfile)
    );
    
    RegisterFile register_file (
        .clock(clk),
        .rst(rst),
        .RegWrite(regWrite),
        .Read_Reg1(IR[25:21]),
        .Read_Reg2(IR[20:16]),
        .Write_Reg(write_register),
        .writeData(write_data_regfile),
        .Read_Data1(read_data1),
        .Read_Data2(read_data2),
        .ReadMAC(MACdata)
    );

    assign pc_jump = {pc[31:28], IR[25:0], 2'b00};
    Mux4x1_32bit mux_srcA (
        .in0(pc),
        .in1(regRD1),
        .in2(32'd0),
        .in3(AluOut),
        .sel(ALUSrcAControl),
        .out(alu_srcA)
    );

    Mux4x1_32bit mux_srcB (
        .in0(regRD2),
        .in1(32'd4),
        .in2(imm_extend),
        .in3(imm_extend << 2),
        .sel(ALUSrcBControl),
        .out(alu_srcB)
    );
	
    Mux2x1_32bit mux_srcB_MAC (
        .in1(alu_srcB),
        .in2(MACreg),
        .sel(MACsrcBsel),
        .out(final_alu_srcB)
    );

    ALU alu (
        .in1(alu_srcA), 
        .in2(final_alu_srcB), 
        .controlBits(aluCtrl), 
        .out(alu_result),
        .branch_res(branch_result)
    );

    SignExtend sign_extend (
        .in(IR[15:0]), 
        .out(imm_extend)
    );

    Mux4x1_32bit mux_pc_input (
        .in0(alu_result),
        .in1(AluOut),
        .in2(pc_jump),
        .in3(32'd0),
        .sel(pcSrc),
        .out(pc_dash)
    );

    always @ (posedge clk)
	begin
        if(pcWrite || (branch&branch_result))
            pc <= pc_dash;
		regRD1   <= read_data1;
		regRD2   <= read_data2;
        MACreg   <= MACdata;
		AluOut   <= alu_result;
        if(IRWrite == 1'b1)
            IR <= instruction;
        DataR  <= read_data;
	end
endmodule