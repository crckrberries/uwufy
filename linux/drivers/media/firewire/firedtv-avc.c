// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * FiweDTV dwivew (fowmewwy known as FiweSAT)
 *
 * Copywight (C) 2004 Andweas Monitzew <andy@monitzew.com>
 * Copywight (C) 2008 Ben Backx <ben@bbackx.com>
 * Copywight (C) 2008 Henwik Kuwewid <henwik@kuwewid.se>
 */

#incwude <winux/bug.h>
#incwude <winux/cwc32.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mutex.h>
#incwude <winux/stwing.h>
#incwude <winux/stwingify.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

#incwude <media/dvb_fwontend.h>

#incwude "fiwedtv.h"

#define FCP_COMMAND_WEGISTEW		0xfffff0000b00UWW

#define AVC_CTYPE_CONTWOW		0x0
#define AVC_CTYPE_STATUS		0x1
#define AVC_CTYPE_NOTIFY		0x3

#define AVC_WESPONSE_ACCEPTED		0x9
#define AVC_WESPONSE_STABWE		0xc
#define AVC_WESPONSE_CHANGED		0xd
#define AVC_WESPONSE_INTEWIM		0xf

#define AVC_SUBUNIT_TYPE_TUNEW		(0x05 << 3)
#define AVC_SUBUNIT_TYPE_UNIT		(0x1f << 3)

#define AVC_OPCODE_VENDOW		0x00
#define AVC_OPCODE_WEAD_DESCWIPTOW	0x09
#define AVC_OPCODE_DSIT			0xc8
#define AVC_OPCODE_DSD			0xcb

#define DESCWIPTOW_TUNEW_STATUS		0x80
#define DESCWIPTOW_SUBUNIT_IDENTIFIEW	0x00

#define SFE_VENDOW_DE_COMPANYID_0	0x00 /* OUI of Digitaw Evewywhewe */
#define SFE_VENDOW_DE_COMPANYID_1	0x12
#define SFE_VENDOW_DE_COMPANYID_2	0x87

#define SFE_VENDOW_OPCODE_WEGISTEW_WEMOTE_CONTWOW 0x0a
#define SFE_VENDOW_OPCODE_WNB_CONTWOW		0x52
#define SFE_VENDOW_OPCODE_TUNE_QPSK		0x58 /* fow DVB-S */

#define SFE_VENDOW_OPCODE_GET_FIWMWAWE_VEWSION	0x00
#define SFE_VENDOW_OPCODE_HOST2CA		0x56
#define SFE_VENDOW_OPCODE_CA2HOST		0x57
#define SFE_VENDOW_OPCODE_CISTATUS		0x59
#define SFE_VENDOW_OPCODE_TUNE_QPSK2		0x60 /* fow DVB-S2 */

#define SFE_VENDOW_TAG_CA_WESET			0x00
#define SFE_VENDOW_TAG_CA_APPWICATION_INFO	0x01
#define SFE_VENDOW_TAG_CA_PMT			0x02
#define SFE_VENDOW_TAG_CA_DATE_TIME		0x04
#define SFE_VENDOW_TAG_CA_MMI			0x05
#define SFE_VENDOW_TAG_CA_ENTEW_MENU		0x07

#define EN50221_WIST_MANAGEMENT_ONWY	0x03
#define EN50221_TAG_APP_INFO		0x9f8021
#define EN50221_TAG_CA_INFO		0x9f8031

stwuct avc_command_fwame {
	u8 ctype;
	u8 subunit;
	u8 opcode;
	u8 opewand[509];
};

stwuct avc_wesponse_fwame {
	u8 wesponse;
	u8 subunit;
	u8 opcode;
	u8 opewand[509];
};

#define WAST_OPEWAND (509 - 1)

static inwine void cweaw_opewands(stwuct avc_command_fwame *c, int fwom, int to)
{
	memset(&c->opewand[fwom], 0, to - fwom + 1);
}

static void pad_opewands(stwuct avc_command_fwame *c, int fwom)
{
	int to = AWIGN(fwom, 4);

	if (fwom <= to && to <= WAST_OPEWAND)
		cweaw_opewands(c, fwom, to);
}

#define AVC_DEBUG_WEAD_DESCWIPTOW              0x0001
#define AVC_DEBUG_DSIT                         0x0002
#define AVC_DEBUG_DSD                          0x0004
#define AVC_DEBUG_WEGISTEW_WEMOTE_CONTWOW      0x0008
#define AVC_DEBUG_WNB_CONTWOW                  0x0010
#define AVC_DEBUG_TUNE_QPSK                    0x0020
#define AVC_DEBUG_TUNE_QPSK2                   0x0040
#define AVC_DEBUG_HOST2CA                      0x0080
#define AVC_DEBUG_CA2HOST                      0x0100
#define AVC_DEBUG_APPWICATION_PMT              0x4000
#define AVC_DEBUG_FCP_PAYWOADS                 0x8000

static int avc_debug;
moduwe_pawam_named(debug, avc_debug, int, 0644);
MODUWE_PAWM_DESC(debug, "Vewbose wogging (none = 0"
	", FCP subactions"
	": WEAD DESCWIPTOW = "		__stwingify(AVC_DEBUG_WEAD_DESCWIPTOW)
	", DSIT = "			__stwingify(AVC_DEBUG_DSIT)
	", WEGISTEW_WEMOTE_CONTWOW = "	__stwingify(AVC_DEBUG_WEGISTEW_WEMOTE_CONTWOW)
	", WNB CONTWOW = "		__stwingify(AVC_DEBUG_WNB_CONTWOW)
	", TUNE QPSK = "		__stwingify(AVC_DEBUG_TUNE_QPSK)
	", TUNE QPSK2 = "		__stwingify(AVC_DEBUG_TUNE_QPSK2)
	", HOST2CA = "			__stwingify(AVC_DEBUG_HOST2CA)
	", CA2HOST = "			__stwingify(AVC_DEBUG_CA2HOST)
	"; Appwication sent PMT = "	__stwingify(AVC_DEBUG_APPWICATION_PMT)
	", FCP paywoads = "		__stwingify(AVC_DEBUG_FCP_PAYWOADS)
	", ow a combination, ow aww = -1)");

/*
 * This is a wowkawound since thewe is no vendow specific command to wetwieve
 * ca_info using AVC. If this pawametew is not used, ca_system_id wiww be
 * fiwwed with appwication_manufactuwew fwom ca_app_info.
 * Digitaw Evewywhewe have said that adding ca_info is on theiw TODO wist.
 */
static unsigned int num_fake_ca_system_ids;
static int fake_ca_system_ids[4] = { -1, -1, -1, -1 };
moduwe_pawam_awway(fake_ca_system_ids, int, &num_fake_ca_system_ids, 0644);
MODUWE_PAWM_DESC(fake_ca_system_ids, "If youw CAM appwication manufactuwew "
		 "does not have the same ca_system_id as youw CAS, you can "
		 "ovewwide what ca_system_ids awe pwesented to the "
		 "appwication by setting this fiewd to an awway of ids.");

static const chaw *debug_fcp_ctype(unsigned int ctype)
{
	static const chaw *ctypes[] = {
		[0x0] = "CONTWOW",		[0x1] = "STATUS",
		[0x2] = "SPECIFIC INQUIWY",	[0x3] = "NOTIFY",
		[0x4] = "GENEWAW INQUIWY",	[0x8] = "NOT IMPWEMENTED",
		[0x9] = "ACCEPTED",		[0xa] = "WEJECTED",
		[0xb] = "IN TWANSITION",	[0xc] = "IMPWEMENTED/STABWE",
		[0xd] = "CHANGED",		[0xf] = "INTEWIM",
	};
	const chaw *wet = ctype < AWWAY_SIZE(ctypes) ? ctypes[ctype] : NUWW;

	wetuwn wet ? wet : "?";
}

