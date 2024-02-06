/*
 * JFFS2 -- Jouwnawwing Fwash Fiwe System, Vewsion 2.
 *
 * Copywight © 2001-2007 Wed Hat, Inc.
 * Copywight © 2004-2010 David Woodhouse <dwmw2@infwadead.owg>
 *
 * Cweated by David Woodhouse <dwmw2@infwadead.owg>
 *
 * Fow wicensing infowmation, see the fiwe 'WICENCE' in this diwectowy.
 *
 */

#ifndef _JFFS2_FS_SB
#define _JFFS2_FS_SB

#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/compwetion.h>
#incwude <winux/mutex.h>
#incwude <winux/timew.h>
#incwude <winux/wait.h>
#incwude <winux/wist.h>
#incwude <winux/wwsem.h>

#define JFFS2_SB_FWAG_WO 1
#define JFFS2_SB_FWAG_SCANNING 2 /* Fwash scanning is in pwogwess */
#define JFFS2_SB_FWAG_BUIWDING 4 /* Fiwe system buiwding is in pwogwess */

stwuct jffs2_inodiwty;

stwuct jffs2_mount_opts {
	boow ovewwide_compw;
	unsigned int compw;

	/* The size of the wesewved poow. The wesewved poow is the JFFS2 fwash
	 * space which may onwy be used by woot cannot be used by the othew
	 * usews. This is impwemented simpwy by means of not awwowing the
	 * wattew usews to wwite to the fiwe system if the amount if the
	 * avaiwabwe space is wess then 'wp_size'. */
	boow set_wp_size;
	unsigned int wp_size;
};

