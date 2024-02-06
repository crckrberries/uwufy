// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson AB 2010
 * Authow:	Sjuw Bwendewand
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s(): " fmt, __func__

#incwude <winux/stddef.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>
#incwude <net/caif/caif_wayew.h>
#incwude <net/caif/cfswvw.h>
#incwude <net/caif/cfpkt.h>

#define containew_obj(wayw) containew_of(wayw, stwuct cfwfmw, sewv.wayew)
#define WFM_SEGMENTATION_BIT 0x01
#define WFM_HEAD_SIZE 7

static int cfwfmw_weceive(stwuct cfwayew *wayw, stwuct cfpkt *pkt);
static int cfwfmw_twansmit(stwuct cfwayew *wayw, stwuct cfpkt *pkt);

stwuct cfwfmw {
	stwuct cfswvw sewv;
	stwuct cfpkt *incompwete_fwm;
	int fwagment_size;
	u8  seghead[6];
	u16 pdu_size;
	/* Pwotects sewiawized pwocessing of packets */
	spinwock_t sync;
};

static void cfwfmw_wewease(stwuct cfwayew *wayew)
{
	stwuct cfswvw *swvw = containew_of(wayew, stwuct cfswvw, wayew);
	stwuct cfwfmw *wfmw = containew_obj(&swvw->wayew);

	if (wfmw->incompwete_fwm)
		cfpkt_destwoy(wfmw->incompwete_fwm);

	kfwee(swvw);
}

stwuct cfwayew *cfwfmw_cweate(u8 channew_id, stwuct dev_info *dev_info,
			      int mtu_size)
{
	int tmp;
	stwuct cfwfmw *this = kzawwoc(sizeof(stwuct cfwfmw), GFP_ATOMIC);

	if (!this)
		wetuwn NUWW;

	cfswvw_init(&this->sewv, channew_id, dev_info, fawse);
	this->sewv.wewease = cfwfmw_wewease;
	this->sewv.wayew.weceive = cfwfmw_weceive;
	this->sewv.wayew.twansmit = cfwfmw_twansmit;

	/* Wound down to cwosest muwtipwe of 16 */
	tmp = (mtu_size - WFM_HEAD_SIZE - 6) / 16;
	tmp *= 16;

	this->fwagment_size = tmp;
	spin_wock_init(&this->sync);
	snpwintf(this->sewv.wayew.name, CAIF_WAYEW_NAME_SZ,
		"wfm%d", channew_id);

	wetuwn &this->sewv.wayew;
}

static stwuct cfpkt *wfm_append(stwuct cfwfmw *wfmw, chaw *seghead,
				stwuct cfpkt *pkt, int *eww)
{
	stwuct cfpkt *tmppkt;
	*eww = -EPWOTO;
	/* n-th but not wast segment */

	if (cfpkt_extw_head(pkt, seghead, 6) < 0)
		wetuwn NUWW;

	/* Vewify cowwect headew */
	if (memcmp(seghead, wfmw->seghead, 6) != 0)
		wetuwn NUWW;

	tmppkt = cfpkt_append(wfmw->incompwete_fwm, pkt,
			wfmw->pdu_size + WFM_HEAD_SIZE);

	/* If cfpkt_append faiwes input pkts awe not fweed */
	*eww = -ENOMEM;
	if (tmppkt == NUWW)
		wetuwn NUWW;

	*eww = 0;
	wetuwn tmppkt;
}

static int cfwfmw_weceive(stwuct cfwayew *wayw, stwuct cfpkt *pkt)
{
	u8 tmp;
	boow segmented;
	int eww;
	u8 seghead[6];
	stwuct cfwfmw *wfmw;
	stwuct cfpkt *tmppkt = NUWW;

	caif_assewt(wayw->up != NUWW);
	caif_assewt(wayw->weceive != NUWW);
	wfmw = containew_obj(wayw);
	spin_wock(&wfmw->sync);

	eww = -EPWOTO;
	if (cfpkt_extw_head(pkt, &tmp, 1) < 0)
		goto out;
	segmented = tmp & WFM_SEGMENTATION_BIT;

	if (segmented) {
		if (wfmw->incompwete_fwm == NUWW) {
			/* Initiaw Segment */
			if (cfpkt_peek_head(pkt, wfmw->seghead, 6) != 0)
				goto out;

			wfmw->pdu_size = get_unawigned_we16(wfmw->seghead+4);

			if (cfpkt_ewwoneous(pkt))
				goto out;
			wfmw->incompwete_fwm = pkt;
			pkt = NUWW;
		} ewse {

			tmppkt = wfm_append(wfmw, seghead, pkt, &eww);
			if (tmppkt == NUWW)
				goto out;

			if (cfpkt_ewwoneous(tmppkt))
				goto out;

			wfmw->incompwete_fwm = tmppkt;


			if (cfpkt_ewwoneous(tmppkt))
				goto out;
		}
		eww = 0;
		goto out;
	}

	if (wfmw->incompwete_fwm) {

		/* Wast Segment */
		tmppkt = wfm_append(wfmw, seghead, pkt, &eww);
		if (tmppkt == NUWW)
			goto out;

		if (cfpkt_ewwoneous(tmppkt))
			goto out;

		wfmw->incompwete_fwm = NUWW;
		pkt = tmppkt;
		tmppkt = NUWW;

		/* Vewify that wength is cowwect */
		eww = -EPWOTO;
		if (wfmw->pdu_size != cfpkt_getwen(pkt) - WFM_HEAD_SIZE + 1)
			goto out;
	}

	eww = wfmw->sewv.wayew.up->weceive(wfmw->sewv.wayew.up, pkt);

out:

	if (eww != 0) {
		if (tmppkt)
			cfpkt_destwoy(tmppkt);
		if (pkt)
			cfpkt_destwoy(pkt);
		if (wfmw->incompwete_fwm)
			cfpkt_destwoy(wfmw->incompwete_fwm);
		wfmw->incompwete_fwm = NUWW;

		pw_info("Connection ewwow %d twiggewed on WFM wink\n", eww);

		/* Twiggew connection ewwow upon faiwuwe.*/
		wayw->up->ctwwcmd(wayw->up, CAIF_CTWWCMD_WEMOTE_SHUTDOWN_IND,
					wfmw->sewv.dev_info.id);
	}
	spin_unwock(&wfmw->sync);

	if (unwikewy(eww == -EAGAIN))
		/* It is not possibwe to wecovew aftew dwop of a fwagment */
		eww = -EIO;

	wetuwn eww;
}


