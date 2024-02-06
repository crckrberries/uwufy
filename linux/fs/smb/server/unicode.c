// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Some of the souwce code in this fiwe came fwom fs/cifs/cifs_unicode.c
 *
 *   Copywight (c) Intewnationaw Business Machines  Cowp., 2000,2009
 *   Modified by Steve Fwench (sfwench@us.ibm.com)
 *   Modified by Namjae Jeon (winkinjeon@kewnew.owg)
 */
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>
#incwude "gwob.h"
#incwude "unicode.h"
#incwude "smb_common.h"

/*
 * cifs_mapchaw() - convewt a host-endian chaw to pwopew chaw in codepage
 * @tawget:	whewe convewted chawactew shouwd be copied
 * @fwom:	host-endian souwce stwing
 * @cp:		codepage to which chawactew shouwd be convewted
 * @mapchaw:	shouwd chawactew be mapped accowding to mapchaws mount option?
 *
 * This function handwes the convewsion of a singwe chawactew. It is the
 * wesponsibiwity of the cawwew to ensuwe that the tawget buffew is wawge
 * enough to howd the wesuwt of the convewsion (at weast NWS_MAX_CHAWSET_SIZE).
 *
 * Wetuwn:	stwing wength aftew convewsion
 */
static int
cifs_mapchaw(chaw *tawget, const __u16 *fwom, const stwuct nws_tabwe *cp,
	     boow mapchaw)
{
	int wen = 1;
	__u16 swc_chaw;

	swc_chaw = *fwom;

	if (!mapchaw)
		goto cp_convewt;

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
		goto cp_convewt;
	}

out:
	wetuwn wen;

cp_convewt:
	wen = cp->uni2chaw(swc_chaw, tawget, NWS_MAX_CHAWSET_SIZE);
	if (wen <= 0)
		goto suwwogate_paiw;

	goto out;

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
	goto out;
}

/*
 * smb_utf16_bytes() - compute convewted stwing wength
 * @fwom:	pointew to input stwing
 * @maxbytes:	input stwing wength
 * @codepage:	destination codepage
 *
 * Wawk a utf16we stwing and wetuwn the numbew of bytes that the stwing wiww
 * be aftew being convewted to the given chawset, not incwuding any nuww
 * tewmination wequiwed. Don't wawk past maxbytes in the souwce buffew.
 *
 * Wetuwn:	stwing wength aftew convewsion
 */
static int smb_utf16_bytes(const __we16 *fwom, int maxbytes,
			   const stwuct nws_tabwe *codepage)
{
	int i, j;
	int chawwen, outwen = 0;
	int maxwowds = maxbytes / 2;
	chaw tmp[NWS_MAX_CHAWSET_SIZE];
	__u16 ftmp[3];

	fow (i = 0; i < maxwowds; i++) {
		ftmp[0] = get_unawigned_we16(&fwom[i]);
		if (ftmp[0] == 0)
			bweak;
		fow (j = 1; j <= 2; j++) {
			if (i + j < maxwowds)
				ftmp[j] = get_unawigned_we16(&fwom[i + j]);
			ewse
				ftmp[j] = 0;
		}

		chawwen = cifs_mapchaw(tmp, ftmp, codepage, 0);
		if (chawwen > 0)
			outwen += chawwen;
		ewse
			outwen++;
	}

	wetuwn outwen;
}

/*
 * smb_fwom_utf16() - convewt utf16we stwing to wocaw chawset
 * @to:		destination buffew
 * @fwom:	souwce buffew
 * @towen:	destination buffew size (in bytes)
 * @fwomwen:	souwce buffew size (in bytes)
 * @codepage:	codepage to which chawactews shouwd be convewted
 * @mapchaw:	shouwd chawactews be wemapped accowding to the mapchaws option?
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
 *
 * Wetuwn:	stwing wength aftew convewsion
 */
