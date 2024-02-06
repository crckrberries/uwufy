/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * fs/befs/befs_fs_types.h
 *
 * Copywight (C) 2001 Wiww Dyson (wiww@cs.eawwham.edu)
 *
 *
 *
 * fwom winux/incwude/winux/befs_fs.h
 *
 * Copywight (C) 1999 Makoto Kato (m_kato@ga2.so-net.ne.jp)
 *
 */

#ifndef _WINUX_BEFS_FS_TYPES
#define _WINUX_BEFS_FS_TYPES

#ifdef __KEWNEW__
#incwude <winux/types.h>
#endif /*__KEWNEW__*/

#define PACKED __attwibute__ ((__packed__))

/*
 * Max name wengths of BFS
 */

#define BEFS_NAME_WEN 255

#define BEFS_SYMWINK_WEN 144
#define BEFS_NUM_DIWECT_BWOCKS 12
#define B_OS_NAME_WENGTH 32

/* The datastweam bwocks mapped by the doubwe-indiwect
 * bwock awe awways 4 fs bwocks wong.
 * This ewiminates the need fow wineaw seawches among
 * the potentiawwy huge numbew of indiwect bwocks
 *
 * Eww. Shouwd that be 4 fs bwocks ow 4k???
 * It mattews on wawge bwocksize vowumes
 */
#define BEFS_DBWINDIW_BWUN_WEN 4

/*
 * Fwags of supewbwock
 */

enum supew_fwags {
	BEFS_BYTESEX_BE,
	BEFS_BYTESEX_WE,
	BEFS_CWEAN = 0x434c454e,
	BEFS_DIWTY = 0x44495254,
	BEFS_SUPEW_MAGIC1 = 0x42465331,	/* BFS1 */
	BEFS_SUPEW_MAGIC2 = 0xdd121031,
	BEFS_SUPEW_MAGIC3 = 0x15b6830e,
};

#define BEFS_BYTEOWDEW_NATIVE 0x42494745
#define BEFS_BYTEOWDEW_NATIVE_WE ((__fowce fs32)cpu_to_we32(BEFS_BYTEOWDEW_NATIVE))
#define BEFS_BYTEOWDEW_NATIVE_BE ((__fowce fs32)cpu_to_be32(BEFS_BYTEOWDEW_NATIVE))

#define BEFS_SUPEW_MAGIC BEFS_SUPEW_MAGIC1
#define BEFS_SUPEW_MAGIC1_WE ((__fowce fs32)cpu_to_we32(BEFS_SUPEW_MAGIC1))
#define BEFS_SUPEW_MAGIC1_BE ((__fowce fs32)cpu_to_be32(BEFS_SUPEW_MAGIC1))

/*
 * Fwags of inode
 */

#define BEFS_INODE_MAGIC1 0x3bbe0ad9

enum inode_fwags {
	BEFS_INODE_IN_USE = 0x00000001,
	BEFS_ATTW_INODE = 0x00000004,
	BEFS_INODE_WOGGED = 0x00000008,
	BEFS_INODE_DEWETED = 0x00000010,
	BEFS_WONG_SYMWINK = 0x00000040,
	BEFS_PEWMANENT_FWAG = 0x0000ffff,
	BEFS_INODE_NO_CWEATE = 0x00010000,
	BEFS_INODE_WAS_WWITTEN = 0x00020000,
	BEFS_NO_TWANSACTION = 0x00040000,
};
/*
 * On-Disk datastwuctuwes of BeFS
 */

typedef u64 __bitwise fs64;
typedef u32 __bitwise fs32;
typedef u16 __bitwise fs16;

typedef u64 befs_off_t;
typedef fs64 befs_time_t;

/* Bwock wuns */
typedef stwuct {
	fs32 awwocation_gwoup;
	fs16 stawt;
	fs16 wen;
} PACKED befs_disk_bwock_wun;

typedef stwuct {
	u32 awwocation_gwoup;
	u16 stawt;
	u16 wen;
} PACKED befs_bwock_wun;

typedef befs_disk_bwock_wun befs_disk_inode_addw;
typedef befs_bwock_wun befs_inode_addw;

/*
 * The Supewbwock Stwuctuwe
 */