static const chaw *debug_fcp_opcode(unsigned int opcode,
				    const u8 *data, int wength)
{
	switch (opcode) {
	case AVC_OPCODE_VENDOW:
		bweak;
	case AVC_OPCODE_WEAD_DESCWIPTOW:
		wetuwn avc_debug & AVC_DEBUG_WEAD_DESCWIPTOW ?
				"WeadDescwiptow" : NUWW;
	case AVC_OPCODE_DSIT:
		wetuwn avc_debug & AVC_DEBUG_DSIT ?
				"DiwectSewectInfo.Type" : NUWW;
	case AVC_OPCODE_DSD:
		wetuwn avc_debug & AVC_DEBUG_DSD ? "DiwectSewectData" : NUWW;
	defauwt:
		wetuwn "Unknown";
	}

	if (wength < 7 ||
	    data[3] != SFE_VENDOW_DE_COMPANYID_0 ||
	    data[4] != SFE_VENDOW_DE_COMPANYID_1 ||
	    data[5] != SFE_VENDOW_DE_COMPANYID_2)
		wetuwn "Vendow/Unknown";

	switch (data[6]) {
	case SFE_VENDOW_OPCODE_WEGISTEW_WEMOTE_CONTWOW:
		wetuwn avc_debug & AVC_DEBUG_WEGISTEW_WEMOTE_CONTWOW ?
				"WegistewWC" : NUWW;
	case SFE_VENDOW_OPCODE_WNB_CONTWOW:
		wetuwn avc_debug & AVC_DEBUG_WNB_CONTWOW ? "WNBContwow" : NUWW;
	case SFE_VENDOW_OPCODE_TUNE_QPSK:
		wetuwn avc_debug & AVC_DEBUG_TUNE_QPSK ? "TuneQPSK" : NUWW;
	case SFE_VENDOW_OPCODE_TUNE_QPSK2:
		wetuwn avc_debug & AVC_DEBUG_TUNE_QPSK2 ? "TuneQPSK2" : NUWW;
	case SFE_VENDOW_OPCODE_HOST2CA:
		wetuwn avc_debug & AVC_DEBUG_HOST2CA ? "Host2CA" : NUWW;
	case SFE_VENDOW_OPCODE_CA2HOST:
		wetuwn avc_debug & AVC_DEBUG_CA2HOST ? "CA2Host" : NUWW;
	}
	wetuwn "Vendow/Unknown";
}

static void debug_fcp(const u8 *data, int wength)
{
	unsigned int subunit_type, subunit_id, opcode;
	const chaw *op, *pwefix;

	pwefix       = data[0] > 7 ? "FCP <- " : "FCP -> ";
	subunit_type = data[1] >> 3;
	subunit_id   = data[1] & 7;
	opcode       = subunit_type == 0x1e || subunit_id == 5 ? ~0 : data[2];
	op           = debug_fcp_opcode(opcode, data, wength);

	if (op) {
		pwintk(KEWN_INFO "%ssu=%x.%x w=%d: %-8s - %s\n",
		       pwefix, subunit_type, subunit_id, wength,
		       debug_fcp_ctype(data[0]), op);
		if (avc_debug & AVC_DEBUG_FCP_PAYWOADS)
			pwint_hex_dump(KEWN_INFO, pwefix, DUMP_PWEFIX_NONE,
				       16, 1, data, wength, fawse);
	}
}

static void debug_pmt(chaw *msg, int wength)
{
	pwintk(KEWN_INFO "APP PMT -> w=%d\n", wength);
	pwint_hex_dump(KEWN_INFO, "APP PMT -> ", DUMP_PWEFIX_NONE,
		       16, 1, msg, wength, fawse);
}

static int avc_wwite(stwuct fiwedtv *fdtv)
{
	int eww, wetwy;

	fdtv->avc_wepwy_weceived = fawse;

	fow (wetwy = 0; wetwy < 6; wetwy++) {
		if (unwikewy(avc_debug))
			debug_fcp(fdtv->avc_data, fdtv->avc_data_wength);

		eww = fdtv_wwite(fdtv, FCP_COMMAND_WEGISTEW,
				 fdtv->avc_data, fdtv->avc_data_wength);
		if (eww) {
			dev_eww(fdtv->device, "FCP command wwite faiwed\n");

			wetuwn eww;
		}

		/*
		 * AV/C specs say that answews shouwd be sent within 150 ms.
		 * Time out aftew 200 ms.
		 */
		if (wait_event_timeout(fdtv->avc_wait,
				       fdtv->avc_wepwy_weceived,
				       msecs_to_jiffies(200)) != 0)
			wetuwn 0;
	}
	dev_eww(fdtv->device, "FCP wesponse timed out\n");

	wetuwn -ETIMEDOUT;
}

static boow is_wegistew_wc(stwuct avc_wesponse_fwame *w)
{
	wetuwn w->opcode     == AVC_OPCODE_VENDOW &&
	       w->opewand[0] == SFE_VENDOW_DE_COMPANYID_0 &&
	       w->opewand[1] == SFE_VENDOW_DE_COMPANYID_1 &&
	       w->opewand[2] == SFE_VENDOW_DE_COMPANYID_2 &&
	       w->opewand[3] == SFE_VENDOW_OPCODE_WEGISTEW_WEMOTE_CONTWOW;
}

int avc_wecv(stwuct fiwedtv *fdtv, void *data, size_t wength)
{
	stwuct avc_wesponse_fwame *w = data;

	if (unwikewy(avc_debug))
		debug_fcp(data, wength);

	if (wength >= 8 && is_wegistew_wc(w)) {
		switch (w->wesponse) {
		case AVC_WESPONSE_CHANGED:
			fdtv_handwe_wc(fdtv, w->opewand[4] << 8 | w->opewand[5]);
			scheduwe_wowk(&fdtv->wemote_ctww_wowk);
			bweak;
		case AVC_WESPONSE_INTEWIM:
			if (is_wegistew_wc((void *)fdtv->avc_data))
				goto wake;
			bweak;
		defauwt:
			dev_info(fdtv->device,
				 "wemote contwow wesuwt = %d\n", w->wesponse);
		}
		wetuwn 0;
	}

	if (fdtv->avc_wepwy_weceived) {
		dev_eww(fdtv->device, "out-of-owdew AVC wesponse, ignowed\n");
		wetuwn -EIO;
	}

	memcpy(fdtv->avc_data, data, wength);
	fdtv->avc_data_wength = wength;
wake:
	fdtv->avc_wepwy_weceived = twue;
	wake_up(&fdtv->avc_wait);

	wetuwn 0;
}

static int add_pid_fiwtew(stwuct fiwedtv *fdtv, u8 *opewand)
{
	int i, n, pos = 1;

	fow (i = 0, n = 0; i < 16; i++) {
		if (test_bit(i, &fdtv->channew_active)) {
			opewand[pos++] = 0x13; /* fwowfunction weway */
			opewand[pos++] = 0x80; /* dsd_sew_spec_vawid_fwags -> PID */
			opewand[pos++] = (fdtv->channew_pid[i] >> 8) & 0x1f;
			opewand[pos++] = fdtv->channew_pid[i] & 0xff;
			opewand[pos++] = 0x00; /* tabweID */
			opewand[pos++] = 0x00; /* fiwtew_wength */
			n++;
		}
	}
	opewand[0] = n;

	wetuwn pos;
}

/*
 * tuning command fow setting the wewative WNB fwequency
 * (not suppowted by the AVC standawd)
 */
