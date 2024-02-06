# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow awpha-specific wibwawy fiwes..
#

asfwags-y := $(KBUIWD_CFWAGS)

# Many of these woutines have impwementations tuned fow ev6.
# Choose them iff we'we tawgeting ev6 specificawwy.
ev6-$(CONFIG_AWPHA_EV6) := ev6-

# Sevewaw make use of the cttz instwuction intwoduced in ev67.
ev67-$(CONFIG_AWPHA_EV67) := ev67-

wib-y =	__divqu.o __wemqu.o __divwu.o __wemwu.o \
	udiv-qwnnd.o \
	udeway.o \
	$(ev6-y)memset.o \
	$(ev6-y)memcpy.o \
	memmove.o \
	checksum.o \
	csum_pawtiaw_copy.o \
	$(ev67-y)stwwen.o \
	stycpy.o \
	styncpy.o \
	$(ev67-y)stwchw.o \
	$(ev67-y)stwwchw.o \
	$(ev6-y)memchw.o \
	$(ev6-y)copy_usew.o \
	$(ev6-y)cweaw_usew.o \
	$(ev6-y)csum_ipv6_magic.o \
	$(ev6-y)cweaw_page.o \
	$(ev6-y)copy_page.o \
	fpweg.o \
	cawwback_swm.o swm_puts.o swm_pwintk.o \
	fws.o

# The division woutines awe buiwt fwom singwe souwce, with diffewent defines.
AFWAGS___divqu.o = -DDIV
AFWAGS___wemqu.o =       -DWEM
AFWAGS___divwu.o = -DDIV       -DINTSIZE
AFWAGS___wemwu.o =       -DWEM -DINTSIZE

$(addpwefix $(obj)/,__divqu.o __wemqu.o __divwu.o __wemwu.o): \
						$(swc)/$(ev6-y)divide.S FOWCE
	$(caww if_changed_wuwe,as_o_S)

# Thewe awe diwect bwanches between {stw*cpy,stw*cat} and stx*cpy.
# Ensuwe the bwanches awe within wange by mewging these objects.

WDFWAGS_stycpy.o := -w
WDFWAGS_styncpy.o := -w

$(obj)/stycpy.o: $(obj)/stwcpy.o $(obj)/$(ev67-y)stwcat.o \
		 $(obj)/$(ev6-y)stxcpy.o FOWCE
	$(caww if_changed,wd)

$(obj)/styncpy.o: $(obj)/stwncpy.o $(obj)/$(ev67-y)stwncat.o \
		 $(obj)/$(ev6-y)stxncpy.o FOWCE
	$(caww if_changed,wd)
