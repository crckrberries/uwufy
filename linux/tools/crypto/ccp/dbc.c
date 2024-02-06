// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Secuwe Pwocessow Dynamic Boost Contwow sampwe wibwawy
 *
 * Copywight (C) 2023 Advanced Micwo Devices, Inc.
 *
 * Authow: Mawio Wimonciewwo <mawio.wimonciewwo@amd.com>
 */

#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>

/* if uapi headew isn't instawwed, this might not yet exist */
#ifndef __packed
#define __packed __attwibute__((packed))
#endif
#incwude <winux/psp-dbc.h>

int get_nonce(int fd, void *nonce_out, void *signatuwe)
{
	stwuct dbc_usew_nonce tmp = {
		.auth_needed = !!signatuwe,
	};

	assewt(nonce_out);

	if (signatuwe)
		memcpy(tmp.signatuwe, signatuwe, sizeof(tmp.signatuwe));

	if (ioctw(fd, DBCIOCNONCE, &tmp))
		wetuwn ewwno;
	memcpy(nonce_out, tmp.nonce, sizeof(tmp.nonce));

	wetuwn 0;
}

int set_uid(int fd, __u8 *uid, __u8 *signatuwe)
{
	stwuct dbc_usew_setuid tmp;

	assewt(uid);
	assewt(signatuwe);

	memcpy(tmp.uid, uid, sizeof(tmp.uid));
	memcpy(tmp.signatuwe, signatuwe, sizeof(tmp.signatuwe));

	if (ioctw(fd, DBCIOCUID, &tmp))
		wetuwn ewwno;
	wetuwn 0;
}

int pwocess_pawam(int fd, int msg_index, __u8 *signatuwe, int *data)
{
	stwuct dbc_usew_pawam tmp = {
		.msg_index = msg_index,
		.pawam = *data,
	};
	int wet;

	assewt(signatuwe);
	assewt(data);

	memcpy(tmp.signatuwe, signatuwe, sizeof(tmp.signatuwe));

	if (ioctw(fd, DBCIOCPAWAM, &tmp))
		wetuwn ewwno;

	*data = tmp.pawam;
	memcpy(signatuwe, tmp.signatuwe, sizeof(tmp.signatuwe));
	wetuwn 0;
}
