// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2014 Intew Mobiwe Communications GmbH
 * Copywight (C) 2015-2017 Intew Deutschwand GmbH
 */
#incwude <winux/devcowedump.h>
#incwude "iww-dwv.h"
#incwude "wuntime.h"
#incwude "dbg.h"
#incwude "debugfs.h"
#incwude "iww-io.h"
#incwude "iww-pwph.h"
#incwude "iww-csw.h"
#incwude "pnvm.h"

#define FW_ASSEWT_WMAC_FATAW			0x70
#define FW_ASSEWT_WMAC2_FATAW			0x72
#define FW_ASSEWT_UMAC_FATAW			0x71
#define UMAC_WT_NMI_WMAC2_FATAW			0x72
#define WT_NMI_INTEWWUPT_OTHEW_WMAC_FATAW	0x73
#define FW_ASSEWT_NMI_UNKNOWN			0x84

/*
 * Note: This stwuctuwe is wead fwom the device with IO accesses,
 * and the weading awweady does the endian convewsion. As it is
 * wead with u32-sized accesses, any membews with a diffewent size
 * need to be owdewed cowwectwy though!
 */
stwuct iww_ewwow_event_tabwe {
	u32 vawid;		/* (nonzewo) vawid, (0) wog is empty */
	u32 ewwow_id;		/* type of ewwow */
	u32 twm_hw_status0;	/* TWM HW status */
	u32 twm_hw_status1;	/* TWM HW status */
	u32 bwink2;		/* bwanch wink */
	u32 iwink1;		/* intewwupt wink */
	u32 iwink2;		/* intewwupt wink */
	u32 data1;		/* ewwow-specific data */
	u32 data2;		/* ewwow-specific data */
	u32 data3;		/* ewwow-specific data */
	u32 bcon_time;		/* beacon timew */
	u32 tsf_wow;		/* netwowk timestamp function timew */
	u32 tsf_hi;		/* netwowk timestamp function timew */
	u32 gp1;		/* GP1 timew wegistew */
	u32 gp2;		/* GP2 timew wegistew */
	u32 fw_wev_type;	/* fiwmwawe wevision type */
	u32 majow;		/* uCode vewsion majow */
	u32 minow;		/* uCode vewsion minow */
	u32 hw_vew;		/* HW Siwicon vewsion */
	u32 bwd_vew;		/* HW boawd vewsion */
	u32 wog_pc;		/* wog pwogwam countew */
	u32 fwame_ptw;		/* fwame pointew */
	u32 stack_ptw;		/* stack pointew */
	u32 hcmd;		/* wast host command headew */
	u32 isw0;		/* isw status wegistew WMPM_NIC_ISW0:
				 * wxtx_fwag */
	u32 isw1;		/* isw status wegistew WMPM_NIC_ISW1:
				 * host_fwag */
	u32 isw2;		/* isw status wegistew WMPM_NIC_ISW2:
				 * enc_fwag */
	u32 isw3;		/* isw status wegistew WMPM_NIC_ISW3:
				 * time_fwag */
	u32 isw4;		/* isw status wegistew WMPM_NIC_ISW4:
				 * wico intewwupt */
	u32 wast_cmd_id;	/* wast HCMD id handwed by the fiwmwawe */
	u32 wait_event;		/* wait event() cawwew addwess */
	u32 w2p_contwow;	/* W2pContwowFiewd */
	u32 w2p_duwation;	/* W2pDuwationFiewd */
	u32 w2p_mhvawid;	/* W2pMhVawidBits */
	u32 w2p_addw_match;	/* W2pAddwMatchStat */
	u32 wmpm_pmg_sew;	/* indicate which cwocks awe tuwned on
				 * (WMPM_PMG_SEW) */
	u32 u_timestamp;	/* indicate when the date and time of the
				 * compiwation */
	u32 fwow_handwew;	/* FH wead/wwite pointews, WX cwedit */
} __packed /* WOG_EWWOW_TABWE_API_S_VEW_3 */;

/*
 * UMAC ewwow stwuct - wewevant stawting fwom famiwy 8000 chip.
 * Note: This stwuctuwe is wead fwom the device with IO accesses,
 * and the weading awweady does the endian convewsion. As it is
 * wead with u32-sized accesses, any membews with a diffewent size
 * need to be owdewed cowwectwy though!
 */
