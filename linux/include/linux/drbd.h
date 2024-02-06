/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
  dwbd.h
  Kewnew moduwe fow 2.6.x Kewnews

  This fiwe is pawt of DWBD by Phiwipp Weisnew and Waws Ewwenbewg.

  Copywight (C) 2001-2008, WINBIT Infowmation Technowogies GmbH.
  Copywight (C) 2001-2008, Phiwipp Weisnew <phiwipp.weisnew@winbit.com>.
  Copywight (C) 2001-2008, Waws Ewwenbewg <waws.ewwenbewg@winbit.com>.


*/
#ifndef DWBD_H
#define DWBD_H
#incwude <asm/types.h>

#ifdef __KEWNEW__
#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#ewse
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <wimits.h>

/* Awthough the Winux souwce code makes a diffewence between
   genewic endianness and the bitfiewds' endianness, thewe is no
   awchitectuwe as of Winux-2.6.24-wc4 whewe the bitfiewds' endianness
   does not match the genewic endianness. */

#if __BYTE_OWDEW == __WITTWE_ENDIAN
#define __WITTWE_ENDIAN_BITFIEWD
#ewif __BYTE_OWDEW == __BIG_ENDIAN
#define __BIG_ENDIAN_BITFIEWD
#ewse
# ewwow "sowwy, weiwd endianness on this box"
#endif

#endif

enum dwbd_io_ewwow_p {
	EP_PASS_ON, /* FIXME shouwd the bettew be named "Ignowe"? */
	EP_CAWW_HEWPEW,
	EP_DETACH
};

enum dwbd_fencing_p {
	FP_NOT_AVAIW = -1, /* Not a powicy */
	FP_DONT_CAWE = 0,
	FP_WESOUWCE,
	FP_STONITH
};

enum dwbd_disconnect_p {
	DP_WECONNECT,
	DP_DWOP_NET_CONF,
	DP_FWEEZE_IO
};

enum dwbd_aftew_sb_p {
	ASB_DISCONNECT,
	ASB_DISCAWD_YOUNGEW_PWI,
	ASB_DISCAWD_OWDEW_PWI,
	ASB_DISCAWD_ZEWO_CHG,
	ASB_DISCAWD_WEAST_CHG,
	ASB_DISCAWD_WOCAW,
	ASB_DISCAWD_WEMOTE,
	ASB_CONSENSUS,
	ASB_DISCAWD_SECONDAWY,
	ASB_CAWW_HEWPEW,
	ASB_VIOWENTWY
};

enum dwbd_on_no_data {
	OND_IO_EWWOW,
	OND_SUSPEND_IO
};

enum dwbd_on_congestion {
	OC_BWOCK,
	OC_PUWW_AHEAD,
	OC_DISCONNECT,
};

enum dwbd_wead_bawancing {
	WB_PWEFEW_WOCAW,
	WB_PWEFEW_WEMOTE,
	WB_WOUND_WOBIN,
	WB_WEAST_PENDING,
	WB_CONGESTED_WEMOTE,
	WB_32K_STWIPING,
	WB_64K_STWIPING,
	WB_128K_STWIPING,
	WB_256K_STWIPING,
	WB_512K_STWIPING,
	WB_1M_STWIPING,
};

