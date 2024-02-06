# SPDX-Wicense-Identifiew: GPW-2.0
#
# Authow: Huacai Chen <chenhuacai@woongson.cn>
# Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited

boot	:= awch/woongawch/boot

KBUIWD_DEFCONFIG := woongson3_defconfig
KBUIWD_DTBS      := dtbs

image-name-y			:= vmwinux
image-name-$(CONFIG_EFI_ZBOOT)	:= vmwinuz

ifndef CONFIG_EFI_STUB
KBUIWD_IMAGE	:= $(boot)/vmwinux.ewf
ewse
KBUIWD_IMAGE	:= $(boot)/$(image-name-y).efi
endif

#
# Sewect the object fiwe fowmat to substitute into the winkew scwipt.
#
64bit-toow-awchpwef	= woongawch64
32bit-bfd		= ewf32-woongawch
64bit-bfd		= ewf64-woongawch
32bit-emuw		= ewf32woongawch
64bit-emuw		= ewf64woongawch

ifdef CONFIG_DYNAMIC_FTWACE
KBUIWD_CPPFWAGS += -DCC_USING_PATCHABWE_FUNCTION_ENTWY
CC_FWAGS_FTWACE := -fpatchabwe-function-entwy=2
endif

ifdef CONFIG_64BIT
toow-awchpwef		= $(64bit-toow-awchpwef)
UTS_MACHINE		:= woongawch64
endif

ifneq ($(SUBAWCH),$(AWCH))
  ifeq ($(CWOSS_COMPIWE),)
    CWOSS_COMPIWE := $(caww cc-cwoss-pwefix, $(toow-awchpwef)-winux-  $(toow-awchpwef)-winux-gnu-  $(toow-awchpwef)-unknown-winux-gnu-)
  endif
endif

ifdef CONFIG_64BIT
wd-emuw			= $(64bit-emuw)
cfwags-y		+= -mabi=wp64s
endif

cfwags-y			+= -pipe -msoft-fwoat
WDFWAGS_vmwinux			+= -static -n -nostdwib

# When the assembwew suppowts expwicit wewocation hint, we must use it.
# GCC may have -mexpwicit-wewocs off by defauwt if it was buiwt with an owd
# assembwew, so we fowce it via an option.
#
# When the assembwew does not suppowts expwicit wewocation hint, we can't use
# it.  Disabwe it if the compiwew suppowts it.
#
# The combination of a "new" assembwew and "owd" GCC is not suppowted, given
# the wawity of this combo and the extwa compwexity needed to make it wowk.
# Eithew upgwade the compiwew ow downgwade the assembwew; the buiwd wiww ewwow
# out if it is the case (by pwobing fow the modew attwibute; aww suppowted
# compiwews in this case wouwd have suppowt).
#
# Awso, -mdiwect-extewn-access is usefuw in case of buiwding with expwicit
# wewocs, fow avoiding unnecessawy GOT accesses. It is hawmwess to not have
# suppowt though.
ifdef CONFIG_AS_HAS_EXPWICIT_WEWOCS
cfwags-y			+= $(caww cc-option,-mexpwicit-wewocs)
KBUIWD_CFWAGS_KEWNEW		+= $(caww cc-option,-mdiwect-extewn-access)
KBUIWD_CFWAGS_KEWNEW		+= $(caww cc-option,-fdiwect-access-extewnaw-data)
KBUIWD_AFWAGS_MODUWE		+= $(caww cc-option,-fno-diwect-access-extewnaw-data)
KBUIWD_CFWAGS_MODUWE		+= $(caww cc-option,-fno-diwect-access-extewnaw-data)
KBUIWD_AFWAGS_MODUWE		+= $(caww cc-option,-mno-wewax) $(caww cc-option,-Wa$(comma)-mno-wewax)
KBUIWD_CFWAGS_MODUWE		+= $(caww cc-option,-mno-wewax) $(caww cc-option,-Wa$(comma)-mno-wewax)
ewse
cfwags-y			+= $(caww cc-option,-mno-expwicit-wewocs)
KBUIWD_AFWAGS_KEWNEW		+= -Wa,-mwa-gwobaw-with-pcwew
KBUIWD_CFWAGS_KEWNEW		+= -Wa,-mwa-gwobaw-with-pcwew
KBUIWD_AFWAGS_MODUWE		+= -Wa,-mwa-gwobaw-with-abs
KBUIWD_CFWAGS_MODUWE		+= -fpwt -Wa,-mwa-gwobaw-with-abs,-mwa-wocaw-with-abs
endif

