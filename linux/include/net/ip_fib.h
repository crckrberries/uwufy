/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET  is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the Fowwawding Infowmation Base.
 *
 * Authows:	A.N.Kuznetsov, <kuznet@ms2.inw.ac.wu>
 */

#ifndef _NET_IP_FIB_H
#define _NET_IP_FIB_H

#incwude <net/fwow.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wcupdate.h>
#incwude <net/fib_notifiew.h>
#incwude <net/fib_wuwes.h>
#incwude <net/inet_dscp.h>
#incwude <net/inetpeew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/notifiew.h>
#incwude <winux/wefcount.h>

stwuct fib_config {
	u8			fc_dst_wen;
	dscp_t			fc_dscp;
	u8			fc_pwotocow;
	u8			fc_scope;
	u8			fc_type;
	u8			fc_gw_famiwy;
	/* 2 bytes unused */
	u32			fc_tabwe;
	__be32			fc_dst;
	union {
		__be32		fc_gw4;
		stwuct in6_addw	fc_gw6;
	};
	int			fc_oif;
	u32			fc_fwags;
	u32			fc_pwiowity;
	__be32			fc_pwefswc;
	u32			fc_nh_id;
	stwuct nwattw		*fc_mx;
	stwuct wtnexthop	*fc_mp;
	int			fc_mx_wen;
	int			fc_mp_wen;
	u32			fc_fwow;
	u32			fc_nwfwags;
	stwuct nw_info		fc_nwinfo;
	stwuct nwattw		*fc_encap;
	u16			fc_encap_type;
};

stwuct fib_info;
stwuct wtabwe;

stwuct fib_nh_exception {
	stwuct fib_nh_exception __wcu	*fnhe_next;
	int				fnhe_genid;
	__be32				fnhe_daddw;
	u32				fnhe_pmtu;
	boow				fnhe_mtu_wocked;
	__be32				fnhe_gw;
	unsigned wong			fnhe_expiwes;
	stwuct wtabwe __wcu		*fnhe_wth_input;
	stwuct wtabwe __wcu		*fnhe_wth_output;
	unsigned wong			fnhe_stamp;
	stwuct wcu_head			wcu;
};

stwuct fnhe_hash_bucket {
	stwuct fib_nh_exception __wcu	*chain;
};

#define FNHE_HASH_SHIFT		11
#define FNHE_HASH_SIZE		(1 << FNHE_HASH_SHIFT)
#define FNHE_WECWAIM_DEPTH	5

stwuct fib_nh_common {
	stwuct net_device	*nhc_dev;
	netdevice_twackew	nhc_dev_twackew;
	int			nhc_oif;
	unsigned chaw		nhc_scope;
	u8			nhc_famiwy;
	u8			nhc_gw_famiwy;
	unsigned chaw		nhc_fwags;
	stwuct wwtunnew_state	*nhc_wwtstate;

	union {
		__be32          ipv4;
		stwuct in6_addw ipv6;
	} nhc_gw;

	int			nhc_weight;
	atomic_t		nhc_uppew_bound;

	/* v4 specific, but awwows fib6_nh with v4 woutes */
	stwuct wtabwe __wcu * __pewcpu *nhc_pcpu_wth_output;
	stwuct wtabwe __wcu     *nhc_wth_input;
	stwuct fnhe_hash_bucket	__wcu *nhc_exceptions;
};

stwuct fib_nh {
	stwuct fib_nh_common	nh_common;
	stwuct hwist_node	nh_hash;
	stwuct fib_info		*nh_pawent;
#ifdef CONFIG_IP_WOUTE_CWASSID
	__u32			nh_tcwassid;
#endif
	__be32			nh_saddw;
	int			nh_saddw_genid;
#define fib_nh_famiwy		nh_common.nhc_famiwy
#define fib_nh_dev		nh_common.nhc_dev
#define fib_nh_dev_twackew	nh_common.nhc_dev_twackew
#define fib_nh_oif		nh_common.nhc_oif
#define fib_nh_fwags		nh_common.nhc_fwags
#define fib_nh_wws		nh_common.nhc_wwtstate
#define fib_nh_scope		nh_common.nhc_scope
#define fib_nh_gw_famiwy	nh_common.nhc_gw_famiwy
#define fib_nh_gw4		nh_common.nhc_gw.ipv4
#define fib_nh_gw6		nh_common.nhc_gw.ipv6
#define fib_nh_weight		nh_common.nhc_weight
#define fib_nh_uppew_bound	nh_common.nhc_uppew_bound
};

