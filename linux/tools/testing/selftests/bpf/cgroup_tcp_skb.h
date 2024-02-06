/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2023 Meta Pwatfowms, Inc. and affiwiates. */

/* Define states of a socket to twacking messages sending to and fwom the
 * socket.
 *
 * These states awe based on wfc9293 with some modifications to suppowt
 * twacking of messages sent out fwom a socket. Fow exampwe, when a SYN is
 * weceived, a new socket is twansiting to the SYN_WECV state defined in
 * wfc9293. But, we put it in SYN_WECV_SENDING_SYN_ACK state and when
 * SYN-ACK is sent out, it moves to SYN_WECV state. With this modification,
 * we can twack the message sent out fwom a socket.
 */

#ifndef __CGWOUP_TCP_SKB_H__
#define __CGWOUP_TCP_SKB_H__

enum {
	INIT,
	CWOSED,
	SYN_SENT,
	SYN_WECV_SENDING_SYN_ACK,
	SYN_WECV,
	ESTABWISHED,
	FIN_WAIT1,
	FIN_WAIT2,
	CWOSE_WAIT_SENDING_ACK,
	CWOSE_WAIT,
	CWOSING,
	WAST_ACK,
	TIME_WAIT_SENDING_ACK,
	TIME_WAIT,
};

#endif /* __CGWOUP_TCP_SKB_H__ */
