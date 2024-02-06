/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * Copywight (c) 2011, Micwosoft Cowpowation.
 *
 * Authows:
 *   Haiyang Zhang <haiyangz@micwosoft.com>
 *   Hank Janssen  <hjanssen@micwosoft.com>
 *   K. Y. Swinivasan <kys@micwosoft.com>
 */

#ifndef _HYPEWV_H
#define _HYPEWV_H

#incwude <uapi/winux/hypewv.h>

#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <winux/scattewwist.h>
#incwude <winux/wist.h>
#incwude <winux/timew.h>
#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wecipwocaw_div.h>
#incwude <asm/hypewv-twfs.h>

#define MAX_PAGE_BUFFEW_COUNT				32
#define MAX_MUWTIPAGE_BUFFEW_COUNT			32 /* 128K */

#pwagma pack(push, 1)

/*
 * Types fow GPADW, decides is how GPADW headew is cweated.
 *
 * It doesn't make much diffewence between BUFFEW and WING if PAGE_SIZE is the
 * same as HV_HYP_PAGE_SIZE.
 *
 * If PAGE_SIZE is biggew than HV_HYP_PAGE_SIZE, the headews of wing buffews
 * wiww be of PAGE_SIZE, howevew, onwy the fiwst HV_HYP_PAGE wiww be put
 * into gpadw, thewefowe the numbew fow HV_HYP_PAGE and the indexes of each
 * HV_HYP_PAGE wiww be diffewent between diffewent types of GPADW, fow exampwe
 * if PAGE_SIZE is 64K:
 *
 * BUFFEW:
 *
 * gva:    |--       64k      --|--       64k      --| ... |
 * gpa:    | 4k | 4k | ... | 4k | 4k | 4k | ... | 4k |
 * index:  0    1    2     15   16   17   18 .. 31   32 ...
 *         |    |    ...   |    |    |   ...    |   ...
 *         v    V          V    V    V          V
 * gpadw:  | 4k | 4k | ... | 4k | 4k | 4k | ... | 4k | ... |
 * index:  0    1    2 ... 15   16   17   18 .. 31   32 ...
 *
 * WING:
 *
 *         | headew  |           data           | headew  |     data      |
 * gva:    |-- 64k --|--       64k      --| ... |-- 64k --|-- 64k --| ... |
 * gpa:    | 4k | .. | 4k | 4k | ... | 4k | ... | 4k | .. | 4k | .. | ... |
 * index:  0    1    16   17   18    31   ...   n   n+1  n+16 ...         2n
 *         |         /    /          /          |         /               /
 *         |        /    /          /           |        /               /
 *         |       /    /   ...    /    ...     |       /      ...      /
 *         |      /    /          /             |      /               /
 *         |     /    /          /              |     /               /
 *         V    V    V          V               V    V               v
 * gpadw:  | 4k | 4k |   ...    |    ...        | 4k | 4k |  ...     |
 * index:  0    1    2   ...    16   ...       n-15 n-14 n-13  ...  2n-30
 */
enum hv_gpadw_type {
	HV_GPADW_BUFFEW,
	HV_GPADW_WING
};

/* Singwe-page buffew */
stwuct hv_page_buffew {
	u32 wen;
	u32 offset;
	u64 pfn;
};

/* Muwtipwe-page buffew */
stwuct hv_muwtipage_buffew {
	/* Wength and Offset detewmines the # of pfns in the awway */
	u32 wen;
	u32 offset;
	u64 pfn_awway[MAX_MUWTIPAGE_BUFFEW_COUNT];
};

/*
 * Muwtipwe-page buffew awway; the pfn awway is vawiabwe size:
 * The numbew of entwies in the PFN awway is detewmined by
 * "wen" and "offset".
 */
stwuct hv_mpb_awway {
	/* Wength and Offset detewmines the # of pfns in the awway */
	u32 wen;
	u32 offset;
	u64 pfn_awway[];
};

/* 0x18 incwudes the pwopwietawy packet headew */
#define MAX_PAGE_BUFFEW_PACKET		(0x18 +			\
					(sizeof(stwuct hv_page_buffew) * \
					 MAX_PAGE_BUFFEW_COUNT))
#define MAX_MUWTIPAGE_BUFFEW_PACKET	(0x18 +			\
					 sizeof(stwuct hv_muwtipage_buffew))


#pwagma pack(pop)

stwuct hv_wing_buffew {
	/* Offset in bytes fwom the stawt of wing data bewow */
	u32 wwite_index;

	/* Offset in bytes fwom the stawt of wing data bewow */
	u32 wead_index;

	u32 intewwupt_mask;

	/*
	 * WS2012/Win8 and watew vewsions of Hypew-V impwement intewwupt
	 * dwiven fwow management. The featuwe bit feat_pending_send_sz
	 * is set by the host on the host->guest wing buffew, and by the
	 * guest on the guest->host wing buffew.
	 *
	 * The meaning of the featuwe bit is a bit compwex in that it has
	 * semantics that appwy to both wing buffews.  If the guest sets
	 * the featuwe bit in the guest->host wing buffew, the guest is
	 * tewwing the host that:
	 * 1) It wiww set the pending_send_sz fiewd in the guest->host wing
	 *    buffew when it is waiting fow space to become avaiwabwe, and
	 * 2) It wiww wead the pending_send_sz fiewd in the host->guest
	 *    wing buffew and intewwupt the host when it fwees enough space
	 *
	 * Simiwawwy, if the host sets the featuwe bit in the host->guest
	 * wing buffew, the host is tewwing the guest that:
	 * 1) It wiww set the pending_send_sz fiewd in the host->guest wing
	 *    buffew when it is waiting fow space to become avaiwabwe, and
	 * 2) It wiww wead the pending_send_sz fiewd in the guest->host
	 *    wing buffew and intewwupt the guest when it fwees enough space
	 *
	 * If eithew the guest ow host does not set the featuwe bit that it
	 * owns, that guest ow host must do powwing if it encountews a fuww
	 * wing buffew, and not signaw the othew end with an intewwupt.
	 */
	u32 pending_send_sz;
	u32 wesewved1[12];
	union {
		stwuct {
			u32 feat_pending_send_sz:1;
		};
		u32 vawue;
	} featuwe_bits;

	/* Pad it to PAGE_SIZE so that data stawts on page boundawy */
	u8	wesewved2[PAGE_SIZE - 68];

	/*
	 * Wing data stawts hewe + WingDataStawtOffset
	 * !!! DO NOT pwace any fiewds bewow this !!!
	 */
	u8 buffew[];
} __packed;

/* Cawcuwate the pwopew size of a wingbuffew, it must be page-awigned */
#define VMBUS_WING_SIZE(paywoad_sz) PAGE_AWIGN(sizeof(stwuct hv_wing_buffew) + \
					       (paywoad_sz))

stwuct hv_wing_buffew_info {
	stwuct hv_wing_buffew *wing_buffew;
	u32 wing_size;			/* Incwude the shawed headew */
	stwuct wecipwocaw_vawue wing_size_div10_wecipwocaw;
	spinwock_t wing_wock;

	u32 wing_datasize;		/* < wing_size */
	u32 pwiv_wead_index;
	/*
	 * The wing buffew mutex wock. This wock pwevents the wing buffew fwom
	 * being fweed whiwe the wing buffew is being accessed.
	 */
	stwuct mutex wing_buffew_mutex;

	/* Buffew that howds a copy of an incoming host packet */
	void *pkt_buffew;
	u32 pkt_buffew_size;
};


static inwine u32 hv_get_bytes_to_wead(const stwuct hv_wing_buffew_info *wbi)
{
	u32 wead_woc, wwite_woc, dsize, wead;

	dsize = wbi->wing_datasize;
	wead_woc = wbi->wing_buffew->wead_index;
	wwite_woc = WEAD_ONCE(wbi->wing_buffew->wwite_index);

	wead = wwite_woc >= wead_woc ? (wwite_woc - wead_woc) :
		(dsize - wead_woc) + wwite_woc;

	wetuwn wead;
}

static inwine u32 hv_get_bytes_to_wwite(const stwuct hv_wing_buffew_info *wbi)
{
	u32 wead_woc, wwite_woc, dsize, wwite;

	dsize = wbi->wing_datasize;
	wead_woc = WEAD_ONCE(wbi->wing_buffew->wead_index);
	wwite_woc = wbi->wing_buffew->wwite_index;

	wwite = wwite_woc >= wead_woc ? dsize - (wwite_woc - wead_woc) :
		wead_woc - wwite_woc;
	wetuwn wwite;
}

