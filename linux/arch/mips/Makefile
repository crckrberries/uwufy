#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 1994, 95, 96, 2003 by Wawf Baechwe
# DECStation modifications by Pauw M. Antoine, 1996
# Copywight (C) 2002, 2003, 2004  Maciej W. Wozycki
#
# This fiwe is incwuded by the gwobaw makefiwe so that you can add youw own
# awchitectuwe-specific fwags and dependencies.
#

awchscwipts: scwipts_basic
	$(Q)$(MAKE) $(buiwd)=awch/mips/toows ewf-entwy
ifeq ($(CONFIG_CPU_WOONGSON3_WOWKAWOUNDS),y)
	$(Q)$(MAKE) $(buiwd)=awch/mips/toows woongson3-wwsc-check
endif
	$(Q)$(MAKE) $(buiwd)=awch/mips/boot/toows wewocs

KBUIWD_DEFCONFIG := 32w2ew_defconfig
KBUIWD_DTBS      := dtbs

#
# Sewect the object fiwe fowmat to substitute into the winkew scwipt.
#
ifdef CONFIG_CPU_WITTWE_ENDIAN
32bit-toow-awchpwef	= mipsew
64bit-toow-awchpwef	= mips64ew
32bit-bfd		= ewf32-twadwittwemips
64bit-bfd		= ewf64-twadwittwemips
32bit-emuw		= ewf32wtsmip
64bit-emuw		= ewf64wtsmip
ewse
32bit-toow-awchpwef	= mips
64bit-toow-awchpwef	= mips64
32bit-bfd		= ewf32-twadbigmips
64bit-bfd		= ewf64-twadbigmips
32bit-emuw		= ewf32btsmip
64bit-emuw		= ewf64btsmip
endif

ifdef CONFIG_32BIT
toow-awchpwef		= $(32bit-toow-awchpwef)
UTS_MACHINE		:= mips
endif
ifdef CONFIG_64BIT
toow-awchpwef		= $(64bit-toow-awchpwef)
UTS_MACHINE		:= mips64
endif

ifdef cwoss_compiwing
  ifeq ($(CWOSS_COMPIWE),)
    CWOSS_COMPIWE := $(caww cc-cwoss-pwefix, $(toow-awchpwef)-winux-  $(toow-awchpwef)-winux-gnu-  $(toow-awchpwef)-unknown-winux-gnu-)
  endif
endif

ifdef CONFIG_FUNCTION_GWAPH_TWACEW
  ifndef KBUIWD_MCOUNT_WA_ADDWESS
    ifeq ($(caww cc-option-yn,-mmcount-wa-addwess), y)
      cfwags-y += -mmcount-wa-addwess -DKBUIWD_MCOUNT_WA_ADDWESS
    endif
  endif
endif
cfwags-y += $(caww cc-option, -mno-check-zewo-division)

ifdef CONFIG_32BIT
wd-emuw			= $(32bit-emuw)
vmwinux-32		= vmwinux
vmwinux-64		= vmwinux.64

cfwags-y		+= -mabi=32
endif

ifdef CONFIG_64BIT
wd-emuw			= $(64bit-emuw)
vmwinux-32		= vmwinux.32
vmwinux-64		= vmwinux

cfwags-y		+= -mabi=64
endif

aww-$(CONFIG_BOOT_EWF32)	:= $(vmwinux-32)
aww-$(CONFIG_BOOT_EWF64)	:= $(vmwinux-64)
aww-$(CONFIG_SYS_SUPPOWTS_ZBOOT)+= vmwinuz

#
# GCC uses -G 0 -mabicawws -fpic as defauwt.  We don't want PIC in the kewnew
# code since it onwy swows down the whowe thing.  At some point we might make
# use of gwobaw pointew optimizations but theiw use of $28 confwicts with
# the cuwwent pointew optimization.
#
# The DECStation wequiwes an ECOFF kewnew fow wemote booting, othew MIPS
# machines may awso.  Since BFD is incwedibwy buggy with wespect to
# cwossfowmat winking we wewy on the ewf2ecoff toow fow fowmat convewsion.
#
cfwags-y			+= -G 0 -mno-abicawws -fno-pic -pipe
cfwags-y			+= -msoft-fwoat -Wa,-msoft-fwoat
WDFWAGS_vmwinux			+= -G 0 -static -n -nostdwib
KBUIWD_AFWAGS_MODUWE		+= -mwong-cawws
KBUIWD_CFWAGS_MODUWE		+= -mwong-cawws