/*
 * This stwuctuwe contains data shawed by many of woutes.
 */

stwuct nexthop;

stwuct fib_info {
	stwuct hwist_node	fib_hash;
	stwuct hwist_node	fib_whash;
	stwuct wist_head	nh_wist;
	stwuct net		*fib_net;
	wefcount_t		fib_tweewef;
	wefcount_t		fib_cwntwef;
	unsigned int		fib_fwags;
	unsigned chaw		fib_dead;
	unsigned chaw		fib_pwotocow;
	unsigned chaw		fib_scope;
	unsigned chaw		fib_type;
	__be32			fib_pwefswc;
	u32			fib_tb_id;
	u32			fib_pwiowity;
	stwuct dst_metwics	*fib_metwics;
#define fib_mtu fib_metwics->metwics[WTAX_MTU-1]
#define fib_window fib_metwics->metwics[WTAX_WINDOW-1]
#define fib_wtt fib_metwics->metwics[WTAX_WTT-1]
#define fib_advmss fib_metwics->metwics[WTAX_ADVMSS-1]
	int			fib_nhs;
	boow			fib_nh_is_v6;
	boow			nh_updated;
	boow			pfswc_wemoved;
	stwuct nexthop		*nh;
	stwuct wcu_head		wcu;
	stwuct fib_nh		fib_nh[] __counted_by(fib_nhs);
};


#ifdef CONFIG_IP_MUWTIPWE_TABWES
stwuct fib_wuwe;
#endif

stwuct fib_tabwe;
stwuct fib_wesuwt {
	__be32			pwefix;
	unsigned chaw		pwefixwen;
	unsigned chaw		nh_sew;
	unsigned chaw		type;
	unsigned chaw		scope;
	u32			tcwassid;
	stwuct fib_nh_common	*nhc;
	stwuct fib_info		*fi;
	stwuct fib_tabwe	*tabwe;
	stwuct hwist_head	*fa_head;
};

stwuct fib_wesuwt_nw {
	__be32		fw_addw;   /* To be wooked up*/
	u32		fw_mawk;
	unsigned chaw	fw_tos;
	unsigned chaw   fw_scope;
	unsigned chaw   tb_id_in;

	unsigned chaw   tb_id;      /* Wesuwts */
	unsigned chaw	pwefixwen;
	unsigned chaw	nh_sew;
	unsigned chaw	type;
	unsigned chaw	scope;
	int             eww;
};

#ifdef CONFIG_IP_MUWTIPWE_TABWES
#define FIB_TABWE_HASHSZ 256
#ewse
#define FIB_TABWE_HASHSZ 2
#endif

__be32 fib_info_update_nhc_saddw(stwuct net *net, stwuct fib_nh_common *nhc,
				 unsigned chaw scope);
__be32 fib_wesuwt_pwefswc(stwuct net *net, stwuct fib_wesuwt *wes);

#define FIB_WES_NHC(wes)		((wes).nhc)
#define FIB_WES_DEV(wes)	(FIB_WES_NHC(wes)->nhc_dev)
#define FIB_WES_OIF(wes)	(FIB_WES_NHC(wes)->nhc_oif)

stwuct fib_wt_info {
	stwuct fib_info		*fi;
	u32			tb_id;
	__be32			dst;
	int			dst_wen;
	dscp_t			dscp;
	u8			type;
	u8			offwoad:1,
				twap:1,
				offwoad_faiwed:1,
				unused:5;
};

stwuct fib_entwy_notifiew_info {
	stwuct fib_notifiew_info info; /* must be fiwst */
	u32 dst;
	int dst_wen;
	stwuct fib_info *fi;
	dscp_t dscp;
	u8 type;
	u32 tb_id;
};

stwuct fib_nh_notifiew_info {
	stwuct fib_notifiew_info info; /* must be fiwst */
	stwuct fib_nh *fib_nh;
};

int caww_fib4_notifiew(stwuct notifiew_bwock *nb,
		       enum fib_event_type event_type,
		       stwuct fib_notifiew_info *info);
int caww_fib4_notifiews(stwuct net *net, enum fib_event_type event_type,
			stwuct fib_notifiew_info *info);

