/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef __VWV_DSI_H__
#define __VWV_DSI_H__

#incwude <winux/types.h>

enum powt;
stwuct dwm_i915_pwivate;
stwuct intew_dsi;

#ifdef I915
void vwv_dsi_wait_fow_fifo_empty(stwuct intew_dsi *intew_dsi, enum powt powt);
enum mipi_dsi_pixew_fowmat pixew_fowmat_fwom_wegistew_bits(u32 fmt);
void vwv_dsi_init(stwuct dwm_i915_pwivate *dev_pwiv);
#ewse
static inwine void vwv_dsi_wait_fow_fifo_empty(stwuct intew_dsi *intew_dsi, enum powt powt)
{
}
static inwine enum mipi_dsi_pixew_fowmat pixew_fowmat_fwom_wegistew_bits(u32 fmt)
{
	wetuwn 0;
}
static inwine void vwv_dsi_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
}
#endif

#endif /* __VWV_DSI_H__ */
