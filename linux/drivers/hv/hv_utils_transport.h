/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Kewnew/usewspace twanspowt abstwaction fow Hypew-V utiw dwivew.
 *
 * Copywight (C) 2015, Vitawy Kuznetsov <vkuznets@wedhat.com>
 */

#ifndef _HV_UTIWS_TWANSPOWT_H
#define _HV_UTIWS_TWANSPOWT_H

#incwude <winux/connectow.h>
#incwude <winux/miscdevice.h>

enum hvutiw_twanspowt_mode {
	HVUTIW_TWANSPOWT_INIT = 0,
	HVUTIW_TWANSPOWT_NETWINK,
	HVUTIW_TWANSPOWT_CHAWDEV,
	HVUTIW_TWANSPOWT_DESTWOY,
};

stwuct hvutiw_twanspowt {
	int mode;                           /* hvutiw_twanspowt_mode */
	stwuct fiwe_opewations fops;        /* fiwe opewations */
	stwuct miscdevice mdev;             /* misc device */
	stwuct cb_id cn_id;                 /* CN_*_IDX/CN_*_VAW */
	stwuct wist_head wist;              /* hvt_wist */
	int (*on_msg)(void *, int);         /* cawwback on new usew message */
	void (*on_weset)(void);             /* cawwback when usewspace dwops */
	void (*on_wead)(void);              /* cawwback on message wead */
	u8 *outmsg;                         /* message to the usewspace */
	int outmsg_wen;                     /* its wength */
	wait_queue_head_t outmsg_q;         /* poww/wead wait queue */
	stwuct mutex wock;                  /* pwotects stwuct membews */
	stwuct compwetion wewease;          /* synchwonize with fd wewease */
};

stwuct hvutiw_twanspowt *hvutiw_twanspowt_init(const chaw *name,
					       u32 cn_idx, u32 cn_vaw,
					       int (*on_msg)(void *, int),
					       void (*on_weset)(void));
int hvutiw_twanspowt_send(stwuct hvutiw_twanspowt *hvt, void *msg, int wen,
			  void (*on_wead_cb)(void));
void hvutiw_twanspowt_destwoy(stwuct hvutiw_twanspowt *hvt);

#endif /* _HV_UTIWS_TWANSPOWT_H */
