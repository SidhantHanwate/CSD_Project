module ALU (
    // Input 1
	input signed [31:0] in1,   

    // Input 2 
	input signed [31:0] in2,

    // Control bits to decide which operation to be performed
	input [3:0] controlBits,

    // Output
	output signed [31:0] out,

    // To indicate whether output is negative or not
	output branch_res
);

    assign out = (controlBits == 4'd0) ? in1 + in2 :                        
                (controlBits == 4'd1) ? in1 - in2 :                        
                (controlBits == 4'd2) ? in1 & in2 :                        
                (controlBits == 4'd3) ? in1 | in2 :
                (controlBits == 4'd4) ? in1 ^ in2 :                        
                (controlBits == 4'd5) ? in1 << in2 :
                (controlBits == 4'd6) ? in1 >> in2 :
                (controlBits == 4'd7) ? ((in1 == in2) ? 32'd1 : 32'd0) :
                (controlBits == 4'd8) ? ((in1 != in2) ? 32'd1 : 32'd0) :
                (controlBits == 4'd9) ? ((in1 > in2) ? 32'd1 : 32'd0) :
                (controlBits == 4'd10) ? ((in1 >= in2) ? 32'd1 : 32'd0) :
                (controlBits == 4'd11) ? ((in1 < in2) ? 32'd1 : 32'd0) :
                (controlBits == 4'd12) ? ((in1 <= in2) ? 32'd1 : 32'd0) :
                (controlBits == 4'd13) ? in1 * in2 :
                (controlBits == 4'd14) ? in1 / in2 :
                in1 % in2;
                
/*
    assign zr = ~(out[31] | out[30] | out[29] | out[28] |
                out[27] | out[26] | out[25] | out[24] |
                out[23] | out[22] | out[21] | out[20] |
                out[19] | out[18] | out[17] | out[16] |
                out[15] | out[14] | out[13] | out[12] |
                out[11] | out[10] | out[9]  | out[8]  |
                out[7]  | out[6]  | out[5]  | out[4]  |
                out[3]  | out[2]  | out[1]  | out[0]);
*/

    assign branch_res = (controlBits == 4'd7) ? out[0]:
                        (controlBits == 4'd8) ? out[0]:
                        (controlBits == 4'd9) ? out[0]:
                        (controlBits == 4'd10) ? out[0]:
                        (controlBits == 4'd11) ? out[0]:
                        (controlBits == 4'd12) ? out[0]: 1'b0;

endmodule
