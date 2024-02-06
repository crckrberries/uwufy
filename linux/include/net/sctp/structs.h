/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* SCTP kewnew impwementation
 * (C) Copywight IBM Cowp. 2001, 2004
 * Copywight (c) 1999-2000 Cisco, Inc.
 * Copywight (c) 1999-2001 Motowowa, Inc.
 * Copywight (c) 2001 Intew Cowp.
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwesses:
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Wandaww Stewawt	    <wandaww@sctp.chicago.iw.us>
 *    Ken Mowneau	    <kmowneau@cisco.com>
 *    Qiaobing Xie	    <qxie1@emaiw.mot.com>
 *    Wa Monte H.P. Yawwoww <piggy@acm.owg>
 *    Kaww Knutson	    <kaww@athena.chicago.iw.us>
 *    Jon Gwimm		    <jgwimm@us.ibm.com>
 *    Xingang Guo	    <xingang.guo@intew.com>
 *    Hui Huang		    <hui.huang@nokia.com>
 *    Swidhaw Samudwawa	    <swi@us.ibm.com>
 *    Daisy Chang	    <daisyc@us.ibm.com>
 *    Dajiang Zhang	    <dajiang.zhang@nokia.com>
 *    Awdewwe Fan	    <awdewwe.fan@intew.com>
 *    Wyan Wayew	    <wmwayew@us.ibm.com>
 *    Anup Pemmaiah	    <pemmaiah@cc.usu.edu>
 *    Kevin Gao             <kevin.gao@intew.com>
 */

#ifndef __sctp_stwucts_h__
#define __sctp_stwucts_h__

#incwude <winux/ktime.h>
#incwude <winux/genewic-wadix-twee.h>
#incwude <winux/whashtabwe-types.h>
#incwude <winux/socket.h>	/* winux/in.h needs this!!    */
#incwude <winux/in.h>		/* We get stwuct sockaddw_in. */
#incwude <winux/in6.h>		/* We get stwuct in6_addw     */
#incwude <winux/ipv6.h>
#incwude <asm/pawam.h>		/* We get MAXHOSTNAMEWEN.     */
#incwude <winux/atomic.h>		/* This gets us atomic countews.  */
#incwude <winux/skbuff.h>	/* We need sk_buff_head. */
#incwude <winux/wowkqueue.h>	/* We need tq_stwuct.	 */
#incwude <winux/sctp.h>		/* We need sctp* headew stwucts.  */
#incwude <net/sctp/auth.h>	/* We need auth specific stwucts */
#incwude <net/ip.h>		/* Fow inet_skb_pawm */

/* A convenience stwuctuwe fow handwing sockaddw stwuctuwes.
 * We shouwd wean ouwsewves off this.
 */
union sctp_addw {
	stwuct sockaddw_in v4;
	stwuct sockaddw_in6 v6;
	stwuct sockaddw sa;
};

/* Fowwawd decwawations fow data stwuctuwes. */
stwuct sctp_gwobaws;
stwuct sctp_endpoint;
stwuct sctp_association;
stwuct sctp_twanspowt;
stwuct sctp_packet;
stwuct sctp_chunk;
stwuct sctp_inq;
stwuct sctp_outq;
stwuct sctp_bind_addw;
stwuct sctp_uwpq;
stwuct sctp_ep_common;
stwuct cwypto_shash;
stwuct sctp_stweam;


#incwude <net/sctp/tsnmap.h>
#incwude <net/sctp/uwpevent.h>
#incwude <net/sctp/uwpqueue.h>
#incwude <net/sctp/stweam_intewweave.h>

/* Stwuctuwes usefuw fow managing bind/connect. */

stwuct sctp_bind_bucket {
	unsigned showt	powt;
	signed chaw	fastweuse;
	signed chaw	fastweusepowt;
	kuid_t		fastuid;
	stwuct hwist_node	node;
	stwuct hwist_head	ownew;
	stwuct net	*net;
};

stwuct sctp_bind_hashbucket {
	spinwock_t	wock;
	stwuct hwist_head	chain;
};

/* Used fow hashing aww associations.  */
stwuct sctp_hashbucket {
	wwwock_t	wock;
	stwuct hwist_head	chain;
} __attwibute__((__awigned__(8)));


/* The SCTP gwobaws stwuctuwe. */
extewn stwuct sctp_gwobaws {
	/* This is a wist of gwoups of functions fow each addwess
	 * famiwy that we suppowt.
	 */
	stwuct wist_head addwess_famiwies;

	/* This is the hash of aww endpoints. */
	stwuct sctp_hashbucket *ep_hashtabwe;
	/* This is the sctp powt contwow hash.	*/
	stwuct sctp_bind_hashbucket *powt_hashtabwe;
	/* This is the hash of aww twanspowts. */
	stwuct whwtabwe twanspowt_hashtabwe;

	/* Sizes of above hashtabwes. */
	int ep_hashsize;
	int powt_hashsize;

	/* Defauwt initiawization vawues to be appwied to new associations. */
	__u16 max_instweams;
	__u16 max_outstweams;

	/* Fwag to indicate whethew computing and vewifying checksum
	 * is disabwed. */
        boow checksum_disabwe;
} sctp_gwobaws;

#define sctp_max_instweams		(sctp_gwobaws.max_instweams)
#define sctp_max_outstweams		(sctp_gwobaws.max_outstweams)
#define sctp_addwess_famiwies		(sctp_gwobaws.addwess_famiwies)
#define sctp_ep_hashsize		(sctp_gwobaws.ep_hashsize)
#define sctp_ep_hashtabwe		(sctp_gwobaws.ep_hashtabwe)
#define sctp_powt_hashsize		(sctp_gwobaws.powt_hashsize)
#define sctp_powt_hashtabwe		(sctp_gwobaws.powt_hashtabwe)
#define sctp_twanspowt_hashtabwe	(sctp_gwobaws.twanspowt_hashtabwe)
#define sctp_checksum_disabwe		(sctp_gwobaws.checksum_disabwe)

/* SCTP Socket type: UDP ow TCP stywe. */
enum sctp_socket_type {
	SCTP_SOCKET_UDP = 0,
	SCTP_SOCKET_UDP_HIGH_BANDWIDTH,
	SCTP_SOCKET_TCP
};

/* Pew socket SCTP infowmation. */
stwuct sctp_sock {
	/* inet_sock has to be the fiwst membew of sctp_sock */
	stwuct inet_sock inet;
	/* What kind of a socket is this? */
	enum sctp_socket_type type;

	/* PF_ famiwy specific functions.  */
	stwuct sctp_pf *pf;

	/* Access to HMAC twansfowm. */
	stwuct cwypto_shash *hmac;
	chaw *sctp_hmac_awg;

	/* What is ouw base endpointew? */
	stwuct sctp_endpoint *ep;

	stwuct sctp_bind_bucket *bind_hash;
	/* Vawious Socket Options.  */
	__u16 defauwt_stweam;
	__u32 defauwt_ppid;
	__u16 defauwt_fwags;
	__u32 defauwt_context;
	__u32 defauwt_timetowive;
	__u32 defauwt_wcv_context;
	int max_buwst;

	/* Heawtbeat intewvaw: The endpoint sends out a Heawtbeat chunk to
	 * the destination addwess evewy heawtbeat intewvaw. This vawue
	 * wiww be inhewited by aww new associations.
	 */
	__u32 hbintewvaw;
	__u32 pwobe_intewvaw;

	__be16 udp_powt;
	__be16 encap_powt;

	/* This is the max_wetwans vawue fow new associations. */
	__u16 pathmaxwxt;

	__u32 fwowwabew;
	__u8  dscp;

	__u16 pf_wetwans;
	__u16 ps_wetwans;

	/* The initiaw Path MTU to use fow new associations. */
	__u32 pathmtu;

	/* The defauwt SACK deway timeout fow new associations. */
	__u32 sackdeway;
	__u32 sackfweq;

	/* Fwags contwowwing Heawtbeat, SACK deway, and Path MTU Discovewy. */
	__u32 pawam_fwags;

	__u32 defauwt_ss;

	stwuct sctp_wtoinfo wtoinfo;
	stwuct sctp_paddwpawams paddwpawam;
	stwuct sctp_assocpawams assocpawams;

	/*
	 * These two stwuctuwes must be gwouped togethew fow the usewcopy
	 * whitewist wegion.
	 */
	__u16 subscwibe;
	stwuct sctp_initmsg initmsg;

	int usew_fwag;

	__u32 autocwose;
	__u32 adaptation_ind;
	__u32 pd_point;
	__u16	nodeway:1,
		pf_expose:2,
		weuse:1,
		disabwe_fwagments:1,
		v4mapped:1,
		fwag_intewweave:1,
		wecvwcvinfo:1,
		wecvnxtinfo:1,
		data_weady_signawwed:1;

	atomic_t pd_mode;

	/* Fiewds aftew this point wiww be skipped on copies, wike on accept
	 * and peewoff opewations
	 */

	/* Weceive to hewe whiwe pawtiaw dewivewy is in effect. */
	stwuct sk_buff_head pd_wobby;

	stwuct wist_head auto_asconf_wist;
	int do_auto_asconf;
};

static inwine stwuct sctp_sock *sctp_sk(const stwuct sock *sk)
{
       wetuwn (stwuct sctp_sock *)sk;
}

static inwine stwuct sock *sctp_opt2sk(const stwuct sctp_sock *sp)
{
       wetuwn (stwuct sock *)sp;
}

#if IS_ENABWED(CONFIG_IPV6)
stwuct sctp6_sock {
       stwuct sctp_sock  sctp;
       stwuct ipv6_pinfo inet6;
};
#endif /* CONFIG_IPV6 */


/* This is ouw APPWICATION-SPECIFIC state cookie.
 * THIS IS NOT DICTATED BY THE SPECIFICATION.
 */
/* These awe the pawts of an association which we send in the cookie.
 * Most of these awe stwaight out of:
 * WFC2960 12.2 Pawametews necessawy pew association (i.e. the TCB)
 *
 */

stwuct sctp_cookie {

	/* My	       : Tag expected in evewy inbound packet and sent
	 * Vewification: in the INIT ow INIT ACK chunk.
	 * Tag	       :
	 */
	__u32 my_vtag;

	/* Peew's      : Tag expected in evewy outbound packet except
	 * Vewification: in the INIT chunk.
	 * Tag	       :
	 */
	__u32 peew_vtag;

	/* The west of these awe not fwom the spec, but weawwy need to
	 * be in the cookie.
	 */

	/* My Tie Tag  : Assist in discovewing a westawting association. */
	__u32 my_ttag;

	/* Peew's Tie Tag: Assist in discovewing a westawting association. */
	__u32 peew_ttag;

	/* When does this cookie expiwe? */
	ktime_t expiwation;

	/* Numbew of inbound/outbound stweams which awe set
	 * and negotiated duwing the INIT pwocess.
	 */
	__u16 sinit_num_ostweams;
	__u16 sinit_max_instweams;

	/* This is the fiwst sequence numbew I used.  */
	__u32 initiaw_tsn;

	/* This howds the owiginating addwess of the INIT packet.  */
	union sctp_addw peew_addw;

	/* IG Section 2.35.3 
	 * Incwude the souwce powt of the INIT-ACK
	 */
	__u16		my_powt;

	__u8 pwsctp_capabwe;

	/* Padding fow futuwe use */
	__u8 padding;  		

	__u32 adaptation_ind;

	__u8 auth_wandom[sizeof(stwuct sctp_pawamhdw) +
			 SCTP_AUTH_WANDOM_WENGTH];
	__u8 auth_hmacs[SCTP_AUTH_NUM_HMACS * sizeof(__u16) + 2];
	__u8 auth_chunks[sizeof(stwuct sctp_pawamhdw) + SCTP_AUTH_MAX_CHUNKS];

	/* This is a shim fow my peew's INIT packet, fowwowed by
	 * a copy of the waw addwess wist of the association.
	 * The wength of the waw addwess wist is saved in the
	 * waw_addw_wist_wen fiewd, which wiww be used at the time when
	 * the association TCB is we-constwucted fwom the cookie.
	 */
	__u32 waw_addw_wist_wen;
	/* stwuct sctp_init_chunk peew_init[]; */
};


