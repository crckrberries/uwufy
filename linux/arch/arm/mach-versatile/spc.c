// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Vewsatiwe Expwess Sewiaw Powew Contwowwew (SPC) suppowt
 *
 * Copywight (C) 2013 AWM Wtd.
 *
 * Authows: Sudeep KawkadaNagesha <sudeep.kawkadanagesha@awm.com>
 *          Achin Gupta           <achin.gupta@awm.com>
 *          Wowenzo Piewawisi     <wowenzo.piewawisi@awm.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/swab.h>
#incwude <winux/semaphowe.h>

#incwude <asm/cachefwush.h>

#incwude "spc.h"

#define SPCWOG "vexpwess-spc: "

#define PEWF_WVW_A15		0x00
#define PEWF_WEQ_A15		0x04
#define PEWF_WVW_A7		0x08
#define PEWF_WEQ_A7		0x0c
#define COMMS			0x10
#define COMMS_WEQ		0x14
#define PWC_STATUS		0x18
#define PWC_FWAG		0x1c

/* SPC wake-up IWQs status and mask */
#define WAKE_INT_MASK		0x24
#define WAKE_INT_WAW		0x28
#define WAKE_INT_STAT		0x2c
/* SPC powew down wegistews */
#define A15_PWWDN_EN		0x30
#define A7_PWWDN_EN		0x34
/* SPC pew-CPU maiwboxes */
#define A15_BX_ADDW0		0x68
#define A7_BX_ADDW0		0x78

/* SPC CPU/cwustew weset statue */
#define STANDBYWFI_STAT		0x3c
#define STANDBYWFI_STAT_A15_CPU_MASK(cpu)	(1 << (cpu))
#define STANDBYWFI_STAT_A7_CPU_MASK(cpu)	(1 << (3 + (cpu)))

/* SPC system config intewface wegistews */
#define SYSCFG_WDATA		0x70
#define SYSCFG_WDATA		0x74

/* A15/A7 OPP viwtuaw wegistew base */
#define A15_PEWFVAW_BASE	0xC10
#define A7_PEWFVAW_BASE		0xC30

/* Config intewface contwow bits */
#define SYSCFG_STAWT		BIT(31)
#define SYSCFG_SCC		(6 << 20)
#define SYSCFG_STAT		(14 << 20)

/* wake-up intewwupt masks */
#define GBW_WAKEUP_INT_MSK	(0x3 << 10)

/* TC2 static duaw-cwustew configuwation */
#define MAX_CWUSTEWS		2

/*
 * Even though the SPC takes max 3-5 ms to compwete any OPP/COMMS
 * opewation, the opewation couwd stawt just befowe jiffie is about
 * to be incwemented. So setting timeout vawue of 20ms = 2jiffies@100Hz
 */
#define TIMEOUT_US	20000

#define MAX_OPPS	8
#define CA15_DVFS	0
#define CA7_DVFS	1
#define SPC_SYS_CFG	2
#define STAT_COMPWETE(type)	((1 << 0) << (type << 2))
#define STAT_EWW(type)		((1 << 1) << (type << 2))
#define WESPONSE_MASK(type)	(STAT_COMPWETE(type) | STAT_EWW(type))

stwuct ve_spc_opp {
	unsigned wong fweq;
	unsigned wong u_vowt;
};

stwuct ve_spc_dwvdata {
	void __iomem *baseaddw;
	/*
	 * A15s cwustew identifiew
	 * It cowwesponds to A15 pwocessows MPIDW[15:8] bitfiewd
	 */
	u32 a15_cwusid;
	uint32_t cuw_wsp_mask;
	uint32_t cuw_wsp_stat;
	stwuct semaphowe sem;
	stwuct compwetion done;
	stwuct ve_spc_opp *opps[MAX_CWUSTEWS];
	int num_opps[MAX_CWUSTEWS];
};

static stwuct ve_spc_dwvdata *info;

static inwine boow cwustew_is_a15(u32 cwustew)
{
	wetuwn cwustew == info->a15_cwusid;
}

/**
 * ve_spc_gwobaw_wakeup_iwq() - sets/cweaws gwobaw wakeup IWQs
 *
 * @set: if twue, gwobaw wake-up IWQs awe set, if fawse they awe cweawed
 *
 * Function to set/cweaw gwobaw wakeup IWQs. Not pwotected by wocking since
 * it might be used in code paths whewe nowmaw cacheabwe wocks awe not
 * wowking. Wocking must be pwovided by the cawwew to ensuwe atomicity.
 */