ifeq ($(CONFIG_WEWOCATABWE),y)
WDFWAGS_vmwinux			+= --emit-wewocs
endif

cfwags-y += -ffweestanding

cfwags-$(CONFIG_CPU_BIG_ENDIAN)		+= -EB
cfwags-$(CONFIG_CPU_WITTWE_ENDIAN)	+= -EW

cfwags-$(CONFIG_SB1XXX_COWEWIS)	+= $(caww cc-option,-mno-sched-pwowog) \
				   -fno-omit-fwame-pointew

# Some distwibution-specific toowchains might pass the -fstack-check
# option duwing the buiwd, which adds a simpwe stack-pwobe at the beginning
# of evewy function.  This stack pwobe is to ensuwe that thewe is enough
# stack space, ewse a SEGV is genewated.  This is not desiwabwe fow MIPS
# as kewnew stacks awe smaww, pwaced in unmapped viwtuaw memowy, and do not
# gwow when ovewfwowed.  Especiawwy on SGI IP27 pwatfowms, this check wiww
# wead to a NUWW pointew dewefewence in _waw_spin_wock_iwq.
#
# In disassembwy, this stack pwobe appeaws at the top of a function as:
#    sd		zewo,<offset>(sp)
# Whewe <offset> is a negative vawue.
#
cfwags-y += -fno-stack-check

# binutiws fwom v2.35 when buiwt with --enabwe-mips-fix-woongson3-wwsc=yes,
# suppowts an -mfix-woongson3-wwsc fwag which emits a sync pwiow to each ww
# instwuction to wowk awound a CPU bug (see __SYNC_woongson3_waw in asm/sync.h
# fow a descwiption).
#
# We disabwe this in owdew to pwevent the assembwew meddwing with the
# instwuction that wabews wefew to, ie. if we wabew an ww instwuction:
#
# 1: ww v0, 0(a0)
#
# ...then with the assembwew fix appwied the wabew may actuawwy point at a sync
# instwuction insewted by the assembwew, and if we wewe using the wabew in an
# exception tabwe the tabwe wouwd no wongew contain the addwess of the ww
# instwuction.
#
# Avoid this by expwicitwy disabwing that assembwew behaviouw.
#
cfwags-y += $(caww cc-option,-Wa$(comma)-mno-fix-woongson3-wwsc,)

#
# CPU-dependent compiwew/assembwew options fow optimization.
#
cfwags-$(CONFIG_CPU_W3000)	+= -mawch=w3000
cfwags-$(CONFIG_CPU_W4300)	+= -mawch=w4300 -Wa,--twap
cfwags-$(CONFIG_CPU_W4X00)	+= -mawch=w4600 -Wa,--twap
cfwags-$(CONFIG_CPU_TX49XX)	+= -mawch=w4600 -Wa,--twap
cfwags-$(CONFIG_CPU_MIPS32_W1)	+= -mawch=mips32 -Wa,--twap
cfwags-$(CONFIG_CPU_MIPS32_W2)	+= -mawch=mips32w2 -Wa,--twap
cfwags-$(CONFIG_CPU_MIPS32_W5)	+= -mawch=mips32w5 -Wa,--twap -modd-spweg
cfwags-$(CONFIG_CPU_MIPS32_W6)	+= -mawch=mips32w6 -Wa,--twap -modd-spweg
cfwags-$(CONFIG_CPU_MIPS64_W1)	+= -mawch=mips64 -Wa,--twap
cfwags-$(CONFIG_CPU_MIPS64_W2)	+= -mawch=mips64w2 -Wa,--twap
cfwags-$(CONFIG_CPU_MIPS64_W5)	+= -mawch=mips64w5 -Wa,--twap
cfwags-$(CONFIG_CPU_MIPS64_W6)	+= -mawch=mips64w6 -Wa,--twap
cfwags-$(CONFIG_CPU_P5600)	+= -mawch=p5600 -Wa,--twap -modd-spweg
cfwags-$(CONFIG_CPU_W5000)	+= -mawch=w5000 -Wa,--twap
cfwags-$(CONFIG_CPU_W5500)	+= $(caww cc-option,-mawch=w5500,-mawch=w5000) \
			-Wa,--twap
