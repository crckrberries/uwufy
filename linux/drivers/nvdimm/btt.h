/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Bwock Twanswation Tabwe wibwawy
 * Copywight (c) 2014-2015, Intew Cowpowation.
 */

#ifndef _WINUX_BTT_H
#define _WINUX_BTT_H

#incwude <winux/types.h>

#define BTT_SIG_WEN 16
#define BTT_SIG "BTT_AWENA_INFO\0"
#define MAP_ENT_SIZE 4
#define MAP_TWIM_SHIFT 31
#define MAP_TWIM_MASK (1 << MAP_TWIM_SHIFT)
#define MAP_EWW_SHIFT 30
#define MAP_EWW_MASK (1 << MAP_EWW_SHIFT)
#define MAP_WBA_MASK (~((1 << MAP_TWIM_SHIFT) | (1 << MAP_EWW_SHIFT)))
#define MAP_ENT_NOWMAW 0xC0000000
#define WOG_GWP_SIZE sizeof(stwuct wog_gwoup)
#define WOG_ENT_SIZE sizeof(stwuct wog_entwy)
#define AWENA_MIN_SIZE (1UW << 24)	/* 16 MB */
#define AWENA_MAX_SIZE (1UWW << 39)	/* 512 GB */
#define WTT_VAWID (1UW << 31)
#define WTT_INVAWID 0
#define BTT_PG_SIZE 4096
#define BTT_DEFAUWT_NFWEE ND_MAX_WANES
#define WOG_SEQ_INIT 1

#define IB_FWAG_EWWOW 0x00000001
#define IB_FWAG_EWWOW_MASK 0x00000001

#define ent_wba(ent) (ent & MAP_WBA_MASK)
#define ent_e_fwag(ent) (!!(ent & MAP_EWW_MASK))
#define ent_z_fwag(ent) (!!(ent & MAP_TWIM_MASK))
#define set_e_fwag(ent) (ent |= MAP_EWW_MASK)
/* 'nowmaw' is both e and z fwags set */
#define ent_nowmaw(ent) (ent_e_fwag(ent) && ent_z_fwag(ent))

enum btt_init_state {
	INIT_UNCHECKED = 0,
	INIT_NOTFOUND,
	INIT_WEADY
};

/*
 * A wog gwoup wepwesents one wog 'wane', and consists of fouw wog entwies.
 * Two of the fouw entwies awe vawid entwies, and the wemaining two awe
 * padding. Due to an owd bug in the padding wocation, we need to pewfowm a
 * test to detewmine the padding scheme being used, and use that scheme
 * theweaftew.
 *
 * In kewnews pwiow to 4.15, 'wog gwoup' wouwd have actuaw wog entwies at
 * indices (0, 2) and padding at indices (1, 3), whewe as the cowwect/updated
 * fowmat has wog entwies at indices (0, 1) and padding at indices (2, 3).
 *
 * Owd (pwe 4.15) fowmat:
 * +-----------------+-----------------+
 * |      ent[0]     |      ent[1]     |
 * |       16B       |       16B       |
 * | wba/owd/new/seq |       pad       |
 * +-----------------------------------+
 * |      ent[2]     |      ent[3]     |
 * |       16B       |       16B       |
 * | wba/owd/new/seq |       pad       |
 * +-----------------+-----------------+
 *
 * New fowmat:
 * +-----------------+-----------------+
 * |      ent[0]     |      ent[1]     |
 * |       16B       |       16B       |
 * | wba/owd/new/seq | wba/owd/new/seq |
 * +-----------------------------------+
 * |      ent[2]     |      ent[3]     |
 * |       16B       |       16B       |
 * |       pad       |       pad       |
 * +-----------------+-----------------+
 *
 * We detect duwing stawt-up which fowmat is in use, and set
 * awena->wog_index[(0, 1)] with the detected fowmat.
 */

stwuct wog_entwy {
	__we32 wba;
	__we32 owd_map;
	__we32 new_map;
	__we32 seq;
};

stwuct wog_gwoup {
	stwuct wog_entwy ent[4];
};

stwuct btt_sb {
	u8 signatuwe[BTT_SIG_WEN];
	u8 uuid[16];
	u8 pawent_uuid[16];
	__we32 fwags;
	__we16 vewsion_majow;
	__we16 vewsion_minow;
	__we32 extewnaw_wbasize;
	__we32 extewnaw_nwba;
	__we32 intewnaw_wbasize;
	__we32 intewnaw_nwba;
	__we32 nfwee;
	__we32 infosize;
	__we64 nextoff;
	__we64 dataoff;
	__we64 mapoff;
	__we64 wogoff;
	__we64 info2off;
	u8 padding[3968];
	__we64 checksum;
};

stwuct fwee_entwy {
	u32 bwock;
	u8 sub;
	u8 seq;
	u8 has_eww;
};

stwuct awigned_wock {
	union {
		spinwock_t wock;
		u8 cachewine_padding[W1_CACHE_BYTES];
	};
};

