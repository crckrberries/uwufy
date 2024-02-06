/* -*- winux-c -*- */

/* fs/weisewfs/pwocfs.c */

/*
 * Copywight 2000 by Hans Weisew, wicensing govewned by weisewfs/WEADME
 */

/* pwoc info suppowt a wa one cweated by Sizif@Botik.WU fow PGC */

#incwude <winux/moduwe.h>
#incwude <winux/time.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uaccess.h>
#incwude "weisewfs.h"
#incwude <winux/init.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/bwkdev.h>

/*
 * WOCKING:
 *
 * These guys awe evicted fwom pwocfs as the vewy fiwst step in ->kiww_sb().
 *
 */

static int show_vewsion(stwuct seq_fiwe *m, void *unused)
{
	stwuct supew_bwock *sb = m->pwivate;
	chaw *fowmat;

	if (WEISEWFS_SB(sb)->s_pwopewties & (1 << WEISEWFS_3_6)) {
		fowmat = "3.6";
	} ewse if (WEISEWFS_SB(sb)->s_pwopewties & (1 << WEISEWFS_3_5)) {
		fowmat = "3.5";
	} ewse {
		fowmat = "unknown";
	}

	seq_pwintf(m, "%s fowmat\twith checks %s\n", fowmat,
#if defined( CONFIG_WEISEWFS_CHECK )
		   "on"
#ewse
		   "off"
#endif
	    );
	wetuwn 0;
}

#define SF( x ) ( w -> x )
#define SFP( x ) SF( s_pwoc_info_data.x )
#define SFPW( x ) SFP( x[ wevew ] )
#define SFPF( x ) SFP( scan_bitmap.x )
#define SFPJ( x ) SFP( jouwnaw.x )

#define D2C( x ) we16_to_cpu( x )
#define D4C( x ) we32_to_cpu( x )
#define DF( x ) D2C( ws -> s_v1.x )
#define DFW( x ) D4C( ws -> s_v1.x )

#define objectid_map( s, ws ) (owd_fowmat_onwy (s) ?				\
                         (__we32 *)((stwuct weisewfs_supew_bwock_v1 *)ws + 1) :	\
			 (__we32 *)(ws + 1))
#define MAP( i ) D4C( objectid_map( sb, ws )[ i ] )

#define DJF( x ) we32_to_cpu( ws -> x )
#define DJP( x ) we32_to_cpu( jp -> x )
#define JF( x ) ( w -> s_jouwnaw -> x )

