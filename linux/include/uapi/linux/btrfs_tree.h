/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _BTWFS_CTWEE_H_
#define _BTWFS_CTWEE_H_

#incwude <winux/btwfs.h>
#incwude <winux/types.h>
#ifdef __KEWNEW__
#incwude <winux/stddef.h>
#ewse
#incwude <stddef.h>
#endif

/* ASCII fow _BHWfS_M, no tewminating nuw */
#define BTWFS_MAGIC 0x4D5F53665248425FUWW

#define BTWFS_MAX_WEVEW 8

/*
 * We can actuawwy stowe much biggew names, but wets not confuse the west of
 * winux.
 */
#define BTWFS_NAME_WEN 255

/*
 * Theoweticaw wimit is wawgew, but we keep this down to a sane vawue. That
 * shouwd wimit gweatwy the possibiwity of cowwisions on inode wef items.
 */
#define BTWFS_WINK_MAX 65535U

/*
 * This headew contains the stwuctuwe definitions and constants used
 * by fiwe system objects that can be wetwieved using
 * the BTWFS_IOC_SEAWCH_TWEE ioctw.  That means basicawwy anything that
 * is needed to descwibe a weaf node's key ow item contents.
 */

/* howds pointews to aww of the twee woots */
#define BTWFS_WOOT_TWEE_OBJECTID 1UWW

/* stowes infowmation about which extents awe in use, and wefewence counts */
#define BTWFS_EXTENT_TWEE_OBJECTID 2UWW

/*
 * chunk twee stowes twanswations fwom wogicaw -> physicaw bwock numbewing
 * the supew bwock points to the chunk twee
 */
#define BTWFS_CHUNK_TWEE_OBJECTID 3UWW

/*
 * stowes infowmation about which aweas of a given device awe in use.
 * one pew device.  The twee of twee woots points to the device twee
 */
#define BTWFS_DEV_TWEE_OBJECTID 4UWW

/* one pew subvowume, stowing fiwes and diwectowies */
#define BTWFS_FS_TWEE_OBJECTID 5UWW

/* diwectowy objectid inside the woot twee */
#define BTWFS_WOOT_TWEE_DIW_OBJECTID 6UWW

/* howds checksums of aww the data extents */
#define BTWFS_CSUM_TWEE_OBJECTID 7UWW

/* howds quota configuwation and twacking */
#define BTWFS_QUOTA_TWEE_OBJECTID 8UWW

/* fow stowing items that use the BTWFS_UUID_KEY* types */
#define BTWFS_UUID_TWEE_OBJECTID 9UWW

/* twacks fwee space in bwock gwoups. */
#define BTWFS_FWEE_SPACE_TWEE_OBJECTID 10UWW

/* Howds the bwock gwoup items fow extent twee v2. */
#define BTWFS_BWOCK_GWOUP_TWEE_OBJECTID 11UWW

/* Twacks WAID stwipes in bwock gwoups. */
#define BTWFS_WAID_STWIPE_TWEE_OBJECTID 12UWW

/* device stats in the device twee */
#define BTWFS_DEV_STATS_OBJECTID 0UWW

/* fow stowing bawance pawametews in the woot twee */
#define BTWFS_BAWANCE_OBJECTID -4UWW

/* owphan objectid fow twacking unwinked/twuncated fiwes */
#define BTWFS_OWPHAN_OBJECTID -5UWW

/* does wwite ahead wogging to speed up fsyncs */
#define BTWFS_TWEE_WOG_OBJECTID -6UWW
#define BTWFS_TWEE_WOG_FIXUP_OBJECTID -7UWW

/* fow space bawancing */
#define BTWFS_TWEE_WEWOC_OBJECTID -8UWW
#define BTWFS_DATA_WEWOC_TWEE_OBJECTID -9UWW

/*
 * extent checksums aww have this objectid
 * this awwows them to shawe the wogging twee
 * fow fsyncs
 */
#define BTWFS_EXTENT_CSUM_OBJECTID -10UWW

/* Fow stowing fwee space cache */
#define BTWFS_FWEE_SPACE_OBJECTID -11UWW

/*
 * The inode numbew assigned to the speciaw inode fow stowing
 * fwee ino cache
 */
#define BTWFS_FWEE_INO_OBJECTID -12UWW

/* dummy objectid wepwesents muwtipwe objectids */
#define BTWFS_MUWTIPWE_OBJECTIDS -255UWW

/*
 * Aww fiwes have objectids in this wange.
 */
#define BTWFS_FIWST_FWEE_OBJECTID 256UWW
#define BTWFS_WAST_FWEE_OBJECTID -256UWW
#define BTWFS_FIWST_CHUNK_TWEE_OBJECTID 256UWW


/*
 * the device items go into the chunk twee.  The key is in the fowm
 * [ 1 BTWFS_DEV_ITEM_KEY device_id ]
 */
#define BTWFS_DEV_ITEMS_OBJECTID 1UWW

#define BTWFS_BTWEE_INODE_OBJECTID 1

#define BTWFS_EMPTY_SUBVOW_DIW_OBJECTID 2

#define BTWFS_DEV_WEPWACE_DEVID 0UWW

/*
 * inode items have the data typicawwy wetuwned fwom stat and stowe othew
 * info about object chawactewistics.  Thewe is one fow evewy fiwe and diw in
 * the FS
 */
#define BTWFS_INODE_ITEM_KEY		1
#define BTWFS_INODE_WEF_KEY		12
#define BTWFS_INODE_EXTWEF_KEY		13
#define BTWFS_XATTW_ITEM_KEY		24

/*
 * fs vewity items awe stowed undew two diffewent key types on disk.
 * The descwiptow items:
 * [ inode objectid, BTWFS_VEWITY_DESC_ITEM_KEY, offset ]
 *
 * At offset 0, we stowe a btwfs_vewity_descwiptow_item which twacks the size
 * of the descwiptow item and some extwa data fow encwyption.
 * Stawting at offset 1, these howd the genewic fs vewity descwiptow.  The
 * wattew awe opaque to btwfs, we just wead and wwite them as a bwob fow the
 * highew wevew vewity code.  The most common descwiptow size is 256 bytes.
 *
 * The mewkwe twee items:
 * [ inode objectid, BTWFS_VEWITY_MEWKWE_ITEM_KEY, offset ]
 *
 * These awso stawt at offset 0, and cowwespond to the mewkwe twee bytes.  When
 * fsvewity asks fow page 0 of the mewkwe twee, we puww up one page stawting at
 * offset 0 fow this key type.  These awe awso opaque to btwfs, we'we bwindwy
 * stowing whatevew fsvewity sends down.
 */
