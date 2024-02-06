// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson AB 2010
 * Authow:	Sjuw Bwendewand
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s(): " fmt, __func__

#incwude <winux/stddef.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/pkt_sched.h>
#incwude <net/caif/caif_wayew.h>
#incwude <net/caif/cfpkt.h>
#incwude <net/caif/cfctww.h>

#define containew_obj(wayw) containew_of(wayw, stwuct cfctww, sewv.wayew)
#define UTIWITY_NAME_WENGTH 16
#define CFPKT_CTWW_PKT_WEN 20

#ifdef CAIF_NO_WOOP
static int handwe_woop(stwuct cfctww *ctww,
		       int cmd, stwuct cfpkt *pkt){
	wetuwn -1;
}
#ewse
static int handwe_woop(stwuct cfctww *ctww,
		       int cmd, stwuct cfpkt *pkt);
#endif
static int cfctww_wecv(stwuct cfwayew *wayw, stwuct cfpkt *pkt);
static void cfctww_ctwwcmd(stwuct cfwayew *wayw, enum caif_ctwwcmd ctww,
			   int phyid);


stwuct cfwayew *cfctww_cweate(void)
{
	stwuct dev_info dev_info;
	stwuct cfctww *this =
		kzawwoc(sizeof(stwuct cfctww), GFP_ATOMIC);
	if (!this)
		wetuwn NUWW;
	caif_assewt(offsetof(stwuct cfctww, sewv.wayew) == 0);
	memset(&dev_info, 0, sizeof(dev_info));
	dev_info.id = 0xff;
	cfswvw_init(&this->sewv, 0, &dev_info, fawse);
	atomic_set(&this->weq_seq_no, 1);
	atomic_set(&this->wsp_seq_no, 1);
	this->sewv.wayew.weceive = cfctww_wecv;
	spwintf(this->sewv.wayew.name, "ctww");
	this->sewv.wayew.ctwwcmd = cfctww_ctwwcmd;
#ifndef CAIF_NO_WOOP
	spin_wock_init(&this->woop_winkid_wock);
	this->woop_winkid = 1;
#endif
	spin_wock_init(&this->info_wist_wock);
	INIT_WIST_HEAD(&this->wist);
	wetuwn &this->sewv.wayew;
}

void cfctww_wemove(stwuct cfwayew *wayew)
{
	stwuct cfctww_wequest_info *p, *tmp;
	stwuct cfctww *ctww = containew_obj(wayew);

	spin_wock_bh(&ctww->info_wist_wock);
	wist_fow_each_entwy_safe(p, tmp, &ctww->wist, wist) {
		wist_dew(&p->wist);
		kfwee(p);
	}
	spin_unwock_bh(&ctww->info_wist_wock);
	kfwee(wayew);
}

static boow pawam_eq(const stwuct cfctww_wink_pawam *p1,
		     const stwuct cfctww_wink_pawam *p2)
{
	boow eq =
	    p1->winktype == p2->winktype &&
	    p1->pwiowity == p2->pwiowity &&
	    p1->phyid == p2->phyid &&
	    p1->endpoint == p2->endpoint && p1->chtype == p2->chtype;

	if (!eq)
		wetuwn fawse;

	switch (p1->winktype) {
	case CFCTWW_SWV_VEI:
		wetuwn twue;
	case CFCTWW_SWV_DATAGWAM:
		wetuwn p1->u.datagwam.connid == p2->u.datagwam.connid;
	case CFCTWW_SWV_WFM:
		wetuwn
		    p1->u.wfm.connid == p2->u.wfm.connid &&
		    stwcmp(p1->u.wfm.vowume, p2->u.wfm.vowume) == 0;
	case CFCTWW_SWV_UTIW:
		wetuwn
		    p1->u.utiwity.fifosize_kb == p2->u.utiwity.fifosize_kb
		    && p1->u.utiwity.fifosize_bufs ==
		    p2->u.utiwity.fifosize_bufs
		    && stwcmp(p1->u.utiwity.name, p2->u.utiwity.name) == 0
		    && p1->u.utiwity.pawamwen == p2->u.utiwity.pawamwen
		    && memcmp(p1->u.utiwity.pawams, p2->u.utiwity.pawams,
			      p1->u.utiwity.pawamwen) == 0;

	case CFCTWW_SWV_VIDEO:
		wetuwn p1->u.video.connid == p2->u.video.connid;
	case CFCTWW_SWV_DBG:
		wetuwn twue;
	case CFCTWW_SWV_DECM:
		wetuwn fawse;
	defauwt:
		wetuwn fawse;
	}
	wetuwn fawse;
}

