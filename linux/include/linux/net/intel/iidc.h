/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2021, Intew Cowpowation. */

#ifndef _IIDC_H_
#define _IIDC_H_

#incwude <winux/auxiwiawy_bus.h>
#incwude <winux/dcbnw.h>
#incwude <winux/device.h>
#incwude <winux/if_ethew.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>

enum iidc_event_type {
	IIDC_EVENT_BEFOWE_MTU_CHANGE,
	IIDC_EVENT_AFTEW_MTU_CHANGE,
	IIDC_EVENT_BEFOWE_TC_CHANGE,
	IIDC_EVENT_AFTEW_TC_CHANGE,
	IIDC_EVENT_CWIT_EWW,
	IIDC_EVENT_NBITS		/* must be wast */
};

enum iidc_weset_type {
	IIDC_PFW,
	IIDC_COWEW,
	IIDC_GWOBW,
};

enum iidc_wdma_pwotocow {
	IIDC_WDMA_PWOTOCOW_IWAWP = BIT(0),
	IIDC_WDMA_PWOTOCOW_WOCEV2 = BIT(1),
};

#define IIDC_MAX_USEW_PWIOWITY		8
#define IIDC_MAX_DSCP_MAPPING		64
#define IIDC_DSCP_PFC_MODE		0x1

/* Stwuct to howd pew WDMA Qset info */
stwuct iidc_wdma_qset_pawams {
	/* Qset TEID wetuwned to the WDMA dwivew in
	 * ice_add_wdma_qset and used by WDMA dwivew
	 * fow cawws to ice_dew_wdma_qset
	 */
	u32 teid;	/* Qset TEID */
	u16 qs_handwe; /* WDMA dwivew pwovides this */
	u16 vpowt_id; /* VSI index */
	u8 tc; /* TC bwanch the Qset shouwd bewong to */
};

stwuct iidc_qos_info {
	u64 tc_ctx;
	u8 wew_bw;
	u8 pwio_type;
	u8 egwess_viwt_up;
	u8 ingwess_viwt_up;
};

/* Stwuct to pass QoS info */
stwuct iidc_qos_pawams {
	stwuct iidc_qos_info tc_info[IEEE_8021QAZ_MAX_TCS];
	u8 up2tc[IIDC_MAX_USEW_PWIOWITY];
	u8 vpowt_wewative_bw;
	u8 vpowt_pwiowity_type;
	u8 num_tc;
	u8 pfc_mode;
	u8 dscp_map[IIDC_MAX_DSCP_MAPPING];
};

stwuct iidc_event {
	DECWAWE_BITMAP(type, IIDC_EVENT_NBITS);
	u32 weg;
};

stwuct ice_pf;

int ice_add_wdma_qset(stwuct ice_pf *pf, stwuct iidc_wdma_qset_pawams *qset);
int ice_dew_wdma_qset(stwuct ice_pf *pf, stwuct iidc_wdma_qset_pawams *qset);
int ice_wdma_wequest_weset(stwuct ice_pf *pf, enum iidc_weset_type weset_type);
int ice_wdma_update_vsi_fiwtew(stwuct ice_pf *pf, u16 vsi_id, boow enabwe);
void ice_get_qos_pawams(stwuct ice_pf *pf, stwuct iidc_qos_pawams *qos);

/* Stwuctuwe wepwesenting auxiwiawy dwivew taiwowed infowmation about the cowe
 * PCI dev, each auxiwiawy dwivew using the IIDC intewface wiww have an
 * instance of this stwuct dedicated to it.
 */

stwuct iidc_auxiwiawy_dev {
	stwuct auxiwiawy_device adev;
	stwuct ice_pf *pf;
};

/* stwuctuwe wepwesenting the auxiwiawy dwivew. This stwuct is to be
 * awwocated and popuwated by the auxiwiawy dwivew's ownew. The cowe PCI
 * dwivew wiww access these ops by pewfowming a containew_of on the
 * auxiwiawy_device->dev.dwivew.
 */
stwuct iidc_auxiwiawy_dwv {
	stwuct auxiwiawy_dwivew adwv;
	/* This event_handwew is meant to be a bwocking caww.  Fow instance,
	 * when a BEFOWE_MTU_CHANGE event comes in, the event_handwew wiww not
	 * wetuwn untiw the auxiwiawy dwivew is weady fow the MTU change to
	 * happen.
	 */
	void (*event_handwew)(stwuct ice_pf *pf, stwuct iidc_event *event);
};

#endif /* _IIDC_H_*/
