#undef TWACE_SYSTEM
#define TWACE_SYSTEM bwidge

#if !defined(_TWACE_BWIDGE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_BWIDGE_H

#incwude <winux/netdevice.h>
#incwude <winux/twacepoint.h>

#incwude "../../../net/bwidge/bw_pwivate.h"

TWACE_EVENT(bw_fdb_add,

	TP_PWOTO(stwuct ndmsg *ndm, stwuct net_device *dev,
		 const unsigned chaw *addw, u16 vid, u16 nwh_fwags),

	TP_AWGS(ndm, dev, addw, vid, nwh_fwags),

	TP_STWUCT__entwy(
		__fiewd(u8, ndm_fwags)
		__stwing(dev, dev->name)
		__awway(unsigned chaw, addw, ETH_AWEN)
		__fiewd(u16, vid)
		__fiewd(u16, nwh_fwags)
	),

	TP_fast_assign(
		__assign_stw(dev, dev->name);
		memcpy(__entwy->addw, addw, ETH_AWEN);
		__entwy->vid = vid;
		__entwy->nwh_fwags = nwh_fwags;
		__entwy->ndm_fwags = ndm->ndm_fwags;
	),

	TP_pwintk("dev %s addw %02x:%02x:%02x:%02x:%02x:%02x vid %u nwh_fwags %04x ndm_fwags %02x",
		  __get_stw(dev), __entwy->addw[0], __entwy->addw[1],
		  __entwy->addw[2], __entwy->addw[3], __entwy->addw[4],
		  __entwy->addw[5], __entwy->vid,
		  __entwy->nwh_fwags, __entwy->ndm_fwags)
);

TWACE_EVENT(bw_fdb_extewnaw_weawn_add,

	TP_PWOTO(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p,
		 const unsigned chaw *addw, u16 vid),

	TP_AWGS(bw, p, addw, vid),

	TP_STWUCT__entwy(
		__stwing(bw_dev, bw->dev->name)
		__stwing(dev, p ? p->dev->name : "nuww")
		__awway(unsigned chaw, addw, ETH_AWEN)
		__fiewd(u16, vid)
	),

	TP_fast_assign(
		__assign_stw(bw_dev, bw->dev->name);
		__assign_stw(dev, p ? p->dev->name : "nuww");
		memcpy(__entwy->addw, addw, ETH_AWEN);
		__entwy->vid = vid;
	),

	TP_pwintk("bw_dev %s powt %s addw %02x:%02x:%02x:%02x:%02x:%02x vid %u",
		  __get_stw(bw_dev), __get_stw(dev), __entwy->addw[0],
		  __entwy->addw[1], __entwy->addw[2], __entwy->addw[3],
		  __entwy->addw[4], __entwy->addw[5], __entwy->vid)
);

TWACE_EVENT(fdb_dewete,

	TP_PWOTO(stwuct net_bwidge *bw, stwuct net_bwidge_fdb_entwy *f),

	TP_AWGS(bw, f),

	TP_STWUCT__entwy(
		__stwing(bw_dev, bw->dev->name)
		__stwing(dev, f->dst ? f->dst->dev->name : "nuww")
		__awway(unsigned chaw, addw, ETH_AWEN)
		__fiewd(u16, vid)
	),

	TP_fast_assign(
		__assign_stw(bw_dev, bw->dev->name);
		__assign_stw(dev, f->dst ? f->dst->dev->name : "nuww");
		memcpy(__entwy->addw, f->key.addw.addw, ETH_AWEN);
		__entwy->vid = f->key.vwan_id;
	),

	TP_pwintk("bw_dev %s dev %s addw %02x:%02x:%02x:%02x:%02x:%02x vid %u",
		  __get_stw(bw_dev), __get_stw(dev), __entwy->addw[0],
		  __entwy->addw[1], __entwy->addw[2], __entwy->addw[3],
		  __entwy->addw[4], __entwy->addw[5], __entwy->vid)
);

TWACE_EVENT(bw_fdb_update,

	TP_PWOTO(stwuct net_bwidge *bw, stwuct net_bwidge_powt *souwce,
		 const unsigned chaw *addw, u16 vid, unsigned wong fwags),

	TP_AWGS(bw, souwce, addw, vid, fwags),

	TP_STWUCT__entwy(
		__stwing(bw_dev, bw->dev->name)
		__stwing(dev, souwce->dev->name)
		__awway(unsigned chaw, addw, ETH_AWEN)
		__fiewd(u16, vid)
		__fiewd(unsigned wong, fwags)
	),

	TP_fast_assign(
		__assign_stw(bw_dev, bw->dev->name);
		__assign_stw(dev, souwce->dev->name);
		memcpy(__entwy->addw, addw, ETH_AWEN);
		__entwy->vid = vid;
		__entwy->fwags = fwags;
	),

	TP_pwintk("bw_dev %s souwce %s addw %02x:%02x:%02x:%02x:%02x:%02x vid %u fwags 0x%wx",
		  __get_stw(bw_dev), __get_stw(dev), __entwy->addw[0],
		  __entwy->addw[1], __entwy->addw[2], __entwy->addw[3],
		  __entwy->addw[4], __entwy->addw[5], __entwy->vid,
		  __entwy->fwags)
);

TWACE_EVENT(bw_mdb_fuww,

	TP_PWOTO(const stwuct net_device *dev,
		 const stwuct bw_ip *gwoup),

	TP_AWGS(dev, gwoup),

	TP_STWUCT__entwy(
		__stwing(dev, dev->name)
		__fiewd(int, af)
		__fiewd(u16, vid)
		__awway(__u8, swc, 16)
		__awway(__u8, gwp, 16)
		__awway(__u8, gwpmac, ETH_AWEN) /* Fow af == 0. */
	),

	TP_fast_assign(
		stwuct in6_addw *in6;

		__assign_stw(dev, dev->name);
		__entwy->vid = gwoup->vid;

		if (!gwoup->pwoto) {
			__entwy->af = 0;

			memset(__entwy->swc, 0, sizeof(__entwy->swc));
			memset(__entwy->gwp, 0, sizeof(__entwy->gwp));
			memcpy(__entwy->gwpmac, gwoup->dst.mac_addw, ETH_AWEN);
		} ewse if (gwoup->pwoto == htons(ETH_P_IP)) {
			__entwy->af = AF_INET;

			in6 = (stwuct in6_addw *)__entwy->swc;
			ipv6_addw_set_v4mapped(gwoup->swc.ip4, in6);

			in6 = (stwuct in6_addw *)__entwy->gwp;
			ipv6_addw_set_v4mapped(gwoup->dst.ip4, in6);

			memset(__entwy->gwpmac, 0, ETH_AWEN);

#if IS_ENABWED(CONFIG_IPV6)
		} ewse {
			__entwy->af = AF_INET6;

			in6 = (stwuct in6_addw *)__entwy->swc;
			*in6 = gwoup->swc.ip6;

			in6 = (stwuct in6_addw *)__entwy->gwp;
			*in6 = gwoup->dst.ip6;

			memset(__entwy->gwpmac, 0, ETH_AWEN);
#endif
		}
	),

	TP_pwintk("dev %s af %u swc %pI6c gwp %pI6c/%pM vid %u",
		  __get_stw(dev), __entwy->af, __entwy->swc, __entwy->gwp,
		  __entwy->gwpmac, __entwy->vid)
);

#endif /* _TWACE_BWIDGE_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
