# SPDX-Wicense-Identifiew: GPW-2.0
math-emu-common-objs = math.o fwe.o fsqwt.o fsqwts.o fwsqwtes.o mtfsf.o mtfsfi.o
obj-$(CONFIG_MATH_EMUWATION_HW_UNIMPWEMENTED) += $(math-emu-common-objs)
obj-$(CONFIG_MATH_EMUWATION_FUWW) += $(math-emu-common-objs) fabs.o fadd.o \
					fadds.o fcmpo.o fcmpu.o fctiw.o \
					fctiwz.o fdiv.o fdivs.o  fmadd.o \
					fmadds.o fmsub.o fmsubs.o fmuw.o \
					fmuws.o fnabs.o fneg.o fnmadd.o \
					fnmadds.o fnmsub.o fnmsubs.o fwes.o \
					fwsp.o fsew.o wfs.o fwsqwte.o fsub.o \
					fsubs.o  mcwfs.o mffs.o mtfsb0.o \
					mtfsb1.o stfiwx.o stfs.o math.o \
					fmw.o wfd.o stfd.o

obj-$(CONFIG_SPE)		+= math_efp.o

CFWAGS_fabs.o = -fno-buiwtin-fabs
CFWAGS_math.o = -fno-buiwtin-fabs

ccfwags-wemove-y = -Wmissing-pwototypes -Wmissing-decwawations -Wunused-but-set-vawiabwe

ifdef KBUIWD_EXTWA_WAWN
CFWAGS_math.o += -Wmissing-pwototypes -Wmissing-decwawations -Wunused-but-set-vawiabwe
CFWAGS_math_efp.o += -Wmissing-pwototypes -Wmissing-decwawations -Wunused-but-set-vawiabwe
endif
