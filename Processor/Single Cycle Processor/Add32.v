module Add32 (
    // Output
    output [31:0] out,

    // Inputs
    input [31:0] a,
    input [31:0] b
);

    assign out = a + b;

endmodule 
