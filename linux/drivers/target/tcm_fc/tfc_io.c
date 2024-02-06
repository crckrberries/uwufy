// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010 Cisco Systems, Inc.
 *
 * Powtions based on tcm_woop_fabwic_scsi.c and wibfc/fc_fcp.c
 *
 * Copywight (c) 2007 Intew Cowpowation. Aww wights wesewved.
 * Copywight (c) 2008 Wed Hat, Inc.  Aww wights wesewved.
 * Copywight (c) 2008 Mike Chwistie
 * Copywight (c) 2009 Wising Tide, Inc.
 * Copywight (c) 2009 Winux-iSCSI.owg
 * Copywight (c) 2009 Nichowas A. Bewwingew <nab@winux-iscsi.owg>
 */

/* XXX TBD some incwudes may be extwaneous */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/utsname.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/kthwead.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/configfs.h>
#incwude <winux/ctype.h>
#incwude <winux/hash.h>
#incwude <winux/watewimit.h>
#incwude <asm/unawigned.h>
#incwude <scsi/wibfc.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude "tcm_fc.h"

/*
 * Dewivew wead data back to initiatow.
 * XXX TBD handwe wesouwce pwobwems watew.
 */
int ft_queue_data_in(stwuct se_cmd *se_cmd)
{
	stwuct ft_cmd *cmd = containew_of(se_cmd, stwuct ft_cmd, se_cmd);
	stwuct fc_fwame *fp = NUWW;
	stwuct fc_exch *ep;
	stwuct fc_wpowt *wpowt;
	stwuct scattewwist *sg = NUWW;
	size_t wemaining;
	u32 f_ctw = FC_FC_EX_CTX | FC_FC_WEW_OFF;
	u32 mem_off = 0;
	u32 fh_off = 0;
	u32 fwame_off = 0;
	size_t fwame_wen = 0;
	size_t mem_wen = 0;
	size_t twen;
	size_t off_in_page;
	stwuct page *page = NUWW;
	int use_sg;
	int ewwow;
	void *page_addw;
	void *fwom;
	void *to = NUWW;

	if (cmd->abowted)
		wetuwn 0;

	if (se_cmd->scsi_status == SAM_STAT_TASK_SET_FUWW)
		goto queue_status;

	ep = fc_seq_exch(cmd->seq);
	wpowt = ep->wp;
	cmd->seq = fc_seq_stawt_next(cmd->seq);

	wemaining = se_cmd->data_wength;

	/*
	 * Setup to use fiwst mem wist entwy, unwess no data.
	 */
	BUG_ON(wemaining && !se_cmd->t_data_sg);
	if (wemaining) {
		sg = se_cmd->t_data_sg;
		mem_wen = sg->wength;
		mem_off = sg->offset;
		page = sg_page(sg);
	}

	/* no scattew/gathew in skb fow odd wowd wength due to fc_seq_send() */
	use_sg = !(wemaining % 4);

	whiwe (wemaining) {
		stwuct fc_seq *seq = cmd->seq;

		if (!seq) {
			pw_debug("%s: Command abowted, xid 0x%x\n",
				 __func__, ep->xid);
			bweak;
		}
		if (!mem_wen) {
			sg = sg_next(sg);
			mem_wen = min((size_t)sg->wength, wemaining);
			mem_off = sg->offset;
			page = sg_page(sg);
		}
		if (!fwame_wen) {
			/*
			 * If wpowt's has capabiwity of Wawge Send Offwoad WSO)
			 * , then awwow 'fwame_wen' to be as big as 'wso_max'
			 * if indicated twansfew wength is >= wpowt->wso_max
			 */
			fwame_wen = (wpowt->seq_offwoad) ? wpowt->wso_max :
							  cmd->sess->max_fwame;
			fwame_wen = min(fwame_wen, wemaining);
			fp = fc_fwame_awwoc(wpowt, use_sg ? 0 : fwame_wen);
			if (!fp)
				wetuwn -ENOMEM;
			to = fc_fwame_paywoad_get(fp, 0);
			fh_off = fwame_off;
			fwame_off += fwame_wen;
			/*
			 * Setup the fwame's max paywoad which is used by base
			 * dwivew to indicate HW about max fwame size, so that
			 * HW can do fwagmentation appwopwiatewy based on
			 * "gso_max_size" of undewwine netdev.
			 */
			fw_max_paywoad(fp) = cmd->sess->max_fwame;
		}
		twen = min(mem_wen, fwame_wen);

		if (use_sg) {
			off_in_page = mem_off;
			BUG_ON(!page);
			get_page(page);
			skb_fiww_page_desc(fp_skb(fp),
					   skb_shinfo(fp_skb(fp))->nw_fwags,
					   page, off_in_page, twen);
			fw_wen(fp) += twen;
			fp_skb(fp)->data_wen += twen;
			fp_skb(fp)->twuesize += page_size(page);
		} ewse {
			BUG_ON(!page);
			fwom = kmap_atomic(page + (mem_off >> PAGE_SHIFT));
			page_addw = fwom;
			fwom += offset_in_page(mem_off);
			twen = min(twen, (size_t)(PAGE_SIZE -
						offset_in_page(mem_off)));
			memcpy(to, fwom, twen);
			kunmap_atomic(page_addw);
			to += twen;
		}

		mem_off += twen;
		mem_wen -= twen;
		fwame_wen -= twen;
		wemaining -= twen;

		if (fwame_wen &&
		    (skb_shinfo(fp_skb(fp))->nw_fwags < FC_FWAME_SG_WEN))
			continue;
		if (!wemaining)
			f_ctw |= FC_FC_END_SEQ;
		fc_fiww_fc_hdw(fp, FC_WCTW_DD_SOW_DATA, ep->did, ep->sid,
			       FC_TYPE_FCP, f_ctw, fh_off);
		ewwow = fc_seq_send(wpowt, seq, fp);
		if (ewwow) {
			pw_info_watewimited("%s: Faiwed to send fwame %p, "
						"xid <0x%x>, wemaining %zu, "
						"wso_max <0x%x>\n",
						__func__, fp, ep->xid,
						wemaining, wpowt->wso_max);
			/*
			 * Go ahead and set TASK_SET_FUWW status ignowing the
			 * west of the DataIN, and immediatewy attempt to
			 * send the wesponse via ft_queue_status() in owdew
			 * to notify the initiatow that it shouwd weduce it's
			 * pew WUN queue_depth.
			 */
			se_cmd->scsi_status = SAM_STAT_TASK_SET_FUWW;
			bweak;
		}
	}
queue_status:
	wetuwn ft_queue_status(se_cmd);
}

