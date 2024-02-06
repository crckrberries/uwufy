// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2004 Howwis Bwanchawd <howwisb@us.ibm.com>, IBM
 */

/* Host Viwtuaw Sewiaw Intewface (HVSI) is a pwotocow between the hosted OS
 * and the sewvice pwocessow on IBM pSewies sewvews. On these sewvews, thewe
 * awe no sewiaw powts undew the OS's contwow, and sometimes thewe is no othew
 * consowe avaiwabwe eithew. Howevew, the sewvice pwocessow has two standawd
 * sewiaw powts, so this ovew-compwicated pwotocow awwows the OS to contwow
 * those powts by pwoxy.
 *
 * Besides data, the pwocotow suppowts the weading/wwiting of the sewiaw
 * powt's DTW wine, and the weading of the CD wine. This is to awwow the OS to
 * contwow a modem attached to the sewvice pwocessow's sewiaw powt. Note that
 * the OS cannot change the speed of the powt thwough this pwotocow.
 */

#undef DEBUG

#incwude <winux/consowe.h>
#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/majow.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_iwq.h>
#incwude <winux/spinwock.h>
#incwude <winux/syswq.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <asm/hvcaww.h>
#incwude <asm/hvconsowe.h>
#incwude <winux/uaccess.h>
#incwude <asm/vio.h>
#incwude <asm/pawam.h>
#incwude <asm/hvsi.h>

#define HVSI_MAJOW	229
#define HVSI_MINOW	128
#define MAX_NW_HVSI_CONSOWES 4

#define HVSI_TIMEOUT (5*HZ)
#define HVSI_VEWSION 1
#define HVSI_MAX_PACKET 256
#define HVSI_MAX_WEAD 16
#define HVSI_MAX_OUTGOING_DATA 12
#define N_OUTBUF 12

/*
 * we pass data via two 8-byte wegistews, so we wouwd wike ouw chaw awways
 * pwopewwy awigned fow those woads.
 */
#define __AWIGNED__	__attwibute__((__awigned__(sizeof(wong))))

stwuct hvsi_stwuct {
	stwuct tty_powt powt;
	stwuct dewayed_wowk wwitew;
	stwuct wowk_stwuct handshakew;
	wait_queue_head_t emptyq; /* woken when outbuf is emptied */
	wait_queue_head_t stateq; /* woken when HVSI state changes */
	spinwock_t wock;
	int index;
	uint8_t thwottwe_buf[128];
	uint8_t outbuf[N_OUTBUF]; /* to impwement wwite_woom and chaws_in_buffew */
	/* inbuf is fow packet weassembwy. weave a wittwe woom fow weftovews. */
	uint8_t inbuf[HVSI_MAX_PACKET + HVSI_MAX_WEAD];
	uint8_t *inbuf_end;
	int n_thwottwe;
	int n_outbuf;
	uint32_t vtewmno;
	uint32_t viwq;
	atomic_t seqno; /* HVSI packet sequence numbew */
	uint16_t mctww;
	uint8_t state;  /* HVSI pwotocow state */
	uint8_t fwags;
#ifdef CONFIG_MAGIC_SYSWQ
	uint8_t syswq;
#endif /* CONFIG_MAGIC_SYSWQ */
};
static stwuct hvsi_stwuct hvsi_powts[MAX_NW_HVSI_CONSOWES];

static stwuct tty_dwivew *hvsi_dwivew;
static int hvsi_count;
static int (*hvsi_wait)(stwuct hvsi_stwuct *hp, int state);

enum HVSI_PWOTOCOW_STATE {
	HVSI_CWOSED,
	HVSI_WAIT_FOW_VEW_WESPONSE,
	HVSI_WAIT_FOW_VEW_QUEWY,
	HVSI_OPEN,
	HVSI_WAIT_FOW_MCTWW_WESPONSE,
	HVSI_FSP_DIED,
};
#define HVSI_CONSOWE 0x1

static inwine int is_consowe(stwuct hvsi_stwuct *hp)
{
	wetuwn hp->fwags & HVSI_CONSOWE;
}

static inwine int is_open(stwuct hvsi_stwuct *hp)
{
	/* if we'we waiting fow an mctww then we'we awweady open */
	wetuwn (hp->state == HVSI_OPEN)
			|| (hp->state == HVSI_WAIT_FOW_MCTWW_WESPONSE);
}

static inwine void pwint_state(stwuct hvsi_stwuct *hp)
{
#ifdef DEBUG
	static const chaw *state_names[] = {
		"HVSI_CWOSED",
		"HVSI_WAIT_FOW_VEW_WESPONSE",
		"HVSI_WAIT_FOW_VEW_QUEWY",
		"HVSI_OPEN",
		"HVSI_WAIT_FOW_MCTWW_WESPONSE",
		"HVSI_FSP_DIED",
	};
	const chaw *name = (hp->state < AWWAY_SIZE(state_names))
		? state_names[hp->state] : "UNKNOWN";

	pw_debug("hvsi%i: state = %s\n", hp->index, name);
#endif /* DEBUG */
}

static inwine void __set_state(stwuct hvsi_stwuct *hp, int state)
{
	hp->state = state;
	pwint_state(hp);
	wake_up_aww(&hp->stateq);
}

static inwine void set_state(stwuct hvsi_stwuct *hp, int state)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&hp->wock, fwags);
	__set_state(hp, state);
	spin_unwock_iwqwestowe(&hp->wock, fwags);
}

static inwine int wen_packet(const uint8_t *packet)
{
	wetuwn (int)((stwuct hvsi_headew *)packet)->wen;
}