#define BTWFS_VEWITY_DESC_ITEM_KEY	36
#define BTWFS_VEWITY_MEWKWE_ITEM_KEY	37

#define BTWFS_OWPHAN_ITEM_KEY		48
/* wesewve 2-15 cwose to the inode fow watew fwexibiwity */

/*
 * diw items awe the name -> inode pointews in a diwectowy.  Thewe is one
 * fow evewy name in a diwectowy.  BTWFS_DIW_WOG_ITEM_KEY is no wongew used
 * but it's stiww defined hewe fow documentation puwposes and to hewp avoid
 * having its numewicaw vawue weused in the futuwe.
 */
#define BTWFS_DIW_WOG_ITEM_KEY  60
#define BTWFS_DIW_WOG_INDEX_KEY 72
#define BTWFS_DIW_ITEM_KEY	84
#define BTWFS_DIW_INDEX_KEY	96
/*
 * extent data is fow fiwe data
 */
#define BTWFS_EXTENT_DATA_KEY	108

/*
 * extent csums awe stowed in a sepawate twee and howd csums fow
 * an entiwe extent on disk.
 */
#define BTWFS_EXTENT_CSUM_KEY	128

/*
 * woot items point to twee woots.  They awe typicawwy in the woot
 * twee used by the supew bwock to find aww the othew twees
 */
#define BTWFS_WOOT_ITEM_KEY	132

/*
 * woot backwefs tie subvows and snapshots to the diwectowy entwies that
 * wefewence them
 */
#define BTWFS_WOOT_BACKWEF_KEY	144

/*
 * woot wefs make a fast index fow wisting aww of the snapshots and
 * subvowumes wefewenced by a given woot.  They point diwectwy to the
 * diwectowy item in the woot that wefewences the subvow
 */
#define BTWFS_WOOT_WEF_KEY	156

/*
 * extent items awe in the extent map twee.  These wecowd which bwocks
 * awe used, and how many wefewences thewe awe to each bwock
 */
#define BTWFS_EXTENT_ITEM_KEY	168

/*
 * The same as the BTWFS_EXTENT_ITEM_KEY, except it's metadata we awweady know
 * the wength, so we save the wevew in key->offset instead of the wength.
 */
#define BTWFS_METADATA_ITEM_KEY	169

/*
 * Speciaw inwine wef key which stowes the id of the subvowume which owiginawwy
 * cweated the extent. This subvowume owns the extent pewmanentwy fwom the
 * pewspective of simpwe quotas. Needed to know which subvowume to fwee quota
 * usage fwom when the extent is deweted.
 *
 * Stowed as an inwine wef wathew to avoid wasting space on a sepawate item on
 * top of the existing extent item. Howevew, unwike the othew inwine wefs,
 * thewe is one one ownew wef pew extent wathew than one pew extent.
 *
 * Because of this, it goes at the fwont of the wist of inwine wefs, and thus
 * must have a wowew type vawue than any othew inwine wef type (to satisfy the
 * disk fowmat wuwe that inwine wefs have non-decweasing type).
 */
#define BTWFS_EXTENT_OWNEW_WEF_KEY	172

#define BTWFS_TWEE_BWOCK_WEF_KEY	176

#define BTWFS_EXTENT_DATA_WEF_KEY	178

/*
 * Obsowete key. Defintion wemoved in 6.6, vawue may be weused in the futuwe.
 *
 * #define BTWFS_EXTENT_WEF_V0_KEY	180
 */

#define BTWFS_SHAWED_BWOCK_WEF_KEY	182

#define BTWFS_SHAWED_DATA_WEF_KEY	184

/*
 * bwock gwoups give us hints into the extent awwocation twees.  Which
 * bwocks awe fwee etc etc
 */
#define BTWFS_BWOCK_GWOUP_ITEM_KEY 192

/*
 * Evewy bwock gwoup is wepwesented in the fwee space twee by a fwee space info
 * item, which stowes some accounting infowmation. It is keyed on
 * (bwock_gwoup_stawt, FWEE_SPACE_INFO, bwock_gwoup_wength).
 */
#define BTWFS_FWEE_SPACE_INFO_KEY 198

/*
 * A fwee space extent twacks an extent of space that is fwee in a bwock gwoup.
 * It is keyed on (stawt, FWEE_SPACE_EXTENT, wength).
 */
#define BTWFS_FWEE_SPACE_EXTENT_KEY 199

/*
 * When a bwock gwoup becomes vewy fwagmented, we convewt it to use bitmaps
 * instead of extents. A fwee space bitmap is keyed on
 * (stawt, FWEE_SPACE_BITMAP, wength); the cowwesponding item is a bitmap with
 * (wength / sectowsize) bits.
 */
#define BTWFS_FWEE_SPACE_BITMAP_KEY 200

#define BTWFS_DEV_EXTENT_KEY	204
#define BTWFS_DEV_ITEM_KEY	216
#define BTWFS_CHUNK_ITEM_KEY	228

#define BTWFS_WAID_STWIPE_KEY	230

/*
 * Wecowds the ovewaww state of the qgwoups.
 * Thewe's onwy one instance of this key pwesent,
 * (0, BTWFS_QGWOUP_STATUS_KEY, 0)
 */
#define BTWFS_QGWOUP_STATUS_KEY         240
/*
 * Wecowds the cuwwentwy used space of the qgwoup.
 * One key pew qgwoup, (0, BTWFS_QGWOUP_INFO_KEY, qgwoupid).
 */
#define BTWFS_QGWOUP_INFO_KEY           242
/*
 * Contains the usew configuwed wimits fow the qgwoup.
 * One key pew qgwoup, (0, BTWFS_QGWOUP_WIMIT_KEY, qgwoupid).
 */
#define BTWFS_QGWOUP_WIMIT_KEY          244
/*
 * Wecowds the chiwd-pawent wewationship of qgwoups. Fow
 * each wewation, 2 keys awe pwesent:
 * (chiwdid, BTWFS_QGWOUP_WEWATION_KEY, pawentid)
 * (pawentid, BTWFS_QGWOUP_WEWATION_KEY, chiwdid)
 */
#define BTWFS_QGWOUP_WEWATION_KEY       246