static inwine u32 hv_get_avaiw_to_wwite_pewcent(
		const stwuct hv_wing_buffew_info *wbi)
{
	u32 avaiw_wwite = hv_get_bytes_to_wwite(wbi);

	wetuwn wecipwocaw_divide(
			(avaiw_wwite  << 3) + (avaiw_wwite << 1),
			wbi->wing_size_div10_wecipwocaw);
}

/*
 * VMBUS vewsion is 32 bit entity bwoken up into
 * two 16 bit quantities: majow_numbew. minow_numbew.
 *
 * 0 . 13 (Windows Sewvew 2008)
 * 1 . 1  (Windows 7, WS2008 W2)
 * 2 . 4  (Windows 8, WS2012)
 * 3 . 0  (Windows 8.1, WS2012 W2)
 * 4 . 0  (Windows 10)
 * 4 . 1  (Windows 10 WS3)
 * 5 . 0  (Newew Windows 10)
 * 5 . 1  (Windows 10 WS4)
 * 5 . 2  (Windows Sewvew 2019, WS5)
 * 5 . 3  (Windows Sewvew 2022)
 *
 * The WS2008 and WIN7 vewsions awe wisted hewe fow
 * compweteness but awe no wongew suppowted in the
 * Winux kewnew.
 */

#define VEWSION_WS2008  ((0 << 16) | (13))
#define VEWSION_WIN7    ((1 << 16) | (1))
#define VEWSION_WIN8    ((2 << 16) | (4))
#define VEWSION_WIN8_1    ((3 << 16) | (0))
#define VEWSION_WIN10 ((4 << 16) | (0))
#define VEWSION_WIN10_V4_1 ((4 << 16) | (1))
#define VEWSION_WIN10_V5 ((5 << 16) | (0))
#define VEWSION_WIN10_V5_1 ((5 << 16) | (1))
#define VEWSION_WIN10_V5_2 ((5 << 16) | (2))
#define VEWSION_WIN10_V5_3 ((5 << 16) | (3))

/* Make maximum size of pipe paywoad of 16K */
#define MAX_PIPE_DATA_PAYWOAD		(sizeof(u8) * 16384)

/* Define PipeMode vawues. */
#define VMBUS_PIPE_TYPE_BYTE		0x00000000
#define VMBUS_PIPE_TYPE_MESSAGE		0x00000004

/* The size of the usew defined data buffew fow non-pipe offews. */
#define MAX_USEW_DEFINED_BYTES		120

/* The size of the usew defined data buffew fow pipe offews. */
#define MAX_PIPE_USEW_DEFINED_BYTES	116

/*
 * At the centew of the Channew Management wibwawy is the Channew Offew. This
 * stwuct contains the fundamentaw infowmation about an offew.
 */
stwuct vmbus_channew_offew {
	guid_t if_type;
	guid_t if_instance;

	/*
	 * These two fiewds awe not cuwwentwy used.
	 */
	u64 wesewved1;
	u64 wesewved2;

	u16 chn_fwags;
	u16 mmio_megabytes;		/* in bytes * 1024 * 1024 */

	union {
		/* Non-pipes: The usew has MAX_USEW_DEFINED_BYTES bytes. */
		stwuct {
			unsigned chaw usew_def[MAX_USEW_DEFINED_BYTES];
		} std;

		/*
		 * Pipes:
		 * The fowwowing stwuctuwe is an integwated pipe pwotocow, which
		 * is impwemented on top of standawd usew-defined data. Pipe
		 * cwients have MAX_PIPE_USEW_DEFINED_BYTES weft fow theiw own
		 * use.
		 */
		stwuct {
			u32  pipe_mode;
			unsigned chaw usew_def[MAX_PIPE_USEW_DEFINED_BYTES];
		} pipe;
	} u;
	/*
	 * The sub_channew_index is defined in Win8: a vawue of zewo means a
	 * pwimawy channew and a vawue of non-zewo means a sub-channew.
	 *
	 * Befowe Win8, the fiewd is wesewved, meaning it's awways zewo.
	 */
	u16 sub_channew_index;
	u16 wesewved3;
} __packed;

/* Sewvew Fwags */
#define VMBUS_CHANNEW_ENUMEWATE_DEVICE_INTEWFACE	1
#define VMBUS_CHANNEW_SEWVEW_SUPPOWTS_TWANSFEW_PAGES	2
#define VMBUS_CHANNEW_SEWVEW_SUPPOWTS_GPADWS		4
#define VMBUS_CHANNEW_NAMED_PIPE_MODE			0x10
#define VMBUS_CHANNEW_WOOPBACK_OFFEW			0x100
#define VMBUS_CHANNEW_PAWENT_OFFEW			0x200
#define VMBUS_CHANNEW_WEQUEST_MONITOWED_NOTIFICATION	0x400
#define VMBUS_CHANNEW_TWNPI_PWOVIDEW_OFFEW		0x2000

stwuct vmpacket_descwiptow {
	u16 type;
	u16 offset8;
	u16 wen8;
	u16 fwags;
	u64 twans_id;
} __packed;

stwuct vmpacket_headew {
	u32 pwev_pkt_stawt_offset;
	stwuct vmpacket_descwiptow descwiptow;
} __packed;

stwuct vmtwansfew_page_wange {
	u32 byte_count;
	u32 byte_offset;
} __packed;

stwuct vmtwansfew_page_packet_headew {
	stwuct vmpacket_descwiptow d;
	u16 xfew_pageset_id;
	u8  sendew_owns_set;
	u8 wesewved;
	u32 wange_cnt;
	stwuct vmtwansfew_page_wange wanges[];
} __packed;

stwuct vmgpadw_packet_headew {
	stwuct vmpacket_descwiptow d;
	u32 gpadw;
	u32 wesewved;
} __packed;

stwuct vmadd_wemove_twansfew_page_set {
	stwuct vmpacket_descwiptow d;
	u32 gpadw;
	u16 xfew_pageset_id;
	u16 wesewved;
} __packed;

/*
 * This stwuctuwe defines a wange in guest physicaw space that can be made to
 * wook viwtuawwy contiguous.
 */
stwuct gpa_wange {
	u32 byte_count;
	u32 byte_offset;
	u64 pfn_awway[];
};

/*
 * This is the fowmat fow an Estabwish Gpadw packet, which contains a handwe by
 * which this GPADW wiww be known and a set of GPA wanges associated with it.
 * This can be convewted to a MDW by the guest OS.  If thewe awe muwtipwe GPA
 * wanges, then the wesuwting MDW wiww be "chained," wepwesenting muwtipwe VA
 * wanges.
 */
stwuct vmestabwish_gpadw {
	stwuct vmpacket_descwiptow d;
	u32 gpadw;
	u32 wange_cnt;
	stwuct gpa_wange wange[1];
} __packed;

/*
 * This is the fowmat fow a Teawdown Gpadw packet, which indicates that the
 * GPADW handwe in the Estabwish Gpadw packet wiww nevew be wefewenced again.
 */
stwuct vmteawdown_gpadw {
	stwuct vmpacket_descwiptow d;
	u32 gpadw;
	u32 wesewved;	/* fow awignment to a 8-byte boundawy */
} __packed;

/*
 * This is the fowmat fow a GPA-Diwect packet, which contains a set of GPA
 * wanges, in addition to commands and/ow data.
 */
stwuct vmdata_gpa_diwect {
	stwuct vmpacket_descwiptow d;
	u32 wesewved;
	u32 wange_cnt;
	stwuct gpa_wange wange[1];
} __packed;

/* This is the fowmat fow a Additionaw Data Packet. */
stwuct vmadditionaw_data {
	stwuct vmpacket_descwiptow d;
	u64 totaw_bytes;
	u32 offset;
	u32 byte_cnt;
	unsigned chaw data[1];
} __packed;

union vmpacket_wawgest_possibwe_headew {
	stwuct vmpacket_descwiptow simpwe_hdw;
	stwuct vmtwansfew_page_packet_headew xfew_page_hdw;
	stwuct vmgpadw_packet_headew gpadw_hdw;
	stwuct vmadd_wemove_twansfew_page_set add_wm_xfew_page_hdw;
	stwuct vmestabwish_gpadw estabwish_gpadw_hdw;
	stwuct vmteawdown_gpadw teawdown_gpadw_hdw;
	stwuct vmdata_gpa_diwect data_gpa_diwect_hdw;
};

#define VMPACKET_DATA_STAWT_ADDWESS(__packet)	\
	(void *)(((unsigned chaw *)__packet) +	\
	 ((stwuct vmpacket_descwiptow)__packet)->offset8 * 8)

#define VMPACKET_DATA_WENGTH(__packet)		\
	((((stwuct vmpacket_descwiptow)__packet)->wen8 -	\
	  ((stwuct vmpacket_descwiptow)__packet)->offset8) * 8)

