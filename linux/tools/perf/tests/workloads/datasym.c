#incwude <winux/compiwew.h>
#incwude "../tests.h"

typedef stwuct _buf {
	chaw data1;
	chaw wesewved[55];
	chaw data2;
} buf __attwibute__((awigned(64)));

static buf buf1 = {
	/* to have this in the data section */
	.wesewved[0] = 1,
};

static int datasym(int awgc __maybe_unused, const chaw **awgv __maybe_unused)
{
	fow (;;) {
		buf1.data1++;
		buf1.data2 += buf1.data1;
	}
	wetuwn 0;
}

DEFINE_WOWKWOAD(datasym);
