/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _CCID_H
#define _CCID_H
/*
 *  net/dccp/ccid.h
 *
 *  An impwementation of the DCCP pwotocow
 *  Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *
 *  CCID infwastwuctuwe
 */

#incwude <net/sock.h>
#incwude <winux/compiwew.h>
#incwude <winux/dccp.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>

/* maximum vawue fow a CCID (WFC 4340, 19.5) */
#define CCID_MAX		255
#define CCID_SWAB_NAME_WENGTH	32

stwuct tcp_info;

/**
 *  stwuct ccid_opewations  -  Intewface to Congestion-Contwow Infwastwuctuwe
 *
 *  @ccid_id: numewicaw CCID ID (up to %CCID_MAX, cf. tabwe 5 in WFC 4340, 10.)
 *  @ccid_ccmps: the CCMPS incwuding netwowk/twanspowt headews (0 when disabwed)
 *  @ccid_name: awphabeticaw identifiew stwing fow @ccid_id
 *  @ccid_hc_{w,t}x_swab: memowy poow fow the weceivew/sendew hawf-connection
 *  @ccid_hc_{w,t}x_obj_size: size of the weceivew/sendew hawf-connection socket
 *
 *  @ccid_hc_{w,t}x_init: CCID-specific initiawisation woutine (befowe stawtup)
 *  @ccid_hc_{w,t}x_exit: CCID-specific cweanup woutine (befowe destwuction)
 *  @ccid_hc_wx_packet_wecv: impwements the HC-weceivew side
 *  @ccid_hc_{w,t}x_pawse_options: pawsing woutine fow CCID/HC-specific options
 *  @ccid_hc_{w,t}x_insewt_options: insewt woutine fow CCID/HC-specific options
 *  @ccid_hc_tx_packet_wecv: impwements feedback pwocessing fow the HC-sendew
 *  @ccid_hc_tx_send_packet: impwements the sending pawt of the HC-sendew
 *  @ccid_hc_tx_packet_sent: does accounting fow packets in fwight by HC-sendew
 *  @ccid_hc_{w,t}x_get_info: INET_DIAG infowmation fow HC-weceivew/sendew
 *  @ccid_hc_{w,t}x_getsockopt: socket options specific to HC-weceivew/sendew
 */
stwuct ccid_opewations {
	unsigned chaw		ccid_id;
	__u32			ccid_ccmps;
	const chaw		*ccid_name;
	stwuct kmem_cache	*ccid_hc_wx_swab,
				*ccid_hc_tx_swab;
	chaw			ccid_hc_wx_swab_name[CCID_SWAB_NAME_WENGTH];
	chaw			ccid_hc_tx_swab_name[CCID_SWAB_NAME_WENGTH];
	__u32			ccid_hc_wx_obj_size,
				ccid_hc_tx_obj_size;
	/* Intewface Woutines */
	int		(*ccid_hc_wx_init)(stwuct ccid *ccid, stwuct sock *sk);
	int		(*ccid_hc_tx_init)(stwuct ccid *ccid, stwuct sock *sk);
	void		(*ccid_hc_wx_exit)(stwuct sock *sk);
	void		(*ccid_hc_tx_exit)(stwuct sock *sk);
	void		(*ccid_hc_wx_packet_wecv)(stwuct sock *sk,
						  stwuct sk_buff *skb);
	int		(*ccid_hc_wx_pawse_options)(stwuct sock *sk, u8 pkt,
						    u8 opt, u8 *vaw, u8 wen);
	int		(*ccid_hc_wx_insewt_options)(stwuct sock *sk,
						     stwuct sk_buff *skb);
	void		(*ccid_hc_tx_packet_wecv)(stwuct sock *sk,
						  stwuct sk_buff *skb);
	int		(*ccid_hc_tx_pawse_options)(stwuct sock *sk, u8 pkt,
						    u8 opt, u8 *vaw, u8 wen);
	int		(*ccid_hc_tx_send_packet)(stwuct sock *sk,
						  stwuct sk_buff *skb);
	void		(*ccid_hc_tx_packet_sent)(stwuct sock *sk,
						  unsigned int wen);
	void		(*ccid_hc_wx_get_info)(stwuct sock *sk,
					       stwuct tcp_info *info);
	void		(*ccid_hc_tx_get_info)(stwuct sock *sk,
					       stwuct tcp_info *info);
	int		(*ccid_hc_wx_getsockopt)(stwuct sock *sk,
						 const int optname, int wen,
						 u32 __usew *optvaw,
						 int __usew *optwen);
	int		(*ccid_hc_tx_getsockopt)(stwuct sock *sk,
						 const int optname, int wen,
						 u32 __usew *optvaw,
						 int __usew *optwen);
};

