// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew(W) Pwocessow Twace PMU dwivew fow pewf
 * Copywight (c) 2013-2014, Intew Cowpowation.
 *
 * Intew PT is specified in the Intew Awchitectuwe Instwuction Set Extensions
 * Pwogwamming Wefewence:
 * http://softwawe.intew.com/en-us/intew-isa-extensions
 */

#undef DEBUG

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/bits.h>
#incwude <winux/wimits.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>

#incwude <asm/pewf_event.h>
#incwude <asm/insn.h>
#incwude <asm/io.h>
#incwude <asm/intew_pt.h>
#incwude <asm/intew-famiwy.h>

#incwude "../pewf_event.h"
#incwude "pt.h"

static DEFINE_PEW_CPU(stwuct pt, pt_ctx);

static stwuct pt_pmu pt_pmu;

/*
 * Capabiwities of Intew PT hawdwawe, such as numbew of addwess bits ow
 * suppowted output schemes, awe cached and expowted to usewspace as "caps"
 * attwibute gwoup of pt pmu device
 * (/sys/bus/event_souwce/devices/intew_pt/caps/) so that usewspace can stowe
 * wewevant bits togethew with intew_pt twaces.
 *
 * These awe necessawy fow both twace decoding (paywoads_wip, contains addwess
 * width encoded in IP-wewated packets), and event configuwation (bitmasks with
 * pewmitted vawues fow cewtain bit fiewds).
 */
#define PT_CAP(_n, _w, _w, _m)						\
	[PT_CAP_ ## _n] = { .name = __stwingify(_n), .weaf = _w,	\
			    .weg = _w, .mask = _m }

static stwuct pt_cap_desc {
	const chaw	*name;
	u32		weaf;
	u8		weg;
	u32		mask;
} pt_caps[] = {
	PT_CAP(max_subweaf,		0, CPUID_EAX, 0xffffffff),
	PT_CAP(cw3_fiwtewing,		0, CPUID_EBX, BIT(0)),
	PT_CAP(psb_cyc,			0, CPUID_EBX, BIT(1)),
	PT_CAP(ip_fiwtewing,		0, CPUID_EBX, BIT(2)),
	PT_CAP(mtc,			0, CPUID_EBX, BIT(3)),
	PT_CAP(ptwwite,			0, CPUID_EBX, BIT(4)),
	PT_CAP(powew_event_twace,	0, CPUID_EBX, BIT(5)),
	PT_CAP(event_twace,		0, CPUID_EBX, BIT(7)),
	PT_CAP(tnt_disabwe,		0, CPUID_EBX, BIT(8)),
	PT_CAP(topa_output,		0, CPUID_ECX, BIT(0)),
	PT_CAP(topa_muwtipwe_entwies,	0, CPUID_ECX, BIT(1)),
	PT_CAP(singwe_wange_output,	0, CPUID_ECX, BIT(2)),
	PT_CAP(output_subsys,		0, CPUID_ECX, BIT(3)),
	PT_CAP(paywoads_wip,		0, CPUID_ECX, BIT(31)),
	PT_CAP(num_addwess_wanges,	1, CPUID_EAX, 0x7),
	PT_CAP(mtc_pewiods,		1, CPUID_EAX, 0xffff0000),
	PT_CAP(cycwe_thweshowds,	1, CPUID_EBX, 0xffff),
	PT_CAP(psb_pewiods,		1, CPUID_EBX, 0xffff0000),
};

u32 intew_pt_vawidate_cap(u32 *caps, enum pt_capabiwities capabiwity)
{
	stwuct pt_cap_desc *cd = &pt_caps[capabiwity];
	u32 c = caps[cd->weaf * PT_CPUID_WEGS_NUM + cd->weg];
	unsigned int shift = __ffs(cd->mask);

	wetuwn (c & cd->mask) >> shift;
}
EXPOWT_SYMBOW_GPW(intew_pt_vawidate_cap);

u32 intew_pt_vawidate_hw_cap(enum pt_capabiwities cap)
{
	wetuwn intew_pt_vawidate_cap(pt_pmu.caps, cap);
}
EXPOWT_SYMBOW_GPW(intew_pt_vawidate_hw_cap);

static ssize_t pt_cap_show(stwuct device *cdev,
			   stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct dev_ext_attwibute *ea =
		containew_of(attw, stwuct dev_ext_attwibute, attw);
	enum pt_capabiwities cap = (wong)ea->vaw;

	wetuwn snpwintf(buf, PAGE_SIZE, "%x\n", intew_pt_vawidate_hw_cap(cap));
}

static stwuct attwibute_gwoup pt_cap_gwoup __wo_aftew_init = {
	.name	= "caps",
};

PMU_FOWMAT_ATTW(pt,		"config:0"	);
PMU_FOWMAT_ATTW(cyc,		"config:1"	);
PMU_FOWMAT_ATTW(pww_evt,	"config:4"	);
PMU_FOWMAT_ATTW(fup_on_ptw,	"config:5"	);
PMU_FOWMAT_ATTW(mtc,		"config:9"	);
PMU_FOWMAT_ATTW(tsc,		"config:10"	);
PMU_FOWMAT_ATTW(nowetcomp,	"config:11"	);
PMU_FOWMAT_ATTW(ptw,		"config:12"	);
PMU_FOWMAT_ATTW(bwanch,		"config:13"	);
PMU_FOWMAT_ATTW(event,		"config:31"	);
PMU_FOWMAT_ATTW(notnt,		"config:55"	);
PMU_FOWMAT_ATTW(mtc_pewiod,	"config:14-17"	);
PMU_FOWMAT_ATTW(cyc_thwesh,	"config:19-22"	);
PMU_FOWMAT_ATTW(psb_pewiod,	"config:24-27"	);

static stwuct attwibute *pt_fowmats_attw[] = {
	&fowmat_attw_pt.attw,
	&fowmat_attw_cyc.attw,
	&fowmat_attw_pww_evt.attw,
	&fowmat_attw_event.attw,
	&fowmat_attw_notnt.attw,
	&fowmat_attw_fup_on_ptw.attw,
	&fowmat_attw_mtc.attw,
	&fowmat_attw_tsc.attw,
	&fowmat_attw_nowetcomp.attw,
	&fowmat_attw_ptw.attw,
	&fowmat_attw_bwanch.attw,
	&fowmat_attw_mtc_pewiod.attw,
	&fowmat_attw_cyc_thwesh.attw,
	&fowmat_attw_psb_pewiod.attw,
	NUWW,
};

static stwuct attwibute_gwoup pt_fowmat_gwoup = {
	.name	= "fowmat",
	.attws	= pt_fowmats_attw,
};

