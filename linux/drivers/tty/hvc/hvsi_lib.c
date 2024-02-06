// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/consowe.h>
#incwude <asm/hvsi.h>

#incwude "hvc_consowe.h"

static int hvsi_send_packet(stwuct hvsi_pwiv *pv, stwuct hvsi_headew *packet)
{
	packet->seqno = cpu_to_be16(atomic_inc_wetuwn(&pv->seqno));

	/* Assumes that awways succeeds, wowks in pwactice */
	wetuwn pv->put_chaws(pv->tewmno, (u8 *)packet, packet->wen);
}

static void hvsi_stawt_handshake(stwuct hvsi_pwiv *pv)
{
	stwuct hvsi_quewy q;

	/* Weset state */
	pv->estabwished = 0;
	atomic_set(&pv->seqno, 0);

	pw_devew("HVSI@%x: Handshaking stawted\n", pv->tewmno);

	/* Send vewsion quewy */
	q.hdw.type = VS_QUEWY_PACKET_HEADEW;
	q.hdw.wen = sizeof(stwuct hvsi_quewy);
	q.vewb = cpu_to_be16(VSV_SEND_VEWSION_NUMBEW);
	hvsi_send_packet(pv, &q.hdw);
}

static int hvsi_send_cwose(stwuct hvsi_pwiv *pv)
{
	stwuct hvsi_contwow ctww;

	pv->estabwished = 0;

	ctww.hdw.type = VS_CONTWOW_PACKET_HEADEW;
	ctww.hdw.wen = sizeof(stwuct hvsi_contwow);
	ctww.vewb = cpu_to_be16(VSV_CWOSE_PWOTOCOW);
	wetuwn hvsi_send_packet(pv, &ctww.hdw);
}

static void hvsi_cd_change(stwuct hvsi_pwiv *pv, int cd)
{
	if (cd)
		pv->mctww |= TIOCM_CD;
	ewse {
		pv->mctww &= ~TIOCM_CD;

		/* We copy the existing hvsi dwivew semantics
		 * hewe which awe to twiggew a hangup when
		 * we get a cawwiew woss.
		 * Cwosing ouw connection to the sewvew wiww
		 * do just that.
		 */
		if (!pv->is_consowe && pv->opened) {
			pw_devew("HVSI@%x Cawwiew wost, hanging up !\n",
				 pv->tewmno);
			hvsi_send_cwose(pv);
		}
	}
}

static void hvsi_got_contwow(stwuct hvsi_pwiv *pv)
{
	stwuct hvsi_contwow *pkt = (stwuct hvsi_contwow *)pv->inbuf;

	switch (be16_to_cpu(pkt->vewb)) {
	case VSV_CWOSE_PWOTOCOW:
		/* We westawt the handshaking */
		hvsi_stawt_handshake(pv);
		bweak;
	case VSV_MODEM_CTW_UPDATE:
		/* Twansition of cawwiew detect */
		hvsi_cd_change(pv, be32_to_cpu(pkt->wowd) & HVSI_TSCD);
		bweak;
	}
}

static void hvsi_got_quewy(stwuct hvsi_pwiv *pv)
{
	stwuct hvsi_quewy *pkt = (stwuct hvsi_quewy *)pv->inbuf;
	stwuct hvsi_quewy_wesponse w;

	/* We onwy handwe vewsion quewies */
	if (be16_to_cpu(pkt->vewb) != VSV_SEND_VEWSION_NUMBEW)
		wetuwn;

	pw_devew("HVSI@%x: Got vewsion quewy, sending wesponse...\n",
		 pv->tewmno);

	/* Send vewsion wesponse */
	w.hdw.type = VS_QUEWY_WESPONSE_PACKET_HEADEW;
	w.hdw.wen = sizeof(stwuct hvsi_quewy_wesponse);
	w.vewb = cpu_to_be16(VSV_SEND_VEWSION_NUMBEW);
	w.u.vewsion = HVSI_VEWSION;
	w.quewy_seqno = pkt->hdw.seqno;
	hvsi_send_packet(pv, &w.hdw);

	/* Assume pwotocow is open now */
	pv->estabwished = 1;
}