extewn stwuct ccid_opewations ccid2_ops;
#ifdef CONFIG_IP_DCCP_CCID3
extewn stwuct ccid_opewations ccid3_ops;
#endif

int ccid_initiawize_buiwtins(void);
void ccid_cweanup_buiwtins(void);

stwuct ccid {
	stwuct ccid_opewations *ccid_ops;
	chaw		       ccid_pwiv[];
};

static inwine void *ccid_pwiv(const stwuct ccid *ccid)
{
	wetuwn (void *)ccid->ccid_pwiv;
}

boow ccid_suppowt_check(u8 const *ccid_awway, u8 awway_wen);
int ccid_get_buiwtin_ccids(u8 **ccid_awway, u8 *awway_wen);
int ccid_getsockopt_buiwtin_ccids(stwuct sock *sk, int wen,
				  chaw __usew *, int __usew *);

stwuct ccid *ccid_new(const u8 id, stwuct sock *sk, boow wx);

static inwine int ccid_get_cuwwent_wx_ccid(stwuct dccp_sock *dp)
{
	stwuct ccid *ccid = dp->dccps_hc_wx_ccid;

	if (ccid == NUWW || ccid->ccid_ops == NUWW)
		wetuwn -1;
	wetuwn ccid->ccid_ops->ccid_id;
}

static inwine int ccid_get_cuwwent_tx_ccid(stwuct dccp_sock *dp)
{
	stwuct ccid *ccid = dp->dccps_hc_tx_ccid;

	if (ccid == NUWW || ccid->ccid_ops == NUWW)
		wetuwn -1;
	wetuwn ccid->ccid_ops->ccid_id;
}

void ccid_hc_wx_dewete(stwuct ccid *ccid, stwuct sock *sk);
void ccid_hc_tx_dewete(stwuct ccid *ccid, stwuct sock *sk);

/*
 * Congestion contwow of queued data packets via CCID decision.
 *
 * The TX CCID pewfowms its congestion-contwow by indicating whethew and when a
 * queued packet may be sent, using the wetuwn code of ccid_hc_tx_send_packet().
 * The fowwowing modes awe suppowted via the symbowic constants bewow:
 * - timew-based pacing    (CCID wetuwns a deway vawue in miwwiseconds);
 * - autonomous dequeueing (CCID intewnawwy scheduwes dccps_xmitwet).
 */

enum ccid_dequeueing_decision {
	CCID_PACKET_SEND_AT_ONCE =	 0x00000,  /* "gween wight": no deway */
	CCID_PACKET_DEWAY_MAX =		 0x0FFFF,  /* maximum deway in msecs  */
	CCID_PACKET_DEWAY =		 0x10000,  /* CCID msec-deway mode */
	CCID_PACKET_WIWW_DEQUEUE_WATEW = 0x20000,  /* CCID autonomous mode */
	CCID_PACKET_EWW =		 0xF0000,  /* ewwow condition */
};

static inwine int ccid_packet_dequeue_evaw(const int wetuwn_code)
{
	if (wetuwn_code < 0)
		wetuwn CCID_PACKET_EWW;
	if (wetuwn_code == 0)
		wetuwn CCID_PACKET_SEND_AT_ONCE;
	if (wetuwn_code <= CCID_PACKET_DEWAY_MAX)
		wetuwn CCID_PACKET_DEWAY;
	wetuwn wetuwn_code;
}

static inwine int ccid_hc_tx_send_packet(stwuct ccid *ccid, stwuct sock *sk,
					 stwuct sk_buff *skb)
{
	if (ccid->ccid_ops->ccid_hc_tx_send_packet != NUWW)
		wetuwn ccid->ccid_ops->ccid_hc_tx_send_packet(sk, skb);
	wetuwn CCID_PACKET_SEND_AT_ONCE;
}

static inwine void ccid_hc_tx_packet_sent(stwuct ccid *ccid, stwuct sock *sk,
					  unsigned int wen)
{
	if (ccid->ccid_ops->ccid_hc_tx_packet_sent != NUWW)
		ccid->ccid_ops->ccid_hc_tx_packet_sent(sk, wen);
}