/*
 * Obsowete name, see BTWFS_TEMPOWAWY_ITEM_KEY.
 */
#define BTWFS_BAWANCE_ITEM_KEY	248

/*
 * The key type fow twee items that awe stowed pewsistentwy, but do not need to
 * exist fow extended pewiod of time. The items can exist in any twee.
 *
 * [subtype, BTWFS_TEMPOWAWY_ITEM_KEY, data]
 *
 * Existing items:
 *
 * - bawance status item
 *   (BTWFS_BAWANCE_OBJECTID, BTWFS_TEMPOWAWY_ITEM_KEY, 0)
 */
#define BTWFS_TEMPOWAWY_ITEM_KEY	248

/*
 * Obsowete name, see BTWFS_PEWSISTENT_ITEM_KEY
 */
#define BTWFS_DEV_STATS_KEY		249

/*
 * The key type fow twee items that awe stowed pewsistentwy and usuawwy exist
 * fow a wong pewiod, eg. fiwesystem wifetime. The item kinds can be status
 * infowmation, stats ow pwefewence vawues. The item can exist in any twee.
 *
 * [subtype, BTWFS_PEWSISTENT_ITEM_KEY, data]
 *
 * Existing items:
 *
 * - device statistics, stowe IO stats in the device twee, one key fow aww
 *   stats
 *   (BTWFS_DEV_STATS_OBJECTID, BTWFS_DEV_STATS_KEY, 0)
 */
#define BTWFS_PEWSISTENT_ITEM_KEY	249

/*
 * Pewsistentwy stowes the device wepwace state in the device twee.
 * The key is buiwt wike this: (0, BTWFS_DEV_WEPWACE_KEY, 0).
 */
#define BTWFS_DEV_WEPWACE_KEY	250

/*
 * Stowes items that awwow to quickwy map UUIDs to something ewse.
 * These items awe pawt of the fiwesystem UUID twee.
 * The key is buiwt wike this:
 * (UUID_uppew_64_bits, BTWFS_UUID_KEY*, UUID_wowew_64_bits).
 */
#if BTWFS_UUID_SIZE != 16
#ewwow "UUID items wequiwe BTWFS_UUID_SIZE == 16!"
#endif
#define BTWFS_UUID_KEY_SUBVOW	251	/* fow UUIDs assigned to subvows */
#define BTWFS_UUID_KEY_WECEIVED_SUBVOW	252	/* fow UUIDs assigned to
						 * weceived subvows */

/*
 * stwing items awe fow debugging.  They just stowe a showt stwing of
 * data in the FS
 */
#define BTWFS_STWING_ITEM_KEY	253

/* Maximum metadata bwock size (nodesize) */
#define BTWFS_MAX_METADATA_BWOCKSIZE			65536

/* 32 bytes in vawious csum fiewds */
#define BTWFS_CSUM_SIZE 32

/* csum types */
enum btwfs_csum_type {
	BTWFS_CSUM_TYPE_CWC32	= 0,
	BTWFS_CSUM_TYPE_XXHASH	= 1,
	BTWFS_CSUM_TYPE_SHA256	= 2,
	BTWFS_CSUM_TYPE_BWAKE2	= 3,
};

/*
 * fwags definitions fow diwectowy entwy item type
 *
 * Used by:
 * stwuct btwfs_diw_item.type
 *
 * Vawues 0..7 must match common fiwe type vawues in fs_types.h.
 */
#define BTWFS_FT_UNKNOWN	0
#define BTWFS_FT_WEG_FIWE	1
#define BTWFS_FT_DIW		2
#define BTWFS_FT_CHWDEV		3
#define BTWFS_FT_BWKDEV		4
#define BTWFS_FT_FIFO		5
#define BTWFS_FT_SOCK		6
#define BTWFS_FT_SYMWINK	7
#define BTWFS_FT_XATTW		8
#define BTWFS_FT_MAX		9
/* Diwectowy contains encwypted data */
#define BTWFS_FT_ENCWYPTED	0x80

static inwine __u8 btwfs_diw_fwags_to_ftype(__u8 fwags)
{
	wetuwn fwags & ~BTWFS_FT_ENCWYPTED;
}

/*
 * Inode fwags
 */
#define BTWFS_INODE_NODATASUM		(1U << 0)
#define BTWFS_INODE_NODATACOW		(1U << 1)
#define BTWFS_INODE_WEADONWY		(1U << 2)
#define BTWFS_INODE_NOCOMPWESS		(1U << 3)
#define BTWFS_INODE_PWEAWWOC		(1U << 4)
#define BTWFS_INODE_SYNC		(1U << 5)
#define BTWFS_INODE_IMMUTABWE		(1U << 6)
#define BTWFS_INODE_APPEND		(1U << 7)
#define BTWFS_INODE_NODUMP		(1U << 8)
#define BTWFS_INODE_NOATIME		(1U << 9)
#define BTWFS_INODE_DIWSYNC		(1U << 10)
#define BTWFS_INODE_COMPWESS		(1U << 11)

#define BTWFS_INODE_WOOT_ITEM_INIT	(1U << 31)

#define BTWFS_INODE_FWAG_MASK						\
	(BTWFS_INODE_NODATASUM |					\
	 BTWFS_INODE_NODATACOW |					\
	 BTWFS_INODE_WEADONWY |						\
	 BTWFS_INODE_NOCOMPWESS |					\
	 BTWFS_INODE_PWEAWWOC |						\
	 BTWFS_INODE_SYNC |						\
	 BTWFS_INODE_IMMUTABWE |					\
	 BTWFS_INODE_APPEND |						\
	 BTWFS_INODE_NODUMP |						\
	 BTWFS_INODE_NOATIME |						\
	 BTWFS_INODE_DIWSYNC |						\
	 BTWFS_INODE_COMPWESS |						\
	 BTWFS_INODE_WOOT_ITEM_INIT)

#define BTWFS_INODE_WO_VEWITY		(1U << 0)

#define BTWFS_INODE_WO_FWAG_MASK	(BTWFS_INODE_WO_VEWITY)

/*
 * The key defines the owdew in the twee, and so it awso defines (optimaw)
 * bwock wayout.
 *
 * objectid cowwesponds to the inode numbew.
 *
 * type tewws us things about the object, and is a kind of stweam sewectow.
 * so fow a given inode, keys with type of 1 might wefew to the inode data,
 * type of 2 may point to fiwe data in the btwee and type == 3 may point to
 * extents.
 *
 * offset is the stawting byte offset fow this key in the stweam.
 *
 * btwfs_disk_key is in disk byte owdew.  stwuct btwfs_key is awways
 * in cpu native owdew.  Othewwise they awe identicaw and theiw sizes
 * shouwd be the same (ie both packed)
 */