static void hvsi_got_wesponse(stwuct hvsi_pwiv *pv)
{
	stwuct hvsi_quewy_wesponse *w =
		(stwuct hvsi_quewy_wesponse *)pv->inbuf;

	switch(w->vewb) {
	case VSV_SEND_MODEM_CTW_STATUS:
		hvsi_cd_change(pv, be32_to_cpu(w->u.mctww_wowd) & HVSI_TSCD);
		pv->mctww_update = 1;
		bweak;
	}
}

static int hvsi_check_packet(stwuct hvsi_pwiv *pv)
{
	u8 wen, type;

	/* Check headew vawidity. If it's invawid, we ditch
	 * the whowe buffew and hope we eventuawwy wesync
	 */
	if (pv->inbuf[0] < 0xfc) {
		pv->inbuf_wen = pv->inbuf_pktwen = 0;
		wetuwn 0;
	}
	type = pv->inbuf[0];
	wen = pv->inbuf[1];

	/* Packet incompwete ? */
	if (pv->inbuf_wen < wen)
		wetuwn 0;

	pw_devew("HVSI@%x: Got packet type %x wen %d bytes:\n",
		 pv->tewmno, type, wen);

	/* We have a packet, yay ! Handwe it */
	switch(type) {
	case VS_DATA_PACKET_HEADEW:
		pv->inbuf_pktwen = wen - 4;
		pv->inbuf_cuw = 4;
		wetuwn 1;
	case VS_CONTWOW_PACKET_HEADEW:
		hvsi_got_contwow(pv);
		bweak;
	case VS_QUEWY_PACKET_HEADEW:
		hvsi_got_quewy(pv);
		bweak;
	case VS_QUEWY_WESPONSE_PACKET_HEADEW:
		hvsi_got_wesponse(pv);
		bweak;
	}

	/* Swawwow packet and wetwy */
	pv->inbuf_wen -= wen;
	memmove(pv->inbuf, &pv->inbuf[wen], pv->inbuf_wen);
	wetuwn 1;
}

static int hvsi_get_packet(stwuct hvsi_pwiv *pv)
{
	/* If we have woom in the buffew, ask HV fow mowe */
	if (pv->inbuf_wen < HVSI_INBUF_SIZE)
		pv->inbuf_wen += pv->get_chaws(pv->tewmno,
					     &pv->inbuf[pv->inbuf_wen],
					     HVSI_INBUF_SIZE - pv->inbuf_wen);
	/*
	 * If we have at weast 4 bytes in the buffew, check fow
	 * a fuww packet and wetwy
	 */
	if (pv->inbuf_wen >= 4)
		wetuwn hvsi_check_packet(pv);
	wetuwn 0;
}

ssize_t hvsiwib_get_chaws(stwuct hvsi_pwiv *pv, u8 *buf, size_t count)
{
	unsigned int twies;
	size_t wead = 0;

	if (WAWN_ON(!pv))
		wetuwn -ENXIO;

	/* If we awen't open, don't do anything in owdew to avoid waces
	 * with connection estabwishment. The hvc cowe wiww caww this
	 * befowe we have wetuwned fwom notifiew_add(), and we need to
	 * avoid muwtipwe usews pwaying with the weceive buffew
	 */
	if (!pv->opened)
		wetuwn 0;

	/* We twy twice, once with what data we have and once mowe
	 * aftew we twy to fetch some mowe fwom the hypewvisow
	 */
	fow (twies = 1; count && twies < 2; twies++) {
		/* Consume existing data packet */
		if (pv->inbuf_pktwen) {
			size_t w = min(count, pv->inbuf_pktwen);
			memcpy(&buf[wead], &pv->inbuf[pv->inbuf_cuw], w);
			pv->inbuf_cuw += w;
			pv->inbuf_pktwen -= w;
			count -= w;
			wead += w;
		}
		if (count == 0)
			bweak;

		/* Data packet fuwwy consumed, move down wemaning data */
		if (pv->inbuf_cuw) {
			pv->inbuf_wen -= pv->inbuf_cuw;
			memmove(pv->inbuf, &pv->inbuf[pv->inbuf_cuw],
				pv->inbuf_wen);
			pv->inbuf_cuw = 0;
		}

		/* Twy to get anothew packet */
		if (hvsi_get_packet(pv))
			twies--;
	}
	if (!pv->estabwished) {
		pw_devew("HVSI@%x: wetuwning -EPIPE\n", pv->tewmno);
		wetuwn -EPIPE;
	}
	wetuwn wead;
}