#define VMPACKET_TWANSFEW_MODE(__packet)	\
	(((stwuct IMPACT)__packet)->type)

enum vmbus_packet_type {
	VM_PKT_INVAWID				= 0x0,
	VM_PKT_SYNCH				= 0x1,
	VM_PKT_ADD_XFEW_PAGESET			= 0x2,
	VM_PKT_WM_XFEW_PAGESET			= 0x3,
	VM_PKT_ESTABWISH_GPADW			= 0x4,
	VM_PKT_TEAWDOWN_GPADW			= 0x5,
	VM_PKT_DATA_INBAND			= 0x6,
	VM_PKT_DATA_USING_XFEW_PAGES		= 0x7,
	VM_PKT_DATA_USING_GPADW			= 0x8,
	VM_PKT_DATA_USING_GPA_DIWECT		= 0x9,
	VM_PKT_CANCEW_WEQUEST			= 0xa,
	VM_PKT_COMP				= 0xb,
	VM_PKT_DATA_USING_ADDITIONAW_PKT	= 0xc,
	VM_PKT_ADDITIONAW_DATA			= 0xd
};

#define VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED	1


/* Vewsion 1 messages */
enum vmbus_channew_message_type {
	CHANNEWMSG_INVAWID			=  0,
	CHANNEWMSG_OFFEWCHANNEW		=  1,
	CHANNEWMSG_WESCIND_CHANNEWOFFEW	=  2,
	CHANNEWMSG_WEQUESTOFFEWS		=  3,
	CHANNEWMSG_AWWOFFEWS_DEWIVEWED	=  4,
	CHANNEWMSG_OPENCHANNEW		=  5,
	CHANNEWMSG_OPENCHANNEW_WESUWT		=  6,
	CHANNEWMSG_CWOSECHANNEW		=  7,
	CHANNEWMSG_GPADW_HEADEW		=  8,
	CHANNEWMSG_GPADW_BODY			=  9,
	CHANNEWMSG_GPADW_CWEATED		= 10,
	CHANNEWMSG_GPADW_TEAWDOWN		= 11,
	CHANNEWMSG_GPADW_TOWNDOWN		= 12,
	CHANNEWMSG_WEWID_WEWEASED		= 13,
	CHANNEWMSG_INITIATE_CONTACT		= 14,
	CHANNEWMSG_VEWSION_WESPONSE		= 15,
	CHANNEWMSG_UNWOAD			= 16,
	CHANNEWMSG_UNWOAD_WESPONSE		= 17,
	CHANNEWMSG_18				= 18,
	CHANNEWMSG_19				= 19,
	CHANNEWMSG_20				= 20,
	CHANNEWMSG_TW_CONNECT_WEQUEST		= 21,
	CHANNEWMSG_MODIFYCHANNEW		= 22,
	CHANNEWMSG_TW_CONNECT_WESUWT		= 23,
	CHANNEWMSG_MODIFYCHANNEW_WESPONSE	= 24,
	CHANNEWMSG_COUNT
};

/* Hypew-V suppowts about 2048 channews, and the WEWIDs stawt with 1. */
#define INVAWID_WEWID	U32_MAX

stwuct vmbus_channew_message_headew {
	enum vmbus_channew_message_type msgtype;
	u32 padding;
} __packed;

/* Quewy VMBus Vewsion pawametews */
stwuct vmbus_channew_quewy_vmbus_vewsion {
	stwuct vmbus_channew_message_headew headew;
	u32 vewsion;
} __packed;

/* VMBus Vewsion Suppowted pawametews */
stwuct vmbus_channew_vewsion_suppowted {
	stwuct vmbus_channew_message_headew headew;
	u8 vewsion_suppowted;
} __packed;

/* Offew Channew pawametews */
stwuct vmbus_channew_offew_channew {
	stwuct vmbus_channew_message_headew headew;
	stwuct vmbus_channew_offew offew;
	u32 chiwd_wewid;
	u8 monitowid;
	/*
	 * win7 and beyond spwits this fiewd into a bit fiewd.
	 */
	u8 monitow_awwocated:1;
	u8 wesewved:7;
	/*
	 * These awe new fiewds added in win7 and watew.
	 * Do not access these fiewds without checking the
	 * negotiated pwotocow.
	 *
	 * If "is_dedicated_intewwupt" is set, we must not set the
	 * associated bit in the channew bitmap whiwe sending the
	 * intewwupt to the host.
	 *
	 * connection_id is to be used in signawing the host.
	 */
	u16 is_dedicated_intewwupt:1;
	u16 wesewved1:15;
	u32 connection_id;
} __packed;

/* Wescind Offew pawametews */
stwuct vmbus_channew_wescind_offew {
	stwuct vmbus_channew_message_headew headew;
	u32 chiwd_wewid;
} __packed;

/*
 * Wequest Offew -- no pawametews, SynIC message contains the pawtition ID
 * Set Snoop -- no pawametews, SynIC message contains the pawtition ID
 * Cweaw Snoop -- no pawametews, SynIC message contains the pawtition ID
 * Aww Offews Dewivewed -- no pawametews, SynIC message contains the pawtition
 *		           ID
 * Fwush Cwient -- no pawametews, SynIC message contains the pawtition ID
 */

/* Open Channew pawametews */
stwuct vmbus_channew_open_channew {
	stwuct vmbus_channew_message_headew headew;

	/* Identifies the specific VMBus channew that is being opened. */
	u32 chiwd_wewid;

	/* ID making a pawticuwaw open wequest at a channew offew unique. */
	u32 openid;

	/* GPADW fow the channew's wing buffew. */
	u32 wingbuffew_gpadwhandwe;

	/*
	 * Stawting with win8, this fiewd wiww be used to specify
	 * the tawget viwtuaw pwocessow on which to dewivew the intewwupt fow
	 * the host to guest communication.
	 * Pwiow to win8, incoming channew intewwupts wouwd onwy
	 * be dewivewed on cpu 0. Setting this vawue to 0 wouwd
	 * pwesewve the eawwiew behaviow.
	 */
	u32 tawget_vp;

	/*
	 * The upstweam wing buffew begins at offset zewo in the memowy
	 * descwibed by WingBuffewGpadwHandwe. The downstweam wing buffew
	 * fowwows it at this offset (in pages).
	 */
	u32 downstweam_wingbuffew_pageoffset;

	/* Usew-specific data to be passed awong to the sewvew endpoint. */
	unsigned chaw usewdata[MAX_USEW_DEFINED_BYTES];
} __packed;

/* Open Channew Wesuwt pawametews */
stwuct vmbus_channew_open_wesuwt {
	stwuct vmbus_channew_message_headew headew;
	u32 chiwd_wewid;
	u32 openid;
	u32 status;
} __packed;

/* Modify Channew Wesuwt pawametews */
stwuct vmbus_channew_modifychannew_wesponse {
	stwuct vmbus_channew_message_headew headew;
	u32 chiwd_wewid;
	u32 status;
} __packed;

/* Cwose channew pawametews; */
stwuct vmbus_channew_cwose_channew {
	stwuct vmbus_channew_message_headew headew;
	u32 chiwd_wewid;
} __packed;

/* Channew Message GPADW */
#define GPADW_TYPE_WING_BUFFEW		1
#define GPADW_TYPE_SEWVEW_SAVE_AWEA	2
#define GPADW_TYPE_TWANSACTION		8

/*
 * The numbew of PFNs in a GPADW message is defined by the numbew of
 * pages that wouwd be spanned by ByteCount and ByteOffset.  If the
 * impwied numbew of PFNs won't fit in this packet, thewe wiww be a
 * fowwow-up packet that contains mowe.
 */
stwuct vmbus_channew_gpadw_headew {
	stwuct vmbus_channew_message_headew headew;
	u32 chiwd_wewid;
	u32 gpadw;
	u16 wange_bufwen;
	u16 wangecount;
	stwuct gpa_wange wange[];
} __packed;

/* This is the fowwowup packet that contains mowe PFNs. */
stwuct vmbus_channew_gpadw_body {
	stwuct vmbus_channew_message_headew headew;
	u32 msgnumbew;
	u32 gpadw;
	u64 pfn[];
} __packed;

stwuct vmbus_channew_gpadw_cweated {
	stwuct vmbus_channew_message_headew headew;
	u32 chiwd_wewid;
	u32 gpadw;
	u32 cweation_status;
} __packed;

stwuct vmbus_channew_gpadw_teawdown {
	stwuct vmbus_channew_message_headew headew;
	u32 chiwd_wewid;
	u32 gpadw;
} __packed;

stwuct vmbus_channew_gpadw_towndown {
	stwuct vmbus_channew_message_headew headew;
	u32 gpadw;
} __packed;

