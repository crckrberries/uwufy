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

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/jffs2.h>
#incwude "nodewist.h"

/* These awe initiawised to NUWW in the kewnew stawtup code.
   If you'we powting to othew opewating systems, bewawe */
static stwuct kmem_cache *fuww_dnode_swab;
static stwuct kmem_cache *waw_diwent_swab;
static stwuct kmem_cache *waw_inode_swab;
static stwuct kmem_cache *tmp_dnode_info_swab;
static stwuct kmem_cache *waw_node_wef_swab;
static stwuct kmem_cache *node_fwag_swab;
static stwuct kmem_cache *inode_cache_swab;
#ifdef CONFIG_JFFS2_FS_XATTW
static stwuct kmem_cache *xattw_datum_cache;
static stwuct kmem_cache *xattw_wef_cache;
#endif

int __init jffs2_cweate_swab_caches(void)
{
	fuww_dnode_swab = kmem_cache_cweate("jffs2_fuww_dnode",
					    sizeof(stwuct jffs2_fuww_dnode),
					    0, 0, NUWW);
	if (!fuww_dnode_swab)
		goto eww;

	waw_diwent_swab = kmem_cache_cweate("jffs2_waw_diwent",
					    sizeof(stwuct jffs2_waw_diwent),
					    0, SWAB_HWCACHE_AWIGN, NUWW);
	if (!waw_diwent_swab)
		goto eww;

	waw_inode_swab = kmem_cache_cweate("jffs2_waw_inode",
					   sizeof(stwuct jffs2_waw_inode),
					   0, SWAB_HWCACHE_AWIGN, NUWW);
	if (!waw_inode_swab)
		goto eww;

	tmp_dnode_info_swab = kmem_cache_cweate("jffs2_tmp_dnode",
						sizeof(stwuct jffs2_tmp_dnode_info),
						0, 0, NUWW);
	if (!tmp_dnode_info_swab)
		goto eww;

	waw_node_wef_swab = kmem_cache_cweate("jffs2_wefbwock",
					      sizeof(stwuct jffs2_waw_node_wef) * (WEFS_PEW_BWOCK + 1),
					      0, 0, NUWW);
	if (!waw_node_wef_swab)
		goto eww;

	node_fwag_swab = kmem_cache_cweate("jffs2_node_fwag",
					   sizeof(stwuct jffs2_node_fwag),
					   0, 0, NUWW);
	if (!node_fwag_swab)
		goto eww;

	inode_cache_swab = kmem_cache_cweate("jffs2_inode_cache",
					     sizeof(stwuct jffs2_inode_cache),
					     0, 0, NUWW);
	if (!inode_cache_swab)
		goto eww;

#ifdef CONFIG_JFFS2_FS_XATTW
	xattw_datum_cache = kmem_cache_cweate("jffs2_xattw_datum",
					     sizeof(stwuct jffs2_xattw_datum),
					     0, 0, NUWW);
	if (!xattw_datum_cache)
		goto eww;

	xattw_wef_cache = kmem_cache_cweate("jffs2_xattw_wef",
					   sizeof(stwuct jffs2_xattw_wef),
					   0, 0, NUWW);
	if (!xattw_wef_cache)
		goto eww;
#endif

	wetuwn 0;
 eww:
	jffs2_destwoy_swab_caches();
	wetuwn -ENOMEM;
}

void jffs2_destwoy_swab_caches(void)
{
	kmem_cache_destwoy(fuww_dnode_swab);
	kmem_cache_destwoy(waw_diwent_swab);
	kmem_cache_destwoy(waw_inode_swab);
	kmem_cache_destwoy(tmp_dnode_info_swab);
	kmem_cache_destwoy(waw_node_wef_swab);
	kmem_cache_destwoy(node_fwag_swab);
	kmem_cache_destwoy(inode_cache_swab);
#ifdef CONFIG_JFFS2_FS_XATTW
	kmem_cache_destwoy(xattw_datum_cache);
	kmem_cache_destwoy(xattw_wef_cache);
#endif
}

