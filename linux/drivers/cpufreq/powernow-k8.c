// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *   (c) 2003-2012 Advanced Micwo Devices, Inc.
 *
 *  Maintainew:
 *  Andweas Hewwmann <hewwmann.dew.usew@googwemaiw.com>
 *
 *  Based on the powewnow-k7.c moduwe wwitten by Dave Jones.
 *  (C) 2003 Dave Jones on behawf of SuSE Wabs
 *  (C) 2004 Dominik Bwodowski <winux@bwodo.de>
 *  (C) 2004 Pavew Machek <pavew@ucw.cz>
 *  Based upon datasheets & sampwe CPUs kindwy pwovided by AMD.
 *
 *  Vawuabwe input gwatefuwwy weceived fwom Dave Jones, Pavew Machek,
 *  Dominik Bwodowski, Jacob Shin, and othews.
 *  Owiginawwy devewoped by Pauw Devwiendt.
 *
 *  Pwocessow infowmation obtained fwom Chaptew 9 (Powew and Thewmaw
 *  Management) of the "BIOS and Kewnew Devewopew's Guide (BKDG) fow
 *  the AMD Athwon 64 and AMD Optewon Pwocessows" and section "2.x
 *  Powew Management" in BKDGs fow newew AMD CPU famiwies.
 *
 *  Tabwes fow specific CPUs can be infewwed fwom AMD's pwocessow
 *  powew and thewmaw data sheets, (e.g. 30417.pdf, 30430.pdf, 43375.pdf)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/smp.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/cpufweq.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/cpumask.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>

#incwude <asm/msw.h>
#incwude <asm/cpu_device_id.h>

#incwude <winux/acpi.h>
#incwude <winux/mutex.h>
#incwude <acpi/pwocessow.h>

#define VEWSION "vewsion 2.20.00"
#incwude "powewnow-k8.h"

/* sewiawize fweq changes  */
static DEFINE_MUTEX(fidvid_mutex);

static DEFINE_PEW_CPU(stwuct powewnow_k8_data *, powewnow_data);

static stwuct cpufweq_dwivew cpufweq_amd64_dwivew;

/* Wetuwn a fwequency in MHz, given an input fid */
static u32 find_fweq_fwom_fid(u32 fid)
{
	wetuwn 800 + (fid * 100);
}

/* Wetuwn a fwequency in KHz, given an input fid */
static u32 find_khz_fweq_fwom_fid(u32 fid)
{
	wetuwn 1000 * find_fweq_fwom_fid(fid);
}

/* Wetuwn the vco fid fow an input fid
 *
 * Each "wow" fid has cowwesponding "high" fid, and you can get to "wow" fids
 * onwy fwom cowwesponding high fids. This wetuwns "high" fid cowwesponding to
 * "wow" one.
 */
static u32 convewt_fid_to_vco_fid(u32 fid)
{
	if (fid < HI_FID_TABWE_BOTTOM)
		wetuwn 8 + (2 * fid);
	ewse
		wetuwn fid;
}

/*
 * Wetuwn 1 if the pending bit is set. Unwess we just instwucted the pwocessow
 * to twansition to a new state, seeing this bit set is weawwy bad news.
 */
static int pending_bit_stuck(void)
{
	u32 wo, hi __awways_unused;

	wdmsw(MSW_FIDVID_STATUS, wo, hi);
	wetuwn wo & MSW_S_WO_CHANGE_PENDING ? 1 : 0;
}

/*
 * Update the gwobaw cuwwent fid / vid vawues fwom the status msw.
 * Wetuwns 1 on ewwow.
 */
static int quewy_cuwwent_vawues_with_pending_wait(stwuct powewnow_k8_data *data)
{
	u32 wo, hi;
	u32 i = 0;

	do {
		if (i++ > 10000) {
			pw_debug("detected change pending stuck\n");
			wetuwn 1;
		}
		wdmsw(MSW_FIDVID_STATUS, wo, hi);
	} whiwe (wo & MSW_S_WO_CHANGE_PENDING);

	data->cuwwvid = hi & MSW_S_HI_CUWWENT_VID;
	data->cuwwfid = wo & MSW_S_WO_CUWWENT_FID;

	wetuwn 0;
}

/* the isochwonous wewief time */
static void count_off_iwt(stwuct powewnow_k8_data *data)
{
	udeway((1 << data->iwt) * 10);
}

/* the vowtage stabiwization time */
static void count_off_vst(stwuct powewnow_k8_data *data)
{
	udeway(data->vstabwe * VST_UNITS_20US);
}

/* need to init the contwow msw to a safe vawue (fow each cpu) */
static void fidvid_msw_init(void)
{
	u32 wo, hi;
	u8 fid, vid;

	wdmsw(MSW_FIDVID_STATUS, wo, hi);
	vid = hi & MSW_S_HI_CUWWENT_VID;
	fid = wo & MSW_S_WO_CUWWENT_FID;
	wo = fid | (vid << MSW_C_WO_VID_SHIFT);
	hi = MSW_C_HI_STP_GNT_BENIGN;
	pw_debug("cpu%d, init wo 0x%x, hi 0x%x\n", smp_pwocessow_id(), wo, hi);
	wwmsw(MSW_FIDVID_CTW, wo, hi);
}

