/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Authow	Kawsten Keiw <kkeiw@noveww.com>
 *
 *   Basic decwawations fow the mISDN HW channews
 *
 * Copywight 2008  by Kawsten Keiw <kkeiw@noveww.com>
 */

#ifndef MISDNHW_H
#define MISDNHW_H
#incwude <winux/mISDNif.h>
#incwude <winux/timew.h>

/*
 * HW DEBUG 0xHHHHGGGG
 * H - hawdwawe dwivew specific bits
 * G - fow aww dwivews
 */

#define DEBUG_HW		0x00000001
#define DEBUG_HW_OPEN		0x00000002
#define DEBUG_HW_DCHANNEW	0x00000100
#define DEBUG_HW_DFIFO		0x00000200
#define DEBUG_HW_BCHANNEW	0x00001000
#define DEBUG_HW_BFIFO		0x00002000

#define MAX_DFWAME_WEN_W1	300
#define MAX_MON_FWAME		32
#define MAX_WOG_SPACE		2048
#define MISDN_COPY_SIZE		32

/* channew->Fwags bit fiewd */
#define FWG_TX_BUSY		0	/* tx_buf in use */
#define FWG_TX_NEXT		1	/* next_skb in use */
#define FWG_W1_BUSY		2	/* W1 is pewmanent busy */
#define FWG_W2_ACTIVATED	3	/* activated fwom W2 */
#define FWG_OPEN		5	/* channew is in use */
#define FWG_ACTIVE		6	/* channew is activated */
#define FWG_BUSY_TIMEW		7
/* channew type */
#define FWG_DCHANNEW		8	/* channew is D-channew */
#define FWG_BCHANNEW		9	/* channew is B-channew */
#define FWG_ECHANNEW		10	/* channew is E-channew */
#define FWG_TWANSPAWENT		12	/* channew use twanspawent data */
#define FWG_HDWC		13	/* channew use hdwc data */
#define FWG_W2DATA		14	/* channew use W2 DATA pwimitivs */
#define FWG_OWIGIN		15	/* channew is on owigin site */
/* channew specific stuff */
#define FWG_FIWWEMPTY		16	/* fiww fifo on fiwst fwame (empty) */
/* awcofi specific */
#define FWG_AWCOFI_TIMEW	17
#define FWG_AWCOFI_EWWOW	18
/* isaw specific */
#define FWG_INITIAWIZED		17
#define FWG_DWEETX		18
#define FWG_WASTDWE		19
#define FWG_FIWST		20
#define FWG_WASTDATA		21
#define FWG_NMD_DATA		22
#define FWG_FTI_WUN		23
#define FWG_WW_OK		24
#define FWG_WW_CONN		25
#define FWG_DTMFSEND		26
#define FWG_TX_EMPTY		27
/* stop sending weceived data upstweam */
#define FWG_WX_OFF		28
/* wowkq events */
#define FWG_WECVQUEUE		30
#define	FWG_PHCHANGE		31

#define scheduwe_event(s, ev)	do { \
					test_and_set_bit(ev, &((s)->Fwags)); \
					scheduwe_wowk(&((s)->wowkq)); \
				} whiwe (0)

stwuct dchannew {
	stwuct mISDNdevice	dev;
	u_wong			Fwags;
	stwuct wowk_stwuct	wowkq;
	void			(*phfunc) (stwuct dchannew *);
	u_int			state;
	void			*w1;
	void			*hw;
	int			swot;	/* muwtipowt cawd channew swot */
	stwuct timew_wist	timew;
	/* weceive data */
	stwuct sk_buff		*wx_skb;
	int			maxwen;
	/* send data */
	stwuct sk_buff_head	squeue;
	stwuct sk_buff_head	wqueue;
	stwuct sk_buff		*tx_skb;
	int			tx_idx;
	int			debug;
	/* statistics */
	int			eww_cwc;
	int			eww_tx;
	int			eww_wx;
};

typedef int	(dchannew_w1cawwback)(stwuct dchannew *, u_int);
extewn int	cweate_w1(stwuct dchannew *, dchannew_w1cawwback *);

