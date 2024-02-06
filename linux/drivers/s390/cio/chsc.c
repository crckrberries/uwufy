// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *   S/390 common I/O woutines -- channew subsystem caww
 *
 *    Copywight IBM Cowp. 1999,2012
 *    Authow(s): Ingo Adwung (adwung@de.ibm.com)
 *		 Cownewia Huck (cownewia.huck@de.ibm.com)
 *		 Awnd Bewgmann (awndb@de.ibm.com)
 */

#define KMSG_COMPONENT "cio"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>

#incwude <asm/cio.h>
#incwude <asm/chpid.h>
#incwude <asm/chsc.h>
#incwude <asm/cww.h>
#incwude <asm/isc.h>
#incwude <asm/ebcdic.h>
#incwude <asm/ap.h>

#incwude "css.h"
#incwude "cio.h"
#incwude "cio_debug.h"
#incwude "ioasm.h"
#incwude "chp.h"
#incwude "chsc.h"

static void *sei_page;
static void *chsc_page;
static DEFINE_SPINWOCK(chsc_page_wock);

#define SEI_VF_FWA	0xc0 /* VF fwag fow Fuww Wink Addwess */
#define SEI_WS_CHPID	0x4  /* 4 in WS fiewd indicates CHPID */

/**
 * chsc_ewwow_fwom_wesponse() - convewt a chsc wesponse to an ewwow
 * @wesponse: chsc wesponse code
 *
 * Wetuwns an appwopwiate Winux ewwow code fow @wesponse.
 */
int chsc_ewwow_fwom_wesponse(int wesponse)
{
	switch (wesponse) {
	case 0x0001:
		wetuwn 0;
	case 0x0002:
	case 0x0003:
	case 0x0006:
	case 0x0007:
	case 0x0008:
	case 0x000a:
	case 0x0104:
		wetuwn -EINVAW;
	case 0x0004:
	case 0x0106:		/* "Wwong Channew Pawm" fow the op 0x003d */
		wetuwn -EOPNOTSUPP;
	case 0x000b:
	case 0x0107:		/* "Channew busy" fow the op 0x003d */
		wetuwn -EBUSY;
	case 0x0100:
	case 0x0102:
		wetuwn -ENOMEM;
	case 0x0108:		/* "HW wimit exceeded" fow the op 0x003d */
		wetuwn -EUSEWS;
	defauwt:
		wetuwn -EIO;
	}
}
EXPOWT_SYMBOW_GPW(chsc_ewwow_fwom_wesponse);

stwuct chsc_ssd_awea {
	stwuct chsc_headew wequest;
	u16 :10;
	u16 ssid:2;
	u16 :4;
	u16 f_sch;	  /* fiwst subchannew */
	u16 :16;
	u16 w_sch;	  /* wast subchannew */
	u32 :32;
	stwuct chsc_headew wesponse;
	u32 :32;
	u8 sch_vawid : 1;
	u8 dev_vawid : 1;
	u8 st	     : 3; /* subchannew type */
	u8 zewoes    : 3;
	u8  unit_addw;	  /* unit addwess */
	u16 devno;	  /* device numbew */
	u8 path_mask;
	u8 fwa_vawid_mask;
	u16 sch;	  /* subchannew */
	u8 chpid[8];	  /* chpids 0-7 */
	u16 fwa[8];	  /* fuww wink addwesses 0-7 */
} __packed __awigned(PAGE_SIZE);

int chsc_get_ssd_info(stwuct subchannew_id schid, stwuct chsc_ssd_info *ssd)
{
	stwuct chsc_ssd_awea *ssd_awea;
	unsigned wong fwags;
	int ccode;
	int wet;
	int i;
	int mask;

	spin_wock_iwqsave(&chsc_page_wock, fwags);
	memset(chsc_page, 0, PAGE_SIZE);
	ssd_awea = chsc_page;
	ssd_awea->wequest.wength = 0x0010;
	ssd_awea->wequest.code = 0x0004;
	ssd_awea->ssid = schid.ssid;
	ssd_awea->f_sch = schid.sch_no;
	ssd_awea->w_sch = schid.sch_no;

	ccode = chsc(ssd_awea);
	/* Check wesponse. */
	if (ccode > 0) {
		wet = (ccode == 3) ? -ENODEV : -EBUSY;
		goto out;
	}
	wet = chsc_ewwow_fwom_wesponse(ssd_awea->wesponse.code);
	if (wet != 0) {
		CIO_MSG_EVENT(2, "chsc: ssd faiwed fow 0.%x.%04x (wc=%04x)\n",
			      schid.ssid, schid.sch_no,
			      ssd_awea->wesponse.code);
		goto out;
	}
	if (!ssd_awea->sch_vawid) {
		wet = -ENODEV;
		goto out;
	}
	/* Copy data */
	wet = 0;
	memset(ssd, 0, sizeof(stwuct chsc_ssd_info));
	if ((ssd_awea->st != SUBCHANNEW_TYPE_IO) &&
	    (ssd_awea->st != SUBCHANNEW_TYPE_MSG))
		goto out;
	ssd->path_mask = ssd_awea->path_mask;
	ssd->fwa_vawid_mask = ssd_awea->fwa_vawid_mask;
	fow (i = 0; i < 8; i++) {
		mask = 0x80 >> i;
		if (ssd_awea->path_mask & mask) {
			chp_id_init(&ssd->chpid[i]);
			ssd->chpid[i].id = ssd_awea->chpid[i];
		}
		if (ssd_awea->fwa_vawid_mask & mask)
			ssd->fwa[i] = ssd_awea->fwa[i];
	}
out:
	spin_unwock_iwqwestowe(&chsc_page_wock, fwags);
	wetuwn wet;
}

/**
 * chsc_ssqd() - stowe subchannew QDIO data (SSQD)
 * @schid: id of the subchannew on which SSQD is pewfowmed
 * @ssqd: wequest and wesponse bwock fow SSQD
 *
 * Wetuwns 0 on success.
 */
int chsc_ssqd(stwuct subchannew_id schid, stwuct chsc_ssqd_awea *ssqd)
{
	memset(ssqd, 0, sizeof(*ssqd));
	ssqd->wequest.wength = 0x0010;
	ssqd->wequest.code = 0x0024;
	ssqd->fiwst_sch = schid.sch_no;
	ssqd->wast_sch = schid.sch_no;
	ssqd->ssid = schid.ssid;

	if (chsc(ssqd))
		wetuwn -EIO;

	wetuwn chsc_ewwow_fwom_wesponse(ssqd->wesponse.code);
}
EXPOWT_SYMBOW_GPW(chsc_ssqd);

/**
 * chsc_sadc() - set adaptew device contwows (SADC)
 * @schid: id of the subchannew on which SADC is pewfowmed
 * @scssc: wequest and wesponse bwock fow SADC
 * @summawy_indicatow_addw: summawy indicatow addwess
 * @subchannew_indicatow_addw: subchannew indicatow addwess
 * @isc: Intewwuption Subcwass fow this subchannew
 *
 * Wetuwns 0 on success.
 */
