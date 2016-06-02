//---------------------------------------------------------------------------
// LatticeMico32 System On A Chip
//
// Top Level Design for the Xilinx Spartan 3-200 Starter Kit
//---------------------------------------------------------------------------

module system
#(

	parameter   bootram_file     = "../firmware/hw-test/image.ram",

	parameter   clk_freq         = 100000000,
	parameter   uart_baud_rate   = 115200
) (
	input             clk, 
	// Debug 
	output            led,
	input             rst,

        // CPU Interface
        input             [12:0] addr,
        input             [7:0]  sram_data,
        input             nwe,
        input             noe,
        input             ncs,

	//SERVO

	output  servo0,
   	output  servo1,

	//GPIO
	inout             [7:0] gpio_io,

	// UART
	input             uart_rxd, 
	output            uart_txd,
	input             uart_rxd1, 
	output            uart_txd1,

	//SPI0
	input             miso, 
	output            mosi,
	output            sck,
	output 		  ss


);
	
//------------------------------------------------------------------
// Whishbone Wires
//------------------------------------------------------------------
wire         gnd   =  1'b0;
wire   [3:0] gnd4  =  4'h0;
wire  [31:0] gnd32 = 32'h00000000;

 
wire [31:0]  lm32i_adr,
             lm32d_adr,
             bram0_adr,
             sram0_adr,
             servo0_adr,
             gpio0_adr,
             uart0_adr,
             timer0_adr,
             spi0_adr;


wire [31:0]  lm32i_dat_r,
             lm32i_dat_w,
             lm32d_dat_r,
             lm32d_dat_w,
             bram0_dat_r,
             bram0_dat_w,
             sram0_dat_w,
             sram0_dat_r,
             servo0_dat_r,
             servo0_dat_w,
             gpio0_dat_r,
             gpio0_dat_w,
             uart0_dat_r,
             uart0_dat_w,
             timer0_dat_r,
             timer0_dat_w,
             spi0_dat_r,
             spi0_dat_w;




wire [3:0]   lm32i_sel,
             lm32d_sel,
             bram0_sel,
             sram0_sel,
             servo0_sel,
             gpio0_sel,
             uart0_sel,
             timer0_sel,
             spi0_sel;


wire         lm32i_we,
             lm32d_we,
             bram0_we,
             sram0_we,
             servo0_we,
             gpio0_we,
             uart0_we,
             timer0_we,
             spi0_we;

wire         lm32i_cyc,
             lm32d_cyc,
             bram0_cyc,
             sram0_cyc,
             servo0_cyc,
             gpio0_cyc,
             uart0_cyc,
             timer0_cyc,
             spi0_cyc;

wire         lm32i_stb,
             lm32d_stb,
             bram0_stb,
             sram0_stb,
             servo0_stb,
             gpio0_stb,
             uart0_stb,
             timer0_stb,
             spi0_stb;

wire         lm32i_ack,
             lm32d_ack,
             bram0_ack,
             sram0_ack,
             servo0_ack,
             gpio0_ack,
             uart0_ack,
             timer0_ack,
             spi0_ack;

wire         lm32i_rty,
             lm32d_rty;

wire         lm32i_err,
             lm32d_err;

wire         lm32i_lock,
             lm32d_lock;

wire [2:0]   lm32i_cti,
             lm32d_cti;

wire [1:0]   lm32i_bte,
             lm32d_bte;

//---------------------------------------------------------------------------
// Interrupts
//---------------------------------------------------------------------------
wire [31:0]  intr_n;
wire         uart0_intr = 0;
wire   [1:0] timer0_intr;
wire         gpio0_intr;

