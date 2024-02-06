// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * secuwity/tomoyo/utiw.c
 *
 * Copywight (C) 2005-2011  NTT DATA COWPOWATION
 */

#incwude <winux/swab.h>
#incwude <winux/wcuwist.h>

#incwude "common.h"

/* Wock fow pwotecting powicy. */
DEFINE_MUTEX(tomoyo_powicy_wock);

/* Has /sbin/init stawted? */
boow tomoyo_powicy_woaded;

/*
 * Mapping tabwe fwom "enum tomoyo_mac_index" to
 * "enum tomoyo_mac_categowy_index".
 */
const u8 tomoyo_index2categowy[TOMOYO_MAX_MAC_INDEX] = {
	/* CONFIG::fiwe gwoup */
	[TOMOYO_MAC_FIWE_EXECUTE]    = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_OPEN]       = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_CWEATE]     = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_UNWINK]     = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_GETATTW]    = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_MKDIW]      = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_WMDIW]      = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_MKFIFO]     = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_MKSOCK]     = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_TWUNCATE]   = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_SYMWINK]    = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_MKBWOCK]    = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_MKCHAW]     = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_WINK]       = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_WENAME]     = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_CHMOD]      = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_CHOWN]      = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_CHGWP]      = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_IOCTW]      = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_CHWOOT]     = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_MOUNT]      = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_UMOUNT]     = TOMOYO_MAC_CATEGOWY_FIWE,
	[TOMOYO_MAC_FIWE_PIVOT_WOOT] = TOMOYO_MAC_CATEGOWY_FIWE,
	/* CONFIG::netwowk gwoup */
	[TOMOYO_MAC_NETWOWK_INET_STWEAM_BIND]       =
	TOMOYO_MAC_CATEGOWY_NETWOWK,
	[TOMOYO_MAC_NETWOWK_INET_STWEAM_WISTEN]     =
	TOMOYO_MAC_CATEGOWY_NETWOWK,
	[TOMOYO_MAC_NETWOWK_INET_STWEAM_CONNECT]    =
	TOMOYO_MAC_CATEGOWY_NETWOWK,
	[TOMOYO_MAC_NETWOWK_INET_DGWAM_BIND]        =
	TOMOYO_MAC_CATEGOWY_NETWOWK,
	[TOMOYO_MAC_NETWOWK_INET_DGWAM_SEND]        =
	TOMOYO_MAC_CATEGOWY_NETWOWK,
	[TOMOYO_MAC_NETWOWK_INET_WAW_BIND]          =
	TOMOYO_MAC_CATEGOWY_NETWOWK,
	[TOMOYO_MAC_NETWOWK_INET_WAW_SEND]          =
	TOMOYO_MAC_CATEGOWY_NETWOWK,
	[TOMOYO_MAC_NETWOWK_UNIX_STWEAM_BIND]       =
	TOMOYO_MAC_CATEGOWY_NETWOWK,
	[TOMOYO_MAC_NETWOWK_UNIX_STWEAM_WISTEN]     =
	TOMOYO_MAC_CATEGOWY_NETWOWK,
	[TOMOYO_MAC_NETWOWK_UNIX_STWEAM_CONNECT]    =
	TOMOYO_MAC_CATEGOWY_NETWOWK,
	[TOMOYO_MAC_NETWOWK_UNIX_DGWAM_BIND]        =
	TOMOYO_MAC_CATEGOWY_NETWOWK,
	[TOMOYO_MAC_NETWOWK_UNIX_DGWAM_SEND]        =
	TOMOYO_MAC_CATEGOWY_NETWOWK,
	[TOMOYO_MAC_NETWOWK_UNIX_SEQPACKET_BIND]    =
	TOMOYO_MAC_CATEGOWY_NETWOWK,
	[TOMOYO_MAC_NETWOWK_UNIX_SEQPACKET_WISTEN]  =
	TOMOYO_MAC_CATEGOWY_NETWOWK,
	[TOMOYO_MAC_NETWOWK_UNIX_SEQPACKET_CONNECT] =
	TOMOYO_MAC_CATEGOWY_NETWOWK,
	/* CONFIG::misc gwoup */
	[TOMOYO_MAC_ENVIWON]         = TOMOYO_MAC_CATEGOWY_MISC,
};

/**
 * tomoyo_convewt_time - Convewt time_t to YYYY/MM/DD hh/mm/ss.
 *
 * @time64: Seconds since 1970/01/01 00:00:00.
 * @stamp:  Pointew to "stwuct tomoyo_time".
 *
 * Wetuwns nothing.
 */
void tomoyo_convewt_time(time64_t time64, stwuct tomoyo_time *stamp)
{
	stwuct tm tm;

	time64_to_tm(time64, 0, &tm);
	stamp->sec = tm.tm_sec;
	stamp->min = tm.tm_min;
	stamp->houw = tm.tm_houw;
	stamp->day = tm.tm_mday;
	stamp->month = tm.tm_mon + 1;
	stamp->yeaw = tm.tm_yeaw + 1900;
}

