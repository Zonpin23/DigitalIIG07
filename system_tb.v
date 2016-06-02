//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
`timescale 1 ns / 100 ps

module system_tb;

//----------------------------------------------------------------------------
// Parameter (may differ for physical synthesis)
//----------------------------------------------------------------------------
parameter tck              = 10;       // clock period in ns
parameter uart_baud_rate   = 1152000;  // uart baud rate for simulation 

parameter clk_freq = 1000000000 / tck; // Frequenzy in HZ
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
reg        clk;
reg        rst;
wire       led;

reg [7:0] data;
reg [7:0]gpio_dir;

//wire [7:0] spi_mosi;
wire [7:0] gpio_io;

wire servo0,servo1;

//----------------------------------------------------------------------------
// UART STUFF (testbench uart, simulating a comm. partner)
//----------------------------------------------------------------------------
wire         uart_rxd;
wire         uart_txd;

genvar 		     i;
   generate 
      for (i=0;i<8;i=i+1)  begin: gpio_tris
	 assign gpio_io[i] = ~(gpio_dir[i]) ? data[i] : 1'bz;
	 
	 end
   endgenerate

//----------------------------------------------------------------------------
// Device Under Test 
//----------------------------------------------------------------------------
system #(
	.clk_freq(           clk_freq         ),
	.uart_baud_rate(     uart_baud_rate   )
) dut  (
	.clk(          clk    ),
	// Debug
	.rst(          rst    ),
	.led(          led    ),
	// Uart
	.uart_rxd(  uart_rxd  ),
	.uart_txd(  uart_txd  ),
	.gpio_io(gpio_io),
	.servo0( servo0 ),
	.servo1( servo1 )
);

/* Clocking device */
initial         clk <= 0;
always #(tck/2) clk <= ~clk;

/* Simulation setup */
initial begin



	$dumpfile("system_tb.vcd");
	//$monitor("%b,%b,%b,%b",clk,rst,uart_txd,uart_rxd);
	$dumpvars(-1, dut, data, gpio_io, servo0, servo1);
	//$dumpvars(-1,clk,rst,uart_txd);
	// reset
	#0  rst <= 1;	
	#100  rst <= 0;	
	#100  rst <= 1;
	#100 gpio_dir<=8'hf0;
	#0 data <= 8'h0f;
	#100 gpio_dir<=8'hf0;
	#0 data <= 8'h0f;

	#(tck*4000000) $finish;
end



endmodule
