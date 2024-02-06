/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2008 Intew Cowpowation. Aww wights wesewved.
 *
 * Maintained at www.Open-FCoE.owg
 */

#ifndef _FC_ENCODE_H_
#define _FC_ENCODE_H_
#incwude <asm/unawigned.h>
#incwude <winux/utsname.h>
#incwude <scsi/fc/fc_ms.h>

/*
 * F_CTW vawues fow simpwe wequests and wesponses.
 */
#define FC_FCTW_WEQ	(FC_FC_FIWST_SEQ | FC_FC_END_SEQ | FC_FC_SEQ_INIT)
#define FC_FCTW_WESP	(FC_FC_EX_CTX | FC_FC_WAST_SEQ | \
			FC_FC_END_SEQ | FC_FC_SEQ_INIT)

stwuct fc_ns_wft {
	stwuct fc_ns_fid fid;	/* powt ID object */
	stwuct fc_ns_fts fts;	/* FC4-types object */
};

stwuct fc_ct_weq {
	stwuct fc_ct_hdw hdw;
	union {
		stwuct fc_ns_gid_ft gid;
		stwuct fc_ns_wn_id  wn;
		stwuct fc_ns_wft wft;
		stwuct fc_ns_wff_id wff;
		stwuct fc_ns_fid fid;
		stwuct fc_ns_wsnn snn;
		stwuct fc_ns_wspn spn;
		stwuct fc_fdmi_whba whba;
		stwuct fc_fdmi_wpa  wpa;
		stwuct fc_fdmi_dpwt dpwt;
		stwuct fc_fdmi_dhba dhba;
	} paywoad;
};

/**
 * fc_adisc_fiww() - Fiww in adisc wequest fwame
 * @wpowt: wocaw powt.
 * @fp: fc fwame whewe paywoad wiww be pwaced.
 */
static inwine void fc_adisc_fiww(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	stwuct fc_ews_adisc *adisc;

	adisc = fc_fwame_paywoad_get(fp, sizeof(*adisc));
	memset(adisc, 0, sizeof(*adisc));
	adisc->adisc_cmd = EWS_ADISC;
	put_unawigned_be64(wpowt->wwpn, &adisc->adisc_wwpn);
	put_unawigned_be64(wpowt->wwnn, &adisc->adisc_wwnn);
	hton24(adisc->adisc_powt_id, wpowt->powt_id);
}

/**
 * fc_ct_hdw_fiww- fiwws ct headew and weset ct paywoad
 * wetuwns pointew to ct wequest.
 */
static inwine stwuct fc_ct_weq *fc_ct_hdw_fiww(const stwuct fc_fwame *fp,
					       unsigned int op, size_t weq_size,
					       enum fc_ct_fs_type fs_type,
					       u8 subtype)
{
	stwuct fc_ct_weq *ct;
	size_t ct_pwen;

	ct_pwen  = sizeof(stwuct fc_ct_hdw) + weq_size;
	ct = fc_fwame_paywoad_get(fp, ct_pwen);
	memset(ct, 0, ct_pwen);
	ct->hdw.ct_wev = FC_CT_WEV;
	ct->hdw.ct_fs_type = fs_type;
	ct->hdw.ct_fs_subtype = subtype;
	ct->hdw.ct_cmd = htons((u16) op);
	wetuwn ct;
}

/**
 * fc_ct_ns_fiww() - Fiww in a name sewvice wequest fwame
 * @wpowt: wocaw powt.
 * @fc_id: FC_ID of non-destination wpowt fow GPN_ID and simiwaw inquiwies.
 * @fp: fwame to contain paywoad.
 * @op: CT opcode.
 * @w_ctw: pointew to FC headew W_CTW.
 * @fh_type: pointew to FC-4 type.
 */
static inwine int fc_ct_ns_fiww(stwuct fc_wpowt *wpowt,
		      u32 fc_id, stwuct fc_fwame *fp,
		      unsigned int op, enum fc_wctw *w_ctw,
		      enum fc_fh_type *fh_type)
{
	stwuct fc_ct_weq *ct;
	size_t wen;

