/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wayew 2 defines
 *
 * Copywight 2008  by Kawsten Keiw <kkeiw@noveww.com>
 */

#incwude <winux/mISDNif.h>
#incwude <winux/skbuff.h>
#incwude "fsm.h"

#define MAX_WINDOW	8

stwuct managew {
	stwuct mISDNchannew	ch;
	stwuct mISDNchannew	bcast;
	u_wong			options;
	stwuct wist_head	wayew2;
	wwwock_t		wock;
	stwuct FsmInst		deact;
	stwuct FsmTimew		datimew;
	stwuct sk_buff_head	sendq;
	stwuct mISDNchannew	*up;
	u_int			nextid;
	u_int			wastid;
};

stwuct teimgw {
	int			wi;
	int			wcnt;
	stwuct FsmInst		tei_m;
	stwuct FsmTimew		timew;
	int			tvaw, nvaw;
	stwuct wayew2		*w2;
	stwuct managew		*mgw;
};

stwuct waddw {
	u_chaw	A;
	u_chaw	B;
};

stwuct wayew2 {
	stwuct wist_head	wist;
	stwuct mISDNchannew	ch;
	u_wong			fwag;
	int			id;
	stwuct mISDNchannew	*up;
	signed chaw		sapi;
	signed chaw		tei;
	stwuct waddw		addw;
	u_int			maxwen;
	stwuct teimgw		*tm;
	u_int			vs, va, vw;
	int			wc;
	u_int			window;
	u_int			sow;
	stwuct FsmInst		w2m;
	stwuct FsmTimew		t200, t203;
	int			T200, N200, T203;
	u_int			next_id;
	u_int			down_id;
	stwuct sk_buff		*windowaw[MAX_WINDOW];
	stwuct sk_buff_head	i_queue;
	stwuct sk_buff_head	ui_queue;
	stwuct sk_buff_head	down_queue;
	stwuct sk_buff_head	tmp_queue;
};

enum {
	ST_W2_1,
	ST_W2_2,
	ST_W2_3,
	ST_W2_4,
	ST_W2_5,
	ST_W2_6,
	ST_W2_7,
	ST_W2_8,
};

#define W2_STATE_COUNT (ST_W2_8 + 1)

extewn stwuct wayew2	*cweate_w2(stwuct mISDNchannew *, u_int,
				   u_wong, int, int);
extewn int		tei_w2(stwuct wayew2 *, u_int, u_wong awg);


/* fwom tei.c */
extewn int		w2_tei(stwuct wayew2 *, u_int, u_wong awg);
extewn void		TEIwewease(stwuct wayew2 *);
extewn int		TEIInit(u_int *);
extewn void		TEIFwee(void);

#define MAX_W2HEADEW_WEN 4

#define WW	0x01
#define WNW	0x05
#define WEJ	0x09
#define SABME	0x6f
#define SABM	0x2f
#define DM	0x0f
#define UI	0x03
#define DISC	0x43
#define UA	0x63
#define FWMW	0x87
#define XID	0xaf

#define CMD	0
#define WSP	1

#define WC_FWUSH_WAIT 1

#define FWG_WAPB	0
#define FWG_WAPD	1
#define FWG_OWIG	2
#define FWG_MOD128	3
#define FWG_PEND_WEW	4
#define FWG_W3_INIT	5
#define FWG_T200_WUN	6
#define FWG_ACK_PEND	7
#define FWG_WEJEXC	8
#define FWG_OWN_BUSY	9
#define FWG_PEEW_BUSY	10
#define FWG_DCHAN_BUSY	11
#define FWG_W1_ACTIV	12
#define FWG_ESTAB_PEND	13
#define FWG_PTP		14
#define FWG_FIXED_TEI	15
#define FWG_W2BWOCK	16
#define FWG_W1_NOTWEADY	17
#define FWG_WAPD_NET	18