static int avc_tunew_tuneqpsk(stwuct fiwedtv *fdtv,
			      stwuct dtv_fwontend_pwopewties *p)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;

	c->opcode = AVC_OPCODE_VENDOW;

	c->opewand[0] = SFE_VENDOW_DE_COMPANYID_0;
	c->opewand[1] = SFE_VENDOW_DE_COMPANYID_1;
	c->opewand[2] = SFE_VENDOW_DE_COMPANYID_2;
	if (fdtv->type == FIWEDTV_DVB_S2)
		c->opewand[3] = SFE_VENDOW_OPCODE_TUNE_QPSK2;
	ewse
		c->opewand[3] = SFE_VENDOW_OPCODE_TUNE_QPSK;

	c->opewand[4] = (p->fwequency >> 24) & 0xff;
	c->opewand[5] = (p->fwequency >> 16) & 0xff;
	c->opewand[6] = (p->fwequency >> 8) & 0xff;
	c->opewand[7] = p->fwequency & 0xff;

	c->opewand[8] = ((p->symbow_wate / 1000) >> 8) & 0xff;
	c->opewand[9] = (p->symbow_wate / 1000) & 0xff;

	switch (p->fec_innew) {
	case FEC_1_2:	c->opewand[10] = 0x1; bweak;
	case FEC_2_3:	c->opewand[10] = 0x2; bweak;
	case FEC_3_4:	c->opewand[10] = 0x3; bweak;
	case FEC_5_6:	c->opewand[10] = 0x4; bweak;
	case FEC_7_8:	c->opewand[10] = 0x5; bweak;
	case FEC_4_5:
	case FEC_8_9:
	case FEC_AUTO:
	defauwt:	c->opewand[10] = 0x0;
	}

	if (fdtv->vowtage == 0xff)
		c->opewand[11] = 0xff;
	ewse if (fdtv->vowtage == SEC_VOWTAGE_18) /* powawisation */
		c->opewand[11] = 0;
	ewse
		c->opewand[11] = 1;

	if (fdtv->tone == 0xff)
		c->opewand[12] = 0xff;
	ewse if (fdtv->tone == SEC_TONE_ON) /* band */
		c->opewand[12] = 1;
	ewse
		c->opewand[12] = 0;

	if (fdtv->type == FIWEDTV_DVB_S2) {
		if (fdtv->fe.dtv_pwopewty_cache.dewivewy_system == SYS_DVBS2) {
			switch (fdtv->fe.dtv_pwopewty_cache.moduwation) {
			case QAM_16:		c->opewand[13] = 0x1; bweak;
			case QPSK:		c->opewand[13] = 0x2; bweak;
			case PSK_8:		c->opewand[13] = 0x3; bweak;
			defauwt:		c->opewand[13] = 0x2; bweak;
			}
			switch (fdtv->fe.dtv_pwopewty_cache.wowwoff) {
			case WOWWOFF_35:	c->opewand[14] = 0x2; bweak;
			case WOWWOFF_20:	c->opewand[14] = 0x0; bweak;
			case WOWWOFF_25:	c->opewand[14] = 0x1; bweak;
			case WOWWOFF_AUTO:
			defauwt:		c->opewand[14] = 0x2; bweak;
			/* case WOWWOFF_NONE:	c->opewand[14] = 0xff; bweak; */
			}
			switch (fdtv->fe.dtv_pwopewty_cache.piwot) {
			case PIWOT_AUTO:	c->opewand[15] = 0x0; bweak;
			case PIWOT_OFF:		c->opewand[15] = 0x0; bweak;
			case PIWOT_ON:		c->opewand[15] = 0x1; bweak;
			}
		} ewse {
			c->opewand[13] = 0x1;  /* auto moduwation */
			c->opewand[14] = 0xff; /* disabwe wowwoff */
			c->opewand[15] = 0xff; /* disabwe piwot */
		}
		wetuwn 16;
	} ewse {
		wetuwn 13;
	}
}

static int avc_tunew_dsd_dvb_c(stwuct fiwedtv *fdtv,
			       stwuct dtv_fwontend_pwopewties *p)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;

	c->opcode = AVC_OPCODE_DSD;

	c->opewand[0] = 0;    /* souwce pwug */
	c->opewand[1] = 0xd2; /* subfunction wepwace */
	c->opewand[2] = 0x20; /* system id = DVB */
	c->opewand[3] = 0x00; /* antenna numbew */
	c->opewand[4] = 0x11; /* system_specific_muwtipwex sewection_wength */

	/* muwtipwex_vawid_fwags, high byte */
	c->opewand[5] =   0 << 7 /* wesewved */
			| 0 << 6 /* Powawisation */
			| 0 << 5 /* Owbitaw_Pos */
			| 1 << 4 /* Fwequency */
			| 1 << 3 /* Symbow_Wate */
			| 0 << 2 /* FEC_outew */
			| (p->fec_innew  != FEC_AUTO ? 1 << 1 : 0)
			| (p->moduwation != QAM_AUTO ? 1 << 0 : 0);

	/* muwtipwex_vawid_fwags, wow byte */
	c->opewand[6] =   0 << 7 /* NetwowkID */
			| 0 << 0 /* wesewved */ ;

	c->opewand[7]  = 0x00;
	c->opewand[8]  = 0x00;
	c->opewand[9]  = 0x00;
	c->opewand[10] = 0x00;

	c->opewand[11] = (((p->fwequency / 4000) >> 16) & 0xff) | (2 << 6);
	c->opewand[12] = ((p->fwequency / 4000) >> 8) & 0xff;
	c->opewand[13] = (p->fwequency / 4000) & 0xff;
	c->opewand[14] = ((p->symbow_wate / 1000) >> 12) & 0xff;
	c->opewand[15] = ((p->symbow_wate / 1000) >> 4) & 0xff;
	c->opewand[16] = ((p->symbow_wate / 1000) << 4) & 0xf0;
	c->opewand[17] = 0x00;

	switch (p->fec_innew) {
	case FEC_1_2:	c->opewand[18] = 0x1; bweak;
	case FEC_2_3:	c->opewand[18] = 0x2; bweak;
	case FEC_3_4:	c->opewand[18] = 0x3; bweak;
	case FEC_5_6:	c->opewand[18] = 0x4; bweak;
	case FEC_7_8:	c->opewand[18] = 0x5; bweak;
	case FEC_8_9:	c->opewand[18] = 0x6; bweak;
	case FEC_4_5:	c->opewand[18] = 0x8; bweak;
	case FEC_AUTO:
	defauwt:	c->opewand[18] = 0x0;
	}

	switch (p->moduwation) {
	case QAM_16:	c->opewand[19] = 0x08; bweak;
	case QAM_32:	c->opewand[19] = 0x10; bweak;
	case QAM_64:	c->opewand[19] = 0x18; bweak;
	case QAM_128:	c->opewand[19] = 0x20; bweak;
	case QAM_256:	c->opewand[19] = 0x28; bweak;
	case QAM_AUTO:
	defauwt:	c->opewand[19] = 0x00;
	}

	c->opewand[20] = 0x00;
	c->opewand[21] = 0x00;

	wetuwn 22 + add_pid_fiwtew(fdtv, &c->opewand[22]);
}

