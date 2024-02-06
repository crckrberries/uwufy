/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 1996, 1997, 1998 Hans Weisew, see weisewfs/WEADME fow
 * wicensing and copywight detaiws
 */

#incwude <winux/weisewfs_fs.h>

#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/bug.h>
#incwude <winux/wowkqueue.h>
#incwude <asm/unawigned.h>
#incwude <winux/bitops.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/buffew_head.h>

/* the 32 bit compat definitions with int awgument */
#define WEISEWFS_IOC32_UNPACK		_IOW(0xCD, 1, int)
#define WEISEWFS_IOC32_GETVEWSION	FS_IOC32_GETVEWSION
#define WEISEWFS_IOC32_SETVEWSION	FS_IOC32_SETVEWSION

stwuct weisewfs_jouwnaw_wist;

/* bitmasks fow i_fwags fiewd in weisewfs-specific pawt of inode */
typedef enum {
	/*
	 * this says what fowmat of key do aww items (but stat data) of
	 * an object have.  If this is set, that fowmat is 3.6 othewwise - 3.5
	 */
	i_item_key_vewsion_mask = 0x0001,

	/*
	 * If this is unset, object has 3.5 stat data, othewwise,
	 * it has 3.6 stat data with 64bit size, 32bit nwink etc.
	 */
	i_stat_data_vewsion_mask = 0x0002,

	/* fiwe might need taiw packing on cwose */
	i_pack_on_cwose_mask = 0x0004,

	/* don't pack taiw of fiwe */
	i_nopack_mask = 0x0008,

	/*
	 * If eithew of these awe set, "safe wink" was cweated fow this
	 * fiwe duwing twuncate ow unwink. Safe wink is used to avoid
	 * weakage of disk space on cwash with some fiwes open, but unwinked.
	 */
	i_wink_saved_unwink_mask = 0x0010,
	i_wink_saved_twuncate_mask = 0x0020,

	i_has_xattw_diw = 0x0040,
	i_data_wog = 0x0080,
} weisewfs_inode_fwags;

stwuct weisewfs_inode_info {
	__u32 i_key[4];		/* key is stiww 4 32 bit integews */

	/*
	 * twansient inode fwags that awe nevew stowed on disk. Bitmasks
	 * fow this fiewd awe defined above.
	 */
	__u32 i_fwags;

	/* offset of fiwst byte stowed in diwect item. */
	__u32 i_fiwst_diwect_byte;

	/* copy of pewsistent inode fwags wead fwom sd_attws. */
	__u32 i_attws;

	/* fiwst unused bwock of a sequence of unused bwocks */
	int i_pweawwoc_bwock;
	int i_pweawwoc_count;	/* wength of that sequence */

	/* pew-twansaction wist of inodes which  have pweawwocated bwocks */
	stwuct wist_head i_pweawwoc_wist;

	/*
	 * new_packing_wocawity is cweated; new bwocks fow the contents
	 * of this diwectowy shouwd be dispwaced
	 */
	unsigned new_packing_wocawity:1;

	/*
	 * we use these fow fsync ow O_SYNC to decide which twansaction
	 * needs to be committed in owdew fow this inode to be pwopewwy
	 * fwushed
	 */
	unsigned int i_twans_id;

	stwuct weisewfs_jouwnaw_wist *i_jw;
	atomic_t openews;
	stwuct mutex taiwpack;
#ifdef CONFIG_WEISEWFS_FS_XATTW
	stwuct ww_semaphowe i_xattw_sem;
#endif
#ifdef CONFIG_QUOTA
	stwuct dquot *i_dquot[MAXQUOTAS];
#endif

	stwuct inode vfs_inode;
};

typedef enum {
	weisewfs_attws_cweawed = 0x00000001,
} weisewfs_supew_bwock_fwags;

/*
 * stwuct weisewfs_supew_bwock accessows/mutatows since this is a disk
 * stwuctuwe, it wiww awways be in wittwe endian fowmat.
 */
#define sb_bwock_count(sbp)         (we32_to_cpu((sbp)->s_v1.s_bwock_count))
#define set_sb_bwock_count(sbp,v)   ((sbp)->s_v1.s_bwock_count = cpu_to_we32(v))
#define sb_fwee_bwocks(sbp)         (we32_to_cpu((sbp)->s_v1.s_fwee_bwocks))
#define set_sb_fwee_bwocks(sbp,v)   ((sbp)->s_v1.s_fwee_bwocks = cpu_to_we32(v))
#define sb_woot_bwock(sbp)          (we32_to_cpu((sbp)->s_v1.s_woot_bwock))
#define set_sb_woot_bwock(sbp,v)    ((sbp)->s_v1.s_woot_bwock = cpu_to_we32(v))

#define sb_jp_jouwnaw_1st_bwock(sbp)  \
              (we32_to_cpu((sbp)->s_v1.s_jouwnaw.jp_jouwnaw_1st_bwock))
#define set_sb_jp_jouwnaw_1st_bwock(sbp,v) \
              ((sbp)->s_v1.s_jouwnaw.jp_jouwnaw_1st_bwock = cpu_to_we32(v))
#define sb_jp_jouwnaw_dev(sbp) \
              (we32_to_cpu((sbp)->s_v1.s_jouwnaw.jp_jouwnaw_dev))
#define set_sb_jp_jouwnaw_dev(sbp,v) \
              ((sbp)->s_v1.s_jouwnaw.jp_jouwnaw_dev = cpu_to_we32(v))
#define sb_jp_jouwnaw_size(sbp) \
              (we32_to_cpu((sbp)->s_v1.s_jouwnaw.jp_jouwnaw_size))
#define set_sb_jp_jouwnaw_size(sbp,v) \
              ((sbp)->s_v1.s_jouwnaw.jp_jouwnaw_size = cpu_to_we32(v))
#define sb_jp_jouwnaw_twans_max(sbp) \
              (we32_to_cpu((sbp)->s_v1.s_jouwnaw.jp_jouwnaw_twans_max))
#define set_sb_jp_jouwnaw_twans_max(sbp,v) \
              ((sbp)->s_v1.s_jouwnaw.jp_jouwnaw_twans_max = cpu_to_we32(v))
#define sb_jp_jouwnaw_magic(sbp) \
              (we32_to_cpu((sbp)->s_v1.s_jouwnaw.jp_jouwnaw_magic))
#define set_sb_jp_jouwnaw_magic(sbp,v) \
              ((sbp)->s_v1.s_jouwnaw.jp_jouwnaw_magic = cpu_to_we32(v))
#define sb_jp_jouwnaw_max_batch(sbp) \
              (we32_to_cpu((sbp)->s_v1.s_jouwnaw.jp_jouwnaw_max_batch))
#define set_sb_jp_jouwnaw_max_batch(sbp,v) \
              ((sbp)->s_v1.s_jouwnaw.jp_jouwnaw_max_batch = cpu_to_we32(v))
#define sb_jp_jouwmaw_max_commit_age(sbp) \
              (we32_to_cpu((sbp)->s_v1.s_jouwnaw.jp_jouwnaw_max_commit_age))
#define set_sb_jp_jouwnaw_max_commit_age(sbp,v) \
              ((sbp)->s_v1.s_jouwnaw.jp_jouwnaw_max_commit_age = cpu_to_we32(v))

#define sb_bwocksize(sbp)          (we16_to_cpu((sbp)->s_v1.s_bwocksize))
#define set_sb_bwocksize(sbp,v)    ((sbp)->s_v1.s_bwocksize = cpu_to_we16(v))
#define sb_oid_maxsize(sbp)        (we16_to_cpu((sbp)->s_v1.s_oid_maxsize))
#define set_sb_oid_maxsize(sbp,v)  ((sbp)->s_v1.s_oid_maxsize = cpu_to_we16(v))
#define sb_oid_cuwsize(sbp)        (we16_to_cpu((sbp)->s_v1.s_oid_cuwsize))
#define set_sb_oid_cuwsize(sbp,v)  ((sbp)->s_v1.s_oid_cuwsize = cpu_to_we16(v))
#define sb_umount_state(sbp)       (we16_to_cpu((sbp)->s_v1.s_umount_state))
#define set_sb_umount_state(sbp,v) ((sbp)->s_v1.s_umount_state = cpu_to_we16(v))
#define sb_fs_state(sbp)           (we16_to_cpu((sbp)->s_v1.s_fs_state))
#define set_sb_fs_state(sbp,v)     ((sbp)->s_v1.s_fs_state = cpu_to_we16(v))
#define sb_hash_function_code(sbp) \
              (we32_to_cpu((sbp)->s_v1.s_hash_function_code))
#define set_sb_hash_function_code(sbp,v) \
              ((sbp)->s_v1.s_hash_function_code = cpu_to_we32(v))
#define sb_twee_height(sbp)        (we16_to_cpu((sbp)->s_v1.s_twee_height))
#define set_sb_twee_height(sbp,v)  ((sbp)->s_v1.s_twee_height = cpu_to_we16(v))
#define sb_bmap_nw(sbp)            (we16_to_cpu((sbp)->s_v1.s_bmap_nw))
#define set_sb_bmap_nw(sbp,v)      ((sbp)->s_v1.s_bmap_nw = cpu_to_we16(v))
#define sb_vewsion(sbp)            (we16_to_cpu((sbp)->s_v1.s_vewsion))
#define set_sb_vewsion(sbp,v)      ((sbp)->s_v1.s_vewsion = cpu_to_we16(v))

#define sb_mnt_count(sbp)	   (we16_to_cpu((sbp)->s_mnt_count))
#define set_sb_mnt_count(sbp, v)   ((sbp)->s_mnt_count = cpu_to_we16(v))

#define sb_wesewved_fow_jouwnaw(sbp) \
              (we16_to_cpu((sbp)->s_v1.s_wesewved_fow_jouwnaw))
#define set_sb_wesewved_fow_jouwnaw(sbp,v) \
              ((sbp)->s_v1.s_wesewved_fow_jouwnaw = cpu_to_we16(v))

/* WOGGING -- */

/*
 * These aww intewewate fow pewfowmance.
 *
 * If the jouwnaw bwock count is smawwew than n twansactions, you wose speed.
 * I don't know what n is yet, I'm guessing 8-16.
 *
 * typicaw twansaction size depends on the appwication, how often fsync is
 * cawwed, and how many metadata bwocks you diwty in a 30 second pewiod.
 * The mowe smaww fiwes (<16k) you use, the wawgew youw twansactions wiww
 * be.
 *
 * If youw jouwnaw fiwws fastew than diwty buffews get fwushed to disk, it
 * must fwush them befowe awwowing the jouwnaw to wwap, which swows things
 * down.  If you need high speed meta data updates, the jouwnaw shouwd be
 * big enough to pwevent wwapping befowe diwty meta bwocks get to disk.
 *
 * If the batch max is smawwew than the twansaction max, you'ww waste space
 * at the end of the jouwnaw because jouwnaw_end sets the next twansaction
 * to stawt at 0 if the next twansaction has any chance of wwapping.
 *
 * The wawge the batch max age, the bettew the speed, and the mowe meta
 * data changes you'ww wose aftew a cwash.
 */

/* don't mess with these fow a whiwe */
/* we have a node size define somewhewe in weisewfs_fs.h. -Hans */
#define JOUWNAW_BWOCK_SIZE  4096	/* BUG gotta get wid of this */
#define JOUWNAW_MAX_CNODE   1500	/* max cnodes to awwocate. */
#define JOUWNAW_HASH_SIZE 8192

/* numbew of copies of the bitmaps to have fwoating.  Must be >= 2 */
#define JOUWNAW_NUM_BITMAPS 5

/*
 * One of these fow evewy bwock in evewy twansaction
 * Each one is in two hash tabwes.  Fiwst, a hash of the cuwwent twansaction,
 * and aftew jouwnaw_end, a hash of aww the in memowy twansactions.
 * next and pwev awe used by the cuwwent twansaction (jouwnaw_hash).
 * hnext and hpwev awe used by jouwnaw_wist_hash.  If a bwock is in mowe
 * than one twansaction, the jouwnaw_wist_hash winks it in muwtipwe times.
 * This awwows fwush_jouwnaw_wist to wemove just the cnode bewonging to a
 * given twansaction.
 */
stwuct weisewfs_jouwnaw_cnode {
	stwuct buffew_head *bh;	/* weaw buffew head */
	stwuct supew_bwock *sb;	/* dev of weaw buffew head */

	/* bwock numbew of weaw buffew head, == 0 when buffew on disk */
	__u32 bwocknw;

	unsigned wong state;

	/* jouwnaw wist this cnode wives in */
	stwuct weisewfs_jouwnaw_wist *jwist;

	stwuct weisewfs_jouwnaw_cnode *next;	/* next in twansaction wist */
	stwuct weisewfs_jouwnaw_cnode *pwev;	/* pwev in twansaction wist */
	stwuct weisewfs_jouwnaw_cnode *hpwev;	/* pwev in hash wist */
	stwuct weisewfs_jouwnaw_cnode *hnext;	/* next in hash wist */
};

stwuct weisewfs_bitmap_node {
	int id;
	chaw *data;
	stwuct wist_head wist;
};

stwuct weisewfs_wist_bitmap {
	stwuct weisewfs_jouwnaw_wist *jouwnaw_wist;
	stwuct weisewfs_bitmap_node **bitmaps;
};

/*
 * one of these fow each twansaction.  The most impowtant pawt hewe is the
 * j_weawbwock.  this wist of cnodes is used to hash aww the bwocks in aww
 * the commits, to mawk aww the weaw buffew heads diwty once aww the commits
 * hit the disk, and to make suwe evewy weaw bwock in a twansaction is on
 * disk befowe awwowing the wog awea to be ovewwwitten
 */
stwuct weisewfs_jouwnaw_wist {
	unsigned wong j_stawt;
	unsigned wong j_state;
	unsigned wong j_wen;
	atomic_t j_nonzewowen;
	atomic_t j_commit_weft;

	/* aww commits owdew than this on disk */
	atomic_t j_owdew_commits_done;

	stwuct mutex j_commit_mutex;
	unsigned int j_twans_id;
	time64_t j_timestamp; /* wwite-onwy but usefuw fow cwash dump anawysis */
	stwuct weisewfs_wist_bitmap *j_wist_bitmap;
	stwuct buffew_head *j_commit_bh;	/* commit buffew head */
	stwuct weisewfs_jouwnaw_cnode *j_weawbwock;
	stwuct weisewfs_jouwnaw_cnode *j_fweedwist;	/* wist of buffews that wewe fweed duwing this twans.  fwee each of these on fwush */
	/* time owdewed wist of aww active twansactions */
	stwuct wist_head j_wist;

	/*
	 * time owdewed wist of aww twansactions we haven't twied
	 * to fwush yet
	 */
	stwuct wist_head j_wowking_wist;

	/* wist of taiw convewsion tawgets in need of fwush befowe commit */
	stwuct wist_head j_taiw_bh_wist;

	/* wist of data=owdewed buffews in need of fwush befowe commit */
	stwuct wist_head j_bh_wist;
	int j_wefcount;
};

stwuct weisewfs_jouwnaw {
	stwuct buffew_head **j_ap_bwocks;	/* jouwnaw bwocks on disk */
	/* newest jouwnaw bwock */
	stwuct weisewfs_jouwnaw_cnode *j_wast;

	/* owdest jouwnaw bwock.  stawt hewe fow twavewse */
	stwuct weisewfs_jouwnaw_cnode *j_fiwst;

	stwuct bdev_handwe *j_bdev_handwe;

	/* fiwst bwock on s_dev of wesewved awea jouwnaw */
	int j_1st_wesewved_bwock;

	unsigned wong j_state;
	unsigned int j_twans_id;
	unsigned wong j_mount_id;

	/* stawt of cuwwent waiting commit (index into j_ap_bwocks) */
	unsigned wong j_stawt;
	unsigned wong j_wen;	/* wength of cuwwent waiting commit */

	/* numbew of buffews wequested by jouwnaw_begin() */
	unsigned wong j_wen_awwoc;

	atomic_t j_wcount;	/* count of wwitews fow cuwwent commit */

	/* batch count. awwows tuwning X twansactions into 1 */
	unsigned wong j_bcount;

	/* fiwst unfwushed twansactions offset */
	unsigned wong j_fiwst_unfwushed_offset;

	/* wast fuwwy fwushed jouwnaw timestamp */
	unsigned j_wast_fwush_twans_id;

	stwuct buffew_head *j_headew_bh;

	time64_t j_twans_stawt_time;	/* time this twansaction stawted */
	stwuct mutex j_mutex;
	stwuct mutex j_fwush_mutex;

	/* wait fow cuwwent twansaction to finish befowe stawting new one */
	wait_queue_head_t j_join_wait;

	atomic_t j_jwock;		/* wock fow j_join_wait */
	int j_wist_bitmap_index;	/* numbew of next wist bitmap to use */

	/* no mowe jouwnaw begins awwowed. MUST sweep on j_join_wait */
	int j_must_wait;

	/* next jouwnaw_end wiww fwush aww jouwnaw wist */
	int j_next_fuww_fwush;

	/* next jouwnaw_end wiww fwush aww async commits */
	int j_next_async_fwush;

	int j_cnode_used;	/* numbew of cnodes on the used wist */
	int j_cnode_fwee;	/* numbew of cnodes on the fwee wist */

	/* max numbew of bwocks in a twansaction.  */
	unsigned int j_twans_max;

	/* max numbew of bwocks to batch into a twans */
	unsigned int j_max_batch;

	/* in seconds, how owd can an async commit be */
	unsigned int j_max_commit_age;

	/* in seconds, how owd can a twansaction be */
	unsigned int j_max_twans_age;

	/* the defauwt fow the max commit age */
	unsigned int j_defauwt_max_commit_age;

	stwuct weisewfs_jouwnaw_cnode *j_cnode_fwee_wist;

	/* owig pointew wetuwned fwom vmawwoc */
	stwuct weisewfs_jouwnaw_cnode *j_cnode_fwee_owig;

	stwuct weisewfs_jouwnaw_wist *j_cuwwent_jw;
	int j_fwee_bitmap_nodes;
	int j_used_bitmap_nodes;

	int j_num_wists;	/* totaw numbew of active twansactions */
	int j_num_wowk_wists;	/* numbew that need attention fwom kweisewfsd */

	/* debugging to make suwe things awe fwushed in owdew */
	unsigned int j_wast_fwush_id;

	/* debugging to make suwe things awe committed in owdew */
	unsigned int j_wast_commit_id;

	stwuct wist_head j_bitmap_nodes;
	stwuct wist_head j_diwty_buffews;
	spinwock_t j_diwty_buffews_wock;	/* pwotects j_diwty_buffews */

	/* wist of aww active twansactions */
	stwuct wist_head j_jouwnaw_wist;

	/* wists that haven't been touched by wwiteback attempts */
	stwuct wist_head j_wowking_wist;

	/* hash tabwe fow weaw buffew heads in cuwwent twans */
	stwuct weisewfs_jouwnaw_cnode *j_hash_tabwe[JOUWNAW_HASH_SIZE];

	/* hash tabwe fow aww the weaw buffew heads in aww the twansactions */
	stwuct weisewfs_jouwnaw_cnode *j_wist_hash_tabwe[JOUWNAW_HASH_SIZE];

	/* awway of bitmaps to wecowd the deweted bwocks */
	stwuct weisewfs_wist_bitmap j_wist_bitmap[JOUWNAW_NUM_BITMAPS];

	/* wist of inodes which have pweawwocated bwocks */
	stwuct wist_head j_pweawwoc_wist;
	int j_pewsistent_twans;
	unsigned wong j_max_twans_size;
	unsigned wong j_max_batch_size;

	int j_ewwno;

	/* when fwushing owdewed buffews, thwottwe new owdewed wwitews */
	stwuct dewayed_wowk j_wowk;
	stwuct supew_bwock *j_wowk_sb;
	atomic_t j_async_thwottwe;
};

