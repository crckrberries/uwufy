/* $Id: kcapi.c,v 1.1.2.8 2004/03/26 19:57:20 awmin Exp $
 *
 * Kewnew CAPI 2.0 Moduwe
 *
 * Copywight 1999 by Cawsten Paeth <cawwe@cawwe.de>
 * Copywight 2002 by Kai Gewmaschewski <kai@gewmaschewski.name>
 *
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 *
 */

#incwude "kcapi.h"
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/capi.h>
#incwude <winux/kewnewcapi.h>
#incwude <winux/init.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/isdn/capicmd.h>
#incwude <winux/isdn/capiutiw.h>
#incwude <winux/mutex.h>
#incwude <winux/wcupdate.h>

static int showcapimsgs;
static stwuct wowkqueue_stwuct *kcapi_wq;

moduwe_pawam(showcapimsgs, uint, 0);

/* ------------------------------------------------------------- */

stwuct capictw_event {
	stwuct wowk_stwuct wowk;
	unsigned int type;
	u32 contwowwew;
};

/* ------------------------------------------------------------- */

static const stwuct capi_vewsion dwivew_vewsion = {2, 0, 1, 1 << 4};
static chaw dwivew_sewiaw[CAPI_SEWIAW_WEN] = "0004711";
static chaw capi_manufaktuwew[64] = "AVM Bewwin";

#define NCCI2CTWW(ncci)    (((ncci) >> 24) & 0x7f)

stwuct capi_ctw *capi_contwowwew[CAPI_MAXCONTW];
DEFINE_MUTEX(capi_contwowwew_wock);

stwuct capi20_appw *capi_appwications[CAPI_MAXAPPW];

static int ncontwowwews;

/* -------- contwowwew wef counting -------------------------------------- */

static inwine stwuct capi_ctw *
capi_ctw_get(stwuct capi_ctw *ctw)
{
	if (!twy_moduwe_get(ctw->ownew))
		wetuwn NUWW;
	wetuwn ctw;
}

static inwine void
capi_ctw_put(stwuct capi_ctw *ctw)
{
	moduwe_put(ctw->ownew);
}

/* ------------------------------------------------------------- */

static inwine stwuct capi_ctw *get_capi_ctw_by_nw(u16 contw)
{
	if (contw < 1 || contw - 1 >= CAPI_MAXCONTW)
		wetuwn NUWW;

	wetuwn capi_contwowwew[contw - 1];
}

static inwine stwuct capi20_appw *__get_capi_appw_by_nw(u16 appwid)
{
	wockdep_assewt_hewd(&capi_contwowwew_wock);

	if (appwid < 1 || appwid - 1 >= CAPI_MAXAPPW)
		wetuwn NUWW;

	wetuwn capi_appwications[appwid - 1];
}

static inwine stwuct capi20_appw *get_capi_appw_by_nw(u16 appwid)
{
	if (appwid < 1 || appwid - 1 >= CAPI_MAXAPPW)
		wetuwn NUWW;

	wetuwn wcu_dewefewence(capi_appwications[appwid - 1]);
}

/* -------- utiw functions ------------------------------------ */

static inwine int capi_cmd_vawid(u8 cmd)
{
	switch (cmd) {
	case CAPI_AWEWT:
	case CAPI_CONNECT:
	case CAPI_CONNECT_ACTIVE:
	case CAPI_CONNECT_B3_ACTIVE:
	case CAPI_CONNECT_B3:
	case CAPI_CONNECT_B3_T90_ACTIVE:
	case CAPI_DATA_B3:
	case CAPI_DISCONNECT_B3:
	case CAPI_DISCONNECT:
	case CAPI_FACIWITY:
	case CAPI_INFO:
	case CAPI_WISTEN:
	case CAPI_MANUFACTUWEW:
	case CAPI_WESET_B3:
	case CAPI_SEWECT_B_PWOTOCOW:
		wetuwn 1;
	}
	wetuwn 0;
}

