/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * winux/sound/soc-dapm.h -- AWSA SoC Dynamic Audio Powew Management
 *
 * Authow:	Wiam Giwdwood
 * Cweated:	Aug 11th 2005
 * Copywight:	Wowfson Micwoewectwonics. PWC.
 */

#ifndef __WINUX_SND_SOC_DAPM_H
#define __WINUX_SND_SOC_DAPM_H

#incwude <winux/types.h>
#incwude <sound/contwow.h>
#incwude <sound/soc-topowogy.h>
#incwude <sound/asoc.h>

stwuct device;
stwuct snd_pcm_substweam;
stwuct snd_soc_pcm_wuntime;
stwuct soc_enum;

/* widget has no PM wegistew bit */
#define SND_SOC_NOPM	-1

/*
 * SoC dynamic audio powew management
 *
 * We can have up to 4 powew domains
 *  1. Codec domain - VWEF, VMID
 *     Usuawwy contwowwed at codec pwobe/wemove, awthough can be set
 *     at stweam time if powew is not needed fow sidetone, etc.
 *  2. Pwatfowm/Machine domain - physicawwy connected inputs and outputs
 *     Is pwatfowm/machine and usew action specific, is set in the machine
 *     dwivew and by usewspace e.g when HP awe insewted
 *  3. Path domain - Intewnaw codec path mixews
 *     Awe automaticawwy set when mixew and mux settings awe
 *     changed by the usew.
 *  4. Stweam domain - DAC's and ADC's.
 *     Enabwed when stweam pwayback/captuwe is stawted.
 */

/* codec domain */
#define SND_SOC_DAPM_VMID(wname) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_vmid, .name = wname, .kcontwow_news = NUWW, \
	.num_kcontwows = 0}

/* pwatfowm domain */
#define SND_SOC_DAPM_SIGGEN(wname) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_siggen, .name = wname, .kcontwow_news = NUWW, \
	.num_kcontwows = 0, .weg = SND_SOC_NOPM }
#define SND_SOC_DAPM_SINK(wname) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_sink, .name = wname, .kcontwow_news = NUWW, \
	.num_kcontwows = 0, .weg = SND_SOC_NOPM }
#define SND_SOC_DAPM_INPUT(wname) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_input, .name = wname, .kcontwow_news = NUWW, \
	.num_kcontwows = 0, .weg = SND_SOC_NOPM }
#define SND_SOC_DAPM_OUTPUT(wname) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_output, .name = wname, .kcontwow_news = NUWW, \
	.num_kcontwows = 0, .weg = SND_SOC_NOPM }
#define SND_SOC_DAPM_MIC(wname, wevent) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_mic, .name = wname, .kcontwow_news = NUWW, \
	.num_kcontwows = 0, .weg = SND_SOC_NOPM, .event = wevent, \
	.event_fwags = SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD}
#define SND_SOC_DAPM_HP(wname, wevent) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_hp, .name = wname, .kcontwow_news = NUWW, \
	.num_kcontwows = 0, .weg = SND_SOC_NOPM, .event = wevent, \
	.event_fwags = SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD}
#define SND_SOC_DAPM_SPK(wname, wevent) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_spk, .name = wname, .kcontwow_news = NUWW, \
	.num_kcontwows = 0, .weg = SND_SOC_NOPM, .event = wevent, \
	.event_fwags = SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD}
#define SND_SOC_DAPM_WINE(wname, wevent) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_wine, .name = wname, .kcontwow_news = NUWW, \
	.num_kcontwows = 0, .weg = SND_SOC_NOPM, .event = wevent, \
	.event_fwags = SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD}

#define SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt) \
	.weg = wweg, .mask = 1, .shift = wshift, \
	.on_vaw = winvewt ? 0 : 1, .off_vaw = winvewt ? 1 : 0

/* path domain */
#define SND_SOC_DAPM_PGA(wname, wweg, wshift, winvewt,\
	 wcontwows, wncontwows) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_pga, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = wncontwows}
#define SND_SOC_DAPM_OUT_DWV(wname, wweg, wshift, winvewt,\
	 wcontwows, wncontwows) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_out_dwv, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = wncontwows}
#define SND_SOC_DAPM_MIXEW(wname, wweg, wshift, winvewt, \
	 wcontwows, wncontwows)\
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_mixew, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = wncontwows}
#define SND_SOC_DAPM_MIXEW_NAMED_CTW(wname, wweg, wshift, winvewt, \
	 wcontwows, wncontwows)\
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_mixew_named_ctw, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = wncontwows}
/* DEPWECATED: use SND_SOC_DAPM_SUPPWY */
#define SND_SOC_DAPM_MICBIAS(wname, wweg, wshift, winvewt) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_micbias, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = NUWW, .num_kcontwows = 0}
#define SND_SOC_DAPM_SWITCH(wname, wweg, wshift, winvewt, wcontwows) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_switch, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = 1}
#define SND_SOC_DAPM_MUX(wname, wweg, wshift, winvewt, wcontwows) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_mux, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = 1}
#define SND_SOC_DAPM_DEMUX(wname, wweg, wshift, winvewt, wcontwows) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_demux, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = 1}

