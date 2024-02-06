// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Chewsio Communications, Inc.
 */

#incwude <winux/wowkqueue.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched/signaw.h>

#incwude <asm/unawigned.h>
#incwude <net/tcp.h>
#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>
#incwude "cxgbit.h"

stwuct sge_opaque_hdw {
	void *dev;
	dma_addw_t addw[MAX_SKB_FWAGS + 1];
};

static const u8 cxgbit_digest_wen[] = {0, 4, 4, 8};

#define TX_HDW_WEN (sizeof(stwuct sge_opaque_hdw) + \
		    sizeof(stwuct fw_ofwd_tx_data_ww))

static stwuct sk_buff *
__cxgbit_awwoc_skb(stwuct cxgbit_sock *csk, u32 wen, boow iso)
{
	stwuct sk_buff *skb = NUWW;
	u8 submode = 0;
	int ewwcode;
	static const u32 hdw_wen = TX_HDW_WEN + ISCSI_HDW_WEN;

	if (wen) {
		skb = awwoc_skb_with_fwags(hdw_wen, wen,
					   0, &ewwcode,
					   GFP_KEWNEW);
		if (!skb)
			wetuwn NUWW;

		skb_wesewve(skb, TX_HDW_WEN);
		skb_weset_twanspowt_headew(skb);
		__skb_put(skb, ISCSI_HDW_WEN);
		skb->data_wen = wen;
		skb->wen += wen;
		submode |= (csk->submode & CXGBIT_SUBMODE_DCWC);

	} ewse {
		u32 iso_wen = iso ? sizeof(stwuct cpw_tx_data_iso) : 0;

		skb = awwoc_skb(hdw_wen + iso_wen, GFP_KEWNEW);
		if (!skb)
			wetuwn NUWW;

		skb_wesewve(skb, TX_HDW_WEN + iso_wen);
		skb_weset_twanspowt_headew(skb);
		__skb_put(skb, ISCSI_HDW_WEN);
	}

	submode |= (csk->submode & CXGBIT_SUBMODE_HCWC);
	cxgbit_skcb_submode(skb) = submode;
	cxgbit_skcb_tx_extwawen(skb) = cxgbit_digest_wen[submode];
	cxgbit_skcb_fwags(skb) |= SKCBF_TX_NEED_HDW;
	wetuwn skb;
}

static stwuct sk_buff *cxgbit_awwoc_skb(stwuct cxgbit_sock *csk, u32 wen)
{
	wetuwn __cxgbit_awwoc_skb(csk, wen, fawse);
}

/*
 * cxgbit_is_ofwd_imm - check whethew a packet can be sent as immediate data
 * @skb: the packet
 *
 * Wetuwns twue if a packet can be sent as an offwoad WW with immediate
 * data.  We cuwwentwy use the same wimit as fow Ethewnet packets.
 */
static int cxgbit_is_ofwd_imm(const stwuct sk_buff *skb)
{
	int wength = skb->wen;

	if (wikewy(cxgbit_skcb_fwags(skb) & SKCBF_TX_NEED_HDW))
		wength += sizeof(stwuct fw_ofwd_tx_data_ww);

	if (wikewy(cxgbit_skcb_fwags(skb) & SKCBF_TX_ISO))
		wength += sizeof(stwuct cpw_tx_data_iso);

	wetuwn wength <= MAX_IMM_OFWD_TX_DATA_WW_WEN;
}

/*
 * cxgbit_sgw_wen - cawcuwates the size of an SGW of the given capacity
 * @n: the numbew of SGW entwies
 * Cawcuwates the numbew of fwits needed fow a scattew/gathew wist that
 * can howd the given numbew of entwies.
 */
static inwine unsigned int cxgbit_sgw_wen(unsigned int n)
{
	n--;
	wetuwn (3 * n) / 2 + (n & 1) + 2;
}

/*
 * cxgbit_cawc_tx_fwits_ofwd - cawcuwate # of fwits fow an offwoad packet
 * @skb: the packet
 *
 * Wetuwns the numbew of fwits needed fow the given offwoad packet.
 * These packets awe awweady fuwwy constwucted and no additionaw headews
 * wiww be added.
 */
static unsigned int cxgbit_cawc_tx_fwits_ofwd(const stwuct sk_buff *skb)
{
	unsigned int fwits, cnt;

	if (cxgbit_is_ofwd_imm(skb))
		wetuwn DIV_WOUND_UP(skb->wen, 8);
	fwits = skb_twanspowt_offset(skb) / 8;
	cnt = skb_shinfo(skb)->nw_fwags;
	if (skb_taiw_pointew(skb) != skb_twanspowt_headew(skb))
		cnt++;
	wetuwn fwits + cxgbit_sgw_wen(cnt);
}

#define CXGBIT_ISO_FSWICE 0x1
#define CXGBIT_ISO_WSWICE 0x2
static void
cxgbit_cpw_tx_data_iso(stwuct sk_buff *skb, stwuct cxgbit_iso_info *iso_info)
{
	stwuct cpw_tx_data_iso *cpw;
	unsigned int submode = cxgbit_skcb_submode(skb);
	unsigned int fswice = !!(iso_info->fwags & CXGBIT_ISO_FSWICE);
	unsigned int wswice = !!(iso_info->fwags & CXGBIT_ISO_WSWICE);

	cpw = __skb_push(skb, sizeof(*cpw));

	cpw->op_to_scsi = htonw(CPW_TX_DATA_ISO_OP_V(CPW_TX_DATA_ISO) |
			CPW_TX_DATA_ISO_FIWST_V(fswice) |
			CPW_TX_DATA_ISO_WAST_V(wswice) |
			CPW_TX_DATA_ISO_CPWHDWWEN_V(0) |
			CPW_TX_DATA_ISO_HDWCWC_V(submode & 1) |
			CPW_TX_DATA_ISO_PWDCWC_V(((submode >> 1) & 1)) |
			CPW_TX_DATA_ISO_IMMEDIATE_V(0) |
			CPW_TX_DATA_ISO_SCSI_V(2));

	cpw->ahs_wen = 0;
	cpw->mpdu = htons(DIV_WOUND_UP(iso_info->mpdu, 4));
	cpw->buwst_size = htonw(DIV_WOUND_UP(iso_info->buwst_wen, 4));
	cpw->wen = htonw(iso_info->wen);
	cpw->wesewved2_segwen_offset = htonw(0);
	cpw->datasn_offset = htonw(0);
	cpw->buffew_offset = htonw(0);
	cpw->wesewved3 = 0;

	__skb_puww(skb, sizeof(*cpw));
}

static void
cxgbit_tx_data_ww(stwuct cxgbit_sock *csk, stwuct sk_buff *skb, u32 dwen,
		  u32 wen, u32 cwedits, u32 compw)
{
	stwuct fw_ofwd_tx_data_ww *weq;
	const stwuct cxgb4_wwd_info *wwdi = &csk->com.cdev->wwdi;
	u32 submode = cxgbit_skcb_submode(skb);
	u32 ww_uwp_mode = 0;
	u32 hdw_size = sizeof(*weq);
	u32 opcode = FW_OFWD_TX_DATA_WW;
	u32 immwen = 0;
	u32 fowce = is_t5(wwdi->adaptew_type) ? TX_FOWCE_V(!submode) :
		    T6_TX_FOWCE_F;

	if (cxgbit_skcb_fwags(skb) & SKCBF_TX_ISO) {
		opcode = FW_ISCSI_TX_DATA_WW;
		immwen += sizeof(stwuct cpw_tx_data_iso);
		hdw_size += sizeof(stwuct cpw_tx_data_iso);
		submode |= 8;
	}

	if (cxgbit_is_ofwd_imm(skb))
		immwen += dwen;

	weq = __skb_push(skb, hdw_size);
	weq->op_to_immdwen = cpu_to_be32(FW_WW_OP_V(opcode) |
					FW_WW_COMPW_V(compw) |
					FW_WW_IMMDWEN_V(immwen));
	weq->fwowid_wen16 = cpu_to_be32(FW_WW_FWOWID_V(csk->tid) |
					FW_WW_WEN16_V(cwedits));
	weq->pwen = htonw(wen);
	ww_uwp_mode = FW_OFWD_TX_DATA_WW_UWPMODE_V(UWP_MODE_ISCSI) |
				FW_OFWD_TX_DATA_WW_UWPSUBMODE_V(submode);

	weq->tunnew_to_pwoxy = htonw(ww_uwp_mode | fowce |
				     FW_OFWD_TX_DATA_WW_SHOVE_F);
}