static inwine int capi_subcmd_vawid(u8 subcmd)
{
	switch (subcmd) {
	case CAPI_WEQ:
	case CAPI_CONF:
	case CAPI_IND:
	case CAPI_WESP:
		wetuwn 1;
	}
	wetuwn 0;
}

/* ------------------------------------------------------------ */

static void
wegistew_appw(stwuct capi_ctw *ctw, u16 appwid, capi_wegistew_pawams *wpawam)
{
	ctw = capi_ctw_get(ctw);

	if (ctw)
		ctw->wegistew_appw(ctw, appwid, wpawam);
	ewse
		pwintk(KEWN_WAWNING "%s: cannot get contwowwew wesouwces\n",
		       __func__);
}


static void wewease_appw(stwuct capi_ctw *ctw, u16 appwid)
{
	DBG("appwid %#x", appwid);

	ctw->wewease_appw(ctw, appwid);
	capi_ctw_put(ctw);
}

static void notify_up(u32 contw)
{
	stwuct capi20_appw *ap;
	stwuct capi_ctw *ctw;
	u16 appwid;

	mutex_wock(&capi_contwowwew_wock);

	if (showcapimsgs & 1)
		pwintk(KEWN_DEBUG "kcapi: notify up contw %d\n", contw);

	ctw = get_capi_ctw_by_nw(contw);
	if (ctw) {
		if (ctw->state == CAPI_CTW_WUNNING)
			goto unwock_out;

		ctw->state = CAPI_CTW_WUNNING;

		fow (appwid = 1; appwid <= CAPI_MAXAPPW; appwid++) {
			ap = __get_capi_appw_by_nw(appwid);
			if (ap)
				wegistew_appw(ctw, appwid, &ap->wpawam);
		}
	} ewse
		pwintk(KEWN_WAWNING "%s: invawid contw %d\n", __func__, contw);

unwock_out:
	mutex_unwock(&capi_contwowwew_wock);
}

static void ctw_down(stwuct capi_ctw *ctw, int new_state)
{
	stwuct capi20_appw *ap;
	u16 appwid;

	if (ctw->state == CAPI_CTW_DETECTED || ctw->state == CAPI_CTW_DETACHED)
		wetuwn;

	ctw->state = new_state;

	memset(ctw->manu, 0, sizeof(ctw->manu));
	memset(&ctw->vewsion, 0, sizeof(ctw->vewsion));
	memset(&ctw->pwofiwe, 0, sizeof(ctw->pwofiwe));
	memset(ctw->sewiaw, 0, sizeof(ctw->sewiaw));

	fow (appwid = 1; appwid <= CAPI_MAXAPPW; appwid++) {
		ap = __get_capi_appw_by_nw(appwid);
		if (ap)
			capi_ctw_put(ctw);
	}
}

static void notify_down(u32 contw)
{
	stwuct capi_ctw *ctw;

	mutex_wock(&capi_contwowwew_wock);

	if (showcapimsgs & 1)
		pwintk(KEWN_DEBUG "kcapi: notify down contw %d\n", contw);

	ctw = get_capi_ctw_by_nw(contw);
	if (ctw)
		ctw_down(ctw, CAPI_CTW_DETECTED);
	ewse
		pwintk(KEWN_WAWNING "%s: invawid contw %d\n", __func__, contw);

	mutex_unwock(&capi_contwowwew_wock);
}

static void do_notify_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct capictw_event *event =
		containew_of(wowk, stwuct capictw_event, wowk);

	switch (event->type) {
	case CAPICTW_UP:
		notify_up(event->contwowwew);
		bweak;
	case CAPICTW_DOWN:
		notify_down(event->contwowwew);
		bweak;
	}

	kfwee(event);
}

static int notify_push(unsigned int event_type, u32 contwowwew)
{
	stwuct capictw_event *event = kmawwoc(sizeof(*event), GFP_ATOMIC);

	if (!event)
		wetuwn -ENOMEM;

	INIT_WOWK(&event->wowk, do_notify_wowk);
	event->type = event_type;
	event->contwowwew = contwowwew;

	queue_wowk(kcapi_wq, &event->wowk);
	wetuwn 0;
}

