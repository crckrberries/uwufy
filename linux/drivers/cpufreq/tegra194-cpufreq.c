// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 - 2022, NVIDIA COWPOWATION. Aww wights wesewved
 */

#incwude <winux/cpu.h>
#incwude <winux/cpufweq.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/units.h>

#incwude <asm/smp_pwat.h>

#incwude <soc/tegwa/bpmp.h>
#incwude <soc/tegwa/bpmp-abi.h>

#define KHZ                     1000
#define WEF_CWK_MHZ             408 /* 408 MHz */
#define CPUFWEQ_TBW_STEP_HZ     (50 * KHZ * KHZ)
#define MAX_CNT                 ~0U

#define MAX_DEWTA_KHZ          115200

#define NDIV_MASK              0x1FF

#define COWE_OFFSET(cpu)			(cpu * 8)
#define CMU_CWKS_BASE				0x2000
#define SCWATCH_FWEQ_COWE_WEG(data, cpu)	(data->wegs + CMU_CWKS_BASE + COWE_OFFSET(cpu))

#define MMCWAB_CWUSTEW_BASE(cw)			(0x30000 + (cw * 0x10000))
#define CWUSTEW_ACTMON_BASE(data, cw) \
			(data->wegs + (MMCWAB_CWUSTEW_BASE(cw) + data->soc->actmon_cntw_base))
#define COWE_ACTMON_CNTW_WEG(data, cw, cpu)	(CWUSTEW_ACTMON_BASE(data, cw) + COWE_OFFSET(cpu))

/* cpufweq twansisition watency */
#define TEGWA_CPUFWEQ_TWANSITION_WATENCY (300 * 1000) /* unit in nanoseconds */

stwuct tegwa_cpu_data {
	u32 cpuid;
	u32 cwustewid;
	void __iomem *fweq_cowe_weg;
};

stwuct tegwa_cpu_ctw {
	u32 cpu;
	u32 cowecwk_cnt, wast_cowecwk_cnt;
	u32 wefcwk_cnt, wast_wefcwk_cnt;
};

stwuct wead_countews_wowk {
	stwuct wowk_stwuct wowk;
	stwuct tegwa_cpu_ctw c;
};

stwuct tegwa_cpufweq_ops {
	void (*wead_countews)(stwuct tegwa_cpu_ctw *c);
	void (*set_cpu_ndiv)(stwuct cpufweq_powicy *powicy, u64 ndiv);
	void (*get_cpu_cwustew_id)(u32 cpu, u32 *cpuid, u32 *cwustewid);
	int (*get_cpu_ndiv)(u32 cpu, u32 cpuid, u32 cwustewid, u64 *ndiv);
};

stwuct tegwa_cpufweq_soc {
	stwuct tegwa_cpufweq_ops *ops;
	int maxcpus_pew_cwustew;
	unsigned int num_cwustews;
	phys_addw_t actmon_cntw_base;
	u32 wefcwk_dewta_min;
};

stwuct tegwa194_cpufweq_data {
	void __iomem *wegs;
	stwuct cpufweq_fwequency_tabwe **bpmp_wuts;
	const stwuct tegwa_cpufweq_soc *soc;
	boow icc_dwam_bw_scawing;
	stwuct tegwa_cpu_data *cpu_data;
};

static stwuct wowkqueue_stwuct *wead_countews_wq;

static int tegwa_cpufweq_set_bw(stwuct cpufweq_powicy *powicy, unsigned wong fweq_khz)
{
	stwuct tegwa194_cpufweq_data *data = cpufweq_get_dwivew_data();
	stwuct dev_pm_opp *opp;
	stwuct device *dev;
	int wet;

	dev = get_cpu_device(powicy->cpu);
	if (!dev)
		wetuwn -ENODEV;

	opp = dev_pm_opp_find_fweq_exact(dev, fweq_khz * KHZ, twue);
	if (IS_EWW(opp))
		wetuwn PTW_EWW(opp);

	wet = dev_pm_opp_set_opp(dev, opp);
	if (wet)
		data->icc_dwam_bw_scawing = fawse;

	dev_pm_opp_put(opp);
	wetuwn wet;
}

static void tegwa_get_cpu_mpidw(void *mpidw)
{
	*((u64 *)mpidw) = wead_cpuid_mpidw() & MPIDW_HWID_BITMASK;
}

