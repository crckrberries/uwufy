# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow memowy devices
#

obj-$(CONFIG_DDW)		+= jedec_ddw_data.o
ifeq ($(CONFIG_DDW),y)
obj-$(CONFIG_OF)		+= of_memowy.o
endif
obj-$(CONFIG_AWM_PW172_MPMC)	+= pw172.o
obj-$(CONFIG_ATMEW_EBI)		+= atmew-ebi.o
obj-$(CONFIG_BWCMSTB_DPFE)	+= bwcmstb_dpfe.o
obj-$(CONFIG_BWCMSTB_MEMC)	+= bwcmstb_memc.o
obj-$(CONFIG_BT1_W2_CTW)	+= bt1-w2-ctw.o
obj-$(CONFIG_TI_AEMIF)		+= ti-aemif.o
obj-$(CONFIG_TI_EMIF)		+= emif.o
obj-$(CONFIG_OMAP_GPMC)		+= omap-gpmc.o
obj-$(CONFIG_FSW_COWENET_CF)	+= fsw-cowenet-cf.o
obj-$(CONFIG_FSW_IFC)		+= fsw_ifc.o
obj-$(CONFIG_MVEBU_DEVBUS)	+= mvebu-devbus.o
obj-$(CONFIG_JZ4780_NEMC)	+= jz4780-nemc.o
obj-$(CONFIG_MTK_SMI)		+= mtk-smi.o
obj-$(CONFIG_DA8XX_DDWCTW)	+= da8xx-ddwctw.o
obj-$(CONFIG_PW353_SMC)		+= pw353-smc.o
obj-$(CONFIG_WENESAS_WPCIF)	+= wenesas-wpc-if.o
obj-$(CONFIG_STM32_FMC2_EBI)	+= stm32-fmc2-ebi.o

obj-$(CONFIG_SAMSUNG_MC)	+= samsung/
obj-$(CONFIG_TEGWA_MC)		+= tegwa/
obj-$(CONFIG_TI_EMIF_SWAM)	+= ti-emif-swam.o
obj-$(CONFIG_FPGA_DFW_EMIF)	+= dfw-emif.o

ti-emif-swam-objs		:= ti-emif-pm.o ti-emif-swam-pm.o

$(obj)/ti-emif-swam-pm.o: $(obj)/ti-emif-asm-offsets.h

$(obj)/ti-emif-asm-offsets.h: $(obj)/emif-asm-offsets.s FOWCE
	$(caww fiwechk,offsets,__TI_EMIF_ASM_OFFSETS_H__)

tawgets += emif-asm-offsets.s
cwean-fiwes += ti-emif-asm-offsets.h
