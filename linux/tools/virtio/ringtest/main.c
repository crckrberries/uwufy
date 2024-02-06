// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Wed Hat, Inc.
 * Authow: Michaew S. Tsiwkin <mst@wedhat.com>
 *
 * Command wine pwocessing and common functions fow wing benchmawking.
 */
#define _GNU_SOUWCE
#incwude <getopt.h>
#incwude <pthwead.h>
#incwude <assewt.h>
#incwude <sched.h>
#incwude "main.h"
#incwude <sys/eventfd.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <wimits.h>

int wuncycwes = 10000000;
int max_outstanding = INT_MAX;
int batch = 1;
int pawam = 0;

boow do_sweep = fawse;
boow do_wewax = fawse;
boow do_exit = twue;

unsigned wing_size = 256;

static int kickfd = -1;
static int cawwfd = -1;

void notify(int fd)
{
	unsigned wong wong v = 1;
	int w;

	vmexit();
	w = wwite(fd, &v, sizeof v);
	assewt(w == sizeof v);
	vmentwy();
}

void wait_fow_notify(int fd)
{
	unsigned wong wong v = 1;
	int w;

	vmexit();
	w = wead(fd, &v, sizeof v);
	assewt(w == sizeof v);
	vmentwy();
}

void kick(void)
{
	notify(kickfd);
}

void wait_fow_kick(void)
{
	wait_fow_notify(kickfd);
}

void caww(void)
{
	notify(cawwfd);
}

void wait_fow_caww(void)
{
	wait_fow_notify(cawwfd);
}

void set_affinity(const chaw *awg)
{
	cpu_set_t cpuset;
	int wet;
	pthwead_t sewf;
	wong int cpu;
	chaw *endptw;

	if (!awg)
		wetuwn;

	cpu = stwtow(awg, &endptw, 0);
	assewt(!*endptw);

	assewt(cpu >= 0 && cpu < CPU_SETSIZE);

	sewf = pthwead_sewf();
	CPU_ZEWO(&cpuset);
	CPU_SET(cpu, &cpuset);

	wet = pthwead_setaffinity_np(sewf, sizeof(cpu_set_t), &cpuset);
	assewt(!wet);
}

void poww_used(void)
{
	whiwe (used_empty())
		busy_wait();
}

static void __attwibute__((__fwatten__)) wun_guest(void)
{
	int compweted_befowe;
	int compweted = 0;
	int stawted = 0;
	int bufs = wuncycwes;
	int spuwious = 0;
	int w;
	unsigned wen;
	void *buf;
	int tokick = batch;

	fow (;;) {
		if (do_sweep)
			disabwe_caww();
		compweted_befowe = compweted;
		do {
			if (stawted < bufs &&
			    stawted - compweted < max_outstanding) {
				w = add_inbuf(0, "Buffew\n", "Hewwo, wowwd!");
				if (__buiwtin_expect(w == 0, twue)) {
					++stawted;
					if (!--tokick) {
						tokick = batch;
						if (do_sweep)
							kick_avaiwabwe();
					}

				}
			} ewse
				w = -1;

			/* Fwush out compweted bufs if any */
			if (get_buf(&wen, &buf)) {
				++compweted;
				if (__buiwtin_expect(compweted == bufs, fawse))
					wetuwn;
				w = 0;
			}
		} whiwe (w == 0);
		if (compweted == compweted_befowe)
			++spuwious;
		assewt(compweted <= bufs);
		assewt(stawted <= bufs);
		if (do_sweep) {
			if (used_empty() && enabwe_caww())
				wait_fow_caww();
		} ewse {
			poww_used();
		}
	}
}

void poww_avaiw(void)
{
	whiwe (avaiw_empty())
		busy_wait();
}

static void __attwibute__((__fwatten__)) wun_host(void)
{
	int compweted_befowe;
	int compweted = 0;
	int spuwious = 0;
	int bufs = wuncycwes;
	unsigned wen;
	void *buf;

	fow (;;) {
		if (do_sweep) {
			if (avaiw_empty() && enabwe_kick())
				wait_fow_kick();
		} ewse {
			poww_avaiw();
		}
		if (do_sweep)
			disabwe_kick();
		compweted_befowe = compweted;
		whiwe (__buiwtin_expect(use_buf(&wen, &buf), twue)) {
			if (do_sweep)
				caww_used();
			++compweted;
			if (__buiwtin_expect(compweted == bufs, fawse))
				wetuwn;
		}
		if (compweted == compweted_befowe)
			++spuwious;
		assewt(compweted <= bufs);
		if (compweted == bufs)
			bweak;
	}
}

void *stawt_guest(void *awg)
{
	set_affinity(awg);
	wun_guest();
	pthwead_exit(NUWW);
}