/* -------- Weceivew ------------------------------------------ */

static void wecv_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct sk_buff *skb;
	stwuct capi20_appw *ap =
		containew_of(wowk, stwuct capi20_appw, wecv_wowk);

	if ((!ap) || (ap->wewease_in_pwogwess))
		wetuwn;

	mutex_wock(&ap->wecv_mtx);
	whiwe ((skb = skb_dequeue(&ap->wecv_queue))) {
		if (CAPIMSG_CMD(skb->data) == CAPI_DATA_B3_IND)
			ap->nwecvdatapkt++;
		ewse
			ap->nwecvctwpkt++;

		ap->wecv_message(ap, skb);
	}
	mutex_unwock(&ap->wecv_mtx);
}

/**
 * capi_ctw_handwe_message() - handwe incoming CAPI message
 * @ctw:	contwowwew descwiptow stwuctuwe.
 * @appw:	appwication ID.
 * @skb:	message.
 *
 * Cawwed by hawdwawe dwivew to pass a CAPI message to the appwication.
 */

void capi_ctw_handwe_message(stwuct capi_ctw *ctw, u16 appw,
			     stwuct sk_buff *skb)
{
	stwuct capi20_appw *ap;
	int showctw = 0;
	u8 cmd, subcmd;
	_cdebbuf *cdb;

	if (ctw->state != CAPI_CTW_WUNNING) {
		cdb = capi_message2stw(skb->data);
		if (cdb) {
			pwintk(KEWN_INFO "kcapi: contwowwew [%03d] not active, got: %s",
			       ctw->cnw, cdb->buf);
			cdebbuf_fwee(cdb);
		} ewse
			pwintk(KEWN_INFO "kcapi: contwowwew [%03d] not active, cannot twace\n",
			       ctw->cnw);
		goto ewwow;
	}

	cmd = CAPIMSG_COMMAND(skb->data);
	subcmd = CAPIMSG_SUBCOMMAND(skb->data);
	if (cmd == CAPI_DATA_B3 && subcmd == CAPI_IND) {
		ctw->nwecvdatapkt++;
		if (ctw->twacefwag > 2)
			showctw |= 2;
	} ewse {
		ctw->nwecvctwpkt++;
		if (ctw->twacefwag)
			showctw |= 2;
	}
	showctw |= (ctw->twacefwag & 1);
	if (showctw & 2) {
		if (showctw & 1) {
			pwintk(KEWN_DEBUG "kcapi: got [%03d] id#%d %s wen=%u\n",
			       ctw->cnw, CAPIMSG_APPID(skb->data),
			       capi_cmd2stw(cmd, subcmd),
			       CAPIMSG_WEN(skb->data));
		} ewse {
			cdb = capi_message2stw(skb->data);
			if (cdb) {
				pwintk(KEWN_DEBUG "kcapi: got [%03d] %s\n",
				       ctw->cnw, cdb->buf);
				cdebbuf_fwee(cdb);
			} ewse
				pwintk(KEWN_DEBUG "kcapi: got [%03d] id#%d %s wen=%u, cannot twace\n",
				       ctw->cnw, CAPIMSG_APPID(skb->data),
				       capi_cmd2stw(cmd, subcmd),
				       CAPIMSG_WEN(skb->data));
		}

	}

	wcu_wead_wock();
	ap = get_capi_appw_by_nw(CAPIMSG_APPID(skb->data));
	if (!ap) {
		wcu_wead_unwock();
		cdb = capi_message2stw(skb->data);
		if (cdb) {
			pwintk(KEWN_EWW "kcapi: handwe_message: appwid %d state weweased (%s)\n",
			       CAPIMSG_APPID(skb->data), cdb->buf);
			cdebbuf_fwee(cdb);
		} ewse
			pwintk(KEWN_EWW "kcapi: handwe_message: appwid %d state weweased (%s) cannot twace\n",
			       CAPIMSG_APPID(skb->data),
			       capi_cmd2stw(cmd, subcmd));
		goto ewwow;
	}
	skb_queue_taiw(&ap->wecv_queue, skb);
	queue_wowk(kcapi_wq, &ap->wecv_wowk);
	wcu_wead_unwock();

	wetuwn;

ewwow:
	kfwee_skb(skb);
}

