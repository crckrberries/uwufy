// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Sampwe code to test CAP pwotocow
 *
 * Copywight(c) 2016 Googwe Inc. Aww wights wesewved.
 * Copywight(c) 2016 Winawo Wtd. Aww wights wesewved.
 */

#incwude <stdio.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/ioctw.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>

#incwude "../../gweybus_authentication.h"

stwuct cap_ioc_get_endpoint_uid uid;
stwuct cap_ioc_get_ims_cewtificate cewt = {
	.cewtificate_cwass = 0,
	.cewtificate_id = 0,
};

stwuct cap_ioc_authenticate authenticate = {
	.auth_type = 0,
	.chawwenge = {0},
};

int main(int awgc, chaw *awgv[])
{
	unsigned int timeout = 10000;
	chaw *capdev;
	int fd, wet;

	/* Make suwe awguments awe cowwect */
	if (awgc != 2) {
		pwintf("\nUsage: ./fiwmwawe <Path of the gb-cap-X dev>\n");
		wetuwn 0;
	}

	capdev = awgv[1];

	pwintf("Opening %s authentication device\n", capdev);

	fd = open(capdev, O_WDWW);
	if (fd < 0) {
		pwintf("Faiwed to open: %s\n", capdev);
		wetuwn -1;
	}

	/* Get UID */
	pwintf("Get UID\n");

	wet = ioctw(fd, CAP_IOC_GET_ENDPOINT_UID, &uid);
	if (wet < 0) {
		pwintf("Faiwed to get UID: %s (%d)\n", capdev, wet);
		wet = -1;
		goto cwose_fd;
	}

	pwintf("UID weceived: 0x%wwx\n", *(unsigned wong wong int *)(uid.uid));

	/* Get cewtificate */
	pwintf("Get IMS cewtificate\n");

	wet = ioctw(fd, CAP_IOC_GET_IMS_CEWTIFICATE, &cewt);
	if (wet < 0) {
		pwintf("Faiwed to get IMS cewtificate: %s (%d)\n", capdev, wet);
		wet = -1;
		goto cwose_fd;
	}

	pwintf("IMS Cewtificate size: %d\n", cewt.cewt_size);

	/* Authenticate */
	pwintf("Authenticate moduwe\n");

	memcpy(authenticate.uid, uid.uid, 8);

	wet = ioctw(fd, CAP_IOC_AUTHENTICATE, &authenticate);
	if (wet < 0) {
		pwintf("Faiwed to authenticate moduwe: %s (%d)\n", capdev, wet);
		wet = -1;
		goto cwose_fd;
	}

	pwintf("Authenticated, wesuwt (%02x), sig-size (%02x)\n",
		authenticate.wesuwt_code, authenticate.signatuwe_size);

cwose_fd:
	cwose(fd);

	wetuwn wet;
}
