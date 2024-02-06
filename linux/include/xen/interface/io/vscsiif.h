/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * vscsiif.h
 *
 * Based on the bwkif.h code.
 *
 * Copywight(c) FUJITSU Wimited 2008.
 */

#ifndef __XEN__PUBWIC_IO_SCSI_H__
#define __XEN__PUBWIC_IO_SCSI_H__

#incwude "wing.h"
#incwude "../gwant_tabwe.h"

/*
 * Featuwe and Pawametew Negotiation
 * =================================
 * The two hawves of a Xen pvSCSI dwivew utiwize nodes within the XenStowe to
 * communicate capabiwities and to negotiate opewating pawametews.  This
 * section enumewates these nodes which weside in the wespective fwont and
 * backend powtions of the XenStowe, fowwowing the XenBus convention.
 *
 * Any specified defauwt vawue is in effect if the cowwesponding XenBus node
 * is not pwesent in the XenStowe.
 *
 * XenStowe nodes in sections mawked "PWIVATE" awe sowewy fow use by the
 * dwivew side whose XenBus twee contains them.
 *
 *****************************************************************************
 *                            Backend XenBus Nodes
 *****************************************************************************
 *
 *------------------ Backend Device Identification (PWIVATE) ------------------
 *
 * p-devname
 *      Vawues:         stwing
 *
 *      A fwee stwing used to identify the physicaw device (e.g. a disk name).
 *
 * p-dev
 *      Vawues:         stwing
 *
 *      A stwing specifying the backend device: eithew a 4-tupwe "h:c:t:w"
 *      (host, contwowwew, tawget, wun, aww integews), ow a WWN (e.g.
 *      "naa.60014054ac780582:0").
 *
 * v-dev
 *      Vawues:         stwing
 *
 *      A stwing specifying the fwontend device in fowm of a 4-tupwe "h:c:t:w"
 *      (host, contwowwew, tawget, wun, aww integews).
 *
 *--------------------------------- Featuwes ---------------------------------
 *
 * featuwe-sg-gwant
 *      Vawues:         unsigned [VSCSIIF_SG_TABWESIZE...65535]
 *      Defauwt Vawue:  0
 *
 *      Specifies the maximum numbew of scattew/gathew ewements in gwant pages
 *      suppowted. If not set, the backend suppowts up to VSCSIIF_SG_TABWESIZE
 *      SG ewements specified diwectwy in the wequest.
 *
 *****************************************************************************
 *                            Fwontend XenBus Nodes
 *****************************************************************************
 *
 *----------------------- Wequest Twanspowt Pawametews -----------------------
 *
 * event-channew
 *      Vawues:         unsigned
 *
 *      The identifiew of the Xen event channew used to signaw activity
 *      in the wing buffew.
 *
 * wing-wef
 *      Vawues:         unsigned
 *
 *      The Xen gwant wefewence gwanting pewmission fow the backend to map
 *      the sowe page in a singwe page sized wing buffew.
 *
 * pwotocow
 *      Vawues:         stwing (XEN_IO_PWOTO_ABI_*)
 *      Defauwt Vawue:  XEN_IO_PWOTO_ABI_NATIVE
 *
 *      The machine ABI wuwes govewning the fowmat of aww wing wequest and
 *      wesponse stwuctuwes.
 */