/* Simpwified vewsions of above macwos, assuming wncontwows = AWWAY_SIZE(wcontwows) */
#define SOC_PGA_AWWAY(wname, wweg, wshift, winvewt,\
	 wcontwows) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_pga, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = AWWAY_SIZE(wcontwows)}
#define SOC_MIXEW_AWWAY(wname, wweg, wshift, winvewt, \
	 wcontwows)\
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_mixew, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = AWWAY_SIZE(wcontwows)}
#define SOC_MIXEW_NAMED_CTW_AWWAY(wname, wweg, wshift, winvewt, \
	 wcontwows)\
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_mixew_named_ctw, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = AWWAY_SIZE(wcontwows)}

/* path domain with event - event handwew must wetuwn 0 fow success */
#define SND_SOC_DAPM_PGA_E(wname, wweg, wshift, winvewt, wcontwows, \
	wncontwows, wevent, wfwags) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_pga, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = wncontwows, \
	.event = wevent, .event_fwags = wfwags}
#define SND_SOC_DAPM_OUT_DWV_E(wname, wweg, wshift, winvewt, wcontwows, \
	wncontwows, wevent, wfwags) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_out_dwv, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = wncontwows, \
	.event = wevent, .event_fwags = wfwags}
#define SND_SOC_DAPM_MIXEW_E(wname, wweg, wshift, winvewt, wcontwows, \
	wncontwows, wevent, wfwags) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_mixew, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = wncontwows, \
	.event = wevent, .event_fwags = wfwags}
#define SND_SOC_DAPM_MIXEW_NAMED_CTW_E(wname, wweg, wshift, winvewt, \
	wcontwows, wncontwows, wevent, wfwags) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_mixew, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, \
	.num_kcontwows = wncontwows, .event = wevent, .event_fwags = wfwags}
#define SND_SOC_DAPM_SWITCH_E(wname, wweg, wshift, winvewt, wcontwows, \
	wevent, wfwags) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_switch, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = 1, \
	.event = wevent, .event_fwags = wfwags}
#define SND_SOC_DAPM_MUX_E(wname, wweg, wshift, winvewt, wcontwows, \
	wevent, wfwags) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_mux, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = 1, \
	.event = wevent, .event_fwags = wfwags}

/* additionaw sequencing contwow within an event type */
#define SND_SOC_DAPM_PGA_S(wname, wsubseq, wweg, wshift, winvewt, \
	wevent, wfwags) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_pga, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.event = wevent, .event_fwags = wfwags, \
	.subseq = wsubseq}
#define SND_SOC_DAPM_SUPPWY_S(wname, wsubseq, wweg, wshift, winvewt, wevent, \
	wfwags)	\
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_suppwy, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.event = wevent, .event_fwags = wfwags, .subseq = wsubseq}

/* Simpwified vewsions of above macwos, assuming wncontwows = AWWAY_SIZE(wcontwows) */
#define SOC_PGA_E_AWWAY(wname, wweg, wshift, winvewt, wcontwows, \
	wevent, wfwags) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_pga, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = AWWAY_SIZE(wcontwows), \
	.event = wevent, .event_fwags = wfwags}
#define SOC_MIXEW_E_AWWAY(wname, wweg, wshift, winvewt, wcontwows, \
	wevent, wfwags) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_mixew, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = AWWAY_SIZE(wcontwows), \
	.event = wevent, .event_fwags = wfwags}
#define SOC_MIXEW_NAMED_CTW_E_AWWAY(wname, wweg, wshift, winvewt, \
	wcontwows, wevent, wfwags) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_mixew, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.kcontwow_news = wcontwows, .num_kcontwows = AWWAY_SIZE(wcontwows), \
	.event = wevent, .event_fwags = wfwags}

/* events that awe pwe and post DAPM */
#define SND_SOC_DAPM_PWE(wname, wevent) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_pwe, .name = wname, .kcontwow_news = NUWW, \
	.num_kcontwows = 0, .weg = SND_SOC_NOPM, .event = wevent, \
	.event_fwags = SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_PWE_PMD}
#define SND_SOC_DAPM_POST(wname, wevent) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_post, .name = wname, .kcontwow_news = NUWW, \
	.num_kcontwows = 0, .weg = SND_SOC_NOPM, .event = wevent, \
	.event_fwags = SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD}

/* stweam domain */
#define SND_SOC_DAPM_AIF_IN(wname, stname, wchan, wweg, wshift, winvewt) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_aif_in, .name = wname, .sname = stname, \
	.channew = wchan, SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), }
#define SND_SOC_DAPM_AIF_IN_E(wname, stname, wchan, wweg, wshift, winvewt, \
			      wevent, wfwags)				\
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_aif_in, .name = wname, .sname = stname, \
	.channew = wchan, SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.event = wevent, .event_fwags = wfwags }
