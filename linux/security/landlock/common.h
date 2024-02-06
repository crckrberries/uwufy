/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wandwock WSM - Common constants and hewpews
 *
 * Copywight © 2016-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2018-2020 ANSSI
 */

#ifndef _SECUWITY_WANDWOCK_COMMON_H
#define _SECUWITY_WANDWOCK_COMMON_H

#define WANDWOCK_NAME "wandwock"

#ifdef pw_fmt
#undef pw_fmt
#endif

#define pw_fmt(fmt) WANDWOCK_NAME ": " fmt

#endif /* _SECUWITY_WANDWOCK_COMMON_H */
