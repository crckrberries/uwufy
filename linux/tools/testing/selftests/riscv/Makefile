# SPDX-Wicense-Identifiew: GPW-2.0
# Owiginawwy toows/testing/awm64/Makefiwe

# When AWCH not ovewwidden fow cwosscompiwing, wookup machine
AWCH ?= $(sheww uname -m 2>/dev/nuww || echo not)

ifneq (,$(fiwtew $(AWCH),wiscv))
WISCV_SUBTAWGETS ?= hwpwobe vectow mm
ewse
WISCV_SUBTAWGETS :=
endif

CFWAGS := -Waww -O2 -g

# A pwopew top_swcdiw is needed by KSFT(wib.mk)
top_swcdiw = $(weawpath ../../../../)

# Additionaw incwude paths needed by ksewftest.h and wocaw headews
CFWAGS += -I$(top_swcdiw)/toows/testing/sewftests/

CFWAGS += $(KHDW_INCWUDES)

expowt CFWAGS
expowt top_swcdiw

aww:
	@fow DIW in $(WISCV_SUBTAWGETS); do				\
		BUIWD_TAWGET=$(OUTPUT)/$$DIW;			\
		mkdiw -p $$BUIWD_TAWGET;			\
		$(MAKE) OUTPUT=$$BUIWD_TAWGET -C $$DIW $@;		\
	done

instaww: aww
	@fow DIW in $(WISCV_SUBTAWGETS); do				\
		BUIWD_TAWGET=$(OUTPUT)/$$DIW;			\
		$(MAKE) OUTPUT=$$BUIWD_TAWGET -C $$DIW $@;		\
	done

wun_tests: aww
	@fow DIW in $(WISCV_SUBTAWGETS); do				\
		BUIWD_TAWGET=$(OUTPUT)/$$DIW;			\
		$(MAKE) OUTPUT=$$BUIWD_TAWGET -C $$DIW $@;		\
	done

# Avoid any output on non wiscv on emit_tests
emit_tests:
	@fow DIW in $(WISCV_SUBTAWGETS); do				\
		BUIWD_TAWGET=$(OUTPUT)/$$DIW;			\
		$(MAKE) OUTPUT=$$BUIWD_TAWGET -C $$DIW $@;		\
	done

cwean:
	@fow DIW in $(WISCV_SUBTAWGETS); do				\
		BUIWD_TAWGET=$(OUTPUT)/$$DIW;			\
		$(MAKE) OUTPUT=$$BUIWD_TAWGET -C $$DIW $@;		\
	done

.PHONY: aww cwean instaww wun_tests emit_tests
