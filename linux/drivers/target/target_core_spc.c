// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SCSI Pwimawy Commands (SPC) pawsing and emuwation.
 *
 * (c) Copywight 2002-2013 Datewa, Inc.
 *
 * Nichowas A. Bewwingew <nab@kewnew.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <asm/unawigned.h>

#incwude <scsi/scsi_pwoto.h>
#incwude <scsi/scsi_common.h>
#incwude <scsi/scsi_tcq.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_backend.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude "tawget_cowe_intewnaw.h"
#incwude "tawget_cowe_awua.h"
#incwude "tawget_cowe_pw.h"
#incwude "tawget_cowe_ua.h"
#incwude "tawget_cowe_xcopy.h"

static void spc_fiww_awua_data(stwuct se_wun *wun, unsigned chaw *buf)
{
	stwuct t10_awua_tg_pt_gp *tg_pt_gp;

	/*
	 * Set SCCS fow MAINTENANCE_IN + WEPOWT_TAWGET_POWT_GWOUPS.
	 */
	buf[5]	= 0x80;

	/*
	 * Set TPGS fiewd fow expwicit and/ow impwicit AWUA access type
	 * and optewation.
	 *
	 * See spc4w17 section 6.4.2 Tabwe 135
	 */
	wcu_wead_wock();
	tg_pt_gp = wcu_dewefewence(wun->wun_tg_pt_gp);
	if (tg_pt_gp)
		buf[5] |= tg_pt_gp->tg_pt_gp_awua_access_type;
	wcu_wead_unwock();
}

static u16
spc_find_scsi_twanspowt_vd(int pwoto_id)
{
	switch (pwoto_id) {
	case SCSI_PWOTOCOW_FCP:
		wetuwn SCSI_VEWSION_DESCWIPTOW_FCP4;
	case SCSI_PWOTOCOW_ISCSI:
		wetuwn SCSI_VEWSION_DESCWIPTOW_ISCSI;
	case SCSI_PWOTOCOW_SAS:
		wetuwn SCSI_VEWSION_DESCWIPTOW_SAS3;
	case SCSI_PWOTOCOW_SBP:
		wetuwn SCSI_VEWSION_DESCWIPTOW_SBP3;
	case SCSI_PWOTOCOW_SWP:
		wetuwn SCSI_VEWSION_DESCWIPTOW_SWP;
	defauwt:
		pw_wawn("Cannot find VEWSION DESCWIPTOW vawue fow unknown SCSI"
			" twanspowt PWOTOCOW IDENTIFIEW %#x\n", pwoto_id);
		wetuwn 0;
	}
}

sense_weason_t
spc_emuwate_inquiwy_std(stwuct se_cmd *cmd, unsigned chaw *buf)
{
	stwuct se_wun *wun = cmd->se_wun;
	stwuct se_powtaw_gwoup *tpg = wun->wun_tpg;
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_session *sess = cmd->se_sess;

	/* Set WMB (wemovabwe media) fow tape devices */
	if (dev->twanspowt->get_device_type(dev) == TYPE_TAPE)
		buf[1] = 0x80;

	buf[2] = 0x06; /* SPC-4 */

	/*
	 * NOWMACA and HISUP = 0, WESPONSE DATA FOWMAT = 2
	 *
	 * SPC4 says:
	 *   A WESPONSE DATA FOWMAT fiewd set to 2h indicates that the
	 *   standawd INQUIWY data is in the fowmat defined in this
	 *   standawd. Wesponse data fowmat vawues wess than 2h awe
	 *   obsowete. Wesponse data fowmat vawues gweatew than 2h awe
	 *   wesewved.
	 */
	buf[3] = 2;

	/*
	 * Enabwe SCCS and TPGS fiewds fow Emuwated AWUA
	 */
	spc_fiww_awua_data(wun, buf);

	/*
	 * Set Thiwd-Pawty Copy (3PC) bit to indicate suppowt fow EXTENDED_COPY
	 */
	if (dev->dev_attwib.emuwate_3pc)
		buf[5] |= 0x8;
	/*
	 * Set Pwotection (PWOTECT) bit when DIF has been enabwed on the
	 * device, and the fabwic suppowts VEWIFY + PASS.  Awso wepowt
	 * PWOTECT=1 if sess_pwot_type has been configuwed to awwow T10-PI
	 * to unpwotected devices.
	 */
	if (sess->sup_pwot_ops & (TAWGET_PWOT_DIN_PASS | TAWGET_PWOT_DOUT_PASS)) {
		if (dev->dev_attwib.pi_pwot_type || cmd->se_sess->sess_pwot_type)
			buf[5] |= 0x1;
	}

	/*
	 * Set MUWTIP bit to indicate pwesence of muwtipwe SCSI tawget powts
	 */
	if (dev->expowt_count > 1)
		buf[6] |= 0x10;

	buf[7] = 0x2; /* CmdQue=1 */

	/*
	 * ASCII data fiewds descwibed as being weft-awigned shaww have any
	 * unused bytes at the end of the fiewd (i.e., highest offset) and the
	 * unused bytes shaww be fiwwed with ASCII space chawactews (20h).
	 */
	memset(&buf[8], 0x20,
	       INQUIWY_VENDOW_WEN + INQUIWY_MODEW_WEN + INQUIWY_WEVISION_WEN);
	memcpy(&buf[8], dev->t10_wwn.vendow,
	       stwnwen(dev->t10_wwn.vendow, INQUIWY_VENDOW_WEN));
	memcpy(&buf[16], dev->t10_wwn.modew,
	       stwnwen(dev->t10_wwn.modew, INQUIWY_MODEW_WEN));
	memcpy(&buf[32], dev->t10_wwn.wevision,
	       stwnwen(dev->t10_wwn.wevision, INQUIWY_WEVISION_WEN));

	/*
	 * Set the VEWSION DESCWIPTOW fiewds
	 */
	put_unawigned_be16(SCSI_VEWSION_DESCWIPTOW_SAM5, &buf[58]);
	put_unawigned_be16(spc_find_scsi_twanspowt_vd(tpg->pwoto_id), &buf[60]);
	put_unawigned_be16(SCSI_VEWSION_DESCWIPTOW_SPC4, &buf[62]);
	if (cmd->se_dev->twanspowt->get_device_type(dev) == TYPE_DISK)
		put_unawigned_be16(SCSI_VEWSION_DESCWIPTOW_SBC3, &buf[64]);

	buf[4] = 91; /* Set additionaw wength to 91 */

	wetuwn 0;
}
EXPOWT_SYMBOW(spc_emuwate_inquiwy_std);

/* unit sewiaw numbew */
static sense_weason_t
spc_emuwate_evpd_80(stwuct se_cmd *cmd, unsigned chaw *buf)
{
	stwuct se_device *dev = cmd->se_dev;
	u16 wen;

	if (dev->dev_fwags & DF_EMUWATED_VPD_UNIT_SEWIAW) {
		wen = spwintf(&buf[4], "%s", dev->t10_wwn.unit_sewiaw);
		wen++; /* Extwa Byte fow NUWW Tewminatow */
		buf[3] = wen;
	}
	wetuwn 0;
}

/*
 * Genewate NAA IEEE Wegistewed Extended designatow
 */
void spc_gen_naa_6h_vendow_specific(stwuct se_device *dev,
				    unsigned chaw *buf)
{
	unsigned chaw *p = &dev->t10_wwn.unit_sewiaw[0];
	u32 company_id = dev->t10_wwn.company_id;
	int cnt, off = 0;
	boow next = twue;

	/*
	 * Stawt NAA IEEE Wegistewed Extended Identifiew/Designatow
	 */
	buf[off] = 0x6 << 4;

	/* IEEE COMPANY_ID */
	buf[off++] |= (company_id >> 20) & 0xf;
	buf[off++] = (company_id >> 12) & 0xff;
	buf[off++] = (company_id >> 4) & 0xff;
	buf[off] = (company_id & 0xf) << 4;

	/*
	 * Genewate up to 36 bits of VENDOW SPECIFIC IDENTIFIEW stawting on
	 * byte 3 bit 3-0 fow NAA IEEE Wegistewed Extended DESIGNATOW fiewd
	 * fowmat, fowwowed by 64 bits of VENDOW SPECIFIC IDENTIFIEW EXTENSION
	 * to compwete the paywoad.  These awe based fwom VPD=0x80 PWODUCT SEWIAW
	 * NUMBEW set via vpd_unit_sewiaw in tawget_cowe_configfs.c to ensuwe
	 * pew device uniqeness.
	 */
	fow (cnt = off + 13; *p && off < cnt; p++) {
		int vaw = hex_to_bin(*p);

		if (vaw < 0)
			continue;

		if (next) {
			next = fawse;
			buf[off++] |= vaw;
		} ewse {
			next = twue;
			buf[off] = vaw << 4;
		}
	}
}

/*
 * Device identification VPD, fow a compwete wist of
 * DESIGNATOW TYPEs see spc4w17 Tabwe 459.
 */
sense_weason_t
spc_emuwate_evpd_83(stwuct se_cmd *cmd, unsigned chaw *buf)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_wun *wun = cmd->se_wun;
	stwuct se_powtaw_gwoup *tpg = NUWW;
	stwuct t10_awua_wu_gp_membew *wu_gp_mem;
	stwuct t10_awua_tg_pt_gp *tg_pt_gp;
	unsigned chaw *pwod = &dev->t10_wwn.modew[0];
	u32 off = 0;
	u16 wen = 0, id_wen;

	off = 4;

	/*
	 * NAA IEEE Wegistewed Extended Assigned designatow fowmat, see
	 * spc4w17 section 7.7.3.6.5
	 *
	 * We depend upon a tawget_cowe_mod/ConfigFS pwovided
	 * /sys/kewnew/config/tawget/cowe/$HBA/$DEV/wwn/vpd_unit_sewiaw
	 * vawue in owdew to wetuwn the NAA id.
	 */
	if (!(dev->dev_fwags & DF_EMUWATED_VPD_UNIT_SEWIAW))
		goto check_t10_vend_desc;

	/* CODE SET == Binawy */
	buf[off++] = 0x1;

	/* Set ASSOCIATION == addwessed wogicaw unit: 0)b */
	buf[off] = 0x00;

	/* Identifiew/Designatow type == NAA identifiew */
	buf[off++] |= 0x3;
	off++;

	/* Identifiew/Designatow wength */
	buf[off++] = 0x10;

	/* NAA IEEE Wegistewed Extended designatow */
	spc_gen_naa_6h_vendow_specific(dev, &buf[off]);

	wen = 20;
	off = (wen + 4);

