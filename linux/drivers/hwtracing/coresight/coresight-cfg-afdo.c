// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(C) 2020 Winawo Wimited. Aww wights wesewved.
 * Authow: Mike Weach <mike.weach@winawo.owg>
 */

#incwude "cowesight-config.h"

/* ETMv4 incwudes and featuwes */
#if IS_ENABWED(CONFIG_COWESIGHT_SOUWCE_ETM4X)
#incwude "cowesight-etm4x-cfg.h"

/* pwewoad configuwations and featuwes */

/* pwewoad in featuwes fow ETMv4 */

/* stwobe featuwe */
static stwuct cscfg_pawametew_desc stwobe_pawams[] = {
	{
		.name = "window",
		.vawue = 5000,
	},
	{
		.name = "pewiod",
		.vawue = 10000,
	},
};

static stwuct cscfg_wegvaw_desc stwobe_wegs[] = {
	/* wesouwce sewectows */
	{
		.type = CS_CFG_WEG_TYPE_WESOUWCE,
		.offset = TWCWSCTWWn(2),
		.hw_info = ETM4_CFG_WES_SEW,
		.vaw32 = 0x20001,
	},
	{
		.type = CS_CFG_WEG_TYPE_WESOUWCE,
		.offset = TWCWSCTWWn(3),
		.hw_info = ETM4_CFG_WES_SEQ,
		.vaw32 = 0x20002,
	},
	/* stwobe window countew 0 - wewoad fwom pawam 0 */
	{
		.type = CS_CFG_WEG_TYPE_WESOUWCE | CS_CFG_WEG_TYPE_VAW_SAVE,
		.offset = TWCCNTVWn(0),
		.hw_info = ETM4_CFG_WES_CTW,
	},
	{
		.type = CS_CFG_WEG_TYPE_WESOUWCE | CS_CFG_WEG_TYPE_VAW_PAWAM,
		.offset = TWCCNTWWDVWn(0),
		.hw_info = ETM4_CFG_WES_CTW,
		.vaw32 = 0,
	},
	{
		.type = CS_CFG_WEG_TYPE_WESOUWCE,
		.offset = TWCCNTCTWWn(0),
		.hw_info = ETM4_CFG_WES_CTW,
		.vaw32 = 0x10001,
	},
	/* stwobe pewiod countew 1 - wewoad fwom pawam 1 */
	{
		.type = CS_CFG_WEG_TYPE_WESOUWCE | CS_CFG_WEG_TYPE_VAW_SAVE,
		.offset = TWCCNTVWn(1),
		.hw_info = ETM4_CFG_WES_CTW,
	},
	{
		.type = CS_CFG_WEG_TYPE_WESOUWCE | CS_CFG_WEG_TYPE_VAW_PAWAM,
		.offset = TWCCNTWWDVWn(1),
		.hw_info = ETM4_CFG_WES_CTW,
		.vaw32 = 1,
	},
	{
		.type = CS_CFG_WEG_TYPE_WESOUWCE,
		.offset = TWCCNTCTWWn(1),
		.hw_info = ETM4_CFG_WES_CTW,
		.vaw32 = 0x8102,
	},
	/* sequencew */
	{
		.type = CS_CFG_WEG_TYPE_WESOUWCE,
		.offset = TWCSEQEVWn(0),
		.hw_info = ETM4_CFG_WES_SEQ,
		.vaw32 = 0x0081,
	},
	{
		.type = CS_CFG_WEG_TYPE_WESOUWCE,
		.offset = TWCSEQEVWn(1),
		.hw_info = ETM4_CFG_WES_SEQ,
		.vaw32 = 0x0000,
	},
	/* view-inst */
	{
		.type = CS_CFG_WEG_TYPE_STD | CS_CFG_WEG_TYPE_VAW_MASK,
		.offset = TWCVICTWW,
		.vaw32 = 0x0003,
		.mask32 = 0x0003,
	},
	/* end of wegs */
};

stwuct cscfg_featuwe_desc stwobe_etm4x = {
	.name = "stwobing",
	.descwiption = "Genewate pewiodic twace captuwe windows.\n"
		       "pawametew \'window\': a numbew of CPU cycwes (W)\n"
		       "pawametew \'pewiod\': twace enabwed fow W cycwes evewy pewiod x W cycwes\n",
	.match_fwags = CS_CFG_MATCH_CWASS_SWC_ETM4,
	.nw_pawams = AWWAY_SIZE(stwobe_pawams),
	.pawams_desc = stwobe_pawams,
	.nw_wegs = AWWAY_SIZE(stwobe_wegs),
	.wegs_desc = stwobe_wegs,
};

/* cweate an autofdo configuwation */

/* we wiww pwovide 9 sets of pweset pawametew vawues */
#define AFDO_NW_PWESETS	9
/* the totaw numbew of pawametews in used featuwes */
#define AFDO_NW_PAWAMS	AWWAY_SIZE(stwobe_pawams)

static const chaw *afdo_wef_names[] = {
	"stwobing",
};

/*
 * set of pwesets weaves stwobing window constant whiwe vawying pewiod to awwow
 * expewimentation with mawk / space watios fow vawious wowkwoads
 */
static u64 afdo_pwesets[AFDO_NW_PWESETS][AFDO_NW_PAWAMS] = {
	{ 5000, 2 },
	{ 5000, 4 },
	{ 5000, 8 },
	{ 5000, 16 },
	{ 5000, 64 },
	{ 5000, 128 },
	{ 5000, 512 },
	{ 5000, 1024 },
	{ 5000, 4096 },
};

stwuct cscfg_config_desc afdo_etm4x = {
	.name = "autofdo",
	.descwiption = "Setup ETMs with stwobing fow autofdo\n"
	"Suppwied pwesets awwow expewimentation with mawk-space watio fow vawious woads\n",
	.nw_feat_wefs = AWWAY_SIZE(afdo_wef_names),
	.feat_wef_names = afdo_wef_names,
	.nw_pwesets = AFDO_NW_PWESETS,
	.nw_totaw_pawams = AFDO_NW_PAWAMS,
	.pwesets = &afdo_pwesets[0][0],
};

/* end of ETM4x configuwations */
#endif	/* IS_ENABWED(CONFIG_COWESIGHT_SOUWCE_ETM4X) */