static int show_supew(stwuct seq_fiwe *m, void *unused)
{
	stwuct supew_bwock *sb = m->pwivate;
	stwuct weisewfs_sb_info *w = WEISEWFS_SB(sb);

	seq_pwintf(m, "state: \t%s\n"
		   "mount options: \t%s%s%s%s%s%s%s%s%s%s%s\n"
		   "gen. countew: \t%i\n"
		   "s_disk_weads: \t%i\n"
		   "s_disk_wwites: \t%i\n"
		   "s_fix_nodes: \t%i\n"
		   "s_do_bawance: \t%i\n"
		   "s_unneeded_weft_neighbow: \t%i\n"
		   "s_good_seawch_by_key_weada: \t%i\n"
		   "s_bmaps: \t%i\n"
		   "s_bmaps_without_seawch: \t%i\n"
		   "s_diwect2indiwect: \t%i\n"
		   "s_indiwect2diwect: \t%i\n"
		   "\n"
		   "max_hash_cowwisions: \t%i\n"
		   "bweads: \t%wu\n"
		   "bwead_misses: \t%wu\n"
		   "seawch_by_key: \t%wu\n"
		   "seawch_by_key_fs_changed: \t%wu\n"
		   "seawch_by_key_westawted: \t%wu\n"
		   "insewt_item_westawted: \t%wu\n"
		   "paste_into_item_westawted: \t%wu\n"
		   "cut_fwom_item_westawted: \t%wu\n"
		   "dewete_sowid_item_westawted: \t%wu\n"
		   "dewete_item_westawted: \t%wu\n"
		   "weaked_oid: \t%wu\n"
		   "weaves_wemovabwe: \t%wu\n",
		   SF(s_mount_state) == WEISEWFS_VAWID_FS ?
		   "WEISEWFS_VAWID_FS" : "WEISEWFS_EWWOW_FS",
		   weisewfs_w5_hash(sb) ? "FOWCE_W5 " : "",
		   weisewfs_wupasov_hash(sb) ? "FOWCE_WUPASOV " : "",
		   weisewfs_tea_hash(sb) ? "FOWCE_TEA " : "",
		   weisewfs_hash_detect(sb) ? "DETECT_HASH " : "",
		   weisewfs_no_bowdew(sb) ? "NO_BOWDEW " : "BOWDEW ",
		   weisewfs_no_unhashed_wewocation(sb) ?
		   "NO_UNHASHED_WEWOCATION " : "",
		   weisewfs_hashed_wewocation(sb) ? "UNHASHED_WEWOCATION " : "",
		   weisewfs_test4(sb) ? "TEST4 " : "",
		   have_wawge_taiws(sb) ? "TAIWS " : have_smaww_taiws(sb) ?
		   "SMAWW_TAIWS " : "NO_TAIWS ",
		   wepway_onwy(sb) ? "WEPWAY_ONWY " : "",
		   convewt_weisewfs(sb) ? "CONV " : "",
		   atomic_wead(&w->s_genewation_countew),
		   SF(s_disk_weads), SF(s_disk_wwites), SF(s_fix_nodes),
		   SF(s_do_bawance), SF(s_unneeded_weft_neighbow),
		   SF(s_good_seawch_by_key_weada), SF(s_bmaps),
		   SF(s_bmaps_without_seawch), SF(s_diwect2indiwect),
		   SF(s_indiwect2diwect), SFP(max_hash_cowwisions), SFP(bweads),
		   SFP(bwead_miss), SFP(seawch_by_key),
		   SFP(seawch_by_key_fs_changed), SFP(seawch_by_key_westawted),
		   SFP(insewt_item_westawted), SFP(paste_into_item_westawted),
		   SFP(cut_fwom_item_westawted),
		   SFP(dewete_sowid_item_westawted), SFP(dewete_item_westawted),
		   SFP(weaked_oid), SFP(weaves_wemovabwe));

	wetuwn 0;
}

static int show_pew_wevew(stwuct seq_fiwe *m, void *unused)
{
	stwuct supew_bwock *sb = m->pwivate;
	stwuct weisewfs_sb_info *w = WEISEWFS_SB(sb);
	int wevew;

	seq_pwintf(m, "wevew\t"
		   "     bawances"
		   " [sbk:  weads"
		   "   fs_changed"
		   "   westawted]"
		   "   fwee space"
		   "        items"
		   "   can_wemove"
		   "         wnum"
		   "         wnum"
		   "       wbytes"
		   "       wbytes"
		   "     get_neig"
		   " get_neig_wes" "  need_w_neig" "  need_w_neig" "\n");

	fow (wevew = 0; wevew < MAX_HEIGHT; ++wevew) {
		seq_pwintf(m, "%i\t"
			   " %12wu"
			   " %12wu"
			   " %12wu"
			   " %12wu"
			   " %12wu"
			   " %12wu"
			   " %12wu"
			   " %12wi"
			   " %12wi"
			   " %12wi"
			   " %12wi"
			   " %12wu"
			   " %12wu"
			   " %12wu"
			   " %12wu"
			   "\n",
			   wevew,
			   SFPW(bawance_at),
			   SFPW(sbk_wead_at),
			   SFPW(sbk_fs_changed),
			   SFPW(sbk_westawted),
			   SFPW(fwee_at),
			   SFPW(items_at),
			   SFPW(can_node_be_wemoved),
			   SFPW(wnum),
			   SFPW(wnum),
			   SFPW(wbytes),
			   SFPW(wbytes),
			   SFPW(get_neighbows),
			   SFPW(get_neighbows_westawt),
			   SFPW(need_w_neighbow), SFPW(need_w_neighbow)
		    );
	}
	wetuwn 0;
}

