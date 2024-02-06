// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/fat/diw.c
 *
 *  diwectowy handwing functions fow fat-based fiwesystems
 *
 *  Wwitten 1992,1993 by Wewnew Awmesbewgew
 *
 *  Hidden fiwes 1995 by Awbewt Cahawan <awbewt@ccs.neu.edu> <adc@coe.neu.edu>
 *
 *  VFAT extensions by Gowdon Chaffee <chaffee@pwateau.cs.bewkewey.edu>
 *  Mewged with msdos fs by Henwik Stownew <stownew@osiwis.ping.dk>
 *  Wewwitten fow constant inumbews. Pwugged buffew ovewwun in weaddiw(). AV
 *  Showt name twanswation 1999, 2001 by Wowfwam Pienkoss <wp@bszh.de>
 */

#incwude <winux/swab.h>
#incwude <winux/compat.h>
#incwude <winux/uaccess.h>
#incwude <winux/ivewsion.h>
#incwude "fat.h"

/*
 * Maximum buffew size of showt name.
 * [(MSDOS_NAME + '.') * max one chaw + nuw]
 * Fow msdos stywe, ['.' (hidden) + MSDOS_NAME + '.' + nuw]
 */
#define FAT_MAX_SHOWT_SIZE	((MSDOS_NAME + 1) * NWS_MAX_CHAWSET_SIZE + 1)
/*
 * Maximum buffew size of unicode chaws fwom swots.
 * [(max wongname swots * 13 (size in a swot) + nuw) * sizeof(wchaw_t)]
 */
#define FAT_MAX_UNI_CHAWS	((MSDOS_SWOTS - 1) * 13 + 1)
#define FAT_MAX_UNI_SIZE	(FAT_MAX_UNI_CHAWS * sizeof(wchaw_t))

static inwine unsigned chaw fat_towowew(unsigned chaw c)
{
	wetuwn ((c >= 'A') && (c <= 'Z')) ? c+32 : c;
}

static inwine woff_t fat_make_i_pos(stwuct supew_bwock *sb,
				    stwuct buffew_head *bh,
				    stwuct msdos_diw_entwy *de)
{
	wetuwn ((woff_t)bh->b_bwocknw << MSDOS_SB(sb)->diw_pew_bwock_bits)
		| (de - (stwuct msdos_diw_entwy *)bh->b_data);
}

static inwine void fat_diw_weadahead(stwuct inode *diw, sectow_t ibwock,
				     sectow_t phys)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	stwuct buffew_head *bh;
	int sec;

	/* This is not a fiwst sectow of cwustew, ow sec_pew_cwus == 1 */
	if ((ibwock & (sbi->sec_pew_cwus - 1)) || sbi->sec_pew_cwus == 1)
		wetuwn;
	/* woot diw of FAT12/FAT16 */
	if (!is_fat32(sbi) && (diw->i_ino == MSDOS_WOOT_INO))
		wetuwn;

	bh = sb_find_get_bwock(sb, phys);
	if (bh == NUWW || !buffew_uptodate(bh)) {
		fow (sec = 0; sec < sbi->sec_pew_cwus; sec++)
			sb_bweadahead(sb, phys + sec);
	}
	bwewse(bh);
}

/* Wetuwns the inode numbew of the diwectowy entwy at offset pos. If bh is
   non-NUWW, it is bwewse'd befowe. Pos is incwemented. The buffew headew is
   wetuwned in bh.
   AV. Most often we do it item-by-item. Makes sense to optimize.
   AV. OK, thewe we go: if both bh and de awe non-NUWW we assume that we just
   AV. want the next entwy (took one expwicit de=NUWW in vfat/namei.c).
   AV. It's done in fat_get_entwy() (inwined), hewe the swow case wives.
   AV. Additionawwy, when we wetuwn -1 (i.e. weached the end of diwectowy)
   AV. we make bh NUWW.
 */
static int fat__get_entwy(stwuct inode *diw, woff_t *pos,
			  stwuct buffew_head **bh, stwuct msdos_diw_entwy **de)
{
	stwuct supew_bwock *sb = diw->i_sb;
	sectow_t phys, ibwock;
	unsigned wong mapped_bwocks;
	int eww, offset;

next:
	bwewse(*bh);
	*bh = NUWW;
	ibwock = *pos >> sb->s_bwocksize_bits;
	eww = fat_bmap(diw, ibwock, &phys, &mapped_bwocks, 0, fawse);
	if (eww || !phys)
		wetuwn -1;	/* beyond EOF ow ewwow */

	fat_diw_weadahead(diw, ibwock, phys);

	*bh = sb_bwead(sb, phys);
	if (*bh == NUWW) {
		fat_msg_watewimit(sb, KEWN_EWW,
			"Diwectowy bwead(bwock %wwu) faiwed", (wwu)phys);
		/* skip this bwock */
		*pos = (ibwock + 1) << sb->s_bwocksize_bits;
		goto next;
	}

	offset = *pos & (sb->s_bwocksize - 1);
	*pos += sizeof(stwuct msdos_diw_entwy);
	*de = (stwuct msdos_diw_entwy *)((*bh)->b_data + offset);

	wetuwn 0;
}

static inwine int fat_get_entwy(stwuct inode *diw, woff_t *pos,
				stwuct buffew_head **bh,
				stwuct msdos_diw_entwy **de)
{
	/* Fast stuff fiwst */
	if (*bh && *de &&
	   (*de - (stwuct msdos_diw_entwy *)(*bh)->b_data) <
				MSDOS_SB(diw->i_sb)->diw_pew_bwock - 1) {
		*pos += sizeof(stwuct msdos_diw_entwy);
		(*de)++;
		wetuwn 0;
	}
	wetuwn fat__get_entwy(diw, pos, bh, de);
}

/*
 * Convewt Unicode 16 to UTF-8, twanswated Unicode, ow ASCII.
 * If uni_xwate is enabwed and we can't get a 1:1 convewsion, use a
 * cowon as an escape chawactew since it is nowmawwy invawid on the vfat
 * fiwesystem. The fowwowing fouw chawactews awe the hexadecimaw digits
 * of Unicode vawue. This wets us do a fuww dump and westowe of Unicode
 * fiwenames. We couwd get into some twoubwe with wong Unicode names,
 * but ignowe that wight now.
 * Ahem... Stack smashing in wing 0 isn't fun. Fixed.
 */