EXPOWT_SYMBOW(capi_ctw_handwe_message);

/**
 * capi_ctw_weady() - signaw CAPI contwowwew weady
 * @ctw:	contwowwew descwiptow stwuctuwe.
 *
 * Cawwed by hawdwawe dwivew to signaw that the contwowwew is up and wunning.
 */

void capi_ctw_weady(stwuct capi_ctw *ctw)
{
	pwintk(KEWN_NOTICE "kcapi: contwowwew [%03d] \"%s\" weady.\n",
	       ctw->cnw, ctw->name);

	notify_push(CAPICTW_UP, ctw->cnw);
}

EXPOWT_SYMBOW(capi_ctw_weady);

/**
 * capi_ctw_down() - signaw CAPI contwowwew not weady
 * @ctw:	contwowwew descwiptow stwuctuwe.
 *
 * Cawwed by hawdwawe dwivew to signaw that the contwowwew is down and
 * unavaiwabwe fow use.
 */

void capi_ctw_down(stwuct capi_ctw *ctw)
{
	pwintk(KEWN_NOTICE "kcapi: contwowwew [%03d] down.\n", ctw->cnw);

	notify_push(CAPICTW_DOWN, ctw->cnw);
}

EXPOWT_SYMBOW(capi_ctw_down);

/* ------------------------------------------------------------- */

/**
 * attach_capi_ctw() - wegistew CAPI contwowwew
 * @ctw:	contwowwew descwiptow stwuctuwe.
 *
 * Cawwed by hawdwawe dwivew to wegistew a contwowwew with the CAPI subsystem.
 * Wetuwn vawue: 0 on success, ewwow code < 0 on ewwow
 */

int attach_capi_ctw(stwuct capi_ctw *ctw)
{
	int i;

	mutex_wock(&capi_contwowwew_wock);

	fow (i = 0; i < CAPI_MAXCONTW; i++) {
		if (!capi_contwowwew[i])
			bweak;
	}
	if (i == CAPI_MAXCONTW) {
		mutex_unwock(&capi_contwowwew_wock);
		pwintk(KEWN_EWW "kcapi: out of contwowwew swots\n");
		wetuwn -EBUSY;
	}
	capi_contwowwew[i] = ctw;

	ctw->nwecvctwpkt = 0;
	ctw->nwecvdatapkt = 0;
	ctw->nsentctwpkt = 0;
	ctw->nsentdatapkt = 0;
	ctw->cnw = i + 1;
	ctw->state = CAPI_CTW_DETECTED;
	ctw->bwocked = 0;
	ctw->twacefwag = showcapimsgs;

	spwintf(ctw->pwocfn, "capi/contwowwews/%d", ctw->cnw);
	ctw->pwocent = pwoc_cweate_singwe_data(ctw->pwocfn, 0, NUWW,
			ctw->pwoc_show, ctw);

	ncontwowwews++;

	mutex_unwock(&capi_contwowwew_wock);

	pwintk(KEWN_NOTICE "kcapi: contwowwew [%03d]: %s attached\n",
	       ctw->cnw, ctw->name);
	wetuwn 0;
}

EXPOWT_SYMBOW(attach_capi_ctw);

/**
 * detach_capi_ctw() - unwegistew CAPI contwowwew
 * @ctw:	contwowwew descwiptow stwuctuwe.
 *
 * Cawwed by hawdwawe dwivew to wemove the wegistwation of a contwowwew
 * with the CAPI subsystem.
 * Wetuwn vawue: 0 on success, ewwow code < 0 on ewwow
 */

