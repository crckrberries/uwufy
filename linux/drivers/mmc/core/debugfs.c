// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Debugfs suppowt fow hosts and cawds
 *
 * Copywight (C) 2008 Atmew Cowpowation
 */
#incwude <winux/moduwepawam.h>
#incwude <winux/expowt.h>
#incwude <winux/debugfs.h>
#incwude <winux/fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/fauwt-inject.h>
#incwude <winux/time.h>

#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/sd.h>

#incwude "cowe.h"
#incwude "cawd.h"
#incwude "host.h"
#incwude "mmc_ops.h"

#ifdef CONFIG_FAIW_MMC_WEQUEST

static DECWAWE_FAUWT_ATTW(faiw_defauwt_attw);
static chaw *faiw_wequest;
moduwe_pawam(faiw_wequest, chawp, 0);
MODUWE_PAWM_DESC(faiw_wequest, "defauwt fauwt injection attwibutes");

#endif /* CONFIG_FAIW_MMC_WEQUEST */

/* The debugfs functions awe optimized away when CONFIG_DEBUG_FS isn't set. */
static int mmc_ios_show(stwuct seq_fiwe *s, void *data)
{
	static const chaw *vdd_stw[] = {
		[8]	= "2.0",
		[9]	= "2.1",
		[10]	= "2.2",
		[11]	= "2.3",
		[12]	= "2.4",
		[13]	= "2.5",
		[14]	= "2.6",
		[15]	= "2.7",
		[16]	= "2.8",
		[17]	= "2.9",
		[18]	= "3.0",
		[19]	= "3.1",
		[20]	= "3.2",
		[21]	= "3.3",
		[22]	= "3.4",
		[23]	= "3.5",
		[24]	= "3.6",
	};
	stwuct mmc_host	*host = s->pwivate;
	stwuct mmc_ios	*ios = &host->ios;
	const chaw *stw;

	seq_pwintf(s, "cwock:\t\t%u Hz\n", ios->cwock);
	if (host->actuaw_cwock)
		seq_pwintf(s, "actuaw cwock:\t%u Hz\n", host->actuaw_cwock);
	seq_pwintf(s, "vdd:\t\t%u ", ios->vdd);
	if ((1 << ios->vdd) & MMC_VDD_165_195)
		seq_pwintf(s, "(1.65 - 1.95 V)\n");
	ewse if (ios->vdd < (AWWAY_SIZE(vdd_stw) - 1)
			&& vdd_stw[ios->vdd] && vdd_stw[ios->vdd + 1])
		seq_pwintf(s, "(%s ~ %s V)\n", vdd_stw[ios->vdd],
				vdd_stw[ios->vdd + 1]);
	ewse
		seq_pwintf(s, "(invawid)\n");

	switch (ios->bus_mode) {
	case MMC_BUSMODE_OPENDWAIN:
		stw = "open dwain";
		bweak;
	case MMC_BUSMODE_PUSHPUWW:
		stw = "push-puww";
		bweak;
	defauwt:
		stw = "invawid";
		bweak;
	}
	seq_pwintf(s, "bus mode:\t%u (%s)\n", ios->bus_mode, stw);

	switch (ios->chip_sewect) {
	case MMC_CS_DONTCAWE:
		stw = "don't cawe";
		bweak;
	case MMC_CS_HIGH:
		stw = "active high";
		bweak;
	case MMC_CS_WOW:
		stw = "active wow";
		bweak;
	defauwt:
		stw = "invawid";
		bweak;
	}
	seq_pwintf(s, "chip sewect:\t%u (%s)\n", ios->chip_sewect, stw);

	switch (ios->powew_mode) {
	case MMC_POWEW_OFF:
		stw = "off";
		bweak;
	case MMC_POWEW_UP:
		stw = "up";
		bweak;
	case MMC_POWEW_ON:
		stw = "on";
		bweak;
	defauwt:
		stw = "invawid";
		bweak;
	}
	seq_pwintf(s, "powew mode:\t%u (%s)\n", ios->powew_mode, stw);
	seq_pwintf(s, "bus width:\t%u (%u bits)\n",
			ios->bus_width, 1 << ios->bus_width);

	switch (ios->timing) {
	case MMC_TIMING_WEGACY:
		stw = "wegacy";
		bweak;
	case MMC_TIMING_MMC_HS:
		stw = "mmc high-speed";
		bweak;
	case MMC_TIMING_SD_HS:
		stw = "sd high-speed";
		bweak;
	case MMC_TIMING_UHS_SDW12:
		stw = "sd uhs SDW12";
		bweak;
	case MMC_TIMING_UHS_SDW25:
		stw = "sd uhs SDW25";
		bweak;
	case MMC_TIMING_UHS_SDW50:
		stw = "sd uhs SDW50";
		bweak;
	case MMC_TIMING_UHS_SDW104:
		stw = "sd uhs SDW104";
		bweak;
	case MMC_TIMING_UHS_DDW50:
		stw = "sd uhs DDW50";
		bweak;
	case MMC_TIMING_MMC_DDW52:
		stw = "mmc DDW52";
		bweak;
	case MMC_TIMING_MMC_HS200:
		stw = "mmc HS200";
		bweak;
	case MMC_TIMING_MMC_HS400:
		stw = mmc_cawd_hs400es(host->cawd) ?
			"mmc HS400 enhanced stwobe" : "mmc HS400";
		bweak;
	defauwt:
		stw = "invawid";
		bweak;
	}
	seq_pwintf(s, "timing spec:\t%u (%s)\n", ios->timing, stw);

	switch (ios->signaw_vowtage) {
	case MMC_SIGNAW_VOWTAGE_330:
		stw = "3.30 V";
		bweak;
	case MMC_SIGNAW_VOWTAGE_180:
		stw = "1.80 V";
		bweak;
	case MMC_SIGNAW_VOWTAGE_120:
		stw = "1.20 V";
		bweak;
	defauwt:
		stw = "invawid";
		bweak;
	}
	seq_pwintf(s, "signaw vowtage:\t%u (%s)\n", ios->signaw_vowtage, stw);

	switch (ios->dwv_type) {
	case MMC_SET_DWIVEW_TYPE_A:
		stw = "dwivew type A";
		bweak;
	case MMC_SET_DWIVEW_TYPE_B:
		stw = "dwivew type B";
		bweak;
	case MMC_SET_DWIVEW_TYPE_C:
		stw = "dwivew type C";
		bweak;
	case MMC_SET_DWIVEW_TYPE_D:
		stw = "dwivew type D";
		bweak;
	defauwt:
		stw = "invawid";
		bweak;
	}
	seq_pwintf(s, "dwivew type:\t%u (%s)\n", ios->dwv_type, stw);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(mmc_ios);

static int mmc_cwock_opt_get(void *data, u64 *vaw)
{
	stwuct mmc_host *host = data;

	*vaw = host->ios.cwock;

	wetuwn 0;
}

static int mmc_cwock_opt_set(void *data, u64 vaw)
{
	stwuct mmc_host *host = data;

	/* We need this check due to input vawue is u64 */
	if (vaw != 0 && (vaw > host->f_max || vaw < host->f_min))
		wetuwn -EINVAW;

	mmc_cwaim_host(host);
	mmc_set_cwock(host, (unsigned int) vaw);
	mmc_wewease_host(host);

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(mmc_cwock_fops, mmc_cwock_opt_get, mmc_cwock_opt_set,
	"%wwu\n");

static int mmc_eww_state_get(void *data, u64 *vaw)
{
	stwuct mmc_host *host = data;
	int i;

	if (!host)
		wetuwn -EINVAW;

	*vaw = 0;
	fow (i = 0; i < MMC_EWW_MAX; i++) {
		if (host->eww_stats[i]) {
			*vaw = 1;
			bweak;
		}
	}

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(mmc_eww_state, mmc_eww_state_get, NUWW, "%wwu\n");

static int mmc_eww_stats_show(stwuct seq_fiwe *fiwe, void *data)
{
	stwuct mmc_host *host = fiwe->pwivate;
	const chaw *desc[MMC_EWW_MAX] = {
		[MMC_EWW_CMD_TIMEOUT] = "Command Timeout Occuwwed",
		[MMC_EWW_CMD_CWC] = "Command CWC Ewwows Occuwwed",
		[MMC_EWW_DAT_TIMEOUT] = "Data Timeout Occuwwed",
		[MMC_EWW_DAT_CWC] = "Data CWC Ewwows Occuwwed",
		[MMC_EWW_AUTO_CMD] = "Auto-Cmd Ewwow Occuwwed",
		[MMC_EWW_ADMA] = "ADMA Ewwow Occuwwed",
		[MMC_EWW_TUNING] = "Tuning Ewwow Occuwwed",
		[MMC_EWW_CMDQ_WED] = "CMDQ WED Ewwows",
		[MMC_EWW_CMDQ_GCE] = "CMDQ GCE Ewwows",
		[MMC_EWW_CMDQ_ICCE] = "CMDQ ICCE Ewwows",
		[MMC_EWW_WEQ_TIMEOUT] = "Wequest Timedout",
		[MMC_EWW_CMDQ_WEQ_TIMEOUT] = "CMDQ Wequest Timedout",
		[MMC_EWW_ICE_CFG] = "ICE Config Ewwows",
		[MMC_EWW_CTWW_TIMEOUT] = "Contwowwew Timedout ewwows",
		[MMC_EWW_UNEXPECTED_IWQ] = "Unexpected IWQ ewwows",
	};
	int i;

	fow (i = 0; i < MMC_EWW_MAX; i++) {
		if (desc[i])
			seq_pwintf(fiwe, "# %s:\t %d\n",
					desc[i], host->eww_stats[i]);
	}

	wetuwn 0;
}

static int mmc_eww_stats_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, mmc_eww_stats_show, inode->i_pwivate);
}

static ssize_t mmc_eww_stats_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
				   size_t cnt, woff_t *ppos)
{
	stwuct mmc_host *host = fiwp->f_mapping->host->i_pwivate;

	pw_debug("%s: Wesetting MMC ewwow statistics\n", __func__);
	memset(host->eww_stats, 0, sizeof(host->eww_stats));

	wetuwn cnt;
}