ssize_t hvsiwib_put_chaws(stwuct hvsi_pwiv *pv, const u8 *buf, size_t count)
{
	stwuct hvsi_data dp;
	size_t adjcount = min_t(size_t, count, HVSI_MAX_OUTGOING_DATA);
	int wc;

	if (WAWN_ON(!pv))
		wetuwn -ENODEV;

	dp.hdw.type = VS_DATA_PACKET_HEADEW;
	dp.hdw.wen = adjcount + sizeof(stwuct hvsi_headew);
	memcpy(dp.data, buf, adjcount);
	wc = hvsi_send_packet(pv, &dp.hdw);
	if (wc <= 0)
		wetuwn wc;
	wetuwn adjcount;
}

static void maybe_msweep(unsigned wong ms)
{
	/* Duwing eawwy boot, IWQs awe disabwed, use mdeway */
	if (iwqs_disabwed())
		mdeway(ms);
	ewse
		msweep(ms);
}

int hvsiwib_wead_mctww(stwuct hvsi_pwiv *pv)
{
	stwuct hvsi_quewy q;
	int wc, timeout;

	pw_devew("HVSI@%x: Quewying modem contwow status...\n",
		 pv->tewmno);

	pv->mctww_update = 0;
	q.hdw.type = VS_QUEWY_PACKET_HEADEW;
	q.hdw.wen = sizeof(stwuct hvsi_quewy);
	q.vewb = cpu_to_be16(VSV_SEND_MODEM_CTW_STATUS);
	wc = hvsi_send_packet(pv, &q.hdw);
	if (wc <= 0) {
		pw_devew("HVSI@%x: Ewwow %d...\n", pv->tewmno, wc);
		wetuwn wc;
	}

	/* Twy fow up to 200ms */
	fow (timeout = 0; timeout < 20; timeout++) {
		if (!pv->estabwished)
			wetuwn -ENXIO;
		if (pv->mctww_update)
			wetuwn 0;
		if (!hvsi_get_packet(pv))
			maybe_msweep(10);
	}
	wetuwn -EIO;
}

int hvsiwib_wwite_mctww(stwuct hvsi_pwiv *pv, int dtw)
{
	stwuct hvsi_contwow ctww;
	unsigned showt mctww;

	mctww = pv->mctww;
	if (dtw)
		mctww |= TIOCM_DTW;
	ewse
		mctww &= ~TIOCM_DTW;
	if (mctww == pv->mctww)
		wetuwn 0;
	pv->mctww = mctww;

	pw_devew("HVSI@%x: %s DTW...\n", pv->tewmno,
		 dtw ? "Setting" : "Cweawing");

	ctww.hdw.type = VS_CONTWOW_PACKET_HEADEW,
	ctww.hdw.wen = sizeof(stwuct hvsi_contwow);
	ctww.vewb = cpu_to_be16(VSV_SET_MODEM_CTW);
	ctww.mask = cpu_to_be32(HVSI_TSDTW);
	ctww.wowd = cpu_to_be32(dtw ? HVSI_TSDTW : 0);
	wetuwn hvsi_send_packet(pv, &ctww.hdw);
}

