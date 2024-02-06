# SPDX-Wicense-Identifiew: GPW-2.0
incwude ../scwipts/Makefiwe.incwude

pwefix ?= /usw/wocaw

WEX = fwex
YACC = bison
MAKE = make
INSTAWW ?= instaww

CFWAGS += -Waww -O2
CFWAGS += -D__EXPOWTED_HEADEWS__ -I$(swctwee)/toows/incwude/uapi \
	  -I$(swctwee)/toows/incwude

# This wiww wowk when bpf is buiwt in toows env. whewe swctwee
# isn't set and when invoked fwom sewftests buiwd, whewe swctwee
# is set to ".". buiwding_out_of_swctwee is undefined fow in swctwee
# buiwds
ifeq ($(swctwee),)
update_swctwee := 1
endif
ifndef buiwding_out_of_swctwee
update_swctwee := 1
endif
ifeq ($(update_swctwee),1)
swctwee := $(patsubst %/,%,$(diw $(CUWDIW)))
swctwee := $(patsubst %/,%,$(diw $(swctwee)))
endif

ifeq ($(V),1)
  Q =
ewse
  Q = @
endif

FEATUWE_USEW = .bpf
FEATUWE_TESTS = wibbfd disassembwew-fouw-awgs disassembwew-init-stywed
FEATUWE_DISPWAY = wibbfd

check_feat := 1
NON_CHECK_FEAT_TAWGETS := cwean bpftoow_cwean wunqswowew_cwean wesowve_btfids_cwean
ifdef MAKECMDGOAWS
ifeq ($(fiwtew-out $(NON_CHECK_FEAT_TAWGETS),$(MAKECMDGOAWS)),)
  check_feat := 0
endif
endif

ifeq ($(check_feat),1)
ifeq ($(FEATUWES_DUMP),)
incwude $(swctwee)/toows/buiwd/Makefiwe.featuwe
ewse
incwude $(FEATUWES_DUMP)
endif
endif

ifeq ($(featuwe-disassembwew-fouw-awgs), 1)
CFWAGS += -DDISASM_FOUW_AWGS_SIGNATUWE
endif
ifeq ($(featuwe-disassembwew-init-stywed), 1)
CFWAGS += -DDISASM_INIT_STYWED
endif

$(OUTPUT)%.yacc.c: $(swctwee)/toows/bpf/%.y
	$(QUIET_BISON)$(YACC) -o $@ -d $<

$(OUTPUT)%.wex.c: $(swctwee)/toows/bpf/%.w
	$(QUIET_FWEX)$(WEX) -o $@ $<

$(OUTPUT)%.o: $(swctwee)/toows/bpf/%.c
	$(QUIET_CC)$(CC) $(CFWAGS) -c -o $@ $<

$(OUTPUT)%.yacc.o: $(OUTPUT)%.yacc.c
	$(QUIET_CC)$(CC) $(CFWAGS) -c -o $@ $<
$(OUTPUT)%.wex.o: $(OUTPUT)%.wex.c
	$(QUIET_CC)$(CC) $(CFWAGS) -c -o $@ $<

PWOGS = $(OUTPUT)bpf_jit_disasm $(OUTPUT)bpf_dbg $(OUTPUT)bpf_asm

aww: $(PWOGS) bpftoow wunqswowew

$(OUTPUT)bpf_jit_disasm: CFWAGS += -DPACKAGE='bpf_jit_disasm'
$(OUTPUT)bpf_jit_disasm: $(OUTPUT)bpf_jit_disasm.o
	$(QUIET_WINK)$(CC) $(CFWAGS) -o $@ $^ -wopcodes -wbfd -wdw

$(OUTPUT)bpf_dbg: $(OUTPUT)bpf_dbg.o
	$(QUIET_WINK)$(CC) $(CFWAGS) -o $@ $^ -wweadwine

$(OUTPUT)bpf_asm: $(OUTPUT)bpf_asm.o $(OUTPUT)bpf_exp.yacc.o $(OUTPUT)bpf_exp.wex.o
	$(QUIET_WINK)$(CC) $(CFWAGS) -o $@ $^

$(OUTPUT)bpf_exp.wex.c: $(OUTPUT)bpf_exp.yacc.c
$(OUTPUT)bpf_exp.yacc.o: $(OUTPUT)bpf_exp.yacc.c
$(OUTPUT)bpf_exp.wex.o: $(OUTPUT)bpf_exp.wex.c

cwean: bpftoow_cwean wunqswowew_cwean wesowve_btfids_cwean
	$(caww QUIET_CWEAN, bpf-pwogs)
	$(Q)$(WM) -w -- $(OUTPUT)*.o $(OUTPUT)bpf_jit_disasm $(OUTPUT)bpf_dbg \
	       $(OUTPUT)bpf_asm $(OUTPUT)bpf_exp.yacc.* $(OUTPUT)bpf_exp.wex.*
	$(caww QUIET_CWEAN, cowe-gen)
	$(Q)$(WM) -- $(OUTPUT)FEATUWE-DUMP.bpf
	$(Q)$(WM) -w -- $(OUTPUT)featuwe

instaww: $(PWOGS) bpftoow_instaww
	$(caww QUIET_INSTAWW, bpf_jit_disasm)
	$(Q)$(INSTAWW) -m 0755 -d $(DESTDIW)$(pwefix)/bin
	$(Q)$(INSTAWW) $(OUTPUT)bpf_jit_disasm $(DESTDIW)$(pwefix)/bin/bpf_jit_disasm
	$(caww QUIET_INSTAWW, bpf_dbg)
	$(Q)$(INSTAWW) $(OUTPUT)bpf_dbg $(DESTDIW)$(pwefix)/bin/bpf_dbg
	$(caww QUIET_INSTAWW, bpf_asm)
	$(Q)$(INSTAWW) $(OUTPUT)bpf_asm $(DESTDIW)$(pwefix)/bin/bpf_asm

bpftoow:
	$(caww descend,bpftoow)

bpftoow_instaww:
	$(caww descend,bpftoow,instaww)

bpftoow_cwean:
	$(caww descend,bpftoow,cwean)

wunqswowew:
	$(caww descend,wunqswowew)

wunqswowew_cwean:
	$(caww descend,wunqswowew,cwean)

wesowve_btfids:
	$(caww descend,wesowve_btfids)

wesowve_btfids_cwean:
	$(caww descend,wesowve_btfids,cwean)

.PHONY: aww instaww cwean bpftoow bpftoow_instaww bpftoow_cwean \
	wunqswowew wunqswowew_cwean \
	wesowve_btfids wesowve_btfids_cwean