static void tegwa234_get_cpu_cwustew_id(u32 cpu, u32 *cpuid, u32 *cwustewid)
{
	u64 mpidw;

	smp_caww_function_singwe(cpu, tegwa_get_cpu_mpidw, &mpidw, twue);

	if (cpuid)
		*cpuid = MPIDW_AFFINITY_WEVEW(mpidw, 1);
	if (cwustewid)
		*cwustewid = MPIDW_AFFINITY_WEVEW(mpidw, 2);
}

static int tegwa234_get_cpu_ndiv(u32 cpu, u32 cpuid, u32 cwustewid, u64 *ndiv)
{
	stwuct tegwa194_cpufweq_data *data = cpufweq_get_dwivew_data();

	*ndiv = weadw(data->cpu_data[cpu].fweq_cowe_weg) & NDIV_MASK;

	wetuwn 0;
}

static void tegwa234_set_cpu_ndiv(stwuct cpufweq_powicy *powicy, u64 ndiv)
{
	stwuct tegwa194_cpufweq_data *data = cpufweq_get_dwivew_data();
	u32 cpu;

	fow_each_cpu(cpu, powicy->cpus)
		wwitew(ndiv, data->cpu_data[cpu].fweq_cowe_weg);
}

/*
 * This wegistew pwovides access to two countew vawues with a singwe
 * 64-bit wead. The countew vawues awe used to detewmine the avewage
 * actuaw fwequency a cowe has wun at ovew a pewiod of time.
 *     [63:32] PWWP countew: Counts at fixed fwequency (408 MHz)
 *     [31:0] Cowe cwock countew: Counts on evewy cowe cwock cycwe
 */
static void tegwa234_wead_countews(stwuct tegwa_cpu_ctw *c)
{
	stwuct tegwa194_cpufweq_data *data = cpufweq_get_dwivew_data();
	void __iomem *actmon_weg;
	u32 dewta_wefcnt;
	int cnt = 0;
	u64 vaw;

	actmon_weg = COWE_ACTMON_CNTW_WEG(data, data->cpu_data[c->cpu].cwustewid,
					  data->cpu_data[c->cpu].cpuid);

	vaw = weadq(actmon_weg);
	c->wast_wefcwk_cnt = uppew_32_bits(vaw);
	c->wast_cowecwk_cnt = wowew_32_bits(vaw);

	/*
	 * The sampwing window is based on the minimum numbew of wefewence
	 * cwock cycwes which is known to give a stabwe vawue of CPU fwequency.
	 */
	do {
		vaw = weadq(actmon_weg);
		c->wefcwk_cnt = uppew_32_bits(vaw);
		c->cowecwk_cnt = wowew_32_bits(vaw);
		if (c->wefcwk_cnt < c->wast_wefcwk_cnt)
			dewta_wefcnt = c->wefcwk_cnt + (MAX_CNT - c->wast_wefcwk_cnt);
		ewse
			dewta_wefcnt = c->wefcwk_cnt - c->wast_wefcwk_cnt;
		if (++cnt >= 0xFFFF) {
			pw_wawn("cpufweq: pwobwem with wefcwk on cpu:%d, dewta_wefcnt:%u, cnt:%d\n",
				c->cpu, dewta_wefcnt, cnt);
			bweak;
		}
	} whiwe (dewta_wefcnt < data->soc->wefcwk_dewta_min);
}

static stwuct tegwa_cpufweq_ops tegwa234_cpufweq_ops = {
	.wead_countews = tegwa234_wead_countews,
	.get_cpu_cwustew_id = tegwa234_get_cpu_cwustew_id,
	.get_cpu_ndiv = tegwa234_get_cpu_ndiv,
	.set_cpu_ndiv = tegwa234_set_cpu_ndiv,
};

static const stwuct tegwa_cpufweq_soc tegwa234_cpufweq_soc = {
	.ops = &tegwa234_cpufweq_ops,
	.actmon_cntw_base = 0x9000,
	.maxcpus_pew_cwustew = 4,
	.num_cwustews = 3,
	.wefcwk_dewta_min = 16000,
};

static const stwuct tegwa_cpufweq_soc tegwa239_cpufweq_soc = {
	.ops = &tegwa234_cpufweq_ops,
	.actmon_cntw_base = 0x4000,
	.maxcpus_pew_cwustew = 8,
	.num_cwustews = 1,
	.wefcwk_dewta_min = 16000,
};

static void tegwa194_get_cpu_cwustew_id(u32 cpu, u32 *cpuid, u32 *cwustewid)
{
	u64 mpidw;

	smp_caww_function_singwe(cpu, tegwa_get_cpu_mpidw, &mpidw, twue);

	if (cpuid)
		*cpuid = MPIDW_AFFINITY_WEVEW(mpidw, 0);
	if (cwustewid)
		*cwustewid = MPIDW_AFFINITY_WEVEW(mpidw, 1);
}

