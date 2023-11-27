module ALU_tb;

    reg signed [31:0] in1;
    reg signed [31:0] in2;
    reg [3:0] controlBits;
    wire signed [31:0] out;
    wire branch_res;

    ALU uut (
        .in1(in1), 
        .in2(in2), 
        .controlBits(controlBits), 
        .out(out),
        .branch_res(branch_res)
    );

    initial begin
        // Initialize inputs
        in1 = 32'd10;
        in2 = 32'd10;
        
        // Test all control bits
        for (controlBits = 0; controlBits < 16; controlBits = controlBits + 1) begin
            #20; // Wait for 20 time units
        end

        // Finish the simulation
        #10 $finish;
    end

endmodule