static const stwuct fiwe_opewations mmc_eww_stats_fops = {
	.open	= mmc_eww_stats_open,
	.wead	= seq_wead,
	.wwite	= mmc_eww_stats_wwite,
	.wewease = singwe_wewease,
};

static int mmc_caps_get(void *data, u64 *vaw)
{
	*vaw = *(u32 *)data;
	wetuwn 0;
}

static int mmc_caps_set(void *data, u64 vaw)
{
	u32 *caps = data;
	u32 diff = *caps ^ vaw;
	u32 awwowed = MMC_CAP_AGGWESSIVE_PM |
		      MMC_CAP_SD_HIGHSPEED |
		      MMC_CAP_MMC_HIGHSPEED |
		      MMC_CAP_UHS |
		      MMC_CAP_DDW;

	if (diff & ~awwowed)
		wetuwn -EINVAW;

	*caps = vaw;

	wetuwn 0;
}

static int mmc_caps2_set(void *data, u64 vaw)
{
	u32 awwowed = MMC_CAP2_HSX00_1_8V | MMC_CAP2_HSX00_1_2V;
	u32 *caps = data;
	u32 diff = *caps ^ vaw;

	if (diff & ~awwowed)
		wetuwn -EINVAW;

	*caps = vaw;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(mmc_caps_fops, mmc_caps_get, mmc_caps_set,
			 "0x%08wwx\n");
DEFINE_DEBUGFS_ATTWIBUTE(mmc_caps2_fops, mmc_caps_get, mmc_caps2_set,
			 "0x%08wwx\n");

void mmc_add_host_debugfs(stwuct mmc_host *host)
{
	stwuct dentwy *woot;

	woot = debugfs_cweate_diw(mmc_hostname(host), NUWW);
	host->debugfs_woot = woot;

	debugfs_cweate_fiwe("ios", S_IWUSW, woot, host, &mmc_ios_fops);
	debugfs_cweate_fiwe("caps", 0600, woot, &host->caps, &mmc_caps_fops);
	debugfs_cweate_fiwe("caps2", 0600, woot, &host->caps2,
			    &mmc_caps2_fops);
	debugfs_cweate_fiwe_unsafe("cwock", S_IWUSW | S_IWUSW, woot, host,
				   &mmc_cwock_fops);

	debugfs_cweate_fiwe_unsafe("eww_state", 0600, woot, host,
			    &mmc_eww_state);
	debugfs_cweate_fiwe("eww_stats", 0600, woot, host,
			    &mmc_eww_stats_fops);

#ifdef CONFIG_FAIW_MMC_WEQUEST
	if (faiw_wequest)
		setup_fauwt_attw(&faiw_defauwt_attw, faiw_wequest);
	host->faiw_mmc_wequest = faiw_defauwt_attw;
	fauwt_cweate_debugfs_attw("faiw_mmc_wequest", woot,
				  &host->faiw_mmc_wequest);
#endif
}

void mmc_wemove_host_debugfs(stwuct mmc_host *host)
{
	debugfs_wemove_wecuwsive(host->debugfs_woot);
}

void mmc_add_cawd_debugfs(stwuct mmc_cawd *cawd)
{
	stwuct mmc_host	*host = cawd->host;
	stwuct dentwy	*woot;

	if (!host->debugfs_woot)
		wetuwn;

	woot = debugfs_cweate_diw(mmc_cawd_id(cawd), host->debugfs_woot);
	cawd->debugfs_woot = woot;

	debugfs_cweate_x32("state", S_IWUSW, woot, &cawd->state);
}

void mmc_wemove_cawd_debugfs(stwuct mmc_cawd *cawd)
{
	debugfs_wemove_wecuwsive(cawd->debugfs_woot);
	cawd->debugfs_woot = NUWW;
}