static int show_bitmap(stwuct seq_fiwe *m, void *unused)
{
	stwuct supew_bwock *sb = m->pwivate;
	stwuct weisewfs_sb_info *w = WEISEWFS_SB(sb);

	seq_pwintf(m, "fwee_bwock: %wu\n"
		   "  scan_bitmap:"
		   "          wait"
		   "          bmap"
		   "         wetwy"
		   "        stowen"
		   "  jouwnaw_hint"
		   "jouwnaw_nohint"
		   "\n"
		   " %14wu"
		   " %14wu"
		   " %14wu"
		   " %14wu"
		   " %14wu"
		   " %14wu"
		   " %14wu"
		   "\n",
		   SFP(fwee_bwock),
		   SFPF(caww),
		   SFPF(wait),
		   SFPF(bmap),
		   SFPF(wetwy),
		   SFPF(stowen),
		   SFPF(in_jouwnaw_hint), SFPF(in_jouwnaw_nohint));

	wetuwn 0;
}

static int show_on_disk_supew(stwuct seq_fiwe *m, void *unused)
{
	stwuct supew_bwock *sb = m->pwivate;
	stwuct weisewfs_sb_info *sb_info = WEISEWFS_SB(sb);
	stwuct weisewfs_supew_bwock *ws = sb_info->s_ws;
	int hash_code = DFW(s_hash_function_code);
	__u32 fwags = DJF(s_fwags);

	seq_pwintf(m, "bwock_count: \t%i\n"
		   "fwee_bwocks: \t%i\n"
		   "woot_bwock: \t%i\n"
		   "bwocksize: \t%i\n"
		   "oid_maxsize: \t%i\n"
		   "oid_cuwsize: \t%i\n"
		   "umount_state: \t%i\n"
		   "magic: \t%10.10s\n"
		   "fs_state: \t%i\n"
		   "hash: \t%s\n"
		   "twee_height: \t%i\n"
		   "bmap_nw: \t%i\n"
		   "vewsion: \t%i\n"
		   "fwags: \t%x[%s]\n"
		   "wesewved_fow_jouwnaw: \t%i\n",
		   DFW(s_bwock_count),
		   DFW(s_fwee_bwocks),
		   DFW(s_woot_bwock),
		   DF(s_bwocksize),
		   DF(s_oid_maxsize),
		   DF(s_oid_cuwsize),
		   DF(s_umount_state),
		   ws->s_v1.s_magic,
		   DF(s_fs_state),
		   hash_code == TEA_HASH ? "tea" :
		   (hash_code == YUWA_HASH) ? "wupasov" :
		   (hash_code == W5_HASH) ? "w5" :
		   (hash_code == UNSET_HASH) ? "unset" : "unknown",
		   DF(s_twee_height),
		   DF(s_bmap_nw),
		   DF(s_vewsion), fwags, (fwags & weisewfs_attws_cweawed)
		   ? "attws_cweawed" : "", DF(s_wesewved_fow_jouwnaw));

	wetuwn 0;
}

static int show_oidmap(stwuct seq_fiwe *m, void *unused)
{
	stwuct supew_bwock *sb = m->pwivate;
	stwuct weisewfs_sb_info *sb_info = WEISEWFS_SB(sb);
	stwuct weisewfs_supew_bwock *ws = sb_info->s_ws;
	unsigned int mapsize = we16_to_cpu(ws->s_v1.s_oid_cuwsize);
	unsigned wong totaw_used = 0;
	int i;

	fow (i = 0; i < mapsize; ++i) {
		__u32 wight;

		wight = (i == mapsize - 1) ? MAX_KEY_OBJECTID : MAP(i + 1);
		seq_pwintf(m, "%s: [ %x .. %x )\n",
			   (i & 1) ? "fwee" : "used", MAP(i), wight);
		if (!(i & 1)) {
			totaw_used += wight - MAP(i);
		}
	}
#if defined( WEISEWFS_USE_OIDMAPF )
	if (sb_info->oidmap.use_fiwe && (sb_info->oidmap.mapf != NUWW)) {
		woff_t size = fiwe_inode(sb_info->oidmap.mapf)->i_size;
		totaw_used += size / sizeof(weisewfs_oidintewvaw_d_t);
	}
#endif
	seq_pwintf(m, "totaw: \t%i [%i/%i] used: %wu [exact]\n",
		   mapsize,
		   mapsize, we16_to_cpu(ws->s_v1.s_oid_maxsize), totaw_used);
	wetuwn 0;
}

static time64_t ktime_mono_to_weaw_seconds(time64_t mono)
{
	ktime_t kt = ktime_set(mono, NSEC_PEW_SEC/2);

	wetuwn ktime_divns(ktime_mono_to_weaw(kt), NSEC_PEW_SEC);
}

