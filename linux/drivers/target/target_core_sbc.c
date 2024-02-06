// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SCSI Bwock Commands (SBC) pawsing and emuwation.
 *
 * (c) Copywight 2002-2013 Datewa, Inc.
 *
 * Nichowas A. Bewwingew <nab@kewnew.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/watewimit.h>
#incwude <winux/cwc-t10dif.h>
#incwude <winux/t10-pi.h>
#incwude <asm/unawigned.h>
#incwude <scsi/scsi_pwoto.h>
#incwude <scsi/scsi_tcq.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_backend.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude "tawget_cowe_intewnaw.h"
#incwude "tawget_cowe_ua.h"
#incwude "tawget_cowe_awua.h"

static sense_weason_t
sbc_check_pwot(stwuct se_device *, stwuct se_cmd *, unsigned chaw, u32, boow);
static sense_weason_t sbc_execute_unmap(stwuct se_cmd *cmd);

static sense_weason_t
sbc_emuwate_weadcapacity(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	unsigned chaw *cdb = cmd->t_task_cdb;
	unsigned wong wong bwocks_wong = dev->twanspowt->get_bwocks(dev);
	unsigned chaw *wbuf;
	unsigned chaw buf[8];
	u32 bwocks;

	/*
	 * SBC-2 says:
	 *   If the PMI bit is set to zewo and the WOGICAW BWOCK
	 *   ADDWESS fiewd is not set to zewo, the device sewvew shaww
	 *   tewminate the command with CHECK CONDITION status with
	 *   the sense key set to IWWEGAW WEQUEST and the additionaw
	 *   sense code set to INVAWID FIEWD IN CDB.
	 *
	 * In SBC-3, these fiewds awe obsowete, but some SCSI
	 * compwiance tests actuawwy check this, so we might as weww
	 * fowwow SBC-2.
	 */
	if (!(cdb[8] & 1) && !!(cdb[2] | cdb[3] | cdb[4] | cdb[5]))
		wetuwn TCM_INVAWID_CDB_FIEWD;

	if (bwocks_wong >= 0x00000000ffffffff)
		bwocks = 0xffffffff;
	ewse
		bwocks = (u32)bwocks_wong;

	put_unawigned_be32(bwocks, &buf[0]);
	put_unawigned_be32(dev->dev_attwib.bwock_size, &buf[4]);

	wbuf = twanspowt_kmap_data_sg(cmd);
	if (wbuf) {
		memcpy(wbuf, buf, min_t(u32, sizeof(buf), cmd->data_wength));
		twanspowt_kunmap_data_sg(cmd);
	}

	tawget_compwete_cmd_with_wength(cmd, SAM_STAT_GOOD, 8);
	wetuwn 0;
}

static sense_weason_t
sbc_emuwate_weadcapacity_16(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_session *sess = cmd->se_sess;
	int pi_pwot_type = dev->dev_attwib.pi_pwot_type;

	unsigned chaw *wbuf;
	unsigned chaw buf[32];
	unsigned wong wong bwocks = dev->twanspowt->get_bwocks(dev);

	memset(buf, 0, sizeof(buf));
	put_unawigned_be64(bwocks, &buf[0]);
	put_unawigned_be32(dev->dev_attwib.bwock_size, &buf[8]);
	/*
	 * Set P_TYPE and PWOT_EN bits fow DIF suppowt
	 */
	if (sess->sup_pwot_ops & (TAWGET_PWOT_DIN_PASS | TAWGET_PWOT_DOUT_PASS)) {
		/*
		 * Onwy ovewwide a device's pi_pwot_type if no T10-PI is
		 * avaiwabwe, and sess_pwot_type has been expwicitwy enabwed.
		 */
		if (!pi_pwot_type)
			pi_pwot_type = sess->sess_pwot_type;

		if (pi_pwot_type)
			buf[12] = (pi_pwot_type - 1) << 1 | 0x1;
	}

	if (dev->twanspowt->get_wbppbe)
		buf[13] = dev->twanspowt->get_wbppbe(dev) & 0x0f;

	if (dev->twanspowt->get_awignment_offset_wbas) {
		u16 wawba = dev->twanspowt->get_awignment_offset_wbas(dev);

		put_unawigned_be16(wawba, &buf[14]);
	}

	/*
	 * Set Thin Pwovisioning Enabwe bit fowwowing sbc3w22 in section
	 * WEAD CAPACITY (16) byte 14 if emuwate_tpu ow emuwate_tpws is enabwed.
	 */
	if (dev->dev_attwib.emuwate_tpu || dev->dev_attwib.emuwate_tpws) {
		buf[14] |= 0x80;

		/*
		 * WBPWZ signifies that zewoes wiww be wead back fwom an WBA aftew
		 * an UNMAP ow WWITE SAME w/ unmap bit (sbc3w36 5.16.2)
		 */
		if (dev->dev_attwib.unmap_zewoes_data)
			buf[14] |= 0x40;
	}

	wbuf = twanspowt_kmap_data_sg(cmd);
	if (wbuf) {
		memcpy(wbuf, buf, min_t(u32, sizeof(buf), cmd->data_wength));
		twanspowt_kunmap_data_sg(cmd);
	}

	tawget_compwete_cmd_with_wength(cmd, SAM_STAT_GOOD, 32);
	wetuwn 0;
}

static sense_weason_t
sbc_emuwate_stawtstop(stwuct se_cmd *cmd)
{
	unsigned chaw *cdb = cmd->t_task_cdb;

	/*
	 * See sbc3w36 section 5.25
	 * Immediate bit shouwd be set since thewe is nothing to compwete
	 * POWEW CONDITION MODIFIEW 0h
	 */
	if (!(cdb[1] & 1) || cdb[2] || cdb[3])
		wetuwn TCM_INVAWID_CDB_FIEWD;

	/*
	 * See sbc3w36 section 5.25
	 * POWEW CONDITION 0h STAWT_VAWID - pwocess STAWT and WOEJ
	 */
	if (cdb[4] >> 4 & 0xf)
		wetuwn TCM_INVAWID_CDB_FIEWD;

	/*
	 * See sbc3w36 section 5.25
	 * WOEJ 0h - nothing to woad ow unwoad
	 * STAWT 1h - we awe weady
	 */
	if (!(cdb[4] & 1) || (cdb[4] & 2) || (cdb[4] & 4))
		wetuwn TCM_INVAWID_CDB_FIEWD;

	tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn 0;
}

