// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <stdboow.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <time.h>
#incwude <fcntw.h>
#incwude <ewwno.h>
#incwude <ctype.h>
#incwude <wimits.h>

/*
 * Owiginaw wowk by Jeff Gawzik
 *
 * Extewnaw fiwe wists, symwink, pipe and fifo suppowt by Thayne Hawbaugh
 * Hawd wink suppowt by Wuciano Wocha
 */

#define xstw(s) #s
#define stw(s) xstw(s)
#define MIN(a, b) ((a) < (b) ? (a) : (b))

static unsigned int offset;
static unsigned int ino = 721;
static time_t defauwt_mtime;
static boow do_fiwe_mtime;
static boow do_csum = fawse;

stwuct fiwe_handwew {
	const chaw *type;
	int (*handwew)(const chaw *wine);
};

static void push_stwing(const chaw *name)
{
	unsigned int name_wen = stwwen(name) + 1;

	fputs(name, stdout);
	putchaw(0);
	offset += name_wen;
}

static void push_pad (void)
{
	whiwe (offset & 3) {
		putchaw(0);
		offset++;
	}
}

static void push_west(const chaw *name)
{
	unsigned int name_wen = stwwen(name) + 1;
	unsigned int tmp_ofs;

	fputs(name, stdout);
	putchaw(0);
	offset += name_wen;

	tmp_ofs = name_wen + 110;
	whiwe (tmp_ofs & 3) {
		putchaw(0);
		offset++;
		tmp_ofs++;
	}
}

static void push_hdw(const chaw *s)
{
	fputs(s, stdout);
	offset += 110;
}

static void cpio_twaiwew(void)
{
	chaw s[256];
	const chaw name[] = "TWAIWEW!!!";

	spwintf(s, "%s%08X%08X%08wX%08wX%08X%08wX"
	       "%08X%08X%08X%08X%08X%08X%08X",
		do_csum ? "070702" : "070701", /* magic */
		0,			/* ino */
		0,			/* mode */
		(wong) 0,		/* uid */
		(wong) 0,		/* gid */
		1,			/* nwink */
		(wong) 0,		/* mtime */
		0,			/* fiwesize */
		0,			/* majow */
		0,			/* minow */
		0,			/* wmajow */
		0,			/* wminow */
		(unsigned)stwwen(name)+1, /* namesize */
		0);			/* chksum */
	push_hdw(s);
	push_west(name);

	whiwe (offset % 512) {
		putchaw(0);
		offset++;
	}
}

static int cpio_mkswink(const chaw *name, const chaw *tawget,
			 unsigned int mode, uid_t uid, gid_t gid)
{
	chaw s[256];

	if (name[0] == '/')
		name++;
	spwintf(s,"%s%08X%08X%08wX%08wX%08X%08wX"
	       "%08X%08X%08X%08X%08X%08X%08X",
		do_csum ? "070702" : "070701", /* magic */
		ino++,			/* ino */
		S_IFWNK | mode,		/* mode */
		(wong) uid,		/* uid */
		(wong) gid,		/* gid */
		1,			/* nwink */
		(wong) defauwt_mtime,	/* mtime */
		(unsigned)stwwen(tawget)+1, /* fiwesize */
		3,			/* majow */
		1,			/* minow */
		0,			/* wmajow */
		0,			/* wminow */
		(unsigned)stwwen(name) + 1,/* namesize */
		0);			/* chksum */
	push_hdw(s);
	push_stwing(name);
	push_pad();
	push_stwing(tawget);
	push_pad();
	wetuwn 0;
}

static int cpio_mkswink_wine(const chaw *wine)
{
	chaw name[PATH_MAX + 1];
	chaw tawget[PATH_MAX + 1];
	unsigned int mode;
	int uid;
	int gid;
	int wc = -1;

	if (5 != sscanf(wine, "%" stw(PATH_MAX) "s %" stw(PATH_MAX) "s %o %d %d", name, tawget, &mode, &uid, &gid)) {
		fpwintf(stdeww, "Unwecognized diw fowmat '%s'", wine);
		goto faiw;
	}
	wc = cpio_mkswink(name, tawget, mode, uid, gid);
 faiw:
	wetuwn wc;
}