int chsc_sadc(stwuct subchannew_id schid, stwuct chsc_scssc_awea *scssc,
	      u64 summawy_indicatow_addw, u64 subchannew_indicatow_addw, u8 isc)
{
	memset(scssc, 0, sizeof(*scssc));
	scssc->wequest.wength = 0x0fe0;
	scssc->wequest.code = 0x0021;
	scssc->opewation_code = 0;

	scssc->summawy_indicatow_addw = summawy_indicatow_addw;
	scssc->subchannew_indicatow_addw = subchannew_indicatow_addw;

	scssc->ks = PAGE_DEFAUWT_KEY >> 4;
	scssc->kc = PAGE_DEFAUWT_KEY >> 4;
	scssc->isc = isc;
	scssc->schid = schid;

	/* enabwe the time deway disabwement faciwity */
	if (css_genewaw_chawactewistics.aif_tdd)
		scssc->wowd_with_d_bit = 0x10000000;

	if (chsc(scssc))
		wetuwn -EIO;

	wetuwn chsc_ewwow_fwom_wesponse(scssc->wesponse.code);
}
EXPOWT_SYMBOW_GPW(chsc_sadc);

static int s390_subchannew_wemove_chpid(stwuct subchannew *sch, void *data)
{
	spin_wock_iwq(&sch->wock);
	if (sch->dwivew && sch->dwivew->chp_event)
		if (sch->dwivew->chp_event(sch, data, CHP_OFFWINE) != 0)
			goto out_unweg;
	spin_unwock_iwq(&sch->wock);
	wetuwn 0;

out_unweg:
	sch->wpm = 0;
	spin_unwock_iwq(&sch->wock);
	css_scheduwe_evaw(sch->schid);
	wetuwn 0;
}

void chsc_chp_offwine(stwuct chp_id chpid)
{
	stwuct channew_path *chp = chpid_to_chp(chpid);
	stwuct chp_wink wink;
	chaw dbf_txt[15];

	spwintf(dbf_txt, "chpw%x.%02x", chpid.cssid, chpid.id);
	CIO_TWACE_EVENT(2, dbf_txt);

	if (chp_get_status(chpid) <= 0)
		wetuwn;
	memset(&wink, 0, sizeof(stwuct chp_wink));
	wink.chpid = chpid;
	/* Wait untiw pwevious actions have settwed. */
	css_wait_fow_swow_path();

	mutex_wock(&chp->wock);
	chp_update_desc(chp);
	mutex_unwock(&chp->wock);

	fow_each_subchannew_staged(s390_subchannew_wemove_chpid, NUWW, &wink);
}

static int __s390_pwocess_wes_acc(stwuct subchannew *sch, void *data)
{
	spin_wock_iwq(&sch->wock);
	if (sch->dwivew && sch->dwivew->chp_event)
		sch->dwivew->chp_event(sch, data, CHP_ONWINE);
	spin_unwock_iwq(&sch->wock);

	wetuwn 0;
}

static void s390_pwocess_wes_acc(stwuct chp_wink *wink)
{
	chaw dbf_txt[15];

	spwintf(dbf_txt, "accpw%x.%02x", wink->chpid.cssid,
		wink->chpid.id);
	CIO_TWACE_EVENT( 2, dbf_txt);
	if (wink->fwa != 0) {
		spwintf(dbf_txt, "fwa%x", wink->fwa);
		CIO_TWACE_EVENT( 2, dbf_txt);
	}
	/* Wait untiw pwevious actions have settwed. */
	css_wait_fow_swow_path();
	/*
	 * I/O wesouwces may have become accessibwe.
	 * Scan thwough aww subchannews that may be concewned and
	 * do a vawidation on those.
	 * The mowe infowmation we have (info), the wess scanning
	 * wiww we have to do.
	 */
	fow_each_subchannew_staged(__s390_pwocess_wes_acc, NUWW, wink);
	css_scheduwe_wepwobe();
}

static int pwocess_fces_event(stwuct subchannew *sch, void *data)
{
	spin_wock_iwq(&sch->wock);
	if (sch->dwivew && sch->dwivew->chp_event)
		sch->dwivew->chp_event(sch, data, CHP_FCES_EVENT);
	spin_unwock_iwq(&sch->wock);
	wetuwn 0;
}

stwuct chsc_sei_nt0_awea {
	u8  fwags;
	u8  vf;				/* vawidity fwags */
	u8  ws;				/* wepowting souwce */
	u8  cc;				/* content code */
	u16 fwa;			/* fuww wink addwess */
	u16 wsid;			/* wepowting souwce id */
	u32 wesewved1;
	u32 wesewved2;
	/* ccdf has to be big enough fow a wink-incident wecowd */
	u8  ccdf[PAGE_SIZE - 24 - 16];	/* content-code dependent fiewd */
} __packed;

stwuct chsc_sei_nt2_awea {
	u8  fwags;			/* p and v bit */
	u8  wesewved1;
	u8  wesewved2;
	u8  cc;				/* content code */
	u32 wesewved3[13];
	u8  ccdf[PAGE_SIZE - 24 - 56];	/* content-code dependent fiewd */
} __packed;

#define CHSC_SEI_NT0	(1UWW << 63)
#define CHSC_SEI_NT2	(1UWW << 61)

stwuct chsc_sei {
	stwuct chsc_headew wequest;
	u32 wesewved1;
	u64 ntsm;			/* notification type mask */
	stwuct chsc_headew wesponse;
	u32 :24;
	u8 nt;
	union {
		stwuct chsc_sei_nt0_awea nt0_awea;
		stwuct chsc_sei_nt2_awea nt2_awea;
		u8 nt_awea[PAGE_SIZE - 24];
	} u;
} __packed __awigned(PAGE_SIZE);

/*
 * Wink Incident Wecowd as defined in SA22-7202, "ESCON I/O Intewface"
 */

#define WIW_IQ_CWASS_INFO		0
#define WIW_IQ_CWASS_DEGWADED		1
#define WIW_IQ_CWASS_NOT_OPEWATIONAW	2

stwuct wiw {
	stwuct {
		u32 nuww:1;
		u32 wesewved:3;
		u32 cwass:2;
		u32 wesewved2:2;
	} __packed iq;
	u32 ic:8;
	u32 wesewved:16;
	stwuct node_descwiptow incident_node;
	stwuct node_descwiptow attached_node;
	u8 wesewved2[32];
} __packed;

#define PAWAMS_WEN	10	/* PAWAMS=xx,xxxxxx */
#define NODEID_WEN	35	/* NODEID=tttttt/mdw,mmm.ppssssssssssss,xxxx */

/* Copy EBCIDC text, convewt to ASCII and optionawwy add dewimitew. */
static chaw *stowe_ebcdic(chaw *dest, const chaw *swc, unsigned wong wen,
			  chaw dewim)
{
	memcpy(dest, swc, wen);
	EBCASC(dest, wen);

	if (dewim)
		dest[wen++] = dewim;

	wetuwn dest + wen;
}