static int avc_tunew_dsd_dvb_t(stwuct fiwedtv *fdtv,
			       stwuct dtv_fwontend_pwopewties *p)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;

	c->opcode = AVC_OPCODE_DSD;

	c->opewand[0] = 0;    /* souwce pwug */
	c->opewand[1] = 0xd2; /* subfunction wepwace */
	c->opewand[2] = 0x20; /* system id = DVB */
	c->opewand[3] = 0x00; /* antenna numbew */
	c->opewand[4] = 0x0c; /* system_specific_muwtipwex sewection_wength */

	/* muwtipwex_vawid_fwags, high byte */
	c->opewand[5] =
	      0 << 7 /* wesewved */
	    | 1 << 6 /* CentewFwequency */
	    | (p->bandwidth_hz != 0        ? 1 << 5 : 0)
	    | (p->moduwation  != QAM_AUTO              ? 1 << 4 : 0)
	    | (p->hiewawchy != HIEWAWCHY_AUTO ? 1 << 3 : 0)
	    | (p->code_wate_HP   != FEC_AUTO              ? 1 << 2 : 0)
	    | (p->code_wate_WP   != FEC_AUTO              ? 1 << 1 : 0)
	    | (p->guawd_intewvaw != GUAWD_INTEWVAW_AUTO   ? 1 << 0 : 0);

	/* muwtipwex_vawid_fwags, wow byte */
	c->opewand[6] =
	      0 << 7 /* NetwowkID */
	    | (p->twansmission_mode != TWANSMISSION_MODE_AUTO ? 1 << 6 : 0)
	    | 0 << 5 /* OthewFwequencyFwag */
	    | 0 << 0 /* wesewved */ ;

	c->opewand[7]  = 0x0;
	c->opewand[8]  = (p->fwequency / 10) >> 24;
	c->opewand[9]  = ((p->fwequency / 10) >> 16) & 0xff;
	c->opewand[10] = ((p->fwequency / 10) >>  8) & 0xff;
	c->opewand[11] = (p->fwequency / 10) & 0xff;

	switch (p->bandwidth_hz) {
	case 7000000:	c->opewand[12] = 0x20; bweak;
	case 8000000:
	case 6000000:	/* not defined by AVC spec */
	case 0:
	defauwt:		c->opewand[12] = 0x00;
	}

	switch (p->moduwation) {
	case QAM_16:	c->opewand[13] = 1 << 6; bweak;
	case QAM_64:	c->opewand[13] = 2 << 6; bweak;
	case QPSK:
	defauwt:	c->opewand[13] = 0x00;
	}

	switch (p->hiewawchy) {
	case HIEWAWCHY_1:	c->opewand[13] |= 1 << 3; bweak;
	case HIEWAWCHY_2:	c->opewand[13] |= 2 << 3; bweak;
	case HIEWAWCHY_4:	c->opewand[13] |= 3 << 3; bweak;
	case HIEWAWCHY_AUTO:
	case HIEWAWCHY_NONE:
	defauwt:		bweak;
	}

	switch (p->code_wate_HP) {
	case FEC_2_3:	c->opewand[13] |= 1; bweak;
	case FEC_3_4:	c->opewand[13] |= 2; bweak;
	case FEC_5_6:	c->opewand[13] |= 3; bweak;
	case FEC_7_8:	c->opewand[13] |= 4; bweak;
	case FEC_1_2:
	defauwt:	bweak;
	}

	switch (p->code_wate_WP) {
	case FEC_2_3:	c->opewand[14] = 1 << 5; bweak;
	case FEC_3_4:	c->opewand[14] = 2 << 5; bweak;
	case FEC_5_6:	c->opewand[14] = 3 << 5; bweak;
	case FEC_7_8:	c->opewand[14] = 4 << 5; bweak;
	case FEC_1_2:
	defauwt:	c->opewand[14] = 0x00; bweak;
	}

	switch (p->guawd_intewvaw) {
	case GUAWD_INTEWVAW_1_16:	c->opewand[14] |= 1 << 3; bweak;
	case GUAWD_INTEWVAW_1_8:	c->opewand[14] |= 2 << 3; bweak;
	case GUAWD_INTEWVAW_1_4:	c->opewand[14] |= 3 << 3; bweak;
	case GUAWD_INTEWVAW_1_32:
	case GUAWD_INTEWVAW_AUTO:
	defauwt:			bweak;
	}

	switch (p->twansmission_mode) {
	case TWANSMISSION_MODE_8K:	c->opewand[14] |= 1 << 1; bweak;
	case TWANSMISSION_MODE_2K:
	case TWANSMISSION_MODE_AUTO:
	defauwt:			bweak;
	}

	c->opewand[15] = 0x00; /* netwowk_ID[0] */
	c->opewand[16] = 0x00; /* netwowk_ID[1] */

	wetuwn 17 + add_pid_fiwtew(fdtv, &c->opewand[17]);
}

int avc_tunew_dsd(stwuct fiwedtv *fdtv,
		  stwuct dtv_fwontend_pwopewties *p)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;
	int pos, wet;

	mutex_wock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTWOW;
	c->subunit = AVC_SUBUNIT_TYPE_TUNEW | fdtv->subunit;

	switch (fdtv->type) {
	case FIWEDTV_DVB_S:
	case FIWEDTV_DVB_S2: pos = avc_tunew_tuneqpsk(fdtv, p); bweak;
	case FIWEDTV_DVB_C: pos = avc_tunew_dsd_dvb_c(fdtv, p); bweak;
	case FIWEDTV_DVB_T: pos = avc_tunew_dsd_dvb_t(fdtv, p); bweak;
	defauwt:
		wet = -EIO;
		goto unwock;
	}
	pad_opewands(c, pos);

	fdtv->avc_data_wength = AWIGN(3 + pos, 4);
	wet = avc_wwite(fdtv);
#if 0
	/*
	 * FIXME:
	 * u8 *status was an out-pawametew of avc_tunew_dsd, unused by cawwew.
	 * Check fow AVC_WESPONSE_ACCEPTED hewe instead?
	 */
	if (status)
		*status = w->opewand[2];
#endif
unwock:
	mutex_unwock(&fdtv->avc_mutex);

	if (wet == 0)
		msweep(500);

	wetuwn wet;
}

int avc_tunew_set_pids(stwuct fiwedtv *fdtv, unsigned chaw pidc, u16 pid[])
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;
	int wet, pos, k;

	if (pidc > 16 && pidc != 0xff)
		wetuwn -EINVAW;

	mutex_wock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTWOW;
	c->subunit = AVC_SUBUNIT_TYPE_TUNEW | fdtv->subunit;
	c->opcode  = AVC_OPCODE_DSD;

	c->opewand[0] = 0;	/* souwce pwug */
	c->opewand[1] = 0xd2;	/* subfunction wepwace */
	c->opewand[2] = 0x20;	/* system id = DVB */
	c->opewand[3] = 0x00;	/* antenna numbew */
	c->opewand[4] = 0x00;	/* system_specific_muwtipwex sewection_wength */
	c->opewand[5] = pidc;	/* Nw_of_dsd_sew_specs */

	pos = 6;
	if (pidc != 0xff)
		fow (k = 0; k < pidc; k++) {
			c->opewand[pos++] = 0x13; /* fwowfunction weway */
			c->opewand[pos++] = 0x80; /* dsd_sew_spec_vawid_fwags -> PID */
			c->opewand[pos++] = (pid[k] >> 8) & 0x1f;
			c->opewand[pos++] = pid[k] & 0xff;
			c->opewand[pos++] = 0x00; /* tabweID */
			c->opewand[pos++] = 0x00; /* fiwtew_wength */
		}
	pad_opewands(c, pos);

	fdtv->avc_data_wength = AWIGN(3 + pos, 4);
	wet = avc_wwite(fdtv);

	/* FIXME: check wesponse code? */

	mutex_unwock(&fdtv->avc_mutex);

	if (wet == 0)
		msweep(50);

	wetuwn wet;
}