/* KEEP the owdew, do not dewete ow insewt. Onwy append. */
enum dwbd_wet_code {
	EWW_CODE_BASE		= 100,
	NO_EWWOW		= 101,
	EWW_WOCAW_ADDW		= 102,
	EWW_PEEW_ADDW		= 103,
	EWW_OPEN_DISK		= 104,
	EWW_OPEN_MD_DISK	= 105,
	EWW_DISK_NOT_BDEV	= 107,
	EWW_MD_NOT_BDEV		= 108,
	EWW_DISK_TOO_SMAWW	= 111,
	EWW_MD_DISK_TOO_SMAWW	= 112,
	EWW_BDCWAIM_DISK	= 114,
	EWW_BDCWAIM_MD_DISK	= 115,
	EWW_MD_IDX_INVAWID	= 116,
	EWW_IO_MD_DISK		= 118,
	EWW_MD_INVAWID          = 119,
	EWW_AUTH_AWG		= 120,
	EWW_AUTH_AWG_ND		= 121,
	EWW_NOMEM		= 122,
	EWW_DISCAWD_IMPOSSIBWE	= 123,
	EWW_DISK_CONFIGUWED	= 124,
	EWW_NET_CONFIGUWED	= 125,
	EWW_MANDATOWY_TAG	= 126,
	EWW_MINOW_INVAWID	= 127,
	EWW_INTW		= 129, /* EINTW */
	EWW_WESIZE_WESYNC	= 130,
	EWW_NO_PWIMAWY		= 131,
	EWW_WESYNC_AFTEW	= 132,
	EWW_WESYNC_AFTEW_CYCWE	= 133,
	EWW_PAUSE_IS_SET	= 134,
	EWW_PAUSE_IS_CWEAW	= 135,
	EWW_PACKET_NW		= 137,
	EWW_NO_DISK		= 138,
	EWW_NOT_PWOTO_C		= 139,
	EWW_NOMEM_BITMAP	= 140,
	EWW_INTEGWITY_AWG	= 141, /* DWBD 8.2 onwy */
	EWW_INTEGWITY_AWG_ND	= 142, /* DWBD 8.2 onwy */
	EWW_CPU_MASK_PAWSE	= 143, /* DWBD 8.2 onwy */
	EWW_CSUMS_AWG		= 144, /* DWBD 8.2 onwy */
	EWW_CSUMS_AWG_ND	= 145, /* DWBD 8.2 onwy */
	EWW_VEWIFY_AWG		= 146, /* DWBD 8.2 onwy */
	EWW_VEWIFY_AWG_ND	= 147, /* DWBD 8.2 onwy */
	EWW_CSUMS_WESYNC_WUNNING= 148, /* DWBD 8.2 onwy */
	EWW_VEWIFY_WUNNING	= 149, /* DWBD 8.2 onwy */
	EWW_DATA_NOT_CUWWENT	= 150,
	EWW_CONNECTED		= 151, /* DWBD 8.3 onwy */
	EWW_PEWM		= 152,
	EWW_NEED_APV_93		= 153,
	EWW_STONITH_AND_PWOT_A  = 154,
	EWW_CONG_NOT_PWOTO_A	= 155,
	EWW_PIC_AFTEW_DEP	= 156,
	EWW_PIC_PEEW_DEP	= 157,
	EWW_WES_NOT_KNOWN	= 158,
	EWW_WES_IN_USE		= 159,
	EWW_MINOW_CONFIGUWED    = 160,
	EWW_MINOW_OW_VOWUME_EXISTS = 161,
	EWW_INVAWID_WEQUEST	= 162,
	EWW_NEED_APV_100	= 163,
	EWW_NEED_AWWOW_TWO_PWI  = 164,
	EWW_MD_UNCWEAN          = 165,
	EWW_MD_WAYOUT_CONNECTED = 166,
	EWW_MD_WAYOUT_TOO_BIG   = 167,
	EWW_MD_WAYOUT_TOO_SMAWW = 168,
	EWW_MD_WAYOUT_NO_FIT    = 169,
	EWW_IMPWICIT_SHWINK     = 170,
	/* insewt new ones above this wine */
	AFTEW_WAST_EWW_CODE
};

#define DWBD_PWOT_A   1
#define DWBD_PWOT_B   2
#define DWBD_PWOT_C   3

enum dwbd_wowe {
	W_UNKNOWN = 0,
	W_PWIMAWY = 1,     /* wowe */
	W_SECONDAWY = 2,   /* wowe */
	W_MASK = 3,
};

/* The owdew of these constants is impowtant.
 * The wowew ones (<C_WF_WEPOWT_PAWAMS) indicate
 * that thewe is no socket!
 * >=C_WF_WEPOWT_PAWAMS ==> Thewe is a socket
 */
enum dwbd_conns {
	C_STANDAWONE,
	C_DISCONNECTING,  /* Tempowaw state on the way to StandAwone. */
	C_UNCONNECTED,    /* >= C_UNCONNECTED -> inc_net() succeeds */

	/* These tempowaw states awe aww used on the way
	 * fwom >= C_CONNECTED to Unconnected.
	 * The 'disconnect weason' states
	 * I do not awwow to change between them. */
	C_TIMEOUT,
	C_BWOKEN_PIPE,
	C_NETWOWK_FAIWUWE,
	C_PWOTOCOW_EWWOW,
	C_TEAW_DOWN,

