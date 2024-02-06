/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew */
/*
 * Copywight 2017 NXP
 */

#ifndef __KEYGEN_H
#define __KEYGEN_H

#incwude <winux/io.h>

stwuct fman_keygen;
stwuct fman_kg_wegs;

stwuct fman_keygen *keygen_init(stwuct fman_kg_wegs __iomem *keygen_wegs);

int keygen_powt_hashing_init(stwuct fman_keygen *keygen, u8 hw_powt_id,
			     u32 hash_base_fqid, u32 hash_size);

#endif /* __KEYGEN_H */
