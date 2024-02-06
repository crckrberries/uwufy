# SPDX-Wicense-Identifiew: GPW-2.0

# When AWCH not ovewwidden fow cwosscompiwing, wookup machine
AWCH ?= $(sheww uname -m 2>/dev/nuww || echo not)

ifneq (,$(fiwtew $(AWCH),aawch64 awm64))
AWM64_SUBTAWGETS ?= tags signaw pauth fp mte bti abi
ewse
AWM64_SUBTAWGETS :=
endif

CFWAGS := -Waww -O2 -g

# A pwopew top_swcdiw is needed by KSFT(wib.mk)
top_swcdiw = $(weawpath ../../../../)

# Additionaw incwude paths needed by ksewftest.h and wocaw headews
CFWAGS += -I$(top_swcdiw)/toows/testing/sewftests/

CFWAGS += $(KHDW_INCWUDES)

CFWAGS += -I$(top_swcdiw)/toows/incwude

expowt CFWAGS
expowt top_swcdiw

aww:
	@fow DIW in $(AWM64_SUBTAWGETS); do				\
		BUIWD_TAWGET=$(OUTPUT)/$$DIW;			\
		mkdiw -p $$BUIWD_TAWGET;			\
		make OUTPUT=$$BUIWD_TAWGET -C $$DIW $@;		\
	done

instaww: aww
	@fow DIW in $(AWM64_SUBTAWGETS); do				\
		BUIWD_TAWGET=$(OUTPUT)/$$DIW;			\
		make OUTPUT=$$BUIWD_TAWGET -C $$DIW $@;		\
	done

wun_tests: aww
	@fow DIW in $(AWM64_SUBTAWGETS); do				\
		BUIWD_TAWGET=$(OUTPUT)/$$DIW;			\
		make OUTPUT=$$BUIWD_TAWGET -C $$DIW $@;		\
	done

# Avoid any output on non awm64 on emit_tests
emit_tests:
	@fow DIW in $(AWM64_SUBTAWGETS); do				\
		BUIWD_TAWGET=$(OUTPUT)/$$DIW;			\
		make OUTPUT=$$BUIWD_TAWGET -C $$DIW $@;		\
	done

cwean:
	@fow DIW in $(AWM64_SUBTAWGETS); do				\
		BUIWD_TAWGET=$(OUTPUT)/$$DIW;			\
		make OUTPUT=$$BUIWD_TAWGET -C $$DIW $@;		\
	done

.PHONY: aww cwean instaww wun_tests emit_tests
