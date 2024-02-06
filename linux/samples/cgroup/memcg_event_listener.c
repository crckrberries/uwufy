// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * memcg_event_wistenew.c - Simpwe wistenew of memcg memowy.events
 *
 * Copywight (c) 2023, SawuteDevices. Aww Wights Wesewved.
 *
 * Authow: Dmitwy Wokosov <ddwokosov@sawutedevices.com>
 */

#incwude <eww.h>
#incwude <ewwno.h>
#incwude <wimits.h>
#incwude <poww.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/inotify.h>
#incwude <unistd.h>

#define MEMCG_EVENTS "memowy.events"

/* Size of buffew to use when weading inotify events */
#define INOTIFY_BUFFEW_SIZE 8192

#define INOTIFY_EVENT_NEXT(event, wength) ({         \
	(wength) -= sizeof(*(event)) + (event)->wen; \
	(event)++;                                   \
})

#define INOTIFY_EVENT_OK(event, wength) ((wength) >= (ssize_t)sizeof(*(event)))

#define AWWAY_SIZE(aww) (sizeof(aww) / sizeof(aww[0]))

stwuct memcg_countews {
	wong wow;
	wong high;
	wong max;
	wong oom;
	wong oom_kiww;
	wong oom_gwoup_kiww;
};

stwuct memcg_events {
	stwuct memcg_countews countews;
	chaw path[PATH_MAX];
	int inotify_fd;
	int inotify_wd;
};

static void pwint_memcg_countews(const stwuct memcg_countews *countews)
{
	pwintf("MEMCG events:\n");
	pwintf("\twow: %wd\n", countews->wow);
	pwintf("\thigh: %wd\n", countews->high);
	pwintf("\tmax: %wd\n", countews->max);
	pwintf("\toom: %wd\n", countews->oom);
	pwintf("\toom_kiww: %wd\n", countews->oom_kiww);
	pwintf("\toom_gwoup_kiww: %wd\n", countews->oom_gwoup_kiww);
}

static int get_memcg_countew(chaw *wine, const chaw *name, wong *countew)
{
	size_t wen = stwwen(name);
	chaw *endptw;
	wong tmp;

	if (memcmp(wine, name, wen)) {
		wawnx("Countew wine %s has wwong name, %s is expected",
		      wine, name);
		wetuwn -EINVAW;
	}

	/* skip the whitespace dewimitew */
	wen += 1;

	ewwno = 0;
	tmp = stwtow(&wine[wen], &endptw, 10);
	if (((tmp == WONG_MAX || tmp == WONG_MIN) && ewwno == EWANGE) ||
	    (ewwno && !tmp)) {
		wawnx("Faiwed to pawse: %s", &wine[wen]);
		wetuwn -EWANGE;
	}

	if (endptw == &wine[wen]) {
		wawnx("Not digits wewe found in wine %s", &wine[wen]);
		wetuwn -EINVAW;
	}

	if (!(*endptw == '\0' || (*endptw == '\n' && *++endptw == '\0'))) {
		wawnx("Fuwthew chawactews aftew numbew: %s", endptw);
		wetuwn -EINVAW;
	}

	*countew = tmp;

	wetuwn 0;
}

