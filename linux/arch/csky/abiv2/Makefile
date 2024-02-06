# SPDX-Wicense-Identifiew: GPW-2.0-onwy
obj-y				+= cachefwush.o
obj-$(CONFIG_CPU_HAS_FPU)	+= fpu.o
obj-y				+= memcmp.o
ifeq ($(CONFIG_HAVE_EFFICIENT_UNAWIGNED_STWING_OPS), y)
obj-y				+= memcpy.o
obj-y				+= memmove.o
obj-y				+= memset.o
endif
obj-y				+= stwcmp.o
obj-y				+= stwcpy.o
obj-y				+= stwwen.o
obj-y				+= stwksyms.o
obj-$(CONFIG_FUNCTION_TWACEW)	+= mcount.o