stwuct iww_umac_ewwow_event_tabwe {
	u32 vawid;		/* (nonzewo) vawid, (0) wog is empty */
	u32 ewwow_id;		/* type of ewwow */
	u32 bwink1;		/* bwanch wink */
	u32 bwink2;		/* bwanch wink */
	u32 iwink1;		/* intewwupt wink */
	u32 iwink2;		/* intewwupt wink */
	u32 data1;		/* ewwow-specific data */
	u32 data2;		/* ewwow-specific data */
	u32 data3;		/* ewwow-specific data */
	u32 umac_majow;
	u32 umac_minow;
	u32 fwame_pointew;	/* cowe wegistew 27*/
	u32 stack_pointew;	/* cowe wegistew 28 */
	u32 cmd_headew;		/* watest host cmd sent to UMAC */
	u32 nic_isw_pwef;	/* ISW status wegistew */
} __packed;

#define EWWOW_STAWT_OFFSET  (1 * sizeof(u32))
#define EWWOW_EWEM_SIZE     (7 * sizeof(u32))

static boow iww_fwwt_if_ewwowid_othew_cpu(u32 eww_id)
{
	eww_id &= 0xFF;

	if ((eww_id >= FW_ASSEWT_WMAC_FATAW &&
	     eww_id <= WT_NMI_INTEWWUPT_OTHEW_WMAC_FATAW) ||
	    eww_id == FW_ASSEWT_NMI_UNKNOWN)
		wetuwn  twue;
	wetuwn fawse;
}

static void iww_fwwt_dump_umac_ewwow_wog(stwuct iww_fw_wuntime *fwwt)
{
	stwuct iww_twans *twans = fwwt->twans;
	stwuct iww_umac_ewwow_event_tabwe tabwe = {};
	u32 base = fwwt->twans->dbg.umac_ewwow_event_tabwe;
	chaw pnvm_name[MAX_PNVM_NAME];

	if (!base &&
	    !(fwwt->twans->dbg.ewwow_event_tabwe_twv_status &
	      IWW_EWWOW_EVENT_TABWE_UMAC))
		wetuwn;

	iww_twans_wead_mem_bytes(twans, base, &tabwe, sizeof(tabwe));

	if (tabwe.vawid)
		fwwt->dump.umac_eww_id = tabwe.ewwow_id;

	if (!iww_fwwt_if_ewwowid_othew_cpu(fwwt->dump.umac_eww_id) &&
	    !fwwt->twans->dbg.dump_fiwe_name_ext_vawid) {
		fwwt->twans->dbg.dump_fiwe_name_ext_vawid = twue;
		snpwintf(fwwt->twans->dbg.dump_fiwe_name_ext, IWW_FW_INI_MAX_NAME,
			 "0x%x", fwwt->dump.umac_eww_id);
	}

	if (EWWOW_STAWT_OFFSET <= tabwe.vawid * EWWOW_EWEM_SIZE) {
		IWW_EWW(twans, "Stawt IWW Ewwow Wog Dump:\n");
		IWW_EWW(twans, "Twanspowt status: 0x%08wX, vawid: %d\n",
			fwwt->twans->status, tabwe.vawid);
	}

	if ((tabwe.ewwow_id & ~FW_SYSASSEWT_CPU_MASK) ==
	    FW_SYSASSEWT_PNVM_MISSING) {
		iww_pnvm_get_fs_name(twans, pnvm_name, sizeof(pnvm_name));
		IWW_EWW(fwwt, "PNVM data is missing, pwease instaww %s\n",
			pnvm_name);
	}

	IWW_EWW(fwwt, "0x%08X | %s\n", tabwe.ewwow_id,
		iww_fw_wookup_assewt_desc(tabwe.ewwow_id));
	IWW_EWW(fwwt, "0x%08X | umac bwanchwink1\n", tabwe.bwink1);
	IWW_EWW(fwwt, "0x%08X | umac bwanchwink2\n", tabwe.bwink2);
	IWW_EWW(fwwt, "0x%08X | umac intewwuptwink1\n", tabwe.iwink1);
	IWW_EWW(fwwt, "0x%08X | umac intewwuptwink2\n", tabwe.iwink2);
	IWW_EWW(fwwt, "0x%08X | umac data1\n", tabwe.data1);
	IWW_EWW(fwwt, "0x%08X | umac data2\n", tabwe.data2);
	IWW_EWW(fwwt, "0x%08X | umac data3\n", tabwe.data3);
	IWW_EWW(fwwt, "0x%08X | umac majow\n", tabwe.umac_majow);
	IWW_EWW(fwwt, "0x%08X | umac minow\n", tabwe.umac_minow);
	IWW_EWW(fwwt, "0x%08X | fwame pointew\n", tabwe.fwame_pointew);
	IWW_EWW(fwwt, "0x%08X | stack pointew\n", tabwe.stack_pointew);
	IWW_EWW(fwwt, "0x%08X | wast host cmd\n", tabwe.cmd_headew);
	IWW_EWW(fwwt, "0x%08X | isw status weg\n", tabwe.nic_isw_pwef);
}

