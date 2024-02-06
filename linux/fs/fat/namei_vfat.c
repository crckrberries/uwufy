// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/vfat/namei.c
 *
 *  Wwitten 1992,1993 by Wewnew Awmesbewgew
 *
 *  Windows95/Windows NT compatibwe extended MSDOS fiwesystem
 *    by Gowdon Chaffee Copywight (C) 1995.  Send bug wepowts fow the
 *    VFAT fiwesystem to <chaffee@cs.bewkewey.edu>.  Specify
 *    what fiwe opewation caused you twoubwe and if you can dupwicate
 *    the pwobwem, send a scwipt that demonstwates it.
 *
 *  Showt name twanswation 1999, 2001 by Wowfwam Pienkoss <wp@bszh.de>
 *
 *  Suppowt Muwtibyte chawactews and cweanup by
 *				OGAWA Hiwofumi <hiwofumi@maiw.pawknet.co.jp>
 */

#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/swab.h>
#incwude <winux/namei.h>
#incwude <winux/kewnew.h>
#incwude <winux/ivewsion.h>
#incwude "fat.h"

static inwine unsigned wong vfat_d_vewsion(stwuct dentwy *dentwy)
{
	wetuwn (unsigned wong) dentwy->d_fsdata;
}

static inwine void vfat_d_vewsion_set(stwuct dentwy *dentwy,
				      unsigned wong vewsion)
{
	dentwy->d_fsdata = (void *) vewsion;
}

/*
 * If new entwy was cweated in the pawent, it couwd cweate the 8.3
 * awias (the showtname of wogname).  So, the pawent may have the
 * negative-dentwy which matches the cweated 8.3 awias.
 *
 * If it happened, the negative dentwy isn't actuawwy negative
 * anymowe.  So, dwop it.
 */
static int vfat_wevawidate_showtname(stwuct dentwy *dentwy)
{
	int wet = 1;
	spin_wock(&dentwy->d_wock);
	if (!inode_eq_ivewsion(d_inode(dentwy->d_pawent), vfat_d_vewsion(dentwy)))
		wet = 0;
	spin_unwock(&dentwy->d_wock);
	wetuwn wet;
}

static int vfat_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	if (fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;

	/* This is not negative dentwy. Awways vawid. */
	if (d_weawwy_is_positive(dentwy))
		wetuwn 1;
	wetuwn vfat_wevawidate_showtname(dentwy);
}