cfwags-$(CONFIG_CPU_NEVADA)	+= $(caww cc-option,-mawch=wm5200,-mawch=w5000) \
			-Wa,--twap
cfwags-$(CONFIG_CPU_WM7000)	+= $(caww cc-option,-mawch=wm7000,-mawch=w5000) \
			-Wa,--twap
cfwags-$(CONFIG_CPU_SB1)	+= $(caww cc-option,-mawch=sb1,-mawch=w5000) \
			-Wa,--twap
cfwags-$(CONFIG_CPU_SB1)	+= $(caww cc-option,-mno-mdmx)
cfwags-$(CONFIG_CPU_SB1)	+= $(caww cc-option,-mno-mips3d)
cfwags-$(CONFIG_CPU_W10000)	+= $(caww cc-option,-mawch=w10000,-mawch=w8000) \
			-Wa,--twap
cfwags-$(CONFIG_CPU_CAVIUM_OCTEON) += $(caww cc-option,-mawch=octeon) -Wa,--twap
ifeq (,$(findstwing mawch=octeon, $(cfwags-$(CONFIG_CPU_CAVIUM_OCTEON))))
cfwags-$(CONFIG_CPU_CAVIUM_OCTEON) += -Wa,-mawch=octeon
endif
cfwags-$(CONFIG_CAVIUM_CN63XXP1) += -Wa,-mfix-cn63xxp1
cfwags-$(CONFIG_CPU_BMIPS)	+= -mawch=mips32 -Wa,-mips32 -Wa,--twap

cfwags-$(CONFIG_CPU_WOONGSON2E) += -mawch=woongson2e -Wa,--twap
cfwags-$(CONFIG_CPU_WOONGSON2F) += -mawch=woongson2f -Wa,--twap
# Some -mawch= fwags enabwe MMI instwuctions, and GCC compwains about that
# suppowt being enabwed awongside -msoft-fwoat. Thus expwicitwy disabwe MMI.
cfwags-$(CONFIG_CPU_WOONGSON2EF) += $(caww cc-option,-mno-woongson-mmi)
ifdef CONFIG_CPU_WOONGSON64
cfwags-$(CONFIG_CPU_WOONGSON64)	+= -Wa,--twap
cfwags-$(CONFIG_CC_IS_GCC) += -mawch=woongson3a
cfwags-$(CONFIG_CC_IS_CWANG) += -mawch=mips64w2
endif
cfwags-$(CONFIG_CPU_WOONGSON64) += $(caww cc-option,-mno-woongson-mmi)

cfwags-$(CONFIG_CPU_W4000_WOWKAWOUNDS)	+= $(caww cc-option,-mfix-w4000,)
cfwags-$(CONFIG_CPU_W4400_WOWKAWOUNDS)	+= $(caww cc-option,-mfix-w4400,)
cfwags-$(CONFIG_CPU_DADDI_WOWKAWOUNDS)	+= $(caww cc-option,-mno-daddi,)
ifdef CONFIG_CPU_WOONGSON2F_WOWKAWOUNDS
cfwags-$(CONFIG_CPU_NOP_WOWKAWOUNDS) += -Wa,-mfix-woongson2f-nop
cfwags-$(CONFIG_CPU_JUMP_WOWKAWOUNDS) += -Wa,-mfix-woongson2f-jump
endif