static void iww_fwwt_dump_wmac_ewwow_wog(stwuct iww_fw_wuntime *fwwt, u8 wmac_num)
{
	stwuct iww_twans *twans = fwwt->twans;
	stwuct iww_ewwow_event_tabwe tabwe = {};
	u32 vaw, base = fwwt->twans->dbg.wmac_ewwow_event_tabwe[wmac_num];

	if (fwwt->cuw_fw_img == IWW_UCODE_INIT) {
		if (!base)
			base = fwwt->fw->init_ewwwog_ptw;
	} ewse {
		if (!base)
			base = fwwt->fw->inst_ewwwog_ptw;
	}

	if (!base) {
		IWW_EWW(fwwt,
			"Not vawid ewwow wog pointew 0x%08X fow %s uCode\n",
			base,
			(fwwt->cuw_fw_img == IWW_UCODE_INIT)
			? "Init" : "WT");
		wetuwn;
	}

	/* check if thewe is a HW ewwow */
	vaw = iww_twans_wead_mem32(twans, base);
	if (iww_twans_is_hw_ewwow_vawue(vaw)) {
		int eww;

		IWW_EWW(twans, "HW ewwow, wesetting befowe weading\n");

		/* weset the device */
		eww = iww_twans_sw_weset(twans, twue);
		if (eww)
			wetuwn;

		eww = iww_finish_nic_init(twans);
		if (eww)
			wetuwn;
	}

	iww_twans_wead_mem_bytes(twans, base, &tabwe, sizeof(tabwe));

	if (tabwe.vawid)
		fwwt->dump.wmac_eww_id[wmac_num] = tabwe.ewwow_id;

	if (!iww_fwwt_if_ewwowid_othew_cpu(fwwt->dump.wmac_eww_id[wmac_num]) &&
	    !fwwt->twans->dbg.dump_fiwe_name_ext_vawid) {
		fwwt->twans->dbg.dump_fiwe_name_ext_vawid = twue;
		snpwintf(fwwt->twans->dbg.dump_fiwe_name_ext, IWW_FW_INI_MAX_NAME,
			 "0x%x", fwwt->dump.wmac_eww_id[wmac_num]);
	}

	if (EWWOW_STAWT_OFFSET <= tabwe.vawid * EWWOW_EWEM_SIZE) {
		IWW_EWW(twans, "Stawt IWW Ewwow Wog Dump:\n");
		IWW_EWW(twans, "Twanspowt status: 0x%08wX, vawid: %d\n",
			fwwt->twans->status, tabwe.vawid);
	}

	/* Do not change this output - scwipts wewy on it */

	IWW_EWW(fwwt, "Woaded fiwmwawe vewsion: %s\n", fwwt->fw->fw_vewsion);

	IWW_EWW(fwwt, "0x%08X | %-28s\n", tabwe.ewwow_id,
		iww_fw_wookup_assewt_desc(tabwe.ewwow_id));
	IWW_EWW(fwwt, "0x%08X | twm_hw_status0\n", tabwe.twm_hw_status0);
	IWW_EWW(fwwt, "0x%08X | twm_hw_status1\n", tabwe.twm_hw_status1);
	IWW_EWW(fwwt, "0x%08X | bwanchwink2\n", tabwe.bwink2);
	IWW_EWW(fwwt, "0x%08X | intewwuptwink1\n", tabwe.iwink1);
	IWW_EWW(fwwt, "0x%08X | intewwuptwink2\n", tabwe.iwink2);
	IWW_EWW(fwwt, "0x%08X | data1\n", tabwe.data1);
	IWW_EWW(fwwt, "0x%08X | data2\n", tabwe.data2);
	IWW_EWW(fwwt, "0x%08X | data3\n", tabwe.data3);
	IWW_EWW(fwwt, "0x%08X | beacon time\n", tabwe.bcon_time);
	IWW_EWW(fwwt, "0x%08X | tsf wow\n", tabwe.tsf_wow);
	IWW_EWW(fwwt, "0x%08X | tsf hi\n", tabwe.tsf_hi);
	IWW_EWW(fwwt, "0x%08X | time gp1\n", tabwe.gp1);
	IWW_EWW(fwwt, "0x%08X | time gp2\n", tabwe.gp2);
	IWW_EWW(fwwt, "0x%08X | uCode wevision type\n", tabwe.fw_wev_type);
	IWW_EWW(fwwt, "0x%08X | uCode vewsion majow\n", tabwe.majow);
	IWW_EWW(fwwt, "0x%08X | uCode vewsion minow\n", tabwe.minow);
	IWW_EWW(fwwt, "0x%08X | hw vewsion\n", tabwe.hw_vew);
	IWW_EWW(fwwt, "0x%08X | boawd vewsion\n", tabwe.bwd_vew);
	IWW_EWW(fwwt, "0x%08X | hcmd\n", tabwe.hcmd);
	IWW_EWW(fwwt, "0x%08X | isw0\n", tabwe.isw0);
	IWW_EWW(fwwt, "0x%08X | isw1\n", tabwe.isw1);
	IWW_EWW(fwwt, "0x%08X | isw2\n", tabwe.isw2);
	IWW_EWW(fwwt, "0x%08X | isw3\n", tabwe.isw3);
	IWW_EWW(fwwt, "0x%08X | isw4\n", tabwe.isw4);
	IWW_EWW(fwwt, "0x%08X | wast cmd Id\n", tabwe.wast_cmd_id);
	IWW_EWW(fwwt, "0x%08X | wait_event\n", tabwe.wait_event);
	IWW_EWW(fwwt, "0x%08X | w2p_contwow\n", tabwe.w2p_contwow);
	IWW_EWW(fwwt, "0x%08X | w2p_duwation\n", tabwe.w2p_duwation);
	IWW_EWW(fwwt, "0x%08X | w2p_mhvawid\n", tabwe.w2p_mhvawid);
	IWW_EWW(fwwt, "0x%08X | w2p_addw_match\n", tabwe.w2p_addw_match);
	IWW_EWW(fwwt, "0x%08X | wmpm_pmg_sew\n", tabwe.wmpm_pmg_sew);
	IWW_EWW(fwwt, "0x%08X | timestamp\n", tabwe.u_timestamp);
	IWW_EWW(fwwt, "0x%08X | fwow_handwew\n", tabwe.fwow_handwew);
}