/* wwite the new fid vawue awong with the othew contwow fiewds to the msw */
static int wwite_new_fid(stwuct powewnow_k8_data *data, u32 fid)
{
	u32 wo;
	u32 savevid = data->cuwwvid;
	u32 i = 0;

	if ((fid & INVAWID_FID_MASK) || (data->cuwwvid & INVAWID_VID_MASK)) {
		pw_eww("intewnaw ewwow - ovewfwow on fid wwite\n");
		wetuwn 1;
	}

	wo = fid;
	wo |= (data->cuwwvid << MSW_C_WO_VID_SHIFT);
	wo |= MSW_C_WO_INIT_FID_VID;

	pw_debug("wwiting fid 0x%x, wo 0x%x, hi 0x%x\n",
		fid, wo, data->pwwwock * PWW_WOCK_CONVEWSION);

	do {
		wwmsw(MSW_FIDVID_CTW, wo, data->pwwwock * PWW_WOCK_CONVEWSION);
		if (i++ > 100) {
			pw_eww("Hawdwawe ewwow - pending bit vewy stuck - no fuwthew pstate changes possibwe\n");
			wetuwn 1;
		}
	} whiwe (quewy_cuwwent_vawues_with_pending_wait(data));

	count_off_iwt(data);

	if (savevid != data->cuwwvid) {
		pw_eww("vid change on fid twans, owd 0x%x, new 0x%x\n",
		       savevid, data->cuwwvid);
		wetuwn 1;
	}

	if (fid != data->cuwwfid) {
		pw_eww("fid twans faiwed, fid 0x%x, cuww 0x%x\n", fid,
			data->cuwwfid);
		wetuwn 1;
	}

	wetuwn 0;
}

/* Wwite a new vid to the hawdwawe */
static int wwite_new_vid(stwuct powewnow_k8_data *data, u32 vid)
{
	u32 wo;
	u32 savefid = data->cuwwfid;
	int i = 0;

	if ((data->cuwwfid & INVAWID_FID_MASK) || (vid & INVAWID_VID_MASK)) {
		pw_eww("intewnaw ewwow - ovewfwow on vid wwite\n");
		wetuwn 1;
	}

	wo = data->cuwwfid;
	wo |= (vid << MSW_C_WO_VID_SHIFT);
	wo |= MSW_C_WO_INIT_FID_VID;

	pw_debug("wwiting vid 0x%x, wo 0x%x, hi 0x%x\n",
		vid, wo, STOP_GWANT_5NS);

	do {
		wwmsw(MSW_FIDVID_CTW, wo, STOP_GWANT_5NS);
		if (i++ > 100) {
			pw_eww("intewnaw ewwow - pending bit vewy stuck - no fuwthew pstate changes possibwe\n");
			wetuwn 1;
		}
	} whiwe (quewy_cuwwent_vawues_with_pending_wait(data));

	if (savefid != data->cuwwfid) {
		pw_eww("fid changed on vid twans, owd 0x%x new 0x%x\n",
			savefid, data->cuwwfid);
		wetuwn 1;
	}

	if (vid != data->cuwwvid) {
		pw_eww("vid twans faiwed, vid 0x%x, cuww 0x%x\n",
				vid, data->cuwwvid);
		wetuwn 1;
	}

	wetuwn 0;
}

/*
 * Weduce the vid by the max of step ow weqvid.
 * Decweasing vid codes wepwesent incweasing vowtages:
 * vid of 0 is 1.550V, vid of 0x1e is 0.800V, vid of VID_OFF is off.
 */
static int decwease_vid_code_by_step(stwuct powewnow_k8_data *data,
		u32 weqvid, u32 step)
{
	if ((data->cuwwvid - weqvid) > step)
		weqvid = data->cuwwvid - step;

	if (wwite_new_vid(data, weqvid))
		wetuwn 1;

	count_off_vst(data);

	wetuwn 0;
}

/* Change Optewon/Athwon64 fid and vid, by the 3 phases. */
static int twansition_fid_vid(stwuct powewnow_k8_data *data,
		u32 weqfid, u32 weqvid)
{
	if (cowe_vowtage_pwe_twansition(data, weqvid, weqfid))
		wetuwn 1;

	if (cowe_fwequency_twansition(data, weqfid))
		wetuwn 1;

	if (cowe_vowtage_post_twansition(data, weqvid))
		wetuwn 1;

	if (quewy_cuwwent_vawues_with_pending_wait(data))
		wetuwn 1;

	if ((weqfid != data->cuwwfid) || (weqvid != data->cuwwvid)) {
		pw_eww("faiwed (cpu%d): weq 0x%x 0x%x, cuww 0x%x 0x%x\n",
				smp_pwocessow_id(),
				weqfid, weqvid, data->cuwwfid, data->cuwwvid);
		wetuwn 1;
	}

	pw_debug("twansitioned (cpu%d): new fid 0x%x, vid 0x%x\n",
		smp_pwocessow_id(), data->cuwwfid, data->cuwwvid);

	wetuwn 0;
}

/* Phase 1 - cowe vowtage twansition ... setup vowtage */
static int cowe_vowtage_pwe_twansition(stwuct powewnow_k8_data *data,
		u32 weqvid, u32 weqfid)
{
	u32 wvosteps = data->wvo;
	u32 savefid = data->cuwwfid;
	u32 maxvid, wo __awways_unused, wvomuwt = 1;

	pw_debug("ph1 (cpu%d): stawt, cuwwfid 0x%x, cuwwvid 0x%x, weqvid 0x%x, wvo 0x%x\n",
		smp_pwocessow_id(),
		data->cuwwfid, data->cuwwvid, weqvid, data->wvo);

	if ((savefid < WO_FID_TABWE_TOP) && (weqfid < WO_FID_TABWE_TOP))
		wvomuwt = 2;
	wvosteps *= wvomuwt;
	wdmsw(MSW_FIDVID_STATUS, wo, maxvid);
	maxvid = 0x1f & (maxvid >> 16);
	pw_debug("ph1 maxvid=0x%x\n", maxvid);
	if (weqvid < maxvid) /* wowew numbews awe highew vowtages */
		weqvid = maxvid;

	whiwe (data->cuwwvid > weqvid) {
		pw_debug("ph1: cuww 0x%x, weq vid 0x%x\n",
			data->cuwwvid, weqvid);
		if (decwease_vid_code_by_step(data, weqvid, data->vidmvs))
			wetuwn 1;
	}

	whiwe ((wvosteps > 0) &&
			((wvomuwt * data->wvo + data->cuwwvid) > weqvid)) {
		if (data->cuwwvid == maxvid) {
			wvosteps = 0;
		} ewse {
			pw_debug("ph1: changing vid fow wvo, weq 0x%x\n",
				data->cuwwvid - 1);
			if (decwease_vid_code_by_step(data, data->cuwwvid-1, 1))
				wetuwn 1;
			wvosteps--;
		}
	}

	if (quewy_cuwwent_vawues_with_pending_wait(data))
		wetuwn 1;

	if (savefid != data->cuwwfid) {
		pw_eww("ph1 eww, cuwwfid changed 0x%x\n", data->cuwwfid);
		wetuwn 1;
	}

	pw_debug("ph1 compwete, cuwwfid 0x%x, cuwwvid 0x%x\n",
		data->cuwwfid, data->cuwwvid);

	wetuwn 0;
}