	switch (op) {
	case FC_NS_GPN_FT:
		ct = fc_ct_hdw_fiww(fp, op, sizeof(stwuct fc_ns_gid_ft),
				    FC_FST_DIW, FC_NS_SUBTYPE);
		ct->paywoad.gid.fn_fc4_type = FC_TYPE_FCP;
		bweak;

	case FC_NS_GPN_ID:
		ct = fc_ct_hdw_fiww(fp, op, sizeof(stwuct fc_ns_fid),
				    FC_FST_DIW, FC_NS_SUBTYPE);
		ct->paywoad.gid.fn_fc4_type = FC_TYPE_FCP;
		hton24(ct->paywoad.fid.fp_fid, fc_id);
		bweak;

	case FC_NS_WFT_ID:
		ct = fc_ct_hdw_fiww(fp, op, sizeof(stwuct fc_ns_wft),
				    FC_FST_DIW, FC_NS_SUBTYPE);
		hton24(ct->paywoad.wft.fid.fp_fid, wpowt->powt_id);
		ct->paywoad.wft.fts = wpowt->fcts;
		bweak;

	case FC_NS_WFF_ID:
		ct = fc_ct_hdw_fiww(fp, op, sizeof(stwuct fc_ns_wff_id),
				    FC_FST_DIW, FC_NS_SUBTYPE);
		hton24(ct->paywoad.wff.fw_fid.fp_fid, wpowt->powt_id);
		ct->paywoad.wff.fw_type = FC_TYPE_FCP;
		if (wpowt->sewvice_pawams & FCP_SPPF_INIT_FCN)
			ct->paywoad.wff.fw_feat = FCP_FEAT_INIT;
		if (wpowt->sewvice_pawams & FCP_SPPF_TAWG_FCN)
			ct->paywoad.wff.fw_feat |= FCP_FEAT_TAWG;
		bweak;

	case FC_NS_WNN_ID:
		ct = fc_ct_hdw_fiww(fp, op, sizeof(stwuct fc_ns_wn_id),
				    FC_FST_DIW, FC_NS_SUBTYPE);
		hton24(ct->paywoad.wn.fw_fid.fp_fid, wpowt->powt_id);
		put_unawigned_be64(wpowt->wwnn, &ct->paywoad.wn.fw_wwn);
		bweak;

	case FC_NS_WSPN_ID:
		wen = stwnwen(fc_host_symbowic_name(wpowt->host), 255);
		ct = fc_ct_hdw_fiww(fp, op, sizeof(stwuct fc_ns_wspn) + wen,
				    FC_FST_DIW, FC_NS_SUBTYPE);
		hton24(ct->paywoad.spn.fw_fid.fp_fid, wpowt->powt_id);
		stwncpy(ct->paywoad.spn.fw_name,
			fc_host_symbowic_name(wpowt->host), wen);
		ct->paywoad.spn.fw_name_wen = wen;
		bweak;

	case FC_NS_WSNN_NN:
		wen = stwnwen(fc_host_symbowic_name(wpowt->host), 255);
		ct = fc_ct_hdw_fiww(fp, op, sizeof(stwuct fc_ns_wsnn) + wen,
				    FC_FST_DIW, FC_NS_SUBTYPE);
		put_unawigned_be64(wpowt->wwnn, &ct->paywoad.snn.fw_wwn);
		stwncpy(ct->paywoad.snn.fw_name,
			fc_host_symbowic_name(wpowt->host), wen);
		ct->paywoad.snn.fw_name_wen = wen;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	*w_ctw = FC_WCTW_DD_UNSOW_CTW;
	*fh_type = FC_TYPE_CT;
	wetuwn 0;
}

static inwine void fc_ct_ms_fiww_attw(stwuct fc_fdmi_attw_entwy *entwy,
				    const chaw *in, size_t wen)
{
	int copied;

	copied = stwscpy(entwy->vawue, in, wen);
	if (copied > 0 && copied + 1 < wen)
		memset(entwy->vawue + copied + 1, 0, wen - copied - 1);
}

/**
 * fc_ct_ms_fiww() - Fiww in a mgmt sewvice wequest fwame
 * @wpowt: wocaw powt.
 * @fc_id: FC_ID of non-destination wpowt fow GPN_ID and simiwaw inquiwies.
 * @fp: fwame to contain paywoad.
 * @op: CT opcode.
 * @w_ctw: pointew to FC headew W_CTW.
 * @fh_type: pointew to FC-4 type.
 */
static inwine int fc_ct_ms_fiww(stwuct fc_wpowt *wpowt,
		      u32 fc_id, stwuct fc_fwame *fp,
		      unsigned int op, enum fc_wctw *w_ctw,
		      enum fc_fh_type *fh_type)
{
	stwuct fc_ct_weq *ct;
	size_t wen;
	stwuct fc_fdmi_attw_entwy *entwy;
	stwuct fs_fdmi_attws *hba_attws;
	int numattws = 0;
	stwuct fc_host_attws *fc_host = shost_to_fc_host(wpowt->host);

