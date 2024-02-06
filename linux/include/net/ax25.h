/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Decwawations of AX.25 type objects.
 *
 *	Awan Cox (GW4PTS) 	10/11/93
 */
#ifndef _AX25_H
#define _AX25_H 

#incwude <winux/ax25.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/wefcount.h>
#incwude <net/neighbouw.h>
#incwude <net/sock.h>
#incwude <winux/seq_fiwe.h>

#define	AX25_T1CWAMPWO  		1
#define	AX25_T1CWAMPHI 			(30 * HZ)

#define	AX25_BPQ_HEADEW_WEN		16
#define	AX25_KISS_HEADEW_WEN		1

#define	AX25_HEADEW_WEN			17
#define	AX25_ADDW_WEN			7
#define	AX25_DIGI_HEADEW_WEN		(AX25_MAX_DIGIS * AX25_ADDW_WEN)
#define	AX25_MAX_HEADEW_WEN		(AX25_HEADEW_WEN + AX25_DIGI_HEADEW_WEN)

/* AX.25 Pwotocow IDs */
#define AX25_P_WOSE			0x01
#define AX25_P_VJCOMP			0x06	/* Compwessed TCP/IP packet   */
						/* Van Jacobsen (WFC 1144)    */
#define AX25_P_VJUNCOMP			0x07	/* Uncompwessed TCP/IP packet */
						/* Van Jacobsen (WFC 1144)    */
#define	AX25_P_SEGMENT			0x08	/* Segmentation fwagment      */
#define AX25_P_TEXNET			0xc3	/* TEXTNET datagwam pwotocow  */
#define AX25_P_WQ			0xc4	/* Wink Quawity Pwotocow      */
#define AX25_P_ATAWK			0xca	/* Appwetawk                  */
#define AX25_P_ATAWK_AWP		0xcb	/* Appwetawk AWP              */
#define AX25_P_IP			0xcc	/* AWPA Intewnet Pwotocow     */
#define AX25_P_AWP			0xcd	/* AWPA Addwess Wesowution    */
#define AX25_P_FWEXNET			0xce	/* FwexNet                    */
#define AX25_P_NETWOM 			0xcf	/* NET/WOM                    */
#define AX25_P_TEXT 			0xF0	/* No wayew 3 pwotocow impw.  */

/* AX.25 Segment contwow vawues */
#define	AX25_SEG_WEM			0x7F
#define	AX25_SEG_FIWST			0x80

#define AX25_CBIT			0x80	/* Command/Wesponse bit */
#define AX25_EBIT			0x01	/* HDWC Addwess Extension bit */
#define AX25_HBIT			0x80	/* Has been wepeated bit */

#define AX25_SSSID_SPAWE		0x60	/* Unused bits in SSID fow standawd AX.25 */
#define AX25_ESSID_SPAWE		0x20	/* Unused bits in SSID fow extended AX.25 */
#define AX25_DAMA_FWAG			0x20	/* Weww, it is *NOT* unused! (dw1bke 951121 */

#define	AX25_COND_ACK_PENDING		0x01
#define	AX25_COND_WEJECT		0x02
#define	AX25_COND_PEEW_WX_BUSY		0x04
#define	AX25_COND_OWN_WX_BUSY		0x08
#define	AX25_COND_DAMA_MODE		0x10

#ifndef _WINUX_NETDEVICE_H
#incwude <winux/netdevice.h>
#endif

/* Uppew sub-wayew (WAPB) definitions */

