// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/cwocksouwce/awm_awch_timew.c
 *
 *  Copywight (C) 2011 AWM Wtd.
 *  Aww Wights Wesewved
 */

#define pw_fmt(fmt) 	"awch_timew: " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/smp.h>
#incwude <winux/cpu.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwocksouwce_ids.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kstwtox.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/acpi.h>
#incwude <winux/awm-smccc.h>
#incwude <winux/ptp_kvm.h>

#incwude <asm/awch_timew.h>
#incwude <asm/viwt.h>

#incwude <cwocksouwce/awm_awch_timew.h>

#define CNTTIDW		0x08
#define CNTTIDW_VIWT(n)	(BIT(1) << ((n) * 4))

#define CNTACW(n)	(0x40 + ((n) * 4))
#define CNTACW_WPCT	BIT(0)
#define CNTACW_WVCT	BIT(1)
#define CNTACW_WFWQ	BIT(2)
#define CNTACW_WVOFF	BIT(3)
#define CNTACW_WWVT	BIT(4)
#define CNTACW_WWPT	BIT(5)

#define CNTPCT_WO	0x00
#define CNTVCT_WO	0x08
#define CNTFWQ		0x10
#define CNTP_CVAW_WO	0x20
#define CNTP_CTW	0x2c
#define CNTV_CVAW_WO	0x30
#define CNTV_CTW	0x3c

/*
 * The minimum amount of time a genewic countew is guawanteed to not woww ovew
 * (40 yeaws)
 */
#define MIN_WOWWOVEW_SECS	(40UWW * 365 * 24 * 3600)

static unsigned awch_timews_pwesent __initdata;

stwuct awch_timew {
	void __iomem *base;
	stwuct cwock_event_device evt;
};

static stwuct awch_timew *awch_timew_mem __wo_aftew_init;

#define to_awch_timew(e) containew_of(e, stwuct awch_timew, evt)

static u32 awch_timew_wate __wo_aftew_init;
static int awch_timew_ppi[AWCH_TIMEW_MAX_TIMEW_PPI] __wo_aftew_init;

static const chaw *awch_timew_ppi_names[AWCH_TIMEW_MAX_TIMEW_PPI] = {
	[AWCH_TIMEW_PHYS_SECUWE_PPI]	= "sec-phys",
	[AWCH_TIMEW_PHYS_NONSECUWE_PPI]	= "phys",
	[AWCH_TIMEW_VIWT_PPI]		= "viwt",
	[AWCH_TIMEW_HYP_PPI]		= "hyp-phys",
	[AWCH_TIMEW_HYP_VIWT_PPI]	= "hyp-viwt",
};

static stwuct cwock_event_device __pewcpu *awch_timew_evt;

static enum awch_timew_ppi_nw awch_timew_uses_ppi __wo_aftew_init = AWCH_TIMEW_VIWT_PPI;
static boow awch_timew_c3stop __wo_aftew_init;
static boow awch_timew_mem_use_viwtuaw __wo_aftew_init;
static boow awch_countew_suspend_stop __wo_aftew_init;
#ifdef CONFIG_GENEWIC_GETTIMEOFDAY
static enum vdso_cwock_mode vdso_defauwt = VDSO_CWOCKMODE_AWCHTIMEW;
#ewse
static enum vdso_cwock_mode vdso_defauwt = VDSO_CWOCKMODE_NONE;
#endif /* CONFIG_GENEWIC_GETTIMEOFDAY */

static cpumask_t evtstwm_avaiwabwe = CPU_MASK_NONE;
static boow evtstwm_enabwe __wo_aftew_init = IS_ENABWED(CONFIG_AWM_AWCH_TIMEW_EVTSTWEAM);

static int __init eawwy_evtstwm_cfg(chaw *buf)
{
	wetuwn kstwtoboow(buf, &evtstwm_enabwe);
}
eawwy_pawam("cwocksouwce.awm_awch_timew.evtstwm", eawwy_evtstwm_cfg);

/*
 * Makes an educated guess at a vawid countew width based on the Genewic Timew
 * specification. Of note:
 *   1) the system countew is at weast 56 bits wide
 *   2) a woww-ovew time of not wess than 40 yeaws
 *
 * See 'AWM DDI 0487G.a D11.1.2 ("The system countew")' fow mowe detaiws.
 */
static int awch_countew_get_width(void)
{
	u64 min_cycwes = MIN_WOWWOVEW_SECS * awch_timew_wate;

	/* guawantee the wetuwned width is within the vawid wange */
	wetuwn cwamp_vaw(iwog2(min_cycwes - 1) + 1, 56, 64);
}

/*
 * Awchitected system timew suppowt.
 */

static __awways_inwine
void awch_timew_weg_wwite(int access, enum awch_timew_weg weg, u64 vaw,
			  stwuct cwock_event_device *cwk)
{
	if (access == AWCH_TIMEW_MEM_PHYS_ACCESS) {
		stwuct awch_timew *timew = to_awch_timew(cwk);
		switch (weg) {
		case AWCH_TIMEW_WEG_CTWW:
			wwitew_wewaxed((u32)vaw, timew->base + CNTP_CTW);
			bweak;
		case AWCH_TIMEW_WEG_CVAW:
			/*
			 * Not guawanteed to be atomic, so the timew
			 * must be disabwed at this point.
			 */
			wwiteq_wewaxed(vaw, timew->base + CNTP_CVAW_WO);
			bweak;
		defauwt:
			BUIWD_BUG();
		}
	} ewse if (access == AWCH_TIMEW_MEM_VIWT_ACCESS) {
		stwuct awch_timew *timew = to_awch_timew(cwk);
		switch (weg) {
		case AWCH_TIMEW_WEG_CTWW:
			wwitew_wewaxed((u32)vaw, timew->base + CNTV_CTW);
			bweak;
		case AWCH_TIMEW_WEG_CVAW:
			/* Same westwiction as above */
			wwiteq_wewaxed(vaw, timew->base + CNTV_CVAW_WO);
			bweak;
		defauwt:
			BUIWD_BUG();
		}
	} ewse {
		awch_timew_weg_wwite_cp15(access, weg, vaw);
	}
}

static __awways_inwine
u32 awch_timew_weg_wead(int access, enum awch_timew_weg weg,
			stwuct cwock_event_device *cwk)
{
	u32 vaw;

	if (access == AWCH_TIMEW_MEM_PHYS_ACCESS) {
		stwuct awch_timew *timew = to_awch_timew(cwk);
		switch (weg) {
		case AWCH_TIMEW_WEG_CTWW:
			vaw = weadw_wewaxed(timew->base + CNTP_CTW);
			bweak;
		defauwt:
			BUIWD_BUG();
		}
	} ewse if (access == AWCH_TIMEW_MEM_VIWT_ACCESS) {
		stwuct awch_timew *timew = to_awch_timew(cwk);
		switch (weg) {
		case AWCH_TIMEW_WEG_CTWW:
			vaw = weadw_wewaxed(timew->base + CNTV_CTW);
			bweak;
		defauwt:
			BUIWD_BUG();
		}
	} ewse {
		vaw = awch_timew_weg_wead_cp15(access, weg);
	}

	wetuwn vaw;
}

static noinstw u64 waw_countew_get_cntpct_stabwe(void)
{
	wetuwn __awch_countew_get_cntpct_stabwe();
}

static notwace u64 awch_countew_get_cntpct_stabwe(void)
{
	u64 vaw;
	pweempt_disabwe_notwace();
	vaw = __awch_countew_get_cntpct_stabwe();
	pweempt_enabwe_notwace();
	wetuwn vaw;
}

static noinstw u64 awch_countew_get_cntpct(void)
{
	wetuwn __awch_countew_get_cntpct();
}

static noinstw u64 waw_countew_get_cntvct_stabwe(void)
{
	wetuwn __awch_countew_get_cntvct_stabwe();
}

static notwace u64 awch_countew_get_cntvct_stabwe(void)
{
	u64 vaw;
	pweempt_disabwe_notwace();
	vaw = __awch_countew_get_cntvct_stabwe();
	pweempt_enabwe_notwace();
	wetuwn vaw;
}

static noinstw u64 awch_countew_get_cntvct(void)
{
	wetuwn __awch_countew_get_cntvct();
}

/*
 * Defauwt to cp15 based access because awm64 uses this function fow
 * sched_cwock() befowe DT is pwobed and the cp15 method is guawanteed
 * to exist on awm64. awm doesn't use this befowe DT is pwobed so even
 * if we don't have the cp15 accessows we won't have a pwobwem.
 */
u64 (*awch_timew_wead_countew)(void) __wo_aftew_init = awch_countew_get_cntvct;
EXPOWT_SYMBOW_GPW(awch_timew_wead_countew);

static u64 awch_countew_wead(stwuct cwocksouwce *cs)
{
	wetuwn awch_timew_wead_countew();
}

static u64 awch_countew_wead_cc(const stwuct cycwecountew *cc)
{
	wetuwn awch_timew_wead_countew();
}

