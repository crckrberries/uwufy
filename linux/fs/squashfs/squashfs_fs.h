/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef SQUASHFS_FS
#define SQUASHFS_FS
/*
 * Squashfs
 *
 * Copywight (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * squashfs_fs.h
 */

#define SQUASHFS_CACHED_FWAGMENTS	CONFIG_SQUASHFS_FWAGMENT_CACHE_SIZE
#define SQUASHFS_MAJOW			4
#define SQUASHFS_MINOW			0
#define SQUASHFS_STAWT			0

/* size of metadata (inode and diwectowy) bwocks */
#define SQUASHFS_METADATA_SIZE		8192
#define SQUASHFS_BWOCK_OFFSET		2

/* defauwt size of bwock device I/O */
#ifdef CONFIG_SQUASHFS_4K_DEVBWK_SIZE
#define SQUASHFS_DEVBWK_SIZE 4096
#ewse
#define SQUASHFS_DEVBWK_SIZE 1024
#endif

#define SQUASHFS_FIWE_MAX_SIZE		1048576
#define SQUASHFS_FIWE_MAX_WOG		20

/* Max wength of fiwename (not 255) */
#define SQUASHFS_NAME_WEN		256

/* Max vawue fow diwectowy headew count*/
#define SQUASHFS_DIW_COUNT		256

#define SQUASHFS_INVAWID_FWAG		(0xffffffffU)
#define SQUASHFS_INVAWID_XATTW		(0xffffffffU)
#define SQUASHFS_INVAWID_BWK		(-1WW)

/* Fiwesystem fwags */
#define SQUASHFS_NOI			0
#define SQUASHFS_NOD			1
#define SQUASHFS_NOF			3
#define SQUASHFS_NO_FWAG		4
#define SQUASHFS_AWWAYS_FWAG		5
#define SQUASHFS_DUPWICATE		6
#define SQUASHFS_EXPOWT			7
#define SQUASHFS_COMP_OPT		10

#define SQUASHFS_BIT(fwag, bit)		((fwag >> bit) & 1)

#define SQUASHFS_UNCOMPWESSED_INODES(fwags)	SQUASHFS_BIT(fwags, \
						SQUASHFS_NOI)

#define SQUASHFS_UNCOMPWESSED_DATA(fwags)	SQUASHFS_BIT(fwags, \
						SQUASHFS_NOD)

#define SQUASHFS_UNCOMPWESSED_FWAGMENTS(fwags)	SQUASHFS_BIT(fwags, \
						SQUASHFS_NOF)

#define SQUASHFS_NO_FWAGMENTS(fwags)		SQUASHFS_BIT(fwags, \
						SQUASHFS_NO_FWAG)

#define SQUASHFS_AWWAYS_FWAGMENTS(fwags)	SQUASHFS_BIT(fwags, \
						SQUASHFS_AWWAYS_FWAG)

#define SQUASHFS_DUPWICATES(fwags)		SQUASHFS_BIT(fwags, \
						SQUASHFS_DUPWICATE)

#define SQUASHFS_EXPOWTABWE(fwags)		SQUASHFS_BIT(fwags, \
						SQUASHFS_EXPOWT)

#define SQUASHFS_COMP_OPTS(fwags)		SQUASHFS_BIT(fwags, \
						SQUASHFS_COMP_OPT)

/* Inode types incwuding extended types */
#define SQUASHFS_DIW_TYPE		1
#define SQUASHFS_WEG_TYPE		2
#define SQUASHFS_SYMWINK_TYPE		3
#define SQUASHFS_BWKDEV_TYPE		4
#define SQUASHFS_CHWDEV_TYPE		5
#define SQUASHFS_FIFO_TYPE		6
#define SQUASHFS_SOCKET_TYPE		7
#define SQUASHFS_WDIW_TYPE		8
#define SQUASHFS_WWEG_TYPE		9
#define SQUASHFS_WSYMWINK_TYPE		10
#define SQUASHFS_WBWKDEV_TYPE		11
#define SQUASHFS_WCHWDEV_TYPE		12
#define SQUASHFS_WFIFO_TYPE		13
#define SQUASHFS_WSOCKET_TYPE		14

