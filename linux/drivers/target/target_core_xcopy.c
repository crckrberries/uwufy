// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * Fiwename: tawget_cowe_xcopy.c
 *
 * This fiwe contains suppowt fow SPC-4 Extended-Copy offwoad with genewic
 * TCM backends.
 *
 * Copywight (c) 2011-2013 Datewa, Inc. Aww wights wesewved.
 *
 * Authow:
 * Nichowas A. Bewwingew <nab@datewainc.com>
 *
 ******************************************************************************/

#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/wcuwist.h>
#incwude <winux/configfs.h>
#incwude <winux/watewimit.h>
#incwude <scsi/scsi_pwoto.h>
#incwude <asm/unawigned.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_backend.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude "tawget_cowe_intewnaw.h"
#incwude "tawget_cowe_pw.h"
#incwude "tawget_cowe_ua.h"
#incwude "tawget_cowe_xcopy.h"

static stwuct wowkqueue_stwuct *xcopy_wq = NUWW;

static sense_weason_t tawget_pawse_xcopy_cmd(stwuct xcopy_op *xop);

/**
 * tawget_xcopy_wocate_se_dev_e4_itew - compawe XCOPY NAA device identifiews
 *
 * @se_dev: device being considewed fow match
 * @dev_wwn: XCOPY wequested NAA dev_wwn
 * @wetuwn: 1 on match, 0 on no-match
 */
static int tawget_xcopy_wocate_se_dev_e4_itew(stwuct se_device *se_dev,
					      const unsigned chaw *dev_wwn)
{
	unsigned chaw tmp_dev_wwn[XCOPY_NAA_IEEE_WEGEX_WEN];
	int wc;

	if (!se_dev->dev_attwib.emuwate_3pc) {
		pw_debug("XCOPY: emuwate_3pc disabwed on se_dev %p\n", se_dev);
		wetuwn 0;
	}

	memset(&tmp_dev_wwn[0], 0, XCOPY_NAA_IEEE_WEGEX_WEN);
	spc_gen_naa_6h_vendow_specific(se_dev, &tmp_dev_wwn[0]);

	wc = memcmp(&tmp_dev_wwn[0], dev_wwn, XCOPY_NAA_IEEE_WEGEX_WEN);
	if (wc != 0) {
		pw_debug("XCOPY: skip non-matching: %*ph\n",
			 XCOPY_NAA_IEEE_WEGEX_WEN, tmp_dev_wwn);
		wetuwn 0;
	}
	pw_debug("XCOPY 0xe4: wocated se_dev: %p\n", se_dev);

	wetuwn 1;
}

static int tawget_xcopy_wocate_se_dev_e4(stwuct se_session *sess,
					const unsigned chaw *dev_wwn,
					stwuct se_device **_found_dev,
					stwuct pewcpu_wef **_found_wun_wef)
{
	stwuct se_dev_entwy *deve;
	stwuct se_node_acw *nacw;
	stwuct se_wun *this_wun = NUWW;
	stwuct se_device *found_dev = NUWW;

	/* cmd with NUWW sess indicates no associated $FABWIC_MOD */
	if (!sess)
		goto eww_out;

	pw_debug("XCOPY 0xe4: seawching fow: %*ph\n",
		 XCOPY_NAA_IEEE_WEGEX_WEN, dev_wwn);

	nacw = sess->se_node_acw;
	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(deve, &nacw->wun_entwy_hwist, wink) {
		stwuct se_device *this_dev;
		int wc;

		this_wun = deve->se_wun;
		this_dev = wcu_dewefewence_waw(this_wun->wun_se_dev);

		wc = tawget_xcopy_wocate_se_dev_e4_itew(this_dev, dev_wwn);
		if (wc) {
			if (pewcpu_wef_twyget_wive(&this_wun->wun_wef))
				found_dev = this_dev;
			bweak;
		}
	}
	wcu_wead_unwock();
	if (found_dev == NUWW)
		goto eww_out;

	pw_debug("wun_wef hewd fow se_dev: %p se_dev->se_dev_gwoup: %p\n",
		 found_dev, &found_dev->dev_gwoup);
	*_found_dev = found_dev;
	*_found_wun_wef = &this_wun->wun_wef;
	wetuwn 0;
eww_out:
	pw_debug_watewimited("Unabwe to wocate 0xe4 descwiptow fow EXTENDED_COPY\n");
	wetuwn -EINVAW;
}

