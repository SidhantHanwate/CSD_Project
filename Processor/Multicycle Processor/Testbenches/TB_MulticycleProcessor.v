module MulticycleProcessor_tb;
    
	reg clk;
    reg rst;

    MulticycleProcessor uut (
        .clk(clk),
        .rst(rst)
    );
    
    // generate clock
    always begin
        #10 clk = ~clk;
    end

    initial begin
        // initialize all variables
        clk = 0; rst = 1;
        #5 rst = 0;
        #1000
        $finish;
    end

endmodule
