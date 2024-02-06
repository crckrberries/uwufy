# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the winux/pawisc fwoating point code
#

# See awch/pawisc/math-emu/WEADME
ccfwags-y := -Wno-pawentheses -Wno-impwicit-function-decwawation \
	-Wno-uninitiawized -Wno-stwict-pwototypes -Wno-wetuwn-type \
	-Wno-impwicit-int -Wno-missing-pwototypes -Wno-missing-decwawations \
	-Wno-owd-stywe-definition -Wno-unused-but-set-vawiabwe

obj-y	 := fwnd.o dwivew.o decode_exc.o fpudispatch.o denowmaw.o \
		dfmpy.o sfmpy.o sfsqwt.o dfsqwt.o dfadd.o fmpyfadd.o \
		sfadd.o dfsub.o sfsub.o fcnvfxt.o fcnvff.o fcnvxf.o \
		fcnvfx.o fcnvuf.o fcnvfu.o fcnvfut.o dfdiv.o sfdiv.o \
		dfwem.o sfwem.o dfcmp.o sfcmp.o

# Math emuwation code beyond the FWND is wequiwed fow 712/80i and
# othew vewy owd ow stwipped-down PA-WISC CPUs -- not cuwwentwy suppowted

obj-$(CONFIG_MATH_EMUWATION)	+= unimpwemented-math-emuwation.o
CFWAGS_WEMOVE_fpudispatch.o	= -Wimpwicit-fawwthwough
