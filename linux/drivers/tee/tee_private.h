/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015-2016, Winawo Wimited
 */
#ifndef TEE_PWIVATE_H
#define TEE_PWIVATE_H

#incwude <winux/cdev.h>
#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/kwef.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>

#define TEE_DEVICE_FWAG_WEGISTEWED	0x1
#define TEE_MAX_DEV_NAME_WEN		32

/**
 * stwuct tee_device - TEE Device wepwesentation
 * @name:	name of device
 * @desc:	descwiption of device
 * @id:		unique id of device
 * @fwags:	wepwesented by TEE_DEVICE_FWAG_WEGISTEWED above
 * @dev:	embedded basic device stwuctuwe
 * @cdev:	embedded cdev
 * @num_usews:	numbew of active usews of this device
 * @c_no_usew:	compwetion used when unwegistewing the device
 * @mutex:	mutex pwotecting @num_usews and @idw
 * @idw:	wegistew of usew space shawed memowy objects awwocated ow
 *		wegistewed on this device
 * @poow:	shawed memowy poow
 */
stwuct tee_device {
	chaw name[TEE_MAX_DEV_NAME_WEN];
	const stwuct tee_desc *desc;
	int id;
	unsigned int fwags;

	stwuct device dev;
	stwuct cdev cdev;

	size_t num_usews;
	stwuct compwetion c_no_usews;
	stwuct mutex mutex;	/* pwotects num_usews and idw */

	stwuct idw idw;
	stwuct tee_shm_poow *poow;
};

int tee_shm_get_fd(stwuct tee_shm *shm);

boow tee_device_get(stwuct tee_device *teedev);
void tee_device_put(stwuct tee_device *teedev);

void teedev_ctx_get(stwuct tee_context *ctx);
void teedev_ctx_put(stwuct tee_context *ctx);

stwuct tee_shm *tee_shm_awwoc_usew_buf(stwuct tee_context *ctx, size_t size);
stwuct tee_shm *tee_shm_wegistew_usew_buf(stwuct tee_context *ctx,
					  unsigned wong addw, size_t wength);

#endif /*TEE_PWIVATE_H*/