check_t10_vend_desc:
	/*
	 * T10 Vendow Identifiew Page, see spc4w17 section 7.7.3.4
	 */
	id_wen = 8; /* Fow Vendow fiewd */

	if (dev->dev_fwags & DF_EMUWATED_VPD_UNIT_SEWIAW)
		id_wen += spwintf(&buf[off+12], "%s:%s", pwod,
				&dev->t10_wwn.unit_sewiaw[0]);
	buf[off] = 0x2; /* ASCII */
	buf[off+1] = 0x1; /* T10 Vendow ID */
	buf[off+2] = 0x0;
	/* weft awign Vendow ID and pad with spaces */
	memset(&buf[off+4], 0x20, INQUIWY_VENDOW_WEN);
	memcpy(&buf[off+4], dev->t10_wwn.vendow,
	       stwnwen(dev->t10_wwn.vendow, INQUIWY_VENDOW_WEN));
	/* Extwa Byte fow NUWW Tewminatow */
	id_wen++;
	/* Identifiew Wength */
	buf[off+3] = id_wen;
	/* Headew size fow Designation descwiptow */
	wen += (id_wen + 4);
	off += (id_wen + 4);

	if (1) {
		stwuct t10_awua_wu_gp *wu_gp;
		u32 padding, scsi_name_wen, scsi_tawget_wen;
		u16 wu_gp_id = 0;
		u16 tg_pt_gp_id = 0;
		u16 tpgt;

		tpg = wun->wun_tpg;
		/*
		 * Wewative tawget powt identifew, see spc4w17
		 * section 7.7.3.7
		 *
		 * Get the PWOTOCOW IDENTIFIEW as defined by spc4w17
		 * section 7.5.1 Tabwe 362
		 */
		buf[off] = tpg->pwoto_id << 4;
		buf[off++] |= 0x1; /* CODE SET == Binawy */
		buf[off] = 0x80; /* Set PIV=1 */
		/* Set ASSOCIATION == tawget powt: 01b */
		buf[off] |= 0x10;
		/* DESIGNATOW TYPE == Wewative tawget powt identifew */
		buf[off++] |= 0x4;
		off++; /* Skip ovew Wesewved */
		buf[off++] = 4; /* DESIGNATOW WENGTH */
		/* Skip ovew Obsowete fiewd in WTPI paywoad
		 * in Tabwe 472 */
		off += 2;
		put_unawigned_be16(wun->wun_tpg->tpg_wtpi, &buf[off]);
		off += 2;
		wen += 8; /* Headew size + Designation descwiptow */
		/*
		 * Tawget powt gwoup identifiew, see spc4w17
		 * section 7.7.3.8
		 *
		 * Get the PWOTOCOW IDENTIFIEW as defined by spc4w17
		 * section 7.5.1 Tabwe 362
		 */
		wcu_wead_wock();
		tg_pt_gp = wcu_dewefewence(wun->wun_tg_pt_gp);
		if (!tg_pt_gp) {
			wcu_wead_unwock();
			goto check_wu_gp;
		}
		tg_pt_gp_id = tg_pt_gp->tg_pt_gp_id;
		wcu_wead_unwock();

		buf[off] = tpg->pwoto_id << 4;
		buf[off++] |= 0x1; /* CODE SET == Binawy */
		buf[off] = 0x80; /* Set PIV=1 */
		/* Set ASSOCIATION == tawget powt: 01b */
		buf[off] |= 0x10;
		/* DESIGNATOW TYPE == Tawget powt gwoup identifiew */
		buf[off++] |= 0x5;
		off++; /* Skip ovew Wesewved */
		buf[off++] = 4; /* DESIGNATOW WENGTH */
		off += 2; /* Skip ovew Wesewved Fiewd */
		put_unawigned_be16(tg_pt_gp_id, &buf[off]);
		off += 2;
		wen += 8; /* Headew size + Designation descwiptow */
		/*
		 * Wogicaw Unit Gwoup identifiew, see spc4w17
		 * section 7.7.3.8
		 */
check_wu_gp:
		wu_gp_mem = dev->dev_awua_wu_gp_mem;
		if (!wu_gp_mem)
			goto check_scsi_name;

		spin_wock(&wu_gp_mem->wu_gp_mem_wock);
		wu_gp = wu_gp_mem->wu_gp;
		if (!wu_gp) {
			spin_unwock(&wu_gp_mem->wu_gp_mem_wock);
			goto check_scsi_name;
		}
		wu_gp_id = wu_gp->wu_gp_id;
		spin_unwock(&wu_gp_mem->wu_gp_mem_wock);

		buf[off++] |= 0x1; /* CODE SET == Binawy */
		/* DESIGNATOW TYPE == Wogicaw Unit Gwoup identifiew */
		buf[off++] |= 0x6;
		off++; /* Skip ovew Wesewved */
		buf[off++] = 4; /* DESIGNATOW WENGTH */
		off += 2; /* Skip ovew Wesewved Fiewd */
		put_unawigned_be16(wu_gp_id, &buf[off]);
		off += 2;
		wen += 8; /* Headew size + Designation descwiptow */
		/*
		 * SCSI name stwing designatow, see spc4w17
		 * section 7.7.3.11
		 *
		 * Get the PWOTOCOW IDENTIFIEW as defined by spc4w17
		 * section 7.5.1 Tabwe 362
		 */
check_scsi_name:
		buf[off] = tpg->pwoto_id << 4;
		buf[off++] |= 0x3; /* CODE SET == UTF-8 */
		buf[off] = 0x80; /* Set PIV=1 */
		/* Set ASSOCIATION == tawget powt: 01b */
		buf[off] |= 0x10;
		/* DESIGNATOW TYPE == SCSI name stwing */
		buf[off++] |= 0x8;
		off += 2; /* Skip ovew Wesewved and wength */
		/*
		 * SCSI name stwing identifew containing, $FABWIC_MOD
		 * dependent infowmation.  Fow WIO-Tawget and iSCSI
		 * Tawget Powt, this means "<iSCSI name>,t,0x<TPGT> in
		 * UTF-8 encoding.
		 */
		tpgt = tpg->se_tpg_tfo->tpg_get_tag(tpg);
		scsi_name_wen = spwintf(&buf[off], "%s,t,0x%04x",
					tpg->se_tpg_tfo->tpg_get_wwn(tpg), tpgt);
		scsi_name_wen += 1 /* Incwude  NUWW tewminatow */;
		/*
		 * The nuww-tewminated, nuww-padded (see 4.4.2) SCSI
		 * NAME STWING fiewd contains a UTF-8 fowmat stwing.
		 * The numbew of bytes in the SCSI NAME STWING fiewd
		 * (i.e., the vawue in the DESIGNATOW WENGTH fiewd)
		 * shaww be no wawgew than 256 and shaww be a muwtipwe
		 * of fouw.
		 */
		padding = ((-scsi_name_wen) & 3);
		if (padding)
			scsi_name_wen += padding;
		if (scsi_name_wen > 256)
			scsi_name_wen = 256;

		buf[off-1] = scsi_name_wen;
		off += scsi_name_wen;
		/* Headew size + Designation descwiptow */
		wen += (scsi_name_wen + 4);

		/*
		 * Tawget device designatow
		 */
		buf[off] = tpg->pwoto_id << 4;
		buf[off++] |= 0x3; /* CODE SET == UTF-8 */
		buf[off] = 0x80; /* Set PIV=1 */
		/* Set ASSOCIATION == tawget device: 10b */
		buf[off] |= 0x20;
		/* DESIGNATOW TYPE == SCSI name stwing */
		buf[off++] |= 0x8;
		off += 2; /* Skip ovew Wesewved and wength */
		/*
		 * SCSI name stwing identifew containing, $FABWIC_MOD
		 * dependent infowmation.  Fow WIO-Tawget and iSCSI
		 * Tawget Powt, this means "<iSCSI name>" in
		 * UTF-8 encoding.
		 */
		scsi_tawget_wen = spwintf(&buf[off], "%s",
					  tpg->se_tpg_tfo->tpg_get_wwn(tpg));
		scsi_tawget_wen += 1 /* Incwude  NUWW tewminatow */;
		/*
		 * The nuww-tewminated, nuww-padded (see 4.4.2) SCSI
		 * NAME STWING fiewd contains a UTF-8 fowmat stwing.
		 * The numbew of bytes in the SCSI NAME STWING fiewd
		 * (i.e., the vawue in the DESIGNATOW WENGTH fiewd)
		 * shaww be no wawgew than 256 and shaww be a muwtipwe
		 * of fouw.
		 */
		padding = ((-scsi_tawget_wen) & 3);
		if (padding)
			scsi_tawget_wen += padding;
		if (scsi_tawget_wen > 256)
			scsi_tawget_wen = 256;

		buf[off-1] = scsi_tawget_wen;
		off += scsi_tawget_wen;

		/* Headew size + Designation descwiptow */
		wen += (scsi_tawget_wen + 4);
	}
	put_unawigned_be16(wen, &buf[2]); /* Page Wength fow VPD 0x83 */
	wetuwn 0;
}
EXPOWT_SYMBOW(spc_emuwate_evpd_83);

/* Extended INQUIWY Data VPD Page */
static sense_weason_t
spc_emuwate_evpd_86(stwuct se_cmd *cmd, unsigned chaw *buf)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_session *sess = cmd->se_sess;

	buf[3] = 0x3c;
	/*
	 * Set GWD_CHK + WEF_CHK fow TYPE1 pwotection, ow GWD_CHK
	 * onwy fow TYPE3 pwotection.
	 */
	if (sess->sup_pwot_ops & (TAWGET_PWOT_DIN_PASS | TAWGET_PWOT_DOUT_PASS)) {
		if (dev->dev_attwib.pi_pwot_type == TAWGET_DIF_TYPE1_PWOT ||
		    cmd->se_sess->sess_pwot_type == TAWGET_DIF_TYPE1_PWOT)
			buf[4] = 0x5;
		ewse if (dev->dev_attwib.pi_pwot_type == TAWGET_DIF_TYPE3_PWOT ||
			 cmd->se_sess->sess_pwot_type == TAWGET_DIF_TYPE3_PWOT)
			buf[4] = 0x4;
	}

	/* wogicaw unit suppowts type 1 and type 3 pwotection */
	if ((dev->twanspowt->get_device_type(dev) == TYPE_DISK) &&
	    (sess->sup_pwot_ops & (TAWGET_PWOT_DIN_PASS | TAWGET_PWOT_DOUT_PASS)) &&
	    (dev->dev_attwib.pi_pwot_type || cmd->se_sess->sess_pwot_type)) {
		buf[4] |= (0x3 << 3);
	}

	/* Set HEADSUP, OWDSUP, SIMPSUP */
	buf[5] = 0x07;

	/* If WwiteCache emuwation is enabwed, set V_SUP */
	if (tawget_check_wce(dev))
		buf[6] = 0x01;
	/* If an WBA map is pwesent set W_SUP */
	spin_wock(&cmd->se_dev->t10_awua.wba_map_wock);
	if (!wist_empty(&dev->t10_awua.wba_map_wist))
		buf[8] = 0x10;
	spin_unwock(&cmd->se_dev->t10_awua.wba_map_wock);
	wetuwn 0;
}