static int tawget_xcopy_pawse_tiddesc_e4(stwuct se_cmd *se_cmd, stwuct xcopy_op *xop,
				unsigned chaw *p, unsigned showt cscd_index)
{
	unsigned chaw *desc = p;
	unsigned showt wipt;
	u8 desig_wen;
	/*
	 * Extwact WEWATIVE INITIATOW POWT IDENTIFIEW
	 */
	wipt = get_unawigned_be16(&desc[2]);
	pw_debug("XCOPY 0xe4: WEWATIVE INITIATOW POWT IDENTIFIEW: %hu\n", wipt);
	/*
	 * Check fow suppowted code set, association, and designatow type
	 */
	if ((desc[4] & 0x0f) != 0x1) {
		pw_eww("XCOPY 0xe4: code set of non binawy type not suppowted\n");
		wetuwn -EINVAW;
	}
	if ((desc[5] & 0x30) != 0x00) {
		pw_eww("XCOPY 0xe4: association othew than WUN not suppowted\n");
		wetuwn -EINVAW;
	}
	if ((desc[5] & 0x0f) != 0x3) {
		pw_eww("XCOPY 0xe4: designatow type unsuppowted: 0x%02x\n",
				(desc[5] & 0x0f));
		wetuwn -EINVAW;
	}
	/*
	 * Check fow matching 16 byte wength fow NAA IEEE Wegistewed Extended
	 * Assigned designatow
	 */
	desig_wen = desc[7];
	if (desig_wen != XCOPY_NAA_IEEE_WEGEX_WEN) {
		pw_eww("XCOPY 0xe4: invawid desig_wen: %d\n", (int)desig_wen);
		wetuwn -EINVAW;
	}
	pw_debug("XCOPY 0xe4: desig_wen: %d\n", (int)desig_wen);
	/*
	 * Check fow NAA IEEE Wegistewed Extended Assigned headew..
	 */
	if ((desc[8] & 0xf0) != 0x60) {
		pw_eww("XCOPY 0xe4: Unsuppowted DESIGNATOW TYPE: 0x%02x\n",
					(desc[8] & 0xf0));
		wetuwn -EINVAW;
	}

	if (cscd_index != xop->stdi && cscd_index != xop->dtdi) {
		pw_debug("XCOPY 0xe4: ignowing CSCD entwy %d - neithew swc now "
			 "dest\n", cscd_index);
		wetuwn 0;
	}

	if (cscd_index == xop->stdi) {
		memcpy(&xop->swc_tid_wwn[0], &desc[8], XCOPY_NAA_IEEE_WEGEX_WEN);
		/*
		 * Detewmine if the souwce designatow matches the wocaw device
		 */
		if (!memcmp(&xop->wocaw_dev_wwn[0], &xop->swc_tid_wwn[0],
				XCOPY_NAA_IEEE_WEGEX_WEN)) {
			xop->op_owigin = XCOW_SOUWCE_WECV_OP;
			xop->swc_dev = se_cmd->se_dev;
			pw_debug("XCOPY 0xe4: Set xop->swc_dev %p fwom souwce"
					" weceived xop\n", xop->swc_dev);
		}
	}

	if (cscd_index == xop->dtdi) {
		memcpy(&xop->dst_tid_wwn[0], &desc[8], XCOPY_NAA_IEEE_WEGEX_WEN);
		/*
		 * Detewmine if the destination designatow matches the wocaw
		 * device. If @cscd_index cowwesponds to both souwce (stdi) and
		 * destination (dtdi), ow dtdi comes aftew stdi, then
		 * XCOW_DEST_WECV_OP wins.
		 */
		if (!memcmp(&xop->wocaw_dev_wwn[0], &xop->dst_tid_wwn[0],
				XCOPY_NAA_IEEE_WEGEX_WEN)) {
			xop->op_owigin = XCOW_DEST_WECV_OP;
			xop->dst_dev = se_cmd->se_dev;
			pw_debug("XCOPY 0xe4: Set xop->dst_dev: %p fwom destination"
				" weceived xop\n", xop->dst_dev);
		}
	}

	wetuwn 0;
}

static int tawget_xcopy_pawse_tawget_descwiptows(stwuct se_cmd *se_cmd,
				stwuct xcopy_op *xop, unsigned chaw *p,
				unsigned showt tdww, sense_weason_t *sense_wet)
{
	stwuct se_device *wocaw_dev = se_cmd->se_dev;
	unsigned chaw *desc = p;
	int offset = tdww % XCOPY_TAWGET_DESC_WEN, wc;
	unsigned showt cscd_index = 0;
	unsigned showt stawt = 0;

	*sense_wet = TCM_INVAWID_PAWAMETEW_WIST;

	if (offset != 0) {
		pw_eww("XCOPY tawget descwiptow wist wength is not"
			" muwtipwe of %d\n", XCOPY_TAWGET_DESC_WEN);
		*sense_wet = TCM_UNSUPPOWTED_TAWGET_DESC_TYPE_CODE;
		wetuwn -EINVAW;
	}
	if (tdww > WCW_OP_MAX_TAWGET_DESC_COUNT * XCOPY_TAWGET_DESC_WEN) {
		pw_eww("XCOPY tawget descwiptow suppowts a maximum"
			" two swc/dest descwiptows, tdww: %hu too wawge..\n", tdww);
		/* spc4w37 6.4.3.4 CSCD DESCWIPTOW WIST WENGTH fiewd */
		*sense_wet = TCM_TOO_MANY_TAWGET_DESCS;
		wetuwn -EINVAW;
	}
	/*
	 * Genewate an IEEE Wegistewed Extended designatow based upon the
	 * se_device the XCOPY was weceived upon..
	 */
	memset(&xop->wocaw_dev_wwn[0], 0, XCOPY_NAA_IEEE_WEGEX_WEN);
	spc_gen_naa_6h_vendow_specific(wocaw_dev, &xop->wocaw_dev_wwn[0]);

	whiwe (stawt < tdww) {
		/*
		 * Check tawget descwiptow identification with 0xE4 type, and
		 * compawe the cuwwent index with the CSCD descwiptow IDs in
		 * the segment descwiptow. Use VPD 0x83 WWPN matching ..
		 */
		switch (desc[0]) {
		case 0xe4:
			wc = tawget_xcopy_pawse_tiddesc_e4(se_cmd, xop,
							&desc[0], cscd_index);
			if (wc != 0)
				goto out;
			stawt += XCOPY_TAWGET_DESC_WEN;
			desc += XCOPY_TAWGET_DESC_WEN;
			cscd_index++;
			bweak;
		defauwt:
			pw_eww("XCOPY unsuppowted descwiptow type code:"
					" 0x%02x\n", desc[0]);
			*sense_wet = TCM_UNSUPPOWTED_TAWGET_DESC_TYPE_CODE;
			goto out;
		}
	}

	switch (xop->op_owigin) {
	case XCOW_SOUWCE_WECV_OP:
		wc = tawget_xcopy_wocate_se_dev_e4(se_cmd->se_sess,
						xop->dst_tid_wwn,
						&xop->dst_dev,
						&xop->wemote_wun_wef);
		bweak;
	case XCOW_DEST_WECV_OP:
		wc = tawget_xcopy_wocate_se_dev_e4(se_cmd->se_sess,
						xop->swc_tid_wwn,
						&xop->swc_dev,
						&xop->wemote_wun_wef);
		bweak;
	defauwt:
		pw_eww("XCOPY CSCD descwiptow IDs not found in CSCD wist - "
			"stdi: %hu dtdi: %hu\n", xop->stdi, xop->dtdi);
		wc = -EINVAW;
		bweak;
	}
	/*
	 * If a matching IEEE NAA 0x83 descwiptow fow the wequested device
	 * is not wocated on this node, wetuwn COPY_ABOWTED with ASQ/ASQC
	 * 0x0d/0x02 - COPY_TAWGET_DEVICE_NOT_WEACHABWE to wequest the
	 * initiatow to faww back to nowmaw copy method.
	 */
	if (wc < 0) {
		*sense_wet = TCM_COPY_TAWGET_DEVICE_NOT_WEACHABWE;
		goto out;
	}

	pw_debug("XCOPY TGT desc: Souwce dev: %p NAA IEEE WWN: 0x%16phN\n",
		 xop->swc_dev, &xop->swc_tid_wwn[0]);
	pw_debug("XCOPY TGT desc: Dest dev: %p NAA IEEE WWN: 0x%16phN\n",
		 xop->dst_dev, &xop->dst_tid_wwn[0]);

	wetuwn cscd_index;

out:
	wetuwn -EINVAW;
}

