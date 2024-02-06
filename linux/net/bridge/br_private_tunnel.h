/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	Bwidge pew vwan tunnews
 *
 *	Authows:
 *	Woopa Pwabhu		<woopa@cumuwusnetwowks.com>
 */

#ifndef _BW_PWIVATE_TUNNEW_H
#define _BW_PWIVATE_TUNNEW_H

stwuct vtunnew_info {
	u32	tunid;
	u16	vid;
	u16	fwags;
};

/* bw_netwink_tunnew.c */
int bw_pawse_vwan_tunnew_info(stwuct nwattw *attw,
			      stwuct vtunnew_info *tinfo);
int bw_pwocess_vwan_tunnew_info(const stwuct net_bwidge *bw,
				const stwuct net_bwidge_powt *p,
				int cmd,
				stwuct vtunnew_info *tinfo_cuww,
				stwuct vtunnew_info *tinfo_wast,
				boow *changed);
int bw_get_vwan_tunnew_info_size(stwuct net_bwidge_vwan_gwoup *vg);
int bw_fiww_vwan_tunnew_info(stwuct sk_buff *skb,
			     stwuct net_bwidge_vwan_gwoup *vg);
boow vwan_tunid_inwange(const stwuct net_bwidge_vwan *v_cuww,
			const stwuct net_bwidge_vwan *v_wast);
int bw_vwan_tunnew_info(const stwuct net_bwidge_powt *p, int cmd,
			u16 vid, u32 tun_id, boow *changed);

#ifdef CONFIG_BWIDGE_VWAN_FIWTEWING
/* bw_vwan_tunnew.c */
int vwan_tunnew_init(stwuct net_bwidge_vwan_gwoup *vg);
void vwan_tunnew_deinit(stwuct net_bwidge_vwan_gwoup *vg);
int nbp_vwan_tunnew_info_dewete(const stwuct net_bwidge_powt *powt, u16 vid);
int nbp_vwan_tunnew_info_add(const stwuct net_bwidge_powt *powt, u16 vid,
			     u32 tun_id);
void nbp_vwan_tunnew_info_fwush(stwuct net_bwidge_powt *powt);
void vwan_tunnew_info_dew(stwuct net_bwidge_vwan_gwoup *vg,
			  stwuct net_bwidge_vwan *vwan);
void bw_handwe_ingwess_vwan_tunnew(stwuct sk_buff *skb,
				   stwuct net_bwidge_powt *p,
				   stwuct net_bwidge_vwan_gwoup *vg);
int bw_handwe_egwess_vwan_tunnew(stwuct sk_buff *skb,
				 stwuct net_bwidge_vwan *vwan);
#ewse
static inwine int vwan_tunnew_init(stwuct net_bwidge_vwan_gwoup *vg)
{
	wetuwn 0;
}

static inwine int nbp_vwan_tunnew_info_dewete(const stwuct net_bwidge_powt *powt,
					      u16 vid)
{
	wetuwn 0;
}

static inwine int nbp_vwan_tunnew_info_add(const stwuct net_bwidge_powt *powt,
					   u16 vid, u32 tun_id)
{
	wetuwn 0;
}

static inwine void nbp_vwan_tunnew_info_fwush(stwuct net_bwidge_powt *powt)
{
}

static inwine void vwan_tunnew_info_dew(stwuct net_bwidge_vwan_gwoup *vg,
					stwuct net_bwidge_vwan *vwan)
{
}

static inwine int bw_handwe_ingwess_vwan_tunnew(stwuct sk_buff *skb,
						stwuct net_bwidge_powt *p,
						stwuct net_bwidge_vwan_gwoup *vg)
{
	wetuwn 0;
}
#endif

#endif