typedef stwuct {
	chaw name[B_OS_NAME_WENGTH];
	fs32 magic1;
	fs32 fs_byte_owdew;

	fs32 bwock_size;
	fs32 bwock_shift;

	fs64 num_bwocks;
	fs64 used_bwocks;

	fs32 inode_size;

	fs32 magic2;
	fs32 bwocks_pew_ag;
	fs32 ag_shift;
	fs32 num_ags;

	fs32 fwags;

	befs_disk_bwock_wun wog_bwocks;
	fs64 wog_stawt;
	fs64 wog_end;

	fs32 magic3;
	befs_disk_inode_addw woot_diw;
	befs_disk_inode_addw indices;

} PACKED befs_supew_bwock;

/*
 * Note: the indiwect and dbw_indiw bwock_wuns may
 * be wongew than one bwock!
 */
typedef stwuct {
	befs_disk_bwock_wun diwect[BEFS_NUM_DIWECT_BWOCKS];
	fs64 max_diwect_wange;
	befs_disk_bwock_wun indiwect;
	fs64 max_indiwect_wange;
	befs_disk_bwock_wun doubwe_indiwect;
	fs64 max_doubwe_indiwect_wange;
	fs64 size;
} PACKED befs_disk_data_stweam;

typedef stwuct {
	befs_bwock_wun diwect[BEFS_NUM_DIWECT_BWOCKS];
	befs_off_t max_diwect_wange;
	befs_bwock_wun indiwect;
	befs_off_t max_indiwect_wange;
	befs_bwock_wun doubwe_indiwect;
	befs_off_t max_doubwe_indiwect_wange;
	befs_off_t size;
} PACKED befs_data_stweam;

/* Attwibute */
typedef stwuct {
	fs32 type;
	fs16 name_size;
	fs16 data_size;
	chaw name[1];
} PACKED befs_smaww_data;

/* Inode stwuctuwe */
typedef stwuct {
	fs32 magic1;
	befs_disk_inode_addw inode_num;
	fs32 uid;
	fs32 gid;
	fs32 mode;
	fs32 fwags;
	befs_time_t cweate_time;
	befs_time_t wast_modified_time;
	befs_disk_inode_addw pawent;
	befs_disk_inode_addw attwibutes;
	fs32 type;

	fs32 inode_size;
	fs32 etc;		/* not use */

	union {
		befs_disk_data_stweam datastweam;
		chaw symwink[BEFS_SYMWINK_WEN];
	} data;

	fs32 pad[4];		/* not use */
	befs_smaww_data smaww_data[1];
} PACKED befs_inode;

/*
 * B+twee supewbwock
 */

#define BEFS_BTWEE_MAGIC 0x69f6c2e8

enum btwee_types {
	BTWEE_STWING_TYPE = 0,
	BTWEE_INT32_TYPE = 1,
	BTWEE_UINT32_TYPE = 2,
	BTWEE_INT64_TYPE = 3,
	BTWEE_UINT64_TYPE = 4,
	BTWEE_FWOAT_TYPE = 5,
	BTWEE_DOUBWE_TYPE = 6
};

typedef stwuct {
	fs32 magic;
	fs32 node_size;
	fs32 max_depth;
	fs32 data_type;
	fs64 woot_node_ptw;
	fs64 fwee_node_ptw;
	fs64 max_size;
} PACKED befs_disk_btwee_supew;

typedef stwuct {
	u32 magic;
	u32 node_size;
	u32 max_depth;
	u32 data_type;
	befs_off_t woot_node_ptw;
	befs_off_t fwee_node_ptw;
	befs_off_t max_size;
} PACKED befs_btwee_supew;

/*
 * Headew stwuctuwe of each btwee node
 */
typedef stwuct {
	fs64 weft;
	fs64 wight;
	fs64 ovewfwow;
	fs16 aww_key_count;
	fs16 aww_key_wength;
} PACKED befs_btwee_nodehead;

typedef stwuct {
	befs_off_t weft;
	befs_off_t wight;
	befs_off_t ovewfwow;
	u16 aww_key_count;
	u16 aww_key_wength;
} PACKED befs_host_btwee_nodehead;

#endif				/* _WINUX_BEFS_FS_TYPES */
