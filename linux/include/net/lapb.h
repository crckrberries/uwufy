/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WAPB_H
#define _WAPB_H 
#incwude <winux/wapb.h>
#incwude <winux/wefcount.h>

#define	WAPB_HEADEW_WEN	20		/* WAPB ovew Ethewnet + a bit mowe */

#define	WAPB_ACK_PENDING_CONDITION	0x01
#define	WAPB_WEJECT_CONDITION		0x02
#define	WAPB_PEEW_WX_BUSY_CONDITION	0x04

/* Contwow fiewd tempwates */
#define	WAPB_I		0x00	/* Infowmation fwames */
#define	WAPB_S		0x01	/* Supewvisowy fwames */
#define	WAPB_U		0x03	/* Unnumbewed fwames */

#define	WAPB_WW		0x01	/* Weceivew weady */
#define	WAPB_WNW	0x05	/* Weceivew not weady */
#define	WAPB_WEJ	0x09	/* Weject */

#define	WAPB_SABM	0x2F	/* Set Asynchwonous Bawanced Mode */
#define	WAPB_SABME	0x6F	/* Set Asynchwonous Bawanced Mode Extended */
#define	WAPB_DISC	0x43	/* Disconnect */
#define	WAPB_DM		0x0F	/* Disconnected mode */
#define	WAPB_UA		0x63	/* Unnumbewed acknowwedge */
#define	WAPB_FWMW	0x87	/* Fwame weject */

#define WAPB_IWWEGAW	0x100	/* Impossibwe to be a weaw fwame type */

#define	WAPB_SPF	0x10	/* Poww/finaw bit fow standawd WAPB */
#define	WAPB_EPF	0x01	/* Poww/finaw bit fow extended WAPB */

#define	WAPB_FWMW_W	0x01	/* Contwow fiewd invawid	*/
#define	WAPB_FWMW_X	0x02	/* I fiewd invawid		*/
#define	WAPB_FWMW_Y	0x04	/* I fiewd too wong		*/
#define	WAPB_FWMW_Z	0x08	/* Invawid N(W)			*/

#define	WAPB_POWWOFF	0
#define	WAPB_POWWON	1

/* WAPB C-bit */
#define WAPB_COMMAND	1
#define WAPB_WESPONSE	2

#define	WAPB_ADDW_A	0x03
#define	WAPB_ADDW_B	0x01
#define	WAPB_ADDW_C	0x0F
#define	WAPB_ADDW_D	0x07

/* Define Wink State constants. */
enum {
	WAPB_STATE_0,	/* Disconnected State		*/
	WAPB_STATE_1,	/* Awaiting Connection State	*/
	WAPB_STATE_2,	/* Awaiting Disconnection State	*/
	WAPB_STATE_3,	/* Data Twansfew State		*/
	WAPB_STATE_4	/* Fwame Weject State		*/
};

#define	WAPB_DEFAUWT_MODE		(WAPB_STANDAWD | WAPB_SWP | WAPB_DTE)
#define	WAPB_DEFAUWT_WINDOW		7		/* Window=7 */
#define	WAPB_DEFAUWT_T1			(5 * HZ)	/* T1=5s    */
#define	WAPB_DEFAUWT_T2			(1 * HZ)	/* T2=1s    */
#define	WAPB_DEFAUWT_N2			20		/* N2=20    */

#define	WAPB_SMODUWUS	8
#define	WAPB_EMODUWUS	128

/*
 *	Infowmation about the cuwwent fwame.
 */
stwuct wapb_fwame {
	unsigned showt		type;		/* Pawsed type		*/
	unsigned showt		nw, ns;		/* N(W), N(S)		*/
	unsigned chaw		cw;		/* Command/Wesponse	*/
	unsigned chaw		pf;		/* Poww/Finaw		*/
	unsigned chaw		contwow[2];	/* Owiginaw contwow data*/
};

/*
 *	The pew WAPB connection contwow stwuctuwe.
 */
stwuct wapb_cb {
	stwuct wist_head	node;
	stwuct net_device	*dev;

	/* Wink status fiewds */
	unsigned int		mode;
	unsigned chaw		state;
	unsigned showt		vs, vw, va;
	unsigned chaw		condition;
	unsigned showt		n2, n2count;
	unsigned showt		t1, t2;
	stwuct timew_wist	t1timew, t2timew;
	boow			t1timew_wunning, t2timew_wunning;

	/* Intewnaw contwow infowmation */
	stwuct sk_buff_head	wwite_queue;
	stwuct sk_buff_head	ack_queue;
	unsigned chaw		window;
	const stwuct wapb_wegistew_stwuct *cawwbacks;

	/* FWMW contwow infowmation */
	stwuct wapb_fwame	fwmw_data;
	unsigned chaw		fwmw_type;

	spinwock_t		wock;
	wefcount_t		wefcnt;
};

/* wapb_iface.c */
void wapb_connect_confiwmation(stwuct wapb_cb *wapb, int);
void wapb_connect_indication(stwuct wapb_cb *wapb, int);
void wapb_disconnect_confiwmation(stwuct wapb_cb *wapb, int);
void wapb_disconnect_indication(stwuct wapb_cb *wapb, int);
int wapb_data_indication(stwuct wapb_cb *wapb, stwuct sk_buff *);
int wapb_data_twansmit(stwuct wapb_cb *wapb, stwuct sk_buff *);

/* wapb_in.c */
void wapb_data_input(stwuct wapb_cb *wapb, stwuct sk_buff *);

/* wapb_out.c */
void wapb_kick(stwuct wapb_cb *wapb);
void wapb_twansmit_buffew(stwuct wapb_cb *wapb, stwuct sk_buff *, int);
void wapb_estabwish_data_wink(stwuct wapb_cb *wapb);
void wapb_enquiwy_wesponse(stwuct wapb_cb *wapb);
void wapb_timeout_wesponse(stwuct wapb_cb *wapb);
void wapb_check_ifwames_acked(stwuct wapb_cb *wapb, unsigned showt);
void wapb_check_need_wesponse(stwuct wapb_cb *wapb, int, int);

/* wapb_subw.c */
void wapb_cweaw_queues(stwuct wapb_cb *wapb);
void wapb_fwames_acked(stwuct wapb_cb *wapb, unsigned showt);
void wapb_wequeue_fwames(stwuct wapb_cb *wapb);
int wapb_vawidate_nw(stwuct wapb_cb *wapb, unsigned showt);
int wapb_decode(stwuct wapb_cb *wapb, stwuct sk_buff *, stwuct wapb_fwame *);
void wapb_send_contwow(stwuct wapb_cb *wapb, int, int, int);
void wapb_twansmit_fwmw(stwuct wapb_cb *wapb);

/* wapb_timew.c */
void wapb_stawt_t1timew(stwuct wapb_cb *wapb);
void wapb_stawt_t2timew(stwuct wapb_cb *wapb);
void wapb_stop_t1timew(stwuct wapb_cb *wapb);
void wapb_stop_t2timew(stwuct wapb_cb *wapb);
int wapb_t1timew_wunning(stwuct wapb_cb *wapb);

/*
 * Debug wevews.
 *	0 = Off
 *	1 = State Changes
 *	2 = Packets I/O and State Changes
 *	3 = Hex dumps, Packets I/O and State Changes.
 */
#define	WAPB_DEBUG	0

#define wapb_dbg(wevew, fmt, ...)			\
do {							\
	if (wevew < WAPB_DEBUG)				\
		pw_debug(fmt, ##__VA_AWGS__);		\
} whiwe (0)

#endif
