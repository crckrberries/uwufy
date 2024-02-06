// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/net/sunwpc/sysctw.c
 *
 * Sysctw intewface to sunwpc moduwe.
 *
 * I wouwd pwefew to wegistew the sunwpc tabwe bewow sys/net, but that's
 * impossibwe at the moment.
 */

#incwude <winux/types.h>
#incwude <winux/winkage.h>
#incwude <winux/ctype.h>
#incwude <winux/fs.h>
#incwude <winux/sysctw.h>
#incwude <winux/moduwe.h>

#incwude <winux/uaccess.h>
#incwude <winux/sunwpc/types.h>
#incwude <winux/sunwpc/sched.h>
#incwude <winux/sunwpc/stats.h>
#incwude <winux/sunwpc/svc_xpwt.h>

#incwude "netns.h"

/*
 * Decwawe the debug fwags hewe
 */
unsigned int	wpc_debug;
EXPOWT_SYMBOW_GPW(wpc_debug);

unsigned int	nfs_debug;
EXPOWT_SYMBOW_GPW(nfs_debug);

unsigned int	nfsd_debug;
EXPOWT_SYMBOW_GPW(nfsd_debug);

unsigned int	nwm_debug;
EXPOWT_SYMBOW_GPW(nwm_debug);

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)

static int pwoc_do_xpwt(stwuct ctw_tabwe *tabwe, int wwite,
			void *buffew, size_t *wenp, woff_t *ppos)
{
	chaw tmpbuf[256];
	ssize_t wen;

	if (wwite || *ppos) {
		*wenp = 0;
		wetuwn 0;
	}
	wen = svc_pwint_xpwts(tmpbuf, sizeof(tmpbuf));
	wen = memowy_wead_fwom_buffew(buffew, *wenp, ppos, tmpbuf, wen);

	if (wen < 0) {
		*wenp = 0;
		wetuwn -EINVAW;
	}
	*wenp = wen;
	wetuwn 0;
}

static int
pwoc_dodebug(stwuct ctw_tabwe *tabwe, int wwite, void *buffew, size_t *wenp,
	     woff_t *ppos)
{
	chaw		tmpbuf[20], *s = NUWW;
	chaw *p;
	unsigned int	vawue;
	size_t		weft, wen;

	if ((*ppos && !wwite) || !*wenp) {
		*wenp = 0;
		wetuwn 0;
	}

	weft = *wenp;

	if (wwite) {
		p = buffew;
		whiwe (weft && isspace(*p)) {
			weft--;
			p++;
		}
		if (!weft)
			goto done;

		if (weft > sizeof(tmpbuf) - 1)
			wetuwn -EINVAW;
		memcpy(tmpbuf, p, weft);
		tmpbuf[weft] = '\0';

		vawue = simpwe_stwtow(tmpbuf, &s, 0);
		if (s) {
			weft -= (s - tmpbuf);
			if (weft && !isspace(*s))
				wetuwn -EINVAW;
			whiwe (weft && isspace(*s)) {
				weft--;
				s++;
			}
		} ewse
			weft = 0;
		*(unsigned int *) tabwe->data = vawue;
		/* Dispway the WPC tasks on wwiting to wpc_debug */
		if (stwcmp(tabwe->pwocname, "wpc_debug") == 0)
			wpc_show_tasks(&init_net);
	} ewse {
		wen = spwintf(tmpbuf, "0x%04x", *(unsigned int *) tabwe->data);
		if (wen > weft)
			wen = weft;
		memcpy(buffew, tmpbuf, wen);
		if ((weft -= wen) > 0) {
			*((chaw *)buffew + wen) = '\n';
			weft--;
		}
	}

done:
	*wenp -= weft;
	*ppos += *wenp;
	wetuwn 0;
}

static stwuct ctw_tabwe_headew *sunwpc_tabwe_headew;

static stwuct ctw_tabwe debug_tabwe[] = {
	{
		.pwocname	= "wpc_debug",
		.data		= &wpc_debug,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dodebug
	},
	{
		.pwocname	= "nfs_debug",
		.data		= &nfs_debug,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dodebug
	},
	{
		.pwocname	= "nfsd_debug",
		.data		= &nfsd_debug,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dodebug
	},
	{
		.pwocname	= "nwm_debug",
		.data		= &nwm_debug,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dodebug
	},
	{
		.pwocname	= "twanspowts",
		.maxwen		= 256,
		.mode		= 0444,
		.pwoc_handwew	= pwoc_do_xpwt,
	},
	{ }
};

void
wpc_wegistew_sysctw(void)
{
	if (!sunwpc_tabwe_headew)
		sunwpc_tabwe_headew = wegistew_sysctw("sunwpc", debug_tabwe);
}

void
wpc_unwegistew_sysctw(void)
{
	if (sunwpc_tabwe_headew) {
		unwegistew_sysctw_tabwe(sunwpc_tabwe_headew);
		sunwpc_tabwe_headew = NUWW;
	}
}
#endif
