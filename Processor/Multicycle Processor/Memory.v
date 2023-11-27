module Memory(
    input clk,
    input memWrite,
    input memRead,
    input IRWrite,
    input [31:0] address,
    input [31:0] writeData,

    output [31:0] readData,
    output [31:0] readInst    
);
    // Memory Size = 4KB
    // (initial 1KB for data mem and remaining for instruction)
    // Assume DataMemory starts from address 0
    // InstructionMemory starts from address 256
    parameter inst_offset = 256;
    
    wire [31:0]final_inst_addr;
    integer i;
    reg [31:0] RAM [1023:0];

    initial begin

        for(i=0; i<256; i=i+1)
            RAM[i] = 32'd0;

        RAM[256] = 32'b00100000000001110000000000001111; // addi $7, $0, 15
        RAM[257] = 32'b00100000000010000000000000000101; // addi $8, $0, 5
        RAM[258] = 32'b00100000000010010000000000001100; // addi $9, $0, 12
        RAM[259] = 32'b00100000000010100000000000010100; // addi $10, $0, 20
        RAM[260] = 32'b01010000111010001000100000000000; // MAC $7, $8
        RAM[261] = 32'b01010001001010101000100000000000; // MAC $9, $10
        
        // RAM[258] = 32'b00100000000010010000000000001100; // addi $9, $0, 12
        // RAM[259] = 32'b000000 01000 01001 01010 00000100000; // add $10, $8, $9
        // RAM[260] = 32'b10101100000010100000000000011000; // sw $10, 20($0)
        // RAM[261] = 32'b10001100000000010000000000011000; // lw $1, 20($0)
        // RAM[262] = 32'b00010000001010000000000000000011; // bne $1, $8, 3
        // RAM[263] = 32'b00001000000000000000000000000011; // j  3
    end

    always @(posedge clk) begin
        if (memWrite)
            RAM[address] <= writeData;
    end

    assign final_inst_addr = address[31:2] + inst_offset;

    assign readData = (memRead==1'b1) ? RAM[address] : 16'd0;
    assign readInst = RAM[final_inst_addr];
endmodule