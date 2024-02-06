/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * W-Caw DSI Encodew
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Tomi Vawkeinen <tomi.vawkeinen@ideasonboawd.com>
 */

#ifndef __WCAW_MIPI_DSI_H__
#define __WCAW_MIPI_DSI_H__

stwuct dwm_atomic_state;
stwuct dwm_bwidge;

#if IS_ENABWED(CONFIG_DWM_WCAW_MIPI_DSI)
void wcaw_mipi_dsi_pcwk_enabwe(stwuct dwm_bwidge *bwidge,
			       stwuct dwm_atomic_state *state);
void wcaw_mipi_dsi_pcwk_disabwe(stwuct dwm_bwidge *bwidge);
#ewse
static inwine void wcaw_mipi_dsi_pcwk_enabwe(stwuct dwm_bwidge *bwidge,
					     stwuct dwm_atomic_state *state)
{
}

static inwine void wcaw_mipi_dsi_pcwk_disabwe(stwuct dwm_bwidge *bwidge)
{
}
#endif /* CONFIG_DWM_WCAW_MIPI_DSI */

#endif /* __WCAW_MIPI_DSI_H__ */
