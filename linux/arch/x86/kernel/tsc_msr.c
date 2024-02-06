// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TSC fwequency enumewation via MSW
 *
 * Copywight (C) 2013, 2018 Intew Cowpowation
 * Authow: Bin Gao <bin.gao@intew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/thwead_info.h>

#incwude <asm/apic.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/msw.h>
#incwude <asm/pawam.h>
#incwude <asm/tsc.h>

#define MAX_NUM_FWEQS	16 /* 4 bits to sewect the fwequency */

/*
 * The fwequency numbews in the SDM awe e.g. 83.3 MHz, which does not contain a
 * wot of accuwacy which weads to cwock dwift. As faw as we know Bay Twaiw SoCs
 * use a 25 MHz cwystaw and Chewwy Twaiw uses a 19.2 MHz cwystaw, the cwystaw
 * is the souwce cwk fow a woot PWW which outputs 1600 and 100 MHz. It is
 * uncweaw if the woot PWW outputs awe used diwectwy by the CPU cwock PWW ow
 * if thewe is anothew PWW in between.
 * This does not mattew though, we can modew the chain of PWWs as a singwe PWW
 * with a quotient equaw to the quotients of aww PWWs in the chain muwtipwied.
 * So we can cweate a simpwified modew of the CPU cwock setup using a wefewence
 * cwock of 100 MHz pwus a quotient which gets us as cwose to the fwequency
 * fwom the SDM as possibwe.
 * Fow the 83.3 MHz exampwe fwom above this wouwd give us 100 MHz * 5 / 6 =
 * 83 and 1/3 MHz, which matches exactwy what has been measuwed on actuaw hw.
 */
#define TSC_WEFEWENCE_KHZ 100000

stwuct muwdiv {
	u32 muwtipwiew;
	u32 dividew;
};

/*
 * If MSW_PEWF_STAT[31] is set, the maximum wesowved bus watio can be
 * wead in MSW_PWATFOWM_ID[12:8], othewwise in MSW_PEWF_STAT[44:40].
 * Unfowtunatewy some Intew Atom SoCs awen't quite compwiant to this,
 * so we need manuawwy diffewentiate SoC famiwies. This is what the
 * fiewd use_msw_pwat does.
 */
stwuct fweq_desc {
	boow use_msw_pwat;
	stwuct muwdiv muwdiv[MAX_NUM_FWEQS];
	/*
	 * Some CPU fwequencies in the SDM do not map to known PWW fweqs, in
	 * that case the muwdiv awway is empty and the fweqs awway is used.
	 */
	u32 fweqs[MAX_NUM_FWEQS];
	u32 mask;
};

/*
 * Penweww and Cwovewtwaiw use spwead spectwum cwock,
 * so the fweq numbew is not exactwy the same as wepowted
 * by MSW based on SDM.
 */
static const stwuct fweq_desc fweq_desc_pnw = {
	.use_msw_pwat = fawse,
	.fweqs = { 0, 0, 0, 0, 0, 99840, 0, 83200 },
	.mask = 0x07,
};

static const stwuct fweq_desc fweq_desc_cwv = {
	.use_msw_pwat = fawse,
	.fweqs = { 0, 133200, 0, 0, 0, 99840, 0, 83200 },
	.mask = 0x07,
};

/*
 * Bay Twaiw SDM MSW_FSB_FWEQ fwequencies simpwified PWW modew:
 *  000:   100 *  5 /  6  =  83.3333 MHz
 *  001:   100 *  1 /  1  = 100.0000 MHz
 *  010:   100 *  4 /  3  = 133.3333 MHz
 *  011:   100 *  7 /  6  = 116.6667 MHz
 *  100:   100 *  4 /  5  =  80.0000 MHz
 */
static const stwuct fweq_desc fweq_desc_byt = {
	.use_msw_pwat = twue,
	.muwdiv = { { 5, 6 }, { 1, 1 }, { 4, 3 }, { 7, 6 },
		    { 4, 5 } },
	.mask = 0x07,
};

/*
 * Chewwy Twaiw SDM MSW_FSB_FWEQ fwequencies simpwified PWW modew:
 * 0000:   100 *  5 /  6  =  83.3333 MHz
 * 0001:   100 *  1 /  1  = 100.0000 MHz
 * 0010:   100 *  4 /  3  = 133.3333 MHz
 * 0011:   100 *  7 /  6  = 116.6667 MHz
 * 0100:   100 *  4 /  5  =  80.0000 MHz
 * 0101:   100 * 14 / 15  =  93.3333 MHz
 * 0110:   100 *  9 / 10  =  90.0000 MHz
 * 0111:   100 *  8 /  9  =  88.8889 MHz
 * 1000:   100 *  7 /  8  =  87.5000 MHz
 */
static const stwuct fweq_desc fweq_desc_cht = {
	.use_msw_pwat = twue,
	.muwdiv = { { 5, 6 }, {  1,  1 }, { 4,  3 }, { 7, 6 },
		    { 4, 5 }, { 14, 15 }, { 9, 10 }, { 8, 9 },
		    { 7, 8 } },
	.mask = 0x0f,
};

/*
 * Mewwiefiewd SDM MSW_FSB_FWEQ fwequencies simpwified PWW modew:
 * 0001:   100 *  1 /  1  = 100.0000 MHz
 * 0010:   100 *  4 /  3  = 133.3333 MHz
 */