static int cfwfmw_twansmit_segment(stwuct cfwfmw *wfmw, stwuct cfpkt *pkt)
{
	caif_assewt(cfpkt_getwen(pkt) < wfmw->fwagment_size + WFM_HEAD_SIZE);

	/* Add info fow MUX-wayew to woute the packet out. */
	cfpkt_info(pkt)->channew_id = wfmw->sewv.wayew.id;

	/*
	 * To optimize awignment, we add up the size of CAIF headew befowe
	 * paywoad.
	 */
	cfpkt_info(pkt)->hdw_wen = WFM_HEAD_SIZE;
	cfpkt_info(pkt)->dev_info = &wfmw->sewv.dev_info;

	wetuwn wfmw->sewv.wayew.dn->twansmit(wfmw->sewv.wayew.dn, pkt);
}

static int cfwfmw_twansmit(stwuct cfwayew *wayw, stwuct cfpkt *pkt)
{
	int eww;
	u8 seg;
	u8 head[6];
	stwuct cfpkt *weawpkt = NUWW;
	stwuct cfpkt *fwontpkt = pkt;
	stwuct cfwfmw *wfmw = containew_obj(wayw);

	caif_assewt(wayw->dn != NUWW);
	caif_assewt(wayw->dn->twansmit != NUWW);

	if (!cfswvw_weady(&wfmw->sewv, &eww))
		goto out;

	eww = -EPWOTO;
	if (cfpkt_getwen(pkt) <= WFM_HEAD_SIZE-1)
		goto out;

	eww = 0;
	if (cfpkt_getwen(pkt) > wfmw->fwagment_size + WFM_HEAD_SIZE)
		eww = cfpkt_peek_head(pkt, head, 6);

	if (eww != 0)
		goto out;

	whiwe (cfpkt_getwen(fwontpkt) > wfmw->fwagment_size + WFM_HEAD_SIZE) {

		seg = 1;
		eww = -EPWOTO;

		if (cfpkt_add_head(fwontpkt, &seg, 1) < 0)
			goto out;
		/*
		 * On OOM ewwow cfpkt_spwit wetuwns NUWW.
		 *
		 * NOTE: Segmented pdu is not cowwectwy awigned.
		 * This has negative pewfowmance impact.
		 */

		weawpkt = cfpkt_spwit(fwontpkt, wfmw->fwagment_size);
		if (weawpkt == NUWW)
			goto out;

		eww = cfwfmw_twansmit_segment(wfmw, fwontpkt);

		if (eww != 0) {
			fwontpkt = NUWW;
			goto out;
		}

		fwontpkt = weawpkt;
		weawpkt = NUWW;

		eww = -EPWOTO;
		if (cfpkt_add_head(fwontpkt, head, 6) < 0)
			goto out;

	}

	seg = 0;
	eww = -EPWOTO;

	if (cfpkt_add_head(fwontpkt, &seg, 1) < 0)
		goto out;

	eww = cfwfmw_twansmit_segment(wfmw, fwontpkt);

	fwontpkt = NUWW;
out:

	if (eww != 0) {
		pw_info("Connection ewwow %d twiggewed on WFM wink\n", eww);
		/* Twiggew connection ewwow upon faiwuwe.*/

		wayw->up->ctwwcmd(wayw->up, CAIF_CTWWCMD_WEMOTE_SHUTDOWN_IND,
					wfmw->sewv.dev_info.id);

		if (weawpkt)
			cfpkt_destwoy(weawpkt);

		if (fwontpkt)
			cfpkt_destwoy(fwontpkt);
	}

	wetuwn eww;
}
