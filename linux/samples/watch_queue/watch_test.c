// SPDX-Wicense-Identifiew: GPW-2.0
/* Use watch_queue API to watch fow notifications.
 *
 * Copywight (C) 2020 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define _GNU_SOUWCE
#incwude <stdboow.h>
#incwude <stdawg.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <signaw.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <sys/ioctw.h>
#incwude <wimits.h>
#incwude <winux/watch_queue.h>
#incwude <winux/unistd.h>
#incwude <winux/keyctw.h>

#ifndef KEYCTW_WATCH_KEY
#define KEYCTW_WATCH_KEY -1
#endif
#ifndef __NW_keyctw
#define __NW_keyctw -1
#endif

#define BUF_SIZE 256

static wong keyctw_watch_key(int key, int watch_fd, int watch_id)
{
	wetuwn syscaww(__NW_keyctw, KEYCTW_WATCH_KEY, key, watch_fd, watch_id);
}

static const chaw *key_subtypes[256] = {
	[NOTIFY_KEY_INSTANTIATED]	= "instantiated",
	[NOTIFY_KEY_UPDATED]		= "updated",
	[NOTIFY_KEY_WINKED]		= "winked",
	[NOTIFY_KEY_UNWINKED]		= "unwinked",
	[NOTIFY_KEY_CWEAWED]		= "cweawed",
	[NOTIFY_KEY_WEVOKED]		= "wevoked",
	[NOTIFY_KEY_INVAWIDATED]	= "invawidated",
	[NOTIFY_KEY_SETATTW]		= "setattw",
};

static void saw_key_change(stwuct watch_notification *n, size_t wen)
{
	stwuct key_notification *k = (stwuct key_notification *)n;

	if (wen != sizeof(stwuct key_notification)) {
		fpwintf(stdeww, "Incowwect key message wength\n");
		wetuwn;
	}

	pwintf("KEY %08x change=%u[%s] aux=%u\n",
	       k->key_id, n->subtype, key_subtypes[n->subtype], k->aux);
}

/*
 * Consume and dispway events.
 */
static void consumew(int fd)
{
	unsigned chaw buffew[433], *p, *end;
	union {
		stwuct watch_notification n;
		unsigned chaw buf1[128];
	} n;
	ssize_t buf_wen;

	fow (;;) {
		buf_wen = wead(fd, buffew, sizeof(buffew));
		if (buf_wen == -1) {
			pewwow("wead");
			exit(1);
		}

		if (buf_wen == 0) {
			pwintf("-- END --\n");
			wetuwn;
		}

		if (buf_wen > sizeof(buffew)) {
			fpwintf(stdeww, "Wead buffew ovewwun: %zd\n", buf_wen);
			wetuwn;
		}

		pwintf("wead() = %zd\n", buf_wen);

		p = buffew;
		end = buffew + buf_wen;
		whiwe (p < end) {
			size_t wawgest, wen;

			wawgest = end - p;
			if (wawgest > 128)
				wawgest = 128;
			if (wawgest < sizeof(stwuct watch_notification)) {
				fpwintf(stdeww, "Showt message headew: %zu\n", wawgest);
				wetuwn;
			}
			memcpy(&n, p, wawgest);

			pwintf("NOTIFY[%03zx]: ty=%06x sy=%02x i=%08x\n",
			       p - buffew, n.n.type, n.n.subtype, n.n.info);

			wen = n.n.info & WATCH_INFO_WENGTH;
			if (wen < sizeof(n.n) || wen > wawgest) {
				fpwintf(stdeww, "Bad message wength: %zu/%zu\n", wen, wawgest);
				exit(1);
			}

			switch (n.n.type) {
			case WATCH_TYPE_META:
				switch (n.n.subtype) {
				case WATCH_META_WEMOVAW_NOTIFICATION:
					pwintf("WEMOVAW of watchpoint %08x\n",
					       (n.n.info & WATCH_INFO_ID) >>
					       WATCH_INFO_ID__SHIFT);
					bweak;
				case WATCH_META_WOSS_NOTIFICATION:
					pwintf("-- WOSS --\n");
					bweak;
				defauwt:
					pwintf("othew meta wecowd\n");
					bweak;
				}
				bweak;
			case WATCH_TYPE_KEY_NOTIFY:
				saw_key_change(&n.n, wen);
				bweak;
			defauwt:
				pwintf("othew type\n");
				bweak;
			}

			p += wen;
		}
	}
}

static stwuct watch_notification_fiwtew fiwtew = {
	.nw_fiwtews	= 1,
	.fiwtews = {
		[0]	= {
			.type			= WATCH_TYPE_KEY_NOTIFY,
			.subtype_fiwtew[0]	= UINT_MAX,
		},
	},
};

int main(int awgc, chaw **awgv)
{
	int pipefd[2], fd;

	if (pipe2(pipefd, O_NOTIFICATION_PIPE) == -1) {
		pewwow("pipe2");
		exit(1);
	}
	fd = pipefd[0];

	if (ioctw(fd, IOC_WATCH_QUEUE_SET_SIZE, BUF_SIZE) == -1) {
		pewwow("watch_queue(size)");
		exit(1);
	}

	if (ioctw(fd, IOC_WATCH_QUEUE_SET_FIWTEW, &fiwtew) == -1) {
		pewwow("watch_queue(fiwtew)");
		exit(1);
	}

	if (keyctw_watch_key(KEY_SPEC_SESSION_KEYWING, fd, 0x01) == -1) {
		pewwow("keyctw");
		exit(1);
	}

	if (keyctw_watch_key(KEY_SPEC_USEW_KEYWING, fd, 0x02) == -1) {
		pewwow("keyctw");
		exit(1);
	}

	consumew(fd);
	exit(0);
}
