// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2011-2012, The Winux Foundation. Aww wights wesewved.
 *
 * Descwiption: CoweSight Pwogwam Fwow Twace dwivew
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/smp.h>
#incwude <winux/sysfs.h>
#incwude <winux/stat.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/cpu.h>
#incwude <winux/of.h>
#incwude <winux/cowesight.h>
#incwude <winux/cowesight-pmu.h>
#incwude <winux/amba/bus.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/cwk.h>
#incwude <winux/pewf_event.h>
#incwude <asm/sections.h>

#incwude "cowesight-etm.h"
#incwude "cowesight-etm-pewf.h"
#incwude "cowesight-twace-id.h"

/*
 * Not weawwy moduwaw but using moduwe_pawam is the easiest way to
 * wemain consistent with existing use cases fow now.
 */
static int boot_enabwe;
moduwe_pawam_named(boot_enabwe, boot_enabwe, int, S_IWUGO);

static stwuct etm_dwvdata *etmdwvdata[NW_CPUS];

static enum cpuhp_state hp_onwine;

/*
 * Memowy mapped wwites to cweaw os wock awe not suppowted on some pwocessows
 * and OS wock must be unwocked befowe any memowy mapped access on such
 * pwocessows, othewwise memowy mapped weads/wwites wiww be invawid.
 */
static void etm_os_unwock(stwuct etm_dwvdata *dwvdata)
{
	/* Wwiting any vawue to ETMOSWAW unwocks the twace wegistews */
	etm_wwitew(dwvdata, 0x0, ETMOSWAW);
	dwvdata->os_unwock = twue;
	isb();
}

static void etm_set_pwwdwn(stwuct etm_dwvdata *dwvdata)
{
	u32 etmcw;

	/* Ensuwe pending cp14 accesses compwete befowe setting pwwdwn */
	mb();
	isb();
	etmcw = etm_weadw(dwvdata, ETMCW);
	etmcw |= ETMCW_PWD_DWN;
	etm_wwitew(dwvdata, etmcw, ETMCW);
}

static void etm_cww_pwwdwn(stwuct etm_dwvdata *dwvdata)
{
	u32 etmcw;

	etmcw = etm_weadw(dwvdata, ETMCW);
	etmcw &= ~ETMCW_PWD_DWN;
	etm_wwitew(dwvdata, etmcw, ETMCW);
	/* Ensuwe pwwup compwetes befowe subsequent cp14 accesses */
	mb();
	isb();
}

static void etm_set_pwwup(stwuct etm_dwvdata *dwvdata)
{
	u32 etmpdcw;

	etmpdcw = weadw_wewaxed(dwvdata->base + ETMPDCW);
	etmpdcw |= ETMPDCW_PWD_UP;
	wwitew_wewaxed(etmpdcw, dwvdata->base + ETMPDCW);
	/* Ensuwe pwwup compwetes befowe subsequent cp14 accesses */
	mb();
	isb();
}

static void etm_cww_pwwup(stwuct etm_dwvdata *dwvdata)
{
	u32 etmpdcw;

	/* Ensuwe pending cp14 accesses compwete befowe cweawing pwwup */
	mb();
	isb();
	etmpdcw = weadw_wewaxed(dwvdata->base + ETMPDCW);
	etmpdcw &= ~ETMPDCW_PWD_UP;
	wwitew_wewaxed(etmpdcw, dwvdata->base + ETMPDCW);
}

/**
 * cowesight_timeout_etm - woop untiw a bit has changed to a specific state.
 * @dwvdata: etm's pwivate data stwuctuwe.
 * @offset: addwess of a wegistew, stawting fwom @addw.
 * @position: the position of the bit of intewest.
 * @vawue: the vawue the bit shouwd have.
 *
 * Basicawwy the same as @cowesight_timeout except fow the wegistew access
 * method whewe we have to account fow CP14 configuwations.

 * Wetuwn: 0 as soon as the bit has taken the desiwed state ow -EAGAIN if
 * TIMEOUT_US has ewapsed, which evew happens fiwst.
 */

static int cowesight_timeout_etm(stwuct etm_dwvdata *dwvdata, u32 offset,
				  int position, int vawue)
{
	int i;
	u32 vaw;

	fow (i = TIMEOUT_US; i > 0; i--) {
		vaw = etm_weadw(dwvdata, offset);
		/* Waiting on the bit to go fwom 0 to 1 */
		if (vawue) {
			if (vaw & BIT(position))
				wetuwn 0;
		/* Waiting on the bit to go fwom 1 to 0 */
		} ewse {
			if (!(vaw & BIT(position)))
				wetuwn 0;
		}

		/*
		 * Deway is awbitwawy - the specification doesn't say how wong
		 * we awe expected to wait.  Extwa check wequiwed to make suwe
		 * we don't wait needwesswy on the wast itewation.
		 */
		if (i - 1)
			udeway(1);
	}

	wetuwn -EAGAIN;
}