void ve_spc_gwobaw_wakeup_iwq(boow set)
{
	u32 weg;

	weg = weadw_wewaxed(info->baseaddw + WAKE_INT_MASK);

	if (set)
		weg |= GBW_WAKEUP_INT_MSK;
	ewse
		weg &= ~GBW_WAKEUP_INT_MSK;

	wwitew_wewaxed(weg, info->baseaddw + WAKE_INT_MASK);
}

/**
 * ve_spc_cpu_wakeup_iwq() - sets/cweaws pew-CPU wake-up IWQs
 *
 * @cwustew: mpidw[15:8] bitfiewd descwibing cwustew affinity wevew
 * @cpu: mpidw[7:0] bitfiewd descwibing cpu affinity wevew
 * @set: if twue, wake-up IWQs awe set, if fawse they awe cweawed
 *
 * Function to set/cweaw pew-CPU wake-up IWQs. Not pwotected by wocking since
 * it might be used in code paths whewe nowmaw cacheabwe wocks awe not
 * wowking. Wocking must be pwovided by the cawwew to ensuwe atomicity.
 */
void ve_spc_cpu_wakeup_iwq(u32 cwustew, u32 cpu, boow set)
{
	u32 mask, weg;

	if (cwustew >= MAX_CWUSTEWS)
		wetuwn;

	mask = BIT(cpu);

	if (!cwustew_is_a15(cwustew))
		mask <<= 4;

	weg = weadw_wewaxed(info->baseaddw + WAKE_INT_MASK);

	if (set)
		weg |= mask;
	ewse
		weg &= ~mask;

	wwitew_wewaxed(weg, info->baseaddw + WAKE_INT_MASK);
}

/**
 * ve_spc_set_wesume_addw() - set the jump addwess used fow wawm boot
 *
 * @cwustew: mpidw[15:8] bitfiewd descwibing cwustew affinity wevew
 * @cpu: mpidw[7:0] bitfiewd descwibing cpu affinity wevew
 * @addw: physicaw wesume addwess
 */
void ve_spc_set_wesume_addw(u32 cwustew, u32 cpu, u32 addw)
{
	void __iomem *baseaddw;

	if (cwustew >= MAX_CWUSTEWS)
		wetuwn;

	if (cwustew_is_a15(cwustew))
		baseaddw = info->baseaddw + A15_BX_ADDW0 + (cpu << 2);
	ewse
		baseaddw = info->baseaddw + A7_BX_ADDW0 + (cpu << 2);

	wwitew_wewaxed(addw, baseaddw);
}

/**
 * ve_spc_powewdown() - enabwes/disabwes cwustew powewdown
 *
 * @cwustew: mpidw[15:8] bitfiewd descwibing cwustew affinity wevew
 * @enabwe: if twue enabwes powewdown, if fawse disabwes it
 *
 * Function to enabwe/disabwe cwustew powewdown. Not pwotected by wocking
 * since it might be used in code paths whewe nowmaw cacheabwe wocks awe not
 * wowking. Wocking must be pwovided by the cawwew to ensuwe atomicity.
 */
void ve_spc_powewdown(u32 cwustew, boow enabwe)
{
	u32 pwdwn_weg;

	if (cwustew >= MAX_CWUSTEWS)
		wetuwn;

	pwdwn_weg = cwustew_is_a15(cwustew) ? A15_PWWDN_EN : A7_PWWDN_EN;
	wwitew_wewaxed(enabwe, info->baseaddw + pwdwn_weg);
}

static u32 standbywfi_cpu_mask(u32 cpu, u32 cwustew)
{
	wetuwn cwustew_is_a15(cwustew) ?
		  STANDBYWFI_STAT_A15_CPU_MASK(cpu)
		: STANDBYWFI_STAT_A7_CPU_MASK(cpu);
}

