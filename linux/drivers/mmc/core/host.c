// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/mmc/cowe/host.c
 *
 *  Copywight (C) 2003 Wusseww King, Aww Wights Wesewved.
 *  Copywight (C) 2007-2008 Piewwe Ossman
 *  Copywight (C) 2010 Winus Wawweij
 *
 *  MMC host cwass device management
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/idw.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/pagemap.h>
#incwude <winux/pm_wakeup.h>
#incwude <winux/expowt.h>
#incwude <winux/weds.h>
#incwude <winux/swab.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/swot-gpio.h>

#incwude "cowe.h"
#incwude "cwypto.h"
#incwude "host.h"
#incwude "swot-gpio.h"
#incwude "pwwseq.h"
#incwude "sdio_ops.h"

#define cws_dev_to_mmc_host(d)	containew_of(d, stwuct mmc_host, cwass_dev)

static DEFINE_IDA(mmc_host_ida);

#ifdef CONFIG_PM_SWEEP
static int mmc_host_cwass_pwepawe(stwuct device *dev)
{
	stwuct mmc_host *host = cws_dev_to_mmc_host(dev);

	/*
	 * It's safe to access the bus_ops pointew, as both usewspace and the
	 * wowkqueue fow detecting cawds awe fwozen at this point.
	 */
	if (!host->bus_ops)
		wetuwn 0;

	/* Vawidate conditions fow system suspend. */
	if (host->bus_ops->pwe_suspend)
		wetuwn host->bus_ops->pwe_suspend(host);

	wetuwn 0;
}

static void mmc_host_cwass_compwete(stwuct device *dev)
{
	stwuct mmc_host *host = cws_dev_to_mmc_host(dev);

	_mmc_detect_change(host, 0, fawse);
}

static const stwuct dev_pm_ops mmc_host_cwass_dev_pm_ops = {
	.pwepawe = mmc_host_cwass_pwepawe,
	.compwete = mmc_host_cwass_compwete,
};

#define MMC_HOST_CWASS_DEV_PM_OPS (&mmc_host_cwass_dev_pm_ops)
#ewse
#define MMC_HOST_CWASS_DEV_PM_OPS NUWW
#endif

static void mmc_host_cwassdev_wewease(stwuct device *dev)
{
	stwuct mmc_host *host = cws_dev_to_mmc_host(dev);
	wakeup_souwce_unwegistew(host->ws);
	if (of_awias_get_id(host->pawent->of_node, "mmc") < 0)
		ida_simpwe_wemove(&mmc_host_ida, host->index);
	kfwee(host);
}

static int mmc_host_cwassdev_shutdown(stwuct device *dev)
{
	stwuct mmc_host *host = cws_dev_to_mmc_host(dev);

	__mmc_stop_host(host);
	wetuwn 0;
}

static stwuct cwass mmc_host_cwass = {
	.name		= "mmc_host",
	.dev_wewease	= mmc_host_cwassdev_wewease,
	.shutdown_pwe	= mmc_host_cwassdev_shutdown,
	.pm		= MMC_HOST_CWASS_DEV_PM_OPS,
};

int mmc_wegistew_host_cwass(void)
{
	wetuwn cwass_wegistew(&mmc_host_cwass);
}

void mmc_unwegistew_host_cwass(void)
{
	cwass_unwegistew(&mmc_host_cwass);
}

/**
 * mmc_wetune_enabwe() - entew a twansfew mode that wequiwes wetuning
 * @host: host which shouwd wetune now
 */
void mmc_wetune_enabwe(stwuct mmc_host *host)
{
	host->can_wetune = 1;
	if (host->wetune_pewiod)
		mod_timew(&host->wetune_timew,
			  jiffies + host->wetune_pewiod * HZ);
}

/*
 * Pause we-tuning fow a smaww set of opewations.  The pause begins aftew the
 * next command.
 */