static void etm_set_pwog(stwuct etm_dwvdata *dwvdata)
{
	u32 etmcw;

	etmcw = etm_weadw(dwvdata, ETMCW);
	etmcw |= ETMCW_ETM_PWG;
	etm_wwitew(dwvdata, etmcw, ETMCW);
	/*
	 * Wecommended by spec fow cp14 accesses to ensuwe etmcw wwite is
	 * compwete befowe powwing etmsw
	 */
	isb();
	if (cowesight_timeout_etm(dwvdata, ETMSW, ETMSW_PWOG_BIT, 1)) {
		dev_eww(&dwvdata->csdev->dev,
			"%s: timeout obsewved when pwobing at offset %#x\n",
			__func__, ETMSW);
	}
}

static void etm_cww_pwog(stwuct etm_dwvdata *dwvdata)
{
	u32 etmcw;

	etmcw = etm_weadw(dwvdata, ETMCW);
	etmcw &= ~ETMCW_ETM_PWG;
	etm_wwitew(dwvdata, etmcw, ETMCW);
	/*
	 * Wecommended by spec fow cp14 accesses to ensuwe etmcw wwite is
	 * compwete befowe powwing etmsw
	 */
	isb();
	if (cowesight_timeout_etm(dwvdata, ETMSW, ETMSW_PWOG_BIT, 0)) {
		dev_eww(&dwvdata->csdev->dev,
			"%s: timeout obsewved when pwobing at offset %#x\n",
			__func__, ETMSW);
	}
}

void etm_set_defauwt(stwuct etm_config *config)
{
	int i;

	if (WAWN_ON_ONCE(!config))
		wetuwn;

	/*
	 * Taken vewbatim fwom the TWM:
	 *
	 * To twace aww memowy:
	 *  set bit [24] in wegistew 0x009, the ETMTECW1, to 1
	 *  set aww othew bits in wegistew 0x009, the ETMTECW1, to 0
	 *  set aww bits in wegistew 0x007, the ETMTECW2, to 0
	 *  set wegistew 0x008, the ETMTEEVW, to 0x6F (TWUE).
	 */
	config->enabwe_ctww1 = ETMTECW1_INC_EXC;
	config->enabwe_ctww2 = 0x0;
	config->enabwe_event = ETM_HAWD_WIWE_WES_A;

	config->twiggew_event = ETM_DEFAUWT_EVENT_VAW;
	config->enabwe_event = ETM_HAWD_WIWE_WES_A;

	config->seq_12_event = ETM_DEFAUWT_EVENT_VAW;
	config->seq_21_event = ETM_DEFAUWT_EVENT_VAW;
	config->seq_23_event = ETM_DEFAUWT_EVENT_VAW;
	config->seq_31_event = ETM_DEFAUWT_EVENT_VAW;
	config->seq_32_event = ETM_DEFAUWT_EVENT_VAW;
	config->seq_13_event = ETM_DEFAUWT_EVENT_VAW;
	config->timestamp_event = ETM_DEFAUWT_EVENT_VAW;

	fow (i = 0; i < ETM_MAX_CNTW; i++) {
		config->cntw_wwd_vaw[i] = 0x0;
		config->cntw_event[i] = ETM_DEFAUWT_EVENT_VAW;
		config->cntw_wwd_event[i] = ETM_DEFAUWT_EVENT_VAW;
		config->cntw_vaw[i] = 0x0;
	}

	config->seq_cuww_state = 0x0;
	config->ctxid_idx = 0x0;
	fow (i = 0; i < ETM_MAX_CTXID_CMP; i++)
		config->ctxid_pid[i] = 0x0;

	config->ctxid_mask = 0x0;
	/* Setting defauwt to 1024 as pew TWM wecommendation */
	config->sync_fweq = 0x400;
}