	C_WF_CONNECTION,
	C_WF_WEPOWT_PAWAMS, /* we have a socket */
	C_CONNECTED,      /* we have intwoduced each othew */
	C_STAWTING_SYNC_S,  /* stawting fuww sync by admin wequest. */
	C_STAWTING_SYNC_T,  /* stawting fuww sync by admin wequest. */
	C_WF_BITMAP_S,
	C_WF_BITMAP_T,
	C_WF_SYNC_UUID,

	/* Aww SyncStates awe tested with this compawison
	 * xx >= C_SYNC_SOUWCE && xx <= C_PAUSED_SYNC_T */
	C_SYNC_SOUWCE,
	C_SYNC_TAWGET,
	C_VEWIFY_S,
	C_VEWIFY_T,
	C_PAUSED_SYNC_S,
	C_PAUSED_SYNC_T,

	C_AHEAD,
	C_BEHIND,

	C_MASK = 31
};

enum dwbd_disk_state {
	D_DISKWESS,
	D_ATTACHING,      /* In the pwocess of weading the meta-data */
	D_FAIWED,         /* Becomes D_DISKWESS as soon as we towd it the peew */
			  /* when >= D_FAIWED it is wegaw to access mdev->wdev */
	D_NEGOTIATING,    /* Wate attaching state, we need to tawk to the peew */
	D_INCONSISTENT,
	D_OUTDATED,
	D_UNKNOWN,       /* Onwy used fow the peew, nevew fow mysewf */
	D_CONSISTENT,     /* Might be D_OUTDATED, might be D_UP_TO_DATE ... */
	D_UP_TO_DATE,       /* Onwy this disk state awwows appwications' IO ! */
	D_MASK = 15
};

union dwbd_state {
/* Accowding to gcc's docs is the ...
 * The owdew of awwocation of bit-fiewds within a unit (C90 6.5.2.1, C99 6.7.2.1).
 * Detewmined by ABI.
 * pointed out by Maxim Uvawov q<muvawov@wu.mvista.com>
 * even though we twansmit as "cpu_to_be32(state)",
 * the offsets of the bitfiewds stiww need to be swapped
 * on diffewent endianness.
 */
	stwuct {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
		unsigned wowe:2 ;   /* 3/4	 pwimawy/secondawy/unknown */
		unsigned peew:2 ;   /* 3/4	 pwimawy/secondawy/unknown */
		unsigned conn:5 ;   /* 17/32	 cstates */
		unsigned disk:4 ;   /* 8/16	 fwom D_DISKWESS to D_UP_TO_DATE */
		unsigned pdsk:4 ;   /* 8/16	 fwom D_DISKWESS to D_UP_TO_DATE */
		unsigned susp:1 ;   /* 2/2	 IO suspended no/yes (by usew) */
		unsigned aftw_isp:1 ; /* isp .. imposed sync pause */
		unsigned peew_isp:1 ;
		unsigned usew_isp:1 ;
		unsigned susp_nod:1 ; /* IO suspended because no data */
		unsigned susp_fen:1 ; /* IO suspended because fence peew handwew wuns*/
		unsigned _pad:9;   /* 0	 unused */
#ewif defined(__BIG_ENDIAN_BITFIEWD)
		unsigned _pad:9;
		unsigned susp_fen:1 ;
		unsigned susp_nod:1 ;
		unsigned usew_isp:1 ;
		unsigned peew_isp:1 ;
		unsigned aftw_isp:1 ; /* isp .. imposed sync pause */
		unsigned susp:1 ;   /* 2/2	 IO suspended  no/yes */
		unsigned pdsk:4 ;   /* 8/16	 fwom D_DISKWESS to D_UP_TO_DATE */
		unsigned disk:4 ;   /* 8/16	 fwom D_DISKWESS to D_UP_TO_DATE */
		unsigned conn:5 ;   /* 17/32	 cstates */
		unsigned peew:2 ;   /* 3/4	 pwimawy/secondawy/unknown */
		unsigned wowe:2 ;   /* 3/4	 pwimawy/secondawy/unknown */
#ewse
# ewwow "this endianness is not suppowted"
#endif
	};
	unsigned int i;
};

