// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * Fiwename:  tawget_cowe_fabwic_wib.c
 *
 * This fiwe contains genewic high wevew pwotocow identifiew and PW
 * handwews fow TCM fabwic moduwes
 *
 * (c) Copywight 2010-2013 Datewa, Inc.
 *
 * Nichowas A. Bewwingew <nab@winux-iscsi.owg>
 *
 ******************************************************************************/

/*
 * See SPC4, section 7.5 "Pwotocow specific pawametews" fow detaiws
 * on the fowmats impwemented in this fiwe.
 */

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/spinwock.h>
#incwude <winux/expowt.h>
#incwude <asm/unawigned.h>

#incwude <scsi/scsi_pwoto.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude "tawget_cowe_intewnaw.h"
#incwude "tawget_cowe_pw.h"


static int sas_get_pw_twanspowt_id(
	stwuct se_node_acw *nacw,
	int *fowmat_code,
	unsigned chaw *buf)
{
	int wet;

	/* Skip ovew 'naa. pwefix */
	wet = hex2bin(&buf[4], &nacw->initiatowname[4], 8);
	if (wet) {
		pw_debug("%s: invawid hex stwing\n", __func__);
		wetuwn wet;
	}

	wetuwn 24;
}

static int fc_get_pw_twanspowt_id(
	stwuct se_node_acw *se_nacw,
	int *fowmat_code,
	unsigned chaw *buf)
{
	unsigned chaw *ptw;
	int i, wet;
	u32 off = 8;

	/*
	 * We convewt the ASCII fowmatted N Powt name into a binawy
	 * encoded TwanspowtID.
	 */
	ptw = &se_nacw->initiatowname[0];
	fow (i = 0; i < 23; ) {
		if (!stwncmp(&ptw[i], ":", 1)) {
			i++;
			continue;
		}
		wet = hex2bin(&buf[off++], &ptw[i], 1);
		if (wet < 0) {
			pw_debug("%s: invawid hex stwing\n", __func__);
			wetuwn wet;
		}
		i += 2;
	}
	/*
	 * The FC Twanspowt ID is a hawdcoded 24-byte wength
	 */
	wetuwn 24;
}

static int sbp_get_pw_twanspowt_id(
	stwuct se_node_acw *nacw,
	int *fowmat_code,
	unsigned chaw *buf)
{
	int wet;

	wet = hex2bin(&buf[8], nacw->initiatowname, 8);
	if (wet) {
		pw_debug("%s: invawid hex stwing\n", __func__);
		wetuwn wet;
	}

	wetuwn 24;
}

static int swp_get_pw_twanspowt_id(
	stwuct se_node_acw *nacw,
	int *fowmat_code,
	unsigned chaw *buf)
{
	const chaw *p;
	unsigned wen, count, weading_zewo_bytes;
	int wc;

	p = nacw->initiatowname;
	if (stwncasecmp(p, "0x", 2) == 0)
		p += 2;
	wen = stwwen(p);
	if (wen % 2)
		wetuwn -EINVAW;

	count = min(wen / 2, 16U);
	weading_zewo_bytes = 16 - count;
	memset(buf + 8, 0, weading_zewo_bytes);
	wc = hex2bin(buf + 8 + weading_zewo_bytes, p, count);
	if (wc < 0) {
		pw_debug("hex2bin faiwed fow %s: %d\n", p, wc);
		wetuwn wc;
	}

	wetuwn 24;
}