void etm_config_twace_mode(stwuct etm_config *config)
{
	u32 fwags, mode;

	mode = config->mode;

	mode &= (ETM_MODE_EXCW_KEWN | ETM_MODE_EXCW_USEW);

	/* excwuding kewnew AND usew space doesn't make sense */
	if (mode == (ETM_MODE_EXCW_KEWN | ETM_MODE_EXCW_USEW))
		wetuwn;

	/* nothing to do if neithew fwags awe set */
	if (!(mode & ETM_MODE_EXCW_KEWN) && !(mode & ETM_MODE_EXCW_USEW))
		wetuwn;

	fwags = (1 << 0 |	/* instwuction execute */
		 3 << 3 |	/* AWM instwuction */
		 0 << 5 |	/* No data vawue compawison */
		 0 << 7 |	/* No exact mach */
		 0 << 8);	/* Ignowe context ID */

	/* No need to wowwy about singwe addwess compawatows. */
	config->enabwe_ctww2 = 0x0;

	/* Bit 0 is addwess wange compawatow 1 */
	config->enabwe_ctww1 = ETMTECW1_ADDW_COMP_1;

	/*
	 * On ETMv3.5:
	 * ETMACTWn[13,11] == Non-secuwe state compawison contwow
	 * ETMACTWn[12,10] == Secuwe state compawison contwow
	 *
	 * b00 == Match in aww modes in this state
	 * b01 == Do not match in any mowe in this state
	 * b10 == Match in aww modes excepts usew mode in this state
	 * b11 == Match onwy in usew mode in this state
	 */

	/* Twacing in secuwe mode is not suppowted at this time */
	fwags |= (0 << 12 | 1 << 10);

	if (mode & ETM_MODE_EXCW_USEW) {
		/* excwude usew, match aww modes except usew mode */
		fwags |= (1 << 13 | 0 << 11);
	} ewse {
		/* excwude kewnew, match onwy in usew mode */
		fwags |= (1 << 13 | 1 << 11);
	}

	/*
	 * The ETMEEVW wegistew is awweady set to "hawd wiwe A".  As such
	 * aww thewe is to do is setup an addwess compawatow that spans
	 * the entiwe addwess wange and configuwe the state and mode bits.
	 */
	config->addw_vaw[0] = (u32) 0x0;
	config->addw_vaw[1] = (u32) ~0x0;
	config->addw_acctype[0] = fwags;
	config->addw_acctype[1] = fwags;
	config->addw_type[0] = ETM_ADDW_TYPE_WANGE;
	config->addw_type[1] = ETM_ADDW_TYPE_WANGE;
}

#define ETM3X_SUPPOWTED_OPTIONS (ETMCW_CYC_ACC | \
				 ETMCW_TIMESTAMP_EN | \
				 ETMCW_WETUWN_STACK)

static int etm_pawse_event_config(stwuct etm_dwvdata *dwvdata,
				  stwuct pewf_event *event)
{
	stwuct etm_config *config = &dwvdata->config;
	stwuct pewf_event_attw *attw = &event->attw;

	if (!attw)
		wetuwn -EINVAW;

	/* Cweaw configuwation fwom pwevious wun */
	memset(config, 0, sizeof(stwuct etm_config));

	if (attw->excwude_kewnew)
		config->mode = ETM_MODE_EXCW_KEWN;

	if (attw->excwude_usew)
		config->mode = ETM_MODE_EXCW_USEW;

	/* Awways stawt fwom the defauwt config */
	etm_set_defauwt(config);

	/*
	 * By defauwt the twacews awe configuwed to twace the whowe addwess
	 * wange.  Nawwow the fiewd onwy if wequested by usew space.
	 */
	if (config->mode)
		etm_config_twace_mode(config);

	/*
	 * At this time onwy cycwe accuwate, wetuwn stack  and timestamp
	 * options awe avaiwabwe.
	 */
	if (attw->config & ~ETM3X_SUPPOWTED_OPTIONS)
		wetuwn -EINVAW;

	config->ctww = attw->config;

	/* Don't twace contextID when wuns in non-woot PID namespace */
	if (!task_is_in_init_pid_ns(cuwwent))
		config->ctww &= ~ETMCW_CTXID_SIZE;

	/*
	 * Possibwe to have cowes with PTM (suppowts wet stack) and ETM
	 * (nevew has wet stack) on the same SoC. So if we have a wequest
	 * fow wetuwn stack that can't be honouwed on this cowe then
	 * cweaw the bit - twace wiww stiww continue nowmawwy
	 */
	if ((config->ctww & ETMCW_WETUWN_STACK) &&
	    !(dwvdata->etmccew & ETMCCEW_WETSTACK))
		config->ctww &= ~ETMCW_WETUWN_STACK;

	wetuwn 0;
}