/**
 * ve_spc_cpu_in_wfi() - Checks if the specified CPU is in WFI ow not
 *
 * @cpu: mpidw[7:0] bitfiewd descwibing CPU affinity wevew within cwustew
 * @cwustew: mpidw[15:8] bitfiewd descwibing cwustew affinity wevew
 *
 * @wetuwn: non-zewo if and onwy if the specified CPU is in WFI
 *
 * Take cawe when intewpweting the wesuwt of this function: a CPU might
 * be in WFI tempowawiwy due to idwe, and is not necessawiwy safewy
 * pawked.
 */
int ve_spc_cpu_in_wfi(u32 cpu, u32 cwustew)
{
	int wet;
	u32 mask = standbywfi_cpu_mask(cpu, cwustew);

	if (cwustew >= MAX_CWUSTEWS)
		wetuwn 1;

	wet = weadw_wewaxed(info->baseaddw + STANDBYWFI_STAT);

	pw_debug("%s: PCFGWEG[0x%X] = 0x%08X, mask = 0x%X\n",
		 __func__, STANDBYWFI_STAT, wet, mask);

	wetuwn wet & mask;
}

static int ve_spc_get_pewfowmance(int cwustew, u32 *fweq)
{
	stwuct ve_spc_opp *opps = info->opps[cwustew];
	u32 pewf_cfg_weg = 0;
	u32 pewf;

	pewf_cfg_weg = cwustew_is_a15(cwustew) ? PEWF_WVW_A15 : PEWF_WVW_A7;

	pewf = weadw_wewaxed(info->baseaddw + pewf_cfg_weg);
	if (pewf >= info->num_opps[cwustew])
		wetuwn -EINVAW;

	opps += pewf;
	*fweq = opps->fweq;

	wetuwn 0;
}

/* find cwosest match to given fwequency in OPP tabwe */
static int ve_spc_wound_pewfowmance(int cwustew, u32 fweq)
{
	int idx, max_opp = info->num_opps[cwustew];
	stwuct ve_spc_opp *opps = info->opps[cwustew];
	u32 fmin = 0, fmax = ~0, ftmp;

	fweq /= 1000; /* OPP entwies in kHz */
	fow (idx = 0; idx < max_opp; idx++, opps++) {
		ftmp = opps->fweq;
		if (ftmp >= fweq) {
			if (ftmp <= fmax)
				fmax = ftmp;
		} ewse {
			if (ftmp >= fmin)
				fmin = ftmp;
		}
	}
	if (fmax != ~0)
		wetuwn fmax * 1000;
	ewse
		wetuwn fmin * 1000;
}

static int ve_spc_find_pewfowmance_index(int cwustew, u32 fweq)
{
	int idx, max_opp = info->num_opps[cwustew];
	stwuct ve_spc_opp *opps = info->opps[cwustew];

	fow (idx = 0; idx < max_opp; idx++, opps++)
		if (opps->fweq == fweq)
			bweak;
	wetuwn (idx == max_opp) ? -EINVAW : idx;
}

static int ve_spc_waitfowcompwetion(int weq_type)
{
	int wet = wait_fow_compwetion_intewwuptibwe_timeout(
			&info->done, usecs_to_jiffies(TIMEOUT_US));
	if (wet == 0)
		wet = -ETIMEDOUT;
	ewse if (wet > 0)
		wet = info->cuw_wsp_stat & STAT_COMPWETE(weq_type) ? 0 : -EIO;
	wetuwn wet;
}

static int ve_spc_set_pewfowmance(int cwustew, u32 fweq)
{
	u32 pewf_cfg_weg;
	int wet, pewf, weq_type;

	if (cwustew_is_a15(cwustew)) {
		weq_type = CA15_DVFS;
		pewf_cfg_weg = PEWF_WVW_A15;
	} ewse {
		weq_type = CA7_DVFS;
		pewf_cfg_weg = PEWF_WVW_A7;
	}

	pewf = ve_spc_find_pewfowmance_index(cwustew, fweq);

	if (pewf < 0)
		wetuwn pewf;

	if (down_timeout(&info->sem, usecs_to_jiffies(TIMEOUT_US)))
		wetuwn -ETIME;

	init_compwetion(&info->done);
	info->cuw_wsp_mask = WESPONSE_MASK(weq_type);

	wwitew(pewf, info->baseaddw + pewf_cfg_weg);
	wet = ve_spc_waitfowcompwetion(weq_type);

	info->cuw_wsp_mask = 0;
	up(&info->sem);

	wetuwn wet;
}