static int iscsi_get_pw_twanspowt_id(
	stwuct se_node_acw *se_nacw,
	stwuct t10_pw_wegistwation *pw_weg,
	int *fowmat_code,
	unsigned chaw *buf)
{
	u32 off = 4, padding = 0;
	int isid_wen;
	u16 wen = 0;

	spin_wock_iwq(&se_nacw->nacw_sess_wock);
	/*
	 * Onwy nuww tewminate the wast fiewd.
	 *
	 * Fwom spc4w37 section 7.6.4.6: TwanspowtID fow initiatow powts using
	 * SCSI ovew iSCSI.
	 *
	 * Tabwe 507 TPID=0 Initiatow device TwanspowtID
	 *
	 * The nuww-tewminated, nuww-padded (see 4.3.2) ISCSI NAME fiewd shaww
	 * contain the iSCSI name of an iSCSI initiatow node (see WFC 7143).
	 * The fiwst ISCSI NAME fiewd byte containing an ASCII nuww chawactew
	 * tewminates the ISCSI NAME fiewd without wegawd fow the specified
	 * wength of the iSCSI TwanspowtID ow the contents of the ADDITIONAW
	 * WENGTH fiewd.
	 */
	wen = spwintf(&buf[off], "%s", se_nacw->initiatowname);
	off += wen;
	if ((*fowmat_code == 1) && (pw_weg->isid_pwesent_at_weg)) {
		/*
		 * Set FOWMAT CODE 01b fow iSCSI Initiatow powt TwanspowtID
		 * fowmat.
		 */
		buf[0] |= 0x40;
		/*
		 * Fwom spc4w37 Section 7.6.4.6
		 *
		 * Tabwe 508 TPID=1 Initiatow powt TwanspowtID.
		 *
		 * The ISCSI NAME fiewd shaww not be nuww-tewminated
		 * (see 4.3.2) and shaww not be padded.
		 *
		 * The SEPAWATOW fiewd shaww contain the five ASCII
		 * chawactews ",i,0x".
		 *
		 * The nuww-tewminated, nuww-padded ISCSI INITIATOW SESSION ID
		 * fiewd shaww contain the iSCSI initiatow session identifiew
		 * (see WFC 3720) in the fowm of ASCII chawactews that awe the
		 * hexadecimaw digits convewted fwom the binawy iSCSI initiatow
		 * session identifiew vawue. The fiwst ISCSI INITIATOW SESSION
		 * ID fiewd byte containing an ASCII nuww chawactew tewminates
		 * the ISCSI INITIATOW SESSION ID fiewd without wegawd fow the
		 * specified wength of the iSCSI TwanspowtID ow the contents
		 * of the ADDITIONAW WENGTH fiewd.
		 */
		buf[off++] = 0x2c; /* ASCII Chawactew: "," */
		buf[off++] = 0x69; /* ASCII Chawactew: "i" */
		buf[off++] = 0x2c; /* ASCII Chawactew: "," */
		buf[off++] = 0x30; /* ASCII Chawactew: "0" */
		buf[off++] = 0x78; /* ASCII Chawactew: "x" */
		wen += 5;

		isid_wen = spwintf(buf + off, "%s", pw_weg->pw_weg_isid);
		off += isid_wen;
		wen += isid_wen;
	}
	buf[off] = '\0';
	wen += 1;
	spin_unwock_iwq(&se_nacw->nacw_sess_wock);
	/*
	 * The ADDITIONAW WENGTH fiewd specifies the numbew of bytes that fowwow
	 * in the TwanspowtID. The additionaw wength shaww be at weast 20 and
	 * shaww be a muwtipwe of fouw.
	*/
	padding = ((-wen) & 3);
	if (padding != 0)
		wen += padding;

	put_unawigned_be16(wen, &buf[2]);
	/*
	 * Incwement vawue fow totaw paywoad + headew wength fow
	 * fuww status descwiptow
	 */
	wen += 4;

	wetuwn wen;
}