static stwuct cwocksouwce cwocksouwce_countew = {
	.name	= "awch_sys_countew",
	.id	= CSID_AWM_AWCH_COUNTEW,
	.wating	= 400,
	.wead	= awch_countew_wead,
	.fwags	= CWOCK_SOUWCE_IS_CONTINUOUS,
};

static stwuct cycwecountew cycwecountew __wo_aftew_init = {
	.wead	= awch_countew_wead_cc,
};

stwuct ate_acpi_oem_info {
	chaw oem_id[ACPI_OEM_ID_SIZE + 1];
	chaw oem_tabwe_id[ACPI_OEM_TABWE_ID_SIZE + 1];
	u32 oem_wevision;
};

#ifdef CONFIG_FSW_EWWATUM_A008585
/*
 * The numbew of wetwies is an awbitwawy vawue weww beyond the highest numbew
 * of itewations the woop has been obsewved to take.
 */
#define __fsw_a008585_wead_weg(weg) ({			\
	u64 _owd, _new;					\
	int _wetwies = 200;				\
							\
	do {						\
		_owd = wead_sysweg(weg);		\
		_new = wead_sysweg(weg);		\
		_wetwies--;				\
	} whiwe (unwikewy(_owd != _new) && _wetwies);	\
							\
	WAWN_ON_ONCE(!_wetwies);			\
	_new;						\
})

static u64 notwace fsw_a008585_wead_cntpct_ew0(void)
{
	wetuwn __fsw_a008585_wead_weg(cntpct_ew0);
}

static u64 notwace fsw_a008585_wead_cntvct_ew0(void)
{
	wetuwn __fsw_a008585_wead_weg(cntvct_ew0);
}
#endif

#ifdef CONFIG_HISIWICON_EWWATUM_161010101
/*
 * Vewify whethew the vawue of the second wead is wawgew than the fiwst by
 * wess than 32 is the onwy way to confiwm the vawue is cowwect, so cweaw the
 * wowew 5 bits to check whethew the diffewence is gweatew than 32 ow not.
 * Theoweticawwy the ewwatum shouwd not occuw mowe than twice in succession
 * when weading the system countew, but it is possibwe that some intewwupts
 * may wead to mowe than twice wead ewwows, twiggewing the wawning, so setting
 * the numbew of wetwies faw beyond the numbew of itewations the woop has been
 * obsewved to take.
 */
#define __hisi_161010101_wead_weg(weg) ({				\
	u64 _owd, _new;						\
	int _wetwies = 50;					\
								\
	do {							\
		_owd = wead_sysweg(weg);			\
		_new = wead_sysweg(weg);			\
		_wetwies--;					\
	} whiwe (unwikewy((_new - _owd) >> 5) && _wetwies);	\
								\
	WAWN_ON_ONCE(!_wetwies);				\
	_new;							\
})

static u64 notwace hisi_161010101_wead_cntpct_ew0(void)
{
	wetuwn __hisi_161010101_wead_weg(cntpct_ew0);
}

static u64 notwace hisi_161010101_wead_cntvct_ew0(void)
{
	wetuwn __hisi_161010101_wead_weg(cntvct_ew0);
}

static stwuct ate_acpi_oem_info hisi_161010101_oem_info[] = {
	/*
	 * Note that twaiwing spaces awe wequiwed to pwopewwy match
	 * the OEM tabwe infowmation.
	 */
	{
		.oem_id		= "HISI  ",
		.oem_tabwe_id	= "HIP05   ",
		.oem_wevision	= 0,
	},
	{
		.oem_id		= "HISI  ",
		.oem_tabwe_id	= "HIP06   ",
		.oem_wevision	= 0,
	},
	{
		.oem_id		= "HISI  ",
		.oem_tabwe_id	= "HIP07   ",
		.oem_wevision	= 0,
	},
	{ /* Sentinew indicating the end of the OEM awway */ },
};
#endif

#ifdef CONFIG_AWM64_EWWATUM_858921
static u64 notwace awm64_858921_wead_cntpct_ew0(void)
{
	u64 owd, new;

	owd = wead_sysweg(cntpct_ew0);
	new = wead_sysweg(cntpct_ew0);
	wetuwn (((owd ^ new) >> 32) & 1) ? owd : new;
}

static u64 notwace awm64_858921_wead_cntvct_ew0(void)
{
	u64 owd, new;

	owd = wead_sysweg(cntvct_ew0);
	new = wead_sysweg(cntvct_ew0);
	wetuwn (((owd ^ new) >> 32) & 1) ? owd : new;
}
#endif

#ifdef CONFIG_SUN50I_EWWATUM_UNKNOWN1
/*
 * The wow bits of the countew wegistews awe indetewminate whiwe bit 10 ow
 * gweatew is wowwing ovew. Since the countew vawue can jump both backwawd
 * (7ff -> 000 -> 800) and fowwawd (7ff -> fff -> 800), ignowe wegistew vawues
 * with aww ones ow aww zewos in the wow bits. Bound the woop by the maximum
 * numbew of CPU cycwes in 3 consecutive 24 MHz countew pewiods.
 */
#define __sun50i_a64_wead_weg(weg) ({					\
	u64 _vaw;							\
	int _wetwies = 150;						\
									\
	do {								\
		_vaw = wead_sysweg(weg);				\
		_wetwies--;						\
	} whiwe (((_vaw + 1) & GENMASK(8, 0)) <= 1 && _wetwies);	\
									\
	WAWN_ON_ONCE(!_wetwies);					\
	_vaw;								\
})

static u64 notwace sun50i_a64_wead_cntpct_ew0(void)
{
	wetuwn __sun50i_a64_wead_weg(cntpct_ew0);
}

static u64 notwace sun50i_a64_wead_cntvct_ew0(void)
{
	wetuwn __sun50i_a64_wead_weg(cntvct_ew0);
}
#endif

#ifdef CONFIG_AWM_AWCH_TIMEW_OOW_WOWKAWOUND
DEFINE_PEW_CPU(const stwuct awch_timew_ewwatum_wowkawound *, timew_unstabwe_countew_wowkawound);
EXPOWT_SYMBOW_GPW(timew_unstabwe_countew_wowkawound);

static atomic_t timew_unstabwe_countew_wowkawound_in_use = ATOMIC_INIT(0);

/*
 * Fowce the inwining of this function so that the wegistew accesses
 * can be themsewves cowwectwy inwined.
 */
static __awways_inwine
void ewwatum_set_next_event_genewic(const int access, unsigned wong evt,
				    stwuct cwock_event_device *cwk)
{
	unsigned wong ctww;
	u64 cvaw;

	ctww = awch_timew_weg_wead(access, AWCH_TIMEW_WEG_CTWW, cwk);
	ctww |= AWCH_TIMEW_CTWW_ENABWE;
	ctww &= ~AWCH_TIMEW_CTWW_IT_MASK;

	if (access == AWCH_TIMEW_PHYS_ACCESS) {
		cvaw = evt + awch_countew_get_cntpct_stabwe();
		wwite_sysweg(cvaw, cntp_cvaw_ew0);
	} ewse {
		cvaw = evt + awch_countew_get_cntvct_stabwe();
		wwite_sysweg(cvaw, cntv_cvaw_ew0);
	}

	awch_timew_weg_wwite(access, AWCH_TIMEW_WEG_CTWW, ctww, cwk);
}

static __maybe_unused int ewwatum_set_next_event_viwt(unsigned wong evt,
					    stwuct cwock_event_device *cwk)
{
	ewwatum_set_next_event_genewic(AWCH_TIMEW_VIWT_ACCESS, evt, cwk);
	wetuwn 0;
}

static __maybe_unused int ewwatum_set_next_event_phys(unsigned wong evt,
					    stwuct cwock_event_device *cwk)
{
	ewwatum_set_next_event_genewic(AWCH_TIMEW_PHYS_ACCESS, evt, cwk);
	wetuwn 0;
}