assign intr_n = { 28'hFFFFFFF, ~timer0_intr[1], ~gpio0_intr, ~timer0_intr[0], ~uart0_intr };

//---------------------------------------------------------------------------
// Wishbone Interconnect
//---------------------------------------------------------------------------
conbus #(
	.s_addr_w(3),
	.s0_addr(3'b000),	// bram     0x00000000 
	.s1_addr(3'b001),	// servo    0x10000000 
	.s2_addr(3'b010),	// gpio     0x20000000 
	.s3_addr(3'b011),	// uart0    0x30000000 
	.s4_addr(3'b100),	// timer    0x40000000 
	.s5_addr(3'b101)	// spi      0x50000000 




) conbus0(
	.sys_clk( clk ),
	.sys_rst( ~rst ),
	// Master0
	.m0_dat_i(  lm32i_dat_w  ),
	.m0_dat_o(  lm32i_dat_r  ),
	.m0_adr_i(  lm32i_adr    ),
	.m0_we_i (  lm32i_we     ),
	.m0_sel_i(  lm32i_sel    ),
	.m0_cyc_i(  lm32i_cyc    ),
	.m0_stb_i(  lm32i_stb    ),
	.m0_ack_o(  lm32i_ack    ),
	// Master1
	.m1_dat_i(  lm32d_dat_w  ),
	.m1_dat_o(  lm32d_dat_r  ),
	.m1_adr_i(  lm32d_adr    ),
	.m1_we_i (  lm32d_we     ),
	.m1_sel_i(  lm32d_sel    ),
	.m1_cyc_i(  lm32d_cyc    ),
	.m1_stb_i(  lm32d_stb    ),
	.m1_ack_o(  lm32d_ack    ),
	// Master2
	.m2_dat_i(  gnd32  ),
	.m2_adr_i(  gnd32  ),
	.m2_sel_i(  gnd4   ),
	.m2_cyc_i(  gnd    ),
	.m2_stb_i(  gnd    ),
	// Master3
	.m3_dat_i(  gnd32  ),
	.m3_adr_i(  gnd32  ),
	.m3_sel_i(  gnd4   ),
	.m3_cyc_i(  gnd    ),
	.m3_stb_i(  gnd    ),
	// Master4
	.m4_dat_i(  gnd32  ),
	.m4_adr_i(  gnd32  ),
	.m4_sel_i(  gnd4   ),
	.m4_cyc_i(  gnd    ),
	.m4_stb_i(  gnd    ),
	// Master5
	.m5_dat_i(  gnd32  ),
	.m5_adr_i(  gnd32  ),
	.m5_sel_i(  gnd4   ),
	.m5_cyc_i(  gnd    ),
	.m5_stb_i(  gnd    ),
	// Master6
	.m6_dat_i(  gnd32  ),
	.m6_adr_i(  gnd32  ),
	.m6_sel_i(  gnd4   ),
	.m6_cyc_i(  gnd    ),
	.m6_stb_i(  gnd    ),


	// Slave0
	.s0_dat_i(  bram0_dat_r ),
	.s0_dat_o(  bram0_dat_w ),
	.s0_adr_o(  bram0_adr   ),
	.s0_sel_o(  bram0_sel   ),
	.s0_we_o(   bram0_we    ),
	.s0_cyc_o(  bram0_cyc   ),
	.s0_stb_o(  bram0_stb   ),
	.s0_ack_i(  bram0_ack   ),
	// Slave1
	.s1_dat_i(  servo0_dat_r ),
	.s1_dat_o(  servo0_dat_w ),
	.s1_adr_o(  servo0_adr   ),
	.s1_sel_o(  servo0_sel   ),
	.s1_we_o(   servo0_we    ),
	.s1_cyc_o(  servo0_cyc   ),
	.s1_stb_o(  servo0_stb   ),
	.s1_ack_i(  servo0_ack   ),
	// Slave2
	.s2_dat_i(  gpio0_dat_r ),
	.s2_dat_o(  gpio0_dat_w ),
	.s2_adr_o(  gpio0_adr   ),
	.s2_sel_o(  gpio0_sel   ),
	.s2_we_o(   gpio0_we    ),
	.s2_cyc_o(  gpio0_cyc   ),
	.s2_stb_o(  gpio0_stb   ),
	.s2_ack_i(  gpio0_ack   ),
	// Slave3
	.s3_dat_i(  uart0_dat_r ),
	.s3_dat_o(  uart0_dat_w ),
	.s3_adr_o(  uart0_adr   ),
	.s3_sel_o(  uart0_sel   ),
	.s3_we_o(   uart0_we    ),
	.s3_cyc_o(  uart0_cyc   ),
	.s3_stb_o(  uart0_stb   ),
	.s3_ack_i(  uart0_ack   ),
	// Slave4
	.s4_dat_i(  timer0_dat_r ),
	.s4_dat_o(  timer0_dat_w ),
	.s4_adr_o(  timer0_adr   ),
	.s4_sel_o(  timer0_sel   ),
	.s4_we_o(   timer0_we    ),
	.s4_cyc_o(  timer0_cyc   ),
	.s4_stb_o(  timer0_stb   ),
	.s4_ack_i(  timer0_ack   ),
	//Slave5
	.s5_dat_i(  spi0_dat_r ),
	.s5_dat_o(  spi0_dat_w ),
	.s5_adr_o(  spi0_adr   ),
	.s5_sel_o(  spi0_sel   ),
	.s5_we_o(   spi0_we    ),
	.s5_cyc_o(  spi0_cyc   ),
	.s5_stb_o(  spi0_stb   ),
	.s5_ack_i(  spi0_ack   )


);


//---------------------------------------------------------------------------
// LM32 CPU 
//---------------------------------------------------------------------------
lm32_cpu lm0 (
	.clk_i(  clk  ),
	.rst_i(  ~rst  ),
	.interrupt_n(  intr_n  ),
	//
	.I_ADR_O(  lm32i_adr    ),
	.I_DAT_I(  lm32i_dat_r  ),
	.I_DAT_O(  lm32i_dat_w  ),
	.I_SEL_O(  lm32i_sel    ),
	.I_CYC_O(  lm32i_cyc    ),
	.I_STB_O(  lm32i_stb    ),
	.I_ACK_I(  lm32i_ack    ),
	.I_WE_O (  lm32i_we     ),
	.I_CTI_O(  lm32i_cti    ),
	.I_LOCK_O( lm32i_lock   ),
	.I_BTE_O(  lm32i_bte    ),
	.I_ERR_I(  lm32i_err    ),
	.I_RTY_I(  lm32i_rty    ),
	//
	.D_ADR_O(  lm32d_adr    ),
	.D_DAT_I(  lm32d_dat_r  ),
	.D_DAT_O(  lm32d_dat_w  ),
	.D_SEL_O(  lm32d_sel    ),
	.D_CYC_O(  lm32d_cyc    ),
	.D_STB_O(  lm32d_stb    ),
	.D_ACK_I(  lm32d_ack    ),
	.D_WE_O (  lm32d_we     ),
	.D_CTI_O(  lm32d_cti    ),
	.D_LOCK_O( lm32d_lock   ),
	.D_BTE_O(  lm32d_bte    ),
	.D_ERR_I(  lm32d_err    ),
	.D_RTY_I(  lm32d_rty    )
);
	
//---------------------------------------------------------------------------
// Block RAM
//---------------------------------------------------------------------------
wb_bram #(
	.adr_width( 12 ),
	.mem_file_name( bootram_file )
) bram0 (
	.clk_i(  clk  ),
	.rst_i(  ~rst  ),
	//
	.wb_adr_i(  bram0_adr    ),
	.wb_dat_o(  bram0_dat_r  ),
	.wb_dat_i(  bram0_dat_w  ),
	.wb_sel_i(  bram0_sel    ),
	.wb_stb_i(  bram0_stb    ),
	.wb_cyc_i(  bram0_cyc    ),
	.wb_ack_o(  bram0_ack    ),
	.wb_we_i(   bram0_we     )
);

//---------------------------------------------------------------------------
// servo0
//---------------------------------------------------------------------------
 wb_servo ser0 (
	.clk(      clk          ),
	.reset(    ~rst          ),
	//
	.wb_adr_i( servo0_adr   ),
	.wb_dat_i( servo0_dat_w ),
	.wb_dat_o( servo0_dat_r ),
	.wb_stb_i( servo0_stb   ),
	.wb_cyc_i( servo0_cyc   ),
	.wb_we_i(  servo0_we    ),
	.wb_sel_i( servo0_sel   ),
	.wb_ack_o( servo0_ack   ), 
//	.intr(     timer0_intr  )
	.servo0( servo0 ),
	.servo1( servo1 )
);

//---------------------------------------------------------------------------
// General Purpose IO
//---------------------------------------------------------------------------

wire        gpio0_irq;

wb_gpio gpio0 (
	.clk(      clk          ),
	.rst(    ~rst          ),
	//
	.wb_adr_i( gpio0_adr    ),
	.wb_dat_i( gpio0_dat_w  ),
	.wb_dat_o( gpio0_dat_r  ),
	.wb_stb_i( gpio0_stb    ),
	.wb_cyc_i( gpio0_cyc    ),
	.wb_we_i(  gpio0_we     ),
	.wb_ack_o( gpio0_ack    ), 
	// GPIO
	.gpio_io(gpio_io)
);

//---------------------------------------------------------------------------
// uart0
//---------------------------------------------------------------------------
wire uart0_rxd;
wire uart0_txd;

wb_uart #(
	.clk_freq( clk_freq        ),
	.baud(     uart_baud_rate  )
) uart0 (
	.clk( clk ),
	.reset( ~rst ),
	//
	.wb_adr_i( uart0_adr ),
	.wb_dat_i( uart0_dat_w ),
	.wb_dat_o( uart0_dat_r ),
	.wb_stb_i( uart0_stb ),
	.wb_cyc_i( uart0_cyc ),
	.wb_we_i(  uart0_we ),
	.wb_sel_i( uart0_sel ),
	.wb_ack_o( uart0_ack ), 
//	.intr(       uart0_intr ),
	.uart_rxd( uart0_rxd ),
	.uart_txd( uart0_txd )
);

//---------------------------------------------------------------------------
// timer0
//---------------------------------------------------------------------------
wb_timer #(
	.clk_freq(   clk_freq  )
) timer0 (
	.clk(      clk          ),
	.reset(    ~rst          ),
	//
	.wb_adr_i( timer0_adr   ),
	.wb_dat_i( timer0_dat_w ),
	.wb_dat_o( timer0_dat_r ),
	.wb_stb_i( timer0_stb   ),
	.wb_cyc_i( timer0_cyc   ),
	.wb_we_i(  timer0_we    ),
	.wb_sel_i( timer0_sel   ),
	.wb_ack_o( timer0_ack   ),
	.intr(     timer0_intr  )
);


//---------------------------------------------------------------------------
// spi0
//---------------------------------------------------------------------------

wb_spi spi0(
	.clk(      clk          ),
	.reset(    ~rst          ),
	//
	.wb_adr_i(  spi0_adr   ),
	.wb_dat_i(  spi0_dat_w ),
	.wb_dat_o(  spi0_dat_r ),
	.wb_stb_i(  spi0_stb   ),
	.wb_cyc_i(  spi0_cyc   ),
	.wb_we_i (  spi0_we    ),
	.wb_sel_i(  spi0_sel   ),
	.wb_ack_o(  spi0_ack   ),
	.ss  (  ss    ), 
	.sck (  sck   ),
	.mosi(  mosi  ),
	.miso(  miso  )

);
//----------------------------------------------------------------------------
// Mux UART wires according to sw[0]
//----------------------------------------------------------------------------
//UART
assign uart_txd  = uart0_txd;
assign uart0_rxd = uart_rxd;
assign led       = ~uart_txd;
//SPI0
/*assign spi_mosi = spi0_mosi;
assign spi0_miso = spi_miso;
assign spi_sck = spi0_sck;
assign spi_ss = spi0_ss;
*/

endmodule 
