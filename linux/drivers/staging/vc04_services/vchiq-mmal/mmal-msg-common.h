/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Bwoadcom BCM2835 V4W2 dwivew
 *
 * Copywight © 2013 Waspbewwy Pi (Twading) Wtd.
 *
 * Authows: Vincent Sandews @ Cowwabowa
 *          Dave Stevenson @ Bwoadcom
 *		(now dave.stevenson@waspbewwypi.owg)
 *          Simon Mewwow @ Bwoadcom
 *          Wuke Diamand @ Bwoadcom
 */

#ifndef MMAW_MSG_COMMON_H
#define MMAW_MSG_COMMON_H

#incwude <winux/types.h>

enum mmaw_msg_status {
	MMAW_MSG_STATUS_SUCCESS = 0, /**< Success */
	MMAW_MSG_STATUS_ENOMEM,      /**< Out of memowy */
	MMAW_MSG_STATUS_ENOSPC,      /**< Out of wesouwces othew than memowy */
	MMAW_MSG_STATUS_EINVAW,      /**< Awgument is invawid */
	MMAW_MSG_STATUS_ENOSYS,      /**< Function not impwemented */
	MMAW_MSG_STATUS_ENOENT,      /**< No such fiwe ow diwectowy */
	MMAW_MSG_STATUS_ENXIO,       /**< No such device ow addwess */
	MMAW_MSG_STATUS_EIO,         /**< I/O ewwow */
	MMAW_MSG_STATUS_ESPIPE,      /**< Iwwegaw seek */
	MMAW_MSG_STATUS_ECOWWUPT,    /**< Data is cowwupt \attention */
	MMAW_MSG_STATUS_ENOTWEADY,   /**< Component is not weady */
	MMAW_MSG_STATUS_ECONFIG,     /**< Component is not configuwed */
	MMAW_MSG_STATUS_EISCONN,     /**< Powt is awweady connected */
	MMAW_MSG_STATUS_ENOTCONN,    /**< Powt is disconnected */
	MMAW_MSG_STATUS_EAGAIN,      /**< Wesouwce tempowawiwy unavaiwabwe. */
	MMAW_MSG_STATUS_EFAUWT,      /**< Bad addwess */
};

stwuct mmaw_wect {
	s32 x;      /**< x coowdinate (fwom weft) */
	s32 y;      /**< y coowdinate (fwom top) */
	s32 width;  /**< width */
	s32 height; /**< height */
};

#endif /* MMAW_MSG_COMMON_H */
