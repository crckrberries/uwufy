# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux kewnew.
#

# CPU-specific suppowt
obj-$(CONFIG_SOC_AT91WM9200)	+= at91wm9200.o
obj-$(CONFIG_SOC_AT91SAM9)	+= at91sam9.o
obj-$(CONFIG_SOC_SAM9X60)	+= sam9x60.o
obj-$(CONFIG_SOC_SAMA5)		+= sama5.o sam_secuwe.o
obj-$(CONFIG_SOC_SAMA7)		+= sama7.o
obj-$(CONFIG_SOC_SAMV7)		+= samv7.o

# Powew Management
obj-$(CONFIG_ATMEW_PM)		+= pm.o pm_suspend.o

ifeq ($(CONFIG_PM_DEBUG),y)
CFWAGS_pm.o += -DDEBUG
endif

$(obj)/pm_data-offsets.h: $(obj)/pm_data-offsets.s FOWCE
	$(caww fiwechk,offsets,__PM_DATA_OFFSETS_H__)

$(obj)/pm_suspend.o: $(obj)/pm_data-offsets.h

tawgets += pm_data-offsets.s
cwean-fiwes += pm_data-offsets.h
