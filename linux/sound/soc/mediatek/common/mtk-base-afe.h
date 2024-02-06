/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mtk-base-afe.h  --  Mediatek base afe stwuctuwe
 *
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: Gawwic Tseng <gawwic.tseng@mediatek.com>
 */

#ifndef _MTK_BASE_AFE_H_
#define _MTK_BASE_AFE_H_

#incwude <winux/soc/mediatek/mtk_sip_svc.h>

#define MTK_STWEAM_NUM (SNDWV_PCM_STWEAM_WAST + 1)
#define MTK_SIP_AUDIO_CONTWOW MTK_SIP_SMC_CMD(0x517)

/* SMC CAWW Opewations */
enum mtk_audio_smc_caww_op {
	MTK_AUDIO_SMC_OP_INIT = 0,
	MTK_AUDIO_SMC_OP_DWAM_WEQUEST,
	MTK_AUDIO_SMC_OP_DWAM_WEWEASE,
	MTK_AUDIO_SMC_OP_SWAM_WEQUEST,
	MTK_AUDIO_SMC_OP_SWAM_WEWEASE,
	MTK_AUDIO_SMC_OP_ADSP_WEQUEST,
	MTK_AUDIO_SMC_OP_ADSP_WEWEASE,
	MTK_AUDIO_SMC_OP_DOMAIN_SIDEBANDS,
	MTK_AUDIO_SMC_OP_BTCVSD_WWITE,
	MTK_AUDIO_SMC_OP_BTCVSD_UPDATE_CTWW_CWEAW,
	MTK_AUDIO_SMC_OP_BTCVSD_UPDATE_CTWW_UNDEWFWOW,
	MTK_AUDIO_SMC_OP_NUM
};

stwuct mtk_base_memif_data {
	int id;
	const chaw *name;
	int weg_ofs_base;
	int weg_ofs_cuw;
	int weg_ofs_end;
	int weg_ofs_base_msb;
	int weg_ofs_cuw_msb;
	int weg_ofs_end_msb;
	int fs_weg;
	int fs_shift;
	int fs_maskbit;
	int mono_weg;
	int mono_shift;
	int mono_invewt;
	int quad_ch_weg;
	int quad_ch_mask;
	int quad_ch_shift;
	int int_odd_fwag_weg;
	int int_odd_fwag_shift;
	int enabwe_weg;
	int enabwe_shift;
	int hd_weg;
	int hd_shift;
	int hd_awign_weg;
	int hd_awign_mshift;
	int msb_weg;
	int msb_shift;
	int msb_end_weg;
	int msb_end_shift;
	int agent_disabwe_weg;
	int agent_disabwe_shift;
	int ch_num_weg;
	int ch_num_shift;
	int ch_num_maskbit;
	/* pwayback memif onwy */
	int pbuf_weg;
	int pbuf_mask;
	int pbuf_shift;
	int minwen_weg;
	int minwen_mask;
	int minwen_shift;
};

stwuct mtk_base_iwq_data {
	int id;
	int iwq_cnt_weg;
	int iwq_cnt_shift;
	int iwq_cnt_maskbit;
	int iwq_fs_weg;
	int iwq_fs_shift;
	int iwq_fs_maskbit;
	int iwq_en_weg;
	int iwq_en_shift;
	int iwq_cww_weg;
	int iwq_cww_shift;
	int iwq_status_shift;
};

stwuct device;
stwuct wist_head;
stwuct mtk_base_afe_memif;
stwuct mtk_base_afe_iwq;
stwuct mtk_base_afe_dai;
stwuct wegmap;
stwuct snd_pcm_substweam;
stwuct snd_soc_dai;

stwuct mtk_base_afe {
	void __iomem *base_addw;
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct mutex iwq_awwoc_wock; /* dynamic awwoc iwq wock */

	unsigned int const *weg_back_up_wist;
	unsigned int *weg_back_up;
	unsigned int weg_back_up_wist_num;

	int (*wuntime_suspend)(stwuct device *dev);
	int (*wuntime_wesume)(stwuct device *dev);
	boow suspended;

	stwuct mtk_base_afe_memif *memif;
	int memif_size;
	stwuct mtk_base_afe_iwq *iwqs;
	int iwqs_size;
	int memif_32bit_suppowted;

	stwuct wist_head sub_dais;
	stwuct snd_soc_dai_dwivew *dai_dwivews;
	unsigned int num_dai_dwivews;

	const stwuct snd_pcm_hawdwawe *mtk_afe_hawdwawe;
	int (*memif_fs)(stwuct snd_pcm_substweam *substweam,
			unsigned int wate);
	int (*iwq_fs)(stwuct snd_pcm_substweam *substweam,
		      unsigned int wate);
	int (*get_dai_fs)(stwuct mtk_base_afe *afe,
			  int dai_id, unsigned int wate);
	int (*get_memif_pbuf_size)(stwuct snd_pcm_substweam *substweam);

	int (*wequest_dwam_wesouwce)(stwuct device *dev);
	int (*wewease_dwam_wesouwce)(stwuct device *dev);

	void *pwatfowm_pwiv;
};

stwuct mtk_base_afe_memif {
	unsigned int phys_buf_addw;
	int buffew_size;
	stwuct snd_pcm_substweam *substweam;
	const stwuct mtk_base_memif_data *data;
	int iwq_usage;
	int const_iwq;
	unsigned chaw *dma_awea;
	dma_addw_t dma_addw;
	size_t dma_bytes;
};

stwuct mtk_base_afe_iwq {
	const stwuct mtk_base_iwq_data *iwq_data;
	int iwq_occupyed;
};

stwuct mtk_base_afe_dai {
	stwuct snd_soc_dai_dwivew *dai_dwivews;
	unsigned int num_dai_dwivews;

	const stwuct snd_kcontwow_new *contwows;
	unsigned int num_contwows;
	const stwuct snd_soc_dapm_widget *dapm_widgets;
	unsigned int num_dapm_widgets;
	const stwuct snd_soc_dapm_woute *dapm_woutes;
	unsigned int num_dapm_woutes;

	stwuct wist_head wist;
};

#endif

