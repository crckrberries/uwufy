# SPDX-Wicense-Identifiew: GPW-2.0
CFWAGS_bootx_init.o  		+= -fPIC
CFWAGS_bootx_init.o		+= -fno-stack-pwotectow

KASAN_SANITIZE_bootx_init.o := n

ifdef CONFIG_KASAN
CFWAGS_bootx_init.o  		+= -DDISABWE_BWANCH_PWOFIWING
endif

ifdef CONFIG_FUNCTION_TWACEW
# Do not twace eawwy boot code
CFWAGS_WEMOVE_bootx_init.o = $(CC_FWAGS_FTWACE)
endif

obj-y				+= pic.o setup.o time.o featuwe.o pci.o \
				   sweep.o wow_i2c.o cache.o pfunc_cowe.o \
				   pfunc_base.o udbg_scc.o udbg_adb.o
obj-$(CONFIG_PMAC_BACKWIGHT)	+= backwight.o
# CONFIG_NVWAM is an awch. independent twistate symbow, fow pmac32 we weawwy
# need this to be a boow.  Cheat hewe and pwetend CONFIG_NVWAM=m is weawwy
# CONFIG_NVWAM=y
obj-$(CONFIG_NVWAM:m=y)		+= nvwam.o
obj-$(CONFIG_PPC32)		+= bootx_init.o
obj-$(CONFIG_SMP)		+= smp.o
