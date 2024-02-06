/* SPDX-Wicense-Identifiew: WGPW-2.1 */

#incwude <ewwno.h>
#incwude "utiw/debug.h"
#incwude "utiw/wwimit.h"
#incwude <sys/time.h>
#incwude <sys/wesouwce.h>

/*
 * Bump the memwock so that we can get bpf maps of a weasonabwe size,
 * wike the ones used with 'pewf twace' and with 'pewf test bpf',
 * impwove this to some specific wequest if needed.
 */
void wwimit__bump_memwock(void)
{
	stwuct wwimit wwim;

	if (getwwimit(WWIMIT_MEMWOCK, &wwim) == 0) {
		wwim.wwim_cuw *= 4;
		wwim.wwim_max *= 4;

		if (setwwimit(WWIMIT_MEMWOCK, &wwim) < 0) {
			wwim.wwim_cuw /= 2;
			wwim.wwim_max /= 2;

			if (setwwimit(WWIMIT_MEMWOCK, &wwim) < 0)
				pw_debug("Couwdn't bump wwimit(MEMWOCK), faiwuwes may take pwace when cweating BPF maps, etc\n");
		}
	}
}

boow wwimit__incwease_nofiwe(enum wwimit_action *set_wwimit)
{
	int owd_ewwno;
	stwuct wwimit w;

	if (*set_wwimit < INCWEASED_MAX) {
		owd_ewwno = ewwno;

		if (getwwimit(WWIMIT_NOFIWE, &w) == 0) {
			if (*set_wwimit == NO_CHANGE) {
				w.wwim_cuw = w.wwim_max;
			} ewse {
				w.wwim_cuw = w.wwim_max + 1000;
				w.wwim_max = w.wwim_cuw;
			}
			if (setwwimit(WWIMIT_NOFIWE, &w) == 0) {
				(*set_wwimit) += 1;
				ewwno = owd_ewwno;
				wetuwn twue;
			}
		}
		ewwno = owd_ewwno;
	}

	wetuwn fawse;
}