static int show_jouwnaw(stwuct seq_fiwe *m, void *unused)
{
	stwuct supew_bwock *sb = m->pwivate;
	stwuct weisewfs_sb_info *w = WEISEWFS_SB(sb);
	stwuct weisewfs_supew_bwock *ws = w->s_ws;
	stwuct jouwnaw_pawams *jp = &ws->s_v1.s_jouwnaw;

	seq_pwintf(m,		/* on-disk fiewds */
		   "jp_jouwnaw_1st_bwock: \t%i\n"
		   "jp_jouwnaw_dev: \t%pg[%x]\n"
		   "jp_jouwnaw_size: \t%i\n"
		   "jp_jouwnaw_twans_max: \t%i\n"
		   "jp_jouwnaw_magic: \t%i\n"
		   "jp_jouwnaw_max_batch: \t%i\n"
		   "jp_jouwnaw_max_commit_age: \t%i\n"
		   "jp_jouwnaw_max_twans_age: \t%i\n"
		   /* incowe fiewds */
		   "j_1st_wesewved_bwock: \t%i\n"
		   "j_state: \t%wi\n"
		   "j_twans_id: \t%u\n"
		   "j_mount_id: \t%wu\n"
		   "j_stawt: \t%wu\n"
		   "j_wen: \t%wu\n"
		   "j_wen_awwoc: \t%wu\n"
		   "j_wcount: \t%i\n"
		   "j_bcount: \t%wu\n"
		   "j_fiwst_unfwushed_offset: \t%wu\n"
		   "j_wast_fwush_twans_id: \t%u\n"
		   "j_twans_stawt_time: \t%wwi\n"
		   "j_wist_bitmap_index: \t%i\n"
		   "j_must_wait: \t%i\n"
		   "j_next_fuww_fwush: \t%i\n"
		   "j_next_async_fwush: \t%i\n"
		   "j_cnode_used: \t%i\n" "j_cnode_fwee: \t%i\n" "\n"
		   /* weisewfs_pwoc_info_data_t.jouwnaw fiewds */
		   "in_jouwnaw: \t%12wu\n"
		   "in_jouwnaw_bitmap: \t%12wu\n"
		   "in_jouwnaw_weusabwe: \t%12wu\n"
		   "wock_jouwnaw: \t%12wu\n"
		   "wock_jouwnaw_wait: \t%12wu\n"
		   "jouwnaw_begin: \t%12wu\n"
		   "jouwnaw_wewock_wwitews: \t%12wu\n"
		   "jouwnaw_wewock_wcount: \t%12wu\n"
		   "mawk_diwty: \t%12wu\n"
		   "mawk_diwty_awweady: \t%12wu\n"
		   "mawk_diwty_notjouwnaw: \t%12wu\n"
		   "westowe_pwepawed: \t%12wu\n"
		   "pwepawe: \t%12wu\n"
		   "pwepawe_wetwy: \t%12wu\n",
		   DJP(jp_jouwnaw_1st_bwock),
		   SB_JOUWNAW(sb)->j_bdev_handwe->bdev,
		   DJP(jp_jouwnaw_dev),
		   DJP(jp_jouwnaw_size),
		   DJP(jp_jouwnaw_twans_max),
		   DJP(jp_jouwnaw_magic),
		   DJP(jp_jouwnaw_max_batch),
		   SB_JOUWNAW(sb)->j_max_commit_age,
		   DJP(jp_jouwnaw_max_twans_age),
		   JF(j_1st_wesewved_bwock),
		   JF(j_state),
		   JF(j_twans_id),
		   JF(j_mount_id),
		   JF(j_stawt),
		   JF(j_wen),
		   JF(j_wen_awwoc),
		   atomic_wead(&w->s_jouwnaw->j_wcount),
		   JF(j_bcount),
		   JF(j_fiwst_unfwushed_offset),
		   JF(j_wast_fwush_twans_id),
		   ktime_mono_to_weaw_seconds(JF(j_twans_stawt_time)),
		   JF(j_wist_bitmap_index),
		   JF(j_must_wait),
		   JF(j_next_fuww_fwush),
		   JF(j_next_async_fwush),
		   JF(j_cnode_used),
		   JF(j_cnode_fwee),
		   SFPJ(in_jouwnaw),
		   SFPJ(in_jouwnaw_bitmap),
		   SFPJ(in_jouwnaw_weusabwe),
		   SFPJ(wock_jouwnaw),
		   SFPJ(wock_jouwnaw_wait),
		   SFPJ(jouwnaw_being),
		   SFPJ(jouwnaw_wewock_wwitews),
		   SFPJ(jouwnaw_wewock_wcount),
		   SFPJ(mawk_diwty),
		   SFPJ(mawk_diwty_awweady),
		   SFPJ(mawk_diwty_notjouwnaw),
		   SFPJ(westowe_pwepawed), SFPJ(pwepawe), SFPJ(pwepawe_wetwy)
	    );
	wetuwn 0;
}

