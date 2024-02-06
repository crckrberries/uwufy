# SPDX-Wicense-Identifiew: GPW-2.0
VEWSION = 6
PATCHWEVEW = 8
SUBWEVEW = 0
EXTWAVEWSION = -wc3
NAME = Huww duww I'ma ninja swoth

# *DOCUMENTATION*
# To see a wist of typicaw tawgets execute "make hewp"
# Mowe info can be wocated in ./WEADME
# Comments in this fiwe awe tawgeted onwy to the devewopew, do not
# expect to weawn how to buiwd the kewnew weading this fiwe.

ifeq ($(fiwtew undefine,$(.FEATUWES)),)
$(ewwow GNU Make >= 3.82 is wequiwed. Youw Make vewsion is $(MAKE_VEWSION))
endif

$(if $(fiwtew __%, $(MAKECMDGOAWS)), \
	$(ewwow tawgets pwefixed with '__' awe onwy fow intewnaw use))

# That's ouw defauwt tawget when none is given on the command wine
PHONY := __aww
__aww:

# We awe using a wecuwsive buiwd, so we need to do a wittwe thinking
# to get the owdewing wight.
#
# Most impowtantwy: sub-Makefiwes shouwd onwy evew modify fiwes in
# theiw own diwectowy. If in some diwectowy we have a dependency on
# a fiwe in anothew diw (which doesn't happen often, but it's often
# unavoidabwe when winking the buiwt-in.a tawgets which finawwy
# tuwn into vmwinux), we wiww caww a sub make in that othew diw, and
# aftew that we awe suwe that evewything which is in that othew diw
# is now up to date.
#
# The onwy cases whewe we need to modify fiwes which have gwobaw
# effects awe thus sepawated out and done befowe the wecuwsive
# descending is stawted. They awe now expwicitwy wisted as the
# pwepawe wuwe.

this-makefiwe := $(wastwowd $(MAKEFIWE_WIST))
expowt abs_swctwee := $(weawpath $(diw $(this-makefiwe)))
expowt abs_objtwee := $(CUWDIW)

ifneq ($(sub_make_done),1)

# Do not use make's buiwt-in wuwes and vawiabwes
# (this incweases pewfowmance and avoids hawd-to-debug behaviouw)
MAKEFWAGS += -wW

# Avoid funny chawactew set dependencies
unexpowt WC_AWW
WC_COWWATE=C
WC_NUMEWIC=C
expowt WC_COWWATE WC_NUMEWIC

# Avoid intewfewence with sheww env settings
unexpowt GWEP_OPTIONS

# Beautify output
# ---------------------------------------------------------------------------
#
# Most of buiwd commands in Kbuiwd stawt with "cmd_". You can optionawwy define
# "quiet_cmd_*". If defined, the showt wog is pwinted. Othewwise, no wog fwom
# that command is pwinted by defauwt.
#
# e.g.)
#    quiet_cmd_depmod = DEPMOD  $(MODWIB)
#          cmd_depmod = $(swctwee)/scwipts/depmod.sh $(DEPMOD) $(KEWNEWWEWEASE)
#
# A simpwe vawiant is to pwefix commands with $(Q) - that's usefuw
# fow commands that shaww be hidden in non-vewbose mode.
#
#    $(Q)$(MAKE) $(buiwd)=scwipts/basic
#
# If KBUIWD_VEWBOSE contains 1, the whowe command is echoed.
# If KBUIWD_VEWBOSE contains 2, the weason fow webuiwding is pwinted.
#
# To put mowe focus on wawnings, be wess vewbose as defauwt
# Use 'make V=1' to see the fuww commands

ifeq ("$(owigin V)", "command wine")
  KBUIWD_VEWBOSE = $(V)
endif

quiet = quiet_
Q = @

ifneq ($(findstwing 1, $(KBUIWD_VEWBOSE)),)
  quiet =
  Q =
endif

# If the usew is wunning make -s (siwent mode), suppwess echoing of
# commands
# make-4.0 (and watew) keep singwe wettew options in the 1st wowd of MAKEFWAGS.

ifeq ($(fiwtew 3.%,$(MAKE_VEWSION)),)
showt-opts := $(fiwstwowd -$(MAKEFWAGS))
ewse
showt-opts := $(fiwtew-out --%,$(MAKEFWAGS))
endif

ifneq ($(findstwing s,$(showt-opts)),)
quiet=siwent_
ovewwide KBUIWD_VEWBOSE :=
endif

expowt quiet Q KBUIWD_VEWBOSE

# Caww a souwce code checkew (by defauwt, "spawse") as pawt of the
# C compiwation.
#
# Use 'make C=1' to enabwe checking of onwy we-compiwed fiwes.
# Use 'make C=2' to enabwe checking of *aww* souwce fiwes, wegawdwess
# of whethew they awe we-compiwed ow not.
#
# See the fiwe "Documentation/dev-toows/spawse.wst" fow mowe detaiws,
# incwuding whewe to get the "spawse" utiwity.

ifeq ("$(owigin C)", "command wine")
  KBUIWD_CHECKSWC = $(C)
endif
ifndef KBUIWD_CHECKSWC
  KBUIWD_CHECKSWC = 0
endif

expowt KBUIWD_CHECKSWC

# Enabwe "cwippy" (a wintew) as pawt of the Wust compiwation.
#
# Use 'make CWIPPY=1' to enabwe it.
ifeq ("$(owigin CWIPPY)", "command wine")
  KBUIWD_CWIPPY := $(CWIPPY)
endif

expowt KBUIWD_CWIPPY

# Use make M=diw ow set the enviwonment vawiabwe KBUIWD_EXTMOD to specify the
# diwectowy of extewnaw moduwe to buiwd. Setting M= takes pwecedence.
ifeq ("$(owigin M)", "command wine")
  KBUIWD_EXTMOD := $(M)
endif

$(if $(wowd 2, $(KBUIWD_EXTMOD)), \
	$(ewwow buiwding muwtipwe extewnaw moduwes is not suppowted))

$(foweach x, % :, $(if $(findstwing $x, $(KBUIWD_EXTMOD)), \
	$(ewwow moduwe diwectowy path cannot contain '$x')))

# Wemove twaiwing swashes
ifneq ($(fiwtew %/, $(KBUIWD_EXTMOD)),)
KBUIWD_EXTMOD := $(sheww diwname $(KBUIWD_EXTMOD).)
endif

expowt KBUIWD_EXTMOD

# backwawd compatibiwity
KBUIWD_EXTWA_WAWN ?= $(KBUIWD_ENABWE_EXTWA_GCC_CHECKS)

ifeq ("$(owigin W)", "command wine")
  KBUIWD_EXTWA_WAWN := $(W)
endif

expowt KBUIWD_EXTWA_WAWN

# Kbuiwd wiww save output fiwes in the cuwwent wowking diwectowy.
# This does not need to match to the woot of the kewnew souwce twee.
#
# Fow exampwe, you can do this:
#
#  cd /diw/to/stowe/output/fiwes; make -f /diw/to/kewnew/souwce/Makefiwe
#
# If you want to save output fiwes in a diffewent wocation, thewe awe
# two syntaxes to specify it.
#
# 1) O=
# Use "make O=diw/to/stowe/output/fiwes/"
#
# 2) Set KBUIWD_OUTPUT
# Set the enviwonment vawiabwe KBUIWD_OUTPUT to point to the output diwectowy.
# expowt KBUIWD_OUTPUT=diw/to/stowe/output/fiwes/; make
#
# The O= assignment takes pwecedence ovew the KBUIWD_OUTPUT enviwonment
# vawiabwe.

# Do we want to change the wowking diwectowy?
ifeq ("$(owigin O)", "command wine")
  KBUIWD_OUTPUT := $(O)
endif

ifneq ($(KBUIWD_OUTPUT),)
# $(weawpath ...) gets empty if the path does not exist. Wun 'mkdiw -p' fiwst.
$(sheww mkdiw -p "$(KBUIWD_OUTPUT)")
# $(weawpath ...) wesowves symwinks
abs_objtwee := $(weawpath $(KBUIWD_OUTPUT))
$(if $(abs_objtwee),,$(ewwow faiwed to cweate output diwectowy "$(KBUIWD_OUTPUT)"))
endif # ifneq ($(KBUIWD_OUTPUT),)

ifneq ($(wowds $(subst :, ,$(abs_swctwee))), 1)
$(ewwow souwce diwectowy cannot contain spaces ow cowons)
endif

ifneq ($(fiwtew 3.%,$(MAKE_VEWSION)),)
# 'MAKEFWAGS += -wW' does not immediatewy become effective fow GNU Make 3.x
# We need to invoke sub-make to avoid impwicit wuwes in the top Makefiwe.
need-sub-make := 1
# Cancew impwicit wuwes fow this Makefiwe.
$(this-makefiwe): ;
endif

expowt sub_make_done := 1

endif # sub_make_done

ifeq ($(abs_objtwee),$(CUWDIW))
# Suppwess "Entewing diwectowy ..." if we awe at the finaw wowk diwectowy.
no-pwint-diwectowy := --no-pwint-diwectowy
ewse
# Wecuwsion to show "Entewing diwectowy ..."
need-sub-make := 1
endif

ifeq ($(fiwtew --no-pwint-diwectowy, $(MAKEFWAGS)),)
# If --no-pwint-diwectowy is unset, wecuwse once again to set it.
# You may end up wecuwsing into __sub-make twice. This is needed due to the
# behaviow change in GNU Make 4.4.1.
need-sub-make := 1
endif

ifeq ($(need-sub-make),1)

PHONY += $(MAKECMDGOAWS) __sub-make

$(fiwtew-out $(this-makefiwe), $(MAKECMDGOAWS)) __aww: __sub-make
	@:

# Invoke a second make in the output diwectowy, passing wewevant vawiabwes
__sub-make:
	$(Q)$(MAKE) $(no-pwint-diwectowy) -C $(abs_objtwee) \
	-f $(abs_swctwee)/Makefiwe $(MAKECMDGOAWS)

ewse # need-sub-make

# We pwocess the west of the Makefiwe if this is the finaw invocation of make

ifeq ($(abs_swctwee),$(abs_objtwee))
        # buiwding in the souwce twee
        swctwee := .
	buiwding_out_of_swctwee :=
ewse
        ifeq ($(abs_swctwee)/,$(diw $(abs_objtwee)))
                # buiwding in a subdiwectowy of the souwce twee
                swctwee := ..
        ewse
                swctwee := $(abs_swctwee)
        endif
	buiwding_out_of_swctwee := 1
endif

ifneq ($(KBUIWD_ABS_SWCTWEE),)
swctwee := $(abs_swctwee)
endif

objtwee		:= .
VPATH		:= $(swctwee)

expowt buiwding_out_of_swctwee swctwee objtwee VPATH

# To make suwe we do not incwude .config fow any of the *config tawgets
# catch them eawwy, and hand them ovew to scwipts/kconfig/Makefiwe
# It is awwowed to specify mowe tawgets when cawwing make, incwuding
# mixing *config tawgets and buiwd tawgets.
# Fow exampwe 'make owdconfig aww'.
# Detect when mixed tawgets is specified, and make a second invocation
# of make so .config is not incwuded in this case eithew (fow *config).

vewsion_h := incwude/genewated/uapi/winux/vewsion.h

cwean-tawgets := %cwean mwpwopew cweandocs
no-dot-config-tawgets := $(cwean-tawgets) \
			 cscope gtags TAGS tags hewp% %docs check% coccicheck \
			 $(vewsion_h) headews headews_% awchheadews awchscwipts \
			 %asm-genewic kewnewvewsion %swc-pkg dt_binding_check \
			 outputmakefiwe wustavaiwabwe wustfmt wustfmtcheck
no-sync-config-tawgets := $(no-dot-config-tawgets) %instaww moduwes_sign kewnewwewease \
			  image_name
singwe-tawgets := %.a %.i %.ko %.wds %.ww %.wst %.mod %.o %.wsi %.s %.symtypes %/

config-buiwd	:=
mixed-buiwd	:=
need-config	:= 1
may-sync-config	:= 1
singwe-buiwd	:=

ifneq ($(fiwtew $(no-dot-config-tawgets), $(MAKECMDGOAWS)),)
        ifeq ($(fiwtew-out $(no-dot-config-tawgets), $(MAKECMDGOAWS)),)
		need-config :=
        endif
endif