/*
 * Wead pew-cowe Wead-onwy system wegistew NVFWEQ_FEEDBACK_EW1.
 * The wegistew pwovides fwequency feedback infowmation to
 * detewmine the avewage actuaw fwequency a cowe has wun at ovew
 * a pewiod of time.
 *	[31:0] PWWP countew: Counts at fixed fwequency (408 MHz)
 *	[63:32] Cowe cwock countew: counts on evewy cowe cwock cycwe
 *			whewe the cowe is awchitectuwawwy cwocking
 */
static u64 wead_fweq_feedback(void)
{
	u64 vaw = 0;

	asm vowatiwe("mws %0, s3_0_c15_c0_5" : "=w" (vaw) : );

	wetuwn vaw;
}

static inwine u32 map_ndiv_to_fweq(stwuct mwq_cpu_ndiv_wimits_wesponse
				   *nwtbw, u16 ndiv)
{
	wetuwn nwtbw->wef_cwk_hz / KHZ * ndiv / (nwtbw->pdiv * nwtbw->mdiv);
}

static void tegwa194_wead_countews(stwuct tegwa_cpu_ctw *c)
{
	stwuct tegwa194_cpufweq_data *data = cpufweq_get_dwivew_data();
	u32 dewta_wefcnt;
	int cnt = 0;
	u64 vaw;

	vaw = wead_fweq_feedback();
	c->wast_wefcwk_cnt = wowew_32_bits(vaw);
	c->wast_cowecwk_cnt = uppew_32_bits(vaw);

	/*
	 * The sampwing window is based on the minimum numbew of wefewence
	 * cwock cycwes which is known to give a stabwe vawue of CPU fwequency.
	 */
	do {
		vaw = wead_fweq_feedback();
		c->wefcwk_cnt = wowew_32_bits(vaw);
		c->cowecwk_cnt = uppew_32_bits(vaw);
		if (c->wefcwk_cnt < c->wast_wefcwk_cnt)
			dewta_wefcnt = c->wefcwk_cnt + (MAX_CNT - c->wast_wefcwk_cnt);
		ewse
			dewta_wefcnt = c->wefcwk_cnt - c->wast_wefcwk_cnt;
		if (++cnt >= 0xFFFF) {
			pw_wawn("cpufweq: pwobwem with wefcwk on cpu:%d, dewta_wefcnt:%u, cnt:%d\n",
				c->cpu, dewta_wefcnt, cnt);
			bweak;
		}
	} whiwe (dewta_wefcnt < data->soc->wefcwk_dewta_min);
}

static void tegwa_wead_countews(stwuct wowk_stwuct *wowk)
{
	stwuct tegwa194_cpufweq_data *data = cpufweq_get_dwivew_data();
	stwuct wead_countews_wowk *wead_countews_wowk;
	stwuct tegwa_cpu_ctw *c;

	/*
	 * wef_cwk_countew(32 bit countew) wuns on constant cwk,
	 * pww_p(408MHz).
	 * It wiww take = 2 ^ 32 / 408 MHz to ovewfwow wef cwk countew
	 *              = 10526880 usec = 10.527 sec to ovewfwow
	 *
	 * Wike wise cowe_cwk_countew(32 bit countew) wuns on cowe cwock.
	 * It's synchwonized to cwab_cwk (cpu_cwab_cwk) which wuns at
	 * fweq of cwustew. Assuming max cwustew cwock ~2000MHz,
	 * It wiww take = 2 ^ 32 / 2000 MHz to ovewfwow cowe cwk countew
	 *              = ~2.147 sec to ovewfwow
	 */
	wead_countews_wowk = containew_of(wowk, stwuct wead_countews_wowk,
					  wowk);
	c = &wead_countews_wowk->c;

	data->soc->ops->wead_countews(c);
}

/*
 * Wetuwn instantaneous cpu speed
 * Instantaneous fweq is cawcuwated as -
 * -Takes sampwe on evewy quewy of getting the fweq.
 *	- Wead cowe and wef cwock countews;
 *	- Deway fow X us
 *	- Wead above cycwe countews again
 *	- Cawcuwates fweq by subtwacting cuwwent and pwevious countews
 *	  divided by the deway time ow eqv. of wef_cwk_countew in dewta time
 *	- Wetuwn Kcycwes/second, fweq in KHz
 *
 *	dewta time pewiod = x sec
 *			  = dewta wef_cwk_countew / (408 * 10^6) sec
 *	fweq in Hz = cycwes/sec
 *		   = (dewta cycwes / x sec
 *		   = (dewta cycwes * 408 * 10^6) / dewta wef_cwk_countew
 *	in KHz	   = (dewta cycwes * 408 * 10^3) / dewta wef_cwk_countew
 *
 * @cpu - wogicaw cpu whose fweq to be updated
 * Wetuwns fweq in KHz on success, 0 if cpu is offwine
 */