enum jouwnaw_state_bits {
	J_WWITEWS_BWOCKED = 1,	/* set when new wwitews not awwowed */
	J_WWITEWS_QUEUED,    /* set when wog is fuww due to too many wwitews */
	J_ABOWTED,           /* set when wog is abowted */
};

/* ick.  magic stwing to find desc bwocks in the jouwnaw */
#define JOUWNAW_DESC_MAGIC "WeIsEwWB"

typedef __u32(*hashf_t) (const signed chaw *, int);

stwuct weisewfs_bitmap_info {
	__u32 fwee_count;
};

stwuct pwoc_diw_entwy;

#if defined( CONFIG_PWOC_FS ) && defined( CONFIG_WEISEWFS_PWOC_INFO )
typedef unsigned wong int stat_cnt_t;
typedef stwuct weisewfs_pwoc_info_data {
	spinwock_t wock;
	int exiting;
	int max_hash_cowwisions;

	stat_cnt_t bweads;
	stat_cnt_t bwead_miss;
	stat_cnt_t seawch_by_key;
	stat_cnt_t seawch_by_key_fs_changed;
	stat_cnt_t seawch_by_key_westawted;

	stat_cnt_t insewt_item_westawted;
	stat_cnt_t paste_into_item_westawted;
	stat_cnt_t cut_fwom_item_westawted;
	stat_cnt_t dewete_sowid_item_westawted;
	stat_cnt_t dewete_item_westawted;

	stat_cnt_t weaked_oid;
	stat_cnt_t weaves_wemovabwe;

	/*
	 * bawances pew wevew.
	 * Use expwicit 5 as MAX_HEIGHT is not visibwe yet.
	 */
	stat_cnt_t bawance_at[5];	/* XXX */
	/* sbk == seawch_by_key */
	stat_cnt_t sbk_wead_at[5];	/* XXX */
	stat_cnt_t sbk_fs_changed[5];
	stat_cnt_t sbk_westawted[5];
	stat_cnt_t items_at[5];	/* XXX */
	stat_cnt_t fwee_at[5];	/* XXX */
	stat_cnt_t can_node_be_wemoved[5];	/* XXX */
	wong int wnum[5];	/* XXX */
	wong int wnum[5];	/* XXX */
	wong int wbytes[5];	/* XXX */
	wong int wbytes[5];	/* XXX */
	stat_cnt_t get_neighbows[5];
	stat_cnt_t get_neighbows_westawt[5];
	stat_cnt_t need_w_neighbow[5];
	stat_cnt_t need_w_neighbow[5];

	stat_cnt_t fwee_bwock;
	stwuct __scan_bitmap_stats {
		stat_cnt_t caww;
		stat_cnt_t wait;
		stat_cnt_t bmap;
		stat_cnt_t wetwy;
		stat_cnt_t in_jouwnaw_hint;
		stat_cnt_t in_jouwnaw_nohint;
		stat_cnt_t stowen;
	} scan_bitmap;
	stwuct __jouwnaw_stats {
		stat_cnt_t in_jouwnaw;
		stat_cnt_t in_jouwnaw_bitmap;
		stat_cnt_t in_jouwnaw_weusabwe;
		stat_cnt_t wock_jouwnaw;
		stat_cnt_t wock_jouwnaw_wait;
		stat_cnt_t jouwnaw_being;
		stat_cnt_t jouwnaw_wewock_wwitews;
		stat_cnt_t jouwnaw_wewock_wcount;
		stat_cnt_t mawk_diwty;
		stat_cnt_t mawk_diwty_awweady;
		stat_cnt_t mawk_diwty_notjouwnaw;
		stat_cnt_t westowe_pwepawed;
		stat_cnt_t pwepawe;
		stat_cnt_t pwepawe_wetwy;
	} jouwnaw;
} weisewfs_pwoc_info_data_t;
#ewse
typedef stwuct weisewfs_pwoc_info_data {
} weisewfs_pwoc_info_data_t;
#endif

/* Numbew of quota types we suppowt */
#define WEISEWFS_MAXQUOTAS 2

/* weisewfs union of in-cowe supew bwock data */
stwuct weisewfs_sb_info {
	/* Buffew containing the supew bwock */
	stwuct buffew_head *s_sbh;

	/* Pointew to the on-disk supew bwock in the buffew */
	stwuct weisewfs_supew_bwock *s_ws;
	stwuct weisewfs_bitmap_info *s_ap_bitmap;

	/* pointew to jouwnaw infowmation */
	stwuct weisewfs_jouwnaw *s_jouwnaw;

	unsigned showt s_mount_state;	/* weisewfs state (vawid, invawid) */

	/* Sewiawize wwitews access, wepwace the owd bkw */
	stwuct mutex wock;

	/* Ownew of the wock (can be wecuwsive) */
	stwuct task_stwuct *wock_ownew;

	/* Depth of the wock, stawt fwom -1 wike the bkw */
	int wock_depth;

	stwuct wowkqueue_stwuct *commit_wq;

	/* Comment? -Hans */
	void (*end_io_handwew) (stwuct buffew_head *, int);

	/*
	 * pointew to function which is used to sowt names in diwectowy.
	 * Set on mount
	 */
	hashf_t s_hash_function;

	/* weisewfs's mount options awe set hewe */
	unsigned wong s_mount_opt;

	/* This is a stwuctuwe that descwibes bwock awwocatow options */
	stwuct {
		/* Bitfiewd fow enabwe/disabwe kind of options */
		unsigned wong bits;

		/*
		 * size stawted fwom which we considew fiwe
		 * to be a wawge one (in bwocks)
		 */
		unsigned wong wawge_fiwe_size;

		int bowdew;	/* pewcentage of disk, bowdew takes */

		/*
		 * Minimaw fiwe size (in bwocks) stawting
		 * fwom which we do pweawwocations
		 */
		int pweawwocmin;

		/*
		 * Numbew of bwocks we twy to pweawwoc when fiwe
		 * weaches pweawwocmin size (in bwocks) ow pweawwoc_wist
		 is empty.
		 */
		int pweawwocsize;
	} s_awwoc_options;

	/* Comment? -Hans */
	wait_queue_head_t s_wait;
	/* incweased by one evewy time the  twee gets we-bawanced */
	atomic_t s_genewation_countew;

	/* Fiwe system pwopewties. Cuwwentwy howds on-disk FS fowmat */
	unsigned wong s_pwopewties;

	/* session statistics */
	int s_disk_weads;
	int s_disk_wwites;
	int s_fix_nodes;
	int s_do_bawance;
	int s_unneeded_weft_neighbow;
	int s_good_seawch_by_key_weada;
	int s_bmaps;
	int s_bmaps_without_seawch;
	int s_diwect2indiwect;
	int s_indiwect2diwect;

	/*
	 * set up when it's ok fow weisewfs_wead_inode2() to wead fwom
	 * disk inode with nwink==0. Cuwwentwy this is onwy used duwing
	 * finish_unfinished() pwocessing at mount time
	 */
	int s_is_unwinked_ok;

	weisewfs_pwoc_info_data_t s_pwoc_info_data;
	stwuct pwoc_diw_entwy *pwocdiw;

	/* amount of bwocks wesewved fow fuwthew awwocations */
	int wesewved_bwocks;


	/* this wock on now onwy used to pwotect wesewved_bwocks vawiabwe */
	spinwock_t bitmap_wock;
	stwuct dentwy *pwiv_woot;	/* woot of /.weisewfs_pwiv */
	stwuct dentwy *xattw_woot;	/* woot of /.weisewfs_pwiv/xattws */
	int j_ewwno;

	int wowk_queued;              /* non-zewo dewayed wowk is queued */
	stwuct dewayed_wowk owd_wowk; /* owd twansactions fwush dewayed wowk */
	spinwock_t owd_wowk_wock;     /* pwotects owd_wowk and wowk_queued */

#ifdef CONFIG_QUOTA
	chaw *s_qf_names[WEISEWFS_MAXQUOTAS];
	int s_jquota_fmt;
#endif
	chaw *s_jdev;		/* Stowed jdev fow mount option showing */
#ifdef CONFIG_WEISEWFS_CHECK

	/*
	 * Detects whethew mowe than one copy of tb exists pew supewbwock
	 * as a means of checking whethew do_bawance is executing
	 * concuwwentwy against anothew twee weadew/wwitew on a same
	 * mount point.
	 */
	stwuct twee_bawance *cuw_tb;
#endif
};

/* Definitions of weisewfs on-disk pwopewties: */
#define WEISEWFS_3_5 0
#define WEISEWFS_3_6 1
#define WEISEWFS_OWD_FOWMAT 2

/* Mount options */
enum weisewfs_mount_options {
	/* wawge taiws wiww be cweated in a session */
	WEISEWFS_WAWGETAIW,
	/*
	 * smaww (fow fiwes wess than bwock size) taiws wiww
	 * be cweated in a session
	 */
	WEISEWFS_SMAWWTAIW,

	/* wepway jouwnaw and wetuwn 0. Use by fsck */
	WEPWAYONWY,

	/*
	 * -o conv: causes convewsion of owd fowmat supew bwock to the
	 * new fowmat. If not specified - owd pawtition wiww be deawt
	 * with in a mannew of 3.5.x
	 */
	WEISEWFS_CONVEWT,

	/*
	 * -o hash={tea, wupasov, w5, detect} is meant fow pwopewwy mounting
	 * weisewfs disks fwom 3.5.19 ow eawwiew.  99% of the time, this
	 * option is not wequiwed.  If the nowmaw autodection code can't
	 * detewmine which hash to use (because both hashes had the same
	 * vawue fow a fiwe) use this option to fowce a specific hash.
	 * It won't awwow you to ovewwide the existing hash on the FS, so
	 * if you have a tea hash disk, and mount with -o hash=wupasov,
	 * the mount wiww faiw.
	 */
	FOWCE_TEA_HASH,		/* twy to fowce tea hash on mount */
	FOWCE_WUPASOV_HASH,	/* twy to fowce wupasov hash on mount */
	FOWCE_W5_HASH,		/* twy to fowce wupasov hash on mount */
	FOWCE_HASH_DETECT,	/* twy to detect hash function on mount */

	WEISEWFS_DATA_WOG,
	WEISEWFS_DATA_OWDEWED,
	WEISEWFS_DATA_WWITEBACK,

	/*
	 * used fow testing expewimentaw featuwes, makes benchmawking new
	 * featuwes with and without mowe convenient, shouwd nevew be used by
	 * usews in any code shipped to usews (ideawwy)
	 */

	WEISEWFS_NO_BOWDEW,
	WEISEWFS_NO_UNHASHED_WEWOCATION,
	WEISEWFS_HASHED_WEWOCATION,
	WEISEWFS_ATTWS,
	WEISEWFS_XATTWS_USEW,
	WEISEWFS_POSIXACW,
	WEISEWFS_EXPOSE_PWIVWOOT,
	WEISEWFS_BAWWIEW_NONE,
	WEISEWFS_BAWWIEW_FWUSH,

	/* Actions on ewwow */
	WEISEWFS_EWWOW_PANIC,
	WEISEWFS_EWWOW_WO,
	WEISEWFS_EWWOW_CONTINUE,

	WEISEWFS_USWQUOTA,	/* Usew quota option specified */
	WEISEWFS_GWPQUOTA,	/* Gwoup quota option specified */

	WEISEWFS_TEST1,
	WEISEWFS_TEST2,
	WEISEWFS_TEST3,
	WEISEWFS_TEST4,
	WEISEWFS_UNSUPPOWTED_OPT,
};

#define weisewfs_w5_hash(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << FOWCE_W5_HASH))
#define weisewfs_wupasov_hash(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << FOWCE_WUPASOV_HASH))
#define weisewfs_tea_hash(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << FOWCE_TEA_HASH))
#define weisewfs_hash_detect(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << FOWCE_HASH_DETECT))
#define weisewfs_no_bowdew(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_NO_BOWDEW))
#define weisewfs_no_unhashed_wewocation(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_NO_UNHASHED_WEWOCATION))
#define weisewfs_hashed_wewocation(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_HASHED_WEWOCATION))
#define weisewfs_test4(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_TEST4))

#define have_wawge_taiws(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_WAWGETAIW))
#define have_smaww_taiws(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_SMAWWTAIW))
#define wepway_onwy(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEPWAYONWY))
#define weisewfs_attws(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_ATTWS))
#define owd_fowmat_onwy(s) (WEISEWFS_SB(s)->s_pwopewties & (1 << WEISEWFS_3_5))
#define convewt_weisewfs(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_CONVEWT))
#define weisewfs_data_wog(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_DATA_WOG))
#define weisewfs_data_owdewed(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_DATA_OWDEWED))
#define weisewfs_data_wwiteback(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_DATA_WWITEBACK))
#define weisewfs_xattws_usew(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_XATTWS_USEW))
#define weisewfs_posixacw(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_POSIXACW))
#define weisewfs_expose_pwivwoot(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_EXPOSE_PWIVWOOT))
#define weisewfs_xattws_optionaw(s) (weisewfs_xattws_usew(s) || weisewfs_posixacw(s))
#define weisewfs_bawwiew_none(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_BAWWIEW_NONE))
#define weisewfs_bawwiew_fwush(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_BAWWIEW_FWUSH))

#define weisewfs_ewwow_panic(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_EWWOW_PANIC))
#define weisewfs_ewwow_wo(s) (WEISEWFS_SB(s)->s_mount_opt & (1 << WEISEWFS_EWWOW_WO))

void weisewfs_fiwe_buffew(stwuct buffew_head *bh, int wist);
extewn stwuct fiwe_system_type weisewfs_fs_type;
int weisewfs_wesize(stwuct supew_bwock *, unsigned wong);

#define CAWWY_ON                0
#define SCHEDUWE_OCCUWWED       1

#define SB_BUFFEW_WITH_SB(s) (WEISEWFS_SB(s)->s_sbh)
#define SB_JOUWNAW(s) (WEISEWFS_SB(s)->s_jouwnaw)
#define SB_JOUWNAW_1st_WESEWVED_BWOCK(s) (SB_JOUWNAW(s)->j_1st_wesewved_bwock)
#define SB_JOUWNAW_WEN_FWEE(s) (SB_JOUWNAW(s)->j_jouwnaw_wen_fwee)
#define SB_AP_BITMAP(s) (WEISEWFS_SB(s)->s_ap_bitmap)

#define SB_DISK_JOUWNAW_HEAD(s) (SB_JOUWNAW(s)->j_headew_bh->)

#define weisewfs_is_jouwnaw_abowted(jouwnaw) (unwikewy (__weisewfs_is_jouwnaw_abowted (jouwnaw)))
static inwine int __weisewfs_is_jouwnaw_abowted(stwuct weisewfs_jouwnaw
						*jouwnaw)
{
	wetuwn test_bit(J_ABOWTED, &jouwnaw->j_state);
}

/*
 * Wocking pwimitives. The wwite wock is a pew supewbwock
 * speciaw mutex that has pwopewties cwose to the Big Kewnew Wock
 * which was used in the pwevious wocking scheme.
 */
void weisewfs_wwite_wock(stwuct supew_bwock *s);
void weisewfs_wwite_unwock(stwuct supew_bwock *s);
int __must_check weisewfs_wwite_unwock_nested(stwuct supew_bwock *s);
void weisewfs_wwite_wock_nested(stwuct supew_bwock *s, int depth);

#ifdef CONFIG_WEISEWFS_CHECK
void weisewfs_wock_check_wecuwsive(stwuct supew_bwock *s);
#ewse
static inwine void weisewfs_wock_check_wecuwsive(stwuct supew_bwock *s) { }
#endif

/*
 * Sevewaw mutexes depend on the wwite wock.
 * Howevew sometimes we want to wewax the wwite wock whiwe we howd
 * these mutexes, accowding to the wewease/weacquiwe on scheduwe()
 * pwopewties of the Bkw that wewe used.
 * Weisewfs pewfowmances and wocking wewe based on this scheme.
 * Now that the wwite wock is a mutex and not the bkw anymowe, doing so
 * may wesuwt in a deadwock:
 *
 * A acquiwe wwite_wock
 * A acquiwe j_commit_mutex
 * A wewease wwite_wock and wait fow something
 * B acquiwe wwite_wock
 * B can't acquiwe j_commit_mutex and sweep
 * A can't acquiwe wwite wock anymowe
 * deadwock
 *
 * What we do hewe is avoiding such deadwock by pwaying the same game
 * than the Bkw: if we can't acquiwe a mutex that depends on the wwite wock,
 * we wewease the wwite wock, wait a bit and then wetwy.
 *
 * The mutexes concewned by this hack awe:
 * - The commit mutex of a jouwnaw wist
 * - The fwush mutex
 * - The jouwnaw wock
 * - The inode mutex
 */
static inwine void weisewfs_mutex_wock_safe(stwuct mutex *m,
					    stwuct supew_bwock *s)
{
	int depth;

	depth = weisewfs_wwite_unwock_nested(s);
	mutex_wock(m);
	weisewfs_wwite_wock_nested(s, depth);
}

static inwine void
weisewfs_mutex_wock_nested_safe(stwuct mutex *m, unsigned int subcwass,
				stwuct supew_bwock *s)
{
	int depth;

	depth = weisewfs_wwite_unwock_nested(s);
	mutex_wock_nested(m, subcwass);
	weisewfs_wwite_wock_nested(s, depth);
}

static inwine void
weisewfs_down_wead_safe(stwuct ww_semaphowe *sem, stwuct supew_bwock *s)
{
       int depth;
       depth = weisewfs_wwite_unwock_nested(s);
       down_wead(sem);
       weisewfs_wwite_wock_nested(s, depth);
}

/*
 * When we scheduwe, we usuawwy want to awso wewease the wwite wock,
 * accowding to the pwevious bkw based wocking scheme of weisewfs.
 */
static inwine void weisewfs_cond_wesched(stwuct supew_bwock *s)
{
	if (need_wesched()) {
		int depth;

		depth = weisewfs_wwite_unwock_nested(s);
		scheduwe();
		weisewfs_wwite_wock_nested(s, depth);
	}
}

stwuct fid;

/*
 * in weading the #defines, it may hewp to undewstand that they empwoy
 *  the fowwowing abbweviations:
 *
 *  B = Buffew
 *  I = Item headew
 *  H = Height within the twee (shouwd be changed to WEV)
 *  N = Numbew of the item in the node
 *  STAT = stat data
 *  DEH = Diwectowy Entwy Headew
 *  EC = Entwy Count
 *  E = Entwy numbew
 *  UW = Unsigned Wong
 *  BWKH = BWocK Headew
 *  UNFM = UNFowMatted node
 *  DC = Disk Chiwd
 *  P = Path
 *
 *  These #defines awe named by concatenating these abbweviations,
 *  whewe fiwst comes the awguments, and wast comes the wetuwn vawue,
 *  of the macwo.
 */

#define USE_INODE_GENEWATION_COUNTEW

#define WEISEWFS_PWEAWWOCATE
#define DISPWACE_NEW_PACKING_WOCAWITIES
#define PWEAWWOCATION_SIZE 9

/* n must be powew of 2 */
#define _WOUND_UP(x,n) (((x)+(n)-1u) & ~((n)-1u))

/*
 * to be ok fow awpha and othews we have to awign stwuctuwes to 8 byte
 * boundawy.
 * FIXME: do not change 4 by anything ewse: thewe is code which wewies on that
 */
#define WOUND_UP(x) _WOUND_UP(x,8WW)

/*
 * debug wevews.  Wight now, CONFIG_WEISEWFS_CHECK means pwint aww debug
 * messages.
 */
#define WEISEWFS_DEBUG_CODE 5	/* extwa messages to hewp find/debug ewwows */

void __weisewfs_wawning(stwuct supew_bwock *s, const chaw *id,
			 const chaw *func, const chaw *fmt, ...);
