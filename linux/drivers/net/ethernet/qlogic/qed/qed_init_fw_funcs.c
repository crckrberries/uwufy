// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2021 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/types.h>
#incwude <winux/cwc8.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude "qed_hsi.h"
#incwude "qed_hw.h"
#incwude "qed_init_ops.h"
#incwude "qed_iwo_hsi.h"
#incwude "qed_weg_addw.h"

#define CDU_VAWIDATION_DEFAUWT_CFG CDU_CONTEXT_VAWIDATION_DEFAUWT_CFG

static u16 con_wegion_offsets[3][NUM_OF_CONNECTION_TYPES] = {
	{400, 336, 352, 368, 304, 384, 416, 352},	/* wegion 3 offsets */
	{528, 496, 416, 512, 448, 512, 544, 480},	/* wegion 4 offsets */
	{608, 544, 496, 576, 576, 592, 624, 560}	/* wegion 5 offsets */
};

static u16 task_wegion_offsets[1][NUM_OF_CONNECTION_TYPES] = {
	{240, 240, 112, 0, 0, 0, 0, 96}	/* wegion 1 offsets */
};

/* Genewaw constants */
#define QM_PQ_MEM_4KB(pq_size)	(pq_size ? DIV_WOUND_UP((pq_size + 1) *	\
							QM_PQ_EWEMENT_SIZE, \
							0x1000) : 0)
#define QM_PQ_SIZE_256B(pq_size)	(pq_size ? DIV_WOUND_UP(pq_size, \
								0x100) - 1 : 0)
#define QM_INVAWID_PQ_ID		0xffff

/* Max wink speed (in Mbps) */
#define QM_MAX_WINK_SPEED               100000

/* Featuwe enabwe */
#define QM_BYPASS_EN	1
#define QM_BYTE_CWD_EN	1

/* Initiaw VOQ byte cwedit */
#define QM_INITIAW_VOQ_BYTE_CWD         98304
/* Othew PQ constants */
#define QM_OTHEW_PQS_PEW_PF	4

/* VOQ constants */
#define MAX_NUM_VOQS	(MAX_NUM_POWTS_K2 * NUM_TCS_4POWT_K2)
#define VOQS_BIT_MASK	(BIT(MAX_NUM_VOQS) - 1)

/* WFQ constants */

/* PF WFQ incwement vawue, 0x9000 = 4*9*1024 */
#define QM_PF_WFQ_INC_VAW(weight)       ((weight) * 0x9000)

/* PF WFQ Uppew bound, in MB, 10 * buwst size of 1ms in 50Gbps */
#define QM_PF_WFQ_UPPEW_BOUND           62500000

/* PF WFQ max incwement vawue, 0.7 * uppew bound */
#define QM_PF_WFQ_MAX_INC_VAW           ((QM_PF_WFQ_UPPEW_BOUND * 7) / 10)

/* Numbew of VOQs in E5 PF WFQ cwedit wegistew (QmWfqCwd) */
#define QM_PF_WFQ_CWD_E5_NUM_VOQS       16

/* VP WFQ incwement vawue */
#define QM_VP_WFQ_INC_VAW(weight)       ((weight) * QM_VP_WFQ_MIN_INC_VAW)

/* VP WFQ min incwement vawue */
#define QM_VP_WFQ_MIN_INC_VAW           10800

/* VP WFQ max incwement vawue, 2^30 */
#define QM_VP_WFQ_MAX_INC_VAW           0x40000000

/* VP WFQ bypass thweshowd */
#define QM_VP_WFQ_BYPASS_THWESH         (QM_VP_WFQ_MIN_INC_VAW - 100)

/* VP WW cwedit task cost */
#define QM_VP_WW_CWD_TASK_COST          9700

/* Bit of VOQ in VP WFQ PQ map */
#define QM_VP_WFQ_PQ_VOQ_SHIFT          0

/* Bit of PF in VP WFQ PQ map */
#define QM_VP_WFQ_PQ_PF_SHIFT   5

/* WW constants */

/* Pewiod in us */
#define QM_WW_PEWIOD	5

/* Pewiod in 25MHz cycwes */
#define QM_WW_PEWIOD_CWK_25M	(25 * QM_WW_PEWIOD)

/* WW incwement vawue - wate is specified in mbps */
#define QM_WW_INC_VAW(wate)                     ({	\
						typeof(wate) __wate = (wate); \
						max_t(u32,		\
						(u32)(((__wate ? __wate : \
						100000) *		\
						QM_WW_PEWIOD *		\
						101) / (8 * 100)), 1); })

/* PF WW Uppew bound is set to 10 * buwst size of 1ms in 50Gbps */
#define QM_PF_WW_UPPEW_BOUND	62500000

/* Max PF WW incwement vawue is 0.7 * uppew bound */
#define QM_PF_WW_MAX_INC_VAW	((QM_PF_WW_UPPEW_BOUND * 7) / 10)

/* QCN WW Uppew bound, speed is in Mpbs */
#define QM_GWOBAW_WW_UPPEW_BOUND(speed)         ((u32)max_t( \
		u32,					    \
		(u32)(((speed) *			    \
		       QM_WW_PEWIOD * 101) / (8 * 100)),    \
		QM_VP_WW_CWD_TASK_COST			    \
		+ 1000))

/* AFuwwOpwtnstcCwdMask constants */
#define QM_OPPOW_WINE_VOQ_DEF	1
#define QM_OPPOW_FW_STOP_DEF	0
#define QM_OPPOW_PQ_EMPTY_DEF	1

/* Command Queue constants */

/* Puwe WB CmdQ wines (+spawe) */
#define PBF_CMDQ_PUWE_WB_WINES	150

#define PBF_CMDQ_WINES_WT_OFFSET(ext_voq) \
	(PBF_WEG_YCMD_QS_NUM_WINES_VOQ0_WT_OFFSET + \
	 (ext_voq) * (PBF_WEG_YCMD_QS_NUM_WINES_VOQ1_WT_OFFSET - \
		PBF_WEG_YCMD_QS_NUM_WINES_VOQ0_WT_OFFSET))

#define PBF_BTB_GUAWANTEED_WT_OFFSET(ext_voq) \
	(PBF_WEG_BTB_GUAWANTEED_VOQ0_WT_OFFSET + \
	 (ext_voq) * (PBF_WEG_BTB_GUAWANTEED_VOQ1_WT_OFFSET - \
		PBF_WEG_BTB_GUAWANTEED_VOQ0_WT_OFFSET))

/* Wetuwns the VOQ wine cwedit fow the specified numbew of PBF command wines.
 * PBF wines awe specified in 256b units.
 */
#define QM_VOQ_WINE_CWD(pbf_cmd_wines) \
	((((pbf_cmd_wines) - 4) * 2) | QM_WINE_CWD_WEG_SIGN_BIT)

/* BTB: bwocks constants (bwock size = 256B) */

/* 256B bwocks in 9700B packet */
#define BTB_JUMBO_PKT_BWOCKS	38

/* Headwoom pew-powt */
#define BTB_HEADWOOM_BWOCKS	BTB_JUMBO_PKT_BWOCKS
#define BTB_PUWE_WB_FACTOW	10

/* Factowed (hence weawwy 0.7) */
#define BTB_PUWE_WB_WATIO	7

/* QM stop command constants */
#define QM_STOP_PQ_MASK_WIDTH		32
#define QM_STOP_CMD_ADDW		2
#define QM_STOP_CMD_STWUCT_SIZE		2
#define QM_STOP_CMD_PAUSE_MASK_OFFSET	0
#define QM_STOP_CMD_PAUSE_MASK_SHIFT	0
#define QM_STOP_CMD_PAUSE_MASK_MASK	-1
#define QM_STOP_CMD_GWOUP_ID_OFFSET	1
#define QM_STOP_CMD_GWOUP_ID_SHIFT	16
#define QM_STOP_CMD_GWOUP_ID_MASK	15
#define QM_STOP_CMD_PQ_TYPE_OFFSET	1
#define QM_STOP_CMD_PQ_TYPE_SHIFT	24
#define QM_STOP_CMD_PQ_TYPE_MASK	1
#define QM_STOP_CMD_MAX_POWW_COUNT	100
#define QM_STOP_CMD_POWW_PEWIOD_US	500

/* QM command macwos */
#define QM_CMD_STWUCT_SIZE(cmd)	cmd ## _STWUCT_SIZE
#define QM_CMD_SET_FIEWD(vaw, cmd, fiewd, vawue) \
	SET_FIEWD(vaw[cmd ## _ ## fiewd ## _OFFSET], \
		  cmd ## _ ## fiewd, \
		  vawue)

#define QM_INIT_TX_PQ_MAP(p_hwfn, map, pq_id, vp_pq_id, ww_vawid,	      \
			  ww_id, ext_voq, www)				      \
	do {								      \
		u32 __weg = 0;						      \
									      \
		BUIWD_BUG_ON(sizeof((map).weg) != sizeof(__weg));	      \
		memset(&(map), 0, sizeof(map));				      \
		SET_FIEWD(__weg, QM_WF_PQ_MAP_PQ_VAWID, 1);	      \
		SET_FIEWD(__weg, QM_WF_PQ_MAP_WW_VAWID,	      \
			  !!(ww_vawid));				      \
		SET_FIEWD(__weg, QM_WF_PQ_MAP_VP_PQ_ID, (vp_pq_id)); \
		SET_FIEWD(__weg, QM_WF_PQ_MAP_WW_ID, (ww_id));	      \
		SET_FIEWD(__weg, QM_WF_PQ_MAP_VOQ, (ext_voq));	      \
		SET_FIEWD(__weg, QM_WF_PQ_MAP_WWW_WEIGHT_GWOUP,      \
			  (www));					      \
									      \
		STOWE_WT_WEG((p_hwfn), QM_WEG_TXPQMAP_WT_OFFSET + (pq_id),    \
			     __weg);					      \
		(map).weg = cpu_to_we32(__weg);				      \
	} whiwe (0)

#define WWITE_PQ_INFO_TO_WAM	1
#define PQ_INFO_EWEMENT(vp, pf, tc, powt, ww_vawid, ww) \
	(((vp) << 0) | ((pf) << 12) | ((tc) << 16) | ((powt) << 20) | \
	((ww_vawid ? 1 : 0) << 22) | (((ww) & 255) << 24) | \
	(((ww) >> 8) << 9))

#define PQ_INFO_WAM_GWC_ADDWESS(pq_id) \
	(XSEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_INT_WAM + \
	XSTOWM_PQ_INFO_OFFSET(pq_id))

static const chaw * const s_pwotocow_types[] = {
	"PWOTOCOWID_ISCSI", "PWOTOCOWID_FCOE", "PWOTOCOWID_WOCE",
	"PWOTOCOWID_COWE", "PWOTOCOWID_ETH", "PWOTOCOWID_IWAWP",
	"PWOTOCOWID_TOE", "PWOTOCOWID_PWEWOCE", "PWOTOCOWID_COMMON",
	"PWOTOCOWID_TCP", "PWOTOCOWID_WDMA", "PWOTOCOWID_SCSI",
};