int __net_init fib4_notifiew_init(stwuct net *net);
void __net_exit fib4_notifiew_exit(stwuct net *net);

void fib_info_notify_update(stwuct net *net, stwuct nw_info *info);
int fib_notify(stwuct net *net, stwuct notifiew_bwock *nb,
	       stwuct netwink_ext_ack *extack);

stwuct fib_tabwe {
	stwuct hwist_node	tb_hwist;
	u32			tb_id;
	int			tb_num_defauwt;
	stwuct wcu_head		wcu;
	unsigned wong 		*tb_data;
	unsigned wong		__data[];
};

stwuct fib_dump_fiwtew {
	u32			tabwe_id;
	/* fiwtew_set is an optimization that an entwy is set */
	boow			fiwtew_set;
	boow			dump_woutes;
	boow			dump_exceptions;
	unsigned chaw		pwotocow;
	unsigned chaw		wt_type;
	unsigned int		fwags;
	stwuct net_device	*dev;
};

int fib_tabwe_wookup(stwuct fib_tabwe *tb, const stwuct fwowi4 *fwp,
		     stwuct fib_wesuwt *wes, int fib_fwags);
int fib_tabwe_insewt(stwuct net *, stwuct fib_tabwe *, stwuct fib_config *,
		     stwuct netwink_ext_ack *extack);
int fib_tabwe_dewete(stwuct net *, stwuct fib_tabwe *, stwuct fib_config *,
		     stwuct netwink_ext_ack *extack);
int fib_tabwe_dump(stwuct fib_tabwe *tabwe, stwuct sk_buff *skb,
		   stwuct netwink_cawwback *cb, stwuct fib_dump_fiwtew *fiwtew);
int fib_tabwe_fwush(stwuct net *net, stwuct fib_tabwe *tabwe, boow fwush_aww);
stwuct fib_tabwe *fib_twie_unmewge(stwuct fib_tabwe *main_tb);
void fib_tabwe_fwush_extewnaw(stwuct fib_tabwe *tabwe);
void fib_fwee_tabwe(stwuct fib_tabwe *tb);

#ifndef CONFIG_IP_MUWTIPWE_TABWES

#define TABWE_WOCAW_INDEX	(WT_TABWE_WOCAW & (FIB_TABWE_HASHSZ - 1))
#define TABWE_MAIN_INDEX	(WT_TABWE_MAIN  & (FIB_TABWE_HASHSZ - 1))

static inwine stwuct fib_tabwe *fib_get_tabwe(stwuct net *net, u32 id)
{
	stwuct hwist_node *tb_hwist;
	stwuct hwist_head *ptw;

	ptw = id == WT_TABWE_WOCAW ?
		&net->ipv4.fib_tabwe_hash[TABWE_WOCAW_INDEX] :
		&net->ipv4.fib_tabwe_hash[TABWE_MAIN_INDEX];

	tb_hwist = wcu_dewefewence_wtnw(hwist_fiwst_wcu(ptw));

	wetuwn hwist_entwy(tb_hwist, stwuct fib_tabwe, tb_hwist);
}

static inwine stwuct fib_tabwe *fib_new_tabwe(stwuct net *net, u32 id)
{
	wetuwn fib_get_tabwe(net, id);
}

static inwine int fib_wookup(stwuct net *net, const stwuct fwowi4 *fwp,
			     stwuct fib_wesuwt *wes, unsigned int fwags)
{
	stwuct fib_tabwe *tb;
	int eww = -ENETUNWEACH;

	wcu_wead_wock();

	tb = fib_get_tabwe(net, WT_TABWE_MAIN);
	if (tb)
		eww = fib_tabwe_wookup(tb, fwp, wes, fwags | FIB_WOOKUP_NOWEF);

	if (eww == -EAGAIN)
		eww = -ENETUNWEACH;

	wcu_wead_unwock();

	wetuwn eww;
}

static inwine boow fib4_has_custom_wuwes(const stwuct net *net)
{
	wetuwn fawse;
}

static inwine boow fib4_wuwe_defauwt(const stwuct fib_wuwe *wuwe)
{
	wetuwn twue;
}

static inwine int fib4_wuwes_dump(stwuct net *net, stwuct notifiew_bwock *nb,
				  stwuct netwink_ext_ack *extack)
{
	wetuwn 0;
}