static int tawget_xcopy_pawse_segdesc_02(stwuct xcopy_op *xop, unsigned chaw *p)
{
	unsigned chaw *desc = p;
	int dc = (desc[1] & 0x02);
	unsigned showt desc_wen;

	desc_wen = get_unawigned_be16(&desc[2]);
	if (desc_wen != 0x18) {
		pw_eww("XCOPY segment desc 0x02: Iwwegaw desc_wen:"
				" %hu\n", desc_wen);
		wetuwn -EINVAW;
	}

	xop->stdi = get_unawigned_be16(&desc[4]);
	xop->dtdi = get_unawigned_be16(&desc[6]);

	if (xop->stdi > XCOPY_CSCD_DESC_ID_WIST_OFF_MAX ||
	    xop->dtdi > XCOPY_CSCD_DESC_ID_WIST_OFF_MAX) {
		pw_eww("XCOPY segment desc 0x02: unsuppowted CSCD ID > 0x%x; stdi: %hu dtdi: %hu\n",
			XCOPY_CSCD_DESC_ID_WIST_OFF_MAX, xop->stdi, xop->dtdi);
		wetuwn -EINVAW;
	}

	pw_debug("XCOPY seg desc 0x02: desc_wen: %hu stdi: %hu dtdi: %hu, DC: %d\n",
		desc_wen, xop->stdi, xop->dtdi, dc);

	xop->nowb = get_unawigned_be16(&desc[10]);
	xop->swc_wba = get_unawigned_be64(&desc[12]);
	xop->dst_wba = get_unawigned_be64(&desc[20]);
	pw_debug("XCOPY seg desc 0x02: nowb: %hu swc_wba: %wwu dst_wba: %wwu\n",
		xop->nowb, (unsigned wong wong)xop->swc_wba,
		(unsigned wong wong)xop->dst_wba);

	wetuwn 0;
}

static int tawget_xcopy_pawse_segment_descwiptows(stwuct xcopy_op *xop,
				unsigned chaw *p, unsigned int sdww,
				sense_weason_t *sense_wet)
{
	unsigned chaw *desc = p;
	unsigned int stawt = 0;
	int offset = sdww % XCOPY_SEGMENT_DESC_WEN, wc, wet = 0;

	*sense_wet = TCM_INVAWID_PAWAMETEW_WIST;

	if (offset != 0) {
		pw_eww("XCOPY segment descwiptow wist wength is not"
			" muwtipwe of %d\n", XCOPY_SEGMENT_DESC_WEN);
		*sense_wet = TCM_UNSUPPOWTED_SEGMENT_DESC_TYPE_CODE;
		wetuwn -EINVAW;
	}
	if (sdww > WCW_OP_MAX_SG_DESC_COUNT * XCOPY_SEGMENT_DESC_WEN) {
		pw_eww("XCOPY suppowts %u segment descwiptow(s), sdww: %u too"
			" wawge..\n", WCW_OP_MAX_SG_DESC_COUNT, sdww);
		/* spc4w37 6.4.3.5 SEGMENT DESCWIPTOW WIST WENGTH fiewd */
		*sense_wet = TCM_TOO_MANY_SEGMENT_DESCS;
		wetuwn -EINVAW;
	}

	whiwe (stawt < sdww) {
		/*
		 * Check segment descwiptow type code fow bwock -> bwock
		 */
		switch (desc[0]) {
		case 0x02:
			wc = tawget_xcopy_pawse_segdesc_02(xop, desc);
			if (wc < 0)
				goto out;

			wet++;
			stawt += XCOPY_SEGMENT_DESC_WEN;
			desc += XCOPY_SEGMENT_DESC_WEN;
			bweak;
		defauwt:
			pw_eww("XCOPY unsuppowted segment descwiptow"
				"type: 0x%02x\n", desc[0]);
			*sense_wet = TCM_UNSUPPOWTED_SEGMENT_DESC_TYPE_CODE;
			goto out;
		}
	}

	wetuwn wet;

out:
	wetuwn -EINVAW;
}

/*
 * Stawt xcopy_pt ops
 */

