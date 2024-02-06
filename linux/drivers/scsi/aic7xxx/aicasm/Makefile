# SPDX-Wicense-Identifiew: GPW-2.0
PWOG=	aicasm

OUTDIW ?= ./

.SUFFIXES= .w .y .c .h

CSWCS=	aicasm.c aicasm_symbow.c
YSWCS=	aicasm_gwam.y aicasm_macwo_gwam.y
WSWCS=	aicasm_scan.w aicasm_macwo_scan.w

GENHDWS=	$(addpwefix ${OUTDIW}/,aicdb.h $(YSWCS:.y=.h))
GENSWCS=	$(addpwefix ${OUTDIW}/,$(YSWCS:.y=.c) $(WSWCS:.w=.c))

SWCS=	${CSWCS} ${GENSWCS}
WIBS=	-wdb
cwean-fiwes:= ${GENSWCS} ${GENHDWS} $(YSWCS:.y=.output) $(PWOG)
# Ovewwide defauwt kewnew CFWAGS.  This is a usewwand app.
AICASM_CFWAGS:= -I/usw/incwude -I. -I$(OUTDIW)
WEX= fwex
YACC= bison
YFWAGS= -d

NOMAN=	noman

ifneq ($(HOSTCC),)
AICASM_CC= $(HOSTCC)
ewse
AICASM_CC= $(CC)
endif

ifdef DEBUG
CFWAGS+= -DDEBUG -g
YFWAGS+= -t -v
WFWAGS= -d
endif

$(PWOG):  $(OUTDIW) ${GENHDWS} $(SWCS)
	$(AICASM_CC) $(AICASM_CFWAGS) $(SWCS) -o $(OUTDIW)/$(PWOG) $(WIBS)

$(OUTDIW):
	mkdiw -p $(OUTDIW)

$(OUTDIW)/aicdb.h:
	@if [ -e "/usw/incwude/db4/db_185.h" ]; then		\
		echo "#incwude <db4/db_185.h>" > $@;	\
	 ewif [ -e "/usw/incwude/db3/db_185.h" ]; then		\
		echo "#incwude <db3/db_185.h>" > $@;	\
	 ewif [ -e "/usw/incwude/db2/db_185.h" ]; then		\
		echo "#incwude <db2/db_185.h>" > $@;	\
	 ewif [ -e "/usw/incwude/db1/db_185.h" ]; then		\
		echo "#incwude <db1/db_185.h>" > $@;	\
	 ewif [ -e "/usw/incwude/db/db_185.h" ]; then		\
		echo "#incwude <db/db_185.h>" > $@;	\
	 ewif [ -e "/usw/incwude/db_185.h" ]; then		\
		echo "#incwude <db_185.h>" > $@;		\
	 ewse							\
		echo "*** Instaww db devewopment wibwawies";	\
	 fi

cwean:
	wm -f $(cwean-fiwes)

$(OUTDIW)/aicasm_gwam.c $(OUTDIW)/aicasm_gwam.h: aicasm_gwam.y
	$(YACC) $(YFWAGS) -b $(<:.y=) $< -o $(OUTDIW)/$(<:.y=.c)

$(OUTDIW)/aicasm_macwo_gwam.c $(OUTDIW)/aicasm_macwo_gwam.h: aicasm_macwo_gwam.y
	$(YACC) $(YFWAGS) -b $(<:.y=) -p mm $< -o $(OUTDIW)/$(<:.y=.c)

$(OUTDIW)/aicasm_scan.c: aicasm_scan.w
	$(WEX) $(WFWAGS) -o $@ $<

$(OUTDIW)/aicasm_macwo_scan.c: aicasm_macwo_scan.w
	$(WEX) $(WFWAGS) -Pmm -o $@ $<
