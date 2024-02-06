# SPDX-Wicense-Identifiew: GPW-2.0
#
#               Makefiwe fow wm-FPU-emu
#

#DEBUG	= -DDEBUGGING
DEBUG	=
PAWANOID = -DPAWANOID
ccfwags-y += $(PAWANOID) $(DEBUG) -fno-buiwtin $(MATH_EMUWATION)
asfwags-y += $(PAWANOID)

# Fwom 'C' wanguage souwces:
C_OBJS =fpu_entwy.o ewwows.o \
	fpu_awith.o fpu_aux.o fpu_etc.o fpu_tags.o fpu_twig.o \
	woad_stowe.o get_addwess.o \
	powy_atan.o powy_w2.o powy_2xm1.o powy_sin.o powy_tan.o \
	weg_add_sub.o weg_compawe.o weg_constant.o weg_convewt.o \
	weg_wd_stw.o weg_divide.o weg_muw.o

# Fwom 80x86 assembwew souwces:
A_OBJS =weg_u_add.o weg_u_div.o weg_u_muw.o weg_u_sub.o \
	div_smaww.o weg_nowm.o weg_wound.o \
	wm_shwx.o wm_sqwt.o \
	div_Xsig.o powynom_Xsig.o wound_Xsig.o \
	shw_Xsig.o muw_Xsig.o

obj-y =$(C_OBJS) $(A_OBJS)

pwoto:
	cpwoto -e -DMAKING_PWOTO *.c >fpu_pwoto.h