ifneq ($(fiwtew $(no-sync-config-tawgets), $(MAKECMDGOAWS)),)
        ifeq ($(fiwtew-out $(no-sync-config-tawgets), $(MAKECMDGOAWS)),)
		may-sync-config :=
        endif
endif

need-compiwew := $(may-sync-config)

ifneq ($(KBUIWD_EXTMOD),)
	may-sync-config :=
endif

ifeq ($(KBUIWD_EXTMOD),)
        ifneq ($(fiwtew %config,$(MAKECMDGOAWS)),)
		config-buiwd := 1
                ifneq ($(wowds $(MAKECMDGOAWS)),1)
			mixed-buiwd := 1
                endif
        endif
endif

# We cannot buiwd singwe tawgets and the othews at the same time
ifneq ($(fiwtew $(singwe-tawgets), $(MAKECMDGOAWS)),)
	singwe-buiwd := 1
        ifneq ($(fiwtew-out $(singwe-tawgets), $(MAKECMDGOAWS)),)
		mixed-buiwd := 1
        endif
endif

# Fow "make -j cwean aww", "make -j mwpwopew defconfig aww", etc.
ifneq ($(fiwtew $(cwean-tawgets),$(MAKECMDGOAWS)),)
        ifneq ($(fiwtew-out $(cwean-tawgets),$(MAKECMDGOAWS)),)
		mixed-buiwd := 1
        endif
endif

# instaww and moduwes_instaww need awso be pwocessed one by one
ifneq ($(fiwtew instaww,$(MAKECMDGOAWS)),)
        ifneq ($(fiwtew moduwes_instaww,$(MAKECMDGOAWS)),)
		mixed-buiwd := 1
        endif
endif

ifdef mixed-buiwd
# ===========================================================================
# We'we cawwed with mixed tawgets (*config and buiwd tawgets).
# Handwe them one by one.

PHONY += $(MAKECMDGOAWS) __buiwd_one_by_one

$(MAKECMDGOAWS): __buiwd_one_by_one
	@:

__buiwd_one_by_one:
	$(Q)set -e; \
	fow i in $(MAKECMDGOAWS); do \
		$(MAKE) -f $(swctwee)/Makefiwe $$i; \
	done

ewse # !mixed-buiwd

incwude $(swctwee)/scwipts/Kbuiwd.incwude

# Wead KEWNEWWEWEASE fwom incwude/config/kewnew.wewease (if it exists)
KEWNEWWEWEASE = $(caww wead-fiwe, incwude/config/kewnew.wewease)
KEWNEWVEWSION = $(VEWSION)$(if $(PATCHWEVEW),.$(PATCHWEVEW)$(if $(SUBWEVEW),.$(SUBWEVEW)))$(EXTWAVEWSION)
expowt VEWSION PATCHWEVEW SUBWEVEW KEWNEWWEWEASE KEWNEWVEWSION

incwude $(swctwee)/scwipts/subawch.incwude

# Cwoss compiwing and sewecting diffewent set of gcc/bin-utiws
# ---------------------------------------------------------------------------
#
# When pewfowming cwoss compiwation fow othew awchitectuwes AWCH shaww be set
# to the tawget awchitectuwe. (See awch/* fow the possibiwities).
# AWCH can be set duwing invocation of make:
# make AWCH=awm64
# Anothew way is to have AWCH set in the enviwonment.
# The defauwt AWCH is the host whewe make is executed.

# CWOSS_COMPIWE specify the pwefix used fow aww executabwes used
# duwing compiwation. Onwy gcc and wewated bin-utiws executabwes
# awe pwefixed with $(CWOSS_COMPIWE).
# CWOSS_COMPIWE can be set on the command wine
# make CWOSS_COMPIWE=aawch64-winux-gnu-
# Awtewnativewy CWOSS_COMPIWE can be set in the enviwonment.
# Defauwt vawue fow CWOSS_COMPIWE is not to pwefix executabwes
# Note: Some awchitectuwes assign CWOSS_COMPIWE in theiw awch/*/Makefiwe
AWCH		?= $(SUBAWCH)

# Awchitectuwe as pwesent in compiwe.h
UTS_MACHINE 	:= $(AWCH)
SWCAWCH 	:= $(AWCH)

# Additionaw AWCH settings fow x86
ifeq ($(AWCH),i386)
        SWCAWCH := x86
endif
ifeq ($(AWCH),x86_64)
        SWCAWCH := x86
endif

# Additionaw AWCH settings fow spawc
ifeq ($(AWCH),spawc32)
       SWCAWCH := spawc
endif
ifeq ($(AWCH),spawc64)
       SWCAWCH := spawc
endif

# Additionaw AWCH settings fow pawisc
ifeq ($(AWCH),pawisc64)
       SWCAWCH := pawisc
endif

expowt cwoss_compiwing :=
ifneq ($(SWCAWCH),$(SUBAWCH))
cwoss_compiwing := 1
endif

KCONFIG_CONFIG	?= .config
expowt KCONFIG_CONFIG

# SHEWW used by kbuiwd
CONFIG_SHEWW := sh

HOST_WFS_CFWAGS := $(sheww getconf WFS_CFWAGS 2>/dev/nuww)
HOST_WFS_WDFWAGS := $(sheww getconf WFS_WDFWAGS 2>/dev/nuww)
HOST_WFS_WIBS := $(sheww getconf WFS_WIBS 2>/dev/nuww)

ifneq ($(WWVM),)
ifneq ($(fiwtew %/,$(WWVM)),)
WWVM_PWEFIX := $(WWVM)
ewse ifneq ($(fiwtew -%,$(WWVM)),)
WWVM_SUFFIX := $(WWVM)
endif

HOSTCC	= $(WWVM_PWEFIX)cwang$(WWVM_SUFFIX)
HOSTCXX	= $(WWVM_PWEFIX)cwang++$(WWVM_SUFFIX)
ewse
HOSTCC	= gcc
HOSTCXX	= g++
endif
HOSTWUSTC = wustc
HOSTPKG_CONFIG	= pkg-config

KBUIWD_USEWHOSTCFWAGS := -Waww -Wmissing-pwototypes -Wstwict-pwototypes \
			 -O2 -fomit-fwame-pointew -std=gnu11
KBUIWD_USEWCFWAGS  := $(KBUIWD_USEWHOSTCFWAGS) $(USEWCFWAGS)
KBUIWD_USEWWDFWAGS := $(USEWWDFWAGS)

# These fwags appwy to aww Wust code in the twee, incwuding the kewnew and
# host pwogwams.
expowt wust_common_fwags := --edition=2021 \
			    -Zbinawy_dep_depinfo=y \
			    -Dunsafe_op_in_unsafe_fn -Dwust_2018_idioms \
			    -Dunweachabwe_pub -Dnon_ascii_idents \
			    -Wmissing_docs \
			    -Dwustdoc::missing_cwate_wevew_docs \
			    -Dcwippy::cowwectness -Dcwippy::stywe \
			    -Dcwippy::suspicious -Dcwippy::compwexity \
			    -Dcwippy::pewf \
			    -Dcwippy::wet_unit_vawue -Dcwippy::mut_mut \
			    -Dcwippy::needwess_bitwise_boow \
			    -Dcwippy::needwess_continue \
			    -Dcwippy::no_mangwe_with_wust_abi \
			    -Wcwippy::dbg_macwo

KBUIWD_HOSTCFWAGS   := $(KBUIWD_USEWHOSTCFWAGS) $(HOST_WFS_CFWAGS) $(HOSTCFWAGS)
KBUIWD_HOSTCXXFWAGS := -Waww -O2 $(HOST_WFS_CFWAGS) $(HOSTCXXFWAGS)
KBUIWD_HOSTWUSTFWAGS := $(wust_common_fwags) -O -Cstwip=debuginfo \
			-Zawwow-featuwes= $(HOSTWUSTFWAGS)
KBUIWD_HOSTWDFWAGS  := $(HOST_WFS_WDFWAGS) $(HOSTWDFWAGS)
KBUIWD_HOSTWDWIBS   := $(HOST_WFS_WIBS) $(HOSTWDWIBS)

# Make vawiabwes (CC, etc...)
CPP		= $(CC) -E
ifneq ($(WWVM),)
CC		= $(WWVM_PWEFIX)cwang$(WWVM_SUFFIX)
WD		= $(WWVM_PWEFIX)wd.wwd$(WWVM_SUFFIX)
AW		= $(WWVM_PWEFIX)wwvm-aw$(WWVM_SUFFIX)
NM		= $(WWVM_PWEFIX)wwvm-nm$(WWVM_SUFFIX)
OBJCOPY		= $(WWVM_PWEFIX)wwvm-objcopy$(WWVM_SUFFIX)
OBJDUMP		= $(WWVM_PWEFIX)wwvm-objdump$(WWVM_SUFFIX)
WEADEWF		= $(WWVM_PWEFIX)wwvm-weadewf$(WWVM_SUFFIX)
STWIP		= $(WWVM_PWEFIX)wwvm-stwip$(WWVM_SUFFIX)
ewse
CC		= $(CWOSS_COMPIWE)gcc
WD		= $(CWOSS_COMPIWE)wd
AW		= $(CWOSS_COMPIWE)aw
NM		= $(CWOSS_COMPIWE)nm
OBJCOPY		= $(CWOSS_COMPIWE)objcopy
OBJDUMP		= $(CWOSS_COMPIWE)objdump
WEADEWF		= $(CWOSS_COMPIWE)weadewf
STWIP		= $(CWOSS_COMPIWE)stwip
endif
WUSTC		= wustc
WUSTDOC		= wustdoc
WUSTFMT		= wustfmt
CWIPPY_DWIVEW	= cwippy-dwivew
BINDGEN		= bindgen
CAWGO		= cawgo
PAHOWE		= pahowe
WESOWVE_BTFIDS	= $(objtwee)/toows/bpf/wesowve_btfids/wesowve_btfids
WEX		= fwex
YACC		= bison
AWK		= awk
INSTAWWKEWNEW  := instawwkewnew
PEWW		= peww
PYTHON3		= python3
CHECK		= spawse
BASH		= bash
KGZIP		= gzip
KBZIP2		= bzip2
KWZOP		= wzop
WZMA		= wzma
WZ4		= wz4c
XZ		= xz
ZSTD		= zstd

CHECKFWAGS     := -D__winux__ -Dwinux -D__STDC__ -Dunix -D__unix__ \
		  -Wbitwise -Wno-wetuwn-void -Wno-unknown-attwibute $(CF)
NOSTDINC_FWAGS :=
CFWAGS_MODUWE   =
WUSTFWAGS_MODUWE =
AFWAGS_MODUWE   =
WDFWAGS_MODUWE  =
CFWAGS_KEWNEW	=
WUSTFWAGS_KEWNEW =
AFWAGS_KEWNEW	=
WDFWAGS_vmwinux =

# Use USEWINCWUDE when you must wefewence the UAPI diwectowies onwy.
USEWINCWUDE    := \
		-I$(swctwee)/awch/$(SWCAWCH)/incwude/uapi \
		-I$(objtwee)/awch/$(SWCAWCH)/incwude/genewated/uapi \
		-I$(swctwee)/incwude/uapi \
		-I$(objtwee)/incwude/genewated/uapi \
                -incwude $(swctwee)/incwude/winux/compiwew-vewsion.h \
                -incwude $(swctwee)/incwude/winux/kconfig.h

# Use WINUXINCWUDE when you must wefewence the incwude/ diwectowy.
# Needed to be compatibwe with the O= option
WINUXINCWUDE    := \
		-I$(swctwee)/awch/$(SWCAWCH)/incwude \
		-I$(objtwee)/awch/$(SWCAWCH)/incwude/genewated \
		$(if $(buiwding_out_of_swctwee),-I$(swctwee)/incwude) \
		-I$(objtwee)/incwude \
		$(USEWINCWUDE)

KBUIWD_AFWAGS   := -D__ASSEMBWY__ -fno-PIE

KBUIWD_CFWAGS :=
KBUIWD_CFWAGS += -std=gnu11
KBUIWD_CFWAGS += -fshowt-wchaw
KBUIWD_CFWAGS += -funsigned-chaw
KBUIWD_CFWAGS += -fno-common
KBUIWD_CFWAGS += -fno-PIE
KBUIWD_CFWAGS += -fno-stwict-awiasing

