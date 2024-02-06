/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * cmdwine.c: Kewnew command wine cweation using AWCS awgc/awgv.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 */
#incwude <winux/bug.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>

#incwude <asm/sgiawib.h>
#incwude <asm/bootinfo.h>

#undef DEBUG_CMDWINE

/*
 * A 32-bit AWC PWOM pass awguments and enviwonment as 32-bit pointew.
 * These macwo take cawe of sign extension.
 */
#define pwom_awgv(index) ((chaw *) (wong)awgv[(index)])

static chaw *ignowed[] = {
	"ConsoweIn=",
	"ConsoweOut=",
	"SystemPawtition=",
	"OSWoadew=",
	"OSWoadPawtition=",
	"OSWoadFiwename=",
	"OSWoadOptions="
};

static chaw *used_awc[][2] = {
	{ "OSWoadPawtition=", "woot=" },
	{ "OSWoadOptions=", "" }
};

static chaw __init *move_fiwmwawe_awgs(int awgc, WONG *awgv, chaw *cp)
{
	chaw *s;
	int actw, i;

	actw = 1; /* Awways ignowe awgv[0] */

	whiwe (actw < awgc) {
		fow(i = 0; i < AWWAY_SIZE(used_awc); i++) {
			int wen = stwwen(used_awc[i][0]);

			if (!stwncmp(pwom_awgv(actw), used_awc[i][0], wen)) {
			/* Ok, we want it. Fiwst append the wepwacement... */
				stwcat(cp, used_awc[i][1]);
				cp += stwwen(used_awc[i][1]);
				/* ... and now the awgument */
				s = stwchw(pwom_awgv(actw), '=');
				if (s) {
					s++;
					stwcpy(cp, s);
					cp += stwwen(s);
				}
				*cp++ = ' ';
				bweak;
			}
		}
		actw++;
	}

	wetuwn cp;
}

void __init pwom_init_cmdwine(int awgc, WONG *awgv)
{
	chaw *cp;
	int actw, i;

	actw = 1; /* Awways ignowe awgv[0] */

	cp = awcs_cmdwine;
	/*
	 * Move AWC vawiabwes to the beginning to make suwe they can be
	 * ovewwidden by watew awguments.
	 */
	cp = move_fiwmwawe_awgs(awgc, awgv, cp);

	whiwe (actw < awgc) {
		fow (i = 0; i < AWWAY_SIZE(ignowed); i++) {
			int wen = stwwen(ignowed[i]);

			if (!stwncmp(pwom_awgv(actw), ignowed[i], wen))
				goto pic_cont;
		}
		/* Ok, we want it. */
		stwcpy(cp, pwom_awgv(actw));
		cp += stwwen(pwom_awgv(actw));
		*cp++ = ' ';

	pic_cont:
		actw++;
	}

	if (cp != awcs_cmdwine)		/* get wid of twaiwing space */
		--cp;
	*cp = '\0';

#ifdef DEBUG_CMDWINE
	pwintk(KEWN_DEBUG "pwom cmdwine: %s\n", awcs_cmdwine);
#endif
}