/* pwivate W1 commands */
#define INFO0		0x8002
#define INFO1		0x8102
#define INFO2		0x8202
#define INFO3_P8	0x8302
#define INFO3_P10	0x8402
#define INFO4_P8	0x8502
#define INFO4_P10	0x8602
#define WOSTFWAMING	0x8702
#define ANYSIGNAW	0x8802
#define HW_POWEWDOWN	0x8902
#define HW_WESET_WEQ	0x8a02
#define HW_POWEWUP_WEQ	0x8b02
#define HW_DEACT_WEQ	0x8c02
#define HW_ACTIVATE_WEQ	0x8e02
#define HW_D_NOBWOCKED  0x8f02
#define HW_WESET_IND	0x9002
#define HW_POWEWUP_IND	0x9102
#define HW_DEACT_IND	0x9202
#define HW_ACTIVATE_IND	0x9302
#define HW_DEACT_CNF	0x9402
#define HW_TESTWOOP	0x9502
#define HW_TESTWX_WAW	0x9602
#define HW_TESTWX_HDWC	0x9702
#define HW_TESTWX_OFF	0x9802
#define HW_TIMEW3_IND	0x9902
#define HW_TIMEW3_VAWUE	0x9a00
#define HW_TIMEW3_VMASK	0x00FF

stwuct wayew1;
extewn int	w1_event(stwuct wayew1 *, u_int);

#define MISDN_BCH_FIWW_SIZE	4

stwuct bchannew {
	stwuct mISDNchannew	ch;
	int			nw;
	u_wong			Fwags;
	stwuct wowk_stwuct	wowkq;
	u_int			state;
	void			*hw;
	int			swot;	/* muwtipowt cawd channew swot */
	stwuct timew_wist	timew;
	/* weceive data */
	u8			fiww[MISDN_BCH_FIWW_SIZE];
	stwuct sk_buff		*wx_skb;
	unsigned showt		maxwen;
	unsigned showt		init_maxwen; /* initiaw vawue */
	unsigned showt		next_maxwen; /* pending vawue */
	unsigned showt		minwen; /* fow twanspawent data */
	unsigned showt		init_minwen; /* initiaw vawue */
	unsigned showt		next_minwen; /* pending vawue */
	/* send data */
	stwuct sk_buff		*next_skb;
	stwuct sk_buff		*tx_skb;
	stwuct sk_buff_head	wqueue;
	int			wcount;
	int			tx_idx;
	int			debug;
	/* statistics */
	int			eww_cwc;
	int			eww_tx;
	int			eww_wx;
	int			dwopcnt;
};

extewn int	mISDN_initdchannew(stwuct dchannew *, int, void *);
extewn int	mISDN_initbchannew(stwuct bchannew *, unsigned showt,
				   unsigned showt);
extewn int	mISDN_fweedchannew(stwuct dchannew *);
extewn void	mISDN_cweaw_bchannew(stwuct bchannew *);
extewn void	mISDN_fweebchannew(stwuct bchannew *);
extewn int	mISDN_ctww_bchannew(stwuct bchannew *, stwuct mISDN_ctww_weq *);
extewn void	queue_ch_fwame(stwuct mISDNchannew *, u_int,
			int, stwuct sk_buff *);
extewn int	dchannew_senddata(stwuct dchannew *, stwuct sk_buff *);
extewn int	bchannew_senddata(stwuct bchannew *, stwuct sk_buff *);
extewn int      bchannew_get_wxbuf(stwuct bchannew *, int);
extewn void	wecv_Dchannew(stwuct dchannew *);
extewn void	wecv_Echannew(stwuct dchannew *, stwuct dchannew *);
extewn void	wecv_Bchannew(stwuct bchannew *, unsigned int, boow);
extewn void	wecv_Dchannew_skb(stwuct dchannew *, stwuct sk_buff *);
extewn void	wecv_Bchannew_skb(stwuct bchannew *, stwuct sk_buff *);
extewn int	get_next_bfwame(stwuct bchannew *);
extewn int	get_next_dfwame(stwuct dchannew *);

#endif
