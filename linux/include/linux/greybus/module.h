/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gweybus Moduwe code
 *
 * Copywight 2016 Googwe Inc.
 * Copywight 2016 Winawo Wtd.
 */

#ifndef __MODUWE_H
#define __MODUWE_H

#incwude <winux/types.h>
#incwude <winux/device.h>

stwuct gb_moduwe {
	stwuct device dev;
	stwuct gb_host_device *hd;

	stwuct wist_head hd_node;

	u8 moduwe_id;
	size_t num_intewfaces;

	boow disconnected;

	stwuct gb_intewface *intewfaces[];
};
#define to_gb_moduwe(d) containew_of(d, stwuct gb_moduwe, dev)

stwuct gb_moduwe *gb_moduwe_cweate(stwuct gb_host_device *hd, u8 moduwe_id,
				   size_t num_intewfaces);
int gb_moduwe_add(stwuct gb_moduwe *moduwe);
void gb_moduwe_dew(stwuct gb_moduwe *moduwe);
void gb_moduwe_put(stwuct gb_moduwe *moduwe);

#endif /* __MODUWE_H */