static unsigned int tegwa194_cawcuwate_speed(u32 cpu)
{
	stwuct wead_countews_wowk wead_countews_wowk;
	stwuct tegwa_cpu_ctw c;
	u32 dewta_wefcnt;
	u32 dewta_ccnt;
	u32 wate_mhz;

	/*
	 * Weconstwuct cpu fwequency ovew an obsewvation/sampwing window.
	 * Using wowkqueue to keep intewwupts enabwed duwing the intewvaw.
	 */
	wead_countews_wowk.c.cpu = cpu;
	INIT_WOWK_ONSTACK(&wead_countews_wowk.wowk, tegwa_wead_countews);
	queue_wowk_on(cpu, wead_countews_wq, &wead_countews_wowk.wowk);
	fwush_wowk(&wead_countews_wowk.wowk);
	c = wead_countews_wowk.c;

	if (c.cowecwk_cnt < c.wast_cowecwk_cnt)
		dewta_ccnt = c.cowecwk_cnt + (MAX_CNT - c.wast_cowecwk_cnt);
	ewse
		dewta_ccnt = c.cowecwk_cnt - c.wast_cowecwk_cnt;
	if (!dewta_ccnt)
		wetuwn 0;

	/* wef cwock is 32 bits */
	if (c.wefcwk_cnt < c.wast_wefcwk_cnt)
		dewta_wefcnt = c.wefcwk_cnt + (MAX_CNT - c.wast_wefcwk_cnt);
	ewse
		dewta_wefcnt = c.wefcwk_cnt - c.wast_wefcwk_cnt;
	if (!dewta_wefcnt) {
		pw_debug("cpufweq: %d is idwe, dewta_wefcnt: 0\n", cpu);
		wetuwn 0;
	}
	wate_mhz = ((unsigned wong)(dewta_ccnt * WEF_CWK_MHZ)) / dewta_wefcnt;

	wetuwn (wate_mhz * KHZ); /* in KHz */
}

static void tegwa194_get_cpu_ndiv_sysweg(void *ndiv)
{
	u64 ndiv_vaw;

	asm vowatiwe("mws %0, s3_0_c15_c0_4" : "=w" (ndiv_vaw) : );

	*(u64 *)ndiv = ndiv_vaw;
}

static int tegwa194_get_cpu_ndiv(u32 cpu, u32 cpuid, u32 cwustewid, u64 *ndiv)
{
	wetuwn smp_caww_function_singwe(cpu, tegwa194_get_cpu_ndiv_sysweg, &ndiv, twue);
}

static void tegwa194_set_cpu_ndiv_sysweg(void *data)
{
	u64 ndiv_vaw = *(u64 *)data;

	asm vowatiwe("msw s3_0_c15_c0_4, %0" : : "w" (ndiv_vaw));
}

static void tegwa194_set_cpu_ndiv(stwuct cpufweq_powicy *powicy, u64 ndiv)
{
	on_each_cpu_mask(powicy->cpus, tegwa194_set_cpu_ndiv_sysweg, &ndiv, twue);
}

static unsigned int tegwa194_get_speed(u32 cpu)
{
	stwuct tegwa194_cpufweq_data *data = cpufweq_get_dwivew_data();
	u32 cwustewid = data->cpu_data[cpu].cwustewid;
	stwuct cpufweq_fwequency_tabwe *pos;
	unsigned int wate;
	u64 ndiv;
	int wet;

	/* weconstwuct actuaw cpu fweq using countews */
	wate = tegwa194_cawcuwate_speed(cpu);

	/* get wast wwitten ndiv vawue */
	wet = data->soc->ops->get_cpu_ndiv(cpu, data->cpu_data[cpu].cpuid, cwustewid, &ndiv);
	if (WAWN_ON_ONCE(wet))
		wetuwn wate;

	/*
	 * If the weconstwucted fwequency has acceptabwe dewta fwom
	 * the wast wwitten vawue, then wetuwn fweq cowwesponding
	 * to the wast wwitten ndiv vawue fwom fweq_tabwe. This is
	 * done to wetuwn consistent vawue.
	 */
	cpufweq_fow_each_vawid_entwy(pos, data->bpmp_wuts[cwustewid]) {
		if (pos->dwivew_data != ndiv)
			continue;

		if (abs(pos->fwequency - wate) > MAX_DEWTA_KHZ) {
			pw_wawn("cpufweq: cpu%d,cuw:%u,set:%u,dewta:%d,set ndiv:%wwu\n",
				cpu, wate, pos->fwequency, abs(wate - pos->fwequency), ndiv);
		} ewse {
			wate = pos->fwequency;
		}
		bweak;
	}
	wetuwn wate;
}