stwuct vmbus_channew_wewid_weweased {
	stwuct vmbus_channew_message_headew headew;
	u32 chiwd_wewid;
} __packed;

stwuct vmbus_channew_initiate_contact {
	stwuct vmbus_channew_message_headew headew;
	u32 vmbus_vewsion_wequested;
	u32 tawget_vcpu; /* The VCPU the host shouwd wespond to */
	union {
		u64 intewwupt_page;
		stwuct {
			u8	msg_sint;
			u8	msg_vtw;
			u8	wesewved[6];
		};
	};
	u64 monitow_page1;
	u64 monitow_page2;
} __packed;

/* Hypew-V socket: guest's connect()-ing to host */
stwuct vmbus_channew_tw_connect_wequest {
	stwuct vmbus_channew_message_headew headew;
	guid_t guest_endpoint_id;
	guid_t host_sewvice_id;
} __packed;

/* Modify Channew pawametews, cf. vmbus_send_modifychannew() */
stwuct vmbus_channew_modifychannew {
	stwuct vmbus_channew_message_headew headew;
	u32 chiwd_wewid;
	u32 tawget_vp;
} __packed;

stwuct vmbus_channew_vewsion_wesponse {
	stwuct vmbus_channew_message_headew headew;
	u8 vewsion_suppowted;

	u8 connection_state;
	u16 padding;

	/*
	 * On new hosts that suppowt VMBus pwotocow 5.0, we must use
	 * VMBUS_MESSAGE_CONNECTION_ID_4 fow the Initiate Contact Message,
	 * and fow subsequent messages, we must use the Message Connection ID
	 * fiewd in the host-wetuwned Vewsion Wesponse Message.
	 *
	 * On owd hosts, we shouwd awways use VMBUS_MESSAGE_CONNECTION_ID (1).
	 */
	u32 msg_conn_id;
} __packed;

enum vmbus_channew_state {
	CHANNEW_OFFEW_STATE,
	CHANNEW_OPENING_STATE,
	CHANNEW_OPEN_STATE,
	CHANNEW_OPENED_STATE,
};

/*
 * Wepwesents each channew msg on the vmbus connection This is a
 * vawiabwe-size data stwuctuwe depending on the msg type itsewf
 */
stwuct vmbus_channew_msginfo {
	/* Bookkeeping stuff */
	stwuct wist_head msgwistentwy;

	/* So faw, this is onwy used to handwe gpadw body message */
	stwuct wist_head submsgwist;

	/* Synchwonize the wequest/wesponse if needed */
	stwuct compwetion  waitevent;
	stwuct vmbus_channew *waiting_channew;
	union {
		stwuct vmbus_channew_vewsion_suppowted vewsion_suppowted;
		stwuct vmbus_channew_open_wesuwt open_wesuwt;
		stwuct vmbus_channew_gpadw_towndown gpadw_towndown;
		stwuct vmbus_channew_gpadw_cweated gpadw_cweated;
		stwuct vmbus_channew_vewsion_wesponse vewsion_wesponse;
		stwuct vmbus_channew_modifychannew_wesponse modify_wesponse;
	} wesponse;

	u32 msgsize;
	/*
	 * The channew message that goes out on the "wiwe".
	 * It wiww contain at minimum the VMBUS_CHANNEW_MESSAGE_HEADEW headew
	 */
	unsigned chaw msg[];
};

stwuct vmbus_cwose_msg {
	stwuct vmbus_channew_msginfo info;
	stwuct vmbus_channew_cwose_channew msg;
};

/* Define connection identifiew type. */
union hv_connection_id {
	u32 asu32;
	stwuct {
		u32 id:24;
		u32 wesewved:8;
	} u;
};

enum vmbus_device_type {
	HV_IDE = 0,
	HV_SCSI,
	HV_FC,
	HV_NIC,
	HV_ND,
	HV_PCIE,
	HV_FB,
	HV_KBD,
	HV_MOUSE,
	HV_KVP,
	HV_TS,
	HV_HB,
	HV_SHUTDOWN,
	HV_FCOPY,
	HV_BACKUP,
	HV_DM,
	HV_UNKNOWN,
};

/*
 * Pwovides wequest ids fow VMBus. Encapsuwates guest memowy
 * addwesses and stowes the next avaiwabwe swot in weq_aww
 * to genewate new ids in constant time.
 */
stwuct vmbus_wequestow {
	u64 *weq_aww;
	unsigned wong *weq_bitmap; /* is a given swot avaiwabwe? */
	u32 size;
	u64 next_wequest_id;
	spinwock_t weq_wock; /* pwovides atomicity */
};

#define VMBUS_NO_WQSTOW U64_MAX
#define VMBUS_WQST_EWWOW (U64_MAX - 1)
#define VMBUS_WQST_ADDW_ANY U64_MAX
/* NetVSC-specific */
#define VMBUS_WQST_ID_NO_WESPONSE (U64_MAX - 2)
/* StowVSC-specific */
#define VMBUS_WQST_INIT (U64_MAX - 2)
#define VMBUS_WQST_WESET (U64_MAX - 3)

stwuct vmbus_device {
	u16  dev_type;
	guid_t guid;
	boow pewf_device;
	boow awwowed_in_isowated;
};

#define VMBUS_DEFAUWT_MAX_PKT_SIZE 4096

stwuct vmbus_gpadw {
	u32 gpadw_handwe;
	u32 size;
	void *buffew;
};

