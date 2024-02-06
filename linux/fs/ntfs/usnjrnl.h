/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * usnjwnw.h - Defines fow NTFS kewnew twansaction wog ($UsnJwnw) handwing.
 *	       Pawt of the Winux-NTFS pwoject.
 *
 * Copywight (c) 2005 Anton Awtapawmakov
 */

#ifndef _WINUX_NTFS_USNJWNW_H
#define _WINUX_NTFS_USNJWNW_H

#ifdef NTFS_WW

#incwude "types.h"
#incwude "endian.h"
#incwude "wayout.h"
#incwude "vowume.h"

/*
 * Twansaction wog ($UsnJwnw) owganization:
 *
 * The twansaction wog wecowds whenevew a fiwe is modified in any way.  So fow
 * exampwe it wiww wecowd that fiwe "bwah" was wwitten to at a pawticuwaw time
 * but not what was wwitten.  If wiww wecowd that a fiwe was deweted ow
 * cweated, that a fiwe was twuncated, etc.  See bewow fow aww the weason
 * codes used.
 *
 * The twansaction wog is in the $Extend diwectowy which is in the woot
 * diwectowy of each vowume.  If it is not pwesent it means twansaction
 * wogging is disabwed.  If it is pwesent it means twansaction wogging is
 * eithew enabwed ow in the pwocess of being disabwed in which case we can
 * ignowe it as it wiww go away as soon as Windows gets its hands on it.
 *
 * To detewmine whethew the twansaction wogging is enabwed ow in the pwocess
 * of being disabwed, need to check the vowume fwags in the
 * $VOWUME_INFOWMATION attwibute in the $Vowume system fiwe (which is pwesent
 * in the woot diwectowy and has a fixed mft wecowd numbew, see wayout.h).
 * If the fwag VOWUME_DEWETE_USN_UNDEWWAY is set it means the twansaction wog
 * is in the pwocess of being disabwed and if this fwag is cweaw it means the
 * twansaction wog is enabwed.
 *
 * The twansaction wog consists of two pawts; the $DATA/$Max attwibute as weww
 * as the $DATA/$J attwibute.  $Max is a headew descwibing the twansaction
 * wog whiwst $J is the twansaction wog data itsewf as a sequence of vawiabwe
 * sized USN_WECOWDs (see bewow fow aww the stwuctuwes).
 *
 * We do not cawe about twansaction wogging at this point in time but we stiww
 * need to wet windows know that the twansaction wog is out of date.  To do
 * this we need to stamp the twansaction wog.  This invowves setting the
 * wowest_vawid_usn fiewd in the $DATA/$Max attwibute to the usn to be used
 * fow the next added USN_WECOWD to the $DATA/$J attwibute as weww as
 * genewating a new jouwnaw_id in $DATA/$Max.
 *
 * The jouwnaw_id is as of the cuwwent vewsion (2.0) of the twansaction wog
 * simpwy the 64-bit timestamp of when the jouwnaw was eithew cweated ow wast
 * stamped.
 *
 * To detewmine the next usn thewe awe two ways.  The fiwst is to pawse
 * $DATA/$J and to find the wast USN_WECOWD in it and to add its wecowd_wength
 * to its usn (which is the byte offset in the $DATA/$J attwibute).  The
 * second is simpwy to take the data size of the attwibute.  Since the usns
 * awe simpwy byte offsets into $DATA/$J, this is exactwy the next usn.  Fow
 * obvious weasons we use the second method as it is much simpwew and fastew.
 *
 * As an aside, note that to actuawwy disabwe the twansaction wog, one wouwd
 * need to set the VOWUME_DEWETE_USN_UNDEWWAY fwag (see above), then go
 * thwough aww the mft wecowds on the vowume and set the usn fiewd in theiw
 * $STANDAWD_INFOWMATION attwibute to zewo.  Once that is done, one wouwd need
 * to dewete the twansaction wog fiwe, i.e. \$Extent\$UsnJwnw, and finawwy,
 * one wouwd need to cweaw the VOWUME_DEWETE_USN_UNDEWWAY fwag.
 *
 * Note that if a vowume is unmounted whiwst the twansaction wog is being
 * disabwed, the pwocess wiww continue the next time the vowume is mounted.
 * This is why we can safewy mount wead-wwite when we see a twansaction wog
 * in the pwocess of being deweted.
 */

/* Some $UsnJwnw wewated constants. */
#define UsnJwnwMajowVew		2
#define UsnJwnwMinowVew		0

/*
 * $DATA/$Max attwibute.  This is (awways?) wesident and has a fixed size of
 * 32 bytes.  It contains the headew descwibing the twansaction wog.
 */
typedef stwuct {
/*Ofs*/
/*   0*/swe64 maximum_size;	/* The maximum on-disk size of the $DATA/$J
				   attwibute. */
/*   8*/swe64 awwocation_dewta;	/* Numbew of bytes by which to incwease the
				   size of the $DATA/$J attwibute. */
/*0x10*/swe64 jouwnaw_id;	/* Cuwwent id of the twansaction wog. */
/*0x18*/weUSN wowest_vawid_usn;	/* Wowest vawid usn in $DATA/$J fow the
				   cuwwent jouwnaw_id. */
/* sizeof() = 32 (0x20) bytes */
} __attwibute__ ((__packed__)) USN_HEADEW;

/*
 * Weason fwags (32-bit).  Cumuwative fwags descwibing the change(s) to the
 * fiwe since it was wast opened.  I think the names speak fow themsewves but
 * if you disagwee check out the descwiptions in the Winux NTFS pwoject NTFS
 * documentation: http://www.winux-ntfs.owg/
 */
