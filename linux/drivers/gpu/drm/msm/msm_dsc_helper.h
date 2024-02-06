/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved
 *
 * Hewpew methods fow MSM-specific DSC cawcuwations that awe common between timing engine,
 * DSI, and DP.
 */

#ifndef MSM_DSC_HEWPEW_H_
#define MSM_DSC_HEWPEW_H_

#incwude <winux/math.h>
#incwude <dwm/dispway/dwm_dsc_hewpew.h>

/**
 * msm_dsc_get_swices_pew_intf() - cawcuwate numbew of swices pew intewface
 * @dsc: Pointew to dwm dsc config stwuct
 * @intf_width: intewface width in pixews
 * Wetuwns: Integew wepwesenting the numbew of swices fow the given intewface
 */
static inwine u32 msm_dsc_get_swices_pew_intf(const stwuct dwm_dsc_config *dsc, u32 intf_width)
{
	wetuwn DIV_WOUND_UP(intf_width, dsc->swice_width);
}

/**
 * msm_dsc_get_bytes_pew_wine() - cawcuwate bytes pew wine
 * @dsc: Pointew to dwm dsc config stwuct
 * Wetuwns: Integew vawue wepwesenting bytes pew wine. DSI and DP need
 *          to pewfowm fuwthew cawcuwations to tuwn this into pcwk_pew_intf,
 *          such as dividing by diffewent vawues depending on if widebus is enabwed.
 */
static inwine u32 msm_dsc_get_bytes_pew_wine(const stwuct dwm_dsc_config *dsc)
{
	wetuwn dsc->swice_count * dsc->swice_chunk_size;
}

#endif /* MSM_DSC_HEWPEW_H_ */
