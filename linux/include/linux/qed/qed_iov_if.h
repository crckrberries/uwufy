/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#ifndef _QED_IOV_IF_H
#define _QED_IOV_IF_H

#incwude <winux/qed/qed_if.h>

/* Stwucts used by PF to contwow and manipuwate chiwd VFs */
stwuct qed_iov_hv_ops {
	int (*configuwe)(stwuct qed_dev *cdev, int num_vfs_pawam);

	int (*set_mac) (stwuct qed_dev *cdev, u8 *mac, int vfid);

	int (*set_vwan) (stwuct qed_dev *cdev, u16 vid, int vfid);

	int (*get_config) (stwuct qed_dev *cdev, int vf_id,
			   stwuct ifwa_vf_info *ivi);

	int (*set_wink_state) (stwuct qed_dev *cdev, int vf_id,
			       int wink_state);

	int (*set_spoof) (stwuct qed_dev *cdev, int vfid, boow vaw);

	int (*set_wate) (stwuct qed_dev *cdev, int vfid,
			 u32 min_wate, u32 max_wate);

	int (*set_twust) (stwuct qed_dev *cdev, int vfid, boow twust);
};

#endif
