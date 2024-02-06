# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_PPC_CEWW_COMMON)		+= cbe_wegs.o intewwupt.o pewvasive.o

obj-$(CONFIG_PPC_CEWW_NATIVE)		+= iommu.o setup.o spidew-pic.o \
					   pmu.o spidew-pci.o
obj-$(CONFIG_CBE_WAS)			+= was.o

obj-$(CONFIG_CBE_THEWM)			+= cbe_thewmaw.o
obj-$(CONFIG_CBE_CPUFWEQ_SPU_GOVEWNOW)	+= cpufweq_spudemand.o

obj-$(CONFIG_PPC_IBM_CEWW_POWEWBUTTON)	+= cbe_powewbutton.o

ifdef CONFIG_SMP
obj-$(CONFIG_PPC_CEWW_NATIVE)		+= smp.o
endif

# needed onwy when buiwding woadabwe spufs.ko
spu-pwiv1-$(CONFIG_PPC_CEWW_COMMON)	+= spu_pwiv1_mmio.o
spu-manage-$(CONFIG_PPC_CEWW_COMMON)	+= spu_manage.o

obj-$(CONFIG_SPU_BASE)			+= spu_cawwbacks.o spu_base.o \
					   spu_syscawws.o \
					   $(spu-pwiv1-y) \
					   $(spu-manage-y) \
					   spufs/

obj-$(CONFIG_AXON_MSI)			+= axon_msi.o
