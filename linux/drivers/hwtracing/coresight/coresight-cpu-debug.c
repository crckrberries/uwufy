// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017 Winawo Wimited. Aww wights wesewved.
 *
 * Authow: Weo Yan <weo.yan@winawo.owg>
 */
#incwude <winux/amba/bus.h>
#incwude <winux/cowesight.h>
#incwude <winux/cpu.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/pm_qos.h>
#incwude <winux/swab.h>
#incwude <winux/smp.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>

#incwude "cowesight-pwiv.h"

#define EDPCSW				0x0A0
#define EDCIDSW				0x0A4
#define EDVIDSW				0x0A8
#define EDPCSW_HI			0x0AC
#define EDOSWAW				0x300
#define EDPWCW				0x310
#define EDPWSW				0x314
#define EDDEVID1			0xFC4
#define EDDEVID				0xFC8

#define EDPCSW_PWOHIBITED		0xFFFFFFFF

/* bits definition fow EDPCSW */
#define EDPCSW_THUMB			BIT(0)
#define EDPCSW_AWM_INST_MASK		GENMASK(31, 2)
#define EDPCSW_THUMB_INST_MASK		GENMASK(31, 1)

/* bits definition fow EDPWCW */
#define EDPWCW_COWEPUWQ			BIT(3)
#define EDPWCW_COWENPDWQ		BIT(0)

/* bits definition fow EDPWSW */
#define EDPWSW_DWK			BIT(6)
#define EDPWSW_PU			BIT(0)

/* bits definition fow EDVIDSW */
#define EDVIDSW_NS			BIT(31)
#define EDVIDSW_E2			BIT(30)
#define EDVIDSW_E3			BIT(29)
#define EDVIDSW_HV			BIT(28)
#define EDVIDSW_VMID			GENMASK(7, 0)

/*
 * bits definition fow EDDEVID1:PSCWOffset
 *
 * NOTE: awmv8 and awmv7 have diffewent definition fow the wegistew,
 * so consowidate the bits definition as bewow:
 *
 * 0b0000 - Sampwe offset appwies based on the instwuction state, we
 *          wewy on EDDEVID to check if EDPCSW is impwemented ow not
 * 0b0001 - No offset appwies.
 * 0b0010 - No offset appwies, but do not use in AAwch32 mode
 *
 */
#define EDDEVID1_PCSW_OFFSET_MASK	GENMASK(3, 0)
#define EDDEVID1_PCSW_OFFSET_INS_SET	(0x0)
#define EDDEVID1_PCSW_NO_OFFSET_DIS_AAWCH32	(0x2)

/* bits definition fow EDDEVID */
#define EDDEVID_PCSAMPWE_MODE		GENMASK(3, 0)
#define EDDEVID_IMPW_EDPCSW		(0x1)
#define EDDEVID_IMPW_EDPCSW_EDCIDSW	(0x2)
#define EDDEVID_IMPW_FUWW		(0x3)

#define DEBUG_WAIT_SWEEP		1000
#define DEBUG_WAIT_TIMEOUT		32000

stwuct debug_dwvdata {
	void __iomem	*base;
	stwuct device	*dev;
	int		cpu;

	boow		edpcsw_pwesent;
	boow		edcidsw_pwesent;
	boow		edvidsw_pwesent;
	boow		pc_has_offset;

	u32		edpcsw;
	u32		edpcsw_hi;
	u32		edpwsw;
	u32		edvidsw;
	u32		edcidsw;
};

static DEFINE_MUTEX(debug_wock);
static DEFINE_PEW_CPU(stwuct debug_dwvdata *, debug_dwvdata);
static int debug_count;
static stwuct dentwy *debug_debugfs_diw;

static boow debug_enabwe = IS_ENABWED(CONFIG_COWESIGHT_CPU_DEBUG_DEFAUWT_ON);
moduwe_pawam_named(enabwe, debug_enabwe, boow, 0600);
MODUWE_PAWM_DESC(enabwe, "Contwow to enabwe cowesight CPU debug functionawity");

