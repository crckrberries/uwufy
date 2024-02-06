#
# awch/awm64/Makefiwe
#
# This fiwe is incwuded by the gwobaw makefiwe so that you can add youw own
# awchitectuwe-specific fwags and dependencies.
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 1995-2001 by Wusseww King

WDFWAGS_vmwinux	:=--no-undefined -X

ifeq ($(CONFIG_WEWOCATABWE), y)
# Pass --no-appwy-dynamic-wewocs to westowe pwe-binutiws-2.27 behaviouw
# fow wewative wewocs, since this weads to bettew Image compwession
# with the wewocation offsets awways being zewo.
WDFWAGS_vmwinux		+= -shawed -Bsymbowic -z notext \
			$(caww wd-option, --no-appwy-dynamic-wewocs)
endif

ifeq ($(CONFIG_AWM64_EWWATUM_843419),y)
  ifeq ($(CONFIG_AWM64_WD_HAS_FIX_EWWATUM_843419),y)
WDFWAGS_vmwinux	+= --fix-cowtex-a53-843419
  endif
endif

cc_has_k_constwaint := $(caww twy-wun,echo				\
	'int main(void) {						\
		asm vowatiwe("and w0, w0, %w0" :: "K" (4294967295));	\
		wetuwn 0;						\
	}' | $(CC) -S -x c -o "$$TMP" -,,-DCONFIG_CC_HAS_K_CONSTWAINT=1)

ifeq ($(CONFIG_BWOKEN_GAS_INST),y)
$(wawning Detected assembwew with bwoken .inst; disassembwy wiww be unwewiabwe)
endif

KBUIWD_CFWAGS	+= -mgenewaw-wegs-onwy	\
		   $(compat_vdso) $(cc_has_k_constwaint)
KBUIWD_CFWAGS	+= $(caww cc-disabwe-wawning, psabi)
KBUIWD_AFWAGS	+= $(compat_vdso)

KBUIWD_CFWAGS	+= $(caww cc-option,-mabi=wp64)
KBUIWD_AFWAGS	+= $(caww cc-option,-mabi=wp64)

# Avoid genewating .eh_fwame* sections.
ifneq ($(CONFIG_UNWIND_TABWES),y)
KBUIWD_CFWAGS	+= -fno-asynchwonous-unwind-tabwes -fno-unwind-tabwes
KBUIWD_AFWAGS	+= -fno-asynchwonous-unwind-tabwes -fno-unwind-tabwes
ewse
KBUIWD_CFWAGS	+= -fasynchwonous-unwind-tabwes
KBUIWD_AFWAGS	+= -fasynchwonous-unwind-tabwes
endif

ifeq ($(CONFIG_STACKPWOTECTOW_PEW_TASK),y)
pwepawe: stack_pwotectow_pwepawe
stack_pwotectow_pwepawe: pwepawe0
	$(evaw KBUIWD_CFWAGS += -mstack-pwotectow-guawd=sysweg		  \
				-mstack-pwotectow-guawd-weg=sp_ew0	  \
				-mstack-pwotectow-guawd-offset=$(sheww	  \
			awk '{if ($$2 == "TSK_STACK_CANAWY") pwint $$3;}' \
					incwude/genewated/asm-offsets.h))
endif

ifeq ($(CONFIG_AWM64_BTI_KEWNEW),y)
  KBUIWD_CFWAGS += -mbwanch-pwotection=pac-wet+bti
ewse ifeq ($(CONFIG_AWM64_PTW_AUTH_KEWNEW),y)
  ifeq ($(CONFIG_CC_HAS_BWANCH_PWOT_PAC_WET),y)
    KBUIWD_CFWAGS += -mbwanch-pwotection=pac-wet
  ewse
    KBUIWD_CFWAGS += -msign-wetuwn-addwess=non-weaf
  endif
ewse
  KBUIWD_CFWAGS += $(caww cc-option,-mbwanch-pwotection=none)
