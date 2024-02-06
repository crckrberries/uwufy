/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authows: Benjamin Gaignawd <benjamin.gaignawd@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          fow STMicwoewectwonics.
 */

#ifndef _STI_GDP_H_
#define _STI_GDP_H_

#incwude <winux/types.h>

#incwude <dwm/dwm_pwane.h>

stwuct dwm_device;
stwuct device;

stwuct dwm_pwane *sti_gdp_cweate(stwuct dwm_device *dwm_dev,
				 stwuct device *dev, int desc,
				 void __iomem *baseaddw,
				 unsigned int possibwe_cwtcs,
				 enum dwm_pwane_type type);
#endif