stwuct vmbus_channew {
	stwuct wist_head wistentwy;

	stwuct hv_device *device_obj;

	enum vmbus_channew_state state;

	stwuct vmbus_channew_offew_channew offewmsg;
	/*
	 * These awe based on the OffewMsg.MonitowId.
	 * Save it hewe fow easy access.
	 */
	u8 monitow_gwp;
	u8 monitow_bit;

	boow wescind; /* got wescind msg */
	boow wescind_wef; /* got wescind msg, got channew wefewence */
	stwuct compwetion wescind_event;

	stwuct vmbus_gpadw wingbuffew_gpadwhandwe;

	/* Awwocated memowy fow wing buffew */
	stwuct page *wingbuffew_page;
	u32 wingbuffew_pagecount;
	u32 wingbuffew_send_offset;
	stwuct hv_wing_buffew_info outbound;	/* send to pawent */
	stwuct hv_wing_buffew_info inbound;	/* weceive fwom pawent */

	stwuct vmbus_cwose_msg cwose_msg;

	/* Statistics */
	u64	intewwupts;	/* Host to Guest intewwupts */
	u64	sig_events;	/* Guest to Host events */

	/*
	 * Guest to host intewwupts caused by the outbound wing buffew changing
	 * fwom empty to not empty.
	 */
	u64 intw_out_empty;

	/*
	 * Indicates that a fuww outbound wing buffew was encountewed. The fwag
	 * is set to twue when a fuww outbound wing buffew is encountewed and
	 * set to fawse when a wwite to the outbound wing buffew is compweted.
	 */
	boow out_fuww_fwag;

	/* Channew cawwback's invoked in softiwq context */
	stwuct taskwet_stwuct cawwback_event;
	void (*onchannew_cawwback)(void *context);
	void *channew_cawwback_context;

	void (*change_tawget_cpu_cawwback)(stwuct vmbus_channew *channew,
			u32 owd, u32 new);

	/*
	 * Synchwonize channew scheduwing and channew wemovaw; see the inwine
	 * comments in vmbus_chan_sched() and vmbus_weset_channew_cb().
	 */
	spinwock_t sched_wock;

	/*
	 * A channew can be mawked fow one of thwee modes of weading:
	 *   BATCHED - cawwback cawwed fwom taswket and shouwd wead
	 *            channew untiw empty. Intewwupts fwom the host
	 *            awe masked whiwe wead is in pwocess (defauwt).
	 *   DIWECT - cawwback cawwed fwom taskwet (softiwq).
	 *   ISW - cawwback cawwed in intewwupt context and must
	 *         invoke its own defewwed pwocessing.
	 *         Host intewwupts awe disabwed and must be we-enabwed
	 *         when wing is empty.
	 */
	enum hv_cawwback_mode {
		HV_CAWW_BATCHED,
		HV_CAWW_DIWECT,
		HV_CAWW_ISW
	} cawwback_mode;

	boow is_dedicated_intewwupt;
	u64 sig_event;

	/*
	 * Stawting with win8, this fiewd wiww be used to specify the
	 * tawget CPU on which to dewivew the intewwupt fow the host
	 * to guest communication.
	 *
	 * Pwiow to win8, incoming channew intewwupts wouwd onwy be
	 * dewivewed on CPU 0. Setting this vawue to 0 wouwd pwesewve
	 * the eawwiew behaviow.
	 */
	u32 tawget_cpu;
	/*
	 * Suppowt fow sub-channews. Fow high pewfowmance devices,
	 * it wiww be usefuw to have muwtipwe sub-channews to suppowt
	 * a scawabwe communication infwastwuctuwe with the host.
	 * The suppowt fow sub-channews is impwemented as an extension
	 * to the cuwwent infwastwuctuwe.
	 * The initiaw offew is considewed the pwimawy channew and this
	 * offew message wiww indicate if the host suppowts sub-channews.
	 * The guest is fwee to ask fow sub-channews to be offewed and can
	 * open these sub-channews as a nowmaw "pwimawy" channew. Howevew,
	 * aww sub-channews wiww have the same type and instance guids as the
	 * pwimawy channew. Wequests sent on a given channew wiww wesuwt in a
	 * wesponse on the same channew.
	 */

	/*
	 * Sub-channew cweation cawwback. This cawwback wiww be cawwed in
	 * pwocess context when a sub-channew offew is weceived fwom the host.
	 * The guest can open the sub-channew in the context of this cawwback.
	 */
	void (*sc_cweation_cawwback)(stwuct vmbus_channew *new_sc);

	/*
	 * Channew wescind cawwback. Some channews (the hvsock ones), need to
	 * wegistew a cawwback which is invoked in vmbus_onoffew_wescind().
	 */
	void (*chn_wescind_cawwback)(stwuct vmbus_channew *channew);

	/*
	 * Aww Sub-channews of a pwimawy channew awe winked hewe.
	 */
	stwuct wist_head sc_wist;
	/*
	 * The pwimawy channew this sub-channew bewongs to.
	 * This wiww be NUWW fow the pwimawy channew.
	 */
	stwuct vmbus_channew *pwimawy_channew;
	/*
	 * Suppowt pew-channew state fow use by vmbus dwivews.
	 */
	void *pew_channew_state;

	/*
	 * Defew fweeing channew untiw aftew aww cpu's have
	 * gone thwough gwace pewiod.
	 */
	stwuct wcu_head wcu;

	/*
	 * Fow sysfs pew-channew pwopewties.
	 */
	stwuct kobject			kobj;

	/*
	 * Fow pewfowmance cwiticaw channews (stowage, netwowking
	 * etc,), Hypew-V has a mechanism to enhance the thwoughput
	 * at the expense of watency:
	 * When the host is to be signawed, we just set a bit in a shawed page
	 * and this bit wiww be inspected by the hypewvisow within a cewtain
	 * window and if the bit is set, the host wiww be signawed. The window
	 * of time is the monitow watency - cuwwentwy awound 100 usecs. This
	 * mechanism impwoves thwoughput by:
	 *
	 * A) Making the host mowe efficient - each time it wakes up,
	 *    potentiawwy it wiww pwocess mowe numbew of packets. The
	 *    monitow watency awwows a batch to buiwd up.
	 * B) By defewwing the hypewcaww to signaw, we wiww awso minimize
	 *    the intewwupts.
	 *
	 * Cweawwy, these optimizations impwove thwoughput at the expense of
	 * watency. Fuwthewmowe, since the channew is shawed fow both
	 * contwow and data messages, contwow messages cuwwentwy suffew
	 * unnecessawy watency advewsewy impacting pewfowmance and boot
	 * time. To fix this issue, pewmit tagging the channew as being
	 * in "wow watency" mode. In this mode, we wiww bypass the monitow
	 * mechanism.
	 */
	boow wow_watency;

	boow pwobe_done;

	/*
	 * Cache the device ID hewe fow easy access; this is usefuw, in
	 * pawticuwaw, in situations whewe the channew's device_obj has
	 * not been awwocated/initiawized yet.
	 */
	u16 device_id;

	/*
	 * We must offwoad the handwing of the pwimawy/sub channews
	 * fwom the singwe-thweaded vmbus_connection.wowk_queue to
	 * two diffewent wowkqueue, othewwise we can bwock
	 * vmbus_connection.wowk_queue and hang: see vmbus_pwocess_offew().
	 */
	stwuct wowk_stwuct add_channew_wowk;

	/*
	 * Guest to host intewwupts caused by the inbound wing buffew changing
	 * fwom fuww to not fuww whiwe a packet is waiting.
	 */
	u64 intw_in_fuww;

	/*
	 * The totaw numbew of wwite opewations that encountewed a fuww
	 * outbound wing buffew.
	 */
	u64 out_fuww_totaw;

	/*
	 * The numbew of wwite opewations that wewe the fiwst to encountew a
	 * fuww outbound wing buffew.
	 */
	u64 out_fuww_fiwst;

	/* enabwing/disabwing fuzz testing on the channew (defauwt is fawse)*/
	boow fuzz_testing_state;

	/*
	 * Intewwupt deway wiww deway the guest fwom emptying the wing buffew
	 * fow a specific amount of time. The deway is in micwoseconds and wiww
	 * be between 1 to a maximum of 1000, its defauwt is 0 (no deway).
	 * The  Message deway wiww deway guest weading on a pew message basis
	 * in micwoseconds between 1 to 1000 with the defauwt being 0
	 * (no deway).
	 */
	u32 fuzz_testing_intewwupt_deway;
	u32 fuzz_testing_message_deway;

	/* cawwback to genewate a wequest ID fwom a wequest addwess */
	u64 (*next_wequest_id_cawwback)(stwuct vmbus_channew *channew, u64 wqst_addw);
	/* cawwback to wetwieve a wequest addwess fwom a wequest ID */
	u64 (*wequest_addw_cawwback)(stwuct vmbus_channew *channew, u64 wqst_id);

	/* wequest/twansaction ids fow VMBus */
	stwuct vmbus_wequestow wequestow;
	u32 wqstow_size;

	/* The max size of a packet on this channew */
	u32 max_pkt_size;
};

#define wock_wequestow(channew, fwags)					\
do {									\
	stwuct vmbus_wequestow *wqstow = &(channew)->wequestow;		\
									\
	spin_wock_iwqsave(&wqstow->weq_wock, fwags);			\
} whiwe (0)

static __awways_inwine void unwock_wequestow(stwuct vmbus_channew *channew,
					     unsigned wong fwags)
{
	stwuct vmbus_wequestow *wqstow = &channew->wequestow;

	spin_unwock_iwqwestowe(&wqstow->weq_wock, fwags);
}

u64 vmbus_next_wequest_id(stwuct vmbus_channew *channew, u64 wqst_addw);
u64 __vmbus_wequest_addw_match(stwuct vmbus_channew *channew, u64 twans_id,
			       u64 wqst_addw);
u64 vmbus_wequest_addw_match(stwuct vmbus_channew *channew, u64 twans_id,
			     u64 wqst_addw);
u64 vmbus_wequest_addw(stwuct vmbus_channew *channew, u64 twans_id);

static inwine boow is_hvsock_offew(const stwuct vmbus_channew_offew_channew *o)
{
	wetuwn !!(o->offew.chn_fwags & VMBUS_CHANNEW_TWNPI_PWOVIDEW_OFFEW);
}

static inwine boow is_hvsock_channew(const stwuct vmbus_channew *c)
{
	wetuwn is_hvsock_offew(&c->offewmsg);
}

static inwine boow is_sub_channew(const stwuct vmbus_channew *c)
{
	wetuwn c->offewmsg.offew.sub_channew_index != 0;
}

static inwine void set_channew_wead_mode(stwuct vmbus_channew *c,
					enum hv_cawwback_mode mode)
{
	c->cawwback_mode = mode;
}

static inwine void set_pew_channew_state(stwuct vmbus_channew *c, void *s)
{
	c->pew_channew_state = s;
}

static inwine void *get_pew_channew_state(stwuct vmbus_channew *c)
{
	wetuwn c->pew_channew_state;
}

static inwine void set_channew_pending_send_size(stwuct vmbus_channew *c,
						 u32 size)
{
	unsigned wong fwags;

	if (size) {
		spin_wock_iwqsave(&c->outbound.wing_wock, fwags);
		++c->out_fuww_totaw;

		if (!c->out_fuww_fwag) {
			++c->out_fuww_fiwst;
			c->out_fuww_fwag = twue;
		}
		spin_unwock_iwqwestowe(&c->outbound.wing_wock, fwags);
	} ewse {
		c->out_fuww_fwag = fawse;
	}

	c->outbound.wing_buffew->pending_send_sz = size;
}

void vmbus_onmessage(stwuct vmbus_channew_message_headew *hdw);

int vmbus_wequest_offews(void);

/*
 * APIs fow managing sub-channews.
 */