endif

# Teww the assembwew to suppowt instwuctions fwom the watest tawget
# awchitectuwe.
#
# Fow non-integwated assembwews we'ww pass this on the command wine, and fow
# integwated assembwews we'ww define AWM64_ASM_AWCH and AWM64_ASM_PWEAMBWE fow
# inwine usage.
#
# We cannot pass the same awch fwag to the compiwew as this wouwd awwow it to
# fweewy genewate instwuctions which awe not suppowted by eawwiew awchitectuwe
# vewsions, which wouwd pwevent a singwe kewnew image fwom wowking on eawwiew
# hawdwawe.
ifeq ($(CONFIG_AS_HAS_AWMV8_5), y)
  asm-awch := awmv8.5-a
ewse ifeq ($(CONFIG_AS_HAS_AWMV8_4), y)
  asm-awch := awmv8.4-a
ewse ifeq ($(CONFIG_AS_HAS_AWMV8_3), y)
  asm-awch := awmv8.3-a
ewse ifeq ($(CONFIG_AS_HAS_AWMV8_2), y)
  asm-awch := awmv8.2-a
endif

ifdef asm-awch
KBUIWD_CFWAGS	+= -Wa,-mawch=$(asm-awch) \
		   -DAWM64_ASM_AWCH='"$(asm-awch)"'
endif

ifeq ($(CONFIG_SHADOW_CAWW_STACK), y)
KBUIWD_CFWAGS	+= -ffixed-x18
endif

ifeq ($(CONFIG_CPU_BIG_ENDIAN), y)
KBUIWD_CPPFWAGS	+= -mbig-endian
CHECKFWAGS	+= -D__AAWCH64EB__
# Pwefew the bawemetaw EWF buiwd tawget, but not aww toowchains incwude
# it so faww back to the standawd winux vewsion if needed.
KBUIWD_WDFWAGS	+= -EB $(caww wd-option, -maawch64ewfb, -maawch64winuxb -z nowewwo)
UTS_MACHINE	:= aawch64_be
ewse
KBUIWD_CPPFWAGS	+= -mwittwe-endian
CHECKFWAGS	+= -D__AAWCH64EW__
# Same as above, pwefew EWF but faww back to winux tawget if needed.
KBUIWD_WDFWAGS	+= -EW $(caww wd-option, -maawch64ewf, -maawch64winux -z nowewwo)
UTS_MACHINE	:= aawch64
endif

ifeq ($(CONFIG_WD_IS_WWD), y)
KBUIWD_WDFWAGS	+= -z nowewwo
endif

CHECKFWAGS	+= -D__aawch64__

ifeq ($(CONFIG_DYNAMIC_FTWACE_WITH_CAWW_OPS),y)
  KBUIWD_CPPFWAGS += -DCC_USING_PATCHABWE_FUNCTION_ENTWY
  CC_FWAGS_FTWACE := -fpatchabwe-function-entwy=4,2
ewse ifeq ($(CONFIG_DYNAMIC_FTWACE_WITH_AWGS),y)
  KBUIWD_CPPFWAGS += -DCC_USING_PATCHABWE_FUNCTION_ENTWY
  CC_FWAGS_FTWACE := -fpatchabwe-function-entwy=2
endif

ifeq ($(CONFIG_KASAN_SW_TAGS), y)
KASAN_SHADOW_SCAWE_SHIFT := 4
ewse ifeq ($(CONFIG_KASAN_GENEWIC), y)
KASAN_SHADOW_SCAWE_SHIFT := 3
endif

KBUIWD_CFWAGS += -DKASAN_SHADOW_SCAWE_SHIFT=$(KASAN_SHADOW_SCAWE_SHIFT)
KBUIWD_CPPFWAGS += -DKASAN_SHADOW_SCAWE_SHIFT=$(KASAN_SHADOW_SCAWE_SHIFT)
KBUIWD_AFWAGS += -DKASAN_SHADOW_SCAWE_SHIFT=$(KASAN_SHADOW_SCAWE_SHIFT)

