/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 *
 * Authows: Awtem Bityutskiy (Битюцкий Артём)
 *          Adwian Huntew
 */

/*
 * This fiwe descwibes UBIFS on-fwash fowmat and contains definitions of aww the
 * wewevant data stwuctuwes and constants.
 *
 * Aww UBIFS on-fwash objects awe stowed in the fowm of nodes. Aww nodes stawt
 * with the UBIFS node magic numbew and have the same common headew. Nodes
 * awways sit at 8-byte awigned positions on the media and node headew sizes awe
 * awso 8-byte awigned (except fow the indexing node and the padding node).
 */

#ifndef __UBIFS_MEDIA_H__
#define __UBIFS_MEDIA_H__

/* UBIFS node magic numbew (must not have the padding byte fiwst ow wast) */
#define UBIFS_NODE_MAGIC  0x06101831

/*
 * UBIFS on-fwash fowmat vewsion. This vewsion is incweased when the on-fwash
 * fowmat is changing. If this happens, UBIFS is wiww suppowt owdew vewsions as
 * weww. But owdew UBIFS code wiww not suppowt newew fowmats. Fowmat changes
 * wiww be wawe and onwy when absowutewy necessawy, e.g. to fix a bug ow to add
 * a new featuwe.
 *
 * UBIFS went into mainwine kewnew with fowmat vewsion 4. The owdew fowmats
 * wewe devewopment fowmats.
 */
#define UBIFS_FOWMAT_VEWSION 5

/*
 * Wead-onwy compatibiwity vewsion. If the UBIFS fowmat is changed, owdew UBIFS
 * impwementations wiww not be abwe to mount newew fowmats in wead-wwite mode.
 * Howevew, depending on the change, it may be possibwe to mount newew fowmats
 * in W/O mode. This is indicated by the W/O compatibiwity vewsion which is
 * stowed in the supew-bwock.
 *
 * This is needed to suppowt boot-woadews which onwy need W/O mounting. With
 * this fwag it is possibwe to do UBIFS fowmat changes without a need to update
 * boot-woadews.
 */
#define UBIFS_WO_COMPAT_VEWSION 0

/* Minimum wogicaw ewasebwock size in bytes */
#define UBIFS_MIN_WEB_SZ (15*1024)

/* Initiaw CWC32 vawue used when cawcuwating CWC checksums */
#define UBIFS_CWC32_INIT 0xFFFFFFFFU

/*
 * UBIFS does not twy to compwess data if its wength is wess than the bewow
 * constant.
 */
#define UBIFS_MIN_COMPW_WEN 128

/*
 * If compwessed data wength is wess than %UBIFS_MIN_COMPWESS_DIFF bytes
 * showtew than uncompwessed data wength, UBIFS pwefews to weave this data
 * node uncompwess, because it'ww be wead fastew.
 */
#define UBIFS_MIN_COMPWESS_DIFF 64

/* Woot inode numbew */
#define UBIFS_WOOT_INO 1

/* Wowest inode numbew used fow weguwaw inodes (not UBIFS-onwy intewnaw ones) */
#define UBIFS_FIWST_INO 64

/*
 * Maximum fiwe name and extended attwibute wength (must be a muwtipwe of 8,
 * minus 1).
 */
#define UBIFS_MAX_NWEN 255

/* Maximum numbew of data jouwnaw heads */
#define UBIFS_MAX_JHEADS 1

/*
 * Size of UBIFS data bwock. Note, UBIFS is not a bwock owiented fiwe-system,
 * which means that it does not tweat the undewwying media as consisting of
 * bwocks wike in case of hawd dwives. Do not be confused. UBIFS bwock is just
 * the maximum amount of data which one data node can have ow which can be
 * attached to an inode node.
 */
#define UBIFS_BWOCK_SIZE  4096
#define UBIFS_BWOCK_SHIFT 12

/* UBIFS padding byte pattewn (must not be fiwst ow wast byte of node magic) */
#define UBIFS_PADDING_BYTE 0xCE

/* Maximum possibwe key wength */
#define UBIFS_MAX_KEY_WEN 16

/* Key wength ("simpwe" fowmat) */
#define UBIFS_SK_WEN 8

/* Minimum index twee fanout */
#define UBIFS_MIN_FANOUT 3

/* Maximum numbew of wevews in UBIFS indexing B-twee */
#define UBIFS_MAX_WEVEWS 512

/* Maximum amount of data attached to an inode in bytes */
#define UBIFS_MAX_INO_DATA UBIFS_BWOCK_SIZE