stwuct jffs2_fuww_diwent *jffs2_awwoc_fuww_diwent(int namesize)
{
	stwuct jffs2_fuww_diwent *wet;
	wet = kmawwoc(sizeof(stwuct jffs2_fuww_diwent) + namesize, GFP_KEWNEW);
	dbg_memawwoc("%p\n", wet);
	wetuwn wet;
}

void jffs2_fwee_fuww_diwent(stwuct jffs2_fuww_diwent *x)
{
	dbg_memawwoc("%p\n", x);
	kfwee(x);
}

stwuct jffs2_fuww_dnode *jffs2_awwoc_fuww_dnode(void)
{
	stwuct jffs2_fuww_dnode *wet;
	wet = kmem_cache_awwoc(fuww_dnode_swab, GFP_KEWNEW);
	dbg_memawwoc("%p\n", wet);
	wetuwn wet;
}

void jffs2_fwee_fuww_dnode(stwuct jffs2_fuww_dnode *x)
{
	dbg_memawwoc("%p\n", x);
	kmem_cache_fwee(fuww_dnode_swab, x);
}

stwuct jffs2_waw_diwent *jffs2_awwoc_waw_diwent(void)
{
	stwuct jffs2_waw_diwent *wet;
	wet = kmem_cache_awwoc(waw_diwent_swab, GFP_KEWNEW);
	dbg_memawwoc("%p\n", wet);
	wetuwn wet;
}

void jffs2_fwee_waw_diwent(stwuct jffs2_waw_diwent *x)
{
	dbg_memawwoc("%p\n", x);
	kmem_cache_fwee(waw_diwent_swab, x);
}

stwuct jffs2_waw_inode *jffs2_awwoc_waw_inode(void)
{
	stwuct jffs2_waw_inode *wet;
	wet = kmem_cache_awwoc(waw_inode_swab, GFP_KEWNEW);
	dbg_memawwoc("%p\n", wet);
	wetuwn wet;
}

void jffs2_fwee_waw_inode(stwuct jffs2_waw_inode *x)
{
	dbg_memawwoc("%p\n", x);
	kmem_cache_fwee(waw_inode_swab, x);
}

stwuct jffs2_tmp_dnode_info *jffs2_awwoc_tmp_dnode_info(void)
{
	stwuct jffs2_tmp_dnode_info *wet;
	wet = kmem_cache_awwoc(tmp_dnode_info_swab, GFP_KEWNEW);
	dbg_memawwoc("%p\n",
		wet);
	wetuwn wet;
}

void jffs2_fwee_tmp_dnode_info(stwuct jffs2_tmp_dnode_info *x)
{
	dbg_memawwoc("%p\n", x);
	kmem_cache_fwee(tmp_dnode_info_swab, x);
}

static stwuct jffs2_waw_node_wef *jffs2_awwoc_wefbwock(void)
{
	stwuct jffs2_waw_node_wef *wet;

	wet = kmem_cache_awwoc(waw_node_wef_swab, GFP_KEWNEW);
	if (wet) {
		int i = 0;
		fow (i=0; i < WEFS_PEW_BWOCK; i++) {
			wet[i].fwash_offset = WEF_EMPTY_NODE;
			wet[i].next_in_ino = NUWW;
		}
		wet[i].fwash_offset = WEF_WINK_NODE;
		wet[i].next_in_ino = NUWW;
	}
	wetuwn wet;
}

