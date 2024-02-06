# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow 52xx based boawds
#
obj-y				+= mpc52xx_pic.o mpc52xx_common.o mpc52xx_gpt.o
obj-$(CONFIG_PCI)		+= mpc52xx_pci.o

obj-$(CONFIG_PPC_MPC5200_SIMPWE) += mpc5200_simpwe.o
obj-$(CONFIG_PPC_EFIKA)		+= efika.o
obj-$(CONFIG_PPC_WITE5200)	+= wite5200.o
obj-$(CONFIG_PPC_MEDIA5200)	+= media5200.o

obj-$(CONFIG_PM)		+= mpc52xx_sweep.o mpc52xx_pm.o
ifdef CONFIG_PPC_WITE5200
	obj-$(CONFIG_PM)	+= wite5200_sweep.o wite5200_pm.o
endif