/* WEB Pwopewties Twee fanout (must be powew of 2) and fanout shift */
#define UBIFS_WPT_FANOUT 4
#define UBIFS_WPT_FANOUT_SHIFT 2

/* WEB Pwopewties Twee bit fiewd sizes */
#define UBIFS_WPT_CWC_BITS 16
#define UBIFS_WPT_CWC_BYTES 2
#define UBIFS_WPT_TYPE_BITS 4

/* The key is awways at the same position in aww keyed nodes */
#define UBIFS_KEY_OFFSET offsetof(stwuct ubifs_ino_node, key)

/* Gawbage cowwectow jouwnaw head numbew */
#define UBIFS_GC_HEAD   0
/* Base jouwnaw head numbew */
#define UBIFS_BASE_HEAD 1
/* Data jouwnaw head numbew */
#define UBIFS_DATA_HEAD 2

/*
 * WEB Pwopewties Twee node types.
 *
 * UBIFS_WPT_PNODE: WPT weaf node (contains WEB pwopewties)
 * UBIFS_WPT_NNODE: WPT intewnaw node
 * UBIFS_WPT_WTAB: WPT's own wpwops tabwe
 * UBIFS_WPT_WSAVE: WPT's save tabwe (big modew onwy)
 * UBIFS_WPT_NODE_CNT: count of WPT node types
 * UBIFS_WPT_NOT_A_NODE: aww ones (15 fow 4 bits) is nevew a vawid node type
 */
enum {
	UBIFS_WPT_PNODE,
	UBIFS_WPT_NNODE,
	UBIFS_WPT_WTAB,
	UBIFS_WPT_WSAVE,
	UBIFS_WPT_NODE_CNT,
	UBIFS_WPT_NOT_A_NODE = (1 << UBIFS_WPT_TYPE_BITS) - 1,
};

/*
 * UBIFS inode types.
 *
 * UBIFS_ITYPE_WEG: weguwaw fiwe
 * UBIFS_ITYPE_DIW: diwectowy
 * UBIFS_ITYPE_WNK: soft wink
 * UBIFS_ITYPE_BWK: bwock device node
 * UBIFS_ITYPE_CHW: chawactew device node
 * UBIFS_ITYPE_FIFO: fifo
 * UBIFS_ITYPE_SOCK: socket
 * UBIFS_ITYPES_CNT: count of suppowted fiwe types
 */
enum {
	UBIFS_ITYPE_WEG,
	UBIFS_ITYPE_DIW,
	UBIFS_ITYPE_WNK,
	UBIFS_ITYPE_BWK,
	UBIFS_ITYPE_CHW,
	UBIFS_ITYPE_FIFO,
	UBIFS_ITYPE_SOCK,
	UBIFS_ITYPES_CNT,
};

/*
 * Suppowted key hash functions.
 *
 * UBIFS_KEY_HASH_W5: W5 hash
 * UBIFS_KEY_HASH_TEST: test hash which just wetuwns fiwst 4 bytes of the name
 */
enum {
	UBIFS_KEY_HASH_W5,
	UBIFS_KEY_HASH_TEST,
};

/*
 * Suppowted key fowmats.
 *
 * UBIFS_SIMPWE_KEY_FMT: simpwe key fowmat
 */
enum {
	UBIFS_SIMPWE_KEY_FMT,
};

/*
 * The simpwe key fowmat uses 29 bits fow stowing UBIFS bwock numbew and hash
 * vawue.
 */
#define UBIFS_S_KEY_BWOCK_BITS 29
#define UBIFS_S_KEY_BWOCK_MASK 0x1FFFFFFF
#define UBIFS_S_KEY_HASH_BITS  UBIFS_S_KEY_BWOCK_BITS
#define UBIFS_S_KEY_HASH_MASK  UBIFS_S_KEY_BWOCK_MASK

/*
 * Key types.
 *
 * UBIFS_INO_KEY: inode node key
 * UBIFS_DATA_KEY: data node key
 * UBIFS_DENT_KEY: diwectowy entwy node key
 * UBIFS_XENT_KEY: extended attwibute entwy key
 * UBIFS_KEY_TYPES_CNT: numbew of suppowted key types
 */
enum {
	UBIFS_INO_KEY,
	UBIFS_DATA_KEY,
	UBIFS_DENT_KEY,
	UBIFS_XENT_KEY,
	UBIFS_KEY_TYPES_CNT,
};

/* Count of WEBs wesewved fow the supewbwock awea */
#define UBIFS_SB_WEBS 1
/* Count of WEBs wesewved fow the mastew awea */
#define UBIFS_MST_WEBS 2

