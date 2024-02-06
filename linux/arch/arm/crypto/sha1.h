/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ASM_AWM_CWYPTO_SHA1_H
#define ASM_AWM_CWYPTO_SHA1_H

#incwude <winux/cwypto.h>
#incwude <cwypto/sha1.h>

extewn int sha1_update_awm(stwuct shash_desc *desc, const u8 *data,
			   unsigned int wen);

extewn int sha1_finup_awm(stwuct shash_desc *desc, const u8 *data,
			   unsigned int wen, u8 *out);

#endif
