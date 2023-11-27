module SingleCycleProcessor(
    input clk,
    input rst
);
	reg [31:0] pc = 32'd0;	// Program Counter
	wire [31:0] pc_next; // holds the actual next program counter until next clock cycle
    
	wire [31:0] instruction; // instruction register
    
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
	wire ALUSrcBControl;
	wire regDst;
	wire regWrite;
	wire jmp;

	// output from mux's
    wire [4:0] write_register;
    wire [31:0] alu_srcB;
    wire [31:0] write_data_regfile;

    wire [31:0] imm_extend; // output from sign extend

    wire [31:0] pc_plus_4, branch_next_pc, branch_pc, jump_pc; // output from pc adders

    wire pc_src;

	// combine all the modules to form the datapath
	ControlUnit control_unit (
        .opcode(instruction[31:26]),
        .memToReg(memToReg),
        .memWrite(memWrite),
        .memRead(memRead),
        .branch(branch),
        .ALUOp(ALUOp),
        .ALUSrcBControl(ALUSrcBControl),
        .regDst(regDst),
        .regWrite(regWrite),
        .jmp(jmp)
    );

	ALUControl alu_control (
        .ALUOp(ALUOp),
        .funct(instruction[5:0]),
        .aluCtrl(aluCtrl)
    );

	InstructionMemory instruction_Mem (
		.clk(clk),
		.PC(pc),
		.instruction(instruction)
	); 

	DataMemory data_mem (
        .clk(clk),
        .memWrite(memWrite),
        .memRead(memRead),
        .address(alu_result),
        .writeData(read_data2),
        .readData(read_data)
    );

	RegisterFile register_file (
        .clock(clk),
        .rst(rst),
        .RegWrite(regWrite),
        .Read_Reg1(instruction[25:21]),
        .Read_Reg2(instruction[20:16]),
        .Write_Reg(write_register),
        .writeData(write_data_regfile),
        .Read_Data1(read_data1),
        .Read_Data2(read_data2)
    );

	ALU alu (
        .in1(read_data1), 
        .in2(alu_srcB), 
        .controlBits(aluCtrl), 
        .out(alu_result),
        .branch_res(branch_result)
    );

	SignExtend sign_extend (
        .in(instruction[15:0]), 
        .out(imm_extend)
    );

	Mux2x1_5bit mux1_reg_dst (
        .in1(instruction[20:16]),
        .in2(instruction[15:11]),
        .sel(regDst),
        .out(write_register)
    );

	Mux2x1 mux2_srcB (
        .in1(read_data2),
        .in2(imm_extend),
        .sel(ALUSrcBControl),
        .out(alu_srcB)
    );
	
    Mux2x1 mux3_mem_to_reg (
        .in1(alu_result),
        .in2(read_data),
        .sel(memToReg),
        .out(write_data_regfile)
    );

    PC program_counter (
        .clk(clk),
        .rst(rst),
        .PCin(pc),
        .PCout(pc_plus_4)
    );

    Add32 add_32bit2 (
        .a(pc_plus_4),
        .b({imm_extend[29:0], 2'b00}),
        .out(branch_pc)
    );

    assign pc_src = branch & branch_result;

    Mux2x1 mux4_branch_instrction (
        .in1(pc_plus_4),
        .in2(branch_pc),
        .sel(pc_src),
        .out(branch_next_pc)
    );

    assign jump_pc = {pc_plus_4[31:28], instruction[25:0], 2'b00};

    Mux2x1 mux4_jump_instrction (
        .in1(branch_next_pc),
        .in2(jump_pc),
        .sel(jmp),
        .out(pc_next)
    );

    always @(*) begin
        pc = pc_next;
    end
    
endmodule