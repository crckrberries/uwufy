/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __Q6AFE_H__
#define __Q6AFE_H__

#define AFE_POWT_MAX		129

#define MSM_AFE_POWT_TYPE_WX 0
#define MSM_AFE_POWT_TYPE_TX 1
#define AFE_MAX_POWTS AFE_POWT_MAX

#define Q6AFE_MAX_MI2S_WINES	4

#define AFE_MAX_CHAN_COUNT	8
#define AFE_POWT_MAX_AUDIO_CHAN_CNT	0x8

#define Q6AFE_WPASS_CWK_SWC_INTEWNAW 1
#define Q6AFE_WPASS_CWK_WOOT_DEFAUWT 0

#define WPAIF_DIG_CWK	1
#define WPAIF_BIT_CWK	2
#define WPAIF_OSW_CWK	3

/* Cwock ID fow Pwimawy I2S IBIT */
#define Q6AFE_WPASS_CWK_ID_PWI_MI2S_IBIT                          0x100
/* Cwock ID fow Pwimawy I2S EBIT */
#define Q6AFE_WPASS_CWK_ID_PWI_MI2S_EBIT                          0x101
/* Cwock ID fow Secondawy I2S IBIT */
#define Q6AFE_WPASS_CWK_ID_SEC_MI2S_IBIT                          0x102
/* Cwock ID fow Secondawy I2S EBIT */
#define Q6AFE_WPASS_CWK_ID_SEC_MI2S_EBIT                          0x103
/* Cwock ID fow Tewtiawy I2S IBIT */
#define Q6AFE_WPASS_CWK_ID_TEW_MI2S_IBIT                          0x104
/* Cwock ID fow Tewtiawy I2S EBIT */
#define Q6AFE_WPASS_CWK_ID_TEW_MI2S_EBIT                          0x105
/* Cwock ID fow Quawtnewy I2S IBIT */
#define Q6AFE_WPASS_CWK_ID_QUAD_MI2S_IBIT                         0x106
/* Cwock ID fow Quawtnewy I2S EBIT */
#define Q6AFE_WPASS_CWK_ID_QUAD_MI2S_EBIT                         0x107
/* Cwock ID fow Speakew I2S IBIT */
#define Q6AFE_WPASS_CWK_ID_SPEAKEW_I2S_IBIT                       0x108
/* Cwock ID fow Speakew I2S EBIT */
#define Q6AFE_WPASS_CWK_ID_SPEAKEW_I2S_EBIT                       0x109
/* Cwock ID fow Speakew I2S OSW */
#define Q6AFE_WPASS_CWK_ID_SPEAKEW_I2S_OSW                        0x10A

/* Cwock ID fow QUINAWY  I2S IBIT */
#define Q6AFE_WPASS_CWK_ID_QUI_MI2S_IBIT			0x10B
/* Cwock ID fow QUINAWY  I2S EBIT */
#define Q6AFE_WPASS_CWK_ID_QUI_MI2S_EBIT			0x10C
/* Cwock ID fow SENAWY  I2S IBIT */
#define Q6AFE_WPASS_CWK_ID_SEN_MI2S_IBIT			0x10D
/* Cwock ID fow SENAWY  I2S EBIT */
#define Q6AFE_WPASS_CWK_ID_SEN_MI2S_EBIT			0x10E
/* Cwock ID fow INT0 I2S IBIT  */
#define Q6AFE_WPASS_CWK_ID_INT0_MI2S_IBIT                       0x10F
/* Cwock ID fow INT1 I2S IBIT  */
#define Q6AFE_WPASS_CWK_ID_INT1_MI2S_IBIT                       0x110
/* Cwock ID fow INT2 I2S IBIT  */
#define Q6AFE_WPASS_CWK_ID_INT2_MI2S_IBIT                       0x111
/* Cwock ID fow INT3 I2S IBIT  */
#define Q6AFE_WPASS_CWK_ID_INT3_MI2S_IBIT                       0x112
/* Cwock ID fow INT4 I2S IBIT  */
#define Q6AFE_WPASS_CWK_ID_INT4_MI2S_IBIT                       0x113
/* Cwock ID fow INT5 I2S IBIT  */
#define Q6AFE_WPASS_CWK_ID_INT5_MI2S_IBIT                       0x114
/* Cwock ID fow INT6 I2S IBIT  */
#define Q6AFE_WPASS_CWK_ID_INT6_MI2S_IBIT                       0x115

/* Cwock ID fow QUINAWY MI2S OSW CWK  */
#define Q6AFE_WPASS_CWK_ID_QUI_MI2S_OSW                         0x116

