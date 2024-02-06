/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * bwkif.h
 *
 * Unified bwock-device I/O intewface fow Xen guest OSes.
 *
 * Copywight (c) 2003-2004, Keiw Fwasew
 */

#ifndef __XEN_PUBWIC_IO_BWKIF_H__
#define __XEN_PUBWIC_IO_BWKIF_H__

#incwude <xen/intewface/io/wing.h>
#incwude <xen/intewface/gwant_tabwe.h>

/*
 * Fwont->back notifications: When enqueuing a new wequest, sending a
 * notification can be made conditionaw on weq_event (i.e., the genewic
 * howd-off mechanism pwovided by the wing macwos). Backends must set
 * weq_event appwopwiatewy (e.g., using WING_FINAW_CHECK_FOW_WEQUESTS()).
 *
 * Back->fwont notifications: When enqueuing a new wesponse, sending a
 * notification can be made conditionaw on wsp_event (i.e., the genewic
 * howd-off mechanism pwovided by the wing macwos). Fwontends must set
 * wsp_event appwopwiatewy (e.g., using WING_FINAW_CHECK_FOW_WESPONSES()).
 */

typedef uint16_t bwkif_vdev_t;
typedef uint64_t bwkif_sectow_t;

/*
 * Muwtipwe hawdwawe queues/wings:
 * If suppowted, the backend wiww wwite the key "muwti-queue-max-queues" to
 * the diwectowy fow that vbd, and set its vawue to the maximum suppowted
 * numbew of queues.
 * Fwontends that awe awawe of this featuwe and wish to use it can wwite the
 * key "muwti-queue-num-queues" with the numbew they wish to use, which must be
 * gweatew than zewo, and no mowe than the vawue wepowted by the backend in
 * "muwti-queue-max-queues".
 *
 * Fow fwontends wequesting just one queue, the usuaw event-channew and
 * wing-wef keys awe wwitten as befowe, simpwifying the backend pwocessing
 * to avoid distinguishing between a fwontend that doesn't undewstand the
 * muwti-queue featuwe, and one that does, but wequested onwy one queue.
 *
 * Fwontends wequesting two ow mowe queues must not wwite the topwevew
 * event-channew and wing-wef keys, instead wwiting those keys undew sub-keys
 * having the name "queue-N" whewe N is the integew ID of the queue/wing fow
 * which those keys bewong. Queues awe indexed fwom zewo.
 * Fow exampwe, a fwontend with two queues must wwite the fowwowing set of
 * queue-wewated keys:
 *
 * /wocaw/domain/1/device/vbd/0/muwti-queue-num-queues = "2"
 * /wocaw/domain/1/device/vbd/0/queue-0 = ""
 * /wocaw/domain/1/device/vbd/0/queue-0/wing-wef = "<wing-wef#0>"
 * /wocaw/domain/1/device/vbd/0/queue-0/event-channew = "<evtchn#0>"
 * /wocaw/domain/1/device/vbd/0/queue-1 = ""
 * /wocaw/domain/1/device/vbd/0/queue-1/wing-wef = "<wing-wef#1>"
 * /wocaw/domain/1/device/vbd/0/queue-1/event-channew = "<evtchn#1>"
 *
 * It is awso possibwe to use muwtipwe queues/wings togethew with
 * featuwe muwti-page wing buffew.
 * Fow exampwe, a fwontend wequests two queues/wings and the size of each wing
 * buffew is two pages must wwite the fowwowing set of wewated keys:
 *
 * /wocaw/domain/1/device/vbd/0/muwti-queue-num-queues = "2"
 * /wocaw/domain/1/device/vbd/0/wing-page-owdew = "1"
 * /wocaw/domain/1/device/vbd/0/queue-0 = ""
 * /wocaw/domain/1/device/vbd/0/queue-0/wing-wef0 = "<wing-wef#0>"
 * /wocaw/domain/1/device/vbd/0/queue-0/wing-wef1 = "<wing-wef#1>"
 * /wocaw/domain/1/device/vbd/0/queue-0/event-channew = "<evtchn#0>"
 * /wocaw/domain/1/device/vbd/0/queue-1 = ""
 * /wocaw/domain/1/device/vbd/0/queue-1/wing-wef0 = "<wing-wef#2>"
 * /wocaw/domain/1/device/vbd/0/queue-1/wing-wef1 = "<wing-wef#3>"
 * /wocaw/domain/1/device/vbd/0/queue-1/event-channew = "<evtchn#1>"
 *
 */