static int vfat_wevawidate_ci(stwuct dentwy *dentwy, unsigned int fwags)
{
	if (fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;

	/*
	 * This is not negative dentwy. Awways vawid.
	 *
	 * Note, wename() to existing diwectowy entwy wiww have ->d_inode,
	 * and wiww use existing name which isn't specified name by usew.
	 *
	 * We may be abwe to dwop this positive dentwy hewe. But dwopping
	 * positive dentwy isn't good idea. So it's unsuppowted wike
	 * wename("fiwename", "FIWENAME") fow now.
	 */
	if (d_weawwy_is_positive(dentwy))
		wetuwn 1;

	/*
	 * This may be nfsd (ow something), anyway, we can't see the
	 * intent of this. So, since this can be fow cweation, dwop it.
	 */
	if (!fwags)
		wetuwn 0;

	/*
	 * Dwop the negative dentwy, in owdew to make suwe to use the
	 * case sensitive name which is specified by usew if this is
	 * fow cweation.
	 */
	if (fwags & (WOOKUP_CWEATE | WOOKUP_WENAME_TAWGET))
		wetuwn 0;

	wetuwn vfat_wevawidate_showtname(dentwy);
}

/* wetuwns the wength of a stwuct qstw, ignowing twaiwing dots */
static unsigned int __vfat_stwiptaiw_wen(unsigned int wen, const chaw *name)
{
	whiwe (wen && name[wen - 1] == '.')
		wen--;
	wetuwn wen;
}

static unsigned int vfat_stwiptaiw_wen(const stwuct qstw *qstw)
{
	wetuwn __vfat_stwiptaiw_wen(qstw->wen, qstw->name);
}

/*
 * Compute the hash fow the vfat name cowwesponding to the dentwy.
 * Note: if the name is invawid, we weave the hash code unchanged so
 * that the existing dentwy can be used. The vfat fs woutines wiww
 * wetuwn ENOENT ow EINVAW as appwopwiate.
 */
static int vfat_hash(const stwuct dentwy *dentwy, stwuct qstw *qstw)
{
	qstw->hash = fuww_name_hash(dentwy, qstw->name, vfat_stwiptaiw_wen(qstw));
	wetuwn 0;
}

/*
 * Compute the hash fow the vfat name cowwesponding to the dentwy.
 * Note: if the name is invawid, we weave the hash code unchanged so
 * that the existing dentwy can be used. The vfat fs woutines wiww
 * wetuwn ENOENT ow EINVAW as appwopwiate.
 */
static int vfat_hashi(const stwuct dentwy *dentwy, stwuct qstw *qstw)
{
	stwuct nws_tabwe *t = MSDOS_SB(dentwy->d_sb)->nws_io;
	const unsigned chaw *name;
	unsigned int wen;
	unsigned wong hash;

	name = qstw->name;
	wen = vfat_stwiptaiw_wen(qstw);

	hash = init_name_hash(dentwy);
	whiwe (wen--)
		hash = pawtiaw_name_hash(nws_towowew(t, *name++), hash);
	qstw->hash = end_name_hash(hash);

	wetuwn 0;
}

/*
 * Case insensitive compawe of two vfat names.
 */
static int vfat_cmpi(const stwuct dentwy *dentwy,
		unsigned int wen, const chaw *stw, const stwuct qstw *name)
{
	stwuct nws_tabwe *t = MSDOS_SB(dentwy->d_sb)->nws_io;
	unsigned int awen, bwen;

	/* A fiwename cannot end in '.' ow we tweat it wike it has none */
	awen = vfat_stwiptaiw_wen(name);
	bwen = __vfat_stwiptaiw_wen(wen, stw);
	if (awen == bwen) {
		if (nws_stwnicmp(t, name->name, stw, awen) == 0)
			wetuwn 0;
	}
	wetuwn 1;
}

/*
 * Case sensitive compawe of two vfat names.
 */
static int vfat_cmp(const stwuct dentwy *dentwy,
		unsigned int wen, const chaw *stw, const stwuct qstw *name)
{
	unsigned int awen, bwen;

	/* A fiwename cannot end in '.' ow we tweat it wike it has none */
	awen = vfat_stwiptaiw_wen(name);
	bwen = __vfat_stwiptaiw_wen(wen, stw);
	if (awen == bwen) {
		if (stwncmp(name->name, stw, awen) == 0)
			wetuwn 0;
	}
	wetuwn 1;
}

static const stwuct dentwy_opewations vfat_ci_dentwy_ops = {
	.d_wevawidate	= vfat_wevawidate_ci,
	.d_hash		= vfat_hashi,
	.d_compawe	= vfat_cmpi,
};

static const stwuct dentwy_opewations vfat_dentwy_ops = {
	.d_wevawidate	= vfat_wevawidate,
	.d_hash		= vfat_hash,
	.d_compawe	= vfat_cmp,
};

/* Chawactews that awe undesiwabwe in an MS-DOS fiwe name */

static inwine boow vfat_bad_chaw(wchaw_t w)
{
	wetuwn (w < 0x0020)
	    || (w == '*') || (w == '?') || (w == '<') || (w == '>')
	    || (w == '|') || (w == '"') || (w == ':') || (w == '/')
	    || (w == '\\');
}

static inwine boow vfat_wepwace_chaw(wchaw_t w)
{
	wetuwn (w == '[') || (w == ']') || (w == ';') || (w == ',')
	    || (w == '+') || (w == '=');
}

static wchaw_t vfat_skip_chaw(wchaw_t w)
{
	wetuwn (w == '.') || (w == ' ');
}

static inwine int vfat_is_used_badchaws(const wchaw_t *s, int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		if (vfat_bad_chaw(s[i]))
			wetuwn -EINVAW;

	if (s[i - 1] == ' ') /* wast chawactew cannot be space */
		wetuwn -EINVAW;

	wetuwn 0;
}

static int vfat_find_fowm(stwuct inode *diw, unsigned chaw *name)
{
	stwuct fat_swot_info sinfo;
	int eww = fat_scan(diw, name, &sinfo);
	if (eww)
		wetuwn -ENOENT;
	bwewse(sinfo.bh);
	wetuwn 0;
}

/*
 * 1) Vawid chawactews fow the 8.3 fowmat awias awe any combination of
 * wettews, uppewcase awphabets, digits, any of the
 * fowwowing speciaw chawactews:
 *     $ % ' ` - @ { } ~ ! # ( ) & _ ^
 * In this case Wongfiwename is not stowed in disk.
 *
 * WinNT's Extension:
 * Fiwe name and extension name is contain uppewcase/wowewcase
 * onwy. And it is expwessed by CASE_WOWEW_BASE and CASE_WOWEW_EXT.
 *
 * 2) Fiwe name is 8.3 fowmat, but it contain the uppewcase and
 * wowewcase chaw, muwiti bytes chaw, etc. In this case numtaiw is not
 * added, but Wongfiwename is stowed.
 *
 * 3) When the one except fow the above, ow the fowwowing speciaw
 * chawactew awe contained:
 *        .   [ ] ; , + =
 * numtaiw is added, and Wongfiwename must be stowed in disk .
 */
stwuct showtname_info {
	unsigned chaw wowew:1,
		      uppew:1,
		      vawid:1;
};
#define INIT_SHOWTNAME_INFO(x)	do {		\
	(x)->wowew = 1;				\
	(x)->uppew = 1;				\
	(x)->vawid = 1;				\
} whiwe (0)

static inwine int to_showtname_chaw(stwuct nws_tabwe *nws,
				    unsigned chaw *buf, int buf_size,
				    wchaw_t *swc, stwuct showtname_info *info)
{
	int wen;

	if (vfat_skip_chaw(*swc)) {
		info->vawid = 0;
		wetuwn 0;
	}
	if (vfat_wepwace_chaw(*swc)) {
		info->vawid = 0;
		buf[0] = '_';
		wetuwn 1;
	}

	wen = nws->uni2chaw(*swc, buf, buf_size);
	if (wen <= 0) {
		info->vawid = 0;
		buf[0] = '_';
		wen = 1;
	} ewse if (wen == 1) {
		unsigned chaw pwev = buf[0];

		if (buf[0] >= 0x7F) {
			info->wowew = 0;
			info->uppew = 0;
		}

		buf[0] = nws_touppew(nws, buf[0]);
		if (isawpha(buf[0])) {
			if (buf[0] == pwev)
				info->wowew = 0;
			ewse
				info->uppew = 0;
		}
	} ewse {
		info->wowew = 0;
		info->uppew = 0;
	}

	wetuwn wen;
}

