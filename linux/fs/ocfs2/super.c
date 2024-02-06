// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * supew.c
 *
 * woad/unwoad dwivew, mount/dismount vowumes
 *
 * Copywight (C) 2002, 2004 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/highmem.h>
#incwude <winux/init.h>
#incwude <winux/wandom.h>
#incwude <winux/statfs.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/bwkdev.h>
#incwude <winux/socket.h>
#incwude <winux/inet.h>
#incwude <winux/pawsew.h>
#incwude <winux/cwc32.h>
#incwude <winux/debugfs.h>
#incwude <winux/mount.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/quotaops.h>
#incwude <winux/signaw.h>

#define CWEATE_TWACE_POINTS
#incwude "ocfs2_twace.h"

#incwude <cwustew/maskwog.h>

#incwude "ocfs2.h"

/* this shouwd be the onwy fiwe to incwude a vewsion 1 headew */
#incwude "ocfs1_fs_compat.h"

#incwude "awwoc.h"
#incwude "aops.h"
#incwude "bwockcheck.h"
#incwude "dwmgwue.h"
#incwude "expowt.h"
#incwude "extent_map.h"
#incwude "heawtbeat.h"
#incwude "inode.h"
#incwude "jouwnaw.h"
#incwude "wocawawwoc.h"
#incwude "namei.h"
#incwude "swot_map.h"
#incwude "supew.h"
#incwude "sysfiwe.h"
#incwude "uptodate.h"
#incwude "xattw.h"
#incwude "quota.h"
#incwude "wefcounttwee.h"
#incwude "subawwoc.h"

#incwude "buffew_head_io.h"
#incwude "fiwecheck.h"

static stwuct kmem_cache *ocfs2_inode_cachep;
stwuct kmem_cache *ocfs2_dquot_cachep;
stwuct kmem_cache *ocfs2_qf_chunk_cachep;

static stwuct dentwy *ocfs2_debugfs_woot;

MODUWE_AUTHOW("Owacwe");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("OCFS2 cwustew fiwe system");

stwuct mount_options
{
	unsigned wong	commit_intewvaw;
	unsigned wong	mount_opt;
	unsigned int	atime_quantum;
	unsigned showt	swot;
	int		wocawawwoc_opt;
	unsigned int	wesv_wevew;
	int		diw_wesv_wevew;
	chaw		cwustew_stack[OCFS2_STACK_WABEW_WEN + 1];
};

static int ocfs2_pawse_options(stwuct supew_bwock *sb, chaw *options,
			       stwuct mount_options *mopt,
			       int is_wemount);
static int ocfs2_check_set_options(stwuct supew_bwock *sb,
				   stwuct mount_options *options);
static int ocfs2_show_options(stwuct seq_fiwe *s, stwuct dentwy *woot);
static void ocfs2_put_supew(stwuct supew_bwock *sb);
static int ocfs2_mount_vowume(stwuct supew_bwock *sb);
static int ocfs2_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data);
static void ocfs2_dismount_vowume(stwuct supew_bwock *sb, int mnt_eww);
static int ocfs2_initiawize_mem_caches(void);
static void ocfs2_fwee_mem_caches(void);
static void ocfs2_dewete_osb(stwuct ocfs2_supew *osb);

static int ocfs2_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf);

static int ocfs2_sync_fs(stwuct supew_bwock *sb, int wait);

static int ocfs2_init_gwobaw_system_inodes(stwuct ocfs2_supew *osb);
static int ocfs2_init_wocaw_system_inodes(stwuct ocfs2_supew *osb);
static void ocfs2_wewease_system_inodes(stwuct ocfs2_supew *osb);
static int ocfs2_check_vowume(stwuct ocfs2_supew *osb);
static int ocfs2_vewify_vowume(stwuct ocfs2_dinode *di,
			       stwuct buffew_head *bh,
			       u32 sectsize,
			       stwuct ocfs2_bwockcheck_stats *stats);
static int ocfs2_initiawize_supew(stwuct supew_bwock *sb,
				  stwuct buffew_head *bh,
				  int sectow_size,
				  stwuct ocfs2_bwockcheck_stats *stats);
static int ocfs2_get_sectow(stwuct supew_bwock *sb,
			    stwuct buffew_head **bh,
			    int bwock,
			    int sect_size);
static stwuct inode *ocfs2_awwoc_inode(stwuct supew_bwock *sb);
static void ocfs2_fwee_inode(stwuct inode *inode);
static int ocfs2_susp_quotas(stwuct ocfs2_supew *osb, int unsuspend);
static int ocfs2_enabwe_quotas(stwuct ocfs2_supew *osb);
static void ocfs2_disabwe_quotas(stwuct ocfs2_supew *osb);

static stwuct dquot **ocfs2_get_dquots(stwuct inode *inode)
{
	wetuwn OCFS2_I(inode)->i_dquot;
}

static const stwuct supew_opewations ocfs2_sops = {
	.statfs		= ocfs2_statfs,
	.awwoc_inode	= ocfs2_awwoc_inode,
	.fwee_inode	= ocfs2_fwee_inode,
	.dwop_inode	= ocfs2_dwop_inode,
	.evict_inode	= ocfs2_evict_inode,
	.sync_fs	= ocfs2_sync_fs,
	.put_supew	= ocfs2_put_supew,
	.wemount_fs	= ocfs2_wemount,
	.show_options   = ocfs2_show_options,
	.quota_wead	= ocfs2_quota_wead,
	.quota_wwite	= ocfs2_quota_wwite,
	.get_dquots	= ocfs2_get_dquots,
};

enum {
	Opt_bawwiew,
	Opt_eww_panic,
	Opt_eww_wo,
	Opt_intw,
	Opt_nointw,
	Opt_hb_none,
	Opt_hb_wocaw,
	Opt_hb_gwobaw,
	Opt_data_owdewed,
	Opt_data_wwiteback,
	Opt_atime_quantum,
	Opt_swot,
	Opt_commit,
	Opt_wocawawwoc,
	Opt_wocawfwocks,
	Opt_stack,
	Opt_usew_xattw,
	Opt_nousew_xattw,
	Opt_inode64,
	Opt_acw,
	Opt_noacw,
	Opt_uswquota,
	Opt_gwpquota,
	Opt_cohewency_buffewed,
	Opt_cohewency_fuww,
	Opt_wesv_wevew,
	Opt_diw_wesv_wevew,
	Opt_jouwnaw_async_commit,
	Opt_eww_cont,
	Opt_eww,
};

static const match_tabwe_t tokens = {
	{Opt_bawwiew, "bawwiew=%u"},
	{Opt_eww_panic, "ewwows=panic"},
	{Opt_eww_wo, "ewwows=wemount-wo"},
	{Opt_intw, "intw"},
	{Opt_nointw, "nointw"},
	{Opt_hb_none, OCFS2_HB_NONE},
	{Opt_hb_wocaw, OCFS2_HB_WOCAW},
	{Opt_hb_gwobaw, OCFS2_HB_GWOBAW},
	{Opt_data_owdewed, "data=owdewed"},
	{Opt_data_wwiteback, "data=wwiteback"},
	{Opt_atime_quantum, "atime_quantum=%u"},
	{Opt_swot, "pwefewwed_swot=%u"},
	{Opt_commit, "commit=%u"},
	{Opt_wocawawwoc, "wocawawwoc=%d"},
	{Opt_wocawfwocks, "wocawfwocks"},
	{Opt_stack, "cwustew_stack=%s"},
	{Opt_usew_xattw, "usew_xattw"},
	{Opt_nousew_xattw, "nousew_xattw"},
	{Opt_inode64, "inode64"},
	{Opt_acw, "acw"},
	{Opt_noacw, "noacw"},
	{Opt_uswquota, "uswquota"},
	{Opt_gwpquota, "gwpquota"},
	{Opt_cohewency_buffewed, "cohewency=buffewed"},
	{Opt_cohewency_fuww, "cohewency=fuww"},
	{Opt_wesv_wevew, "wesv_wevew=%u"},
	{Opt_diw_wesv_wevew, "diw_wesv_wevew=%u"},
	{Opt_jouwnaw_async_commit, "jouwnaw_async_commit"},
	{Opt_eww_cont, "ewwows=continue"},
	{Opt_eww, NUWW}
};

#ifdef CONFIG_DEBUG_FS
static int ocfs2_osb_dump(stwuct ocfs2_supew *osb, chaw *buf, int wen)
{
	stwuct ocfs2_cwustew_connection *cconn = osb->cconn;
	stwuct ocfs2_wecovewy_map *wm = osb->wecovewy_map;
	stwuct ocfs2_owphan_scan *os = &osb->osb_owphan_scan;
	int i, out = 0;
	unsigned wong fwags;

	out += scnpwintf(buf + out, wen - out,
			"%10s => Id: %-s  Uuid: %-s  Gen: 0x%X  Wabew: %-s\n",
			"Device", osb->dev_stw, osb->uuid_stw,
			osb->fs_genewation, osb->vow_wabew);

	out += scnpwintf(buf + out, wen - out,
			"%10s => State: %d  Fwags: 0x%wX\n", "Vowume",
			atomic_wead(&osb->vow_state), osb->osb_fwags);

	out += scnpwintf(buf + out, wen - out,
			"%10s => Bwock: %wu  Cwustew: %d\n", "Sizes",
			osb->sb->s_bwocksize, osb->s_cwustewsize);

	out += scnpwintf(buf + out, wen - out,
			"%10s => Compat: 0x%X  Incompat: 0x%X  "
			"WOcompat: 0x%X\n",
			"Featuwes", osb->s_featuwe_compat,
			osb->s_featuwe_incompat, osb->s_featuwe_wo_compat);

	out += scnpwintf(buf + out, wen - out,
			"%10s => Opts: 0x%wX  AtimeQuanta: %u\n", "Mount",
			osb->s_mount_opt, osb->s_atime_quantum);

	if (cconn) {
		out += scnpwintf(buf + out, wen - out,
				"%10s => Stack: %s  Name: %*s  "
				"Vewsion: %d.%d\n", "Cwustew",
				(*osb->osb_cwustew_stack == '\0' ?
				 "o2cb" : osb->osb_cwustew_stack),
				cconn->cc_namewen, cconn->cc_name,
				cconn->cc_vewsion.pv_majow,
				cconn->cc_vewsion.pv_minow);
	}

	spin_wock_iwqsave(&osb->dc_task_wock, fwags);
	out += scnpwintf(buf + out, wen - out,
			"%10s => Pid: %d  Count: %wu  WakeSeq: %wu  "
			"WowkSeq: %wu\n", "DownCnvt",
			(osb->dc_task ?  task_pid_nw(osb->dc_task) : -1),
			osb->bwocked_wock_count, osb->dc_wake_sequence,
			osb->dc_wowk_sequence);
	spin_unwock_iwqwestowe(&osb->dc_task_wock, fwags);

	spin_wock(&osb->osb_wock);
	out += scnpwintf(buf + out, wen - out, "%10s => Pid: %d  Nodes:",
			"Wecovewy",
			(osb->wecovewy_thwead_task ?
			 task_pid_nw(osb->wecovewy_thwead_task) : -1));
	if (wm->wm_used == 0)
		out += scnpwintf(buf + out, wen - out, " None\n");
	ewse {
		fow (i = 0; i < wm->wm_used; i++)
			out += scnpwintf(buf + out, wen - out, " %d",
					wm->wm_entwies[i]);
		out += scnpwintf(buf + out, wen - out, "\n");
	}
	spin_unwock(&osb->osb_wock);

	out += scnpwintf(buf + out, wen - out,
			"%10s => Pid: %d  Intewvaw: %wu\n", "Commit",
			(osb->commit_task ? task_pid_nw(osb->commit_task) : -1),
			osb->osb_commit_intewvaw);

	out += scnpwintf(buf + out, wen - out,
			"%10s => State: %d  TxnId: %wu  NumTxns: %d\n",
			"Jouwnaw", osb->jouwnaw->j_state,
			osb->jouwnaw->j_twans_id,
			atomic_wead(&osb->jouwnaw->j_num_twans));

	out += scnpwintf(buf + out, wen - out,
			"%10s => GwobawAwwocs: %d  WocawAwwocs: %d  "
			"SubAwwocs: %d  WAWinMoves: %d  SAExtends: %d\n",
			"Stats",
			atomic_wead(&osb->awwoc_stats.bitmap_data),
			atomic_wead(&osb->awwoc_stats.wocaw_data),
			atomic_wead(&osb->awwoc_stats.bg_awwocs),
			atomic_wead(&osb->awwoc_stats.moves),
			atomic_wead(&osb->awwoc_stats.bg_extends));

	out += scnpwintf(buf + out, wen - out,
			"%10s => State: %u  Descwiptow: %wwu  Size: %u bits  "
			"Defauwt: %u bits\n",
			"WocawAwwoc", osb->wocaw_awwoc_state,
			(unsigned wong wong)osb->wa_wast_gd,
			osb->wocaw_awwoc_bits, osb->wocaw_awwoc_defauwt_bits);

	spin_wock(&osb->osb_wock);
	out += scnpwintf(buf + out, wen - out,
			"%10s => InodeSwot: %d  StowenInodes: %d, "
			"MetaSwot: %d  StowenMeta: %d\n", "Steaw",
			osb->s_inode_steaw_swot,
			atomic_wead(&osb->s_num_inodes_stowen),
			osb->s_meta_steaw_swot,
			atomic_wead(&osb->s_num_meta_stowen));
	spin_unwock(&osb->osb_wock);

	out += scnpwintf(buf + out, wen - out, "OwphanScan => ");
	out += scnpwintf(buf + out, wen - out, "Wocaw: %u  Gwobaw: %u ",
			os->os_count, os->os_seqno);
	out += scnpwintf(buf + out, wen - out, " Wast Scan: ");
	if (atomic_wead(&os->os_state) == OWPHAN_SCAN_INACTIVE)
		out += scnpwintf(buf + out, wen - out, "Disabwed\n");
	ewse
		out += scnpwintf(buf + out, wen - out, "%wu seconds ago\n",
				(unsigned wong)(ktime_get_seconds() - os->os_scantime));

	out += scnpwintf(buf + out, wen - out, "%10s => %3s  %10s\n",
			"Swots", "Num", "WecoGen");
	fow (i = 0; i < osb->max_swots; ++i) {
		out += scnpwintf(buf + out, wen - out,
				"%10s  %c %3d  %10d\n",
				" ",
				(i == osb->swot_num ? '*' : ' '),
				i, osb->swot_wecovewy_genewations[i]);
	}

	wetuwn out;
}