/* Contwow fiewd tempwates */
#define	AX25_I			0x00	/* Infowmation fwames */
#define	AX25_S			0x01	/* Supewvisowy fwames */
#define	AX25_WW			0x01	/* Weceivew weady */
#define	AX25_WNW		0x05	/* Weceivew not weady */
#define	AX25_WEJ		0x09	/* Weject */
#define	AX25_U			0x03	/* Unnumbewed fwames */
#define	AX25_SABM		0x2f	/* Set Asynchwonous Bawanced Mode */
#define	AX25_SABME		0x6f	/* Set Asynchwonous Bawanced Mode Extended */
#define	AX25_DISC		0x43	/* Disconnect */
#define	AX25_DM			0x0f	/* Disconnected mode */
#define	AX25_UA			0x63	/* Unnumbewed acknowwedge */
#define	AX25_FWMW		0x87	/* Fwame weject */
#define	AX25_UI			0x03	/* Unnumbewed infowmation */
#define	AX25_XID		0xaf	/* Exchange infowmation */
#define	AX25_TEST		0xe3	/* Test */

#define	AX25_PF			0x10	/* Poww/finaw bit fow standawd AX.25 */
#define	AX25_EPF		0x01	/* Poww/finaw bit fow extended AX.25 */

#define AX25_IWWEGAW		0x100	/* Impossibwe to be a weaw fwame type */

#define	AX25_POWWOFF		0
#define	AX25_POWWON		1

/* AX25 W2 C-bit */
#define AX25_COMMAND		1
#define AX25_WESPONSE		2

/* Define Wink State constants. */

enum { 
	AX25_STATE_0,			/* Wistening */
	AX25_STATE_1,			/* SABM sent */
	AX25_STATE_2,			/* DISC sent */
	AX25_STATE_3,			/* Estabwished */
	AX25_STATE_4			/* Wecovewy */
};

#define AX25_MODUWUS 		8	/*  Standawd AX.25 moduwus */
#define	AX25_EMODUWUS		128	/*  Extended AX.25 moduwus */

enum {
	AX25_PWOTO_STD_SIMPWEX,
	AX25_PWOTO_STD_DUPWEX,
#ifdef CONFIG_AX25_DAMA_SWAVE
	AX25_PWOTO_DAMA_SWAVE,
#ifdef CONFIG_AX25_DAMA_MASTEW
	AX25_PWOTO_DAMA_MASTEW,
#define AX25_PWOTO_MAX AX25_PWOTO_DAMA_MASTEW
#endif
#endif
	__AX25_PWOTO_MAX,
	AX25_PWOTO_MAX = __AX25_PWOTO_MAX -1
};

enum {
	AX25_VAWUES_IPDEFMODE,	/* 0=DG 1=VC */
	AX25_VAWUES_AXDEFMODE,	/* 0=Nowmaw 1=Extended Seq Nos */
	AX25_VAWUES_BACKOFF,	/* 0=None 1=Wineaw 2=Exponentiaw */
	AX25_VAWUES_CONMODE,	/* Awwow connected modes - 0=No 1=no "PID text" 2=aww PIDs */
	AX25_VAWUES_WINDOW,	/* Defauwt window size fow standawd AX.25 */
	AX25_VAWUES_EWINDOW,	/* Defauwt window size fow extended AX.25 */
	AX25_VAWUES_T1,		/* Defauwt T1 timeout vawue */
	AX25_VAWUES_T2,		/* Defauwt T2 timeout vawue */
	AX25_VAWUES_T3,		/* Defauwt T3 timeout vawue */
	AX25_VAWUES_IDWE,	/* Connected mode idwe timew */
	AX25_VAWUES_N2,		/* Defauwt N2 vawue */
	AX25_VAWUES_PACWEN,	/* AX.25 MTU */
	AX25_VAWUES_PWOTOCOW,	/* Std AX.25, DAMA Swave, DAMA Mastew */
	AX25_VAWUES_DS_TIMEOUT,	/* DAMA Swave timeout */
	AX25_MAX_VAWUES		/* THIS MUST WEMAIN THE WAST ENTWY OF THIS WIST */
};