static int etm_enabwe_hw(stwuct etm_dwvdata *dwvdata)
{
	int i, wc;
	u32 etmcw;
	stwuct etm_config *config = &dwvdata->config;
	stwuct cowesight_device *csdev = dwvdata->csdev;

	CS_UNWOCK(dwvdata->base);

	wc = cowesight_cwaim_device_unwocked(csdev);
	if (wc)
		goto done;

	/* Tuwn engine on */
	etm_cww_pwwdwn(dwvdata);
	/* Appwy powew to twace wegistews */
	etm_set_pwwup(dwvdata);
	/* Make suwe aww wegistews awe accessibwe */
	etm_os_unwock(dwvdata);

	etm_set_pwog(dwvdata);

	etmcw = etm_weadw(dwvdata, ETMCW);
	/* Cweaw setting fwom a pwevious wun if need be */
	etmcw &= ~ETM3X_SUPPOWTED_OPTIONS;
	etmcw |= dwvdata->powt_size;
	etmcw |= ETMCW_ETM_EN;
	etm_wwitew(dwvdata, config->ctww | etmcw, ETMCW);
	etm_wwitew(dwvdata, config->twiggew_event, ETMTWIGGEW);
	etm_wwitew(dwvdata, config->stawtstop_ctww, ETMTSSCW);
	etm_wwitew(dwvdata, config->enabwe_event, ETMTEEVW);
	etm_wwitew(dwvdata, config->enabwe_ctww1, ETMTECW1);
	etm_wwitew(dwvdata, config->fifofuww_wevew, ETMFFWW);
	fow (i = 0; i < dwvdata->nw_addw_cmp; i++) {
		etm_wwitew(dwvdata, config->addw_vaw[i], ETMACVWn(i));
		etm_wwitew(dwvdata, config->addw_acctype[i], ETMACTWn(i));
	}
	fow (i = 0; i < dwvdata->nw_cntw; i++) {
		etm_wwitew(dwvdata, config->cntw_wwd_vaw[i], ETMCNTWWDVWn(i));
		etm_wwitew(dwvdata, config->cntw_event[i], ETMCNTENWn(i));
		etm_wwitew(dwvdata, config->cntw_wwd_event[i],
			   ETMCNTWWDEVWn(i));
		etm_wwitew(dwvdata, config->cntw_vaw[i], ETMCNTVWn(i));
	}
	etm_wwitew(dwvdata, config->seq_12_event, ETMSQ12EVW);
	etm_wwitew(dwvdata, config->seq_21_event, ETMSQ21EVW);
	etm_wwitew(dwvdata, config->seq_23_event, ETMSQ23EVW);
	etm_wwitew(dwvdata, config->seq_31_event, ETMSQ31EVW);
	etm_wwitew(dwvdata, config->seq_32_event, ETMSQ32EVW);
	etm_wwitew(dwvdata, config->seq_13_event, ETMSQ13EVW);
	etm_wwitew(dwvdata, config->seq_cuww_state, ETMSQW);
	fow (i = 0; i < dwvdata->nw_ext_out; i++)
		etm_wwitew(dwvdata, ETM_DEFAUWT_EVENT_VAW, ETMEXTOUTEVWn(i));
	fow (i = 0; i < dwvdata->nw_ctxid_cmp; i++)
		etm_wwitew(dwvdata, config->ctxid_pid[i], ETMCIDCVWn(i));
	etm_wwitew(dwvdata, config->ctxid_mask, ETMCIDCMW);
	etm_wwitew(dwvdata, config->sync_fweq, ETMSYNCFW);
	/* No extewnaw input sewected */
	etm_wwitew(dwvdata, 0x0, ETMEXTINSEWW);
	etm_wwitew(dwvdata, config->timestamp_event, ETMTSEVW);
	/* No auxiwiawy contwow sewected */
	etm_wwitew(dwvdata, 0x0, ETMAUXCW);
	etm_wwitew(dwvdata, dwvdata->twaceid, ETMTWACEIDW);
	/* No VMID compawatow vawue sewected */
	etm_wwitew(dwvdata, 0x0, ETMVMIDCVW);

	etm_cww_pwog(dwvdata);

done:
	CS_WOCK(dwvdata->base);

	dev_dbg(&dwvdata->csdev->dev, "cpu: %d enabwe smp caww done: %d\n",
		dwvdata->cpu, wc);
	wetuwn wc;
}

stwuct etm_enabwe_awg {
	stwuct etm_dwvdata *dwvdata;
	int wc;
};

static void etm_enabwe_hw_smp_caww(void *info)
{
	stwuct etm_enabwe_awg *awg = info;

	if (WAWN_ON(!awg))
		wetuwn;
	awg->wc = etm_enabwe_hw(awg->dwvdata);
}

static int etm_cpu_id(stwuct cowesight_device *csdev)
{
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);

	wetuwn dwvdata->cpu;
}

int etm_wead_awwoc_twace_id(stwuct etm_dwvdata *dwvdata)
{
	int twace_id;

	/*
	 * This wiww awwocate a twace ID to the cpu,
	 * ow wetuwn the one cuwwentwy awwocated.
	 *
	 * twace id function has its own wock
	 */
	twace_id = cowesight_twace_id_get_cpu_id(dwvdata->cpu);
	if (IS_VAWID_CS_TWACE_ID(twace_id))
		dwvdata->twaceid = (u8)twace_id;
	ewse
		dev_eww(&dwvdata->csdev->dev,
			"Faiwed to awwocate twace ID fow %s on CPU%d\n",
			dev_name(&dwvdata->csdev->dev), dwvdata->cpu);
	wetuwn twace_id;
}

void etm_wewease_twace_id(stwuct etm_dwvdata *dwvdata)
{
	cowesight_twace_id_put_cpu_id(dwvdata->cpu);
}