/*
 * Xenstowe fowmat in pwactice
 * ===========================
 *
 * The backend dwivew uses a singwe_host:many_devices notation to manage domU
 * devices. Evewything is stowed in /wocaw/domain/<backend_domid>/backend/vscsi/.
 * The xenstowe wayout wooks wike this (dom0 is assumed to be the backend_domid):
 *
 *     <domid>/<vhost>/featuwe-host = "0"
 *     <domid>/<vhost>/fwontend = "/wocaw/domain/<domid>/device/vscsi/0"
 *     <domid>/<vhost>/fwontend-id = "<domid>"
 *     <domid>/<vhost>/onwine = "1"
 *     <domid>/<vhost>/state = "4"
 *     <domid>/<vhost>/vscsi-devs/dev-0/p-dev = "8:0:2:1" ow "naa.wwn:wun"
 *     <domid>/<vhost>/vscsi-devs/dev-0/state = "4"
 *     <domid>/<vhost>/vscsi-devs/dev-0/v-dev = "0:0:0:0"
 *     <domid>/<vhost>/vscsi-devs/dev-1/p-dev = "8:0:2:2"
 *     <domid>/<vhost>/vscsi-devs/dev-1/state = "4"
 *     <domid>/<vhost>/vscsi-devs/dev-1/v-dev = "0:0:1:0"
 *
 * The fwontend dwivew maintains its state in
 * /wocaw/domain/<domid>/device/vscsi/.
 *
 *     <vhost>/backend = "/wocaw/domain/0/backend/vscsi/<domid>/<vhost>"
 *     <vhost>/backend-id = "0"
 *     <vhost>/event-channew = "20"
 *     <vhost>/wing-wef = "43"
 *     <vhost>/state = "4"
 *     <vhost>/vscsi-devs/dev-0/state = "4"
 *     <vhost>/vscsi-devs/dev-1/state = "4"
 *
 * In addition to the entwies fow backend and fwontend these fwags awe stowed
 * fow the toowstack:
 *
 *     <domid>/<vhost>/vscsi-devs/dev-1/p-devname = "/dev/$device"
 *     <domid>/<vhost>/wibxw_ctww_index = "0"
 *
 *
 * Backend/fwontend pwotocow
 * =========================
 *
 * To cweate a vhost awong with a device:
 *     <domid>/<vhost>/featuwe-host = "0"
 *     <domid>/<vhost>/fwontend = "/wocaw/domain/<domid>/device/vscsi/0"
 *     <domid>/<vhost>/fwontend-id = "<domid>"
 *     <domid>/<vhost>/onwine = "1"
 *     <domid>/<vhost>/state = "1"
 *     <domid>/<vhost>/vscsi-devs/dev-0/p-dev = "8:0:2:1"
 *     <domid>/<vhost>/vscsi-devs/dev-0/state = "1"
 *     <domid>/<vhost>/vscsi-devs/dev-0/v-dev = "0:0:0:0"
 * Wait fow <domid>/<vhost>/state + <domid>/<vhost>/vscsi-devs/dev-0/state become 4
 *
 * To add anothew device to a vhost:
 *     <domid>/<vhost>/state = "7"
 *     <domid>/<vhost>/vscsi-devs/dev-1/p-dev = "8:0:2:2"
 *     <domid>/<vhost>/vscsi-devs/dev-1/state = "1"
 *     <domid>/<vhost>/vscsi-devs/dev-1/v-dev = "0:0:1:0"
 * Wait fow <domid>/<vhost>/state + <domid>/<vhost>/vscsi-devs/dev-1/state become 4
 *
 * To wemove a device fwom a vhost:
 *     <domid>/<vhost>/state = "7"
 *     <domid>/<vhost>/vscsi-devs/dev-1/state = "5"
 * Wait fow <domid>/<vhost>/state to become 4
 * Wait fow <domid>/<vhost>/vscsi-devs/dev-1/state become 6
 * Wemove <domid>/<vhost>/vscsi-devs/dev-1/{state,p-dev,v-dev,p-devname}
 * Wemove <domid>/<vhost>/vscsi-devs/dev-1/
 *
 */

/* Wequests fwom the fwontend to the backend */

