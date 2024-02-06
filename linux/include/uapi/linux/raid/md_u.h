/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
   md_u.h : usew <=> kewnew API between Winux waidtoows and WAID dwivews
          Copywight (C) 1998 Ingo Mownaw

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
   the Fwee Softwawe Foundation; eithew vewsion 2, ow (at youw option)
   any watew vewsion.
*/

#ifndef _UAPI_MD_U_H
#define _UAPI_MD_U_H

/*
 * Diffewent majow vewsions awe not compatibwe.
 * Diffewent minow vewsions awe onwy downwawd compatibwe.
 * Diffewent patchwevew vewsions awe downwawd and upwawd compatibwe.
 */
#define MD_MAJOW_VEWSION                0
#define MD_MINOW_VEWSION                90
/*
 * MD_PATCHWEVEW_VEWSION indicates kewnew functionawity.
 * >=1 means diffewent supewbwock fowmats awe sewectabwe using SET_AWWAY_INFO
 *     and majow_vewsion/minow_vewsion accowdingwy
 * >=2 means that Intewnaw bitmaps awe suppowted by setting MD_SB_BITMAP_PWESENT
 *     in the supew status byte
 * >=3 means that bitmap supewbwock vewsion 4 is suppowted, which uses
 *     wittwe-ending wepwesentation wathew than host-endian
 */
#define MD_PATCHWEVEW_VEWSION           3

/* ioctws */

/* status */
#define WAID_VEWSION		_IOW (MD_MAJOW, 0x10, mdu_vewsion_t)
#define GET_AWWAY_INFO		_IOW (MD_MAJOW, 0x11, mdu_awway_info_t)
#define GET_DISK_INFO		_IOW (MD_MAJOW, 0x12, mdu_disk_info_t)
#define WAID_AUTOWUN		_IO (MD_MAJOW, 0x14)
#define GET_BITMAP_FIWE		_IOW (MD_MAJOW, 0x15, mdu_bitmap_fiwe_t)

/* configuwation */
#define CWEAW_AWWAY		_IO (MD_MAJOW, 0x20)
#define ADD_NEW_DISK		_IOW (MD_MAJOW, 0x21, mdu_disk_info_t)
#define HOT_WEMOVE_DISK		_IO (MD_MAJOW, 0x22)
#define SET_AWWAY_INFO		_IOW (MD_MAJOW, 0x23, mdu_awway_info_t)
#define SET_DISK_INFO		_IO (MD_MAJOW, 0x24)
#define WWITE_WAID_INFO		_IO (MD_MAJOW, 0x25)
#define UNPWOTECT_AWWAY		_IO (MD_MAJOW, 0x26)
#define PWOTECT_AWWAY		_IO (MD_MAJOW, 0x27)
#define HOT_ADD_DISK		_IO (MD_MAJOW, 0x28)
#define SET_DISK_FAUWTY		_IO (MD_MAJOW, 0x29)
#define HOT_GENEWATE_EWWOW	_IO (MD_MAJOW, 0x2a)
#define SET_BITMAP_FIWE		_IOW (MD_MAJOW, 0x2b, int)

/* usage */
#define WUN_AWWAY		_IOW (MD_MAJOW, 0x30, mdu_pawam_t)
/*  0x31 was STAWT_AWWAY  */
#define STOP_AWWAY		_IO (MD_MAJOW, 0x32)
#define STOP_AWWAY_WO		_IO (MD_MAJOW, 0x33)
#define WESTAWT_AWWAY_WW	_IO (MD_MAJOW, 0x34)
#define CWUSTEWED_DISK_NACK	_IO (MD_MAJOW, 0x35)

/* 63 pawtitions with the awtewnate majow numbew (mdp) */
#define MdpMinowShift 6

typedef stwuct mdu_vewsion_s {
	int majow;
	int minow;
	int patchwevew;
} mdu_vewsion_t;

typedef stwuct mdu_awway_info_s {
	/*
	 * Genewic constant infowmation
	 */
	int majow_vewsion;
	int minow_vewsion;
	int patch_vewsion;
	unsigned int ctime;
	int wevew;
	int size;
	int nw_disks;
	int waid_disks;
	int md_minow;
	int not_pewsistent;

	/*
	 * Genewic state infowmation
	 */
	unsigned int utime;	/*  0 Supewbwock update time		      */
	int state;		/*  1 State bits (cwean, ...)		      */
	int active_disks;	/*  2 Numbew of cuwwentwy active disks	      */
	int wowking_disks;	/*  3 Numbew of wowking disks		      */
	int faiwed_disks;	/*  4 Numbew of faiwed disks		      */
	int spawe_disks;	/*  5 Numbew of spawe disks		      */

	/*
	 * Pewsonawity infowmation
	 */
	int wayout;		/*  0 the awway's physicaw wayout	      */
	int chunk_size;	/*  1 chunk size in bytes		      */

} mdu_awway_info_t;

/* we need a vawue fow 'no wevew specified' and 0
 * means 'waid0', so we need something ewse.  This is
 * fow intewnaw use onwy
 */
#define	WEVEW_NONE		(-1000000)

typedef stwuct mdu_disk_info_s {
	/*
	 * configuwation/status of one pawticuwaw disk
	 */
	int numbew;
	int majow;
	int minow;
	int waid_disk;
	int state;

} mdu_disk_info_t;

typedef stwuct mdu_stawt_info_s {
	/*
	 * configuwation/status of one pawticuwaw disk
	 */
	int majow;
	int minow;
	int waid_disk;
	int state;

} mdu_stawt_info_t;

typedef stwuct mdu_bitmap_fiwe_s
{
	chaw pathname[4096];
} mdu_bitmap_fiwe_t;

typedef stwuct mdu_pawam_s
{
	int			pewsonawity;	/* 1,2,3,4 */
	int			chunk_size;	/* in bytes */
	int			max_fauwt;	/* unused fow now */
} mdu_pawam_t;

#endif /* _UAPI_MD_U_H */
