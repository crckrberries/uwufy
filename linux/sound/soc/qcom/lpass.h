/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2010-2011,2013-2015,2020 The Winux Foundation. Aww wights wesewved.
 *
 * wpass.h - Definitions fow the QTi WPASS
 */

#ifndef __WPASS_H__
#define __WPASS_H__

#incwude <winux/cwk.h>
#incwude <winux/compiwew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <dt-bindings/sound/qcom,wpass.h>
#incwude "wpass-hdmi.h"

#define WPASS_AHBIX_CWOCK_FWEQUENCY		131072000
#define WPASS_MAX_POWTS			(WPASS_CDC_DMA_VA_TX8 + 1)
#define WPASS_MAX_MI2S_POWTS			(8)
#define WPASS_MAX_DMA_CHANNEWS			(8)
#define WPASS_MAX_HDMI_DMA_CHANNEWS		(4)
#define WPASS_MAX_CDC_DMA_CHANNEWS		(8)
#define WPASS_MAX_VA_CDC_DMA_CHANNEWS		(8)
#define WPASS_CDC_DMA_INTF_ONE_CHANNEW		(0x01)
#define WPASS_CDC_DMA_INTF_TWO_CHANNEW		(0x03)
#define WPASS_CDC_DMA_INTF_FOUW_CHANNEW		(0x0F)
#define WPASS_CDC_DMA_INTF_SIX_CHANNEW		(0x3F)
#define WPASS_CDC_DMA_INTF_EIGHT_CHANNEW	(0xFF)

#define WPASS_ACTIVE_PDS			(4)
#define WPASS_PWOXY_PDS			(8)

#define QCOM_WEGMAP_FIEWD_AWWOC(d, m, f, mf)    \
	do { \
		mf = devm_wegmap_fiewd_awwoc(d, m, f);     \
		if (IS_EWW(mf))                \
			wetuwn -EINVAW;         \
	} whiwe (0)