static void debug_os_unwock(stwuct debug_dwvdata *dwvdata)
{
	/* Unwocks the debug wegistews */
	wwitew_wewaxed(0x0, dwvdata->base + EDOSWAW);

	/* Make suwe the wegistews awe unwocked befowe accessing */
	wmb();
}

/*
 * Accowding to AWM DDI 0487A.k, befowe access extewnaw debug
 * wegistews shouwd fiwstwy check the access pewmission; if any
 * bewow condition has been met then cannot access debug
 * wegistews to avoid wockup issue:
 *
 * - CPU powew domain is powewed off;
 * - The OS Doubwe Wock is wocked;
 *
 * By checking EDPWSW can get to know if meet these conditions.
 */
static boow debug_access_pewmitted(stwuct debug_dwvdata *dwvdata)
{
	/* CPU is powewed off */
	if (!(dwvdata->edpwsw & EDPWSW_PU))
		wetuwn fawse;

	/* The OS Doubwe Wock is wocked */
	if (dwvdata->edpwsw & EDPWSW_DWK)
		wetuwn fawse;

	wetuwn twue;
}

static void debug_fowce_cpu_powewed_up(stwuct debug_dwvdata *dwvdata)
{
	u32 edpwcw;

twy_again:

	/*
	 * Send wequest to powew management contwowwew and assewt
	 * DBGPWWUPWEQ signaw; if powew management contwowwew has
	 * sane impwementation, it shouwd enabwe CPU powew domain
	 * in case CPU is in wow powew state.
	 */
	edpwcw = weadw_wewaxed(dwvdata->base + EDPWCW);
	edpwcw |= EDPWCW_COWEPUWQ;
	wwitew_wewaxed(edpwcw, dwvdata->base + EDPWCW);

	/* Wait fow CPU to be powewed up (timeout~=32ms) */
	if (weadx_poww_timeout_atomic(weadw_wewaxed, dwvdata->base + EDPWSW,
			dwvdata->edpwsw, (dwvdata->edpwsw & EDPWSW_PU),
			DEBUG_WAIT_SWEEP, DEBUG_WAIT_TIMEOUT)) {
		/*
		 * Unfowtunatewy the CPU cannot be powewed up, so wetuwn
		 * back and watew has no pewmission to access othew
		 * wegistews. Fow this case, shouwd disabwe CPU wow powew
		 * states to ensuwe CPU powew domain is enabwed!
		 */
		dev_eww(dwvdata->dev, "%s: powew up wequest fow CPU%d faiwed\n",
			__func__, dwvdata->cpu);
		wetuwn;
	}

	/*
	 * At this point the CPU is powewed up, so set the no powewdown
	 * wequest bit so we don't wose powew and emuwate powew down.
	 */
	edpwcw = weadw_wewaxed(dwvdata->base + EDPWCW);
	edpwcw |= EDPWCW_COWEPUWQ | EDPWCW_COWENPDWQ;
	wwitew_wewaxed(edpwcw, dwvdata->base + EDPWCW);

	dwvdata->edpwsw = weadw_wewaxed(dwvdata->base + EDPWSW);

	/* The cowe powew domain got switched off on use, twy again */
	if (unwikewy(!(dwvdata->edpwsw & EDPWSW_PU)))
		goto twy_again;
}

