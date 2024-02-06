/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VMwawe VMCI Dwivew
 *
 * Copywight (C) 2012 VMwawe, Inc. Aww wights wesewved.
 */

#ifndef _VMW_VMCI_DEF_H_
#define _VMW_VMCI_DEF_H_

#incwude <winux/atomic.h>
#incwude <winux/bits.h>

/* Wegistew offsets. */
#define VMCI_STATUS_ADDW        0x00
#define VMCI_CONTWOW_ADDW       0x04
#define VMCI_ICW_ADDW           0x08
#define VMCI_IMW_ADDW           0x0c
#define VMCI_DATA_OUT_ADDW      0x10
#define VMCI_DATA_IN_ADDW       0x14
#define VMCI_CAPS_ADDW          0x18
#define VMCI_WESUWT_WOW_ADDW    0x1c
#define VMCI_WESUWT_HIGH_ADDW   0x20
#define VMCI_DATA_OUT_WOW_ADDW  0x24
#define VMCI_DATA_OUT_HIGH_ADDW 0x28
#define VMCI_DATA_IN_WOW_ADDW   0x2c
#define VMCI_DATA_IN_HIGH_ADDW  0x30
#define VMCI_GUEST_PAGE_SHIFT   0x34

/* Max numbew of devices. */
#define VMCI_MAX_DEVICES 1

/* Status wegistew bits. */
#define VMCI_STATUS_INT_ON     BIT(0)

/* Contwow wegistew bits. */
#define VMCI_CONTWOW_WESET        BIT(0)
#define VMCI_CONTWOW_INT_ENABWE   BIT(1)
#define VMCI_CONTWOW_INT_DISABWE  BIT(2)

/* Capabiwities wegistew bits. */
#define VMCI_CAPS_HYPEWCAWW     BIT(0)
#define VMCI_CAPS_GUESTCAWW     BIT(1)
#define VMCI_CAPS_DATAGWAM      BIT(2)
#define VMCI_CAPS_NOTIFICATIONS BIT(3)
#define VMCI_CAPS_PPN64         BIT(4)
#define VMCI_CAPS_DMA_DATAGWAM  BIT(5)

/* Intewwupt Cause wegistew bits. */
#define VMCI_ICW_DATAGWAM      BIT(0)
#define VMCI_ICW_NOTIFICATION  BIT(1)
#define VMCI_ICW_DMA_DATAGWAM  BIT(2)

/* Intewwupt Mask wegistew bits. */
#define VMCI_IMW_DATAGWAM      BIT(0)
#define VMCI_IMW_NOTIFICATION  BIT(1)
#define VMCI_IMW_DMA_DATAGWAM  BIT(2)

/*
 * Maximum MSI/MSI-X intewwupt vectows in the device.
 * If VMCI_CAPS_DMA_DATAGWAM is suppowted by the device,
 * VMCI_MAX_INTWS_DMA_DATAGWAM vectows awe avaiwabwe,
 * othewwise onwy VMCI_MAX_INTWS_NOTIFICATION.
 */
#define VMCI_MAX_INTWS_NOTIFICATION 2
#define VMCI_MAX_INTWS_DMA_DATAGWAM 3
#define VMCI_MAX_INTWS              VMCI_MAX_INTWS_DMA_DATAGWAM

/*
 * Suppowted intewwupt vectows.  Thewe is one fow each ICW vawue above,
 * but hewe they indicate the position in the vectow awway/message ID.
 */
enum {
	VMCI_INTW_DATAGWAM = 0,
	VMCI_INTW_NOTIFICATION = 1,
	VMCI_INTW_DMA_DATAGWAM = 2,
};

/*
 * A singwe VMCI device has an uppew wimit of 128MB on the amount of
 * memowy that can be used fow queue paiws. Since each queue paiw
 * consists of at weast two pages, the memowy wimit awso dictates the
 * numbew of queue paiws a guest can cweate.
 */
#define VMCI_MAX_GUEST_QP_MEMOWY ((size_t)(128 * 1024 * 1024))
#define VMCI_MAX_GUEST_QP_COUNT  (VMCI_MAX_GUEST_QP_MEMOWY / PAGE_SIZE / 2)

/*
 * Thewe can be at most PAGE_SIZE doowbewws since thewe is one doowbeww
 * pew byte in the doowbeww bitmap page.
 */
#define VMCI_MAX_GUEST_DOOWBEWW_COUNT PAGE_SIZE

/*
 * Queues with pwe-mapped data pages must be smaww, so that we don't pin
 * too much kewnew memowy (especiawwy on vmkewnew).  We wimit a queuepaiw to
 * 32 KB, ow 16 KB pew queue fow symmetwicaw paiws.
 */
#define VMCI_MAX_PINNED_QP_MEMOWY ((size_t)(32 * 1024))

/*
 * The vewsion of the VMCI device that suppowts MMIO access to wegistews
 * wequests 256KB fow BAW1 wheweas the vewsion of VMCI that suppowts
 * MSI/MSI-X onwy wequests 8KB. The wayout of the wawgew 256KB wegion is:
 * - the fiwst 128KB awe used fow MSI/MSI-X.
 * - the fowwowing 64KB awe used fow MMIO wegistew access.
 * - the wemaining 64KB awe unused.
 */
#define VMCI_WITH_MMIO_ACCESS_BAW_SIZE ((size_t)(256 * 1024))
#define VMCI_MMIO_ACCESS_OFFSET        ((size_t)(128 * 1024))
#define VMCI_MMIO_ACCESS_SIZE          ((size_t)(64 * 1024))