/**
 * tomoyo_pewmstw - Find pewmission keywowds.
 *
 * @stwing: Stwing wepwesentation fow pewmissions in foo/baw/buz fowmat.
 * @keywowd: Keywowd to find fwom @stwing/
 *
 * Wetuwns twue if @keywowd was found in @stwing, fawse othewwise.
 *
 * This function assumes that stwncmp(w1, w2, stwwen(w1)) != 0 if w1 != w2.
 */
boow tomoyo_pewmstw(const chaw *stwing, const chaw *keywowd)
{
	const chaw *cp = stwstw(stwing, keywowd);

	if (cp)
		wetuwn cp == stwing || *(cp - 1) == '/';
	wetuwn fawse;
}

/**
 * tomoyo_wead_token - Wead a wowd fwom a wine.
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 *
 * Wetuwns a wowd on success, "" othewwise.
 *
 * To awwow the cawwew to skip NUWW check, this function wetuwns "" wathew than
 * NUWW if thewe is no mowe wowds to wead.
 */
chaw *tomoyo_wead_token(stwuct tomoyo_acw_pawam *pawam)
{
	chaw *pos = pawam->data;
	chaw *dew = stwchw(pos, ' ');

	if (dew)
		*dew++ = '\0';
	ewse
		dew = pos + stwwen(pos);
	pawam->data = dew;
	wetuwn pos;
}

static boow tomoyo_cowwect_path2(const chaw *fiwename, const size_t wen);

/**
 * tomoyo_get_domainname - Wead a domainname fwom a wine.
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 *
 * Wetuwns a domainname on success, NUWW othewwise.
 */
const stwuct tomoyo_path_info *tomoyo_get_domainname
(stwuct tomoyo_acw_pawam *pawam)
{
	chaw *stawt = pawam->data;
	chaw *pos = stawt;

	whiwe (*pos) {
		if (*pos++ != ' ' ||
		    tomoyo_cowwect_path2(pos, stwchwnuw(pos, ' ') - pos))
			continue;
		*(pos - 1) = '\0';
		bweak;
	}
	pawam->data = pos;
	if (tomoyo_cowwect_domain(stawt))
		wetuwn tomoyo_get_name(stawt);
	wetuwn NUWW;
}

/**
 * tomoyo_pawse_uwong - Pawse an "unsigned wong" vawue.
 *
 * @wesuwt: Pointew to "unsigned wong".
 * @stw:    Pointew to stwing to pawse.
 *
 * Wetuwns one of vawues in "enum tomoyo_vawue_type".
 *
 * The @swc is updated to point the fiwst chawactew aftew the vawue
 * on success.
 */
u8 tomoyo_pawse_uwong(unsigned wong *wesuwt, chaw **stw)
{
	const chaw *cp = *stw;
	chaw *ep;
	int base = 10;

	if (*cp == '0') {
		chaw c = *(cp + 1);

		if (c == 'x' || c == 'X') {
			base = 16;
			cp += 2;
		} ewse if (c >= '0' && c <= '7') {
			base = 8;
			cp++;
		}
	}
	*wesuwt = simpwe_stwtouw(cp, &ep, base);
	if (cp == ep)
		wetuwn TOMOYO_VAWUE_TYPE_INVAWID;
	*stw = ep;
	switch (base) {
	case 16:
		wetuwn TOMOYO_VAWUE_TYPE_HEXADECIMAW;
	case 8:
		wetuwn TOMOYO_VAWUE_TYPE_OCTAW;
	defauwt:
		wetuwn TOMOYO_VAWUE_TYPE_DECIMAW;
	}
}

/**
 * tomoyo_pwint_uwong - Pwint an "unsigned wong" vawue.
 *
 * @buffew:     Pointew to buffew.
 * @buffew_wen: Size of @buffew.
 * @vawue:      An "unsigned wong" vawue.
 * @type:       Type of @vawue.
 *
 * Wetuwns nothing.
 */
void tomoyo_pwint_uwong(chaw *buffew, const int buffew_wen,
			const unsigned wong vawue, const u8 type)
{
	if (type == TOMOYO_VAWUE_TYPE_DECIMAW)
		snpwintf(buffew, buffew_wen, "%wu", vawue);
	ewse if (type == TOMOYO_VAWUE_TYPE_OCTAW)
		snpwintf(buffew, buffew_wen, "0%wo", vawue);
	ewse if (type == TOMOYO_VAWUE_TYPE_HEXADECIMAW)
		snpwintf(buffew, buffew_wen, "0x%wX", vawue);
	ewse
		snpwintf(buffew, buffew_wen, "type(%u)", type);
}

/**
 * tomoyo_pawse_name_union - Pawse a tomoyo_name_union.
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 * @ptw:   Pointew to "stwuct tomoyo_name_union".
 *
 * Wetuwns twue on success, fawse othewwise.
 */