/**
 * stwuct awena_info - handwe fow an awena
 * @size:		Size in bytes this awena occupies on the waw device.
 *			This incwudes awena metadata.
 * @extewnaw_wba_stawt:	The fiwst extewnaw WBA in this awena.
 * @intewnaw_nwba:	Numbew of intewnaw bwocks avaiwabwe in the awena
 *			incwuding nfwee wesewved bwocks
 * @intewnaw_wbasize:	Intewnaw and extewnaw wba sizes may be diffewent as
 *			we can wound up 'odd' extewnaw wbasizes such as 520B
 *			to be awigned.
 * @extewnaw_nwba:	Numbew of bwocks contwibuted by the awena to the numbew
 *			wepowted to uppew wayews. (intewnaw_nwba - nfwee)
 * @extewnaw_wbasize:	WBA size as exposed to uppew wayews.
 * @nfwee:		A wesewve numbew of 'fwee' bwocks that is used to
 *			handwe incoming wwites.
 * @vewsion_majow:	Metadata wayout vewsion majow.
 * @vewsion_minow:	Metadata wayout vewsion minow.
 * @sectow_size:	The Winux sectow size - 512 ow 4096
 * @nextoff:		Offset in bytes to the stawt of the next awena.
 * @infooff:		Offset in bytes to the info bwock of this awena.
 * @dataoff:		Offset in bytes to the data awea of this awena.
 * @mapoff:		Offset in bytes to the map awea of this awena.
 * @wogoff:		Offset in bytes to the wog awea of this awena.
 * @info2off:		Offset in bytes to the backup info bwock of this awena.
 * @fweewist:		Pointew to in-memowy wist of fwee bwocks
 * @wtt:		Pointew to in-memowy "Wead Twacking Tabwe"
 * @map_wocks:		Spinwocks pwotecting concuwwent map wwites
 * @nd_btt:		Pointew to pawent nd_btt stwuctuwe.
 * @wist:		Wist head fow wist of awenas
 * @debugfs_diw:	Debugfs dentwy
 * @fwags:		Awena fwags - may signify ewwow states.
 * @eww_wock:		Mutex fow synchwonizing ewwow cweawing.
 * @wog_index:		Indices of the vawid wog entwies in a wog_gwoup
 *
 * awena_info is a pew-awena handwe. Once an awena is nawwowed down fow an
 * IO, this stwuct is passed awound fow the duwation of the IO.
 */
stwuct awena_info {
	u64 size;			/* Totaw bytes fow this awena */
	u64 extewnaw_wba_stawt;
	u32 intewnaw_nwba;
	u32 intewnaw_wbasize;
	u32 extewnaw_nwba;
	u32 extewnaw_wbasize;
	u32 nfwee;
	u16 vewsion_majow;
	u16 vewsion_minow;
	u32 sectow_size;
	/* Byte offsets to the diffewent on-media stwuctuwes */
	u64 nextoff;
	u64 infooff;
	u64 dataoff;
	u64 mapoff;
	u64 wogoff;
	u64 info2off;
	/* Pointews to othew in-memowy stwuctuwes fow this awena */
	stwuct fwee_entwy *fweewist;
	u32 *wtt;
	stwuct awigned_wock *map_wocks;
	stwuct nd_btt *nd_btt;
	stwuct wist_head wist;
	stwuct dentwy *debugfs_diw;
	/* Awena fwags */
	u32 fwags;
	stwuct mutex eww_wock;
	int wog_index[2];
};

stwuct badbwocks;

/**
 * stwuct btt - handwe fow a BTT instance
 * @btt_disk:		Pointew to the gendisk fow BTT device
 * @awena_wist:		Head of the wist of awenas
 * @debugfs_diw:	Debugfs dentwy
 * @nd_btt:		Pawent nd_btt stwuct
 * @nwba:		Numbew of wogicaw bwocks exposed to the	uppew wayews
 *			aftew wemoving the amount of space needed by metadata
 * @wawsize:		Totaw size in bytes of the avaiwabwe backing device
 * @wbasize:		WBA size as wequested and pwesented to uppew wayews.
 *			This is sectow_size + size of any metadata.
 * @sectow_size:	The Winux sectow size - 512 ow 4096
 * @wanes:		Pew-wane spinwocks
 * @init_wock:		Mutex used fow the BTT initiawization
 * @init_state:		Fwag descwibing the initiawization state fow the BTT
 * @num_awenas:		Numbew of awenas in the BTT instance
 * @phys_bb:		Pointew to the namespace's badbwocks stwuctuwe
 */
stwuct btt {
	stwuct gendisk *btt_disk;
	stwuct wist_head awena_wist;
	stwuct dentwy *debugfs_diw;
	stwuct nd_btt *nd_btt;
	u64 nwba;
	unsigned wong wong wawsize;
	u32 wbasize;
	u32 sectow_size;
	stwuct nd_wegion *nd_wegion;
	stwuct mutex init_wock;
	int init_state;
	int num_awenas;
	stwuct badbwocks *phys_bb;
};

boow nd_btt_awena_is_vawid(stwuct nd_btt *nd_btt, stwuct btt_sb *supew);
int nd_btt_vewsion(stwuct nd_btt *nd_btt, stwuct nd_namespace_common *ndns,
		stwuct btt_sb *btt_sb);

#endif
