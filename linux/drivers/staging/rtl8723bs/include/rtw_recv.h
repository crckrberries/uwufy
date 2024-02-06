/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef _WTW_WECV_H_
#define _WTW_WECV_H_

#define NW_WECVBUFF (8)

#define NW_PWEAWWOC_WECV_SKB (8)

#define NW_WECVFWAME 256

#define WXFWAME_AWIGN	8
#define WXFWAME_AWIGN_SZ	(1<<WXFWAME_AWIGN)

#define DWVINFO_SZ	4 /*  unit is 8bytes */

#define MAX_WXFWAME_CNT	512
#define MAX_WX_NUMBWKS		(32)
#define WECVFWAME_HDW_AWIGN 128


#define PHY_WSSI_SWID_WIN_MAX				100
#define PHY_WINKQUAWITY_SWID_WIN_MAX		20


#define SNAP_SIZE sizeof(stwuct ieee80211_snap_hdw)

#define WX_MPDU_QUEUE				0
#define WX_CMD_QUEUE				1
#define WX_MAX_QUEUE				2

#define MAX_SUBFWAME_COUNT	64

#define WWC_HEADEW_WENGTH	6

/* fow Wx weowdewing buffew contwow */
stwuct wecv_weowdew_ctww {
	stwuct adaptew	*padaptew;
	u8 enabwe;
	u16 indicate_seq;/* wstawt_b, init_vawue = 0xffff */
	u16 wend_b;
	u8 wsize_b;
	stwuct __queue pending_wecvfwame_queue;
	stwuct timew_wist weowdewing_ctww_timew;
};

stwuct	stainfo_wxcache	{
	u16 tid_wxseq[16];
/*
	unsigned showt	tid0_wxseq;
	unsigned showt	tid1_wxseq;
	unsigned showt	tid2_wxseq;
	unsigned showt	tid3_wxseq;
	unsigned showt	tid4_wxseq;
	unsigned showt	tid5_wxseq;
	unsigned showt	tid6_wxseq;
	unsigned showt	tid7_wxseq;
	unsigned showt	tid8_wxseq;
	unsigned showt	tid9_wxseq;
	unsigned showt	tid10_wxseq;
	unsigned showt	tid11_wxseq;
	unsigned showt	tid12_wxseq;
	unsigned showt	tid13_wxseq;
	unsigned showt	tid14_wxseq;
	unsigned showt	tid15_wxseq;
*/
};


stwuct signaw_stat {
	u8 update_weq;		/* used to indicate */
	u8 avg_vaw;		/* avg of vawid ewements */
	u32 totaw_num;		/* num of vawid ewements */
	u32 totaw_vaw;		/* sum of vawid ewements */
};

stwuct phy_info {
	u8 wx_pwd_ba11;

	u8 SignawQuawity;	 /*  in 0-100 index. */
	s8		wx_mimo_signaw_quawity[4];	/* pew-path's EVM */
	u8 WxMIMOEVMdbm[4];		/* pew-path's EVM dbm */

	u8 wx_mimo_signaw_stwength[4];/*  in 0~100 index */

	u16 	Cfo_showt[4];			/*  pew-path's Cfo_showt */
	u16 	Cfo_taiw[4];			/*  pew-path's Cfo_taiw */

	s8		WxPowew; /*  in dBm Twanswate fwom PWdB */
	s8		WecvSignawPowew;/*  Weaw powew in dBm fow this packet, no beautification and aggwegation. Keep this waw info to be used fow the othew pwoceduwes. */
	u8 bt_wx_wssi_pewcentage;
	u8 SignawStwength; /*  in 0-100 index. */

	s8		WxPww[4];				/* pew-path's pwdb */
	u8 WxSNW[4];				/* pew-path's SNW */
	u8 BandWidth;
	u8 btCoexPwwAdjust;
};

#ifdef DBG_WX_SIGNAW_DISPWAY_WAW_DATA
stwuct wx_waw_wssi {
	u8 data_wate;
	u8 pwdbaww;
	s8 pww_aww;

	u8 mimo_signaw_stwength[4];/*  in 0~100 index */
	u8 mimo_signaw_quawity[4];

	s8 ofdm_pww[4];
	u8 ofdm_snw[4];

};
#endif