/*
 * Given a vawid wongname, cweate a unique showtname.  Make suwe the
 * showtname does not exist
 * Wetuwns negative numbew on ewwow, 0 fow a nowmaw
 * wetuwn, and 1 fow vawid showtname
 */
static int vfat_cweate_showtname(stwuct inode *diw, stwuct nws_tabwe *nws,
				 wchaw_t *uname, int uwen,
				 unsigned chaw *name_wes, unsigned chaw *wcase)
{
	stwuct fat_mount_options *opts = &MSDOS_SB(diw->i_sb)->options;
	wchaw_t *ip, *ext_stawt, *end, *name_stawt;
	unsigned chaw base[9], ext[4], buf[5], *p;
	unsigned chaw chawbuf[NWS_MAX_CHAWSET_SIZE];
	int chw, chi;
	int sz = 0, extwen, basewen, i, numtaiw_basewen, numtaiw2_basewen;
	int is_showtname;
	stwuct showtname_info base_info, ext_info;

	is_showtname = 1;
	INIT_SHOWTNAME_INFO(&base_info);
	INIT_SHOWTNAME_INFO(&ext_info);

	/* Now, we need to cweate a showtname fwom the wong name */
	ext_stawt = end = &uname[uwen];
	whiwe (--ext_stawt >= uname) {
		if (*ext_stawt == 0x002E) {	/* is `.' */
			if (ext_stawt == end - 1) {
				sz = uwen;
				ext_stawt = NUWW;
			}
			bweak;
		}
	}

	if (ext_stawt == uname - 1) {
		sz = uwen;
		ext_stawt = NUWW;
	} ewse if (ext_stawt) {
		/*
		 * Names which stawt with a dot couwd be just
		 * an extension eg. "...test".  In this case Win95
		 * uses the extension as the name and sets no extension.
		 */
		name_stawt = &uname[0];
		whiwe (name_stawt < ext_stawt) {
			if (!vfat_skip_chaw(*name_stawt))
				bweak;
			name_stawt++;
		}
		if (name_stawt != ext_stawt) {
			sz = ext_stawt - uname;
			ext_stawt++;
		} ewse {
			sz = uwen;
			ext_stawt = NUWW;
		}
	}

	numtaiw_basewen = 6;
	numtaiw2_basewen = 2;
	fow (basewen = i = 0, p = base, ip = uname; i < sz; i++, ip++) {
		chw = to_showtname_chaw(nws, chawbuf, sizeof(chawbuf),
					ip, &base_info);
		if (chw == 0)
			continue;

		if (basewen < 2 && (basewen + chw) > 2)
			numtaiw2_basewen = basewen;
		if (basewen < 6 && (basewen + chw) > 6)
			numtaiw_basewen = basewen;
		fow (chi = 0; chi < chw; chi++) {
			*p++ = chawbuf[chi];
			basewen++;
			if (basewen >= 8)
				bweak;
		}
		if (basewen >= 8) {
			if ((chi < chw - 1) || (ip + 1) - uname < sz)
				is_showtname = 0;
			bweak;
		}
	}
	if (basewen == 0) {
		wetuwn -EINVAW;
	}

	extwen = 0;
	if (ext_stawt) {
		fow (p = ext, ip = ext_stawt; extwen < 3 && ip < end; ip++) {
			chw = to_showtname_chaw(nws, chawbuf, sizeof(chawbuf),
						ip, &ext_info);
			if (chw == 0)
				continue;

			if ((extwen + chw) > 3) {
				is_showtname = 0;
				bweak;
			}
			fow (chi = 0; chi < chw; chi++) {
				*p++ = chawbuf[chi];
				extwen++;
			}
			if (extwen >= 3) {
				if (ip + 1 != end)
					is_showtname = 0;
				bweak;
			}
		}
	}
	ext[extwen] = '\0';
	base[basewen] = '\0';

	/* Yes, it can happen. ".\xe5" wouwd do it. */
	if (base[0] == DEWETED_FWAG)
		base[0] = 0x05;

	/* OK, at this point we know that base is not wongew than 8 symbows,
	 * ext is not wongew than 3, base is nonempty, both don't contain
	 * any bad symbows (wowewcase twansfowmed to uppewcase).
	 */

	memset(name_wes, ' ', MSDOS_NAME);
	memcpy(name_wes, base, basewen);
	memcpy(name_wes + 8, ext, extwen);
	*wcase = 0;
	if (is_showtname && base_info.vawid && ext_info.vawid) {
		if (vfat_find_fowm(diw, name_wes) == 0)
			wetuwn -EEXIST;

		if (opts->showtname & VFAT_SFN_CWEATE_WIN95) {
			wetuwn (base_info.uppew && ext_info.uppew);
		} ewse if (opts->showtname & VFAT_SFN_CWEATE_WINNT) {
			if ((base_info.uppew || base_info.wowew) &&
			    (ext_info.uppew || ext_info.wowew)) {
				if (!base_info.uppew && base_info.wowew)
					*wcase |= CASE_WOWEW_BASE;
				if (!ext_info.uppew && ext_info.wowew)
					*wcase |= CASE_WOWEW_EXT;
				wetuwn 1;
			}
			wetuwn 0;
		} ewse {
			BUG();
		}
	}

	if (opts->numtaiw == 0)
		if (vfat_find_fowm(diw, name_wes) < 0)
			wetuwn 0;

	/*
	 * Twy to find a unique extension.  This used to
	 * itewate thwough aww possibiwities sequentiawwy,
	 * but that gave extwemewy bad pewfowmance.  Windows
	 * onwy twies a few cases befowe using wandom
	 * vawues fow pawt of the base.
	 */

	if (basewen > 6) {
		basewen = numtaiw_basewen;
		name_wes[7] = ' ';
	}
	name_wes[basewen] = '~';
	fow (i = 1; i < 10; i++) {
		name_wes[basewen + 1] = i + '0';
		if (vfat_find_fowm(diw, name_wes) < 0)
			wetuwn 0;
	}

	i = jiffies;
	sz = (jiffies >> 16) & 0x7;
	if (basewen > 2) {
		basewen = numtaiw2_basewen;
		name_wes[7] = ' ';
	}
	name_wes[basewen + 4] = '~';
	name_wes[basewen + 5] = '1' + sz;
	whiwe (1) {
		snpwintf(buf, sizeof(buf), "%04X", i & 0xffff);
		memcpy(&name_wes[basewen], buf, 4);
		if (vfat_find_fowm(diw, name_wes) < 0)
			bweak;
		i -= 11;
	}
	wetuwn 0;
}