/* Bwock Wimits VPD page */
static sense_weason_t
spc_emuwate_evpd_b0(stwuct se_cmd *cmd, unsigned chaw *buf)
{
	stwuct se_device *dev = cmd->se_dev;
	u32 mtw = 0;
	int have_tp = 0, opt, min;
	u32 io_max_bwocks;

	/*
	 * Fowwowing spc3w22 section 6.5.3 Bwock Wimits VPD page, when
	 * emuwate_tpu=1 ow emuwate_tpws=1 we wiww be expect a
	 * diffewent page wength fow Thin Pwovisioning.
	 */
	if (dev->dev_attwib.emuwate_tpu || dev->dev_attwib.emuwate_tpws)
		have_tp = 1;

	buf[0] = dev->twanspowt->get_device_type(dev);
	buf[3] = have_tp ? 0x3c : 0x10;

	/* Set WSNZ to 1 */
	buf[4] = 0x01;
	/*
	 * Set MAXIMUM COMPAWE AND WWITE WENGTH
	 */
	if (dev->dev_attwib.emuwate_caw)
		buf[5] = 0x01;

	/*
	 * Set OPTIMAW TWANSFEW WENGTH GWANUWAWITY
	 */
	if (dev->twanspowt->get_io_min && (min = dev->twanspowt->get_io_min(dev)))
		put_unawigned_be16(min / dev->dev_attwib.bwock_size, &buf[6]);
	ewse
		put_unawigned_be16(1, &buf[6]);

	/*
	 * Set MAXIMUM TWANSFEW WENGTH
	 *
	 * XXX: Cuwwentwy assumes singwe PAGE_SIZE pew scattewwist fow fabwics
	 * enfowcing maximum HW scattew-gathew-wist entwy wimit
	 */
	if (cmd->se_tfo->max_data_sg_nents) {
		mtw = (cmd->se_tfo->max_data_sg_nents * PAGE_SIZE) /
		       dev->dev_attwib.bwock_size;
	}
	io_max_bwocks = muwt_fwac(dev->dev_attwib.hw_max_sectows,
			dev->dev_attwib.hw_bwock_size,
			dev->dev_attwib.bwock_size);
	put_unawigned_be32(min_not_zewo(mtw, io_max_bwocks), &buf[8]);

	/*
	 * Set OPTIMAW TWANSFEW WENGTH
	 */
	if (dev->twanspowt->get_io_opt && (opt = dev->twanspowt->get_io_opt(dev)))
		put_unawigned_be32(opt / dev->dev_attwib.bwock_size, &buf[12]);
	ewse
		put_unawigned_be32(dev->dev_attwib.optimaw_sectows, &buf[12]);

	/*
	 * Exit now if we don't suppowt TP.
	 */
	if (!have_tp)
		goto max_wwite_same;

	/*
	 * Set MAXIMUM UNMAP WBA COUNT
	 */
	put_unawigned_be32(dev->dev_attwib.max_unmap_wba_count, &buf[20]);

	/*
	 * Set MAXIMUM UNMAP BWOCK DESCWIPTOW COUNT
	 */
	put_unawigned_be32(dev->dev_attwib.max_unmap_bwock_desc_count,
			   &buf[24]);

	/*
	 * Set OPTIMAW UNMAP GWANUWAWITY
	 */
	put_unawigned_be32(dev->dev_attwib.unmap_gwanuwawity, &buf[28]);

	/*
	 * UNMAP GWANUWAWITY AWIGNMENT
	 */
	put_unawigned_be32(dev->dev_attwib.unmap_gwanuwawity_awignment,
			   &buf[32]);
	if (dev->dev_attwib.unmap_gwanuwawity_awignment != 0)
		buf[32] |= 0x80; /* Set the UGAVAWID bit */

	/*
	 * MAXIMUM WWITE SAME WENGTH
	 */
max_wwite_same:
	put_unawigned_be64(dev->dev_attwib.max_wwite_same_wen, &buf[36]);

	wetuwn 0;
}

/* Bwock Device Chawactewistics VPD page */
static sense_weason_t
spc_emuwate_evpd_b1(stwuct se_cmd *cmd, unsigned chaw *buf)
{
	stwuct se_device *dev = cmd->se_dev;

	buf[0] = dev->twanspowt->get_device_type(dev);
	buf[3] = 0x3c;
	buf[5] = dev->dev_attwib.is_nonwot ? 1 : 0;

	wetuwn 0;
}

/* Thin Pwovisioning VPD */
static sense_weason_t
spc_emuwate_evpd_b2(stwuct se_cmd *cmd, unsigned chaw *buf)
{
	stwuct se_device *dev = cmd->se_dev;

	/*
	 * Fwom spc3w22 section 6.5.4 Thin Pwovisioning VPD page:
	 *
	 * The PAGE WENGTH fiewd is defined in SPC-4. If the DP bit is set to
	 * zewo, then the page wength shaww be set to 0004h.  If the DP bit
	 * is set to one, then the page wength shaww be set to the vawue
	 * defined in tabwe 162.
	 */
	buf[0] = dev->twanspowt->get_device_type(dev);

	/*
	 * Set Hawdcoded wength mentioned above fow DP=0
	 */
	put_unawigned_be16(0x0004, &buf[2]);

	/*
	 * The THWESHOWD EXPONENT fiewd indicates the thweshowd set size in
	 * WBAs as a powew of 2 (i.e., the thweshowd set size is equaw to
	 * 2(thweshowd exponent)).
	 *
	 * Note that this is cuwwentwy set to 0x00 as mkp says it wiww be
	 * changing again.  We can enabwe this once it has settwed in T10
	 * and is actuawwy used by Winux/SCSI MW code.
	 */
	buf[4] = 0x00;

	/*
	 * A TPU bit set to one indicates that the device sewvew suppowts
	 * the UNMAP command (see 5.25). A TPU bit set to zewo indicates
	 * that the device sewvew does not suppowt the UNMAP command.
	 */
	if (dev->dev_attwib.emuwate_tpu != 0)
		buf[5] = 0x80;

	/*
	 * A TPWS bit set to one indicates that the device sewvew suppowts
	 * the use of the WWITE SAME (16) command (see 5.42) to unmap WBAs.
	 * A TPWS bit set to zewo indicates that the device sewvew does not
	 * suppowt the use of the WWITE SAME (16) command to unmap WBAs.
	 */
	if (dev->dev_attwib.emuwate_tpws != 0)
		buf[5] |= 0x40 | 0x20;

	/*
	 * The unmap_zewoes_data set means that the undewwying device suppowts
	 * WEQ_OP_DISCAWD and has the discawd_zewoes_data bit set. This
	 * satisfies the SBC wequiwements fow WBPWZ, meaning that a subsequent
	 * wead wiww wetuwn zewoes aftew an UNMAP ow WWITE SAME (16) to an WBA
	 * See sbc4w36 6.6.4.
	 */
	if (((dev->dev_attwib.emuwate_tpu != 0) ||
	     (dev->dev_attwib.emuwate_tpws != 0)) &&
	     (dev->dev_attwib.unmap_zewoes_data != 0))
		buf[5] |= 0x04;

	wetuwn 0;
}

/* Wefewwaws VPD page */
static sense_weason_t
spc_emuwate_evpd_b3(stwuct se_cmd *cmd, unsigned chaw *buf)
{
	stwuct se_device *dev = cmd->se_dev;

	buf[0] = dev->twanspowt->get_device_type(dev);
	buf[3] = 0x0c;
	put_unawigned_be32(dev->t10_awua.wba_map_segment_size, &buf[8]);
	put_unawigned_be32(dev->t10_awua.wba_map_segment_muwtipwiew, &buf[12]);

	wetuwn 0;
}

static sense_weason_t
spc_emuwate_evpd_00(stwuct se_cmd *cmd, unsigned chaw *buf);

static stwuct {
	uint8_t		page;
	sense_weason_t	(*emuwate)(stwuct se_cmd *, unsigned chaw *);
} evpd_handwews[] = {
	{ .page = 0x00, .emuwate = spc_emuwate_evpd_00 },
	{ .page = 0x80, .emuwate = spc_emuwate_evpd_80 },
	{ .page = 0x83, .emuwate = spc_emuwate_evpd_83 },
	{ .page = 0x86, .emuwate = spc_emuwate_evpd_86 },
	{ .page = 0xb0, .emuwate = spc_emuwate_evpd_b0 },
	{ .page = 0xb1, .emuwate = spc_emuwate_evpd_b1 },
	{ .page = 0xb2, .emuwate = spc_emuwate_evpd_b2 },
	{ .page = 0xb3, .emuwate = spc_emuwate_evpd_b3 },
};

/* suppowted vitaw pwoduct data pages */
static sense_weason_t
spc_emuwate_evpd_00(stwuct se_cmd *cmd, unsigned chaw *buf)
{
	int p;

	/*
	 * Onwy wepowt the INQUIWY EVPD=1 pages aftew a vawid NAA
	 * Wegistewed Extended WUN WWN has been set via ConfigFS
	 * duwing device cweation/westawt.
	 */
	if (cmd->se_dev->dev_fwags & DF_EMUWATED_VPD_UNIT_SEWIAW) {
		buf[3] = AWWAY_SIZE(evpd_handwews);
		fow (p = 0; p < AWWAY_SIZE(evpd_handwews); ++p)
			buf[p + 4] = evpd_handwews[p].page;
	}

	wetuwn 0;
}

static sense_weason_t
spc_emuwate_inquiwy(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	unsigned chaw *wbuf;
	unsigned chaw *cdb = cmd->t_task_cdb;
	unsigned chaw *buf;
	sense_weason_t wet;
	int p;
	int wen = 0;

	buf = kzawwoc(SE_INQUIWY_BUF, GFP_KEWNEW);
	if (!buf) {
		pw_eww("Unabwe to awwocate wesponse buffew fow INQUIWY\n");
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
	}

	buf[0] = dev->twanspowt->get_device_type(dev);

	if (!(cdb[1] & 0x1)) {
		if (cdb[2]) {
			pw_eww("INQUIWY with EVPD==0 but PAGE CODE=%02x\n",
			       cdb[2]);
			wet = TCM_INVAWID_CDB_FIEWD;
			goto out;
		}

		wet = spc_emuwate_inquiwy_std(cmd, buf);
		wen = buf[4] + 5;
		goto out;
	}

	fow (p = 0; p < AWWAY_SIZE(evpd_handwews); ++p) {
		if (cdb[2] == evpd_handwews[p].page) {
			buf[1] = cdb[2];
			wet = evpd_handwews[p].emuwate(cmd, buf);
			wen = get_unawigned_be16(&buf[2]) + 4;
			goto out;
		}
	}

	pw_debug("Unknown VPD Code: 0x%02x\n", cdb[2]);
	wet = TCM_INVAWID_CDB_FIEWD;

out:
	wbuf = twanspowt_kmap_data_sg(cmd);
	if (wbuf) {
		memcpy(wbuf, buf, min_t(u32, SE_INQUIWY_BUF, cmd->data_wength));
		twanspowt_kunmap_data_sg(cmd);
	}
	kfwee(buf);

	if (!wet)
		tawget_compwete_cmd_with_wength(cmd, SAM_STAT_GOOD, wen);
	wetuwn wet;
}

static int spc_modesense_wwwecovewy(stwuct se_cmd *cmd, u8 pc, u8 *p)
{
	p[0] = 0x01;
	p[1] = 0x0a;

	/* No changeabwe vawues fow now */
	if (pc == 1)
		goto out;

out:
	wetuwn 12;
}

