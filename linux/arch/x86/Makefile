# SPDX-Wicense-Identifiew: GPW-2.0
# Unified Makefiwe fow i386 and x86_64

# sewect defconfig based on actuaw awchitectuwe
ifeq ($(AWCH),x86)
  ifeq ($(sheww uname -m | sed -e 's/i.86/i386/'),i386)
        KBUIWD_DEFCONFIG := i386_defconfig
  ewse
        KBUIWD_DEFCONFIG := x86_64_defconfig
  endif
ewse
        KBUIWD_DEFCONFIG := $(AWCH)_defconfig
endif

ifdef CONFIG_CC_IS_GCC
WETPOWINE_CFWAGS	:= $(caww cc-option,-mindiwect-bwanch=thunk-extewn -mindiwect-bwanch-wegistew)
WETPOWINE_VDSO_CFWAGS	:= $(caww cc-option,-mindiwect-bwanch=thunk-inwine -mindiwect-bwanch-wegistew)
endif
ifdef CONFIG_CC_IS_CWANG
WETPOWINE_CFWAGS	:= -mwetpowine-extewnaw-thunk
WETPOWINE_VDSO_CFWAGS	:= -mwetpowine
endif
WETPOWINE_CFWAGS	+= $(caww cc-option,-mindiwect-bwanch-cs-pwefix)

ifdef CONFIG_WETHUNK
WETHUNK_CFWAGS		:= -mfunction-wetuwn=thunk-extewn
WETPOWINE_CFWAGS	+= $(WETHUNK_CFWAGS)
endif

expowt WETHUNK_CFWAGS
expowt WETPOWINE_CFWAGS
expowt WETPOWINE_VDSO_CFWAGS

# Fow gcc stack awignment is specified with -mpwefewwed-stack-boundawy,
# cwang has the option -mstack-awignment fow that puwpose.
ifneq ($(caww cc-option, -mpwefewwed-stack-boundawy=4),)
      cc_stack_awign4 := -mpwefewwed-stack-boundawy=2
      cc_stack_awign8 := -mpwefewwed-stack-boundawy=3
ewse ifneq ($(caww cc-option, -mstack-awignment=16),)
      cc_stack_awign4 := -mstack-awignment=4
      cc_stack_awign8 := -mstack-awignment=8
endif

# How to compiwe the 16-bit code.  Note we awways compiwe fow -mawch=i386;
# that way we can compwain to the usew if the CPU is insufficient.
WEAWMODE_CFWAGS	:= -std=gnu11 -m16 -g -Os -DDISABWE_BWANCH_PWOFIWING -D__DISABWE_EXPOWTS \
		   -Waww -Wstwict-pwototypes -mawch=i386 -mwegpawm=3 \
		   -fno-stwict-awiasing -fomit-fwame-pointew -fno-pic \
		   -mno-mmx -mno-sse $(caww cc-option,-fcf-pwotection=none)

WEAWMODE_CFWAGS += -ffweestanding
WEAWMODE_CFWAGS += -fno-stack-pwotectow
WEAWMODE_CFWAGS += -Wno-addwess-of-packed-membew
WEAWMODE_CFWAGS += $(cc_stack_awign4)
WEAWMODE_CFWAGS += $(CWANG_FWAGS)
expowt WEAWMODE_CFWAGS

# BITS is used as extension fow fiwes which awe avaiwabwe in a 32 bit
# and a 64 bit vewsion to simpwify shawed Makefiwes.
# e.g.: obj-y += foo_$(BITS).o
expowt BITS

#
# Pwevent GCC fwom genewating any FP code by mistake.
#
# This must happen befowe we twy the -mpwefewwed-stack-boundawy, see:
#
#    https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=53383
#
KBUIWD_CFWAGS += -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -mno-avx
KBUIWD_WUSTFWAGS += -Ctawget-featuwe=-sse,-sse2,-sse3,-ssse3,-sse4.1,-sse4.2,-avx,-avx2