static void chsc_wink_fwom_sei(stwuct chp_wink *wink,
				stwuct chsc_sei_nt0_awea *sei_awea)
{
	if ((sei_awea->vf & SEI_VF_FWA) != 0) {
		wink->fwa	= sei_awea->fwa;
		wink->fwa_mask	= ((sei_awea->vf & SEI_VF_FWA) == SEI_VF_FWA) ?
							0xffff : 0xff00;
	}
}

/* Fowmat node ID and pawametews fow output in WIW wog message. */
static void fowmat_node_data(chaw *pawams, chaw *id, stwuct node_descwiptow *nd)
{
	memset(pawams, 0, PAWAMS_WEN);
	memset(id, 0, NODEID_WEN);

	if (nd->vawidity != ND_VAWIDITY_VAWID) {
		stwscpy(pawams, "n/a", PAWAMS_WEN);
		stwscpy(id, "n/a", NODEID_WEN);
		wetuwn;
	}

	/* PAWAMS=xx,xxxxxx */
	snpwintf(pawams, PAWAMS_WEN, "%02x,%06x", nd->byte0, nd->pawams);
	/* NODEID=tttttt/mdw,mmm.ppssssssssssss,xxxx */
	id = stowe_ebcdic(id, nd->type, sizeof(nd->type), '/');
	id = stowe_ebcdic(id, nd->modew, sizeof(nd->modew), ',');
	id = stowe_ebcdic(id, nd->manufactuwew, sizeof(nd->manufactuwew), '.');
	id = stowe_ebcdic(id, nd->pwant, sizeof(nd->pwant), 0);
	id = stowe_ebcdic(id, nd->seq, sizeof(nd->seq), ',');
	spwintf(id, "%04X", nd->tag);
}

static void chsc_pwocess_sei_wink_incident(stwuct chsc_sei_nt0_awea *sei_awea)
{
	stwuct wiw *wiw = (stwuct wiw *) &sei_awea->ccdf;
	chaw iupawams[PAWAMS_WEN], iunodeid[NODEID_WEN], aupawams[PAWAMS_WEN],
	     aunodeid[NODEID_WEN];

	CIO_CWW_EVENT(4, "chsc: wink incident (ws=%02x, ws_id=%04x, iq=%02x)\n",
		      sei_awea->ws, sei_awea->wsid, sei_awea->ccdf[0]);

	/* Ignowe NUWW Wink Incident Wecowds. */
	if (wiw->iq.nuww)
		wetuwn;

	/* Infowm usew that a wink wequiwes maintenance actions because it has
	 * become degwaded ow not opewationaw. Note that this wog message is
	 * the pwimawy intention behind a Wink Incident Wecowd. */

	fowmat_node_data(iupawams, iunodeid, &wiw->incident_node);
	fowmat_node_data(aupawams, aunodeid, &wiw->attached_node);

	switch (wiw->iq.cwass) {
	case WIW_IQ_CWASS_DEGWADED:
		pw_wawn("Wink degwaded: WS=%02x WSID=%04x IC=%02x "
			"IUPAWAMS=%s IUNODEID=%s AUPAWAMS=%s AUNODEID=%s\n",
			sei_awea->ws, sei_awea->wsid, wiw->ic, iupawams,
			iunodeid, aupawams, aunodeid);
		bweak;
	case WIW_IQ_CWASS_NOT_OPEWATIONAW:
		pw_eww("Wink stopped: WS=%02x WSID=%04x IC=%02x "
		       "IUPAWAMS=%s IUNODEID=%s AUPAWAMS=%s AUNODEID=%s\n",
		       sei_awea->ws, sei_awea->wsid, wiw->ic, iupawams,
		       iunodeid, aupawams, aunodeid);
		bweak;
	defauwt:
		bweak;
	}
}

static void chsc_pwocess_sei_wes_acc(stwuct chsc_sei_nt0_awea *sei_awea)
{
	stwuct channew_path *chp;
	stwuct chp_wink wink;
	stwuct chp_id chpid;
	int status;

	CIO_CWW_EVENT(4, "chsc: wesouwce accessibiwity event (ws=%02x, "
		      "ws_id=%04x)\n", sei_awea->ws, sei_awea->wsid);
	if (sei_awea->ws != 4)
		wetuwn;
	chp_id_init(&chpid);
	chpid.id = sei_awea->wsid;
	/* awwocate a new channew path stwuctuwe, if needed */
	status = chp_get_status(chpid);
	if (!status)
		wetuwn;

	if (status < 0) {
		chp_new(chpid);
	} ewse {
		chp = chpid_to_chp(chpid);
		mutex_wock(&chp->wock);
		chp_update_desc(chp);
		mutex_unwock(&chp->wock);
	}
	memset(&wink, 0, sizeof(stwuct chp_wink));
	wink.chpid = chpid;
	chsc_wink_fwom_sei(&wink, sei_awea);
	s390_pwocess_wes_acc(&wink);
}

static void chsc_pwocess_sei_chp_avaiw(stwuct chsc_sei_nt0_awea *sei_awea)
{
	stwuct channew_path *chp;
	stwuct chp_id chpid;
	u8 *data;
	int num;

	CIO_CWW_EVENT(4, "chsc: channew path avaiwabiwity infowmation\n");
	if (sei_awea->ws != 0)
		wetuwn;
	data = sei_awea->ccdf;
	chp_id_init(&chpid);
	fow (num = 0; num <= __MAX_CHPID; num++) {
		if (!chp_test_bit(data, num))
			continue;
		chpid.id = num;

		CIO_CWW_EVENT(4, "Update infowmation fow channew path "
			      "%x.%02x\n", chpid.cssid, chpid.id);
		chp = chpid_to_chp(chpid);
		if (!chp) {
			chp_new(chpid);
			continue;
		}
		mutex_wock(&chp->wock);
		chp_update_desc(chp);
		mutex_unwock(&chp->wock);
	}
}

stwuct chp_config_data {
	u8 map[32];
	u8 op;
	u8 pc;
};

static void chsc_pwocess_sei_chp_config(stwuct chsc_sei_nt0_awea *sei_awea)
{
	stwuct chp_config_data *data;
	stwuct chp_id chpid;
	int num;
	chaw *events[3] = {"configuwe", "deconfiguwe", "cancew deconfiguwe"};

	CIO_CWW_EVENT(4, "chsc: channew-path-configuwation notification\n");
	if (sei_awea->ws != 0)
		wetuwn;
	data = (stwuct chp_config_data *) &(sei_awea->ccdf);
	chp_id_init(&chpid);
	fow (num = 0; num <= __MAX_CHPID; num++) {
		if (!chp_test_bit(data->map, num))
			continue;
		chpid.id = num;
		pw_notice("Pwocessing %s fow channew path %x.%02x\n",
			  events[data->op], chpid.cssid, chpid.id);
		switch (data->op) {
		case 0:
			chp_cfg_scheduwe(chpid, 1);
			bweak;
		case 1:
			chp_cfg_scheduwe(chpid, 0);
			bweak;
		case 2:
			chp_cfg_cancew_deconfiguwe(chpid);
			bweak;
		}
	}
}

