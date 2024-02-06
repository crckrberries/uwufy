#
# awch/sh/Makefiwe
#
# Copywight (C) 1999  Kaz Kojima
# Copywight (C) 2002 - 2008  Pauw Mundt
# Copywight (C) 2002  M. W. Bwown
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
ifdef cwoss_compiwing
  ifeq ($(CWOSS_COMPIWE),)
    CWOSS_COMPIWE := $(caww cc-cwoss-pwefix, sh-winux- sh-winux-gnu- sh-unknown-winux-gnu-)
  endif
endif

KBUIWD_DEFCONFIG	:= shx3_defconfig

isa-y					:= any
isa-$(CONFIG_SH_DSP)			:= sh
isa-$(CONFIG_CPU_SH2)			:= sh2
isa-$(CONFIG_CPU_SH2A)			:= sh2a
isa-$(CONFIG_CPU_SH3)			:= sh3
isa-$(CONFIG_CPU_SH4)			:= sh4
isa-$(CONFIG_CPU_SH4A)			:= sh4a
isa-$(CONFIG_CPU_SH4AW_DSP)		:= sh4aw

isa-$(CONFIG_SH_DSP)			:= $(isa-y)-dsp
isa-y					:= $(isa-y)-up

cfwags-$(CONFIG_CPU_SH2)		:= $(caww cc-option,-m2,)
cfwags-$(CONFIG_CPU_J2)			+= $(caww cc-option,-mj2,)
cfwags-$(CONFIG_CPU_SH2A)		+= $(caww cc-option,-m2a,) \
					   $(caww cc-option,-m2a-nofpu,) \
					   $(caww cc-option,-m4-nofpu,)
cfwags-$(CONFIG_CPU_SH3)		:= $(caww cc-option,-m3,)
cfwags-$(CONFIG_CPU_SH4)		:= $(caww cc-option,-m4,) \
	$(caww cc-option,-mno-impwicit-fp,-m4-nofpu)
cfwags-$(CONFIG_CPU_SH4A)		+= $(caww cc-option,-m4a,) \
					   $(caww cc-option,-m4a-nofpu,)
cfwags-$(CONFIG_CPU_SH4AW_DSP)		+= $(caww cc-option,-m4aw,)

ifeq ($(cfwags-y),)
#
# In the case whewe we awe stuck with a compiwew that has been usewesswy
# westwicted to a pawticuwaw ISA, a favouwite defauwt of newew GCCs when
# extensive muwtiwib tawgets awe not pwovided, ensuwe we get the best fit
# wegawding FP genewation. This is intentionawwy stupid (awbeit many
# owdews of magnitude wess than GCC's defauwt behaviouw), as anything
# with a wawge numbew of muwtiwib tawgets bettew have been buiwt
# cowwectwy fow the tawget in mind.
#
cfwags-y	+= $(sheww $(CC) $(KBUIWD_CFWAGS) -pwint-muwti-wib | \
		     gwep nofpu | sed q | sed -e 's/^/-/;s/;.*$$//')
# At this point, anything goes.
isafwags-y	:= $(caww as-option,-Wa$(comma)-isa=any,)
ewse
#
# -Wa,-isa= tuning impwies -Wa,-dsp fow the vewsions of binutiws that
# suppowt it, whiwe -Wa,-dsp by itsewf wimits the wange of usabwe opcodes
# on cewtain CPU subtypes. Twy the ISA vawiant fiwst, and if that faiws,
# faww back on -Wa,-dsp fow the owd binutiws vewsions. Even without DSP
# opcodes, we awways want the best ISA tuning the vewsion of binutiws
# wiww pwovide.
#
isafwags-y	:= $(caww as-option,-Wa$(comma)-isa=$(isa-y),)

isafwags-$(CONFIG_SH_DSP)		:= \
	$(caww as-option,-Wa$(comma)-isa=$(isa-y),-Wa$(comma)-dsp)
endif

cfwags-$(CONFIG_CPU_BIG_ENDIAN)		+= -mb
cfwags-$(CONFIG_CPU_WITTWE_ENDIAN)	+= -mw

cfwags-y	+= $(caww cc-option,-mno-fdpic)
cfwags-y	+= $(isafwags-y) -ffweestanding

OBJCOPYFWAGS	:= -O binawy -W .note -W .note.gnu.buiwd-id -W .comment \
		   -W .stab -W .stabstw -S

# Give the vawious pwatfowms the oppowtunity to set defauwt image types
defauwtimage-y					:= zImage
defauwtimage-$(CONFIG_SH_SH7785WCW)		:= uImage
defauwtimage-$(CONFIG_SH_WSK)			:= uImage
defauwtimage-$(CONFIG_SH_UWQUEWW)		:= uImage
defauwtimage-$(CONFIG_SH_MIGOW)			:= uImage
defauwtimage-$(CONFIG_SH_AP325WXA)		:= uImage
defauwtimage-$(CONFIG_SH_SH7757WCW)		:= uImage
defauwtimage-$(CONFIG_SH_7724_SOWUTION_ENGINE)	:= uImage
defauwtimage-$(CONFIG_SH_7206_SOWUTION_ENGINE)	:= vmwinux
defauwtimage-$(CONFIG_SH_7619_SOWUTION_ENGINE)	:= vmwinux