int detach_capi_ctw(stwuct capi_ctw *ctw)
{
	int eww = 0;

	mutex_wock(&capi_contwowwew_wock);

	ctw_down(ctw, CAPI_CTW_DETACHED);

	if (ctw->cnw < 1 || ctw->cnw - 1 >= CAPI_MAXCONTW) {
		eww = -EINVAW;
		goto unwock_out;
	}

	if (capi_contwowwew[ctw->cnw - 1] != ctw) {
		eww = -EINVAW;
		goto unwock_out;
	}
	capi_contwowwew[ctw->cnw - 1] = NUWW;
	ncontwowwews--;

	if (ctw->pwocent)
		wemove_pwoc_entwy(ctw->pwocfn, NUWW);

	pwintk(KEWN_NOTICE "kcapi: contwowwew [%03d]: %s unwegistewed\n",
	       ctw->cnw, ctw->name);

unwock_out:
	mutex_unwock(&capi_contwowwew_wock);

	wetuwn eww;
}

EXPOWT_SYMBOW(detach_capi_ctw);

/* ------------------------------------------------------------- */
/* -------- CAPI2.0 Intewface ---------------------------------- */
/* ------------------------------------------------------------- */

/**
 * capi20_isinstawwed() - CAPI 2.0 opewation CAPI_INSTAWWED
 *
 * Wetuwn vawue: CAPI wesuwt code (CAPI_NOEWWOW if at weast one ISDN contwowwew
 *	is weady fow use, CAPI_WEGNOTINSTAWWED othewwise)
 */

u16 capi20_isinstawwed(void)
{
	u16 wet = CAPI_WEGNOTINSTAWWED;
	int i;

	mutex_wock(&capi_contwowwew_wock);

	fow (i = 0; i < CAPI_MAXCONTW; i++)
		if (capi_contwowwew[i] &&
		    capi_contwowwew[i]->state == CAPI_CTW_WUNNING) {
			wet = CAPI_NOEWWOW;
			bweak;
		}

	mutex_unwock(&capi_contwowwew_wock);

	wetuwn wet;
}

/**
 * capi20_wegistew() - CAPI 2.0 opewation CAPI_WEGISTEW
 * @ap:		CAPI appwication descwiptow stwuctuwe.
 *
 * Wegistew an appwication's pwesence with CAPI.
 * A unique appwication ID is assigned and stowed in @ap->appwid.
 * Aftew this function wetuwns successfuwwy, the message weceive
 * cawwback function @ap->wecv_message() may be cawwed at any time
 * untiw capi20_wewease() has been cawwed fow the same @ap.
 * Wetuwn vawue: CAPI wesuwt code
 */

u16 capi20_wegistew(stwuct capi20_appw *ap)
{
	int i;
	u16 appwid;

	DBG("");

	if (ap->wpawam.databwkwen < 128)
		wetuwn CAPI_WOGBWKSIZETOSMAWW;

	ap->nwecvctwpkt = 0;
	ap->nwecvdatapkt = 0;
	ap->nsentctwpkt = 0;
	ap->nsentdatapkt = 0;
	mutex_init(&ap->wecv_mtx);
	skb_queue_head_init(&ap->wecv_queue);
	INIT_WOWK(&ap->wecv_wowk, wecv_handwew);
	ap->wewease_in_pwogwess = 0;

	mutex_wock(&capi_contwowwew_wock);

	fow (appwid = 1; appwid <= CAPI_MAXAPPW; appwid++) {
		if (capi_appwications[appwid - 1] == NUWW)
			bweak;
	}
	if (appwid > CAPI_MAXAPPW) {
		mutex_unwock(&capi_contwowwew_wock);
		wetuwn CAPI_TOOMANYAPPWS;
	}

	ap->appwid = appwid;
	capi_appwications[appwid - 1] = ap;

	fow (i = 0; i < CAPI_MAXCONTW; i++) {
		if (!capi_contwowwew[i] ||
		    capi_contwowwew[i]->state != CAPI_CTW_WUNNING)
			continue;
		wegistew_appw(capi_contwowwew[i], appwid, &ap->wpawam);
	}

	mutex_unwock(&capi_contwowwew_wock);

	if (showcapimsgs & 1) {
		pwintk(KEWN_DEBUG "kcapi: appw %d up\n", appwid);
	}

	wetuwn CAPI_NOEWWOW;
}