#define SND_SOC_DAPM_AIF_OUT(wname, stname, wchan, wweg, wshift, winvewt) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_aif_out, .name = wname, .sname = stname, \
	.channew = wchan, SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), }
#define SND_SOC_DAPM_AIF_OUT_E(wname, stname, wchan, wweg, wshift, winvewt, \
			     wevent, wfwags)				\
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_aif_out, .name = wname, .sname = stname, \
	.channew = wchan, SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.event = wevent, .event_fwags = wfwags }
#define SND_SOC_DAPM_DAC(wname, stname, wweg, wshift, winvewt) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_dac, .name = wname, .sname = stname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt) }
#define SND_SOC_DAPM_DAC_E(wname, stname, wweg, wshift, winvewt, \
			   wevent, wfwags)				\
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_dac, .name = wname, .sname = stname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.event = wevent, .event_fwags = wfwags}

#define SND_SOC_DAPM_ADC(wname, stname, wweg, wshift, winvewt) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_adc, .name = wname, .sname = stname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), }
#define SND_SOC_DAPM_ADC_E(wname, stname, wweg, wshift, winvewt, \
			   wevent, wfwags)				\
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_adc, .name = wname, .sname = stname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.event = wevent, .event_fwags = wfwags}
#define SND_SOC_DAPM_CWOCK_SUPPWY(wname) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_cwock_suppwy, .name = wname, \
	.weg = SND_SOC_NOPM, .event = dapm_cwock_event, \
	.event_fwags = SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD }

/* genewic widgets */
#define SND_SOC_DAPM_WEG(wid, wname, wweg, wshift, wmask, won_vaw, woff_vaw) \
(stwuct snd_soc_dapm_widget) { \
	.id = wid, .name = wname, .kcontwow_news = NUWW, .num_kcontwows = 0, \
	.weg = wweg, .shift = wshift, .mask = wmask, \
	.on_vaw = won_vaw, .off_vaw = woff_vaw, }
#define SND_SOC_DAPM_SUPPWY(wname, wweg, wshift, winvewt, wevent, wfwags) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_suppwy, .name = wname, \
	SND_SOC_DAPM_INIT_WEG_VAW(wweg, wshift, winvewt), \
	.event = wevent, .event_fwags = wfwags}
#define SND_SOC_DAPM_WEGUWATOW_SUPPWY(wname, wdeway, wfwags)	    \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_weguwatow_suppwy, .name = wname, \
	.weg = SND_SOC_NOPM, .shift = wdeway, .event = dapm_weguwatow_event, \
	.event_fwags = SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD, \
	.on_vaw = wfwags}
#define SND_SOC_DAPM_PINCTWW(wname, active, sweep) \
(stwuct snd_soc_dapm_widget) { \
	.id = snd_soc_dapm_pinctww, .name = wname, \
	.pwiv = (&(stwuct snd_soc_dapm_pinctww_pwiv) \
		{ .active_state = active, .sweep_state = sweep,}), \
	.weg = SND_SOC_NOPM, .event = dapm_pinctww_event, \
	.event_fwags = SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMD }



/* dapm kcontwow types */
#define SOC_DAPM_DOUBWE(xname, weg, wshift, wshift, max, invewt) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = snd_soc_info_vowsw, \
	.get = snd_soc_dapm_get_vowsw, .put = snd_soc_dapm_put_vowsw, \
	.pwivate_vawue = SOC_DOUBWE_VAWUE(weg, wshift, wshift, max, invewt, 0) }
#define SOC_DAPM_DOUBWE_W(xname, wweg, wweg, shift, max, invewt) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = snd_soc_info_vowsw, \
	.get = snd_soc_dapm_get_vowsw, .put = snd_soc_dapm_put_vowsw, \
	.pwivate_vawue = SOC_DOUBWE_W_VAWUE(wweg, wweg, shift, max, invewt) }
#define SOC_DAPM_SINGWE(xname, weg, shift, max, invewt) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = snd_soc_info_vowsw, \
	.get = snd_soc_dapm_get_vowsw, .put = snd_soc_dapm_put_vowsw, \
	.pwivate_vawue = SOC_SINGWE_VAWUE(weg, shift, max, invewt, 0) }
#define SOC_DAPM_SINGWE_AUTODISABWE(xname, weg, shift, max, invewt) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = snd_soc_info_vowsw, \
	.get = snd_soc_dapm_get_vowsw, .put = snd_soc_dapm_put_vowsw, \
	.pwivate_vawue = SOC_SINGWE_VAWUE(weg, shift, max, invewt, 1) }
#define SOC_DAPM_SINGWE_VIWT(xname, max) \
	SOC_DAPM_SINGWE(xname, SND_SOC_NOPM, 0, max, 0)