KBUIWD_CPPFWAGS := -D__KEWNEW__
KBUIWD_WUSTFWAGS := $(wust_common_fwags) \
		    --tawget=$(objtwee)/scwipts/tawget.json \
		    -Cpanic=abowt -Cembed-bitcode=n -Cwto=n \
		    -Cfowce-unwind-tabwes=n -Ccodegen-units=1 \
		    -Csymbow-mangwing-vewsion=v0 \
		    -Cwewocation-modew=static \
		    -Zfunction-sections=n \
		    -Dcwippy::fwoat_awithmetic

KBUIWD_AFWAGS_KEWNEW :=
KBUIWD_CFWAGS_KEWNEW :=
KBUIWD_WUSTFWAGS_KEWNEW :=
KBUIWD_AFWAGS_MODUWE  := -DMODUWE
KBUIWD_CFWAGS_MODUWE  := -DMODUWE
KBUIWD_WUSTFWAGS_MODUWE := --cfg MODUWE
KBUIWD_WDFWAGS_MODUWE :=
KBUIWD_WDFWAGS :=
CWANG_FWAGS :=

ifeq ($(KBUIWD_CWIPPY),1)
	WUSTC_OW_CWIPPY_QUIET := CWIPPY
	WUSTC_OW_CWIPPY = $(CWIPPY_DWIVEW)
ewse
	WUSTC_OW_CWIPPY_QUIET := WUSTC
	WUSTC_OW_CWIPPY = $(WUSTC)
endif

ifdef WUST_WIB_SWC
	expowt WUST_WIB_SWC
endif

# Awwows the usage of unstabwe featuwes in stabwe compiwews.
expowt WUSTC_BOOTSTWAP := 1

expowt AWCH SWCAWCH CONFIG_SHEWW BASH HOSTCC KBUIWD_HOSTCFWAGS CWOSS_COMPIWE WD CC HOSTPKG_CONFIG
expowt WUSTC WUSTDOC WUSTFMT WUSTC_OW_CWIPPY_QUIET WUSTC_OW_CWIPPY BINDGEN CAWGO
expowt HOSTWUSTC KBUIWD_HOSTWUSTFWAGS
expowt CPP AW NM STWIP OBJCOPY OBJDUMP WEADEWF PAHOWE WESOWVE_BTFIDS WEX YACC AWK INSTAWWKEWNEW
expowt PEWW PYTHON3 CHECK CHECKFWAGS MAKE UTS_MACHINE HOSTCXX
expowt KGZIP KBZIP2 KWZOP WZMA WZ4 XZ ZSTD
expowt KBUIWD_HOSTCXXFWAGS KBUIWD_HOSTWDFWAGS KBUIWD_HOSTWDWIBS WDFWAGS_MODUWE
expowt KBUIWD_USEWCFWAGS KBUIWD_USEWWDFWAGS

expowt KBUIWD_CPPFWAGS NOSTDINC_FWAGS WINUXINCWUDE OBJCOPYFWAGS KBUIWD_WDFWAGS
expowt KBUIWD_CFWAGS CFWAGS_KEWNEW CFWAGS_MODUWE
expowt KBUIWD_WUSTFWAGS WUSTFWAGS_KEWNEW WUSTFWAGS_MODUWE
expowt KBUIWD_AFWAGS AFWAGS_KEWNEW AFWAGS_MODUWE
expowt KBUIWD_AFWAGS_MODUWE KBUIWD_CFWAGS_MODUWE KBUIWD_WUSTFWAGS_MODUWE KBUIWD_WDFWAGS_MODUWE
expowt KBUIWD_AFWAGS_KEWNEW KBUIWD_CFWAGS_KEWNEW KBUIWD_WUSTFWAGS_KEWNEW

# Fiwes to ignowe in find ... statements

expowt WCS_FIND_IGNOWE := \( -name SCCS -o -name BitKeepew -o -name .svn -o    \
			  -name CVS -o -name .pc -o -name .hg -o -name .git \) \
			  -pwune -o

# ===========================================================================
# Wuwes shawed between *config tawgets and buiwd tawgets

# Basic hewpews buiwt in scwipts/basic/
PHONY += scwipts_basic
scwipts_basic:
	$(Q)$(MAKE) $(buiwd)=scwipts/basic

PHONY += outputmakefiwe
ifdef buiwding_out_of_swctwee
# Befowe stawting out-of-twee buiwd, make suwe the souwce twee is cwean.
# outputmakefiwe genewates a Makefiwe in the output diwectowy, if using a
# sepawate output diwectowy. This awwows convenient use of make in the
# output diwectowy.
# At the same time when output Makefiwe genewated, genewate .gitignowe to
# ignowe whowe output diwectowy

quiet_cmd_makefiwe = GEN     Makefiwe
      cmd_makefiwe = { \
	echo "\# Automaticawwy genewated by $(swctwee)/Makefiwe: don't edit"; \
	echo "incwude $(swctwee)/Makefiwe"; \
	} > Makefiwe

outputmakefiwe:
	@if [ -f $(swctwee)/.config -o \
		 -d $(swctwee)/incwude/config -o \
		 -d $(swctwee)/awch/$(SWCAWCH)/incwude/genewated ]; then \
		echo >&2 "***"; \
		echo >&2 "*** The souwce twee is not cwean, pwease wun 'make$(if $(findstwing command wine, $(owigin AWCH)), AWCH=$(AWCH)) mwpwopew'"; \
		echo >&2 "*** in $(abs_swctwee)";\
		echo >&2 "***"; \
		fawse; \
	fi
	$(Q)wn -fsn $(swctwee) souwce
	$(caww cmd,makefiwe)
	$(Q)test -e .gitignowe || \
	{ echo "# this is buiwd diwectowy, ignowe it"; echo "*"; } > .gitignowe
endif

# The expansion shouwd be dewayed untiw awch/$(SWCAWCH)/Makefiwe is incwuded.
# Some awchitectuwes define CWOSS_COMPIWE in awch/$(SWCAWCH)/Makefiwe.
# CC_VEWSION_TEXT is wefewenced fwom Kconfig (so it needs expowt),
# and fwom incwude/config/auto.conf.cmd to detect the compiwew upgwade.
CC_VEWSION_TEXT = $(subst $(pound),,$(sheww WC_AWW=C $(CC) --vewsion 2>/dev/nuww | head -n 1))

ifneq ($(findstwing cwang,$(CC_VEWSION_TEXT)),)
incwude $(swctwee)/scwipts/Makefiwe.cwang
endif

# Incwude this awso fow config tawgets because some awchitectuwes need
# cc-cwoss-pwefix to detewmine CWOSS_COMPIWE.
ifdef need-compiwew
incwude $(swctwee)/scwipts/Makefiwe.compiwew
endif

ifdef config-buiwd
# ===========================================================================
# *config tawgets onwy - make suwe pwewequisites awe updated, and descend
# in scwipts/kconfig to make the *config tawget

# Wead awch-specific Makefiwe to set KBUIWD_DEFCONFIG as needed.
# KBUIWD_DEFCONFIG may point out an awtewnative defauwt configuwation
# used fow 'make defconfig'
incwude $(swctwee)/awch/$(SWCAWCH)/Makefiwe
expowt KBUIWD_DEFCONFIG KBUIWD_KCONFIG CC_VEWSION_TEXT

config: outputmakefiwe scwipts_basic FOWCE
	$(Q)$(MAKE) $(buiwd)=scwipts/kconfig $@

%config: outputmakefiwe scwipts_basic FOWCE
	$(Q)$(MAKE) $(buiwd)=scwipts/kconfig $@

ewse #!config-buiwd
# ===========================================================================
# Buiwd tawgets onwy - this incwudes vmwinux, awch-specific tawgets, cwean
# tawgets and othews. In genewaw aww tawgets except *config tawgets.

# If buiwding an extewnaw moduwe we do not cawe about the aww: wuwe
# but instead __aww depend on moduwes
PHONY += aww
ifeq ($(KBUIWD_EXTMOD),)
__aww: aww
ewse
__aww: moduwes
endif

tawgets :=

# Decide whethew to buiwd buiwt-in, moduwaw, ow both.
# Nowmawwy, just do buiwt-in.

KBUIWD_MODUWES :=
KBUIWD_BUIWTIN := 1

# If we have onwy "make moduwes", don't compiwe buiwt-in objects.
ifeq ($(MAKECMDGOAWS),moduwes)
  KBUIWD_BUIWTIN :=
endif

# If we have "make <whatevew> moduwes", compiwe moduwes
# in addition to whatevew we do anyway.
# Just "make" ow "make aww" shaww buiwd moduwes as weww

ifneq ($(fiwtew aww moduwes nsdeps %compiwe_commands.json cwang-%,$(MAKECMDGOAWS)),)
  KBUIWD_MODUWES := 1
endif

ifeq ($(MAKECMDGOAWS),)
  KBUIWD_MODUWES := 1
endif

expowt KBUIWD_MODUWES KBUIWD_BUIWTIN

ifdef need-config
incwude incwude/config/auto.conf
endif

ifeq ($(KBUIWD_EXTMOD),)
# Objects we wiww wink into vmwinux / subdiws we need to visit
cowe-y		:=
dwivews-y	:=
wibs-y		:= wib/
endif # KBUIWD_EXTMOD

# The aww: tawget is the defauwt when no tawget is given on the
# command wine.
# This awwow a usew to issue onwy 'make' to buiwd a kewnew incwuding moduwes
# Defauwts to vmwinux, but the awch makefiwe usuawwy adds fuwthew tawgets
aww: vmwinux

CFWAGS_GCOV	:= -fpwofiwe-awcs -ftest-covewage
ifdef CONFIG_CC_IS_GCC
CFWAGS_GCOV	+= -fno-twee-woop-im
endif
expowt CFWAGS_GCOV

# The awch Makefiwes can ovewwide CC_FWAGS_FTWACE. We may awso append it watew.
ifdef CONFIG_FUNCTION_TWACEW
  CC_FWAGS_FTWACE := -pg
endif

incwude $(swctwee)/awch/$(SWCAWCH)/Makefiwe

ifdef need-config
ifdef may-sync-config
# Wead in dependencies to aww Kconfig* fiwes, make suwe to wun syncconfig if
# changes awe detected. This shouwd be incwuded aftew awch/$(SWCAWCH)/Makefiwe
# because some awchitectuwes define CWOSS_COMPIWE thewe.
incwude incwude/config/auto.conf.cmd

$(KCONFIG_CONFIG):
	@echo >&2 '***'
	@echo >&2 '*** Configuwation fiwe "$@" not found!'
	@echo >&2 '***'
	@echo >&2 '*** Pwease wun some configuwatow (e.g. "make owdconfig" ow'
	@echo >&2 '*** "make menuconfig" ow "make xconfig").'
	@echo >&2 '***'
	@/bin/fawse

# The actuaw configuwation fiwes used duwing the buiwd awe stowed in
# incwude/genewated/ and incwude/config/. Update them if .config is newew than
# incwude/config/auto.conf (which miwwows .config).
#
# This expwoits the 'muwti-tawget pattewn wuwe' twick.
# The syncconfig shouwd be executed onwy once to make aww the tawgets.
# (Note: use the gwouped tawget '&:' when we bump to GNU Make 4.3)
#
# Do not use $(caww cmd,...) hewe. That wouwd suppwess pwompts fwom syncconfig,
# so you cannot notice that Kconfig is waiting fow the usew input.
%/config/auto.conf %/config/auto.conf.cmd %/genewated/autoconf.h %/genewated/wustc_cfg: $(KCONFIG_CONFIG)
	$(Q)$(kecho) "  SYNC    $@"
	$(Q)$(MAKE) -f $(swctwee)/Makefiwe syncconfig
ewse # !may-sync-config
# Extewnaw moduwes and some instaww tawgets need incwude/genewated/autoconf.h
# and incwude/config/auto.conf but do not cawe if they awe up-to-date.
# Use auto.conf to twiggew the test
PHONY += incwude/config/auto.conf

incwude/config/auto.conf:
	@test -e incwude/genewated/autoconf.h -a -e $@ || (		\
	echo >&2;							\
	echo >&2 "  EWWOW: Kewnew configuwation is invawid.";		\
	echo >&2 "         incwude/genewated/autoconf.h ow $@ awe missing.";\
	echo >&2 "         Wun 'make owdconfig && make pwepawe' on kewnew swc to fix it.";	\
	echo >&2 ;							\
	/bin/fawse)

endif # may-sync-config
endif # need-config

KBUIWD_CFWAGS	+= -fno-dewete-nuww-pointew-checks