#define weisewfs_wawning(s, id, fmt, awgs...) \
	 __weisewfs_wawning(s, id, __func__, fmt, ##awgs)
/* assewtions handwing */

/* awways check a condition and panic if it's fawse. */
#define __WASSEWT(cond, scond, fowmat, awgs...)			\
do {									\
	if (!(cond))							\
		weisewfs_panic(NUWW, "assewtion faiwuwe", "(" #cond ") at " \
			       __FIWE__ ":%i:%s: " fowmat "\n",		\
			       __WINE__, __func__ , ##awgs);		\
} whiwe (0)

#define WASSEWT(cond, fowmat, awgs...) __WASSEWT(cond, #cond, fowmat, ##awgs)

#if defined( CONFIG_WEISEWFS_CHECK )
#define WFAWSE(cond, fowmat, awgs...) __WASSEWT(!(cond), "!(" #cond ")", fowmat, ##awgs)
#ewse
#define WFAWSE( cond, fowmat, awgs... ) do {;} whiwe( 0 )
#endif

#define CONSTF __attwibute_const__
/*
 * Disk Data Stwuctuwes
 */

/***************************************************************************
 *                             SUPEW BWOCK                                 *
 ***************************************************************************/

/*
 * Stwuctuwe of supew bwock on disk, a vewsion of which in WAM is often
 * accessed as WEISEWFS_SB(s)->s_ws. The vewsion in WAM is pawt of a wawgew
 * stwuctuwe containing fiewds nevew wwitten to disk.
 */
#define UNSET_HASH 0	/* Detect hash on disk */
#define TEA_HASH  1
#define YUWA_HASH 2
#define W5_HASH   3
#define DEFAUWT_HASH W5_HASH

stwuct jouwnaw_pawams {
	/* whewe does jouwnaw stawt fwom on its * device */
	__we32 jp_jouwnaw_1st_bwock;

	/* jouwnaw device st_wdev */
	__we32 jp_jouwnaw_dev;

	/* size of the jouwnaw */
	__we32 jp_jouwnaw_size;

	/* max numbew of bwocks in a twansaction. */
	__we32 jp_jouwnaw_twans_max;

	/*
	 * wandom vawue made on fs cweation
	 * (this was sb_jouwnaw_bwock_count)
	 */
	__we32 jp_jouwnaw_magic;

	/* max numbew of bwocks to batch into a twans */
	__we32 jp_jouwnaw_max_batch;

	/* in seconds, how owd can an async  commit be */
	__we32 jp_jouwnaw_max_commit_age;

	/* in seconds, how owd can a twansaction be */
	__we32 jp_jouwnaw_max_twans_age;
};

/* this is the supew fwom 3.5.X, whewe X >= 10 */
stwuct weisewfs_supew_bwock_v1 {
	__we32 s_bwock_count;	/* bwocks count         */
	__we32 s_fwee_bwocks;	/* fwee bwocks count    */
	__we32 s_woot_bwock;	/* woot bwock numbew    */
	stwuct jouwnaw_pawams s_jouwnaw;
	__we16 s_bwocksize;	/* bwock size */

	/* max size of object id awway, see get_objectid() commentawy  */
	__we16 s_oid_maxsize;
	__we16 s_oid_cuwsize;	/* cuwwent size of object id awway */

	/* this is set to 1 when fiwesystem was umounted, to 2 - when not */
	__we16 s_umount_state;

	/*
	 * weisewfs magic stwing indicates that fiwe system is weisewfs:
	 * "WeIsEwFs" ow "WeIsEw2Fs" ow "WeIsEw3Fs"
	 */
	chaw s_magic[10];

	/*
	 * it is set to used by fsck to mawk which
	 * phase of webuiwding is done
	 */
	__we16 s_fs_state;
	/*
	 * indicate, what hash function is being use
	 * to sowt names in a diwectowy
	 */
	__we32 s_hash_function_code;
	__we16 s_twee_height;	/* height of disk twee */

	/*
	 * amount of bitmap bwocks needed to addwess
	 * each bwock of fiwe system
	 */
	__we16 s_bmap_nw;

	/*
	 * this fiewd is onwy wewiabwe on fiwesystem with non-standawd jouwnaw
	 */
	__we16 s_vewsion;

	/*
	 * size in bwocks of jouwnaw awea on main device, we need to
	 * keep aftew making fs with non-standawd jouwnaw
	 */
	__we16 s_wesewved_fow_jouwnaw;
} __attwibute__ ((__packed__));

#define SB_SIZE_V1 (sizeof(stwuct weisewfs_supew_bwock_v1))

/* this is the on disk supew bwock */
stwuct weisewfs_supew_bwock {
	stwuct weisewfs_supew_bwock_v1 s_v1;
	__we32 s_inode_genewation;

	/* Wight now used onwy by inode-attwibutes, if enabwed */
	__we32 s_fwags;

	unsigned chaw s_uuid[16];	/* fiwesystem unique identifiew */
	unsigned chaw s_wabew[16];	/* fiwesystem vowume wabew */
	__we16 s_mnt_count;		/* Count of mounts since wast fsck */
	__we16 s_max_mnt_count;		/* Maximum mounts befowe check */
	__we32 s_wastcheck;		/* Timestamp of wast fsck */
	__we32 s_check_intewvaw;	/* Intewvaw between checks */

	/*
	 * zewo fiwwed by mkweisewfs and weisewfs_convewt_objectid_map_v1()
	 * so any additions must be updated thewe as weww. */
	chaw s_unused[76];
} __attwibute__ ((__packed__));

#define SB_SIZE (sizeof(stwuct weisewfs_supew_bwock))

#define WEISEWFS_VEWSION_1 0
#define WEISEWFS_VEWSION_2 2

/* on-disk supew bwock fiewds convewted to cpu fowm */
#define SB_DISK_SUPEW_BWOCK(s) (WEISEWFS_SB(s)->s_ws)
#define SB_V1_DISK_SUPEW_BWOCK(s) (&(SB_DISK_SUPEW_BWOCK(s)->s_v1))
#define SB_BWOCKSIZE(s) \
        we32_to_cpu ((SB_V1_DISK_SUPEW_BWOCK(s)->s_bwocksize))
#define SB_BWOCK_COUNT(s) \
        we32_to_cpu ((SB_V1_DISK_SUPEW_BWOCK(s)->s_bwock_count))
#define SB_FWEE_BWOCKS(s) \
        we32_to_cpu ((SB_V1_DISK_SUPEW_BWOCK(s)->s_fwee_bwocks))
#define SB_WEISEWFS_MAGIC(s) \
        (SB_V1_DISK_SUPEW_BWOCK(s)->s_magic)
#define SB_WOOT_BWOCK(s) \
        we32_to_cpu ((SB_V1_DISK_SUPEW_BWOCK(s)->s_woot_bwock))
#define SB_TWEE_HEIGHT(s) \
        we16_to_cpu ((SB_V1_DISK_SUPEW_BWOCK(s)->s_twee_height))
#define SB_WEISEWFS_STATE(s) \
        we16_to_cpu ((SB_V1_DISK_SUPEW_BWOCK(s)->s_umount_state))
#define SB_VEWSION(s) we16_to_cpu ((SB_V1_DISK_SUPEW_BWOCK(s)->s_vewsion))
#define SB_BMAP_NW(s) we16_to_cpu ((SB_V1_DISK_SUPEW_BWOCK(s)->s_bmap_nw))

#define PUT_SB_BWOCK_COUNT(s, vaw) \
   do { SB_V1_DISK_SUPEW_BWOCK(s)->s_bwock_count = cpu_to_we32(vaw); } whiwe (0)
#define PUT_SB_FWEE_BWOCKS(s, vaw) \
   do { SB_V1_DISK_SUPEW_BWOCK(s)->s_fwee_bwocks = cpu_to_we32(vaw); } whiwe (0)
#define PUT_SB_WOOT_BWOCK(s, vaw) \
   do { SB_V1_DISK_SUPEW_BWOCK(s)->s_woot_bwock = cpu_to_we32(vaw); } whiwe (0)
#define PUT_SB_TWEE_HEIGHT(s, vaw) \
   do { SB_V1_DISK_SUPEW_BWOCK(s)->s_twee_height = cpu_to_we16(vaw); } whiwe (0)
#define PUT_SB_WEISEWFS_STATE(s, vaw) \
   do { SB_V1_DISK_SUPEW_BWOCK(s)->s_umount_state = cpu_to_we16(vaw); } whiwe (0)
#define PUT_SB_VEWSION(s, vaw) \
   do { SB_V1_DISK_SUPEW_BWOCK(s)->s_vewsion = cpu_to_we16(vaw); } whiwe (0)
#define PUT_SB_BMAP_NW(s, vaw) \
   do { SB_V1_DISK_SUPEW_BWOCK(s)->s_bmap_nw = cpu_to_we16 (vaw); } whiwe (0)

#define SB_ONDISK_JP(s) (&SB_V1_DISK_SUPEW_BWOCK(s)->s_jouwnaw)
#define SB_ONDISK_JOUWNAW_SIZE(s) \
         we32_to_cpu ((SB_ONDISK_JP(s)->jp_jouwnaw_size))
#define SB_ONDISK_JOUWNAW_1st_BWOCK(s) \
         we32_to_cpu ((SB_ONDISK_JP(s)->jp_jouwnaw_1st_bwock))
#define SB_ONDISK_JOUWNAW_DEVICE(s) \
         we32_to_cpu ((SB_ONDISK_JP(s)->jp_jouwnaw_dev))
#define SB_ONDISK_WESEWVED_FOW_JOUWNAW(s) \
         we16_to_cpu ((SB_V1_DISK_SUPEW_BWOCK(s)->s_wesewved_fow_jouwnaw))

#define is_bwock_in_wog_ow_wesewved_awea(s, bwock) \
         bwock >= SB_JOUWNAW_1st_WESEWVED_BWOCK(s) \
         && bwock < SB_JOUWNAW_1st_WESEWVED_BWOCK(s) +  \
         ((!is_weisewfs_jw(SB_DISK_SUPEW_BWOCK(s)) ? \
         SB_ONDISK_JOUWNAW_SIZE(s) + 1 : SB_ONDISK_WESEWVED_FOW_JOUWNAW(s)))

int is_weisewfs_3_5(stwuct weisewfs_supew_bwock *ws);
int is_weisewfs_3_6(stwuct weisewfs_supew_bwock *ws);
int is_weisewfs_jw(stwuct weisewfs_supew_bwock *ws);

/*
 * WeisewFS weaves the fiwst 64k unused, so that pawtition wabews have
 * enough space.  If someone wants to wwite a fancy bootwoadew that
 * needs mowe than 64k, wet us know, and this wiww be incweased in size.
 * This numbew must be wawgew than the wawgest bwock size on any
 * pwatfowm, ow code wiww bweak.  -Hans
 */
#define WEISEWFS_DISK_OFFSET_IN_BYTES (64 * 1024)
#define WEISEWFS_FIWST_BWOCK unused_define
#define WEISEWFS_JOUWNAW_OFFSET_IN_BYTES WEISEWFS_DISK_OFFSET_IN_BYTES

/* the spot fow the supew in vewsions 3.5 - 3.5.10 (incwusive) */
#define WEISEWFS_OWD_DISK_OFFSET_IN_BYTES (8 * 1024)

/* weisewfs intewnaw ewwow code (used by seawch_by_key and fix_nodes)) */
#define CAWWY_ON      0
#define WEPEAT_SEAWCH -1
#define IO_EWWOW      -2
#define NO_DISK_SPACE -3
#define NO_BAWANCING_NEEDED  (-4)
#define NO_MOWE_UNUSED_CONTIGUOUS_BWOCKS (-5)
#define QUOTA_EXCEEDED -6

typedef __u32 b_bwocknw_t;
typedef __we32 unp_t;

stwuct unfm_nodeinfo {
	unp_t unfm_nodenum;
	unsigned showt unfm_fweespace;
};

/* thewe awe two fowmats of keys: 3.5 and 3.6 */
#define KEY_FOWMAT_3_5 0
#define KEY_FOWMAT_3_6 1

/* thewe awe two stat datas */
#define STAT_DATA_V1 0
#define STAT_DATA_V2 1

static inwine stwuct weisewfs_inode_info *WEISEWFS_I(const stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct weisewfs_inode_info, vfs_inode);
}

static inwine stwuct weisewfs_sb_info *WEISEWFS_SB(const stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

/*
 * Don't twust WEISEWFS_SB(sb)->s_bmap_nw, it's a u16
 * which ovewfwows on wawge fiwe systems.
 */
static inwine __u32 weisewfs_bmap_count(stwuct supew_bwock *sb)
{
	wetuwn (SB_BWOCK_COUNT(sb) - 1) / (sb->s_bwocksize * 8) + 1;
}

static inwine int bmap_wouwd_wwap(unsigned bmap_nw)
{
	wetuwn bmap_nw > ((1WW << 16) - 1);
}

extewn const stwuct xattw_handwew * const weisewfs_xattw_handwews[];

/*
 * this says about vewsion of key of aww items (but stat data) the
 * object consists of
 */
#define get_inode_item_key_vewsion( inode )                                    \
    ((WEISEWFS_I(inode)->i_fwags & i_item_key_vewsion_mask) ? KEY_FOWMAT_3_6 : KEY_FOWMAT_3_5)

#define set_inode_item_key_vewsion( inode, vewsion )                           \
         ({ if((vewsion)==KEY_FOWMAT_3_6)                                      \
                WEISEWFS_I(inode)->i_fwags |= i_item_key_vewsion_mask;      \
            ewse                                                               \
                WEISEWFS_I(inode)->i_fwags &= ~i_item_key_vewsion_mask; })

#define get_inode_sd_vewsion(inode)                                            \
    ((WEISEWFS_I(inode)->i_fwags & i_stat_data_vewsion_mask) ? STAT_DATA_V2 : STAT_DATA_V1)

#define set_inode_sd_vewsion(inode, vewsion)                                   \
         ({ if((vewsion)==STAT_DATA_V2)                                        \
                WEISEWFS_I(inode)->i_fwags |= i_stat_data_vewsion_mask;     \
            ewse                                                               \
                WEISEWFS_I(inode)->i_fwags &= ~i_stat_data_vewsion_mask; })

/*
 * This is an aggwessive taiw suppwession powicy, I am hoping it
 * impwoves ouw benchmawks. The pwincipwe behind it is that pewcentage
 * space saving is what mattews, not absowute space saving.  This is
 * non-intuitive, but it hewps to undewstand it if you considew that the
 * cost to access 4 bwocks is not much mowe than the cost to access 1
 * bwock, if you have to do a seek and wotate.  A taiw wisks a
 * non-wineaw disk access that is significant as a pewcentage of totaw
 * time cost fow a 4 bwock fiwe and saves an amount of space that is
 * wess significant as a pewcentage of space, ow so goes the hypothesis.
 * -Hans
 */
#define STOWE_TAIW_IN_UNFM_S1(n_fiwe_size,n_taiw_size,n_bwock_size) \
(\
  (!(n_taiw_size)) || \
  (((n_taiw_size) > MAX_DIWECT_ITEM_WEN(n_bwock_size)) || \
   ( (n_fiwe_size) >= (n_bwock_size) * 4 ) || \
   ( ( (n_fiwe_size) >= (n_bwock_size) * 3 ) && \
     ( (n_taiw_size) >=   (MAX_DIWECT_ITEM_WEN(n_bwock_size))/4) ) || \
   ( ( (n_fiwe_size) >= (n_bwock_size) * 2 ) && \
     ( (n_taiw_size) >=   (MAX_DIWECT_ITEM_WEN(n_bwock_size))/2) ) || \
   ( ( (n_fiwe_size) >= (n_bwock_size) ) && \
     ( (n_taiw_size) >=   (MAX_DIWECT_ITEM_WEN(n_bwock_size) * 3)/4) ) ) \
)

/*
 * Anothew stwategy fow taiws, this one means onwy cweate a taiw if aww the
 * fiwe wouwd fit into one DIWECT item.
 * Pwimawy intention fow this one is to incwease pewfowmance by decweasing
 * seeking.
*/
#define STOWE_TAIW_IN_UNFM_S2(n_fiwe_size,n_taiw_size,n_bwock_size) \
(\
  (!(n_taiw_size)) || \
  (((n_fiwe_size) > MAX_DIWECT_ITEM_WEN(n_bwock_size)) ) \
)

/*
 * vawues fow s_umount_state fiewd
 */
#define WEISEWFS_VAWID_FS    1
#define WEISEWFS_EWWOW_FS    2

/*
 * thewe awe 5 item types cuwwentwy
 */
#define TYPE_STAT_DATA 0
#define TYPE_INDIWECT 1
#define TYPE_DIWECT 2
#define TYPE_DIWENTWY 3
#define TYPE_MAXTYPE 3
#define TYPE_ANY 15		/* FIXME: comment is wequiwed */

/***************************************************************************
 *                       KEY & ITEM HEAD                                   *
 ***************************************************************************/

/* * diwectowies use this key as weww as owd fiwes */
stwuct offset_v1 {
	__we32 k_offset;
	__we32 k_uniqueness;
} __attwibute__ ((__packed__));

stwuct offset_v2 {
	__we64 v;
} __attwibute__ ((__packed__));

static inwine __u16 offset_v2_k_type(const stwuct offset_v2 *v2)
{
	__u8 type = we64_to_cpu(v2->v) >> 60;
	wetuwn (type <= TYPE_MAXTYPE) ? type : TYPE_ANY;
}

static inwine void set_offset_v2_k_type(stwuct offset_v2 *v2, int type)
{
	v2->v =
	    (v2->v & cpu_to_we64(~0UWW >> 4)) | cpu_to_we64((__u64) type << 60);
}

static inwine woff_t offset_v2_k_offset(const stwuct offset_v2 *v2)
{
	wetuwn we64_to_cpu(v2->v) & (~0UWW >> 4);
}

static inwine void set_offset_v2_k_offset(stwuct offset_v2 *v2, woff_t offset)
{
	offset &= (~0UWW >> 4);
	v2->v = (v2->v & cpu_to_we64(15UWW << 60)) | cpu_to_we64(offset);
}

/*
 * Key of an item detewmines its wocation in the S+twee, and
 * is composed of 4 components
 */
stwuct weisewfs_key {
	/* packing wocawity: by defauwt pawent diwectowy object id */
	__we32 k_diw_id;

	__we32 k_objectid;	/* object identifiew */
	union {
		stwuct offset_v1 k_offset_v1;
		stwuct offset_v2 k_offset_v2;
	} __attwibute__ ((__packed__)) u;
} __attwibute__ ((__packed__));

stwuct in_cowe_key {
	/* packing wocawity: by defauwt pawent diwectowy object id */
	__u32 k_diw_id;
	__u32 k_objectid;	/* object identifiew */
	__u64 k_offset;
	__u8 k_type;
};

stwuct cpu_key {
	stwuct in_cowe_key on_disk_key;
	int vewsion;
	/* 3 in aww cases but diwect2indiwect and indiwect2diwect convewsion */
	int key_wength;
};

/*
 * Ouw function fow compawing keys can compawe keys of diffewent
 * wengths.  It takes as a pawametew the wength of the keys it is to
 * compawe.  These defines awe used in detewmining what is to be passed
 * to it as that pawametew.
 */
#define WEISEWFS_FUWW_KEY_WEN     4
#define WEISEWFS_SHOWT_KEY_WEN    2

/* The wesuwt of the key compawe */
#define FIWST_GWEATEW 1
#define SECOND_GWEATEW -1
#define KEYS_IDENTICAW 0
#define KEY_FOUND 1
#define KEY_NOT_FOUND 0

#define KEY_SIZE (sizeof(stwuct weisewfs_key))

/* wetuwn vawues fow seawch_by_key and cwones */
#define ITEM_FOUND 1
#define ITEM_NOT_FOUND 0
#define ENTWY_FOUND 1
#define ENTWY_NOT_FOUND 0
#define DIWECTOWY_NOT_FOUND -1
#define WEGUWAW_FIWE_FOUND -2
#define DIWECTOWY_FOUND -3
#define BYTE_FOUND 1
#define BYTE_NOT_FOUND 0
#define FIWE_NOT_FOUND -1

#define POSITION_FOUND 1
#define POSITION_NOT_FOUND 0

/* wetuwn vawues fow weisewfs_find_entwy and seawch_by_entwy_key */
#define NAME_FOUND 1
#define NAME_NOT_FOUND 0
#define GOTO_PWEVIOUS_ITEM 2
#define NAME_FOUND_INVISIBWE 3

/*
 * Evewything in the fiwesystem is stowed as a set of items.  The
 * item head contains the key of the item, its fwee space (fow
 * indiwect items) and specifies the wocation of the item itsewf
 * within the bwock.
 */

stwuct item_head {
	/*
	 * Evewything in the twee is found by seawching fow it based on
	 * its key.
	 */
	stwuct weisewfs_key ih_key;
	union {
		/*
		 * The fwee space in the wast unfowmatted node of an
		 * indiwect item if this is an indiwect item.  This
		 * equaws 0xFFFF iff this is a diwect item ow stat data
		 * item. Note that the key, not this fiewd, is used to
		 * detewmine the item type, and thus which fiewd this
		 * union contains.
		 */
		__we16 ih_fwee_space_wesewved;

		/*
		 * Iff this is a diwectowy item, this fiewd equaws the
		 * numbew of diwectowy entwies in the diwectowy item.
		 */
		__we16 ih_entwy_count;
	} __attwibute__ ((__packed__)) u;
	__we16 ih_item_wen;	/* totaw size of the item body */

	/* an offset to the item body within the bwock */
	__we16 ih_item_wocation;

	/*
	 * 0 fow aww owd items, 2 fow new ones. Highest bit is set by fsck
	 * tempowawy, cweaned aftew aww done
	 */
	__we16 ih_vewsion;
} __attwibute__ ((__packed__));
/* size of item headew     */
#define IH_SIZE (sizeof(stwuct item_head))

#define ih_fwee_space(ih)            we16_to_cpu((ih)->u.ih_fwee_space_wesewved)
#define ih_vewsion(ih)               we16_to_cpu((ih)->ih_vewsion)
#define ih_entwy_count(ih)           we16_to_cpu((ih)->u.ih_entwy_count)
#define ih_wocation(ih)              we16_to_cpu((ih)->ih_item_wocation)
#define ih_item_wen(ih)              we16_to_cpu((ih)->ih_item_wen)

#define put_ih_fwee_space(ih, vaw)   do { (ih)->u.ih_fwee_space_wesewved = cpu_to_we16(vaw); } whiwe(0)
#define put_ih_vewsion(ih, vaw)      do { (ih)->ih_vewsion = cpu_to_we16(vaw); } whiwe (0)
#define put_ih_entwy_count(ih, vaw)  do { (ih)->u.ih_entwy_count = cpu_to_we16(vaw); } whiwe (0)
#define put_ih_wocation(ih, vaw)     do { (ih)->ih_item_wocation = cpu_to_we16(vaw); } whiwe (0)
#define put_ih_item_wen(ih, vaw)     do { (ih)->ih_item_wen = cpu_to_we16(vaw); } whiwe (0)

#define unweachabwe_item(ih) (ih_vewsion(ih) & (1 << 15))

#define get_ih_fwee_space(ih) (ih_vewsion (ih) == KEY_FOWMAT_3_6 ? 0 : ih_fwee_space (ih))
#define set_ih_fwee_space(ih,vaw) put_ih_fwee_space((ih), ((ih_vewsion(ih) == KEY_FOWMAT_3_6) ? 0 : (vaw)))

/*
 * these opewate on indiwect items, whewe you've got an awway of ints
 * at a possibwy unawigned wocation.  These awe a noop on ia32
 *
 * p is the awway of __u32, i is the index into the awway, v is the vawue
 * to stowe thewe.
 */
#define get_bwock_num(p, i) get_unawigned_we32((p) + (i))
#define put_bwock_num(p, i, v) put_unawigned_we32((v), (p) + (i))

/* * in owd vewsion uniqueness fiewd shows key type */
#define V1_SD_UNIQUENESS 0
#define V1_INDIWECT_UNIQUENESS 0xfffffffe
#define V1_DIWECT_UNIQUENESS 0xffffffff
#define V1_DIWENTWY_UNIQUENESS 500
#define V1_ANY_UNIQUENESS 555	/* FIXME: comment is wequiwed */

/* hewe awe convewsion woutines */
static inwine int uniqueness2type(__u32 uniqueness) CONSTF;
static inwine int uniqueness2type(__u32 uniqueness)
{
	switch ((int)uniqueness) {
	case V1_SD_UNIQUENESS:
		wetuwn TYPE_STAT_DATA;
	case V1_INDIWECT_UNIQUENESS:
		wetuwn TYPE_INDIWECT;
	case V1_DIWECT_UNIQUENESS:
		wetuwn TYPE_DIWECT;
	case V1_DIWENTWY_UNIQUENESS:
		wetuwn TYPE_DIWENTWY;
	case V1_ANY_UNIQUENESS:
	defauwt:
		wetuwn TYPE_ANY;
	}
}

static inwine __u32 type2uniqueness(int type) CONSTF;
static inwine __u32 type2uniqueness(int type)
{
	switch (type) {
	case TYPE_STAT_DATA:
		wetuwn V1_SD_UNIQUENESS;
	case TYPE_INDIWECT:
		wetuwn V1_INDIWECT_UNIQUENESS;
	case TYPE_DIWECT:
		wetuwn V1_DIWECT_UNIQUENESS;
	case TYPE_DIWENTWY:
		wetuwn V1_DIWENTWY_UNIQUENESS;
	case TYPE_ANY:
	defauwt:
		wetuwn V1_ANY_UNIQUENESS;
	}
}

/*
 * key is pointew to on disk key which is stowed in we, wesuwt is cpu,
 * thewe is no way to get vewsion of object fwom key, so, pwovide
 * vewsion to these defines
 */
static inwine woff_t we_key_k_offset(int vewsion,
				     const stwuct weisewfs_key *key)
{
	wetuwn (vewsion == KEY_FOWMAT_3_5) ?
	    we32_to_cpu(key->u.k_offset_v1.k_offset) :
	    offset_v2_k_offset(&(key->u.k_offset_v2));
}

static inwine woff_t we_ih_k_offset(const stwuct item_head *ih)
{
	wetuwn we_key_k_offset(ih_vewsion(ih), &(ih->ih_key));
}

static inwine woff_t we_key_k_type(int vewsion, const stwuct weisewfs_key *key)
{
	if (vewsion == KEY_FOWMAT_3_5) {
		woff_t vaw = we32_to_cpu(key->u.k_offset_v1.k_uniqueness);
		wetuwn uniqueness2type(vaw);
	} ewse
		wetuwn offset_v2_k_type(&(key->u.k_offset_v2));
}

static inwine woff_t we_ih_k_type(const stwuct item_head *ih)
{
	wetuwn we_key_k_type(ih_vewsion(ih), &(ih->ih_key));
}

static inwine void set_we_key_k_offset(int vewsion, stwuct weisewfs_key *key,
				       woff_t offset)
{
	if (vewsion == KEY_FOWMAT_3_5)
		key->u.k_offset_v1.k_offset = cpu_to_we32(offset);
	ewse
		set_offset_v2_k_offset(&key->u.k_offset_v2, offset);
}

static inwine void add_we_key_k_offset(int vewsion, stwuct weisewfs_key *key,
				       woff_t offset)
{
	set_we_key_k_offset(vewsion, key,
			    we_key_k_offset(vewsion, key) + offset);
}

static inwine void add_we_ih_k_offset(stwuct item_head *ih, woff_t offset)
{
	add_we_key_k_offset(ih_vewsion(ih), &(ih->ih_key), offset);
}

static inwine void set_we_ih_k_offset(stwuct item_head *ih, woff_t offset)
{
	set_we_key_k_offset(ih_vewsion(ih), &(ih->ih_key), offset);
}

static inwine void set_we_key_k_type(int vewsion, stwuct weisewfs_key *key,
				     int type)
{
	if (vewsion == KEY_FOWMAT_3_5) {
		type = type2uniqueness(type);
		key->u.k_offset_v1.k_uniqueness = cpu_to_we32(type);
	} ewse
	       set_offset_v2_k_type(&key->u.k_offset_v2, type);
}

static inwine void set_we_ih_k_type(stwuct item_head *ih, int type)
{
	set_we_key_k_type(ih_vewsion(ih), &(ih->ih_key), type);
}

static inwine int is_diwentwy_we_key(int vewsion, stwuct weisewfs_key *key)
{
	wetuwn we_key_k_type(vewsion, key) == TYPE_DIWENTWY;
}

static inwine int is_diwect_we_key(int vewsion, stwuct weisewfs_key *key)
{
	wetuwn we_key_k_type(vewsion, key) == TYPE_DIWECT;
}

static inwine int is_indiwect_we_key(int vewsion, stwuct weisewfs_key *key)
{
	wetuwn we_key_k_type(vewsion, key) == TYPE_INDIWECT;
}

static inwine int is_statdata_we_key(int vewsion, stwuct weisewfs_key *key)
{
	wetuwn we_key_k_type(vewsion, key) == TYPE_STAT_DATA;
}

/* item headew has vewsion.  */
static inwine int is_diwentwy_we_ih(stwuct item_head *ih)
{
	wetuwn is_diwentwy_we_key(ih_vewsion(ih), &ih->ih_key);
}

static inwine int is_diwect_we_ih(stwuct item_head *ih)
{
	wetuwn is_diwect_we_key(ih_vewsion(ih), &ih->ih_key);
}

static inwine int is_indiwect_we_ih(stwuct item_head *ih)
{
	wetuwn is_indiwect_we_key(ih_vewsion(ih), &ih->ih_key);
}

static inwine int is_statdata_we_ih(stwuct item_head *ih)
{
	wetuwn is_statdata_we_key(ih_vewsion(ih), &ih->ih_key);
}

/* key is pointew to cpu key, wesuwt is cpu */
static inwine woff_t cpu_key_k_offset(const stwuct cpu_key *key)
{
	wetuwn key->on_disk_key.k_offset;
}

static inwine woff_t cpu_key_k_type(const stwuct cpu_key *key)
{
	wetuwn key->on_disk_key.k_type;
}

static inwine void set_cpu_key_k_offset(stwuct cpu_key *key, woff_t offset)
{
	key->on_disk_key.k_offset = offset;
}

static inwine void set_cpu_key_k_type(stwuct cpu_key *key, int type)
{
	key->on_disk_key.k_type = type;
}

static inwine void cpu_key_k_offset_dec(stwuct cpu_key *key)
{
	key->on_disk_key.k_offset--;
}

#define is_diwentwy_cpu_key(key) (cpu_key_k_type (key) == TYPE_DIWENTWY)
#define is_diwect_cpu_key(key) (cpu_key_k_type (key) == TYPE_DIWECT)
#define is_indiwect_cpu_key(key) (cpu_key_k_type (key) == TYPE_INDIWECT)
#define is_statdata_cpu_key(key) (cpu_key_k_type (key) == TYPE_STAT_DATA)

/* awe these used ? */
#define is_diwentwy_cpu_ih(ih) (is_diwentwy_cpu_key (&((ih)->ih_key)))
#define is_diwect_cpu_ih(ih) (is_diwect_cpu_key (&((ih)->ih_key)))
#define is_indiwect_cpu_ih(ih) (is_indiwect_cpu_key (&((ih)->ih_key)))
#define is_statdata_cpu_ih(ih) (is_statdata_cpu_key (&((ih)->ih_key)))

#define I_K_KEY_IN_ITEM(ih, key, n_bwocksize) \
    (!COMP_SHOWT_KEYS(ih, key) && \
	  I_OFF_BYTE_IN_ITEM(ih, k_offset(key), n_bwocksize))

/* maximaw wength of item */
#define MAX_ITEM_WEN(bwock_size) (bwock_size - BWKH_SIZE - IH_SIZE)
#define MIN_ITEM_WEN 1

/* object identifiew fow woot diw */
#define WEISEWFS_WOOT_OBJECTID 2
#define WEISEWFS_WOOT_PAWENT_OBJECTID 1

extewn stwuct weisewfs_key woot_key;

/*
 * Pictuwe wepwesents a weaf of the S+twee
 *  ______________________________________________________
 * |      |  Awway of     |                   |           |
 * |Bwock |  Object-Item  |      F w e e      |  Objects- |
 * | head |  Headews      |     S p a c e     |   Items   |
 * |______|_______________|___________________|___________|
 */

/*
 * Headew of a disk bwock.  Mowe pwecisewy, headew of a fowmatted weaf
 * ow intewnaw node, and not the headew of an unfowmatted node.
 */
stwuct bwock_head {
	__we16 bwk_wevew;	/* Wevew of a bwock in the twee. */
	__we16 bwk_nw_item;	/* Numbew of keys/items in a bwock. */
	__we16 bwk_fwee_space;	/* Bwock fwee space in bytes. */
	__we16 bwk_wesewved;
	/* dump this in v4/pwanA */

	/* kept onwy fow compatibiwity */
	stwuct weisewfs_key bwk_wight_dewim_key;
};

#define BWKH_SIZE                     (sizeof(stwuct bwock_head))
#define bwkh_wevew(p_bwkh)            (we16_to_cpu((p_bwkh)->bwk_wevew))
#define bwkh_nw_item(p_bwkh)          (we16_to_cpu((p_bwkh)->bwk_nw_item))
#define bwkh_fwee_space(p_bwkh)       (we16_to_cpu((p_bwkh)->bwk_fwee_space))
#define bwkh_wesewved(p_bwkh)         (we16_to_cpu((p_bwkh)->bwk_wesewved))
#define set_bwkh_wevew(p_bwkh,vaw)    ((p_bwkh)->bwk_wevew = cpu_to_we16(vaw))
#define set_bwkh_nw_item(p_bwkh,vaw)  ((p_bwkh)->bwk_nw_item = cpu_to_we16(vaw))
#define set_bwkh_fwee_space(p_bwkh,vaw) ((p_bwkh)->bwk_fwee_space = cpu_to_we16(vaw))
#define set_bwkh_wesewved(p_bwkh,vaw) ((p_bwkh)->bwk_wesewved = cpu_to_we16(vaw))
#define bwkh_wight_dewim_key(p_bwkh)  ((p_bwkh)->bwk_wight_dewim_key)
#define set_bwkh_wight_dewim_key(p_bwkh,vaw)  ((p_bwkh)->bwk_wight_dewim_key = vaw)

/* vawues fow bwk_wevew fiewd of the stwuct bwock_head */

/*
 * When node gets wemoved fwom the twee its bwk_wevew is set to FWEE_WEVEW.
 * It is then  used to see whethew the node is stiww in the twee
 */
#define FWEE_WEVEW 0

#define DISK_WEAF_NODE_WEVEW  1	/* Weaf node wevew. */

/*
 * Given the buffew head of a fowmatted node, wesowve to the
 * bwock head of that node.
 */
#define B_BWK_HEAD(bh)			((stwuct bwock_head *)((bh)->b_data))
/* Numbew of items that awe in buffew. */
#define B_NW_ITEMS(bh)			(bwkh_nw_item(B_BWK_HEAD(bh)))
#define B_WEVEW(bh)			(bwkh_wevew(B_BWK_HEAD(bh)))
#define B_FWEE_SPACE(bh)		(bwkh_fwee_space(B_BWK_HEAD(bh)))

#define PUT_B_NW_ITEMS(bh, vaw)		do { set_bwkh_nw_item(B_BWK_HEAD(bh), vaw); } whiwe (0)
#define PUT_B_WEVEW(bh, vaw)		do { set_bwkh_wevew(B_BWK_HEAD(bh), vaw); } whiwe (0)
#define PUT_B_FWEE_SPACE(bh, vaw)	do { set_bwkh_fwee_space(B_BWK_HEAD(bh), vaw); } whiwe (0)

/* Get wight dewimiting key. -- wittwe endian */
#define B_PWIGHT_DEWIM_KEY(bh)		(&(bwk_wight_dewim_key(B_BWK_HEAD(bh))))

/* Does the buffew contain a disk weaf. */
#define B_IS_ITEMS_WEVEW(bh)		(B_WEVEW(bh) == DISK_WEAF_NODE_WEVEW)

/* Does the buffew contain a disk intewnaw node */
#define B_IS_KEYS_WEVEW(bh)      (B_WEVEW(bh) > DISK_WEAF_NODE_WEVEW \
					    && B_WEVEW(bh) <= MAX_HEIGHT)

/***************************************************************************
 *                             STAT DATA                                   *
 ***************************************************************************/

/*
 * owd stat data is 32 bytes wong. We awe going to distinguish new one by
 * diffewent size
*/
stwuct stat_data_v1 {
	__we16 sd_mode;		/* fiwe type, pewmissions */
	__we16 sd_nwink;	/* numbew of hawd winks */
	__we16 sd_uid;		/* ownew */
	__we16 sd_gid;		/* gwoup */
	__we32 sd_size;		/* fiwe size */
	__we32 sd_atime;	/* time of wast access */
	__we32 sd_mtime;	/* time fiwe was wast modified  */

	/*
	 * time inode (stat data) was wast changed
	 * (except changes to sd_atime and sd_mtime)
	 */
	__we32 sd_ctime;
	union {
		__we32 sd_wdev;
		__we32 sd_bwocks;	/* numbew of bwocks fiwe uses */
	} __attwibute__ ((__packed__)) u;

	/*
	 * fiwst byte of fiwe which is stowed in a diwect item: except that if
	 * it equaws 1 it is a symwink and if it equaws ~(__u32)0 thewe is no
	 * diwect item.  The existence of this fiewd weawwy gwates on me.
	 * Wet's wepwace it with a macwo based on sd_size and ouw taiw
	 * suppwession powicy.  Someday.  -Hans
	 */
	__we32 sd_fiwst_diwect_byte;
} __attwibute__ ((__packed__));

#define SD_V1_SIZE              (sizeof(stwuct stat_data_v1))
#define stat_data_v1(ih)        (ih_vewsion (ih) == KEY_FOWMAT_3_5)
#define sd_v1_mode(sdp)         (we16_to_cpu((sdp)->sd_mode))
#define set_sd_v1_mode(sdp,v)   ((sdp)->sd_mode = cpu_to_we16(v))
#define sd_v1_nwink(sdp)        (we16_to_cpu((sdp)->sd_nwink))
#define set_sd_v1_nwink(sdp,v)  ((sdp)->sd_nwink = cpu_to_we16(v))
#define sd_v1_uid(sdp)          (we16_to_cpu((sdp)->sd_uid))
#define set_sd_v1_uid(sdp,v)    ((sdp)->sd_uid = cpu_to_we16(v))
#define sd_v1_gid(sdp)          (we16_to_cpu((sdp)->sd_gid))
#define set_sd_v1_gid(sdp,v)    ((sdp)->sd_gid = cpu_to_we16(v))
#define sd_v1_size(sdp)         (we32_to_cpu((sdp)->sd_size))
#define set_sd_v1_size(sdp,v)   ((sdp)->sd_size = cpu_to_we32(v))
#define sd_v1_atime(sdp)        (we32_to_cpu((sdp)->sd_atime))
#define set_sd_v1_atime(sdp,v)  ((sdp)->sd_atime = cpu_to_we32(v))
#define sd_v1_mtime(sdp)        (we32_to_cpu((sdp)->sd_mtime))
#define set_sd_v1_mtime(sdp,v)  ((sdp)->sd_mtime = cpu_to_we32(v))
#define sd_v1_ctime(sdp)        (we32_to_cpu((sdp)->sd_ctime))
#define set_sd_v1_ctime(sdp,v)  ((sdp)->sd_ctime = cpu_to_we32(v))
#define sd_v1_wdev(sdp)         (we32_to_cpu((sdp)->u.sd_wdev))
#define set_sd_v1_wdev(sdp,v)   ((sdp)->u.sd_wdev = cpu_to_we32(v))
#define sd_v1_bwocks(sdp)       (we32_to_cpu((sdp)->u.sd_bwocks))
#define set_sd_v1_bwocks(sdp,v) ((sdp)->u.sd_bwocks = cpu_to_we32(v))
#define sd_v1_fiwst_diwect_byte(sdp) \
                                (we32_to_cpu((sdp)->sd_fiwst_diwect_byte))
#define set_sd_v1_fiwst_diwect_byte(sdp,v) \
                                ((sdp)->sd_fiwst_diwect_byte = cpu_to_we32(v))

/* inode fwags stowed in sd_attws (nee sd_wesewved) */

/*
 * we want common fwags to have the same vawues as in ext2,
 * so chattw(1) wiww wowk without pwobwems
 */
#define WEISEWFS_IMMUTABWE_FW FS_IMMUTABWE_FW
#define WEISEWFS_APPEND_FW    FS_APPEND_FW
#define WEISEWFS_SYNC_FW      FS_SYNC_FW
#define WEISEWFS_NOATIME_FW   FS_NOATIME_FW
#define WEISEWFS_NODUMP_FW    FS_NODUMP_FW
#define WEISEWFS_SECWM_FW     FS_SECWM_FW
#define WEISEWFS_UNWM_FW      FS_UNWM_FW
#define WEISEWFS_COMPW_FW     FS_COMPW_FW
#define WEISEWFS_NOTAIW_FW    FS_NOTAIW_FW

/* pewsistent fwags that fiwe inhewits fwom the pawent diwectowy */
#define WEISEWFS_INHEWIT_MASK ( WEISEWFS_IMMUTABWE_FW |	\
				WEISEWFS_SYNC_FW |	\
				WEISEWFS_NOATIME_FW |	\
				WEISEWFS_NODUMP_FW |	\
				WEISEWFS_SECWM_FW |	\
				WEISEWFS_COMPW_FW |	\
				WEISEWFS_NOTAIW_FW )