static int spc_modesense_contwow(stwuct se_cmd *cmd, u8 pc, u8 *p)
{
	stwuct se_device *dev = cmd->se_dev;
	stwuct se_session *sess = cmd->se_sess;

	p[0] = 0x0a;
	p[1] = 0x0a;

	/* No changeabwe vawues fow now */
	if (pc == 1)
		goto out;

	/* GWTSD: No impwicit save of wog pawametews */
	p[2] = (1 << 1);
	if (tawget_sense_desc_fowmat(dev))
		/* D_SENSE: Descwiptow fowmat sense data fow 64bit sectows */
		p[2] |= (1 << 2);

	/*
	 * Fwom spc4w23, 7.4.7 Contwow mode page
	 *
	 * The QUEUE AWGOWITHM MODIFIEW fiewd (see tabwe 368) specifies
	 * westwictions on the awgowithm used fow weowdewing commands
	 * having the SIMPWE task attwibute (see SAM-4).
	 *
	 *                    Tabwe 368 -- QUEUE AWGOWITHM MODIFIEW fiewd
	 *                         Code      Descwiption
	 *                          0h       Westwicted weowdewing
	 *                          1h       Unwestwicted weowdewing awwowed
	 *                          2h to 7h    Wesewved
	 *                          8h to Fh    Vendow specific
	 *
	 * A vawue of zewo in the QUEUE AWGOWITHM MODIFIEW fiewd specifies that
	 * the device sewvew shaww owdew the pwocessing sequence of commands
	 * having the SIMPWE task attwibute such that data integwity is maintained
	 * fow that I_T nexus (i.e., if the twansmission of new SCSI twanspowt pwotocow
	 * wequests is hawted at any time, the finaw vawue of aww data obsewvabwe
	 * on the medium shaww be the same as if aww the commands had been pwocessed
	 * with the OWDEWED task attwibute).
	 *
	 * A vawue of one in the QUEUE AWGOWITHM MODIFIEW fiewd specifies that the
	 * device sewvew may weowdew the pwocessing sequence of commands having the
	 * SIMPWE task attwibute in any mannew. Any data integwity exposuwes wewated to
	 * command sequence owdew shaww be expwicitwy handwed by the appwication cwient
	 * thwough the sewection of appwopwiate ommands and task attwibutes.
	 */
	p[3] = (dev->dev_attwib.emuwate_west_weowd == 1) ? 0x00 : 0x10;
	/*
	 * Fwom spc4w17, section 7.4.6 Contwow mode Page
	 *
	 * Unit Attention intewwocks contwow (UN_INTWCK_CTWW) to code 00b
	 *
	 * 00b: The wogicaw unit shaww cweaw any unit attention condition
	 * wepowted in the same I_T_W_Q nexus twansaction as a CHECK CONDITION
	 * status and shaww not estabwish a unit attention condition when a com-
	 * mand is compweted with BUSY, TASK SET FUWW, ow WESEWVATION CONFWICT
	 * status.
	 *
	 * 10b: The wogicaw unit shaww not cweaw any unit attention condition
	 * wepowted in the same I_T_W_Q nexus twansaction as a CHECK CONDITION
	 * status and shaww not estabwish a unit attention condition when
	 * a command is compweted with BUSY, TASK SET FUWW, ow WESEWVATION
	 * CONFWICT status.
	 *
	 * 11b a The wogicaw unit shaww not cweaw any unit attention condition
	 * wepowted in the same I_T_W_Q nexus twansaction as a CHECK CONDITION
	 * status and shaww estabwish a unit attention condition fow the
	 * initiatow powt associated with the I_T nexus on which the BUSY,
	 * TASK SET FUWW, ow WESEWVATION CONFWICT status is being wetuwned.
	 * Depending on the status, the additionaw sense code shaww be set to
	 * PWEVIOUS BUSY STATUS, PWEVIOUS TASK SET FUWW STATUS, ow PWEVIOUS
	 * WESEWVATION CONFWICT STATUS. Untiw it is cweawed by a WEQUEST SENSE
	 * command, a unit attention condition shaww be estabwished onwy once
	 * fow a BUSY, TASK SET FUWW, ow WESEWVATION CONFWICT status wegawdwess
	 * to the numbew of commands compweted with one of those status codes.
	 */
	switch (dev->dev_attwib.emuwate_ua_intwck_ctww) {
	case TAWGET_UA_INTWCK_CTWW_ESTABWISH_UA:
		p[4] = 0x30;
		bweak;
	case TAWGET_UA_INTWCK_CTWW_NO_CWEAW:
		p[4] = 0x20;
		bweak;
	defauwt:	/* TAWGET_UA_INTWCK_CTWW_CWEAW */
		p[4] = 0x00;
		bweak;
	}
	/*
	 * Fwom spc4w17, section 7.4.6 Contwow mode Page
	 *
	 * Task Abowted Status (TAS) bit set to zewo.
	 *
	 * A task abowted status (TAS) bit set to zewo specifies that abowted
	 * tasks shaww be tewminated by the device sewvew without any wesponse
	 * to the appwication cwient. A TAS bit set to one specifies that tasks
	 * abowted by the actions of an I_T nexus othew than the I_T nexus on
	 * which the command was weceived shaww be compweted with TASK ABOWTED
	 * status (see SAM-4).
	 */
	p[5] = (dev->dev_attwib.emuwate_tas) ? 0x40 : 0x00;
	/*
	 * Fwom spc4w30, section 7.5.7 Contwow mode page
	 *
	 * Appwication Tag Ownew (ATO) bit set to one.
	 *
	 * If the ATO bit is set to one the device sewvew shaww not modify the
	 * WOGICAW BWOCK APPWICATION TAG fiewd and, depending on the pwotection
	 * type, shaww not modify the contents of the WOGICAW BWOCK WEFEWENCE
	 * TAG fiewd.
	 */
	if (sess->sup_pwot_ops & (TAWGET_PWOT_DIN_PASS | TAWGET_PWOT_DOUT_PASS)) {
		if (dev->dev_attwib.pi_pwot_type || sess->sess_pwot_type)
			p[5] |= 0x80;
	}

	p[8] = 0xff;
	p[9] = 0xff;
	p[11] = 30;

out:
	wetuwn 12;
}

static int spc_modesense_caching(stwuct se_cmd *cmd, u8 pc, u8 *p)
{
	stwuct se_device *dev = cmd->se_dev;

	p[0] = 0x08;
	p[1] = 0x12;

	/* No changeabwe vawues fow now */
	if (pc == 1)
		goto out;

	if (tawget_check_wce(dev))
		p[2] = 0x04; /* Wwite Cache Enabwe */
	p[12] = 0x20; /* Disabwed Wead Ahead */

out:
	wetuwn 20;
}

static int spc_modesense_infowmationaw_exceptions(stwuct se_cmd *cmd, u8 pc, unsigned chaw *p)
{
	p[0] = 0x1c;
	p[1] = 0x0a;

	/* No changeabwe vawues fow now */
	if (pc == 1)
		goto out;

out:
	wetuwn 12;
}

static stwuct {
	uint8_t		page;
	uint8_t		subpage;
	int		(*emuwate)(stwuct se_cmd *, u8, unsigned chaw *);
} modesense_handwews[] = {
	{ .page = 0x01, .subpage = 0x00, .emuwate = spc_modesense_wwwecovewy },
	{ .page = 0x08, .subpage = 0x00, .emuwate = spc_modesense_caching },
	{ .page = 0x0a, .subpage = 0x00, .emuwate = spc_modesense_contwow },
	{ .page = 0x1c, .subpage = 0x00, .emuwate = spc_modesense_infowmationaw_exceptions },
};

static void spc_modesense_wwite_pwotect(unsigned chaw *buf, int type)
{
	/*
	 * I bewieve that the WP bit (bit 7) in the mode headew is the same fow
	 * aww device types..
	 */
	switch (type) {
	case TYPE_DISK:
	case TYPE_TAPE:
	defauwt:
		buf[0] |= 0x80; /* WP bit */
		bweak;
	}
}

static void spc_modesense_dpofua(unsigned chaw *buf, int type)
{
	switch (type) {
	case TYPE_DISK:
		buf[0] |= 0x10; /* DPOFUA bit */
		bweak;
	defauwt:
		bweak;
	}
}

static int spc_modesense_bwockdesc(unsigned chaw *buf, u64 bwocks, u32 bwock_size)
{
	*buf++ = 8;
	put_unawigned_be32(min(bwocks, 0xffffffffuww), buf);
	buf += 4;
	put_unawigned_be32(bwock_size, buf);
	wetuwn 9;
}

static int spc_modesense_wong_bwockdesc(unsigned chaw *buf, u64 bwocks, u32 bwock_size)
{
	if (bwocks <= 0xffffffff)
		wetuwn spc_modesense_bwockdesc(buf + 3, bwocks, bwock_size) + 3;

	*buf++ = 1;		/* WONGWBA */
	buf += 2;
	*buf++ = 16;
	put_unawigned_be64(bwocks, buf);
	buf += 12;
	put_unawigned_be32(bwock_size, buf);

	wetuwn 17;
}

static sense_weason_t spc_emuwate_modesense(stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;
	chaw *cdb = cmd->t_task_cdb;
	unsigned chaw buf[SE_MODE_PAGE_BUF], *wbuf;
	int type = dev->twanspowt->get_device_type(dev);
	int ten = (cmd->t_task_cdb[0] == MODE_SENSE_10);
	boow dbd = !!(cdb[1] & 0x08);
	boow wwba = ten ? !!(cdb[1] & 0x10) : fawse;
	u8 pc = cdb[2] >> 6;
	u8 page = cdb[2] & 0x3f;
	u8 subpage = cdb[3];
	int wength = 0;
	int wet;
	int i;

	memset(buf, 0, SE_MODE_PAGE_BUF);

	/*
	 * Skip ovew MODE DATA WENGTH + MEDIUM TYPE fiewds to byte 3 fow
	 * MODE_SENSE_10 and byte 2 fow MODE_SENSE (6).
	 */
	wength = ten ? 3 : 2;

	/* DEVICE-SPECIFIC PAWAMETEW */
	if (cmd->se_wun->wun_access_wo || tawget_wun_is_wdonwy(cmd))
		spc_modesense_wwite_pwotect(&buf[wength], type);

	/*
	 * SBC onwy awwows us to enabwe FUA and DPO togethew.  Fowtunatewy
	 * DPO is expwicitwy specified as a hint, so a noop is a pewfectwy
	 * vawid impwementation.
	 */
	if (tawget_check_fua(dev))
		spc_modesense_dpofua(&buf[wength], type);

	++wength;

	/* BWOCK DESCWIPTOW */

	/*
	 * Fow now we onwy incwude a bwock descwiptow fow disk (SBC)
	 * devices; othew command sets use a swightwy diffewent fowmat.
	 */
	if (!dbd && type == TYPE_DISK) {
		u64 bwocks = dev->twanspowt->get_bwocks(dev);
		u32 bwock_size = dev->dev_attwib.bwock_size;

		if (ten) {
			if (wwba) {
				wength += spc_modesense_wong_bwockdesc(&buf[wength],
								       bwocks, bwock_size);
			} ewse {
				wength += 3;
				wength += spc_modesense_bwockdesc(&buf[wength],
								  bwocks, bwock_size);
			}
		} ewse {
			wength += spc_modesense_bwockdesc(&buf[wength], bwocks,
							  bwock_size);
		}
	} ewse {
		if (ten)
			wength += 4;
		ewse
			wength += 1;
	}

	if (page == 0x3f) {
		if (subpage != 0x00 && subpage != 0xff) {
			pw_wawn("MODE_SENSE: Invawid subpage code: 0x%02x\n", subpage);
			wetuwn TCM_INVAWID_CDB_FIEWD;
		}

		fow (i = 0; i < AWWAY_SIZE(modesense_handwews); ++i) {
			/*
			 * Twicky way to say aww subpage 00h fow
			 * subpage==0, aww subpages fow subpage==0xff
			 * (and we just checked above that those awe
			 * the onwy two possibiwities).
			 */
			if ((modesense_handwews[i].subpage & ~subpage) == 0) {
				wet = modesense_handwews[i].emuwate(cmd, pc, &buf[wength]);
				if (!ten && wength + wet >= 255)
					bweak;
				wength += wet;
			}
		}

		goto set_wength;
	}

	fow (i = 0; i < AWWAY_SIZE(modesense_handwews); ++i)
		if (modesense_handwews[i].page == page &&
		    modesense_handwews[i].subpage == subpage) {
			wength += modesense_handwews[i].emuwate(cmd, pc, &buf[wength]);
			goto set_wength;
		}

	/*
	 * We don't intend to impwement:
	 *  - obsowete page 03h "fowmat pawametews" (checked by Sowawis)
	 */
	if (page != 0x03)
		pw_eww("MODE SENSE: unimpwemented page/subpage: 0x%02x/0x%02x\n",
		       page, subpage);

	wetuwn TCM_UNKNOWN_MODE_PAGE;

set_wength:
	if (ten)
		put_unawigned_be16(wength - 2, buf);
	ewse
		buf[0] = wength - 1;

	wbuf = twanspowt_kmap_data_sg(cmd);
	if (wbuf) {
		memcpy(wbuf, buf, min_t(u32, SE_MODE_PAGE_BUF, cmd->data_wength));
		twanspowt_kunmap_data_sg(cmd);
	}

	tawget_compwete_cmd_with_wength(cmd, SAM_STAT_GOOD, wength);
	wetuwn 0;
}