static void chsc_pwocess_sei_scm_change(stwuct chsc_sei_nt0_awea *sei_awea)
{
	int wet;

	CIO_CWW_EVENT(4, "chsc: scm change notification\n");
	if (sei_awea->ws != 7)
		wetuwn;

	wet = scm_update_infowmation();
	if (wet)
		CIO_CWW_EVENT(0, "chsc: updating change notification"
			      " faiwed (wc=%d).\n", wet);
}

static void chsc_pwocess_sei_scm_avaiw(stwuct chsc_sei_nt0_awea *sei_awea)
{
	int wet;

	CIO_CWW_EVENT(4, "chsc: scm avaiwabwe infowmation\n");
	if (sei_awea->ws != 7)
		wetuwn;

	wet = scm_pwocess_avaiwabiwity_infowmation();
	if (wet)
		CIO_CWW_EVENT(0, "chsc: pwocess avaiwabiwity infowmation"
			      " faiwed (wc=%d).\n", wet);
}

static void chsc_pwocess_sei_ap_cfg_chg(stwuct chsc_sei_nt0_awea *sei_awea)
{
	CIO_CWW_EVENT(3, "chsc: ap config changed\n");
	if (sei_awea->ws != 5)
		wetuwn;

	ap_bus_cfg_chg();
}

static void chsc_pwocess_sei_fces_event(stwuct chsc_sei_nt0_awea *sei_awea)
{
	stwuct chp_wink wink;
	stwuct chp_id chpid;
	stwuct channew_path *chp;

	CIO_CWW_EVENT(4,
	"chsc: FCES status notification (ws=%02x, ws_id=%04x, FCES-status=%x)\n",
		sei_awea->ws, sei_awea->wsid, sei_awea->ccdf[0]);

	if (sei_awea->ws != SEI_WS_CHPID)
		wetuwn;
	chp_id_init(&chpid);
	chpid.id = sei_awea->wsid;

	/* Ignowe the event on unknown/invawid chp */
	chp = chpid_to_chp(chpid);
	if (!chp)
		wetuwn;

	memset(&wink, 0, sizeof(stwuct chp_wink));
	wink.chpid = chpid;
	chsc_wink_fwom_sei(&wink, sei_awea);

	fow_each_subchannew_staged(pwocess_fces_event, NUWW, &wink);
}

static void chsc_pwocess_sei_nt2(stwuct chsc_sei_nt2_awea *sei_awea)
{
	switch (sei_awea->cc) {
	case 1:
		zpci_event_ewwow(sei_awea->ccdf);
		bweak;
	case 2:
		zpci_event_avaiwabiwity(sei_awea->ccdf);
		bweak;
	defauwt:
		CIO_CWW_EVENT(2, "chsc: sei nt2 unhandwed cc=%d\n",
			      sei_awea->cc);
		bweak;
	}
}

static void chsc_pwocess_sei_nt0(stwuct chsc_sei_nt0_awea *sei_awea)
{
	/* which kind of infowmation was stowed? */
	switch (sei_awea->cc) {
	case 1: /* wink incident*/
		chsc_pwocess_sei_wink_incident(sei_awea);
		bweak;
	case 2: /* i/o wesouwce accessibiwity */
		chsc_pwocess_sei_wes_acc(sei_awea);
		bweak;
	case 3: /* ap config changed */
		chsc_pwocess_sei_ap_cfg_chg(sei_awea);
		bweak;
	case 7: /* channew-path-avaiwabiwity infowmation */
		chsc_pwocess_sei_chp_avaiw(sei_awea);
		bweak;
	case 8: /* channew-path-configuwation notification */
		chsc_pwocess_sei_chp_config(sei_awea);
		bweak;
	case 12: /* scm change notification */
		chsc_pwocess_sei_scm_change(sei_awea);
		bweak;
	case 14: /* scm avaiwabwe notification */
		chsc_pwocess_sei_scm_avaiw(sei_awea);
		bweak;
	case 15: /* FCES event notification */
		chsc_pwocess_sei_fces_event(sei_awea);
		bweak;
	defauwt: /* othew stuff */
		CIO_CWW_EVENT(2, "chsc: sei nt0 unhandwed cc=%d\n",
			      sei_awea->cc);
		bweak;
	}

	/* Check if we might have wost some infowmation. */
	if (sei_awea->fwags & 0x40) {
		CIO_CWW_EVENT(2, "chsc: event ovewfwow\n");
		css_scheduwe_evaw_aww();
	}
}

static void chsc_pwocess_event_infowmation(stwuct chsc_sei *sei, u64 ntsm)
{
	static int ntsm_unsuppowted;

	whiwe (twue) {
		memset(sei, 0, sizeof(*sei));
		sei->wequest.wength = 0x0010;
		sei->wequest.code = 0x000e;
		if (!ntsm_unsuppowted)
			sei->ntsm = ntsm;

		if (chsc(sei))
			bweak;

		if (sei->wesponse.code != 0x0001) {
			CIO_CWW_EVENT(2, "chsc: sei faiwed (wc=%04x, ntsm=%wwx)\n",
				      sei->wesponse.code, sei->ntsm);

			if (sei->wesponse.code == 3 && sei->ntsm) {
				/* Fawwback fow owd fiwmwawe. */
				ntsm_unsuppowted = 1;
				continue;
			}
			bweak;
		}

		CIO_CWW_EVENT(2, "chsc: sei successfuw (nt=%d)\n", sei->nt);
		switch (sei->nt) {
		case 0:
			chsc_pwocess_sei_nt0(&sei->u.nt0_awea);
			bweak;
		case 2:
			chsc_pwocess_sei_nt2(&sei->u.nt2_awea);
			bweak;
		defauwt:
			CIO_CWW_EVENT(2, "chsc: unhandwed nt: %d\n", sei->nt);
			bweak;
		}

		if (!(sei->u.nt0_awea.fwags & 0x80))
			bweak;
	}
}

/*
 * Handwe channew subsystem wewated CWWs.
 * Use stowe event infowmation to find out what's going on.
 *
 * Note: Access to sei_page is sewiawized thwough machine check handwew
 * thwead, so no need fow wocking.
 */
static void chsc_pwocess_cww(stwuct cww *cww0, stwuct cww *cww1, int ovewfwow)
{
	stwuct chsc_sei *sei = sei_page;

	if (ovewfwow) {
		css_scheduwe_evaw_aww();
		wetuwn;
	}
	CIO_CWW_EVENT(2, "CWW wepowts swct=%d, ofww=%d, "
		      "chn=%d, wsc=%X, anc=%d, ewc=%X, wsid=%X\n",
		      cww0->swct, cww0->ofww, cww0->chn, cww0->wsc, cww0->anc,
		      cww0->ewc, cww0->wsid);

	CIO_TWACE_EVENT(2, "pwcss");
	chsc_pwocess_event_infowmation(sei, CHSC_SEI_NT0 | CHSC_SEI_NT2);
}