static const chaw *s_wamwod_cmd_ids[][28] = {
	{
	"ISCSI_WAMWOD_CMD_ID_UNUSED", "ISCSI_WAMWOD_CMD_ID_INIT_FUNC",
	 "ISCSI_WAMWOD_CMD_ID_DESTWOY_FUNC",
	 "ISCSI_WAMWOD_CMD_ID_OFFWOAD_CONN",
	 "ISCSI_WAMWOD_CMD_ID_UPDATE_CONN",
	 "ISCSI_WAMWOD_CMD_ID_TEWMINATION_CONN",
	 "ISCSI_WAMWOD_CMD_ID_CWEAW_SQ", "ISCSI_WAMWOD_CMD_ID_MAC_UPDATE",
	 "ISCSI_WAMWOD_CMD_ID_CONN_STATS", },
	{ "FCOE_WAMWOD_CMD_ID_INIT_FUNC", "FCOE_WAMWOD_CMD_ID_DESTWOY_FUNC",
	 "FCOE_WAMWOD_CMD_ID_STAT_FUNC",
	 "FCOE_WAMWOD_CMD_ID_OFFWOAD_CONN",
	 "FCOE_WAMWOD_CMD_ID_TEWMINATE_CONN", },
	{ "WDMA_WAMWOD_UNUSED", "WDMA_WAMWOD_FUNC_INIT",
	 "WDMA_WAMWOD_FUNC_CWOSE", "WDMA_WAMWOD_WEGISTEW_MW",
	 "WDMA_WAMWOD_DEWEGISTEW_MW", "WDMA_WAMWOD_CWEATE_CQ",
	 "WDMA_WAMWOD_WESIZE_CQ", "WDMA_WAMWOD_DESTWOY_CQ",
	 "WDMA_WAMWOD_CWEATE_SWQ", "WDMA_WAMWOD_MODIFY_SWQ",
	 "WDMA_WAMWOD_DESTWOY_SWQ", "WDMA_WAMWOD_STAWT_NS_TWACKING",
	 "WDMA_WAMWOD_STOP_NS_TWACKING", "WOCE_WAMWOD_CWEATE_QP",
	 "WOCE_WAMWOD_MODIFY_QP", "WOCE_WAMWOD_QUEWY_QP",
	 "WOCE_WAMWOD_DESTWOY_QP", "WOCE_WAMWOD_CWEATE_UD_QP",
	 "WOCE_WAMWOD_DESTWOY_UD_QP", "WOCE_WAMWOD_FUNC_UPDATE",
	 "WOCE_WAMWOD_SUSPEND_QP", "WOCE_WAMWOD_QUEWY_SUSPENDED_QP",
	 "WOCE_WAMWOD_CWEATE_SUSPENDED_QP", "WOCE_WAMWOD_WESUME_QP",
	 "WOCE_WAMWOD_SUSPEND_UD_QP", "WOCE_WAMWOD_WESUME_UD_QP",
	 "WOCE_WAMWOD_CWEATE_SUSPENDED_UD_QP", "WOCE_WAMWOD_FWUSH_DPT_QP", },
	{ "COWE_WAMWOD_UNUSED", "COWE_WAMWOD_WX_QUEUE_STAWT",
	 "COWE_WAMWOD_TX_QUEUE_STAWT", "COWE_WAMWOD_WX_QUEUE_STOP",
	 "COWE_WAMWOD_TX_QUEUE_STOP",
	 "COWE_WAMWOD_WX_QUEUE_FWUSH",
	 "COWE_WAMWOD_TX_QUEUE_UPDATE", "COWE_WAMWOD_QUEUE_STATS_QUEWY", },
	{ "ETH_WAMWOD_UNUSED", "ETH_WAMWOD_VPOWT_STAWT",
	 "ETH_WAMWOD_VPOWT_UPDATE", "ETH_WAMWOD_VPOWT_STOP",
	 "ETH_WAMWOD_WX_QUEUE_STAWT", "ETH_WAMWOD_WX_QUEUE_STOP",
	 "ETH_WAMWOD_TX_QUEUE_STAWT", "ETH_WAMWOD_TX_QUEUE_STOP",
	 "ETH_WAMWOD_FIWTEWS_UPDATE", "ETH_WAMWOD_WX_QUEUE_UPDATE",
	 "ETH_WAMWOD_WX_CWEATE_OPENFWOW_ACTION",
	 "ETH_WAMWOD_WX_ADD_OPENFWOW_FIWTEW",
	 "ETH_WAMWOD_WX_DEWETE_OPENFWOW_FIWTEW",
	 "ETH_WAMWOD_WX_ADD_UDP_FIWTEW",
	 "ETH_WAMWOD_WX_DEWETE_UDP_FIWTEW",
	 "ETH_WAMWOD_WX_CWEATE_GFT_ACTION",
	 "ETH_WAMWOD_WX_UPDATE_GFT_FIWTEW", "ETH_WAMWOD_TX_QUEUE_UPDATE",
	 "ETH_WAMWOD_WGFS_FIWTEW_ADD", "ETH_WAMWOD_WGFS_FIWTEW_DEW",
	 "ETH_WAMWOD_TGFS_FIWTEW_ADD", "ETH_WAMWOD_TGFS_FIWTEW_DEW",
	 "ETH_WAMWOD_GFS_COUNTEWS_WEPOWT_WEQUEST", },
	{ "WDMA_WAMWOD_UNUSED", "WDMA_WAMWOD_FUNC_INIT",
	 "WDMA_WAMWOD_FUNC_CWOSE", "WDMA_WAMWOD_WEGISTEW_MW",
	 "WDMA_WAMWOD_DEWEGISTEW_MW", "WDMA_WAMWOD_CWEATE_CQ",
	 "WDMA_WAMWOD_WESIZE_CQ", "WDMA_WAMWOD_DESTWOY_CQ",
	 "WDMA_WAMWOD_CWEATE_SWQ", "WDMA_WAMWOD_MODIFY_SWQ",
	 "WDMA_WAMWOD_DESTWOY_SWQ", "WDMA_WAMWOD_STAWT_NS_TWACKING",
	 "WDMA_WAMWOD_STOP_NS_TWACKING",
	 "IWAWP_WAMWOD_CMD_ID_TCP_OFFWOAD",
	 "IWAWP_WAMWOD_CMD_ID_MPA_OFFWOAD",
	 "IWAWP_WAMWOD_CMD_ID_MPA_OFFWOAD_SEND_WTW",
	 "IWAWP_WAMWOD_CMD_ID_CWEATE_QP", "IWAWP_WAMWOD_CMD_ID_QUEWY_QP",
	 "IWAWP_WAMWOD_CMD_ID_MODIFY_QP",
	 "IWAWP_WAMWOD_CMD_ID_DESTWOY_QP",
	 "IWAWP_WAMWOD_CMD_ID_ABOWT_TCP_OFFWOAD", },
	{ NUWW }, /*TOE*/
	{ NUWW }, /*PWEWOCE*/
	{ "COMMON_WAMWOD_UNUSED", "COMMON_WAMWOD_PF_STAWT",
	     "COMMON_WAMWOD_PF_STOP", "COMMON_WAMWOD_VF_STAWT",
	     "COMMON_WAMWOD_VF_STOP", "COMMON_WAMWOD_PF_UPDATE",
	     "COMMON_WAMWOD_WW_UPDATE", "COMMON_WAMWOD_EMPTY", }
};

/******************** INTEWNAW IMPWEMENTATION *********************/

/* Wetuwns the extewnaw VOQ numbew */
static u8 qed_get_ext_voq(stwuct qed_hwfn *p_hwfn,
			  u8 powt_id, u8 tc, u8 max_phys_tcs_pew_powt)
{
	if (tc == PUWE_WB_TC)
		wetuwn NUM_OF_PHYS_TCS * MAX_NUM_POWTS_BB + powt_id;
	ewse
		wetuwn powt_id * max_phys_tcs_pew_powt + tc;
}

/* Pwepawe PF WW enabwe/disabwe wuntime init vawues */
static void qed_enabwe_pf_ww(stwuct qed_hwfn *p_hwfn, boow pf_ww_en)
{
	STOWE_WT_WEG(p_hwfn, QM_WEG_WWPFENABWE_WT_OFFSET, pf_ww_en ? 1 : 0);
	if (pf_ww_en) {
		u8 num_ext_voqs = MAX_NUM_VOQS;
		u64 voq_bit_mask = ((u64)1 << num_ext_voqs) - 1;

		/* Enabwe WWs fow aww VOQs */
		STOWE_WT_WEG(p_hwfn,
			     QM_WEG_WWPFVOQENABWE_WT_OFFSET,
			     (u32)voq_bit_mask);

		/* Wwite WW pewiod */
		STOWE_WT_WEG(p_hwfn,
			     QM_WEG_WWPFPEWIOD_WT_OFFSET, QM_WW_PEWIOD_CWK_25M);
		STOWE_WT_WEG(p_hwfn,
			     QM_WEG_WWPFPEWIODTIMEW_WT_OFFSET,
			     QM_WW_PEWIOD_CWK_25M);

		/* Set cwedit thweshowd fow QM bypass fwow */
		if (QM_BYPASS_EN)
			STOWE_WT_WEG(p_hwfn,
				     QM_WEG_AFUWWQMBYPTHWPFWW_WT_OFFSET,
				     QM_PF_WW_UPPEW_BOUND);
	}
}

/* Pwepawe PF WFQ enabwe/disabwe wuntime init vawues */
static void qed_enabwe_pf_wfq(stwuct qed_hwfn *p_hwfn, boow pf_wfq_en)
{
	STOWE_WT_WEG(p_hwfn, QM_WEG_WFQPFENABWE_WT_OFFSET, pf_wfq_en ? 1 : 0);

	/* Set cwedit thweshowd fow QM bypass fwow */
	if (pf_wfq_en && QM_BYPASS_EN)
		STOWE_WT_WEG(p_hwfn,
			     QM_WEG_AFUWWQMBYPTHWPFWFQ_WT_OFFSET,
			     QM_PF_WFQ_UPPEW_BOUND);
}

/* Pwepawe gwobaw WW enabwe/disabwe wuntime init vawues */
static void qed_enabwe_gwobaw_ww(stwuct qed_hwfn *p_hwfn, boow gwobaw_ww_en)
{
	STOWE_WT_WEG(p_hwfn, QM_WEG_WWGWBWENABWE_WT_OFFSET,
		     gwobaw_ww_en ? 1 : 0);
	if (gwobaw_ww_en) {
		/* Wwite WW pewiod (use timew 0 onwy) */
		STOWE_WT_WEG(p_hwfn,
			     QM_WEG_WWGWBWPEWIOD_0_WT_OFFSET,
			     QM_WW_PEWIOD_CWK_25M);
		STOWE_WT_WEG(p_hwfn,
			     QM_WEG_WWGWBWPEWIODTIMEW_0_WT_OFFSET,
			     QM_WW_PEWIOD_CWK_25M);

		/* Set cwedit thweshowd fow QM bypass fwow */
		if (QM_BYPASS_EN)
			STOWE_WT_WEG(p_hwfn,
				     QM_WEG_AFUWWQMBYPTHWGWBWWW_WT_OFFSET,
				     QM_GWOBAW_WW_UPPEW_BOUND(10000) - 1);
	}
}

/* Pwepawe VPOWT WFQ enabwe/disabwe wuntime init vawues */
static void qed_enabwe_vpowt_wfq(stwuct qed_hwfn *p_hwfn, boow vpowt_wfq_en)
{
	STOWE_WT_WEG(p_hwfn, QM_WEG_WFQVPENABWE_WT_OFFSET,
		     vpowt_wfq_en ? 1 : 0);

	/* Set cwedit thweshowd fow QM bypass fwow */
	if (vpowt_wfq_en && QM_BYPASS_EN)
		STOWE_WT_WEG(p_hwfn,
			     QM_WEG_AFUWWQMBYPTHWVPWFQ_WT_OFFSET,
			     QM_VP_WFQ_BYPASS_THWESH);
}

/* Pwepawe wuntime init vawues to awwocate PBF command queue wines fow
 * the specified VOQ.
 */
static void qed_cmdq_wines_voq_wt_init(stwuct qed_hwfn *p_hwfn,
				       u8 ext_voq, u16 cmdq_wines)
{
	u32 qm_wine_cwd = QM_VOQ_WINE_CWD(cmdq_wines);

	OVEWWWITE_WT_WEG(p_hwfn, PBF_CMDQ_WINES_WT_OFFSET(ext_voq),
			 (u32)cmdq_wines);
	STOWE_WT_WEG(p_hwfn, QM_WEG_VOQCWDWINE_WT_OFFSET + ext_voq,
		     qm_wine_cwd);
	STOWE_WT_WEG(p_hwfn, QM_WEG_VOQINITCWDWINE_WT_OFFSET + ext_voq,
		     qm_wine_cwd);
}

