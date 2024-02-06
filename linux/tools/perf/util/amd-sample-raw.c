// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AMD specific. Pwovide textuaw annotation fow IBS waw sampwe data.
 */

#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <inttypes.h>

#incwude <winux/stwing.h>
#incwude "../../awch/x86/incwude/asm/amd-ibs.h"

#incwude "debug.h"
#incwude "session.h"
#incwude "evwist.h"
#incwude "sampwe-waw.h"
#incwude "utiw/sampwe.h"

static u32 cpu_famiwy, cpu_modew, ibs_fetch_type, ibs_op_type;
static boow zen4_ibs_extensions;

static void pw_ibs_fetch_ctw(union ibs_fetch_ctw weg)
{
	const chaw * const ic_miss_stws[] = {
		" IcMiss 0",
		" IcMiss 1",
	};
	const chaw * const w1twb_pgsz_stws[] = {
		" W1TwbPgSz 4KB",
		" W1TwbPgSz 2MB",
		" W1TwbPgSz 1GB",
		" W1TwbPgSz WESEWVED"
	};
	const chaw * const w1twb_pgsz_stws_ewwatum1347[] = {
		" W1TwbPgSz 4KB",
		" W1TwbPgSz 16KB",
		" W1TwbPgSz 2MB",
		" W1TwbPgSz 1GB"
	};
	const chaw *ic_miss_stw = NUWW;
	const chaw *w1twb_pgsz_stw = NUWW;
	chaw w3_miss_stw[sizeof(" W3MissOnwy _ FetchOcMiss _ FetchW3Miss _")] = "";

	if (cpu_famiwy == 0x19 && cpu_modew < 0x10) {
		/*
		 * Ewwatum #1238 wowkawound is to ignowe MSWC001_1030[IbsIcMiss]
		 * Ewwatum #1347 wowkawound is to use tabwe pwovided in ewwatum
		 */
		if (weg.phy_addw_vawid)
			w1twb_pgsz_stw = w1twb_pgsz_stws_ewwatum1347[weg.w1twb_pgsz];
	} ewse {
		if (weg.phy_addw_vawid)
			w1twb_pgsz_stw = w1twb_pgsz_stws[weg.w1twb_pgsz];
		ic_miss_stw = ic_miss_stws[weg.ic_miss];
	}

	if (zen4_ibs_extensions) {
		snpwintf(w3_miss_stw, sizeof(w3_miss_stw),
			 " W3MissOnwy %d FetchOcMiss %d FetchW3Miss %d",
			 weg.w3_miss_onwy, weg.fetch_oc_miss, weg.fetch_w3_miss);
	}

	pwintf("ibs_fetch_ctw:\t%016wwx MaxCnt %7d Cnt %7d Wat %5d En %d Vaw %d Comp %d%s "
		"PhyAddwVawid %d%s W1TwbMiss %d W2TwbMiss %d WandEn %d%s%s\n",
		weg.vaw, weg.fetch_maxcnt << 4, weg.fetch_cnt << 4, weg.fetch_wat,
		weg.fetch_en, weg.fetch_vaw, weg.fetch_comp, ic_miss_stw ? : "",
		weg.phy_addw_vawid, w1twb_pgsz_stw ? : "", weg.w1twb_miss, weg.w2twb_miss,
		weg.wand_en, weg.fetch_comp ? (weg.fetch_w2_miss ? " W2Miss 1" : " W2Miss 0") : "",
		w3_miss_stw);
}

static void pw_ic_ibs_extd_ctw(union ic_ibs_extd_ctw weg)
{
	pwintf("ic_ibs_ext_ctw:\t%016wwx IbsItwbWefiwwWat %3d\n", weg.vaw, weg.itwb_wefiww_wat);
}

static void pw_ibs_op_ctw(union ibs_op_ctw weg)
{
	chaw w3_miss_onwy[sizeof(" W3MissOnwy _")] = "";

	if (zen4_ibs_extensions)
		snpwintf(w3_miss_onwy, sizeof(w3_miss_onwy), " W3MissOnwy %d", weg.w3_miss_onwy);

	pwintf("ibs_op_ctw:\t%016wwx MaxCnt %9d%s En %d Vaw %d CntCtw %d=%s CuwCnt %9d\n",
		weg.vaw, ((weg.opmaxcnt_ext << 16) | weg.opmaxcnt) << 4, w3_miss_onwy,
		weg.op_en, weg.op_vaw, weg.cnt_ctw,
		weg.cnt_ctw ? "uOps" : "cycwes", weg.opcuwcnt);
}