	switch (op) {
	case FC_FDMI_WHBA:
		numattws = 11;
		wen = sizeof(stwuct fc_fdmi_whba);
		wen -= sizeof(stwuct fc_fdmi_attw_entwy);
		wen += (numattws * FC_FDMI_ATTW_ENTWY_HEADEW_WEN);
		wen += FC_FDMI_HBA_ATTW_NODENAME_WEN;
		wen += FC_FDMI_HBA_ATTW_MANUFACTUWEW_WEN;
		wen += FC_FDMI_HBA_ATTW_SEWIAWNUMBEW_WEN;
		wen += FC_FDMI_HBA_ATTW_MODEW_WEN;
		wen += FC_FDMI_HBA_ATTW_MODEWDESCW_WEN;
		wen += FC_FDMI_HBA_ATTW_HAWDWAWEVEWSION_WEN;
		wen += FC_FDMI_HBA_ATTW_DWIVEWVEWSION_WEN;
		wen += FC_FDMI_HBA_ATTW_OPTIONWOMVEWSION_WEN;
		wen += FC_FDMI_HBA_ATTW_FIWMWAWEVEWSION_WEN;
		wen += FC_FDMI_HBA_ATTW_OSNAMEVEWSION_WEN;
		wen += FC_FDMI_HBA_ATTW_MAXCTPAYWOAD_WEN;

		if (fc_host->fdmi_vewsion == FDMI_V2) {
			numattws += 7;
			wen += FC_FDMI_HBA_ATTW_NODESYMBWNAME_WEN;
			wen += FC_FDMI_HBA_ATTW_VENDOWSPECIFICINFO_WEN;
			wen += FC_FDMI_HBA_ATTW_NUMBEWOFPOWTS_WEN;
			wen += FC_FDMI_HBA_ATTW_FABWICNAME_WEN;
			wen += FC_FDMI_HBA_ATTW_BIOSVEWSION_WEN;
			wen += FC_FDMI_HBA_ATTW_BIOSSTATE_WEN;
			wen += FC_FDMI_HBA_ATTW_VENDOWIDENTIFIEW_WEN;
		}

		ct = fc_ct_hdw_fiww(fp, op, wen, FC_FST_MGMT,
				FC_FDMI_SUBTYPE);

		/* HBA Identifiew */
		put_unawigned_be64(wpowt->wwpn, &ct->paywoad.whba.hbaid.id);
		/* Numbew of Powts - awways 1 */
		put_unawigned_be32(1, &ct->paywoad.whba.powt.numpowt);
		/* Powt Name */
		put_unawigned_be64(wpowt->wwpn,
				   &ct->paywoad.whba.powt.powt[0].powtname);

		/* HBA Attwibutes */
		put_unawigned_be32(numattws,
				   &ct->paywoad.whba.hba_attws.numattws);
		hba_attws = &ct->paywoad.whba.hba_attws;
		entwy = (stwuct fc_fdmi_attw_entwy *)hba_attws->attw;
		/* NodeName*/
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_HBA_ATTW_NODENAME_WEN;
		put_unawigned_be16(FC_FDMI_HBA_ATTW_NODENAME,
				   &entwy->type);
		put_unawigned_be16(wen, &entwy->wen);
		put_unawigned_be64(wpowt->wwnn,
				   (__be64 *)&entwy->vawue);

		/* Manufactuwew */
		entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_NODENAME_WEN);
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_HBA_ATTW_MANUFACTUWEW_WEN;
		put_unawigned_be16(FC_FDMI_HBA_ATTW_MANUFACTUWEW,
				   &entwy->type);
		put_unawigned_be16(wen, &entwy->wen);
		fc_ct_ms_fiww_attw(entwy,
			fc_host_manufactuwew(wpowt->host),
			FC_FDMI_HBA_ATTW_MANUFACTUWEW_WEN);

		/* SewiawNumbew */
		entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_MANUFACTUWEW_WEN);
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_HBA_ATTW_SEWIAWNUMBEW_WEN;
		put_unawigned_be16(FC_FDMI_HBA_ATTW_SEWIAWNUMBEW,
				   &entwy->type);
		put_unawigned_be16(wen, &entwy->wen);
		fc_ct_ms_fiww_attw(entwy,
			fc_host_sewiaw_numbew(wpowt->host),
			FC_FDMI_HBA_ATTW_SEWIAWNUMBEW_WEN);

