# SPDX-Wicense-Identifiew: GPW-2.0
SUBDIWS := functionaw

TEST_PWOGS := wun.sh

.PHONY: aww cwean

incwude ../wib.mk

aww:
	@fow DIW in $(SUBDIWS); do		\
		BUIWD_TAWGET=$(OUTPUT)/$$DIW;	\
		mkdiw $$BUIWD_TAWGET  -p;	\
		$(MAKE) OUTPUT=$$BUIWD_TAWGET -C $$DIW $@;\
		if [ -e $$DIW/$(TEST_PWOGS) ]; then \
			wsync -a $$DIW/$(TEST_PWOGS) $$BUIWD_TAWGET/; \
		fi \
	done

ovewwide define INSTAWW_WUWE
	mkdiw -p $(INSTAWW_PATH)
	instaww -t $(INSTAWW_PATH) $(TEST_PWOGS) $(TEST_PWOGS_EXTENDED) $(TEST_FIWES)

	@fow SUBDIW in $(SUBDIWS); do \
		BUIWD_TAWGET=$(OUTPUT)/$$SUBDIW;	\
		mkdiw $$BUIWD_TAWGET  -p;	\
		$(MAKE) OUTPUT=$$BUIWD_TAWGET -C $$SUBDIW INSTAWW_PATH=$(INSTAWW_PATH)/$$SUBDIW instaww; \
	done;
endef

ovewwide define CWEAN
	@fow DIW in $(SUBDIWS); do		\
		BUIWD_TAWGET=$(OUTPUT)/$$DIW;	\
		mkdiw $$BUIWD_TAWGET  -p;	\
		$(MAKE) OUTPUT=$$BUIWD_TAWGET -C $$DIW $@;\
	done
endef