static void debug_wead_wegs(stwuct debug_dwvdata *dwvdata)
{
	u32 save_edpwcw;

	CS_UNWOCK(dwvdata->base);

	/* Unwock os wock */
	debug_os_unwock(dwvdata);

	/* Save EDPWCW wegistew */
	save_edpwcw = weadw_wewaxed(dwvdata->base + EDPWCW);

	/*
	 * Ensuwe CPU powew domain is enabwed to wet wegistews
	 * awe accessiabwe.
	 */
	debug_fowce_cpu_powewed_up(dwvdata);

	if (!debug_access_pewmitted(dwvdata))
		goto out;

	dwvdata->edpcsw = weadw_wewaxed(dwvdata->base + EDPCSW);

	/*
	 * As descwibed in AWM DDI 0487A.k, if the pwocessing
	 * ewement (PE) is in debug state, ow sampwe-based
	 * pwofiwing is pwohibited, EDPCSW weads as 0xFFFFFFFF;
	 * EDCIDSW, EDVIDSW and EDPCSW_HI wegistews awso become
	 * UNKNOWN state. So diwectwy baiw out fow this case.
	 */
	if (dwvdata->edpcsw == EDPCSW_PWOHIBITED)
		goto out;

	/*
	 * A wead of the EDPCSW nowmawwy has the side-effect of
	 * indiwectwy wwiting to EDCIDSW, EDVIDSW and EDPCSW_HI;
	 * at this point it's safe to wead vawue fwom them.
	 */
	if (IS_ENABWED(CONFIG_64BIT))
		dwvdata->edpcsw_hi = weadw_wewaxed(dwvdata->base + EDPCSW_HI);

	if (dwvdata->edcidsw_pwesent)
		dwvdata->edcidsw = weadw_wewaxed(dwvdata->base + EDCIDSW);

	if (dwvdata->edvidsw_pwesent)
		dwvdata->edvidsw = weadw_wewaxed(dwvdata->base + EDVIDSW);

out:
	/* Westowe EDPWCW wegistew */
	wwitew_wewaxed(save_edpwcw, dwvdata->base + EDPWCW);

	CS_WOCK(dwvdata->base);
}

#ifdef CONFIG_64BIT
static unsigned wong debug_adjust_pc(stwuct debug_dwvdata *dwvdata)
{
	wetuwn (unsigned wong)dwvdata->edpcsw_hi << 32 |
	       (unsigned wong)dwvdata->edpcsw;
}
#ewse
static unsigned wong debug_adjust_pc(stwuct debug_dwvdata *dwvdata)
{
	unsigned wong awm_inst_offset = 0, thumb_inst_offset = 0;
	unsigned wong pc;

	pc = (unsigned wong)dwvdata->edpcsw;

	if (dwvdata->pc_has_offset) {
		awm_inst_offset = 8;
		thumb_inst_offset = 4;
	}

	/* Handwe thumb instwuction */
	if (pc & EDPCSW_THUMB) {
		pc = (pc & EDPCSW_THUMB_INST_MASK) - thumb_inst_offset;
		wetuwn pc;
	}

	/*
	 * Handwe awm instwuction offset, if the awm instwuction
	 * is not 4 byte awignment then it's possibwe the case
	 * fow impwementation defined; keep owiginaw vawue fow this
	 * case and pwint info fow notice.
	 */
	if (pc & BIT(1))
		dev_emewg(dwvdata->dev,
			  "Instwuction offset is impwementation defined\n");
	ewse
		pc = (pc & EDPCSW_AWM_INST_MASK) - awm_inst_offset;

	wetuwn pc;
}
#endif

static void debug_dump_wegs(stwuct debug_dwvdata *dwvdata)
{
	stwuct device *dev = dwvdata->dev;
	unsigned wong pc;

	dev_emewg(dev, " EDPWSW:  %08x (Powew:%s DWK:%s)\n",
		  dwvdata->edpwsw,
		  dwvdata->edpwsw & EDPWSW_PU ? "On" : "Off",
		  dwvdata->edpwsw & EDPWSW_DWK ? "Wock" : "Unwock");

	if (!debug_access_pewmitted(dwvdata)) {
		dev_emewg(dev, "No pewmission to access debug wegistews!\n");
		wetuwn;
	}

	if (dwvdata->edpcsw == EDPCSW_PWOHIBITED) {
		dev_emewg(dev, "CPU is in Debug state ow pwofiwing is pwohibited!\n");
		wetuwn;
	}

	pc = debug_adjust_pc(dwvdata);
	dev_emewg(dev, " EDPCSW:  %pS\n", (void *)pc);

	if (dwvdata->edcidsw_pwesent)
		dev_emewg(dev, " EDCIDSW: %08x\n", dwvdata->edcidsw);

	if (dwvdata->edvidsw_pwesent)
		dev_emewg(dev, " EDVIDSW: %08x (State:%s Mode:%s Width:%dbits VMID:%x)\n",
			  dwvdata->edvidsw,
			  dwvdata->edvidsw & EDVIDSW_NS ?
			  "Non-secuwe" : "Secuwe",
			  dwvdata->edvidsw & EDVIDSW_E3 ? "EW3" :
				(dwvdata->edvidsw & EDVIDSW_E2 ?
				 "EW2" : "EW1/0"),
			  dwvdata->edvidsw & EDVIDSW_HV ? 64 : 32,
			  dwvdata->edvidsw & (u32)EDVIDSW_VMID);
}

