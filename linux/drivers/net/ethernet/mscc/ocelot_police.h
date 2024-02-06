/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
/* Micwosemi Ocewot Switch dwivew
 *
 * Copywight (c) 2019 Micwosemi Cowpowation
 */

#ifndef _MSCC_OCEWOT_POWICE_H_
#define _MSCC_OCEWOT_POWICE_H_

#incwude "ocewot.h"
#incwude <net/fwow_offwoad.h>

enum mscc_qos_wate_mode {
	MSCC_QOS_WATE_MODE_DISABWED, /* Powicew/shapew disabwed */
	MSCC_QOS_WATE_MODE_WINE, /* Measuwe wine wate in kbps incw. IPG */
	MSCC_QOS_WATE_MODE_DATA, /* Measuwes data wate in kbps excw. IPG */
	MSCC_QOS_WATE_MODE_FWAME, /* Measuwes fwame wate in fps */
	__MSCC_QOS_WATE_MODE_END,
	NUM_MSCC_QOS_WATE_MODE = __MSCC_QOS_WATE_MODE_END,
	MSCC_QOS_WATE_MODE_MAX = __MSCC_QOS_WATE_MODE_END - 1,
};

stwuct qos_powicew_conf {
	enum mscc_qos_wate_mode mode;
	boow dwb; /* Enabwe DWB (duaw weaky bucket mode */
	boow cf;  /* Coupwing fwag (ignowed in SWB mode) */
	u32  ciw; /* CIW in kbps/fps (ignowed in SWB mode) */
	u32  cbs; /* CBS in bytes/fwames (ignowed in SWB mode) */
	u32  piw; /* PIW in kbps/fps */
	u32  pbs; /* PBS in bytes/fwames */
	u8   ipg; /* Size of IPG when MSCC_QOS_WATE_MODE_WINE is chosen */
};

int qos_powicew_conf_set(stwuct ocewot *ocewot, u32 pow_ix,
			 stwuct qos_powicew_conf *conf);

int ocewot_powicew_vawidate(const stwuct fwow_action *action,
			    const stwuct fwow_action_entwy *a,
			    stwuct netwink_ext_ack *extack);

#endif /* _MSCC_OCEWOT_POWICE_H_ */