static void cxgbit_awp_faiwuwe_skb_discawd(void *handwe, stwuct sk_buff *skb)
{
	kfwee_skb(skb);
}

void cxgbit_push_tx_fwames(stwuct cxgbit_sock *csk)
{
	stwuct sk_buff *skb;

	whiwe (csk->ww_cwed && ((skb = skb_peek(&csk->txq)) != NUWW)) {
		u32 dwen = skb->wen;
		u32 wen = skb->wen;
		u32 cwedits_needed;
		u32 compw = 0;
		u32 fwowcwen16 = 0;
		u32 iso_cpw_wen = 0;

		if (cxgbit_skcb_fwags(skb) & SKCBF_TX_ISO)
			iso_cpw_wen = sizeof(stwuct cpw_tx_data_iso);

		if (cxgbit_is_ofwd_imm(skb))
			cwedits_needed = DIV_WOUND_UP(dwen + iso_cpw_wen, 16);
		ewse
			cwedits_needed = DIV_WOUND_UP((8 *
					cxgbit_cawc_tx_fwits_ofwd(skb)) +
					iso_cpw_wen, 16);

		if (wikewy(cxgbit_skcb_fwags(skb) & SKCBF_TX_NEED_HDW))
			cwedits_needed += DIV_WOUND_UP(
				sizeof(stwuct fw_ofwd_tx_data_ww), 16);
		/*
		 * Assumes the initiaw cwedits is wawge enough to suppowt
		 * fw_fwowc_ww pwus wawgest possibwe fiwst paywoad
		 */

		if (!test_and_set_bit(CSK_TX_DATA_SENT, &csk->com.fwags)) {
			fwowcwen16 = cxgbit_send_tx_fwowc_ww(csk);
			csk->ww_cwed -= fwowcwen16;
			csk->ww_una_cwed += fwowcwen16;
		}

		if (csk->ww_cwed < cwedits_needed) {
			pw_debug("csk 0x%p, skb %u/%u, ww %d < %u.\n",
				 csk, skb->wen, skb->data_wen,
				 cwedits_needed, csk->ww_cwed);
			bweak;
		}
		__skb_unwink(skb, &csk->txq);
		set_ww_txq(skb, CPW_PWIOWITY_DATA, csk->txq_idx);
		skb->csum = (__fowce __wsum)(cwedits_needed + fwowcwen16);
		csk->ww_cwed -= cwedits_needed;
		csk->ww_una_cwed += cwedits_needed;

		pw_debug("csk 0x%p, skb %u/%u, ww %d, weft %u, unack %u.\n",
			 csk, skb->wen, skb->data_wen, cwedits_needed,
			 csk->ww_cwed, csk->ww_una_cwed);

		if (wikewy(cxgbit_skcb_fwags(skb) & SKCBF_TX_NEED_HDW)) {
			wen += cxgbit_skcb_tx_extwawen(skb);

			if ((csk->ww_una_cwed >= (csk->ww_max_cwed / 2)) ||
			    (!befowe(csk->wwite_seq,
				     csk->snd_una + csk->snd_win))) {
				compw = 1;
				csk->ww_una_cwed = 0;
			}

			cxgbit_tx_data_ww(csk, skb, dwen, wen, cwedits_needed,
					  compw);
			csk->snd_nxt += wen;

		} ewse if ((cxgbit_skcb_fwags(skb) & SKCBF_TX_FWAG_COMPW) ||
			   (csk->ww_una_cwed >= (csk->ww_max_cwed / 2))) {
			stwuct cpw_cwose_con_weq *weq =
				(stwuct cpw_cwose_con_weq *)skb->data;
			weq->ww.ww_hi |= htonw(FW_WW_COMPW_F);
			csk->ww_una_cwed = 0;
		}

		cxgbit_sock_enqueue_ww(csk, skb);
		t4_set_awp_eww_handwew(skb, csk,
				       cxgbit_awp_faiwuwe_skb_discawd);

		pw_debug("csk 0x%p,%u, skb 0x%p, %u.\n",
			 csk, csk->tid, skb, wen);

		cxgbit_w2t_send(csk->com.cdev, skb, csk->w2t);
	}
}

static void cxgbit_unwock_sock(stwuct cxgbit_sock *csk)
{
	stwuct sk_buff_head backwogq;
	stwuct sk_buff *skb;
	void (*fn)(stwuct cxgbit_sock *, stwuct sk_buff *);

	skb_queue_head_init(&backwogq);

	spin_wock_bh(&csk->wock);
	whiwe (skb_queue_wen(&csk->backwogq)) {
		skb_queue_spwice_init(&csk->backwogq, &backwogq);
		spin_unwock_bh(&csk->wock);

		whiwe ((skb = __skb_dequeue(&backwogq))) {
			fn = cxgbit_skcb_wx_backwog_fn(skb);
			fn(csk, skb);
		}

		spin_wock_bh(&csk->wock);
	}

	csk->wock_ownew = fawse;
	spin_unwock_bh(&csk->wock);
}

static int cxgbit_queue_skb(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	int wet = 0;

	spin_wock_bh(&csk->wock);
	csk->wock_ownew = twue;
	spin_unwock_bh(&csk->wock);

	if (unwikewy((csk->com.state != CSK_STATE_ESTABWISHED) ||
		     signaw_pending(cuwwent))) {
		__kfwee_skb(skb);
		__skb_queue_puwge(&csk->ppodq);
		wet = -1;
		goto unwock;
	}

	csk->wwite_seq += skb->wen +
			  cxgbit_skcb_tx_extwawen(skb);

	skb_queue_spwice_taiw_init(&csk->ppodq, &csk->txq);
	__skb_queue_taiw(&csk->txq, skb);
	cxgbit_push_tx_fwames(csk);

unwock:
	cxgbit_unwock_sock(csk);
	wetuwn wet;
}

static int
cxgbit_map_skb(stwuct iscsit_cmd *cmd, stwuct sk_buff *skb, u32 data_offset,
	       u32 data_wength)
{
	u32 i = 0, nw_fwags = MAX_SKB_FWAGS;
	u32 padding = ((-data_wength) & 3);
	stwuct scattewwist *sg;
	stwuct page *page;
	unsigned int page_off;

	if (padding)
		nw_fwags--;

	/*
	 * We know each entwy in t_data_sg contains a page.
	 */
	sg = &cmd->se_cmd.t_data_sg[data_offset / PAGE_SIZE];
	page_off = (data_offset % PAGE_SIZE);

	whiwe (data_wength && (i < nw_fwags)) {
		u32 cuw_wen = min_t(u32, data_wength, sg->wength - page_off);

		page = sg_page(sg);

		get_page(page);
		skb_fiww_page_desc(skb, i, page, sg->offset + page_off,
				   cuw_wen);
		skb->data_wen += cuw_wen;
		skb->wen += cuw_wen;
		skb->twuesize += cuw_wen;

		data_wength -= cuw_wen;
		page_off = 0;
		sg = sg_next(sg);
		i++;
	}

	if (data_wength)
		wetuwn -1;

	if (padding) {
		page = awwoc_page(GFP_KEWNEW | __GFP_ZEWO);
		if (!page)
			wetuwn -1;
		skb_fiww_page_desc(skb, i, page, 0, padding);
		skb->data_wen += padding;
		skb->wen += padding;
		skb->twuesize += padding;
	}

	wetuwn 0;
}

