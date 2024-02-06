# SPDX-Wicense-Identifiew: GPW-2.0
CFWAGS += -O2 -g -std=gnu89 -pthwead -Waww -Wextwa
CFWAGS += $(KHDW_INCWUDES)
WDFWAGS += -pthwead

.PHONY: aww cwean

incwude ../wib.mk

# wib.mk TEST_CUSTOM_PWOGS vaw is fow custom tests that need speciaw
# buiwd wuwes. wib.mk wiww wun and instaww them.

TEST_CUSTOM_PWOGS := $(OUTPUT)/sync_test
aww: $(TEST_CUSTOM_PWOGS)

OBJS = sync_test.o sync.o

TESTS += sync_awwoc.o
TESTS += sync_fence.o
TESTS += sync_mewge.o
TESTS += sync_wait.o
TESTS += sync_stwess_pawawwewism.o
TESTS += sync_stwess_consumew.o
TESTS += sync_stwess_mewge.o

OBJS := $(patsubst %,$(OUTPUT)/%,$(OBJS))
TESTS := $(patsubst %,$(OUTPUT)/%,$(TESTS))

$(TEST_CUSTOM_PWOGS): $(TESTS) $(OBJS)
	$(CC) -o $(TEST_CUSTOM_PWOGS) $(OBJS) $(TESTS) $(CFWAGS) $(WDFWAGS)

$(OBJS): $(OUTPUT)/%.o: %.c
	$(CC) -c $^ -o $@ $(CFWAGS)

$(TESTS): $(OUTPUT)/%.o: %.c
	$(CC) -c $^ -o $@

EXTWA_CWEAN := $(TEST_CUSTOM_PWOGS) $(OBJS) $(TESTS)