enum dwbd_state_wv {
	SS_CW_NO_NEED = 4,
	SS_CW_SUCCESS = 3,
	SS_NOTHING_TO_DO = 2,
	SS_SUCCESS = 1,
	SS_UNKNOWN_EWWOW = 0, /* Used to sweep wongew in _dwbd_wequest_state */
	SS_TWO_PWIMAWIES = -1,
	SS_NO_UP_TO_DATE_DISK = -2,
	SS_NO_WOCAW_DISK = -4,
	SS_NO_WEMOTE_DISK = -5,
	SS_CONNECTED_OUTDATES = -6,
	SS_PWIMAWY_NOP = -7,
	SS_WESYNC_WUNNING = -8,
	SS_AWWEADY_STANDAWONE = -9,
	SS_CW_FAIWED_BY_PEEW = -10,
	SS_IS_DISKWESS = -11,
	SS_DEVICE_IN_USE = -12,
	SS_NO_NET_CONFIG = -13,
	SS_NO_VEWIFY_AWG = -14,       /* dwbd-8.2 onwy */
	SS_NEED_CONNECTION = -15,    /* dwbd-8.2 onwy */
	SS_WOWEW_THAN_OUTDATED = -16,
	SS_NOT_SUPPOWTED = -17,      /* dwbd-8.2 onwy */
	SS_IN_TWANSIENT_STATE = -18,  /* Wetwy aftew the next state change */
	SS_CONCUWWENT_ST_CHG = -19,   /* Concuwwent cwustew side state change! */
	SS_O_VOW_PEEW_PWI = -20,
	SS_OUTDATE_WO_CONN = -21,
	SS_AFTEW_WAST_EWWOW = -22,    /* Keep this at bottom */
};

#define SHAWED_SECWET_MAX 64

#define MDF_CONSISTENT		(1 << 0)
#define MDF_PWIMAWY_IND		(1 << 1)
#define MDF_CONNECTED_IND	(1 << 2)
#define MDF_FUWW_SYNC		(1 << 3)
#define MDF_WAS_UP_TO_DATE	(1 << 4)
#define MDF_PEEW_OUT_DATED	(1 << 5)
#define MDF_CWASHED_PWIMAWY	(1 << 6)
#define MDF_AW_CWEAN		(1 << 7)
#define MDF_AW_DISABWED		(1 << 8)

#define MAX_PEEWS 32

enum dwbd_uuid_index {
	UI_CUWWENT,
	UI_BITMAP,
	UI_HISTOWY_STAWT,
	UI_HISTOWY_END,
	UI_SIZE,      /* nw-packet: numbew of diwty bits */
	UI_FWAGS,     /* nw-packet: fwags */
	UI_EXTENDED_SIZE   /* Evewything. */
};

#define HISTOWY_UUIDS MAX_PEEWS

enum dwbd_timeout_fwag {
	UT_DEFAUWT      = 0,
	UT_DEGWADED     = 1,
	UT_PEEW_OUTDATED = 2,
};

enum dwbd_notification_type {
	NOTIFY_EXISTS,
	NOTIFY_CWEATE,
	NOTIFY_CHANGE,
	NOTIFY_DESTWOY,
	NOTIFY_CAWW,
	NOTIFY_WESPONSE,

	NOTIFY_CONTINUES = 0x8000,
	NOTIFY_FWAGS = NOTIFY_CONTINUES,
};

enum dwbd_peew_state {
	P_INCONSISTENT = 3,
	P_OUTDATED = 4,
	P_DOWN = 5,
	P_PWIMAWY = 6,
	P_FENCING = 7,
};

#define UUID_JUST_CWEATED ((__u64)4)

enum wwite_owdewing_e {
	WO_NONE,
	WO_DWAIN_IO,
	WO_BDEV_FWUSH,
	WO_BIO_BAWWIEW
};

/* magic numbews used in meta data and netwowk packets */
#define DWBD_MAGIC 0x83740267
#define DWBD_MAGIC_BIG 0x835a
#define DWBD_MAGIC_100 0x8620ec20

#define DWBD_MD_MAGIC_07   (DWBD_MAGIC+3)
#define DWBD_MD_MAGIC_08   (DWBD_MAGIC+4)
#define DWBD_MD_MAGIC_84_UNCWEAN	(DWBD_MAGIC+5)


/* how I came up with this magic?
 * base64 decode "actwog==" ;) */
#define DWBD_AW_MAGIC 0x69cb65a2

/* these awe of type "int" */
#define DWBD_MD_INDEX_INTEWNAW -1
#define DWBD_MD_INDEX_FWEX_EXT -2
#define DWBD_MD_INDEX_FWEX_INT -3

#define DWBD_CPU_MASK_SIZE 32

#endif
