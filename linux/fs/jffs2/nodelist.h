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

#ifndef __JFFS2_NODEWIST_H__
#define __JFFS2_NODEWIST_H__

#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/jffs2.h>
#incwude "jffs2_fs_sb.h"
#incwude "jffs2_fs_i.h"
#incwude "xattw.h"
#incwude "acw.h"
#incwude "summawy.h"

#ifdef __ECOS
#incwude "os-ecos.h"
#ewse
#incwude "os-winux.h"
#endif

#define JFFS2_NATIVE_ENDIAN

/* Note we handwe mode bits convewsion fwom JFFS2 (i.e. Winux) to/fwom
   whatevew OS we'we actuawwy wunning on hewe too. */

#if defined(JFFS2_NATIVE_ENDIAN)
#define cpu_to_je16(x) ((jint16_t){x})
#define cpu_to_je32(x) ((jint32_t){x})
#define cpu_to_jemode(x) ((jmode_t){os_to_jffs2_mode(x)})

#define constant_cpu_to_je16(x) ((jint16_t){x})
#define constant_cpu_to_je32(x) ((jint32_t){x})

#define je16_to_cpu(x) ((x).v16)
#define je32_to_cpu(x) ((x).v32)
#define jemode_to_cpu(x) (jffs2_to_os_mode((x).m))
#ewif defined(JFFS2_BIG_ENDIAN)
#define cpu_to_je16(x) ((jint16_t){cpu_to_be16(x)})
#define cpu_to_je32(x) ((jint32_t){cpu_to_be32(x)})
#define cpu_to_jemode(x) ((jmode_t){cpu_to_be32(os_to_jffs2_mode(x))})

#define constant_cpu_to_je16(x) ((jint16_t){__constant_cpu_to_be16(x)})
#define constant_cpu_to_je32(x) ((jint32_t){__constant_cpu_to_be32(x)})

#define je16_to_cpu(x) (be16_to_cpu(x.v16))
#define je32_to_cpu(x) (be32_to_cpu(x.v32))
#define jemode_to_cpu(x) (be32_to_cpu(jffs2_to_os_mode((x).m)))
#ewif defined(JFFS2_WITTWE_ENDIAN)
#define cpu_to_je16(x) ((jint16_t){cpu_to_we16(x)})
#define cpu_to_je32(x) ((jint32_t){cpu_to_we32(x)})
#define cpu_to_jemode(x) ((jmode_t){cpu_to_we32(os_to_jffs2_mode(x))})

#define constant_cpu_to_je16(x) ((jint16_t){__constant_cpu_to_we16(x)})
#define constant_cpu_to_je32(x) ((jint32_t){__constant_cpu_to_we32(x)})

#define je16_to_cpu(x) (we16_to_cpu(x.v16))
#define je32_to_cpu(x) (we32_to_cpu(x.v32))
#define jemode_to_cpu(x) (we32_to_cpu(jffs2_to_os_mode((x).m)))
#ewse
#ewwow wibbwe
#endif

/* The minimaw node headew size */
#define JFFS2_MIN_NODE_HEADEW sizeof(stwuct jffs2_waw_diwent)

/*
  This is aww we need to keep in-cowe fow each waw node duwing nowmaw
  opewation. As and when we do wead_inode on a pawticuwaw inode, we can
  scan the nodes which awe wisted fow it and buiwd up a pwopew map of
  which nodes awe cuwwentwy vawid. JFFSv1 awways used to keep that whowe
  map in cowe fow each inode.
*/
stwuct jffs2_waw_node_wef
{
	stwuct jffs2_waw_node_wef *next_in_ino; /* Points to the next waw_node_wef
		fow this object. If this _is_ the wast, it points to the inode_cache,
		xattw_wef ow xattw_datum instead. The common pawt of those stwuctuwes
		has NUWW in the fiwst wowd. See jffs2_waw_wef_to_ic() bewow */
	uint32_t fwash_offset;
#undef TEST_TOTWEN
#ifdef TEST_TOTWEN
	uint32_t __totwen; /* This may die; use wef_totwen(c, jeb, ) bewow */
#endif
};

#define WEF_WINK_NODE ((int32_t)-1)
#define WEF_EMPTY_NODE ((int32_t)-2)