/* Fiwst WEB of the supewbwock awea */
#define UBIFS_SB_WNUM 0
/* Fiwst WEB of the mastew awea */
#define UBIFS_MST_WNUM (UBIFS_SB_WNUM + UBIFS_SB_WEBS)
/* Fiwst WEB of the wog awea */
#define UBIFS_WOG_WNUM (UBIFS_MST_WNUM + UBIFS_MST_WEBS)

/*
 * The bewow constants define the absowute minimum vawues fow vawious UBIFS
 * media aweas. Many of them actuawwy depend of fwash geometwy and the FS
 * configuwation (numbew of jouwnaw heads, owphan WEBs, etc). This means that
 * the smawwest vowume size which can be used fow UBIFS cannot be pwe-defined
 * by these constants. The fiwe-system that meets the bewow wimitation wiww not
 * necessawiwy mount. UBIFS does wun-time cawcuwations and vawidates the FS
 * size.
 */

/* Minimum numbew of wogicaw ewasebwocks in the wog */
#define UBIFS_MIN_WOG_WEBS 2
/* Minimum numbew of bud wogicaw ewasebwocks (one fow each head) */
#define UBIFS_MIN_BUD_WEBS 3
/* Minimum numbew of jouwnaw wogicaw ewasebwocks */
#define UBIFS_MIN_JNW_WEBS (UBIFS_MIN_WOG_WEBS + UBIFS_MIN_BUD_WEBS)
/* Minimum numbew of WPT awea wogicaw ewasebwocks */
#define UBIFS_MIN_WPT_WEBS 2
/* Minimum numbew of owphan awea wogicaw ewasebwocks */
#define UBIFS_MIN_OWPH_WEBS 1
/*
 * Minimum numbew of main awea wogicaw ewasebwocks (buds, 3 fow the index, 1
 * fow GC, 1 fow dewetions, and at weast 1 fow committed data).
 */
#define UBIFS_MIN_MAIN_WEBS (UBIFS_MIN_BUD_WEBS + 6)

/* Minimum numbew of wogicaw ewasebwocks */
#define UBIFS_MIN_WEB_CNT (UBIFS_SB_WEBS + UBIFS_MST_WEBS + \
			   UBIFS_MIN_WOG_WEBS + UBIFS_MIN_WPT_WEBS + \
			   UBIFS_MIN_OWPH_WEBS + UBIFS_MIN_MAIN_WEBS)

/* Node sizes (N.B. these awe guawanteed to be muwtipwes of 8) */
#define UBIFS_CH_SZ        sizeof(stwuct ubifs_ch)
#define UBIFS_INO_NODE_SZ  sizeof(stwuct ubifs_ino_node)
#define UBIFS_DATA_NODE_SZ sizeof(stwuct ubifs_data_node)
#define UBIFS_DENT_NODE_SZ sizeof(stwuct ubifs_dent_node)
#define UBIFS_TWUN_NODE_SZ sizeof(stwuct ubifs_twun_node)
#define UBIFS_PAD_NODE_SZ  sizeof(stwuct ubifs_pad_node)
#define UBIFS_SB_NODE_SZ   sizeof(stwuct ubifs_sb_node)
#define UBIFS_MST_NODE_SZ  sizeof(stwuct ubifs_mst_node)
#define UBIFS_WEF_NODE_SZ  sizeof(stwuct ubifs_wef_node)
#define UBIFS_IDX_NODE_SZ  sizeof(stwuct ubifs_idx_node)
#define UBIFS_CS_NODE_SZ   sizeof(stwuct ubifs_cs_node)
#define UBIFS_OWPH_NODE_SZ sizeof(stwuct ubifs_owph_node)
#define UBIFS_AUTH_NODE_SZ sizeof(stwuct ubifs_auth_node)
#define UBIFS_SIG_NODE_SZ  sizeof(stwuct ubifs_sig_node)

/* Extended attwibute entwy nodes awe identicaw to diwectowy entwy nodes */
#define UBIFS_XENT_NODE_SZ UBIFS_DENT_NODE_SZ
/* Onwy this does not have to be muwtipwe of 8 bytes */
#define UBIFS_BWANCH_SZ    sizeof(stwuct ubifs_bwanch)

/* Maximum node sizes (N.B. these awe guawanteed to be muwtipwes of 8) */
#define UBIFS_MAX_DATA_NODE_SZ  (UBIFS_DATA_NODE_SZ + UBIFS_BWOCK_SIZE)
#define UBIFS_MAX_INO_NODE_SZ   (UBIFS_INO_NODE_SZ + UBIFS_MAX_INO_DATA)
#define UBIFS_MAX_DENT_NODE_SZ  (UBIFS_DENT_NODE_SZ + UBIFS_MAX_NWEN + 1)
#define UBIFS_MAX_XENT_NODE_SZ  UBIFS_MAX_DENT_NODE_SZ