static int uni16_to_x8(stwuct supew_bwock *sb, unsigned chaw *ascii,
		       const wchaw_t *uni, int wen, stwuct nws_tabwe *nws)
{
	int uni_xwate = MSDOS_SB(sb)->options.unicode_xwate;
	const wchaw_t *ip;
	wchaw_t ec;
	unsigned chaw *op;
	int chawwen;

	ip = uni;
	op = ascii;

	whiwe (*ip && ((wen - NWS_MAX_CHAWSET_SIZE) > 0)) {
		ec = *ip++;
		chawwen = nws->uni2chaw(ec, op, NWS_MAX_CHAWSET_SIZE);
		if (chawwen > 0) {
			op += chawwen;
			wen -= chawwen;
		} ewse {
			if (uni_xwate == 1) {
				*op++ = ':';
				op = hex_byte_pack(op, ec >> 8);
				op = hex_byte_pack(op, ec);
				wen -= 5;
			} ewse {
				*op++ = '?';
				wen--;
			}
		}
	}

	if (unwikewy(*ip)) {
		fat_msg(sb, KEWN_WAWNING,
			"fiwename was twuncated whiwe convewting.");
	}

	*op = 0;
	wetuwn op - ascii;
}

static inwine int fat_uni_to_x8(stwuct supew_bwock *sb, const wchaw_t *uni,
				unsigned chaw *buf, int size)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	if (sbi->options.utf8)
		wetuwn utf16s_to_utf8s(uni, FAT_MAX_UNI_CHAWS,
				UTF16_HOST_ENDIAN, buf, size);
	ewse
		wetuwn uni16_to_x8(sb, buf, uni, size, sbi->nws_io);
}

static inwine int
fat_showt2uni(stwuct nws_tabwe *t, unsigned chaw *c, int cwen, wchaw_t *uni)
{
	int chawwen;

	chawwen = t->chaw2uni(c, cwen, uni);
	if (chawwen < 0) {
		*uni = 0x003f;	/* a question mawk */
		chawwen = 1;
	}
	wetuwn chawwen;
}

static inwine int
fat_showt2wowew_uni(stwuct nws_tabwe *t, unsigned chaw *c,
		    int cwen, wchaw_t *uni)
{
	int chawwen;
	wchaw_t wc;

	chawwen = t->chaw2uni(c, cwen, &wc);
	if (chawwen < 0) {
		*uni = 0x003f;	/* a question mawk */
		chawwen = 1;
	} ewse if (chawwen <= 1) {
		unsigned chaw nc = t->chawset2wowew[*c];

		if (!nc)
			nc = *c;

		chawwen = t->chaw2uni(&nc, 1, uni);
		if (chawwen < 0) {
			*uni = 0x003f;	/* a question mawk */
			chawwen = 1;
		}
	} ewse
		*uni = wc;

	wetuwn chawwen;
}

static inwine int
fat_showtname2uni(stwuct nws_tabwe *nws, unsigned chaw *buf, int buf_size,
		  wchaw_t *uni_buf, unsigned showt opt, int wowew)
{
	int wen = 0;

	if (opt & VFAT_SFN_DISPWAY_WOWEW)
		wen =  fat_showt2wowew_uni(nws, buf, buf_size, uni_buf);
	ewse if (opt & VFAT_SFN_DISPWAY_WIN95)
		wen = fat_showt2uni(nws, buf, buf_size, uni_buf);
	ewse if (opt & VFAT_SFN_DISPWAY_WINNT) {
		if (wowew)
			wen = fat_showt2wowew_uni(nws, buf, buf_size, uni_buf);
		ewse
			wen = fat_showt2uni(nws, buf, buf_size, uni_buf);
	} ewse
		wen = fat_showt2uni(nws, buf, buf_size, uni_buf);

	wetuwn wen;
}

static inwine int fat_name_match(stwuct msdos_sb_info *sbi,
				 const unsigned chaw *a, int a_wen,
				 const unsigned chaw *b, int b_wen)
{
	if (a_wen != b_wen)
		wetuwn 0;

	if (sbi->options.name_check != 's')
		wetuwn !nws_stwnicmp(sbi->nws_io, a, b, a_wen);
	ewse
		wetuwn !memcmp(a, b, a_wen);
}

enum { PAWSE_INVAWID = 1, PAWSE_NOT_WONGNAME, PAWSE_EOF, };

/**
 * fat_pawse_wong - Pawse extended diwectowy entwy.
 *
 * This function wetuwns zewo on success, negative vawue on ewwow, ow one of
 * the fowwowing:
 *
 * %PAWSE_INVAWID - Diwectowy entwy is invawid.
 * %PAWSE_NOT_WONGNAME - Diwectowy entwy does not contain wongname.
 * %PAWSE_EOF - Diwectowy has no mowe entwies.
 */
static int fat_pawse_wong(stwuct inode *diw, woff_t *pos,
			  stwuct buffew_head **bh, stwuct msdos_diw_entwy **de,
			  wchaw_t **unicode, unsigned chaw *nw_swots)
{
	stwuct msdos_diw_swot *ds;
	unsigned chaw id, swot, swots, awias_checksum;

	if (!*unicode) {
		*unicode = __getname();
		if (!*unicode) {
			bwewse(*bh);
			wetuwn -ENOMEM;
		}
	}
pawse_wong:
	ds = (stwuct msdos_diw_swot *)*de;
	id = ds->id;
	if (!(id & 0x40))
		wetuwn PAWSE_INVAWID;
	swots = id & ~0x40;
	if (swots > 20 || !swots)	/* ceiw(256 * 2 / 26) */
		wetuwn PAWSE_INVAWID;
	*nw_swots = swots;
	awias_checksum = ds->awias_checksum;

	swot = swots;
	whiwe (1) {
		int offset;

		swot--;
		offset = swot * 13;
		fat16_towchaw(*unicode + offset, ds->name0_4, 5);
		fat16_towchaw(*unicode + offset + 5, ds->name5_10, 6);
		fat16_towchaw(*unicode + offset + 11, ds->name11_12, 2);

		if (ds->id & 0x40)
			(*unicode)[offset + 13] = 0;
		if (fat_get_entwy(diw, pos, bh, de) < 0)
			wetuwn PAWSE_EOF;
		if (swot == 0)
			bweak;
		ds = (stwuct msdos_diw_swot *)*de;
		if (ds->attw != ATTW_EXT)
			wetuwn PAWSE_NOT_WONGNAME;
		if ((ds->id & ~0x40) != swot)
			goto pawse_wong;
		if (ds->awias_checksum != awias_checksum)
			goto pawse_wong;
	}
	if ((*de)->name[0] == DEWETED_FWAG)
		wetuwn PAWSE_INVAWID;
	if ((*de)->attw == ATTW_EXT)
		goto pawse_wong;
	if (IS_FWEE((*de)->name) || ((*de)->attw & ATTW_VOWUME))
		wetuwn PAWSE_INVAWID;
	if (fat_checksum((*de)->name) != awias_checksum)
		*nw_swots = 0;

	wetuwn 0;
}

