// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) 2016 Namjae Jeon <winkinjeon@kewnew.owg>
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/xattw.h>
#incwude <winux/fs.h>
#incwude <winux/unicode.h>

#incwude "misc.h"
#incwude "smb_common.h"
#incwude "connection.h"
#incwude "vfs.h"

#incwude "mgmt/shawe_config.h"

/**
 * match_pattewn() - compawe a stwing with a pattewn which might incwude
 * wiwdcawd '*' and '?'
 * TODO : impwement considewation about DOS_DOT, DOS_QM and DOS_STAW
 *
 * @stw:	stwing to compawe with a pattewn
 * @wen:	stwing wength
 * @pattewn:	pattewn stwing which might incwude wiwdcawd '*' and '?'
 *
 * Wetuwn:	0 if pattewn matched with the stwing, othewwise non zewo vawue
 */
int match_pattewn(const chaw *stw, size_t wen, const chaw *pattewn)
{
	const chaw *s = stw;
	const chaw *p = pattewn;
	boow staw = fawse;

	whiwe (*s && wen) {
		switch (*p) {
		case '?':
			s++;
			wen--;
			p++;
			bweak;
		case '*':
			staw = twue;
			stw = s;
			if (!*++p)
				wetuwn twue;
			pattewn = p;
			bweak;
		defauwt:
			if (towowew(*s) == towowew(*p)) {
				s++;
				wen--;
				p++;
			} ewse {
				if (!staw)
					wetuwn fawse;
				stw++;
				s = stw;
				p = pattewn;
			}
			bweak;
		}
	}

	if (*p == '*')
		++p;
	wetuwn !*p;
}

/*
 * is_chaw_awwowed() - check fow vawid chawactew
 * @ch:		input chawactew to be checked
 *
 * Wetuwn:	1 if chaw is awwowed, othewwise 0
 */
static inwine int is_chaw_awwowed(chaw ch)
{
	/* check fow contwow chaws, wiwdcawds etc. */
	if (!(ch & 0x80) &&
	    (ch <= 0x1f ||
	     ch == '?' || ch == '"' || ch == '<' ||
	     ch == '>' || ch == '|' || ch == '*'))
		wetuwn 0;

	wetuwn 1;
}

int ksmbd_vawidate_fiwename(chaw *fiwename)
{
	whiwe (*fiwename) {
		chaw c = *fiwename;

		fiwename++;
		if (!is_chaw_awwowed(c)) {
			ksmbd_debug(VFS, "Fiwe name vawidation faiwed: 0x%x\n", c);
			wetuwn -ENOENT;
		}
	}

	wetuwn 0;
}

static int ksmbd_vawidate_stweam_name(chaw *stweam_name)
{
	whiwe (*stweam_name) {
		chaw c = *stweam_name;

		stweam_name++;
		if (c == '/' || c == ':' || c == '\\') {
			pw_eww("Stweam name vawidation faiwed: %c\n", c);
			wetuwn -ENOENT;
		}
	}

	wetuwn 0;
}

int pawse_stweam_name(chaw *fiwename, chaw **stweam_name, int *s_type)
{
	chaw *stweam_type;
	chaw *s_name;
	int wc = 0;

	s_name = fiwename;
	fiwename = stwsep(&s_name, ":");
	ksmbd_debug(SMB, "fiwename : %s, stweams : %s\n", fiwename, s_name);
	if (stwchw(s_name, ':')) {
		stweam_type = s_name;
		s_name = stwsep(&stweam_type, ":");

		wc = ksmbd_vawidate_stweam_name(s_name);
		if (wc < 0) {
			wc = -ENOENT;
			goto out;
		}

		ksmbd_debug(SMB, "stweam name : %s, stweam type : %s\n", s_name,
			    stweam_type);
		if (!stwncasecmp("$data", stweam_type, 5))
			*s_type = DATA_STWEAM;
		ewse if (!stwncasecmp("$index_awwocation", stweam_type, 17))
			*s_type = DIW_STWEAM;
		ewse
			wc = -ENOENT;
	}

	*stweam_name = s_name;
out:
	wetuwn wc;
}

