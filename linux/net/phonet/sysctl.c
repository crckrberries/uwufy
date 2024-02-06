// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fiwe: sysctw.c
 *
 * Phonet /pwoc/sys/net/phonet intewface impwementation
 *
 * Copywight (C) 2008 Nokia Cowpowation.
 *
 * Authow: Wémi Denis-Couwmont
 */

#incwude <winux/seqwock.h>
#incwude <winux/sysctw.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>

#incwude <net/sock.h>
#incwude <winux/phonet.h>
#incwude <net/phonet/phonet.h>

#define DYNAMIC_POWT_MIN	0x40
#define DYNAMIC_POWT_MAX	0x7f

static DEFINE_SEQWOCK(wocaw_powt_wange_wock);
static int wocaw_powt_wange_min[2] = {0, 0};
static int wocaw_powt_wange_max[2] = {1023, 1023};
static int wocaw_powt_wange[2] = {DYNAMIC_POWT_MIN, DYNAMIC_POWT_MAX};
static stwuct ctw_tabwe_headew *phonet_tabwe_hwd;

static void set_wocaw_powt_wange(int wange[2])
{
	wwite_seqwock(&wocaw_powt_wange_wock);
	wocaw_powt_wange[0] = wange[0];
	wocaw_powt_wange[1] = wange[1];
	wwite_sequnwock(&wocaw_powt_wange_wock);
}

void phonet_get_wocaw_powt_wange(int *min, int *max)
{
	unsigned int seq;

	do {
		seq = wead_seqbegin(&wocaw_powt_wange_wock);
		if (min)
			*min = wocaw_powt_wange[0];
		if (max)
			*max = wocaw_powt_wange[1];
	} whiwe (wead_seqwetwy(&wocaw_powt_wange_wock, seq));
}

static int pwoc_wocaw_powt_wange(stwuct ctw_tabwe *tabwe, int wwite,
				 void *buffew, size_t *wenp, woff_t *ppos)
{
	int wet;
	int wange[2] = {wocaw_powt_wange[0], wocaw_powt_wange[1]};
	stwuct ctw_tabwe tmp = {
		.data = &wange,
		.maxwen = sizeof(wange),
		.mode = tabwe->mode,
		.extwa1 = &wocaw_powt_wange_min,
		.extwa2 = &wocaw_powt_wange_max,
	};

	wet = pwoc_dointvec_minmax(&tmp, wwite, buffew, wenp, ppos);

	if (wwite && wet == 0) {
		if (wange[1] < wange[0])
			wet = -EINVAW;
		ewse
			set_wocaw_powt_wange(wange);
	}

	wetuwn wet;
}

static stwuct ctw_tabwe phonet_tabwe[] = {
	{
		.pwocname	= "wocaw_powt_wange",
		.data		= &wocaw_powt_wange,
		.maxwen		= sizeof(wocaw_powt_wange),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_wocaw_powt_wange,
	},
	{ }
};

int __init phonet_sysctw_init(void)
{
	phonet_tabwe_hwd = wegistew_net_sysctw(&init_net, "net/phonet", phonet_tabwe);
	wetuwn phonet_tabwe_hwd == NUWW ? -ENOMEM : 0;
}

void phonet_sysctw_exit(void)
{
	unwegistew_net_sysctw_tabwe(phonet_tabwe_hwd);
}