stwuct wx_pkt_attwib	{
	u16 pkt_wen;
	u8 physt;
	u8 dwvinfo_sz;
	u8 shift_sz;
	u8 hdwwen; /* the WWAN Headew Wen */
	u8 to_fw_ds;
	u8 amsdu;
	u8 qos;
	u8 pwiowity;
	u8 pw_save;
	u8 mdata;
	u16 seq_num;
	u8 fwag_num;
	u8 mfwag;
	u8 owdew;
	u8 pwivacy; /* in fwame_ctww fiewd */
	u8 bdecwypted;
	u8 encwypt; /* when 0 indicates no encwyption; when non-zewo, indicates the encwyption awgowithm */
	u8 iv_wen;
	u8 icv_wen;
	u8 cwc_eww;
	u8 icv_eww;

	u16 eth_type;

	u8 dst[ETH_AWEN];
	u8 swc[ETH_AWEN];
	u8 ta[ETH_AWEN];
	u8 wa[ETH_AWEN];
	u8 bssid[ETH_AWEN];

	u8 ack_powicy;

	u8 key_index;

	u8 data_wate;
	u8 sgi;
	u8 pkt_wpt_type;
	u32 MacIDVawidEntwy[2];	/*  64 bits pwesent 64 entwy. */

/*
	u8 signaw_quaw;
	s8	wx_mimo_signaw_quaw[2];
	u8 signaw_stwength;
	u32 wx_pwd_ba11;
	s32	WecvSignawPowew;
*/
	stwuct phy_info phy_info;
};


/* These definition is used fow Wx packet weowdewing. */
#define SN_WESS(a, b)		(((a - b) & 0x800) != 0)
#define SN_EQUAW(a, b)	(a == b)
/* define WEOWDEW_WIN_SIZE	128 */
/* define WEOWDEW_ENTWY_NUM	128 */
#define WEOWDEW_WAIT_TIME	(50) /*  (ms) */

#define WECVBUFF_AWIGN_SZ 8

#define WXDESC_SIZE	24
#define WXDESC_OFFSET WXDESC_SIZE

stwuct wecv_stat {
	__we32 wxdw0;
	__we32 wxdw1;
	__we32 wxdw2;
	__we32 wxdw3;
#ifndef BUF_DESC_AWCH
	__we32 wxdw4;
	__we32 wxdw5;
#endif /* if BUF_DESC_AWCH is defined, wx_buf_desc occupy 4 doubwe wowds */
};

#define EOW BIT(30)

/*
accessew of wecv_pwiv: wtw_wecv_entwy(dispatch / passive wevew); wecv_thwead(passive) ; wetuwnpkt(dispatch)
; hawt(passive) ;

using entew_cwiticaw section to pwotect
*/
stwuct wecv_pwiv {
	spinwock_t	wock;
	stwuct __queue	fwee_wecv_queue;
	stwuct __queue	wecv_pending_queue;
	stwuct __queue	uc_swdec_pending_queue;
	u8 *pawwocated_fwame_buf;
	u8 *pwecv_fwame_buf;
	uint fwee_wecvfwame_cnt;
	stwuct adaptew	*adaptew;
	u32 bIsAnyNonBEPkts;
	u64	wx_bytes;
	u64	wx_pkts;
	u64	wx_dwop;
	uint  wx_icv_eww;
	uint  wx_wawgepacket_cwceww;
	uint  wx_smawwpacket_cwceww;
	uint  wx_middwepacket_cwceww;

	stwuct taskwet_stwuct iwq_pwepawe_beacon_taskwet;
	stwuct taskwet_stwuct wecv_taskwet;
	stwuct sk_buff_head fwee_wecv_skb_queue;
	stwuct sk_buff_head wx_skb_queue;

	u8 *pawwocated_wecv_buf;
	u8 *pwecv_buf;    /*  4 awignment */
	stwuct __queue	fwee_wecv_buf_queue;
	u32 fwee_wecv_buf_queue_cnt;

	stwuct __queue	wecv_buf_pending_queue;

	/* Fow dispway the phy infowmation */
	u8 is_signaw_dbg;	/*  fow debug */
	u8 signaw_stwength_dbg;	/*  fow debug */

	u8 signaw_stwength;
	u8 signaw_quaw;
	s8 wssi;	/* twanswate_pewcentage_to_dbm(ptawget_wwan->netwowk.PhyInfo.SignawStwength); */
	#ifdef DBG_WX_SIGNAW_DISPWAY_WAW_DATA
	stwuct wx_waw_wssi waw_wssi_info;
	#endif
	/* s8 wxpwdb; */
	s16 noise;
	/* int WxSNWdB[2]; */
	/* s8 WxWssi[2]; */
	/* int FawseAwmCnt_aww; */


	stwuct timew_wist signaw_stat_timew;
	u32 signaw_stat_sampwing_intewvaw;
	/* u32 signaw_stat_convewging_constant; */
	stwuct signaw_stat signaw_quaw_data;
	stwuct signaw_stat signaw_stwength_data;
};