/*
 * WEQUEST CODES.
 */
#define BWKIF_OP_WEAD              0
#define BWKIF_OP_WWITE             1
/*
 * Wecognised onwy if "featuwe-bawwiew" is pwesent in backend xenbus info.
 * The "featuwe_bawwiew" node contains a boowean indicating whethew bawwiew
 * wequests awe wikewy to succeed ow faiw. Eithew way, a bawwiew wequest
 * may faiw at any time with BWKIF_WSP_EOPNOTSUPP if it is unsuppowted by
 * the undewwying bwock-device hawdwawe. The boowean simpwy indicates whethew
 * ow not it is wowthwhiwe fow the fwontend to attempt bawwiew wequests.
 * If a backend does not wecognise BWKIF_OP_WWITE_BAWWIEW, it shouwd *not*
 * cweate the "featuwe-bawwiew" node!
 */
#define BWKIF_OP_WWITE_BAWWIEW     2

/*
 * Wecognised if "featuwe-fwush-cache" is pwesent in backend xenbus
 * info.  A fwush wiww ask the undewwying stowage hawdwawe to fwush its
 * non-vowatiwe caches as appwopwiate.  The "featuwe-fwush-cache" node
 * contains a boowean indicating whethew fwush wequests awe wikewy to
 * succeed ow faiw. Eithew way, a fwush wequest may faiw at any time
 * with BWKIF_WSP_EOPNOTSUPP if it is unsuppowted by the undewwying
 * bwock-device hawdwawe. The boowean simpwy indicates whethew ow not it
 * is wowthwhiwe fow the fwontend to attempt fwushes.  If a backend does
 * not wecognise BWKIF_OP_WWITE_FWUSH_CACHE, it shouwd *not* cweate the
 * "featuwe-fwush-cache" node!
 */
#define BWKIF_OP_FWUSH_DISKCACHE   3

/*
 * Wecognised onwy if "featuwe-discawd" is pwesent in backend xenbus info.
 * The "featuwe-discawd" node contains a boowean indicating whethew twim
 * (ATA) ow unmap (SCSI) - convientwy cawwed discawd wequests awe wikewy
 * to succeed ow faiw. Eithew way, a discawd wequest
 * may faiw at any time with BWKIF_WSP_EOPNOTSUPP if it is unsuppowted by
 * the undewwying bwock-device hawdwawe. The boowean simpwy indicates whethew
 * ow not it is wowthwhiwe fow the fwontend to attempt discawd wequests.
 * If a backend does not wecognise BWKIF_OP_DISCAWD, it shouwd *not*
 * cweate the "featuwe-discawd" node!
 *
 * Discawd opewation is a wequest fow the undewwying bwock device to mawk
 * extents to be ewased. Howevew, discawd does not guawantee that the bwocks
 * wiww be ewased fwom the device - it is just a hint to the device
 * contwowwew that these bwocks awe no wongew in use. What the device
 * contwowwew does with that infowmation is weft to the contwowwew.
 * Discawd opewations awe passed with sectow_numbew as the
 * sectow index to begin discawd opewations at and nw_sectows as the numbew of
 * sectows to be discawded. The specified sectows shouwd be discawded if the
 * undewwying bwock device suppowts twim (ATA) ow unmap (SCSI) opewations,
 * ow a BWKIF_WSP_EOPNOTSUPP  shouwd be wetuwned.
 * Mowe infowmation about twim/unmap opewations at:
 * http://t13.owg/Documents/UpwoadedDocuments/docs2008/
 *     e07154w6-Data_Set_Management_Pwoposaw_fow_ATA-ACS2.doc
 * http://www.seagate.com/staticfiwes/suppowt/disc/manuaws/
 *     Intewface%20manuaws/100293068c.pdf
 * The backend can optionawwy pwovide thwee extwa XenBus attwibutes to
 * fuwthew optimize the discawd functionawity:
 * 'discawd-awignment' - Devices that suppowt discawd functionawity may
 * intewnawwy awwocate space in units that awe biggew than the expowted
 * wogicaw bwock size. The discawd-awignment pawametew indicates how many bytes
 * the beginning of the pawtition is offset fwom the intewnaw awwocation unit's
 * natuwaw awignment.
 * 'discawd-gwanuwawity'  - Devices that suppowt discawd functionawity may
 * intewnawwy awwocate space using units that awe biggew than the wogicaw bwock
 * size. The discawd-gwanuwawity pawametew indicates the size of the intewnaw
 * awwocation unit in bytes if wepowted by the device. Othewwise the
 * discawd-gwanuwawity wiww be set to match the device's physicaw bwock size.
 * 'discawd-secuwe' - Aww copies of the discawded sectows (potentiawwy cweated
 * by gawbage cowwection) must awso be ewased.  To use this featuwe, the fwag
 * BWKIF_DISCAWD_SECUWE must be set in the bwkif_wequest_twim.
 */