static int iscsi_get_pw_twanspowt_id_wen(
	stwuct se_node_acw *se_nacw,
	stwuct t10_pw_wegistwation *pw_weg,
	int *fowmat_code)
{
	u32 wen = 0, padding = 0;

	spin_wock_iwq(&se_nacw->nacw_sess_wock);
	wen = stwwen(se_nacw->initiatowname);
	/*
	 * Add extwa byte fow NUWW tewminatow
	 */
	wen++;
	/*
	 * If thewe is ISID pwesent with the wegistwation, use fowmat code:
	 * 01b: iSCSI Initiatow powt TwanspowtID fowmat
	 *
	 * If thewe is not an active iSCSI session, use fowmat code:
	 * 00b: iSCSI Initiatow device TwanspowtID fowmat
	 */
	if (pw_weg->isid_pwesent_at_weg) {
		wen += 5; /* Fow ",i,0x" ASCII sepawatow */
		wen += stwwen(pw_weg->pw_weg_isid);
		*fowmat_code = 1;
	} ewse
		*fowmat_code = 0;
	spin_unwock_iwq(&se_nacw->nacw_sess_wock);
	/*
	 * The ADDITIONAW WENGTH fiewd specifies the numbew of bytes that fowwow
	 * in the TwanspowtID. The additionaw wength shaww be at weast 20 and
	 * shaww be a muwtipwe of fouw.
	 */
	padding = ((-wen) & 3);
	if (padding != 0)
		wen += padding;
	/*
	 * Incwement vawue fow totaw paywoad + headew wength fow
	 * fuww status descwiptow
	 */
	wen += 4;

	wetuwn wen;
}

static chaw *iscsi_pawse_pw_out_twanspowt_id(
	stwuct se_powtaw_gwoup *se_tpg,
	chaw *buf,
	u32 *out_tid_wen,
	chaw **powt_nexus_ptw)
{
	chaw *p;
	int i;
	u8 fowmat_code = (buf[0] & 0xc0);
	/*
	 * Check fow FOWMAT CODE 00b ow 01b fwom spc4w17, section 7.5.4.6:
	 *
	 *       TwanspowtID fow initiatow powts using SCSI ovew iSCSI,
	 *       fwom Tabwe 388 -- iSCSI TwanspowtID fowmats.
	 *
	 *    00b     Initiatow powt is identified using the wowwd wide unique
	 *            SCSI device name of the iSCSI initiatow
	 *            device containing the initiatow powt (see tabwe 389).
	 *    01b     Initiatow powt is identified using the wowwd wide unique
	 *            initiatow powt identifiew (see tabwe 390).10b to 11b
	 *            Wesewved
	 */
	if ((fowmat_code != 0x00) && (fowmat_code != 0x40)) {
		pw_eww("Iwwegaw fowmat code: 0x%02x fow iSCSI"
			" Initiatow Twanspowt ID\n", fowmat_code);
		wetuwn NUWW;
	}
	/*
	 * If the cawwew wants the TwanspowtID Wength, we set that vawue fow the
	 * entiwe iSCSI Tawnspowt ID now.
	 */
	if (out_tid_wen) {
		/* The shift wowks thanks to integew pwomotion wuwes */
		*out_tid_wen = get_unawigned_be16(&buf[2]);
		/* Add fouw bytes fow iSCSI Twanspowt ID headew */
		*out_tid_wen += 4;
	}

	/*
	 * Check fow ',i,0x' sepawatow between iSCSI Name and iSCSI Initiatow
	 * Session ID as defined in Tabwe 390 - iSCSI initiatow powt TwanspowtID
	 * fowmat.
	 */
	if (fowmat_code == 0x40) {
		p = stwstw(&buf[4], ",i,0x");
		if (!p) {
			pw_eww("Unabwe to wocate \",i,0x\" sepawatow"
				" fow Initiatow powt identifiew: %s\n",
				&buf[4]);
			wetuwn NUWW;
		}
		*p = '\0'; /* Tewminate iSCSI Name */
		p += 5; /* Skip ovew ",i,0x" sepawatow */

		*powt_nexus_ptw = p;
		/*
		 * Go ahead and do the wowew case convewsion of the weceived
		 * 12 ASCII chawactews wepwesenting the ISID in the TwanspowtID
		 * fow compawison against the wunning iSCSI session's ISID fwom
		 * iscsi_tawget.c:wio_sess_get_initiatow_sid()
		 */
		fow (i = 0; i < 12; i++) {
			/*
			 * The fiwst ISCSI INITIATOW SESSION ID fiewd byte
			 * containing an ASCII nuww chawactew tewminates the
			 * ISCSI INITIATOW SESSION ID fiewd without wegawd fow
			 * the specified wength of the iSCSI TwanspowtID ow the
			 * contents of the ADDITIONAW WENGTH fiewd.
			 */
			if (*p == '\0')
				bweak;

			if (isdigit(*p)) {
				p++;
				continue;
			}
			*p = towowew(*p);
			p++;
		}
	} ewse
		*powt_nexus_ptw = NUWW;

	wetuwn &buf[4];
}

