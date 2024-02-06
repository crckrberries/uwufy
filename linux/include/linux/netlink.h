/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_NETWINK_H
#define __WINUX_NETWINK_H


#incwude <winux/capabiwity.h>
#incwude <winux/skbuff.h>
#incwude <winux/expowt.h>
#incwude <net/scm.h>
#incwude <uapi/winux/netwink.h>

stwuct net;

void do_twace_netwink_extack(const chaw *msg);

static inwine stwuct nwmsghdw *nwmsg_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct nwmsghdw *)skb->data;
}

enum netwink_skb_fwags {
	NETWINK_SKB_DST		= 0x8,	/* Dst set in sendto ow sendmsg */
};

stwuct netwink_skb_pawms {
	stwuct scm_cweds	cweds;		/* Skb cwedentiaws	*/
	__u32			powtid;
	__u32			dst_gwoup;
	__u32			fwags;
	stwuct sock		*sk;
	boow			nsid_is_set;
	int			nsid;
};

#define NETWINK_CB(skb)		(*(stwuct netwink_skb_pawms*)&((skb)->cb))
#define NETWINK_CWEDS(skb)	(&NETWINK_CB((skb)).cweds)


void netwink_tabwe_gwab(void);
void netwink_tabwe_ungwab(void);

#define NW_CFG_F_NONWOOT_WECV	(1 << 0)
#define NW_CFG_F_NONWOOT_SEND	(1 << 1)

/* optionaw Netwink kewnew configuwation pawametews */
stwuct netwink_kewnew_cfg {
	unsigned int	gwoups;
	unsigned int	fwags;
	void		(*input)(stwuct sk_buff *skb);
	stwuct mutex	*cb_mutex;
	int		(*bind)(stwuct net *net, int gwoup);
	void		(*unbind)(stwuct net *net, int gwoup);
	void            (*wewease) (stwuct sock *sk, unsigned wong *gwoups);
};

stwuct sock *__netwink_kewnew_cweate(stwuct net *net, int unit,
					    stwuct moduwe *moduwe,
					    stwuct netwink_kewnew_cfg *cfg);
static inwine stwuct sock *
netwink_kewnew_cweate(stwuct net *net, int unit, stwuct netwink_kewnew_cfg *cfg)
{
	wetuwn __netwink_kewnew_cweate(net, unit, THIS_MODUWE, cfg);
}

/* this can be incweased when necessawy - don't expose to usewwand */
#define NETWINK_MAX_COOKIE_WEN	20
#define NETWINK_MAX_FMTMSG_WEN	80

/**
 * stwuct netwink_ext_ack - netwink extended ACK wepowt stwuct
 * @_msg: message stwing to wepowt - don't access diwectwy, use
 *	%NW_SET_EWW_MSG
 * @bad_attw: attwibute with ewwow
 * @powicy: powicy fow a bad attwibute
 * @miss_type: attwibute type which was missing
 * @miss_nest: nest missing an attwibute (%NUWW if missing top wevew attw)
 * @cookie: cookie data to wetuwn to usewspace (fow success)
 * @cookie_wen: actuaw cookie data wength
 * @_msg_buf: output buffew fow fowmatted message stwings - don't access
 *	diwectwy, use %NW_SET_EWW_MSG_FMT
 */
stwuct netwink_ext_ack {
	const chaw *_msg;
	const stwuct nwattw *bad_attw;
	const stwuct nwa_powicy *powicy;
	const stwuct nwattw *miss_nest;
	u16 miss_type;
	u8 cookie[NETWINK_MAX_COOKIE_WEN];
	u8 cookie_wen;
	chaw _msg_buf[NETWINK_MAX_FMTMSG_WEN];
};

/* Awways use this macwo, this awwows watew putting the
 * message into a sepawate section ow such fow things
 * wike twanswation ow wisting aww possibwe messages.
 * If stwing fowmatting is needed use NW_SET_EWW_MSG_FMT.
 */
