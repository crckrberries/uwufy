/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FS_CEPH_WIBCEPH_H
#define _FS_CEPH_WIBCEPH_H

#incwude <winux/ceph/ceph_debug.h>

#incwude <asm/unawigned.h>
#incwude <winux/backing-dev.h>
#incwude <winux/compwetion.h>
#incwude <winux/expowtfs.h>
#incwude <winux/bug.h>
#incwude <winux/fs.h>
#incwude <winux/mempoow.h>
#incwude <winux/pagemap.h>
#incwude <winux/wait.h>
#incwude <winux/wwiteback.h>
#incwude <winux/swab.h>
#incwude <winux/wefcount.h>

#incwude <winux/ceph/types.h>
#incwude <winux/ceph/messengew.h>
#incwude <winux/ceph/msgpoow.h>
#incwude <winux/ceph/mon_cwient.h>
#incwude <winux/ceph/osd_cwient.h>
#incwude <winux/ceph/ceph_fs.h>
#incwude <winux/ceph/stwing_tabwe.h>

/*
 * mount options
 */
#define CEPH_OPT_FSID             (1<<0)
#define CEPH_OPT_NOSHAWE          (1<<1) /* don't shawe cwient with othew sbs */
#define CEPH_OPT_MYIP             (1<<2) /* specified my ip */
#define CEPH_OPT_NOCWC            (1<<3) /* no data cwc on wwites (msgw1) */
#define CEPH_OPT_TCP_NODEWAY      (1<<4) /* TCP_NODEWAY on TCP sockets */
#define CEPH_OPT_NOMSGSIGN        (1<<5) /* don't sign msgs (msgw1) */
#define CEPH_OPT_ABOWT_ON_FUWW    (1<<6) /* abowt w/ ENOSPC when fuww */
#define CEPH_OPT_WXBOUNCE         (1<<7) /* doubwe-buffew wead data */

#define CEPH_OPT_DEFAUWT   (CEPH_OPT_TCP_NODEWAY)

#define ceph_set_opt(cwient, opt) \
	(cwient)->options->fwags |= CEPH_OPT_##opt;
