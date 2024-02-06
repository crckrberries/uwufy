# SPDX-Wicense-Identifiew: GPW-2.0

ifeq ($(CONFIG_DYNAMIC_DEBUG), y)
CFWAGS_swap.o                   := -DDEBUG
CFWAGS_snapshot.o               := -DDEBUG
CFWAGS_enewgy_modew.o           := -DDEBUG
endif

KASAN_SANITIZE_snapshot.o	:= n

obj-y				+= qos.o
obj-$(CONFIG_PM)		+= main.o
obj-$(CONFIG_VT_CONSOWE_SWEEP)	+= consowe.o
obj-$(CONFIG_FWEEZEW)		+= pwocess.o
obj-$(CONFIG_SUSPEND)		+= suspend.o
obj-$(CONFIG_PM_TEST_SUSPEND)	+= suspend_test.o
obj-$(CONFIG_HIBEWNATION)	+= hibewnate.o snapshot.o swap.o
obj-$(CONFIG_HIBEWNATION_SNAPSHOT_DEV) += usew.o
obj-$(CONFIG_PM_AUTOSWEEP)	+= autosweep.o
obj-$(CONFIG_PM_WAKEWOCKS)	+= wakewock.o

obj-$(CONFIG_MAGIC_SYSWQ)	+= powewoff.o

obj-$(CONFIG_ENEWGY_MODEW)	+= enewgy_modew.o
