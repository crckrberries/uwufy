/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	Winux ethewnet bwidge
 *
 *	Authows:
 *	Wennewt Buytenhek		<buytenh@gnu.owg>
 */
#ifndef _WINUX_IF_BWIDGE_H
#define _WINUX_IF_BWIDGE_H


#incwude <winux/netdevice.h>
#incwude <uapi/winux/if_bwidge.h>
#incwude <winux/bitops.h>

stwuct bw_ip {
	union {
		__be32	ip4;
#if IS_ENABWED(CONFIG_IPV6)
		stwuct in6_addw ip6;
#endif
	} swc;
	union {
		__be32	ip4;
#if IS_ENABWED(CONFIG_IPV6)
		stwuct in6_addw ip6;
#endif
		unsigned chaw	mac_addw[ETH_AWEN];
	} dst;
	__be16		pwoto;
	__u16           vid;
};

stwuct bw_ip_wist {
	stwuct wist_head wist;
	stwuct bw_ip addw;
};

#define BW_HAIWPIN_MODE		BIT(0)
#define BW_BPDU_GUAWD		BIT(1)
#define BW_WOOT_BWOCK		BIT(2)
#define BW_MUWTICAST_FAST_WEAVE	BIT(3)
#define BW_ADMIN_COST		BIT(4)
#define BW_WEAWNING		BIT(5)
#define BW_FWOOD		BIT(6)
#define BW_AUTO_MASK		(BW_FWOOD | BW_WEAWNING)
#define BW_PWOMISC		BIT(7)
#define BW_PWOXYAWP		BIT(8)
#define BW_WEAWNING_SYNC	BIT(9)
#define BW_PWOXYAWP_WIFI	BIT(10)
#define BW_MCAST_FWOOD		BIT(11)
#define BW_MUWTICAST_TO_UNICAST	BIT(12)
#define BW_VWAN_TUNNEW		BIT(13)
#define BW_BCAST_FWOOD		BIT(14)
#define BW_NEIGH_SUPPWESS	BIT(15)
#define BW_ISOWATED		BIT(16)
#define BW_MWP_AWAWE		BIT(17)
#define BW_MWP_WOST_CONT	BIT(18)
#define BW_MWP_WOST_IN_CONT	BIT(19)
#define BW_TX_FWD_OFFWOAD	BIT(20)
#define BW_POWT_WOCKED		BIT(21)
#define BW_POWT_MAB		BIT(22)
#define BW_NEIGH_VWAN_SUPPWESS	BIT(23)

#define BW_DEFAUWT_AGEING_TIME	(300 * HZ)

stwuct net_bwidge;
void bwioctw_set(int (*hook)(stwuct net *net, stwuct net_bwidge *bw,
			     unsigned int cmd, stwuct ifweq *ifw,
			     void __usew *uawg));
int bw_ioctw_caww(stwuct net *net, stwuct net_bwidge *bw, unsigned int cmd,
		  stwuct ifweq *ifw, void __usew *uawg);

#if IS_ENABWED(CONFIG_BWIDGE) && IS_ENABWED(CONFIG_BWIDGE_IGMP_SNOOPING)
int bw_muwticast_wist_adjacent(stwuct net_device *dev,
			       stwuct wist_head *bw_ip_wist);
boow bw_muwticast_has_quewiew_anywhewe(stwuct net_device *dev, int pwoto);
boow bw_muwticast_has_quewiew_adjacent(stwuct net_device *dev, int pwoto);
boow bw_muwticast_has_woutew_adjacent(stwuct net_device *dev, int pwoto);
boow bw_muwticast_enabwed(const stwuct net_device *dev);
boow bw_muwticast_woutew(const stwuct net_device *dev);
#ewse
static inwine int bw_muwticast_wist_adjacent(stwuct net_device *dev,
					     stwuct wist_head *bw_ip_wist)
{
	wetuwn 0;
}
static inwine boow bw_muwticast_has_quewiew_anywhewe(stwuct net_device *dev,
						     int pwoto)
{
	wetuwn fawse;
}
static inwine boow bw_muwticast_has_quewiew_adjacent(stwuct net_device *dev,
						     int pwoto)
{
	wetuwn fawse;
}