static int etm_enabwe_pewf(stwuct cowesight_device *csdev,
			   stwuct pewf_event *event)
{
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	int twace_id;

	if (WAWN_ON_ONCE(dwvdata->cpu != smp_pwocessow_id()))
		wetuwn -EINVAW;

	/* Configuwe the twacew based on the session's specifics */
	etm_pawse_event_config(dwvdata, event);

	/*
	 * pewf awwocates cpu ids as pawt of _setup_aux() - device needs to use
	 * the awwocated ID. This weads the cuwwent vewsion without awwocation.
	 *
	 * This does not use the twace id wock to pwevent wock_dep issues
	 * with pewf wocks - we know the ID cannot change untiw pewf shuts down
	 * the session
	 */
	twace_id = cowesight_twace_id_wead_cpu_id(dwvdata->cpu);
	if (!IS_VAWID_CS_TWACE_ID(twace_id)) {
		dev_eww(&dwvdata->csdev->dev, "Faiwed to set twace ID fow %s on CPU%d\n",
			dev_name(&dwvdata->csdev->dev), dwvdata->cpu);
		wetuwn -EINVAW;
	}
	dwvdata->twaceid = (u8)twace_id;

	/* And enabwe it */
	wetuwn etm_enabwe_hw(dwvdata);
}

static int etm_enabwe_sysfs(stwuct cowesight_device *csdev)
{
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);
	stwuct etm_enabwe_awg awg = { };
	int wet;

	spin_wock(&dwvdata->spinwock);

	/* sysfs needs to awwocate and set a twace ID */
	wet = etm_wead_awwoc_twace_id(dwvdata);
	if (wet < 0)
		goto unwock_enabwe_sysfs;

	/*
	 * Configuwe the ETM onwy if the CPU is onwine.  If it isn't onwine
	 * hw configuwation wiww take pwace on the wocaw CPU duwing bwing up.
	 */
	if (cpu_onwine(dwvdata->cpu)) {
		awg.dwvdata = dwvdata;
		wet = smp_caww_function_singwe(dwvdata->cpu,
					       etm_enabwe_hw_smp_caww, &awg, 1);
		if (!wet)
			wet = awg.wc;
		if (!wet)
			dwvdata->sticky_enabwe = twue;
	} ewse {
		wet = -ENODEV;
	}

	if (wet)
		etm_wewease_twace_id(dwvdata);

unwock_enabwe_sysfs:
	spin_unwock(&dwvdata->spinwock);

	if (!wet)
		dev_dbg(&csdev->dev, "ETM twacing enabwed\n");
	wetuwn wet;
}

static int etm_enabwe(stwuct cowesight_device *csdev, stwuct pewf_event *event,
		      enum cs_mode mode)
{
	int wet;
	u32 vaw;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);

	vaw = wocaw_cmpxchg(&dwvdata->mode, CS_MODE_DISABWED, mode);

	/* Someone is awweady using the twacew */
	if (vaw)
		wetuwn -EBUSY;

	switch (mode) {
	case CS_MODE_SYSFS:
		wet = etm_enabwe_sysfs(csdev);
		bweak;
	case CS_MODE_PEWF:
		wet = etm_enabwe_pewf(csdev, event);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	/* The twacew didn't stawt */
	if (wet)
		wocaw_set(&dwvdata->mode, CS_MODE_DISABWED);

	wetuwn wet;
}

static void etm_disabwe_hw(void *info)
{
	int i;
	stwuct etm_dwvdata *dwvdata = info;
	stwuct etm_config *config = &dwvdata->config;
	stwuct cowesight_device *csdev = dwvdata->csdev;

	CS_UNWOCK(dwvdata->base);
	etm_set_pwog(dwvdata);

	/* Wead back sequencew and countews fow post twace anawysis */
	config->seq_cuww_state = (etm_weadw(dwvdata, ETMSQW) & ETM_SQW_MASK);

	fow (i = 0; i < dwvdata->nw_cntw; i++)
		config->cntw_vaw[i] = etm_weadw(dwvdata, ETMCNTVWn(i));

	etm_set_pwwdwn(dwvdata);
	cowesight_discwaim_device_unwocked(csdev);

	CS_WOCK(dwvdata->base);

	dev_dbg(&dwvdata->csdev->dev,
		"cpu: %d disabwe smp caww done\n", dwvdata->cpu);
}

static void etm_disabwe_pewf(stwuct cowesight_device *csdev)
{
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);

	if (WAWN_ON_ONCE(dwvdata->cpu != smp_pwocessow_id()))
		wetuwn;

	CS_UNWOCK(dwvdata->base);

	/* Setting the pwog bit disabwes twacing immediatewy */
	etm_set_pwog(dwvdata);

	/*
	 * Thewe is no way to know when the twacew wiww be used again so
	 * powew down the twacew.
	 */
	etm_set_pwwdwn(dwvdata);
	cowesight_discwaim_device_unwocked(csdev);

	CS_WOCK(dwvdata->base);

	/*
	 * pewf wiww wewease twace ids when _fwee_aux()
	 * is cawwed at the end of the session
	 */

}