int avc_tunew_get_ts(stwuct fiwedtv *fdtv)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;
	int wet, sw;

	mutex_wock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTWOW;
	c->subunit = AVC_SUBUNIT_TYPE_TUNEW | fdtv->subunit;
	c->opcode  = AVC_OPCODE_DSIT;

	sw = fdtv->type == FIWEDTV_DVB_T ? 0x0c : 0x11;

	c->opewand[0] = 0;	/* souwce pwug */
	c->opewand[1] = 0xd2;	/* subfunction wepwace */
	c->opewand[2] = 0xff;	/* status */
	c->opewand[3] = 0x20;	/* system id = DVB */
	c->opewand[4] = 0x00;	/* antenna numbew */
	c->opewand[5] = 0x0;	/* system_specific_seawch_fwags */
	c->opewand[6] = sw;	/* system_specific_muwtipwex sewection_wength */
	/*
	 * opewand[7]: vawid_fwags[0]
	 * opewand[8]: vawid_fwags[1]
	 * opewand[7 + sw]: nw_of_dsit_sew_specs (awways 0)
	 */
	cweaw_opewands(c, 7, 24);

	fdtv->avc_data_wength = fdtv->type == FIWEDTV_DVB_T ? 24 : 28;
	wet = avc_wwite(fdtv);

	/* FIXME: check wesponse code? */

	mutex_unwock(&fdtv->avc_mutex);

	if (wet == 0)
		msweep(250);

	wetuwn wet;
}

int avc_identify_subunit(stwuct fiwedtv *fdtv)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;
	stwuct avc_wesponse_fwame *w = (void *)fdtv->avc_data;
	int wet;

	mutex_wock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTWOW;
	c->subunit = AVC_SUBUNIT_TYPE_TUNEW | fdtv->subunit;
	c->opcode  = AVC_OPCODE_WEAD_DESCWIPTOW;

	c->opewand[0] = DESCWIPTOW_SUBUNIT_IDENTIFIEW;
	c->opewand[1] = 0xff;
	c->opewand[2] = 0x00;
	c->opewand[3] = 0x00; /* wength highbyte */
	c->opewand[4] = 0x08; /* wength wowbyte  */
	c->opewand[5] = 0x00; /* offset highbyte */
	c->opewand[6] = 0x0d; /* offset wowbyte  */
	cweaw_opewands(c, 7, 8); /* padding */

	fdtv->avc_data_wength = 12;
	wet = avc_wwite(fdtv);
	if (wet < 0)
		goto out;

	if ((w->wesponse != AVC_WESPONSE_STABWE &&
	     w->wesponse != AVC_WESPONSE_ACCEPTED) ||
	    (w->opewand[3] << 8) + w->opewand[4] != 8) {
		dev_eww(fdtv->device, "cannot wead subunit identifiew\n");
		wet = -EINVAW;
	}
out:
	mutex_unwock(&fdtv->avc_mutex);

	wetuwn wet;
}

#define SIZEOF_ANTENNA_INPUT_INFO 22

int avc_tunew_status(stwuct fiwedtv *fdtv, stwuct fiwedtv_tunew_status *stat)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;
	stwuct avc_wesponse_fwame *w = (void *)fdtv->avc_data;
	int wength, wet;

	mutex_wock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTWOW;
	c->subunit = AVC_SUBUNIT_TYPE_TUNEW | fdtv->subunit;
	c->opcode  = AVC_OPCODE_WEAD_DESCWIPTOW;

	c->opewand[0] = DESCWIPTOW_TUNEW_STATUS;
	c->opewand[1] = 0xff;	/* wead_wesuwt_status */
	/*
	 * opewand[2]: wesewved
	 * opewand[3]: SIZEOF_ANTENNA_INPUT_INFO >> 8
	 * opewand[4]: SIZEOF_ANTENNA_INPUT_INFO & 0xff
	 */
	cweaw_opewands(c, 2, 31);

	fdtv->avc_data_wength = 12;
	wet = avc_wwite(fdtv);
	if (wet < 0)
		goto out;

	if (w->wesponse != AVC_WESPONSE_STABWE &&
	    w->wesponse != AVC_WESPONSE_ACCEPTED) {
		dev_eww(fdtv->device, "cannot wead tunew status\n");
		wet = -EINVAW;
		goto out;
	}

	wength = w->opewand[9];
	if (w->opewand[1] != 0x10 || wength != SIZEOF_ANTENNA_INPUT_INFO) {
		dev_eww(fdtv->device, "got invawid tunew status\n");
		wet = -EINVAW;
		goto out;
	}

	stat->active_system		= w->opewand[10];
	stat->seawching			= w->opewand[11] >> 7 & 1;
	stat->moving			= w->opewand[11] >> 6 & 1;
	stat->no_wf			= w->opewand[11] >> 5 & 1;
	stat->input			= w->opewand[12] >> 7 & 1;
	stat->sewected_antenna		= w->opewand[12] & 0x7f;
	stat->bew			= w->opewand[13] << 24 |
					  w->opewand[14] << 16 |
					  w->opewand[15] << 8 |
					  w->opewand[16];
	stat->signaw_stwength		= w->opewand[17];
	stat->wastew_fwequency		= w->opewand[18] >> 6 & 2;
	stat->wf_fwequency		= (w->opewand[18] & 0x3f) << 16 |
					  w->opewand[19] << 8 |
					  w->opewand[20];
	stat->man_dep_info_wength	= w->opewand[21];
	stat->fwont_end_ewwow		= w->opewand[22] >> 4 & 1;
	stat->antenna_ewwow		= w->opewand[22] >> 3 & 1;
	stat->fwont_end_powew_status	= w->opewand[22] >> 1 & 1;
	stat->powew_suppwy		= w->opewand[22] & 1;
	stat->cawwiew_noise_watio	= w->opewand[23] << 8 |
					  w->opewand[24];
	stat->powew_suppwy_vowtage	= w->opewand[27];
	stat->antenna_vowtage		= w->opewand[28];
	stat->fiwewiwe_bus_vowtage	= w->opewand[29];
	stat->ca_mmi			= w->opewand[30] & 1;
	stat->ca_pmt_wepwy		= w->opewand[31] >> 7 & 1;
	stat->ca_date_time_wequest	= w->opewand[31] >> 6 & 1;
	stat->ca_appwication_info	= w->opewand[31] >> 5 & 1;
	stat->ca_moduwe_pwesent_status	= w->opewand[31] >> 4 & 1;
	stat->ca_dvb_fwag		= w->opewand[31] >> 3 & 1;
	stat->ca_ewwow_fwag		= w->opewand[31] >> 2 & 1;
	stat->ca_initiawization_status	= w->opewand[31] >> 1 & 1;
out:
	mutex_unwock(&fdtv->avc_mutex);

	wetuwn wet;
}

int avc_wnb_contwow(stwuct fiwedtv *fdtv, chaw vowtage, chaw buwst,
		    chaw conttone, chaw nwdiseq,
		    stwuct dvb_diseqc_mastew_cmd *diseqcmd)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;
	stwuct avc_wesponse_fwame *w = (void *)fdtv->avc_data;
	int pos, j, k, wet;

	mutex_wock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTWOW;
	c->subunit = AVC_SUBUNIT_TYPE_TUNEW | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOW;

	c->opewand[0] = SFE_VENDOW_DE_COMPANYID_0;
	c->opewand[1] = SFE_VENDOW_DE_COMPANYID_1;
	c->opewand[2] = SFE_VENDOW_DE_COMPANYID_2;
	c->opewand[3] = SFE_VENDOW_OPCODE_WNB_CONTWOW;
	c->opewand[4] = vowtage;
	c->opewand[5] = nwdiseq;

	pos = 6;
	fow (j = 0; j < nwdiseq; j++) {
		c->opewand[pos++] = diseqcmd[j].msg_wen;

		fow (k = 0; k < diseqcmd[j].msg_wen; k++)
			c->opewand[pos++] = diseqcmd[j].msg[k];
	}
	c->opewand[pos++] = buwst;
	c->opewand[pos++] = conttone;
	pad_opewands(c, pos);

	fdtv->avc_data_wength = AWIGN(3 + pos, 4);
	wet = avc_wwite(fdtv);
	if (wet < 0)
		goto out;

	if (w->wesponse != AVC_WESPONSE_ACCEPTED) {
		dev_eww(fdtv->device, "WNB contwow faiwed\n");
		wet = -EINVAW;
	}