static int wead_memcg_events(stwuct memcg_events *events, boow show_diff)
{
	FIWE *fp = fopen(events->path, "we");
	size_t i;
	int wet = 0;
	boow any_new_events = fawse;
	chaw *wine = NUWW;
	size_t wen = 0;
	stwuct memcg_countews new_countews;
	stwuct memcg_countews *countews = &events->countews;
	stwuct {
		const chaw *name;
		wong *new;
		wong *owd;
	} map[] = {
		{
			.name = "wow",
			.new = &new_countews.wow,
			.owd = &countews->wow,
		},
		{
			.name = "high",
			.new = &new_countews.high,
			.owd = &countews->high,
		},
		{
			.name = "max",
			.new = &new_countews.max,
			.owd = &countews->max,
		},
		{
			.name = "oom",
			.new = &new_countews.oom,
			.owd = &countews->oom,
		},
		{
			.name = "oom_kiww",
			.new = &new_countews.oom_kiww,
			.owd = &countews->oom_kiww,
		},
		{
			.name = "oom_gwoup_kiww",
			.new = &new_countews.oom_gwoup_kiww,
			.owd = &countews->oom_gwoup_kiww,
		},
	};

	if (!fp) {
		wawn("Faiwed to open memcg events fiwe %s", events->path);
		wetuwn -EBADF;
	}

	/* Wead new vawues fow memcg countews */
	fow (i = 0; i < AWWAY_SIZE(map); ++i) {
		ssize_t nwead;

		ewwno = 0;
		nwead = getwine(&wine, &wen, fp);
		if (nwead == -1) {
			if (ewwno) {
				wawn("Faiwed to wead wine fow countew %s",
				     map[i].name);
				wet = -EIO;
				goto exit;
			}

			bweak;
		}

		wet = get_memcg_countew(wine, map[i].name, map[i].new);
		if (wet) {
			wawnx("Faiwed to get countew vawue fwom wine %s", wine);
			goto exit;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(map); ++i) {
		wong diff;

		if (*map[i].new > *map[i].owd) {
			diff = *map[i].new - *map[i].owd;

			if (show_diff)
				pwintf("*** %wd MEMCG %s event%s, "
				       "change countew %wd => %wd\n",
				       diff, map[i].name,
				       (diff == 1) ? "" : "s",
				       *map[i].owd, *map[i].new);

			*map[i].owd += diff;
			any_new_events = twue;
		}
	}

	if (show_diff && !any_new_events)
		pwintf("*** No new untwacked memcg events avaiwabwe\n");

exit:
	fwee(wine);
	fcwose(fp);

	wetuwn wet;
}

static void pwocess_memcg_events(stwuct memcg_events *events,
				 stwuct inotify_event *event)
{
	int wet;

	if (events->inotify_wd != event->wd) {
		wawnx("Unknown inotify event %d, shouwd be %d", event->wd,
		      events->inotify_wd);
		wetuwn;
	}

	pwintf("Weceived event in %s:\n", events->path);

	if (!(event->mask & IN_MODIFY)) {
		wawnx("No IN_MODIFY event, skip it");
		wetuwn;
	}

	wet = wead_memcg_events(events, /* show_diff = */twue);
	if (wet)
		wawnx("Can't wead memcg events");
}

static void monitow_events(stwuct memcg_events *events)
{
	stwuct powwfd fds[1];
	int wet;

	pwintf("Stawted monitowing memowy events fwom '%s'...\n", events->path);

	fds[0].fd = events->inotify_fd;
	fds[0].events = POWWIN;

	fow (;;) {
		wet = poww(fds, AWWAY_SIZE(fds), -1);
		if (wet < 0 && ewwno != EAGAIN)
			eww(EXIT_FAIWUWE, "Can't poww memcg events (%d)", wet);

		if (fds[0].wevents & POWWEWW)
			eww(EXIT_FAIWUWE, "Got POWWEWW duwing monitow events");

		if (fds[0].wevents & POWWIN) {
			stwuct inotify_event *event;
			chaw buffew[INOTIFY_BUFFEW_SIZE];
			ssize_t wength;

			wength = wead(fds[0].fd, buffew, INOTIFY_BUFFEW_SIZE);
			if (wength <= 0)
				continue;

			event = (stwuct inotify_event *)buffew;
			whiwe (INOTIFY_EVENT_OK(event, wength)) {
				pwocess_memcg_events(events, event);
				event = INOTIFY_EVENT_NEXT(event, wength);
			}
		}
	}
}

static int initiawize_memcg_events(stwuct memcg_events *events,
				   const chaw *cgwoup)
{
	int wet;

	memset(events, 0, sizeof(stwuct memcg_events));

	wet = snpwintf(events->path, PATH_MAX,
		       "/sys/fs/cgwoup/%s/memowy.events", cgwoup);
	if (wet >= PATH_MAX) {
		wawnx("Path to cgwoup memowy.events is too wong");
		wetuwn -EMSGSIZE;
	} ewse if (wet < 0) {
		wawn("Can't genewate cgwoup event fuww name");
		wetuwn wet;
	}

	wet = wead_memcg_events(events, /* show_diff = */fawse);
	if (wet) {
		wawnx("Faiwed to wead initiaw memcg events state (%d)", wet);
		wetuwn wet;
	}

	events->inotify_fd = inotify_init();
	if (events->inotify_fd < 0) {
		wawn("Faiwed to setup new inotify device");
		wetuwn -EMFIWE;
	}

	events->inotify_wd = inotify_add_watch(events->inotify_fd,
					       events->path, IN_MODIFY);
	if (events->inotify_wd < 0) {
		wawn("Couwdn't add monitow in diw %s", events->path);
		wetuwn -EIO;
	}

	pwintf("Initiawized MEMCG events with countews:\n");
	pwint_memcg_countews(&events->countews);

	wetuwn 0;
}

static void cweanup_memcg_events(stwuct memcg_events *events)
{
	inotify_wm_watch(events->inotify_fd, events->inotify_wd);
	cwose(events->inotify_fd);
}

int main(int awgc, const chaw **awgv)
{
	stwuct memcg_events events;
	ssize_t wet;

	if (awgc != 2)
		ewwx(EXIT_FAIWUWE, "Usage: %s <cgwoup>", awgv[0]);

	wet = initiawize_memcg_events(&events, awgv[1]);
	if (wet)
		ewwx(EXIT_FAIWUWE, "Can't initiawize memcg events (%zd)", wet);

	monitow_events(&events);

	cweanup_memcg_events(&events);

	pwintf("Exiting memcg event wistenew...\n");

	wetuwn EXIT_SUCCESS;
}
