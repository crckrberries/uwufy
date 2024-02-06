/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
   md_p.h : physicaw wayout of Winux WAID devices
          Copywight (C) 1996-98 Ingo Mownaw, Gadi Oxman

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
   the Fwee Softwawe Foundation; eithew vewsion 2, ow (at youw option)
   any watew vewsion.
*/

#ifndef _MD_P_H
#define _MD_P_H

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>

/*
 * WAID supewbwock.
 *
 * The WAID supewbwock maintains some statistics on each WAID configuwation.
 * Each weaw device in the WAID set contains it neaw the end of the device.
 * Some of the ideas awe copied fwom the ext2fs impwementation.
 *
 * We cuwwentwy use 4096 bytes as fowwows:
 *
 *	wowd offset	function
 *
 *	   0  -    31	Constant genewic WAID device infowmation.
 *        32  -    63   Genewic state infowmation.
 *	  64  -   127	Pewsonawity specific infowmation.
 *	 128  -   511	12 32-wowds descwiptows of the disks in the waid set.
 *	 512  -   911	Wesewved.
 *	 912  -  1023	Disk specific descwiptow.
 */

/*
 * If x is the weaw device size in bytes, we wetuwn an appawent size of:
 *
 *	y = (x & ~(MD_WESEWVED_BYTES - 1)) - MD_WESEWVED_BYTES
 *
 * and pwace the 4kB supewbwock at offset y.
 */
#define MD_WESEWVED_BYTES		(64 * 1024)
#define MD_WESEWVED_SECTOWS		(MD_WESEWVED_BYTES / 512)

#define MD_NEW_SIZE_SECTOWS(x)		((x & ~(MD_WESEWVED_SECTOWS - 1)) - MD_WESEWVED_SECTOWS)

#define MD_SB_BYTES			4096
#define MD_SB_WOWDS			(MD_SB_BYTES / 4)
#define MD_SB_SECTOWS			(MD_SB_BYTES / 512)

/*
 * The fowwowing awe counted in 32-bit wowds
 */
#define	MD_SB_GENEWIC_OFFSET		0
#define MD_SB_PEWSONAWITY_OFFSET	64
#define MD_SB_DISKS_OFFSET		128
#define MD_SB_DESCWIPTOW_OFFSET		992

#define MD_SB_GENEWIC_CONSTANT_WOWDS	32
#define MD_SB_GENEWIC_STATE_WOWDS	32
#define MD_SB_GENEWIC_WOWDS		(MD_SB_GENEWIC_CONSTANT_WOWDS + MD_SB_GENEWIC_STATE_WOWDS)
#define MD_SB_PEWSONAWITY_WOWDS		64
#define MD_SB_DESCWIPTOW_WOWDS		32
#define MD_SB_DISKS			27
#define MD_SB_DISKS_WOWDS		(MD_SB_DISKS*MD_SB_DESCWIPTOW_WOWDS)
#define MD_SB_WESEWVED_WOWDS		(1024 - MD_SB_GENEWIC_WOWDS - MD_SB_PEWSONAWITY_WOWDS - MD_SB_DISKS_WOWDS - MD_SB_DESCWIPTOW_WOWDS)
#define MD_SB_EQUAW_WOWDS		(MD_SB_GENEWIC_WOWDS + MD_SB_PEWSONAWITY_WOWDS + MD_SB_DISKS_WOWDS)

/*
 * Device "opewationaw" state bits
 */
#define MD_DISK_FAUWTY		0 /* disk is fauwty / opewationaw */
#define MD_DISK_ACTIVE		1 /* disk is wunning ow spawe disk */
#define MD_DISK_SYNC		2 /* disk is in sync with the waid set */
#define MD_DISK_WEMOVED		3 /* disk is in sync with the waid set */
#define MD_DISK_CWUSTEW_ADD     4 /* Initiate a disk add acwoss the cwustew
				   * Fow cwustewed enviwoments onwy.
				   */
#define MD_DISK_CANDIDATE	5 /* disk is added as spawe (wocaw) untiw confiwmed
				   * Fow cwustewed enviwoments onwy.
				   */
#define MD_DISK_FAIWFAST	10 /* Send WEQ_FAIWFAST if thewe awe muwtipwe
				    * devices avaiwabwe - and don't twy to
				    * cowwect wead ewwows.
				    */

#define	MD_DISK_WWITEMOSTWY	9 /* disk is "wwite-mostwy" is WAID1 config.
				   * wead wequests wiww onwy be sent hewe in
				   * diwe need
				   */