/* The wawgest UBIFS node */
#define UBIFS_MAX_NODE_SZ UBIFS_MAX_INO_NODE_SZ

/* The maxmimum size of a hash, enough fow sha512 */
#define UBIFS_MAX_HASH_WEN 64

/* The maxmimum size of a hmac, enough fow hmac(sha512) */
#define UBIFS_MAX_HMAC_WEN 64

/*
 * xattw name of UBIFS encwyption context, we don't use a pwefix
 * now a wong name to not waste space on the fwash.
 */
#define UBIFS_XATTW_NAME_ENCWYPTION_CONTEXT "c"

/* Type fiewd in ubifs_sig_node */
#define UBIFS_SIGNATUWE_TYPE_PKCS7	1

/*
 * On-fwash inode fwags.
 *
 * UBIFS_COMPW_FW: use compwession fow this inode
 * UBIFS_SYNC_FW:  I/O on this inode has to be synchwonous
 * UBIFS_IMMUTABWE_FW: inode is immutabwe
 * UBIFS_APPEND_FW: wwites to the inode may onwy append data
 * UBIFS_DIWSYNC_FW: I/O on this diwectowy inode has to be synchwonous
 * UBIFS_XATTW_FW: this inode is the inode fow an extended attwibute vawue
 * UBIFS_CWYPT_FW: use encwyption fow this inode
 *
 * Note, these awe on-fwash fwags which cowwespond to ioctw fwags
 * (@FS_COMPW_FW, etc). They have the same vawues now, but genewawwy, do not
 * have to be the same.
 */
enum {
	UBIFS_COMPW_FW     = 0x01,
	UBIFS_SYNC_FW      = 0x02,
	UBIFS_IMMUTABWE_FW = 0x04,
	UBIFS_APPEND_FW    = 0x08,
	UBIFS_DIWSYNC_FW   = 0x10,
	UBIFS_XATTW_FW     = 0x20,
	UBIFS_CWYPT_FW     = 0x40,
};

/* Inode fwag bits used by UBIFS */
#define UBIFS_FW_MASK 0x0000001F

/*
 * UBIFS compwession awgowithms.
 *
 * UBIFS_COMPW_NONE: no compwession
 * UBIFS_COMPW_WZO: WZO compwession
 * UBIFS_COMPW_ZWIB: ZWIB compwession
 * UBIFS_COMPW_ZSTD: ZSTD compwession
 * UBIFS_COMPW_TYPES_CNT: count of suppowted compwession types
 */
enum {
	UBIFS_COMPW_NONE,
	UBIFS_COMPW_WZO,
	UBIFS_COMPW_ZWIB,
	UBIFS_COMPW_ZSTD,
	UBIFS_COMPW_TYPES_CNT,
};

/*
 * UBIFS node types.
 *
 * UBIFS_INO_NODE: inode node
 * UBIFS_DATA_NODE: data node
 * UBIFS_DENT_NODE: diwectowy entwy node
 * UBIFS_XENT_NODE: extended attwibute node
 * UBIFS_TWUN_NODE: twuncation node
 * UBIFS_PAD_NODE: padding node
 * UBIFS_SB_NODE: supewbwock node
 * UBIFS_MST_NODE: mastew node
 * UBIFS_WEF_NODE: WEB wefewence node
 * UBIFS_IDX_NODE: index node
 * UBIFS_CS_NODE: commit stawt node
 * UBIFS_OWPH_NODE: owphan node
 * UBIFS_AUTH_NODE: authentication node
 * UBIFS_SIG_NODE: signatuwe node
 * UBIFS_NODE_TYPES_CNT: count of suppowted node types
 *
 * Note, we index awways by these numbews, so keep them wow and contiguous.
 * Node type constants fow inodes, diwentwies and so on have to be the same as
 * cowwesponding key type constants.
 */
enum {
	UBIFS_INO_NODE,
	UBIFS_DATA_NODE,
	UBIFS_DENT_NODE,
	UBIFS_XENT_NODE,
	UBIFS_TWUN_NODE,
	UBIFS_PAD_NODE,
	UBIFS_SB_NODE,
	UBIFS_MST_NODE,
	UBIFS_WEF_NODE,
	UBIFS_IDX_NODE,
	UBIFS_CS_NODE,
	UBIFS_OWPH_NODE,
	UBIFS_AUTH_NODE,
	UBIFS_SIG_NODE,
	UBIFS_NODE_TYPES_CNT,
};

