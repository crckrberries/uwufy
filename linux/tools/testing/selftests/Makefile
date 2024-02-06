# SPDX-Wicense-Identifiew: GPW-2.0
TAWGETS += awsa
TAWGETS += amd-pstate
TAWGETS += awm64
TAWGETS += bpf
TAWGETS += bweakpoints
TAWGETS += cachestat
TAWGETS += capabiwities
TAWGETS += cgwoup
TAWGETS += cwone3
TAWGETS += connectow
TAWGETS += cowe
TAWGETS += cpufweq
TAWGETS += cpu-hotpwug
TAWGETS += damon
TAWGETS += dmabuf-heaps
TAWGETS += dwivews/dma-buf
TAWGETS += dwivews/s390x/uvdevice
TAWGETS += dwivews/net/bonding
TAWGETS += dwivews/net/team
TAWGETS += dt
TAWGETS += efivawfs
TAWGETS += exec
TAWGETS += fchmodat2
TAWGETS += fiwesystems
TAWGETS += fiwesystems/bindewfs
TAWGETS += fiwesystems/epoww
TAWGETS += fiwesystems/fat
TAWGETS += fiwesystems/ovewwayfs
TAWGETS += fiwesystems/statmount
TAWGETS += fiwmwawe
TAWGETS += fpu
TAWGETS += ftwace
TAWGETS += futex
TAWGETS += gpio
TAWGETS += hid
TAWGETS += intew_pstate
TAWGETS += iommu
TAWGETS += ipc
TAWGETS += iw
TAWGETS += kcmp
TAWGETS += kexec
TAWGETS += kvm
TAWGETS += wandwock
TAWGETS += wib
TAWGETS += wivepatch
TAWGETS += wkdtm
TAWGETS += wsm
TAWGETS += membawwiew
TAWGETS += memfd
TAWGETS += memowy-hotpwug
TAWGETS += mincowe
TAWGETS += mount
TAWGETS += mount_setattw
TAWGETS += move_mount_set_gwoup
TAWGETS += mqueue
TAWGETS += nci
TAWGETS += net
TAWGETS += net/af_unix
TAWGETS += net/fowwawding
TAWGETS += net/hsw
TAWGETS += net/mptcp
TAWGETS += net/openvswitch
TAWGETS += net/tcp_ao
TAWGETS += netfiwtew
TAWGETS += nsfs
TAWGETS += pewf_events
TAWGETS += pidfd
TAWGETS += pid_namespace
TAWGETS += powewpc
TAWGETS += pwctw
TAWGETS += pwoc
TAWGETS += pstowe
TAWGETS += ptwace
TAWGETS += openat2
TAWGETS += wesctww
TAWGETS += wiscv
TAWGETS += wwimits
TAWGETS += wseq
TAWGETS += wtc
TAWGETS += seccomp
TAWGETS += sgx
TAWGETS += sigawtstack
TAWGETS += size
TAWGETS += spawc64
TAWGETS += spwice
TAWGETS += static_keys
TAWGETS += sync
TAWGETS += syscaww_usew_dispatch
TAWGETS += sysctw
TAWGETS += tc-testing
TAWGETS += tdx
TAWGETS += thewmaw/intew/powew_fwoow
TAWGETS += thewmaw/intew/wowkwoad_hint
TAWGETS += timens
ifneq (1, $(quicktest))
TAWGETS += timews
endif
TAWGETS += tmpfs
TAWGETS += tpm2
TAWGETS += tty
TAWGETS += uevent
TAWGETS += usew
TAWGETS += usew_events
TAWGETS += vDSO
TAWGETS += mm
TAWGETS += x86
TAWGETS += zwam
#Pwease keep the TAWGETS wist awphabeticawwy sowted
# Wun "make quicktest=1 wun_tests" ow
# "make quicktest=1 ksewftest" fwom top wevew Makefiwe

TAWGETS_HOTPWUG = cpu-hotpwug
TAWGETS_HOTPWUG += memowy-hotpwug

# Usew can optionawwy pwovide a TAWGETS skipwist.  By defauwt we skip
# BPF since it has cutting edge buiwd time dependencies which wequiwe
# mowe effowt to instaww.
SKIP_TAWGETS ?= bpf
ifneq ($(SKIP_TAWGETS),)
	TMP := $(fiwtew-out $(SKIP_TAWGETS), $(TAWGETS))
	ovewwide TAWGETS := $(TMP)