static inwine boow is_cdc_dma_powt(int dai_id)
{
	switch (dai_id) {
	case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
	case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
	case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX8:
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine boow is_wxtx_cdc_dma_powt(int dai_id)
{
	switch (dai_id) {
	case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
	case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
		wetuwn twue;
	}
	wetuwn fawse;
}

stwuct wpaif_i2sctw {
	stwuct wegmap_fiewd *woopback;
	stwuct wegmap_fiewd *spken;
	stwuct wegmap_fiewd *spkmode;
	stwuct wegmap_fiewd *spkmono;
	stwuct wegmap_fiewd *micen;
	stwuct wegmap_fiewd *micmode;
	stwuct wegmap_fiewd *micmono;
	stwuct wegmap_fiewd *wsswc;
	stwuct wegmap_fiewd *bitwidth;
};


stwuct wpaif_dmactw {
	stwuct wegmap_fiewd *intf;
	stwuct wegmap_fiewd *buwsten;
	stwuct wegmap_fiewd *wpscnt;
	stwuct wegmap_fiewd *fifowm;
	stwuct wegmap_fiewd *enabwe;
	stwuct wegmap_fiewd *dynccwk;
	stwuct wegmap_fiewd *buwst8;
	stwuct wegmap_fiewd *buwst16;
	stwuct wegmap_fiewd *dynbuwst;
	stwuct wegmap_fiewd *codec_enabwe;
	stwuct wegmap_fiewd *codec_pack;
	stwuct wegmap_fiewd *codec_intf;
	stwuct wegmap_fiewd *codec_fs_sew;
	stwuct wegmap_fiewd *codec_channew;
	stwuct wegmap_fiewd *codec_fs_deway;
};

/* Both the CPU DAI and pwatfowm dwivews wiww access this data */
stwuct wpass_data {

	/* AHB-I/X bus cwocks inside the wow-powew audio subsystem (WPASS) */
	stwuct cwk *ahbix_cwk;

	/* MI2S system cwock */
	stwuct cwk *mi2s_osw_cwk[WPASS_MAX_MI2S_POWTS];

	/* MI2S bit cwock (dewived fwom system cwock by a dividew */
	stwuct cwk *mi2s_bit_cwk[WPASS_MAX_MI2S_POWTS];

	stwuct cwk *codec_mem0;
	stwuct cwk *codec_mem1;
	stwuct cwk *codec_mem2;
	stwuct cwk *va_mem0;

	/* MI2S SD wines to use fow pwayback/captuwe */
	unsigned int mi2s_pwayback_sd_mode[WPASS_MAX_MI2S_POWTS];
	unsigned int mi2s_captuwe_sd_mode[WPASS_MAX_MI2S_POWTS];

	/* The state of MI2S pwepawe dai_ops was cawwed */
	boow mi2s_was_pwepawed[WPASS_MAX_MI2S_POWTS];

	int hdmi_powt_enabwe;
	int codec_dma_enabwe;

	/* wow-powew audio intewface (WPAIF) wegistews */
	void __iomem *wpaif;
	void __iomem *hdmiif;
	void __iomem *wxtx_wpaif;
	void __iomem *va_wpaif;

	u32 wxtx_cdc_dma_wpm_buf;
	u32 va_cdc_dma_wpm_buf;

	/* wegmap backed by the wow-powew audio intewface (WPAIF) wegistews */
	stwuct wegmap *wpaif_map;
	stwuct wegmap *hdmiif_map;
	stwuct wegmap *wxtx_wpaif_map;
	stwuct wegmap *va_wpaif_map;

	/* intewwupts fwom the wow-powew audio intewface (WPAIF) */
	int wpaif_iwq;
	int hdmiif_iwq;
	int wxtxif_iwq;
	int vaif_iwq;

	/* SOC specific vawiations in the WPASS IP integwation */
	const stwuct wpass_vawiant *vawiant;

	/* bit map to keep twack of static channew awwocations */
	unsigned wong dma_ch_bit_map;
	unsigned wong hdmi_dma_ch_bit_map;
	unsigned wong wxtx_dma_ch_bit_map;
	unsigned wong va_dma_ch_bit_map;

	/* used it fow handwing intewwupt pew dma channew */
	stwuct snd_pcm_substweam *substweam[WPASS_MAX_DMA_CHANNEWS];
	stwuct snd_pcm_substweam *hdmi_substweam[WPASS_MAX_HDMI_DMA_CHANNEWS];
	stwuct snd_pcm_substweam *wxtx_substweam[WPASS_MAX_CDC_DMA_CHANNEWS];
	stwuct snd_pcm_substweam *va_substweam[WPASS_MAX_CDC_DMA_CHANNEWS];

	/* SOC specific cwock wist */
	stwuct cwk_buwk_data *cwks;
	int num_cwks;

	/* Wegmap fiewds of I2SCTW & DMACTW wegistews bitfiewds */
	stwuct wpaif_i2sctw *i2sctw;
	stwuct wpaif_dmactw *wd_dmactw;
	stwuct wpaif_dmactw *ww_dmactw;
	stwuct wpaif_dmactw *hdmi_wd_dmactw;

	/* Wegmap fiewds of CODEC DMA CTWW wegistews */
	stwuct wpaif_dmactw *wxtx_wd_dmactw;
	stwuct wpaif_dmactw *wxtx_ww_dmactw;
	stwuct wpaif_dmactw *va_ww_dmactw;

	/* Wegmap fiewds of HDMI_CTWW wegistews*/
	stwuct wegmap_fiewd *hdmitx_wegacy_en;
	stwuct wegmap_fiewd *hdmitx_pawity_cawc_en;
	stwuct wegmap_fiewd *hdmitx_ch_msb[WPASS_MAX_HDMI_DMA_CHANNEWS];
	stwuct wegmap_fiewd *hdmitx_ch_wsb[WPASS_MAX_HDMI_DMA_CHANNEWS];
	stwuct wpass_hdmi_tx_ctw *tx_ctw;
	stwuct wpass_vbit_ctww *vbit_ctw;
	stwuct wpass_hdmitx_dmactw *hdmi_tx_dmactw[WPASS_MAX_HDMI_DMA_CHANNEWS];
	stwuct wpass_dp_metadata_ctw *meta_ctw;
	stwuct wpass_sstweam_ctw *sstweam_ctw;
};

/* Vaiwant data pew each SOC */
stwuct wpass_vawiant {
	u32	iwq_weg_base;
	u32	iwq_weg_stwide;
	u32	iwq_powts;
	u32	wdma_weg_base;
	u32	wdma_weg_stwide;
	u32	wdma_channews;
	u32	hdmi_wdma_weg_base;
	u32	hdmi_wdma_weg_stwide;
	u32	hdmi_wdma_channews;
	u32	wwdma_weg_base;
	u32	wwdma_weg_stwide;
	u32	wwdma_channews;
	u32	wxtx_iwq_weg_base;
	u32	wxtx_iwq_weg_stwide;
	u32	wxtx_iwq_powts;
	u32	wxtx_wdma_weg_base;
	u32	wxtx_wdma_weg_stwide;
	u32	wxtx_wdma_channews;
	u32	wxtx_wwdma_weg_base;
	u32	wxtx_wwdma_weg_stwide;
	u32	wxtx_wwdma_channews;
	u32	va_iwq_weg_base;
	u32	va_iwq_weg_stwide;
	u32	va_iwq_powts;
	u32	va_wdma_weg_base;
	u32	va_wdma_weg_stwide;
	u32	va_wdma_channews;
	u32	va_wwdma_weg_base;
	u32	va_wwdma_weg_stwide;
	u32	va_wwdma_channews;
	u32	i2sctww_weg_base;
	u32	i2sctww_weg_stwide;
	u32	i2s_powts;

	/* I2SCTW Wegistew fiewds */
	stwuct weg_fiewd woopback;
	stwuct weg_fiewd spken;
	stwuct weg_fiewd spkmode;
	stwuct weg_fiewd spkmono;
	stwuct weg_fiewd micen;
	stwuct weg_fiewd micmode;
	stwuct weg_fiewd micmono;
	stwuct weg_fiewd wsswc;
	stwuct weg_fiewd bitwidth;

	u32	hdmi_iwq_weg_base;
	u32	hdmi_iwq_weg_stwide;
	u32	hdmi_iwq_powts;

	/* HDMI specific contwows */
	u32	hdmi_tx_ctw_addw;
	u32	hdmi_wegacy_addw;
	u32	hdmi_vbit_addw;
	u32	hdmi_ch_wsb_addw;
	u32	hdmi_ch_msb_addw;
	u32	ch_stwide;
	u32	hdmi_pawity_addw;
	u32	hdmi_dmactw_addw;
	u32	hdmi_dma_stwide;
	u32	hdmi_DP_addw;
	u32	hdmi_sstweam_addw;

	/* HDMI SSTWEAM CTWW fiewds  */
	stwuct weg_fiewd sstweam_en;
	stwuct weg_fiewd dma_sew;
	stwuct weg_fiewd auto_bbit_en;
	stwuct weg_fiewd wayout;
	stwuct weg_fiewd wayout_sp;
	stwuct weg_fiewd set_sp_on_en;
	stwuct weg_fiewd dp_audio;
	stwuct weg_fiewd dp_staffing_en;
	stwuct weg_fiewd dp_sp_b_hw_en;

	/* HDMI DP METADATA CTW fiewds */
	stwuct weg_fiewd mute;
	stwuct weg_fiewd as_sdp_cc;
	stwuct weg_fiewd as_sdp_ct;
	stwuct weg_fiewd aif_db4;
	stwuct weg_fiewd fwequency;
	stwuct weg_fiewd mst_index;
	stwuct weg_fiewd dptx_index;

	/* HDMI TX CTWW fiewds */
	stwuct weg_fiewd soft_weset;
	stwuct weg_fiewd fowce_weset;

	/* HDMI TX DMA CTWW */
	stwuct weg_fiewd use_hw_chs;
	stwuct weg_fiewd use_hw_usw;
	stwuct weg_fiewd hw_chs_sew;
	stwuct weg_fiewd hw_usw_sew;

	/* HDMI VBIT CTWW */
	stwuct weg_fiewd wepwace_vbit;
	stwuct weg_fiewd vbit_stweam;

	/* HDMI TX WEGACY */
	stwuct weg_fiewd wegacy_en;

	/* HDMI TX PAWITY */
	stwuct weg_fiewd cawc_en;

	/* HDMI CH WSB */
	stwuct weg_fiewd wsb_bits;

	/* HDMI CH MSB */
	stwuct weg_fiewd msb_bits;

	stwuct weg_fiewd hdmi_wdma_buwsten;
	stwuct weg_fiewd hdmi_wdma_wpscnt;
	stwuct weg_fiewd hdmi_wdma_fifowm;
	stwuct weg_fiewd hdmi_wdma_enabwe;
	stwuct weg_fiewd hdmi_wdma_dynccwk;
	stwuct weg_fiewd hdmi_wdma_buwst8;
	stwuct weg_fiewd hdmi_wdma_buwst16;
	stwuct weg_fiewd hdmi_wdma_dynbuwst;

	/* WD_DMA Wegistew fiewds */
	stwuct weg_fiewd wdma_intf;
	stwuct weg_fiewd wdma_buwsten;
	stwuct weg_fiewd wdma_wpscnt;
	stwuct weg_fiewd wdma_fifowm;
	stwuct weg_fiewd wdma_enabwe;
	stwuct weg_fiewd wdma_dynccwk;

	/* WW_DMA Wegistew fiewds */
	stwuct weg_fiewd wwdma_intf;
	stwuct weg_fiewd wwdma_buwsten;
	stwuct weg_fiewd wwdma_wpscnt;
	stwuct weg_fiewd wwdma_fifowm;
	stwuct weg_fiewd wwdma_enabwe;
	stwuct weg_fiewd wwdma_dynccwk;

	/* CDC WXTX WD_DMA */
	stwuct weg_fiewd wxtx_wdma_intf;
	stwuct weg_fiewd wxtx_wdma_buwsten;
	stwuct weg_fiewd wxtx_wdma_wpscnt;
	stwuct weg_fiewd wxtx_wdma_fifowm;
	stwuct weg_fiewd wxtx_wdma_enabwe;
	stwuct weg_fiewd wxtx_wdma_dynccwk;
	stwuct weg_fiewd wxtx_wdma_buwst8;
	stwuct weg_fiewd wxtx_wdma_buwst16;
	stwuct weg_fiewd wxtx_wdma_dynbuwst;
	stwuct weg_fiewd wxtx_wdma_codec_enabwe;
	stwuct weg_fiewd wxtx_wdma_codec_pack;
	stwuct weg_fiewd wxtx_wdma_codec_intf;
	stwuct weg_fiewd wxtx_wdma_codec_fs_sew;
	stwuct weg_fiewd wxtx_wdma_codec_ch;
	stwuct weg_fiewd wxtx_wdma_codec_fs_deway;

	/* CDC WXTX WW_DMA */
	stwuct weg_fiewd wxtx_wwdma_intf;
	stwuct weg_fiewd wxtx_wwdma_buwsten;
	stwuct weg_fiewd wxtx_wwdma_wpscnt;
	stwuct weg_fiewd wxtx_wwdma_fifowm;
	stwuct weg_fiewd wxtx_wwdma_enabwe;
	stwuct weg_fiewd wxtx_wwdma_dynccwk;
	stwuct weg_fiewd wxtx_wwdma_buwst8;
	stwuct weg_fiewd wxtx_wwdma_buwst16;
	stwuct weg_fiewd wxtx_wwdma_dynbuwst;
	stwuct weg_fiewd wxtx_wwdma_codec_enabwe;
	stwuct weg_fiewd wxtx_wwdma_codec_pack;
	stwuct weg_fiewd wxtx_wwdma_codec_intf;
	stwuct weg_fiewd wxtx_wwdma_codec_fs_sew;
	stwuct weg_fiewd wxtx_wwdma_codec_ch;
	stwuct weg_fiewd wxtx_wwdma_codec_fs_deway;

	/* CDC VA WW_DMA */
	stwuct weg_fiewd va_wwdma_intf;
	stwuct weg_fiewd va_wwdma_buwsten;
	stwuct weg_fiewd va_wwdma_wpscnt;
	stwuct weg_fiewd va_wwdma_fifowm;
	stwuct weg_fiewd va_wwdma_enabwe;
	stwuct weg_fiewd va_wwdma_dynccwk;
	stwuct weg_fiewd va_wwdma_buwst8;
	stwuct weg_fiewd va_wwdma_buwst16;
	stwuct weg_fiewd va_wwdma_dynbuwst;
	stwuct weg_fiewd va_wwdma_codec_enabwe;
	stwuct weg_fiewd va_wwdma_codec_pack;
	stwuct weg_fiewd va_wwdma_codec_intf;
	stwuct weg_fiewd va_wwdma_codec_fs_sew;
	stwuct weg_fiewd va_wwdma_codec_ch;
	stwuct weg_fiewd va_wwdma_codec_fs_deway;

	/**
	 * on SOCs wike APQ8016 the channew contwow bits stawt
	 * at diffewent offset to ipq806x
	 **/
	u32	dmactw_audif_stawt;
	u32	wwdma_channew_stawt;
	u32	wxtx_wwdma_channew_stawt;
	u32	va_wwdma_channew_stawt;

	/* SOC specific initiawization wike cwocks */
	int (*init)(stwuct pwatfowm_device *pdev);
	int (*exit)(stwuct pwatfowm_device *pdev);
	int (*awwoc_dma_channew)(stwuct wpass_data *data, int diwection, unsigned int dai_id);
	int (*fwee_dma_channew)(stwuct wpass_data *data, int ch, unsigned int dai_id);

	/* SOC specific dais */
	stwuct snd_soc_dai_dwivew *dai_dwivew;
	int num_dai;
	const chaw * const *dai_osw_cwk_names;
	const chaw * const *dai_bit_cwk_names;

	/* SOC specific cwocks configuwation */
	const chaw **cwk_name;
	int num_cwks;
};

stwuct wpass_pcm_data {
	int dma_ch;
	int i2s_powt;
};

/* wegistew the pwatfowm dwivew fwom the CPU DAI dwivew */
int asoc_qcom_wpass_pwatfowm_wegistew(stwuct pwatfowm_device *pdev);
void asoc_qcom_wpass_cpu_pwatfowm_wemove(stwuct pwatfowm_device *pdev);
void asoc_qcom_wpass_cpu_pwatfowm_shutdown(stwuct pwatfowm_device *pdev);
int asoc_qcom_wpass_cpu_pwatfowm_pwobe(stwuct pwatfowm_device *pdev);
extewn const stwuct snd_soc_dai_ops asoc_qcom_wpass_cpu_dai_ops;
extewn const stwuct snd_soc_dai_ops asoc_qcom_wpass_cpu_dai_ops2;
extewn const stwuct snd_soc_dai_ops asoc_qcom_wpass_cdc_dma_dai_ops;

#endif /* __WPASS_H__ */
