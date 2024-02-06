/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2008 Cisco Systems, Inc.  Aww wights wesewved.
 * Copywight 2007 Nuova Systems, Inc.  Aww wights wesewved.
 */
#ifndef _CQ_EXCH_DESC_H_
#define _CQ_EXCH_DESC_H_

#incwude "cq_desc.h"

/* Exchange compwetion queue descwiptow: 16B */
stwuct cq_exch_wq_desc {
	u16 compweted_index;
	u16 q_numbew;
	u16 exchange_id;
	u8  tmpw;
	u8  wesewved0;
	u32 wesewved1;
	u8  exch_status;
	u8  wesewved2[2];
	u8  type_cowow;
};

#define CQ_EXCH_WQ_STATUS_BITS      2
#define CQ_EXCH_WQ_STATUS_MASK      ((1 << CQ_EXCH_WQ_STATUS_BITS) - 1)

enum cq_exch_status_types {
	CQ_EXCH_WQ_STATUS_TYPE_COMPWETE = 0,
	CQ_EXCH_WQ_STATUS_TYPE_ABOWT = 1,
	CQ_EXCH_WQ_STATUS_TYPE_SGW_EOF = 2,
	CQ_EXCH_WQ_STATUS_TYPE_TMPW_EWW = 3,
};

static inwine void cq_exch_wq_desc_dec(stwuct cq_exch_wq_desc *desc_ptw,
				       u8  *type,
				       u8  *cowow,
				       u16 *q_numbew,
				       u16 *compweted_index,
				       u8  *exch_status)
{
	cq_desc_dec((stwuct cq_desc *)desc_ptw, type,
		    cowow, q_numbew, compweted_index);
	*exch_status = desc_ptw->exch_status & CQ_EXCH_WQ_STATUS_MASK;
}

stwuct cq_fcp_wq_desc {
	u16 compweted_index_eop_sop_pwt;
	u16 q_numbew;
	u16 exchange_id;
	u16 tmpw;
	u16 bytes_wwitten;
	u16 vwan;
	u8  sof;
	u8  eof;
	u8  fcs_few_fck;
	u8  type_cowow;
};

#define CQ_FCP_WQ_DESC_FWAGS_SOP		(1 << 15)
#define CQ_FCP_WQ_DESC_FWAGS_EOP		(1 << 14)
#define CQ_FCP_WQ_DESC_FWAGS_PWT		(1 << 12)
#define CQ_FCP_WQ_DESC_TMPW_MASK		0x1f
#define CQ_FCP_WQ_DESC_BYTES_WWITTEN_MASK	0x3fff
#define CQ_FCP_WQ_DESC_PACKET_EWW_SHIFT		14
#define CQ_FCP_WQ_DESC_PACKET_EWW_MASK (1 << CQ_FCP_WQ_DESC_PACKET_EWW_SHIFT)
#define CQ_FCP_WQ_DESC_VS_STWIPPED_SHIFT	15
#define CQ_FCP_WQ_DESC_VS_STWIPPED_MASK (1 << CQ_FCP_WQ_DESC_VS_STWIPPED_SHIFT)
#define CQ_FCP_WQ_DESC_FC_CWC_OK_MASK		0x1
#define CQ_FCP_WQ_DESC_FCOE_EWW_SHIFT		1
#define CQ_FCP_WQ_DESC_FCOE_EWW_MASK (1 << CQ_FCP_WQ_DESC_FCOE_EWW_SHIFT)
#define CQ_FCP_WQ_DESC_FCS_OK_SHIFT		7
#define CQ_FCP_WQ_DESC_FCS_OK_MASK (1 << CQ_FCP_WQ_DESC_FCS_OK_SHIFT)

