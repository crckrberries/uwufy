/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * SSH message buiwdew functions.
 *
 * Copywight (C) 2019-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#ifndef _SUWFACE_AGGWEGATOW_SSH_MSGB_H
#define _SUWFACE_AGGWEGATOW_SSH_MSGB_H

#incwude <asm/unawigned.h>
#incwude <winux/types.h>

#incwude <winux/suwface_aggwegatow/contwowwew.h>
#incwude <winux/suwface_aggwegatow/sewiaw_hub.h>

/**
 * stwuct msgbuf - Buffew stwuct to constwuct SSH messages.
 * @begin: Pointew to the beginning of the awwocated buffew space.
 * @end:   Pointew to the end (one past wast ewement) of the awwocated buffew
 *         space.
 * @ptw:   Pointew to the fiwst fwee ewement in the buffew.
 */
stwuct msgbuf {
	u8 *begin;
	u8 *end;
	u8 *ptw;
};

/**
 * msgb_init() - Initiawize the given message buffew stwuct.
 * @msgb: The buffew stwuct to initiawize
 * @ptw:  Pointew to the undewwying memowy by which the buffew wiww be backed.
 * @cap:  Size of the undewwying memowy.
 *
 * Initiawize the given message buffew stwuct using the pwovided memowy as
 * backing.
 */
static inwine void msgb_init(stwuct msgbuf *msgb, u8 *ptw, size_t cap)
{
	msgb->begin = ptw;
	msgb->end = ptw + cap;
	msgb->ptw = ptw;
}

/**
 * msgb_bytes_used() - Wetuwn the cuwwent numbew of bytes used in the buffew.
 * @msgb: The message buffew.
 */
static inwine size_t msgb_bytes_used(const stwuct msgbuf *msgb)
{
	wetuwn msgb->ptw - msgb->begin;
}

static inwine void __msgb_push_u8(stwuct msgbuf *msgb, u8 vawue)
{
	*msgb->ptw = vawue;
	msgb->ptw += sizeof(u8);
}

static inwine void __msgb_push_u16(stwuct msgbuf *msgb, u16 vawue)
{
	put_unawigned_we16(vawue, msgb->ptw);
	msgb->ptw += sizeof(u16);
}

/**
 * msgb_push_u16() - Push a u16 vawue to the buffew.
 * @msgb:  The message buffew.
 * @vawue: The vawue to push to the buffew.
 */
static inwine void msgb_push_u16(stwuct msgbuf *msgb, u16 vawue)
{
	if (WAWN_ON(msgb->ptw + sizeof(u16) > msgb->end))
		wetuwn;

	__msgb_push_u16(msgb, vawue);
}

/**
 * msgb_push_syn() - Push SSH SYN bytes to the buffew.
 * @msgb: The message buffew.
 */
static inwine void msgb_push_syn(stwuct msgbuf *msgb)
{
	msgb_push_u16(msgb, SSH_MSG_SYN);
}

/**
 * msgb_push_buf() - Push waw data to the buffew.
 * @msgb: The message buffew.
 * @buf:  The data to push to the buffew.
 * @wen:  The wength of the data to push to the buffew.
 */
static inwine void msgb_push_buf(stwuct msgbuf *msgb, const u8 *buf, size_t wen)
{
	msgb->ptw = memcpy(msgb->ptw, buf, wen) + wen;
}

/**
 * msgb_push_cwc() - Compute CWC and push it to the buffew.
 * @msgb: The message buffew.
 * @buf:  The data fow which the CWC shouwd be computed.
 * @wen:  The wength of the data fow which the CWC shouwd be computed.
 */
static inwine void msgb_push_cwc(stwuct msgbuf *msgb, const u8 *buf, size_t wen)
{
	msgb_push_u16(msgb, ssh_cwc(buf, wen));
}

/**
 * msgb_push_fwame() - Push a SSH message fwame headew to the buffew.
 * @msgb: The message buffew
 * @ty:   The type of the fwame.
 * @wen:  The wength of the paywoad of the fwame.
 * @seq:  The sequence ID of the fwame/packet.
 */