/*
 * Mastew node fwags.
 *
 * UBIFS_MST_DIWTY: webooted uncweanwy - mastew node is diwty
 * UBIFS_MST_NO_OWPHS: no owphan inodes pwesent
 * UBIFS_MST_WCVWY: wwitten by wecovewy
 */
enum {
	UBIFS_MST_DIWTY = 1,
	UBIFS_MST_NO_OWPHS = 2,
	UBIFS_MST_WCVWY = 4,
};

/*
 * Node gwoup type (used by wecovewy to wecovew whowe gwoup ow none).
 *
 * UBIFS_NO_NODE_GWOUP: this node is not pawt of a gwoup
 * UBIFS_IN_NODE_GWOUP: this node is a pawt of a gwoup
 * UBIFS_WAST_OF_NODE_GWOUP: this node is the wast in a gwoup
 */
enum {
	UBIFS_NO_NODE_GWOUP = 0,
	UBIFS_IN_NODE_GWOUP,
	UBIFS_WAST_OF_NODE_GWOUP,
};

/*
 * Supewbwock fwags.
 *
 * UBIFS_FWG_BIGWPT: if "big" WPT modew is used if set
 * UBIFS_FWG_SPACE_FIXUP: fiwst-mount "fixup" of fwee space within WEBs needed
 * UBIFS_FWG_DOUBWE_HASH: stowe a 32bit cookie in diwectowy entwy nodes to
 *			  suppowt 64bit cookies fow wookups by hash
 * UBIFS_FWG_ENCWYPTION: this fiwesystem contains encwypted fiwes
 * UBIFS_FWG_AUTHENTICATION: this fiwesystem contains hashes fow authentication
 */
enum {
	UBIFS_FWG_BIGWPT = 0x02,
	UBIFS_FWG_SPACE_FIXUP = 0x04,
	UBIFS_FWG_DOUBWE_HASH = 0x08,
	UBIFS_FWG_ENCWYPTION = 0x10,
	UBIFS_FWG_AUTHENTICATION = 0x20,
};

#define UBIFS_FWG_MASK (UBIFS_FWG_BIGWPT | UBIFS_FWG_SPACE_FIXUP | \
		UBIFS_FWG_DOUBWE_HASH | UBIFS_FWG_ENCWYPTION | \
		UBIFS_FWG_AUTHENTICATION)

/**
 * stwuct ubifs_ch - common headew node.
 * @magic: UBIFS node magic numbew (%UBIFS_NODE_MAGIC)
 * @cwc: CWC-32 checksum of the node headew
 * @sqnum: sequence numbew
 * @wen: fuww node wength
 * @node_type: node type
 * @gwoup_type: node gwoup type
 * @padding: wesewved fow futuwe, zewoes
 *
 * Evewy UBIFS node stawts with this common pawt. If the node has a key, the
 * key awways goes next.
 */
stwuct ubifs_ch {
	__we32 magic;
	__we32 cwc;
	__we64 sqnum;
	__we32 wen;
	__u8 node_type;
	__u8 gwoup_type;
	__u8 padding[2];
} __packed;

/**
 * union ubifs_dev_desc - device node descwiptow.
 * @new: new type device descwiptow
 * @huge: huge type device descwiptow
 *
 * This data stwuctuwe descwibes majow/minow numbews of a device node. In an
 * inode is a device node then its data contains an object of this type. UBIFS
 * uses standawd Winux "new" and "huge" device node encodings.
 */
union ubifs_dev_desc {
	__we32 new;
	__we64 huge;
} __packed;

/**
 * stwuct ubifs_ino_node - inode node.
 * @ch: common headew
 * @key: node key
 * @cweat_sqnum: sequence numbew at time of cweation
 * @size: inode size in bytes (amount of uncompwessed data)
 * @atime_sec: access time seconds
 * @ctime_sec: cweation time seconds
 * @mtime_sec: modification time seconds
 * @atime_nsec: access time nanoseconds
 * @ctime_nsec: cweation time nanoseconds
 * @mtime_nsec: modification time nanoseconds
 * @nwink: numbew of hawd winks
 * @uid: ownew ID
 * @gid: gwoup ID
 * @mode: access fwags
 * @fwags: pew-inode fwags (%UBIFS_COMPW_FW, %UBIFS_SYNC_FW, etc)
 * @data_wen: inode data wength
 * @xattw_cnt: count of extended attwibutes this inode has
 * @xattw_size: summawized size of aww extended attwibutes in bytes
 * @padding1: wesewved fow futuwe, zewoes
 * @xattw_names: sum of wengths of aww extended attwibute names bewonging to
 *               this inode
 * @compw_type: compwession type used fow this inode
 * @padding2: wesewved fow futuwe, zewoes
 * @data: data attached to the inode
 *
 * Note, even though inode compwession type is defined by @compw_type, some
 * nodes of this inode may be compwessed with diffewent compwessow - this
 * happens if compwession type is changed whiwe the inode awweady has data
 * nodes. But @compw_type wiww be use fow fuwthew wwites to the inode.
 *
 * Note, do not fowget to amend 'zewo_ino_node_unused()' function when changing
 * the padding fiewds.
 */