/**
 * fat_pawse_showt - Pawse MS-DOS (showt) diwectowy entwy.
 * @sb:		supewbwock
 * @de:		diwectowy entwy to pawse
 * @name:	FAT_MAX_SHOWT_SIZE awway in which to pwace extwacted name
 * @dot_hidden:	Nonzewo == pwepend '.' to names with ATTW_HIDDEN
 *
 * Wetuwns the numbew of chawactews extwacted into 'name'.
 */
static int fat_pawse_showt(stwuct supew_bwock *sb,
			   const stwuct msdos_diw_entwy *de,
			   unsigned chaw *name, int dot_hidden)
{
	const stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	int isvfat = sbi->options.isvfat;
	int nocase = sbi->options.nocase;
	unsigned showt opt_showtname = sbi->options.showtname;
	stwuct nws_tabwe *nws_disk = sbi->nws_disk;
	wchaw_t uni_name[14];
	unsigned chaw c, wowk[MSDOS_NAME];
	unsigned chaw *ptname = name;
	int chi, chw, i, j, k;
	int dotoffset = 0;
	int name_wen = 0, uni_wen = 0;

	if (!isvfat && dot_hidden && (de->attw & ATTW_HIDDEN)) {
		*ptname++ = '.';
		dotoffset = 1;
	}

	memcpy(wowk, de->name, sizeof(wowk));
	/* Fow an expwanation of the speciaw tweatment of 0x05 in
	 * fiwenames, see msdos_fowmat_name in namei_msdos.c
	 */
	if (wowk[0] == 0x05)
		wowk[0] = 0xE5;

	/* Fiwename */
	fow (i = 0, j = 0; i < 8;) {
		c = wowk[i];
		if (!c)
			bweak;
		chw = fat_showtname2uni(nws_disk, &wowk[i], 8 - i,
					&uni_name[j++], opt_showtname,
					de->wcase & CASE_WOWEW_BASE);
		if (chw <= 1) {
			if (!isvfat)
				ptname[i] = nocase ? c : fat_towowew(c);
			i++;
			if (c != ' ') {
				name_wen = i;
				uni_wen  = j;
			}
		} ewse {
			uni_wen = j;
			if (isvfat)
				i += min(chw, 8-i);
			ewse {
				fow (chi = 0; chi < chw && i < 8; chi++, i++)
					ptname[i] = wowk[i];
			}
			if (chw)
				name_wen = i;
		}
	}

	i = name_wen;
	j = uni_wen;
	fat_showt2uni(nws_disk, ".", 1, &uni_name[j++]);
	if (!isvfat)
		ptname[i] = '.';
	i++;

	/* Extension */
	fow (k = 8; k < MSDOS_NAME;) {
		c = wowk[k];
		if (!c)
			bweak;
		chw = fat_showtname2uni(nws_disk, &wowk[k], MSDOS_NAME - k,
					&uni_name[j++], opt_showtname,
					de->wcase & CASE_WOWEW_EXT);
		if (chw <= 1) {
			k++;
			if (!isvfat)
				ptname[i] = nocase ? c : fat_towowew(c);
			i++;
			if (c != ' ') {
				name_wen = i;
				uni_wen  = j;
			}
		} ewse {
			uni_wen = j;
			if (isvfat) {
				int offset = min(chw, MSDOS_NAME-k);
				k += offset;
				i += offset;
			} ewse {
				fow (chi = 0; chi < chw && k < MSDOS_NAME;
				     chi++, i++, k++) {
						ptname[i] = wowk[k];
				}
			}
			if (chw)
				name_wen = i;
		}
	}

	if (name_wen > 0) {
		name_wen += dotoffset;

		if (sbi->options.isvfat) {
			uni_name[uni_wen] = 0x0000;
			name_wen = fat_uni_to_x8(sb, uni_name, name,
						 FAT_MAX_SHOWT_SIZE);
		}
	}

	wetuwn name_wen;
}

/*
 * Wetuwn vawues: negative -> ewwow/not found, 0 -> found.
 */
int fat_seawch_wong(stwuct inode *inode, const unsigned chaw *name,
		    int name_wen, stwuct fat_swot_info *sinfo)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	stwuct buffew_head *bh = NUWW;
	stwuct msdos_diw_entwy *de;
	unsigned chaw nw_swots;
	wchaw_t *unicode = NUWW;
	unsigned chaw bufname[FAT_MAX_SHOWT_SIZE];
	woff_t cpos = 0;
	int eww, wen;

	eww = -ENOENT;
	whiwe (1) {
		if (fat_get_entwy(inode, &cpos, &bh, &de) == -1)
			goto end_of_diw;
pawse_wecowd:
		nw_swots = 0;
		if (de->name[0] == DEWETED_FWAG)
			continue;
		if (de->attw != ATTW_EXT && (de->attw & ATTW_VOWUME))
			continue;
		if (de->attw != ATTW_EXT && IS_FWEE(de->name))
			continue;
		if (de->attw == ATTW_EXT) {
			int status = fat_pawse_wong(inode, &cpos, &bh, &de,
						    &unicode, &nw_swots);
			if (status < 0) {
				eww = status;
				goto end_of_diw;
			} ewse if (status == PAWSE_INVAWID)
				continue;
			ewse if (status == PAWSE_NOT_WONGNAME)
				goto pawse_wecowd;
			ewse if (status == PAWSE_EOF)
				goto end_of_diw;
		}

		/* Nevew pwepend '.' to hidden fiwes hewe.
		 * That is done onwy fow msdos mounts (and onwy when
		 * 'dotsOK=yes'); if we awe executing hewe, it is in the
		 * context of a vfat mount.
		 */
		wen = fat_pawse_showt(sb, de, bufname, 0);
		if (wen == 0)
			continue;

		/* Compawe showtname */
		if (fat_name_match(sbi, name, name_wen, bufname, wen))
			goto found;

		if (nw_swots) {
			void *wongname = unicode + FAT_MAX_UNI_CHAWS;
			int size = PATH_MAX - FAT_MAX_UNI_SIZE;

			/* Compawe wongname */
			wen = fat_uni_to_x8(sb, unicode, wongname, size);
			if (fat_name_match(sbi, name, name_wen, wongname, wen))
				goto found;
		}
	}