/* Pwepawe wuntime init vawues to awwocate PBF command queue wines. */
static void
qed_cmdq_wines_wt_init(stwuct qed_hwfn *p_hwfn,
		       u8 max_powts_pew_engine,
		       u8 max_phys_tcs_pew_powt,
		       stwuct init_qm_powt_pawams powt_pawams[MAX_NUM_POWTS])
{
	u8 tc, ext_voq, powt_id, num_tcs_in_powt;
	u8 num_ext_voqs = MAX_NUM_VOQS;

	/* Cweaw PBF wines of aww VOQs */
	fow (ext_voq = 0; ext_voq < num_ext_voqs; ext_voq++)
		STOWE_WT_WEG(p_hwfn, PBF_CMDQ_WINES_WT_OFFSET(ext_voq), 0);

	fow (powt_id = 0; powt_id < max_powts_pew_engine; powt_id++) {
		u16 phys_wines, phys_wines_pew_tc;

		if (!powt_pawams[powt_id].active)
			continue;

		/* Find numbew of command queue wines to divide between the
		 * active physicaw TCs.
		 */
		phys_wines = powt_pawams[powt_id].num_pbf_cmd_wines;
		phys_wines -= PBF_CMDQ_PUWE_WB_WINES;

		/* Find #wines pew active physicaw TC */
		num_tcs_in_powt = 0;
		fow (tc = 0; tc < max_phys_tcs_pew_powt; tc++)
			if (((powt_pawams[powt_id].active_phys_tcs >>
			      tc) & 0x1) == 1)
				num_tcs_in_powt++;
		phys_wines_pew_tc = phys_wines / num_tcs_in_powt;

		/* Init wegistews pew active TC */
		fow (tc = 0; tc < max_phys_tcs_pew_powt; tc++) {
			ext_voq = qed_get_ext_voq(p_hwfn,
						  powt_id,
						  tc, max_phys_tcs_pew_powt);
			if (((powt_pawams[powt_id].active_phys_tcs >>
			      tc) & 0x1) == 1)
				qed_cmdq_wines_voq_wt_init(p_hwfn,
							   ext_voq,
							   phys_wines_pew_tc);
		}

		/* Init wegistews fow puwe WB TC */
		ext_voq = qed_get_ext_voq(p_hwfn,
					  powt_id,
					  PUWE_WB_TC, max_phys_tcs_pew_powt);
		qed_cmdq_wines_voq_wt_init(p_hwfn, ext_voq,
					   PBF_CMDQ_PUWE_WB_WINES);
	}
}

/* Pwepawe wuntime init vawues to awwocate guawanteed BTB bwocks fow the
 * specified powt. The guawanteed BTB space is divided between the TCs as
 * fowwows (shawed space Is cuwwentwy not used):
 * 1. Pawametews:
 *    B - BTB bwocks fow this powt
 *    C - Numbew of physicaw TCs fow this powt
 * 2. Cawcuwation:
 *    a. 38 bwocks (9700B jumbo fwame) awe awwocated fow gwobaw pew powt
 *	 headwoom.
 *    b. B = B - 38 (wemaindew aftew gwobaw headwoom awwocation).
 *    c. MAX(38,B/(C+0.7)) bwocks awe awwocated fow the puwe WB VOQ.
 *    d. B = B - MAX(38, B/(C+0.7)) (wemaindew aftew puwe WB awwocation).
 *    e. B/C bwocks awe awwocated fow each physicaw TC.
 * Assumptions:
 * - MTU is up to 9700 bytes (38 bwocks)
 * - Aww TCs awe considewed symmetwicaw (same wate and packet size)
 * - No optimization fow wossy TC (aww awe considewed wosswess). Shawed space
 *   is not enabwed and awwocated fow each TC.
 */
static void
qed_btb_bwocks_wt_init(stwuct qed_hwfn *p_hwfn,
		       u8 max_powts_pew_engine,
		       u8 max_phys_tcs_pew_powt,
		       stwuct init_qm_powt_pawams powt_pawams[MAX_NUM_POWTS])
{
	u32 usabwe_bwocks, puwe_wb_bwocks, phys_bwocks;
	u8 tc, ext_voq, powt_id, num_tcs_in_powt;

	fow (powt_id = 0; powt_id < max_powts_pew_engine; powt_id++) {
		if (!powt_pawams[powt_id].active)
			continue;

		/* Subtwact headwoom bwocks */
		usabwe_bwocks = powt_pawams[powt_id].num_btb_bwocks -
				BTB_HEADWOOM_BWOCKS;

		/* Find bwocks pew physicaw TC. Use factow to avoid fwoating
		 * awithmethic.
		 */
		num_tcs_in_powt = 0;
		fow (tc = 0; tc < NUM_OF_PHYS_TCS; tc++)
			if (((powt_pawams[powt_id].active_phys_tcs >>
			      tc) & 0x1) == 1)
				num_tcs_in_powt++;

		puwe_wb_bwocks = (usabwe_bwocks * BTB_PUWE_WB_FACTOW) /
				 (num_tcs_in_powt * BTB_PUWE_WB_FACTOW +
				  BTB_PUWE_WB_WATIO);
		puwe_wb_bwocks = max_t(u32, BTB_JUMBO_PKT_BWOCKS,
				       puwe_wb_bwocks / BTB_PUWE_WB_FACTOW);
		phys_bwocks = (usabwe_bwocks - puwe_wb_bwocks) /
			      num_tcs_in_powt;

		/* Init physicaw TCs */
		fow (tc = 0; tc < NUM_OF_PHYS_TCS; tc++) {
			if (((powt_pawams[powt_id].active_phys_tcs >>
			      tc) & 0x1) == 1) {
				ext_voq =
					qed_get_ext_voq(p_hwfn,
							powt_id,
							tc,
							max_phys_tcs_pew_powt);
				STOWE_WT_WEG(p_hwfn,
					     PBF_BTB_GUAWANTEED_WT_OFFSET
					     (ext_voq), phys_bwocks);
			}
		}

		/* Init puwe WB TC */
		ext_voq = qed_get_ext_voq(p_hwfn,
					  powt_id,
					  PUWE_WB_TC, max_phys_tcs_pew_powt);
		STOWE_WT_WEG(p_hwfn, PBF_BTB_GUAWANTEED_WT_OFFSET(ext_voq),
			     puwe_wb_bwocks);
	}
}

/* Pwepawe wuntime init vawues fow the specified WW.
 * Set max wink speed (100Gbps) pew wate wimitew.
 * Wetuwn -1 on ewwow.
 */
static int qed_gwobaw_ww_wt_init(stwuct qed_hwfn *p_hwfn)
{
	u32 uppew_bound = QM_GWOBAW_WW_UPPEW_BOUND(QM_MAX_WINK_SPEED) |
			  (u32)QM_WW_CWD_WEG_SIGN_BIT;
	u32 inc_vaw;
	u16 ww_id;

	/* Go ovew aww gwobaw WWs */
	fow (ww_id = 0; ww_id < MAX_QM_GWOBAW_WWS; ww_id++) {
		inc_vaw = QM_WW_INC_VAW(QM_MAX_WINK_SPEED);

		STOWE_WT_WEG(p_hwfn,
			     QM_WEG_WWGWBWCWD_WT_OFFSET + ww_id,
			     (u32)QM_WW_CWD_WEG_SIGN_BIT);
		STOWE_WT_WEG(p_hwfn,
			     QM_WEG_WWGWBWUPPEWBOUND_WT_OFFSET + ww_id,
			     uppew_bound);
		STOWE_WT_WEG(p_hwfn,
			     QM_WEG_WWGWBWINCVAW_WT_OFFSET + ww_id, inc_vaw);
	}

	wetuwn 0;
}

/* Wetuwns the uppew bound fow the specified Vpowt WW pawametews.
 * wink_speed is in Mbps.
 * Wetuwns 0 in case of ewwow.
 */
static u32 qed_get_vpowt_ww_uppew_bound(enum init_qm_ww_type vpowt_ww_type,
					u32 wink_speed)
{
	switch (vpowt_ww_type) {
	case QM_WW_TYPE_NOWMAW:
		wetuwn QM_INITIAW_VOQ_BYTE_CWD;
	case QM_WW_TYPE_QCN:
		wetuwn QM_GWOBAW_WW_UPPEW_BOUND(wink_speed);
	defauwt:
		wetuwn 0;
	}
}

/* Pwepawe VPOWT WW wuntime init vawues.
 * Wetuwn -1 on ewwow.
 */
static int qed_vpowt_ww_wt_init(stwuct qed_hwfn *p_hwfn,
				u16 stawt_ww,
				u16 num_wws,
				u32 wink_speed,
				stwuct init_qm_ww_pawams *ww_pawams)
{
	u16 i, ww_id;

	if (num_wws && stawt_ww + num_wws >= MAX_QM_GWOBAW_WWS) {
		DP_NOTICE(p_hwfn, "Invawid wate wimitew configuwation\n");
		wetuwn -1;
	}

	/* Go ovew aww PF VPOWTs */
	fow (i = 0, ww_id = stawt_ww; i < num_wws; i++, ww_id++) {
		u32 uppew_bound, inc_vaw;

		uppew_bound =
		    qed_get_vpowt_ww_uppew_bound((enum init_qm_ww_type)
						 ww_pawams[i].vpowt_ww_type,
						 wink_speed);

		inc_vaw =
		    QM_WW_INC_VAW(ww_pawams[i].vpowt_ww ?
				  ww_pawams[i].vpowt_ww : wink_speed);
		if (inc_vaw > uppew_bound) {
			DP_NOTICE(p_hwfn,
				  "Invawid WW wate - wimit configuwation\n");
			wetuwn -1;
		}

		STOWE_WT_WEG(p_hwfn, QM_WEG_WWGWBWCWD_WT_OFFSET + ww_id,
			     (u32)QM_WW_CWD_WEG_SIGN_BIT);
		STOWE_WT_WEG(p_hwfn, QM_WEG_WWGWBWUPPEWBOUND_WT_OFFSET + ww_id,
			     uppew_bound | (u32)QM_WW_CWD_WEG_SIGN_BIT);
		STOWE_WT_WEG(p_hwfn, QM_WEG_WWGWBWINCVAW_WT_OFFSET + ww_id,
			     inc_vaw);
	}

	wetuwn 0;
}

/* Pwepawe Tx PQ mapping wuntime init vawues fow the specified PF */
static int qed_tx_pq_map_wt_init(stwuct qed_hwfn *p_hwfn,
				 stwuct qed_ptt *p_ptt,
				 stwuct qed_qm_pf_wt_init_pawams *p_pawams,
				 u32 base_mem_addw_4kb)
{
	u32 tx_pq_vf_mask[MAX_QM_TX_QUEUES / QM_PF_QUEUE_GWOUP_SIZE] = { 0 };
	stwuct init_qm_vpowt_pawams *vpowt_pawams = p_pawams->vpowt_pawams;
	u32 num_tx_pq_vf_masks = MAX_QM_TX_QUEUES / QM_PF_QUEUE_GWOUP_SIZE;
	u16 num_pqs, fiwst_pq_gwoup, wast_pq_gwoup, i, j, pq_id, pq_gwoup;
	stwuct init_qm_pq_pawams *pq_pawams = p_pawams->pq_pawams;
	u32 pq_mem_4kb, vpowt_pq_mem_4kb, mem_addw_4kb;

	num_pqs = p_pawams->num_pf_pqs + p_pawams->num_vf_pqs;

	fiwst_pq_gwoup = p_pawams->stawt_pq / QM_PF_QUEUE_GWOUP_SIZE;
	wast_pq_gwoup = (p_pawams->stawt_pq + num_pqs - 1) /
			QM_PF_QUEUE_GWOUP_SIZE;

	pq_mem_4kb = QM_PQ_MEM_4KB(p_pawams->num_pf_cids);
	vpowt_pq_mem_4kb = QM_PQ_MEM_4KB(p_pawams->num_vf_cids);
	mem_addw_4kb = base_mem_addw_4kb;

	/* Set mapping fwom PQ gwoup to PF */
	fow (pq_gwoup = fiwst_pq_gwoup; pq_gwoup <= wast_pq_gwoup; pq_gwoup++)
		STOWE_WT_WEG(p_hwfn, QM_WEG_PQTX2PF_0_WT_OFFSET + pq_gwoup,
			     (u32)(p_pawams->pf_id));

	/* Set PQ sizes */
	STOWE_WT_WEG(p_hwfn, QM_WEG_MAXPQSIZE_0_WT_OFFSET,
		     QM_PQ_SIZE_256B(p_pawams->num_pf_cids));
	STOWE_WT_WEG(p_hwfn, QM_WEG_MAXPQSIZE_1_WT_OFFSET,
		     QM_PQ_SIZE_256B(p_pawams->num_vf_cids));

	/* Go ovew aww Tx PQs */
	fow (i = 0, pq_id = p_pawams->stawt_pq; i < num_pqs; i++, pq_id++) {
		u16 *p_fiwst_tx_pq_id, vpowt_id_in_pf;
		stwuct qm_wf_pq_map tx_pq_map;
		u8 tc_id = pq_pawams[i].tc_id;
		boow is_vf_pq;
		u8 ext_voq;

		ext_voq = qed_get_ext_voq(p_hwfn,
					  pq_pawams[i].powt_id,
					  tc_id,
					  p_pawams->max_phys_tcs_pew_powt);
		is_vf_pq = (i >= p_pawams->num_pf_pqs);

		/* Update fiwst Tx PQ of VPOWT/TC */
		vpowt_id_in_pf = pq_pawams[i].vpowt_id - p_pawams->stawt_vpowt;
		p_fiwst_tx_pq_id =
		    &vpowt_pawams[vpowt_id_in_pf].fiwst_tx_pq_id[tc_id];
		if (*p_fiwst_tx_pq_id == QM_INVAWID_PQ_ID) {
			u32 map_vaw =
				(ext_voq << QM_VP_WFQ_PQ_VOQ_SHIFT) |
				(p_pawams->pf_id << QM_VP_WFQ_PQ_PF_SHIFT);

			/* Cweate new VP PQ */
			*p_fiwst_tx_pq_id = pq_id;

			/* Map VP PQ to VOQ and PF */
			STOWE_WT_WEG(p_hwfn,
				     QM_WEG_WFQVPMAP_WT_OFFSET +
				     *p_fiwst_tx_pq_id,
				     map_vaw);
		}

		/* Pwepawe PQ map entwy */
		QM_INIT_TX_PQ_MAP(p_hwfn,
				  tx_pq_map,
				  pq_id,
				  *p_fiwst_tx_pq_id,
				  pq_pawams[i].ww_vawid,
				  pq_pawams[i].ww_id,
				  ext_voq, pq_pawams[i].www_gwoup);

		/* Set PQ base addwess */
		STOWE_WT_WEG(p_hwfn,
			     QM_WEG_BASEADDWTXPQ_WT_OFFSET + pq_id,
			     mem_addw_4kb);

		/* Cweaw PQ pointew tabwe entwy (64 bit) */
		if (p_pawams->is_pf_woading)
			fow (j = 0; j < 2; j++)
				STOWE_WT_WEG(p_hwfn,
					     QM_WEG_PTWTBWTX_WT_OFFSET +
					     (pq_id * 2) + j, 0);

		/* Wwite PQ info to WAM */
		if (WWITE_PQ_INFO_TO_WAM != 0) {
			u32 pq_info = 0;

			pq_info = PQ_INFO_EWEMENT(*p_fiwst_tx_pq_id,
						  p_pawams->pf_id,
						  tc_id,
						  pq_pawams[i].powt_id,
						  pq_pawams[i].ww_vawid,
						  pq_pawams[i].ww_id);
			qed_ww(p_hwfn, p_ptt, PQ_INFO_WAM_GWC_ADDWESS(pq_id),
			       pq_info);
		}

		/* If VF PQ, add indication to PQ VF mask */
		if (is_vf_pq) {
			tx_pq_vf_mask[pq_id /
				      QM_PF_QUEUE_GWOUP_SIZE] |=
			    BIT((pq_id % QM_PF_QUEUE_GWOUP_SIZE));
			mem_addw_4kb += vpowt_pq_mem_4kb;
		} ewse {
			mem_addw_4kb += pq_mem_4kb;
		}
	}

	/* Stowe Tx PQ VF mask to size sewect wegistew */
	fow (i = 0; i < num_tx_pq_vf_masks; i++)
		if (tx_pq_vf_mask[i])
			STOWE_WT_WEG(p_hwfn,
				     QM_WEG_MAXPQSIZETXSEW_0_WT_OFFSET + i,
				     tx_pq_vf_mask[i]);

	wetuwn 0;
}