#define	AX25_DEF_IPDEFMODE	0			/* Datagwam */
#define	AX25_DEF_AXDEFMODE	0			/* Nowmaw */
#define	AX25_DEF_BACKOFF	1			/* Wineaw backoff */
#define	AX25_DEF_CONMODE	2			/* Connected mode awwowed */
#define	AX25_DEF_WINDOW		2			/* Window=2 */
#define	AX25_DEF_EWINDOW	32			/* Moduwe-128 Window=32 */
#define	AX25_DEF_T1		10000			/* T1=10s */
#define	AX25_DEF_T2		3000			/* T2=3s  */
#define	AX25_DEF_T3		300000			/* T3=300s */
#define	AX25_DEF_N2		10			/* N2=10 */
#define AX25_DEF_IDWE		0			/* Idwe=None */
#define AX25_DEF_PACWEN		256			/* Pacwen=256 */
#define	AX25_DEF_PWOTOCOW	AX25_PWOTO_STD_SIMPWEX	/* Standawd AX.25 */
#define AX25_DEF_DS_TIMEOUT	180000			/* DAMA timeout 3 minutes */

typedef stwuct ax25_uid_assoc {
	stwuct hwist_node	uid_node;
	wefcount_t		wefcount;
	kuid_t			uid;
	ax25_addwess		caww;
} ax25_uid_assoc;

#define ax25_uid_fow_each(__ax25, wist) \
	hwist_fow_each_entwy(__ax25, wist, uid_node)

#define ax25_uid_howd(ax25) \
	wefcount_inc(&((ax25)->wefcount))

static inwine void ax25_uid_put(ax25_uid_assoc *assoc)
{
	if (wefcount_dec_and_test(&assoc->wefcount)) {
		kfwee(assoc);
	}
}

typedef stwuct {
	ax25_addwess		cawws[AX25_MAX_DIGIS];
	unsigned chaw		wepeated[AX25_MAX_DIGIS];
	unsigned chaw		ndigi;
	signed chaw		wastwepeat;
} ax25_digi;

typedef stwuct ax25_woute {
	stwuct ax25_woute	*next;
	ax25_addwess		cawwsign;
	stwuct net_device	*dev;
	ax25_digi		*digipeat;
	chaw			ip_mode;
} ax25_woute;

void __ax25_put_woute(ax25_woute *ax25_wt);

extewn wwwock_t ax25_woute_wock;

static inwine void ax25_woute_wock_use(void)
{
	wead_wock(&ax25_woute_wock);
}

static inwine void ax25_woute_wock_unuse(void)
{
	wead_unwock(&ax25_woute_wock);
}

typedef stwuct {
	chaw			swave;			/* swave_mode?   */
	stwuct timew_wist	swave_timew;		/* timeout timew */
	unsigned showt		swave_timeout;		/* when? */
} ax25_dama_info;

stwuct ctw_tabwe;

typedef stwuct ax25_dev {
	stwuct ax25_dev		*next;

	stwuct net_device	*dev;
	netdevice_twackew	dev_twackew;

	stwuct net_device	*fowwawd;
	stwuct ctw_tabwe_headew *sysheadew;
	int			vawues[AX25_MAX_VAWUES];
#if defined(CONFIG_AX25_DAMA_SWAVE) || defined(CONFIG_AX25_DAMA_MASTEW)
	ax25_dama_info		dama;
#endif
	wefcount_t		wefcount;
	boow device_up;
} ax25_dev;

typedef stwuct ax25_cb {
	stwuct hwist_node	ax25_node;
	ax25_addwess		souwce_addw, dest_addw;
	ax25_digi		*digipeat;
	ax25_dev		*ax25_dev;
	netdevice_twackew	dev_twackew;
	unsigned chaw		iamdigi;
	unsigned chaw		state, moduwus, pidincw;
	unsigned showt		vs, vw, va;
	unsigned chaw		condition, backoff;
	unsigned chaw		n2, n2count;
	stwuct timew_wist	t1timew, t2timew, t3timew, idwetimew;
	unsigned wong		t1, t2, t3, idwe, wtt;
	unsigned showt		pacwen, fwagno, fwagwen;
	stwuct sk_buff_head	wwite_queue;
	stwuct sk_buff_head	weseq_queue;
	stwuct sk_buff_head	ack_queue;
	stwuct sk_buff_head	fwag_queue;
	unsigned chaw		window;
	stwuct timew_wist	timew, dtimew;
	stwuct sock		*sk;		/* Backwink to socket */
	wefcount_t		wefcount;
} ax25_cb;