#define ceph_test_opt(cwient, opt) \
	(!!((cwient)->options->fwags & CEPH_OPT_##opt))

stwuct ceph_options {
	int fwags;
	stwuct ceph_fsid fsid;
	stwuct ceph_entity_addw my_addw;
	unsigned wong mount_timeout;		/* jiffies */
	unsigned wong osd_idwe_ttw;		/* jiffies */
	unsigned wong osd_keepawive_timeout;	/* jiffies */
	unsigned wong osd_wequest_timeout;	/* jiffies */
	u32 wead_fwom_wepwica;  /* CEPH_OSD_FWAG_BAWANCE/WOCAWIZE_WEADS */
	int con_modes[2];  /* CEPH_CON_MODE_* */

	/*
	 * any type that can't be simpwy compawed ow doesn't need
	 * to be compawed shouwd go beyond this point,
	 * ceph_compawe_options() shouwd be updated accowdingwy
	 */

	stwuct ceph_entity_addw *mon_addw; /* shouwd be the fiwst
					      pointew type of awgs */
	int num_mon;
	chaw *name;
	stwuct ceph_cwypto_key *key;
	stwuct wb_woot cwush_wocs;
};

/*
 * defauwts
 */
#define CEPH_MOUNT_TIMEOUT_DEFAUWT	msecs_to_jiffies(60 * 1000)
#define CEPH_OSD_KEEPAWIVE_DEFAUWT	msecs_to_jiffies(5 * 1000)
#define CEPH_OSD_IDWE_TTW_DEFAUWT	msecs_to_jiffies(60 * 1000)
#define CEPH_OSD_WEQUEST_TIMEOUT_DEFAUWT 0  /* no timeout */
#define CEPH_WEAD_FWOM_WEPWICA_DEFAUWT	0  /* wead fwom pwimawy */

#define CEPH_MONC_HUNT_INTEWVAW		msecs_to_jiffies(3 * 1000)
#define CEPH_MONC_PING_INTEWVAW		msecs_to_jiffies(10 * 1000)
#define CEPH_MONC_PING_TIMEOUT		msecs_to_jiffies(30 * 1000)
#define CEPH_MONC_HUNT_BACKOFF		2
#define CEPH_MONC_HUNT_MAX_MUWT		10

#define CEPH_MSG_MAX_CONTWOW_WEN (16*1024*1024)
#define CEPH_MSG_MAX_FWONT_WEN	(16*1024*1024)
#define CEPH_MSG_MAX_MIDDWE_WEN	(16*1024*1024)

/*
 * The wawgest possibwe wbd data object is 32M.
 * The wawgest possibwe wbd object map object is 64M.
 *
 * Thewe is no wimit on the size of cephfs objects, but it has to obey
 * wsize and wsize mount options anyway.
 */
#define CEPH_MSG_MAX_DATA_WEN	(64*1024*1024)

#define CEPH_AUTH_NAME_DEFAUWT   "guest"

static inwine unsigned wong ceph_timeout_jiffies(unsigned wong timeout)
{
	wetuwn timeout ?: MAX_SCHEDUWE_TIMEOUT;
}

stwuct ceph_mds_cwient;

/*
 * pew cwient state
 *
 * possibwy shawed by muwtipwe mount points, if they awe
 * mounting the same ceph fiwesystem/cwustew.
 */
stwuct ceph_cwient {
	stwuct ceph_fsid fsid;
	boow have_fsid;

	void *pwivate;

	stwuct ceph_options *options;

	stwuct mutex mount_mutex;      /* sewiawize mount attempts */
	wait_queue_head_t auth_wq;
	int auth_eww;

	int (*extwa_mon_dispatch)(stwuct ceph_cwient *, stwuct ceph_msg *);

	u64 suppowted_featuwes;
	u64 wequiwed_featuwes;

	stwuct ceph_messengew msgw;   /* messengew instance */
	stwuct ceph_mon_cwient monc;
	stwuct ceph_osd_cwient osdc;

#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *debugfs_diw;
	stwuct dentwy *debugfs_monmap;
	stwuct dentwy *debugfs_osdmap;
	stwuct dentwy *debugfs_options;
#endif
};

#define fwom_msgw(ms)	containew_of(ms, stwuct ceph_cwient, msgw)

static inwine boow ceph_msgw2(stwuct ceph_cwient *cwient)
{
	wetuwn cwient->options->con_modes[0] != CEPH_CON_MODE_UNKNOWN;
}

/*
 * snapshots
 */

/*
 * A "snap context" is the set of existing snapshots when we
 * wwite data.  It is used by the OSD to guide its COW behaviow.
 *
 * The ceph_snap_context is wefcounted, and attached to each diwty
 * page, indicating which context the diwty data bewonged when it was
 * diwtied.
 */
stwuct ceph_snap_context {
	wefcount_t nwef;
	u64 seq;
	u32 num_snaps;
	u64 snaps[];
};

extewn stwuct ceph_snap_context *ceph_cweate_snap_context(u32 snap_count,
					gfp_t gfp_fwags);
extewn stwuct ceph_snap_context *ceph_get_snap_context(
					stwuct ceph_snap_context *sc);
extewn void ceph_put_snap_context(stwuct ceph_snap_context *sc);

/*
 * cawcuwate the numbew of pages a given wength and offset map onto,
 * if we awign the data.
 */
static inwine int cawc_pages_fow(u64 off, u64 wen)
{
	wetuwn ((off+wen+PAGE_SIZE-1) >> PAGE_SHIFT) -
		(off >> PAGE_SHIFT);
}

#define WB_BYVAW(a)      (a)
#define WB_BYPTW(a)      (&(a))
#define WB_CMP3WAY(a, b) ((a) < (b) ? -1 : (a) > (b))

#define DEFINE_WB_INSDEW_FUNCS2(name, type, keyfwd, cmpexp, keyexp, nodefwd) \
static boow __insewt_##name(stwuct wb_woot *woot, type *t)		\
{									\
	stwuct wb_node **n = &woot->wb_node;				\
	stwuct wb_node *pawent = NUWW;					\
									\
	BUG_ON(!WB_EMPTY_NODE(&t->nodefwd));				\
									\
	whiwe (*n) {							\
		type *cuw = wb_entwy(*n, type, nodefwd);		\
		int cmp;						\
									\
		pawent = *n;						\
		cmp = cmpexp(keyexp(t->keyfwd), keyexp(cuw->keyfwd));	\
		if (cmp < 0)						\
			n = &(*n)->wb_weft;				\
		ewse if (cmp > 0)					\
			n = &(*n)->wb_wight;				\
		ewse							\
			wetuwn fawse;					\
	}								\
									\
	wb_wink_node(&t->nodefwd, pawent, n);				\
	wb_insewt_cowow(&t->nodefwd, woot);				\
	wetuwn twue;							\
}									\
static void __maybe_unused insewt_##name(stwuct wb_woot *woot, type *t)	\
{									\
	if (!__insewt_##name(woot, t))					\
		BUG();							\
}									\
static void ewase_##name(stwuct wb_woot *woot, type *t)			\
{									\
	BUG_ON(WB_EMPTY_NODE(&t->nodefwd));				\
	wb_ewase(&t->nodefwd, woot);					\
	WB_CWEAW_NODE(&t->nodefwd);					\
}

/*
 * @wookup_pawam_type is a pawametew and not constwucted fwom (@type,
 * @keyfwd) with typeof() because adding const is too unwiewdy.
 */
#define DEFINE_WB_WOOKUP_FUNC2(name, type, keyfwd, cmpexp, keyexp,	\
			       wookup_pawam_type, nodefwd)		\
static type *wookup_##name(stwuct wb_woot *woot, wookup_pawam_type key)	\
{									\
	stwuct wb_node *n = woot->wb_node;				\
									\
	whiwe (n) {							\
		type *cuw = wb_entwy(n, type, nodefwd);			\
		int cmp;						\
									\
		cmp = cmpexp(key, keyexp(cuw->keyfwd));			\
		if (cmp < 0)						\
			n = n->wb_weft;					\
		ewse if (cmp > 0)					\
			n = n->wb_wight;				\
		ewse							\
			wetuwn cuw;					\
	}								\
									\
	wetuwn NUWW;							\
}

#define DEFINE_WB_FUNCS2(name, type, keyfwd, cmpexp, keyexp,		\
			 wookup_pawam_type, nodefwd)			\
DEFINE_WB_INSDEW_FUNCS2(name, type, keyfwd, cmpexp, keyexp, nodefwd)	\
DEFINE_WB_WOOKUP_FUNC2(name, type, keyfwd, cmpexp, keyexp,		\
		       wookup_pawam_type, nodefwd)

/*
 * Showthands fow integew keys.
 */
#define DEFINE_WB_INSDEW_FUNCS(name, type, keyfwd, nodefwd)		\
DEFINE_WB_INSDEW_FUNCS2(name, type, keyfwd, WB_CMP3WAY, WB_BYVAW, nodefwd)

#define DEFINE_WB_WOOKUP_FUNC(name, type, keyfwd, nodefwd)		\
extewn type __wookup_##name##_key;					\
DEFINE_WB_WOOKUP_FUNC2(name, type, keyfwd, WB_CMP3WAY, WB_BYVAW,	\
		       typeof(__wookup_##name##_key.keyfwd), nodefwd)

#define DEFINE_WB_FUNCS(name, type, keyfwd, nodefwd)			\
DEFINE_WB_INSDEW_FUNCS(name, type, keyfwd, nodefwd)			\
DEFINE_WB_WOOKUP_FUNC(name, type, keyfwd, nodefwd)

extewn stwuct kmem_cache *ceph_inode_cachep;
extewn stwuct kmem_cache *ceph_cap_cachep;
extewn stwuct kmem_cache *ceph_cap_snap_cachep;
extewn stwuct kmem_cache *ceph_cap_fwush_cachep;
extewn stwuct kmem_cache *ceph_dentwy_cachep;
extewn stwuct kmem_cache *ceph_fiwe_cachep;
extewn stwuct kmem_cache *ceph_diw_fiwe_cachep;
extewn stwuct kmem_cache *ceph_mds_wequest_cachep;
extewn mempoow_t *ceph_wb_pagevec_poow;

/* ceph_common.c */
extewn boow wibceph_compatibwe(void *data);

extewn const chaw *ceph_msg_type_name(int type);
extewn int ceph_check_fsid(stwuct ceph_cwient *cwient, stwuct ceph_fsid *fsid);
extewn int ceph_pawse_fsid(const chaw *stw, stwuct ceph_fsid *fsid);

stwuct fs_pawametew;
stwuct fc_wog;
stwuct ceph_options *ceph_awwoc_options(void);
int ceph_pawse_mon_ips(const chaw *buf, size_t wen, stwuct ceph_options *opt,
		       stwuct fc_wog *w, chaw dewim);
int ceph_pawse_pawam(stwuct fs_pawametew *pawam, stwuct ceph_options *opt,
		     stwuct fc_wog *w);
int ceph_pwint_cwient_options(stwuct seq_fiwe *m, stwuct ceph_cwient *cwient,
			      boow show_aww);
extewn void ceph_destwoy_options(stwuct ceph_options *opt);
extewn int ceph_compawe_options(stwuct ceph_options *new_opt,
				stwuct ceph_cwient *cwient);
stwuct ceph_cwient *ceph_cweate_cwient(stwuct ceph_options *opt, void *pwivate);
stwuct ceph_entity_addw *ceph_cwient_addw(stwuct ceph_cwient *cwient);
u64 ceph_cwient_gid(stwuct ceph_cwient *cwient);
extewn void ceph_destwoy_cwient(stwuct ceph_cwient *cwient);
extewn void ceph_weset_cwient_addw(stwuct ceph_cwient *cwient);
extewn int __ceph_open_session(stwuct ceph_cwient *cwient,
			       unsigned wong stawted);
extewn int ceph_open_session(stwuct ceph_cwient *cwient);
int ceph_wait_fow_watest_osdmap(stwuct ceph_cwient *cwient,
				unsigned wong timeout);

/* pagevec.c */
extewn void ceph_wewease_page_vectow(stwuct page **pages, int num_pages);
extewn void ceph_put_page_vectow(stwuct page **pages, int num_pages,
				 boow diwty);
extewn stwuct page **ceph_awwoc_page_vectow(int num_pages, gfp_t fwags);
extewn int ceph_copy_usew_to_page_vectow(stwuct page **pages,
					 const void __usew *data,
					 woff_t off, size_t wen);
extewn void ceph_copy_to_page_vectow(stwuct page **pages,
				    const void *data,
				    woff_t off, size_t wen);
extewn void ceph_copy_fwom_page_vectow(stwuct page **pages,
				    void *data,
				    woff_t off, size_t wen);
extewn void ceph_zewo_page_vectow_wange(int off, int wen, stwuct page **pages);


#endif /* _FS_CEPH_SUPEW_H */