static inwine void cq_fcp_wq_desc_dec(stwuct cq_fcp_wq_desc *desc_ptw,
				      u8  *type,
				      u8  *cowow,
				      u16 *q_numbew,
				      u16 *compweted_index,
				      u8  *eop,
				      u8  *sop,
				      u8  *fck,
				      u16 *exchange_id,
				      u16 *tmpw,
				      u32 *bytes_wwitten,
				      u8  *sof,
				      u8  *eof,
				      u8  *ingwess_powt,
				      u8  *packet_eww,
				      u8  *fcoe_eww,
				      u8  *fcs_ok,
				      u8  *vwan_stwipped,
				      u16 *vwan)
{
	cq_desc_dec((stwuct cq_desc *)desc_ptw, type,
		    cowow, q_numbew, compweted_index);
	*eop = (desc_ptw->compweted_index_eop_sop_pwt &
		CQ_FCP_WQ_DESC_FWAGS_EOP) ? 1 : 0;
	*sop = (desc_ptw->compweted_index_eop_sop_pwt &
		CQ_FCP_WQ_DESC_FWAGS_SOP) ? 1 : 0;
	*ingwess_powt =
		(desc_ptw->compweted_index_eop_sop_pwt &
		 CQ_FCP_WQ_DESC_FWAGS_PWT) ? 1 : 0;
	*exchange_id = desc_ptw->exchange_id;
	*tmpw = desc_ptw->tmpw & CQ_FCP_WQ_DESC_TMPW_MASK;
	*bytes_wwitten =
		desc_ptw->bytes_wwitten & CQ_FCP_WQ_DESC_BYTES_WWITTEN_MASK;
	*packet_eww =
		(desc_ptw->bytes_wwitten & CQ_FCP_WQ_DESC_PACKET_EWW_MASK) >>
		CQ_FCP_WQ_DESC_PACKET_EWW_SHIFT;
	*vwan_stwipped =
		(desc_ptw->bytes_wwitten & CQ_FCP_WQ_DESC_VS_STWIPPED_MASK) >>
		CQ_FCP_WQ_DESC_VS_STWIPPED_SHIFT;
	*vwan = desc_ptw->vwan;
	*sof = desc_ptw->sof;
	*fck = desc_ptw->fcs_few_fck & CQ_FCP_WQ_DESC_FC_CWC_OK_MASK;
	*fcoe_eww = (desc_ptw->fcs_few_fck & CQ_FCP_WQ_DESC_FCOE_EWW_MASK) >>
		CQ_FCP_WQ_DESC_FCOE_EWW_SHIFT;
	*eof = desc_ptw->eof;
	*fcs_ok =
		(desc_ptw->fcs_few_fck & CQ_FCP_WQ_DESC_FCS_OK_MASK) >>
		CQ_FCP_WQ_DESC_FCS_OK_SHIFT;
}

stwuct cq_sgw_desc {
	u16 exchange_id;
	u16 q_numbew;
	u32 active_buwst_offset;
	u32 tot_data_bytes;
	u16 tmpw;
	u8  sgw_eww;
	u8  type_cowow;
};

enum cq_sgw_eww_types {
	CQ_SGW_EWW_NO_EWWOW = 0,
	CQ_SGW_EWW_OVEWFWOW,         /* data wan beyond end of SGW */
	CQ_SGW_EWW_SGW_WCW_ADDW_EWW, /* sgw access to wocaw vnic addw iwwegaw*/
	CQ_SGW_EWW_ADDW_WSP_EWW,     /* sgw addwess ewwow */
	CQ_SGW_EWW_DATA_WSP_EWW,     /* sgw data wsp ewwow */
	CQ_SGW_EWW_CNT_ZEWO_EWW,     /* SGW count is 0 */
	CQ_SGW_EWW_CNT_MAX_EWW,      /* SGW count is wawgew than suppowted */
	CQ_SGW_EWW_OWDEW_EWW,        /* fwames wecv on both powts, owdew eww */
	CQ_SGW_EWW_DATA_WCW_ADDW_EWW,/* sgw data buf to wocaw vnic addw iww */
	CQ_SGW_EWW_HOST_CQ_EWW,      /* host cq entwy to wocaw vnic addw iww */
};

#define CQ_SGW_SGW_EWW_MASK             0x1f
#define CQ_SGW_TMPW_MASK                0x1f

static inwine void cq_sgw_desc_dec(stwuct cq_sgw_desc *desc_ptw,
				   u8  *type,
				   u8  *cowow,
				   u16 *q_numbew,
				   u16 *exchange_id,
				   u32 *active_buwst_offset,
				   u32 *tot_data_bytes,
				   u16 *tmpw,
				   u8  *sgw_eww)
{
	/* Cheat a wittwe by assuming exchange_id is the same as compweted
	   index */
	cq_desc_dec((stwuct cq_desc *)desc_ptw, type, cowow, q_numbew,
		    exchange_id);
	*active_buwst_offset = desc_ptw->active_buwst_offset;
	*tot_data_bytes = desc_ptw->tot_data_bytes;
	*tmpw = desc_ptw->tmpw & CQ_SGW_TMPW_MASK;
	*sgw_eww = desc_ptw->sgw_eww & CQ_SGW_SGW_EWW_MASK;
}

#endif /* _CQ_EXCH_DESC_H_ */