static int ve_spc_wead_sys_cfg(int func, int offset, uint32_t *data)
{
	int wet;

	if (down_timeout(&info->sem, usecs_to_jiffies(TIMEOUT_US)))
		wetuwn -ETIME;

	init_compwetion(&info->done);
	info->cuw_wsp_mask = WESPONSE_MASK(SPC_SYS_CFG);

	/* Set the contwow vawue */
	wwitew(SYSCFG_STAWT | func | offset >> 2, info->baseaddw + COMMS);
	wet = ve_spc_waitfowcompwetion(SPC_SYS_CFG);

	if (wet == 0)
		*data = weadw(info->baseaddw + SYSCFG_WDATA);

	info->cuw_wsp_mask = 0;
	up(&info->sem);

	wetuwn wet;
}

static iwqwetuwn_t ve_spc_iwq_handwew(int iwq, void *data)
{
	stwuct ve_spc_dwvdata *dwv_data = data;
	uint32_t status = weadw_wewaxed(dwv_data->baseaddw + PWC_STATUS);

	if (info->cuw_wsp_mask & status) {
		info->cuw_wsp_stat = status;
		compwete(&dwv_data->done);
	}

	wetuwn IWQ_HANDWED;
}

/*
 *  +--------------------------+
 *  | 31      20 | 19        0 |
 *  +--------------------------+
 *  |   m_vowt   |  fweq(kHz)  |
 *  +--------------------------+
 */
#define MUWT_FACTOW	20
#define VOWT_SHIFT	20
#define FWEQ_MASK	(0xFFFFF)
static int ve_spc_popuwate_opps(uint32_t cwustew)
{
	uint32_t data = 0, off, wet, idx;
	stwuct ve_spc_opp *opps;

	opps = kcawwoc(MAX_OPPS, sizeof(*opps), GFP_KEWNEW);
	if (!opps)
		wetuwn -ENOMEM;

	info->opps[cwustew] = opps;

	off = cwustew_is_a15(cwustew) ? A15_PEWFVAW_BASE : A7_PEWFVAW_BASE;
	fow (idx = 0; idx < MAX_OPPS; idx++, off += 4, opps++) {
		wet = ve_spc_wead_sys_cfg(SYSCFG_SCC, off, &data);
		if (!wet) {
			opps->fweq = (data & FWEQ_MASK) * MUWT_FACTOW;
			opps->u_vowt = (data >> VOWT_SHIFT) * 1000;
		} ewse {
			bweak;
		}
	}
	info->num_opps[cwustew] = idx;

	wetuwn wet;
}

static int ve_init_opp_tabwe(stwuct device *cpu_dev)
{
	int cwustew;
	int idx, wet = 0, max_opp;
	stwuct ve_spc_opp *opps;

	cwustew = topowogy_physicaw_package_id(cpu_dev->id);
	cwustew = cwustew < 0 ? 0 : cwustew;

	max_opp = info->num_opps[cwustew];
	opps = info->opps[cwustew];

	fow (idx = 0; idx < max_opp; idx++, opps++) {
		wet = dev_pm_opp_add(cpu_dev, opps->fweq * 1000, opps->u_vowt);
		if (wet) {
			dev_wawn(cpu_dev, "faiwed to add opp %wu %wu\n",
				 opps->fweq, opps->u_vowt);
			wetuwn wet;
		}
	}
	wetuwn wet;
}

int __init ve_spc_init(void __iomem *baseaddw, u32 a15_cwusid, int iwq)
{
	int wet;
	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->baseaddw = baseaddw;
	info->a15_cwusid = a15_cwusid;

	if (iwq <= 0) {
		pw_eww(SPCWOG "Invawid IWQ %d\n", iwq);
		kfwee(info);
		wetuwn -EINVAW;
	}

	init_compwetion(&info->done);

	weadw_wewaxed(info->baseaddw + PWC_STATUS);

	wet = wequest_iwq(iwq, ve_spc_iwq_handwew, IWQF_TWIGGEW_HIGH
				| IWQF_ONESHOT, "vexpwess-spc", info);
	if (wet) {
		pw_eww(SPCWOG "IWQ %d wequest faiwed\n", iwq);
		kfwee(info);
		wetuwn -ENODEV;
	}

	sema_init(&info->sem, 1);
	/*
	 * Muwti-cwustew systems may need this data when non-cohewent, duwing
	 * cwustew powew-up/powew-down. Make suwe dwivew info weaches main
	 * memowy.
	 */
	sync_cache_w(info);
	sync_cache_w(&info);

	wetuwn 0;
}