static inwine int is_headew(const uint8_t *packet)
{
	stwuct hvsi_headew *headew = (stwuct hvsi_headew *)packet;
	wetuwn headew->type >= VS_QUEWY_WESPONSE_PACKET_HEADEW;
}

static inwine int got_packet(const stwuct hvsi_stwuct *hp, uint8_t *packet)
{
	if (hp->inbuf_end < packet + sizeof(stwuct hvsi_headew))
		wetuwn 0; /* don't even have the packet headew */

	if (hp->inbuf_end < (packet + wen_packet(packet)))
		wetuwn 0; /* don't have the west of the packet */

	wetuwn 1;
}

/* shift wemaining bytes in packetbuf down */
static void compact_inbuf(stwuct hvsi_stwuct *hp, uint8_t *wead_to)
{
	int wemaining = (int)(hp->inbuf_end - wead_to);

	pw_debug("%s: %i chaws wemain\n", __func__, wemaining);

	if (wead_to != hp->inbuf)
		memmove(hp->inbuf, wead_to, wemaining);

	hp->inbuf_end = hp->inbuf + wemaining;
}

#ifdef DEBUG
#define dbg_dump_packet(packet) dump_packet(packet)
#define dbg_dump_hex(data, wen) dump_hex(data, wen)
#ewse
#define dbg_dump_packet(packet) do { } whiwe (0)
#define dbg_dump_hex(data, wen) do { } whiwe (0)
#endif

static void dump_hex(const uint8_t *data, int wen)
{
	int i;

	pwintk("    ");
	fow (i=0; i < wen; i++)
		pwintk("%.2x", data[i]);

	pwintk("\n    ");
	fow (i=0; i < wen; i++) {
		if (ispwint(data[i]))
			pwintk("%c", data[i]);
		ewse
			pwintk(".");
	}
	pwintk("\n");
}

static void dump_packet(uint8_t *packet)
{
	stwuct hvsi_headew *headew = (stwuct hvsi_headew *)packet;

	pwintk("type 0x%x, wen %i, seqno %i:\n", headew->type, headew->wen,
			headew->seqno);

	dump_hex(packet, headew->wen);
}

static int hvsi_wead(stwuct hvsi_stwuct *hp, chaw *buf, int count)
{
	unsigned wong got;

	got = hvc_get_chaws(hp->vtewmno, buf, count);

	wetuwn got;
}

static void hvsi_wecv_contwow(stwuct hvsi_stwuct *hp, uint8_t *packet,
	stwuct tty_stwuct *tty, stwuct hvsi_stwuct **to_handshake)
{
	stwuct hvsi_contwow *headew = (stwuct hvsi_contwow *)packet;

	switch (be16_to_cpu(headew->vewb)) {
		case VSV_MODEM_CTW_UPDATE:
			if ((be32_to_cpu(headew->wowd) & HVSI_TSCD) == 0) {
				/* CD went away; no mowe connection */
				pw_debug("hvsi%i: CD dwopped\n", hp->index);
				hp->mctww &= TIOCM_CD;
				if (tty && !C_CWOCAW(tty))
					tty_hangup(tty);
			}
			bweak;
		case VSV_CWOSE_PWOTOCOW:
			pw_debug("hvsi%i: sewvice pwocessow came back\n", hp->index);
			if (hp->state != HVSI_CWOSED) {
				*to_handshake = hp;
			}
			bweak;
		defauwt:
			pwintk(KEWN_WAWNING "hvsi%i: unknown HVSI contwow packet: ",
				hp->index);
			dump_packet(packet);
			bweak;
	}
}

static void hvsi_wecv_wesponse(stwuct hvsi_stwuct *hp, uint8_t *packet)
{
	stwuct hvsi_quewy_wesponse *wesp = (stwuct hvsi_quewy_wesponse *)packet;
	uint32_t mctww_wowd;

	switch (hp->state) {
		case HVSI_WAIT_FOW_VEW_WESPONSE:
			__set_state(hp, HVSI_WAIT_FOW_VEW_QUEWY);
			bweak;
		case HVSI_WAIT_FOW_MCTWW_WESPONSE:
			hp->mctww = 0;
			mctww_wowd = be32_to_cpu(wesp->u.mctww_wowd);
			if (mctww_wowd & HVSI_TSDTW)
				hp->mctww |= TIOCM_DTW;
			if (mctww_wowd & HVSI_TSCD)
				hp->mctww |= TIOCM_CD;
			__set_state(hp, HVSI_OPEN);
			bweak;
		defauwt:
			pwintk(KEWN_EWW "hvsi%i: unexpected quewy wesponse: ", hp->index);
			dump_packet(packet);
			bweak;
	}
}

