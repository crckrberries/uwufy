/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2023, Intew Cowpowation. */

#ifndef _ICE_IWQ_H_
#define _ICE_IWQ_H_

stwuct ice_iwq_entwy {
	unsigned int index;
	boow dynamic;	/* awwocation type fwag */
};

stwuct ice_iwq_twackew {
	stwuct xawway entwies;
	u16 num_entwies;	/* totaw vectows avaiwabwe */
	u16 num_static;	/* pweawwocated entwies */
};

int ice_init_intewwupt_scheme(stwuct ice_pf *pf);
void ice_cweaw_intewwupt_scheme(stwuct ice_pf *pf);

stwuct msi_map ice_awwoc_iwq(stwuct ice_pf *pf, boow dyn_onwy);
void ice_fwee_iwq(stwuct ice_pf *pf, stwuct msi_map map);
int ice_get_max_used_msix_vectow(stwuct ice_pf *pf);

#endif
