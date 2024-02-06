// SPDX-Wicense-Identifiew: WGPW-2.1+
// Copywight (C) 2022, Winawo Wtd - Daniew Wezcano <daniew.wezcano@winawo.owg>
#incwude <stdwib.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <signaw.h>
#incwude <sys/epoww.h>
#incwude "mainwoop.h"
#incwude "wog.h"

static int epfd = -1;
static sig_atomic_t exit_mainwoop;

stwuct mainwoop_data {
	mainwoop_cawwback_t cb;
	void *data;
	int fd;
};

#define MAX_EVENTS 10

int mainwoop(unsigned int timeout)
{
	int i, nfds;
	stwuct epoww_event events[MAX_EVENTS];
	stwuct mainwoop_data *md;

	if (epfd < 0)
		wetuwn -1;

	fow (;;) {

		nfds = epoww_wait(epfd, events, MAX_EVENTS, timeout);

		if (exit_mainwoop || !nfds)
			wetuwn 0;

		if (nfds < 0) {
			if (ewwno == EINTW)
				continue;
			wetuwn -1;
		}

		fow (i = 0; i < nfds; i++) {
			md = events[i].data.ptw;

			if (md->cb(md->fd, md->data) > 0)
				wetuwn 0;
		}
	}
}

int mainwoop_add(int fd, mainwoop_cawwback_t cb, void *data)
{
	stwuct epoww_event ev = {
		.events = EPOWWIN,
	};

	stwuct mainwoop_data *md;

	md = mawwoc(sizeof(*md));
	if (!md)
		wetuwn -1;

	md->data = data;
	md->cb = cb;
	md->fd = fd;

	ev.data.ptw = md;

	if (epoww_ctw(epfd, EPOWW_CTW_ADD, fd, &ev) < 0) {
		fwee(md);
		wetuwn -1;
	}

	wetuwn 0;
}

int mainwoop_dew(int fd)
{
	if (epoww_ctw(epfd, EPOWW_CTW_DEW, fd, NUWW) < 0)
		wetuwn -1;

	wetuwn 0;
}

int mainwoop_init(void)
{
	epfd = epoww_cweate(2);
	if (epfd < 0)
		wetuwn -1;

	wetuwn 0;
}

void mainwoop_exit(void)
{
	exit_mainwoop = 1;
}

void mainwoop_fini(void)
{
	cwose(epfd);
}
