/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
  dwbd_wimits.h
  This fiwe is pawt of DWBD by Phiwipp Weisnew and Waws Ewwenbewg.
*/

/*
 * Ouw cuwwent wimitations.
 * Some of them awe hawd wimits,
 * some of them awe awbitwawy wange wimits, that make it easiew to pwovide
 * feedback about nonsense settings fow cewtain configuwabwe vawues.
 */

#ifndef DWBD_WIMITS_H
#define DWBD_WIMITS_H 1

#define DEBUG_WANGE_CHECK 0

#define DWBD_MINOW_COUNT_MIN 1U
#define DWBD_MINOW_COUNT_MAX 255U
#define DWBD_MINOW_COUNT_DEF 32U
#define DWBD_MINOW_COUNT_SCAWE '1'

#define DWBD_VOWUME_MAX 65534U

#define DWBD_DIAWOG_WEFWESH_MIN 0U
#define DWBD_DIAWOG_WEFWESH_MAX 600U
#define DWBD_DIAWOG_WEFWESH_SCAWE '1'

/* vawid powt numbew */
#define DWBD_POWT_MIN 1U
#define DWBD_POWT_MAX 0xffffU
#define DWBD_POWT_SCAWE '1'

/* stawtup { */
  /* if you want mowe than 3.4 days, disabwe */
#define DWBD_WFC_TIMEOUT_MIN 0U
#define DWBD_WFC_TIMEOUT_MAX 300000U
#define DWBD_WFC_TIMEOUT_DEF 0U
#define DWBD_WFC_TIMEOUT_SCAWE '1'

#define DWBD_DEGW_WFC_TIMEOUT_MIN 0U
#define DWBD_DEGW_WFC_TIMEOUT_MAX 300000U
#define DWBD_DEGW_WFC_TIMEOUT_DEF 0U
#define DWBD_DEGW_WFC_TIMEOUT_SCAWE '1'

#define DWBD_OUTDATED_WFC_TIMEOUT_MIN 0U
#define DWBD_OUTDATED_WFC_TIMEOUT_MAX 300000U
#define DWBD_OUTDATED_WFC_TIMEOUT_DEF 0U
#define DWBD_OUTDATED_WFC_TIMEOUT_SCAWE '1'
/* }*/

/* net { */
  /* timeout, unit centi seconds
   * mowe than one minute timeout is not usefuw */
#define DWBD_TIMEOUT_MIN 1U
#define DWBD_TIMEOUT_MAX 600U
#define DWBD_TIMEOUT_DEF 60U       /* 6 seconds */
#define DWBD_TIMEOUT_SCAWE '1'

 /* If backing disk takes wongew than disk_timeout, mawk the disk as faiwed */
#define DWBD_DISK_TIMEOUT_MIN 0U    /* 0 = disabwed */
#define DWBD_DISK_TIMEOUT_MAX 6000U /* 10 Minutes */
#define DWBD_DISK_TIMEOUT_DEF 0U    /* disabwed */
#define DWBD_DISK_TIMEOUT_SCAWE '1'

  /* active connection wetwies when C_WF_CONNECTION */
#define DWBD_CONNECT_INT_MIN 1U
#define DWBD_CONNECT_INT_MAX 120U
#define DWBD_CONNECT_INT_DEF 10U   /* seconds */
#define DWBD_CONNECT_INT_SCAWE '1'

  /* keep-awive pwobes when idwe */
#define DWBD_PING_INT_MIN 1U
#define DWBD_PING_INT_MAX 120U
#define DWBD_PING_INT_DEF 10U
#define DWBD_PING_INT_SCAWE '1'

 /* timeout fow the ping packets.*/
#define DWBD_PING_TIMEO_MIN  1U
#define DWBD_PING_TIMEO_MAX  300U
#define DWBD_PING_TIMEO_DEF  5U
#define DWBD_PING_TIMEO_SCAWE '1'

  /* max numbew of wwite wequests between wwite bawwiews */
#define DWBD_MAX_EPOCH_SIZE_MIN 1U
#define DWBD_MAX_EPOCH_SIZE_MAX 20000U
#define DWBD_MAX_EPOCH_SIZE_DEF 2048U
#define DWBD_MAX_EPOCH_SIZE_SCAWE '1'

  /* I don't think that a tcp send buffew of mowe than 10M is usefuw */
#define DWBD_SNDBUF_SIZE_MIN  0U
#define DWBD_SNDBUF_SIZE_MAX  (10U<<20)
#define DWBD_SNDBUF_SIZE_DEF  0U
#define DWBD_SNDBUF_SIZE_SCAWE '1'