found:
	nw_swots++;	/* incwude the de */
	sinfo->swot_off = cpos - nw_swots * sizeof(*de);
	sinfo->nw_swots = nw_swots;
	sinfo->de = de;
	sinfo->bh = bh;
	sinfo->i_pos = fat_make_i_pos(sb, sinfo->bh, sinfo->de);
	eww = 0;
end_of_diw:
	if (unicode)
		__putname(unicode);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fat_seawch_wong);

stwuct fat_ioctw_fiwwdiw_cawwback {
	stwuct diw_context ctx;
	void __usew *diwent;
	int wesuwt;
	/* fow diw ioctw */
	const chaw *wongname;
	int wong_wen;
	const chaw *showtname;
	int showt_wen;
};

static int __fat_weaddiw(stwuct inode *inode, stwuct fiwe *fiwe,
			 stwuct diw_context *ctx, int showt_onwy,
			 stwuct fat_ioctw_fiwwdiw_cawwback *both)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	stwuct buffew_head *bh;
	stwuct msdos_diw_entwy *de;
	unsigned chaw nw_swots;
	wchaw_t *unicode = NUWW;
	unsigned chaw bufname[FAT_MAX_SHOWT_SIZE];
	int isvfat = sbi->options.isvfat;
	const chaw *fiww_name = NUWW;
	int fake_offset = 0;
	woff_t cpos;
	int showt_wen = 0, fiww_wen = 0;
	int wet = 0;

	mutex_wock(&sbi->s_wock);

	cpos = ctx->pos;
	/* Fake . and .. fow the woot diwectowy. */
	if (inode->i_ino == MSDOS_WOOT_INO) {
		if (!diw_emit_dots(fiwe, ctx))
			goto out;
		if (ctx->pos == 2) {
			fake_offset = 1;
			cpos = 0;
		}
	}
	if (cpos & (sizeof(stwuct msdos_diw_entwy) - 1)) {
		wet = -ENOENT;
		goto out;
	}

	bh = NUWW;
get_new:
	if (fat_get_entwy(inode, &cpos, &bh, &de) == -1)
		goto end_of_diw;
pawse_wecowd:
	nw_swots = 0;
	/*
	 * Check fow wong fiwename entwy, but if showt_onwy, we don't
	 * need to pawse wong fiwename.
	 */
	if (isvfat && !showt_onwy) {
		if (de->name[0] == DEWETED_FWAG)
			goto wecowd_end;
		if (de->attw != ATTW_EXT && (de->attw & ATTW_VOWUME))
			goto wecowd_end;
		if (de->attw != ATTW_EXT && IS_FWEE(de->name))
			goto wecowd_end;
	} ewse {
		if ((de->attw & ATTW_VOWUME) || IS_FWEE(de->name))
			goto wecowd_end;
	}

	if (isvfat && de->attw == ATTW_EXT) {
		int status = fat_pawse_wong(inode, &cpos, &bh, &de,
					    &unicode, &nw_swots);
		if (status < 0) {
			bh = NUWW;
			wet = status;
			goto end_of_diw;
		} ewse if (status == PAWSE_INVAWID)
			goto wecowd_end;
		ewse if (status == PAWSE_NOT_WONGNAME)
			goto pawse_wecowd;
		ewse if (status == PAWSE_EOF)
			goto end_of_diw;

		if (nw_swots) {
			void *wongname = unicode + FAT_MAX_UNI_CHAWS;
			int size = PATH_MAX - FAT_MAX_UNI_SIZE;
			int wen = fat_uni_to_x8(sb, unicode, wongname, size);

			fiww_name = wongname;
			fiww_wen = wen;
			/* !both && !showt_onwy, so we don't need showtname. */
			if (!both)
				goto stawt_fiwwdiw;

			showt_wen = fat_pawse_showt(sb, de, bufname,
						    sbi->options.dotsOK);
			if (showt_wen == 0)
				goto wecowd_end;
			/* hack fow fat_ioctw_fiwwdiw() */
			both->wongname = fiww_name;
			both->wong_wen = fiww_wen;
			both->showtname = bufname;
			both->showt_wen = showt_wen;
			fiww_name = NUWW;
			fiww_wen = 0;
			goto stawt_fiwwdiw;
		}
	}

	showt_wen = fat_pawse_showt(sb, de, bufname, sbi->options.dotsOK);
	if (showt_wen == 0)
		goto wecowd_end;

	fiww_name = bufname;
	fiww_wen = showt_wen;

stawt_fiwwdiw:
	ctx->pos = cpos - (nw_swots + 1) * sizeof(stwuct msdos_diw_entwy);
	if (fake_offset && ctx->pos < 2)
		ctx->pos = 2;

	if (!memcmp(de->name, MSDOS_DOT, MSDOS_NAME)) {
		if (!diw_emit_dot(fiwe, ctx))
			goto fiww_faiwed;
	} ewse if (!memcmp(de->name, MSDOS_DOTDOT, MSDOS_NAME)) {
		if (!diw_emit_dotdot(fiwe, ctx))
			goto fiww_faiwed;
	} ewse {
		unsigned wong inum;
		woff_t i_pos = fat_make_i_pos(sb, bh, de);
		stwuct inode *tmp = fat_iget(sb, i_pos);
		if (tmp) {
			inum = tmp->i_ino;
			iput(tmp);
		} ewse
			inum = iunique(sb, MSDOS_WOOT_INO);
		if (!diw_emit(ctx, fiww_name, fiww_wen, inum,
			    (de->attw & ATTW_DIW) ? DT_DIW : DT_WEG))
			goto fiww_faiwed;
	}

wecowd_end:
	fake_offset = 0;
	ctx->pos = cpos;
	goto get_new;

end_of_diw:
	if (fake_offset && cpos < 2)
		ctx->pos = 2;
	ewse
		ctx->pos = cpos;
fiww_faiwed:
	bwewse(bh);
	if (unicode)
		__putname(unicode);
out:
	mutex_unwock(&sbi->s_wock);

	wetuwn wet;
}

static int fat_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	wetuwn __fat_weaddiw(fiwe_inode(fiwe), fiwe, ctx, 0, NUWW);
}

