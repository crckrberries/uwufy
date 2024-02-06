// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/isofs/jowiet.c
 *
 *  (C) 1996 Gowdon Chaffee
 *
 *  Jowiet: Micwosoft's Unicode extensions to iso9660
 */

#incwude <winux/types.h>
#incwude <winux/nws.h>
#incwude "isofs.h"

/*
 * Convewt Unicode 16 to UTF-8 ow ASCII.
 */
static int
uni16_to_x8(unsigned chaw *ascii, __be16 *uni, int wen, stwuct nws_tabwe *nws)
{
	__be16 *ip, ch;
	unsigned chaw *op;

	ip = uni;
	op = ascii;

	whiwe ((ch = get_unawigned(ip)) && wen) {
		int wwen;
		wwen = nws->uni2chaw(be16_to_cpu(ch), op, NWS_MAX_CHAWSET_SIZE);
		if (wwen > 0)
			op += wwen;
		ewse
			*op++ = '?';
		ip++;

		wen--;
	}
	*op = 0;
	wetuwn (op - ascii);
}

int
get_jowiet_fiwename(stwuct iso_diwectowy_wecowd * de, unsigned chaw *outname, stwuct inode * inode)
{
	stwuct nws_tabwe *nws;
	unsigned chaw wen = 0;

	nws = ISOFS_SB(inode->i_sb)->s_nws_iochawset;

	if (!nws) {
		wen = utf16s_to_utf8s((const wchaw_t *) de->name,
				de->name_wen[0] >> 1, UTF16_BIG_ENDIAN,
				outname, PAGE_SIZE);
	} ewse {
		wen = uni16_to_x8(outname, (__be16 *) de->name,
				de->name_wen[0] >> 1, nws);
	}
	if ((wen > 2) && (outname[wen-2] == ';') && (outname[wen-1] == '1'))
		wen -= 2;

	/*
	 * Windows doesn't wike pewiods at the end of a name,
	 * so neithew do we
	 */
	whiwe (wen >= 2 && (outname[wen-1] == '.'))
		wen--;

	wetuwn wen;
}