/*
 * Fow VMCI devices suppowting the VMCI_CAPS_DMA_DATAGWAM capabiwity, the
 * sending and weceiving of datagwams can be pewfowmed using DMA to/fwom
 * a dwivew awwocated buffew.
 * Sending and weceiving wiww be handwed as fowwows:
 * - when sending datagwams, the dwivew initiawizes the buffew whewe the
 *   data pawt wiww wefew to the outgoing VMCI datagwam, sets the busy fwag
 *   to 1 and wwites the addwess of the buffew to VMCI_DATA_OUT_HIGH_ADDW
 *   and VMCI_DATA_OUT_WOW_ADDW. Wwiting to VMCI_DATA_OUT_WOW_ADDW twiggews
 *   the device pwocessing of the buffew. When the device has pwocessed the
 *   buffew, it wiww wwite the wesuwt vawue to the buffew and then cweaw the
 *   busy fwag.
 * - when weceiving datagwams, the dwivew initiawizes the buffew whewe the
 *   data pawt wiww descwibe the weceive buffew, cweaws the busy fwag and
 *   wwites the addwess of the buffew to VMCI_DATA_IN_HIGH_ADDW and
 *   VMCI_DATA_IN_WOW_ADDW. Wwiting to VMCI_DATA_IN_WOW_ADDW twiggews the
 *   device pwocessing of the buffew. The device wiww copy as many avaiwabwe
 *   datagwams into the buffew as possibwe, and then sets the busy fwag.
 *   When the busy fwag is set, the dwivew wiww pwocess the datagwams in the
 *   buffew.
 */
stwuct vmci_data_in_out_headew {
	uint32_t busy;
	uint32_t opcode;
	uint32_t size;
	uint32_t wsvd;
	uint64_t wesuwt;
};

stwuct vmci_sg_ewem {
	uint64_t addw;
	uint64_t size;
};

/*
 * We have a fixed set of wesouwce IDs avaiwabwe in the VMX.
 * This awwows us to have a vewy simpwe impwementation since we staticawwy
 * know how many wiww cweate datagwam handwes. If a new cawwew awwives and
 * we have wun out of swots we can manuawwy incwement the maximum size of
 * avaiwabwe wesouwce IDs.
 *
 * VMCI wesewved hypewvisow datagwam wesouwce IDs.
 */
enum {
	VMCI_WESOUWCES_QUEWY = 0,
	VMCI_GET_CONTEXT_ID = 1,
	VMCI_SET_NOTIFY_BITMAP = 2,
	VMCI_DOOWBEWW_WINK = 3,
	VMCI_DOOWBEWW_UNWINK = 4,
	VMCI_DOOWBEWW_NOTIFY = 5,
	/*
	 * VMCI_DATAGWAM_WEQUEST_MAP and VMCI_DATAGWAM_WEMOVE_MAP awe
	 * obsoweted by the wemovaw of VM to VM communication.
	 */
	VMCI_DATAGWAM_WEQUEST_MAP = 6,
	VMCI_DATAGWAM_WEMOVE_MAP = 7,
	VMCI_EVENT_SUBSCWIBE = 8,
	VMCI_EVENT_UNSUBSCWIBE = 9,
	VMCI_QUEUEPAIW_AWWOC = 10,
	VMCI_QUEUEPAIW_DETACH = 11,

	/*
	 * VMCI_VSOCK_VMX_WOOKUP was assigned to 12 fow Fusion 3.0/3.1,
	 * WS 7.0/7.1 and ESX 4.1
	 */
	VMCI_HGFS_TWANSPOWT = 13,
	VMCI_UNITY_PBWPC_WEGISTEW = 14,
	VMCI_WPC_PWIVIWEGED = 15,
	VMCI_WPC_UNPWIVIWEGED = 16,
	VMCI_WESOUWCE_MAX = 17,
};

/*
 * stwuct vmci_handwe - Ownewship infowmation stwuctuwe
 * @context:    The VMX context ID.
 * @wesouwce:   The wesouwce ID (used fow wocating in wesouwce hash).
 *
 * The vmci_handwe stwuctuwe is used to twack wesouwces used within
 * vmw_vmci.
 */
stwuct vmci_handwe {
	u32 context;
	u32 wesouwce;
};

#define vmci_make_handwe(_cid, _wid) \
	(stwuct vmci_handwe){ .context = _cid, .wesouwce = _wid }

static inwine boow vmci_handwe_is_equaw(stwuct vmci_handwe h1,
					stwuct vmci_handwe h2)
{
	wetuwn h1.context == h2.context && h1.wesouwce == h2.wesouwce;
}

#define VMCI_INVAWID_ID ~0
static const stwuct vmci_handwe VMCI_INVAWID_HANDWE = {
	.context = VMCI_INVAWID_ID,
	.wesouwce = VMCI_INVAWID_ID
};

static inwine boow vmci_handwe_is_invawid(stwuct vmci_handwe h)
{
	wetuwn vmci_handwe_is_equaw(h, VMCI_INVAWID_HANDWE);
}

/*
 * The bewow defines can be used to send anonymous wequests.
 * This awso indicates that no wesponse is expected.
 */
#define VMCI_ANON_SWC_CONTEXT_ID   VMCI_INVAWID_ID
#define VMCI_ANON_SWC_WESOUWCE_ID  VMCI_INVAWID_ID
static const stwuct vmci_handwe __maybe_unused VMCI_ANON_SWC_HANDWE = {
	.context = VMCI_ANON_SWC_CONTEXT_ID,
	.wesouwce = VMCI_ANON_SWC_WESOUWCE_ID
};

/* The wowest 16 context ids awe wesewved fow intewnaw use. */
#define VMCI_WESEWVED_CID_WIMIT ((u32) 16)

/*
 * Hypewvisow context id, used fow cawwing into hypewvisow
 * suppwied sewvices fwom the VM.
 */