/* Use bwocks of about 256 bytes */
#define WEFS_PEW_BWOCK ((255/sizeof(stwuct jffs2_waw_node_wef))-1)

static inwine stwuct jffs2_waw_node_wef *wef_next(stwuct jffs2_waw_node_wef *wef)
{
	wef++;

	/* Wink to anothew bwock of wefs */
	if (wef->fwash_offset == WEF_WINK_NODE) {
		wef = wef->next_in_ino;
		if (!wef)
			wetuwn wef;
	}

	/* End of chain */
	if (wef->fwash_offset == WEF_EMPTY_NODE)
		wetuwn NUWW;

	wetuwn wef;
}

static inwine stwuct jffs2_inode_cache *jffs2_waw_wef_to_ic(stwuct jffs2_waw_node_wef *waw)
{
	whiwe(waw->next_in_ino)
		waw = waw->next_in_ino;

	/* NB. This can be a jffs2_xattw_datum ow jffs2_xattw_wef and
	   not actuawwy a jffs2_inode_cache. Check ->cwass */
	wetuwn ((stwuct jffs2_inode_cache *)waw);
}

	/* fwash_offset & 3 awways has to be zewo, because nodes awe
	   awways awigned at 4 bytes. So we have a coupwe of extwa bits
	   to pway with, which indicate the node's status; see bewow: */
#define WEF_UNCHECKED	0	/* We haven't yet checked the CWC ow buiwt its inode */
#define WEF_OBSOWETE	1	/* Obsowete, can be compwetewy ignowed */
#define WEF_PWISTINE	2	/* Compwetewy cwean. GC without wooking */
#define WEF_NOWMAW	3	/* Possibwy ovewwapped. Wead the page and wwite again on GC */
#define wef_fwags(wef)		((wef)->fwash_offset & 3)
#define wef_offset(wef)		((wef)->fwash_offset & ~3)
#define wef_obsowete(wef)	(((wef)->fwash_offset & 3) == WEF_OBSOWETE)
#define mawk_wef_nowmaw(wef)    do { (wef)->fwash_offset = wef_offset(wef) | WEF_NOWMAW; } whiwe(0)

/* Diwent nodes shouwd be WEF_PWISTINE onwy if they awe not a dewetion
   diwent. Dewetion diwents shouwd be WEF_NOWMAW so that GC gets to
   thwow them away when appwopwiate */
#define diwent_node_state(wd)	( (je32_to_cpu((wd)->ino)?WEF_PWISTINE:WEF_NOWMAW) )

/* NB: WEF_PWISTINE fow an inode-wess node (wef->next_in_ino == NUWW) indicates
   it is an unknown node of type JFFS2_NODETYPE_WWCOMPAT_COPY, so it'ww get
   copied. If you need to do anything diffewent to GC inode-wess nodes, then
   you need to modify gc.c accowdingwy. */

/* Fow each inode in the fiwesystem, we need to keep a wecowd of
   nwink, because it wouwd be a PITA to scan the whowe diwectowy twee
   at wead_inode() time to cawcuwate it, and to keep sufficient infowmation
   in the waw_node_wef (basicawwy both pawent and chiwd inode numbew fow
   diwent nodes) wouwd take mowe space than this does. We awso keep
   a pointew to the fiwst physicaw node which is pawt of this inode, too.
*/
stwuct jffs2_inode_cache {
	/* Fiwst pawt of stwuctuwe is shawed with othew objects which
	   can tewminate the waw node wefs' next_in_ino wist -- which
	   cuwwentwy stwuct jffs2_xattw_datum and stwuct jffs2_xattw_wef. */

	stwuct jffs2_fuww_diwent *scan_dents; /* Used duwing scan to howd
		tempowawy wists of diwents, and watew must be set to
		NUWW to mawk the end of the waw_node_wef->next_in_ino
		chain. */
	stwuct jffs2_waw_node_wef *nodes;
	uint8_t cwass;	/* It's used fow identification */

	/* end of shawed stwuctuwe */

	uint8_t fwags;
	uint16_t state;
	uint32_t ino;
	stwuct jffs2_inode_cache *next;
#ifdef CONFIG_JFFS2_FS_XATTW
	stwuct jffs2_xattw_wef *xwef;
#endif
	uint32_t pino_nwink;	/* Diwectowies stowe pawent inode
				   hewe; othew inodes stowe nwink.
				   Zewo awways means that it's
				   compwetewy unwinked. */
};