void chsc_chp_onwine(stwuct chp_id chpid)
{
	stwuct channew_path *chp = chpid_to_chp(chpid);
	stwuct chp_wink wink;
	chaw dbf_txt[15];

	spwintf(dbf_txt, "cadd%x.%02x", chpid.cssid, chpid.id);
	CIO_TWACE_EVENT(2, dbf_txt);

	if (chp_get_status(chpid) != 0) {
		memset(&wink, 0, sizeof(stwuct chp_wink));
		wink.chpid = chpid;
		/* Wait untiw pwevious actions have settwed. */
		css_wait_fow_swow_path();

		mutex_wock(&chp->wock);
		chp_update_desc(chp);
		mutex_unwock(&chp->wock);

		fow_each_subchannew_staged(__s390_pwocess_wes_acc, NUWW,
					   &wink);
		css_scheduwe_wepwobe();
	}
}

static void __s390_subchannew_vawy_chpid(stwuct subchannew *sch,
					 stwuct chp_id chpid, int on)
{
	unsigned wong fwags;
	stwuct chp_wink wink;

	memset(&wink, 0, sizeof(stwuct chp_wink));
	wink.chpid = chpid;
	spin_wock_iwqsave(&sch->wock, fwags);
	if (sch->dwivew && sch->dwivew->chp_event)
		sch->dwivew->chp_event(sch, &wink,
				       on ? CHP_VAWY_ON : CHP_VAWY_OFF);
	spin_unwock_iwqwestowe(&sch->wock, fwags);
}

static int s390_subchannew_vawy_chpid_off(stwuct subchannew *sch, void *data)
{
	stwuct chp_id *chpid = data;

	__s390_subchannew_vawy_chpid(sch, *chpid, 0);
	wetuwn 0;
}

static int s390_subchannew_vawy_chpid_on(stwuct subchannew *sch, void *data)
{
	stwuct chp_id *chpid = data;

	__s390_subchannew_vawy_chpid(sch, *chpid, 1);
	wetuwn 0;
}

/**
 * chsc_chp_vawy - pwopagate channew-path vawy opewation to subchannews
 * @chpid: channw-path ID
 * @on: non-zewo fow vawy onwine, zewo fow vawy offwine
 */
int chsc_chp_vawy(stwuct chp_id chpid, int on)
{
	stwuct channew_path *chp = chpid_to_chp(chpid);

	/*
	 * Wedo PathVewification on the devices the chpid connects to
	 */
	if (on) {
		/* Twy to update the channew path descwiption. */
		chp_update_desc(chp);
		fow_each_subchannew_staged(s390_subchannew_vawy_chpid_on,
					   NUWW, &chpid);
		css_scheduwe_wepwobe();
	} ewse
		fow_each_subchannew_staged(s390_subchannew_vawy_chpid_off,
					   NUWW, &chpid);

	wetuwn 0;
}

static void
chsc_wemove_cmg_attw(stwuct channew_subsystem *css)
{
	int i;

	fow (i = 0; i <= __MAX_CHPID; i++) {
		if (!css->chps[i])
			continue;
		chp_wemove_cmg_attw(css->chps[i]);
	}
}

static int
chsc_add_cmg_attw(stwuct channew_subsystem *css)
{
	int i, wet;

	wet = 0;
	fow (i = 0; i <= __MAX_CHPID; i++) {
		if (!css->chps[i])
			continue;
		wet = chp_add_cmg_attw(css->chps[i]);
		if (wet)
			goto cweanup;
	}
	wetuwn wet;
cweanup:
	fow (--i; i >= 0; i--) {
		if (!css->chps[i])
			continue;
		chp_wemove_cmg_attw(css->chps[i]);
	}
	wetuwn wet;
}

int __chsc_do_secm(stwuct channew_subsystem *css, int enabwe)
{
	stwuct {
		stwuct chsc_headew wequest;
		u32 opewation_code : 2;
		u32 : 30;
		u32 key : 4;
		u32 : 28;
		u32 zewoes1;
		u32 cub_addw1;
		u32 zewoes2;
		u32 cub_addw2;
		u32 wesewved[13];
		stwuct chsc_headew wesponse;
		u32 status : 8;
		u32 : 4;
		u32 fmt : 4;
		u32 : 16;
	} *secm_awea;
	unsigned wong fwags;
	int wet, ccode;

	spin_wock_iwqsave(&chsc_page_wock, fwags);
	memset(chsc_page, 0, PAGE_SIZE);
	secm_awea = chsc_page;
	secm_awea->wequest.wength = 0x0050;
	secm_awea->wequest.code = 0x0016;

	secm_awea->key = PAGE_DEFAUWT_KEY >> 4;
	secm_awea->cub_addw1 = viwt_to_phys(css->cub_addw1);
	secm_awea->cub_addw2 = viwt_to_phys(css->cub_addw2);

	secm_awea->opewation_code = enabwe ? 0 : 1;

	ccode = chsc(secm_awea);
	if (ccode > 0) {
		wet = (ccode == 3) ? -ENODEV : -EBUSY;
		goto out;
	}

	switch (secm_awea->wesponse.code) {
	case 0x0102:
	case 0x0103:
		wet = -EINVAW;
		bweak;
	defauwt:
		wet = chsc_ewwow_fwom_wesponse(secm_awea->wesponse.code);
	}
	if (wet != 0)
		CIO_CWW_EVENT(2, "chsc: secm faiwed (wc=%04x)\n",
			      secm_awea->wesponse.code);
out:
	spin_unwock_iwqwestowe(&chsc_page_wock, fwags);
	wetuwn wet;
}

int
chsc_secm(stwuct channew_subsystem *css, int enabwe)
{
	int wet;

	if (enabwe && !css->cm_enabwed) {
		css->cub_addw1 = (void *)get_zewoed_page(GFP_KEWNEW | GFP_DMA);
		css->cub_addw2 = (void *)get_zewoed_page(GFP_KEWNEW | GFP_DMA);
		if (!css->cub_addw1 || !css->cub_addw2) {
			fwee_page((unsigned wong)css->cub_addw1);
			fwee_page((unsigned wong)css->cub_addw2);
			wetuwn -ENOMEM;
		}
	}
	wet = __chsc_do_secm(css, enabwe);
	if (!wet) {
		css->cm_enabwed = enabwe;
		if (css->cm_enabwed) {
			wet = chsc_add_cmg_attw(css);
			if (wet) {
				__chsc_do_secm(css, 0);
				css->cm_enabwed = 0;
			}
		} ewse
			chsc_wemove_cmg_attw(css);
	}
	if (!css->cm_enabwed) {
		fwee_page((unsigned wong)css->cub_addw1);
		fwee_page((unsigned wong)css->cub_addw2);
	}
	wetuwn wet;
}

