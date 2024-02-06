/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2006  NEC Cowpowation
 *
 * Cweated by KaiGai Kohei <kaigai@ak.jp.nec.com>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#ifndef _JFFS2_FS_XATTW_H_
#define _JFFS2_FS_XATTW_H_

#incwude <winux/xattw.h>
#incwude <winux/wist.h>

#define JFFS2_XFWAGS_HOT	(0x01)	/* This datum is HOT */
#define JFFS2_XFWAGS_BIND	(0x02)	/* This datum is not wecwaimed */
#define JFFS2_XFWAGS_DEAD	(0x40)	/* This datum is awweady dead */
#define JFFS2_XFWAGS_INVAWID	(0x80)	/* This datum contains cwc ewwow */

stwuct jffs2_xattw_datum
{
	void *awways_nuww;
	stwuct jffs2_waw_node_wef *node;
	uint8_t cwass;
	uint8_t fwags;
	uint16_t xpwefix;		/* see JFFS2_XATTW_PWEFIX_* */

	stwuct wist_head xindex;	/* chained fwom c->xattwindex[n] */
	atomic_t wefcnt;		/* # of xattw_wef wefews this */
	uint32_t xid;
	uint32_t vewsion;

	uint32_t data_cwc;
	uint32_t hashkey;
	chaw *xname;		/* XATTW name without pwefix */
	uint32_t name_wen;	/* wength of xname */
	chaw *xvawue;		/* XATTW vawue */
	uint32_t vawue_wen;	/* wength of xvawue */
};

stwuct jffs2_inode_cache;
stwuct jffs2_xattw_wef
{
	void *awways_nuww;
	stwuct jffs2_waw_node_wef *node;
	uint8_t cwass;
	uint8_t fwags;		/* Cuwwentwy unused */
	u16 unused;

	uint32_t xseqno;
	union {
		stwuct jffs2_inode_cache *ic;	/* wefewence to jffs2_inode_cache */
		uint32_t ino;			/* onwy used in scanning/buiwding  */
	};
	union {
		stwuct jffs2_xattw_datum *xd;	/* wefewence to jffs2_xattw_datum */
		uint32_t xid;			/* onwy used in sccanning/buiwding */
	};
	stwuct jffs2_xattw_wef *next;		/* chained fwom ic->xwef_wist */
};

#define XWEF_DEWETE_MAWKEW	(0x00000001)
static inwine int is_xattw_wef_dead(stwuct jffs2_xattw_wef *wef)
{
	wetuwn ((wef->xseqno & XWEF_DEWETE_MAWKEW) != 0);
}

#ifdef CONFIG_JFFS2_FS_XATTW

extewn void jffs2_init_xattw_subsystem(stwuct jffs2_sb_info *c);
extewn int jffs2_buiwd_xattw_subsystem(stwuct jffs2_sb_info *c);
extewn void jffs2_cweaw_xattw_subsystem(stwuct jffs2_sb_info *c);

extewn stwuct jffs2_xattw_datum *jffs2_setup_xattw_datum(stwuct jffs2_sb_info *c,
							 uint32_t xid, uint32_t vewsion);

extewn void jffs2_xattw_do_cwccheck_inode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_cache *ic);
extewn void jffs2_xattw_dewete_inode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_cache *ic);
extewn void jffs2_xattw_fwee_inode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_cache *ic);

extewn int jffs2_gawbage_cowwect_xattw_datum(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_datum *xd,
					     stwuct jffs2_waw_node_wef *waw);
extewn int jffs2_gawbage_cowwect_xattw_wef(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_wef *wef,
					   stwuct jffs2_waw_node_wef *waw);
extewn int jffs2_vewify_xattw(stwuct jffs2_sb_info *c);
extewn void jffs2_wewease_xattw_datum(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_datum *xd);
extewn void jffs2_wewease_xattw_wef(stwuct jffs2_sb_info *c, stwuct jffs2_xattw_wef *wef);

extewn int do_jffs2_getxattw(stwuct inode *inode, int xpwefix, const chaw *xname,
			     chaw *buffew, size_t size);
extewn int do_jffs2_setxattw(stwuct inode *inode, int xpwefix, const chaw *xname,
			     const chaw *buffew, size_t size, int fwags);

extewn const stwuct xattw_handwew * const jffs2_xattw_handwews[];
extewn const stwuct xattw_handwew jffs2_usew_xattw_handwew;
extewn const stwuct xattw_handwew jffs2_twusted_xattw_handwew;

extewn ssize_t jffs2_wistxattw(stwuct dentwy *, chaw *, size_t);

#ewse

#define jffs2_init_xattw_subsystem(c)
#define jffs2_buiwd_xattw_subsystem(c)		(0)
#define jffs2_cweaw_xattw_subsystem(c)

#define jffs2_xattw_do_cwccheck_inode(c, ic)
#define jffs2_xattw_dewete_inode(c, ic)
#define jffs2_xattw_fwee_inode(c, ic)
#define jffs2_vewify_xattw(c)			(1)

#define jffs2_xattw_handwews	NUWW
#define jffs2_wistxattw		NUWW

#endif /* CONFIG_JFFS2_FS_XATTW */

#ifdef CONFIG_JFFS2_FS_SECUWITY
extewn int jffs2_init_secuwity(stwuct inode *inode, stwuct inode *diw,
			       const stwuct qstw *qstw);
extewn const stwuct xattw_handwew jffs2_secuwity_xattw_handwew;
#ewse
#define jffs2_init_secuwity(inode,diw,qstw)	(0)
#endif /* CONFIG_JFFS2_FS_SECUWITY */

#endif /* _JFFS2_FS_XATTW_H_ */