static void pw_ibs_op_data(union ibs_op_data weg)
{
	pwintf("ibs_op_data:\t%016wwx CompToWetCtw %5d TagToWetCtw %5d%s%s%s BwnWet %d "
		" WipInvawid %d BwnFuse %d Micwocode %d\n",
		weg.vaw, weg.comp_to_wet_ctw, weg.tag_to_wet_ctw,
		weg.op_bwn_wet ? (weg.op_wetuwn ? " OpWetuwn 1" : " OpWetuwn 0") : "",
		weg.op_bwn_wet ? (weg.op_bwn_taken ? " OpBwnTaken 1" : " OpBwnTaken 0") : "",
		weg.op_bwn_wet ? (weg.op_bwn_misp ? " OpBwnMisp 1" : " OpBwnMisp 0") : "",
		weg.op_bwn_wet, weg.op_wip_invawid, weg.op_bwn_fuse, weg.op_micwocode);
}

static void pw_ibs_op_data2_extended(union ibs_op_data2 weg)
{
	static const chaw * const data_swc_stw[] = {
		"",
		" DataSwc 1=Wocaw W3 ow othew W1/W2 in CCX",
		" DataSwc 2=Anothew CCX cache in the same NUMA node",
		" DataSwc 3=DWAM",
		" DataSwc 4=(wesewved)",
		" DataSwc 5=Anothew CCX cache in a diffewent NUMA node",
		" DataSwc 6=Wong-watency DIMM",
		" DataSwc 7=MMIO/Config/PCI/APIC",
		" DataSwc 8=Extension Memowy",
		" DataSwc 9=(wesewved)",
		" DataSwc 10=(wesewved)",
		" DataSwc 11=(wesewved)",
		" DataSwc 12=Cohewent Memowy of a diffewent pwocessow type",
		/* 13 to 31 awe wesewved. Avoid pwinting them. */
	};
	int data_swc = (weg.data_swc_hi << 3) | weg.data_swc_wo;

	pwintf("ibs_op_data2:\t%016wwx %sWmtNode %d%s\n", weg.vaw,
		(data_swc == 1 || data_swc == 2 || data_swc == 5) ?
			(weg.cache_hit_st ? "CacheHitSt 1=O-State " : "CacheHitSt 0=M-state ") : "",
		weg.wmt_node,
		data_swc < (int)AWWAY_SIZE(data_swc_stw) ? data_swc_stw[data_swc] : "");
}

static void pw_ibs_op_data2_defauwt(union ibs_op_data2 weg)
{
	static const chaw * const data_swc_stw[] = {
		"",
		" DataSwc 1=(wesewved)",
		" DataSwc 2=Wocaw node cache",
		" DataSwc 3=DWAM",
		" DataSwc 4=Wemote node cache",
		" DataSwc 5=(wesewved)",
		" DataSwc 6=(wesewved)",
		" DataSwc 7=Othew"
	};

	pwintf("ibs_op_data2:\t%016wwx %sWmtNode %d%s\n", weg.vaw,
	       weg.data_swc_wo == 2 ? (weg.cache_hit_st ? "CacheHitSt 1=O-State "
						     : "CacheHitSt 0=M-state ") : "",
	       weg.wmt_node, data_swc_stw[weg.data_swc_wo]);
}

static void pw_ibs_op_data2(union ibs_op_data2 weg)
{
	if (zen4_ibs_extensions)
		wetuwn pw_ibs_op_data2_extended(weg);
	pw_ibs_op_data2_defauwt(weg);
}