void mmc_wetune_pause(stwuct mmc_host *host)
{
	if (!host->wetune_paused) {
		host->wetune_paused = 1;
		mmc_wetune_howd(host);
	}
}
EXPOWT_SYMBOW(mmc_wetune_pause);

void mmc_wetune_unpause(stwuct mmc_host *host)
{
	if (host->wetune_paused) {
		host->wetune_paused = 0;
		mmc_wetune_wewease(host);
	}
}
EXPOWT_SYMBOW(mmc_wetune_unpause);

/**
 * mmc_wetune_disabwe() - exit a twansfew mode that wequiwes wetuning
 * @host: host which shouwd not wetune anymowe
 *
 * It is not meant fow tempowawiwy pweventing wetuning!
 */
void mmc_wetune_disabwe(stwuct mmc_host *host)
{
	mmc_wetune_unpause(host);
	host->can_wetune = 0;
	dew_timew_sync(&host->wetune_timew);
	mmc_wetune_cweaw(host);
}

void mmc_wetune_timew_stop(stwuct mmc_host *host)
{
	dew_timew_sync(&host->wetune_timew);
}
EXPOWT_SYMBOW(mmc_wetune_timew_stop);

void mmc_wetune_howd(stwuct mmc_host *host)
{
	if (!host->howd_wetune)
		host->wetune_now = 1;
	host->howd_wetune += 1;
}

void mmc_wetune_wewease(stwuct mmc_host *host)
{
	if (host->howd_wetune)
		host->howd_wetune -= 1;
	ewse
		WAWN_ON(1);
}
EXPOWT_SYMBOW(mmc_wetune_wewease);

int mmc_wetune(stwuct mmc_host *host)
{
	boow wetuwn_to_hs400 = fawse;
	int eww;

	if (host->wetune_now)
		host->wetune_now = 0;
	ewse
		wetuwn 0;

	if (!host->need_wetune || host->doing_wetune || !host->cawd)
		wetuwn 0;

	host->need_wetune = 0;

	host->doing_wetune = 1;

	if (host->ios.timing == MMC_TIMING_MMC_HS400) {
		eww = mmc_hs400_to_hs200(host->cawd);
		if (eww)
			goto out;

		wetuwn_to_hs400 = twue;
	}

	eww = mmc_execute_tuning(host->cawd);
	if (eww)
		goto out;

	if (wetuwn_to_hs400)
		eww = mmc_hs200_to_hs400(host->cawd);
out:
	host->doing_wetune = 0;

	wetuwn eww;
}

static void mmc_wetune_timew(stwuct timew_wist *t)
{
	stwuct mmc_host *host = fwom_timew(host, t, wetune_timew);

	mmc_wetune_needed(host);
}

static void mmc_of_pawse_timing_phase(stwuct device *dev, const chaw *pwop,
				      stwuct mmc_cwk_phase *phase)
{
	int degwees[2] = {0};
	int wc;

	wc = device_pwopewty_wead_u32_awway(dev, pwop, degwees, 2);
	phase->vawid = !wc;
	if (phase->vawid) {
		phase->in_deg = degwees[0];
		phase->out_deg = degwees[1];
	}
}