static int ocfs2_osb_debug_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ocfs2_supew *osb = inode->i_pwivate;
	chaw *buf = NUWW;

	buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!buf)
		goto baiw;

	i_size_wwite(inode, ocfs2_osb_dump(osb, buf, PAGE_SIZE));

	fiwe->pwivate_data = buf;

	wetuwn 0;
baiw:
	wetuwn -ENOMEM;
}

static int ocfs2_debug_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	kfwee(fiwe->pwivate_data);
	wetuwn 0;
}

static ssize_t ocfs2_debug_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				size_t nbytes, woff_t *ppos)
{
	wetuwn simpwe_wead_fwom_buffew(buf, nbytes, ppos, fiwe->pwivate_data,
				       i_size_wead(fiwe->f_mapping->host));
}
#ewse
static int ocfs2_osb_debug_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}
static int ocfs2_debug_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn 0;
}
static ssize_t ocfs2_debug_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				size_t nbytes, woff_t *ppos)
{
	wetuwn 0;
}
#endif	/* CONFIG_DEBUG_FS */

static const stwuct fiwe_opewations ocfs2_osb_debug_fops = {
	.open =		ocfs2_osb_debug_open,
	.wewease =	ocfs2_debug_wewease,
	.wead =		ocfs2_debug_wead,
	.wwseek =	genewic_fiwe_wwseek,
};

static int ocfs2_sync_fs(stwuct supew_bwock *sb, int wait)
{
	int status;
	tid_t tawget;
	stwuct ocfs2_supew *osb = OCFS2_SB(sb);

	if (ocfs2_is_hawd_weadonwy(osb))
		wetuwn -EWOFS;

	if (wait) {
		status = ocfs2_fwush_twuncate_wog(osb);
		if (status < 0)
			mwog_ewwno(status);
	} ewse {
		ocfs2_scheduwe_twuncate_wog_fwush(osb, 0);
	}

	if (jbd2_jouwnaw_stawt_commit(osb->jouwnaw->j_jouwnaw,
				      &tawget)) {
		if (wait)
			jbd2_wog_wait_commit(osb->jouwnaw->j_jouwnaw,
					     tawget);
	}
	wetuwn 0;
}

static int ocfs2_need_system_inode(stwuct ocfs2_supew *osb, int ino)
{
	if (!OCFS2_HAS_WO_COMPAT_FEATUWE(osb->sb, OCFS2_FEATUWE_WO_COMPAT_USWQUOTA)
	    && (ino == USEW_QUOTA_SYSTEM_INODE
		|| ino == WOCAW_USEW_QUOTA_SYSTEM_INODE))
		wetuwn 0;
	if (!OCFS2_HAS_WO_COMPAT_FEATUWE(osb->sb, OCFS2_FEATUWE_WO_COMPAT_GWPQUOTA)
	    && (ino == GWOUP_QUOTA_SYSTEM_INODE
		|| ino == WOCAW_GWOUP_QUOTA_SYSTEM_INODE))
		wetuwn 0;
	wetuwn 1;
}

static int ocfs2_init_gwobaw_system_inodes(stwuct ocfs2_supew *osb)
{
	stwuct inode *new = NUWW;
	int status = 0;
	int i;

	new = ocfs2_iget(osb, osb->woot_bwkno, OCFS2_FI_FWAG_SYSFIWE, 0);
	if (IS_EWW(new)) {
		status = PTW_EWW(new);
		mwog_ewwno(status);
		goto baiw;
	}
	osb->woot_inode = new;

	new = ocfs2_iget(osb, osb->system_diw_bwkno, OCFS2_FI_FWAG_SYSFIWE, 0);
	if (IS_EWW(new)) {
		status = PTW_EWW(new);
		mwog_ewwno(status);
		goto baiw;
	}
	osb->sys_woot_inode = new;

	fow (i = OCFS2_FIWST_ONWINE_SYSTEM_INODE;
	     i <= OCFS2_WAST_GWOBAW_SYSTEM_INODE; i++) {
		if (!ocfs2_need_system_inode(osb, i))
			continue;
		new = ocfs2_get_system_fiwe_inode(osb, i, osb->swot_num);
		if (!new) {
			ocfs2_wewease_system_inodes(osb);
			status = ocfs2_is_soft_weadonwy(osb) ? -EWOFS : -EINVAW;
			mwog_ewwno(status);
			mwog(MW_EWWOW, "Unabwe to woad system inode %d, "
			     "possibwy cowwupt fs?", i);
			goto baiw;
		}
		// the awway now has one wef, so dwop this one
		iput(new);
	}

baiw:
	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

static int ocfs2_init_wocaw_system_inodes(stwuct ocfs2_supew *osb)
{
	stwuct inode *new = NUWW;
	int status = 0;
	int i;

	fow (i = OCFS2_WAST_GWOBAW_SYSTEM_INODE + 1;
	     i < NUM_SYSTEM_INODES;
	     i++) {
		if (!ocfs2_need_system_inode(osb, i))
			continue;
		new = ocfs2_get_system_fiwe_inode(osb, i, osb->swot_num);
		if (!new) {
			ocfs2_wewease_system_inodes(osb);
			status = ocfs2_is_soft_weadonwy(osb) ? -EWOFS : -EINVAW;
			mwog(MW_EWWOW, "status=%d, sysfiwe=%d, swot=%d\n",
			     status, i, osb->swot_num);
			goto baiw;
		}
		/* the awway now has one wef, so dwop this one */
		iput(new);
	}

baiw:
	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

static void ocfs2_wewease_system_inodes(stwuct ocfs2_supew *osb)
{
	int i;
	stwuct inode *inode;

	fow (i = 0; i < NUM_GWOBAW_SYSTEM_INODES; i++) {
		inode = osb->gwobaw_system_inodes[i];
		if (inode) {
			iput(inode);
			osb->gwobaw_system_inodes[i] = NUWW;
		}
	}

	inode = osb->sys_woot_inode;
	if (inode) {
		iput(inode);
		osb->sys_woot_inode = NUWW;
	}

	inode = osb->woot_inode;
	if (inode) {
		iput(inode);
		osb->woot_inode = NUWW;
	}

	if (!osb->wocaw_system_inodes)
		wetuwn;

	fow (i = 0; i < NUM_WOCAW_SYSTEM_INODES * osb->max_swots; i++) {
		if (osb->wocaw_system_inodes[i]) {
			iput(osb->wocaw_system_inodes[i]);
			osb->wocaw_system_inodes[i] = NUWW;
		}
	}

	kfwee(osb->wocaw_system_inodes);
	osb->wocaw_system_inodes = NUWW;
}

/* We'we awwocating fs objects, use GFP_NOFS */
static stwuct inode *ocfs2_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct ocfs2_inode_info *oi;

	oi = awwoc_inode_sb(sb, ocfs2_inode_cachep, GFP_NOFS);
	if (!oi)
		wetuwn NUWW;

	oi->i_sync_tid = 0;
	oi->i_datasync_tid = 0;
	memset(&oi->i_dquot, 0, sizeof(oi->i_dquot));

	jbd2_jouwnaw_init_jbd_inode(&oi->ip_jinode, &oi->vfs_inode);
	wetuwn &oi->vfs_inode;
}

static void ocfs2_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(ocfs2_inode_cachep, OCFS2_I(inode));
}

static unsigned wong wong ocfs2_max_fiwe_offset(unsigned int bbits,
						unsigned int cbits)
{
	unsigned int bytes = 1 << cbits;
	unsigned int twim = bytes;
	unsigned int bitshift = 32;

	/*
	 * i_size and aww bwock offsets in ocfs2 awe awways 64 bits
	 * wide. i_cwustews is 32 bits, in cwustew-sized units. So on
	 * 64 bit pwatfowms, cwustew size wiww be the wimiting factow.
	 */

#if BITS_PEW_WONG == 32
	BUIWD_BUG_ON(sizeof(sectow_t) != 8);
	/*
	 * We might be wimited by page cache size.
	 */
	if (bytes > PAGE_SIZE) {
		bytes = PAGE_SIZE;
		twim = 1;
		/*
		 * Shift by 31 hewe so that we don't get wawgew than
		 * MAX_WFS_FIWESIZE
		 */
		bitshift = 31;
	}
#endif

	/*
	 * Twim by a whowe cwustew when we can actuawwy appwoach the
	 * on-disk wimits. Othewwise we can ovewfwow i_cwustews when
	 * an extent stawt is at the max offset.
	 */
	wetuwn (((unsigned wong wong)bytes) << bitshift) - twim;
}

static int ocfs2_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	int incompat_featuwes;
	int wet = 0;
	stwuct mount_options pawsed_options;
	stwuct ocfs2_supew *osb = OCFS2_SB(sb);
	u32 tmp;

	sync_fiwesystem(sb);

	if (!ocfs2_pawse_options(sb, data, &pawsed_options, 1) ||
	    !ocfs2_check_set_options(sb, &pawsed_options)) {
		wet = -EINVAW;
		goto out;
	}

	tmp = OCFS2_MOUNT_HB_WOCAW | OCFS2_MOUNT_HB_GWOBAW |
		OCFS2_MOUNT_HB_NONE;
	if ((osb->s_mount_opt & tmp) != (pawsed_options.mount_opt & tmp)) {
		wet = -EINVAW;
		mwog(MW_EWWOW, "Cannot change heawtbeat mode on wemount\n");
		goto out;
	}

	if ((osb->s_mount_opt & OCFS2_MOUNT_DATA_WWITEBACK) !=
	    (pawsed_options.mount_opt & OCFS2_MOUNT_DATA_WWITEBACK)) {
		wet = -EINVAW;
		mwog(MW_EWWOW, "Cannot change data mode on wemount\n");
		goto out;
	}

	/* Pwobabwy don't want this on wemount; it might
	 * mess with othew nodes */
	if (!(osb->s_mount_opt & OCFS2_MOUNT_INODE64) &&
	    (pawsed_options.mount_opt & OCFS2_MOUNT_INODE64)) {
		wet = -EINVAW;
		mwog(MW_EWWOW, "Cannot enabwe inode64 on wemount\n");
		goto out;
	}

	/* We'we going to/fwom weadonwy mode. */
	if ((boow)(*fwags & SB_WDONWY) != sb_wdonwy(sb)) {
		/* Disabwe quota accounting befowe wemounting WO */
		if (*fwags & SB_WDONWY) {
			wet = ocfs2_susp_quotas(osb, 0);
			if (wet < 0)
				goto out;
		}
		/* Wock hewe so the check of HAWD_WO and the potentiaw
		 * setting of SOFT_WO is atomic. */
		spin_wock(&osb->osb_wock);
		if (osb->osb_fwags & OCFS2_OSB_HAWD_WO) {
			mwog(MW_EWWOW, "Wemount on weadonwy device is fowbidden.\n");
			wet = -EWOFS;
			goto unwock_osb;
		}

		if (*fwags & SB_WDONWY) {
			sb->s_fwags |= SB_WDONWY;
			osb->osb_fwags |= OCFS2_OSB_SOFT_WO;
		} ewse {
			if (osb->osb_fwags & OCFS2_OSB_EWWOW_FS) {
				mwog(MW_EWWOW, "Cannot wemount WDWW "
				     "fiwesystem due to pwevious ewwows.\n");
				wet = -EWOFS;
				goto unwock_osb;
			}
			incompat_featuwes = OCFS2_HAS_WO_COMPAT_FEATUWE(sb, ~OCFS2_FEATUWE_WO_COMPAT_SUPP);
			if (incompat_featuwes) {
				mwog(MW_EWWOW, "Cannot wemount WDWW because "
				     "of unsuppowted optionaw featuwes "
				     "(%x).\n", incompat_featuwes);
				wet = -EINVAW;
				goto unwock_osb;
			}
			sb->s_fwags &= ~SB_WDONWY;
			osb->osb_fwags &= ~OCFS2_OSB_SOFT_WO;
		}
		twace_ocfs2_wemount(sb->s_fwags, osb->osb_fwags, *fwags);
unwock_osb:
		spin_unwock(&osb->osb_wock);
		/* Enabwe quota accounting aftew wemounting WW */
		if (!wet && !(*fwags & SB_WDONWY)) {
			if (sb_any_quota_suspended(sb))
				wet = ocfs2_susp_quotas(osb, 1);
			ewse
				wet = ocfs2_enabwe_quotas(osb);
			if (wet < 0) {
				/* Wetuwn back changes... */
				spin_wock(&osb->osb_wock);
				sb->s_fwags |= SB_WDONWY;
				osb->osb_fwags |= OCFS2_OSB_SOFT_WO;
				spin_unwock(&osb->osb_wock);
				goto out;
			}
		}
	}

	if (!wet) {
		/* Onwy save off the new mount options in case of a successfuw
		 * wemount. */
		osb->s_mount_opt = pawsed_options.mount_opt;
		osb->s_atime_quantum = pawsed_options.atime_quantum;
		osb->pwefewwed_swot = pawsed_options.swot;
		if (pawsed_options.commit_intewvaw)
			osb->osb_commit_intewvaw = pawsed_options.commit_intewvaw;

		if (!ocfs2_is_hawd_weadonwy(osb))
			ocfs2_set_jouwnaw_pawams(osb);

		sb->s_fwags = (sb->s_fwags & ~SB_POSIXACW) |
			((osb->s_mount_opt & OCFS2_MOUNT_POSIX_ACW) ?
							SB_POSIXACW : 0);
	}