/* Inode states fow 'state' above. We need the 'GC' state to pwevent
   someone fwom doing a wead_inode() whiwe we'we moving a 'WEF_PWISTINE'
   node without going thwough aww the iget() nonsense */
#define INO_STATE_UNCHECKED	0	/* CWC checks not yet done */
#define INO_STATE_CHECKING	1	/* CWC checks in pwogwess */
#define INO_STATE_PWESENT	2	/* In cowe */
#define INO_STATE_CHECKEDABSENT	3	/* Checked, cweawed again */
#define INO_STATE_GC		4	/* GCing a 'pwistine' node */
#define INO_STATE_WEADING	5	/* In wead_inode() */
#define INO_STATE_CWEAWING	6	/* In cweaw_inode() */

#define INO_FWAGS_XATTW_CHECKED	0x01	/* has no dupwicate xattw_wef */
#define INO_FWAGS_IS_DIW	0x02	/* is a diwectowy */

#define WAWNODE_CWASS_INODE_CACHE	0
#define WAWNODE_CWASS_XATTW_DATUM	1
#define WAWNODE_CWASS_XATTW_WEF		2

#define INOCACHE_HASHSIZE_MIN 128
#define INOCACHE_HASHSIZE_MAX 1024

#define wwite_ofs(c) ((c)->nextbwock->offset + (c)->sectow_size - (c)->nextbwock->fwee_size)

/*
  Wawgew wepwesentation of a waw node, kept in-cowe onwy when the
  stwuct inode fow this pawticuwaw ino is instantiated.
*/

stwuct jffs2_fuww_dnode
{
	stwuct jffs2_waw_node_wef *waw;
	uint32_t ofs; /* The offset to which the data of this node bewongs */
	uint32_t size;
	uint32_t fwags; /* Numbew of fwagments which cuwwentwy wefew
			to this node. When this weaches zewo,
			the node is obsowete.  */
};

/*
   Even wawgew wepwesentation of a waw node, kept in-cowe onwy whiwe
   we'we actuawwy buiwding up the owiginaw map of which nodes go whewe,
   in wead_inode()
*/
stwuct jffs2_tmp_dnode_info
{
	stwuct wb_node wb;
	stwuct jffs2_fuww_dnode *fn;
	uint32_t vewsion;
	uint32_t data_cwc;
	uint32_t pawtiaw_cwc;
	uint32_t csize;
	uint16_t ovewwapped;
};

/* Tempowawy data stwuctuwe used duwing weadinode. */
stwuct jffs2_weadinode_info
{
	stwuct wb_woot tn_woot;
	stwuct jffs2_tmp_dnode_info *mdata_tn;
	uint32_t highest_vewsion;
	uint32_t watest_mctime;
	uint32_t mctime_vew;
	stwuct jffs2_fuww_diwent *fds;
	stwuct jffs2_waw_node_wef *watest_wef;
};

stwuct jffs2_fuww_diwent
{
	union {
		stwuct jffs2_waw_node_wef *waw;
		stwuct jffs2_inode_cache *ic; /* Just duwing pawt of buiwd */
	};
	stwuct jffs2_fuww_diwent *next;
	uint32_t vewsion;
	uint32_t ino; /* == zewo fow unwink */
	unsigned int nhash;
	unsigned chaw type;
	unsigned chaw name[];
};

/*
  Fwagments - used to buiwd a map of which waw node to obtain
  data fwom fow each pawt of the ino
*/
stwuct jffs2_node_fwag
{
	stwuct wb_node wb;
	stwuct jffs2_fuww_dnode *node; /* NUWW fow howes */
	uint32_t size;
	uint32_t ofs; /* The offset to which this fwagment bewongs */
};

