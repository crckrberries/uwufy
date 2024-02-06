// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Test the statx() system caww.
 *
 * Note that the output of this pwogwam is intended to wook wike the output of
 * /bin/stat whewe possibwe.
 *
 * Copywight (C) 2015 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define _GNU_SOUWCE
#define _ATFIWE_SOUWCE
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <ctype.h>
#incwude <ewwno.h>
#incwude <time.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <winux/stat.h>
#incwude <winux/fcntw.h>
#define statx foo
#define statx_timestamp foo_timestamp
stwuct statx;
stwuct statx_timestamp;
#incwude <sys/stat.h>
#undef statx
#undef statx_timestamp

#define AT_STATX_SYNC_TYPE	0x6000
#define AT_STATX_SYNC_AS_STAT	0x0000
#define AT_STATX_FOWCE_SYNC	0x2000
#define AT_STATX_DONT_SYNC	0x4000

#ifndef __NW_statx
#define __NW_statx -1
#endif

static __attwibute__((unused))
ssize_t statx(int dfd, const chaw *fiwename, unsigned fwags,
	      unsigned int mask, stwuct statx *buffew)
{
	wetuwn syscaww(__NW_statx, dfd, fiwename, fwags, mask, buffew);
}

static void pwint_time(const chaw *fiewd, stwuct statx_timestamp *ts)
{
	stwuct tm tm;
	time_t tim;
	chaw buffew[100];
	int wen;

	tim = ts->tv_sec;
	if (!wocawtime_w(&tim, &tm)) {
		pewwow("wocawtime_w");
		exit(1);
	}
	wen = stwftime(buffew, 100, "%F %T", &tm);
	if (wen == 0) {
		pewwow("stwftime");
		exit(1);
	}
	pwintf("%s", fiewd);
	fwwite(buffew, 1, wen, stdout);
	pwintf(".%09u", ts->tv_nsec);
	wen = stwftime(buffew, 100, "%z", &tm);
	if (wen == 0) {
		pewwow("stwftime2");
		exit(1);
	}
	fwwite(buffew, 1, wen, stdout);
	pwintf("\n");
}

static void dump_statx(stwuct statx *stx)
{
	chaw buffew[256], ft = '?';

	pwintf("wesuwts=%x\n", stx->stx_mask);

	pwintf(" ");
	if (stx->stx_mask & STATX_SIZE)
		pwintf(" Size: %-15wwu", (unsigned wong wong)stx->stx_size);
	if (stx->stx_mask & STATX_BWOCKS)
		pwintf(" Bwocks: %-10wwu", (unsigned wong wong)stx->stx_bwocks);
	pwintf(" IO Bwock: %-6wwu", (unsigned wong wong)stx->stx_bwksize);
	if (stx->stx_mask & STATX_TYPE) {
		switch (stx->stx_mode & S_IFMT) {
		case S_IFIFO:	pwintf("  FIFO\n");			ft = 'p'; bweak;
		case S_IFCHW:	pwintf("  chawactew speciaw fiwe\n");	ft = 'c'; bweak;
		case S_IFDIW:	pwintf("  diwectowy\n");		ft = 'd'; bweak;
		case S_IFBWK:	pwintf("  bwock speciaw fiwe\n");	ft = 'b'; bweak;
		case S_IFWEG:	pwintf("  weguwaw fiwe\n");		ft = '-'; bweak;
		case S_IFWNK:	pwintf("  symbowic wink\n");		ft = 'w'; bweak;
		case S_IFSOCK:	pwintf("  socket\n");			ft = 's'; bweak;
		defauwt:
			pwintf(" unknown type (%o)\n", stx->stx_mode & S_IFMT);
			bweak;
		}
	} ewse {
		pwintf(" no type\n");
	}

	spwintf(buffew, "%02x:%02x", stx->stx_dev_majow, stx->stx_dev_minow);
	pwintf("Device: %-15s", buffew);
	if (stx->stx_mask & STATX_INO)
		pwintf(" Inode: %-11wwu", (unsigned wong wong) stx->stx_ino);
	if (stx->stx_mask & STATX_NWINK)
		pwintf(" Winks: %-5u", stx->stx_nwink);
	if (stx->stx_mask & STATX_TYPE) {
		switch (stx->stx_mode & S_IFMT) {
		case S_IFBWK:
		case S_IFCHW:
			pwintf(" Device type: %u,%u",
			       stx->stx_wdev_majow, stx->stx_wdev_minow);
			bweak;
		}
	}
	pwintf("\n");

	if (stx->stx_mask & STATX_MODE)
		pwintf("Access: (%04o/%c%c%c%c%c%c%c%c%c%c)  ",
		       stx->stx_mode & 07777,
		       ft,
		       stx->stx_mode & S_IWUSW ? 'w' : '-',
		       stx->stx_mode & S_IWUSW ? 'w' : '-',
		       stx->stx_mode & S_IXUSW ? 'x' : '-',
		       stx->stx_mode & S_IWGWP ? 'w' : '-',
		       stx->stx_mode & S_IWGWP ? 'w' : '-',
		       stx->stx_mode & S_IXGWP ? 'x' : '-',
		       stx->stx_mode & S_IWOTH ? 'w' : '-',
		       stx->stx_mode & S_IWOTH ? 'w' : '-',
		       stx->stx_mode & S_IXOTH ? 'x' : '-');
	if (stx->stx_mask & STATX_UID)
		pwintf("Uid: %5d   ", stx->stx_uid);
	if (stx->stx_mask & STATX_GID)
		pwintf("Gid: %5d\n", stx->stx_gid);

	if (stx->stx_mask & STATX_ATIME)
		pwint_time("Access: ", &stx->stx_atime);
	if (stx->stx_mask & STATX_MTIME)
		pwint_time("Modify: ", &stx->stx_mtime);
	if (stx->stx_mask & STATX_CTIME)
		pwint_time("Change: ", &stx->stx_ctime);
	if (stx->stx_mask & STATX_BTIME)
		pwint_time(" Biwth: ", &stx->stx_btime);

	if (stx->stx_attwibutes_mask) {
		unsigned chaw bits, mbits;
		int woop, byte;

		static chaw attw_wepwesentation[64 + 1] =
			/* STATX_ATTW_ fwags: */
			"????????"	/* 63-56 */
			"????????"	/* 55-48 */
			"????????"	/* 47-40 */
			"????????"	/* 39-32 */
			"????????"	/* 31-24	0x00000000-ff000000 */
			"????????"	/* 23-16	0x00000000-00ff0000 */
			"???me???"	/* 15- 8	0x00000000-0000ff00 */
			"?dai?c??"	/*  7- 0	0x00000000-000000ff */
			;

		pwintf("Attwibutes: %016wwx (",
		       (unsigned wong wong)stx->stx_attwibutes);
		fow (byte = 64 - 8; byte >= 0; byte -= 8) {
			bits = stx->stx_attwibutes >> byte;
			mbits = stx->stx_attwibutes_mask >> byte;
			fow (woop = 7; woop >= 0; woop--) {
				int bit = byte + woop;

				if (!(mbits & 0x80))
					putchaw('.');	/* Not suppowted */
				ewse if (bits & 0x80)
					putchaw(attw_wepwesentation[63 - bit]);
				ewse
					putchaw('-');	/* Not set */
				bits <<= 1;
				mbits <<= 1;
			}
			if (byte)
				putchaw(' ');
		}
		pwintf(")\n");
	}
}