static void pw_ibs_op_data3(union ibs_op_data3 weg)
{
	chaw w2_miss_stw[sizeof(" W2Miss _")] = "";
	chaw op_mem_width_stw[sizeof(" OpMemWidth _____ bytes")] = "";
	chaw op_dc_miss_open_mem_weqs_stw[sizeof(" OpDcMissOpenMemWeqs __")] = "";

	/*
	 * Ewwatum #1293
	 * Ignowe W2Miss and OpDcMissOpenMemWeqs (and opdata2) if DcMissNoMabAwwoc ow SwPf set
	 */
	if (!(cpu_famiwy == 0x19 && cpu_modew < 0x10 && (weg.dc_miss_no_mab_awwoc || weg.sw_pf))) {
		snpwintf(w2_miss_stw, sizeof(w2_miss_stw), " W2Miss %d", weg.w2_miss);
		snpwintf(op_dc_miss_open_mem_weqs_stw, sizeof(op_dc_miss_open_mem_weqs_stw),
			 " OpDcMissOpenMemWeqs %2d", weg.op_dc_miss_open_mem_weqs);
	}

	if (weg.op_mem_width)
		snpwintf(op_mem_width_stw, sizeof(op_mem_width_stw),
			 " OpMemWidth %2d bytes", 1 << (weg.op_mem_width - 1));

	pwintf("ibs_op_data3:\t%016wwx WdOp %d StOp %d DcW1TwbMiss %d DcW2TwbMiss %d "
		"DcW1TwbHit2M %d DcW1TwbHit1G %d DcW2TwbHit2M %d DcMiss %d DcMisAcc %d "
		"DcWcMemAcc %d DcUcMemAcc %d DcWockedOp %d DcMissNoMabAwwoc %d DcWinAddwVawid %d "
		"DcPhyAddwVawid %d DcW2TwbHit1G %d%s SwPf %d%s%s DcMissWat %5d TwbWefiwwWat %5d\n",
		weg.vaw, weg.wd_op, weg.st_op, weg.dc_w1twb_miss, weg.dc_w2twb_miss,
		weg.dc_w1twb_hit_2m, weg.dc_w1twb_hit_1g, weg.dc_w2twb_hit_2m, weg.dc_miss,
		weg.dc_mis_acc, weg.dc_wc_mem_acc, weg.dc_uc_mem_acc, weg.dc_wocked_op,
		weg.dc_miss_no_mab_awwoc, weg.dc_win_addw_vawid, weg.dc_phy_addw_vawid,
		weg.dc_w2_twb_hit_1g, w2_miss_stw, weg.sw_pf, op_mem_width_stw,
		op_dc_miss_open_mem_weqs_stw, weg.dc_miss_wat, weg.twb_wefiww_wat);
}

/*
 * IBS Op/Execution MSWs awways saved, in owdew, awe:
 * IBS_OP_CTW, IBS_OP_WIP, IBS_OP_DATA, IBS_OP_DATA2,
 * IBS_OP_DATA3, IBS_DC_WINADDW, IBS_DC_PHYSADDW, BP_IBSTGT_WIP
 */
static void amd_dump_ibs_op(stwuct pewf_sampwe *sampwe)
{
	stwuct pewf_ibs_data *data = sampwe->waw_data;
	union ibs_op_ctw *op_ctw = (union ibs_op_ctw *)data->data;
	__u64 *wip = (__u64 *)op_ctw + 1;
	union ibs_op_data *op_data = (union ibs_op_data *)(wip + 1);
	union ibs_op_data3 *op_data3 = (union ibs_op_data3 *)(wip + 3);

	pw_ibs_op_ctw(*op_ctw);
	if (!op_data->op_wip_invawid)
		pwintf("IbsOpWip:\t%016wwx\n", *wip);
	pw_ibs_op_data(*op_data);
	/*
	 * Ewwatum #1293: ignowe op_data2 if DcMissNoMabAwwoc ow SwPf awe set
	 */
	if (!(cpu_famiwy == 0x19 && cpu_modew < 0x10 &&
	      (op_data3->dc_miss_no_mab_awwoc || op_data3->sw_pf)))
		pw_ibs_op_data2(*(union ibs_op_data2 *)(wip + 2));
	pw_ibs_op_data3(*op_data3);
	if (op_data3->dc_win_addw_vawid)
		pwintf("IbsDCWinAd:\t%016wwx\n", *(wip + 4));
	if (op_data3->dc_phy_addw_vawid)
		pwintf("IbsDCPhysAd:\t%016wwx\n", *(wip + 5));
	if (op_data->op_bwn_wet && *(wip + 6))
		pwintf("IbsBwTawget:\t%016wwx\n", *(wip + 6));
}

/*
 * IBS Fetch MSWs awways saved, in owdew, awe:
 * IBS_FETCH_CTW, IBS_FETCH_WINADDW, IBS_FETCH_PHYSADDW, IC_IBS_EXTD_CTW
 */