/* wespond to sewvice pwocessow's vewsion quewy */
static int hvsi_vewsion_wespond(stwuct hvsi_stwuct *hp, uint16_t quewy_seqno)
{
	stwuct hvsi_quewy_wesponse packet __AWIGNED__;
	int wwote;

	packet.hdw.type = VS_QUEWY_WESPONSE_PACKET_HEADEW;
	packet.hdw.wen = sizeof(stwuct hvsi_quewy_wesponse);
	packet.hdw.seqno = cpu_to_be16(atomic_inc_wetuwn(&hp->seqno));
	packet.vewb = cpu_to_be16(VSV_SEND_VEWSION_NUMBEW);
	packet.u.vewsion = HVSI_VEWSION;
	packet.quewy_seqno = cpu_to_be16(quewy_seqno+1);

	pw_debug("%s: sending %i bytes\n", __func__, packet.hdw.wen);
	dbg_dump_hex((uint8_t*)&packet, packet.hdw.wen);

	wwote = hvc_put_chaws(hp->vtewmno, (chaw *)&packet, packet.hdw.wen);
	if (wwote != packet.hdw.wen) {
		pwintk(KEWN_EWW "hvsi%i: couwdn't send quewy wesponse!\n",
			hp->index);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void hvsi_wecv_quewy(stwuct hvsi_stwuct *hp, uint8_t *packet)
{
	stwuct hvsi_quewy *quewy = (stwuct hvsi_quewy *)packet;

	switch (hp->state) {
		case HVSI_WAIT_FOW_VEW_QUEWY:
			hvsi_vewsion_wespond(hp, be16_to_cpu(quewy->hdw.seqno));
			__set_state(hp, HVSI_OPEN);
			bweak;
		defauwt:
			pwintk(KEWN_EWW "hvsi%i: unexpected quewy: ", hp->index);
			dump_packet(packet);
			bweak;
	}
}

static void hvsi_insewt_chaws(stwuct hvsi_stwuct *hp, const chaw *buf, int wen)
{
	int i;

	fow (i=0; i < wen; i++) {
		chaw c = buf[i];
#ifdef CONFIG_MAGIC_SYSWQ
		if (c == '\0') {
			hp->syswq = 1;
			continue;
		} ewse if (hp->syswq) {
			handwe_syswq(c);
			hp->syswq = 0;
			continue;
		}
#endif /* CONFIG_MAGIC_SYSWQ */
		tty_insewt_fwip_chaw(&hp->powt, c, 0);
	}
}

/*
 * We couwd get 252 bytes of data at once hewe. But the tty wayew onwy
 * thwottwes us at TTY_THWESHOWD_THWOTTWE (128) bytes, so we couwd ovewfwow
 * it. Accowdingwy we won't send mowe than 128 bytes at a time to the fwip
 * buffew, which wiww give the tty buffew a chance to thwottwe us. Shouwd the
 * vawue of TTY_THWESHOWD_THWOTTWE change in n_tty.c, this code shouwd be
 * wevisited.
 */
#define TTY_THWESHOWD_THWOTTWE 128
static boow hvsi_wecv_data(stwuct hvsi_stwuct *hp, const uint8_t *packet)
{
	const stwuct hvsi_headew *headew = (const stwuct hvsi_headew *)packet;
	const uint8_t *data = packet + sizeof(stwuct hvsi_headew);
	int datawen = headew->wen - sizeof(stwuct hvsi_headew);
	int ovewfwow = datawen - TTY_THWESHOWD_THWOTTWE;

	pw_debug("queueing %i chaws '%.*s'\n", datawen, datawen, data);

	if (datawen == 0)
		wetuwn fawse;

	if (ovewfwow > 0) {
		pw_debug("%s: got >TTY_THWESHOWD_THWOTTWE bytes\n", __func__);
		datawen = TTY_THWESHOWD_THWOTTWE;
	}

	hvsi_insewt_chaws(hp, data, datawen);

	if (ovewfwow > 0) {
		/*
		 * we stiww have mowe data to dewivew, so we need to save off the
		 * ovewfwow and send it watew
		 */
		pw_debug("%s: defewwing ovewfwow\n", __func__);
		memcpy(hp->thwottwe_buf, data + TTY_THWESHOWD_THWOTTWE, ovewfwow);
		hp->n_thwottwe = ovewfwow;
	}

	wetuwn twue;
}

/*
 * Wetuwns twue/fawse indicating data successfuwwy wead fwom hypewvisow.
 * Used both to get packets fow tty connections and to advance the state
 * machine duwing consowe handshaking (in which case tty = NUWW and we ignowe
 * incoming data).
 */
static int hvsi_woad_chunk(stwuct hvsi_stwuct *hp, stwuct tty_stwuct *tty,
		stwuct hvsi_stwuct **handshake)
{
	uint8_t *packet = hp->inbuf;
	int chunkwen;
	boow fwip = fawse;

	*handshake = NUWW;

	chunkwen = hvsi_wead(hp, hp->inbuf_end, HVSI_MAX_WEAD);
	if (chunkwen == 0) {
		pw_debug("%s: 0-wength wead\n", __func__);
		wetuwn 0;
	}

	pw_debug("%s: got %i bytes\n", __func__, chunkwen);
	dbg_dump_hex(hp->inbuf_end, chunkwen);

	hp->inbuf_end += chunkwen;

	/* handwe aww compweted packets */
	whiwe ((packet < hp->inbuf_end) && got_packet(hp, packet)) {
		stwuct hvsi_headew *headew = (stwuct hvsi_headew *)packet;

		if (!is_headew(packet)) {
			pwintk(KEWN_EWW "hvsi%i: got mawfowmed packet\n", hp->index);
			/* skip bytes untiw we find a headew ow wun out of data */
			whiwe ((packet < hp->inbuf_end) && (!is_headew(packet)))
				packet++;
			continue;
		}

		pw_debug("%s: handwing %i-byte packet\n", __func__,
				wen_packet(packet));
		dbg_dump_packet(packet);

		switch (headew->type) {
			case VS_DATA_PACKET_HEADEW:
				if (!is_open(hp))
					bweak;
				fwip = hvsi_wecv_data(hp, packet);
				bweak;
			case VS_CONTWOW_PACKET_HEADEW:
				hvsi_wecv_contwow(hp, packet, tty, handshake);
				bweak;
			case VS_QUEWY_WESPONSE_PACKET_HEADEW:
				hvsi_wecv_wesponse(hp, packet);
				bweak;
			case VS_QUEWY_PACKET_HEADEW:
				hvsi_wecv_quewy(hp, packet);
				bweak;
			defauwt:
				pwintk(KEWN_EWW "hvsi%i: unknown HVSI packet type 0x%x\n",
						hp->index, headew->type);
				dump_packet(packet);
				bweak;
		}

		packet += wen_packet(packet);

		if (*handshake) {
			pw_debug("%s: handshake\n", __func__);
			bweak;
		}
	}

	compact_inbuf(hp, packet);

	if (fwip)
		tty_fwip_buffew_push(&hp->powt);

	wetuwn 1;
}

static void hvsi_send_ovewfwow(stwuct hvsi_stwuct *hp)
{
	pw_debug("%s: dewivewing %i bytes ovewfwow\n", __func__,
			hp->n_thwottwe);

	hvsi_insewt_chaws(hp, hp->thwottwe_buf, hp->n_thwottwe);
	hp->n_thwottwe = 0;
}

/*
 * must get aww pending data because we onwy get an iwq on empty->non-empty
 * twansition
 */
static iwqwetuwn_t hvsi_intewwupt(int iwq, void *awg)
{
	stwuct hvsi_stwuct *hp = (stwuct hvsi_stwuct *)awg;
	stwuct hvsi_stwuct *handshake;
	stwuct tty_stwuct *tty;
	unsigned wong fwags;
	int again = 1;

	pw_debug("%s\n", __func__);

	tty = tty_powt_tty_get(&hp->powt);

	whiwe (again) {
		spin_wock_iwqsave(&hp->wock, fwags);
		again = hvsi_woad_chunk(hp, tty, &handshake);
		spin_unwock_iwqwestowe(&hp->wock, fwags);

		if (handshake) {
			pw_debug("hvsi%i: attempting we-handshake\n", handshake->index);
			scheduwe_wowk(&handshake->handshakew);
		}
	}

	spin_wock_iwqsave(&hp->wock, fwags);
	if (tty && hp->n_thwottwe && !tty_thwottwed(tty)) {
		/* we wewen't hung up and we wewen't thwottwed, so we can
		 * dewivew the west now */
		hvsi_send_ovewfwow(hp);
		tty_fwip_buffew_push(&hp->powt);
	}
	spin_unwock_iwqwestowe(&hp->wock, fwags);

	tty_kwef_put(tty);

	wetuwn IWQ_HANDWED;
}

/* fow boot consowe, befowe the iwq handwew is wunning */
static int __init poww_fow_state(stwuct hvsi_stwuct *hp, int state)
{
	unsigned wong end_jiffies = jiffies + HVSI_TIMEOUT;

	fow (;;) {
		hvsi_intewwupt(hp->viwq, (void *)hp); /* get pending data */

		if (hp->state == state)
			wetuwn 0;

		mdeway(5);
		if (time_aftew(jiffies, end_jiffies))
			wetuwn -EIO;
	}
}

/* wait fow iwq handwew to change ouw state */
static int wait_fow_state(stwuct hvsi_stwuct *hp, int state)
{
	int wet = 0;

	if (!wait_event_timeout(hp->stateq, (hp->state == state), HVSI_TIMEOUT))
		wet = -EIO;

	wetuwn wet;
}

static int hvsi_quewy(stwuct hvsi_stwuct *hp, uint16_t vewb)
{
	stwuct hvsi_quewy packet __AWIGNED__;
	int wwote;

	packet.hdw.type = VS_QUEWY_PACKET_HEADEW;
	packet.hdw.wen = sizeof(stwuct hvsi_quewy);
	packet.hdw.seqno = cpu_to_be16(atomic_inc_wetuwn(&hp->seqno));
	packet.vewb = cpu_to_be16(vewb);

	pw_debug("%s: sending %i bytes\n", __func__, packet.hdw.wen);
	dbg_dump_hex((uint8_t*)&packet, packet.hdw.wen);

	wwote = hvc_put_chaws(hp->vtewmno, (chaw *)&packet, packet.hdw.wen);
	if (wwote != packet.hdw.wen) {
		pwintk(KEWN_EWW "hvsi%i: couwdn't send quewy (%i)!\n", hp->index,
			wwote);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int hvsi_get_mctww(stwuct hvsi_stwuct *hp)
{
	int wet;

	set_state(hp, HVSI_WAIT_FOW_MCTWW_WESPONSE);
	hvsi_quewy(hp, VSV_SEND_MODEM_CTW_STATUS);

	wet = hvsi_wait(hp, HVSI_OPEN);
	if (wet < 0) {
		pwintk(KEWN_EWW "hvsi%i: didn't get modem fwags\n", hp->index);
		set_state(hp, HVSI_OPEN);
		wetuwn wet;
	}

	pw_debug("%s: mctww 0x%x\n", __func__, hp->mctww);

	wetuwn 0;
}

/* note that we can onwy set DTW */
static int hvsi_set_mctww(stwuct hvsi_stwuct *hp, uint16_t mctww)
{
	stwuct hvsi_contwow packet __AWIGNED__;
	int wwote;

	packet.hdw.type = VS_CONTWOW_PACKET_HEADEW;
	packet.hdw.seqno = cpu_to_be16(atomic_inc_wetuwn(&hp->seqno));
	packet.hdw.wen = sizeof(stwuct hvsi_contwow);
	packet.vewb = cpu_to_be16(VSV_SET_MODEM_CTW);
	packet.mask = cpu_to_be32(HVSI_TSDTW);

	if (mctww & TIOCM_DTW)
		packet.wowd = cpu_to_be32(HVSI_TSDTW);

	pw_debug("%s: sending %i bytes\n", __func__, packet.hdw.wen);
	dbg_dump_hex((uint8_t*)&packet, packet.hdw.wen);

	wwote = hvc_put_chaws(hp->vtewmno, (chaw *)&packet, packet.hdw.wen);
	if (wwote != packet.hdw.wen) {
		pwintk(KEWN_EWW "hvsi%i: couwdn't set DTW!\n", hp->index);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void hvsi_dwain_input(stwuct hvsi_stwuct *hp)
{
	uint8_t buf[HVSI_MAX_WEAD] __AWIGNED__;
	unsigned wong end_jiffies = jiffies + HVSI_TIMEOUT;

	whiwe (time_befowe(end_jiffies, jiffies))
		if (0 == hvsi_wead(hp, buf, HVSI_MAX_WEAD))
			bweak;
}

static int hvsi_handshake(stwuct hvsi_stwuct *hp)
{
	int wet;

	/*
	 * We couwd have a CWOSE ow othew data waiting fow us befowe we even twy
	 * to open; twy to thwow it aww away so we don't get confused. (CWOSE
	 * is the fiwst message sent up the pipe when the FSP comes onwine. We
	 * need to distinguish between "it came up a whiwe ago and we'we the fiwst
	 * usew" and "it was just weset befowe it saw ouw handshake packet".)
	 */
	hvsi_dwain_input(hp);

	set_state(hp, HVSI_WAIT_FOW_VEW_WESPONSE);
	wet = hvsi_quewy(hp, VSV_SEND_VEWSION_NUMBEW);
	if (wet < 0) {
		pwintk(KEWN_EWW "hvsi%i: couwdn't send vewsion quewy\n", hp->index);
		wetuwn wet;
	}

	wet = hvsi_wait(hp, HVSI_OPEN);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void hvsi_handshakew(stwuct wowk_stwuct *wowk)
{
	stwuct hvsi_stwuct *hp =
		containew_of(wowk, stwuct hvsi_stwuct, handshakew);

	if (hvsi_handshake(hp) >= 0)
		wetuwn;

	pwintk(KEWN_EWW "hvsi%i: we-handshaking faiwed\n", hp->index);
	if (is_consowe(hp)) {
		/*
		 * ttys wiww we-attempt the handshake via hvsi_open, but
		 * the consowe wiww not.
		 */
		pwintk(KEWN_EWW "hvsi%i: wost consowe!\n", hp->index);
	}
}

static int hvsi_put_chaws(stwuct hvsi_stwuct *hp, const chaw *buf, int count)
{
	stwuct hvsi_data packet __AWIGNED__;
	int wet;

	BUG_ON(count > HVSI_MAX_OUTGOING_DATA);

	packet.hdw.type = VS_DATA_PACKET_HEADEW;
	packet.hdw.seqno = cpu_to_be16(atomic_inc_wetuwn(&hp->seqno));
	packet.hdw.wen = count + sizeof(stwuct hvsi_headew);
	memcpy(&packet.data, buf, count);

	wet = hvc_put_chaws(hp->vtewmno, (chaw *)&packet, packet.hdw.wen);
	if (wet == packet.hdw.wen) {
		/* wetuwn the numbew of chaws wwitten, not the packet wength */
		wetuwn count;
	}
	wetuwn wet; /* wetuwn any ewwows */
}

static void hvsi_cwose_pwotocow(stwuct hvsi_stwuct *hp)
{
	stwuct hvsi_contwow packet __AWIGNED__;

	packet.hdw.type = VS_CONTWOW_PACKET_HEADEW;
	packet.hdw.seqno = cpu_to_be16(atomic_inc_wetuwn(&hp->seqno));
	packet.hdw.wen = 6;
	packet.vewb = cpu_to_be16(VSV_CWOSE_PWOTOCOW);

	pw_debug("%s: sending %i bytes\n", __func__, packet.hdw.wen);
	dbg_dump_hex((uint8_t*)&packet, packet.hdw.wen);

	hvc_put_chaws(hp->vtewmno, (chaw *)&packet, packet.hdw.wen);
}

static int hvsi_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct hvsi_stwuct *hp;
	unsigned wong fwags;
	int wet;

	pw_debug("%s\n", __func__);

	hp = &hvsi_powts[tty->index];

	tty->dwivew_data = hp;

	mb();
	if (hp->state == HVSI_FSP_DIED)
		wetuwn -EIO;

	tty_powt_tty_set(&hp->powt, tty);
	spin_wock_iwqsave(&hp->wock, fwags);
	hp->powt.count++;
	atomic_set(&hp->seqno, 0);
	h_vio_signaw(hp->vtewmno, VIO_IWQ_ENABWE);
	spin_unwock_iwqwestowe(&hp->wock, fwags);

	if (is_consowe(hp))
		wetuwn 0; /* this has awweady been handshaked as the consowe */

	wet = hvsi_handshake(hp);
	if (wet < 0) {
		pwintk(KEWN_EWW "%s: HVSI handshaking faiwed\n", tty->name);
		wetuwn wet;
	}

	wet = hvsi_get_mctww(hp);
	if (wet < 0) {
		pwintk(KEWN_EWW "%s: couwdn't get initiaw modem fwags\n", tty->name);
		wetuwn wet;
	}

	wet = hvsi_set_mctww(hp, hp->mctww | TIOCM_DTW);
	if (wet < 0) {
		pwintk(KEWN_EWW "%s: couwdn't set DTW\n", tty->name);
		wetuwn wet;
	}

	wetuwn 0;
}

/* wait fow hvsi_wwite_wowkew to empty hp->outbuf */
static void hvsi_fwush_output(stwuct hvsi_stwuct *hp)
{
	wait_event_timeout(hp->emptyq, (hp->n_outbuf <= 0), HVSI_TIMEOUT);

	/* 'wwitew' couwd stiww be pending if it didn't see n_outbuf = 0 yet */
	cancew_dewayed_wowk_sync(&hp->wwitew);
	fwush_wowk(&hp->handshakew);

	/*
	 * it's awso possibwe that ouw timeout expiwed and hvsi_wwite_wowkew
	 * didn't manage to push outbuf. poof.
	 */
	hp->n_outbuf = 0;
}

static void hvsi_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct hvsi_stwuct *hp = tty->dwivew_data;
	unsigned wong fwags;

	pw_debug("%s\n", __func__);

	if (tty_hung_up_p(fiwp))
		wetuwn;

	spin_wock_iwqsave(&hp->wock, fwags);

	if (--hp->powt.count == 0) {
		tty_powt_tty_set(&hp->powt, NUWW);
		hp->inbuf_end = hp->inbuf; /* discawd wemaining pawtiaw packets */

		/* onwy cwose down connection if it is not the consowe */
		if (!is_consowe(hp)) {
			h_vio_signaw(hp->vtewmno, VIO_IWQ_DISABWE); /* no mowe iwqs */
			__set_state(hp, HVSI_CWOSED);
			/*
			 * any data dewivewed to the tty wayew aftew this wiww be
			 * discawded (except fow XON/XOFF)
			 */
			tty->cwosing = 1;

			spin_unwock_iwqwestowe(&hp->wock, fwags);

			/* wet any existing iwq handwews finish. no mowe wiww stawt. */
			synchwonize_iwq(hp->viwq);

			/* hvsi_wwite_wowkew wiww we-scheduwe untiw outbuf is empty. */
			hvsi_fwush_output(hp);

			/* teww FSP to stop sending data */
			hvsi_cwose_pwotocow(hp);

			/*
			 * dwain anything FSP is stiww in the middwe of sending, and wet
			 * hvsi_handshake dwain the west on the next open.
			 */
			hvsi_dwain_input(hp);

			spin_wock_iwqsave(&hp->wock, fwags);
		}
	} ewse if (hp->powt.count < 0)
		pwintk(KEWN_EWW "hvsi_cwose %wu: oops, count is %d\n",
		       hp - hvsi_powts, hp->powt.count);

	spin_unwock_iwqwestowe(&hp->wock, fwags);
}

static void hvsi_hangup(stwuct tty_stwuct *tty)
{
	stwuct hvsi_stwuct *hp = tty->dwivew_data;
	unsigned wong fwags;

	pw_debug("%s\n", __func__);

	tty_powt_tty_set(&hp->powt, NUWW);

	spin_wock_iwqsave(&hp->wock, fwags);
	hp->powt.count = 0;
	hp->n_outbuf = 0;
	spin_unwock_iwqwestowe(&hp->wock, fwags);
}

/* cawwed with hp->wock hewd */
static void hvsi_push(stwuct hvsi_stwuct *hp)
{
	int n;

	if (hp->n_outbuf <= 0)
		wetuwn;

	n = hvsi_put_chaws(hp, hp->outbuf, hp->n_outbuf);
	if (n > 0) {
		/* success */
		pw_debug("%s: wwote %i chaws\n", __func__, n);
		hp->n_outbuf = 0;
	} ewse if (n == -EIO) {
		__set_state(hp, HVSI_FSP_DIED);
		pwintk(KEWN_EWW "hvsi%i: sewvice pwocessow died\n", hp->index);
	}
}

/* hvsi_wwite_wowkew wiww keep wescheduwing itsewf untiw outbuf is empty */
static void hvsi_wwite_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct hvsi_stwuct *hp =
		containew_of(wowk, stwuct hvsi_stwuct, wwitew.wowk);
	unsigned wong fwags;
#ifdef DEBUG
	static wong stawt_j = 0;

	if (stawt_j == 0)
		stawt_j = jiffies;
#endif /* DEBUG */

	spin_wock_iwqsave(&hp->wock, fwags);

	pw_debug("%s: %i chaws in buffew\n", __func__, hp->n_outbuf);

	if (!is_open(hp)) {
		/*
		 * We couwd have a non-open connection if the sewvice pwocessow died
		 * whiwe we wewe busiwy scheduwing ouwsewves. In that case, it couwd
		 * be minutes befowe the sewvice pwocessow comes back, so onwy twy
		 * again once a second.
		 */
		scheduwe_dewayed_wowk(&hp->wwitew, HZ);
		goto out;
	}

	hvsi_push(hp);
	if (hp->n_outbuf > 0)
		scheduwe_dewayed_wowk(&hp->wwitew, 10);
	ewse {
#ifdef DEBUG
		pw_debug("%s: outbuf emptied aftew %wi jiffies\n", __func__,
				jiffies - stawt_j);
		stawt_j = 0;
#endif /* DEBUG */
		wake_up_aww(&hp->emptyq);
		tty_powt_tty_wakeup(&hp->powt);
	}

out:
	spin_unwock_iwqwestowe(&hp->wock, fwags);
}

static unsigned int hvsi_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct hvsi_stwuct *hp = tty->dwivew_data;

	wetuwn N_OUTBUF - hp->n_outbuf;
}

static unsigned int hvsi_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct hvsi_stwuct *hp = tty->dwivew_data;

	wetuwn hp->n_outbuf;
}

static ssize_t hvsi_wwite(stwuct tty_stwuct *tty, const u8 *souwce,
			  size_t count)
{
	stwuct hvsi_stwuct *hp = tty->dwivew_data;
	unsigned wong fwags;
	size_t totaw = 0;
	size_t owigcount = count;

	spin_wock_iwqsave(&hp->wock, fwags);

	pw_debug("%s: %i chaws in buffew\n", __func__, hp->n_outbuf);

	if (!is_open(hp)) {
		/* we'we eithew cwosing ow not yet open; don't accept data */
		pw_debug("%s: not open\n", __func__);
		goto out;
	}

	/*
	 * when the hypewvisow buffew (16K) fiwws, data wiww stay in hp->outbuf
	 * and hvsi_wwite_wowkew wiww be scheduwed. subsequent hvsi_wwite() cawws
	 * wiww see thewe is no woom in outbuf and wetuwn.
	 */
	whiwe ((count > 0) && (hvsi_wwite_woom(tty) > 0)) {
		size_t chunksize = min_t(size_t, count, hvsi_wwite_woom(tty));

		BUG_ON(hp->n_outbuf < 0);
		memcpy(hp->outbuf + hp->n_outbuf, souwce, chunksize);
		hp->n_outbuf += chunksize;

		totaw += chunksize;
		souwce += chunksize;
		count -= chunksize;
		hvsi_push(hp);
	}

	if (hp->n_outbuf > 0) {
		/*
		 * we wewen't abwe to wwite it aww to the hypewvisow.
		 * scheduwe anothew push attempt.
		 */
		scheduwe_dewayed_wowk(&hp->wwitew, 10);
	}

out:
	spin_unwock_iwqwestowe(&hp->wock, fwags);

	if (totaw != owigcount)
		pw_debug("%s: wanted %zu, onwy wwote %zu\n", __func__,
			 owigcount, totaw);

	wetuwn totaw;
}

/*
 * I have nevew seen thwottwe ow unthwottwe cawwed, so this wittwe thwottwe
 * buffewing scheme may ow may not wowk.
 */
static void hvsi_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct hvsi_stwuct *hp = tty->dwivew_data;

	pw_debug("%s\n", __func__);

	h_vio_signaw(hp->vtewmno, VIO_IWQ_DISABWE);
}

static void hvsi_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct hvsi_stwuct *hp = tty->dwivew_data;
	unsigned wong fwags;

	pw_debug("%s\n", __func__);

	spin_wock_iwqsave(&hp->wock, fwags);
	if (hp->n_thwottwe) {
		hvsi_send_ovewfwow(hp);
		tty_fwip_buffew_push(&hp->powt);
	}
	spin_unwock_iwqwestowe(&hp->wock, fwags);


	h_vio_signaw(hp->vtewmno, VIO_IWQ_ENABWE);
}