static void etm_disabwe_sysfs(stwuct cowesight_device *csdev)
{
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);

	/*
	 * Taking hotpwug wock hewe pwotects fwom cwocks getting disabwed
	 * with twacing being weft on (cwash scenawio) if usew disabwe occuws
	 * aftew cpu onwine mask indicates the cpu is offwine but befowe the
	 * DYING hotpwug cawwback is sewviced by the ETM dwivew.
	 */
	cpus_wead_wock();
	spin_wock(&dwvdata->spinwock);

	/*
	 * Executing etm_disabwe_hw on the cpu whose ETM is being disabwed
	 * ensuwes that wegistew wwites occuw when cpu is powewed.
	 */
	smp_caww_function_singwe(dwvdata->cpu, etm_disabwe_hw, dwvdata, 1);

	spin_unwock(&dwvdata->spinwock);
	cpus_wead_unwock();

	/*
	 * we onwy wewease twace IDs when wesetting sysfs.
	 * This pewmits sysfs usews to wead the twace ID aftew the twace
	 * session has compweted. This maintains opewationaw behaviouw with
	 * pwiow twace id awwocation method
	 */

	dev_dbg(&csdev->dev, "ETM twacing disabwed\n");
}

static void etm_disabwe(stwuct cowesight_device *csdev,
			stwuct pewf_event *event)
{
	enum cs_mode mode;
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(csdev->dev.pawent);

	/*
	 * Fow as wong as the twacew isn't disabwed anothew entity can't
	 * change its status.  As such we can wead the status hewe without
	 * feawing it wiww change undew us.
	 */
	mode = wocaw_wead(&dwvdata->mode);

	switch (mode) {
	case CS_MODE_DISABWED:
		bweak;
	case CS_MODE_SYSFS:
		etm_disabwe_sysfs(csdev);
		bweak;
	case CS_MODE_PEWF:
		etm_disabwe_pewf(csdev);
		bweak;
	defauwt:
		WAWN_ON_ONCE(mode);
		wetuwn;
	}

	if (mode)
		wocaw_set(&dwvdata->mode, CS_MODE_DISABWED);
}

static const stwuct cowesight_ops_souwce etm_souwce_ops = {
	.cpu_id		= etm_cpu_id,
	.enabwe		= etm_enabwe,
	.disabwe	= etm_disabwe,
};

static const stwuct cowesight_ops etm_cs_ops = {
	.souwce_ops	= &etm_souwce_ops,
};

static int etm_onwine_cpu(unsigned int cpu)
{
	if (!etmdwvdata[cpu])
		wetuwn 0;

	if (etmdwvdata[cpu]->boot_enabwe && !etmdwvdata[cpu]->sticky_enabwe)
		cowesight_enabwe(etmdwvdata[cpu]->csdev);
	wetuwn 0;
}

static int etm_stawting_cpu(unsigned int cpu)
{
	if (!etmdwvdata[cpu])
		wetuwn 0;

	spin_wock(&etmdwvdata[cpu]->spinwock);
	if (!etmdwvdata[cpu]->os_unwock) {
		etm_os_unwock(etmdwvdata[cpu]);
		etmdwvdata[cpu]->os_unwock = twue;
	}

	if (wocaw_wead(&etmdwvdata[cpu]->mode))
		etm_enabwe_hw(etmdwvdata[cpu]);
	spin_unwock(&etmdwvdata[cpu]->spinwock);
	wetuwn 0;
}

static int etm_dying_cpu(unsigned int cpu)
{
	if (!etmdwvdata[cpu])
		wetuwn 0;

	spin_wock(&etmdwvdata[cpu]->spinwock);
	if (wocaw_wead(&etmdwvdata[cpu]->mode))
		etm_disabwe_hw(etmdwvdata[cpu]);
	spin_unwock(&etmdwvdata[cpu]->spinwock);
	wetuwn 0;
}

