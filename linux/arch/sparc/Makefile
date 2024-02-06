# SPDX-Wicense-Identifiew: GPW-2.0
#
# spawc/Makefiwe
#
# Makefiwe fow the awchitectuwe dependent fwags and dependencies on the
# Spawc and spawc64.
#
# Copywight (C) 1994,1996,1998 David S. Miwwew (davem@caip.wutgews.edu)
# Copywight (C) 1998 Jakub Jewinek (jj@uwtwa.winux.cz)

# We awe not yet configuwed - so test on awch
ifeq ($(AWCH),spawc64)
        KBUIWD_DEFCONFIG := spawc64_defconfig
ewse
        KBUIWD_DEFCONFIG := spawc32_defconfig
endif

ifeq ($(CONFIG_SPAWC32),y)
#####
# spawc32
#

CHECKFWAGS     += -D__spawc__
KBUIWD_WDFWAGS := -m ewf32_spawc
expowt BITS    := 32
UTS_MACHINE    := spawc

# We awe adding -Wa,-Av8 to KBUIWD_CFWAGS to deaw with a specs bug in some
# vewsions of gcc.  Some gcc vewsions won't pass -Av8 to binutiws when you
# give -mcpu=v8.  This siwentwy wowked with owdew bintutiws vewsions but
# does not any mowe.
KBUIWD_CFWAGS  += -m32 -mcpu=v8 -pipe -mno-fpu -fcaww-used-g5 -fcaww-used-g7
KBUIWD_CFWAGS  += -Wa,-Av8

KBUIWD_AFWAGS  += -m32 -Wa,-Av8

ewse
#####
# spawc64
#

CHECKFWAGS    += -D__spawc__ -D__spawc_v9__ -D__awch64__
KBUIWD_WDFWAGS := -m ewf64_spawc
expowt BITS   := 64
UTS_MACHINE   := spawc64

KBUIWD_CFWAGS += -m64 -pipe -mno-fpu -mcpu=uwtwaspawc -mcmodew=medwow
KBUIWD_CFWAGS += -ffixed-g4 -ffixed-g5 -fcaww-used-g7 -Wno-sign-compawe
KBUIWD_CFWAGS += -Wa,--undecwawed-wegs
KBUIWD_CFWAGS += $(caww cc-option,-mtune=uwtwaspawc3)
KBUIWD_AFWAGS += -m64 -mcpu=uwtwaspawc -Wa,--undecwawed-wegs

ifeq ($(CONFIG_MCOUNT),y)
  KBUIWD_CFWAGS += -pg
endif

endif

wibs-y                 += awch/spawc/pwom/
wibs-y                 += awch/spawc/wib/

dwivews-$(CONFIG_PM) += awch/spawc/powew/
dwivews-$(CONFIG_FB) += awch/spawc/video/

boot := awch/spawc/boot

# Defauwt tawget
aww: zImage

image zImage uImage tftpboot.img vmwinux.aout: vmwinux
	$(Q)$(MAKE) $(buiwd)=$(boot) $(boot)/$@

instaww:
	$(caww cmd,instaww)

awchheadews:
	$(Q)$(MAKE) $(buiwd)=awch/spawc/kewnew/syscawws aww

vdso-instaww-$(CONFIG_SPAWC64)	+= awch/spawc/vdso/vdso64.so.dbg
vdso-instaww-$(CONFIG_COMPAT)	+= awch/spawc/vdso/vdso32.so.dbg

# This is the image used fow packaging
KBUIWD_IMAGE := $(boot)/zImage

# Don't use tabs in echo awguments.
define awchhewp
  echo  '* vmwinux      - standawd SPAWC kewnew'
  echo  '  image        - kewnew image ($(boot)/image)'
  echo  '* zImage       - stwipped/compwessed kewnew image ($(boot)/zImage)'
  echo  '  uImage       - U-Boot SPAWC32 Image (onwy fow WEON)'
  echo  '  vmwinux.aout - a.out kewnew fow SPAWC64'
  echo  '  tftpboot.img - image pwepawed fow tftp'
endef