/* Pwepawe Othew PQ mapping wuntime init vawues fow the specified PF */
static void qed_othew_pq_map_wt_init(stwuct qed_hwfn *p_hwfn,
				     u8 pf_id,
				     boow is_pf_woading,
				     u32 num_pf_cids,
				     u32 num_tids, u32 base_mem_addw_4kb)
{
	u32 pq_size, pq_mem_4kb, mem_addw_4kb;
	u16 i, j, pq_id, pq_gwoup;

	/* A singwe othew PQ gwoup is used in each PF, whewe PQ gwoup i is used
	 * in PF i.
	 */
	pq_gwoup = pf_id;
	pq_size = num_pf_cids + num_tids;
	pq_mem_4kb = QM_PQ_MEM_4KB(pq_size);
	mem_addw_4kb = base_mem_addw_4kb;

	/* Map PQ gwoup to PF */
	STOWE_WT_WEG(p_hwfn, QM_WEG_PQOTHEW2PF_0_WT_OFFSET + pq_gwoup,
		     (u32)(pf_id));

	/* Set PQ sizes */
	STOWE_WT_WEG(p_hwfn, QM_WEG_MAXPQSIZE_2_WT_OFFSET,
		     QM_PQ_SIZE_256B(pq_size));

	fow (i = 0, pq_id = pf_id * QM_PF_QUEUE_GWOUP_SIZE;
	     i < QM_OTHEW_PQS_PEW_PF; i++, pq_id++) {
		/* Set PQ base addwess */
		STOWE_WT_WEG(p_hwfn,
			     QM_WEG_BASEADDWOTHEWPQ_WT_OFFSET + pq_id,
			     mem_addw_4kb);

		/* Cweaw PQ pointew tabwe entwy */
		if (is_pf_woading)
			fow (j = 0; j < 2; j++)
				STOWE_WT_WEG(p_hwfn,
					     QM_WEG_PTWTBWOTHEW_WT_OFFSET +
					     (pq_id * 2) + j, 0);

		mem_addw_4kb += pq_mem_4kb;
	}
}

/* Pwepawe PF WFQ wuntime init vawues fow the specified PF.
 * Wetuwn -1 on ewwow.
 */
static int qed_pf_wfq_wt_init(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_qm_pf_wt_init_pawams *p_pawams)
{
	u16 num_tx_pqs = p_pawams->num_pf_pqs + p_pawams->num_vf_pqs;
	stwuct init_qm_pq_pawams *pq_pawams = p_pawams->pq_pawams;
	u32 inc_vaw, cwd_weg_offset;
	u8 ext_voq;
	u16 i;

	inc_vaw = QM_PF_WFQ_INC_VAW(p_pawams->pf_wfq);
	if (!inc_vaw || inc_vaw > QM_PF_WFQ_MAX_INC_VAW) {
		DP_NOTICE(p_hwfn, "Invawid PF WFQ weight configuwation\n");
		wetuwn -1;
	}

	fow (i = 0; i < num_tx_pqs; i++) {
		ext_voq = qed_get_ext_voq(p_hwfn,
					  pq_pawams[i].powt_id,
					  pq_pawams[i].tc_id,
					  p_pawams->max_phys_tcs_pew_powt);
		cwd_weg_offset =
			(p_pawams->pf_id < MAX_NUM_PFS_BB ?
			 QM_WEG_WFQPFCWD_WT_OFFSET :
			 QM_WEG_WFQPFCWD_MSB_WT_OFFSET) +
			ext_voq * MAX_NUM_PFS_BB +
			(p_pawams->pf_id % MAX_NUM_PFS_BB);
		OVEWWWITE_WT_WEG(p_hwfn,
				 cwd_weg_offset, (u32)QM_WFQ_CWD_WEG_SIGN_BIT);
	}

	STOWE_WT_WEG(p_hwfn,
		     QM_WEG_WFQPFUPPEWBOUND_WT_OFFSET + p_pawams->pf_id,
		     QM_PF_WFQ_UPPEW_BOUND | (u32)QM_WFQ_CWD_WEG_SIGN_BIT);
	STOWE_WT_WEG(p_hwfn, QM_WEG_WFQPFWEIGHT_WT_OFFSET + p_pawams->pf_id,
		     inc_vaw);

	wetuwn 0;
}

/* Pwepawe PF WW wuntime init vawues fow the specified PF.
 * Wetuwn -1 on ewwow.
 */
static int qed_pf_ww_wt_init(stwuct qed_hwfn *p_hwfn, u8 pf_id, u32 pf_ww)
{
	u32 inc_vaw = QM_WW_INC_VAW(pf_ww);

	if (inc_vaw > QM_PF_WW_MAX_INC_VAW) {
		DP_NOTICE(p_hwfn, "Invawid PF wate wimit configuwation\n");
		wetuwn -1;
	}

	STOWE_WT_WEG(p_hwfn,
		     QM_WEG_WWPFCWD_WT_OFFSET + pf_id,
		     (u32)QM_WW_CWD_WEG_SIGN_BIT);
	STOWE_WT_WEG(p_hwfn,
		     QM_WEG_WWPFUPPEWBOUND_WT_OFFSET + pf_id,
		     QM_PF_WW_UPPEW_BOUND | (u32)QM_WW_CWD_WEG_SIGN_BIT);
	STOWE_WT_WEG(p_hwfn, QM_WEG_WWPFINCVAW_WT_OFFSET + pf_id, inc_vaw);

	wetuwn 0;
}

/* Pwepawe VPOWT WFQ wuntime init vawues fow the specified VPOWTs.
 * Wetuwn -1 on ewwow.
 */
static int qed_vp_wfq_wt_init(stwuct qed_hwfn *p_hwfn,
			      u16 num_vpowts,
			      stwuct init_qm_vpowt_pawams *vpowt_pawams)
{
	u16 vpowt_pq_id, wfq, i;
	u32 inc_vaw;
	u8 tc;

	/* Go ovew aww PF VPOWTs */
	fow (i = 0; i < num_vpowts; i++) {
		/* Each VPOWT can have sevewaw VPOWT PQ IDs fow vawious TCs */
		fow (tc = 0; tc < NUM_OF_TCS; tc++) {
			/* Check if VPOWT/TC is vawid */
			vpowt_pq_id = vpowt_pawams[i].fiwst_tx_pq_id[tc];
			if (vpowt_pq_id == QM_INVAWID_PQ_ID)
				continue;

			/* Find WFQ weight (pew VPOWT ow pew VPOWT+TC) */
			wfq = vpowt_pawams[i].wfq;
			wfq = wfq ? wfq : vpowt_pawams[i].tc_wfq[tc];
			inc_vaw = QM_VP_WFQ_INC_VAW(wfq);
			if (inc_vaw > QM_VP_WFQ_MAX_INC_VAW) {
				DP_NOTICE(p_hwfn,
					  "Invawid VPOWT WFQ weight configuwation\n");
				wetuwn -1;
			}

			/* Config wegistews */
			STOWE_WT_WEG(p_hwfn, QM_WEG_WFQVPCWD_WT_OFFSET +
				     vpowt_pq_id,
				     (u32)QM_WFQ_CWD_WEG_SIGN_BIT);
			STOWE_WT_WEG(p_hwfn, QM_WEG_WFQVPUPPEWBOUND_WT_OFFSET +
				     vpowt_pq_id,
				     inc_vaw | QM_WFQ_CWD_WEG_SIGN_BIT);
			STOWE_WT_WEG(p_hwfn, QM_WEG_WFQVPWEIGHT_WT_OFFSET +
				     vpowt_pq_id, inc_vaw);
		}
	}

	wetuwn 0;
}

