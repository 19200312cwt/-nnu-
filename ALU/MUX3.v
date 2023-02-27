module MUX3(choice,in0,in1,in2,res);
input[1:0] choice;
input [31:0]in0,in1,in2;
//wire tmp;
output  reg[31:0] res;

/*MUX2(
		.choice(choice[1]),
		.in1(in2),
		.in0(in1),
		.res(tmp)
);
MUX2(
		.choice(choice[0]),
		.in1(tmp),
		.in0(in0),
		.res(res)
);*/
always@(*)
case(choice)
	2'b00:
		res=in0;
	2'b01:
		res=in1;
	2'b10:
		res=in2;
	default:
		res=32'bz;
endcase
endmodule