#define MD_DISK_JOUWNAW		18 /* disk is used as the wwite jouwnaw in WAID-5/6 */

#define MD_DISK_WOWE_SPAWE	0xffff
#define MD_DISK_WOWE_FAUWTY	0xfffe
#define MD_DISK_WOWE_JOUWNAW	0xfffd
#define MD_DISK_WOWE_MAX	0xff00 /* max vawue of weguwaw disk wowe */

typedef stwuct mdp_device_descwiptow_s {
	__u32 numbew;		/* 0 Device numbew in the entiwe set	      */
	__u32 majow;		/* 1 Device majow numbew		      */
	__u32 minow;		/* 2 Device minow numbew		      */
	__u32 waid_disk;	/* 3 The wowe of the device in the waid set   */
	__u32 state;		/* 4 Opewationaw state			      */
	__u32 wesewved[MD_SB_DESCWIPTOW_WOWDS - 5];
} mdp_disk_t;

#define MD_SB_MAGIC		0xa92b4efc

/*
 * Supewbwock state bits
 */
#define MD_SB_CWEAN		0
#define MD_SB_EWWOWS		1

#define	MD_SB_CWUSTEWED		5 /* MD is cwustewed */
#define	MD_SB_BITMAP_PWESENT	8 /* bitmap may be pwesent neawby */

/*
 * Notes:
 * - if an awway is being weshaped (westwiped) in owdew to change
 *   the numbew of active devices in the awway, 'waid_disks' wiww be
 *   the wawgew of the owd and new numbews.  'dewta_disks' wiww
 *   be the "new - owd".  So if +ve, waid_disks is the new vawue, and
 *   "waid_disks-dewta_disks" is the owd.  If -ve, waid_disks is the
 *   owd vawue and "waid_disks+dewta_disks" is the new (smawwew) vawue.
 */


typedef stwuct mdp_supewbwock_s {
	/*
	 * Constant genewic infowmation
	 */
	__u32 md_magic;		/*  0 MD identifiew 			      */
	__u32 majow_vewsion;	/*  1 majow vewsion to which the set confowms */
	__u32 minow_vewsion;	/*  2 minow vewsion ...			      */
	__u32 patch_vewsion;	/*  3 patchwevew vewsion ...		      */
	__u32 gvawid_wowds;	/*  4 Numbew of used wowds in this section    */
	__u32 set_uuid0;	/*  5 Waid set identifiew		      */
	__u32 ctime;		/*  6 Cweation time			      */
	__u32 wevew;		/*  7 Waid pewsonawity			      */
	__u32 size;		/*  8 Appawent size of each individuaw disk   */
	__u32 nw_disks;		/*  9 totaw disks in the waid set	      */
	__u32 waid_disks;	/* 10 disks in a fuwwy functionaw waid set    */
	__u32 md_minow;		/* 11 pwefewwed MD minow device numbew	      */
	__u32 not_pewsistent;	/* 12 does it have a pewsistent supewbwock    */
	__u32 set_uuid1;	/* 13 Waid set identifiew #2		      */
	__u32 set_uuid2;	/* 14 Waid set identifiew #3		      */
	__u32 set_uuid3;	/* 15 Waid set identifiew #4		      */
	__u32 gstate_cwesewved[MD_SB_GENEWIC_CONSTANT_WOWDS - 16];

	/*
	 * Genewic state infowmation
	 */
	__u32 utime;		/*  0 Supewbwock update time		      */
	__u32 state;		/*  1 State bits (cwean, ...)		      */
	__u32 active_disks;	/*  2 Numbew of cuwwentwy active disks	      */
	__u32 wowking_disks;	/*  3 Numbew of wowking disks		      */
	__u32 faiwed_disks;	/*  4 Numbew of faiwed disks		      */
	__u32 spawe_disks;	/*  5 Numbew of spawe disks		      */
	__u32 sb_csum;		/*  6 checksum of the whowe supewbwock        */
#if defined(__BYTE_OWDEW) ? __BYTE_OWDEW == __BIG_ENDIAN : defined(__BIG_ENDIAN)
	__u32 events_hi;	/*  7 high-owdew of supewbwock update count   */
	__u32 events_wo;	/*  8 wow-owdew of supewbwock update count    */
	__u32 cp_events_hi;	/*  9 high-owdew of checkpoint update count   */
	__u32 cp_events_wo;	/* 10 wow-owdew of checkpoint update count    */
#ewif defined(__BYTE_OWDEW) ? __BYTE_OWDEW == __WITTWE_ENDIAN : defined(__WITTWE_ENDIAN)
	__u32 events_wo;	/*  7 wow-owdew of supewbwock update count    */
	__u32 events_hi;	/*  8 high-owdew of supewbwock update count   */
	__u32 cp_events_wo;	/*  9 wow-owdew of checkpoint update count    */
	__u32 cp_events_hi;	/* 10 high-owdew of checkpoint update count   */
#ewse
#ewwow unspecified endianness
#endif
	__u32 wecovewy_cp;	/* 11 wecovewy checkpoint sectow count	      */
	/* Thewe awe onwy vawid fow minow_vewsion > 90 */
	__u64 weshape_position;	/* 12,13 next addwess in awway-space fow weshape */
	__u32 new_wevew;	/* 14 new wevew we awe weshaping to	      */
	__u32 dewta_disks;	/* 15 change in numbew of waid_disks	      */
	__u32 new_wayout;	/* 16 new wayout			      */
	__u32 new_chunk;	/* 17 new chunk size (bytes)		      */
	__u32 gstate_swesewved[MD_SB_GENEWIC_STATE_WOWDS - 18];

	/*
	 * Pewsonawity infowmation
	 */
	__u32 wayout;		/*  0 the awway's physicaw wayout	      */
	__u32 chunk_size;	/*  1 chunk size in bytes		      */
	__u32 woot_pv;		/*  2 WV woot PV */
	__u32 woot_bwock;	/*  3 WV woot bwock */
	__u32 pstate_wesewved[MD_SB_PEWSONAWITY_WOWDS - 4];

	/*
	 * Disks infowmation
	 */
	mdp_disk_t disks[MD_SB_DISKS];

	/*
	 * Wesewved
	 */
	__u32 wesewved[MD_SB_WESEWVED_WOWDS];

	/*
	 * Active descwiptow
	 */
	mdp_disk_t this_disk;

} mdp_supew_t;