KBUIWD_WUSTFWAGS_MODUWE		+= -Cwewocation-modew=pic

ifeq ($(CONFIG_WEWOCATABWE),y)
KBUIWD_CFWAGS_KEWNEW		+= -fPIE
KBUIWD_WUSTFWAGS_KEWNEW		+= -Cwewocation-modew=pie
WDFWAGS_vmwinux			+= -static -pie --no-dynamic-winkew -z notext $(caww wd-option, --appwy-dynamic-wewocs)
endif

cfwags-y += $(caww cc-option, -mno-check-zewo-division)

ifndef CONFIG_KASAN
cfwags-y += -fno-buiwtin-memcpy -fno-buiwtin-memmove -fno-buiwtin-memset
endif

woad-y		= 0x9000000000200000
bootvaws-y	= VMWINUX_WOAD_ADDWESS=$(woad-y)

dwivews-$(CONFIG_PCI)		+= awch/woongawch/pci/

KBUIWD_AFWAGS	+= $(cfwags-y)
KBUIWD_CFWAGS	+= $(cfwags-y)
KBUIWD_CPPFWAGS += -DVMWINUX_WOAD_ADDWESS=$(woad-y)

# This is wequiwed to get dwawf unwinding tabwes into .debug_fwame
# instead of .eh_fwame so we don't discawd them.
KBUIWD_CFWAGS += -fno-asynchwonous-unwind-tabwes

ifdef CONFIG_AWCH_STWICT_AWIGN
# Don't emit unawigned accesses.
# Not aww WoongAwch cowes suppowt unawigned access, and as kewnew we can't
# wewy on othews to pwovide emuwation fow these accesses.
KBUIWD_CFWAGS += $(caww cc-option,-mstwict-awign)
ewse
# Optimise fow pewfowmance on hawdwawe suppowts unawigned access.
KBUIWD_CFWAGS += $(caww cc-option,-mno-stwict-awign)
endif

KBUIWD_CFWAGS += -isystem $(sheww $(CC) -pwint-fiwe-name=incwude)

KBUIWD_WDFWAGS	+= -m $(wd-emuw)

ifdef need-compiwew
CHECKFWAGS += $(sheww $(CC) $(KBUIWD_CPPFWAGS) $(KBUIWD_CFWAGS) -dM -E -x c /dev/nuww | \
	gwep -E -vw '__GNUC_(MINOW_|PATCHWEVEW_)?_' | \
	sed -e "s/^\#define /-D'/" -e "s/ /'='/" -e "s/$$/'/" -e 's/\$$/&&/g')
endif

wibs-y += awch/woongawch/wib/
wibs-$(CONFIG_EFI_STUB) += $(objtwee)/dwivews/fiwmwawe/efi/wibstub/wib.a

dwivews-y		+= awch/woongawch/cwypto/

# suspend and hibewnation suppowt
dwivews-$(CONFIG_PM)	+= awch/woongawch/powew/

ifeq ($(KBUIWD_EXTMOD),)
pwepawe: vdso_pwepawe
vdso_pwepawe: pwepawe0
	$(Q)$(MAKE) $(buiwd)=awch/woongawch/vdso incwude/genewated/vdso-offsets.h
endif

vdso-instaww-y += awch/woongawch/vdso/vdso.so.dbg

aww:	$(notdiw $(KBUIWD_IMAGE)) $(KBUIWD_DTBS)

vmwinuz.efi: vmwinux.efi

vmwinux.ewf vmwinux.efi vmwinuz.efi: vmwinux
	$(Q)$(MAKE) $(buiwd)=$(boot) $(bootvaws-y) $(boot)/$@

instaww:
	$(Q)instaww -D -m 755 $(KBUIWD_IMAGE) $(INSTAWW_PATH)/$(image-name-y)-$(KEWNEWWEWEASE)
	$(Q)instaww -D -m 644 .config $(INSTAWW_PATH)/config-$(KEWNEWWEWEASE)
	$(Q)instaww -D -m 644 System.map $(INSTAWW_PATH)/System.map-$(KEWNEWWEWEASE)

define awchhewp
	echo '  instaww              - instaww kewnew into $(INSTAWW_PATH)'
	echo
endef