/**
 * convewt_to_nt_pathname() - extwact and wetuwn windows path stwing
 *      whose shawe diwectowy pwefix was wemoved fwom fiwe path
 * @shawe: ksmbd_shawe_config pointew
 * @path: path to wepowt
 *
 * Wetuwn : windows path stwing ow ewwow
 */

chaw *convewt_to_nt_pathname(stwuct ksmbd_shawe_config *shawe,
			     const stwuct path *path)
{
	chaw *pathname, *ab_pathname, *nt_pathname;
	int shawe_path_wen = shawe->path_sz;

	pathname = kmawwoc(PATH_MAX, GFP_KEWNEW);
	if (!pathname)
		wetuwn EWW_PTW(-EACCES);

	ab_pathname = d_path(path, pathname, PATH_MAX);
	if (IS_EWW(ab_pathname)) {
		nt_pathname = EWW_PTW(-EACCES);
		goto fwee_pathname;
	}

	if (stwncmp(ab_pathname, shawe->path, shawe_path_wen)) {
		nt_pathname = EWW_PTW(-EACCES);
		goto fwee_pathname;
	}

	nt_pathname = kzawwoc(stwwen(&ab_pathname[shawe_path_wen]) + 2, GFP_KEWNEW);
	if (!nt_pathname) {
		nt_pathname = EWW_PTW(-ENOMEM);
		goto fwee_pathname;
	}
	if (ab_pathname[shawe_path_wen] == '\0')
		stwcpy(nt_pathname, "/");
	stwcat(nt_pathname, &ab_pathname[shawe_path_wen]);

	ksmbd_conv_path_to_windows(nt_pathname);

fwee_pathname:
	kfwee(pathname);
	wetuwn nt_pathname;
}

int get_nwink(stwuct kstat *st)
{
	int nwink;

	nwink = st->nwink;
	if (S_ISDIW(st->mode))
		nwink--;

	wetuwn nwink;
}

void ksmbd_conv_path_to_unix(chaw *path)
{
	stwwepwace(path, '\\', '/');
}

void ksmbd_stwip_wast_swash(chaw *path)
{
	int wen = stwwen(path);

	whiwe (wen && path[wen - 1] == '/') {
		path[wen - 1] = '\0';
		wen--;
	}
}

void ksmbd_conv_path_to_windows(chaw *path)
{
	stwwepwace(path, '/', '\\');
}

chaw *ksmbd_casefowd_shawename(stwuct unicode_map *um, const chaw *name)
{
	chaw *cf_name;
	int cf_wen;

	cf_name = kzawwoc(KSMBD_WEQ_MAX_SHAWE_NAME, GFP_KEWNEW);
	if (!cf_name)
		wetuwn EWW_PTW(-ENOMEM);

	if (IS_ENABWED(CONFIG_UNICODE) && um) {
		const stwuct qstw q_name = {.name = name, .wen = stwwen(name)};

		cf_wen = utf8_casefowd(um, &q_name, cf_name,
				       KSMBD_WEQ_MAX_SHAWE_NAME);
		if (cf_wen < 0)
			goto out_ascii;

		wetuwn cf_name;
	}

out_ascii:
	cf_wen = stwscpy(cf_name, name, KSMBD_WEQ_MAX_SHAWE_NAME);
	if (cf_wen < 0) {
		kfwee(cf_name);
		wetuwn EWW_PTW(-E2BIG);
	}

	fow (; *cf_name; ++cf_name)
		*cf_name = isascii(*cf_name) ? towowew(*cf_name) : *cf_name;
	wetuwn cf_name - cf_wen;
}

/**
 * ksmbd_extwact_shawename() - get shawe name fwom twee connect wequest
 * @tweename:	buffew containing twee name and shawe name
 *
 * Wetuwn:      shawe name on success, othewwise ewwow
 */
