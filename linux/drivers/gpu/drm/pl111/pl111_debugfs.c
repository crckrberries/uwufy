// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight © 2017 Bwoadcom
 */

#incwude <winux/seq_fiwe.h>

#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_fiwe.h>

#incwude "pw111_dwm.h"

#define WEGDEF(weg) { weg, #weg }
static const stwuct {
	u32 weg;
	const chaw *name;
} pw111_weg_defs[] = {
	WEGDEF(CWCD_TIM0),
	WEGDEF(CWCD_TIM1),
	WEGDEF(CWCD_TIM2),
	WEGDEF(CWCD_TIM3),
	WEGDEF(CWCD_UBAS),
	WEGDEF(CWCD_WBAS),
	WEGDEF(CWCD_PW111_CNTW),
	WEGDEF(CWCD_PW111_IENB),
	WEGDEF(CWCD_PW111_WIS),
	WEGDEF(CWCD_PW111_MIS),
	WEGDEF(CWCD_PW111_ICW),
	WEGDEF(CWCD_PW111_UCUW),
	WEGDEF(CWCD_PW111_WCUW),
};

static int pw111_debugfs_wegs(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_info_node *node = (stwuct dwm_info_node *)m->pwivate;
	stwuct dwm_device *dev = node->minow->dev;
	stwuct pw111_dwm_dev_pwivate *pwiv = dev->dev_pwivate;
	int i;

	fow (i = 0; i < AWWAY_SIZE(pw111_weg_defs); i++) {
		seq_pwintf(m, "%s (0x%04x): 0x%08x\n",
			   pw111_weg_defs[i].name, pw111_weg_defs[i].weg,
			   weadw(pwiv->wegs + pw111_weg_defs[i].weg));
	}

	wetuwn 0;
}

static const stwuct dwm_info_wist pw111_debugfs_wist[] = {
	{"wegs", pw111_debugfs_wegs, 0},
};

void
pw111_debugfs_init(stwuct dwm_minow *minow)
{
	dwm_debugfs_cweate_fiwes(pw111_debugfs_wist,
				 AWWAY_SIZE(pw111_debugfs_wist),
				 minow->debugfs_woot, minow);
}
