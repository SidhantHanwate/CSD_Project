`timescale 1ns / 1ps

/////////////////////////////////////////////////
parameter WIDTH = 14;  // Parameter to represent the data width

module displayMemory (
    input clk,
    input wr_en_display,       // Write enable
    input byteWrite,           // Byte writing enable
    input half_wordWrite,      // Half-word writing enable
    input full_wordWrite,      // Full-word writing enable
    input [31:0] writeAddress, // Byte writable address with 2 additional bits for bytes
    input [31:0] writeData,
    input [31:0] displayAddr,  // Word-readable address
    output wire [31:0] displayData
);

    wire [WIDTH+1:0] writeAddress_internal;
    wire [WIDTH-1:0] displayAddr_internal;
    
    assign displayAddr_internal = displayAddr[WIDTH-1:0];  // Word addressable
    assign writeAddress_internal = writeAddress[WIDTH+1:0]; // Byte addressable

    // Memory array with a width of 32 bits and a depth of 9600 words
    reg [31:0] memory [0:9599]; // 2^(WIDTH-5)
    
    // Initialize memory with data from the file "displayMemory.mem"
    initial
        $readmemb("displayMemory.mem", memory, 0, 9599);

    wire [WIDTH-1:0] byteAddress;
    assign byteAddress = writeAddress_internal[WIDTH+1:2];  // Convert byte address to word
    
    always @(posedge clk)
    begin
        if (wr_en_display && (writeAddress_internal < 16'd38400))
        begin
            if (full_wordWrite == 1'b1)
                memory[byteAddress] <= writeData;
            
            if (half_wordWrite == 1'b1)
            begin
                if (writeAddress_internal[1] == 1'b0)
                    memory[byteAddress][31:16] <= writeData[15:0];
                else if (writeAddress_internal[1] == 1'b1)
                    memory[byteAddress][15:0] <= writeData[15:0];
            end
            
            if (byteWrite)
            begin
                if (writeAddress_internal[1:0] == 2'b00)
                    memory[byteAddress][31:24] <= writeData[7:0];
                else if (writeAddress_internal[1:0] == 2'b01)
                    memory[byteAddress][23:16] <= writeData[7:0];
                else if (writeAddress_internal[1:0] == 2'b10)
                    memory[byteAddress][15:8] <= writeData[7:0];
                else
                    memory[byteAddress][7:0] <= writeData[7:0];
            end
        end
    end

    // Check if the input address is in the memory range
    assign displayData = (displayAddr_internal < 14'd9600) ? memory[displayAddr_internal] : 32'd0;

endmodule