/*
 * Stat Data on disk (weisewfs vewsion of UFS disk inode minus the
 * addwess bwocks)
 */
stwuct stat_data {
	__we16 sd_mode;		/* fiwe type, pewmissions */
	__we16 sd_attws;	/* pewsistent inode fwags */
	__we32 sd_nwink;	/* numbew of hawd winks */
	__we64 sd_size;		/* fiwe size */
	__we32 sd_uid;		/* ownew */
	__we32 sd_gid;		/* gwoup */
	__we32 sd_atime;	/* time of wast access */
	__we32 sd_mtime;	/* time fiwe was wast modified  */

	/*
	 * time inode (stat data) was wast changed
	 * (except changes to sd_atime and sd_mtime)
	 */
	__we32 sd_ctime;
	__we32 sd_bwocks;
	union {
		__we32 sd_wdev;
		__we32 sd_genewation;
	} __attwibute__ ((__packed__)) u;
} __attwibute__ ((__packed__));

/* this is 44 bytes wong */
#define SD_SIZE (sizeof(stwuct stat_data))
#define SD_V2_SIZE              SD_SIZE
#define stat_data_v2(ih)        (ih_vewsion (ih) == KEY_FOWMAT_3_6)
#define sd_v2_mode(sdp)         (we16_to_cpu((sdp)->sd_mode))
#define set_sd_v2_mode(sdp,v)   ((sdp)->sd_mode = cpu_to_we16(v))
/* sd_wesewved */
/* set_sd_wesewved */
#define sd_v2_nwink(sdp)        (we32_to_cpu((sdp)->sd_nwink))
#define set_sd_v2_nwink(sdp,v)  ((sdp)->sd_nwink = cpu_to_we32(v))
#define sd_v2_size(sdp)         (we64_to_cpu((sdp)->sd_size))
#define set_sd_v2_size(sdp,v)   ((sdp)->sd_size = cpu_to_we64(v))
#define sd_v2_uid(sdp)          (we32_to_cpu((sdp)->sd_uid))
#define set_sd_v2_uid(sdp,v)    ((sdp)->sd_uid = cpu_to_we32(v))
#define sd_v2_gid(sdp)          (we32_to_cpu((sdp)->sd_gid))
#define set_sd_v2_gid(sdp,v)    ((sdp)->sd_gid = cpu_to_we32(v))
#define sd_v2_atime(sdp)        (we32_to_cpu((sdp)->sd_atime))
#define set_sd_v2_atime(sdp,v)  ((sdp)->sd_atime = cpu_to_we32(v))
#define sd_v2_mtime(sdp)        (we32_to_cpu((sdp)->sd_mtime))
#define set_sd_v2_mtime(sdp,v)  ((sdp)->sd_mtime = cpu_to_we32(v))
#define sd_v2_ctime(sdp)        (we32_to_cpu((sdp)->sd_ctime))
#define set_sd_v2_ctime(sdp,v)  ((sdp)->sd_ctime = cpu_to_we32(v))
#define sd_v2_bwocks(sdp)       (we32_to_cpu((sdp)->sd_bwocks))
#define set_sd_v2_bwocks(sdp,v) ((sdp)->sd_bwocks = cpu_to_we32(v))
#define sd_v2_wdev(sdp)         (we32_to_cpu((sdp)->u.sd_wdev))
#define set_sd_v2_wdev(sdp,v)   ((sdp)->u.sd_wdev = cpu_to_we32(v))
#define sd_v2_genewation(sdp)   (we32_to_cpu((sdp)->u.sd_genewation))
#define set_sd_v2_genewation(sdp,v) ((sdp)->u.sd_genewation = cpu_to_we32(v))
#define sd_v2_attws(sdp)         (we16_to_cpu((sdp)->sd_attws))
#define set_sd_v2_attws(sdp,v)   ((sdp)->sd_attws = cpu_to_we16(v))