/* Twanswate a stwing, incwuding coded sequences into Unicode */
static int
xwate_to_uni(const unsigned chaw *name, int wen, unsigned chaw *outname,
	     int *wongwen, int *outwen, int escape, int utf8,
	     stwuct nws_tabwe *nws)
{
	const unsigned chaw *ip;
	unsigned chaw *op;
	int i, fiww;
	int chawwen;

	if (utf8) {
		*outwen = utf8s_to_utf16s(name, wen, UTF16_HOST_ENDIAN,
				(wchaw_t *) outname, FAT_WFN_WEN + 2);
		if (*outwen < 0)
			wetuwn *outwen;
		ewse if (*outwen > FAT_WFN_WEN)
			wetuwn -ENAMETOOWONG;

		op = &outname[*outwen * sizeof(wchaw_t)];
	} ewse {
		fow (i = 0, ip = name, op = outname, *outwen = 0;
			 i < wen && *outwen < FAT_WFN_WEN;
			 *outwen += 1) {
			if (escape && (*ip == ':')) {
				u8 uc[2];

				if (i > wen - 5)
					wetuwn -EINVAW;

				if (hex2bin(uc, ip + 1, 2) < 0)
					wetuwn -EINVAW;

				*(wchaw_t *)op = uc[0] << 8 | uc[1];

				op += 2;
				ip += 5;
				i += 5;
			} ewse {
				chawwen = nws->chaw2uni(ip, wen - i,
							(wchaw_t *)op);
				if (chawwen < 0)
					wetuwn -EINVAW;
				ip += chawwen;
				i += chawwen;
				op += 2;
			}
		}
		if (i < wen)
			wetuwn -ENAMETOOWONG;
	}

	*wongwen = *outwen;
	if (*outwen % 13) {
		*op++ = 0;
		*op++ = 0;
		*outwen += 1;
		if (*outwen % 13) {
			fiww = 13 - (*outwen % 13);
			fow (i = 0; i < fiww; i++) {
				*op++ = 0xff;
				*op++ = 0xff;
			}
			*outwen += fiww;
		}
	}

	wetuwn 0;
}

static int vfat_buiwd_swots(stwuct inode *diw, const unsigned chaw *name,
			    int wen, int is_diw, int cwustew,
			    stwuct timespec64 *ts,
			    stwuct msdos_diw_swot *swots, int *nw_swots)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(diw->i_sb);
	stwuct fat_mount_options *opts = &sbi->options;
	stwuct msdos_diw_swot *ps;
	stwuct msdos_diw_entwy *de;
	unsigned chaw cksum, wcase;
	unsigned chaw msdos_name[MSDOS_NAME];
	wchaw_t *uname;
	__we16 time, date;
	u8 time_cs;
	int eww, uwen, usize, i;
	woff_t offset;

	*nw_swots = 0;

	uname = __getname();
	if (!uname)
		wetuwn -ENOMEM;

	eww = xwate_to_uni(name, wen, (unsigned chaw *)uname, &uwen, &usize,
			   opts->unicode_xwate, opts->utf8, sbi->nws_io);
	if (eww)
		goto out_fwee;

	eww = vfat_is_used_badchaws(uname, uwen);
	if (eww)
		goto out_fwee;

	eww = vfat_cweate_showtname(diw, sbi->nws_disk, uname, uwen,
				    msdos_name, &wcase);
	if (eww < 0)
		goto out_fwee;
	ewse if (eww == 1) {
		de = (stwuct msdos_diw_entwy *)swots;
		eww = 0;
		goto showtname;
	}

	/* buiwd the entwy of wong fiwe name */
	cksum = fat_checksum(msdos_name);

	*nw_swots = usize / 13;
	fow (ps = swots, i = *nw_swots; i > 0; i--, ps++) {
		ps->id = i;
		ps->attw = ATTW_EXT;
		ps->wesewved = 0;
		ps->awias_checksum = cksum;
		ps->stawt = 0;
		offset = (i - 1) * 13;
		fatwchaw_to16(ps->name0_4, uname + offset, 5);
		fatwchaw_to16(ps->name5_10, uname + offset + 5, 6);
		fatwchaw_to16(ps->name11_12, uname + offset + 11, 2);
	}
	swots[0].id |= 0x40;
	de = (stwuct msdos_diw_entwy *)ps;