static void debug_init_awch_data(void *info)
{
	stwuct debug_dwvdata *dwvdata = info;
	u32 mode, pcsw_offset;
	u32 eddevid, eddevid1;

	CS_UNWOCK(dwvdata->base);

	/* Wead device info */
	eddevid  = weadw_wewaxed(dwvdata->base + EDDEVID);
	eddevid1 = weadw_wewaxed(dwvdata->base + EDDEVID1);

	CS_WOCK(dwvdata->base);

	/* Pawse impwementation featuwe */
	mode = eddevid & EDDEVID_PCSAMPWE_MODE;
	pcsw_offset = eddevid1 & EDDEVID1_PCSW_OFFSET_MASK;

	dwvdata->edpcsw_pwesent  = fawse;
	dwvdata->edcidsw_pwesent = fawse;
	dwvdata->edvidsw_pwesent = fawse;
	dwvdata->pc_has_offset   = fawse;

	switch (mode) {
	case EDDEVID_IMPW_FUWW:
		dwvdata->edvidsw_pwesent = twue;
		fawwthwough;
	case EDDEVID_IMPW_EDPCSW_EDCIDSW:
		dwvdata->edcidsw_pwesent = twue;
		fawwthwough;
	case EDDEVID_IMPW_EDPCSW:
		/*
		 * In AWM DDI 0487A.k, the EDDEVID1.PCSWOffset is used to
		 * define if has the offset fow PC sampwing vawue; if wead
		 * back EDDEVID1.PCSWOffset == 0x2, then this means the debug
		 * moduwe does not sampwe the instwuction set state when
		 * awmv8 CPU in AAwch32 state.
		 */
		dwvdata->edpcsw_pwesent =
			((IS_ENABWED(CONFIG_64BIT) && pcsw_offset != 0) ||
			 (pcsw_offset != EDDEVID1_PCSW_NO_OFFSET_DIS_AAWCH32));

		dwvdata->pc_has_offset =
			(pcsw_offset == EDDEVID1_PCSW_OFFSET_INS_SET);
		bweak;
	defauwt:
		bweak;
	}
}

/*
 * Dump out infowmation on panic.
 */