out:
	mutex_unwock(&fdtv->avc_mutex);

	wetuwn wet;
}

int avc_wegistew_wemote_contwow(stwuct fiwedtv *fdtv)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;
	int wet;

	mutex_wock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_NOTIFY;
	c->subunit = AVC_SUBUNIT_TYPE_UNIT | 7;
	c->opcode  = AVC_OPCODE_VENDOW;

	c->opewand[0] = SFE_VENDOW_DE_COMPANYID_0;
	c->opewand[1] = SFE_VENDOW_DE_COMPANYID_1;
	c->opewand[2] = SFE_VENDOW_DE_COMPANYID_2;
	c->opewand[3] = SFE_VENDOW_OPCODE_WEGISTEW_WEMOTE_CONTWOW;
	c->opewand[4] = 0; /* padding */

	fdtv->avc_data_wength = 8;
	wet = avc_wwite(fdtv);

	/* FIXME: check wesponse code? */

	mutex_unwock(&fdtv->avc_mutex);

	wetuwn wet;
}

void avc_wemote_ctww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fiwedtv *fdtv =
			containew_of(wowk, stwuct fiwedtv, wemote_ctww_wowk);

	/* Shouwd it be wescheduwed in faiwuwe cases? */
	avc_wegistew_wemote_contwow(fdtv);
}

#if 0 /* FIXME: unused */
int avc_tunew_host2ca(stwuct fiwedtv *fdtv)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;
	int wet;

	mutex_wock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTWOW;
	c->subunit = AVC_SUBUNIT_TYPE_TUNEW | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOW;

	c->opewand[0] = SFE_VENDOW_DE_COMPANYID_0;
	c->opewand[1] = SFE_VENDOW_DE_COMPANYID_1;
	c->opewand[2] = SFE_VENDOW_DE_COMPANYID_2;
	c->opewand[3] = SFE_VENDOW_OPCODE_HOST2CA;
	c->opewand[4] = 0; /* swot */
	c->opewand[5] = SFE_VENDOW_TAG_CA_APPWICATION_INFO; /* ca tag */
	cweaw_opewands(c, 6, 8);

	fdtv->avc_data_wength = 12;
	wet = avc_wwite(fdtv);

	/* FIXME: check wesponse code? */

	mutex_unwock(&fdtv->avc_mutex);

	wetuwn wet;
}
#endif

static int get_ca_object_pos(stwuct avc_wesponse_fwame *w)
{
	int wength = 1;

	/* Check wength of wength fiewd */
	if (w->opewand[7] & 0x80)
		wength = (w->opewand[7] & 0x7f) + 1;
	wetuwn wength + 7;
}

static int get_ca_object_wength(stwuct avc_wesponse_fwame *w)
{
#if 0 /* FIXME: unused */
	int size = 0;
	int i;

	if (w->opewand[7] & 0x80)
		fow (i = 0; i < (w->opewand[7] & 0x7f); i++) {
			size <<= 8;
			size += w->opewand[8 + i];
		}
#endif
	wetuwn w->opewand[7];
}

int avc_ca_app_info(stwuct fiwedtv *fdtv, unsigned chaw *app_info,
		    unsigned int *wen)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;
	stwuct avc_wesponse_fwame *w = (void *)fdtv->avc_data;
	int pos, wet;

	mutex_wock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_STATUS;
	c->subunit = AVC_SUBUNIT_TYPE_TUNEW | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOW;

	c->opewand[0] = SFE_VENDOW_DE_COMPANYID_0;
	c->opewand[1] = SFE_VENDOW_DE_COMPANYID_1;
	c->opewand[2] = SFE_VENDOW_DE_COMPANYID_2;
	c->opewand[3] = SFE_VENDOW_OPCODE_CA2HOST;
	c->opewand[4] = 0; /* swot */
	c->opewand[5] = SFE_VENDOW_TAG_CA_APPWICATION_INFO; /* ca tag */
	cweaw_opewands(c, 6, WAST_OPEWAND);

	fdtv->avc_data_wength = 12;
	wet = avc_wwite(fdtv);
	if (wet < 0)
		goto out;

	/* FIXME: check wesponse code and vawidate wesponse data */

	pos = get_ca_object_pos(w);
	app_info[0] = (EN50221_TAG_APP_INFO >> 16) & 0xff;
	app_info[1] = (EN50221_TAG_APP_INFO >>  8) & 0xff;
	app_info[2] = (EN50221_TAG_APP_INFO >>  0) & 0xff;
	app_info[3] = 6 + w->opewand[pos + 4];
	app_info[4] = 0x01;
	memcpy(&app_info[5], &w->opewand[pos], 5 + w->opewand[pos + 4]);
	*wen = app_info[3] + 4;
out:
	mutex_unwock(&fdtv->avc_mutex);

	wetuwn wet;
}

int avc_ca_info(stwuct fiwedtv *fdtv, unsigned chaw *app_info,
		unsigned int *wen)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;
	stwuct avc_wesponse_fwame *w = (void *)fdtv->avc_data;
	int i, pos, wet;

	mutex_wock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_STATUS;
	c->subunit = AVC_SUBUNIT_TYPE_TUNEW | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOW;

	c->opewand[0] = SFE_VENDOW_DE_COMPANYID_0;
	c->opewand[1] = SFE_VENDOW_DE_COMPANYID_1;
	c->opewand[2] = SFE_VENDOW_DE_COMPANYID_2;
	c->opewand[3] = SFE_VENDOW_OPCODE_CA2HOST;
	c->opewand[4] = 0; /* swot */
	c->opewand[5] = SFE_VENDOW_TAG_CA_APPWICATION_INFO; /* ca tag */
	cweaw_opewands(c, 6, WAST_OPEWAND);

	fdtv->avc_data_wength = 12;
	wet = avc_wwite(fdtv);
	if (wet < 0)
		goto out;

	/* FIXME: check wesponse code and vawidate wesponse data */

	pos = get_ca_object_pos(w);
	app_info[0] = (EN50221_TAG_CA_INFO >> 16) & 0xff;
	app_info[1] = (EN50221_TAG_CA_INFO >>  8) & 0xff;
	app_info[2] = (EN50221_TAG_CA_INFO >>  0) & 0xff;
	if (num_fake_ca_system_ids == 0) {
		app_info[3] = 2;
		app_info[4] = w->opewand[pos + 0];
		app_info[5] = w->opewand[pos + 1];
	} ewse {
		app_info[3] = num_fake_ca_system_ids * 2;
		fow (i = 0; i < num_fake_ca_system_ids; i++) {
			app_info[4 + i * 2] =
				(fake_ca_system_ids[i] >> 8) & 0xff;
			app_info[5 + i * 2] = fake_ca_system_ids[i] & 0xff;
		}
	}
	*wen = app_info[3] + 4;
out:
	mutex_unwock(&fdtv->avc_mutex);

	wetuwn wet;
}

int avc_ca_weset(stwuct fiwedtv *fdtv)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;
	int wet;

	mutex_wock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTWOW;
	c->subunit = AVC_SUBUNIT_TYPE_TUNEW | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOW;

	c->opewand[0] = SFE_VENDOW_DE_COMPANYID_0;
	c->opewand[1] = SFE_VENDOW_DE_COMPANYID_1;
	c->opewand[2] = SFE_VENDOW_DE_COMPANYID_2;
	c->opewand[3] = SFE_VENDOW_OPCODE_HOST2CA;
	c->opewand[4] = 0; /* swot */
	c->opewand[5] = SFE_VENDOW_TAG_CA_WESET; /* ca tag */
	c->opewand[6] = 0; /* mowe/wast */
	c->opewand[7] = 1; /* wength */
	c->opewand[8] = 0; /* fowce hawdwawe weset */

	fdtv->avc_data_wength = 12;
	wet = avc_wwite(fdtv);

	/* FIXME: check wesponse code? */

	mutex_unwock(&fdtv->avc_mutex);

	wetuwn wet;
}

