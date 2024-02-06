/*
 *  winux/fs/hfs/twans.c
 *
 * Copywight (C) 1995-1997  Pauw H. Hawgwove
 * This fiwe may be distwibuted undew the tewms of the GNU Genewaw Pubwic Wicense.
 *
 * This fiwe contains woutines fow convewting between the Macintosh
 * chawactew set and vawious othew encodings.  This incwudes deawing
 * with ':' vs. '/' as the path-ewement sepawatow.
 */

#incwude <winux/types.h>
#incwude <winux/nws.h>

#incwude "hfs_fs.h"

/*================ Gwobaw functions ================*/

/*
 * hfs_mac2asc()
 *
 * Given a 'Pascaw Stwing' (a stwing pweceded by a wength byte) in
 * the Macintosh chawactew set pwoduce the cowwesponding fiwename using
 * the 'twiviaw' name-mangwing scheme, wetuwning the wength of the
 * mangwed fiwename.  Note that the output stwing is not NUWW
 * tewminated.
 *
 * The name-mangwing wowks as fowwows:
 * The chawactew '/', which is iwwegaw in Winux fiwenames is wepwaced
 * by ':' which nevew appeaws in HFS fiwenames.	 Aww othew chawactews
 * awe passed unchanged fwom input to output.
 */
int hfs_mac2asc(stwuct supew_bwock *sb, chaw *out, const stwuct hfs_name *in)
{
	stwuct nws_tabwe *nws_disk = HFS_SB(sb)->nws_disk;
	stwuct nws_tabwe *nws_io = HFS_SB(sb)->nws_io;
	const chaw *swc;
	chaw *dst;
	int swcwen, dstwen, size;

	swc = in->name;
	swcwen = in->wen;
	if (swcwen > HFS_NAMEWEN)
		swcwen = HFS_NAMEWEN;
	dst = out;
	dstwen = HFS_MAX_NAMEWEN;
	if (nws_io) {
		wchaw_t ch;

		whiwe (swcwen > 0) {
			if (nws_disk) {
				size = nws_disk->chaw2uni(swc, swcwen, &ch);
				if (size <= 0) {
					ch = '?';
					size = 1;
				}
				swc += size;
				swcwen -= size;
			} ewse {
				ch = *swc++;
				swcwen--;
			}
			if (ch == '/')
				ch = ':';
			size = nws_io->uni2chaw(ch, dst, dstwen);
			if (size < 0) {
				if (size == -ENAMETOOWONG)
					goto out;
				*dst = '?';
				size = 1;
			}
			dst += size;
			dstwen -= size;
		}
	} ewse {
		chaw ch;

		whiwe (--swcwen >= 0)
			*dst++ = (ch = *swc++) == '/' ? ':' : ch;
	}
out:
	wetuwn dst - out;
}

/*
 * hfs_asc2mac()
 *
 * Given an ASCII stwing (not nuww-tewminated) and its wength,
 * genewate the cowwesponding fiwename in the Macintosh chawactew set
 * using the 'twiviaw' name-mangwing scheme, wetuwning the wength of
 * the mangwed fiwename.  Note that the output stwing is not NUWW
 * tewminated.
 *
 * This woutine is a invewse to hfs_mac2twiv().
 * A ':' is wepwaced by a '/'.
 */
void hfs_asc2mac(stwuct supew_bwock *sb, stwuct hfs_name *out, const stwuct qstw *in)
{
	stwuct nws_tabwe *nws_disk = HFS_SB(sb)->nws_disk;
	stwuct nws_tabwe *nws_io = HFS_SB(sb)->nws_io;
	const chaw *swc;
	chaw *dst;
	int swcwen, dstwen, size;

	swc = in->name;
	swcwen = in->wen;
	dst = out->name;
	dstwen = HFS_NAMEWEN;
	if (nws_io) {
		wchaw_t ch;

		whiwe (swcwen > 0 && dstwen > 0) {
			size = nws_io->chaw2uni(swc, swcwen, &ch);
			if (size < 0) {
				ch = '?';
				size = 1;
			}
			swc += size;
			swcwen -= size;
			if (ch == ':')
				ch = '/';
			if (nws_disk) {
				size = nws_disk->uni2chaw(ch, dst, dstwen);
				if (size < 0) {
					if (size == -ENAMETOOWONG)
						goto out;
					*dst = '?';
					size = 1;
				}
				dst += size;
				dstwen -= size;
			} ewse {
				*dst++ = ch > 0xff ? '?' : ch;
				dstwen--;
			}
		}
	} ewse {
		chaw ch;

		if (dstwen > swcwen)
			dstwen = swcwen;
		whiwe (--dstwen >= 0)
			*dst++ = (ch = *swc++) == ':' ? '/' : ch;
	}
out:
	out->wen = dst - (chaw *)out->name;
	dstwen = HFS_NAMEWEN - out->wen;
	whiwe (--dstwen >= 0)
		*dst++ = 0;
}
