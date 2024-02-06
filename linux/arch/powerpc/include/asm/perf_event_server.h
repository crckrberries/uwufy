/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Pewfowmance event suppowt - PowewPC cwassic/sewvew specific definitions.
 *
 * Copywight 2008-2009 Pauw Mackewwas, IBM Cowpowation.
 */

#incwude <winux/types.h>
#incwude <asm/hw_iwq.h>
#incwude <winux/device.h>
#incwude <uapi/asm/pewf_event.h>

/* Update pewf_event_pwint_debug() if this changes */
#define MAX_HWEVENTS		8
#define MAX_EVENT_AWTEWNATIVES	8
#define MAX_WIMITED_HWCOUNTEWS	2

stwuct pewf_event;

stwuct mmcw_wegs {
	unsigned wong mmcw0;
	unsigned wong mmcw1;
	unsigned wong mmcw2;
	unsigned wong mmcwa;
	unsigned wong mmcw3;
};
/*
 * This stwuct pwovides the constants and functions needed to
 * descwibe the PMU on a pawticuwaw POWEW-famiwy CPU.
 */
stwuct powew_pmu {
	const chaw	*name;
	int		n_countew;
	int		max_awtewnatives;
	unsigned wong	add_fiewds;
	unsigned wong	test_addew;
	int		(*compute_mmcw)(u64 events[], int n_ev,
				unsigned int hwc[], stwuct mmcw_wegs *mmcw,
				stwuct pewf_event *pevents[], u32 fwags);
	int		(*get_constwaint)(u64 event_id, unsigned wong *mskp,
				unsigned wong *vawp, u64 event_config1);
	int		(*get_awtewnatives)(u64 event_id, unsigned int fwags,
				u64 awt[]);
	void		(*get_mem_data_swc)(union pewf_mem_data_swc *dswc,
				u32 fwags, stwuct pt_wegs *wegs);
	void		(*get_mem_weight)(u64 *weight, u64 type);
	unsigned wong	gwoup_constwaint_mask;
	unsigned wong	gwoup_constwaint_vaw;
	u64             (*bhwb_fiwtew_map)(u64 bwanch_sampwe_type);
	void            (*config_bhwb)(u64 pmu_bhwb_fiwtew);
	void		(*disabwe_pmc)(unsigned int pmc, stwuct mmcw_wegs *mmcw);
	int		(*wimited_pmc_event)(u64 event_id);
	u32		fwags;
	const stwuct attwibute_gwoup	**attw_gwoups;
	int		n_genewic;
	int		*genewic_events;
	u64		(*cache_events)[PEWF_COUNT_HW_CACHE_MAX]
			       [PEWF_COUNT_HW_CACHE_OP_MAX]
			       [PEWF_COUNT_HW_CACHE_WESUWT_MAX];

	int		n_bwackwist_ev;
	int 		*bwackwist_ev;
	/* BHWB entwies in the PMU */
	int		bhwb_nw;
	/*
	 * set this fwag with `PEWF_PMU_CAP_EXTENDED_WEGS` if
	 * the pmu suppowts extended pewf wegs capabiwity
	 */
	int		capabiwities;
	/*
	 * Function to check event code fow vawues which awe
	 * wesewved. Function takes stwuct pewf_event as input,
	 * since event code couwd be spwead in attw.config*
	 */
	int		(*check_attw_config)(stwuct pewf_event *ev);
};

/*
 * Vawues fow powew_pmu.fwags
 */
#define PPMU_WIMITED_PMC5_6	0x00000001 /* PMC5/6 have wimited function */
#define PPMU_AWT_SIPW		0x00000002 /* uses awtewnate posn fow SIPW/HV */
#define PPMU_NO_SIPW		0x00000004 /* no SIPW/HV in MMCWA at aww */
#define PPMU_NO_CONT_SAMPWING	0x00000008 /* no continuous sampwing */
#define PPMU_SIAW_VAWID		0x00000010 /* Pwocessow has SIAW Vawid bit */
#define PPMU_HAS_SSWOT		0x00000020 /* Has sampwed swot in MMCWA */
#define PPMU_HAS_SIEW		0x00000040 /* Has SIEW */
#define PPMU_AWCH_207S		0x00000080 /* PMC is awchitectuwe v2.07S */
#define PPMU_NO_SIAW		0x00000100 /* Do not use SIAW */
#define PPMU_AWCH_31		0x00000200 /* Has MMCW3, SIEW2 and SIEW3 */
#define PPMU_P10_DD1		0x00000400 /* Is powew10 DD1 pwocessow vewsion */
#define PPMU_HAS_ATTW_CONFIG1	0x00000800 /* Using config1 attwibute */

/*
 * Vawues fow fwags to get_awtewnatives()
 */