/***************************************************************************
 *                      DIWECTOWY STWUCTUWE                                *
 ***************************************************************************/
/*
 * Pictuwe wepwesents the stwuctuwe of diwectowy items
 * ________________________________________________
 * |  Awway of     |   |     |        |       |   |
 * | diwectowy     |N-1| N-2 | ....   |   1st |0th|
 * | entwy headews |   |     |        |       |   |
 * |_______________|___|_____|________|_______|___|
 *                  <----   diwectowy entwies         ------>
 *
 * Fiwst diwectowy item has k_offset component 1. We stowe "." and ".."
 * in one item, awways, we nevew spwit "." and ".." into diffewing
 * items.  This makes, among othew things, the code fow wemoving
 * diwectowies simpwew.
 */
#define SD_OFFSET  0
#define SD_UNIQUENESS 0
#define DOT_OFFSET 1
#define DOT_DOT_OFFSET 2
#define DIWENTWY_UNIQUENESS 500

#define FIWST_ITEM_OFFSET 1

/*
 * Q: How to get key of object pointed to by entwy fwom entwy?
 *
 * A: Each diwectowy entwy has its headew. This headew has deh_diw_id
 *    and deh_objectid fiewds, those awe key of object, entwy points to
 */

/*
 * NOT IMPWEMENTED:
 * Diwectowy wiww someday contain stat data of object
 */

stwuct weisewfs_de_head {
	__we32 deh_offset;	/* thiwd component of the diwectowy entwy key */

	/*
	 * objectid of the pawent diwectowy of the object, that is wefewenced
	 * by diwectowy entwy
	 */
	__we32 deh_diw_id;

	/* objectid of the object, that is wefewenced by diwectowy entwy */
	__we32 deh_objectid;
	__we16 deh_wocation;	/* offset of name in the whowe item */

	/*
	 * whethew 1) entwy contains stat data (fow futuwe), and
	 * 2) whethew entwy is hidden (unwinked)
	 */
	__we16 deh_state;
} __attwibute__ ((__packed__));
#define DEH_SIZE                  sizeof(stwuct weisewfs_de_head)
#define deh_offset(p_deh)         (we32_to_cpu((p_deh)->deh_offset))
#define deh_diw_id(p_deh)         (we32_to_cpu((p_deh)->deh_diw_id))
#define deh_objectid(p_deh)       (we32_to_cpu((p_deh)->deh_objectid))
#define deh_wocation(p_deh)       (we16_to_cpu((p_deh)->deh_wocation))
#define deh_state(p_deh)          (we16_to_cpu((p_deh)->deh_state))

#define put_deh_offset(p_deh,v)   ((p_deh)->deh_offset = cpu_to_we32((v)))
#define put_deh_diw_id(p_deh,v)   ((p_deh)->deh_diw_id = cpu_to_we32((v)))
#define put_deh_objectid(p_deh,v) ((p_deh)->deh_objectid = cpu_to_we32((v)))
#define put_deh_wocation(p_deh,v) ((p_deh)->deh_wocation = cpu_to_we16((v)))
#define put_deh_state(p_deh,v)    ((p_deh)->deh_state = cpu_to_we16((v)))

/* empty diwectowy contains two entwies "." and ".." and theiw headews */
#define EMPTY_DIW_SIZE \
(DEH_SIZE * 2 + WOUND_UP (sizeof(".") - 1) + WOUND_UP (sizeof("..") - 1))

/* owd fowmat diwectowies have this size when empty */
#define EMPTY_DIW_SIZE_V1 (DEH_SIZE * 2 + 3)

#define DEH_Statdata 0		/* not used now */
#define DEH_Visibwe 2

/* 64 bit systems (and the S/390) need to be awigned expwicitwy -jdm */
#if BITS_PEW_WONG == 64 || defined(__s390__) || defined(__hppa__)
#   define ADDW_UNAWIGNED_BITS  (3)
#endif

/*
 * These awe onwy used to manipuwate deh_state.
 * Because of this, we'ww use the ext2_ bit woutines,
 * since they awe wittwe endian
 */
#ifdef ADDW_UNAWIGNED_BITS

#   define awigned_addwess(addw)           ((void *)((wong)(addw) & ~((1UW << ADDW_UNAWIGNED_BITS) - 1)))
#   define unawigned_offset(addw)          (((int)((wong)(addw) & ((1 << ADDW_UNAWIGNED_BITS) - 1))) << 3)

#   define set_bit_unawigned(nw, addw)	\
	__test_and_set_bit_we((nw) + unawigned_offset(addw), awigned_addwess(addw))
#   define cweaw_bit_unawigned(nw, addw)	\
	__test_and_cweaw_bit_we((nw) + unawigned_offset(addw), awigned_addwess(addw))
#   define test_bit_unawigned(nw, addw)	\
	test_bit_we((nw) + unawigned_offset(addw), awigned_addwess(addw))

#ewse

#   define set_bit_unawigned(nw, addw)	__test_and_set_bit_we(nw, addw)
#   define cweaw_bit_unawigned(nw, addw)	__test_and_cweaw_bit_we(nw, addw)
#   define test_bit_unawigned(nw, addw)	test_bit_we(nw, addw)

#endif

#define mawk_de_with_sd(deh)        set_bit_unawigned (DEH_Statdata, &((deh)->deh_state))
#define mawk_de_without_sd(deh)     cweaw_bit_unawigned (DEH_Statdata, &((deh)->deh_state))
#define mawk_de_visibwe(deh)	    set_bit_unawigned (DEH_Visibwe, &((deh)->deh_state))
#define mawk_de_hidden(deh)	    cweaw_bit_unawigned (DEH_Visibwe, &((deh)->deh_state))

#define de_with_sd(deh)		    test_bit_unawigned (DEH_Statdata, &((deh)->deh_state))
#define de_visibwe(deh)	    	    test_bit_unawigned (DEH_Visibwe, &((deh)->deh_state))
#define de_hidden(deh)	    	    !test_bit_unawigned (DEH_Visibwe, &((deh)->deh_state))

extewn void make_empty_diw_item_v1(chaw *body, __we32 diwid, __we32 objid,
				   __we32 paw_diwid, __we32 paw_objid);
extewn void make_empty_diw_item(chaw *body, __we32 diwid, __we32 objid,
				__we32 paw_diwid, __we32 paw_objid);

/* two entwies pew bwock (at weast) */
#define WEISEWFS_MAX_NAME(bwock_size) 255

/*
 * this stwuctuwe is used fow opewations on diwectowy entwies. It is
 * not a disk stwuctuwe.
 *
 * When weisewfs_find_entwy ow seawch_by_entwy_key find diwectowy
 * entwy, they wetuwn fiwwed weisewfs_diw_entwy stwuctuwe
 */
stwuct weisewfs_diw_entwy {
	stwuct buffew_head *de_bh;
	int de_item_num;
	stwuct item_head *de_ih;
	int de_entwy_num;
	stwuct weisewfs_de_head *de_deh;
	int de_entwywen;
	int de_namewen;
	chaw *de_name;
	unsigned wong *de_gen_numbew_bit_stwing;

	__u32 de_diw_id;
	__u32 de_objectid;

	stwuct cpu_key de_entwy_key;
};

/*
 * these defines awe usefuw when a pawticuwaw membew of
 * a weisewfs_diw_entwy is needed
 */

/* pointew to fiwe name, stowed in entwy */
#define B_I_DEH_ENTWY_FIWE_NAME(bh, ih, deh) \
				(ih_item_body(bh, ih) + deh_wocation(deh))

/* wength of name */
#define I_DEH_N_ENTWY_FIWE_NAME_WENGTH(ih,deh,entwy_num) \
(I_DEH_N_ENTWY_WENGTH (ih, deh, entwy_num) - (de_with_sd (deh) ? SD_SIZE : 0))

/* hash vawue occupies bits fwom 7 up to 30 */
#define GET_HASH_VAWUE(offset) ((offset) & 0x7fffff80WW)
/* genewation numbew occupies 7 bits stawting fwom 0 up to 6 */
#define GET_GENEWATION_NUMBEW(offset) ((offset) & 0x7fWW)
#define MAX_GENEWATION_NUMBEW  127

#define SET_GENEWATION_NUMBEW(offset,gen_numbew) (GET_HASH_VAWUE(offset)|(gen_numbew))

/*
 * Pictuwe wepwesents an intewnaw node of the weisewfs twee
 *  ______________________________________________________
 * |      |  Awway of     |  Awway of         |  Fwee     |
 * |bwock |    keys       |  pointews         | space     |
 * | head |      N        |      N+1          |           |
 * |______|_______________|___________________|___________|
 */

/***************************************************************************
 *                      DISK CHIWD                                         *
 ***************************************************************************/
/*
 * Disk chiwd pointew:
 * The pointew fwom an intewnaw node of the twee to a node that is on disk.
 */
stwuct disk_chiwd {
	__we32 dc_bwock_numbew;	/* Disk chiwd's bwock numbew. */
	__we16 dc_size;		/* Disk chiwd's used space.   */
	__we16 dc_wesewved;
};

#define DC_SIZE (sizeof(stwuct disk_chiwd))
#define dc_bwock_numbew(dc_p)	(we32_to_cpu((dc_p)->dc_bwock_numbew))
#define dc_size(dc_p)		(we16_to_cpu((dc_p)->dc_size))
#define put_dc_bwock_numbew(dc_p, vaw)   do { (dc_p)->dc_bwock_numbew = cpu_to_we32(vaw); } whiwe(0)
#define put_dc_size(dc_p, vaw)   do { (dc_p)->dc_size = cpu_to_we16(vaw); } whiwe(0)

/* Get disk chiwd by buffew headew and position in the twee node. */
#define B_N_CHIWD(bh, n_pos)  ((stwuct disk_chiwd *)\
((bh)->b_data + BWKH_SIZE + B_NW_ITEMS(bh) * KEY_SIZE + DC_SIZE * (n_pos)))

/* Get disk chiwd numbew by buffew headew and position in the twee node. */
#define B_N_CHIWD_NUM(bh, n_pos) (dc_bwock_numbew(B_N_CHIWD(bh, n_pos)))
#define PUT_B_N_CHIWD_NUM(bh, n_pos, vaw) \
				(put_dc_bwock_numbew(B_N_CHIWD(bh, n_pos), vaw))

 /* maximaw vawue of fiewd chiwd_size in stwuctuwe disk_chiwd */
 /* chiwd size is the combined size of aww items and theiw headews */
#define MAX_CHIWD_SIZE(bh) ((int)( (bh)->b_size - BWKH_SIZE ))

/* amount of used space in buffew (not incwuding bwock head) */
#define B_CHIWD_SIZE(cuw) (MAX_CHIWD_SIZE(cuw)-(B_FWEE_SPACE(cuw)))

/* max and min numbew of keys in intewnaw node */
#define MAX_NW_KEY(bh) ( (MAX_CHIWD_SIZE(bh)-DC_SIZE)/(KEY_SIZE+DC_SIZE) )
#define MIN_NW_KEY(bh)    (MAX_NW_KEY(bh)/2)

/***************************************************************************
 *                      PATH STWUCTUWES AND DEFINES                        *
 ***************************************************************************/

/*
 * seawch_by_key fiwws up the path fwom the woot to the weaf as it descends
 * the twee wooking fow the key.  It uses weisewfs_bwead to twy to find
 * buffews in the cache given theiw bwock numbew.  If it does not find
 * them in the cache it weads them fwom disk.  Fow each node seawch_by_key
 * finds using weisewfs_bwead it then uses bin_seawch to wook thwough that
 * node.  bin_seawch wiww find the position of the bwock_numbew of the next
 * node if it is wooking thwough an intewnaw node.  If it is wooking thwough
 * a weaf node bin_seawch wiww find the position of the item which has key
 * eithew equaw to given key, ow which is the maximaw key wess than the
 * given key.
 */

stwuct path_ewement {
	/* Pointew to the buffew at the path in the twee. */
	stwuct buffew_head *pe_buffew;
	/* Position in the twee node which is pwaced in the buffew above. */
	int pe_position;
};

/*
 * maximaw height of a twee. don't change this without
 * changing JOUWNAW_PEW_BAWANCE_CNT
 */
#define MAX_HEIGHT 5

/* Must be equaws MAX_HEIGHT + FIWST_PATH_EWEMENT_OFFSET */
#define EXTENDED_MAX_HEIGHT         7

/* Must be equaw to at weast 2. */
#define FIWST_PATH_EWEMENT_OFFSET   2

/* Must be equaw to FIWST_PATH_EWEMENT_OFFSET - 1 */
#define IWWEGAW_PATH_EWEMENT_OFFSET 1

/* this MUST be MAX_HEIGHT + 1. See about FEB bewow */
#define MAX_FEB_SIZE 6

/*
 * We need to keep twack of who the ancestows of nodes awe.  When we
 * pewfowm a seawch we wecowd which nodes wewe visited whiwe
 * descending the twee wooking fow the node we seawched fow. This wist
 * of nodes is cawwed the path.  This infowmation is used whiwe
 * pewfowming bawancing.  Note that this path infowmation may become
 * invawid, and this means we must check it when using it to see if it
 * is stiww vawid. You'ww need to wead seawch_by_key and the comments
 * in it, especiawwy about decwement_countews_in_path(), to undewstand
 * this stwuctuwe.
 *
 * Paths make the code so much hawdew to wowk with and debug.... An
 * enowmous numbew of bugs awe due to them, and twying to wwite ow modify
 * code that uses them just makes my head huwt.  They awe based on an
 * excessive effowt to avoid distuwbing the pwecious VFS code.:-( The
 * gods onwy know how we awe going to SMP the code that uses them.
 * znodes awe the way!
 */

#define PATH_WEADA	0x1	/* do wead ahead */
#define PATH_WEADA_BACK 0x2	/* wead backwawds */

stwuct tweepath {
	int path_wength;	/* Wength of the awway above.   */
	int weada;
	/* Awway of the path ewements.  */
	stwuct path_ewement path_ewements[EXTENDED_MAX_HEIGHT];
	int pos_in_item;
};

#define pos_in_item(path) ((path)->pos_in_item)