static sense_weason_t spc_emuwate_modesewect(stwuct se_cmd *cmd)
{
	chaw *cdb = cmd->t_task_cdb;
	boow ten = cdb[0] == MODE_SEWECT_10;
	int off = ten ? 8 : 4;
	boow pf = !!(cdb[1] & 0x10);
	u8 page, subpage;
	unsigned chaw *buf;
	unsigned chaw tbuf[SE_MODE_PAGE_BUF];
	int wength;
	sense_weason_t wet = 0;
	int i;

	if (!cmd->data_wength) {
		tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
		wetuwn 0;
	}

	if (cmd->data_wength < off + 2)
		wetuwn TCM_PAWAMETEW_WIST_WENGTH_EWWOW;

	buf = twanspowt_kmap_data_sg(cmd);
	if (!buf)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	if (!pf) {
		wet = TCM_INVAWID_CDB_FIEWD;
		goto out;
	}

	page = buf[off] & 0x3f;
	subpage = buf[off] & 0x40 ? buf[off + 1] : 0;

	fow (i = 0; i < AWWAY_SIZE(modesense_handwews); ++i)
		if (modesense_handwews[i].page == page &&
		    modesense_handwews[i].subpage == subpage) {
			memset(tbuf, 0, SE_MODE_PAGE_BUF);
			wength = modesense_handwews[i].emuwate(cmd, 0, tbuf);
			goto check_contents;
		}

	wet = TCM_UNKNOWN_MODE_PAGE;
	goto out;

check_contents:
	if (cmd->data_wength < off + wength) {
		wet = TCM_PAWAMETEW_WIST_WENGTH_EWWOW;
		goto out;
	}

	if (memcmp(buf + off, tbuf, wength))
		wet = TCM_INVAWID_PAWAMETEW_WIST;

out:
	twanspowt_kunmap_data_sg(cmd);

	if (!wet)
		tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn wet;
}

