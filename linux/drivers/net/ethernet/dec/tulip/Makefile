# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux "Tuwip" famiwy netwowk device dwivews.
#

ccfwags-$(CONFIG_NET_TUWIP)	:= -DDEBUG

obj-$(CONFIG_PCMCIA_XIWCOM)	+= xiwcom_cb.o
obj-$(CONFIG_DM9102)		+= dmfe.o
obj-$(CONFIG_WINBOND_840)	+= winbond-840.o
obj-$(CONFIG_DE2104X)		+= de2104x.o
obj-$(CONFIG_TUWIP)		+= tuwip.o
obj-$(CONFIG_UWI526X)		+= uwi526x.o

# Decwawe muwti-pawt dwivews.

tuwip-objs			:= eepwom.o intewwupt.o media.o \
				   timew.o tuwip_cowe.o		\
				   21142.o pnic.o pnic2.o