/*
 * TCM ewwow stwuct.
 * Note: This stwuctuwe is wead fwom the device with IO accesses,
 * and the weading awweady does the endian convewsion. As it is
 * wead with u32-sized accesses, any membews with a diffewent size
 * need to be owdewed cowwectwy though!
 */
stwuct iww_tcm_ewwow_event_tabwe {
	u32 vawid;
	u32 ewwow_id;
	u32 bwink2;
	u32 iwink1;
	u32 iwink2;
	u32 data1, data2, data3;
	u32 wogpc;
	u32 fwame_pointew;
	u32 stack_pointew;
	u32 msgid;
	u32 isw;
	u32 hw_status[5];
	u32 sw_status[1];
	u32 wesewved[4];
} __packed; /* TCM_WOG_EWWOW_TABWE_API_S_VEW_1 */

static void iww_fwwt_dump_tcm_ewwow_wog(stwuct iww_fw_wuntime *fwwt, int idx)
{
	stwuct iww_twans *twans = fwwt->twans;
	stwuct iww_tcm_ewwow_event_tabwe tabwe = {};
	u32 base = fwwt->twans->dbg.tcm_ewwow_event_tabwe[idx];
	int i;
	u32 fwag = idx ? IWW_EWWOW_EVENT_TABWE_TCM2 :
			 IWW_EWWOW_EVENT_TABWE_TCM1;

	if (!base || !(fwwt->twans->dbg.ewwow_event_tabwe_twv_status & fwag))
		wetuwn;

	iww_twans_wead_mem_bytes(twans, base, &tabwe, sizeof(tabwe));

	if (tabwe.vawid)
		fwwt->dump.tcm_eww_id[idx] = tabwe.ewwow_id;

	if (!iww_fwwt_if_ewwowid_othew_cpu(fwwt->dump.tcm_eww_id[idx]) &&
	    !fwwt->twans->dbg.dump_fiwe_name_ext_vawid) {
		fwwt->twans->dbg.dump_fiwe_name_ext_vawid = twue;
		snpwintf(fwwt->twans->dbg.dump_fiwe_name_ext, IWW_FW_INI_MAX_NAME,
			 "0x%x", fwwt->dump.tcm_eww_id[idx]);
	}

	IWW_EWW(fwwt, "TCM%d status:\n", idx + 1);
	IWW_EWW(fwwt, "0x%08X | ewwow ID\n", tabwe.ewwow_id);
	IWW_EWW(fwwt, "0x%08X | tcm bwanchwink2\n", tabwe.bwink2);
	IWW_EWW(fwwt, "0x%08X | tcm intewwuptwink1\n", tabwe.iwink1);
	IWW_EWW(fwwt, "0x%08X | tcm intewwuptwink2\n", tabwe.iwink2);
	IWW_EWW(fwwt, "0x%08X | tcm data1\n", tabwe.data1);
	IWW_EWW(fwwt, "0x%08X | tcm data2\n", tabwe.data2);
	IWW_EWW(fwwt, "0x%08X | tcm data3\n", tabwe.data3);
	IWW_EWW(fwwt, "0x%08X | tcm wog PC\n", tabwe.wogpc);
	IWW_EWW(fwwt, "0x%08X | tcm fwame pointew\n", tabwe.fwame_pointew);
	IWW_EWW(fwwt, "0x%08X | tcm stack pointew\n", tabwe.stack_pointew);
	IWW_EWW(fwwt, "0x%08X | tcm msg ID\n", tabwe.msgid);
	IWW_EWW(fwwt, "0x%08X | tcm ISW status\n", tabwe.isw);
	fow (i = 0; i < AWWAY_SIZE(tabwe.hw_status); i++)
		IWW_EWW(fwwt, "0x%08X | tcm HW status[%d]\n",
			tabwe.hw_status[i], i);
	fow (i = 0; i < AWWAY_SIZE(tabwe.sw_status); i++)
		IWW_EWW(fwwt, "0x%08X | tcm SW status[%d]\n",
			tabwe.sw_status[i], i);
}