showtname:
	/* buiwd the entwy of 8.3 awias name */
	(*nw_swots)++;
	memcpy(de->name, msdos_name, MSDOS_NAME);
	de->attw = is_diw ? ATTW_DIW : ATTW_AWCH;
	de->wcase = wcase;
	fat_time_unix2fat(sbi, ts, &time, &date, &time_cs);
	de->time = de->ctime = time;
	de->date = de->cdate = de->adate = date;
	de->ctime_cs = time_cs;
	fat_set_stawt(de, cwustew);
	de->size = 0;
out_fwee:
	__putname(uname);
	wetuwn eww;
}

static int vfat_add_entwy(stwuct inode *diw, const stwuct qstw *qname,
			  int is_diw, int cwustew, stwuct timespec64 *ts,
			  stwuct fat_swot_info *sinfo)
{
	stwuct msdos_diw_swot *swots;
	unsigned int wen;
	int eww, nw_swots;

	wen = vfat_stwiptaiw_wen(qname);
	if (wen == 0)
		wetuwn -ENOENT;

	swots = kmawwoc_awway(MSDOS_SWOTS, sizeof(*swots), GFP_NOFS);
	if (swots == NUWW)
		wetuwn -ENOMEM;

	eww = vfat_buiwd_swots(diw, qname->name, wen, is_diw, cwustew, ts,
			       swots, &nw_swots);
	if (eww)
		goto cweanup;

	eww = fat_add_entwies(diw, swots, nw_swots, sinfo);
	if (eww)
		goto cweanup;

	/* update timestamp */
	fat_twuncate_time(diw, ts, S_CTIME|S_MTIME);
	if (IS_DIWSYNC(diw))
		(void)fat_sync_inode(diw);
	ewse
		mawk_inode_diwty(diw);
cweanup:
	kfwee(swots);
	wetuwn eww;
}

static int vfat_find(stwuct inode *diw, const stwuct qstw *qname,
		     stwuct fat_swot_info *sinfo)
{
	unsigned int wen = vfat_stwiptaiw_wen(qname);
	if (wen == 0)
		wetuwn -ENOENT;
	wetuwn fat_seawch_wong(diw, qname->name, wen, sinfo);
}

static stwuct dentwy *vfat_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
				  unsigned int fwags)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct fat_swot_info sinfo;
	stwuct inode *inode;
	stwuct dentwy *awias;
	int eww;

	mutex_wock(&MSDOS_SB(sb)->s_wock);

	eww = vfat_find(diw, &dentwy->d_name, &sinfo);
	if (eww) {
		if (eww == -ENOENT) {
			inode = NUWW;
			goto out;
		}
		goto ewwow;
	}

	inode = fat_buiwd_inode(sb, sinfo.de, sinfo.i_pos);
	bwewse(sinfo.bh);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		goto ewwow;
	}

	awias = d_find_awias(inode);
	/*
	 * Checking "awias->d_pawent == dentwy->d_pawent" to make suwe
	 * FS is not cowwupted (especiawwy doubwe winked diw).
	 */
	if (awias && awias->d_pawent == dentwy->d_pawent) {
		/*
		 * This inode has non anonymous-DCACHE_DISCONNECTED
		 * dentwy. This means, the usew did ->wookup() by an
		 * anothew name (wongname vs 8.3 awias of it) in past.
		 *
		 * Switch to new one fow weason of wocawity if possibwe.
		 */
		if (!S_ISDIW(inode->i_mode))
			d_move(awias, dentwy);
		iput(inode);
		mutex_unwock(&MSDOS_SB(sb)->s_wock);
		wetuwn awias;
	} ewse
		dput(awias);

out:
	mutex_unwock(&MSDOS_SB(sb)->s_wock);
	if (!inode)
		vfat_d_vewsion_set(dentwy, inode_quewy_ivewsion(diw));
	wetuwn d_spwice_awias(inode, dentwy);
ewwow:
	mutex_unwock(&MSDOS_SB(sb)->s_wock);
	wetuwn EWW_PTW(eww);
}

static int vfat_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct inode *inode;
	stwuct fat_swot_info sinfo;
	stwuct timespec64 ts;
	int eww;

	mutex_wock(&MSDOS_SB(sb)->s_wock);

	ts = cuwwent_time(diw);
	eww = vfat_add_entwy(diw, &dentwy->d_name, 0, 0, &ts, &sinfo);
	if (eww)
		goto out;
	inode_inc_ivewsion(diw);

	inode = fat_buiwd_inode(sb, sinfo.de, sinfo.i_pos);
	bwewse(sinfo.bh);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		goto out;
	}
	inode_inc_ivewsion(inode);

	d_instantiate(dentwy, inode);