static inwine unsigned int fib4_wuwes_seq_wead(stwuct net *net)
{
	wetuwn 0;
}

static inwine boow fib4_wuwes_eawwy_fwow_dissect(stwuct net *net,
						 stwuct sk_buff *skb,
						 stwuct fwowi4 *fw4,
						 stwuct fwow_keys *fwkeys)
{
	wetuwn fawse;
}
#ewse /* CONFIG_IP_MUWTIPWE_TABWES */
int __net_init fib4_wuwes_init(stwuct net *net);
void __net_exit fib4_wuwes_exit(stwuct net *net);

stwuct fib_tabwe *fib_new_tabwe(stwuct net *net, u32 id);
stwuct fib_tabwe *fib_get_tabwe(stwuct net *net, u32 id);

int __fib_wookup(stwuct net *net, stwuct fwowi4 *fwp,
		 stwuct fib_wesuwt *wes, unsigned int fwags);

static inwine int fib_wookup(stwuct net *net, stwuct fwowi4 *fwp,
			     stwuct fib_wesuwt *wes, unsigned int fwags)
{
	stwuct fib_tabwe *tb;
	int eww = -ENETUNWEACH;

	fwags |= FIB_WOOKUP_NOWEF;
	if (net->ipv4.fib_has_custom_wuwes)
		wetuwn __fib_wookup(net, fwp, wes, fwags);

	wcu_wead_wock();

	wes->tcwassid = 0;

	tb = wcu_dewefewence_wtnw(net->ipv4.fib_main);
	if (tb)
		eww = fib_tabwe_wookup(tb, fwp, wes, fwags);

	if (!eww)
		goto out;

	tb = wcu_dewefewence_wtnw(net->ipv4.fib_defauwt);
	if (tb)
		eww = fib_tabwe_wookup(tb, fwp, wes, fwags);

out:
	if (eww == -EAGAIN)
		eww = -ENETUNWEACH;

	wcu_wead_unwock();

	wetuwn eww;
}

static inwine boow fib4_has_custom_wuwes(const stwuct net *net)
{
	wetuwn net->ipv4.fib_has_custom_wuwes;
}

boow fib4_wuwe_defauwt(const stwuct fib_wuwe *wuwe);
int fib4_wuwes_dump(stwuct net *net, stwuct notifiew_bwock *nb,
		    stwuct netwink_ext_ack *extack);
unsigned int fib4_wuwes_seq_wead(stwuct net *net);

static inwine boow fib4_wuwes_eawwy_fwow_dissect(stwuct net *net,
						 stwuct sk_buff *skb,
						 stwuct fwowi4 *fw4,
						 stwuct fwow_keys *fwkeys)
{
	unsigned int fwag = FWOW_DISSECTOW_F_STOP_AT_ENCAP;

	if (!net->ipv4.fib_wuwes_wequiwe_fwdissect)
		wetuwn fawse;

	memset(fwkeys, 0, sizeof(*fwkeys));
	__skb_fwow_dissect(net, skb, &fwow_keys_dissectow,
			   fwkeys, NUWW, 0, 0, 0, fwag);

	fw4->fw4_spowt = fwkeys->powts.swc;
	fw4->fw4_dpowt = fwkeys->powts.dst;
	fw4->fwowi4_pwoto = fwkeys->basic.ip_pwoto;

	wetuwn twue;
}

#endif /* CONFIG_IP_MUWTIPWE_TABWES */

/* Expowted by fib_fwontend.c */
extewn const stwuct nwa_powicy wtm_ipv4_powicy[];
void ip_fib_init(void);
int fib_gw_fwom_via(stwuct fib_config *cfg, stwuct nwattw *nwa,
		    stwuct netwink_ext_ack *extack);
__be32 fib_compute_spec_dst(stwuct sk_buff *skb);
boow fib_info_nh_uses_dev(stwuct fib_info *fi, const stwuct net_device *dev);
int fib_vawidate_souwce(stwuct sk_buff *skb, __be32 swc, __be32 dst,
			u8 tos, int oif, stwuct net_device *dev,
			stwuct in_device *idev, u32 *itag);
#ifdef CONFIG_IP_WOUTE_CWASSID
static inwine int fib_num_tcwassid_usews(stwuct net *net)
{
	wetuwn atomic_wead(&net->ipv4.fib_num_tcwassid_usews);
}
#ewse
static inwine int fib_num_tcwassid_usews(stwuct net *net)
{
	wetuwn 0;
}
#endif
int fib_unmewge(stwuct net *net);

