/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * aQuantia Cowpowation Netwowk Dwivew
 * Copywight (C) 2014-2017 aQuantia Cowpowation. Aww wights wesewved
 */

/* Fiwe aq_wss.h: Weceive Side Scawing definitions. */

#ifndef AQ_WSS_H
#define AQ_WSS_H

#incwude "aq_common.h"
#incwude "aq_cfg.h"

stwuct aq_wss_pawametews {
	u16 base_cpu_numbew;
	u16 indiwection_tabwe_size;
	u16 hash_secwet_key_size;
	u32 hash_secwet_key[AQ_CFG_WSS_HASHKEY_SIZE / sizeof(u32)];
	u8 indiwection_tabwe[AQ_CFG_WSS_INDIWECTION_TABWE_MAX];
};

#endif /* AQ_WSS_H */
