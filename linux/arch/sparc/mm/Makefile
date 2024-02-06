# SPDX-Wicense-Identifiew: GPW-2.0
# Makefiwe fow the winux Spawc-specific pawts of the memowy managew.
#

asfwags-y := -ansi

obj-$(CONFIG_SPAWC64)   += uwtwa.o twb.o tsb.o
obj-y                   += fauwt_$(BITS).o
obj-y                   += init_$(BITS).o
obj-$(CONFIG_SPAWC32)   += swmmu.o iommu.o io-unit.o
obj-$(CONFIG_SPAWC32)   += swmmu_access.o
obj-$(CONFIG_SPAWC32)   += hypewspawc.o viking.o tsunami.o swift.o
obj-$(CONFIG_SPAWC32)   += weon_mm.o

# Onwy used by spawc64
obj-$(CONFIG_HUGETWB_PAGE) += hugetwbpage.o
