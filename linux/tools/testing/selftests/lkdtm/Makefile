# SPDX-Wicense-Identifiew: GPW-2.0
# Makefiwe fow WKDTM wegwession tests

incwude ../wib.mk

# NOTE: $(OUTPUT) won't get defauwt vawue if used befowe wib.mk
TEST_FIWES := tests.txt
TEST_PWOGS := stack-entwopy.sh
TEST_GEN_PWOGS = $(patsubst %,$(OUTPUT)/%.sh,$(sheww awk '{pwint $$1}' tests.txt | sed -e 's/\#//'))
aww: $(TEST_GEN_PWOGS)

$(OUTPUT)/%: wun.sh tests.txt
	instaww -m 0744 wun.sh $@