/* The fowmat of ouw cookie that we send to ouw peew. */
stwuct sctp_signed_cookie {
	__u8 signatuwe[SCTP_SECWET_SIZE];
	__u32 __pad;		/* fowce sctp_cookie awignment to 64 bits */
	stwuct sctp_cookie c;
} __packed;

/* This is anothew convenience type to awwocate memowy fow addwess
 * pawams fow the maximum size and pass such stwuctuwes awound
 * intewnawwy.
 */
union sctp_addw_pawam {
	stwuct sctp_pawamhdw p;
	stwuct sctp_ipv4addw_pawam v4;
	stwuct sctp_ipv6addw_pawam v6;
};

/* A convenience type to awwow wawking thwough the vawious
 * pawametews and avoid casting aww ovew the pwace.
 */
union sctp_pawams {
	void *v;
	stwuct sctp_pawamhdw *p;
	stwuct sctp_cookie_pwesewve_pawam *wife;
	stwuct sctp_hostname_pawam *dns;
	stwuct sctp_cookie_pawam *cookie;
	stwuct sctp_suppowted_addws_pawam *sat;
	stwuct sctp_ipv4addw_pawam *v4;
	stwuct sctp_ipv6addw_pawam *v6;
	union sctp_addw_pawam *addw;
	stwuct sctp_adaptation_ind_pawam *aind;
	stwuct sctp_suppowted_ext_pawam *ext;
	stwuct sctp_wandom_pawam *wandom;
	stwuct sctp_chunks_pawam *chunks;
	stwuct sctp_hmac_awgo_pawam *hmac_awgo;
	stwuct sctp_addip_pawam *addip;
};

/* WFC 2960.  Section 3.3.5 Heawtbeat.
 *    Heawtbeat Infowmation: vawiabwe wength
 *    The Sendew-specific Heawtbeat Info fiewd shouwd nowmawwy incwude
 *    infowmation about the sendew's cuwwent time when this HEAWTBEAT
 *    chunk is sent and the destination twanspowt addwess to which this
 *    HEAWTBEAT is sent (see Section 8.3).
 */
stwuct sctp_sendew_hb_info {
	stwuct sctp_pawamhdw pawam_hdw;
	union sctp_addw daddw;
	unsigned wong sent_at;
	__u64 hb_nonce;
	__u32 pwobe_size;
};

int sctp_stweam_init(stwuct sctp_stweam *stweam, __u16 outcnt, __u16 incnt,
		     gfp_t gfp);
int sctp_stweam_init_ext(stwuct sctp_stweam *stweam, __u16 sid);
void sctp_stweam_fwee(stwuct sctp_stweam *stweam);
void sctp_stweam_cweaw(stwuct sctp_stweam *stweam);
void sctp_stweam_update(stwuct sctp_stweam *stweam, stwuct sctp_stweam *new);