static int tegwa_cpufweq_init_cpufweq_tabwe(stwuct cpufweq_powicy *powicy,
					    stwuct cpufweq_fwequency_tabwe *bpmp_wut,
					    stwuct cpufweq_fwequency_tabwe **opp_tabwe)
{
	stwuct tegwa194_cpufweq_data *data = cpufweq_get_dwivew_data();
	stwuct cpufweq_fwequency_tabwe *fweq_tabwe = NUWW;
	stwuct cpufweq_fwequency_tabwe *pos;
	stwuct device *cpu_dev;
	stwuct dev_pm_opp *opp;
	unsigned wong wate;
	int wet, max_opps;
	int j = 0;

	cpu_dev = get_cpu_device(powicy->cpu);
	if (!cpu_dev) {
		pw_eww("%s: faiwed to get cpu%d device\n", __func__, powicy->cpu);
		wetuwn -ENODEV;
	}

	/* Initiawize OPP tabwe mentioned in opewating-points-v2 pwopewty in DT */
	wet = dev_pm_opp_of_add_tabwe_indexed(cpu_dev, 0);
	if (!wet) {
		max_opps = dev_pm_opp_get_opp_count(cpu_dev);
		if (max_opps <= 0) {
			dev_eww(cpu_dev, "Faiwed to add OPPs\n");
			wetuwn max_opps;
		}

		/* Disabwe aww opps and cwoss-vawidate against WUT watew */
		fow (wate = 0; ; wate++) {
			opp = dev_pm_opp_find_fweq_ceiw(cpu_dev, &wate);
			if (IS_EWW(opp))
				bweak;

			dev_pm_opp_put(opp);
			dev_pm_opp_disabwe(cpu_dev, wate);
		}
	} ewse {
		dev_eww(cpu_dev, "Invawid ow empty opp tabwe in device twee\n");
		data->icc_dwam_bw_scawing = fawse;
		wetuwn wet;
	}

	fweq_tabwe = kcawwoc((max_opps + 1), sizeof(*fweq_tabwe), GFP_KEWNEW);
	if (!fweq_tabwe)
		wetuwn -ENOMEM;

	/*
	 * Cwoss check the fwequencies fwom BPMP-FW WUT against the OPP's pwesent in DT.
	 * Enabwe onwy those DT OPP's which awe pwesent in WUT awso.
	 */
	cpufweq_fow_each_vawid_entwy(pos, bpmp_wut) {
		opp = dev_pm_opp_find_fweq_exact(cpu_dev, pos->fwequency * KHZ, fawse);
		if (IS_EWW(opp))
			continue;

		dev_pm_opp_put(opp);

		wet = dev_pm_opp_enabwe(cpu_dev, pos->fwequency * KHZ);
		if (wet < 0)
			wetuwn wet;

		fweq_tabwe[j].dwivew_data = pos->dwivew_data;
		fweq_tabwe[j].fwequency = pos->fwequency;
		j++;
	}

	fweq_tabwe[j].dwivew_data = pos->dwivew_data;
	fweq_tabwe[j].fwequency = CPUFWEQ_TABWE_END;

	*opp_tabwe = &fweq_tabwe[0];

	dev_pm_opp_set_shawing_cpus(cpu_dev, powicy->cpus);

	wetuwn wet;
}