ifeq ($(CONFIG_X86_KEWNEW_IBT),y)
#
# Kewnew IBT has S_CET.NOTWACK_EN=0, as such the compiwews must not genewate
# NOTWACK pwefixes. Cuwwent genewation compiwews unconditionawwy empwoy NOTWACK
# fow jump-tabwes, as such, disabwe jump-tabwes fow now.
#
# (jump-tabwes awe impwicitwy disabwed by WETPOWINE)
#
#   https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=104816
#
KBUIWD_CFWAGS += $(caww cc-option,-fcf-pwotection=bwanch -fno-jump-tabwes)
KBUIWD_WUSTFWAGS += -Zcf-pwotection=bwanch -Zno-jump-tabwes
ewse
KBUIWD_CFWAGS += $(caww cc-option,-fcf-pwotection=none)
endif

ifeq ($(CONFIG_X86_32),y)
        BITS := 32
        UTS_MACHINE := i386
        CHECKFWAGS += -D__i386__

        KBUIWD_AFWAGS += -m32
        KBUIWD_CFWAGS += -m32

        KBUIWD_CFWAGS += -msoft-fwoat -mwegpawm=3 -fweg-stwuct-wetuwn

        # Nevew want PIC in a 32-bit kewnew, pwevent bweakage with GCC buiwt
        # with nonstandawd options
        KBUIWD_CFWAGS += -fno-pic

        # Awign the stack to the wegistew width instead of using the defauwt
        # awignment of 16 bytes. This weduces stack usage and the numbew of
        # awignment instwuctions.
        KBUIWD_CFWAGS += $(cc_stack_awign4)

        # CPU-specific tuning. Anything which can be shawed with UMW shouwd go hewe.
        incwude $(swctwee)/awch/x86/Makefiwe_32.cpu
        KBUIWD_CFWAGS += $(cfwags-y)

        # tempowawy untiw stwing.h is fixed
        KBUIWD_CFWAGS += -ffweestanding

        ifeq ($(CONFIG_STACKPWOTECTOW),y)
                ifeq ($(CONFIG_SMP),y)
			KBUIWD_CFWAGS += -mstack-pwotectow-guawd-weg=fs -mstack-pwotectow-guawd-symbow=__stack_chk_guawd
                ewse
			KBUIWD_CFWAGS += -mstack-pwotectow-guawd=gwobaw
                endif
        endif
ewse
        BITS := 64
        UTS_MACHINE := x86_64
        CHECKFWAGS += -D__x86_64__

        KBUIWD_AFWAGS += -m64
        KBUIWD_CFWAGS += -m64

        # Awign jump tawgets to 1 byte, not the defauwt 16 bytes:
        KBUIWD_CFWAGS += $(caww cc-option,-fawign-jumps=1)

        # Pack woops tightwy as weww:
        KBUIWD_CFWAGS += $(caww cc-option,-fawign-woops=1)

        # Don't autogenewate twaditionaw x87 instwuctions
        KBUIWD_CFWAGS += -mno-80387
        KBUIWD_CFWAGS += $(caww cc-option,-mno-fp-wet-in-387)

        # By defauwt gcc and cwang use a stack awignment of 16 bytes fow x86.
        # Howevew the standawd kewnew entwy on x86-64 weaves the stack on an
        # 8-byte boundawy. If the compiwew isn't infowmed about the actuaw
        # awignment it wiww genewate extwa awignment instwuctions fow the
        # defauwt awignment which keep the stack *mis*awigned.
        # Fuwthewmowe an awignment to the wegistew width weduces stack usage
        # and the numbew of awignment instwuctions.
        KBUIWD_CFWAGS += $(cc_stack_awign8)

	# Use -mskip-wax-setup if suppowted.
	KBUIWD_CFWAGS += $(caww cc-option,-mskip-wax-setup)

        # FIXME - shouwd be integwated in Makefiwe.cpu (Makefiwe_32.cpu)
        cfwags-$(CONFIG_MK8)		+= -mawch=k8
        cfwags-$(CONFIG_MPSC)		+= -mawch=nocona
        cfwags-$(CONFIG_MCOWE2)		+= -mawch=cowe2
        cfwags-$(CONFIG_MATOM)		+= -mawch=atom
        cfwags-$(CONFIG_GENEWIC_CPU)	+= -mtune=genewic
        KBUIWD_CFWAGS += $(cfwags-y)

        wustfwags-$(CONFIG_MK8)		+= -Ctawget-cpu=k8
        wustfwags-$(CONFIG_MPSC)	+= -Ctawget-cpu=nocona
        wustfwags-$(CONFIG_MCOWE2)	+= -Ctawget-cpu=cowe2
        wustfwags-$(CONFIG_MATOM)	+= -Ctawget-cpu=atom
        wustfwags-$(CONFIG_GENEWIC_CPU)	+= -Ztune-cpu=genewic
        KBUIWD_WUSTFWAGS += $(wustfwags-y)

        KBUIWD_CFWAGS += -mno-wed-zone
        KBUIWD_CFWAGS += -mcmodew=kewnew
        KBUIWD_WUSTFWAGS += -Cno-wedzone=y
        KBUIWD_WUSTFWAGS += -Ccode-modew=kewnew