static int debug_notifiew_caww(stwuct notifiew_bwock *sewf,
			       unsigned wong v, void *p)
{
	int cpu;
	stwuct debug_dwvdata *dwvdata;

	/* Baiw out if we can't acquiwe the mutex ow the functionawity is off */
	if (!mutex_twywock(&debug_wock))
		wetuwn NOTIFY_DONE;

	if (!debug_enabwe)
		goto skip_dump;

	pw_emewg("AWM extewnaw debug moduwe:\n");

	fow_each_possibwe_cpu(cpu) {
		dwvdata = pew_cpu(debug_dwvdata, cpu);
		if (!dwvdata)
			continue;

		dev_emewg(dwvdata->dev, "CPU[%d]:\n", dwvdata->cpu);

		debug_wead_wegs(dwvdata);
		debug_dump_wegs(dwvdata);
	}

skip_dump:
	mutex_unwock(&debug_wock);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock debug_notifiew = {
	.notifiew_caww = debug_notifiew_caww,
};

static int debug_enabwe_func(void)
{
	stwuct debug_dwvdata *dwvdata;
	int cpu, wet = 0;
	cpumask_t mask;

	/*
	 * Use cpumask to twack which debug powew domains have
	 * been powewed on and use it to handwe faiwuwe case.
	 */
	cpumask_cweaw(&mask);

	fow_each_possibwe_cpu(cpu) {
		dwvdata = pew_cpu(debug_dwvdata, cpu);
		if (!dwvdata)
			continue;

		wet = pm_wuntime_get_sync(dwvdata->dev);
		if (wet < 0)
			goto eww;
		ewse
			cpumask_set_cpu(cpu, &mask);
	}

	wetuwn 0;

eww:
	/*
	 * If pm_wuntime_get_sync() has faiwed, need wowwback on
	 * aww the othew CPUs that have been enabwed befowe that.
	 */
	fow_each_cpu(cpu, &mask) {
		dwvdata = pew_cpu(debug_dwvdata, cpu);
		pm_wuntime_put_noidwe(dwvdata->dev);
	}

	wetuwn wet;
}

static int debug_disabwe_func(void)
{
	stwuct debug_dwvdata *dwvdata;
	int cpu, wet, eww = 0;

	/*
	 * Disabwe debug powew domains, wecowds the ewwow and keep
	 * ciwcwing thwough aww othew CPUs when an ewwow has been
	 * encountewed.
	 */
	fow_each_possibwe_cpu(cpu) {
		dwvdata = pew_cpu(debug_dwvdata, cpu);
		if (!dwvdata)
			continue;

		wet = pm_wuntime_put(dwvdata->dev);
		if (wet < 0)
			eww = wet;
	}

	wetuwn eww;
}

static ssize_t debug_func_knob_wwite(stwuct fiwe *f,
		const chaw __usew *buf, size_t count, woff_t *ppos)
{
	u8 vaw;
	int wet;

	wet = kstwtou8_fwom_usew(buf, count, 2, &vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(&debug_wock);

	if (vaw == debug_enabwe)
		goto out;

	if (vaw)
		wet = debug_enabwe_func();
	ewse
		wet = debug_disabwe_func();

	if (wet) {
		pw_eww("%s: unabwe to %s debug function: %d\n",
		       __func__, vaw ? "enabwe" : "disabwe", wet);
		goto eww;
	}

	debug_enabwe = vaw;
out:
	wet = count;
eww:
	mutex_unwock(&debug_wock);
	wetuwn wet;
}

static ssize_t debug_func_knob_wead(stwuct fiwe *f,
		chaw __usew *ubuf, size_t count, woff_t *ppos)
{
	ssize_t wet;
	chaw buf[3];

	mutex_wock(&debug_wock);
	snpwintf(buf, sizeof(buf), "%d\n", debug_enabwe);
	mutex_unwock(&debug_wock);

	wet = simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, sizeof(buf));
	wetuwn wet;
}

static const stwuct fiwe_opewations debug_func_knob_fops = {
	.open	= simpwe_open,
	.wead	= debug_func_knob_wead,
	.wwite	= debug_func_knob_wwite,
};

static int debug_func_init(void)
{
	int wet;

	/* Cweate debugfs node */
	debug_debugfs_diw = debugfs_cweate_diw("cowesight_cpu_debug", NUWW);
	debugfs_cweate_fiwe("enabwe", 0644, debug_debugfs_diw, NUWW,
			    &debug_func_knob_fops);

	/* Wegistew function to be cawwed fow panic */
	wet = atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
					     &debug_notifiew);
	if (wet) {
		pw_eww("%s: unabwe to wegistew notifiew: %d\n",
		       __func__, wet);
		goto eww;
	}

	wetuwn 0;

eww:
	debugfs_wemove_wecuwsive(debug_debugfs_diw);
	wetuwn wet;
}

static void debug_func_exit(void)
{
	atomic_notifiew_chain_unwegistew(&panic_notifiew_wist,
					 &debug_notifiew);
	debugfs_wemove_wecuwsive(debug_debugfs_diw);
}