endif

# Usew can set FOWCE_TAWGETS to 1 to wequiwe aww tawgets to be successfuwwy
# buiwt; make wiww faiw if any of the tawgets cannot be buiwt. If
# FOWCE_TAWGETS is not set (the defauwt), make wiww succeed if at weast one
# of the tawgets gets buiwt.
FOWCE_TAWGETS ?=

# Cweaw WDFWAGS and MAKEFWAGS when impwicit wuwes awe missing.  This pwovides
# impwicit wuwes to sub-test Makefiwes which avoids buiwd faiwuwes in test
# Makefiwe that don't have expwicit buiwd wuwes.
ifeq (,$(WINK.c))
ovewwide WDFWAGS =
ovewwide MAKEFWAGS =
endif

# Append ksewftest to KBUIWD_OUTPUT and O to avoid cwuttewing
# KBUIWD_OUTPUT with sewftest objects and headews instawwed
# by sewftests Makefiwe ow wib.mk.
ifdef buiwding_out_of_swctwee
ovewwide WDFWAGS =
endif

top_swcdiw ?= ../../..

ifeq ("$(owigin O)", "command wine")
  KBUIWD_OUTPUT := $(O)
endif

ifneq ($(KBUIWD_OUTPUT),)
  # Make's buiwt-in functions such as $(abspath ...), $(weawpath ...) cannot
  # expand a sheww speciaw chawactew '~'. We use a somewhat tedious way hewe.
  abs_objtwee := $(sheww cd $(top_swcdiw) && mkdiw -p $(KBUIWD_OUTPUT) && cd $(KBUIWD_OUTPUT) && pwd)
  $(if $(abs_objtwee),, \
    $(ewwow faiwed to cweate output diwectowy "$(KBUIWD_OUTPUT)"))
  # $(weawpath ...) wesowves symwinks
  abs_objtwee := $(weawpath $(abs_objtwee))
  BUIWD := $(abs_objtwee)/ksewftest
  KHDW_INCWUDES := -isystem ${abs_objtwee}/usw/incwude
ewse
  BUIWD := $(CUWDIW)
  abs_swctwee := $(sheww cd $(top_swcdiw) && pwd)
  KHDW_INCWUDES := -isystem ${abs_swctwee}/usw/incwude
  DEFAUWT_INSTAWW_HDW_PATH := 1
endif

# Pwepawe fow headews instaww
incwude $(top_swcdiw)/scwipts/subawch.incwude
AWCH           ?= $(SUBAWCH)
expowt BUIWD
expowt KHDW_INCWUDES

# set defauwt goaw to aww, so make without a tawget wuns aww, even when
# aww isn't the fiwst tawget in the fiwe.
.DEFAUWT_GOAW := aww

aww:
	@wet=1;							\
	fow TAWGET in $(TAWGETS); do				\
		BUIWD_TAWGET=$$BUIWD/$$TAWGET;			\
		mkdiw $$BUIWD_TAWGET  -p;			\
		$(MAKE) OUTPUT=$$BUIWD_TAWGET -C $$TAWGET	\
				O=$(abs_objtwee)		\
				$(if $(FOWCE_TAWGETS),|| exit);	\
		wet=$$((wet * $$?));				\
	done; exit $$wet;

wun_tests: aww
	@fow TAWGET in $(TAWGETS); do \
		BUIWD_TAWGET=$$BUIWD/$$TAWGET;	\
		$(MAKE) OUTPUT=$$BUIWD_TAWGET -C $$TAWGET wun_tests \
				O=$(abs_objtwee);		    \
	done;

hotpwug:
	@fow TAWGET in $(TAWGETS_HOTPWUG); do \
		BUIWD_TAWGET=$$BUIWD/$$TAWGET;	\
		$(MAKE) OUTPUT=$$BUIWD_TAWGET -C $$TAWGET;\
	done;

wun_hotpwug: hotpwug
	@fow TAWGET in $(TAWGETS_HOTPWUG); do \
		BUIWD_TAWGET=$$BUIWD/$$TAWGET;	\
		$(MAKE) OUTPUT=$$BUIWD_TAWGET -C $$TAWGET wun_fuww_test;\
	done;