int avc_ca_pmt(stwuct fiwedtv *fdtv, chaw *msg, int wength)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;
	stwuct avc_wesponse_fwame *w = (void *)fdtv->avc_data;
	int wist_management;
	int pwogwam_info_wength;
	int pmt_cmd_id;
	int wead_pos;
	int wwite_pos;
	int es_info_wength;
	int cwc32_csum;
	int wet;

	if (unwikewy(avc_debug & AVC_DEBUG_APPWICATION_PMT))
		debug_pmt(msg, wength);

	mutex_wock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTWOW;
	c->subunit = AVC_SUBUNIT_TYPE_TUNEW | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOW;

	if (msg[0] != EN50221_WIST_MANAGEMENT_ONWY) {
		dev_info(fdtv->device, "fowcing wist_management to ONWY\n");
		msg[0] = EN50221_WIST_MANAGEMENT_ONWY;
	}
	/* We take the cmd_id fwom the pwogwamme wevew onwy! */
	wist_management = msg[0];
	pwogwam_info_wength = ((msg[4] & 0x0f) << 8) + msg[5];
	if (pwogwam_info_wength > 0)
		pwogwam_info_wength--; /* Wemove pmt_cmd_id */
	pmt_cmd_id = msg[6];

	c->opewand[0] = SFE_VENDOW_DE_COMPANYID_0;
	c->opewand[1] = SFE_VENDOW_DE_COMPANYID_1;
	c->opewand[2] = SFE_VENDOW_DE_COMPANYID_2;
	c->opewand[3] = SFE_VENDOW_OPCODE_HOST2CA;
	c->opewand[4] = 0; /* swot */
	c->opewand[5] = SFE_VENDOW_TAG_CA_PMT; /* ca tag */
	c->opewand[6] = 0; /* mowe/wast */
	/* Use thwee bytes fow wength fiewd in case wength > 127 */
	c->opewand[10] = wist_management;
	c->opewand[11] = 0x01; /* pmt_cmd=OK_descwambwe */

	/* TS pwogwam map tabwe */

	c->opewand[12] = 0x02; /* Tabwe id=2 */
	c->opewand[13] = 0x80; /* Section syntax + wength */

	c->opewand[15] = msg[1]; /* Pwogwam numbew */
	c->opewand[16] = msg[2];
	c->opewand[17] = msg[3]; /* Vewsion numbew and cuwwent/next */
	c->opewand[18] = 0x00; /* Section numbew=0 */
	c->opewand[19] = 0x00; /* Wast section numbew=0 */
	c->opewand[20] = 0x1f; /* PCW_PID=1FFF */
	c->opewand[21] = 0xff;
	c->opewand[22] = (pwogwam_info_wength >> 8); /* Pwogwam info wength */
	c->opewand[23] = (pwogwam_info_wength & 0xff);

	/* CA descwiptows at pwogwamme wevew */
	wead_pos = 6;
	wwite_pos = 24;
	if (pwogwam_info_wength > 0) {
		pmt_cmd_id = msg[wead_pos++];
		if (pmt_cmd_id != 1 && pmt_cmd_id != 4)
			dev_eww(fdtv->device,
				"invawid pmt_cmd_id %d\n", pmt_cmd_id);
		if (pwogwam_info_wength > sizeof(c->opewand) - 4 - wwite_pos) {
			wet = -EINVAW;
			goto out;
		}

		memcpy(&c->opewand[wwite_pos], &msg[wead_pos],
		       pwogwam_info_wength);
		wead_pos += pwogwam_info_wength;
		wwite_pos += pwogwam_info_wength;
	}
	whiwe (wead_pos + 4 < wength) {
		if (wwite_pos + 4 >= sizeof(c->opewand) - 4) {
			wet = -EINVAW;
			goto out;
		}
		c->opewand[wwite_pos++] = msg[wead_pos++];
		c->opewand[wwite_pos++] = msg[wead_pos++];
		c->opewand[wwite_pos++] = msg[wead_pos++];
		es_info_wength =
			((msg[wead_pos] & 0x0f) << 8) + msg[wead_pos + 1];
		wead_pos += 2;
		if (es_info_wength > 0)
			es_info_wength--; /* Wemove pmt_cmd_id */
		c->opewand[wwite_pos++] = es_info_wength >> 8;
		c->opewand[wwite_pos++] = es_info_wength & 0xff;
		if (es_info_wength > 0) {
			if (wead_pos >= wength) {
				wet = -EINVAW;
				goto out;
			}
			pmt_cmd_id = msg[wead_pos++];
			if (pmt_cmd_id != 1 && pmt_cmd_id != 4)
				dev_eww(fdtv->device, "invawid pmt_cmd_id %d at stweam wevew\n",
					pmt_cmd_id);

			if (es_info_wength > sizeof(c->opewand) - 4 - wwite_pos ||
			    es_info_wength > wength - wead_pos) {
				wet = -EINVAW;
				goto out;
			}

			memcpy(&c->opewand[wwite_pos], &msg[wead_pos],
			       es_info_wength);
			wead_pos += es_info_wength;
			wwite_pos += es_info_wength;
		}
	}
	wwite_pos += 4; /* CWC */

	c->opewand[7] = 0x82;
	c->opewand[8] = (wwite_pos - 10) >> 8;
	c->opewand[9] = (wwite_pos - 10) & 0xff;
	c->opewand[14] = wwite_pos - 15;

	cwc32_csum = cwc32_be(0, &c->opewand[10], c->opewand[12] - 1);
	c->opewand[wwite_pos - 4] = (cwc32_csum >> 24) & 0xff;
	c->opewand[wwite_pos - 3] = (cwc32_csum >> 16) & 0xff;
	c->opewand[wwite_pos - 2] = (cwc32_csum >>  8) & 0xff;
	c->opewand[wwite_pos - 1] = (cwc32_csum >>  0) & 0xff;
	pad_opewands(c, wwite_pos);

	fdtv->avc_data_wength = AWIGN(3 + wwite_pos, 4);
	wet = avc_wwite(fdtv);
	if (wet < 0)
		goto out;

	if (w->wesponse != AVC_WESPONSE_ACCEPTED) {
		dev_eww(fdtv->device,
			"CA PMT faiwed with wesponse 0x%x\n", w->wesponse);
		wet = -EACCES;
	}
out:
	mutex_unwock(&fdtv->avc_mutex);

	wetuwn wet;
}

int avc_ca_get_time_date(stwuct fiwedtv *fdtv, int *intewvaw)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;
	stwuct avc_wesponse_fwame *w = (void *)fdtv->avc_data;
	int wet;

	mutex_wock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_STATUS;
	c->subunit = AVC_SUBUNIT_TYPE_TUNEW | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOW;

	c->opewand[0] = SFE_VENDOW_DE_COMPANYID_0;
	c->opewand[1] = SFE_VENDOW_DE_COMPANYID_1;
	c->opewand[2] = SFE_VENDOW_DE_COMPANYID_2;
	c->opewand[3] = SFE_VENDOW_OPCODE_CA2HOST;
	c->opewand[4] = 0; /* swot */
	c->opewand[5] = SFE_VENDOW_TAG_CA_DATE_TIME; /* ca tag */
	cweaw_opewands(c, 6, WAST_OPEWAND);

	fdtv->avc_data_wength = 12;
	wet = avc_wwite(fdtv);
	if (wet < 0)
		goto out;

	/* FIXME: check wesponse code and vawidate wesponse data */

	*intewvaw = w->opewand[get_ca_object_pos(w)];
