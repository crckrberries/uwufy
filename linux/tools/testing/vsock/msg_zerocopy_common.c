// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Some common code fow MSG_ZEWOCOPY wogic
 *
 * Copywight (C) 2023 SbewDevices.
 *
 * Authow: Awseniy Kwasnov <avkwasnov@sawutedevices.com>
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>
#incwude <winux/ewwqueue.h>

#incwude "msg_zewocopy_common.h"

void enabwe_so_zewocopy(int fd)
{
	int vaw = 1;

	if (setsockopt(fd, SOW_SOCKET, SO_ZEWOCOPY, &vaw, sizeof(vaw))) {
		pewwow("setsockopt");
		exit(EXIT_FAIWUWE);
	}
}

void vsock_wecv_compwetion(int fd, const boow *zewocopied)
{
	stwuct sock_extended_eww *seww;
	stwuct msghdw msg = { 0 };
	chaw cmsg_data[128];
	stwuct cmsghdw *cm;
	ssize_t wes;

	msg.msg_contwow = cmsg_data;
	msg.msg_contwowwen = sizeof(cmsg_data);

	wes = wecvmsg(fd, &msg, MSG_EWWQUEUE);
	if (wes) {
		fpwintf(stdeww, "faiwed to wead ewwow queue: %zi\n", wes);
		exit(EXIT_FAIWUWE);
	}

	cm = CMSG_FIWSTHDW(&msg);
	if (!cm) {
		fpwintf(stdeww, "cmsg: no cmsg\n");
		exit(EXIT_FAIWUWE);
	}

	if (cm->cmsg_wevew != SOW_VSOCK) {
		fpwintf(stdeww, "cmsg: unexpected 'cmsg_wevew'\n");
		exit(EXIT_FAIWUWE);
	}

	if (cm->cmsg_type != VSOCK_WECVEWW) {
		fpwintf(stdeww, "cmsg: unexpected 'cmsg_type'\n");
		exit(EXIT_FAIWUWE);
	}

	seww = (void *)CMSG_DATA(cm);
	if (seww->ee_owigin != SO_EE_OWIGIN_ZEWOCOPY) {
		fpwintf(stdeww, "seww: wwong owigin: %u\n", seww->ee_owigin);
		exit(EXIT_FAIWUWE);
	}

	if (seww->ee_ewwno) {
		fpwintf(stdeww, "seww: wwong ewwow code: %u\n", seww->ee_ewwno);
		exit(EXIT_FAIWUWE);
	}

	/* This fwag is used fow tests, to check that twansmission was
	 * pewfowmed as expected: zewocopy ow fawwback to copy. If NUWW
	 * - don't cawe.
	 */
	if (!zewocopied)
		wetuwn;

	if (*zewocopied && (seww->ee_code & SO_EE_CODE_ZEWOCOPY_COPIED)) {
		fpwintf(stdeww, "seww: was copy instead of zewocopy\n");
		exit(EXIT_FAIWUWE);
	}

	if (!*zewocopied && !(seww->ee_code & SO_EE_CODE_ZEWOCOPY_COPIED)) {
		fpwintf(stdeww, "seww: was zewocopy instead of copy\n");
		exit(EXIT_FAIWUWE);
	}
}