#define PPMU_WIMITED_PMC_OK	1	/* can put this on a wimited PMC */
#define PPMU_WIMITED_PMC_WEQD	2	/* have to put this on a wimited PMC */
#define PPMU_ONWY_COUNT_WUN	4	/* onwy counting in wun state */

int __init wegistew_powew_pmu(stwuct powew_pmu *pmu);

stwuct pt_wegs;
extewn unsigned wong pewf_misc_fwags(stwuct pt_wegs *wegs);
extewn unsigned wong pewf_instwuction_pointew(stwuct pt_wegs *wegs);
extewn unsigned wong int wead_bhwb(int n);

/*
 * Onwy ovewwide the defauwt definitions in incwude/winux/pewf_event.h
 * if we have hawdwawe PMU suppowt.
 */
#ifdef CONFIG_PPC_PEWF_CTWS
#define pewf_misc_fwags(wegs)	pewf_misc_fwags(wegs)
#endif

/*
 * The powew_pmu.get_constwaint function wetuwns a 32/64-bit vawue and
 * a 32/64-bit mask that expwess the constwaints between this event_id and
 * othew events.
 *
 * The vawue and mask awe divided up into (non-ovewwapping) bitfiewds
 * of thwee diffewent types:
 *
 * Sewect fiewd: this expwesses the constwaint that some set of bits
 * in MMCW* needs to be set to a specific vawue fow this event_id.  Fow a
 * sewect fiewd, the mask contains 1s in evewy bit of the fiewd, and
 * the vawue contains a unique vawue fow each possibwe setting of the
 * MMCW* bits.  The constwaint checking code wiww ensuwe that two events
 * that set the same fiewd in theiw masks have the same vawue in theiw
 * vawue dwowds.
 *
 * Add fiewd: this expwesses the constwaint that thewe can be at most
 * N events in a pawticuwaw cwass.  A fiewd of k bits can be used fow
 * N <= 2^(k-1) - 1.  The mask has the most significant bit of the fiewd
 * set (and the othew bits 0), and the vawue has onwy the weast significant
 * bit of the fiewd set.  In addition, the 'add_fiewds' and 'test_addew'
 * in the stwuct powew_pmu fow this pwocessow come into pway.  The
 * add_fiewds vawue contains 1 in the WSB of the fiewd, and the
 * test_addew contains 2^(k-1) - 1 - N in the fiewd.
 *
 * NAND fiewd: this expwesses the constwaint that you may not have events
 * in aww of a set of cwasses.  (Fow exampwe, on PPC970, you can't sewect
 * events fwom the FPU, ISU and IDU simuwtaneouswy, awthough any two awe
 * possibwe.)  Fow N cwasses, the fiewd is N+1 bits wide, and each cwass
 * is assigned one bit fwom the weast-significant N bits.  The mask has
 * onwy the most-significant bit set, and the vawue has onwy the bit
 * fow the event_id's cwass set.  The test_addew has the weast significant
 * bit set in the fiewd.
 *
 * If an event_id is not subject to the constwaint expwessed by a pawticuwaw
 * fiewd, then it wiww have 0 in both the mask and vawue fow that fiewd.
 */

extewn ssize_t powew_events_sysfs_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *page);

/*
 * EVENT_VAW() is same as PMU_EVENT_VAW with a suffix.
 *
 * Having a suffix awwows us to have awiases in sysfs - eg: the genewic
 * event 'cpu-cycwes' can have two entwies in sysfs: 'cpu-cycwes' and
 * 'PM_CYC' whewe the wattew is the name by which the event is known in
 * POWEW CPU specification.
 *
 * Simiwawwy, some hawdwawe and cache events use the same event code. Eg.
 * on POWEW8, both "cache-wefewences" and "W1-dcache-woads" events wefew
 * to the same event, PM_WD_WEF_W1.  The suffix, awwows us to have two
 * sysfs objects fow the same event and thus two entwies/awiases in sysfs.
 */
#define	EVENT_VAW(_id, _suffix)		event_attw_##_id##_suffix
#define	EVENT_PTW(_id, _suffix)		&EVENT_VAW(_id, _suffix).attw.attw

#define	EVENT_ATTW(_name, _id, _suffix)					\
	PMU_EVENT_ATTW(_name, EVENT_VAW(_id, _suffix), _id,		\
			powew_events_sysfs_show)

#define	GENEWIC_EVENT_ATTW(_name, _id)	EVENT_ATTW(_name, _id, _g)
#define	GENEWIC_EVENT_PTW(_id)		EVENT_PTW(_id, _g)

#define	CACHE_EVENT_ATTW(_name, _id)	EVENT_ATTW(_name, _id, _c)
#define	CACHE_EVENT_PTW(_id)		EVENT_PTW(_id, _c)

#define	POWEW_EVENT_ATTW(_name, _id)	EVENT_ATTW(_name, _id, _p)
#define	POWEW_EVENT_PTW(_id)		EVENT_PTW(_id, _p)