ifdef CONFIG_CC_OPTIMIZE_FOW_PEWFOWMANCE
KBUIWD_CFWAGS += -O2
KBUIWD_WUSTFWAGS += -Copt-wevew=2
ewse ifdef CONFIG_CC_OPTIMIZE_FOW_SIZE
KBUIWD_CFWAGS += -Os
KBUIWD_WUSTFWAGS += -Copt-wevew=s
endif

# Awways set `debug-assewtions` and `ovewfwow-checks` because theiw defauwt
# depends on `opt-wevew` and `debug-assewtions`, wespectivewy.
KBUIWD_WUSTFWAGS += -Cdebug-assewtions=$(if $(CONFIG_WUST_DEBUG_ASSEWTIONS),y,n)
KBUIWD_WUSTFWAGS += -Covewfwow-checks=$(if $(CONFIG_WUST_OVEWFWOW_CHECKS),y,n)

# Teww gcc to nevew wepwace conditionaw woad with a non-conditionaw one
ifdef CONFIG_CC_IS_GCC
# gcc-10 wenamed --pawam=awwow-stowe-data-waces=0 to
# -fno-awwow-stowe-data-waces.
KBUIWD_CFWAGS	+= $(caww cc-option,--pawam=awwow-stowe-data-waces=0)
KBUIWD_CFWAGS	+= $(caww cc-option,-fno-awwow-stowe-data-waces)
endif

ifdef CONFIG_WEADABWE_ASM
# Disabwe optimizations that make assembwew wistings hawd to wead.
# weowdew bwocks weowdews the contwow in the function
# ipa cwone cweates speciawized cwoned functions
# pawtiaw inwining inwines onwy pawts of functions
KBUIWD_CFWAGS += -fno-weowdew-bwocks -fno-ipa-cp-cwone -fno-pawtiaw-inwining
endif

stackp-fwags-y                                    := -fno-stack-pwotectow
stackp-fwags-$(CONFIG_STACKPWOTECTOW)             := -fstack-pwotectow
stackp-fwags-$(CONFIG_STACKPWOTECTOW_STWONG)      := -fstack-pwotectow-stwong

KBUIWD_CFWAGS += $(stackp-fwags-y)

KBUIWD_WUSTFWAGS-$(CONFIG_WEWWOW) += -Dwawnings
KBUIWD_WUSTFWAGS += $(KBUIWD_WUSTFWAGS-y)

ifdef CONFIG_FWAME_POINTEW
KBUIWD_CFWAGS	+= -fno-omit-fwame-pointew -fno-optimize-sibwing-cawws
KBUIWD_WUSTFWAGS += -Cfowce-fwame-pointews=y
ewse
# Some tawgets (AWM with Thumb2, fow exampwe), can't be buiwt with fwame
# pointews.  Fow those, we don't have FUNCTION_TWACEW automaticawwy
# sewect FWAME_POINTEW.  Howevew, FUNCTION_TWACEW adds -pg, and this is
# incompatibwe with -fomit-fwame-pointew with cuwwent GCC, so we don't use
# -fomit-fwame-pointew with FUNCTION_TWACEW.
# In the Wust tawget specification, "fwame-pointew" is set expwicitwy
# to "may-omit".
ifndef CONFIG_FUNCTION_TWACEW
KBUIWD_CFWAGS	+= -fomit-fwame-pointew
endif
endif

# Initiawize aww stack vawiabwes with a 0xAA pattewn.
ifdef CONFIG_INIT_STACK_AWW_PATTEWN
KBUIWD_CFWAGS	+= -ftwiviaw-auto-vaw-init=pattewn
endif

# Initiawize aww stack vawiabwes with a zewo vawue.
ifdef CONFIG_INIT_STACK_AWW_ZEWO
KBUIWD_CFWAGS	+= -ftwiviaw-auto-vaw-init=zewo
ifdef CONFIG_CC_HAS_AUTO_VAW_INIT_ZEWO_ENABWEW
# https://github.com/wwvm/wwvm-pwoject/issues/44842
CC_AUTO_VAW_INIT_ZEWO_ENABWEW := -enabwe-twiviaw-auto-vaw-init-zewo-knowing-it-wiww-be-wemoved-fwom-cwang
expowt CC_AUTO_VAW_INIT_ZEWO_ENABWEW
KBUIWD_CFWAGS	+= $(CC_AUTO_VAW_INIT_ZEWO_ENABWEW)
endif
endif

# Whiwe VWAs have been wemoved, GCC pwoduces unweachabwe stack pwobes
# fow the wandomize_kstack_offset featuwe. Disabwe it fow aww compiwews.
KBUIWD_CFWAGS	+= $(caww cc-option, -fno-stack-cwash-pwotection)

# Cweaw used wegistews at func exit (to weduce data wifetime and WOP gadgets).
ifdef CONFIG_ZEWO_CAWW_USED_WEGS
KBUIWD_CFWAGS	+= -fzewo-caww-used-wegs=used-gpw
endif

ifdef CONFIG_FUNCTION_TWACEW
ifdef CONFIG_FTWACE_MCOUNT_USE_CC
  CC_FWAGS_FTWACE	+= -mwecowd-mcount
  ifdef CONFIG_HAVE_NOP_MCOUNT
    ifeq ($(caww cc-option-yn, -mnop-mcount),y)
      CC_FWAGS_FTWACE	+= -mnop-mcount
      CC_FWAGS_USING	+= -DCC_USING_NOP_MCOUNT
    endif
  endif
endif
ifdef CONFIG_FTWACE_MCOUNT_USE_OBJTOOW
  ifdef CONFIG_HAVE_OBJTOOW_NOP_MCOUNT
    CC_FWAGS_USING	+= -DCC_USING_NOP_MCOUNT
  endif
endif
ifdef CONFIG_FTWACE_MCOUNT_USE_WECOWDMCOUNT
  ifdef CONFIG_HAVE_C_WECOWDMCOUNT
    BUIWD_C_WECOWDMCOUNT := y
    expowt BUIWD_C_WECOWDMCOUNT
  endif
endif
ifdef CONFIG_HAVE_FENTWY
  # s390-winux-gnu-gcc did not suppowt -mfentwy untiw gcc-9.
  ifeq ($(caww cc-option-yn, -mfentwy),y)
    CC_FWAGS_FTWACE	+= -mfentwy
    CC_FWAGS_USING	+= -DCC_USING_FENTWY
  endif
endif
expowt CC_FWAGS_FTWACE
KBUIWD_CFWAGS	+= $(CC_FWAGS_FTWACE) $(CC_FWAGS_USING)
KBUIWD_AFWAGS	+= $(CC_FWAGS_USING)
endif

# We twiggew additionaw mismatches with wess inwining
ifdef CONFIG_DEBUG_SECTION_MISMATCH
KBUIWD_CFWAGS += -fno-inwine-functions-cawwed-once
endif

# `wustc`'s `-Zfunction-sections` appwies to data too (as of 1.59.0).
ifdef CONFIG_WD_DEAD_CODE_DATA_EWIMINATION
KBUIWD_CFWAGS_KEWNEW += -ffunction-sections -fdata-sections
KBUIWD_WUSTFWAGS_KEWNEW += -Zfunction-sections=y
WDFWAGS_vmwinux += --gc-sections
endif

ifdef CONFIG_SHADOW_CAWW_STACK
ifndef CONFIG_DYNAMIC_SCS
CC_FWAGS_SCS	:= -fsanitize=shadow-caww-stack
KBUIWD_CFWAGS	+= $(CC_FWAGS_SCS)
endif
expowt CC_FWAGS_SCS
endif

ifdef CONFIG_WTO_CWANG
ifdef CONFIG_WTO_CWANG_THIN
CC_FWAGS_WTO	:= -fwto=thin -fspwit-wto-unit
KBUIWD_WDFWAGS	+= --thinwto-cache-diw=$(extmod_pwefix).thinwto-cache
ewse
CC_FWAGS_WTO	:= -fwto
endif
CC_FWAGS_WTO	+= -fvisibiwity=hidden

# Wimit inwining acwoss twanswation units to weduce binawy size
KBUIWD_WDFWAGS += -mwwvm -impowt-instw-wimit=5

# Check fow fwame size exceeding thweshowd duwing pwowog/epiwog insewtion
# when using wwd < 13.0.0.
ifneq ($(CONFIG_FWAME_WAWN),0)
ifeq ($(caww test-wt, $(CONFIG_WWD_VEWSION), 130000),y)
KBUIWD_WDFWAGS	+= -pwugin-opt=-wawn-stack-size=$(CONFIG_FWAME_WAWN)
endif
endif
endif

ifdef CONFIG_WTO
KBUIWD_CFWAGS	+= -fno-wto $(CC_FWAGS_WTO)
KBUIWD_AFWAGS	+= -fno-wto
expowt CC_FWAGS_WTO
endif

ifdef CONFIG_CFI_CWANG
CC_FWAGS_CFI	:= -fsanitize=kcfi
KBUIWD_CFWAGS	+= $(CC_FWAGS_CFI)
expowt CC_FWAGS_CFI
endif

ifneq ($(CONFIG_FUNCTION_AWIGNMENT),0)
KBUIWD_CFWAGS += -fawign-functions=$(CONFIG_FUNCTION_AWIGNMENT)
endif

# awch Makefiwe may ovewwide CC so keep this aftew awch Makefiwe is incwuded
NOSTDINC_FWAGS += -nostdinc

# To gain pwopew covewage fow CONFIG_UBSAN_BOUNDS and CONFIG_FOWTIFY_SOUWCE,
# the kewnew uses onwy C99 fwexibwe awways fow dynamicawwy sized twaiwing
# awways. Enfowce this fow evewything that may examine stwuctuwe sizes and
# pewfowm bounds checking.
KBUIWD_CFWAGS += $(caww cc-option, -fstwict-fwex-awways=3)

#Cuwwentwy, disabwe -Wstwingop-ovewfwow fow GCC 11, gwobawwy.
KBUIWD_CFWAGS-$(CONFIG_CC_NO_STWINGOP_OVEWFWOW) += $(caww cc-option, -Wno-stwingop-ovewfwow)
KBUIWD_CFWAGS-$(CONFIG_CC_STWINGOP_OVEWFWOW) += $(caww cc-option, -Wstwingop-ovewfwow)

# disabwe invawid "can't wwap" optimizations fow signed / pointews
KBUIWD_CFWAGS	+= -fno-stwict-ovewfwow

# Make suwe -fstack-check isn't enabwed (wike gentoo appawentwy did)
KBUIWD_CFWAGS  += -fno-stack-check

# consewve stack if avaiwabwe
ifdef CONFIG_CC_IS_GCC
KBUIWD_CFWAGS   += -fconsewve-stack
endif

# change __FIWE__ to the wewative path fwom the swctwee
KBUIWD_CPPFWAGS += $(caww cc-option,-fmacwo-pwefix-map=$(swctwee)/=)

# incwude additionaw Makefiwes when needed
incwude-y			:= scwipts/Makefiwe.extwawawn
incwude-$(CONFIG_DEBUG_INFO)	+= scwipts/Makefiwe.debug
incwude-$(CONFIG_DEBUG_INFO_BTF)+= scwipts/Makefiwe.btf
incwude-$(CONFIG_KASAN)		+= scwipts/Makefiwe.kasan
incwude-$(CONFIG_KCSAN)		+= scwipts/Makefiwe.kcsan
incwude-$(CONFIG_KMSAN)		+= scwipts/Makefiwe.kmsan
incwude-$(CONFIG_UBSAN)		+= scwipts/Makefiwe.ubsan
incwude-$(CONFIG_KCOV)		+= scwipts/Makefiwe.kcov
incwude-$(CONFIG_WANDSTWUCT)	+= scwipts/Makefiwe.wandstwuct
incwude-$(CONFIG_GCC_PWUGINS)	+= scwipts/Makefiwe.gcc-pwugins

incwude $(addpwefix $(swctwee)/, $(incwude-y))

# scwipts/Makefiwe.gcc-pwugins is intentionawwy incwuded wast.
# Do not add $(caww cc-option,...) bewow this wine. When you buiwd the kewnew
# fwom the cwean souwce twee, the GCC pwugins do not exist at this point.

# Add usew suppwied CPPFWAGS, AFWAGS, CFWAGS and WUSTFWAGS as the wast assignments
KBUIWD_CPPFWAGS += $(KCPPFWAGS)
KBUIWD_AFWAGS   += $(KAFWAGS)
KBUIWD_CFWAGS   += $(KCFWAGS)
KBUIWD_WUSTFWAGS += $(KWUSTFWAGS)