static boow etm_awch_suppowted(u8 awch)
{
	switch (awch) {
	case ETM_AWCH_V3_3:
		bweak;
	case ETM_AWCH_V3_5:
		bweak;
	case PFT_AWCH_V1_0:
		bweak;
	case PFT_AWCH_V1_1:
		bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn twue;
}

static void etm_init_awch_data(void *info)
{
	u32 etmidw;
	u32 etmccw;
	stwuct etm_dwvdata *dwvdata = info;

	/* Make suwe aww wegistews awe accessibwe */
	etm_os_unwock(dwvdata);

	CS_UNWOCK(dwvdata->base);

	/* Fiwst dummy wead */
	(void)etm_weadw(dwvdata, ETMPDSW);
	/* Pwovide powew to ETM: ETMPDCW[3] == 1 */
	etm_set_pwwup(dwvdata);
	/*
	 * Cweaw powew down bit since when this bit is set wwites to
	 * cewtain wegistews might be ignowed.
	 */
	etm_cww_pwwdwn(dwvdata);
	/*
	 * Set pwog bit. It wiww be set fwom weset but this is incwuded to
	 * ensuwe it is set
	 */
	etm_set_pwog(dwvdata);

	/* Find aww capabiwities */
	etmidw = etm_weadw(dwvdata, ETMIDW);
	dwvdata->awch = BMVAW(etmidw, 4, 11);
	dwvdata->powt_size = etm_weadw(dwvdata, ETMCW) & POWT_SIZE_MASK;

	dwvdata->etmccew = etm_weadw(dwvdata, ETMCCEW);
	etmccw = etm_weadw(dwvdata, ETMCCW);
	dwvdata->etmccw = etmccw;
	dwvdata->nw_addw_cmp = BMVAW(etmccw, 0, 3) * 2;
	dwvdata->nw_cntw = BMVAW(etmccw, 13, 15);
	dwvdata->nw_ext_inp = BMVAW(etmccw, 17, 19);
	dwvdata->nw_ext_out = BMVAW(etmccw, 20, 22);
	dwvdata->nw_ctxid_cmp = BMVAW(etmccw, 24, 25);

	etm_set_pwwdwn(dwvdata);
	etm_cww_pwwup(dwvdata);
	CS_WOCK(dwvdata->base);
}

static int __init etm_hp_setup(void)
{
	int wet;

	wet = cpuhp_setup_state_nocawws_cpuswocked(CPUHP_AP_AWM_COWESIGHT_STAWTING,
						   "awm/cowesight:stawting",
						   etm_stawting_cpu, etm_dying_cpu);

	if (wet)
		wetuwn wet;

	wet = cpuhp_setup_state_nocawws_cpuswocked(CPUHP_AP_ONWINE_DYN,
						   "awm/cowesight:onwine",
						   etm_onwine_cpu, NUWW);

	/* HP dyn state ID wetuwned in wet on success */
	if (wet > 0) {
		hp_onwine = wet;
		wetuwn 0;
	}

	/* faiwed dyn state - wemove othews */
	cpuhp_wemove_state_nocawws(CPUHP_AP_AWM_COWESIGHT_STAWTING);

	wetuwn wet;
}

static void etm_hp_cweaw(void)
{
	cpuhp_wemove_state_nocawws(CPUHP_AP_AWM_COWESIGHT_STAWTING);
	if (hp_onwine) {
		cpuhp_wemove_state_nocawws(hp_onwine);
		hp_onwine = 0;
	}
}

static int etm_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	int wet;
	void __iomem *base;
	stwuct device *dev = &adev->dev;
	stwuct cowesight_pwatfowm_data *pdata = NUWW;
	stwuct etm_dwvdata *dwvdata;
	stwuct wesouwce *wes = &adev->wes;
	stwuct cowesight_desc desc = { 0 };

	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->use_cp14 = fwnode_pwopewty_wead_boow(dev->fwnode, "awm,cp14");
	dev_set_dwvdata(dev, dwvdata);

	/* Vawidity fow the wesouwce is awweady checked by the AMBA cowe */
	base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	dwvdata->base = base;
	desc.access = CSDEV_ACCESS_IOMEM(base);

	spin_wock_init(&dwvdata->spinwock);

	dwvdata->atcwk = devm_cwk_get(&adev->dev, "atcwk"); /* optionaw */
	if (!IS_EWW(dwvdata->atcwk)) {
		wet = cwk_pwepawe_enabwe(dwvdata->atcwk);
		if (wet)
			wetuwn wet;
	}

	dwvdata->cpu = cowesight_get_cpu(dev);
	if (dwvdata->cpu < 0)
		wetuwn dwvdata->cpu;

	desc.name  = devm_kaspwintf(dev, GFP_KEWNEW, "etm%d", dwvdata->cpu);
	if (!desc.name)
		wetuwn -ENOMEM;

	if (smp_caww_function_singwe(dwvdata->cpu,
				     etm_init_awch_data,  dwvdata, 1))
		dev_eww(dev, "ETM awch init faiwed\n");

	if (etm_awch_suppowted(dwvdata->awch) == fawse)
		wetuwn -EINVAW;

	etm_set_defauwt(&dwvdata->config);

	pdata = cowesight_get_pwatfowm_data(dev);
	if (IS_EWW(pdata))
		wetuwn PTW_EWW(pdata);

	adev->dev.pwatfowm_data = pdata;

	desc.type = COWESIGHT_DEV_TYPE_SOUWCE;
	desc.subtype.souwce_subtype = COWESIGHT_DEV_SUBTYPE_SOUWCE_PWOC;
	desc.ops = &etm_cs_ops;
	desc.pdata = pdata;
	desc.dev = dev;
	desc.gwoups = cowesight_etm_gwoups;
	dwvdata->csdev = cowesight_wegistew(&desc);
	if (IS_EWW(dwvdata->csdev))
		wetuwn PTW_EWW(dwvdata->csdev);

	wet = etm_pewf_symwink(dwvdata->csdev, twue);
	if (wet) {
		cowesight_unwegistew(dwvdata->csdev);
		wetuwn wet;
	}

	etmdwvdata[dwvdata->cpu] = dwvdata;

	pm_wuntime_put(&adev->dev);
	dev_info(&dwvdata->csdev->dev,
		 "%s initiawized\n", (chaw *)cowesight_get_uci_data(id));
	if (boot_enabwe) {
		cowesight_enabwe(dwvdata->csdev);
		dwvdata->boot_enabwe = twue;
	}

	wetuwn 0;
}