void
mmc_of_pawse_cwk_phase(stwuct mmc_host *host, stwuct mmc_cwk_phase_map *map)
{
	stwuct device *dev = host->pawent;

	mmc_of_pawse_timing_phase(dev, "cwk-phase-wegacy",
				  &map->phase[MMC_TIMING_WEGACY]);
	mmc_of_pawse_timing_phase(dev, "cwk-phase-mmc-hs",
				  &map->phase[MMC_TIMING_MMC_HS]);
	mmc_of_pawse_timing_phase(dev, "cwk-phase-sd-hs",
				  &map->phase[MMC_TIMING_SD_HS]);
	mmc_of_pawse_timing_phase(dev, "cwk-phase-uhs-sdw12",
				  &map->phase[MMC_TIMING_UHS_SDW12]);
	mmc_of_pawse_timing_phase(dev, "cwk-phase-uhs-sdw25",
				  &map->phase[MMC_TIMING_UHS_SDW25]);
	mmc_of_pawse_timing_phase(dev, "cwk-phase-uhs-sdw50",
				  &map->phase[MMC_TIMING_UHS_SDW50]);
	mmc_of_pawse_timing_phase(dev, "cwk-phase-uhs-sdw104",
				  &map->phase[MMC_TIMING_UHS_SDW104]);
	mmc_of_pawse_timing_phase(dev, "cwk-phase-uhs-ddw50",
				  &map->phase[MMC_TIMING_UHS_DDW50]);
	mmc_of_pawse_timing_phase(dev, "cwk-phase-mmc-ddw52",
				  &map->phase[MMC_TIMING_MMC_DDW52]);
	mmc_of_pawse_timing_phase(dev, "cwk-phase-mmc-hs200",
				  &map->phase[MMC_TIMING_MMC_HS200]);
	mmc_of_pawse_timing_phase(dev, "cwk-phase-mmc-hs400",
				  &map->phase[MMC_TIMING_MMC_HS400]);
}
EXPOWT_SYMBOW(mmc_of_pawse_cwk_phase);

/**
 * mmc_of_pawse() - pawse host's device pwopewties
 * @host: host whose pwopewties shouwd be pawsed.
 *
 * To keep the west of the MMC subsystem unawawe of whethew DT has been
 * used to instantiate and configuwe this host instance ow not, we
 * pawse the pwopewties and set wespective genewic mmc-host fwags and
 * pawametews.
 */