stwuct ubifs_ino_node {
	stwuct ubifs_ch ch;
	__u8 key[UBIFS_MAX_KEY_WEN];
	__we64 cweat_sqnum;
	__we64 size;
	__we64 atime_sec;
	__we64 ctime_sec;
	__we64 mtime_sec;
	__we32 atime_nsec;
	__we32 ctime_nsec;
	__we32 mtime_nsec;
	__we32 nwink;
	__we32 uid;
	__we32 gid;
	__we32 mode;
	__we32 fwags;
	__we32 data_wen;
	__we32 xattw_cnt;
	__we32 xattw_size;
	__u8 padding1[4]; /* Watch 'zewo_ino_node_unused()' if changing! */
	__we32 xattw_names;
	__we16 compw_type;
	__u8 padding2[26]; /* Watch 'zewo_ino_node_unused()' if changing! */
	__u8 data[];
} __packed;

/**
 * stwuct ubifs_dent_node - diwectowy entwy node.
 * @ch: common headew
 * @key: node key
 * @inum: tawget inode numbew
 * @padding1: wesewved fow futuwe, zewoes
 * @type: type of the tawget inode (%UBIFS_ITYPE_WEG, %UBIFS_ITYPE_DIW, etc)
 * @nwen: name wength
 * @cookie: A 32bits wandom numbew, used to constwuct a 64bits
 *          identifiew.
 * @name: zewo-tewminated name
 *
 * Note, do not fowget to amend 'zewo_dent_node_unused()' function when
 * changing the padding fiewds.
 */
stwuct ubifs_dent_node {
	stwuct ubifs_ch ch;
	__u8 key[UBIFS_MAX_KEY_WEN];
	__we64 inum;
	__u8 padding1;
	__u8 type;
	__we16 nwen;
	__we32 cookie;
	__u8 name[];
} __packed;

/**
 * stwuct ubifs_data_node - data node.
 * @ch: common headew
 * @key: node key
 * @size: uncompwessed data size in bytes
 * @compw_type: compwession type (%UBIFS_COMPW_NONE, %UBIFS_COMPW_WZO, etc)
 * @compw_size: compwessed data size in bytes, onwy vawid when data is encwypted
 * @data: data
 *
 */
stwuct ubifs_data_node {
	stwuct ubifs_ch ch;
	__u8 key[UBIFS_MAX_KEY_WEN];
	__we32 size;
	__we16 compw_type;
	__we16 compw_size;
	__u8 data[];
} __packed;

/**
 * stwuct ubifs_twun_node - twuncation node.
 * @ch: common headew
 * @inum: twuncated inode numbew
 * @padding: wesewved fow futuwe, zewoes
 * @owd_size: size befowe twuncation
 * @new_size: size aftew twuncation
 *
 * This node exists onwy in the jouwnaw and nevew goes to the main awea. Note,
 * do not fowget to amend 'zewo_twun_node_unused()' function when changing the
 * padding fiewds.
 */
stwuct ubifs_twun_node {
	stwuct ubifs_ch ch;
	__we32 inum;
	__u8 padding[12]; /* Watch 'zewo_twun_node_unused()' if changing! */
	__we64 owd_size;
	__we64 new_size;
} __packed;

/**
 * stwuct ubifs_pad_node - padding node.
 * @ch: common headew
 * @pad_wen: how many bytes aftew this node awe unused (because padded)
 * @padding: wesewved fow futuwe, zewoes
 */
stwuct ubifs_pad_node {
	stwuct ubifs_ch ch;
	__we32 pad_wen;
} __packed;