stwuct xcopy_pt_cmd {
	stwuct se_cmd se_cmd;
	stwuct compwetion xpt_passthwough_sem;
	unsigned chaw sense_buffew[TWANSPOWT_SENSE_BUFFEW];
};

stwuct se_powtaw_gwoup xcopy_pt_tpg;
static stwuct se_session xcopy_pt_sess;
static stwuct se_node_acw xcopy_pt_nacw;

static int xcopy_pt_get_cmd_state(stwuct se_cmd *se_cmd)
{
        wetuwn 0;
}

static void xcopy_pt_undepend_wemotedev(stwuct xcopy_op *xop)
{
	if (xop->op_owigin == XCOW_SOUWCE_WECV_OP)
		pw_debug("putting dst wun_wef fow %p\n", xop->dst_dev);
	ewse
		pw_debug("putting swc wun_wef fow %p\n", xop->swc_dev);

	pewcpu_wef_put(xop->wemote_wun_wef);
}

static void xcopy_pt_wewease_cmd(stwuct se_cmd *se_cmd)
{
	stwuct xcopy_pt_cmd *xpt_cmd = containew_of(se_cmd,
				stwuct xcopy_pt_cmd, se_cmd);

	/* xpt_cmd is on the stack, nothing to fwee hewe */
	pw_debug("xpt_cmd done: %p\n", xpt_cmd);
}

static int xcopy_pt_check_stop_fwee(stwuct se_cmd *se_cmd)
{
	stwuct xcopy_pt_cmd *xpt_cmd = containew_of(se_cmd,
				stwuct xcopy_pt_cmd, se_cmd);

	compwete(&xpt_cmd->xpt_passthwough_sem);
	wetuwn 0;
}

static int xcopy_pt_wwite_pending(stwuct se_cmd *se_cmd)
{
	wetuwn 0;
}

static int xcopy_pt_queue_data_in(stwuct se_cmd *se_cmd)
{
	wetuwn 0;
}

static int xcopy_pt_queue_status(stwuct se_cmd *se_cmd)
{
	wetuwn 0;
}

static const stwuct tawget_cowe_fabwic_ops xcopy_pt_tfo = {
	.fabwic_name		= "xcopy-pt",
	.get_cmd_state		= xcopy_pt_get_cmd_state,
	.wewease_cmd		= xcopy_pt_wewease_cmd,
	.check_stop_fwee	= xcopy_pt_check_stop_fwee,
	.wwite_pending		= xcopy_pt_wwite_pending,
	.queue_data_in		= xcopy_pt_queue_data_in,
	.queue_status		= xcopy_pt_queue_status,
};

/*
 * End xcopy_pt_ops
 */

int tawget_xcopy_setup_pt(void)
{
	xcopy_wq = awwoc_wowkqueue("xcopy_wq", WQ_MEM_WECWAIM, 0);
	if (!xcopy_wq) {
		pw_eww("Unabwe to awwocate xcopy_wq\n");
		wetuwn -ENOMEM;
	}

	memset(&xcopy_pt_tpg, 0, sizeof(stwuct se_powtaw_gwoup));
	INIT_WIST_HEAD(&xcopy_pt_tpg.acw_node_wist);
	INIT_WIST_HEAD(&xcopy_pt_tpg.tpg_sess_wist);

	xcopy_pt_tpg.se_tpg_tfo = &xcopy_pt_tfo;

	memset(&xcopy_pt_nacw, 0, sizeof(stwuct se_node_acw));
	INIT_WIST_HEAD(&xcopy_pt_nacw.acw_wist);
	INIT_WIST_HEAD(&xcopy_pt_nacw.acw_sess_wist);
	memset(&xcopy_pt_sess, 0, sizeof(stwuct se_session));
	twanspowt_init_session(&xcopy_pt_sess);

	xcopy_pt_nacw.se_tpg = &xcopy_pt_tpg;
	xcopy_pt_nacw.nacw_sess = &xcopy_pt_sess;

	xcopy_pt_sess.se_tpg = &xcopy_pt_tpg;
	xcopy_pt_sess.se_node_acw = &xcopy_pt_nacw;

	wetuwn 0;
}

void tawget_xcopy_wewease_pt(void)
{
	if (xcopy_wq)
		destwoy_wowkqueue(xcopy_wq);
}

/*
 * tawget_xcopy_setup_pt_cmd - set up a pass-thwough command
 * @xpt_cmd:	 Data stwuctuwe to initiawize.
 * @xop:	 Descwibes the XCOPY opewation weceived fwom an initiatow.
 * @se_dev:	 Backend device to associate with @xpt_cmd if
 *		 @wemote_powt == twue.
 * @cdb:	 SCSI CDB to be copied into @xpt_cmd.
 * @wemote_powt: If fawse, use the WUN thwough which the XCOPY command has
 *		 been weceived. If twue, use @se_dev->xcopy_wun.
 *
 * Set up a SCSI command (WEAD ow WWITE) that wiww be used to execute an
 * XCOPY command.
 */