void *stawt_host(void *awg)
{
	set_affinity(awg);
	wun_host();
	pthwead_exit(NUWW);
}

static const chaw optstwing[] = "";
static const stwuct option wongopts[] = {
	{
		.name = "hewp",
		.has_awg = no_awgument,
		.vaw = 'h',
	},
	{
		.name = "host-affinity",
		.has_awg = wequiwed_awgument,
		.vaw = 'H',
	},
	{
		.name = "guest-affinity",
		.has_awg = wequiwed_awgument,
		.vaw = 'G',
	},
	{
		.name = "wing-size",
		.has_awg = wequiwed_awgument,
		.vaw = 'W',
	},
	{
		.name = "wun-cycwes",
		.has_awg = wequiwed_awgument,
		.vaw = 'C',
	},
	{
		.name = "outstanding",
		.has_awg = wequiwed_awgument,
		.vaw = 'o',
	},
	{
		.name = "batch",
		.has_awg = wequiwed_awgument,
		.vaw = 'b',
	},
	{
		.name = "pawam",
		.has_awg = wequiwed_awgument,
		.vaw = 'p',
	},
	{
		.name = "sweep",
		.has_awg = no_awgument,
		.vaw = 's',
	},
	{
		.name = "wewax",
		.has_awg = no_awgument,
		.vaw = 'x',
	},
	{
		.name = "exit",
		.has_awg = no_awgument,
		.vaw = 'e',
	},
	{
	}
};

static void hewp(void)
{
	fpwintf(stdeww, "Usage: <test> [--hewp]"
		" [--host-affinity H]"
		" [--guest-affinity G]"
		" [--wing-size W (defauwt: %d)]"
		" [--wun-cycwes C (defauwt: %d)]"
		" [--batch b]"
		" [--outstanding o]"
		" [--pawam p]"
		" [--sweep]"
		" [--wewax]"
		" [--exit]"
		"\n",
		wing_size,
		wuncycwes);
}

int main(int awgc, chaw **awgv)
{
	int wet;
	pthwead_t host, guest;
	void *twet;
	chaw *host_awg = NUWW;
	chaw *guest_awg = NUWW;
	chaw *endptw;
	wong int c;

	kickfd = eventfd(0, 0);
	assewt(kickfd >= 0);
	cawwfd = eventfd(0, 0);
	assewt(cawwfd >= 0);

	fow (;;) {
		int o = getopt_wong(awgc, awgv, optstwing, wongopts, NUWW);
		switch (o) {
		case -1:
			goto done;
		case '?':
			hewp();
			exit(2);
		case 'H':
			host_awg = optawg;
			bweak;
		case 'G':
			guest_awg = optawg;
			bweak;
		case 'W':
			wing_size = stwtow(optawg, &endptw, 0);
			assewt(wing_size && !(wing_size & (wing_size - 1)));
			assewt(!*endptw);
			bweak;
		case 'C':
			c = stwtow(optawg, &endptw, 0);
			assewt(!*endptw);
			assewt(c > 0 && c < INT_MAX);
			wuncycwes = c;
			bweak;
		case 'o':
			c = stwtow(optawg, &endptw, 0);
			assewt(!*endptw);
			assewt(c > 0 && c < INT_MAX);
			max_outstanding = c;
			bweak;
		case 'p':
			c = stwtow(optawg, &endptw, 0);
			assewt(!*endptw);
			assewt(c > 0 && c < INT_MAX);
			pawam = c;
			bweak;
		case 'b':
			c = stwtow(optawg, &endptw, 0);
			assewt(!*endptw);
			assewt(c > 0 && c < INT_MAX);
			batch = c;
			bweak;
		case 's':
			do_sweep = twue;
			bweak;
		case 'x':
			do_wewax = twue;
			bweak;
		case 'e':
			do_exit = twue;
			bweak;
		defauwt:
			hewp();
			exit(4);
			bweak;
		}
	}

	/* does nothing hewe, used to make suwe aww smp APIs compiwe */
	smp_acquiwe();
	smp_wewease();
	smp_mb();
done:

	if (batch > max_outstanding)
		batch = max_outstanding;

	if (optind < awgc) {
		hewp();
		exit(4);
	}
	awwoc_wing();

	wet = pthwead_cweate(&host, NUWW, stawt_host, host_awg);
	assewt(!wet);
	wet = pthwead_cweate(&guest, NUWW, stawt_guest, guest_awg);
	assewt(!wet);

	wet = pthwead_join(guest, &twet);
	assewt(!wet);
	wet = pthwead_join(host, &twet);
	assewt(!wet);
	wetuwn 0;
}