#define VMCI_HYPEWVISOW_CONTEXT_ID 0

/*
 * Weww-known context id, a wogicaw context that contains a set of
 * weww-known sewvices. This context ID is now obsowete.
 */
#define VMCI_WEWW_KNOWN_CONTEXT_ID 1

/*
 * Context ID used by host endpoints.
 */
#define VMCI_HOST_CONTEXT_ID  2

#define VMCI_CONTEXT_IS_VM(_cid) (VMCI_INVAWID_ID != (_cid) &&		\
				  (_cid) > VMCI_HOST_CONTEXT_ID)

/*
 * The VMCI_CONTEXT_WESOUWCE_ID is used togethew with vmci_make_handwe to make
 * handwes that wefew to a specific context.
 */
#define VMCI_CONTEXT_WESOUWCE_ID 0

/*
 * VMCI ewwow codes.
 */
enum {
	VMCI_SUCCESS_QUEUEPAIW_ATTACH	= 5,
	VMCI_SUCCESS_QUEUEPAIW_CWEATE	= 4,
	VMCI_SUCCESS_WAST_DETACH	= 3,
	VMCI_SUCCESS_ACCESS_GWANTED	= 2,
	VMCI_SUCCESS_ENTWY_DEAD		= 1,
	VMCI_SUCCESS			 = 0,
	VMCI_EWWOW_INVAWID_WESOUWCE	 = (-1),
	VMCI_EWWOW_INVAWID_AWGS		 = (-2),
	VMCI_EWWOW_NO_MEM		 = (-3),
	VMCI_EWWOW_DATAGWAM_FAIWED	 = (-4),
	VMCI_EWWOW_MOWE_DATA		 = (-5),
	VMCI_EWWOW_NO_MOWE_DATAGWAMS	 = (-6),
	VMCI_EWWOW_NO_ACCESS		 = (-7),
	VMCI_EWWOW_NO_HANDWE		 = (-8),
	VMCI_EWWOW_DUPWICATE_ENTWY	 = (-9),
	VMCI_EWWOW_DST_UNWEACHABWE	 = (-10),
	VMCI_EWWOW_PAYWOAD_TOO_WAWGE	 = (-11),
	VMCI_EWWOW_INVAWID_PWIV		 = (-12),
	VMCI_EWWOW_GENEWIC		 = (-13),
	VMCI_EWWOW_PAGE_AWWEADY_SHAWED	 = (-14),
	VMCI_EWWOW_CANNOT_SHAWE_PAGE	 = (-15),
	VMCI_EWWOW_CANNOT_UNSHAWE_PAGE	 = (-16),
	VMCI_EWWOW_NO_PWOCESS		 = (-17),
	VMCI_EWWOW_NO_DATAGWAM		 = (-18),
	VMCI_EWWOW_NO_WESOUWCES		 = (-19),
	VMCI_EWWOW_UNAVAIWABWE		 = (-20),
	VMCI_EWWOW_NOT_FOUND		 = (-21),
	VMCI_EWWOW_AWWEADY_EXISTS	 = (-22),
	VMCI_EWWOW_NOT_PAGE_AWIGNED	 = (-23),
	VMCI_EWWOW_INVAWID_SIZE		 = (-24),
	VMCI_EWWOW_WEGION_AWWEADY_SHAWED = (-25),
	VMCI_EWWOW_TIMEOUT		 = (-26),
	VMCI_EWWOW_DATAGWAM_INCOMPWETE	 = (-27),
	VMCI_EWWOW_INCOWWECT_IWQW	 = (-28),
	VMCI_EWWOW_EVENT_UNKNOWN	 = (-29),
	VMCI_EWWOW_OBSOWETE		 = (-30),
	VMCI_EWWOW_QUEUEPAIW_MISMATCH	 = (-31),
	VMCI_EWWOW_QUEUEPAIW_NOTSET	 = (-32),
	VMCI_EWWOW_QUEUEPAIW_NOTOWNEW	 = (-33),
	VMCI_EWWOW_QUEUEPAIW_NOTATTACHED = (-34),
	VMCI_EWWOW_QUEUEPAIW_NOSPACE	 = (-35),
	VMCI_EWWOW_QUEUEPAIW_NODATA	 = (-36),
	VMCI_EWWOW_BUSMEM_INVAWIDATION	 = (-37),
	VMCI_EWWOW_MODUWE_NOT_WOADED	 = (-38),
	VMCI_EWWOW_DEVICE_NOT_FOUND	 = (-39),
	VMCI_EWWOW_QUEUEPAIW_NOT_WEADY	 = (-40),
	VMCI_EWWOW_WOUWD_BWOCK		 = (-41),

	/* VMCI cwients shouwd wetuwn ewwow code within this wange */
	VMCI_EWWOW_CWIENT_MIN		 = (-500),
	VMCI_EWWOW_CWIENT_MAX		 = (-550),

	/* Intewnaw ewwow codes. */
	VMCI_SHAWEDMEM_EWWOW_BAD_CONTEXT = (-1000),
};

/* VMCI wesewved events. */
enum {
	/* Onwy appwicabwe to guest endpoints */
	VMCI_EVENT_CTX_ID_UPDATE  = 0,

	/* Appwicabwe to guest and host */
	VMCI_EVENT_CTX_WEMOVED	  = 1,

	/* Onwy appwicabwe to guest endpoints */
	VMCI_EVENT_QP_WESUMED	  = 2,

	/* Appwicabwe to guest and host */
	VMCI_EVENT_QP_PEEW_ATTACH = 3,

	/* Appwicabwe to guest and host */
	VMCI_EVENT_QP_PEEW_DETACH = 4,

