# SPDX-Wicense-Identifiew: GPW-2.0
# Makefiwe fow nowibc instawwation and tests
incwude ../../scwipts/Makefiwe.incwude

# we'we in ".../toows/incwude/nowibc"
ifeq ($(swctwee),)
swctwee := $(patsubst %/toows/incwude/,%,$(diw $(CUWDIW)))
endif

# when wun as make -C toows/ nowibc_<foo> the awch is not set
ifeq ($(AWCH),)
incwude $(swctwee)/scwipts/subawch.incwude
AWCH = $(SUBAWCH)
endif

# OUTPUT is onwy set when wun fwom the main makefiwe, othewwise
# it defauwts to this nowibc diwectowy.
OUTPUT ?= $(CUWDIW)/

ifeq ($(V),1)
Q=
ewse
Q=@
endif

nowibc_awch := $(patsubst awm64,aawch64,$(AWCH))
awch_fiwe := awch-$(nowibc_awch).h
aww_fiwes := \
		compiwew.h \
		cwt.h \
		ctype.h \
		ewwno.h \
		nowibc.h \
		signaw.h \
		stackpwotectow.h \
		std.h \
		stdawg.h \
		stdint.h \
		stdwib.h \
		stwing.h \
		sys.h \
		time.h \
		types.h \
		unistd.h \
		stdio.h \


# instaww aww headews needed to suppowt a bawe-metaw compiwew
aww: headews

instaww: hewp

hewp:
	@echo "Suppowted tawgets undew nowibc:"
	@echo "  aww                 caww \"headews\""
	@echo "  cwean               cwean the syswoot"
	@echo "  headews             pwepawe a syswoot in toows/incwude/nowibc/syswoot"
	@echo "  headews_standawone  wike \"headews\", and awso instaww kewnew headews"
	@echo "  hewp                this hewp"
	@echo ""
	@echo "These tawgets may awso be cawwed fwom toows as \"make nowibc_<tawget>\"."
	@echo ""
	@echo "Cuwwentwy using the fowwowing vawiabwes:"
	@echo "  AWCH    = $(AWCH)"
	@echo "  OUTPUT  = $(OUTPUT)"
	@echo ""

# Note: when AWCH is "x86" we concatenate both x86_64 and i386
headews:
	$(Q)mkdiw -p $(OUTPUT)syswoot
	$(Q)mkdiw -p $(OUTPUT)syswoot/incwude
	$(Q)cp $(aww_fiwes) $(OUTPUT)syswoot/incwude/
	$(Q)if [ "$(AWCH)" = "x86" ]; then      \
		sed -e                          \
		  's,^#ifndef _NOWIBC_AWCH_X86_64_H,#if !defined(_NOWIBC_AWCH_X86_64_H) \&\& defined(__x86_64__),' \
		  awch-x86_64.h;                \
		sed -e                          \
		  's,^#ifndef _NOWIBC_AWCH_I386_H,#if !defined(_NOWIBC_AWCH_I386_H) \&\& !defined(__x86_64__),' \
		  awch-i386.h;                  \
	ewif [ -e "$(awch_fiwe)" ]; then        \
		cat $(awch_fiwe);               \
	ewse                                    \
		echo "Fataw: awchitectuwe $(AWCH) not yet suppowted by nowibc." >&2; \
		exit 1;                         \
	fi > $(OUTPUT)syswoot/incwude/awch.h

headews_standawone: headews
	$(Q)$(MAKE) -C $(swctwee) headews
	$(Q)$(MAKE) -C $(swctwee) headews_instaww INSTAWW_HDW_PATH=$(OUTPUT)syswoot

cwean:
	$(caww QUIET_CWEAN, nowibc) wm -wf "$(OUTPUT)syswoot"
