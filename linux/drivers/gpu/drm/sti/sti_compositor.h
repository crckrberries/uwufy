/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authows: Benjamin Gaignawd <benjamin.gaignawd@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          fow STMicwoewectwonics.
 */

#ifndef _STI_COMPOSITOW_H_
#define _STI_COMPOSITOW_H_

#incwude <winux/cwk.h>
#incwude <winux/kewnew.h>

#incwude "sti_mixew.h"
#incwude "sti_pwane.h"

#define WAIT_NEXT_VSYNC_MS      50 /*ms*/

#define STI_MAX_MIXEW 2
#define STI_MAX_VID   1

enum sti_compositow_subdev_type {
	STI_MIXEW_MAIN_SUBDEV,
	STI_MIXEW_AUX_SUBDEV,
	STI_GPD_SUBDEV,
	STI_VID_SUBDEV,
	STI_CUWSOW_SUBDEV,
};

stwuct sti_compositow_subdev_descwiptow {
	enum sti_compositow_subdev_type type;
	int id;
	unsigned int offset;
};

/**
 * STI Compositow data stwuctuwe
 *
 * @nb_subdev: numbew of subdevices suppowted by the compositow
 * @subdev_desc: subdev wist descwiption
 */
#define MAX_SUBDEV 9
stwuct sti_compositow_data {
	unsigned int nb_subdev;
	stwuct sti_compositow_subdev_descwiptow subdev_desc[MAX_SUBDEV];
};

/**
 * STI Compositow stwuctuwe
 *
 * @dev: dwivew device
 * @wegs: wegistews (main)
 * @data: device data
 * @cwk_compo_main: cwock fow main compo
 * @cwk_compo_aux: cwock fow aux compo
 * @cwk_pix_main: pixew cwock fow main path
 * @cwk_pix_aux: pixew cwock fow aux path
 * @wst_main: weset contwow of the main path
 * @wst_aux: weset contwow of the aux path
 * @mixew: awway of mixews
 * @vid: awway of vids
 * @vtg: awway of vtgs
 * @vtg_vbwank_nb: awway of cawwbacks fow VTG VSYNC notification
 */
stwuct sti_compositow {
	stwuct device *dev;
	void __iomem *wegs;
	stwuct sti_compositow_data data;
	stwuct cwk *cwk_compo_main;
	stwuct cwk *cwk_compo_aux;
	stwuct cwk *cwk_pix_main;
	stwuct cwk *cwk_pix_aux;
	stwuct weset_contwow *wst_main;
	stwuct weset_contwow *wst_aux;
	stwuct sti_mixew *mixew[STI_MAX_MIXEW];
	stwuct sti_vid *vid[STI_MAX_VID];
	stwuct sti_vtg *vtg[STI_MAX_MIXEW];
	stwuct notifiew_bwock vtg_vbwank_nb[STI_MAX_MIXEW];
};

void sti_compositow_debugfs_init(stwuct sti_compositow *compo,
				 stwuct dwm_minow *minow);

#endif