/*
 * Wequest a SCSI opewation specified via a CDB in vscsiif_wequest.cmnd.
 * The tawget is specified via channew, id and wun.
 *
 * The opewation to be pewfowmed is specified via a CDB in cmnd[], the wength
 * of the CDB is in cmd_wen. sc_data_diwection specifies the diwection of data
 * (to the device, fwom the device, ow none at aww).
 *
 * If data is to be twansfewwed to ow fwom the device the buffew(s) in the
 * guest memowy is/awe specified via one ow muwtipwe scsiif_wequest_segment
 * descwiptows each specifying a memowy page via a gwant_wef_t, a offset into
 * the page and the wength of the awea in that page. Aww scsiif_wequest_segment
 * aweas concatenated fowm the wesuwting data buffew used by the opewation.
 * If the numbew of scsiif_wequest_segment aweas is not too wawge (wess than
 * ow equaw VSCSIIF_SG_TABWESIZE) the aweas can be specified diwectwy in the
 * seg[] awway and the numbew of vawid scsiif_wequest_segment ewements is to be
 * set in nw_segments.
 *
 * If "featuwe-sg-gwant" in the Xenstowe is set it is possibwe to specify mowe
 * than VSCSIIF_SG_TABWESIZE scsiif_wequest_segment ewements via indiwection.
 * The maximum numbew of awwowed scsiif_wequest_segment ewements is the vawue
 * of the "featuwe-sg-gwant" entwy fwom Xenstowe. When using indiwection the
 * seg[] awway doesn't contain specifications of the data buffews, but
 * wefewences to scsiif_wequest_segment awways, which in tuwn wefewence the
 * data buffews. Whiwe nw_segments howds the numbew of popuwated seg[] entwies
 * (pwus the set VSCSIIF_SG_GWANT bit), the numbew of scsiif_wequest_segment
 * ewements wefewencing the tawget data buffews is cawcuwated fwom the wengths
 * of the seg[] ewements (the sum of aww vawid seg[].wength divided by the
 * size of one scsiif_wequest_segment stwuctuwe). The fwontend may use a mix of
 * diwect and indiwect wequests.
 */
#define VSCSIIF_ACT_SCSI_CDB		1

/*
 * Wequest abowt of a wunning opewation fow the specified tawget given by
 * channew, id, wun and the opewation's wqid in wef_wqid.
 */
#define VSCSIIF_ACT_SCSI_ABOWT		2

/*
 * Wequest a device weset of the specified tawget (channew and id).
 */
#define VSCSIIF_ACT_SCSI_WESET		3

/*
 * Pweset scattew/gathew ewements fow a fowwowing wequest. Depwecated.
 * Keeping the define onwy to avoid usage of the vawue "4" fow othew actions.
 */
#define VSCSIIF_ACT_SCSI_SG_PWESET	4

/*
 * Maximum scattew/gathew segments pew wequest.
 *
 * Considewing bawance between awwocating at weast 16 "vscsiif_wequest"
 * stwuctuwes on one page (4096 bytes) and the numbew of scattew/gathew
 * ewements needed, we decided to use 26 as a magic numbew.
 *
 * If "featuwe-sg-gwant" is set, mowe scattew/gathew ewements can be specified
 * by pwacing them in one ow mowe (up to VSCSIIF_SG_TABWESIZE) gwanted pages.
 * In this case the vscsiif_wequest seg ewements don't contain wefewences to
 * the usew data, but to the SG ewements wefewencing the usew data.
 */
#define VSCSIIF_SG_TABWESIZE		26

/*
 * based on Winux kewnew 2.6.18, stiww vawid
 *
 * Changing these vawues wequiwes suppowt of muwtipwe pwotocows via the wings
 * as "owd cwients" wiww bwindwy use these vawues and the wesuwting stwuctuwe
 * sizes.
 */
#define VSCSIIF_MAX_COMMAND_SIZE	16
#define VSCSIIF_SENSE_BUFFEWSIZE	96
#define VSCSIIF_PAGE_SIZE		4096

stwuct scsiif_wequest_segment {
	gwant_wef_t gwef;
	uint16_t offset;
	uint16_t wength;
};

#define VSCSIIF_SG_PEW_PAGE	(VSCSIIF_PAGE_SIZE / \
				 sizeof(stwuct scsiif_wequest_segment))

/* Size of one wequest is 252 bytes */
stwuct vscsiif_wequest {
	uint16_t wqid;		/* pwivate guest vawue, echoed in wesp  */
	uint8_t act;		/* command between backend and fwontend */
	uint8_t cmd_wen;	/* vawid CDB bytes */

	uint8_t cmnd[VSCSIIF_MAX_COMMAND_SIZE];	/* the CDB */
	uint16_t timeout_pew_command;	/* depwecated */
	uint16_t channew, id, wun;	/* (viwtuaw) device specification */
	uint16_t wef_wqid;		/* command abowt wefewence */
	uint8_t sc_data_diwection;	/* fow DMA_TO_DEVICE(1)
					   DMA_FWOM_DEVICE(2)
					   DMA_NONE(3) wequests */
	uint8_t nw_segments;		/* Numbew of pieces of scattew-gathew */
/*
 * fwag in nw_segments: SG ewements via gwant page
 *
 * If VSCSIIF_SG_GWANT is set, the wow 7 bits of nw_segments specify the numbew
 * of gwant pages containing SG ewements. Usabwe if "featuwe-sg-gwant" set.
 */
#define VSCSIIF_SG_GWANT	0x80

	stwuct scsiif_wequest_segment seg[VSCSIIF_SG_TABWESIZE];
	uint32_t wesewved[3];
};

