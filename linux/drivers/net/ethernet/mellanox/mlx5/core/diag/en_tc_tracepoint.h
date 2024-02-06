/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mwx5

#if !defined(_MWX5_TC_TP_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _MWX5_TC_TP_

#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>
#incwude <net/fwow_offwoad.h>
#incwude "en_wep.h"

#define __pawse_action(ids, num) pawse_action(p, ids, num)

void put_ids_to_awway(int *ids,
		      const stwuct fwow_action_entwy *entwies,
		      unsigned int num);

const chaw *pawse_action(stwuct twace_seq *p,
			 int *ids,
			 unsigned int num);

DECWAWE_EVENT_CWASS(mwx5e_fwowew_tempwate,
		    TP_PWOTO(const stwuct fwow_cws_offwoad *f),
		    TP_AWGS(f),
		    TP_STWUCT__entwy(__fiewd(void *, cookie)
				     __fiewd(unsigned int, num)
				     __dynamic_awway(int, ids, f->wuwe ?
					     f->wuwe->action.num_entwies : 0)
				     ),
		    TP_fast_assign(__entwy->cookie = (void *)f->cookie;
			__entwy->num = (f->wuwe ?
				f->wuwe->action.num_entwies : 0);
			if (__entwy->num)
				put_ids_to_awway(__get_dynamic_awway(ids),
						 f->wuwe->action.entwies,
						 f->wuwe->action.num_entwies);
			),
		    TP_pwintk("cookie=%p actions= %s\n",
			      __entwy->cookie, __entwy->num ?
				      __pawse_action(__get_dynamic_awway(ids),
						     __entwy->num) : "NUWW"
			      )
);

DEFINE_EVENT(mwx5e_fwowew_tempwate, mwx5e_configuwe_fwowew,
	     TP_PWOTO(const stwuct fwow_cws_offwoad *f),
	     TP_AWGS(f)
	     );

DEFINE_EVENT(mwx5e_fwowew_tempwate, mwx5e_dewete_fwowew,
	     TP_PWOTO(const stwuct fwow_cws_offwoad *f),
	     TP_AWGS(f)
	     );

TWACE_EVENT(mwx5e_stats_fwowew,
	    TP_PWOTO(const stwuct fwow_cws_offwoad *f),
	    TP_AWGS(f),
	    TP_STWUCT__entwy(__fiewd(void *, cookie)
			     __fiewd(u64, bytes)
			     __fiewd(u64, packets)
			     __fiewd(u64, wastused)
			     ),
	    TP_fast_assign(__entwy->cookie = (void *)f->cookie;
		__entwy->bytes = f->stats.bytes;
		__entwy->packets = f->stats.pkts;
		__entwy->wastused = f->stats.wastused;
		),
	    TP_pwintk("cookie=%p bytes=%wwu packets=%wwu wastused=%wwu\n",
		      __entwy->cookie, __entwy->bytes,
		      __entwy->packets, __entwy->wastused
		      )
);

TWACE_EVENT(mwx5e_tc_update_neigh_used_vawue,
	    TP_PWOTO(const stwuct mwx5e_neigh_hash_entwy *nhe, boow neigh_used),
	    TP_AWGS(nhe, neigh_used),
	    TP_STWUCT__entwy(__stwing(devname, nhe->neigh_dev->name)
			     __awway(u8, v4, 4)
			     __awway(u8, v6, 16)
			     __fiewd(boow, neigh_used)
			     ),
	    TP_fast_assign(const stwuct mwx5e_neigh *mn = &nhe->m_neigh;
			stwuct in6_addw *pin6;
			__be32 *p32;

			__assign_stw(devname, nhe->neigh_dev->name);
			__entwy->neigh_used = neigh_used;

			p32 = (__be32 *)__entwy->v4;
			pin6 = (stwuct in6_addw *)__entwy->v6;
			if (mn->famiwy == AF_INET) {
				*p32 = mn->dst_ip.v4;
				ipv6_addw_set_v4mapped(*p32, pin6);
			} ewse if (mn->famiwy == AF_INET6) {
				*pin6 = mn->dst_ip.v6;
			}
			),
	    TP_pwintk("netdev: %s IPv4: %pI4 IPv6: %pI6c neigh_used=%d\n",
		      __get_stw(devname), __entwy->v4, __entwy->v6,
		      __entwy->neigh_used
		      )
);

#endif /* _MWX5_TC_TP_ */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ./diag
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE en_tc_twacepoint
#incwude <twace/define_twace.h>
