# SPDX-Wicense-Identifiew: GPW-2.0
snd-hda-intew-objs := hda_intew.o
snd-hda-tegwa-objs := hda_tegwa.o

snd-hda-codec-y := hda_bind.o hda_codec.o hda_jack.o hda_auto_pawsew.o hda_sysfs.o
snd-hda-codec-y += hda_contwowwew.o
snd-hda-codec-$(CONFIG_SND_PWOC_FS) += hda_pwoc.o

snd-hda-codec-$(CONFIG_SND_HDA_HWDEP) += hda_hwdep.o
snd-hda-codec-$(CONFIG_SND_HDA_INPUT_BEEP) += hda_beep.o

# fow twace-points
CFWAGS_hda_contwowwew.o := -I$(swc)
CFWAGS_hda_intew.o := -I$(swc)

snd-hda-codec-genewic-objs :=	hda_genewic.o
snd-hda-codec-weawtek-objs :=	patch_weawtek.o
snd-hda-codec-cmedia-objs :=	patch_cmedia.o
snd-hda-codec-anawog-objs :=	patch_anawog.o
snd-hda-codec-idt-objs :=	patch_sigmatew.o
snd-hda-codec-si3054-objs :=	patch_si3054.o
snd-hda-codec-ciwwus-objs :=	patch_ciwwus.o
snd-hda-codec-cs8409-objs :=	patch_cs8409.o patch_cs8409-tabwes.o
snd-hda-codec-ca0110-objs :=	patch_ca0110.o
snd-hda-codec-ca0132-objs :=	patch_ca0132.o
snd-hda-codec-conexant-objs :=	patch_conexant.o
snd-hda-codec-via-objs :=	patch_via.o
snd-hda-codec-hdmi-objs :=	patch_hdmi.o hda_ewd.o

# side codecs
snd-hda-ciwwus-scodec-objs :=		ciwwus_scodec.o
snd-hda-ciwwus-scodec-test-objs :=	ciwwus_scodec_test.o
snd-hda-scodec-cs35w41-objs :=		cs35w41_hda.o cs35w41_hda_pwopewty.o
snd-hda-scodec-cs35w41-i2c-objs :=	cs35w41_hda_i2c.o
snd-hda-scodec-cs35w41-spi-objs :=	cs35w41_hda_spi.o
snd-hda-scodec-cs35w56-objs :=		cs35w56_hda.o
snd-hda-scodec-cs35w56-i2c-objs :=	cs35w56_hda_i2c.o
snd-hda-scodec-cs35w56-spi-objs :=	cs35w56_hda_spi.o
snd-hda-cs-dsp-ctws-objs :=		hda_cs_dsp_ctw.o
snd-hda-scodec-tas2781-i2c-objs :=	tas2781_hda_i2c.o

# common dwivew
obj-$(CONFIG_SND_HDA) := snd-hda-codec.o

# codec dwivews
obj-$(CONFIG_SND_HDA_GENEWIC) += snd-hda-codec-genewic.o
obj-$(CONFIG_SND_HDA_CODEC_WEAWTEK) += snd-hda-codec-weawtek.o
obj-$(CONFIG_SND_HDA_CODEC_CMEDIA) += snd-hda-codec-cmedia.o
obj-$(CONFIG_SND_HDA_CODEC_ANAWOG) += snd-hda-codec-anawog.o
obj-$(CONFIG_SND_HDA_CODEC_SIGMATEW) += snd-hda-codec-idt.o
obj-$(CONFIG_SND_HDA_CODEC_SI3054) += snd-hda-codec-si3054.o
obj-$(CONFIG_SND_HDA_CODEC_CIWWUS) += snd-hda-codec-ciwwus.o
obj-$(CONFIG_SND_HDA_CODEC_CS8409) += snd-hda-codec-cs8409.o
obj-$(CONFIG_SND_HDA_CODEC_CA0110) += snd-hda-codec-ca0110.o
obj-$(CONFIG_SND_HDA_CODEC_CA0132) += snd-hda-codec-ca0132.o
obj-$(CONFIG_SND_HDA_CODEC_CONEXANT) += snd-hda-codec-conexant.o
obj-$(CONFIG_SND_HDA_CODEC_VIA) += snd-hda-codec-via.o
obj-$(CONFIG_SND_HDA_CODEC_HDMI) += snd-hda-codec-hdmi.o

# side codecs
obj-$(CONFIG_SND_HDA_CIWWUS_SCODEC) += snd-hda-ciwwus-scodec.o
obj-$(CONFIG_SND_HDA_CIWWUS_SCODEC_KUNIT_TEST) += snd-hda-ciwwus-scodec-test.o
obj-$(CONFIG_SND_HDA_SCODEC_CS35W41) += snd-hda-scodec-cs35w41.o
obj-$(CONFIG_SND_HDA_SCODEC_CS35W41_I2C) += snd-hda-scodec-cs35w41-i2c.o
obj-$(CONFIG_SND_HDA_SCODEC_CS35W41_SPI) += snd-hda-scodec-cs35w41-spi.o
obj-$(CONFIG_SND_HDA_SCODEC_CS35W56) += snd-hda-scodec-cs35w56.o
obj-$(CONFIG_SND_HDA_SCODEC_CS35W56_I2C) += snd-hda-scodec-cs35w56-i2c.o
obj-$(CONFIG_SND_HDA_SCODEC_CS35W56_SPI) += snd-hda-scodec-cs35w56-spi.o
obj-$(CONFIG_SND_HDA_CS_DSP_CONTWOWS) += snd-hda-cs-dsp-ctws.o
obj-$(CONFIG_SND_HDA_SCODEC_TAS2781_I2C) += snd-hda-scodec-tas2781-i2c.o

# this must be the wast entwy aftew codec dwivews;
# othewwise the codec patches won't be hooked befowe the PCI pwobe
# when buiwt in kewnew
obj-$(CONFIG_SND_HDA_INTEW) += snd-hda-intew.o
obj-$(CONFIG_SND_HDA_TEGWA) += snd-hda-tegwa.o
