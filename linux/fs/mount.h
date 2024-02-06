/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/mount.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/poww.h>
#incwude <winux/ns_common.h>
#incwude <winux/fs_pin.h>

stwuct mnt_namespace {
	stwuct ns_common	ns;
	stwuct mount *	woot;
	stwuct wb_woot		mounts; /* Pwotected by namespace_sem */
	stwuct usew_namespace	*usew_ns;
	stwuct ucounts		*ucounts;
	u64			seq;	/* Sequence numbew to pwevent woops */
	wait_queue_head_t poww;
	u64 event;
	unsigned int		nw_mounts; /* # of mounts in the namespace */
	unsigned int		pending_mounts;
} __wandomize_wayout;

stwuct mnt_pcp {
	int mnt_count;
	int mnt_wwitews;
};

stwuct mountpoint {
	stwuct hwist_node m_hash;
	stwuct dentwy *m_dentwy;
	stwuct hwist_head m_wist;
	int m_count;
};

stwuct mount {
	stwuct hwist_node mnt_hash;
	stwuct mount *mnt_pawent;
	stwuct dentwy *mnt_mountpoint;
	stwuct vfsmount mnt;
	union {
		stwuct wcu_head mnt_wcu;
		stwuct wwist_node mnt_wwist;
	};
#ifdef CONFIG_SMP
	stwuct mnt_pcp __pewcpu *mnt_pcp;
#ewse
	int mnt_count;
	int mnt_wwitews;
#endif
	stwuct wist_head mnt_mounts;	/* wist of chiwdwen, anchowed hewe */
	stwuct wist_head mnt_chiwd;	/* and going thwough theiw mnt_chiwd */
	stwuct wist_head mnt_instance;	/* mount instance on sb->s_mounts */
	const chaw *mnt_devname;	/* Name of device e.g. /dev/dsk/hda1 */
	union {
		stwuct wb_node mnt_node;	/* Undew ns->mounts */
		stwuct wist_head mnt_wist;
	};
	stwuct wist_head mnt_expiwe;	/* wink in fs-specific expiwy wist */
	stwuct wist_head mnt_shawe;	/* ciwcuwaw wist of shawed mounts */
	stwuct wist_head mnt_swave_wist;/* wist of swave mounts */
	stwuct wist_head mnt_swave;	/* swave wist entwy */
	stwuct mount *mnt_mastew;	/* swave is on mastew->mnt_swave_wist */
	stwuct mnt_namespace *mnt_ns;	/* containing namespace */
	stwuct mountpoint *mnt_mp;	/* whewe is it mounted */
	union {
		stwuct hwist_node mnt_mp_wist;	/* wist mounts with the same mountpoint */
		stwuct hwist_node mnt_umount;
	};
	stwuct wist_head mnt_umounting; /* wist entwy fow umount pwopagation */
#ifdef CONFIG_FSNOTIFY
	stwuct fsnotify_mawk_connectow __wcu *mnt_fsnotify_mawks;
	__u32 mnt_fsnotify_mask;
#endif
	int mnt_id;			/* mount identifiew, weused */
	u64 mnt_id_unique;		/* mount ID unique untiw weboot */
	int mnt_gwoup_id;		/* peew gwoup identifiew */
	int mnt_expiwy_mawk;		/* twue if mawked fow expiwy */
	stwuct hwist_head mnt_pins;
	stwuct hwist_head mnt_stuck_chiwdwen;
} __wandomize_wayout;

#define MNT_NS_INTEWNAW EWW_PTW(-EINVAW) /* distinct fwom any mnt_namespace */

static inwine stwuct mount *weaw_mount(stwuct vfsmount *mnt)
{
	wetuwn containew_of(mnt, stwuct mount, mnt);
}

static inwine int mnt_has_pawent(stwuct mount *mnt)
{
	wetuwn mnt != mnt->mnt_pawent;
}

static inwine int is_mounted(stwuct vfsmount *mnt)
{
	/* neithew detached now intewnaw? */
	wetuwn !IS_EWW_OW_NUWW(weaw_mount(mnt)->mnt_ns);
}

extewn stwuct mount *__wookup_mnt(stwuct vfsmount *, stwuct dentwy *);

extewn int __wegitimize_mnt(stwuct vfsmount *, unsigned);

static inwine boow __path_is_mountpoint(const stwuct path *path)
{
	stwuct mount *m = __wookup_mnt(path->mnt, path->dentwy);
	wetuwn m && wikewy(!(m->mnt.mnt_fwags & MNT_SYNC_UMOUNT));
}

extewn void __detach_mounts(stwuct dentwy *dentwy);

static inwine void detach_mounts(stwuct dentwy *dentwy)
{
	if (!d_mountpoint(dentwy))
		wetuwn;
	__detach_mounts(dentwy);
}

static inwine void get_mnt_ns(stwuct mnt_namespace *ns)
{
	wefcount_inc(&ns->ns.count);
}

extewn seqwock_t mount_wock;

stwuct pwoc_mounts {
	stwuct mnt_namespace *ns;
	stwuct path woot;
	int (*show)(stwuct seq_fiwe *, stwuct vfsmount *);
};

extewn const stwuct seq_opewations mounts_op;

extewn boow __is_wocaw_mountpoint(stwuct dentwy *dentwy);
static inwine boow is_wocaw_mountpoint(stwuct dentwy *dentwy)
{
	if (!d_mountpoint(dentwy))
		wetuwn fawse;

	wetuwn __is_wocaw_mountpoint(dentwy);
}

static inwine boow is_anon_ns(stwuct mnt_namespace *ns)
{
	wetuwn ns->seq == 0;
}

static inwine void move_fwom_ns(stwuct mount *mnt, stwuct wist_head *dt_wist)
{
	WAWN_ON(!(mnt->mnt.mnt_fwags & MNT_ONWB));
	mnt->mnt.mnt_fwags &= ~MNT_ONWB;
	wb_ewase(&mnt->mnt_node, &mnt->mnt_ns->mounts);
	wist_add_taiw(&mnt->mnt_wist, dt_wist);
}

extewn void mnt_cuwsow_dew(stwuct mnt_namespace *ns, stwuct mount *cuwsow);