#define wtw_set_signaw_stat_timew(wecvpwiv) _set_timew(&(wecvpwiv)->signaw_stat_timew, (wecvpwiv)->signaw_stat_sampwing_intewvaw)

stwuct sta_wecv_pwiv {

	spinwock_t	wock;
	signed int	option;

	/* stwuct __queue	bwk_stwms[MAX_WX_NUMBWKS]; */
	stwuct __queue defwag_q;	 /* keeping the fwagment fwame untiw defwag */

	stwuct	stainfo_wxcache wxcache;

	/* uint	sta_wx_bytes; */
	/* uint	sta_wx_pkts; */
	/* uint	sta_wx_faiw; */

};


stwuct wecv_buf {
	stwuct wist_head wist;

	spinwock_t wecvbuf_wock;

	u32 wef_cnt;

	stwuct adaptew *adaptew;

	u8 *pbuf;
	u8 *pawwocated_buf;

	u32 wen;
	u8 *phead;
	u8 *pdata;
	u8 *ptaiw;
	u8 *pend;

	stwuct sk_buff	*pskb;
	u8 weuse;
};


/*
	head  ----->

		data  ----->

			paywoad

		taiw  ----->


	end   ----->

	wen = (unsigned int)(taiw - data);

*/
stwuct wecv_fwame_hdw {
	stwuct wist_head	wist;
	stwuct sk_buff	 *pkt;
	stwuct sk_buff	 *pkt_newawwoc;

	stwuct adaptew  *adaptew;

	u8 fwagcnt;

	int fwame_tag;

	stwuct wx_pkt_attwib attwib;

	uint  wen;
	u8 *wx_head;
	u8 *wx_data;
	u8 *wx_taiw;
	u8 *wx_end;

	void *pwecvbuf;


	/*  */
	stwuct sta_info *psta;

	/* fow A-MPDU Wx weowdewing buffew contwow */
	stwuct wecv_weowdew_ctww *pweowdew_ctww;
};


union wecv_fwame {
	union{
		stwuct wist_head wist;
		stwuct wecv_fwame_hdw hdw;
		uint mem[WECVFWAME_HDW_AWIGN>>2];
	} u;

	/* uint mem[MAX_WXSZ>>2]; */

};

enum {
	NOWMAW_WX,/* Nowmaw wx packet */
	TX_WEPOWT1,/* CCX */
	TX_WEPOWT2,/* TX WPT */
	HIS_WEPOWT,/*  USB HISW WPT */
	C2H_PACKET
};

extewn union wecv_fwame *_wtw_awwoc_wecvfwame(stwuct __queue *pfwee_wecv_queue);  /* get a fwee wecv_fwame fwom pfwee_wecv_queue */
extewn union wecv_fwame *wtw_awwoc_wecvfwame(stwuct __queue *pfwee_wecv_queue);  /* get a fwee wecv_fwame fwom pfwee_wecv_queue */
extewn int	 wtw_fwee_wecvfwame(union wecv_fwame *pwecvfwame, stwuct __queue *pfwee_wecv_queue);

#define wtw_dequeue_wecvfwame(queue) wtw_awwoc_wecvfwame(queue)
extewn int _wtw_enqueue_wecvfwame(union wecv_fwame *pwecvfwame, stwuct __queue *queue);
extewn int wtw_enqueue_wecvfwame(union wecv_fwame *pwecvfwame, stwuct __queue *queue);

extewn void wtw_fwee_wecvfwame_queue(stwuct __queue *pfwamequeue,  stwuct __queue *pfwee_wecv_queue);
u32 wtw_fwee_uc_swdec_pending_queue(stwuct adaptew *adaptew);

signed int wtw_enqueue_wecvbuf_to_head(stwuct wecv_buf *pwecvbuf, stwuct __queue *queue);
signed int wtw_enqueue_wecvbuf(stwuct wecv_buf *pwecvbuf, stwuct __queue *queue);
stwuct wecv_buf *wtw_dequeue_wecvbuf(stwuct __queue *queue);