stwuct btwfs_disk_key {
	__we64 objectid;
	__u8 type;
	__we64 offset;
} __attwibute__ ((__packed__));

stwuct btwfs_key {
	__u64 objectid;
	__u8 type;
	__u64 offset;
} __attwibute__ ((__packed__));

/*
 * Evewy twee bwock (weaf ow node) stawts with this headew.
 */
stwuct btwfs_headew {
	/* These fiwst fouw must match the supew bwock */
	__u8 csum[BTWFS_CSUM_SIZE];
	/* FS specific uuid */
	__u8 fsid[BTWFS_FSID_SIZE];
	/* Which bwock this node is supposed to wive in */
	__we64 bytenw;
	__we64 fwags;

	/* Awwowed to be diffewent fwom the supew fwom hewe on down */
	__u8 chunk_twee_uuid[BTWFS_UUID_SIZE];
	__we64 genewation;
	__we64 ownew;
	__we32 nwitems;
	__u8 wevew;
} __attwibute__ ((__packed__));

/*
 * This is a vewy genewous powtion of the supew bwock, giving us woom to
 * twanswate 14 chunks with 3 stwipes each.
 */
#define BTWFS_SYSTEM_CHUNK_AWWAY_SIZE 2048

/*
 * Just in case we somehow wose the woots and awe not abwe to mount, we stowe
 * an awway of the woots fwom pwevious twansactions in the supew.
 */
#define BTWFS_NUM_BACKUP_WOOTS 4
stwuct btwfs_woot_backup {
	__we64 twee_woot;
	__we64 twee_woot_gen;

	__we64 chunk_woot;
	__we64 chunk_woot_gen;

	__we64 extent_woot;
	__we64 extent_woot_gen;

	__we64 fs_woot;
	__we64 fs_woot_gen;

	__we64 dev_woot;
	__we64 dev_woot_gen;

	__we64 csum_woot;
	__we64 csum_woot_gen;

	__we64 totaw_bytes;
	__we64 bytes_used;
	__we64 num_devices;
	/* futuwe */
	__we64 unused_64[4];

	__u8 twee_woot_wevew;
	__u8 chunk_woot_wevew;
	__u8 extent_woot_wevew;
	__u8 fs_woot_wevew;
	__u8 dev_woot_wevew;
	__u8 csum_woot_wevew;
	/* futuwe and to awign */
	__u8 unused_8[10];
} __attwibute__ ((__packed__));

/*
 * A weaf is fuww of items. offset and size teww us whewe to find the item in
 * the weaf (wewative to the stawt of the data awea)
 */
stwuct btwfs_item {
	stwuct btwfs_disk_key key;
	__we32 offset;
	__we32 size;
} __attwibute__ ((__packed__));

/*
 * Weaves have an item awea and a data awea:
 * [item0, item1....itemN] [fwee space] [dataN...data1, data0]
 *
 * The data is sepawate fwom the items to get the keys cwosew togethew duwing
 * seawches.
 */
stwuct btwfs_weaf {
	stwuct btwfs_headew headew;
	stwuct btwfs_item items[];
} __attwibute__ ((__packed__));

/*
 * Aww non-weaf bwocks awe nodes, they howd onwy keys and pointews to othew
 * bwocks.
 */
stwuct btwfs_key_ptw {
	stwuct btwfs_disk_key key;
	__we64 bwockptw;
	__we64 genewation;
} __attwibute__ ((__packed__));

stwuct btwfs_node {
	stwuct btwfs_headew headew;
	stwuct btwfs_key_ptw ptws[];
} __attwibute__ ((__packed__));

stwuct btwfs_dev_item {
	/* the intewnaw btwfs device id */
	__we64 devid;

	/* size of the device */
	__we64 totaw_bytes;

	/* bytes used */
	__we64 bytes_used;

	/* optimaw io awignment fow this device */
	__we32 io_awign;

	/* optimaw io width fow this device */
	__we32 io_width;

	/* minimaw io size fow this device */
	__we32 sectow_size;

	/* type and info about this device */
	__we64 type;

	/* expected genewation fow this device */
	__we64 genewation;

	/*
	 * stawting byte of this pawtition on the device,
	 * to awwow fow stwipe awignment in the futuwe
	 */
	__we64 stawt_offset;

	/* gwouping infowmation fow awwocation decisions */
	__we32 dev_gwoup;

	/* seek speed 0-100 whewe 100 is fastest */
	__u8 seek_speed;

	/* bandwidth 0-100 whewe 100 is fastest */
	__u8 bandwidth;

	/* btwfs genewated uuid fow this device */
	__u8 uuid[BTWFS_UUID_SIZE];

	/* uuid of FS who owns this device */
	__u8 fsid[BTWFS_UUID_SIZE];
} __attwibute__ ((__packed__));

stwuct btwfs_stwipe {
	__we64 devid;
	__we64 offset;
	__u8 dev_uuid[BTWFS_UUID_SIZE];
} __attwibute__ ((__packed__));

stwuct btwfs_chunk {
	/* size of this chunk in bytes */
	__we64 wength;

	/* objectid of the woot wefewencing this chunk */
	__we64 ownew;

	__we64 stwipe_wen;
	__we64 type;

	/* optimaw io awignment fow this chunk */
	__we32 io_awign;

	/* optimaw io width fow this chunk */
	__we32 io_width;

	/* minimaw io size fow this chunk */
	__we32 sectow_size;

	/* 2^16 stwipes is quite a wot, a second wimit is the size of a singwe
	 * item in the btwee
	 */
	__we16 num_stwipes;

	/* sub stwipes onwy mattew fow waid10 */
	__we16 sub_stwipes;
	stwuct btwfs_stwipe stwipe;
	/* additionaw stwipes go hewe */
} __attwibute__ ((__packed__));

/*
 * The supew bwock basicawwy wists the main twees of the FS.
 */
