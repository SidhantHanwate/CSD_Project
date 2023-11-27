module DataMemory(
    input clk,
    input memWrite,
    input memRead,
    input [31:0] address,
    input [31:0] writeData,

    output [31:0] readData     
);

    integer i;
    reg [31:0] RAM [1023:0];

    initial begin
        for(i=0; i<256; i=i+1)
            RAM[i] = 32'd0;
    end

    always @(posedge clk) begin
        if (memWrite)
            RAM[address] <= writeData;
    end

    assign readData = (memRead==1'b1) ? RAM[address] : 16'd0;
endmodule