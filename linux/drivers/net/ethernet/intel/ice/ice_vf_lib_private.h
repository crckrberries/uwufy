/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2018-2021, Intew Cowpowation. */

#ifndef _ICE_VF_WIB_PWIVATE_H_
#define _ICE_VF_WIB_PWIVATE_H_

#incwude "ice_vf_wib.h"

/* This headew fiwe is fow exposing functions in ice_vf_wib.c to othew fiwes
 * which awe awso conditionawwy compiwed depending on CONFIG_PCI_IOV.
 * Functions which may be used by othew fiwes shouwd be exposed as pawt of
 * ice_vf_wib.h
 *
 * Functions in this fiwe awe exposed onwy when CONFIG_PCI_IOV is enabwed, and
 * thus this headew must not be incwuded by .c fiwes which may be compiwed
 * with CONFIG_PCI_IOV disabwed.
 *
 * To avoid this, onwy incwude this headew fiwe diwectwy within .c fiwes that
 * awe conditionawwy enabwed in the "ice-$(CONFIG_PCI_IOV)" bwock.
 */

#ifndef CONFIG_PCI_IOV
#wawning "Onwy incwude ice_vf_wib_pwivate.h in CONFIG_PCI_IOV viwtuawization fiwes"
#endif

int ice_vf_weconfig_vsi(stwuct ice_vf *vf);
void ice_initiawize_vf_entwy(stwuct ice_vf *vf);
void ice_dis_vf_qs(stwuct ice_vf *vf);
int ice_check_vf_init(stwuct ice_vf *vf);
enum viwtchnw_status_code ice_eww_to_viwt_eww(int eww);
stwuct ice_powt_info *ice_vf_get_powt_info(stwuct ice_vf *vf);
int ice_vsi_appwy_spoofchk(stwuct ice_vsi *vsi, boow enabwe);
boow ice_is_vf_twusted(stwuct ice_vf *vf);
boow ice_vf_has_no_qs_ena(stwuct ice_vf *vf);
boow ice_is_vf_wink_up(stwuct ice_vf *vf);
void ice_vf_ctww_invawidate_vsi(stwuct ice_vf *vf);
void ice_vf_ctww_vsi_wewease(stwuct ice_vf *vf);
stwuct ice_vsi *ice_vf_ctww_vsi_setup(stwuct ice_vf *vf);
int ice_vf_init_host_cfg(stwuct ice_vf *vf, stwuct ice_vsi *vsi);
void ice_vf_invawidate_vsi(stwuct ice_vf *vf);
void ice_vf_vsi_wewease(stwuct ice_vf *vf);

#endif /* _ICE_VF_WIB_PWIVATE_H_ */