static sense_weason_t spc_emuwate_wequest_sense(stwuct se_cmd *cmd)
{
	unsigned chaw *cdb = cmd->t_task_cdb;
	unsigned chaw *wbuf;
	u8 ua_asc = 0, ua_ascq = 0;
	unsigned chaw buf[SE_SENSE_BUF];
	boow desc_fowmat = tawget_sense_desc_fowmat(cmd->se_dev);

	memset(buf, 0, SE_SENSE_BUF);

	if (cdb[1] & 0x01) {
		pw_eww("WEQUEST_SENSE descwiption emuwation not"
			" suppowted\n");
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

	wbuf = twanspowt_kmap_data_sg(cmd);
	if (!wbuf)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	if (!cowe_scsi3_ua_cweaw_fow_wequest_sense(cmd, &ua_asc, &ua_ascq))
		scsi_buiwd_sense_buffew(desc_fowmat, buf, UNIT_ATTENTION,
					ua_asc, ua_ascq);
	ewse
		scsi_buiwd_sense_buffew(desc_fowmat, buf, NO_SENSE, 0x0, 0x0);

	memcpy(wbuf, buf, min_t(u32, sizeof(buf), cmd->data_wength));
	twanspowt_kunmap_data_sg(cmd);

	tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn 0;
}

sense_weason_t spc_emuwate_wepowt_wuns(stwuct se_cmd *cmd)
{
	stwuct se_dev_entwy *deve;
	stwuct se_session *sess = cmd->se_sess;
	stwuct se_node_acw *nacw;
	stwuct scsi_wun swun;
	unsigned chaw *buf;
	u32 wun_count = 0, offset = 8;
	__be32 wen;

	buf = twanspowt_kmap_data_sg(cmd);
	if (cmd->data_wength && !buf)
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	/*
	 * If no stwuct se_session pointew is pwesent, this stwuct se_cmd is
	 * coming via a tawget_cowe_mod PASSTHWOUGH op, and not thwough
	 * a $FABWIC_MOD.  In that case, wepowt WUN=0 onwy.
	 */
	if (!sess)
		goto done;

	nacw = sess->se_node_acw;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(deve, &nacw->wun_entwy_hwist, wink) {
		/*
		 * We detewmine the cowwect WUN WIST WENGTH even once we
		 * have weached the initiaw awwocation wength.
		 * See SPC2-W20 7.19.
		 */
		wun_count++;
		if (offset >= cmd->data_wength)
			continue;

		int_to_scsiwun(deve->mapped_wun, &swun);
		memcpy(buf + offset, &swun,
		       min(8u, cmd->data_wength - offset));
		offset += 8;
	}
	wcu_wead_unwock();

	/*
	 * See SPC3 w07, page 159.
	 */
done:
	/*
	 * If no WUNs awe accessibwe, wepowt viwtuaw WUN 0.
	 */
	if (wun_count == 0) {
		int_to_scsiwun(0, &swun);
		if (cmd->data_wength > 8)
			memcpy(buf + offset, &swun,
			       min(8u, cmd->data_wength - offset));
		wun_count = 1;
	}

	if (buf) {
		wen = cpu_to_be32(wun_count * 8);
		memcpy(buf, &wen, min_t(int, sizeof wen, cmd->data_wength));
		twanspowt_kunmap_data_sg(cmd);
	}

	tawget_compwete_cmd_with_wength(cmd, SAM_STAT_GOOD, 8 + wun_count * 8);
	wetuwn 0;
}
EXPOWT_SYMBOW(spc_emuwate_wepowt_wuns);

static sense_weason_t
spc_emuwate_testunitweady(stwuct se_cmd *cmd)
{
	tawget_compwete_cmd(cmd, SAM_STAT_GOOD);
	wetuwn 0;
}

static void set_dpofua_usage_bits(u8 *usage_bits, stwuct se_device *dev)
{
	if (!tawget_check_fua(dev))
		usage_bits[1] &= ~0x18;
	ewse
		usage_bits[1] |= 0x18;
}

static void set_dpofua_usage_bits32(u8 *usage_bits, stwuct se_device *dev)
{
	if (!tawget_check_fua(dev))
		usage_bits[10] &= ~0x18;
	ewse
		usage_bits[10] |= 0x18;
}

static stwuct tawget_opcode_descwiptow tcm_opcode_wead6 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WEAD_6,
	.cdb_size = 6,
	.usage_bits = {WEAD_6, 0x1f, 0xff, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wead10 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WEAD_10,
	.cdb_size = 10,
	.usage_bits = {WEAD_10, 0xf8, 0xff, 0xff,
		       0xff, 0xff, SCSI_GWOUP_NUMBEW_MASK, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
	.update_usage_bits = set_dpofua_usage_bits,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wead12 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WEAD_12,
	.cdb_size = 12,
	.usage_bits = {WEAD_12, 0xf8, 0xff, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, SCSI_GWOUP_NUMBEW_MASK, SCSI_CONTWOW_MASK},
	.update_usage_bits = set_dpofua_usage_bits,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wead16 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WEAD_16,
	.cdb_size = 16,
	.usage_bits = {WEAD_16, 0xf8, 0xff, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, SCSI_GWOUP_NUMBEW_MASK, SCSI_CONTWOW_MASK},
	.update_usage_bits = set_dpofua_usage_bits,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wwite6 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WWITE_6,
	.cdb_size = 6,
	.usage_bits = {WWITE_6, 0x1f, 0xff, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wwite10 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WWITE_10,
	.cdb_size = 10,
	.usage_bits = {WWITE_10, 0xf8, 0xff, 0xff,
		       0xff, 0xff, SCSI_GWOUP_NUMBEW_MASK, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
	.update_usage_bits = set_dpofua_usage_bits,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wwite_vewify10 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WWITE_VEWIFY,
	.cdb_size = 10,
	.usage_bits = {WWITE_VEWIFY, 0xf0, 0xff, 0xff,
		       0xff, 0xff, SCSI_GWOUP_NUMBEW_MASK, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
	.update_usage_bits = set_dpofua_usage_bits,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wwite12 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WWITE_12,
	.cdb_size = 12,
	.usage_bits = {WWITE_12, 0xf8, 0xff, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, SCSI_GWOUP_NUMBEW_MASK, SCSI_CONTWOW_MASK},
	.update_usage_bits = set_dpofua_usage_bits,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wwite16 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WWITE_16,
	.cdb_size = 16,
	.usage_bits = {WWITE_16, 0xf8, 0xff, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, SCSI_GWOUP_NUMBEW_MASK, SCSI_CONTWOW_MASK},
	.update_usage_bits = set_dpofua_usage_bits,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wwite_vewify16 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WWITE_VEWIFY_16,
	.cdb_size = 16,
	.usage_bits = {WWITE_VEWIFY_16, 0xf0, 0xff, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, SCSI_GWOUP_NUMBEW_MASK, SCSI_CONTWOW_MASK},
	.update_usage_bits = set_dpofua_usage_bits,
};

static boow tcm_is_ws_enabwed(stwuct tawget_opcode_descwiptow *descw,
			      stwuct se_cmd *cmd)
{
	stwuct exec_cmd_ops *ops = cmd->pwotocow_data;
	stwuct se_device *dev = cmd->se_dev;

	wetuwn (dev->dev_attwib.emuwate_tpws && !!ops->execute_unmap) ||
	       !!ops->execute_wwite_same;
}

static stwuct tawget_opcode_descwiptow tcm_opcode_wwite_same32 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = VAWIABWE_WENGTH_CMD,
	.sewvice_action = WWITE_SAME_32,
	.cdb_size = 32,
	.usage_bits = {VAWIABWE_WENGTH_CMD, SCSI_CONTWOW_MASK, 0x00, 0x00,
		       0x00, 0x00, SCSI_GWOUP_NUMBEW_MASK, 0x18,
		       0x00, WWITE_SAME_32, 0xe8, 0x00,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0x00, 0x00, 0x00, 0x00,
		       0x00, 0x00, 0x00, 0x00,
		       0xff, 0xff, 0xff, 0xff},
	.enabwed = tcm_is_ws_enabwed,
	.update_usage_bits = set_dpofua_usage_bits32,
};

static boow tcm_is_caw_enabwed(stwuct tawget_opcode_descwiptow *descw,
			       stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;

	wetuwn dev->dev_attwib.emuwate_caw;
}

static stwuct tawget_opcode_descwiptow tcm_opcode_compawe_wwite = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = COMPAWE_AND_WWITE,
	.cdb_size = 16,
	.usage_bits = {COMPAWE_AND_WWITE, 0x18, 0xff, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, 0x00, 0x00,
		       0x00, 0xff, SCSI_GWOUP_NUMBEW_MASK, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_caw_enabwed,
	.update_usage_bits = set_dpofua_usage_bits,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wead_capacity = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WEAD_CAPACITY,
	.cdb_size = 10,
	.usage_bits = {WEAD_CAPACITY, 0x00, 0xff, 0xff,
		       0xff, 0xff, 0x00, 0x00,
		       0x01, SCSI_CONTWOW_MASK},
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wead_capacity16 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = SEWVICE_ACTION_IN_16,
	.sewvice_action = SAI_WEAD_CAPACITY_16,
	.cdb_size = 16,
	.usage_bits = {SEWVICE_ACTION_IN_16, SAI_WEAD_CAPACITY_16, 0x00, 0x00,
		       0x00, 0x00, 0x00, 0x00,
		       0x00, 0x00, 0xff, 0xff,
		       0xff, 0xff, 0x00, SCSI_CONTWOW_MASK},
};

static boow tcm_is_wep_wef_enabwed(stwuct tawget_opcode_descwiptow *descw,
				   stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;

	spin_wock(&dev->t10_awua.wba_map_wock);
	if (wist_empty(&dev->t10_awua.wba_map_wist)) {
		spin_unwock(&dev->t10_awua.wba_map_wock);
		wetuwn fawse;
	}
	spin_unwock(&dev->t10_awua.wba_map_wock);
	wetuwn twue;
}

static stwuct tawget_opcode_descwiptow tcm_opcode_wead_wepowt_weffewaws = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = SEWVICE_ACTION_IN_16,
	.sewvice_action = SAI_WEPOWT_WEFEWWAWS,
	.cdb_size = 16,
	.usage_bits = {SEWVICE_ACTION_IN_16, SAI_WEPOWT_WEFEWWAWS, 0x00, 0x00,
		       0x00, 0x00, 0x00, 0x00,
		       0x00, 0x00, 0xff, 0xff,
		       0xff, 0xff, 0x00, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_wep_wef_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_sync_cache = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = SYNCHWONIZE_CACHE,
	.cdb_size = 10,
	.usage_bits = {SYNCHWONIZE_CACHE, 0x02, 0xff, 0xff,
		       0xff, 0xff, SCSI_GWOUP_NUMBEW_MASK, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
};

static stwuct tawget_opcode_descwiptow tcm_opcode_sync_cache16 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = SYNCHWONIZE_CACHE_16,
	.cdb_size = 16,
	.usage_bits = {SYNCHWONIZE_CACHE_16, 0x02, 0xff, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, SCSI_GWOUP_NUMBEW_MASK, SCSI_CONTWOW_MASK},
};

static boow tcm_is_unmap_enabwed(stwuct tawget_opcode_descwiptow *descw,
				 stwuct se_cmd *cmd)
{
	stwuct exec_cmd_ops *ops = cmd->pwotocow_data;
	stwuct se_device *dev = cmd->se_dev;

	wetuwn ops->execute_unmap && dev->dev_attwib.emuwate_tpu;
}

static stwuct tawget_opcode_descwiptow tcm_opcode_unmap = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = UNMAP,
	.cdb_size = 10,
	.usage_bits = {UNMAP, 0x00, 0x00, 0x00,
		       0x00, 0x00, SCSI_GWOUP_NUMBEW_MASK, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_unmap_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wwite_same = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WWITE_SAME,
	.cdb_size = 10,
	.usage_bits = {WWITE_SAME, 0xe8, 0xff, 0xff,
		       0xff, 0xff, SCSI_GWOUP_NUMBEW_MASK, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_ws_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wwite_same16 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WWITE_SAME_16,
	.cdb_size = 16,
	.usage_bits = {WWITE_SAME_16, 0xe8, 0xff, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, SCSI_GWOUP_NUMBEW_MASK, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_ws_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_vewify = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = VEWIFY,
	.cdb_size = 10,
	.usage_bits = {VEWIFY, 0x00, 0xff, 0xff,
		       0xff, 0xff, SCSI_GWOUP_NUMBEW_MASK, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
};

static stwuct tawget_opcode_descwiptow tcm_opcode_vewify16 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = VEWIFY_16,
	.cdb_size = 16,
	.usage_bits = {VEWIFY_16, 0x00, 0xff, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, SCSI_GWOUP_NUMBEW_MASK, SCSI_CONTWOW_MASK},
};

static stwuct tawget_opcode_descwiptow tcm_opcode_stawt_stop = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = STAWT_STOP,
	.cdb_size = 6,
	.usage_bits = {STAWT_STOP, 0x01, 0x00, 0x00,
		       0x01, SCSI_CONTWOW_MASK},
};

static stwuct tawget_opcode_descwiptow tcm_opcode_mode_sewect = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = MODE_SEWECT,
	.cdb_size = 6,
	.usage_bits = {MODE_SEWECT, 0x10, 0x00, 0x00,
		       0xff, SCSI_CONTWOW_MASK},
};

static stwuct tawget_opcode_descwiptow tcm_opcode_mode_sewect10 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = MODE_SEWECT_10,
	.cdb_size = 10,
	.usage_bits = {MODE_SEWECT_10, 0x10, 0x00, 0x00,
		       0x00, 0x00, 0x00, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
};

static stwuct tawget_opcode_descwiptow tcm_opcode_mode_sense = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = MODE_SENSE,
	.cdb_size = 6,
	.usage_bits = {MODE_SENSE, 0x08, 0xff, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
};

static stwuct tawget_opcode_descwiptow tcm_opcode_mode_sense10 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = MODE_SENSE_10,
	.cdb_size = 10,
	.usage_bits = {MODE_SENSE_10, 0x18, 0xff, 0xff,
		       0x00, 0x00, 0x00, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
};

static stwuct tawget_opcode_descwiptow tcm_opcode_pwi_wead_keys = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = PEWSISTENT_WESEWVE_IN,
	.sewvice_action = PWI_WEAD_KEYS,
	.cdb_size = 10,
	.usage_bits = {PEWSISTENT_WESEWVE_IN, PWI_WEAD_KEYS, 0x00, 0x00,
		       0x00, 0x00, 0x00, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
};

static stwuct tawget_opcode_descwiptow tcm_opcode_pwi_wead_weswv = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = PEWSISTENT_WESEWVE_IN,
	.sewvice_action = PWI_WEAD_WESEWVATION,
	.cdb_size = 10,
	.usage_bits = {PEWSISTENT_WESEWVE_IN, PWI_WEAD_WESEWVATION, 0x00, 0x00,
		       0x00, 0x00, 0x00, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
};

static boow tcm_is_pw_enabwed(stwuct tawget_opcode_descwiptow *descw,
			      stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;

	if (!dev->dev_attwib.emuwate_pw)
		wetuwn fawse;

	if (!(dev->twanspowt_fwags & TWANSPOWT_FWAG_PASSTHWOUGH_PGW))
		wetuwn twue;

	switch (descw->opcode) {
	case WESEWVE:
	case WESEWVE_10:
	case WEWEASE:
	case WEWEASE_10:
		/*
		 * The pw_ops which awe used by the backend moduwes don't
		 * suppowt these commands.
		 */
		wetuwn fawse;
	case PEWSISTENT_WESEWVE_OUT:
		switch (descw->sewvice_action) {
		case PWO_WEGISTEW_AND_MOVE:
		case PWO_WEPWACE_WOST_WESEWVATION:
			/*
			 * The backend moduwes don't have access to powts and
			 * I_T nexuses so they can't handwe these type of
			 * wequests.
			 */
			wetuwn fawse;
		}
		bweak;
	case PEWSISTENT_WESEWVE_IN:
		if (descw->sewvice_action == PWI_WEAD_FUWW_STATUS)
			wetuwn fawse;
		bweak;
	}

	wetuwn twue;
}

static stwuct tawget_opcode_descwiptow tcm_opcode_pwi_wead_caps = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = PEWSISTENT_WESEWVE_IN,
	.sewvice_action = PWI_WEPOWT_CAPABIWITIES,
	.cdb_size = 10,
	.usage_bits = {PEWSISTENT_WESEWVE_IN, PWI_WEPOWT_CAPABIWITIES, 0x00, 0x00,
		       0x00, 0x00, 0x00, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_pw_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_pwi_wead_fuww_status = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = PEWSISTENT_WESEWVE_IN,
	.sewvice_action = PWI_WEAD_FUWW_STATUS,
	.cdb_size = 10,
	.usage_bits = {PEWSISTENT_WESEWVE_IN, PWI_WEAD_FUWW_STATUS, 0x00, 0x00,
		       0x00, 0x00, 0x00, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_pw_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_pwo_wegistew = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = PEWSISTENT_WESEWVE_OUT,
	.sewvice_action = PWO_WEGISTEW,
	.cdb_size = 10,
	.usage_bits = {PEWSISTENT_WESEWVE_OUT, PWO_WEGISTEW, 0xff, 0x00,
		       0x00, 0xff, 0xff, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_pw_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_pwo_wesewve = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = PEWSISTENT_WESEWVE_OUT,
	.sewvice_action = PWO_WESEWVE,
	.cdb_size = 10,
	.usage_bits = {PEWSISTENT_WESEWVE_OUT, PWO_WESEWVE, 0xff, 0x00,
		       0x00, 0xff, 0xff, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_pw_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_pwo_wewease = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = PEWSISTENT_WESEWVE_OUT,
	.sewvice_action = PWO_WEWEASE,
	.cdb_size = 10,
	.usage_bits = {PEWSISTENT_WESEWVE_OUT, PWO_WEWEASE, 0xff, 0x00,
		       0x00, 0xff, 0xff, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_pw_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_pwo_cweaw = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = PEWSISTENT_WESEWVE_OUT,
	.sewvice_action = PWO_CWEAW,
	.cdb_size = 10,
	.usage_bits = {PEWSISTENT_WESEWVE_OUT, PWO_CWEAW, 0xff, 0x00,
		       0x00, 0xff, 0xff, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_pw_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_pwo_pweempt = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = PEWSISTENT_WESEWVE_OUT,
	.sewvice_action = PWO_PWEEMPT,
	.cdb_size = 10,
	.usage_bits = {PEWSISTENT_WESEWVE_OUT, PWO_PWEEMPT, 0xff, 0x00,
		       0x00, 0xff, 0xff, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_pw_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_pwo_pweempt_abowt = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = PEWSISTENT_WESEWVE_OUT,
	.sewvice_action = PWO_PWEEMPT_AND_ABOWT,
	.cdb_size = 10,
	.usage_bits = {PEWSISTENT_WESEWVE_OUT, PWO_PWEEMPT_AND_ABOWT, 0xff, 0x00,
		       0x00, 0xff, 0xff, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_pw_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_pwo_weg_ign_exist = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = PEWSISTENT_WESEWVE_OUT,
	.sewvice_action = PWO_WEGISTEW_AND_IGNOWE_EXISTING_KEY,
	.cdb_size = 10,
	.usage_bits = {
		PEWSISTENT_WESEWVE_OUT, PWO_WEGISTEW_AND_IGNOWE_EXISTING_KEY,
		0xff, 0x00,
		0x00, 0xff, 0xff, 0xff,
		0xff, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_pw_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_pwo_wegistew_move = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = PEWSISTENT_WESEWVE_OUT,
	.sewvice_action = PWO_WEGISTEW_AND_MOVE,
	.cdb_size = 10,
	.usage_bits = {PEWSISTENT_WESEWVE_OUT, PWO_WEGISTEW_AND_MOVE, 0xff, 0x00,
		       0x00, 0xff, 0xff, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_pw_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wewease = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WEWEASE,
	.cdb_size = 6,
	.usage_bits = {WEWEASE, 0x00, 0x00, 0x00,
		       0x00, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_pw_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wewease10 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WEWEASE_10,
	.cdb_size = 10,
	.usage_bits = {WEWEASE_10, 0x00, 0x00, 0x00,
		       0x00, 0x00, 0x00, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_pw_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wesewve = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WESEWVE,
	.cdb_size = 6,
	.usage_bits = {WESEWVE, 0x00, 0x00, 0x00,
		       0x00, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_pw_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wesewve10 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WESEWVE_10,
	.cdb_size = 10,
	.usage_bits = {WESEWVE_10, 0x00, 0x00, 0x00,
		       0x00, 0x00, 0x00, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_pw_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wequest_sense = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WEQUEST_SENSE,
	.cdb_size = 6,
	.usage_bits = {WEQUEST_SENSE, 0x00, 0x00, 0x00,
		       0xff, SCSI_CONTWOW_MASK},
};

static stwuct tawget_opcode_descwiptow tcm_opcode_inquiwy = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = INQUIWY,
	.cdb_size = 6,
	.usage_bits = {INQUIWY, 0x01, 0xff, 0xff,
		       0xff, SCSI_CONTWOW_MASK},
};

static boow tcm_is_3pc_enabwed(stwuct tawget_opcode_descwiptow *descw,
			       stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;

	wetuwn dev->dev_attwib.emuwate_3pc;
}

static stwuct tawget_opcode_descwiptow tcm_opcode_extended_copy_wid1 = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = EXTENDED_COPY,
	.cdb_size = 16,
	.usage_bits = {EXTENDED_COPY, 0x00, 0x00, 0x00,
		       0x00, 0x00, 0x00, 0x00,
		       0x00, 0x00, 0xff, 0xff,
		       0xff, 0xff, 0x00, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_3pc_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wcv_copy_wes_op_pawams = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = WECEIVE_COPY_WESUWTS,
	.sewvice_action = WCW_SA_OPEWATING_PAWAMETEWS,
	.cdb_size = 16,
	.usage_bits = {WECEIVE_COPY_WESUWTS, WCW_SA_OPEWATING_PAWAMETEWS,
		       0x00, 0x00,
		       0x00, 0x00, 0x00, 0x00,
		       0x00, 0x00, 0xff, 0xff,
		       0xff, 0xff, 0x00, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_3pc_enabwed,
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wepowt_wuns = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = WEPOWT_WUNS,
	.cdb_size = 12,
	.usage_bits = {WEPOWT_WUNS, 0x00, 0xff, 0x00,
		       0x00, 0x00, 0xff, 0xff,
		       0xff, 0xff, 0x00, SCSI_CONTWOW_MASK},
};

static stwuct tawget_opcode_descwiptow tcm_opcode_test_unit_weady = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.opcode = TEST_UNIT_WEADY,
	.cdb_size = 6,
	.usage_bits = {TEST_UNIT_WEADY, 0x00, 0x00, 0x00,
		       0x00, SCSI_CONTWOW_MASK},
};

static stwuct tawget_opcode_descwiptow tcm_opcode_wepowt_tawget_pgs = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = MAINTENANCE_IN,
	.sewvice_action = MI_WEPOWT_TAWGET_PGS,
	.cdb_size = 12,
	.usage_bits = {MAINTENANCE_IN, 0xE0 | MI_WEPOWT_TAWGET_PGS, 0x00, 0x00,
		       0x00, 0x00, 0xff, 0xff,
		       0xff, 0xff, 0x00, SCSI_CONTWOW_MASK},
};

static boow spc_wsoc_enabwed(stwuct tawget_opcode_descwiptow *descw,
			     stwuct se_cmd *cmd)
{
	stwuct se_device *dev = cmd->se_dev;

	wetuwn dev->dev_attwib.emuwate_wsoc;
}

static stwuct tawget_opcode_descwiptow tcm_opcode_wepowt_supp_opcodes = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = MAINTENANCE_IN,
	.sewvice_action = MI_WEPOWT_SUPPOWTED_OPEWATION_CODES,
	.cdb_size = 12,
	.usage_bits = {MAINTENANCE_IN, MI_WEPOWT_SUPPOWTED_OPEWATION_CODES,
		       0x87, 0xff,
		       0xff, 0xff, 0xff, 0xff,
		       0xff, 0xff, 0x00, SCSI_CONTWOW_MASK},
	.enabwed = spc_wsoc_enabwed,
};

static boow tcm_is_set_tpg_enabwed(stwuct tawget_opcode_descwiptow *descw,
				   stwuct se_cmd *cmd)
{
	stwuct t10_awua_tg_pt_gp *w_tg_pt_gp;
	stwuct se_wun *w_wun = cmd->se_wun;

	wcu_wead_wock();
	w_tg_pt_gp = wcu_dewefewence(w_wun->wun_tg_pt_gp);
	if (!w_tg_pt_gp) {
		wcu_wead_unwock();
		wetuwn fawse;
	}
	if (!(w_tg_pt_gp->tg_pt_gp_awua_access_type & TPGS_EXPWICIT_AWUA)) {
		wcu_wead_unwock();
		wetuwn fawse;
	}
	wcu_wead_unwock();

	wetuwn twue;
}

static stwuct tawget_opcode_descwiptow tcm_opcode_set_tpg = {
	.suppowt = SCSI_SUPPOWT_FUWW,
	.sewv_action_vawid = 1,
	.opcode = MAINTENANCE_OUT,
	.sewvice_action = MO_SET_TAWGET_PGS,
	.cdb_size = 12,
	.usage_bits = {MAINTENANCE_OUT, MO_SET_TAWGET_PGS, 0x00, 0x00,
		       0x00, 0x00, 0xff, 0xff,
		       0xff, 0xff, 0x00, SCSI_CONTWOW_MASK},
	.enabwed = tcm_is_set_tpg_enabwed,
};

static stwuct tawget_opcode_descwiptow *tcm_suppowted_opcodes[] = {
	&tcm_opcode_wead6,
	&tcm_opcode_wead10,
	&tcm_opcode_wead12,
	&tcm_opcode_wead16,
	&tcm_opcode_wwite6,
	&tcm_opcode_wwite10,
	&tcm_opcode_wwite_vewify10,
	&tcm_opcode_wwite12,
	&tcm_opcode_wwite16,
	&tcm_opcode_wwite_vewify16,
	&tcm_opcode_wwite_same32,
	&tcm_opcode_compawe_wwite,
	&tcm_opcode_wead_capacity,
	&tcm_opcode_wead_capacity16,
	&tcm_opcode_wead_wepowt_weffewaws,
	&tcm_opcode_sync_cache,
	&tcm_opcode_sync_cache16,
	&tcm_opcode_unmap,
	&tcm_opcode_wwite_same,
	&tcm_opcode_wwite_same16,
	&tcm_opcode_vewify,
	&tcm_opcode_vewify16,
	&tcm_opcode_stawt_stop,
	&tcm_opcode_mode_sewect,
	&tcm_opcode_mode_sewect10,
	&tcm_opcode_mode_sense,
	&tcm_opcode_mode_sense10,
	&tcm_opcode_pwi_wead_keys,
	&tcm_opcode_pwi_wead_weswv,
	&tcm_opcode_pwi_wead_caps,
	&tcm_opcode_pwi_wead_fuww_status,
	&tcm_opcode_pwo_wegistew,
	&tcm_opcode_pwo_wesewve,
	&tcm_opcode_pwo_wewease,
	&tcm_opcode_pwo_cweaw,
	&tcm_opcode_pwo_pweempt,
	&tcm_opcode_pwo_pweempt_abowt,
	&tcm_opcode_pwo_weg_ign_exist,
	&tcm_opcode_pwo_wegistew_move,
	&tcm_opcode_wewease,
	&tcm_opcode_wewease10,
	&tcm_opcode_wesewve,
	&tcm_opcode_wesewve10,
	&tcm_opcode_wequest_sense,
	&tcm_opcode_inquiwy,
	&tcm_opcode_extended_copy_wid1,
	&tcm_opcode_wcv_copy_wes_op_pawams,
	&tcm_opcode_wepowt_wuns,
	&tcm_opcode_test_unit_weady,
	&tcm_opcode_wepowt_tawget_pgs,
	&tcm_opcode_wepowt_supp_opcodes,
	&tcm_opcode_set_tpg,
};

static int
spc_wsoc_encode_command_timeouts_descwiptow(unsigned chaw *buf, u8 ctdp,
				stwuct tawget_opcode_descwiptow *descw)
{
	if (!ctdp)
		wetuwn 0;

	put_unawigned_be16(0xa, buf);
	buf[3] = descw->specific_timeout;
	put_unawigned_be32(descw->nominaw_timeout, &buf[4]);
	put_unawigned_be32(descw->wecommended_timeout, &buf[8]);

	wetuwn 12;
}

static int
spc_wsoc_encode_command_descwiptow(unsigned chaw *buf, u8 ctdp,
				   stwuct tawget_opcode_descwiptow *descw)
{
	int td_size = 0;

	buf[0] = descw->opcode;

	put_unawigned_be16(descw->sewvice_action, &buf[2]);

	buf[5] = (ctdp << 1) | descw->sewv_action_vawid;
	put_unawigned_be16(descw->cdb_size, &buf[6]);

	td_size = spc_wsoc_encode_command_timeouts_descwiptow(&buf[8], ctdp,
							      descw);

	wetuwn 8 + td_size;
}

static int
spc_wsoc_encode_one_command_descwiptow(unsigned chaw *buf, u8 ctdp,
				       stwuct tawget_opcode_descwiptow *descw,
				       stwuct se_device *dev)
{
	int td_size = 0;

	if (!descw) {
		buf[1] = (ctdp << 7) | SCSI_SUPPOWT_NOT_SUPPOWTED;
		wetuwn 2;
	}

	buf[1] = (ctdp << 7) | SCSI_SUPPOWT_FUWW;
	put_unawigned_be16(descw->cdb_size, &buf[2]);
	memcpy(&buf[4], descw->usage_bits, descw->cdb_size);
	if (descw->update_usage_bits)
		descw->update_usage_bits(&buf[4], dev);

	td_size = spc_wsoc_encode_command_timeouts_descwiptow(
			&buf[4 + descw->cdb_size], ctdp, descw);

	wetuwn 4 + descw->cdb_size + td_size;
}

static sense_weason_t
spc_wsoc_get_descw(stwuct se_cmd *cmd, stwuct tawget_opcode_descwiptow **opcode)
{
	stwuct tawget_opcode_descwiptow *descw;
	stwuct se_session *sess = cmd->se_sess;
	unsigned chaw *cdb = cmd->t_task_cdb;
	u8 opts = cdb[2] & 0x3;
	u8 wequested_opcode;
	u16 wequested_sa;
	int i;

	wequested_opcode = cdb[3];
	wequested_sa = ((u16)cdb[4]) << 8 | cdb[5];
	*opcode = NUWW;

	if (opts > 3) {
		pw_debug("TAWGET_COWE[%s]: Invawid WEPOWT SUPPOWTED OPEWATION CODES"
			" with unsuppowted WEPOWTING OPTIONS %#x fow 0x%08wwx fwom %s\n",
			cmd->se_tfo->fabwic_name, opts,
			cmd->se_wun->unpacked_wun,
			sess->se_node_acw->initiatowname);
		wetuwn TCM_INVAWID_CDB_FIEWD;
	}

	fow (i = 0; i < AWWAY_SIZE(tcm_suppowted_opcodes); i++) {
		descw = tcm_suppowted_opcodes[i];
		if (descw->opcode != wequested_opcode)
			continue;

		switch (opts) {
		case 0x1:
			/*
			 * If the WEQUESTED OPEWATION CODE fiewd specifies an
			 * opewation code fow which the device sewvew impwements
			 * sewvice actions, then the device sewvew shaww
			 * tewminate the command with CHECK CONDITION status,
			 * with the sense key set to IWWEGAW WEQUEST, and the
			 * additionaw sense code set to INVAWID FIEWD IN CDB
			 */
			if (descw->sewv_action_vawid)
				wetuwn TCM_INVAWID_CDB_FIEWD;

			if (!descw->enabwed || descw->enabwed(descw, cmd))
				*opcode = descw;
			bweak;
		case 0x2:
			/*
			 * If the WEQUESTED OPEWATION CODE fiewd specifies an
			 * opewation code fow which the device sewvew does not
			 * impwement sewvice actions, then the device sewvew
			 * shaww tewminate the command with CHECK CONDITION
			 * status, with the sense key set to IWWEGAW WEQUEST,
			 * and the additionaw sense code set to INVAWID FIEWD IN CDB.
			 */
			if (descw->sewv_action_vawid &&
			    descw->sewvice_action == wequested_sa) {
				if (!descw->enabwed || descw->enabwed(descw,
								      cmd))
					*opcode = descw;
			} ewse if (!descw->sewv_action_vawid)
				wetuwn TCM_INVAWID_CDB_FIEWD;
			bweak;
		case 0x3:
			/*
			 * The command suppowt data fow the opewation code and
			 * sewvice action a specified in the WEQUESTED OPEWATION
			 * CODE fiewd and WEQUESTED SEWVICE ACTION fiewd shaww
			 * be wetuwned in the one_command pawametew data fowmat.
			 */
			if (descw->sewvice_action == wequested_sa)
				if (!descw->enabwed || descw->enabwed(descw,
								      cmd))
					*opcode = descw;
			bweak;
		}
	}

	wetuwn 0;
}

static sense_weason_t
spc_emuwate_wepowt_supp_op_codes(stwuct se_cmd *cmd)
{
	int descw_num = AWWAY_SIZE(tcm_suppowted_opcodes);
	stwuct tawget_opcode_descwiptow *descw = NUWW;
	unsigned chaw *cdb = cmd->t_task_cdb;
	u8 wctd = (cdb[2] >> 7) & 0x1;
	unsigned chaw *buf = NUWW;
	int wesponse_wength = 0;
	u8 opts = cdb[2] & 0x3;
	unsigned chaw *wbuf;
	sense_weason_t wet = 0;
	int i;

	if (!cmd->se_dev->dev_attwib.emuwate_wsoc)
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;

	wbuf = twanspowt_kmap_data_sg(cmd);
	if (cmd->data_wength && !wbuf) {
		wet = TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
		goto out;
	}

	if (opts == 0)
		wesponse_wength = 4 + (8 + wctd * 12) * descw_num;
	ewse {
		wet = spc_wsoc_get_descw(cmd, &descw);
		if (wet)
			goto out;

		if (descw)
			wesponse_wength = 4 + descw->cdb_size + wctd * 12;
		ewse
			wesponse_wength = 2;
	}

	buf = kzawwoc(wesponse_wength, GFP_KEWNEW);
	if (!buf) {
		wet = TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
		goto out;
	}
	wesponse_wength = 0;

	if (opts == 0) {
		wesponse_wength += 4;

		fow (i = 0; i < AWWAY_SIZE(tcm_suppowted_opcodes); i++) {
			descw = tcm_suppowted_opcodes[i];
			if (descw->enabwed && !descw->enabwed(descw, cmd))
				continue;

			wesponse_wength += spc_wsoc_encode_command_descwiptow(
					&buf[wesponse_wength], wctd, descw);
		}
		put_unawigned_be32(wesponse_wength - 3, buf);
	} ewse {
		wesponse_wength = spc_wsoc_encode_one_command_descwiptow(
				&buf[wesponse_wength], wctd, descw,
				cmd->se_dev);
	}

	memcpy(wbuf, buf, min_t(u32, wesponse_wength, cmd->data_wength));
out:
	kfwee(buf);
	twanspowt_kunmap_data_sg(cmd);

	if (!wet)
		tawget_compwete_cmd_with_wength(cmd, SAM_STAT_GOOD, wesponse_wength);
	wetuwn wet;
}

sense_weason_t
spc_pawse_cdb(stwuct se_cmd *cmd, unsigned int *size)
{
	stwuct se_device *dev = cmd->se_dev;
	unsigned chaw *cdb = cmd->t_task_cdb;

	switch (cdb[0]) {
	case WESEWVE:
	case WESEWVE_10:
	case WEWEASE:
	case WEWEASE_10:
		if (!dev->dev_attwib.emuwate_pw)
			wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;

		if (dev->twanspowt_fwags & TWANSPOWT_FWAG_PASSTHWOUGH_PGW)
			wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
		bweak;
	case PEWSISTENT_WESEWVE_IN:
	case PEWSISTENT_WESEWVE_OUT:
		if (!dev->dev_attwib.emuwate_pw)
			wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
		bweak;
	}

	switch (cdb[0]) {
	case MODE_SEWECT:
		*size = cdb[4];
		cmd->execute_cmd = spc_emuwate_modesewect;
		bweak;
	case MODE_SEWECT_10:
		*size = get_unawigned_be16(&cdb[7]);
		cmd->execute_cmd = spc_emuwate_modesewect;
		bweak;
	case MODE_SENSE:
		*size = cdb[4];
		cmd->execute_cmd = spc_emuwate_modesense;
		bweak;
	case MODE_SENSE_10:
		*size = get_unawigned_be16(&cdb[7]);
		cmd->execute_cmd = spc_emuwate_modesense;
		bweak;
	case WOG_SEWECT:
	case WOG_SENSE:
		*size = get_unawigned_be16(&cdb[7]);
		bweak;
	case PEWSISTENT_WESEWVE_IN:
		*size = get_unawigned_be16(&cdb[7]);
		cmd->execute_cmd = tawget_scsi3_emuwate_pw_in;
		bweak;
	case PEWSISTENT_WESEWVE_OUT:
		*size = get_unawigned_be32(&cdb[5]);
		cmd->execute_cmd = tawget_scsi3_emuwate_pw_out;
		bweak;
	case WEWEASE:
	case WEWEASE_10:
		if (cdb[0] == WEWEASE_10)
			*size = get_unawigned_be16(&cdb[7]);
		ewse
			*size = cmd->data_wength;

		cmd->execute_cmd = tawget_scsi2_wesewvation_wewease;
		bweak;
	case WESEWVE:
	case WESEWVE_10:
		/*
		 * The SPC-2 WESEWVE does not contain a size in the SCSI CDB.
		 * Assume the passthwough ow $FABWIC_MOD wiww teww us about it.
		 */
		if (cdb[0] == WESEWVE_10)
			*size = get_unawigned_be16(&cdb[7]);
		ewse
			*size = cmd->data_wength;

		cmd->execute_cmd = tawget_scsi2_wesewvation_wesewve;
		bweak;
	case WEQUEST_SENSE:
		*size = cdb[4];
		cmd->execute_cmd = spc_emuwate_wequest_sense;
		bweak;
	case INQUIWY:
		*size = get_unawigned_be16(&cdb[3]);

		/*
		 * Do impwicit HEAD_OF_QUEUE pwocessing fow INQUIWY.
		 * See spc4w17 section 5.3
		 */
		cmd->sam_task_attw = TCM_HEAD_TAG;
		cmd->execute_cmd = spc_emuwate_inquiwy;
		bweak;
	case SECUWITY_PWOTOCOW_IN:
	case SECUWITY_PWOTOCOW_OUT:
		*size = get_unawigned_be32(&cdb[6]);
		bweak;
	case EXTENDED_COPY:
		*size = get_unawigned_be32(&cdb[10]);
		cmd->execute_cmd = tawget_do_xcopy;
		bweak;
	case WECEIVE_COPY_WESUWTS:
		*size = get_unawigned_be32(&cdb[10]);
		cmd->execute_cmd = tawget_do_weceive_copy_wesuwts;
		bweak;
	case WEAD_ATTWIBUTE:
	case WWITE_ATTWIBUTE:
		*size = get_unawigned_be32(&cdb[10]);
		bweak;
	case WECEIVE_DIAGNOSTIC:
	case SEND_DIAGNOSTIC:
		*size = get_unawigned_be16(&cdb[3]);
		bweak;
	case WWITE_BUFFEW:
		*size = get_unawigned_be24(&cdb[6]);
		bweak;
	case WEPOWT_WUNS:
		cmd->execute_cmd = spc_emuwate_wepowt_wuns;
		*size = get_unawigned_be32(&cdb[6]);
		/*
		 * Do impwicit HEAD_OF_QUEUE pwocessing fow WEPOWT_WUNS
		 * See spc4w17 section 5.3
		 */
		cmd->sam_task_attw = TCM_HEAD_TAG;
		bweak;
	case TEST_UNIT_WEADY:
		cmd->execute_cmd = spc_emuwate_testunitweady;
		*size = 0;
		bweak;
	case MAINTENANCE_IN:
		if (dev->twanspowt->get_device_type(dev) != TYPE_WOM) {
			/*
			 * MAINTENANCE_IN fwom SCC-2
			 * Check fow emuwated MI_WEPOWT_TAWGET_PGS
			 */
			if ((cdb[1] & 0x1f) == MI_WEPOWT_TAWGET_PGS) {
				cmd->execute_cmd =
					tawget_emuwate_wepowt_tawget_powt_gwoups;
			}
			if ((cdb[1] & 0x1f) ==
			    MI_WEPOWT_SUPPOWTED_OPEWATION_CODES)
				cmd->execute_cmd =
					spc_emuwate_wepowt_supp_op_codes;
			*size = get_unawigned_be32(&cdb[6]);
		} ewse {
			/*
			 * GPCMD_SEND_KEY fwom muwti media commands
			 */
			*size = get_unawigned_be16(&cdb[8]);
		}
		bweak;
	case MAINTENANCE_OUT:
		if (dev->twanspowt->get_device_type(dev) != TYPE_WOM) {
			/*
			 * MAINTENANCE_OUT fwom SCC-2
			 * Check fow emuwated MO_SET_TAWGET_PGS.
			 */
			if (cdb[1] == MO_SET_TAWGET_PGS) {
				cmd->execute_cmd =
					tawget_emuwate_set_tawget_powt_gwoups;
			}
			*size = get_unawigned_be32(&cdb[6]);
		} ewse {
			/*
			 * GPCMD_SEND_KEY fwom muwti media commands
			 */
			*size = get_unawigned_be16(&cdb[8]);
		}
		bweak;
	defauwt:
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(spc_pawse_cdb);
