module Memory_TB;
    reg clk;
    reg memWrite;
    reg memRead;
    reg IRWrite;
    reg [31:0] address;
    reg [31:0] writeData;
    wire [31:0] readData;
    wire [31:0] readInst;

    // Instantiate the Memory module
    Memory uut (
        .clk(clk),
        .memWrite(memWrite),
        .memRead(memRead),
        .IRWrite(IRWrite),
        .address(address),
        .writeData(writeData),
        .readData(readData),
        .readInst(readInst)
    );

    initial begin
        // Initialize clock
        clk = 0;

        // Apply reset
        memWrite = 0;
        memRead = 0;
        IRWrite = 0;
        address = 0;
        writeData = 0;
        #10; // Wait for a few clock cycles

        // Test cases
        // Example: Writing data to memory
        address = 10; // Accessing the instruction memory
        memWrite = 1;
        writeData = 32'h00400020; // Example instruction: "add $0, $8, $4"
        #10;
        memWrite = 0;
        #10;

        // Reading data from memory
        address = 10; // Accessing the instruction memory
        memRead = 1;
        #10;
        memRead = 0;
        #10;

        // Reading instruction from memory
        address = 16; // Accessing the instruction memory
        IRWrite = 1;
        #10;
        IRWrite = 0;
        #10;

    end

    // Clock generation (50% duty cycle)
    always begin
        #5 clk = ~clk;
    end

endmodule