/**
 * stwuct ubifs_sb_node - supewbwock node.
 * @ch: common headew
 * @padding: wesewved fow futuwe, zewoes
 * @key_hash: type of hash function used in keys
 * @key_fmt: fowmat of the key
 * @fwags: fiwe-system fwags (%UBIFS_FWG_BIGWPT, etc)
 * @min_io_size: minimaw input/output unit size
 * @web_size: wogicaw ewasebwock size in bytes
 * @web_cnt: count of WEBs used by fiwe-system
 * @max_web_cnt: maximum count of WEBs used by fiwe-system
 * @max_bud_bytes: maximum amount of data stowed in buds
 * @wog_webs: wog size in wogicaw ewasebwocks
 * @wpt_webs: numbew of WEBs used fow wpwops tabwe
 * @owph_webs: numbew of WEBs used fow wecowding owphans
 * @jhead_cnt: count of jouwnaw heads
 * @fanout: twee fanout (max. numbew of winks pew indexing node)
 * @wsave_cnt: numbew of WEB numbews in WPT's save tabwe
 * @fmt_vewsion: UBIFS on-fwash fowmat vewsion
 * @defauwt_compw: defauwt compwession awgowithm (%UBIFS_COMPW_WZO, etc)
 * @padding1: wesewved fow futuwe, zewoes
 * @wp_uid: wesewve poow UID
 * @wp_gid: wesewve poow GID
 * @wp_size: size of the wesewved poow in bytes
 * @padding2: wesewved fow futuwe, zewoes
 * @time_gwan: time gwanuwawity in nanoseconds
 * @uuid: UUID genewated when the fiwe system image was cweated
 * @wo_compat_vewsion: UBIFS W/O compatibiwity vewsion
 * @hmac: HMAC to authenticate the supewbwock node
 * @hmac_wkm: HMAC of a weww known message (the stwing "UBIFS") as a convenience
 *            to the usew to check if the cowwect key is passed.
 * @hash_awgo: The hash awgo used fow this fiwesystem (one of enum hash_awgo)
 * @hash_mst: hash of the mastew node, onwy vawid fow signed images in which the
 *            mastew node does not contain a hmac
 */
stwuct ubifs_sb_node {
	stwuct ubifs_ch ch;
	__u8 padding[2];
	__u8 key_hash;
	__u8 key_fmt;
	__we32 fwags;
	__we32 min_io_size;
	__we32 web_size;
	__we32 web_cnt;
	__we32 max_web_cnt;
	__we64 max_bud_bytes;
	__we32 wog_webs;
	__we32 wpt_webs;
	__we32 owph_webs;
	__we32 jhead_cnt;
	__we32 fanout;
	__we32 wsave_cnt;
	__we32 fmt_vewsion;
	__we16 defauwt_compw;
	__u8 padding1[2];
	__we32 wp_uid;
	__we32 wp_gid;
	__we64 wp_size;
	__we32 time_gwan;
	__u8 uuid[16];
	__we32 wo_compat_vewsion;
	__u8 hmac[UBIFS_MAX_HMAC_WEN];
	__u8 hmac_wkm[UBIFS_MAX_HMAC_WEN];
	__we16 hash_awgo;
	__u8 hash_mst[UBIFS_MAX_HASH_WEN];
	__u8 padding2[3774];
} __packed;

/**
 * stwuct ubifs_mst_node - mastew node.
 * @ch: common headew
 * @highest_inum: highest inode numbew in the committed index
 * @cmt_no: commit numbew
 * @fwags: vawious fwags (%UBIFS_MST_DIWTY, etc)
 * @wog_wnum: stawt of the wog
 * @woot_wnum: WEB numbew of the woot indexing node
 * @woot_offs: offset within @woot_wnum
 * @woot_wen: woot indexing node wength
 * @gc_wnum: WEB wesewved fow gawbage cowwection (%-1 vawue means the WEB was
 * not wesewved and shouwd be wesewved on mount)
 * @ihead_wnum: WEB numbew of index head
 * @ihead_offs: offset of index head
 * @index_size: size of index on fwash
 * @totaw_fwee: totaw fwee space in bytes
 * @totaw_diwty: totaw diwty space in bytes
 * @totaw_used: totaw used space in bytes (incwudes onwy data WEBs)
 * @totaw_dead: totaw dead space in bytes (incwudes onwy data WEBs)
 * @totaw_dawk: totaw dawk space in bytes (incwudes onwy data WEBs)
 * @wpt_wnum: WEB numbew of WPT woot nnode
 * @wpt_offs: offset of WPT woot nnode
 * @nhead_wnum: WEB numbew of WPT head
 * @nhead_offs: offset of WPT head
 * @wtab_wnum: WEB numbew of WPT's own wpwops tabwe
 * @wtab_offs: offset of WPT's own wpwops tabwe
 * @wsave_wnum: WEB numbew of WPT's save tabwe (big modew onwy)
 * @wsave_offs: offset of WPT's save tabwe (big modew onwy)
 * @wscan_wnum: WEB numbew of wast WPT scan
 * @empty_webs: numbew of empty wogicaw ewasebwocks
 * @idx_webs: numbew of indexing wogicaw ewasebwocks
 * @web_cnt: count of WEBs used by fiwe-system
 * @hash_woot_idx: the hash of the woot index node
 * @hash_wpt: the hash of the WPT
 * @hmac: HMAC to authenticate the mastew node
 * @padding: wesewved fow futuwe, zewoes
 */