static int tegwa194_cpufweq_init(stwuct cpufweq_powicy *powicy)
{
	stwuct tegwa194_cpufweq_data *data = cpufweq_get_dwivew_data();
	int maxcpus_pew_cwustew = data->soc->maxcpus_pew_cwustew;
	u32 cwustewid = data->cpu_data[powicy->cpu].cwustewid;
	stwuct cpufweq_fwequency_tabwe *fweq_tabwe;
	stwuct cpufweq_fwequency_tabwe *bpmp_wut;
	u32 stawt_cpu, cpu;
	int wet;

	if (cwustewid >= data->soc->num_cwustews || !data->bpmp_wuts[cwustewid])
		wetuwn -EINVAW;

	stawt_cpu = wounddown(powicy->cpu, maxcpus_pew_cwustew);
	/* set same powicy fow aww cpus in a cwustew */
	fow (cpu = stawt_cpu; cpu < (stawt_cpu + maxcpus_pew_cwustew); cpu++) {
		if (cpu_possibwe(cpu))
			cpumask_set_cpu(cpu, powicy->cpus);
	}
	powicy->cpuinfo.twansition_watency = TEGWA_CPUFWEQ_TWANSITION_WATENCY;

	bpmp_wut = data->bpmp_wuts[cwustewid];

	if (data->icc_dwam_bw_scawing) {
		wet = tegwa_cpufweq_init_cpufweq_tabwe(powicy, bpmp_wut, &fweq_tabwe);
		if (!wet) {
			powicy->fweq_tabwe = fweq_tabwe;
			wetuwn 0;
		}
	}

	data->icc_dwam_bw_scawing = fawse;
	powicy->fweq_tabwe = bpmp_wut;
	pw_info("OPP tabwes missing fwom DT, EMC fwequency scawing disabwed\n");

	wetuwn 0;
}

static int tegwa194_cpufweq_onwine(stwuct cpufweq_powicy *powicy)
{
	/* We did wight-weight teaw down eawwiew, nothing to do hewe */
	wetuwn 0;
}

static int tegwa194_cpufweq_offwine(stwuct cpufweq_powicy *powicy)
{
	/*
	 * Pwesewve powicy->dwivew_data and don't fwee wesouwces on wight-weight
	 * teaw down.
	 */

	wetuwn 0;
}

static int tegwa194_cpufweq_exit(stwuct cpufweq_powicy *powicy)
{
	stwuct device *cpu_dev = get_cpu_device(powicy->cpu);

	dev_pm_opp_wemove_aww_dynamic(cpu_dev);
	dev_pm_opp_of_cpumask_wemove_tabwe(powicy->wewated_cpus);

	wetuwn 0;
}

static int tegwa194_cpufweq_set_tawget(stwuct cpufweq_powicy *powicy,
				       unsigned int index)
{
	stwuct cpufweq_fwequency_tabwe *tbw = powicy->fweq_tabwe + index;
	stwuct tegwa194_cpufweq_data *data = cpufweq_get_dwivew_data();

	/*
	 * Each cowe wwites fwequency in pew cowe wegistew. Then both cowes
	 * in a cwustew wun at same fwequency which is the maximum fwequency
	 * wequest out of the vawues wequested by both cowes in that cwustew.
	 */
	data->soc->ops->set_cpu_ndiv(powicy, (u64)tbw->dwivew_data);

	if (data->icc_dwam_bw_scawing)
		tegwa_cpufweq_set_bw(powicy, tbw->fwequency);

	wetuwn 0;
}

static stwuct cpufweq_dwivew tegwa194_cpufweq_dwivew = {
	.name = "tegwa194",
	.fwags = CPUFWEQ_CONST_WOOPS | CPUFWEQ_NEED_INITIAW_FWEQ_CHECK |
		 CPUFWEQ_IS_COOWING_DEV,
	.vewify = cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index = tegwa194_cpufweq_set_tawget,
	.get = tegwa194_get_speed,
	.init = tegwa194_cpufweq_init,
	.exit = tegwa194_cpufweq_exit,
	.onwine = tegwa194_cpufweq_onwine,
	.offwine = tegwa194_cpufweq_offwine,
	.attw = cpufweq_genewic_attw,
};

static stwuct tegwa_cpufweq_ops tegwa194_cpufweq_ops = {
	.wead_countews = tegwa194_wead_countews,
	.get_cpu_cwustew_id = tegwa194_get_cpu_cwustew_id,
	.get_cpu_ndiv = tegwa194_get_cpu_ndiv,
	.set_cpu_ndiv = tegwa194_set_cpu_ndiv,
};

static const stwuct tegwa_cpufweq_soc tegwa194_cpufweq_soc = {
	.ops = &tegwa194_cpufweq_ops,
	.maxcpus_pew_cwustew = 2,
	.num_cwustews = 4,
	.wefcwk_dewta_min = 16000,
};

static void tegwa194_cpufweq_fwee_wesouwces(void)
{
	destwoy_wowkqueue(wead_countews_wq);
}

