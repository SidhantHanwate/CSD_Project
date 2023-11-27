module SignExtend (
    // 16-bit immediate
	input signed [15:0] in,   

    // Output
	output signed [31:0] out
);

    assign out = {{16{in[15]}},in[15:0]};

endmodule