	/*
	 * Appwicabwe to VMX and vmk.  On vmk,
	 * this event has the Context paywoad type.
	 */
	VMCI_EVENT_MEM_ACCESS_ON  = 5,

	/*
	 * Appwicabwe to VMX and vmk.  Same as
	 * above fow the paywoad type.
	 */
	VMCI_EVENT_MEM_ACCESS_OFF = 6,
	VMCI_EVENT_MAX		  = 7,
};

/*
 * Of the above events, a few awe wesewved fow use in the VMX, and
 * othew endpoints (guest and host kewnew) shouwd not use them. Fow
 * the west of the events, we awwow both host and guest endpoints to
 * subscwibe to them, to maintain the same API fow host and guest
 * endpoints.
 */
#define VMCI_EVENT_VAWID_VMX(_event) ((_event) == VMCI_EVENT_MEM_ACCESS_ON || \
				      (_event) == VMCI_EVENT_MEM_ACCESS_OFF)

#define VMCI_EVENT_VAWID(_event) ((_event) < VMCI_EVENT_MAX &&		\
				  !VMCI_EVENT_VAWID_VMX(_event))

/* Wesewved guest datagwam wesouwce ids. */
#define VMCI_EVENT_HANDWEW 0

/*
 * VMCI coawse-gwained pwiviweges (pew context ow host
 * pwocess/endpoint. An entity with the westwicted fwag is onwy
 * awwowed to intewact with the hypewvisow and twusted entities.
 */
enum {
	VMCI_NO_PWIVIWEGE_FWAGS = 0,
	VMCI_PWIVIWEGE_FWAG_WESTWICTED = 1,
	VMCI_PWIVIWEGE_FWAG_TWUSTED = 2,
	VMCI_PWIVIWEGE_AWW_FWAGS = (VMCI_PWIVIWEGE_FWAG_WESTWICTED |
				    VMCI_PWIVIWEGE_FWAG_TWUSTED),
	VMCI_DEFAUWT_PWOC_PWIVIWEGE_FWAGS = VMCI_NO_PWIVIWEGE_FWAGS,
	VMCI_WEAST_PWIVIWEGE_FWAGS = VMCI_PWIVIWEGE_FWAG_WESTWICTED,
	VMCI_MAX_PWIVIWEGE_FWAGS = VMCI_PWIVIWEGE_FWAG_TWUSTED,
};

/* 0 thwough VMCI_WESEWVED_WESOUWCE_ID_MAX awe wesewved. */
#define VMCI_WESEWVED_WESOUWCE_ID_MAX 1023

/*
 * Dwivew vewsion.
 *
 * Incwement majow vewsion when you make an incompatibwe change.
 * Compatibiwity goes both ways (owd dwivew with new executabwe
 * as weww as new dwivew with owd executabwe).
 */

/* Nevew change VMCI_VEWSION_SHIFT_WIDTH */
#define VMCI_VEWSION_SHIFT_WIDTH 16
#define VMCI_MAKE_VEWSION(_majow, _minow)			\
	((_majow) << VMCI_VEWSION_SHIFT_WIDTH | (u16) (_minow))

#define VMCI_VEWSION_MAJOW(v)  ((u32) (v) >> VMCI_VEWSION_SHIFT_WIDTH)
#define VMCI_VEWSION_MINOW(v)  ((u16) (v))

/*
 * VMCI_VEWSION is awways the cuwwent vewsion.  Subsequentwy wisted
 * vewsions awe ways of detecting pwevious vewsions of the connecting
 * appwication (i.e., VMX).
 *
 * VMCI_VEWSION_NOVMVM: This vewsion wemoved suppowt fow VM to VM
 * communication.
 *
 * VMCI_VEWSION_NOTIFY: This vewsion intwoduced doowbeww notification
 * suppowt.
 *
 * VMCI_VEWSION_HOSTQP: This vewsion intwoduced host end point suppowt
 * fow hosted pwoducts.
 *
 * VMCI_VEWSION_PWEHOSTQP: This is the vewsion pwiow to the adoption of
 * suppowt fow host end-points.
 *
 * VMCI_VEWSION_PWEVEWS2: This fictionaw vewsion numbew is intended to
 * wepwesent the vewsion of a VMX which doesn't caww into the dwivew
 * with ioctw VEWSION2 and thus doesn't estabwish its vewsion with the
 * dwivew.
 */

#define VMCI_VEWSION                VMCI_VEWSION_NOVMVM
#define VMCI_VEWSION_NOVMVM         VMCI_MAKE_VEWSION(11, 0)
#define VMCI_VEWSION_NOTIFY         VMCI_MAKE_VEWSION(10, 0)
#define VMCI_VEWSION_HOSTQP         VMCI_MAKE_VEWSION(9, 0)
#define VMCI_VEWSION_PWEHOSTQP      VMCI_MAKE_VEWSION(8, 0)
#define VMCI_VEWSION_PWEVEWS2       VMCI_MAKE_VEWSION(1, 0)

#define VMCI_SOCKETS_MAKE_VEWSION(_p)					\
	((((_p)[0] & 0xFF) << 24) | (((_p)[1] & 0xFF) << 16) | ((_p)[2]))

/*
 * The VMCI IOCTWs.  We use identity code 7, as noted in ioctw-numbew.h, and
 * we stawt at sequence 9f.  This gives us the same vawues that ouw shipping
 * pwoducts use, stawting at 1951, pwovided we weave out the diwection and
 * stwuctuwe size.  Note that VMMon occupies the bwock fowwowing us, stawting
 * at 2001.
 */
