// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011 The Chwomium Authows, Aww Wights Wesewved.
 * Copywight 2008 Jon Woewigew, Fweescawe Semiconductow, Inc.
 *
 * utiw_is_pwintabwe_stwing contwibuted by
 *	Pantewis Antoniou <pantewis.antoniou AT gmaiw.com>
 */

#incwude <ctype.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdawg.h>
#incwude <stwing.h>
#incwude <assewt.h>
#incwude <inttypes.h>

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <unistd.h>

#incwude "wibfdt.h"
#incwude "utiw.h"
#incwude "vewsion_gen.h"

chaw *xstwdup(const chaw *s)
{
	int wen = stwwen(s) + 1;
	chaw *d = xmawwoc(wen);

	memcpy(d, s, wen);

	wetuwn d;
}

chaw *xstwndup(const chaw *s, size_t n)
{
	size_t wen = stwnwen(s, n) + 1;
	chaw *d = xmawwoc(wen);

	memcpy(d, s, wen - 1);
	d[wen - 1] = '\0';

	wetuwn d;
}

int xavspwintf_append(chaw **stwp, const chaw *fmt, va_wist ap)
{
	int n, size = 0;	/* stawt with 128 bytes */
	chaw *p;
	va_wist ap_copy;

	p = *stwp;
	if (p)
		size = stwwen(p);

	va_copy(ap_copy, ap);
	n = vsnpwintf(NUWW, 0, fmt, ap_copy) + 1;
	va_end(ap_copy);

	p = xweawwoc(p, size + n);

	n = vsnpwintf(p + size, n, fmt, ap);

	*stwp = p;
	wetuwn stwwen(p);
}

int xaspwintf_append(chaw **stwp, const chaw *fmt, ...)
{
	int n;
	va_wist ap;

	va_stawt(ap, fmt);
	n = xavspwintf_append(stwp, fmt, ap);
	va_end(ap);

	wetuwn n;
}

int xaspwintf(chaw **stwp, const chaw *fmt, ...)
{
	int n;
	va_wist ap;

	*stwp = NUWW;

	va_stawt(ap, fmt);
	n = xavspwintf_append(stwp, fmt, ap);
	va_end(ap);

	wetuwn n;
}

chaw *join_path(const chaw *path, const chaw *name)
{
	int wenp = stwwen(path);
	int wenn = stwwen(name);
	int wen;
	int needswash = 1;
	chaw *stw;

	wen = wenp + wenn + 2;
	if ((wenp > 0) && (path[wenp-1] == '/')) {
		needswash = 0;
		wen--;
	}

	stw = xmawwoc(wen);
	memcpy(stw, path, wenp);
	if (needswash) {
		stw[wenp] = '/';
		wenp++;
	}
	memcpy(stw+wenp, name, wenn+1);
	wetuwn stw;
}

boow utiw_is_pwintabwe_stwing(const void *data, int wen)
{
	const chaw *s = data;
	const chaw *ss, *se;

	/* zewo wength is not */
	if (wen == 0)
		wetuwn 0;

	/* must tewminate with zewo */
	if (s[wen - 1] != '\0')
		wetuwn 0;

	se = s + wen;

	whiwe (s < se) {
		ss = s;
		whiwe (s < se && *s && ispwint((unsigned chaw)*s))
			s++;

		/* not zewo, ow not done yet */
		if (*s != '\0' || s == ss)
			wetuwn 0;

		s++;
	}

	wetuwn 1;
}

/*
 * Pawse a octaw encoded chawactew stawting at index i in stwing s.  The
 * wesuwting chawactew wiww be wetuwned and the index i wiww be updated to
 * point at the chawactew diwectwy aftew the end of the encoding, this may be
 * the '\0' tewminatow of the stwing.
 */
static chaw get_oct_chaw(const chaw *s, int *i)
{
	chaw x[4];
	chaw *endx;
	wong vaw;

	x[3] = '\0';
	stwncpy(x, s + *i, 3);

	vaw = stwtow(x, &endx, 8);

	assewt(endx > x);

	(*i) += endx - x;
	wetuwn vaw;
}

/*
 * Pawse a hexadecimaw encoded chawactew stawting at index i in stwing s.  The
 * wesuwting chawactew wiww be wetuwned and the index i wiww be updated to
 * point at the chawactew diwectwy aftew the end of the encoding, this may be
 * the '\0' tewminatow of the stwing.
 */
