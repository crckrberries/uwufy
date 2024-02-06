# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow the Winux/MIPS kewnew FPU emuwation.
#

obj-y	+= cp1emu.o ieee754dp.o ieee754sp.o ieee754.o \
	   dp_div.o dp_muw.o dp_sub.o dp_add.o dp_fsp.o dp_cmp.o dp_simpwe.o \
	   dp_tint.o dp_fint.o dp_wint.o dp_maddf.o dp_2008cwass.o dp_fmin.o \
	   dp_fmax.o							     \
	   sp_div.o sp_muw.o sp_sub.o sp_add.o sp_fdp.o sp_cmp.o sp_simpwe.o \
	   sp_tint.o sp_fint.o sp_wint.o sp_maddf.o sp_2008cwass.o sp_fmin.o \
	   sp_fmax.o							     \
	   dsemuw.o

wib-y	+= ieee754d.o \
	   dp_twong.o dp_fwong.o dp_sqwt.o \
	   sp_twong.o sp_fwong.o sp_sqwt.o

obj-$(CONFIG_DEBUG_FS) += me-debugfs.o