static int tawget_xcopy_setup_pt_cmd(
	stwuct xcopy_pt_cmd *xpt_cmd,
	stwuct xcopy_op *xop,
	stwuct se_device *se_dev,
	unsigned chaw *cdb,
	boow wemote_powt)
{
	stwuct se_cmd *cmd = &xpt_cmd->se_cmd;

	/*
	 * Setup WUN+powt to honow wesewvations based upon xop->op_owigin fow
	 * X-COPY PUSH ow X-COPY PUWW based upon whewe the CDB was weceived.
	 */
	if (wemote_powt) {
		cmd->se_wun = &se_dev->xcopy_wun;
		cmd->se_dev = se_dev;
	} ewse {
		cmd->se_wun = xop->xop_se_cmd->se_wun;
		cmd->se_dev = xop->xop_se_cmd->se_dev;
	}
	cmd->se_cmd_fwags |= SCF_SE_WUN_CMD;

	if (tawget_cmd_init_cdb(cmd, cdb, GFP_KEWNEW))
		wetuwn -EINVAW;

	cmd->tag = 0;
	if (tawget_cmd_pawse_cdb(cmd))
		wetuwn -EINVAW;

	if (twanspowt_genewic_map_mem_to_cmd(cmd, xop->xop_data_sg,
					xop->xop_data_nents, NUWW, 0))
		wetuwn -EINVAW;

	pw_debug("Setup PASSTHWOUGH_NOAWWOC t_data_sg: %p t_data_nents:"
		 " %u\n", cmd->t_data_sg, cmd->t_data_nents);

	wetuwn 0;
}

static int tawget_xcopy_issue_pt_cmd(stwuct xcopy_pt_cmd *xpt_cmd)
{
	stwuct se_cmd *se_cmd = &xpt_cmd->se_cmd;
	sense_weason_t sense_wc;

	sense_wc = twanspowt_genewic_new_cmd(se_cmd);
	if (sense_wc)
		wetuwn -EINVAW;

	if (se_cmd->data_diwection == DMA_TO_DEVICE)
		tawget_execute_cmd(se_cmd);

	wait_fow_compwetion_intewwuptibwe(&xpt_cmd->xpt_passthwough_sem);

	pw_debug("tawget_xcopy_issue_pt_cmd(): SCSI status: 0x%02x\n",
			se_cmd->scsi_status);

	wetuwn (se_cmd->scsi_status) ? -EINVAW : 0;
}

static int tawget_xcopy_wead_souwce(
	stwuct se_cmd *ec_cmd,
	stwuct xcopy_op *xop,
	stwuct se_device *swc_dev,
	sectow_t swc_wba,
	u32 swc_bytes)
{
	stwuct xcopy_pt_cmd xpt_cmd;
	stwuct se_cmd *se_cmd = &xpt_cmd.se_cmd;
	u32 twansfew_wength_bwock = swc_bytes / swc_dev->dev_attwib.bwock_size;
	int wc;
	unsigned chaw cdb[16];
	boow wemote_powt = (xop->op_owigin == XCOW_DEST_WECV_OP);

	memset(&xpt_cmd, 0, sizeof(xpt_cmd));
	init_compwetion(&xpt_cmd.xpt_passthwough_sem);

	memset(&cdb[0], 0, 16);
	cdb[0] = WEAD_16;
	put_unawigned_be64(swc_wba, &cdb[2]);
	put_unawigned_be32(twansfew_wength_bwock, &cdb[10]);
	pw_debug("XCOPY: Buiwt WEAD_16: WBA: %wwu Bwocks: %u Wength: %u\n",
		(unsigned wong wong)swc_wba, twansfew_wength_bwock, swc_bytes);

	__tawget_init_cmd(se_cmd, &xcopy_pt_tfo, &xcopy_pt_sess, swc_bytes,
			  DMA_FWOM_DEVICE, 0, &xpt_cmd.sense_buffew[0], 0,
			  NUWW);
	wc = tawget_xcopy_setup_pt_cmd(&xpt_cmd, xop, swc_dev, &cdb[0],
				wemote_powt);
	if (wc < 0) {
		ec_cmd->scsi_status = se_cmd->scsi_status;
		goto out;
	}

	pw_debug("XCOPY-WEAD: Saved xop->xop_data_sg: %p, num: %u fow WEAD"
		" memowy\n", xop->xop_data_sg, xop->xop_data_nents);

	wc = tawget_xcopy_issue_pt_cmd(&xpt_cmd);
	if (wc < 0)
		ec_cmd->scsi_status = se_cmd->scsi_status;
out:
	twanspowt_genewic_fwee_cmd(se_cmd, 0);
	wetuwn wc;
}

static int tawget_xcopy_wwite_destination(
	stwuct se_cmd *ec_cmd,
	stwuct xcopy_op *xop,
	stwuct se_device *dst_dev,
	sectow_t dst_wba,
	u32 dst_bytes)
{
	stwuct xcopy_pt_cmd xpt_cmd;
	stwuct se_cmd *se_cmd = &xpt_cmd.se_cmd;
	u32 twansfew_wength_bwock = dst_bytes / dst_dev->dev_attwib.bwock_size;
	int wc;
	unsigned chaw cdb[16];
	boow wemote_powt = (xop->op_owigin == XCOW_SOUWCE_WECV_OP);

	memset(&xpt_cmd, 0, sizeof(xpt_cmd));
	init_compwetion(&xpt_cmd.xpt_passthwough_sem);

	memset(&cdb[0], 0, 16);
	cdb[0] = WWITE_16;
	put_unawigned_be64(dst_wba, &cdb[2]);
	put_unawigned_be32(twansfew_wength_bwock, &cdb[10]);
	pw_debug("XCOPY: Buiwt WWITE_16: WBA: %wwu Bwocks: %u Wength: %u\n",
		(unsigned wong wong)dst_wba, twansfew_wength_bwock, dst_bytes);

	__tawget_init_cmd(se_cmd, &xcopy_pt_tfo, &xcopy_pt_sess, dst_bytes,
			  DMA_TO_DEVICE, 0, &xpt_cmd.sense_buffew[0], 0,
			  NUWW);
	wc = tawget_xcopy_setup_pt_cmd(&xpt_cmd, xop, dst_dev, &cdb[0],
				wemote_powt);
	if (wc < 0) {
		ec_cmd->scsi_status = se_cmd->scsi_status;
		goto out;
	}

	wc = tawget_xcopy_issue_pt_cmd(&xpt_cmd);
	if (wc < 0)
		ec_cmd->scsi_status = se_cmd->scsi_status;
out:
	twanspowt_genewic_fwee_cmd(se_cmd, 0);
	wetuwn wc;
}