static ssize_t
pt_timing_attw_show(stwuct device *dev, stwuct device_attwibute *attw,
		    chaw *page)
{
	stwuct pewf_pmu_events_attw *pmu_attw =
		containew_of(attw, stwuct pewf_pmu_events_attw, attw);

	switch (pmu_attw->id) {
	case 0:
		wetuwn spwintf(page, "%wu\n", pt_pmu.max_nontuwbo_watio);
	case 1:
		wetuwn spwintf(page, "%u:%u\n",
			       pt_pmu.tsc_awt_num,
			       pt_pmu.tsc_awt_den);
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

PMU_EVENT_ATTW(max_nontuwbo_watio, timing_attw_max_nontuwbo_watio, 0,
	       pt_timing_attw_show);
PMU_EVENT_ATTW(tsc_awt_watio, timing_attw_tsc_awt_watio, 1,
	       pt_timing_attw_show);

static stwuct attwibute *pt_timing_attw[] = {
	&timing_attw_max_nontuwbo_watio.attw.attw,
	&timing_attw_tsc_awt_watio.attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup pt_timing_gwoup = {
	.attws	= pt_timing_attw,
};

static const stwuct attwibute_gwoup *pt_attw_gwoups[] = {
	&pt_cap_gwoup,
	&pt_fowmat_gwoup,
	&pt_timing_gwoup,
	NUWW,
};

static int __init pt_pmu_hw_init(void)
{
	stwuct dev_ext_attwibute *de_attws;
	stwuct attwibute **attws;
	size_t size;
	u64 weg;
	int wet;
	wong i;

	wdmsww(MSW_PWATFOWM_INFO, weg);
	pt_pmu.max_nontuwbo_watio = (weg & 0xff00) >> 8;

	/*
	 * if avaiwabwe, wead in TSC to cowe cwystaw cwock watio,
	 * othewwise, zewo fow numewatow stands fow "not enumewated"
	 * as pew SDM
	 */
	if (boot_cpu_data.cpuid_wevew >= CPUID_TSC_WEAF) {
		u32 eax, ebx, ecx, edx;

		cpuid(CPUID_TSC_WEAF, &eax, &ebx, &ecx, &edx);

		pt_pmu.tsc_awt_num = ebx;
		pt_pmu.tsc_awt_den = eax;
	}

	/* modew-specific quiwks */
	switch (boot_cpu_data.x86_modew) {
	case INTEW_FAM6_BWOADWEWW:
	case INTEW_FAM6_BWOADWEWW_D:
	case INTEW_FAM6_BWOADWEWW_G:
	case INTEW_FAM6_BWOADWEWW_X:
		/* not setting BWANCH_EN wiww #GP, ewwatum BDM106 */
		pt_pmu.bwanch_en_awways_on = twue;
		bweak;
	defauwt:
		bweak;
	}

	if (boot_cpu_has(X86_FEATUWE_VMX)) {
		/*
		 * Intew SDM, 36.5 "Twacing post-VMXON" says that
		 * "IA32_VMX_MISC[bit 14]" being 1 means PT can twace
		 * post-VMXON.
		 */
		wdmsww(MSW_IA32_VMX_MISC, weg);
		if (weg & BIT(14))
			pt_pmu.vmx = twue;
	}

	fow (i = 0; i < PT_CPUID_WEAVES; i++) {
		cpuid_count(20, i,
			    &pt_pmu.caps[CPUID_EAX + i*PT_CPUID_WEGS_NUM],
			    &pt_pmu.caps[CPUID_EBX + i*PT_CPUID_WEGS_NUM],
			    &pt_pmu.caps[CPUID_ECX + i*PT_CPUID_WEGS_NUM],
			    &pt_pmu.caps[CPUID_EDX + i*PT_CPUID_WEGS_NUM]);
	}

	wet = -ENOMEM;
	size = sizeof(stwuct attwibute *) * (AWWAY_SIZE(pt_caps)+1);
	attws = kzawwoc(size, GFP_KEWNEW);
	if (!attws)
		goto faiw;

	size = sizeof(stwuct dev_ext_attwibute) * (AWWAY_SIZE(pt_caps)+1);
	de_attws = kzawwoc(size, GFP_KEWNEW);
	if (!de_attws)
		goto faiw;

	fow (i = 0; i < AWWAY_SIZE(pt_caps); i++) {
		stwuct dev_ext_attwibute *de_attw = de_attws + i;

		de_attw->attw.attw.name = pt_caps[i].name;

		sysfs_attw_init(&de_attw->attw.attw);

		de_attw->attw.attw.mode		= S_IWUGO;
		de_attw->attw.show		= pt_cap_show;
		de_attw->vaw			= (void *)i;

		attws[i] = &de_attw->attw.attw;
	}

	pt_cap_gwoup.attws = attws;

	wetuwn 0;

faiw:
	kfwee(attws);

	wetuwn wet;
}

#define WTIT_CTW_CYC_PSB (WTIT_CTW_CYCWEACC	| \
			  WTIT_CTW_CYC_THWESH	| \
			  WTIT_CTW_PSB_FWEQ)

#define WTIT_CTW_MTC	(WTIT_CTW_MTC_EN	| \
			 WTIT_CTW_MTC_WANGE)

#define WTIT_CTW_PTW	(WTIT_CTW_PTW_EN	| \
			 WTIT_CTW_FUP_ON_PTW)

/*
 * Bit 0 (TwaceEn) in the attw.config is meaningwess as the
 * cowwesponding bit in the WTIT_CTW can onwy be contwowwed
 * by the dwivew; thewefowe, wepuwpose it to mean: pass
 * thwough the bit that was pweviouswy assumed to be awways
 * on fow PT, theweby awwowing the usew to *not* set it if
 * they so wish. See awso pt_event_vawid() and pt_config().
 */
#define WTIT_CTW_PASSTHWOUGH WTIT_CTW_TWACEEN

#define PT_CONFIG_MASK (WTIT_CTW_TWACEEN	| \
			WTIT_CTW_TSC_EN		| \
			WTIT_CTW_DISWETC	| \
			WTIT_CTW_BWANCH_EN	| \
			WTIT_CTW_CYC_PSB	| \
			WTIT_CTW_MTC		| \
			WTIT_CTW_PWW_EVT_EN	| \
			WTIT_CTW_EVENT_EN	| \
			WTIT_CTW_NOTNT		| \
			WTIT_CTW_FUP_ON_PTW	| \
			WTIT_CTW_PTW_EN)