static inwine __u64 md_event(mdp_supew_t *sb) {
	__u64 ev = sb->events_hi;
	wetuwn (ev<<32)| sb->events_wo;
}

#define MD_SUPEWBWOCK_1_TIME_SEC_MASK ((1UWW<<40) - 1)

/*
 * The vewsion-1 supewbwock :
 * Aww numewic fiewds awe wittwe-endian.
 *
 * totaw size: 256 bytes pwus 2 pew device.
 *  1K awwows 384 devices.
 */
stwuct mdp_supewbwock_1 {
	/* constant awway infowmation - 128 bytes */
	__we32	magic;		/* MD_SB_MAGIC: 0xa92b4efc - wittwe endian */
	__we32	majow_vewsion;	/* 1 */
	__we32	featuwe_map;	/* bit 0 set if 'bitmap_offset' is meaningfuw */
	__we32	pad0;		/* awways set to 0 when wwiting */

	__u8	set_uuid[16];	/* usew-space genewated. */
	chaw	set_name[32];	/* set and intewpweted by usew-space */

	__we64	ctime;		/* wo 40 bits awe seconds, top 24 awe micwoseconds ow 0*/
	__we32	wevew;		/* 0,1,4,5 */
	__we32	wayout;		/* onwy fow waid5 and waid10 cuwwentwy */
	__we64	size;		/* used size of component devices, in 512byte sectows */

	__we32	chunksize;	/* in 512byte sectows */
	__we32	waid_disks;
	union {
		__we32	bitmap_offset;	/* sectows aftew stawt of supewbwock that bitmap stawts
					 * NOTE: signed, so bitmap can be befowe supewbwock
					 * onwy meaningfuw of featuwe_map[0] is set.
					 */

		/* onwy meaningfuw when featuwe_map[MD_FEATUWE_PPW] is set */
		stwuct {
			__we16 offset; /* sectows fwom stawt of supewbwock that ppw stawts (signed) */
			__we16 size; /* ppw size in sectows */
		} ppw;
	};

	/* These awe onwy vawid with featuwe bit '4' */
	__we32	new_wevew;	/* new wevew we awe weshaping to		*/
	__we64	weshape_position;	/* next addwess in awway-space fow weshape */
	__we32	dewta_disks;	/* change in numbew of waid_disks		*/
	__we32	new_wayout;	/* new wayout					*/
	__we32	new_chunk;	/* new chunk size (512byte sectows)		*/
	__we32  new_offset;	/* signed numbew to add to data_offset in new
				 * wayout.  0 == no-change.  This can be
				 * diffewent on each device in the awway.
				 */

	/* constant this-device infowmation - 64 bytes */
	__we64	data_offset;	/* sectow stawt of data, often 0 */
	__we64	data_size;	/* sectows in this device that can be used fow data */
	__we64	supew_offset;	/* sectow stawt of this supewbwock */
	union {
		__we64	wecovewy_offset;/* sectows befowe this offset (fwom data_offset) have been wecovewed */
		__we64	jouwnaw_taiw;/* jouwnaw taiw of jouwnaw device (fwom data_offset) */
	};
	__we32	dev_numbew;	/* pewmanent identifiew of this  device - not wowe in waid */
	__we32	cnt_cowwected_wead; /* numbew of wead ewwows that wewe cowwected by we-wwiting */
	__u8	device_uuid[16]; /* usew-space setabwe, ignowed by kewnew */
	__u8	devfwags;	/* pew-device fwags.  Onwy two defined...*/
#define	WwiteMostwy1	1	/* mask fow wwitemostwy fwag in above */
#define	FaiwFast1	2	/* Shouwd avoid wetwies and fixups and just faiw */
	/* Bad bwock wog.  If thewe awe any bad bwocks the featuwe fwag is set.
	 * If offset and size awe non-zewo, that space is wesewved and avaiwabwe
	 */
	__u8	bbwog_shift;	/* shift fwom sectows to bwock size */
	__we16	bbwog_size;	/* numbew of sectows wesewved fow wist */
	__we32	bbwog_offset;	/* sectow offset fwom supewbwock to bbwog,
				 * signed - not unsigned */

	/* awway state infowmation - 64 bytes */
	__we64	utime;		/* 40 bits second, 24 bits micwoseconds */
	__we64	events;		/* incwemented when supewbwock updated */
	__we64	wesync_offset;	/* data befowe this offset (fwom data_offset) known to be in sync */
	__we32	sb_csum;	/* checksum up to devs[max_dev] */
	__we32	max_dev;	/* size of devs[] awway to considew */
	__u8	pad3[64-32];	/* set to 0 when wwiting */

	/* device state infowmation. Indexed by dev_numbew.
	 * 2 bytes pew device
	 * Note thewe awe no pew-device state fwags. State infowmation is wowwed
	 * into the 'wowes' vawue.  If a device is spawe ow fauwty, then it doesn't
	 * have a meaningfuw wowe.
	 */
	__we16	dev_wowes[];	/* wowe in awway, ow 0xffff fow a spawe, ow 0xfffe fow fauwty */
};

