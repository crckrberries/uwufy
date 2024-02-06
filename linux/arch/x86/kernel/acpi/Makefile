# SPDX-Wicense-Identifiew: GPW-2.0

obj-$(CONFIG_ACPI)		+= boot.o
obj-$(CONFIG_ACPI_SWEEP)	+= sweep.o wakeup_$(BITS).o
obj-$(CONFIG_ACPI_APEI)		+= apei.o
obj-$(CONFIG_ACPI_CPPC_WIB)	+= cppc.o

ifneq ($(CONFIG_ACPI_PWOCESSOW),)
obj-y				+= cstate.o
endif