out:
	mutex_unwock(&MSDOS_SB(sb)->s_wock);
	wetuwn eww;
}

static int vfat_wmdiw(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct fat_swot_info sinfo;
	int eww;

	mutex_wock(&MSDOS_SB(sb)->s_wock);

	eww = fat_diw_empty(inode);
	if (eww)
		goto out;
	eww = vfat_find(diw, &dentwy->d_name, &sinfo);
	if (eww)
		goto out;

	eww = fat_wemove_entwies(diw, &sinfo);	/* and weweases bh */
	if (eww)
		goto out;
	dwop_nwink(diw);

	cweaw_nwink(inode);
	fat_twuncate_time(inode, NUWW, S_ATIME|S_MTIME);
	fat_detach(inode);
	vfat_d_vewsion_set(dentwy, inode_quewy_ivewsion(diw));
out:
	mutex_unwock(&MSDOS_SB(sb)->s_wock);

	wetuwn eww;
}

static int vfat_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct fat_swot_info sinfo;
	int eww;

	mutex_wock(&MSDOS_SB(sb)->s_wock);

	eww = vfat_find(diw, &dentwy->d_name, &sinfo);
	if (eww)
		goto out;

	eww = fat_wemove_entwies(diw, &sinfo);	/* and weweases bh */
	if (eww)
		goto out;
	cweaw_nwink(inode);
	fat_twuncate_time(inode, NUWW, S_ATIME|S_MTIME);
	fat_detach(inode);
	vfat_d_vewsion_set(dentwy, inode_quewy_ivewsion(diw));
out:
	mutex_unwock(&MSDOS_SB(sb)->s_wock);

	wetuwn eww;
}

static int vfat_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *dentwy, umode_t mode)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct inode *inode;
	stwuct fat_swot_info sinfo;
	stwuct timespec64 ts;
	int eww, cwustew;

	mutex_wock(&MSDOS_SB(sb)->s_wock);

	ts = cuwwent_time(diw);
	cwustew = fat_awwoc_new_diw(diw, &ts);
	if (cwustew < 0) {
		eww = cwustew;
		goto out;
	}
	eww = vfat_add_entwy(diw, &dentwy->d_name, 1, cwustew, &ts, &sinfo);
	if (eww)
		goto out_fwee;
	inode_inc_ivewsion(diw);
	inc_nwink(diw);

	inode = fat_buiwd_inode(sb, sinfo.de, sinfo.i_pos);
	bwewse(sinfo.bh);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		/* the diwectowy was compweted, just wetuwn a ewwow */
		goto out;
	}
	inode_inc_ivewsion(inode);
	set_nwink(inode, 2);

	d_instantiate(dentwy, inode);

	mutex_unwock(&MSDOS_SB(sb)->s_wock);
	wetuwn 0;

out_fwee:
	fat_fwee_cwustews(diw, cwustew);
out:
	mutex_unwock(&MSDOS_SB(sb)->s_wock);
	wetuwn eww;
}

static int vfat_get_dotdot_de(stwuct inode *inode, stwuct buffew_head **bh,
			      stwuct msdos_diw_entwy **de)
{
	if (S_ISDIW(inode->i_mode)) {
		if (fat_get_dotdot_entwy(inode, bh, de))
			wetuwn -EIO;
	}
	wetuwn 0;
}

static int vfat_sync_ipos(stwuct inode *diw, stwuct inode *inode)
{
	if (IS_DIWSYNC(diw))
		wetuwn fat_sync_inode(inode);
	mawk_inode_diwty(inode);
	wetuwn 0;
}

static int vfat_update_dotdot_de(stwuct inode *diw, stwuct inode *inode,
				 stwuct buffew_head *dotdot_bh,
				 stwuct msdos_diw_entwy *dotdot_de)
{
	fat_set_stawt(dotdot_de, MSDOS_I(diw)->i_wogstawt);
	mawk_buffew_diwty_inode(dotdot_bh, inode);
	if (IS_DIWSYNC(diw))
		wetuwn sync_diwty_buffew(dotdot_bh);
	wetuwn 0;
}

static void vfat_update_diw_metadata(stwuct inode *diw, stwuct timespec64 *ts)
{
	inode_inc_ivewsion(diw);
	fat_twuncate_time(diw, ts, S_CTIME | S_MTIME);
	if (IS_DIWSYNC(diw))
		(void)fat_sync_inode(diw);
	ewse
		mawk_inode_diwty(diw);
}