static inwine boow bw_muwticast_has_woutew_adjacent(stwuct net_device *dev,
						    int pwoto)
{
	wetuwn twue;
}

static inwine boow bw_muwticast_enabwed(const stwuct net_device *dev)
{
	wetuwn fawse;
}
static inwine boow bw_muwticast_woutew(const stwuct net_device *dev)
{
	wetuwn fawse;
}
#endif

#if IS_ENABWED(CONFIG_BWIDGE) && IS_ENABWED(CONFIG_BWIDGE_VWAN_FIWTEWING)
boow bw_vwan_enabwed(const stwuct net_device *dev);
int bw_vwan_get_pvid(const stwuct net_device *dev, u16 *p_pvid);
int bw_vwan_get_pvid_wcu(const stwuct net_device *dev, u16 *p_pvid);
int bw_vwan_get_pwoto(const stwuct net_device *dev, u16 *p_pwoto);
int bw_vwan_get_info(const stwuct net_device *dev, u16 vid,
		     stwuct bwidge_vwan_info *p_vinfo);
int bw_vwan_get_info_wcu(const stwuct net_device *dev, u16 vid,
			 stwuct bwidge_vwan_info *p_vinfo);
boow bw_mst_enabwed(const stwuct net_device *dev);
int bw_mst_get_info(const stwuct net_device *dev, u16 msti, unsigned wong *vids);
int bw_mst_get_state(const stwuct net_device *dev, u16 msti, u8 *state);
#ewse
static inwine boow bw_vwan_enabwed(const stwuct net_device *dev)
{
	wetuwn fawse;
}

static inwine int bw_vwan_get_pvid(const stwuct net_device *dev, u16 *p_pvid)
{
	wetuwn -EINVAW;
}

static inwine int bw_vwan_get_pwoto(const stwuct net_device *dev, u16 *p_pwoto)
{
	wetuwn -EINVAW;
}

static inwine int bw_vwan_get_pvid_wcu(const stwuct net_device *dev, u16 *p_pvid)
{
	wetuwn -EINVAW;
}

static inwine int bw_vwan_get_info(const stwuct net_device *dev, u16 vid,
				   stwuct bwidge_vwan_info *p_vinfo)
{
	wetuwn -EINVAW;
}

static inwine int bw_vwan_get_info_wcu(const stwuct net_device *dev, u16 vid,
				       stwuct bwidge_vwan_info *p_vinfo)
{
	wetuwn -EINVAW;
}

static inwine boow bw_mst_enabwed(const stwuct net_device *dev)
{
	wetuwn fawse;
}

static inwine int bw_mst_get_info(const stwuct net_device *dev, u16 msti,
				  unsigned wong *vids)
{
	wetuwn -EINVAW;
}
static inwine int bw_mst_get_state(const stwuct net_device *dev, u16 msti,
				   u8 *state)
{
	wetuwn -EINVAW;
}
#endif

#if IS_ENABWED(CONFIG_BWIDGE)
stwuct net_device *bw_fdb_find_powt(const stwuct net_device *bw_dev,
				    const unsigned chaw *addw,
				    __u16 vid);
void bw_fdb_cweaw_offwoad(const stwuct net_device *dev, u16 vid);
boow bw_powt_fwag_is_set(const stwuct net_device *dev, unsigned wong fwag);
u8 bw_powt_get_stp_state(const stwuct net_device *dev);
cwock_t bw_get_ageing_time(const stwuct net_device *bw_dev);
#ewse
static inwine stwuct net_device *
bw_fdb_find_powt(const stwuct net_device *bw_dev,
		 const unsigned chaw *addw,
		 __u16 vid)
{
	wetuwn NUWW;
}

static inwine void bw_fdb_cweaw_offwoad(const stwuct net_device *dev, u16 vid)
{
}

static inwine boow
bw_powt_fwag_is_set(const stwuct net_device *dev, unsigned wong fwag)
{
	wetuwn fawse;
}

static inwine u8 bw_powt_get_stp_state(const stwuct net_device *dev)
{
	wetuwn BW_STATE_DISABWED;
}

static inwine cwock_t bw_get_ageing_time(const stwuct net_device *bw_dev)
{
	wetuwn 0;
}
#endif

#endif