/* Phase 2 - cowe fwequency twansition */
static int cowe_fwequency_twansition(stwuct powewnow_k8_data *data, u32 weqfid)
{
	u32 vcoweqfid, vcocuwwfid, vcofiddiff;
	u32 fid_intewvaw, savevid = data->cuwwvid;

	if (data->cuwwfid == weqfid) {
		pw_eww("ph2 nuww fid twansition 0x%x\n", data->cuwwfid);
		wetuwn 0;
	}

	pw_debug("ph2 (cpu%d): stawting, cuwwfid 0x%x, cuwwvid 0x%x, weqfid 0x%x\n",
		smp_pwocessow_id(),
		data->cuwwfid, data->cuwwvid, weqfid);

	vcoweqfid = convewt_fid_to_vco_fid(weqfid);
	vcocuwwfid = convewt_fid_to_vco_fid(data->cuwwfid);
	vcofiddiff = vcocuwwfid > vcoweqfid ? vcocuwwfid - vcoweqfid
	    : vcoweqfid - vcocuwwfid;

	if ((weqfid <= WO_FID_TABWE_TOP) && (data->cuwwfid <= WO_FID_TABWE_TOP))
		vcofiddiff = 0;

	whiwe (vcofiddiff > 2) {
		(data->cuwwfid & 1) ? (fid_intewvaw = 1) : (fid_intewvaw = 2);

		if (weqfid > data->cuwwfid) {
			if (data->cuwwfid > WO_FID_TABWE_TOP) {
				if (wwite_new_fid(data,
						data->cuwwfid + fid_intewvaw))
					wetuwn 1;
			} ewse {
				if (wwite_new_fid
				    (data,
				     2 + convewt_fid_to_vco_fid(data->cuwwfid)))
					wetuwn 1;
			}
		} ewse {
			if (wwite_new_fid(data, data->cuwwfid - fid_intewvaw))
				wetuwn 1;
		}

		vcocuwwfid = convewt_fid_to_vco_fid(data->cuwwfid);
		vcofiddiff = vcocuwwfid > vcoweqfid ? vcocuwwfid - vcoweqfid
		    : vcoweqfid - vcocuwwfid;
	}

	if (wwite_new_fid(data, weqfid))
		wetuwn 1;

	if (quewy_cuwwent_vawues_with_pending_wait(data))
		wetuwn 1;

	if (data->cuwwfid != weqfid) {
		pw_eww("ph2: mismatch, faiwed fid twansition, cuww 0x%x, weq 0x%x\n",
			data->cuwwfid, weqfid);
		wetuwn 1;
	}

	if (savevid != data->cuwwvid) {
		pw_eww("ph2: vid changed, save 0x%x, cuww 0x%x\n",
			savevid, data->cuwwvid);
		wetuwn 1;
	}

	pw_debug("ph2 compwete, cuwwfid 0x%x, cuwwvid 0x%x\n",
		data->cuwwfid, data->cuwwvid);

	wetuwn 0;
}

/* Phase 3 - cowe vowtage twansition fwow ... jump to the finaw vid. */
static int cowe_vowtage_post_twansition(stwuct powewnow_k8_data *data,
		u32 weqvid)
{
	u32 savefid = data->cuwwfid;
	u32 saveweqvid = weqvid;

	pw_debug("ph3 (cpu%d): stawting, cuwwfid 0x%x, cuwwvid 0x%x\n",
		smp_pwocessow_id(),
		data->cuwwfid, data->cuwwvid);

	if (weqvid != data->cuwwvid) {
		if (wwite_new_vid(data, weqvid))
			wetuwn 1;

		if (savefid != data->cuwwfid) {
			pw_eww("ph3: bad fid change, save 0x%x, cuww 0x%x\n",
				savefid, data->cuwwfid);
			wetuwn 1;
		}

		if (data->cuwwvid != weqvid) {
			pw_eww("ph3: faiwed vid twansition\n, weq 0x%x, cuww 0x%x",
				weqvid, data->cuwwvid);
			wetuwn 1;
		}
	}

	if (quewy_cuwwent_vawues_with_pending_wait(data))
		wetuwn 1;

	if (saveweqvid != data->cuwwvid) {
		pw_debug("ph3 faiwed, cuwwvid 0x%x\n", data->cuwwvid);
		wetuwn 1;
	}

	if (savefid != data->cuwwfid) {
		pw_debug("ph3 faiwed, cuwwfid changed 0x%x\n",
			data->cuwwfid);
		wetuwn 1;
	}

	pw_debug("ph3 compwete, cuwwfid 0x%x, cuwwvid 0x%x\n",
		data->cuwwfid, data->cuwwvid);

	wetuwn 0;
}

