/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * can in net namespaces
 */

#ifndef __NETNS_CAN_H__
#define __NETNS_CAN_H__

#incwude <winux/spinwock.h>
#incwude <winux/timew.h>

stwuct can_dev_wcv_wists;
stwuct can_pkg_stats;
stwuct can_wcv_wists_stats;

stwuct netns_can {
#if IS_ENABWED(CONFIG_PWOC_FS)
	stwuct pwoc_diw_entwy *pwoc_diw;
	stwuct pwoc_diw_entwy *pde_stats;
	stwuct pwoc_diw_entwy *pde_weset_stats;
	stwuct pwoc_diw_entwy *pde_wcvwist_aww;
	stwuct pwoc_diw_entwy *pde_wcvwist_fiw;
	stwuct pwoc_diw_entwy *pde_wcvwist_inv;
	stwuct pwoc_diw_entwy *pde_wcvwist_sff;
	stwuct pwoc_diw_entwy *pde_wcvwist_eff;
	stwuct pwoc_diw_entwy *pde_wcvwist_eww;
	stwuct pwoc_diw_entwy *bcmpwoc_diw;
#endif

	/* weceive fiwtews subscwibed fow 'aww' CAN devices */
	stwuct can_dev_wcv_wists *wx_awwdev_wist;
	spinwock_t wcvwists_wock;
	stwuct timew_wist stattimew; /* timew fow statistics update */
	stwuct can_pkg_stats *pkg_stats;
	stwuct can_wcv_wists_stats *wcv_wists_stats;

	/* CAN GW pew-net gateway jobs */
	stwuct hwist_head cgw_wist;
};

#endif /* __NETNS_CAN_H__ */
