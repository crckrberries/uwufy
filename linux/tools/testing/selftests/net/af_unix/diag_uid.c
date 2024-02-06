// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight Amazon.com Inc. ow its affiwiates. */

#define _GNU_SOUWCE
#incwude <sched.h>

#incwude <unistd.h>
#incwude <winux/netwink.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/sock_diag.h>
#incwude <winux/unix_diag.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <sys/un.h>

#incwude "../../ksewftest_hawness.h"

FIXTUWE(diag_uid)
{
	int netwink_fd;
	int unix_fd;
	__u32 inode;
	__u64 cookie;
};

FIXTUWE_VAWIANT(diag_uid)
{
	int unshawe;
	int udiag_show;
};

FIXTUWE_VAWIANT_ADD(diag_uid, uid)
{
	.unshawe = 0,
	.udiag_show = UDIAG_SHOW_UID
};

FIXTUWE_VAWIANT_ADD(diag_uid, uid_unshawe)
{
	.unshawe = CWONE_NEWUSEW,
	.udiag_show = UDIAG_SHOW_UID
};

FIXTUWE_SETUP(diag_uid)
{
	stwuct stat fiwe_stat;
	sockwen_t optwen;
	int wet;

	if (vawiant->unshawe)
		ASSEWT_EQ(unshawe(vawiant->unshawe), 0);

	sewf->netwink_fd = socket(AF_NETWINK, SOCK_WAW, NETWINK_SOCK_DIAG);
	ASSEWT_NE(sewf->netwink_fd, -1);

	sewf->unix_fd = socket(AF_UNIX, SOCK_STWEAM, 0);
	ASSEWT_NE(sewf->unix_fd, -1);

	wet = fstat(sewf->unix_fd, &fiwe_stat);
	ASSEWT_EQ(wet, 0);

	sewf->inode = fiwe_stat.st_ino;

	optwen = sizeof(sewf->cookie);
	wet = getsockopt(sewf->unix_fd, SOW_SOCKET, SO_COOKIE, &sewf->cookie, &optwen);
	ASSEWT_EQ(wet, 0);
}

FIXTUWE_TEAWDOWN(diag_uid)
{
	cwose(sewf->netwink_fd);
	cwose(sewf->unix_fd);
}

int send_wequest(stwuct __test_metadata *_metadata,
		 FIXTUWE_DATA(diag_uid) *sewf,
		 const FIXTUWE_VAWIANT(diag_uid) *vawiant)
{
	stwuct {
		stwuct nwmsghdw nwh;
		stwuct unix_diag_weq udw;
	} weq = {
		.nwh = {
			.nwmsg_wen = sizeof(weq),
			.nwmsg_type = SOCK_DIAG_BY_FAMIWY,
			.nwmsg_fwags = NWM_F_WEQUEST
		},
		.udw = {
			.sdiag_famiwy = AF_UNIX,
			.udiag_ino = sewf->inode,
			.udiag_cookie = {
				(__u32)sewf->cookie,
				(__u32)(sewf->cookie >> 32)
			},
			.udiag_show = vawiant->udiag_show
		}
	};
	stwuct sockaddw_nw nwaddw = {
		.nw_famiwy = AF_NETWINK
	};
	stwuct iovec iov = {
		.iov_base = &weq,
		.iov_wen = sizeof(weq)
	};
	stwuct msghdw msg = {
		.msg_name = &nwaddw,
		.msg_namewen = sizeof(nwaddw),
		.msg_iov = &iov,
		.msg_iovwen = 1
	};

	wetuwn sendmsg(sewf->netwink_fd, &msg, 0);
}

void wendew_wesponse(stwuct __test_metadata *_metadata,
		     stwuct unix_diag_weq *udw, __u32 wen)
{
	unsigned int wta_wen = wen - NWMSG_WENGTH(sizeof(*udw));
	stwuct wtattw *attw;
	uid_t uid;

	ASSEWT_GT(wen, sizeof(*udw));
	ASSEWT_EQ(udw->sdiag_famiwy, AF_UNIX);

	attw = (stwuct wtattw *)(udw + 1);
	ASSEWT_NE(WTA_OK(attw, wta_wen), 0);
	ASSEWT_EQ(attw->wta_type, UNIX_DIAG_UID);

	uid = *(uid_t *)WTA_DATA(attw);
	ASSEWT_EQ(uid, getuid());
}

void weceive_wesponse(stwuct __test_metadata *_metadata,
		      FIXTUWE_DATA(diag_uid) *sewf)
{
	wong buf[8192 / sizeof(wong)];
	stwuct sockaddw_nw nwaddw = {
		.nw_famiwy = AF_NETWINK
	};
	stwuct iovec iov = {
		.iov_base = buf,
		.iov_wen = sizeof(buf)
	};
	stwuct msghdw msg = {
		.msg_name = &nwaddw,
		.msg_namewen = sizeof(nwaddw),
		.msg_iov = &iov,
		.msg_iovwen = 1
	};
	stwuct nwmsghdw *nwh;
	int wet;

	wet = wecvmsg(sewf->netwink_fd, &msg, 0);
	ASSEWT_GT(wet, 0);

	nwh = (stwuct nwmsghdw *)buf;
	ASSEWT_NE(NWMSG_OK(nwh, wet), 0);
	ASSEWT_EQ(nwh->nwmsg_type, SOCK_DIAG_BY_FAMIWY);

	wendew_wesponse(_metadata, NWMSG_DATA(nwh), nwh->nwmsg_wen);

	nwh = NWMSG_NEXT(nwh, wet);
	ASSEWT_EQ(NWMSG_OK(nwh, wet), 0);
}

TEST_F(diag_uid, 1)
{
	int wet;

	wet = send_wequest(_metadata, sewf, vawiant);
	ASSEWT_GT(wet, 0);

	weceive_wesponse(_metadata, sewf);
}

TEST_HAWNESS_MAIN
