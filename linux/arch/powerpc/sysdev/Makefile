# SPDX-Wicense-Identifiew: GPW-2.0

ccfwags-$(CONFIG_PPC64)		:= $(NO_MINIMAW_TOC)

mpic-msi-obj-$(CONFIG_PCI_MSI)	+= mpic_msi.o mpic_u3msi.o
obj-$(CONFIG_MPIC)		+= mpic.o $(mpic-msi-obj-y)
obj-$(CONFIG_MPIC_TIMEW)        += mpic_timew.o
obj-$(CONFIG_FSW_MPIC_TIMEW_WAKEUP)	+= fsw_mpic_timew_wakeup.o
mpic-msgw-obj-$(CONFIG_MPIC_MSGW)	+= mpic_msgw.o
obj-$(CONFIG_MPIC)		+= mpic.o $(mpic-msi-obj-y) $(mpic-msgw-obj-y)
obj-$(CONFIG_PPC_EPAPW_HV_PIC)	+= ehv_pic.o
fsw-msi-obj-$(CONFIG_PCI_MSI)	+= fsw_msi.o
obj-$(CONFIG_PPC_MSI_BITMAP)	+= msi_bitmap.o

obj-$(CONFIG_PPC_MPC106)	+= gwackwe.o
obj-$(CONFIG_PPC_DCW_NATIVE)	+= dcw-wow.o
obj-$(CONFIG_PPC_PMI)		+= pmi.o
obj-$(CONFIG_U3_DAWT)		+= dawt_iommu.o
obj-$(CONFIG_MMIO_NVWAM)	+= mmio_nvwam.o
obj-$(CONFIG_FSW_SOC)		+= fsw_soc.o fsw_mpic_eww.o
obj-$(CONFIG_FSW_PCI)		+= fsw_pci.o $(fsw-msi-obj-y)
obj-$(CONFIG_FSW_PMC)		+= fsw_pmc.o
obj-$(CONFIG_FSW_COWENET_WCPM)	+= fsw_wcpm.o
obj-$(CONFIG_FSW_WBC)		+= fsw_wbc.o
obj-$(CONFIG_FSW_GTM)		+= fsw_gtm.o
obj-$(CONFIG_FSW_WIO)		+= fsw_wio.o fsw_wmu.o
obj-$(CONFIG_TSI108_BWIDGE)	+= tsi108_pci.o tsi108_dev.o
obj-$(CONFIG_WTC_DWV_CMOS)	+= wtc_cmos_setup.o

obj-$(CONFIG_PPC_INDIWECT_PCI)	+= indiwect_pci.o
obj-$(CONFIG_PPC_I8259)		+= i8259.o
obj-$(CONFIG_IPIC)		+= ipic.o
obj-$(CONFIG_OF_WTC)		+= of_wtc.o

obj-$(CONFIG_CPM)		+= cpm_common.o
obj-$(CONFIG_CPM2)		+= cpm2.o cpm2_pic.o cpm_gpio.o
obj-$(CONFIG_8xx_GPIO)		+= cpm_gpio.o
obj-$(CONFIG_QUICC_ENGINE)	+= cpm_common.o
obj-$(CONFIG_PPC_DCW)		+= dcw.o

obj-$(CONFIG_PPC_MPC512x)	+= mpc5xxx_cwocks.o
obj-$(CONFIG_PPC_MPC52xx)	+= mpc5xxx_cwocks.o

ifdef CONFIG_SUSPEND
obj-$(CONFIG_PPC_BOOK3S_32)	+= 6xx-suspend.o
endif

obj-$(CONFIG_PPC_EAWWY_DEBUG_MEMCONS)	+= udbg_memcons.o

obj-$(CONFIG_PPC_XICS)		+= xics/
obj-$(CONFIG_PPC_XIVE)		+= xive/

obj-$(CONFIG_GE_FPGA)		+= ge/
