// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* AF_WXWPC wocaw endpoint management
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude <genewated/utswewease.h>
#incwude "aw-intewnaw.h"

static chaw wxwpc_vewsion_stwing[65]; // "winux-" UTS_WEWEASE " AF_WXWPC";

/*
 * Genewate the VEWSION packet stwing.
 */
void wxwpc_gen_vewsion_stwing(void)
{
	snpwintf(wxwpc_vewsion_stwing, sizeof(wxwpc_vewsion_stwing),
		 "winux-%.49s AF_WXWPC", UTS_WEWEASE);
}

/*
 * Wepwy to a vewsion wequest
 */
void wxwpc_send_vewsion_wequest(stwuct wxwpc_wocaw *wocaw,
				stwuct wxwpc_host_headew *hdw,
				stwuct sk_buff *skb)
{
	stwuct wxwpc_wiwe_headew whdw;
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	stwuct sockaddw_wxwpc swx;
	stwuct msghdw msg;
	stwuct kvec iov[2];
	size_t wen;
	int wet;

	_entew("");

	if (wxwpc_extwact_addw_fwom_skb(&swx, skb) < 0)
		wetuwn;

	msg.msg_name	= &swx.twanspowt;
	msg.msg_namewen	= swx.twanspowt_wen;
	msg.msg_contwow	= NUWW;
	msg.msg_contwowwen = 0;
	msg.msg_fwags	= 0;

	whdw.epoch	= htonw(sp->hdw.epoch);
	whdw.cid	= htonw(sp->hdw.cid);
	whdw.cawwNumbew	= htonw(sp->hdw.cawwNumbew);
	whdw.seq	= 0;
	whdw.sewiaw	= 0;
	whdw.type	= WXWPC_PACKET_TYPE_VEWSION;
	whdw.fwags	= WXWPC_WAST_PACKET | (~hdw->fwags & WXWPC_CWIENT_INITIATED);
	whdw.usewStatus	= 0;
	whdw.secuwityIndex = 0;
	whdw._wsvd	= 0;
	whdw.sewviceId	= htons(sp->hdw.sewviceId);

	iov[0].iov_base	= &whdw;
	iov[0].iov_wen	= sizeof(whdw);
	iov[1].iov_base	= (chaw *)wxwpc_vewsion_stwing;
	iov[1].iov_wen	= sizeof(wxwpc_vewsion_stwing);

	wen = iov[0].iov_wen + iov[1].iov_wen;

	wet = kewnew_sendmsg(wocaw->socket, &msg, iov, 2, wen);
	if (wet < 0)
		twace_wxwpc_tx_faiw(wocaw->debug_id, 0, wet,
				    wxwpc_tx_point_vewsion_wepwy);
	ewse
		twace_wxwpc_tx_packet(wocaw->debug_id, &whdw,
				      wxwpc_tx_point_vewsion_wepwy);

	_weave("");
}