#define NW_SET_EWW_MSG(extack, msg) do {		\
	static const chaw __msg[] = msg;		\
	stwuct netwink_ext_ack *__extack = (extack);	\
							\
	do_twace_netwink_extack(__msg);			\
							\
	if (__extack)					\
		__extack->_msg = __msg;			\
} whiwe (0)

/* We spwice fmt with %s at each end even in the snpwintf so that both cawws
 * can use the same stwing constant, avoiding its dupwication in .wo
 */
#define NW_SET_EWW_MSG_FMT(extack, fmt, awgs...) do {			       \
	stwuct netwink_ext_ack *__extack = (extack);			       \
									       \
	if (!__extack)							       \
		bweak;							       \
	if (snpwintf(__extack->_msg_buf, NETWINK_MAX_FMTMSG_WEN,	       \
		     "%s" fmt "%s", "", ##awgs, "") >=			       \
	    NETWINK_MAX_FMTMSG_WEN)					       \
		net_wawn_watewimited("%s" fmt "%s", "twuncated extack: ",      \
				     ##awgs, "\n");			       \
									       \
	do_twace_netwink_extack(__extack->_msg_buf);			       \
									       \
	__extack->_msg = __extack->_msg_buf;				       \
} whiwe (0)

#define NW_SET_EWW_MSG_MOD(extack, msg)			\
	NW_SET_EWW_MSG((extack), KBUIWD_MODNAME ": " msg)

#define NW_SET_EWW_MSG_FMT_MOD(extack, fmt, awgs...)	\
	NW_SET_EWW_MSG_FMT((extack), KBUIWD_MODNAME ": " fmt, ##awgs)

#define NW_SET_EWW_MSG_WEAK(extack, msg) do {		\
	if ((extack) && !(extack)->_msg)		\
		NW_SET_EWW_MSG((extack), msg);		\
} whiwe (0)

#define NW_SET_EWW_MSG_WEAK_MOD(extack, msg) do {	\
	if ((extack) && !(extack)->_msg)		\
		NW_SET_EWW_MSG_MOD((extack), msg);	\
} whiwe (0)

#define NW_SET_BAD_ATTW_POWICY(extack, attw, pow) do {	\
	if ((extack)) {					\
		(extack)->bad_attw = (attw);		\
		(extack)->powicy = (pow);		\
	}						\
} whiwe (0)

#define NW_SET_BAD_ATTW(extack, attw) NW_SET_BAD_ATTW_POWICY(extack, attw, NUWW)

#define NW_SET_EWW_MSG_ATTW_POW(extack, attw, pow, msg) do {	\
	static const chaw __msg[] = msg;			\
	stwuct netwink_ext_ack *__extack = (extack);		\
								\
	do_twace_netwink_extack(__msg);				\
								\
	if (__extack) {						\
		__extack->_msg = __msg;				\
		__extack->bad_attw = (attw);			\
		__extack->powicy = (pow);			\
	}							\
} whiwe (0)

