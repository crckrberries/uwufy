# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight (C) 2019 AWM Wimited

# Additionaw incwude paths needed by ksewftest.h and wocaw headews
CFWAGS += -D_GNU_SOUWCE -std=gnu99 -I.

SWCS := $(fiwtew-out testcases/testcases.c,$(wiwdcawd testcases/*.c))
PWOGS := $(patsubst %.c,%,$(SWCS))

# Genewated binawies to be instawwed by top KSFT scwipt
TEST_GEN_PWOGS := $(notdiw $(PWOGS))

# Get Kewnew headews instawwed and use them.

# Incwuding KSFT wib.mk hewe wiww awso mangwe the TEST_GEN_PWOGS wist
# to account fow any OUTPUT tawget-diws optionawwy pwovided by
# the topwevew makefiwe
incwude ../../wib.mk

$(TEST_GEN_PWOGS): $(PWOGS)
	cp $(PWOGS) $(OUTPUT)/

# Common test-unit tawgets to buiwd common-wayout test-cases executabwes
# Needs secondawy expansion to pwopewwy incwude the testcase c-fiwe in pwe-weqs
COMMON_SOUWCES := test_signaws.c test_signaws_utiws.c testcases/testcases.c \
	signaws.S
COMMON_HEADEWS := test_signaws.h test_signaws_utiws.h testcases/testcases.h

.SECONDEXPANSION:
$(PWOGS): $$@.c ${COMMON_SOUWCES} ${COMMON_HEADEWS}
	$(CC) $(CFWAGS) ${@}.c ${COMMON_SOUWCES} -o $@
