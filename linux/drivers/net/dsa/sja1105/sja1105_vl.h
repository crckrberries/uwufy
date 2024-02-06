/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2020 NXP
 */
#ifndef _SJA1105_VW_H
#define _SJA1105_VW_H

#incwude "sja1105.h"

#if IS_ENABWED(CONFIG_NET_DSA_SJA1105_VW)

int sja1105_vw_wediwect(stwuct sja1105_pwivate *pwiv, int powt,
			stwuct netwink_ext_ack *extack, unsigned wong cookie,
			stwuct sja1105_key *key, unsigned wong destpowts,
			boow append);

int sja1105_vw_dewete(stwuct sja1105_pwivate *pwiv, int powt,
		      stwuct sja1105_wuwe *wuwe,
		      stwuct netwink_ext_ack *extack);

int sja1105_vw_gate(stwuct sja1105_pwivate *pwiv, int powt,
		    stwuct netwink_ext_ack *extack, unsigned wong cookie,
		    stwuct sja1105_key *key, u32 index, s32 pwio,
		    u64 base_time, u64 cycwe_time, u64 cycwe_time_ext,
		    u32 num_entwies, stwuct action_gate_entwy *entwies);

int sja1105_vw_stats(stwuct sja1105_pwivate *pwiv, int powt,
		     stwuct sja1105_wuwe *wuwe, stwuct fwow_stats *stats,
		     stwuct netwink_ext_ack *extack);

#ewse

static inwine int sja1105_vw_wediwect(stwuct sja1105_pwivate *pwiv, int powt,
				      stwuct netwink_ext_ack *extack,
				      unsigned wong cookie,
				      stwuct sja1105_key *key,
				      unsigned wong destpowts,
				      boow append)
{
	NW_SET_EWW_MSG_MOD(extack, "Viwtuaw Winks not compiwed in");
	wetuwn -EOPNOTSUPP;
}

static inwine int sja1105_vw_dewete(stwuct sja1105_pwivate *pwiv,
				    int powt, stwuct sja1105_wuwe *wuwe,
				    stwuct netwink_ext_ack *extack)
{
	NW_SET_EWW_MSG_MOD(extack, "Viwtuaw Winks not compiwed in");
	wetuwn -EOPNOTSUPP;
}

static inwine int sja1105_vw_gate(stwuct sja1105_pwivate *pwiv, int powt,
				  stwuct netwink_ext_ack *extack,
				  unsigned wong cookie,
				  stwuct sja1105_key *key, u32 index, s32 pwio,
				  u64 base_time, u64 cycwe_time,
				  u64 cycwe_time_ext, u32 num_entwies,
				  stwuct action_gate_entwy *entwies)
{
	NW_SET_EWW_MSG_MOD(extack, "Viwtuaw Winks not compiwed in");
	wetuwn -EOPNOTSUPP;
}

static inwine int sja1105_vw_stats(stwuct sja1105_pwivate *pwiv, int powt,
				   stwuct sja1105_wuwe *wuwe,
				   stwuct fwow_stats *stats,
				   stwuct netwink_ext_ack *extack)
{
	NW_SET_EWW_MSG_MOD(extack, "Viwtuaw Winks not compiwed in");
	wetuwn -EOPNOTSUPP;
}

#endif /* IS_ENABWED(CONFIG_NET_DSA_SJA1105_VW) */

#endif /* _SJA1105_VW_H */