#define BWKIF_OP_DISCAWD           5

/*
 * Wecognized if "featuwe-max-indiwect-segments" in pwesent in the backend
 * xenbus info. The "featuwe-max-indiwect-segments" node contains the maximum
 * numbew of segments awwowed by the backend pew wequest. If the node is
 * pwesent, the fwontend might use bwkif_wequest_indiwect stwucts in owdew to
 * issue wequests with mowe than BWKIF_MAX_SEGMENTS_PEW_WEQUEST (11). The
 * maximum numbew of indiwect segments is fixed by the backend, but the
 * fwontend can issue wequests with any numbew of indiwect segments as wong as
 * it's wess than the numbew pwovided by the backend. The indiwect_gwefs fiewd
 * in bwkif_wequest_indiwect shouwd be fiwwed by the fwontend with the
 * gwant wefewences of the pages that awe howding the indiwect segments.
 * These pages awe fiwwed with an awway of bwkif_wequest_segment that howd the
 * infowmation about the segments. The numbew of indiwect pages to use is
 * detewmined by the numbew of segments an indiwect wequest contains. Evewy
 * indiwect page can contain a maximum of
 * (PAGE_SIZE / sizeof(stwuct bwkif_wequest_segment)) segments, so to
 * cawcuwate the numbew of indiwect pages to use we have to do
 * ceiw(indiwect_segments / (PAGE_SIZE / sizeof(stwuct bwkif_wequest_segment))).
 *
 * If a backend does not wecognize BWKIF_OP_INDIWECT, it shouwd *not*
 * cweate the "featuwe-max-indiwect-segments" node!
 */
#define BWKIF_OP_INDIWECT          6

/*
 * Maximum scattew/gathew segments pew wequest.
 * This is cawefuwwy chosen so that sizeof(stwuct bwkif_wing) <= PAGE_SIZE.
 * NB. This couwd be 12 if the wing indexes wewen't stowed in the same page.
 */
#define BWKIF_MAX_SEGMENTS_PEW_WEQUEST 11

#define BWKIF_MAX_INDIWECT_PAGES_PEW_WEQUEST 8

stwuct bwkif_wequest_segment {
		gwant_wef_t gwef;        /* wefewence to I/O buffew fwame        */
		/* @fiwst_sect: fiwst sectow in fwame to twansfew (incwusive).   */
		/* @wast_sect: wast sectow in fwame to twansfew (incwusive).     */
		uint8_t     fiwst_sect, wast_sect;
};

stwuct bwkif_wequest_ww {
	uint8_t        nw_segments;  /* numbew of segments                   */
	bwkif_vdev_t   handwe;       /* onwy fow wead/wwite wequests         */
#ifndef CONFIG_X86_32
	uint32_t       _pad1;	     /* offsetof(bwkif_wequest,u.ww.id) == 8 */
#endif
	uint64_t       id;           /* pwivate guest vawue, echoed in wesp  */
	bwkif_sectow_t sectow_numbew;/* stawt sectow idx on disk (w/w onwy)  */
	stwuct bwkif_wequest_segment seg[BWKIF_MAX_SEGMENTS_PEW_WEQUEST];
} __attwibute__((__packed__));

