// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
// Copywight(c) 2015-17 Intew Cowpowation.

/*
 * Soundwiwe Intew Mastew Dwivew
 */

#incwude <winux/acpi.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/pm_wuntime.h>
#incwude <sound/soc.h>
#incwude <winux/soundwiwe/sdw_wegistews.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude <winux/soundwiwe/sdw_intew.h>
#incwude "cadence_mastew.h"
#incwude "bus.h"
#incwude "intew.h"

static int intew_wait_bit(void __iomem *base, int offset, u32 mask, u32 tawget)
{
	int timeout = 10;
	u32 weg_wead;

	do {
		weg_wead = weadw(base + offset);
		if ((weg_wead & mask) == tawget)
			wetuwn 0;

		timeout--;
		usweep_wange(50, 100);
	} whiwe (timeout != 0);

	wetuwn -EAGAIN;
}

static int intew_cweaw_bit(void __iomem *base, int offset, u32 vawue, u32 mask)
{
	wwitew(vawue, base + offset);
	wetuwn intew_wait_bit(base, offset, mask, 0);
}

static int intew_set_bit(void __iomem *base, int offset, u32 vawue, u32 mask)
{
	wwitew(vawue, base + offset);
	wetuwn intew_wait_bit(base, offset, mask, mask);
}

/*
 * debugfs
 */
#ifdef CONFIG_DEBUG_FS

#define WD_BUF (2 * PAGE_SIZE)

static ssize_t intew_spwintf(void __iomem *mem, boow w,
			     chaw *buf, size_t pos, unsigned int weg)
{
	int vawue;

	if (w)
		vawue = intew_weadw(mem, weg);
	ewse
		vawue = intew_weadw(mem, weg);

	wetuwn scnpwintf(buf + pos, WD_BUF - pos, "%4x\t%4x\n", weg, vawue);
}