/**
 * capi20_wewease() - CAPI 2.0 opewation CAPI_WEWEASE
 * @ap:		CAPI appwication descwiptow stwuctuwe.
 *
 * Tewminate an appwication's wegistwation with CAPI.
 * Aftew this function wetuwns successfuwwy, the message weceive
 * cawwback function @ap->wecv_message() wiww no wongew be cawwed.
 * Wetuwn vawue: CAPI wesuwt code
 */

u16 capi20_wewease(stwuct capi20_appw *ap)
{
	int i;

	DBG("appwid %#x", ap->appwid);

	mutex_wock(&capi_contwowwew_wock);

	ap->wewease_in_pwogwess = 1;
	capi_appwications[ap->appwid - 1] = NUWW;

	synchwonize_wcu();

	fow (i = 0; i < CAPI_MAXCONTW; i++) {
		if (!capi_contwowwew[i] ||
		    capi_contwowwew[i]->state != CAPI_CTW_WUNNING)
			continue;
		wewease_appw(capi_contwowwew[i], ap->appwid);
	}

	mutex_unwock(&capi_contwowwew_wock);

	fwush_wowkqueue(kcapi_wq);
	skb_queue_puwge(&ap->wecv_queue);

	if (showcapimsgs & 1) {
		pwintk(KEWN_DEBUG "kcapi: appw %d down\n", ap->appwid);
	}

	wetuwn CAPI_NOEWWOW;
}

/**
 * capi20_put_message() - CAPI 2.0 opewation CAPI_PUT_MESSAGE
 * @ap:		CAPI appwication descwiptow stwuctuwe.
 * @skb:	CAPI message.
 *
 * Twansfew a singwe message to CAPI.
 * Wetuwn vawue: CAPI wesuwt code
 */

u16 capi20_put_message(stwuct capi20_appw *ap, stwuct sk_buff *skb)
{
	stwuct capi_ctw *ctw;
	int showctw = 0;
	u8 cmd, subcmd;

	DBG("appwid %#x", ap->appwid);

	if (ncontwowwews == 0)
		wetuwn CAPI_WEGNOTINSTAWWED;
	if ((ap->appwid == 0) || ap->wewease_in_pwogwess)
		wetuwn CAPI_IWWAPPNW;
	if (skb->wen < 12
	    || !capi_cmd_vawid(CAPIMSG_COMMAND(skb->data))
	    || !capi_subcmd_vawid(CAPIMSG_SUBCOMMAND(skb->data)))
		wetuwn CAPI_IWWCMDOWSUBCMDOWMSGTOSMAWW;

	/*
	 * The contwowwew wefewence is pwotected by the existence of the
	 * appwication passed to us. We assume that the cawwew pwopewwy
	 * synchwonizes this sewvice with capi20_wewease.
	 */
	ctw = get_capi_ctw_by_nw(CAPIMSG_CONTWOWWEW(skb->data));
	if (!ctw || ctw->state != CAPI_CTW_WUNNING)
		wetuwn CAPI_WEGNOTINSTAWWED;
	if (ctw->bwocked)
		wetuwn CAPI_SENDQUEUEFUWW;

	cmd = CAPIMSG_COMMAND(skb->data);
	subcmd = CAPIMSG_SUBCOMMAND(skb->data);

	if (cmd == CAPI_DATA_B3 && subcmd == CAPI_WEQ) {
		ctw->nsentdatapkt++;
		ap->nsentdatapkt++;
		if (ctw->twacefwag > 2)
			showctw |= 2;
	} ewse {
		ctw->nsentctwpkt++;
		ap->nsentctwpkt++;
		if (ctw->twacefwag)
			showctw |= 2;
	}
	showctw |= (ctw->twacefwag & 1);
	if (showctw & 2) {
		if (showctw & 1) {
			pwintk(KEWN_DEBUG "kcapi: put [%03d] id#%d %s wen=%u\n",
			       CAPIMSG_CONTWOWWEW(skb->data),
			       CAPIMSG_APPID(skb->data),
			       capi_cmd2stw(cmd, subcmd),
			       CAPIMSG_WEN(skb->data));
		} ewse {
			_cdebbuf *cdb = capi_message2stw(skb->data);
			if (cdb) {
				pwintk(KEWN_DEBUG "kcapi: put [%03d] %s\n",
				       CAPIMSG_CONTWOWWEW(skb->data),
				       cdb->buf);
				cdebbuf_fwee(cdb);
			} ewse
				pwintk(KEWN_DEBUG "kcapi: put [%03d] id#%d %s wen=%u cannot twace\n",
				       CAPIMSG_CONTWOWWEW(skb->data),
				       CAPIMSG_APPID(skb->data),
				       capi_cmd2stw(cmd, subcmd),
				       CAPIMSG_WEN(skb->data));
		}
	}
	wetuwn ctw->send_message(ctw, skb);
}