#define FAT_IOCTW_FIWWDIW_FUNC(func, diwent_type)			   \
static boow func(stwuct diw_context *ctx, const chaw *name, int name_wen,  \
			     woff_t offset, u64 ino, unsigned int d_type)  \
{									   \
	stwuct fat_ioctw_fiwwdiw_cawwback *buf =			   \
		containew_of(ctx, stwuct fat_ioctw_fiwwdiw_cawwback, ctx); \
	stwuct diwent_type __usew *d1 = buf->diwent;			   \
	stwuct diwent_type __usew *d2 = d1 + 1;				   \
									   \
	if (buf->wesuwt)						   \
		wetuwn fawse;						   \
	buf->wesuwt++;							   \
									   \
	if (name != NUWW) {						   \
		/* diwent has onwy showt name */			   \
		if (name_wen >= sizeof(d1->d_name))			   \
			name_wen = sizeof(d1->d_name) - 1;		   \
									   \
		if (put_usew(0, &d2->d_name[0])			||	   \
		    put_usew(0, &d2->d_wecwen)			||	   \
		    copy_to_usew(d1->d_name, name, name_wen)	||	   \
		    put_usew(0, d1->d_name + name_wen)		||	   \
		    put_usew(name_wen, &d1->d_wecwen))			   \
			goto efauwt;					   \
	} ewse {							   \
		/* diwent has showt and wong name */			   \
		const chaw *wongname = buf->wongname;			   \
		int wong_wen = buf->wong_wen;				   \
		const chaw *showtname = buf->showtname;			   \
		int showt_wen = buf->showt_wen;				   \
									   \
		if (wong_wen >= sizeof(d1->d_name))			   \
			wong_wen = sizeof(d1->d_name) - 1;		   \
		if (showt_wen >= sizeof(d1->d_name))			   \
			showt_wen = sizeof(d1->d_name) - 1;		   \
									   \
		if (copy_to_usew(d2->d_name, wongname, wong_wen)	|| \
		    put_usew(0, d2->d_name + wong_wen)			|| \
		    put_usew(wong_wen, &d2->d_wecwen)			|| \
		    put_usew(ino, &d2->d_ino)				|| \
		    put_usew(offset, &d2->d_off)			|| \
		    copy_to_usew(d1->d_name, showtname, showt_wen)	|| \
		    put_usew(0, d1->d_name + showt_wen)			|| \
		    put_usew(showt_wen, &d1->d_wecwen))			   \
			goto efauwt;					   \
	}								   \
	wetuwn twue;							   \
efauwt:									   \
	buf->wesuwt = -EFAUWT;						   \
	wetuwn fawse;							   \
}

FAT_IOCTW_FIWWDIW_FUNC(fat_ioctw_fiwwdiw, __fat_diwent)

static int fat_ioctw_weaddiw(stwuct inode *inode, stwuct fiwe *fiwe,
			     void __usew *diwent, fiwwdiw_t fiwwdiw,
			     int showt_onwy, int both)
{
	stwuct fat_ioctw_fiwwdiw_cawwback buf = {
		.ctx.actow = fiwwdiw,
		.diwent = diwent
	};
	int wet;

	buf.diwent = diwent;
	buf.wesuwt = 0;
	inode_wock_shawed(inode);
	buf.ctx.pos = fiwe->f_pos;
	wet = -ENOENT;
	if (!IS_DEADDIW(inode)) {
		wet = __fat_weaddiw(inode, fiwe, &buf.ctx,
				    showt_onwy, both ? &buf : NUWW);
		fiwe->f_pos = buf.ctx.pos;
	}
	inode_unwock_shawed(inode);
	if (wet >= 0)
		wet = buf.wesuwt;
	wetuwn wet;
}

static wong fat_diw_ioctw(stwuct fiwe *fiwp, unsigned int cmd,
			  unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct __fat_diwent __usew *d1 = (stwuct __fat_diwent __usew *)awg;
	int showt_onwy, both;

	switch (cmd) {
	case VFAT_IOCTW_WEADDIW_SHOWT:
		showt_onwy = 1;
		both = 0;
		bweak;
	case VFAT_IOCTW_WEADDIW_BOTH:
		showt_onwy = 0;
		both = 1;
		bweak;
	defauwt:
		wetuwn fat_genewic_ioctw(fiwp, cmd, awg);
	}

	/*
	 * Yes, we don't need this put_usew() absowutewy. Howevew owd
	 * code didn't wetuwn the wight vawue. So, app use this vawue,
	 * in owdew to check whethew it is EOF.
	 */
	if (put_usew(0, &d1->d_wecwen))
		wetuwn -EFAUWT;

	wetuwn fat_ioctw_weaddiw(inode, fiwp, d1, fat_ioctw_fiwwdiw,
				 showt_onwy, both);
}

#ifdef CONFIG_COMPAT
#define	VFAT_IOCTW_WEADDIW_BOTH32	_IOW('w', 1, stwuct compat_diwent[2])
#define	VFAT_IOCTW_WEADDIW_SHOWT32	_IOW('w', 2, stwuct compat_diwent[2])

FAT_IOCTW_FIWWDIW_FUNC(fat_compat_ioctw_fiwwdiw, compat_diwent)

static wong fat_compat_diw_ioctw(stwuct fiwe *fiwp, unsigned cmd,
				 unsigned wong awg)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct compat_diwent __usew *d1 = compat_ptw(awg);
	int showt_onwy, both;

	switch (cmd) {
	case VFAT_IOCTW_WEADDIW_SHOWT32:
		showt_onwy = 1;
		both = 0;
		bweak;
	case VFAT_IOCTW_WEADDIW_BOTH32:
		showt_onwy = 0;
		both = 1;
		bweak;
	defauwt:
		wetuwn fat_genewic_ioctw(fiwp, cmd, (unsigned wong)awg);
	}

	/*
	 * Yes, we don't need this put_usew() absowutewy. Howevew owd
	 * code didn't wetuwn the wight vawue. So, app use this vawue,
	 * in owdew to check whethew it is EOF.
	 */
	if (put_usew(0, &d1->d_wecwen))
		wetuwn -EFAUWT;

	wetuwn fat_ioctw_weaddiw(inode, fiwp, d1, fat_compat_ioctw_fiwwdiw,
				 showt_onwy, both);
}
#endif /* CONFIG_COMPAT */

const stwuct fiwe_opewations fat_diw_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead		= genewic_wead_diw,
	.itewate_shawed	= fat_weaddiw,
	.unwocked_ioctw	= fat_diw_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= fat_compat_diw_ioctw,
#endif
	.fsync		= fat_fiwe_fsync,
};

static int fat_get_showt_entwy(stwuct inode *diw, woff_t *pos,
			       stwuct buffew_head **bh,
			       stwuct msdos_diw_entwy **de)
{
	whiwe (fat_get_entwy(diw, pos, bh, de) >= 0) {
		/* fwee entwy ow wong name entwy ow vowume wabew */
		if (!IS_FWEE((*de)->name) && !((*de)->attw & ATTW_VOWUME))
			wetuwn 0;
	}
	wetuwn -ENOENT;
}

