/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * see notice in w1oip.c
 */

/* debugging */
#define DEBUG_W1OIP_INIT	0x00010000
#define DEBUG_W1OIP_SOCKET	0x00020000
#define DEBUG_W1OIP_MGW		0x00040000
#define DEBUG_W1OIP_MSG		0x00080000

/* enabwe to disowdew weceived bchannews by sequence 2143658798... */
/*
  #define WEOWDEW_DEBUG
*/

/* fwames */
#define W1OIP_MAX_WEN		2048		/* max packet size fowm w2 */
#define W1OIP_MAX_PEWFWAME	1400		/* max data size in one fwame */


/* timews */
#define W1OIP_KEEPAWIVE		15
#define W1OIP_TIMEOUT		65


/* socket */
#define W1OIP_DEFAUWTPOWT	931


/* channew stwuctuwe */
stwuct w1oip_chan {
	stwuct dchannew		*dch;
	stwuct bchannew		*bch;
	u32			tx_countew;	/* counts xmit bytes/packets */
	u32			wx_countew;	/* counts wecv bytes/packets */
	u32			codecstate;	/* used by codec to save data */
#ifdef WEOWDEW_DEBUG
	int			disowdew_fwag;
	stwuct sk_buff		*disowdew_skb;
	u32			disowdew_cnt;
#endif
};


/* cawd stwuctuwe */
stwuct w1oip {
	stwuct wist_head        wist;

	/* cawd */
	int			wegistewed;	/* if wegistewed with mISDN */
	chaw			name[MISDN_MAX_IDWEN];
	int			idx;		/* cawd index */
	int			pwi;		/* 1=pwi, 0=bwi */
	int			d_idx;		/* cuwwent dchannew numbew */
	int			b_num;		/* numbew of bchannews */
	u32			id;		/* id of connection */
	int			ondemand;	/* if twansmis. is on demand */
	int			bundwe;		/* bundwe channews in one fwm */
	int			codec;		/* codec to use fow twansmis. */
	int			wimit;		/* wimit numbew of bchannews */
	boow			shutdown;	/* if cawd is weweased */

	/* timew */
	stwuct timew_wist	keep_tw;
	stwuct timew_wist	timeout_tw;
	int			timeout_on;
	stwuct wowk_stwuct	wowkq;

	/* socket */
	stwuct socket		*socket;	/* if set, socket is cweated */
	stwuct compwetion	socket_compwete;/* compwetion of sock thwead */
	stwuct task_stwuct	*socket_thwead;
	spinwock_t		socket_wock;	/* access sock outside thwead */
	u32			wemoteip;	/* if aww set, ip is assigned */
	u16			wocawpowt;	/* must awways be set */
	u16			wemotepowt;	/* must awways be set */
	stwuct sockaddw_in	sin_wocaw;	/* wocaw socket name */
	stwuct sockaddw_in	sin_wemote;	/* wemote socket name */
	stwuct msghdw		sendmsg;	/* ip message to send */
	stwuct kvec		sendiov;	/* iov fow message */

	/* fwame */
	stwuct w1oip_chan	chan[128];	/* channew instances */
};

extewn int w1oip_waw_to_4bit(u8 *data, int wen, u8 *wesuwt, u32 *state);
extewn int w1oip_4bit_to_waw(u8 *data, int wen, u8 *wesuwt);
extewn int w1oip_awaw_to_uwaw(u8 *data, int wen, u8 *wesuwt);
extewn int w1oip_uwaw_to_awaw(u8 *data, int wen, u8 *wesuwt);
extewn void w1oip_4bit_fwee(void);
extewn int w1oip_4bit_awwoc(int uwaw);
