module RegisterFile_tb;

    // Define constants for register addresses
    reg CLOCK;
    reg RESET;
    reg REG_WRITE;
    reg [4:0] READ_REG1;
    reg [4:0] READ_REG2;
    reg [4:0] WRITE_REG;
    reg [31:0] WRITE_DATA;
    wire [31:0] READ_DATA1;
    wire [31:0] READ_DATA2;

    // Instantiate the RegisterFile module
    RegisterFile uut (
        .clock(CLOCK),
        .rst(RESET),
        .RegWrite(REG_WRITE),
        .Read_Reg1(READ_REG1),
        .Read_Reg2(READ_REG2),
        .Write_Reg(WRITE_REG),
        .writeData(WRITE_DATA),
        .Read_Data1(READ_DATA1),
        .Read_Data2(READ_DATA2)
    );

    // Clock generation
    always begin
        #5 CLOCK = ~CLOCK; // Toggle the clock every 5 time units
    end

    // Test case 1: Write data to register 3 and read from register 3 and 4
    initial begin
        CLOCK = 0;
        RESET = 1;
        #10 RESET = 0; // Release reset

        // Write data to register 3
        WRITE_REG = 3;
        WRITE_DATA = 32'hAABBCCDD;
        REG_WRITE = 1;
        READ_REG1 = 3;
        READ_REG2 = 4;

        // Perform read operations
        #10;

        // Check the results
        if (READ_DATA1 === 32'hAABBCCDD)
            $display("Test Case 1: Passed");
        else
            $display("Test Case 1: Failed");

        // Test case 2: Write data to register 5 and read from register 5 and 7
        // You can add more test cases like this
        WRITE_REG = 5;
        WRITE_DATA = 32'h11223344;
        REG_WRITE = 1;
        READ_REG1 = 5;
        READ_REG2 = 7;

        // Perform read operations
        #10;

        // Check the results
        if (READ_DATA1 === 32'h11223344)
            $display("Test Case 2: Passed");
        else
            $display("Test Case 2: Failed");

        // Finish simulation
        $finish;
    end

endmodule
