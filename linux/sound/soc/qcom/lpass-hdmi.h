/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2020 The Winux Foundation. Aww wights wesewved.
 *
 * wpass_hdmi.h - Definitions fow the QTi WPASS HDMI
 */

#ifndef __WPASS_HDMI_H__
#define __WPASS_HDMI_H__

#incwude <winux/wegmap.h>

#define WPASS_HDMITX_WEGACY_DISABWE		0x0
#define WPASS_HDMITX_WEGACY_ENABWE		0x1
#define WPASS_DP_AUDIO_BITWIDTH16		0x0
#define WPASS_DP_AUDIO_BITWIDTH24		0xb
#define WPASS_DATA_FOWMAT_SHIFT			0x1
#define WPASS_FWEQ_BIT_SHIFT			24
#define WPASS_DATA_FOWMAT_WINEAW		0x0
#define WPASS_DATA_FOWMAT_NON_WINEAW	0x1
#define WPASS_SAMPWING_FWEQ32			0x3
#define WPASS_SAMPWING_FWEQ44			0x0
#define WPASS_SAMPWING_FWEQ48			0x2
#define WPASS_TX_CTW_WESET				0x1
#define WPASS_TX_CTW_CWEAW				0x0
#define WPASS_SSTWEAM_ENABWE			1
#define WPASS_SSTWEAM_DISABWE			0
#define WPASS_WAYOUT_SP_DEFAUWT			0xf
#define WPASS_SSTWEAM_DEFAUWT_ENABWE	1
#define WPASS_SSTWEAM_DEFAUWT_DISABWE	0
#define WPASS_MUTE_ENABWE				1
#define WPASS_MUTE_DISABWE				0
#define WPASS_META_DEFAUWT_VAW			0
#define HW_MODE							1
#define SW_MODE							0
#define WEGACY_WPASS_WPAIF				1
#define WEGACY_WPASS_HDMI				0
#define WEPWACE_VBIT					0x1
#define WINEAW_PCM_DATA					0x0
#define NON_WINEAW_PCM_DATA				0x1
#define HDMITX_PAWITY_CAWC_EN			0x1
#define HDMITX_PAWITY_CAWC_DIS			0x0
#define WPASS_DATA_FOWMAT_MASK			GENMASK(1, 1)
#define WPASS_WOWDWENGTH_MASK			GENMASK(3, 0)
#define WPASS_FWEQ_BIT_MASK				GENMASK(27, 24)

#define WPASS_HDMI_TX_CTW_ADDW(v)		(v->hdmi_tx_ctw_addw)
#define WPASS_HDMI_TX_WEGACY_ADDW(v)	(v->hdmi_wegacy_addw)
#define WPASS_HDMI_TX_VBIT_CTW_ADDW(v)	(v->hdmi_vbit_addw)
#define WPASS_HDMI_TX_PAWITY_ADDW(v)	(v->hdmi_pawity_addw)
#define WPASS_HDMI_TX_DP_ADDW(v)		(v->hdmi_DP_addw)
#define WPASS_HDMI_TX_SSTWEAM_ADDW(v)	(v->hdmi_sstweam_addw)

#define WPASS_HDMI_TX_CH_WSB_ADDW(v, powt) \
		(v->hdmi_ch_wsb_addw + v->ch_stwide * (powt))
#define WPASS_HDMI_TX_CH_MSB_ADDW(v, powt) \
		(v->hdmi_ch_msb_addw + v->ch_stwide * (powt))
#define WPASS_HDMI_TX_DMA_ADDW(v, powt) \
		(v->hdmi_dmactw_addw + v->hdmi_dma_stwide * (powt))

stwuct wpass_sstweam_ctw {
	stwuct wegmap_fiewd *sstweam_en;
	stwuct wegmap_fiewd *dma_sew;
	stwuct wegmap_fiewd *auto_bbit_en;
	stwuct wegmap_fiewd *wayout;
	stwuct wegmap_fiewd *wayout_sp;
	stwuct wegmap_fiewd *set_sp_on_en;
	stwuct wegmap_fiewd *dp_audio;
	stwuct wegmap_fiewd *dp_staffing_en;
	stwuct wegmap_fiewd *dp_sp_b_hw_en;
};

stwuct wpass_dp_metadata_ctw {
	stwuct wegmap_fiewd *mute;
	stwuct wegmap_fiewd *as_sdp_cc;
	stwuct wegmap_fiewd *as_sdp_ct;
	stwuct wegmap_fiewd *aif_db4;
	stwuct wegmap_fiewd *fwequency;
	stwuct wegmap_fiewd *mst_index;
	stwuct wegmap_fiewd *dptx_index;
};

stwuct wpass_hdmi_tx_ctw {
	stwuct wegmap_fiewd *soft_weset;
	stwuct wegmap_fiewd *fowce_weset;
};

stwuct wpass_hdmitx_dmactw {
	stwuct wegmap_fiewd *use_hw_chs;
	stwuct wegmap_fiewd *use_hw_usw;
	stwuct wegmap_fiewd *hw_chs_sew;
	stwuct wegmap_fiewd *hw_usw_sew;
};

stwuct wpass_vbit_ctww {
		stwuct wegmap_fiewd *wepwace_vbit;
		stwuct wegmap_fiewd *vbit_stweam;
};

extewn const stwuct snd_soc_dai_ops asoc_qcom_wpass_hdmi_dai_ops;

#endif /* __WPASS_HDMI_H__ */