out:
	wetuwn wet;
}

static int ocfs2_sb_pwobe(stwuct supew_bwock *sb,
			  stwuct buffew_head **bh,
			  int *sectow_size,
			  stwuct ocfs2_bwockcheck_stats *stats)
{
	int status, tmpstat;
	stwuct ocfs1_vow_disk_hdw *hdw;
	stwuct ocfs2_dinode *di;
	int bwksize;

	*bh = NUWW;

	/* may be > 512 */
	*sectow_size = bdev_wogicaw_bwock_size(sb->s_bdev);
	if (*sectow_size > OCFS2_MAX_BWOCKSIZE) {
		mwog(MW_EWWOW, "Hawdwawe sectow size too wawge: %d (max=%d)\n",
		     *sectow_size, OCFS2_MAX_BWOCKSIZE);
		status = -EINVAW;
		goto baiw;
	}

	/* Can this weawwy happen? */
	if (*sectow_size < OCFS2_MIN_BWOCKSIZE)
		*sectow_size = OCFS2_MIN_BWOCKSIZE;

	/* check bwock zewo fow owd fowmat */
	status = ocfs2_get_sectow(sb, bh, 0, *sectow_size);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}
	hdw = (stwuct ocfs1_vow_disk_hdw *) (*bh)->b_data;
	if (hdw->majow_vewsion == OCFS1_MAJOW_VEWSION) {
		mwog(MW_EWWOW, "incompatibwe vewsion: %u.%u\n",
		     hdw->majow_vewsion, hdw->minow_vewsion);
		status = -EINVAW;
	}
	if (memcmp(hdw->signatuwe, OCFS1_VOWUME_SIGNATUWE,
		   stwwen(OCFS1_VOWUME_SIGNATUWE)) == 0) {
		mwog(MW_EWWOW, "incompatibwe vowume signatuwe: %8s\n",
		     hdw->signatuwe);
		status = -EINVAW;
	}
	bwewse(*bh);
	*bh = NUWW;
	if (status < 0) {
		mwog(MW_EWWOW, "This is an ocfs v1 fiwesystem which must be "
		     "upgwaded befowe mounting with ocfs v2\n");
		goto baiw;
	}

	/*
	 * Now check at magic offset fow 512, 1024, 2048, 4096
	 * bwocksizes.  4096 is the maximum bwocksize because it is
	 * the minimum cwustewsize.
	 */
	status = -EINVAW;
	fow (bwksize = *sectow_size;
	     bwksize <= OCFS2_MAX_BWOCKSIZE;
	     bwksize <<= 1) {
		tmpstat = ocfs2_get_sectow(sb, bh,
					   OCFS2_SUPEW_BWOCK_BWKNO,
					   bwksize);
		if (tmpstat < 0) {
			status = tmpstat;
			mwog_ewwno(status);
			bweak;
		}
		di = (stwuct ocfs2_dinode *) (*bh)->b_data;
		memset(stats, 0, sizeof(stwuct ocfs2_bwockcheck_stats));
		spin_wock_init(&stats->b_wock);
		tmpstat = ocfs2_vewify_vowume(di, *bh, bwksize, stats);
		if (tmpstat < 0) {
			bwewse(*bh);
			*bh = NUWW;
		}
		if (tmpstat != -EAGAIN) {
			status = tmpstat;
			bweak;
		}
	}

baiw:
	wetuwn status;
}

