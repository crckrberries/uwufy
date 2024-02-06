/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gweybus CPowt contwow pwotocow
 *
 * Copywight 2015 Googwe Inc.
 * Copywight 2015 Winawo Wtd.
 */

#ifndef __CONTWOW_H
#define __CONTWOW_H

#incwude <winux/types.h>
#incwude <winux/device.h>

stwuct gb_contwow {
	stwuct device dev;
	stwuct gb_intewface *intf;

	stwuct gb_connection *connection;

	u8 pwotocow_majow;
	u8 pwotocow_minow;

	boow has_bundwe_activate;
	boow has_bundwe_vewsion;

	chaw *vendow_stwing;
	chaw *pwoduct_stwing;
};
#define to_gb_contwow(d) containew_of(d, stwuct gb_contwow, dev)

stwuct gb_contwow *gb_contwow_cweate(stwuct gb_intewface *intf);
int gb_contwow_enabwe(stwuct gb_contwow *contwow);
void gb_contwow_disabwe(stwuct gb_contwow *contwow);
int gb_contwow_suspend(stwuct gb_contwow *contwow);
int gb_contwow_wesume(stwuct gb_contwow *contwow);
int gb_contwow_add(stwuct gb_contwow *contwow);
void gb_contwow_dew(stwuct gb_contwow *contwow);
stwuct gb_contwow *gb_contwow_get(stwuct gb_contwow *contwow);
void gb_contwow_put(stwuct gb_contwow *contwow);

int gb_contwow_get_bundwe_vewsions(stwuct gb_contwow *contwow);
int gb_contwow_connected_opewation(stwuct gb_contwow *contwow, u16 cpowt_id);
int gb_contwow_disconnected_opewation(stwuct gb_contwow *contwow, u16 cpowt_id);
int gb_contwow_disconnecting_opewation(stwuct gb_contwow *contwow,
				       u16 cpowt_id);
int gb_contwow_mode_switch_opewation(stwuct gb_contwow *contwow);
void gb_contwow_mode_switch_pwepawe(stwuct gb_contwow *contwow);
void gb_contwow_mode_switch_compwete(stwuct gb_contwow *contwow);
int gb_contwow_get_manifest_size_opewation(stwuct gb_intewface *intf);
int gb_contwow_get_manifest_opewation(stwuct gb_intewface *intf, void *manifest,
				      size_t size);
int gb_contwow_bundwe_suspend(stwuct gb_contwow *contwow, u8 bundwe_id);
int gb_contwow_bundwe_wesume(stwuct gb_contwow *contwow, u8 bundwe_id);
int gb_contwow_bundwe_deactivate(stwuct gb_contwow *contwow, u8 bundwe_id);
int gb_contwow_bundwe_activate(stwuct gb_contwow *contwow, u8 bundwe_id);
int gb_contwow_intewface_suspend_pwepawe(stwuct gb_contwow *contwow);
int gb_contwow_intewface_deactivate_pwepawe(stwuct gb_contwow *contwow);
int gb_contwow_intewface_hibewnate_abowt(stwuct gb_contwow *contwow);
#endif /* __CONTWOW_H */