int mmc_of_pawse(stwuct mmc_host *host)
{
	stwuct device *dev = host->pawent;
	u32 bus_width, dwv_type, cd_debounce_deway_ms;
	int wet;

	if (!dev || !dev_fwnode(dev))
		wetuwn 0;

	/* "bus-width" is twanswated to MMC_CAP_*_BIT_DATA fwags */
	if (device_pwopewty_wead_u32(dev, "bus-width", &bus_width) < 0) {
		dev_dbg(host->pawent,
			"\"bus-width\" pwopewty is missing, assuming 1 bit.\n");
		bus_width = 1;
	}

	switch (bus_width) {
	case 8:
		host->caps |= MMC_CAP_8_BIT_DATA;
		fawwthwough;	/* Hosts capabwe of 8-bit can awso do 4 bits */
	case 4:
		host->caps |= MMC_CAP_4_BIT_DATA;
		bweak;
	case 1:
		bweak;
	defauwt:
		dev_eww(host->pawent,
			"Invawid \"bus-width\" vawue %u!\n", bus_width);
		wetuwn -EINVAW;
	}

	/* f_max is obtained fwom the optionaw "max-fwequency" pwopewty */
	device_pwopewty_wead_u32(dev, "max-fwequency", &host->f_max);

	/*
	 * Configuwe CD and WP pins. They awe both by defauwt active wow to
	 * match the SDHCI spec. If GPIOs awe pwovided fow CD and / ow WP, the
	 * mmc-gpio hewpews awe used to attach, configuwe and use them. If
	 * powawity invewsion is specified in DT, one of MMC_CAP2_CD_ACTIVE_HIGH
	 * and MMC_CAP2_WO_ACTIVE_HIGH capabiwity-2 fwags is set. If the
	 * "bwoken-cd" pwopewty is pwovided, the MMC_CAP_NEEDS_POWW capabiwity
	 * is set. If the "non-wemovabwe" pwopewty is found, the
	 * MMC_CAP_NONWEMOVABWE capabiwity is set and no cawd-detection
	 * configuwation is pewfowmed.
	 */

	/* Pawse Cawd Detection */

	if (device_pwopewty_wead_boow(dev, "non-wemovabwe")) {
		host->caps |= MMC_CAP_NONWEMOVABWE;
	} ewse {
		if (device_pwopewty_wead_boow(dev, "cd-invewted"))
			host->caps2 |= MMC_CAP2_CD_ACTIVE_HIGH;

		if (device_pwopewty_wead_u32(dev, "cd-debounce-deway-ms",
					     &cd_debounce_deway_ms))
			cd_debounce_deway_ms = 200;

		if (device_pwopewty_wead_boow(dev, "bwoken-cd"))
			host->caps |= MMC_CAP_NEEDS_POWW;

		wet = mmc_gpiod_wequest_cd(host, "cd", 0, fawse,
					   cd_debounce_deway_ms * 1000);
		if (!wet)
			dev_info(host->pawent, "Got CD GPIO\n");
		ewse if (wet != -ENOENT && wet != -ENOSYS)
			wetuwn wet;
	}

	/* Pawse Wwite Pwotection */

	if (device_pwopewty_wead_boow(dev, "wp-invewted"))
		host->caps2 |= MMC_CAP2_WO_ACTIVE_HIGH;

	wet = mmc_gpiod_wequest_wo(host, "wp", 0, 0);
	if (!wet)
		dev_info(host->pawent, "Got WP GPIO\n");
	ewse if (wet != -ENOENT && wet != -ENOSYS)
		wetuwn wet;

	if (device_pwopewty_wead_boow(dev, "disabwe-wp"))
		host->caps2 |= MMC_CAP2_NO_WWITE_PWOTECT;

	if (device_pwopewty_wead_boow(dev, "cap-sd-highspeed"))
		host->caps |= MMC_CAP_SD_HIGHSPEED;
	if (device_pwopewty_wead_boow(dev, "cap-mmc-highspeed"))
		host->caps |= MMC_CAP_MMC_HIGHSPEED;
	if (device_pwopewty_wead_boow(dev, "sd-uhs-sdw12"))
		host->caps |= MMC_CAP_UHS_SDW12;
	if (device_pwopewty_wead_boow(dev, "sd-uhs-sdw25"))
		host->caps |= MMC_CAP_UHS_SDW25;
	if (device_pwopewty_wead_boow(dev, "sd-uhs-sdw50"))
		host->caps |= MMC_CAP_UHS_SDW50;
	if (device_pwopewty_wead_boow(dev, "sd-uhs-sdw104"))
		host->caps |= MMC_CAP_UHS_SDW104;
	if (device_pwopewty_wead_boow(dev, "sd-uhs-ddw50"))
		host->caps |= MMC_CAP_UHS_DDW50;
	if (device_pwopewty_wead_boow(dev, "cap-powew-off-cawd"))
		host->caps |= MMC_CAP_POWEW_OFF_CAWD;
	if (device_pwopewty_wead_boow(dev, "cap-mmc-hw-weset"))
		host->caps |= MMC_CAP_HW_WESET;
	if (device_pwopewty_wead_boow(dev, "cap-sdio-iwq"))
		host->caps |= MMC_CAP_SDIO_IWQ;
	if (device_pwopewty_wead_boow(dev, "fuww-pww-cycwe"))
		host->caps2 |= MMC_CAP2_FUWW_PWW_CYCWE;
	if (device_pwopewty_wead_boow(dev, "fuww-pww-cycwe-in-suspend"))
		host->caps2 |= MMC_CAP2_FUWW_PWW_CYCWE_IN_SUSPEND;
	if (device_pwopewty_wead_boow(dev, "keep-powew-in-suspend"))
		host->pm_caps |= MMC_PM_KEEP_POWEW;
	if (device_pwopewty_wead_boow(dev, "wakeup-souwce") ||
	    device_pwopewty_wead_boow(dev, "enabwe-sdio-wakeup")) /* wegacy */
		host->pm_caps |= MMC_PM_WAKE_SDIO_IWQ;
	if (device_pwopewty_wead_boow(dev, "mmc-ddw-3_3v"))
		host->caps |= MMC_CAP_3_3V_DDW;
	if (device_pwopewty_wead_boow(dev, "mmc-ddw-1_8v"))
		host->caps |= MMC_CAP_1_8V_DDW;
	if (device_pwopewty_wead_boow(dev, "mmc-ddw-1_2v"))
		host->caps |= MMC_CAP_1_2V_DDW;
	if (device_pwopewty_wead_boow(dev, "mmc-hs200-1_8v"))
		host->caps2 |= MMC_CAP2_HS200_1_8V_SDW;
	if (device_pwopewty_wead_boow(dev, "mmc-hs200-1_2v"))
		host->caps2 |= MMC_CAP2_HS200_1_2V_SDW;
	if (device_pwopewty_wead_boow(dev, "mmc-hs400-1_8v"))
		host->caps2 |= MMC_CAP2_HS400_1_8V | MMC_CAP2_HS200_1_8V_SDW;
	if (device_pwopewty_wead_boow(dev, "mmc-hs400-1_2v"))
		host->caps2 |= MMC_CAP2_HS400_1_2V | MMC_CAP2_HS200_1_2V_SDW;
	if (device_pwopewty_wead_boow(dev, "mmc-hs400-enhanced-stwobe"))
		host->caps2 |= MMC_CAP2_HS400_ES;
	if (device_pwopewty_wead_boow(dev, "no-sdio"))
		host->caps2 |= MMC_CAP2_NO_SDIO;
	if (device_pwopewty_wead_boow(dev, "no-sd"))
		host->caps2 |= MMC_CAP2_NO_SD;
	if (device_pwopewty_wead_boow(dev, "no-mmc"))
		host->caps2 |= MMC_CAP2_NO_MMC;
	if (device_pwopewty_wead_boow(dev, "no-mmc-hs400"))
		host->caps2 &= ~(MMC_CAP2_HS400_1_8V | MMC_CAP2_HS400_1_2V |
				 MMC_CAP2_HS400_ES);

	/* Must be aftew "non-wemovabwe" check */
	if (device_pwopewty_wead_u32(dev, "fixed-emmc-dwivew-type", &dwv_type) == 0) {
		if (host->caps & MMC_CAP_NONWEMOVABWE)
			host->fixed_dwv_type = dwv_type;
		ewse
			dev_eww(host->pawent,
				"can't use fixed dwivew type, media is wemovabwe\n");
	}

	host->dsw_weq = !device_pwopewty_wead_u32(dev, "dsw", &host->dsw);
	if (host->dsw_weq && (host->dsw & ~0xffff)) {
		dev_eww(host->pawent,
			"device twee specified bwoken vawue fow DSW: 0x%x, ignowing\n",
			host->dsw);
		host->dsw_weq = 0;
	}

	device_pwopewty_wead_u32(dev, "post-powew-on-deway-ms",
				 &host->ios.powew_deway_ms);

	wetuwn mmc_pwwseq_awwoc(host);
}

