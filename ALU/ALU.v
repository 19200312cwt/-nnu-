`include "Adder_32.v"
`include "Ctr.v"
`include "MUX2_1.v"
`include "MUX2_32.v"
`include "OR_32.v"
`include "MUX3.v"

module ALU(A,B,Result,Zero,Overflow,Add_Result,Less_Result,OR_Result,ALUctr);
input[31:0] A,B;
input[2:0] ALUctr;

output wire[31:0] Result;
output wire Zero,Overflow;
output wire[31:0] Add_Result,Less_Result,OR_Result;

wire Add_Carry,Add_Overflow,Add_Sign;
wire Less;
wire SUBctr,OVctr,SIGctr;
wire[1:0] OPctr;
Ctr   ctr
		(
		.ALUctr(ALUctr),
		.SUBctr(SUBctr),
		.OVctr(OVctr),
		.SIGctr(SIGctr),
		.OPctr(OPctr)
		);

Adder_32 adder_32
		(
		.A(A),
		.B(B),
		.cin(SUBctr),
		.Add_Carry(Add_Carry),
		.Add_Overflow(Add_Overflow),
		.Add_Sign(Add_Sign),
		.Add_Result(Add_Result),
		.Zero(Zero)
		);

MUX2_1  mux2_1
		(
		.choice(SIGctr),
		.in0(SUBctr^Add_Carry),
		.in1(Add_Overflow^Add_Sign),
		.res(Less)
	);
MUX2_32  mux2_32
		(
		.choice(Less),
		.in0(32'b0),
		.in1(32'b1),
		.res(Less_Result)
	);
	
OR_32  or_32
		(
		.A(A),
		.B(B),
		.res(OR_Result)
);

MUX3  mux3(
		.choice(OPctr),
		.in0(Add_Result),
		.in1(OR_Result),
		.in2(Less_Result),
		.res(Result)
	);
assign Overflow=Add_Overflow&OVctr;
endmodule
	