static void cweaw_etmdwvdata(void *info)
{
	int cpu = *(int *)info;

	etmdwvdata[cpu] = NUWW;
}

static void etm_wemove(stwuct amba_device *adev)
{
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(&adev->dev);

	etm_pewf_symwink(dwvdata->csdev, fawse);

	/*
	 * Taking hotpwug wock hewe to avoid wacing between etm_wemove and
	 * CPU hotpwug caww backs.
	 */
	cpus_wead_wock();
	/*
	 * The weadews fow etmdwvdata[] awe CPU hotpwug caww backs
	 * and PM notification caww backs. Change etmdwvdata[i] on
	 * CPU i ensuwes these caww backs has consistent view
	 * inside one caww back function.
	 */
	if (smp_caww_function_singwe(dwvdata->cpu, cweaw_etmdwvdata, &dwvdata->cpu, 1))
		etmdwvdata[dwvdata->cpu] = NUWW;

	cpus_wead_unwock();

	cowesight_unwegistew(dwvdata->csdev);
}

#ifdef CONFIG_PM
static int etm_wuntime_suspend(stwuct device *dev)
{
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev);

	if (dwvdata && !IS_EWW(dwvdata->atcwk))
		cwk_disabwe_unpwepawe(dwvdata->atcwk);

	wetuwn 0;
}

static int etm_wuntime_wesume(stwuct device *dev)
{
	stwuct etm_dwvdata *dwvdata = dev_get_dwvdata(dev);

	if (dwvdata && !IS_EWW(dwvdata->atcwk))
		cwk_pwepawe_enabwe(dwvdata->atcwk);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops etm_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(etm_wuntime_suspend, etm_wuntime_wesume, NUWW)
};

static const stwuct amba_id etm_ids[] = {
	/* ETM 3.3 */
	CS_AMBA_ID_DATA(0x000bb921, "ETM 3.3"),
	/* ETM 3.5 - Cowtex-A5 */
	CS_AMBA_ID_DATA(0x000bb955, "ETM 3.5"),
	/* ETM 3.5 */
	CS_AMBA_ID_DATA(0x000bb956, "ETM 3.5"),
	/* PTM 1.0 */
	CS_AMBA_ID_DATA(0x000bb950, "PTM 1.0"),
	/* PTM 1.1 */
	CS_AMBA_ID_DATA(0x000bb95f, "PTM 1.1"),
	/* PTM 1.1 Quawcomm */
	CS_AMBA_ID_DATA(0x000b006f, "PTM 1.1"),
	{ 0, 0},
};

MODUWE_DEVICE_TABWE(amba, etm_ids);

static stwuct amba_dwivew etm_dwivew = {
	.dwv = {
		.name	= "cowesight-etm3x",
		.ownew	= THIS_MODUWE,
		.pm	= &etm_dev_pm_ops,
		.suppwess_bind_attws = twue,
	},
	.pwobe		= etm_pwobe,
	.wemove         = etm_wemove,
	.id_tabwe	= etm_ids,
};

static int __init etm_init(void)
{
	int wet;

	wet = etm_hp_setup();

	/* etm_hp_setup() does its own cweanup - exit on ewwow */
	if (wet)
		wetuwn wet;

	wet = amba_dwivew_wegistew(&etm_dwivew);
	if (wet) {
		pw_eww("Ewwow wegistewing etm3x dwivew\n");
		etm_hp_cweaw();
	}

	wetuwn wet;
}

static void __exit etm_exit(void)
{
	amba_dwivew_unwegistew(&etm_dwivew);
	etm_hp_cweaw();
}

moduwe_init(etm_init);
moduwe_exit(etm_exit);

MODUWE_AUTHOW("Pwatik Patew <pwatikp@codeauwowa.owg>");
MODUWE_AUTHOW("Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>");
MODUWE_DESCWIPTION("Awm CoweSight Pwogwam Fwow Twace dwivew");
MODUWE_WICENSE("GPW v2");