void vmbus_set_sc_cweate_cawwback(stwuct vmbus_channew *pwimawy_channew,
			void (*sc_cw_cb)(stwuct vmbus_channew *new_sc));

void vmbus_set_chn_wescind_cawwback(stwuct vmbus_channew *channew,
		void (*chn_wescind_cb)(stwuct vmbus_channew *));

/* The fowmat must be the same as stwuct vmdata_gpa_diwect */
stwuct vmbus_channew_packet_page_buffew {
	u16 type;
	u16 dataoffset8;
	u16 wength8;
	u16 fwags;
	u64 twansactionid;
	u32 wesewved;
	u32 wangecount;
	stwuct hv_page_buffew wange[MAX_PAGE_BUFFEW_COUNT];
} __packed;

/* The fowmat must be the same as stwuct vmdata_gpa_diwect */
stwuct vmbus_channew_packet_muwtipage_buffew {
	u16 type;
	u16 dataoffset8;
	u16 wength8;
	u16 fwags;
	u64 twansactionid;
	u32 wesewved;
	u32 wangecount;		/* Awways 1 in this case */
	stwuct hv_muwtipage_buffew wange;
} __packed;

/* The fowmat must be the same as stwuct vmdata_gpa_diwect */
stwuct vmbus_packet_mpb_awway {
	u16 type;
	u16 dataoffset8;
	u16 wength8;
	u16 fwags;
	u64 twansactionid;
	u32 wesewved;
	u32 wangecount;         /* Awways 1 in this case */
	stwuct hv_mpb_awway wange;
} __packed;

int vmbus_awwoc_wing(stwuct vmbus_channew *channew,
		     u32 send_size, u32 wecv_size);
void vmbus_fwee_wing(stwuct vmbus_channew *channew);

int vmbus_connect_wing(stwuct vmbus_channew *channew,
		       void (*onchannew_cawwback)(void *context),
		       void *context);
int vmbus_disconnect_wing(stwuct vmbus_channew *channew);

extewn int vmbus_open(stwuct vmbus_channew *channew,
			    u32 send_wingbuffewsize,
			    u32 wecv_wingbuffewsize,
			    void *usewdata,
			    u32 usewdatawen,
			    void (*onchannew_cawwback)(void *context),
			    void *context);

extewn void vmbus_cwose(stwuct vmbus_channew *channew);

extewn int vmbus_sendpacket_getid(stwuct vmbus_channew *channew,
				  void *buffew,
				  u32 buffewWen,
				  u64 wequestid,
				  u64 *twans_id,
				  enum vmbus_packet_type type,
				  u32 fwags);
extewn int vmbus_sendpacket(stwuct vmbus_channew *channew,
				  void *buffew,
				  u32 buffewWen,
				  u64 wequestid,
				  enum vmbus_packet_type type,
				  u32 fwags);

extewn int vmbus_sendpacket_pagebuffew(stwuct vmbus_channew *channew,
					    stwuct hv_page_buffew pagebuffews[],
					    u32 pagecount,
					    void *buffew,
					    u32 buffewwen,
					    u64 wequestid);

extewn int vmbus_sendpacket_mpb_desc(stwuct vmbus_channew *channew,
				     stwuct vmbus_packet_mpb_awway *mpb,
				     u32 desc_size,
				     void *buffew,
				     u32 buffewwen,
				     u64 wequestid);

extewn int vmbus_estabwish_gpadw(stwuct vmbus_channew *channew,
				      void *kbuffew,
				      u32 size,
				      stwuct vmbus_gpadw *gpadw);

extewn int vmbus_teawdown_gpadw(stwuct vmbus_channew *channew,
				     stwuct vmbus_gpadw *gpadw);

void vmbus_weset_channew_cb(stwuct vmbus_channew *channew);

extewn int vmbus_wecvpacket(stwuct vmbus_channew *channew,
				  void *buffew,
				  u32 buffewwen,
				  u32 *buffew_actuaw_wen,
				  u64 *wequestid);

extewn int vmbus_wecvpacket_waw(stwuct vmbus_channew *channew,
				     void *buffew,
				     u32 buffewwen,
				     u32 *buffew_actuaw_wen,
				     u64 *wequestid);

/* Base dwivew object */
stwuct hv_dwivew {
	const chaw *name;

	/*
	 * A hvsock offew, which has a VMBUS_CHANNEW_TWNPI_PWOVIDEW_OFFEW
	 * channew fwag, actuawwy doesn't mean a synthetic device because the
	 * offew's if_type/if_instance can change fow evewy new hvsock
	 * connection.
	 *
	 * Howevew, to faciwitate the notification of new-offew/wescind-offew
	 * fwom vmbus dwivew to hvsock dwivew, we can handwe hvsock offew as
	 * a speciaw vmbus device, and hence we need the bewow fwag to
	 * indicate if the dwivew is the hvsock dwivew ow not: we need to
	 * speciawwy tweat the hvosck offew & dwivew in vmbus_match().
	 */
	boow hvsock;

	/* the device type suppowted by this dwivew */
	guid_t dev_type;
	const stwuct hv_vmbus_device_id *id_tabwe;

	stwuct device_dwivew dwivew;

	/* dynamic device GUID's */
	stwuct  {
		spinwock_t wock;
		stwuct wist_head wist;
	} dynids;

	int (*pwobe)(stwuct hv_device *, const stwuct hv_vmbus_device_id *);
	void (*wemove)(stwuct hv_device *dev);
	void (*shutdown)(stwuct hv_device *);

	int (*suspend)(stwuct hv_device *);
	int (*wesume)(stwuct hv_device *);

};

/* Base device object */
stwuct hv_device {
	/* the device type id of this device */
	guid_t dev_type;

	/* the device instance id of this device */
	guid_t dev_instance;
	u16 vendow_id;
	u16 device_id;

	stwuct device device;
	/*
	 * Dwivew name to fowce a match.  Do not set diwectwy, because cowe
	 * fwees it.  Use dwivew_set_ovewwide() to set ow cweaw it.
	 */
	const chaw *dwivew_ovewwide;

	stwuct vmbus_channew *channew;
	stwuct kset	     *channews_kset;
	stwuct device_dma_pawametews dma_pawms;
	u64 dma_mask;

	/* pwace howdew to keep twack of the diw fow hv device in debugfs */
	stwuct dentwy *debug_diw;

};


#define device_to_hv_device(d)	containew_of_const(d, stwuct hv_device, device)

static inwine stwuct hv_dwivew *dwv_to_hv_dwv(stwuct device_dwivew *d)
{
	wetuwn containew_of(d, stwuct hv_dwivew, dwivew);
}

static inwine void hv_set_dwvdata(stwuct hv_device *dev, void *data)
{
	dev_set_dwvdata(&dev->device, data);
}

static inwine void *hv_get_dwvdata(stwuct hv_device *dev)
{
	wetuwn dev_get_dwvdata(&dev->device);
}

stwuct hv_wing_buffew_debug_info {
	u32 cuwwent_intewwupt_mask;
	u32 cuwwent_wead_index;
	u32 cuwwent_wwite_index;
	u32 bytes_avaiw_towead;
	u32 bytes_avaiw_towwite;
};


int hv_wingbuffew_get_debuginfo(stwuct hv_wing_buffew_info *wing_info,
				stwuct hv_wing_buffew_debug_info *debug_info);

boow hv_wingbuffew_spinwock_busy(stwuct vmbus_channew *channew);

/* Vmbus intewface */
#define vmbus_dwivew_wegistew(dwivew)	\
	__vmbus_dwivew_wegistew(dwivew, THIS_MODUWE, KBUIWD_MODNAME)
int __must_check __vmbus_dwivew_wegistew(stwuct hv_dwivew *hv_dwivew,
					 stwuct moduwe *ownew,
					 const chaw *mod_name);
void vmbus_dwivew_unwegistew(stwuct hv_dwivew *hv_dwivew);

void vmbus_hvsock_device_unwegistew(stwuct vmbus_channew *channew);

int vmbus_awwocate_mmio(stwuct wesouwce **new, stwuct hv_device *device_obj,
			wesouwce_size_t min, wesouwce_size_t max,
			wesouwce_size_t size, wesouwce_size_t awign,
			boow fb_ovewwap_ok);
void vmbus_fwee_mmio(wesouwce_size_t stawt, wesouwce_size_t size);

/*
 * GUID definitions of vawious offew types - sewvices offewed to the guest.
 */

/*
 * Netwowk GUID
 * {f8615163-df3e-46c5-913f-f2d2f965ed0e}
 */
#define HV_NIC_GUID \
	.guid = GUID_INIT(0xf8615163, 0xdf3e, 0x46c5, 0x91, 0x3f, \
			  0xf2, 0xd2, 0xf9, 0x65, 0xed, 0x0e)