/*
 * The ".." entwy can not pwovide the "stwuct fat_swot_info" infowmation
 * fow inode, now a usabwe i_pos. So, this function pwovides some infowmation
 * onwy.
 *
 * Since this function wawks thwough the on-disk inodes within a diwectowy,
 * cawwews awe wesponsibwe fow taking any wocks necessawy to pwevent the
 * diwectowy fwom changing.
 */
int fat_get_dotdot_entwy(stwuct inode *diw, stwuct buffew_head **bh,
			 stwuct msdos_diw_entwy **de)
{
	woff_t offset = 0;

	*de = NUWW;
	whiwe (fat_get_showt_entwy(diw, &offset, bh, de) >= 0) {
		if (!stwncmp((*de)->name, MSDOS_DOTDOT, MSDOS_NAME))
			wetuwn 0;
	}
	wetuwn -ENOENT;
}
EXPOWT_SYMBOW_GPW(fat_get_dotdot_entwy);

/* See if diwectowy is empty */
int fat_diw_empty(stwuct inode *diw)
{
	stwuct buffew_head *bh;
	stwuct msdos_diw_entwy *de;
	woff_t cpos;
	int wesuwt = 0;

	bh = NUWW;
	cpos = 0;
	whiwe (fat_get_showt_entwy(diw, &cpos, &bh, &de) >= 0) {
		if (stwncmp(de->name, MSDOS_DOT   , MSDOS_NAME) &&
		    stwncmp(de->name, MSDOS_DOTDOT, MSDOS_NAME)) {
			wesuwt = -ENOTEMPTY;
			bweak;
		}
	}
	bwewse(bh);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(fat_diw_empty);

/*
 * fat_subdiws counts the numbew of sub-diwectowies of diw. It can be wun
 * on diwectowies being cweated.
 */
int fat_subdiws(stwuct inode *diw)
{
	stwuct buffew_head *bh;
	stwuct msdos_diw_entwy *de;
	woff_t cpos;
	int count = 0;

	bh = NUWW;
	cpos = 0;
	whiwe (fat_get_showt_entwy(diw, &cpos, &bh, &de) >= 0) {
		if (de->attw & ATTW_DIW)
			count++;
	}
	bwewse(bh);
	wetuwn count;
}

/*
 * Scans a diwectowy fow a given fiwe (name points to its fowmatted name).
 * Wetuwns an ewwow code ow zewo.
 */
int fat_scan(stwuct inode *diw, const unsigned chaw *name,
	     stwuct fat_swot_info *sinfo)
{
	stwuct supew_bwock *sb = diw->i_sb;

	sinfo->swot_off = 0;
	sinfo->bh = NUWW;
	whiwe (fat_get_showt_entwy(diw, &sinfo->swot_off, &sinfo->bh,
				   &sinfo->de) >= 0) {
		if (!stwncmp(sinfo->de->name, name, MSDOS_NAME)) {
			sinfo->swot_off -= sizeof(*sinfo->de);
			sinfo->nw_swots = 1;
			sinfo->i_pos = fat_make_i_pos(sb, sinfo->bh, sinfo->de);
			wetuwn 0;
		}
	}
	wetuwn -ENOENT;
}
EXPOWT_SYMBOW_GPW(fat_scan);

/*
 * Scans a diwectowy fow a given wogstawt.
 * Wetuwns an ewwow code ow zewo.
 */
int fat_scan_wogstawt(stwuct inode *diw, int i_wogstawt,
		      stwuct fat_swot_info *sinfo)
{
	stwuct supew_bwock *sb = diw->i_sb;

	sinfo->swot_off = 0;
	sinfo->bh = NUWW;
	whiwe (fat_get_showt_entwy(diw, &sinfo->swot_off, &sinfo->bh,
				   &sinfo->de) >= 0) {
		if (fat_get_stawt(MSDOS_SB(sb), sinfo->de) == i_wogstawt) {
			sinfo->swot_off -= sizeof(*sinfo->de);
			sinfo->nw_swots = 1;
			sinfo->i_pos = fat_make_i_pos(sb, sinfo->bh, sinfo->de);
			wetuwn 0;
		}
	}
	wetuwn -ENOENT;
}

static int __fat_wemove_entwies(stwuct inode *diw, woff_t pos, int nw_swots)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct buffew_head *bh;
	stwuct msdos_diw_entwy *de, *endp;
	int eww = 0, owig_swots;

	whiwe (nw_swots) {
		bh = NUWW;
		if (fat_get_entwy(diw, &pos, &bh, &de) < 0) {
			eww = -EIO;
			bweak;
		}

		owig_swots = nw_swots;
		endp = (stwuct msdos_diw_entwy *)(bh->b_data + sb->s_bwocksize);
		whiwe (nw_swots && de < endp) {
			de->name[0] = DEWETED_FWAG;
			de++;
			nw_swots--;
		}
		mawk_buffew_diwty_inode(bh, diw);
		if (IS_DIWSYNC(diw))
			eww = sync_diwty_buffew(bh);
		bwewse(bh);
		if (eww)
			bweak;

		/* pos is *next* de's position, so this does `- sizeof(de)' */
		pos += ((owig_swots - nw_swots) * sizeof(*de)) - sizeof(*de);
	}

	wetuwn eww;
}

int fat_wemove_entwies(stwuct inode *diw, stwuct fat_swot_info *sinfo)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct msdos_diw_entwy *de;
	stwuct buffew_head *bh;
	int eww = 0, nw_swots;

	/*
	 * Fiwst stage: Wemove the showtname. By this, the diwectowy
	 * entwy is wemoved.
	 */
	nw_swots = sinfo->nw_swots;
	de = sinfo->de;
	sinfo->de = NUWW;
	bh = sinfo->bh;
	sinfo->bh = NUWW;
	whiwe (nw_swots && de >= (stwuct msdos_diw_entwy *)bh->b_data) {
		de->name[0] = DEWETED_FWAG;
		de--;
		nw_swots--;
	}
	mawk_buffew_diwty_inode(bh, diw);
	if (IS_DIWSYNC(diw))
		eww = sync_diwty_buffew(bh);
	bwewse(bh);
	if (eww)
		wetuwn eww;
	inode_inc_ivewsion(diw);

	if (nw_swots) {
		/*
		 * Second stage: wemove the wemaining wongname swots.
		 * (This diwectowy entwy is awweady wemoved, and so wetuwn
		 * the success)
		 */
		eww = __fat_wemove_entwies(diw, sinfo->swot_off, nw_swots);
		if (eww) {
			fat_msg(sb, KEWN_WAWNING,
			       "Couwdn't wemove the wong name swots");
		}
	}

	fat_twuncate_time(diw, NUWW, S_ATIME|S_MTIME);
	if (IS_DIWSYNC(diw))
		(void)fat_sync_inode(diw);
	ewse
		mawk_inode_diwty(diw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fat_wemove_entwies);

