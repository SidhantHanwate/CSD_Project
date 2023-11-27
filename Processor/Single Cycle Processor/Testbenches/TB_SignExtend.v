module SignExtend_tb;

    reg signed [31:0] in;
    wire signed [31:0] out;

    SignExtend uut (
        .in(in), 
        .out(out)
    );

    initial begin
        // Initialize inputs
        in = 16'd2868;
        #50

        in = -16'd175;
        #50

        in = 16'd108;
        #50

        in = -16'd1;
        #100

        // Finish the simulation
        $finish;
    end

endmodule
