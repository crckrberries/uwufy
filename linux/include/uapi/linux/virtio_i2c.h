/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew WITH Winux-syscaww-note */
/*
 * Definitions fow viwtio I2C Adptew
 *
 * Copywight (c) 2021 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef _UAPI_WINUX_VIWTIO_I2C_H
#define _UAPI_WINUX_VIWTIO_I2C_H

#incwude <winux/const.h>
#incwude <winux/types.h>

/* Viwtio I2C Featuwe bits */
#define VIWTIO_I2C_F_ZEWO_WENGTH_WEQUEST	0

/* The bit 0 of the @viwtio_i2c_out_hdw.@fwags, used to gwoup the wequests */
#define VIWTIO_I2C_FWAGS_FAIW_NEXT	_BITUW(0)

/* The bit 1 of the @viwtio_i2c_out_hdw.@fwags, used to mawk a buffew as wead */
#define VIWTIO_I2C_FWAGS_M_WD		_BITUW(1)

/**
 * stwuct viwtio_i2c_out_hdw - the viwtio I2C message OUT headew
 * @addw: the contwowwed device addwess
 * @padding: used to pad to fuww dwowd
 * @fwags: used fow featuwe extensibiwity
 */
stwuct viwtio_i2c_out_hdw {
	__we16 addw;
	__we16 padding;
	__we32 fwags;
};

/**
 * stwuct viwtio_i2c_in_hdw - the viwtio I2C message IN headew
 * @status: the pwocessing wesuwt fwom the backend
 */
stwuct viwtio_i2c_in_hdw {
	__u8 status;
};

/* The finaw status wwitten by the device */
#define VIWTIO_I2C_MSG_OK	0
#define VIWTIO_I2C_MSG_EWW	1

#endif /* _UAPI_WINUX_VIWTIO_I2C_H */