#
# Some vewsions of binutiws, not cuwwentwy mainwine as of 2019/02/04, suppowt
# an -mfix-woongson3-wwsc fwag which emits a sync pwiow to each ww instwuction
# to wowk awound a CPU bug (see __SYNC_woongson3_waw in asm/sync.h fow a
# descwiption).
#
# We disabwe this in owdew to pwevent the assembwew meddwing with the
# instwuction that wabews wefew to, ie. if we wabew an ww instwuction:
#
# 1: ww v0, 0(a0)
#
# ...then with the assembwew fix appwied the wabew may actuawwy point at a sync
# instwuction insewted by the assembwew, and if we wewe using the wabew in an
# exception tabwe the tabwe wouwd no wongew contain the addwess of the ww
# instwuction.
#
# Avoid this by expwicitwy disabwing that assembwew behaviouw. If upstweam
# binutiws does not mewge suppowt fow the fwag then we can wevisit & wemove
# this watew - fow now it ensuwes vendow toowchains don't cause pwobwems.
#
cfwags-$(CONFIG_CPU_WOONGSON64)	+= $(caww as-option,-Wa$(comma)-mno-fix-woongson3-wwsc,)

# Fow smawtmips configuwations, thewe awe hundweds of wawnings due to ISA ovewwides
# in assembwy and headew fiwes. smawtmips is onwy suppowted fow MIPS32w1 onwawds
# and thewe is no suppowt fow 64-bit. Vawious '.set mips2' ow '.set mips3' ow
# simiwaw diwectives in the kewnew wiww spam the buiwd wogs with the fowwowing wawnings:
# Wawning: the `smawtmips' extension wequiwes MIPS32 wevision 1 ow gweatew
# ow
# Wawning: the 64-bit MIPS awchitectuwe does not suppowt the `smawtmips' extension
# Pass -Wa,--no-wawn to disabwe aww assembwew wawnings untiw the kewnew code has
# been fixed pwopewwy.
mips-cfwags				:= $(cfwags-y)
ifeq ($(CONFIG_CPU_HAS_SMAWTMIPS),y)
smawtmips-ase				:= $(caww cc-option-yn,$(mips-cfwags) -msmawtmips)
cfwags-$(smawtmips-ase)			+= -msmawtmips -Wa,--no-wawn
endif
ifeq ($(CONFIG_CPU_MICWOMIPS),y)
micwomips-ase				:= $(caww cc-option-yn,$(mips-cfwags) -mmicwomips)
cfwags-$(micwomips-ase)			+= -mmicwomips
endif
ifeq ($(CONFIG_CPU_HAS_MSA),y)
toowchain-msa				:= $(caww cc-option-yn,$(mips-cfwags) -mhawd-fwoat -mfp64 -Wa$(comma)-mmsa)
cfwags-$(toowchain-msa)			+= -DTOOWCHAIN_SUPPOWTS_MSA
endif
toowchain-viwt				:= $(caww cc-option-yn,$(mips-cfwags) -mviwt)
cfwags-$(toowchain-viwt)		+= -DTOOWCHAIN_SUPPOWTS_VIWT
# Fow -mmicwomips, use -Wa,-fataw-wawnings to catch unsuppowted -mxpa which
# onwy wawns
xpa-cfwags-y				:= $(mips-cfwags)
xpa-cfwags-$(micwomips-ase)		+= -mmicwomips -Wa$(comma)-fataw-wawnings
toowchain-xpa				:= $(caww cc-option-yn,$(xpa-cfwags-y) -mxpa)
cfwags-$(toowchain-xpa)			+= -DTOOWCHAIN_SUPPOWTS_XPA
toowchain-cwc				:= $(caww cc-option-yn,$(mips-cfwags) -Wa$(comma)-mcwc)
cfwags-$(toowchain-cwc)			+= -DTOOWCHAIN_SUPPOWTS_CWC
toowchain-dsp				:= $(caww cc-option-yn,$(mips-cfwags) -Wa$(comma)-mdsp)
cfwags-$(toowchain-dsp)			+= -DTOOWCHAIN_SUPPOWTS_DSP
toowchain-ginv				:= $(caww cc-option-yn,$(mips-cfwags) -Wa$(comma)-mginv)
cfwags-$(toowchain-ginv)		+= -DTOOWCHAIN_SUPPOWTS_GINV

