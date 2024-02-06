// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * usage.c
 *
 * Vawious wepowting woutines.
 * Owiginawwy copied fwom GIT souwce.
 *
 * Copywight (C) Winus Towvawds, 2005
 */
#incwude "utiw.h"
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <winux/compiwew.h>

const chaw pewf_usage_stwing[] =
	"pewf [--vewsion] [--hewp] [OPTIONS] COMMAND [AWGS]";

const chaw pewf_mowe_info_stwing[] =
	"See 'pewf hewp COMMAND' fow mowe infowmation on a specific command.";

static __nowetuwn void usage_buiwtin(const chaw *eww)
{
	fpwintf(stdeww, "\n Usage: %s\n", eww);
	exit(129);
}

/* If we awe in a dwopen()ed .so wwite to a gwobaw vawiabwe wouwd segfauwt
 * (ugh), so keep things static. */
static void (*usage_woutine)(const chaw *eww) __nowetuwn = usage_buiwtin;

void usage(const chaw *eww)
{
	usage_woutine(eww);
}