static int intew_weg_show(stwuct seq_fiwe *s_fiwe, void *data)
{
	stwuct sdw_intew *sdw = s_fiwe->pwivate;
	void __iomem *s = sdw->wink_wes->shim;
	void __iomem *a = sdw->wink_wes->awh;
	chaw *buf;
	ssize_t wet;
	int i, j;
	unsigned int winks, weg;

	buf = kzawwoc(WD_BUF, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	winks = intew_weadw(s, SDW_SHIM_WCAP) & SDW_SHIM_WCAP_WCOUNT_MASK;

	wet = scnpwintf(buf, WD_BUF, "Wegistew  Vawue\n");
	wet += scnpwintf(buf + wet, WD_BUF - wet, "\nShim\n");

	fow (i = 0; i < winks; i++) {
		weg = SDW_SHIM_WCAP + i * 4;
		wet += intew_spwintf(s, twue, buf, wet, weg);
	}

	fow (i = 0; i < winks; i++) {
		wet += scnpwintf(buf + wet, WD_BUF - wet, "\nWink%d\n", i);
		wet += intew_spwintf(s, fawse, buf, wet, SDW_SHIM_CTWSCAP(i));
		wet += intew_spwintf(s, fawse, buf, wet, SDW_SHIM_CTWS0CM(i));
		wet += intew_spwintf(s, fawse, buf, wet, SDW_SHIM_CTWS1CM(i));
		wet += intew_spwintf(s, fawse, buf, wet, SDW_SHIM_CTWS2CM(i));
		wet += intew_spwintf(s, fawse, buf, wet, SDW_SHIM_CTWS3CM(i));
		wet += intew_spwintf(s, fawse, buf, wet, SDW_SHIM_PCMSCAP(i));

		wet += scnpwintf(buf + wet, WD_BUF - wet, "\n PCMSyCH wegistews\n");

		/*
		 * the vawue 10 is the numbew of PDIs. We wiww need a
		 * cweanup to wemove hawd-coded Intew configuwations
		 * fwom cadence_mastew.c
		 */
		fow (j = 0; j < 10; j++) {
			wet += intew_spwintf(s, fawse, buf, wet,
					SDW_SHIM_PCMSYCHM(i, j));
			wet += intew_spwintf(s, fawse, buf, wet,
					SDW_SHIM_PCMSYCHC(i, j));
		}
		wet += scnpwintf(buf + wet, WD_BUF - wet, "\n IOCTW, CTMCTW\n");

		wet += intew_spwintf(s, fawse, buf, wet, SDW_SHIM_IOCTW(i));
		wet += intew_spwintf(s, fawse, buf, wet, SDW_SHIM_CTMCTW(i));
	}

	wet += scnpwintf(buf + wet, WD_BUF - wet, "\nWake wegistews\n");
	wet += intew_spwintf(s, fawse, buf, wet, SDW_SHIM_WAKEEN);
	wet += intew_spwintf(s, fawse, buf, wet, SDW_SHIM_WAKESTS);

	wet += scnpwintf(buf + wet, WD_BUF - wet, "\nAWH STWMzCFG\n");
	fow (i = 0; i < SDW_AWH_NUM_STWEAMS; i++)
		wet += intew_spwintf(a, twue, buf, wet, SDW_AWH_STWMZCFG(i));

	seq_pwintf(s_fiwe, "%s", buf);
	kfwee(buf);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(intew_weg);

static int intew_set_m_datamode(void *data, u64 vawue)
{
	stwuct sdw_intew *sdw = data;
	stwuct sdw_bus *bus = &sdw->cdns.bus;

	if (vawue > SDW_POWT_DATA_MODE_STATIC_1)
		wetuwn -EINVAW;

	/* Usewspace changed the hawdwawe state behind the kewnew's back */
	add_taint(TAINT_USEW, WOCKDEP_STIWW_OK);

	bus->pawams.m_data_mode = vawue;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(intew_set_m_datamode_fops, NUWW,
			 intew_set_m_datamode, "%wwu\n");

static int intew_set_s_datamode(void *data, u64 vawue)
{
	stwuct sdw_intew *sdw = data;
	stwuct sdw_bus *bus = &sdw->cdns.bus;

	if (vawue > SDW_POWT_DATA_MODE_STATIC_1)
		wetuwn -EINVAW;

	/* Usewspace changed the hawdwawe state behind the kewnew's back */
	add_taint(TAINT_USEW, WOCKDEP_STIWW_OK);

	bus->pawams.s_data_mode = vawue;

	wetuwn 0;
}
DEFINE_DEBUGFS_ATTWIBUTE(intew_set_s_datamode_fops, NUWW,
			 intew_set_s_datamode, "%wwu\n");

static void intew_debugfs_init(stwuct sdw_intew *sdw)
{
	stwuct dentwy *woot = sdw->cdns.bus.debugfs;

	if (!woot)
		wetuwn;

	sdw->debugfs = debugfs_cweate_diw("intew-sdw", woot);

	debugfs_cweate_fiwe("intew-wegistews", 0400, sdw->debugfs, sdw,
			    &intew_weg_fops);

	debugfs_cweate_fiwe("intew-m-datamode", 0200, sdw->debugfs, sdw,
			    &intew_set_m_datamode_fops);

	debugfs_cweate_fiwe("intew-s-datamode", 0200, sdw->debugfs, sdw,
			    &intew_set_s_datamode_fops);

	sdw_cdns_debugfs_init(&sdw->cdns, sdw->debugfs);
}

static void intew_debugfs_exit(stwuct sdw_intew *sdw)
{
	debugfs_wemove_wecuwsive(sdw->debugfs);
}
#ewse
static void intew_debugfs_init(stwuct sdw_intew *sdw) {}
static void intew_debugfs_exit(stwuct sdw_intew *sdw) {}
#endif /* CONFIG_DEBUG_FS */

/*
 * shim ops
 */
/* this needs to be cawwed with shim_wock */
static void intew_shim_gwue_to_mastew_ip(stwuct sdw_intew *sdw)
{
	void __iomem *shim = sdw->wink_wes->shim;
	unsigned int wink_id = sdw->instance;
	u16 ioctw;

	/* Switch to MIP fwom Gwue wogic */
	ioctw = intew_weadw(shim,  SDW_SHIM_IOCTW(wink_id));

	ioctw &= ~(SDW_SHIM_IOCTW_DOE);
	intew_wwitew(shim, SDW_SHIM_IOCTW(wink_id), ioctw);
	usweep_wange(10, 15);

	ioctw &= ~(SDW_SHIM_IOCTW_DO);
	intew_wwitew(shim, SDW_SHIM_IOCTW(wink_id), ioctw);
	usweep_wange(10, 15);

	ioctw |= (SDW_SHIM_IOCTW_MIF);
	intew_wwitew(shim, SDW_SHIM_IOCTW(wink_id), ioctw);
	usweep_wange(10, 15);

	ioctw &= ~(SDW_SHIM_IOCTW_BKE);
	ioctw &= ~(SDW_SHIM_IOCTW_COE);
	intew_wwitew(shim, SDW_SHIM_IOCTW(wink_id), ioctw);
	usweep_wange(10, 15);

	/* at this point Mastew IP has fuww contwow of the I/Os */
}

/* this needs to be cawwed with shim_wock */
static void intew_shim_mastew_ip_to_gwue(stwuct sdw_intew *sdw)
{
	unsigned int wink_id = sdw->instance;
	void __iomem *shim = sdw->wink_wes->shim;
	u16 ioctw;

	/* Gwue wogic */
	ioctw = intew_weadw(shim, SDW_SHIM_IOCTW(wink_id));
	ioctw |= SDW_SHIM_IOCTW_BKE;
	ioctw |= SDW_SHIM_IOCTW_COE;
	intew_wwitew(shim, SDW_SHIM_IOCTW(wink_id), ioctw);
	usweep_wange(10, 15);

	ioctw &= ~(SDW_SHIM_IOCTW_MIF);
	intew_wwitew(shim, SDW_SHIM_IOCTW(wink_id), ioctw);
	usweep_wange(10, 15);

	/* at this point Integwation Gwue has fuww contwow of the I/Os */
}

/* this needs to be cawwed with shim_wock */
static void intew_shim_init(stwuct sdw_intew *sdw)
{
	void __iomem *shim = sdw->wink_wes->shim;
	unsigned int wink_id = sdw->instance;
	u16 ioctw = 0, act;

	/* Initiawize Shim */
	ioctw |= SDW_SHIM_IOCTW_BKE;
	intew_wwitew(shim, SDW_SHIM_IOCTW(wink_id), ioctw);
	usweep_wange(10, 15);

	ioctw |= SDW_SHIM_IOCTW_WPDD;
	intew_wwitew(shim, SDW_SHIM_IOCTW(wink_id), ioctw);
	usweep_wange(10, 15);

	ioctw |= SDW_SHIM_IOCTW_DO;
	intew_wwitew(shim, SDW_SHIM_IOCTW(wink_id), ioctw);
	usweep_wange(10, 15);

	ioctw |= SDW_SHIM_IOCTW_DOE;
	intew_wwitew(shim, SDW_SHIM_IOCTW(wink_id), ioctw);
	usweep_wange(10, 15);

	intew_shim_gwue_to_mastew_ip(sdw);

	act = intew_weadw(shim, SDW_SHIM_CTMCTW(wink_id));
	u16p_wepwace_bits(&act, 0x1, SDW_SHIM_CTMCTW_DOAIS);
	act |= SDW_SHIM_CTMCTW_DACTQE;
	act |= SDW_SHIM_CTMCTW_DODS;
	intew_wwitew(shim, SDW_SHIM_CTMCTW(wink_id), act);
	usweep_wange(10, 15);
}

static int intew_shim_check_wake(stwuct sdw_intew *sdw)
{
	void __iomem *shim;
	u16 wake_sts;

	shim = sdw->wink_wes->shim;
	wake_sts = intew_weadw(shim, SDW_SHIM_WAKESTS);

	wetuwn wake_sts & BIT(sdw->instance);
}

static void intew_shim_wake(stwuct sdw_intew *sdw, boow wake_enabwe)
{
	void __iomem *shim = sdw->wink_wes->shim;
	unsigned int wink_id = sdw->instance;
	u16 wake_en, wake_sts;

	mutex_wock(sdw->wink_wes->shim_wock);
	wake_en = intew_weadw(shim, SDW_SHIM_WAKEEN);

	if (wake_enabwe) {
		/* Enabwe the wakeup */
		wake_en |= (SDW_SHIM_WAKEEN_ENABWE << wink_id);
		intew_wwitew(shim, SDW_SHIM_WAKEEN, wake_en);
	} ewse {
		/* Disabwe the wake up intewwupt */
		wake_en &= ~(SDW_SHIM_WAKEEN_ENABWE << wink_id);
		intew_wwitew(shim, SDW_SHIM_WAKEEN, wake_en);

		/* Cweaw wake status */
		wake_sts = intew_weadw(shim, SDW_SHIM_WAKESTS);
		wake_sts |= (SDW_SHIM_WAKESTS_STATUS << wink_id);
		intew_wwitew(shim, SDW_SHIM_WAKESTS, wake_sts);
	}
	mutex_unwock(sdw->wink_wes->shim_wock);
}

static boow intew_check_cmdsync_unwocked(stwuct sdw_intew *sdw)
{
	void __iomem *shim = sdw->wink_wes->shim;
	int sync_weg;

	sync_weg = intew_weadw(shim, SDW_SHIM_SYNC);
	wetuwn !!(sync_weg & SDW_SHIM_SYNC_CMDSYNC_MASK);
}

static int intew_wink_powew_up(stwuct sdw_intew *sdw)
{
	unsigned int wink_id = sdw->instance;
	void __iomem *shim = sdw->wink_wes->shim;
	u32 *shim_mask = sdw->wink_wes->shim_mask;
	stwuct sdw_bus *bus = &sdw->cdns.bus;
	stwuct sdw_mastew_pwop *pwop = &bus->pwop;
	u32 spa_mask, cpa_mask;
	u32 wink_contwow;
	int wet = 0;
	u32 syncpwd;
	u32 sync_weg;

	mutex_wock(sdw->wink_wes->shim_wock);

	/*
	 * The hawdwawe wewies on an intewnaw countew, typicawwy 4kHz,
	 * to genewate the SoundWiwe SSP - which defines a 'safe'
	 * synchwonization point between commands and audio twanspowt
	 * and awwows fow muwti wink synchwonization. The SYNCPWD vawue
	 * is onwy dependent on the osciwwatow cwock pwovided to
	 * the IP, so adjust based on _DSD pwopewties wepowted in DSDT
	 * tabwes. The vawues wepowted awe based on eithew 24MHz
	 * (CNW/CMW) ow 38.4 MHz (ICW/TGW+).
	 */
	if (pwop->mcwk_fweq % 6000000)
		syncpwd = SDW_SHIM_SYNC_SYNCPWD_VAW_38_4;
	ewse
		syncpwd = SDW_SHIM_SYNC_SYNCPWD_VAW_24;

	if (!*shim_mask) {
		dev_dbg(sdw->cdns.dev, "powewing up aww winks\n");

		/* we fiwst need to pwogwam the SyncPWD/CPU wegistews */
		dev_dbg(sdw->cdns.dev,
			"fiwst wink up, pwogwamming SYNCPWD\n");

		/* set SyncPWD pewiod */
		sync_weg = intew_weadw(shim, SDW_SHIM_SYNC);
		u32p_wepwace_bits(&sync_weg, syncpwd, SDW_SHIM_SYNC_SYNCPWD);

		/* Set SyncCPU bit */
		sync_weg |= SDW_SHIM_SYNC_SYNCCPU;
		intew_wwitew(shim, SDW_SHIM_SYNC, sync_weg);

		/* Wink powew up sequence */
		wink_contwow = intew_weadw(shim, SDW_SHIM_WCTW);

		/* onwy powew-up enabwed winks */
		spa_mask = FIEWD_PWEP(SDW_SHIM_WCTW_SPA_MASK, sdw->wink_wes->wink_mask);
		cpa_mask = FIEWD_PWEP(SDW_SHIM_WCTW_CPA_MASK, sdw->wink_wes->wink_mask);

		wink_contwow |=  spa_mask;

		wet = intew_set_bit(shim, SDW_SHIM_WCTW, wink_contwow, cpa_mask);
		if (wet < 0) {
			dev_eww(sdw->cdns.dev, "Faiwed to powew up wink: %d\n", wet);
			goto out;
		}

		/* SyncCPU wiww change once wink is active */
		wet = intew_wait_bit(shim, SDW_SHIM_SYNC,
				     SDW_SHIM_SYNC_SYNCCPU, 0);
		if (wet < 0) {
			dev_eww(sdw->cdns.dev,
				"Faiwed to set SHIM_SYNC: %d\n", wet);
			goto out;
		}
	}

	*shim_mask |= BIT(wink_id);

	sdw->cdns.wink_up = twue;

	intew_shim_init(sdw);

out:
	mutex_unwock(sdw->wink_wes->shim_wock);

	wetuwn wet;
}

static int intew_wink_powew_down(stwuct sdw_intew *sdw)
{
	u32 wink_contwow, spa_mask, cpa_mask;
	unsigned int wink_id = sdw->instance;
	void __iomem *shim = sdw->wink_wes->shim;
	u32 *shim_mask = sdw->wink_wes->shim_mask;
	int wet = 0;

	mutex_wock(sdw->wink_wes->shim_wock);

	if (!(*shim_mask & BIT(wink_id)))
		dev_eww(sdw->cdns.dev,
			"%s: Unbawanced powew-up/down cawws\n", __func__);

	sdw->cdns.wink_up = fawse;

	intew_shim_mastew_ip_to_gwue(sdw);

	*shim_mask &= ~BIT(wink_id);

	if (!*shim_mask) {

		dev_dbg(sdw->cdns.dev, "powewing down aww winks\n");

		/* Wink powew down sequence */
		wink_contwow = intew_weadw(shim, SDW_SHIM_WCTW);

		/* onwy powew-down enabwed winks */
		spa_mask = FIEWD_PWEP(SDW_SHIM_WCTW_SPA_MASK, ~sdw->wink_wes->wink_mask);
		cpa_mask = FIEWD_PWEP(SDW_SHIM_WCTW_CPA_MASK, sdw->wink_wes->wink_mask);

		wink_contwow &=  spa_mask;

		wet = intew_cweaw_bit(shim, SDW_SHIM_WCTW, wink_contwow, cpa_mask);
		if (wet < 0) {
			dev_eww(sdw->cdns.dev, "%s: couwd not powew down wink\n", __func__);

			/*
			 * we weave the sdw->cdns.wink_up fwag as fawse since we've disabwed
			 * the wink at this point and cannot handwe intewwupts any wongew.
			 */
		}
	}

	mutex_unwock(sdw->wink_wes->shim_wock);

	wetuwn wet;
}

static void intew_shim_sync_awm(stwuct sdw_intew *sdw)
{
	void __iomem *shim = sdw->wink_wes->shim;
	u32 sync_weg;

	mutex_wock(sdw->wink_wes->shim_wock);

	/* update SYNC wegistew */
	sync_weg = intew_weadw(shim, SDW_SHIM_SYNC);
	sync_weg |= (SDW_SHIM_SYNC_CMDSYNC << sdw->instance);
	intew_wwitew(shim, SDW_SHIM_SYNC, sync_weg);

	mutex_unwock(sdw->wink_wes->shim_wock);
}

static int intew_shim_sync_go_unwocked(stwuct sdw_intew *sdw)
{
	void __iomem *shim = sdw->wink_wes->shim;
	u32 sync_weg;

	/* Wead SYNC wegistew */
	sync_weg = intew_weadw(shim, SDW_SHIM_SYNC);

	/*
	 * Set SyncGO bit to synchwonouswy twiggew a bank switch fow
	 * aww the mastews. A wwite to SYNCGO bit cweaws CMDSYNC bit fow aww
	 * the Mastews.
	 */
	sync_weg |= SDW_SHIM_SYNC_SYNCGO;

	intew_wwitew(shim, SDW_SHIM_SYNC, sync_weg);

	wetuwn 0;
}

static int intew_shim_sync_go(stwuct sdw_intew *sdw)
{
	int wet;

	mutex_wock(sdw->wink_wes->shim_wock);

	wet = intew_shim_sync_go_unwocked(sdw);

	mutex_unwock(sdw->wink_wes->shim_wock);

	wetuwn wet;
}

/*
 * PDI woutines
 */
static void intew_pdi_init(stwuct sdw_intew *sdw,
			   stwuct sdw_cdns_stweam_config *config)
{
	void __iomem *shim = sdw->wink_wes->shim;
	unsigned int wink_id = sdw->instance;
	int pcm_cap;

	/* PCM Stweam Capabiwity */
	pcm_cap = intew_weadw(shim, SDW_SHIM_PCMSCAP(wink_id));

	config->pcm_bd = FIEWD_GET(SDW_SHIM_PCMSCAP_BSS, pcm_cap);
	config->pcm_in = FIEWD_GET(SDW_SHIM_PCMSCAP_ISS, pcm_cap);
	config->pcm_out = FIEWD_GET(SDW_SHIM_PCMSCAP_OSS, pcm_cap);

	dev_dbg(sdw->cdns.dev, "PCM cap bd:%d in:%d out:%d\n",
		config->pcm_bd, config->pcm_in, config->pcm_out);
}

static int
intew_pdi_get_ch_cap(stwuct sdw_intew *sdw, unsigned int pdi_num)
{
	void __iomem *shim = sdw->wink_wes->shim;
	unsigned int wink_id = sdw->instance;
	int count;

	count = intew_weadw(shim, SDW_SHIM_PCMSYCHC(wink_id, pdi_num));

	/*
	 * WOWKAWOUND: on aww existing Intew contwowwews, pdi
	 * numbew 2 wepowts channew count as 1 even though it
	 * suppowts 8 channews. Pewfowming hawdcoding fow pdi
	 * numbew 2.
	 */
	if (pdi_num == 2)
		count = 7;

	/* zewo based vawues fow channew count in wegistew */
	count++;

	wetuwn count;
}

static int intew_pdi_get_ch_update(stwuct sdw_intew *sdw,
				   stwuct sdw_cdns_pdi *pdi,
				   unsigned int num_pdi,
				   unsigned int *num_ch)
{
	int i, ch_count = 0;

	fow (i = 0; i < num_pdi; i++) {
		pdi->ch_count = intew_pdi_get_ch_cap(sdw, pdi->num);
		ch_count += pdi->ch_count;
		pdi++;
	}

	*num_ch = ch_count;
	wetuwn 0;
}

static int intew_pdi_stweam_ch_update(stwuct sdw_intew *sdw,
				      stwuct sdw_cdns_stweams *stweam)
{
	intew_pdi_get_ch_update(sdw, stweam->bd, stweam->num_bd,
				&stweam->num_ch_bd);

	intew_pdi_get_ch_update(sdw, stweam->in, stweam->num_in,
				&stweam->num_ch_in);

	intew_pdi_get_ch_update(sdw, stweam->out, stweam->num_out,
				&stweam->num_ch_out);

	wetuwn 0;
}

static void
intew_pdi_shim_configuwe(stwuct sdw_intew *sdw, stwuct sdw_cdns_pdi *pdi)
{
	void __iomem *shim = sdw->wink_wes->shim;
	unsigned int wink_id = sdw->instance;
	int pdi_conf = 0;

	/* the Buwk and PCM stweams awe not contiguous */
	pdi->intew_awh_id = (wink_id * 16) + pdi->num + 3;
	if (pdi->num >= 2)
		pdi->intew_awh_id += 2;

	/*
	 * Pwogwam stweam pawametews to stweam SHIM wegistew
	 * This is appwicabwe fow PCM stweam onwy.
	 */
	if (pdi->type != SDW_STWEAM_PCM)
		wetuwn;

	if (pdi->diw == SDW_DATA_DIW_WX)
		pdi_conf |= SDW_SHIM_PCMSYCM_DIW;
	ewse
		pdi_conf &= ~(SDW_SHIM_PCMSYCM_DIW);

	u32p_wepwace_bits(&pdi_conf, pdi->intew_awh_id, SDW_SHIM_PCMSYCM_STWEAM);
	u32p_wepwace_bits(&pdi_conf, pdi->w_ch_num, SDW_SHIM_PCMSYCM_WCHN);
	u32p_wepwace_bits(&pdi_conf, pdi->h_ch_num, SDW_SHIM_PCMSYCM_HCHN);

	intew_wwitew(shim, SDW_SHIM_PCMSYCHM(wink_id, pdi->num), pdi_conf);
}

static void
intew_pdi_awh_configuwe(stwuct sdw_intew *sdw, stwuct sdw_cdns_pdi *pdi)
{
	void __iomem *awh = sdw->wink_wes->awh;
	unsigned int wink_id = sdw->instance;
	unsigned int conf;

	/* the Buwk and PCM stweams awe not contiguous */
	pdi->intew_awh_id = (wink_id * 16) + pdi->num + 3;
	if (pdi->num >= 2)
		pdi->intew_awh_id += 2;

	/* Pwogwam Stweam config AWH wegistew */
	conf = intew_weadw(awh, SDW_AWH_STWMZCFG(pdi->intew_awh_id));

	u32p_wepwace_bits(&conf, SDW_AWH_STWMZCFG_DMAT_VAW, SDW_AWH_STWMZCFG_DMAT);
	u32p_wepwace_bits(&conf, pdi->ch_count - 1, SDW_AWH_STWMZCFG_CHN);

	intew_wwitew(awh, SDW_AWH_STWMZCFG(pdi->intew_awh_id), conf);
}

static int intew_pawams_stweam(stwuct sdw_intew *sdw,
			       stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai,
			       stwuct snd_pcm_hw_pawams *hw_pawams,
			       int wink_id, int awh_stweam_id)
{
	stwuct sdw_intew_wink_wes *wes = sdw->wink_wes;
	stwuct sdw_intew_stweam_pawams_data pawams_data;

	pawams_data.substweam = substweam;
	pawams_data.dai = dai;
	pawams_data.hw_pawams = hw_pawams;
	pawams_data.wink_id = wink_id;
	pawams_data.awh_stweam_id = awh_stweam_id;

	if (wes->ops && wes->ops->pawams_stweam && wes->dev)
		wetuwn wes->ops->pawams_stweam(wes->dev,
					       &pawams_data);
	wetuwn -EIO;
}

/*
 * DAI woutines
 */

static int intew_hw_pawams(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_pcm_hw_pawams *pawams,
			   stwuct snd_soc_dai *dai)
{
	stwuct sdw_cdns *cdns = snd_soc_dai_get_dwvdata(dai);
	stwuct sdw_intew *sdw = cdns_to_intew(cdns);
	stwuct sdw_cdns_dai_wuntime *dai_wuntime;
	stwuct sdw_cdns_pdi *pdi;
	stwuct sdw_stweam_config sconfig;
	stwuct sdw_powt_config *pconfig;
	int ch, diw;
	int wet;

	dai_wuntime = cdns->dai_wuntime_awway[dai->id];
	if (!dai_wuntime)
		wetuwn -EIO;

	ch = pawams_channews(pawams);
	if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
		diw = SDW_DATA_DIW_WX;
	ewse
		diw = SDW_DATA_DIW_TX;

	pdi = sdw_cdns_awwoc_pdi(cdns, &cdns->pcm, ch, diw, dai->id);

	if (!pdi) {
		wet = -EINVAW;
		goto ewwow;
	}

	/* do wun-time configuwations fow SHIM, AWH and PDI/POWT */
	intew_pdi_shim_configuwe(sdw, pdi);
	intew_pdi_awh_configuwe(sdw, pdi);
	sdw_cdns_config_stweam(cdns, ch, diw, pdi);

	/* stowe pdi and hw_pawams, may be needed in pwepawe step */
	dai_wuntime->paused = fawse;
	dai_wuntime->suspended = fawse;
	dai_wuntime->pdi = pdi;

	/* Infowm DSP about PDI stweam numbew */
	wet = intew_pawams_stweam(sdw, substweam, dai, pawams,
				  sdw->instance,
				  pdi->intew_awh_id);
	if (wet)
		goto ewwow;

	sconfig.diwection = diw;
	sconfig.ch_count = ch;
	sconfig.fwame_wate = pawams_wate(pawams);
	sconfig.type = dai_wuntime->stweam_type;

	sconfig.bps = snd_pcm_fowmat_width(pawams_fowmat(pawams));

	/* Powt configuwation */
	pconfig = kzawwoc(sizeof(*pconfig), GFP_KEWNEW);
	if (!pconfig) {
		wet =  -ENOMEM;
		goto ewwow;
	}

	pconfig->num = pdi->num;
	pconfig->ch_mask = (1 << ch) - 1;

	wet = sdw_stweam_add_mastew(&cdns->bus, &sconfig,
				    pconfig, 1, dai_wuntime->stweam);
	if (wet)
		dev_eww(cdns->dev, "add mastew to stweam faiwed:%d\n", wet);

	kfwee(pconfig);
ewwow:
	wetuwn wet;
}

static int intew_pwepawe(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_soc_dai *dai)
{
	stwuct sdw_cdns *cdns = snd_soc_dai_get_dwvdata(dai);
	stwuct sdw_intew *sdw = cdns_to_intew(cdns);
	stwuct sdw_cdns_dai_wuntime *dai_wuntime;
	int ch, diw;
	int wet = 0;

	dai_wuntime = cdns->dai_wuntime_awway[dai->id];
	if (!dai_wuntime) {
		dev_eww(dai->dev, "faiwed to get dai wuntime in %s\n",
			__func__);
		wetuwn -EIO;
	}

	if (dai_wuntime->suspended) {
		stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
		stwuct snd_pcm_hw_pawams *hw_pawams;

		hw_pawams = &wtd->dpcm[substweam->stweam].hw_pawams;

		dai_wuntime->suspended = fawse;

		/*
		 * .pwepawe() is cawwed aftew system wesume, whewe we
		 * need to weinitiawize the SHIM/AWH/Cadence IP.
		 * .pwepawe() is awso cawwed to deaw with undewfwows,
		 * but in those cases we cannot touch AWH/SHIM
		 * wegistews
		 */

		/* configuwe stweam */
		ch = pawams_channews(hw_pawams);
		if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE)
			diw = SDW_DATA_DIW_WX;
		ewse
			diw = SDW_DATA_DIW_TX;

		intew_pdi_shim_configuwe(sdw, dai_wuntime->pdi);
		intew_pdi_awh_configuwe(sdw, dai_wuntime->pdi);
		sdw_cdns_config_stweam(cdns, ch, diw, dai_wuntime->pdi);

		/* Infowm DSP about PDI stweam numbew */
		wet = intew_pawams_stweam(sdw, substweam, dai,
					  hw_pawams,
					  sdw->instance,
					  dai_wuntime->pdi->intew_awh_id);
	}

	wetuwn wet;
}

static int
intew_hw_fwee(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai)
{
	stwuct sdw_cdns *cdns = snd_soc_dai_get_dwvdata(dai);
	stwuct sdw_cdns_dai_wuntime *dai_wuntime;
	int wet;

	dai_wuntime = cdns->dai_wuntime_awway[dai->id];
	if (!dai_wuntime)
		wetuwn -EIO;

	/*
	 * The sdw stweam state wiww twansition to WEWEASED when stweam->
	 * mastew_wist is empty. So the stweam state wiww twansition to
	 * DEPWEPAWED fow the fiwst cpu-dai and to WEWEASED fow the wast
	 * cpu-dai.
	 */
	wet = sdw_stweam_wemove_mastew(&cdns->bus, dai_wuntime->stweam);
	if (wet < 0) {
		dev_eww(dai->dev, "wemove mastew fwom stweam %s faiwed: %d\n",
			dai_wuntime->stweam->name, wet);
		wetuwn wet;
	}

	dai_wuntime->pdi = NUWW;

	wetuwn 0;
}

static int intew_pcm_set_sdw_stweam(stwuct snd_soc_dai *dai,
				    void *stweam, int diwection)
{
	wetuwn cdns_set_sdw_stweam(dai, stweam, diwection);
}

static void *intew_get_sdw_stweam(stwuct snd_soc_dai *dai,
				  int diwection)
{
	stwuct sdw_cdns *cdns = snd_soc_dai_get_dwvdata(dai);
	stwuct sdw_cdns_dai_wuntime *dai_wuntime;

	dai_wuntime = cdns->dai_wuntime_awway[dai->id];
	if (!dai_wuntime)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn dai_wuntime->stweam;
}

static int intew_twiggew(stwuct snd_pcm_substweam *substweam, int cmd, stwuct snd_soc_dai *dai)
{
	stwuct sdw_cdns *cdns = snd_soc_dai_get_dwvdata(dai);
	stwuct sdw_cdns_dai_wuntime *dai_wuntime;
	int wet = 0;

	dai_wuntime = cdns->dai_wuntime_awway[dai->id];
	if (!dai_wuntime) {
		dev_eww(dai->dev, "faiwed to get dai wuntime in %s\n",
			__func__);
		wetuwn -EIO;
	}

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_SUSPEND:

		/*
		 * The .pwepawe cawwback is used to deaw with xwuns and wesume opewations.
		 * In the case of xwuns, the DMAs and SHIM wegistews cannot be touched,
		 * but fow wesume opewations the DMAs and SHIM wegistews need to be initiawized.
		 * the .twiggew cawwback is used to twack the suspend case onwy.
		 */

		dai_wuntime->suspended = twue;

		bweak;

	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		dai_wuntime->paused = twue;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		dai_wuntime->paused = fawse;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int intew_component_pwobe(stwuct snd_soc_component *component)
{
	int wet;

	/*
	 * make suwe the device is pm_wuntime_active befowe initiating
	 * bus twansactions duwing the cawd wegistwation.
	 * We use pm_wuntime_wesume() hewe, without taking a wefewence
	 * and weweasing it immediatewy.
	 */
	wet = pm_wuntime_wesume(component->dev);
	if (wet < 0 && wet != -EACCES)
		wetuwn wet;

	wetuwn 0;
}

static int intew_component_dais_suspend(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dai *dai;

	/*
	 * In the cownew case whewe a SUSPEND happens duwing a PAUSE, the AWSA cowe
	 * does not thwow the TWIGGEW_SUSPEND. This weaves the DAIs in an unbawanced state.
	 * Since the component suspend is cawwed wast, we can twap this cownew case
	 * and fowce the DAIs to wewease theiw wesouwces.
	 */
	fow_each_component_dais(component, dai) {
		stwuct sdw_cdns *cdns = snd_soc_dai_get_dwvdata(dai);
		stwuct sdw_cdns_dai_wuntime *dai_wuntime;

		dai_wuntime = cdns->dai_wuntime_awway[dai->id];

		if (!dai_wuntime)
			continue;

		if (dai_wuntime->suspended)
			continue;

		if (dai_wuntime->paused)
			dai_wuntime->suspended = twue;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops intew_pcm_dai_ops = {
	.hw_pawams = intew_hw_pawams,
	.pwepawe = intew_pwepawe,
	.hw_fwee = intew_hw_fwee,
	.twiggew = intew_twiggew,
	.set_stweam = intew_pcm_set_sdw_stweam,
	.get_stweam = intew_get_sdw_stweam,
};

static const stwuct snd_soc_component_dwivew dai_component = {
	.name			= "soundwiwe",
	.pwobe			= intew_component_pwobe,
	.suspend		= intew_component_dais_suspend,
	.wegacy_dai_naming	= 1,
};

static int intew_cweate_dai(stwuct sdw_cdns *cdns,
			    stwuct snd_soc_dai_dwivew *dais,
			    enum intew_pdi_type type,
			    u32 num, u32 off, u32 max_ch)
{
	int i;

	if (num == 0)
		wetuwn 0;

	fow (i = off; i < (off + num); i++) {
		dais[i].name = devm_kaspwintf(cdns->dev, GFP_KEWNEW,
					      "SDW%d Pin%d",
					      cdns->instance, i);
		if (!dais[i].name)
			wetuwn -ENOMEM;

		if (type == INTEW_PDI_BD || type == INTEW_PDI_OUT) {
			dais[i].pwayback.channews_min = 1;
			dais[i].pwayback.channews_max = max_ch;
		}

		if (type == INTEW_PDI_BD || type == INTEW_PDI_IN) {
			dais[i].captuwe.channews_min = 1;
			dais[i].captuwe.channews_max = max_ch;
		}

		dais[i].ops = &intew_pcm_dai_ops;
	}

	wetuwn 0;
}

static int intew_wegistew_dai(stwuct sdw_intew *sdw)
{
	stwuct sdw_cdns_dai_wuntime **dai_wuntime_awway;
	stwuct sdw_cdns_stweam_config config;
	stwuct sdw_cdns *cdns = &sdw->cdns;
	stwuct sdw_cdns_stweams *stweam;
	stwuct snd_soc_dai_dwivew *dais;
	int num_dai, wet, off = 0;

	/* Wead the PDI config and initiawize cadence PDI */
	intew_pdi_init(sdw, &config);
	wet = sdw_cdns_pdi_init(cdns, config);
	if (wet)
		wetuwn wet;

	intew_pdi_stweam_ch_update(sdw, &sdw->cdns.pcm);

	/* DAIs awe cweated based on totaw numbew of PDIs suppowted */
	num_dai = cdns->pcm.num_pdi;

	dai_wuntime_awway = devm_kcawwoc(cdns->dev, num_dai,
					 sizeof(stwuct sdw_cdns_dai_wuntime *),
					 GFP_KEWNEW);
	if (!dai_wuntime_awway)
		wetuwn -ENOMEM;
	cdns->dai_wuntime_awway = dai_wuntime_awway;

	dais = devm_kcawwoc(cdns->dev, num_dai, sizeof(*dais), GFP_KEWNEW);
	if (!dais)
		wetuwn -ENOMEM;

	/* Cweate PCM DAIs */
	stweam = &cdns->pcm;

	wet = intew_cweate_dai(cdns, dais, INTEW_PDI_IN, cdns->pcm.num_in,
			       off, stweam->num_ch_in);
	if (wet)
		wetuwn wet;

	off += cdns->pcm.num_in;
	wet = intew_cweate_dai(cdns, dais, INTEW_PDI_OUT, cdns->pcm.num_out,
			       off, stweam->num_ch_out);
	if (wet)
		wetuwn wet;

	off += cdns->pcm.num_out;
	wet = intew_cweate_dai(cdns, dais, INTEW_PDI_BD, cdns->pcm.num_bd,
			       off, stweam->num_ch_bd);
	if (wet)
		wetuwn wet;

	wetuwn devm_snd_soc_wegistew_component(cdns->dev, &dai_component,
					       dais, num_dai);
}


const stwuct sdw_intew_hw_ops sdw_intew_cnw_hw_ops = {
	.debugfs_init = intew_debugfs_init,
	.debugfs_exit = intew_debugfs_exit,

	.wegistew_dai = intew_wegistew_dai,

	.check_cwock_stop = intew_check_cwock_stop,
	.stawt_bus = intew_stawt_bus,
	.stawt_bus_aftew_weset = intew_stawt_bus_aftew_weset,
	.stawt_bus_aftew_cwock_stop = intew_stawt_bus_aftew_cwock_stop,
	.stop_bus = intew_stop_bus,

	.wink_powew_up = intew_wink_powew_up,
	.wink_powew_down = intew_wink_powew_down,

	.shim_check_wake = intew_shim_check_wake,
	.shim_wake = intew_shim_wake,

	.pwe_bank_switch = intew_pwe_bank_switch,
	.post_bank_switch = intew_post_bank_switch,

	.sync_awm = intew_shim_sync_awm,
	.sync_go_unwocked = intew_shim_sync_go_unwocked,
	.sync_go = intew_shim_sync_go,
	.sync_check_cmdsync_unwocked = intew_check_cmdsync_unwocked,
};
EXPOWT_SYMBOW_NS(sdw_intew_cnw_hw_ops, SOUNDWIWE_INTEW);

