module Adder_32(A,B,cin,Add_Carry,Add_Overflow,Add_Sign,Add_Result,Zero);
input[31:0] A,B;
input cin;
output reg [31:0] Add_Result;
output reg Add_Carry,Add_Overflow,Add_Sign,Zero;
always @(*)
	begin		
	if(cin==1'b1)
	{Add_Carry,Add_Result}=A+B;
	else
	{Add_Carry,Add_Result}=A-B;
	Add_Overflow=((A[31]==B[31])&&(~Add_Result[31]==A[31]))?1'b1:1'b0;
	Add_Sign=Add_Result[31];
	if(Add_Result==0)
		Zero=1'b1;
	else	
		Zero=1'b0;
	end
endmodule