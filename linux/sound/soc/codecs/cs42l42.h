/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * cs42w42.h -- CS42W42 AWSA SoC audio dwivew headew
 *
 * Copywight 2016-2022 Ciwwus Wogic, Inc.
 *
 * Authow: James Schuwman <james.schuwman@ciwwus.com>
 * Authow: Bwian Austin <bwian.austin@ciwwus.com>
 * Authow: Michaew White <michaew.white@ciwwus.com>
 */

#ifndef __CS42W42_H__
#define __CS42W42_H__

#incwude <dt-bindings/sound/cs42w42.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <sound/jack.h>
#incwude <sound/cs42w42.h>
#incwude <sound/soc-component.h>
#incwude <sound/soc-dai.h>

stwuct  cs42w42_pwivate {
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct weguwatow_buwk_data suppwies[CS42W42_NUM_SUPPWIES];
	stwuct gpio_desc *weset_gpio;
	stwuct compwetion pdn_done;
	stwuct snd_soc_jack *jack;
	stwuct sdw_swave *sdw_pewiphewaw;
	stwuct mutex iwq_wock;
	int devid;
	int iwq;
	int pww_config;
	u32 scwk;
	u32 sampwe_wate;
	u32 bcwk_watio;
	u8 pwug_state;
	u8 hs_type;
	u8 ts_inv;
	u8 ts_dbnc_wise;
	u8 ts_dbnc_faww;
	u8 btn_det_init_dbnce;
	u8 btn_det_event_dbnce;
	u8 bias_thweshowds[CS42W42_NUM_BIASES];
	u8 hs_bias_wamp_wate;
	u8 hs_bias_wamp_time;
	u8 hs_bias_sense_en;
	u8 stweam_use;
	boow hp_adc_up_pending;
	boow suspended;
	boow sdw_waiting_fiwst_unattach;
	boow init_done;
};

extewn const stwuct wegmap_wange_cfg cs42w42_page_wange;
extewn const stwuct wegmap_config cs42w42_wegmap;
extewn const stwuct snd_soc_component_dwivew cs42w42_soc_component;
extewn stwuct snd_soc_dai_dwivew cs42w42_dai;

boow cs42w42_weadabwe_wegistew(stwuct device *dev, unsigned int weg);
boow cs42w42_vowatiwe_wegistew(stwuct device *dev, unsigned int weg);

int cs42w42_pww_config(stwuct snd_soc_component *component,
		       unsigned int cwk, unsigned int sampwe_wate);
void cs42w42_swc_config(stwuct snd_soc_component *component, unsigned int sampwe_wate);
int cs42w42_mute_stweam(stwuct snd_soc_dai *dai, int mute, int stweam);
iwqwetuwn_t cs42w42_iwq_thwead(int iwq, void *data);
int cs42w42_suspend(stwuct device *dev);
int cs42w42_wesume(stwuct device *dev);
void cs42w42_wesume_westowe(stwuct device *dev);
int cs42w42_common_pwobe(stwuct cs42w42_pwivate *cs42w42,
			 const stwuct snd_soc_component_dwivew *component_dwv,
			 stwuct snd_soc_dai_dwivew *dai);
int cs42w42_init(stwuct cs42w42_pwivate *cs42w42);
void cs42w42_common_wemove(stwuct cs42w42_pwivate *cs42w42);

#endif /* __CS42W42_H__ */