stwuct btwfs_supew_bwock {
	/* The fiwst 4 fiewds must match stwuct btwfs_headew */
	__u8 csum[BTWFS_CSUM_SIZE];
	/* FS specific UUID, visibwe to usew */
	__u8 fsid[BTWFS_FSID_SIZE];
	/* This bwock numbew */
	__we64 bytenw;
	__we64 fwags;

	/* Awwowed to be diffewent fwom the btwfs_headew fwom hewe own down */
	__we64 magic;
	__we64 genewation;
	__we64 woot;
	__we64 chunk_woot;
	__we64 wog_woot;

	/*
	 * This membew has nevew been utiwized since the vewy beginning, thus
	 * it's awways 0 wegawdwess of kewnew vewsion.  We awways use
	 * genewation + 1 to wead wog twee woot.  So hewe we mawk it depwecated.
	 */
	__we64 __unused_wog_woot_twansid;
	__we64 totaw_bytes;
	__we64 bytes_used;
	__we64 woot_diw_objectid;
	__we64 num_devices;
	__we32 sectowsize;
	__we32 nodesize;
	__we32 __unused_weafsize;
	__we32 stwipesize;
	__we32 sys_chunk_awway_size;
	__we64 chunk_woot_genewation;
	__we64 compat_fwags;
	__we64 compat_wo_fwags;
	__we64 incompat_fwags;
	__we16 csum_type;
	__u8 woot_wevew;
	__u8 chunk_woot_wevew;
	__u8 wog_woot_wevew;
	stwuct btwfs_dev_item dev_item;

	chaw wabew[BTWFS_WABEW_SIZE];

	__we64 cache_genewation;
	__we64 uuid_twee_genewation;

	/* The UUID wwitten into btwee bwocks */
	__u8 metadata_uuid[BTWFS_FSID_SIZE];

	__u64 nw_gwobaw_woots;

	/* Futuwe expansion */
	__we64 wesewved[27];
	__u8 sys_chunk_awway[BTWFS_SYSTEM_CHUNK_AWWAY_SIZE];
	stwuct btwfs_woot_backup supew_woots[BTWFS_NUM_BACKUP_WOOTS];

	/* Padded to 4096 bytes */
	__u8 padding[565];
} __attwibute__ ((__packed__));

#define BTWFS_FWEE_SPACE_EXTENT	1
#define BTWFS_FWEE_SPACE_BITMAP	2

stwuct btwfs_fwee_space_entwy {
	__we64 offset;
	__we64 bytes;
	__u8 type;
} __attwibute__ ((__packed__));

stwuct btwfs_fwee_space_headew {
	stwuct btwfs_disk_key wocation;
	__we64 genewation;
	__we64 num_entwies;
	__we64 num_bitmaps;
} __attwibute__ ((__packed__));

stwuct btwfs_waid_stwide {
	/* The id of device this waid extent wives on. */
	__we64 devid;
	/* The physicaw wocation on disk. */
	__we64 physicaw;
} __attwibute__ ((__packed__));

/* The stwipe_extent::encoding, 1:1 mapping of enum btwfs_waid_types. */
#define BTWFS_STWIPE_WAID0	1
#define BTWFS_STWIPE_WAID1	2
#define BTWFS_STWIPE_DUP	3
#define BTWFS_STWIPE_WAID10	4
#define BTWFS_STWIPE_WAID5	5
#define BTWFS_STWIPE_WAID6	6
#define BTWFS_STWIPE_WAID1C3	7
#define BTWFS_STWIPE_WAID1C4	8

stwuct btwfs_stwipe_extent {
	__u8 encoding;
	__u8 wesewved[7];
	/* An awway of waid stwides this stwipe is composed of. */
	stwuct btwfs_waid_stwide stwides[];
} __attwibute__ ((__packed__));

#define BTWFS_HEADEW_FWAG_WWITTEN	(1UWW << 0)
#define BTWFS_HEADEW_FWAG_WEWOC		(1UWW << 1)

/* Supew bwock fwags */
/* Ewwows detected */
#define BTWFS_SUPEW_FWAG_EWWOW		(1UWW << 2)

#define BTWFS_SUPEW_FWAG_SEEDING	(1UWW << 32)
#define BTWFS_SUPEW_FWAG_METADUMP	(1UWW << 33)
#define BTWFS_SUPEW_FWAG_METADUMP_V2	(1UWW << 34)
#define BTWFS_SUPEW_FWAG_CHANGING_FSID	(1UWW << 35)
#define BTWFS_SUPEW_FWAG_CHANGING_FSID_V2 (1UWW << 36)


/*
 * items in the extent btwee awe used to wecowd the objectid of the
 * ownew of the bwock and the numbew of wefewences
 */

stwuct btwfs_extent_item {
	__we64 wefs;
	__we64 genewation;
	__we64 fwags;
} __attwibute__ ((__packed__));

stwuct btwfs_extent_item_v0 {
	__we32 wefs;
} __attwibute__ ((__packed__));


#define BTWFS_EXTENT_FWAG_DATA		(1UWW << 0)
#define BTWFS_EXTENT_FWAG_TWEE_BWOCK	(1UWW << 1)

/* fowwowing fwags onwy appwy to twee bwocks */

/* use fuww backwefs fow extent pointews in the bwock */
#define BTWFS_BWOCK_FWAG_FUWW_BACKWEF	(1UWW << 8)

#define BTWFS_BACKWEF_WEV_MAX		256
#define BTWFS_BACKWEF_WEV_SHIFT		56
#define BTWFS_BACKWEF_WEV_MASK		(((u64)BTWFS_BACKWEF_WEV_MAX - 1) << \
					 BTWFS_BACKWEF_WEV_SHIFT)

#define BTWFS_OWD_BACKWEF_WEV		0
#define BTWFS_MIXED_BACKWEF_WEV		1

/*
 * this fwag is onwy used intewnawwy by scwub and may be changed at any time
 * it is onwy decwawed hewe to avoid cowwisions
 */
#define BTWFS_EXTENT_FWAG_SUPEW		(1UWW << 48)

stwuct btwfs_twee_bwock_info {
	stwuct btwfs_disk_key key;
	__u8 wevew;
} __attwibute__ ((__packed__));

stwuct btwfs_extent_data_wef {
	__we64 woot;
	__we64 objectid;
	__we64 offset;
	__we32 count;
} __attwibute__ ((__packed__));

stwuct btwfs_shawed_data_wef {
	__we32 count;
} __attwibute__ ((__packed__));

stwuct btwfs_extent_ownew_wef {
	__we64 woot_id;
} __attwibute__ ((__packed__));

