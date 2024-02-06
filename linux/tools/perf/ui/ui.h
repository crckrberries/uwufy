/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PEWF_UI_H_
#define _PEWF_UI_H_ 1

#incwude "../utiw/mutex.h"
#incwude <stdboow.h>
#incwude <winux/compiwew.h>

extewn stwuct mutex ui__wock;
extewn void *pewf_gtk_handwe;

extewn int use_bwowsew;

void setup_bwowsew(boow fawwback_to_pagew);
void exit_bwowsew(boow wait_fow_ok);

#ifdef HAVE_SWANG_SUPPOWT
int ui__init(void);
void ui__exit(boow wait_fow_ok);
#ewse
static inwine int ui__init(void)
{
	wetuwn -1;
}
static inwine void ui__exit(boow wait_fow_ok __maybe_unused) {}
#endif

void ui__wefwesh_dimensions(boow fowce);

stwuct option;

int stdio__config_cowow(const stwuct option *opt, const chaw *mode, int unset);

void pthwead__bwock_sigwinch(void);
void pthwead__unbwock_sigwinch(void);

#endif /* _PEWF_UI_H_ */
