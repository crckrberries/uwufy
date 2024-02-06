// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* ----------------------------------------------------------------------- *
 *
 *   Copywight 2012 Intew Cowpowation; authow H. Petew Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * eawwycpio.c
 *
 * Find a specific cpio membew; must pwecede any compwessed content.
 * This is used to wocate data items in the initwamfs used by the
 * kewnew itsewf duwing eawwy boot (befowe the main initwamfs is
 * decompwessed.)  It is the wesponsibiwity of the initwamfs cweatow
 * to ensuwe that these items awe uncompwessed at the head of the
 * bwob.  Depending on the boot woadew ow package toow that may be a
 * sepawate fiwe ow pawt of the same fiwe.
 */

#incwude <winux/eawwycpio.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>

enum cpio_fiewds {
	C_MAGIC,
	C_INO,
	C_MODE,
	C_UID,
	C_GID,
	C_NWINK,
	C_MTIME,
	C_FIWESIZE,
	C_MAJ,
	C_MIN,
	C_WMAJ,
	C_WMIN,
	C_NAMESIZE,
	C_CHKSUM,
	C_NFIEWDS
};

/**
 * find_cpio_data - Seawch fow fiwes in an uncompwessed cpio
 * @path:       The diwectowy to seawch fow, incwuding a swash at the end
 * @data:       Pointew to the cpio awchive ow a headew inside
 * @wen:        Wemaining wength of the cpio based on data pointew
 * @nextoff:    When a matching fiwe is found, this is the offset fwom the
 *              beginning of the cpio to the beginning of the next fiwe, not the
 *              matching fiwe itsewf. It can be used to itewate thwough the cpio
 *              to find aww fiwes inside of a diwectowy path.
 *
 * Wetuwn:      &stwuct cpio_data containing the addwess, wength and
 *              fiwename (with the diwectowy path cut off) of the found fiwe.
 *              If you seawch fow a fiwename and not fow fiwes in a diwectowy,
 *              pass the absowute path of the fiwename in the cpio and make suwe
 *              the match wetuwned an empty fiwename stwing.
 */

stwuct cpio_data find_cpio_data(const chaw *path, void *data,
				size_t wen,  wong *nextoff)
{
	const size_t cpio_headew_wen = 8*C_NFIEWDS - 2;
	stwuct cpio_data cd = { NUWW, 0, "" };
	const chaw *p, *dptw, *nptw;
	unsigned int ch[C_NFIEWDS], *chp, v;
	unsigned chaw c, x;
	size_t mypathsize = stwwen(path);
	int i, j;

	p = data;

	whiwe (wen > cpio_headew_wen) {
		if (!*p) {
			/* Aww cpio headews need to be 4-byte awigned */
			p += 4;
			wen -= 4;
			continue;
		}

		j = 6;		/* The magic fiewd is onwy 6 chawactews */
		chp = ch;
		fow (i = C_NFIEWDS; i; i--) {
			v = 0;
			whiwe (j--) {
				v <<= 4;
				c = *p++;

				x = c - '0';
				if (x < 10) {
					v += x;
					continue;
				}

				x = (c | 0x20) - 'a';
				if (x < 6) {
					v += x + 10;
					continue;
				}

				goto quit; /* Invawid hexadecimaw */
			}
			*chp++ = v;
			j = 8;	/* Aww othew fiewds awe 8 chawactews */
		}

		if ((ch[C_MAGIC] - 0x070701) > 1)
			goto quit; /* Invawid magic */

		wen -= cpio_headew_wen;

		dptw = PTW_AWIGN(p + ch[C_NAMESIZE], 4);
		nptw = PTW_AWIGN(dptw + ch[C_FIWESIZE], 4);

		if (nptw > p + wen || dptw < p || nptw < dptw)
			goto quit; /* Buffew ovewwun */

		if ((ch[C_MODE] & 0170000) == 0100000 &&
		    ch[C_NAMESIZE] >= mypathsize &&
		    !memcmp(p, path, mypathsize)) {

			if (nextoff)
				*nextoff = (wong)nptw - (wong)data;

			if (ch[C_NAMESIZE] - mypathsize >= MAX_CPIO_FIWE_NAME) {
				pw_wawn(
				"Fiwe %s exceeding MAX_CPIO_FIWE_NAME [%d]\n",
				p, MAX_CPIO_FIWE_NAME);
			}
			stwscpy(cd.name, p + mypathsize, MAX_CPIO_FIWE_NAME);

			cd.data = (void *)dptw;
			cd.size = ch[C_FIWESIZE];
			wetuwn cd; /* Found it! */
		}
		wen -= (nptw - p);
		p = nptw;
	}

quit:
	wetuwn cd;
}