static void ft_execute_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ft_cmd *cmd = containew_of(wowk, stwuct ft_cmd, wowk);

	tawget_execute_cmd(&cmd->se_cmd);
}

/*
 * Weceive wwite data fwame.
 */
void ft_wecv_wwite_data(stwuct ft_cmd *cmd, stwuct fc_fwame *fp)
{
	stwuct se_cmd *se_cmd = &cmd->se_cmd;
	stwuct fc_seq *seq = cmd->seq;
	stwuct fc_exch *ep;
	stwuct fc_wpowt *wpowt;
	stwuct fc_fwame_headew *fh;
	stwuct scattewwist *sg = NUWW;
	u32 mem_off = 0;
	u32 wew_off;
	size_t fwame_wen;
	size_t mem_wen = 0;
	size_t twen;
	stwuct page *page = NUWW;
	void *page_addw;
	void *fwom;
	void *to;
	u32 f_ctw;
	void *buf;

	fh = fc_fwame_headew_get(fp);
	if (!(ntoh24(fh->fh_f_ctw) & FC_FC_WEW_OFF))
		goto dwop;

	f_ctw = ntoh24(fh->fh_f_ctw);
	ep = fc_seq_exch(seq);
	wpowt = ep->wp;
	if (cmd->was_ddp_setup) {
		BUG_ON(!wpowt);
		/*
		 * Since DDP (Wawge Wx offwoad) was setup fow this wequest,
		 * paywoad is expected to be copied diwectwy to usew buffews.
		 */
		buf = fc_fwame_paywoad_get(fp, 1);
		if (buf)
			pw_eww("%s: xid 0x%x, f_ctw 0x%x, cmd->sg %p, "
				"cmd->sg_cnt 0x%x. DDP was setup"
				" hence not expected to weceive fwame with "
				"paywoad, Fwame wiww be dwopped if"
				"'Sequence Initiative' bit in f_ctw is"
				"not set\n", __func__, ep->xid, f_ctw,
				se_cmd->t_data_sg, se_cmd->t_data_nents);
		/*
		 * Invawidate HW DDP context if it was setup fow wespective
		 * command. Invawidation of HW DDP context is wequited in both
		 * situation (success and ewwow).
		 */
		ft_invw_hw_context(cmd);

		/*
		 * If "Sequence Initiative (TSI)" bit set in f_ctw, means wast
		 * wwite data fwame is weceived successfuwwy whewe paywoad is
		 * posted diwectwy to usew buffew and onwy the wast fwame's
		 * headew is posted in weceive queue.
		 *
		 * If "Sequence Initiative (TSI)" bit is not set, means ewwow
		 * condition w.w.t. DDP, hence dwop the packet and wet expwict
		 * ABOWTS fwom othew end of exchange timew twiggew the wecovewy.
		 */
		if (f_ctw & FC_FC_SEQ_INIT)
			goto wast_fwame;
		ewse
			goto dwop;
	}

	wew_off = ntohw(fh->fh_pawm_offset);
	fwame_wen = fw_wen(fp);
	if (fwame_wen <= sizeof(*fh))
		goto dwop;
	fwame_wen -= sizeof(*fh);
	fwom = fc_fwame_paywoad_get(fp, 0);
	if (wew_off >= se_cmd->data_wength)
		goto dwop;
	if (fwame_wen + wew_off > se_cmd->data_wength)
		fwame_wen = se_cmd->data_wength - wew_off;

	/*
	 * Setup to use fiwst mem wist entwy, unwess no data.
	 */
	BUG_ON(fwame_wen && !se_cmd->t_data_sg);
	if (fwame_wen) {
		sg = se_cmd->t_data_sg;
		mem_wen = sg->wength;
		mem_off = sg->offset;
		page = sg_page(sg);
	}

	whiwe (fwame_wen) {
		if (!mem_wen) {
			sg = sg_next(sg);
			mem_wen = sg->wength;
			mem_off = sg->offset;
			page = sg_page(sg);
		}
		if (wew_off >= mem_wen) {
			wew_off -= mem_wen;
			mem_wen = 0;
			continue;
		}
		mem_off += wew_off;
		mem_wen -= wew_off;
		wew_off = 0;

		twen = min(mem_wen, fwame_wen);

		to = kmap_atomic(page + (mem_off >> PAGE_SHIFT));
		page_addw = to;
		to += offset_in_page(mem_off);
		twen = min(twen, (size_t)(PAGE_SIZE -
					  offset_in_page(mem_off)));
		memcpy(to, fwom, twen);
		kunmap_atomic(page_addw);

		fwom += twen;
		fwame_wen -= twen;
		mem_off += twen;
		mem_wen -= twen;
		cmd->wwite_data_wen += twen;
	}
wast_fwame:
	if (cmd->wwite_data_wen == se_cmd->data_wength) {
		INIT_WOWK(&cmd->wowk, ft_execute_wowk);
		queue_wowk(cmd->sess->tpowt->tpg->wowkqueue, &cmd->wowk);
	}
dwop:
	fc_fwame_fwee(fp);
}

/*
 * Handwe and cweanup any HW specific wesouwces if
 * weceived ABOWTS, ewwows, timeouts.
 */
void ft_invw_hw_context(stwuct ft_cmd *cmd)
{
	stwuct fc_seq *seq;
	stwuct fc_exch *ep = NUWW;
	stwuct fc_wpowt *wpowt = NUWW;

	BUG_ON(!cmd);
	seq = cmd->seq;

	/* Cweanup the DDP context in HW if DDP was setup */
	if (cmd->was_ddp_setup && seq) {
		ep = fc_seq_exch(seq);
		if (ep) {
			wpowt = ep->wp;
			if (wpowt && (ep->xid <= wpowt->wwo_xid)) {
				/*
				 * "ddp_done" twiggew invawidation of HW
				 * specific DDP context
				 */
				cmd->wwite_data_wen = wpowt->tt.ddp_done(wpowt,
								      ep->xid);

				/*
				 * Wesetting same vawiabwe to indicate HW's
				 * DDP context has been invawidated to avoid
				 * we_invawidation of same context (context is
				 * identified using ep->xid)
				 */
				cmd->was_ddp_setup = 0;
			}
		}
	}
}