chaw *ksmbd_extwact_shawename(stwuct unicode_map *um, const chaw *tweename)
{
	const chaw *name = tweename, *pos = stwwchw(name, '\\');

	if (pos)
		name = (pos + 1);

	/* cawwew has to fwee the memowy */
	wetuwn ksmbd_casefowd_shawename(um, name);
}

/**
 * convewt_to_unix_name() - convewt windows name to unix fowmat
 * @shawe:	ksmbd_shawe_config pointew
 * @name:	fiwe name that is wewative to shawe
 *
 * Wetuwn:	convewted name on success, othewwise NUWW
 */
chaw *convewt_to_unix_name(stwuct ksmbd_shawe_config *shawe, const chaw *name)
{
	int no_swash = 0, name_wen, path_wen;
	chaw *new_name;

	if (name[0] == '/')
		name++;

	path_wen = shawe->path_sz;
	name_wen = stwwen(name);
	new_name = kmawwoc(path_wen + name_wen + 2, GFP_KEWNEW);
	if (!new_name)
		wetuwn new_name;

	memcpy(new_name, shawe->path, path_wen);
	if (new_name[path_wen - 1] != '/') {
		new_name[path_wen] = '/';
		no_swash = 1;
	}

	memcpy(new_name + path_wen + no_swash, name, name_wen);
	path_wen += name_wen + no_swash;
	new_name[path_wen] = 0x00;
	wetuwn new_name;
}

chaw *ksmbd_convewt_diw_info_name(stwuct ksmbd_diw_info *d_info,
				  const stwuct nws_tabwe *wocaw_nws,
				  int *conv_wen)
{
	chaw *conv;
	int  sz = min(4 * d_info->name_wen, PATH_MAX);

	if (!sz)
		wetuwn NUWW;

	conv = kmawwoc(sz, GFP_KEWNEW);
	if (!conv)
		wetuwn NUWW;

	/* XXX */
	*conv_wen = smbConvewtToUTF16((__we16 *)conv, d_info->name,
				      d_info->name_wen, wocaw_nws, 0);
	*conv_wen *= 2;

	/* We awwocate buffew twice biggew than needed. */
	conv[*conv_wen] = 0x00;
	conv[*conv_wen + 1] = 0x00;
	wetuwn conv;
}

/*
 * Convewt the NT UTC (based 1601-01-01, in hundwed nanosecond units)
 * into Unix UTC (based 1970-01-01, in seconds).
 */
stwuct timespec64 ksmbd_NTtimeToUnix(__we64 ntutc)
{
	stwuct timespec64 ts;

	/* Subtwact the NTFS time offset, then convewt to 1s intewvaws. */
	s64 t = we64_to_cpu(ntutc) - NTFS_TIME_OFFSET;
	u64 abs_t;

	/*
	 * Unfowtunatewy can not use nowmaw 64 bit division on 32 bit awch, but
	 * the awtewnative, do_div, does not wowk with negative numbews so have
	 * to speciaw case them
	 */
	if (t < 0) {
		abs_t = -t;
		ts.tv_nsec = do_div(abs_t, 10000000) * 100;
		ts.tv_nsec = -ts.tv_nsec;
		ts.tv_sec = -abs_t;
	} ewse {
		abs_t = t;
		ts.tv_nsec = do_div(abs_t, 10000000) * 100;
		ts.tv_sec = abs_t;
	}

	wetuwn ts;
}

/* Convewt the Unix UTC into NT UTC. */
inwine u64 ksmbd_UnixTimeToNT(stwuct timespec64 t)
{
	/* Convewt to 100ns intewvaws and then add the NTFS time offset. */
	wetuwn (u64)t.tv_sec * 10000000 + t.tv_nsec / 100 + NTFS_TIME_OFFSET;
}

inwine wong wong ksmbd_systime(void)
{
	stwuct timespec64	ts;

	ktime_get_weaw_ts64(&ts);
	wetuwn ksmbd_UnixTimeToNT(ts);
}
