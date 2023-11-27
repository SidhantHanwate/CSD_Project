module ALUControl (
    input [3:0] ALUOp,
    input [5:0] funct,
    output reg [3:0] aluCtrl    
);
    
    parameter ADDFN = 6'b100000;
    parameter SUBFN = 6'b100010;
    parameter ANDFN = 6'b100100;
    parameter ORFN  = 6'b100101;
    parameter XORFN = 6'b100110;
    parameter SLLFN = 6'b000000;
    parameter SRLFN = 6'b000010;

    reg [3:0] fno;
    /* 
        ALUControl: 
        0: Add
        1: Subtract
        2: And
        3: or
        4: Xor
        5: sll
        6: srl
        7: beq
        8: bne
        9: bgt
        10: bge
        11: blt
        12: ble
    */

    always @ (funct)
    begin
        case(funct)
            ADDFN: fno = 4'b0000;
            SUBFN: fno = 4'b0001;
            ANDFN: fno = 4'b0010;
            ORFN: fno = 4'b0011;
            XORFN: fno = 4'b0100;
            SLLFN: fno = 4'b0101;
            SRLFN: fno = 4'b0110;
            default: fno = 4'b0000;
        endcase
    end

    /* 
        ALUOP: 4 bits: 
        // ALUOp = 0  --> (RTYPE instruction) ALU Operation will be decided by funct value
        // ALUOp = 1  --> Addition
        // ALUOp = 2  --> And
        // ALUOp = 3  --> Or
        // ALUOp = 4  --> BEQ
        // ALUOp = 5  --> BNE
        // ALUOp = 6  --> BGT
        // ALUOp = 7  --> BGE
        // ALUOp = 8  --> BLT
        // ALUOp = 9  --> BLE
    */

    always @ (ALUOp, funct)
    begin
        case(ALUOp)
            4'b0000: aluCtrl = fno;
            4'b0001: aluCtrl = 4'b0000;     // normal ADD op but immediate source 
            4'b0010: aluCtrl = 4'b0010;     // normal AND op but immediate source
            4'b0011: aluCtrl = 4'b0011;     // normal OR op but immediate source
            4'b0100: aluCtrl = 4'b0111;
            4'b0101: aluCtrl = 4'b1000;
            4'b0110: aluCtrl = 4'b1001;
            4'b0111: aluCtrl = 4'b1010;
            4'b1000: aluCtrl = 4'b1011;
            4'b1001: aluCtrl = 4'b1100;
            4'b1010: aluCtrl = 4'b1101;
            default: aluCtrl = 4'b0000;
        endcase
    end

endmodule