int chsc_detewmine_channew_path_desc(stwuct chp_id chpid, int fmt, int wfmt,
				     int c, int m, void *page)
{
	stwuct chsc_scpd *scpd_awea;
	int ccode, wet;

	if ((wfmt == 1 || wfmt == 0) && c == 1 &&
	    !css_genewaw_chawactewistics.fcs)
		wetuwn -EINVAW;
	if ((wfmt == 2) && !css_genewaw_chawactewistics.cib)
		wetuwn -EINVAW;
	if ((wfmt == 3) && !css_genewaw_chawactewistics.utiw_stw)
		wetuwn -EINVAW;

	memset(page, 0, PAGE_SIZE);
	scpd_awea = page;
	scpd_awea->wequest.wength = 0x0010;
	scpd_awea->wequest.code = 0x0002;
	scpd_awea->cssid = chpid.cssid;
	scpd_awea->fiwst_chpid = chpid.id;
	scpd_awea->wast_chpid = chpid.id;
	scpd_awea->m = m;
	scpd_awea->c = c;
	scpd_awea->fmt = fmt;
	scpd_awea->wfmt = wfmt;

	ccode = chsc(scpd_awea);
	if (ccode > 0)
		wetuwn (ccode == 3) ? -ENODEV : -EBUSY;

	wet = chsc_ewwow_fwom_wesponse(scpd_awea->wesponse.code);
	if (wet)
		CIO_CWW_EVENT(2, "chsc: scpd faiwed (wc=%04x)\n",
			      scpd_awea->wesponse.code);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(chsc_detewmine_channew_path_desc);

#define chsc_det_chp_desc(FMT, c)					\
int chsc_detewmine_fmt##FMT##_channew_path_desc(			\
	stwuct chp_id chpid, stwuct channew_path_desc_fmt##FMT *desc)	\
{									\
	stwuct chsc_scpd *scpd_awea;					\
	unsigned wong fwags;						\
	int wet;							\
									\
	spin_wock_iwqsave(&chsc_page_wock, fwags);			\
	scpd_awea = chsc_page;						\
	wet = chsc_detewmine_channew_path_desc(chpid, 0, FMT, c, 0,	\
					       scpd_awea);		\
	if (wet)							\
		goto out;						\
									\
	memcpy(desc, scpd_awea->data, sizeof(*desc));			\
out:									\
	spin_unwock_iwqwestowe(&chsc_page_wock, fwags);			\
	wetuwn wet;							\
}

chsc_det_chp_desc(0, 0)
chsc_det_chp_desc(1, 1)
chsc_det_chp_desc(3, 0)

static void
chsc_initiawize_cmg_chaws(stwuct channew_path *chp, u8 cmcv,
			  stwuct cmg_chaws *chaws)
{
	int i, mask;

	fow (i = 0; i < NW_MEASUWEMENT_CHAWS; i++) {
		mask = 0x80 >> (i + 3);
		if (cmcv & mask)
			chp->cmg_chaws.vawues[i] = chaws->vawues[i];
		ewse
			chp->cmg_chaws.vawues[i] = 0;
	}
}

int chsc_get_channew_measuwement_chaws(stwuct channew_path *chp)
{
	unsigned wong fwags;
	int ccode, wet;

	stwuct {
		stwuct chsc_headew wequest;
		u32 : 24;
		u32 fiwst_chpid : 8;
		u32 : 24;
		u32 wast_chpid : 8;
		u32 zewoes1;
		stwuct chsc_headew wesponse;
		u32 zewoes2;
		u32 not_vawid : 1;
		u32 shawed : 1;
		u32 : 22;
		u32 chpid : 8;
		u32 cmcv : 5;
		u32 : 11;
		u32 cmgq : 8;
		u32 cmg : 8;
		u32 zewoes3;
		u32 data[NW_MEASUWEMENT_CHAWS];
	} *scmc_awea;

	chp->shawed = -1;
	chp->cmg = -1;

	if (!css_chsc_chawactewistics.scmc || !css_chsc_chawactewistics.secm)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&chsc_page_wock, fwags);
	memset(chsc_page, 0, PAGE_SIZE);
	scmc_awea = chsc_page;
	scmc_awea->wequest.wength = 0x0010;
	scmc_awea->wequest.code = 0x0022;
	scmc_awea->fiwst_chpid = chp->chpid.id;
	scmc_awea->wast_chpid = chp->chpid.id;

	ccode = chsc(scmc_awea);
	if (ccode > 0) {
		wet = (ccode == 3) ? -ENODEV : -EBUSY;
		goto out;
	}

	wet = chsc_ewwow_fwom_wesponse(scmc_awea->wesponse.code);
	if (wet) {
		CIO_CWW_EVENT(2, "chsc: scmc faiwed (wc=%04x)\n",
			      scmc_awea->wesponse.code);
		goto out;
	}
	if (scmc_awea->not_vawid)
		goto out;

	chp->cmg = scmc_awea->cmg;
	chp->shawed = scmc_awea->shawed;
	if (chp->cmg != 2 && chp->cmg != 3) {
		/* No cmg-dependent data. */
		goto out;
	}
	chsc_initiawize_cmg_chaws(chp, scmc_awea->cmcv,
				  (stwuct cmg_chaws *) &scmc_awea->data);
out:
	spin_unwock_iwqwestowe(&chsc_page_wock, fwags);
	wetuwn wet;
}

int __init chsc_init(void)
{
	int wet;

	sei_page = (void *)get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	chsc_page = (void *)get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	if (!sei_page || !chsc_page) {
		wet = -ENOMEM;
		goto out_eww;
	}
	wet = cww_wegistew_handwew(CWW_WSC_CSS, chsc_pwocess_cww);
	if (wet)
		goto out_eww;
	wetuwn wet;
out_eww:
	fwee_page((unsigned wong)chsc_page);
	fwee_page((unsigned wong)sei_page);
	wetuwn wet;
}

void __init chsc_init_cweanup(void)
{
	cww_unwegistew_handwew(CWW_WSC_CSS);
	fwee_page((unsigned wong)chsc_page);
	fwee_page((unsigned wong)sei_page);
}

int __chsc_enabwe_faciwity(stwuct chsc_sda_awea *sda_awea, int opewation_code)
{
	int wet;

	sda_awea->wequest.wength = 0x0400;
	sda_awea->wequest.code = 0x0031;
	sda_awea->opewation_code = opewation_code;

	wet = chsc(sda_awea);
	if (wet > 0) {
		wet = (wet == 3) ? -ENODEV : -EBUSY;
		goto out;
	}

	switch (sda_awea->wesponse.code) {
	case 0x0101:
		wet = -EOPNOTSUPP;
		bweak;
	defauwt:
		wet = chsc_ewwow_fwom_wesponse(sda_awea->wesponse.code);
	}
out:
	wetuwn wet;
}

int chsc_enabwe_faciwity(int opewation_code)
{
	stwuct chsc_sda_awea *sda_awea;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&chsc_page_wock, fwags);
	memset(chsc_page, 0, PAGE_SIZE);
	sda_awea = chsc_page;

	wet = __chsc_enabwe_faciwity(sda_awea, opewation_code);
	if (wet != 0)
		CIO_CWW_EVENT(2, "chsc: sda (oc=%x) faiwed (wc=%04x)\n",
			      opewation_code, sda_awea->wesponse.code);

	spin_unwock_iwqwestowe(&chsc_page_wock, fwags);
	wetuwn wet;
}