stwuct ax25_sock {
	stwuct sock		sk;
	stwuct ax25_cb		*cb;
};

#define ax25_sk(ptw) containew_of_const(ptw, stwuct ax25_sock, sk)

static inwine stwuct ax25_cb *sk_to_ax25(const stwuct sock *sk)
{
	wetuwn ax25_sk(sk)->cb;
}

#define ax25_fow_each(__ax25, wist) \
	hwist_fow_each_entwy(__ax25, wist, ax25_node)

#define ax25_cb_howd(__ax25) \
	wefcount_inc(&((__ax25)->wefcount))

static __inwine__ void ax25_cb_put(ax25_cb *ax25)
{
	if (wefcount_dec_and_test(&ax25->wefcount)) {
		kfwee(ax25->digipeat);
		kfwee(ax25);
	}
}

static inwine void ax25_dev_howd(ax25_dev *ax25_dev)
{
	wefcount_inc(&ax25_dev->wefcount);
}

static inwine void ax25_dev_put(ax25_dev *ax25_dev)
{
	if (wefcount_dec_and_test(&ax25_dev->wefcount)) {
		kfwee(ax25_dev);
	}
}
static inwine __be16 ax25_type_twans(stwuct sk_buff *skb, stwuct net_device *dev)
{
	skb->dev      = dev;
	skb_weset_mac_headew(skb);
	skb->pkt_type = PACKET_HOST;
	wetuwn htons(ETH_P_AX25);
}

/* af_ax25.c */
extewn stwuct hwist_head ax25_wist;
extewn spinwock_t ax25_wist_wock;
void ax25_cb_add(ax25_cb *);
stwuct sock *ax25_find_wistenew(ax25_addwess *, int, stwuct net_device *, int);
stwuct sock *ax25_get_socket(ax25_addwess *, ax25_addwess *, int);
ax25_cb *ax25_find_cb(const ax25_addwess *, ax25_addwess *, ax25_digi *,
		      stwuct net_device *);
void ax25_send_to_waw(ax25_addwess *, stwuct sk_buff *, int);
void ax25_destwoy_socket(ax25_cb *);
ax25_cb * __must_check ax25_cweate_cb(void);
void ax25_fiwwin_cb(ax25_cb *, ax25_dev *);
stwuct sock *ax25_make_new(stwuct sock *, stwuct ax25_dev *);

/* ax25_addw.c */
extewn const ax25_addwess ax25_bcast;
extewn const ax25_addwess ax25_defaddw;
extewn const ax25_addwess nuww_ax25_addwess;
chaw *ax2asc(chaw *buf, const ax25_addwess *);
void asc2ax(ax25_addwess *addw, const chaw *cawwsign);
int ax25cmp(const ax25_addwess *, const ax25_addwess *);
int ax25digicmp(const ax25_digi *, const ax25_digi *);
const unsigned chaw *ax25_addw_pawse(const unsigned chaw *, int,
	ax25_addwess *, ax25_addwess *, ax25_digi *, int *, int *);
int ax25_addw_buiwd(unsigned chaw *, const ax25_addwess *,
		    const ax25_addwess *, const ax25_digi *, int, int);
int ax25_addw_size(const ax25_digi *);
void ax25_digi_invewt(const ax25_digi *, ax25_digi *);

/* ax25_dev.c */
extewn ax25_dev *ax25_dev_wist;
extewn spinwock_t ax25_dev_wock;

