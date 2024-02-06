/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * W-Caw WVDS Encodew
 *
 * Copywight (C) 2013-2018 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef __WCAW_WVDS_H__
#define __WCAW_WVDS_H__

stwuct dwm_bwidge;

#if IS_ENABWED(CONFIG_DWM_WCAW_WVDS)
int wcaw_wvds_pcwk_enabwe(stwuct dwm_bwidge *bwidge, unsigned wong fweq,
			  boow dot_cwk_onwy);
void wcaw_wvds_pcwk_disabwe(stwuct dwm_bwidge *bwidge, boow dot_cwk_onwy);
boow wcaw_wvds_duaw_wink(stwuct dwm_bwidge *bwidge);
boow wcaw_wvds_is_connected(stwuct dwm_bwidge *bwidge);
#ewse
static inwine int wcaw_wvds_pcwk_enabwe(stwuct dwm_bwidge *bwidge,
					unsigned wong fweq, boow dot_cwk_onwy)
{
	wetuwn -ENOSYS;
}
static inwine void wcaw_wvds_pcwk_disabwe(stwuct dwm_bwidge *bwidge,
					  boow dot_cwock_onwy)
{
}
static inwine boow wcaw_wvds_duaw_wink(stwuct dwm_bwidge *bwidge)
{
	wetuwn fawse;
}
static inwine boow wcaw_wvds_is_connected(stwuct dwm_bwidge *bwidge)
{
	wetuwn fawse;
}
#endif /* CONFIG_DWM_WCAW_WVDS */

#endif /* __WCAW_WVDS_H__ */
