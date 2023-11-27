module ControlUnit_TB;
    reg [5:0] opcode;
    reg clock;
    wire memToReg, memWrite, memRead, branch;
    wire [3:0] ALUOp;
    wire ALUSrcAControl;
    wire [1:0] ALUSrcBControl;
    wire regDst;
    wire regWrite;
    wire jmp;
    wire IorD;
    wire IRWrite;
    wire pcWrite;
    wire pcSrc;

    // Instantiate the ControlUnit module
    ControlUnit uut (
        .opcode(opcode),
        .clock(clock),
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
        .pcSrc(pcSrc)
    );

    initial begin
        // Initialize clock
        clock = 0;

        // Test case 1: R-type instruction
        opcode = 6'b001000; 
        #50;

        // Test case 2: ADDI instruction
        opcode = 6'b001000; 
        #50;

        // Test case 3: ANDI instruction
        opcode = 6'b001100; 
        #50;

        // Test case 4: ORI instruction
        opcode = 6'b001101; 
        #50;

        // Test case 5: LW instruction
        opcode = 6'b100011; 
        #50;

        // Test case 6: SW instruction
        opcode = 6'b101011; 
        #50;

        // Test case 7: BEQ instruction
        opcode = 6'b000100; 
        #50;

        // Test case 8: BNE instruction
        opcode = 6'b000101; 
        #50;

        // Test case 9: BGT instruction
        opcode = 6'b001110; 
        #50;

        // Test case 10: BGE instruction
        opcode = 6'b010001; 
        #50;

        // Test case 11: BLT instruction
        opcode = 6'b010010; 
        #50;

        // Test case 12: BLE instruction
        opcode = 6'b010011; 
        #50;

        // Test case 13: J instruction
        opcode = 6'b000010; 
        #50;

        // Test case 14: JAL instruction
        opcode = 6'b000011; 
        #50;

    end

    // Clock generation (50% duty cycle)
    always begin
        #5 clock = ~clock;
    end

endmodule
