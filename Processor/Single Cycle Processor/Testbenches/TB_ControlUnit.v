module ControlUnit_tb;

    // Inputs
    reg [5:0] opcode;

    // Outputs
    wire memToReg;
    wire memWrite;
    wire memRead;
    wire branch;
    wire [3:0] ALUOp;
    wire ALUSrcBControl;
    wire regDst;
    wire regWrite;
    wire jmp;

    // Instantiate the ControlUnit module
    ControlUnit uut (
        .opcode(opcode),
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

    // Testbench stimulus
    initial begin

        // Test case 1: R-type instruction
        opcode = 6'b000000; 
        #10;

        // Test case 2: ADDI instruction
        opcode = 6'b001000; 
        #10;

        // Test case 3: ANDI instruction
        opcode = 6'b001100; 
        #10;

        // Test case 4: ORI instruction
        opcode = 6'b001101; 
        #10;

        // Test case 5: LW instruction
        opcode = 6'b100011; 
        #10;

        // Test case 6: SW instruction
        opcode = 6'b101011; 
        #10;

        // Test case 7: BEQ instruction
        opcode = 6'b000100; 
        #10;

        // Test case 8: BNE instruction
        opcode = 6'b000101; 
        #10;

        // Test case 9: BGT instruction
        opcode = 6'b001110; 
        #10;

        // Test case 10: BGE instruction
        opcode = 6'b010001; 
        #10;

        // Test case 11: BLT instruction
        opcode = 6'b010010; 
        #10;

        // Test case 12: BLE instruction
        opcode = 6'b010011; 
        #10;

        // Test case 13: J instruction
        opcode = 6'b000010; 
        #10;

        // Test case 14: JAL instruction
        opcode = 6'b000011; 
        #10;



        

        $finish;
    end
    
endmodule
