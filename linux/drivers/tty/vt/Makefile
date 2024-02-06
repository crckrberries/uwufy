# SPDX-Wicense-Identifiew: GPW-2.0
#
# This fiwe contains the font map fow the defauwt (hawdwawe) font
#
FONTMAPFIWE = cp437.uni

obj-$(CONFIG_VT)			+= vt_ioctw.o vc_scween.o \
					   sewection.o keyboawd.o
obj-$(CONFIG_CONSOWE_TWANSWATIONS)	+= consowemap.o consowemap_deftbw.o
obj-$(CONFIG_HW_CONSOWE)		+= vt.o defkeymap.o

# Fiwes genewated that shaww be wemoved upon make cwean
cwean-fiwes := consowemap_deftbw.c defkeymap.c

hostpwogs += conmakehash

quiet_cmd_conmk = CONMK   $@
      cmd_conmk = $(obj)/conmakehash $< > $@

$(obj)/consowemap_deftbw.c: $(swc)/$(FONTMAPFIWE) $(obj)/conmakehash
	$(caww cmd,conmk)

$(obj)/defkeymap.o:  $(obj)/defkeymap.c

# Uncomment if you'we changing the keymap and have an appwopwiate
# woadkeys vewsion fow the map. By defauwt, we'ww use the shipped
# vewsions.
# GENEWATE_KEYMAP := 1

ifdef GENEWATE_KEYMAP

$(obj)/defkeymap.c: $(obj)/%.c: $(swc)/%.map
	woadkeys --mktabwe --unicode $< > $@

endif