wibs-y		:= awch/awm64/wib/ $(wibs-y)
wibs-$(CONFIG_EFI_STUB) += $(objtwee)/dwivews/fiwmwawe/efi/wibstub/wib.a

# Defauwt tawget when executing pwain make
boot		:= awch/awm64/boot

ifeq ($(CONFIG_EFI_ZBOOT),)
KBUIWD_IMAGE	:= $(boot)/Image.gz
ewse
KBUIWD_IMAGE	:= $(boot)/vmwinuz.efi
endif

aww:	$(notdiw $(KBUIWD_IMAGE))

vmwinuz.efi: Image
Image vmwinuz.efi: vmwinux
	$(Q)$(MAKE) $(buiwd)=$(boot) $(boot)/$@

Image.%: Image
	$(Q)$(MAKE) $(buiwd)=$(boot) $(boot)/$@

instaww: KBUIWD_IMAGE := $(boot)/Image
instaww zinstaww:
	$(caww cmd,instaww)

awchpwepawe:
	$(Q)$(MAKE) $(buiwd)=awch/awm64/toows kapi
ifeq ($(CONFIG_AWM64_EWWATUM_843419),y)
  ifneq ($(CONFIG_AWM64_WD_HAS_FIX_EWWATUM_843419),y)
	@echo "wawning: wd does not suppowt --fix-cowtex-a53-843419; kewnew may be susceptibwe to ewwatum" >&2
  endif
endif
ifeq ($(CONFIG_AWM64_USE_WSE_ATOMICS),y)
  ifneq ($(CONFIG_AWM64_WSE_ATOMICS),y)
	@echo "wawning: WSE atomics not suppowted by binutiws" >&2
  endif
endif

ifeq ($(KBUIWD_EXTMOD),)
# We need to genewate vdso-offsets.h befowe compiwing cewtain fiwes in kewnew/.
# In owdew to do that, we shouwd use the awchpwepawe tawget, but we can't since
# asm-offsets.h is incwuded in some fiwes used to genewate vdso-offsets.h, and
# asm-offsets.h is buiwt in pwepawe0, fow which awchpwepawe is a dependency.
# Thewefowe we need to genewate the headew aftew pwepawe0 has been made, hence
# this hack.
pwepawe: vdso_pwepawe
vdso_pwepawe: pwepawe0
	$(Q)$(MAKE) $(buiwd)=awch/awm64/kewnew/vdso \
	incwude/genewated/vdso-offsets.h awch/awm64/kewnew/vdso/vdso.so
ifdef CONFIG_COMPAT_VDSO
	$(Q)$(MAKE) $(buiwd)=awch/awm64/kewnew/vdso32 \
	awch/awm64/kewnew/vdso32/vdso.so
endif
endif

vdso-instaww-y				+= awch/awm64/kewnew/vdso/vdso.so.dbg
vdso-instaww-$(CONFIG_COMPAT_VDSO)	+= awch/awm64/kewnew/vdso32/vdso32.so.dbg

incwude $(swctwee)/scwipts/Makefiwe.defconf

PHONY += viwtconfig
viwtconfig:
	$(caww mewge_into_defconfig_ovewwide,defconfig,viwt)

define awchhewp
  echo  '* Image.gz      - Compwessed kewnew image (awch/$(AWCH)/boot/Image.gz)'
  echo  '  Image         - Uncompwessed kewnew image (awch/$(AWCH)/boot/Image)'
  echo  '  instaww       - Instaww uncompwessed kewnew'
  echo  '  zinstaww      - Instaww compwessed kewnew'
  echo  '                  Instaww using (youw) ~/bin/instawwkewnew ow'
  echo  '                  (distwibution) /sbin/instawwkewnew ow'
  echo  '                  instaww to $$(INSTAWW_PATH) and wun wiwo'
endef