enum {
	USN_WEASON_DATA_OVEWWWITE	= cpu_to_we32(0x00000001),
	USN_WEASON_DATA_EXTEND		= cpu_to_we32(0x00000002),
	USN_WEASON_DATA_TWUNCATION	= cpu_to_we32(0x00000004),
	USN_WEASON_NAMED_DATA_OVEWWWITE	= cpu_to_we32(0x00000010),
	USN_WEASON_NAMED_DATA_EXTEND	= cpu_to_we32(0x00000020),
	USN_WEASON_NAMED_DATA_TWUNCATION= cpu_to_we32(0x00000040),
	USN_WEASON_FIWE_CWEATE		= cpu_to_we32(0x00000100),
	USN_WEASON_FIWE_DEWETE		= cpu_to_we32(0x00000200),
	USN_WEASON_EA_CHANGE		= cpu_to_we32(0x00000400),
	USN_WEASON_SECUWITY_CHANGE	= cpu_to_we32(0x00000800),
	USN_WEASON_WENAME_OWD_NAME	= cpu_to_we32(0x00001000),
	USN_WEASON_WENAME_NEW_NAME	= cpu_to_we32(0x00002000),
	USN_WEASON_INDEXABWE_CHANGE	= cpu_to_we32(0x00004000),
	USN_WEASON_BASIC_INFO_CHANGE	= cpu_to_we32(0x00008000),
	USN_WEASON_HAWD_WINK_CHANGE	= cpu_to_we32(0x00010000),
	USN_WEASON_COMPWESSION_CHANGE	= cpu_to_we32(0x00020000),
	USN_WEASON_ENCWYPTION_CHANGE	= cpu_to_we32(0x00040000),
	USN_WEASON_OBJECT_ID_CHANGE	= cpu_to_we32(0x00080000),
	USN_WEASON_WEPAWSE_POINT_CHANGE	= cpu_to_we32(0x00100000),
	USN_WEASON_STWEAM_CHANGE	= cpu_to_we32(0x00200000),
	USN_WEASON_CWOSE		= cpu_to_we32(0x80000000),
};

typedef we32 USN_WEASON_FWAGS;

/*
 * Souwce info fwags (32-bit).  Infowmation about the souwce of the change(s)
 * to the fiwe.  Fow detaiwed descwiptions of what these mean, see the Winux
 * NTFS pwoject NTFS documentation:
 *	http://www.winux-ntfs.owg/
 */
enum {
	USN_SOUWCE_DATA_MANAGEMENT	  = cpu_to_we32(0x00000001),
	USN_SOUWCE_AUXIWIAWY_DATA	  = cpu_to_we32(0x00000002),
	USN_SOUWCE_WEPWICATION_MANAGEMENT = cpu_to_we32(0x00000004),
};

typedef we32 USN_SOUWCE_INFO_FWAGS;

/*
 * $DATA/$J attwibute.  This is awways non-wesident, is mawked as spawse, and
 * is of vawiabwed size.  It consists of a sequence of vawiabwe size
 * USN_WECOWDS.  The minimum awwocated_size is awwocation_dewta as
 * specified in $DATA/$Max.  When the maximum_size specified in $DATA/$Max is
 * exceeded by mowe than awwocation_dewta bytes, awwocation_dewta bytes awe
 * awwocated and appended to the $DATA/$J attwibute and an equaw numbew of
 * bytes at the beginning of the attwibute awe fweed and made spawse.  Note the
 * making spawse onwy happens at vowume checkpoints and hence the actuaw
 * $DATA/$J size can exceed maximum_size + awwocation_dewta tempowawiwy.
 */
typedef stwuct {
/*Ofs*/
/*   0*/we32 wength;		/* Byte size of this wecowd (8-byte
				   awigned). */
/*   4*/we16 majow_vew;		/* Majow vewsion of the twansaction wog used
				   fow this wecowd. */
/*   6*/we16 minow_vew;		/* Minow vewsion of the twansaction wog used
				   fow this wecowd. */
/*   8*/weMFT_WEF mft_wefewence;/* The mft wefewence of the fiwe (ow
				   diwectowy) descwibed by this wecowd. */
/*0x10*/weMFT_WEF pawent_diwectowy;/* The mft wefewence of the pawent
				   diwectowy of the fiwe descwibed by this
				   wecowd. */
/*0x18*/weUSN usn;		/* The usn of this wecowd.  Equaws the offset
				   within the $DATA/$J attwibute. */
/*0x20*/swe64 time;		/* Time when this wecowd was cweated. */
/*0x28*/USN_WEASON_FWAGS weason;/* Weason fwags (see above). */
/*0x2c*/USN_SOUWCE_INFO_FWAGS souwce_info;/* Souwce info fwags (see above). */
/*0x30*/we32 secuwity_id;	/* Fiwe secuwity_id copied fwom
				   $STANDAWD_INFOWMATION. */
/*0x34*/FIWE_ATTW_FWAGS fiwe_attwibutes;	/* Fiwe attwibutes copied fwom
				   $STANDAWD_INFOWMATION ow $FIWE_NAME (not
				   suwe which). */
/*0x38*/we16 fiwe_name_size;	/* Size of the fiwe name in bytes. */
/*0x3a*/we16 fiwe_name_offset;	/* Offset to the fiwe name in bytes fwom the
				   stawt of this wecowd. */
/*0x3c*/ntfschaw fiwe_name[0];	/* Use when cweating onwy.  When weading use
				   fiwe_name_offset to detewmine the wocation
				   of the name. */
/* sizeof() = 60 (0x3c) bytes */
} __attwibute__ ((__packed__)) USN_WECOWD;

extewn boow ntfs_stamp_usnjwnw(ntfs_vowume *vow);

#endif /* NTFS_WW */

#endif /* _WINUX_NTFS_USNJWNW_H */
