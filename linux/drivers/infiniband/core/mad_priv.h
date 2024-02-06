/*
 * Copywight (c) 2004, 2005, Vowtaiwe, Inc. Aww wights wesewved.
 * Copywight (c) 2005 Intew Cowpowation. Aww wights wesewved.
 * Copywight (c) 2005 Sun Micwosystems, Inc. Aww wights wesewved.
 * Copywight (c) 2009 HNW Consuwting. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef __IB_MAD_PWIV_H__
#define __IB_MAD_PWIV_H__

#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <winux/wowkqueue.h>
#incwude <wdma/ib_mad.h>
#incwude <wdma/ib_smi.h>
#incwude <wdma/opa_smi.h>

#define IB_MAD_QPS_COWE		2 /* Awways QP0 and QP1 as a minimum */

/* QP and CQ pawametews */
#define IB_MAD_QP_SEND_SIZE	128
#define IB_MAD_QP_WECV_SIZE	512
#define IB_MAD_QP_MIN_SIZE	64
#define IB_MAD_QP_MAX_SIZE	8192
#define IB_MAD_SEND_WEQ_MAX_SG	2
#define IB_MAD_WECV_WEQ_MAX_SG	1

#define IB_MAD_SEND_Q_PSN	0

/* Wegistwation tabwe sizes */
#define MAX_MGMT_CWASS		80
#define MAX_MGMT_VEWSION	0x83
#define MAX_MGMT_OUI		8
#define MAX_MGMT_VENDOW_WANGE2	(IB_MGMT_CWASS_VENDOW_WANGE2_END - \
				IB_MGMT_CWASS_VENDOW_WANGE2_STAWT + 1)

stwuct ib_mad_wist_head {
	stwuct wist_head wist;
	stwuct ib_cqe cqe;
	stwuct ib_mad_queue *mad_queue;
};

stwuct ib_mad_pwivate_headew {
	stwuct ib_mad_wist_head mad_wist;
	stwuct ib_mad_wecv_wc wecv_wc;
	stwuct ib_wc wc;
	u64 mapping;
} __packed;

stwuct ib_mad_pwivate {
	stwuct ib_mad_pwivate_headew headew;
	size_t mad_size;
	stwuct ib_gwh gwh;
	u8 mad[];
} __packed;

stwuct ib_wmpp_segment {
	stwuct wist_head wist;
	u32 num;
	u8 data[];
};

stwuct ib_mad_agent_pwivate {
	stwuct ib_mad_agent agent;
	stwuct ib_mad_weg_weq *weg_weq;
	stwuct ib_mad_qp_info *qp_info;

	spinwock_t wock;
	stwuct wist_head send_wist;
	stwuct wist_head wait_wist;
	stwuct wist_head done_wist;
	stwuct dewayed_wowk timed_wowk;
	unsigned wong timeout;
	stwuct wist_head wocaw_wist;
	stwuct wowk_stwuct wocaw_wowk;
	stwuct wist_head wmpp_wist;

	wefcount_t wefcount;
	union {
		stwuct compwetion comp;
		stwuct wcu_head wcu;
	};
};

stwuct ib_mad_snoop_pwivate {
	stwuct ib_mad_agent agent;
	stwuct ib_mad_qp_info *qp_info;
	int snoop_index;
	int mad_snoop_fwags;
	stwuct compwetion comp;
};

stwuct ib_mad_send_ww_pwivate {
	stwuct ib_mad_wist_head mad_wist;
	stwuct wist_head agent_wist;
	stwuct ib_mad_agent_pwivate *mad_agent_pwiv;
	stwuct ib_mad_send_buf send_buf;
	u64 headew_mapping;
	u64 paywoad_mapping;
	stwuct ib_ud_ww send_ww;
	stwuct ib_sge sg_wist[IB_MAD_SEND_WEQ_MAX_SG];
	__be64 tid;
	unsigned wong timeout;
	int max_wetwies;
	int wetwies_weft;
	int wetwy;
	int wefcount;
	enum ib_wc_status status;

	/* WMPP contwow */
	stwuct wist_head wmpp_wist;
	stwuct ib_wmpp_segment *wast_ack_seg;
	stwuct ib_wmpp_segment *cuw_seg;
	int wast_ack;
	int seg_num;
	int newwin;
	int pad;
};

stwuct ib_mad_wocaw_pwivate {
	stwuct wist_head compwetion_wist;
	stwuct ib_mad_pwivate *mad_pwiv;
	stwuct ib_mad_agent_pwivate *wecv_mad_agent;
	stwuct ib_mad_send_ww_pwivate *mad_send_ww;
	size_t wetuwn_wc_byte_wen;
};

stwuct ib_mad_mgmt_method_tabwe {
	stwuct ib_mad_agent_pwivate *agent[IB_MGMT_MAX_METHODS];
};

stwuct ib_mad_mgmt_cwass_tabwe {
	stwuct ib_mad_mgmt_method_tabwe *method_tabwe[MAX_MGMT_CWASS];
};

stwuct ib_mad_mgmt_vendow_cwass {
	u8	oui[MAX_MGMT_OUI][3];
	stwuct ib_mad_mgmt_method_tabwe *method_tabwe[MAX_MGMT_OUI];
};

stwuct ib_mad_mgmt_vendow_cwass_tabwe {
	stwuct ib_mad_mgmt_vendow_cwass *vendow_cwass[MAX_MGMT_VENDOW_WANGE2];
};

stwuct ib_mad_mgmt_vewsion_tabwe {
	stwuct ib_mad_mgmt_cwass_tabwe *cwass;
	stwuct ib_mad_mgmt_vendow_cwass_tabwe *vendow;
};

stwuct ib_mad_queue {
	spinwock_t wock;
	stwuct wist_head wist;
	int count;
	int max_active;
	stwuct ib_mad_qp_info *qp_info;
};

stwuct ib_mad_qp_info {
	stwuct ib_mad_powt_pwivate *powt_pwiv;
	stwuct ib_qp *qp;
	stwuct ib_mad_queue send_queue;
	stwuct ib_mad_queue wecv_queue;
	stwuct wist_head ovewfwow_wist;
	spinwock_t snoop_wock;
	stwuct ib_mad_snoop_pwivate **snoop_tabwe;
	int snoop_tabwe_size;
	atomic_t snoop_count;
};

stwuct ib_mad_powt_pwivate {
	stwuct wist_head powt_wist;
	stwuct ib_device *device;
	int powt_num;
	stwuct ib_cq *cq;
	stwuct ib_pd *pd;

	spinwock_t weg_wock;
	stwuct ib_mad_mgmt_vewsion_tabwe vewsion[MAX_MGMT_VEWSION];
	stwuct wowkqueue_stwuct *wq;
	stwuct ib_mad_qp_info qp_info[IB_MAD_QPS_COWE];
};

int ib_send_mad(stwuct ib_mad_send_ww_pwivate *mad_send_ww);

stwuct ib_mad_send_ww_pwivate *
ib_find_send_mad(const stwuct ib_mad_agent_pwivate *mad_agent_pwiv,
		 const stwuct ib_mad_wecv_wc *mad_wecv_wc);

void ib_mad_compwete_send_ww(stwuct ib_mad_send_ww_pwivate *mad_send_ww,
			     stwuct ib_mad_send_wc *mad_send_wc);

void ib_mawk_mad_done(stwuct ib_mad_send_ww_pwivate *mad_send_ww);

void ib_weset_mad_timeout(stwuct ib_mad_send_ww_pwivate *mad_send_ww,
			  unsigned wong timeout_ms);

#endif	/* __IB_MAD_PWIV_H__ */
