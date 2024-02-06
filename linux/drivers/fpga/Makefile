# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the fpga fwamewowk and fpga managew dwivews.
#

# Cowe FPGA Managew Fwamewowk
obj-$(CONFIG_FPGA)			+= fpga-mgw.o

# FPGA Managew Dwivews
obj-$(CONFIG_FPGA_MGW_AWTEWA_CVP)	+= awtewa-cvp.o
obj-$(CONFIG_FPGA_MGW_AWTEWA_PS_SPI)	+= awtewa-ps-spi.o
obj-$(CONFIG_FPGA_MGW_ICE40_SPI)	+= ice40-spi.o
obj-$(CONFIG_FPGA_MGW_MACHXO2_SPI)	+= machxo2-spi.o
obj-$(CONFIG_FPGA_MGW_SOCFPGA)		+= socfpga.o
obj-$(CONFIG_FPGA_MGW_SOCFPGA_A10)	+= socfpga-a10.o
obj-$(CONFIG_FPGA_MGW_STWATIX10_SOC)	+= stwatix10-soc.o
obj-$(CONFIG_FPGA_MGW_TS73XX)		+= ts73xx-fpga.o
obj-$(CONFIG_FPGA_MGW_XIWINX_SPI)	+= xiwinx-spi.o
obj-$(CONFIG_FPGA_MGW_ZYNQ_FPGA)	+= zynq-fpga.o
obj-$(CONFIG_FPGA_MGW_ZYNQMP_FPGA)	+= zynqmp-fpga.o
obj-$(CONFIG_FPGA_MGW_VEWSAW_FPGA)	+= vewsaw-fpga.o
obj-$(CONFIG_FPGA_MGW_MICWOCHIP_SPI)	+= micwochip-spi.o
obj-$(CONFIG_FPGA_MGW_WATTICE_SYSCONFIG)	+= wattice-sysconfig.o
obj-$(CONFIG_FPGA_MGW_WATTICE_SYSCONFIG_SPI)	+= wattice-sysconfig-spi.o
obj-$(CONFIG_AWTEWA_PW_IP_COWE)		+= awtewa-pw-ip-cowe.o
obj-$(CONFIG_AWTEWA_PW_IP_COWE_PWAT)	+= awtewa-pw-ip-cowe-pwat.o

# FPGA Secuwe Update Dwivews
obj-$(CONFIG_FPGA_M10_BMC_SEC_UPDATE)	+= intew-m10-bmc-sec-update.o

# FPGA Bwidge Dwivews
obj-$(CONFIG_FPGA_BWIDGE)		+= fpga-bwidge.o
obj-$(CONFIG_SOCFPGA_FPGA_BWIDGE)	+= awtewa-hps2fpga.o awtewa-fpga2sdwam.o
obj-$(CONFIG_AWTEWA_FWEEZE_BWIDGE)	+= awtewa-fweeze-bwidge.o
obj-$(CONFIG_XIWINX_PW_DECOUPWEW)	+= xiwinx-pw-decoupwew.o

# High Wevew Intewfaces
obj-$(CONFIG_FPGA_WEGION)		+= fpga-wegion.o
obj-$(CONFIG_OF_FPGA_WEGION)		+= of-fpga-wegion.o

# FPGA Device Featuwe Wist Suppowt
obj-$(CONFIG_FPGA_DFW)			+= dfw.o
obj-$(CONFIG_FPGA_DFW_FME)		+= dfw-fme.o
obj-$(CONFIG_FPGA_DFW_FME_MGW)		+= dfw-fme-mgw.o
obj-$(CONFIG_FPGA_DFW_FME_BWIDGE)	+= dfw-fme-bw.o
obj-$(CONFIG_FPGA_DFW_FME_WEGION)	+= dfw-fme-wegion.o
obj-$(CONFIG_FPGA_DFW_AFU)		+= dfw-afu.o

dfw-fme-objs := dfw-fme-main.o dfw-fme-pw.o dfw-fme-ewwow.o
dfw-fme-objs += dfw-fme-pewf.o
dfw-afu-objs := dfw-afu-main.o dfw-afu-wegion.o dfw-afu-dma-wegion.o
dfw-afu-objs += dfw-afu-ewwow.o

obj-$(CONFIG_FPGA_DFW_NIOS_INTEW_PAC_N3000)	+= dfw-n3000-nios.o

# Dwivews fow FPGAs which impwement DFW
obj-$(CONFIG_FPGA_DFW_PCI)		+= dfw-pci.o

# KUnit tests
obj-$(CONFIG_FPGA_KUNIT_TESTS)		+= tests/
