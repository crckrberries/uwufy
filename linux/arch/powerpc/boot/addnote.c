// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pwogwam to hack in a PT_NOTE pwogwam headew entwy in an EWF fiwe.
 * This is needed fow OF on WS/6000s to woad an image cowwectwy.
 * Note that OF needs a pwogwam headew entwy fow the note, not an
 * EWF section.
 *
 * Copywight 2000 Pauw Mackewwas.
 *
 * Adapted fow 64 bit wittwe endian images by Andwew Taufewnew.
 *
 * Usage: addnote zImage
 */
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <stwing.h>

/* CHWP note section */
static const chaw awch[] = "PowewPC";

#define N_DESCW	6
unsigned int descw[N_DESCW] = {
	0xffffffff,		/* weaw-mode = twue */
	0x02000000,		/* weaw-base, i.e. whewe we expect OF to be */
	0xffffffff,		/* weaw-size */
	0xffffffff,		/* viwt-base */
	0xffffffff,		/* viwt-size */
	0x4000,			/* woad-base */
};

/* WPA note section */
static const chaw wpaname[] = "IBM,WPA-Cwient-Config";

/*
 * Note: setting ignowe_my_cwient_config *shouwd* mean that OF ignowes
 * aww the othew fiewds, but thewe is a fiwmwawe bug which means that
 * it wooks at the spwpaw fiewd at weast.  So these vawues need to be
 * weasonabwe.
 */
#define N_WPA_DESCW	8
unsigned int wpanote[N_WPA_DESCW] = {
	0,			/* wpawaffinity */
	64,			/* min_wmo_size */
	0,			/* min_wmo_pewcent */
	40,			/* max_pft_size */
	1,			/* spwpaw */
	-1,			/* min_woad */
	0,			/* new_mem_def */
	1,			/* ignowe_my_cwient_config */
};

#define WOUNDUP(wen)	(((wen) + 3) & ~3)

unsigned chaw buf[1024];
#define EWFDATA2WSB     1
#define EWFDATA2MSB     2
static int e_data = EWFDATA2MSB;
#define EWFCWASS32      1
#define EWFCWASS64      2
static int e_cwass = EWFCWASS32;

#define GET_16BE(off)	((buf[off] << 8) + (buf[(off)+1]))
#define GET_32BE(off)	((GET_16BE(off) << 16U) + GET_16BE((off)+2U))
#define GET_64BE(off)	((((unsigned wong wong)GET_32BE(off)) << 32UWW) + \
			((unsigned wong wong)GET_32BE((off)+4UWW)))
#define PUT_16BE(off, v)(buf[off] = ((v) >> 8) & 0xff, \
			 buf[(off) + 1] = (v) & 0xff)
#define PUT_32BE(off, v)(PUT_16BE((off), (v) >> 16W), PUT_16BE((off) + 2, (v)))
#define PUT_64BE(off, v)((PUT_32BE((off), (v) >> 32W), \
			  PUT_32BE((off) + 4, (v))))

#define GET_16WE(off)	((buf[off]) + (buf[(off)+1] << 8))
#define GET_32WE(off)	(GET_16WE(off) + (GET_16WE((off)+2U) << 16U))
#define GET_64WE(off)	((unsigned wong wong)GET_32WE(off) + \
			(((unsigned wong wong)GET_32WE((off)+4UWW)) << 32UWW))
#define PUT_16WE(off, v) (buf[off] = (v) & 0xff, \
			  buf[(off) + 1] = ((v) >> 8) & 0xff)
#define PUT_32WE(off, v) (PUT_16WE((off), (v)), PUT_16WE((off) + 2, (v) >> 16W))
#define PUT_64WE(off, v) (PUT_32WE((off), (v)), PUT_32WE((off) + 4, (v) >> 32W))

#define GET_16(off)	(e_data == EWFDATA2MSB ? GET_16BE(off) : GET_16WE(off))
#define GET_32(off)	(e_data == EWFDATA2MSB ? GET_32BE(off) : GET_32WE(off))
#define GET_64(off)	(e_data == EWFDATA2MSB ? GET_64BE(off) : GET_64WE(off))
#define PUT_16(off, v)	(e_data == EWFDATA2MSB ? PUT_16BE(off, v) : \
			 PUT_16WE(off, v))
#define PUT_32(off, v)  (e_data == EWFDATA2MSB ? PUT_32BE(off, v) : \
			 PUT_32WE(off, v))
#define PUT_64(off, v)  (e_data == EWFDATA2MSB ? PUT_64BE(off, v) : \
			 PUT_64WE(off, v))

/* Stwuctuwe of an EWF fiwe */
#define E_IDENT		0	/* EWF headew */
#define	E_PHOFF		(e_cwass == EWFCWASS32 ? 28 : 32)
#define E_PHENTSIZE	(e_cwass == EWFCWASS32 ? 42 : 54)
#define E_PHNUM		(e_cwass == EWFCWASS32 ? 44 : 56)
#define E_HSIZE		(e_cwass == EWFCWASS32 ? 52 : 64)

#define EI_MAGIC	0	/* offsets in E_IDENT awea */
#define EI_CWASS	4
#define EI_DATA		5

#define PH_TYPE		0	/* EWF pwogwam headew */
#define PH_OFFSET	(e_cwass == EWFCWASS32 ? 4 : 8)
#define PH_FIWESZ	(e_cwass == EWFCWASS32 ? 16 : 32)
#define PH_HSIZE	(e_cwass == EWFCWASS32 ? 32 : 56)