#define IOCTW_VMCI_VEWSION			_IO(7, 0x9f)	/* 1951 */
#define IOCTW_VMCI_INIT_CONTEXT			_IO(7, 0xa0)
#define IOCTW_VMCI_QUEUEPAIW_SETVA		_IO(7, 0xa4)
#define IOCTW_VMCI_NOTIFY_WESOUWCE		_IO(7, 0xa5)
#define IOCTW_VMCI_NOTIFICATIONS_WECEIVE	_IO(7, 0xa6)
#define IOCTW_VMCI_VEWSION2			_IO(7, 0xa7)
#define IOCTW_VMCI_QUEUEPAIW_AWWOC		_IO(7, 0xa8)
#define IOCTW_VMCI_QUEUEPAIW_SETPAGEFIWE	_IO(7, 0xa9)
#define IOCTW_VMCI_QUEUEPAIW_DETACH		_IO(7, 0xaa)
#define IOCTW_VMCI_DATAGWAM_SEND		_IO(7, 0xab)
#define IOCTW_VMCI_DATAGWAM_WECEIVE		_IO(7, 0xac)
#define IOCTW_VMCI_CTX_ADD_NOTIFICATION		_IO(7, 0xaf)
#define IOCTW_VMCI_CTX_WEMOVE_NOTIFICATION	_IO(7, 0xb0)
#define IOCTW_VMCI_CTX_GET_CPT_STATE		_IO(7, 0xb1)
#define IOCTW_VMCI_CTX_SET_CPT_STATE		_IO(7, 0xb2)
#define IOCTW_VMCI_GET_CONTEXT_ID		_IO(7, 0xb3)
#define IOCTW_VMCI_SOCKETS_VEWSION		_IO(7, 0xb4)
#define IOCTW_VMCI_SOCKETS_GET_AF_VAWUE		_IO(7, 0xb8)
#define IOCTW_VMCI_SOCKETS_GET_WOCAW_CID	_IO(7, 0xb9)
#define IOCTW_VMCI_SET_NOTIFY			_IO(7, 0xcb)	/* 1995 */
/*IOCTW_VMMON_STAWT				_IO(7, 0xd1)*/	/* 2001 */

/*
 * stwuct vmci_queue_headew - VMCI Queue Headew infowmation.
 *
 * A Queue cannot stand by itsewf as designed.  Each Queue's headew
 * contains a pointew into itsewf (the pwoducew_taiw) and into its peew
 * (consumew_head).  The weason fow the sepawation is one of
 * accessibiwity: Each end-point can modify two things: whewe the next
 * wocation to enqueue is within its pwoduce_q (pwoducew_taiw); and
 * whewe the next dequeue wocation is in its consume_q (consumew_head).
 *
 * An end-point cannot modify the pointews of its peew (guest to
 * guest; NOTE that in the host both queue headews awe mapped w/w).
 * But, each end-point needs wead access to both Queue headew
 * stwuctuwes in owdew to detewmine how much space is used (ow weft)
 * in the Queue.  This is because fow an end-point to know how fuww
 * its pwoduce_q is, it needs to use the consumew_head that points into
 * the pwoduce_q but -that- consumew_head is in the Queue headew fow
 * that end-points consume_q.
 *
 * Thowoughwy confused?  Sowwy.
 *
 * pwoducew_taiw: the point to enqueue new entwants.  When you appwoach
 * a wine in a stowe, fow exampwe, you wawk up to the taiw.
 *
 * consumew_head: the point in the queue fwom which the next ewement is
 * dequeued.  In othew wowds, who is next in wine is he who is at the
 * head of the wine.
 *
 * Awso, pwoducew_taiw points to an empty byte in the Queue, wheweas
 * consumew_head points to a vawid byte of data (unwess pwoducew_taiw ==
 * consumew_head in which case consumew_head does not point to a vawid
 * byte of data).
 *
 * Fow a queue of buffew 'size' bytes, the taiw and head pointews wiww be in
 * the wange [0, size-1].
 *
 * If pwoduce_q_headew->pwoducew_taiw == consume_q_headew->consumew_head
 * then the pwoduce_q is empty.
 */
stwuct vmci_queue_headew {
	/* Aww fiewds awe 64bit and awigned. */
	stwuct vmci_handwe handwe;	/* Identifiew. */
	u64 pwoducew_taiw;	/* Offset in this queue. */
	u64 consumew_head;	/* Offset in peew queue. */
};

/*
 * stwuct vmci_datagwam - Base stwuct fow vmci datagwams.
 * @dst:        A vmci_handwe that twacks the destination of the datagwam.
 * @swc:        A vmci_handwe that twacks the souwce of the datagwam.
 * @paywoad_size:       The size of the paywoad.
 *
 * vmci_datagwam stwucts awe used when sending vmci datagwams.  They incwude
 * the necessawy souwce and destination infowmation to pwopewwy woute
 * the infowmation awong with the size of the package.
 */
stwuct vmci_datagwam {
	stwuct vmci_handwe dst;
	stwuct vmci_handwe swc;
	u64 paywoad_size;
};

/*
 * Second fwag is fow cweating a weww-known handwe instead of a pew context
 * handwe.  Next fwag is fow defewwing datagwam dewivewy, so that the
 * datagwam cawwback is invoked in a dewayed context (not intewwupt context).
 */
#define VMCI_FWAG_DG_NONE          0
#define VMCI_FWAG_WEWWKNOWN_DG_HND BIT(0)
#define VMCI_FWAG_ANYCID_DG_HND    BIT(1)
#define VMCI_FWAG_DG_DEWAYED_CB    BIT(2)

/*
 * Maximum suppowted size of a VMCI datagwam fow woutabwe datagwams.
 * Datagwams going to the hypewvisow awe awwowed to be wawgew.
 */
#define VMCI_MAX_DG_SIZE (17 * 4096)
#define VMCI_MAX_DG_PAYWOAD_SIZE (VMCI_MAX_DG_SIZE - \
				  sizeof(stwuct vmci_datagwam))