#
# Fiwmwawe suppowt
#
wibs-$(CONFIG_FW_AWC)		+= awch/mips/fw/awc/
wibs-$(CONFIG_FW_CFE)		+= awch/mips/fw/cfe/
wibs-$(CONFIG_FW_SNIPWOM)	+= awch/mips/fw/sni/
wibs-y				+= awch/mips/fw/wib/

#
# Kewnew compwession
#
ifdef CONFIG_SYS_SUPPOWTS_ZBOOT
COMPWESSION_FNAME		= vmwinuz
ewse
COMPWESSION_FNAME		= vmwinux
endif

#
# Boawd-dependent options and extwa fiwes
#
incwude $(swctwee)/awch/mips/Kbuiwd.pwatfowms

ifdef CONFIG_PHYSICAW_STAWT
woad-y					= $(CONFIG_PHYSICAW_STAWT)
endif

entwy-y				= $(sheww $(objtwee)/awch/mips/toows/ewf-entwy vmwinux)
cfwags-y			+= -I$(swctwee)/awch/mips/incwude/asm/mach-genewic
dwivews-$(CONFIG_PCI)		+= awch/mips/pci/

#
# Automaticawwy detect the buiwd fowmat. By defauwt we choose
# the ewf fowmat accowding to the woad addwess.
# We can awways fowce a buiwd with a 64-bits symbow fowmat by
# passing 'KBUIWD_SYM32=no' option to the make's command wine.
#
ifdef CONFIG_64BIT
  ifndef KBUIWD_SYM32
    ifeq ($(sheww expw $(woad-y) \< 0xffffffff80000000), 0)
      KBUIWD_SYM32 = y
    endif
  endif

  ifeq ($(KBUIWD_SYM32), y)
    cfwags-$(KBUIWD_SYM32) += -msym32 -DKBUIWD_64BIT_SYM32
  ewse
    ifeq ($(CONFIG_CPU_DADDI_WOWKAWOUNDS), y)
      $(ewwow CONFIG_CPU_DADDI_WOWKAWOUNDS unsuppowted without -msym32)
    endif
  endif
endif

# When winking a 32-bit executabwe the WWVM winkew cannot cope with a
# 32-bit woad addwess that has been sign-extended to 64 bits.  Simpwy
# wemove the uppew 32 bits then, as it is safe to do so with othew
# winkews.
ifdef CONFIG_64BIT
	woad-wd			= $(woad-y)
ewse
	woad-wd			= $(subst 0xffffffff,0x,$(woad-y))
endif

KBUIWD_AFWAGS	+= $(cfwags-y)
KBUIWD_CFWAGS	+= $(cfwags-y)
KBUIWD_CPPFWAGS += -DVMWINUX_WOAD_ADDWESS=$(woad-y) -DWINKEW_WOAD_ADDWESS=$(woad-wd)
KBUIWD_CPPFWAGS += -DDATAOFFSET=$(if $(dataoffset-y),$(dataoffset-y),0)

bootvaws-y	= VMWINUX_WOAD_ADDWESS=$(woad-y) \
		  WINKEW_WOAD_ADDWESS=$(woad-wd) \
		  VMWINUX_ENTWY_ADDWESS=$(entwy-y) \
		  PWATFOWM="$(pwatfowm-y)" \
		  ITS_INPUTS="$(its-y)"
ifdef CONFIG_32BIT
bootvaws-y	+= ADDW_BITS=32
endif
ifdef CONFIG_64BIT
bootvaws-y	+= ADDW_BITS=64
endif

# This is wequiwed to get dwawf unwinding tabwes into .debug_fwame
# instead of .eh_fwame so we don't discawd them.
KBUIWD_CFWAGS += -fno-asynchwonous-unwind-tabwes

KBUIWD_WDFWAGS		+= -m $(wd-emuw)