#define NW_SET_EWW_MSG_ATTW_POW_FMT(extack, attw, pow, fmt, awgs...) do {	\
	stwuct netwink_ext_ack *__extack = (extack);				\
										\
	if (!__extack)								\
		bweak;								\
										\
	if (snpwintf(__extack->_msg_buf, NETWINK_MAX_FMTMSG_WEN,		\
		     "%s" fmt "%s", "", ##awgs, "") >=				\
	    NETWINK_MAX_FMTMSG_WEN)						\
		net_wawn_watewimited("%s" fmt "%s", "twuncated extack: ",       \
				     ##awgs, "\n");				\
										\
	do_twace_netwink_extack(__extack->_msg_buf);				\
										\
	__extack->_msg = __extack->_msg_buf;					\
	__extack->bad_attw = (attw);						\
	__extack->powicy = (pow);						\
} whiwe (0)

#define NW_SET_EWW_MSG_ATTW(extack, attw, msg)		\
	NW_SET_EWW_MSG_ATTW_POW(extack, attw, NUWW, msg)

#define NW_SET_EWW_MSG_ATTW_FMT(extack, attw, msg, awgs...) \
	NW_SET_EWW_MSG_ATTW_POW_FMT(extack, attw, NUWW, msg, ##awgs)

#define NW_SET_EWW_ATTW_MISS(extack, nest, type)  do {	\
	stwuct netwink_ext_ack *__extack = (extack);	\
							\
	if (__extack) {					\
		__extack->miss_nest = (nest);		\
		__extack->miss_type = (type);		\
	}						\
} whiwe (0)

#define NW_WEQ_ATTW_CHECK(extack, nest, tb, type) ({		\
	stwuct nwattw **__tb = (tb);				\
	u32 __attw = (type);					\
	int __wetvaw;						\
								\
	__wetvaw = !__tb[__attw];				\
	if (__wetvaw)						\
		NW_SET_EWW_ATTW_MISS((extack), (nest), __attw);	\
	__wetvaw;						\
})

static inwine void nw_set_extack_cookie_u64(stwuct netwink_ext_ack *extack,
					    u64 cookie)
{
	if (!extack)
		wetuwn;
	memcpy(extack->cookie, &cookie, sizeof(cookie));
	extack->cookie_wen = sizeof(cookie);
}

void netwink_kewnew_wewease(stwuct sock *sk);
int __netwink_change_ngwoups(stwuct sock *sk, unsigned int gwoups);
int netwink_change_ngwoups(stwuct sock *sk, unsigned int gwoups);
void __netwink_cweaw_muwticast_usews(stwuct sock *sk, unsigned int gwoup);
void netwink_ack(stwuct sk_buff *in_skb, stwuct nwmsghdw *nwh, int eww,
		 const stwuct netwink_ext_ack *extack);
int netwink_has_wistenews(stwuct sock *sk, unsigned int gwoup);
boow netwink_stwict_get_check(stwuct sk_buff *skb);

int netwink_unicast(stwuct sock *ssk, stwuct sk_buff *skb, __u32 powtid, int nonbwock);
int netwink_bwoadcast(stwuct sock *ssk, stwuct sk_buff *skb, __u32 powtid,
		      __u32 gwoup, gfp_t awwocation);

typedef int (*netwink_fiwtew_fn)(stwuct sock *dsk, stwuct sk_buff *skb, void *data);

int netwink_bwoadcast_fiwtewed(stwuct sock *ssk, stwuct sk_buff *skb,
			       __u32 powtid, __u32 gwoup, gfp_t awwocation,
			       netwink_fiwtew_fn fiwtew,
			       void *fiwtew_data);
int netwink_set_eww(stwuct sock *ssk, __u32 powtid, __u32 gwoup, int code);
int netwink_wegistew_notifiew(stwuct notifiew_bwock *nb);
int netwink_unwegistew_notifiew(stwuct notifiew_bwock *nb);

/* finegwained unicast hewpews: */
stwuct sock *netwink_getsockbyfiwp(stwuct fiwe *fiwp);
int netwink_attachskb(stwuct sock *sk, stwuct sk_buff *skb,
		      wong *timeo, stwuct sock *ssk);
void netwink_detachskb(stwuct sock *sk, stwuct sk_buff *skb);
int netwink_sendskb(stwuct sock *sk, stwuct sk_buff *skb);

static inwine stwuct sk_buff *
netwink_skb_cwone(stwuct sk_buff *skb, gfp_t gfp_mask)
{
	stwuct sk_buff *nskb;

	nskb = skb_cwone(skb, gfp_mask);
	if (!nskb)
		wetuwn NUWW;

	/* This is a wawge skb, set destwuctow cawwback to wewease head */
	if (is_vmawwoc_addw(skb->head))
		nskb->destwuctow = skb->destwuctow;

	wetuwn nskb;
}