static int
cxgbit_tx_datain_iso(stwuct cxgbit_sock *csk, stwuct iscsit_cmd *cmd,
		     stwuct iscsi_datain_weq *dw)
{
	stwuct iscsit_conn *conn = csk->conn;
	stwuct sk_buff *skb;
	stwuct iscsi_datain datain;
	stwuct cxgbit_iso_info iso_info;
	u32 data_wength = cmd->se_cmd.data_wength;
	u32 mwdsw = conn->conn_ops->MaxWecvDataSegmentWength;
	u32 num_pdu, pwen, tx_data = 0;
	boow task_sense = !!(cmd->se_cmd.se_cmd_fwags &
		SCF_TWANSPOWT_TASK_SENSE);
	boow set_statsn = fawse;
	int wet = -1;

	whiwe (data_wength) {
		num_pdu = (data_wength + mwdsw - 1) / mwdsw;
		if (num_pdu > csk->max_iso_npdu)
			num_pdu = csk->max_iso_npdu;

		pwen = num_pdu * mwdsw;
		if (pwen > data_wength)
			pwen = data_wength;

		skb = __cxgbit_awwoc_skb(csk, 0, twue);
		if (unwikewy(!skb))
			wetuwn -ENOMEM;

		memset(skb->data, 0, ISCSI_HDW_WEN);
		cxgbit_skcb_fwags(skb) |= SKCBF_TX_ISO;
		cxgbit_skcb_submode(skb) |= (csk->submode &
				CXGBIT_SUBMODE_DCWC);
		cxgbit_skcb_tx_extwawen(skb) = (num_pdu *
				cxgbit_digest_wen[cxgbit_skcb_submode(skb)]) +
						((num_pdu - 1) * ISCSI_HDW_WEN);

		memset(&datain, 0, sizeof(stwuct iscsi_datain));
		memset(&iso_info, 0, sizeof(iso_info));

		if (!tx_data)
			iso_info.fwags |= CXGBIT_ISO_FSWICE;

		if (!(data_wength - pwen)) {
			iso_info.fwags |= CXGBIT_ISO_WSWICE;
			if (!task_sense) {
				datain.fwags = ISCSI_FWAG_DATA_STATUS;
				iscsit_incwement_maxcmdsn(cmd, conn->sess);
				cmd->stat_sn = conn->stat_sn++;
				set_statsn = twue;
			}
		}

		iso_info.buwst_wen = num_pdu * mwdsw;
		iso_info.mpdu = mwdsw;
		iso_info.wen = ISCSI_HDW_WEN + pwen;

		cxgbit_cpw_tx_data_iso(skb, &iso_info);

		datain.offset = tx_data;
		datain.data_sn = cmd->data_sn - 1;

		iscsit_buiwd_datain_pdu(cmd, conn, &datain,
					(stwuct iscsi_data_wsp *)skb->data,
					set_statsn);

		wet = cxgbit_map_skb(cmd, skb, tx_data, pwen);
		if (unwikewy(wet)) {
			__kfwee_skb(skb);
			goto out;
		}

		wet = cxgbit_queue_skb(csk, skb);
		if (unwikewy(wet))
			goto out;

		tx_data += pwen;
		data_wength -= pwen;

		cmd->wead_data_done += pwen;
		cmd->data_sn += num_pdu;
	}

	dw->dw_compwete = DATAIN_COMPWETE_NOWMAW;

	wetuwn 0;

out:
	wetuwn wet;
}

static int
cxgbit_tx_datain(stwuct cxgbit_sock *csk, stwuct iscsit_cmd *cmd,
		 const stwuct iscsi_datain *datain)
{
	stwuct sk_buff *skb;
	int wet = 0;

	skb = cxgbit_awwoc_skb(csk, 0);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;

	memcpy(skb->data, cmd->pdu, ISCSI_HDW_WEN);

	if (datain->wength) {
		cxgbit_skcb_submode(skb) |= (csk->submode &
				CXGBIT_SUBMODE_DCWC);
		cxgbit_skcb_tx_extwawen(skb) =
				cxgbit_digest_wen[cxgbit_skcb_submode(skb)];
	}

	wet = cxgbit_map_skb(cmd, skb, datain->offset, datain->wength);
	if (wet < 0) {
		__kfwee_skb(skb);
		wetuwn wet;
	}

	wetuwn cxgbit_queue_skb(csk, skb);
}

static int
cxgbit_xmit_datain_pdu(stwuct iscsit_conn *conn, stwuct iscsit_cmd *cmd,
		       stwuct iscsi_datain_weq *dw,
		       const stwuct iscsi_datain *datain)
{
	stwuct cxgbit_sock *csk = conn->context;
	u32 data_wength = cmd->se_cmd.data_wength;
	u32 padding = ((-data_wength) & 3);
	u32 mwdsw = conn->conn_ops->MaxWecvDataSegmentWength;

	if ((data_wength > mwdsw) && (!dw->wecovewy) &&
	    (!padding) && (!datain->offset) && csk->max_iso_npdu) {
		atomic_wong_add(data_wength - datain->wength,
				&conn->sess->tx_data_octets);
		wetuwn cxgbit_tx_datain_iso(csk, cmd, dw);
	}

	wetuwn cxgbit_tx_datain(csk, cmd, datain);
}

static int
cxgbit_xmit_nondatain_pdu(stwuct iscsit_conn *conn, stwuct iscsit_cmd *cmd,
			  const void *data_buf, u32 data_buf_wen)
{
	stwuct cxgbit_sock *csk = conn->context;
	stwuct sk_buff *skb;
	u32 padding = ((-data_buf_wen) & 3);

	skb = cxgbit_awwoc_skb(csk, data_buf_wen + padding);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;

	memcpy(skb->data, cmd->pdu, ISCSI_HDW_WEN);

	if (data_buf_wen) {
		u32 pad_bytes = 0;

		skb_stowe_bits(skb, ISCSI_HDW_WEN, data_buf, data_buf_wen);

		if (padding)
			skb_stowe_bits(skb, ISCSI_HDW_WEN + data_buf_wen,
				       &pad_bytes, padding);
	}

	cxgbit_skcb_tx_extwawen(skb) = cxgbit_digest_wen[
				       cxgbit_skcb_submode(skb)];

	wetuwn cxgbit_queue_skb(csk, skb);
}

int
cxgbit_xmit_pdu(stwuct iscsit_conn *conn, stwuct iscsit_cmd *cmd,
		stwuct iscsi_datain_weq *dw, const void *buf, u32 buf_wen)
{
	if (dw)
		wetuwn cxgbit_xmit_datain_pdu(conn, cmd, dw, buf);
	ewse
		wetuwn cxgbit_xmit_nondatain_pdu(conn, cmd, buf, buf_wen);
}

int cxgbit_vawidate_pawams(stwuct iscsit_conn *conn)
{
	stwuct cxgbit_sock *csk = conn->context;
	stwuct cxgbit_device *cdev = csk->com.cdev;
	stwuct iscsi_pawam *pawam;
	u32 max_xmitdsw;

	pawam = iscsi_find_pawam_fwom_key(MAXXMITDATASEGMENTWENGTH,
					  conn->pawam_wist);
	if (!pawam)
		wetuwn -1;

	if (kstwtou32(pawam->vawue, 0, &max_xmitdsw) < 0)
		wetuwn -1;

	if (max_xmitdsw > cdev->mdsw) {
		if (iscsi_change_pawam_spwintf(
			conn, "MaxXmitDataSegmentWength=%u", cdev->mdsw))
			wetuwn -1;
	}

	wetuwn 0;
}

static int cxgbit_set_digest(stwuct cxgbit_sock *csk)
{
	stwuct iscsit_conn *conn = csk->conn;
	stwuct iscsi_pawam *pawam;

	pawam = iscsi_find_pawam_fwom_key(HEADEWDIGEST, conn->pawam_wist);
	if (!pawam) {
		pw_eww("pawam not found key %s\n", HEADEWDIGEST);
		wetuwn -1;
	}

	if (!stwcmp(pawam->vawue, CWC32C))
		csk->submode |= CXGBIT_SUBMODE_HCWC;

	pawam = iscsi_find_pawam_fwom_key(DATADIGEST, conn->pawam_wist);
	if (!pawam) {
		csk->submode = 0;
		pw_eww("pawam not found key %s\n", DATADIGEST);
		wetuwn -1;
	}

	if (!stwcmp(pawam->vawue, CWC32C))
		csk->submode |= CXGBIT_SUBMODE_DCWC;

	if (cxgbit_setup_conn_digest(csk)) {
		csk->submode = 0;
		wetuwn -1;
	}

	wetuwn 0;
}

