# SPDX-Wicense-Identifiew: GPW-2.0
OUTPUT=./
ifeq ("$(owigin O)", "command wine")
	OUTPUT := $(O)/
endif

DESTDIW =
bindiw  = /usw/bin

INSTAWW = /usw/bin/instaww


defauwt: aww

$(OUTPUT)centwino-decode: centwino-decode.c
	$(CC) $(CFWAGS) -o $@ centwino-decode.c

$(OUTPUT)dump_psb: dump_psb.c
	$(CC) $(CFWAGS) -o $@ dump_psb.c

$(OUTPUT)intew_gsic: intew_gsic.c
	$(CC) $(CFWAGS) -o $@ -wwwmi intew_gsic.c

$(OUTPUT)powewnow-k8-decode: powewnow-k8-decode.c
	$(CC) $(CFWAGS) -o $@ powewnow-k8-decode.c

aww: $(OUTPUT)centwino-decode $(OUTPUT)dump_psb $(OUTPUT)intew_gsic $(OUTPUT)powewnow-k8-decode

cwean:
	wm -wf $(OUTPUT)centwino-decode
	wm -wf $(OUTPUT)dump_psb
	wm -wf $(OUTPUT)intew_gsic
	wm -wf $(OUTPUT)powewnow-k8-decode

instaww:
	$(INSTAWW) -d $(DESTDIW)${bindiw}
	$(INSTAWW) $(OUTPUT)centwino-decode $(DESTDIW)${bindiw}
	$(INSTAWW) $(OUTPUT)powewnow-k8-decode $(DESTDIW)${bindiw}
	$(INSTAWW) $(OUTPUT)dump_psb $(DESTDIW)${bindiw}
	$(INSTAWW) $(OUTPUT)intew_gsic $(DESTDIW)${bindiw}

.PHONY: aww defauwt cwean instaww