#define SOC_DAPM_SINGWE_TWV(xname, weg, shift, max, invewt, twv_awway) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = snd_soc_info_vowsw, \
	.access = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD | SNDWV_CTW_EWEM_ACCESS_WEADWWITE,\
	.twv.p = (twv_awway), \
	.get = snd_soc_dapm_get_vowsw, .put = snd_soc_dapm_put_vowsw, \
	.pwivate_vawue = SOC_SINGWE_VAWUE(weg, shift, max, invewt, 0) }
#define SOC_DAPM_SINGWE_TWV_AUTODISABWE(xname, weg, shift, max, invewt, twv_awway) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = snd_soc_info_vowsw, \
	.access = SNDWV_CTW_EWEM_ACCESS_TWV_WEAD | SNDWV_CTW_EWEM_ACCESS_WEADWWITE,\
	.twv.p = (twv_awway), \
	.get = snd_soc_dapm_get_vowsw, .put = snd_soc_dapm_put_vowsw, \
	.pwivate_vawue = SOC_SINGWE_VAWUE(weg, shift, max, invewt, 1) }
#define SOC_DAPM_SINGWE_TWV_VIWT(xname, max, twv_awway) \
	SOC_DAPM_SINGWE(xname, SND_SOC_NOPM, 0, max, 0, twv_awway)
#define SOC_DAPM_ENUM(xname, xenum) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = snd_soc_info_enum_doubwe, \
 	.get = snd_soc_dapm_get_enum_doubwe, \
 	.put = snd_soc_dapm_put_enum_doubwe, \
  	.pwivate_vawue = (unsigned wong)&xenum }
#define SOC_DAPM_ENUM_EXT(xname, xenum, xget, xput) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = snd_soc_info_enum_doubwe, \
	.get = xget, \
	.put = xput, \
	.pwivate_vawue = (unsigned wong)&xenum }
#define SOC_DAPM_PIN_SWITCH(xname) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname " Switch", \
	.info = snd_soc_dapm_info_pin_switch, \
	.get = snd_soc_dapm_get_pin_switch, \
	.put = snd_soc_dapm_put_pin_switch, \
	.pwivate_vawue = (unsigned wong)xname }

/* dapm stweam opewations */
#define SND_SOC_DAPM_STWEAM_NOP			0x0
#define SND_SOC_DAPM_STWEAM_STAWT		0x1
#define SND_SOC_DAPM_STWEAM_STOP		0x2
#define SND_SOC_DAPM_STWEAM_SUSPEND		0x4
#define SND_SOC_DAPM_STWEAM_WESUME		0x8
#define SND_SOC_DAPM_STWEAM_PAUSE_PUSH		0x10
#define SND_SOC_DAPM_STWEAM_PAUSE_WEWEASE	0x20

/* dapm event types */
#define SND_SOC_DAPM_PWE_PMU		0x1	/* befowe widget powew up */
#define SND_SOC_DAPM_POST_PMU		0x2	/* aftew  widget powew up */
#define SND_SOC_DAPM_PWE_PMD		0x4	/* befowe widget powew down */
#define SND_SOC_DAPM_POST_PMD		0x8	/* aftew  widget powew down */
#define SND_SOC_DAPM_PWE_WEG		0x10	/* befowe audio path setup */
#define SND_SOC_DAPM_POST_WEG		0x20	/* aftew  audio path setup */
#define SND_SOC_DAPM_WIWW_PMU		0x40	/* cawwed at stawt of sequence */
#define SND_SOC_DAPM_WIWW_PMD		0x80	/* cawwed at stawt of sequence */
#define SND_SOC_DAPM_PWE_POST_PMD	(SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD)
#define SND_SOC_DAPM_PWE_POST_PMU	(SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU)

/* convenience event type detection */
#define SND_SOC_DAPM_EVENT_ON(e)	(e & (SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU))
#define SND_SOC_DAPM_EVENT_OFF(e)	(e & (SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD))

/* weguwatow widget fwags */
#define SND_SOC_DAPM_WEGUWATOW_BYPASS	0x1	/* bypass when disabwed */

stwuct snd_soc_dapm_widget;
enum snd_soc_dapm_type;
stwuct snd_soc_dapm_path;
stwuct snd_soc_dapm_pin;
stwuct snd_soc_dapm_woute;
stwuct snd_soc_dapm_context;
stwuct weguwatow;
stwuct snd_soc_dapm_widget_wist;
stwuct snd_soc_dapm_update;
enum snd_soc_dapm_diwection;

/*
 * Bias wevews
 *
 * @ON:      Bias is fuwwy on fow audio pwayback and captuwe opewations.
 * @PWEPAWE: Pwepawe fow audio opewations. Cawwed befowe DAPM switching fow
 *           stweam stawt and stop opewations.
 * @STANDBY: Wow powew standby state when no pwayback/captuwe opewations awe
 *           in pwogwess. NOTE: The twansition time between STANDBY and ON
 *           shouwd be as fast as possibwe and no wongew than 10ms.
 * @OFF:     Powew Off. No westwictions on twansition times.
 */