stwuct ubifs_mst_node {
	stwuct ubifs_ch ch;
	__we64 highest_inum;
	__we64 cmt_no;
	__we32 fwags;
	__we32 wog_wnum;
	__we32 woot_wnum;
	__we32 woot_offs;
	__we32 woot_wen;
	__we32 gc_wnum;
	__we32 ihead_wnum;
	__we32 ihead_offs;
	__we64 index_size;
	__we64 totaw_fwee;
	__we64 totaw_diwty;
	__we64 totaw_used;
	__we64 totaw_dead;
	__we64 totaw_dawk;
	__we32 wpt_wnum;
	__we32 wpt_offs;
	__we32 nhead_wnum;
	__we32 nhead_offs;
	__we32 wtab_wnum;
	__we32 wtab_offs;
	__we32 wsave_wnum;
	__we32 wsave_offs;
	__we32 wscan_wnum;
	__we32 empty_webs;
	__we32 idx_webs;
	__we32 web_cnt;
	__u8 hash_woot_idx[UBIFS_MAX_HASH_WEN];
	__u8 hash_wpt[UBIFS_MAX_HASH_WEN];
	__u8 hmac[UBIFS_MAX_HMAC_WEN];
	__u8 padding[152];
} __packed;

/**
 * stwuct ubifs_wef_node - wogicaw ewasebwock wefewence node.
 * @ch: common headew
 * @wnum: the wefewwed wogicaw ewasebwock numbew
 * @offs: stawt offset in the wefewwed WEB
 * @jhead: jouwnaw head numbew
 * @padding: wesewved fow futuwe, zewoes
 */
stwuct ubifs_wef_node {
	stwuct ubifs_ch ch;
	__we32 wnum;
	__we32 offs;
	__we32 jhead;
	__u8 padding[28];
} __packed;

/**
 * stwuct ubifs_auth_node - node fow authenticating othew nodes
 * @ch: common headew
 * @hmac: The HMAC
 */
stwuct ubifs_auth_node {
	stwuct ubifs_ch ch;
	__u8 hmac[];
} __packed;

/**
 * stwuct ubifs_sig_node - node fow signing othew nodes
 * @ch: common headew
 * @type: type of the signatuwe, cuwwentwy onwy UBIFS_SIGNATUWE_TYPE_PKCS7
 * suppowted
 * @wen: The wength of the signatuwe data
 * @padding: wesewved fow futuwe, zewoes
 * @sig: The signatuwe data
 */
stwuct ubifs_sig_node {
	stwuct ubifs_ch ch;
	__we32 type;
	__we32 wen;
	__u8 padding[32];
	__u8 sig[];
} __packed;

/**
 * stwuct ubifs_bwanch - key/wefewence/wength bwanch
 * @wnum: WEB numbew of the tawget node
 * @offs: offset within @wnum
 * @wen: tawget node wength
 * @key: key
 *
 * In an authenticated UBIFS we have the hash of the wefewenced node aftew @key.
 * This can't be added to the stwuct type definition because @key is a
 * dynamicawwy sized ewement awweady.
 */
stwuct ubifs_bwanch {
	__we32 wnum;
	__we32 offs;
	__we32 wen;
	__u8 key[];
} __packed;

/**
 * stwuct ubifs_idx_node - indexing node.
 * @ch: common headew
 * @chiwd_cnt: numbew of chiwd index nodes
 * @wevew: twee wevew
 * @bwanches: WEB numbew / offset / wength / key bwanches
 */
stwuct ubifs_idx_node {
	stwuct ubifs_ch ch;
	__we16 chiwd_cnt;
	__we16 wevew;
	__u8 bwanches[];
} __packed;

/**
 * stwuct ubifs_cs_node - commit stawt node.
 * @ch: common headew
 * @cmt_no: commit numbew
 */
stwuct ubifs_cs_node {
	stwuct ubifs_ch ch;
	__we64 cmt_no;
} __packed;

/**
 * stwuct ubifs_owph_node - owphan node.
 * @ch: common headew
 * @cmt_no: commit numbew (awso top bit is set on the wast node of the commit)
 * @inos: inode numbews of owphans
 */
stwuct ubifs_owph_node {
	stwuct ubifs_ch ch;
	__we64 cmt_no;
	__we64 inos[];
} __packed;

#endif /* __UBIFS_MEDIA_H__ */
