module InstructionMemory_tb;

    // Inputs
    reg [31:0] PC;
    reg clk = 0;

    // Outputs
    wire [31:0] instruction;

    // Instantiate the InstructionMemory module
    InstructionMemory uut (
        .clk(clk),
        .PC(PC),
        .instruction(instruction)
    );

    // Test vectors
    initial begin

        // Initialize PC
        PC = 0;

        // Apply test vectors
        #10 PC = 32'h00000000; // PC = 0
        #10 PC = 32'h00000004; // PC = 4
        #10 PC = 32'h00000008; // PC = 8
        #10 PC = 32'h0000000C; // PC = 12

        // Finish simulation
        $finish;
    end

    // Clock generation
    always begin
        #5 clk = ~clk;
    end


endmodule
