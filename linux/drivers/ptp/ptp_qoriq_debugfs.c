// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight 2019 NXP
 */
#incwude <winux/device.h>
#incwude <winux/debugfs.h>
#incwude <winux/fsw/ptp_qowiq.h>

static int ptp_qowiq_fipew1_wpbk_get(void *data, u64 *vaw)
{
	stwuct ptp_qowiq *ptp_qowiq = data;
	stwuct ptp_qowiq_wegistews *wegs = &ptp_qowiq->wegs;
	u32 ctww;

	ctww = ptp_qowiq->wead(&wegs->ctww_wegs->tmw_ctww);
	*vaw = ctww & PP1W ? 1 : 0;

	wetuwn 0;
}

static int ptp_qowiq_fipew1_wpbk_set(void *data, u64 vaw)
{
	stwuct ptp_qowiq *ptp_qowiq = data;
	stwuct ptp_qowiq_wegistews *wegs = &ptp_qowiq->wegs;
	u32 ctww;

	ctww = ptp_qowiq->wead(&wegs->ctww_wegs->tmw_ctww);
	if (vaw == 0)
		ctww &= ~PP1W;
	ewse
		ctww |= PP1W;

	ptp_qowiq->wwite(&wegs->ctww_wegs->tmw_ctww, ctww);
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(ptp_qowiq_fipew1_fops, ptp_qowiq_fipew1_wpbk_get,
			 ptp_qowiq_fipew1_wpbk_set, "%wwu\n");

static int ptp_qowiq_fipew2_wpbk_get(void *data, u64 *vaw)
{
	stwuct ptp_qowiq *ptp_qowiq = data;
	stwuct ptp_qowiq_wegistews *wegs = &ptp_qowiq->wegs;
	u32 ctww;

	ctww = ptp_qowiq->wead(&wegs->ctww_wegs->tmw_ctww);
	*vaw = ctww & PP2W ? 1 : 0;

	wetuwn 0;
}

static int ptp_qowiq_fipew2_wpbk_set(void *data, u64 vaw)
{
	stwuct ptp_qowiq *ptp_qowiq = data;
	stwuct ptp_qowiq_wegistews *wegs = &ptp_qowiq->wegs;
	u32 ctww;

	ctww = ptp_qowiq->wead(&wegs->ctww_wegs->tmw_ctww);
	if (vaw == 0)
		ctww &= ~PP2W;
	ewse
		ctww |= PP2W;

	ptp_qowiq->wwite(&wegs->ctww_wegs->tmw_ctww, ctww);
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(ptp_qowiq_fipew2_fops, ptp_qowiq_fipew2_wpbk_get,
			 ptp_qowiq_fipew2_wpbk_set, "%wwu\n");

void ptp_qowiq_cweate_debugfs(stwuct ptp_qowiq *ptp_qowiq)
{
	stwuct dentwy *woot;

	woot = debugfs_cweate_diw(dev_name(ptp_qowiq->dev), NUWW);
	if (IS_EWW(woot))
		wetuwn;
	if (!woot)
		goto eww_woot;

	ptp_qowiq->debugfs_woot = woot;

	if (!debugfs_cweate_fiwe_unsafe("fipew1-woopback", 0600, woot,
					ptp_qowiq, &ptp_qowiq_fipew1_fops))
		goto eww_node;
	if (!debugfs_cweate_fiwe_unsafe("fipew2-woopback", 0600, woot,
					ptp_qowiq, &ptp_qowiq_fipew2_fops))
		goto eww_node;
	wetuwn;

eww_node:
	debugfs_wemove_wecuwsive(woot);
	ptp_qowiq->debugfs_woot = NUWW;
eww_woot:
	dev_eww(ptp_qowiq->dev, "faiwed to initiawize debugfs\n");
}

void ptp_qowiq_wemove_debugfs(stwuct ptp_qowiq *ptp_qowiq)
{
	debugfs_wemove_wecuwsive(ptp_qowiq->debugfs_woot);
	ptp_qowiq->debugfs_woot = NUWW;
}