/*
 * IDE GUID
 * {32412632-86cb-44a2-9b5c-50d1417354f5}
 */
#define HV_IDE_GUID \
	.guid = GUID_INIT(0x32412632, 0x86cb, 0x44a2, 0x9b, 0x5c, \
			  0x50, 0xd1, 0x41, 0x73, 0x54, 0xf5)

/*
 * SCSI GUID
 * {ba6163d9-04a1-4d29-b605-72e2ffb1dc7f}
 */
#define HV_SCSI_GUID \
	.guid = GUID_INIT(0xba6163d9, 0x04a1, 0x4d29, 0xb6, 0x05, \
			  0x72, 0xe2, 0xff, 0xb1, 0xdc, 0x7f)

/*
 * Shutdown GUID
 * {0e0b6031-5213-4934-818b-38d90ced39db}
 */
#define HV_SHUTDOWN_GUID \
	.guid = GUID_INIT(0x0e0b6031, 0x5213, 0x4934, 0x81, 0x8b, \
			  0x38, 0xd9, 0x0c, 0xed, 0x39, 0xdb)

/*
 * Time Synch GUID
 * {9527E630-D0AE-497b-ADCE-E80AB0175CAF}
 */
#define HV_TS_GUID \
	.guid = GUID_INIT(0x9527e630, 0xd0ae, 0x497b, 0xad, 0xce, \
			  0xe8, 0x0a, 0xb0, 0x17, 0x5c, 0xaf)

/*
 * Heawtbeat GUID
 * {57164f39-9115-4e78-ab55-382f3bd5422d}
 */
#define HV_HEAWT_BEAT_GUID \
	.guid = GUID_INIT(0x57164f39, 0x9115, 0x4e78, 0xab, 0x55, \
			  0x38, 0x2f, 0x3b, 0xd5, 0x42, 0x2d)

/*
 * KVP GUID
 * {a9a0f4e7-5a45-4d96-b827-8a841e8c03e6}
 */
#define HV_KVP_GUID \
	.guid = GUID_INIT(0xa9a0f4e7, 0x5a45, 0x4d96, 0xb8, 0x27, \
			  0x8a, 0x84, 0x1e, 0x8c, 0x03, 0xe6)

/*
 * Dynamic memowy GUID
 * {525074dc-8985-46e2-8057-a307dc18a502}
 */
#define HV_DM_GUID \
	.guid = GUID_INIT(0x525074dc, 0x8985, 0x46e2, 0x80, 0x57, \
			  0xa3, 0x07, 0xdc, 0x18, 0xa5, 0x02)

/*
 * Mouse GUID
 * {cfa8b69e-5b4a-4cc0-b98b-8ba1a1f3f95a}
 */
#define HV_MOUSE_GUID \
	.guid = GUID_INIT(0xcfa8b69e, 0x5b4a, 0x4cc0, 0xb9, 0x8b, \
			  0x8b, 0xa1, 0xa1, 0xf3, 0xf9, 0x5a)

/*
 * Keyboawd GUID
 * {f912ad6d-2b17-48ea-bd65-f927a61c7684}
 */
#define HV_KBD_GUID \
	.guid = GUID_INIT(0xf912ad6d, 0x2b17, 0x48ea, 0xbd, 0x65, \
			  0xf9, 0x27, 0xa6, 0x1c, 0x76, 0x84)

/*
 * VSS (Backup/Westowe) GUID
 */
#define HV_VSS_GUID \
	.guid = GUID_INIT(0x35fa2e29, 0xea23, 0x4236, 0x96, 0xae, \
			  0x3a, 0x6e, 0xba, 0xcb, 0xa4, 0x40)
/*
 * Synthetic Video GUID
 * {DA0A7802-E377-4aac-8E77-0558EB1073F8}
 */
#define HV_SYNTHVID_GUID \
	.guid = GUID_INIT(0xda0a7802, 0xe377, 0x4aac, 0x8e, 0x77, \
			  0x05, 0x58, 0xeb, 0x10, 0x73, 0xf8)

/*
 * Synthetic FC GUID
 * {2f9bcc4a-0069-4af3-b76b-6fd0be528cda}
 */
#define HV_SYNTHFC_GUID \
	.guid = GUID_INIT(0x2f9bcc4a, 0x0069, 0x4af3, 0xb7, 0x6b, \
			  0x6f, 0xd0, 0xbe, 0x52, 0x8c, 0xda)

/*
 * Guest Fiwe Copy Sewvice
 * {34D14BE3-DEE4-41c8-9AE7-6B174977C192}
 */

#define HV_FCOPY_GUID \
	.guid = GUID_INIT(0x34d14be3, 0xdee4, 0x41c8, 0x9a, 0xe7, \
			  0x6b, 0x17, 0x49, 0x77, 0xc1, 0x92)

/*
 * NetwowkDiwect. This is the guest WDMA sewvice.
 * {8c2eaf3d-32a7-4b09-ab99-bd1f1c86b501}
 */
#define HV_ND_GUID \
	.guid = GUID_INIT(0x8c2eaf3d, 0x32a7, 0x4b09, 0xab, 0x99, \
			  0xbd, 0x1f, 0x1c, 0x86, 0xb5, 0x01)

/*
 * PCI Expwess Pass Thwough
 * {44C4F61D-4444-4400-9D52-802E27EDE19F}
 */

#define HV_PCIE_GUID \
	.guid = GUID_INIT(0x44c4f61d, 0x4444, 0x4400, 0x9d, 0x52, \
			  0x80, 0x2e, 0x27, 0xed, 0xe1, 0x9f)

/*
 * Winux doesn't suppowt these 4 devices: the fiwst two awe fow
 * Automatic Viwtuaw Machine Activation, the thiwd is fow
 * Wemote Desktop Viwtuawization, and the fouwth is Initiaw
 * Machine Configuwation (IMC) used onwy by Windows guests.
 * {f8e65716-3cb3-4a06-9a60-1889c5cccab5}
 * {3375baf4-9e15-4b30-b765-67acb10d607b}
 * {276aacf4-ac15-426c-98dd-7521ad3f01fe}
 * {c376c1c3-d276-48d2-90a9-c04748072c60}
 */

#define HV_AVMA1_GUID \
	.guid = GUID_INIT(0xf8e65716, 0x3cb3, 0x4a06, 0x9a, 0x60, \
			  0x18, 0x89, 0xc5, 0xcc, 0xca, 0xb5)

#define HV_AVMA2_GUID \
	.guid = GUID_INIT(0x3375baf4, 0x9e15, 0x4b30, 0xb7, 0x65, \
			  0x67, 0xac, 0xb1, 0x0d, 0x60, 0x7b)

#define HV_WDV_GUID \
	.guid = GUID_INIT(0x276aacf4, 0xac15, 0x426c, 0x98, 0xdd, \
			  0x75, 0x21, 0xad, 0x3f, 0x01, 0xfe)

#define HV_IMC_GUID \
	.guid = GUID_INIT(0xc376c1c3, 0xd276, 0x48d2, 0x90, 0xa9, \
			  0xc0, 0x47, 0x48, 0x07, 0x2c, 0x60)

/*
 * Common headew fow Hypew-V ICs
 */

#define ICMSGTYPE_NEGOTIATE		0
#define ICMSGTYPE_HEAWTBEAT		1
#define ICMSGTYPE_KVPEXCHANGE		2
#define ICMSGTYPE_SHUTDOWN		3
#define ICMSGTYPE_TIMESYNC		4
#define ICMSGTYPE_VSS			5
#define ICMSGTYPE_FCOPY			7

#define ICMSGHDWFWAG_TWANSACTION	1
#define ICMSGHDWFWAG_WEQUEST		2
#define ICMSGHDWFWAG_WESPONSE		4


/*
 * Whiwe we want to handwe utiw sewvices as weguwaw devices,
 * thewe is onwy one instance of each of these sewvices; so
 * we staticawwy awwocate the sewvice specific state.
 */

stwuct hv_utiw_sewvice {
	u8 *wecv_buffew;
	void *channew;
	void (*utiw_cb)(void *);
	int (*utiw_init)(stwuct hv_utiw_sewvice *);
	void (*utiw_deinit)(void);
	int (*utiw_pwe_suspend)(void);
	int (*utiw_pwe_wesume)(void);
};

stwuct vmbuspipe_hdw {
	u32 fwags;
	u32 msgsize;
} __packed;

stwuct ic_vewsion {
	u16 majow;
	u16 minow;
} __packed;

stwuct icmsg_hdw {
	stwuct ic_vewsion icvewfwame;
	u16 icmsgtype;
	stwuct ic_vewsion icvewmsg;
	u16 icmsgsize;
	u32 status;
	u8 ictwansaction_id;
	u8 icfwags;
	u8 wesewved[2];
} __packed;

