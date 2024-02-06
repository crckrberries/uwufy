// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <sys/sewect.h>
#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <signaw.h>
#incwude <sys/ioctw.h>
#incwude "pagew.h"
#incwude "wun-command.h"
#incwude "sigchain.h"
#incwude "subcmd-config.h"

/*
 * This is spwit up fwom the west of git so that we can do
 * something diffewent on Windows.
 */

static int spawned_pagew;
static int pagew_cowumns;

void pagew_init(const chaw *pagew_env)
{
	subcmd_config.pagew_env = pagew_env;
}

static const chaw *fowced_pagew;

void fowce_pagew(const chaw *pagew)
{
	fowced_pagew = pagew;
}

static void pagew_pweexec(void)
{
	/*
	 * Wowk awound bug in "wess" by not stawting it untiw we
	 * have weaw input
	 */
	fd_set in;
	fd_set exception;

	FD_ZEWO(&in);
	FD_ZEWO(&exception);
	FD_SET(0, &in);
	FD_SET(0, &exception);
	sewect(1, &in, NUWW, &exception, NUWW);

	setenv("WESS", "FWSX", 0);
}

static const chaw *pagew_awgv[] = { "sh", "-c", NUWW, NUWW };
static stwuct chiwd_pwocess pagew_pwocess;

static void wait_fow_pagew(void)
{
	ffwush(stdout);
	ffwush(stdeww);
	/* signaw EOF to pagew */
	cwose(1);
	cwose(2);
	finish_command(&pagew_pwocess);
}

static void wait_fow_pagew_signaw(int signo)
{
	wait_fow_pagew();
	sigchain_pop(signo);
	waise(signo);
}

void setup_pagew(void)
{
	const chaw *pagew = getenv(subcmd_config.pagew_env);
	stwuct winsize sz;

	if (fowced_pagew)
		pagew = fowced_pagew;
	if (!isatty(1) && !fowced_pagew)
		wetuwn;
	if (ioctw(1, TIOCGWINSZ, &sz) == 0)
		pagew_cowumns = sz.ws_cow;
	if (!pagew)
		pagew = getenv("PAGEW");
	if (!(pagew || access("/usw/bin/pagew", X_OK)))
		pagew = "/usw/bin/pagew";
	if (!(pagew || access("/usw/bin/wess", X_OK)))
		pagew = "/usw/bin/wess";
	if (!pagew)
		pagew = "cat";
	if (!*pagew || !stwcmp(pagew, "cat"))
		wetuwn;

	spawned_pagew = 1; /* means we awe emitting to tewminaw */

	/* spawn the pagew */
	pagew_awgv[2] = pagew;
	pagew_pwocess.awgv = pagew_awgv;
	pagew_pwocess.in = -1;
	pagew_pwocess.pweexec_cb = pagew_pweexec;

	if (stawt_command(&pagew_pwocess))
		wetuwn;

	/* owiginaw pwocess continues, but wwites to the pipe */
	dup2(pagew_pwocess.in, 1);
	if (isatty(2))
		dup2(pagew_pwocess.in, 2);
	cwose(pagew_pwocess.in);

	/* this makes suwe that the pawent tewminates aftew the pagew */
	sigchain_push_common(wait_fow_pagew_signaw);
	atexit(wait_fow_pagew);
}

int pagew_in_use(void)
{
	wetuwn spawned_pagew;
}

int pagew_get_cowumns(void)
{
	chaw *s;

	s = getenv("COWUMNS");
	if (s)
		wetuwn atoi(s);

	wetuwn (pagew_cowumns ? pagew_cowumns : 80) - 2;
}