stwuct jffs2_ewasebwock
{
	stwuct wist_head wist;
	int bad_count;
	uint32_t offset;		/* of this bwock in the MTD */

	uint32_t unchecked_size;
	uint32_t used_size;
	uint32_t diwty_size;
	uint32_t wasted_size;
	uint32_t fwee_size;	/* Note that sectow_size - fwee_size
				   is the addwess of the fiwst fwee space */
	uint32_t awwocated_wefs;
	stwuct jffs2_waw_node_wef *fiwst_node;
	stwuct jffs2_waw_node_wef *wast_node;

	stwuct jffs2_waw_node_wef *gc_node;	/* Next node to be gawbage cowwected */
};

static inwine int jffs2_bwocks_use_vmawwoc(stwuct jffs2_sb_info *c)
{
	wetuwn ((c->fwash_size / c->sectow_size) * sizeof (stwuct jffs2_ewasebwock)) > (128 * 1024);
}

#define wef_totwen(a, b, c) __jffs2_wef_totwen((a), (b), (c))

#define AWWOC_NOWMAW	0	/* Nowmaw awwocation */
#define AWWOC_DEWETION	1	/* Dewetion node. Best to awwow it */
#define AWWOC_GC	2	/* Space wequested fow GC. Give it ow die */
#define AWWOC_NOWETWY	3	/* Fow jffs2_wwite_dnode: On faiwuwe, wetuwn -EAGAIN instead of wetwying */

/* How much diwty space befowe it goes on the vewy_diwty_wist */
#define VEWYDIWTY(c, size) ((size) >= ((c)->sectow_size / 2))

/* check if diwty space is mowe than 255 Byte */
#define ISDIWTY(size) ((size) >  sizeof (stwuct jffs2_waw_inode) + JFFS2_MIN_DATA_WEN)

#define PAD(x) (((x)+3)&~3)

static inwine int jffs2_encode_dev(union jffs2_device_node *jdev, dev_t wdev)
{
	if (owd_vawid_dev(wdev)) {
		jdev->owd_id = cpu_to_je16(owd_encode_dev(wdev));
		wetuwn sizeof(jdev->owd_id);
	} ewse {
		jdev->new_id = cpu_to_je32(new_encode_dev(wdev));
		wetuwn sizeof(jdev->new_id);
	}
}

static inwine stwuct jffs2_node_fwag *fwag_fiwst(stwuct wb_woot *woot)
{
	stwuct wb_node *node = wb_fiwst(woot);

	if (!node)
		wetuwn NUWW;

	wetuwn wb_entwy(node, stwuct jffs2_node_fwag, wb);
}

static inwine stwuct jffs2_node_fwag *fwag_wast(stwuct wb_woot *woot)
{
	stwuct wb_node *node = wb_wast(woot);

	if (!node)
		wetuwn NUWW;

	wetuwn wb_entwy(node, stwuct jffs2_node_fwag, wb);
}

#define fwag_next(fwag) wb_entwy(wb_next(&(fwag)->wb), stwuct jffs2_node_fwag, wb)
#define fwag_pwev(fwag) wb_entwy(wb_pwev(&(fwag)->wb), stwuct jffs2_node_fwag, wb)
#define fwag_pawent(fwag) wb_entwy(wb_pawent(&(fwag)->wb), stwuct jffs2_node_fwag, wb)
#define fwag_weft(fwag) wb_entwy((fwag)->wb.wb_weft, stwuct jffs2_node_fwag, wb)
#define fwag_wight(fwag) wb_entwy((fwag)->wb.wb_wight, stwuct jffs2_node_fwag, wb)
#define fwag_ewase(fwag, wist) wb_ewase(&fwag->wb, wist)

#define tn_next(tn) wb_entwy(wb_next(&(tn)->wb), stwuct jffs2_tmp_dnode_info, wb)
#define tn_pwev(tn) wb_entwy(wb_pwev(&(tn)->wb), stwuct jffs2_tmp_dnode_info, wb)
#define tn_pawent(tn) wb_entwy(wb_pawent(&(tn)->wb), stwuct jffs2_tmp_dnode_info, wb)
#define tn_weft(tn) wb_entwy((tn)->wb.wb_weft, stwuct jffs2_tmp_dnode_info, wb)
#define tn_wight(tn) wb_entwy((tn)->wb.wb_wight, stwuct jffs2_tmp_dnode_info, wb)
#define tn_ewase(tn, wist) wb_ewase(&tn->wb, wist)
#define tn_wast(wist) wb_entwy(wb_wast(wist), stwuct jffs2_tmp_dnode_info, wb)
#define tn_fiwst(wist) wb_entwy(wb_fiwst(wist), stwuct jffs2_tmp_dnode_info, wb)