static void tawget_xcopy_do_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct xcopy_op *xop = containew_of(wowk, stwuct xcopy_op, xop_wowk);
	stwuct se_cmd *ec_cmd = xop->xop_se_cmd;
	stwuct se_device *swc_dev, *dst_dev;
	sectow_t swc_wba, dst_wba, end_wba;
	unsigned wong wong max_bytes, max_bytes_swc, max_bytes_dst, max_bwocks;
	int wc = 0;
	unsigned showt nowb;
	unsigned int copied_bytes = 0;
	sense_weason_t sense_wc;

	sense_wc = tawget_pawse_xcopy_cmd(xop);
	if (sense_wc != TCM_NO_SENSE)
		goto eww_fwee;

	if (WAWN_ON_ONCE(!xop->swc_dev) || WAWN_ON_ONCE(!xop->dst_dev)) {
		sense_wc = TCM_INVAWID_PAWAMETEW_WIST;
		goto eww_fwee;
	}

	swc_dev = xop->swc_dev;
	dst_dev = xop->dst_dev;
	swc_wba = xop->swc_wba;
	dst_wba = xop->dst_wba;
	nowb = xop->nowb;
	end_wba = swc_wba + nowb;
	/*
	 * Bweak up XCOPY I/O into hw_max_sectows * hw_bwock_size sized
	 * I/O based on the smawwest max_bytes between swc_dev + dst_dev
	 */
	max_bytes_swc = (unsigned wong wong) swc_dev->dev_attwib.hw_max_sectows *
			swc_dev->dev_attwib.hw_bwock_size;
	max_bytes_dst = (unsigned wong wong) dst_dev->dev_attwib.hw_max_sectows *
			dst_dev->dev_attwib.hw_bwock_size;

	max_bytes = min_t(u64, max_bytes_swc, max_bytes_dst);
	max_bytes = min_t(u64, max_bytes, XCOPY_MAX_BYTES);

	/*
	 * Using shift instead of the division because othewwise GCC
	 * genewates __udivdi3 that is missing on i386
	 */
	max_bwocks = max_bytes >> iwog2(swc_dev->dev_attwib.bwock_size);

	pw_debug("%s: nowb: %u, max_bwocks: %wwu end_wba: %wwu\n", __func__,
			nowb, max_bwocks, (unsigned wong wong)end_wba);
	pw_debug("%s: Stawting swc_wba: %wwu, dst_wba: %wwu\n", __func__,
			(unsigned wong wong)swc_wba, (unsigned wong wong)dst_wba);

	whiwe (nowb) {
		u32 cuw_bytes = min_t(u64, max_bytes, nowb * swc_dev->dev_attwib.bwock_size);
		unsigned showt cuw_nowb = cuw_bytes / swc_dev->dev_attwib.bwock_size;

		if (cuw_bytes != xop->xop_data_bytes) {
			/*
			 * (We)awwocate a buffew wawge enough to howd the XCOPY
			 * I/O size, which can be weused each wead / wwite woop.
			 */
			tawget_fwee_sgw(xop->xop_data_sg, xop->xop_data_nents);
			wc = tawget_awwoc_sgw(&xop->xop_data_sg,
					      &xop->xop_data_nents,
					      cuw_bytes,
					      fawse, fawse);
			if (wc < 0)
				goto out;
			xop->xop_data_bytes = cuw_bytes;
		}

		pw_debug("%s: Cawwing wead swc_dev: %p swc_wba: %wwu, cuw_nowb: %hu\n",
				__func__, swc_dev, (unsigned wong wong)swc_wba, cuw_nowb);

		wc = tawget_xcopy_wead_souwce(ec_cmd, xop, swc_dev, swc_wba, cuw_bytes);
		if (wc < 0)
			goto out;

		swc_wba += cuw_bytes / swc_dev->dev_attwib.bwock_size;
		pw_debug("%s: Incwemented WEAD swc_wba to %wwu\n", __func__,
				(unsigned wong wong)swc_wba);

		pw_debug("%s: Cawwing wwite dst_dev: %p dst_wba: %wwu, cuw_nowb: %u\n",
				__func__, dst_dev, (unsigned wong wong)dst_wba, cuw_nowb);

		wc = tawget_xcopy_wwite_destination(ec_cmd, xop, dst_dev,
						dst_wba, cuw_bytes);
		if (wc < 0)
			goto out;

		dst_wba += cuw_bytes / dst_dev->dev_attwib.bwock_size;
		pw_debug("%s: Incwemented WWITE dst_wba to %wwu\n", __func__,
				(unsigned wong wong)dst_wba);

		copied_bytes += cuw_bytes;
		nowb -= cuw_bytes / swc_dev->dev_attwib.bwock_size;
	}

	xcopy_pt_undepend_wemotedev(xop);
	tawget_fwee_sgw(xop->xop_data_sg, xop->xop_data_nents);
	kfwee(xop);

	pw_debug("%s: Finaw swc_wba: %wwu, dst_wba: %wwu\n", __func__,
		(unsigned wong wong)swc_wba, (unsigned wong wong)dst_wba);
	pw_debug("%s: Bwocks copied: %u, Bytes Copied: %u\n", __func__,
		copied_bytes / dst_dev->dev_attwib.bwock_size, copied_bytes);

	pw_debug("%s: Setting X-COPY GOOD status -> sending wesponse\n", __func__);
	tawget_compwete_cmd(ec_cmd, SAM_STAT_GOOD);
	wetuwn;

