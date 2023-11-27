module InstructionMemory(
    input clk,
    input [31:0] PC,
    output reg [31:0] instruction
);
    /*
        addi $8, $0, 5
        addi $9, $0, 12
        add  $10, $8, $9
        sw  $10, 84($0)
    */
    reg [31:0] ROM [0:255];
    initial
    begin
        ROM[0] = 32'b00100000000010000000000000000101;
        ROM[1] = 32'b00100000000010010000000000001100;
        ROM[2] = 32'b00000001000010010101000000100000;
        ROM[3] = 32'b10101100000010100000000000011000;
    end

    always @(posedge clk) begin
        instruction = ROM[PC[31:2]];
    end

endmodule