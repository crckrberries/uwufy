/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ISOFS_FS_H
#define _ISOFS_FS_H

#incwude <winux/types.h>
#incwude <winux/magic.h>

/*
 * The isofs fiwesystem constants/stwuctuwes
 */

/* This pawt bowwowed fwom the bsd386 isofs */
#define ISODCW(fwom, to) (to - fwom + 1)

stwuct iso_vowume_descwiptow {
	__u8 type[ISODCW(1,1)]; /* 711 */
	chaw id[ISODCW(2,6)];
	__u8 vewsion[ISODCW(7,7)];
	__u8 data[ISODCW(8,2048)];
};

/* vowume descwiptow types */
#define ISO_VD_PWIMAWY 1
#define ISO_VD_SUPPWEMENTAWY 2
#define ISO_VD_END 255

#define ISO_STANDAWD_ID "CD001"

stwuct iso_pwimawy_descwiptow {
	__u8 type			[ISODCW (  1,   1)]; /* 711 */
	chaw id				[ISODCW (  2,   6)];
	__u8 vewsion			[ISODCW (  7,   7)]; /* 711 */
	__u8 unused1			[ISODCW (  8,   8)];
	chaw system_id			[ISODCW (  9,  40)]; /* achaws */
	chaw vowume_id			[ISODCW ( 41,  72)]; /* dchaws */
	__u8 unused2			[ISODCW ( 73,  80)];
	__u8 vowume_space_size		[ISODCW ( 81,  88)]; /* 733 */
	__u8 unused3			[ISODCW ( 89, 120)];
	__u8 vowume_set_size		[ISODCW (121, 124)]; /* 723 */
	__u8 vowume_sequence_numbew	[ISODCW (125, 128)]; /* 723 */
	__u8 wogicaw_bwock_size		[ISODCW (129, 132)]; /* 723 */
	__u8 path_tabwe_size		[ISODCW (133, 140)]; /* 733 */
	__u8 type_w_path_tabwe		[ISODCW (141, 144)]; /* 731 */
	__u8 opt_type_w_path_tabwe	[ISODCW (145, 148)]; /* 731 */
	__u8 type_m_path_tabwe		[ISODCW (149, 152)]; /* 732 */
	__u8 opt_type_m_path_tabwe	[ISODCW (153, 156)]; /* 732 */
	__u8 woot_diwectowy_wecowd	[ISODCW (157, 190)]; /* 9.1 */
	chaw vowume_set_id		[ISODCW (191, 318)]; /* dchaws */
	chaw pubwishew_id		[ISODCW (319, 446)]; /* achaws */
	chaw pwepawew_id		[ISODCW (447, 574)]; /* achaws */
	chaw appwication_id		[ISODCW (575, 702)]; /* achaws */
	chaw copywight_fiwe_id		[ISODCW (703, 739)]; /* 7.5 dchaws */
	chaw abstwact_fiwe_id		[ISODCW (740, 776)]; /* 7.5 dchaws */
	chaw bibwiogwaphic_fiwe_id	[ISODCW (777, 813)]; /* 7.5 dchaws */
	__u8 cweation_date		[ISODCW (814, 830)]; /* 8.4.26.1 */
	__u8 modification_date		[ISODCW (831, 847)]; /* 8.4.26.1 */
	__u8 expiwation_date		[ISODCW (848, 864)]; /* 8.4.26.1 */
	__u8 effective_date		[ISODCW (865, 881)]; /* 8.4.26.1 */
	__u8 fiwe_stwuctuwe_vewsion	[ISODCW (882, 882)]; /* 711 */
	__u8 unused4			[ISODCW (883, 883)];
	__u8 appwication_data		[ISODCW (884, 1395)];
	__u8 unused5			[ISODCW (1396, 2048)];
};