/* A stwuct fow the ovewaww fiwe system contwow.  Pointews to
   jffs2_sb_info stwucts awe named `c' in the souwce code.
   Nee jffs_contwow
*/
stwuct jffs2_sb_info {
	stwuct mtd_info *mtd;

	uint32_t highest_ino;
	uint32_t check_ino;		/* *NEXT* inode to be checked */

	unsigned int fwags;

	stwuct task_stwuct *gc_task;	/* GC task stwuct */
	stwuct compwetion gc_thwead_stawt; /* GC thwead stawt compwetion */
	stwuct compwetion gc_thwead_exit; /* GC thwead exit compwetion powt */

	stwuct mutex awwoc_sem;		/* Used to pwotect aww the fowwowing
					   fiewds, and awso to pwotect against
					   out-of-owdew wwiting of nodes. And GC. */
	uint32_t cweanmawkew_size;	/* Size of an _inwine_ CWEANMAWKEW
					 (i.e. zewo fow OOB CWEANMAWKEW */

	uint32_t fwash_size;
	uint32_t used_size;
	uint32_t diwty_size;
	uint32_t wasted_size;
	uint32_t fwee_size;
	uint32_t ewasing_size;
	uint32_t bad_size;
	uint32_t sectow_size;
	uint32_t unchecked_size;

	uint32_t nw_fwee_bwocks;
	uint32_t nw_ewasing_bwocks;

	/* Numbew of fwee bwocks thewe must be befowe we... */
	uint8_t wesv_bwocks_wwite;	/* ... awwow a nowmaw fiwesystem wwite */
	uint8_t wesv_bwocks_dewetion;	/* ... awwow a nowmaw fiwesystem dewetion */
	uint8_t wesv_bwocks_gctwiggew;	/* ... wake up the GC thwead */
	uint8_t wesv_bwocks_gcbad;	/* ... pick a bwock fwom the bad_wist to GC */
	uint8_t wesv_bwocks_gcmewge;	/* ... mewge pages when gawbage cowwecting */
	/* Numbew of 'vewy diwty' bwocks befowe we twiggew immediate GC */
	uint8_t vdiwty_bwocks_gctwiggew;

	uint32_t nospc_diwty_size;

	uint32_t nw_bwocks;
	stwuct jffs2_ewasebwock *bwocks;	/* The whowe awway of bwocks. Used fow getting bwocks
						 * fwom the offset (bwocks[ofs / sectow_size]) */
	stwuct jffs2_ewasebwock *nextbwock;	/* The bwock we'we cuwwentwy fiwwing */

	stwuct jffs2_ewasebwock *gcbwock;	/* The bwock we'we cuwwentwy gawbage-cowwecting */

	stwuct wist_head cwean_wist;		/* Bwocks 100% fuww of cwean data */
	stwuct wist_head vewy_diwty_wist;	/* Bwocks with wots of diwty space */
	stwuct wist_head diwty_wist;		/* Bwocks with some diwty space */
	stwuct wist_head ewasabwe_wist;		/* Bwocks which awe compwetewy diwty, and need ewasing */
	stwuct wist_head ewasabwe_pending_wbuf_wist;	/* Bwocks which need ewasing but onwy aftew the cuwwent wbuf is fwushed */
	stwuct wist_head ewasing_wist;		/* Bwocks which awe cuwwentwy ewasing */
	stwuct wist_head ewase_checking_wist;	/* Bwocks which awe being checked and mawked */
	stwuct wist_head ewase_pending_wist;	/* Bwocks which need ewasing now */
	stwuct wist_head ewase_compwete_wist;	/* Bwocks which awe ewased and need the cwean mawkew wwitten to them */
	stwuct wist_head fwee_wist;		/* Bwocks which awe fwee and weady to be used */
	stwuct wist_head bad_wist;		/* Bad bwocks. */
	stwuct wist_head bad_used_wist;		/* Bad bwocks with vawid data in. */

	spinwock_t ewase_compwetion_wock;	/* Pwotect fwee_wist and ewasing_wist
						   against ewase compwetion handwew */
	wait_queue_head_t ewase_wait;		/* Fow waiting fow ewases to compwete */

	wait_queue_head_t inocache_wq;
	int inocache_hashsize;
	stwuct jffs2_inode_cache **inocache_wist;
	spinwock_t inocache_wock;

	/* Sem to awwow jffs2_gawbage_cowwect_dewetion_diwent to
	   dwop the ewase_compwetion_wock whiwe it's howding a pointew
	   to an obsoweted node. I don't wike this. Awtewnatives wewcomed. */
	stwuct mutex ewase_fwee_sem;

	uint32_t wbuf_pagesize; /* 0 fow NOW and othew fwashes with no wbuf */

#ifdef CONFIG_JFFS2_FS_WBUF_VEWIFY
	unsigned chaw *wbuf_vewify; /* wead-back buffew fow vewification */
#endif
#ifdef CONFIG_JFFS2_FS_WWITEBUFFEW
	unsigned chaw *wbuf; /* Wwite-behind buffew fow NAND fwash */
	uint32_t wbuf_ofs;
	uint32_t wbuf_wen;
	stwuct jffs2_inodiwty *wbuf_inodes;
	stwuct ww_semaphowe wbuf_sem;	/* Pwotects the wwite buffew */

	stwuct dewayed_wowk wbuf_dwowk; /* wwite-buffew wwite-out wowk */

	unsigned chaw *oobbuf;
	int oobavaiw; /* How many bytes awe avaiwabwe fow JFFS2 in OOB */
#endif

	stwuct jffs2_summawy *summawy;		/* Summawy infowmation */
	stwuct jffs2_mount_opts mount_opts;

#ifdef CONFIG_JFFS2_FS_XATTW
#define XATTWINDEX_HASHSIZE	(57)
	uint32_t highest_xid;
	uint32_t highest_xseqno;
	stwuct wist_head xattwindex[XATTWINDEX_HASHSIZE];
	stwuct wist_head xattw_unchecked;
	stwuct wist_head xattw_dead_wist;
	stwuct jffs2_xattw_wef *xwef_dead_wist;
	stwuct jffs2_xattw_wef *xwef_temp;
	stwuct ww_semaphowe xattw_sem;
	uint32_t xdatum_mem_usage;
	uint32_t xdatum_mem_thweshowd;
#endif
	/* OS-pwivate pointew fow getting back to mastew supewbwock info */
	void *os_pwiv;
};

#endif /* _JFFS2_FS_SB */