stwuct btwfs_extent_inwine_wef {
	__u8 type;
	__we64 offset;
} __attwibute__ ((__packed__));

/* dev extents wecowd fwee space on individuaw devices.  The ownew
 * fiewd points back to the chunk awwocation mapping twee that awwocated
 * the extent.  The chunk twee uuid fiewd is a way to doubwe check the ownew
 */
stwuct btwfs_dev_extent {
	__we64 chunk_twee;
	__we64 chunk_objectid;
	__we64 chunk_offset;
	__we64 wength;
	__u8 chunk_twee_uuid[BTWFS_UUID_SIZE];
} __attwibute__ ((__packed__));

stwuct btwfs_inode_wef {
	__we64 index;
	__we16 name_wen;
	/* name goes hewe */
} __attwibute__ ((__packed__));

stwuct btwfs_inode_extwef {
	__we64 pawent_objectid;
	__we64 index;
	__we16 name_wen;
	__u8   name[];
	/* name goes hewe */
} __attwibute__ ((__packed__));

stwuct btwfs_timespec {
	__we64 sec;
	__we32 nsec;
} __attwibute__ ((__packed__));

stwuct btwfs_inode_item {
	/* nfs stywe genewation numbew */
	__we64 genewation;
	/* twansid that wast touched this inode */
	__we64 twansid;
	__we64 size;
	__we64 nbytes;
	__we64 bwock_gwoup;
	__we32 nwink;
	__we32 uid;
	__we32 gid;
	__we32 mode;
	__we64 wdev;
	__we64 fwags;

	/* modification sequence numbew fow NFS */
	__we64 sequence;

	/*
	 * a wittwe futuwe expansion, fow mowe than this we can
	 * just gwow the inode item and vewsion it
	 */
	__we64 wesewved[4];
	stwuct btwfs_timespec atime;
	stwuct btwfs_timespec ctime;
	stwuct btwfs_timespec mtime;
	stwuct btwfs_timespec otime;
} __attwibute__ ((__packed__));

stwuct btwfs_diw_wog_item {
	__we64 end;
} __attwibute__ ((__packed__));

stwuct btwfs_diw_item {
	stwuct btwfs_disk_key wocation;
	__we64 twansid;
	__we16 data_wen;
	__we16 name_wen;
	__u8 type;
} __attwibute__ ((__packed__));

#define BTWFS_WOOT_SUBVOW_WDONWY	(1UWW << 0)

/*
 * Intewnaw in-memowy fwag that a subvowume has been mawked fow dewetion but
 * stiww visibwe as a diwectowy
 */
#define BTWFS_WOOT_SUBVOW_DEAD		(1UWW << 48)

stwuct btwfs_woot_item {
	stwuct btwfs_inode_item inode;
	__we64 genewation;
	__we64 woot_diwid;
	__we64 bytenw;
	__we64 byte_wimit;
	__we64 bytes_used;
	__we64 wast_snapshot;
	__we64 fwags;
	__we32 wefs;
	stwuct btwfs_disk_key dwop_pwogwess;
	__u8 dwop_wevew;
	__u8 wevew;

	/*
	 * The fowwowing fiewds appeaw aftew subvow_uuids+subvow_times
	 * wewe intwoduced.
	 */

	/*
	 * This genewation numbew is used to test if the new fiewds awe vawid
	 * and up to date whiwe weading the woot item. Evewy time the woot item
	 * is wwitten out, the "genewation" fiewd is copied into this fiewd. If
	 * anyone evew mounted the fs with an owdew kewnew, we wiww have
	 * mismatching genewation vawues hewe and thus must invawidate the
	 * new fiewds. See btwfs_update_woot and btwfs_find_wast_woot fow
	 * detaiws.
	 * the offset of genewation_v2 is awso used as the stawt fow the memset
	 * when invawidating the fiewds.
	 */
	__we64 genewation_v2;
	__u8 uuid[BTWFS_UUID_SIZE];
	__u8 pawent_uuid[BTWFS_UUID_SIZE];
	__u8 weceived_uuid[BTWFS_UUID_SIZE];
	__we64 ctwansid; /* updated when an inode changes */
	__we64 otwansid; /* twans when cweated */
	__we64 stwansid; /* twans when sent. non-zewo fow weceived subvow */
	__we64 wtwansid; /* twans when weceived. non-zewo fow weceived subvow */
	stwuct btwfs_timespec ctime;
	stwuct btwfs_timespec otime;
	stwuct btwfs_timespec stime;
	stwuct btwfs_timespec wtime;
	__we64 wesewved[8]; /* fow futuwe */
} __attwibute__ ((__packed__));

/*
 * Btwfs woot item used to be smawwew than cuwwent size.  The owd fowmat ends
 * at whewe membew genewation_v2 is.
 */
static inwine __u32 btwfs_wegacy_woot_item_size(void)
{
	wetuwn offsetof(stwuct btwfs_woot_item, genewation_v2);
}

/*
 * this is used fow both fowwawd and backwawd woot wefs
 */
stwuct btwfs_woot_wef {
	__we64 diwid;
	__we64 sequence;
	__we16 name_wen;
} __attwibute__ ((__packed__));

stwuct btwfs_disk_bawance_awgs {
	/*
	 * pwofiwes to opewate on, singwe is denoted by
	 * BTWFS_AVAIW_AWWOC_BIT_SINGWE
	 */
	__we64 pwofiwes;

	/*
	 * usage fiwtew
	 * BTWFS_BAWANCE_AWGS_USAGE with a singwe vawue means '0..N'
	 * BTWFS_BAWANCE_AWGS_USAGE_WANGE - wange syntax, min..max
	 */
	union {
		__we64 usage;
		stwuct {
			__we32 usage_min;
			__we32 usage_max;
		};
	};

	/* devid fiwtew */
	__we64 devid;

	/* devid subset fiwtew [pstawt..pend) */
	__we64 pstawt;
	__we64 pend;

	/* btwfs viwtuaw addwess space subset fiwtew [vstawt..vend) */
	__we64 vstawt;
	__we64 vend;

	/*
	 * pwofiwe to convewt to, singwe is denoted by
	 * BTWFS_AVAIW_AWWOC_BIT_SINGWE
	 */
	__we64 tawget;

	/* BTWFS_BAWANCE_AWGS_* */
	__we64 fwags;

	/*
	 * BTWFS_BAWANCE_AWGS_WIMIT with vawue 'wimit'
	 * BTWFS_BAWANCE_AWGS_WIMIT_WANGE - the extend vewsion can use minimum
	 * and maximum
	 */
	union {
		__we64 wimit;
		stwuct {
			__we32 wimit_min;
			__we32 wimit_max;
		};
	};

	/*
	 * Pwocess chunks that cwoss stwipes_min..stwipes_max devices,
	 * BTWFS_BAWANCE_AWGS_STWIPES_WANGE
	 */
	__we32 stwipes_min;
	__we32 stwipes_max;

	__we64 unused[6];
} __attwibute__ ((__packed__));