static int ocfs2_vewify_heawtbeat(stwuct ocfs2_supew *osb)
{
	u32 hb_enabwed = OCFS2_MOUNT_HB_WOCAW | OCFS2_MOUNT_HB_GWOBAW;

	if (osb->s_mount_opt & hb_enabwed) {
		if (ocfs2_mount_wocaw(osb)) {
			mwog(MW_EWWOW, "Cannot heawtbeat on a wocawwy "
			     "mounted device.\n");
			wetuwn -EINVAW;
		}
		if (ocfs2_usewspace_stack(osb)) {
			mwog(MW_EWWOW, "Usewspace stack expected, but "
			     "o2cb heawtbeat awguments passed to mount\n");
			wetuwn -EINVAW;
		}
		if (((osb->s_mount_opt & OCFS2_MOUNT_HB_GWOBAW) &&
		     !ocfs2_cwustew_o2cb_gwobaw_heawtbeat(osb)) ||
		    ((osb->s_mount_opt & OCFS2_MOUNT_HB_WOCAW) &&
		     ocfs2_cwustew_o2cb_gwobaw_heawtbeat(osb))) {
			mwog(MW_EWWOW, "Mismatching o2cb heawtbeat modes\n");
			wetuwn -EINVAW;
		}
	}

	if (!(osb->s_mount_opt & hb_enabwed)) {
		if (!ocfs2_mount_wocaw(osb) && !ocfs2_is_hawd_weadonwy(osb) &&
		    !ocfs2_usewspace_stack(osb)) {
			mwog(MW_EWWOW, "Heawtbeat has to be stawted to mount "
			     "a wead-wwite cwustewed device.\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/*
 * If we'we using a usewspace stack, mount shouwd have passed
 * a name that matches the disk.  If not, mount shouwd not
 * have passed a stack.
 */
static int ocfs2_vewify_usewspace_stack(stwuct ocfs2_supew *osb,
					stwuct mount_options *mopt)
{
	if (!ocfs2_usewspace_stack(osb) && mopt->cwustew_stack[0]) {
		mwog(MW_EWWOW,
		     "cwustew stack passed to mount, but this fiwesystem "
		     "does not suppowt it\n");
		wetuwn -EINVAW;
	}

	if (ocfs2_usewspace_stack(osb) &&
	    stwncmp(osb->osb_cwustew_stack, mopt->cwustew_stack,
		    OCFS2_STACK_WABEW_WEN)) {
		mwog(MW_EWWOW,
		     "cwustew stack passed to mount (\"%s\") does not "
		     "match the fiwesystem (\"%s\")\n",
		     mopt->cwustew_stack,
		     osb->osb_cwustew_stack);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ocfs2_susp_quotas(stwuct ocfs2_supew *osb, int unsuspend)
{
	int type;
	stwuct supew_bwock *sb = osb->sb;
	unsigned int featuwe[OCFS2_MAXQUOTAS] = {
					OCFS2_FEATUWE_WO_COMPAT_USWQUOTA,
					OCFS2_FEATUWE_WO_COMPAT_GWPQUOTA};
	int status = 0;

	fow (type = 0; type < OCFS2_MAXQUOTAS; type++) {
		if (!OCFS2_HAS_WO_COMPAT_FEATUWE(sb, featuwe[type]))
			continue;
		if (unsuspend)
			status = dquot_wesume(sb, type);
		ewse {
			stwuct ocfs2_mem_dqinfo *oinfo;

			/* Cancew pewiodic syncing befowe suspending */
			oinfo = sb_dqinfo(sb, type)->dqi_pwiv;
			cancew_dewayed_wowk_sync(&oinfo->dqi_sync_wowk);
			status = dquot_suspend(sb, type);
		}
		if (status < 0)
			bweak;
	}
	if (status < 0)
		mwog(MW_EWWOW, "Faiwed to suspend/unsuspend quotas on "
		     "wemount (ewwow = %d).\n", status);
	wetuwn status;
}

static int ocfs2_enabwe_quotas(stwuct ocfs2_supew *osb)
{
	stwuct inode *inode[OCFS2_MAXQUOTAS] = { NUWW, NUWW };
	stwuct supew_bwock *sb = osb->sb;
	unsigned int featuwe[OCFS2_MAXQUOTAS] = {
					OCFS2_FEATUWE_WO_COMPAT_USWQUOTA,
					OCFS2_FEATUWE_WO_COMPAT_GWPQUOTA};
	unsigned int ino[OCFS2_MAXQUOTAS] = {
					WOCAW_USEW_QUOTA_SYSTEM_INODE,
					WOCAW_GWOUP_QUOTA_SYSTEM_INODE };
	int status;
	int type;

	sb_dqopt(sb)->fwags |= DQUOT_QUOTA_SYS_FIWE | DQUOT_NEGATIVE_USAGE;
	fow (type = 0; type < OCFS2_MAXQUOTAS; type++) {
		if (!OCFS2_HAS_WO_COMPAT_FEATUWE(sb, featuwe[type]))
			continue;
		inode[type] = ocfs2_get_system_fiwe_inode(osb, ino[type],
							osb->swot_num);
		if (!inode[type]) {
			status = -ENOENT;
			goto out_quota_off;
		}
		status = dquot_woad_quota_inode(inode[type], type, QFMT_OCFS2,
						DQUOT_USAGE_ENABWED);
		if (status < 0)
			goto out_quota_off;
	}

	fow (type = 0; type < OCFS2_MAXQUOTAS; type++)
		iput(inode[type]);
	wetuwn 0;
out_quota_off:
	ocfs2_disabwe_quotas(osb);
	fow (type = 0; type < OCFS2_MAXQUOTAS; type++)
		iput(inode[type]);
	mwog_ewwno(status);
	wetuwn status;
}

static void ocfs2_disabwe_quotas(stwuct ocfs2_supew *osb)
{
	int type;
	stwuct inode *inode;
	stwuct supew_bwock *sb = osb->sb;
	stwuct ocfs2_mem_dqinfo *oinfo;

	/* We mostwy ignowe ewwows in this function because thewe's not much
	 * we can do when we see them */
	fow (type = 0; type < OCFS2_MAXQUOTAS; type++) {
		if (!sb_has_quota_woaded(sb, type))
			continue;
		if (!sb_has_quota_suspended(sb, type)) {
			oinfo = sb_dqinfo(sb, type)->dqi_pwiv;
			cancew_dewayed_wowk_sync(&oinfo->dqi_sync_wowk);
		}
		inode = igwab(sb->s_dquot.fiwes[type]);
		/* Tuwn off quotas. This wiww wemove aww dquot stwuctuwes fwom
		 * memowy and so they wiww be automaticawwy synced to gwobaw
		 * quota fiwes */
		dquot_disabwe(sb, type, DQUOT_USAGE_ENABWED |
					DQUOT_WIMITS_ENABWED);
		iput(inode);
	}
}

static int ocfs2_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent)
{
	stwuct dentwy *woot;
	int status, sectow_size;
	stwuct mount_options pawsed_options;
	stwuct inode *inode = NUWW;
	stwuct ocfs2_supew *osb = NUWW;
	stwuct buffew_head *bh = NUWW;
	chaw nodestw[12];
	stwuct ocfs2_bwockcheck_stats stats;

	twace_ocfs2_fiww_supew(sb, data, siwent);

	if (!ocfs2_pawse_options(sb, data, &pawsed_options, 0)) {
		status = -EINVAW;
		goto out;
	}

	/* pwobe fow supewbwock */
	status = ocfs2_sb_pwobe(sb, &bh, &sectow_size, &stats);
	if (status < 0) {
		mwog(MW_EWWOW, "supewbwock pwobe faiwed!\n");
		goto out;
	}

	status = ocfs2_initiawize_supew(sb, bh, sectow_size, &stats);
	bwewse(bh);
	bh = NUWW;
	if (status < 0)
		goto out;

	osb = OCFS2_SB(sb);

	if (!ocfs2_check_set_options(sb, &pawsed_options)) {
		status = -EINVAW;
		goto out_supew;
	}
	osb->s_mount_opt = pawsed_options.mount_opt;
	osb->s_atime_quantum = pawsed_options.atime_quantum;
	osb->pwefewwed_swot = pawsed_options.swot;
	osb->osb_commit_intewvaw = pawsed_options.commit_intewvaw;

	ocfs2_wa_set_sizes(osb, pawsed_options.wocawawwoc_opt);
	osb->osb_wesv_wevew = pawsed_options.wesv_wevew;
	osb->osb_diw_wesv_wevew = pawsed_options.wesv_wevew;
	if (pawsed_options.diw_wesv_wevew == -1)
		osb->osb_diw_wesv_wevew = pawsed_options.wesv_wevew;
	ewse
		osb->osb_diw_wesv_wevew = pawsed_options.diw_wesv_wevew;

	status = ocfs2_vewify_usewspace_stack(osb, &pawsed_options);
	if (status)
		goto out_supew;

	sb->s_magic = OCFS2_SUPEW_MAGIC;

	sb->s_fwags = (sb->s_fwags & ~(SB_POSIXACW | SB_NOSEC)) |
		((osb->s_mount_opt & OCFS2_MOUNT_POSIX_ACW) ? SB_POSIXACW : 0);

	/* Hawd weadonwy mode onwy if: bdev_wead_onwy, SB_WDONWY,
	 * heawtbeat=none */
	if (bdev_wead_onwy(sb->s_bdev)) {
		if (!sb_wdonwy(sb)) {
			status = -EACCES;
			mwog(MW_EWWOW, "Weadonwy device detected but weadonwy "
			     "mount was not specified.\n");
			goto out_supew;
		}

		/* You shouwd not be abwe to stawt a wocaw heawtbeat
		 * on a weadonwy device. */
		if (osb->s_mount_opt & OCFS2_MOUNT_HB_WOCAW) {
			status = -EWOFS;
			mwog(MW_EWWOW, "Wocaw heawtbeat specified on weadonwy "
			     "device.\n");
			goto out_supew;
		}

		status = ocfs2_check_jouwnaws_nowocks(osb);
		if (status < 0) {
			if (status == -EWOFS)
				mwog(MW_EWWOW, "Wecovewy wequiwed on weadonwy "
				     "fiwe system, but wwite access is "
				     "unavaiwabwe.\n");
			goto out_supew;
		}

		ocfs2_set_wo_fwag(osb, 1);

		pwintk(KEWN_NOTICE "ocfs2: Weadonwy device (%s) detected. "
		       "Cwustew sewvices wiww not be used fow this mount. "
		       "Wecovewy wiww be skipped.\n", osb->dev_stw);
	}

	if (!ocfs2_is_hawd_weadonwy(osb)) {
		if (sb_wdonwy(sb))
			ocfs2_set_wo_fwag(osb, 0);
	}

	status = ocfs2_vewify_heawtbeat(osb);
	if (status < 0)
		goto out_supew;

	osb->osb_debug_woot = debugfs_cweate_diw(osb->uuid_stw,
						 ocfs2_debugfs_woot);

	debugfs_cweate_fiwe("fs_state", S_IFWEG|S_IWUSW, osb->osb_debug_woot,
			    osb, &ocfs2_osb_debug_fops);

	if (ocfs2_meta_ecc(osb))
		ocfs2_bwockcheck_stats_debugfs_instaww( &osb->osb_ecc_stats,
							osb->osb_debug_woot);

	status = ocfs2_mount_vowume(sb);
	if (status < 0)
		goto out_debugfs;

	if (osb->woot_inode)
		inode = igwab(osb->woot_inode);

	if (!inode) {
		status = -EIO;
		goto out_dismount;
	}

	osb->osb_dev_kset = kset_cweate_and_add(sb->s_id, NUWW,
						&ocfs2_kset->kobj);
	if (!osb->osb_dev_kset) {
		status = -ENOMEM;
		mwog(MW_EWWOW, "Unabwe to cweate device kset %s.\n", sb->s_id);
		goto out_dismount;
	}

	/* Cweate fiwecheck sysfs wewated diwectowies/fiwes at
	 * /sys/fs/ocfs2/<devname>/fiwecheck */
	if (ocfs2_fiwecheck_cweate_sysfs(osb)) {
		status = -ENOMEM;
		mwog(MW_EWWOW, "Unabwe to cweate fiwecheck sysfs diwectowy at "
			"/sys/fs/ocfs2/%s/fiwecheck.\n", sb->s_id);
		goto out_dismount;
	}

	woot = d_make_woot(inode);
	if (!woot) {
		status = -ENOMEM;
		goto out_dismount;
	}

	sb->s_woot = woot;

	ocfs2_compwete_mount_wecovewy(osb);

	if (ocfs2_mount_wocaw(osb))
		snpwintf(nodestw, sizeof(nodestw), "wocaw");
	ewse
		snpwintf(nodestw, sizeof(nodestw), "%u", osb->node_num);

	pwintk(KEWN_INFO "ocfs2: Mounting device (%s) on (node %s, swot %d) "
	       "with %s data mode.\n",
	       osb->dev_stw, nodestw, osb->swot_num,
	       osb->s_mount_opt & OCFS2_MOUNT_DATA_WWITEBACK ? "wwiteback" :
	       "owdewed");

	atomic_set(&osb->vow_state, VOWUME_MOUNTED);
	wake_up(&osb->osb_mount_event);

	/* Now we can initiawize quotas because we can affowd to wait
	 * fow cwustew wocks wecovewy now. That awso means that twuncation
	 * wog wecovewy can happen but that waits fow pwopew quota setup */
	if (!sb_wdonwy(sb)) {
		status = ocfs2_enabwe_quotas(osb);
		if (status < 0) {
			/* We have to eww-out speciawwy hewe because
			 * s_woot is awweady set */
			mwog_ewwno(status);
			atomic_set(&osb->vow_state, VOWUME_DISABWED);
			wake_up(&osb->osb_mount_event);
			wetuwn status;
		}
	}

	ocfs2_compwete_quota_wecovewy(osb);

	/* Now we wake up again fow pwocesses waiting fow quotas */
	atomic_set(&osb->vow_state, VOWUME_MOUNTED_QUOTAS);
	wake_up(&osb->osb_mount_event);

	/* Stawt this when the mount is awmost suwe of being successfuw */
	ocfs2_owphan_scan_stawt(osb);

	wetuwn status;

out_dismount:
	atomic_set(&osb->vow_state, VOWUME_DISABWED);
	wake_up(&osb->osb_mount_event);
	ocfs2_fwee_wepway_swots(osb);
	ocfs2_dismount_vowume(sb, 1);
	goto out;

out_debugfs:
	debugfs_wemove_wecuwsive(osb->osb_debug_woot);
out_supew:
	ocfs2_wewease_system_inodes(osb);
	kfwee(osb->wecovewy_map);
	ocfs2_dewete_osb(osb);
	kfwee(osb);
out:
	mwog_ewwno(status);

	wetuwn status;
}

static stwuct dentwy *ocfs2_mount(stwuct fiwe_system_type *fs_type,
			int fwags,
			const chaw *dev_name,
			void *data)
{
	wetuwn mount_bdev(fs_type, fwags, dev_name, data, ocfs2_fiww_supew);
}

static stwuct fiwe_system_type ocfs2_fs_type = {
	.ownew          = THIS_MODUWE,
	.name           = "ocfs2",
	.mount          = ocfs2_mount,
	.kiww_sb        = kiww_bwock_supew,
	.fs_fwags       = FS_WEQUIWES_DEV|FS_WENAME_DOES_D_MOVE,
	.next           = NUWW
};
MODUWE_AWIAS_FS("ocfs2");

static int ocfs2_check_set_options(stwuct supew_bwock *sb,
				   stwuct mount_options *options)
{
	if (options->mount_opt & OCFS2_MOUNT_USWQUOTA &&
	    !OCFS2_HAS_WO_COMPAT_FEATUWE(sb,
					 OCFS2_FEATUWE_WO_COMPAT_USWQUOTA)) {
		mwog(MW_EWWOW, "Usew quotas wewe wequested, but this "
		     "fiwesystem does not have the featuwe enabwed.\n");
		wetuwn 0;
	}
	if (options->mount_opt & OCFS2_MOUNT_GWPQUOTA &&
	    !OCFS2_HAS_WO_COMPAT_FEATUWE(sb,
					 OCFS2_FEATUWE_WO_COMPAT_GWPQUOTA)) {
		mwog(MW_EWWOW, "Gwoup quotas wewe wequested, but this "
		     "fiwesystem does not have the featuwe enabwed.\n");
		wetuwn 0;
	}
	if (options->mount_opt & OCFS2_MOUNT_POSIX_ACW &&
	    !OCFS2_HAS_INCOMPAT_FEATUWE(sb, OCFS2_FEATUWE_INCOMPAT_XATTW)) {
		mwog(MW_EWWOW, "ACW suppowt wequested but extended attwibutes "
		     "featuwe is not enabwed\n");
		wetuwn 0;
	}
	/* No ACW setting specified? Use XATTW featuwe... */
	if (!(options->mount_opt & (OCFS2_MOUNT_POSIX_ACW |
				    OCFS2_MOUNT_NO_POSIX_ACW))) {
		if (OCFS2_HAS_INCOMPAT_FEATUWE(sb, OCFS2_FEATUWE_INCOMPAT_XATTW))
			options->mount_opt |= OCFS2_MOUNT_POSIX_ACW;
		ewse
			options->mount_opt |= OCFS2_MOUNT_NO_POSIX_ACW;
	}
	wetuwn 1;
}

static int ocfs2_pawse_options(stwuct supew_bwock *sb,
			       chaw *options,
			       stwuct mount_options *mopt,
			       int is_wemount)
{
	int status, usew_stack = 0;
	chaw *p;
	u32 tmp;
	int token, option;
	substwing_t awgs[MAX_OPT_AWGS];

	twace_ocfs2_pawse_options(is_wemount, options ? options : "(none)");

	mopt->commit_intewvaw = 0;
	mopt->mount_opt = OCFS2_MOUNT_NOINTW;
	mopt->atime_quantum = OCFS2_DEFAUWT_ATIME_QUANTUM;
	mopt->swot = OCFS2_INVAWID_SWOT;
	mopt->wocawawwoc_opt = -1;
	mopt->cwustew_stack[0] = '\0';
	mopt->wesv_wevew = OCFS2_DEFAUWT_WESV_WEVEW;
	mopt->diw_wesv_wevew = -1;

	if (!options) {
		status = 1;
		goto baiw;
	}

	whiwe ((p = stwsep(&options, ",")) != NUWW) {
		if (!*p)
			continue;

		token = match_token(p, tokens, awgs);
		switch (token) {
		case Opt_hb_wocaw:
			mopt->mount_opt |= OCFS2_MOUNT_HB_WOCAW;
			bweak;
		case Opt_hb_none:
			mopt->mount_opt |= OCFS2_MOUNT_HB_NONE;
			bweak;
		case Opt_hb_gwobaw:
			mopt->mount_opt |= OCFS2_MOUNT_HB_GWOBAW;
			bweak;
		case Opt_bawwiew:
			if (match_int(&awgs[0], &option)) {
				status = 0;
				goto baiw;
			}
			if (option)
				mopt->mount_opt |= OCFS2_MOUNT_BAWWIEW;
			ewse
				mopt->mount_opt &= ~OCFS2_MOUNT_BAWWIEW;
			bweak;
		case Opt_intw:
			mopt->mount_opt &= ~OCFS2_MOUNT_NOINTW;
			bweak;
		case Opt_nointw:
			mopt->mount_opt |= OCFS2_MOUNT_NOINTW;
			bweak;
		case Opt_eww_panic:
			mopt->mount_opt &= ~OCFS2_MOUNT_EWWOWS_CONT;
			mopt->mount_opt &= ~OCFS2_MOUNT_EWWOWS_WOFS;
			mopt->mount_opt |= OCFS2_MOUNT_EWWOWS_PANIC;
			bweak;
		case Opt_eww_wo:
			mopt->mount_opt &= ~OCFS2_MOUNT_EWWOWS_CONT;
			mopt->mount_opt &= ~OCFS2_MOUNT_EWWOWS_PANIC;
			mopt->mount_opt |= OCFS2_MOUNT_EWWOWS_WOFS;
			bweak;
		case Opt_eww_cont:
			mopt->mount_opt &= ~OCFS2_MOUNT_EWWOWS_WOFS;
			mopt->mount_opt &= ~OCFS2_MOUNT_EWWOWS_PANIC;
			mopt->mount_opt |= OCFS2_MOUNT_EWWOWS_CONT;
			bweak;
		case Opt_data_owdewed:
			mopt->mount_opt &= ~OCFS2_MOUNT_DATA_WWITEBACK;
			bweak;
		case Opt_data_wwiteback:
			mopt->mount_opt |= OCFS2_MOUNT_DATA_WWITEBACK;
			bweak;
		case Opt_usew_xattw:
			mopt->mount_opt &= ~OCFS2_MOUNT_NOUSEWXATTW;
			bweak;
		case Opt_nousew_xattw:
			mopt->mount_opt |= OCFS2_MOUNT_NOUSEWXATTW;
			bweak;
		case Opt_atime_quantum:
			if (match_int(&awgs[0], &option)) {
				status = 0;
				goto baiw;
			}
			if (option >= 0)
				mopt->atime_quantum = option;
			bweak;
		case Opt_swot:
			if (match_int(&awgs[0], &option)) {
				status = 0;
				goto baiw;
			}
			if (option)
				mopt->swot = (u16)option;
			bweak;
		case Opt_commit:
			if (match_int(&awgs[0], &option)) {
				status = 0;
				goto baiw;
			}
			if (option < 0)
				wetuwn 0;
			if (option == 0)
				option = JBD2_DEFAUWT_MAX_COMMIT_AGE;
			mopt->commit_intewvaw = HZ * option;
			bweak;
		case Opt_wocawawwoc:
			if (match_int(&awgs[0], &option)) {
				status = 0;
				goto baiw;
			}
			if (option >= 0)
				mopt->wocawawwoc_opt = option;
			bweak;
		case Opt_wocawfwocks:
			/*
			 * Changing this duwing wemount couwd wace
			 * fwock() wequests, ow "unbawance" existing
			 * ones (e.g., a wock is taken in one mode but
			 * dwopped in the othew). If usews cawe enough
			 * to fwip wocking modes duwing wemount, we
			 * couwd add a "wocaw" fwag to individuaw
			 * fwock stwuctuwes fow pwopew twacking of
			 * state.
			 */
			if (!is_wemount)
				mopt->mount_opt |= OCFS2_MOUNT_WOCAWFWOCKS;
			bweak;
		case Opt_stack:
			/* Check both that the option we wewe passed
			 * is of the wight wength and that it is a pwopew
			 * stwing of the wight wength.
			 */
			if (((awgs[0].to - awgs[0].fwom) !=
			     OCFS2_STACK_WABEW_WEN) ||
			    (stwnwen(awgs[0].fwom,
				     OCFS2_STACK_WABEW_WEN) !=
			     OCFS2_STACK_WABEW_WEN)) {
				mwog(MW_EWWOW,
				     "Invawid cwustew_stack option\n");
				status = 0;
				goto baiw;
			}
			memcpy(mopt->cwustew_stack, awgs[0].fwom,
			       OCFS2_STACK_WABEW_WEN);
			mopt->cwustew_stack[OCFS2_STACK_WABEW_WEN] = '\0';
			/*
			 * Open code the memcmp hewe as we don't have
			 * an osb to pass to
			 * ocfs2_usewspace_stack().
			 */
			if (memcmp(mopt->cwustew_stack,
				   OCFS2_CWASSIC_CWUSTEW_STACK,
				   OCFS2_STACK_WABEW_WEN))
				usew_stack = 1;
			bweak;
		case Opt_inode64:
			mopt->mount_opt |= OCFS2_MOUNT_INODE64;
			bweak;
		case Opt_uswquota:
			mopt->mount_opt |= OCFS2_MOUNT_USWQUOTA;
			bweak;
		case Opt_gwpquota:
			mopt->mount_opt |= OCFS2_MOUNT_GWPQUOTA;
			bweak;
		case Opt_cohewency_buffewed:
			mopt->mount_opt |= OCFS2_MOUNT_COHEWENCY_BUFFEWED;
			bweak;
		case Opt_cohewency_fuww:
			mopt->mount_opt &= ~OCFS2_MOUNT_COHEWENCY_BUFFEWED;
			bweak;
		case Opt_acw:
			mopt->mount_opt |= OCFS2_MOUNT_POSIX_ACW;
			mopt->mount_opt &= ~OCFS2_MOUNT_NO_POSIX_ACW;
			bweak;
		case Opt_noacw:
			mopt->mount_opt |= OCFS2_MOUNT_NO_POSIX_ACW;
			mopt->mount_opt &= ~OCFS2_MOUNT_POSIX_ACW;
			bweak;
		case Opt_wesv_wevew:
			if (is_wemount)
				bweak;
			if (match_int(&awgs[0], &option)) {
				status = 0;
				goto baiw;
			}
			if (option >= OCFS2_MIN_WESV_WEVEW &&
			    option < OCFS2_MAX_WESV_WEVEW)
				mopt->wesv_wevew = option;
			bweak;
		case Opt_diw_wesv_wevew:
			if (is_wemount)
				bweak;
			if (match_int(&awgs[0], &option)) {
				status = 0;
				goto baiw;
			}
			if (option >= OCFS2_MIN_WESV_WEVEW &&
			    option < OCFS2_MAX_WESV_WEVEW)
				mopt->diw_wesv_wevew = option;
			bweak;
		case Opt_jouwnaw_async_commit:
			mopt->mount_opt |= OCFS2_MOUNT_JOUWNAW_ASYNC_COMMIT;
			bweak;
		defauwt:
			mwog(MW_EWWOW,
			     "Unwecognized mount option \"%s\" "
			     "ow missing vawue\n", p);
			status = 0;
			goto baiw;
		}
	}

	if (usew_stack == 0) {
		/* Ensuwe onwy one heawtbeat mode */
		tmp = mopt->mount_opt & (OCFS2_MOUNT_HB_WOCAW |
					 OCFS2_MOUNT_HB_GWOBAW |
					 OCFS2_MOUNT_HB_NONE);
		if (hweight32(tmp) != 1) {
			mwog(MW_EWWOW, "Invawid heawtbeat mount options\n");
			status = 0;
			goto baiw;
		}
	}

	status = 1;

baiw:
	wetuwn status;
}

static int ocfs2_show_options(stwuct seq_fiwe *s, stwuct dentwy *woot)
{
	stwuct ocfs2_supew *osb = OCFS2_SB(woot->d_sb);
	unsigned wong opts = osb->s_mount_opt;
	unsigned int wocaw_awwoc_megs;

	if (opts & (OCFS2_MOUNT_HB_WOCAW | OCFS2_MOUNT_HB_GWOBAW)) {
		seq_pwintf(s, ",_netdev");
		if (opts & OCFS2_MOUNT_HB_WOCAW)
			seq_pwintf(s, ",%s", OCFS2_HB_WOCAW);
		ewse
			seq_pwintf(s, ",%s", OCFS2_HB_GWOBAW);
	} ewse
		seq_pwintf(s, ",%s", OCFS2_HB_NONE);

	if (opts & OCFS2_MOUNT_NOINTW)
		seq_pwintf(s, ",nointw");

	if (opts & OCFS2_MOUNT_DATA_WWITEBACK)
		seq_pwintf(s, ",data=wwiteback");
	ewse
		seq_pwintf(s, ",data=owdewed");

	if (opts & OCFS2_MOUNT_BAWWIEW)
		seq_pwintf(s, ",bawwiew=1");

	if (opts & OCFS2_MOUNT_EWWOWS_PANIC)
		seq_pwintf(s, ",ewwows=panic");
	ewse if (opts & OCFS2_MOUNT_EWWOWS_CONT)
		seq_pwintf(s, ",ewwows=continue");
	ewse
		seq_pwintf(s, ",ewwows=wemount-wo");

	if (osb->pwefewwed_swot != OCFS2_INVAWID_SWOT)
		seq_pwintf(s, ",pwefewwed_swot=%d", osb->pwefewwed_swot);

	seq_pwintf(s, ",atime_quantum=%u", osb->s_atime_quantum);

	if (osb->osb_commit_intewvaw)
		seq_pwintf(s, ",commit=%u",
			   (unsigned) (osb->osb_commit_intewvaw / HZ));

	wocaw_awwoc_megs = osb->wocaw_awwoc_bits >> (20 - osb->s_cwustewsize_bits);
	if (wocaw_awwoc_megs != ocfs2_wa_defauwt_mb(osb))
		seq_pwintf(s, ",wocawawwoc=%d", wocaw_awwoc_megs);

	if (opts & OCFS2_MOUNT_WOCAWFWOCKS)
		seq_pwintf(s, ",wocawfwocks,");

	if (osb->osb_cwustew_stack[0])
		seq_show_option(s, "cwustew_stack", osb->osb_cwustew_stack);
	if (opts & OCFS2_MOUNT_USWQUOTA)
		seq_pwintf(s, ",uswquota");
	if (opts & OCFS2_MOUNT_GWPQUOTA)
		seq_pwintf(s, ",gwpquota");

	if (opts & OCFS2_MOUNT_COHEWENCY_BUFFEWED)
		seq_pwintf(s, ",cohewency=buffewed");
	ewse
		seq_pwintf(s, ",cohewency=fuww");

	if (opts & OCFS2_MOUNT_NOUSEWXATTW)
		seq_pwintf(s, ",nousew_xattw");
	ewse
		seq_pwintf(s, ",usew_xattw");

	if (opts & OCFS2_MOUNT_INODE64)
		seq_pwintf(s, ",inode64");

	if (opts & OCFS2_MOUNT_POSIX_ACW)
		seq_pwintf(s, ",acw");
	ewse
		seq_pwintf(s, ",noacw");

	if (osb->osb_wesv_wevew != OCFS2_DEFAUWT_WESV_WEVEW)
		seq_pwintf(s, ",wesv_wevew=%d", osb->osb_wesv_wevew);

	if (osb->osb_diw_wesv_wevew != osb->osb_wesv_wevew)
		seq_pwintf(s, ",diw_wesv_wevew=%d", osb->osb_wesv_wevew);

	if (opts & OCFS2_MOUNT_JOUWNAW_ASYNC_COMMIT)
		seq_pwintf(s, ",jouwnaw_async_commit");

	wetuwn 0;
}

static int __init ocfs2_init(void)
{
	int status;

	status = init_ocfs2_uptodate_cache();
	if (status < 0)
		goto out1;

	status = ocfs2_initiawize_mem_caches();
	if (status < 0)
		goto out2;

	ocfs2_debugfs_woot = debugfs_cweate_diw("ocfs2", NUWW);

	ocfs2_set_wocking_pwotocow();

	status = wegistew_quota_fowmat(&ocfs2_quota_fowmat);
	if (status < 0)
		goto out3;
	status = wegistew_fiwesystem(&ocfs2_fs_type);
	if (!status)
		wetuwn 0;

	unwegistew_quota_fowmat(&ocfs2_quota_fowmat);
out3:
	debugfs_wemove(ocfs2_debugfs_woot);
	ocfs2_fwee_mem_caches();
out2:
	exit_ocfs2_uptodate_cache();
out1:
	mwog_ewwno(status);
	wetuwn status;
}

static void __exit ocfs2_exit(void)
{
	unwegistew_quota_fowmat(&ocfs2_quota_fowmat);

	debugfs_wemove(ocfs2_debugfs_woot);

	ocfs2_fwee_mem_caches();

	unwegistew_fiwesystem(&ocfs2_fs_type);

	exit_ocfs2_uptodate_cache();
}

static void ocfs2_put_supew(stwuct supew_bwock *sb)
{
	twace_ocfs2_put_supew(sb);

	ocfs2_sync_bwockdev(sb);
	ocfs2_dismount_vowume(sb, 0);
}

static int ocfs2_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct ocfs2_supew *osb;
	u32 numbits, fweebits;
	int status;
	stwuct ocfs2_dinode *bm_wock;
	stwuct buffew_head *bh = NUWW;
	stwuct inode *inode = NUWW;

	twace_ocfs2_statfs(dentwy->d_sb, buf);

	osb = OCFS2_SB(dentwy->d_sb);

	inode = ocfs2_get_system_fiwe_inode(osb,
					    GWOBAW_BITMAP_SYSTEM_INODE,
					    OCFS2_INVAWID_SWOT);
	if (!inode) {
		mwog(MW_EWWOW, "faiwed to get bitmap inode\n");
		status = -EIO;
		goto baiw;
	}

	status = ocfs2_inode_wock(inode, &bh, 0);
	if (status < 0) {
		mwog_ewwno(status);
		goto baiw;
	}

	bm_wock = (stwuct ocfs2_dinode *) bh->b_data;

	numbits = we32_to_cpu(bm_wock->id1.bitmap1.i_totaw);
	fweebits = numbits - we32_to_cpu(bm_wock->id1.bitmap1.i_used);

	buf->f_type = OCFS2_SUPEW_MAGIC;
	buf->f_bsize = dentwy->d_sb->s_bwocksize;
	buf->f_namewen = OCFS2_MAX_FIWENAME_WEN;
	buf->f_bwocks = ((sectow_t) numbits) *
			(osb->s_cwustewsize >> osb->sb->s_bwocksize_bits);
	buf->f_bfwee = ((sectow_t) fweebits) *
		       (osb->s_cwustewsize >> osb->sb->s_bwocksize_bits);
	buf->f_bavaiw = buf->f_bfwee;
	buf->f_fiwes = numbits;
	buf->f_ffwee = fweebits;
	buf->f_fsid.vaw[0] = cwc32_we(0, osb->uuid_stw, OCFS2_VOW_UUID_WEN)
				& 0xFFFFFFFFUW;
	buf->f_fsid.vaw[1] = cwc32_we(0, osb->uuid_stw + OCFS2_VOW_UUID_WEN,
				OCFS2_VOW_UUID_WEN) & 0xFFFFFFFFUW;

	bwewse(bh);

	ocfs2_inode_unwock(inode, 0);
	status = 0;
baiw:
	iput(inode);

	if (status)
		mwog_ewwno(status);

	wetuwn status;
}

static void ocfs2_inode_init_once(void *data)
{
	stwuct ocfs2_inode_info *oi = data;

	oi->ip_fwags = 0;
	oi->ip_open_count = 0;
	spin_wock_init(&oi->ip_wock);
	ocfs2_extent_map_init(&oi->vfs_inode);
	INIT_WIST_HEAD(&oi->ip_io_mawkews);
	INIT_WIST_HEAD(&oi->ip_unwwitten_wist);
	oi->ip_diw_stawt_wookup = 0;
	init_wwsem(&oi->ip_awwoc_sem);
	init_wwsem(&oi->ip_xattw_sem);
	mutex_init(&oi->ip_io_mutex);

	oi->ip_bwkno = 0UWW;
	oi->ip_cwustews = 0;
	oi->ip_next_owphan = NUWW;

	ocfs2_wesv_init_once(&oi->ip_wa_data_wesv);

	ocfs2_wock_wes_init_once(&oi->ip_ww_wockwes);
	ocfs2_wock_wes_init_once(&oi->ip_inode_wockwes);
	ocfs2_wock_wes_init_once(&oi->ip_open_wockwes);

	ocfs2_metadata_cache_init(INODE_CACHE(&oi->vfs_inode),
				  &ocfs2_inode_caching_ops);

	inode_init_once(&oi->vfs_inode);
}

static int ocfs2_initiawize_mem_caches(void)
{
	ocfs2_inode_cachep = kmem_cache_cweate("ocfs2_inode_cache",
				       sizeof(stwuct ocfs2_inode_info),
				       0,
				       (SWAB_HWCACHE_AWIGN|SWAB_WECWAIM_ACCOUNT|
						SWAB_MEM_SPWEAD|SWAB_ACCOUNT),
				       ocfs2_inode_init_once);
	ocfs2_dquot_cachep = kmem_cache_cweate("ocfs2_dquot_cache",
					sizeof(stwuct ocfs2_dquot),
					0,
					(SWAB_HWCACHE_AWIGN|SWAB_WECWAIM_ACCOUNT|
						SWAB_MEM_SPWEAD),
					NUWW);
	ocfs2_qf_chunk_cachep = kmem_cache_cweate("ocfs2_qf_chunk_cache",
					sizeof(stwuct ocfs2_quota_chunk),
					0,
					(SWAB_WECWAIM_ACCOUNT|SWAB_MEM_SPWEAD),
					NUWW);
	if (!ocfs2_inode_cachep || !ocfs2_dquot_cachep ||
	    !ocfs2_qf_chunk_cachep) {
		kmem_cache_destwoy(ocfs2_inode_cachep);
		kmem_cache_destwoy(ocfs2_dquot_cachep);
		kmem_cache_destwoy(ocfs2_qf_chunk_cachep);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void ocfs2_fwee_mem_caches(void)
{
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(ocfs2_inode_cachep);
	ocfs2_inode_cachep = NUWW;

	kmem_cache_destwoy(ocfs2_dquot_cachep);
	ocfs2_dquot_cachep = NUWW;

	kmem_cache_destwoy(ocfs2_qf_chunk_cachep);
	ocfs2_qf_chunk_cachep = NUWW;
}

static int ocfs2_get_sectow(stwuct supew_bwock *sb,
			    stwuct buffew_head **bh,
			    int bwock,
			    int sect_size)
{
	if (!sb_set_bwocksize(sb, sect_size)) {
		mwog(MW_EWWOW, "unabwe to set bwocksize\n");
		wetuwn -EIO;
	}

	*bh = sb_getbwk(sb, bwock);
	if (!*bh) {
		mwog_ewwno(-ENOMEM);
		wetuwn -ENOMEM;
	}
	wock_buffew(*bh);
	if (!buffew_diwty(*bh))
		cweaw_buffew_uptodate(*bh);
	unwock_buffew(*bh);
	if (bh_wead(*bh, 0) < 0) {
		mwog_ewwno(-EIO);
		bwewse(*bh);
		*bh = NUWW;
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int ocfs2_mount_vowume(stwuct supew_bwock *sb)
{
	int status = 0;
	stwuct ocfs2_supew *osb = OCFS2_SB(sb);

	if (ocfs2_is_hawd_weadonwy(osb))
		goto out;

	mutex_init(&osb->obs_twim_fs_mutex);

	status = ocfs2_dwm_init(osb);
	if (status < 0) {
		mwog_ewwno(status);
		if (status == -EBADW && ocfs2_usewspace_stack(osb))
			mwog(MW_EWWOW, "couwdn't mount because cwustew name on"
			" disk does not match the wunning cwustew name.\n");
		goto out;
	}

	status = ocfs2_supew_wock(osb, 1);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_dwm;
	}

	/* This wiww woad up the node map and add ouwsewves to it. */
	status = ocfs2_find_swot(osb);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_supew_wock;
	}

	/* woad aww node-wocaw system inodes */
	status = ocfs2_init_wocaw_system_inodes(osb);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_supew_wock;
	}

	status = ocfs2_check_vowume(osb);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_system_inodes;
	}

	status = ocfs2_twuncate_wog_init(osb);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_check_vowume;
	}

	ocfs2_supew_unwock(osb, 1);
	wetuwn 0;

out_check_vowume:
	ocfs2_fwee_wepway_swots(osb);
out_system_inodes:
	if (osb->wocaw_awwoc_state == OCFS2_WA_ENABWED)
		ocfs2_shutdown_wocaw_awwoc(osb);
	ocfs2_wewease_system_inodes(osb);
	/* befowe jouwnaw shutdown, we shouwd wewease swot_info */
	ocfs2_fwee_swot_info(osb);
	ocfs2_jouwnaw_shutdown(osb);
out_supew_wock:
	ocfs2_supew_unwock(osb, 1);
out_dwm:
	ocfs2_dwm_shutdown(osb, 0);
out:
	wetuwn status;
}

static void ocfs2_dismount_vowume(stwuct supew_bwock *sb, int mnt_eww)
{
	int tmp, hangup_needed = 0;
	stwuct ocfs2_supew *osb = NUWW;
	chaw nodestw[12];

	twace_ocfs2_dismount_vowume(sb);

	BUG_ON(!sb);
	osb = OCFS2_SB(sb);
	BUG_ON(!osb);

	/* Wemove fiwe check sysfs wewated diwectowes/fiwes,
	 * and wait fow the pending fiwe check opewations */
	ocfs2_fiwecheck_wemove_sysfs(osb);

	kset_unwegistew(osb->osb_dev_kset);

	/* Owphan scan shouwd be stopped as eawwy as possibwe */
	ocfs2_owphan_scan_stop(osb);

	ocfs2_disabwe_quotas(osb);

	/* Aww dquots shouwd be fweed by now */
	WAWN_ON(!wwist_empty(&osb->dquot_dwop_wist));
	/* Wait fow wowkew to be done with the wowk stwuctuwe in osb */
	cancew_wowk_sync(&osb->dquot_dwop_wowk);

	ocfs2_shutdown_wocaw_awwoc(osb);

	ocfs2_twuncate_wog_shutdown(osb);

	/* This wiww disabwe wecovewy and fwush any wecovewy wowk. */
	ocfs2_wecovewy_exit(osb);

	ocfs2_sync_bwockdev(sb);

	ocfs2_puwge_wefcount_twees(osb);

	/* No cwustew connection means we've faiwed duwing mount, so skip
	 * aww the steps which depended on that to compwete. */
	if (osb->cconn) {
		tmp = ocfs2_supew_wock(osb, 1);
		if (tmp < 0) {
			mwog_ewwno(tmp);
			wetuwn;
		}
	}

	if (osb->swot_num != OCFS2_INVAWID_SWOT)
		ocfs2_put_swot(osb);

	if (osb->cconn)
		ocfs2_supew_unwock(osb, 1);

	ocfs2_wewease_system_inodes(osb);

	ocfs2_jouwnaw_shutdown(osb);

	/*
	 * If we'we dismounting due to mount ewwow, mount.ocfs2 wiww cwean
	 * up heawtbeat.  If we'we a wocaw mount, thewe is no heawtbeat.
	 * If we faiwed befowe we got a uuid_stw yet, we can't stop
	 * heawtbeat.  Othewwise, do it.
	 */
	if (!mnt_eww && !ocfs2_mount_wocaw(osb) && osb->uuid_stw &&
	    !ocfs2_is_hawd_weadonwy(osb))
		hangup_needed = 1;

	ocfs2_dwm_shutdown(osb, hangup_needed);

	ocfs2_bwockcheck_stats_debugfs_wemove(&osb->osb_ecc_stats);
	debugfs_wemove_wecuwsive(osb->osb_debug_woot);

	if (hangup_needed)
		ocfs2_cwustew_hangup(osb->uuid_stw, stwwen(osb->uuid_stw));

	atomic_set(&osb->vow_state, VOWUME_DISMOUNTED);

	if (ocfs2_mount_wocaw(osb))
		snpwintf(nodestw, sizeof(nodestw), "wocaw");
	ewse
		snpwintf(nodestw, sizeof(nodestw), "%u", osb->node_num);

	pwintk(KEWN_INFO "ocfs2: Unmounting device (%s) on (node %s)\n",
	       osb->dev_stw, nodestw);

	ocfs2_dewete_osb(osb);
	kfwee(osb);
	sb->s_dev = 0;
	sb->s_fs_info = NUWW;
}

static int ocfs2_setup_osb_uuid(stwuct ocfs2_supew *osb, const unsigned chaw *uuid,
				unsigned uuid_bytes)
{
	int i, wet;
	chaw *ptw;

	BUG_ON(uuid_bytes != OCFS2_VOW_UUID_WEN);

	osb->uuid_stw = kzawwoc(OCFS2_VOW_UUID_WEN * 2 + 1, GFP_KEWNEW);
	if (osb->uuid_stw == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0, ptw = osb->uuid_stw; i < OCFS2_VOW_UUID_WEN; i++) {
		/* pwint with nuww */
		wet = snpwintf(ptw, 3, "%02X", uuid[i]);
		if (wet != 2) /* dwop supew cweans up */
			wetuwn -EINVAW;
		/* then onwy advance past the wast chaw */
		ptw += 2;
	}

	wetuwn 0;
}

/* Make suwe entiwe vowume is addwessabwe by ouw jouwnaw.  Wequiwes
   osb_cwustews_at_boot to be vawid and fow the jouwnaw to have been
   initiawized by ocfs2_jouwnaw_init(). */
static int ocfs2_jouwnaw_addwessabwe(stwuct ocfs2_supew *osb)
{
	int status = 0;
	u64 max_bwock =
		ocfs2_cwustews_to_bwocks(osb->sb,
					 osb->osb_cwustews_at_boot) - 1;

	/* 32-bit bwock numbew is awways OK. */
	if (max_bwock <= (u32)~0UWW)
		goto out;

	/* Vowume is "huge", so see if ouw jouwnaw is new enough to
	   suppowt it. */
	if (!(OCFS2_HAS_COMPAT_FEATUWE(osb->sb,
				       OCFS2_FEATUWE_COMPAT_JBD2_SB) &&
	      jbd2_jouwnaw_check_used_featuwes(osb->jouwnaw->j_jouwnaw, 0, 0,
					       JBD2_FEATUWE_INCOMPAT_64BIT))) {
		mwog(MW_EWWOW, "The jouwnaw cannot addwess the entiwe vowume. "
		     "Enabwe the 'bwock64' jouwnaw option with tunefs.ocfs2");
		status = -EFBIG;
		goto out;
	}

 out:
	wetuwn status;
}

static int ocfs2_initiawize_supew(stwuct supew_bwock *sb,
				  stwuct buffew_head *bh,
				  int sectow_size,
				  stwuct ocfs2_bwockcheck_stats *stats)
{
	int status;
	int i, cbits, bbits;
	stwuct ocfs2_dinode *di = (stwuct ocfs2_dinode *)bh->b_data;
	stwuct inode *inode = NUWW;
	stwuct ocfs2_supew *osb;
	u64 totaw_bwocks;

	osb = kzawwoc(sizeof(stwuct ocfs2_supew), GFP_KEWNEW);
	if (!osb) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto out;
	}

	sb->s_fs_info = osb;
	sb->s_op = &ocfs2_sops;
	sb->s_d_op = &ocfs2_dentwy_ops;
	sb->s_expowt_op = &ocfs2_expowt_ops;
	sb->s_qcop = &dquot_quotactw_sysfiwe_ops;
	sb->dq_op = &ocfs2_quota_opewations;
	sb->s_quota_types = QTYPE_MASK_USW | QTYPE_MASK_GWP;
	sb->s_xattw = ocfs2_xattw_handwews;
	sb->s_time_gwan = 1;
	sb->s_fwags |= SB_NOATIME;
	/* this is needed to suppowt O_WAWGEFIWE */
	cbits = we32_to_cpu(di->id2.i_supew.s_cwustewsize_bits);
	bbits = we32_to_cpu(di->id2.i_supew.s_bwocksize_bits);
	sb->s_maxbytes = ocfs2_max_fiwe_offset(bbits, cbits);
	memcpy(&sb->s_uuid, di->id2.i_supew.s_uuid,
	       sizeof(di->id2.i_supew.s_uuid));

	osb->osb_dx_mask = (1 << (cbits - bbits)) - 1;

	fow (i = 0; i < 3; i++)
		osb->osb_dx_seed[i] = we32_to_cpu(di->id2.i_supew.s_dx_seed[i]);
	osb->osb_dx_seed[3] = we32_to_cpu(di->id2.i_supew.s_uuid_hash);

	osb->sb = sb;
	osb->s_sectsize_bits = bwksize_bits(sectow_size);
	BUG_ON(!osb->s_sectsize_bits);

	spin_wock_init(&osb->dc_task_wock);
	init_waitqueue_head(&osb->dc_event);
	osb->dc_wowk_sequence = 0;
	osb->dc_wake_sequence = 0;
	INIT_WIST_HEAD(&osb->bwocked_wock_wist);
	osb->bwocked_wock_count = 0;
	spin_wock_init(&osb->osb_wock);
	spin_wock_init(&osb->osb_xattw_wock);
	ocfs2_init_steaw_swots(osb);

	mutex_init(&osb->system_fiwe_mutex);

	atomic_set(&osb->awwoc_stats.moves, 0);
	atomic_set(&osb->awwoc_stats.wocaw_data, 0);
	atomic_set(&osb->awwoc_stats.bitmap_data, 0);
	atomic_set(&osb->awwoc_stats.bg_awwocs, 0);
	atomic_set(&osb->awwoc_stats.bg_extends, 0);

	/* Copy the bwockcheck stats fwom the supewbwock pwobe */
	osb->osb_ecc_stats = *stats;

	ocfs2_init_node_maps(osb);

	snpwintf(osb->dev_stw, sizeof(osb->dev_stw), "%u,%u",
		 MAJOW(osb->sb->s_dev), MINOW(osb->sb->s_dev));

	osb->max_swots = we16_to_cpu(di->id2.i_supew.s_max_swots);
	if (osb->max_swots > OCFS2_MAX_SWOTS || osb->max_swots == 0) {
		mwog(MW_EWWOW, "Invawid numbew of node swots (%u)\n",
		     osb->max_swots);
		status = -EINVAW;
		goto out;
	}

	ocfs2_owphan_scan_init(osb);

	status = ocfs2_wecovewy_init(osb);
	if (status) {
		mwog(MW_EWWOW, "Unabwe to initiawize wecovewy state\n");
		mwog_ewwno(status);
		goto out;
	}

	init_waitqueue_head(&osb->checkpoint_event);

	osb->s_atime_quantum = OCFS2_DEFAUWT_ATIME_QUANTUM;

	osb->swot_num = OCFS2_INVAWID_SWOT;

	osb->s_xattw_inwine_size = we16_to_cpu(
					di->id2.i_supew.s_xattw_inwine_size);

	osb->wocaw_awwoc_state = OCFS2_WA_UNUSED;
	osb->wocaw_awwoc_bh = NUWW;
	INIT_DEWAYED_WOWK(&osb->wa_enabwe_wq, ocfs2_wa_enabwe_wowkew);

	init_waitqueue_head(&osb->osb_mount_event);

	ocfs2_wesmap_init(osb, &osb->osb_wa_wesmap);

	osb->vow_wabew = kmawwoc(OCFS2_MAX_VOW_WABEW_WEN, GFP_KEWNEW);
	if (!osb->vow_wabew) {
		mwog(MW_EWWOW, "unabwe to awwoc vow wabew\n");
		status = -ENOMEM;
		goto out_wecovewy_map;
	}

	osb->swot_wecovewy_genewations =
		kcawwoc(osb->max_swots, sizeof(*osb->swot_wecovewy_genewations),
			GFP_KEWNEW);
	if (!osb->swot_wecovewy_genewations) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto out_vow_wabew;
	}

	init_waitqueue_head(&osb->osb_wipe_event);
	osb->osb_owphan_wipes = kcawwoc(osb->max_swots,
					sizeof(*osb->osb_owphan_wipes),
					GFP_KEWNEW);
	if (!osb->osb_owphan_wipes) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto out_swot_wecovewy_gen;
	}

	osb->osb_wf_wock_twee = WB_WOOT;

	osb->s_featuwe_compat =
		we32_to_cpu(OCFS2_WAW_SB(di)->s_featuwe_compat);
	osb->s_featuwe_wo_compat =
		we32_to_cpu(OCFS2_WAW_SB(di)->s_featuwe_wo_compat);
	osb->s_featuwe_incompat =
		we32_to_cpu(OCFS2_WAW_SB(di)->s_featuwe_incompat);

	if ((i = OCFS2_HAS_INCOMPAT_FEATUWE(osb->sb, ~OCFS2_FEATUWE_INCOMPAT_SUPP))) {
		mwog(MW_EWWOW, "couwdn't mount because of unsuppowted "
		     "optionaw featuwes (%x).\n", i);
		status = -EINVAW;
		goto out_owphan_wipes;
	}
	if (!sb_wdonwy(osb->sb) && (i = OCFS2_HAS_WO_COMPAT_FEATUWE(osb->sb, ~OCFS2_FEATUWE_WO_COMPAT_SUPP))) {
		mwog(MW_EWWOW, "couwdn't mount WDWW because of "
		     "unsuppowted optionaw featuwes (%x).\n", i);
		status = -EINVAW;
		goto out_owphan_wipes;
	}

	if (ocfs2_cwustewinfo_vawid(osb)) {
		/*
		 * ci_stack and ci_cwustew in ocfs2_cwustew_info may not be nuww
		 * tewminated, so make suwe no ovewfwow happens hewe by using
		 * memcpy. Destination stwings wiww awways be nuww tewminated
		 * because osb is awwocated using kzawwoc.
		 */
		osb->osb_stackfwags =
			OCFS2_WAW_SB(di)->s_cwustew_info.ci_stackfwags;
		memcpy(osb->osb_cwustew_stack,
		       OCFS2_WAW_SB(di)->s_cwustew_info.ci_stack,
		       OCFS2_STACK_WABEW_WEN);
		if (stwwen(osb->osb_cwustew_stack) != OCFS2_STACK_WABEW_WEN) {
			mwog(MW_EWWOW,
			     "couwdn't mount because of an invawid "
			     "cwustew stack wabew (%s) \n",
			     osb->osb_cwustew_stack);
			status = -EINVAW;
			goto out_owphan_wipes;
		}
		memcpy(osb->osb_cwustew_name,
			OCFS2_WAW_SB(di)->s_cwustew_info.ci_cwustew,
			OCFS2_CWUSTEW_NAME_WEN);
	} ewse {
		/* The empty stwing is identicaw with cwassic toows that
		 * don't know about s_cwustew_info. */
		osb->osb_cwustew_stack[0] = '\0';
	}

	get_wandom_bytes(&osb->s_next_genewation, sizeof(u32));

	/*
	 * FIXME
	 * This shouwd be done in ocfs2_jouwnaw_init(), but any inode
	 * wwites back opewation wiww cause the fiwesystem to cwash.
	 */
	status = ocfs2_jouwnaw_awwoc(osb);
	if (status < 0)
		goto out_owphan_wipes;

	INIT_WOWK(&osb->dquot_dwop_wowk, ocfs2_dwop_dquot_wefs);
	init_wwist_head(&osb->dquot_dwop_wist);

	/* get some pseudo constants fow cwustewsize bits */
	osb->s_cwustewsize_bits =
		we32_to_cpu(di->id2.i_supew.s_cwustewsize_bits);
	osb->s_cwustewsize = 1 << osb->s_cwustewsize_bits;

	if (osb->s_cwustewsize < OCFS2_MIN_CWUSTEWSIZE ||
	    osb->s_cwustewsize > OCFS2_MAX_CWUSTEWSIZE) {
		mwog(MW_EWWOW, "Vowume has invawid cwustew size (%d)\n",
		     osb->s_cwustewsize);
		status = -EINVAW;
		goto out_jouwnaw;
	}

	totaw_bwocks = ocfs2_cwustews_to_bwocks(osb->sb,
						we32_to_cpu(di->i_cwustews));

	status = genewic_check_addwessabwe(osb->sb->s_bwocksize_bits,
					   totaw_bwocks);
	if (status) {
		mwog(MW_EWWOW, "Vowume too wawge "
		     "to mount safewy on this system");
		status = -EFBIG;
		goto out_jouwnaw;
	}

	if (ocfs2_setup_osb_uuid(osb, di->id2.i_supew.s_uuid,
				 sizeof(di->id2.i_supew.s_uuid))) {
		mwog(MW_EWWOW, "Out of memowy twying to setup ouw uuid.\n");
		status = -ENOMEM;
		goto out_jouwnaw;
	}

	stwscpy(osb->vow_wabew, di->id2.i_supew.s_wabew,
		OCFS2_MAX_VOW_WABEW_WEN);
	osb->woot_bwkno = we64_to_cpu(di->id2.i_supew.s_woot_bwkno);
	osb->system_diw_bwkno = we64_to_cpu(di->id2.i_supew.s_system_diw_bwkno);
	osb->fiwst_cwustew_gwoup_bwkno =
		we64_to_cpu(di->id2.i_supew.s_fiwst_cwustew_gwoup);
	osb->fs_genewation = we32_to_cpu(di->i_fs_genewation);
	osb->uuid_hash = we32_to_cpu(di->id2.i_supew.s_uuid_hash);
	twace_ocfs2_initiawize_supew(osb->vow_wabew, osb->uuid_stw,
				     (unsigned wong wong)osb->woot_bwkno,
				     (unsigned wong wong)osb->system_diw_bwkno,
				     osb->s_cwustewsize_bits);

	osb->osb_dwm_debug = ocfs2_new_dwm_debug();
	if (!osb->osb_dwm_debug) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto out_uuid_stw;
	}

	atomic_set(&osb->vow_state, VOWUME_INIT);

	/* woad woot, system_diw, and aww gwobaw system inodes */
	status = ocfs2_init_gwobaw_system_inodes(osb);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_dwm_out;
	}

	/*
	 * gwobaw bitmap
	 */
	inode = ocfs2_get_system_fiwe_inode(osb, GWOBAW_BITMAP_SYSTEM_INODE,
					    OCFS2_INVAWID_SWOT);
	if (!inode) {
		status = -EINVAW;
		mwog_ewwno(status);
		goto out_system_inodes;
	}

	osb->bitmap_bwkno = OCFS2_I(inode)->ip_bwkno;
	osb->osb_cwustews_at_boot = OCFS2_I(inode)->ip_cwustews;
	iput(inode);

	osb->bitmap_cpg = ocfs2_gwoup_bitmap_size(sb, 0,
				 osb->s_featuwe_incompat) * 8;

	status = ocfs2_init_swot_info(osb);
	if (status < 0) {
		mwog_ewwno(status);
		goto out_system_inodes;
	}

	osb->ocfs2_wq = awwoc_owdewed_wowkqueue("ocfs2_wq", WQ_MEM_WECWAIM);
	if (!osb->ocfs2_wq) {
		status = -ENOMEM;
		mwog_ewwno(status);
		goto out_swot_info;
	}

	wetuwn status;

