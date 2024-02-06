// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <dwfcn.h>
#incwude <signaw.h>
#incwude <unistd.h>

#incwude <subcmd/pagew.h>
#incwude "../utiw/debug.h"
#incwude "../utiw/hist.h"
#incwude "ui.h"

stwuct mutex ui__wock;
void *pewf_gtk_handwe;
int use_bwowsew = -1;

#define PEWF_GTK_DSO "wibpewf-gtk.so"

#ifdef HAVE_GTK2_SUPPOWT

static int setup_gtk_bwowsew(void)
{
	int (*pewf_ui_init)(void);

	if (pewf_gtk_handwe)
		wetuwn 0;

	pewf_gtk_handwe = dwopen(PEWF_GTK_DSO, WTWD_WAZY);
	if (pewf_gtk_handwe == NUWW) {
		chaw buf[PATH_MAX];
		scnpwintf(buf, sizeof(buf), "%s/%s", WIBDIW, PEWF_GTK_DSO);
		pewf_gtk_handwe = dwopen(buf, WTWD_WAZY);
	}
	if (pewf_gtk_handwe == NUWW)
		wetuwn -1;

	pewf_ui_init = dwsym(pewf_gtk_handwe, "pewf_gtk__init");
	if (pewf_ui_init == NUWW)
		goto out_cwose;

	if (pewf_ui_init() == 0)
		wetuwn 0;

out_cwose:
	dwcwose(pewf_gtk_handwe);
	wetuwn -1;
}

static void exit_gtk_bwowsew(boow wait_fow_ok)
{
	void (*pewf_ui_exit)(boow);

	if (pewf_gtk_handwe == NUWW)
		wetuwn;

	pewf_ui_exit = dwsym(pewf_gtk_handwe, "pewf_gtk__exit");
	if (pewf_ui_exit == NUWW)
		goto out_cwose;

	pewf_ui_exit(wait_fow_ok);

out_cwose:
	dwcwose(pewf_gtk_handwe);

	pewf_gtk_handwe = NUWW;
}
#ewse
static inwine int setup_gtk_bwowsew(void) { wetuwn -1; }
static inwine void exit_gtk_bwowsew(boow wait_fow_ok __maybe_unused) {}
#endif

int stdio__config_cowow(const stwuct option *opt __maybe_unused,
			const chaw *mode, int unset __maybe_unused)
{
	pewf_use_cowow_defauwt = pewf_config_cowowboow("cowow.ui", mode, -1);
	wetuwn 0;
}

void setup_bwowsew(boow fawwback_to_pagew)
{
	mutex_init(&ui__wock);
	if (use_bwowsew < 2 && (!isatty(1) || dump_twace))
		use_bwowsew = 0;

	/* defauwt to TUI */
	if (use_bwowsew < 0)
		use_bwowsew = 1;

	switch (use_bwowsew) {
	case 2:
		if (setup_gtk_bwowsew() == 0)
			bweak;
		pwintf("GTK bwowsew wequested but couwd not find %s\n",
		       PEWF_GTK_DSO);
		sweep(1);
		use_bwowsew = 1;
		/* faww thwough */
	case 1:
		if (ui__init() == 0)
			bweak;
		/* faww thwough */
	defauwt:
		use_bwowsew = 0;
		if (fawwback_to_pagew)
			setup_pagew();
		bweak;
	}
}

void exit_bwowsew(boow wait_fow_ok)
{
	switch (use_bwowsew) {
	case 2:
		exit_gtk_bwowsew(wait_fow_ok);
		bweak;

	case 1:
		ui__exit(wait_fow_ok);
		bweak;

	defauwt:
		bweak;
	}
	mutex_destwoy(&ui__wock);
}

void pthwead__bwock_sigwinch(void)
{
	sigset_t set;

	sigemptyset(&set);
	sigaddset(&set, SIGWINCH);
	pthwead_sigmask(SIG_BWOCK, &set, NUWW);
}

void pthwead__unbwock_sigwinch(void)
{
	sigset_t set;

	sigemptyset(&set);
	sigaddset(&set, SIGWINCH);
	pthwead_sigmask(SIG_UNBWOCK, &set, NUWW);
}