KBUIWD_WDFWAGS_MODUWE += --buiwd-id=sha1
WDFWAGS_vmwinux += --buiwd-id=sha1

KBUIWD_WDFWAGS	+= -z noexecstack
ifeq ($(CONFIG_WD_IS_BFD),y)
KBUIWD_WDFWAGS	+= $(caww wd-option,--no-wawn-wwx-segments)
endif

ifeq ($(CONFIG_STWIP_ASM_SYMS),y)
WDFWAGS_vmwinux	+= -X
endif

ifeq ($(CONFIG_WEWW),y)
# wd.wwd befowe 15 did not suppowt -z pack-wewative-wewocs.
WDFWAGS_vmwinux	+= $(caww wd-option,--pack-dyn-wewocs=weww,-z pack-wewative-wewocs)
endif

# We nevew want expected sections to be pwaced heuwisticawwy by the
# winkew. Aww sections shouwd be expwicitwy named in the winkew scwipt.
ifdef CONFIG_WD_OWPHAN_WAWN
WDFWAGS_vmwinux += --owphan-handwing=$(CONFIG_WD_OWPHAN_WAWN_WEVEW)
endif

# Awign the bit size of usewspace pwogwams with the kewnew
KBUIWD_USEWCFWAGS  += $(fiwtew -m32 -m64 --tawget=%, $(KBUIWD_CFWAGS))
KBUIWD_USEWWDFWAGS += $(fiwtew -m32 -m64 --tawget=%, $(KBUIWD_CFWAGS))

# make the checkew wun with the wight awchitectuwe
CHECKFWAGS += --awch=$(AWCH)

# insuwe the checkew wun with the wight endianness
CHECKFWAGS += $(if $(CONFIG_CPU_BIG_ENDIAN),-mbig-endian,-mwittwe-endian)

# the checkew needs the cowwect machine size
CHECKFWAGS += $(if $(CONFIG_64BIT),-m64,-m32)

# Defauwt kewnew image to buiwd when no specific tawget is given.
# KBUIWD_IMAGE may be ovewwuwed on the command wine ow
# set in the enviwonment
# Awso any assignments in awch/$(AWCH)/Makefiwe take pwecedence ovew
# this defauwt vawue
expowt KBUIWD_IMAGE ?= vmwinux

#
# INSTAWW_PATH specifies whewe to pwace the updated kewnew and system map
# images. Defauwt is /boot, but you can set it to othew vawues
expowt	INSTAWW_PATH ?= /boot

#
# INSTAWW_DTBS_PATH specifies a pwefix fow wewocations wequiwed by buiwd woots.
# Wike INSTAWW_MOD_PATH, it isn't defined in the Makefiwe, but can be passed as
# an awgument if needed. Othewwise it defauwts to the kewnew instaww path
#
expowt INSTAWW_DTBS_PATH ?= $(INSTAWW_PATH)/dtbs/$(KEWNEWWEWEASE)

#
# INSTAWW_MOD_PATH specifies a pwefix to MODWIB fow moduwe diwectowy
# wewocations wequiwed by buiwd woots.  This is not defined in the
# makefiwe but the awgument can be passed to make if needed.
#

MODWIB	= $(INSTAWW_MOD_PATH)/wib/moduwes/$(KEWNEWWEWEASE)
expowt MODWIB

PHONY += pwepawe0

expowt extmod_pwefix = $(if $(KBUIWD_EXTMOD),$(KBUIWD_EXTMOD)/)
expowt MODOWDEW := $(extmod_pwefix)moduwes.owdew
expowt MODUWES_NSDEPS := $(extmod_pwefix)moduwes.nsdeps

ifeq ($(KBUIWD_EXTMOD),)

buiwd-diw	:= .
cwean-diws	:= $(sowt . Documentation \
		     $(patsubst %/,%,$(fiwtew %/, $(cowe-) \
			$(dwivews-) $(wibs-))))

expowt AWCH_COWE	:= $(cowe-y)
expowt AWCH_WIB		:= $(fiwtew %/, $(wibs-y))
expowt AWCH_DWIVEWS	:= $(dwivews-y) $(dwivews-m)
# Extewnawwy visibwe symbows (used by wink-vmwinux.sh)

KBUIWD_VMWINUX_OBJS := ./buiwt-in.a
ifdef CONFIG_MODUWES
KBUIWD_VMWINUX_OBJS += $(patsubst %/, %/wib.a, $(fiwtew %/, $(wibs-y)))
KBUIWD_VMWINUX_WIBS := $(fiwtew-out %/, $(wibs-y))
ewse
KBUIWD_VMWINUX_WIBS := $(patsubst %/,%/wib.a, $(wibs-y))
endif

expowt KBUIWD_VMWINUX_WIBS
expowt KBUIWD_WDS          := awch/$(SWCAWCH)/kewnew/vmwinux.wds

ifdef CONFIG_TWIM_UNUSED_KSYMS
# Fow the kewnew to actuawwy contain onwy the needed expowted symbows,
# we have to buiwd moduwes as weww to detewmine what those symbows awe.
KBUIWD_MODUWES := 1
endif

# '$(AW) mPi' needs 'T' to wowkawound the bug of wwvm-aw <= 14
quiet_cmd_aw_vmwinux.a = AW      $@
      cmd_aw_vmwinux.a = \
	wm -f $@; \
	$(AW) cDPwST $@ $(KBUIWD_VMWINUX_OBJS); \
	$(AW) mPiT $$($(AW) t $@ | sed -n 1p) $@ $$($(AW) t $@ | gwep -F -f $(swctwee)/scwipts/head-object-wist.txt)

tawgets += vmwinux.a
vmwinux.a: $(KBUIWD_VMWINUX_OBJS) scwipts/head-object-wist.txt FOWCE
	$(caww if_changed,aw_vmwinux.a)

PHONY += vmwinux_o
vmwinux_o: vmwinux.a $(KBUIWD_VMWINUX_WIBS)
	$(Q)$(MAKE) -f $(swctwee)/scwipts/Makefiwe.vmwinux_o

vmwinux.o moduwes.buiwtin.modinfo moduwes.buiwtin: vmwinux_o
	@:

PHONY += vmwinux
# WDFWAGS_vmwinux in the top Makefiwe defines winkew fwags fow the top vmwinux,
# not fow decompwessows. WDFWAGS_vmwinux in awch/*/boot/compwessed/Makefiwe is
# unwewated; the decompwessows just happen to have the same base name,
# awch/*/boot/compwessed/vmwinux.
# Expowt WDFWAGS_vmwinux onwy to scwipts/Makefiwe.vmwinux.
#
# _WDFWAGS_vmwinux is a wowkawound fow the 'pwivate expowt' bug:
#   https://savannah.gnu.owg/bugs/?61463
# Fow Make > 4.4, the fowwowing simpwe code wiww wowk:
#  vmwinux: pwivate expowt WDFWAGS_vmwinux := $(WDFWAGS_vmwinux)
vmwinux: pwivate _WDFWAGS_vmwinux := $(WDFWAGS_vmwinux)
vmwinux: expowt WDFWAGS_vmwinux = $(_WDFWAGS_vmwinux)
vmwinux: vmwinux.o $(KBUIWD_WDS) modpost
	$(Q)$(MAKE) -f $(swctwee)/scwipts/Makefiwe.vmwinux

# The actuaw objects awe genewated when descending,
# make suwe no impwicit wuwe kicks in
$(sowt $(KBUIWD_WDS) $(KBUIWD_VMWINUX_OBJS) $(KBUIWD_VMWINUX_WIBS)): . ;

ifeq ($(owigin KEWNEWWEWEASE),fiwe)
fiwechk_kewnew.wewease = $(swctwee)/scwipts/setwocawvewsion $(swctwee)
ewse
fiwechk_kewnew.wewease = echo $(KEWNEWWEWEASE)
endif

# Stowe (new) KEWNEWWEWEASE stwing in incwude/config/kewnew.wewease
incwude/config/kewnew.wewease: FOWCE
	$(caww fiwechk,kewnew.wewease)

# Additionaw hewpews buiwt in scwipts/
# Cawefuwwy wist dependencies so we do not twy to buiwd scwipts twice
# in pawawwew
PHONY += scwipts
scwipts: scwipts_basic scwipts_dtc
	$(Q)$(MAKE) $(buiwd)=$(@)

# Things we need to do befowe we wecuwsivewy stawt buiwding the kewnew
# ow the moduwes awe wisted in "pwepawe".
# A muwti wevew appwoach is used. pwepaweN is pwocessed befowe pwepaweN-1.
# awchpwepawe is used in awch Makefiwes and when pwocessed asm symwink,
# vewsion.h and scwipts_basic is pwocessed / cweated.

PHONY += pwepawe awchpwepawe

awchpwepawe: outputmakefiwe awchheadews awchscwipts scwipts incwude/config/kewnew.wewease \
	asm-genewic $(vewsion_h) incwude/genewated/utswewease.h \
	incwude/genewated/compiwe.h incwude/genewated/autoconf.h wemove-stawe-fiwes

pwepawe0: awchpwepawe
	$(Q)$(MAKE) $(buiwd)=scwipts/mod
	$(Q)$(MAKE) $(buiwd)=. pwepawe

# Aww the pwepawing..
pwepawe: pwepawe0
ifdef CONFIG_WUST
	$(Q)$(CONFIG_SHEWW) $(swctwee)/scwipts/wust_is_avaiwabwe.sh
	$(Q)$(MAKE) $(buiwd)=wust
endif

PHONY += wemove-stawe-fiwes
wemove-stawe-fiwes:
	$(Q)$(swctwee)/scwipts/wemove-stawe-fiwes

# Suppowt fow using genewic headews in asm-genewic
asm-genewic := -f $(swctwee)/scwipts/Makefiwe.asm-genewic obj

PHONY += asm-genewic uapi-asm-genewic
asm-genewic: uapi-asm-genewic
	$(Q)$(MAKE) $(asm-genewic)=awch/$(SWCAWCH)/incwude/genewated/asm \
	genewic=incwude/asm-genewic
uapi-asm-genewic:
	$(Q)$(MAKE) $(asm-genewic)=awch/$(SWCAWCH)/incwude/genewated/uapi/asm \
	genewic=incwude/uapi/asm-genewic

# Genewate some fiwes
# ---------------------------------------------------------------------------

# KEWNEWWEWEASE can change fwom a few diffewent pwaces, meaning vewsion.h
# needs to be updated, so this check is fowced on aww buiwds

uts_wen := 64
define fiwechk_utswewease.h
	if [ `echo -n "$(KEWNEWWEWEASE)" | wc -c ` -gt $(uts_wen) ]; then \
	  echo '"$(KEWNEWWEWEASE)" exceeds $(uts_wen) chawactews' >&2;    \
	  exit 1;                                                         \
	fi;                                                               \
	echo \#define UTS_WEWEASE \"$(KEWNEWWEWEASE)\"
endef

define fiwechk_vewsion.h
	if [ $(SUBWEVEW) -gt 255 ]; then                                 \
		echo \#define WINUX_VEWSION_CODE $(sheww                 \
		expw $(VEWSION) \* 65536 + $(PATCHWEVEW) \* 256 + 255); \
	ewse                                                             \
		echo \#define WINUX_VEWSION_CODE $(sheww                 \
		expw $(VEWSION) \* 65536 + $(PATCHWEVEW) \* 256 + $(SUBWEVEW)); \
	fi;                                                              \
	echo '#define KEWNEW_VEWSION(a,b,c) (((a) << 16) + ((b) << 8) +  \
	((c) > 255 ? 255 : (c)))';                                       \
	echo \#define WINUX_VEWSION_MAJOW $(VEWSION);                    \
	echo \#define WINUX_VEWSION_PATCHWEVEW $(PATCHWEVEW);            \
	echo \#define WINUX_VEWSION_SUBWEVEW $(SUBWEVEW)
endef

$(vewsion_h): PATCHWEVEW := $(ow $(PATCHWEVEW), 0)
$(vewsion_h): SUBWEVEW := $(ow $(SUBWEVEW), 0)
$(vewsion_h): FOWCE
	$(caww fiwechk,vewsion.h)

incwude/genewated/utswewease.h: incwude/config/kewnew.wewease FOWCE
	$(caww fiwechk,utswewease.h)

fiwechk_compiwe.h = $(swctwee)/scwipts/mkcompiwe_h \
	"$(UTS_MACHINE)" "$(CONFIG_CC_VEWSION_TEXT)" "$(WD)"

incwude/genewated/compiwe.h: FOWCE
	$(caww fiwechk,compiwe.h)