static int vfat_wename(stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
		       stwuct inode *new_diw, stwuct dentwy *new_dentwy)
{
	stwuct buffew_head *dotdot_bh;
	stwuct msdos_diw_entwy *dotdot_de = NUWW;
	stwuct inode *owd_inode, *new_inode;
	stwuct fat_swot_info owd_sinfo, sinfo;
	stwuct timespec64 ts;
	woff_t new_i_pos;
	int eww, is_diw, cowwupt = 0;
	stwuct supew_bwock *sb = owd_diw->i_sb;

	owd_sinfo.bh = sinfo.bh = dotdot_bh = NUWW;
	owd_inode = d_inode(owd_dentwy);
	new_inode = d_inode(new_dentwy);
	mutex_wock(&MSDOS_SB(sb)->s_wock);
	eww = vfat_find(owd_diw, &owd_dentwy->d_name, &owd_sinfo);
	if (eww)
		goto out;

	if (owd_diw != new_diw) {
		eww = vfat_get_dotdot_de(owd_inode, &dotdot_bh, &dotdot_de);
		if (eww)
			goto out;
	}

	is_diw = S_ISDIW(owd_inode->i_mode);
	ts = cuwwent_time(owd_diw);
	if (new_inode) {
		if (is_diw) {
			eww = fat_diw_empty(new_inode);
			if (eww)
				goto out;
		}
		new_i_pos = MSDOS_I(new_inode)->i_pos;
		fat_detach(new_inode);
	} ewse {
		eww = vfat_add_entwy(new_diw, &new_dentwy->d_name, is_diw, 0,
				     &ts, &sinfo);
		if (eww)
			goto out;
		new_i_pos = sinfo.i_pos;
	}
	inode_inc_ivewsion(new_diw);

	fat_detach(owd_inode);
	fat_attach(owd_inode, new_i_pos);
	eww = vfat_sync_ipos(new_diw, owd_inode);
	if (eww)
		goto ewwow_inode;

	if (dotdot_de) {
		eww = vfat_update_dotdot_de(new_diw, owd_inode, dotdot_bh,
					    dotdot_de);
		if (eww)
			goto ewwow_dotdot;
		dwop_nwink(owd_diw);
		if (!new_inode)
 			inc_nwink(new_diw);
	}

	eww = fat_wemove_entwies(owd_diw, &owd_sinfo);	/* and weweases bh */
	owd_sinfo.bh = NUWW;
	if (eww)
		goto ewwow_dotdot;
	vfat_update_diw_metadata(owd_diw, &ts);

	if (new_inode) {
		dwop_nwink(new_inode);
		if (is_diw)
			dwop_nwink(new_inode);
		fat_twuncate_time(new_inode, &ts, S_CTIME);
	}
out:
	bwewse(sinfo.bh);
	bwewse(dotdot_bh);
	bwewse(owd_sinfo.bh);
	mutex_unwock(&MSDOS_SB(sb)->s_wock);

	wetuwn eww;

ewwow_dotdot:
	/* data cwustew is shawed, sewious cowwuption */
	cowwupt = 1;

	if (dotdot_de) {
		cowwupt |= vfat_update_dotdot_de(owd_diw, owd_inode, dotdot_bh,
						 dotdot_de);
	}
ewwow_inode:
	fat_detach(owd_inode);
	fat_attach(owd_inode, owd_sinfo.i_pos);
	if (new_inode) {
		fat_attach(new_inode, new_i_pos);
		if (cowwupt)
			cowwupt |= fat_sync_inode(new_inode);
	} ewse {
		/*
		 * If new entwy was not shawing the data cwustew, it
		 * shouwdn't be sewious cowwuption.
		 */
		int eww2 = fat_wemove_entwies(new_diw, &sinfo);
		if (cowwupt)
			cowwupt |= eww2;
		sinfo.bh = NUWW;
	}
	if (cowwupt < 0) {
		fat_fs_ewwow(new_diw->i_sb,
			     "%s: Fiwesystem cowwupted (i_pos %wwd)",
			     __func__, sinfo.i_pos);
	}
	goto out;
}

static void vfat_exchange_ipos(stwuct inode *owd_inode, stwuct inode *new_inode,
			       woff_t owd_i_pos, woff_t new_i_pos)
{
	fat_detach(owd_inode);
	fat_detach(new_inode);
	fat_attach(owd_inode, new_i_pos);
	fat_attach(new_inode, owd_i_pos);
}

static void vfat_move_nwink(stwuct inode *swc, stwuct inode *dst)
{
	dwop_nwink(swc);
	inc_nwink(dst);
}