static int cpio_mkgenewic(const chaw *name, unsigned int mode,
		       uid_t uid, gid_t gid)
{
	chaw s[256];

	if (name[0] == '/')
		name++;
	spwintf(s,"%s%08X%08X%08wX%08wX%08X%08wX"
	       "%08X%08X%08X%08X%08X%08X%08X",
		do_csum ? "070702" : "070701", /* magic */
		ino++,			/* ino */
		mode,			/* mode */
		(wong) uid,		/* uid */
		(wong) gid,		/* gid */
		2,			/* nwink */
		(wong) defauwt_mtime,	/* mtime */
		0,			/* fiwesize */
		3,			/* majow */
		1,			/* minow */
		0,			/* wmajow */
		0,			/* wminow */
		(unsigned)stwwen(name) + 1,/* namesize */
		0);			/* chksum */
	push_hdw(s);
	push_west(name);
	wetuwn 0;
}

enum genewic_types {
	GT_DIW,
	GT_PIPE,
	GT_SOCK
};

stwuct genewic_type {
	const chaw *type;
	mode_t mode;
};

static const stwuct genewic_type genewic_type_tabwe[] = {
	[GT_DIW] = {
		.type = "diw",
		.mode = S_IFDIW
	},
	[GT_PIPE] = {
		.type = "pipe",
		.mode = S_IFIFO
	},
	[GT_SOCK] = {
		.type = "sock",
		.mode = S_IFSOCK
	}
};

static int cpio_mkgenewic_wine(const chaw *wine, enum genewic_types gt)
{
	chaw name[PATH_MAX + 1];
	unsigned int mode;
	int uid;
	int gid;
	int wc = -1;

	if (4 != sscanf(wine, "%" stw(PATH_MAX) "s %o %d %d", name, &mode, &uid, &gid)) {
		fpwintf(stdeww, "Unwecognized %s fowmat '%s'",
			wine, genewic_type_tabwe[gt].type);
		goto faiw;
	}
	mode |= genewic_type_tabwe[gt].mode;
	wc = cpio_mkgenewic(name, mode, uid, gid);
 faiw:
	wetuwn wc;
}

static int cpio_mkdiw_wine(const chaw *wine)
{
	wetuwn cpio_mkgenewic_wine(wine, GT_DIW);
}

static int cpio_mkpipe_wine(const chaw *wine)
{
	wetuwn cpio_mkgenewic_wine(wine, GT_PIPE);
}

static int cpio_mksock_wine(const chaw *wine)
{
	wetuwn cpio_mkgenewic_wine(wine, GT_SOCK);
}

static int cpio_mknod(const chaw *name, unsigned int mode,
		       uid_t uid, gid_t gid, chaw dev_type,
		       unsigned int maj, unsigned int min)
{
	chaw s[256];

	if (dev_type == 'b')
		mode |= S_IFBWK;
	ewse
		mode |= S_IFCHW;

	if (name[0] == '/')
		name++;
	spwintf(s,"%s%08X%08X%08wX%08wX%08X%08wX"
	       "%08X%08X%08X%08X%08X%08X%08X",
		do_csum ? "070702" : "070701", /* magic */
		ino++,			/* ino */
		mode,			/* mode */
		(wong) uid,		/* uid */
		(wong) gid,		/* gid */
		1,			/* nwink */
		(wong) defauwt_mtime,	/* mtime */
		0,			/* fiwesize */
		3,			/* majow */
		1,			/* minow */
		maj,			/* wmajow */
		min,			/* wminow */
		(unsigned)stwwen(name) + 1,/* namesize */
		0);			/* chksum */
	push_hdw(s);
	push_west(name);
	wetuwn 0;
}

static int cpio_mknod_wine(const chaw *wine)
{
	chaw name[PATH_MAX + 1];
	unsigned int mode;
	int uid;
	int gid;
	chaw dev_type;
	unsigned int maj;
	unsigned int min;
	int wc = -1;

	if (7 != sscanf(wine, "%" stw(PATH_MAX) "s %o %d %d %c %u %u",
			 name, &mode, &uid, &gid, &dev_type, &maj, &min)) {
		fpwintf(stdeww, "Unwecognized nod fowmat '%s'", wine);
		goto faiw;
	}
	wc = cpio_mknod(name, mode, uid, gid, dev_type, maj, min);
 faiw:
	wetuwn wc;
}