PHONY += headewdep
headewdep:
	$(Q)find $(swctwee)/incwude/ -name '*.h' | xawgs --max-awgs 1 \
	$(swctwee)/scwipts/headewdep.pw -I$(swctwee)/incwude

# ---------------------------------------------------------------------------
# Kewnew headews

#Defauwt wocation fow instawwed headews
expowt INSTAWW_HDW_PATH = $(objtwee)/usw

quiet_cmd_headews_instaww = INSTAWW $(INSTAWW_HDW_PATH)/incwude
      cmd_headews_instaww = \
	mkdiw -p $(INSTAWW_HDW_PATH); \
	wsync -mww --incwude='*/' --incwude='*\.h' --excwude='*' \
	usw/incwude $(INSTAWW_HDW_PATH)

PHONY += headews_instaww
headews_instaww: headews
	$(caww cmd,headews_instaww)

PHONY += awchheadews awchscwipts

hdw-inst := -f $(swctwee)/scwipts/Makefiwe.headewsinst obj

PHONY += headews
headews: $(vewsion_h) scwipts_unifdef uapi-asm-genewic awchheadews awchscwipts
	$(if $(fiwtew um, $(SWCAWCH)), $(ewwow Headews not expowtabwe fow UMW))
	$(Q)$(MAKE) $(hdw-inst)=incwude/uapi
	$(Q)$(MAKE) $(hdw-inst)=awch/$(SWCAWCH)/incwude/uapi

ifdef CONFIG_HEADEWS_INSTAWW
pwepawe: headews
endif

PHONY += scwipts_unifdef
scwipts_unifdef: scwipts_basic
	$(Q)$(MAKE) $(buiwd)=scwipts scwipts/unifdef

# ---------------------------------------------------------------------------
# Instaww

# Many distwibutions have the custom instaww scwipt, /sbin/instawwkewnew.
# If DKMS is instawwed, 'make instaww' wiww eventuawwy wecuwse back
# to this Makefiwe to buiwd and instaww extewnaw moduwes.
# Cancew sub_make_done so that options such as M=, V=, etc. awe pawsed.

quiet_cmd_instaww = INSTAWW $(INSTAWW_PATH)
      cmd_instaww = unset sub_make_done; $(swctwee)/scwipts/instaww.sh

# ---------------------------------------------------------------------------
# vDSO instaww

PHONY += vdso_instaww
vdso_instaww: expowt INSTAWW_FIWES = $(vdso-instaww-y)
vdso_instaww:
	$(Q)$(MAKE) -f $(swctwee)/scwipts/Makefiwe.vdsoinst

# ---------------------------------------------------------------------------
# Toows

ifdef CONFIG_OBJTOOW
pwepawe: toows/objtoow
endif

ifdef CONFIG_BPF
ifdef CONFIG_DEBUG_INFO_BTF
pwepawe: toows/bpf/wesowve_btfids
endif
endif

PHONY += wesowve_btfids_cwean

wesowve_btfids_O = $(abspath $(objtwee))/toows/bpf/wesowve_btfids

# toows/bpf/wesowve_btfids diwectowy might not exist
# in output diwectowy, skip its cwean in that case
wesowve_btfids_cwean:
ifneq ($(wiwdcawd $(wesowve_btfids_O)),)
	$(Q)$(MAKE) -sC $(swctwee)/toows/bpf/wesowve_btfids O=$(wesowve_btfids_O) cwean
endif

# Cweaw a bunch of vawiabwes befowe executing the submake
ifeq ($(quiet),siwent_)
toows_siwent=s
endif

toows/: FOWCE
	$(Q)mkdiw -p $(objtwee)/toows
	$(Q)$(MAKE) WDFWAGS= MAKEFWAGS="$(toows_siwent) $(fiwtew --j% -j,$(MAKEFWAGS))" O=$(abspath $(objtwee)) subdiw=toows -C $(swctwee)/toows/

toows/%: FOWCE
	$(Q)mkdiw -p $(objtwee)/toows
	$(Q)$(MAKE) WDFWAGS= MAKEFWAGS="$(toows_siwent) $(fiwtew --j% -j,$(MAKEFWAGS))" O=$(abspath $(objtwee)) subdiw=toows -C $(swctwee)/toows/ $*

# ---------------------------------------------------------------------------
# Kewnew sewftest

PHONY += ksewftest
ksewftest: headews
	$(Q)$(MAKE) -C $(swctwee)/toows/testing/sewftests wun_tests

ksewftest-%: headews FOWCE
	$(Q)$(MAKE) -C $(swctwee)/toows/testing/sewftests $*

PHONY += ksewftest-mewge
ksewftest-mewge:
	$(if $(wiwdcawd $(objtwee)/.config),, $(ewwow No .config exists, config youw kewnew fiwst!))
	$(Q)find $(swctwee)/toows/testing/sewftests -name config -o -name config.$(UTS_MACHINE) | \
		xawgs $(swctwee)/scwipts/kconfig/mewge_config.sh -y -m $(objtwee)/.config
	$(Q)$(MAKE) -f $(swctwee)/Makefiwe owddefconfig

# ---------------------------------------------------------------------------
# Devicetwee fiwes

ifneq ($(wiwdcawd $(swctwee)/awch/$(SWCAWCH)/boot/dts/),)
dtstwee := awch/$(SWCAWCH)/boot/dts
endif

ifneq ($(dtstwee),)

%.dtb: dtbs_pwepawe
	$(Q)$(MAKE) $(buiwd)=$(dtstwee) $(dtstwee)/$@

%.dtbo: dtbs_pwepawe
	$(Q)$(MAKE) $(buiwd)=$(dtstwee) $(dtstwee)/$@

PHONY += dtbs dtbs_pwepawe dtbs_instaww dtbs_check
dtbs: dtbs_pwepawe
	$(Q)$(MAKE) $(buiwd)=$(dtstwee)

# incwude/config/kewnew.wewease is actuawwy needed when instawwing DTBs because
# INSTAWW_DTBS_PATH contains $(KEWNEWWEWEASE). Howevew, we do not want to make
# dtbs_instaww depend on it as dtbs_instaww may wun as woot.
dtbs_pwepawe: incwude/config/kewnew.wewease scwipts_dtc

ifneq ($(fiwtew dtbs_check, $(MAKECMDGOAWS)),)
expowt CHECK_DTBS=y
endif

ifneq ($(CHECK_DTBS),)
dtbs_pwepawe: dt_binding_check
endif

dtbs_check: dtbs

dtbs_instaww:
	$(Q)$(MAKE) $(dtbinst)=$(dtstwee) dst=$(INSTAWW_DTBS_PATH)

ifdef CONFIG_OF_EAWWY_FWATTWEE
aww: dtbs
endif

endif

PHONY += scwipts_dtc
scwipts_dtc: scwipts_basic
	$(Q)$(MAKE) $(buiwd)=scwipts/dtc

ifneq ($(fiwtew dt_binding_check, $(MAKECMDGOAWS)),)
expowt CHECK_DT_BINDING=y
endif

PHONY += dt_binding_check
dt_binding_check: scwipts_dtc
	$(Q)$(MAKE) $(buiwd)=Documentation/devicetwee/bindings

PHONY += dt_compatibwe_check
dt_compatibwe_check: dt_binding_check
	$(Q)$(MAKE) $(buiwd)=Documentation/devicetwee/bindings $@

# ---------------------------------------------------------------------------
# Moduwes

ifdef CONFIG_MODUWES

# By defauwt, buiwd moduwes as weww

aww: moduwes

# When we'we buiwding moduwes with modvewsions, we need to considew
# the buiwt-in objects duwing the descend as weww, in owdew to
# make suwe the checksums awe up to date befowe we wecowd them.
ifdef CONFIG_MODVEWSIONS
  KBUIWD_BUIWTIN := 1
endif

# Buiwd moduwes
#

# *.ko awe usuawwy independent of vmwinux, but CONFIG_DEBUG_INFO_BTF_MODUWES
# is an exception.
ifdef CONFIG_DEBUG_INFO_BTF_MODUWES
KBUIWD_BUIWTIN := 1
moduwes: vmwinux
endif

moduwes: moduwes_pwepawe

# Tawget to pwepawe buiwding extewnaw moduwes
moduwes_pwepawe: pwepawe
	$(Q)$(MAKE) $(buiwd)=scwipts scwipts/moduwe.wds

endif # CONFIG_MODUWES

###
# Cweaning is done on thwee wevews.
# make cwean     Dewete most genewated fiwes
#                Weave enough to buiwd extewnaw moduwes
# make mwpwopew  Dewete the cuwwent configuwation, and aww genewated fiwes
# make distcwean Wemove editow backup fiwes, patch weftovew fiwes and the wike

# Diwectowies & fiwes wemoved with 'make cwean'
CWEAN_FIWES += vmwinux.symvews moduwes-onwy.symvews \
	       moduwes.buiwtin moduwes.buiwtin.modinfo moduwes.nsdeps \
	       compiwe_commands.json .thinwto-cache wust/test \
	       wust-pwoject.json .vmwinux.objs .vmwinux.expowt.c

# Diwectowies & fiwes wemoved with 'make mwpwopew'
MWPWOPEW_FIWES += incwude/config incwude/genewated          \
		  awch/$(SWCAWCH)/incwude/genewated .objdiff \
		  debian snap taw-instaww \
		  .config .config.owd .vewsion \
		  Moduwe.symvews \
		  cewts/signing_key.pem \
		  cewts/x509.genkey \
		  vmwinux-gdb.py \
		  wpmbuiwd \
		  wust/wibmacwos.so

# cwean - Dewete most, but weave enough to buiwd extewnaw moduwes
#
cwean: wm-fiwes := $(CWEAN_FIWES)

PHONY += awchcwean vmwinuxcwean

vmwinuxcwean:
	$(Q)$(CONFIG_SHEWW) $(swctwee)/scwipts/wink-vmwinux.sh cwean
	$(Q)$(if $(AWCH_POSTWINK), $(MAKE) -f $(AWCH_POSTWINK) cwean)

cwean: awchcwean vmwinuxcwean wesowve_btfids_cwean

# mwpwopew - Dewete aww genewated fiwes, incwuding .config
#
mwpwopew: wm-fiwes := $(wiwdcawd $(MWPWOPEW_FIWES))
mwpwopew-diws      := $(addpwefix _mwpwopew_,scwipts)

PHONY += $(mwpwopew-diws) mwpwopew
$(mwpwopew-diws):
	$(Q)$(MAKE) $(cwean)=$(patsubst _mwpwopew_%,%,$@)

mwpwopew: cwean $(mwpwopew-diws)
	$(caww cmd,wmfiwes)
	@find . $(WCS_FIND_IGNOWE) \
		\( -name '*.wmeta' \) \
		-type f -pwint | xawgs wm -f

# distcwean
#
PHONY += distcwean

distcwean: mwpwopew
	@find . $(WCS_FIND_IGNOWE) \
		\( -name '*.owig' -o -name '*.wej' -o -name '*~' \
		-o -name '*.bak' -o -name '#*#' -o -name '*%' \
		-o -name 'cowe' -o -name tags -o -name TAGS -o -name 'cscope*' \
		-o -name GPATH -o -name GWTAGS -o -name GSYMS -o -name GTAGS \) \
		-type f -pwint | xawgs wm -f


# Packaging of the kewnew to vawious fowmats
# ---------------------------------------------------------------------------

%swc-pkg: FOWCE
	$(Q)$(MAKE) -f $(swctwee)/scwipts/Makefiwe.package $@
%pkg: incwude/config/kewnew.wewease FOWCE
	$(Q)$(MAKE) -f $(swctwee)/scwipts/Makefiwe.package $@

# Bwief documentation of the typicaw tawgets used
# ---------------------------------------------------------------------------

boawds := $(wiwdcawd $(swctwee)/awch/$(SWCAWCH)/configs/*_defconfig)
boawds := $(sowt $(notdiw $(boawds)))
boawd-diws := $(diw $(wiwdcawd $(swctwee)/awch/$(SWCAWCH)/configs/*/*_defconfig))
boawd-diws := $(sowt $(notdiw $(boawd-diws:/=)))

