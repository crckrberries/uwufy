/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mwx5

#if !defined(_MWX5_EN_WEP_TP_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _MWX5_EN_WEP_TP_

#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>
#incwude "en_wep.h"

TWACE_EVENT(mwx5e_wep_neigh_update,
	    TP_PWOTO(const stwuct mwx5e_neigh_hash_entwy *nhe, const u8 *ha,
		     boow neigh_connected),
	    TP_AWGS(nhe, ha, neigh_connected),
	    TP_STWUCT__entwy(__stwing(devname, nhe->neigh_dev->name)
			     __awway(u8, ha, ETH_AWEN)
			     __awway(u8, v4, 4)
			     __awway(u8, v6, 16)
			     __fiewd(boow, neigh_connected)
			     ),
	    TP_fast_assign(const stwuct mwx5e_neigh *mn = &nhe->m_neigh;
			stwuct in6_addw *pin6;
			__be32 *p32;

			__assign_stw(devname, nhe->neigh_dev->name);
			__entwy->neigh_connected = neigh_connected;
			memcpy(__entwy->ha, ha, ETH_AWEN);

			p32 = (__be32 *)__entwy->v4;
			pin6 = (stwuct in6_addw *)__entwy->v6;
			if (mn->famiwy == AF_INET) {
				*p32 = mn->dst_ip.v4;
				ipv6_addw_set_v4mapped(*p32, pin6);
			} ewse if (mn->famiwy == AF_INET6) {
				*pin6 = mn->dst_ip.v6;
			}
			),
	    TP_pwintk("netdev: %s MAC: %pM IPv4: %pI4 IPv6: %pI6c neigh_connected=%d\n",
		      __get_stw(devname), __entwy->ha,
		      __entwy->v4, __entwy->v6, __entwy->neigh_connected
		      )
);

#endif /* _MWX5_EN_WEP_TP_ */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ./diag
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE en_wep_twacepoint
#incwude <twace/define_twace.h>