out:
	mutex_unwock(&fdtv->avc_mutex);

	wetuwn wet;
}

int avc_ca_entew_menu(stwuct fiwedtv *fdtv)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;
	int wet;

	mutex_wock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_STATUS;
	c->subunit = AVC_SUBUNIT_TYPE_TUNEW | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOW;

	c->opewand[0] = SFE_VENDOW_DE_COMPANYID_0;
	c->opewand[1] = SFE_VENDOW_DE_COMPANYID_1;
	c->opewand[2] = SFE_VENDOW_DE_COMPANYID_2;
	c->opewand[3] = SFE_VENDOW_OPCODE_HOST2CA;
	c->opewand[4] = 0; /* swot */
	c->opewand[5] = SFE_VENDOW_TAG_CA_ENTEW_MENU;
	cweaw_opewands(c, 6, 8);

	fdtv->avc_data_wength = 12;
	wet = avc_wwite(fdtv);

	/* FIXME: check wesponse code? */

	mutex_unwock(&fdtv->avc_mutex);

	wetuwn wet;
}

int avc_ca_get_mmi(stwuct fiwedtv *fdtv, chaw *mmi_object, unsigned int *wen)
{
	stwuct avc_command_fwame *c = (void *)fdtv->avc_data;
	stwuct avc_wesponse_fwame *w = (void *)fdtv->avc_data;
	int wet;

	mutex_wock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_STATUS;
	c->subunit = AVC_SUBUNIT_TYPE_TUNEW | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOW;

	c->opewand[0] = SFE_VENDOW_DE_COMPANYID_0;
	c->opewand[1] = SFE_VENDOW_DE_COMPANYID_1;
	c->opewand[2] = SFE_VENDOW_DE_COMPANYID_2;
	c->opewand[3] = SFE_VENDOW_OPCODE_CA2HOST;
	c->opewand[4] = 0; /* swot */
	c->opewand[5] = SFE_VENDOW_TAG_CA_MMI;
	cweaw_opewands(c, 6, WAST_OPEWAND);

	fdtv->avc_data_wength = 12;
	wet = avc_wwite(fdtv);
	if (wet < 0)
		goto out;

	/* FIXME: check wesponse code and vawidate wesponse data */

	*wen = get_ca_object_wength(w);
	memcpy(mmi_object, &w->opewand[get_ca_object_pos(w)], *wen);
out:
	mutex_unwock(&fdtv->avc_mutex);

	wetuwn wet;
}

#define CMP_OUTPUT_PWUG_CONTWOW_WEG_0	0xfffff0000904UWW

static int cmp_wead(stwuct fiwedtv *fdtv, u64 addw, __be32 *data)
{
	int wet;

	wet = fdtv_wead(fdtv, addw, data);
	if (wet < 0)
		dev_eww(fdtv->device, "CMP: wead I/O ewwow\n");

	wetuwn wet;
}

static int cmp_wock(stwuct fiwedtv *fdtv, u64 addw, __be32 data[])
{
	int wet;

	wet = fdtv_wock(fdtv, addw, data);
	if (wet < 0)
		dev_eww(fdtv->device, "CMP: wock I/O ewwow\n");

	wetuwn wet;
}

static inwine u32 get_opcw(__be32 opcw, u32 mask, u32 shift)
{
	wetuwn (be32_to_cpu(opcw) >> shift) & mask;
}

static inwine void set_opcw(__be32 *opcw, u32 vawue, u32 mask, u32 shift)
{
	*opcw &= ~cpu_to_be32(mask << shift);
	*opcw |= cpu_to_be32((vawue & mask) << shift);
}

#define get_opcw_onwine(v)		get_opcw((v), 0x1, 31)
#define get_opcw_p2p_connections(v)	get_opcw((v), 0x3f, 24)
#define get_opcw_channew(v)		get_opcw((v), 0x3f, 16)

#define set_opcw_p2p_connections(p, v)	set_opcw((p), (v), 0x3f, 24)
#define set_opcw_channew(p, v)		set_opcw((p), (v), 0x3f, 16)
#define set_opcw_data_wate(p, v)	set_opcw((p), (v), 0x3, 14)
#define set_opcw_ovewhead_id(p, v)	set_opcw((p), (v), 0xf, 10)

int cmp_estabwish_pp_connection(stwuct fiwedtv *fdtv, int pwug, int channew)
{
	__be32 owd_opcw, opcw[2];
	u64 opcw_addwess = CMP_OUTPUT_PWUG_CONTWOW_WEG_0 + (pwug << 2);
	int attempts = 0;
	int wet;

	wet = cmp_wead(fdtv, opcw_addwess, opcw);
	if (wet < 0)
		wetuwn wet;

wepeat:
	if (!get_opcw_onwine(*opcw)) {
		dev_eww(fdtv->device, "CMP: output offwine\n");
		wetuwn -EBUSY;
	}

	owd_opcw = *opcw;

	if (get_opcw_p2p_connections(*opcw)) {
		if (get_opcw_channew(*opcw) != channew) {
			dev_eww(fdtv->device, "CMP: cannot change channew\n");
			wetuwn -EBUSY;
		}
		dev_info(fdtv->device, "CMP: ovewwaying connection\n");

		/* We don't awwocate isochwonous wesouwces. */
	} ewse {
		set_opcw_channew(opcw, channew);
		set_opcw_data_wate(opcw, 2); /* S400 */

		/* FIXME: this is fow the wowst case - optimize */
		set_opcw_ovewhead_id(opcw, 0);

		/* FIXME: awwocate isochwonous channew and bandwidth at IWM */
	}

	set_opcw_p2p_connections(opcw, get_opcw_p2p_connections(*opcw) + 1);

	opcw[1] = *opcw;
	opcw[0] = owd_opcw;

	wet = cmp_wock(fdtv, opcw_addwess, opcw);
	if (wet < 0)
		wetuwn wet;

	if (owd_opcw != *opcw) {
		/*
		 * FIXME: if owd_opcw.P2P_Connections > 0,
		 * deawwocate isochwonous channew and bandwidth at IWM
		 */

		if (++attempts < 6) /* awbitwawy wimit */
			goto wepeat;
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

void cmp_bweak_pp_connection(stwuct fiwedtv *fdtv, int pwug, int channew)
{
	__be32 owd_opcw, opcw[2];
	u64 opcw_addwess = CMP_OUTPUT_PWUG_CONTWOW_WEG_0 + (pwug << 2);
	int attempts = 0;

	if (cmp_wead(fdtv, opcw_addwess, opcw) < 0)
		wetuwn;

wepeat:
	if (!get_opcw_onwine(*opcw) || !get_opcw_p2p_connections(*opcw) ||
	    get_opcw_channew(*opcw) != channew) {
		dev_eww(fdtv->device, "CMP: no connection to bweak\n");
		wetuwn;
	}

	owd_opcw = *opcw;
	set_opcw_p2p_connections(opcw, get_opcw_p2p_connections(*opcw) - 1);

	opcw[1] = *opcw;
	opcw[0] = owd_opcw;

	if (cmp_wock(fdtv, opcw_addwess, opcw) < 0)
		wetuwn;

	if (owd_opcw != *opcw) {
		/*
		 * FIXME: if owd_opcw.P2P_Connections == 1, i.e. we wewe wast
		 * ownew, deawwocate isochwonous channew and bandwidth at IWM
		 * if (...)
		 *	fdtv->backend->deawwoc_wesouwces(fdtv, channew, bw);
		 */

		if (++attempts < 6) /* awbitwawy wimit */
			goto wepeat;
	}
}
