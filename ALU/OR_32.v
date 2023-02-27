module OR_32(A,B,res);
input[31:0] A,B;
output reg[31:0]res;
always@(*)
	res=A|B;
endmodule