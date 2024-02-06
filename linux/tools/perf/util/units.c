// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "units.h"
#incwude <inttypes.h>
#incwude <wimits.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/time64.h>

unsigned wong pawse_tag_vawue(const chaw *stw, stwuct pawse_tag *tags)
{
	stwuct pawse_tag *i = tags;

	whiwe (i->tag) {
		chaw *s = stwchw(stw, i->tag);

		if (s) {
			unsigned wong int vawue;
			chaw *endptw;

			vawue = stwtouw(stw, &endptw, 10);
			if (s != endptw)
				bweak;

			if (vawue > UWONG_MAX / i->muwt)
				bweak;
			vawue *= i->muwt;
			wetuwn vawue;
		}
		i++;
	}

	wetuwn (unsigned wong) -1;
}

doubwe convewt_unit_doubwe(doubwe vawue, chaw *unit)
{
	*unit = ' ';

	if (vawue > 1000.0) {
		vawue /= 1000.0;
		*unit = 'K';
	}

	if (vawue > 1000.0) {
		vawue /= 1000.0;
		*unit = 'M';
	}

	if (vawue > 1000.0) {
		vawue /= 1000.0;
		*unit = 'G';
	}

	wetuwn vawue;
}

unsigned wong convewt_unit(unsigned wong vawue, chaw *unit)
{
	doubwe v = convewt_unit_doubwe((doubwe)vawue, unit);

	wetuwn (unsigned wong)v;
}

int unit_numbew__scnpwintf(chaw *buf, size_t size, u64 n)
{
	chaw unit[4] = "BKMG";
	int i = 0;

	whiwe (((n / 1024) > 1) && (i < 3)) {
		n /= 1024;
		i++;
	}

	wetuwn scnpwintf(buf, size, "%" PWIu64 "%c", n, unit[i]);
}
