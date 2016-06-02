#include "soc-hw.h"


servo_t  *servo0 = (servo_t *)  0x10000000;
gpio_t   *gpio0  = (gpio_t *)   0x20000000;
uart_t   *uart0  = (uart_t *)   0x30000000;
timer_t   *timer0  = (timer_t *)   0x40000000;
spi_t	*spi0 	= (spi_t *)  	0x50000000;

isr_ptr_t isr_table[32];


void tic_isr();
/***************************************************************************
 * IRQ handling
 */
void isr_null()
{
}

void irq_handler(uint32_t pending)
{
	int i;

	for(i=0; i<32; i++) {
		if (pending & 0x01) (*isr_table[i])();
		pending >>= 1;
	}
}

void isr_init()
{
	int i;
	for(i=0; i<32; i++)
		isr_table[i] = &isr_null;
}

void isr_register(int irq, isr_ptr_t isr)
{
	isr_table[irq] = isr;
}

void isr_unregister(int irq)
{
	isr_table[irq] = &isr_null;
}


/***************************************************************************
 * TIMER Functions
 */
void msleep(uint32_t msec)
{
	uint32_t tcr;

	// Use timer0.1
	timer0->compare1 = (FCPU/1000)*msec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;

	do {
		//halt();
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}

void nsleep(uint32_t nsec)
{
	uint32_t tcr;

	// Use timer0.1
	timer0->compare1 = (FCPU/1000000)*nsec;
	timer0->counter1 = 0;
	timer0->tcr1 = TIMER_EN;

	do {
		//halt();
 		tcr = timer0->tcr1;
 	} while ( ! (tcr & TIMER_TRIG) );
}


uint32_t tic_msec;

void tic_isr()
{
	tic_msec++;
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;
}

void tic_init()
{
	tic_msec = 0;

	// Setup timer0.0
	timer0->compare0 = (FCPU/10000);
	timer0->counter0 = 0;
	timer0->tcr0     = TIMER_EN | TIMER_AR | TIMER_IRQEN;

	isr_register(1, &tic_isr);
}




/***************************************************************************
 * UART Functions
 */
void uart_init()
{
	//uart0->ier = 0x00;  // Interrupt Enable Register
	//uart0->lcr = 0x03;  // Line Control Register:    8N1
	//uart0->mcr = 0x00;  // Modem Control Register

	// Setup Divisor register (Fclk / Baud)
	//uart0->div = (FCPU/(57600*16));
}

char uart_getchar()
{   
	while (! (uart0->ucr & UART_DR)) ;
	return uart0->rxtx;
}

void uart_putchar(char c)
{
	while (uart0->ucr & UART_BUSY) ;
	uart0->rxtx = c;
}

void uart_putstr(char *str)
{
	char *c = str;
	while(*c) {
		uart_putchar(*c);
		c++;
	}
}
/*
***************************************************************************
 * GPIO Functions
 */


char gpio_get_in()
{   
	
	return gpio0->gpio_in;
}

char gpio_get_dir()
{   
	
	return gpio0->gpio_dir;
}



void gpio_put_out(char c)
{
	
	gpio0->gpio_out = c;
}

void gpio_put_dir(char c)
{
	
	gpio0->gpio_dir = c;
}

/*
***************************************************************************
 * SERVO Functions
 */

void servo_put_T0(int c)
{
	
	servo0->servo_T0 = c;
}

void servo_put_D0(int c)
{
	
	servo0->servo_D0 = c;
}
void servo_put_T1(int c)
{
	
	servo0->servo_T1 = c;
}

void servo_put_D1(int c)
{
	
	servo0->servo_D1 = c;
}



void servo_set_T0(unsigned int c)
{      
	
	unsigned int a = 100000*c;
	servo0->servo_T0 = a;
	
}

void servo_set_D0(unsigned int c)
{
	unsigned int tmp = (c * 10000);
	unsigned int b = (tmp/18);
	unsigned int g = b + 100000;
	servo0->servo_D0 = g;
}
void servo_set_T1(unsigned int c)
{       
	unsigned int a = 100000*c;
	servo0->servo_T1 = a;
}


void servo_set_D1(unsigned int c)
{
	unsigned int tmp = (c * 10000);
	unsigned int b = (tmp/18);
	unsigned int g = b + 100000;
	servo0->servo_D1 = g;
}



/*****************************************SPI0 Functions************/
/*
char spi_get_div(spi_t *spi){
	return spi->spi_divisor;
}

char spi_get_mosi(spi_t *spi){
	return spi->spi_rx_tx;

}

char spi_get_cs(spi_t *spi){
	return spi->spi_cs;
}

char spi_get_miso(spi_t *spi){
	while ((spi -> spi_run));
	return spi->spi_rx_tx;

}

void spi_set_div(spi_t *spi, char c){
	 spi->spi_divisor = c;
}

void spi_set_cs(spi_t *spi, char  c){
	spi->spi_cs=c;
}
void spi_set_mosi(spi_t *spi, char c){
	 while ((spi -> spi_run));
	 spi->	spi_rx_tx = c;
}

void spi_set_miso(spi_t *spi, char c){
	 while ((spi -> spi_run));
	 spi0->spi_rx_tx = c;
}
*/

/***************************************************************************
 * SPI Functions
 */
//These are the specific funtions for the rc522 rfid reader card

void spi_start()
{
	spi0->ucr=0x1;
	spi0->ucr=0x0;
}
unsigned char spi_read (char reg)
{
	//reg= reg<<1;
	uint32_t regAddress = (0x80 | (reg & 0x7E));
	regAddress = regAddress << 8;
	while(spi0->ucr & SPI_BUSY);
	spi0->data_in= regAddress;
	spi_start();
	while(spi0->ucr & SPI_BUSY);
	
	return spi0->data_out;	
}
void spi_write (char reg, char value)
{
	//reg=reg<<1;
	uint32_t regAddress=(reg & 0x7E);
	regAddress = regAddress << 8;
	uint32_t data0 = regAddress | value;
	while(spi0->ucr & SPI_BUSY);
	spi0->data_in=data0;
	spi_start();
}






