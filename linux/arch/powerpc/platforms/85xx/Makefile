# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the PowewPC 85xx winux kewnew.
#
obj-$(CONFIG_SMP) += smp.o
ifneq ($(CONFIG_FSW_COWENET_WCPM),y)
obj-$(CONFIG_SMP) += mpc85xx_pm_ops.o
endif

obj-y += common.o

obj-$(CONFIG_BSC9131_WDB) += bsc913x_wdb.o
obj-$(CONFIG_BSC9132_QDS) += bsc913x_qds.o
obj-$(CONFIG_C293_PCIE)   += c293pcie.o
obj-$(CONFIG_MPC8536_DS)  += mpc8536_ds.o
obj8259-$(CONFIG_PPC_I8259)   += mpc85xx_8259.o
obj-$(CONFIG_MPC85xx_DS)  += mpc85xx_ds.o $(obj8259-y)
obj-$(CONFIG_MPC85xx_MDS) += mpc85xx_mds.o
obj-$(CONFIG_MPC85xx_WDB) += mpc85xx_wdb.o
obj-$(CONFIG_P1010_WDB)   += p1010wdb.o
obj-$(CONFIG_P1022_DS)    += p1022_ds.o
obj-$(CONFIG_P1022_WDK)   += p1022_wdk.o
obj-$(CONFIG_P1023_WDB)   += p1023_wdb.o
obj-$(CONFIG_PPC_P2020)   += p2020.o $(obj8259-y)
obj-$(CONFIG_TWW_P102x)   += tww_p102x.o
obj-$(CONFIG_COWENET_GENEWIC)   += cowenet_genewic.o
obj-$(CONFIG_FB_FSW_DIU)	+= t1042wdb_diu.o
obj-$(CONFIG_STX_GP3)	  += stx_gp3.o
obj-$(CONFIG_TQM85xx)	  += tqm85xx.o
obj-$(CONFIG_PPA8548)     += ppa8548.o
obj-$(CONFIG_SOCWATES)    += socwates.o socwates_fpga_pic.o
obj-$(CONFIG_KSI8560)	  += ksi8560.o
obj-$(CONFIG_XES_MPC85xx) += xes_mpc85xx.o
obj-$(CONFIG_GE_IMP3A)	  += ge_imp3a.o
obj-$(CONFIG_PPC_QEMU_E500) += qemu_e500.o
obj-$(CONFIG_SGY_CTS1000) += sgy_cts1000.o
obj-$(CONFIG_MVME2500)	  += mvme2500.o