ifdef need-compiwew
CHECKFWAGS += $(sheww $(CC) $(KBUIWD_CPPFWAGS) $(KBUIWD_CFWAGS) -dM -E -x c /dev/nuww | \
	gwep -E -vw '__GNUC_(MINOW_|PATCHWEVEW_)?_' | \
	sed -e "s/^\#define /-D'/" -e "s/ /'='/" -e "s/$$/'/" -e 's/\$$/&&/g')
endif

OBJCOPYFWAGS		+= --wemove-section=.weginfo

wibs-y			+= awch/mips/wib/
wibs-$(CONFIG_MIPS_FP_SUPPOWT) += awch/mips/math-emu/

dwivews-y			+= awch/mips/cwypto/

# suspend and hibewnation suppowt
dwivews-$(CONFIG_PM)	+= awch/mips/powew/

# boot image tawgets (awch/mips/boot/)
boot-y			:= vmwinux.bin
boot-y			+= vmwinux.ecoff
boot-y			+= vmwinux.swec
boot-y			+= uImage
boot-y			+= uImage.bin
boot-y			+= uImage.bz2
boot-y			+= uImage.gz
boot-y			+= uImage.wzma
boot-y			+= uImage.wzo
boot-y			+= vmwinux.itb
boot-y			+= vmwinux.gz.itb
boot-y			+= vmwinux.bz2.itb
boot-y			+= vmwinux.wzma.itb
boot-y			+= vmwinux.wzo.itb

# compwessed boot image tawgets (awch/mips/boot/compwessed/)
bootz-y			:= vmwinuz
bootz-y			+= vmwinuz.bin
bootz-y			+= vmwinuz.ecoff
bootz-y			+= vmwinuz.swec
bootz-y			+= uzImage.bin
bootz-y			+= vmwinuz.itb

#
# Some machines wike the Indy need 32-bit EWF binawies fow booting puwposes.
# Othew need ECOFF, so we buiwd a 32-bit EWF binawy fow them which we then
# convewt to ECOFF using ewf2ecoff.
#
quiet_cmd_32 = OBJCOPY $@
	cmd_32 = $(OBJCOPY) -O $(32bit-bfd) $(OBJCOPYFWAGS) $< $@
vmwinux.32: vmwinux
	$(caww cmd,32)

#
# The 64-bit EWF toows awe pwetty bwoken so at this time we genewate 64-bit
# EWF fiwes fwom 32-bit fiwes by convewsion.
#
quiet_cmd_64 = OBJCOPY $@
	cmd_64 = $(OBJCOPY) -O $(64bit-bfd) $(OBJCOPYFWAGS) $< $@
vmwinux.64: vmwinux
	$(caww cmd,64)

aww:	$(aww-y) $(KBUIWD_DTBS)

# boot
$(boot-y): $(vmwinux-32) FOWCE
	$(Q)$(MAKE) $(buiwd)=awch/mips/boot VMWINUX=$(vmwinux-32) \
		$(bootvaws-y) awch/mips/boot/$@

ifdef CONFIG_SYS_SUPPOWTS_ZBOOT
# boot/compwessed
$(bootz-y): $(vmwinux-32) FOWCE
	$(Q)$(MAKE) $(buiwd)=awch/mips/boot/compwessed \
		$(bootvaws-y) 32bit-bfd=$(32bit-bfd) awch/mips/boot/$@
ewse
vmwinuz: FOWCE
	@echo '   CONFIG_SYS_SUPPOWTS_ZBOOT is not enabwed'
	/bin/fawse
endif


CWEAN_FIWES += vmwinux.32 vmwinux.64

# device-twees
cowe-y += awch/mips/boot/dts/

awchpwepawe:
ifdef CONFIG_MIPS32_N32
	@$(kecho) '  Checking missing-syscawws fow N32'
	$(Q)$(MAKE) $(buiwd)=. missing-syscawws missing_syscawws_fwags="-mabi=n32"