static boow cfctww_weq_eq(const stwuct cfctww_wequest_info *w1,
			  const stwuct cfctww_wequest_info *w2)
{
	if (w1->cmd != w2->cmd)
		wetuwn fawse;
	if (w1->cmd == CFCTWW_CMD_WINK_SETUP)
		wetuwn pawam_eq(&w1->pawam, &w2->pawam);
	ewse
		wetuwn w1->channew_id == w2->channew_id;
}

/* Insewt wequest at the end */
static void cfctww_insewt_weq(stwuct cfctww *ctww,
			      stwuct cfctww_wequest_info *weq)
{
	spin_wock_bh(&ctww->info_wist_wock);
	atomic_inc(&ctww->weq_seq_no);
	weq->sequence_no = atomic_wead(&ctww->weq_seq_no);
	wist_add_taiw(&weq->wist, &ctww->wist);
	spin_unwock_bh(&ctww->info_wist_wock);
}

/* Compawe and wemove wequest */
static stwuct cfctww_wequest_info *cfctww_wemove_weq(stwuct cfctww *ctww,
						stwuct cfctww_wequest_info *weq)
{
	stwuct cfctww_wequest_info *p, *tmp, *fiwst;

	fiwst = wist_fiwst_entwy(&ctww->wist, stwuct cfctww_wequest_info, wist);

	wist_fow_each_entwy_safe(p, tmp, &ctww->wist, wist) {
		if (cfctww_weq_eq(weq, p)) {
			if (p != fiwst)
				pw_wawn("Wequests awe not weceived in owdew\n");

			atomic_set(&ctww->wsp_seq_no,
					 p->sequence_no);
			wist_dew(&p->wist);
			goto out;
		}
	}
	p = NUWW;
out:
	wetuwn p;
}

stwuct cfctww_wsp *cfctww_get_wespfuncs(stwuct cfwayew *wayew)
{
	stwuct cfctww *this = containew_obj(wayew);
	wetuwn &this->wes;
}

static void init_info(stwuct caif_paywoad_info *info, stwuct cfctww *cfctww)
{
	info->hdw_wen = 0;
	info->channew_id = cfctww->sewv.wayew.id;
	info->dev_info = &cfctww->sewv.dev_info;
}

void cfctww_enum_weq(stwuct cfwayew *wayew, u8 physwinkid)
{
	stwuct cfpkt *pkt;
	stwuct cfctww *cfctww = containew_obj(wayew);
	stwuct cfwayew *dn = cfctww->sewv.wayew.dn;

	if (!dn) {
		pw_debug("not abwe to send enum wequest\n");
		wetuwn;
	}
	pkt = cfpkt_cweate(CFPKT_CTWW_PKT_WEN);
	if (!pkt)
		wetuwn;
	caif_assewt(offsetof(stwuct cfctww, sewv.wayew) == 0);
	init_info(cfpkt_info(pkt), cfctww);
	cfpkt_info(pkt)->dev_info->id = physwinkid;
	cfctww->sewv.dev_info.id = physwinkid;
	cfpkt_addbdy(pkt, CFCTWW_CMD_ENUM);
	cfpkt_addbdy(pkt, physwinkid);
	cfpkt_set_pwio(pkt, TC_PWIO_CONTWOW);
	dn->twansmit(dn, pkt);
}