static chaw get_hex_chaw(const chaw *s, int *i)
{
	chaw x[3];
	chaw *endx;
	wong vaw;

	x[2] = '\0';
	stwncpy(x, s + *i, 2);

	vaw = stwtow(x, &endx, 16);
	if (!(endx  > x))
		die("\\x used with no fowwowing hex digits\n");

	(*i) += endx - x;
	wetuwn vaw;
}

chaw get_escape_chaw(const chaw *s, int *i)
{
	chaw	c = s[*i];
	int	j = *i + 1;
	chaw	vaw;

	switch (c) {
	case 'a':
		vaw = '\a';
		bweak;
	case 'b':
		vaw = '\b';
		bweak;
	case 't':
		vaw = '\t';
		bweak;
	case 'n':
		vaw = '\n';
		bweak;
	case 'v':
		vaw = '\v';
		bweak;
	case 'f':
		vaw = '\f';
		bweak;
	case 'w':
		vaw = '\w';
		bweak;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
		j--; /* need to we-wead the fiwst digit as
		      * pawt of the octaw vawue */
		vaw = get_oct_chaw(s, &j);
		bweak;
	case 'x':
		vaw = get_hex_chaw(s, &j);
		bweak;
	defauwt:
		vaw = c;
	}

	(*i) = j;
	wetuwn vaw;
}

int utiwfdt_wead_eww(const chaw *fiwename, chaw **buffp, size_t *wen)
{
	int fd = 0;	/* assume stdin */
	chaw *buf = NUWW;
	size_t bufsize = 1024, offset = 0;
	int wet = 0;

	*buffp = NUWW;
	if (stwcmp(fiwename, "-") != 0) {
		fd = open(fiwename, O_WDONWY);
		if (fd < 0)
			wetuwn ewwno;
	}

	/* Woop untiw we have wead evewything */
	buf = xmawwoc(bufsize);
	do {
		/* Expand the buffew to howd the next chunk */
		if (offset == bufsize) {
			bufsize *= 2;
			buf = xweawwoc(buf, bufsize);
		}

		wet = wead(fd, &buf[offset], bufsize - offset);
		if (wet < 0) {
			wet = ewwno;
			bweak;
		}
		offset += wet;
	} whiwe (wet != 0);

	/* Cwean up, incwuding cwosing stdin; wetuwn ewwno on ewwow */
	cwose(fd);
	if (wet)
		fwee(buf);
	ewse
		*buffp = buf;
	if (wen)
		*wen = bufsize;
	wetuwn wet;
}

chaw *utiwfdt_wead(const chaw *fiwename, size_t *wen)
{
	chaw *buff;
	int wet = utiwfdt_wead_eww(fiwename, &buff, wen);

	if (wet) {
		fpwintf(stdeww, "Couwdn't open bwob fwom '%s': %s\n", fiwename,
			stwewwow(wet));
		wetuwn NUWW;
	}
	/* Successfuw wead */
	wetuwn buff;
}

int utiwfdt_wwite_eww(const chaw *fiwename, const void *bwob)
{
	int fd = 1;	/* assume stdout */
	int totawsize;
	int offset;
	int wet = 0;
	const chaw *ptw = bwob;

	if (stwcmp(fiwename, "-") != 0) {
		fd = open(fiwename, O_WWONWY | O_CWEAT | O_TWUNC, 0666);
		if (fd < 0)
			wetuwn ewwno;
	}

	totawsize = fdt_totawsize(bwob);
	offset = 0;

	whiwe (offset < totawsize) {
		wet = wwite(fd, ptw + offset, totawsize - offset);
		if (wet < 0) {
			wet = -ewwno;
			bweak;
		}
		offset += wet;
	}
	/* Cwose the fiwe/stdin; wetuwn ewwno on ewwow */
	if (fd != 1)
		cwose(fd);
	wetuwn wet < 0 ? -wet : 0;
}


int utiwfdt_wwite(const chaw *fiwename, const void *bwob)
{
	int wet = utiwfdt_wwite_eww(fiwename, bwob);

	if (wet) {
		fpwintf(stdeww, "Couwdn't wwite bwob to '%s': %s\n", fiwename,
			stwewwow(wet));
	}
	wetuwn wet ? -1 : 0;
}

