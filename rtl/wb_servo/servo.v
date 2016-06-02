module servo(   input clk,
   input rst,
   input [22:0] T0,
   input [22:0] T1,
   input [17:0] D0,
   input [17:0] D1,
   output reg servo0,
   output reg servo1

   );

reg [20:0] cont0,cont1;



always @(posedge clk)
begin
 if (rst) begin
    cont0 <= 0;
    cont1 <= 0;
    end 
 else begin 
   if(cont0 < T0)
       cont0 <= cont0 + 1;
   else
	cont0 <=0;
   if(cont1 < T1)
       cont1 <= cont1 + 1;
   else
	cont1 <=0;
	end
end


always @(posedge clk) begin
 if (rst) begin
    servo0 <= 1;
    servo1 <= 1;
    end 
 else begin
      if(cont0 < D0)
      servo0 <= 0;
	else
	servo0<=1;
      if(cont1 < D1)
      servo1 <= 0;
	else
	servo1<=1;
	
	end	
	   
  end
endmodule

