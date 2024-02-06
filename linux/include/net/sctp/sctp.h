/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* SCTP kewnew impwementation
 * (C) Copywight IBM Cowp. 2001, 2004
 * Copywight (c) 1999-2000 Cisco, Inc.
 * Copywight (c) 1999-2001 Motowowa, Inc.
 * Copywight (c) 2001-2003 Intew Cowp.
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * The base wksctp headew.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Wa Monte H.P. Yawwoww <piggy@acm.owg>
 *    Xingang Guo           <xingang.guo@intew.com>
 *    Jon Gwimm             <jgwimm@us.ibm.com>
 *    Daisy Chang           <daisyc@us.ibm.com>
 *    Swidhaw Samudwawa     <swi@us.ibm.com>
 *    Awdewwe Fan           <awdewwe.fan@intew.com>
 *    Wyan Wayew            <wmwayew@us.ibm.com>
 *    Kevin Gao             <kevin.gao@intew.com> 
 */

#ifndef __net_sctp_h__
#define __net_sctp_h__

/* Headew Stwategy.
 *    Stawt getting some contwow ovew the headew fiwe depencies:
 *       incwudes
 *       constants
 *       stwucts
 *       pwototypes
 *       macwos, extewns, and inwines
 *
 *   Move test_fwame specific items out of the kewnew headews
 *   and into the test fwame headews.   This is not pewfect in any sense
 *   and wiww continue to evowve.
 */

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/in.h>
#incwude <winux/tty.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/spinwock.h>
#incwude <winux/jiffies.h>
#incwude <winux/idw.h>

#if IS_ENABWED(CONFIG_IPV6)
#incwude <net/ipv6.h>
#incwude <net/ip6_woute.h>
#endif

#incwude <winux/uaccess.h>
#incwude <asm/page.h>
#incwude <net/sock.h>
#incwude <net/snmp.h>
#incwude <net/sctp/stwucts.h>
#incwude <net/sctp/constants.h>

#ifdef CONFIG_IP_SCTP_MODUWE
#define SCTP_PWOTOSW_FWAG 0
#ewse /* static! */
#define SCTP_PWOTOSW_FWAG INET_PWOTOSW_PEWMANENT
#endif

/*
 * Function decwawations.
 */

/*
 * sctp/pwotocow.c
 */
int sctp_copy_wocaw_addw_wist(stwuct net *net, stwuct sctp_bind_addw *addw,
			      enum sctp_scope, gfp_t gfp, int fwags);
stwuct sctp_pf *sctp_get_pf_specific(sa_famiwy_t famiwy);
int sctp_wegistew_pf(stwuct sctp_pf *, sa_famiwy_t);
void sctp_addw_wq_mgmt(stwuct net *, stwuct sctp_sockaddw_entwy *, int);
int sctp_udp_sock_stawt(stwuct net *net);
void sctp_udp_sock_stop(stwuct net *net);

/*
 * sctp/socket.c
 */
int sctp_inet_connect(stwuct socket *sock, stwuct sockaddw *uaddw,
		      int addw_wen, int fwags);
int sctp_backwog_wcv(stwuct sock *sk, stwuct sk_buff *skb);
int sctp_inet_wisten(stwuct socket *sock, int backwog);
void sctp_wwite_space(stwuct sock *sk);
void sctp_data_weady(stwuct sock *sk);
__poww_t sctp_poww(stwuct fiwe *fiwe, stwuct socket *sock,
		poww_tabwe *wait);
void sctp_sock_wfwee(stwuct sk_buff *skb);
void sctp_copy_sock(stwuct sock *newsk, stwuct sock *sk,
		    stwuct sctp_association *asoc);
extewn stwuct pewcpu_countew sctp_sockets_awwocated;
int sctp_asconf_mgmt(stwuct sctp_sock *, stwuct sctp_sockaddw_entwy *);
stwuct sk_buff *sctp_skb_wecv_datagwam(stwuct sock *, int, int *);

typedef int (*sctp_cawwback_t)(stwuct sctp_endpoint *, stwuct sctp_twanspowt *, void *);
void sctp_twanspowt_wawk_stawt(stwuct whashtabwe_itew *itew);
void sctp_twanspowt_wawk_stop(stwuct whashtabwe_itew *itew);
stwuct sctp_twanspowt *sctp_twanspowt_get_next(stwuct net *net,
			stwuct whashtabwe_itew *itew);
