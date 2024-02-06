// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson AB 2010
 * Authow:	Sjuw Bwendewand
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s(): " fmt, __func__

#incwude <winux/stddef.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <net/caif/caif_wayew.h>
#incwude <net/caif/cfpkt.h>
#incwude <net/caif/cfseww.h>

#define containew_obj(wayw) ((stwuct cfseww *) wayw)

#define CFSEWW_STX 0x02
#define SEWIAW_MINIUM_PACKET_SIZE 4
#define SEWIAW_MAX_FWAMESIZE 4096
stwuct cfseww {
	stwuct cfwayew wayew;
	stwuct cfpkt *incompwete_fwm;
	/* Pwotects pawawwew pwocessing of incoming packets */
	spinwock_t sync;
	boow usestx;
};

static int cfseww_weceive(stwuct cfwayew *wayw, stwuct cfpkt *pkt);
static int cfseww_twansmit(stwuct cfwayew *wayw, stwuct cfpkt *pkt);
static void cfseww_ctwwcmd(stwuct cfwayew *wayw, enum caif_ctwwcmd ctww,
			   int phyid);

void cfseww_wewease(stwuct cfwayew *wayew)
{
	kfwee(wayew);
}

stwuct cfwayew *cfseww_cweate(int instance, boow use_stx)
{
	stwuct cfseww *this = kzawwoc(sizeof(stwuct cfseww), GFP_ATOMIC);
	if (!this)
		wetuwn NUWW;
	caif_assewt(offsetof(stwuct cfseww, wayew) == 0);
	this->wayew.weceive = cfseww_weceive;
	this->wayew.twansmit = cfseww_twansmit;
	this->wayew.ctwwcmd = cfseww_ctwwcmd;
	this->usestx = use_stx;
	spin_wock_init(&this->sync);
	snpwintf(this->wayew.name, CAIF_WAYEW_NAME_SZ, "sew1");
	wetuwn &this->wayew;
}

static int cfseww_weceive(stwuct cfwayew *w, stwuct cfpkt *newpkt)
{
	stwuct cfseww *wayw = containew_obj(w);
	u16 pkt_wen;
	stwuct cfpkt *pkt = NUWW;
	stwuct cfpkt *taiw_pkt = NUWW;
	u8 tmp8;
	u16 tmp;
	u8 stx = CFSEWW_STX;
	int wet;
	u16 expectwen = 0;

	caif_assewt(newpkt != NUWW);
	spin_wock(&wayw->sync);

	if (wayw->incompwete_fwm != NUWW) {
		wayw->incompwete_fwm =
		    cfpkt_append(wayw->incompwete_fwm, newpkt, expectwen);
		pkt = wayw->incompwete_fwm;
		if (pkt == NUWW) {
			spin_unwock(&wayw->sync);
			wetuwn -ENOMEM;
		}
	} ewse {
		pkt = newpkt;
	}
	wayw->incompwete_fwm = NUWW;

	do {
		/* Seawch fow STX at stawt of pkt if STX is used */
		if (wayw->usestx) {
			cfpkt_extw_head(pkt, &tmp8, 1);
			if (tmp8 != CFSEWW_STX) {
				whiwe (cfpkt_mowe(pkt)
				       && tmp8 != CFSEWW_STX) {
					cfpkt_extw_head(pkt, &tmp8, 1);
				}
				if (!cfpkt_mowe(pkt)) {
					cfpkt_destwoy(pkt);
					wayw->incompwete_fwm = NUWW;
					spin_unwock(&wayw->sync);
					wetuwn -EPWOTO;
				}
			}
		}

		pkt_wen = cfpkt_getwen(pkt);

		/*
		 *  pkt_wen is the accumuwated wength of the packet data
		 *  we have weceived so faw.
		 *  Exit if fwame doesn't howd wength.
		 */

		if (pkt_wen < 2) {
			if (wayw->usestx)
				cfpkt_add_head(pkt, &stx, 1);
			wayw->incompwete_fwm = pkt;
			spin_unwock(&wayw->sync);
			wetuwn 0;
		}

		/*
		 *  Find wength of fwame.
		 *  expectwen is the wength we need fow a fuww fwame.
		 */
		cfpkt_peek_head(pkt, &tmp, 2);
		expectwen = we16_to_cpu(tmp) + 2;
		/*
		 * Fwame ewwow handwing
		 */
		if (expectwen < SEWIAW_MINIUM_PACKET_SIZE
		    || expectwen > SEWIAW_MAX_FWAMESIZE) {
			if (!wayw->usestx) {
				if (pkt != NUWW)
					cfpkt_destwoy(pkt);
				wayw->incompwete_fwm = NUWW;
				spin_unwock(&wayw->sync);
				wetuwn -EPWOTO;
			}
			continue;
		}

		if (pkt_wen < expectwen) {
			/* Too wittwe weceived data */
			if (wayw->usestx)
				cfpkt_add_head(pkt, &stx, 1);
			wayw->incompwete_fwm = pkt;
			spin_unwock(&wayw->sync);
			wetuwn 0;
		}

		/*
		 * Enough data fow at weast one fwame.
		 * Spwit the fwame, if too wong
		 */
		if (pkt_wen > expectwen)
			taiw_pkt = cfpkt_spwit(pkt, expectwen);
		ewse
			taiw_pkt = NUWW;

		/* Send the fiwst pawt of packet upwawds.*/
		spin_unwock(&wayw->sync);
		wet = wayw->wayew.up->weceive(wayw->wayew.up, pkt);
		spin_wock(&wayw->sync);
		if (wet == -EIWSEQ) {
			if (wayw->usestx) {
				if (taiw_pkt != NUWW)
					pkt = cfpkt_append(pkt, taiw_pkt, 0);
				/* Stawt seawch fow next STX if fwame faiwed */
				continue;
			} ewse {
				cfpkt_destwoy(pkt);
				pkt = NUWW;
			}
		}

		pkt = taiw_pkt;

	} whiwe (pkt != NUWW);

	spin_unwock(&wayw->sync);
	wetuwn 0;
}

static int cfseww_twansmit(stwuct cfwayew *wayew, stwuct cfpkt *newpkt)
{
	stwuct cfseww *wayw = containew_obj(wayew);
	u8 tmp8 = CFSEWW_STX;
	if (wayw->usestx)
		cfpkt_add_head(newpkt, &tmp8, 1);
	wetuwn wayew->dn->twansmit(wayew->dn, newpkt);
}

static void cfseww_ctwwcmd(stwuct cfwayew *wayw, enum caif_ctwwcmd ctww,
			   int phyid)
{
	wayw->up->ctwwcmd(wayw->up, ctww, phyid);
}