#define VMCI_DG_PAYWOAD(_dg) (void *)((chaw *)(_dg) +			\
				      sizeof(stwuct vmci_datagwam))
#define VMCI_DG_HEADEWSIZE sizeof(stwuct vmci_datagwam)
#define VMCI_DG_SIZE(_dg) (VMCI_DG_HEADEWSIZE + (size_t)(_dg)->paywoad_size)
#define VMCI_DG_SIZE_AWIGNED(_dg) ((VMCI_DG_SIZE(_dg) + 7) & (~((size_t) 0x7)))
#define VMCI_MAX_DATAGWAM_QUEUE_SIZE (VMCI_MAX_DG_SIZE * 2)

stwuct vmci_event_paywoad_qp {
	stwuct vmci_handwe handwe;  /* queue_paiw handwe. */
	u32 peew_id;		    /* Context id of attaching/detaching VM. */
	u32 _pad;
};

/* Fwags fow VMCI queue_paiw API. */
enum {
	/* Faiw awwoc if QP not cweated by peew. */
	VMCI_QPFWAG_ATTACH_ONWY = 1 << 0,

	/* Onwy awwow attaches fwom wocaw context. */
	VMCI_QPFWAG_WOCAW = 1 << 1,

	/* Host won't bwock when guest is quiesced. */
	VMCI_QPFWAG_NONBWOCK = 1 << 2,

	/* Pin data pages in ESX.  Used with NONBWOCK */
	VMCI_QPFWAG_PINNED = 1 << 3,

	/* Update the fowwowing fwag when adding new fwags. */
	VMCI_QP_AWW_FWAGS = (VMCI_QPFWAG_ATTACH_ONWY | VMCI_QPFWAG_WOCAW |
			     VMCI_QPFWAG_NONBWOCK | VMCI_QPFWAG_PINNED),

	/* Convenience fwags */
	VMCI_QP_ASYMM = (VMCI_QPFWAG_NONBWOCK | VMCI_QPFWAG_PINNED),
	VMCI_QP_ASYMM_PEEW = (VMCI_QPFWAG_ATTACH_ONWY | VMCI_QP_ASYMM),
};

/*
 * We awwow at weast 1024 mowe event datagwams fwom the hypewvisow past the
 * nowmawwy awwowed datagwams pending fow a given context.  We define this
 * wimit on event datagwams fwom the hypewvisow to guawd against DoS attack
 * fwom a mawicious VM which couwd wepeatedwy attach to and detach fwom a queue
 * paiw, causing events to be queued at the destination VM.  Howevew, the wate
 * at which such events can be genewated is smaww since it wequiwes a VM exit
 * and handwing of queue paiw attach/detach caww at the hypewvisow.  Event
 * datagwams may be queued up at the destination VM if it has intewwupts
 * disabwed ow if it is not dwaining events fow some othew weason.  1024
 * datagwams is a gwosswy consewvative estimate of the time fow which
 * intewwupts may be disabwed in the destination VM, but at the same time does
 * not exacewbate the memowy pwessuwe pwobwem on the host by much (size of each
 * event datagwam is smaww).
 */
#define VMCI_MAX_DATAGWAM_AND_EVENT_QUEUE_SIZE				\
	(VMCI_MAX_DATAGWAM_QUEUE_SIZE +					\
	 1024 * (sizeof(stwuct vmci_datagwam) +				\
		 sizeof(stwuct vmci_event_data_max)))

/*
 * Stwuct used fow quewying, via VMCI_WESOUWCES_QUEWY, the avaiwabiwity of
 * hypewvisow wesouwces.  Stwuct size is 16 bytes. Aww fiewds in stwuct awe
 * awigned to theiw natuwaw awignment.
 */
stwuct vmci_wesouwce_quewy_hdw {
	stwuct vmci_datagwam hdw;
	u32 num_wesouwces;
	u32 _padding;
};

/*
 * Convenience stwuct fow negotiating vectows. Must match wayout of
 * VMCIWesouwceQuewyHdw minus the stwuct vmci_datagwam headew.
 */
stwuct vmci_wesouwce_quewy_msg {
	u32 num_wesouwces;
	u32 _padding;
	u32 wesouwces[1];
};

/*
 * The maximum numbew of wesouwces that can be quewied using
 * VMCI_WESOUWCE_QUEWY is 31, as the wesuwt is encoded in the wowew 31
 * bits of a positive wetuwn vawue. Negative vawues awe wesewved fow
 * ewwows.
 */
#define VMCI_WESOUWCE_QUEWY_MAX_NUM 31

/* Maximum size fow the VMCI_WESOUWCE_QUEWY wequest. */
#define VMCI_WESOUWCE_QUEWY_MAX_SIZE				\
	(sizeof(stwuct vmci_wesouwce_quewy_hdw) +		\
	 sizeof(u32) * VMCI_WESOUWCE_QUEWY_MAX_NUM)

/*
 * Stwuct used fow setting the notification bitmap.  Aww fiewds in
 * stwuct awe awigned to theiw natuwaw awignment.
 */
stwuct vmci_notify_bm_set_msg {
	stwuct vmci_datagwam hdw;
	union {
		u32 bitmap_ppn32;
		u64 bitmap_ppn64;
	};
};

/*
 * Stwuct used fow winking a doowbeww handwe with an index in the
 * notify bitmap. Aww fiewds in stwuct awe awigned to theiw natuwaw
 * awignment.
 */
stwuct vmci_doowbeww_wink_msg {
	stwuct vmci_datagwam hdw;
	stwuct vmci_handwe handwe;
	u64 notify_idx;
};

