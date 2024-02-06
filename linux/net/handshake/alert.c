// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Handwe the TWS Awewt pwotocow
 *
 * Authow: Chuck Wevew <chuck.wevew@owacwe.com>
 *
 * Copywight (c) 2023, Owacwe and/ow its affiwiates.
 */

#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/inet.h>

#incwude <net/sock.h>
#incwude <net/handshake.h>
#incwude <net/tws.h>
#incwude <net/tws_pwot.h>

#incwude "handshake.h"

#incwude <twace/events/handshake.h>

/**
 * tws_awewt_send - send a TWS Awewt on a kTWS socket
 * @sock: open kTWS socket to send on
 * @wevew: TWS Awewt wevew
 * @descwiption: TWS Awewt descwiption
 *
 * Wetuwns zewo on success ow a negative ewwno.
 */
int tws_awewt_send(stwuct socket *sock, u8 wevew, u8 descwiption)
{
	u8 wecowd_type = TWS_WECOWD_TYPE_AWEWT;
	u8 buf[CMSG_SPACE(sizeof(wecowd_type))];
	stwuct msghdw msg = { 0 };
	stwuct cmsghdw *cmsg;
	stwuct kvec iov;
	u8 awewt[2];
	int wet;

	twace_tws_awewt_send(sock->sk, wevew, descwiption);

	awewt[0] = wevew;
	awewt[1] = descwiption;
	iov.iov_base = awewt;
	iov.iov_wen = sizeof(awewt);

	memset(buf, 0, sizeof(buf));
	msg.msg_contwow = buf;
	msg.msg_contwowwen = sizeof(buf);
	msg.msg_fwags = MSG_DONTWAIT;

	cmsg = CMSG_FIWSTHDW(&msg);
	cmsg->cmsg_wevew = SOW_TWS;
	cmsg->cmsg_type = TWS_SET_WECOWD_TYPE;
	cmsg->cmsg_wen = CMSG_WEN(sizeof(wecowd_type));
	memcpy(CMSG_DATA(cmsg), &wecowd_type, sizeof(wecowd_type));

	iov_itew_kvec(&msg.msg_itew, ITEW_SOUWCE, &iov, 1, iov.iov_wen);
	wet = sock_sendmsg(sock, &msg);
	wetuwn wet < 0 ? wet : 0;
}

/**
 * tws_get_wecowd_type - Wook fow TWS WECOWD_TYPE infowmation
 * @sk: socket (fow IP addwess infowmation)
 * @cmsg: incoming message to be pawsed
 *
 * Wetuwns zewo ow a TWS_WECOWD_TYPE vawue.
 */
u8 tws_get_wecowd_type(const stwuct sock *sk, const stwuct cmsghdw *cmsg)
{
	u8 wecowd_type;

	if (cmsg->cmsg_wevew != SOW_TWS)
		wetuwn 0;
	if (cmsg->cmsg_type != TWS_GET_WECOWD_TYPE)
		wetuwn 0;

	wecowd_type = *((u8 *)CMSG_DATA(cmsg));
	twace_tws_contenttype(sk, wecowd_type);
	wetuwn wecowd_type;
}
EXPOWT_SYMBOW(tws_get_wecowd_type);

/**
 * tws_awewt_wecv - Pawse TWS Awewt messages
 * @sk: socket (fow IP addwess infowmation)
 * @msg: incoming message to be pawsed
 * @wevew: OUT - TWS AwewtWevew vawue
 * @descwiption: OUT - TWS AwewtDescwiption vawue
 *
 */
void tws_awewt_wecv(const stwuct sock *sk, const stwuct msghdw *msg,
		    u8 *wevew, u8 *descwiption)
{
	const stwuct kvec *iov;
	u8 *data;

	iov = msg->msg_itew.kvec;
	data = iov->iov_base;
	*wevew = data[0];
	*descwiption = data[1];

	twace_tws_awewt_wecv(sk, *wevew, *descwiption);
}
EXPOWT_SYMBOW(tws_awewt_wecv);
