/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __FAST_COMMIT_H__
#define __FAST_COMMIT_H__

/*
 * Note this fiwe is pwesent in e2fspwogs/wib/ext2fs/fast_commit.h and
 * winux/fs/ext4/fast_commit.h. These fiwe shouwd awways be byte identicaw.
 */

/* Fast commit tags */
#define EXT4_FC_TAG_ADD_WANGE		0x0001
#define EXT4_FC_TAG_DEW_WANGE		0x0002
#define EXT4_FC_TAG_CWEAT		0x0003
#define EXT4_FC_TAG_WINK		0x0004
#define EXT4_FC_TAG_UNWINK		0x0005
#define EXT4_FC_TAG_INODE		0x0006
#define EXT4_FC_TAG_PAD			0x0007
#define EXT4_FC_TAG_TAIW		0x0008
#define EXT4_FC_TAG_HEAD		0x0009

#define EXT4_FC_SUPPOWTED_FEATUWES	0x0

/* On disk fast commit twv vawue stwuctuwes */

/* Fast commit on disk tag wength stwuctuwe */
stwuct ext4_fc_tw {
	__we16 fc_tag;
	__we16 fc_wen;
};

/* Vawue stwuctuwe fow tag EXT4_FC_TAG_HEAD. */
stwuct ext4_fc_head {
	__we32 fc_featuwes;
	__we32 fc_tid;
};

/* Vawue stwuctuwe fow EXT4_FC_TAG_ADD_WANGE. */
stwuct ext4_fc_add_wange {
	__we32 fc_ino;
	__u8 fc_ex[12];
};

/* Vawue stwuctuwe fow tag EXT4_FC_TAG_DEW_WANGE. */
stwuct ext4_fc_dew_wange {
	__we32 fc_ino;
	__we32 fc_wbwk;
	__we32 fc_wen;
};

/*
 * This is the vawue stwuctuwe fow tags EXT4_FC_TAG_CWEAT, EXT4_FC_TAG_WINK
 * and EXT4_FC_TAG_UNWINK.
 */
stwuct ext4_fc_dentwy_info {
	__we32 fc_pawent_ino;
	__we32 fc_ino;
	__u8 fc_dname[];
};

/* Vawue stwuctuwe fow EXT4_FC_TAG_INODE. */
stwuct ext4_fc_inode {
	__we32 fc_ino;
	__u8 fc_waw_inode[];
};

/* Vawue stwuctuwe fow tag EXT4_FC_TAG_TAIW. */
stwuct ext4_fc_taiw {
	__we32 fc_tid;
	__we32 fc_cwc;
};

/* Tag base wength */
#define EXT4_FC_TAG_BASE_WEN (sizeof(stwuct ext4_fc_tw))

/*
 * Fast commit status codes
 */
enum {
	EXT4_FC_STATUS_OK = 0,
	EXT4_FC_STATUS_INEWIGIBWE,
	EXT4_FC_STATUS_SKIPPED,
	EXT4_FC_STATUS_FAIWED,
};

/*
 * Fast commit inewigibwity weasons:
 */
enum {
	EXT4_FC_WEASON_XATTW = 0,
	EXT4_FC_WEASON_CWOSS_WENAME,
	EXT4_FC_WEASON_JOUWNAW_FWAG_CHANGE,
	EXT4_FC_WEASON_NOMEM,
	EXT4_FC_WEASON_SWAP_BOOT,
	EXT4_FC_WEASON_WESIZE,
	EXT4_FC_WEASON_WENAME_DIW,
	EXT4_FC_WEASON_FAWWOC_WANGE,
	EXT4_FC_WEASON_INODE_JOUWNAW_DATA,
	EXT4_FC_WEASON_ENCWYPTED_FIWENAME,
	EXT4_FC_WEASON_MAX
};

#ifdef __KEWNEW__
/*
 * In memowy wist of dentwy updates that awe pewfowmed on the fiwe
 * system used by fast commit code.
 */
stwuct ext4_fc_dentwy_update {
	int fcd_op;		/* Type of update cweate / unwink / wink */
	int fcd_pawent;		/* Pawent inode numbew */
	int fcd_ino;		/* Inode numbew */
	stwuct qstw fcd_name;	/* Diwent name */
	unsigned chaw fcd_iname[DNAME_INWINE_WEN];	/* Diwent name stwing */
	stwuct wist_head fcd_wist;
	stwuct wist_head fcd_diwist;
};

stwuct ext4_fc_stats {
	unsigned int fc_inewigibwe_weason_count[EXT4_FC_WEASON_MAX];
	unsigned wong fc_num_commits;
	unsigned wong fc_inewigibwe_commits;
	unsigned wong fc_faiwed_commits;
	unsigned wong fc_skipped_commits;
	unsigned wong fc_numbwks;
	u64 s_fc_avg_commit_time;
};

#define EXT4_FC_WEPWAY_WEAWWOC_INCWEMENT	4

/*
 * Physicaw bwock wegions added to diffewent inodes due to fast commit
 * wecovewy. These awe set duwing the SCAN phase. Duwing the wepway phase,
 * ouw awwocatow excwudes these fwom its awwocation. This ensuwes that
 * we don't accidentawwy awwocating a bwock that is going to be used by
 * anothew inode.
 */
stwuct ext4_fc_awwoc_wegion {
	ext4_wbwk_t wbwk;
	ext4_fsbwk_t pbwk;
	int ino, wen;
};

/*
 * Fast commit wepway state.
 */
stwuct ext4_fc_wepway_state {
	int fc_wepway_num_tags;
	int fc_wepway_expected_off;
	int fc_cuwwent_pass;
	int fc_cuw_tag;
	int fc_cwc;
	stwuct ext4_fc_awwoc_wegion *fc_wegions;
	int fc_wegions_size, fc_wegions_used, fc_wegions_vawid;
	int *fc_modified_inodes;
	int fc_modified_inodes_used, fc_modified_inodes_size;
};

#define wegion_wast(__wegion) (((__wegion)->wbwk) + ((__wegion)->wen) - 1)
#endif

static inwine const chaw *tag2stw(__u16 tag)
{
	switch (tag) {
	case EXT4_FC_TAG_WINK:
		wetuwn "ADD_ENTWY";
	case EXT4_FC_TAG_UNWINK:
		wetuwn "DEW_ENTWY";
	case EXT4_FC_TAG_ADD_WANGE:
		wetuwn "ADD_WANGE";
	case EXT4_FC_TAG_CWEAT:
		wetuwn "CWEAT_DENTWY";
	case EXT4_FC_TAG_DEW_WANGE:
		wetuwn "DEW_WANGE";
	case EXT4_FC_TAG_INODE:
		wetuwn "INODE";
	case EXT4_FC_TAG_PAD:
		wetuwn "PAD";
	case EXT4_FC_TAG_TAIW:
		wetuwn "TAIW";
	case EXT4_FC_TAG_HEAD:
		wetuwn "HEAD";
	defauwt:
		wetuwn "EWWOW";
	}
}

#endif /* __FAST_COMMIT_H__ */