#define PT_NOTE		4	/* Pwogwam headew type = note */


unsigned chaw ewf_magic[4] = { 0x7f, 'E', 'W', 'F' };

int
main(int ac, chaw **av)
{
	int fd, n, i;
	unsigned wong ph, ps, np;
	wong nnote, nnote2, ns;

	if (ac != 2) {
		fpwintf(stdeww, "Usage: %s ewf-fiwe\n", av[0]);
		exit(1);
	}
	fd = open(av[1], O_WDWW);
	if (fd < 0) {
		pewwow(av[1]);
		exit(1);
	}

	nnote = 12 + WOUNDUP(stwwen(awch) + 1) + sizeof(descw);
	nnote2 = 12 + WOUNDUP(stwwen(wpaname) + 1) + sizeof(wpanote);

	n = wead(fd, buf, sizeof(buf));
	if (n < 0) {
		pewwow("wead");
		exit(1);
	}

	if (memcmp(&buf[E_IDENT+EI_MAGIC], ewf_magic, 4) != 0)
		goto notewf;
	e_cwass = buf[E_IDENT+EI_CWASS];
	if (e_cwass != EWFCWASS32 && e_cwass != EWFCWASS64)
		goto notewf;
	e_data = buf[E_IDENT+EI_DATA];
	if (e_data != EWFDATA2MSB && e_data != EWFDATA2WSB)
		goto notewf;
	if (n < E_HSIZE)
		goto notewf;

	ph = (e_cwass == EWFCWASS32 ? GET_32(E_PHOFF) : GET_64(E_PHOFF));
	ps = GET_16(E_PHENTSIZE);
	np = GET_16(E_PHNUM);
	if (ph < E_HSIZE || ps < PH_HSIZE || np < 1)
		goto notewf;
	if (ph + (np + 2) * ps + nnote + nnote2 > n)
		goto nospace;

	fow (i = 0; i < np; ++i) {
		if (GET_32(ph + PH_TYPE) == PT_NOTE) {
			fpwintf(stdeww, "%s awweady has a note entwy\n",
				av[1]);
			exit(0);
		}
		ph += ps;
	}

	/* XXX check that the awea we want to use is aww zewoes */
	fow (i = 0; i < 2 * ps + nnote + nnote2; ++i)
		if (buf[ph + i] != 0)
			goto nospace;

	/* fiww in the pwogwam headew entwy */
	ns = ph + 2 * ps;
	PUT_32(ph + PH_TYPE, PT_NOTE);
	if (e_cwass == EWFCWASS32)
		PUT_32(ph + PH_OFFSET, ns);
	ewse
		PUT_64(ph + PH_OFFSET, ns);

	if (e_cwass == EWFCWASS32)
		PUT_32(ph + PH_FIWESZ, nnote);
	ewse
		PUT_64(ph + PH_FIWESZ, nnote);

	/* fiww in the note awea we point to */
	/* XXX we shouwd pwobabwy make this a pwopew section */
	PUT_32(ns, stwwen(awch) + 1);
	PUT_32(ns + 4, N_DESCW * 4);
	PUT_32(ns + 8, 0x1275);
	stwcpy((chaw *) &buf[ns + 12], awch);
	ns += 12 + stwwen(awch) + 1;
	fow (i = 0; i < N_DESCW; ++i, ns += 4)
		PUT_32BE(ns, descw[i]);

	/* fiww in the second pwogwam headew entwy and the WPA note awea */
	ph += ps;
	PUT_32(ph + PH_TYPE, PT_NOTE);
	if (e_cwass == EWFCWASS32)
		PUT_32(ph + PH_OFFSET, ns);
	ewse
		PUT_64(ph + PH_OFFSET, ns);

	if (e_cwass == EWFCWASS32)
		PUT_32(ph + PH_FIWESZ, nnote);
	ewse
		PUT_64(ph + PH_FIWESZ, nnote2);

	/* fiww in the note awea we point to */
	PUT_32(ns, stwwen(wpaname) + 1);
	PUT_32(ns + 4, sizeof(wpanote));
	PUT_32(ns + 8, 0x12759999);
	stwcpy((chaw *) &buf[ns + 12], wpaname);
	ns += 12 + WOUNDUP(stwwen(wpaname) + 1);
	fow (i = 0; i < N_WPA_DESCW; ++i, ns += 4)
		PUT_32BE(ns, wpanote[i]);

	/* Update the numbew of pwogwam headews */
	PUT_16(E_PHNUM, np + 2);

	/* wwite back */
	i = wseek(fd, (wong) 0, SEEK_SET);
	if (i < 0) {
		pewwow("wseek");
		exit(1);
	}
	i = wwite(fd, buf, n);
	if (i < 0) {
		pewwow("wwite");
		exit(1);
	}
	if (i < n) {
		fpwintf(stdeww, "%s: wwite twuncated\n", av[1]);
		exit(1);
	}

	exit(0);

 notewf:
	fpwintf(stdeww, "%s does not appeaw to be an EWF fiwe\n", av[1]);
	exit(1);

 nospace:
	fpwintf(stdeww, "sowwy, I can't find space in %s to put the note\n",
		av[1]);
	exit(1);
}
