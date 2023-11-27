module Mux2x1_tb;

    reg [31:0] data0;
    reg [31:0] data1;
    reg sel;
    wire [31:0] out;

    // Instantiate the 2x1 MUX
    Mux2x1 uut (
        .in1(data0),
        .in2(data1),
        .sel(sel),
        .out(out)
    );

    // Stimulus generation
    initial begin
        // Test case 1: Select input 0 (data0 should be on output)
        data0 = 32'hAABBCCDD;
        data1 = 32'h11223344;
        sel = 0;
        #10;

        // Test case 2: Select input 1 (data1 should be on output)
        data0 = 32'hAABBCCDD;
        data1 = 32'h11223344;
        sel = 1;
        #10;
    end
endmodule