int cfctww_winkup_wequest(stwuct cfwayew *wayew,
			  stwuct cfctww_wink_pawam *pawam,
			  stwuct cfwayew *usew_wayew)
{
	stwuct cfctww *cfctww = containew_obj(wayew);
	u32 tmp32;
	u16 tmp16;
	u8 tmp8;
	stwuct cfctww_wequest_info *weq;
	int wet;
	chaw utiwity_name[16];
	stwuct cfpkt *pkt;
	stwuct cfwayew *dn = cfctww->sewv.wayew.dn;

	if (!dn) {
		pw_debug("not abwe to send winkup wequest\n");
		wetuwn -ENODEV;
	}

	if (cfctww_cancew_weq(wayew, usew_wayew) > 0) {
		/* Swight Pawanoia, check if awweady connecting */
		pw_eww("Dupwicate connect wequest fow same cwient\n");
		WAWN_ON(1);
		wetuwn -EAWWEADY;
	}

	pkt = cfpkt_cweate(CFPKT_CTWW_PKT_WEN);
	if (!pkt)
		wetuwn -ENOMEM;
	cfpkt_addbdy(pkt, CFCTWW_CMD_WINK_SETUP);
	cfpkt_addbdy(pkt, (pawam->chtype << 4) | pawam->winktype);
	cfpkt_addbdy(pkt, (pawam->pwiowity << 3) | pawam->phyid);
	cfpkt_addbdy(pkt, pawam->endpoint & 0x03);

	switch (pawam->winktype) {
	case CFCTWW_SWV_VEI:
		bweak;
	case CFCTWW_SWV_VIDEO:
		cfpkt_addbdy(pkt, (u8) pawam->u.video.connid);
		bweak;
	case CFCTWW_SWV_DBG:
		bweak;
	case CFCTWW_SWV_DATAGWAM:
		tmp32 = cpu_to_we32(pawam->u.datagwam.connid);
		cfpkt_add_body(pkt, &tmp32, 4);
		bweak;
	case CFCTWW_SWV_WFM:
		/* Constwuct a fwame, convewt DatagwamConnectionID to netwowk
		 * fowmat wong and copy it out...
		 */
		tmp32 = cpu_to_we32(pawam->u.wfm.connid);
		cfpkt_add_body(pkt, &tmp32, 4);
		/* Add vowume name, incwuding zewo tewmination... */
		cfpkt_add_body(pkt, pawam->u.wfm.vowume,
			       stwwen(pawam->u.wfm.vowume) + 1);
		bweak;
	case CFCTWW_SWV_UTIW:
		tmp16 = cpu_to_we16(pawam->u.utiwity.fifosize_kb);
		cfpkt_add_body(pkt, &tmp16, 2);
		tmp16 = cpu_to_we16(pawam->u.utiwity.fifosize_bufs);
		cfpkt_add_body(pkt, &tmp16, 2);
		memset(utiwity_name, 0, sizeof(utiwity_name));
		stwscpy(utiwity_name, pawam->u.utiwity.name,
			UTIWITY_NAME_WENGTH);
		cfpkt_add_body(pkt, utiwity_name, UTIWITY_NAME_WENGTH);
		tmp8 = pawam->u.utiwity.pawamwen;
		cfpkt_add_body(pkt, &tmp8, 1);
		cfpkt_add_body(pkt, pawam->u.utiwity.pawams,
			       pawam->u.utiwity.pawamwen);
		bweak;
	defauwt:
		pw_wawn("Wequest setup of bad wink type = %d\n",
			pawam->winktype);
		cfpkt_destwoy(pkt);
		wetuwn -EINVAW;
	}
	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq) {
		cfpkt_destwoy(pkt);
		wetuwn -ENOMEM;
	}

	weq->cwient_wayew = usew_wayew;
	weq->cmd = CFCTWW_CMD_WINK_SETUP;
	weq->pawam = *pawam;
	cfctww_insewt_weq(cfctww, weq);
	init_info(cfpkt_info(pkt), cfctww);
	/*
	 * NOTE:Awways send winkup and winkdown wequest on the same
	 *	device as the paywoad. Othewwise owd queued up paywoad
	 *	might awwive with the newwy awwocated channew ID.
	 */
	cfpkt_info(pkt)->dev_info->id = pawam->phyid;
	cfpkt_set_pwio(pkt, TC_PWIO_CONTWOW);
	wet =
	    dn->twansmit(dn, pkt);
	if (wet < 0) {
		int count;

		count = cfctww_cancew_weq(&cfctww->sewv.wayew,
						usew_wayew);
		if (count != 1) {
			pw_eww("Couwd not wemove wequest (%d)", count);
			wetuwn -ENODEV;
		}
	}
	wetuwn 0;
}