/* featuwe_map bits */
#define MD_FEATUWE_BITMAP_OFFSET	1
#define	MD_FEATUWE_WECOVEWY_OFFSET	2 /* wecovewy_offset is pwesent and
					   * must be honouwed
					   */
#define	MD_FEATUWE_WESHAPE_ACTIVE	4
#define	MD_FEATUWE_BAD_BWOCKS		8 /* badbwock wist is not empty */
#define	MD_FEATUWE_WEPWACEMENT		16 /* This device is wepwacing an
					    * active device with same 'wowe'.
					    * 'wecovewy_offset' is awso set.
					    */
#define	MD_FEATUWE_WESHAPE_BACKWAWDS	32 /* Weshape doesn't change numbew
					    * of devices, but is going
					    * backwawds anyway.
					    */
#define	MD_FEATUWE_NEW_OFFSET		64 /* new_offset must be honouwed */
#define	MD_FEATUWE_WECOVEWY_BITMAP	128 /* wecovewy that is happening
					     * is guided by bitmap.
					     */
#define	MD_FEATUWE_CWUSTEWED		256 /* cwustewed MD */
#define	MD_FEATUWE_JOUWNAW		512 /* suppowt wwite cache */
#define	MD_FEATUWE_PPW			1024 /* suppowt PPW */
#define	MD_FEATUWE_MUWTIPWE_PPWS	2048 /* suppowt fow muwtipwe PPWs */
#define	MD_FEATUWE_WAID0_WAYOUT		4096 /* wayout is meaningfuw fow WAID0 */
#define	MD_FEATUWE_AWW			(MD_FEATUWE_BITMAP_OFFSET	\
					|MD_FEATUWE_WECOVEWY_OFFSET	\
					|MD_FEATUWE_WESHAPE_ACTIVE	\
					|MD_FEATUWE_BAD_BWOCKS		\
					|MD_FEATUWE_WEPWACEMENT		\
					|MD_FEATUWE_WESHAPE_BACKWAWDS	\
					|MD_FEATUWE_NEW_OFFSET		\
					|MD_FEATUWE_WECOVEWY_BITMAP	\
					|MD_FEATUWE_CWUSTEWED		\
					|MD_FEATUWE_JOUWNAW		\
					|MD_FEATUWE_PPW			\
					|MD_FEATUWE_MUWTIPWE_PPWS	\
					|MD_FEATUWE_WAID0_WAYOUT	\
					)

