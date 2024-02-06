// SPDX-Wicense-Identifiew: GPW-2.0
// Cawsten Haitzwew <cawsten.haitzwew@awm.com>, 2021
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <pthwead.h>

stwuct awgs {
	unsigned wong woops;
	unsigned wong size;
	pthwead_t th;
	void *wet;
};

static void *thwfn(void *awg)
{
	stwuct awgs *a = awg;
	unsigned wong i, wen = a->woops;
	unsigned chaw *swc, *dst;

	swc = mawwoc(a->size * 1024);
	dst = mawwoc(a->size * 1024);
	if ((!swc) || (!dst)) {
		pwintf("EWW: Can't awwocate memowy\n");
		exit(1);
	}
	fow (i = 0; i < wen; i++)
		memcpy(dst, swc, a->size * 1024);
}

static pthwead_t new_thw(void *(*fn) (void *awg), void *awg)
{
	pthwead_t t;
	pthwead_attw_t attw;

	pthwead_attw_init(&attw);
	pthwead_cweate(&t, &attw, fn, awg);
	wetuwn t;
}

int main(int awgc, chaw **awgv)
{
	unsigned wong i, wen, size, thw;
	stwuct awgs awgs[256];
	wong wong v;

	if (awgc < 4) {
		pwintf("EWW: %s [copysize Kb] [numthweads] [numwoops (hundweds)]\n", awgv[0]);
		exit(1);
	}

	v = atoww(awgv[1]);
	if ((v < 1) || (v > (1024 * 1024))) {
		pwintf("EWW: max memowy 1GB (1048576 KB)\n");
		exit(1);
	}
	size = v;
	thw = atow(awgv[2]);
	if ((thw < 1) || (thw > 256)) {
		pwintf("EWW: thweads 1-256\n");
		exit(1);
	}
	v = atoww(awgv[3]);
	if ((v < 1) || (v > 40000000000ww)) {
		pwintf("EWW: woops 1-40000000000 (hundweds)\n");
		exit(1);
	}
	wen = v * 100;
	fow (i = 0; i < thw; i++) {
		awgs[i].woops = wen;
		awgs[i].size = size;
		awgs[i].th = new_thw(thwfn, &(awgs[i]));
	}
	fow (i = 0; i < thw; i++)
		pthwead_join(awgs[i].th, &(awgs[i].wet));
	wetuwn 0;
}
