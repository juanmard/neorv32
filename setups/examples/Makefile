OSFLOW := ../osflow
EXAMPLES := ../../examples
TEMPLATES := ../../../rtl/templates
MV := mv

TASK := clean $(BITSTREAM)

FOMU_REV ?= pvt

ifndef BOARD
$(error BOARD needs to be set to 'Fomu', 'iCESugar' or 'UPDuino_v3'!)
endif

RTL_USB_DIR = ../../examples/serial-usb
SOURCES = \
        $(RTL_USB_DIR)/edge_detect.v \
        $(RTL_USB_DIR)/serial.v \
        $(RTL_USB_DIR)/usb_fs_in_arb.v \
        $(RTL_USB_DIR)/usb_fs_in_pe.v \
        $(RTL_USB_DIR)/usb_fs_out_arb.v \
        $(RTL_USB_DIR)/usb_fs_out_pe.v \
        $(RTL_USB_DIR)/usb_fs_pe.v \
        $(RTL_USB_DIR)/usb_fs_rx.v \
        $(RTL_USB_DIR)/usb_fs_tx_mux.v \
        $(RTL_USB_DIR)/usb_fs_tx.v \
        $(RTL_USB_DIR)/usb_reset_det.v \
        $(RTL_USB_DIR)/usb_serial_ctrl_ep.v \
        $(RTL_USB_DIR)/usb_uart_bridge_ep.v \
        $(RTL_USB_DIR)/usb_uart_core.v \
        $(RTL_USB_DIR)/usb_uart_i40.v \
		../../examples/serial_echo.v

run:
	$(eval TASK ?= clean $(BITSTREAM))
	$(MAKE) -C $(OSFLOW)/$(BOARD)/ \
	  BOARD_SRC=$(EXAMPLES)/neorv32_$(BOARD)_BoardTop_$(DESIGN).vhd \
	  TOP=neorv32_$(BOARD)_BoardTop_$(DESIGN) \
	  ID=$(DESIGN) \
	  $(TASK)
	$(MV) $(OSFLOW)/$(BOARD)/$(BITSTREAM) ./

Fomu:
ifeq ($(DESIGN),Minimal)
	$(eval IMEM_SRC := ../../../rtl/core/neorv32_imem.vhd)
else
	$(eval IMEM_SRC := ../devices/ice40/neorv32_imem.ice40up_spram.vhd)
endif
	$(MAKE) \
	  BITSTREAM=neorv32_$(BOARD)_$(FOMU_REV)_$(DESIGN).bit \
	  NEORV32_MEM_SRC="${IMEM_SRC} ../devices/ice40/neorv32_dmem.ice40up_spram.vhd" \
	  run

iCESugar:
	$(MAKE) \
	  BITSTREAM=neorv32_$(BOARD)_$(DESIGN).bit \
	  run

UPduino_v3:
	$(MAKE) \
	  BITSTREAM=neorv32_$(BOARD)_$(DESIGN).bit \
	  run

Minimal:
	$(MAKE) \
	  DESIGN=$@ \
	  DESIGN_SRC=$(TEMPLATES)/processor/neorv32_ProcessorTop_Minimal*.vhd \
	  $(BOARD)

MinimalBoot:
	$(MAKE) \
	  DESIGN=$@ \
	  DESIGN_SRC=$(TEMPLATES)/processor/neorv32_ProcessorTop_MinimalBoot.vhd \
	  $(BOARD)

UP5KDemo:
	$(MAKE) \
	  DESIGN=$@ \
	  DESIGN_SRC=$(TEMPLATES)/processor/neorv32_ProcessorTop_UP5KDemo.vhd \
	  $(BOARD)

MixedLanguage:
	$(MAKE) \
	  DESIGN=$@ \
	  DESIGN_SRC=$(TEMPLATES)/processor/neorv32_ProcessorTop_Minimal*.vhd \
	  NEORV32_VERILOG_SRC='$(SOURCES) ../devices/ice40/sb_ice40_components.v ../../examples/neorv32_Fomu_MixedLanguage_ClkGen.v' \
	  $(BOARD)

.PHONY: Fomu