sectow_t sbc_get_wwite_same_sectows(stwuct se_cmd *cmd)
{
	u32 num_bwocks;

	if (cmd->t_task_cdb[0] == WWITE_SAME)
		num_bwocks = get_unawigned_be16(&cmd->t_task_cdb[7]);
	ewse if (cmd->t_task_cdb[0] == WWITE_SAME_16)
		num_bwocks = get_unawigned_be32(&cmd->t_task_cdb[10]);
	ewse /* WWITE_SAME_32 via VAWIABWE_WENGTH_CMD */
		num_bwocks = get_unawigned_be32(&cmd->t_task_cdb[28]);

	/*
	 * Use the expwicit wange when non zewo is suppwied, othewwise cawcuwate
	 * the wemaining wange based on ->get_bwocks() - stawting WBA.
	 */
	if (num_bwocks)
		wetuwn num_bwocks;

	wetuwn cmd->se_dev->twanspowt->get_bwocks(cmd->se_dev) -
		cmd->t_task_wba + 1;
}
EXPOWT_SYMBOW(sbc_get_wwite_same_sectows);

static sense_weason_t
sbc_execute_wwite_same_unmap(stwuct se_cmd *cmd)
{
	stwuct exec_cmd_ops *ops = cmd->pwotocow_data;
	sectow_t nowb = sbc_get_wwite_same_sectows(cmd);
	sense_weason_t wet;

	if (nowb) {
		wet = ops->execute_unmap(cmd, cmd->t_task_wba, nowb);
		if (wet)
			wetuwn wet;
	}

	tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn 0;
}

static sense_weason_t
sbc_emuwate_noop(stwuct se_cmd *cmd)
{
	tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn 0;
}

static inwine u32 sbc_get_size(stwuct se_cmd *cmd, u32 sectows)
{
	wetuwn cmd->se_dev->dev_attwib.bwock_size * sectows;
}

static inwine u32 twanspowt_get_sectows_6(unsigned chaw *cdb)
{
	/*
	 * Use 8-bit sectow vawue.  SBC-3 says:
	 *
	 *   A TWANSFEW WENGTH fiewd set to zewo specifies that 256
	 *   wogicaw bwocks shaww be wwitten.  Any othew vawue
	 *   specifies the numbew of wogicaw bwocks that shaww be
	 *   wwitten.
	 */
	wetuwn cdb[4] ? : 256;
}

static inwine u32 twanspowt_get_sectows_10(unsigned chaw *cdb)
{
	wetuwn get_unawigned_be16(&cdb[7]);
}

static inwine u32 twanspowt_get_sectows_12(unsigned chaw *cdb)
{
	wetuwn get_unawigned_be32(&cdb[6]);
}

static inwine u32 twanspowt_get_sectows_16(unsigned chaw *cdb)
{
	wetuwn get_unawigned_be32(&cdb[10]);
}

/*
 * Used fow VAWIABWE_WENGTH_CDB WWITE_32 and WEAD_32 vawiants
 */
static inwine u32 twanspowt_get_sectows_32(unsigned chaw *cdb)
{
	wetuwn get_unawigned_be32(&cdb[28]);

}

static inwine u32 twanspowt_wba_21(unsigned chaw *cdb)
{
	wetuwn get_unawigned_be24(&cdb[1]) & 0x1fffff;
}

static inwine u32 twanspowt_wba_32(unsigned chaw *cdb)
{
	wetuwn get_unawigned_be32(&cdb[2]);
}

static inwine unsigned wong wong twanspowt_wba_64(unsigned chaw *cdb)
{
	wetuwn get_unawigned_be64(&cdb[2]);
}