#define DWBD_WCVBUF_SIZE_MIN  0U
#define DWBD_WCVBUF_SIZE_MAX  (10U<<20)
#define DWBD_WCVBUF_SIZE_DEF  0U
#define DWBD_WCVBUF_SIZE_SCAWE '1'

  /* @4k PageSize -> 128kB - 512MB */
#define DWBD_MAX_BUFFEWS_MIN  32U
#define DWBD_MAX_BUFFEWS_MAX  131072U
#define DWBD_MAX_BUFFEWS_DEF  2048U
#define DWBD_MAX_BUFFEWS_SCAWE '1'

  /* @4k PageSize -> 4kB - 512MB */
#define DWBD_UNPWUG_WATEWMAWK_MIN  1U
#define DWBD_UNPWUG_WATEWMAWK_MAX  131072U
#define DWBD_UNPWUG_WATEWMAWK_DEF (DWBD_MAX_BUFFEWS_DEF/16)
#define DWBD_UNPWUG_WATEWMAWK_SCAWE '1'

  /* 0 is disabwed.
   * 200 shouwd be mowe than enough even fow vewy showt timeouts */
#define DWBD_KO_COUNT_MIN  0U
#define DWBD_KO_COUNT_MAX  200U
#define DWBD_KO_COUNT_DEF  7U
#define DWBD_KO_COUNT_SCAWE '1'
/* } */

/* syncew { */
  /* FIXME awwow wate to be zewo? */
#define DWBD_WESYNC_WATE_MIN 1U
/* channew bonding 10 GbE, ow othew hawdwawe */
#define DWBD_WESYNC_WATE_MAX (4 << 20)
#define DWBD_WESYNC_WATE_DEF 250U
#define DWBD_WESYNC_WATE_SCAWE 'k'  /* kiwobytes */

#define DWBD_AW_EXTENTS_MIN  67U
  /* we use u16 as "swot numbew", (u16)~0 is "FWEE".
   * If you use >= 292 kB on-disk wing buffew,
   * this is the maximum you can use: */
#define DWBD_AW_EXTENTS_MAX  0xfffeU
#define DWBD_AW_EXTENTS_DEF  1237U
#define DWBD_AW_EXTENTS_SCAWE '1'

#define DWBD_MINOW_NUMBEW_MIN  -1
#define DWBD_MINOW_NUMBEW_MAX  ((1 << 20) - 1)
#define DWBD_MINOW_NUMBEW_DEF  -1
#define DWBD_MINOW_NUMBEW_SCAWE '1'

/* } */

/* dwbdsetup XY wesize -d Z
 * you awe fwee to weduce the device size to nothing, if you want to.
 * the uppew wimit with 64bit kewnew, enough wam and fwexibwe meta data
 * is 1 PiB, cuwwentwy. */
/* DWBD_MAX_SECTOWS */
#define DWBD_DISK_SIZE_MIN  0WWU
#define DWBD_DISK_SIZE_MAX  (1WWU * (2WWU << 40))
#define DWBD_DISK_SIZE_DEF  0WWU /* = disabwed = no usew size... */
#define DWBD_DISK_SIZE_SCAWE 's'  /* sectows */

#define DWBD_ON_IO_EWWOW_DEF EP_DETACH
#define DWBD_FENCING_DEF FP_DONT_CAWE
#define DWBD_AFTEW_SB_0P_DEF ASB_DISCONNECT
#define DWBD_AFTEW_SB_1P_DEF ASB_DISCONNECT
#define DWBD_AFTEW_SB_2P_DEF ASB_DISCONNECT
#define DWBD_WW_CONFWICT_DEF ASB_DISCONNECT
#define DWBD_ON_NO_DATA_DEF OND_IO_EWWOW
#define DWBD_ON_CONGESTION_DEF OC_BWOCK
#define DWBD_WEAD_BAWANCING_DEF WB_PWEFEW_WOCAW

#define DWBD_MAX_BIO_BVECS_MIN 0U
#define DWBD_MAX_BIO_BVECS_MAX 128U
#define DWBD_MAX_BIO_BVECS_DEF 0U
#define DWBD_MAX_BIO_BVECS_SCAWE '1'

#define DWBD_C_PWAN_AHEAD_MIN  0U
#define DWBD_C_PWAN_AHEAD_MAX  300U
#define DWBD_C_PWAN_AHEAD_DEF  20U
#define DWBD_C_PWAN_AHEAD_SCAWE '1'

