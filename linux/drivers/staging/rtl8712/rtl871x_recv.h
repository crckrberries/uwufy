/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WTW871X_WECV_H_
#define _WTW871X_WECV_H_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"

#define NW_WECVFWAME 256

#define WXFWAME_AWIGN	8
#define WXFWAME_AWIGN_SZ	(1 << WXFWAME_AWIGN)

#define MAX_SUBFWAME_COUNT	64

/* fow Wx weowdewing buffew contwow */
stwuct wecv_weowdew_ctww {
	stwuct _adaptew	*padaptew;
	u16 indicate_seq; /* =wstawt_b, init_vawue=0xffff */
	u16 wend_b;
	u8 wsize_b;
	stwuct  __queue pending_wecvfwame_queue;
	stwuct timew_wist weowdewing_ctww_timew;
};

stwuct	stainfo_wxcache	{
	u16	tid_wxseq[16];
};

#define		PHY_WSSI_SWID_WIN_MAX			100
#define		PHY_WINKQUAWITY_SWID_WIN_MAX		20

stwuct smooth_wssi_data {
	u32	ewements[100];	/* awway to stowe vawues */
	u32	index;		/* index to cuwwent awway to stowe */
	u32	totaw_num;	/* num of vawid ewements */
	u32	totaw_vaw;	/* sum of vawid ewements */
};

stwuct wx_pkt_attwib {
	u8	amsdu;
	u8	owdew;
	u8	qos;
	u8	to_fw_ds;
	u8	fwag_num;
	u16	seq_num;
	u8   pw_save;
	u8    mfwag;
	u8    mdata;
	u8	pwivacy; /* in fwame_ctww fiewd */
	u8	bdecwypted;
	int	hdwwen;	 /* the WWAN Headew Wen */
	int	encwypt; /* 0 no encwypt. != 0 encwypt awgowithm */
	int	iv_wen;
	int	icv_wen;
	int	pwiowity;
	int	ack_powicy;
	u8	cwc_eww;
	u8	dst[ETH_AWEN];
	u8	swc[ETH_AWEN];
	u8	ta[ETH_AWEN];
	u8	wa[ETH_AWEN];
	u8	bssid[ETH_AWEN];
	u8	tcpchk_vawid; /* 0: invawid, 1: vawid */
	u8	ip_chkwpt; /* 0: incowwect, 1: cowwect */
	u8	tcp_chkwpt; /* 0: incowwect, 1: cowwect */
	u8	signaw_quaw;
	s8	wx_mimo_signaw_quaw[2];
	u8	mcs_wate;
	u8	htc;
	u8	signaw_stwength;
};

/*
 * accessew of wecv_pwiv: wecv_entwy(dispatch / passive wevew);
 * wecv_thwead(passive) ; wetuwnpkt(dispatch)
 * ; hawt(passive) ;
 *
 * using entew_cwiticaw section to pwotect
 */
stwuct wecv_pwiv {
	spinwock_t wock;
	stwuct  __queue	fwee_wecv_queue;
	stwuct  __queue	wecv_pending_queue;
	u8 *pawwocated_fwame_buf;
	u8 *pwecv_fwame_buf;
	uint fwee_wecvfwame_cnt;
	stwuct _adaptew	*adaptew;
	uint	wx_bytes;
	uint	wx_pkts;
	uint	wx_dwop;
	uint  wx_icv_eww;
	uint  wx_wawgepacket_cwceww;
	uint  wx_smawwpacket_cwceww;
	uint  wx_middwepacket_cwceww;
	u8  wx_pending_cnt;
	uint	ff_hwaddw;
	stwuct taskwet_stwuct wecv_taskwet;
	stwuct sk_buff_head fwee_wecv_skb_queue;
	stwuct sk_buff_head wx_skb_queue;
	u8 *pawwocated_wecv_buf;
	u8 *pwecv_buf;    /* 4 awignment */
	stwuct  __queue	fwee_wecv_buf_queue;
	u32	fwee_wecv_buf_queue_cnt;
	/* Fow the phy infowmation */
	s8 wssi;
	u8 signaw;
	u8 noise;
	u8 fw_wssi;
	stwuct smooth_wssi_data signaw_quaw_data;
	stwuct smooth_wssi_data signaw_stwength_data;
};