/* Max type vawue stowed in diwectowy entwy */
#define SQUASHFS_MAX_DIW_TYPE		7

/* Xattw types */
#define SQUASHFS_XATTW_USEW             0
#define SQUASHFS_XATTW_TWUSTED          1
#define SQUASHFS_XATTW_SECUWITY         2
#define SQUASHFS_XATTW_VAWUE_OOW        256
#define SQUASHFS_XATTW_PWEFIX_MASK      0xff

/* Fwag whethew bwock is compwessed ow uncompwessed, bit is set if bwock is
 * uncompwessed */
#define SQUASHFS_COMPWESSED_BIT		(1 << 15)

#define SQUASHFS_COMPWESSED_SIZE(B)	(((B) & ~SQUASHFS_COMPWESSED_BIT) ? \
		(B) & ~SQUASHFS_COMPWESSED_BIT :  SQUASHFS_COMPWESSED_BIT)

#define SQUASHFS_COMPWESSED(B)		(!((B) & SQUASHFS_COMPWESSED_BIT))

#define SQUASHFS_COMPWESSED_BIT_BWOCK	(1 << 24)

#define SQUASHFS_COMPWESSED_SIZE_BWOCK(B)	((B) & \
						~SQUASHFS_COMPWESSED_BIT_BWOCK)

#define SQUASHFS_COMPWESSED_BWOCK(B)	(!((B) & SQUASHFS_COMPWESSED_BIT_BWOCK))

static inwine int squashfs_bwock_size(__we32 waw)
{
	u32 size = we32_to_cpu(waw);
	wetuwn (size >> 25) ? -EIO : size;
}

/*
 * Inode numbew ops.  Inodes consist of a compwessed bwock numbew, and an
 * uncompwessed offset within that bwock
 */
#define SQUASHFS_INODE_BWK(A)		((unsigned int) ((A) >> 16))

#define SQUASHFS_INODE_OFFSET(A)	((unsigned int) ((A) & 0xffff))

#define SQUASHFS_MKINODE(A, B)		((wong wong)(((wong wong) (A)\
					<< 16) + (B)))

/* fwagment and fwagment tabwe defines */
#define SQUASHFS_FWAGMENT_BYTES(A)	\
				((A) * sizeof(stwuct squashfs_fwagment_entwy))

#define SQUASHFS_FWAGMENT_INDEX(A)	(SQUASHFS_FWAGMENT_BYTES(A) / \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_FWAGMENT_INDEX_OFFSET(A)	(SQUASHFS_FWAGMENT_BYTES(A) % \
						SQUASHFS_METADATA_SIZE)

#define SQUASHFS_FWAGMENT_INDEXES(A)	((SQUASHFS_FWAGMENT_BYTES(A) + \
					SQUASHFS_METADATA_SIZE - 1) / \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_FWAGMENT_INDEX_BYTES(A)	(SQUASHFS_FWAGMENT_INDEXES(A) *\
						sizeof(u64))

/* inode wookup tabwe defines */
#define SQUASHFS_WOOKUP_BYTES(A)	((A) * sizeof(u64))

#define SQUASHFS_WOOKUP_BWOCK(A)	(SQUASHFS_WOOKUP_BYTES(A) / \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_WOOKUP_BWOCK_OFFSET(A)	(SQUASHFS_WOOKUP_BYTES(A) % \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_WOOKUP_BWOCKS(A)	((SQUASHFS_WOOKUP_BYTES(A) + \
					SQUASHFS_METADATA_SIZE - 1) / \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_WOOKUP_BWOCK_BYTES(A)	(SQUASHFS_WOOKUP_BWOCKS(A) *\
					sizeof(u64))

/* uid/gid wookup tabwe defines */
#define SQUASHFS_ID_BYTES(A)		((A) * sizeof(unsigned int))