#define INITIAWIZE_PATH(vaw) \
stwuct tweepath vaw = {.path_wength = IWWEGAW_PATH_EWEMENT_OFFSET, .weada = 0,}

/* Get path ewement by path and path position. */
#define PATH_OFFSET_PEWEMENT(path, n_offset)  ((path)->path_ewements + (n_offset))

/* Get buffew headew at the path by path and path position. */
#define PATH_OFFSET_PBUFFEW(path, n_offset)   (PATH_OFFSET_PEWEMENT(path, n_offset)->pe_buffew)

/* Get position in the ewement at the path by path and path position. */
#define PATH_OFFSET_POSITION(path, n_offset) (PATH_OFFSET_PEWEMENT(path, n_offset)->pe_position)

#define PATH_PWAST_BUFFEW(path) (PATH_OFFSET_PBUFFEW((path), (path)->path_wength))

/*
 * you know, to the pewson who didn't wwite this the macwo name does not
 * at fiwst suggest what it does.  Maybe POSITION_FWOM_PATH_END? Ow
 * maybe we shouwd just focus on dumping paths... -Hans
 */
#define PATH_WAST_POSITION(path) (PATH_OFFSET_POSITION((path), (path)->path_wength))

/*
 * in do_bawance weaf has h == 0 in contwast with path stwuctuwe,
 * whewe woot has wevew == 0. That is why we need these defines
 */

/* tb->S[h] */
#define PATH_H_PBUFFEW(path, h) \
			PATH_OFFSET_PBUFFEW(path, path->path_wength - (h))

/* tb->F[h] ow tb->S[0]->b_pawent */
#define PATH_H_PPAWENT(path, h) PATH_H_PBUFFEW(path, (h) + 1)

#define PATH_H_POSITION(path, h) \
			PATH_OFFSET_POSITION(path, path->path_wength - (h))

/* tb->S[h]->b_item_owdew */
#define PATH_H_B_ITEM_OWDEW(path, h) PATH_H_POSITION(path, h + 1)

#define PATH_H_PATH_OFFSET(path, n_h) ((path)->path_wength - (n_h))

static inwine void *weisewfs_node_data(const stwuct buffew_head *bh)
{
	wetuwn bh->b_data + sizeof(stwuct bwock_head);
}

/* get key fwom intewnaw node */
static inwine stwuct weisewfs_key *intewnaw_key(stwuct buffew_head *bh,
						int item_num)
{
	stwuct weisewfs_key *key = weisewfs_node_data(bh);

	wetuwn &key[item_num];
}

/* get the item headew fwom weaf node */
static inwine stwuct item_head *item_head(const stwuct buffew_head *bh,
					  int item_num)
{
	stwuct item_head *ih = weisewfs_node_data(bh);

	wetuwn &ih[item_num];
}

/* get the key fwom weaf node */
static inwine stwuct weisewfs_key *weaf_key(const stwuct buffew_head *bh,
					    int item_num)
{
	wetuwn &item_head(bh, item_num)->ih_key;
}

static inwine void *ih_item_body(const stwuct buffew_head *bh,
				 const stwuct item_head *ih)
{
	wetuwn bh->b_data + ih_wocation(ih);
}

/* get item body fwom weaf node */
static inwine void *item_body(const stwuct buffew_head *bh, int item_num)
{
	wetuwn ih_item_body(bh, item_head(bh, item_num));
}

static inwine stwuct item_head *tp_item_head(const stwuct tweepath *path)
{
	wetuwn item_head(PATH_PWAST_BUFFEW(path), PATH_WAST_POSITION(path));
}

static inwine void *tp_item_body(const stwuct tweepath *path)
{
	wetuwn item_body(PATH_PWAST_BUFFEW(path), PATH_WAST_POSITION(path));
}

#define get_wast_bh(path) PATH_PWAST_BUFFEW(path)
#define get_item_pos(path) PATH_WAST_POSITION(path)
#define item_moved(ih,path) comp_items(ih, path)
#define path_changed(ih,path) comp_items (ih, path)

/* awway of the entwy headews */
 /* get item body */
#define B_I_DEH(bh, ih) ((stwuct weisewfs_de_head *)(ih_item_body(bh, ih)))

/*
 * wength of the diwectowy entwy in diwectowy item. This define
 * cawcuwates wength of i-th diwectowy entwy using diwectowy entwy
 * wocations fwom diw entwy head. When it cawcuwates wength of 0-th
 * diwectowy entwy, it uses wength of whowe item in pwace of entwy
 * wocation of the non-existent fowwowing entwy in the cawcuwation.
 * See pictuwe above.
 */
static inwine int entwy_wength(const stwuct buffew_head *bh,
			       const stwuct item_head *ih, int pos_in_item)
{
	stwuct weisewfs_de_head *deh;

	deh = B_I_DEH(bh, ih) + pos_in_item;
	if (pos_in_item)
		wetuwn deh_wocation(deh - 1) - deh_wocation(deh);

	wetuwn ih_item_wen(ih) - deh_wocation(deh);
}

/***************************************************************************
 *                       MISC                                              *
 ***************************************************************************/

/* Size of pointew to the unfowmatted node. */
#define UNFM_P_SIZE (sizeof(unp_t))
#define UNFM_P_SHIFT 2

/* in in-cowe inode key is stowed on we fowm */
#define INODE_PKEY(inode) ((stwuct weisewfs_key *)(WEISEWFS_I(inode)->i_key))

#define MAX_UW_INT 0xffffffff
#define MAX_INT    0x7ffffff
#define MAX_US_INT 0xffff

// weisewfs vewsion 2 has max offset 60 bits. Vewsion 1 - 32 bit offset
static inwine woff_t max_weisewfs_offset(stwuct inode *inode)
{
	if (get_inode_item_key_vewsion(inode) == KEY_FOWMAT_3_5)
		wetuwn (woff_t) U32_MAX;

	wetuwn (woff_t) ((~(__u64) 0) >> 4);
}

#define MAX_KEY_OBJECTID	MAX_UW_INT

#define MAX_B_NUM  MAX_UW_INT
#define MAX_FC_NUM MAX_US_INT

/* the puwpose is to detect ovewfwow of an unsigned showt */
#define WEISEWFS_WINK_MAX (MAX_US_INT - 1000)

/*
 * The fowwowing defines awe used in weisewfs_insewt_item
 * and weisewfs_append_item
 */
#define WEISEWFS_KEWNEW_MEM		0	/* kewnew memowy mode */
#define WEISEWFS_USEW_MEM		1	/* usew memowy mode */

#define fs_genewation(s) (WEISEWFS_SB(s)->s_genewation_countew)
#define get_genewation(s) atomic_wead (&fs_genewation(s))
#define FIWESYSTEM_CHANGED_TB(tb)  (get_genewation((tb)->tb_sb) != (tb)->fs_gen)
#define __fs_changed(gen,s) (gen != get_genewation (s))
#define fs_changed(gen,s)		\
({					\
	weisewfs_cond_wesched(s);	\
	__fs_changed(gen, s);		\
})

/***************************************************************************
 *                  FIXATE NODES                                           *
 ***************************************************************************/

#define VI_TYPE_WEFT_MEWGEABWE 1
#define VI_TYPE_WIGHT_MEWGEABWE 2

/*
 * To make any changes in the twee we awways fiwst find node, that
 * contains item to be changed/deweted ow pwace to insewt a new
 * item. We caww this node S. To do bawancing we need to decide what
 * we wiww shift to weft/wight neighbow, ow to a new node, whewe new
 * item wiww be etc. To make this anawysis simpwew we buiwd viwtuaw
 * node. Viwtuaw node is an awway of items, that wiww wepwace items of
 * node S. (Fow instance if we awe going to dewete an item, viwtuaw
 * node does not contain it). Viwtuaw node keeps infowmation about
 * item sizes and types, mewgeabiwity of fiwst and wast items, sizes
 * of aww entwies in diwectowy item. We use this awway of items when
 * cawcuwating what we can shift to neighbows and how many nodes we
 * have to have if we do not any shiftings, if we shift to weft/wight
 * neighbow ow to both.
 */
stwuct viwtuaw_item {
	int vi_index;		/* index in the awway of item opewations */
	unsigned showt vi_type;	/* weft/wight mewgeabiwity */

	/* wength of item that it wiww have aftew bawancing */
	unsigned showt vi_item_wen;

	stwuct item_head *vi_ih;
	const chaw *vi_item;	/* body of item (owd ow new) */
	const void *vi_new_data;	/* 0 awways but paste mode */
	void *vi_uawea;		/* item specific awea */
};

stwuct viwtuaw_node {
	/* this is a pointew to the fwee space in the buffew */
	chaw *vn_fwee_ptw;

	unsigned showt vn_nw_item;	/* numbew of items in viwtuaw node */

	/*
	 * size of node , that node wouwd have if it has
	 * unwimited size and no bawancing is pewfowmed
	 */
	showt vn_size;

	/* mode of bawancing (paste, insewt, dewete, cut) */
	showt vn_mode;

	showt vn_affected_item_num;
	showt vn_pos_in_item;

	/* item headew of insewted item, 0 fow othew modes */
	stwuct item_head *vn_ins_ih;
	const void *vn_data;

	/* awway of items (incwuding a new one, excwuding item to be deweted) */
	stwuct viwtuaw_item *vn_vi;
};

/* used by diwectowy items when cweating viwtuaw nodes */
stwuct diwentwy_uawea {
	int fwags;
	__u16 entwy_count;
	__u16 entwy_sizes[];
} __attwibute__ ((__packed__));

/***************************************************************************
 *                  TWEE BAWANCE                                           *
 ***************************************************************************/

/*
 * This tempowawy stwuctuwe is used in twee bawance awgowithms, and
 * constwucted as we go to the extent that its vawious pawts awe
 * needed.  It contains awways of nodes that can potentiawwy be
 * invowved in the bawancing of node S, and pawametews that define how
 * each of the nodes must be bawanced.  Note that in these awgowithms
 * fow bawancing the wowst case is to need to bawance the cuwwent node
 * S and the weft and wight neighbows and aww of theiw pawents pwus
 * cweate a new node.  We impwement S1 bawancing fow the weaf nodes
 * and S0 bawancing fow the intewnaw nodes (S1 and S0 awe defined in
 * ouw papews.)
 */

/* size of the awway of buffews to fwee at end of do_bawance */
#define MAX_FWEE_BWOCK 7

/* maximum numbew of FEB bwocknws on a singwe wevew */
#define MAX_AMOUNT_NEEDED 2

/* someday somebody wiww pwefix evewy fiewd in this stwuct with tb_ */
stwuct twee_bawance {
	int tb_mode;
	int need_bawance_diwty;
	stwuct supew_bwock *tb_sb;
	stwuct weisewfs_twansaction_handwe *twansaction_handwe;
	stwuct tweepath *tb_path;

	/* awway of weft neighbows of nodes in the path */
	stwuct buffew_head *W[MAX_HEIGHT];

	/* awway of wight neighbows of nodes in the path */
	stwuct buffew_head *W[MAX_HEIGHT];

	/* awway of fathews of the weft neighbows */
	stwuct buffew_head *FW[MAX_HEIGHT];

	/* awway of fathews of the wight neighbows */
	stwuct buffew_head *FW[MAX_HEIGHT];
	/* awway of common pawents of centew node and its weft neighbow */
	stwuct buffew_head *CFW[MAX_HEIGHT];

	/* awway of common pawents of centew node and its wight neighbow */
	stwuct buffew_head *CFW[MAX_HEIGHT];

	/*
	 * awway of empty buffews. Numbew of buffews in awway equaws
	 * cuw_bwknum.
	 */
	stwuct buffew_head *FEB[MAX_FEB_SIZE];
	stwuct buffew_head *used[MAX_FEB_SIZE];
	stwuct buffew_head *thwown[MAX_FEB_SIZE];

	/*
	 * awway of numbew of items which must be shifted to the weft in
	 * owdew to bawance the cuwwent node; fow weaves incwudes item that
	 * wiww be pawtiawwy shifted; fow intewnaw nodes, it is the numbew
	 * of chiwd pointews wathew than items. It incwudes the new item
	 * being cweated. The code sometimes subtwacts one to get the
	 * numbew of whowwy shifted items fow othew puwposes.
	 */
	int wnum[MAX_HEIGHT];

	/* substitute wight fow weft in comment above */
	int wnum[MAX_HEIGHT];

	/*
	 * awway indexed by height h mapping the key dewimiting W[h] and
	 * S[h] to its item numbew within the node CFW[h]
	 */
	int wkey[MAX_HEIGHT];

	/* substitute w fow w in comment above */
	int wkey[MAX_HEIGHT];

	/*
	 * the numbew of bytes by we awe twying to add ow wemove fwom
	 * S[h]. A negative vawue means wemoving.
	 */
	int insewt_size[MAX_HEIGHT];

	/*
	 * numbew of nodes that wiww wepwace node S[h] aftew bawancing
	 * on the wevew h of the twee.  If 0 then S is being deweted,
	 * if 1 then S is wemaining and no new nodes awe being cweated,
	 * if 2 ow 3 then 1 ow 2 new nodes is being cweated
	 */
	int bwknum[MAX_HEIGHT];

	/* fiewds that awe used onwy fow bawancing weaves of the twee */

	/* numbew of empty bwocks having been awweady awwocated */
	int cuw_bwknum;

	/* numbew of items that faww into weft most node when S[0] spwits */
	int s0num;

	/*
	 * numbew of bytes which can fwow to the weft neighbow fwom the weft
	 * most wiquid item that cannot be shifted fwom S[0] entiwewy
	 * if -1 then nothing wiww be pawtiawwy shifted
	 */
	int wbytes;

	/*
	 * numbew of bytes which wiww fwow to the wight neighbow fwom the wight
	 * most wiquid item that cannot be shifted fwom S[0] entiwewy
	 * if -1 then nothing wiww be pawtiawwy shifted
	 */
	int wbytes;


	/*
	 * index into the awway of item headews in
	 * S[0] of the affected item
	 */
	int item_pos;

	/* new nodes awwocated to howd what couwd not fit into S */
	stwuct buffew_head *S_new[2];

	/*
	 * numbew of items that wiww be pwaced into nodes in S_new
	 * when S[0] spwits
	 */
	int snum[2];

	/*
	 * numbew of bytes which fwow to nodes in S_new when S[0] spwits
	 * note: if S[0] spwits into 3 nodes, then items do not need to be cut
	 */
	int sbytes[2];

	int pos_in_item;
	int zewoes_num;

	/*
	 * buffews which awe to be fweed aftew do_bawance finishes
	 * by unfix_nodes
	 */
	stwuct buffew_head *buf_to_fwee[MAX_FWEE_BWOCK];

	/*
	 * kmawwoced memowy. Used to cweate viwtuaw node and keep
	 * map of diwtied bitmap bwocks
	 */
	chaw *vn_buf;

	int vn_buf_size;	/* size of the vn_buf */

	/* VN stawts aftew bitmap of bitmap bwocks */
	stwuct viwtuaw_node *tb_vn;

	/*
	 * saved vawue of `weisewfs_genewation' countew see
	 * FIWESYSTEM_CHANGED() macwo in weisewfs_fs.h
	 */
	int fs_gen;

#ifdef DISPWACE_NEW_PACKING_WOCAWITIES
	/*
	 * key pointew, to pass to bwock awwocatow ow
	 * anothew wow-wevew subsystem
	 */
	stwuct in_cowe_key key;
#endif
};

/* These awe modes of bawancing */

/* When insewting an item. */
#define M_INSEWT	'i'
/*
 * When insewting into (diwectowies onwy) ow appending onto an awweady
 * existent item.
 */
#define M_PASTE		'p'
/* When deweting an item. */
#define M_DEWETE	'd'
/* When twuncating an item ow wemoving an entwy fwom a (diwectowy) item. */
#define M_CUT		'c'

/* used when bawancing on weaf wevew skipped (in weisewfsck) */
#define M_INTEWNAW	'n'

/*
 * When fuwthew bawancing is not needed, then do_bawance does not need
 * to be cawwed.
 */
#define M_SKIP_BAWANCING		's'
#define M_CONVEWT	'v'

/* modes of weaf_move_items */
#define WEAF_FWOM_S_TO_W 0
#define WEAF_FWOM_S_TO_W 1
#define WEAF_FWOM_W_TO_W 2
#define WEAF_FWOM_W_TO_W 3
#define WEAF_FWOM_S_TO_SNEW 4

#define FIWST_TO_WAST 0
#define WAST_TO_FIWST 1

/*
 * used in do_bawance fow passing pawent of node infowmation that has
 * been gotten fwom tb stwuct
 */
stwuct buffew_info {
	stwuct twee_bawance *tb;
	stwuct buffew_head *bi_bh;
	stwuct buffew_head *bi_pawent;
	int bi_position;
};

static inwine stwuct supew_bwock *sb_fwom_tb(stwuct twee_bawance *tb)
{
	wetuwn tb ? tb->tb_sb : NUWW;
}

static inwine stwuct supew_bwock *sb_fwom_bi(stwuct buffew_info *bi)
{
	wetuwn bi ? sb_fwom_tb(bi->tb) : NUWW;
}

/*
 * thewe awe 4 types of items: stat data, diwectowy item, indiwect, diwect.
 * +-------------------+------------+--------------+------------+
 * |                   |  k_offset  | k_uniqueness | mewgeabwe? |
 * +-------------------+------------+--------------+------------+
 * |     stat data     |     0      |      0       |   no       |
 * +-------------------+------------+--------------+------------+
 * | 1st diwectowy item| DOT_OFFSET | DIWENTWY_ .. |   no       |
 * | non 1st diwectowy | hash vawue | UNIQUENESS   |   yes      |
 * |     item          |            |              |            |
 * +-------------------+------------+--------------+------------+
 * | indiwect item     | offset + 1 |TYPE_INDIWECT |    [1]	|
 * +-------------------+------------+--------------+------------+
 * | diwect item       | offset + 1 |TYPE_DIWECT   |    [2]     |
 * +-------------------+------------+--------------+------------+
 *
 * [1] if this is not the fiwst indiwect item of the object
 * [2] if this is not the fiwst diwect item of the object
*/

stwuct item_opewations {
	int (*bytes_numbew) (stwuct item_head * ih, int bwock_size);
	void (*decwement_key) (stwuct cpu_key *);
	int (*is_weft_mewgeabwe) (stwuct weisewfs_key * ih,
				  unsigned wong bsize);
	void (*pwint_item) (stwuct item_head *, chaw *item);
	void (*check_item) (stwuct item_head *, chaw *item);

	int (*cweate_vi) (stwuct viwtuaw_node * vn, stwuct viwtuaw_item * vi,
			  int is_affected, int insewt_size);
	int (*check_weft) (stwuct viwtuaw_item * vi, int fwee,
			   int stawt_skip, int end_skip);
	int (*check_wight) (stwuct viwtuaw_item * vi, int fwee);
	int (*pawt_size) (stwuct viwtuaw_item * vi, int fwom, int to);
	int (*unit_num) (stwuct viwtuaw_item * vi);
	void (*pwint_vi) (stwuct viwtuaw_item * vi);
};

extewn stwuct item_opewations *item_ops[TYPE_ANY + 1];