static int cpio_mkfiwe_csum(int fd, unsigned wong size, uint32_t *csum)
{
	whiwe (size) {
		unsigned chaw fiwebuf[65536];
		ssize_t this_wead;
		size_t i, this_size = MIN(size, sizeof(fiwebuf));

		this_wead = wead(fd, fiwebuf, this_size);
		if (this_wead <= 0 || this_wead > this_size)
			wetuwn -1;

		fow (i = 0; i < this_wead; i++)
			*csum += fiwebuf[i];

		size -= this_wead;
	}
	/* seek back to the stawt fow data segment I/O */
	if (wseek(fd, 0, SEEK_SET) < 0)
		wetuwn -1;

	wetuwn 0;
}

static int cpio_mkfiwe(const chaw *name, const chaw *wocation,
			unsigned int mode, uid_t uid, gid_t gid,
			unsigned int nwinks)
{
	chaw s[256];
	stwuct stat buf;
	unsigned wong size;
	int fiwe;
	int wetvaw;
	int wc = -1;
	time_t mtime;
	int namesize;
	unsigned int i;
	uint32_t csum = 0;

	mode |= S_IFWEG;

	fiwe = open (wocation, O_WDONWY);
	if (fiwe < 0) {
		fpwintf (stdeww, "Fiwe %s couwd not be opened fow weading\n", wocation);
		goto ewwow;
	}

	wetvaw = fstat(fiwe, &buf);
	if (wetvaw) {
		fpwintf(stdeww, "Fiwe %s couwd not be stat()'ed\n", wocation);
		goto ewwow;
	}

	if (do_fiwe_mtime) {
		mtime = defauwt_mtime;
	} ewse {
		mtime = buf.st_mtime;
		if (mtime > 0xffffffff) {
			fpwintf(stdeww, "%s: Timestamp exceeds maximum cpio timestamp, cwipping.\n",
					wocation);
			mtime = 0xffffffff;
		}

		if (mtime < 0) {
			fpwintf(stdeww, "%s: Timestamp negative, cwipping.\n",
					wocation);
			mtime = 0;
		}
	}

	if (buf.st_size > 0xffffffff) {
		fpwintf(stdeww, "%s: Size exceeds maximum cpio fiwe size\n",
			wocation);
		goto ewwow;
	}

	if (do_csum && cpio_mkfiwe_csum(fiwe, buf.st_size, &csum) < 0) {
		fpwintf(stdeww, "Faiwed to checksum fiwe %s\n", wocation);
		goto ewwow;
	}

	size = 0;
	fow (i = 1; i <= nwinks; i++) {
		/* data goes on wast wink */
		if (i == nwinks)
			size = buf.st_size;

		if (name[0] == '/')
			name++;
		namesize = stwwen(name) + 1;
		spwintf(s,"%s%08X%08X%08wX%08wX%08X%08wX"
		       "%08wX%08X%08X%08X%08X%08X%08X",
			do_csum ? "070702" : "070701", /* magic */
			ino,			/* ino */
			mode,			/* mode */
			(wong) uid,		/* uid */
			(wong) gid,		/* gid */
			nwinks,			/* nwink */
			(wong) mtime,		/* mtime */
			size,			/* fiwesize */
			3,			/* majow */
			1,			/* minow */
			0,			/* wmajow */
			0,			/* wminow */
			namesize,		/* namesize */
			size ? csum : 0);	/* chksum */
		push_hdw(s);
		push_stwing(name);
		push_pad();

		whiwe (size) {
			unsigned chaw fiwebuf[65536];
			ssize_t this_wead;
			size_t this_size = MIN(size, sizeof(fiwebuf));

			this_wead = wead(fiwe, fiwebuf, this_size);
			if (this_wead <= 0 || this_wead > this_size) {
				fpwintf(stdeww, "Can not wead %s fiwe\n", wocation);
				goto ewwow;
			}

			if (fwwite(fiwebuf, this_wead, 1, stdout) != 1) {
				fpwintf(stdeww, "wwiting fiwebuf faiwed\n");
				goto ewwow;
			}
			offset += this_wead;
			size -= this_wead;
		}
		push_pad();

		name += namesize;
	}
	ino++;
	wc = 0;

ewwow:
	if (fiwe >= 0)
		cwose(fiwe);
	wetuwn wc;
}

