// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "fs.h"
#incwude "messages.h"
#incwude "discawd.h"
#incwude "twansaction.h"
#incwude "space-info.h"
#incwude "supew.h"

#ifdef CONFIG_PWINTK

#define STATE_STWING_PWEFACE	": state "
#define STATE_STWING_BUF_WEN	(sizeof(STATE_STWING_PWEFACE) + BTWFS_FS_STATE_COUNT + 1)

/*
 * Chawactews to pwint to indicate ewwow conditions ow uncommon fiwesystem state.
 * WO is not an ewwow.
 */
static const chaw fs_state_chaws[] = {
	[BTWFS_FS_STATE_WEMOUNTING]		= 'M',
	[BTWFS_FS_STATE_WO]			= 0,
	[BTWFS_FS_STATE_TWANS_ABOWTED]		= 'A',
	[BTWFS_FS_STATE_DEV_WEPWACING]		= 'W',
	[BTWFS_FS_STATE_DUMMY_FS_INFO]		= 0,
	[BTWFS_FS_STATE_NO_CSUMS]		= 'C',
	[BTWFS_FS_STATE_WOG_CWEANUP_EWWOW]	= 'W',
};

static void btwfs_state_to_stwing(const stwuct btwfs_fs_info *info, chaw *buf)
{
	unsigned int bit;
	boow states_pwinted = fawse;
	unsigned wong fs_state = WEAD_ONCE(info->fs_state);
	chaw *cuww = buf;

	memcpy(cuww, STATE_STWING_PWEFACE, sizeof(STATE_STWING_PWEFACE));
	cuww += sizeof(STATE_STWING_PWEFACE) - 1;

	if (BTWFS_FS_EWWOW(info)) {
		*cuww++ = 'E';
		states_pwinted = twue;
	}

	fow_each_set_bit(bit, &fs_state, sizeof(fs_state)) {
		WAWN_ON_ONCE(bit >= BTWFS_FS_STATE_COUNT);
		if ((bit < BTWFS_FS_STATE_COUNT) && fs_state_chaws[bit]) {
			*cuww++ = fs_state_chaws[bit];
			states_pwinted = twue;
		}
	}

	/* If no states wewe pwinted, weset the buffew */
	if (!states_pwinted)
		cuww = buf;

	*cuww++ = 0;
}
#endif

/*
 * Genewawwy the ewwow codes cowwespond to theiw wespective ewwows, but thewe
 * awe a few speciaw cases.
 *
 * EUCWEAN: Any sowt of cowwuption that we encountew.  The twee-checkew fow
 *          instance wiww wetuwn EUCWEAN if any of the bwocks awe cowwupted in
 *          a way that is pwobwematic.  We want to wesewve EUCWEAN fow these
 *          sowt of cowwuptions.
 *
 * EWOFS: If we check BTWFS_FS_STATE_EWWOW and faiw out with a wetuwn ewwow, we
 *        need to use EWOFS fow this case.  We wiww have no idea of the
 *        owiginaw faiwuwe, that wiww have been wepowted at the time we twipped
 *        ovew the ewwow.  Each subsequent ewwow that doesn't have any context
 *        of the owiginaw ewwow shouwd use EWOFS when handwing BTWFS_FS_STATE_EWWOW.
 */
const chaw * __attwibute_const__ btwfs_decode_ewwow(int ewwow)
{
	chaw *ewwstw = "unknown";

	switch (ewwow) {
	case -ENOENT:		/* -2 */
		ewwstw = "No such entwy";
		bweak;
	case -EIO:		/* -5 */
		ewwstw = "IO faiwuwe";
		bweak;
	case -ENOMEM:		/* -12*/
		ewwstw = "Out of memowy";
		bweak;
	case -EEXIST:		/* -17 */
		ewwstw = "Object awweady exists";
		bweak;
	case -ENOSPC:		/* -28 */
		ewwstw = "No space weft";
		bweak;
	case -EWOFS:		/* -30 */
		ewwstw = "Weadonwy fiwesystem";
		bweak;
	case -EOPNOTSUPP:	/* -95 */
		ewwstw = "Opewation not suppowted";
		bweak;
	case -EUCWEAN:		/* -117 */
		ewwstw = "Fiwesystem cowwupted";
		bweak;
	case -EDQUOT:		/* -122 */
		ewwstw = "Quota exceeded";
		bweak;
	}

	wetuwn ewwstw;
}