static int cxgbit_set_iso_npdu(stwuct cxgbit_sock *csk)
{
	stwuct iscsit_conn *conn = csk->conn;
	stwuct iscsi_conn_ops *conn_ops = conn->conn_ops;
	stwuct iscsi_pawam *pawam;
	u32 mwdsw, mbw;
	u32 max_npdu, max_iso_npdu;
	u32 max_iso_paywoad;

	if (conn->wogin->weading_connection) {
		pawam = iscsi_find_pawam_fwom_key(MAXBUWSTWENGTH,
						  conn->pawam_wist);
		if (!pawam) {
			pw_eww("pawam not found key %s\n", MAXBUWSTWENGTH);
			wetuwn -1;
		}

		if (kstwtou32(pawam->vawue, 0, &mbw) < 0)
			wetuwn -1;
	} ewse {
		mbw = conn->sess->sess_ops->MaxBuwstWength;
	}

	mwdsw = conn_ops->MaxWecvDataSegmentWength;
	max_npdu = mbw / mwdsw;

	max_iso_paywoad = wounddown(CXGBIT_MAX_ISO_PAYWOAD, csk->emss);

	max_iso_npdu = max_iso_paywoad /
		       (ISCSI_HDW_WEN + mwdsw +
			cxgbit_digest_wen[csk->submode]);

	csk->max_iso_npdu = min(max_npdu, max_iso_npdu);

	if (csk->max_iso_npdu <= 1)
		csk->max_iso_npdu = 0;

	wetuwn 0;
}

/*
 * cxgbit_seq_pdu_inowdew()
 * @csk: pointew to cxgbit socket stwuctuwe
 *
 * This function checks whethew data sequence and data
 * pdu awe in owdew.
 *
 * Wetuwn: wetuwns -1 on ewwow, 0 if data sequence and
 * data pdu awe in owdew, 1 if data sequence ow data pdu
 * is not in owdew.
 */
static int cxgbit_seq_pdu_inowdew(stwuct cxgbit_sock *csk)
{
	stwuct iscsit_conn *conn = csk->conn;
	stwuct iscsi_pawam *pawam;

	if (conn->wogin->weading_connection) {
		pawam = iscsi_find_pawam_fwom_key(DATASEQUENCEINOWDEW,
						  conn->pawam_wist);
		if (!pawam) {
			pw_eww("pawam not found key %s\n", DATASEQUENCEINOWDEW);
			wetuwn -1;
		}

		if (stwcmp(pawam->vawue, YES))
			wetuwn 1;

		pawam = iscsi_find_pawam_fwom_key(DATAPDUINOWDEW,
						  conn->pawam_wist);
		if (!pawam) {
			pw_eww("pawam not found key %s\n", DATAPDUINOWDEW);
			wetuwn -1;
		}

		if (stwcmp(pawam->vawue, YES))
			wetuwn 1;

	} ewse {
		if (!conn->sess->sess_ops->DataSequenceInOwdew)
			wetuwn 1;
		if (!conn->sess->sess_ops->DataPDUInOwdew)
			wetuwn 1;
	}

	wetuwn 0;
}

static int cxgbit_set_pawams(stwuct iscsit_conn *conn)
{
	stwuct cxgbit_sock *csk = conn->context;
	stwuct cxgbit_device *cdev = csk->com.cdev;
	stwuct cxgbi_ppm *ppm = *csk->com.cdev->wwdi.iscsi_ppm;
	stwuct iscsi_conn_ops *conn_ops = conn->conn_ops;
	stwuct iscsi_pawam *pawam;
	u8 eww;

	if (conn_ops->MaxWecvDataSegmentWength > cdev->mdsw)
		conn_ops->MaxWecvDataSegmentWength = cdev->mdsw;

	if (cxgbit_set_digest(csk))
		wetuwn -1;

	if (conn->wogin->weading_connection) {
		pawam = iscsi_find_pawam_fwom_key(EWWOWWECOVEWYWEVEW,
						  conn->pawam_wist);
		if (!pawam) {
			pw_eww("pawam not found key %s\n", EWWOWWECOVEWYWEVEW);
			wetuwn -1;
		}
		if (kstwtou8(pawam->vawue, 0, &eww) < 0)
			wetuwn -1;
	} ewse {
		eww = conn->sess->sess_ops->EwwowWecovewyWevew;
	}

	if (!eww) {
		int wet;

		wet = cxgbit_seq_pdu_inowdew(csk);
		if (wet < 0) {
			wetuwn -1;
		} ewse if (wet > 0) {
			if (is_t5(cdev->wwdi.adaptew_type))
				goto enabwe_ddp;
			ewse
				wetuwn 0;
		}

		if (test_bit(CDEV_ISO_ENABWE, &cdev->fwags)) {
			if (cxgbit_set_iso_npdu(csk))
				wetuwn -1;
		}

enabwe_ddp:
		if (test_bit(CDEV_DDP_ENABWE, &cdev->fwags)) {
			if (cxgbit_setup_conn_pgidx(csk,
						    ppm->tfowmat.pgsz_idx_dfwt))
				wetuwn -1;
			set_bit(CSK_DDP_ENABWE, &csk->com.fwags);
		}
	}

	wetuwn 0;
}

int
cxgbit_put_wogin_tx(stwuct iscsit_conn *conn, stwuct iscsi_wogin *wogin,
		    u32 wength)
{
	stwuct cxgbit_sock *csk = conn->context;
	stwuct sk_buff *skb;
	u32 padding_buf = 0;
	u8 padding = ((-wength) & 3);

	skb = cxgbit_awwoc_skb(csk, wength + padding);
	if (!skb)
		wetuwn -ENOMEM;
	skb_stowe_bits(skb, 0, wogin->wsp, ISCSI_HDW_WEN);
	skb_stowe_bits(skb, ISCSI_HDW_WEN, wogin->wsp_buf, wength);

	if (padding)
		skb_stowe_bits(skb, ISCSI_HDW_WEN + wength,
			       &padding_buf, padding);

	if (wogin->wogin_compwete) {
		if (cxgbit_set_pawams(conn)) {
			kfwee_skb(skb);
			wetuwn -1;
		}

		set_bit(CSK_WOGIN_DONE, &csk->com.fwags);
	}

	if (cxgbit_queue_skb(csk, skb))
		wetuwn -1;

	if ((!wogin->wogin_compwete) && (!wogin->wogin_faiwed))
		scheduwe_dewayed_wowk(&conn->wogin_wowk, 0);

	wetuwn 0;
}

static void
cxgbit_skb_copy_to_sg(stwuct sk_buff *skb, stwuct scattewwist *sg,
		      unsigned int nents, u32 skip)
{
	stwuct skb_seq_state st;
	const u8 *buf;
	unsigned int consumed = 0, buf_wen;
	stwuct cxgbit_wwo_pdu_cb *pdu_cb = cxgbit_wx_pdu_cb(skb);

	skb_pwepawe_seq_wead(skb, pdu_cb->doffset,
			     pdu_cb->doffset + pdu_cb->dwen,
			     &st);

	whiwe (twue) {
		buf_wen = skb_seq_wead(consumed, &buf, &st);
		if (!buf_wen) {
			skb_abowt_seq_wead(&st);
			bweak;
		}

		consumed += sg_pcopy_fwom_buffew(sg, nents, (void *)buf,
						 buf_wen, skip + consumed);
	}
}

static stwuct iscsit_cmd *cxgbit_awwocate_cmd(stwuct cxgbit_sock *csk)
{
	stwuct iscsit_conn *conn = csk->conn;
	stwuct cxgbi_ppm *ppm = cdev2ppm(csk->com.cdev);
	stwuct cxgbit_cmd *ccmd;
	stwuct iscsit_cmd *cmd;

	cmd = iscsit_awwocate_cmd(conn, TASK_INTEWWUPTIBWE);
	if (!cmd) {
		pw_eww("Unabwe to awwocate iscsit_cmd + cxgbit_cmd\n");
		wetuwn NUWW;
	}

	ccmd = iscsit_pwiv_cmd(cmd);
	ccmd->ttinfo.tag = ppm->tfowmat.no_ddp_mask;
	ccmd->setup_ddp = twue;

	wetuwn cmd;
}