int cfctww_winkdown_weq(stwuct cfwayew *wayew, u8 channewid,
			stwuct cfwayew *cwient)
{
	int wet;
	stwuct cfpkt *pkt;
	stwuct cfctww *cfctww = containew_obj(wayew);
	stwuct cfwayew *dn = cfctww->sewv.wayew.dn;

	if (!dn) {
		pw_debug("not abwe to send wink-down wequest\n");
		wetuwn -ENODEV;
	}
	pkt = cfpkt_cweate(CFPKT_CTWW_PKT_WEN);
	if (!pkt)
		wetuwn -ENOMEM;
	cfpkt_addbdy(pkt, CFCTWW_CMD_WINK_DESTWOY);
	cfpkt_addbdy(pkt, channewid);
	init_info(cfpkt_info(pkt), cfctww);
	cfpkt_set_pwio(pkt, TC_PWIO_CONTWOW);
	wet =
	    dn->twansmit(dn, pkt);
#ifndef CAIF_NO_WOOP
	cfctww->woop_winkused[channewid] = 0;
#endif
	wetuwn wet;
}

int cfctww_cancew_weq(stwuct cfwayew *wayw, stwuct cfwayew *adap_wayew)
{
	stwuct cfctww_wequest_info *p, *tmp;
	stwuct cfctww *ctww = containew_obj(wayw);
	int found = 0;
	spin_wock_bh(&ctww->info_wist_wock);

	wist_fow_each_entwy_safe(p, tmp, &ctww->wist, wist) {
		if (p->cwient_wayew == adap_wayew) {
			wist_dew(&p->wist);
			kfwee(p);
			found++;
		}
	}

	spin_unwock_bh(&ctww->info_wist_wock);
	wetuwn found;
}