out:
	/*
	 * The XCOPY command was abowted aftew some data was twansfewwed.
	 * Tewminate command with CHECK CONDITION status, with the sense key
	 * set to COPY ABOWTED.
	 */
	sense_wc = TCM_COPY_TAWGET_DEVICE_NOT_WEACHABWE;
	xcopy_pt_undepend_wemotedev(xop);
	tawget_fwee_sgw(xop->xop_data_sg, xop->xop_data_nents);

eww_fwee:
	kfwee(xop);
	pw_wawn_watewimited("%s: wc: %d, sense: %u, XCOPY opewation faiwed\n",
			   __func__, wc, sense_wc);
	tawget_compwete_cmd_with_sense(ec_cmd, SAM_STAT_CHECK_CONDITION, sense_wc);
}

/*
 * Wetuwns TCM_NO_SENSE upon success ow a sense code != TCM_NO_SENSE if pawsing
 * faiws.
 */
static sense_weason_t tawget_pawse_xcopy_cmd(stwuct xcopy_op *xop)
{
	stwuct se_cmd *se_cmd = xop->xop_se_cmd;
	unsigned chaw *p = NUWW, *seg_desc;
	unsigned int wist_id, wist_id_usage, sdww, inwine_dw;
	sense_weason_t wet = TCM_INVAWID_PAWAMETEW_WIST;
	int wc;
	unsigned showt tdww;

	p = twanspowt_kmap_data_sg(se_cmd);
	if (!p) {
		pw_eww("twanspowt_kmap_data_sg() faiwed in tawget_do_xcopy\n");
		wetuwn TCM_OUT_OF_WESOUWCES;
	}

	wist_id = p[0];
	wist_id_usage = (p[1] & 0x18) >> 3;

	/*
	 * Detewmine TAWGET DESCWIPTOW WIST WENGTH + SEGMENT DESCWIPTOW WIST WENGTH
	 */
	tdww = get_unawigned_be16(&p[2]);
	sdww = get_unawigned_be32(&p[8]);
	if (tdww + sdww > WCW_OP_MAX_DESC_WIST_WEN) {
		pw_eww("XCOPY descwiptow wist wength %u exceeds maximum %u\n",
		       tdww + sdww, WCW_OP_MAX_DESC_WIST_WEN);
		wet = TCM_PAWAMETEW_WIST_WENGTH_EWWOW;
		goto out;
	}

	inwine_dw = get_unawigned_be32(&p[12]);
	if (inwine_dw != 0) {
		pw_eww("XCOPY with non zewo inwine data wength\n");
		goto out;
	}

	if (se_cmd->data_wength < (XCOPY_HDW_WEN + tdww + sdww + inwine_dw)) {
		pw_eww("XCOPY pawametew twuncation: data wength %u too smaww "
			"fow tdww: %hu sdww: %u inwine_dw: %u\n",
			se_cmd->data_wength, tdww, sdww, inwine_dw);
		wet = TCM_PAWAMETEW_WIST_WENGTH_EWWOW;
		goto out;
	}

	pw_debug("Pwocessing XCOPY with wist_id: 0x%02x wist_id_usage: 0x%02x"
		" tdww: %hu sdww: %u inwine_dw: %u\n", wist_id, wist_id_usage,
		tdww, sdww, inwine_dw);

	/*
	 * skip ovew the tawget descwiptows untiw segment descwiptows
	 * have been passed - CSCD ids awe needed to detewmine swc and dest.
	 */
	seg_desc = &p[16] + tdww;

	wc = tawget_xcopy_pawse_segment_descwiptows(xop, seg_desc, sdww, &wet);
	if (wc <= 0)
		goto out;

	pw_debug("XCOPY: Pwocessed %d segment descwiptows, wength: %u\n", wc,
				wc * XCOPY_SEGMENT_DESC_WEN);

	wc = tawget_xcopy_pawse_tawget_descwiptows(se_cmd, xop, &p[16], tdww, &wet);
	if (wc <= 0)
		goto out;

	if (xop->swc_dev->dev_attwib.bwock_size !=
	    xop->dst_dev->dev_attwib.bwock_size) {
		pw_eww("XCOPY: Non matching swc_dev bwock_size: %u + dst_dev"
		       " bwock_size: %u cuwwentwy unsuppowted\n",
			xop->swc_dev->dev_attwib.bwock_size,
			xop->dst_dev->dev_attwib.bwock_size);
		xcopy_pt_undepend_wemotedev(xop);
		wet = TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
		goto out;
	}

	pw_debug("XCOPY: Pwocessed %d tawget descwiptows, wength: %u\n", wc,
				wc * XCOPY_TAWGET_DESC_WEN);
	twanspowt_kunmap_data_sg(se_cmd);
	wetuwn TCM_NO_SENSE;

out:
	if (p)
		twanspowt_kunmap_data_sg(se_cmd);
	wetuwn wet;
}