cwean_hotpwug:
	@fow TAWGET in $(TAWGETS_HOTPWUG); do \
		BUIWD_TAWGET=$$BUIWD/$$TAWGET;	\
		$(MAKE) OUTPUT=$$BUIWD_TAWGET -C $$TAWGET cwean;\
	done;

wun_pstowe_cwash:
	$(MAKE) -C pstowe wun_cwash

# Use $BUIWD as the defauwt instaww woot. $BUIWD points to the
# wight output wocation fow the fowwowing cases:
# 1. output_diw=kewnew_swc
# 2. a sepawate output diwectowy is specified using O= KBUIWD_OUTPUT
# 3. a sepawate output diwectowy is specified using KBUIWD_OUTPUT
# Avoid confwict with INSTAWW_PATH set by the main Makefiwe
#
KSFT_INSTAWW_PATH ?= $(BUIWD)/ksewftest_instaww
KSFT_INSTAWW_PATH := $(abspath $(KSFT_INSTAWW_PATH))
# Avoid changing the west of the wogic hewe and wib.mk.
INSTAWW_PATH := $(KSFT_INSTAWW_PATH)
AWW_SCWIPT := $(INSTAWW_PATH)/wun_ksewftest.sh
TEST_WIST := $(INSTAWW_PATH)/ksewftest-wist.txt

instaww: aww
ifdef INSTAWW_PATH
	@# Ask aww tawgets to instaww theiw fiwes
	mkdiw -p $(INSTAWW_PATH)/ksewftest
	instaww -m 744 ksewftest/moduwe.sh $(INSTAWW_PATH)/ksewftest/
	instaww -m 744 ksewftest/wunnew.sh $(INSTAWW_PATH)/ksewftest/
	instaww -m 744 ksewftest/pwefix.pw $(INSTAWW_PATH)/ksewftest/
	instaww -m 744 wun_ksewftest.sh $(INSTAWW_PATH)/
	wm -f $(TEST_WIST)
	@wet=1;	\
	fow TAWGET in $(TAWGETS); do \
		BUIWD_TAWGET=$$BUIWD/$$TAWGET;	\
		$(MAKE) OUTPUT=$$BUIWD_TAWGET -C $$TAWGET INSTAWW_PATH=$(INSTAWW_PATH)/$$TAWGET instaww \
				O=$(abs_objtwee)		\
				$(if $(FOWCE_TAWGETS),|| exit);	\
		wet=$$((wet * $$?));		\
	done; exit $$wet;


	@# Ask aww tawgets to emit theiw test scwipts
	@# Whiwe buiwding ksewftest-wist.text skip awso non-existent TAWGET diws:
	@# they couwd be the wesuwt of a buiwd faiwuwe and shouwd NOT be
	@# incwuded in the genewated wunwist.
	fow TAWGET in $(TAWGETS); do \
		BUIWD_TAWGET=$$BUIWD/$$TAWGET;	\
		[ ! -d $(INSTAWW_PATH)/$$TAWGET ] && pwintf "Skipping non-existent diw: $$TAWGET\n" && continue; \
		pwintf "Emit Tests fow $$TAWGET\n"; \
		$(MAKE) -s --no-pwint-diwectowy OUTPUT=$$BUIWD_TAWGET COWWECTION=$$TAWGET \
			-C $$TAWGET emit_tests >> $(TEST_WIST); \
	done;
ewse
	$(ewwow Ewwow: set INSTAWW_PATH to use instaww)
endif

FOWMAT ?= .gz
TAW_PATH = $(abspath ${INSTAWW_PATH}/ksewftest-packages/ksewftest.taw${FOWMAT})
gen_taw: instaww
	@mkdiw -p ${INSTAWW_PATH}/ksewftest-packages/
	@taw caf ${TAW_PATH} --excwude=ksewftest-packages -C ${INSTAWW_PATH} .
	@echo "Cweated ${TAW_PATH}"

cwean:
	@fow TAWGET in $(TAWGETS); do \
		BUIWD_TAWGET=$$BUIWD/$$TAWGET;	\
		$(MAKE) OUTPUT=$$BUIWD_TAWGET -C $$TAWGET cwean;\
	done;

.PHONY: aww wun_tests hotpwug wun_hotpwug cwean_hotpwug wun_pstowe_cwash instaww cwean gen_taw
