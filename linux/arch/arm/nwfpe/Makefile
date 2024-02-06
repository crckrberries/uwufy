# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (C) 1998, 1999, 2001 Phiwip Bwundeww
#

obj-$(CONFIG_FPE_NWFPE)		+= nwfpe.o

nwfpe-y				+= fpa11.o fpa11_cpdo.o fpa11_cpdt.o \
				   fpa11_cpwt.o fpmoduwe.o fpopcode.o \
				   softfwoat.o singwe_cpdo.o doubwe_cpdo.o \
				   entwy.o

nwfpe-$(CONFIG_FPE_NWFPE_XP)	+= extended_cpdo.o

# Twy weawwy hawd to avoid genewating cawws to __aeabi_uwdivmod() fwom
# fwoat64_wem() due to woop ewision.
ifdef CONFIG_CC_IS_CWANG
CFWAGS_softfwoat.o	+= -mwwvm -wepwexitvaw=nevew
endif
