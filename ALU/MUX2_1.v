module MUX2_1
(
    input  wire  in0,     //Data
    input  wire in1,     //Data 
    input  wire choice,    //High: in1 ;Low: in0
    output reg res  
);
always@(choice or in0 or in1)
    if(!choice)  res=in0;
    else     res=in1;
endmodule 