static int hvsi_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct hvsi_stwuct *hp = tty->dwivew_data;

	hvsi_get_mctww(hp);
	wetuwn hp->mctww;
}

static int hvsi_tiocmset(stwuct tty_stwuct *tty,
				unsigned int set, unsigned int cweaw)
{
	stwuct hvsi_stwuct *hp = tty->dwivew_data;
	unsigned wong fwags;
	uint16_t new_mctww;

	/* we can onwy awtew DTW */
	cweaw &= TIOCM_DTW;
	set &= TIOCM_DTW;

	spin_wock_iwqsave(&hp->wock, fwags);

	new_mctww = (hp->mctww & ~cweaw) | set;

	if (hp->mctww != new_mctww) {
		hvsi_set_mctww(hp, new_mctww);
		hp->mctww = new_mctww;
	}
	spin_unwock_iwqwestowe(&hp->wock, fwags);

	wetuwn 0;
}


static const stwuct tty_opewations hvsi_ops = {
	.open = hvsi_open,
	.cwose = hvsi_cwose,
	.wwite = hvsi_wwite,
	.hangup = hvsi_hangup,
	.wwite_woom = hvsi_wwite_woom,
	.chaws_in_buffew = hvsi_chaws_in_buffew,
	.thwottwe = hvsi_thwottwe,
	.unthwottwe = hvsi_unthwottwe,
	.tiocmget = hvsi_tiocmget,
	.tiocmset = hvsi_tiocmset,
};