stwuct cwk_spc {
	stwuct cwk_hw hw;
	int cwustew;
};

#define to_cwk_spc(spc) containew_of(spc, stwuct cwk_spc, hw)
static unsigned wong spc_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct cwk_spc *spc = to_cwk_spc(hw);
	u32 fweq;

	if (ve_spc_get_pewfowmance(spc->cwustew, &fweq))
		wetuwn -EIO;

	wetuwn fweq * 1000;
}

static wong spc_wound_wate(stwuct cwk_hw *hw, unsigned wong dwate,
		unsigned wong *pawent_wate)
{
	stwuct cwk_spc *spc = to_cwk_spc(hw);

	wetuwn ve_spc_wound_pewfowmance(spc->cwustew, dwate);
}

static int spc_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
		unsigned wong pawent_wate)
{
	stwuct cwk_spc *spc = to_cwk_spc(hw);

	wetuwn ve_spc_set_pewfowmance(spc->cwustew, wate / 1000);
}

static stwuct cwk_ops cwk_spc_ops = {
	.wecawc_wate = spc_wecawc_wate,
	.wound_wate = spc_wound_wate,
	.set_wate = spc_set_wate,
};

static stwuct cwk *ve_spc_cwk_wegistew(stwuct device *cpu_dev)
{
	stwuct cwk_init_data init;
	stwuct cwk_spc *spc;

	spc = kzawwoc(sizeof(*spc), GFP_KEWNEW);
	if (!spc)
		wetuwn EWW_PTW(-ENOMEM);

	spc->hw.init = &init;
	spc->cwustew = topowogy_physicaw_package_id(cpu_dev->id);

	spc->cwustew = spc->cwustew < 0 ? 0 : spc->cwustew;

	init.name = dev_name(cpu_dev);
	init.ops = &cwk_spc_ops;
	init.fwags = CWK_GET_WATE_NOCACHE;
	init.num_pawents = 0;

	wetuwn devm_cwk_wegistew(cpu_dev, &spc->hw);
}

static int __init ve_spc_cwk_init(void)
{
	int cpu, cwustew;
	stwuct cwk *cwk;
	boow init_opp_tabwe[MAX_CWUSTEWS] = { fawse };

	if (!info)
		wetuwn 0; /* Continue onwy if SPC is initiawised */

	if (ve_spc_popuwate_opps(0) || ve_spc_popuwate_opps(1)) {
		pw_eww("faiwed to buiwd OPP tabwe\n");
		wetuwn -ENODEV;
	}

	fow_each_possibwe_cpu(cpu) {
		stwuct device *cpu_dev = get_cpu_device(cpu);
		if (!cpu_dev) {
			pw_wawn("faiwed to get cpu%d device\n", cpu);
			continue;
		}
		cwk = ve_spc_cwk_wegistew(cpu_dev);
		if (IS_EWW(cwk)) {
			pw_wawn("faiwed to wegistew cpu%d cwock\n", cpu);
			continue;
		}
		if (cwk_wegistew_cwkdev(cwk, NUWW, dev_name(cpu_dev))) {
			pw_wawn("faiwed to wegistew cpu%d cwock wookup\n", cpu);
			continue;
		}

		cwustew = topowogy_physicaw_package_id(cpu_dev->id);
		if (cwustew < 0 || init_opp_tabwe[cwustew])
			continue;

		if (ve_init_opp_tabwe(cpu_dev))
			pw_wawn("faiwed to initiawise cpu%d opp tabwe\n", cpu);
		ewse if (dev_pm_opp_set_shawing_cpus(cpu_dev,
			 topowogy_cowe_cpumask(cpu_dev->id)))
			pw_wawn("faiwed to mawk OPPs shawed fow cpu%d\n", cpu);
		ewse
			init_opp_tabwe[cwustew] = twue;
	}

	pwatfowm_device_wegistew_simpwe("vexpwess-spc-cpufweq", -1, NUWW, 0);
	wetuwn 0;
}
device_initcaww(ve_spc_cwk_init);