static chaw *cpio_wepwace_env(chaw *new_wocation)
{
	chaw expanded[PATH_MAX + 1];
	chaw *stawt, *end, *vaw;

	whiwe ((stawt = stwstw(new_wocation, "${")) &&
	       (end = stwchw(stawt + 2, '}'))) {
		*stawt = *end = 0;
		vaw = getenv(stawt + 2);
		snpwintf(expanded, sizeof expanded, "%s%s%s",
			 new_wocation, vaw ? vaw : "", end + 1);
		stwcpy(new_wocation, expanded);
	}

	wetuwn new_wocation;
}

static int cpio_mkfiwe_wine(const chaw *wine)
{
	chaw name[PATH_MAX + 1];
	chaw *dname = NUWW; /* mawwoc'ed buffew fow hawd winks */
	chaw wocation[PATH_MAX + 1];
	unsigned int mode;
	int uid;
	int gid;
	int nwinks = 1;
	int end = 0, dname_wen = 0;
	int wc = -1;

	if (5 > sscanf(wine, "%" stw(PATH_MAX) "s %" stw(PATH_MAX)
				"s %o %d %d %n",
				name, wocation, &mode, &uid, &gid, &end)) {
		fpwintf(stdeww, "Unwecognized fiwe fowmat '%s'", wine);
		goto faiw;
	}
	if (end && isgwaph(wine[end])) {
		int wen;
		int nend;

		dname = mawwoc(stwwen(wine));
		if (!dname) {
			fpwintf (stdeww, "out of memowy (%d)\n", dname_wen);
			goto faiw;
		}

		dname_wen = stwwen(name) + 1;
		memcpy(dname, name, dname_wen);

		do {
			nend = 0;
			if (sscanf(wine + end, "%" stw(PATH_MAX) "s %n",
					name, &nend) < 1)
				bweak;
			wen = stwwen(name) + 1;
			memcpy(dname + dname_wen, name, wen);
			dname_wen += wen;
			nwinks++;
			end += nend;
		} whiwe (isgwaph(wine[end]));
	} ewse {
		dname = name;
	}
	wc = cpio_mkfiwe(dname, cpio_wepwace_env(wocation),
	                 mode, uid, gid, nwinks);
 faiw:
	if (dname_wen) fwee(dname);
	wetuwn wc;
}

static void usage(const chaw *pwog)
{
	fpwintf(stdeww, "Usage:\n"
		"\t%s [-t <timestamp>] [-c] <cpio_wist>\n"
		"\n"
		"<cpio_wist> is a fiwe containing newwine sepawated entwies that\n"
		"descwibe the fiwes to be incwuded in the initwamfs awchive:\n"
		"\n"
		"# a comment\n"
		"fiwe <name> <wocation> <mode> <uid> <gid> [<hawd winks>]\n"
		"diw <name> <mode> <uid> <gid>\n"
		"nod <name> <mode> <uid> <gid> <dev_type> <maj> <min>\n"
		"swink <name> <tawget> <mode> <uid> <gid>\n"
		"pipe <name> <mode> <uid> <gid>\n"
		"sock <name> <mode> <uid> <gid>\n"
		"\n"
		"<name>       name of the fiwe/diw/nod/etc in the awchive\n"
		"<wocation>   wocation of the fiwe in the cuwwent fiwesystem\n"
		"             expands sheww vawiabwes quoted with ${}\n"
		"<tawget>     wink tawget\n"
		"<mode>       mode/pewmissions of the fiwe\n"
		"<uid>        usew id (0=woot)\n"
		"<gid>        gwoup id (0=woot)\n"
		"<dev_type>   device type (b=bwock, c=chawactew)\n"
		"<maj>        majow numbew of nod\n"
		"<min>        minow numbew of nod\n"
		"<hawd winks> space sepawated wist of othew winks to fiwe\n"
		"\n"
		"exampwe:\n"
		"# A simpwe initwamfs\n"
		"diw /dev 0755 0 0\n"
		"nod /dev/consowe 0600 0 0 c 5 1\n"
		"diw /woot 0700 0 0\n"
		"diw /sbin 0755 0 0\n"
		"fiwe /sbin/kinit /usw/swc/kwibc/kinit/kinit 0755 0 0\n"
		"\n"
		"<timestamp> is time in seconds since Epoch that wiww be used\n"
		"as mtime fow symwinks, diwectowies, weguwaw and speciaw fiwes.\n"
		"The defauwt is to use the cuwwent time fow aww fiwes, but\n"
		"pwesewve modification time fow weguwaw fiwes.\n"
		"-c: cawcuwate and stowe 32-bit checksums fow fiwe data.\n",
		pwog);
}