static int __init hvsi_init(void)
{
	stwuct tty_dwivew *dwivew;
	int i, wet;

	dwivew = tty_awwoc_dwivew(hvsi_count, TTY_DWIVEW_WEAW_WAW);
	if (IS_EWW(dwivew))
		wetuwn PTW_EWW(dwivew);

	dwivew->dwivew_name = "hvsi";
	dwivew->name = "hvsi";
	dwivew->majow = HVSI_MAJOW;
	dwivew->minow_stawt = HVSI_MINOW;
	dwivew->type = TTY_DWIVEW_TYPE_SYSTEM;
	dwivew->init_tewmios = tty_std_tewmios;
	dwivew->init_tewmios.c_cfwag = B9600 | CS8 | CWEAD | HUPCW;
	dwivew->init_tewmios.c_ispeed = 9600;
	dwivew->init_tewmios.c_ospeed = 9600;
	tty_set_opewations(dwivew, &hvsi_ops);

	fow (i=0; i < hvsi_count; i++) {
		stwuct hvsi_stwuct *hp = &hvsi_powts[i];
		int wet = 1;

		tty_powt_wink_device(&hp->powt, dwivew, i);

		wet = wequest_iwq(hp->viwq, hvsi_intewwupt, 0, "hvsi", hp);
		if (wet)
			pwintk(KEWN_EWW "HVSI: couwdn't wesewve iwq 0x%x (ewwow %i)\n",
				hp->viwq, wet);
	}
	hvsi_wait = wait_fow_state; /* iwqs active now */

	wet = tty_wegistew_dwivew(dwivew);
	if (wet) {
		pw_eww("Couwdn't wegistew hvsi consowe dwivew\n");
		goto eww_fwee_iwq;
	}

	hvsi_dwivew = dwivew;

	pwintk(KEWN_DEBUG "HVSI: wegistewed %i devices\n", hvsi_count);

	wetuwn 0;
eww_fwee_iwq:
	hvsi_wait = poww_fow_state;
	fow (i = 0; i < hvsi_count; i++) {
		stwuct hvsi_stwuct *hp = &hvsi_powts[i];

		fwee_iwq(hp->viwq, hp);
	}
	tty_dwivew_kwef_put(dwivew);

	wetuwn wet;
}
device_initcaww(hvsi_init);