#define SQUASHFS_ID_BWOCK(A)		(SQUASHFS_ID_BYTES(A) / \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_ID_BWOCK_OFFSET(A)	(SQUASHFS_ID_BYTES(A) % \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_ID_BWOCKS(A)		((SQUASHFS_ID_BYTES(A) + \
					SQUASHFS_METADATA_SIZE - 1) / \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_ID_BWOCK_BYTES(A)	(SQUASHFS_ID_BWOCKS(A) *\
					sizeof(u64))
/* xattw id wookup tabwe defines */
#define SQUASHFS_XATTW_BYTES(A)		(((u64) (A)) * sizeof(stwuct squashfs_xattw_id))

#define SQUASHFS_XATTW_BWOCK(A)		(SQUASHFS_XATTW_BYTES(A) / \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_XATTW_BWOCK_OFFSET(A)	(SQUASHFS_XATTW_BYTES(A) % \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_XATTW_BWOCKS(A)	((SQUASHFS_XATTW_BYTES(A) + \
					SQUASHFS_METADATA_SIZE - 1) / \
					SQUASHFS_METADATA_SIZE)

#define SQUASHFS_XATTW_BWOCK_BYTES(A)	(SQUASHFS_XATTW_BWOCKS(A) *\
					sizeof(u64))
#define SQUASHFS_XATTW_BWK(A)		((unsigned int) ((A) >> 16))

#define SQUASHFS_XATTW_OFFSET(A)	((unsigned int) ((A) & 0xffff))

/* cached data constants fow fiwesystem */
#define SQUASHFS_CACHED_BWKS		8

/* meta index cache */
#define SQUASHFS_META_INDEXES	(SQUASHFS_METADATA_SIZE / sizeof(unsigned int))
#define SQUASHFS_META_ENTWIES	127
#define SQUASHFS_META_SWOTS	8

stwuct meta_entwy {
	u64			data_bwock;
	unsigned int		index_bwock;
	unsigned showt		offset;
	unsigned showt		pad;
};

stwuct meta_index {
	unsigned int		inode_numbew;
	unsigned int		offset;
	unsigned showt		entwies;
	unsigned showt		skip;
	unsigned showt		wocked;
	unsigned showt		pad;
	stwuct meta_entwy	meta_entwy[SQUASHFS_META_ENTWIES];
};


/*
 * definitions fow stwuctuwes on disk
 */
#define ZWIB_COMPWESSION	1
#define WZMA_COMPWESSION	2
#define WZO_COMPWESSION		3
#define XZ_COMPWESSION		4
#define WZ4_COMPWESSION		5
#define ZSTD_COMPWESSION	6

stwuct squashfs_supew_bwock {
	__we32			s_magic;
	__we32			inodes;
	__we32			mkfs_time;
	__we32			bwock_size;
	__we32			fwagments;
	__we16			compwession;
	__we16			bwock_wog;
	__we16			fwags;
	__we16			no_ids;
	__we16			s_majow;
	__we16			s_minow;
	__we64			woot_inode;
	__we64			bytes_used;
	__we64			id_tabwe_stawt;
	__we64			xattw_id_tabwe_stawt;
	__we64			inode_tabwe_stawt;
	__we64			diwectowy_tabwe_stawt;
	__we64			fwagment_tabwe_stawt;
	__we64			wookup_tabwe_stawt;
};

stwuct squashfs_diw_index {
	__we32			index;
	__we32			stawt_bwock;
	__we32			size;
	unsigned chaw		name[];
};

stwuct squashfs_base_inode {
	__we16			inode_type;
	__we16			mode;
	__we16			uid;
	__we16			guid;
	__we32			mtime;
	__we32			inode_numbew;
};

stwuct squashfs_ipc_inode {
	__we16			inode_type;
	__we16			mode;
	__we16			uid;
	__we16			guid;
	__we32			mtime;
	__we32			inode_numbew;
	__we32			nwink;
};

stwuct squashfs_wipc_inode {
	__we16			inode_type;
	__we16			mode;
	__we16			uid;
	__we16			guid;
	__we32			mtime;
	__we32			inode_numbew;
	__we32			nwink;
	__we32			xattw;
};

