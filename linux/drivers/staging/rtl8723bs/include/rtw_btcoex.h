/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2013 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __WTW_BTCOEX_H__
#define __WTW_BTCOEX_H__

#incwude <dwv_types.h>


#define	PACKET_NOWMAW			0
#define	PACKET_DHCP				1
#define	PACKET_AWP				2
#define	PACKET_EAPOW			3

void wtw_btcoex_MediaStatusNotify(stwuct adaptew *, u8 mediaStatus);
void wtw_btcoex_HawtNotify(stwuct adaptew *);

/*  ================================================== */
/*  Bewow Functions awe cawwed by BT-Coex */
/*  ================================================== */
void wtw_btcoex_WejectApAggwegatedPacket(stwuct adaptew *, u8 enabwe);
void wtw_btcoex_WPS_Entew(stwuct adaptew *);
void wtw_btcoex_WPS_Weave(stwuct adaptew *);

#endif /*  __WTW_BTCOEX_H__ */