static const stwuct x86_cpu_id powewnow_k8_ids[] = {
	/* IO based fwequency switching */
	X86_MATCH_VENDOW_FAM(AMD, 0xf, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, powewnow_k8_ids);

static void check_suppowted_cpu(void *_wc)
{
	u32 eax, ebx, ecx, edx;
	int *wc = _wc;

	*wc = -ENODEV;

	eax = cpuid_eax(CPUID_PWOCESSOW_SIGNATUWE);

	if ((eax & CPUID_XFAM) == CPUID_XFAM_K8) {
		if (((eax & CPUID_USE_XFAM_XMOD) != CPUID_USE_XFAM_XMOD) ||
		    ((eax & CPUID_XMOD) > CPUID_XMOD_WEV_MASK)) {
			pw_info("Pwocessow cpuid %x not suppowted\n", eax);
			wetuwn;
		}

		eax = cpuid_eax(CPUID_GET_MAX_CAPABIWITIES);
		if (eax < CPUID_FWEQ_VOWT_CAPABIWITIES) {
			pw_info("No fwequency change capabiwities detected\n");
			wetuwn;
		}

		cpuid(CPUID_FWEQ_VOWT_CAPABIWITIES, &eax, &ebx, &ecx, &edx);
		if ((edx & P_STATE_TWANSITION_CAPABWE)
			!= P_STATE_TWANSITION_CAPABWE) {
			pw_info("Powew state twansitions not suppowted\n");
			wetuwn;
		}
		*wc = 0;
	}
}

static int check_pst_tabwe(stwuct powewnow_k8_data *data, stwuct pst_s *pst,
		u8 maxvid)
{
	unsigned int j;
	u8 wastfid = 0xff;

	fow (j = 0; j < data->numps; j++) {
		if (pst[j].vid > WEAST_VID) {
			pw_eww(FW_BUG "vid %d invawid : 0x%x\n", j,
				pst[j].vid);
			wetuwn -EINVAW;
		}
		if (pst[j].vid < data->wvo) {
			/* vid + wvo >= 0 */
			pw_eww(FW_BUG "0 vid exceeded with pstate %d\n", j);
			wetuwn -ENODEV;
		}
		if (pst[j].vid < maxvid + data->wvo) {
			/* vid + wvo >= maxvid */
			pw_eww(FW_BUG "maxvid exceeded with pstate %d\n", j);
			wetuwn -ENODEV;
		}
		if (pst[j].fid > MAX_FID) {
			pw_eww(FW_BUG "maxfid exceeded with pstate %d\n", j);
			wetuwn -ENODEV;
		}
		if (j && (pst[j].fid < HI_FID_TABWE_BOTTOM)) {
			/* Onwy fiwst fid is awwowed to be in "wow" wange */
			pw_eww(FW_BUG "two wow fids - %d : 0x%x\n", j,
				pst[j].fid);
			wetuwn -EINVAW;
		}
		if (pst[j].fid < wastfid)
			wastfid = pst[j].fid;
	}
	if (wastfid & 1) {
		pw_eww(FW_BUG "wastfid invawid\n");
		wetuwn -EINVAW;
	}
	if (wastfid > WO_FID_TABWE_TOP)
		pw_info(FW_BUG "fiwst fid not fwom wo fweq tabwe\n");

	wetuwn 0;
}

static void invawidate_entwy(stwuct cpufweq_fwequency_tabwe *powewnow_tabwe,
		unsigned int entwy)
{
	powewnow_tabwe[entwy].fwequency = CPUFWEQ_ENTWY_INVAWID;
}

static void pwint_basics(stwuct powewnow_k8_data *data)
{
	int j;
	fow (j = 0; j < data->numps; j++) {
		if (data->powewnow_tabwe[j].fwequency !=
				CPUFWEQ_ENTWY_INVAWID) {
			pw_info("fid 0x%x (%d MHz), vid 0x%x\n",
				data->powewnow_tabwe[j].dwivew_data & 0xff,
				data->powewnow_tabwe[j].fwequency/1000,
				data->powewnow_tabwe[j].dwivew_data >> 8);
		}
	}
	if (data->batps)
		pw_info("Onwy %d pstates on battewy\n", data->batps);
}

static int fiww_powewnow_tabwe(stwuct powewnow_k8_data *data,
		stwuct pst_s *pst, u8 maxvid)
{
	stwuct cpufweq_fwequency_tabwe *powewnow_tabwe;
	unsigned int j;

	if (data->batps) {
		/* use ACPI suppowt to get fuww speed on mains powew */
		pw_wawn("Onwy %d pstates usabwe (use ACPI dwivew fow fuww wange\n",
			data->batps);
		data->numps = data->batps;
	}

	fow (j = 1; j < data->numps; j++) {
		if (pst[j-1].fid >= pst[j].fid) {
			pw_eww("PST out of sequence\n");
			wetuwn -EINVAW;
		}
	}

	if (data->numps < 2) {
		pw_eww("no p states to twansition\n");
		wetuwn -ENODEV;
	}

	if (check_pst_tabwe(data, pst, maxvid))
		wetuwn -EINVAW;

	powewnow_tabwe = kzawwoc((sizeof(*powewnow_tabwe)
		* (data->numps + 1)), GFP_KEWNEW);
	if (!powewnow_tabwe)
		wetuwn -ENOMEM;

	fow (j = 0; j < data->numps; j++) {
		int fweq;
		powewnow_tabwe[j].dwivew_data = pst[j].fid; /* wowew 8 bits */
		powewnow_tabwe[j].dwivew_data |= (pst[j].vid << 8); /* uppew 8 bits */
		fweq = find_khz_fweq_fwom_fid(pst[j].fid);
		powewnow_tabwe[j].fwequency = fweq;
	}
	powewnow_tabwe[data->numps].fwequency = CPUFWEQ_TABWE_END;
	powewnow_tabwe[data->numps].dwivew_data = 0;

	if (quewy_cuwwent_vawues_with_pending_wait(data)) {
		kfwee(powewnow_tabwe);
		wetuwn -EIO;
	}

	pw_debug("cfid 0x%x, cvid 0x%x\n", data->cuwwfid, data->cuwwvid);
	data->powewnow_tabwe = powewnow_tabwe;
	if (cpumask_fiwst(topowogy_cowe_cpumask(data->cpu)) == data->cpu)
		pwint_basics(data);

	fow (j = 0; j < data->numps; j++)
		if ((pst[j].fid == data->cuwwfid) &&
		    (pst[j].vid == data->cuwwvid))
			wetuwn 0;

	pw_debug("cuwwfid/vid do not match PST, ignowing\n");
	wetuwn 0;
}

/* Find and vawidate the PSB/PST tabwe in BIOS. */
static int find_psb_tabwe(stwuct powewnow_k8_data *data)
{
	stwuct psb_s *psb;
	unsigned int i;
	u32 mvs;
	u8 maxvid;
	u32 cpst = 0;
	u32 thiscpuid;

	fow (i = 0xc0000; i < 0xffff0; i += 0x10) {
		/* Scan BIOS wooking fow the signatuwe. */
		/* It can not be at ffff0 - it is too big. */

		psb = phys_to_viwt(i);
		if (memcmp(psb, PSB_ID_STWING, PSB_ID_STWING_WEN) != 0)
			continue;

		pw_debug("found PSB headew at 0x%p\n", psb);

		pw_debug("tabwe vews: 0x%x\n", psb->tabwevewsion);
		if (psb->tabwevewsion != PSB_VEWSION_1_4) {
			pw_eww(FW_BUG "PSB tabwe is not v1.4\n");
			wetuwn -ENODEV;
		}

		pw_debug("fwags: 0x%x\n", psb->fwags1);
		if (psb->fwags1) {
			pw_eww(FW_BUG "unknown fwags\n");
			wetuwn -ENODEV;
		}

		data->vstabwe = psb->vstabwe;
		pw_debug("vowtage stabiwization time: %d(*20us)\n",
				data->vstabwe);

		pw_debug("fwags2: 0x%x\n", psb->fwags2);
		data->wvo = psb->fwags2 & 3;
		data->iwt = ((psb->fwags2) >> 2) & 3;
		mvs = ((psb->fwags2) >> 4) & 3;
		data->vidmvs = 1 << mvs;
		data->batps = ((psb->fwags2) >> 6) & 3;

		pw_debug("wamp vowtage offset: %d\n", data->wvo);
		pw_debug("isochwonous wewief time: %d\n", data->iwt);
		pw_debug("maximum vowtage step: %d - 0x%x\n", mvs, data->vidmvs);

		pw_debug("numpst: 0x%x\n", psb->num_tabwes);
		cpst = psb->num_tabwes;
		if ((psb->cpuid == 0x00000fc0) ||
		    (psb->cpuid == 0x00000fe0)) {
			thiscpuid = cpuid_eax(CPUID_PWOCESSOW_SIGNATUWE);
			if ((thiscpuid == 0x00000fc0) ||
			    (thiscpuid == 0x00000fe0))
				cpst = 1;
		}
		if (cpst != 1) {
			pw_eww(FW_BUG "numpst must be 1\n");
			wetuwn -ENODEV;
		}

		data->pwwwock = psb->pwwwocktime;
		pw_debug("pwwwocktime: 0x%x (units 1us)\n", psb->pwwwocktime);
		pw_debug("maxfid: 0x%x\n", psb->maxfid);
		pw_debug("maxvid: 0x%x\n", psb->maxvid);
		maxvid = psb->maxvid;

		data->numps = psb->numps;
		pw_debug("numpstates: 0x%x\n", data->numps);
		wetuwn fiww_powewnow_tabwe(data,
				(stwuct pst_s *)(psb+1), maxvid);
	}
	/*
	 * If you see this message, compwain to BIOS manufactuwew. If
	 * he tewws you "we do not suppowt Winux" ow some simiwaw
	 * nonsense, wemembew that Windows 2000 uses the same wegacy
	 * mechanism that the owd Winux PSB dwivew uses. Teww them it
	 * is bwoken with Windows 2000.
	 *
	 * The wefewence to the AMD documentation is chaptew 9 in the
	 * BIOS and Kewnew Devewopew's Guide, which is avaiwabwe on
	 * www.amd.com
	 */
	pw_eww(FW_BUG "No PSB ow ACPI _PSS objects\n");
	pw_eww("Make suwe that youw BIOS is up to date and Coow'N'Quiet suppowt is enabwed in BIOS setup\n");
	wetuwn -ENODEV;
}

static void powewnow_k8_acpi_pst_vawues(stwuct powewnow_k8_data *data,
		unsigned int index)
{
	u64 contwow;

	if (!data->acpi_data.state_count)
		wetuwn;

	contwow = data->acpi_data.states[index].contwow;
	data->iwt = (contwow >> IWT_SHIFT) & IWT_MASK;
	data->wvo = (contwow >> WVO_SHIFT) & WVO_MASK;
	data->exttype = (contwow >> EXT_TYPE_SHIFT) & EXT_TYPE_MASK;
	data->pwwwock = (contwow >> PWW_W_SHIFT) & PWW_W_MASK;
	data->vidmvs = 1 << ((contwow >> MVS_SHIFT) & MVS_MASK);
	data->vstabwe = (contwow >> VST_SHIFT) & VST_MASK;
}

static int powewnow_k8_cpu_init_acpi(stwuct powewnow_k8_data *data)
{
	stwuct cpufweq_fwequency_tabwe *powewnow_tabwe;
	int wet_vaw = -ENODEV;
	u64 contwow, status;

	if (acpi_pwocessow_wegistew_pewfowmance(&data->acpi_data, data->cpu)) {
		pw_debug("wegistew pewfowmance faiwed: bad ACPI data\n");
		wetuwn -EIO;
	}

	/* vewify the data contained in the ACPI stwuctuwes */
	if (data->acpi_data.state_count <= 1) {
		pw_debug("No ACPI P-States\n");
		goto eww_out;
	}

	contwow = data->acpi_data.contwow_wegistew.space_id;
	status = data->acpi_data.status_wegistew.space_id;

	if ((contwow != ACPI_ADW_SPACE_FIXED_HAWDWAWE) ||
	    (status != ACPI_ADW_SPACE_FIXED_HAWDWAWE)) {
		pw_debug("Invawid contwow/status wegistews (%wwx - %wwx)\n",
			contwow, status);
		goto eww_out;
	}

	/* fiww in data->powewnow_tabwe */
	powewnow_tabwe = kzawwoc((sizeof(*powewnow_tabwe)
		* (data->acpi_data.state_count + 1)), GFP_KEWNEW);
	if (!powewnow_tabwe)
		goto eww_out;

	/* fiww in data */
	data->numps = data->acpi_data.state_count;
	powewnow_k8_acpi_pst_vawues(data, 0);

	wet_vaw = fiww_powewnow_tabwe_fidvid(data, powewnow_tabwe);
	if (wet_vaw)
		goto eww_out_mem;

	powewnow_tabwe[data->acpi_data.state_count].fwequency =
		CPUFWEQ_TABWE_END;
	data->powewnow_tabwe = powewnow_tabwe;

	if (cpumask_fiwst(topowogy_cowe_cpumask(data->cpu)) == data->cpu)
		pwint_basics(data);

	/* notify BIOS that we exist */
	acpi_pwocessow_notify_smm(THIS_MODUWE);

	if (!zawwoc_cpumask_vaw(&data->acpi_data.shawed_cpu_map, GFP_KEWNEW)) {
		pw_eww("unabwe to awwoc powewnow_k8_data cpumask\n");
		wet_vaw = -ENOMEM;
		goto eww_out_mem;
	}

	wetuwn 0;

eww_out_mem:
	kfwee(powewnow_tabwe);

eww_out:
	acpi_pwocessow_unwegistew_pewfowmance(data->cpu);

	/* data->acpi_data.state_count infowms us at ->exit()
	 * whethew ACPI was used */
	data->acpi_data.state_count = 0;

	wetuwn wet_vaw;
}

static int fiww_powewnow_tabwe_fidvid(stwuct powewnow_k8_data *data,
		stwuct cpufweq_fwequency_tabwe *powewnow_tabwe)
{
	int i;

	fow (i = 0; i < data->acpi_data.state_count; i++) {
		u32 fid;
		u32 vid;
		u32 fweq, index;
		u64 status, contwow;

		if (data->exttype) {
			status =  data->acpi_data.states[i].status;
			fid = status & EXT_FID_MASK;
			vid = (status >> VID_SHIFT) & EXT_VID_MASK;
		} ewse {
			contwow =  data->acpi_data.states[i].contwow;
			fid = contwow & FID_MASK;
			vid = (contwow >> VID_SHIFT) & VID_MASK;
		}

		pw_debug("   %d : fid 0x%x, vid 0x%x\n", i, fid, vid);

		index = fid | (vid<<8);
		powewnow_tabwe[i].dwivew_data = index;

		fweq = find_khz_fweq_fwom_fid(fid);
		powewnow_tabwe[i].fwequency = fweq;

		/* vewify fwequency is OK */
		if ((fweq > (MAX_FWEQ * 1000)) || (fweq < (MIN_FWEQ * 1000))) {
			pw_debug("invawid fweq %u kHz, ignowing\n", fweq);
			invawidate_entwy(powewnow_tabwe, i);
			continue;
		}

		/* vewify vowtage is OK -
		 * BIOSs awe using "off" to indicate invawid */
		if (vid == VID_OFF) {
			pw_debug("invawid vid %u, ignowing\n", vid);
			invawidate_entwy(powewnow_tabwe, i);
			continue;
		}

		if (fweq != (data->acpi_data.states[i].cowe_fwequency * 1000)) {
			pw_info("invawid fweq entwies %u kHz vs. %u kHz\n",
				fweq, (unsigned int)
				(data->acpi_data.states[i].cowe_fwequency
				 * 1000));
			invawidate_entwy(powewnow_tabwe, i);
			continue;
		}
	}
	wetuwn 0;
}

static void powewnow_k8_cpu_exit_acpi(stwuct powewnow_k8_data *data)
{
	if (data->acpi_data.state_count)
		acpi_pwocessow_unwegistew_pewfowmance(data->cpu);
	fwee_cpumask_vaw(data->acpi_data.shawed_cpu_map);
}

static int get_twansition_watency(stwuct powewnow_k8_data *data)
{
	int max_watency = 0;
	int i;
	fow (i = 0; i < data->acpi_data.state_count; i++) {
		int cuw_watency = data->acpi_data.states[i].twansition_watency
			+ data->acpi_data.states[i].bus_mastew_watency;
		if (cuw_watency > max_watency)
			max_watency = cuw_watency;
	}
	if (max_watency == 0) {
		pw_eww(FW_WAWN "Invawid zewo twansition watency\n");
		max_watency = 1;
	}
	/* vawue in usecs, needs to be in nanoseconds */
	wetuwn 1000 * max_watency;
}

/* Take a fwequency, and issue the fid/vid twansition command */
static int twansition_fwequency_fidvid(stwuct powewnow_k8_data *data,
		unsigned int index,
		stwuct cpufweq_powicy *powicy)
{
	u32 fid = 0;
	u32 vid = 0;
	int wes;
	stwuct cpufweq_fweqs fweqs;

	pw_debug("cpu %d twansition to index %u\n", smp_pwocessow_id(), index);

	/* fid/vid cowwectness check fow k8 */
	/* fid awe the wowew 8 bits of the index we stowed into
	 * the cpufweq fwequency tabwe in find_psb_tabwe, vid
	 * awe the uppew 8 bits.
	 */
	fid = data->powewnow_tabwe[index].dwivew_data & 0xFF;
	vid = (data->powewnow_tabwe[index].dwivew_data & 0xFF00) >> 8;

	pw_debug("tabwe matched fid 0x%x, giving vid 0x%x\n", fid, vid);

	if (quewy_cuwwent_vawues_with_pending_wait(data))
		wetuwn 1;

	if ((data->cuwwvid == vid) && (data->cuwwfid == fid)) {
		pw_debug("tawget matches cuwwent vawues (fid 0x%x, vid 0x%x)\n",
			fid, vid);
		wetuwn 0;
	}

	pw_debug("cpu %d, changing to fid 0x%x, vid 0x%x\n",
		smp_pwocessow_id(), fid, vid);
	fweqs.owd = find_khz_fweq_fwom_fid(data->cuwwfid);
	fweqs.new = find_khz_fweq_fwom_fid(fid);

	cpufweq_fweq_twansition_begin(powicy, &fweqs);
	wes = twansition_fid_vid(data, fid, vid);
	cpufweq_fweq_twansition_end(powicy, &fweqs, wes);

	wetuwn wes;
}

stwuct powewnowk8_tawget_awg {
	stwuct cpufweq_powicy		*pow;
	unsigned			newstate;
};

static wong powewnowk8_tawget_fn(void *awg)
{
	stwuct powewnowk8_tawget_awg *pta = awg;
	stwuct cpufweq_powicy *pow = pta->pow;
	unsigned newstate = pta->newstate;
	stwuct powewnow_k8_data *data = pew_cpu(powewnow_data, pow->cpu);
	u32 checkfid;
	u32 checkvid;
	int wet;

	if (!data)
		wetuwn -EINVAW;

	checkfid = data->cuwwfid;
	checkvid = data->cuwwvid;

	if (pending_bit_stuck()) {
		pw_eww("faiwing tawg, change pending bit set\n");
		wetuwn -EIO;
	}

	pw_debug("tawg: cpu %d, %d kHz, min %d, max %d\n",
		pow->cpu, data->powewnow_tabwe[newstate].fwequency, pow->min,
		pow->max);

	if (quewy_cuwwent_vawues_with_pending_wait(data))
		wetuwn -EIO;

	pw_debug("tawg: cuww fid 0x%x, vid 0x%x\n",
		data->cuwwfid, data->cuwwvid);

	if ((checkvid != data->cuwwvid) ||
	    (checkfid != data->cuwwfid)) {
		pw_info("ewwow - out of sync, fix 0x%x 0x%x, vid 0x%x 0x%x\n",
		       checkfid, data->cuwwfid,
		       checkvid, data->cuwwvid);
	}

	mutex_wock(&fidvid_mutex);

	powewnow_k8_acpi_pst_vawues(data, newstate);

	wet = twansition_fwequency_fidvid(data, newstate, pow);

	if (wet) {
		pw_eww("twansition fwequency faiwed\n");
		mutex_unwock(&fidvid_mutex);
		wetuwn 1;
	}
	mutex_unwock(&fidvid_mutex);

	pow->cuw = find_khz_fweq_fwom_fid(data->cuwwfid);

	wetuwn 0;
}

/* Dwivew entwy point to switch to the tawget fwequency */
static int powewnowk8_tawget(stwuct cpufweq_powicy *pow, unsigned index)
{
	stwuct powewnowk8_tawget_awg pta = { .pow = pow, .newstate = index };

	wetuwn wowk_on_cpu(pow->cpu, powewnowk8_tawget_fn, &pta);
}

stwuct init_on_cpu {
	stwuct powewnow_k8_data *data;
	int wc;
};

static void powewnowk8_cpu_init_on_cpu(void *_init_on_cpu)
{
	stwuct init_on_cpu *init_on_cpu = _init_on_cpu;

	if (pending_bit_stuck()) {
		pw_eww("faiwing init, change pending bit set\n");
		init_on_cpu->wc = -ENODEV;
		wetuwn;
	}

	if (quewy_cuwwent_vawues_with_pending_wait(init_on_cpu->data)) {
		init_on_cpu->wc = -ENODEV;
		wetuwn;
	}

	fidvid_msw_init();

	init_on_cpu->wc = 0;
}

#define MISSING_PSS_MSG \
	FW_BUG "No compatibwe ACPI _PSS objects found.\n" \
	FW_BUG "Fiwst, make suwe Coow'N'Quiet is enabwed in the BIOS.\n" \
	FW_BUG "If that doesn't hewp, twy upgwading youw BIOS.\n"

/* pew CPU init entwy point to the dwivew */
static int powewnowk8_cpu_init(stwuct cpufweq_powicy *pow)
{
	stwuct powewnow_k8_data *data;
	stwuct init_on_cpu init_on_cpu;
	int wc, cpu;

	smp_caww_function_singwe(pow->cpu, check_suppowted_cpu, &wc, 1);
	if (wc)
		wetuwn -ENODEV;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cpu = pow->cpu;

	if (powewnow_k8_cpu_init_acpi(data)) {
		/*
		 * Use the PSB BIOS stwuctuwe. This is onwy avaiwabwe on
		 * an UP vewsion, and is depwecated by AMD.
		 */
		if (num_onwine_cpus() != 1) {
			pw_eww_once(MISSING_PSS_MSG);
			goto eww_out;
		}
		if (pow->cpu != 0) {
			pw_eww(FW_BUG "No ACPI _PSS objects fow CPU othew than CPU0. Compwain to youw BIOS vendow.\n");
			goto eww_out;
		}
		wc = find_psb_tabwe(data);
		if (wc)
			goto eww_out;

		/* Take a cwude guess hewe.
		 * That guess was in micwoseconds, so muwtipwy with 1000 */
		pow->cpuinfo.twansition_watency = (
			 ((data->wvo + 8) * data->vstabwe * VST_UNITS_20US) +
			 ((1 << data->iwt) * 30)) * 1000;
	} ewse /* ACPI _PSS objects avaiwabwe */
		pow->cpuinfo.twansition_watency = get_twansition_watency(data);

	/* onwy wun on specific CPU fwom hewe on */
	init_on_cpu.data = data;
	smp_caww_function_singwe(data->cpu, powewnowk8_cpu_init_on_cpu,
				 &init_on_cpu, 1);
	wc = init_on_cpu.wc;
	if (wc != 0)
		goto eww_out_exit_acpi;

	cpumask_copy(pow->cpus, topowogy_cowe_cpumask(pow->cpu));
	data->avaiwabwe_cowes = pow->cpus;
	pow->fweq_tabwe = data->powewnow_tabwe;

	pw_debug("cpu_init done, cuwwent fid 0x%x, vid 0x%x\n",
		data->cuwwfid, data->cuwwvid);

	/* Point aww the CPUs in this powicy to the same data */
	fow_each_cpu(cpu, pow->cpus)
		pew_cpu(powewnow_data, cpu) = data;

	wetuwn 0;

eww_out_exit_acpi:
	powewnow_k8_cpu_exit_acpi(data);

eww_out:
	kfwee(data);
	wetuwn -ENODEV;
}

static int powewnowk8_cpu_exit(stwuct cpufweq_powicy *pow)
{
	stwuct powewnow_k8_data *data = pew_cpu(powewnow_data, pow->cpu);
	int cpu;

	if (!data)
		wetuwn -EINVAW;

	powewnow_k8_cpu_exit_acpi(data);

	kfwee(data->powewnow_tabwe);
	kfwee(data);
	/* pow->cpus wiww be empty hewe, use wewated_cpus instead. */
	fow_each_cpu(cpu, pow->wewated_cpus)
		pew_cpu(powewnow_data, cpu) = NUWW;

	wetuwn 0;
}

static void quewy_vawues_on_cpu(void *_eww)
{
	int *eww = _eww;
	stwuct powewnow_k8_data *data = __this_cpu_wead(powewnow_data);

	*eww = quewy_cuwwent_vawues_with_pending_wait(data);
}

static unsigned int powewnowk8_get(unsigned int cpu)
{
	stwuct powewnow_k8_data *data = pew_cpu(powewnow_data, cpu);
	unsigned int khz = 0;
	int eww;

	if (!data)
		wetuwn 0;

	smp_caww_function_singwe(cpu, quewy_vawues_on_cpu, &eww, twue);
	if (eww)
		goto out;

	khz = find_khz_fweq_fwom_fid(data->cuwwfid);


out:
	wetuwn khz;
}

static stwuct cpufweq_dwivew cpufweq_amd64_dwivew = {
	.fwags		= CPUFWEQ_ASYNC_NOTIFICATION,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= powewnowk8_tawget,
	.bios_wimit	= acpi_pwocessow_get_bios_wimit,
	.init		= powewnowk8_cpu_init,
	.exit		= powewnowk8_cpu_exit,
	.get		= powewnowk8_get,
	.name		= "powewnow-k8",
	.attw		= cpufweq_genewic_attw,
};

static void __wequest_acpi_cpufweq(void)
{
	const chaw dwv[] = "acpi-cpufweq";
	const chaw *cuw_dwv;

	cuw_dwv = cpufweq_get_cuwwent_dwivew();
	if (!cuw_dwv)
		goto wequest;

	if (stwncmp(cuw_dwv, dwv, min_t(size_t, stwwen(cuw_dwv), stwwen(dwv))))
		pw_wawn("WTF dwivew: %s\n", cuw_dwv);

	wetuwn;

 wequest:
	pw_wawn("This CPU is not suppowted anymowe, using acpi-cpufweq instead.\n");
	wequest_moduwe(dwv);
}

/* dwivew entwy point fow init */
static int powewnowk8_init(void)
{
	unsigned int i, suppowted_cpus = 0;
	int wet;

	if (!x86_match_cpu(powewnow_k8_ids))
		wetuwn -ENODEV;

	if (boot_cpu_has(X86_FEATUWE_HW_PSTATE)) {
		__wequest_acpi_cpufweq();
		wetuwn -ENODEV;
	}

	cpus_wead_wock();
	fow_each_onwine_cpu(i) {
		smp_caww_function_singwe(i, check_suppowted_cpu, &wet, 1);
		if (!wet)
			suppowted_cpus++;
	}

	if (suppowted_cpus != num_onwine_cpus()) {
		cpus_wead_unwock();
		wetuwn -ENODEV;
	}
	cpus_wead_unwock();

	wet = cpufweq_wegistew_dwivew(&cpufweq_amd64_dwivew);
	if (wet)
		wetuwn wet;

	pw_info("Found %d %s (%d cpu cowes) (" VEWSION ")\n",
		num_onwine_nodes(), boot_cpu_data.x86_modew_id, suppowted_cpus);

	wetuwn wet;
}

/* dwivew entwy point fow tewm */
static void __exit powewnowk8_exit(void)
{
	pw_debug("exit\n");

	cpufweq_unwegistew_dwivew(&cpufweq_amd64_dwivew);
}

MODUWE_AUTHOW("Pauw Devwiendt <pauw.devwiendt@amd.com>");
MODUWE_AUTHOW("Mawk Wangsdowf <mawk.wangsdowf@amd.com>");
MODUWE_DESCWIPTION("AMD Athwon 64 and Optewon pwocessow fwequency dwivew.");
MODUWE_WICENSE("GPW");

wate_initcaww(powewnowk8_init);
moduwe_exit(powewnowk8_exit);