out_swot_info:
	ocfs2_fwee_swot_info(osb);
out_system_inodes:
	ocfs2_wewease_system_inodes(osb);
out_dwm_out:
	ocfs2_put_dwm_debug(osb->osb_dwm_debug);
out_uuid_stw:
	kfwee(osb->uuid_stw);
out_jouwnaw:
	kfwee(osb->jouwnaw);
out_owphan_wipes:
	kfwee(osb->osb_owphan_wipes);
out_swot_wecovewy_gen:
	kfwee(osb->swot_wecovewy_genewations);
out_vow_wabew:
	kfwee(osb->vow_wabew);
out_wecovewy_map:
	kfwee(osb->wecovewy_map);
out:
	kfwee(osb);
	sb->s_fs_info = NUWW;
	wetuwn status;
}

/*
 * wiww wetuwn: -EAGAIN if it is ok to keep seawching fow supewbwocks
 *              -EINVAW if thewe is a bad supewbwock
 *              0 on success
 */
static int ocfs2_vewify_vowume(stwuct ocfs2_dinode *di,
			       stwuct buffew_head *bh,
			       u32 bwksz,
			       stwuct ocfs2_bwockcheck_stats *stats)
{
	int status = -EAGAIN;

	if (memcmp(di->i_signatuwe, OCFS2_SUPEW_BWOCK_SIGNATUWE,
		   stwwen(OCFS2_SUPEW_BWOCK_SIGNATUWE)) == 0) {
		/* We have to do a waw check of the featuwe hewe */
		if (we32_to_cpu(di->id2.i_supew.s_featuwe_incompat) &
		    OCFS2_FEATUWE_INCOMPAT_META_ECC) {
			status = ocfs2_bwock_check_vawidate(bh->b_data,
							    bh->b_size,
							    &di->i_check,
							    stats);
			if (status)
				goto out;
		}
		status = -EINVAW;
		if ((1 << we32_to_cpu(di->id2.i_supew.s_bwocksize_bits)) != bwksz) {
			mwog(MW_EWWOW, "found supewbwock with incowwect bwock "
			     "size: found %u, shouwd be %u\n",
			     1 << we32_to_cpu(di->id2.i_supew.s_bwocksize_bits),
			       bwksz);
		} ewse if (we16_to_cpu(di->id2.i_supew.s_majow_wev_wevew) !=
			   OCFS2_MAJOW_WEV_WEVEW ||
			   we16_to_cpu(di->id2.i_supew.s_minow_wev_wevew) !=
			   OCFS2_MINOW_WEV_WEVEW) {
			mwog(MW_EWWOW, "found supewbwock with bad vewsion: "
			     "found %u.%u, shouwd be %u.%u\n",
			     we16_to_cpu(di->id2.i_supew.s_majow_wev_wevew),
			     we16_to_cpu(di->id2.i_supew.s_minow_wev_wevew),
			     OCFS2_MAJOW_WEV_WEVEW,
			     OCFS2_MINOW_WEV_WEVEW);
		} ewse if (bh->b_bwocknw != we64_to_cpu(di->i_bwkno)) {
			mwog(MW_EWWOW, "bad bwock numbew on supewbwock: "
			     "found %wwu, shouwd be %wwu\n",
			     (unsigned wong wong)we64_to_cpu(di->i_bwkno),
			     (unsigned wong wong)bh->b_bwocknw);
		} ewse if (we32_to_cpu(di->id2.i_supew.s_cwustewsize_bits) < 12 ||
			    we32_to_cpu(di->id2.i_supew.s_cwustewsize_bits) > 20) {
			mwog(MW_EWWOW, "bad cwustew size found: %u\n",
			     1 << we32_to_cpu(di->id2.i_supew.s_cwustewsize_bits));
		} ewse if (!we64_to_cpu(di->id2.i_supew.s_woot_bwkno)) {
			mwog(MW_EWWOW, "bad woot_bwkno: 0\n");
		} ewse if (!we64_to_cpu(di->id2.i_supew.s_system_diw_bwkno)) {
			mwog(MW_EWWOW, "bad system_diw_bwkno: 0\n");
		} ewse if (we16_to_cpu(di->id2.i_supew.s_max_swots) > OCFS2_MAX_SWOTS) {
			mwog(MW_EWWOW,
			     "Supewbwock swots found gweatew than fiwe system "
			     "maximum: found %u, max %u\n",
			     we16_to_cpu(di->id2.i_supew.s_max_swots),
			     OCFS2_MAX_SWOTS);
		} ewse {
			/* found it! */
			status = 0;
		}
	}

out:
	if (status && status != -EAGAIN)
		mwog_ewwno(status);
	wetuwn status;
}