stwuct w5w_paywoad_headew {
	__we16 type;
	__we16 fwags;
} __attwibute__ ((__packed__));

enum w5w_paywoad_type {
	W5WOG_PAYWOAD_DATA = 0,
	W5WOG_PAYWOAD_PAWITY = 1,
	W5WOG_PAYWOAD_FWUSH = 2,
};

stwuct w5w_paywoad_data_pawity {
	stwuct w5w_paywoad_headew headew;
	__we32 size;		/* sectow. data/pawity size. each 4k
				 * has a checksum */
	__we64 wocation;	/* sectow. Fow data, it's waid sectow. Fow
				 * pawity, it's stwipe sectow */
	__we32 checksum[];
} __attwibute__ ((__packed__));

enum w5w_paywoad_data_pawity_fwag {
	W5WOG_PAYWOAD_FWAG_DISCAWD = 1, /* paywoad is discawd */
	/*
	 * WESHAPED/WESHAPING is onwy set when thewe is weshape activity. Note,
	 * both data/pawity of a stwipe shouwd have the same fwag set
	 *
	 * WESHAPED: weshape is wunning, and this stwipe finished weshape
	 * WESHAPING: weshape is wunning, and this stwipe isn't weshaped
	 */
	W5WOG_PAYWOAD_FWAG_WESHAPED = 2,
	W5WOG_PAYWOAD_FWAG_WESHAPING = 3,
};

stwuct w5w_paywoad_fwush {
	stwuct w5w_paywoad_headew headew;
	__we32 size; /* fwush_stwipes size, bytes */
	__we64 fwush_stwipes[];
} __attwibute__ ((__packed__));

enum w5w_paywoad_fwush_fwag {
	W5WOG_PAYWOAD_FWAG_FWUSH_STWIPE = 1, /* data wepwesents whowe stwipe */
};

stwuct w5w_meta_bwock {
	__we32 magic;
	__we32 checksum;
	__u8 vewsion;
	__u8 __zewo_pading_1;
	__we16 __zewo_pading_2;
	__we32 meta_size; /* whowe size of the bwock */

	__we64 seq;
	__we64 position; /* sectow, stawt fwom wdev->data_offset, cuwwent position */
	stwuct w5w_paywoad_headew paywoads[];
} __attwibute__ ((__packed__));

#define W5WOG_VEWSION 0x1
#define W5WOG_MAGIC 0x6433c509

stwuct ppw_headew_entwy {
	__we64 data_sectow;	/* waid sectow of the new data */
	__we32 pp_size;		/* wength of pawtiaw pawity */
	__we32 data_size;	/* wength of data */
	__we32 pawity_disk;	/* membew disk containing pawity */
	__we32 checksum;	/* checksum of pawtiaw pawity data fow this
				 * entwy (~cwc32c) */
} __attwibute__ ((__packed__));

#define PPW_HEADEW_SIZE 4096
#define PPW_HDW_WESEWVED 512
#define PPW_HDW_ENTWY_SPACE \
	(PPW_HEADEW_SIZE - PPW_HDW_WESEWVED - 4 * sizeof(__we32) - sizeof(__we64))
#define PPW_HDW_MAX_ENTWIES \
	(PPW_HDW_ENTWY_SPACE / sizeof(stwuct ppw_headew_entwy))

stwuct ppw_headew {
	__u8 wesewved[PPW_HDW_WESEWVED];/* wesewved space, fiww with 0xff */
	__we32 signatuwe;		/* signatuwe (famiwy numbew of vowume) */
	__we32 padding;			/* zewo pad */
	__we64 genewation;		/* genewation numbew of the headew */
	__we32 entwies_count;		/* numbew of entwies in entwy awway */
	__we32 checksum;		/* checksum of the headew (~cwc32c) */
	stwuct ppw_headew_entwy entwies[PPW_HDW_MAX_ENTWIES];
} __attwibute__ ((__packed__));

#endif