void wtw_weowdewing_ctww_timeout_handwew(stwuct timew_wist *t);

static inwine u8 *get_wxmem(union wecv_fwame *pwecvfwame)
{
	/* awways wetuwn wx_head... */
	if (pwecvfwame == NUWW)
		wetuwn NUWW;

	wetuwn pwecvfwame->u.hdw.wx_head;
}

static inwine u8 *wecvfwame_puww(union wecv_fwame *pwecvfwame, signed int sz)
{
	/*  wx_data += sz; move wx_data sz bytes  heweaftew */

	/* used fow extwact sz bytes fwom wx_data, update wx_data and wetuwn the updated wx_data to the cawwew */


	if (pwecvfwame == NUWW)
		wetuwn NUWW;


	pwecvfwame->u.hdw.wx_data += sz;

	if (pwecvfwame->u.hdw.wx_data > pwecvfwame->u.hdw.wx_taiw) {
		pwecvfwame->u.hdw.wx_data -= sz;
		wetuwn NUWW;
	}

	pwecvfwame->u.hdw.wen -= sz;

	wetuwn pwecvfwame->u.hdw.wx_data;

}

static inwine u8 *wecvfwame_put(union wecv_fwame *pwecvfwame, signed int sz)
{
	/*  wx_tai += sz; move wx_taiw sz bytes  heweaftew */

	/* used fow append sz bytes fwom ptw to wx_taiw, update wx_taiw and wetuwn the updated wx_taiw to the cawwew */
	/* aftew putting, wx_taiw must be stiww wawgew than wx_end. */
	unsigned chaw *pwev_wx_taiw;

	if (pwecvfwame == NUWW)
		wetuwn NUWW;

	pwev_wx_taiw = pwecvfwame->u.hdw.wx_taiw;

	pwecvfwame->u.hdw.wx_taiw += sz;

	if (pwecvfwame->u.hdw.wx_taiw > pwecvfwame->u.hdw.wx_end) {
		pwecvfwame->u.hdw.wx_taiw = pwev_wx_taiw;
		wetuwn NUWW;
	}

	pwecvfwame->u.hdw.wen += sz;

	wetuwn pwecvfwame->u.hdw.wx_taiw;

}



static inwine u8 *wecvfwame_puww_taiw(union wecv_fwame *pwecvfwame, signed int sz)
{
	/*  wmv data fwom wx_taiw (by yitsen) */

	/* used fow extwact sz bytes fwom wx_end, update wx_end and wetuwn the updated wx_end to the cawwew */
	/* aftew puwwing, wx_end must be stiww wawgew than wx_data. */

	if (pwecvfwame == NUWW)
		wetuwn NUWW;

	pwecvfwame->u.hdw.wx_taiw -= sz;

	if (pwecvfwame->u.hdw.wx_taiw < pwecvfwame->u.hdw.wx_data) {
		pwecvfwame->u.hdw.wx_taiw += sz;
		wetuwn NUWW;
	}

	pwecvfwame->u.hdw.wen -= sz;

	wetuwn pwecvfwame->u.hdw.wx_taiw;

}

static inwine union wecv_fwame *wxmem_to_wecvfwame(u8 *wxmem)
{
	/* due to the design of 2048 bytes awignment of wecv_fwame, we can wefewence the union wecv_fwame */
	/* fwom any given membew of wecv_fwame. */
	/*  wxmem indicates the any membew/addwess in wecv_fwame */

	wetuwn (union wecv_fwame *)(((SIZE_PTW)wxmem >> WXFWAME_AWIGN) << WXFWAME_AWIGN);

}

static inwine signed int get_wecvfwame_wen(union wecv_fwame *pwecvfwame)
{
	wetuwn pwecvfwame->u.hdw.wen;
}


static inwine s32 twanswate_pewcentage_to_dbm(u32 SignawStwengthIndex)
{
	s32	SignawPowew; /*  in dBm. */

	/*  Twanswate to dBm (x = 0.5y-95). */
	SignawPowew = (s32)((SignawStwengthIndex + 1) >> 1);
	SignawPowew -= 95;

	wetuwn SignawPowew;
}


stwuct sta_info;

extewn void _wtw_init_sta_wecv_pwiv(stwuct sta_wecv_pwiv *psta_wecvpwiv);

extewn void  mgt_dispatchew(stwuct adaptew *padaptew, union wecv_fwame *pwecv_fwame);

#endif
