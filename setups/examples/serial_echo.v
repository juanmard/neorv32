//---------------------------------------------------
// @brief  Serial example echo for FOMU (loopback).
// @author Juan Manuel Rico
//---------------------------------------------------
module serial_echo (
        input  clki,

        input click,

        inout  usb_dp,
        inout  usb_dn,
        output usb_dp_pu
);

    wire clk_48mhz;
    assign clk_48mhz = clki; // FOMU use 48Mhz external clock

    // Generate reset signal
    reg [5:0] reset_cnt = 0;
    wire reset = ~reset_cnt[5];
    always @(posedge clk_48mhz)
        reset_cnt <= reset_cnt + reset;

    // uart pipeline in
    reg [7:0]  uart_in_data;
    reg        uart_in_valid;
    wire       uart_in_ready;

    // uart pipeline out
    wire [7:0] uart_out_data;
    wire       uart_out_valid;
    reg        uart_out_ready;

    // Send text through the serial port
    localparam DELAY_WIDTH = 16;
    reg [DELAY_WIDTH-1:0] delay;
    reg end_transmition;

    always @(posedge clk_48mhz) begin
        // Reset.
        if (reset) begin
            delay <= 0;
            end_transmition <= 0;
            uart_in_valid <= 0;
        end else begin
            // If delay not active, send a new char.
            if (~|delay) begin

                // If char is not valid on UART, send it.
                if (!uart_in_valid) begin
                        uart_in_valid <= 1;
                        uart_in_data <= "R";

                 // If char not ready, but valid. End of transmision.
                end else if (!uart_in_ready) begin
                        end_transmition <= 1; // Need another cicle clock.

                // If char is valid, check end of transmision.
                end else begin
                    if (end_transmition) begin
                        end_transmition <= 0;
                        uart_in_valid <= 0;
                        delay <= 1;
                    end
                end

            // If delay not zero, increment to zero.
            end else begin
                delay = delay + 1;
            end
        end
    end

    // usb uart - this instanciates the entire USB device.
    usb_uart uart (
        .clk_48mhz (clk_48mhz),
        .reset     (reset),

        // pins
        .pin_usb_p (usb_dp),
        .pin_usb_n (usb_dn),

        // uart pipeline in
        .uart_in_data  (uart_in_data),
        .uart_in_valid (uart_in_valid),
        .uart_in_ready (uart_in_ready),

        // uart pipeline out
        .uart_out_data  (uart_out_data),
        .uart_out_valid (uart_out_valid),
        .uart_out_ready (uart_out_ready)

        // debug
        //.debug (debug)
    );

    // USB Host Detect Pull Up
    assign usb_dp_pu = 1'b1;

endmodule