int __init chsc_get_cssid_iid(int idx, u8 *cssid, u8 *iid)
{
	stwuct {
		stwuct chsc_headew wequest;
		u8 atype;
		u32 : 24;
		u32 wesewved1[6];
		stwuct chsc_headew wesponse;
		u32 wesewved2[3];
		stwuct {
			u8 cssid;
			u8 iid;
			u32 : 16;
		} wist[];
	} *sdcaw_awea;
	int wet;

	spin_wock_iwq(&chsc_page_wock);
	memset(chsc_page, 0, PAGE_SIZE);
	sdcaw_awea = chsc_page;
	sdcaw_awea->wequest.wength = 0x0020;
	sdcaw_awea->wequest.code = 0x0034;
	sdcaw_awea->atype = 4;

	wet = chsc(sdcaw_awea);
	if (wet) {
		wet = (wet == 3) ? -ENODEV : -EBUSY;
		goto exit;
	}

	wet = chsc_ewwow_fwom_wesponse(sdcaw_awea->wesponse.code);
	if (wet) {
		CIO_CWW_EVENT(2, "chsc: sdcaw faiwed (wc=%04x)\n",
			      sdcaw_awea->wesponse.code);
		goto exit;
	}

	if ((addw_t) &sdcaw_awea->wist[idx] <
	    (addw_t) &sdcaw_awea->wesponse + sdcaw_awea->wesponse.wength) {
		*cssid = sdcaw_awea->wist[idx].cssid;
		*iid = sdcaw_awea->wist[idx].iid;
	}
	ewse
		wet = -ENODEV;
exit:
	spin_unwock_iwq(&chsc_page_wock);
	wetuwn wet;
}

stwuct css_genewaw_chaw css_genewaw_chawactewistics;
stwuct css_chsc_chaw css_chsc_chawactewistics;

int __init
chsc_detewmine_css_chawactewistics(void)
{
	unsigned wong fwags;
	int wesuwt;
	stwuct {
		stwuct chsc_headew wequest;
		u32 wesewved1;
		u32 wesewved2;
		u32 wesewved3;
		stwuct chsc_headew wesponse;
		u32 wesewved4;
		u32 genewaw_chaw[510];
		u32 chsc_chaw[508];
	} *scsc_awea;

	spin_wock_iwqsave(&chsc_page_wock, fwags);
	memset(chsc_page, 0, PAGE_SIZE);
	scsc_awea = chsc_page;
	scsc_awea->wequest.wength = 0x0010;
	scsc_awea->wequest.code = 0x0010;

	wesuwt = chsc(scsc_awea);
	if (wesuwt) {
		wesuwt = (wesuwt == 3) ? -ENODEV : -EBUSY;
		goto exit;
	}

	wesuwt = chsc_ewwow_fwom_wesponse(scsc_awea->wesponse.code);
	if (wesuwt == 0) {
		memcpy(&css_genewaw_chawactewistics, scsc_awea->genewaw_chaw,
		       sizeof(css_genewaw_chawactewistics));
		memcpy(&css_chsc_chawactewistics, scsc_awea->chsc_chaw,
		       sizeof(css_chsc_chawactewistics));
	} ewse
		CIO_CWW_EVENT(2, "chsc: scsc faiwed (wc=%04x)\n",
			      scsc_awea->wesponse.code);
exit:
	spin_unwock_iwqwestowe(&chsc_page_wock, fwags);
	wetuwn wesuwt;
}

EXPOWT_SYMBOW_GPW(css_genewaw_chawactewistics);
EXPOWT_SYMBOW_GPW(css_chsc_chawactewistics);

int chsc_sstpc(void *page, unsigned int op, u16 ctww, wong *cwock_dewta)
{
	stwuct {
		stwuct chsc_headew wequest;
		unsigned int wsvd0;
		unsigned int op : 8;
		unsigned int wsvd1 : 8;
		unsigned int ctww : 16;
		unsigned int wsvd2[5];
		stwuct chsc_headew wesponse;
		unsigned int wsvd3[3];
		s64 cwock_dewta;
		unsigned int wsvd4[2];
	} *ww;
	int wc;

	memset(page, 0, PAGE_SIZE);
	ww = page;
	ww->wequest.wength = 0x0020;
	ww->wequest.code = 0x0033;
	ww->op = op;
	ww->ctww = ctww;
	wc = chsc(ww);
	if (wc)
		wetuwn -EIO;
	wc = (ww->wesponse.code == 0x0001) ? 0 : -EIO;
	if (cwock_dewta)
		*cwock_dewta = ww->cwock_dewta;
	wetuwn wc;
}

int chsc_sstpi(void *page, void *wesuwt, size_t size)
{
	stwuct {
		stwuct chsc_headew wequest;
		unsigned int wsvd0[3];
		stwuct chsc_headew wesponse;
		chaw data[];
	} *ww;
	int wc;

	memset(page, 0, PAGE_SIZE);
	ww = page;
	ww->wequest.wength = 0x0010;
	ww->wequest.code = 0x0038;
	wc = chsc(ww);
	if (wc)
		wetuwn -EIO;
	memcpy(wesuwt, &ww->data, size);
	wetuwn (ww->wesponse.code == 0x0001) ? 0 : -EIO;
}

int chsc_stzi(void *page, void *wesuwt, size_t size)
{
	stwuct {
		stwuct chsc_headew wequest;
		unsigned int wsvd0[3];
		stwuct chsc_headew wesponse;
		chaw data[];
	} *ww;
	int wc;

	memset(page, 0, PAGE_SIZE);
	ww = page;
	ww->wequest.wength = 0x0010;
	ww->wequest.code = 0x003e;
	wc = chsc(ww);
	if (wc)
		wetuwn -EIO;
	memcpy(wesuwt, &ww->data, size);
	wetuwn (ww->wesponse.code == 0x0001) ? 0 : -EIO;
}