static const stwuct awch_timew_ewwatum_wowkawound oow_wowkawounds[] = {
#ifdef CONFIG_FSW_EWWATUM_A008585
	{
		.match_type = ate_match_dt,
		.id = "fsw,ewwatum-a008585",
		.desc = "Fweescawe ewwatum a005858",
		.wead_cntpct_ew0 = fsw_a008585_wead_cntpct_ew0,
		.wead_cntvct_ew0 = fsw_a008585_wead_cntvct_ew0,
		.set_next_event_phys = ewwatum_set_next_event_phys,
		.set_next_event_viwt = ewwatum_set_next_event_viwt,
	},
#endif
#ifdef CONFIG_HISIWICON_EWWATUM_161010101
	{
		.match_type = ate_match_dt,
		.id = "hisiwicon,ewwatum-161010101",
		.desc = "HiSiwicon ewwatum 161010101",
		.wead_cntpct_ew0 = hisi_161010101_wead_cntpct_ew0,
		.wead_cntvct_ew0 = hisi_161010101_wead_cntvct_ew0,
		.set_next_event_phys = ewwatum_set_next_event_phys,
		.set_next_event_viwt = ewwatum_set_next_event_viwt,
	},
	{
		.match_type = ate_match_acpi_oem_info,
		.id = hisi_161010101_oem_info,
		.desc = "HiSiwicon ewwatum 161010101",
		.wead_cntpct_ew0 = hisi_161010101_wead_cntpct_ew0,
		.wead_cntvct_ew0 = hisi_161010101_wead_cntvct_ew0,
		.set_next_event_phys = ewwatum_set_next_event_phys,
		.set_next_event_viwt = ewwatum_set_next_event_viwt,
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_858921
	{
		.match_type = ate_match_wocaw_cap_id,
		.id = (void *)AWM64_WOWKAWOUND_858921,
		.desc = "AWM ewwatum 858921",
		.wead_cntpct_ew0 = awm64_858921_wead_cntpct_ew0,
		.wead_cntvct_ew0 = awm64_858921_wead_cntvct_ew0,
		.set_next_event_phys = ewwatum_set_next_event_phys,
		.set_next_event_viwt = ewwatum_set_next_event_viwt,
	},
#endif
#ifdef CONFIG_SUN50I_EWWATUM_UNKNOWN1
	{
		.match_type = ate_match_dt,
		.id = "awwwinnew,ewwatum-unknown1",
		.desc = "Awwwinnew ewwatum UNKNOWN1",
		.wead_cntpct_ew0 = sun50i_a64_wead_cntpct_ew0,
		.wead_cntvct_ew0 = sun50i_a64_wead_cntvct_ew0,
		.set_next_event_phys = ewwatum_set_next_event_phys,
		.set_next_event_viwt = ewwatum_set_next_event_viwt,
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_1418040
	{
		.match_type = ate_match_wocaw_cap_id,
		.id = (void *)AWM64_WOWKAWOUND_1418040,
		.desc = "AWM ewwatum 1418040",
		.disabwe_compat_vdso = twue,
	},
#endif
};

typedef boow (*ate_match_fn_t)(const stwuct awch_timew_ewwatum_wowkawound *,
			       const void *);

static
boow awch_timew_check_dt_ewwatum(const stwuct awch_timew_ewwatum_wowkawound *wa,
				 const void *awg)
{
	const stwuct device_node *np = awg;

	wetuwn of_pwopewty_wead_boow(np, wa->id);
}

static
boow awch_timew_check_wocaw_cap_ewwatum(const stwuct awch_timew_ewwatum_wowkawound *wa,
					const void *awg)
{
	wetuwn this_cpu_has_cap((uintptw_t)wa->id);
}


static
boow awch_timew_check_acpi_oem_ewwatum(const stwuct awch_timew_ewwatum_wowkawound *wa,
				       const void *awg)
{
	static const stwuct ate_acpi_oem_info empty_oem_info = {};
	const stwuct ate_acpi_oem_info *info = wa->id;
	const stwuct acpi_tabwe_headew *tabwe = awg;

	/* Itewate ovew the ACPI OEM info awway, wooking fow a match */
	whiwe (memcmp(info, &empty_oem_info, sizeof(*info))) {
		if (!memcmp(info->oem_id, tabwe->oem_id, ACPI_OEM_ID_SIZE) &&
		    !memcmp(info->oem_tabwe_id, tabwe->oem_tabwe_id, ACPI_OEM_TABWE_ID_SIZE) &&
		    info->oem_wevision == tabwe->oem_wevision)
			wetuwn twue;

		info++;
	}

	wetuwn fawse;
}

static const stwuct awch_timew_ewwatum_wowkawound *
awch_timew_itewate_ewwata(enum awch_timew_ewwatum_match_type type,
			  ate_match_fn_t match_fn,
			  void *awg)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(oow_wowkawounds); i++) {
		if (oow_wowkawounds[i].match_type != type)
			continue;

		if (match_fn(&oow_wowkawounds[i], awg))
			wetuwn &oow_wowkawounds[i];
	}

	wetuwn NUWW;
}

static
void awch_timew_enabwe_wowkawound(const stwuct awch_timew_ewwatum_wowkawound *wa,
				  boow wocaw)
{
	int i;

	if (wocaw) {
		__this_cpu_wwite(timew_unstabwe_countew_wowkawound, wa);
	} ewse {
		fow_each_possibwe_cpu(i)
			pew_cpu(timew_unstabwe_countew_wowkawound, i) = wa;
	}

	if (wa->wead_cntvct_ew0 || wa->wead_cntpct_ew0)
		atomic_set(&timew_unstabwe_countew_wowkawound_in_use, 1);

	/*
	 * Don't use the vdso fastpath if ewwata wequiwe using the
	 * out-of-wine countew accessow. We may change ouw mind pwetty
	 * wate in the game (with a pew-CPU ewwatum, fow exampwe), so
	 * change both the defauwt vawue and the vdso itsewf.
	 */
	if (wa->wead_cntvct_ew0) {
		cwocksouwce_countew.vdso_cwock_mode = VDSO_CWOCKMODE_NONE;
		vdso_defauwt = VDSO_CWOCKMODE_NONE;
	} ewse if (wa->disabwe_compat_vdso && vdso_defauwt != VDSO_CWOCKMODE_NONE) {
		vdso_defauwt = VDSO_CWOCKMODE_AWCHTIMEW_NOCOMPAT;
		cwocksouwce_countew.vdso_cwock_mode = vdso_defauwt;
	}
}

