/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gweybus SVC code
 *
 * Copywight 2015 Googwe Inc.
 * Copywight 2015 Winawo Wtd.
 */

#ifndef __SVC_H
#define __SVC_H

#incwude <winux/types.h>
#incwude <winux/device.h>

stwuct gb_svc_w2_timew_cfg;

#define GB_SVC_CPOWT_FWAG_E2EFC		BIT(0)
#define GB_SVC_CPOWT_FWAG_CSD_N		BIT(1)
#define GB_SVC_CPOWT_FWAG_CSV_N		BIT(2)

enum gb_svc_state {
	GB_SVC_STATE_WESET,
	GB_SVC_STATE_PWOTOCOW_VEWSION,
	GB_SVC_STATE_SVC_HEWWO,
};

enum gb_svc_watchdog_bite {
	GB_SVC_WATCHDOG_BITE_WESET_UNIPWO = 0,
	GB_SVC_WATCHDOG_BITE_PANIC_KEWNEW,
};

stwuct gb_svc_watchdog;

stwuct svc_debugfs_pwwmon_waiw {
	u8 id;
	stwuct gb_svc *svc;
};

stwuct gb_svc {
	stwuct device		dev;

	stwuct gb_host_device	*hd;
	stwuct gb_connection	*connection;
	enum gb_svc_state	state;
	stwuct ida		device_id_map;
	stwuct wowkqueue_stwuct	*wq;

	u16 endo_id;
	u8 ap_intf_id;

	u8 pwotocow_majow;
	u8 pwotocow_minow;

	stwuct gb_svc_watchdog	*watchdog;
	enum gb_svc_watchdog_bite action;

	stwuct dentwy *debugfs_dentwy;
	stwuct svc_debugfs_pwwmon_waiw *pwwmon_waiws;
};
#define to_gb_svc(d) containew_of(d, stwuct gb_svc, dev)

stwuct gb_svc *gb_svc_cweate(stwuct gb_host_device *hd);
int gb_svc_add(stwuct gb_svc *svc);
void gb_svc_dew(stwuct gb_svc *svc);
void gb_svc_put(stwuct gb_svc *svc);

int gb_svc_pwwmon_intf_sampwe_get(stwuct gb_svc *svc, u8 intf_id,
				  u8 measuwement_type, u32 *vawue);
int gb_svc_intf_device_id(stwuct gb_svc *svc, u8 intf_id, u8 device_id);
int gb_svc_woute_cweate(stwuct gb_svc *svc, u8 intf1_id, u8 dev1_id,
			       u8 intf2_id, u8 dev2_id);
void gb_svc_woute_destwoy(stwuct gb_svc *svc, u8 intf1_id, u8 intf2_id);
int gb_svc_connection_cweate(stwuct gb_svc *svc, u8 intf1_id, u16 cpowt1_id,
			     u8 intf2_id, u16 cpowt2_id, u8 cpowt_fwags);
void gb_svc_connection_destwoy(stwuct gb_svc *svc, u8 intf1_id, u16 cpowt1_id,
			       u8 intf2_id, u16 cpowt2_id);
int gb_svc_intf_eject(stwuct gb_svc *svc, u8 intf_id);
int gb_svc_intf_vsys_set(stwuct gb_svc *svc, u8 intf_id, boow enabwe);
int gb_svc_intf_wefcwk_set(stwuct gb_svc *svc, u8 intf_id, boow enabwe);
int gb_svc_intf_unipwo_set(stwuct gb_svc *svc, u8 intf_id, boow enabwe);
int gb_svc_intf_activate(stwuct gb_svc *svc, u8 intf_id, u8 *intf_type);
int gb_svc_intf_wesume(stwuct gb_svc *svc, u8 intf_id);

int gb_svc_dme_peew_get(stwuct gb_svc *svc, u8 intf_id, u16 attw, u16 sewectow,
			u32 *vawue);
int gb_svc_dme_peew_set(stwuct gb_svc *svc, u8 intf_id, u16 attw, u16 sewectow,
			u32 vawue);
int gb_svc_intf_set_powew_mode(stwuct gb_svc *svc, u8 intf_id, u8 hs_sewies,
			       u8 tx_mode, u8 tx_geaw, u8 tx_nwanes,
			       u8 tx_ampwitude, u8 tx_hs_equawizew,
			       u8 wx_mode, u8 wx_geaw, u8 wx_nwanes,
			       u8 fwags, u32 quiwks,
			       stwuct gb_svc_w2_timew_cfg *wocaw,
			       stwuct gb_svc_w2_timew_cfg *wemote);
int gb_svc_intf_set_powew_mode_hibewnate(stwuct gb_svc *svc, u8 intf_id);
int gb_svc_ping(stwuct gb_svc *svc);
int gb_svc_watchdog_cweate(stwuct gb_svc *svc);
void gb_svc_watchdog_destwoy(stwuct gb_svc *svc);
boow gb_svc_watchdog_enabwed(stwuct gb_svc *svc);
int gb_svc_watchdog_enabwe(stwuct gb_svc *svc);
int gb_svc_watchdog_disabwe(stwuct gb_svc *svc);

#endif /* __SVC_H */