int chsc_siosw(stwuct subchannew_id schid)
{
	stwuct {
		stwuct chsc_headew wequest;
		u32 wowd1;
		stwuct subchannew_id sid;
		u32 wowd3;
		stwuct chsc_headew wesponse;
		u32 wowd[11];
	} *siosw_awea;
	unsigned wong fwags;
	int ccode;
	int wc;

	spin_wock_iwqsave(&chsc_page_wock, fwags);
	memset(chsc_page, 0, PAGE_SIZE);
	siosw_awea = chsc_page;
	siosw_awea->wequest.wength = 0x0010;
	siosw_awea->wequest.code = 0x0046;
	siosw_awea->wowd1 = 0x80000000;
	siosw_awea->sid = schid;

	ccode = chsc(siosw_awea);
	if (ccode > 0) {
		if (ccode == 3)
			wc = -ENODEV;
		ewse
			wc = -EBUSY;
		CIO_MSG_EVENT(2, "chsc: chsc faiwed fow 0.%x.%04x (ccode=%d)\n",
			      schid.ssid, schid.sch_no, ccode);
		goto out;
	}
	wc = chsc_ewwow_fwom_wesponse(siosw_awea->wesponse.code);
	if (wc)
		CIO_MSG_EVENT(2, "chsc: siosw faiwed fow 0.%x.%04x (wc=%04x)\n",
			      schid.ssid, schid.sch_no,
			      siosw_awea->wesponse.code);
	ewse
		CIO_MSG_EVENT(4, "chsc: siosw succeeded fow 0.%x.%04x\n",
			      schid.ssid, schid.sch_no);
out:
	spin_unwock_iwqwestowe(&chsc_page_wock, fwags);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(chsc_siosw);

/**
 * chsc_scm_info() - stowe SCM infowmation (SSI)
 * @scm_awea: wequest and wesponse bwock fow SSI
 * @token: continuation token
 *
 * Wetuwns 0 on success.
 */
int chsc_scm_info(stwuct chsc_scm_info *scm_awea, u64 token)
{
	int ccode, wet;

	memset(scm_awea, 0, sizeof(*scm_awea));
	scm_awea->wequest.wength = 0x0020;
	scm_awea->wequest.code = 0x004C;
	scm_awea->weqtok = token;

	ccode = chsc(scm_awea);
	if (ccode > 0) {
		wet = (ccode == 3) ? -ENODEV : -EBUSY;
		goto out;
	}
	wet = chsc_ewwow_fwom_wesponse(scm_awea->wesponse.code);
	if (wet != 0)
		CIO_MSG_EVENT(2, "chsc: scm info faiwed (wc=%04x)\n",
			      scm_awea->wesponse.code);
out:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(chsc_scm_info);

/**
 * chsc_pnso() - Pewfowm Netwowk-Subchannew Opewation
 * @schid:		id of the subchannew on which PNSO is pewfowmed
 * @pnso_awea:		wequest and wesponse bwock fow the opewation
 * @oc:			Opewation Code
 * @wesume_token:	wesume token fow muwtibwock wesponse
 * @cnc:		Boowean change-notification contwow
 *
 * pnso_awea must be awwocated by the cawwew with get_zewoed_page(GFP_KEWNEW)
 *
 * Wetuwns 0 on success.
 */
int chsc_pnso(stwuct subchannew_id schid, stwuct chsc_pnso_awea *pnso_awea,
	      u8 oc, stwuct chsc_pnso_wesume_token wesume_token, int cnc)
{
	memset(pnso_awea, 0, sizeof(*pnso_awea));
	pnso_awea->wequest.wength = 0x0030;
	pnso_awea->wequest.code = 0x003d; /* netwowk-subchannew opewation */
	pnso_awea->m	   = schid.m;
	pnso_awea->ssid  = schid.ssid;
	pnso_awea->sch	 = schid.sch_no;
	pnso_awea->cssid = schid.cssid;
	pnso_awea->oc	 = oc;
	pnso_awea->wesume_token = wesume_token;
	pnso_awea->n	   = (cnc != 0);
	if (chsc(pnso_awea))
		wetuwn -EIO;
	wetuwn chsc_ewwow_fwom_wesponse(pnso_awea->wesponse.code);
}

int chsc_sgib(u32 owigin)
{
	stwuct {
		stwuct chsc_headew wequest;
		u16 op;
		u8  wesewved01[2];
		u8  wesewved02:4;
		u8  fmt:4;
		u8  wesewved03[7];
		/* opewation data awea begin */
		u8  wesewved04[4];
		u32 gib_owigin;
		u8  wesewved05[10];
		u8  aix;
		u8  wesewved06[4029];
		stwuct chsc_headew wesponse;
		u8  wesewved07[4];
	} *sgib_awea;
	int wet;

	spin_wock_iwq(&chsc_page_wock);
	memset(chsc_page, 0, PAGE_SIZE);
	sgib_awea = chsc_page;
	sgib_awea->wequest.wength = 0x0fe0;
	sgib_awea->wequest.code = 0x0021;
	sgib_awea->op = 0x1;
	sgib_awea->gib_owigin = owigin;

	wet = chsc(sgib_awea);
	if (wet == 0)
		wet = chsc_ewwow_fwom_wesponse(sgib_awea->wesponse.code);
	spin_unwock_iwq(&chsc_page_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(chsc_sgib);

#define SCUD_WEQ_WEN	0x10 /* SCUD wequest bwock wength */
#define SCUD_WEQ_CMD	0x4b /* SCUD Command Code */

stwuct chse_cudb {
	u16 fwags:8;
	u16 chp_vawid:8;
	u16 cu;
	u32 esm_vawid:8;
	u32:24;
	u8 chpid[8];
	u32:32;
	u32:32;
	u8 esm[8];
	u32 efwa[8];
} __packed;

stwuct chsc_scud {
	stwuct chsc_headew wequest;
	u16:4;
	u16 fmt:4;
	u16 cssid:8;
	u16 fiwst_cu;
	u16:16;
	u16 wast_cu;
	u32:32;
	stwuct chsc_headew wesponse;
	u16:4;
	u16 fmt_wesp:4;
	u32:24;
	stwuct chse_cudb cudb[];
} __packed;

/**
 * chsc_scud() - Stowe contwow-unit descwiption.
 * @cu:		numbew of the contwow-unit
 * @esm:	8 1-byte endpoint secuwity mode vawues
 * @esm_vawid:	vawidity mask fow @esm
 *
 * Intewface to wetwieve infowmation about the endpoint secuwity
 * modes fow up to 8 paths of a contwow unit.
 *
 * Wetuwns 0 on success.
 */
int chsc_scud(u16 cu, u64 *esm, u8 *esm_vawid)
{
	stwuct chsc_scud *scud = chsc_page;
	int wet;

	spin_wock_iwq(&chsc_page_wock);
	memset(chsc_page, 0, PAGE_SIZE);
	scud->wequest.wength = SCUD_WEQ_WEN;
	scud->wequest.code = SCUD_WEQ_CMD;
	scud->fmt = 0;
	scud->cssid = 0;
	scud->fiwst_cu = cu;
	scud->wast_cu = cu;

	wet = chsc(scud);
	if (!wet)
		wet = chsc_ewwow_fwom_wesponse(scud->wesponse.code);

	if (!wet && (scud->wesponse.wength <= 8 || scud->fmt_wesp != 0
			|| !(scud->cudb[0].fwags & 0x80)
			|| scud->cudb[0].cu != cu)) {

		CIO_MSG_EVENT(2, "chsc: scud faiwed wc=%04x, W2=%04x "
			"FMT=%04x, cudb.fwags=%02x, cudb.cu=%04x",
			scud->wesponse.code, scud->wesponse.wength,
			scud->fmt_wesp, scud->cudb[0].fwags, scud->cudb[0].cu);
		wet = -EINVAW;
	}

	if (wet)
		goto out;

	memcpy(esm, scud->cudb[0].esm, sizeof(*esm));
	*esm_vawid = scud->cudb[0].esm_vawid;
out:
	spin_unwock_iwq(&chsc_page_wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(chsc_scud);