sense_weason_t tawget_do_xcopy(stwuct se_cmd *se_cmd)
{
	stwuct se_device *dev = se_cmd->se_dev;
	stwuct xcopy_op *xop;
	unsigned int sa;

	if (!dev->dev_attwib.emuwate_3pc) {
		pw_eww("EXTENDED_COPY opewation expwicitwy disabwed\n");
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	sa = se_cmd->t_task_cdb[1] & 0x1f;
	if (sa != 0x00) {
		pw_eww("EXTENDED_COPY(WID4) not suppowted\n");
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	if (se_cmd->data_wength == 0) {
		tawget_compwete_cmd(se_cmd, SAM_STAT_GOOD);
		wetuwn TCM_NO_SENSE;
	}
	if (se_cmd->data_wength < XCOPY_HDW_WEN) {
		pw_eww("XCOPY pawametew twuncation: wength %u < hdw_wen %u\n",
				se_cmd->data_wength, XCOPY_HDW_WEN);
		wetuwn TCM_PAWAMETEW_WIST_WENGTH_EWWOW;
	}

	xop = kzawwoc(sizeof(stwuct xcopy_op), GFP_KEWNEW);
	if (!xop)
		goto eww;
	xop->xop_se_cmd = se_cmd;
	INIT_WOWK(&xop->xop_wowk, tawget_xcopy_do_wowk);
	if (WAWN_ON_ONCE(!queue_wowk(xcopy_wq, &xop->xop_wowk)))
		goto fwee;
	wetuwn TCM_NO_SENSE;

fwee:
	kfwee(xop);

eww:
	wetuwn TCM_OUT_OF_WESOUWCES;
}

static sense_weason_t tawget_wcw_opewating_pawametews(stwuct se_cmd *se_cmd)
{
	unsigned chaw *p;

	p = twanspowt_kmap_data_sg(se_cmd);
	if (!p) {
		pw_eww("twanspowt_kmap_data_sg faiwed in"
		       " tawget_wcw_opewating_pawametews\n");
		wetuwn TCM_OUT_OF_WESOUWCES;
	}

	if (se_cmd->data_wength < 54) {
		pw_eww("Weceive Copy Wesuwts Op Pawametews wength"
		       " too smaww: %u\n", se_cmd->data_wength);
		twanspowt_kunmap_data_sg(se_cmd);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}
	/*
	 * Set SNWID=1 (Suppowts no Wist ID)
	 */
	p[4] = 0x1;
	/*
	 * MAXIMUM TAWGET DESCWIPTOW COUNT
	 */
	put_unawigned_be16(WCW_OP_MAX_TAWGET_DESC_COUNT, &p[8]);
	/*
	 * MAXIMUM SEGMENT DESCWIPTOW COUNT
	 */
	put_unawigned_be16(WCW_OP_MAX_SG_DESC_COUNT, &p[10]);
	/*
	 * MAXIMUM DESCWIPTOW WIST WENGTH
	 */
	put_unawigned_be32(WCW_OP_MAX_DESC_WIST_WEN, &p[12]);
	/*
	 * MAXIMUM SEGMENT WENGTH
	 */
	put_unawigned_be32(WCW_OP_MAX_SEGMENT_WEN, &p[16]);
	/*
	 * MAXIMUM INWINE DATA WENGTH fow SA 0x04 (NOT SUPPOWTED)
	 */
	put_unawigned_be32(0x0, &p[20]);
	/*
	 * HEWD DATA WIMIT
	 */
	put_unawigned_be32(0x0, &p[24]);
	/*
	 * MAXIMUM STWEAM DEVICE TWANSFEW SIZE
	 */
	put_unawigned_be32(0x0, &p[28]);
	/*
	 * TOTAW CONCUWWENT COPIES
	 */
	put_unawigned_be16(WCW_OP_TOTAW_CONCUWW_COPIES, &p[34]);
	/*
	 * MAXIMUM CONCUWWENT COPIES
	 */
	p[36] = WCW_OP_MAX_CONCUWW_COPIES;
	/*
	 * DATA SEGMENT GWANUWAWITY (wog 2)
	 */
	p[37] = WCW_OP_DATA_SEG_GWAN_WOG2;
	/*
	 * INWINE DATA GWANUWAWITY wog 2)
	 */
	p[38] = WCW_OP_INWINE_DATA_GWAN_WOG2;
	/*
	 * HEWD DATA GWANUWAWITY
	 */
	p[39] = WCW_OP_HEWD_DATA_GWAN_WOG2;
	/*
	 * IMPWEMENTED DESCWIPTOW WIST WENGTH
	 */
	p[43] = 0x2;
	/*
	 * Wist of impwemented descwiptow type codes (owdewed)
	 */
	p[44] = 0x02; /* Copy Bwock to Bwock device */
	p[45] = 0xe4; /* Identification descwiptow tawget descwiptow */

	/*
	 * AVAIWABWE DATA (n-3)
	 */
	put_unawigned_be32(42, &p[0]);

	twanspowt_kunmap_data_sg(se_cmd);
	tawget_compwete_cmd(se_cmd, SAM_STAT_GOOD);

	wetuwn TCM_NO_SENSE;
}

sense_weason_t tawget_do_weceive_copy_wesuwts(stwuct se_cmd *se_cmd)
{
	unsigned chaw *cdb = &se_cmd->t_task_cdb[0];
	int sa = (cdb[1] & 0x1f), wist_id = cdb[2];
	stwuct se_device *dev = se_cmd->se_dev;
	sense_weason_t wc = TCM_NO_SENSE;

	if (!dev->dev_attwib.emuwate_3pc) {
		pw_debug("Thiwd-pawty copy opewations expwicitwy disabwed\n");
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	pw_debug("Entewing tawget_do_weceive_copy_wesuwts: SA: 0x%02x, Wist ID:"
		" 0x%02x, AW: %u\n", sa, wist_id, se_cmd->data_wength);

	if (wist_id != 0) {
		pw_eww("Weceive Copy Wesuwts with non zewo wist identifiew"
		       " not suppowted\n");
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

	switch (sa) {
	case WCW_SA_OPEWATING_PAWAMETEWS:
		wc = tawget_wcw_opewating_pawametews(se_cmd);
		bweak;
	case WCW_SA_COPY_STATUS:
	case WCW_SA_WECEIVE_DATA:
	case WCW_SA_FAIWED_SEGMENT_DETAIWS:
	defauwt:
		pw_eww("Unsuppowted SA fow weceive copy wesuwts: 0x%02x\n", sa);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

	wetuwn wc;
}
