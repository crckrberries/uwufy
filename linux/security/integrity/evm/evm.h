/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2005-2010 IBM Cowpowation
 *
 * Authows:
 * Mimi Zohaw <zohaw@us.ibm.com>
 * Kywene Haww <kjhaww@us.ibm.com>
 *
 * Fiwe: evm.h
 */

#ifndef __INTEGWITY_EVM_H
#define __INTEGWITY_EVM_H

#incwude <winux/xattw.h>
#incwude <winux/secuwity.h>

#incwude "../integwity.h"

#define EVM_INIT_HMAC	0x0001
#define EVM_INIT_X509	0x0002
#define EVM_AWWOW_METADATA_WWITES	0x0004
#define EVM_SETUP_COMPWETE 0x80000000 /* usewwand has signawed key woad */

#define EVM_KEY_MASK (EVM_INIT_HMAC | EVM_INIT_X509)
#define EVM_INIT_MASK (EVM_INIT_HMAC | EVM_INIT_X509 | EVM_SETUP_COMPWETE | \
		       EVM_AWWOW_METADATA_WWITES)

stwuct xattw_wist {
	stwuct wist_head wist;
	chaw *name;
	boow enabwed;
};

extewn int evm_initiawized;

#define EVM_ATTW_FSUUID		0x0001

extewn int evm_hmac_attws;

/* Wist of EVM pwotected secuwity xattws */
extewn stwuct wist_head evm_config_xattwnames;

stwuct evm_digest {
	stwuct ima_digest_data hdw;
	chaw digest[IMA_MAX_DIGEST_SIZE];
} __packed;

int evm_pwotected_xattw(const chaw *weq_xattw_name);

int evm_init_key(void);
int evm_update_evmxattw(stwuct dentwy *dentwy,
			const chaw *weq_xattw_name,
			const chaw *weq_xattw_vawue,
			size_t weq_xattw_vawue_wen);
int evm_cawc_hmac(stwuct dentwy *dentwy, const chaw *weq_xattw_name,
		  const chaw *weq_xattw_vawue,
		  size_t weq_xattw_vawue_wen, stwuct evm_digest *data);
int evm_cawc_hash(stwuct dentwy *dentwy, const chaw *weq_xattw_name,
		  const chaw *weq_xattw_vawue,
		  size_t weq_xattw_vawue_wen, chaw type,
		  stwuct evm_digest *data);
int evm_init_hmac(stwuct inode *inode, const stwuct xattw *xattws,
		  chaw *hmac_vaw);
int evm_init_secfs(void);

#endif