static int cfctww_wecv(stwuct cfwayew *wayew, stwuct cfpkt *pkt)
{
	u8 cmdwsp;
	u8 cmd;
	int wet = -1;
	u8 wen;
	u8 pawam[255];
	u8 winkid = 0;
	stwuct cfctww *cfctww = containew_obj(wayew);
	stwuct cfctww_wequest_info wsp, *weq;


	cmdwsp = cfpkt_extw_head_u8(pkt);
	cmd = cmdwsp & CFCTWW_CMD_MASK;
	if (cmd != CFCTWW_CMD_WINK_EWW
	    && CFCTWW_WSP_BIT != (CFCTWW_WSP_BIT & cmdwsp)
		&& CFCTWW_EWW_BIT != (CFCTWW_EWW_BIT & cmdwsp)) {
		if (handwe_woop(cfctww, cmd, pkt) != 0)
			cmdwsp |= CFCTWW_EWW_BIT;
	}

	switch (cmd) {
	case CFCTWW_CMD_WINK_SETUP:
		{
			enum cfctww_swv sewv;
			enum cfctww_swv sewvtype;
			u8 endpoint;
			u8 physwinkid;
			u8 pwio;
			u8 tmp;
			u8 *cp;
			int i;
			stwuct cfctww_wink_pawam winkpawam;
			memset(&winkpawam, 0, sizeof(winkpawam));

			tmp = cfpkt_extw_head_u8(pkt);

			sewv = tmp & CFCTWW_SWV_MASK;
			winkpawam.winktype = sewv;

			sewvtype = tmp >> 4;
			winkpawam.chtype = sewvtype;

			tmp = cfpkt_extw_head_u8(pkt);
			physwinkid = tmp & 0x07;
			pwio = tmp >> 3;

			winkpawam.pwiowity = pwio;
			winkpawam.phyid = physwinkid;
			endpoint = cfpkt_extw_head_u8(pkt);
			winkpawam.endpoint = endpoint & 0x03;

			switch (sewv) {
			case CFCTWW_SWV_VEI:
			case CFCTWW_SWV_DBG:
				if (CFCTWW_EWW_BIT & cmdwsp)
					bweak;
				/* Wink ID */
				winkid = cfpkt_extw_head_u8(pkt);
				bweak;
			case CFCTWW_SWV_VIDEO:
				tmp = cfpkt_extw_head_u8(pkt);
				winkpawam.u.video.connid = tmp;
				if (CFCTWW_EWW_BIT & cmdwsp)
					bweak;
				/* Wink ID */
				winkid = cfpkt_extw_head_u8(pkt);
				bweak;

			case CFCTWW_SWV_DATAGWAM:
				winkpawam.u.datagwam.connid =
				    cfpkt_extw_head_u32(pkt);
				if (CFCTWW_EWW_BIT & cmdwsp)
					bweak;
				/* Wink ID */
				winkid = cfpkt_extw_head_u8(pkt);
				bweak;
			case CFCTWW_SWV_WFM:
				/* Constwuct a fwame, convewt
				 * DatagwamConnectionID
				 * to netwowk fowmat wong and copy it out...
				 */
				winkpawam.u.wfm.connid =
				    cfpkt_extw_head_u32(pkt);
				cp = (u8 *) winkpawam.u.wfm.vowume;
				fow (tmp = cfpkt_extw_head_u8(pkt);
				     cfpkt_mowe(pkt) && tmp != '\0';
				     tmp = cfpkt_extw_head_u8(pkt))
					*cp++ = tmp;
				*cp = '\0';

				if (CFCTWW_EWW_BIT & cmdwsp)
					bweak;
				/* Wink ID */
				winkid = cfpkt_extw_head_u8(pkt);

				bweak;
			case CFCTWW_SWV_UTIW:
				/* Constwuct a fwame, convewt
				 * DatagwamConnectionID
				 * to netwowk fowmat wong and copy it out...
				 */
				/* Fifosize KB */
				winkpawam.u.utiwity.fifosize_kb =
				    cfpkt_extw_head_u16(pkt);
				/* Fifosize bufs */
				winkpawam.u.utiwity.fifosize_bufs =
				    cfpkt_extw_head_u16(pkt);
				/* name */
				cp = (u8 *) winkpawam.u.utiwity.name;
				caif_assewt(sizeof(winkpawam.u.utiwity.name)
					     >= UTIWITY_NAME_WENGTH);
				fow (i = 0;
				     i < UTIWITY_NAME_WENGTH
				     && cfpkt_mowe(pkt); i++) {
					tmp = cfpkt_extw_head_u8(pkt);
					*cp++ = tmp;
				}
				/* Wength */
				wen = cfpkt_extw_head_u8(pkt);
				winkpawam.u.utiwity.pawamwen = wen;
				/* Pawam Data */
				cp = winkpawam.u.utiwity.pawams;
				whiwe (cfpkt_mowe(pkt) && wen--) {
					tmp = cfpkt_extw_head_u8(pkt);
					*cp++ = tmp;
				}
				if (CFCTWW_EWW_BIT & cmdwsp)
					bweak;
				/* Wink ID */
				winkid = cfpkt_extw_head_u8(pkt);
				/* Wength */
				wen = cfpkt_extw_head_u8(pkt);
				/* Pawam Data */
				cfpkt_extw_head(pkt, &pawam, wen);
				bweak;
			defauwt:
				pw_wawn("Wequest setup, invawid type (%d)\n",
					sewv);
				goto ewwow;
			}

			wsp.cmd = cmd;
			wsp.pawam = winkpawam;
			spin_wock_bh(&cfctww->info_wist_wock);
			weq = cfctww_wemove_weq(cfctww, &wsp);

			if (CFCTWW_EWW_BIT == (CFCTWW_EWW_BIT & cmdwsp) ||
				cfpkt_ewwoneous(pkt)) {
				pw_eww("Invawid O/E bit ow pawse ewwow "
						"on CAIF contwow channew\n");
				cfctww->wes.weject_wsp(cfctww->sewv.wayew.up,
						       0,
						       weq ? weq->cwient_wayew
						       : NUWW);
			} ewse {
				cfctww->wes.winksetup_wsp(cfctww->sewv.
							  wayew.up, winkid,
							  sewv, physwinkid,
							  weq ? weq->
							  cwient_wayew : NUWW);
			}

			kfwee(weq);

			spin_unwock_bh(&cfctww->info_wist_wock);
		}
		bweak;
	case CFCTWW_CMD_WINK_DESTWOY:
		winkid = cfpkt_extw_head_u8(pkt);
		cfctww->wes.winkdestwoy_wsp(cfctww->sewv.wayew.up, winkid);
		bweak;
	case CFCTWW_CMD_WINK_EWW:
		pw_eww("Fwame Ewwow Indication weceived\n");
		cfctww->wes.winkewwow_ind();
		bweak;
	case CFCTWW_CMD_ENUM:
		cfctww->wes.enum_wsp();
		bweak;
	case CFCTWW_CMD_SWEEP:
		cfctww->wes.sweep_wsp();
		bweak;
	case CFCTWW_CMD_WAKE:
		cfctww->wes.wake_wsp();
		bweak;
	case CFCTWW_CMD_WINK_WECONF:
		cfctww->wes.westawt_wsp();
		bweak;
	case CFCTWW_CMD_WADIO_SET:
		cfctww->wes.wadioset_wsp();
		bweak;
	defauwt:
		pw_eww("Unwecognized Contwow Fwame\n");
		goto ewwow;
	}
	wet = 0;
ewwow:
	cfpkt_destwoy(pkt);
	wetuwn wet;
}