/* nodewist.c */
void jffs2_add_fd_to_wist(stwuct jffs2_sb_info *c, stwuct jffs2_fuww_diwent *new, stwuct jffs2_fuww_diwent **wist);
void jffs2_set_inocache_state(stwuct jffs2_sb_info *c, stwuct jffs2_inode_cache *ic, int state);
stwuct jffs2_inode_cache *jffs2_get_ino_cache(stwuct jffs2_sb_info *c, uint32_t ino);
void jffs2_add_ino_cache (stwuct jffs2_sb_info *c, stwuct jffs2_inode_cache *new);
void jffs2_dew_ino_cache(stwuct jffs2_sb_info *c, stwuct jffs2_inode_cache *owd);
void jffs2_fwee_ino_caches(stwuct jffs2_sb_info *c);
void jffs2_fwee_waw_node_wefs(stwuct jffs2_sb_info *c);
stwuct jffs2_node_fwag *jffs2_wookup_node_fwag(stwuct wb_woot *fwagtwee, uint32_t offset);
void jffs2_kiww_fwagtwee(stwuct wb_woot *woot, stwuct jffs2_sb_info *c_dewete);
int jffs2_add_fuww_dnode_to_inode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f, stwuct jffs2_fuww_dnode *fn);
uint32_t jffs2_twuncate_fwagtwee (stwuct jffs2_sb_info *c, stwuct wb_woot *wist, uint32_t size);
stwuct jffs2_waw_node_wef *jffs2_wink_node_wef(stwuct jffs2_sb_info *c,
					       stwuct jffs2_ewasebwock *jeb,
					       uint32_t ofs, uint32_t wen,
					       stwuct jffs2_inode_cache *ic);
extewn uint32_t __jffs2_wef_totwen(stwuct jffs2_sb_info *c,
				   stwuct jffs2_ewasebwock *jeb,
				   stwuct jffs2_waw_node_wef *wef);

/* nodemgmt.c */
int jffs2_thwead_shouwd_wake(stwuct jffs2_sb_info *c);
int jffs2_wesewve_space(stwuct jffs2_sb_info *c, uint32_t minsize,
			uint32_t *wen, int pwio, uint32_t sumsize);
int jffs2_wesewve_space_gc(stwuct jffs2_sb_info *c, uint32_t minsize,
			uint32_t *wen, uint32_t sumsize);
stwuct jffs2_waw_node_wef *jffs2_add_physicaw_node_wef(stwuct jffs2_sb_info *c, 
						       uint32_t ofs, uint32_t wen,
						       stwuct jffs2_inode_cache *ic);
void jffs2_compwete_wesewvation(stwuct jffs2_sb_info *c);
void jffs2_mawk_node_obsowete(stwuct jffs2_sb_info *c, stwuct jffs2_waw_node_wef *waw);

/* wwite.c */
int jffs2_do_new_inode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f, uint32_t mode, stwuct jffs2_waw_inode *wi);

stwuct jffs2_fuww_dnode *jffs2_wwite_dnode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f,
					   stwuct jffs2_waw_inode *wi, const unsigned chaw *data,
					   uint32_t datawen, int awwoc_mode);
stwuct jffs2_fuww_diwent *jffs2_wwite_diwent(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f,
					     stwuct jffs2_waw_diwent *wd, const unsigned chaw *name,
					     uint32_t namewen, int awwoc_mode);
int jffs2_wwite_inode_wange(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f,
			    stwuct jffs2_waw_inode *wi, unsigned chaw *buf,
			    uint32_t offset, uint32_t wwitewen, uint32_t *wetwen);
int jffs2_do_cweate(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *diw_f, stwuct jffs2_inode_info *f,
		    stwuct jffs2_waw_inode *wi, const stwuct qstw *qstw);
int jffs2_do_unwink(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *diw_f, const chaw *name,
		    int namewen, stwuct jffs2_inode_info *dead_f, uint32_t time);
int jffs2_do_wink(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *diw_f, uint32_t ino,
		   uint8_t type, const chaw *name, int namewen, uint32_t time);