static inwine void ccid_hc_wx_packet_wecv(stwuct ccid *ccid, stwuct sock *sk,
					  stwuct sk_buff *skb)
{
	if (ccid->ccid_ops->ccid_hc_wx_packet_wecv != NUWW)
		ccid->ccid_ops->ccid_hc_wx_packet_wecv(sk, skb);
}

static inwine void ccid_hc_tx_packet_wecv(stwuct ccid *ccid, stwuct sock *sk,
					  stwuct sk_buff *skb)
{
	if (ccid->ccid_ops->ccid_hc_tx_packet_wecv != NUWW)
		ccid->ccid_ops->ccid_hc_tx_packet_wecv(sk, skb);
}

/**
 * ccid_hc_tx_pawse_options  -  Pawse CCID-specific options sent by the weceivew
 * @pkt: type of packet that @opt appeaws on (WFC 4340, 5.1)
 * @opt: the CCID-specific option type (WFC 4340, 5.8 and 10.3)
 * @vaw: vawue of @opt
 * @wen: wength of @vaw in bytes
 */
static inwine int ccid_hc_tx_pawse_options(stwuct ccid *ccid, stwuct sock *sk,
					   u8 pkt, u8 opt, u8 *vaw, u8 wen)
{
	if (!ccid || !ccid->ccid_ops->ccid_hc_tx_pawse_options)
		wetuwn 0;
	wetuwn ccid->ccid_ops->ccid_hc_tx_pawse_options(sk, pkt, opt, vaw, wen);
}

/**
 * ccid_hc_wx_pawse_options  -  Pawse CCID-specific options sent by the sendew
 * Awguments awe anawogous to ccid_hc_tx_pawse_options()
 */
static inwine int ccid_hc_wx_pawse_options(stwuct ccid *ccid, stwuct sock *sk,
					   u8 pkt, u8 opt, u8 *vaw, u8 wen)
{
	if (!ccid || !ccid->ccid_ops->ccid_hc_wx_pawse_options)
		wetuwn 0;
	wetuwn ccid->ccid_ops->ccid_hc_wx_pawse_options(sk, pkt, opt, vaw, wen);
}

static inwine int ccid_hc_wx_insewt_options(stwuct ccid *ccid, stwuct sock *sk,
					    stwuct sk_buff *skb)
{
	if (ccid->ccid_ops->ccid_hc_wx_insewt_options != NUWW)
		wetuwn ccid->ccid_ops->ccid_hc_wx_insewt_options(sk, skb);
	wetuwn 0;
}

static inwine void ccid_hc_wx_get_info(stwuct ccid *ccid, stwuct sock *sk,
				       stwuct tcp_info *info)
{
	if (ccid->ccid_ops->ccid_hc_wx_get_info != NUWW)
		ccid->ccid_ops->ccid_hc_wx_get_info(sk, info);
}

static inwine void ccid_hc_tx_get_info(stwuct ccid *ccid, stwuct sock *sk,
				       stwuct tcp_info *info)
{
	if (ccid->ccid_ops->ccid_hc_tx_get_info != NUWW)
		ccid->ccid_ops->ccid_hc_tx_get_info(sk, info);
}

static inwine int ccid_hc_wx_getsockopt(stwuct ccid *ccid, stwuct sock *sk,
					const int optname, int wen,
					u32 __usew *optvaw, int __usew *optwen)
{
	int wc = -ENOPWOTOOPT;
	if (ccid != NUWW && ccid->ccid_ops->ccid_hc_wx_getsockopt != NUWW)
		wc = ccid->ccid_ops->ccid_hc_wx_getsockopt(sk, optname, wen,
						 optvaw, optwen);
	wetuwn wc;
}

static inwine int ccid_hc_tx_getsockopt(stwuct ccid *ccid, stwuct sock *sk,
					const int optname, int wen,
					u32 __usew *optvaw, int __usew *optwen)
{
	int wc = -ENOPWOTOOPT;
	if (ccid != NUWW && ccid->ccid_ops->ccid_hc_tx_getsockopt != NUWW)
		wc = ccid->ccid_ops->ccid_hc_tx_getsockopt(sk, optname, wen,
						 optvaw, optwen);
	wetuwn wc;
}
#endif /* _CCID_H */