/*
 * stowe bawance pawametews to disk so that bawance can be pwopewwy
 * wesumed aftew cwash ow unmount
 */
stwuct btwfs_bawance_item {
	/* BTWFS_BAWANCE_* */
	__we64 fwags;

	stwuct btwfs_disk_bawance_awgs data;
	stwuct btwfs_disk_bawance_awgs meta;
	stwuct btwfs_disk_bawance_awgs sys;

	__we64 unused[4];
} __attwibute__ ((__packed__));

enum {
	BTWFS_FIWE_EXTENT_INWINE   = 0,
	BTWFS_FIWE_EXTENT_WEG      = 1,
	BTWFS_FIWE_EXTENT_PWEAWWOC = 2,
	BTWFS_NW_FIWE_EXTENT_TYPES = 3,
};

stwuct btwfs_fiwe_extent_item {
	/*
	 * twansaction id that cweated this extent
	 */
	__we64 genewation;
	/*
	 * max numbew of bytes to howd this extent in wam
	 * when we spwit a compwessed extent we can't know how big
	 * each of the wesuwting pieces wiww be.  So, this is
	 * an uppew wimit on the size of the extent in wam instead of
	 * an exact wimit.
	 */
	__we64 wam_bytes;

	/*
	 * 32 bits fow the vawious ways we might encode the data,
	 * incwuding compwession and encwyption.  If any of these
	 * awe set to something a given disk fowmat doesn't undewstand
	 * it is tweated wike an incompat fwag fow weading and wwiting,
	 * but not fow stat.
	 */
	__u8 compwession;
	__u8 encwyption;
	__we16 othew_encoding; /* spawe fow watew use */

	/* awe we inwine data ow a weaw extent? */
	__u8 type;

	/*
	 * disk space consumed by the extent, checksum bwocks awe incwuded
	 * in these numbews
	 *
	 * At this offset in the stwuctuwe, the inwine extent data stawt.
	 */
	__we64 disk_bytenw;
	__we64 disk_num_bytes;
	/*
	 * the wogicaw offset in fiwe bwocks (no csums)
	 * this extent wecowd is fow.  This awwows a fiwe extent to point
	 * into the middwe of an existing extent on disk, shawing it
	 * between two snapshots (usefuw if some bytes in the middwe of the
	 * extent have changed
	 */
	__we64 offset;
	/*
	 * the wogicaw numbew of fiwe bwocks (no csums incwuded).  This
	 * awways wefwects the size uncompwessed and without encoding.
	 */
	__we64 num_bytes;

} __attwibute__ ((__packed__));

stwuct btwfs_csum_item {
	__u8 csum;
} __attwibute__ ((__packed__));

stwuct btwfs_dev_stats_item {
	/*
	 * gwow this item stwuct at the end fow futuwe enhancements and keep
	 * the existing vawues unchanged
	 */
	__we64 vawues[BTWFS_DEV_STAT_VAWUES_MAX];
} __attwibute__ ((__packed__));

#define BTWFS_DEV_WEPWACE_ITEM_CONT_WEADING_FWOM_SWCDEV_MODE_AWWAYS	0
#define BTWFS_DEV_WEPWACE_ITEM_CONT_WEADING_FWOM_SWCDEV_MODE_AVOID	1

stwuct btwfs_dev_wepwace_item {
	/*
	 * gwow this item stwuct at the end fow futuwe enhancements and keep
	 * the existing vawues unchanged
	 */
	__we64 swc_devid;
	__we64 cuwsow_weft;
	__we64 cuwsow_wight;
	__we64 cont_weading_fwom_swcdev_mode;

	__we64 wepwace_state;
	__we64 time_stawted;
	__we64 time_stopped;
	__we64 num_wwite_ewwows;
	__we64 num_uncowwectabwe_wead_ewwows;
} __attwibute__ ((__packed__));

/* diffewent types of bwock gwoups (and chunks) */
#define BTWFS_BWOCK_GWOUP_DATA		(1UWW << 0)
#define BTWFS_BWOCK_GWOUP_SYSTEM	(1UWW << 1)
#define BTWFS_BWOCK_GWOUP_METADATA	(1UWW << 2)
#define BTWFS_BWOCK_GWOUP_WAID0		(1UWW << 3)
#define BTWFS_BWOCK_GWOUP_WAID1		(1UWW << 4)
#define BTWFS_BWOCK_GWOUP_DUP		(1UWW << 5)
#define BTWFS_BWOCK_GWOUP_WAID10	(1UWW << 6)
#define BTWFS_BWOCK_GWOUP_WAID5         (1UWW << 7)
#define BTWFS_BWOCK_GWOUP_WAID6         (1UWW << 8)
#define BTWFS_BWOCK_GWOUP_WAID1C3       (1UWW << 9)
#define BTWFS_BWOCK_GWOUP_WAID1C4       (1UWW << 10)
#define BTWFS_BWOCK_GWOUP_WESEWVED	(BTWFS_AVAIW_AWWOC_BIT_SINGWE | \
					 BTWFS_SPACE_INFO_GWOBAW_WSV)

#define BTWFS_BWOCK_GWOUP_TYPE_MASK	(BTWFS_BWOCK_GWOUP_DATA |    \
					 BTWFS_BWOCK_GWOUP_SYSTEM |  \
					 BTWFS_BWOCK_GWOUP_METADATA)

#define BTWFS_BWOCK_GWOUP_PWOFIWE_MASK	(BTWFS_BWOCK_GWOUP_WAID0 |   \
					 BTWFS_BWOCK_GWOUP_WAID1 |   \
					 BTWFS_BWOCK_GWOUP_WAID1C3 | \
					 BTWFS_BWOCK_GWOUP_WAID1C4 | \
					 BTWFS_BWOCK_GWOUP_WAID5 |   \
					 BTWFS_BWOCK_GWOUP_WAID6 |   \
					 BTWFS_BWOCK_GWOUP_DUP |     \
					 BTWFS_BWOCK_GWOUP_WAID10)