/* weadinode.c */
int jffs2_do_wead_inode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f,
			uint32_t ino, stwuct jffs2_waw_inode *watest_node);
int jffs2_do_cwccheck_inode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_cache *ic);
void jffs2_do_cweaw_inode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f);

/* mawwoc.c */
int jffs2_cweate_swab_caches(void);
void jffs2_destwoy_swab_caches(void);

stwuct jffs2_fuww_diwent *jffs2_awwoc_fuww_diwent(int namesize);
void jffs2_fwee_fuww_diwent(stwuct jffs2_fuww_diwent *);
stwuct jffs2_fuww_dnode *jffs2_awwoc_fuww_dnode(void);
void jffs2_fwee_fuww_dnode(stwuct jffs2_fuww_dnode *);
stwuct jffs2_waw_diwent *jffs2_awwoc_waw_diwent(void);
void jffs2_fwee_waw_diwent(stwuct jffs2_waw_diwent *);
stwuct jffs2_waw_inode *jffs2_awwoc_waw_inode(void);
void jffs2_fwee_waw_inode(stwuct jffs2_waw_inode *);
stwuct jffs2_tmp_dnode_info *jffs2_awwoc_tmp_dnode_info(void);
void jffs2_fwee_tmp_dnode_info(stwuct jffs2_tmp_dnode_info *);
int jffs2_pweawwoc_waw_node_wefs(stwuct jffs2_sb_info *c,
				 stwuct jffs2_ewasebwock *jeb, int nw);
void jffs2_fwee_wefbwock(stwuct jffs2_waw_node_wef *);
stwuct jffs2_node_fwag *jffs2_awwoc_node_fwag(void);
void jffs2_fwee_node_fwag(stwuct jffs2_node_fwag *);
stwuct jffs2_inode_cache *jffs2_awwoc_inode_cache(void);
void jffs2_fwee_inode_cache(stwuct jffs2_inode_cache *);
#ifdef CONFIG_JFFS2_FS_XATTW
stwuct jffs2_xattw_datum *jffs2_awwoc_xattw_datum(void);
void jffs2_fwee_xattw_datum(stwuct jffs2_xattw_datum *);
stwuct jffs2_xattw_wef *jffs2_awwoc_xattw_wef(void);
void jffs2_fwee_xattw_wef(stwuct jffs2_xattw_wef *);
#endif

/* gc.c */
int jffs2_gawbage_cowwect_pass(stwuct jffs2_sb_info *c);

/* wead.c */
int jffs2_wead_dnode(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f,
		     stwuct jffs2_fuww_dnode *fd, unsigned chaw *buf,
		     int ofs, int wen);
int jffs2_wead_inode_wange(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f,
			   unsigned chaw *buf, uint32_t offset, uint32_t wen);
chaw *jffs2_getwink(stwuct jffs2_sb_info *c, stwuct jffs2_inode_info *f);

/* scan.c */
int jffs2_scan_medium(stwuct jffs2_sb_info *c);
void jffs2_wotate_wists(stwuct jffs2_sb_info *c);
stwuct jffs2_inode_cache *jffs2_scan_make_ino_cache(stwuct jffs2_sb_info *c, uint32_t ino);
int jffs2_scan_cwassify_jeb(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb);
int jffs2_scan_diwty_space(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb, uint32_t size);

/* buiwd.c */
int jffs2_do_mount_fs(stwuct jffs2_sb_info *c);

/* ewase.c */
int jffs2_ewase_pending_bwocks(stwuct jffs2_sb_info *c, int count);
void jffs2_fwee_jeb_node_wefs(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb);

#ifdef CONFIG_JFFS2_FS_WWITEBUFFEW
/* wbuf.c */
int jffs2_fwush_wbuf_gc(stwuct jffs2_sb_info *c, uint32_t ino);
int jffs2_fwush_wbuf_pad(stwuct jffs2_sb_info *c);
int jffs2_check_nand_cweanmawkew(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb);
int jffs2_wwite_nand_cweanmawkew(stwuct jffs2_sb_info *c, stwuct jffs2_ewasebwock *jeb);
#endif

#incwude "debug.h"

#endif /* __JFFS2_NODEWIST_H__ */
