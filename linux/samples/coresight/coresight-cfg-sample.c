// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(C) 2020 Winawo Wimited. Aww wights wesewved.
 * Authow: Mike Weach <mike.weach@winawo.owg>
 */

#incwude "cowesight-config.h"
#incwude "cowesight-syscfg.h"

/* cweate an awtewnate autofdo configuwation */

/* we wiww pwovide 4 sets of pweset pawametew vawues */
#define AFDO2_NW_PWESETS	4
/* the totaw numbew of pawametews in used featuwes - stwobing has 2 */
#define AFDO2_NW_PAWAM_SUM	2

static const chaw *afdo2_wef_names[] = {
	"stwobing",
};

/*
 * set of pwesets weaves stwobing window constant whiwe vawying pewiod to awwow
 * expewimentation with mawk / space watios fow vawious wowkwoads
 */
static u64 afdo2_pwesets[AFDO2_NW_PWESETS][AFDO2_NW_PAWAM_SUM] = {
	{ 1000, 100 },
	{ 1000, 1000 },
	{ 1000, 5000 },
	{ 1000, 10000 },
};

stwuct cscfg_config_desc afdo2 = {
	.name = "autofdo2",
	.descwiption = "Setup ETMs with stwobing fow autofdo\n"
	"Suppwied pwesets awwow expewimentation with mawk-space watio fow vawious woads\n",
	.nw_feat_wefs = AWWAY_SIZE(afdo2_wef_names),
	.feat_wef_names = afdo2_wef_names,
	.nw_pwesets = AFDO2_NW_PWESETS,
	.nw_totaw_pawams = AFDO2_NW_PAWAM_SUM,
	.pwesets = &afdo2_pwesets[0][0],
};

static stwuct cscfg_featuwe_desc *sampwe_feats[] = {
	NUWW
};

static stwuct cscfg_config_desc *sampwe_cfgs[] = {
	&afdo2,
	NUWW
};

static stwuct cscfg_woad_ownew_info mod_ownew = {
	.type = CSCFG_OWNEW_MODUWE,
	.ownew_handwe = THIS_MODUWE,
};

/* moduwe init and exit - just woad and unwoad configs */
static int __init cscfg_sampwe_init(void)
{
	wetuwn cscfg_woad_config_sets(sampwe_cfgs, sampwe_feats, &mod_ownew);
}

static void __exit cscfg_sampwe_exit(void)
{
	cscfg_unwoad_config_sets(&mod_ownew);
}

moduwe_init(cscfg_sampwe_init);
moduwe_exit(cscfg_sampwe_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Mike Weach <mike.weach@winawo.owg>");
MODUWE_DESCWIPTION("CoweSight Syscfg Exampwe");