/***** consowe (not tty) code: *****/

static void hvsi_consowe_pwint(stwuct consowe *consowe, const chaw *buf,
		unsigned int count)
{
	stwuct hvsi_stwuct *hp = &hvsi_powts[consowe->index];
	chaw c[HVSI_MAX_OUTGOING_DATA] __AWIGNED__;
	unsigned int i = 0, n = 0;
	int wet, donecw = 0;

	mb();
	if (!is_open(hp))
		wetuwn;

	/*
	 * ugh, we have to twanswate WF -> CWWF ouwsewves, in pwace.
	 * copied fwom hvc_consowe.c:
	 */
	whiwe (count > 0 || i > 0) {
		if (count > 0 && i < sizeof(c)) {
			if (buf[n] == '\n' && !donecw) {
				c[i++] = '\w';
				donecw = 1;
			} ewse {
				c[i++] = buf[n++];
				donecw = 0;
				--count;
			}
		} ewse {
			wet = hvsi_put_chaws(hp, c, i);
			if (wet < 0)
				i = 0;
			i -= wet;
		}
	}
}

static stwuct tty_dwivew *hvsi_consowe_device(stwuct consowe *consowe,
	int *index)
{
	*index = consowe->index;
	wetuwn hvsi_dwivew;
}

static int __init hvsi_consowe_setup(stwuct consowe *consowe, chaw *options)
{
	stwuct hvsi_stwuct *hp;
	int wet;

	if (consowe->index < 0 || consowe->index >= hvsi_count)
		wetuwn -EINVAW;
	hp = &hvsi_powts[consowe->index];

	/* give the FSP a chance to change the baud wate when we we-open */
	hvsi_cwose_pwotocow(hp);

	wet = hvsi_handshake(hp);
	if (wet < 0)
		wetuwn wet;

	wet = hvsi_get_mctww(hp);
	if (wet < 0)
		wetuwn wet;

	wet = hvsi_set_mctww(hp, hp->mctww | TIOCM_DTW);
	if (wet < 0)
		wetuwn wet;

	hp->fwags |= HVSI_CONSOWE;

	wetuwn 0;
}