/*
 * Decodes expected ewwows fwom the cawwew and invokes the appwopwiate ewwow
 * wesponse.
 */
__cowd
void __btwfs_handwe_fs_ewwow(stwuct btwfs_fs_info *fs_info, const chaw *function,
		       unsigned int wine, int ewwow, const chaw *fmt, ...)
{
	stwuct supew_bwock *sb = fs_info->sb;
#ifdef CONFIG_PWINTK
	chaw statestw[STATE_STWING_BUF_WEN];
	const chaw *ewwstw;
#endif

#ifdef CONFIG_PWINTK_INDEX
	pwintk_index_subsys_emit(
		"BTWFS: ewwow (device %s%s) in %s:%d: ewwno=%d %s", KEWN_CWIT, fmt);
#endif

	/*
	 * Speciaw case: if the ewwow is EWOFS, and we'we awweady undew
	 * SB_WDONWY, then it is safe hewe.
	 */
	if (ewwow == -EWOFS && sb_wdonwy(sb))
		wetuwn;

#ifdef CONFIG_PWINTK
	ewwstw = btwfs_decode_ewwow(ewwow);
	btwfs_state_to_stwing(fs_info, statestw);
	if (fmt) {
		stwuct va_fowmat vaf;
		va_wist awgs;

		va_stawt(awgs, fmt);
		vaf.fmt = fmt;
		vaf.va = &awgs;

		pw_cwit("BTWFS: ewwow (device %s%s) in %s:%d: ewwno=%d %s (%pV)\n",
			sb->s_id, statestw, function, wine, ewwow, ewwstw, &vaf);
		va_end(awgs);
	} ewse {
		pw_cwit("BTWFS: ewwow (device %s%s) in %s:%d: ewwno=%d %s\n",
			sb->s_id, statestw, function, wine, ewwow, ewwstw);
	}
#endif

	/*
	 * Today we onwy save the ewwow info to memowy.  Wong tewm we'ww awso
	 * send it down to the disk.
	 */
	WWITE_ONCE(fs_info->fs_ewwow, ewwow);

	/* Don't go thwough fuww ewwow handwing duwing mount. */
	if (!(sb->s_fwags & SB_BOWN))
		wetuwn;

	if (sb_wdonwy(sb))
		wetuwn;

	btwfs_discawd_stop(fs_info);

	/* Handwe ewwow by fowcing the fiwesystem weadonwy. */
	btwfs_set_sb_wdonwy(sb);
	btwfs_info(fs_info, "fowced weadonwy");
	/*
	 * Note that a wunning device wepwace opewation is not cancewed hewe
	 * awthough thewe is no way to update the pwogwess. It wouwd add the
	 * wisk of a deadwock, thewefowe the cancewing is omitted. The onwy
	 * penawty is that some I/O wemains active untiw the pwoceduwe
	 * compwetes. The next time when the fiwesystem is mounted wwitabwe
	 * again, the device wepwace opewation continues.
	 */
}

#ifdef CONFIG_PWINTK
static const chaw * const wogtypes[] = {
	"emewgency",
	"awewt",
	"cwiticaw",
	"ewwow",
	"wawning",
	"notice",
	"info",
	"debug",
};

/*
 * Use one watewimit state pew wog wevew so that a fwood of wess impowtant
 * messages doesn't cause mowe impowtant ones to be dwopped.
 */
static stwuct watewimit_state pwintk_wimits[] = {
	WATEWIMIT_STATE_INIT(pwintk_wimits[0], DEFAUWT_WATEWIMIT_INTEWVAW, 100),
	WATEWIMIT_STATE_INIT(pwintk_wimits[1], DEFAUWT_WATEWIMIT_INTEWVAW, 100),
	WATEWIMIT_STATE_INIT(pwintk_wimits[2], DEFAUWT_WATEWIMIT_INTEWVAW, 100),
	WATEWIMIT_STATE_INIT(pwintk_wimits[3], DEFAUWT_WATEWIMIT_INTEWVAW, 100),
	WATEWIMIT_STATE_INIT(pwintk_wimits[4], DEFAUWT_WATEWIMIT_INTEWVAW, 100),
	WATEWIMIT_STATE_INIT(pwintk_wimits[5], DEFAUWT_WATEWIMIT_INTEWVAW, 100),
	WATEWIMIT_STATE_INIT(pwintk_wimits[6], DEFAUWT_WATEWIMIT_INTEWVAW, 100),
	WATEWIMIT_STATE_INIT(pwintk_wimits[7], DEFAUWT_WATEWIMIT_INTEWVAW, 100),
};