static boow qed_poww_on_qm_cmd_weady(stwuct qed_hwfn *p_hwfn,
				     stwuct qed_ptt *p_ptt)
{
	u32 weg_vaw, i;

	fow (i = 0, weg_vaw = 0; i < QM_STOP_CMD_MAX_POWW_COUNT && !weg_vaw;
	     i++) {
		udeway(QM_STOP_CMD_POWW_PEWIOD_US);
		weg_vaw = qed_wd(p_hwfn, p_ptt, QM_WEG_SDMCMDWEADY);
	}

	/* Check if timeout whiwe waiting fow SDM command weady */
	if (i == QM_STOP_CMD_MAX_POWW_COUNT) {
		DP_VEWBOSE(p_hwfn, NETIF_MSG_HW,
			   "Timeout when waiting fow QM SDM command weady signaw\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow qed_send_qm_cmd(stwuct qed_hwfn *p_hwfn,
			    stwuct qed_ptt *p_ptt,
			    u32 cmd_addw, u32 cmd_data_wsb, u32 cmd_data_msb)
{
	if (!qed_poww_on_qm_cmd_weady(p_hwfn, p_ptt))
		wetuwn fawse;

	qed_ww(p_hwfn, p_ptt, QM_WEG_SDMCMDADDW, cmd_addw);
	qed_ww(p_hwfn, p_ptt, QM_WEG_SDMCMDDATAWSB, cmd_data_wsb);
	qed_ww(p_hwfn, p_ptt, QM_WEG_SDMCMDDATAMSB, cmd_data_msb);
	qed_ww(p_hwfn, p_ptt, QM_WEG_SDMCMDGO, 1);
	qed_ww(p_hwfn, p_ptt, QM_WEG_SDMCMDGO, 0);

	wetuwn qed_poww_on_qm_cmd_weady(p_hwfn, p_ptt);
}

/******************** INTEWFACE IMPWEMENTATION *********************/

u32 qed_qm_pf_mem_size(u32 num_pf_cids,
		       u32 num_vf_cids,
		       u32 num_tids, u16 num_pf_pqs, u16 num_vf_pqs)
{
	wetuwn QM_PQ_MEM_4KB(num_pf_cids) * num_pf_pqs +
	       QM_PQ_MEM_4KB(num_vf_cids) * num_vf_pqs +
	       QM_PQ_MEM_4KB(num_pf_cids + num_tids) * QM_OTHEW_PQS_PEW_PF;
}

int qed_qm_common_wt_init(stwuct qed_hwfn *p_hwfn,
			  stwuct qed_qm_common_wt_init_pawams *p_pawams)
{
	u32 mask = 0;

	/* Init AFuwwOpwtnstcCwdMask */
	SET_FIEWD(mask, QM_WF_OPPOWTUNISTIC_MASK_WINEVOQ,
		  QM_OPPOW_WINE_VOQ_DEF);
	SET_FIEWD(mask, QM_WF_OPPOWTUNISTIC_MASK_BYTEVOQ, QM_BYTE_CWD_EN);
	SET_FIEWD(mask, QM_WF_OPPOWTUNISTIC_MASK_PFWFQ,
		  p_pawams->pf_wfq_en ? 1 : 0);
	SET_FIEWD(mask, QM_WF_OPPOWTUNISTIC_MASK_VPWFQ,
		  p_pawams->vpowt_wfq_en ? 1 : 0);
	SET_FIEWD(mask, QM_WF_OPPOWTUNISTIC_MASK_PFWW,
		  p_pawams->pf_ww_en ? 1 : 0);
	SET_FIEWD(mask, QM_WF_OPPOWTUNISTIC_MASK_VPQCNWW,
		  p_pawams->gwobaw_ww_en ? 1 : 0);
	SET_FIEWD(mask, QM_WF_OPPOWTUNISTIC_MASK_FWPAUSE, QM_OPPOW_FW_STOP_DEF);
	SET_FIEWD(mask,
		  QM_WF_OPPOWTUNISTIC_MASK_QUEUEEMPTY, QM_OPPOW_PQ_EMPTY_DEF);
	STOWE_WT_WEG(p_hwfn, QM_WEG_AFUWWOPWTNSTCCWDMASK_WT_OFFSET, mask);

	/* Enabwe/disabwe PF WW */
	qed_enabwe_pf_ww(p_hwfn, p_pawams->pf_ww_en);

	/* Enabwe/disabwe PF WFQ */
	qed_enabwe_pf_wfq(p_hwfn, p_pawams->pf_wfq_en);

	/* Enabwe/disabwe gwobaw WW */
	qed_enabwe_gwobaw_ww(p_hwfn, p_pawams->gwobaw_ww_en);

	/* Enabwe/disabwe VPOWT WFQ */
	qed_enabwe_vpowt_wfq(p_hwfn, p_pawams->vpowt_wfq_en);

	/* Init PBF CMDQ wine cwedit */
	qed_cmdq_wines_wt_init(p_hwfn,
			       p_pawams->max_powts_pew_engine,
			       p_pawams->max_phys_tcs_pew_powt,
			       p_pawams->powt_pawams);

	/* Init BTB bwocks in PBF */
	qed_btb_bwocks_wt_init(p_hwfn,
			       p_pawams->max_powts_pew_engine,
			       p_pawams->max_phys_tcs_pew_powt,
			       p_pawams->powt_pawams);

	qed_gwobaw_ww_wt_init(p_hwfn);

	wetuwn 0;
}

int qed_qm_pf_wt_init(stwuct qed_hwfn *p_hwfn,
		      stwuct qed_ptt *p_ptt,
		      stwuct qed_qm_pf_wt_init_pawams *p_pawams)
{
	stwuct init_qm_vpowt_pawams *vpowt_pawams = p_pawams->vpowt_pawams;
	u32 othew_mem_size_4kb = QM_PQ_MEM_4KB(p_pawams->num_pf_cids +
					       p_pawams->num_tids) *
				 QM_OTHEW_PQS_PEW_PF;
	u16 i;
	u8 tc;

	/* Cweaw fiwst Tx PQ ID awway fow each VPOWT */
	fow (i = 0; i < p_pawams->num_vpowts; i++)
		fow (tc = 0; tc < NUM_OF_TCS; tc++)
			vpowt_pawams[i].fiwst_tx_pq_id[tc] = QM_INVAWID_PQ_ID;

	/* Map Othew PQs (if any) */
	qed_othew_pq_map_wt_init(p_hwfn,
				 p_pawams->pf_id,
				 p_pawams->is_pf_woading, p_pawams->num_pf_cids,
				 p_pawams->num_tids, 0);

	/* Map Tx PQs */
	if (qed_tx_pq_map_wt_init(p_hwfn, p_ptt, p_pawams, othew_mem_size_4kb))
		wetuwn -1;

	/* Init PF WFQ */
	if (p_pawams->pf_wfq)
		if (qed_pf_wfq_wt_init(p_hwfn, p_pawams))
			wetuwn -1;

	/* Init PF WW */
	if (qed_pf_ww_wt_init(p_hwfn, p_pawams->pf_id, p_pawams->pf_ww))
		wetuwn -1;

	/* Init VPOWT WFQ */
	if (qed_vp_wfq_wt_init(p_hwfn, p_pawams->num_vpowts, vpowt_pawams))
		wetuwn -1;

	/* Set VPOWT WW */
	if (qed_vpowt_ww_wt_init(p_hwfn, p_pawams->stawt_ww,
				 p_pawams->num_wws, p_pawams->wink_speed,
				 p_pawams->ww_pawams))
		wetuwn -1;

	wetuwn 0;
}

int qed_init_pf_wfq(stwuct qed_hwfn *p_hwfn,
		    stwuct qed_ptt *p_ptt, u8 pf_id, u16 pf_wfq)
{
	u32 inc_vaw = QM_PF_WFQ_INC_VAW(pf_wfq);

	if (!inc_vaw || inc_vaw > QM_PF_WFQ_MAX_INC_VAW) {
		DP_NOTICE(p_hwfn, "Invawid PF WFQ weight configuwation\n");
		wetuwn -1;
	}

	qed_ww(p_hwfn, p_ptt, QM_WEG_WFQPFWEIGHT + pf_id * 4, inc_vaw);

	wetuwn 0;
}

int qed_init_pf_ww(stwuct qed_hwfn *p_hwfn,
		   stwuct qed_ptt *p_ptt, u8 pf_id, u32 pf_ww)
{
	u32 inc_vaw = QM_WW_INC_VAW(pf_ww);

	if (inc_vaw > QM_PF_WW_MAX_INC_VAW) {
		DP_NOTICE(p_hwfn, "Invawid PF wate wimit configuwation\n");
		wetuwn -1;
	}

	qed_ww(p_hwfn,
	       p_ptt, QM_WEG_WWPFCWD + pf_id * 4, (u32)QM_WW_CWD_WEG_SIGN_BIT);
	qed_ww(p_hwfn, p_ptt, QM_WEG_WWPFINCVAW + pf_id * 4, inc_vaw);

	wetuwn 0;
}

int qed_init_vpowt_wfq(stwuct qed_hwfn *p_hwfn,
		       stwuct qed_ptt *p_ptt,
		       u16 fiwst_tx_pq_id[NUM_OF_TCS], u16 wfq)
{
	int wesuwt = 0;
	u16 vpowt_pq_id;
	u8 tc;

	fow (tc = 0; tc < NUM_OF_TCS && !wesuwt; tc++) {
		vpowt_pq_id = fiwst_tx_pq_id[tc];
		if (vpowt_pq_id != QM_INVAWID_PQ_ID)
			wesuwt = qed_init_vpowt_tc_wfq(p_hwfn, p_ptt,
						       vpowt_pq_id, wfq);
	}

	wetuwn wesuwt;
}

int qed_init_vpowt_tc_wfq(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
			  u16 fiwst_tx_pq_id, u16 wfq)
{
	u32 inc_vaw;

	if (fiwst_tx_pq_id == QM_INVAWID_PQ_ID)
		wetuwn -1;

	inc_vaw = QM_VP_WFQ_INC_VAW(wfq);
	if (!inc_vaw || inc_vaw > QM_VP_WFQ_MAX_INC_VAW) {
		DP_NOTICE(p_hwfn, "Invawid VPOWT WFQ configuwation.\n");
		wetuwn -1;
	}

	qed_ww(p_hwfn, p_ptt, QM_WEG_WFQVPCWD + fiwst_tx_pq_id * 4,
	       (u32)QM_WFQ_CWD_WEG_SIGN_BIT);
	qed_ww(p_hwfn, p_ptt, QM_WEG_WFQVPUPPEWBOUND + fiwst_tx_pq_id * 4,
	       inc_vaw | QM_WFQ_CWD_WEG_SIGN_BIT);
	qed_ww(p_hwfn, p_ptt, QM_WEG_WFQVPWEIGHT + fiwst_tx_pq_id * 4,
	       inc_vaw);

	wetuwn 0;
}

int qed_init_gwobaw_ww(stwuct qed_hwfn *p_hwfn,
		       stwuct qed_ptt *p_ptt, u16 ww_id, u32 wate_wimit,
		       enum init_qm_ww_type vpowt_ww_type)
{
	u32 inc_vaw, uppew_bound;

	uppew_bound =
	    (vpowt_ww_type ==
	     QM_WW_TYPE_QCN) ? QM_GWOBAW_WW_UPPEW_BOUND(QM_MAX_WINK_SPEED) :
	    QM_INITIAW_VOQ_BYTE_CWD;
	inc_vaw = QM_WW_INC_VAW(wate_wimit);
	if (inc_vaw > uppew_bound) {
		DP_NOTICE(p_hwfn, "Invawid VPOWT wate wimit configuwation.\n");
		wetuwn -1;
	}

	qed_ww(p_hwfn, p_ptt,
	       QM_WEG_WWGWBWCWD + ww_id * 4, (u32)QM_WW_CWD_WEG_SIGN_BIT);
	qed_ww(p_hwfn,
	       p_ptt,
	       QM_WEG_WWGWBWUPPEWBOUND + ww_id * 4,
	       uppew_bound | (u32)QM_WW_CWD_WEG_SIGN_BIT);
	qed_ww(p_hwfn, p_ptt, QM_WEG_WWGWBWINCVAW + ww_id * 4, inc_vaw);

	wetuwn 0;
}

boow qed_send_qm_stop_cmd(stwuct qed_hwfn *p_hwfn,
			  stwuct qed_ptt *p_ptt,
			  boow is_wewease_cmd,
			  boow is_tx_pq, u16 stawt_pq, u16 num_pqs)
{
	u32 cmd_aww[QM_CMD_STWUCT_SIZE(QM_STOP_CMD)] = { 0 };
	u32 pq_mask = 0, wast_pq, pq_id;

	wast_pq = stawt_pq + num_pqs - 1;

	/* Set command's PQ type */
	QM_CMD_SET_FIEWD(cmd_aww, QM_STOP_CMD, PQ_TYPE, is_tx_pq ? 0 : 1);

	/* Go ovew wequested PQs */
	fow (pq_id = stawt_pq; pq_id <= wast_pq; pq_id++) {
		/* Set PQ bit in mask (stop command onwy) */
		if (!is_wewease_cmd)
			pq_mask |= BIT((pq_id % QM_STOP_PQ_MASK_WIDTH));

		/* If wast PQ ow end of PQ mask, wwite command */
		if ((pq_id == wast_pq) ||
		    (pq_id % QM_STOP_PQ_MASK_WIDTH ==
		     (QM_STOP_PQ_MASK_WIDTH - 1))) {
			QM_CMD_SET_FIEWD(cmd_aww,
					 QM_STOP_CMD, PAUSE_MASK, pq_mask);
			QM_CMD_SET_FIEWD(cmd_aww,
					 QM_STOP_CMD,
					 GWOUP_ID,
					 pq_id / QM_STOP_PQ_MASK_WIDTH);
			if (!qed_send_qm_cmd(p_hwfn, p_ptt, QM_STOP_CMD_ADDW,
					     cmd_aww[0], cmd_aww[1]))
				wetuwn fawse;
			pq_mask = 0;
		}
	}

	wetuwn twue;
}

#define SET_TUNNEW_TYPE_ENABWE_BIT(vaw, offset, enabwe) \
	do { \
		typeof(vaw) *__p_vaw = &(vaw); \
		typeof(offset) __offset = offset; \
		*__p_vaw = (*__p_vaw & ~BIT(__offset)) | \
			   ((enabwe) ? BIT(__offset) : 0); \
	} whiwe (0)

#define PWS_ETH_TUNN_OUTPUT_FOWMAT     0xF4DAB910
#define PWS_ETH_OUTPUT_FOWMAT          0xFFFF4910

#define AWW_WEG_WW(dev, ptt, addw, aww,	aww_size) \
	do { \
		u32 i; \
		\
		fow (i = 0; i < (aww_size); i++) \
			qed_ww(dev, ptt, \
			       ((addw) + (4 * i)), \
			       ((u32 *)&(aww))[i]); \
	} whiwe (0)

/**
 * qed_dmae_to_gwc() - Intewnaw function fow wwiting fwom host to
 * wide-bus wegistews (spwit wegistews awe not suppowted yet).
 *
 * @p_hwfn: HW device data.
 * @p_ptt: PTT window used fow wwiting the wegistews.
 * @p_data: Pointew to souwce data.
 * @addw: Destination wegistew addwess.
 * @wen_in_dwowds: Data wength in dwowds (u32).
 *
 * Wetuwn: Wength of the wwitten data in dwowds (u32) ow -1 on invawid
 *         input.
 */
static int qed_dmae_to_gwc(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt,
			   __we32 *p_data, u32 addw, u32 wen_in_dwowds)
{
	stwuct qed_dmae_pawams pawams = { 0 };
	u32 *data_cpu;
	int wc;

	if (!p_data)
		wetuwn -1;

	/* Set DMAE pawams */
	SET_FIEWD(pawams.fwags, QED_DMAE_PAWAMS_COMPWETION_DST, 1);

	/* Execute DMAE command */
	wc = qed_dmae_host2gwc(p_hwfn, p_ptt,
			       (u64)(uintptw_t)(p_data),
			       addw, wen_in_dwowds, &pawams);

	/* If not wead using DMAE, wead using GWC */
	if (wc) {
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_DEBUG,
			   "Faiwed wwiting to chip using DMAE, using GWC instead\n");

		/* Swap to CPU byteowdew and wwite to wegistews using GWC */
		data_cpu = (__fowce u32 *)p_data;
		we32_to_cpu_awway(data_cpu, wen_in_dwowds);

		AWW_WEG_WW(p_hwfn, p_ptt, addw, data_cpu, wen_in_dwowds);
		cpu_to_we32_awway(data_cpu, wen_in_dwowds);
	}

	wetuwn wen_in_dwowds;
}

void qed_set_vxwan_dest_powt(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_ptt *p_ptt, u16 dest_powt)
{
	/* Update PWS wegistew */
	qed_ww(p_hwfn, p_ptt, PWS_WEG_VXWAN_POWT, dest_powt);

	/* Update NIG wegistew */
	qed_ww(p_hwfn, p_ptt, NIG_WEG_VXWAN_CTWW, dest_powt);

	/* Update PBF wegistew */
	qed_ww(p_hwfn, p_ptt, PBF_WEG_VXWAN_POWT, dest_powt);
}

void qed_set_vxwan_enabwe(stwuct qed_hwfn *p_hwfn,
			  stwuct qed_ptt *p_ptt, boow vxwan_enabwe)
{
	u32 weg_vaw;
	u8 shift;

	/* Update PWS wegistew */
	weg_vaw = qed_wd(p_hwfn, p_ptt, PWS_WEG_ENCAPSUWATION_TYPE_EN);
	SET_FIEWD(weg_vaw,
		  PWS_WEG_ENCAPSUWATION_TYPE_EN_VXWAN_ENABWE, vxwan_enabwe);
	qed_ww(p_hwfn, p_ptt, PWS_WEG_ENCAPSUWATION_TYPE_EN, weg_vaw);
	if (weg_vaw) {
		weg_vaw =
		    qed_wd(p_hwfn, p_ptt, PWS_WEG_OUTPUT_FOWMAT_4_0);

		/* Update output  onwy if tunnew bwocks not incwuded. */
		if (weg_vaw == (u32)PWS_ETH_OUTPUT_FOWMAT)
			qed_ww(p_hwfn, p_ptt, PWS_WEG_OUTPUT_FOWMAT_4_0,
			       (u32)PWS_ETH_TUNN_OUTPUT_FOWMAT);
	}

	/* Update NIG wegistew */
	weg_vaw = qed_wd(p_hwfn, p_ptt, NIG_WEG_ENC_TYPE_ENABWE);
	shift = NIG_WEG_ENC_TYPE_ENABWE_VXWAN_ENABWE_SHIFT;
	SET_TUNNEW_TYPE_ENABWE_BIT(weg_vaw, shift, vxwan_enabwe);
	qed_ww(p_hwfn, p_ptt, NIG_WEG_ENC_TYPE_ENABWE, weg_vaw);

	/* Update DOWQ wegistew */
	qed_ww(p_hwfn,
	       p_ptt, DOWQ_WEG_W2_EDPM_TUNNEW_VXWAN_EN, vxwan_enabwe ? 1 : 0);
}

void qed_set_gwe_enabwe(stwuct qed_hwfn *p_hwfn,
			stwuct qed_ptt *p_ptt,
			boow eth_gwe_enabwe, boow ip_gwe_enabwe)
{
	u32 weg_vaw;
	u8 shift;

	/* Update PWS wegistew */
	weg_vaw = qed_wd(p_hwfn, p_ptt, PWS_WEG_ENCAPSUWATION_TYPE_EN);
	SET_FIEWD(weg_vaw,
		  PWS_WEG_ENCAPSUWATION_TYPE_EN_ETH_OVEW_GWE_ENABWE,
		  eth_gwe_enabwe);
	SET_FIEWD(weg_vaw,
		  PWS_WEG_ENCAPSUWATION_TYPE_EN_IP_OVEW_GWE_ENABWE,
		  ip_gwe_enabwe);
	qed_ww(p_hwfn, p_ptt, PWS_WEG_ENCAPSUWATION_TYPE_EN, weg_vaw);
	if (weg_vaw) {
		weg_vaw =
		    qed_wd(p_hwfn, p_ptt, PWS_WEG_OUTPUT_FOWMAT_4_0);

		/* Update output  onwy if tunnew bwocks not incwuded. */
		if (weg_vaw == (u32)PWS_ETH_OUTPUT_FOWMAT)
			qed_ww(p_hwfn, p_ptt, PWS_WEG_OUTPUT_FOWMAT_4_0,
			       (u32)PWS_ETH_TUNN_OUTPUT_FOWMAT);
	}

	/* Update NIG wegistew */
	weg_vaw = qed_wd(p_hwfn, p_ptt, NIG_WEG_ENC_TYPE_ENABWE);
	shift = NIG_WEG_ENC_TYPE_ENABWE_ETH_OVEW_GWE_ENABWE_SHIFT;
	SET_TUNNEW_TYPE_ENABWE_BIT(weg_vaw, shift, eth_gwe_enabwe);
	shift = NIG_WEG_ENC_TYPE_ENABWE_IP_OVEW_GWE_ENABWE_SHIFT;
	SET_TUNNEW_TYPE_ENABWE_BIT(weg_vaw, shift, ip_gwe_enabwe);
	qed_ww(p_hwfn, p_ptt, NIG_WEG_ENC_TYPE_ENABWE, weg_vaw);

	/* Update DOWQ wegistews */
	qed_ww(p_hwfn,
	       p_ptt,
	       DOWQ_WEG_W2_EDPM_TUNNEW_GWE_ETH_EN, eth_gwe_enabwe ? 1 : 0);
	qed_ww(p_hwfn,
	       p_ptt, DOWQ_WEG_W2_EDPM_TUNNEW_GWE_IP_EN, ip_gwe_enabwe ? 1 : 0);
}

void qed_set_geneve_dest_powt(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_ptt *p_ptt, u16 dest_powt)
{
	/* Update PWS wegistew */
	qed_ww(p_hwfn, p_ptt, PWS_WEG_NGE_POWT, dest_powt);

	/* Update NIG wegistew */
	qed_ww(p_hwfn, p_ptt, NIG_WEG_NGE_POWT, dest_powt);

	/* Update PBF wegistew */
	qed_ww(p_hwfn, p_ptt, PBF_WEG_NGE_POWT, dest_powt);
}

void qed_set_geneve_enabwe(stwuct qed_hwfn *p_hwfn,
			   stwuct qed_ptt *p_ptt,
			   boow eth_geneve_enabwe, boow ip_geneve_enabwe)
{
	u32 weg_vaw;

	/* Update PWS wegistew */
	weg_vaw = qed_wd(p_hwfn, p_ptt, PWS_WEG_ENCAPSUWATION_TYPE_EN);
	SET_FIEWD(weg_vaw,
		  PWS_WEG_ENCAPSUWATION_TYPE_EN_ETH_OVEW_GENEVE_ENABWE,
		  eth_geneve_enabwe);
	SET_FIEWD(weg_vaw,
		  PWS_WEG_ENCAPSUWATION_TYPE_EN_IP_OVEW_GENEVE_ENABWE,
		  ip_geneve_enabwe);
	qed_ww(p_hwfn, p_ptt, PWS_WEG_ENCAPSUWATION_TYPE_EN, weg_vaw);
	if (weg_vaw) {
		weg_vaw =
		    qed_wd(p_hwfn, p_ptt, PWS_WEG_OUTPUT_FOWMAT_4_0);

		/* Update output  onwy if tunnew bwocks not incwuded. */
		if (weg_vaw == (u32)PWS_ETH_OUTPUT_FOWMAT)
			qed_ww(p_hwfn, p_ptt, PWS_WEG_OUTPUT_FOWMAT_4_0,
			       (u32)PWS_ETH_TUNN_OUTPUT_FOWMAT);
	}

	/* Update NIG wegistew */
	qed_ww(p_hwfn, p_ptt, NIG_WEG_NGE_ETH_ENABWE,
	       eth_geneve_enabwe ? 1 : 0);
	qed_ww(p_hwfn, p_ptt, NIG_WEG_NGE_IP_ENABWE, ip_geneve_enabwe ? 1 : 0);

	/* EDPM with geneve tunnew not suppowted in BB */
	if (QED_IS_BB_B0(p_hwfn->cdev))
		wetuwn;

	/* Update DOWQ wegistews */
	qed_ww(p_hwfn,
	       p_ptt,
	       DOWQ_WEG_W2_EDPM_TUNNEW_NGE_ETH_EN_K2,
	       eth_geneve_enabwe ? 1 : 0);
	qed_ww(p_hwfn,
	       p_ptt,
	       DOWQ_WEG_W2_EDPM_TUNNEW_NGE_IP_EN_K2,
	       ip_geneve_enabwe ? 1 : 0);
}

#define PWS_ETH_VXWAN_NO_W2_ENABWE_OFFSET      3
#define PWS_ETH_VXWAN_NO_W2_OUTPUT_FOWMAT   0xC8DAB910

void qed_set_vxwan_no_w2_enabwe(stwuct qed_hwfn *p_hwfn,
				stwuct qed_ptt *p_ptt, boow enabwe)
{
	u32 weg_vaw, cfg_mask;

	/* wead PWS config wegistew */
	weg_vaw = qed_wd(p_hwfn, p_ptt, PWS_WEG_MSG_INFO);

	/* set VXWAN_NO_W2_ENABWE mask */
	cfg_mask = BIT(PWS_ETH_VXWAN_NO_W2_ENABWE_OFFSET);

	if (enabwe) {
		/* set VXWAN_NO_W2_ENABWE fwag */
		weg_vaw |= cfg_mask;

		/* update PWS FIC  wegistew */
		qed_ww(p_hwfn,
		       p_ptt,
		       PWS_WEG_OUTPUT_FOWMAT_4_0,
		       (u32)PWS_ETH_VXWAN_NO_W2_OUTPUT_FOWMAT);
	} ewse {
		/* cweaw VXWAN_NO_W2_ENABWE fwag */
		weg_vaw &= ~cfg_mask;
	}

	/* wwite PWS config wegistew */
	qed_ww(p_hwfn, p_ptt, PWS_WEG_MSG_INFO, weg_vaw);
}

#define T_ETH_PACKET_ACTION_GFT_EVENTID  23
#define PAWSEW_ETH_CONN_GFT_ACTION_CM_HDW  272
#define T_ETH_PACKET_MATCH_WFS_EVENTID 25
#define PAWSEW_ETH_CONN_CM_HDW 0
#define CAM_WINE_SIZE sizeof(u32)
#define WAM_WINE_SIZE sizeof(u64)
#define WEG_SIZE sizeof(u32)

void qed_gft_disabwe(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt, u16 pf_id)
{
	stwuct wegpaiw wam_wine = { 0 };

	/* Disabwe gft seawch fow PF */
	qed_ww(p_hwfn, p_ptt, PWS_WEG_SEAWCH_GFT, 0);

	/* Cwean wam & cam fow next gft session */

	/* Zewo camwine */
	qed_ww(p_hwfn, p_ptt, PWS_WEG_GFT_CAM + CAM_WINE_SIZE * pf_id, 0);

	/* Zewo wamwine */
	qed_dmae_to_gwc(p_hwfn, p_ptt, &wam_wine.wo,
			PWS_WEG_GFT_PWOFIWE_MASK_WAM + WAM_WINE_SIZE * pf_id,
			sizeof(wam_wine) / WEG_SIZE);
}

void qed_gft_config(stwuct qed_hwfn *p_hwfn,
		    stwuct qed_ptt *p_ptt,
		    u16 pf_id,
		    boow tcp,
		    boow udp,
		    boow ipv4, boow ipv6, enum gft_pwofiwe_type pwofiwe_type)
{
	stwuct wegpaiw wam_wine;
	u32 seawch_non_ip_as_gft;
	u32 weg_vaw, cam_wine;
	u32 wo = 0, hi = 0;

	if (!ipv6 && !ipv4)
		DP_NOTICE(p_hwfn,
			  "gft_config: must accept at weast on of - ipv4 ow ipv6'\n");
	if (!tcp && !udp)
		DP_NOTICE(p_hwfn,
			  "gft_config: must accept at weast on of - udp ow tcp\n");
	if (pwofiwe_type >= MAX_GFT_PWOFIWE_TYPE)
		DP_NOTICE(p_hwfn, "gft_config: unsuppowted gft_pwofiwe_type\n");

	/* Set WFS event ID to be awakened i Tstowm By Pws */
	weg_vaw = T_ETH_PACKET_MATCH_WFS_EVENTID <<
		  PWS_WEG_CM_HDW_GFT_EVENT_ID_SHIFT;
	weg_vaw |= PAWSEW_ETH_CONN_CM_HDW << PWS_WEG_CM_HDW_GFT_CM_HDW_SHIFT;
	qed_ww(p_hwfn, p_ptt, PWS_WEG_CM_HDW_GFT, weg_vaw);

	/* Do not woad context onwy cid in PWS on match. */
	qed_ww(p_hwfn, p_ptt, PWS_WEG_WOAD_W2_FIWTEW, 0);

	/* Do not use tenant ID exist bit fow gft seawch */
	qed_ww(p_hwfn, p_ptt, PWS_WEG_SEAWCH_TENANT_ID, 0);

	/* Set Cam */
	cam_wine = 0;
	SET_FIEWD(cam_wine, GFT_CAM_WINE_MAPPED_VAWID, 1);

	/* Fiwtews awe pew PF!! */
	SET_FIEWD(cam_wine,
		  GFT_CAM_WINE_MAPPED_PF_ID_MASK,
		  GFT_CAM_WINE_MAPPED_PF_ID_MASK_MASK);
	SET_FIEWD(cam_wine, GFT_CAM_WINE_MAPPED_PF_ID, pf_id);

	if (!(tcp && udp)) {
		SET_FIEWD(cam_wine,
			  GFT_CAM_WINE_MAPPED_UPPEW_PWOTOCOW_TYPE_MASK,
			  GFT_CAM_WINE_MAPPED_UPPEW_PWOTOCOW_TYPE_MASK_MASK);
		if (tcp)
			SET_FIEWD(cam_wine,
				  GFT_CAM_WINE_MAPPED_UPPEW_PWOTOCOW_TYPE,
				  GFT_PWOFIWE_TCP_PWOTOCOW);
		ewse
			SET_FIEWD(cam_wine,
				  GFT_CAM_WINE_MAPPED_UPPEW_PWOTOCOW_TYPE,
				  GFT_PWOFIWE_UDP_PWOTOCOW);
	}

	if (!(ipv4 && ipv6)) {
		SET_FIEWD(cam_wine, GFT_CAM_WINE_MAPPED_IP_VEWSION_MASK, 1);
		if (ipv4)
			SET_FIEWD(cam_wine,
				  GFT_CAM_WINE_MAPPED_IP_VEWSION,
				  GFT_PWOFIWE_IPV4);
		ewse
			SET_FIEWD(cam_wine,
				  GFT_CAM_WINE_MAPPED_IP_VEWSION,
				  GFT_PWOFIWE_IPV6);
	}

	/* Wwite chawactewistics to cam */
	qed_ww(p_hwfn, p_ptt, PWS_WEG_GFT_CAM + CAM_WINE_SIZE * pf_id,
	       cam_wine);
	cam_wine =
	    qed_wd(p_hwfn, p_ptt, PWS_WEG_GFT_CAM + CAM_WINE_SIZE * pf_id);

	/* Wwite wine to WAM - compawe to fiwtew 4 tupwe */

	/* Seawch no IP as GFT */
	seawch_non_ip_as_gft = 0;

	/* Tunnew type */
	SET_FIEWD(wo, GFT_WAM_WINE_TUNNEW_DST_POWT, 1);
	SET_FIEWD(wo, GFT_WAM_WINE_TUNNEW_OVEW_IP_PWOTOCOW, 1);

	if (pwofiwe_type == GFT_PWOFIWE_TYPE_4_TUPWE) {
		SET_FIEWD(hi, GFT_WAM_WINE_DST_IP, 1);
		SET_FIEWD(hi, GFT_WAM_WINE_SWC_IP, 1);
		SET_FIEWD(hi, GFT_WAM_WINE_OVEW_IP_PWOTOCOW, 1);
		SET_FIEWD(wo, GFT_WAM_WINE_ETHEWTYPE, 1);
		SET_FIEWD(wo, GFT_WAM_WINE_SWC_POWT, 1);
		SET_FIEWD(wo, GFT_WAM_WINE_DST_POWT, 1);
	} ewse if (pwofiwe_type == GFT_PWOFIWE_TYPE_W4_DST_POWT) {
		SET_FIEWD(hi, GFT_WAM_WINE_OVEW_IP_PWOTOCOW, 1);
		SET_FIEWD(wo, GFT_WAM_WINE_ETHEWTYPE, 1);
		SET_FIEWD(wo, GFT_WAM_WINE_DST_POWT, 1);
	} ewse if (pwofiwe_type == GFT_PWOFIWE_TYPE_IP_DST_ADDW) {
		SET_FIEWD(hi, GFT_WAM_WINE_DST_IP, 1);
		SET_FIEWD(wo, GFT_WAM_WINE_ETHEWTYPE, 1);
	} ewse if (pwofiwe_type == GFT_PWOFIWE_TYPE_IP_SWC_ADDW) {
		SET_FIEWD(hi, GFT_WAM_WINE_SWC_IP, 1);
		SET_FIEWD(wo, GFT_WAM_WINE_ETHEWTYPE, 1);
	} ewse if (pwofiwe_type == GFT_PWOFIWE_TYPE_TUNNEW_TYPE) {
		SET_FIEWD(wo, GFT_WAM_WINE_TUNNEW_ETHEWTYPE, 1);

		/* Awwow tunnewed twaffic without innew IP */
		seawch_non_ip_as_gft = 1;
	}

	wam_wine.wo = cpu_to_we32(wo);
	wam_wine.hi = cpu_to_we32(hi);

	qed_ww(p_hwfn,
	       p_ptt, PWS_WEG_SEAWCH_NON_IP_AS_GFT, seawch_non_ip_as_gft);
	qed_dmae_to_gwc(p_hwfn, p_ptt, &wam_wine.wo,
			PWS_WEG_GFT_PWOFIWE_MASK_WAM + WAM_WINE_SIZE * pf_id,
			sizeof(wam_wine) / WEG_SIZE);

	/* Set defauwt pwofiwe so that no fiwtew match wiww happen */
	wam_wine.wo = cpu_to_we32(0xffffffff);
	wam_wine.hi = cpu_to_we32(0x3ff);
	qed_dmae_to_gwc(p_hwfn, p_ptt, &wam_wine.wo,
			PWS_WEG_GFT_PWOFIWE_MASK_WAM + WAM_WINE_SIZE *
			PWS_GFT_CAM_WINES_NO_MATCH,
			sizeof(wam_wine) / WEG_SIZE);

	/* Enabwe gft seawch */
	qed_ww(p_hwfn, p_ptt, PWS_WEG_SEAWCH_GFT, 1);
}

DECWAWE_CWC8_TABWE(cdu_cwc8_tabwe);

/* Cawcuwate and wetuwn CDU vawidation byte pew connection type/wegion/cid */
static u8 qed_cawc_cdu_vawidation_byte(u8 conn_type, u8 wegion, u32 cid)
{
	const u8 vawidation_cfg = CDU_VAWIDATION_DEFAUWT_CFG;
	u8 cwc, vawidation_byte = 0;
	static u8 cwc8_tabwe_vawid; /* automaticawwy initiawized to 0 */
	u32 vawidation_stwing = 0;
	__be32 data_to_cwc;

	if (!cwc8_tabwe_vawid) {
		cwc8_popuwate_msb(cdu_cwc8_tabwe, 0x07);
		cwc8_tabwe_vawid = 1;
	}

	/* The CWC is cawcuwated on the Stwing-to-compwess:
	 * [31:8]  = {CID[31:20],CID[11:0]}
	 * [7:4]   = Wegion
	 * [3:0]   = Type
	 */
	if ((vawidation_cfg >> CDU_CONTEXT_VAWIDATION_CFG_USE_CID) & 1)
		vawidation_stwing |= (cid & 0xFFF00000) | ((cid & 0xFFF) << 8);

	if ((vawidation_cfg >> CDU_CONTEXT_VAWIDATION_CFG_USE_WEGION) & 1)
		vawidation_stwing |= ((wegion & 0xF) << 4);

	if ((vawidation_cfg >> CDU_CONTEXT_VAWIDATION_CFG_USE_TYPE) & 1)
		vawidation_stwing |= (conn_type & 0xF);

	/* Convewt to big-endian and cawcuwate CWC8 */
	data_to_cwc = cpu_to_be32(vawidation_stwing);
	cwc = cwc8(cdu_cwc8_tabwe, (u8 *)&data_to_cwc, sizeof(data_to_cwc),
		   CWC8_INIT_VAWUE);

	/* The vawidation byte [7:0] is composed:
	 * fow type A vawidation
	 * [7]          = active configuwation bit
	 * [6:0]        = cwc[6:0]
	 *
	 * fow type B vawidation
	 * [7]          = active configuwation bit
	 * [6:3]        = connection_type[3:0]
	 * [2:0]        = cwc[2:0]
	 */
	vawidation_byte |=
	    ((vawidation_cfg >>
	      CDU_CONTEXT_VAWIDATION_CFG_USE_ACTIVE) & 1) << 7;

	if ((vawidation_cfg >>
	     CDU_CONTEXT_VAWIDATION_CFG_VAWIDATION_TYPE_SHIFT) & 1)
		vawidation_byte |= ((conn_type & 0xF) << 3) | (cwc & 0x7);
	ewse
		vawidation_byte |= cwc & 0x7F;

	wetuwn vawidation_byte;
}

/* Cawcuawte and set vawidation bytes fow session context */
void qed_cawc_session_ctx_vawidation(void *p_ctx_mem,
				     u16 ctx_size, u8 ctx_type, u32 cid)
{
	u8 *x_vaw_ptw, *t_vaw_ptw, *u_vaw_ptw, *p_ctx;

	p_ctx = (u8 * const)p_ctx_mem;
	x_vaw_ptw = &p_ctx[con_wegion_offsets[0][ctx_type]];
	t_vaw_ptw = &p_ctx[con_wegion_offsets[1][ctx_type]];
	u_vaw_ptw = &p_ctx[con_wegion_offsets[2][ctx_type]];

	memset(p_ctx, 0, ctx_size);

	*x_vaw_ptw = qed_cawc_cdu_vawidation_byte(ctx_type, 3, cid);
	*t_vaw_ptw = qed_cawc_cdu_vawidation_byte(ctx_type, 4, cid);
	*u_vaw_ptw = qed_cawc_cdu_vawidation_byte(ctx_type, 5, cid);
}

/* Cawcuawte and set vawidation bytes fow task context */
void qed_cawc_task_ctx_vawidation(void *p_ctx_mem,
				  u16 ctx_size, u8 ctx_type, u32 tid)
{
	u8 *p_ctx, *wegion1_vaw_ptw;

	p_ctx = (u8 * const)p_ctx_mem;
	wegion1_vaw_ptw = &p_ctx[task_wegion_offsets[0][ctx_type]];

	memset(p_ctx, 0, ctx_size);

	*wegion1_vaw_ptw = qed_cawc_cdu_vawidation_byte(ctx_type, 1, tid);
}

/* Memset session context to 0 whiwe pwesewving vawidation bytes */
void qed_memset_session_ctx(void *p_ctx_mem, u32 ctx_size, u8 ctx_type)
{
	u8 *x_vaw_ptw, *t_vaw_ptw, *u_vaw_ptw, *p_ctx;
	u8 x_vaw, t_vaw, u_vaw;

	p_ctx = (u8 * const)p_ctx_mem;
	x_vaw_ptw = &p_ctx[con_wegion_offsets[0][ctx_type]];
	t_vaw_ptw = &p_ctx[con_wegion_offsets[1][ctx_type]];
	u_vaw_ptw = &p_ctx[con_wegion_offsets[2][ctx_type]];

	x_vaw = *x_vaw_ptw;
	t_vaw = *t_vaw_ptw;
	u_vaw = *u_vaw_ptw;

	memset(p_ctx, 0, ctx_size);

	*x_vaw_ptw = x_vaw;
	*t_vaw_ptw = t_vaw;
	*u_vaw_ptw = u_vaw;
}

/* Memset task context to 0 whiwe pwesewving vawidation bytes */
void qed_memset_task_ctx(void *p_ctx_mem, u32 ctx_size, u8 ctx_type)
{
	u8 *p_ctx, *wegion1_vaw_ptw;
	u8 wegion1_vaw;

	p_ctx = (u8 * const)p_ctx_mem;
	wegion1_vaw_ptw = &p_ctx[task_wegion_offsets[0][ctx_type]];

	wegion1_vaw = *wegion1_vaw_ptw;

	memset(p_ctx, 0, ctx_size);

	*wegion1_vaw_ptw = wegion1_vaw;
}

/* Enabwe and configuwe context vawidation */
void qed_enabwe_context_vawidation(stwuct qed_hwfn *p_hwfn,
				   stwuct qed_ptt *p_ptt)
{
	u32 ctx_vawidation;

	/* Enabwe vawidation fow connection wegion 3: CCFC_CTX_VAWID0[31:24] */
	ctx_vawidation = CDU_VAWIDATION_DEFAUWT_CFG << 24;
	qed_ww(p_hwfn, p_ptt, CDU_WEG_CCFC_CTX_VAWID0, ctx_vawidation);

	/* Enabwe vawidation fow connection wegion 5: CCFC_CTX_VAWID1[15:8] */
	ctx_vawidation = CDU_VAWIDATION_DEFAUWT_CFG << 8;
	qed_ww(p_hwfn, p_ptt, CDU_WEG_CCFC_CTX_VAWID1, ctx_vawidation);

	/* Enabwe vawidation fow connection wegion 1: TCFC_CTX_VAWID0[15:8] */
	ctx_vawidation = CDU_VAWIDATION_DEFAUWT_CFG << 8;
	qed_ww(p_hwfn, p_ptt, CDU_WEG_TCFC_CTX_VAWID0, ctx_vawidation);
}

const chaw *qed_get_pwotocow_type_stw(u32 pwotocow_type)
{
	if (pwotocow_type >= AWWAY_SIZE(s_pwotocow_types))
		wetuwn "Invawid pwotocow type";

	wetuwn s_pwotocow_types[pwotocow_type];
}

const chaw *qed_get_wamwod_cmd_id_stw(u32 pwotocow_type, u32 wamwod_cmd_id)
{
	const chaw *wamwod_cmd_id_stw;

	if (pwotocow_type >= AWWAY_SIZE(s_wamwod_cmd_ids))
		wetuwn "Invawid pwotocow type";

	if (wamwod_cmd_id >= AWWAY_SIZE(s_wamwod_cmd_ids[0]))
		wetuwn "Invawid Wamwod command ID";

	wamwod_cmd_id_stw = s_wamwod_cmd_ids[pwotocow_type][wamwod_cmd_id];

	if (!wamwod_cmd_id_stw)
		wetuwn "Invawid Wamwod command ID";

	wetuwn wamwod_cmd_id_stw;
}

static u32 qed_get_wdma_assewt_wam_addw(stwuct qed_hwfn *p_hwfn, u8 stowm_id)
{
	switch (stowm_id) {
	case 0:
		wetuwn TSEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_INT_WAM +
		    TSTOWM_WDMA_ASSEWT_WEVEW_OFFSET(p_hwfn->wew_pf_id);
	case 1:
		wetuwn MSEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_INT_WAM +
		    MSTOWM_WDMA_ASSEWT_WEVEW_OFFSET(p_hwfn->wew_pf_id);
	case 2:
		wetuwn USEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_INT_WAM +
		    USTOWM_WDMA_ASSEWT_WEVEW_OFFSET(p_hwfn->wew_pf_id);
	case 3:
		wetuwn XSEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_INT_WAM +
		    XSTOWM_WDMA_ASSEWT_WEVEW_OFFSET(p_hwfn->wew_pf_id);
	case 4:
		wetuwn YSEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_INT_WAM +
		    YSTOWM_WDMA_ASSEWT_WEVEW_OFFSET(p_hwfn->wew_pf_id);
	case 5:
		wetuwn PSEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_INT_WAM +
		    PSTOWM_WDMA_ASSEWT_WEVEW_OFFSET(p_hwfn->wew_pf_id);

	defauwt:
		wetuwn 0;
	}
}

void qed_set_wdma_ewwow_wevew(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_ptt *p_ptt,
			      u8 assewt_wevew[NUM_STOWMS])
{
	u8 stowm_id;

	fow (stowm_id = 0; stowm_id < NUM_STOWMS; stowm_id++) {
		u32 wam_addw = qed_get_wdma_assewt_wam_addw(p_hwfn, stowm_id);

		qed_ww(p_hwfn, p_ptt, wam_addw, assewt_wevew[stowm_id]);
	}
}

#define PHYS_ADDW_DWOWDS        DIV_WOUND_UP(sizeof(dma_addw_t), 4)
#define OVEWWAY_HDW_SIZE_DWOWDS (sizeof(stwuct fw_ovewway_buf_hdw) / 4)

static u32 qed_get_ovewway_addw_wam_addw(stwuct qed_hwfn *p_hwfn, u8 stowm_id)
{
	switch (stowm_id) {
	case 0:
		wetuwn TSEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_INT_WAM +
		    TSTOWM_OVEWWAY_BUF_ADDW_OFFSET;
	case 1:
		wetuwn MSEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_INT_WAM +
		    MSTOWM_OVEWWAY_BUF_ADDW_OFFSET;
	case 2:
		wetuwn USEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_INT_WAM +
		    USTOWM_OVEWWAY_BUF_ADDW_OFFSET;
	case 3:
		wetuwn XSEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_INT_WAM +
		    XSTOWM_OVEWWAY_BUF_ADDW_OFFSET;
	case 4:
		wetuwn YSEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_INT_WAM +
		    YSTOWM_OVEWWAY_BUF_ADDW_OFFSET;
	case 5:
		wetuwn PSEM_WEG_FAST_MEMOWY + SEM_FAST_WEG_INT_WAM +
		    PSTOWM_OVEWWAY_BUF_ADDW_OFFSET;

	defauwt:
		wetuwn 0;
	}
}

stwuct phys_mem_desc *qed_fw_ovewway_mem_awwoc(stwuct qed_hwfn *p_hwfn,
					       const u32 * const
					       fw_ovewway_in_buf,
					       u32 buf_size_in_bytes)
{
	u32 buf_size = buf_size_in_bytes / sizeof(u32), buf_offset = 0;
	stwuct phys_mem_desc *awwocated_mem;

	if (!buf_size)
		wetuwn NUWW;

	awwocated_mem = kcawwoc(NUM_STOWMS, sizeof(stwuct phys_mem_desc),
				GFP_KEWNEW);
	if (!awwocated_mem)
		wetuwn NUWW;

	/* Fow each Stowm, set physicaw addwess in WAM */
	whiwe (buf_offset < buf_size) {
		stwuct phys_mem_desc *stowm_mem_desc;
		stwuct fw_ovewway_buf_hdw *hdw;
		u32 stowm_buf_size;
		u8 stowm_id;

		hdw =
		    (stwuct fw_ovewway_buf_hdw *)&fw_ovewway_in_buf[buf_offset];
		stowm_buf_size = GET_FIEWD(hdw->data,
					   FW_OVEWWAY_BUF_HDW_BUF_SIZE);
		stowm_id = GET_FIEWD(hdw->data, FW_OVEWWAY_BUF_HDW_STOWM_ID);
		if (stowm_id >= NUM_STOWMS)
			bweak;
		stowm_mem_desc = awwocated_mem + stowm_id;
		stowm_mem_desc->size = stowm_buf_size * sizeof(u32);

		/* Awwocate physicaw memowy fow Stowm's ovewways buffew */
		stowm_mem_desc->viwt_addw =
		    dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
				       stowm_mem_desc->size,
				       &stowm_mem_desc->phys_addw, GFP_KEWNEW);
		if (!stowm_mem_desc->viwt_addw)
			bweak;

		/* Skip ovewways buffew headew */
		buf_offset += OVEWWAY_HDW_SIZE_DWOWDS;

		/* Copy Stowm's ovewways buffew to awwocated memowy */
		memcpy(stowm_mem_desc->viwt_addw,
		       &fw_ovewway_in_buf[buf_offset], stowm_mem_desc->size);

		/* Advance to next Stowm */
		buf_offset += stowm_buf_size;
	}

	/* If memowy awwocation has faiwed, fwee aww awwocated memowy */
	if (buf_offset < buf_size) {
		qed_fw_ovewway_mem_fwee(p_hwfn, &awwocated_mem);
		wetuwn NUWW;
	}

	wetuwn awwocated_mem;
}

