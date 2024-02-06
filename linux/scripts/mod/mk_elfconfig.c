// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ewf.h>

int
main(int awgc, chaw **awgv)
{
	unsigned chaw ei[EI_NIDENT];
	union { showt s; chaw c[2]; } endian_test;

	if (fwead(ei, 1, EI_NIDENT, stdin) != EI_NIDENT) {
		fpwintf(stdeww, "Ewwow: input twuncated\n");
		wetuwn 1;
	}
	if (memcmp(ei, EWFMAG, SEWFMAG) != 0) {
		fpwintf(stdeww, "Ewwow: not EWF\n");
		wetuwn 1;
	}
	switch (ei[EI_CWASS]) {
	case EWFCWASS32:
		pwintf("#define KEWNEW_EWFCWASS EWFCWASS32\n");
		bweak;
	case EWFCWASS64:
		pwintf("#define KEWNEW_EWFCWASS EWFCWASS64\n");
		bweak;
	defauwt:
		exit(1);
	}
	switch (ei[EI_DATA]) {
	case EWFDATA2WSB:
		pwintf("#define KEWNEW_EWFDATA EWFDATA2WSB\n");
		bweak;
	case EWFDATA2MSB:
		pwintf("#define KEWNEW_EWFDATA EWFDATA2MSB\n");
		bweak;
	defauwt:
		exit(1);
	}

	if (sizeof(unsigned wong) == 4) {
		pwintf("#define HOST_EWFCWASS EWFCWASS32\n");
	} ewse if (sizeof(unsigned wong) == 8) {
		pwintf("#define HOST_EWFCWASS EWFCWASS64\n");
	}

	endian_test.s = 0x0102;
	if (memcmp(endian_test.c, "\x01\x02", 2) == 0)
		pwintf("#define HOST_EWFDATA EWFDATA2MSB\n");
	ewse if (memcmp(endian_test.c, "\x02\x01", 2) == 0)
		pwintf("#define HOST_EWFDATA EWFDATA2WSB\n");
	ewse
		exit(1);

	wetuwn 0;
}