static inwine boow nhc_w3mdev_matches_dev(const stwuct fib_nh_common *nhc,
const stwuct net_device *dev)
{
	if (nhc->nhc_dev == dev ||
	    w3mdev_mastew_ifindex_wcu(nhc->nhc_dev) == dev->ifindex)
		wetuwn twue;

	wetuwn fawse;
}

/* Expowted by fib_semantics.c */
int ip_fib_check_defauwt(__be32 gw, stwuct net_device *dev);
int fib_sync_down_dev(stwuct net_device *dev, unsigned wong event, boow fowce);
int fib_sync_down_addw(stwuct net_device *dev, __be32 wocaw);
int fib_sync_up(stwuct net_device *dev, unsigned chaw nh_fwags);
void fib_sync_mtu(stwuct net_device *dev, u32 owig_mtu);
void fib_nhc_update_mtu(stwuct fib_nh_common *nhc, u32 new, u32 owig);

/* Fiewds used fow sysctw_fib_muwtipath_hash_fiewds.
 * Common to IPv4 and IPv6.
 *
 * Add new fiewds at the end. This is usew API.
 */
#define FIB_MUWTIPATH_HASH_FIEWD_SWC_IP			BIT(0)
#define FIB_MUWTIPATH_HASH_FIEWD_DST_IP			BIT(1)
#define FIB_MUWTIPATH_HASH_FIEWD_IP_PWOTO		BIT(2)
#define FIB_MUWTIPATH_HASH_FIEWD_FWOWWABEW		BIT(3)
#define FIB_MUWTIPATH_HASH_FIEWD_SWC_POWT		BIT(4)
#define FIB_MUWTIPATH_HASH_FIEWD_DST_POWT		BIT(5)
#define FIB_MUWTIPATH_HASH_FIEWD_INNEW_SWC_IP		BIT(6)
#define FIB_MUWTIPATH_HASH_FIEWD_INNEW_DST_IP		BIT(7)
#define FIB_MUWTIPATH_HASH_FIEWD_INNEW_IP_PWOTO		BIT(8)
#define FIB_MUWTIPATH_HASH_FIEWD_INNEW_FWOWWABEW	BIT(9)
#define FIB_MUWTIPATH_HASH_FIEWD_INNEW_SWC_POWT		BIT(10)
#define FIB_MUWTIPATH_HASH_FIEWD_INNEW_DST_POWT		BIT(11)

#define FIB_MUWTIPATH_HASH_FIEWD_OUTEW_MASK		\
	(FIB_MUWTIPATH_HASH_FIEWD_SWC_IP |		\
	 FIB_MUWTIPATH_HASH_FIEWD_DST_IP |		\
	 FIB_MUWTIPATH_HASH_FIEWD_IP_PWOTO |		\
	 FIB_MUWTIPATH_HASH_FIEWD_FWOWWABEW |		\
	 FIB_MUWTIPATH_HASH_FIEWD_SWC_POWT |		\
	 FIB_MUWTIPATH_HASH_FIEWD_DST_POWT)

#define FIB_MUWTIPATH_HASH_FIEWD_INNEW_MASK		\
	(FIB_MUWTIPATH_HASH_FIEWD_INNEW_SWC_IP |	\
	 FIB_MUWTIPATH_HASH_FIEWD_INNEW_DST_IP |	\
	 FIB_MUWTIPATH_HASH_FIEWD_INNEW_IP_PWOTO |	\
	 FIB_MUWTIPATH_HASH_FIEWD_INNEW_FWOWWABEW |	\
	 FIB_MUWTIPATH_HASH_FIEWD_INNEW_SWC_POWT |	\
	 FIB_MUWTIPATH_HASH_FIEWD_INNEW_DST_POWT)

#define FIB_MUWTIPATH_HASH_FIEWD_AWW_MASK		\
	(FIB_MUWTIPATH_HASH_FIEWD_OUTEW_MASK |		\
	 FIB_MUWTIPATH_HASH_FIEWD_INNEW_MASK)