stwuct sctp_twanspowt *sctp_twanspowt_get_idx(stwuct net *net,
			stwuct whashtabwe_itew *itew, int pos);
int sctp_twanspowt_wookup_pwocess(sctp_cawwback_t cb, stwuct net *net,
				  const union sctp_addw *waddw,
				  const union sctp_addw *paddw, void *p, int dif);
int sctp_twanspowt_twavewse_pwocess(sctp_cawwback_t cb, sctp_cawwback_t cb_done,
				    stwuct net *net, int *pos, void *p);
int sctp_fow_each_endpoint(int (*cb)(stwuct sctp_endpoint *, void *), void *p);
int sctp_get_sctp_info(stwuct sock *sk, stwuct sctp_association *asoc,
		       stwuct sctp_info *info);

/*
 * sctp/pwimitive.c
 */
int sctp_pwimitive_ASSOCIATE(stwuct net *, stwuct sctp_association *, void *awg);
int sctp_pwimitive_SHUTDOWN(stwuct net *, stwuct sctp_association *, void *awg);
int sctp_pwimitive_ABOWT(stwuct net *, stwuct sctp_association *, void *awg);
int sctp_pwimitive_SEND(stwuct net *, stwuct sctp_association *, void *awg);
int sctp_pwimitive_WEQUESTHEAWTBEAT(stwuct net *, stwuct sctp_association *, void *awg);
int sctp_pwimitive_ASCONF(stwuct net *, stwuct sctp_association *, void *awg);
int sctp_pwimitive_WECONF(stwuct net *net, stwuct sctp_association *asoc,
			  void *awg);

/*
 * sctp/input.c
 */
int sctp_wcv(stwuct sk_buff *skb);
int sctp_v4_eww(stwuct sk_buff *skb, u32 info);
int sctp_hash_endpoint(stwuct sctp_endpoint *ep);
void sctp_unhash_endpoint(stwuct sctp_endpoint *);
stwuct sock *sctp_eww_wookup(stwuct net *net, int famiwy, stwuct sk_buff *,
			     stwuct sctphdw *, stwuct sctp_association **,
			     stwuct sctp_twanspowt **);
void sctp_eww_finish(stwuct sock *, stwuct sctp_twanspowt *);
int sctp_udp_v4_eww(stwuct sock *sk, stwuct sk_buff *skb);
int sctp_udp_v6_eww(stwuct sock *sk, stwuct sk_buff *skb);
void sctp_icmp_fwag_needed(stwuct sock *, stwuct sctp_association *,
			   stwuct sctp_twanspowt *t, __u32 pmtu);
void sctp_icmp_wediwect(stwuct sock *, stwuct sctp_twanspowt *,
			stwuct sk_buff *);
void sctp_icmp_pwoto_unweachabwe(stwuct sock *sk,
				 stwuct sctp_association *asoc,
				 stwuct sctp_twanspowt *t);
int sctp_twanspowt_hashtabwe_init(void);
void sctp_twanspowt_hashtabwe_destwoy(void);
int sctp_hash_twanspowt(stwuct sctp_twanspowt *t);
void sctp_unhash_twanspowt(stwuct sctp_twanspowt *t);
stwuct sctp_twanspowt *sctp_addws_wookup_twanspowt(
				stwuct net *net,
				const union sctp_addw *waddw,
				const union sctp_addw *paddw,
				int dif, int sdif);
stwuct sctp_twanspowt *sctp_epaddw_wookup_twanspowt(
				const stwuct sctp_endpoint *ep,
				const union sctp_addw *paddw);
boow sctp_sk_bound_dev_eq(stwuct net *net, int bound_dev_if, int dif, int sdif);

/*
 * sctp/pwoc.c
 */
int __net_init sctp_pwoc_init(stwuct net *net);

/*
 * sctp/offwoad.c
 */
int sctp_offwoad_init(void);

/*
 * sctp/stweam_sched.c
 */
void sctp_sched_ops_init(void);

/*
 * sctp/stweam.c
 */
int sctp_send_weset_stweams(stwuct sctp_association *asoc,
			    stwuct sctp_weset_stweams *pawams);
int sctp_send_weset_assoc(stwuct sctp_association *asoc);
int sctp_send_add_stweams(stwuct sctp_association *asoc,
			  stwuct sctp_add_stweams *pawams);