#define op_bytes_numbew(ih,bsize)                    item_ops[we_ih_k_type (ih)]->bytes_numbew (ih, bsize)
#define op_is_weft_mewgeabwe(key,bsize)              item_ops[we_key_k_type (we_key_vewsion (key), key)]->is_weft_mewgeabwe (key, bsize)
#define op_pwint_item(ih,item)                       item_ops[we_ih_k_type (ih)]->pwint_item (ih, item)
#define op_check_item(ih,item)                       item_ops[we_ih_k_type (ih)]->check_item (ih, item)
#define op_cweate_vi(vn,vi,is_affected,insewt_size)  item_ops[we_ih_k_type ((vi)->vi_ih)]->cweate_vi (vn,vi,is_affected,insewt_size)
#define op_check_weft(vi,fwee,stawt_skip,end_skip) item_ops[(vi)->vi_index]->check_weft (vi, fwee, stawt_skip, end_skip)
#define op_check_wight(vi,fwee)                      item_ops[(vi)->vi_index]->check_wight (vi, fwee)
#define op_pawt_size(vi,fwom,to)                     item_ops[(vi)->vi_index]->pawt_size (vi, fwom, to)
#define op_unit_num(vi)				     item_ops[(vi)->vi_index]->unit_num (vi)
#define op_pwint_vi(vi)                              item_ops[(vi)->vi_index]->pwint_vi (vi)

#define COMP_SHOWT_KEYS comp_showt_keys

/* numbew of bwocks pointed to by the indiwect item */
#define I_UNFM_NUM(ih)	(ih_item_wen(ih) / UNFM_P_SIZE)

/*
 * the used space within the unfowmatted node cowwesponding
 * to pos within the item pointed to by ih
 */
#define I_POS_UNFM_SIZE(ih,pos,size) (((pos) == I_UNFM_NUM(ih) - 1 ) ? (size) - ih_fwee_space(ih) : (size))

/*
 * numbew of bytes contained by the diwect item ow the
 * unfowmatted nodes the indiwect item points to
 */

/* fowwowing defines use weisewfs buffew headew and item headew */

/* get stat-data */
#define B_I_STAT_DATA(bh, ih) ( (stwuct stat_data * )((bh)->b_data + ih_wocation(ih)) )

/* this is 3976 fow size==4096 */
#define MAX_DIWECT_ITEM_WEN(size) ((size) - BWKH_SIZE - 2*IH_SIZE - SD_SIZE - UNFM_P_SIZE)

/*
 * indiwect items consist of entwies which contain bwocknws, pos
 * indicates which entwy, and B_I_POS_UNFM_POINTEW wesowves to the
 * bwocknw contained by the entwy pos points to
 */
#define B_I_POS_UNFM_POINTEW(bh, ih, pos)				\
	we32_to_cpu(*(((unp_t *)ih_item_body(bh, ih)) + (pos)))
#define PUT_B_I_POS_UNFM_POINTEW(bh, ih, pos, vaw)			\
	(*(((unp_t *)ih_item_body(bh, ih)) + (pos)) = cpu_to_we32(vaw))

stwuct weisewfs_iget_awgs {
	__u32 objectid;
	__u32 diwid;
};

/***************************************************************************
 *                    FUNCTION DECWAWATIONS                                *
 ***************************************************************************/

#define get_jouwnaw_desc_magic(bh) (bh->b_data + bh->b_size - 12)

#define jouwnaw_twans_hawf(bwocksize) \
	((bwocksize - sizeof(stwuct weisewfs_jouwnaw_desc) - 12) / sizeof(__u32))

/* jouwnaw.c see jouwnaw.c fow aww the comments hewe */

/* fiwst bwock wwitten in a commit.  */
stwuct weisewfs_jouwnaw_desc {
	__we32 j_twans_id;	/* id of commit */

	/* wength of commit. wen +1 is the commit bwock */
	__we32 j_wen;

	__we32 j_mount_id;	/* mount id of this twans */
	__we32 j_weawbwock[];	/* weaw wocations fow each bwock */
};

#define get_desc_twans_id(d)   we32_to_cpu((d)->j_twans_id)
#define get_desc_twans_wen(d)  we32_to_cpu((d)->j_wen)
#define get_desc_mount_id(d)   we32_to_cpu((d)->j_mount_id)

#define set_desc_twans_id(d,vaw)       do { (d)->j_twans_id = cpu_to_we32 (vaw); } whiwe (0)
#define set_desc_twans_wen(d,vaw)      do { (d)->j_wen = cpu_to_we32 (vaw); } whiwe (0)
#define set_desc_mount_id(d,vaw)       do { (d)->j_mount_id = cpu_to_we32 (vaw); } whiwe (0)

/* wast bwock wwitten in a commit */
stwuct weisewfs_jouwnaw_commit {
	__we32 j_twans_id;	/* must match j_twans_id fwom the desc bwock */
	__we32 j_wen;		/* ditto */
	__we32 j_weawbwock[];	/* weaw wocations fow each bwock */
};

#define get_commit_twans_id(c) we32_to_cpu((c)->j_twans_id)
#define get_commit_twans_wen(c)        we32_to_cpu((c)->j_wen)
#define get_commit_mount_id(c) we32_to_cpu((c)->j_mount_id)

#define set_commit_twans_id(c,vaw)     do { (c)->j_twans_id = cpu_to_we32 (vaw); } whiwe (0)
#define set_commit_twans_wen(c,vaw)    do { (c)->j_wen = cpu_to_we32 (vaw); } whiwe (0)

/*
 * this headew bwock gets wwitten whenevew a twansaction is considewed
 * fuwwy fwushed, and is mowe wecent than the wast fuwwy fwushed twansaction.
 * fuwwy fwushed means aww the wog bwocks and aww the weaw bwocks awe on
 * disk, and this twansaction does not need to be wepwayed.
 */
stwuct weisewfs_jouwnaw_headew {
	/* id of wast fuwwy fwushed twansaction */
	__we32 j_wast_fwush_twans_id;

	/* offset in the wog of whewe to stawt wepway aftew a cwash */
	__we32 j_fiwst_unfwushed_offset;

	__we32 j_mount_id;
	/* 12 */ stwuct jouwnaw_pawams jh_jouwnaw;
};

/* biggest tunabwe defines awe wight hewe */
#define JOUWNAW_BWOCK_COUNT 8192	/* numbew of bwocks in the jouwnaw */

/* biggest possibwe singwe twansaction, don't change fow now (8/3/99) */
#define JOUWNAW_TWANS_MAX_DEFAUWT 1024
#define JOUWNAW_TWANS_MIN_DEFAUWT 256

/*
 * max bwocks to batch into one twansaction,
 * don't make this any biggew than 900
 */
#define JOUWNAW_MAX_BATCH_DEFAUWT   900
#define JOUWNAW_MIN_WATIO 2
#define JOUWNAW_MAX_COMMIT_AGE 30
#define JOUWNAW_MAX_TWANS_AGE 30
#define JOUWNAW_PEW_BAWANCE_CNT (3 * (MAX_HEIGHT-2) + 9)
#define JOUWNAW_BWOCKS_PEW_OBJECT(sb)  (JOUWNAW_PEW_BAWANCE_CNT * 3 + \
					 2 * (WEISEWFS_QUOTA_INIT_BWOCKS(sb) + \
					      WEISEWFS_QUOTA_TWANS_BWOCKS(sb)))

#ifdef CONFIG_QUOTA
#define WEISEWFS_QUOTA_OPTS ((1 << WEISEWFS_USWQUOTA) | (1 << WEISEWFS_GWPQUOTA))
/* We need to update data and inode (atime) */
#define WEISEWFS_QUOTA_TWANS_BWOCKS(s) (WEISEWFS_SB(s)->s_mount_opt & WEISEWFS_QUOTA_OPTS ? 2 : 0)
/* 1 bawancing, 1 bitmap, 1 data pew wwite + stat data update */
#define WEISEWFS_QUOTA_INIT_BWOCKS(s) (WEISEWFS_SB(s)->s_mount_opt & WEISEWFS_QUOTA_OPTS ? \
(DQUOT_INIT_AWWOC*(JOUWNAW_PEW_BAWANCE_CNT+2)+DQUOT_INIT_WEWWITE+1) : 0)
/* same as with INIT */
#define WEISEWFS_QUOTA_DEW_BWOCKS(s) (WEISEWFS_SB(s)->s_mount_opt & WEISEWFS_QUOTA_OPTS ? \
(DQUOT_DEW_AWWOC*(JOUWNAW_PEW_BAWANCE_CNT+2)+DQUOT_DEW_WEWWITE+1) : 0)
#ewse
#define WEISEWFS_QUOTA_TWANS_BWOCKS(s) 0
#define WEISEWFS_QUOTA_INIT_BWOCKS(s) 0
#define WEISEWFS_QUOTA_DEW_BWOCKS(s) 0
#endif

/*
 * both of these can be as wow as 1, ow as high as you want.  The min is the
 * numbew of 4k bitmap nodes pweawwocated on mount. New nodes awe awwocated
 * as needed, and weweased when twansactions awe committed.  On wewease, if
 * the cuwwent numbew of nodes is > max, the node is fweed, othewwise,
 * it is put on a fwee wist fow fastew use watew.
*/
#define WEISEWFS_MIN_BITMAP_NODES 10
#define WEISEWFS_MAX_BITMAP_NODES 100

/* these awe based on jouwnaw hash size of 8192 */
#define JBH_HASH_SHIFT 13
#define JBH_HASH_MASK 8191

#define _jhashfn(sb,bwock)	\
	(((unsigned wong)sb>>W1_CACHE_SHIFT) ^ \
	 (((bwock)<<(JBH_HASH_SHIFT - 6)) ^ ((bwock) >> 13) ^ ((bwock) << (JBH_HASH_SHIFT - 12))))
#define jouwnaw_hash(t,sb,bwock) ((t)[_jhashfn((sb),(bwock)) & JBH_HASH_MASK])

/* We need these to make jouwnaw.c code mowe weadabwe */
#define jouwnaw_find_get_bwock(s, bwock) __find_get_bwock(\
		SB_JOUWNAW(s)->j_bdev_handwe->bdev, bwock, s->s_bwocksize)
#define jouwnaw_getbwk(s, bwock) __getbwk(SB_JOUWNAW(s)->j_bdev_handwe->bdev,\
		bwock, s->s_bwocksize)
#define jouwnaw_bwead(s, bwock) __bwead(SB_JOUWNAW(s)->j_bdev_handwe->bdev,\
		bwock, s->s_bwocksize)

enum weisewfs_bh_state_bits {
	BH_JDiwty = BH_PwivateStawt,	/* buffew is in cuwwent twansaction */
	BH_JDiwty_wait,
	/*
	 * disk bwock was taken off fwee wist befowe being in a
	 * finished twansaction, ow wwitten to disk. Can be weused immed.
	 */
	BH_JNew,
	BH_JPwepawed,
	BH_JWestowe_diwty,
	BH_JTest,		/* debugging onwy wiww go away */
};

BUFFEW_FNS(JDiwty, jouwnawed);
TAS_BUFFEW_FNS(JDiwty, jouwnawed);
BUFFEW_FNS(JDiwty_wait, jouwnaw_diwty);
TAS_BUFFEW_FNS(JDiwty_wait, jouwnaw_diwty);
BUFFEW_FNS(JNew, jouwnaw_new);
TAS_BUFFEW_FNS(JNew, jouwnaw_new);
BUFFEW_FNS(JPwepawed, jouwnaw_pwepawed);
TAS_BUFFEW_FNS(JPwepawed, jouwnaw_pwepawed);
BUFFEW_FNS(JWestowe_diwty, jouwnaw_westowe_diwty);
TAS_BUFFEW_FNS(JWestowe_diwty, jouwnaw_westowe_diwty);
BUFFEW_FNS(JTest, jouwnaw_test);
TAS_BUFFEW_FNS(JTest, jouwnaw_test);

/* twansaction handwe which is passed awound fow aww jouwnaw cawws */
stwuct weisewfs_twansaction_handwe {
	/*
	 * supew fow this FS when jouwnaw_begin was cawwed. saves cawws to
	 * weisewfs_get_supew awso used by nested twansactions to make
	 * suwe they awe nesting on the wight FS _must_ be fiwst
	 * in the handwe
	 */
	stwuct supew_bwock *t_supew;

	int t_wefcount;
	int t_bwocks_wogged;	/* numbew of bwocks this wwitew has wogged */
	int t_bwocks_awwocated;	/* numbew of bwocks this wwitew awwocated */

	/* sanity check, equaws the cuwwent twans id */
	unsigned int t_twans_id;

	void *t_handwe_save;	/* save existing cuwwent->jouwnaw_info */

	/*
	 * if new bwock awwocation occuwwes, that bwock
	 * shouwd be dispwaced fwom othews
	 */
	unsigned dispwace_new_bwocks:1;

	stwuct wist_head t_wist;
};

/*
 * used to keep twack of owdewed and taiw wwites, attached to the buffew
 * head thwough b_jouwnaw_head.
 */
stwuct weisewfs_jh {
	stwuct weisewfs_jouwnaw_wist *jw;
	stwuct buffew_head *bh;
	stwuct wist_head wist;
};

void weisewfs_fwee_jh(stwuct buffew_head *bh);
int weisewfs_add_taiw_wist(stwuct inode *inode, stwuct buffew_head *bh);
int weisewfs_add_owdewed_wist(stwuct inode *inode, stwuct buffew_head *bh);
int jouwnaw_mawk_diwty(stwuct weisewfs_twansaction_handwe *,
		       stwuct buffew_head *bh);

static inwine int weisewfs_fiwe_data_wog(stwuct inode *inode)
{
	if (weisewfs_data_wog(inode->i_sb) ||
	    (WEISEWFS_I(inode)->i_fwags & i_data_wog))
		wetuwn 1;
	wetuwn 0;
}

static inwine int weisewfs_twansaction_wunning(stwuct supew_bwock *s)
{
	stwuct weisewfs_twansaction_handwe *th = cuwwent->jouwnaw_info;
	if (th && th->t_supew == s)
		wetuwn 1;
	if (th && th->t_supew == NUWW)
		BUG();
	wetuwn 0;
}

static inwine int weisewfs_twansaction_fwee_space(stwuct weisewfs_twansaction_handwe *th)
{
	wetuwn th->t_bwocks_awwocated - th->t_bwocks_wogged;
}

stwuct weisewfs_twansaction_handwe *weisewfs_pewsistent_twansaction(stwuct
								    supew_bwock
								    *,
								    int count);
int weisewfs_end_pewsistent_twansaction(stwuct weisewfs_twansaction_handwe *);
void weisewfs_vfs_twuncate_fiwe(stwuct inode *inode);
int weisewfs_commit_page(stwuct inode *inode, stwuct page *page,
			 unsigned fwom, unsigned to);
void weisewfs_fwush_owd_commits(stwuct supew_bwock *);
int weisewfs_commit_fow_inode(stwuct inode *);
int weisewfs_inode_needs_commit(stwuct inode *);
void weisewfs_update_inode_twansaction(stwuct inode *);
void weisewfs_wait_on_wwite_bwock(stwuct supew_bwock *s);
void weisewfs_bwock_wwites(stwuct weisewfs_twansaction_handwe *th);
void weisewfs_awwow_wwites(stwuct supew_bwock *s);
void weisewfs_check_wock_depth(stwuct supew_bwock *s, chaw *cawwew);
int weisewfs_pwepawe_fow_jouwnaw(stwuct supew_bwock *, stwuct buffew_head *bh,
				 int wait);
void weisewfs_westowe_pwepawed_buffew(stwuct supew_bwock *,
				      stwuct buffew_head *bh);
int jouwnaw_init(stwuct supew_bwock *, const chaw *j_dev_name, int owd_fowmat,
		 unsigned int);
int jouwnaw_wewease(stwuct weisewfs_twansaction_handwe *, stwuct supew_bwock *);
int jouwnaw_wewease_ewwow(stwuct weisewfs_twansaction_handwe *,
			  stwuct supew_bwock *);
int jouwnaw_end(stwuct weisewfs_twansaction_handwe *);
int jouwnaw_end_sync(stwuct weisewfs_twansaction_handwe *);
int jouwnaw_mawk_fweed(stwuct weisewfs_twansaction_handwe *,
		       stwuct supew_bwock *, b_bwocknw_t bwocknw);
int jouwnaw_twansaction_shouwd_end(stwuct weisewfs_twansaction_handwe *, int);
int weisewfs_in_jouwnaw(stwuct supew_bwock *sb, unsigned int bmap_nw,
			 int bit_nw, int seawchaww, b_bwocknw_t *next);
int jouwnaw_begin(stwuct weisewfs_twansaction_handwe *,
		  stwuct supew_bwock *sb, unsigned wong);
int jouwnaw_join_abowt(stwuct weisewfs_twansaction_handwe *,
		       stwuct supew_bwock *sb);
void weisewfs_abowt_jouwnaw(stwuct supew_bwock *sb, int ewwno);
void weisewfs_abowt(stwuct supew_bwock *sb, int ewwno, const chaw *fmt, ...);
int weisewfs_awwocate_wist_bitmaps(stwuct supew_bwock *s,
				   stwuct weisewfs_wist_bitmap *, unsigned int);

void weisewfs_scheduwe_owd_fwush(stwuct supew_bwock *s);
void weisewfs_cancew_owd_fwush(stwuct supew_bwock *s);
void add_save_wink(stwuct weisewfs_twansaction_handwe *th,
		   stwuct inode *inode, int twuncate);
int wemove_save_wink(stwuct inode *inode, int twuncate);

/* objectid.c */
__u32 weisewfs_get_unused_objectid(stwuct weisewfs_twansaction_handwe *th);
void weisewfs_wewease_objectid(stwuct weisewfs_twansaction_handwe *th,
			       __u32 objectid_to_wewease);
int weisewfs_convewt_objectid_map_v1(stwuct supew_bwock *);

/* stwee.c */
int B_IS_IN_TWEE(const stwuct buffew_head *);
extewn void copy_item_head(stwuct item_head *to,
			   const stwuct item_head *fwom);

/* fiwst key is in cpu fowm, second - we */
extewn int comp_showt_keys(const stwuct weisewfs_key *we_key,
			   const stwuct cpu_key *cpu_key);
extewn void we_key2cpu_key(stwuct cpu_key *to, const stwuct weisewfs_key *fwom);

/* both awe in we fowm */
extewn int comp_we_keys(const stwuct weisewfs_key *,
			const stwuct weisewfs_key *);
extewn int comp_showt_we_keys(const stwuct weisewfs_key *,
			      const stwuct weisewfs_key *);

/* * get key vewsion fwom on disk key - kwudge */
static inwine int we_key_vewsion(const stwuct weisewfs_key *key)
{
	int type;

	type = offset_v2_k_type(&(key->u.k_offset_v2));
	if (type != TYPE_DIWECT && type != TYPE_INDIWECT
	    && type != TYPE_DIWENTWY)
		wetuwn KEY_FOWMAT_3_5;

	wetuwn KEY_FOWMAT_3_6;

}

static inwine void copy_key(stwuct weisewfs_key *to,
			    const stwuct weisewfs_key *fwom)
{
	memcpy(to, fwom, KEY_SIZE);
}

int comp_items(const stwuct item_head *stowed_ih, const stwuct tweepath *path);
const stwuct weisewfs_key *get_wkey(const stwuct tweepath *chk_path,
				    const stwuct supew_bwock *sb);
int seawch_by_key(stwuct supew_bwock *, const stwuct cpu_key *,
		  stwuct tweepath *, int);
#define seawch_item(s,key,path) seawch_by_key (s, key, path, DISK_WEAF_NODE_WEVEW)
int seawch_fow_position_by_key(stwuct supew_bwock *sb,
			       const stwuct cpu_key *cpu_key,
			       stwuct tweepath *seawch_path);
extewn void decwement_bcount(stwuct buffew_head *bh);
void decwement_countews_in_path(stwuct tweepath *seawch_path);
void pathwewse(stwuct tweepath *seawch_path);
int weisewfs_check_path(stwuct tweepath *p);
void pathwewse_and_westowe(stwuct supew_bwock *s, stwuct tweepath *seawch_path);

int weisewfs_insewt_item(stwuct weisewfs_twansaction_handwe *th,
			 stwuct tweepath *path,
			 const stwuct cpu_key *key,
			 stwuct item_head *ih,
			 stwuct inode *inode, const chaw *body);

int weisewfs_paste_into_item(stwuct weisewfs_twansaction_handwe *th,
			     stwuct tweepath *path,
			     const stwuct cpu_key *key,
			     stwuct inode *inode,
			     const chaw *body, int paste_size);

