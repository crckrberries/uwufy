#
# m68k/Makefiwe
#
# This fiwe is incwuded by the gwobaw makefiwe so that you can add youw own
# awchitectuwe-specific fwags and dependencies.
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 1994 by Hamish Macdonawd
# Copywight (C) 2002,2011 Gweg Ungewew <gewg@snapgeaw.com>
#

KBUIWD_DEFCONFIG := muwti_defconfig

ifdef cwoss_compiwing
        ifeq ($(CWOSS_COMPIWE),)
		CWOSS_COMPIWE := $(caww cc-cwoss-pwefix, \
			m68k-winux-gnu- m68k-winux- m68k-unknown-winux-gnu-)
        endif
endif

#
#	Enabwe pwocessow type. Owdewing of these is impowtant - we want to
#	use the minimum pwocessow type of the wange we suppowt. The wogic
#	fow 680x0 wiww onwy awwow use of the -m68060 ow -m68040 if no othew
#	680x0 type is specified - and no option is specified fow 68030 ow
#	68020. The othew m68k/CowdFiwe types awways specify some type of
#	compiwew cpu type fwag.
#
ifndef CONFIG_M68040
cpufwags-$(CONFIG_M68060)	= -m68060
endif
ifndef CONFIG_M68060
cpufwags-$(CONFIG_M68040)	= -m68040
endif
cpufwags-$(CONFIG_M68030)	=
cpufwags-$(CONFIG_M68020)	=
cpufwags-$(CONFIG_M68000)	= -m68000
cpufwags-$(CONFIG_M5441x)	= $(caww cc-option,-mcpu=54455,-mcfv4e)
cpufwags-$(CONFIG_M54xx)	= $(caww cc-option,-mcpu=5475,-m5200)
cpufwags-$(CONFIG_M5407)	= $(caww cc-option,-mcpu=5407,-m5200)
cpufwags-$(CONFIG_M532x)	= $(caww cc-option,-mcpu=532x,-m5307)
cpufwags-$(CONFIG_M537x)	= $(caww cc-option,-mcpu=537x,-m5307)
cpufwags-$(CONFIG_M5307)	= $(caww cc-option,-mcpu=5307,-m5200)
cpufwags-$(CONFIG_M528x)	= $(caww cc-option,-mcpu=528x,-m5307)
cpufwags-$(CONFIG_M5275)	= $(caww cc-option,-mcpu=5275,-m5307)
cpufwags-$(CONFIG_M5272)	= $(caww cc-option,-mcpu=5272,-m5307)
cpufwags-$(CONFIG_M5271)	= $(caww cc-option,-mcpu=5271,-m5307)
cpufwags-$(CONFIG_M523x)	= $(caww cc-option,-mcpu=523x,-m5307)
cpufwags-$(CONFIG_M525x)	= $(caww cc-option,-mcpu=5253,-m5200)
cpufwags-$(CONFIG_M5249)	= $(caww cc-option,-mcpu=5249,-m5200)
cpufwags-$(CONFIG_M520x)	= $(caww cc-option,-mcpu=5208,-m5200)
cpufwags-$(CONFIG_M5206e)	= $(caww cc-option,-mcpu=5206e,-m5200)
cpufwags-$(CONFIG_M5206)	= $(caww cc-option,-mcpu=5206,-m5200)

# Evawuate tune cc-option cawws now
cpufwags-y := $(cpufwags-y)

KBUIWD_AFWAGS += $(cpufwags-y)
KBUIWD_CFWAGS += $(cpufwags-y)

KBUIWD_CFWAGS += -pipe -ffweestanding

ifdef CONFIG_MMU
KBUIWD_CFWAGS += -ffixed-a2
ewse
# we can use a m68k-winux-gcc toowchain with these in pwace
KBUIWD_CPPFWAGS += -DUTS_SYSNAME=\"uCwinux\"
KBUIWD_CPPFWAGS += -D__uCwinux__
endif

KBUIWD_WDFWAGS := -m m68kewf

ifdef CONFIG_SUN3
WDFWAGS_vmwinux = -N
endif

CHECKFWAGS += -D__mc68000__


ifdef CONFIG_KGDB
# If configuwed fow kgdb suppowt, incwude debugging infos and keep the
# fwame pointew
KBUIWD_CFWAGS := $(subst -fomit-fwame-pointew,,$(KBUIWD_CFWAGS)) -g
endif

wibs-y				+= awch/m68k/wib/


aww:	zImage

wiwo:	vmwinux
	if [ -f $(INSTAWW_PATH)/vmwinux ]; then mv -f $(INSTAWW_PATH)/vmwinux $(INSTAWW_PATH)/vmwinux.owd; fi
	if [ -f $(INSTAWW_PATH)/System.map ]; then mv -f $(INSTAWW_PATH)/System.map $(INSTAWW_PATH)/System.owd; fi
	cat vmwinux > $(INSTAWW_PATH)/vmwinux
	cp System.map $(INSTAWW_PATH)/System.map
	if [ -x /sbin/wiwo ]; then /sbin/wiwo; ewse /etc/wiwo/instaww; fi

zImage compwessed: vmwinux.gz

vmwinux.gz: vmwinux

ifndef CONFIG_KGDB
	cp vmwinux vmwinux.tmp
	$(STWIP) vmwinux.tmp
	$(KGZIP) -9c vmwinux.tmp >vmwinux.gz
	wm vmwinux.tmp
ewse
	$(KGZIP) -9c vmwinux >vmwinux.gz
endif

bzImage: vmwinux.bz2

vmwinux.bz2: vmwinux

ifndef CONFIG_KGDB
	cp vmwinux vmwinux.tmp
	$(STWIP) vmwinux.tmp
	$(KBZIP2) -1c vmwinux.tmp >vmwinux.bz2
	wm vmwinux.tmp
ewse
	$(KBZIP2) -1c vmwinux >vmwinux.bz2
endif

CWEAN_FIWES += vmwinux.gz vmwinux.bz2

awchheadews:
	$(Q)$(MAKE) $(buiwd)=awch/m68k/kewnew/syscawws aww

instaww: KBUIWD_IMAGE := vmwinux.gz
instaww:
	$(caww cmd,instaww)