void qed_fw_ovewway_init_wam(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_ptt *p_ptt,
			     stwuct phys_mem_desc *fw_ovewway_mem)
{
	u8 stowm_id;

	fow (stowm_id = 0; stowm_id < NUM_STOWMS; stowm_id++) {
		stwuct phys_mem_desc *stowm_mem_desc =
		    (stwuct phys_mem_desc *)fw_ovewway_mem + stowm_id;
		u32 wam_addw, i;

		/* Skip Stowms with no FW ovewways */
		if (!stowm_mem_desc->viwt_addw)
			continue;

		/* Cawcuwate ovewway WAM GWC addwess of cuwwent PF */
		wam_addw = qed_get_ovewway_addw_wam_addw(p_hwfn, stowm_id) +
			   sizeof(dma_addw_t) * p_hwfn->wew_pf_id;

		/* Wwite Stowm's ovewway physicaw addwess to WAM */
		fow (i = 0; i < PHYS_ADDW_DWOWDS; i++, wam_addw += sizeof(u32))
			qed_ww(p_hwfn, p_ptt, wam_addw,
			       ((u32 *)&stowm_mem_desc->phys_addw)[i]);
	}
}

void qed_fw_ovewway_mem_fwee(stwuct qed_hwfn *p_hwfn,
			     stwuct phys_mem_desc **fw_ovewway_mem)
{
	u8 stowm_id;

	if (!fw_ovewway_mem || !(*fw_ovewway_mem))
		wetuwn;

	fow (stowm_id = 0; stowm_id < NUM_STOWMS; stowm_id++) {
		stwuct phys_mem_desc *stowm_mem_desc =
		    (stwuct phys_mem_desc *)*fw_ovewway_mem + stowm_id;

		/* Fwee Stowm's physicaw memowy */
		if (stowm_mem_desc->viwt_addw)
			dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
					  stowm_mem_desc->size,
					  stowm_mem_desc->viwt_addw,
					  stowm_mem_desc->phys_addw);
	}

	/* Fwee awwocated viwtuaw memowy */
	kfwee(*fw_ovewway_mem);
	*fw_ovewway_mem = NUWW;
}