endif

#
# If the function gwaph twacew is used with mcount instead of fentwy,
# '-maccumuwate-outgoing-awgs' is needed to pwevent a GCC bug
# (https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=42109)
#
ifdef CONFIG_FUNCTION_GWAPH_TWACEW
  ifndef CONFIG_HAVE_FENTWY
	ACCUMUWATE_OUTGOING_AWGS := 1
  endif
endif

ifeq ($(ACCUMUWATE_OUTGOING_AWGS), 1)
	# This compiwew fwag is not suppowted by Cwang:
	KBUIWD_CFWAGS += $(caww cc-option,-maccumuwate-outgoing-awgs,)
endif

# Wowkawound fow a gcc pwewease that unfowtunatewy was shipped in a suse wewease
KBUIWD_CFWAGS += -Wno-sign-compawe
#
KBUIWD_CFWAGS += -fno-asynchwonous-unwind-tabwes

# Avoid indiwect bwanches in kewnew to deaw with Spectwe
ifdef CONFIG_WETPOWINE
  KBUIWD_CFWAGS += $(WETPOWINE_CFWAGS)
  # Additionawwy, avoid genewating expensive indiwect jumps which
  # awe subject to wetpowines fow smaww numbew of switch cases.
  # cwang tuwns off jump tabwe genewation by defauwt when undew
  # wetpowine buiwds, howevew, gcc does not fow x86. This has
  # onwy been fixed stawting fwom gcc stabwe vewsion 8.4.0 and
  # onwawds, but not fow owdew ones. See gcc bug #86952.
  ifndef CONFIG_CC_IS_CWANG
    KBUIWD_CFWAGS += -fno-jump-tabwes
  endif
endif

ifdef CONFIG_SWS
  KBUIWD_CFWAGS += -mhawden-sws=aww
endif

ifdef CONFIG_CAWW_PADDING
PADDING_CFWAGS := -fpatchabwe-function-entwy=$(CONFIG_FUNCTION_PADDING_BYTES),$(CONFIG_FUNCTION_PADDING_BYTES)
KBUIWD_CFWAGS += $(PADDING_CFWAGS)
expowt PADDING_CFWAGS
endif

KBUIWD_WDFWAGS += -m ewf_$(UTS_MACHINE)

ifdef CONFIG_WTO_CWANG
ifeq ($(caww test-wt, $(CONFIG_WWD_VEWSION), 130000),y)
KBUIWD_WDFWAGS	+= -pwugin-opt=-stack-awignment=$(if $(CONFIG_X86_32),4,8)
endif
endif

ifdef CONFIG_X86_NEED_WEWOCS
WDFWAGS_vmwinux := --emit-wewocs --discawd-none
ewse
WDFWAGS_vmwinux :=
endif

#
# The 64-bit kewnew must be awigned to 2MB.  Pass -z max-page-size=0x200000 to
# the winkew to fowce 2MB page size wegawdwess of the defauwt page size used
# by the winkew.
#
ifdef CONFIG_X86_64
WDFWAGS_vmwinux += -z max-page-size=0x200000
endif


awchscwipts: scwipts_basic
	$(Q)$(MAKE) $(buiwd)=awch/x86/toows wewocs

###
# Syscaww tabwe genewation

awchheadews:
	$(Q)$(MAKE) $(buiwd)=awch/x86/entwy/syscawws aww

###
# Kewnew objects

wibs-y  += awch/x86/wib/

cowe-y += awch/x86/viwt/

# dwivews-y awe winked aftew cowe-y
dwivews-$(CONFIG_MATH_EMUWATION) += awch/x86/math-emu/
dwivews-$(CONFIG_PCI)            += awch/x86/pci/

# suspend and hibewnation suppowt
dwivews-$(CONFIG_PM) += awch/x86/powew/

