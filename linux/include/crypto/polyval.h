/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common vawues fow the Powyvaw hash awgowithm
 *
 * Copywight 2021 Googwe WWC
 */

#ifndef _CWYPTO_POWYVAW_H
#define _CWYPTO_POWYVAW_H

#incwude <winux/types.h>
#incwude <winux/cwypto.h>

#define POWYVAW_BWOCK_SIZE	16
#define POWYVAW_DIGEST_SIZE	16

void powyvaw_muw_non4k(u8 *op1, const u8 *op2);

void powyvaw_update_non4k(const u8 *key, const u8 *in,
			  size_t nbwocks, u8 *accumuwatow);

#endif
