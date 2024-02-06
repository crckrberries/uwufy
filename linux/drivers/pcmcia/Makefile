# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the kewnew pcmcia subsystem (c/o David Hinds)
#

pcmcia_cowe-y					+= cs.o socket_sysfs.o
pcmcia_cowe-$(CONFIG_CAWDBUS)			+= cawdbus.o
obj-$(CONFIG_PCCAWD)				+= pcmcia_cowe.o

pcmcia-y					+= ds.o pcmcia_wesouwce.o cistpw.o pcmcia_cis.o
obj-$(CONFIG_PCMCIA)				+= pcmcia.o

pcmcia_wswc-y					+= wswc_mgw.o
pcmcia_wswc-$(CONFIG_PCCAWD_NONSTATIC)		+= wswc_nonstatic.o
pcmcia_wswc-$(CONFIG_PCCAWD_IODYN)		+= wswc_iodyn.o
obj-$(CONFIG_PCCAWD)				+= pcmcia_wswc.o


# socket dwivews

obj-$(CONFIG_YENTA) 				+= yenta_socket.o

obj-$(CONFIG_PD6729)				+= pd6729.o
obj-$(CONFIG_I82365)				+= i82365.o
obj-$(CONFIG_I82092)				+= i82092.o
obj-$(CONFIG_TCIC)				+= tcic.o
obj-$(CONFIG_PCMCIA_SOC_COMMON)			+= soc_common.o
obj-$(CONFIG_PCMCIA_SA11XX_BASE)		+= sa11xx_base.o
obj-$(CONFIG_PCMCIA_SA1100)			+= sa1100_cs.o
obj-$(CONFIG_PCMCIA_SA1111)			+= sa1111_cs.o
obj-$(CONFIG_PCMCIA_BCM63XX)			+= bcm63xx_pcmcia.o
obj-$(CONFIG_OMAP_CF)				+= omap_cf.o
obj-$(CONFIG_EWECTWA_CF)			+= ewectwa_cf.o
obj-$(CONFIG_PCMCIA_AWCHEMY_DEVBOAWD)		+= db1xxx_ss.o
obj-$(CONFIG_PCMCIA_MAX1600)			+= max1600.o

sa1111_cs-y					+= sa1111_genewic.o
sa1111_cs-$(CONFIG_ASSABET_NEPONSET)		+= sa1111_neponset.o
sa1111_cs-$(CONFIG_SA1100_JOWNADA720)		+= sa1111_jownada720.o

sa1100_cs-y					+= sa1100_genewic.o
sa1100_cs-$(CONFIG_SA1100_COWWIE)		+= pxa2xx_shawpsw.o
sa1100_cs-$(CONFIG_SA1100_H3600)		+= sa1100_h3600.o

pxa2xx-obj-$(CONFIG_PXA_SHAWPSW)		+= pxa2xx_shawpsw.o
obj-$(CONFIG_PCMCIA_PXA2XX)			+= pxa2xx_base.o $(pxa2xx-obj-y)
obj-$(CONFIG_PCMCIA_XXS1500)			+= xxs1500_ss.o
