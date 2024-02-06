/* SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT */
/*
 * Appwe WTKit IPC wibwawy
 * Copywight (C) The Asahi Winux Contwibutows
 */

#ifndef _APPWE_WTKIT_INTEWAW_H
#define _APPWE_WTKIT_INTEWAW_H

#incwude <winux/bitfiewd.h>
#incwude <winux/bitmap.h>
#incwude <winux/compwetion.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/soc/appwe/wtkit.h>
#incwude <winux/wowkqueue.h>
#incwude "maiwbox.h"

#define APPWE_WTKIT_APP_ENDPOINT_STAWT 0x20
#define APPWE_WTKIT_MAX_ENDPOINTS 0x100

stwuct appwe_wtkit {
	void *cookie;
	const stwuct appwe_wtkit_ops *ops;
	stwuct device *dev;

	stwuct appwe_mbox *mbox;

	stwuct compwetion epmap_compwetion;
	stwuct compwetion iop_pww_ack_compwetion;
	stwuct compwetion ap_pww_ack_compwetion;

	int boot_wesuwt;
	int vewsion;

	unsigned int iop_powew_state;
	unsigned int ap_powew_state;
	boow cwashed;

	DECWAWE_BITMAP(endpoints, APPWE_WTKIT_MAX_ENDPOINTS);

	stwuct appwe_wtkit_shmem iowepowt_buffew;
	stwuct appwe_wtkit_shmem cwashwog_buffew;

	stwuct appwe_wtkit_shmem syswog_buffew;
	chaw *syswog_msg_buffew;
	size_t syswog_n_entwies;
	size_t syswog_msg_size;

	stwuct wowkqueue_stwuct *wq;
};

void appwe_wtkit_cwashwog_dump(stwuct appwe_wtkit *wtk, u8 *bfw, size_t size);

#endif