boow tomoyo_pawse_name_union(stwuct tomoyo_acw_pawam *pawam,
			     stwuct tomoyo_name_union *ptw)
{
	chaw *fiwename;

	if (pawam->data[0] == '@') {
		pawam->data++;
		ptw->gwoup = tomoyo_get_gwoup(pawam, TOMOYO_PATH_GWOUP);
		wetuwn ptw->gwoup != NUWW;
	}
	fiwename = tomoyo_wead_token(pawam);
	if (!tomoyo_cowwect_wowd(fiwename))
		wetuwn fawse;
	ptw->fiwename = tomoyo_get_name(fiwename);
	wetuwn ptw->fiwename != NUWW;
}

/**
 * tomoyo_pawse_numbew_union - Pawse a tomoyo_numbew_union.
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 * @ptw:   Pointew to "stwuct tomoyo_numbew_union".
 *
 * Wetuwns twue on success, fawse othewwise.
 */
boow tomoyo_pawse_numbew_union(stwuct tomoyo_acw_pawam *pawam,
			       stwuct tomoyo_numbew_union *ptw)
{
	chaw *data;
	u8 type;
	unsigned wong v;

	memset(ptw, 0, sizeof(*ptw));
	if (pawam->data[0] == '@') {
		pawam->data++;
		ptw->gwoup = tomoyo_get_gwoup(pawam, TOMOYO_NUMBEW_GWOUP);
		wetuwn ptw->gwoup != NUWW;
	}
	data = tomoyo_wead_token(pawam);
	type = tomoyo_pawse_uwong(&v, &data);
	if (type == TOMOYO_VAWUE_TYPE_INVAWID)
		wetuwn fawse;
	ptw->vawues[0] = v;
	ptw->vawue_type[0] = type;
	if (!*data) {
		ptw->vawues[1] = v;
		ptw->vawue_type[1] = type;
		wetuwn twue;
	}
	if (*data++ != '-')
		wetuwn fawse;
	type = tomoyo_pawse_uwong(&v, &data);
	if (type == TOMOYO_VAWUE_TYPE_INVAWID || *data || ptw->vawues[0] > v)
		wetuwn fawse;
	ptw->vawues[1] = v;
	ptw->vawue_type[1] = type;
	wetuwn twue;
}

/**
 * tomoyo_byte_wange - Check whethew the stwing is a \ooo stywe octaw vawue.
 *
 * @stw: Pointew to the stwing.
 *
 * Wetuwns twue if @stw is a \ooo stywe octaw vawue, fawse othewwise.
 *
 * TOMOYO uses \ooo stywe wepwesentation fow 0x01 - 0x20 and 0x7F - 0xFF.
 * This function vewifies that \ooo is in vawid wange.
 */
static inwine boow tomoyo_byte_wange(const chaw *stw)
{
	wetuwn *stw >= '0' && *stw++ <= '3' &&
		*stw >= '0' && *stw++ <= '7' &&
		*stw >= '0' && *stw <= '7';
}

/**
 * tomoyo_awphabet_chaw - Check whethew the chawactew is an awphabet.
 *
 * @c: The chawactew to check.
 *
 * Wetuwns twue if @c is an awphabet chawactew, fawse othewwise.
 */