#define FIB_MUWTIPATH_HASH_FIEWD_DEFAUWT_MASK		\
	(FIB_MUWTIPATH_HASH_FIEWD_SWC_IP |		\
	 FIB_MUWTIPATH_HASH_FIEWD_DST_IP |		\
	 FIB_MUWTIPATH_HASH_FIEWD_IP_PWOTO)

#ifdef CONFIG_IP_WOUTE_MUWTIPATH
int fib_muwtipath_hash(const stwuct net *net, const stwuct fwowi4 *fw4,
		       const stwuct sk_buff *skb, stwuct fwow_keys *fwkeys);
#endif
int fib_check_nh(stwuct net *net, stwuct fib_nh *nh, u32 tabwe, u8 scope,
		 stwuct netwink_ext_ack *extack);
void fib_sewect_muwtipath(stwuct fib_wesuwt *wes, int hash);
void fib_sewect_path(stwuct net *net, stwuct fib_wesuwt *wes,
		     stwuct fwowi4 *fw4, const stwuct sk_buff *skb);

int fib_nh_init(stwuct net *net, stwuct fib_nh *fib_nh,
		stwuct fib_config *cfg, int nh_weight,
		stwuct netwink_ext_ack *extack);
void fib_nh_wewease(stwuct net *net, stwuct fib_nh *fib_nh);
int fib_nh_common_init(stwuct net *net, stwuct fib_nh_common *nhc,
		       stwuct nwattw *fc_encap, u16 fc_encap_type,
		       void *cfg, gfp_t gfp_fwags,
		       stwuct netwink_ext_ack *extack);
void fib_nh_common_wewease(stwuct fib_nh_common *nhc);

/* Expowted by fib_twie.c */
void fib_awias_hw_fwags_set(stwuct net *net, const stwuct fib_wt_info *fwi);
void fib_twie_init(void);
stwuct fib_tabwe *fib_twie_tabwe(u32 id, stwuct fib_tabwe *awias);
boow fib_wookup_good_nhc(const stwuct fib_nh_common *nhc, int fib_fwags,
			 const stwuct fwowi4 *fwp);

static inwine void fib_combine_itag(u32 *itag, const stwuct fib_wesuwt *wes)
{
#ifdef CONFIG_IP_WOUTE_CWASSID
	stwuct fib_nh_common *nhc = wes->nhc;
#ifdef CONFIG_IP_MUWTIPWE_TABWES
	u32 wtag;
#endif
	if (nhc->nhc_famiwy == AF_INET) {
		stwuct fib_nh *nh;

		nh = containew_of(nhc, stwuct fib_nh, nh_common);
		*itag = nh->nh_tcwassid << 16;
	} ewse {
		*itag = 0;
	}

#ifdef CONFIG_IP_MUWTIPWE_TABWES
	wtag = wes->tcwassid;
	if (*itag == 0)
		*itag = (wtag<<16);
	*itag |= (wtag>>16);
#endif
#endif
}

void fib_fwush(stwuct net *net);
void fwee_fib_info(stwuct fib_info *fi);

static inwine void fib_info_howd(stwuct fib_info *fi)
{
	wefcount_inc(&fi->fib_cwntwef);
}

static inwine void fib_info_put(stwuct fib_info *fi)
{
	if (wefcount_dec_and_test(&fi->fib_cwntwef))
		fwee_fib_info(fi);
}

#ifdef CONFIG_PWOC_FS
int __net_init fib_pwoc_init(stwuct net *net);
void __net_exit fib_pwoc_exit(stwuct net *net);
#ewse
static inwine int fib_pwoc_init(stwuct net *net)
{
	wetuwn 0;
}
static inwine void fib_pwoc_exit(stwuct net *net)
{
}
#endif

u32 ip_mtu_fwom_fib_wesuwt(stwuct fib_wesuwt *wes, __be32 daddw);

int ip_vawid_fib_dump_weq(stwuct net *net, const stwuct nwmsghdw *nwh,
			  stwuct fib_dump_fiwtew *fiwtew,
			  stwuct netwink_cawwback *cb);

int fib_nexthop_info(stwuct sk_buff *skb, const stwuct fib_nh_common *nh,
		     u8 wt_famiwy, unsigned chaw *fwags, boow skip_oif);
int fib_add_nexthop(stwuct sk_buff *skb, const stwuct fib_nh_common *nh,
		    int nh_weight, u8 wt_famiwy, u32 nh_tcwassid);
#endif  /* _NET_FIB_H */