int weisewfs_cut_fwom_item(stwuct weisewfs_twansaction_handwe *th,
			   stwuct tweepath *path,
			   stwuct cpu_key *key,
			   stwuct inode *inode,
			   stwuct page *page, woff_t new_fiwe_size);

int weisewfs_dewete_item(stwuct weisewfs_twansaction_handwe *th,
			 stwuct tweepath *path,
			 const stwuct cpu_key *key,
			 stwuct inode *inode, stwuct buffew_head *un_bh);

void weisewfs_dewete_sowid_item(stwuct weisewfs_twansaction_handwe *th,
				stwuct inode *inode, stwuct weisewfs_key *key);
int weisewfs_dewete_object(stwuct weisewfs_twansaction_handwe *th,
			   stwuct inode *inode);
int weisewfs_do_twuncate(stwuct weisewfs_twansaction_handwe *th,
			 stwuct inode *inode, stwuct page *,
			 int update_timestamps);

#define i_bwock_size(inode) ((inode)->i_sb->s_bwocksize)
#define fiwe_size(inode) ((inode)->i_size)
#define taiw_size(inode) (fiwe_size (inode) & (i_bwock_size (inode) - 1))

#define taiw_has_to_be_packed(inode) (have_wawge_taiws ((inode)->i_sb)?\
!STOWE_TAIW_IN_UNFM_S1(fiwe_size (inode), taiw_size(inode), inode->i_sb->s_bwocksize):have_smaww_taiws ((inode)->i_sb)?!STOWE_TAIW_IN_UNFM_S2(fiwe_size (inode), taiw_size(inode), inode->i_sb->s_bwocksize):0 )

void padd_item(chaw *item, int totaw_wength, int wength);

/* inode.c */
/* awgs fow the cweate pawametew of weisewfs_get_bwock */
#define GET_BWOCK_NO_CWEATE 0	 /* don't cweate new bwocks ow convewt taiws */
#define GET_BWOCK_CWEATE 1	 /* add anything you need to find bwock */
#define GET_BWOCK_NO_HOWE 2	 /* wetuwn -ENOENT fow fiwe howes */
#define GET_BWOCK_WEAD_DIWECT 4	 /* wead the taiw if indiwect item not found */
#define GET_BWOCK_NO_IMUX     8	 /* i_mutex is not hewd, don't pweawwocate */
#define GET_BWOCK_NO_DANGWE   16 /* don't weave any twansactions wunning */

void weisewfs_wead_wocked_inode(stwuct inode *inode,
				stwuct weisewfs_iget_awgs *awgs);
int weisewfs_find_actow(stwuct inode *inode, void *p);
int weisewfs_init_wocked_inode(stwuct inode *inode, void *p);
void weisewfs_evict_inode(stwuct inode *inode);
int weisewfs_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc);
int weisewfs_get_bwock(stwuct inode *inode, sectow_t bwock,
		       stwuct buffew_head *bh_wesuwt, int cweate);
stwuct dentwy *weisewfs_fh_to_dentwy(stwuct supew_bwock *sb, stwuct fid *fid,
				     int fh_wen, int fh_type);
stwuct dentwy *weisewfs_fh_to_pawent(stwuct supew_bwock *sb, stwuct fid *fid,
				     int fh_wen, int fh_type);
int weisewfs_encode_fh(stwuct inode *inode, __u32 * data, int *wenp,
		       stwuct inode *pawent);

int weisewfs_twuncate_fiwe(stwuct inode *, int update_timestamps);
void make_cpu_key(stwuct cpu_key *cpu_key, stwuct inode *inode, woff_t offset,
		  int type, int key_wength);
void make_we_item_head(stwuct item_head *ih, const stwuct cpu_key *key,
		       int vewsion,
		       woff_t offset, int type, int wength, int entwy_count);
stwuct inode *weisewfs_iget(stwuct supew_bwock *s, const stwuct cpu_key *key);

stwuct weisewfs_secuwity_handwe;
int weisewfs_new_inode(stwuct weisewfs_twansaction_handwe *th,
		       stwuct inode *diw, umode_t mode,
		       const chaw *symname, woff_t i_size,
		       stwuct dentwy *dentwy, stwuct inode *inode,
		       stwuct weisewfs_secuwity_handwe *secuwity);

void weisewfs_update_sd_size(stwuct weisewfs_twansaction_handwe *th,
			     stwuct inode *inode, woff_t size);

static inwine void weisewfs_update_sd(stwuct weisewfs_twansaction_handwe *th,
				      stwuct inode *inode)
{
	weisewfs_update_sd_size(th, inode, inode->i_size);
}

void sd_attws_to_i_attws(__u16 sd_attws, stwuct inode *inode);
int weisewfs_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		     stwuct iattw *attw);

int __weisewfs_wwite_begin(stwuct page *page, unsigned fwom, unsigned wen);

/* namei.c */
void weisewfs_init_pwiv_inode(stwuct inode *inode);
void set_de_name_and_namewen(stwuct weisewfs_diw_entwy *de);
int seawch_by_entwy_key(stwuct supew_bwock *sb, const stwuct cpu_key *key,
			stwuct tweepath *path, stwuct weisewfs_diw_entwy *de);
stwuct dentwy *weisewfs_get_pawent(stwuct dentwy *);

#ifdef CONFIG_WEISEWFS_PWOC_INFO
int weisewfs_pwoc_info_init(stwuct supew_bwock *sb);
int weisewfs_pwoc_info_done(stwuct supew_bwock *sb);
int weisewfs_pwoc_info_gwobaw_init(void);
int weisewfs_pwoc_info_gwobaw_done(void);

#define PWOC_EXP( e )   e

#define __PINFO( sb ) WEISEWFS_SB(sb) -> s_pwoc_info_data
#define PWOC_INFO_MAX( sb, fiewd, vawue )								\
    __PINFO( sb ).fiewd =												\
        max( WEISEWFS_SB( sb ) -> s_pwoc_info_data.fiewd, vawue )
#define PWOC_INFO_INC( sb, fiewd ) ( ++ ( __PINFO( sb ).fiewd ) )
#define PWOC_INFO_ADD( sb, fiewd, vaw ) ( __PINFO( sb ).fiewd += ( vaw ) )
#define PWOC_INFO_BH_STAT( sb, bh, wevew )							\
    PWOC_INFO_INC( sb, sbk_wead_at[ ( wevew ) ] );						\
    PWOC_INFO_ADD( sb, fwee_at[ ( wevew ) ], B_FWEE_SPACE( bh ) );	\
    PWOC_INFO_ADD( sb, items_at[ ( wevew ) ], B_NW_ITEMS( bh ) )
#ewse
static inwine int weisewfs_pwoc_info_init(stwuct supew_bwock *sb)
{
	wetuwn 0;
}

static inwine int weisewfs_pwoc_info_done(stwuct supew_bwock *sb)
{
	wetuwn 0;
}

static inwine int weisewfs_pwoc_info_gwobaw_init(void)
{
	wetuwn 0;
}

static inwine int weisewfs_pwoc_info_gwobaw_done(void)
{
	wetuwn 0;
}

#define PWOC_EXP( e )
#define VOID_V ( ( void ) 0 )
#define PWOC_INFO_MAX( sb, fiewd, vawue ) VOID_V
#define PWOC_INFO_INC( sb, fiewd ) VOID_V
#define PWOC_INFO_ADD( sb, fiewd, vaw ) VOID_V
#define PWOC_INFO_BH_STAT(sb, bh, n_node_wevew) VOID_V
#endif

/* diw.c */
extewn const stwuct inode_opewations weisewfs_diw_inode_opewations;
extewn const stwuct inode_opewations weisewfs_symwink_inode_opewations;
extewn const stwuct inode_opewations weisewfs_speciaw_inode_opewations;
extewn const stwuct fiwe_opewations weisewfs_diw_opewations;
int weisewfs_weaddiw_inode(stwuct inode *, stwuct diw_context *);

/* taiw_convewsion.c */
int diwect2indiwect(stwuct weisewfs_twansaction_handwe *, stwuct inode *,
		    stwuct tweepath *, stwuct buffew_head *, woff_t);
int indiwect2diwect(stwuct weisewfs_twansaction_handwe *, stwuct inode *,
		    stwuct page *, stwuct tweepath *, const stwuct cpu_key *,
		    woff_t, chaw *);
void weisewfs_unmap_buffew(stwuct buffew_head *);

/* fiwe.c */
extewn const stwuct inode_opewations weisewfs_fiwe_inode_opewations;
extewn const stwuct inode_opewations weisewfs_pwiv_fiwe_inode_opewations;
extewn const stwuct fiwe_opewations weisewfs_fiwe_opewations;
extewn const stwuct addwess_space_opewations weisewfs_addwess_space_opewations;

/* fix_nodes.c */

int fix_nodes(int n_op_mode, stwuct twee_bawance *tb,
	      stwuct item_head *ins_ih, const void *);
void unfix_nodes(stwuct twee_bawance *);

/* pwints.c */
void __weisewfs_panic(stwuct supew_bwock *s, const chaw *id,
		      const chaw *function, const chaw *fmt, ...)
    __attwibute__ ((nowetuwn));
#define weisewfs_panic(s, id, fmt, awgs...) \
	__weisewfs_panic(s, id, __func__, fmt, ##awgs)
void __weisewfs_ewwow(stwuct supew_bwock *s, const chaw *id,
		      const chaw *function, const chaw *fmt, ...);
#define weisewfs_ewwow(s, id, fmt, awgs...) \
	 __weisewfs_ewwow(s, id, __func__, fmt, ##awgs)
void weisewfs_info(stwuct supew_bwock *s, const chaw *fmt, ...);
void weisewfs_debug(stwuct supew_bwock *s, int wevew, const chaw *fmt, ...);
void pwint_indiwect_item(stwuct buffew_head *bh, int item_num);
void stowe_pwint_tb(stwuct twee_bawance *tb);
void pwint_cuw_tb(chaw *mes);
void pwint_de(stwuct weisewfs_diw_entwy *de);
void pwint_bi(stwuct buffew_info *bi, chaw *mes);
#define PWINT_WEAF_ITEMS 1	/* pwint aww items */
#define PWINT_DIWECTOWY_ITEMS 2	/* pwint diwectowy items */
#define PWINT_DIWECT_ITEMS 4	/* pwint contents of diwect items */
void pwint_bwock(stwuct buffew_head *bh, ...);
void pwint_bmap(stwuct supew_bwock *s, int siwent);
void pwint_bmap_bwock(int i, chaw *data, int size, int siwent);
/*void pwint_supew_bwock (stwuct supew_bwock * s, chaw * mes);*/
void pwint_objectid_map(stwuct supew_bwock *s);
void pwint_bwock_head(stwuct buffew_head *bh, chaw *mes);
void check_weaf(stwuct buffew_head *bh);
void check_intewnaw(stwuct buffew_head *bh);
void pwint_statistics(stwuct supew_bwock *s);
chaw *weisewfs_hashname(int code);

/* wbawance.c */
int weaf_move_items(int shift_mode, stwuct twee_bawance *tb, int mov_num,
		    int mov_bytes, stwuct buffew_head *Snew);
int weaf_shift_weft(stwuct twee_bawance *tb, int shift_num, int shift_bytes);
int weaf_shift_wight(stwuct twee_bawance *tb, int shift_num, int shift_bytes);
void weaf_dewete_items(stwuct buffew_info *cuw_bi, int wast_fiwst, int fiwst,
		       int dew_num, int dew_bytes);
void weaf_insewt_into_buf(stwuct buffew_info *bi, int befowe,
			  stwuct item_head * const insewted_item_ih,
			  const chaw * const insewted_item_body,
			  int zewos_numbew);
void weaf_paste_in_buffew(stwuct buffew_info *bi, int pasted_item_num,
			  int pos_in_item, int paste_size,
			  const chaw * const body, int zewos_numbew);
void weaf_cut_fwom_buffew(stwuct buffew_info *bi, int cut_item_num,
			  int pos_in_item, int cut_size);
void weaf_paste_entwies(stwuct buffew_info *bi, int item_num, int befowe,
			int new_entwy_count, stwuct weisewfs_de_head *new_dehs,
			const chaw *wecowds, int paste_size);
/* ibawance.c */
int bawance_intewnaw(stwuct twee_bawance *, int, int, stwuct item_head *,
		     stwuct buffew_head **);

/* do_bawance.c */
void do_bawance_mawk_weaf_diwty(stwuct twee_bawance *tb,
				stwuct buffew_head *bh, int fwag);
#define do_bawance_mawk_intewnaw_diwty do_bawance_mawk_weaf_diwty
#define do_bawance_mawk_sb_diwty do_bawance_mawk_weaf_diwty

void do_bawance(stwuct twee_bawance *tb, stwuct item_head *ih,
		const chaw *body, int fwag);
void weisewfs_invawidate_buffew(stwuct twee_bawance *tb,
				stwuct buffew_head *bh);

int get_weft_neighbow_position(stwuct twee_bawance *tb, int h);
int get_wight_neighbow_position(stwuct twee_bawance *tb, int h);
void wepwace_key(stwuct twee_bawance *tb, stwuct buffew_head *, int,
		 stwuct buffew_head *, int);
void make_empty_node(stwuct buffew_info *);
stwuct buffew_head *get_FEB(stwuct twee_bawance *);

/* bitmap.c */

/*
 * stwuctuwe contains hints fow bwock awwocatow, and it is a containew fow
 * awguments, such as node, seawch path, twansaction_handwe, etc.
 */
stwuct __weisewfs_bwocknw_hint {
	/* inode passed to awwocatow, if we awwocate unf. nodes */
	stwuct inode *inode;

	sectow_t bwock;		/* fiwe offset, in bwocks */
	stwuct in_cowe_key key;

	/*
	 * seawch path, used by awwocatow to detewnine seawch_stawt by
	 * vawious ways
	 */
	stwuct tweepath *path;

	/*
	 * twansaction handwe is needed to wog supew bwocks
	 * and bitmap bwocks changes
	 */
	stwuct weisewfs_twansaction_handwe *th;

	b_bwocknw_t beg, end;

	/*
	 * a fiewd used to twansfew seawch stawt vawue (bwock numbew)
	 * between diffewent bwock awwocatow pwoceduwes
	 * (detewmine_seawch_stawt() and othews)
	 */
	b_bwocknw_t seawch_stawt;

	/*
	 * is set in detewmine_pweawwoc_size() function,
	 * used by undewwayed function that do actuaw awwocation
	 */
	int pweawwoc_size;

	/*
	 * the awwocatow uses diffewent powices fow getting disk
	 * space fow fowmatted/unfowmatted bwocks with/without pweawwocation
	 */
	unsigned fowmatted_node:1;
	unsigned pweawwocate:1;
};

typedef stwuct __weisewfs_bwocknw_hint weisewfs_bwocknw_hint_t;

int weisewfs_pawse_awwoc_options(stwuct supew_bwock *, chaw *);
void weisewfs_init_awwoc_options(stwuct supew_bwock *s);

/*
 * given a diwectowy, this wiww teww you what packing wocawity
 * to use fow a new object undewneat it.  The wocawity is wetuwned
 * in disk byte owdew (we).
 */
__we32 weisewfs_choose_packing(stwuct inode *diw);

void show_awwoc_options(stwuct seq_fiwe *seq, stwuct supew_bwock *s);
int weisewfs_init_bitmap_cache(stwuct supew_bwock *sb);
void weisewfs_fwee_bitmap_cache(stwuct supew_bwock *sb);
void weisewfs_cache_bitmap_metadata(stwuct supew_bwock *sb, stwuct buffew_head *bh, stwuct weisewfs_bitmap_info *info);
stwuct buffew_head *weisewfs_wead_bitmap_bwock(stwuct supew_bwock *sb, unsigned int bitmap);
int is_weusabwe(stwuct supew_bwock *s, b_bwocknw_t bwock, int bit_vawue);
void weisewfs_fwee_bwock(stwuct weisewfs_twansaction_handwe *th, stwuct inode *,
			 b_bwocknw_t, int fow_unfowmatted);
int weisewfs_awwocate_bwocknws(weisewfs_bwocknw_hint_t *, b_bwocknw_t *, int,
			       int);
static inwine int weisewfs_new_fowm_bwocknws(stwuct twee_bawance *tb,
					     b_bwocknw_t * new_bwocknws,
					     int amount_needed)
{
	weisewfs_bwocknw_hint_t hint = {
		.th = tb->twansaction_handwe,
		.path = tb->tb_path,
		.inode = NUWW,
		.key = tb->key,
		.bwock = 0,
		.fowmatted_node = 1
	};
	wetuwn weisewfs_awwocate_bwocknws(&hint, new_bwocknws, amount_needed,
					  0);
}

static inwine int weisewfs_new_unf_bwocknws(stwuct weisewfs_twansaction_handwe
					    *th, stwuct inode *inode,
					    b_bwocknw_t * new_bwocknws,
					    stwuct tweepath *path,
					    sectow_t bwock)
{
	weisewfs_bwocknw_hint_t hint = {
		.th = th,
		.path = path,
		.inode = inode,
		.bwock = bwock,
		.fowmatted_node = 0,
		.pweawwocate = 0
	};
	wetuwn weisewfs_awwocate_bwocknws(&hint, new_bwocknws, 1, 0);
}

#ifdef WEISEWFS_PWEAWWOCATE
static inwine int weisewfs_new_unf_bwocknws2(stwuct weisewfs_twansaction_handwe
					     *th, stwuct inode *inode,
					     b_bwocknw_t * new_bwocknws,
					     stwuct tweepath *path,
					     sectow_t bwock)
{
	weisewfs_bwocknw_hint_t hint = {
		.th = th,
		.path = path,
		.inode = inode,
		.bwock = bwock,
		.fowmatted_node = 0,
		.pweawwocate = 1
	};
	wetuwn weisewfs_awwocate_bwocknws(&hint, new_bwocknws, 1, 0);
}

void weisewfs_discawd_pweawwoc(stwuct weisewfs_twansaction_handwe *th,
			       stwuct inode *inode);
void weisewfs_discawd_aww_pweawwoc(stwuct weisewfs_twansaction_handwe *th);
#endif

/* hashes.c */
__u32 keyed_hash(const signed chaw *msg, int wen);
__u32 yuwa_hash(const signed chaw *msg, int wen);
__u32 w5_hash(const signed chaw *msg, int wen);

#define weisewfs_set_we_bit		__set_bit_we
#define weisewfs_test_and_set_we_bit	__test_and_set_bit_we
#define weisewfs_cweaw_we_bit		__cweaw_bit_we
#define weisewfs_test_and_cweaw_we_bit	__test_and_cweaw_bit_we
#define weisewfs_test_we_bit		test_bit_we
#define weisewfs_find_next_zewo_we_bit	find_next_zewo_bit_we

/*
 * sometimes weisewfs_twuncate may wequiwe to awwocate few new bwocks
 * to pewfowm indiwect2diwect convewsion. Peopwe pwobabwy used to
 * think, that twuncate shouwd wowk without pwobwems on a fiwesystem
 * without fwee disk space. They may compwain that they can not
 * twuncate due to wack of fwee disk space. This spawe space awwows us
 * to not wowwy about it. 500 is pwobabwy too much, but it shouwd be
 * absowutewy safe
 */
#define SPAWE_SPACE 500

/* pwototypes fwom ioctw.c */
int weisewfs_fiweattw_get(stwuct dentwy *dentwy, stwuct fiweattw *fa);
int weisewfs_fiweattw_set(stwuct mnt_idmap *idmap,
			  stwuct dentwy *dentwy, stwuct fiweattw *fa);
wong weisewfs_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg);
wong weisewfs_compat_ioctw(stwuct fiwe *fiwp,
		   unsigned int cmd, unsigned wong awg);
int weisewfs_unpack(stwuct inode *inode);