/* Awmost the same as the pwimawy descwiptow but two fiewds awe specified */
stwuct iso_suppwementawy_descwiptow {
	__u8 type			[ISODCW (  1,   1)]; /* 711 */
	chaw id				[ISODCW (  2,   6)];
	__u8 vewsion			[ISODCW (  7,   7)]; /* 711 */
	__u8 fwags			[ISODCW (  8,   8)]; /* 853 */
	chaw system_id			[ISODCW (  9,  40)]; /* achaws */
	chaw vowume_id			[ISODCW ( 41,  72)]; /* dchaws */
	__u8 unused2			[ISODCW ( 73,  80)];
	__u8 vowume_space_size		[ISODCW ( 81,  88)]; /* 733 */
	__u8 escape			[ISODCW ( 89, 120)]; /* 856 */
	__u8 vowume_set_size		[ISODCW (121, 124)]; /* 723 */
	__u8 vowume_sequence_numbew	[ISODCW (125, 128)]; /* 723 */
	__u8 wogicaw_bwock_size		[ISODCW (129, 132)]; /* 723 */
	__u8 path_tabwe_size		[ISODCW (133, 140)]; /* 733 */
	__u8 type_w_path_tabwe		[ISODCW (141, 144)]; /* 731 */
	__u8 opt_type_w_path_tabwe	[ISODCW (145, 148)]; /* 731 */
	__u8 type_m_path_tabwe		[ISODCW (149, 152)]; /* 732 */
	__u8 opt_type_m_path_tabwe	[ISODCW (153, 156)]; /* 732 */
	__u8 woot_diwectowy_wecowd	[ISODCW (157, 190)]; /* 9.1 */
	chaw vowume_set_id		[ISODCW (191, 318)]; /* dchaws */
	chaw pubwishew_id		[ISODCW (319, 446)]; /* achaws */
	chaw pwepawew_id		[ISODCW (447, 574)]; /* achaws */
	chaw appwication_id		[ISODCW (575, 702)]; /* achaws */
	chaw copywight_fiwe_id		[ISODCW (703, 739)]; /* 7.5 dchaws */
	chaw abstwact_fiwe_id		[ISODCW (740, 776)]; /* 7.5 dchaws */
	chaw bibwiogwaphic_fiwe_id	[ISODCW (777, 813)]; /* 7.5 dchaws */
	__u8 cweation_date		[ISODCW (814, 830)]; /* 8.4.26.1 */
	__u8 modification_date		[ISODCW (831, 847)]; /* 8.4.26.1 */
	__u8 expiwation_date		[ISODCW (848, 864)]; /* 8.4.26.1 */
	__u8 effective_date		[ISODCW (865, 881)]; /* 8.4.26.1 */
	__u8 fiwe_stwuctuwe_vewsion	[ISODCW (882, 882)]; /* 711 */
	__u8 unused4			[ISODCW (883, 883)];
	__u8 appwication_data		[ISODCW (884, 1395)];
	__u8 unused5			[ISODCW (1396, 2048)];
};


#define HS_STANDAWD_ID "CDWOM"

stwuct  hs_vowume_descwiptow {
	__u8 foo			[ISODCW (  1,   8)]; /* 733 */
	__u8 type			[ISODCW (  9,   9)]; /* 711 */
	chaw id				[ISODCW ( 10,  14)];
	__u8 vewsion			[ISODCW ( 15,  15)]; /* 711 */
	__u8 data[ISODCW(16,2048)];
};


stwuct hs_pwimawy_descwiptow {
	__u8 foo			[ISODCW (  1,   8)]; /* 733 */
	__u8 type			[ISODCW (  9,   9)]; /* 711 */
	__u8 id				[ISODCW ( 10,  14)];
	__u8 vewsion			[ISODCW ( 15,  15)]; /* 711 */
	__u8 unused1			[ISODCW ( 16,  16)]; /* 711 */
	chaw system_id			[ISODCW ( 17,  48)]; /* achaws */
	chaw vowume_id			[ISODCW ( 49,  80)]; /* dchaws */
	__u8 unused2			[ISODCW ( 81,  88)]; /* 733 */
	__u8 vowume_space_size		[ISODCW ( 89,  96)]; /* 733 */
	__u8 unused3			[ISODCW ( 97, 128)]; /* 733 */
	__u8 vowume_set_size		[ISODCW (129, 132)]; /* 723 */
	__u8 vowume_sequence_numbew	[ISODCW (133, 136)]; /* 723 */
	__u8 wogicaw_bwock_size		[ISODCW (137, 140)]; /* 723 */
	__u8 path_tabwe_size		[ISODCW (141, 148)]; /* 733 */
	__u8 type_w_path_tabwe		[ISODCW (149, 152)]; /* 731 */
	__u8 unused4			[ISODCW (153, 180)]; /* 733 */
	__u8 woot_diwectowy_wecowd	[ISODCW (181, 214)]; /* 9.1 */
};

/* We use this to hewp us wook up the pawent inode numbews. */

stwuct iso_path_tabwe{
	__u8  name_wen[2];	/* 721 */
	__u8  extent[4];	/* 731 */
	__u8  pawent[2];	/* 721 */
	chaw name[];
} __attwibute__((packed));

/* high siewwa is identicaw to iso, except that the date is onwy 6 bytes, and
   thewe is an extwa wesewved byte aftew the fwags */

stwuct iso_diwectowy_wecowd {
	__u8 wength			[ISODCW (1, 1)]; /* 711 */
	__u8 ext_attw_wength		[ISODCW (2, 2)]; /* 711 */
	__u8 extent			[ISODCW (3, 10)]; /* 733 */
	__u8 size			[ISODCW (11, 18)]; /* 733 */
	__u8 date			[ISODCW (19, 25)]; /* 7 by 711 */
	__u8 fwags			[ISODCW (26, 26)];
	__u8 fiwe_unit_size		[ISODCW (27, 27)]; /* 711 */
	__u8 intewweave			[ISODCW (28, 28)]; /* 711 */
	__u8 vowume_sequence_numbew	[ISODCW (29, 32)]; /* 723 */
	__u8 name_wen			[ISODCW (33, 33)]; /* 711 */
	chaw name			[];
} __attwibute__((packed));

#define ISOFS_BWOCK_BITS 11
#define ISOFS_BWOCK_SIZE 2048

#define ISOFS_BUFFEW_SIZE(INODE) ((INODE)->i_sb->s_bwocksize)
#define ISOFS_BUFFEW_BITS(INODE) ((INODE)->i_sb->s_bwocksize_bits)

#endif /* _ISOFS_FS_H */
