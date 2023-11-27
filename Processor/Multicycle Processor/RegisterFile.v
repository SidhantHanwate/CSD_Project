module RegisterFile
(
    input clock,
    input rst,

    // RegWrite is 1 if a register should be written
	input RegWrite,

    // Address of register from which data has to be read
	input [4:0] Read_Reg1,
	input [4:0] Read_Reg2,

    // Address of register to which data has to be written
	input [4:0] Write_Reg,

    // Data to be written
	input [31:0] writeData,

    // Read data
	output [31:0] Read_Data1,
	output [31:0] Read_Data2,
    output [31:0] ReadMAC
);

    reg [31:0] registerFile [31:0];

    initial begin
        registerFile[0] <= 32'd0;
        registerFile[1] <= 32'd0;
        registerFile[2] <= 32'd0;
        registerFile[3] <= 32'd0;
        registerFile[4] <= 32'd0;
        registerFile[5] <= 32'd0;
        registerFile[6] <= 32'd0;
        registerFile[7] <= 32'd0;
        registerFile[8] <= 32'd0;
        registerFile[9] <= 32'd0;
        registerFile[10] <= 32'd0;
        registerFile[11] <= 32'd0;
        registerFile[12] <= 32'd0;
        registerFile[13] <= 32'd0;
        registerFile[14] <= 32'd0;
        registerFile[15] <= 32'd0;
        registerFile[16] <= 32'd0;
        registerFile[17] <= 32'd0;
        registerFile[18] <= 32'd0;
        registerFile[19] <= 32'd0;
        registerFile[20] <= 32'd0;
        registerFile[21] <= 32'd0;
        registerFile[22] <= 32'd0;
        registerFile[23] <= 32'd0;
        registerFile[24] <= 32'd0;
        registerFile[25] <= 32'd0;
        registerFile[26] <= 32'd0;
        registerFile[27] <= 32'd0;
        registerFile[28] <= 32'd0;
        registerFile[29] <= 32'd0;
        registerFile[30] <= 32'd0;
        registerFile[31] <= 32'd0;
    end

    always @ (posedge clock or posedge rst) 
    begin
        if(rst) begin
            registerFile[0] <= 32'd0;
            registerFile[1] <= 32'd0;
            registerFile[2] <= 32'd0;
            registerFile[3] <= 32'd0;
            registerFile[4] <= 32'd0;
            registerFile[5] <= 32'd0;
            registerFile[6] <= 32'd0;
            registerFile[7] <= 32'd0;
            registerFile[8] <= 32'd0;
            registerFile[9] <= 32'd0;
            registerFile[10] <= 32'd0;
            registerFile[11] <= 32'd0;
            registerFile[12] <= 32'd0;
            registerFile[13] <= 32'd0;
            registerFile[14] <= 32'd0;
            registerFile[15] <= 32'd0;
            registerFile[16] <= 32'd0;
            registerFile[17] <= 32'd0;
            registerFile[18] <= 32'd0;
            registerFile[19] <= 32'd0;
            registerFile[20] <= 32'd0;
            registerFile[21] <= 32'd0;
            registerFile[22] <= 32'd0;
            registerFile[23] <= 32'd0;
            registerFile[24] <= 32'd0;
            registerFile[25] <= 32'd0;
            registerFile[26] <= 32'd0;
            registerFile[27] <= 32'd0;
            registerFile[28] <= 32'd0;
            registerFile[29] <= 32'd0;
            registerFile[30] <= 32'd0;
            registerFile[31] <= 32'd0;
        end
        else begin
            if( RegWrite ) begin
                registerFile[Write_Reg] <= writeData;
            end
        end	
    end

    assign Read_Data1 = registerFile[Read_Reg1];
    assign Read_Data2 = registerFile[Read_Reg2];
    assign ReadMAC = registerFile[17];

endmodule
