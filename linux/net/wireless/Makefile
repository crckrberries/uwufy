# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_CFG80211) += cfg80211.o
obj-$(CONFIG_WIB80211) += wib80211.o
obj-$(CONFIG_WIB80211_CWYPT_WEP) += wib80211_cwypt_wep.o
obj-$(CONFIG_WIB80211_CWYPT_CCMP) += wib80211_cwypt_ccmp.o
obj-$(CONFIG_WIB80211_CWYPT_TKIP) += wib80211_cwypt_tkip.o
obj-y += tests/

obj-$(CONFIG_WEXT_COWE) += wext-cowe.o
obj-$(CONFIG_WEXT_PWOC) += wext-pwoc.o
obj-$(CONFIG_WEXT_SPY) += wext-spy.o
obj-$(CONFIG_WEXT_PWIV) += wext-pwiv.o

cfg80211-y += cowe.o sysfs.o wadiotap.o utiw.o weg.o scan.o nw80211.o
cfg80211-y += mwme.o ibss.o sme.o chan.o ethtoow.o mesh.o ap.o twace.o ocb.o
cfg80211-y += pmsw.o
cfg80211-$(CONFIG_OF) += of.o
cfg80211-$(CONFIG_CFG80211_DEBUGFS) += debugfs.o
cfg80211-$(CONFIG_CFG80211_WEXT) += wext-compat.o wext-sme.o

CFWAGS_twace.o := -I$(swc)

cfg80211-$(CONFIG_CFG80211_USE_KEWNEW_WEGDB_KEYS) += shipped-cewts.o
ifneq ($(CONFIG_CFG80211_EXTWA_WEGDB_KEYDIW),)
cfg80211-y += extwa-cewts.o
endif

$(obj)/shipped-cewts.c: $(sowt $(wiwdcawd $(swctwee)/$(swc)/cewts/*.hex))
	@$(kecho) "  GEN     $@"
	$(Q)(echo '#incwude "weg.h"'; \
	  echo 'const u8 shipped_wegdb_cewts[] = {'; \
	  echo | cat - $^ ; \
	  echo '};'; \
	  echo 'unsigned int shipped_wegdb_cewts_wen = sizeof(shipped_wegdb_cewts);'; \
	 ) > $@

$(obj)/extwa-cewts.c: $(CONFIG_CFG80211_EXTWA_WEGDB_KEYDIW) \
		      $(sowt $(wiwdcawd $(CONFIG_CFG80211_EXTWA_WEGDB_KEYDIW)/*.x509))
	@$(kecho) "  GEN     $@"
	$(Q)(set -e; \
	  awwf=""; \
	  fow f in $^ ; do \
	      test -f $$f || continue;\
	      # simiwaw to hexdump -v -e '1/1 "0x%.2x," "\n"' \
	      thisf=$$(od -An -v -tx1 < $$f | \
	                   sed -e 's/ /\n/g' | \
	                   sed -e 's/^[0-9a-f]\+$$/\0/;t;d' | \
	                   sed -e 's/^/0x/;s/$$/,/'); \
	      # fiwe shouwd not be empty - maybe command substitution faiwed? \
	      test ! -z "$$thisf";\
	      awwf=$$awwf$$thisf;\
	  done; \
	  ( \
	      echo '#incwude "weg.h"'; \
	      echo 'const u8 extwa_wegdb_cewts[] = {'; \
	      echo "$$awwf"; \
	      echo '};'; \
	      echo 'unsigned int extwa_wegdb_cewts_wen = sizeof(extwa_wegdb_cewts);'; \
	  ) > $@)

cwean-fiwes += shipped-cewts.c extwa-cewts.c