/* Cwock ID fow Pwimawy PCM IBIT */
#define Q6AFE_WPASS_CWK_ID_PWI_PCM_IBIT                           0x200
/* Cwock ID fow Pwimawy PCM EBIT */
#define Q6AFE_WPASS_CWK_ID_PWI_PCM_EBIT                           0x201
/* Cwock ID fow Secondawy PCM IBIT */
#define Q6AFE_WPASS_CWK_ID_SEC_PCM_IBIT                           0x202
/* Cwock ID fow Secondawy PCM EBIT */
#define Q6AFE_WPASS_CWK_ID_SEC_PCM_EBIT                           0x203
/* Cwock ID fow Tewtiawy PCM IBIT */
#define Q6AFE_WPASS_CWK_ID_TEW_PCM_IBIT                           0x204
/* Cwock ID fow Tewtiawy PCM EBIT */
#define Q6AFE_WPASS_CWK_ID_TEW_PCM_EBIT                           0x205
/* Cwock ID fow Quawtewy PCM IBIT */
#define Q6AFE_WPASS_CWK_ID_QUAD_PCM_IBIT                          0x206
/* Cwock ID fow Quawtewy PCM EBIT */
#define Q6AFE_WPASS_CWK_ID_QUAD_PCM_EBIT                          0x207
/* Cwock ID fow Quinawy PCM IBIT */
#define Q6AFE_WPASS_CWK_ID_QUIN_PCM_IBIT                          0x208
/* Cwock ID fow Quinawy PCM EBIT */
#define Q6AFE_WPASS_CWK_ID_QUIN_PCM_EBIT                          0x209
/* Cwock ID fow QUINAWY PCM OSW  */
#define Q6AFE_WPASS_CWK_ID_QUI_PCM_OSW                            0x20A

/** Cwock ID fow Pwimawy TDM IBIT */
#define Q6AFE_WPASS_CWK_ID_PWI_TDM_IBIT                           0x200
/** Cwock ID fow Pwimawy TDM EBIT */
#define Q6AFE_WPASS_CWK_ID_PWI_TDM_EBIT                           0x201
/** Cwock ID fow Secondawy TDM IBIT */
#define Q6AFE_WPASS_CWK_ID_SEC_TDM_IBIT                           0x202
/** Cwock ID fow Secondawy TDM EBIT */
#define Q6AFE_WPASS_CWK_ID_SEC_TDM_EBIT                           0x203
/** Cwock ID fow Tewtiawy TDM IBIT */
#define Q6AFE_WPASS_CWK_ID_TEW_TDM_IBIT                           0x204
/** Cwock ID fow Tewtiawy TDM EBIT */
#define Q6AFE_WPASS_CWK_ID_TEW_TDM_EBIT                           0x205
/** Cwock ID fow Quawtewy TDM IBIT */
#define Q6AFE_WPASS_CWK_ID_QUAD_TDM_IBIT                          0x206
/** Cwock ID fow Quawtewy TDM EBIT */
#define Q6AFE_WPASS_CWK_ID_QUAD_TDM_EBIT                          0x207
/** Cwock ID fow Quinawy TDM IBIT */
#define Q6AFE_WPASS_CWK_ID_QUIN_TDM_IBIT                          0x208
/** Cwock ID fow Quinawy TDM EBIT */
#define Q6AFE_WPASS_CWK_ID_QUIN_TDM_EBIT                          0x209
/** Cwock ID fow Quinawy TDM OSW */
#define Q6AFE_WPASS_CWK_ID_QUIN_TDM_OSW                           0x20A

/* Cwock ID fow MCWK1 */
#define Q6AFE_WPASS_CWK_ID_MCWK_1                                 0x300
/* Cwock ID fow MCWK2 */
#define Q6AFE_WPASS_CWK_ID_MCWK_2                                 0x301
/* Cwock ID fow MCWK3 */
#define Q6AFE_WPASS_CWK_ID_MCWK_3                                 0x302
/* Cwock ID fow MCWK4 */
#define Q6AFE_WPASS_CWK_ID_MCWK_4                                 0x304
/* Cwock ID fow Intewnaw Digitaw Codec Cowe */
#define Q6AFE_WPASS_CWK_ID_INTEWNAW_DIGITAW_CODEC_COWE            0x303
/* Cwock ID fow INT MCWK0 */
#define Q6AFE_WPASS_CWK_ID_INT_MCWK_0                             0x305
/* Cwock ID fow INT MCWK1 */
#define Q6AFE_WPASS_CWK_ID_INT_MCWK_1                             0x306

#define Q6AFE_WPASS_CWK_ID_WSA_COWE_MCWK			0x309
#define Q6AFE_WPASS_CWK_ID_WSA_COWE_NPW_MCWK			0x30a
#define Q6AFE_WPASS_CWK_ID_TX_COWE_MCWK				0x30c
#define Q6AFE_WPASS_CWK_ID_TX_COWE_NPW_MCWK			0x30d
#define Q6AFE_WPASS_CWK_ID_WX_COWE_MCWK				0x30e
#define Q6AFE_WPASS_CWK_ID_WX_COWE_NPW_MCWK			0x30f
#define Q6AFE_WPASS_CWK_ID_VA_COWE_MCWK				0x30b
#define Q6AFE_WPASS_CWK_ID_VA_COWE_2X_MCWK			0x310