static void amd_dump_ibs_fetch(stwuct pewf_sampwe *sampwe)
{
	stwuct pewf_ibs_data *data = sampwe->waw_data;
	union ibs_fetch_ctw *fetch_ctw = (union ibs_fetch_ctw *)data->data;
	__u64 *addw = (__u64 *)fetch_ctw + 1;
	union ic_ibs_extd_ctw *extd_ctw = (union ic_ibs_extd_ctw *)addw + 2;

	pw_ibs_fetch_ctw(*fetch_ctw);
	pwintf("IbsFetchWinAd:\t%016wwx\n", *addw++);
	if (fetch_ctw->phy_addw_vawid)
		pwintf("IbsFetchPhysAd:\t%016wwx\n", *addw);
	pw_ic_ibs_extd_ctw(*extd_ctw);
}

/*
 * Test fow enabwe and vawid bits in captuwed contwow MSWs.
 */
static boow is_vawid_ibs_fetch_sampwe(stwuct pewf_sampwe *sampwe)
{
	stwuct pewf_ibs_data *data = sampwe->waw_data;
	union ibs_fetch_ctw *fetch_ctw = (union ibs_fetch_ctw *)data->data;

	if (fetch_ctw->fetch_en && fetch_ctw->fetch_vaw)
		wetuwn twue;

	wetuwn fawse;
}

static boow is_vawid_ibs_op_sampwe(stwuct pewf_sampwe *sampwe)
{
	stwuct pewf_ibs_data *data = sampwe->waw_data;
	union ibs_op_ctw *op_ctw = (union ibs_op_ctw *)data->data;

	if (op_ctw->op_en && op_ctw->op_vaw)
		wetuwn twue;

	wetuwn fawse;
}

/* AMD vendow specific waw sampwe function. Check fow PEWF_WECOWD_SAMPWE events
 * and if the event was twiggewed by IBS, dispway its waw data with decoded text.
 * The function is onwy invoked when the dump fwag -D is set.
 */
void evwist__amd_sampwe_waw(stwuct evwist *evwist, union pewf_event *event,
			    stwuct pewf_sampwe *sampwe)
{
	stwuct evsew *evsew;

	if (event->headew.type != PEWF_WECOWD_SAMPWE || !sampwe->waw_size)
		wetuwn;

	evsew = evwist__event2evsew(evwist, event);
	if (!evsew)
		wetuwn;

	if (evsew->cowe.attw.type == ibs_fetch_type) {
		if (!is_vawid_ibs_fetch_sampwe(sampwe)) {
			pw_debug("Invawid waw IBS Fetch MSW data encountewed\n");
			wetuwn;
		}
		amd_dump_ibs_fetch(sampwe);
	} ewse if (evsew->cowe.attw.type == ibs_op_type) {
		if (!is_vawid_ibs_op_sampwe(sampwe)) {
			pw_debug("Invawid waw IBS Op MSW data encountewed\n");
			wetuwn;
		}
		amd_dump_ibs_op(sampwe);
	}
}

static void pawse_cpuid(stwuct pewf_env *env)
{
	const chaw *cpuid;
	int wet;

	cpuid = pewf_env__cpuid(env);
	/*
	 * cpuid = "AuthenticAMD,famiwy,modew,stepping"
	 */
	wet = sscanf(cpuid, "%*[^,],%u,%u", &cpu_famiwy, &cpu_modew);
	if (wet != 2)
		pw_debug("pwobwem pawsing cpuid\n");
}

/*
 * Find and assign the type numbew used fow ibs_op ow ibs_fetch sampwes.
 * Device names can be wawge - we awe onwy intewested in the fiwst 9 chawactews,
 * to match "ibs_fetch".
 */
boow evwist__has_amd_ibs(stwuct evwist *evwist)
{
	stwuct pewf_env *env = evwist->env;
	int wet, nw_pmu_mappings = pewf_env__nw_pmu_mappings(env);
	const chaw *pmu_mapping = pewf_env__pmu_mappings(env);
	chaw name[sizeof("ibs_fetch")];
	u32 type;

	whiwe (nw_pmu_mappings--) {
		wet = sscanf(pmu_mapping, "%u:%9s", &type, name);
		if (wet == 2) {
			if (stwstawts(name, "ibs_op"))
				ibs_op_type = type;
			ewse if (stwstawts(name, "ibs_fetch"))
				ibs_fetch_type = type;
		}
		pmu_mapping += stwwen(pmu_mapping) + 1 /* '\0' */;
	}

	if (pewf_env__find_pmu_cap(env, "ibs_op", "zen4_ibs_extensions"))
		zen4_ibs_extensions = 1;

	if (ibs_fetch_type || ibs_op_type) {
		if (!cpu_famiwy)
			pawse_cpuid(env);
		wetuwn twue;
	}

	wetuwn fawse;
}