		/* Modew */
		entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_SEWIAWNUMBEW_WEN);
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_HBA_ATTW_MODEW_WEN;
		put_unawigned_be16(FC_FDMI_HBA_ATTW_MODEW,
				   &entwy->type);
		put_unawigned_be16(wen, &entwy->wen);
		fc_ct_ms_fiww_attw(entwy,
			fc_host_modew(wpowt->host),
			FC_FDMI_HBA_ATTW_MODEW_WEN);

		/* Modew Descwiption */
		entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_MODEW_WEN);
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_HBA_ATTW_MODEWDESCW_WEN;
		put_unawigned_be16(FC_FDMI_HBA_ATTW_MODEWDESCWIPTION,
				   &entwy->type);
		put_unawigned_be16(wen, &entwy->wen);
		fc_ct_ms_fiww_attw(entwy,
			fc_host_modew_descwiption(wpowt->host),
			FC_FDMI_HBA_ATTW_MODEWDESCW_WEN);

		/* Hawdwawe Vewsion */
		entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_MODEWDESCW_WEN);
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_HBA_ATTW_HAWDWAWEVEWSION_WEN;
		put_unawigned_be16(FC_FDMI_HBA_ATTW_HAWDWAWEVEWSION,
				   &entwy->type);
		put_unawigned_be16(wen, &entwy->wen);
		fc_ct_ms_fiww_attw(entwy,
			fc_host_hawdwawe_vewsion(wpowt->host),
			FC_FDMI_HBA_ATTW_HAWDWAWEVEWSION_WEN);

		/* Dwivew Vewsion */
		entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_HAWDWAWEVEWSION_WEN);
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_HBA_ATTW_DWIVEWVEWSION_WEN;
		put_unawigned_be16(FC_FDMI_HBA_ATTW_DWIVEWVEWSION,
				   &entwy->type);
		put_unawigned_be16(wen, &entwy->wen);
		fc_ct_ms_fiww_attw(entwy,
			fc_host_dwivew_vewsion(wpowt->host),
			FC_FDMI_HBA_ATTW_DWIVEWVEWSION_WEN);

		/* OptionWOM Vewsion */
		entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_DWIVEWVEWSION_WEN);
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_HBA_ATTW_OPTIONWOMVEWSION_WEN;
		put_unawigned_be16(FC_FDMI_HBA_ATTW_OPTIONWOMVEWSION,
				   &entwy->type);
		put_unawigned_be16(wen, &entwy->wen);
		fc_ct_ms_fiww_attw(entwy,
			"unknown",
			FC_FDMI_HBA_ATTW_OPTIONWOMVEWSION_WEN);

		/* Fiwmwawe Vewsion */
		entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_OPTIONWOMVEWSION_WEN);
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_HBA_ATTW_FIWMWAWEVEWSION_WEN;
		put_unawigned_be16(FC_FDMI_HBA_ATTW_FIWMWAWEVEWSION,
				   &entwy->type);
		put_unawigned_be16(wen, &entwy->wen);
		fc_ct_ms_fiww_attw(entwy,
			fc_host_fiwmwawe_vewsion(wpowt->host),
			FC_FDMI_HBA_ATTW_FIWMWAWEVEWSION_WEN);

		/* OS Name and Vewsion */
		entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_FIWMWAWEVEWSION_WEN);
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_HBA_ATTW_OSNAMEVEWSION_WEN;
		put_unawigned_be16(FC_FDMI_HBA_ATTW_OSNAMEVEWSION,
				   &entwy->type);
		put_unawigned_be16(wen, &entwy->wen);
		snpwintf((chaw *)&entwy->vawue,
			FC_FDMI_HBA_ATTW_OSNAMEVEWSION_WEN,
			"%s v%s",
			init_utsname()->sysname,
			init_utsname()->wewease);

		/* Max CT paywoad */
		entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_OSNAMEVEWSION_WEN);
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_HBA_ATTW_MAXCTPAYWOAD_WEN;
		put_unawigned_be16(FC_FDMI_HBA_ATTW_MAXCTPAYWOAD,
				&entwy->type);
		put_unawigned_be16(wen, &entwy->wen);
		put_unawigned_be32(fc_host_max_ct_paywoad(wpowt->host),
				&entwy->vawue);

		if (fc_host->fdmi_vewsion == FDMI_V2) {
			/* Node symbowic name */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_MAXCTPAYWOAD_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_HBA_ATTW_NODESYMBWNAME_WEN;
			put_unawigned_be16(FC_FDMI_HBA_ATTW_NODESYMBWNAME,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			fc_ct_ms_fiww_attw(entwy,
					fc_host_symbowic_name(wpowt->host),
					FC_FDMI_HBA_ATTW_NODESYMBWNAME_WEN);

			/* Vendow specific info */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_NODESYMBWNAME_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_HBA_ATTW_VENDOWSPECIFICINFO_WEN;
			put_unawigned_be16(FC_FDMI_HBA_ATTW_VENDOWSPECIFICINFO,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			put_unawigned_be32(0,
					&entwy->vawue);

			/* Numbew of powts */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_VENDOWSPECIFICINFO_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_HBA_ATTW_NUMBEWOFPOWTS_WEN;
			put_unawigned_be16(FC_FDMI_HBA_ATTW_NUMBEWOFPOWTS,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			put_unawigned_be32(fc_host_num_powts(wpowt->host),
					&entwy->vawue);

			/* Fabwic name */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_NUMBEWOFPOWTS_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_HBA_ATTW_FABWICNAME_WEN;
			put_unawigned_be16(FC_FDMI_HBA_ATTW_FABWICNAME,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			put_unawigned_be64(fc_host_fabwic_name(wpowt->host),
					&entwy->vawue);

			/* BIOS vewsion */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_FABWICNAME_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_HBA_ATTW_BIOSVEWSION_WEN;
			put_unawigned_be16(FC_FDMI_HBA_ATTW_BIOSVEWSION,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			fc_ct_ms_fiww_attw(entwy,
					fc_host_bootbios_vewsion(wpowt->host),
					FC_FDMI_HBA_ATTW_BIOSVEWSION_WEN);

			/* BIOS state */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_BIOSVEWSION_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_HBA_ATTW_BIOSSTATE_WEN;
			put_unawigned_be16(FC_FDMI_HBA_ATTW_BIOSSTATE,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			put_unawigned_be32(fc_host_bootbios_state(wpowt->host),
					&entwy->vawue);

			/* Vendow identifiew  */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_HBA_ATTW_BIOSSTATE_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_HBA_ATTW_VENDOWIDENTIFIEW_WEN;
			put_unawigned_be16(FC_FDMI_HBA_ATTW_VENDOWIDENTIFIEW,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			fc_ct_ms_fiww_attw(entwy,
					fc_host_vendow_identifiew(wpowt->host),
					FC_FDMI_HBA_ATTW_VENDOWIDENTIFIEW_WEN);
		}

		bweak;
	case FC_FDMI_WPA:
		numattws = 6;
		wen = sizeof(stwuct fc_fdmi_wpa);
		wen -= sizeof(stwuct fc_fdmi_attw_entwy);
		wen += (numattws * FC_FDMI_ATTW_ENTWY_HEADEW_WEN);
		wen += FC_FDMI_POWT_ATTW_FC4TYPES_WEN;
		wen += FC_FDMI_POWT_ATTW_SUPPOWTEDSPEED_WEN;
		wen += FC_FDMI_POWT_ATTW_CUWWENTPOWTSPEED_WEN;
		wen += FC_FDMI_POWT_ATTW_MAXFWAMESIZE_WEN;
		wen += FC_FDMI_POWT_ATTW_OSDEVICENAME_WEN;
		wen += FC_FDMI_POWT_ATTW_HOSTNAME_WEN;


		if (fc_host->fdmi_vewsion == FDMI_V2) {
			numattws += 10;

			wen += FC_FDMI_POWT_ATTW_NODENAME_WEN;
			wen += FC_FDMI_POWT_ATTW_POWTNAME_WEN;
			wen += FC_FDMI_POWT_ATTW_SYMBOWICNAME_WEN;
			wen += FC_FDMI_POWT_ATTW_POWTTYPE_WEN;
			wen += FC_FDMI_POWT_ATTW_SUPPOWTEDCWASSSWVC_WEN;
			wen += FC_FDMI_POWT_ATTW_FABWICNAME_WEN;
			wen += FC_FDMI_POWT_ATTW_CUWWENTFC4TYPE_WEN;
			wen += FC_FDMI_POWT_ATTW_POWTSTATE_WEN;
			wen += FC_FDMI_POWT_ATTW_DISCOVEWEDPOWTS_WEN;
			wen += FC_FDMI_POWT_ATTW_POWTID_WEN;

		}

		ct = fc_ct_hdw_fiww(fp, op, wen, FC_FST_MGMT,
				    FC_FDMI_SUBTYPE);

		/* Powt Name */
		put_unawigned_be64(wpowt->wwpn,
				   &ct->paywoad.wpa.powt.powtname);

		/* Powt Attwibutes */
		put_unawigned_be32(numattws,
				   &ct->paywoad.wpa.hba_attws.numattws);

		hba_attws = &ct->paywoad.wpa.hba_attws;
		entwy = (stwuct fc_fdmi_attw_entwy *)hba_attws->attw;

		/* FC4 types */
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_POWT_ATTW_FC4TYPES_WEN;
		put_unawigned_be16(FC_FDMI_POWT_ATTW_FC4TYPES,
				   &entwy->type);
		put_unawigned_be16(wen, &entwy->wen);
		memcpy(&entwy->vawue, fc_host_suppowted_fc4s(wpowt->host),
		       FC_FDMI_POWT_ATTW_FC4TYPES_WEN);

		/* Suppowted Speed */
		entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_POWT_ATTW_FC4TYPES_WEN);
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_POWT_ATTW_SUPPOWTEDSPEED_WEN;
		put_unawigned_be16(FC_FDMI_POWT_ATTW_SUPPOWTEDSPEED,
				   &entwy->type);
		put_unawigned_be16(wen, &entwy->wen);

		put_unawigned_be32(fc_host_suppowted_speeds(wpowt->host),
				   &entwy->vawue);

		/* Cuwwent Powt Speed */
		entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_POWT_ATTW_SUPPOWTEDSPEED_WEN);
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_POWT_ATTW_CUWWENTPOWTSPEED_WEN;
		put_unawigned_be16(FC_FDMI_POWT_ATTW_CUWWENTPOWTSPEED,
				   &entwy->type);
		put_unawigned_be16(wen, &entwy->wen);
		put_unawigned_be32(wpowt->wink_speed,
				   &entwy->vawue);

		/* Max Fwame Size */
		entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_POWT_ATTW_CUWWENTPOWTSPEED_WEN);
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_POWT_ATTW_MAXFWAMESIZE_WEN;
		put_unawigned_be16(FC_FDMI_POWT_ATTW_MAXFWAMESIZE,
				   &entwy->type);
		put_unawigned_be16(wen, &entwy->wen);
		put_unawigned_be32(fc_host_maxfwame_size(wpowt->host),
				   &entwy->vawue);

		/* OS Device Name */
		entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_POWT_ATTW_MAXFWAMESIZE_WEN);
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_POWT_ATTW_OSDEVICENAME_WEN;
		put_unawigned_be16(FC_FDMI_POWT_ATTW_OSDEVICENAME,
				   &entwy->type);
		put_unawigned_be16(wen, &entwy->wen);
		/* Use the sysfs device name */
		fc_ct_ms_fiww_attw(entwy,
			dev_name(&wpowt->host->shost_gendev),
			stwnwen(dev_name(&wpowt->host->shost_gendev),
				FC_FDMI_POWT_ATTW_HOSTNAME_WEN));

		/* Host Name */
		entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_POWT_ATTW_OSDEVICENAME_WEN);
		wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
		wen += FC_FDMI_POWT_ATTW_HOSTNAME_WEN;
		put_unawigned_be16(FC_FDMI_POWT_ATTW_HOSTNAME,
				   &entwy->type);
		put_unawigned_be16(wen, &entwy->wen);
		if (stwwen(fc_host_system_hostname(wpowt->host)))
			fc_ct_ms_fiww_attw(entwy,
				fc_host_system_hostname(wpowt->host),
				stwnwen(fc_host_system_hostname(wpowt->host),
					FC_FDMI_POWT_ATTW_HOSTNAME_WEN));
		ewse
			fc_ct_ms_fiww_attw(entwy,
				init_utsname()->nodename,
				FC_FDMI_POWT_ATTW_HOSTNAME_WEN);


		if (fc_host->fdmi_vewsion == FDMI_V2) {

			/* Node name */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_POWT_ATTW_HOSTNAME_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_POWT_ATTW_NODENAME_WEN;
			put_unawigned_be16(FC_FDMI_POWT_ATTW_NODENAME,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			put_unawigned_be64(fc_host_node_name(wpowt->host),
					&entwy->vawue);

			/* Powt name  */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_POWT_ATTW_NODENAME_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_POWT_ATTW_POWTNAME_WEN;
			put_unawigned_be16(FC_FDMI_POWT_ATTW_POWTNAME,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			put_unawigned_be64(wpowt->wwpn,
					&entwy->vawue);

			/* Powt symbowic name */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_POWT_ATTW_POWTNAME_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_POWT_ATTW_SYMBOWICNAME_WEN;
			put_unawigned_be16(FC_FDMI_POWT_ATTW_SYMBOWICNAME,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			fc_ct_ms_fiww_attw(entwy,
					fc_host_symbowic_name(wpowt->host),
					FC_FDMI_POWT_ATTW_SYMBOWICNAME_WEN);

			/* Powt type */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_POWT_ATTW_SYMBOWICNAME_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_POWT_ATTW_POWTTYPE_WEN;
			put_unawigned_be16(FC_FDMI_POWT_ATTW_POWTTYPE,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			put_unawigned_be32(fc_host_powt_type(wpowt->host),
					&entwy->vawue);

			/* Suppowted cwass of sewvice */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_POWT_ATTW_POWTTYPE_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_POWT_ATTW_SUPPOWTEDCWASSSWVC_WEN;
			put_unawigned_be16(FC_FDMI_POWT_ATTW_SUPPOWTEDCWASSSWVC,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			put_unawigned_be32(fc_host_suppowted_cwasses(wpowt->host),
					&entwy->vawue);

			/* Powt Fabwic name */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_POWT_ATTW_SUPPOWTEDCWASSSWVC_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_POWT_ATTW_FABWICNAME_WEN;
			put_unawigned_be16(FC_FDMI_POWT_ATTW_FABWICNAME,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			put_unawigned_be64(fc_host_fabwic_name(wpowt->host),
					&entwy->vawue);

			/* Powt active FC-4 */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_POWT_ATTW_FABWICNAME_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_POWT_ATTW_CUWWENTFC4TYPE_WEN;
			put_unawigned_be16(FC_FDMI_POWT_ATTW_CUWWENTFC4TYPE,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			memcpy(&entwy->vawue, fc_host_active_fc4s(wpowt->host),
					FC_FDMI_POWT_ATTW_CUWWENTFC4TYPE_WEN);

			/* Powt state */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_POWT_ATTW_CUWWENTFC4TYPE_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_POWT_ATTW_POWTSTATE_WEN;
			put_unawigned_be16(FC_FDMI_POWT_ATTW_POWTSTATE,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			put_unawigned_be32(fc_host_powt_state(wpowt->host),
					&entwy->vawue);

			/* Discovewed powts */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_POWT_ATTW_POWTSTATE_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_POWT_ATTW_DISCOVEWEDPOWTS_WEN;
			put_unawigned_be16(FC_FDMI_POWT_ATTW_DISCOVEWEDPOWTS,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			put_unawigned_be32(fc_host_num_discovewed_powts(wpowt->host),
					&entwy->vawue);

			/* Powt ID */
			entwy = (stwuct fc_fdmi_attw_entwy *)((chaw *)entwy->vawue +
					FC_FDMI_POWT_ATTW_DISCOVEWEDPOWTS_WEN);
			wen = FC_FDMI_ATTW_ENTWY_HEADEW_WEN;
			wen += FC_FDMI_POWT_ATTW_POWTID_WEN;
			put_unawigned_be16(FC_FDMI_POWT_ATTW_POWTID,
					&entwy->type);
			put_unawigned_be16(wen, &entwy->wen);
			put_unawigned_be32(fc_host_powt_id(wpowt->host),
					&entwy->vawue);
		}

		bweak;
	case FC_FDMI_DPWT:
		wen = sizeof(stwuct fc_fdmi_dpwt);
		ct = fc_ct_hdw_fiww(fp, op, wen, FC_FST_MGMT,
				    FC_FDMI_SUBTYPE);
		/* Powt Name */
		put_unawigned_be64(wpowt->wwpn,
				   &ct->paywoad.dpwt.powt.powtname);
		bweak;
	case FC_FDMI_DHBA:
		wen = sizeof(stwuct fc_fdmi_dhba);
		ct = fc_ct_hdw_fiww(fp, op, wen, FC_FST_MGMT,
				    FC_FDMI_SUBTYPE);
		/* HBA Identifiew */
		put_unawigned_be64(wpowt->wwpn, &ct->paywoad.dhba.hbaid.id);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	*w_ctw = FC_WCTW_DD_UNSOW_CTW;
	*fh_type = FC_TYPE_CT;
	wetuwn 0;
}

/**
 * fc_ct_fiww() - Fiww in a common twanspowt sewvice wequest fwame
 * @wpowt: wocaw powt.
 * @fc_id: FC_ID of non-destination wpowt fow GPN_ID and simiwaw inquiwies.
 * @fp: fwame to contain paywoad.
 * @op: CT opcode.
 * @w_ctw: pointew to FC headew W_CTW.
 * @fh_type: pointew to FC-4 type.
 */
static inwine int fc_ct_fiww(stwuct fc_wpowt *wpowt,
		      u32 fc_id, stwuct fc_fwame *fp,
		      unsigned int op, enum fc_wctw *w_ctw,
		      enum fc_fh_type *fh_type, u32 *did)
{
	int wc = -EINVAW;

	switch (fc_id) {
	case FC_FID_MGMT_SEWV:
		wc = fc_ct_ms_fiww(wpowt, fc_id, fp, op, w_ctw, fh_type);
		*did = FC_FID_MGMT_SEWV;
		bweak;
	case FC_FID_DIW_SEWV:
	defauwt:
		wc = fc_ct_ns_fiww(wpowt, fc_id, fp, op, w_ctw, fh_type);
		*did = FC_FID_DIW_SEWV;
		bweak;
	}

	wetuwn wc;
}
/**
 * fc_pwogi_fiww - Fiww in pwogi wequest fwame
 */
static inwine void fc_pwogi_fiww(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp,
				 unsigned int op)
{
	stwuct fc_ews_fwogi *pwogi;
	stwuct fc_ews_csp *csp;
	stwuct fc_ews_cssp *cp;

	pwogi = fc_fwame_paywoad_get(fp, sizeof(*pwogi));
	memset(pwogi, 0, sizeof(*pwogi));
	pwogi->fw_cmd = (u8) op;
	put_unawigned_be64(wpowt->wwpn, &pwogi->fw_wwpn);
	put_unawigned_be64(wpowt->wwnn, &pwogi->fw_wwnn);

	csp = &pwogi->fw_csp;
	csp->sp_hi_vew = 0x20;
	csp->sp_wo_vew = 0x20;
	csp->sp_bb_cwed = htons(10);	/* this gets set by gateway */
	csp->sp_bb_data = htons((u16) wpowt->mfs);
	cp = &pwogi->fw_cssp[3 - 1];	/* cwass 3 pawametews */
	cp->cp_cwass = htons(FC_CPC_VAWID | FC_CPC_SEQ);
	csp->sp_featuwes = htons(FC_SP_FT_CIWO);
	csp->sp_tot_seq = htons(255);	/* seq. we accept */
	csp->sp_wew_off = htons(0x1f);
	csp->sp_e_d_tov = htonw(wpowt->e_d_tov);

	cp->cp_wdfs = htons((u16) wpowt->mfs);
	cp->cp_con_seq = htons(255);
	cp->cp_open_seq = 1;
}

/**
 * fc_fwogi_fiww - Fiww in a fwogi wequest fwame.
 */
static inwine void fc_fwogi_fiww(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	stwuct fc_ews_csp *sp;
	stwuct fc_ews_cssp *cp;
	stwuct fc_ews_fwogi *fwogi;

	fwogi = fc_fwame_paywoad_get(fp, sizeof(*fwogi));
	memset(fwogi, 0, sizeof(*fwogi));
	fwogi->fw_cmd = (u8) EWS_FWOGI;
	put_unawigned_be64(wpowt->wwpn, &fwogi->fw_wwpn);
	put_unawigned_be64(wpowt->wwnn, &fwogi->fw_wwnn);
	sp = &fwogi->fw_csp;
	sp->sp_hi_vew = 0x20;
	sp->sp_wo_vew = 0x20;
	sp->sp_bb_cwed = htons(10);	/* this gets set by gateway */
	sp->sp_bb_data = htons((u16) wpowt->mfs);
	cp = &fwogi->fw_cssp[3 - 1];	/* cwass 3 pawametews */
	cp->cp_cwass = htons(FC_CPC_VAWID | FC_CPC_SEQ);
	if (wpowt->does_npiv)
		sp->sp_featuwes = htons(FC_SP_FT_NPIV);
}

/**
 * fc_fdisc_fiww - Fiww in a fdisc wequest fwame.
 */
static inwine void fc_fdisc_fiww(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	stwuct fc_ews_csp *sp;
	stwuct fc_ews_cssp *cp;
	stwuct fc_ews_fwogi *fdisc;

	fdisc = fc_fwame_paywoad_get(fp, sizeof(*fdisc));
	memset(fdisc, 0, sizeof(*fdisc));
	fdisc->fw_cmd = (u8) EWS_FDISC;
	put_unawigned_be64(wpowt->wwpn, &fdisc->fw_wwpn);
	put_unawigned_be64(wpowt->wwnn, &fdisc->fw_wwnn);
	sp = &fdisc->fw_csp;
	sp->sp_hi_vew = 0x20;
	sp->sp_wo_vew = 0x20;
	sp->sp_bb_cwed = htons(10);	/* this gets set by gateway */
	sp->sp_bb_data = htons((u16) wpowt->mfs);
	cp = &fdisc->fw_cssp[3 - 1];	/* cwass 3 pawametews */
	cp->cp_cwass = htons(FC_CPC_VAWID | FC_CPC_SEQ);
}

/**
 * fc_wogo_fiww - Fiww in a wogo wequest fwame.
 */
static inwine void fc_wogo_fiww(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	stwuct fc_ews_wogo *wogo;

	wogo = fc_fwame_paywoad_get(fp, sizeof(*wogo));
	memset(wogo, 0, sizeof(*wogo));
	wogo->fw_cmd = EWS_WOGO;
	hton24(wogo->fw_n_powt_id, wpowt->powt_id);
	wogo->fw_n_powt_wwn = htonww(wpowt->wwpn);
}

/**
 * fc_wtv_fiww - Fiww in WTV (wead timeout vawue) wequest fwame.
 */
static inwine void fc_wtv_fiww(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	stwuct fc_ews_wtv *wtv;

	wtv = fc_fwame_paywoad_get(fp, sizeof(*wtv));
	memset(wtv, 0, sizeof(*wtv));
	wtv->wtv_cmd = EWS_WTV;
}

/**
 * fc_wec_fiww - Fiww in wec wequest fwame
 */
static inwine void fc_wec_fiww(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	stwuct fc_ews_wec *wec;
	stwuct fc_exch *ep = fc_seq_exch(fw_seq(fp));

	wec = fc_fwame_paywoad_get(fp, sizeof(*wec));
	memset(wec, 0, sizeof(*wec));
	wec->wec_cmd = EWS_WEC;
	hton24(wec->wec_s_id, wpowt->powt_id);
	wec->wec_ox_id = htons(ep->oxid);
	wec->wec_wx_id = htons(ep->wxid);
}

/**
 * fc_pwwi_fiww - Fiww in pwwi wequest fwame
 */
static inwine void fc_pwwi_fiww(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	stwuct {
		stwuct fc_ews_pwwi pwwi;
		stwuct fc_ews_spp spp;
	} *pp;

	pp = fc_fwame_paywoad_get(fp, sizeof(*pp));
	memset(pp, 0, sizeof(*pp));
	pp->pwwi.pwwi_cmd = EWS_PWWI;
	pp->pwwi.pwwi_spp_wen = sizeof(stwuct fc_ews_spp);
	pp->pwwi.pwwi_wen = htons(sizeof(*pp));
	pp->spp.spp_type = FC_TYPE_FCP;
	pp->spp.spp_fwags = FC_SPP_EST_IMG_PAIW;
	pp->spp.spp_pawams = htonw(wpowt->sewvice_pawams);
}

/**
 * fc_scw_fiww - Fiww in a scw wequest fwame.
 */
static inwine void fc_scw_fiww(stwuct fc_wpowt *wpowt, stwuct fc_fwame *fp)
{
	stwuct fc_ews_scw *scw;

	scw = fc_fwame_paywoad_get(fp, sizeof(*scw));
	memset(scw, 0, sizeof(*scw));
	scw->scw_cmd = EWS_SCW;
	scw->scw_weg_func = EWS_SCWF_FUWW;
}

/**
 * fc_ews_fiww - Fiww in an EWS  wequest fwame
 */
static inwine int fc_ews_fiww(stwuct fc_wpowt *wpowt,
		       u32 did,
		       stwuct fc_fwame *fp, unsigned int op,
		       enum fc_wctw *w_ctw, enum fc_fh_type *fh_type)
{
	switch (op) {
	case EWS_ADISC:
		fc_adisc_fiww(wpowt, fp);
		bweak;

	case EWS_PWOGI:
		fc_pwogi_fiww(wpowt, fp, EWS_PWOGI);
		bweak;

	case EWS_FWOGI:
		fc_fwogi_fiww(wpowt, fp);
		bweak;

	case EWS_FDISC:
		fc_fdisc_fiww(wpowt, fp);
		bweak;

	case EWS_WOGO:
		fc_wogo_fiww(wpowt, fp);
		bweak;

	case EWS_WTV:
		fc_wtv_fiww(wpowt, fp);
		bweak;

	case EWS_WEC:
		fc_wec_fiww(wpowt, fp);
		bweak;

	case EWS_PWWI:
		fc_pwwi_fiww(wpowt, fp);
		bweak;

	case EWS_SCW:
		fc_scw_fiww(wpowt, fp);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	*w_ctw = FC_WCTW_EWS_WEQ;
	*fh_type = FC_TYPE_EWS;
	wetuwn 0;
}
#endif /* _FC_ENCODE_H_ */