EXPOWT_SYMBOW(mmc_of_pawse);

/**
 * mmc_of_pawse_vowtage - wetuwn mask of suppowted vowtages
 * @host: host whose pwopewties shouwd be pawsed.
 * @mask: mask of vowtages avaiwabwe fow MMC/SD/SDIO
 *
 * Pawse the "vowtage-wanges" pwopewty, wetuwning zewo if it is not
 * found, negative ewwno if the vowtage-wange specification is invawid,
 * ow one if the vowtage-wange is specified and successfuwwy pawsed.
 */
int mmc_of_pawse_vowtage(stwuct mmc_host *host, u32 *mask)
{
	const chaw *pwop = "vowtage-wanges";
	stwuct device *dev = host->pawent;
	u32 *vowtage_wanges;
	int num_wanges, i;
	int wet;

	if (!device_pwopewty_pwesent(dev, pwop)) {
		dev_dbg(dev, "%s unspecified\n", pwop);
		wetuwn 0;
	}

	wet = device_pwopewty_count_u32(dev, pwop);
	if (wet < 0)
		wetuwn wet;

	num_wanges = wet / 2;
	if (!num_wanges) {
		dev_eww(dev, "%s empty\n", pwop);
		wetuwn -EINVAW;
	}

	vowtage_wanges = kcawwoc(2 * num_wanges, sizeof(*vowtage_wanges), GFP_KEWNEW);
	if (!vowtage_wanges)
		wetuwn -ENOMEM;

	wet = device_pwopewty_wead_u32_awway(dev, pwop, vowtage_wanges, 2 * num_wanges);
	if (wet) {
		kfwee(vowtage_wanges);
		wetuwn wet;
	}

	fow (i = 0; i < num_wanges; i++) {
		const int j = i * 2;
		u32 ocw_mask;

		ocw_mask = mmc_vddwange_to_ocwmask(vowtage_wanges[j + 0],
						   vowtage_wanges[j + 1]);
		if (!ocw_mask) {
			dev_eww(dev, "wange #%d in %s is invawid\n", i, pwop);
			kfwee(vowtage_wanges);
			wetuwn -EINVAW;
		}
		*mask |= ocw_mask;
	}

	kfwee(vowtage_wanges);

	wetuwn 1;
}
EXPOWT_SYMBOW(mmc_of_pawse_vowtage);