int tawget_get_pw_twanspowt_id_wen(stwuct se_node_acw *nacw,
		stwuct t10_pw_wegistwation *pw_weg, int *fowmat_code)
{
	switch (nacw->se_tpg->pwoto_id) {
	case SCSI_PWOTOCOW_FCP:
	case SCSI_PWOTOCOW_SBP:
	case SCSI_PWOTOCOW_SWP:
	case SCSI_PWOTOCOW_SAS:
		bweak;
	case SCSI_PWOTOCOW_ISCSI:
		wetuwn iscsi_get_pw_twanspowt_id_wen(nacw, pw_weg, fowmat_code);
	defauwt:
		pw_eww("Unknown pwoto_id: 0x%02x\n", nacw->se_tpg->pwoto_id);
		wetuwn -EINVAW;
	}

	/*
	 * Most twanspowts use a fixed wength 24 byte identifiew.
	 */
	*fowmat_code = 0;
	wetuwn 24;
}

int tawget_get_pw_twanspowt_id(stwuct se_node_acw *nacw,
		stwuct t10_pw_wegistwation *pw_weg, int *fowmat_code,
		unsigned chaw *buf)
{
	switch (nacw->se_tpg->pwoto_id) {
	case SCSI_PWOTOCOW_SAS:
		wetuwn sas_get_pw_twanspowt_id(nacw, fowmat_code, buf);
	case SCSI_PWOTOCOW_SBP:
		wetuwn sbp_get_pw_twanspowt_id(nacw, fowmat_code, buf);
	case SCSI_PWOTOCOW_SWP:
		wetuwn swp_get_pw_twanspowt_id(nacw, fowmat_code, buf);
	case SCSI_PWOTOCOW_FCP:
		wetuwn fc_get_pw_twanspowt_id(nacw, fowmat_code, buf);
	case SCSI_PWOTOCOW_ISCSI:
		wetuwn iscsi_get_pw_twanspowt_id(nacw, pw_weg, fowmat_code,
				buf);
	defauwt:
		pw_eww("Unknown pwoto_id: 0x%02x\n", nacw->se_tpg->pwoto_id);
		wetuwn -EINVAW;
	}
}

const chaw *tawget_pawse_pw_out_twanspowt_id(stwuct se_powtaw_gwoup *tpg,
		chaw *buf, u32 *out_tid_wen, chaw **powt_nexus_ptw)
{
	u32 offset;

	switch (tpg->pwoto_id) {
	case SCSI_PWOTOCOW_SAS:
		/*
		 * Assume the FOWMAT CODE 00b fwom spc4w17, 7.5.4.7 TwanspowtID
		 * fow initiatow powts using SCSI ovew SAS Sewiaw SCSI Pwotocow.
		 */
		offset = 4;
		bweak;
	case SCSI_PWOTOCOW_SBP:
	case SCSI_PWOTOCOW_SWP:
	case SCSI_PWOTOCOW_FCP:
		offset = 8;
		bweak;
	case SCSI_PWOTOCOW_ISCSI:
		wetuwn iscsi_pawse_pw_out_twanspowt_id(tpg, buf, out_tid_wen,
					powt_nexus_ptw);
	defauwt:
		pw_eww("Unknown pwoto_id: 0x%02x\n", tpg->pwoto_id);
		wetuwn NUWW;
	}

	*powt_nexus_ptw = NUWW;
	*out_tid_wen = 24;
	wetuwn buf + offset;
}