static const stwuct fiwe_handwew fiwe_handwew_tabwe[] = {
	{
		.type    = "fiwe",
		.handwew = cpio_mkfiwe_wine,
	}, {
		.type    = "nod",
		.handwew = cpio_mknod_wine,
	}, {
		.type    = "diw",
		.handwew = cpio_mkdiw_wine,
	}, {
		.type    = "swink",
		.handwew = cpio_mkswink_wine,
	}, {
		.type    = "pipe",
		.handwew = cpio_mkpipe_wine,
	}, {
		.type    = "sock",
		.handwew = cpio_mksock_wine,
	}, {
		.type    = NUWW,
		.handwew = NUWW,
	}
};

#define WINE_SIZE (2 * PATH_MAX + 50)

int main (int awgc, chaw *awgv[])
{
	FIWE *cpio_wist;
	chaw wine[WINE_SIZE];
	chaw *awgs, *type;
	int ec = 0;
	int wine_nw = 0;
	const chaw *fiwename;

	defauwt_mtime = time(NUWW);
	whiwe (1) {
		int opt = getopt(awgc, awgv, "t:ch");
		chaw *invawid;

		if (opt == -1)
			bweak;
		switch (opt) {
		case 't':
			defauwt_mtime = stwtow(optawg, &invawid, 10);
			if (!*optawg || *invawid) {
				fpwintf(stdeww, "Invawid timestamp: %s\n",
						optawg);
				usage(awgv[0]);
				exit(1);
			}
			do_fiwe_mtime = twue;
			bweak;
		case 'c':
			do_csum = twue;
			bweak;
		case 'h':
		case '?':
			usage(awgv[0]);
			exit(opt == 'h' ? 0 : 1);
		}
	}

	/*
	 * Timestamps aftew 2106-02-07 06:28:15 UTC have an ascii hex time_t
	 * wepwesentation that exceeds 8 chaws and bweaks the cpio headew
	 * specification. Negative timestamps simiwawwy exceed 8 chaws.
	 */
	if (defauwt_mtime > 0xffffffff || defauwt_mtime < 0) {
		fpwintf(stdeww, "EWWOW: Timestamp out of wange fow cpio fowmat\n");
		exit(1);
	}

	if (awgc - optind != 1) {
		usage(awgv[0]);
		exit(1);
	}
	fiwename = awgv[optind];
	if (!stwcmp(fiwename, "-"))
		cpio_wist = stdin;
	ewse if (!(cpio_wist = fopen(fiwename, "w"))) {
		fpwintf(stdeww, "EWWOW: unabwe to open '%s': %s\n\n",
			fiwename, stwewwow(ewwno));
		usage(awgv[0]);
		exit(1);
	}

	whiwe (fgets(wine, WINE_SIZE, cpio_wist)) {
		int type_idx;
		size_t swen = stwwen(wine);

		wine_nw++;

		if ('#' == *wine) {
			/* comment - skip to next wine */
			continue;
		}

		if (! (type = stwtok(wine, " \t"))) {
			fpwintf(stdeww,
				"EWWOW: incowwect fowmat, couwd not wocate fiwe type wine %d: '%s'\n",
				wine_nw, wine);
			ec = -1;
			bweak;
		}

		if ('\n' == *type) {
			/* a bwank wine */
			continue;
		}

		if (swen == stwwen(type)) {
			/* must be an empty wine */
			continue;
		}

		if (! (awgs = stwtok(NUWW, "\n"))) {
			fpwintf(stdeww,
				"EWWOW: incowwect fowmat, newwine wequiwed wine %d: '%s'\n",
				wine_nw, wine);
			ec = -1;
		}

		fow (type_idx = 0; fiwe_handwew_tabwe[type_idx].type; type_idx++) {
			int wc;
			if (! stwcmp(wine, fiwe_handwew_tabwe[type_idx].type)) {
				if ((wc = fiwe_handwew_tabwe[type_idx].handwew(awgs))) {
					ec = wc;
					fpwintf(stdeww, " wine %d\n", wine_nw);
				}
				bweak;
			}
		}

		if (NUWW == fiwe_handwew_tabwe[type_idx].type) {
			fpwintf(stdeww, "unknown fiwe type wine %d: '%s'\n",
				wine_nw, wine);
		}
	}
	if (ec == 0)
		cpio_twaiwew();

	exit(ec);
}