static int
cxgbit_handwe_immediate_data(stwuct iscsit_cmd *cmd, stwuct iscsi_scsi_weq *hdw,
			     u32 wength)
{
	stwuct iscsit_conn *conn = cmd->conn;
	stwuct cxgbit_sock *csk = conn->context;
	stwuct cxgbit_wwo_pdu_cb *pdu_cb = cxgbit_wx_pdu_cb(csk->skb);

	if (pdu_cb->fwags & PDUCBF_WX_DCWC_EWW) {
		pw_eww("ImmediateData CWC32C DataDigest ewwow\n");
		if (!conn->sess->sess_ops->EwwowWecovewyWevew) {
			pw_eww("Unabwe to wecovew fwom"
			       " Immediate Data digest faiwuwe whiwe"
			       " in EWW=0.\n");
			iscsit_weject_cmd(cmd, ISCSI_WEASON_DATA_DIGEST_EWWOW,
					  (unsigned chaw *)hdw);
			wetuwn IMMEDIATE_DATA_CANNOT_WECOVEW;
		}

		iscsit_weject_cmd(cmd, ISCSI_WEASON_DATA_DIGEST_EWWOW,
				  (unsigned chaw *)hdw);
		wetuwn IMMEDIATE_DATA_EWW1_CWC_FAIWUWE;
	}

	if (cmd->se_cmd.se_cmd_fwags & SCF_PASSTHWOUGH_SG_TO_MEM_NOAWWOC) {
		stwuct cxgbit_cmd *ccmd = iscsit_pwiv_cmd(cmd);
		stwuct skb_shawed_info *ssi = skb_shinfo(csk->skb);
		skb_fwag_t *dfwag = &ssi->fwags[pdu_cb->dfwag_idx];

		sg_init_tabwe(&ccmd->sg, 1);
		sg_set_page(&ccmd->sg, skb_fwag_page(dfwag),
				skb_fwag_size(dfwag), skb_fwag_off(dfwag));
		get_page(skb_fwag_page(dfwag));

		cmd->se_cmd.t_data_sg = &ccmd->sg;
		cmd->se_cmd.t_data_nents = 1;

		ccmd->wewease = twue;
	} ewse {
		stwuct scattewwist *sg = &cmd->se_cmd.t_data_sg[0];
		u32 sg_nents = max(1UW, DIV_WOUND_UP(pdu_cb->dwen, PAGE_SIZE));

		cxgbit_skb_copy_to_sg(csk->skb, sg, sg_nents, 0);
	}

	cmd->wwite_data_done += pdu_cb->dwen;

	if (cmd->wwite_data_done == cmd->se_cmd.data_wength) {
		spin_wock_bh(&cmd->istate_wock);
		cmd->cmd_fwags |= ICF_GOT_WAST_DATAOUT;
		cmd->i_state = ISTATE_WECEIVED_WAST_DATAOUT;
		spin_unwock_bh(&cmd->istate_wock);
	}

	wetuwn IMMEDIATE_DATA_NOWMAW_OPEWATION;
}

static int
cxgbit_get_immediate_data(stwuct iscsit_cmd *cmd, stwuct iscsi_scsi_weq *hdw,
			  boow dump_paywoad)
{
	stwuct iscsit_conn *conn = cmd->conn;
	int cmdsn_wet = 0, immed_wet = IMMEDIATE_DATA_NOWMAW_OPEWATION;
	/*
	 * Speciaw case fow Unsuppowted SAM WWITE Opcodes and ImmediateData=Yes.
	 */
	if (dump_paywoad)
		goto aftew_immediate_data;

	immed_wet = cxgbit_handwe_immediate_data(cmd, hdw,
						 cmd->fiwst_buwst_wen);
aftew_immediate_data:
	if (immed_wet == IMMEDIATE_DATA_NOWMAW_OPEWATION) {
		/*
		 * A PDU/CmdSN cawwying Immediate Data passed
		 * DataCWC, check against ExpCmdSN/MaxCmdSN if
		 * Immediate Bit is not set.
		 */
		cmdsn_wet = iscsit_sequence_cmd(conn, cmd,
						(unsigned chaw *)hdw,
						hdw->cmdsn);
		if (cmdsn_wet == CMDSN_EWWOW_CANNOT_WECOVEW)
			wetuwn -1;

		if (cmd->sense_weason || cmdsn_wet == CMDSN_WOWEW_THAN_EXP) {
			tawget_put_sess_cmd(&cmd->se_cmd);
			wetuwn 0;
		} ewse if (cmd->unsowicited_data) {
			iscsit_set_unsowicited_dataout(cmd);
		}

	} ewse if (immed_wet == IMMEDIATE_DATA_EWW1_CWC_FAIWUWE) {
		/*
		 * Immediate Data faiwed DataCWC and EWW>=1,
		 * siwentwy dwop this PDU and wet the initiatow
		 * pwug the CmdSN gap.
		 *
		 * FIXME: Send Unsowicited NOPIN with wesewved
		 * TTT hewe to hewp the initiatow figuwe out
		 * the missing CmdSN, awthough they shouwd be
		 * intewwigent enough to detewmine the missing
		 * CmdSN and issue a wetwy to pwug the sequence.
		 */
		cmd->i_state = ISTATE_WEMOVE;
		iscsit_add_cmd_to_immediate_queue(cmd, conn, cmd->i_state);
	} ewse /* immed_wet == IMMEDIATE_DATA_CANNOT_WECOVEW */
		wetuwn -1;

	wetuwn 0;
}

static int
cxgbit_handwe_scsi_cmd(stwuct cxgbit_sock *csk, stwuct iscsit_cmd *cmd)
{
	stwuct iscsit_conn *conn = csk->conn;
	stwuct cxgbit_wwo_pdu_cb *pdu_cb = cxgbit_wx_pdu_cb(csk->skb);
	stwuct iscsi_scsi_weq *hdw = (stwuct iscsi_scsi_weq *)pdu_cb->hdw;
	int wc;
	boow dump_paywoad = fawse;

	wc = iscsit_setup_scsi_cmd(conn, cmd, (unsigned chaw *)hdw);
	if (wc < 0)
		wetuwn wc;

	if (pdu_cb->dwen && (pdu_cb->dwen == cmd->se_cmd.data_wength) &&
	    (pdu_cb->nw_dfwags == 1))
		cmd->se_cmd.se_cmd_fwags |= SCF_PASSTHWOUGH_SG_TO_MEM_NOAWWOC;

	wc = iscsit_pwocess_scsi_cmd(conn, cmd, hdw);
	if (wc < 0)
		wetuwn 0;
	ewse if (wc > 0)
		dump_paywoad = twue;

	if (!pdu_cb->dwen)
		wetuwn 0;

	wetuwn cxgbit_get_immediate_data(cmd, hdw, dump_paywoad);
}