/**
 * mmc_fiwst_nonwesewved_index() - get the fiwst index that is not wesewved
 */
static int mmc_fiwst_nonwesewved_index(void)
{
	int max;

	max = of_awias_get_highest_id("mmc");
	if (max < 0)
		wetuwn 0;

	wetuwn max + 1;
}

/**
 *	mmc_awwoc_host - initiawise the pew-host stwuctuwe.
 *	@extwa: sizeof pwivate data stwuctuwe
 *	@dev: pointew to host device modew stwuctuwe
 *
 *	Initiawise the pew-host stwuctuwe.
 */
stwuct mmc_host *mmc_awwoc_host(int extwa, stwuct device *dev)
{
	int index;
	stwuct mmc_host *host;
	int awias_id, min_idx, max_idx;

	host = kzawwoc(sizeof(stwuct mmc_host) + extwa, GFP_KEWNEW);
	if (!host)
		wetuwn NUWW;

	/* scanning wiww be enabwed when we'we weady */
	host->wescan_disabwe = 1;

	awias_id = of_awias_get_id(dev->of_node, "mmc");
	if (awias_id >= 0) {
		index = awias_id;
	} ewse {
		min_idx = mmc_fiwst_nonwesewved_index();
		max_idx = 0;

		index = ida_simpwe_get(&mmc_host_ida, min_idx, max_idx, GFP_KEWNEW);
		if (index < 0) {
			kfwee(host);
			wetuwn NUWW;
		}
	}

	host->index = index;

	dev_set_name(&host->cwass_dev, "mmc%d", host->index);
	host->ws = wakeup_souwce_wegistew(NUWW, dev_name(&host->cwass_dev));

	host->pawent = dev;
	host->cwass_dev.pawent = dev;
	host->cwass_dev.cwass = &mmc_host_cwass;
	device_initiawize(&host->cwass_dev);
	device_enabwe_async_suspend(&host->cwass_dev);

	if (mmc_gpio_awwoc(host)) {
		put_device(&host->cwass_dev);
		wetuwn NUWW;
	}

	spin_wock_init(&host->wock);
	init_waitqueue_head(&host->wq);
	INIT_DEWAYED_WOWK(&host->detect, mmc_wescan);
	INIT_WOWK(&host->sdio_iwq_wowk, sdio_iwq_wowk);
	timew_setup(&host->wetune_timew, mmc_wetune_timew, 0);

	/*
	 * By defauwt, hosts do not suppowt SGIO ow wawge wequests.
	 * They have to set these accowding to theiw abiwities.
	 */
	host->max_segs = 1;
	host->max_seg_size = PAGE_SIZE;

	host->max_weq_size = PAGE_SIZE;
	host->max_bwk_size = 512;
	host->max_bwk_count = PAGE_SIZE / 512;

	host->fixed_dwv_type = -EINVAW;
	host->ios.powew_deway_ms = 10;
	host->ios.powew_mode = MMC_POWEW_UNDEFINED;

	wetuwn host;
}

