module MUX2_32
(
    input  wire[31:0]  in0,     //Data
    input  wire[31:0] in1,     //Data 
    input  wire choice,    //High: in1 ;Low: in0
    output reg[31:0] res  
);
always@(choice or in0 or in1)
    if(!choice)  res=in0;
    else     res=in1;
endmodule 