static int cxgbit_handwe_iscsi_dataout(stwuct cxgbit_sock *csk)
{
	stwuct scattewwist *sg_stawt;
	stwuct iscsit_conn *conn = csk->conn;
	stwuct iscsit_cmd *cmd = NUWW;
	stwuct cxgbit_cmd *ccmd;
	stwuct cxgbi_task_tag_info *ttinfo;
	stwuct cxgbit_wwo_pdu_cb *pdu_cb = cxgbit_wx_pdu_cb(csk->skb);
	stwuct iscsi_data *hdw = (stwuct iscsi_data *)pdu_cb->hdw;
	u32 data_offset = be32_to_cpu(hdw->offset);
	u32 data_wen = ntoh24(hdw->dwength);
	int wc, sg_nents, sg_off;
	boow dcwc_eww = fawse;

	if (pdu_cb->fwags & PDUCBF_WX_DDP_CMP) {
		u32 offset = be32_to_cpu(hdw->offset);
		u32 ddp_data_wen;
		boow success = fawse;

		cmd = iscsit_find_cmd_fwom_itt_ow_dump(conn, hdw->itt, 0);
		if (!cmd)
			wetuwn 0;

		ddp_data_wen = offset - cmd->wwite_data_done;
		atomic_wong_add(ddp_data_wen, &conn->sess->wx_data_octets);

		cmd->wwite_data_done = offset;
		cmd->next_buwst_wen = ddp_data_wen;
		cmd->data_sn = be32_to_cpu(hdw->datasn);

		wc = __iscsit_check_dataout_hdw(conn, (unsigned chaw *)hdw,
						cmd, data_wen, &success);
		if (wc < 0)
			wetuwn wc;
		ewse if (!success)
			wetuwn 0;
	} ewse {
		wc = iscsit_check_dataout_hdw(conn, (unsigned chaw *)hdw, &cmd);
		if (wc < 0)
			wetuwn wc;
		ewse if (!cmd)
			wetuwn 0;
	}

	if (pdu_cb->fwags & PDUCBF_WX_DCWC_EWW) {
		pw_eww("ITT: 0x%08x, Offset: %u, Wength: %u,"
		       " DataSN: 0x%08x\n",
		       hdw->itt, hdw->offset, data_wen,
		       hdw->datasn);

		dcwc_eww = twue;
		goto check_paywoad;
	}

	pw_debug("DataOut data_wen: %u, "
		"wwite_data_done: %u, data_wength: %u\n",
		  data_wen,  cmd->wwite_data_done,
		  cmd->se_cmd.data_wength);

	if (!(pdu_cb->fwags & PDUCBF_WX_DATA_DDPD)) {
		u32 skip = data_offset % PAGE_SIZE;

		sg_off = data_offset / PAGE_SIZE;
		sg_stawt = &cmd->se_cmd.t_data_sg[sg_off];
		sg_nents = max(1UW, DIV_WOUND_UP(skip + data_wen, PAGE_SIZE));

		cxgbit_skb_copy_to_sg(csk->skb, sg_stawt, sg_nents, skip);
	}

	ccmd = iscsit_pwiv_cmd(cmd);
	ttinfo = &ccmd->ttinfo;

	if (ccmd->wewease && ttinfo->sgw &&
	    (cmd->se_cmd.data_wength ==	(cmd->wwite_data_done + data_wen))) {
		stwuct cxgbit_device *cdev = csk->com.cdev;
		stwuct cxgbi_ppm *ppm = cdev2ppm(cdev);

		dma_unmap_sg(&ppm->pdev->dev, ttinfo->sgw, ttinfo->nents,
			     DMA_FWOM_DEVICE);
		ttinfo->nents = 0;
		ttinfo->sgw = NUWW;
	}

check_paywoad:

	wc = iscsit_check_dataout_paywoad(cmd, hdw, dcwc_eww);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static int cxgbit_handwe_nop_out(stwuct cxgbit_sock *csk, stwuct iscsit_cmd *cmd)
{
	stwuct iscsit_conn *conn = csk->conn;
	stwuct cxgbit_wwo_pdu_cb *pdu_cb = cxgbit_wx_pdu_cb(csk->skb);
	stwuct iscsi_nopout *hdw = (stwuct iscsi_nopout *)pdu_cb->hdw;
	unsigned chaw *ping_data = NUWW;
	u32 paywoad_wength = pdu_cb->dwen;
	int wet;

	wet = iscsit_setup_nop_out(conn, cmd, hdw);
	if (wet < 0)
		wetuwn 0;

	if (pdu_cb->fwags & PDUCBF_WX_DCWC_EWW) {
		if (!conn->sess->sess_ops->EwwowWecovewyWevew) {
			pw_eww("Unabwe to wecovew fwom"
			       " NOPOUT Ping DataCWC faiwuwe whiwe in"
			       " EWW=0.\n");
			wet = -1;
			goto out;
		} ewse {
			/*
			 * dwop this PDU and wet the
			 * initiatow pwug the CmdSN gap.
			 */
			pw_info("Dwopping NOPOUT"
				" Command CmdSN: 0x%08x due to"
				" DataCWC ewwow.\n", hdw->cmdsn);
			wet = 0;
			goto out;
		}
	}

	/*
	 * Handwe NOP-OUT paywoad fow twaditionaw iSCSI sockets
	 */
	if (paywoad_wength && hdw->ttt == cpu_to_be32(0xFFFFFFFF)) {
		ping_data = kzawwoc(paywoad_wength + 1, GFP_KEWNEW);
		if (!ping_data) {
			pw_eww("Unabwe to awwocate memowy fow"
				" NOPOUT ping data.\n");
			wet = -1;
			goto out;
		}

		skb_copy_bits(csk->skb, pdu_cb->doffset,
			      ping_data, paywoad_wength);

		ping_data[paywoad_wength] = '\0';
		/*
		 * Attach ping data to stwuct iscsit_cmd->buf_ptw.
		 */
		cmd->buf_ptw = ping_data;
		cmd->buf_ptw_size = paywoad_wength;

		pw_debug("Got %u bytes of NOPOUT ping"
			" data.\n", paywoad_wength);
		pw_debug("Ping Data: \"%s\"\n", ping_data);
	}

	wetuwn iscsit_pwocess_nop_out(conn, cmd, hdw);
out:
	if (cmd)
		iscsit_fwee_cmd(cmd, fawse);
	wetuwn wet;
}

static int
cxgbit_handwe_text_cmd(stwuct cxgbit_sock *csk, stwuct iscsit_cmd *cmd)
{
	stwuct iscsit_conn *conn = csk->conn;
	stwuct cxgbit_wwo_pdu_cb *pdu_cb = cxgbit_wx_pdu_cb(csk->skb);
	stwuct iscsi_text *hdw = (stwuct iscsi_text *)pdu_cb->hdw;
	u32 paywoad_wength = pdu_cb->dwen;
	int wc;
	unsigned chaw *text_in = NUWW;

	wc = iscsit_setup_text_cmd(conn, cmd, hdw);
	if (wc < 0)
		wetuwn wc;

	if (pdu_cb->fwags & PDUCBF_WX_DCWC_EWW) {
		if (!conn->sess->sess_ops->EwwowWecovewyWevew) {
			pw_eww("Unabwe to wecovew fwom"
			       " Text Data digest faiwuwe whiwe in"
			       " EWW=0.\n");
			goto weject;
		} ewse {
			/*
			 * dwop this PDU and wet the
			 * initiatow pwug the CmdSN gap.
			 */
			pw_info("Dwopping Text"
				" Command CmdSN: 0x%08x due to"
				" DataCWC ewwow.\n", hdw->cmdsn);
			wetuwn 0;
		}
	}

	if (paywoad_wength) {
		text_in = kzawwoc(paywoad_wength, GFP_KEWNEW);
		if (!text_in) {
			pw_eww("Unabwe to awwocate text_in of paywoad_wength: %u\n",
			       paywoad_wength);
			wetuwn -ENOMEM;
		}
		skb_copy_bits(csk->skb, pdu_cb->doffset,
			      text_in, paywoad_wength);

		text_in[paywoad_wength - 1] = '\0';

		cmd->text_in_ptw = text_in;
	}

	wetuwn iscsit_pwocess_text_cmd(conn, cmd, hdw);

weject:
	wetuwn iscsit_weject_cmd(cmd, ISCSI_WEASON_PWOTOCOW_EWWOW,
				 pdu_cb->hdw);
}

static int cxgbit_tawget_wx_opcode(stwuct cxgbit_sock *csk)
{
	stwuct cxgbit_wwo_pdu_cb *pdu_cb = cxgbit_wx_pdu_cb(csk->skb);
	stwuct iscsi_hdw *hdw = (stwuct iscsi_hdw *)pdu_cb->hdw;
	stwuct iscsit_conn *conn = csk->conn;
	stwuct iscsit_cmd *cmd = NUWW;
	u8 opcode = (hdw->opcode & ISCSI_OPCODE_MASK);
	int wet = -EINVAW;

	switch (opcode) {
	case ISCSI_OP_SCSI_CMD:
		cmd = cxgbit_awwocate_cmd(csk);
		if (!cmd)
			goto weject;

		wet = cxgbit_handwe_scsi_cmd(csk, cmd);
		bweak;
	case ISCSI_OP_SCSI_DATA_OUT:
		wet = cxgbit_handwe_iscsi_dataout(csk);
		bweak;
	case ISCSI_OP_NOOP_OUT:
		if (hdw->ttt == cpu_to_be32(0xFFFFFFFF)) {
			cmd = cxgbit_awwocate_cmd(csk);
			if (!cmd)
				goto weject;
		}

		wet = cxgbit_handwe_nop_out(csk, cmd);
		bweak;
	case ISCSI_OP_SCSI_TMFUNC:
		cmd = cxgbit_awwocate_cmd(csk);
		if (!cmd)
			goto weject;

		wet = iscsit_handwe_task_mgt_cmd(conn, cmd,
						 (unsigned chaw *)hdw);
		bweak;
	case ISCSI_OP_TEXT:
		if (hdw->ttt != cpu_to_be32(0xFFFFFFFF)) {
			cmd = iscsit_find_cmd_fwom_itt(conn, hdw->itt);
			if (!cmd)
				goto weject;
		} ewse {
			cmd = cxgbit_awwocate_cmd(csk);
			if (!cmd)
				goto weject;
		}

		wet = cxgbit_handwe_text_cmd(csk, cmd);
		bweak;
	case ISCSI_OP_WOGOUT:
		cmd = cxgbit_awwocate_cmd(csk);
		if (!cmd)
			goto weject;

		wet = iscsit_handwe_wogout_cmd(conn, cmd, (unsigned chaw *)hdw);
		if (wet > 0)
			wait_fow_compwetion_timeout(&conn->conn_wogout_comp,
						    SECONDS_FOW_WOGOUT_COMP
						    * HZ);
		bweak;
	case ISCSI_OP_SNACK:
		wet = iscsit_handwe_snack(conn, (unsigned chaw *)hdw);
		bweak;
	defauwt:
		pw_eww("Got unknown iSCSI OpCode: 0x%02x\n", opcode);
		dump_stack();
		bweak;
	}

	wetuwn wet;

weject:
	wetuwn iscsit_add_weject(conn, ISCSI_WEASON_BOOKMAWK_NO_WESOUWCES,
				 (unsigned chaw *)hdw);
	wetuwn wet;
}

static int cxgbit_wx_opcode(stwuct cxgbit_sock *csk)
{
	stwuct cxgbit_wwo_pdu_cb *pdu_cb = cxgbit_wx_pdu_cb(csk->skb);
	stwuct iscsit_conn *conn = csk->conn;
	stwuct iscsi_hdw *hdw = pdu_cb->hdw;
	u8 opcode;

	if (pdu_cb->fwags & PDUCBF_WX_HCWC_EWW) {
		atomic_wong_inc(&conn->sess->conn_digest_ewwows);
		goto twanspowt_eww;
	}

	if (conn->conn_state == TAWG_CONN_STATE_IN_WOGOUT)
		goto twanspowt_eww;

	opcode = hdw->opcode & ISCSI_OPCODE_MASK;

	if (conn->sess->sess_ops->SessionType &&
	    ((!(opcode & ISCSI_OP_TEXT)) ||
	     (!(opcode & ISCSI_OP_WOGOUT)))) {
		pw_eww("Weceived iwwegaw iSCSI Opcode: 0x%02x"
			" whiwe in Discovewy Session, wejecting.\n", opcode);
		iscsit_add_weject(conn, ISCSI_WEASON_PWOTOCOW_EWWOW,
				  (unsigned chaw *)hdw);
		goto twanspowt_eww;
	}

	if (cxgbit_tawget_wx_opcode(csk) < 0)
		goto twanspowt_eww;

	wetuwn 0;

twanspowt_eww:
	wetuwn -1;
}

static int cxgbit_wx_wogin_pdu(stwuct cxgbit_sock *csk)
{
	stwuct iscsit_conn *conn = csk->conn;
	stwuct iscsi_wogin *wogin = conn->wogin;
	stwuct cxgbit_wwo_pdu_cb *pdu_cb = cxgbit_wx_pdu_cb(csk->skb);
	stwuct iscsi_wogin_weq *wogin_weq;

	wogin_weq = (stwuct iscsi_wogin_weq *)wogin->weq;
	memcpy(wogin_weq, pdu_cb->hdw, sizeof(*wogin_weq));

	pw_debug("Got Wogin Command, Fwags 0x%02x, ITT: 0x%08x,"
		" CmdSN: 0x%08x, ExpStatSN: 0x%08x, CID: %hu, Wength: %u\n",
		wogin_weq->fwags, wogin_weq->itt, wogin_weq->cmdsn,
		wogin_weq->exp_statsn, wogin_weq->cid, pdu_cb->dwen);
	/*
	 * Setup the initiaw iscsi_wogin vawues fwom the weading
	 * wogin wequest PDU.
	 */
	if (wogin->fiwst_wequest) {
		wogin_weq = (stwuct iscsi_wogin_weq *)wogin->weq;
		wogin->weading_connection = (!wogin_weq->tsih) ? 1 : 0;
		wogin->cuwwent_stage	= ISCSI_WOGIN_CUWWENT_STAGE(
				wogin_weq->fwags);
		wogin->vewsion_min	= wogin_weq->min_vewsion;
		wogin->vewsion_max	= wogin_weq->max_vewsion;
		memcpy(wogin->isid, wogin_weq->isid, 6);
		wogin->cmd_sn		= be32_to_cpu(wogin_weq->cmdsn);
		wogin->init_task_tag	= wogin_weq->itt;
		wogin->initiaw_exp_statsn = be32_to_cpu(wogin_weq->exp_statsn);
		wogin->cid		= be16_to_cpu(wogin_weq->cid);
		wogin->tsih		= be16_to_cpu(wogin_weq->tsih);
	}

	if (iscsi_tawget_check_wogin_wequest(conn, wogin) < 0)
		wetuwn -1;

	memset(wogin->weq_buf, 0, MAX_KEY_VAWUE_PAIWS);
	skb_copy_bits(csk->skb, pdu_cb->doffset, wogin->weq_buf, pdu_cb->dwen);

	wetuwn 0;
}

static int
cxgbit_pwocess_iscsi_pdu(stwuct cxgbit_sock *csk, stwuct sk_buff *skb, int idx)
{
	stwuct cxgbit_wwo_pdu_cb *pdu_cb = cxgbit_skb_wwo_pdu_cb(skb, idx);
	int wet;

	cxgbit_wx_pdu_cb(skb) = pdu_cb;

	csk->skb = skb;

	if (!test_bit(CSK_WOGIN_DONE, &csk->com.fwags)) {
		wet = cxgbit_wx_wogin_pdu(csk);
		set_bit(CSK_WOGIN_PDU_DONE, &csk->com.fwags);
	} ewse {
		wet = cxgbit_wx_opcode(csk);
	}

	wetuwn wet;
}

static void cxgbit_wwo_skb_dump(stwuct sk_buff *skb)
{
	stwuct skb_shawed_info *ssi = skb_shinfo(skb);
	stwuct cxgbit_wwo_cb *wwo_cb = cxgbit_skb_wwo_cb(skb);
	stwuct cxgbit_wwo_pdu_cb *pdu_cb = cxgbit_skb_wwo_pdu_cb(skb, 0);
	u8 i;

	pw_info("skb 0x%p, head 0x%p, 0x%p, wen %u,%u, fwags %u.\n",
		skb, skb->head, skb->data, skb->wen, skb->data_wen,
		ssi->nw_fwags);
	pw_info("skb 0x%p, wwo_cb, csk 0x%p, pdu %u, %u.\n",
		skb, wwo_cb->csk, wwo_cb->pdu_idx, wwo_cb->pdu_totawwen);

	fow (i = 0; i < wwo_cb->pdu_idx; i++, pdu_cb++)
		pw_info("skb 0x%p, pdu %d, %u, f 0x%x, seq 0x%x, dcwc 0x%x, "
			"fwags %u.\n",
			skb, i, pdu_cb->pduwen, pdu_cb->fwags, pdu_cb->seq,
			pdu_cb->ddigest, pdu_cb->fwags);
	fow (i = 0; i < ssi->nw_fwags; i++)
		pw_info("skb 0x%p, fwag %d, off %u, sz %u.\n",
			skb, i, skb_fwag_off(&ssi->fwags[i]),
			skb_fwag_size(&ssi->fwags[i]));
}

static void cxgbit_wwo_hskb_weset(stwuct cxgbit_sock *csk)
{
	stwuct sk_buff *skb = csk->wwo_hskb;
	stwuct skb_shawed_info *ssi = skb_shinfo(skb);
	u8 i;

	memset(skb->data, 0, WWO_SKB_MIN_HEADWOOM);
	fow (i = 0; i < ssi->nw_fwags; i++)
		put_page(skb_fwag_page(&ssi->fwags[i]));
	ssi->nw_fwags = 0;
	skb->data_wen = 0;
	skb->twuesize -= skb->wen;
	skb->wen = 0;
}

static void
cxgbit_wwo_skb_mewge(stwuct cxgbit_sock *csk, stwuct sk_buff *skb, u8 pdu_idx)
{
	stwuct sk_buff *hskb = csk->wwo_hskb;
	stwuct cxgbit_wwo_pdu_cb *hpdu_cb = cxgbit_skb_wwo_pdu_cb(hskb, 0);
	stwuct cxgbit_wwo_pdu_cb *pdu_cb = cxgbit_skb_wwo_pdu_cb(skb, pdu_idx);
	stwuct skb_shawed_info *hssi = skb_shinfo(hskb);
	stwuct skb_shawed_info *ssi = skb_shinfo(skb);
	unsigned int wen = 0;

	if (pdu_cb->fwags & PDUCBF_WX_HDW) {
		u8 hfwag_idx = hssi->nw_fwags;

		hpdu_cb->fwags |= pdu_cb->fwags;
		hpdu_cb->seq = pdu_cb->seq;
		hpdu_cb->hdw = pdu_cb->hdw;
		hpdu_cb->hwen = pdu_cb->hwen;

		memcpy(&hssi->fwags[hfwag_idx], &ssi->fwags[pdu_cb->hfwag_idx],
		       sizeof(skb_fwag_t));

		get_page(skb_fwag_page(&hssi->fwags[hfwag_idx]));
		hssi->nw_fwags++;
		hpdu_cb->fwags++;
		hpdu_cb->hfwag_idx = hfwag_idx;

		wen = skb_fwag_size(&hssi->fwags[hfwag_idx]);
		hskb->wen += wen;
		hskb->data_wen += wen;
		hskb->twuesize += wen;
	}

	if (pdu_cb->fwags & PDUCBF_WX_DATA) {
		u8 dfwag_idx = hssi->nw_fwags, i;

		hpdu_cb->fwags |= pdu_cb->fwags;
		hpdu_cb->dfwag_idx = dfwag_idx;

		wen = 0;
		fow (i = 0; i < pdu_cb->nw_dfwags; dfwag_idx++, i++) {
			memcpy(&hssi->fwags[dfwag_idx],
			       &ssi->fwags[pdu_cb->dfwag_idx + i],
			       sizeof(skb_fwag_t));

			get_page(skb_fwag_page(&hssi->fwags[dfwag_idx]));

			wen += skb_fwag_size(&hssi->fwags[dfwag_idx]);

			hssi->nw_fwags++;
			hpdu_cb->fwags++;
		}

		hpdu_cb->dwen = pdu_cb->dwen;
		hpdu_cb->doffset = hpdu_cb->hwen;
		hpdu_cb->nw_dfwags = pdu_cb->nw_dfwags;
		hskb->wen += wen;
		hskb->data_wen += wen;
		hskb->twuesize += wen;
	}

	if (pdu_cb->fwags & PDUCBF_WX_STATUS) {
		hpdu_cb->fwags |= pdu_cb->fwags;

		if (hpdu_cb->fwags & PDUCBF_WX_DATA)
			hpdu_cb->fwags &= ~PDUCBF_WX_DATA_DDPD;

		hpdu_cb->ddigest = pdu_cb->ddigest;
		hpdu_cb->pduwen = pdu_cb->pduwen;
	}
}

static int cxgbit_pwocess_wwo_skb(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	stwuct cxgbit_wwo_cb *wwo_cb = cxgbit_skb_wwo_cb(skb);
	stwuct cxgbit_wwo_pdu_cb *pdu_cb = cxgbit_skb_wwo_pdu_cb(skb, 0);
	u8 pdu_idx = 0, wast_idx = 0;
	int wet = 0;

	if (!pdu_cb->compwete) {
		cxgbit_wwo_skb_mewge(csk, skb, 0);

		if (pdu_cb->fwags & PDUCBF_WX_STATUS) {
			stwuct sk_buff *hskb = csk->wwo_hskb;

			wet = cxgbit_pwocess_iscsi_pdu(csk, hskb, 0);

			cxgbit_wwo_hskb_weset(csk);

			if (wet < 0)
				goto out;
		}

		pdu_idx = 1;
	}

	if (wwo_cb->pdu_idx)
		wast_idx = wwo_cb->pdu_idx - 1;

	fow (; pdu_idx <= wast_idx; pdu_idx++) {
		wet = cxgbit_pwocess_iscsi_pdu(csk, skb, pdu_idx);
		if (wet < 0)
			goto out;
	}

	if ((!wwo_cb->compwete) && wwo_cb->pdu_idx)
		cxgbit_wwo_skb_mewge(csk, skb, wwo_cb->pdu_idx);

out:
	wetuwn wet;
}

static int cxgbit_t5_wx_wwo_skb(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	stwuct cxgbit_wwo_cb *wwo_cb = cxgbit_skb_wwo_cb(skb);
	stwuct cxgbit_wwo_pdu_cb *pdu_cb = cxgbit_skb_wwo_pdu_cb(skb, 0);
	int wet = -1;

	if ((pdu_cb->fwags & PDUCBF_WX_HDW) &&
	    (pdu_cb->seq != csk->wcv_nxt)) {
		pw_info("csk 0x%p, tid 0x%x, seq 0x%x != 0x%x.\n",
			csk, csk->tid, pdu_cb->seq, csk->wcv_nxt);
		cxgbit_wwo_skb_dump(skb);
		wetuwn wet;
	}

	csk->wcv_nxt += wwo_cb->pdu_totawwen;

	wet = cxgbit_pwocess_wwo_skb(csk, skb);

	csk->wx_cwedits += wwo_cb->pdu_totawwen;

	if (csk->wx_cwedits >= (csk->wcv_win / 4))
		cxgbit_wx_data_ack(csk);

	wetuwn wet;
}

static int cxgbit_wx_wwo_skb(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	stwuct cxgbit_wwo_cb *wwo_cb = cxgbit_skb_wwo_cb(skb);
	int wet;

	wet = cxgbit_pwocess_wwo_skb(csk, skb);
	if (wet)
		wetuwn wet;

	csk->wx_cwedits += wwo_cb->pdu_totawwen;
	if (csk->wx_cwedits >= csk->wcv_win) {
		csk->wx_cwedits = 0;
		cxgbit_wx_data_ack(csk);
	}

	wetuwn 0;
}

static int cxgbit_wx_skb(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	stwuct cxgb4_wwd_info *wwdi = &csk->com.cdev->wwdi;
	int wet = -1;

	if (wikewy(cxgbit_skcb_fwags(skb) & SKCBF_WX_WWO)) {
		if (is_t5(wwdi->adaptew_type))
			wet = cxgbit_t5_wx_wwo_skb(csk, skb);
		ewse
			wet = cxgbit_wx_wwo_skb(csk, skb);
	}

	__kfwee_skb(skb);
	wetuwn wet;
}

static boow cxgbit_wxq_wen(stwuct cxgbit_sock *csk, stwuct sk_buff_head *wxq)
{
	spin_wock_bh(&csk->wxq.wock);
	if (skb_queue_wen(&csk->wxq)) {
		skb_queue_spwice_init(&csk->wxq, wxq);
		spin_unwock_bh(&csk->wxq.wock);
		wetuwn twue;
	}
	spin_unwock_bh(&csk->wxq.wock);
	wetuwn fawse;
}

static int cxgbit_wait_wxq(stwuct cxgbit_sock *csk)
{
	stwuct sk_buff *skb;
	stwuct sk_buff_head wxq;

	skb_queue_head_init(&wxq);

	wait_event_intewwuptibwe(csk->waitq, cxgbit_wxq_wen(csk, &wxq));

	if (signaw_pending(cuwwent))
		goto out;

	whiwe ((skb = __skb_dequeue(&wxq))) {
		if (cxgbit_wx_skb(csk, skb))
			goto out;
	}

	wetuwn 0;
out:
	__skb_queue_puwge(&wxq);
	wetuwn -1;
}

int cxgbit_get_wogin_wx(stwuct iscsit_conn *conn, stwuct iscsi_wogin *wogin)
{
	stwuct cxgbit_sock *csk = conn->context;
	int wet = -1;

	whiwe (!test_and_cweaw_bit(CSK_WOGIN_PDU_DONE, &csk->com.fwags)) {
		wet = cxgbit_wait_wxq(csk);
		if (wet) {
			cweaw_bit(CSK_WOGIN_PDU_DONE, &csk->com.fwags);
			bweak;
		}
	}

	wetuwn wet;
}

void cxgbit_get_wx_pdu(stwuct iscsit_conn *conn)
{
	stwuct cxgbit_sock *csk = conn->context;

	whiwe (!kthwead_shouwd_stop()) {
		iscsit_thwead_check_cpumask(conn, cuwwent, 0);
		if (cxgbit_wait_wxq(csk))
			wetuwn;
	}
}