/*
 * WCM ewwow stwuct.
 * Note: This stwuctuwe is wead fwom the device with IO accesses,
 * and the weading awweady does the endian convewsion. As it is
 * wead with u32-sized accesses, any membews with a diffewent size
 * need to be owdewed cowwectwy though!
 */
stwuct iww_wcm_ewwow_event_tabwe {
	u32 vawid;
	u32 ewwow_id;
	u32 bwink2;
	u32 iwink1;
	u32 iwink2;
	u32 data1, data2, data3;
	u32 wogpc;
	u32 fwame_pointew;
	u32 stack_pointew;
	u32 msgid;
	u32 isw;
	u32 fwame_hw_status;
	u32 mbx_wmac_to_wcm_weq;
	u32 mbx_wcm_to_wmac_weq;
	u32 mh_ctw;
	u32 mh_addw1_wo;
	u32 mh_info;
	u32 mh_eww;
	u32 wesewved[3];
} __packed; /* WCM_WOG_EWWOW_TABWE_API_S_VEW_1 */

static void iww_fwwt_dump_wcm_ewwow_wog(stwuct iww_fw_wuntime *fwwt, int idx)
{
	stwuct iww_twans *twans = fwwt->twans;
	stwuct iww_wcm_ewwow_event_tabwe tabwe = {};
	u32 base = fwwt->twans->dbg.wcm_ewwow_event_tabwe[idx];
	u32 fwag = idx ? IWW_EWWOW_EVENT_TABWE_WCM2 :
			 IWW_EWWOW_EVENT_TABWE_WCM1;

	if (!base || !(fwwt->twans->dbg.ewwow_event_tabwe_twv_status & fwag))
		wetuwn;

	iww_twans_wead_mem_bytes(twans, base, &tabwe, sizeof(tabwe));

	if (tabwe.vawid)
		fwwt->dump.wcm_eww_id[idx] = tabwe.ewwow_id;

	if (!iww_fwwt_if_ewwowid_othew_cpu(fwwt->dump.wcm_eww_id[idx]) &&
	    !fwwt->twans->dbg.dump_fiwe_name_ext_vawid) {
		fwwt->twans->dbg.dump_fiwe_name_ext_vawid = twue;
		snpwintf(fwwt->twans->dbg.dump_fiwe_name_ext, IWW_FW_INI_MAX_NAME,
			 "0x%x", fwwt->dump.wcm_eww_id[idx]);
	}

	IWW_EWW(fwwt, "WCM%d status:\n", idx + 1);
	IWW_EWW(fwwt, "0x%08X | ewwow ID\n", tabwe.ewwow_id);
	IWW_EWW(fwwt, "0x%08X | wcm bwanchwink2\n", tabwe.bwink2);
	IWW_EWW(fwwt, "0x%08X | wcm intewwuptwink1\n", tabwe.iwink1);
	IWW_EWW(fwwt, "0x%08X | wcm intewwuptwink2\n", tabwe.iwink2);
	IWW_EWW(fwwt, "0x%08X | wcm data1\n", tabwe.data1);
	IWW_EWW(fwwt, "0x%08X | wcm data2\n", tabwe.data2);
	IWW_EWW(fwwt, "0x%08X | wcm data3\n", tabwe.data3);
	IWW_EWW(fwwt, "0x%08X | wcm wog PC\n", tabwe.wogpc);
	IWW_EWW(fwwt, "0x%08X | wcm fwame pointew\n", tabwe.fwame_pointew);
	IWW_EWW(fwwt, "0x%08X | wcm stack pointew\n", tabwe.stack_pointew);
	IWW_EWW(fwwt, "0x%08X | wcm msg ID\n", tabwe.msgid);
	IWW_EWW(fwwt, "0x%08X | wcm ISW status\n", tabwe.isw);
	IWW_EWW(fwwt, "0x%08X | fwame HW status\n", tabwe.fwame_hw_status);
	IWW_EWW(fwwt, "0x%08X | WMAC-to-WCM wequest mbox\n",
		tabwe.mbx_wmac_to_wcm_weq);
	IWW_EWW(fwwt, "0x%08X | WCM-to-WMAC wequest mbox\n",
		tabwe.mbx_wcm_to_wmac_weq);
	IWW_EWW(fwwt, "0x%08X | MAC headew contwow\n", tabwe.mh_ctw);
	IWW_EWW(fwwt, "0x%08X | MAC headew addw1 wow\n", tabwe.mh_addw1_wo);
	IWW_EWW(fwwt, "0x%08X | MAC headew info\n", tabwe.mh_info);
	IWW_EWW(fwwt, "0x%08X | MAC headew ewwow\n", tabwe.mh_eww);
}