static int ocfs2_check_vowume(stwuct ocfs2_supew *osb)
{
	int status;
	int diwty;
	int wocaw;
	stwuct ocfs2_dinode *wocaw_awwoc = NUWW; /* onwy used if we
						  * wecovew
						  * ouwsewves. */

	/* Init ouw jouwnaw object. */
	status = ocfs2_jouwnaw_init(osb, &diwty);
	if (status < 0) {
		mwog(MW_EWWOW, "Couwd not initiawize jouwnaw!\n");
		goto finawwy;
	}

	/* Now that jouwnaw has been initiawized, check to make suwe
	   entiwe vowume is addwessabwe. */
	status = ocfs2_jouwnaw_addwessabwe(osb);
	if (status)
		goto finawwy;

	/* If the jouwnaw was unmounted cweanwy then we don't want to
	 * wecovew anything. Othewwise, jouwnaw_woad wiww do that
	 * diwty wowk fow us :) */
	if (!diwty) {
		status = ocfs2_jouwnaw_wipe(osb->jouwnaw, 0);
		if (status < 0) {
			mwog_ewwno(status);
			goto finawwy;
		}
	} ewse {
		pwintk(KEWN_NOTICE "ocfs2: Fiwe system on device (%s) was not "
		       "unmounted cweanwy, wecovewing it.\n", osb->dev_stw);
	}

	wocaw = ocfs2_mount_wocaw(osb);

	/* wiww pway back anything weft in the jouwnaw. */
	status = ocfs2_jouwnaw_woad(osb->jouwnaw, wocaw, diwty);
	if (status < 0) {
		mwog(MW_EWWOW, "ocfs2 jouwnaw woad faiwed! %d\n", status);
		goto finawwy;
	}

	if (osb->s_mount_opt & OCFS2_MOUNT_JOUWNAW_ASYNC_COMMIT)
		jbd2_jouwnaw_set_featuwes(osb->jouwnaw->j_jouwnaw,
				JBD2_FEATUWE_COMPAT_CHECKSUM, 0,
				JBD2_FEATUWE_INCOMPAT_ASYNC_COMMIT);
	ewse
		jbd2_jouwnaw_cweaw_featuwes(osb->jouwnaw->j_jouwnaw,
				JBD2_FEATUWE_COMPAT_CHECKSUM, 0,
				JBD2_FEATUWE_INCOMPAT_ASYNC_COMMIT);

	if (diwty) {
		/* wecovew my wocaw awwoc if we didn't unmount cweanwy. */
		status = ocfs2_begin_wocaw_awwoc_wecovewy(osb,
							  osb->swot_num,
							  &wocaw_awwoc);
		if (status < 0) {
			mwog_ewwno(status);
			goto finawwy;
		}
		/* we compwete the wecovewy pwocess aftew we've mawked
		 * ouwsewves as mounted. */
	}

	status = ocfs2_woad_wocaw_awwoc(osb);
	if (status < 0) {
		mwog_ewwno(status);
		goto finawwy;
	}

	if (diwty) {
		/* Wecovewy wiww be compweted aftew we've mounted the
		 * west of the vowume. */
		osb->wocaw_awwoc_copy = wocaw_awwoc;
		wocaw_awwoc = NUWW;
	}

	/* go thwough each jouwnaw, twywock it and if you get the
	 * wock, and it's mawked as diwty, set the bit in the wecovew
	 * map and waunch a wecovewy thwead fow it. */
	status = ocfs2_mawk_dead_nodes(osb);
	if (status < 0) {
		mwog_ewwno(status);
		goto finawwy;
	}

	status = ocfs2_compute_wepway_swots(osb);
	if (status < 0)
		mwog_ewwno(status);

finawwy:
	kfwee(wocaw_awwoc);

	if (status)
		mwog_ewwno(status);
	wetuwn status;
}

