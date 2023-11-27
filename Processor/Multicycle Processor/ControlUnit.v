module ControlUnit(

	// 6-bit opcode
	input [5: 0] opcode,

    input clock,

	// control bit to indicate whether write from memory to register
	output memToReg,

	// control bit to indicate whether write in memory or not
	output memWrite,
	
	// control bit to indicate whether read from memory or not
	output memRead,
	
	// control bit to indicate whether it is branch instruction or not
	output branch,

	// control bit input to ALUControl
	output [3:0] ALUOp,

    // control bit for first source to ALU
	output [1:0]ALUSrcAControl,

	// control bit for second source to ALU
	output [1:0]ALUSrcBControl,

	// control bit for register destination
	output regDst,

	// control bit to indicate whether write in register or not
	output regWrite,

	// control bit to indicate whether it is jump instruction or not
	output jmp,

    // To indicate instruction or data
    output IorD,

    // To write the instruction into the instruction register
    output IRWrite,

    // To update the PC with this new value
    output pcWrite,

    // 
    output MACsrcBsel,

    // to indicate either an instruction or data address.
    output [1:0]pcSrc,

    output reg[3:0] state
);

    parameter Reset = 0;
    parameter Fetch = 1;
    parameter Decode = 2;
    parameter MemAdr = 3;
    parameter MemRead = 4;
    parameter MemWB = 5;
    parameter MemWrite = 6;
    parameter ExecuteR = 7;
    parameter AluWB = 8;
    parameter Branch = 9;
    parameter ExecuteI = 10;
    parameter ImmWB = 11;
    parameter Jump = 12;
    parameter MACadd = 13;

	parameter RTYPE = 6'b000000;    // 0
	parameter ADDI = 6'b001000;     // 8
	parameter ANDI = 6'b001100;		// 12
	parameter ORI = 6'b001101;		// 13
	parameter LW = 6'b100011;		// 35
	parameter SW = 6'b101011;		// 43
	parameter BEQ = 6'b000100;		// 4
	parameter BNE = 6'b000101;		// 5
	parameter BGT = 6'b001110;		// 14 (decided by me)
	parameter BGE = 6'b010001;		// 17 (decided by me)
	parameter BLT = 6'b010010;		// 18 (decided by me)
	parameter BLE = 6'b010011;		// 19 (decided by me)
	parameter J = 6'b000010;		// 2
	parameter JAL = 6'b000011;		// 3
    parameter MAC = 6'b010100;      // 20

    // reg [3:0] state;
    wire [3:0] nextState;

	initial
    begin   
        state = Reset;
    end

    always @ (posedge clock)
        begin
            state <= nextState;
        end

    assign memToReg = (state == MemWB) ? 1'b1 : 1'b0;
    assign memWrite = (state == MemWrite) ? 1'b1 : 1'b0;
    assign memRead = (state == MemRead) ? 1'b1 : 1'b0;
    assign branch = (state == Branch) ? 1'b1 : 1'b0;
    assign ALUOp = (state == MemAdr) ? 4'b0001 : 
                   (state == ExecuteR && opcode == MAC) ? 4'b1010 :
                   (state == MACadd) ? 4'b0001 : 
                   (state == ExecuteR) ? 4'b0000 :
                   (state == Branch && opcode == BEQ) ? 4'b0100 : 
                   (state == Branch && opcode == BNE) ? 4'b0101 :
                   (state == Branch && opcode == BGT) ? 4'b0110 :
                   (state == Branch && opcode == BGE) ? 4'b0111 :
                   (state == Branch && opcode == BLT) ? 4'b1000 :
                   (state == Branch && opcode == BLE) ? 4'b1001 :
                   (state == ExecuteI && opcode == ADDI) ? 4'b0001 : 
                   (state == ExecuteI && opcode == ANDI) ? 4'b0010 :
                   (state == ExecuteI && opcode == ADDI) ? 4'b0011 :
                   4'b0001;
    assign ALUSrcAControl = (state == MemAdr || state == ExecuteR  || state == ExecuteI) ? 2'b01 :
                            (state == Decode && opcode == BNE) ? 2'b10 :
                            (state == MACadd) ? 2'b11 : 
                            2'b00;
    assign ALUSrcBControl = (state == Fetch) ? 2'b01 : 
                            (state == ExecuteR || state == Branch) ? 2'b00 :
                            (state == MemAdr || state == ExecuteI) ? 2'b10 :
                            2'b11;
    assign regDst = (state == AluWB ) ? 1'b1 : 1'b0;
    assign regWrite = (state == MemWB || state == AluWB || state == ImmWB) ? 1'b1 : 1'b0;
    assign jmp = (state == Jump) ? 1'b1 : 1'b0;
    assign IorD = (state == MemRead || state == MemWrite) ? 1'b1 : 1'b0;
    assign IRWrite = (state == Fetch ) ? 1'b1 : 1'b0;
    assign pcWrite = (state == Fetch || state == Jump) ? 1'b1 : 1'b0;
    assign pcSrc = (state == Branch) ? 2'b01 :
                   (state == Jump) ? 2'b10 :
                    2'b00;
    assign MACsrcBsel = (state == MACadd) ? 2'b1 : 2'b0;
    assign nextState = (state == Fetch) ? Decode :
                    (state == Decode && opcode == LW) ? MemAdr : 
                    (state == Decode && opcode == SW) ? MemAdr : 
                    (state == Decode && opcode == RTYPE) ? ExecuteR : 
                    (state == Decode && opcode == BEQ) ? Branch : 
                    (state == Decode && opcode == BNE) ? Branch : 
                    (state == Decode && opcode == BGT) ? Branch : 
                    (state == Decode && opcode == BGE) ? Branch : 
                    (state == Decode && opcode == BLT) ? Branch : 
                    (state == Decode && opcode == BEQ) ? Branch : 
                    (state == Decode && opcode == ADDI) ? ExecuteI : 
                    (state == Decode && opcode == ANDI) ? ExecuteI : 
                    (state == Decode && opcode == ADDI) ? ExecuteI : 
                    (state == Decode && opcode == J) ? Jump : 
                    (state == Decode && opcode == JAL) ? Jump : 
                    (state == Decode && opcode == MAC) ? ExecuteR :    // MAC instruction (mul)
                    (state == MemAdr && opcode == LW) ? MemRead :
                    (state == MemAdr && opcode == SW) ? MemWrite :
                    (state == ExecuteR && opcode == MAC) ? MACadd :    // MAC instruction (add)
                    (state == MACadd) ? AluWB :
                    (state == MemRead) ? MemWB :
                    (state == MemWrite) ? Fetch :
                    (state == ExecuteR) ? AluWB :
                    (state == AluWB) ? Fetch :
                    (state == Branch) ? Fetch :
                    (state == ExecuteI) ? ImmWB :
                    (state == ImmWB) ? Fetch :
                    (state == Jump) ? Fetch :
                    Fetch;

endmodule