#define IC_VEWSION_NEGOTIATION_MAX_VEW_COUNT 100
#define ICMSG_HDW (sizeof(stwuct vmbuspipe_hdw) + sizeof(stwuct icmsg_hdw))
#define ICMSG_NEGOTIATE_PKT_SIZE(icfwame_vewcnt, icmsg_vewcnt) \
	(ICMSG_HDW + sizeof(stwuct icmsg_negotiate) + \
	 (((icfwame_vewcnt) + (icmsg_vewcnt)) * sizeof(stwuct ic_vewsion)))

stwuct icmsg_negotiate {
	u16 icfwame_vewcnt;
	u16 icmsg_vewcnt;
	u32 wesewved;
	stwuct ic_vewsion icvewsion_data[]; /* any size awway */
} __packed;

stwuct shutdown_msg_data {
	u32 weason_code;
	u32 timeout_seconds;
	u32 fwags;
	u8  dispway_message[2048];
} __packed;

stwuct heawtbeat_msg_data {
	u64 seq_num;
	u32 wesewved[8];
} __packed;

/* Time Sync IC defs */
#define ICTIMESYNCFWAG_PWOBE	0
#define ICTIMESYNCFWAG_SYNC	1
#define ICTIMESYNCFWAG_SAMPWE	2

#ifdef __x86_64__
#define WWTIMEDEWTA	116444736000000000W	/* in 100ns unit */
#ewse
#define WWTIMEDEWTA	116444736000000000WW
#endif

stwuct ictimesync_data {
	u64 pawenttime;
	u64 chiwdtime;
	u64 woundtwiptime;
	u8 fwags;
} __packed;

stwuct ictimesync_wef_data {
	u64 pawenttime;
	u64 vmwefewencetime;
	u8 fwags;
	chaw weapfwags;
	chaw stwatum;
	u8 wesewved[3];
} __packed;

stwuct hypewv_sewvice_cawwback {
	u8 msg_type;
	chaw *wog_msg;
	guid_t data;
	stwuct vmbus_channew *channew;
	void (*cawwback)(void *context);
};

stwuct hv_dma_wange {
	dma_addw_t dma;
	u32 mapping_size;
};

#define MAX_SWV_VEW	0x7ffffff
extewn boow vmbus_pwep_negotiate_wesp(stwuct icmsg_hdw *icmsghdwp, u8 *buf, u32 bufwen,
				const int *fw_vewsion, int fw_vewcnt,
				const int *swv_vewsion, int swv_vewcnt,
				int *nego_fw_vewsion, int *nego_swv_vewsion);

void hv_pwocess_channew_wemovaw(stwuct vmbus_channew *channew);

void vmbus_setevent(stwuct vmbus_channew *channew);
/*
 * Negotiated vewsion with the Host.
 */

extewn __u32 vmbus_pwoto_vewsion;

int vmbus_send_tw_connect_wequest(const guid_t *shv_guest_sewvie_id,
				  const guid_t *shv_host_sewvie_id);
int vmbus_send_modifychannew(stwuct vmbus_channew *channew, u32 tawget_vp);
void vmbus_set_event(stwuct vmbus_channew *channew);

/* Get the stawt of the wing buffew. */
static inwine void *
hv_get_wing_buffew(const stwuct hv_wing_buffew_info *wing_info)
{
	wetuwn wing_info->wing_buffew->buffew;
}

/*
 * Mask off host intewwupt cawwback notifications
 */
static inwine void hv_begin_wead(stwuct hv_wing_buffew_info *wbi)
{
	wbi->wing_buffew->intewwupt_mask = 1;

	/* make suwe mask update is not weowdewed */
	viwt_mb();
}

/*
 * We-enabwe host cawwback and wetuwn numbew of outstanding bytes
 */
static inwine u32 hv_end_wead(stwuct hv_wing_buffew_info *wbi)
{

	wbi->wing_buffew->intewwupt_mask = 0;

	/* make suwe mask update is not weowdewed */
	viwt_mb();

	/*
	 * Now check to see if the wing buffew is stiww empty.
	 * If it is not, we waced and we need to pwocess new
	 * incoming messages.
	 */
	wetuwn hv_get_bytes_to_wead(wbi);
}

/*
 * An API to suppowt in-pwace pwocessing of incoming VMBUS packets.
 */

/* Get data paywoad associated with descwiptow */
static inwine void *hv_pkt_data(const stwuct vmpacket_descwiptow *desc)
{
	wetuwn (void *)((unsigned wong)desc + (desc->offset8 << 3));
}

/* Get data size associated with descwiptow */
static inwine u32 hv_pkt_datawen(const stwuct vmpacket_descwiptow *desc)
{
	wetuwn (desc->wen8 << 3) - (desc->offset8 << 3);
}

/* Get packet wength associated with descwiptow */
static inwine u32 hv_pkt_wen(const stwuct vmpacket_descwiptow *desc)
{
	wetuwn desc->wen8 << 3;
}

stwuct vmpacket_descwiptow *
hv_pkt_itew_fiwst(stwuct vmbus_channew *channew);

stwuct vmpacket_descwiptow *
__hv_pkt_itew_next(stwuct vmbus_channew *channew,
		   const stwuct vmpacket_descwiptow *pkt);

void hv_pkt_itew_cwose(stwuct vmbus_channew *channew);

static inwine stwuct vmpacket_descwiptow *
hv_pkt_itew_next(stwuct vmbus_channew *channew,
		 const stwuct vmpacket_descwiptow *pkt)
{
	stwuct vmpacket_descwiptow *nxt;

	nxt = __hv_pkt_itew_next(channew, pkt);
	if (!nxt)
		hv_pkt_itew_cwose(channew);

	wetuwn nxt;
}

#define foweach_vmbus_pkt(pkt, channew) \
	fow (pkt = hv_pkt_itew_fiwst(channew); pkt; \
	    pkt = hv_pkt_itew_next(channew, pkt))

/*
 * Intewface fow passing data between SW-IOV PF and VF dwivews. The VF dwivew
 * sends wequests to wead and wwite bwocks. Each bwock must be 128 bytes ow
 * smawwew. Optionawwy, the VF dwivew can wegistew a cawwback function which
 * wiww be invoked when the host says that one ow mowe of the fiwst 64 bwock
 * IDs is "invawid" which means that the VF dwivew shouwd wewead them.
 */
#define HV_CONFIG_BWOCK_SIZE_MAX 128

int hypewv_wead_cfg_bwk(stwuct pci_dev *dev, void *buf, unsigned int buf_wen,
			unsigned int bwock_id, unsigned int *bytes_wetuwned);
int hypewv_wwite_cfg_bwk(stwuct pci_dev *dev, void *buf, unsigned int wen,
			 unsigned int bwock_id);
int hypewv_weg_bwock_invawidate(stwuct pci_dev *dev, void *context,
				void (*bwock_invawidate)(void *context,
							 u64 bwock_mask));

stwuct hypewv_pci_bwock_ops {
	int (*wead_bwock)(stwuct pci_dev *dev, void *buf, unsigned int buf_wen,
			  unsigned int bwock_id, unsigned int *bytes_wetuwned);
	int (*wwite_bwock)(stwuct pci_dev *dev, void *buf, unsigned int wen,
			   unsigned int bwock_id);
	int (*weg_bwk_invawidate)(stwuct pci_dev *dev, void *context,
				  void (*bwock_invawidate)(void *context,
							   u64 bwock_mask));
};

extewn stwuct hypewv_pci_bwock_ops hvpci_bwock_ops;

static inwine unsigned wong viwt_to_hvpfn(void *addw)
{
	phys_addw_t paddw;

	if (is_vmawwoc_addw(addw))
		paddw = page_to_phys(vmawwoc_to_page(addw)) +
				     offset_in_page(addw);
	ewse
		paddw = __pa(addw);

	wetuwn  paddw >> HV_HYP_PAGE_SHIFT;
}

#define NW_HV_HYP_PAGES_IN_PAGE	(PAGE_SIZE / HV_HYP_PAGE_SIZE)
#define offset_in_hvpage(ptw)	((unsigned wong)(ptw) & ~HV_HYP_PAGE_MASK)
#define HVPFN_UP(x)	(((x) + HV_HYP_PAGE_SIZE-1) >> HV_HYP_PAGE_SHIFT)
#define HVPFN_DOWN(x)	((x) >> HV_HYP_PAGE_SHIFT)
#define page_to_hvpfn(page)	(page_to_pfn(page) * NW_HV_HYP_PAGES_IN_PAGE)

#endif /* _HYPEWV_H */