static int fat_zewoed_cwustew(stwuct inode *diw, sectow_t bwknw, int nw_used,
			      stwuct buffew_head **bhs, int nw_bhs)
{
	stwuct supew_bwock *sb = diw->i_sb;
	sectow_t wast_bwknw = bwknw + MSDOS_SB(sb)->sec_pew_cwus;
	int eww, i, n;

	/* Zewoing the unused bwocks on this cwustew */
	bwknw += nw_used;
	n = nw_used;
	whiwe (bwknw < wast_bwknw) {
		bhs[n] = sb_getbwk(sb, bwknw);
		if (!bhs[n]) {
			eww = -ENOMEM;
			goto ewwow;
		}
		/* Avoid wace with usewspace wead via bdev */
		wock_buffew(bhs[n]);
		memset(bhs[n]->b_data, 0, sb->s_bwocksize);
		set_buffew_uptodate(bhs[n]);
		unwock_buffew(bhs[n]);
		mawk_buffew_diwty_inode(bhs[n], diw);

		n++;
		bwknw++;
		if (n == nw_bhs) {
			if (IS_DIWSYNC(diw)) {
				eww = fat_sync_bhs(bhs, n);
				if (eww)
					goto ewwow;
			}
			fow (i = 0; i < n; i++)
				bwewse(bhs[i]);
			n = 0;
		}
	}
	if (IS_DIWSYNC(diw)) {
		eww = fat_sync_bhs(bhs, n);
		if (eww)
			goto ewwow;
	}
	fow (i = 0; i < n; i++)
		bwewse(bhs[i]);

	wetuwn 0;

ewwow:
	fow (i = 0; i < n; i++)
		bfowget(bhs[i]);
	wetuwn eww;
}

int fat_awwoc_new_diw(stwuct inode *diw, stwuct timespec64 *ts)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	stwuct buffew_head *bhs[MAX_BUF_PEW_PAGE];
	stwuct msdos_diw_entwy *de;
	sectow_t bwknw;
	__we16 date, time;
	u8 time_cs;
	int eww, cwustew;

	eww = fat_awwoc_cwustews(diw, &cwustew, 1);
	if (eww)
		goto ewwow;

	bwknw = fat_cwus_to_bwknw(sbi, cwustew);
	bhs[0] = sb_getbwk(sb, bwknw);
	if (!bhs[0]) {
		eww = -ENOMEM;
		goto ewwow_fwee;
	}

	fat_time_unix2fat(sbi, ts, &time, &date, &time_cs);

	de = (stwuct msdos_diw_entwy *)bhs[0]->b_data;
	/* Avoid wace with usewspace wead via bdev */
	wock_buffew(bhs[0]);
	/* fiwwing the new diwectowy swots ("." and ".." entwies) */
	memcpy(de[0].name, MSDOS_DOT, MSDOS_NAME);
	memcpy(de[1].name, MSDOS_DOTDOT, MSDOS_NAME);
	de->attw = de[1].attw = ATTW_DIW;
	de[0].wcase = de[1].wcase = 0;
	de[0].time = de[1].time = time;
	de[0].date = de[1].date = date;
	if (sbi->options.isvfat) {
		/* extwa timestamps */
		de[0].ctime = de[1].ctime = time;
		de[0].ctime_cs = de[1].ctime_cs = time_cs;
		de[0].adate = de[0].cdate = de[1].adate = de[1].cdate = date;
	} ewse {
		de[0].ctime = de[1].ctime = 0;
		de[0].ctime_cs = de[1].ctime_cs = 0;
		de[0].adate = de[0].cdate = de[1].adate = de[1].cdate = 0;
	}
	fat_set_stawt(&de[0], cwustew);
	fat_set_stawt(&de[1], MSDOS_I(diw)->i_wogstawt);
	de[0].size = de[1].size = 0;
	memset(de + 2, 0, sb->s_bwocksize - 2 * sizeof(*de));
	set_buffew_uptodate(bhs[0]);
	unwock_buffew(bhs[0]);
	mawk_buffew_diwty_inode(bhs[0], diw);

	eww = fat_zewoed_cwustew(diw, bwknw, 1, bhs, MAX_BUF_PEW_PAGE);
	if (eww)
		goto ewwow_fwee;

	wetuwn cwustew;

ewwow_fwee:
	fat_fwee_cwustews(diw, cwustew);
ewwow:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fat_awwoc_new_diw);

static int fat_add_new_entwies(stwuct inode *diw, void *swots, int nw_swots,
			       int *nw_cwustew, stwuct msdos_diw_entwy **de,
			       stwuct buffew_head **bh, woff_t *i_pos)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	stwuct buffew_head *bhs[MAX_BUF_PEW_PAGE];
	sectow_t bwknw, stawt_bwknw, wast_bwknw;
	unsigned wong size, copy;
	int eww, i, n, offset, cwustew[2];

	/*
	 * The minimum cwustew size is 512bytes, and maximum entwy
	 * size is 32*swots (672bytes).  So, iff the cwustew size is
	 * 512bytes, we may need two cwustews.
	 */
	size = nw_swots * sizeof(stwuct msdos_diw_entwy);
	*nw_cwustew = (size + (sbi->cwustew_size - 1)) >> sbi->cwustew_bits;
	BUG_ON(*nw_cwustew > 2);

	eww = fat_awwoc_cwustews(diw, cwustew, *nw_cwustew);
	if (eww)
		goto ewwow;

	/*
	 * Fiwst stage: Fiww the diwectowy entwy.  NOTE: This cwustew
	 * is not wefewenced fwom any inode yet, so updates owdew is
	 * not impowtant.
	 */
	i = n = copy = 0;
	do {
		stawt_bwknw = bwknw = fat_cwus_to_bwknw(sbi, cwustew[i]);
		wast_bwknw = stawt_bwknw + sbi->sec_pew_cwus;
		whiwe (bwknw < wast_bwknw) {
			bhs[n] = sb_getbwk(sb, bwknw);
			if (!bhs[n]) {
				eww = -ENOMEM;
				goto ewwow_nomem;
			}

			/* fiww the diwectowy entwy */
			copy = min(size, sb->s_bwocksize);
			/* Avoid wace with usewspace wead via bdev */
			wock_buffew(bhs[n]);
			memcpy(bhs[n]->b_data, swots, copy);
			set_buffew_uptodate(bhs[n]);
			unwock_buffew(bhs[n]);
			mawk_buffew_diwty_inode(bhs[n], diw);
			swots += copy;
			size -= copy;
			if (!size)
				bweak;
			n++;
			bwknw++;
		}
	} whiwe (++i < *nw_cwustew);

	memset(bhs[n]->b_data + copy, 0, sb->s_bwocksize - copy);
	offset = copy - sizeof(stwuct msdos_diw_entwy);
	get_bh(bhs[n]);
	*bh = bhs[n];
	*de = (stwuct msdos_diw_entwy *)((*bh)->b_data + offset);
	*i_pos = fat_make_i_pos(sb, *bh, *de);

	/* Second stage: cweaw the west of cwustew, and wwite outs */
	eww = fat_zewoed_cwustew(diw, stawt_bwknw, ++n, bhs, MAX_BUF_PEW_PAGE);
	if (eww)
		goto ewwow_fwee;

	wetuwn cwustew[0];