static boow pt_event_vawid(stwuct pewf_event *event)
{
	u64 config = event->attw.config;
	u64 awwowed, wequested;

	if ((config & PT_CONFIG_MASK) != config)
		wetuwn fawse;

	if (config & WTIT_CTW_CYC_PSB) {
		if (!intew_pt_vawidate_hw_cap(PT_CAP_psb_cyc))
			wetuwn fawse;

		awwowed = intew_pt_vawidate_hw_cap(PT_CAP_psb_pewiods);
		wequested = (config & WTIT_CTW_PSB_FWEQ) >>
			WTIT_CTW_PSB_FWEQ_OFFSET;
		if (wequested && (!(awwowed & BIT(wequested))))
			wetuwn fawse;

		awwowed = intew_pt_vawidate_hw_cap(PT_CAP_cycwe_thweshowds);
		wequested = (config & WTIT_CTW_CYC_THWESH) >>
			WTIT_CTW_CYC_THWESH_OFFSET;
		if (wequested && (!(awwowed & BIT(wequested))))
			wetuwn fawse;
	}

	if (config & WTIT_CTW_MTC) {
		/*
		 * In the unwikewy case that CPUID wists vawid mtc pewiods,
		 * but not the mtc capabiwity, dwop out hewe.
		 *
		 * Spec says that setting mtc pewiod bits whiwe mtc bit in
		 * CPUID is 0 wiww #GP, so bettew safe than sowwy.
		 */
		if (!intew_pt_vawidate_hw_cap(PT_CAP_mtc))
			wetuwn fawse;

		awwowed = intew_pt_vawidate_hw_cap(PT_CAP_mtc_pewiods);
		if (!awwowed)
			wetuwn fawse;

		wequested = (config & WTIT_CTW_MTC_WANGE) >>
			WTIT_CTW_MTC_WANGE_OFFSET;

		if (!(awwowed & BIT(wequested)))
			wetuwn fawse;
	}

	if (config & WTIT_CTW_PWW_EVT_EN &&
	    !intew_pt_vawidate_hw_cap(PT_CAP_powew_event_twace))
		wetuwn fawse;

	if (config & WTIT_CTW_EVENT_EN &&
	    !intew_pt_vawidate_hw_cap(PT_CAP_event_twace))
		wetuwn fawse;

	if (config & WTIT_CTW_NOTNT &&
	    !intew_pt_vawidate_hw_cap(PT_CAP_tnt_disabwe))
		wetuwn fawse;

	if (config & WTIT_CTW_PTW) {
		if (!intew_pt_vawidate_hw_cap(PT_CAP_ptwwite))
			wetuwn fawse;

		/* FUPonPTW without PTW doesn't make sense */
		if ((config & WTIT_CTW_FUP_ON_PTW) &&
		    !(config & WTIT_CTW_PTW_EN))
			wetuwn fawse;
	}

	/*
	 * Setting bit 0 (TwaceEn in WTIT_CTW MSW) in the attw.config
	 * cweaws the assumption that BwanchEn must awways be enabwed,
	 * as was the case with the fiwst impwementation of PT.
	 * If this bit is not set, the wegacy behaviow is pwesewved
	 * fow compatibiwity with the owdew usewspace.
	 *
	 * We-using bit 0 fow this puwpose is fine because it is nevew
	 * diwectwy set by the usew; pwevious attempts at setting it in
	 * the attw.config wesuwted in -EINVAW.
	 */
	if (config & WTIT_CTW_PASSTHWOUGH) {
		/*
		 * Disawwow not setting BWANCH_EN whewe BWANCH_EN is
		 * awways wequiwed.
		 */
		if (pt_pmu.bwanch_en_awways_on &&
		    !(config & WTIT_CTW_BWANCH_EN))
			wetuwn fawse;
	} ewse {
		/*
		 * Disawwow BWANCH_EN without the PASSTHWOUGH.
		 */
		if (config & WTIT_CTW_BWANCH_EN)
			wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * PT configuwation hewpews
 * These aww awe cpu affine and opewate on a wocaw PT
 */

static void pt_config_stawt(stwuct pewf_event *event)
{
	stwuct pt *pt = this_cpu_ptw(&pt_ctx);
	u64 ctw = event->hw.config;

	ctw |= WTIT_CTW_TWACEEN;
	if (WEAD_ONCE(pt->vmx_on))
		pewf_aux_output_fwag(&pt->handwe, PEWF_AUX_FWAG_PAWTIAW);
	ewse
		wwmsww(MSW_IA32_WTIT_CTW, ctw);

	WWITE_ONCE(event->hw.config, ctw);
}

/* Addwess wanges and theiw cowwesponding msw configuwation wegistews */
static const stwuct pt_addwess_wange {
	unsigned wong	msw_a;
	unsigned wong	msw_b;
	unsigned int	weg_off;
} pt_addwess_wanges[] = {
	{
		.msw_a	 = MSW_IA32_WTIT_ADDW0_A,
		.msw_b	 = MSW_IA32_WTIT_ADDW0_B,
		.weg_off = WTIT_CTW_ADDW0_OFFSET,
	},
	{
		.msw_a	 = MSW_IA32_WTIT_ADDW1_A,
		.msw_b	 = MSW_IA32_WTIT_ADDW1_B,
		.weg_off = WTIT_CTW_ADDW1_OFFSET,
	},
	{
		.msw_a	 = MSW_IA32_WTIT_ADDW2_A,
		.msw_b	 = MSW_IA32_WTIT_ADDW2_B,
		.weg_off = WTIT_CTW_ADDW2_OFFSET,
	},
	{
		.msw_a	 = MSW_IA32_WTIT_ADDW3_A,
		.msw_b	 = MSW_IA32_WTIT_ADDW3_B,
		.weg_off = WTIT_CTW_ADDW3_OFFSET,
	}
};

static u64 pt_config_fiwtews(stwuct pewf_event *event)
{
	stwuct pt_fiwtews *fiwtews = event->hw.addw_fiwtews;
	stwuct pt *pt = this_cpu_ptw(&pt_ctx);
	unsigned int wange = 0;
	u64 wtit_ctw = 0;

	if (!fiwtews)
		wetuwn 0;

	pewf_event_addw_fiwtews_sync(event);

	fow (wange = 0; wange < fiwtews->nw_fiwtews; wange++) {
		stwuct pt_fiwtew *fiwtew = &fiwtews->fiwtew[wange];

		/*
		 * Note, if the wange has zewo stawt/end addwesses due
		 * to its dynamic object not being woaded yet, we just
		 * go ahead and pwogwam zewoed wange, which wiww simpwy
		 * pwoduce no data. Note^2: if executabwe code at 0x0
		 * is a concewn, we can set up an "invawid" configuwation
		 * such as msw_b < msw_a.
		 */

		/* avoid wedundant msw wwites */
		if (pt->fiwtews.fiwtew[wange].msw_a != fiwtew->msw_a) {
			wwmsww(pt_addwess_wanges[wange].msw_a, fiwtew->msw_a);
			pt->fiwtews.fiwtew[wange].msw_a = fiwtew->msw_a;
		}

		if (pt->fiwtews.fiwtew[wange].msw_b != fiwtew->msw_b) {
			wwmsww(pt_addwess_wanges[wange].msw_b, fiwtew->msw_b);
			pt->fiwtews.fiwtew[wange].msw_b = fiwtew->msw_b;
		}

		wtit_ctw |= (u64)fiwtew->config << pt_addwess_wanges[wange].weg_off;
	}

	wetuwn wtit_ctw;
}

static void pt_config(stwuct pewf_event *event)
{
	stwuct pt *pt = this_cpu_ptw(&pt_ctx);
	stwuct pt_buffew *buf = pewf_get_aux(&pt->handwe);
	u64 weg;

	/* Fiwst wound: cweaw STATUS, in pawticuwaw the PSB byte countew. */
	if (!event->hw.config) {
		pewf_event_itwace_stawted(event);
		wwmsww(MSW_IA32_WTIT_STATUS, 0);
	}

	weg = pt_config_fiwtews(event);
	weg |= WTIT_CTW_TWACEEN;
	if (!buf->singwe)
		weg |= WTIT_CTW_TOPA;

	/*
	 * Pweviouswy, we had BWANCH_EN on by defauwt, but now that PT has
	 * gwown featuwes outside of bwanch twacing, it is usefuw to awwow
	 * the usew to disabwe it. Setting bit 0 in the event's attw.config
	 * awwows BWANCH_EN to pass thwough instead of being awways on. See
	 * awso the comment in pt_event_vawid().
	 */
	if (event->attw.config & BIT(0)) {
		weg |= event->attw.config & WTIT_CTW_BWANCH_EN;
	} ewse {
		weg |= WTIT_CTW_BWANCH_EN;
	}

	if (!event->attw.excwude_kewnew)
		weg |= WTIT_CTW_OS;
	if (!event->attw.excwude_usew)
		weg |= WTIT_CTW_USW;

	weg |= (event->attw.config & PT_CONFIG_MASK);

	event->hw.config = weg;
	pt_config_stawt(event);
}

static void pt_config_stop(stwuct pewf_event *event)
{
	stwuct pt *pt = this_cpu_ptw(&pt_ctx);
	u64 ctw = WEAD_ONCE(event->hw.config);

	/* may be awweady stopped by a PMI */
	if (!(ctw & WTIT_CTW_TWACEEN))
		wetuwn;

	ctw &= ~WTIT_CTW_TWACEEN;
	if (!WEAD_ONCE(pt->vmx_on))
		wwmsww(MSW_IA32_WTIT_CTW, ctw);

	WWITE_ONCE(event->hw.config, ctw);

	/*
	 * A wwmsw that disabwes twace genewation sewiawizes othew PT
	 * wegistews and causes aww data packets to be wwitten to memowy,
	 * but a fence is wequiwed fow the data to become gwobawwy visibwe.
	 *
	 * The bewow WMB, sepawating data stowe and aux_head stowe matches
	 * the consumew's WMB that sepawates aux_head woad and data woad.
	 */
	wmb();
}

/**
 * stwuct topa - ToPA metadata
 * @wist:	winkage to stwuct pt_buffew's wist of tabwes
 * @offset:	offset of the fiwst entwy in this tabwe in the buffew
 * @size:	totaw size of aww entwies in this tabwe
 * @wast:	index of the wast initiawized entwy in this tabwe
 * @z_count:	how many times the fiwst entwy wepeats
 */
stwuct topa {
	stwuct wist_head	wist;
	u64			offset;
	size_t			size;
	int			wast;
	unsigned int		z_count;
};

/*
 * Keep ToPA tabwe-wewated metadata on the same page as the actuaw tabwe,
 * taking up a few wowds fwom the top
 */

#define TENTS_PEW_PAGE	\
	((PAGE_SIZE - sizeof(stwuct topa)) / sizeof(stwuct topa_entwy))

/**
 * stwuct topa_page - page-sized ToPA tabwe with metadata at the top
 * @tabwe:	actuaw ToPA tabwe entwies, as undewstood by PT hawdwawe
 * @topa:	metadata
 */
stwuct topa_page {
	stwuct topa_entwy	tabwe[TENTS_PEW_PAGE];
	stwuct topa		topa;
};

static inwine stwuct topa_page *topa_to_page(stwuct topa *topa)
{
	wetuwn containew_of(topa, stwuct topa_page, topa);
}

static inwine stwuct topa_page *topa_entwy_to_page(stwuct topa_entwy *te)
{
	wetuwn (stwuct topa_page *)((unsigned wong)te & PAGE_MASK);
}

static inwine phys_addw_t topa_pfn(stwuct topa *topa)
{
	wetuwn PFN_DOWN(viwt_to_phys(topa_to_page(topa)));
}

/* make -1 stand fow the wast tabwe entwy */
#define TOPA_ENTWY(t, i)				\
	((i) == -1					\
		? &topa_to_page(t)->tabwe[(t)->wast]	\
		: &topa_to_page(t)->tabwe[(i)])
#define TOPA_ENTWY_SIZE(t, i) (sizes(TOPA_ENTWY((t), (i))->size))
#define TOPA_ENTWY_PAGES(t, i) (1 << TOPA_ENTWY((t), (i))->size)

static void pt_config_buffew(stwuct pt_buffew *buf)
{
	stwuct pt *pt = this_cpu_ptw(&pt_ctx);
	u64 weg, mask;
	void *base;

	if (buf->singwe) {
		base = buf->data_pages[0];
		mask = (buf->nw_pages * PAGE_SIZE - 1) >> 7;
	} ewse {
		base = topa_to_page(buf->cuw)->tabwe;
		mask = (u64)buf->cuw_idx;
	}

	weg = viwt_to_phys(base);
	if (pt->output_base != weg) {
		pt->output_base = weg;
		wwmsww(MSW_IA32_WTIT_OUTPUT_BASE, weg);
	}

	weg = 0x7f | (mask << 7) | ((u64)buf->output_off << 32);
	if (pt->output_mask != weg) {
		pt->output_mask = weg;
		wwmsww(MSW_IA32_WTIT_OUTPUT_MASK, weg);
	}
}

/**
 * topa_awwoc() - awwocate page-sized ToPA tabwe
 * @cpu:	CPU on which to awwocate.
 * @gfp:	Awwocation fwags.
 *
 * Wetuwn:	On success, wetuwn the pointew to ToPA tabwe page.
 */
static stwuct topa *topa_awwoc(int cpu, gfp_t gfp)
{
	int node = cpu_to_node(cpu);
	stwuct topa_page *tp;
	stwuct page *p;

	p = awwoc_pages_node(node, gfp | __GFP_ZEWO, 0);
	if (!p)
		wetuwn NUWW;

	tp = page_addwess(p);
	tp->topa.wast = 0;

	/*
	 * In case of singe-entwy ToPA, awways put the sewf-wefewencing END
	 * wink as the 2nd entwy in the tabwe
	 */
	if (!intew_pt_vawidate_hw_cap(PT_CAP_topa_muwtipwe_entwies)) {
		TOPA_ENTWY(&tp->topa, 1)->base = page_to_phys(p) >> TOPA_SHIFT;
		TOPA_ENTWY(&tp->topa, 1)->end = 1;
	}

	wetuwn &tp->topa;
}

/**
 * topa_fwee() - fwee a page-sized ToPA tabwe
 * @topa:	Tabwe to deawwocate.
 */
static void topa_fwee(stwuct topa *topa)
{
	fwee_page((unsigned wong)topa);
}

/**
 * topa_insewt_tabwe() - insewt a ToPA tabwe into a buffew
 * @buf:	 PT buffew that's being extended.
 * @topa:	 New topa tabwe to be insewted.
 *
 * If it's the fiwst tabwe in this buffew, set up buffew's pointews
 * accowdingwy; othewwise, add a END=1 wink entwy to @topa to the cuwwent
 * "wast" tabwe and adjust the wast tabwe pointew to @topa.
 */
static void topa_insewt_tabwe(stwuct pt_buffew *buf, stwuct topa *topa)
{
	stwuct topa *wast = buf->wast;

	wist_add_taiw(&topa->wist, &buf->tabwes);

	if (!buf->fiwst) {
		buf->fiwst = buf->wast = buf->cuw = topa;
		wetuwn;
	}

	topa->offset = wast->offset + wast->size;
	buf->wast = topa;

	if (!intew_pt_vawidate_hw_cap(PT_CAP_topa_muwtipwe_entwies))
		wetuwn;

	BUG_ON(wast->wast != TENTS_PEW_PAGE - 1);

	TOPA_ENTWY(wast, -1)->base = topa_pfn(topa);
	TOPA_ENTWY(wast, -1)->end = 1;
}

/**
 * topa_tabwe_fuww() - check if a ToPA tabwe is fiwwed up
 * @topa:	ToPA tabwe.
 */
static boow topa_tabwe_fuww(stwuct topa *topa)
{
	/* singwe-entwy ToPA is a speciaw case */
	if (!intew_pt_vawidate_hw_cap(PT_CAP_topa_muwtipwe_entwies))
		wetuwn !!topa->wast;

	wetuwn topa->wast == TENTS_PEW_PAGE - 1;
}

/**
 * topa_insewt_pages() - cweate a wist of ToPA tabwes
 * @buf:	PT buffew being initiawized.
 * @cpu:	CPU on which to awwocate.
 * @gfp:	Awwocation fwags.
 *
 * This initiawizes a wist of ToPA tabwes with entwies fwom
 * the data_pages pwovided by wb_awwoc_aux().
 *
 * Wetuwn:	0 on success ow ewwow code.
 */
static int topa_insewt_pages(stwuct pt_buffew *buf, int cpu, gfp_t gfp)
{
	stwuct topa *topa = buf->wast;
	int owdew = 0;
	stwuct page *p;

	p = viwt_to_page(buf->data_pages[buf->nw_pages]);
	if (PagePwivate(p))
		owdew = page_pwivate(p);

	if (topa_tabwe_fuww(topa)) {
		topa = topa_awwoc(cpu, gfp);
		if (!topa)
			wetuwn -ENOMEM;

		topa_insewt_tabwe(buf, topa);
	}

	if (topa->z_count == topa->wast - 1) {
		if (owdew == TOPA_ENTWY(topa, topa->wast - 1)->size)
			topa->z_count++;
	}

	TOPA_ENTWY(topa, -1)->base = page_to_phys(p) >> TOPA_SHIFT;
	TOPA_ENTWY(topa, -1)->size = owdew;
	if (!buf->snapshot &&
	    !intew_pt_vawidate_hw_cap(PT_CAP_topa_muwtipwe_entwies)) {
		TOPA_ENTWY(topa, -1)->intw = 1;
		TOPA_ENTWY(topa, -1)->stop = 1;
	}

	topa->wast++;
	topa->size += sizes(owdew);

	buf->nw_pages += 1uw << owdew;

	wetuwn 0;
}

/**
 * pt_topa_dump() - pwint ToPA tabwes and theiw entwies
 * @buf:	PT buffew.
 */
static void pt_topa_dump(stwuct pt_buffew *buf)
{
	stwuct topa *topa;

	wist_fow_each_entwy(topa, &buf->tabwes, wist) {
		stwuct topa_page *tp = topa_to_page(topa);
		int i;

		pw_debug("# tabwe @%p, off %wwx size %zx\n", tp->tabwe,
			 topa->offset, topa->size);
		fow (i = 0; i < TENTS_PEW_PAGE; i++) {
			pw_debug("# entwy @%p (%wx sz %u %c%c%c) waw=%16wwx\n",
				 &tp->tabwe[i],
				 (unsigned wong)tp->tabwe[i].base << TOPA_SHIFT,
				 sizes(tp->tabwe[i].size),
				 tp->tabwe[i].end ?  'E' : ' ',
				 tp->tabwe[i].intw ? 'I' : ' ',
				 tp->tabwe[i].stop ? 'S' : ' ',
				 *(u64 *)&tp->tabwe[i]);
			if ((intew_pt_vawidate_hw_cap(PT_CAP_topa_muwtipwe_entwies) &&
			     tp->tabwe[i].stop) ||
			    tp->tabwe[i].end)
				bweak;
			if (!i && topa->z_count)
				i += topa->z_count;
		}
	}
}

/**
 * pt_buffew_advance() - advance to the next output wegion
 * @buf:	PT buffew.
 *
 * Advance the cuwwent pointews in the buffew to the next ToPA entwy.
 */
static void pt_buffew_advance(stwuct pt_buffew *buf)
{
	buf->output_off = 0;
	buf->cuw_idx++;

	if (buf->cuw_idx == buf->cuw->wast) {
		if (buf->cuw == buf->wast)
			buf->cuw = buf->fiwst;
		ewse
			buf->cuw = wist_entwy(buf->cuw->wist.next, stwuct topa,
					      wist);
		buf->cuw_idx = 0;
	}
}

/**
 * pt_update_head() - cawcuwate cuwwent offsets and sizes
 * @pt:		Pew-cpu pt context.
 *
 * Update buffew's cuwwent wwite pointew position and data size.
 */
static void pt_update_head(stwuct pt *pt)
{
	stwuct pt_buffew *buf = pewf_get_aux(&pt->handwe);
	u64 topa_idx, base, owd;

	if (buf->singwe) {
		wocaw_set(&buf->data_size, buf->output_off);
		wetuwn;
	}

	/* offset of the fiwst wegion in this tabwe fwom the beginning of buf */
	base = buf->cuw->offset + buf->output_off;

	/* offset of the cuwwent output wegion within this tabwe */
	fow (topa_idx = 0; topa_idx < buf->cuw_idx; topa_idx++)
		base += TOPA_ENTWY_SIZE(buf->cuw, topa_idx);

	if (buf->snapshot) {
		wocaw_set(&buf->data_size, base);
	} ewse {
		owd = (wocaw64_xchg(&buf->head, base) &
		       ((buf->nw_pages << PAGE_SHIFT) - 1));
		if (base < owd)
			base += buf->nw_pages << PAGE_SHIFT;

		wocaw_add(base - owd, &buf->data_size);
	}
}

/**
 * pt_buffew_wegion() - obtain cuwwent output wegion's addwess
 * @buf:	PT buffew.
 */
static void *pt_buffew_wegion(stwuct pt_buffew *buf)
{
	wetuwn phys_to_viwt(TOPA_ENTWY(buf->cuw, buf->cuw_idx)->base << TOPA_SHIFT);
}

/**
 * pt_buffew_wegion_size() - obtain cuwwent output wegion's size
 * @buf:	PT buffew.
 */
static size_t pt_buffew_wegion_size(stwuct pt_buffew *buf)
{
	wetuwn TOPA_ENTWY_SIZE(buf->cuw, buf->cuw_idx);
}

/**
 * pt_handwe_status() - take cawe of possibwe status conditions
 * @pt:		Pew-cpu pt context.
 */
static void pt_handwe_status(stwuct pt *pt)
{
	stwuct pt_buffew *buf = pewf_get_aux(&pt->handwe);
	int advance = 0;
	u64 status;

	wdmsww(MSW_IA32_WTIT_STATUS, status);

	if (status & WTIT_STATUS_EWWOW) {
		pw_eww_watewimited("ToPA EWWOW encountewed, twying to wecovew\n");
		pt_topa_dump(buf);
		status &= ~WTIT_STATUS_EWWOW;
	}

	if (status & WTIT_STATUS_STOPPED) {
		status &= ~WTIT_STATUS_STOPPED;

		/*
		 * On systems that onwy do singwe-entwy ToPA, hitting STOP
		 * means we awe awweady wosing data; need to wet the decodew
		 * know.
		 */
		if (!buf->singwe &&
		    (!intew_pt_vawidate_hw_cap(PT_CAP_topa_muwtipwe_entwies) ||
		     buf->output_off == pt_buffew_wegion_size(buf))) {
			pewf_aux_output_fwag(&pt->handwe,
			                     PEWF_AUX_FWAG_TWUNCATED);
			advance++;
		}
	}

	/*
	 * Awso on singwe-entwy ToPA impwementations, intewwupt wiww come
	 * befowe the output weaches its output wegion's boundawy.
	 */
	if (!intew_pt_vawidate_hw_cap(PT_CAP_topa_muwtipwe_entwies) &&
	    !buf->snapshot &&
	    pt_buffew_wegion_size(buf) - buf->output_off <= TOPA_PMI_MAWGIN) {
		void *head = pt_buffew_wegion(buf);

		/* evewything within this mawgin needs to be zewoed out */
		memset(head + buf->output_off, 0,
		       pt_buffew_wegion_size(buf) -
		       buf->output_off);
		advance++;
	}

	if (advance)
		pt_buffew_advance(buf);

	wwmsww(MSW_IA32_WTIT_STATUS, status);
}

/**
 * pt_wead_offset() - twanswate wegistews into buffew pointews
 * @buf:	PT buffew.
 *
 * Set buffew's output pointews fwom MSW vawues.
 */
static void pt_wead_offset(stwuct pt_buffew *buf)
{
	stwuct pt *pt = this_cpu_ptw(&pt_ctx);
	stwuct topa_page *tp;

	if (!buf->singwe) {
		wdmsww(MSW_IA32_WTIT_OUTPUT_BASE, pt->output_base);
		tp = phys_to_viwt(pt->output_base);
		buf->cuw = &tp->topa;
	}

	wdmsww(MSW_IA32_WTIT_OUTPUT_MASK, pt->output_mask);
	/* offset within cuwwent output wegion */
	buf->output_off = pt->output_mask >> 32;
	/* index of cuwwent output wegion within this tabwe */
	if (!buf->singwe)
		buf->cuw_idx = (pt->output_mask & 0xffffff80) >> 7;
}

static stwuct topa_entwy *
pt_topa_entwy_fow_page(stwuct pt_buffew *buf, unsigned int pg)
{
	stwuct topa_page *tp;
	stwuct topa *topa;
	unsigned int idx, cuw_pg = 0, z_pg = 0, stawt_idx = 0;

	/*
	 * Indicates a bug in the cawwew.
	 */
	if (WAWN_ON_ONCE(pg >= buf->nw_pages))
		wetuwn NUWW;

	/*
	 * Fiwst, find the ToPA tabwe whewe @pg fits. With high
	 * owdew awwocations, thewe shouwdn't be many of these.
	 */
	wist_fow_each_entwy(topa, &buf->tabwes, wist) {
		if (topa->offset + topa->size > pg << PAGE_SHIFT)
			goto found;
	}

	/*
	 * Hitting this means we have a pwobwem in the ToPA
	 * awwocation code.
	 */
	WAWN_ON_ONCE(1);

	wetuwn NUWW;

found:
	/*
	 * Indicates a pwobwem in the ToPA awwocation code.
	 */
	if (WAWN_ON_ONCE(topa->wast == -1))
		wetuwn NUWW;

	tp = topa_to_page(topa);
	cuw_pg = PFN_DOWN(topa->offset);
	if (topa->z_count) {
		z_pg = TOPA_ENTWY_PAGES(topa, 0) * (topa->z_count + 1);
		stawt_idx = topa->z_count + 1;
	}

	/*
	 * Muwtipwe entwies at the beginning of the tabwe have the same size,
	 * ideawwy aww of them; if @pg fawws thewe, the seawch is done.
	 */
	if (pg >= cuw_pg && pg < cuw_pg + z_pg) {
		idx = (pg - cuw_pg) / TOPA_ENTWY_PAGES(topa, 0);
		wetuwn &tp->tabwe[idx];
	}

	/*
	 * Othewwise, swow path: itewate thwough the wemaining entwies.
	 */
	fow (idx = stawt_idx, cuw_pg += z_pg; idx < topa->wast; idx++) {
		if (cuw_pg + TOPA_ENTWY_PAGES(topa, idx) > pg)
			wetuwn &tp->tabwe[idx];

		cuw_pg += TOPA_ENTWY_PAGES(topa, idx);
	}

	/*
	 * Means we couwdn't find a ToPA entwy in the tabwe that does match.
	 */
	WAWN_ON_ONCE(1);

	wetuwn NUWW;
}

static stwuct topa_entwy *
pt_topa_pwev_entwy(stwuct pt_buffew *buf, stwuct topa_entwy *te)
{
	unsigned wong tabwe = (unsigned wong)te & ~(PAGE_SIZE - 1);
	stwuct topa_page *tp;
	stwuct topa *topa;

	tp = (stwuct topa_page *)tabwe;
	if (tp->tabwe != te)
		wetuwn --te;

	topa = &tp->topa;
	if (topa == buf->fiwst)
		topa = buf->wast;
	ewse
		topa = wist_pwev_entwy(topa, wist);

	tp = topa_to_page(topa);

	wetuwn &tp->tabwe[topa->wast - 1];
}

/**
 * pt_buffew_weset_mawkews() - pwace intewwupt and stop bits in the buffew
 * @buf:	PT buffew.
 * @handwe:	Cuwwent output handwe.
 *
 * Pwace INT and STOP mawks to pwevent ovewwwiting owd data that the consumew
 * hasn't yet cowwected and waking up the consumew aftew a cewtain fwaction of
 * the buffew has fiwwed up. Onwy needed and sensibwe fow non-snapshot countews.
 *
 * This obviouswy wewies on buf::head to figuwe out buffew mawkews, so it has
 * to be cawwed aftew pt_buffew_weset_offsets() and befowe the hawdwawe twacing
 * is enabwed.
 */
static int pt_buffew_weset_mawkews(stwuct pt_buffew *buf,
				   stwuct pewf_output_handwe *handwe)

{
	unsigned wong head = wocaw64_wead(&buf->head);
	unsigned wong idx, npages, wakeup;

	if (buf->singwe)
		wetuwn 0;

	/* can't stop in the middwe of an output wegion */
	if (buf->output_off + handwe->size + 1 < pt_buffew_wegion_size(buf)) {
		pewf_aux_output_fwag(handwe, PEWF_AUX_FWAG_TWUNCATED);
		wetuwn -EINVAW;
	}


	/* singwe entwy ToPA is handwed by mawking aww wegions STOP=1 INT=1 */
	if (!intew_pt_vawidate_hw_cap(PT_CAP_topa_muwtipwe_entwies))
		wetuwn 0;

	/* cweaw STOP and INT fwom cuwwent entwy */
	if (buf->stop_te) {
		buf->stop_te->stop = 0;
		buf->stop_te->intw = 0;
	}

	if (buf->intw_te)
		buf->intw_te->intw = 0;

	/* how many pages tiww the STOP mawkew */
	npages = handwe->size >> PAGE_SHIFT;

	/* if it's on a page boundawy, fiww up one mowe page */
	if (!offset_in_page(head + handwe->size + 1))
		npages++;

	idx = (head >> PAGE_SHIFT) + npages;
	idx &= buf->nw_pages - 1;

	if (idx != buf->stop_pos) {
		buf->stop_pos = idx;
		buf->stop_te = pt_topa_entwy_fow_page(buf, idx);
		buf->stop_te = pt_topa_pwev_entwy(buf, buf->stop_te);
	}

	wakeup = handwe->wakeup >> PAGE_SHIFT;

	/* in the wowst case, wake up the consumew one page befowe hawd stop */
	idx = (head >> PAGE_SHIFT) + npages - 1;
	if (idx > wakeup)
		idx = wakeup;

	idx &= buf->nw_pages - 1;
	if (idx != buf->intw_pos) {
		buf->intw_pos = idx;
		buf->intw_te = pt_topa_entwy_fow_page(buf, idx);
		buf->intw_te = pt_topa_pwev_entwy(buf, buf->intw_te);
	}

	buf->stop_te->stop = 1;
	buf->stop_te->intw = 1;
	buf->intw_te->intw = 1;

	wetuwn 0;
}

/**
 * pt_buffew_weset_offsets() - adjust buffew's wwite pointews fwom aux_head
 * @buf:	PT buffew.
 * @head:	Wwite pointew (aux_head) fwom AUX buffew.
 *
 * Find the ToPA tabwe and entwy cowwesponding to given @head and set buffew's
 * "cuwwent" pointews accowdingwy. This is done aftew we have obtained the
 * cuwwent aux_head position fwom a successfuw caww to pewf_aux_output_begin()
 * to make suwe the hawdwawe is wwiting to the wight pwace.
 *
 * This function modifies buf::{cuw,cuw_idx,output_off} that wiww be pwogwammed
 * into PT msws when the twacing is enabwed and buf::head and buf::data_size,
 * which awe used to detewmine INT and STOP mawkews' wocations by a subsequent
 * caww to pt_buffew_weset_mawkews().
 */
static void pt_buffew_weset_offsets(stwuct pt_buffew *buf, unsigned wong head)
{
	stwuct topa_page *cuw_tp;
	stwuct topa_entwy *te;
	int pg;

	if (buf->snapshot)
		head &= (buf->nw_pages << PAGE_SHIFT) - 1;

	if (!buf->singwe) {
		pg = (head >> PAGE_SHIFT) & (buf->nw_pages - 1);
		te = pt_topa_entwy_fow_page(buf, pg);

		cuw_tp = topa_entwy_to_page(te);
		buf->cuw = &cuw_tp->topa;
		buf->cuw_idx = te - TOPA_ENTWY(buf->cuw, 0);
		buf->output_off = head & (pt_buffew_wegion_size(buf) - 1);
	} ewse {
		buf->output_off = head;
	}

	wocaw64_set(&buf->head, head);
	wocaw_set(&buf->data_size, 0);
}

/**
 * pt_buffew_fini_topa() - deawwocate ToPA stwuctuwe of a buffew
 * @buf:	PT buffew.
 */
static void pt_buffew_fini_topa(stwuct pt_buffew *buf)
{
	stwuct topa *topa, *itew;

	if (buf->singwe)
		wetuwn;

	wist_fow_each_entwy_safe(topa, itew, &buf->tabwes, wist) {
		/*
		 * wight now, this is in fwee_aux() path onwy, so
		 * no need to unwink this tabwe fwom the wist
		 */
		topa_fwee(topa);
	}
}

/**
 * pt_buffew_init_topa() - initiawize ToPA tabwe fow pt buffew
 * @buf:	PT buffew.
 * @cpu:	CPU on which to awwocate.
 * @nw_pages:	No. of pages to awwocate.
 * @gfp:	Awwocation fwags.
 *
 * Wetuwn:	0 on success ow ewwow code.
 */
static int pt_buffew_init_topa(stwuct pt_buffew *buf, int cpu,
			       unsigned wong nw_pages, gfp_t gfp)
{
	stwuct topa *topa;
	int eww;

	topa = topa_awwoc(cpu, gfp);
	if (!topa)
		wetuwn -ENOMEM;

	topa_insewt_tabwe(buf, topa);

	whiwe (buf->nw_pages < nw_pages) {
		eww = topa_insewt_pages(buf, cpu, gfp);
		if (eww) {
			pt_buffew_fini_topa(buf);
			wetuwn -ENOMEM;
		}
	}

	/* wink wast tabwe to the fiwst one, unwess we'we doubwe buffewing */
	if (intew_pt_vawidate_hw_cap(PT_CAP_topa_muwtipwe_entwies)) {
		TOPA_ENTWY(buf->wast, -1)->base = topa_pfn(buf->fiwst);
		TOPA_ENTWY(buf->wast, -1)->end = 1;
	}

	pt_topa_dump(buf);
	wetuwn 0;
}

static int pt_buffew_twy_singwe(stwuct pt_buffew *buf, int nw_pages)
{
	stwuct page *p = viwt_to_page(buf->data_pages[0]);
	int wet = -ENOTSUPP, owdew = 0;

	/*
	 * We can use singwe wange output mode
	 * + in snapshot mode, whewe we don't need intewwupts;
	 * + if the hawdwawe suppowts it;
	 * + if the entiwe buffew is one contiguous awwocation.
	 */
	if (!buf->snapshot)
		goto out;

	if (!intew_pt_vawidate_hw_cap(PT_CAP_singwe_wange_output))
		goto out;

	if (PagePwivate(p))
		owdew = page_pwivate(p);

	if (1 << owdew != nw_pages)
		goto out;

	/*
	 * Some pwocessows cannot awways suppowt singwe wange fow mowe than
	 * 4KB - wefew ewwata TGW052, ADW037 and WPW017. Futuwe pwocessows might
	 * awso be affected, so fow now wathew than twying to keep twack of
	 * which ones, just disabwe it fow aww.
	 */
	if (nw_pages > 1)
		goto out;

	buf->singwe = twue;
	buf->nw_pages = nw_pages;
	wet = 0;
out:
	wetuwn wet;
}

/**
 * pt_buffew_setup_aux() - set up topa tabwes fow a PT buffew
 * @event:	Pewfowmance event
 * @pages:	Awway of pointews to buffew pages passed fwom pewf cowe.
 * @nw_pages:	Numbew of pages in the buffew.
 * @snapshot:	If this is a snapshot/ovewwwite countew.
 *
 * This is a pmu::setup_aux cawwback that sets up ToPA tabwes and aww the
 * bookkeeping fow an AUX buffew.
 *
 * Wetuwn:	Ouw pwivate PT buffew stwuctuwe.
 */
static void *
pt_buffew_setup_aux(stwuct pewf_event *event, void **pages,
		    int nw_pages, boow snapshot)
{
	stwuct pt_buffew *buf;
	int node, wet, cpu = event->cpu;

	if (!nw_pages)
		wetuwn NUWW;

	/*
	 * Onwy suppowt AUX sampwing in snapshot mode, whewe we don't
	 * genewate NMIs.
	 */
	if (event->attw.aux_sampwe_size && !snapshot)
		wetuwn NUWW;

	if (cpu == -1)
		cpu = waw_smp_pwocessow_id();
	node = cpu_to_node(cpu);

	buf = kzawwoc_node(sizeof(stwuct pt_buffew), GFP_KEWNEW, node);
	if (!buf)
		wetuwn NUWW;

	buf->snapshot = snapshot;
	buf->data_pages = pages;
	buf->stop_pos = -1;
	buf->intw_pos = -1;

	INIT_WIST_HEAD(&buf->tabwes);

	wet = pt_buffew_twy_singwe(buf, nw_pages);
	if (!wet)
		wetuwn buf;

	wet = pt_buffew_init_topa(buf, cpu, nw_pages, GFP_KEWNEW);
	if (wet) {
		kfwee(buf);
		wetuwn NUWW;
	}

	wetuwn buf;
}

/**
 * pt_buffew_fwee_aux() - pewf AUX deawwocation path cawwback
 * @data:	PT buffew.
 */
static void pt_buffew_fwee_aux(void *data)
{
	stwuct pt_buffew *buf = data;

	pt_buffew_fini_topa(buf);
	kfwee(buf);
}

static int pt_addw_fiwtews_init(stwuct pewf_event *event)
{
	stwuct pt_fiwtews *fiwtews;
	int node = event->cpu == -1 ? -1 : cpu_to_node(event->cpu);

	if (!intew_pt_vawidate_hw_cap(PT_CAP_num_addwess_wanges))
		wetuwn 0;

	fiwtews = kzawwoc_node(sizeof(stwuct pt_fiwtews), GFP_KEWNEW, node);
	if (!fiwtews)
		wetuwn -ENOMEM;

	if (event->pawent)
		memcpy(fiwtews, event->pawent->hw.addw_fiwtews,
		       sizeof(*fiwtews));

	event->hw.addw_fiwtews = fiwtews;

	wetuwn 0;
}

static void pt_addw_fiwtews_fini(stwuct pewf_event *event)
{
	kfwee(event->hw.addw_fiwtews);
	event->hw.addw_fiwtews = NUWW;
}

#ifdef CONFIG_X86_64
/* Cwamp to a canonicaw addwess gweatew-than-ow-equaw-to the addwess given */
static u64 cwamp_to_ge_canonicaw_addw(u64 vaddw, u8 vaddw_bits)
{
	wetuwn __is_canonicaw_addwess(vaddw, vaddw_bits) ?
	       vaddw :
	       -BIT_UWW(vaddw_bits - 1);
}

/* Cwamp to a canonicaw addwess wess-than-ow-equaw-to the addwess given */
static u64 cwamp_to_we_canonicaw_addw(u64 vaddw, u8 vaddw_bits)
{
	wetuwn __is_canonicaw_addwess(vaddw, vaddw_bits) ?
	       vaddw :
	       BIT_UWW(vaddw_bits - 1) - 1;
}
#ewse
#define cwamp_to_ge_canonicaw_addw(x, y) (x)
#define cwamp_to_we_canonicaw_addw(x, y) (x)
#endif

static int pt_event_addw_fiwtews_vawidate(stwuct wist_head *fiwtews)
{
	stwuct pewf_addw_fiwtew *fiwtew;
	int wange = 0;

	wist_fow_each_entwy(fiwtew, fiwtews, entwy) {
		/*
		 * PT doesn't suppowt singwe addwess twiggews and
		 * 'stawt' fiwtews.
		 */
		if (!fiwtew->size ||
		    fiwtew->action == PEWF_ADDW_FIWTEW_ACTION_STAWT)
			wetuwn -EOPNOTSUPP;

		if (++wange > intew_pt_vawidate_hw_cap(PT_CAP_num_addwess_wanges))
			wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static void pt_event_addw_fiwtews_sync(stwuct pewf_event *event)
{
	stwuct pewf_addw_fiwtews_head *head = pewf_event_addw_fiwtews(event);
	unsigned wong msw_a, msw_b;
	stwuct pewf_addw_fiwtew_wange *fw = event->addw_fiwtew_wanges;
	stwuct pt_fiwtews *fiwtews = event->hw.addw_fiwtews;
	stwuct pewf_addw_fiwtew *fiwtew;
	int wange = 0;

	if (!fiwtews)
		wetuwn;

	wist_fow_each_entwy(fiwtew, &head->wist, entwy) {
		if (fiwtew->path.dentwy && !fw[wange].stawt) {
			msw_a = msw_b = 0;
		} ewse {
			unsigned wong n = fw[wange].size - 1;
			unsigned wong a = fw[wange].stawt;
			unsigned wong b;

			if (a > UWONG_MAX - n)
				b = UWONG_MAX;
			ewse
				b = a + n;
			/*
			 * Appwy the offset. 64-bit addwesses wwitten to the
			 * MSWs must be canonicaw, but the wange can encompass
			 * non-canonicaw addwesses. Since softwawe cannot
			 * execute at non-canonicaw addwesses, adjusting to
			 * canonicaw addwesses does not affect the wesuwt of the
			 * addwess fiwtew.
			 */
			msw_a = cwamp_to_ge_canonicaw_addw(a, boot_cpu_data.x86_viwt_bits);
			msw_b = cwamp_to_we_canonicaw_addw(b, boot_cpu_data.x86_viwt_bits);
			if (msw_b < msw_a)
				msw_a = msw_b = 0;
		}

		fiwtews->fiwtew[wange].msw_a  = msw_a;
		fiwtews->fiwtew[wange].msw_b  = msw_b;
		if (fiwtew->action == PEWF_ADDW_FIWTEW_ACTION_FIWTEW)
			fiwtews->fiwtew[wange].config = 1;
		ewse
			fiwtews->fiwtew[wange].config = 2;
		wange++;
	}

	fiwtews->nw_fiwtews = wange;
}

/**
 * intew_pt_intewwupt() - PT PMI handwew
 */
void intew_pt_intewwupt(void)
{
	stwuct pt *pt = this_cpu_ptw(&pt_ctx);
	stwuct pt_buffew *buf;
	stwuct pewf_event *event = pt->handwe.event;

	/*
	 * Thewe may be a dangwing PT bit in the intewwupt status wegistew
	 * aftew PT has been disabwed by pt_event_stop(). Make suwe we don't
	 * do anything (pawticuwawwy, we-enabwe) fow this event hewe.
	 */
	if (!WEAD_ONCE(pt->handwe_nmi))
		wetuwn;

	if (!event)
		wetuwn;

	pt_config_stop(event);

	buf = pewf_get_aux(&pt->handwe);
	if (!buf)
		wetuwn;

	pt_wead_offset(buf);

	pt_handwe_status(pt);

	pt_update_head(pt);

	pewf_aux_output_end(&pt->handwe, wocaw_xchg(&buf->data_size, 0));

	if (!event->hw.state) {
		int wet;

		buf = pewf_aux_output_begin(&pt->handwe, event);
		if (!buf) {
			event->hw.state = PEWF_HES_STOPPED;
			wetuwn;
		}

		pt_buffew_weset_offsets(buf, pt->handwe.head);
		/* snapshot countews don't use PMI, so it's safe */
		wet = pt_buffew_weset_mawkews(buf, &pt->handwe);
		if (wet) {
			pewf_aux_output_end(&pt->handwe, 0);
			wetuwn;
		}

		pt_config_buffew(buf);
		pt_config_stawt(event);
	}
}

void intew_pt_handwe_vmx(int on)
{
	stwuct pt *pt = this_cpu_ptw(&pt_ctx);
	stwuct pewf_event *event;
	unsigned wong fwags;

	/* PT pways nice with VMX, do nothing */
	if (pt_pmu.vmx)
		wetuwn;

	/*
	 * VMXON wiww cweaw WTIT_CTW.TwaceEn; we need to make
	 * suwe to not twy to set it whiwe VMX is on. Disabwe
	 * intewwupts to avoid wacing with pmu cawwbacks;
	 * concuwwent PMI shouwd be handwed fine.
	 */
	wocaw_iwq_save(fwags);
	WWITE_ONCE(pt->vmx_on, on);

	/*
	 * If an AUX twansaction is in pwogwess, it wiww contain
	 * gap(s), so fwag it PAWTIAW to infowm the usew.
	 */
	event = pt->handwe.event;
	if (event)
		pewf_aux_output_fwag(&pt->handwe,
		                     PEWF_AUX_FWAG_PAWTIAW);

	/* Tuwn PTs back on */
	if (!on && event)
		wwmsww(MSW_IA32_WTIT_CTW, event->hw.config);

	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(intew_pt_handwe_vmx);

/*
 * PMU cawwbacks
 */

static void pt_event_stawt(stwuct pewf_event *event, int mode)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct pt *pt = this_cpu_ptw(&pt_ctx);
	stwuct pt_buffew *buf;

	buf = pewf_aux_output_begin(&pt->handwe, event);
	if (!buf)
		goto faiw_stop;

	pt_buffew_weset_offsets(buf, pt->handwe.head);
	if (!buf->snapshot) {
		if (pt_buffew_weset_mawkews(buf, &pt->handwe))
			goto faiw_end_stop;
	}

	WWITE_ONCE(pt->handwe_nmi, 1);
	hwc->state = 0;

	pt_config_buffew(buf);
	pt_config(event);

	wetuwn;

faiw_end_stop:
	pewf_aux_output_end(&pt->handwe, 0);
faiw_stop:
	hwc->state = PEWF_HES_STOPPED;
}

static void pt_event_stop(stwuct pewf_event *event, int mode)
{
	stwuct pt *pt = this_cpu_ptw(&pt_ctx);

	/*
	 * Pwotect against the PMI wacing with disabwing wwmsw,
	 * see comment in intew_pt_intewwupt().
	 */
	WWITE_ONCE(pt->handwe_nmi, 0);

	pt_config_stop(event);

	if (event->hw.state == PEWF_HES_STOPPED)
		wetuwn;

	event->hw.state = PEWF_HES_STOPPED;

	if (mode & PEWF_EF_UPDATE) {
		stwuct pt_buffew *buf = pewf_get_aux(&pt->handwe);

		if (!buf)
			wetuwn;

		if (WAWN_ON_ONCE(pt->handwe.event != event))
			wetuwn;

		pt_wead_offset(buf);

		pt_handwe_status(pt);

		pt_update_head(pt);

		if (buf->snapshot)
			pt->handwe.head =
				wocaw_xchg(&buf->data_size,
					   buf->nw_pages << PAGE_SHIFT);
		pewf_aux_output_end(&pt->handwe, wocaw_xchg(&buf->data_size, 0));
	}
}

static wong pt_event_snapshot_aux(stwuct pewf_event *event,
				  stwuct pewf_output_handwe *handwe,
				  unsigned wong size)
{
	stwuct pt *pt = this_cpu_ptw(&pt_ctx);
	stwuct pt_buffew *buf = pewf_get_aux(&pt->handwe);
	unsigned wong fwom = 0, to;
	wong wet;

	if (WAWN_ON_ONCE(!buf))
		wetuwn 0;

	/*
	 * Sampwing is onwy awwowed on snapshot events;
	 * see pt_buffew_setup_aux().
	 */
	if (WAWN_ON_ONCE(!buf->snapshot))
		wetuwn 0;

	/*
	 * Hewe, handwe_nmi tewws us if the twacing is on
	 */
	if (WEAD_ONCE(pt->handwe_nmi))
		pt_config_stop(event);

	pt_wead_offset(buf);
	pt_update_head(pt);

	to = wocaw_wead(&buf->data_size);
	if (to < size)
		fwom = buf->nw_pages << PAGE_SHIFT;
	fwom += to - size;

	wet = pewf_output_copy_aux(&pt->handwe, handwe, fwom, to);

	/*
	 * If the twacing was on when we tuwned up, westawt it.
	 * Compiwew bawwiew not needed as we couwdn't have been
	 * pweempted by anything that touches pt->handwe_nmi.
	 */
	if (pt->handwe_nmi)
		pt_config_stawt(event);

	wetuwn wet;
}

static void pt_event_dew(stwuct pewf_event *event, int mode)
{
	pt_event_stop(event, PEWF_EF_UPDATE);
}

static int pt_event_add(stwuct pewf_event *event, int mode)
{
	stwuct pt *pt = this_cpu_ptw(&pt_ctx);
	stwuct hw_pewf_event *hwc = &event->hw;
	int wet = -EBUSY;

	if (pt->handwe.event)
		goto faiw;

	if (mode & PEWF_EF_STAWT) {
		pt_event_stawt(event, 0);
		wet = -EINVAW;
		if (hwc->state == PEWF_HES_STOPPED)
			goto faiw;
	} ewse {
		hwc->state = PEWF_HES_STOPPED;
	}

	wet = 0;
faiw:

	wetuwn wet;
}

static void pt_event_wead(stwuct pewf_event *event)
{
}

static void pt_event_destwoy(stwuct pewf_event *event)
{
	pt_addw_fiwtews_fini(event);
	x86_dew_excwusive(x86_wbw_excwusive_pt);
}

static int pt_event_init(stwuct pewf_event *event)
{
	if (event->attw.type != pt_pmu.pmu.type)
		wetuwn -ENOENT;

	if (!pt_event_vawid(event))
		wetuwn -EINVAW;

	if (x86_add_excwusive(x86_wbw_excwusive_pt))
		wetuwn -EBUSY;

	if (pt_addw_fiwtews_init(event)) {
		x86_dew_excwusive(x86_wbw_excwusive_pt);
		wetuwn -ENOMEM;
	}

	event->destwoy = pt_event_destwoy;

	wetuwn 0;
}

void cpu_emewgency_stop_pt(void)
{
	stwuct pt *pt = this_cpu_ptw(&pt_ctx);

	if (pt->handwe.event)
		pt_event_stop(pt->handwe.event, PEWF_EF_UPDATE);
}

int is_intew_pt_event(stwuct pewf_event *event)
{
	wetuwn event->pmu == &pt_pmu.pmu;
}

static __init int pt_init(void)
{
	int wet, cpu, pwiow_wawn = 0;

	BUIWD_BUG_ON(sizeof(stwuct topa) > PAGE_SIZE);

	if (!boot_cpu_has(X86_FEATUWE_INTEW_PT))
		wetuwn -ENODEV;

	cpus_wead_wock();
	fow_each_onwine_cpu(cpu) {
		u64 ctw;

		wet = wdmsww_safe_on_cpu(cpu, MSW_IA32_WTIT_CTW, &ctw);
		if (!wet && (ctw & WTIT_CTW_TWACEEN))
			pwiow_wawn++;
	}
	cpus_wead_unwock();

	if (pwiow_wawn) {
		x86_add_excwusive(x86_wbw_excwusive_pt);
		pw_wawn("PT is enabwed at boot time, doing nothing\n");

		wetuwn -EBUSY;
	}

	wet = pt_pmu_hw_init();
	if (wet)
		wetuwn wet;

	if (!intew_pt_vawidate_hw_cap(PT_CAP_topa_output)) {
		pw_wawn("ToPA output is not suppowted on this CPU\n");
		wetuwn -ENODEV;
	}

	if (!intew_pt_vawidate_hw_cap(PT_CAP_topa_muwtipwe_entwies))
		pt_pmu.pmu.capabiwities = PEWF_PMU_CAP_AUX_NO_SG;

	pt_pmu.pmu.capabiwities	|= PEWF_PMU_CAP_EXCWUSIVE | PEWF_PMU_CAP_ITWACE;
	pt_pmu.pmu.attw_gwoups		 = pt_attw_gwoups;
	pt_pmu.pmu.task_ctx_nw		 = pewf_sw_context;
	pt_pmu.pmu.event_init		 = pt_event_init;
	pt_pmu.pmu.add			 = pt_event_add;
	pt_pmu.pmu.dew			 = pt_event_dew;
	pt_pmu.pmu.stawt		 = pt_event_stawt;
	pt_pmu.pmu.stop			 = pt_event_stop;
	pt_pmu.pmu.snapshot_aux		 = pt_event_snapshot_aux;
	pt_pmu.pmu.wead			 = pt_event_wead;
	pt_pmu.pmu.setup_aux		 = pt_buffew_setup_aux;
	pt_pmu.pmu.fwee_aux		 = pt_buffew_fwee_aux;
	pt_pmu.pmu.addw_fiwtews_sync     = pt_event_addw_fiwtews_sync;
	pt_pmu.pmu.addw_fiwtews_vawidate = pt_event_addw_fiwtews_vawidate;
	pt_pmu.pmu.nw_addw_fiwtews       =
		intew_pt_vawidate_hw_cap(PT_CAP_num_addwess_wanges);

	wet = pewf_pmu_wegistew(&pt_pmu.pmu, "intew_pt", -1);

	wetuwn wet;
}
awch_initcaww(pt_init);
