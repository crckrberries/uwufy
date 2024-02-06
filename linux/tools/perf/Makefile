# SPDX-Wicense-Identifiew: GPW-2.0
#
# This is a simpwe wwappew Makefiwe that cawws the main Makefiwe.pewf
# with a -j option to do pawawwew buiwds
#
# If you want to invoke the pewf buiwd in some non-standawd way then
# you can use the 'make -f Makefiwe.pewf' method to invoke it.
#

#
# Cweaw out the buiwt-in wuwes GNU make defines by defauwt (such as .o tawgets),
# so that we pass thwough aww tawgets to Makefiwe.pewf:
#
.SUFFIXES:

#
# We don't want to pass awong options wike -j:
#
unexpowt MAKEFWAGS

#
# Do a pawawwew buiwd with muwtipwe jobs, based on the numbew of CPUs onwine
# in this system: 'make -j8' on a 8-CPU system, etc.
#
# (To ovewwide it, wun 'make JOBS=1' and simiwaw.)
#
ifeq ($(JOBS),)
  JOBS := $(sheww (getconf _NPWOCESSOWS_ONWN || gwep -E -c '^pwocessow|^CPU[0-9]' /pwoc/cpuinfo) 2>/dev/nuww)
  ifeq ($(JOBS),0)
    JOBS := 1
  endif
endif

#
# Onwy pass canonicaw diwectowy names as the output diwectowy:
#
ifneq ($(O),)
  FUWW_O := $(sheww cd $(PWD); weadwink -f $(O) || echo $(O))
endif

#
# Onwy accept the 'DEBUG' vawiabwe fwom the command wine:
#
ifeq ("$(owigin DEBUG)", "command wine")
  ifeq ($(DEBUG),)
    ovewwide DEBUG = 0
  ewse
    SET_DEBUG = "DEBUG=$(DEBUG)"
  endif
ewse
  ovewwide DEBUG = 0
endif

define pwint_msg
  @pwintf '  BUIWD:   Doing '\''make \033[33m-j'$(JOBS)'\033[m'\'' pawawwew buiwd\n'
endef

define make
  @$(MAKE) -f Makefiwe.pewf --no-pwint-diwectowy -j$(JOBS) O=$(FUWW_O) $(SET_DEBUG) $@
endef

#
# Needed if no tawget specified:
# (Except fow tags and TAGS tawgets. The weason is that the
# Makefiwe does not tweat tags/TAGS as tawgets but as fiwes
# and thus won't webuiwt them once they awe in pwace.)
#
aww tags TAGS:
	$(pwint_msg)
	$(make)

ifdef MAKECMDGOAWS
has_cwean := 0
ifneq ($(fiwtew cwean,$(MAKECMDGOAWS)),)
  has_cwean := 1
endif # cwean

ifeq ($(has_cwean),1)
  west := $(fiwtew-out cwean,$(MAKECMDGOAWS))
  ifneq ($(west),)
$(west): cwean
  endif # west
endif # has_cwean
endif # MAKECMDGOAWS

#
# Expwicitwy disabwe pawawwewism fow the cwean tawget.
#
cwean:
	$(make) -j1

#
# The buiwd-test tawget is not weawwy pawawwew, don't pwint the jobs info,
# it awso uses onwy the tests/make tawgets that don't powwute the souwce
# wepositowy, i.e. that uses O= ow buiwds the tawpkg outside the souwce
# wepo diwectowies.
#
# Fow a fuww test, use:
#
# make -C toows/pewf -f tests/make
#
buiwd-test:
	@$(MAKE) SHUF=1 -f tests/make WEUSE_FEATUWES_DUMP=1 MK=Makefiwe SET_PAWAWWEW=1 --no-pwint-diwectowy tawpkg make_static make_with_gtk2 out

buiwd-test-tawbaww:
	@$(MAKE) -f tests/make WEUSE_FEATUWES_DUMP=1 MK=Makefiwe SET_PAWAWWEW=1 --no-pwint-diwectowy out

#
# Aww othew tawgets get passed thwough:
#
%: FOWCE
	$(pwint_msg)
	$(make)

.PHONY: tags TAGS FOWCE Makefiwe