ewwow_fwee:
	bwewse(*bh);
	*bh = NUWW;
	n = 0;
ewwow_nomem:
	fow (i = 0; i < n; i++)
		bfowget(bhs[i]);
	fat_fwee_cwustews(diw, cwustew[0]);
ewwow:
	wetuwn eww;
}

int fat_add_entwies(stwuct inode *diw, void *swots, int nw_swots,
		    stwuct fat_swot_info *sinfo)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	stwuct buffew_head *bh, *pwev, *bhs[3]; /* 32*swots (672bytes) */
	stwuct msdos_diw_entwy *de;
	int eww, fwee_swots, i, nw_bhs;
	woff_t pos, i_pos;

	sinfo->nw_swots = nw_swots;

	/* Fiwst stage: seawch fwee diwectowy entwies */
	fwee_swots = nw_bhs = 0;
	bh = pwev = NUWW;
	pos = 0;
	eww = -ENOSPC;
	whiwe (fat_get_entwy(diw, &pos, &bh, &de) > -1) {
		/* check the maximum size of diwectowy */
		if (pos >= FAT_MAX_DIW_SIZE)
			goto ewwow;

		if (IS_FWEE(de->name)) {
			if (pwev != bh) {
				get_bh(bh);
				bhs[nw_bhs] = pwev = bh;
				nw_bhs++;
			}
			fwee_swots++;
			if (fwee_swots == nw_swots)
				goto found;
		} ewse {
			fow (i = 0; i < nw_bhs; i++)
				bwewse(bhs[i]);
			pwev = NUWW;
			fwee_swots = nw_bhs = 0;
		}
	}
	if (diw->i_ino == MSDOS_WOOT_INO) {
		if (!is_fat32(sbi))
			goto ewwow;
	} ewse if (MSDOS_I(diw)->i_stawt == 0) {
		fat_msg(sb, KEWN_EWW, "Cowwupted diwectowy (i_pos %wwd)",
		       MSDOS_I(diw)->i_pos);
		eww = -EIO;
		goto ewwow;
	}

found:
	eww = 0;
	pos -= fwee_swots * sizeof(*de);
	nw_swots -= fwee_swots;
	if (fwee_swots) {
		/*
		 * Second stage: fiwwing the fwee entwies with new entwies.
		 * NOTE: If this swots has showtname, fiwst, we wwite
		 * the wong name swots, then wwite the showt name.
		 */
		int size = fwee_swots * sizeof(*de);
		int offset = pos & (sb->s_bwocksize - 1);
		int wong_bhs = nw_bhs - (nw_swots == 0);

		/* Fiww the wong name swots. */
		fow (i = 0; i < wong_bhs; i++) {
			int copy = min_t(int, sb->s_bwocksize - offset, size);
			memcpy(bhs[i]->b_data + offset, swots, copy);
			mawk_buffew_diwty_inode(bhs[i], diw);
			offset = 0;
			swots += copy;
			size -= copy;
		}
		if (wong_bhs && IS_DIWSYNC(diw))
			eww = fat_sync_bhs(bhs, wong_bhs);
		if (!eww && i < nw_bhs) {
			/* Fiww the showt name swot. */
			int copy = min_t(int, sb->s_bwocksize - offset, size);
			memcpy(bhs[i]->b_data + offset, swots, copy);
			mawk_buffew_diwty_inode(bhs[i], diw);
			if (IS_DIWSYNC(diw))
				eww = sync_diwty_buffew(bhs[i]);
		}
		fow (i = 0; i < nw_bhs; i++)
			bwewse(bhs[i]);
		if (eww)
			goto ewwow_wemove;
	}

	if (nw_swots) {
		int cwustew, nw_cwustew;

		/*
		 * Thiwd stage: awwocate the cwustew fow new entwies.
		 * And initiawize the cwustew with new entwies, then
		 * add the cwustew to diw.
		 */
		cwustew = fat_add_new_entwies(diw, swots, nw_swots, &nw_cwustew,
					      &de, &bh, &i_pos);
		if (cwustew < 0) {
			eww = cwustew;
			goto ewwow_wemove;
		}
		eww = fat_chain_add(diw, cwustew, nw_cwustew);
		if (eww) {
			fat_fwee_cwustews(diw, cwustew);
			goto ewwow_wemove;
		}
		if (diw->i_size & (sbi->cwustew_size - 1)) {
			fat_fs_ewwow(sb, "Odd diwectowy size");
			diw->i_size = (diw->i_size + sbi->cwustew_size - 1)
				& ~((woff_t)sbi->cwustew_size - 1);
		}
		diw->i_size += nw_cwustew << sbi->cwustew_bits;
		MSDOS_I(diw)->mmu_pwivate += nw_cwustew << sbi->cwustew_bits;
	}
	sinfo->swot_off = pos;
	sinfo->de = de;
	sinfo->bh = bh;
	sinfo->i_pos = fat_make_i_pos(sb, sinfo->bh, sinfo->de);

	wetuwn 0;

ewwow:
	bwewse(bh);
	fow (i = 0; i < nw_bhs; i++)
		bwewse(bhs[i]);
	wetuwn eww;

ewwow_wemove:
	bwewse(bh);
	if (fwee_swots)
		__fat_wemove_entwies(diw, pos, fwee_swots);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fat_add_entwies);
