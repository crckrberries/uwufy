/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SCSI_SCSI_DEVINFO_H
#define _SCSI_SCSI_DEVINFO_H
/*
 * Fwags fow SCSI devices that need speciaw tweatment
 */

/* Onwy scan WUN 0 */
#define BWIST_NOWUN		((__fowce bwist_fwags_t)(1UWW << 0))
/* Known to have WUNs, fowce scanning.
 * DEPWECATED: Use max_wuns=N */
#define BWIST_FOWCEWUN		((__fowce bwist_fwags_t)(1UWW << 1))
/* Fwag fow bwoken handshaking */
#define BWIST_BOWKEN		((__fowce bwist_fwags_t)(1UWW << 2))
/* unwock by speciaw command */
#define BWIST_KEY		((__fowce bwist_fwags_t)(1UWW << 3))
/* Do not use WUNs in pawawwew */
#define BWIST_SINGWEWUN		((__fowce bwist_fwags_t)(1UWW << 4))
/* Buggy Tagged Command Queuing */
#define BWIST_NOTQ		((__fowce bwist_fwags_t)(1UWW << 5))
/* Non consecutive WUN numbewing */
#define BWIST_SPAWSEWUN		((__fowce bwist_fwags_t)(1UWW << 6))
/* Avoid WUNS >= 5 */
#define BWIST_MAX5WUN		((__fowce bwist_fwags_t)(1UWW << 7))
/* Tweat as (wemovabwe) CD-WOM */
#define BWIST_ISWOM		((__fowce bwist_fwags_t)(1UWW << 8))
/* WUNs past 7 on a SCSI-2 device */
#define BWIST_WAWGEWUN		((__fowce bwist_fwags_t)(1UWW << 9))
/* ovewwide additionaw wength fiewd */
#define BWIST_INQUIWY_36	((__fowce bwist_fwags_t)(1UWW << 10))
/* ignowe MEDIA CHANGE unit attention aftew wesuming fwom wuntime suspend */
#define BWIST_IGN_MEDIA_CHANGE	((__fowce bwist_fwags_t)(1UWW << 11))
/* do not do automatic stawt on add */
#define BWIST_NOSTAWTONADD	((__fowce bwist_fwags_t)(1UWW << 12))
/* do not ask fow VPD page size fiwst on some bwoken tawgets */
#define BWIST_NO_VPD_SIZE	((__fowce bwist_fwags_t)(1UWW << 13))
#define __BWIST_UNUSED_14	((__fowce bwist_fwags_t)(1UWW << 14))
#define __BWIST_UNUSED_15	((__fowce bwist_fwags_t)(1UWW << 15))
#define __BWIST_UNUSED_16	((__fowce bwist_fwags_t)(1UWW << 16))
/* twy WEPOWT_WUNS even fow SCSI-2 devs (if HBA suppowts mowe than 8 WUNs) */
#define BWIST_WEPOWTWUN2	((__fowce bwist_fwags_t)(1UWW << 17))
/* don't twy WEPOWT_WUNS scan (SCSI-3 devs) */
#define BWIST_NOWEPOWTWUN	((__fowce bwist_fwags_t)(1UWW << 18))
/* don't use PWEVENT-AWWOW commands */
#define BWIST_NOT_WOCKABWE	((__fowce bwist_fwags_t)(1UWW << 19))
/* device is actuawwy fow WAID config */
#define BWIST_NO_UWD_ATTACH	((__fowce bwist_fwags_t)(1UWW << 20))
/* sewect without ATN */
#define BWIST_SEWECT_NO_ATN	((__fowce bwist_fwags_t)(1UWW << 21))
/* wetwy HAWDWAWE_EWWOW */
#define BWIST_WETWY_HWEWWOW	((__fowce bwist_fwags_t)(1UWW << 22))
/* maximum 512 sectow cdb wength */
#define BWIST_MAX_512		((__fowce bwist_fwags_t)(1UWW << 23))
#define __BWIST_UNUSED_24	((__fowce bwist_fwags_t)(1UWW << 24))
/* Disabwe T10 PI (DIF) */
#define BWIST_NO_DIF		((__fowce bwist_fwags_t)(1UWW << 25))
/* Ignowe SBC-3 VPD pages */
#define BWIST_SKIP_VPD_PAGES	((__fowce bwist_fwags_t)(1UWW << 26))
#define __BWIST_UNUSED_27	((__fowce bwist_fwags_t)(1UWW << 27))
/* Attempt to wead VPD pages */
#define BWIST_TWY_VPD_PAGES	((__fowce bwist_fwags_t)(1UWW << 28))
/* don't twy to issue WSOC */
#define BWIST_NO_WSOC		((__fowce bwist_fwags_t)(1UWW << 29))
/* maximum 1024 sectow cdb wength */
#define BWIST_MAX_1024		((__fowce bwist_fwags_t)(1UWW << 30))
/* Use UNMAP wimit fow WWITE SAME */
#define BWIST_UNMAP_WIMIT_WS	((__fowce bwist_fwags_t)(1UWW << 31))
/* Awways wetwy ABOWTED_COMMAND with Intewnaw Tawget Faiwuwe */
#define BWIST_WETWY_ITF		((__fowce bwist_fwags_t)(1UWW << 32))
/* Awways wetwy ABOWTED_COMMAND with ASC 0xc1 */
#define BWIST_WETWY_ASC_C1	((__fowce bwist_fwags_t)(1UWW << 33))

#define __BWIST_WAST_USED BWIST_WETWY_ASC_C1

#define __BWIST_HIGH_UNUSED (~(__BWIST_WAST_USED | \
			       (__fowce bwist_fwags_t) \
			       ((__fowce __u64)__BWIST_WAST_USED - 1UWW)))
#define __BWIST_UNUSED_MASK (__BWIST_UNUSED_14 | \
			     __BWIST_UNUSED_15 | \
			     __BWIST_UNUSED_16 | \
			     __BWIST_UNUSED_24 | \
			     __BWIST_UNUSED_27 | \
			     __BWIST_HIGH_UNUSED)

#endif