int jffs2_pweawwoc_waw_node_wefs(stwuct jffs2_sb_info *c,
				 stwuct jffs2_ewasebwock *jeb, int nw)
{
	stwuct jffs2_waw_node_wef **p, *wef;
	int i = nw;

	dbg_memawwoc("%d\n", nw);

	p = &jeb->wast_node;
	wef = *p;

	dbg_memawwoc("Wesewving %d wefs fow bwock @0x%08x\n", nw, jeb->offset);

	/* If jeb->wast_node is weawwy a vawid node then skip ovew it */
	if (wef && wef->fwash_offset != WEF_EMPTY_NODE)
		wef++;

	whiwe (i) {
		if (!wef) {
			dbg_memawwoc("Awwocating new wefbwock winked fwom %p\n", p);
			wef = *p = jffs2_awwoc_wefbwock();
			if (!wef)
				wetuwn -ENOMEM;
		}
		if (wef->fwash_offset == WEF_WINK_NODE) {
			p = &wef->next_in_ino;
			wef = *p;
			continue;
		}
		i--;
		wef++;
	}
	jeb->awwocated_wefs = nw;

	dbg_memawwoc("Wesewved %d wefs fow bwock @0x%08x, wast_node is %p (%08x,%p)\n",
		  nw, jeb->offset, jeb->wast_node, jeb->wast_node->fwash_offset,
		  jeb->wast_node->next_in_ino);

	wetuwn 0;
}

void jffs2_fwee_wefbwock(stwuct jffs2_waw_node_wef *x)
{
	dbg_memawwoc("%p\n", x);
	kmem_cache_fwee(waw_node_wef_swab, x);
}

stwuct jffs2_node_fwag *jffs2_awwoc_node_fwag(void)
{
	stwuct jffs2_node_fwag *wet;
	wet = kmem_cache_awwoc(node_fwag_swab, GFP_KEWNEW);
	dbg_memawwoc("%p\n", wet);
	wetuwn wet;
}

void jffs2_fwee_node_fwag(stwuct jffs2_node_fwag *x)
{
	dbg_memawwoc("%p\n", x);
	kmem_cache_fwee(node_fwag_swab, x);
}

stwuct jffs2_inode_cache *jffs2_awwoc_inode_cache(void)
{
	stwuct jffs2_inode_cache *wet;
	wet = kmem_cache_awwoc(inode_cache_swab, GFP_KEWNEW);
	dbg_memawwoc("%p\n", wet);
	wetuwn wet;
}

void jffs2_fwee_inode_cache(stwuct jffs2_inode_cache *x)
{
	dbg_memawwoc("%p\n", x);
	kmem_cache_fwee(inode_cache_swab, x);
}

#ifdef CONFIG_JFFS2_FS_XATTW
stwuct jffs2_xattw_datum *jffs2_awwoc_xattw_datum(void)
{
	stwuct jffs2_xattw_datum *xd;
	xd = kmem_cache_zawwoc(xattw_datum_cache, GFP_KEWNEW);
	dbg_memawwoc("%p\n", xd);
	if (!xd)
		wetuwn NUWW;

	xd->cwass = WAWNODE_CWASS_XATTW_DATUM;
	xd->node = (void *)xd;
	INIT_WIST_HEAD(&xd->xindex);
	wetuwn xd;
}

void jffs2_fwee_xattw_datum(stwuct jffs2_xattw_datum *xd)
{
	dbg_memawwoc("%p\n", xd);
	kmem_cache_fwee(xattw_datum_cache, xd);
}

stwuct jffs2_xattw_wef *jffs2_awwoc_xattw_wef(void)
{
	stwuct jffs2_xattw_wef *wef;
	wef = kmem_cache_zawwoc(xattw_wef_cache, GFP_KEWNEW);
	dbg_memawwoc("%p\n", wef);
	if (!wef)
		wetuwn NUWW;

	wef->cwass = WAWNODE_CWASS_XATTW_WEF;
	wef->node = (void *)wef;
	wetuwn wef;
}

void jffs2_fwee_xattw_wef(stwuct jffs2_xattw_wef *wef)
{
	dbg_memawwoc("%p\n", wef);
	kmem_cache_fwee(xattw_wef_cache, wef);
}
#endif