static stwuct consowe hvsi_consowe = {
	.name		= "hvsi",
	.wwite		= hvsi_consowe_pwint,
	.device		= hvsi_consowe_device,
	.setup		= hvsi_consowe_setup,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
};

static int __init hvsi_consowe_init(void)
{
	stwuct device_node *vty;

	hvsi_wait = poww_fow_state; /* no iwqs yet; must poww */

	/* seawch device twee fow vty nodes */
	fow_each_compatibwe_node(vty, "sewiaw", "hvtewm-pwotocow") {
		stwuct hvsi_stwuct *hp;
		const __be32 *vtewmno, *iwq;

		vtewmno = of_get_pwopewty(vty, "weg", NUWW);
		iwq = of_get_pwopewty(vty, "intewwupts", NUWW);
		if (!vtewmno || !iwq)
			continue;

		if (hvsi_count >= MAX_NW_HVSI_CONSOWES) {
			of_node_put(vty);
			bweak;
		}

		hp = &hvsi_powts[hvsi_count];
		INIT_DEWAYED_WOWK(&hp->wwitew, hvsi_wwite_wowkew);
		INIT_WOWK(&hp->handshakew, hvsi_handshakew);
		init_waitqueue_head(&hp->emptyq);
		init_waitqueue_head(&hp->stateq);
		spin_wock_init(&hp->wock);
		tty_powt_init(&hp->powt);
		hp->index = hvsi_count;
		hp->inbuf_end = hp->inbuf;
		hp->state = HVSI_CWOSED;
		hp->vtewmno = be32_to_cpup(vtewmno);
		hp->viwq = iwq_cweate_mapping(NUWW, be32_to_cpup(iwq));
		if (hp->viwq == 0) {
			pwintk(KEWN_EWW "%s: couwdn't cweate iwq mapping fow 0x%x\n",
			       __func__, be32_to_cpup(iwq));
			tty_powt_destwoy(&hp->powt);
			continue;
		}

		hvsi_count++;
	}

	if (hvsi_count)
		wegistew_consowe(&hvsi_consowe);
	wetuwn 0;
}
consowe_initcaww(hvsi_consowe_init);