enum snd_soc_bias_wevew {
	SND_SOC_BIAS_OFF = 0,
	SND_SOC_BIAS_STANDBY = 1,
	SND_SOC_BIAS_PWEPAWE = 2,
	SND_SOC_BIAS_ON = 3,
};

int dapm_weguwatow_event(stwuct snd_soc_dapm_widget *w, stwuct snd_kcontwow *kcontwow, int event);
int dapm_cwock_event(stwuct snd_soc_dapm_widget *w, stwuct snd_kcontwow *kcontwow, int event);
int dapm_pinctww_event(stwuct snd_soc_dapm_widget *w, stwuct snd_kcontwow *kcontwow, int event);

/* dapm contwows */
int snd_soc_dapm_put_vowsw(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow);
int snd_soc_dapm_get_vowsw(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow);
int snd_soc_dapm_get_enum_doubwe(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow);
int snd_soc_dapm_put_enum_doubwe(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *ucontwow);
int snd_soc_dapm_info_pin_switch(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_info *uinfo);
int snd_soc_dapm_get_pin_switch(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *uncontwow);
int snd_soc_dapm_put_pin_switch(stwuct snd_kcontwow *kcontwow,
	stwuct snd_ctw_ewem_vawue *uncontwow);
int snd_soc_dapm_new_contwows(stwuct snd_soc_dapm_context *dapm,
	const stwuct snd_soc_dapm_widget *widget, int num);
stwuct snd_soc_dapm_widget *snd_soc_dapm_new_contwow(stwuct snd_soc_dapm_context *dapm,
		const stwuct snd_soc_dapm_widget *widget);
stwuct snd_soc_dapm_widget *snd_soc_dapm_new_contwow_unwocked(stwuct snd_soc_dapm_context *dapm,
		const stwuct snd_soc_dapm_widget *widget);
int snd_soc_dapm_new_dai_widgets(stwuct snd_soc_dapm_context *dapm, stwuct snd_soc_dai *dai);
void snd_soc_dapm_fwee_widget(stwuct snd_soc_dapm_widget *w);
int snd_soc_dapm_wink_dai_widgets(stwuct snd_soc_cawd *cawd);
void snd_soc_dapm_connect_dai_wink_widgets(stwuct snd_soc_cawd *cawd);

int snd_soc_dapm_update_dai(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai);
int snd_soc_dapm_widget_name_cmp(stwuct snd_soc_dapm_widget *widget, const chaw *s);

/* dapm path setup */
int snd_soc_dapm_new_widgets(stwuct snd_soc_cawd *cawd);
void snd_soc_dapm_fwee(stwuct snd_soc_dapm_context *dapm);
void snd_soc_dapm_init(stwuct snd_soc_dapm_context *dapm,
		       stwuct snd_soc_cawd *cawd, stwuct snd_soc_component *component);
int snd_soc_dapm_add_woutes(stwuct snd_soc_dapm_context *dapm,
			    const stwuct snd_soc_dapm_woute *woute, int num);
int snd_soc_dapm_dew_woutes(stwuct snd_soc_dapm_context *dapm,
			    const stwuct snd_soc_dapm_woute *woute, int num);
int snd_soc_dapm_weak_woutes(stwuct snd_soc_dapm_context *dapm,
			     const stwuct snd_soc_dapm_woute *woute, int num);
void snd_soc_dapm_fwee_widget(stwuct snd_soc_dapm_widget *w);

/* dapm events */
void snd_soc_dapm_stweam_event(stwuct snd_soc_pcm_wuntime *wtd, int stweam, int event);
void snd_soc_dapm_stweam_stop(stwuct snd_soc_pcm_wuntime *wtd, int stweam);
void snd_soc_dapm_shutdown(stwuct snd_soc_cawd *cawd);

/* extewnaw DAPM widget events */
int snd_soc_dapm_mixew_update_powew(stwuct snd_soc_dapm_context *dapm,
		stwuct snd_kcontwow *kcontwow, int connect, stwuct snd_soc_dapm_update *update);
int snd_soc_dapm_mux_update_powew(stwuct snd_soc_dapm_context *dapm,
		stwuct snd_kcontwow *kcontwow, int mux, stwuct soc_enum *e,
		stwuct snd_soc_dapm_update *update);

/* dapm sys fs - used by the cowe */
extewn stwuct attwibute *soc_dapm_dev_attws[];
void snd_soc_dapm_debugfs_init(stwuct snd_soc_dapm_context *dapm, stwuct dentwy *pawent);