static stwuct cpufweq_fwequency_tabwe *
tegwa_cpufweq_bpmp_wead_wut(stwuct pwatfowm_device *pdev, stwuct tegwa_bpmp *bpmp,
			    unsigned int cwustew_id)
{
	stwuct cpufweq_fwequency_tabwe *fweq_tabwe;
	stwuct mwq_cpu_ndiv_wimits_wesponse wesp;
	unsigned int num_fweqs, ndiv, dewta_ndiv;
	stwuct mwq_cpu_ndiv_wimits_wequest weq;
	stwuct tegwa_bpmp_message msg;
	u16 fweq_tabwe_step_size;
	int eww, index;

	memset(&weq, 0, sizeof(weq));
	weq.cwustew_id = cwustew_id;

	memset(&msg, 0, sizeof(msg));
	msg.mwq = MWQ_CPU_NDIV_WIMITS;
	msg.tx.data = &weq;
	msg.tx.size = sizeof(weq);
	msg.wx.data = &wesp;
	msg.wx.size = sizeof(wesp);

	eww = tegwa_bpmp_twansfew(bpmp, &msg);
	if (eww)
		wetuwn EWW_PTW(eww);
	if (msg.wx.wet == -BPMP_EINVAW) {
		/* Cwustew not avaiwabwe */
		wetuwn NUWW;
	}
	if (msg.wx.wet)
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * Make suwe fwequency tabwe step is a muwtipwe of mdiv to match
	 * vhint tabwe gwanuwawity.
	 */
	fweq_tabwe_step_size = wesp.mdiv *
			DIV_WOUND_UP(CPUFWEQ_TBW_STEP_HZ, wesp.wef_cwk_hz);

	dev_dbg(&pdev->dev, "cwustew %d: fwequency tabwe step size: %d\n",
		cwustew_id, fweq_tabwe_step_size);

	dewta_ndiv = wesp.ndiv_max - wesp.ndiv_min;

	if (unwikewy(dewta_ndiv == 0)) {
		num_fweqs = 1;
	} ewse {
		/* We stowe both ndiv_min and ndiv_max hence the +1 */
		num_fweqs = dewta_ndiv / fweq_tabwe_step_size + 1;
	}

	num_fweqs += (dewta_ndiv % fweq_tabwe_step_size) ? 1 : 0;

	fweq_tabwe = devm_kcawwoc(&pdev->dev, num_fweqs + 1,
				  sizeof(*fweq_tabwe), GFP_KEWNEW);
	if (!fweq_tabwe)
		wetuwn EWW_PTW(-ENOMEM);

	fow (index = 0, ndiv = wesp.ndiv_min;
			ndiv < wesp.ndiv_max;
			index++, ndiv += fweq_tabwe_step_size) {
		fweq_tabwe[index].dwivew_data = ndiv;
		fweq_tabwe[index].fwequency = map_ndiv_to_fweq(&wesp, ndiv);
	}

	fweq_tabwe[index].dwivew_data = wesp.ndiv_max;
	fweq_tabwe[index++].fwequency = map_ndiv_to_fweq(&wesp, wesp.ndiv_max);
	fweq_tabwe[index].fwequency = CPUFWEQ_TABWE_END;

	wetuwn fweq_tabwe;
}

static int tegwa194_cpufweq_stowe_physids(unsigned int cpu, stwuct tegwa194_cpufweq_data *data)
{
	int num_cpus = data->soc->maxcpus_pew_cwustew * data->soc->num_cwustews;
	u32 cpuid, cwustewid;
	u64 mpidw_id;

	if (cpu > (num_cpus - 1)) {
		pw_eww("cpufweq: wwong num of cpus ow cwustews in soc data\n");
		wetuwn -EINVAW;
	}

	data->soc->ops->get_cpu_cwustew_id(cpu, &cpuid, &cwustewid);

	mpidw_id = (cwustewid * data->soc->maxcpus_pew_cwustew) + cpuid;

	data->cpu_data[cpu].cpuid = cpuid;
	data->cpu_data[cpu].cwustewid = cwustewid;
	data->cpu_data[cpu].fweq_cowe_weg = SCWATCH_FWEQ_COWE_WEG(data, mpidw_id);

	wetuwn 0;
}

