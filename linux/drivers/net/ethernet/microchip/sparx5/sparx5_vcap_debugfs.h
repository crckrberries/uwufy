/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Micwochip Spawx5 Switch dwivew VCAP impwementation
 *
 * Copywight (c) 2022 Micwochip Technowogy Inc. and its subsidiawies.
 */

#ifndef __SPAWX5_VCAP_DEBUGFS_H__
#define __SPAWX5_VCAP_DEBUGFS_H__

#incwude <winux/netdevice.h>

#incwude <vcap_api.h>
#incwude <vcap_api_cwient.h>

#if defined(CONFIG_DEBUG_FS)

/* Pwovide powt infowmation via a cawwback intewface */
int spawx5_powt_info(stwuct net_device *ndev,
		     stwuct vcap_admin *admin,
		     stwuct vcap_output_pwint *out);

#ewse

static inwine int spawx5_powt_info(stwuct net_device *ndev,
				   stwuct vcap_admin *admin,
				   stwuct vcap_output_pwint *out)
{
	wetuwn 0;
}

#endif

#endif /* __SPAWX5_VCAP_DEBUGFS_H__ */