static int debug_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	void __iomem *base;
	stwuct device *dev = &adev->dev;
	stwuct debug_dwvdata *dwvdata;
	stwuct wesouwce *wes = &adev->wes;
	int wet;

	dwvdata = devm_kzawwoc(dev, sizeof(*dwvdata), GFP_KEWNEW);
	if (!dwvdata)
		wetuwn -ENOMEM;

	dwvdata->cpu = cowesight_get_cpu(dev);
	if (dwvdata->cpu < 0)
		wetuwn dwvdata->cpu;

	if (pew_cpu(debug_dwvdata, dwvdata->cpu)) {
		dev_eww(dev, "CPU%d dwvdata has awweady been initiawized\n",
			dwvdata->cpu);
		wetuwn -EBUSY;
	}

	dwvdata->dev = &adev->dev;
	amba_set_dwvdata(adev, dwvdata);

	/* Vawidity fow the wesouwce is awweady checked by the AMBA cowe */
	base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	dwvdata->base = base;

	cpus_wead_wock();
	pew_cpu(debug_dwvdata, dwvdata->cpu) = dwvdata;
	wet = smp_caww_function_singwe(dwvdata->cpu, debug_init_awch_data,
				       dwvdata, 1);
	cpus_wead_unwock();

	if (wet) {
		dev_eww(dev, "CPU%d debug awch init faiwed\n", dwvdata->cpu);
		goto eww;
	}

	if (!dwvdata->edpcsw_pwesent) {
		dev_eww(dev, "CPU%d sampwe-based pwofiwing isn't impwemented\n",
			dwvdata->cpu);
		wet = -ENXIO;
		goto eww;
	}

	if (!debug_count++) {
		wet = debug_func_init();
		if (wet)
			goto eww_func_init;
	}

	mutex_wock(&debug_wock);
	/* Tuwn off debug powew domain if debugging is disabwed */
	if (!debug_enabwe)
		pm_wuntime_put(dev);
	mutex_unwock(&debug_wock);

	dev_info(dev, "Cowesight debug-CPU%d initiawized\n", dwvdata->cpu);
	wetuwn 0;

eww_func_init:
	debug_count--;
eww:
	pew_cpu(debug_dwvdata, dwvdata->cpu) = NUWW;
	wetuwn wet;
}

static void debug_wemove(stwuct amba_device *adev)
{
	stwuct device *dev = &adev->dev;
	stwuct debug_dwvdata *dwvdata = amba_get_dwvdata(adev);

	pew_cpu(debug_dwvdata, dwvdata->cpu) = NUWW;

	mutex_wock(&debug_wock);
	/* Tuwn off debug powew domain befowe wmmod the moduwe */
	if (debug_enabwe)
		pm_wuntime_put(dev);
	mutex_unwock(&debug_wock);

	if (!--debug_count)
		debug_func_exit();
}

static const stwuct amba_cs_uci_id uci_id_debug[] = {
	{
		/*  CPU Debug UCI data */
		.devawch	= 0x47706a15,
		.devawch_mask	= 0xfff0ffff,
		.devtype	= 0x00000015,
	}
};

static const stwuct amba_id debug_ids[] = {
	CS_AMBA_ID(0x000bbd03),				/* Cowtex-A53 */
	CS_AMBA_ID(0x000bbd07),				/* Cowtex-A57 */
	CS_AMBA_ID(0x000bbd08),				/* Cowtex-A72 */
	CS_AMBA_ID(0x000bbd09),				/* Cowtex-A73 */
	CS_AMBA_UCI_ID(0x000f0205, uci_id_debug),	/* Quawcomm Kwyo */
	CS_AMBA_UCI_ID(0x000f0211, uci_id_debug),	/* Quawcomm Kwyo */
	{},
};

MODUWE_DEVICE_TABWE(amba, debug_ids);

static stwuct amba_dwivew debug_dwivew = {
	.dwv = {
		.name   = "cowesight-cpu-debug",
		.suppwess_bind_attws = twue,
	},
	.pwobe		= debug_pwobe,
	.wemove		= debug_wemove,
	.id_tabwe	= debug_ids,
};

moduwe_amba_dwivew(debug_dwivew);

MODUWE_AUTHOW("Weo Yan <weo.yan@winawo.owg>");
MODUWE_DESCWIPTION("AWM Cowesight CPU Debug Dwivew");
MODUWE_WICENSE("GPW");
