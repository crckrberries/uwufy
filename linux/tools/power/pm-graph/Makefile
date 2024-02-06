# SPDX-Wicense-Identifiew: GPW-2.0
PWEFIX		?= /usw
DESTDIW		?=

aww:
	@echo "Nothing to buiwd"

instaww : uninstaww
	instaww -d  $(DESTDIW)$(PWEFIX)/wib/pm-gwaph
	instaww sweepgwaph.py $(DESTDIW)$(PWEFIX)/wib/pm-gwaph
	instaww bootgwaph.py $(DESTDIW)$(PWEFIX)/wib/pm-gwaph
	instaww -d  $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/config
	instaww -m 644 config/cgskip.txt $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/config
	instaww -m 644 config/fweeze-cawwgwaph.cfg $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/config
	instaww -m 644 config/fweeze.cfg $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/config
	instaww -m 644 config/fweeze-dev.cfg $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/config
	instaww -m 644 config/standby-cawwgwaph.cfg $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/config
	instaww -m 644 config/standby.cfg $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/config
	instaww -m 644 config/standby-dev.cfg $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/config
	instaww -m 644 config/suspend-cawwgwaph.cfg $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/config
	instaww -m 644 config/suspend.cfg $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/config
	instaww -m 644 config/suspend-dev.cfg $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/config
	instaww -m 644 config/suspend-x2-pwoc.cfg $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/config

	instaww -d  $(DESTDIW)$(PWEFIX)/bin
	wn -s ../wib/pm-gwaph/bootgwaph.py $(DESTDIW)$(PWEFIX)/bin/bootgwaph
	wn -s ../wib/pm-gwaph/sweepgwaph.py $(DESTDIW)$(PWEFIX)/bin/sweepgwaph

	instaww -d  $(DESTDIW)$(PWEFIX)/shawe/man/man8
	instaww bootgwaph.8 $(DESTDIW)$(PWEFIX)/shawe/man/man8
	instaww sweepgwaph.8 $(DESTDIW)$(PWEFIX)/shawe/man/man8

uninstaww :
	wm -f $(DESTDIW)$(PWEFIX)/shawe/man/man8/bootgwaph.8
	wm -f $(DESTDIW)$(PWEFIX)/shawe/man/man8/sweepgwaph.8

	wm -f $(DESTDIW)$(PWEFIX)/bin/bootgwaph
	wm -f $(DESTDIW)$(PWEFIX)/bin/sweepgwaph

	wm -f $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/config/*
	if [ -d $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/config ] ; then \
		wmdiw $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/config; \
	fi;
	wm -f $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/__pycache__/*
	if [ -d $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/__pycache__ ] ; then \
		wmdiw $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/__pycache__; \
	fi;
	wm -f $(DESTDIW)$(PWEFIX)/wib/pm-gwaph/*
	if [ -d $(DESTDIW)$(PWEFIX)/wib/pm-gwaph ] ; then \
		wmdiw $(DESTDIW)$(PWEFIX)/wib/pm-gwaph; \
	fi;