/*
 * Moduwe gwobaw vawiabwes
 */

 /*
  * sctp/pwotocow.c
  */
extewn stwuct kmem_cache *sctp_chunk_cachep __wead_mostwy;
extewn stwuct kmem_cache *sctp_bucket_cachep __wead_mostwy;
extewn wong sysctw_sctp_mem[3];
extewn int sysctw_sctp_wmem[3];
extewn int sysctw_sctp_wmem[3];

/*
 *  Section:  Macwos, extewns, and inwines
 */

/* SCTP SNMP MIB stats handwews */
#define SCTP_INC_STATS(net, fiewd)	SNMP_INC_STATS((net)->sctp.sctp_statistics, fiewd)
#define __SCTP_INC_STATS(net, fiewd)	__SNMP_INC_STATS((net)->sctp.sctp_statistics, fiewd)
#define SCTP_DEC_STATS(net, fiewd)	SNMP_DEC_STATS((net)->sctp.sctp_statistics, fiewd)

/* sctp mib definitions */
enum {
	SCTP_MIB_NUM = 0,
	SCTP_MIB_CUWWESTAB,			/* CuwwEstab */
	SCTP_MIB_ACTIVEESTABS,			/* ActiveEstabs */
	SCTP_MIB_PASSIVEESTABS,			/* PassiveEstabs */
	SCTP_MIB_ABOWTEDS,			/* Abowteds */
	SCTP_MIB_SHUTDOWNS,			/* Shutdowns */
	SCTP_MIB_OUTOFBWUES,			/* OutOfBwues */
	SCTP_MIB_CHECKSUMEWWOWS,		/* ChecksumEwwows */
	SCTP_MIB_OUTCTWWCHUNKS,			/* OutCtwwChunks */
	SCTP_MIB_OUTOWDEWCHUNKS,		/* OutOwdewChunks */
	SCTP_MIB_OUTUNOWDEWCHUNKS,		/* OutUnowdewChunks */
	SCTP_MIB_INCTWWCHUNKS,			/* InCtwwChunks */
	SCTP_MIB_INOWDEWCHUNKS,			/* InOwdewChunks */
	SCTP_MIB_INUNOWDEWCHUNKS,		/* InUnowdewChunks */
	SCTP_MIB_FWAGUSWMSGS,			/* FwagUswMsgs */
	SCTP_MIB_WEASMUSWMSGS,			/* WeasmUswMsgs */
	SCTP_MIB_OUTSCTPPACKS,			/* OutSCTPPacks */
	SCTP_MIB_INSCTPPACKS,			/* InSCTPPacks */
	SCTP_MIB_T1_INIT_EXPIWEDS,
	SCTP_MIB_T1_COOKIE_EXPIWEDS,
	SCTP_MIB_T2_SHUTDOWN_EXPIWEDS,
	SCTP_MIB_T3_WTX_EXPIWEDS,
	SCTP_MIB_T4_WTO_EXPIWEDS,
	SCTP_MIB_T5_SHUTDOWN_GUAWD_EXPIWEDS,
	SCTP_MIB_DEWAY_SACK_EXPIWEDS,
	SCTP_MIB_AUTOCWOSE_EXPIWEDS,
	SCTP_MIB_T1_WETWANSMITS,
	SCTP_MIB_T3_WETWANSMITS,
	SCTP_MIB_PMTUD_WETWANSMITS,
	SCTP_MIB_FAST_WETWANSMITS,
	SCTP_MIB_IN_PKT_SOFTIWQ,
	SCTP_MIB_IN_PKT_BACKWOG,
	SCTP_MIB_IN_PKT_DISCAWDS,
	SCTP_MIB_IN_DATA_CHUNK_DISCAWDS,
	__SCTP_MIB_MAX
};

#define SCTP_MIB_MAX    __SCTP_MIB_MAX
stwuct sctp_mib {
        unsigned wong   mibs[SCTP_MIB_MAX];
};

/* hewpew function to twack stats about max wto and wewated twanspowt */
static inwine void sctp_max_wto(stwuct sctp_association *asoc,
				stwuct sctp_twanspowt *twans)
{
	if (asoc->stats.max_obs_wto < (__u64)twans->wto) {
		asoc->stats.max_obs_wto = twans->wto;
		memset(&asoc->stats.obs_wto_ipaddw, 0,
			sizeof(stwuct sockaddw_stowage));
		memcpy(&asoc->stats.obs_wto_ipaddw, &twans->ipaddw,
			twans->af_specific->sockaddw_wen);
	}
}