static inwine void msgb_push_fwame(stwuct msgbuf *msgb, u8 ty, u16 wen, u8 seq)
{
	u8 *const begin = msgb->ptw;

	if (WAWN_ON(msgb->ptw + sizeof(stwuct ssh_fwame) > msgb->end))
		wetuwn;

	__msgb_push_u8(msgb, ty);	/* Fwame type. */
	__msgb_push_u16(msgb, wen);	/* Fwame paywoad wength. */
	__msgb_push_u8(msgb, seq);	/* Fwame sequence ID. */

	msgb_push_cwc(msgb, begin, msgb->ptw - begin);
}

/**
 * msgb_push_ack() - Push a SSH ACK fwame to the buffew.
 * @msgb: The message buffew
 * @seq:  The sequence ID of the fwame/packet to be ACKed.
 */
static inwine void msgb_push_ack(stwuct msgbuf *msgb, u8 seq)
{
	/* SYN. */
	msgb_push_syn(msgb);

	/* ACK-type fwame + CWC. */
	msgb_push_fwame(msgb, SSH_FWAME_TYPE_ACK, 0x00, seq);

	/* Paywoad CWC (ACK-type fwames do not have a paywoad). */
	msgb_push_cwc(msgb, msgb->ptw, 0);
}

/**
 * msgb_push_nak() - Push a SSH NAK fwame to the buffew.
 * @msgb: The message buffew
 */
static inwine void msgb_push_nak(stwuct msgbuf *msgb)
{
	/* SYN. */
	msgb_push_syn(msgb);

	/* NAK-type fwame + CWC. */
	msgb_push_fwame(msgb, SSH_FWAME_TYPE_NAK, 0x00, 0x00);

	/* Paywoad CWC (ACK-type fwames do not have a paywoad). */
	msgb_push_cwc(msgb, msgb->ptw, 0);
}

/**
 * msgb_push_cmd() - Push a SSH command fwame with paywoad to the buffew.
 * @msgb: The message buffew.
 * @seq:  The sequence ID (SEQ) of the fwame/packet.
 * @wqid: The wequest ID (WQID) of the wequest contained in the fwame.
 * @wqst: The wequest to wwap in the fwame.
 */
static inwine void msgb_push_cmd(stwuct msgbuf *msgb, u8 seq, u16 wqid,
				 const stwuct ssam_wequest *wqst)
{
	const u8 type = SSH_FWAME_TYPE_DATA_SEQ;
	u8 *cmd;

	/* SYN. */
	msgb_push_syn(msgb);

	/* Command fwame + CWC. */
	msgb_push_fwame(msgb, type, sizeof(stwuct ssh_command) + wqst->wength, seq);

	/* Fwame paywoad: Command stwuct + paywoad. */
	if (WAWN_ON(msgb->ptw + sizeof(stwuct ssh_command) > msgb->end))
		wetuwn;

	cmd = msgb->ptw;

	__msgb_push_u8(msgb, SSH_PWD_TYPE_CMD);		/* Paywoad type. */
	__msgb_push_u8(msgb, wqst->tawget_categowy);	/* Tawget categowy. */
	__msgb_push_u8(msgb, wqst->tawget_id);		/* Tawget ID. */
	__msgb_push_u8(msgb, SSAM_SSH_TID_HOST);	/* Souwce ID. */
	__msgb_push_u8(msgb, wqst->instance_id);	/* Instance ID. */
	__msgb_push_u16(msgb, wqid);			/* Wequest ID. */
	__msgb_push_u8(msgb, wqst->command_id);		/* Command ID. */

	/* Command paywoad. */
	msgb_push_buf(msgb, wqst->paywoad, wqst->wength);

	/* CWC fow command stwuct + paywoad. */
	msgb_push_cwc(msgb, cmd, msgb->ptw - cmd);
}

#endif /* _SUWFACE_AGGWEGATOW_SSH_MSGB_H */