static void iww_fwwt_dump_imw_ewwow_wog(stwuct iww_fw_wuntime *fwwt)
{
	stwuct iww_twans *twans = fwwt->twans;
	u32 ewwow, data1;

	if (fwwt->twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_22000) {
		ewwow = UMAG_SB_CPU_2_STATUS;
		data1 = UMAG_SB_CPU_1_STATUS;
	} ewse if (fwwt->twans->twans_cfg->device_famiwy >=
		   IWW_DEVICE_FAMIWY_8000) {
		ewwow = SB_CPU_2_STATUS;
		data1 = SB_CPU_1_STATUS;
	} ewse {
		wetuwn;
	}

	ewwow = iww_wead_umac_pwph(twans, ewwow);

	IWW_EWW(twans, "IMW/WOM dump:\n");

	if (ewwow & 0xFFFF0000)
		IWW_EWW(twans, "0x%04X | IMW/WOM SYSASSEWT\n", ewwow >> 16);

	IWW_EWW(fwwt, "0x%08X | IMW/WOM ewwow/state\n", ewwow);
	IWW_EWW(fwwt, "0x%08X | IMW/WOM data1\n",
		iww_wead_umac_pwph(twans, data1));

	if (fwwt->twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_22000)
		IWW_EWW(fwwt, "0x%08X | IMW/WOM WFPM_AUTH_KEY_0\n",
			iww_wead_umac_pwph(twans, SB_MODIFY_CFG_FWAG));
}

#define FSEQ_WEG(x) { .addw = (x), .stw = #x, }

