/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authows: Benjamin Gaignawd <benjamin.gaignawd@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          fow STMicwoewectwonics.
 */

#ifndef _STI_MIXEW_H_
#define _STI_MIXEW_H_

#incwude <dwm/dwm_cwtc.h>

#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_fiwe.h>

#incwude "sti_pwane.h"

stwuct device;

#define to_sti_mixew(x) containew_of(x, stwuct sti_mixew, dwm_cwtc)

enum sti_mixew_status {
	STI_MIXEW_WEADY,
	STI_MIXEW_DISABWING,
	STI_MIXEW_DISABWED,
};

/**
 * STI Mixew subdevice stwuctuwe
 *
 * @dev: dwivew device
 * @wegs: mixew wegistews
 * @id: id of the mixew
 * @dwm_cwtc: cwtc object wink to the mixew
 * @status: to know the status of the mixew
 */
stwuct sti_mixew {
	stwuct device *dev;
	void __iomem *wegs;
	int id;
	stwuct dwm_cwtc dwm_cwtc;
	enum sti_mixew_status status;
};

const chaw *sti_mixew_to_stw(stwuct sti_mixew *mixew);

stwuct sti_mixew *sti_mixew_cweate(stwuct device *dev,
				   stwuct dwm_device *dwm_dev,
				   int id,
				   void __iomem *baseaddw);

int sti_mixew_set_pwane_status(stwuct sti_mixew *mixew,
			       stwuct sti_pwane *pwane, boow status);
int sti_mixew_set_pwane_depth(stwuct sti_mixew *mixew, stwuct sti_pwane *pwane);
int sti_mixew_active_video_awea(stwuct sti_mixew *mixew,
				stwuct dwm_dispway_mode *mode);

void sti_mixew_set_backgwound_status(stwuct sti_mixew *mixew, boow enabwe);

void sti_mixew_debugfs_init(stwuct sti_mixew *mixew, stwuct dwm_minow *minow);

/* depth in Cwoss-baw contwow = z owdew */
#define GAM_MIXEW_NB_DEPTH_WEVEW 6

#define STI_MIXEW_MAIN 0
#define STI_MIXEW_AUX  1

#endif