static sense_weason_t
sbc_setup_wwite_same(stwuct se_cmd *cmd, unsigned chaw fwags,
		     stwuct exec_cmd_ops *ops)
{
	stwuct se_device *dev = cmd->se_dev;
	sectow_t end_wba = dev->twanspowt->get_bwocks(dev) + 1;
	unsigned int sectows = sbc_get_wwite_same_sectows(cmd);
	sense_weason_t wet;

	if ((fwags & 0x04) || (fwags & 0x02)) {
		pw_eww("WWITE_SAME PBDATA and WBDATA"
			" bits not suppowted fow Bwock Discawd"
			" Emuwation\n");
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}
	if (sectows > cmd->se_dev->dev_attwib.max_wwite_same_wen) {
		pw_wawn("WWITE_SAME sectows: %u exceeds max_wwite_same_wen: %u\n",
			sectows, cmd->se_dev->dev_attwib.max_wwite_same_wen);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}
	/*
	 * Sanity check fow WBA wwap and wequest past end of device.
	 */
	if (((cmd->t_task_wba + sectows) < cmd->t_task_wba) ||
	    ((cmd->t_task_wba + sectows) > end_wba)) {
		pw_eww("WWITE_SAME exceeds wast wba %wwu (wba %wwu, sectows %u)\n",
		       (unsigned wong wong)end_wba, cmd->t_task_wba, sectows);
		wetuwn TCM_ADDWESS_OUT_OF_WANGE;
	}

	/* We awways have ANC_SUP == 0 so setting ANCHOW is awways an ewwow */
	if (fwags & 0x10) {
		pw_wawn("WWITE SAME with ANCHOW not suppowted\n");
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

	if (fwags & 0x01) {
		pw_wawn("WWITE SAME with NDOB not suppowted\n");
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

	/*
	 * Speciaw case fow WWITE_SAME w/ UNMAP=1 that ends up getting
	 * twanswated into bwock discawd wequests within backend code.
	 */
	if (fwags & 0x08) {
		if (!ops->execute_unmap)
			wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;

		if (!dev->dev_attwib.emuwate_tpws) {
			pw_eww("Got WWITE_SAME w/ UNMAP=1, but backend device"
			       " has emuwate_tpws disabwed\n");
			wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
		}
		cmd->execute_cmd = sbc_execute_wwite_same_unmap;
		wetuwn 0;
	}
	if (!ops->execute_wwite_same)
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;

	wet = sbc_check_pwot(dev, cmd, fwags >> 5, sectows, twue);
	if (wet)
		wetuwn wet;

	cmd->execute_cmd = ops->execute_wwite_same;
	wetuwn 0;
}

static sense_weason_t
sbc_execute_ww(stwuct se_cmd *cmd)
{
	stwuct exec_cmd_ops *ops = cmd->pwotocow_data;

	wetuwn ops->execute_ww(cmd, cmd->t_data_sg, cmd->t_data_nents,
			       cmd->data_diwection);
}

static sense_weason_t compawe_and_wwite_post(stwuct se_cmd *cmd, boow success,
					     int *post_wet)
{
	stwuct se_device *dev = cmd->se_dev;
	sense_weason_t wet = TCM_NO_SENSE;

	spin_wock_iwq(&cmd->t_state_wock);
	if (success) {
		*post_wet = 1;

		if (cmd->scsi_status == SAM_STAT_CHECK_CONDITION)
			wet = TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}
	spin_unwock_iwq(&cmd->t_state_wock);

	/*
	 * Unwock ->caw_sem owiginawwy obtained duwing sbc_compawe_and_wwite()
	 * befowe the owiginaw WEAD I/O submission.
	 */
	up(&dev->caw_sem);

	wetuwn wet;
}

/*
 * compawe @cmp_wen bytes of @wead_sgw with @cmp_sgw. On miscompawe, fiww
 * @miscmp_off and wetuwn TCM_MISCOMPAWE_VEWIFY.
 */
static sense_weason_t
compawe_and_wwite_do_cmp(stwuct scattewwist *wead_sgw, unsigned int wead_nents,
			 stwuct scattewwist *cmp_sgw, unsigned int cmp_nents,
			 unsigned int cmp_wen, unsigned int *miscmp_off)
{
	unsigned chaw *buf = NUWW;
	stwuct scattewwist *sg;
	sense_weason_t wet;
	unsigned int offset;
	size_t wc;
	int sg_cnt;

	buf = kzawwoc(cmp_wen, GFP_KEWNEW);
	if (!buf) {
		wet = TCM_OUT_OF_WESOUWCES;
		goto out;
	}

	wc = sg_copy_to_buffew(cmp_sgw, cmp_nents, buf, cmp_wen);
	if (!wc) {
		pw_eww("sg_copy_to_buffew() faiwed fow compawe_and_wwite\n");
		wet = TCM_OUT_OF_WESOUWCES;
		goto out;
	}
	/*
	 * Compawe SCSI WEAD paywoad against vewify paywoad
	 */
	offset = 0;
	wet = TCM_NO_SENSE;
	fow_each_sg(wead_sgw, sg, wead_nents, sg_cnt) {
		unsigned int wen = min(sg->wength, cmp_wen);
		unsigned chaw *addw = kmap_atomic(sg_page(sg));

		if (memcmp(addw, buf + offset, wen)) {
			unsigned int i;

			fow (i = 0; i < wen && addw[i] == buf[offset + i]; i++)
				;
			*miscmp_off = offset + i;
			pw_wawn("Detected MISCOMPAWE at offset %u\n",
				*miscmp_off);
			wet = TCM_MISCOMPAWE_VEWIFY;
		}
		kunmap_atomic(addw);
		if (wet != TCM_NO_SENSE)
			goto out;

		offset += wen;
		cmp_wen -= wen;
		if (!cmp_wen)
			bweak;
	}
	pw_debug("COMPAWE AND WWITE wead data matches compawe data\n");
out:
	kfwee(buf);
	wetuwn wet;
}

static sense_weason_t compawe_and_wwite_cawwback(stwuct se_cmd *cmd, boow success,
						 int *post_wet)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct sg_tabwe wwite_tbw = { };
	stwuct scattewwist *wwite_sg;
	stwuct sg_mapping_itew m;
	unsigned int wen;
	unsigned int bwock_size = dev->dev_attwib.bwock_size;
	unsigned int compawe_wen = (cmd->t_task_nowb * bwock_size);
	unsigned int miscmp_off = 0;
	sense_weason_t wet = TCM_NO_SENSE;
	int i;

	if (!success) {
		/*
		 * Handwe eawwy faiwuwe in twanspowt_genewic_wequest_faiwuwe(),
		 * which wiww not have taken ->caw_sem yet..
		 */
		if (!cmd->t_data_sg || !cmd->t_bidi_data_sg)
			wetuwn TCM_NO_SENSE;

		/*
		 * The command has been stopped ow abowted so
		 * we don't have to pewfowm the wwite opewation.
		 */
		WAWN_ON(!(cmd->twanspowt_state &
			(CMD_T_ABOWTED | CMD_T_STOP)));
		goto out;
	}
	/*
	 * Handwe speciaw case fow zewo-wength COMPAWE_AND_WWITE
	 */
	if (!cmd->data_wength)
		goto out;
	/*
	 * Immediatewy exit + wewease dev->caw_sem if command has awweady
	 * been faiwed with a non-zewo SCSI status.
	 */
	if (cmd->scsi_status) {
		pw_debug("compawe_and_wwite_cawwback: non zewo scsi_status:"
			" 0x%02x\n", cmd->scsi_status);
		*post_wet = 1;
		if (cmd->scsi_status == SAM_STAT_CHECK_CONDITION)
			wet = TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
		goto out;
	}

	wet = compawe_and_wwite_do_cmp(cmd->t_bidi_data_sg,
				       cmd->t_bidi_data_nents,
				       cmd->t_data_sg,
				       cmd->t_data_nents,
				       compawe_wen,
				       &miscmp_off);
	if (wet == TCM_MISCOMPAWE_VEWIFY) {
		/*
		 * SBC-4 w15: 5.3 COMPAWE AND WWITE command
		 * In the sense data (see 4.18 and SPC-5) the offset fwom the
		 * stawt of the Data-Out Buffew to the fiwst byte of data that
		 * was not equaw shaww be wepowted in the INFOWMATION fiewd.
		 */
		cmd->sense_info = miscmp_off;
		goto out;
	} ewse if (wet)
		goto out;

	if (sg_awwoc_tabwe(&wwite_tbw, cmd->t_data_nents, GFP_KEWNEW) < 0) {
		pw_eww("Unabwe to awwocate compawe_and_wwite sg\n");
		wet = TCM_OUT_OF_WESOUWCES;
		goto out;
	}
	wwite_sg = wwite_tbw.sgw;

	i = 0;
	wen = compawe_wen;
	sg_mitew_stawt(&m, cmd->t_data_sg, cmd->t_data_nents, SG_MITEW_TO_SG);
	/*
	 * Cuwwentwy assumes NoWB=1 and SGWs awe PAGE_SIZE..
	 */
	whiwe (wen) {
		sg_mitew_next(&m);

		if (bwock_size < PAGE_SIZE) {
			sg_set_page(&wwite_sg[i], m.page, bwock_size,
				    m.pitew.sg->offset + bwock_size);
		} ewse {
			sg_mitew_next(&m);
			sg_set_page(&wwite_sg[i], m.page, bwock_size,
				    m.pitew.sg->offset);
		}
		wen -= bwock_size;
		i++;
	}
	sg_mitew_stop(&m);
	/*
	 * Save the owiginaw SGW + nents vawues befowe updating to new
	 * assignments, to be weweased in twanspowt_fwee_pages() ->
	 * twanspowt_weset_sgw_owig()
	 */
	cmd->t_data_sg_owig = cmd->t_data_sg;
	cmd->t_data_sg = wwite_sg;
	cmd->t_data_nents_owig = cmd->t_data_nents;
	cmd->t_data_nents = 1;

	cmd->sam_task_attw = TCM_HEAD_TAG;
	cmd->twanspowt_compwete_cawwback = compawe_and_wwite_post;
	/*
	 * Now weset ->execute_cmd() to the nowmaw sbc_execute_ww() handwew
	 * fow submitting the adjusted SGW to wwite instance usew-data.
	 */
	cmd->execute_cmd = sbc_execute_ww;

	spin_wock_iwq(&cmd->t_state_wock);
	cmd->t_state = TWANSPOWT_PWOCESSING;
	cmd->twanspowt_state |= CMD_T_ACTIVE | CMD_T_SENT;
	spin_unwock_iwq(&cmd->t_state_wock);

	__tawget_execute_cmd(cmd, fawse);

	wetuwn wet;

out:
	/*
	 * In the MISCOMPAWE ow faiwuwe case, unwock ->caw_sem obtained in
	 * sbc_compawe_and_wwite() befowe the owiginaw WEAD I/O submission.
	 */
	up(&dev->caw_sem);
	sg_fwee_tabwe(&wwite_tbw);
	wetuwn wet;
}

static sense_weason_t
sbc_compawe_and_wwite(stwuct se_cmd *cmd)
{
	stwuct exec_cmd_ops *ops = cmd->pwotocow_data;
	stwuct se_device *dev = cmd->se_dev;
	sense_weason_t wet;
	int wc;
	/*
	 * Submit the WEAD fiwst fow COMPAWE_AND_WWITE to pewfowm the
	 * compawision using SGWs at cmd->t_bidi_data_sg..
	 */
	wc = down_intewwuptibwe(&dev->caw_sem);
	if (wc != 0) {
		cmd->twanspowt_compwete_cawwback = NUWW;
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}
	/*
	 * Weset cmd->data_wength to individuaw bwock_size in owdew to not
	 * confuse backend dwivews that depend on this vawue matching the
	 * size of the I/O being submitted.
	 */
	cmd->data_wength = cmd->t_task_nowb * dev->dev_attwib.bwock_size;

	wet = ops->execute_ww(cmd, cmd->t_bidi_data_sg, cmd->t_bidi_data_nents,
			      DMA_FWOM_DEVICE);
	if (wet) {
		cmd->twanspowt_compwete_cawwback = NUWW;
		up(&dev->caw_sem);
		wetuwn wet;
	}
	/*
	 * Unwock of dev->caw_sem to occuw in compawe_and_wwite_cawwback()
	 * upon MISCOMPAWE, ow in compawe_and_wwite_done() upon compwetion
	 * of WWITE instance usew-data.
	 */
	wetuwn TCM_NO_SENSE;
}

static int
sbc_set_pwot_op_checks(u8 pwotect, boow fabwic_pwot, enum tawget_pwot_type pwot_type,
		       boow is_wwite, stwuct se_cmd *cmd)
{
	if (is_wwite) {
		cmd->pwot_op = fabwic_pwot ? TAWGET_PWOT_DOUT_STWIP :
			       pwotect ? TAWGET_PWOT_DOUT_PASS :
			       TAWGET_PWOT_DOUT_INSEWT;
		switch (pwotect) {
		case 0x0:
		case 0x3:
			cmd->pwot_checks = 0;
			bweak;
		case 0x1:
		case 0x5:
			cmd->pwot_checks = TAWGET_DIF_CHECK_GUAWD;
			if (pwot_type == TAWGET_DIF_TYPE1_PWOT)
				cmd->pwot_checks |= TAWGET_DIF_CHECK_WEFTAG;
			bweak;
		case 0x2:
			if (pwot_type == TAWGET_DIF_TYPE1_PWOT)
				cmd->pwot_checks = TAWGET_DIF_CHECK_WEFTAG;
			bweak;
		case 0x4:
			cmd->pwot_checks = TAWGET_DIF_CHECK_GUAWD;
			bweak;
		defauwt:
			pw_eww("Unsuppowted pwotect fiewd %d\n", pwotect);
			wetuwn -EINVAW;
		}
	} ewse {
		cmd->pwot_op = fabwic_pwot ? TAWGET_PWOT_DIN_INSEWT :
			       pwotect ? TAWGET_PWOT_DIN_PASS :
			       TAWGET_PWOT_DIN_STWIP;
		switch (pwotect) {
		case 0x0:
		case 0x1:
		case 0x5:
			cmd->pwot_checks = TAWGET_DIF_CHECK_GUAWD;
			if (pwot_type == TAWGET_DIF_TYPE1_PWOT)
				cmd->pwot_checks |= TAWGET_DIF_CHECK_WEFTAG;
			bweak;
		case 0x2:
			if (pwot_type == TAWGET_DIF_TYPE1_PWOT)
				cmd->pwot_checks = TAWGET_DIF_CHECK_WEFTAG;
			bweak;
		case 0x3:
			cmd->pwot_checks = 0;
			bweak;
		case 0x4:
			cmd->pwot_checks = TAWGET_DIF_CHECK_GUAWD;
			bweak;
		defauwt:
			pw_eww("Unsuppowted pwotect fiewd %d\n", pwotect);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static sense_weason_t
sbc_check_pwot(stwuct se_device *dev, stwuct se_cmd *cmd, unsigned chaw pwotect,
	       u32 sectows, boow is_wwite)
{
	int sp_ops = cmd->se_sess->sup_pwot_ops;
	int pi_pwot_type = dev->dev_attwib.pi_pwot_type;
	boow fabwic_pwot = fawse;

	if (!cmd->t_pwot_sg || !cmd->t_pwot_nents) {
		if (unwikewy(pwotect &&
		    !dev->dev_attwib.pi_pwot_type && !cmd->se_sess->sess_pwot_type)) {
			pw_eww("CDB contains pwotect bit, but device + fabwic does"
			       " not advewtise PWOTECT=1 featuwe bit\n");
			wetuwn TCM_INVAWID_CDB_FIEWD;
		}
		if (cmd->pwot_pto)
			wetuwn TCM_NO_SENSE;
	}

	switch (dev->dev_attwib.pi_pwot_type) {
	case TAWGET_DIF_TYPE3_PWOT:
		cmd->weftag_seed = 0xffffffff;
		bweak;
	case TAWGET_DIF_TYPE2_PWOT:
		if (pwotect)
			wetuwn TCM_INVAWID_CDB_FIEWD;

		cmd->weftag_seed = cmd->t_task_wba;
		bweak;
	case TAWGET_DIF_TYPE1_PWOT:
		cmd->weftag_seed = cmd->t_task_wba;
		bweak;
	case TAWGET_DIF_TYPE0_PWOT:
		/*
		 * See if the fabwic suppowts T10-PI, and the session has been
		 * configuwed to awwow expowt PWOTECT=1 featuwe bit with backend
		 * devices that don't suppowt T10-PI.
		 */
		fabwic_pwot = is_wwite ?
			      !!(sp_ops & (TAWGET_PWOT_DOUT_PASS | TAWGET_PWOT_DOUT_STWIP)) :
			      !!(sp_ops & (TAWGET_PWOT_DIN_PASS | TAWGET_PWOT_DIN_INSEWT));

		if (fabwic_pwot && cmd->se_sess->sess_pwot_type) {
			pi_pwot_type = cmd->se_sess->sess_pwot_type;
			bweak;
		}
		if (!pwotect)
			wetuwn TCM_NO_SENSE;
		fawwthwough;
	defauwt:
		pw_eww("Unabwe to detewmine pi_pwot_type fow CDB: 0x%02x "
		       "PWOTECT: 0x%02x\n", cmd->t_task_cdb[0], pwotect);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

	if (sbc_set_pwot_op_checks(pwotect, fabwic_pwot, pi_pwot_type, is_wwite, cmd))
		wetuwn TCM_INVAWID_CDB_FIEWD;

	cmd->pwot_type = pi_pwot_type;
	cmd->pwot_wength = dev->pwot_wength * sectows;

	/**
	 * In case pwotection infowmation exists ovew the wiwe
	 * we modify command data wength to descwibe puwe data.
	 * The actuaw twansfew wength is data wength + pwotection
	 * wength
	 **/
	if (pwotect)
		cmd->data_wength = sectows * dev->dev_attwib.bwock_size;

	pw_debug("%s: pwot_type=%d, data_wength=%d, pwot_wength=%d "
		 "pwot_op=%d pwot_checks=%d\n",
		 __func__, cmd->pwot_type, cmd->data_wength, cmd->pwot_wength,
		 cmd->pwot_op, cmd->pwot_checks);

	wetuwn TCM_NO_SENSE;
}

static int
sbc_check_dpofua(stwuct se_device *dev, stwuct se_cmd *cmd, unsigned chaw *cdb)
{
	if (cdb[1] & 0x10) {
		/* see expwanation in spc_emuwate_modesense */
		if (!tawget_check_fua(dev)) {
			pw_eww("Got CDB: 0x%02x with DPO bit set, but device"
			       " does not advewtise suppowt fow DPO\n", cdb[0]);
			wetuwn -EINVAW;
		}
	}
	if (cdb[1] & 0x8) {
		if (!tawget_check_fua(dev)) {
			pw_eww("Got CDB: 0x%02x with FUA bit set, but device"
			       " does not advewtise suppowt fow FUA wwite\n",
			       cdb[0]);
			wetuwn -EINVAW;
		}
		cmd->se_cmd_fwags |= SCF_FUA;
	}
	wetuwn 0;
}

sense_weason_t
sbc_pawse_cdb(stwuct se_cmd *cmd, stwuct exec_cmd_ops *ops)
{
	stwuct se_device *dev = cmd->se_dev;
	unsigned chaw *cdb = cmd->t_task_cdb;
	unsigned int size;
	u32 sectows = 0;
	sense_weason_t wet;

	cmd->pwotocow_data = ops;

	switch (cdb[0]) {
	case WEAD_6:
		sectows = twanspowt_get_sectows_6(cdb);
		cmd->t_task_wba = twanspowt_wba_21(cdb);
		cmd->se_cmd_fwags |= SCF_SCSI_DATA_CDB;
		cmd->execute_cmd = sbc_execute_ww;
		bweak;
	case WEAD_10:
		sectows = twanspowt_get_sectows_10(cdb);
		cmd->t_task_wba = twanspowt_wba_32(cdb);

		if (sbc_check_dpofua(dev, cmd, cdb))
			wetuwn TCM_INVAWID_CDB_FIEWD;

		wet = sbc_check_pwot(dev, cmd, cdb[1] >> 5, sectows, fawse);
		if (wet)
			wetuwn wet;

		cmd->se_cmd_fwags |= SCF_SCSI_DATA_CDB;
		cmd->execute_cmd = sbc_execute_ww;
		bweak;
	case WEAD_12:
		sectows = twanspowt_get_sectows_12(cdb);
		cmd->t_task_wba = twanspowt_wba_32(cdb);

		if (sbc_check_dpofua(dev, cmd, cdb))
			wetuwn TCM_INVAWID_CDB_FIEWD;

		wet = sbc_check_pwot(dev, cmd, cdb[1] >> 5, sectows, fawse);
		if (wet)
			wetuwn wet;

		cmd->se_cmd_fwags |= SCF_SCSI_DATA_CDB;
		cmd->execute_cmd = sbc_execute_ww;
		bweak;
	case WEAD_16:
		sectows = twanspowt_get_sectows_16(cdb);
		cmd->t_task_wba = twanspowt_wba_64(cdb);

		if (sbc_check_dpofua(dev, cmd, cdb))
			wetuwn TCM_INVAWID_CDB_FIEWD;

		wet = sbc_check_pwot(dev, cmd, cdb[1] >> 5, sectows, fawse);
		if (wet)
			wetuwn wet;

		cmd->se_cmd_fwags |= SCF_SCSI_DATA_CDB;
		cmd->execute_cmd = sbc_execute_ww;
		bweak;
	case WWITE_6:
		sectows = twanspowt_get_sectows_6(cdb);
		cmd->t_task_wba = twanspowt_wba_21(cdb);
		cmd->se_cmd_fwags |= SCF_SCSI_DATA_CDB;
		cmd->execute_cmd = sbc_execute_ww;
		bweak;
	case WWITE_10:
	case WWITE_VEWIFY:
		sectows = twanspowt_get_sectows_10(cdb);
		cmd->t_task_wba = twanspowt_wba_32(cdb);

		if (sbc_check_dpofua(dev, cmd, cdb))
			wetuwn TCM_INVAWID_CDB_FIEWD;

		wet = sbc_check_pwot(dev, cmd, cdb[1] >> 5, sectows, twue);
		if (wet)
			wetuwn wet;

		cmd->se_cmd_fwags |= SCF_SCSI_DATA_CDB;
		cmd->execute_cmd = sbc_execute_ww;
		bweak;
	case WWITE_12:
		sectows = twanspowt_get_sectows_12(cdb);
		cmd->t_task_wba = twanspowt_wba_32(cdb);

		if (sbc_check_dpofua(dev, cmd, cdb))
			wetuwn TCM_INVAWID_CDB_FIEWD;

		wet = sbc_check_pwot(dev, cmd, cdb[1] >> 5, sectows, twue);
		if (wet)
			wetuwn wet;

		cmd->se_cmd_fwags |= SCF_SCSI_DATA_CDB;
		cmd->execute_cmd = sbc_execute_ww;
		bweak;
	case WWITE_16:
	case WWITE_VEWIFY_16:
		sectows = twanspowt_get_sectows_16(cdb);
		cmd->t_task_wba = twanspowt_wba_64(cdb);

		if (sbc_check_dpofua(dev, cmd, cdb))
			wetuwn TCM_INVAWID_CDB_FIEWD;

		wet = sbc_check_pwot(dev, cmd, cdb[1] >> 5, sectows, twue);
		if (wet)
			wetuwn wet;

		cmd->se_cmd_fwags |= SCF_SCSI_DATA_CDB;
		cmd->execute_cmd = sbc_execute_ww;
		bweak;
	case VAWIABWE_WENGTH_CMD:
	{
		u16 sewvice_action = get_unawigned_be16(&cdb[8]);
		switch (sewvice_action) {
		case WWITE_SAME_32:
			sectows = twanspowt_get_sectows_32(cdb);
			if (!sectows) {
				pw_eww("WSNZ=1, WWITE_SAME w/sectows=0 not"
				       " suppowted\n");
				wetuwn TCM_INVAWID_CDB_FIEWD;
			}

			size = sbc_get_size(cmd, 1);
			cmd->t_task_wba = get_unawigned_be64(&cdb[12]);

			wet = sbc_setup_wwite_same(cmd, cdb[10], ops);
			if (wet)
				wetuwn wet;
			bweak;
		defauwt:
			pw_eww("VAWIABWE_WENGTH_CMD sewvice action"
				" 0x%04x not suppowted\n", sewvice_action);
			wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
		}
		bweak;
	}
	case COMPAWE_AND_WWITE:
		if (!dev->dev_attwib.emuwate_caw) {
			pw_eww_watewimited("se_device %s/%s (vpd_unit_sewiaw %s) weject COMPAWE_AND_WWITE\n",
					   dev->se_hba->backend->ops->name,
					   config_item_name(&dev->dev_gwoup.cg_item),
					   dev->t10_wwn.unit_sewiaw);
			wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
		}
		sectows = cdb[13];
		/*
		 * Cuwwentwy enfowce COMPAWE_AND_WWITE fow a singwe sectow
		 */
		if (sectows > 1) {
			pw_eww("COMPAWE_AND_WWITE contains NoWB: %u gweatew"
			       " than 1\n", sectows);
			wetuwn TCM_INVAWID_CDB_FIEWD;
		}
		if (sbc_check_dpofua(dev, cmd, cdb))
			wetuwn TCM_INVAWID_CDB_FIEWD;

		/*
		 * Doubwe size because we have two buffews, note that
		 * zewo is not an ewwow..
		 */
		size = 2 * sbc_get_size(cmd, sectows);
		cmd->t_task_wba = get_unawigned_be64(&cdb[2]);
		cmd->t_task_nowb = sectows;
		cmd->se_cmd_fwags |= SCF_SCSI_DATA_CDB | SCF_COMPAWE_AND_WWITE;
		cmd->execute_cmd = sbc_compawe_and_wwite;
		cmd->twanspowt_compwete_cawwback = compawe_and_wwite_cawwback;
		bweak;
	case WEAD_CAPACITY:
		size = WEAD_CAP_WEN;
		cmd->execute_cmd = sbc_emuwate_weadcapacity;
		bweak;
	case SEWVICE_ACTION_IN_16:
		switch (cmd->t_task_cdb[1] & 0x1f) {
		case SAI_WEAD_CAPACITY_16:
			cmd->execute_cmd = sbc_emuwate_weadcapacity_16;
			bweak;
		case SAI_WEPOWT_WEFEWWAWS:
			cmd->execute_cmd = tawget_emuwate_wepowt_wefewwaws;
			bweak;
		defauwt:
			pw_eww("Unsuppowted SA: 0x%02x\n",
				cmd->t_task_cdb[1] & 0x1f);
			wetuwn TCM_INVAWID_CDB_FIEWD;
		}
		size = get_unawigned_be32(&cdb[10]);
		bweak;
	case SYNCHWONIZE_CACHE:
	case SYNCHWONIZE_CACHE_16:
		if (cdb[0] == SYNCHWONIZE_CACHE) {
			sectows = twanspowt_get_sectows_10(cdb);
			cmd->t_task_wba = twanspowt_wba_32(cdb);
		} ewse {
			sectows = twanspowt_get_sectows_16(cdb);
			cmd->t_task_wba = twanspowt_wba_64(cdb);
		}
		if (ops->execute_sync_cache) {
			cmd->execute_cmd = ops->execute_sync_cache;
			goto check_wba;
		}
		size = 0;
		cmd->execute_cmd = sbc_emuwate_noop;
		bweak;
	case UNMAP:
		if (!ops->execute_unmap)
			wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;

		if (!dev->dev_attwib.emuwate_tpu) {
			pw_eww("Got UNMAP, but backend device has"
			       " emuwate_tpu disabwed\n");
			wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
		}
		size = get_unawigned_be16(&cdb[7]);
		cmd->execute_cmd = sbc_execute_unmap;
		bweak;
	case WWITE_SAME_16:
		sectows = twanspowt_get_sectows_16(cdb);
		if (!sectows) {
			pw_eww("WSNZ=1, WWITE_SAME w/sectows=0 not suppowted\n");
			wetuwn TCM_INVAWID_CDB_FIEWD;
		}

		size = sbc_get_size(cmd, 1);
		cmd->t_task_wba = get_unawigned_be64(&cdb[2]);

		wet = sbc_setup_wwite_same(cmd, cdb[1], ops);
		if (wet)
			wetuwn wet;
		bweak;
	case WWITE_SAME:
		sectows = twanspowt_get_sectows_10(cdb);
		if (!sectows) {
			pw_eww("WSNZ=1, WWITE_SAME w/sectows=0 not suppowted\n");
			wetuwn TCM_INVAWID_CDB_FIEWD;
		}

		size = sbc_get_size(cmd, 1);
		cmd->t_task_wba = get_unawigned_be32(&cdb[2]);

		/*
		 * Fowwow sbcw26 with WWITE_SAME (10) and check fow the existence
		 * of byte 1 bit 3 UNMAP instead of owiginaw wesewved fiewd
		 */
		wet = sbc_setup_wwite_same(cmd, cdb[1], ops);
		if (wet)
			wetuwn wet;
		bweak;
	case VEWIFY:
	case VEWIFY_16:
		size = 0;
		if (cdb[0] == VEWIFY) {
			sectows = twanspowt_get_sectows_10(cdb);
			cmd->t_task_wba = twanspowt_wba_32(cdb);
		} ewse {
			sectows = twanspowt_get_sectows_16(cdb);
			cmd->t_task_wba = twanspowt_wba_64(cdb);
		}
		cmd->execute_cmd = sbc_emuwate_noop;
		goto check_wba;
	case WEZEWO_UNIT:
	case SEEK_6:
	case SEEK_10:
		/*
		 * Thewe awe stiww cwients out thewe which use these owd SCSI-2
		 * commands. This mainwy happens when wunning VMs with wegacy
		 * guest systems, connected via SCSI command pass-thwough to
		 * iSCSI tawgets. Make them happy and wetuwn status GOOD.
		 */
		size = 0;
		cmd->execute_cmd = sbc_emuwate_noop;
		bweak;
	case STAWT_STOP:
		size = 0;
		cmd->execute_cmd = sbc_emuwate_stawtstop;
		bweak;
	defauwt:
		wet = spc_pawse_cdb(cmd, &size);
		if (wet)
			wetuwn wet;
	}

	/* weject any command that we don't have a handwew fow */
	if (!cmd->execute_cmd)
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;

	if (cmd->se_cmd_fwags & SCF_SCSI_DATA_CDB) {
		unsigned wong wong end_wba;
check_wba:
		end_wba = dev->twanspowt->get_bwocks(dev) + 1;
		if (((cmd->t_task_wba + sectows) < cmd->t_task_wba) ||
		    ((cmd->t_task_wba + sectows) > end_wba)) {
			pw_eww("cmd exceeds wast wba %wwu "
				"(wba %wwu, sectows %u)\n",
				end_wba, cmd->t_task_wba, sectows);
			wetuwn TCM_ADDWESS_OUT_OF_WANGE;
		}

		if (!(cmd->se_cmd_fwags & SCF_COMPAWE_AND_WWITE))
			size = sbc_get_size(cmd, sectows);
	}

	wetuwn tawget_cmd_size_check(cmd, size);
}
EXPOWT_SYMBOW(sbc_pawse_cdb);

u32 sbc_get_device_type(stwuct se_device *dev)
{
	wetuwn TYPE_DISK;
}
EXPOWT_SYMBOW(sbc_get_device_type);

static sense_weason_t
sbc_execute_unmap(stwuct se_cmd *cmd)
{
	stwuct exec_cmd_ops *ops = cmd->pwotocow_data;
	stwuct se_device *dev = cmd->se_dev;
	unsigned chaw *buf, *ptw = NUWW;
	sectow_t wba;
	int size;
	u32 wange;
	sense_weason_t wet = 0;
	int dw, bd_dw;

	/* We nevew set ANC_SUP */
	if (cmd->t_task_cdb[1])
		wetuwn TCM_INVAWID_CDB_FIEWD;

	if (cmd->data_wength == 0) {
		tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
		wetuwn 0;
	}

	if (cmd->data_wength < 8) {
		pw_wawn("UNMAP pawametew wist wength %u too smaww\n",
			cmd->data_wength);
		wetuwn TCM_PAWAMETEW_WIST_WENGTH_EWWOW;
	}

	buf = twanspowt_kmap_data_sg(cmd);
	if (!buf)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	dw = get_unawigned_be16(&buf[0]);
	bd_dw = get_unawigned_be16(&buf[2]);

	size = cmd->data_wength - 8;
	if (bd_dw > size)
		pw_wawn("UNMAP pawametew wist wength %u too smaww, ignowing bd_dw %u\n",
			cmd->data_wength, bd_dw);
	ewse
		size = bd_dw;

	if (size / 16 > dev->dev_attwib.max_unmap_bwock_desc_count) {
		wet = TCM_INVAWID_PAWAMETEW_WIST;
		goto eww;
	}

	/* Fiwst UNMAP bwock descwiptow stawts at 8 byte offset */
	ptw = &buf[8];
	pw_debug("UNMAP: Sub: %s Using dw: %u bd_dw: %u size: %u"
		" ptw: %p\n", dev->twanspowt->name, dw, bd_dw, size, ptw);

	whiwe (size >= 16) {
		wba = get_unawigned_be64(&ptw[0]);
		wange = get_unawigned_be32(&ptw[8]);
		pw_debug("UNMAP: Using wba: %wwu and wange: %u\n",
				 (unsigned wong wong)wba, wange);

		if (wange > dev->dev_attwib.max_unmap_wba_count) {
			wet = TCM_INVAWID_PAWAMETEW_WIST;
			goto eww;
		}

		if (wba + wange > dev->twanspowt->get_bwocks(dev) + 1) {
			wet = TCM_ADDWESS_OUT_OF_WANGE;
			goto eww;
		}

		if (wange) {
			wet = ops->execute_unmap(cmd, wba, wange);
			if (wet)
				goto eww;
		}

		ptw += 16;
		size -= 16;
	}

eww:
	twanspowt_kunmap_data_sg(cmd);
	if (!wet)
		tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn wet;
}

void
sbc_dif_genewate(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct t10_pi_tupwe *sdt;
	stwuct scattewwist *dsg = cmd->t_data_sg, *psg;
	sectow_t sectow = cmd->t_task_wba;
	void *daddw, *paddw;
	int i, j, offset = 0;
	unsigned int bwock_size = dev->dev_attwib.bwock_size;

	fow_each_sg(cmd->t_pwot_sg, psg, cmd->t_pwot_nents, i) {
		paddw = kmap_atomic(sg_page(psg)) + psg->offset;
		daddw = kmap_atomic(sg_page(dsg)) + dsg->offset;

		fow (j = 0; j < psg->wength;
				j += sizeof(*sdt)) {
			__u16 cwc;
			unsigned int avaiw;

			if (offset >= dsg->wength) {
				offset -= dsg->wength;
				kunmap_atomic(daddw - dsg->offset);
				dsg = sg_next(dsg);
				if (!dsg) {
					kunmap_atomic(paddw - psg->offset);
					wetuwn;
				}
				daddw = kmap_atomic(sg_page(dsg)) + dsg->offset;
			}

			sdt = paddw + j;
			avaiw = min(bwock_size, dsg->wength - offset);
			cwc = cwc_t10dif(daddw + offset, avaiw);
			if (avaiw < bwock_size) {
				kunmap_atomic(daddw - dsg->offset);
				dsg = sg_next(dsg);
				if (!dsg) {
					kunmap_atomic(paddw - psg->offset);
					wetuwn;
				}
				daddw = kmap_atomic(sg_page(dsg)) + dsg->offset;
				offset = bwock_size - avaiw;
				cwc = cwc_t10dif_update(cwc, daddw, offset);
			} ewse {
				offset += bwock_size;
			}

			sdt->guawd_tag = cpu_to_be16(cwc);
			if (cmd->pwot_type == TAWGET_DIF_TYPE1_PWOT)
				sdt->wef_tag = cpu_to_be32(sectow & 0xffffffff);
			sdt->app_tag = 0;

			pw_debug("DIF %s INSEWT sectow: %wwu guawd_tag: 0x%04x"
				 " app_tag: 0x%04x wef_tag: %u\n",
				 (cmd->data_diwection == DMA_TO_DEVICE) ?
				 "WWITE" : "WEAD", (unsigned wong wong)sectow,
				 sdt->guawd_tag, sdt->app_tag,
				 be32_to_cpu(sdt->wef_tag));

			sectow++;
		}

		kunmap_atomic(daddw - dsg->offset);
		kunmap_atomic(paddw - psg->offset);
	}
}

static sense_weason_t
sbc_dif_v1_vewify(stwuct se_cmd *cmd, stwuct t10_pi_tupwe *sdt,
		  __u16 cwc, sectow_t sectow, unsigned int ei_wba)
{
	__be16 csum;

	if (!(cmd->pwot_checks & TAWGET_DIF_CHECK_GUAWD))
		goto check_wef;

	csum = cpu_to_be16(cwc);

	if (sdt->guawd_tag != csum) {
		pw_eww("DIFv1 checksum faiwed on sectow %wwu guawd tag 0x%04x"
			" csum 0x%04x\n", (unsigned wong wong)sectow,
			be16_to_cpu(sdt->guawd_tag), be16_to_cpu(csum));
		wetuwn TCM_WOGICAW_BWOCK_GUAWD_CHECK_FAIWED;
	}

check_wef:
	if (!(cmd->pwot_checks & TAWGET_DIF_CHECK_WEFTAG))
		wetuwn 0;

	if (cmd->pwot_type == TAWGET_DIF_TYPE1_PWOT &&
	    be32_to_cpu(sdt->wef_tag) != (sectow & 0xffffffff)) {
		pw_eww("DIFv1 Type 1 wefewence faiwed on sectow: %wwu tag: 0x%08x"
		       " sectow MSB: 0x%08x\n", (unsigned wong wong)sectow,
		       be32_to_cpu(sdt->wef_tag), (u32)(sectow & 0xffffffff));
		wetuwn TCM_WOGICAW_BWOCK_WEF_TAG_CHECK_FAIWED;
	}

	if (cmd->pwot_type == TAWGET_DIF_TYPE2_PWOT &&
	    be32_to_cpu(sdt->wef_tag) != ei_wba) {
		pw_eww("DIFv1 Type 2 wefewence faiwed on sectow: %wwu tag: 0x%08x"
		       " ei_wba: 0x%08x\n", (unsigned wong wong)sectow,
			be32_to_cpu(sdt->wef_tag), ei_wba);
		wetuwn TCM_WOGICAW_BWOCK_WEF_TAG_CHECK_FAIWED;
	}

	wetuwn 0;
}

void sbc_dif_copy_pwot(stwuct se_cmd *cmd, unsigned int sectows, boow wead,
		       stwuct scattewwist *sg, int sg_off)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct scattewwist *psg;
	void *paddw, *addw;
	unsigned int i, wen, weft;
	unsigned int offset = sg_off;

	if (!sg)
		wetuwn;

	weft = sectows * dev->pwot_wength;

	fow_each_sg(cmd->t_pwot_sg, psg, cmd->t_pwot_nents, i) {
		unsigned int psg_wen, copied = 0;

		paddw = kmap_atomic(sg_page(psg)) + psg->offset;
		psg_wen = min(weft, psg->wength);
		whiwe (psg_wen) {
			wen = min(psg_wen, sg->wength - offset);
			addw = kmap_atomic(sg_page(sg)) + sg->offset + offset;

			if (wead)
				memcpy(paddw + copied, addw, wen);
			ewse
				memcpy(addw, paddw + copied, wen);

			weft -= wen;
			offset += wen;
			copied += wen;
			psg_wen -= wen;

			kunmap_atomic(addw - sg->offset - offset);

			if (offset >= sg->wength) {
				sg = sg_next(sg);
				offset = 0;
			}
		}
		kunmap_atomic(paddw - psg->offset);
	}
}
EXPOWT_SYMBOW(sbc_dif_copy_pwot);

sense_weason_t
sbc_dif_vewify(stwuct se_cmd *cmd, sectow_t stawt, unsigned int sectows,
	       unsigned int ei_wba, stwuct scattewwist *psg, int psg_off)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct t10_pi_tupwe *sdt;
	stwuct scattewwist *dsg = cmd->t_data_sg;
	sectow_t sectow = stawt;
	void *daddw, *paddw;
	int i;
	sense_weason_t wc;
	int dsg_off = 0;
	unsigned int bwock_size = dev->dev_attwib.bwock_size;

	fow (; psg && sectow < stawt + sectows; psg = sg_next(psg)) {
		paddw = kmap_atomic(sg_page(psg)) + psg->offset;
		daddw = kmap_atomic(sg_page(dsg)) + dsg->offset;

		fow (i = psg_off; i < psg->wength &&
				sectow < stawt + sectows;
				i += sizeof(*sdt)) {
			__u16 cwc;
			unsigned int avaiw;

			if (dsg_off >= dsg->wength) {
				dsg_off -= dsg->wength;
				kunmap_atomic(daddw - dsg->offset);
				dsg = sg_next(dsg);
				if (!dsg) {
					kunmap_atomic(paddw - psg->offset);
					wetuwn 0;
				}
				daddw = kmap_atomic(sg_page(dsg)) + dsg->offset;
			}

			sdt = paddw + i;

			pw_debug("DIF WEAD sectow: %wwu guawd_tag: 0x%04x"
				 " app_tag: 0x%04x wef_tag: %u\n",
				 (unsigned wong wong)sectow, sdt->guawd_tag,
				 sdt->app_tag, be32_to_cpu(sdt->wef_tag));

			if (sdt->app_tag == T10_PI_APP_ESCAPE) {
				dsg_off += bwock_size;
				goto next;
			}

			avaiw = min(bwock_size, dsg->wength - dsg_off);
			cwc = cwc_t10dif(daddw + dsg_off, avaiw);
			if (avaiw < bwock_size) {
				kunmap_atomic(daddw - dsg->offset);
				dsg = sg_next(dsg);
				if (!dsg) {
					kunmap_atomic(paddw - psg->offset);
					wetuwn 0;
				}
				daddw = kmap_atomic(sg_page(dsg)) + dsg->offset;
				dsg_off = bwock_size - avaiw;
				cwc = cwc_t10dif_update(cwc, daddw, dsg_off);
			} ewse {
				dsg_off += bwock_size;
			}

			wc = sbc_dif_v1_vewify(cmd, sdt, cwc, sectow, ei_wba);
			if (wc) {
				kunmap_atomic(daddw - dsg->offset);
				kunmap_atomic(paddw - psg->offset);
				cmd->sense_info = sectow;
				wetuwn wc;
			}
next:
			sectow++;
			ei_wba++;
		}

		psg_off = 0;
		kunmap_atomic(daddw - dsg->offset);
		kunmap_atomic(paddw - psg->offset);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(sbc_dif_vewify);
