
//---------------------------------------------------------------------------
// Wishbone UART 
//
// Register Description:
//
//    0x00 UCR      [ 0 | 0 | 0 | tx_busy | 0 | 0 | rx_error | rx_avail ]
//    0x04 DATA
//
//---------------------------------------------------------------------------

module wb_servo (
	input              clk,
	input              reset,
	// Wishbone interface
	input              wb_stb_i,
	input              wb_cyc_i,
	output             wb_ack_o,
	input              wb_we_i,
	input       [31:0] wb_adr_i,
	input        [3:0] wb_sel_i,
	input       [31:0] wb_dat_i,
	output reg  [31:0] wb_dat_o,
	// Serial Wires

   	output  servo0,
   	output  servo1	
);

	reg [22:0] T0,T1;
	reg [17:0] D0,D1;


servo serv0 ( .clk(clk),
	.rst(resetn),
	.T0(T0),
	.T1(T1),
	.D0(D0),
	.D1(D1),
	.servo0(servo0),
	.servo1(servo1));



wire wb_rd = wb_stb_i & wb_cyc_i & ~wb_we_i;
wire wb_wr = wb_stb_i & wb_cyc_i &  wb_we_i;

reg  ack;

assign wb_ack_o       = wb_stb_i & wb_cyc_i & ack;

always @(posedge clk)
begin
	if (reset) begin
		wb_dat_o[31:8] <= 24'b0;
		ack    <= 0;
	end else begin
		wb_dat_o[31:8] <= 24'b0;
		ack    <= 0;

		if (wb_wr & ~ack) begin
			ack <= 1;

			case (wb_adr_i[3:2])
			2'b00: begin
				T0 <= wb_dat_i;
				end
			2'b01: begin
				D0 <= wb_dat_i;
				end			
			2'b10: begin
				T1 <= wb_dat_i;
				end
			2'b11: begin
				D1 <= wb_dat_i;
				end			

			default: begin
				wb_dat_o[7:0] <= 8'b0;
				 end
			endcase
		end 
	end
	
end

endmodule