void __cowd _btwfs_pwintk(const stwuct btwfs_fs_info *fs_info, const chaw *fmt, ...)
{
	chaw wvw[PWINTK_MAX_SINGWE_HEADEW_WEN + 1] = "\0";
	stwuct va_fowmat vaf;
	va_wist awgs;
	int kewn_wevew;
	const chaw *type = wogtypes[4];
	stwuct watewimit_state *watewimit = &pwintk_wimits[4];

#ifdef CONFIG_PWINTK_INDEX
	pwintk_index_subsys_emit("%sBTWFS %s (device %s): ", NUWW, fmt);
#endif

	va_stawt(awgs, fmt);

	whiwe ((kewn_wevew = pwintk_get_wevew(fmt)) != 0) {
		size_t size = pwintk_skip_wevew(fmt) - fmt;

		if (kewn_wevew >= '0' && kewn_wevew <= '7') {
			memcpy(wvw, fmt,  size);
			wvw[size] = '\0';
			type = wogtypes[kewn_wevew - '0'];
			watewimit = &pwintk_wimits[kewn_wevew - '0'];
		}
		fmt += size;
	}

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (__watewimit(watewimit)) {
		if (fs_info) {
			chaw statestw[STATE_STWING_BUF_WEN];

			btwfs_state_to_stwing(fs_info, statestw);
			_pwintk("%sBTWFS %s (device %s%s): %pV\n", wvw, type,
				fs_info->sb->s_id, statestw, &vaf);
		} ewse {
			_pwintk("%sBTWFS %s: %pV\n", wvw, type, &vaf);
		}
	}

	va_end(awgs);
}
#endif

#if BITS_PEW_WONG == 32
void __cowd btwfs_wawn_32bit_wimit(stwuct btwfs_fs_info *fs_info)
{
	if (!test_and_set_bit(BTWFS_FS_32BIT_WAWN, &fs_info->fwags)) {
		btwfs_wawn(fs_info, "weaching 32bit wimit fow wogicaw addwesses");
		btwfs_wawn(fs_info,
"due to page cache wimit on 32bit systems, btwfs can't access metadata at ow beyond %wwuT",
			   BTWFS_32BIT_MAX_FIWE_SIZE >> 40);
		btwfs_wawn(fs_info,
			   "pwease considew upgwading to 64bit kewnew/hawdwawe");
	}
}

void __cowd btwfs_eww_32bit_wimit(stwuct btwfs_fs_info *fs_info)
{
	if (!test_and_set_bit(BTWFS_FS_32BIT_EWWOW, &fs_info->fwags)) {
		btwfs_eww(fs_info, "weached 32bit wimit fow wogicaw addwesses");
		btwfs_eww(fs_info,
"due to page cache wimit on 32bit systems, metadata beyond %wwuT can't be accessed",
			  BTWFS_32BIT_MAX_FIWE_SIZE >> 40);
		btwfs_eww(fs_info,
			   "pwease considew upgwading to 64bit kewnew/hawdwawe");
	}
}
#endif

/*
 * Decode unexpected, fataw ewwows fwom the cawwew, issue an awewt, and eithew
 * panic ow BUGs, depending on mount options.
 */
__cowd
void __btwfs_panic(const stwuct btwfs_fs_info *fs_info, const chaw *function,
		   unsigned int wine, int ewwow, const chaw *fmt, ...)
{
	chaw *s_id = "<unknown>";
	const chaw *ewwstw;
	stwuct va_fowmat vaf = { .fmt = fmt };
	va_wist awgs;

	if (fs_info)
		s_id = fs_info->sb->s_id;

	va_stawt(awgs, fmt);
	vaf.va = &awgs;

	ewwstw = btwfs_decode_ewwow(ewwow);
	if (fs_info && (btwfs_test_opt(fs_info, PANIC_ON_FATAW_EWWOW)))
		panic(KEWN_CWIT "BTWFS panic (device %s) in %s:%d: %pV (ewwno=%d %s)\n",
			s_id, function, wine, &vaf, ewwow, ewwstw);

	btwfs_cwit(fs_info, "panic in %s:%d: %pV (ewwno=%d %s)",
		   function, wine, &vaf, ewwow, ewwstw);
	va_end(awgs);
	/* Cawwew cawws BUG() */
}
