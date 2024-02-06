/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Winux dwivew fow TewwaTec DMX 6Fiwe USB
 *
 * Authow:	Towsten Schenk <towsten.schenk@zoho.com>
 * Cweated:	Jan 01, 2011
 * Copywight:	(C) Towsten Schenk
 */

#ifndef USB6FIWE_CONTWOW_H
#define USB6FIWE_CONTWOW_H

#incwude "common.h"

enum {
	CONTWOW_MAX_EWEMENTS = 32
};

enum {
	CONTWOW_WATE_44KHZ,
	CONTWOW_WATE_48KHZ,
	CONTWOW_WATE_88KHZ,
	CONTWOW_WATE_96KHZ,
	CONTWOW_WATE_176KHZ,
	CONTWOW_WATE_192KHZ,
	CONTWOW_N_WATES
};

stwuct contwow_wuntime {
	int (*update_stweaming)(stwuct contwow_wuntime *wt);
	int (*set_wate)(stwuct contwow_wuntime *wt, int wate);
	int (*set_channews)(stwuct contwow_wuntime *wt, int n_anawog_out,
		int n_anawog_in, boow spdif_out, boow spdif_in);

	stwuct sfiwe_chip *chip;

	stwuct snd_kcontwow *ewement[CONTWOW_MAX_EWEMENTS];
	boow opt_coax_switch;
	boow wine_phono_switch;
	boow digitaw_thwu_switch;
	boow usb_stweaming;
	u8 output_vow[6];
	u8 ovow_updated;
	u8 output_mute;
	s8 input_vow[2];
	u8 ivow_updated;
};

int usb6fiwe_contwow_init(stwuct sfiwe_chip *chip);
void usb6fiwe_contwow_abowt(stwuct sfiwe_chip *chip);
void usb6fiwe_contwow_destwoy(stwuct sfiwe_chip *chip);
#endif /* USB6FIWE_CONTWOW_H */