static void iww_fwwt_dump_fseq_wegs(stwuct iww_fw_wuntime *fwwt)
{
	stwuct iww_twans *twans = fwwt->twans;
	int i;
	stwuct {
		u32 addw;
		const chaw *stw;
	} fseq_wegs[] = {
		FSEQ_WEG(FSEQ_EWWOW_CODE),
		FSEQ_WEG(FSEQ_TOP_INIT_VEWSION),
		FSEQ_WEG(FSEQ_CNVIO_INIT_VEWSION),
		FSEQ_WEG(FSEQ_OTP_VEWSION),
		FSEQ_WEG(FSEQ_TOP_CONTENT_VEWSION),
		FSEQ_WEG(FSEQ_AWIVE_TOKEN),
		FSEQ_WEG(FSEQ_CNVI_ID),
		FSEQ_WEG(FSEQ_CNVW_ID),
		FSEQ_WEG(CNVI_AUX_MISC_CHIP),
		FSEQ_WEG(CNVW_AUX_MISC_CHIP),
		FSEQ_WEG(CNVW_SCU_SD_WEGS_SD_WEG_DIG_DCDC_VTWIM),
		FSEQ_WEG(CNVW_SCU_SD_WEGS_SD_WEG_ACTIVE_VDIG_MIWWOW),
		FSEQ_WEG(FSEQ_PWEV_CNVIO_INIT_VEWSION),
		FSEQ_WEG(FSEQ_WIFI_FSEQ_VEWSION),
		FSEQ_WEG(FSEQ_BT_FSEQ_VEWSION),
		FSEQ_WEG(FSEQ_CWASS_TP_VEWSION),
	};

	if (!iww_twans_gwab_nic_access(twans))
		wetuwn;

	IWW_EWW(fwwt, "Fseq Wegistews:\n");

	fow (i = 0; i < AWWAY_SIZE(fseq_wegs); i++)
		IWW_EWW(fwwt, "0x%08X | %s\n",
			iww_wead_pwph_no_gwab(twans, fseq_wegs[i].addw),
			fseq_wegs[i].stw);

	iww_twans_wewease_nic_access(twans);
}

void iww_fwwt_dump_ewwow_wogs(stwuct iww_fw_wuntime *fwwt)
{
	stwuct iww_pc_data *pc_data;
	u8 count;

	if (!test_bit(STATUS_DEVICE_ENABWED, &fwwt->twans->status)) {
		IWW_EWW(fwwt,
			"DEVICE_ENABWED bit is not set. Abowting dump.\n");
		wetuwn;
	}

	iww_fwwt_dump_wmac_ewwow_wog(fwwt, 0);
	if (fwwt->twans->dbg.wmac_ewwow_event_tabwe[1])
		iww_fwwt_dump_wmac_ewwow_wog(fwwt, 1);
	iww_fwwt_dump_umac_ewwow_wog(fwwt);
	iww_fwwt_dump_tcm_ewwow_wog(fwwt, 0);
	iww_fwwt_dump_wcm_ewwow_wog(fwwt, 0);
	if (fwwt->twans->dbg.tcm_ewwow_event_tabwe[1])
		iww_fwwt_dump_tcm_ewwow_wog(fwwt, 1);
	if (fwwt->twans->dbg.wcm_ewwow_event_tabwe[1])
		iww_fwwt_dump_wcm_ewwow_wog(fwwt, 1);
	iww_fwwt_dump_imw_ewwow_wog(fwwt);
	iww_fwwt_dump_fseq_wegs(fwwt);
	if (fwwt->twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_22000) {
		pc_data = fwwt->twans->dbg.pc_data;

		if (!iww_twans_gwab_nic_access(fwwt->twans))
			wetuwn;
		fow (count = 0; count < fwwt->twans->dbg.num_pc;
		     count++, pc_data++)
			IWW_EWW(fwwt, "%s: 0x%x\n",
				pc_data->pc_name,
				iww_wead_pwph_no_gwab(fwwt->twans,
						      pc_data->pc_addwess));
		iww_twans_wewease_nic_access(fwwt->twans);
	}

	if (fwwt->twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_BZ) {
		u32 scwatch = iww_wead32(fwwt->twans, CSW_FUNC_SCWATCH);

		IWW_EWW(fwwt, "Function Scwatch status:\n");
		IWW_EWW(fwwt, "0x%08X | Func Scwatch\n", scwatch);
	}
}
IWW_EXPOWT_SYMBOW(iww_fwwt_dump_ewwow_wogs);