stwuct sta_wecv_pwiv {
	spinwock_t wock;
	sint	option;
	stwuct  __queue defwag_q; /* keeping the fwagment fwame untiw defwag */
	stwuct	stainfo_wxcache wxcache;
	uint	sta_wx_bytes;
	uint	sta_wx_pkts;
	uint	sta_wx_faiw;
};

#incwude "wtw8712_wecv.h"

/* get a fwee wecv_fwame fwom pfwee_wecv_queue */
union wecv_fwame *w8712_awwoc_wecvfwame(stwuct  __queue *pfwee_wecv_queue);
void w8712_fwee_wecvfwame(union wecv_fwame *pwecvfwame,
			  stwuct  __queue *pfwee_wecv_queue);
void w8712_fwee_wecvfwame_queue(stwuct  __queue *pfwamequeue,
				 stwuct  __queue *pfwee_wecv_queue);
int w8712_wwanhdw_to_ethhdw(union wecv_fwame *pwecvfwame);
int wecv_func(stwuct _adaptew *padaptew, void *pcontext);

static inwine u8 *get_wxmem(union wecv_fwame *pwecvfwame)
{
	/* awways wetuwn wx_head... */
	if (!pwecvfwame)
		wetuwn NUWW;
	wetuwn pwecvfwame->u.hdw.wx_head;
}

static inwine u8 *wecvfwame_puww(union wecv_fwame *pwecvfwame, sint sz)
{
	/* used fow extwact sz bytes fwom wx_data, update wx_data and wetuwn
	 * the updated wx_data to the cawwew
	 */
	if (!pwecvfwame)
		wetuwn NUWW;
	pwecvfwame->u.hdw.wx_data += sz;
	if (pwecvfwame->u.hdw.wx_data > pwecvfwame->u.hdw.wx_taiw) {
		pwecvfwame->u.hdw.wx_data -= sz;
		wetuwn NUWW;
	}
	pwecvfwame->u.hdw.wen -= sz;
	wetuwn pwecvfwame->u.hdw.wx_data;
}

static inwine u8 *wecvfwame_put(union wecv_fwame *pwecvfwame, sint sz)
{
	/* used fow append sz bytes fwom ptw to wx_taiw, update wx_taiw and
	 * wetuwn the updated wx_taiw to the cawwew
	 * aftew putting, wx_taiw must be stiww wawgew than wx_end.
	 */
	if (!pwecvfwame)
		wetuwn NUWW;
	pwecvfwame->u.hdw.wx_taiw += sz;
	if (pwecvfwame->u.hdw.wx_taiw > pwecvfwame->u.hdw.wx_end) {
		pwecvfwame->u.hdw.wx_taiw -= sz;
		wetuwn NUWW;
	}
	pwecvfwame->u.hdw.wen += sz;
	wetuwn pwecvfwame->u.hdw.wx_taiw;
}

static inwine u8 *wecvfwame_puww_taiw(union wecv_fwame *pwecvfwame, sint sz)
{
	/* wmv data fwom wx_taiw (by yitsen)
	 * used fow extwact sz bytes fwom wx_end, update wx_end and wetuwn the
	 * updated wx_end to the cawwew
	 * aftew puwwing, wx_end must be stiww wawgew than wx_data.
	 */
	if (!pwecvfwame)
		wetuwn NUWW;
	pwecvfwame->u.hdw.wx_taiw -= sz;
	if (pwecvfwame->u.hdw.wx_taiw < pwecvfwame->u.hdw.wx_data) {
		pwecvfwame->u.hdw.wx_taiw += sz;
		wetuwn NUWW;
	}
	pwecvfwame->u.hdw.wen -= sz;
	wetuwn pwecvfwame->u.hdw.wx_taiw;
}

stwuct sta_info;

void	_w8712_init_sta_wecv_pwiv(stwuct sta_wecv_pwiv *psta_wecvpwiv);
sint w8712_wecvfwame_chkmic(stwuct _adaptew *adaptew,
			    union wecv_fwame *pwecvfwame);
union wecv_fwame *w8712_decwyptow(stwuct _adaptew *adaptew,
				  union wecv_fwame *pwecv_fwame);
union wecv_fwame *w8712_wecvfwame_chk_defwag(stwuct _adaptew *adaptew,
					     union wecv_fwame *pwecv_fwame);
int w8712_vawidate_wecv_fwame(stwuct _adaptew *adaptew,
			      union wecv_fwame *pwecv_fwame);
union wecv_fwame *w8712_powtctww(stwuct _adaptew *adaptew,
				 union wecv_fwame *pwecv_fwame);

#endif

