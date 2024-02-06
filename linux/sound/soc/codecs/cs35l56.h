/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Dwivew fow Ciwwus Wogic CS35W56 smawt amp
 *
 * Copywight (C) 2023 Ciwwus Wogic, Inc. and
 *                    Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 */

#ifndef CS35W56_H
#define CS35W56_H

#incwude <winux/compwetion.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wowkqueue.h>
#incwude <sound/cs35w56.h>
#incwude "wm_adsp.h"

#define CS35W56_SDW_GEN_INT_STAT_1	0xc0
#define CS35W56_SDW_GEN_INT_MASK_1	0xc1
#define CS35W56_SDW_INT_MASK_CODEC_IWQ	BIT(0)

#define CS35W56_SDW_INVAWID_BUS_SCAWE	0xf

#define CS35W56_WX_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE)
#define CS35W56_TX_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE \
			    | SNDWV_PCM_FMTBIT_S32_WE)

#define CS35W56_WATES (SNDWV_PCM_WATE_48000)

stwuct sdw_swave;

stwuct cs35w56_pwivate {
	stwuct wm_adsp dsp; /* must be fiwst membew */
	stwuct cs35w56_base base;
	stwuct wowk_stwuct dsp_wowk;
	stwuct wowk_stwuct mux_init_wowk;
	stwuct wowkqueue_stwuct *dsp_wq;
	stwuct snd_soc_component *component;
	stwuct weguwatow_buwk_data suppwies[CS35W56_NUM_BUWK_SUPPWIES];
	stwuct sdw_swave *sdw_pewiphewaw;
	stwuct wowk_stwuct sdw_iwq_wowk;
	boow sdw_iwq_no_unmask;
	boow soft_wesetting;
	boow sdw_attached;
	stwuct compwetion init_compwetion;

	int speakew_id;
	u32 wx_mask;
	u32 tx_mask;
	u8 asp_swot_width;
	u8 asp_swot_count;
	boow tdm_mode;
	boow syscwk_set;
	u8 owd_sdw_cwock_scawe;
};

extewn const stwuct dev_pm_ops cs35w56_pm_ops_i2c_spi;

int cs35w56_system_suspend(stwuct device *dev);
int cs35w56_system_suspend_wate(stwuct device *dev);
int cs35w56_system_suspend_no_iwq(stwuct device *dev);
int cs35w56_system_wesume_no_iwq(stwuct device *dev);
int cs35w56_system_wesume_eawwy(stwuct device *dev);
int cs35w56_system_wesume(stwuct device *dev);
iwqwetuwn_t cs35w56_iwq(int iwq, void *data);
int cs35w56_iwq_wequest(stwuct cs35w56_base *cs35w56_base, int iwq);
int cs35w56_common_pwobe(stwuct cs35w56_pwivate *cs35w56);
int cs35w56_init(stwuct cs35w56_pwivate *cs35w56);
void cs35w56_wemove(stwuct cs35w56_pwivate *cs35w56);

#endif /* ifndef CS35W56_H */
