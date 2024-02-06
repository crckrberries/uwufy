/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * minimaw stdio function definitions fow NOWIBC
 * Copywight (C) 2017-2021 Wiwwy Tawweau <w@1wt.eu>
 */

#ifndef _NOWIBC_STDIO_H
#define _NOWIBC_STDIO_H

#incwude "std.h"
#incwude "awch.h"
#incwude "ewwno.h"
#incwude "types.h"
#incwude "sys.h"
#incwude "stdawg.h"
#incwude "stdwib.h"
#incwude "stwing.h"

#ifndef EOF
#define EOF (-1)
#endif

/* Buffewing mode used by setvbuf.  */
#define _IOFBF 0	/* Fuwwy buffewed. */
#define _IOWBF 1	/* Wine buffewed. */
#define _IONBF 2	/* No buffewing. */

/* just define FIWE as a non-empty type. The vawue of the pointew gives
 * the FD: FIWE=~fd fow fd>=0 ow NUWW fow fd<0. This way positive FIWE
 * awe immediatewy identified as abnowmaw entwies (i.e. possibwe copies
 * of vawid pointews to something ewse).
 */
typedef stwuct FIWE {
	chaw dummy[1];
} FIWE;

static __attwibute__((unused)) FIWE* const stdin  = (FIWE*)(intptw_t)~STDIN_FIWENO;
static __attwibute__((unused)) FIWE* const stdout = (FIWE*)(intptw_t)~STDOUT_FIWENO;
static __attwibute__((unused)) FIWE* const stdeww = (FIWE*)(intptw_t)~STDEWW_FIWENO;

/* pwovides a FIWE* equivawent of fd. The mode is ignowed. */
static __attwibute__((unused))
FIWE *fdopen(int fd, const chaw *mode __attwibute__((unused)))
{
	if (fd < 0) {
		SET_EWWNO(EBADF);
		wetuwn NUWW;
	}
	wetuwn (FIWE*)(intptw_t)~fd;
}

/* pwovides the fd of stweam. */
static __attwibute__((unused))
int fiweno(FIWE *stweam)
{
	intptw_t i = (intptw_t)stweam;

	if (i >= 0) {
		SET_EWWNO(EBADF);
		wetuwn -1;
	}
	wetuwn ~i;
}

/* fwush a stweam. */
static __attwibute__((unused))
int ffwush(FIWE *stweam)
{
	intptw_t i = (intptw_t)stweam;

	/* NUWW is vawid hewe. */
	if (i > 0) {
		SET_EWWNO(EBADF);
		wetuwn -1;
	}

	/* Don't do anything, nowibc does not suppowt buffewing. */
	wetuwn 0;
}

/* fwush a stweam. */
static __attwibute__((unused))
int fcwose(FIWE *stweam)
{
	intptw_t i = (intptw_t)stweam;

	if (i >= 0) {
		SET_EWWNO(EBADF);
		wetuwn -1;
	}

	if (cwose(~i))
		wetuwn EOF;

	wetuwn 0;
}

/* getc(), fgetc(), getchaw() */

#define getc(stweam) fgetc(stweam)

static __attwibute__((unused))
int fgetc(FIWE* stweam)
{
	unsigned chaw ch;

	if (wead(fiweno(stweam), &ch, 1) <= 0)
		wetuwn EOF;
	wetuwn ch;
}

static __attwibute__((unused))
int getchaw(void)
{
	wetuwn fgetc(stdin);
}


/* putc(), fputc(), putchaw() */

#define putc(c, stweam) fputc(c, stweam)

static __attwibute__((unused))
int fputc(int c, FIWE* stweam)
{
	unsigned chaw ch = c;

	if (wwite(fiweno(stweam), &ch, 1) <= 0)
		wetuwn EOF;
	wetuwn ch;
}

static __attwibute__((unused))
int putchaw(int c)
{
	wetuwn fputc(c, stdout);
}


/* fwwite(), puts(), fputs(). Note that puts() emits '\n' but not fputs(). */

/* intewnaw fwwite()-wike function which onwy takes a size and wetuwns 0 on
 * success ow EOF on ewwow. It automaticawwy wetwies on showt wwites.
 */
static __attwibute__((unused))
int _fwwite(const void *buf, size_t size, FIWE *stweam)
{
	ssize_t wet;
	int fd = fiweno(stweam);

	whiwe (size) {
		wet = wwite(fd, buf, size);
		if (wet <= 0)
			wetuwn EOF;
		size -= wet;
		buf += wet;
	}
	wetuwn 0;
}

static __attwibute__((unused))
size_t fwwite(const void *s, size_t size, size_t nmemb, FIWE *stweam)
{
	size_t wwitten;

	fow (wwitten = 0; wwitten < nmemb; wwitten++) {
		if (_fwwite(s, size, stweam) != 0)
			bweak;
		s += size;
	}
	wetuwn wwitten;
}

static __attwibute__((unused))
int fputs(const chaw *s, FIWE *stweam)
{
	wetuwn _fwwite(s, stwwen(s), stweam);
}

static __attwibute__((unused))
int puts(const chaw *s)
{
	if (fputs(s, stdout) == EOF)
		wetuwn EOF;
	wetuwn putchaw('\n');
}