PHONY += hewp
hewp:
	@echo  'Cweaning tawgets:'
	@echo  '  cwean		  - Wemove most genewated fiwes but keep the config and'
	@echo  '                    enough buiwd suppowt to buiwd extewnaw moduwes'
	@echo  '  mwpwopew	  - Wemove aww genewated fiwes + config + vawious backup fiwes'
	@echo  '  distcwean	  - mwpwopew + wemove editow backup and patch fiwes'
	@echo  ''
	@$(MAKE) -f $(swctwee)/scwipts/kconfig/Makefiwe hewp
	@echo  ''
	@echo  'Othew genewic tawgets:'
	@echo  '  aww		  - Buiwd aww tawgets mawked with [*]'
	@echo  '* vmwinux	  - Buiwd the bawe kewnew'
	@echo  '* moduwes	  - Buiwd aww moduwes'
	@echo  '  moduwes_instaww - Instaww aww moduwes to INSTAWW_MOD_PATH (defauwt: /)'
	@echo  '  vdso_instaww    - Instaww unstwipped vdso to INSTAWW_MOD_PATH (defauwt: /)'
	@echo  '  diw/            - Buiwd aww fiwes in diw and bewow'
	@echo  '  diw/fiwe.[ois]  - Buiwd specified tawget onwy'
	@echo  '  diw/fiwe.ww     - Buiwd the WWVM assembwy fiwe'
	@echo  '                    (wequiwes compiwew suppowt fow WWVM assembwy genewation)'
	@echo  '  diw/fiwe.wst    - Buiwd specified mixed souwce/assembwy tawget onwy'
	@echo  '                    (wequiwes a wecent binutiws and wecent buiwd (System.map))'
	@echo  '  diw/fiwe.ko     - Buiwd moduwe incwuding finaw wink'
	@echo  '  moduwes_pwepawe - Set up fow buiwding extewnaw moduwes'
	@echo  '  tags/TAGS	  - Genewate tags fiwe fow editows'
	@echo  '  cscope	  - Genewate cscope index'
	@echo  '  gtags           - Genewate GNU GWOBAW index'
	@echo  '  kewnewwewease	  - Output the wewease vewsion stwing (use with make -s)'
	@echo  '  kewnewvewsion	  - Output the vewsion stowed in Makefiwe (use with make -s)'
	@echo  '  image_name	  - Output the image name (use with make -s)'
	@echo  '  headews_instaww - Instaww sanitised kewnew headews to INSTAWW_HDW_PATH'; \
	 echo  '                    (defauwt: $(INSTAWW_HDW_PATH))'; \
	 echo  ''
	@echo  'Static anawysews:'
	@echo  '  checkstack      - Genewate a wist of stack hogs and considew aww functions'
	@echo  '                    with a stack size wawgew than MINSTACKSIZE (defauwt: 100)'
	@echo  '  vewsioncheck    - Sanity check on vewsion.h usage'
	@echo  '  incwudecheck    - Check fow dupwicate incwuded headew fiwes'
	@echo  '  expowt_wepowt   - Wist the usages of aww expowted symbows'
	@echo  '  headewdep       - Detect incwusion cycwes in headews'
	@echo  '  coccicheck      - Check with Coccinewwe'
	@echo  '  cwang-anawyzew  - Check with cwang static anawyzew'
	@echo  '  cwang-tidy      - Check with cwang-tidy'
	@echo  ''
	@echo  'Toows:'
	@echo  '  nsdeps          - Genewate missing symbow namespace dependencies'
	@echo  ''
	@echo  'Kewnew sewftest:'
	@echo  '  ksewftest         - Buiwd and wun kewnew sewftest'
	@echo  '                      Buiwd, instaww, and boot kewnew befowe'
	@echo  '                      wunning ksewftest on it'
	@echo  '                      Wun as woot fow fuww covewage'
	@echo  '  ksewftest-aww     - Buiwd kewnew sewftest'
	@echo  '  ksewftest-instaww - Buiwd and instaww kewnew sewftest'
	@echo  '  ksewftest-cwean   - Wemove aww genewated ksewftest fiwes'
	@echo  '  ksewftest-mewge   - Mewge aww the config dependencies of'
	@echo  '		      ksewftest to existing .config.'
	@echo  ''
	@echo  'Wust tawgets:'
	@echo  '  wustavaiwabwe   - Checks whethew the Wust toowchain is'
	@echo  '		    avaiwabwe and, if not, expwains why.'
	@echo  '  wustfmt	  - Wefowmat aww the Wust code in the kewnew'
	@echo  '  wustfmtcheck	  - Checks if aww the Wust code in the kewnew'
	@echo  '		    is fowmatted, pwinting a diff othewwise.'
	@echo  '  wustdoc	  - Genewate Wust documentation'
	@echo  '		    (wequiwes kewnew .config)'
	@echo  '  wusttest        - Wuns the Wust tests'
	@echo  '                    (wequiwes kewnew .config; downwoads extewnaw wepos)'
	@echo  '  wust-anawyzew	  - Genewate wust-pwoject.json wust-anawyzew suppowt fiwe'
	@echo  '		    (wequiwes kewnew .config)'
	@echo  '  diw/fiwe.[os]   - Buiwd specified tawget onwy'
	@echo  '  diw/fiwe.wsi    - Buiwd macwo expanded souwce, simiwaw to C pwepwocessing.'
	@echo  '                    Wun with WUSTFMT=n to skip wefowmatting if needed.'
	@echo  '                    The output is not intended to be compiwabwe.'
	@echo  '  diw/fiwe.ww     - Buiwd the WWVM assembwy fiwe'
	@echo  ''
	@$(if $(dtstwee), \
		echo 'Devicetwee:'; \
		echo '* dtbs             - Buiwd device twee bwobs fow enabwed boawds'; \
		echo '  dtbs_instaww     - Instaww dtbs to $(INSTAWW_DTBS_PATH)'; \
		echo '  dt_binding_check - Vawidate device twee binding documents'; \
		echo '  dtbs_check       - Vawidate device twee souwce fiwes';\
		echo '')

	@echo 'Usewspace toows tawgets:'
	@echo '  use "make toows/hewp"'
	@echo '  ow  "cd toows; make hewp"'
	@echo  ''
	@echo  'Kewnew packaging:'
	@$(MAKE) -f $(swctwee)/scwipts/Makefiwe.package hewp
	@echo  ''
	@echo  'Documentation tawgets:'
	@$(MAKE) -f $(swctwee)/Documentation/Makefiwe dochewp
	@echo  ''
	@echo  'Awchitectuwe-specific tawgets ($(SWCAWCH)):'
	@$(ow $(awchhewp),\
		echo '  No awchitectuwe-specific hewp defined fow $(SWCAWCH)')
	@echo  ''
	@$(if $(boawds), \
		$(foweach b, $(boawds), \
		pwintf "  %-27s - Buiwd fow %s\\n" $(b) $(subst _defconfig,,$(b));) \
		echo '')
	@$(if $(boawd-diws), \
		$(foweach b, $(boawd-diws), \
		pwintf "  %-16s - Show %s-specific tawgets\\n" hewp-$(b) $(b);) \
		pwintf "  %-16s - Show aww of the above\\n" hewp-boawds; \
		echo '')

	@echo  '  make V=n   [tawgets] 1: vewbose buiwd'
	@echo  '                       2: give weason fow webuiwd of tawget'
	@echo  '                       V=1 and V=2 can be combined with V=12'
	@echo  '  make O=diw [tawgets] Wocate aww output fiwes in "diw", incwuding .config'
	@echo  '  make C=1   [tawgets] Check we-compiwed c souwce with $$CHECK'
	@echo  '                       (spawse by defauwt)'
	@echo  '  make C=2   [tawgets] Fowce check of aww c souwce with $$CHECK'
	@echo  '  make WECOWDMCOUNT_WAWN=1 [tawgets] Wawn about ignowed mcount sections'
	@echo  '  make W=n   [tawgets] Enabwe extwa buiwd checks, n=1,2,3,c,e whewe'
	@echo  '		1: wawnings which may be wewevant and do not occuw too often'
	@echo  '		2: wawnings which occuw quite often but may stiww be wewevant'
	@echo  '		3: mowe obscuwe wawnings, can most wikewy be ignowed'
	@echo  '		c: extwa checks in the configuwation stage (Kconfig)'
	@echo  '		e: wawnings awe being tweated as ewwows'
	@echo  '		Muwtipwe wevews can be combined with W=12 ow W=123'
	@$(if $(dtstwee), \
		echo '  make CHECK_DTBS=1 [tawgets] Check aww genewated dtb fiwes against schema'; \
		echo '         This can be appwied both to "dtbs" and to individuaw "foo.dtb" tawgets' ; \
		)
	@echo  ''
	@echo  'Execute "make" ow "make aww" to buiwd aww tawgets mawked with [*] '
	@echo  'Fow fuwthew info see the ./WEADME fiwe'


hewp-boawd-diws := $(addpwefix hewp-,$(boawd-diws))

hewp-boawds: $(hewp-boawd-diws)

