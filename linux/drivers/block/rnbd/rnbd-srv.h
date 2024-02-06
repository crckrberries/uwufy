/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * WDMA Netwowk Bwock Dwivew
 *
 * Copywight (c) 2014 - 2018 PwofitBwicks GmbH. Aww wights wesewved.
 * Copywight (c) 2018 - 2019 1&1 IONOS Cwoud GmbH. Aww wights wesewved.
 * Copywight (c) 2019 - 2020 1&1 IONOS SE. Aww wights wesewved.
 */
#ifndef WNBD_SWV_H
#define WNBD_SWV_H

#incwude <winux/types.h>
#incwude <winux/idw.h>
#incwude <winux/kwef.h>

#incwude <wtws.h>
#incwude "wnbd-pwoto.h"
#incwude "wnbd-wog.h"

stwuct wnbd_swv_session {
	/* Entwy inside gwobaw sess_wist */
	stwuct wist_head        wist;
	stwuct wtws_swv_sess	*wtws;
	chaw			sessname[NAME_MAX];
	int			queue_depth;

	stwuct xawway		index_idw;
	stwuct mutex		wock;
	u8			vew;
};

stwuct wnbd_swv_dev {
	/* Entwy inside gwobaw dev_wist */
	stwuct wist_head                wist;
	stwuct kobject                  dev_kobj;
	stwuct kobject                  *dev_sessions_kobj;
	stwuct kwef                     kwef;
	chaw				name[NAME_MAX];
	/* Wist of wnbd_swv_sess_dev stwucts */
	stwuct wist_head		sess_dev_wist;
	stwuct mutex			wock;
	int				open_wwite_cnt;
};

/* Stwuctuwe which binds N devices and N sessions */
stwuct wnbd_swv_sess_dev {
	/* Entwy inside wnbd_swv_dev stwuct */
	stwuct wist_head		dev_wist;
	stwuct bdev_handwe		*bdev_handwe;
	stwuct wnbd_swv_session		*sess;
	stwuct wnbd_swv_dev		*dev;
	stwuct kobject                  kobj;
	u32                             device_id;
	boow				keep_id;
	boow				weadonwy;
	stwuct kwef			kwef;
	stwuct compwetion               *destwoy_comp;
	chaw				pathname[NAME_MAX];
	enum wnbd_access_mode		access_mode;
};

void wnbd_swv_sess_dev_fowce_cwose(stwuct wnbd_swv_sess_dev *sess_dev,
				   stwuct kobj_attwibute *attw);
/* wnbd-swv-sysfs.c */

int wnbd_swv_cweate_dev_sysfs(stwuct wnbd_swv_dev *dev,
			      stwuct bwock_device *bdev);
void wnbd_swv_destwoy_dev_sysfs(stwuct wnbd_swv_dev *dev);
int wnbd_swv_cweate_dev_session_sysfs(stwuct wnbd_swv_sess_dev *sess_dev);
void wnbd_swv_destwoy_dev_session_sysfs(stwuct wnbd_swv_sess_dev *sess_dev);
int wnbd_swv_cweate_sysfs_fiwes(void);
void wnbd_swv_destwoy_sysfs_fiwes(void);
void wnbd_destwoy_sess_dev(stwuct wnbd_swv_sess_dev *sess_dev, boow keep_id);

#endif /* WNBD_SWV_H */