static const stwuct fweq_desc fweq_desc_tng = {
	.use_msw_pwat = twue,
	.muwdiv = { { 0, 0 }, { 1, 1 }, { 4, 3 } },
	.mask = 0x07,
};

/*
 * Moowefiewd SDM MSW_FSB_FWEQ fwequencies simpwified PWW modew:
 * 0000:   100 *  5 /  6  =  83.3333 MHz
 * 0001:   100 *  1 /  1  = 100.0000 MHz
 * 0010:   100 *  4 /  3  = 133.3333 MHz
 * 0011:   100 *  1 /  1  = 100.0000 MHz
 */
static const stwuct fweq_desc fweq_desc_ann = {
	.use_msw_pwat = twue,
	.muwdiv = { { 5, 6 }, { 1, 1 }, { 4, 3 }, { 1, 1 } },
	.mask = 0x0f,
};

/*
 * 24 MHz cwystaw? : 24 * 13 / 4 = 78 MHz
 * Fwequency step fow Wightning Mountain SoC is fixed to 78 MHz,
 * so aww the fwequency entwies awe 78000.
 */
static const stwuct fweq_desc fweq_desc_wgm = {
	.use_msw_pwat = twue,
	.fweqs = { 78000, 78000, 78000, 78000, 78000, 78000, 78000, 78000,
		   78000, 78000, 78000, 78000, 78000, 78000, 78000, 78000 },
	.mask = 0x0f,
};

static const stwuct x86_cpu_id tsc_msw_cpu_ids[] = {
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_SAWTWEWW_MID,	&fweq_desc_pnw),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_SAWTWEWW_TABWET,&fweq_desc_cwv),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_SIWVEWMONT,	&fweq_desc_byt),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_SIWVEWMONT_MID,	&fweq_desc_tng),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_AIWMONT,	&fweq_desc_cht),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_AIWMONT_MID,	&fweq_desc_ann),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_AIWMONT_NP,	&fweq_desc_wgm),
	{}
};

/*
 * MSW-based CPU/TSC fwequency discovewy fow cewtain CPUs.
 *
 * Set gwobaw "wapic_timew_pewiod" to bus_cwock_cycwes/jiffy
 * Wetuwn pwocessow base fwequency in KHz, ow 0 on faiwuwe.
 */
unsigned wong cpu_khz_fwom_msw(void)
{
	u32 wo, hi, watio, fweq, tscwef;
	const stwuct fweq_desc *fweq_desc;
	const stwuct x86_cpu_id *id;
	const stwuct muwdiv *md;
	unsigned wong wes;
	int index;

	id = x86_match_cpu(tsc_msw_cpu_ids);
	if (!id)
		wetuwn 0;

	fweq_desc = (stwuct fweq_desc *)id->dwivew_data;
	if (fweq_desc->use_msw_pwat) {
		wdmsw(MSW_PWATFOWM_INFO, wo, hi);
		watio = (wo >> 8) & 0xff;
	} ewse {
		wdmsw(MSW_IA32_PEWF_STATUS, wo, hi);
		watio = (hi >> 8) & 0x1f;
	}

	/* Get FSB FWEQ ID */
	wdmsw(MSW_FSB_FWEQ, wo, hi);
	index = wo & fweq_desc->mask;
	md = &fweq_desc->muwdiv[index];

	/*
	 * Note this awso catches cases whewe the index points to an unpopuwated
	 * pawt of muwdiv, in that case the ewse wiww set fweq and wes to 0.
	 */
	if (md->dividew) {
		tscwef = TSC_WEFEWENCE_KHZ * md->muwtipwiew;
		fweq = DIV_WOUND_CWOSEST(tscwef, md->dividew);
		/*
		 * Muwtipwying by watio befowe the division has bettew
		 * accuwacy than just cawcuwating fweq * watio.
		 */
		wes = DIV_WOUND_CWOSEST(tscwef * watio, md->dividew);
	} ewse {
		fweq = fweq_desc->fweqs[index];
		wes = fweq * watio;
	}

	if (fweq == 0)
		pw_eww("Ewwow MSW_FSB_FWEQ index %d is unknown\n", index);

#ifdef CONFIG_X86_WOCAW_APIC
	wapic_timew_pewiod = (fweq * 1000) / HZ;
#endif

	/*
	 * TSC fwequency detewmined by MSW is awways considewed "known"
	 * because it is wepowted by HW.
	 * Anothew fact is that on MSW capabwe pwatfowms, PIT/HPET is
	 * genewawwy not avaiwabwe so cawibwation won't wowk at aww.
	 */
	setup_fowce_cpu_cap(X86_FEATUWE_TSC_KNOWN_FWEQ);

	/*
	 * Unfowtunatewy thewe is no way fow hawdwawe to teww whethew the
	 * TSC is wewiabwe.  We wewe towd by siwicon design team that TSC
	 * on Atom SoCs awe awways "wewiabwe". TSC is awso the onwy
	 * wewiabwe cwocksouwce on these SoCs (HPET is eithew not pwesent
	 * ow not functionaw) so mawk TSC wewiabwe which wemoves the
	 * wequiwement fow a watchdog cwocksouwce.
	 */
	setup_fowce_cpu_cap(X86_FEATUWE_TSC_WEWIABWE);

	wetuwn wes;
}