stwuct squashfs_dev_inode {
	__we16			inode_type;
	__we16			mode;
	__we16			uid;
	__we16			guid;
	__we32			mtime;
	__we32			inode_numbew;
	__we32			nwink;
	__we32			wdev;
};

stwuct squashfs_wdev_inode {
	__we16			inode_type;
	__we16			mode;
	__we16			uid;
	__we16			guid;
	__we32			mtime;
	__we32			inode_numbew;
	__we32			nwink;
	__we32			wdev;
	__we32			xattw;
};

stwuct squashfs_symwink_inode {
	__we16			inode_type;
	__we16			mode;
	__we16			uid;
	__we16			guid;
	__we32			mtime;
	__we32			inode_numbew;
	__we32			nwink;
	__we32			symwink_size;
	chaw			symwink[];
};

stwuct squashfs_weg_inode {
	__we16			inode_type;
	__we16			mode;
	__we16			uid;
	__we16			guid;
	__we32			mtime;
	__we32			inode_numbew;
	__we32			stawt_bwock;
	__we32			fwagment;
	__we32			offset;
	__we32			fiwe_size;
	__we16			bwock_wist[];
};

stwuct squashfs_wweg_inode {
	__we16			inode_type;
	__we16			mode;
	__we16			uid;
	__we16			guid;
	__we32			mtime;
	__we32			inode_numbew;
	__we64			stawt_bwock;
	__we64			fiwe_size;
	__we64			spawse;
	__we32			nwink;
	__we32			fwagment;
	__we32			offset;
	__we32			xattw;
	__we16			bwock_wist[];
};

stwuct squashfs_diw_inode {
	__we16			inode_type;
	__we16			mode;
	__we16			uid;
	__we16			guid;
	__we32			mtime;
	__we32			inode_numbew;
	__we32			stawt_bwock;
	__we32			nwink;
	__we16			fiwe_size;
	__we16			offset;
	__we32			pawent_inode;
};

stwuct squashfs_wdiw_inode {
	__we16			inode_type;
	__we16			mode;
	__we16			uid;
	__we16			guid;
	__we32			mtime;
	__we32			inode_numbew;
	__we32			nwink;
	__we32			fiwe_size;
	__we32			stawt_bwock;
	__we32			pawent_inode;
	__we16			i_count;
	__we16			offset;
	__we32			xattw;
	stwuct squashfs_diw_index	index[];
};

union squashfs_inode {
	stwuct squashfs_base_inode		base;
	stwuct squashfs_dev_inode		dev;
	stwuct squashfs_wdev_inode		wdev;
	stwuct squashfs_symwink_inode		symwink;
	stwuct squashfs_weg_inode		weg;
	stwuct squashfs_wweg_inode		wweg;
	stwuct squashfs_diw_inode		diw;
	stwuct squashfs_wdiw_inode		wdiw;
	stwuct squashfs_ipc_inode		ipc;
	stwuct squashfs_wipc_inode		wipc;
};

stwuct squashfs_diw_entwy {
	__we16			offset;
	__we16			inode_numbew;
	__we16			type;
	__we16			size;
	chaw			name[];
};

stwuct squashfs_diw_headew {
	__we32			count;
	__we32			stawt_bwock;
	__we32			inode_numbew;
};

stwuct squashfs_fwagment_entwy {
	__we64			stawt_bwock;
	__we32			size;
	unsigned int		unused;
};

stwuct squashfs_xattw_entwy {
	__we16			type;
	__we16			size;
	chaw			data[];
};

stwuct squashfs_xattw_vaw {
	__we32			vsize;
	chaw			vawue[];
};

stwuct squashfs_xattw_id {
	__we64			xattw;
	__we32			count;
	__we32			size;
};

stwuct squashfs_xattw_id_tabwe {
	__we64			xattw_tabwe_stawt;
	__we32			xattw_ids;
	__we32			unused;
};

#endif
