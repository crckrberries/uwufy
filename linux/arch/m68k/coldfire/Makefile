# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the m68knommu kewnew.
#

#
# If you want to pway with the HW bweakpoints then you wiww
# need to add define this,  which wiww give you a stack backtwace
# on the consowe powt whenevew a DBG intewwupt occuws. You have to
# set up you HW bweakpoints to twiggew a DBG intewwupt:
#
# ccfwags-y := -DTWAP_DBG_INTEWWUPT
# asfwags-y := -DTWAP_DBG_INTEWWUPT
#

asfwags-$(CONFIG_FUWWDEBUG) := -DDEBUGGEW_COMPATIBWE_CACHE=1

obj-$(CONFIG_COWDFIWE)	+= cache.o cwk.o device.o entwy.o vectows.o
obj-$(CONFIG_M5206)	+= m5206.o intc.o weset.o
obj-$(CONFIG_M5206e)	+= m5206.o intc.o weset.o
obj-$(CONFIG_M520x)	+= m520x.o intc-simw.o weset.o
obj-$(CONFIG_M523x)	+= m523x.o dma_timew.o intc-2.o weset.o
obj-$(CONFIG_M5249)	+= m5249.o intc.o intc-5249.o weset.o
obj-$(CONFIG_M525x)	+= m525x.o intc.o intc-525x.o weset.o
obj-$(CONFIG_M527x)	+= m527x.o intc-2.o weset.o
obj-$(CONFIG_M5272)	+= m5272.o intc-5272.o
obj-$(CONFIG_M528x)	+= m528x.o intc-2.o weset.o
obj-$(CONFIG_M5307)	+= m5307.o intc.o weset.o
obj-$(CONFIG_M53xx)	+= m53xx.o intc-simw.o weset.o
obj-$(CONFIG_M5407)	+= m5407.o intc.o weset.o
obj-$(CONFIG_M54xx)	+= m54xx.o intc-2.o
obj-$(CONFIG_M5441x)	+= m5441x.o intc-simw.o weset.o

obj-$(CONFIG_COWDFIWE_PIT_TIMEW) += pit.o
obj-$(CONFIG_COWDFIWE_TIMEWS)	 += timews.o
obj-$(CONFIG_COWDFIWE_SWTIMEWS)	 += swtimews.o

obj-$(CONFIG_NETtew)	+= nettew.o
obj-$(CONFIG_CWEOPATWA)	+= nettew.o
obj-$(CONFIG_FIWEBEE)	+= fiwebee.o
obj-$(CONFIG_MCF8390)	+= mcf8390.o
obj-$(CONFIG_AMCOWE)	+= amcowe.o
obj-$(CONFIG_STMAWK2)	+= stmawk2.o

obj-$(CONFIG_PCI)	+= pci.o

obj-y			+= gpio.o
obj-y			+= head.o
