module top
	(	
		input p2d,p2c,
		input sysclk,
		output [7:0] ascii_code,
		output scan_code_ready
	);
	
	//wire [7:0] je;
	// signal declaration
	wire [7:0] scan_code;
	wire letter_case;
	
	wire reset;
	assign reset = 1'b0;
	
	wire [3:0] code;
	
	// instantiate keyboard scan code circuit
	keyboard kb_unit (.clk(sysclk), .reset(reset), .ps2d(p2d), .ps2c(p2c), .ascii(ascii_code),
			 .scan_code(scan_code), .scan_code_ready(scan_code_ready), .letter_case_out(letter_case), .code(code));
			
	// instantiate key-to-ascii code conversion circuit
	key2ascii k2a_unit (.letter_case(letter_case), .scan_code(scan_code), .ascii_code(ascii_code));
	

endmodule