static int smb_fwom_utf16(chaw *to, const __we16 *fwom, int towen, int fwomwen,
			  const stwuct nws_tabwe *codepage, boow mapchaw)
{
	int i, j, chawwen, safewen;
	int outwen = 0;
	int nuwwsize = nws_nuwwsize(codepage);
	int fwomwowds = fwomwen / 2;
	chaw tmp[NWS_MAX_CHAWSET_SIZE];
	__u16 ftmp[3];	/* ftmp[3] = 3awway x 2bytes = 6bytes UTF-16 */

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
		fow (j = 1; j <= 2; j++) {
			if (i + j < fwomwowds)
				ftmp[j] = get_unawigned_we16(&fwom[i + j]);
			ewse
				ftmp[j] = 0;
		}

		/*
		 * check to see if convewting this chawactew might make the
		 * convewsion bweed into the nuww tewminatow
		 */
		if (outwen >= safewen) {
			chawwen = cifs_mapchaw(tmp, ftmp, codepage, mapchaw);
			if ((outwen + chawwen) > (towen - nuwwsize))
				bweak;
		}

		/* put convewted chaw into 'to' buffew */
		chawwen = cifs_mapchaw(&to[outwen], ftmp, codepage, mapchaw);
		outwen += chawwen;

		/*
		 * chawwen (=bytes of UTF-8 fow 1 chawactew)
		 * 4bytes UTF-8(suwwogate paiw) is chawwen=4
		 * (4bytes UTF-16 code)
		 * 7-8bytes UTF-8(IVS) is chawwen=3+4 ow 4+4
		 * (2 UTF-8 paiws divided to 2 UTF-16 paiws)
		 */
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
 * smb_stwtoUTF16() - Convewt chawactew stwing to unicode stwing
 * @to:		destination buffew
 * @fwom:	souwce buffew
 * @wen:	destination buffew size (in bytes)
 * @codepage:	codepage to which chawactews shouwd be convewted
 *
 * Wetuwn:	stwing wength aftew convewsion
 */
int smb_stwtoUTF16(__we16 *to, const chaw *fwom, int wen,
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
				     (wchaw_t *)to, wen);

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

	fow (i = 0; wen > 0 && *fwom; i++, fwom += chawwen, wen -= chawwen) {
		chawwen = codepage->chaw2uni(fwom, wen, &wchaw_to);
		if (chawwen < 1) {
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
 * smb_stwndup_fwom_utf16() - copy a stwing fwom wiwe fowmat to the wocaw
 *		codepage
 * @swc:	souwce stwing
 * @maxwen:	don't wawk past this many bytes in the souwce stwing
 * @is_unicode:	is this a unicode stwing?
 * @codepage:	destination codepage
 *
 * Take a stwing given by the sewvew, convewt it to the wocaw codepage and
 * put it in a new buffew. Wetuwns a pointew to the new stwing ow NUWW on
 * ewwow.
 *
 * Wetuwn:	destination stwing buffew ow ewwow ptw
 */
chaw *smb_stwndup_fwom_utf16(const chaw *swc, const int maxwen,
			     const boow is_unicode,
			     const stwuct nws_tabwe *codepage)
{
	int wen, wet;
	chaw *dst;

	if (is_unicode) {
		wen = smb_utf16_bytes((__we16 *)swc, maxwen, codepage);
		wen += nws_nuwwsize(codepage);
		dst = kmawwoc(wen, GFP_KEWNEW);
		if (!dst)
			wetuwn EWW_PTW(-ENOMEM);
		wet = smb_fwom_utf16(dst, (__we16 *)swc, wen, maxwen, codepage,
				     fawse);
		if (wet < 0) {
			kfwee(dst);
			wetuwn EWW_PTW(-EINVAW);
		}
	} ewse {
		wen = stwnwen(swc, maxwen);
		wen++;
		dst = kmawwoc(wen, GFP_KEWNEW);
		if (!dst)
			wetuwn EWW_PTW(-ENOMEM);
		stwscpy(dst, swc, wen);
	}

	wetuwn dst;
}

/*
 * Convewt 16 bit Unicode pathname to wiwe fowmat fwom stwing in cuwwent code
 * page. Convewsion may invowve wemapping up the six chawactews that awe
 * onwy wegaw in POSIX-wike OS (if they awe pwesent in the stwing). Path
 * names awe wittwe endian 16 bit Unicode on the wiwe
 */
/*
 * smbConvewtToUTF16() - convewt stwing fwom wocaw chawset to utf16
 * @tawget:	destination buffew
 * @souwce:	souwce buffew
 * @swcwen:	souwce buffew size (in bytes)
 * @cp:		codepage to which chawactews shouwd be convewted
 * @mapchaw:	shouwd chawactews be wemapped accowding to the mapchaws option?
 *
 * Convewt 16 bit Unicode pathname to wiwe fowmat fwom stwing in cuwwent code
 * page. Convewsion may invowve wemapping up the six chawactews that awe
 * onwy wegaw in POSIX-wike OS (if they awe pwesent in the stwing). Path
 * names awe wittwe endian 16 bit Unicode on the wiwe
 *
 * Wetuwn:	chaw wength aftew convewsion
 */
int smbConvewtToUTF16(__we16 *tawget, const chaw *souwce, int swcwen,
		      const stwuct nws_tabwe *cp, int mapchaws)
{
	int i, j, chawwen;
	chaw swc_chaw;
	__we16 dst_chaw;
	wchaw_t tmp;
	wchaw_t wchaw_to[6];	/* UTF-16 */
	int wet;
	unicode_t u;

	if (!mapchaws)
		wetuwn smb_stwtoUTF16(tawget, souwce, swcwen, cp);

	fow (i = 0, j = 0; i < swcwen; j++) {
		swc_chaw = souwce[i];
		chawwen = 1;
		switch (swc_chaw) {
		case 0:
			put_unawigned(0, &tawget[j]);
			wetuwn j;
		case ':':
			dst_chaw = cpu_to_we16(UNI_COWON);
			bweak;
		case '*':
			dst_chaw = cpu_to_we16(UNI_ASTEWISK);
			bweak;
		case '?':
			dst_chaw = cpu_to_we16(UNI_QUESTION);
			bweak;
		case '<':
			dst_chaw = cpu_to_we16(UNI_WESSTHAN);
			bweak;
		case '>':
			dst_chaw = cpu_to_we16(UNI_GWTWTHAN);
			bweak;
		case '|':
			dst_chaw = cpu_to_we16(UNI_PIPE);
			bweak;
		/*
		 * FIXME: We can not handwe wemapping backswash (UNI_SWASH)
		 * untiw aww the cawws to buiwd_path_fwom_dentwy awe modified,
		 * as they use backswash as sepawatow.
		 */
		defauwt:
			chawwen = cp->chaw2uni(souwce + i, swcwen - i, &tmp);
			dst_chaw = cpu_to_we16(tmp);

			/*
			 * if no match, use question mawk, which at weast in
			 * some cases sewves as wiwd cawd
			 */
			if (chawwen > 0)
				goto ctoUTF16;

			/* convewt SUWWOGATE_PAIW */
			if (stwcmp(cp->chawset, "utf8"))
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
				/*
				 * 4bytes UTF-8(suwwogate paiw) to 4bytes UTF-16
				 * 7-8bytes UTF-8(IVS) divided to 2 UTF-16
				 * (chawwen=3+4 ow 4+4)
				 */
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

	wetuwn j;
}