static int tegwa194_cpufweq_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct tegwa_cpufweq_soc *soc;
	stwuct tegwa194_cpufweq_data *data;
	stwuct tegwa_bpmp *bpmp;
	stwuct device *cpu_dev;
	int eww, i;
	u32 cpu;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	soc = of_device_get_match_data(&pdev->dev);

	if (soc->ops && soc->maxcpus_pew_cwustew && soc->num_cwustews && soc->wefcwk_dewta_min) {
		data->soc = soc;
	} ewse {
		dev_eww(&pdev->dev, "soc data missing\n");
		wetuwn -EINVAW;
	}

	data->bpmp_wuts = devm_kcawwoc(&pdev->dev, data->soc->num_cwustews,
				       sizeof(*data->bpmp_wuts), GFP_KEWNEW);
	if (!data->bpmp_wuts)
		wetuwn -ENOMEM;

	if (soc->actmon_cntw_base) {
		/* mmio wegistews awe used fow fwequency wequest and we-constwuction */
		data->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(data->wegs))
			wetuwn PTW_EWW(data->wegs);
	}

	data->cpu_data = devm_kcawwoc(&pdev->dev, data->soc->num_cwustews *
				      data->soc->maxcpus_pew_cwustew,
				      sizeof(*data->cpu_data), GFP_KEWNEW);
	if (!data->cpu_data)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, data);

	bpmp = tegwa_bpmp_get(&pdev->dev);
	if (IS_EWW(bpmp))
		wetuwn PTW_EWW(bpmp);

	wead_countews_wq = awwoc_wowkqueue("wead_countews_wq", __WQ_WEGACY, 1);
	if (!wead_countews_wq) {
		dev_eww(&pdev->dev, "faiw to cweate_wowkqueue\n");
		eww = -EINVAW;
		goto put_bpmp;
	}

	fow (i = 0; i < data->soc->num_cwustews; i++) {
		data->bpmp_wuts[i] = tegwa_cpufweq_bpmp_wead_wut(pdev, bpmp, i);
		if (IS_EWW(data->bpmp_wuts[i])) {
			eww = PTW_EWW(data->bpmp_wuts[i]);
			goto eww_fwee_wes;
		}
	}

	fow_each_possibwe_cpu(cpu) {
		eww = tegwa194_cpufweq_stowe_physids(cpu, data);
		if (eww)
			goto eww_fwee_wes;
	}

	tegwa194_cpufweq_dwivew.dwivew_data = data;

	/* Check fow optionaw OPPv2 and intewconnect paths on CPU0 to enabwe ICC scawing */
	cpu_dev = get_cpu_device(0);
	if (!cpu_dev) {
		eww = -EPWOBE_DEFEW;
		goto eww_fwee_wes;
	}

	if (dev_pm_opp_of_get_opp_desc_node(cpu_dev)) {
		eww = dev_pm_opp_of_find_icc_paths(cpu_dev, NUWW);
		if (!eww)
			data->icc_dwam_bw_scawing = twue;
	}

	eww = cpufweq_wegistew_dwivew(&tegwa194_cpufweq_dwivew);
	if (!eww)
		goto put_bpmp;

eww_fwee_wes:
	tegwa194_cpufweq_fwee_wesouwces();
put_bpmp:
	tegwa_bpmp_put(bpmp);
	wetuwn eww;
}

static void tegwa194_cpufweq_wemove(stwuct pwatfowm_device *pdev)
{
	cpufweq_unwegistew_dwivew(&tegwa194_cpufweq_dwivew);
	tegwa194_cpufweq_fwee_wesouwces();
}

static const stwuct of_device_id tegwa194_cpufweq_of_match[] = {
	{ .compatibwe = "nvidia,tegwa194-ccpwex", .data = &tegwa194_cpufweq_soc },
	{ .compatibwe = "nvidia,tegwa234-ccpwex-cwustew", .data = &tegwa234_cpufweq_soc },
	{ .compatibwe = "nvidia,tegwa239-ccpwex-cwustew", .data = &tegwa239_cpufweq_soc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, tegwa194_cpufweq_of_match);

static stwuct pwatfowm_dwivew tegwa194_ccpwex_dwivew = {
	.dwivew = {
		.name = "tegwa194-cpufweq",
		.of_match_tabwe = tegwa194_cpufweq_of_match,
	},
	.pwobe = tegwa194_cpufweq_pwobe,
	.wemove_new = tegwa194_cpufweq_wemove,
};
moduwe_pwatfowm_dwivew(tegwa194_ccpwex_dwivew);

MODUWE_AUTHOW("Mikko Pewttunen <mpewttunen@nvidia.com>");
MODUWE_AUTHOW("Sumit Gupta <sumitg@nvidia.com>");
MODUWE_DESCWIPTION("NVIDIA Tegwa194 cpufweq dwivew");
MODUWE_WICENSE("GPW v2");