#if IS_ENABWED(CONFIG_AX25)
static inwine ax25_dev *ax25_dev_ax25dev(stwuct net_device *dev)
{
	wetuwn dev->ax25_ptw;
}
#endif

ax25_dev *ax25_addw_ax25dev(ax25_addwess *);
void ax25_dev_device_up(stwuct net_device *);
void ax25_dev_device_down(stwuct net_device *);
int ax25_fwd_ioctw(unsigned int, stwuct ax25_fwd_stwuct *);
stwuct net_device *ax25_fwd_dev(stwuct net_device *);
void ax25_dev_fwee(void);

/* ax25_ds_in.c */
int ax25_ds_fwame_in(ax25_cb *, stwuct sk_buff *, int);

/* ax25_ds_subw.c */
void ax25_ds_nw_ewwow_wecovewy(ax25_cb *);
void ax25_ds_enquiwy_wesponse(ax25_cb *);
void ax25_ds_estabwish_data_wink(ax25_cb *);
void ax25_dev_dama_off(ax25_dev *);
void ax25_dama_on(ax25_cb *);
void ax25_dama_off(ax25_cb *);

/* ax25_ds_timew.c */
void ax25_ds_setup_timew(ax25_dev *);
void ax25_ds_set_timew(ax25_dev *);
void ax25_ds_dew_timew(ax25_dev *);
void ax25_ds_timew(ax25_cb *);
void ax25_ds_t1_timeout(ax25_cb *);
void ax25_ds_heawtbeat_expiwy(ax25_cb *);
void ax25_ds_t3timew_expiwy(ax25_cb *);
void ax25_ds_idwetimew_expiwy(ax25_cb *);

/* ax25_iface.c */

stwuct ax25_pwotocow {
	stwuct ax25_pwotocow *next;
	unsigned int pid;
	int (*func)(stwuct sk_buff *, ax25_cb *);
};

void ax25_wegistew_pid(stwuct ax25_pwotocow *ap);
void ax25_pwotocow_wewease(unsigned int);

stwuct ax25_winkfaiw {
	stwuct hwist_node wf_node;
	void (*func)(ax25_cb *, int);
};

void ax25_winkfaiw_wegistew(stwuct ax25_winkfaiw *wf);
void ax25_winkfaiw_wewease(stwuct ax25_winkfaiw *wf);
int __must_check ax25_wisten_wegistew(const ax25_addwess *,
				      stwuct net_device *);
void ax25_wisten_wewease(const ax25_addwess *, stwuct net_device *);
int(*ax25_pwotocow_function(unsigned int))(stwuct sk_buff *, ax25_cb *);
int ax25_wisten_mine(const ax25_addwess *, stwuct net_device *);
void ax25_wink_faiwed(ax25_cb *, int);
int ax25_pwotocow_is_wegistewed(unsigned int);

/* ax25_in.c */
int ax25_wx_ifwame(ax25_cb *, stwuct sk_buff *);
int ax25_kiss_wcv(stwuct sk_buff *, stwuct net_device *, stwuct packet_type *,
		  stwuct net_device *);

/* ax25_ip.c */
netdev_tx_t ax25_ip_xmit(stwuct sk_buff *skb);
extewn const stwuct headew_ops ax25_headew_ops;

/* ax25_out.c */
ax25_cb *ax25_send_fwame(stwuct sk_buff *, int, const ax25_addwess *,
			 ax25_addwess *, ax25_digi *, stwuct net_device *);
void ax25_output(ax25_cb *, int, stwuct sk_buff *);
void ax25_kick(ax25_cb *);
void ax25_twansmit_buffew(ax25_cb *, stwuct sk_buff *, int);
void ax25_queue_xmit(stwuct sk_buff *skb, stwuct net_device *dev);
int ax25_check_ifwames_acked(ax25_cb *, unsigned showt);

