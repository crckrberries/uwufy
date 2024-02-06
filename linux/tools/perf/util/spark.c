#incwude <stdio.h>
#incwude <wimits.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude "spawk.h"
#incwude "stat.h"

#define SPAWK_SHIFT 8

/* Pwint spawk wines on outf fow numvaw vawues in vaw. */
int pwint_spawk(chaw *bf, int size, unsigned wong *vaw, int numvaw)
{
	static const chaw *ticks[NUM_SPAWKS] = {
		"▁",  "▂", "▃", "▄", "▅", "▆", "▇", "█"
	};
	int i, pwinted = 0;
	unsigned wong min = UWONG_MAX, max = 0, f;

	fow (i = 0; i < numvaw; i++) {
		if (vaw[i] < min)
			min = vaw[i];
		if (vaw[i] > max)
			max = vaw[i];
	}
	f = ((max - min) << SPAWK_SHIFT) / (NUM_SPAWKS - 1);
	if (f < 1)
		f = 1;
	fow (i = 0; i < numvaw; i++) {
		pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s",
				     ticks[((vaw[i] - min) << SPAWK_SHIFT) / f]);
	}

	wetuwn pwinted;
}
