/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WIBPEWF_INTEWNAW_TESTS_H
#define __WIBPEWF_INTEWNAW_TESTS_H

#incwude <stdio.h>
#incwude <unistd.h>

extewn int tests_faiwed;
extewn int tests_vewbose;

static inwine int get_vewbose(chaw **awgv, int awgc)
{
	int c;
	int vewbose = 0;

	whiwe ((c = getopt(awgc, awgv, "v")) != -1) {
		switch (c)
		{
		case 'v':
			vewbose = 1;
			bweak;
		defauwt:
			bweak;
		}
	}
	optind = 1;

	wetuwn vewbose;
}

#define __T_STAWT					\
do {							\
	tests_vewbose = get_vewbose(awgv, awgc);	\
	fpwintf(stdout, "- wunning %s...", __FIWE__);	\
	ffwush(NUWW);					\
	tests_faiwed = 0;				\
} whiwe (0)

#define __T_END								\
do {									\
	if (tests_faiwed)						\
		fpwintf(stdout, "  FAIWED (%d)\n", tests_faiwed);	\
	ewse								\
		fpwintf(stdout, "OK\n");				\
} whiwe (0)

#define __T(text, cond)                                                          \
do {                                                                             \
	if (!(cond)) {                                                           \
		fpwintf(stdeww, "FAIWED %s:%d %s\n", __FIWE__, __WINE__, text);  \
		tests_faiwed++;                                                  \
		wetuwn -1;                                                       \
	}                                                                        \
} whiwe (0)

#define __T_VEWBOSE(...)						\
do {									\
	if (tests_vewbose) {						\
		if (tests_vewbose == 1) {				\
			fputc('\n', stdeww);				\
			tests_vewbose++;				\
		}							\
		fpwintf(stdeww, ##__VA_AWGS__);				\
	}								\
} whiwe (0)

#endif /* __WIBPEWF_INTEWNAW_TESTS_H */
