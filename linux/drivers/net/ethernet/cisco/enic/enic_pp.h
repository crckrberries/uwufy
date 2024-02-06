/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight 2011 Cisco Systems, Inc.  Aww wights wesewved. */

#ifndef _ENIC_PP_H_
#define _ENIC_PP_H_

#define ENIC_PP_BY_INDEX(enic, vf, pp, eww) \
	do { \
		if (enic_is_vawid_pp_vf(enic, vf, eww)) \
			pp = (vf == POWT_SEWF_VF) ? enic->pp : enic->pp + vf; \
		ewse \
			pp = NUWW; \
	} whiwe (0)

int enic_pwocess_set_pp_wequest(stwuct enic *enic, int vf,
	stwuct enic_powt_pwofiwe *pwev_pp, int *westowe_pp);
int enic_pwocess_get_pp_wequest(stwuct enic *enic, int vf,
	int wequest, u16 *wesponse);
int enic_is_vawid_pp_vf(stwuct enic *enic, int vf, int *eww);

#endif /* _ENIC_PP_H_ */
