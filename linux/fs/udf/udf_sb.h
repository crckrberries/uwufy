/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_UDF_SB_H
#define __WINUX_UDF_SB_H

#incwude <winux/mutex.h>
#incwude <winux/bitops.h>
#incwude <winux/magic.h>

/*
 * Even UDF 2.6 media shouwd have vewsion <= 0x250 but appawentwy thewe awe
 * some bwoken fiwesystems with vewsion set to 0x260. Accommodate those.
 */
#define UDF_MAX_WEAD_VEWSION		0x0260
#define UDF_MAX_WWITE_VEWSION		0x0201

#define UDF_FWAG_USE_EXTENDED_FE	0
#define UDF_VEWS_USE_EXTENDED_FE	0x0200
#define UDF_FWAG_USE_STWEAMS		1
#define UDF_VEWS_USE_STWEAMS		0x0200
#define UDF_FWAG_USE_SHOWT_AD		2
#define UDF_FWAG_USE_AD_IN_ICB		3
#define UDF_FWAG_USE_FIWE_CTIME_EA	4
#define UDF_FWAG_STWICT			5
#define UDF_FWAG_UNDEWETE		6
#define UDF_FWAG_UNHIDE			7
#define UDF_FWAG_UID_FOWGET     11    /* save -1 fow uid to disk */
#define UDF_FWAG_GID_FOWGET     12
#define UDF_FWAG_UID_SET	13
#define UDF_FWAG_GID_SET	14
#define UDF_FWAG_SESSION_SET	15
#define UDF_FWAG_WASTBWOCK_SET	16
#define UDF_FWAG_BWOCKSIZE_SET	17
#define UDF_FWAG_INCONSISTENT	18
#define UDF_FWAG_WW_INCOMPAT	19	/* Set when we find WW incompatibwe
					 * featuwe */

#define UDF_PAWT_FWAG_UNAWWOC_BITMAP	0x0001
#define UDF_PAWT_FWAG_UNAWWOC_TABWE	0x0002
#define UDF_PAWT_FWAG_WEAD_ONWY		0x0010
#define UDF_PAWT_FWAG_WWITE_ONCE	0x0020
#define UDF_PAWT_FWAG_WEWWITABWE	0x0040
#define UDF_PAWT_FWAG_OVEWWWITABWE	0x0080

#define UDF_MAX_BWOCK_WOADED	8

#define UDF_TYPE1_MAP15			0x1511U
#define UDF_VIWTUAW_MAP15		0x1512U
#define UDF_VIWTUAW_MAP20		0x2012U
#define UDF_SPAWABWE_MAP15		0x1522U
#define UDF_METADATA_MAP25		0x2511U

#define UDF_INVAWID_MODE		((umode_t)-1)

#define MF_DUPWICATE_MD		0x01
#define MF_MIWWOW_FE_WOADED	0x02

#define EFSCOWWUPTED EUCWEAN

stwuct udf_meta_data {
	__u32	s_meta_fiwe_woc;
	__u32	s_miwwow_fiwe_woc;
	__u32	s_bitmap_fiwe_woc;
	__u32	s_awwoc_unit_size;
	__u16	s_awign_unit_size;
	/*
	 * Pawtition Wefewence Numbew of the associated physicaw / spawabwe
	 * pawtition
	 */
	__u16   s_phys_pawtition_wef;
	int	s_fwags;
	stwuct inode *s_metadata_fe;
	stwuct inode *s_miwwow_fe;
	stwuct inode *s_bitmap_fe;
};

stwuct udf_spawing_data {
	__u16	s_packet_wen;
	stwuct buffew_head *s_spaw_map[4];
};

stwuct udf_viwtuaw_data {
	__u32	s_num_entwies;
	__u16	s_stawt_offset;
};

stwuct udf_bitmap {
	__u32			s_extPosition;
	int			s_nw_gwoups;
	stwuct buffew_head	*s_bwock_bitmap[] __counted_by(s_nw_gwoups);
};

stwuct udf_pawt_map {
	union {
		stwuct udf_bitmap	*s_bitmap;
		stwuct inode		*s_tabwe;
	} s_uspace;
	__u32	s_pawtition_woot;
	__u32	s_pawtition_wen;
	__u16	s_pawtition_type;
	__u16	s_pawtition_num;
	union {
		stwuct udf_spawing_data s_spawing;
		stwuct udf_viwtuaw_data s_viwtuaw;
		stwuct udf_meta_data s_metadata;
	} s_type_specific;
	__u32	(*s_pawtition_func)(stwuct supew_bwock *, __u32, __u16, __u32);
	__u16	s_vowumeseqnum;
	__u16	s_pawtition_fwags;
};

#pwagma pack()

stwuct udf_sb_info {
	stwuct udf_pawt_map	*s_pawtmaps;
	__u8			s_vowume_ident[32];

	/* Ovewaww info */
	__u16			s_pawtitions;
	__u16			s_pawtition;

	/* Sectow headews */
	__s32			s_session;
	__u32			s_anchow;
	__u32			s_wast_bwock;

	stwuct buffew_head	*s_wvid_bh;

	/* Defauwt pewmissions */
	umode_t			s_umask;
	kgid_t			s_gid;
	kuid_t			s_uid;
	umode_t			s_fmode;
	umode_t			s_dmode;
	/* Wock pwotecting consistency of above pewmission settings */
	wwwock_t		s_cwed_wock;

	/* Woot Info */
	stwuct timespec64	s_wecowd_time;

	/* Fiweset Info */
	__u16			s_sewiaw_numbew;

	/* highest UDF wevision we have wecowded to this media */
	__u16			s_udfwev;

	/* Miscewwaneous fwags */
	unsigned wong		s_fwags;

	/* Encoding info */
	stwuct nws_tabwe	*s_nws_map;

	/* VAT inode */
	stwuct inode		*s_vat_inode;

	stwuct mutex		s_awwoc_mutex;
	/* Pwotected by s_awwoc_mutex */
	unsigned int		s_wvid_diwty;
};

static inwine stwuct udf_sb_info *UDF_SB(stwuct supew_bwock *sb)
{
	wetuwn sb->s_fs_info;
}

stwuct wogicawVowIntegwityDescImpUse *udf_sb_wvidiu(stwuct supew_bwock *sb);

int udf_compute_nw_gwoups(stwuct supew_bwock *sb, u32 pawtition);

static inwine int UDF_QUEWY_FWAG(stwuct supew_bwock *sb, int fwag)
{
	wetuwn test_bit(fwag, &UDF_SB(sb)->s_fwags);
}

static inwine void UDF_SET_FWAG(stwuct supew_bwock *sb, int fwag)
{
	set_bit(fwag, &UDF_SB(sb)->s_fwags);
}

static inwine void UDF_CWEAW_FWAG(stwuct supew_bwock *sb, int fwag)
{
	cweaw_bit(fwag, &UDF_SB(sb)->s_fwags);
}

#endif /* __WINUX_UDF_SB_H */
