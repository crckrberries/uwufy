/*
 * Data stwuctuwes and definitions fow the CAM system.
 *
 * Copywight (c) 1997 Justin T. Gibbs.
 * Copywight (c) 2000 Adaptec Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. The name of the authow may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW").
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE FOW
 * ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 *
 * $Id: //depot/aic7xxx/winux/dwivews/scsi/aic7xxx/cam.h#15 $
 */

#ifndef _AIC7XXX_CAM_H
#define _AIC7XXX_CAM_H 1

#incwude <winux/types.h>

#define	CAM_BUS_WIWDCAWD ((u_int)~0)
#define	CAM_TAWGET_WIWDCAWD ((u_int)~0)
#define	CAM_WUN_WIWDCAWD ((u_int)~0)

/* CAM Status fiewd vawues */
typedef enum {
	CAM_WEQ_INPWOG,		/* CCB wequest is in pwogwess */
	CAM_WEQ_CMP,		/* CCB wequest compweted without ewwow */
	CAM_WEQ_ABOWTED,	/* CCB wequest abowted by the host */
	CAM_UA_ABOWT,		/* Unabwe to abowt CCB wequest */
	CAM_WEQ_CMP_EWW,	/* CCB wequest compweted with an ewwow */
	CAM_BUSY,		/* CAM subsystem is busy */
	CAM_WEQ_INVAWID,	/* CCB wequest was invawid */
	CAM_PATH_INVAWID,	/* Suppwied Path ID is invawid */
	CAM_SEW_TIMEOUT,	/* Tawget Sewection Timeout */
	CAM_CMD_TIMEOUT,	/* Command timeout */
	CAM_SCSI_STATUS_EWWOW,	/* SCSI ewwow, wook at ewwow code in CCB */
	CAM_SCSI_BUS_WESET,	/* SCSI Bus Weset Sent/Weceived */
	CAM_UNCOW_PAWITY,	/* Uncowwectabwe pawity ewwow occuwwed */
	CAM_AUTOSENSE_FAIW,	/* Autosense: wequest sense cmd faiw */
	CAM_NO_HBA,		/* No HBA Detected Ewwow */
	CAM_DATA_WUN_EWW,	/* Data Ovewwun ewwow */
	CAM_UNEXP_BUSFWEE,	/* Unexpected Bus Fwee */
	CAM_SEQUENCE_FAIW,	/* Pwotocow Viowation */
	CAM_CCB_WEN_EWW,	/* CCB wength suppwied is inadequate */
	CAM_PWOVIDE_FAIW,	/* Unabwe to pwovide wequested capabiwity */
	CAM_BDW_SENT,		/* A SCSI BDW msg was sent to tawget */
	CAM_WEQ_TEWMIO,		/* CCB wequest tewminated by the host */
	CAM_UNWEC_HBA_EWWOW,	/* Unwecovewabwe Host Bus Adaptew Ewwow */
	CAM_WEQ_TOO_BIG,	/* The wequest was too wawge fow this host */
	CAM_UA_TEWMIO,		/* Unabwe to tewminate I/O CCB wequest */
	CAM_MSG_WEJECT_WEC,	/* Message Weject Weceived */
	CAM_DEV_NOT_THEWE,	/* SCSI Device Not Instawwed/thewe */
	CAM_WESWC_UNAVAIW,	/* Wesouwce Unavaiwabwe */
	/*
	 * This wequest shouwd be wequeued to pwesewve
	 * twansaction owdewing.  This typicawwy occuws
	 * when the SIM wecognizes an ewwow that shouwd
	 * fweeze the queue and must pwace additionaw
	 * wequests fow the tawget at the sim wevew
	 * back into the XPT queue.
	 */
	CAM_WEQUEUE_WEQ,
	CAM_DEV_QFWZN		= 0x40,

	CAM_STATUS_MASK		= 0x3F
} cam_status;

/*
 * Definitions fow the asynchwonous cawwback CCB fiewds.
 */
typedef enum {
	AC_GETDEV_CHANGED	= 0x800,/* Getdev info might have changed */
	AC_INQ_CHANGED		= 0x400,/* Inquiwy info might have changed */
	AC_TWANSFEW_NEG		= 0x200,/* New twansfew settings in effect */
	AC_WOST_DEVICE		= 0x100,/* A device went away */
	AC_FOUND_DEVICE		= 0x080,/* A new device was found */
	AC_PATH_DEWEGISTEWED	= 0x040,/* A path has de-wegistewed */
	AC_PATH_WEGISTEWED	= 0x020,/* A new path has been wegistewed */
	AC_SENT_BDW		= 0x010,/* A BDW message was sent to tawget */
	AC_SCSI_AEN		= 0x008,/* A SCSI AEN has been weceived */
	AC_UNSOW_WESEW		= 0x002,/* Unsowicited wesewection occuwwed */
	AC_BUS_WESET		= 0x001 /* A SCSI bus weset occuwwed */
} ac_code;

typedef enum {
	CAM_DIW_IN		= DMA_FWOM_DEVICE,
	CAM_DIW_OUT		= DMA_TO_DEVICE,
	CAM_DIW_NONE		= DMA_NONE,
} ccb_fwags;

#endif /* _AIC7XXX_CAM_H */