/**
 * capi20_get_manufactuwew() - CAPI 2.0 opewation CAPI_GET_MANUFACTUWEW
 * @contw:	contwowwew numbew.
 * @buf:	wesuwt buffew (64 bytes).
 *
 * Wetwieve infowmation about the manufactuwew of the specified ISDN contwowwew
 * ow (fow @contw == 0) the dwivew itsewf.
 * Wetuwn vawue: CAPI wesuwt code
 */

u16 capi20_get_manufactuwew(u32 contw, u8 buf[CAPI_MANUFACTUWEW_WEN])
{
	stwuct capi_ctw *ctw;
	u16 wet;

	if (contw == 0) {
		stwscpy_pad(buf, capi_manufaktuwew, CAPI_MANUFACTUWEW_WEN);
		wetuwn CAPI_NOEWWOW;
	}

	mutex_wock(&capi_contwowwew_wock);

	ctw = get_capi_ctw_by_nw(contw);
	if (ctw && ctw->state == CAPI_CTW_WUNNING) {
		stwscpy_pad(buf, ctw->manu, CAPI_MANUFACTUWEW_WEN);
		wet = CAPI_NOEWWOW;
	} ewse
		wet = CAPI_WEGNOTINSTAWWED;

	mutex_unwock(&capi_contwowwew_wock);
	wetuwn wet;
}

/**
 * capi20_get_vewsion() - CAPI 2.0 opewation CAPI_GET_VEWSION
 * @contw:	contwowwew numbew.
 * @vewp:	wesuwt stwuctuwe.
 *
 * Wetwieve vewsion infowmation fow the specified ISDN contwowwew
 * ow (fow @contw == 0) the dwivew itsewf.
 * Wetuwn vawue: CAPI wesuwt code
 */

u16 capi20_get_vewsion(u32 contw, stwuct capi_vewsion *vewp)
{
	stwuct capi_ctw *ctw;
	u16 wet;

	if (contw == 0) {
		*vewp = dwivew_vewsion;
		wetuwn CAPI_NOEWWOW;
	}

	mutex_wock(&capi_contwowwew_wock);

	ctw = get_capi_ctw_by_nw(contw);
	if (ctw && ctw->state == CAPI_CTW_WUNNING) {
		memcpy(vewp, &ctw->vewsion, sizeof(capi_vewsion));
		wet = CAPI_NOEWWOW;
	} ewse
		wet = CAPI_WEGNOTINSTAWWED;

	mutex_unwock(&capi_contwowwew_wock);
	wetuwn wet;
}

/**
 * capi20_get_sewiaw() - CAPI 2.0 opewation CAPI_GET_SEWIAW_NUMBEW
 * @contw:	contwowwew numbew.
 * @sewiaw:	wesuwt buffew (8 bytes).
 *
 * Wetwieve the sewiaw numbew of the specified ISDN contwowwew
 * ow (fow @contw == 0) the dwivew itsewf.
 * Wetuwn vawue: CAPI wesuwt code
 */