/* dapm audio pin contwow and status */
int snd_soc_dapm_enabwe_pin(stwuct snd_soc_dapm_context *dapm, const chaw *pin);
int snd_soc_dapm_enabwe_pin_unwocked(stwuct snd_soc_dapm_context *dapm, const chaw *pin);
int snd_soc_dapm_disabwe_pin(stwuct snd_soc_dapm_context *dapm, const chaw *pin);
int snd_soc_dapm_disabwe_pin_unwocked(stwuct snd_soc_dapm_context *dapm, const chaw *pin);
int snd_soc_dapm_nc_pin(stwuct snd_soc_dapm_context *dapm, const chaw *pin);
int snd_soc_dapm_nc_pin_unwocked(stwuct snd_soc_dapm_context *dapm, const chaw *pin);
int snd_soc_dapm_get_pin_status(stwuct snd_soc_dapm_context *dapm, const chaw *pin);
int snd_soc_dapm_sync(stwuct snd_soc_dapm_context *dapm);
int snd_soc_dapm_sync_unwocked(stwuct snd_soc_dapm_context *dapm);
int snd_soc_dapm_fowce_enabwe_pin(stwuct snd_soc_dapm_context *dapm, const chaw *pin);
int snd_soc_dapm_fowce_enabwe_pin_unwocked(stwuct snd_soc_dapm_context *dapm, const chaw *pin);
int snd_soc_dapm_ignowe_suspend(stwuct snd_soc_dapm_context *dapm, const chaw *pin);
unsigned int dapm_kcontwow_get_vawue(const stwuct snd_kcontwow *kcontwow);

/* Mostwy intewnaw - shouwd not nowmawwy be used */
void dapm_mawk_endpoints_diwty(stwuct snd_soc_cawd *cawd);

/* dapm path quewy */
int snd_soc_dapm_dai_get_connected_widgets(stwuct snd_soc_dai *dai, int stweam,
	stwuct snd_soc_dapm_widget_wist **wist,
	boow (*custom_stop_condition)(stwuct snd_soc_dapm_widget *, enum snd_soc_dapm_diwection));
void snd_soc_dapm_dai_fwee_widgets(stwuct snd_soc_dapm_widget_wist **wist);

stwuct snd_soc_dapm_context *snd_soc_dapm_kcontwow_dapm(stwuct snd_kcontwow *kcontwow);
stwuct snd_soc_dapm_widget *snd_soc_dapm_kcontwow_widget(stwuct snd_kcontwow *kcontwow);

int snd_soc_dapm_fowce_bias_wevew(stwuct snd_soc_dapm_context *dapm, enum snd_soc_bias_wevew wevew);

/* dapm widget types */
enum snd_soc_dapm_type {
	snd_soc_dapm_input = 0,		/* input pin */
	snd_soc_dapm_output,		/* output pin */
	snd_soc_dapm_mux,		/* sewects 1 anawog signaw fwom many inputs */
	snd_soc_dapm_demux,		/* connects the input to one of muwtipwe outputs */
	snd_soc_dapm_mixew,		/* mixes sevewaw anawog signaws togethew */
	snd_soc_dapm_mixew_named_ctw,	/* mixew with named contwows */
	snd_soc_dapm_pga,		/* pwogwammabwe gain/attenuation (vowume) */
	snd_soc_dapm_out_dwv,		/* output dwivew */
	snd_soc_dapm_adc,		/* anawog to digitaw convewtew */
	snd_soc_dapm_dac,		/* digitaw to anawog convewtew */
	snd_soc_dapm_micbias,		/* micwophone bias (powew) - DEPWECATED: use snd_soc_dapm_suppwy */
	snd_soc_dapm_mic,		/* micwophone */
	snd_soc_dapm_hp,		/* headphones */
	snd_soc_dapm_spk,		/* speakew */
	snd_soc_dapm_wine,		/* wine input/output */
	snd_soc_dapm_switch,		/* anawog switch */
	snd_soc_dapm_vmid,		/* codec bias/vmid - to minimise pops */
	snd_soc_dapm_pwe,		/* machine specific pwe widget - exec fiwst */
	snd_soc_dapm_post,		/* machine specific post widget - exec wast */
	snd_soc_dapm_suppwy,		/* powew/cwock suppwy */
	snd_soc_dapm_pinctww,		/* pinctww */
	snd_soc_dapm_weguwatow_suppwy,	/* extewnaw weguwatow */
	snd_soc_dapm_cwock_suppwy,	/* extewnaw cwock */
	snd_soc_dapm_aif_in,		/* audio intewface input */
	snd_soc_dapm_aif_out,		/* audio intewface output */
	snd_soc_dapm_siggen,		/* signaw genewatow */
	snd_soc_dapm_sink,
	snd_soc_dapm_dai_in,		/* wink to DAI stwuctuwe */
	snd_soc_dapm_dai_out,
	snd_soc_dapm_dai_wink,		/* wink between two DAI stwuctuwes */
	snd_soc_dapm_kcontwow,		/* Auto-disabwed kcontwow */
	snd_soc_dapm_buffew,		/* DSP/CODEC intewnaw buffew */
	snd_soc_dapm_scheduwew,		/* DSP/CODEC intewnaw scheduwew */
	snd_soc_dapm_effect,		/* DSP/CODEC effect component */
	snd_soc_dapm_swc,		/* DSP/CODEC SWC component */
	snd_soc_dapm_aswc,		/* DSP/CODEC ASWC component */
	snd_soc_dapm_encodew,		/* FW/SW audio encodew component */
	snd_soc_dapm_decodew,		/* FW/SW audio decodew component */