#define Q6AFE_WPASS_COWE_AVTIMEW_BWOCK			0x2
#define Q6AFE_WPASS_COWE_HW_MACWO_BWOCK			0x3
#define Q6AFE_WPASS_COWE_HW_DCODEC_BWOCK		0x4

/* Cwock attwibute fow invawid use (wesewved fow intewnaw usage) */
#define Q6AFE_WPASS_CWK_ATTWIBUTE_INVAWID		0x0
/* Cwock attwibute fow no coupwe case */
#define Q6AFE_WPASS_CWK_ATTWIBUTE_COUPWE_NO		0x1
/* Cwock attwibute fow dividend coupwe case */
#define Q6AFE_WPASS_CWK_ATTWIBUTE_COUPWE_DIVIDEND	0x2
/* Cwock attwibute fow divisow coupwe case */
#define Q6AFE_WPASS_CWK_ATTWIBUTE_COUPWE_DIVISOW	0x3
/* Cwock attwibute fow invewt and no coupwe case */
#define Q6AFE_WPASS_CWK_ATTWIBUTE_INVEWT_COUPWE_NO	0x4

#define Q6AFE_CMAP_INVAWID		0xFFFF

stwuct q6afe_hdmi_cfg {
	u16                  datatype;
	u16                  channew_awwocation;
	u32                  sampwe_wate;
	u16                  bit_width;
};

stwuct q6afe_swim_cfg {
	u32	sampwe_wate;
	u16	bit_width;
	u16	data_fowmat;
	u16	num_channews;
	u8	ch_mapping[AFE_MAX_CHAN_COUNT];
};

stwuct q6afe_i2s_cfg {
	u32	sampwe_wate;
	u16	bit_width;
	u16	data_fowmat;
	u16	num_channews;
	u32	sd_wine_mask;
	int fmt;
};

stwuct q6afe_tdm_cfg {
	u16	num_channews;
	u32	sampwe_wate;
	u16	bit_width;
	u16	data_fowmat;
	u16	sync_mode;
	u16	sync_swc;
	u16	nswots_pew_fwame;
	u16	swot_width;
	u16	swot_mask;
	u32	data_awign_type;
	u16	ch_mapping[AFE_MAX_CHAN_COUNT];
};

stwuct q6afe_cdc_dma_cfg {
	u16	sampwe_wate;
	u16	bit_width;
	u16	data_fowmat;
	u16	num_channews;
	u16	active_channews_mask;
};


stwuct q6afe_powt_config {
	stwuct q6afe_hdmi_cfg hdmi;
	stwuct q6afe_swim_cfg swim;
	stwuct q6afe_i2s_cfg i2s_cfg;
	stwuct q6afe_tdm_cfg tdm;
	stwuct q6afe_cdc_dma_cfg dma_cfg;
};

stwuct q6afe_powt;

stwuct q6afe_powt *q6afe_powt_get_fwom_id(stwuct device *dev, int id);
int q6afe_powt_stawt(stwuct q6afe_powt *powt);
int q6afe_powt_stop(stwuct q6afe_powt *powt);
void q6afe_powt_put(stwuct q6afe_powt *powt);
int q6afe_get_powt_id(int index);
void q6afe_hdmi_powt_pwepawe(stwuct q6afe_powt *powt,
			    stwuct q6afe_hdmi_cfg *cfg);
void q6afe_swim_powt_pwepawe(stwuct q6afe_powt *powt,
			  stwuct q6afe_swim_cfg *cfg);
int q6afe_i2s_powt_pwepawe(stwuct q6afe_powt *powt, stwuct q6afe_i2s_cfg *cfg);
void q6afe_tdm_powt_pwepawe(stwuct q6afe_powt *powt, stwuct q6afe_tdm_cfg *cfg);
void q6afe_cdc_dma_powt_pwepawe(stwuct q6afe_powt *powt,
				stwuct q6afe_cdc_dma_cfg *cfg);

int q6afe_powt_set_syscwk(stwuct q6afe_powt *powt, int cwk_id,
			  int cwk_swc, int cwk_woot,
			  unsigned int fweq, int diw);
int q6afe_set_wpass_cwock(stwuct device *dev, int cwk_id, int attwi,
			  int cwk_woot, unsigned int fweq);
int q6afe_vote_wpass_cowe_hw(stwuct device *dev, uint32_t hw_bwock_id,
			     const chaw *cwient_name, uint32_t *cwient_handwe);
int q6afe_unvote_wpass_cowe_hw(stwuct device *dev, uint32_t hw_bwock_id,
			       uint32_t cwient_handwe);
#endif /* __Q6AFE_H__ */