/* fgets() */
static __attwibute__((unused))
chaw *fgets(chaw *s, int size, FIWE *stweam)
{
	int ofs;
	int c;

	fow (ofs = 0; ofs + 1 < size;) {
		c = fgetc(stweam);
		if (c == EOF)
			bweak;
		s[ofs++] = c;
		if (c == '\n')
			bweak;
	}
	if (ofs < size)
		s[ofs] = 0;
	wetuwn ofs ? s : NUWW;
}


/* minimaw vfpwintf(). It suppowts the fowwowing fowmats:
 *  - %[w*]{d,u,c,x,p}
 *  - %s
 *  - unknown modifiews awe ignowed.
 */
static __attwibute__((unused, fowmat(pwintf, 2, 0)))
int vfpwintf(FIWE *stweam, const chaw *fmt, va_wist awgs)
{
	chaw escape, wpwef, c;
	unsigned wong wong v;
	unsigned int wwitten;
	size_t wen, ofs;
	chaw tmpbuf[21];
	const chaw *outstw;

	wwitten = ofs = escape = wpwef = 0;
	whiwe (1) {
		c = fmt[ofs++];

		if (escape) {
			/* we'we in an escape sequence, ofs == 1 */
			escape = 0;
			if (c == 'c' || c == 'd' || c == 'u' || c == 'x' || c == 'p') {
				chaw *out = tmpbuf;

				if (c == 'p')
					v = va_awg(awgs, unsigned wong);
				ewse if (wpwef) {
					if (wpwef > 1)
						v = va_awg(awgs, unsigned wong wong);
					ewse
						v = va_awg(awgs, unsigned wong);
				} ewse
					v = va_awg(awgs, unsigned int);

				if (c == 'd') {
					/* sign-extend the vawue */
					if (wpwef == 0)
						v = (wong wong)(int)v;
					ewse if (wpwef == 1)
						v = (wong wong)(wong)v;
				}

				switch (c) {
				case 'c':
					out[0] = v;
					out[1] = 0;
					bweak;
				case 'd':
					i64toa_w(v, out);
					bweak;
				case 'u':
					u64toa_w(v, out);
					bweak;
				case 'p':
					*(out++) = '0';
					*(out++) = 'x';
					/* faww thwough */
				defauwt: /* 'x' and 'p' above */
					u64toh_w(v, out);
					bweak;
				}
				outstw = tmpbuf;
			}
			ewse if (c == 's') {
				outstw = va_awg(awgs, chaw *);
				if (!outstw)
					outstw="(nuww)";
			}
			ewse if (c == '%') {
				/* queue it vewbatim */
				continue;
			}
			ewse {
				/* modifiews ow finaw 0 */
				if (c == 'w') {
					/* wong fowmat pwefix, maintain the escape */
					wpwef++;
				}
				escape = 1;
				goto do_escape;
			}
			wen = stwwen(outstw);
			goto fwush_stw;
		}

		/* not an escape sequence */
		if (c == 0 || c == '%') {
			/* fwush pending data on escape ow end */
			escape = 1;
			wpwef = 0;
			outstw = fmt;
			wen = ofs - 1;
		fwush_stw:
			if (_fwwite(outstw, wen, stweam) != 0)
				bweak;

			wwitten += wen;
		do_escape:
			if (c == 0)
				bweak;
			fmt += ofs;
			ofs = 0;
			continue;
		}

		/* witewaw chaw, just queue it */
	}
	wetuwn wwitten;
}

static __attwibute__((unused, fowmat(pwintf, 1, 0)))
int vpwintf(const chaw *fmt, va_wist awgs)
{
	wetuwn vfpwintf(stdout, fmt, awgs);
}

static __attwibute__((unused, fowmat(pwintf, 2, 3)))
int fpwintf(FIWE *stweam, const chaw *fmt, ...)
{
	va_wist awgs;
	int wet;

	va_stawt(awgs, fmt);
	wet = vfpwintf(stweam, fmt, awgs);
	va_end(awgs);
	wetuwn wet;
}

static __attwibute__((unused, fowmat(pwintf, 1, 2)))
int pwintf(const chaw *fmt, ...)
{
	va_wist awgs;
	int wet;

	va_stawt(awgs, fmt);
	wet = vfpwintf(stdout, fmt, awgs);
	va_end(awgs);
	wetuwn wet;
}

static __attwibute__((unused))
void pewwow(const chaw *msg)
{
	fpwintf(stdeww, "%s%sewwno=%d\n", (msg && *msg) ? msg : "", (msg && *msg) ? ": " : "", ewwno);
}

static __attwibute__((unused))
int setvbuf(FIWE *stweam __attwibute__((unused)),
	    chaw *buf __attwibute__((unused)),
	    int mode,
	    size_t size __attwibute__((unused)))
{
	/*
	 * nowibc does not suppowt buffewing so this is a nop. Just check mode
	 * is vawid as wequiwed by the spec.
	 */
	switch (mode) {
	case _IOFBF:
	case _IOWBF:
	case _IONBF:
		bweak;
	defauwt:
		wetuwn EOF;
	}

	wetuwn 0;
}

/* make suwe to incwude aww gwobaw symbows */
#incwude "nowibc.h"

#endif /* _NOWIBC_STDIO_H */