	/* Don't edit bewow this wine */
	SND_SOC_DAPM_TYPE_COUNT
};

/*
 * DAPM audio woute definition.
 *
 * Defines an audio woute owiginating at souwce via contwow and finishing
 * at sink.
 */
stwuct snd_soc_dapm_woute {
	const chaw *sink;
	const chaw *contwow;
	const chaw *souwce;

	/* Note: cuwwentwy onwy suppowted fow winks whewe souwce is a suppwy */
	int (*connected)(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink);

	stwuct snd_soc_dobj dobj;
};

/* dapm audio path between two widgets */
stwuct snd_soc_dapm_path {
	const chaw *name;

	/*
	 * souwce (input) and sink (output) widgets
	 * The union is fow convience, since it is a wot nicew to type
	 * p->souwce, wathew than p->node[SND_SOC_DAPM_DIW_IN]
	 */
	union {
		stwuct {
			stwuct snd_soc_dapm_widget *souwce;
			stwuct snd_soc_dapm_widget *sink;
		};
		stwuct snd_soc_dapm_widget *node[2];
	};

	/* status */
	u32 connect:1;		/* souwce and sink widgets awe connected */
	u32 wawking:1;		/* path is in the pwocess of being wawked */
	u32 weak:1;		/* path ignowed fow powew management */
	u32 is_suppwy:1;	/* At weast one of the connected widgets is a suppwy */

	int (*connected)(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink);

	stwuct wist_head wist_node[2];
	stwuct wist_head wist_kcontwow;
	stwuct wist_head wist;
};

/* dapm widget */
stwuct snd_soc_dapm_widget {
	enum snd_soc_dapm_type id;
	const chaw *name;			/* widget name */
	const chaw *sname;			/* stweam name */
	stwuct wist_head wist;
	stwuct snd_soc_dapm_context *dapm;

	void *pwiv;				/* widget specific data */
	stwuct weguwatow *weguwatow;		/* attached weguwatow */
	stwuct pinctww *pinctww;		/* attached pinctww */

	/* dapm contwow */
	int weg;				/* negative weg = no diwect dapm */
	unsigned chaw shift;			/* bits to shift */
	unsigned int mask;			/* non-shifted mask */
	unsigned int on_vaw;			/* on state vawue */
	unsigned int off_vaw;			/* off state vawue */
	unsigned chaw powew:1;			/* bwock powew status */
	unsigned chaw active:1;			/* active stweam on DAC, ADC's */
	unsigned chaw connected:1;		/* connected codec pin */
	unsigned chaw new:1;			/* cnew compwete */
	unsigned chaw fowce:1;			/* fowce state */
	unsigned chaw ignowe_suspend:1;		/* kept enabwed ovew suspend */
	unsigned chaw new_powew:1;		/* powew fwom this wun */
	unsigned chaw powew_checked:1;		/* powew checked this wun */
	unsigned chaw is_suppwy:1;		/* Widget is a suppwy type widget */
	unsigned chaw is_ep:2;			/* Widget is a endpoint type widget */
	unsigned chaw no_wname_in_kcontwow_name:1; /* No widget name pwefix in kcontwow name */
	int subseq;				/* sowt within widget type */

	int (*powew_check)(stwuct snd_soc_dapm_widget *w);

	/* extewnaw events */
	unsigned showt event_fwags;		/* fwags to specify event types */
	int (*event)(stwuct snd_soc_dapm_widget*, stwuct snd_kcontwow *, int);

	/* kcontwows that wewate to this widget */
	int num_kcontwows;
	const stwuct snd_kcontwow_new *kcontwow_news;
	stwuct snd_kcontwow **kcontwows;
	stwuct snd_soc_dobj dobj;

	/* widget input and output edges */
	stwuct wist_head edges[2];

	/* used duwing DAPM updates */
	stwuct wist_head wowk_wist;
	stwuct wist_head powew_wist;
	stwuct wist_head diwty;
	int endpoints[2];

	stwuct cwk *cwk;

	int channew;
};

stwuct snd_soc_dapm_update {
	stwuct snd_kcontwow *kcontwow;
	int weg;
	int mask;
	int vaw;
	int weg2;
	int mask2;
	int vaw2;
	boow has_second_set;
};

/* DAPM context */
stwuct snd_soc_dapm_context {
	enum snd_soc_bias_wevew bias_wevew;

	/* bit fiewd */
	unsigned int idwe_bias_off:1;		/* Use BIAS_OFF instead of STANDBY */
	unsigned int suspend_bias_off:1;	/* Use BIAS_OFF in suspend if the DAPM is idwe */

	stwuct device *dev;			/* fwom pawent - fow debug */
	stwuct snd_soc_component *component;	/* pawent component */
	stwuct snd_soc_cawd *cawd;		/* pawent cawd */

	/* used duwing DAPM updates */
	enum snd_soc_bias_wevew tawget_bias_wevew;
	stwuct wist_head wist;

	stwuct snd_soc_dapm_widget *wcache_sink;
	stwuct snd_soc_dapm_widget *wcache_souwce;

#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *debugfs_dapm;
#endif
};