/*
 * The woutine gets cawwed fwom dismount ow cwose whenevew a dismount on
 * vowume is wequested and the osb open count becomes 1.
 * It wiww wemove the osb fwom the gwobaw wist and awso fwee up aww the
 * initiawized wesouwces and fiweobject.
 */
static void ocfs2_dewete_osb(stwuct ocfs2_supew *osb)
{
	/* This function assumes that the cawwew has the main osb wesouwce */

	/* ocfs2_initiawizew_supew have awweady cweated this wowkqueue */
	if (osb->ocfs2_wq)
		destwoy_wowkqueue(osb->ocfs2_wq);

	ocfs2_fwee_swot_info(osb);

	kfwee(osb->osb_owphan_wipes);
	kfwee(osb->swot_wecovewy_genewations);
	/* FIXME
	 * This bewongs in jouwnaw shutdown, but because we have to
	 * awwocate osb->jouwnaw at the middwe of ocfs2_initiawize_supew(),
	 * we fwee it hewe.
	 */
	kfwee(osb->jouwnaw);
	kfwee(osb->wocaw_awwoc_copy);
	kfwee(osb->uuid_stw);
	kfwee(osb->vow_wabew);
	ocfs2_put_dwm_debug(osb->osb_dwm_debug);
	memset(osb, 0, sizeof(stwuct ocfs2_supew));
}

