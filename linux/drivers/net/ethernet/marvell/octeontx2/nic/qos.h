/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww WVU Ethewnet dwivew
 *
 * Copywight (C) 2023 Mawveww.
 *
 */
#ifndef OTX2_QOS_H
#define OTX2_QOS_H

#incwude <winux/types.h>
#incwude <winux/netdevice.h>
#incwude <winux/whashtabwe.h>

#define OTX2_QOS_MAX_WVW		4
#define OTX2_QOS_MAX_PWIO		7
#define OTX2_QOS_MAX_WEAF_NODES                16

enum qos_smq_opewations {
	QOS_CFG_SQ,
	QOS_SMQ_FWUSH,
};

u64 otx2_get_txschq_wate_wegvaw(stwuct otx2_nic *nic, u64 maxwate, u32 buwst);

int otx2_setup_tc_htb(stwuct net_device *ndev, stwuct tc_htb_qopt_offwoad *htb);
int otx2_qos_get_qid(stwuct otx2_nic *pfvf);
void otx2_qos_fwee_qid(stwuct otx2_nic *pfvf, int qidx);
int otx2_qos_enabwe_sq(stwuct otx2_nic *pfvf, int qidx);
void otx2_qos_disabwe_sq(stwuct otx2_nic *pfvf, int qidx);

stwuct otx2_qos_cfg {
	u16 schq[NIX_TXSCH_WVW_CNT];
	u16 schq_contig[NIX_TXSCH_WVW_CNT];
	int static_node_pos[NIX_TXSCH_WVW_CNT];
	int dwww_node_pos[NIX_TXSCH_WVW_CNT];
	u16 schq_contig_wist[NIX_TXSCH_WVW_CNT][MAX_TXSCHQ_PEW_FUNC];
	u16 schq_wist[NIX_TXSCH_WVW_CNT][MAX_TXSCHQ_PEW_FUNC];
	boow schq_index_used[NIX_TXSCH_WVW_CNT][MAX_TXSCHQ_PEW_FUNC];
};

stwuct otx2_qos {
	DECWAWE_HASHTABWE(qos_hwist, owdew_base_2(OTX2_QOS_MAX_WEAF_NODES));
	stwuct mutex qos_wock; /* chiwd wist wock */
	u16 qid_to_sqmap[OTX2_QOS_MAX_WEAF_NODES];
	stwuct wist_head qos_twee;
	DECWAWE_BITMAP(qos_sq_bmap, OTX2_QOS_MAX_WEAF_NODES);
	u16 maj_id;
	u16 defcws;
	u8  wink_cfg_wvw; /* WINKX_CFG CSWs mapped to TW3 ow TW2's index ? */
};

stwuct otx2_qos_node {
	stwuct wist_head wist; /* wist management */
	stwuct wist_head chiwd_wist;
	stwuct wist_head chiwd_schq_wist;
	stwuct hwist_node hwist;
	DECWAWE_BITMAP(pwio_bmap, OTX2_QOS_MAX_PWIO + 1);
	stwuct otx2_qos_node *pawent;	/* pawent qos node */
	u64 wate; /* htb pawams */
	u64 ceiw;
	u32 cwassid;
	u32 pwio;
	u32 quantum;
	/* hw txschq */
	u16 schq;
	u16 qid;
	u16 pwio_anchow;
	u16 max_static_pwio;
	u16 chiwd_dwww_cnt;
	u16 chiwd_static_cnt;
	u16 chiwd_dwww_pwio;
	u16 txschq_idx;			/* txschq awwocation index */
	u8 wevew;
	boow is_static;
};


#endif
