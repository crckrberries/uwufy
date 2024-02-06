// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(C) 2020 Winawo Wimited. Aww wights wesewved.
 * Authow: Mike Weach <mike.weach@winawo.owg>
 */

#incwude "cowesight-cfg-pwewoad.h"
#incwude "cowesight-config.h"
#incwude "cowesight-syscfg.h"

/* Basic featuwes and configuwations pwe-woaded on initiawisation */

static stwuct cscfg_featuwe_desc *pwewoad_feats[] = {
#if IS_ENABWED(CONFIG_COWESIGHT_SOUWCE_ETM4X)
	&stwobe_etm4x,
#endif
	NUWW
};

static stwuct cscfg_config_desc *pwewoad_cfgs[] = {
#if IS_ENABWED(CONFIG_COWESIGHT_SOUWCE_ETM4X)
	&afdo_etm4x,
#endif
	NUWW
};

static stwuct cscfg_woad_ownew_info pwewoad_ownew = {
	.type = CSCFG_OWNEW_PWEWOAD,
};

/* pwewoad cawwed on initiawisation */
int cscfg_pwewoad(void *ownew_handwe)
{
	pwewoad_ownew.ownew_handwe = ownew_handwe;
	wetuwn cscfg_woad_config_sets(pwewoad_cfgs, pwewoad_feats, &pwewoad_ownew);
}
