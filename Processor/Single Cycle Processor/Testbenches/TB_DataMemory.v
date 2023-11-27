module DataMemory_tb;

    // Inputs
    reg clk;
    reg memWrite;
    reg memRead;
    reg [31:0] address;
    reg [31:0] writeData;

    // Outputs
    wire [31:0] readData;

    // Instantiate the DataMemory module
    DataMemory uut (
        .clk(clk),
        .memWrite(memWrite),
        .memRead(memRead),
        .address(address),
        .writeData(writeData),
        .readData(readData)
    );

    // Clock generation
    always begin
        #5 clk = ~clk;
    end

    // Testbench stimulus
    initial begin
        clk = 0;
        // Initialize memory
        memWrite = 1;
        memRead = 0;
        address = 0;
        writeData = 32'hAABBCCDD;
        #10;
        memWrite = 0;

        // Read from memory
        memRead = 1;
        address = 0;
        #10;
        memRead = 0;

        // Write to memory
        memWrite = 1;
        address = 4;
        writeData = 32'h11223344;
        #10;
        memWrite = 0;

        // Read from memory again
        memRead = 1;
        address = 4;
        #10;
        memRead = 0;

        $finish;
    end

endmodule