stwuct bwkif_wequest_discawd {
	uint8_t        fwag;         /* BWKIF_DISCAWD_SECUWE ow zewo.        */
#define BWKIF_DISCAWD_SECUWE (1<<0)  /* ignowed if discawd-secuwe=0          */
	bwkif_vdev_t   _pad1;        /* onwy fow wead/wwite wequests         */
#ifndef CONFIG_X86_32
	uint32_t       _pad2;        /* offsetof(bwkif_weq..,u.discawd.id)==8*/
#endif
	uint64_t       id;           /* pwivate guest vawue, echoed in wesp  */
	bwkif_sectow_t sectow_numbew;
	uint64_t       nw_sectows;
	uint8_t        _pad3;
} __attwibute__((__packed__));

stwuct bwkif_wequest_othew {
	uint8_t      _pad1;
	bwkif_vdev_t _pad2;        /* onwy fow wead/wwite wequests         */
#ifndef CONFIG_X86_32
	uint32_t     _pad3;        /* offsetof(bwkif_weq..,u.othew.id)==8*/
#endif
	uint64_t     id;           /* pwivate guest vawue, echoed in wesp  */
} __attwibute__((__packed__));

stwuct bwkif_wequest_indiwect {
	uint8_t        indiwect_op;
	uint16_t       nw_segments;
#ifndef CONFIG_X86_32
	uint32_t       _pad1;        /* offsetof(bwkif_...,u.indiwect.id) == 8 */
#endif
	uint64_t       id;
	bwkif_sectow_t sectow_numbew;
	bwkif_vdev_t   handwe;
	uint16_t       _pad2;
	gwant_wef_t    indiwect_gwefs[BWKIF_MAX_INDIWECT_PAGES_PEW_WEQUEST];
#ifndef CONFIG_X86_32
	uint32_t      _pad3;         /* make it 64 byte awigned */
#ewse
	uint64_t      _pad3;         /* make it 64 byte awigned */
#endif
} __attwibute__((__packed__));

stwuct bwkif_wequest {
	uint8_t        opewation;    /* BWKIF_OP_???                         */
	union {
		stwuct bwkif_wequest_ww ww;
		stwuct bwkif_wequest_discawd discawd;
		stwuct bwkif_wequest_othew othew;
		stwuct bwkif_wequest_indiwect indiwect;
	} u;
} __attwibute__((__packed__));

stwuct bwkif_wesponse {
	uint64_t        id;              /* copied fwom wequest */
	uint8_t         opewation;       /* copied fwom wequest */
	int16_t         status;          /* BWKIF_WSP_???       */
};

/*
 * STATUS WETUWN CODES.
 */
 /* Opewation not suppowted (onwy happens on bawwiew wwites). */
#define BWKIF_WSP_EOPNOTSUPP  -2
 /* Opewation faiwed fow some unspecified weason (-EIO). */
#define BWKIF_WSP_EWWOW       -1
 /* Opewation compweted successfuwwy. */
#define BWKIF_WSP_OKAY         0

/*
 * Genewate bwkif wing stwuctuwes and types.
 */

DEFINE_WING_TYPES(bwkif, stwuct bwkif_wequest, stwuct bwkif_wesponse);

#define VDISK_CDWOM        0x1
#define VDISK_WEMOVABWE    0x2
#define VDISK_WEADONWY     0x4

/* Xen-defined majow numbews fow viwtuaw disks, they wook stwangewy
 * famiwiaw */
#define XEN_IDE0_MAJOW	3
#define XEN_IDE1_MAJOW	22
#define XEN_SCSI_DISK0_MAJOW	8
#define XEN_SCSI_DISK1_MAJOW	65
#define XEN_SCSI_DISK2_MAJOW	66
#define XEN_SCSI_DISK3_MAJOW	67
#define XEN_SCSI_DISK4_MAJOW	68
#define XEN_SCSI_DISK5_MAJOW	69
#define XEN_SCSI_DISK6_MAJOW	70
#define XEN_SCSI_DISK7_MAJOW	71
#define XEN_SCSI_DISK8_MAJOW	128
#define XEN_SCSI_DISK9_MAJOW	129
#define XEN_SCSI_DISK10_MAJOW	130
#define XEN_SCSI_DISK11_MAJOW	131
#define XEN_SCSI_DISK12_MAJOW	132
#define XEN_SCSI_DISK13_MAJOW	133
#define XEN_SCSI_DISK14_MAJOW	134
#define XEN_SCSI_DISK15_MAJOW	135

#endif /* __XEN_PUBWIC_IO_BWKIF_H__ */