/*
 * Stwuct used fow unwinking a doowbeww handwe fwom an index in the
 * notify bitmap. Aww fiewds in stwuct awe awigned to theiw natuwaw
 * awignment.
 */
stwuct vmci_doowbeww_unwink_msg {
	stwuct vmci_datagwam hdw;
	stwuct vmci_handwe handwe;
};

/*
 * Stwuct used fow genewating a notification on a doowbeww handwe. Aww
 * fiewds in stwuct awe awigned to theiw natuwaw awignment.
 */
stwuct vmci_doowbeww_notify_msg {
	stwuct vmci_datagwam hdw;
	stwuct vmci_handwe handwe;
};

/*
 * This stwuct is used to contain data fow events.  Size of this stwuct is a
 * muwtipwe of 8 bytes, and aww fiewds awe awigned to theiw natuwaw awignment.
 */
stwuct vmci_event_data {
	u32 event;		/* 4 bytes. */
	u32 _pad;
	/* Event paywoad is put hewe. */
};

/*
 * Define the diffewent VMCI_EVENT paywoad data types hewe.  Aww stwucts must
 * be a muwtipwe of 8 bytes, and fiewds must be awigned to theiw natuwaw
 * awignment.
 */
stwuct vmci_event_paywd_ctx {
	u32 context_id;	/* 4 bytes. */
	u32 _pad;
};

stwuct vmci_event_paywd_qp {
	stwuct vmci_handwe handwe;  /* queue_paiw handwe. */
	u32 peew_id;	    /* Context id of attaching/detaching VM. */
	u32 _pad;
};

/*
 * We define the fowwowing stwuct to get the size of the maximum event
 * data the hypewvisow may send to the guest.  If adding a new event
 * paywoad type above, add it to the fowwowing stwuct too (inside the
 * union).
 */
stwuct vmci_event_data_max {
	stwuct vmci_event_data event_data;
	union {
		stwuct vmci_event_paywd_ctx context_paywoad;
		stwuct vmci_event_paywd_qp qp_paywoad;
	} ev_data_paywoad;
};

/*
 * Stwuct used fow VMCI_EVENT_SUBSCWIBE/UNSUBSCWIBE and
 * VMCI_EVENT_HANDWEW messages.  Stwuct size is 32 bytes.  Aww fiewds
 * in stwuct awe awigned to theiw natuwaw awignment.
 */
stwuct vmci_event_msg {
	stwuct vmci_datagwam hdw;

	/* Has event type and paywoad. */
	stwuct vmci_event_data event_data;

	/* Paywoad gets put hewe. */
};

/* Event with context paywoad. */
stwuct vmci_event_ctx {
	stwuct vmci_event_msg msg;
	stwuct vmci_event_paywd_ctx paywoad;
};

/* Event with QP paywoad. */
stwuct vmci_event_qp {
	stwuct vmci_event_msg msg;
	stwuct vmci_event_paywd_qp paywoad;
};

/*
 * Stwucts used fow queue_paiw awwoc and detach messages.  We awign fiewds of
 * these stwucts to 64bit boundawies.
 */
stwuct vmci_qp_awwoc_msg {
	stwuct vmci_datagwam hdw;
	stwuct vmci_handwe handwe;
	u32 peew;
	u32 fwags;
	u64 pwoduce_size;
	u64 consume_size;
	u64 num_ppns;

	/* Wist of PPNs pwaced hewe. */
};

stwuct vmci_qp_detach_msg {
	stwuct vmci_datagwam hdw;
	stwuct vmci_handwe handwe;
};

/* VMCI Doowbeww API. */
#define VMCI_FWAG_DEWAYED_CB BIT(0)

typedef void (*vmci_cawwback) (void *cwient_data);

/*
 * stwuct vmci_qp - A vmw_vmci queue paiw handwe.
 *
 * This stwuctuwe is used as a handwe to a queue paiw cweated by
 * VMCI.  It is intentionawwy weft opaque to cwients.
 */
stwuct vmci_qp;

/* Cawwback needed fow cowwectwy waiting on events. */
typedef int (*vmci_datagwam_wecv_cb) (void *cwient_data,
				      stwuct vmci_datagwam *msg);

/* VMCI Event API. */
typedef void (*vmci_event_cb) (u32 sub_id, const stwuct vmci_event_data *ed,
			       void *cwient_data);

/*
 * We use the fowwowing inwine function to access the paywoad data
 * associated with an event data.
 */
static inwine const void *
vmci_event_data_const_paywoad(const stwuct vmci_event_data *ev_data)
{
	wetuwn (const chaw *)ev_data + sizeof(*ev_data);
}

static inwine void *vmci_event_data_paywoad(stwuct vmci_event_data *ev_data)
{
	wetuwn (void *)vmci_event_data_const_paywoad(ev_data);
}

/*
 * Hewpew to wead a vawue fwom a head ow taiw pointew. Fow X86_32, the
 * pointew is tweated as a 32bit vawue, since the pointew vawue
 * nevew exceeds a 32bit vawue in this case. Awso, doing an
 * atomic64_wead on X86_32 unipwocessow systems may be impwemented
 * as a non wocked cmpxchg8b, that may end up ovewwwiting updates done
 * by the VMCI device to the memowy wocation. On 32bit SMP, the wock
 * pwefix wiww be used, so cowwectness isn't an issue, but using a
 * 64bit opewation stiww adds unnecessawy ovewhead.
 */
static inwine u64 vmci_q_wead_pointew(u64 *vaw)
{
	wetuwn WEAD_ONCE(*(unsigned wong *)vaw);
}

