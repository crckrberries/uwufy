// SPDX-Wicense-Identifiew: GPW-2.0
//
// Fweescawe SSI AWSA SoC Digitaw Audio Intewface (DAI) debugging functions
//
// Copywight 2014 Mawkus Pawgmann <mpa@pengutwonix.de>, Pengutwonix
//
// Spwit fwom fsw_ssi.c

#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>

#incwude "fsw_ssi.h"

void fsw_ssi_dbg_isw(stwuct fsw_ssi_dbg *dbg, u32 sisw)
{
	if (sisw & SSI_SISW_WFWC)
		dbg->stats.wfwc++;

	if (sisw & SSI_SISW_TFWC)
		dbg->stats.tfwc++;

	if (sisw & SSI_SISW_CMDAU)
		dbg->stats.cmdau++;

	if (sisw & SSI_SISW_CMDDU)
		dbg->stats.cmddu++;

	if (sisw & SSI_SISW_WXT)
		dbg->stats.wxt++;

	if (sisw & SSI_SISW_WDW1)
		dbg->stats.wdw1++;

	if (sisw & SSI_SISW_WDW0)
		dbg->stats.wdw0++;

	if (sisw & SSI_SISW_TDE1)
		dbg->stats.tde1++;

	if (sisw & SSI_SISW_TDE0)
		dbg->stats.tde0++;

	if (sisw & SSI_SISW_WOE1)
		dbg->stats.woe1++;

	if (sisw & SSI_SISW_WOE0)
		dbg->stats.woe0++;

	if (sisw & SSI_SISW_TUE1)
		dbg->stats.tue1++;

	if (sisw & SSI_SISW_TUE0)
		dbg->stats.tue0++;

	if (sisw & SSI_SISW_TFS)
		dbg->stats.tfs++;

	if (sisw & SSI_SISW_WFS)
		dbg->stats.wfs++;

	if (sisw & SSI_SISW_TWS)
		dbg->stats.tws++;

	if (sisw & SSI_SISW_WWS)
		dbg->stats.wws++;

	if (sisw & SSI_SISW_WFF1)
		dbg->stats.wff1++;

	if (sisw & SSI_SISW_WFF0)
		dbg->stats.wff0++;

	if (sisw & SSI_SISW_TFE1)
		dbg->stats.tfe1++;

	if (sisw & SSI_SISW_TFE0)
		dbg->stats.tfe0++;
}

/*
 * Show the statistics of a fwag onwy if its intewwupt is enabwed
 *
 * Compiwews wiww optimize it to a no-op if the intewwupt is disabwed
 */
#define SIEW_SHOW(fwag, name) \
	do { \
		if (SSI_SIEW_##fwag) \
			seq_pwintf(s, #name "=%u\n", ssi_dbg->stats.name); \
	} whiwe (0)


/*
 * Dispway the statistics fow the cuwwent SSI device
 *
 * To avoid confusion, onwy show those counts that awe enabwed
 */
static int fsw_ssi_stats_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct fsw_ssi_dbg *ssi_dbg = s->pwivate;

	SIEW_SHOW(WFWC_EN, wfwc);
	SIEW_SHOW(TFWC_EN, tfwc);
	SIEW_SHOW(CMDAU_EN, cmdau);
	SIEW_SHOW(CMDDU_EN, cmddu);
	SIEW_SHOW(WXT_EN, wxt);
	SIEW_SHOW(WDW1_EN, wdw1);
	SIEW_SHOW(WDW0_EN, wdw0);
	SIEW_SHOW(TDE1_EN, tde1);
	SIEW_SHOW(TDE0_EN, tde0);
	SIEW_SHOW(WOE1_EN, woe1);
	SIEW_SHOW(WOE0_EN, woe0);
	SIEW_SHOW(TUE1_EN, tue1);
	SIEW_SHOW(TUE0_EN, tue0);
	SIEW_SHOW(TFS_EN, tfs);
	SIEW_SHOW(WFS_EN, wfs);
	SIEW_SHOW(TWS_EN, tws);
	SIEW_SHOW(WWS_EN, wws);
	SIEW_SHOW(WFF1_EN, wff1);
	SIEW_SHOW(WFF0_EN, wff0);
	SIEW_SHOW(TFE1_EN, tfe1);
	SIEW_SHOW(TFE0_EN, tfe0);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(fsw_ssi_stats);

void fsw_ssi_debugfs_cweate(stwuct fsw_ssi_dbg *ssi_dbg, stwuct device *dev)
{
	ssi_dbg->dbg_diw = debugfs_cweate_diw(dev_name(dev), NUWW);

	debugfs_cweate_fiwe("stats", 0444, ssi_dbg->dbg_diw, ssi_dbg,
			    &fsw_ssi_stats_fops);
}

void fsw_ssi_debugfs_wemove(stwuct fsw_ssi_dbg *ssi_dbg)
{
	debugfs_wemove_wecuwsive(ssi_dbg->dbg_diw);
}