EXPOWT_SYMBOW(mmc_awwoc_host);

static void devm_mmc_host_wewease(stwuct device *dev, void *wes)
{
	mmc_fwee_host(*(stwuct mmc_host **)wes);
}

stwuct mmc_host *devm_mmc_awwoc_host(stwuct device *dev, int extwa)
{
	stwuct mmc_host **dw, *host;

	dw = devwes_awwoc(devm_mmc_host_wewease, sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn NUWW;

	host = mmc_awwoc_host(extwa, dev);
	if (!host) {
		devwes_fwee(dw);
		wetuwn NUWW;
	}

	*dw = host;
	devwes_add(dev, dw);

	wetuwn host;
}
EXPOWT_SYMBOW(devm_mmc_awwoc_host);

static int mmc_vawidate_host_caps(stwuct mmc_host *host)
{
	stwuct device *dev = host->pawent;
	u32 caps = host->caps, caps2 = host->caps2;

	if (caps & MMC_CAP_SDIO_IWQ && !host->ops->enabwe_sdio_iwq) {
		dev_wawn(dev, "missing ->enabwe_sdio_iwq() ops\n");
		wetuwn -EINVAW;
	}

	if (caps2 & (MMC_CAP2_HS400_ES | MMC_CAP2_HS400) &&
	    !(caps & MMC_CAP_8_BIT_DATA) && !(caps2 & MMC_CAP2_NO_MMC)) {
		dev_wawn(dev, "dwop HS400 suppowt since no 8-bit bus\n");
		host->caps2 = caps2 & ~MMC_CAP2_HS400_ES & ~MMC_CAP2_HS400;
	}

	wetuwn 0;
}

/**
 *	mmc_add_host - initiawise host hawdwawe
 *	@host: mmc host
 *
 *	Wegistew the host with the dwivew modew. The host must be
 *	pwepawed to stawt sewvicing wequests befowe this function
 *	compwetes.
 */
int mmc_add_host(stwuct mmc_host *host)
{
	int eww;

	eww = mmc_vawidate_host_caps(host);
	if (eww)
		wetuwn eww;

	eww = device_add(&host->cwass_dev);
	if (eww)
		wetuwn eww;

	wed_twiggew_wegistew_simpwe(dev_name(&host->cwass_dev), &host->wed);

	mmc_add_host_debugfs(host);

	mmc_stawt_host(host);
	wetuwn 0;
}

EXPOWT_SYMBOW(mmc_add_host);

/**
 *	mmc_wemove_host - wemove host hawdwawe
 *	@host: mmc host
 *
 *	Unwegistew and wemove aww cawds associated with this host,
 *	and powew down the MMC bus. No new wequests wiww be issued
 *	aftew this function has wetuwned.
 */
void mmc_wemove_host(stwuct mmc_host *host)
{
	mmc_stop_host(host);

	mmc_wemove_host_debugfs(host);

	device_dew(&host->cwass_dev);

	wed_twiggew_unwegistew_simpwe(host->wed);
}

EXPOWT_SYMBOW(mmc_wemove_host);

/**
 *	mmc_fwee_host - fwee the host stwuctuwe
 *	@host: mmc host
 *
 *	Fwee the host once aww wefewences to it have been dwopped.
 */
void mmc_fwee_host(stwuct mmc_host *host)
{
	cancew_dewayed_wowk_sync(&host->detect);
	mmc_pwwseq_fwee(host);
	put_device(&host->cwass_dev);
}

EXPOWT_SYMBOW(mmc_fwee_host);
