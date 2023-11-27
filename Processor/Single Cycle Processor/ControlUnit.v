module ControlUnit(

	// 6-bit opcode
	input [5: 0] opcode,

	// control bit to indicate whether write from memory to register
	output reg memToReg,

	// control bit to indicate whether write in memory or not
	output reg memWrite,
	
	// control bit to indicate whether read from memory or not
	output reg memRead,
	
	// control bit to indicate whether it is branch instruction or not
	output reg branch,

	// control bit input to ALUControl
	output reg [3:0] ALUOp,

	// control bit for second source to ALU
	output reg ALUSrcBControl,

	// control bit for register destination
	output reg regDst,

	// control bit to indicate whether write in register or not
	output reg regWrite,

	// control bit to indicate whether it is jump instruction or not
	output reg jmp
);

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

	// ALUOp = 0  --> ALU Operation will be decided by funct value
	// ALUOp = 1  --> Addition
	// ALUOp = 2  --> And
	// ALUOp = 3  --> Or
	// ALUOp = 4  --> BEQ
	// ALUOp = 5  --> BNE
	// ALUOp = 6  --> BGT
	// ALUOp = 7  --> BGE
	// ALUOp = 8  --> BLT
	// ALUOp = 9  --> BLE
	always @ (opcode)
	begin
		case(opcode)
			RTYPE:
			begin
				memToReg = 0;
				memWrite = 0;
				memRead = 0;
				branch = 0;
				ALUOp = 4'b0000;
				ALUSrcBControl = 0;
				regDst = 1;  		// rd
				regWrite = 1;
				jmp = 0;
			end
			ADDI:
			begin
				memToReg = 0;
				memWrite = 0;
				memRead = 0;
				branch = 0;
				ALUOp = 4'b0001;	// 1
				ALUSrcBControl = 1;
				regDst = 0;			// rt
				regWrite = 1;
				jmp = 0;
			end
			ANDI:
			begin
				memToReg = 0;
				memWrite = 0;
				memRead = 0;
				branch = 0;
				ALUOp = 4'b0010;	// 2
				ALUSrcBControl = 1;
				regDst = 0;			// rt
				regWrite = 1;
				jmp = 0;
			end
			ORI:
			begin
				memToReg = 0;
				memWrite = 0;
				memRead = 0;
				branch = 0;
				ALUOp = 4'b0011;	// 3
				ALUSrcBControl = 1;
				regDst = 0;			// rt
				regWrite = 1;
				jmp = 0;
			end
			LW:
			begin
				memToReg = 1;
				memWrite = 0;
				memRead = 1;
				branch = 0;
				ALUOp = 4'b0001;	// 1
				ALUSrcBControl = 1;
				regDst = 0;			// rt
				regWrite = 1;
				jmp = 0;
			end
			SW:
			begin
				memToReg = 0;
				memWrite = 1;
				memRead = 0;
				branch = 0;
				ALUOp = 4'b0001;	// 1
				ALUSrcBControl = 1;
				regDst = 0;			// Don't care
				regWrite = 0;
				jmp = 0;
			end
			BEQ:
			begin
				memToReg = 0;
				memWrite = 0;
				memRead = 0;
				branch = 1;
				ALUOp = 4'b0100;	// 4
				ALUSrcBControl = 0;
				regDst = 0;			// Don't care
				regWrite = 0;
				jmp = 0;
			end
			BNE:
			begin
				memToReg = 0;
				memWrite = 0;
				memRead = 0;
				branch = 0;
				ALUOp = 4'b0101;	// 5
				ALUSrcBControl = 0;
				regDst = 0;			// Don't care
				regWrite = 0;
				jmp = 0;
			end
			BGT:
			begin
				memToReg = 0;
				memWrite = 0;
				memRead = 0;
				branch = 1;
				ALUOp = 4'b0110;	// 6
				ALUSrcBControl = 0;
				regDst = 0;			// Don't care
				regWrite = 0;
				jmp = 0;
			end
			BGE:
			begin
				memToReg = 0;
				memWrite = 0;
				memRead = 0;
				branch = 1;
				ALUOp = 4'b0111;	// 7
				ALUSrcBControl = 0;
				regDst = 0;			// Don't care
				regWrite = 0;
				jmp = 0;
			end
			BLT:
			begin
				memToReg = 0;
				memWrite = 0;
				memRead = 0;
				branch = 1;
				ALUOp = 4'b1000;	// 8
				ALUSrcBControl = 0;
				regDst = 0;			// Don't care
				regWrite = 0;
				jmp = 0;
			end
			BLE:
			begin
				memToReg = 0;
				memWrite = 0;
				memRead = 0;
				branch = 1;
				ALUOp = 4'b1001;	// 9
				ALUSrcBControl = 0;
				regDst = 0;			// Don't care
				regWrite = 0;
				jmp = 0;
			end
			J:
			begin
				memToReg = 0;
				memWrite = 0;
				memRead = 0;
				branch = 0;
				ALUOp = 4'b0000;     // Don't care
				ALUSrcBControl = 0; 
				regDst = 0;			// Don't care
				regWrite = 0;
				jmp = 1;
			end
			JAL:
			begin
				memToReg = 0;
				memWrite = 0;
				memRead = 0;
				branch = 0;
				ALUOp = 4'b0000;     // Don't care
				ALUSrcBControl = 0; 
				regDst = 0;			// Don't care
				regWrite = 0;
				jmp = 1;
			end
			default:
				begin
				memToReg = 0;
				memWrite = 0;
				memRead = 0;
				branch = 0;
				ALUOp = 4'b0000;    
				ALUSrcBControl = 0; 
				regDst = 0;		
				regWrite = 0;
				jmp = 0;
			end
		endcase
	end

endmodule