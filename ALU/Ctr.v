module Ctr( ALUctr,SUBctr,OPctr,SIGctr,OVctr);
input [2:0] ALUctr;
output reg SUBctr,OVctr,SIGctr;
output reg[1:0] OPctr;


always@(*)
begin
	case(ALUctr)
	//addu
        3'b000:
            begin
            SUBctr=1'b0;
				OVctr=1'b0;
				SIGctr=1'b0;
				OPctr=2'b00;
            end
				
	//add
        3'b001:
            begin
				SUBctr=1'b0;
				OVctr=1'b1;
				SIGctr=1'b0;
				OPctr=2'b00;
            end
				
	//or
        3'b010:
            begin
            SUBctr=1'b0;
				OVctr=1'b0;
				SIGctr=1'b0;
				OPctr=2'b01;
            end
	//未用
			/*3'b011:
				begin
				end*/
	//subu
        3'b100:
            begin
				SUBctr=1'b1;
				OVctr=1'b0;
				SIGctr=1'b0;
				OPctr=2'b00;
            end
        
   //sub
        3'b101:
            begin
				SUBctr=1'b1;
				OVctr=1'b1;
				SIGctr=1'b0;
				OPctr=2'b00;
            end
		  //sltu
        3'b110:
            begin
				SUBctr=1'b1;
				OVctr=1'b0;
				SIGctr=1'b0;
				OPctr=2'b10;
            end
        //slt
        3'b111:
            begin                        
				SUBctr=1'b1;
				OVctr=1'b0;
				SIGctr=1'b1;
				OPctr=2'b10;
           end 
			  
			  default:
			  begin                        
				SUBctr=1'b0;
				OVctr=1'b0;
				SIGctr=1'b0;
				OPctr=2'b0;
           end 
    endcase
end
endmodule