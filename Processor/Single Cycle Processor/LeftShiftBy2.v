module LeftShiftBy2 (
    // Output
    output [31:0] out,

    // Input
    input [31:0] in
);

    assign out = in << 2;

endmodule 