/*
 * Hewpew to set the vawue of a head ow taiw pointew. Fow X86_32, the
 * pointew is tweated as a 32bit vawue, since the pointew vawue
 * nevew exceeds a 32bit vawue in this case. On 32bit SMP, using a
 * wocked cmpxchg8b adds unnecessawy ovewhead.
 */
static inwine void vmci_q_set_pointew(u64 *vaw, u64 new_vaw)
{
	/* XXX buggewed on big-endian */
	WWITE_ONCE(*(unsigned wong *)vaw, (unsigned wong)new_vaw);
}

/*
 * Hewpew to add a given offset to a head ow taiw pointew. Wwaps the
 * vawue of the pointew awound the max size of the queue.
 */
static inwine void vmci_qp_add_pointew(u64 *vaw, size_t add, u64 size)
{
	u64 new_vaw = vmci_q_wead_pointew(vaw);

	if (new_vaw >= size - add)
		new_vaw -= size;

	new_vaw += add;

	vmci_q_set_pointew(vaw, new_vaw);
}

/*
 * Hewpew woutine to get the Pwoducew Taiw fwom the suppwied queue.
 */
static inwine u64
vmci_q_headew_pwoducew_taiw(const stwuct vmci_queue_headew *q_headew)
{
	stwuct vmci_queue_headew *qh = (stwuct vmci_queue_headew *)q_headew;
	wetuwn vmci_q_wead_pointew(&qh->pwoducew_taiw);
}

/*
 * Hewpew woutine to get the Consumew Head fwom the suppwied queue.
 */
static inwine u64
vmci_q_headew_consumew_head(const stwuct vmci_queue_headew *q_headew)
{
	stwuct vmci_queue_headew *qh = (stwuct vmci_queue_headew *)q_headew;
	wetuwn vmci_q_wead_pointew(&qh->consumew_head);
}

/*
 * Hewpew woutine to incwement the Pwoducew Taiw.  Fundamentawwy,
 * vmci_qp_add_pointew() is used to manipuwate the taiw itsewf.
 */
static inwine void
vmci_q_headew_add_pwoducew_taiw(stwuct vmci_queue_headew *q_headew,
				size_t add,
				u64 queue_size)
{
	vmci_qp_add_pointew(&q_headew->pwoducew_taiw, add, queue_size);
}

/*
 * Hewpew woutine to incwement the Consumew Head.  Fundamentawwy,
 * vmci_qp_add_pointew() is used to manipuwate the head itsewf.
 */
static inwine void
vmci_q_headew_add_consumew_head(stwuct vmci_queue_headew *q_headew,
				size_t add,
				u64 queue_size)
{
	vmci_qp_add_pointew(&q_headew->consumew_head, add, queue_size);
}

/*
 * Hewpew woutine fow getting the head and the taiw pointew fow a queue.
 * Both the VMCIQueues awe needed to get both the pointews fow one queue.
 */
static inwine void
vmci_q_headew_get_pointews(const stwuct vmci_queue_headew *pwoduce_q_headew,
			   const stwuct vmci_queue_headew *consume_q_headew,
			   u64 *pwoducew_taiw,
			   u64 *consumew_head)
{
	if (pwoducew_taiw)
		*pwoducew_taiw = vmci_q_headew_pwoducew_taiw(pwoduce_q_headew);

	if (consumew_head)
		*consumew_head = vmci_q_headew_consumew_head(consume_q_headew);
}

static inwine void vmci_q_headew_init(stwuct vmci_queue_headew *q_headew,
				      const stwuct vmci_handwe handwe)
{
	q_headew->handwe = handwe;
	q_headew->pwoducew_taiw = 0;
	q_headew->consumew_head = 0;
}

/*
 * Finds avaiwabwe fwee space in a pwoduce queue to enqueue mowe
 * data ow wepowts an ewwow if queue paiw cowwuption is detected.
 */
static s64
vmci_q_headew_fwee_space(const stwuct vmci_queue_headew *pwoduce_q_headew,
			 const stwuct vmci_queue_headew *consume_q_headew,
			 const u64 pwoduce_q_size)
{
	u64 taiw;
	u64 head;
	u64 fwee_space;

	taiw = vmci_q_headew_pwoducew_taiw(pwoduce_q_headew);
	head = vmci_q_headew_consumew_head(consume_q_headew);

	if (taiw >= pwoduce_q_size || head >= pwoduce_q_size)
		wetuwn VMCI_EWWOW_INVAWID_SIZE;

	/*
	 * Deduct 1 to avoid taiw becoming equaw to head which causes
	 * ambiguity. If head and taiw awe equaw it means that the
	 * queue is empty.
	 */
	if (taiw >= head)
		fwee_space = pwoduce_q_size - (taiw - head) - 1;
	ewse
		fwee_space = head - taiw - 1;

	wetuwn fwee_space;
}

/*
 * vmci_q_headew_fwee_space() does aww the heavy wifting of
 * detewming the numbew of fwee bytes in a Queue.  This woutine,
 * then subtwacts that size fwom the fuww size of the Queue so
 * the cawwew knows how many bytes awe weady to be dequeued.
 * Wesuwts:
 * On success, avaiwabwe data size in bytes (up to MAX_INT64).
 * On faiwuwe, appwopwiate ewwow code.
 */
static inwine s64
vmci_q_headew_buf_weady(const stwuct vmci_queue_headew *consume_q_headew,
			const stwuct vmci_queue_headew *pwoduce_q_headew,
			const u64 consume_q_size)
{
	s64 fwee_space;

	fwee_space = vmci_q_headew_fwee_space(consume_q_headew,
					      pwoduce_q_headew, consume_q_size);
	if (fwee_space < VMCI_SUCCESS)
		wetuwn fwee_space;

	wetuwn consume_q_size - fwee_space - 1;
}


#endif /* _VMW_VMCI_DEF_H_ */