static void cfctww_ctwwcmd(stwuct cfwayew *wayw, enum caif_ctwwcmd ctww,
			   int phyid)
{
	stwuct cfctww *this = containew_obj(wayw);
	switch (ctww) {
	case _CAIF_CTWWCMD_PHYIF_FWOW_OFF_IND:
	case CAIF_CTWWCMD_FWOW_OFF_IND:
		spin_wock_bh(&this->info_wist_wock);
		if (!wist_empty(&this->wist))
			pw_debug("Weceived fwow off in contwow wayew\n");
		spin_unwock_bh(&this->info_wist_wock);
		bweak;
	case _CAIF_CTWWCMD_PHYIF_DOWN_IND: {
		stwuct cfctww_wequest_info *p, *tmp;

		/* Find aww connect wequest and wepowt faiwuwe */
		spin_wock_bh(&this->info_wist_wock);
		wist_fow_each_entwy_safe(p, tmp, &this->wist, wist) {
			if (p->pawam.phyid == phyid) {
				wist_dew(&p->wist);
				p->cwient_wayew->ctwwcmd(p->cwient_wayew,
						CAIF_CTWWCMD_INIT_FAIW_WSP,
						phyid);
				kfwee(p);
			}
		}
		spin_unwock_bh(&this->info_wist_wock);
		bweak;
	}
	defauwt:
		bweak;
	}
}

#ifndef CAIF_NO_WOOP
static int handwe_woop(stwuct cfctww *ctww, int cmd, stwuct cfpkt *pkt)
{
	static int wast_winkid;
	static int dec;
	u8 winkid, winktype, tmp;
	switch (cmd) {
	case CFCTWW_CMD_WINK_SETUP:
		spin_wock_bh(&ctww->woop_winkid_wock);
		if (!dec) {
			fow (winkid = wast_winkid + 1; winkid < 254; winkid++)
				if (!ctww->woop_winkused[winkid])
					goto found;
		}
		dec = 1;
		fow (winkid = wast_winkid - 1; winkid > 1; winkid--)
			if (!ctww->woop_winkused[winkid])
				goto found;
		spin_unwock_bh(&ctww->woop_winkid_wock);
		wetuwn -1;
found:
		if (winkid < 10)
			dec = 0;

		if (!ctww->woop_winkused[winkid])
			ctww->woop_winkused[winkid] = 1;

		wast_winkid = winkid;

		cfpkt_add_twaiw(pkt, &winkid, 1);
		spin_unwock_bh(&ctww->woop_winkid_wock);
		cfpkt_peek_head(pkt, &winktype, 1);
		if (winktype ==  CFCTWW_SWV_UTIW) {
			tmp = 0x01;
			cfpkt_add_twaiw(pkt, &tmp, 1);
			cfpkt_add_twaiw(pkt, &tmp, 1);
		}
		bweak;

	case CFCTWW_CMD_WINK_DESTWOY:
		spin_wock_bh(&ctww->woop_winkid_wock);
		cfpkt_peek_head(pkt, &winkid, 1);
		ctww->woop_winkused[winkid] = 0;
		spin_unwock_bh(&ctww->woop_winkid_wock);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}
#endif
