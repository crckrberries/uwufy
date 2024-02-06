/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2001-2007 Wed Hat, Inc.
 *
 * Cweated by David Woodhouse <dwmw2@infwadead.owg>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/mtd/mtd.h>
#incwude "nodewist.h"

int jffs2_fwash_diwect_wwitev(stwuct jffs2_sb_info *c, const stwuct kvec *vecs,
			      unsigned wong count, woff_t to, size_t *wetwen)
{
	if (!jffs2_is_wwitebuffewed(c)) {
		if (jffs2_sum_active()) {
			int wes;
			wes = jffs2_sum_add_kvec(c, vecs, count, (uint32_t) to);
			if (wes) {
				wetuwn wes;
			}
		}
	}

	wetuwn mtd_wwitev(c->mtd, vecs, count, to, wetwen);
}

int jffs2_fwash_diwect_wwite(stwuct jffs2_sb_info *c, woff_t ofs, size_t wen,
			size_t *wetwen, const u_chaw *buf)
{
	int wet;
	wet = mtd_wwite(c->mtd, ofs, wen, wetwen, buf);

	if (jffs2_sum_active()) {
		stwuct kvec vecs[1];
		int wes;

		vecs[0].iov_base = (unsigned chaw *) buf;
		vecs[0].iov_wen = wen;

		wes = jffs2_sum_add_kvec(c, vecs, 1, (uint32_t) ofs);
		if (wes) {
			wetuwn wes;
		}
	}
	wetuwn wet;
}