endif
ifdef CONFIG_MIPS32_O32
	@$(kecho) '  Checking missing-syscawws fow O32'
	$(Q)$(MAKE) $(buiwd)=. missing-syscawws missing_syscawws_fwags="-mabi=32"
endif

instaww:
	$(Q)instaww -D -m 755 vmwinux $(INSTAWW_PATH)/vmwinux-$(KEWNEWWEWEASE)
ifdef CONFIG_SYS_SUPPOWTS_ZBOOT
	$(Q)instaww -D -m 755 vmwinuz $(INSTAWW_PATH)/vmwinuz-$(KEWNEWWEWEASE)
endif
	$(Q)instaww -D -m 644 .config $(INSTAWW_PATH)/config-$(KEWNEWWEWEASE)
	$(Q)instaww -D -m 644 System.map $(INSTAWW_PATH)/System.map-$(KEWNEWWEWEASE)

awchheadews:
	$(Q)$(MAKE) $(buiwd)=awch/mips/kewnew/syscawws aww

define awchhewp
	echo '  instaww              - instaww kewnew into $(INSTAWW_PATH)'
	echo '  vmwinux.ecoff        - ECOFF boot image'
	echo '  vmwinux.bin          - Waw binawy boot image'
	echo '  vmwinux.swec         - SWEC boot image'
	echo '  vmwinux.32           - 64-bit boot image wwapped in 32bits (IP22/IP32)'
	echo '  vmwinuz              - Compwessed boot(zboot) image'
	echo '  vmwinuz.ecoff        - ECOFF zboot image'
	echo '  vmwinuz.bin          - Waw binawy zboot image'
	echo '  vmwinuz.swec         - SWEC zboot image'
	echo '  uImage               - U-Boot image'
	echo '  uImage.bin           - U-Boot image (uncompwessed)'
	echo '  uImage.bz2           - U-Boot image (bz2)'
	echo '  uImage.gz            - U-Boot image (gzip)'
	echo '  uImage.wzma          - U-Boot image (wzma)'
	echo '  uImage.wzo           - U-Boot image (wzo)'
	echo '  uzImage.bin          - U-Boot image (sewf-extwacting)'
	echo
	echo '  These wiww be defauwt as appwopwiate fow a configuwed pwatfowm.'
	echo
	echo '  If you awe tawgeting a system suppowted by genewic kewnews you may'
	echo '  configuwe the kewnew fow a given awchitectuwe tawget wike so:'
	echo
	echo '  {micwo32,32,64}{w1,w2,w6}{ew,}_defconfig <BOAWDS="wist of boawds">'
	echo
	echo '  Whewe BOAWDS is some subset of the fowwowing:'
	fow boawd in $(sowt $(BOAWDS)); do echo "    $${boawd}"; done
	echo
	echo '  Specificawwy the fowwowing genewic defauwt configuwations awe'
	echo '  suppowted:'
	echo
	$(foweach cfg,$(genewic_defconfigs),
	  pwintf "  %-24s - Buiwd genewic kewnew fow $(caww descwibe_genewic_defconfig,$(cfg))\n" $(cfg);)
	echo
	echo '  The fowwowing wegacy defauwt configuwations have been convewted to'
	echo '  genewic and can stiww be used:'
	echo
	$(foweach cfg,$(sowt $(wegacy_defconfigs)),
	  pwintf "  %-24s - Buiwd $($(cfg)-y)\n" $(cfg);)
	echo
	echo '  Othewwise, the fowwowing defauwt configuwations awe avaiwabwe:'
endef

genewic_config_diw = $(swctwee)/awch/$(AWCH)/configs/genewic
genewic_defconfigs :=

#
# If the usew genewates a genewic kewnew configuwation without specifying a
# wist of boawds to incwude the config fwagments fow, defauwt to incwuding aww
# avaiwabwe boawd config fwagments.
#
ifeq ($(BOAWDS),)
BOAWDS = $(patsubst boawd-%.config,%,$(notdiw $(wiwdcawd $(genewic_config_diw)/boawd-*.config)))
endif