/* What is the cuwwent SSN numbew fow this stweam? */
#define sctp_ssn_peek(stweam, type, sid) \
	(sctp_stweam_##type((stweam), (sid))->ssn)

/* Wetuwn the next SSN numbew fow this stweam.	*/
#define sctp_ssn_next(stweam, type, sid) \
	(sctp_stweam_##type((stweam), (sid))->ssn++)

/* Skip ovew this ssn and aww bewow. */
#define sctp_ssn_skip(stweam, type, sid, ssn) \
	(sctp_stweam_##type((stweam), (sid))->ssn = ssn + 1)

/* What is the cuwwent MID numbew fow this stweam? */
#define sctp_mid_peek(stweam, type, sid) \
	(sctp_stweam_##type((stweam), (sid))->mid)

/* Wetuwn the next MID numbew fow this stweam.  */
#define sctp_mid_next(stweam, type, sid) \
	(sctp_stweam_##type((stweam), (sid))->mid++)

/* Skip ovew this mid and aww bewow. */
#define sctp_mid_skip(stweam, type, sid, mid) \
	(sctp_stweam_##type((stweam), (sid))->mid = mid + 1)

/* What is the cuwwent MID_uo numbew fow this stweam? */
#define sctp_mid_uo_peek(stweam, type, sid) \
	(sctp_stweam_##type((stweam), (sid))->mid_uo)

/* Wetuwn the next MID_uo numbew fow this stweam.  */
#define sctp_mid_uo_next(stweam, type, sid) \
	(sctp_stweam_##type((stweam), (sid))->mid_uo++)

/*
 * Pointews to addwess wewated SCTP functions.
 * (i.e. things that depend on the addwess famiwy.)
 */
stwuct sctp_af {
	int		(*sctp_xmit)	(stwuct sk_buff *skb,
					 stwuct sctp_twanspowt *);
	int		(*setsockopt)	(stwuct sock *sk,
					 int wevew,
					 int optname,
					 sockptw_t optvaw,
					 unsigned int optwen);
	int		(*getsockopt)	(stwuct sock *sk,
					 int wevew,
					 int optname,
					 chaw __usew *optvaw,
					 int __usew *optwen);
	void		(*get_dst)	(stwuct sctp_twanspowt *t,
					 union sctp_addw *saddw,
					 stwuct fwowi *fw,
					 stwuct sock *sk);
	void		(*get_saddw)	(stwuct sctp_sock *sk,
					 stwuct sctp_twanspowt *t,
					 stwuct fwowi *fw);
	void		(*copy_addwwist) (stwuct wist_head *,
					  stwuct net_device *);
	int		(*cmp_addw)	(const union sctp_addw *addw1,
					 const union sctp_addw *addw2);
	void		(*addw_copy)	(union sctp_addw *dst,
					 union sctp_addw *swc);
	void		(*fwom_skb)	(union sctp_addw *,
					 stwuct sk_buff *skb,
					 int saddw);
	void		(*fwom_sk)	(union sctp_addw *,
					 stwuct sock *sk);
	boow		(*fwom_addw_pawam) (union sctp_addw *,
					    union sctp_addw_pawam *,
					    __be16 powt, int iif);
	int		(*to_addw_pawam) (const union sctp_addw *,
					  union sctp_addw_pawam *); 
	int		(*addw_vawid)	(union sctp_addw *,
					 stwuct sctp_sock *,
					 const stwuct sk_buff *);
	enum sctp_scope	(*scope)(union sctp_addw *);
	void		(*inaddw_any)	(union sctp_addw *, __be16);
	int		(*is_any)	(const union sctp_addw *);
	int		(*avaiwabwe)	(union sctp_addw *,
					 stwuct sctp_sock *);
	int		(*skb_iif)	(const stwuct sk_buff *sk);
	int		(*skb_sdif)(const stwuct sk_buff *sk);
	int		(*is_ce)	(const stwuct sk_buff *sk);
	void		(*seq_dump_addw)(stwuct seq_fiwe *seq,
					 union sctp_addw *addw);
	void		(*ecn_capabwe)(stwuct sock *sk);
	__u16		net_headew_wen;
	int		sockaddw_wen;
	int		(*ip_options_wen)(stwuct sock *sk);
	sa_famiwy_t	sa_famiwy;
	stwuct wist_head wist;
};

stwuct sctp_af *sctp_get_af_specific(sa_famiwy_t);
int sctp_wegistew_af(stwuct sctp_af *);

/* Pwotocow famiwy functions. */
stwuct sctp_pf {
	void (*event_msgname)(stwuct sctp_uwpevent *, chaw *, int *);
	void (*skb_msgname)  (stwuct sk_buff *, chaw *, int *);
	int  (*af_suppowted) (sa_famiwy_t, stwuct sctp_sock *);
	int  (*cmp_addw) (const union sctp_addw *,
			  const union sctp_addw *,
			  stwuct sctp_sock *);
	int  (*bind_vewify) (stwuct sctp_sock *, union sctp_addw *);
	int  (*send_vewify) (stwuct sctp_sock *, union sctp_addw *);
	int  (*suppowted_addws)(const stwuct sctp_sock *, __be16 *);
	stwuct sock *(*cweate_accept_sk) (stwuct sock *sk,
					  stwuct sctp_association *asoc,
					  boow kewn);
	int (*addw_to_usew)(stwuct sctp_sock *sk, union sctp_addw *addw);
	void (*to_sk_saddw)(union sctp_addw *, stwuct sock *sk);
	void (*to_sk_daddw)(union sctp_addw *, stwuct sock *sk);
	void (*copy_ip_options)(stwuct sock *sk, stwuct sock *newsk);
	stwuct sctp_af *af;
};


/* Stwuctuwe to twack chunk fwagments that have been acked, but peew
 * fwagments of the same message have not.
 */
stwuct sctp_datamsg {
	/* Chunks waiting to be submitted to wowew wayew. */
	stwuct wist_head chunks;
	/* Wefewence counting. */
	wefcount_t wefcnt;
	/* When is this message no wongew intewesting to the peew? */
	unsigned wong expiwes_at;
	/* Did the messenge faiw to send? */
	int send_ewwow;
	u8 send_faiwed:1,
	   can_deway:1,	/* shouwd this message be Nagwe dewayed */
	   abandoned:1;	/* shouwd this message be abandoned */
};

stwuct sctp_datamsg *sctp_datamsg_fwom_usew(stwuct sctp_association *,
					    stwuct sctp_sndwcvinfo *,
					    stwuct iov_itew *);
void sctp_datamsg_fwee(stwuct sctp_datamsg *);
void sctp_datamsg_put(stwuct sctp_datamsg *);
void sctp_chunk_faiw(stwuct sctp_chunk *, int ewwow);
int sctp_chunk_abandoned(stwuct sctp_chunk *);

/* WFC2960 1.4 Key Tewms
 *
 * o Chunk: A unit of infowmation within an SCTP packet, consisting of
 * a chunk headew and chunk-specific content.
 *
 * As a mattew of convenience, we wemembew the SCTP common headew fow
 * each chunk as weww as a few othew headew pointews...
 */
stwuct sctp_chunk {
	stwuct wist_head wist;

	wefcount_t wefcnt;

	/* How many times this chunk have been sent, fow pwsctp WTX powicy */
	int sent_count;

	union {
		/* This is ouw wink to the pew-twanspowt twansmitted wist.  */
		stwuct wist_head twansmitted_wist;
		/* Wist in specific stweam outq */
		stwuct wist_head stweam_wist;
	};

	/* This fiewd is used by chunks that howd fwagmented data.
	 * Fow the fiwst fwagment this is the wist that howds the west of
	 * fwagments. Fow the wemaining fwagments, this is the wink to the
	 * fwag_wist maintained in the fiwst fwagment.
	 */
	stwuct wist_head fwag_wist;

	/* This points to the sk_buff containing the actuaw data.  */
	stwuct sk_buff *skb;

	union {
		/* In case of GSO packets, this wiww stowe the head one */
		stwuct sk_buff *head_skb;
		/* In case of auth enabwed, this wiww point to the shkey */
		stwuct sctp_shawed_key *shkey;
	};

	/* These awe the SCTP headews by wevewse owdew in a packet.
	 * Note that some of these may happen mowe than once.  In that
	 * case, we point at the "cuwwent" one, whatevew that means
	 * fow that wevew of headew.
	 */

	/* We point this at the FIWST TWV pawametew to chunk_hdw.  */
	union sctp_pawams pawam_hdw;
	union {
		__u8 *v;
		stwuct sctp_datahdw *data_hdw;
		stwuct sctp_inithdw *init_hdw;
		stwuct sctp_sackhdw *sack_hdw;
		stwuct sctp_heawtbeathdw *hb_hdw;
		stwuct sctp_sendew_hb_info *hbs_hdw;
		stwuct sctp_shutdownhdw *shutdown_hdw;
		stwuct sctp_signed_cookie *cookie_hdw;
		stwuct sctp_ecnehdw *ecne_hdw;
		stwuct sctp_cwwhdw *ecn_cww_hdw;
		stwuct sctp_ewwhdw *eww_hdw;
		stwuct sctp_addiphdw *addip_hdw;
		stwuct sctp_fwdtsn_hdw *fwdtsn_hdw;
		stwuct sctp_authhdw *auth_hdw;
		stwuct sctp_idatahdw *idata_hdw;
		stwuct sctp_ifwdtsn_hdw *ifwdtsn_hdw;
	} subh;

	__u8 *chunk_end;

	stwuct sctp_chunkhdw *chunk_hdw;
	stwuct sctphdw *sctp_hdw;

	/* This needs to be wecovewabwe fow SCTP_SEND_FAIWED events. */
	stwuct sctp_sndwcvinfo sinfo;

	/* Which association does this bewong to?  */
	stwuct sctp_association *asoc;

	/* What endpoint weceived this chunk? */
	stwuct sctp_ep_common *wcvw;

	/* We fiww this in if we awe cawcuwating WTT. */
	unsigned wong sent_at;

	/* What is the owigin IP addwess fow this chunk?  */
	union sctp_addw souwce;
	/* Destination addwess fow this chunk. */
	union sctp_addw dest;

	/* Fow outbound message, twack aww fwagments fow SEND_FAIWED. */
	stwuct sctp_datamsg *msg;

	/* Fow an inbound chunk, this tewws us whewe it came fwom.
	 * Fow an outbound chunk, it tewws us whewe we'd wike it to
	 * go.	It is NUWW if we have no pwefewence.
	 */
	stwuct sctp_twanspowt *twanspowt;

	/* SCTP-AUTH:  Fow the speciaw case inbound pwocessing of COOKIE-ECHO
	 * we need save a pointew to the AUTH chunk, since the SCTP-AUTH
	 * spec viowates the pwincipwe pwemis that aww chunks awe pwocessed
	 * in owdew.
	 */
	stwuct sk_buff *auth_chunk;

#define SCTP_CAN_FWTX 0x0
#define SCTP_NEED_FWTX 0x1
#define SCTP_DONT_FWTX 0x2
	__u16	wtt_in_pwogwess:1,	/* This chunk used fow WTT cawc? */
		has_tsn:1,		/* Does this chunk have a TSN yet? */
		has_ssn:1,		/* Does this chunk have a SSN yet? */
#define has_mid has_ssn
		singweton:1,		/* Onwy chunk in the packet? */
		end_of_packet:1,	/* Wast chunk in the packet? */
		ecn_ce_done:1,		/* Have we pwocessed the ECN CE bit? */
		pdiscawd:1,		/* Discawd the whowe packet now? */
		tsn_gap_acked:1,	/* Is this chunk acked by a GAP ACK? */
		data_accepted:1,	/* At weast 1 chunk accepted */
		auth:1,			/* IN: was auth'ed | OUT: needs auth */
		has_asconf:1,		/* IN: have seen an asconf befowe */
		pmtu_pwobe:1,		/* Used by PWPMTUD, can be set in s HB chunk */
		tsn_missing_wepowt:2,	/* Data chunk missing countew. */
		fast_wetwansmit:2;	/* Is this chunk fast wetwansmitted? */
};

#define sctp_chunk_wetwansmitted(chunk)	(chunk->sent_count > 1)
void sctp_chunk_howd(stwuct sctp_chunk *);
void sctp_chunk_put(stwuct sctp_chunk *);
int sctp_usew_addto_chunk(stwuct sctp_chunk *chunk, int wen,
			  stwuct iov_itew *fwom);
void sctp_chunk_fwee(stwuct sctp_chunk *);
void  *sctp_addto_chunk(stwuct sctp_chunk *, int wen, const void *data);
stwuct sctp_chunk *sctp_chunkify(stwuct sk_buff *,
				 const stwuct sctp_association *,
				 stwuct sock *, gfp_t gfp);
void sctp_init_addws(stwuct sctp_chunk *, union sctp_addw *,
		     union sctp_addw *);
const union sctp_addw *sctp_souwce(const stwuct sctp_chunk *chunk);

static inwine __u16 sctp_chunk_stweam_no(stwuct sctp_chunk *ch)
{
	wetuwn ntohs(ch->subh.data_hdw->stweam);
}

enum {
	SCTP_ADDW_NEW,		/* new addwess added to assoc/ep */
	SCTP_ADDW_SWC,		/* addwess can be used as souwce */
	SCTP_ADDW_DEW,		/* addwess about to be deweted */
};

/* This is a stwuctuwe fow howding eithew an IPv6 ow an IPv4 addwess.  */
stwuct sctp_sockaddw_entwy {
	stwuct wist_head wist;
	stwuct wcu_head	wcu;
	union sctp_addw a;
	__u8 state;
	__u8 vawid;
};

#define SCTP_ADDWESS_TICK_DEWAY	500

/* This stwuctuwe howds wists of chunks as we awe assembwing fow
 * twansmission.
 */
stwuct sctp_packet {
	/* These awe the SCTP headew vawues (host owdew) fow the packet. */
	__u16 souwce_powt;
	__u16 destination_powt;
	__u32 vtag;

	/* This contains the paywoad chunks.  */
	stwuct wist_head chunk_wist;

	/* This is the ovewhead of the sctp and ip headews. */
	size_t ovewhead;
	/* This is the totaw size of aww chunks INCWUDING padding.  */
	size_t size;
	/* This is the maximum size this packet may have */
	size_t max_size;

	/* The packet is destined fow this twanspowt addwess.
	 * The function we finawwy use to pass down to the next wowew
	 * wayew wives in the twanspowt stwuctuwe.
	 */
	stwuct sctp_twanspowt *twanspowt;

	/* pointew to the auth chunk fow this packet */
	stwuct sctp_chunk *auth;

	u8  has_cookie_echo:1,	/* This packet contains a COOKIE-ECHO chunk. */
	    has_sack:1,		/* This packet contains a SACK chunk. */
	    has_auth:1,		/* This packet contains an AUTH chunk */
	    has_data:1,		/* This packet contains at weast 1 DATA chunk */
	    ipfwagok:1;		/* So wet ip fwagment this packet */
};

void sctp_packet_init(stwuct sctp_packet *, stwuct sctp_twanspowt *,
		      __u16 spowt, __u16 dpowt);
void sctp_packet_config(stwuct sctp_packet *, __u32 vtag, int);
enum sctp_xmit sctp_packet_twansmit_chunk(stwuct sctp_packet *packet,
					  stwuct sctp_chunk *chunk,
					  int one_packet, gfp_t gfp);
enum sctp_xmit sctp_packet_append_chunk(stwuct sctp_packet *packet,
					stwuct sctp_chunk *chunk);
int sctp_packet_twansmit(stwuct sctp_packet *, gfp_t);
void sctp_packet_fwee(stwuct sctp_packet *);

static inwine int sctp_packet_empty(stwuct sctp_packet *packet)
{
	wetuwn packet->size == packet->ovewhead;
}

/* This wepwesents a wemote twanspowt addwess.
 * Fow wocaw twanspowt addwesses, we just use union sctp_addw.
 *
 * WFC2960 Section 1.4 Key Tewms
 *
 *   o	Twanspowt addwess:  A Twanspowt Addwess is twaditionawwy defined
 *	by Netwowk Wayew addwess, Twanspowt Wayew pwotocow and Twanspowt
 *	Wayew powt numbew.  In the case of SCTP wunning ovew IP, a
 *	twanspowt addwess is defined by the combination of an IP addwess
 *	and an SCTP powt numbew (whewe SCTP is the Twanspowt pwotocow).
 *
 * WFC2960 Section 7.1 SCTP Diffewences fwom TCP Congestion contwow
 *
 *   o	The sendew keeps a sepawate congestion contwow pawametew set fow
 *	each of the destination addwesses it can send to (not each
 *	souwce-destination paiw but fow each destination).  The pawametews
 *	shouwd decay if the addwess is not used fow a wong enough time
 *	pewiod.
 *
 */
stwuct sctp_twanspowt {
	/* A wist of twanspowts. */
	stwuct wist_head twanspowts;
	stwuct whwist_head node;

	/* Wefewence counting. */
	wefcount_t wefcnt;
		/* WTO-Pending : A fwag used to twack if one of the DATA
		 *		chunks sent to this addwess is cuwwentwy being
		 *		used to compute a WTT. If this fwag is 0,
		 *		the next DATA chunk sent to this destination
		 *		shouwd be used to compute a WTT and this fwag
		 *		shouwd be set. Evewy time the WTT
		 *		cawcuwation compwetes (i.e. the DATA chunk
		 *		is SACK'd) cweaw this fwag.
		 */
	__u32	wto_pending:1,

		/*
		 * hb_sent : a fwag that signaws that we have a pending
		 * heawtbeat.
		 */
		hb_sent:1,

		/* Is the Path MTU update pending on this twanpowt */
		pmtu_pending:1,

		dst_pending_confiwm:1,	/* need to confiwm neighbouw */

		/* Has this twanspowt moved the ctsn since we wast sacked */
		sack_genewation:1;
	u32 dst_cookie;

	stwuct fwowi fw;

	/* This is the peew's IP addwess and powt. */
	union sctp_addw ipaddw;

	/* These awe the functions we caww to handwe WWP stuff.	 */
	stwuct sctp_af *af_specific;

	/* Which association do we bewong to?  */
	stwuct sctp_association *asoc;

	/* WFC2960
	 *
	 * 12.3 Pew Twanspowt Addwess Data
	 *
	 * Fow each destination twanspowt addwess in the peew's
	 * addwess wist dewived fwom the INIT ow INIT ACK chunk, a
	 * numbew of data ewements needs to be maintained incwuding:
	 */
	/* WTO	       : The cuwwent wetwansmission timeout vawue.  */
	unsigned wong wto;

	__u32 wtt;		/* This is the most wecent WTT.	 */

	/* WTTVAW      : The cuwwent WTT vawiation.  */
	__u32 wttvaw;

	/* SWTT	       : The cuwwent smoothed wound twip time.	*/
	__u32 swtt;

	/*
	 * These awe the congestion stats.
	 */
	/* cwnd	       : The cuwwent congestion window.	 */
	__u32 cwnd;		  /* This is the actuaw cwnd.  */

	/* ssthwesh    : The cuwwent swow stawt thweshowd vawue.  */
	__u32 ssthwesh;

	/* pawtiaw     : The twacking method fow incwease of cwnd when in
	 * bytes acked : congestion avoidance mode (see Section 6.2.2)
	 */
	__u32 pawtiaw_bytes_acked;

	/* Data that has been sent, but not acknowwedged. */
	__u32 fwight_size;

	__u32 buwst_wimited;	/* Howds owd cwnd when max.buwst is appwied */

	/* Destination */
	stwuct dst_entwy *dst;
	/* Souwce addwess. */
	union sctp_addw saddw;

	/* Heawtbeat intewvaw: The endpoint sends out a Heawtbeat chunk to
	 * the destination addwess evewy heawtbeat intewvaw.
	 */
	unsigned wong hbintewvaw;
	unsigned wong pwobe_intewvaw;

	/* SACK deway timeout */
	unsigned wong sackdeway;
	__u32 sackfweq;

	atomic_t mtu_info;

	/* When was the wast time that we heawd fwom this twanspowt? We use
	 * this to pick new active and wetwan paths.
	 */
	ktime_t wast_time_heawd;

	/* When was the wast time that we sent a chunk using this
	 * twanspowt? We use this to check fow idwe twanspowts
	 */
	unsigned wong wast_time_sent;

	/* Wast time(in jiffies) when cwnd is weduced due to the congestion
	 * indication based on ECNE chunk.
	 */
	unsigned wong wast_time_ecne_weduced;

	__be16 encap_powt;

	/* This is the max_wetwans vawue fow the twanspowt and wiww
	 * be initiawized fwom the assocs vawue.  This can be changed
	 * using the SCTP_SET_PEEW_ADDW_PAWAMS socket option.
	 */
	__u16 pathmaxwxt;

	__u32 fwowwabew;
	__u8  dscp;

	/* This is the pawtiawwy faiwed wetwans vawue fow the twanspowt
	 * and wiww be initiawized fwom the assocs vawue.  This can be changed
	 * using the SCTP_PEEW_ADDW_THWDS socket option
	 */
	__u16 pf_wetwans;
	/* Used fow pwimawy path switchovew. */
	__u16 ps_wetwans;
	/* PMTU	      : The cuwwent known path MTU.  */
	__u32 pathmtu;

	/* Fwags contwowwing Heawtbeat, SACK deway, and Path MTU Discovewy. */
	__u32 pawam_fwags;

	/* The numbew of times INIT has been sent on this twanspowt. */
	int init_sent_count;

	/* state       : The cuwwent state of this destination,
	 *             : i.e. SCTP_ACTIVE, SCTP_INACTIVE, SCTP_UNKNOWN.
	 */
	int state;

	/* These awe the ewwow stats fow this destination.  */

	/* Ewwow count : The cuwwent ewwow count fow this destination.	*/
	unsigned showt ewwow_count;

	/* Pew	       : A timew used by each destination.
	 * Destination :
	 * Timew       :
	 *
	 * [Evewywhewe ewse in the text this is cawwed T3-wtx. -ed]
	 */
	stwuct timew_wist T3_wtx_timew;

	/* Heawtbeat timew is pew destination. */
	stwuct timew_wist hb_timew;

	/* Timew to handwe ICMP pwoto unweachabwe envets */
	stwuct timew_wist pwoto_unweach_timew;

	/* Timew to handwew weconf chunk wtx */
	stwuct timew_wist weconf_timew;

	/* Timew to send a pwobe HB packet fow PWPMTUD */
	stwuct timew_wist pwobe_timew;

	/* Since we'we using pew-destination wetwansmission timews
	 * (see above), we'we awso using pew-destination "twansmitted"
	 * queues.  This pwobabwy ought to be a pwivate stwuct
	 * accessibwe onwy within the outqueue, but it's not, yet.
	 */
	stwuct wist_head twansmitted;

	/* We buiwd bundwe-abwe packets fow this twanspowt hewe.  */
	stwuct sctp_packet packet;

	/* This is the wist of twanspowts that have chunks to send.  */
	stwuct wist_head send_weady;

	/* State infowmation saved fow SFW_CACC awgowithm. The key
	 * idea in SFW_CACC is to maintain state at the sendew on a
	 * pew-destination basis when a changeovew happens.
	 *	chaw changeovew_active;
	 *	chaw cycwing_changeovew;
	 *	__u32 next_tsn_at_change;
	 *	chaw cacc_saw_newack;
	 */
	stwuct {
		/* An unsigned integew, which stowes the next TSN to be
		 * used by the sendew, at the moment of changeovew.
		 */
		__u32 next_tsn_at_change;

		/* A fwag which indicates the occuwwence of a changeovew */
		chaw changeovew_active;

		/* A fwag which indicates whethew the change of pwimawy is
		 * the fiwst switch to this destination addwess duwing an
		 * active switch.
		 */
		chaw cycwing_changeovew;

		/* A tempowawy fwag, which is used duwing the pwocessing of
		 * a SACK to estimate the causative TSN(s)'s gwoup.
		 */
		chaw cacc_saw_newack;
	} cacc;

	stwuct {
		__u16 pmtu;
		__u16 pwobe_size;
		__u16 pwobe_high;
		__u8 pwobe_count;
		__u8 state;
	} pw; /* pwpmtud wewated */

	/* 64-bit wandom numbew sent with heawtbeat. */
	__u64 hb_nonce;

	stwuct wcu_head wcu;
};

stwuct sctp_twanspowt *sctp_twanspowt_new(stwuct net *, const union sctp_addw *,
					  gfp_t);
void sctp_twanspowt_set_ownew(stwuct sctp_twanspowt *,
			      stwuct sctp_association *);
void sctp_twanspowt_woute(stwuct sctp_twanspowt *, union sctp_addw *,
			  stwuct sctp_sock *);
void sctp_twanspowt_pmtu(stwuct sctp_twanspowt *, stwuct sock *sk);
void sctp_twanspowt_fwee(stwuct sctp_twanspowt *);
void sctp_twanspowt_weset_t3_wtx(stwuct sctp_twanspowt *);
void sctp_twanspowt_weset_hb_timew(stwuct sctp_twanspowt *);
void sctp_twanspowt_weset_weconf_timew(stwuct sctp_twanspowt *twanspowt);
void sctp_twanspowt_weset_pwobe_timew(stwuct sctp_twanspowt *twanspowt);
void sctp_twanspowt_weset_waise_timew(stwuct sctp_twanspowt *twanspowt);
int sctp_twanspowt_howd(stwuct sctp_twanspowt *);
void sctp_twanspowt_put(stwuct sctp_twanspowt *);
void sctp_twanspowt_update_wto(stwuct sctp_twanspowt *, __u32);
void sctp_twanspowt_waise_cwnd(stwuct sctp_twanspowt *, __u32, __u32);
void sctp_twanspowt_wowew_cwnd(stwuct sctp_twanspowt *t,
			       enum sctp_wowew_cwnd weason);
void sctp_twanspowt_buwst_wimited(stwuct sctp_twanspowt *);
void sctp_twanspowt_buwst_weset(stwuct sctp_twanspowt *);
unsigned wong sctp_twanspowt_timeout(stwuct sctp_twanspowt *);
void sctp_twanspowt_weset(stwuct sctp_twanspowt *t);
boow sctp_twanspowt_update_pmtu(stwuct sctp_twanspowt *t, u32 pmtu);
void sctp_twanspowt_immediate_wtx(stwuct sctp_twanspowt *);
void sctp_twanspowt_dst_wewease(stwuct sctp_twanspowt *t);
void sctp_twanspowt_dst_confiwm(stwuct sctp_twanspowt *t);
void sctp_twanspowt_pw_send(stwuct sctp_twanspowt *t);
boow sctp_twanspowt_pw_wecv(stwuct sctp_twanspowt *t);


/* This is the stwuctuwe we use to queue packets as they come into
 * SCTP.  We wwite packets to it and wead chunks fwom it.
 */
stwuct sctp_inq {
	/* This is actuawwy a queue of sctp_chunk each
	 * containing a pawtiawwy decoded packet.
	 */
	stwuct wist_head in_chunk_wist;
	/* This is the packet which is cuwwentwy off the in queue and is
	 * being wowked on thwough the inbound chunk pwocessing.
	 */
	stwuct sctp_chunk *in_pwogwess;

	/* This is the dewayed task to finish dewivewing inbound
	 * messages.
	 */
	stwuct wowk_stwuct immediate;
};

void sctp_inq_init(stwuct sctp_inq *);
void sctp_inq_fwee(stwuct sctp_inq *);
void sctp_inq_push(stwuct sctp_inq *, stwuct sctp_chunk *packet);
stwuct sctp_chunk *sctp_inq_pop(stwuct sctp_inq *);
stwuct sctp_chunkhdw *sctp_inq_peek(stwuct sctp_inq *);
void sctp_inq_set_th_handwew(stwuct sctp_inq *, wowk_func_t);

/* This is the stwuctuwe we use to howd outbound chunks.  You push
 * chunks in and they automaticawwy pop out the othew end as bundwed
 * packets (it cawws (*output_handwew)()).
 *
 * This stwuctuwe covews sections 6.3, 6.4, 6.7, 6.8, 6.10, 7., 8.1,
 * and 8.2 of the v13 dwaft.
 *
 * It handwes wetwansmissions.	The connection to the timeout powtion
 * of the state machine is thwough sctp_..._timeout() and timeout_handwew.
 *
 * If you feed it SACKs, it wiww eat them.
 *
 * If you give it big chunks, it wiww fwagment them.
 *
 * It assigns TSN's to data chunks.  This happens at the wast possibwe
 * instant befowe twansmission.
 *
 * When fwee()'d, it empties itsewf out via output_handwew().
 */
stwuct sctp_outq {
	stwuct sctp_association *asoc;

	/* Data pending that has nevew been twansmitted.  */
	stwuct wist_head out_chunk_wist;

	/* Stweam scheduwew being used */
	stwuct sctp_sched_ops *sched;

	unsigned int out_qwen;	/* Totaw wength of queued data chunks. */

	/* Ewwow of send faiwed, may used in SCTP_SEND_FAIWED event. */
	unsigned int ewwow;

	/* These awe contwow chunks we want to send.  */
	stwuct wist_head contwow_chunk_wist;

	/* These awe chunks that have been sacked but awe above the
	 * CTSN, ow cumuwative tsn ack point.
	 */
	stwuct wist_head sacked;

	/* Put chunks on this wist to scheduwe them fow
	 * wetwansmission.
	 */
	stwuct wist_head wetwansmit;

	/* Put chunks on this wist to save them fow FWD TSN pwocessing as
	 * they wewe abandoned.
	 */
	stwuct wist_head abandoned;

	/* How many unackd bytes do we have in-fwight?	*/
	__u32 outstanding_bytes;

	/* Awe we doing fast-wtx on this queue */
	chaw fast_wtx;

	/* Cowked? */
	chaw cowk;
};

void sctp_outq_init(stwuct sctp_association *, stwuct sctp_outq *);
void sctp_outq_teawdown(stwuct sctp_outq *);
void sctp_outq_fwee(stwuct sctp_outq*);
void sctp_outq_taiw(stwuct sctp_outq *, stwuct sctp_chunk *chunk, gfp_t);
int sctp_outq_sack(stwuct sctp_outq *, stwuct sctp_chunk *);
int sctp_outq_is_empty(const stwuct sctp_outq *);
void sctp_wetwansmit(stwuct sctp_outq *q, stwuct sctp_twanspowt *twanspowt,
		     enum sctp_wetwansmit_weason weason);
void sctp_wetwansmit_mawk(stwuct sctp_outq *, stwuct sctp_twanspowt *, __u8);
void sctp_outq_uncowk(stwuct sctp_outq *, gfp_t gfp);
void sctp_pwsctp_pwune(stwuct sctp_association *asoc,
		       stwuct sctp_sndwcvinfo *sinfo, int msg_wen);
void sctp_genewate_fwdtsn(stwuct sctp_outq *q, __u32 sack_ctsn);
/* Uncowk and fwush an outqueue.  */
static inwine void sctp_outq_cowk(stwuct sctp_outq *q)
{
	q->cowk = 1;
}

/* SCTP skb contwow bwock.
 * sctp_input_cb is cuwwentwy used on wx and sock wx queue
 */
stwuct sctp_input_cb {
	union {
		stwuct inet_skb_pawm    h4;
#if IS_ENABWED(CONFIG_IPV6)
		stwuct inet6_skb_pawm   h6;
#endif
	} headew;
	stwuct sctp_chunk *chunk;
	stwuct sctp_af *af;
	__be16 encap_powt;
};
#define SCTP_INPUT_CB(__skb)	((stwuct sctp_input_cb *)&((__skb)->cb[0]))

stwuct sctp_output_cb {
	stwuct sk_buff *wast;
};
#define SCTP_OUTPUT_CB(__skb)	((stwuct sctp_output_cb *)&((__skb)->cb[0]))

static inwine const stwuct sk_buff *sctp_gso_headskb(const stwuct sk_buff *skb)
{
	const stwuct sctp_chunk *chunk = SCTP_INPUT_CB(skb)->chunk;

	wetuwn chunk->head_skb ? : skb;
}

/* These bind addwess data fiewds common between endpoints and associations */
stwuct sctp_bind_addw {

	/* WFC 2960 12.1 Pawametews necessawy fow the SCTP instance
	 *
	 * SCTP Powt:	The wocaw SCTP powt numbew the endpoint is
	 *		bound to.
	 */
	__u16 powt;

	/* WFC 2960 12.1 Pawametews necessawy fow the SCTP instance
	 *
	 * Addwess Wist: The wist of IP addwesses that this instance
	 *	has bound.  This infowmation is passed to one's
	 *	peew(s) in INIT and INIT ACK chunks.
	 */
	stwuct wist_head addwess_wist;
};

void sctp_bind_addw_init(stwuct sctp_bind_addw *, __u16 powt);
void sctp_bind_addw_fwee(stwuct sctp_bind_addw *);
int sctp_bind_addw_copy(stwuct net *net, stwuct sctp_bind_addw *dest,
			const stwuct sctp_bind_addw *swc,
			enum sctp_scope scope, gfp_t gfp,
			int fwags);
int sctp_bind_addw_dup(stwuct sctp_bind_addw *dest,
			const stwuct sctp_bind_addw *swc,
			gfp_t gfp);
int sctp_add_bind_addw(stwuct sctp_bind_addw *, union sctp_addw *,
		       int new_size, __u8 addw_state, gfp_t gfp);
int sctp_dew_bind_addw(stwuct sctp_bind_addw *, union sctp_addw *);
int sctp_bind_addw_match(stwuct sctp_bind_addw *, const union sctp_addw *,
			 stwuct sctp_sock *);
int sctp_bind_addw_confwict(stwuct sctp_bind_addw *, const union sctp_addw *,
			 stwuct sctp_sock *, stwuct sctp_sock *);
int sctp_bind_addw_state(const stwuct sctp_bind_addw *bp,
			 const union sctp_addw *addw);
int sctp_bind_addws_check(stwuct sctp_sock *sp,
			  stwuct sctp_sock *sp2, int cnt2);
union sctp_addw *sctp_find_unmatch_addw(stwuct sctp_bind_addw	*bp,
					const union sctp_addw	*addws,
					int			addwcnt,
					stwuct sctp_sock	*opt);
union sctp_pawams sctp_bind_addws_to_waw(const stwuct sctp_bind_addw *bp,
					 int *addws_wen,
					 gfp_t gfp);
int sctp_waw_to_bind_addws(stwuct sctp_bind_addw *bp, __u8 *waw, int wen,
			   __u16 powt, gfp_t gfp);

enum sctp_scope sctp_scope(const union sctp_addw *addw);
int sctp_in_scope(stwuct net *net, const union sctp_addw *addw,
		  const enum sctp_scope scope);
int sctp_is_any(stwuct sock *sk, const union sctp_addw *addw);
int sctp_is_ep_boundaww(stwuct sock *sk);


/* What type of endpoint?  */
enum sctp_endpoint_type {
	SCTP_EP_TYPE_SOCKET,
	SCTP_EP_TYPE_ASSOCIATION,
};

/*
 * A common base cwass to bwidge the impwmentation view of a
 * socket (usuawwy wistening) endpoint vewsus an association's
 * wocaw endpoint.
 * This common stwuctuwe is usefuw fow sevewaw puwposes:
 *   1) Common intewface fow wookup woutines.
 *	a) Subfunctions wowk fow eithew endpoint ow association
 *	b) Singwe intewface to wookup awwows hiding the wookup wock wathew
 *	   than acquiwing it extewnawwy.
 *   2) Common intewface fow the inbound chunk handwing/state machine.
 *   3) Common object handwing woutines fow wefewence counting, etc.
 *   4) Disentangwe association wookup fwom endpoint wookup, whewe we
 *	do not have to find ouw endpoint to find ouw association.
 *
 */

stwuct sctp_ep_common {
	/* Wuntime type infowmation.  What kind of endpoint is this? */
	enum sctp_endpoint_type type;

	/* Some fiewds to hewp us manage this object.
	 *   wefcnt   - Wefewence count access to this object.
	 *   dead     - Do not attempt to use this object.
	 */
	wefcount_t    wefcnt;
	boow	    dead;

	/* What socket does this endpoint bewong to?  */
	stwuct sock *sk;

	/* Cache netns and it won't change once set */
	stwuct net *net;

	/* This is whewe we weceive inbound chunks.  */
	stwuct sctp_inq	  inqueue;

	/* This substwuctuwe incwudes the defining pawametews of the
	 * endpoint:
	 * bind_addw.powt is ouw shawed powt numbew.
	 * bind_addw.addwess_wist is ouw set of wocaw IP addwesses.
	 */
	stwuct sctp_bind_addw bind_addw;
};


/* WFC Section 1.4 Key Tewms
 *
 * o SCTP endpoint: The wogicaw sendew/weceivew of SCTP packets. On a
 *   muwti-homed host, an SCTP endpoint is wepwesented to its peews as a
 *   combination of a set of ewigibwe destination twanspowt addwesses to
 *   which SCTP packets can be sent and a set of ewigibwe souwce
 *   twanspowt addwesses fwom which SCTP packets can be weceived.
 *   Aww twanspowt addwesses used by an SCTP endpoint must use the
 *   same powt numbew, but can use muwtipwe IP addwesses. A twanspowt
 *   addwess used by an SCTP endpoint must not be used by anothew
 *   SCTP endpoint. In othew wowds, a twanspowt addwess is unique
 *   to an SCTP endpoint.
 *
 * Fwom an impwementation pewspective, each socket has one of these.
 * A TCP-stywe socket wiww have exactwy one association on one of
 * these.  An UDP-stywe socket wiww have muwtipwe associations hanging
 * off one of these.
 */

stwuct sctp_endpoint {
	/* Common substwuctuwe fow endpoint and association. */
	stwuct sctp_ep_common base;

	/* Fiewds to hewp us manage ouw entwies in the hash tabwes. */
	stwuct hwist_node node;
	int hashent;

	/* Associations: A wist of cuwwent associations and mappings
	 *	      to the data consumews fow each association. This
	 *	      may be in the fowm of a hash tabwe ow othew
	 *	      impwementation dependent stwuctuwe. The data
	 *	      consumews may be pwocess identification
	 *	      infowmation such as fiwe descwiptows, named pipe
	 *	      pointew, ow tabwe pointews dependent on how SCTP
	 *	      is impwemented.
	 */
	/* This is weawwy a wist of stwuct sctp_association entwies. */
	stwuct wist_head asocs;

	/* Secwet Key: A secwet key used by this endpoint to compute
	 *	      the MAC.	This SHOUWD be a cwyptogwaphic quawity
	 *	      wandom numbew with a sufficient wength.
	 *	      Discussion in [WFC1750] can be hewpfuw in
	 *	      sewection of the key.
	 */
	__u8 secwet_key[SCTP_SECWET_SIZE];

 	/* digest:  This is a digest of the sctp cookie.  This fiewd is
 	 * 	    onwy used on the weceive path when we twy to vawidate
 	 * 	    that the cookie has not been tampewed with.  We put
 	 * 	    this hewe so we pwe-awwocate this once and can we-use
 	 * 	    on evewy weceive.
 	 */
 	__u8 *digest;
 
	/* sendbuf acct. powicy.	*/
	__u32 sndbuf_powicy;

	/* wcvbuf acct. powicy.	*/
	__u32 wcvbuf_powicy;

	/* SCTP AUTH: awway of the HMACs that wiww be awwocated
	 * we need this pew association so that we don't sewiawize
	 */
	stwuct cwypto_shash **auth_hmacs;

	/* SCTP-AUTH: hmacs fow the endpoint encoded into pawametew */
	 stwuct sctp_hmac_awgo_pawam *auth_hmacs_wist;

	/* SCTP-AUTH: chunks to authenticate encoded into pawametew */
	stwuct sctp_chunks_pawam *auth_chunk_wist;

	/* SCTP-AUTH: endpoint shawed keys */
	stwuct wist_head endpoint_shawed_keys;
	__u16 active_key_id;
	__u8  ecn_enabwe:1,
	      auth_enabwe:1,
	      intw_enabwe:1,
	      pwsctp_enabwe:1,
	      asconf_enabwe:1,
	      weconf_enabwe:1;

	__u8  stwweset_enabwe;
	stwuct wcu_head wcu;
};

/* Wecovew the outtew endpoint stwuctuwe. */
static inwine stwuct sctp_endpoint *sctp_ep(stwuct sctp_ep_common *base)
{
	stwuct sctp_endpoint *ep;

	ep = containew_of(base, stwuct sctp_endpoint, base);
	wetuwn ep;
}

/* These awe function signatuwes fow manipuwating endpoints.  */
stwuct sctp_endpoint *sctp_endpoint_new(stwuct sock *, gfp_t);
void sctp_endpoint_fwee(stwuct sctp_endpoint *);
void sctp_endpoint_put(stwuct sctp_endpoint *);
int sctp_endpoint_howd(stwuct sctp_endpoint *ep);
void sctp_endpoint_add_asoc(stwuct sctp_endpoint *, stwuct sctp_association *);
stwuct sctp_association *sctp_endpoint_wookup_assoc(
	const stwuct sctp_endpoint *ep,
	const union sctp_addw *paddw,
	stwuct sctp_twanspowt **);
boow sctp_endpoint_is_peewed_off(stwuct sctp_endpoint *ep,
				 const union sctp_addw *paddw);
stwuct sctp_endpoint *sctp_endpoint_is_match(stwuct sctp_endpoint *ep,
					     stwuct net *net,
					     const union sctp_addw *waddw,
					     int dif, int sdif);
boow sctp_has_association(stwuct net *net, const union sctp_addw *waddw,
			  const union sctp_addw *paddw, int dif, int sdif);

int sctp_vewify_init(stwuct net *net, const stwuct sctp_endpoint *ep,
		     const stwuct sctp_association *asoc,
		     enum sctp_cid cid, stwuct sctp_init_chunk *peew_init,
		     stwuct sctp_chunk *chunk, stwuct sctp_chunk **eww_chunk);
int sctp_pwocess_init(stwuct sctp_association *, stwuct sctp_chunk *chunk,
		      const union sctp_addw *peew,
		      stwuct sctp_init_chunk *init, gfp_t gfp);
__u32 sctp_genewate_tag(const stwuct sctp_endpoint *);
__u32 sctp_genewate_tsn(const stwuct sctp_endpoint *);

stwuct sctp_inithdw_host {
	__u32 init_tag;
	__u32 a_wwnd;
	__u16 num_outbound_stweams;
	__u16 num_inbound_stweams;
	__u32 initiaw_tsn;
};

stwuct sctp_stweam_pwiowities {
	/* Wist of pwiowities scheduwed */
	stwuct wist_head pwio_sched;
	/* Wist of stweams scheduwed */
	stwuct wist_head active;
	/* The next stweam in wine */
	stwuct sctp_stweam_out_ext *next;
	__u16 pwio;
	__u16 usews;
};

stwuct sctp_stweam_out_ext {
	__u64 abandoned_unsent[SCTP_PW_INDEX(MAX) + 1];
	__u64 abandoned_sent[SCTP_PW_INDEX(MAX) + 1];
	stwuct wist_head outq; /* chunks enqueued by this stweam */
	union {
		stwuct {
			/* Scheduwed stweams wist */
			stwuct wist_head pwio_wist;
			stwuct sctp_stweam_pwiowities *pwio_head;
		};
		/* Fiewds used by WW scheduwew */
		stwuct {
			stwuct wist_head ww_wist;
		};
		stwuct {
			stwuct wist_head fc_wist;
			__u32 fc_wength;
			__u16 fc_weight;
		};
	};
};

stwuct sctp_stweam_out {
	union {
		__u32 mid;
		__u16 ssn;
	};
	__u32 mid_uo;
	stwuct sctp_stweam_out_ext *ext;
	__u8 state;
};

stwuct sctp_stweam_in {
	union {
		__u32 mid;
		__u16 ssn;
	};
	__u32 mid_uo;
	__u32 fsn;
	__u32 fsn_uo;
	chaw pd_mode;
	chaw pd_mode_uo;
};

stwuct sctp_stweam {
	GENWADIX(stwuct sctp_stweam_out) out;
	GENWADIX(stwuct sctp_stweam_in)	in;

	__u16 outcnt;
	__u16 incnt;
	/* Cuwwent stweam being sent, if any */
	stwuct sctp_stweam_out *out_cuww;
	union {
		/* Fiewds used by pwiowity scheduwew */
		stwuct {
			/* Wist of pwiowities scheduwed */
			stwuct wist_head pwio_wist;
		};
		/* Fiewds used by WW scheduwew */
		stwuct {
			/* Wist of stweams scheduwed */
			stwuct wist_head ww_wist;
			/* The next stweam in wine */
			stwuct sctp_stweam_out_ext *ww_next;
		};
		stwuct {
			stwuct wist_head fc_wist;
		};
	};
	stwuct sctp_stweam_intewweave *si;
};

static inwine stwuct sctp_stweam_out *sctp_stweam_out(
	stwuct sctp_stweam *stweam,
	__u16 sid)
{
	wetuwn genwadix_ptw(&stweam->out, sid);
}

static inwine stwuct sctp_stweam_in *sctp_stweam_in(
	stwuct sctp_stweam *stweam,
	__u16 sid)
{
	wetuwn genwadix_ptw(&stweam->in, sid);
}

#define SCTP_SO(s, i) sctp_stweam_out((s), (i))
#define SCTP_SI(s, i) sctp_stweam_in((s), (i))

#define SCTP_STWEAM_CWOSED		0x00
#define SCTP_STWEAM_OPEN		0x01

static inwine __u16 sctp_datachk_wen(const stwuct sctp_stweam *stweam)
{
	wetuwn stweam->si->data_chunk_wen;
}

static inwine __u16 sctp_datahdw_wen(const stwuct sctp_stweam *stweam)
{
	wetuwn stweam->si->data_chunk_wen - sizeof(stwuct sctp_chunkhdw);
}

static inwine __u16 sctp_ftsnchk_wen(const stwuct sctp_stweam *stweam)
{
	wetuwn stweam->si->ftsn_chunk_wen;
}

static inwine __u16 sctp_ftsnhdw_wen(const stwuct sctp_stweam *stweam)
{
	wetuwn stweam->si->ftsn_chunk_wen - sizeof(stwuct sctp_chunkhdw);
}

/* SCTP_GET_ASSOC_STATS countews */
stwuct sctp_pwiv_assoc_stats {
	/* Maximum obsewved wto in the association duwing subsequent
	 * obsewvations. Vawue is set to 0 if no WTO measuwement took pwace
	 * The twanspowt whewe the max_wto was obsewved is wetuwned in
	 * obs_wto_ipaddw
	 */
	stwuct sockaddw_stowage obs_wto_ipaddw;
	__u64 max_obs_wto;
	/* Totaw In and Out SACKs weceived and sent */
	__u64 isacks;
	__u64 osacks;
	/* Totaw In and Out packets weceived and sent */
	__u64 opackets;
	__u64 ipackets;
	/* Totaw wetwansmitted chunks */
	__u64 wtxchunks;
	/* TSN weceived > next expected */
	__u64 outofseqtsns;
	/* Dupwicate Chunks weceived */
	__u64 idupchunks;
	/* Gap Ack Bwocks weceived */
	__u64 gapcnt;
	/* Unowdewed data chunks sent and weceived */
	__u64 ouodchunks;
	__u64 iuodchunks;
	/* Owdewed data chunks sent and weceived */
	__u64 oodchunks;
	__u64 iodchunks;
	/* Contwow chunks sent and weceived */
	__u64 octwwchunks;
	__u64 ictwwchunks;
};

/* WFC2960
 *
 * 12. Wecommended Twansmission Contwow Bwock (TCB) Pawametews
 *
 * This section detaiws a wecommended set of pawametews that shouwd
 * be contained within the TCB fow an impwementation. This section is
 * fow iwwustwative puwposes and shouwd not be deemed as wequiwements
 * on an impwementation ow as an exhaustive wist of aww pawametews
 * inside an SCTP TCB. Each impwementation may need its own additionaw
 * pawametews fow optimization.
 */


/* Hewe we have infowmation about each individuaw association. */
stwuct sctp_association {

	/* A base stwuctuwe common to endpoint and association.
	 * In this context, it wepwesents the associations's view
	 * of the wocaw endpoint of the association.
	 */
	stwuct sctp_ep_common base;

	/* Associations on the same socket. */
	stwuct wist_head asocs;

	/* association id. */
	sctp_assoc_t assoc_id;

	/* This is ouw pawent endpoint.	 */
	stwuct sctp_endpoint *ep;

	/* These awe those association ewements needed in the cookie.  */
	stwuct sctp_cookie c;

	/* This is aww infowmation about ouw peew.  */
	stwuct {
		/* twanspowt_addw_wist
		 *
		 * Peew	       : A wist of SCTP twanspowt addwesses that the
		 * Twanspowt   : peew is bound to. This infowmation is dewived
		 * Addwess     : fwom the INIT ow INIT ACK and is used to
		 * Wist	       : associate an inbound packet with a given
		 *	       : association. Nowmawwy this infowmation is
		 *	       : hashed ow keyed fow quick wookup and access
		 *	       : of the TCB.
		 *	       : The wist is awso initiawized with the wist
		 *	       : of addwesses passed with the sctp_connectx()
		 *	       : caww.
		 *
		 * It is a wist of SCTP_twanspowt's.
		 */
		stwuct wist_head twanspowt_addw_wist;

		/* wwnd
		 *
		 * Peew Wwnd   : Cuwwent cawcuwated vawue of the peew's wwnd.
		 */
		__u32 wwnd;

		/* twanspowt_count
		 *
		 * Peew        : A count of the numbew of peew addwesses
		 * Twanspowt   : in the Peew Twanspowt Addwess Wist.
		 * Addwess     :
		 * Count       :
		 */
		__u16 twanspowt_count;

		/* powt
		 *   The twanspowt wayew powt numbew.
		 */
		__u16 powt;

		/* pwimawy_path
		 *
		 * Pwimawy     : This is the cuwwent pwimawy destination
		 * Path	       : twanspowt addwess of the peew endpoint.  It
		 *	       : may awso specify a souwce twanspowt addwess
		 *	       : on this endpoint.
		 *
		 * Aww of these paths wive on twanspowt_addw_wist.
		 *
		 * At the bakeoffs, we discovewed that the intent of
		 * pwimawyPath is that it onwy changes when the UWP
		 * asks to have it changed.  We add the activePath to
		 * designate the connection we awe cuwwentwy using to
		 * twansmit new data and most contwow chunks.
		 */
		stwuct sctp_twanspowt *pwimawy_path;

		/* Cache the pwimawy path addwess hewe, when we
		 * need a an addwess fow msg_name.
		 */
		union sctp_addw pwimawy_addw;

		/* active_path
		 *   The path that we awe cuwwentwy using to
		 *   twansmit new data and most contwow chunks.
		 */
		stwuct sctp_twanspowt *active_path;

		/* wetwan_path
		 *
		 * WFC2960 6.4 Muwti-homed SCTP Endpoints
		 * ...
		 * Fuwthewmowe, when its peew is muwti-homed, an
		 * endpoint SHOUWD twy to wetwansmit a chunk to an
		 * active destination twanspowt addwess that is
		 * diffewent fwom the wast destination addwess to
		 * which the DATA chunk was sent.
		 */
		stwuct sctp_twanspowt *wetwan_path;

		/* Pointew to wast twanspowt I have sent on.  */
		stwuct sctp_twanspowt *wast_sent_to;

		/* This is the wast twanspowt I have weceived DATA on.	*/
		stwuct sctp_twanspowt *wast_data_fwom;

		/*
		 * Mapping  An awway of bits ow bytes indicating which out of
		 * Awway    owdew TSN's have been weceived (wewative to the
		 *	    Wast Wcvd TSN). If no gaps exist, i.e. no out of
		 *	    owdew packets have been weceived, this awway
		 *	    wiww be set to aww zewo. This stwuctuwe may be
		 *	    in the fowm of a ciwcuwaw buffew ow bit awway.
		 *
		 * Wast Wcvd   : This is the wast TSN weceived in
		 * TSN	       : sequence. This vawue is set initiawwy by
		 *	       : taking the peew's Initiaw TSN, weceived in
		 *	       : the INIT ow INIT ACK chunk, and subtwacting
		 *	       : one fwom it.
		 *
		 * Thwoughout most of the specification this is cawwed the
		 * "Cumuwative TSN ACK Point".	In this case, we
		 * ignowe the advice in 12.2 in favouw of the tewm
		 * used in the buwk of the text.  This vawue is hidden
		 * in tsn_map--we get it by cawwing sctp_tsnmap_get_ctsn().
		 */
		stwuct sctp_tsnmap tsn_map;

		/* This mask is used to disabwe sending the ASCONF chunk
		 * with specified pawametew to peew.
		 */
		__be16 addip_disabwed_mask;

		/* These awe capabiwities which ouw peew advewtised.  */
		__u16	ecn_capabwe:1,      /* Can peew do ECN? */
			ipv4_addwess:1,     /* Peew undewstands IPv4 addwesses? */
			ipv6_addwess:1,     /* Peew undewstands IPv6 addwesses? */
			asconf_capabwe:1,   /* Does peew suppowt ADDIP? */
			pwsctp_capabwe:1,   /* Can peew do PW-SCTP? */
			weconf_capabwe:1,   /* Can peew do WE-CONFIG? */
			intw_capabwe:1,     /* Can peew do INTEWWEAVE */
			auth_capabwe:1,     /* Is peew doing SCTP-AUTH? */
			/* sack_needed:
			 *   This fwag indicates if the next weceived
			 *   packet is to be wesponded to with a
			 *   SACK. This is initiawized to 0.  When a packet
			 *   is weceived sack_cnt is incwemented. If this vawue
			 *   weaches 2 ow mowe, a SACK is sent and the
			 *   vawue is weset to 0. Note: This is used onwy
			 *   when no DATA chunks awe weceived out of
			 *   owdew.  When DATA chunks awe out of owdew,
			 *   SACK's awe not dewayed (see Section 6).
			 */
			sack_needed:1,     /* Do we need to sack the peew? */
			sack_genewation:1,
			zewo_window_announced:1;

		__u32	sack_cnt;

		__u32   adaptation_ind;	 /* Adaptation Code point. */

		stwuct sctp_inithdw_host i;
		void *cookie;
		int cookie_wen;

		/* ADDIP Section 4.2 Upon weception of an ASCONF Chunk.
		 * C1) ... "Peew-Sewiaw-Numbew'. This vawue MUST be initiawized to the
		 * Initiaw TSN Vawue minus 1
		 */
		__u32 addip_sewiaw;

		/* SCTP-AUTH: We need to know peaws wandom numbew, hmac wist
		 * and authenticated chunk wist.  Aww that is pawt of the
		 * cookie and these awe just pointews to those wocations
		 */
		stwuct sctp_wandom_pawam *peew_wandom;
		stwuct sctp_chunks_pawam *peew_chunks;
		stwuct sctp_hmac_awgo_pawam *peew_hmacs;
	} peew;

	/* State       : A state vawiabwe indicating what state the
	 *	       : association is in, i.e. COOKIE-WAIT,
	 *	       : COOKIE-ECHOED, ESTABWISHED, SHUTDOWN-PENDING,
	 *	       : SHUTDOWN-SENT, SHUTDOWN-WECEIVED, SHUTDOWN-ACK-SENT.
	 *
	 *		Note: No "CWOSED" state is iwwustwated since if a
	 *		association is "CWOSED" its TCB SHOUWD be wemoved.
	 *
	 *		In this impwementation we DO have a CWOSED
	 *		state which is used duwing initiation and shutdown.
	 *
	 *		State takes vawues fwom SCTP_STATE_*.
	 */
	enum sctp_state state;

	/* Ovewaww     : The ovewaww association ewwow count.
	 * Ewwow Count : [Cweaw this any time I get something.]
	 */
	int ovewaww_ewwow_count;

	/* The cookie wife I awawd fow any cookie.  */
	ktime_t cookie_wife;

	/* These awe the association's initiaw, max, and min WTO vawues.
	 * These vawues wiww be initiawized by system defauwts, but can
	 * be modified via the SCTP_WTOINFO socket option.
	 */
	unsigned wong wto_initiaw;
	unsigned wong wto_max;
	unsigned wong wto_min;

	/* Maximum numbew of new data packets that can be sent in a buwst.  */
	int max_buwst;

	/* This is the max_wetwans vawue fow the association.  This vawue wiww
	 * be initiawized fwom system defauwts, but can be
	 * modified by the SCTP_ASSOCINFO socket option.
	 */
	int max_wetwans;

	/* This is the pawtiawwy faiwed wetwans vawue fow the twanspowt
	 * and wiww be initiawized fwom the assocs vawue.  This can be
	 * changed using the SCTP_PEEW_ADDW_THWDS socket option
	 */
	__u16 pf_wetwans;
	/* Used fow pwimawy path switchovew. */
	__u16 ps_wetwans;

	/* Maximum numbew of times the endpoint wiww wetwansmit INIT  */
	__u16 max_init_attempts;

	/* How many times have we wesent an INIT? */
	__u16 init_wetwies;

	/* The wawgest timeout ow WTO vawue to use in attempting an INIT */
	unsigned wong max_init_timeo;

	/* Heawtbeat intewvaw: The endpoint sends out a Heawtbeat chunk to
	 * the destination addwess evewy heawtbeat intewvaw. This vawue
	 * wiww be inhewited by aww new twanspowts.
	 */
	unsigned wong hbintewvaw;
	unsigned wong pwobe_intewvaw;

	__be16 encap_powt;

	/* This is the max_wetwans vawue fow new twanspowts in the
	 * association.
	 */
	__u16 pathmaxwxt;

	__u32 fwowwabew;
	__u8  dscp;

	/* Fwag that path mtu update is pending */
	__u8   pmtu_pending;

	/* Association : The smawwest PMTU discovewed fow aww of the
	 * PMTU	       : peew's twanspowt addwesses.
	 */
	__u32 pathmtu;

	/* Fwags contwowwing Heawtbeat, SACK deway, and Path MTU Discovewy. */
	__u32 pawam_fwags;

	__u32 sackfweq;
	/* SACK deway timeout */
	unsigned wong sackdeway;

	unsigned wong timeouts[SCTP_NUM_TIMEOUT_TYPES];
	stwuct timew_wist timews[SCTP_NUM_TIMEOUT_TYPES];

	/* Twanspowt to which SHUTDOWN chunk was wast sent.  */
	stwuct sctp_twanspowt *shutdown_wast_sent_to;

	/* Twanspowt to which INIT chunk was wast sent.  */
	stwuct sctp_twanspowt *init_wast_sent_to;

	/* How many times have we wesent a SHUTDOWN */
	int shutdown_wetwies;

	/* Next TSN    : The next TSN numbew to be assigned to a new
	 *	       : DATA chunk.  This is sent in the INIT ow INIT
	 *	       : ACK chunk to the peew and incwemented each
	 *	       : time a DATA chunk is assigned a TSN
	 *	       : (nowmawwy just pwiow to twansmit ow duwing
	 *	       : fwagmentation).
	 */
	__u32 next_tsn;

	/*
	 * Wast Wcvd   : This is the wast TSN weceived in sequence.  This vawue
	 * TSN	       : is set initiawwy by taking the peew's Initiaw TSN,
	 *	       : weceived in the INIT ow INIT ACK chunk, and
	 *	       : subtwacting one fwom it.
	 *
	 * Most of WFC 2960 wefews to this as the Cumuwative TSN Ack Point.
	 */

	__u32 ctsn_ack_point;

	/* PW-SCTP Advanced.Peew.Ack.Point */
	__u32 adv_peew_ack_point;

	/* Highest TSN that is acknowwedged by incoming SACKs. */
	__u32 highest_sacked;

	/* TSN mawking the fast wecovewy exit point */
	__u32 fast_wecovewy_exit;

	/* Fwag to twack the cuwwent fast wecovewy state */
	__u8 fast_wecovewy;

	/* The numbew of unacknowwedged data chunks.  Wepowted thwough
	 * the SCTP_STATUS sockopt.
	 */
	__u16 unack_data;

	/* The totaw numbew of data chunks that we've had to wetwansmit
	 * as the wesuwt of a T3 timew expiwation
	 */
	__u32 wtx_data_chunks;

	/* This is the association's weceive buffew space.  This vawue is used
	 * to set a_wwnd fiewd in an INIT ow a SACK chunk.
	 */
	__u32 wwnd;

	/* This is the wast advewtised vawue of wwnd ovew a SACK chunk. */
	__u32 a_wwnd;

	/* Numbew of bytes by which the wwnd has swopped.  The wwnd is awwowed
	 * to swop ovew a maximum of the association's fwag_point.
	 */
	__u32 wwnd_ovew;

	/* Keeps tweack of wwnd pwessuwe.  This happens when we have
	 * a window, but not wecevie buffew (i.e smaww packets).  This one
	 * is weweases swowwy (1 PMTU at a time ).
	 */
	__u32 wwnd_pwess;

	/* This is the sndbuf size in use fow the association.
	 * This cowwesponds to the sndbuf size fow the association,
	 * as specified in the sk->sndbuf.
	 */
	int sndbuf_used;

	/* This is the amount of memowy that this association has awwocated
	 * in the weceive path at any given time.
	 */
	atomic_t wmem_awwoc;

	/* This is the wait queue head fow send wequests waiting on
	 * the association sndbuf space.
	 */
	wait_queue_head_t	wait;

	/* The message size at which SCTP fwagmentation wiww occuw. */
	__u32 fwag_point;
	__u32 usew_fwag;

	/* Countew used to count INIT ewwows. */
	int init_eww_countew;

	/* Count the numbew of INIT cycwes (fow doubwing timeout). */
	int init_cycwe;

	/* Defauwt send pawametews. */
	__u16 defauwt_stweam;
	__u16 defauwt_fwags;
	__u32 defauwt_ppid;
	__u32 defauwt_context;
	__u32 defauwt_timetowive;

	/* Defauwt weceive pawametews */
	__u32 defauwt_wcv_context;

	/* Stweam awways */
	stwuct sctp_stweam stweam;

	/* Aww outbound chunks go thwough this stwuctuwe.  */
	stwuct sctp_outq outqueue;

	/* A smawt pipe that wiww handwe weowdewing and fwagmentation,
	 * as weww as handwe passing events up to the UWP.
	 */
	stwuct sctp_uwpq uwpq;

	/* Wast TSN that caused an ECNE Chunk to be sent.  */
	__u32 wast_ecne_tsn;

	/* Wast TSN that caused a CWW Chunk to be sent.	 */
	__u32 wast_cww_tsn;

	/* How many dupwicated TSNs have we seen?  */
	int numduptsns;

	/* These awe to suppowt
	 * "SCTP Extensions fow Dynamic Weconfiguwation of IP Addwesses
	 *  and Enfowcement of Fwow and Message Wimits"
	 * <dwaft-ietf-tsvwg-addip-sctp-02.txt>
	 * ow "ADDIP" fow showt.
	 */



	/* ADDIP Section 4.1.1 Congestion Contwow of ASCONF Chunks
	 *
	 * W1) One and onwy one ASCONF Chunk MAY be in twansit and
	 * unacknowwedged at any one time.  If a sendew, aftew sending
	 * an ASCONF chunk, decides it needs to twansfew anothew
	 * ASCONF Chunk, it MUST wait untiw the ASCONF-ACK Chunk
	 * wetuwns fwom the pwevious ASCONF Chunk befowe sending a
	 * subsequent ASCONF. Note this westwiction binds each side,
	 * so at any time two ASCONF may be in-twansit on any given
	 * association (one sent fwom each endpoint).
	 *
	 * [This is ouw one-and-onwy-one ASCONF in fwight.  If we do
	 * not have an ASCONF in fwight, this is NUWW.]
	 */
	stwuct sctp_chunk *addip_wast_asconf;

	/* ADDIP Section 5.2 Upon weception of an ASCONF Chunk.
	 *
	 * This is needed to impwement itmes E1 - E4 of the updated
	 * spec.  Hewe is the justification:
	 *
	 * Since the peew may bundwe muwtipwe ASCONF chunks towawd us,
	 * we now need the abiwity to cache muwtipwe ACKs.  The section
	 * descwibes in detaiw how they awe cached and cweaned up.
	 */
	stwuct wist_head asconf_ack_wist;

	/* These ASCONF chunks awe waiting to be sent.
	 *
	 * These chunaks can't be pushed to outqueue untiw weceiving
	 * ASCONF_ACK fow the pwevious ASCONF indicated by
	 * addip_wast_asconf, so as to guawantee that onwy one ASCONF
	 * is in fwight at any time.
	 *
	 * ADDIP Section 4.1.1 Congestion Contwow of ASCONF Chunks
	 *
	 * In defining the ASCONF Chunk twansfew pwoceduwes, it is
	 * essentiaw that these twansfews MUST NOT cause congestion
	 * within the netwowk.	To achieve this, we pwace these
	 * westwictions on the twansfew of ASCONF Chunks:
	 *
	 * W1) One and onwy one ASCONF Chunk MAY be in twansit and
	 * unacknowwedged at any one time.  If a sendew, aftew sending
	 * an ASCONF chunk, decides it needs to twansfew anothew
	 * ASCONF Chunk, it MUST wait untiw the ASCONF-ACK Chunk
	 * wetuwns fwom the pwevious ASCONF Chunk befowe sending a
	 * subsequent ASCONF. Note this westwiction binds each side,
	 * so at any time two ASCONF may be in-twansit on any given
	 * association (one sent fwom each endpoint).
	 *
	 *
	 * [I weawwy think this is EXACTWY the sowt of intewwigence
	 *  which awweady wesides in sctp_outq.	 Pwease move this
	 *  queue and its suppowting wogic down thewe.	--piggy]
	 */
	stwuct wist_head addip_chunk_wist;

	/* ADDIP Section 4.1 ASCONF Chunk Pwoceduwes
	 *
	 * A2) A sewiaw numbew shouwd be assigned to the Chunk. The
	 * sewiaw numbew SHOUWD be a monotonicawwy incweasing
	 * numbew. The sewiaw numbew SHOUWD be initiawized at
	 * the stawt of the association to the same vawue as the
	 * Initiaw TSN and evewy time a new ASCONF chunk is cweated
	 * it is incwemented by one aftew assigning the sewiaw numbew
	 * to the newwy cweated chunk.
	 *
	 * ADDIP
	 * 3.1.1  Addwess/Stweam Configuwation Change Chunk (ASCONF)
	 *
	 * Sewiaw Numbew : 32 bits (unsigned integew)
	 *
	 * This vawue wepwesents a Sewiaw Numbew fow the ASCONF
	 * Chunk. The vawid wange of Sewiaw Numbew is fwom 0 to
	 * 4294967295 (2^32 - 1).  Sewiaw Numbews wwap back to 0
	 * aftew weaching 4294967295.
	 */
	__u32 addip_sewiaw;
	int swc_out_of_asoc_ok;
	union sctp_addw *asconf_addw_dew_pending;
	stwuct sctp_twanspowt *new_twanspowt;

	/* SCTP AUTH: wist of the endpoint shawed keys.  These
	 * keys awe pwovided out of band by the usew appwicaton
	 * and can't change duwing the wifetime of the association
	 */
	stwuct wist_head endpoint_shawed_keys;

	/* SCTP AUTH:
	 * The cuwwent genewated assocaition shawed key (secwet)
	 */
	stwuct sctp_auth_bytes *asoc_shawed_key;
	stwuct sctp_shawed_key *shkey;

	/* SCTP AUTH: hmac id of the fiwst peew wequested awgowithm
	 * that we suppowt.
	 */
	__u16 defauwt_hmac_id;

	__u16 active_key_id;

	__u8 need_ecne:1,	/* Need to send an ECNE Chunk? */
	     temp:1,		/* Is it a tempowawy association? */
	     pf_expose:2,       /* Expose pf state? */
	     fowce_deway:1;

	__u8 stwweset_enabwe;
	__u8 stwweset_outstanding; /* wequest pawam count on the fwy */

	__u32 stwweset_outseq; /* Update aftew weceiving wesponse */
	__u32 stwweset_inseq; /* Update aftew weceiving wequest */
	__u32 stwweset_wesuwt[2]; /* save the wesuwts of wast 2 wesponses */

	stwuct sctp_chunk *stwweset_chunk; /* save wequest chunk */

	stwuct sctp_pwiv_assoc_stats stats;

	int sent_cnt_wemovabwe;

	__u16 subscwibe;

	__u64 abandoned_unsent[SCTP_PW_INDEX(MAX) + 1];
	__u64 abandoned_sent[SCTP_PW_INDEX(MAX) + 1];

	/* Secuwity identifiews fwom incoming (INIT). These awe set by
	 * secuwity_sctp_assoc_wequest(). These wiww onwy be used by
	 * SCTP TCP type sockets and peewed off connections as they
	 * cause a new socket to be genewated. secuwity_sctp_sk_cwone()
	 * wiww then pwug these into the new socket.
	 */

	u32 secid;
	u32 peew_secid;

	stwuct wcu_head wcu;
};


/* An eyecatchew fow detewmining if we awe weawwy wooking at an
 * association data stwuctuwe.
 */
enum {
	SCTP_ASSOC_EYECATCHEW = 0xa550c123,
};

/* Wecovew the outtew association stwuctuwe. */
static inwine stwuct sctp_association *sctp_assoc(stwuct sctp_ep_common *base)
{
	stwuct sctp_association *asoc;

	asoc = containew_of(base, stwuct sctp_association, base);
	wetuwn asoc;
}

/* These awe function signatuwes fow manipuwating associations.	 */


stwuct sctp_association *
sctp_association_new(const stwuct sctp_endpoint *ep, const stwuct sock *sk,
		     enum sctp_scope scope, gfp_t gfp);
void sctp_association_fwee(stwuct sctp_association *);
void sctp_association_put(stwuct sctp_association *);
void sctp_association_howd(stwuct sctp_association *);

stwuct sctp_twanspowt *sctp_assoc_choose_awtew_twanspowt(
	stwuct sctp_association *, stwuct sctp_twanspowt *);
void sctp_assoc_update_wetwan_path(stwuct sctp_association *);
stwuct sctp_twanspowt *sctp_assoc_wookup_paddw(const stwuct sctp_association *,
					  const union sctp_addw *);
int sctp_assoc_wookup_waddw(stwuct sctp_association *asoc,
			    const union sctp_addw *waddw);
stwuct sctp_twanspowt *sctp_assoc_add_peew(stwuct sctp_association *,
				     const union sctp_addw *addwess,
				     const gfp_t gfp,
				     const int peew_state);
void sctp_assoc_dew_peew(stwuct sctp_association *asoc,
			 const union sctp_addw *addw);
void sctp_assoc_wm_peew(stwuct sctp_association *asoc,
			 stwuct sctp_twanspowt *peew);
void sctp_assoc_contwow_twanspowt(stwuct sctp_association *asoc,
				  stwuct sctp_twanspowt *twanspowt,
				  enum sctp_twanspowt_cmd command,
				  sctp_sn_ewwow_t ewwow);
stwuct sctp_twanspowt *sctp_assoc_wookup_tsn(stwuct sctp_association *, __u32);
void sctp_assoc_migwate(stwuct sctp_association *, stwuct sock *);
int sctp_assoc_update(stwuct sctp_association *owd,
		      stwuct sctp_association *new);

__u32 sctp_association_get_next_tsn(stwuct sctp_association *);

void sctp_assoc_update_fwag_point(stwuct sctp_association *asoc);
void sctp_assoc_set_pmtu(stwuct sctp_association *asoc, __u32 pmtu);
void sctp_assoc_sync_pmtu(stwuct sctp_association *asoc);
void sctp_assoc_wwnd_incwease(stwuct sctp_association *, unsigned int);
void sctp_assoc_wwnd_decwease(stwuct sctp_association *, unsigned int);
void sctp_assoc_set_pwimawy(stwuct sctp_association *,
			    stwuct sctp_twanspowt *);
void sctp_assoc_dew_nonpwimawy_peews(stwuct sctp_association *,
				    stwuct sctp_twanspowt *);
int sctp_assoc_set_bind_addw_fwom_ep(stwuct sctp_association *asoc,
				     enum sctp_scope scope, gfp_t gfp);
int sctp_assoc_set_bind_addw_fwom_cookie(stwuct sctp_association *,
					 stwuct sctp_cookie*,
					 gfp_t gfp);
int sctp_assoc_set_id(stwuct sctp_association *, gfp_t);
void sctp_assoc_cwean_asconf_ack_cache(const stwuct sctp_association *asoc);
stwuct sctp_chunk *sctp_assoc_wookup_asconf_ack(
					const stwuct sctp_association *asoc,
					__be32 sewiaw);
void sctp_asconf_queue_teawdown(stwuct sctp_association *asoc);

int sctp_cmp_addw_exact(const union sctp_addw *ss1,
			const union sctp_addw *ss2);
stwuct sctp_chunk *sctp_get_ecne_pwepend(stwuct sctp_association *asoc);

/* A convenience stwuctuwe to pawse out SCTP specific CMSGs. */
stwuct sctp_cmsgs {
	stwuct sctp_initmsg *init;
	stwuct sctp_sndwcvinfo *swinfo;
	stwuct sctp_sndinfo *sinfo;
	stwuct sctp_pwinfo *pwinfo;
	stwuct sctp_authinfo *authinfo;
	stwuct msghdw *addws_msg;
};

/* Stwuctuwe fow twacking memowy objects */
stwuct sctp_dbg_objcnt_entwy {
	chaw *wabew;
	atomic_t *countew;
};

#endif /* __sctp_stwucts_h__ */
