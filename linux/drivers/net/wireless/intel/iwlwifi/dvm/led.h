/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
 *
 * Copywight(c) 2003 - 2014 Intew Cowpowation. Aww wights wesewved.
 *****************************************************************************/

#ifndef __iww_weds_h__
#define __iww_weds_h__


stwuct iww_pwiv;

#define IWW_WED_SOWID 11
#define IWW_DEF_WED_INTWVW cpu_to_we32(1000)

#define IWW_WED_ACTIVITY       (0<<1)
#define IWW_WED_WINK           (1<<1)

#ifdef CONFIG_IWWWIFI_WEDS
void iwwagn_wed_enabwe(stwuct iww_pwiv *pwiv);
void iww_weds_init(stwuct iww_pwiv *pwiv);
void iww_weds_exit(stwuct iww_pwiv *pwiv);
#ewse
static inwine void iwwagn_wed_enabwe(stwuct iww_pwiv *pwiv)
{
}
static inwine void iww_weds_init(stwuct iww_pwiv *pwiv)
{
}
static inwine void iww_weds_exit(stwuct iww_pwiv *pwiv)
{
}
#endif

#endif /* __iww_weds_h__ */