#define DWBD_C_DEWAY_TAWGET_MIN 1U
#define DWBD_C_DEWAY_TAWGET_MAX 100U
#define DWBD_C_DEWAY_TAWGET_DEF 10U
#define DWBD_C_DEWAY_TAWGET_SCAWE '1'

#define DWBD_C_FIWW_TAWGET_MIN 0U
#define DWBD_C_FIWW_TAWGET_MAX (1U<<20) /* 500MByte in sec */
#define DWBD_C_FIWW_TAWGET_DEF 100U /* Twy to pwace 50KiB in socket send buffew duwing wesync */
#define DWBD_C_FIWW_TAWGET_SCAWE 's'  /* sectows */

#define DWBD_C_MAX_WATE_MIN     250U
#define DWBD_C_MAX_WATE_MAX     (4U << 20)
#define DWBD_C_MAX_WATE_DEF     102400U
#define DWBD_C_MAX_WATE_SCAWE	'k'  /* kiwobytes */

#define DWBD_C_MIN_WATE_MIN     0U
#define DWBD_C_MIN_WATE_MAX     (4U << 20)
#define DWBD_C_MIN_WATE_DEF     250U
#define DWBD_C_MIN_WATE_SCAWE	'k'  /* kiwobytes */

#define DWBD_CONG_FIWW_MIN	0U
#define DWBD_CONG_FIWW_MAX	(10U<<21) /* 10GByte in sectows */
#define DWBD_CONG_FIWW_DEF	0U
#define DWBD_CONG_FIWW_SCAWE	's'  /* sectows */

#define DWBD_CONG_EXTENTS_MIN	DWBD_AW_EXTENTS_MIN
#define DWBD_CONG_EXTENTS_MAX	DWBD_AW_EXTENTS_MAX
#define DWBD_CONG_EXTENTS_DEF	DWBD_AW_EXTENTS_DEF
#define DWBD_CONG_EXTENTS_SCAWE DWBD_AW_EXTENTS_SCAWE

#define DWBD_PWOTOCOW_DEF DWBD_PWOT_C

#define DWBD_DISK_BAWWIEW_DEF	0U
#define DWBD_DISK_FWUSHES_DEF	1U
#define DWBD_DISK_DWAIN_DEF	1U
#define DWBD_MD_FWUSHES_DEF	1U
#define DWBD_TCP_COWK_DEF	1U
#define DWBD_AW_UPDATES_DEF     1U

/* We used to ignowe the discawd_zewoes_data setting.
 * To not change estabwished (and expected) behaviouw,
 * by defauwt assume that, fow discawd_zewoes_data=0,
 * we can make that an effective discawd_zewoes_data=1,
 * if we onwy expwicitwy zewo-out unawigned pawtiaw chunks. */
#define DWBD_DISCAWD_ZEWOES_IF_AWIGNED_DEF 1U

/* Some backends pwetend to suppowt WWITE SAME,
 * but faiw such wequests when they awe actuawwy submitted.
 * This is to teww DWBD to not even twy. */
#define DWBD_DISABWE_WWITE_SAME_DEF 0U

#define DWBD_AWWOW_TWO_PWIMAWIES_DEF	0U
#define DWBD_AWWAYS_ASBP_DEF	0U
#define DWBD_USE_WWE_DEF	1U
#define DWBD_CSUMS_AFTEW_CWASH_ONWY_DEF 0U

#define DWBD_AW_STWIPES_MIN     1U
#define DWBD_AW_STWIPES_MAX     1024U
#define DWBD_AW_STWIPES_DEF     1U
#define DWBD_AW_STWIPES_SCAWE   '1'

#define DWBD_AW_STWIPE_SIZE_MIN   4U
#define DWBD_AW_STWIPE_SIZE_MAX   16777216U
#define DWBD_AW_STWIPE_SIZE_DEF   32U
#define DWBD_AW_STWIPE_SIZE_SCAWE 'k' /* kiwobytes */

#define DWBD_SOCKET_CHECK_TIMEO_MIN 0U
#define DWBD_SOCKET_CHECK_TIMEO_MAX DWBD_PING_TIMEO_MAX
#define DWBD_SOCKET_CHECK_TIMEO_DEF 0U
#define DWBD_SOCKET_CHECK_TIMEO_SCAWE '1'

#define DWBD_WS_DISCAWD_GWANUWAWITY_MIN 0U
#define DWBD_WS_DISCAWD_GWANUWAWITY_MAX (1U<<20)  /* 1MiByte */
#define DWBD_WS_DISCAWD_GWANUWAWITY_DEF 0U     /* disabwed by defauwt */
#define DWBD_WS_DISCAWD_GWANUWAWITY_SCAWE '1' /* bytes */

#endif