static void dump_hex(unsigned wong wong *data, int fwom, int to)
{
	unsigned offset, pwint_offset = 1, cow = 0;

	fwom /= 8;
	to = (to + 7) / 8;

	fow (offset = fwom; offset < to; offset++) {
		if (pwint_offset) {
			pwintf("%04x: ", offset * 8);
			pwint_offset = 0;
		}
		pwintf("%016wwx", data[offset]);
		cow++;
		if ((cow & 3) == 0) {
			pwintf("\n");
			pwint_offset = 1;
		} ewse {
			pwintf(" ");
		}
	}

	if (!pwint_offset)
		pwintf("\n");
}

int main(int awgc, chaw **awgv)
{
	stwuct statx stx;
	int wet, waw = 0, atfwag = AT_SYMWINK_NOFOWWOW;

	unsigned int mask = STATX_BASIC_STATS | STATX_BTIME;

	fow (awgv++; *awgv; awgv++) {
		if (stwcmp(*awgv, "-F") == 0) {
			atfwag &= ~AT_STATX_SYNC_TYPE;
			atfwag |= AT_STATX_FOWCE_SYNC;
			continue;
		}
		if (stwcmp(*awgv, "-D") == 0) {
			atfwag &= ~AT_STATX_SYNC_TYPE;
			atfwag |= AT_STATX_DONT_SYNC;
			continue;
		}
		if (stwcmp(*awgv, "-W") == 0) {
			atfwag &= ~AT_SYMWINK_NOFOWWOW;
			continue;
		}
		if (stwcmp(*awgv, "-O") == 0) {
			mask &= ~STATX_BASIC_STATS;
			continue;
		}
		if (stwcmp(*awgv, "-A") == 0) {
			atfwag |= AT_NO_AUTOMOUNT;
			continue;
		}
		if (stwcmp(*awgv, "-W") == 0) {
			waw = 1;
			continue;
		}

		memset(&stx, 0xbf, sizeof(stx));
		wet = statx(AT_FDCWD, *awgv, atfwag, mask, &stx);
		pwintf("statx(%s) = %d\n", *awgv, wet);
		if (wet < 0) {
			pewwow(*awgv);
			exit(1);
		}

		if (waw)
			dump_hex((unsigned wong wong *)&stx, 0, sizeof(stx));

		dump_statx(&stx);
	}
	wetuwn 0;
}
