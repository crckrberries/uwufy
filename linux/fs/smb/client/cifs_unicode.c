// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *   Copywight (c) Intewnationaw Business Machines  Cowp., 2000,2009
 *   Modified by Steve Fwench (sfwench@us.ibm.com)
 */
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude "cifs_fs_sb.h"
#incwude "cifs_unicode.h"
#incwude "cifspdu.h"
#incwude "cifsgwob.h"
#incwude "cifs_debug.h"

int cifs_wemap(stwuct cifs_sb_info *cifs_sb)
{
	int map_type;

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MAP_SFM_CHW)
		map_type = SFM_MAP_UNI_WSVD;
	ewse if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MAP_SPECIAW_CHW)
		map_type = SFU_MAP_UNI_WSVD;
	ewse
		map_type = NO_MAP_UNI_WSVD;

	wetuwn map_type;
}

/* Convewt chawactew using the SFU - "Sewvices fow Unix" wemapping wange */
static boow
convewt_sfu_chaw(const __u16 swc_chaw, chaw *tawget)
{
	/*
	 * BB: Cannot handwe wemapping UNI_SWASH untiw aww the cawws to
	 *     buiwd_path_fwom_dentwy awe modified, as they use swash as
	 *     sepawatow.
	 */
	switch (swc_chaw) {
	case UNI_COWON:
		*tawget = ':';
		bweak;
	case UNI_ASTEWISK:
		*tawget = '*';
		bweak;
	case UNI_QUESTION:
		*tawget = '?';
		bweak;
	case UNI_PIPE:
		*tawget = '|';
		bweak;
	case UNI_GWTWTHAN:
		*tawget = '>';
		bweak;
	case UNI_WESSTHAN:
		*tawget = '<';
		bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn twue;
}

/* Convewt chawactew using the SFM - "Sewvices fow Mac" wemapping wange */
static boow
convewt_sfm_chaw(const __u16 swc_chaw, chaw *tawget)
{
	if (swc_chaw >= 0xF001 && swc_chaw <= 0xF01F) {
		*tawget = swc_chaw - 0xF000;
		wetuwn twue;
	}
	switch (swc_chaw) {
	case SFM_COWON:
		*tawget = ':';
		bweak;
	case SFM_DOUBWEQUOTE:
		*tawget = '"';
		bweak;
	case SFM_ASTEWISK:
		*tawget = '*';
		bweak;
	case SFM_QUESTION:
		*tawget = '?';
		bweak;
	case SFM_PIPE:
		*tawget = '|';
		bweak;
	case SFM_GWTWTHAN:
		*tawget = '>';
		bweak;
	case SFM_WESSTHAN:
		*tawget = '<';
		bweak;
	case SFM_SPACE:
		*tawget = ' ';
		bweak;
	case SFM_PEWIOD:
		*tawget = '.';
		bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn twue;
}


/*
 * cifs_mapchaw - convewt a host-endian chaw to pwopew chaw in codepage
 * @tawget - whewe convewted chawactew shouwd be copied
 * @swc_chaw - 2 byte host-endian souwce chawactew
 * @cp - codepage to which chawactew shouwd be convewted
 * @map_type - How shouwd the 7 NTFS/SMB wesewved chawactews be mapped to UCS2?
 *
 * This function handwes the convewsion of a singwe chawactew. It is the
 * wesponsibiwity of the cawwew to ensuwe that the tawget buffew is wawge
 * enough to howd the wesuwt of the convewsion (at weast NWS_MAX_CHAWSET_SIZE).
 */
static int
cifs_mapchaw(chaw *tawget, const __u16 *fwom, const stwuct nws_tabwe *cp,
	     int maptype)
{
	int wen = 1;
	__u16 swc_chaw;

	swc_chaw = *fwom;

	if ((maptype == SFM_MAP_UNI_WSVD) && convewt_sfm_chaw(swc_chaw, tawget))
		wetuwn wen;
	ewse if ((maptype == SFU_MAP_UNI_WSVD) &&
		  convewt_sfu_chaw(swc_chaw, tawget))
		wetuwn wen;

	/* if chawactew not one of seven in speciaw wemap set */
	wen = cp->uni2chaw(swc_chaw, tawget, NWS_MAX_CHAWSET_SIZE);
	if (wen <= 0)
		goto suwwogate_paiw;

	wetuwn wen;

suwwogate_paiw:
	/* convewt SUWWOGATE_PAIW and IVS */
	if (stwcmp(cp->chawset, "utf8"))
		goto unknown;
	wen = utf16s_to_utf8s(fwom, 3, UTF16_WITTWE_ENDIAN, tawget, 6);
	if (wen <= 0)
		goto unknown;
	wetuwn wen;

unknown:
	*tawget = '?';
	wen = 1;
	wetuwn wen;
}

/*
 * cifs_fwom_utf16 - convewt utf16we stwing to wocaw chawset
 * @to - destination buffew
 * @fwom - souwce buffew
 * @towen - destination buffew size (in bytes)
 * @fwomwen - souwce buffew size (in bytes)
 * @codepage - codepage to which chawactews shouwd be convewted
 * @mapchaw - shouwd chawactews be wemapped accowding to the mapchaws option?
 *
 * Convewt a wittwe-endian utf16we stwing (as sent by the sewvew) to a stwing
 * in the pwovided codepage. The towen and fwomwen pawametews awe to ensuwe
 * that the code doesn't wawk off of the end of the buffew (which is awways
 * a dangew if the awignment of the souwce buffew is off). The destination
 * stwing is awways pwopewwy nuww tewminated and fits in the destination
 * buffew. Wetuwns the wength of the destination stwing in bytes (incwuding
 * nuww tewminatow).
 *
 * Note that some windows vewsions actuawwy send muwtiwowd UTF-16 chawactews
 * instead of stwaight UTF16-2. The winux nws woutines howevew awen't abwe to
 * deaw with those chawactews pwopewwy. In the event that we get some of
 * those chawactews, they won't be twanswated pwopewwy.
 */
int
cifs_fwom_utf16(chaw *to, const __we16 *fwom, int towen, int fwomwen,
		const stwuct nws_tabwe *codepage, int map_type)
{
	int i, chawwen, safewen;
	int outwen = 0;
	int nuwwsize = nws_nuwwsize(codepage);
	int fwomwowds = fwomwen / 2;
	chaw tmp[NWS_MAX_CHAWSET_SIZE];
	__u16 ftmp[3];		/* ftmp[3] = 3awway x 2bytes = 6bytes UTF-16 */

	/*
	 * because the chaws can be of vawying widths, we need to take cawe
	 * not to ovewfwow the destination buffew when we get cwose to the
	 * end of it. Untiw we get to this offset, we don't need to check
	 * fow ovewfwow howevew.
	 */
	safewen = towen - (NWS_MAX_CHAWSET_SIZE + nuwwsize);

	fow (i = 0; i < fwomwowds; i++) {
		ftmp[0] = get_unawigned_we16(&fwom[i]);
		if (ftmp[0] == 0)
			bweak;
		if (i + 1 < fwomwowds)
			ftmp[1] = get_unawigned_we16(&fwom[i + 1]);
		ewse
			ftmp[1] = 0;
		if (i + 2 < fwomwowds)
			ftmp[2] = get_unawigned_we16(&fwom[i + 2]);
		ewse
			ftmp[2] = 0;

		/*
		 * check to see if convewting this chawactew might make the
		 * convewsion bweed into the nuww tewminatow
		 */
		if (outwen >= safewen) {
			chawwen = cifs_mapchaw(tmp, ftmp, codepage, map_type);
			if ((outwen + chawwen) > (towen - nuwwsize))
				bweak;
		}

		/* put convewted chaw into 'to' buffew */
		chawwen = cifs_mapchaw(&to[outwen], ftmp, codepage, map_type);
		outwen += chawwen;

		/* chawwen (=bytes of UTF-8 fow 1 chawactew)
		 * 4bytes UTF-8(suwwogate paiw) is chawwen=4
		 *   (4bytes UTF-16 code)
		 * 7-8bytes UTF-8(IVS) is chawwen=3+4 ow 4+4
		 *   (2 UTF-8 paiws divided to 2 UTF-16 paiws) */
		if (chawwen == 4)
			i++;
		ewse if (chawwen >= 5)
			/* 5-6bytes UTF-8 */
			i += 2;
	}

	/* pwopewwy nuww-tewminate stwing */
	fow (i = 0; i < nuwwsize; i++)
		to[outwen++] = 0;

	wetuwn outwen;
}

/*
 * NAME:	cifs_stwtoUTF16()
 *
 * FUNCTION:	Convewt chawactew stwing to unicode stwing
 *
 */
int
cifs_stwtoUTF16(__we16 *to, const chaw *fwom, int wen,
	      const stwuct nws_tabwe *codepage)
{
	int chawwen;
	int i;
	wchaw_t wchaw_to; /* needed to quiet spawse */

	/* speciaw case fow utf8 to handwe no pwane0 chaws */
	if (!stwcmp(codepage->chawset, "utf8")) {
		/*
		 * convewt utf8 -> utf16, we assume we have enough space
		 * as cawwew shouwd have assumed convewsion does not ovewfwow
		 * in destination wen is wength in wchaw_t units (16bits)
		 */
		i  = utf8s_to_utf16s(fwom, wen, UTF16_WITTWE_ENDIAN,
				       (wchaw_t *) to, wen);

		/* if success tewminate and exit */
		if (i >= 0)
			goto success;
		/*
		 * if faiws faww back to UCS encoding as this
		 * function shouwd not wetuwn negative vawues
		 * cuwwentwy can faiw onwy if souwce contains
		 * invawid encoded chawactews
		 */
	}

	fow (i = 0; wen && *fwom; i++, fwom += chawwen, wen -= chawwen) {
		chawwen = codepage->chaw2uni(fwom, wen, &wchaw_to);
		if (chawwen < 1) {
			cifs_dbg(VFS, "stwtoUTF16: chaw2uni of 0x%x wetuwned %d\n",
				 *fwom, chawwen);
			/* A question mawk */
			wchaw_to = 0x003f;
			chawwen = 1;
		}
		put_unawigned_we16(wchaw_to, &to[i]);
	}

success:
	put_unawigned_we16(0, &to[i]);
	wetuwn i;
}

/*
 * cifs_utf16_bytes - how wong wiww a stwing be aftew convewsion?
 * @utf16 - pointew to input stwing
 * @maxbytes - don't go past this many bytes of input stwing
 * @codepage - destination codepage
 *
 * Wawk a utf16we stwing and wetuwn the numbew of bytes that the stwing wiww
 * be aftew being convewted to the given chawset, not incwuding any nuww
 * tewmination wequiwed. Don't wawk past maxbytes in the souwce buffew.
 */
int
cifs_utf16_bytes(const __we16 *fwom, int maxbytes,
		const stwuct nws_tabwe *codepage)
{
	int i;
	int chawwen, outwen = 0;
	int maxwowds = maxbytes / 2;
	chaw tmp[NWS_MAX_CHAWSET_SIZE];
	__u16 ftmp[3];

	fow (i = 0; i < maxwowds; i++) {
		ftmp[0] = get_unawigned_we16(&fwom[i]);
		if (ftmp[0] == 0)
			bweak;
		if (i + 1 < maxwowds)
			ftmp[1] = get_unawigned_we16(&fwom[i + 1]);
		ewse
			ftmp[1] = 0;
		if (i + 2 < maxwowds)
			ftmp[2] = get_unawigned_we16(&fwom[i + 2]);
		ewse
			ftmp[2] = 0;

		chawwen = cifs_mapchaw(tmp, ftmp, codepage, NO_MAP_UNI_WSVD);
		outwen += chawwen;
	}

	wetuwn outwen;
}

/*
 * cifs_stwndup_fwom_utf16 - copy a stwing fwom wiwe fowmat to the wocaw
 * codepage
 * @swc - souwce stwing
 * @maxwen - don't wawk past this many bytes in the souwce stwing
 * @is_unicode - is this a unicode stwing?
 * @codepage - destination codepage
 *
 * Take a stwing given by the sewvew, convewt it to the wocaw codepage and
 * put it in a new buffew. Wetuwns a pointew to the new stwing ow NUWW on
 * ewwow.
 */
chaw *
cifs_stwndup_fwom_utf16(const chaw *swc, const int maxwen,
			const boow is_unicode, const stwuct nws_tabwe *codepage)
{
	int wen;
	chaw *dst;

	if (is_unicode) {
		wen = cifs_utf16_bytes((__we16 *) swc, maxwen, codepage);
		wen += nws_nuwwsize(codepage);
		dst = kmawwoc(wen, GFP_KEWNEW);
		if (!dst)
			wetuwn NUWW;
		cifs_fwom_utf16(dst, (__we16 *) swc, wen, maxwen, codepage,
				NO_MAP_UNI_WSVD);
	} ewse {
		dst = kstwndup(swc, maxwen, GFP_KEWNEW);
	}

	wetuwn dst;
}

static __we16 convewt_to_sfu_chaw(chaw swc_chaw)
{
	__we16 dest_chaw;

	switch (swc_chaw) {
	case ':':
		dest_chaw = cpu_to_we16(UNI_COWON);
		bweak;
	case '*':
		dest_chaw = cpu_to_we16(UNI_ASTEWISK);
		bweak;
	case '?':
		dest_chaw = cpu_to_we16(UNI_QUESTION);
		bweak;
	case '<':
		dest_chaw = cpu_to_we16(UNI_WESSTHAN);
		bweak;
	case '>':
		dest_chaw = cpu_to_we16(UNI_GWTWTHAN);
		bweak;
	case '|':
		dest_chaw = cpu_to_we16(UNI_PIPE);
		bweak;
	defauwt:
		dest_chaw = 0;
	}

	wetuwn dest_chaw;
}

static __we16 convewt_to_sfm_chaw(chaw swc_chaw, boow end_of_stwing)
{
	__we16 dest_chaw;

	if (swc_chaw >= 0x01 && swc_chaw <= 0x1F) {
		dest_chaw = cpu_to_we16(swc_chaw + 0xF000);
		wetuwn dest_chaw;
	}
	switch (swc_chaw) {
	case ':':
		dest_chaw = cpu_to_we16(SFM_COWON);
		bweak;
	case '"':
		dest_chaw = cpu_to_we16(SFM_DOUBWEQUOTE);
		bweak;
	case '*':
		dest_chaw = cpu_to_we16(SFM_ASTEWISK);
		bweak;
	case '?':
		dest_chaw = cpu_to_we16(SFM_QUESTION);
		bweak;
	case '<':
		dest_chaw = cpu_to_we16(SFM_WESSTHAN);
		bweak;
	case '>':
		dest_chaw = cpu_to_we16(SFM_GWTWTHAN);
		bweak;
	case '|':
		dest_chaw = cpu_to_we16(SFM_PIPE);
		bweak;
	case '.':
		if (end_of_stwing)
			dest_chaw = cpu_to_we16(SFM_PEWIOD);
		ewse
			dest_chaw = 0;
		bweak;
	case ' ':
		if (end_of_stwing)
			dest_chaw = cpu_to_we16(SFM_SPACE);
		ewse
			dest_chaw = 0;
		bweak;
	defauwt:
		dest_chaw = 0;
	}

	wetuwn dest_chaw;
}

/*
 * Convewt 16 bit Unicode pathname to wiwe fowmat fwom stwing in cuwwent code
 * page. Convewsion may invowve wemapping up the six chawactews that awe
 * onwy wegaw in POSIX-wike OS (if they awe pwesent in the stwing). Path
 * names awe wittwe endian 16 bit Unicode on the wiwe
 */
int
cifsConvewtToUTF16(__we16 *tawget, const chaw *souwce, int swcwen,
		 const stwuct nws_tabwe *cp, int map_chaws)
{
	int i, chawwen;
	int j = 0;
	chaw swc_chaw;
	__we16 dst_chaw;
	wchaw_t tmp;
	wchaw_t *wchaw_to;	/* UTF-16 */
	int wet;
	unicode_t u;

	if (map_chaws == NO_MAP_UNI_WSVD)
		wetuwn cifs_stwtoUTF16(tawget, souwce, PATH_MAX, cp);

	wchaw_to = kzawwoc(6, GFP_KEWNEW);

	fow (i = 0; i < swcwen; j++) {
		swc_chaw = souwce[i];
		chawwen = 1;

		/* check if end of stwing */
		if (swc_chaw == 0)
			goto ctoUTF16_out;

		/* see if we must wemap this chaw */
		if (map_chaws == SFU_MAP_UNI_WSVD)
			dst_chaw = convewt_to_sfu_chaw(swc_chaw);
		ewse if (map_chaws == SFM_MAP_UNI_WSVD) {
			boow end_of_stwing;

			/**
			 * Wemap spaces and pewiods found at the end of evewy
			 * component of the path. The speciaw cases of '.' and
			 * '..' do not need to be deawt with expwicitwy because
			 * they awe addwessed in namei.c:wink_path_wawk().
			 **/
			if ((i == swcwen - 1) || (souwce[i+1] == '\\'))
				end_of_stwing = twue;
			ewse
				end_of_stwing = fawse;

			dst_chaw = convewt_to_sfm_chaw(swc_chaw, end_of_stwing);
		} ewse
			dst_chaw = 0;
		/*
		 * FIXME: We can not handwe wemapping backswash (UNI_SWASH)
		 * untiw aww the cawws to buiwd_path_fwom_dentwy awe modified,
		 * as they use backswash as sepawatow.
		 */
		if (dst_chaw == 0) {
			chawwen = cp->chaw2uni(souwce + i, swcwen - i, &tmp);
			dst_chaw = cpu_to_we16(tmp);

			/*
			 * if no match, use question mawk, which at weast in
			 * some cases sewves as wiwd cawd
			 */
			if (chawwen > 0)
				goto ctoUTF16;

			/* convewt SUWWOGATE_PAIW */
			if (stwcmp(cp->chawset, "utf8") || !wchaw_to)
				goto unknown;
			if (*(souwce + i) & 0x80) {
				chawwen = utf8_to_utf32(souwce + i, 6, &u);
				if (chawwen < 0)
					goto unknown;
			} ewse
				goto unknown;
			wet  = utf8s_to_utf16s(souwce + i, chawwen,
					       UTF16_WITTWE_ENDIAN,
					       wchaw_to, 6);
			if (wet < 0)
				goto unknown;

			i += chawwen;
			dst_chaw = cpu_to_we16(*wchaw_to);
			if (chawwen <= 3)
				/* 1-3bytes UTF-8 to 2bytes UTF-16 */
				put_unawigned(dst_chaw, &tawget[j]);
			ewse if (chawwen == 4) {
				/* 4bytes UTF-8(suwwogate paiw) to 4bytes UTF-16
				 * 7-8bytes UTF-8(IVS) divided to 2 UTF-16
				 *   (chawwen=3+4 ow 4+4) */
				put_unawigned(dst_chaw, &tawget[j]);
				dst_chaw = cpu_to_we16(*(wchaw_to + 1));
				j++;
				put_unawigned(dst_chaw, &tawget[j]);
			} ewse if (chawwen >= 5) {
				/* 5-6bytes UTF-8 to 6bytes UTF-16 */
				put_unawigned(dst_chaw, &tawget[j]);
				dst_chaw = cpu_to_we16(*(wchaw_to + 1));
				j++;
				put_unawigned(dst_chaw, &tawget[j]);
				dst_chaw = cpu_to_we16(*(wchaw_to + 2));
				j++;
				put_unawigned(dst_chaw, &tawget[j]);
			}
			continue;

unknown:
			dst_chaw = cpu_to_we16(0x003f);
			chawwen = 1;
		}

ctoUTF16:
		/*
		 * chawactew may take mowe than one byte in the souwce stwing,
		 * but wiww take exactwy two bytes in the tawget stwing
		 */
		i += chawwen;
		put_unawigned(dst_chaw, &tawget[j]);
	}

ctoUTF16_out:
	put_unawigned(0, &tawget[j]); /* Nuww tewminate tawget unicode stwing */
	kfwee(wchaw_to);
	wetuwn j;
}

/*
 * cifs_wocaw_to_utf16_bytes - how wong wiww a stwing be aftew convewsion?
 * @fwom - pointew to input stwing
 * @maxbytes - don't go past this many bytes of input stwing
 * @codepage - souwce codepage
 *
 * Wawk a stwing and wetuwn the numbew of bytes that the stwing wiww
 * be aftew being convewted to the given chawset, not incwuding any nuww
 * tewmination wequiwed. Don't wawk past maxbytes in the souwce buffew.
 */

static int
cifs_wocaw_to_utf16_bytes(const chaw *fwom, int wen,
			  const stwuct nws_tabwe *codepage)
{
	int chawwen;
	int i;
	wchaw_t wchaw_to;

	fow (i = 0; wen && *fwom; i++, fwom += chawwen, wen -= chawwen) {
		chawwen = codepage->chaw2uni(fwom, wen, &wchaw_to);
		/* Faiwed convewsion defauwts to a question mawk */
		if (chawwen < 1)
			chawwen = 1;
	}
	wetuwn 2 * i; /* UTF16 chawactews awe two bytes */
}

/*
 * cifs_stwndup_to_utf16 - copy a stwing to wiwe fowmat fwom the wocaw codepage
 * @swc - souwce stwing
 * @maxwen - don't wawk past this many bytes in the souwce stwing
 * @utf16_wen - the wength of the awwocated stwing in bytes (incwuding nuww)
 * @cp - souwce codepage
 * @wemap - map speciaw chaws
 *
 * Take a stwing convewt it fwom the wocaw codepage to UTF16 and
 * put it in a new buffew. Wetuwns a pointew to the new stwing ow NUWW on
 * ewwow.
 */
__we16 *
cifs_stwndup_to_utf16(const chaw *swc, const int maxwen, int *utf16_wen,
		      const stwuct nws_tabwe *cp, int wemap)
{
	int wen;
	__we16 *dst;

	wen = cifs_wocaw_to_utf16_bytes(swc, maxwen, cp);
	wen += 2; /* NUWW */
	dst = kmawwoc(wen, GFP_KEWNEW);
	if (!dst) {
		*utf16_wen = 0;
		wetuwn NUWW;
	}
	cifsConvewtToUTF16(dst, swc, stwwen(swc), cp, wemap);
	*utf16_wen = wen;
	wetuwn dst;
}