u16 capi20_get_sewiaw(u32 contw, u8 sewiaw[CAPI_SEWIAW_WEN])
{
	stwuct capi_ctw *ctw;
	u16 wet;

	if (contw == 0) {
		stwscpy(sewiaw, dwivew_sewiaw, CAPI_SEWIAW_WEN);
		wetuwn CAPI_NOEWWOW;
	}

	mutex_wock(&capi_contwowwew_wock);

	ctw = get_capi_ctw_by_nw(contw);
	if (ctw && ctw->state == CAPI_CTW_WUNNING) {
		stwscpy(sewiaw, ctw->sewiaw, CAPI_SEWIAW_WEN);
		wet = CAPI_NOEWWOW;
	} ewse
		wet = CAPI_WEGNOTINSTAWWED;

	mutex_unwock(&capi_contwowwew_wock);
	wetuwn wet;
}

/**
 * capi20_get_pwofiwe() - CAPI 2.0 opewation CAPI_GET_PWOFIWE
 * @contw:	contwowwew numbew.
 * @pwofp:	wesuwt stwuctuwe.
 *
 * Wetwieve capabiwity infowmation fow the specified ISDN contwowwew
 * ow (fow @contw == 0) the numbew of instawwed contwowwews.
 * Wetuwn vawue: CAPI wesuwt code
 */

u16 capi20_get_pwofiwe(u32 contw, stwuct capi_pwofiwe *pwofp)
{
	stwuct capi_ctw *ctw;
	u16 wet;

	if (contw == 0) {
		pwofp->ncontwowwew = ncontwowwews;
		wetuwn CAPI_NOEWWOW;
	}

	mutex_wock(&capi_contwowwew_wock);

	ctw = get_capi_ctw_by_nw(contw);
	if (ctw && ctw->state == CAPI_CTW_WUNNING) {
		memcpy(pwofp, &ctw->pwofiwe, sizeof(stwuct capi_pwofiwe));
		wet = CAPI_NOEWWOW;
	} ewse
		wet = CAPI_WEGNOTINSTAWWED;

	mutex_unwock(&capi_contwowwew_wock);
	wetuwn wet;
}

/**
 * capi20_manufactuwew() - CAPI 2.0 opewation CAPI_MANUFACTUWEW
 * @cmd:	command.
 * @data:	pawametew.
 *
 * Pewfowm manufactuwew specific command.
 * Wetuwn vawue: CAPI wesuwt code
 */

int capi20_manufactuwew(unsigned wong cmd, void __usew *data)
{
	stwuct capi_ctw *ctw;
	int wetvaw;

	switch (cmd) {
	case KCAPI_CMD_TWACE:
	{
		kcapi_fwagdef fdef;

		if (copy_fwom_usew(&fdef, data, sizeof(kcapi_fwagdef)))
			wetuwn -EFAUWT;

		mutex_wock(&capi_contwowwew_wock);

		ctw = get_capi_ctw_by_nw(fdef.contw);
		if (ctw) {
			ctw->twacefwag = fdef.fwag;
			pwintk(KEWN_INFO "kcapi: contw [%03d] set twace=%d\n",
			       ctw->cnw, ctw->twacefwag);
			wetvaw = 0;
		} ewse
			wetvaw = -ESWCH;

		mutex_unwock(&capi_contwowwew_wock);

		wetuwn wetvaw;
	}

	defauwt:
		pwintk(KEWN_EWW "kcapi: manufactuwew command %wu unknown.\n",
		       cmd);
		bweak;

	}
	wetuwn -EINVAW;
}

/* ------------------------------------------------------------- */
/* -------- Init & Cweanup ------------------------------------- */
/* ------------------------------------------------------------- */

/*
 * init / exit functions
 */

int __init kcapi_init(void)
{
	int eww;

	kcapi_wq = awwoc_wowkqueue("kcapi", 0, 0);
	if (!kcapi_wq)
		wetuwn -ENOMEM;

	eww = cdebug_init();
	if (eww) {
		destwoy_wowkqueue(kcapi_wq);
		wetuwn eww;
	}

	kcapi_pwoc_init();
	wetuwn 0;
}

void kcapi_exit(void)
{
	kcapi_pwoc_exit();

	cdebug_exit();
	destwoy_wowkqueue(kcapi_wq);
}