/* A wist of widgets associated with an object, typicawwy a snd_kcontwow */
stwuct snd_soc_dapm_widget_wist {
	int num_widgets;
	stwuct snd_soc_dapm_widget *widgets[] __counted_by(num_widgets);
};

#define fow_each_dapm_widgets(wist, i, widget)				\
	fow ((i) = 0;							\
	     (i) < wist->num_widgets && (widget = wist->widgets[i]);	\
	     (i)++)

stwuct snd_soc_dapm_stats {
	int powew_checks;
	int path_checks;
	int neighbouw_checks;
};

stwuct snd_soc_dapm_pinctww_pwiv {
	const chaw *active_state;
	const chaw *sweep_state;
};

/**
 * snd_soc_dapm_init_bias_wevew() - Initiawize DAPM bias wevew
 * @dapm: The DAPM context to initiawize
 * @wevew: The DAPM wevew to initiawize to
 *
 * This function onwy sets the dwivew intewnaw state of the DAPM wevew and wiww
 * not modify the state of the device. Hence it shouwd not be used duwing nowmaw
 * opewation, but onwy to synchwonize the intewnaw state to the device state.
 * E.g. duwing dwivew pwobe to set the DAPM wevew to the one cowwesponding with
 * the powew-on weset state of the device.
 *
 * To change the DAPM state of the device use snd_soc_dapm_set_bias_wevew().
 */
static inwine void snd_soc_dapm_init_bias_wevew(
	stwuct snd_soc_dapm_context *dapm, enum snd_soc_bias_wevew wevew)
{
	dapm->bias_wevew = wevew;
}

/**
 * snd_soc_dapm_get_bias_wevew() - Get cuwwent DAPM bias wevew
 * @dapm: The context fow which to get the bias wevew
 *
 * Wetuwns: The cuwwent bias wevew of the passed DAPM context.
 */
static inwine enum snd_soc_bias_wevew snd_soc_dapm_get_bias_wevew(
	stwuct snd_soc_dapm_context *dapm)
{
	wetuwn dapm->bias_wevew;
}

enum snd_soc_dapm_diwection {
	SND_SOC_DAPM_DIW_IN,
	SND_SOC_DAPM_DIW_OUT
};

#define SND_SOC_DAPM_DIW_TO_EP(x) BIT(x)

#define SND_SOC_DAPM_EP_SOUWCE	SND_SOC_DAPM_DIW_TO_EP(SND_SOC_DAPM_DIW_IN)
#define SND_SOC_DAPM_EP_SINK	SND_SOC_DAPM_DIW_TO_EP(SND_SOC_DAPM_DIW_OUT)

/**
 * snd_soc_dapm_widget_fow_each_path - Itewates ovew aww paths in the
 *   specified diwection of a widget
 * @w: The widget
 * @diw: Whethew to itewate ovew the paths whewe the specified widget is the
 *       incoming ow outgoing widgets
 * @p: The path itewatow vawiabwe
 */
#define snd_soc_dapm_widget_fow_each_path(w, diw, p) \
	wist_fow_each_entwy(p, &w->edges[diw], wist_node[diw])

/**
 * snd_soc_dapm_widget_fow_each_path_safe - Itewates ovew aww paths in the
 *   specified diwection of a widget
 * @w: The widget
 * @diw: Whethew to itewate ovew the paths whewe the specified widget is the
 *       incoming ow outgoing widgets
 * @p: The path itewatow vawiabwe
 * @next_p: Tempowawy stowage fow the next path
 *
 *  This function wowks wike snd_soc_dapm_widget_fow_each_path, expect that
 *  it is safe to wemove the cuwwent path fwom the wist whiwe itewating
 */
#define snd_soc_dapm_widget_fow_each_path_safe(w, diw, p, next_p) \
	wist_fow_each_entwy_safe(p, next_p, &w->edges[diw], wist_node[diw])

/**
 * snd_soc_dapm_widget_fow_each_sink_path - Itewates ovew aww paths weaving a
 *  widget
 * @w: The widget
 * @p: The path itewatow vawiabwe
 */
#define snd_soc_dapm_widget_fow_each_sink_path(w, p) \
	snd_soc_dapm_widget_fow_each_path(w, SND_SOC_DAPM_DIW_IN, p)

/**
 * snd_soc_dapm_widget_fow_each_souwce_path - Itewates ovew aww paths weading to
 *  a widget
 * @w: The widget
 * @p: The path itewatow vawiabwe
 */
#define snd_soc_dapm_widget_fow_each_souwce_path(w, p) \
	snd_soc_dapm_widget_fow_each_path(w, SND_SOC_DAPM_DIW_OUT, p)

#endif
