`timescale  1ns / 1ps
`include "ALU.v"
module tb_ALU;

// ALU Parameters
parameter PERIOD  = 10;


// ALU Inputs
reg   [31:0]  A                            = 0 ;
reg   [31:0]  B                            = 0 ;
reg   [2:0]  ALUctr                        = 0 ;

// ALU Outputs
wire[31:0] Result                          ;
wire  Zero                                 ;
wire  Overflow                             ;
wire[31:0]Add_Result                       ;
wire[31:0]Less_Result                      ;
wire[31:0]OR_Result                        ;


ALU  u_ALU (
    .A                       ( A                      [31:0] ),
    .B                       ( B                      [31:0] ),
    .ALUctr                  ( ALUctr                 [2:0]  ),
    .Result                  ( Result                        ),
    .Zero                    ( Zero                          ),
    .Overflow                ( Overflow                      ),
    .Add_Result              (Add_Result                     ),
    .Less_Result             ( Less_Result                   ),
    .OR_Result               ( OR_Result                     )
);

initial
begin
    $dumpfile("tb_ALU.vcd");
    $dumpvars;
      //addu          
	    ALUctr=3'b000;
         A=32'hf2340000;
         B=32'h80000000;
    #20  A=32'h7fffffff;
         B=32'h70000001;
    #20  A=32'hffffffff;
         B=32'h00000001;
    //add
         ALUctr=3'b001;
         A=32'hf2340000;
         B=32'h80000000;
    #20  A=32'h7fffffff;
         B=32'h70000001;
    #20  A=32'h7fffffff;
         B=32'hf0000001;
    #20  A=32'hffffffff;
         B=32'h00000001;
			
	//or
    #20  ALUctr=3'b010;        
         A=32'h00000000;
         B=32'h00000000;
    #20  A=32'h7fffffff;
         B=32'hf0000001;
    
    //subu
    #20  ALUctr=3'b100;        
         A=32'h72340000;
         B=32'h60000000;
    #20  A=32'h7fffffff;
         B=32'hf0000001;
    #20  A=32'hffffffff;
         B=32'hffffffff;
    #20  A=32'hf0000000;
         B=32'h0fffffff; 
			
	 //sub    
    #20  ALUctr=3'b101;        
         A=32'h72340000;
         B=32'h60000000;
    #20  A=32'h7fffffff;
         B=32'hf0000001;
    #20  A=32'hf00fffff;
         B=32'h7ffffff1;
    #20  A=32'hffffffff;
         B=32'hffffffff;
    #20  A=32'hf0000000;
         B=32'h0fffffff;
     //sltu
    #20  ALUctr=3'b110;        
         A=32'h72340000;
         B=32'hf0000000;
    #20  A=32'h7000000f;
         B=32'h7f000001;
    #20  A=32'hf0001231;
         B=32'h7ac34545;
    //slt
    #20  ALUctr=3'b111;        
         A=32'h72340000;
         B=32'hf0000000;
    #20  A=32'h7000000f;
         B=32'h7f000001;
    #20  A=32'hf0001231;
         B=32'h7ac34545;
    $finish;
end

endmodule