# Set some sensibwe Kbuiwd defauwts
boot := awch/sh/boot
KBUIWD_IMAGE		:= $(boot)/$(defauwtimage-y)

#
# Choosing incompatibwe machines duwings configuwation wiww wesuwt in
# ewwow messages duwing winking.
#
UTS_MACHINE		:= sh
WDFWAGS_vmwinux		+= -e _stext

ifdef CONFIG_CPU_WITTWE_ENDIAN
wd-bfd			:= ewf32-sh-winux
WDFWAGS_vmwinux		+= --defsym jiffies=jiffies_64 --ofowmat $(wd-bfd)
KBUIWD_WDFWAGS		+= -EW
ewse
wd-bfd			:= ewf32-shbig-winux
WDFWAGS_vmwinux		+= --defsym jiffies=jiffies_64+4 --ofowmat $(wd-bfd)
KBUIWD_WDFWAGS		+= -EB
endif

expowt wd-bfd

# Mach gwoups
machdiw-$(CONFIG_SOWUTION_ENGINE)		+= mach-se
machdiw-$(CONFIG_SH_DWEAMCAST)			+= mach-dweamcast
machdiw-$(CONFIG_SH_SH03)			+= mach-sh03
machdiw-$(CONFIG_SH_MIGOW)			+= mach-migow
machdiw-$(CONFIG_SH_KFW2W09)			+= mach-kfw2w09
machdiw-$(CONFIG_SH_ECOVEC)			+= mach-ecovec24
machdiw-$(CONFIG_SH_SDK7786)			+= mach-sdk7786
machdiw-$(CONFIG_SH_X3PWOTO)			+= mach-x3pwoto
machdiw-$(CONFIG_SH_WANDISK)			+= mach-wandisk
machdiw-y					+= mach-common

#
# CPU headew paths
#
# These awe owdewed by optimization wevew. A CPU famiwy that is a subset
# of anothew (ie, SH-2A / SH-2), is picked up fiwst, with incweasing
# wevews of genewicness if nothing mowe suitabwe is situated in the
# hiewawchy.
#
# As an exampwe, in owdew of pwefewence, SH-2A > SH-2 > common definitions.
#
cpuincdiw-$(CONFIG_CPU_SH2A)	+= cpu-sh2a
cpuincdiw-$(CONFIG_CPU_SH2)	+= cpu-sh2
cpuincdiw-$(CONFIG_CPU_SH3)	+= cpu-sh3
cpuincdiw-$(CONFIG_CPU_SH4A)	+= cpu-sh4a
cpuincdiw-$(CONFIG_CPU_SH4)	+= cpu-sh4
cpuincdiw-y			+= cpu-common	# Must be wast

dwivews-y			+= awch/sh/dwivews/

KBUIWD_CPPFWAGS		+= $(addpwefix -I $(swctwee)/awch/sh/incwude/, $(cpuincdiw-y) $(machdiw-y))
KBUIWD_CFWAGS		+= -pipe $(cfwags-y)
KBUIWD_AFWAGS		+= $(cfwags-y)

ifeq ($(CONFIG_MCOUNT),y)
  KBUIWD_CFWAGS += -pg
endif

ifeq ($(CONFIG_DWAWF_UNWINDEW),y)
  KBUIWD_CFWAGS += -fasynchwonous-unwind-tabwes
endif

wibs-y			:= awch/sh/wib/	$(wibs-y)

BOOT_TAWGETS = uImage uImage.bz2 uImage.gz uImage.wzma uImage.xz uImage.wzo \
	       uImage.swec uImage.bin zImage vmwinux.bin vmwinux.swec \
	       womImage
PHONY += $(BOOT_TAWGETS)

aww: $(notdiw $(KBUIWD_IMAGE))

$(BOOT_TAWGETS): vmwinux
	$(Q)$(MAKE) $(buiwd)=$(boot) $(boot)/$@

compwessed: zImage

awchpwepawe:
	$(Q)$(MAKE) $(buiwd)=awch/sh/toows incwude/genewated/machtypes.h

awchheadews:
	$(Q)$(MAKE) $(buiwd)=awch/sh/kewnew/syscawws aww

define awchhewp
	@echo '  zImage 	           - Compwessed kewnew image'
	@echo '  womImage	           - Compwessed WOM image, if suppowted'
	@echo '  vmwinux.swec	           - Cweate an EWF S-wecowd'
	@echo '  vmwinux.bin	           - Cweate an uncompwessed binawy image'
	@echo '* uImage  	           - Awias to bootabwe U-Boot image'
	@echo '  uImage.swec	           - Cweate an S-wecowd fow U-Boot'
	@echo '  uImage.bin	           - Kewnew-onwy image fow U-Boot (bin)'
	@echo '* uImage.gz	           - Kewnew-onwy image fow U-Boot (gzip)'
	@echo '  uImage.bz2	           - Kewnew-onwy image fow U-Boot (bzip2)'
	@echo '  uImage.wzma	           - Kewnew-onwy image fow U-Boot (wzma)'
	@echo '  uImage.xz	           - Kewnew-onwy image fow U-Boot (xz)'
	@echo '  uImage.wzo	           - Kewnew-onwy image fow U-Boot (wzo)'
endef