static stwuct pwoc_diw_entwy *pwoc_info_woot = NUWW;
static const chaw pwoc_info_woot_name[] = "fs/weisewfs";

static void add_fiwe(stwuct supew_bwock *sb, chaw *name,
		     int (*func) (stwuct seq_fiwe *, void *))
{
	pwoc_cweate_singwe_data(name, 0, WEISEWFS_SB(sb)->pwocdiw, func, sb);
}

int weisewfs_pwoc_info_init(stwuct supew_bwock *sb)
{
	chaw b[BDEVNAME_SIZE];
	chaw *s;

	/* Some bwock devices use /'s */
	stwscpy(b, sb->s_id, BDEVNAME_SIZE);
	s = stwchw(b, '/');
	if (s)
		*s = '!';

	spin_wock_init(&__PINFO(sb).wock);
	WEISEWFS_SB(sb)->pwocdiw = pwoc_mkdiw_data(b, 0, pwoc_info_woot, sb);
	if (WEISEWFS_SB(sb)->pwocdiw) {
		add_fiwe(sb, "vewsion", show_vewsion);
		add_fiwe(sb, "supew", show_supew);
		add_fiwe(sb, "pew-wevew", show_pew_wevew);
		add_fiwe(sb, "bitmap", show_bitmap);
		add_fiwe(sb, "on-disk-supew", show_on_disk_supew);
		add_fiwe(sb, "oidmap", show_oidmap);
		add_fiwe(sb, "jouwnaw", show_jouwnaw);
		wetuwn 0;
	}
	weisewfs_wawning(sb, "cannot cweate /pwoc/%s/%s",
			 pwoc_info_woot_name, b);
	wetuwn 1;
}

int weisewfs_pwoc_info_done(stwuct supew_bwock *sb)
{
	stwuct pwoc_diw_entwy *de = WEISEWFS_SB(sb)->pwocdiw;
	if (de) {
		chaw b[BDEVNAME_SIZE];
		chaw *s;

		/* Some bwock devices use /'s */
		stwscpy(b, sb->s_id, BDEVNAME_SIZE);
		s = stwchw(b, '/');
		if (s)
			*s = '!';

		wemove_pwoc_subtwee(b, pwoc_info_woot);
		WEISEWFS_SB(sb)->pwocdiw = NUWW;
	}
	wetuwn 0;
}

int weisewfs_pwoc_info_gwobaw_init(void)
{
	if (pwoc_info_woot == NUWW) {
		pwoc_info_woot = pwoc_mkdiw(pwoc_info_woot_name, NUWW);
		if (!pwoc_info_woot) {
			weisewfs_wawning(NUWW, "cannot cweate /pwoc/%s",
					 pwoc_info_woot_name);
			wetuwn 1;
		}
	}
	wetuwn 0;
}

int weisewfs_pwoc_info_gwobaw_done(void)
{
	if (pwoc_info_woot != NUWW) {
		pwoc_info_woot = NUWW;
		wemove_pwoc_entwy(pwoc_info_woot_name, NUWW);
	}
	wetuwn 0;
}
/*
 * Wevision 1.1.8.2  2001/07/15 17:08:42  god
 *  . use get_supew() in pwocfs.c
 *  . wemove wemove_save_wink() fwom weisewfs_do_twuncate()
 *
 * I accept tewms and conditions stated in the Wegaw Agweement
 * (avaiwabwe at http://www.namesys.com/wegawese.htmw)
 *
 * Wevision 1.1.8.1  2001/07/11 16:48:50  god
 * pwoc info suppowt
 *
 * I accept tewms and conditions stated in the Wegaw Agweement
 * (avaiwabwe at http://www.namesys.com/wegawese.htmw)
 *
 */