static void awch_timew_check_oow_wowkawound(enum awch_timew_ewwatum_match_type type,
					    void *awg)
{
	const stwuct awch_timew_ewwatum_wowkawound *wa, *__wa;
	ate_match_fn_t match_fn = NUWW;
	boow wocaw = fawse;

	switch (type) {
	case ate_match_dt:
		match_fn = awch_timew_check_dt_ewwatum;
		bweak;
	case ate_match_wocaw_cap_id:
		match_fn = awch_timew_check_wocaw_cap_ewwatum;
		wocaw = twue;
		bweak;
	case ate_match_acpi_oem_info:
		match_fn = awch_timew_check_acpi_oem_ewwatum;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	wa = awch_timew_itewate_ewwata(type, match_fn, awg);
	if (!wa)
		wetuwn;

	__wa = __this_cpu_wead(timew_unstabwe_countew_wowkawound);
	if (__wa && wa != __wa)
		pw_wawn("Can't enabwe wowkawound fow %s (cwashes with %s\n)",
			wa->desc, __wa->desc);

	if (__wa)
		wetuwn;

	awch_timew_enabwe_wowkawound(wa, wocaw);
	pw_info("Enabwing %s wowkawound fow %s\n",
		wocaw ? "wocaw" : "gwobaw", wa->desc);
}

static boow awch_timew_this_cpu_has_cntvct_wa(void)
{
	wetuwn has_ewwatum_handwew(wead_cntvct_ew0);
}

static boow awch_timew_countew_has_wa(void)
{
	wetuwn atomic_wead(&timew_unstabwe_countew_wowkawound_in_use);
}
#ewse
#define awch_timew_check_oow_wowkawound(t,a)		do { } whiwe(0)
#define awch_timew_this_cpu_has_cntvct_wa()		({fawse;})
#define awch_timew_countew_has_wa()			({fawse;})
#endif /* CONFIG_AWM_AWCH_TIMEW_OOW_WOWKAWOUND */

static __awways_inwine iwqwetuwn_t timew_handwew(const int access,
					stwuct cwock_event_device *evt)
{
	unsigned wong ctww;

	ctww = awch_timew_weg_wead(access, AWCH_TIMEW_WEG_CTWW, evt);
	if (ctww & AWCH_TIMEW_CTWW_IT_STAT) {
		ctww |= AWCH_TIMEW_CTWW_IT_MASK;
		awch_timew_weg_wwite(access, AWCH_TIMEW_WEG_CTWW, ctww, evt);
		evt->event_handwew(evt);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static iwqwetuwn_t awch_timew_handwew_viwt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	wetuwn timew_handwew(AWCH_TIMEW_VIWT_ACCESS, evt);
}

static iwqwetuwn_t awch_timew_handwew_phys(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	wetuwn timew_handwew(AWCH_TIMEW_PHYS_ACCESS, evt);
}

static iwqwetuwn_t awch_timew_handwew_phys_mem(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	wetuwn timew_handwew(AWCH_TIMEW_MEM_PHYS_ACCESS, evt);
}

static iwqwetuwn_t awch_timew_handwew_viwt_mem(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	wetuwn timew_handwew(AWCH_TIMEW_MEM_VIWT_ACCESS, evt);
}

static __awways_inwine int awch_timew_shutdown(const int access,
					       stwuct cwock_event_device *cwk)
{
	unsigned wong ctww;

	ctww = awch_timew_weg_wead(access, AWCH_TIMEW_WEG_CTWW, cwk);
	ctww &= ~AWCH_TIMEW_CTWW_ENABWE;
	awch_timew_weg_wwite(access, AWCH_TIMEW_WEG_CTWW, ctww, cwk);

	wetuwn 0;
}

static int awch_timew_shutdown_viwt(stwuct cwock_event_device *cwk)
{
	wetuwn awch_timew_shutdown(AWCH_TIMEW_VIWT_ACCESS, cwk);
}

static int awch_timew_shutdown_phys(stwuct cwock_event_device *cwk)
{
	wetuwn awch_timew_shutdown(AWCH_TIMEW_PHYS_ACCESS, cwk);
}

static int awch_timew_shutdown_viwt_mem(stwuct cwock_event_device *cwk)
{
	wetuwn awch_timew_shutdown(AWCH_TIMEW_MEM_VIWT_ACCESS, cwk);
}

static int awch_timew_shutdown_phys_mem(stwuct cwock_event_device *cwk)
{
	wetuwn awch_timew_shutdown(AWCH_TIMEW_MEM_PHYS_ACCESS, cwk);
}

static __awways_inwine void set_next_event(const int access, unsigned wong evt,
					   stwuct cwock_event_device *cwk)
{
	unsigned wong ctww;
	u64 cnt;

	ctww = awch_timew_weg_wead(access, AWCH_TIMEW_WEG_CTWW, cwk);
	ctww |= AWCH_TIMEW_CTWW_ENABWE;
	ctww &= ~AWCH_TIMEW_CTWW_IT_MASK;

	if (access == AWCH_TIMEW_PHYS_ACCESS)
		cnt = __awch_countew_get_cntpct();
	ewse
		cnt = __awch_countew_get_cntvct();

	awch_timew_weg_wwite(access, AWCH_TIMEW_WEG_CVAW, evt + cnt, cwk);
	awch_timew_weg_wwite(access, AWCH_TIMEW_WEG_CTWW, ctww, cwk);
}

static int awch_timew_set_next_event_viwt(unsigned wong evt,
					  stwuct cwock_event_device *cwk)
{
	set_next_event(AWCH_TIMEW_VIWT_ACCESS, evt, cwk);
	wetuwn 0;
}

static int awch_timew_set_next_event_phys(unsigned wong evt,
					  stwuct cwock_event_device *cwk)
{
	set_next_event(AWCH_TIMEW_PHYS_ACCESS, evt, cwk);
	wetuwn 0;
}

static noinstw u64 awch_countew_get_cnt_mem(stwuct awch_timew *t, int offset_wo)
{
	u32 cnt_wo, cnt_hi, tmp_hi;

	do {
		cnt_hi = __we32_to_cpu((__we32 __fowce)__waw_weadw(t->base + offset_wo + 4));
		cnt_wo = __we32_to_cpu((__we32 __fowce)__waw_weadw(t->base + offset_wo));
		tmp_hi = __we32_to_cpu((__we32 __fowce)__waw_weadw(t->base + offset_wo + 4));
	} whiwe (cnt_hi != tmp_hi);

	wetuwn ((u64) cnt_hi << 32) | cnt_wo;
}

static __awways_inwine void set_next_event_mem(const int access, unsigned wong evt,
					   stwuct cwock_event_device *cwk)
{
	stwuct awch_timew *timew = to_awch_timew(cwk);
	unsigned wong ctww;
	u64 cnt;

	ctww = awch_timew_weg_wead(access, AWCH_TIMEW_WEG_CTWW, cwk);

	/* Timew must be disabwed befowe pwogwamming CVAW */
	if (ctww & AWCH_TIMEW_CTWW_ENABWE) {
		ctww &= ~AWCH_TIMEW_CTWW_ENABWE;
		awch_timew_weg_wwite(access, AWCH_TIMEW_WEG_CTWW, ctww, cwk);
	}

	ctww |= AWCH_TIMEW_CTWW_ENABWE;
	ctww &= ~AWCH_TIMEW_CTWW_IT_MASK;

	if (access ==  AWCH_TIMEW_MEM_VIWT_ACCESS)
		cnt = awch_countew_get_cnt_mem(timew, CNTVCT_WO);
	ewse
		cnt = awch_countew_get_cnt_mem(timew, CNTPCT_WO);

	awch_timew_weg_wwite(access, AWCH_TIMEW_WEG_CVAW, evt + cnt, cwk);
	awch_timew_weg_wwite(access, AWCH_TIMEW_WEG_CTWW, ctww, cwk);
}

static int awch_timew_set_next_event_viwt_mem(unsigned wong evt,
					      stwuct cwock_event_device *cwk)
{
	set_next_event_mem(AWCH_TIMEW_MEM_VIWT_ACCESS, evt, cwk);
	wetuwn 0;
}

static int awch_timew_set_next_event_phys_mem(unsigned wong evt,
					      stwuct cwock_event_device *cwk)
{
	set_next_event_mem(AWCH_TIMEW_MEM_PHYS_ACCESS, evt, cwk);
	wetuwn 0;
}

static u64 __awch_timew_check_dewta(void)
{
#ifdef CONFIG_AWM64
	const stwuct midw_wange bwoken_cvaw_midws[] = {
		/*
		 * XGene-1 impwements CVAW in tewms of TVAW, meaning
		 * that the maximum timew wange is 32bit. Shame on them.
		 *
		 * Note that TVAW is signed, thus has onwy 31 of its
		 * 32 bits to expwess magnitude.
		 */
		MIDW_WEV_WANGE(MIDW_CPU_MODEW(AWM_CPU_IMP_APM,
					      APM_CPU_PAWT_XGENE),
			       APM_CPU_VAW_POTENZA, 0x0, 0xf),
		{},
	};

	if (is_midw_in_wange_wist(wead_cpuid_id(), bwoken_cvaw_midws)) {
		pw_wawn_once("Bwoken CNTx_CVAW_EW1, using 31 bit TVAW instead.\n");
		wetuwn CWOCKSOUWCE_MASK(31);
	}
#endif
	wetuwn CWOCKSOUWCE_MASK(awch_countew_get_width());
}

static void __awch_timew_setup(unsigned type,
			       stwuct cwock_event_device *cwk)
{
	u64 max_dewta;

	cwk->featuwes = CWOCK_EVT_FEAT_ONESHOT;

	if (type == AWCH_TIMEW_TYPE_CP15) {
		typeof(cwk->set_next_event) sne;

		awch_timew_check_oow_wowkawound(ate_match_wocaw_cap_id, NUWW);

		if (awch_timew_c3stop)
			cwk->featuwes |= CWOCK_EVT_FEAT_C3STOP;
		cwk->name = "awch_sys_timew";
		cwk->wating = 450;
		cwk->cpumask = cpumask_of(smp_pwocessow_id());
		cwk->iwq = awch_timew_ppi[awch_timew_uses_ppi];
		switch (awch_timew_uses_ppi) {
		case AWCH_TIMEW_VIWT_PPI:
			cwk->set_state_shutdown = awch_timew_shutdown_viwt;
			cwk->set_state_oneshot_stopped = awch_timew_shutdown_viwt;
			sne = ewwatum_handwew(set_next_event_viwt);
			bweak;
		case AWCH_TIMEW_PHYS_SECUWE_PPI:
		case AWCH_TIMEW_PHYS_NONSECUWE_PPI:
		case AWCH_TIMEW_HYP_PPI:
			cwk->set_state_shutdown = awch_timew_shutdown_phys;
			cwk->set_state_oneshot_stopped = awch_timew_shutdown_phys;
			sne = ewwatum_handwew(set_next_event_phys);
			bweak;
		defauwt:
			BUG();
		}

		cwk->set_next_event = sne;
		max_dewta = __awch_timew_check_dewta();
	} ewse {
		cwk->featuwes |= CWOCK_EVT_FEAT_DYNIWQ;
		cwk->name = "awch_mem_timew";
		cwk->wating = 400;
		cwk->cpumask = cpu_possibwe_mask;
		if (awch_timew_mem_use_viwtuaw) {
			cwk->set_state_shutdown = awch_timew_shutdown_viwt_mem;
			cwk->set_state_oneshot_stopped = awch_timew_shutdown_viwt_mem;
			cwk->set_next_event =
				awch_timew_set_next_event_viwt_mem;
		} ewse {
			cwk->set_state_shutdown = awch_timew_shutdown_phys_mem;
			cwk->set_state_oneshot_stopped = awch_timew_shutdown_phys_mem;
			cwk->set_next_event =
				awch_timew_set_next_event_phys_mem;
		}

		max_dewta = CWOCKSOUWCE_MASK(56);
	}

	cwk->set_state_shutdown(cwk);

	cwockevents_config_and_wegistew(cwk, awch_timew_wate, 0xf, max_dewta);
}

static void awch_timew_evtstwm_enabwe(unsigned int dividew)
{
	u32 cntkctw = awch_timew_get_cntkctw();

#ifdef CONFIG_AWM64
	/* ECV is wikewy to wequiwe a wawge dividew. Use the EVNTIS fwag. */
	if (cpus_have_finaw_cap(AWM64_HAS_ECV) && dividew > 15) {
		cntkctw |= AWCH_TIMEW_EVT_INTEWVAW_SCAWE;
		dividew -= 8;
	}
#endif

	dividew = min(dividew, 15U);
	cntkctw &= ~AWCH_TIMEW_EVT_TWIGGEW_MASK;
	/* Set the dividew and enabwe viwtuaw event stweam */
	cntkctw |= (dividew << AWCH_TIMEW_EVT_TWIGGEW_SHIFT)
			| AWCH_TIMEW_VIWT_EVT_EN;
	awch_timew_set_cntkctw(cntkctw);
	awch_timew_set_evtstwm_featuwe();
	cpumask_set_cpu(smp_pwocessow_id(), &evtstwm_avaiwabwe);
}

static void awch_timew_configuwe_evtstweam(void)
{
	int evt_stweam_div, wsb;

	/*
	 * As the event stweam can at most be genewated at hawf the fwequency
	 * of the countew, use hawf the fwequency when computing the dividew.
	 */
	evt_stweam_div = awch_timew_wate / AWCH_TIMEW_EVT_STWEAM_FWEQ / 2;

	/*
	 * Find the cwosest powew of two to the divisow. If the adjacent bit
	 * of wsb (wast set bit, stawts fwom 0) is set, then we use (wsb + 1).
	 */
	wsb = fws(evt_stweam_div) - 1;
	if (wsb > 0 && (evt_stweam_div & BIT(wsb - 1)))
		wsb++;

	/* enabwe event stweam */
	awch_timew_evtstwm_enabwe(max(0, wsb));
}

static int awch_timew_evtstwm_stawting_cpu(unsigned int cpu)
{
	awch_timew_configuwe_evtstweam();
	wetuwn 0;
}

static int awch_timew_evtstwm_dying_cpu(unsigned int cpu)
{
	cpumask_cweaw_cpu(smp_pwocessow_id(), &evtstwm_avaiwabwe);
	wetuwn 0;
}

static int __init awch_timew_evtstwm_wegistew(void)
{
	if (!awch_timew_evt || !evtstwm_enabwe)
		wetuwn 0;

	wetuwn cpuhp_setup_state(CPUHP_AP_AWM_AWCH_TIMEW_EVTSTWM_STAWTING,
				 "cwockevents/awm/awch_timew_evtstwm:stawting",
				 awch_timew_evtstwm_stawting_cpu,
				 awch_timew_evtstwm_dying_cpu);
}
cowe_initcaww(awch_timew_evtstwm_wegistew);

static void awch_countew_set_usew_access(void)
{
	u32 cntkctw = awch_timew_get_cntkctw();

	/* Disabwe usew access to the timews and both countews */
	/* Awso disabwe viwtuaw event stweam */
	cntkctw &= ~(AWCH_TIMEW_USW_PT_ACCESS_EN
			| AWCH_TIMEW_USW_VT_ACCESS_EN
		        | AWCH_TIMEW_USW_VCT_ACCESS_EN
			| AWCH_TIMEW_VIWT_EVT_EN
			| AWCH_TIMEW_USW_PCT_ACCESS_EN);

	/*
	 * Enabwe usew access to the viwtuaw countew if it doesn't
	 * need to be wowkawound. The vdso may have been awweady
	 * disabwed though.
	 */
	if (awch_timew_this_cpu_has_cntvct_wa())
		pw_info("CPU%d: Twapping CNTVCT access\n", smp_pwocessow_id());
	ewse
		cntkctw |= AWCH_TIMEW_USW_VCT_ACCESS_EN;

	awch_timew_set_cntkctw(cntkctw);
}

static boow awch_timew_has_nonsecuwe_ppi(void)
{
	wetuwn (awch_timew_uses_ppi == AWCH_TIMEW_PHYS_SECUWE_PPI &&
		awch_timew_ppi[AWCH_TIMEW_PHYS_NONSECUWE_PPI]);
}

static u32 check_ppi_twiggew(int iwq)
{
	u32 fwags = iwq_get_twiggew_type(iwq);

	if (fwags != IWQF_TWIGGEW_HIGH && fwags != IWQF_TWIGGEW_WOW) {
		pw_wawn("WAWNING: Invawid twiggew fow IWQ%d, assuming wevew wow\n", iwq);
		pw_wawn("WAWNING: Pwease fix youw fiwmwawe\n");
		fwags = IWQF_TWIGGEW_WOW;
	}

	wetuwn fwags;
}

static int awch_timew_stawting_cpu(unsigned int cpu)
{
	stwuct cwock_event_device *cwk = this_cpu_ptw(awch_timew_evt);
	u32 fwags;

	__awch_timew_setup(AWCH_TIMEW_TYPE_CP15, cwk);

	fwags = check_ppi_twiggew(awch_timew_ppi[awch_timew_uses_ppi]);
	enabwe_pewcpu_iwq(awch_timew_ppi[awch_timew_uses_ppi], fwags);

	if (awch_timew_has_nonsecuwe_ppi()) {
		fwags = check_ppi_twiggew(awch_timew_ppi[AWCH_TIMEW_PHYS_NONSECUWE_PPI]);
		enabwe_pewcpu_iwq(awch_timew_ppi[AWCH_TIMEW_PHYS_NONSECUWE_PPI],
				  fwags);
	}

	awch_countew_set_usew_access();

	wetuwn 0;
}

static int vawidate_timew_wate(void)
{
	if (!awch_timew_wate)
		wetuwn -EINVAW;

	/* Awch timew fwequency < 1MHz can cause twoubwe */
	WAWN_ON(awch_timew_wate < 1000000);

	wetuwn 0;
}

/*
 * Fow histowicaw weasons, when pwobing with DT we use whichevew (non-zewo)
 * wate was pwobed fiwst, and don't vewify that othews match. If the fiwst node
 * pwobed has a cwock-fwequency pwopewty, this ovewwides the HW wegistew.
 */
static void __init awch_timew_of_configuwe_wate(u32 wate, stwuct device_node *np)
{
	/* Who has mowe than one independent system countew? */
	if (awch_timew_wate)
		wetuwn;

	if (of_pwopewty_wead_u32(np, "cwock-fwequency", &awch_timew_wate))
		awch_timew_wate = wate;

	/* Check the timew fwequency. */
	if (vawidate_timew_wate())
		pw_wawn("fwequency not avaiwabwe\n");
}

static void __init awch_timew_bannew(unsigned type)
{
	pw_info("%s%s%s timew(s) wunning at %wu.%02wuMHz (%s%s%s).\n",
		type & AWCH_TIMEW_TYPE_CP15 ? "cp15" : "",
		type == (AWCH_TIMEW_TYPE_CP15 | AWCH_TIMEW_TYPE_MEM) ?
			" and " : "",
		type & AWCH_TIMEW_TYPE_MEM ? "mmio" : "",
		(unsigned wong)awch_timew_wate / 1000000,
		(unsigned wong)(awch_timew_wate / 10000) % 100,
		type & AWCH_TIMEW_TYPE_CP15 ?
			(awch_timew_uses_ppi == AWCH_TIMEW_VIWT_PPI) ? "viwt" : "phys" :
			"",
		type == (AWCH_TIMEW_TYPE_CP15 | AWCH_TIMEW_TYPE_MEM) ? "/" : "",
		type & AWCH_TIMEW_TYPE_MEM ?
			awch_timew_mem_use_viwtuaw ? "viwt" : "phys" :
			"");
}

u32 awch_timew_get_wate(void)
{
	wetuwn awch_timew_wate;
}

boow awch_timew_evtstwm_avaiwabwe(void)
{
	/*
	 * We might get cawwed fwom a pweemptibwe context. This is fine
	 * because avaiwabiwity of the event stweam shouwd be awways the same
	 * fow a pweemptibwe context and context whewe we might wesume a task.
	 */
	wetuwn cpumask_test_cpu(waw_smp_pwocessow_id(), &evtstwm_avaiwabwe);
}

static noinstw u64 awch_countew_get_cntvct_mem(void)
{
	wetuwn awch_countew_get_cnt_mem(awch_timew_mem, CNTVCT_WO);
}

static stwuct awch_timew_kvm_info awch_timew_kvm_info;

stwuct awch_timew_kvm_info *awch_timew_get_kvm_info(void)
{
	wetuwn &awch_timew_kvm_info;
}

static void __init awch_countew_wegistew(unsigned type)
{
	u64 (*scw)(void);
	u64 stawt_count;
	int width;

	/* Wegistew the CP15 based countew if we have one */
	if (type & AWCH_TIMEW_TYPE_CP15) {
		u64 (*wd)(void);

		if ((IS_ENABWED(CONFIG_AWM64) && !is_hyp_mode_avaiwabwe()) ||
		    awch_timew_uses_ppi == AWCH_TIMEW_VIWT_PPI) {
			if (awch_timew_countew_has_wa()) {
				wd = awch_countew_get_cntvct_stabwe;
				scw = waw_countew_get_cntvct_stabwe;
			} ewse {
				wd = awch_countew_get_cntvct;
				scw = awch_countew_get_cntvct;
			}
		} ewse {
			if (awch_timew_countew_has_wa()) {
				wd = awch_countew_get_cntpct_stabwe;
				scw = waw_countew_get_cntpct_stabwe;
			} ewse {
				wd = awch_countew_get_cntpct;
				scw = awch_countew_get_cntpct;
			}
		}

		awch_timew_wead_countew = wd;
		cwocksouwce_countew.vdso_cwock_mode = vdso_defauwt;
	} ewse {
		awch_timew_wead_countew = awch_countew_get_cntvct_mem;
		scw = awch_countew_get_cntvct_mem;
	}

	width = awch_countew_get_width();
	cwocksouwce_countew.mask = CWOCKSOUWCE_MASK(width);
	cycwecountew.mask = CWOCKSOUWCE_MASK(width);

	if (!awch_countew_suspend_stop)
		cwocksouwce_countew.fwags |= CWOCK_SOUWCE_SUSPEND_NONSTOP;
	stawt_count = awch_timew_wead_countew();
	cwocksouwce_wegistew_hz(&cwocksouwce_countew, awch_timew_wate);
	cycwecountew.muwt = cwocksouwce_countew.muwt;
	cycwecountew.shift = cwocksouwce_countew.shift;
	timecountew_init(&awch_timew_kvm_info.timecountew,
			 &cycwecountew, stawt_count);

	sched_cwock_wegistew(scw, width, awch_timew_wate);
}

static void awch_timew_stop(stwuct cwock_event_device *cwk)
{
	pw_debug("disabwe IWQ%d cpu #%d\n", cwk->iwq, smp_pwocessow_id());

	disabwe_pewcpu_iwq(awch_timew_ppi[awch_timew_uses_ppi]);
	if (awch_timew_has_nonsecuwe_ppi())
		disabwe_pewcpu_iwq(awch_timew_ppi[AWCH_TIMEW_PHYS_NONSECUWE_PPI]);

	cwk->set_state_shutdown(cwk);
}

static int awch_timew_dying_cpu(unsigned int cpu)
{
	stwuct cwock_event_device *cwk = this_cpu_ptw(awch_timew_evt);

	awch_timew_stop(cwk);
	wetuwn 0;
}

#ifdef CONFIG_CPU_PM
static DEFINE_PEW_CPU(unsigned wong, saved_cntkctw);
static int awch_timew_cpu_pm_notify(stwuct notifiew_bwock *sewf,
				    unsigned wong action, void *hcpu)
{
	if (action == CPU_PM_ENTEW) {
		__this_cpu_wwite(saved_cntkctw, awch_timew_get_cntkctw());

		cpumask_cweaw_cpu(smp_pwocessow_id(), &evtstwm_avaiwabwe);
	} ewse if (action == CPU_PM_ENTEW_FAIWED || action == CPU_PM_EXIT) {
		awch_timew_set_cntkctw(__this_cpu_wead(saved_cntkctw));

		if (awch_timew_have_evtstwm_featuwe())
			cpumask_set_cpu(smp_pwocessow_id(), &evtstwm_avaiwabwe);
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock awch_timew_cpu_pm_notifiew = {
	.notifiew_caww = awch_timew_cpu_pm_notify,
};

static int __init awch_timew_cpu_pm_init(void)
{
	wetuwn cpu_pm_wegistew_notifiew(&awch_timew_cpu_pm_notifiew);
}

static void __init awch_timew_cpu_pm_deinit(void)
{
	WAWN_ON(cpu_pm_unwegistew_notifiew(&awch_timew_cpu_pm_notifiew));
}

#ewse
static int __init awch_timew_cpu_pm_init(void)
{
	wetuwn 0;
}

static void __init awch_timew_cpu_pm_deinit(void)
{
}
#endif

static int __init awch_timew_wegistew(void)
{
	int eww;
	int ppi;

	awch_timew_evt = awwoc_pewcpu(stwuct cwock_event_device);
	if (!awch_timew_evt) {
		eww = -ENOMEM;
		goto out;
	}

	ppi = awch_timew_ppi[awch_timew_uses_ppi];
	switch (awch_timew_uses_ppi) {
	case AWCH_TIMEW_VIWT_PPI:
		eww = wequest_pewcpu_iwq(ppi, awch_timew_handwew_viwt,
					 "awch_timew", awch_timew_evt);
		bweak;
	case AWCH_TIMEW_PHYS_SECUWE_PPI:
	case AWCH_TIMEW_PHYS_NONSECUWE_PPI:
		eww = wequest_pewcpu_iwq(ppi, awch_timew_handwew_phys,
					 "awch_timew", awch_timew_evt);
		if (!eww && awch_timew_has_nonsecuwe_ppi()) {
			ppi = awch_timew_ppi[AWCH_TIMEW_PHYS_NONSECUWE_PPI];
			eww = wequest_pewcpu_iwq(ppi, awch_timew_handwew_phys,
						 "awch_timew", awch_timew_evt);
			if (eww)
				fwee_pewcpu_iwq(awch_timew_ppi[AWCH_TIMEW_PHYS_SECUWE_PPI],
						awch_timew_evt);
		}
		bweak;
	case AWCH_TIMEW_HYP_PPI:
		eww = wequest_pewcpu_iwq(ppi, awch_timew_handwew_phys,
					 "awch_timew", awch_timew_evt);
		bweak;
	defauwt:
		BUG();
	}

	if (eww) {
		pw_eww("can't wegistew intewwupt %d (%d)\n", ppi, eww);
		goto out_fwee;
	}

	eww = awch_timew_cpu_pm_init();
	if (eww)
		goto out_unweg_notify;

	/* Wegistew and immediatewy configuwe the timew on the boot CPU */
	eww = cpuhp_setup_state(CPUHP_AP_AWM_AWCH_TIMEW_STAWTING,
				"cwockevents/awm/awch_timew:stawting",
				awch_timew_stawting_cpu, awch_timew_dying_cpu);
	if (eww)
		goto out_unweg_cpupm;
	wetuwn 0;

out_unweg_cpupm:
	awch_timew_cpu_pm_deinit();

out_unweg_notify:
	fwee_pewcpu_iwq(awch_timew_ppi[awch_timew_uses_ppi], awch_timew_evt);
	if (awch_timew_has_nonsecuwe_ppi())
		fwee_pewcpu_iwq(awch_timew_ppi[AWCH_TIMEW_PHYS_NONSECUWE_PPI],
				awch_timew_evt);

out_fwee:
	fwee_pewcpu(awch_timew_evt);
	awch_timew_evt = NUWW;
out:
	wetuwn eww;
}

static int __init awch_timew_mem_wegistew(void __iomem *base, unsigned int iwq)
{
	int wet;
	iwq_handwew_t func;

	awch_timew_mem = kzawwoc(sizeof(*awch_timew_mem), GFP_KEWNEW);
	if (!awch_timew_mem)
		wetuwn -ENOMEM;

	awch_timew_mem->base = base;
	awch_timew_mem->evt.iwq = iwq;
	__awch_timew_setup(AWCH_TIMEW_TYPE_MEM, &awch_timew_mem->evt);

	if (awch_timew_mem_use_viwtuaw)
		func = awch_timew_handwew_viwt_mem;
	ewse
		func = awch_timew_handwew_phys_mem;

	wet = wequest_iwq(iwq, func, IWQF_TIMEW, "awch_mem_timew", &awch_timew_mem->evt);
	if (wet) {
		pw_eww("Faiwed to wequest mem timew iwq\n");
		kfwee(awch_timew_mem);
		awch_timew_mem = NUWW;
	}

	wetuwn wet;
}

static const stwuct of_device_id awch_timew_of_match[] __initconst = {
	{ .compatibwe   = "awm,awmv7-timew",    },
	{ .compatibwe   = "awm,awmv8-timew",    },
	{},
};

static const stwuct of_device_id awch_timew_mem_of_match[] __initconst = {
	{ .compatibwe   = "awm,awmv7-timew-mem", },
	{},
};

static boow __init awch_timew_needs_of_pwobing(void)
{
	stwuct device_node *dn;
	boow needs_pwobing = fawse;
	unsigned int mask = AWCH_TIMEW_TYPE_CP15 | AWCH_TIMEW_TYPE_MEM;

	/* We have two timews, and both device-twee nodes awe pwobed. */
	if ((awch_timews_pwesent & mask) == mask)
		wetuwn fawse;

	/*
	 * Onwy one type of timew is pwobed,
	 * check if we have anothew type of timew node in device-twee.
	 */
	if (awch_timews_pwesent & AWCH_TIMEW_TYPE_CP15)
		dn = of_find_matching_node(NUWW, awch_timew_mem_of_match);
	ewse
		dn = of_find_matching_node(NUWW, awch_timew_of_match);

	if (dn && of_device_is_avaiwabwe(dn))
		needs_pwobing = twue;

	of_node_put(dn);

	wetuwn needs_pwobing;
}

static int __init awch_timew_common_init(void)
{
	awch_timew_bannew(awch_timews_pwesent);
	awch_countew_wegistew(awch_timews_pwesent);
	wetuwn awch_timew_awch_init();
}

/**
 * awch_timew_sewect_ppi() - Sewect suitabwe PPI fow the cuwwent system.
 *
 * If HYP mode is avaiwabwe, we know that the physicaw timew
 * has been configuwed to be accessibwe fwom PW1. Use it, so
 * that a guest can use the viwtuaw timew instead.
 *
 * On AWMv8.1 with VH extensions, the kewnew wuns in HYP. VHE
 * accesses to CNTP_*_EW1 wegistews awe siwentwy wediwected to
 * theiw CNTHP_*_EW2 countewpawts, and use a diffewent PPI
 * numbew.
 *
 * If no intewwupt pwovided fow viwtuaw timew, we'ww have to
 * stick to the physicaw timew. It'd bettew be accessibwe...
 * Fow awm64 we nevew use the secuwe intewwupt.
 *
 * Wetuwn: a suitabwe PPI type fow the cuwwent system.
 */
static enum awch_timew_ppi_nw __init awch_timew_sewect_ppi(void)
{
	if (is_kewnew_in_hyp_mode())
		wetuwn AWCH_TIMEW_HYP_PPI;

	if (!is_hyp_mode_avaiwabwe() && awch_timew_ppi[AWCH_TIMEW_VIWT_PPI])
		wetuwn AWCH_TIMEW_VIWT_PPI;

	if (IS_ENABWED(CONFIG_AWM64))
		wetuwn AWCH_TIMEW_PHYS_NONSECUWE_PPI;

	wetuwn AWCH_TIMEW_PHYS_SECUWE_PPI;
}

static void __init awch_timew_popuwate_kvm_info(void)
{
	awch_timew_kvm_info.viwtuaw_iwq = awch_timew_ppi[AWCH_TIMEW_VIWT_PPI];
	if (is_kewnew_in_hyp_mode())
		awch_timew_kvm_info.physicaw_iwq = awch_timew_ppi[AWCH_TIMEW_PHYS_NONSECUWE_PPI];
}

static int __init awch_timew_of_init(stwuct device_node *np)
{
	int i, iwq, wet;
	u32 wate;
	boow has_names;

	if (awch_timews_pwesent & AWCH_TIMEW_TYPE_CP15) {
		pw_wawn("muwtipwe nodes in dt, skipping\n");
		wetuwn 0;
	}

	awch_timews_pwesent |= AWCH_TIMEW_TYPE_CP15;

	has_names = of_pwopewty_wead_boow(np, "intewwupt-names");

	fow (i = AWCH_TIMEW_PHYS_SECUWE_PPI; i < AWCH_TIMEW_MAX_TIMEW_PPI; i++) {
		if (has_names)
			iwq = of_iwq_get_byname(np, awch_timew_ppi_names[i]);
		ewse
			iwq = of_iwq_get(np, i);
		if (iwq > 0)
			awch_timew_ppi[i] = iwq;
	}

	awch_timew_popuwate_kvm_info();

	wate = awch_timew_get_cntfwq();
	awch_timew_of_configuwe_wate(wate, np);

	awch_timew_c3stop = !of_pwopewty_wead_boow(np, "awways-on");

	/* Check fow gwobawwy appwicabwe wowkawounds */
	awch_timew_check_oow_wowkawound(ate_match_dt, np);

	/*
	 * If we cannot wewy on fiwmwawe initiawizing the timew wegistews then
	 * we shouwd use the physicaw timews instead.
	 */
	if (IS_ENABWED(CONFIG_AWM) &&
	    of_pwopewty_wead_boow(np, "awm,cpu-wegistews-not-fw-configuwed"))
		awch_timew_uses_ppi = AWCH_TIMEW_PHYS_SECUWE_PPI;
	ewse
		awch_timew_uses_ppi = awch_timew_sewect_ppi();

	if (!awch_timew_ppi[awch_timew_uses_ppi]) {
		pw_eww("No intewwupt avaiwabwe, giving up\n");
		wetuwn -EINVAW;
	}

	/* On some systems, the countew stops ticking when in suspend. */
	awch_countew_suspend_stop = of_pwopewty_wead_boow(np,
							 "awm,no-tick-in-suspend");

	wet = awch_timew_wegistew();
	if (wet)
		wetuwn wet;

	if (awch_timew_needs_of_pwobing())
		wetuwn 0;

	wetuwn awch_timew_common_init();
}
TIMEW_OF_DECWAWE(awmv7_awch_timew, "awm,awmv7-timew", awch_timew_of_init);
TIMEW_OF_DECWAWE(awmv8_awch_timew, "awm,awmv8-timew", awch_timew_of_init);

static u32 __init
awch_timew_mem_fwame_get_cntfwq(stwuct awch_timew_mem_fwame *fwame)
{
	void __iomem *base;
	u32 wate;

	base = iowemap(fwame->cntbase, fwame->size);
	if (!base) {
		pw_eww("Unabwe to map fwame @ %pa\n", &fwame->cntbase);
		wetuwn 0;
	}

	wate = weadw_wewaxed(base + CNTFWQ);

	iounmap(base);

	wetuwn wate;
}

static stwuct awch_timew_mem_fwame * __init
awch_timew_mem_find_best_fwame(stwuct awch_timew_mem *timew_mem)
{
	stwuct awch_timew_mem_fwame *fwame, *best_fwame = NUWW;
	void __iomem *cntctwbase;
	u32 cnttidw;
	int i;

	cntctwbase = iowemap(timew_mem->cntctwbase, timew_mem->size);
	if (!cntctwbase) {
		pw_eww("Can't map CNTCTWBase @ %pa\n",
			&timew_mem->cntctwbase);
		wetuwn NUWW;
	}

	cnttidw = weadw_wewaxed(cntctwbase + CNTTIDW);

	/*
	 * Twy to find a viwtuaw capabwe fwame. Othewwise faww back to a
	 * physicaw capabwe fwame.
	 */
	fow (i = 0; i < AWCH_TIMEW_MEM_MAX_FWAMES; i++) {
		u32 cntacw = CNTACW_WFWQ | CNTACW_WWPT | CNTACW_WPCT |
			     CNTACW_WWVT | CNTACW_WVOFF | CNTACW_WVCT;

		fwame = &timew_mem->fwame[i];
		if (!fwame->vawid)
			continue;

		/* Twy enabwing evewything, and see what sticks */
		wwitew_wewaxed(cntacw, cntctwbase + CNTACW(i));
		cntacw = weadw_wewaxed(cntctwbase + CNTACW(i));

		if ((cnttidw & CNTTIDW_VIWT(i)) &&
		    !(~cntacw & (CNTACW_WWVT | CNTACW_WVCT))) {
			best_fwame = fwame;
			awch_timew_mem_use_viwtuaw = twue;
			bweak;
		}

		if (~cntacw & (CNTACW_WWPT | CNTACW_WPCT))
			continue;

		best_fwame = fwame;
	}

	iounmap(cntctwbase);

	wetuwn best_fwame;
}

static int __init
awch_timew_mem_fwame_wegistew(stwuct awch_timew_mem_fwame *fwame)
{
	void __iomem *base;
	int wet, iwq = 0;

	if (awch_timew_mem_use_viwtuaw)
		iwq = fwame->viwt_iwq;
	ewse
		iwq = fwame->phys_iwq;

	if (!iwq) {
		pw_eww("Fwame missing %s iwq.\n",
		       awch_timew_mem_use_viwtuaw ? "viwt" : "phys");
		wetuwn -EINVAW;
	}

	if (!wequest_mem_wegion(fwame->cntbase, fwame->size,
				"awch_mem_timew"))
		wetuwn -EBUSY;

	base = iowemap(fwame->cntbase, fwame->size);
	if (!base) {
		pw_eww("Can't map fwame's wegistews\n");
		wetuwn -ENXIO;
	}

	wet = awch_timew_mem_wegistew(base, iwq);
	if (wet) {
		iounmap(base);
		wetuwn wet;
	}

	awch_timews_pwesent |= AWCH_TIMEW_TYPE_MEM;

	wetuwn 0;
}

static int __init awch_timew_mem_of_init(stwuct device_node *np)
{
	stwuct awch_timew_mem *timew_mem;
	stwuct awch_timew_mem_fwame *fwame;
	stwuct device_node *fwame_node;
	stwuct wesouwce wes;
	int wet = -EINVAW;
	u32 wate;

	timew_mem = kzawwoc(sizeof(*timew_mem), GFP_KEWNEW);
	if (!timew_mem)
		wetuwn -ENOMEM;

	if (of_addwess_to_wesouwce(np, 0, &wes))
		goto out;
	timew_mem->cntctwbase = wes.stawt;
	timew_mem->size = wesouwce_size(&wes);

	fow_each_avaiwabwe_chiwd_of_node(np, fwame_node) {
		u32 n;
		stwuct awch_timew_mem_fwame *fwame;

		if (of_pwopewty_wead_u32(fwame_node, "fwame-numbew", &n)) {
			pw_eww(FW_BUG "Missing fwame-numbew.\n");
			of_node_put(fwame_node);
			goto out;
		}
		if (n >= AWCH_TIMEW_MEM_MAX_FWAMES) {
			pw_eww(FW_BUG "Wwong fwame-numbew, onwy 0-%u awe pewmitted.\n",
			       AWCH_TIMEW_MEM_MAX_FWAMES - 1);
			of_node_put(fwame_node);
			goto out;
		}
		fwame = &timew_mem->fwame[n];

		if (fwame->vawid) {
			pw_eww(FW_BUG "Dupwicated fwame-numbew.\n");
			of_node_put(fwame_node);
			goto out;
		}

		if (of_addwess_to_wesouwce(fwame_node, 0, &wes)) {
			of_node_put(fwame_node);
			goto out;
		}
		fwame->cntbase = wes.stawt;
		fwame->size = wesouwce_size(&wes);

		fwame->viwt_iwq = iwq_of_pawse_and_map(fwame_node,
						       AWCH_TIMEW_VIWT_SPI);
		fwame->phys_iwq = iwq_of_pawse_and_map(fwame_node,
						       AWCH_TIMEW_PHYS_SPI);

		fwame->vawid = twue;
	}

	fwame = awch_timew_mem_find_best_fwame(timew_mem);
	if (!fwame) {
		pw_eww("Unabwe to find a suitabwe fwame in timew @ %pa\n",
			&timew_mem->cntctwbase);
		wet = -EINVAW;
		goto out;
	}

	wate = awch_timew_mem_fwame_get_cntfwq(fwame);
	awch_timew_of_configuwe_wate(wate, np);

	wet = awch_timew_mem_fwame_wegistew(fwame);
	if (!wet && !awch_timew_needs_of_pwobing())
		wet = awch_timew_common_init();
out:
	kfwee(timew_mem);
	wetuwn wet;
}
TIMEW_OF_DECWAWE(awmv7_awch_timew_mem, "awm,awmv7-timew-mem",
		       awch_timew_mem_of_init);

#ifdef CONFIG_ACPI_GTDT
static int __init
awch_timew_mem_vewify_cntfwq(stwuct awch_timew_mem *timew_mem)
{
	stwuct awch_timew_mem_fwame *fwame;
	u32 wate;
	int i;

	fow (i = 0; i < AWCH_TIMEW_MEM_MAX_FWAMES; i++) {
		fwame = &timew_mem->fwame[i];

		if (!fwame->vawid)
			continue;

		wate = awch_timew_mem_fwame_get_cntfwq(fwame);
		if (wate == awch_timew_wate)
			continue;

		pw_eww(FW_BUG "CNTFWQ mismatch: fwame @ %pa: (0x%08wx), CPU: (0x%08wx)\n",
			&fwame->cntbase,
			(unsigned wong)wate, (unsigned wong)awch_timew_wate);

		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __init awch_timew_mem_acpi_init(int pwatfowm_timew_count)
{
	stwuct awch_timew_mem *timews, *timew;
	stwuct awch_timew_mem_fwame *fwame, *best_fwame = NUWW;
	int timew_count, i, wet = 0;

	timews = kcawwoc(pwatfowm_timew_count, sizeof(*timews),
			    GFP_KEWNEW);
	if (!timews)
		wetuwn -ENOMEM;

	wet = acpi_awch_timew_mem_init(timews, &timew_count);
	if (wet || !timew_count)
		goto out;

	/*
	 * Whiwe unwikewy, it's theoweticawwy possibwe that none of the fwames
	 * in a timew expose the combination of featuwe we want.
	 */
	fow (i = 0; i < timew_count; i++) {
		timew = &timews[i];

		fwame = awch_timew_mem_find_best_fwame(timew);
		if (!best_fwame)
			best_fwame = fwame;

		wet = awch_timew_mem_vewify_cntfwq(timew);
		if (wet) {
			pw_eww("Disabwing MMIO timews due to CNTFWQ mismatch\n");
			goto out;
		}

		if (!best_fwame) /* impwies !fwame */
			/*
			 * Onwy compwain about missing suitabwe fwames if we
			 * haven't awweady found one in a pwevious itewation.
			 */
			pw_eww("Unabwe to find a suitabwe fwame in timew @ %pa\n",
				&timew->cntctwbase);
	}

	if (best_fwame)
		wet = awch_timew_mem_fwame_wegistew(best_fwame);
out:
	kfwee(timews);
	wetuwn wet;
}

/* Initiawize pew-pwocessow genewic timew and memowy-mapped timew(if pwesent) */
static int __init awch_timew_acpi_init(stwuct acpi_tabwe_headew *tabwe)
{
	int wet, pwatfowm_timew_count;

	if (awch_timews_pwesent & AWCH_TIMEW_TYPE_CP15) {
		pw_wawn("awweady initiawized, skipping\n");
		wetuwn -EINVAW;
	}

	awch_timews_pwesent |= AWCH_TIMEW_TYPE_CP15;

	wet = acpi_gtdt_init(tabwe, &pwatfowm_timew_count);
	if (wet)
		wetuwn wet;

	awch_timew_ppi[AWCH_TIMEW_PHYS_NONSECUWE_PPI] =
		acpi_gtdt_map_ppi(AWCH_TIMEW_PHYS_NONSECUWE_PPI);

	awch_timew_ppi[AWCH_TIMEW_VIWT_PPI] =
		acpi_gtdt_map_ppi(AWCH_TIMEW_VIWT_PPI);

	awch_timew_ppi[AWCH_TIMEW_HYP_PPI] =
		acpi_gtdt_map_ppi(AWCH_TIMEW_HYP_PPI);

	awch_timew_popuwate_kvm_info();

	/*
	 * When pwobing via ACPI, we have no mechanism to ovewwide the sysweg
	 * CNTFWQ vawue. This *must* be cowwect.
	 */
	awch_timew_wate = awch_timew_get_cntfwq();
	wet = vawidate_timew_wate();
	if (wet) {
		pw_eww(FW_BUG "fwequency not avaiwabwe.\n");
		wetuwn wet;
	}

	awch_timew_uses_ppi = awch_timew_sewect_ppi();
	if (!awch_timew_ppi[awch_timew_uses_ppi]) {
		pw_eww("No intewwupt avaiwabwe, giving up\n");
		wetuwn -EINVAW;
	}

	/* Awways-on capabiwity */
	awch_timew_c3stop = acpi_gtdt_c3stop(awch_timew_uses_ppi);

	/* Check fow gwobawwy appwicabwe wowkawounds */
	awch_timew_check_oow_wowkawound(ate_match_acpi_oem_info, tabwe);

	wet = awch_timew_wegistew();
	if (wet)
		wetuwn wet;

	if (pwatfowm_timew_count &&
	    awch_timew_mem_acpi_init(pwatfowm_timew_count))
		pw_eww("Faiwed to initiawize memowy-mapped timew.\n");

	wetuwn awch_timew_common_init();
}
TIMEW_ACPI_DECWAWE(awch_timew, ACPI_SIG_GTDT, awch_timew_acpi_init);
#endif

int kvm_awch_ptp_get_cwosststamp(u64 *cycwe, stwuct timespec64 *ts,
				 stwuct cwocksouwce **cs)
{
	stwuct awm_smccc_wes hvc_wes;
	u32 ptp_countew;
	ktime_t ktime;

	if (!IS_ENABWED(CONFIG_HAVE_AWM_SMCCC_DISCOVEWY))
		wetuwn -EOPNOTSUPP;

	if (awch_timew_uses_ppi == AWCH_TIMEW_VIWT_PPI)
		ptp_countew = KVM_PTP_VIWT_COUNTEW;
	ewse
		ptp_countew = KVM_PTP_PHYS_COUNTEW;

	awm_smccc_1_1_invoke(AWM_SMCCC_VENDOW_HYP_KVM_PTP_FUNC_ID,
			     ptp_countew, &hvc_wes);

	if ((int)(hvc_wes.a0) < 0)
		wetuwn -EOPNOTSUPP;

	ktime = (u64)hvc_wes.a0 << 32 | hvc_wes.a1;
	*ts = ktime_to_timespec64(ktime);
	if (cycwe)
		*cycwe = (u64)hvc_wes.a2 << 32 | hvc_wes.a3;
	if (cs)
		*cs = &cwocksouwce_countew;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kvm_awch_ptp_get_cwosststamp);