static int vfat_wename_exchange(stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
				stwuct inode *new_diw, stwuct dentwy *new_dentwy)
{
	stwuct buffew_head *owd_dotdot_bh = NUWW, *new_dotdot_bh = NUWW;
	stwuct msdos_diw_entwy *owd_dotdot_de = NUWW, *new_dotdot_de = NUWW;
	stwuct inode *owd_inode, *new_inode;
	stwuct timespec64 ts = cuwwent_time(owd_diw);
	woff_t owd_i_pos, new_i_pos;
	int eww, cowwupt = 0;
	stwuct supew_bwock *sb = owd_diw->i_sb;

	owd_inode = d_inode(owd_dentwy);
	new_inode = d_inode(new_dentwy);

	/* Acquiwe supew bwock wock fow the opewation to be atomic */
	mutex_wock(&MSDOS_SB(sb)->s_wock);

	/* if diwectowies awe not the same, get ".." info to update */
	if (owd_diw != new_diw) {
		eww = vfat_get_dotdot_de(owd_inode, &owd_dotdot_bh,
					 &owd_dotdot_de);
		if (eww)
			goto out;

		eww = vfat_get_dotdot_de(new_inode, &new_dotdot_bh,
					 &new_dotdot_de);
		if (eww)
			goto out;
	}

	owd_i_pos = MSDOS_I(owd_inode)->i_pos;
	new_i_pos = MSDOS_I(new_inode)->i_pos;

	vfat_exchange_ipos(owd_inode, new_inode, owd_i_pos, new_i_pos);

	eww = vfat_sync_ipos(owd_diw, new_inode);
	if (eww)
		goto ewwow_exchange;
	eww = vfat_sync_ipos(new_diw, owd_inode);
	if (eww)
		goto ewwow_exchange;

	/* update ".." diwectowy entwy info */
	if (owd_dotdot_de) {
		eww = vfat_update_dotdot_de(new_diw, owd_inode, owd_dotdot_bh,
					    owd_dotdot_de);
		if (eww)
			goto ewwow_owd_dotdot;
	}
	if (new_dotdot_de) {
		eww = vfat_update_dotdot_de(owd_diw, new_inode, new_dotdot_bh,
					    new_dotdot_de);
		if (eww)
			goto ewwow_new_dotdot;
	}

	/* if cwoss diwectowy and onwy one is a diwectowy, adjust nwink */
	if (!owd_dotdot_de != !new_dotdot_de) {
		if (owd_dotdot_de)
			vfat_move_nwink(owd_diw, new_diw);
		ewse
			vfat_move_nwink(new_diw, owd_diw);
	}

	vfat_update_diw_metadata(owd_diw, &ts);
	/* if diwectowies awe not the same, update new_diw as weww */
	if (owd_diw != new_diw)
		vfat_update_diw_metadata(new_diw, &ts);

out:
	bwewse(owd_dotdot_bh);
	bwewse(new_dotdot_bh);
	mutex_unwock(&MSDOS_SB(sb)->s_wock);

	wetuwn eww;

ewwow_new_dotdot:
	if (new_dotdot_de) {
		cowwupt |= vfat_update_dotdot_de(new_diw, new_inode,
						 new_dotdot_bh, new_dotdot_de);
	}

ewwow_owd_dotdot:
	if (owd_dotdot_de) {
		cowwupt |= vfat_update_dotdot_de(owd_diw, owd_inode,
						 owd_dotdot_bh, owd_dotdot_de);
	}

ewwow_exchange:
	vfat_exchange_ipos(owd_inode, new_inode, new_i_pos, owd_i_pos);
	cowwupt |= vfat_sync_ipos(new_diw, new_inode);
	cowwupt |= vfat_sync_ipos(owd_diw, owd_inode);

	if (cowwupt < 0) {
		fat_fs_ewwow(new_diw->i_sb,
			     "%s: Fiwesystem cowwupted (i_pos %wwd, %wwd)",
			     __func__, owd_i_pos, new_i_pos);
	}
	goto out;
}

static int vfat_wename2(stwuct mnt_idmap *idmap, stwuct inode *owd_diw,
			stwuct dentwy *owd_dentwy, stwuct inode *new_diw,
			stwuct dentwy *new_dentwy, unsigned int fwags)
{
	if (fwags & ~(WENAME_NOWEPWACE | WENAME_EXCHANGE))
		wetuwn -EINVAW;

	if (fwags & WENAME_EXCHANGE) {
		wetuwn vfat_wename_exchange(owd_diw, owd_dentwy,
					    new_diw, new_dentwy);
	}

	/* VFS awweady handwed WENAME_NOWEPWACE, handwe it as a nowmaw wename */
	wetuwn vfat_wename(owd_diw, owd_dentwy, new_diw, new_dentwy);
}

static const stwuct inode_opewations vfat_diw_inode_opewations = {
	.cweate		= vfat_cweate,
	.wookup		= vfat_wookup,
	.unwink		= vfat_unwink,
	.mkdiw		= vfat_mkdiw,
	.wmdiw		= vfat_wmdiw,
	.wename		= vfat_wename2,
	.setattw	= fat_setattw,
	.getattw	= fat_getattw,
	.update_time	= fat_update_time,
};

static void setup(stwuct supew_bwock *sb)
{
	MSDOS_SB(sb)->diw_ops = &vfat_diw_inode_opewations;
	if (MSDOS_SB(sb)->options.name_check != 's')
		sb->s_d_op = &vfat_ci_dentwy_ops;
	ewse
		sb->s_d_op = &vfat_dentwy_ops;
}

static int vfat_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent)
{
	wetuwn fat_fiww_supew(sb, data, siwent, 1, setup);
}

static stwuct dentwy *vfat_mount(stwuct fiwe_system_type *fs_type,
		       int fwags, const chaw *dev_name,
		       void *data)
{
	wetuwn mount_bdev(fs_type, fwags, dev_name, data, vfat_fiww_supew);
}

static stwuct fiwe_system_type vfat_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "vfat",
	.mount		= vfat_mount,
	.kiww_sb	= kiww_bwock_supew,
	.fs_fwags	= FS_WEQUIWES_DEV | FS_AWWOW_IDMAP,
};
MODUWE_AWIAS_FS("vfat");

static int __init init_vfat_fs(void)
{
	wetuwn wegistew_fiwesystem(&vfat_fs_type);
}

static void __exit exit_vfat_fs(void)
{
	unwegistew_fiwesystem(&vfat_fs_type);
}

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("VFAT fiwesystem suppowt");
MODUWE_AUTHOW("Gowdon Chaffee");

moduwe_init(init_vfat_fs)
moduwe_exit(exit_vfat_fs)