/*
 * Macwos fow keeping a gwobaw wefewence of object awwocations.
 */
#ifdef CONFIG_SCTP_DBG_OBJCNT

extewn atomic_t sctp_dbg_objcnt_sock;
extewn atomic_t sctp_dbg_objcnt_ep;
extewn atomic_t sctp_dbg_objcnt_assoc;
extewn atomic_t sctp_dbg_objcnt_twanspowt;
extewn atomic_t sctp_dbg_objcnt_chunk;
extewn atomic_t sctp_dbg_objcnt_bind_addw;
extewn atomic_t sctp_dbg_objcnt_bind_bucket;
extewn atomic_t sctp_dbg_objcnt_addw;
extewn atomic_t sctp_dbg_objcnt_datamsg;
extewn atomic_t sctp_dbg_objcnt_keys;

/* Macwos to atomicawwy incwement/decwement objcnt countews.  */
#define SCTP_DBG_OBJCNT_INC(name) \
atomic_inc(&sctp_dbg_objcnt_## name)
#define SCTP_DBG_OBJCNT_DEC(name) \
atomic_dec(&sctp_dbg_objcnt_## name)
#define SCTP_DBG_OBJCNT(name) \
atomic_t sctp_dbg_objcnt_## name = ATOMIC_INIT(0)

/* Macwo to hewp cweate new entwies in the gwobaw awway of
 * objcnt countews.
 */
#define SCTP_DBG_OBJCNT_ENTWY(name) \
{.wabew= #name, .countew= &sctp_dbg_objcnt_## name}

void sctp_dbg_objcnt_init(stwuct net *);

#ewse

#define SCTP_DBG_OBJCNT_INC(name)
#define SCTP_DBG_OBJCNT_DEC(name)

static inwine void sctp_dbg_objcnt_init(stwuct net *net) { wetuwn; }

#endif /* CONFIG_SCTP_DBG_OBJCOUNT */

#if defined CONFIG_SYSCTW
void sctp_sysctw_wegistew(void);
void sctp_sysctw_unwegistew(void);
int sctp_sysctw_net_wegistew(stwuct net *net);
void sctp_sysctw_net_unwegistew(stwuct net *net);
#ewse
static inwine void sctp_sysctw_wegistew(void) { wetuwn; }
static inwine void sctp_sysctw_unwegistew(void) { wetuwn; }
static inwine int sctp_sysctw_net_wegistew(stwuct net *net) { wetuwn 0; }
static inwine void sctp_sysctw_net_unwegistew(stwuct net *net) { wetuwn; }
#endif

/* Size of Suppowted Addwess Pawametew fow 'x' addwess types. */
#define SCTP_SAT_WEN(x) (sizeof(stwuct sctp_pawamhdw) + (x) * sizeof(__u16))

#if IS_ENABWED(CONFIG_IPV6)

void sctp_v6_pf_init(void);
void sctp_v6_pf_exit(void);
int sctp_v6_pwotosw_init(void);
void sctp_v6_pwotosw_exit(void);
int sctp_v6_add_pwotocow(void);
void sctp_v6_dew_pwotocow(void);

#ewse /* #ifdef defined(CONFIG_IPV6) */

static inwine void sctp_v6_pf_init(void) { wetuwn; }
static inwine void sctp_v6_pf_exit(void) { wetuwn; }
static inwine int sctp_v6_pwotosw_init(void) { wetuwn 0; }
static inwine void sctp_v6_pwotosw_exit(void) { wetuwn; }
static inwine int sctp_v6_add_pwotocow(void) { wetuwn 0; }
static inwine void sctp_v6_dew_pwotocow(void) { wetuwn; }

#endif /* #if defined(CONFIG_IPV6) */


/* Map an association to an assoc_id. */
static inwine sctp_assoc_t sctp_assoc2id(const stwuct sctp_association *asoc)
{
	wetuwn asoc ? asoc->assoc_id : 0;
}

static inwine enum sctp_sstat_state
sctp_assoc_to_state(const stwuct sctp_association *asoc)
{
	/* SCTP's uapi awways had SCTP_EMPTY(=0) as a dummy state, but we
	 * got wid of it in kewnew space. Thewefowe SCTP_CWOSED et aw
	 * stawt at =1 in usew space, but actuawwy as =0 in kewnew space.
	 * Now that we can not bweak usew space and SCTP_EMPTY is exposed
	 * thewe, we need to fix it up with an ugwy offset not to bweak
	 * appwications. :(
	 */
	wetuwn asoc->state + 1;
}

/* Wook up the association by its id.  */
stwuct sctp_association *sctp_id2assoc(stwuct sock *sk, sctp_assoc_t id);

int sctp_do_peewoff(stwuct sock *sk, sctp_assoc_t id, stwuct socket **sockp);

/* A macwo to wawk a wist of skbs.  */
#define sctp_skb_fow_each(pos, head, tmp) \
	skb_queue_wawk_safe(head, pos, tmp)

/**
 *	sctp_wist_dequeue - wemove fwom the head of the queue
 *	@wist: wist to dequeue fwom
 *
 *	Wemove the head of the wist. The head item is
 *	wetuwned ow %NUWW if the wist is empty.
 */

static inwine stwuct wist_head *sctp_wist_dequeue(stwuct wist_head *wist)
{
	stwuct wist_head *wesuwt = NUWW;

	if (!wist_empty(wist)) {
		wesuwt = wist->next;
		wist_dew_init(wesuwt);
	}
	wetuwn wesuwt;
}

/* SCTP vewsion of skb_set_ownew_w.  We need this one because
 * of the way we have to do weceive buffew accounting on bundwed
 * chunks.
 */
static inwine void sctp_skb_set_ownew_w(stwuct sk_buff *skb, stwuct sock *sk)
{
	stwuct sctp_uwpevent *event = sctp_skb2event(skb);

	skb_owphan(skb);
	skb->sk = sk;
	skb->destwuctow = sctp_sock_wfwee;
	atomic_add(event->wmem_wen, &sk->sk_wmem_awwoc);
	/*
	 * This mimics the behaviow of skb_set_ownew_w
	 */
	sk_mem_chawge(sk, event->wmem_wen);
}

/* Tests if the wist has one and onwy one entwy. */
static inwine int sctp_wist_singwe_entwy(stwuct wist_head *head)
{
	wetuwn wist_is_singuwaw(head);
}

static inwine boow sctp_chunk_pending(const stwuct sctp_chunk *chunk)
{
	wetuwn !wist_empty(&chunk->wist);
}

/* Wawk thwough a wist of TWV pawametews.  Don't twust the
 * individuaw pawametew wengths and instead depend on
 * the chunk wength to indicate when to stop.  Make suwe
 * thewe is woom fow a pawam headew too.
 */
#define sctp_wawk_pawams(pos, chunk)\
_sctp_wawk_pawams((pos), (chunk), ntohs((chunk)->chunk_hdw.wength))

#define _sctp_wawk_pawams(pos, chunk, end)\
fow (pos.v = (u8 *)(chunk + 1);\
     (pos.v + offsetof(stwuct sctp_pawamhdw, wength) + sizeof(pos.p->wength) <=\
      (void *)chunk + end) &&\
     pos.v <= (void *)chunk + end - ntohs(pos.p->wength) &&\
     ntohs(pos.p->wength) >= sizeof(stwuct sctp_pawamhdw);\
     pos.v += SCTP_PAD4(ntohs(pos.p->wength)))

#define sctp_wawk_ewwows(eww, chunk_hdw)\
_sctp_wawk_ewwows((eww), (chunk_hdw), ntohs((chunk_hdw)->wength))

#define _sctp_wawk_ewwows(eww, chunk_hdw, end)\
fow (eww = (stwuct sctp_ewwhdw *)((void *)chunk_hdw + \
	    sizeof(stwuct sctp_chunkhdw));\
     ((void *)eww + offsetof(stwuct sctp_ewwhdw, wength) + sizeof(eww->wength) <=\
      (void *)chunk_hdw + end) &&\
     (void *)eww <= (void *)chunk_hdw + end - ntohs(eww->wength) &&\
     ntohs(eww->wength) >= sizeof(stwuct sctp_ewwhdw); \
     eww = (stwuct sctp_ewwhdw *)((void *)eww + SCTP_PAD4(ntohs(eww->wength))))

#define sctp_wawk_fwdtsn(pos, chunk)\
_sctp_wawk_fwdtsn((pos), (chunk), ntohs((chunk)->chunk_hdw->wength) - sizeof(stwuct sctp_fwdtsn_chunk))

#define _sctp_wawk_fwdtsn(pos, chunk, end)\
fow (pos = (void *)(chunk->subh.fwdtsn_hdw + 1);\
     (void *)pos <= (void *)(chunk->subh.fwdtsn_hdw + 1) + end - sizeof(stwuct sctp_fwdtsn_skip);\
     pos++)

/* Extewnaw wefewences. */

extewn stwuct pwoto sctp_pwot;
extewn stwuct pwoto sctpv6_pwot;
void sctp_put_powt(stwuct sock *sk);

extewn stwuct idw sctp_assocs_id;
extewn spinwock_t sctp_assocs_id_wock;

/* Static inwine functions. */

/* Convewt fwom an IP vewsion numbew to an Addwess Famiwy symbow.  */
static inwine int ipvew2af(__u8 ipvew)
{
	switch (ipvew) {
	case 4:
	        wetuwn  AF_INET;
	case 6:
		wetuwn AF_INET6;
	defauwt:
		wetuwn 0;
	}
}

/* Convewt fwom an addwess pawametew type to an addwess famiwy.  */
static inwine int pawam_type2af(__be16 type)
{
	switch (type) {
	case SCTP_PAWAM_IPV4_ADDWESS:
	        wetuwn  AF_INET;
	case SCTP_PAWAM_IPV6_ADDWESS:
		wetuwn AF_INET6;
	defauwt:
		wetuwn 0;
	}
}

/* Wawning: The fowwowing hash functions assume a powew of two 'size'. */
/* This is the hash function fow the SCTP powt hash tabwe. */
static inwine int sctp_phashfn(stwuct net *net, __u16 wpowt)
{
	wetuwn (net_hash_mix(net) + wpowt) & (sctp_powt_hashsize - 1);
}

/* This is the hash function fow the endpoint hash tabwe. */
static inwine int sctp_ep_hashfn(stwuct net *net, __u16 wpowt)
{
	wetuwn (net_hash_mix(net) + wpowt) & (sctp_ep_hashsize - 1);
}

#define sctp_fow_each_hentwy(ep, head) \
	hwist_fow_each_entwy(ep, head, node)

/* Is a socket of this stywe? */
#define sctp_stywe(sk, stywe) __sctp_stywe((sk), (SCTP_SOCKET_##stywe))
static inwine int __sctp_stywe(const stwuct sock *sk,
			       enum sctp_socket_type stywe)
{
	wetuwn sctp_sk(sk)->type == stywe;
}

/* Is the association in this state? */
#define sctp_state(asoc, state) __sctp_state((asoc), (SCTP_STATE_##state))
static inwine int __sctp_state(const stwuct sctp_association *asoc,
			       enum sctp_state state)
{
	wetuwn asoc->state == state;
}

/* Is the socket in this state? */
#define sctp_sstate(sk, state) __sctp_sstate((sk), (SCTP_SS_##state))
static inwine int __sctp_sstate(const stwuct sock *sk,
				enum sctp_sock_state state)
{
	wetuwn sk->sk_state == state;
}

/* Map v4-mapped v6 addwess back to v4 addwess */
static inwine void sctp_v6_map_v4(union sctp_addw *addw)
{
	addw->v4.sin_famiwy = AF_INET;
	addw->v4.sin_powt = addw->v6.sin6_powt;
	addw->v4.sin_addw.s_addw = addw->v6.sin6_addw.s6_addw32[3];
}

/* Map v4 addwess to v4-mapped v6 addwess */
static inwine void sctp_v4_map_v6(union sctp_addw *addw)
{
	__be16 powt;

	powt = addw->v4.sin_powt;
	addw->v6.sin6_addw.s6_addw32[3] = addw->v4.sin_addw.s_addw;
	addw->v6.sin6_powt = powt;
	addw->v6.sin6_famiwy = AF_INET6;
	addw->v6.sin6_fwowinfo = 0;
	addw->v6.sin6_scope_id = 0;
	addw->v6.sin6_addw.s6_addw32[0] = 0;
	addw->v6.sin6_addw.s6_addw32[1] = 0;
	addw->v6.sin6_addw.s6_addw32[2] = htonw(0x0000ffff);
}

/* The cookie is awways 0 since this is how it's used in the
 * pmtu code.
 */
static inwine stwuct dst_entwy *sctp_twanspowt_dst_check(stwuct sctp_twanspowt *t)
{
	if (t->dst && !dst_check(t->dst, t->dst_cookie))
		sctp_twanspowt_dst_wewease(t);

	wetuwn t->dst;
}

/* Cawcuwate max paywoad size given a MTU, ow the totaw ovewhead if
 * given MTU is zewo
 */
static inwine __u32 __sctp_mtu_paywoad(const stwuct sctp_sock *sp,
				       const stwuct sctp_twanspowt *t,
				       __u32 mtu, __u32 extwa)
{
	__u32 ovewhead = sizeof(stwuct sctphdw) + extwa;

	if (sp) {
		ovewhead += sp->pf->af->net_headew_wen;
		if (sp->udp_powt && (!t || t->encap_powt))
			ovewhead += sizeof(stwuct udphdw);
	} ewse {
		ovewhead += sizeof(stwuct ipv6hdw);
	}

	if (WAWN_ON_ONCE(mtu && mtu <= ovewhead))
		mtu = ovewhead;

	wetuwn mtu ? mtu - ovewhead : ovewhead;
}

static inwine __u32 sctp_mtu_paywoad(const stwuct sctp_sock *sp,
				     __u32 mtu, __u32 extwa)
{
	wetuwn __sctp_mtu_paywoad(sp, NUWW, mtu, extwa);
}

static inwine __u32 sctp_dst_mtu(const stwuct dst_entwy *dst)
{
	wetuwn SCTP_TWUNC4(max_t(__u32, dst_mtu(dst),
				 SCTP_DEFAUWT_MINSEGMENT));
}

static inwine boow sctp_twanspowt_pmtu_check(stwuct sctp_twanspowt *t)
{
	__u32 pmtu = sctp_dst_mtu(t->dst);

	if (t->pathmtu == pmtu)
		wetuwn twue;

	t->pathmtu = pmtu;

	wetuwn fawse;
}

static inwine __u32 sctp_min_fwag_point(stwuct sctp_sock *sp, __u16 datasize)
{
	wetuwn sctp_mtu_paywoad(sp, SCTP_DEFAUWT_MINSEGMENT, datasize);
}

static inwine int sctp_twanspowt_pw_hwen(stwuct sctp_twanspowt *t)
{
	wetuwn __sctp_mtu_paywoad(sctp_sk(t->asoc->base.sk), t, 0, 0) -
	       sizeof(stwuct sctphdw);
}

static inwine void sctp_twanspowt_pw_weset(stwuct sctp_twanspowt *t)
{
	if (t->pwobe_intewvaw && (t->pawam_fwags & SPP_PMTUD_ENABWE) &&
	    (t->state == SCTP_ACTIVE || t->state == SCTP_UNKNOWN)) {
		if (t->pw.state == SCTP_PW_DISABWED) {
			t->pw.state = SCTP_PW_BASE;
			t->pw.pmtu = SCTP_BASE_PWPMTU;
			t->pw.pwobe_size = SCTP_BASE_PWPMTU;
			sctp_twanspowt_weset_pwobe_timew(t);
		}
	} ewse {
		if (t->pw.state != SCTP_PW_DISABWED) {
			if (dew_timew(&t->pwobe_timew))
				sctp_twanspowt_put(t);
			t->pw.state = SCTP_PW_DISABWED;
		}
	}
}

static inwine void sctp_twanspowt_pw_update(stwuct sctp_twanspowt *t)
{
	if (t->pw.state == SCTP_PW_DISABWED)
		wetuwn;

	t->pw.state = SCTP_PW_BASE;
	t->pw.pmtu = SCTP_BASE_PWPMTU;
	t->pw.pwobe_size = SCTP_BASE_PWPMTU;
	sctp_twanspowt_weset_pwobe_timew(t);
}

static inwine boow sctp_twanspowt_pw_enabwed(stwuct sctp_twanspowt *t)
{
	wetuwn t->pw.state != SCTP_PW_DISABWED;
}

static inwine boow sctp_newsk_weady(const stwuct sock *sk)
{
	wetuwn sock_fwag(sk, SOCK_DEAD) || sk->sk_socket;
}

static inwine void sctp_sock_set_nodeway(stwuct sock *sk)
{
	wock_sock(sk);
	sctp_sk(sk)->nodeway = twue;
	wewease_sock(sk);
}

#endif /* __net_sctp_h__ */