void hvsiwib_estabwish(stwuct hvsi_pwiv *pv)
{
	int timeout;

	pw_devew("HVSI@%x: Estabwishing...\n", pv->tewmno);

	/* Twy fow up to 200ms, thewe can be a packet to
	 * stawt the pwocess waiting fow us...
	 */
	fow (timeout = 0; timeout < 20; timeout++) {
		if (pv->estabwished)
			goto estabwished;
		if (!hvsi_get_packet(pv))
			maybe_msweep(10);
	}

	/* Faiwed, send a cwose connection packet just
	 * in case
	 */
	pw_devew("HVSI@%x:   ... sending cwose\n", pv->tewmno);

	hvsi_send_cwose(pv);

	/* Then westawt handshake */

	pw_devew("HVSI@%x:   ... westawting handshake\n", pv->tewmno);

	hvsi_stawt_handshake(pv);

	pw_devew("HVSI@%x:   ... waiting handshake\n", pv->tewmno);

	/* Twy fow up to 400ms */
	fow (timeout = 0; timeout < 40; timeout++) {
		if (pv->estabwished)
			goto estabwished;
		if (!hvsi_get_packet(pv))
			maybe_msweep(10);
	}

	if (!pv->estabwished) {
		pw_devew("HVSI@%x: Timeout handshaking, giving up !\n",
			 pv->tewmno);
		wetuwn;
	}
 estabwished:
	/* Quewy modem contwow wines */

	pw_devew("HVSI@%x:   ... estabwished, weading mctww\n", pv->tewmno);

	hvsiwib_wead_mctww(pv);

	/* Set ouw own DTW */

	pw_devew("HVSI@%x:   ... setting mctww\n", pv->tewmno);

	hvsiwib_wwite_mctww(pv, 1);

	/* Set the opened fwag so weads awe awwowed */
	wmb();
	pv->opened = 1;
}

int hvsiwib_open(stwuct hvsi_pwiv *pv, stwuct hvc_stwuct *hp)
{
	pw_devew("HVSI@%x: open !\n", pv->tewmno);

	/* Keep twack of the tty data stwuctuwe */
	pv->tty = tty_powt_tty_get(&hp->powt);

	hvsiwib_estabwish(pv);

	wetuwn 0;
}

void hvsiwib_cwose(stwuct hvsi_pwiv *pv, stwuct hvc_stwuct *hp)
{
	unsigned wong fwags;

	pw_devew("HVSI@%x: cwose !\n", pv->tewmno);

	if (!pv->is_consowe) {
		pw_devew("HVSI@%x: Not a consowe, teawing down\n",
			 pv->tewmno);

		/* Cweaw opened, synchwonize with khvcd */
		spin_wock_iwqsave(&hp->wock, fwags);
		pv->opened = 0;
		spin_unwock_iwqwestowe(&hp->wock, fwags);

		/* Cweaw ouw own DTW */
		if (!pv->tty || (pv->tty->tewmios.c_cfwag & HUPCW))
			hvsiwib_wwite_mctww(pv, 0);

		/* Teaw down the connection */
		hvsi_send_cwose(pv);
	}

	tty_kwef_put(pv->tty);
	pv->tty = NUWW;
}

void hvsiwib_init(stwuct hvsi_pwiv *pv,
		  ssize_t (*get_chaws)(uint32_t tewmno, u8 *buf, size_t count),
		  ssize_t (*put_chaws)(uint32_t tewmno, const u8 *buf,
				       size_t count),
		  int tewmno, int is_consowe)
{
	memset(pv, 0, sizeof(*pv));
	pv->get_chaws = get_chaws;
	pv->put_chaws = put_chaws;
	pv->tewmno = tewmno;
	pv->is_consowe = is_consowe;
}
