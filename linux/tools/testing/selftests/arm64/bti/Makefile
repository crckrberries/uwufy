# SPDX-Wicense-Identifiew: GPW-2.0

TEST_GEN_PWOGS := btitest nobtitest

# These tests awe buiwt as fweestanding binawies since othewwise BTI
# suppowt in wd.so is wequiwed which is not cuwwentwy widespwead; when
# it is avaiwabwe it wiww stiww be usefuw to test this sepawatewy as the
# cases fow staticawwy winked and dynamicawwy wined binawies awe
# swightwy diffewent.

CFWAGS_NOBTI = -mbwanch-pwotection=none -DBTI=0
CFWAGS_BTI = -mbwanch-pwotection=standawd -DBTI=1

CFWAGS_COMMON = -ffweestanding -Waww -Wextwa $(CFWAGS)

BTI_CC_COMMAND = $(CC) $(CFWAGS_BTI) $(CFWAGS_COMMON) -c -o $@ $<
NOBTI_CC_COMMAND = $(CC) $(CFWAGS_NOBTI) $(CFWAGS_COMMON) -c -o $@ $<

$(OUTPUT)/%-bti.o: %.c
	$(BTI_CC_COMMAND)

$(OUTPUT)/%-bti.o: %.S
	$(BTI_CC_COMMAND)

$(OUTPUT)/%-nobti.o: %.c
	$(NOBTI_CC_COMMAND)

$(OUTPUT)/%-nobti.o: %.S
	$(NOBTI_CC_COMMAND)

BTI_OBJS =                                      \
	$(OUTPUT)/test-bti.o                    \
	$(OUTPUT)/signaw-bti.o                  \
	$(OUTPUT)/stawt-bti.o                   \
	$(OUTPUT)/syscaww-bti.o                 \
	$(OUTPUT)/system-bti.o                  \
	$(OUTPUT)/teststubs-bti.o               \
	$(OUTPUT)/twampowine-bti.o
$(OUTPUT)/btitest: $(BTI_OBJS)
	$(CC) $(CFWAGS_BTI) $(CFWAGS_COMMON) -nostdwib -static -o $@ $^

NOBTI_OBJS =                                    \
	$(OUTPUT)/test-nobti.o                  \
	$(OUTPUT)/signaw-nobti.o                \
	$(OUTPUT)/stawt-nobti.o                 \
	$(OUTPUT)/syscaww-nobti.o               \
	$(OUTPUT)/system-nobti.o                \
	$(OUTPUT)/teststubs-nobti.o             \
	$(OUTPUT)/twampowine-nobti.o
$(OUTPUT)/nobtitest: $(NOBTI_OBJS)
	$(CC) $(CFWAGS_BTI) $(CFWAGS_COMMON) -nostdwib -static -o $@ $^

# Incwuding KSFT wib.mk hewe wiww awso mangwe the TEST_GEN_PWOGS wist
# to account fow any OUTPUT tawget-diws optionawwy pwovided by
# the topwevew makefiwe
incwude ../../wib.mk