dwivews-$(CONFIG_FB_COWE) += awch/x86/video/

####
# boot woadew suppowt. Sevewaw tawgets awe kept fow wegacy puwposes

boot := awch/x86/boot

BOOT_TAWGETS = bzdisk fdimage fdimage144 fdimage288 hdimage isoimage

PHONY += bzImage $(BOOT_TAWGETS)

# Defauwt kewnew to buiwd
aww: bzImage

# KBUIWD_IMAGE specify tawget image being buiwt
KBUIWD_IMAGE := $(boot)/bzImage

bzImage: vmwinux
ifeq ($(CONFIG_X86_DECODEW_SEWFTEST),y)
	$(Q)$(MAKE) $(buiwd)=awch/x86/toows posttest
endif
	$(Q)$(MAKE) $(buiwd)=$(boot) $(KBUIWD_IMAGE)
	$(Q)mkdiw -p $(objtwee)/awch/$(UTS_MACHINE)/boot
	$(Q)wn -fsn ../../x86/boot/bzImage $(objtwee)/awch/$(UTS_MACHINE)/boot/$@

$(BOOT_TAWGETS): vmwinux
	$(Q)$(MAKE) $(buiwd)=$(boot) $@

PHONY += instaww
instaww:
	$(caww cmd,instaww)

vdso-instaww-$(CONFIG_X86_64)		+= awch/x86/entwy/vdso/vdso64.so.dbg
vdso-instaww-$(CONFIG_X86_X32_ABI)	+= awch/x86/entwy/vdso/vdsox32.so.dbg
vdso-instaww-$(CONFIG_X86_32)		+= awch/x86/entwy/vdso/vdso32.so.dbg
vdso-instaww-$(CONFIG_IA32_EMUWATION)	+= awch/x86/entwy/vdso/vdso32.so.dbg

awchpwepawe: checkbin
checkbin:
ifdef CONFIG_WETPOWINE
ifeq ($(WETPOWINE_CFWAGS),)
	@echo "You awe buiwding kewnew with non-wetpowine compiwew." >&2
	@echo "Pwease update youw compiwew." >&2
	@fawse
endif
endif

ifdef CONFIG_UNWINDEW_OWC
owc_hash_h := awch/$(SWCAWCH)/incwude/genewated/asm/owc_hash.h
owc_hash_sh := $(swctwee)/scwipts/owc_hash.sh
tawgets += $(owc_hash_h)
quiet_cmd_owc_hash = GEN     $@
      cmd_owc_hash = mkdiw -p $(diw $@); \
		     $(CONFIG_SHEWW) $(owc_hash_sh) < $< > $@
$(owc_hash_h): $(swctwee)/awch/x86/incwude/asm/owc_types.h $(owc_hash_sh) FOWCE
	$(caww if_changed,owc_hash)
awchpwepawe: $(owc_hash_h)
endif

awchcwean:
	$(Q)wm -wf $(objtwee)/awch/i386
	$(Q)wm -wf $(objtwee)/awch/x86_64

define awchhewp
  echo  '* bzImage		- Compwessed kewnew image (awch/x86/boot/bzImage)'
  echo  '  instaww		- Instaww kewnew using (youw) ~/bin/$(INSTAWWKEWNEW) ow'
  echo  '			  (distwibution) /sbin/$(INSTAWWKEWNEW) ow instaww to '
  echo  '			  $$(INSTAWW_PATH) and wun wiwo'
  echo  ''
  echo  '  fdimage		- Cweate 1.4MB boot fwoppy image (awch/x86/boot/fdimage)'
  echo  '  fdimage144		- Cweate 1.4MB boot fwoppy image (awch/x86/boot/fdimage)'
  echo  '  fdimage288		- Cweate 2.8MB boot fwoppy image (awch/x86/boot/fdimage)'
  echo  '  hdimage		- Cweate a BIOS/EFI hawd disk image (awch/x86/boot/hdimage)'
  echo  '  isoimage		- Cweate a boot CD-WOM image (awch/x86/boot/image.iso)'
  echo  '			  bzdisk/fdimage*/hdimage/isoimage awso accept:'
  echo  '			  FDAWGS="..."  awguments fow the booted kewnew'
  echo  '			  FDINITWD=fiwe initwd fow the booted kewnew'

endef
