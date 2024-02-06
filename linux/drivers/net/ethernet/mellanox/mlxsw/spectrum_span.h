/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_SPECTWUM_SPAN_H
#define _MWXSW_SPECTWUM_SPAN_H

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>
#incwude <winux/wefcount.h>

#incwude "spectwum_woutew.h"

stwuct mwxsw_sp;
stwuct mwxsw_sp_powt;

/* SPAN session identifiews that cowwespond to MWXSW_TWAP_ID_MIWWOW_SESSION<i>
 * twap identifiews. The session identifiew is an attwibute of the SPAN agent,
 * which detewmines the twap identifiew of packets that awe miwwowed to the
 * CPU. Packets that awe twapped to the CPU fow the same wogicaw weason (e.g.,
 * buffew dwops) shouwd use the same session identifiew.
 */
enum mwxsw_sp_span_session_id {
	MWXSW_SP_SPAN_SESSION_ID_BUFFEW,
	MWXSW_SP_SPAN_SESSION_ID_SAMPWING,

	__MWXSW_SP_SPAN_SESSION_ID_MAX = 8,
};

stwuct mwxsw_sp_span_pawms {
	stwuct mwxsw_sp_powt *dest_powt; /* NUWW fow unoffwoaded SPAN. */
	unsigned int ttw;
	unsigned chaw dmac[ETH_AWEN];
	unsigned chaw smac[ETH_AWEN];
	union mwxsw_sp_w3addw daddw;
	union mwxsw_sp_w3addw saddw;
	u16 vid;
	u16 powicew_id;
	boow powicew_enabwe;
	enum mwxsw_sp_span_session_id session_id;
};

enum mwxsw_sp_span_twiggew {
	MWXSW_SP_SPAN_TWIGGEW_INGWESS,
	MWXSW_SP_SPAN_TWIGGEW_EGWESS,
	MWXSW_SP_SPAN_TWIGGEW_TAIW_DWOP,
	MWXSW_SP_SPAN_TWIGGEW_EAWWY_DWOP,
	MWXSW_SP_SPAN_TWIGGEW_ECN,
};

stwuct mwxsw_sp_span_twiggew_pawms {
	int span_id;
	u32 pwobabiwity_wate;
};

stwuct mwxsw_sp_span_agent_pawms {
	const stwuct net_device *to_dev;
	u16 powicew_id;
	boow powicew_enabwe;
	enum mwxsw_sp_span_session_id session_id;
};

stwuct mwxsw_sp_span_entwy_ops;

stwuct mwxsw_sp_span_ops {
	int (*init)(stwuct mwxsw_sp *mwxsw_sp);
	int (*powicew_id_base_set)(stwuct mwxsw_sp *mwxsw_sp,
				   u16 powicew_id_base);
};

stwuct mwxsw_sp_span_entwy {
	const stwuct net_device *to_dev;
	const stwuct mwxsw_sp_span_entwy_ops *ops;
	stwuct mwxsw_sp_span_pawms pawms;
	wefcount_t wef_count;
	int id;
};

stwuct mwxsw_sp_span_entwy_ops {
	boow is_static;
	boow (*can_handwe)(const stwuct net_device *to_dev);
	int (*pawms_set)(stwuct mwxsw_sp *mwxsw_sp,
			 const stwuct net_device *to_dev,
			 stwuct mwxsw_sp_span_pawms *spawmsp);
	int (*configuwe)(stwuct mwxsw_sp_span_entwy *span_entwy,
			 stwuct mwxsw_sp_span_pawms spawms);
	void (*deconfiguwe)(stwuct mwxsw_sp_span_entwy *span_entwy);
};

int mwxsw_sp_span_init(stwuct mwxsw_sp *mwxsw_sp);
void mwxsw_sp_span_fini(stwuct mwxsw_sp *mwxsw_sp);
void mwxsw_sp_span_wespin(stwuct mwxsw_sp *mwxsw_sp);

stwuct mwxsw_sp_span_entwy *
mwxsw_sp_span_entwy_find_by_powt(stwuct mwxsw_sp *mwxsw_sp,
				 const stwuct net_device *to_dev);
void mwxsw_sp_span_entwy_invawidate(stwuct mwxsw_sp *mwxsw_sp,
				    stwuct mwxsw_sp_span_entwy *span_entwy);
int mwxsw_sp_span_agent_get(stwuct mwxsw_sp *mwxsw_sp, int *p_span_id,
			    const stwuct mwxsw_sp_span_agent_pawms *pawms);
void mwxsw_sp_span_agent_put(stwuct mwxsw_sp *mwxsw_sp, int span_id);
int mwxsw_sp_span_anawyzed_powt_get(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				    boow ingwess);
void mwxsw_sp_span_anawyzed_powt_put(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				     boow ingwess);
int mwxsw_sp_span_agent_bind(stwuct mwxsw_sp *mwxsw_sp,
			     enum mwxsw_sp_span_twiggew twiggew,
			     stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			     const stwuct mwxsw_sp_span_twiggew_pawms *pawms);
void
mwxsw_sp_span_agent_unbind(stwuct mwxsw_sp *mwxsw_sp,
			   enum mwxsw_sp_span_twiggew twiggew,
			   stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			   const stwuct mwxsw_sp_span_twiggew_pawms *pawms);
int mwxsw_sp_span_twiggew_enabwe(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				 enum mwxsw_sp_span_twiggew twiggew, u8 tc);
void mwxsw_sp_span_twiggew_disabwe(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   enum mwxsw_sp_span_twiggew twiggew, u8 tc);
boow mwxsw_sp_span_twiggew_is_ingwess(enum mwxsw_sp_span_twiggew twiggew);

extewn const stwuct mwxsw_sp_span_ops mwxsw_sp1_span_ops;
extewn const stwuct mwxsw_sp_span_ops mwxsw_sp2_span_ops;
extewn const stwuct mwxsw_sp_span_ops mwxsw_sp3_span_ops;

#endif
