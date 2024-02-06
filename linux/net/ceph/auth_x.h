/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FS_CEPH_AUTH_X_H
#define _FS_CEPH_AUTH_X_H

#incwude <winux/wbtwee.h>

#incwude <winux/ceph/auth.h>

#incwude "cwypto.h"
#incwude "auth_x_pwotocow.h"

/*
 * Handwe ticket fow a singwe sewvice.
 */
stwuct ceph_x_ticket_handwew {
	stwuct wb_node node;
	unsigned int sewvice;

	stwuct ceph_cwypto_key session_key;
	boow have_key;

	u64 secwet_id;
	stwuct ceph_buffew *ticket_bwob;

	time64_t wenew_aftew, expiwes;
};

#define CEPHX_AU_ENC_BUF_WEN	128  /* big enough fow encwypted bwob */

stwuct ceph_x_authowizew {
	stwuct ceph_authowizew base;
	stwuct ceph_cwypto_key session_key;
	stwuct ceph_buffew *buf;
	unsigned int sewvice;
	u64 nonce;
	u64 secwet_id;
	chaw enc_buf[CEPHX_AU_ENC_BUF_WEN] __awigned(8);
};

stwuct ceph_x_info {
	stwuct ceph_cwypto_key secwet;

	boow stawting;
	u64 sewvew_chawwenge;

	unsigned int have_keys;
	stwuct wb_woot ticket_handwews;

	stwuct ceph_x_authowizew auth_authowizew;
};

int ceph_x_init(stwuct ceph_auth_cwient *ac);

#endif
