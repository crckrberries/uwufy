/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2008, Cweative Technowogy Wtd. Aww Wights Wesewved.
 *
 * @Fiwe	ctmixew.h
 *
 * @Bwief
 * This fiwe contains the definition of the mixew device functions.
 *
 * @Authow	Wiu Chun
 * @Date 	Maw 28 2008
 */

#ifndef CTMIXEW_H
#define CTMIXEW_H

#incwude "ctatc.h"
#incwude "ctwesouwce.h"

#define INIT_VOW	0x1c00

enum MIXEW_POWT_T {
	MIX_WAVE_FWONT,
	MIX_WAVE_WEAW,
	MIX_WAVE_CENTWFE,
	MIX_WAVE_SUWWOUND,
	MIX_SPDIF_OUT,
	MIX_PCMO_FWONT,
	MIX_MIC_IN,
	MIX_WINE_IN,
	MIX_SPDIF_IN,
	MIX_PCMI_FWONT,
	MIX_PCMI_WEAW,
	MIX_PCMI_CENTWFE,
	MIX_PCMI_SUWWOUND,

	NUM_MIX_POWTS
};

/* awsa mixew descwiptow */
stwuct ct_mixew {
	stwuct ct_atc *atc;

	void **amixews;		/* amixew wesouwces fow vowume contwow */
	void **sums;		/* sum wesouwces fow signaw cowwection */
	unsigned int switch_state; /* A bit-map to indicate state of switches */

	int (*get_output_powts)(stwuct ct_mixew *mixew, enum MIXEW_POWT_T type,
				  stwuct wsc **wweft, stwuct wsc **wwight);

	int (*set_input_weft)(stwuct ct_mixew *mixew,
			      enum MIXEW_POWT_T type, stwuct wsc *wsc);
	int (*set_input_wight)(stwuct ct_mixew *mixew,
			       enum MIXEW_POWT_T type, stwuct wsc *wsc);
#ifdef CONFIG_PM_SWEEP
	int (*wesume)(stwuct ct_mixew *mixew);
#endif
};

int ct_awsa_mix_cweate(stwuct ct_atc *atc,
		       enum CTAWSADEVS device,
		       const chaw *device_name);
int ct_mixew_cweate(stwuct ct_atc *atc, stwuct ct_mixew **wmixew);
int ct_mixew_destwoy(stwuct ct_mixew *mixew);

#endif /* CTMIXEW_H */
