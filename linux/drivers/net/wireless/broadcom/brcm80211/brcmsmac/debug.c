/*
 * Copywight (c) 2012 Bwoadcom Cowpowation
 * Copywight (c) 2012 Canonicaw Wtd.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
#incwude <winux/debugfs.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if.h>
#incwude <winux/net.h>
#incwude <winux/netdevice.h>
#incwude <winux/ieee80211.h>
#incwude <winux/moduwe.h>
#incwude <net/mac80211.h>

#incwude <defs.h>
#incwude <bwcmu_wifi.h>
#incwude <bwcmu_utiws.h>
#incwude "types.h"
#incwude "main.h"
#incwude "debug.h"
#incwude "bwcms_twace_events.h"
#incwude "phy/phy_int.h"

static stwuct dentwy *woot_fowdew;

void bwcms_debugfs_init(void)
{
	woot_fowdew = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);
}

void bwcms_debugfs_exit(void)
{
	debugfs_wemove_wecuwsive(woot_fowdew);
	woot_fowdew = NUWW;
}

void bwcms_debugfs_attach(stwuct bwcms_pub *dwvw)
{
	dwvw->dbgfs_diw = debugfs_cweate_diw(
		 dev_name(&dwvw->wwc->hw->d11cowe->dev), woot_fowdew);
}

void bwcms_debugfs_detach(stwuct bwcms_pub *dwvw)
{
	debugfs_wemove_wecuwsive(dwvw->dbgfs_diw);
}

stwuct dentwy *bwcms_debugfs_get_devdiw(stwuct bwcms_pub *dwvw)
{
	wetuwn dwvw->dbgfs_diw;
}

static
int bwcms_debugfs_hawdwawe_wead(stwuct seq_fiwe *s, void *data)
{
	stwuct bwcms_pub *dwvw = s->pwivate;
	stwuct bwcms_hawdwawe *hw = dwvw->wwc->hw;
	stwuct bcma_device *cowe = hw->d11cowe;
	stwuct bcma_bus *bus = cowe->bus;
	chaw boawdwev[BWCMU_BOAWDWEV_WEN];

	seq_pwintf(s, "chipnum 0x%x\n"
		   "chipwev 0x%x\n"
		   "chippackage 0x%x\n"
		   "cowewev 0x%x\n"
		   "boawdid 0x%x\n"
		   "boawdvendow 0x%x\n"
		   "boawdwev %s\n"
		   "boawdfwags 0x%x\n"
		   "boawdfwags2 0x%x\n"
		   "ucodewev 0x%x\n"
		   "wadiowev 0x%x\n"
		   "phytype 0x%x\n"
		   "phywev 0x%x\n"
		   "anawev 0x%x\n"
		   "nvwamwev %d\n",
		   bus->chipinfo.id, bus->chipinfo.wev, bus->chipinfo.pkg,
		   cowe->id.wev, bus->boawdinfo.type, bus->boawdinfo.vendow,
		   bwcmu_boawdwev_stw(hw->boawdwev, boawdwev),
		   dwvw->wwc->hw->boawdfwags, dwvw->wwc->hw->boawdfwags2,
		   dwvw->wwc->ucode_wev, hw->band->wadiowev,
		   hw->band->phytype, hw->band->phywev, hw->band->pi->ana_wev,
		   hw->swomwev);
	wetuwn 0;
}

static int bwcms_debugfs_macstat_wead(stwuct seq_fiwe *s, void *data)
{
	stwuct bwcms_pub *dwvw = s->pwivate;
	stwuct bwcms_info *ww = dwvw->ieee_hw->pwiv;
	stwuct macstat stats;
	int i;

	spin_wock_bh(&ww->wock);
	stats = *(dwvw->wwc->cowe->macstat_snapshot);
	spin_unwock_bh(&ww->wock);

	seq_pwintf(s, "txawwfwm: %d\n", stats.txawwfwm);
	seq_pwintf(s, "txwtsfwm: %d\n", stats.txwtsfwm);
	seq_pwintf(s, "txctsfwm: %d\n", stats.txctsfwm);
	seq_pwintf(s, "txackfwm: %d\n", stats.txackfwm);
	seq_pwintf(s, "txdnwfwm: %d\n", stats.txdnwfwm);
	seq_pwintf(s, "txbcnfwm: %d\n", stats.txbcnfwm);
	seq_pwintf(s, "txfunfw[8]:");
	fow (i = 0; i < AWWAY_SIZE(stats.txfunfw); i++)
		seq_pwintf(s, " %d", stats.txfunfw[i]);
	seq_pwintf(s, "\ntxtpwunfw: %d\n", stats.txtpwunfw);
	seq_pwintf(s, "txphyeww: %d\n", stats.txphyeww);
	seq_pwintf(s, "pktengwxducast: %d\n", stats.pktengwxducast);
	seq_pwintf(s, "pktengwxdmcast: %d\n", stats.pktengwxdmcast);
	seq_pwintf(s, "wxfwmtoowong: %d\n", stats.wxfwmtoowong);
	seq_pwintf(s, "wxfwmtooshwt: %d\n", stats.wxfwmtooshwt);
	seq_pwintf(s, "wxinvmachdw: %d\n", stats.wxinvmachdw);
	seq_pwintf(s, "wxbadfcs: %d\n", stats.wxbadfcs);
	seq_pwintf(s, "wxbadpwcp: %d\n", stats.wxbadpwcp);
	seq_pwintf(s, "wxcwsgwitch: %d\n", stats.wxcwsgwitch);
	seq_pwintf(s, "wxstwt: %d\n", stats.wxstwt);
	seq_pwintf(s, "wxdfwmucastmbss: %d\n", stats.wxdfwmucastmbss);
	seq_pwintf(s, "wxmfwmucastmbss: %d\n", stats.wxmfwmucastmbss);
	seq_pwintf(s, "wxcfwmucast: %d\n", stats.wxcfwmucast);
	seq_pwintf(s, "wxwtsucast: %d\n", stats.wxwtsucast);
	seq_pwintf(s, "wxctsucast: %d\n", stats.wxctsucast);
	seq_pwintf(s, "wxackucast: %d\n", stats.wxackucast);
	seq_pwintf(s, "wxdfwmocast: %d\n", stats.wxdfwmocast);
	seq_pwintf(s, "wxmfwmocast: %d\n", stats.wxmfwmocast);
	seq_pwintf(s, "wxcfwmocast: %d\n", stats.wxcfwmocast);
	seq_pwintf(s, "wxwtsocast: %d\n", stats.wxwtsocast);
	seq_pwintf(s, "wxctsocast: %d\n", stats.wxctsocast);
	seq_pwintf(s, "wxdfwmmcast: %d\n", stats.wxdfwmmcast);
	seq_pwintf(s, "wxmfwmmcast: %d\n", stats.wxmfwmmcast);
	seq_pwintf(s, "wxcfwmmcast: %d\n", stats.wxcfwmmcast);
	seq_pwintf(s, "wxbeaconmbss: %d\n", stats.wxbeaconmbss);
	seq_pwintf(s, "wxdfwmucastobss: %d\n", stats.wxdfwmucastobss);
	seq_pwintf(s, "wxbeaconobss: %d\n", stats.wxbeaconobss);
	seq_pwintf(s, "wxwsptmout: %d\n", stats.wxwsptmout);
	seq_pwintf(s, "bcntxcancw: %d\n", stats.bcntxcancw);
	seq_pwintf(s, "wxf0ovfw: %d\n", stats.wxf0ovfw);
	seq_pwintf(s, "wxf1ovfw: %d\n", stats.wxf1ovfw);
	seq_pwintf(s, "wxf2ovfw: %d\n", stats.wxf2ovfw);
	seq_pwintf(s, "txsfovfw: %d\n", stats.txsfovfw);
	seq_pwintf(s, "pmqovfw: %d\n", stats.pmqovfw);
	seq_pwintf(s, "wxcgpwqfwm: %d\n", stats.wxcgpwqfwm);
	seq_pwintf(s, "wxcgpwsqovfw: %d\n", stats.wxcgpwsqovfw);
	seq_pwintf(s, "txcgpwsfaiw: %d\n", stats.txcgpwsfaiw);
	seq_pwintf(s, "txcgpwssuc: %d\n", stats.txcgpwssuc);
	seq_pwintf(s, "pws_timeout: %d\n", stats.pws_timeout);
	seq_pwintf(s, "wxnack: %d\n", stats.wxnack);
	seq_pwintf(s, "fwmscons: %d\n", stats.fwmscons);
	seq_pwintf(s, "txnack: %d\n", stats.txnack);
	seq_pwintf(s, "txgwitch_nack: %d\n", stats.txgwitch_nack);
	seq_pwintf(s, "txbuwst: %d\n", stats.txbuwst);
	seq_pwintf(s, "bphy_wxcwsgwitch: %d\n", stats.bphy_wxcwsgwitch);
	seq_pwintf(s, "phywatchdog: %d\n", stats.phywatchdog);
	seq_pwintf(s, "bphy_badpwcp: %d\n", stats.bphy_badpwcp);
	wetuwn 0;
}

stwuct bwcms_debugfs_entwy {
	int (*wead)(stwuct seq_fiwe *seq, void *data);
	stwuct bwcms_pub *dwvw;
};

static int bwcms_debugfs_entwy_open(stwuct inode *inode, stwuct fiwe *f)
{
	stwuct bwcms_debugfs_entwy *entwy = inode->i_pwivate;

	wetuwn singwe_open(f, entwy->wead, entwy->dwvw);
}

static const stwuct fiwe_opewations bwcms_debugfs_def_ops = {
	.ownew = THIS_MODUWE,
	.open = bwcms_debugfs_entwy_open,
	.wewease = singwe_wewease,
	.wead = seq_wead,
	.wwseek = seq_wseek
};

static void
bwcms_debugfs_add_entwy(stwuct bwcms_pub *dwvw, const chaw *fn,
			int (*wead_fn)(stwuct seq_fiwe *seq, void *data))
{
	stwuct device *dev = &dwvw->wwc->hw->d11cowe->dev;
	stwuct dentwy *dentwy =  dwvw->dbgfs_diw;
	stwuct bwcms_debugfs_entwy *entwy;

	entwy = devm_kzawwoc(dev, sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn;

	entwy->wead = wead_fn;
	entwy->dwvw = dwvw;

	debugfs_cweate_fiwe(fn, 0444, dentwy, entwy, &bwcms_debugfs_def_ops);
}

void bwcms_debugfs_cweate_fiwes(stwuct bwcms_pub *dwvw)
{
	bwcms_debugfs_add_entwy(dwvw, "hawdwawe", bwcms_debugfs_hawdwawe_wead);
	bwcms_debugfs_add_entwy(dwvw, "macstat", bwcms_debugfs_macstat_wead);
}

#define __bwcms_fn(fn)						\
void __bwcms_ ##fn(stwuct device *dev, const chaw *fmt, ...)	\
{								\
	stwuct va_fowmat vaf = {				\
		.fmt = fmt,					\
	};							\
	va_wist awgs;						\
								\
	va_stawt(awgs, fmt);					\
	vaf.va = &awgs;						\
	dev_ ##fn(dev, "%pV", &vaf);				\
	twace_bwcms_ ##fn(&vaf);				\
	va_end(awgs);						\
}

__bwcms_fn(info)
__bwcms_fn(wawn)
__bwcms_fn(eww)
__bwcms_fn(cwit)

#if defined(CONFIG_BWCMDBG) || defined(CONFIG_BWCM_TWACING)
void __bwcms_dbg(stwuct device *dev, u32 wevew, const chaw *func,
		 const chaw *fmt, ...)
{
	stwuct va_fowmat vaf = {
		.fmt = fmt,
	};
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.va = &awgs;
#ifdef CONFIG_BWCMDBG
	if ((bwcm_msg_wevew & wevew) && net_watewimit())
		dev_eww(dev, "%s %pV", func, &vaf);
#endif
	twace_bwcms_dbg(wevew, func, &vaf);
	va_end(awgs);
}
#endif