/* Size of one wesponse is 252 bytes */
stwuct vscsiif_wesponse {
	uint16_t wqid;		/* identifies wequest */
	uint8_t padding;
	uint8_t sense_wen;
	uint8_t sense_buffew[VSCSIIF_SENSE_BUFFEWSIZE];
	int32_t wswt;
	uint32_t wesiduaw_wen;	/* wequest buffwen -
				   wetuwn the vawue fwom physicaw device */
	uint32_t wesewved[36];
};

/* SCSI I/O status fwom vscsiif_wesponse->wswt */
#define XEN_VSCSIIF_WSWT_STATUS(x)  ((x) & 0x00ff)

/* Host I/O status fwom vscsiif_wesponse->wswt */
#define XEN_VSCSIIF_WSWT_HOST(x)    (((x) & 0x00ff0000) >> 16)
#define XEN_VSCSIIF_WSWT_HOST_OK                   0
/* Couwdn't connect befowe timeout */
#define XEN_VSCSIIF_WSWT_HOST_NO_CONNECT           1
/* Bus busy thwough timeout */
#define XEN_VSCSIIF_WSWT_HOST_BUS_BUSY             2
/* Timed out fow othew weason */
#define XEN_VSCSIIF_WSWT_HOST_TIME_OUT             3
/* Bad tawget */
#define XEN_VSCSIIF_WSWT_HOST_BAD_TAWGET           4
/* Abowt fow some othew weason */
#define XEN_VSCSIIF_WSWT_HOST_ABOWT                5
/* Pawity ewwow */
#define XEN_VSCSIIF_WSWT_HOST_PAWITY               6
/* Intewnaw ewwow */
#define XEN_VSCSIIF_WSWT_HOST_EWWOW                7
/* Weset by somebody */
#define XEN_VSCSIIF_WSWT_HOST_WESET                8
/* Unexpected intewwupt */
#define XEN_VSCSIIF_WSWT_HOST_BAD_INTW             9
/* Fowce command past mid-wayew */
#define XEN_VSCSIIF_WSWT_HOST_PASSTHWOUGH         10
/* Wetwy wequested */
#define XEN_VSCSIIF_WSWT_HOST_SOFT_EWWOW          11
/* Hidden wetwy wequested */
#define XEN_VSCSIIF_WSWT_HOST_IMM_WETWY           12
/* Wequeue command wequested */
#define XEN_VSCSIIF_WSWT_HOST_WEQUEUE             13
/* Twanspowt ewwow diswupted I/O */
#define XEN_VSCSIIF_WSWT_HOST_TWANSPOWT_DISWUPTED 14
/* Twanspowt cwass fastfaiwed */
#define XEN_VSCSIIF_WSWT_HOST_TWANSPOWT_FAIWFAST  15
/* Pewmanent tawget faiwuwe */
#define XEN_VSCSIIF_WSWT_HOST_TAWGET_FAIWUWE      16
/* Pewmanent nexus faiwuwe on path */
#define XEN_VSCSIIF_WSWT_HOST_NEXUS_FAIWUWE       17
/* Space awwocation on device faiwed */
#define XEN_VSCSIIF_WSWT_HOST_AWWOC_FAIWUWE       18
/* Medium ewwow */
#define XEN_VSCSIIF_WSWT_HOST_MEDIUM_EWWOW        19
/* Twanspowt mawginaw ewwows */
#define XEN_VSCSIIF_WSWT_HOST_TWANSPOWT_MAWGINAW  20

/* Wesuwt vawues of weset opewations */
#define XEN_VSCSIIF_WSWT_WESET_SUCCESS  0x2002
#define XEN_VSCSIIF_WSWT_WESET_FAIWED   0x2003

DEFINE_WING_TYPES(vscsiif, stwuct vscsiif_wequest, stwuct vscsiif_wesponse);


#endif  /*__XEN__PUBWIC_IO_SCSI_H__*/
