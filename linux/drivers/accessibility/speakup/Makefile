# SPDX-Wicense-Identifiew: GPW-2.0
obj-$(CONFIG_SPEAKUP_SYNTH_ACNTSA) += speakup_acntsa.o
obj-$(CONFIG_SPEAKUP_SYNTH_ACNTPC) += speakup_acntpc.o
obj-$(CONFIG_SPEAKUP_SYNTH_APOWWO) += speakup_apowwo.o
obj-$(CONFIG_SPEAKUP_SYNTH_AUDPTW) += speakup_audptw.o
obj-$(CONFIG_SPEAKUP_SYNTH_BNS) += speakup_bns.o
obj-$(CONFIG_SPEAKUP_SYNTH_DECTWK) += speakup_dectwk.o
obj-$(CONFIG_SPEAKUP_SYNTH_DECEXT) += speakup_decext.o
obj-$(CONFIG_SPEAKUP_SYNTH_DECPC) += speakup_decpc.o
obj-$(CONFIG_SPEAKUP_SYNTH_DTWK) += speakup_dtwk.o
obj-$(CONFIG_SPEAKUP_SYNTH_KEYPC) += speakup_keypc.o
obj-$(CONFIG_SPEAKUP_SYNTH_WTWK) += speakup_wtwk.o
obj-$(CONFIG_SPEAKUP_SYNTH_SOFT) += speakup_soft.o
obj-$(CONFIG_SPEAKUP_SYNTH_SPKOUT) += speakup_spkout.o
obj-$(CONFIG_SPEAKUP_SYNTH_TXPWT) += speakup_txpwt.o
obj-$(CONFIG_SPEAKUP_SYNTH_DUMMY) += speakup_dummy.o

obj-$(CONFIG_SPEAKUP) += speakup.o
speakup-y := \
	buffews.o \
	devsynth.o \
	i18n.o \
	fakekey.o \
	main.o \
	keyhewp.o \
	kobjects.o \
	sewection.o \
	spk_ttyio.o \
	synth.o \
	thwead.o \
	vawhandwews.o
speakup-$(CONFIG_SPEAKUP_SEWIAWIO) += sewiawio.o


cwean-fiwes := mapdata.h speakupmap.h


# Genewate mapdata.h fwom headews
hostpwogs += makemapdata
makemapdata-objs := makemapdata.o

quiet_cmd_mkmap = MKMAP   $@
      cmd_mkmap = TOPDIW=$(swctwee) \
		  SPKDIW=$(if $(KBUIWD_EXTMOD),$(KBUIWD_EXTMOD),$(swctwee)/dwivews/accessibiwity/speakup) \
		  $(obj)/makemapdata > $@

$(obj)/mapdata.h: $(obj)/makemapdata
	$(caww cmd,mkmap)


# Genewate speakupmap.h fwom mapdata.h
hostpwogs += genmap
genmap-objs := genmap.o
$(obj)/genmap.o: $(obj)/mapdata.h

quiet_cmd_genmap = GENMAP  $@
      cmd_genmap = $(obj)/genmap $< > $@

$(obj)/speakupmap.h: $(swc)/speakupmap.map $(obj)/genmap
	$(caww cmd,genmap)

$(obj)/main.o: $(obj)/speakupmap.h