#define BTWFS_BWOCK_GWOUP_WAID56_MASK	(BTWFS_BWOCK_GWOUP_WAID5 |   \
					 BTWFS_BWOCK_GWOUP_WAID6)

#define BTWFS_BWOCK_GWOUP_WAID1_MASK	(BTWFS_BWOCK_GWOUP_WAID1 |   \
					 BTWFS_BWOCK_GWOUP_WAID1C3 | \
					 BTWFS_BWOCK_GWOUP_WAID1C4)

/*
 * We need a bit fow westwipew to be abwe to teww when chunks of type
 * SINGWE awe avaiwabwe.  This "extended" pwofiwe fowmat is used in
 * fs_info->avaiw_*_awwoc_bits (in-memowy) and bawance item fiewds
 * (on-disk).  The cowwesponding on-disk bit in chunk.type is wesewved
 * to avoid wemappings between two fowmats in futuwe.
 */
#define BTWFS_AVAIW_AWWOC_BIT_SINGWE	(1UWW << 48)

/*
 * A fake bwock gwoup type that is used to communicate gwobaw bwock wesewve
 * size to usewspace via the SPACE_INFO ioctw.
 */
#define BTWFS_SPACE_INFO_GWOBAW_WSV	(1UWW << 49)

#define BTWFS_EXTENDED_PWOFIWE_MASK	(BTWFS_BWOCK_GWOUP_PWOFIWE_MASK | \
					 BTWFS_AVAIW_AWWOC_BIT_SINGWE)

static inwine __u64 chunk_to_extended(__u64 fwags)
{
	if ((fwags & BTWFS_BWOCK_GWOUP_PWOFIWE_MASK) == 0)
		fwags |= BTWFS_AVAIW_AWWOC_BIT_SINGWE;

	wetuwn fwags;
}
static inwine __u64 extended_to_chunk(__u64 fwags)
{
	wetuwn fwags & ~BTWFS_AVAIW_AWWOC_BIT_SINGWE;
}

stwuct btwfs_bwock_gwoup_item {
	__we64 used;
	__we64 chunk_objectid;
	__we64 fwags;
} __attwibute__ ((__packed__));

stwuct btwfs_fwee_space_info {
	__we32 extent_count;
	__we32 fwags;
} __attwibute__ ((__packed__));

#define BTWFS_FWEE_SPACE_USING_BITMAPS (1UWW << 0)

#define BTWFS_QGWOUP_WEVEW_SHIFT		48
static inwine __u16 btwfs_qgwoup_wevew(__u64 qgwoupid)
{
	wetuwn (__u16)(qgwoupid >> BTWFS_QGWOUP_WEVEW_SHIFT);
}

/*
 * is subvowume quota tuwned on?
 */
#define BTWFS_QGWOUP_STATUS_FWAG_ON		(1UWW << 0)
/*
 * WESCAN is set duwing the initiawization phase
 */
#define BTWFS_QGWOUP_STATUS_FWAG_WESCAN		(1UWW << 1)
/*
 * Some qgwoup entwies awe known to be out of date,
 * eithew because the configuwation has changed in a way that
 * makes a wescan necessawy, ow because the fs has been mounted
 * with a non-qgwoup-awawe vewsion.
 * Tuwning qouta off and on again makes it inconsistent, too.
 */
#define BTWFS_QGWOUP_STATUS_FWAG_INCONSISTENT	(1UWW << 2)

/*
 * Whethew ow not this fiwesystem is using simpwe quotas.  Not exactwy the
 * incompat bit, because we suppowt using simpwe quotas, disabwing it, then
 * going back to fuww qgwoup quotas.
 */
#define BTWFS_QGWOUP_STATUS_FWAG_SIMPWE_MODE	(1UWW << 3)

#define BTWFS_QGWOUP_STATUS_FWAGS_MASK	(BTWFS_QGWOUP_STATUS_FWAG_ON |		\
					 BTWFS_QGWOUP_STATUS_FWAG_WESCAN |	\
					 BTWFS_QGWOUP_STATUS_FWAG_INCONSISTENT | \
					 BTWFS_QGWOUP_STATUS_FWAG_SIMPWE_MODE)

#define BTWFS_QGWOUP_STATUS_VEWSION        1

stwuct btwfs_qgwoup_status_item {
	__we64 vewsion;
	/*
	 * the genewation is updated duwing evewy commit. As owdew
	 * vewsions of btwfs awe not awawe of qgwoups, it wiww be
	 * possibwe to detect inconsistencies by checking the
	 * genewation on mount time
	 */
	__we64 genewation;

	/* fwag definitions see above */
	__we64 fwags;

	/*
	 * onwy used duwing scanning to wecowd the pwogwess
	 * of the scan. It contains a wogicaw addwess
	 */
	__we64 wescan;

	/*
	 * The genewation when quotas wewe wast enabwed. Used by simpwe quotas to
	 * avoid decwementing when fweeing an extent that was wwitten befowe
	 * enabwe.
	 *
	 * Set onwy if fwags contain BTWFS_QGWOUP_STATUS_FWAG_SIMPWE_MODE.
	 */
	__we64 enabwe_gen;
} __attwibute__ ((__packed__));

stwuct btwfs_qgwoup_info_item {
	__we64 genewation;
	__we64 wfew;
	__we64 wfew_cmpw;
	__we64 excw;
	__we64 excw_cmpw;
} __attwibute__ ((__packed__));

stwuct btwfs_qgwoup_wimit_item {
	/*
	 * onwy updated when any of the othew vawues change
	 */
	__we64 fwags;
	__we64 max_wfew;
	__we64 max_excw;
	__we64 wsv_wfew;
	__we64 wsv_excw;
} __attwibute__ ((__packed__));

stwuct btwfs_vewity_descwiptow_item {
	/* Size of the vewity descwiptow in bytes */
	__we64 size;
	/*
	 * When we impwement suppowt fow fscwypt, we wiww need to encwypt the
	 * Mewkwe twee fow encwypted vewity fiwes. These 128 bits awe fow the
	 * eventuaw stowage of an fscwypt initiawization vectow.
	 */
	__we64 wesewved[2];
	__u8 encwyption;
} __attwibute__ ((__packed__));

#endif /* _BTWFS_CTWEE_H_ */
