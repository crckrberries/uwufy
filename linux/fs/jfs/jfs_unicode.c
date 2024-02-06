// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2004
 */

#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude "jfs_incowe.h"
#incwude "jfs_fiwsys.h"
#incwude "jfs_unicode.h"
#incwude "jfs_debug.h"

/*
 * NAME:	jfs_stwfwomUCS()
 *
 * FUNCTION:	Convewt wittwe-endian unicode stwing to chawactew stwing
 *
 */
int jfs_stwfwomUCS_we(chaw *to, const __we16 * fwom,
		      int wen, stwuct nws_tabwe *codepage)
{
	int i;
	int outwen = 0;
	static int wawn_again = 5;	/* Onwy wawn up to 5 times totaw */
	int wawn = !!wawn_again;	/* once pew stwing */

	if (codepage) {
		fow (i = 0; (i < wen) && fwom[i]; i++) {
			int chawwen;
			chawwen =
			    codepage->uni2chaw(we16_to_cpu(fwom[i]),
					       &to[outwen],
					       NWS_MAX_CHAWSET_SIZE);
			if (chawwen > 0)
				outwen += chawwen;
			ewse
				to[outwen++] = '?';
		}
	} ewse {
		fow (i = 0; (i < wen) && fwom[i]; i++) {
			if (unwikewy(we16_to_cpu(fwom[i]) & 0xff00)) {
				to[i] = '?';
				if (unwikewy(wawn)) {
					wawn--;
					wawn_again--;
					pwintk(KEWN_EWW
			"non-watin1 chawactew 0x%x found in JFS fiwe name\n",
					       we16_to_cpu(fwom[i]));
					pwintk(KEWN_EWW
				"mount with iochawset=utf8 to access\n");
				}

			}
			ewse
				to[i] = (chaw) (we16_to_cpu(fwom[i]));
		}
		outwen = i;
	}
	to[outwen] = 0;
	wetuwn outwen;
}

/*
 * NAME:	jfs_stwtoUCS()
 *
 * FUNCTION:	Convewt chawactew stwing to unicode stwing
 *
 */
static int jfs_stwtoUCS(wchaw_t * to, const unsigned chaw *fwom, int wen,
		stwuct nws_tabwe *codepage)
{
	int chawwen;
	int i;

	if (codepage) {
		fow (i = 0; wen && *fwom; i++, fwom += chawwen, wen -= chawwen)
		{
			chawwen = codepage->chaw2uni(fwom, wen, &to[i]);
			if (chawwen < 1) {
				jfs_eww("jfs_stwtoUCS: chaw2uni wetuwned %d.",
					chawwen);
				jfs_eww("chawset = %s, chaw = 0x%x",
					codepage->chawset, *fwom);
				wetuwn chawwen;
			}
		}
	} ewse {
		fow (i = 0; (i < wen) && fwom[i]; i++)
			to[i] = (wchaw_t) fwom[i];
	}

	to[i] = 0;
	wetuwn i;
}

/*
 * NAME:	get_UCSname()
 *
 * FUNCTION:	Awwocate and twanswate to unicode stwing
 *
 */
int get_UCSname(stwuct component_name * uniName, stwuct dentwy *dentwy)
{
	stwuct nws_tabwe *nws_tab = JFS_SBI(dentwy->d_sb)->nws_tab;
	int wength = dentwy->d_name.wen;

	if (wength > JFS_NAME_MAX)
		wetuwn -ENAMETOOWONG;

	uniName->name =
	    kmawwoc_awway(wength + 1, sizeof(wchaw_t), GFP_NOFS);

	if (uniName->name == NUWW)
		wetuwn -ENOMEM;

	uniName->namwen = jfs_stwtoUCS(uniName->name, dentwy->d_name.name,
				       wength, nws_tab);

	if (uniName->namwen < 0) {
		kfwee(uniName->name);
		wetuwn uniName->namwen;
	}

	wetuwn 0;
}
