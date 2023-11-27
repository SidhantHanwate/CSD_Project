module ALUControl_tb;

    // Inputs
    reg [3:0] ALUOp;
    reg [5:0] funct;

    // Outputs
    wire [3:0] aluCtrl;

    // Instantiate the ALUControl module
    ALUControl uut (
        .ALUOp(ALUOp),
        .funct(funct),
        .aluCtrl(aluCtrl)
    );

    // Testbench stimulus
    initial begin

        // Test case 1: ADD operation
        ALUOp = 4'b0000;
        funct = 6'b100000;
        #10;
        
        // Test case 2: SUB operation
        ALUOp = 4'b0000;
        funct = 6'b100010;
        #10;
        
        // Test case 3: AND operation
        ALUOp = 4'b0000;
        funct = 6'b100100;
        #10;
        
        // Test case 4: OR operation
        ALUOp = 4'b0000;
        funct = 6'b100101;
        #10;
        
        // Test case 5: XOR operation
        ALUOp = 4'b0000;
        funct = 6'b100110;
        #10;
        
        // Test case 6: SLL operation
        ALUOp = 4'b0000;
        funct = 6'b000000;
        #10;
        
        // Test case 7: SRL operation
        ALUOp = 4'b0000;
        funct = 6'b000010;
        #10;


        // Test case 8: ADD operation
        ALUOp = 4'b0001;
        funct = 6'b000000;
        #10;

        // Test case 9: AND operation
        ALUOp = 4'b0010;
        funct = 6'b000000;
        #10;

        // Test case 10: OR operation
        ALUOp = 4'b0011;
        funct = 6'b000000;
        #10;

        // Test case 11: BEQ operation
        ALUOp = 4'b0100;
        funct = 6'b000000;
        #10;

        // Test case 12: BNE operation
        ALUOp = 4'b0101;
        funct = 6'b000000;
        #10;

        // Test case 13: BGT operation
        ALUOp = 4'b0110;
        funct = 6'b000000;
        #10;

        // Test case 14: BGE operation
        ALUOp = 4'b0111;
        funct = 6'b000000;
        #10;

        // Test case 15: BLT operation
        ALUOp = 4'b1000;
        funct = 6'b000000;
        #10;

        // Test case 16: BLE operation
        ALUOp = 4'b1001;
        funct = 6'b000000;
        #10;
        
        $finish;
    end

endmodule