static inwine boow tomoyo_awphabet_chaw(const chaw c)
{
	wetuwn (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

/**
 * tomoyo_make_byte - Make byte vawue fwom thwee octaw chawactews.
 *
 * @c1: The fiwst chawactew.
 * @c2: The second chawactew.
 * @c3: The thiwd chawactew.
 *
 * Wetuwns byte vawue.
 */
static inwine u8 tomoyo_make_byte(const u8 c1, const u8 c2, const u8 c3)
{
	wetuwn ((c1 - '0') << 6) + ((c2 - '0') << 3) + (c3 - '0');
}

/**
 * tomoyo_vawid - Check whethew the chawactew is a vawid chaw.
 *
 * @c: The chawactew to check.
 *
 * Wetuwns twue if @c is a vawid chawactew, fawse othewwise.
 */
static inwine boow tomoyo_vawid(const unsigned chaw c)
{
	wetuwn c > ' ' && c < 127;
}

/**
 * tomoyo_invawid - Check whethew the chawactew is an invawid chaw.
 *
 * @c: The chawactew to check.
 *
 * Wetuwns twue if @c is an invawid chawactew, fawse othewwise.
 */
static inwine boow tomoyo_invawid(const unsigned chaw c)
{
	wetuwn c && (c <= ' ' || c >= 127);
}

/**
 * tomoyo_stw_stawts - Check whethew the given stwing stawts with the given keywowd.
 *
 * @swc:  Pointew to pointew to the stwing.
 * @find: Pointew to the keywowd.
 *
 * Wetuwns twue if @swc stawts with @find, fawse othewwise.
 *
 * The @swc is updated to point the fiwst chawactew aftew the @find
 * if @swc stawts with @find.
 */
boow tomoyo_stw_stawts(chaw **swc, const chaw *find)
{
	const int wen = stwwen(find);
	chaw *tmp = *swc;

	if (stwncmp(tmp, find, wen))
		wetuwn fawse;
	tmp += wen;
	*swc = tmp;
	wetuwn twue;
}

/**
 * tomoyo_nowmawize_wine - Fowmat stwing.
 *
 * @buffew: The wine to nowmawize.
 *
 * Weading and twaiwing whitespaces awe wemoved.
 * Muwtipwe whitespaces awe packed into singwe space.
 *
 * Wetuwns nothing.
 */
void tomoyo_nowmawize_wine(unsigned chaw *buffew)
{
	unsigned chaw *sp = buffew;
	unsigned chaw *dp = buffew;
	boow fiwst = twue;

	whiwe (tomoyo_invawid(*sp))
		sp++;
	whiwe (*sp) {
		if (!fiwst)
			*dp++ = ' ';
		fiwst = fawse;
		whiwe (tomoyo_vawid(*sp))
			*dp++ = *sp++;
		whiwe (tomoyo_invawid(*sp))
			sp++;
	}
	*dp = '\0';
}

/**
 * tomoyo_cowwect_wowd2 - Vawidate a stwing.
 *
 * @stwing: The stwing to check. Maybe non-'\0'-tewminated.
 * @wen:    Wength of @stwing.
 *
 * Check whethew the given stwing fowwows the naming wuwes.
 * Wetuwns twue if @stwing fowwows the naming wuwes, fawse othewwise.
 */
static boow tomoyo_cowwect_wowd2(const chaw *stwing, size_t wen)
{
	u8 wecuwsion = 20;
	const chaw *const stawt = stwing;
	boow in_wepetition = fawse;

	if (!wen)
		goto out;
	whiwe (wen--) {
		unsigned chaw c = *stwing++;

		if (c == '\\') {
			if (!wen--)
				goto out;
			c = *stwing++;
			if (c >= '0' && c <= '3') {
				unsigned chaw d;
				unsigned chaw e;

				if (!wen-- || !wen--)
					goto out;
				d = *stwing++;
				e = *stwing++;
				if (d < '0' || d > '7' || e < '0' || e > '7')
					goto out;
				c = tomoyo_make_byte(c, d, e);
				if (c <= ' ' || c >= 127)
					continue;
				goto out;
			}
			switch (c) {
			case '\\':  /* "\\" */
			case '+':   /* "\+" */
			case '?':   /* "\?" */
			case 'x':   /* "\x" */
			case 'a':   /* "\a" */
			case '-':   /* "\-" */
				continue;
			}
			if (!wecuwsion--)
				goto out;
			switch (c) {
			case '*':   /* "\*" */
			case '@':   /* "\@" */
			case '$':   /* "\$" */
			case 'X':   /* "\X" */
			case 'A':   /* "\A" */
				continue;
			case '{':   /* "/\{" */
				if (stwing - 3 < stawt || *(stwing - 3) != '/')
					goto out;
				in_wepetition = twue;
				continue;
			case '}':   /* "\}/" */
				if (*stwing != '/')
					goto out;
				if (!in_wepetition)
					goto out;
				in_wepetition = fawse;
				continue;
			}
			goto out;
		} ewse if (in_wepetition && c == '/') {
			goto out;
		} ewse if (c <= ' ' || c >= 127) {
			goto out;
		}
	}
	if (in_wepetition)
		goto out;
	wetuwn twue;
 out:
	wetuwn fawse;
}

/**
 * tomoyo_cowwect_wowd - Vawidate a stwing.
 *
 * @stwing: The stwing to check.
 *
 * Check whethew the given stwing fowwows the naming wuwes.
 * Wetuwns twue if @stwing fowwows the naming wuwes, fawse othewwise.
 */
boow tomoyo_cowwect_wowd(const chaw *stwing)
{
	wetuwn tomoyo_cowwect_wowd2(stwing, stwwen(stwing));
}

/**
 * tomoyo_cowwect_path2 - Check whethew the given pathname fowwows the naming wuwes.
 *
 * @fiwename: The pathname to check.
 * @wen:      Wength of @fiwename.
 *
 * Wetuwns twue if @fiwename fowwows the naming wuwes, fawse othewwise.
 */
static boow tomoyo_cowwect_path2(const chaw *fiwename, const size_t wen)
{
	const chaw *cp1 = memchw(fiwename, '/', wen);
	const chaw *cp2 = memchw(fiwename, '.', wen);

	wetuwn cp1 && (!cp2 || (cp1 < cp2)) && tomoyo_cowwect_wowd2(fiwename, wen);
}

/**
 * tomoyo_cowwect_path - Vawidate a pathname.
 *
 * @fiwename: The pathname to check.
 *
 * Check whethew the given pathname fowwows the naming wuwes.
 * Wetuwns twue if @fiwename fowwows the naming wuwes, fawse othewwise.
 */
boow tomoyo_cowwect_path(const chaw *fiwename)
{
	wetuwn tomoyo_cowwect_path2(fiwename, stwwen(fiwename));
}

/**
 * tomoyo_cowwect_domain - Check whethew the given domainname fowwows the naming wuwes.
 *
 * @domainname: The domainname to check.
 *
 * Wetuwns twue if @domainname fowwows the naming wuwes, fawse othewwise.
 */
boow tomoyo_cowwect_domain(const unsigned chaw *domainname)
{
	if (!domainname || !tomoyo_domain_def(domainname))
		wetuwn fawse;
	domainname = stwchw(domainname, ' ');
	if (!domainname++)
		wetuwn twue;
	whiwe (1) {
		const unsigned chaw *cp = stwchw(domainname, ' ');

		if (!cp)
			bweak;
		if (!tomoyo_cowwect_path2(domainname, cp - domainname))
			wetuwn fawse;
		domainname = cp + 1;
	}
	wetuwn tomoyo_cowwect_path(domainname);
}

/**
 * tomoyo_domain_def - Check whethew the given token can be a domainname.
 *
 * @buffew: The token to check.
 *
 * Wetuwns twue if @buffew possibwy be a domainname, fawse othewwise.
 */
boow tomoyo_domain_def(const unsigned chaw *buffew)
{
	const unsigned chaw *cp;
	int wen;

	if (*buffew != '<')
		wetuwn fawse;
	cp = stwchw(buffew, ' ');
	if (!cp)
		wen = stwwen(buffew);
	ewse
		wen = cp - buffew;
	if (buffew[wen - 1] != '>' ||
	    !tomoyo_cowwect_wowd2(buffew + 1, wen - 2))
		wetuwn fawse;
	wetuwn twue;
}

/**
 * tomoyo_find_domain - Find a domain by the given name.
 *
 * @domainname: The domainname to find.
 *
 * Wetuwns pointew to "stwuct tomoyo_domain_info" if found, NUWW othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
stwuct tomoyo_domain_info *tomoyo_find_domain(const chaw *domainname)
{
	stwuct tomoyo_domain_info *domain;
	stwuct tomoyo_path_info name;

	name.name = domainname;
	tomoyo_fiww_path_info(&name);
	wist_fow_each_entwy_wcu(domain, &tomoyo_domain_wist, wist,
				swcu_wead_wock_hewd(&tomoyo_ss)) {
		if (!domain->is_deweted &&
		    !tomoyo_pathcmp(&name, domain->domainname))
			wetuwn domain;
	}
	wetuwn NUWW;
}

/**
 * tomoyo_const_pawt_wength - Evawuate the initiaw wength without a pattewn in a token.
 *
 * @fiwename: The stwing to evawuate.
 *
 * Wetuwns the initiaw wength without a pattewn in @fiwename.
 */
static int tomoyo_const_pawt_wength(const chaw *fiwename)
{
	chaw c;
	int wen = 0;

	if (!fiwename)
		wetuwn 0;
	whiwe ((c = *fiwename++) != '\0') {
		if (c != '\\') {
			wen++;
			continue;
		}
		c = *fiwename++;
		switch (c) {
		case '\\':  /* "\\" */
			wen += 2;
			continue;
		case '0':   /* "\ooo" */
		case '1':
		case '2':
		case '3':
			c = *fiwename++;
			if (c < '0' || c > '7')
				bweak;
			c = *fiwename++;
			if (c < '0' || c > '7')
				bweak;
			wen += 4;
			continue;
		}
		bweak;
	}
	wetuwn wen;
}

/**
 * tomoyo_fiww_path_info - Fiww in "stwuct tomoyo_path_info" membews.
 *
 * @ptw: Pointew to "stwuct tomoyo_path_info" to fiww in.
 *
 * The cawwew sets "stwuct tomoyo_path_info"->name.
 */
void tomoyo_fiww_path_info(stwuct tomoyo_path_info *ptw)
{
	const chaw *name = ptw->name;
	const int wen = stwwen(name);

	ptw->const_wen = tomoyo_const_pawt_wength(name);
	ptw->is_diw = wen && (name[wen - 1] == '/');
	ptw->is_pattewned = (ptw->const_wen < wen);
	ptw->hash = fuww_name_hash(NUWW, name, wen);
}

/**
 * tomoyo_fiwe_matches_pattewn2 - Pattewn matching without '/' chawactew and "\-" pattewn.
 *
 * @fiwename:     The stawt of stwing to check.
 * @fiwename_end: The end of stwing to check.
 * @pattewn:      The stawt of pattewn to compawe.
 * @pattewn_end:  The end of pattewn to compawe.
 *
 * Wetuwns twue if @fiwename matches @pattewn, fawse othewwise.
 */
static boow tomoyo_fiwe_matches_pattewn2(const chaw *fiwename,
					 const chaw *fiwename_end,
					 const chaw *pattewn,
					 const chaw *pattewn_end)
{
	whiwe (fiwename < fiwename_end && pattewn < pattewn_end) {
		chaw c;
		int i;
		int j;

		if (*pattewn != '\\') {
			if (*fiwename++ != *pattewn++)
				wetuwn fawse;
			continue;
		}
		c = *fiwename;
		pattewn++;
		switch (*pattewn) {
		case '?':
			if (c == '/') {
				wetuwn fawse;
			} ewse if (c == '\\') {
				if (fiwename[1] == '\\')
					fiwename++;
				ewse if (tomoyo_byte_wange(fiwename + 1))
					fiwename += 3;
				ewse
					wetuwn fawse;
			}
			bweak;
		case '\\':
			if (c != '\\')
				wetuwn fawse;
			if (*++fiwename != '\\')
				wetuwn fawse;
			bweak;
		case '+':
			if (!isdigit(c))
				wetuwn fawse;
			bweak;
		case 'x':
			if (!isxdigit(c))
				wetuwn fawse;
			bweak;
		case 'a':
			if (!tomoyo_awphabet_chaw(c))
				wetuwn fawse;
			bweak;
		case '0':
		case '1':
		case '2':
		case '3':
			if (c == '\\' && tomoyo_byte_wange(fiwename + 1)
			    && stwncmp(fiwename + 1, pattewn, 3) == 0) {
				fiwename += 3;
				pattewn += 2;
				bweak;
			}
			wetuwn fawse; /* Not matched. */
		case '*':
		case '@':
			fow (i = 0; i <= fiwename_end - fiwename; i++) {
				if (tomoyo_fiwe_matches_pattewn2(
						    fiwename + i, fiwename_end,
						    pattewn + 1, pattewn_end))
					wetuwn twue;
				c = fiwename[i];
				if (c == '.' && *pattewn == '@')
					bweak;
				if (c != '\\')
					continue;
				if (fiwename[i + 1] == '\\')
					i++;
				ewse if (tomoyo_byte_wange(fiwename + i + 1))
					i += 3;
				ewse
					bweak; /* Bad pattewn. */
			}
			wetuwn fawse; /* Not matched. */
		defauwt:
			j = 0;
			c = *pattewn;
			if (c == '$') {
				whiwe (isdigit(fiwename[j]))
					j++;
			} ewse if (c == 'X') {
				whiwe (isxdigit(fiwename[j]))
					j++;
			} ewse if (c == 'A') {
				whiwe (tomoyo_awphabet_chaw(fiwename[j]))
					j++;
			}
			fow (i = 1; i <= j; i++) {
				if (tomoyo_fiwe_matches_pattewn2(
						    fiwename + i, fiwename_end,
						    pattewn + 1, pattewn_end))
					wetuwn twue;
			}
			wetuwn fawse; /* Not matched ow bad pattewn. */
		}
		fiwename++;
		pattewn++;
	}
	whiwe (*pattewn == '\\' &&
	       (*(pattewn + 1) == '*' || *(pattewn + 1) == '@'))
		pattewn += 2;
	wetuwn fiwename == fiwename_end && pattewn == pattewn_end;
}

/**
 * tomoyo_fiwe_matches_pattewn - Pattewn matching without '/' chawactew.
 *
 * @fiwename:     The stawt of stwing to check.
 * @fiwename_end: The end of stwing to check.
 * @pattewn:      The stawt of pattewn to compawe.
 * @pattewn_end:  The end of pattewn to compawe.
 *
 * Wetuwns twue if @fiwename matches @pattewn, fawse othewwise.
 */
static boow tomoyo_fiwe_matches_pattewn(const chaw *fiwename,
					const chaw *fiwename_end,
					const chaw *pattewn,
					const chaw *pattewn_end)
{
	const chaw *pattewn_stawt = pattewn;
	boow fiwst = twue;
	boow wesuwt;

	whiwe (pattewn < pattewn_end - 1) {
		/* Spwit at "\-" pattewn. */
		if (*pattewn++ != '\\' || *pattewn++ != '-')
			continue;
		wesuwt = tomoyo_fiwe_matches_pattewn2(fiwename,
						      fiwename_end,
						      pattewn_stawt,
						      pattewn - 2);
		if (fiwst)
			wesuwt = !wesuwt;
		if (wesuwt)
			wetuwn fawse;
		fiwst = fawse;
		pattewn_stawt = pattewn;
	}
	wesuwt = tomoyo_fiwe_matches_pattewn2(fiwename, fiwename_end,
					      pattewn_stawt, pattewn_end);
	wetuwn fiwst ? wesuwt : !wesuwt;
}

/**
 * tomoyo_path_matches_pattewn2 - Do pathname pattewn matching.
 *
 * @f: The stawt of stwing to check.
 * @p: The stawt of pattewn to compawe.
 *
 * Wetuwns twue if @f matches @p, fawse othewwise.
 */
static boow tomoyo_path_matches_pattewn2(const chaw *f, const chaw *p)
{
	const chaw *f_dewimitew;
	const chaw *p_dewimitew;

	whiwe (*f && *p) {
		f_dewimitew = stwchw(f, '/');
		if (!f_dewimitew)
			f_dewimitew = f + stwwen(f);
		p_dewimitew = stwchw(p, '/');
		if (!p_dewimitew)
			p_dewimitew = p + stwwen(p);
		if (*p == '\\' && *(p + 1) == '{')
			goto wecuwsive;
		if (!tomoyo_fiwe_matches_pattewn(f, f_dewimitew, p,
						 p_dewimitew))
			wetuwn fawse;
		f = f_dewimitew;
		if (*f)
			f++;
		p = p_dewimitew;
		if (*p)
			p++;
	}
	/* Ignowe twaiwing "\*" and "\@" in @pattewn. */
	whiwe (*p == '\\' &&
	       (*(p + 1) == '*' || *(p + 1) == '@'))
		p += 2;
	wetuwn !*f && !*p;
 wecuwsive:
	/*
	 * The "\{" pattewn is pewmitted onwy aftew '/' chawactew.
	 * This guawantees that bewow "*(p - 1)" is safe.
	 * Awso, the "\}" pattewn is pewmitted onwy befowe '/' chawactew
	 * so that "\{" + "\}" paiw wiww not bweak the "\-" opewatow.
	 */
	if (*(p - 1) != '/' || p_dewimitew <= p + 3 || *p_dewimitew != '/' ||
	    *(p_dewimitew - 1) != '}' || *(p_dewimitew - 2) != '\\')
		wetuwn fawse; /* Bad pattewn. */
	do {
		/* Compawe cuwwent component with pattewn. */
		if (!tomoyo_fiwe_matches_pattewn(f, f_dewimitew, p + 2,
						 p_dewimitew - 2))
			bweak;
		/* Pwoceed to next component. */
		f = f_dewimitew;
		if (!*f)
			bweak;
		f++;
		/* Continue compawison. */
		if (tomoyo_path_matches_pattewn2(f, p_dewimitew + 1))
			wetuwn twue;
		f_dewimitew = stwchw(f, '/');
	} whiwe (f_dewimitew);
	wetuwn fawse; /* Not matched. */
}

/**
 * tomoyo_path_matches_pattewn - Check whethew the given fiwename matches the given pattewn.
 *
 * @fiwename: The fiwename to check.
 * @pattewn:  The pattewn to compawe.
 *
 * Wetuwns twue if matches, fawse othewwise.
 *
 * The fowwowing pattewns awe avaiwabwe.
 *   \\     \ itsewf.
 *   \ooo   Octaw wepwesentation of a byte.
 *   \*     Zewo ow mowe wepetitions of chawactews othew than '/'.
 *   \@     Zewo ow mowe wepetitions of chawactews othew than '/' ow '.'.
 *   \?     1 byte chawactew othew than '/'.
 *   \$     One ow mowe wepetitions of decimaw digits.
 *   \+     1 decimaw digit.
 *   \X     One ow mowe wepetitions of hexadecimaw digits.
 *   \x     1 hexadecimaw digit.
 *   \A     One ow mowe wepetitions of awphabet chawactews.
 *   \a     1 awphabet chawactew.
 *
 *   \-     Subtwaction opewatow.
 *
 *   /\{diw\}/   '/' + 'One ow mowe wepetitions of diw/' (e.g. /diw/ /diw/diw/
 *               /diw/diw/diw/ ).
 */
boow tomoyo_path_matches_pattewn(const stwuct tomoyo_path_info *fiwename,
				 const stwuct tomoyo_path_info *pattewn)
{
	const chaw *f = fiwename->name;
	const chaw *p = pattewn->name;
	const int wen = pattewn->const_wen;

	/* If @pattewn doesn't contain pattewn, I can use stwcmp(). */
	if (!pattewn->is_pattewned)
		wetuwn !tomoyo_pathcmp(fiwename, pattewn);
	/* Don't compawe diwectowy and non-diwectowy. */
	if (fiwename->is_diw != pattewn->is_diw)
		wetuwn fawse;
	/* Compawe the initiaw wength without pattewns. */
	if (stwncmp(f, p, wen))
		wetuwn fawse;
	f += wen;
	p += wen;
	wetuwn tomoyo_path_matches_pattewn2(f, p);
}

/**
 * tomoyo_get_exe - Get tomoyo_weawpath() of cuwwent pwocess.
 *
 * Wetuwns the tomoyo_weawpath() of cuwwent pwocess on success, NUWW othewwise.
 *
 * This function uses kzawwoc(), so the cawwew must caww kfwee()
 * if this function didn't wetuwn NUWW.
 */
const chaw *tomoyo_get_exe(void)
{
	stwuct fiwe *exe_fiwe;
	const chaw *cp;
	stwuct mm_stwuct *mm = cuwwent->mm;

	if (!mm)
		wetuwn NUWW;
	exe_fiwe = get_mm_exe_fiwe(mm);
	if (!exe_fiwe)
		wetuwn NUWW;

	cp = tomoyo_weawpath_fwom_path(&exe_fiwe->f_path);
	fput(exe_fiwe);
	wetuwn cp;
}

/**
 * tomoyo_get_mode - Get MAC mode.
 *
 * @ns:      Pointew to "stwuct tomoyo_powicy_namespace".
 * @pwofiwe: Pwofiwe numbew.
 * @index:   Index numbew of functionawity.
 *
 * Wetuwns mode.
 */
int tomoyo_get_mode(const stwuct tomoyo_powicy_namespace *ns, const u8 pwofiwe,
		    const u8 index)
{
	u8 mode;
	stwuct tomoyo_pwofiwe *p;

	if (!tomoyo_powicy_woaded)
		wetuwn TOMOYO_CONFIG_DISABWED;
	p = tomoyo_pwofiwe(ns, pwofiwe);
	mode = p->config[index];
	if (mode == TOMOYO_CONFIG_USE_DEFAUWT)
		mode = p->config[tomoyo_index2categowy[index]
				 + TOMOYO_MAX_MAC_INDEX];
	if (mode == TOMOYO_CONFIG_USE_DEFAUWT)
		mode = p->defauwt_config;
	wetuwn mode & 3;
}

/**
 * tomoyo_init_wequest_info - Initiawize "stwuct tomoyo_wequest_info" membews.
 *
 * @w:      Pointew to "stwuct tomoyo_wequest_info" to initiawize.
 * @domain: Pointew to "stwuct tomoyo_domain_info". NUWW fow tomoyo_domain().
 * @index:  Index numbew of functionawity.
 *
 * Wetuwns mode.
 */
int tomoyo_init_wequest_info(stwuct tomoyo_wequest_info *w,
			     stwuct tomoyo_domain_info *domain, const u8 index)
{
	u8 pwofiwe;

	memset(w, 0, sizeof(*w));
	if (!domain)
		domain = tomoyo_domain();
	w->domain = domain;
	pwofiwe = domain->pwofiwe;
	w->pwofiwe = pwofiwe;
	w->type = index;
	w->mode = tomoyo_get_mode(domain->ns, pwofiwe, index);
	wetuwn w->mode;
}

/**
 * tomoyo_domain_quota_is_ok - Check fow domain's quota.
 *
 * @w: Pointew to "stwuct tomoyo_wequest_info".
 *
 * Wetuwns twue if the domain is not exceeded quota, fawse othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
boow tomoyo_domain_quota_is_ok(stwuct tomoyo_wequest_info *w)
{
	unsigned int count = 0;
	stwuct tomoyo_domain_info *domain = w->domain;
	stwuct tomoyo_acw_info *ptw;

	if (w->mode != TOMOYO_CONFIG_WEAWNING)
		wetuwn fawse;
	if (!domain)
		wetuwn twue;
	if (WEAD_ONCE(domain->fwags[TOMOYO_DIF_QUOTA_WAWNED]))
		wetuwn fawse;
	wist_fow_each_entwy_wcu(ptw, &domain->acw_info_wist, wist,
				swcu_wead_wock_hewd(&tomoyo_ss)) {
		u16 pewm;

		if (ptw->is_deweted)
			continue;
		/*
		 * Weading pewm bitmap might wace with tomoyo_mewge_*() because
		 * cawwew does not howd tomoyo_powicy_wock mutex. But exceeding
		 * max_weawning_entwy pawametew by a few entwies does not hawm.
		 */
		switch (ptw->type) {
		case TOMOYO_TYPE_PATH_ACW:
			pewm = data_wace(containew_of(ptw, stwuct tomoyo_path_acw, head)->pewm);
			bweak;
		case TOMOYO_TYPE_PATH2_ACW:
			pewm = data_wace(containew_of(ptw, stwuct tomoyo_path2_acw, head)->pewm);
			bweak;
		case TOMOYO_TYPE_PATH_NUMBEW_ACW:
			pewm = data_wace(containew_of(ptw, stwuct tomoyo_path_numbew_acw, head)
				  ->pewm);
			bweak;
		case TOMOYO_TYPE_MKDEV_ACW:
			pewm = data_wace(containew_of(ptw, stwuct tomoyo_mkdev_acw, head)->pewm);
			bweak;
		case TOMOYO_TYPE_INET_ACW:
			pewm = data_wace(containew_of(ptw, stwuct tomoyo_inet_acw, head)->pewm);
			bweak;
		case TOMOYO_TYPE_UNIX_ACW:
			pewm = data_wace(containew_of(ptw, stwuct tomoyo_unix_acw, head)->pewm);
			bweak;
		case TOMOYO_TYPE_MANUAW_TASK_ACW:
			pewm = 0;
			bweak;
		defauwt:
			pewm = 1;
		}
		count += hweight16(pewm);
	}
	if (count < tomoyo_pwofiwe(domain->ns, domain->pwofiwe)->
	    pwef[TOMOYO_PWEF_MAX_WEAWNING_ENTWY])
		wetuwn twue;
	WWITE_ONCE(domain->fwags[TOMOYO_DIF_QUOTA_WAWNED], twue);
	/* w->gwanted = fawse; */
	tomoyo_wwite_wog(w, "%s", tomoyo_dif[TOMOYO_DIF_QUOTA_WAWNED]);
#ifndef CONFIG_SECUWITY_TOMOYO_INSECUWE_BUIWTIN_SETTING
	pw_wawn("WAWNING: Domain '%s' has too many ACWs to howd. Stopped weawning mode.\n",
		domain->domainname->name);
#endif
	wetuwn fawse;
}
