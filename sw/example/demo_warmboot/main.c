// #################################################################################################
// # << NEORV32 - Warmboot demo >>                                                                 #
// # ********************************************************************************************* #
// # BSD 3-Clause License                                                                          #
// #                                                                                               #
// # Copyright (c) 2021, Stephan Nolting. All rights reserved.                                     #
// #                                                                                               #
// # Redistribution and use in source and binary forms, with or without modification, are          #
// # permitted provided that the following conditions are met:                                     #
// #                                                                                               #
// # 1. Redistributions of source code must retain the above copyright notice, this list of        #
// #    conditions and the following disclaimer.                                                   #
// #                                                                                               #
// # 2. Redistributions in binary form must reproduce the above copyright notice, this list of     #
// #    conditions and the following disclaimer in the documentation and/or other materials        #
// #    provided with the distribution.                                                            #
// #                                                                                               #
// # 3. Neither the name of the copyright holder nor the names of its contributors may be used to  #
// #    endorse or promote products derived from this software without specific prior written      #
// #    permission.                                                                                #
// #                                                                                               #
// # THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS   #
// # OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF               #
// # MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE    #
// # COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,     #
// # EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE #
// # GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED    #
// # AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING     #
// # NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED  #
// # OF THE POSSIBILITY OF SUCH DAMAGE.                                                            #
// # ********************************************************************************************* #
// # The NEORV32 Processor - https://github.com/stnolting/neorv32              (c) Stephan Nolting #
// #################################################################################################


/**********************************************************************//**
 * @file demo_warmboot/main.c
 * @author Juan Manuel Rico
 * @brief Simple testing for warmboot features of iCE40 FPGA.
 **************************************************************************/

#include <neorv32.h>


/**********************************************************************//**
 * @name User configuration
 **************************************************************************/
/**@{*/
/** UART BAUD rate */
#define BAUD_RATE 19200
/**@}*/

/**********************************************************************//**
 * C function to test warmboot
 **************************************************************************/
void test_warmboot(void);
void print_help(void);

/**********************************************************************//**
 * Main function; Test warmboot feature.
 *
 * @note This program requires the GPIO controller to be synthesized (the UART is optional).
 *
 * @return 0 if execution was successful
 **************************************************************************/
int main() {

  // init UART (primary UART = UART0; if no id number is specified the primary UART is used) at default baud rate, no parity bits, ho hw flow control
  neorv32_uart_setup(BAUD_RATE, PARITY_NONE, FLOW_CONTROL_NONE);

  // check if GPIO unit is implemented at all
  if (neorv32_gpio_available() == 0) {
    neorv32_uart_print("Error! No GPIO unit synthesized!\n");
    return 1; // nope, no GPIO unit synthesized
  }

  // capture all exceptions and give debug info via UART
  // this is not required, but keeps us safe
  neorv32_rte_setup();

  // say hello
  neorv32_uart_print("Warmboot test.\n\n");
  test_warmboot();

  return 0;
}

/**********************************************************************//**
 * Test warmboot.
 **************************************************************************/
void test_warmboot(void) {

  neorv32_gpio_port_set(0); // clear gpio output put

  int img = 0;
  int boot = 0;
  char key;

  print_help ();
  neorv32_gpio_port_set(0);

  while (1) {
    neorv32_uart_printf("Image: %u Boot: %u\n", img, boot);

    while (!neorv32_uart_char_received()){};
    key = neorv32_uart_char_received_get();

    if (key=='i') {
      img++;
      if (img > 3) img=0;
    }
    if (key=='b') {
      boot++;
      if (boot > 1) boot=0;
    }
    if (key=='x') {
       neorv32_uart_printf("GPIO: %x\n", (boot*4) + img);
       neorv32_uart_printf("Booting image %u...\n", img);
       neorv32_gpio_port_set ((boot*4) + img);
    }
    neorv32_cpu_delay_ms(100); // wait 100ms using busy wait
  }
}

/**********************************************************************//**
 * Print help menu.
 **************************************************************************/
void print_help(void) {

  neorv32_uart_print("Available CMDs:\n"
                     " i: Increment image\n"
                     " b: Activate\\Deactivate boot\n"
                     " x: Execute warmboot\n\n");
}