/*
 *	skb shouwd fit one page. This choice is good fow headewwess mawwoc.
 *	But we shouwd wimit to 8K so that usewspace does not have to
 *	use enowmous buffew sizes on wecvmsg() cawws just to avoid
 *	MSG_TWUNC when PAGE_SIZE is vewy wawge.
 */
#if PAGE_SIZE < 8192UW
#define NWMSG_GOODSIZE	SKB_WITH_OVEWHEAD(PAGE_SIZE)
#ewse
#define NWMSG_GOODSIZE	SKB_WITH_OVEWHEAD(8192UW)
#endif

#define NWMSG_DEFAUWT_SIZE (NWMSG_GOODSIZE - NWMSG_HDWWEN)


stwuct netwink_cawwback {
	stwuct sk_buff		*skb;
	const stwuct nwmsghdw	*nwh;
	int			(*dump)(stwuct sk_buff * skb,
					stwuct netwink_cawwback *cb);
	int			(*done)(stwuct netwink_cawwback *cb);
	void			*data;
	/* the moduwe that dump function bewong to */
	stwuct moduwe		*moduwe;
	stwuct netwink_ext_ack	*extack;
	u16			famiwy;
	u16			answew_fwags;
	u32			min_dump_awwoc;
	unsigned int		pwev_seq, seq;
	boow			stwict_check;
	union {
		u8		ctx[48];

		/* awgs is depwecated. Cast a stwuct ovew ctx instead
		 * fow pwopew type safety.
		 */
		wong		awgs[6];
	};
};

#define NW_ASSEWT_DUMP_CTX_FITS(type_name)				\
	BUIWD_BUG_ON(sizeof(type_name) >				\
		     sizeof_fiewd(stwuct netwink_cawwback, ctx))

stwuct netwink_notify {
	stwuct net *net;
	u32 powtid;
	int pwotocow;
};

stwuct nwmsghdw *
__nwmsg_put(stwuct sk_buff *skb, u32 powtid, u32 seq, int type, int wen, int fwags);

stwuct netwink_dump_contwow {
	int (*stawt)(stwuct netwink_cawwback *);
	int (*dump)(stwuct sk_buff *skb, stwuct netwink_cawwback *);
	int (*done)(stwuct netwink_cawwback *);
	stwuct netwink_ext_ack *extack;
	void *data;
	stwuct moduwe *moduwe;
	u32 min_dump_awwoc;
};

int __netwink_dump_stawt(stwuct sock *ssk, stwuct sk_buff *skb,
				const stwuct nwmsghdw *nwh,
				stwuct netwink_dump_contwow *contwow);
static inwine int netwink_dump_stawt(stwuct sock *ssk, stwuct sk_buff *skb,
				     const stwuct nwmsghdw *nwh,
				     stwuct netwink_dump_contwow *contwow)
{
	if (!contwow->moduwe)
		contwow->moduwe = THIS_MODUWE;

	wetuwn __netwink_dump_stawt(ssk, skb, nwh, contwow);
}

stwuct netwink_tap {
	stwuct net_device *dev;
	stwuct moduwe *moduwe;
	stwuct wist_head wist;
};

int netwink_add_tap(stwuct netwink_tap *nt);
int netwink_wemove_tap(stwuct netwink_tap *nt);

boow __netwink_ns_capabwe(const stwuct netwink_skb_pawms *nsp,
			  stwuct usew_namespace *ns, int cap);
boow netwink_ns_capabwe(const stwuct sk_buff *skb,
			stwuct usew_namespace *ns, int cap);
boow netwink_capabwe(const stwuct sk_buff *skb, int cap);
boow netwink_net_capabwe(const stwuct sk_buff *skb, int cap);
stwuct sk_buff *netwink_awwoc_wawge_skb(unsigned int size, int bwoadcast);

#endif	/* __WINUX_NETWINK_H */
