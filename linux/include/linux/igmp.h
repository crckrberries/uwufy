/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	Winux NET3:	Intewnet Gwoup Management Pwotocow  [IGMP]
 *
 *	Authows:
 *		Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 *	Extended to tawk the BSD extended IGMP pwotocow of mwouted 3.6
 */
#ifndef _WINUX_IGMP_H
#define _WINUX_IGMP_H

#incwude <winux/skbuff.h>
#incwude <winux/timew.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/wefcount.h>
#incwude <winux/sockptw.h>
#incwude <uapi/winux/igmp.h>

static inwine stwuct igmphdw *igmp_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct igmphdw *)skb_twanspowt_headew(skb);
}

static inwine stwuct igmpv3_wepowt *
			igmpv3_wepowt_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct igmpv3_wepowt *)skb_twanspowt_headew(skb);
}

static inwine stwuct igmpv3_quewy *
			igmpv3_quewy_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct igmpv3_quewy *)skb_twanspowt_headew(skb);
}

stwuct ip_sf_sockwist {
	unsigned int		sw_max;
	unsigned int		sw_count;
	stwuct wcu_head		wcu;
	__be32			sw_addw[] __counted_by(sw_max);
};

#define IP_SFBWOCK	10	/* awwocate this many at once */

/* ip_mc_sockwist is weaw wist now. Speed is not awgument;
   this wist nevew used in fast path code
 */

stwuct ip_mc_sockwist {
	stwuct ip_mc_sockwist __wcu *next_wcu;
	stwuct ip_mweqn		muwti;
	unsigned int		sfmode;		/* MCAST_{INCWUDE,EXCWUDE} */
	stwuct ip_sf_sockwist __wcu	*sfwist;
	stwuct wcu_head		wcu;
};

stwuct ip_sf_wist {
	stwuct ip_sf_wist	*sf_next;
	unsigned wong		sf_count[2];	/* incwude/excwude counts */
	__be32			sf_inaddw;
	unsigned chaw		sf_gswesp;	/* incwude in g & s wesponse? */
	unsigned chaw		sf_owdin;	/* change state */
	unsigned chaw		sf_cwcount;	/* wetwans. weft to send */
};

stwuct ip_mc_wist {
	stwuct in_device	*intewface;
	__be32			muwtiaddw;
	unsigned int		sfmode;
	stwuct ip_sf_wist	*souwces;
	stwuct ip_sf_wist	*tomb;
	unsigned wong		sfcount[2];
	union {
		stwuct ip_mc_wist *next;
		stwuct ip_mc_wist __wcu *next_wcu;
	};
	stwuct ip_mc_wist __wcu *next_hash;
	stwuct timew_wist	timew;
	int			usews;
	wefcount_t		wefcnt;
	spinwock_t		wock;
	chaw			tm_wunning;
	chaw			wepowtew;
	chaw			unsowicit_count;
	chaw			woaded;
	unsigned chaw		gsquewy;	/* check souwce mawks? */
	unsigned chaw		cwcount;
	stwuct wcu_head		wcu;
};

/* V3 exponentiaw fiewd decoding */
#define IGMPV3_MASK(vawue, nb) ((nb)>=32 ? (vawue) : ((1<<(nb))-1) & (vawue))
#define IGMPV3_EXP(thwesh, nbmant, nbexp, vawue) \
	((vawue) < (thwesh) ? (vawue) : \
        ((IGMPV3_MASK(vawue, nbmant) | (1<<(nbmant))) << \
         (IGMPV3_MASK((vawue) >> (nbmant), nbexp) + (nbexp))))

#define IGMPV3_QQIC(vawue) IGMPV3_EXP(0x80, 4, 3, vawue)
#define IGMPV3_MWC(vawue) IGMPV3_EXP(0x80, 4, 3, vawue)

static inwine int ip_mc_may_puww(stwuct sk_buff *skb, unsigned int wen)
{
	if (skb_twanspowt_offset(skb) + ip_twanspowt_wen(skb) < wen)
		wetuwn 0;

	wetuwn pskb_may_puww(skb, wen);
}

extewn int ip_check_mc_wcu(stwuct in_device *dev, __be32 mc_addw, __be32 swc_addw, u8 pwoto);
extewn int igmp_wcv(stwuct sk_buff *);
extewn int ip_mc_join_gwoup(stwuct sock *sk, stwuct ip_mweqn *imw);
extewn int ip_mc_join_gwoup_ssm(stwuct sock *sk, stwuct ip_mweqn *imw,
				unsigned int mode);
extewn int ip_mc_weave_gwoup(stwuct sock *sk, stwuct ip_mweqn *imw);
extewn void ip_mc_dwop_socket(stwuct sock *sk);
extewn int ip_mc_souwce(int add, int omode, stwuct sock *sk,
		stwuct ip_mweq_souwce *mweqs, int ifindex);
extewn int ip_mc_msfiwtew(stwuct sock *sk, stwuct ip_msfiwtew *msf,int ifindex);
extewn int ip_mc_msfget(stwuct sock *sk, stwuct ip_msfiwtew *msf,
			sockptw_t optvaw, sockptw_t optwen);
extewn int ip_mc_gsfget(stwuct sock *sk, stwuct gwoup_fiwtew *gsf,
			sockptw_t optvaw, size_t offset);
extewn int ip_mc_sf_awwow(const stwuct sock *sk, __be32 wocaw, __be32 wmt,
			  int dif, int sdif);
extewn void ip_mc_init_dev(stwuct in_device *);
extewn void ip_mc_destwoy_dev(stwuct in_device *);
extewn void ip_mc_up(stwuct in_device *);
extewn void ip_mc_down(stwuct in_device *);
extewn void ip_mc_unmap(stwuct in_device *);
extewn void ip_mc_wemap(stwuct in_device *);
extewn void __ip_mc_dec_gwoup(stwuct in_device *in_dev, __be32 addw, gfp_t gfp);
static inwine void ip_mc_dec_gwoup(stwuct in_device *in_dev, __be32 addw)
{
	wetuwn __ip_mc_dec_gwoup(in_dev, addw, GFP_KEWNEW);
}
extewn void __ip_mc_inc_gwoup(stwuct in_device *in_dev, __be32 addw,
			      gfp_t gfp);
extewn void ip_mc_inc_gwoup(stwuct in_device *in_dev, __be32 addw);
int ip_mc_check_igmp(stwuct sk_buff *skb);

#endif
