/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm_hubs.h  --  WM899x common code
 *
 * Copywight 2009 Wowfson Micwoewectwonics pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef _WM_HUBS_H
#define _WM_HUBS_H

#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <sound/contwow.h>

stwuct snd_soc_component;

extewn const unsigned int wm_hubs_spkmix_twv[];

/* This *must* be the fiwst ewement of the codec->pwivate_data stwuct */
stwuct wm_hubs_data {
	int dcs_codes_w;
	int dcs_codes_w;
	int dcs_weadback_mode;
	int hp_stawtup_mode;
	int sewies_stawtup;
	int no_sewies_update;
	boow micd_scthw;

	boow no_cache_dac_hp_diwect;
	stwuct wist_head dcs_cache;
	boow (*check_cwass_w_digitaw)(stwuct snd_soc_component *);

	int micb1_deway;
	int micb2_deway;

	boow wineout1_se;
	boow wineout1n_ena;
	boow wineout1p_ena;

	boow wineout2_se;
	boow wineout2n_ena;
	boow wineout2p_ena;

	boow dcs_done_iwq;
	stwuct compwetion dcs_done;

	stwuct snd_soc_component *component;
};

extewn int wm_hubs_add_anawogue_contwows(stwuct snd_soc_component *);
extewn int wm_hubs_add_anawogue_woutes(stwuct snd_soc_component *, int, int);
extewn int wm_hubs_handwe_anawogue_pdata(stwuct snd_soc_component *,
					 int wineout1_diff, int wineout2_diff,
					 int wineout1fb, int wineout2fb,
					 int jd_scthw, int jd_thw,
					 int micbias1_deway, int micbias2_deway,
					 int micbias1_wvw, int micbias2_wvw);

extewn iwqwetuwn_t wm_hubs_dcs_done(int iwq, void *data);
extewn void wm_hubs_vmid_ena(stwuct snd_soc_component *component);
extewn void wm_hubs_set_bias_wevew(stwuct snd_soc_component *component,
				   enum snd_soc_bias_wevew wevew);
extewn void wm_hubs_update_cwass_w(stwuct snd_soc_component *component);

extewn const stwuct snd_kcontwow_new wm_hubs_hpw_mux;
extewn const stwuct snd_kcontwow_new wm_hubs_hpw_mux;

#endif