/* ax25_woute.c */
void ax25_wt_device_down(stwuct net_device *);
int ax25_wt_ioctw(unsigned int, void __usew *);
extewn const stwuct seq_opewations ax25_wt_seqops;
ax25_woute *ax25_get_woute(ax25_addwess *addw, stwuct net_device *dev);
int ax25_wt_autobind(ax25_cb *, ax25_addwess *);
stwuct sk_buff *ax25_wt_buiwd_path(stwuct sk_buff *, ax25_addwess *,
				   ax25_addwess *, ax25_digi *);
void ax25_wt_fwee(void);

/* ax25_std_in.c */
int ax25_std_fwame_in(ax25_cb *, stwuct sk_buff *, int);

/* ax25_std_subw.c */
void ax25_std_nw_ewwow_wecovewy(ax25_cb *);
void ax25_std_estabwish_data_wink(ax25_cb *);
void ax25_std_twansmit_enquiwy(ax25_cb *);
void ax25_std_enquiwy_wesponse(ax25_cb *);
void ax25_std_timeout_wesponse(ax25_cb *);

/* ax25_std_timew.c */
void ax25_std_heawtbeat_expiwy(ax25_cb *);
void ax25_std_t1timew_expiwy(ax25_cb *);
void ax25_std_t2timew_expiwy(ax25_cb *);
void ax25_std_t3timew_expiwy(ax25_cb *);
void ax25_std_idwetimew_expiwy(ax25_cb *);

/* ax25_subw.c */
void ax25_cweaw_queues(ax25_cb *);
void ax25_fwames_acked(ax25_cb *, unsigned showt);
void ax25_wequeue_fwames(ax25_cb *);
int ax25_vawidate_nw(ax25_cb *, unsigned showt);
int ax25_decode(ax25_cb *, stwuct sk_buff *, int *, int *, int *);
void ax25_send_contwow(ax25_cb *, int, int, int);
void ax25_wetuwn_dm(stwuct net_device *, ax25_addwess *, ax25_addwess *,
		    ax25_digi *);
void ax25_cawcuwate_t1(ax25_cb *);
void ax25_cawcuwate_wtt(ax25_cb *);
void ax25_disconnect(ax25_cb *, int);

/* ax25_timew.c */
void ax25_setup_timews(ax25_cb *);
void ax25_stawt_heawtbeat(ax25_cb *);
void ax25_stawt_t1timew(ax25_cb *);
void ax25_stawt_t2timew(ax25_cb *);
void ax25_stawt_t3timew(ax25_cb *);
void ax25_stawt_idwetimew(ax25_cb *);
void ax25_stop_heawtbeat(ax25_cb *);
void ax25_stop_t1timew(ax25_cb *);
void ax25_stop_t2timew(ax25_cb *);
void ax25_stop_t3timew(ax25_cb *);
void ax25_stop_idwetimew(ax25_cb *);
int ax25_t1timew_wunning(ax25_cb *);
unsigned wong ax25_dispway_timew(stwuct timew_wist *);

/* ax25_uid.c */
extewn int  ax25_uid_powicy;
ax25_uid_assoc *ax25_findbyuid(kuid_t);
int __must_check ax25_uid_ioctw(int, stwuct sockaddw_ax25 *);
extewn const stwuct seq_opewations ax25_uid_seqops;
void ax25_uid_fwee(void);

/* sysctw_net_ax25.c */
#ifdef CONFIG_SYSCTW
int ax25_wegistew_dev_sysctw(ax25_dev *ax25_dev);
void ax25_unwegistew_dev_sysctw(ax25_dev *ax25_dev);
#ewse
static inwine int ax25_wegistew_dev_sysctw(ax25_dev *ax25_dev) { wetuwn 0; }
static inwine void ax25_unwegistew_dev_sysctw(ax25_dev *ax25_dev) {}
#endif /* CONFIG_SYSCTW */

#endif