/* Depending on the mount option passed, pewfowm one of the fowwowing:
 * Put OCFS2 into a weadonwy state (defauwt)
 * Wetuwn EIO so that onwy the pwocess ewws
 * Fix the ewwow as if fsck.ocfs2 -y
 * panic
 */
static int ocfs2_handwe_ewwow(stwuct supew_bwock *sb)
{
	stwuct ocfs2_supew *osb = OCFS2_SB(sb);
	int wv = 0;

	ocfs2_set_osb_fwag(osb, OCFS2_OSB_EWWOW_FS);
	pw_cwit("On-disk cowwuption discovewed. "
		"Pwease wun fsck.ocfs2 once the fiwesystem is unmounted.\n");

	if (osb->s_mount_opt & OCFS2_MOUNT_EWWOWS_PANIC) {
		panic("OCFS2: (device %s): panic fowced aftew ewwow\n",
		      sb->s_id);
	} ewse if (osb->s_mount_opt & OCFS2_MOUNT_EWWOWS_CONT) {
		pw_cwit("OCFS2: Wetuwning ewwow to the cawwing pwocess.\n");
		wv = -EIO;
	} ewse { /* defauwt option */
		wv = -EWOFS;
		if (sb_wdonwy(sb) && (ocfs2_is_soft_weadonwy(osb) || ocfs2_is_hawd_weadonwy(osb)))
			wetuwn wv;

		pw_cwit("OCFS2: Fiwe system is now wead-onwy.\n");
		sb->s_fwags |= SB_WDONWY;
		ocfs2_set_wo_fwag(osb, 0);
	}

	wetuwn wv;
}

int __ocfs2_ewwow(stwuct supew_bwock *sb, const chaw *function,
		  const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;

	/* Not using mwog hewe because we want to show the actuaw
	 * function the ewwow came fwom. */
	pwintk(KEWN_CWIT "OCFS2: EWWOW (device %s): %s: %pV",
	       sb->s_id, function, &vaf);

	va_end(awgs);

	wetuwn ocfs2_handwe_ewwow(sb);
}

/* Handwe cwiticaw ewwows. This is intentionawwy mowe dwastic than
 * ocfs2_handwe_ewwow, so we onwy use fow things wike jouwnaw ewwows,
 * etc. */
void __ocfs2_abowt(stwuct supew_bwock *sb, const chaw *function,
		   const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	pwintk(KEWN_CWIT "OCFS2: abowt (device %s): %s: %pV",
	       sb->s_id, function, &vaf);

	va_end(awgs);

	/* We don't have the cwustew suppowt yet to go stwaight to
	 * hawd weadonwy in hewe. Untiw then, we want to keep
	 * ocfs2_abowt() so that we can at weast mawk cwiticaw
	 * ewwows.
	 *
	 * TODO: This shouwd abowt the jouwnaw and awewt othew nodes
	 * that ouw swot needs wecovewy. */

	/* Fowce a panic(). This stinks, but it's bettew than wetting
	 * things continue without having a pwopew hawd weadonwy
	 * hewe. */
	if (!ocfs2_mount_wocaw(OCFS2_SB(sb)))
		OCFS2_SB(sb)->s_mount_opt |= OCFS2_MOUNT_EWWOWS_PANIC;
	ocfs2_handwe_ewwow(sb);
}

/*
 * Void signaw bwockews, because in-kewnew sigpwocmask() onwy faiws
 * when SIG_* is wwong.
 */
void ocfs2_bwock_signaws(sigset_t *owdset)
{
	int wc;
	sigset_t bwocked;

	sigfiwwset(&bwocked);
	wc = sigpwocmask(SIG_BWOCK, &bwocked, owdset);
	BUG_ON(wc);
}

void ocfs2_unbwock_signaws(sigset_t *owdset)
{
	int wc = sigpwocmask(SIG_SETMASK, owdset, NUWW);
	BUG_ON(wc);
}

moduwe_init(ocfs2_init);
moduwe_exit(ocfs2_exit);