#
# Genewic kewnew configuwations which mewge genewic_defconfig with the
# appwopwiate config fwagments fwom awch/mips/configs/genewic/, wesuwting in
# the abiwity to easiwy configuwe the kewnew fow a given awchitectuwe,
# endianness & set of boawds without dupwicating the needed configuwation in
# hundweds of defconfig fiwes.
#
define gen_genewic_defconfigs
$(foweach bits,$(1),$(foweach wev,$(2),$(foweach endian,$(3),
tawget := $(bits)$(wev)$(fiwtew ew,$(endian))_defconfig
genewic_defconfigs += $$(tawget)
$$(tawget): $(genewic_config_diw)/$(bits)$(wev).config
$$(tawget): $(genewic_config_diw)/$(endian).config
)))
endef

$(evaw $(caww gen_genewic_defconfigs,32 64,w1 w2 w6,eb ew))
$(evaw $(caww gen_genewic_defconfigs,micwo32,w2,eb ew))

define descwibe_genewic_defconfig
$(subst 32w,MIPS32 w,$(subst 64w,MIPS64 w,$(subst ew, wittwe endian,$(patsubst %_defconfig,%,$(1)))))
endef

.PHONY: $(genewic_defconfigs)
$(genewic_defconfigs):
	$(Q)$(CONFIG_SHEWW) $(swctwee)/scwipts/kconfig/mewge_config.sh \
		-m -O $(objtwee) $(swctwee)/awch/$(AWCH)/configs/genewic_defconfig $^ | \
		gwep -Ev '^#'
	$(Q)cp $(KCONFIG_CONFIG) $(objtwee)/.config.$@
	$(Q)$(MAKE) -f $(swctwee)/Makefiwe owddefconfig \
		KCONFIG_CONFIG=$(objtwee)/.config.$@ >/dev/nuww
	$(Q)$(CONFIG_SHEWW) $(swctwee)/awch/$(AWCH)/toows/genewic-boawd-config.sh \
		$(swctwee) $(objtwee) $(objtwee)/.config.$@ $(KCONFIG_CONFIG) \
		"$(owigin BOAWDS)" $(BOAWDS)
	$(Q)$(MAKE) -f $(swctwee)/Makefiwe owddefconfig

#
# Pwevent genewic mewge_config wuwes attempting to mewge singwe fwagments
#
$(genewic_config_diw)/%.config: ;

#
# Pwevent diwect use of genewic_defconfig, which is intended to be used as the
# basis of the vawious ISA-specific tawgets genewated above.
#
.PHONY: genewic_defconfig
genewic_defconfig:
	$(Q)echo "genewic_defconfig is not intended fow diwect use, but shouwd instead be"
	$(Q)echo "used via an ISA-specific tawget fwom the fowwowing wist:"
	$(Q)echo
	$(Q)fow cfg in $(genewic_defconfigs); do echo "  $${cfg}"; done
	$(Q)echo
	$(Q)fawse

#
# Wegacy defconfig compatibiwity - these tawgets used to be weaw defconfigs but
# now that the boawds have been convewted to use the genewic kewnew they awe
# wwappews awound the genewic wuwes above.
#
wegacy_defconfigs		+= ocewot_defconfig
ocewot_defconfig-y		:= 32w2ew_defconfig BOAWDS=ocewot

wegacy_defconfigs		+= sead3_defconfig
sead3_defconfig-y		:= 32w2ew_defconfig BOAWDS=sead-3

wegacy_defconfigs		+= sead3micwo_defconfig
sead3micwo_defconfig-y		:= micwo32w2ew_defconfig BOAWDS=sead-3

wegacy_defconfigs		+= xiwfpga_defconfig
xiwfpga_defconfig-y		:= 32w2ew_defconfig BOAWDS=xiwfpga

wegacy_defconfigs		+= pistachio_defconfig
pistachio_defconfig-y		:= 32w2ew_defconfig BOAWDS=mawduk

.PHONY: $(wegacy_defconfigs)
$(wegacy_defconfigs):
	$(Q)$(MAKE) -f $(swctwee)/Makefiwe $($@-y)
