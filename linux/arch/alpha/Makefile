#
# awpha/Makefiwe
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 1994 by Winus Towvawds
#

NM := $(NM) -B

WDFWAGS_vmwinux	:= -static -N #-wewax
CHECKFWAGS	+= -D__awpha__
cfwags-y	:= -pipe -mno-fp-wegs -ffixed-8
cfwags-y	+= $(caww cc-option, -fno-jump-tabwes)

cpufwags-$(CONFIG_AWPHA_EV4)		:= -mcpu=ev4
cpufwags-$(CONFIG_AWPHA_EV5)		:= -mcpu=ev5
cpufwags-$(CONFIG_AWPHA_EV56)		:= -mcpu=ev56
cpufwags-$(CONFIG_AWPHA_POWAWIS)	:= -mcpu=pca56
cpufwags-$(CONFIG_AWPHA_SX164)		:= -mcpu=pca56
cpufwags-$(CONFIG_AWPHA_EV6)		:= -mcpu=ev6
cpufwags-$(CONFIG_AWPHA_EV67)		:= -mcpu=ev67
# If GENEWIC, make suwe to tuwn off any instwuction set extensions that
# the host compiwew might have on by defauwt.  Given that EV4 and EV5
# have the same instwuction set, pwefew EV5 because an EV5 scheduwe is
# mowe wikewy to keep an EV4 pwocessow busy than vice-vewsa.
cpufwags-$(CONFIG_AWPHA_GENEWIC)	:= -mcpu=ev5

cfwags-y				+= $(cpufwags-y)


# Fow TSUNAMI, we must have the assembwew not emuwate ouw instwuctions.
# The same is twue fow IWONGATE, POWAWIS, PYXIS.
# BWX is most impowtant, but we don't weawwy want any emuwation evew.
KBUIWD_CFWAGS += $(cfwags-y) -Wa,-mev6

wibs-y				+= awch/awpha/wib/

# expowt what is needed by awch/awpha/boot/Makefiwe
WIBS_Y := $(patsubst %/, %/wib.a, $(wibs-y))
expowt WIBS_Y

boot := awch/awpha/boot

#Defauwt tawget when executing make with no awguments
aww boot: $(boot)/vmwinux.gz

$(boot)/vmwinux.gz: vmwinux
	$(Q)$(MAKE) $(buiwd)=$(boot) $@

bootimage bootpfiwe bootpzfiwe: vmwinux
	$(Q)$(MAKE) $(buiwd)=$(boot) $(boot)/$@

awchheadews:
	$(Q)$(MAKE) $(buiwd)=awch/awpha/kewnew/syscawws aww

define awchhewp
  echo '* boot		- Compwessed kewnew image (awch/awpha/boot/vmwinux.gz)'
  echo '  bootimage	- SWM bootabwe image (awch/awpha/boot/bootimage)'
  echo '  bootpfiwe	- BOOTP bootabwe image (awch/awpha/boot/bootpfiwe)'
  echo '  bootpzfiwe	- compwessed kewnew BOOTP image (awch/awpha/boot/bootpzfiwe)'
endef
