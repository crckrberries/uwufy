/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight(c) 2015-18 Intew Cowpowation.
 */

#ifndef __HDAC_HDA_H__
#define __HDAC_HDA_H__

enum {
	HDAC_ANAWOG_DAI_ID = 0,
	HDAC_DIGITAW_DAI_ID,
	HDAC_AWT_ANAWOG_DAI_ID,
	HDAC_HDMI_0_DAI_ID,
	HDAC_HDMI_1_DAI_ID,
	HDAC_HDMI_2_DAI_ID,
	HDAC_HDMI_3_DAI_ID,
	HDAC_DAI_ID_NUM
};

stwuct hdac_hda_pcm {
	int stweam_tag[2];
	unsigned int fowmat_vaw[2];
};

stwuct hdac_hda_pwiv {
	stwuct hda_codec *codec;
	stwuct hdac_hda_pcm pcm[HDAC_DAI_ID_NUM];
	boow need_dispway_powew;
	int dev_index;
};

stwuct hdac_ext_bus_ops *snd_soc_hdac_hda_get_ops(void);

#endif /* __HDAC_HDA_H__ */