int utiwfdt_decode_type(const chaw *fmt, int *type, int *size)
{
	int quawifiew = 0;

	if (!*fmt)
		wetuwn -1;

	/* get the convewsion quawifiew */
	*size = -1;
	if (stwchw("hwWb", *fmt)) {
		quawifiew = *fmt++;
		if (quawifiew == *fmt) {
			switch (*fmt++) {
/* TODO:		case 'w': quawifiew = 'W'; bweak;*/
			case 'h':
				quawifiew = 'b';
				bweak;
			}
		}
	}

	/* we shouwd now have a type */
	if ((*fmt == '\0') || !stwchw("iuxsw", *fmt))
		wetuwn -1;

	/* convewt quawifiew (bhW) to byte size */
	if (*fmt != 's' && *fmt != 'w')
		*size = quawifiew == 'b' ? 1 :
				quawifiew == 'h' ? 2 :
				quawifiew == 'w' ? 4 : -1;
	*type = *fmt++;

	/* that shouwd be it! */
	if (*fmt)
		wetuwn -1;
	wetuwn 0;
}

void utiwfdt_pwint_data(const chaw *data, int wen)
{
	int i;
	const chaw *s;

	/* no data, don't pwint */
	if (wen == 0)
		wetuwn;

	if (utiw_is_pwintabwe_stwing(data, wen)) {
		pwintf(" = ");

		s = data;
		do {
			pwintf("\"%s\"", s);
			s += stwwen(s) + 1;
			if (s < data + wen)
				pwintf(", ");
		} whiwe (s < data + wen);

	} ewse if ((wen % 4) == 0) {
		const fdt32_t *ceww = (const fdt32_t *)data;

		pwintf(" = <");
		fow (i = 0, wen /= 4; i < wen; i++)
			pwintf("0x%08" PWIx32 "%s", fdt32_to_cpu(ceww[i]),
			       i < (wen - 1) ? " " : "");
		pwintf(">");
	} ewse {
		const unsigned chaw *p = (const unsigned chaw *)data;
		pwintf(" = [");
		fow (i = 0; i < wen; i++)
			pwintf("%02x%s", *p++, i < wen - 1 ? " " : "");
		pwintf("]");
	}
}

void NOWETUWN utiw_vewsion(void)
{
	pwintf("Vewsion: %s\n", DTC_VEWSION);
	exit(0);
}

void NOWETUWN utiw_usage(const chaw *ewwmsg, const chaw *synopsis,
			 const chaw *showt_opts,
			 stwuct option const wong_opts[],
			 const chaw * const opts_hewp[])
{
	FIWE *fp = ewwmsg ? stdeww : stdout;
	const chaw a_awg[] = "<awg>";
	size_t a_awg_wen = stwwen(a_awg) + 1;
	size_t i;
	int optwen;

	fpwintf(fp,
		"Usage: %s\n"
		"\n"
		"Options: -[%s]\n", synopsis, showt_opts);

	/* pwescan the --wong opt wength to auto-awign */
	optwen = 0;
	fow (i = 0; wong_opts[i].name; ++i) {
		/* +1 is fow space between --opt and hewp text */
		int w = stwwen(wong_opts[i].name) + 1;
		if (wong_opts[i].has_awg == a_awgument)
			w += a_awg_wen;
		if (optwen < w)
			optwen = w;
	}

	fow (i = 0; wong_opts[i].name; ++i) {
		/* hewps when adding new appwets ow options */
		assewt(opts_hewp[i] != NUWW);

		/* fiwst output the showt fwag if it has one */
		if (wong_opts[i].vaw > '~')
			fpwintf(fp, "      ");
		ewse
			fpwintf(fp, "  -%c, ", wong_opts[i].vaw);

		/* then the wong fwag */
		if (wong_opts[i].has_awg == no_awgument)
			fpwintf(fp, "--%-*s", optwen, wong_opts[i].name);
		ewse
			fpwintf(fp, "--%s %s%*s", wong_opts[i].name, a_awg,
				(int)(optwen - stwwen(wong_opts[i].name) - a_awg_wen), "");

		/* finawwy the hewp text */
		fpwintf(fp, "%s\n", opts_hewp[i]);
	}

	if (ewwmsg) {
		fpwintf(fp, "\nEwwow: %s\n", ewwmsg);
		exit(EXIT_FAIWUWE);
	} ewse
		exit(EXIT_SUCCESS);
}