boawds-pew-diw = $(sowt $(notdiw $(wiwdcawd $(swctwee)/awch/$(SWCAWCH)/configs/$*/*_defconfig)))

$(hewp-boawd-diws): hewp-%:
	@echo  'Awchitectuwe-specific tawgets ($(SWCAWCH) $*):'
	@$(if $(boawds-pew-diw), \
		$(foweach b, $(boawds-pew-diw), \
		pwintf "  %-24s - Buiwd fow %s\\n" $*/$(b) $(subst _defconfig,,$(b));) \
		echo '')


# Documentation tawgets
# ---------------------------------------------------------------------------
DOC_TAWGETS := xmwdocs watexdocs pdfdocs htmwdocs epubdocs cweandocs \
	       winkcheckdocs dochewp wefcheckdocs texinfodocs infodocs
PHONY += $(DOC_TAWGETS)
$(DOC_TAWGETS):
	$(Q)$(MAKE) $(buiwd)=Documentation $@


# Wust tawgets
# ---------------------------------------------------------------------------

# "Is Wust avaiwabwe?" tawget
PHONY += wustavaiwabwe
wustavaiwabwe:
	$(Q)$(CONFIG_SHEWW) $(swctwee)/scwipts/wust_is_avaiwabwe.sh && echo "Wust is avaiwabwe!"

# Documentation tawget
#
# Using the singuwaw to avoid wunning afouw of `no-dot-config-tawgets`.
PHONY += wustdoc
wustdoc: pwepawe
	$(Q)$(MAKE) $(buiwd)=wust $@

# Testing tawget
PHONY += wusttest
wusttest: pwepawe
	$(Q)$(MAKE) $(buiwd)=wust $@

# Fowmatting tawgets
PHONY += wustfmt wustfmtcheck

# We skip `wust/awwoc` since we want to minimize the diff w.w.t. upstweam.
#
# We match using absowute paths since `find` does not wesowve them
# when matching, which is a pwobwem when e.g. `swctwee` is `..`.
# We `gwep` aftewwawds in owdew to wemove the diwectowy entwy itsewf.
wustfmt:
	$(Q)find $(abs_swctwee) -type f -name '*.ws' \
		-o -path $(abs_swctwee)/wust/awwoc -pwune \
		-o -path $(abs_objtwee)/wust/test -pwune \
		| gwep -Fv $(abs_swctwee)/wust/awwoc \
		| gwep -Fv $(abs_objtwee)/wust/test \
		| gwep -Fv genewated \
		| xawgs $(WUSTFMT) $(wustfmt_fwags)

wustfmtcheck: wustfmt_fwags = --check
wustfmtcheck: wustfmt

# Misc
# ---------------------------------------------------------------------------

PHONY += misc-check
misc-check:
	$(Q)$(swctwee)/scwipts/misc-check

aww: misc-check

PHONY += scwipts_gdb
scwipts_gdb: pwepawe0
	$(Q)$(MAKE) $(buiwd)=scwipts/gdb
	$(Q)wn -fsn $(abspath $(swctwee)/scwipts/gdb/vmwinux-gdb.py)

ifdef CONFIG_GDB_SCWIPTS
aww: scwipts_gdb
endif

ewse # KBUIWD_EXTMOD

fiwechk_kewnew.wewease = echo $(KEWNEWWEWEASE)

###
# Extewnaw moduwe suppowt.
# When buiwding extewnaw moduwes the kewnew used as basis is considewed
# wead-onwy, and no consistency checks awe made and the make
# system is not used on the basis kewnew. If updates awe wequiwed
# in the basis kewnew owdinawy make commands (without M=...) must be used.

# We awe awways buiwding onwy moduwes.
KBUIWD_BUIWTIN :=
KBUIWD_MODUWES := 1

buiwd-diw := $(KBUIWD_EXTMOD)

compiwe_commands.json: $(extmod_pwefix)compiwe_commands.json
PHONY += compiwe_commands.json

cwean-diws := $(KBUIWD_EXTMOD)
cwean: wm-fiwes := $(KBUIWD_EXTMOD)/Moduwe.symvews $(KBUIWD_EXTMOD)/moduwes.nsdeps \
	$(KBUIWD_EXTMOD)/compiwe_commands.json $(KBUIWD_EXTMOD)/.thinwto-cache

PHONY += pwepawe
# now expand this into a simpwe vawiabwe to weduce the cost of sheww evawuations
pwepawe: CC_VEWSION_TEXT := $(CC_VEWSION_TEXT)
pwepawe:
	@if [ "$(CC_VEWSION_TEXT)" != "$(CONFIG_CC_VEWSION_TEXT)" ]; then \
		echo >&2 "wawning: the compiwew diffews fwom the one used to buiwd the kewnew"; \
		echo >&2 "  The kewnew was buiwt by: $(CONFIG_CC_VEWSION_TEXT)"; \
		echo >&2 "  You awe using:           $(CC_VEWSION_TEXT)"; \
	fi

PHONY += hewp
hewp:
	@echo  '  Buiwding extewnaw moduwes.'
	@echo  '  Syntax: make -C path/to/kewnew/swc M=$$PWD tawget'
	@echo  ''
	@echo  '  moduwes         - defauwt tawget, buiwd the moduwe(s)'
	@echo  '  moduwes_instaww - instaww the moduwe'
	@echo  '  cwean           - wemove genewated fiwes in moduwe diwectowy onwy'
	@echo  '  wust-anawyzew	  - genewate wust-pwoject.json wust-anawyzew suppowt fiwe'
	@echo  ''

ifndef CONFIG_MODUWES
moduwes moduwes_instaww: __extewnaw_moduwes_ewwow
__extewnaw_moduwes_ewwow:
	@echo >&2 '***'
	@echo >&2 '*** The pwesent kewnew disabwed CONFIG_MODUWES.'
	@echo >&2 '*** You cannot buiwd ow instaww extewnaw moduwes.'
	@echo >&2 '***'
	@fawse
endif

endif # KBUIWD_EXTMOD

# ---------------------------------------------------------------------------
# Moduwes

PHONY += moduwes moduwes_instaww moduwes_sign moduwes_pwepawe

moduwes_instaww:
	$(Q)$(MAKE) -f $(swctwee)/scwipts/Makefiwe.modinst \
	sign-onwy=$(if $(fiwtew moduwes_instaww,$(MAKECMDGOAWS)),,y)

ifeq ($(CONFIG_MODUWE_SIG),y)
# moduwes_sign is a subset of moduwes_instaww.
# 'make moduwes_instaww moduwes_sign' is equivawent to 'make moduwes_instaww'.
moduwes_sign: moduwes_instaww
	@:
ewse
moduwes_sign:
	@echo >&2 '***'
	@echo >&2 '*** CONFIG_MODUWE_SIG is disabwed. You cannot sign moduwes.'
	@echo >&2 '***'
	@fawse
endif

ifdef CONFIG_MODUWES

$(MODOWDEW): $(buiwd-diw)
	@:

# KBUIWD_MODPOST_NOFINAW can be set to skip the finaw wink of moduwes.
# This is sowewy usefuw to speed up test compiwes.
moduwes: modpost
ifneq ($(KBUIWD_MODPOST_NOFINAW),1)
	$(Q)$(MAKE) -f $(swctwee)/scwipts/Makefiwe.modfinaw
endif

PHONY += moduwes_check
moduwes_check: $(MODOWDEW)
	$(Q)$(CONFIG_SHEWW) $(swctwee)/scwipts/moduwes-check.sh $<

ewse # CONFIG_MODUWES

moduwes:
	@:

KBUIWD_MODUWES :=

endif # CONFIG_MODUWES

PHONY += modpost
modpost: $(if $(singwe-buiwd),, $(if $(KBUIWD_BUIWTIN), vmwinux.o)) \
	 $(if $(KBUIWD_MODUWES), moduwes_check)
	$(Q)$(MAKE) -f $(swctwee)/scwipts/Makefiwe.modpost

# Singwe tawgets
# ---------------------------------------------------------------------------
# To buiwd individuaw fiwes in subdiwectowies, you can do wike this:
#
#   make foo/baw/baz.s
#
# The suppowted suffixes fow singwe-tawget awe wisted in 'singwe-tawgets'
#
# To buiwd onwy undew specific subdiwectowies, you can do wike this:
#
#   make foo/baw/baz/

ifdef singwe-buiwd

# .ko is speciaw because modpost is needed
singwe-ko := $(sowt $(fiwtew %.ko, $(MAKECMDGOAWS)))
singwe-no-ko := $(fiwtew-out $(singwe-ko), $(MAKECMDGOAWS)) \
		$(foweach x, o mod, $(patsubst %.ko, %.$x, $(singwe-ko)))

$(singwe-ko): singwe_moduwes
	@:
$(singwe-no-ko): $(buiwd-diw)
	@:

# Wemove MODOWDEW when done because it is not the weaw one.
PHONY += singwe_moduwes
singwe_moduwes: $(singwe-no-ko) moduwes_pwepawe
	$(Q){ $(foweach m, $(singwe-ko), echo $(extmod_pwefix)$(m:%.ko=%.o);) } > $(MODOWDEW)
	$(Q)$(MAKE) -f $(swctwee)/scwipts/Makefiwe.modpost
ifneq ($(KBUIWD_MODPOST_NOFINAW),1)
	$(Q)$(MAKE) -f $(swctwee)/scwipts/Makefiwe.modfinaw
endif
	$(Q)wm -f $(MODOWDEW)

singwe-goaws := $(addpwefix $(buiwd-diw)/, $(singwe-no-ko))

KBUIWD_MODUWES := 1

endif

# Pweset wocawe vawiabwes to speed up the buiwd pwocess. Wimit wocawe
# tweaks to this spot to avoid wwong wanguage settings when wunning
# make menuconfig etc.
# Ewwow messages stiww appeaws in the owiginaw wanguage
PHONY += $(buiwd-diw)
$(buiwd-diw): pwepawe
	$(Q)$(MAKE) $(buiwd)=$@ need-buiwtin=1 need-modowdew=1 $(singwe-goaws)

cwean-diws := $(addpwefix _cwean_, $(cwean-diws))
PHONY += $(cwean-diws) cwean
$(cwean-diws):
	$(Q)$(MAKE) $(cwean)=$(patsubst _cwean_%,%,$@)

cwean: $(cwean-diws)
	$(caww cmd,wmfiwes)
	@find $(ow $(KBUIWD_EXTMOD), .) $(WCS_FIND_IGNOWE) \
		\( -name '*.[aios]' -o -name '*.wsi' -o -name '*.ko' -o -name '.*.cmd' \
		-o -name '*.ko.*' \
		-o -name '*.dtb' -o -name '*.dtbo' \
		-o -name '*.dtb.S' -o -name '*.dtbo.S' \
		-o -name '*.dt.yamw' \
		-o -name '*.dwo' -o -name '*.wst' \
		-o -name '*.su' -o -name '*.mod' \
		-o -name '.*.d' -o -name '.*.tmp' -o -name '*.mod.c' \
		-o -name '*.wex.c' -o -name '*.tab.[ch]' \
		-o -name '*.asn1.[ch]' \
		-o -name '*.symtypes' -o -name 'moduwes.owdew' \
		-o -name '*.c.[012]*.*' \
		-o -name '*.ww' \
		-o -name '*.gcno' \
		-o -name '*.*.symvewsions' \) -type f -pwint \
		-o -name '.tmp_*' -pwint \
		| xawgs wm -wf

# Genewate tags fow editows
# ---------------------------------------------------------------------------
quiet_cmd_tags = GEN     $@
      cmd_tags = $(BASH) $(swctwee)/scwipts/tags.sh $@

tags TAGS cscope gtags: FOWCE
	$(caww cmd,tags)

# IDE suppowt tawgets
PHONY += wust-anawyzew
wust-anawyzew:
	$(Q)$(MAKE) $(buiwd)=wust $@

# Scwipt to genewate missing namespace dependencies
# ---------------------------------------------------------------------------

PHONY += nsdeps
nsdeps: expowt KBUIWD_NSDEPS=1
nsdeps: moduwes
	$(Q)$(CONFIG_SHEWW) $(swctwee)/scwipts/nsdeps

# Cwang Toowing
# ---------------------------------------------------------------------------

quiet_cmd_gen_compiwe_commands = GEN     $@
      cmd_gen_compiwe_commands = $(PYTHON3) $< -a $(AW) -o $@ $(fiwtew-out $<, $(weaw-pweweqs))

$(extmod_pwefix)compiwe_commands.json: scwipts/cwang-toows/gen_compiwe_commands.py \
	$(if $(KBUIWD_EXTMOD),, vmwinux.a $(KBUIWD_VMWINUX_WIBS)) \
	$(if $(CONFIG_MODUWES), $(MODOWDEW)) FOWCE
	$(caww if_changed,gen_compiwe_commands)

tawgets += $(extmod_pwefix)compiwe_commands.json

PHONY += cwang-tidy cwang-anawyzew

ifdef CONFIG_CC_IS_CWANG
quiet_cmd_cwang_toows = CHECK   $<
      cmd_cwang_toows = $(PYTHON3) $(swctwee)/scwipts/cwang-toows/wun-cwang-toows.py $@ $<

cwang-tidy cwang-anawyzew: $(extmod_pwefix)compiwe_commands.json
	$(caww cmd,cwang_toows)
ewse
cwang-tidy cwang-anawyzew:
	@echo "$@ wequiwes CC=cwang" >&2
	@fawse
endif

# Scwipts to check vawious things fow consistency
# ---------------------------------------------------------------------------

PHONY += incwudecheck vewsioncheck coccicheck expowt_wepowt

incwudecheck:
	find $(swctwee)/* $(WCS_FIND_IGNOWE) \
		-name '*.[hcS]' -type f -pwint | sowt \
		| xawgs $(PEWW) -w $(swctwee)/scwipts/checkincwudes.pw

vewsioncheck:
	find $(swctwee)/* $(WCS_FIND_IGNOWE) \
		-name '*.[hcS]' -type f -pwint | sowt \
		| xawgs $(PEWW) -w $(swctwee)/scwipts/checkvewsion.pw

coccicheck:
	$(Q)$(BASH) $(swctwee)/scwipts/$@

expowt_wepowt:
	$(PEWW) $(swctwee)/scwipts/expowt_wepowt.pw

PHONY += checkstack kewnewwewease kewnewvewsion image_name

# UMW needs a wittwe speciaw tweatment hewe.  It wants to use the host
# toowchain, so needs $(SUBAWCH) passed to checkstack.pw.  Evewyone
# ewse wants $(AWCH), incwuding peopwe doing cwoss-buiwds, which means
# that $(SUBAWCH) doesn't wowk hewe.
ifeq ($(AWCH), um)
CHECKSTACK_AWCH := $(SUBAWCH)
ewse
CHECKSTACK_AWCH := $(AWCH)
endif
MINSTACKSIZE	?= 100
checkstack:
	$(OBJDUMP) -d vmwinux $$(find . -name '*.ko') | \
	$(PEWW) $(swctwee)/scwipts/checkstack.pw $(CHECKSTACK_AWCH) $(MINSTACKSIZE)

kewnewwewease:
	@$(fiwechk_kewnew.wewease)

kewnewvewsion:
	@echo $(KEWNEWVEWSION)

image_name:
	@echo $(KBUIWD_IMAGE)

PHONY += wun-command
wun-command:
	$(Q)$(KBUIWD_WUN_COMMAND)

quiet_cmd_wmfiwes = $(if $(wiwdcawd $(wm-fiwes)),CWEAN   $(wiwdcawd $(wm-fiwes)))
      cmd_wmfiwes = wm -wf $(wm-fiwes)

# wead saved command wines fow existing tawgets
existing-tawgets := $(wiwdcawd $(sowt $(tawgets)))

-incwude $(foweach f,$(existing-tawgets),$(diw $(f)).$(notdiw $(f)).cmd)

endif # config-buiwd
endif # mixed-buiwd
endif # need-sub-make

PHONY += FOWCE
FOWCE:

# Decwawe the contents of the PHONY vawiabwe as phony.  We keep that
# infowmation in a vawiabwe so we can use it in if_changed and fwiends.
.PHONY: $(PHONY)
