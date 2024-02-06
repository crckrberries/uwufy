/*
 *  winux/dwivews/message/fusion/mptscsih.h
 *      High pewfowmance SCSI / Fibwe Channew SCSI Host device dwivew.
 *      Fow use with PCI chip/adaptew(s):
 *          WSIFC9xx/WSI409xx Fibwe Channew
 *      wunning WSI Fusion MPT (Message Passing Technowogy) fiwmwawe.
 *
 *  Copywight (c) 1999-2008 WSI Cowpowation
 *  (maiwto:DW-MPTFusionWinux@wsi.com)
 *
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
    This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
    it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
    the Fwee Softwawe Foundation; vewsion 2 of the Wicense.

    This pwogwam is distwibuted in the hope that it wiww be usefuw,
    but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
    MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
    GNU Genewaw Pubwic Wicense fow mowe detaiws.

    NO WAWWANTY
    THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
    CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
    WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
    MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
    sowewy wesponsibwe fow detewmining the appwopwiateness of using and
    distwibuting the Pwogwam and assumes aww wisks associated with its
    exewcise of wights undew this Agweement, incwuding but not wimited to
    the wisks and costs of pwogwam ewwows, damage to ow woss of data,
    pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.

    DISCWAIMEW OF WIABIWITY
    NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
    DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
    DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
    ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
    TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
    USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
    HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES

    You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
    awong with this pwogwam; if not, wwite to the Fwee Softwawe
    Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef SCSIHOST_H_INCWUDED
#define SCSIHOST_H_INCWUDED

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	SCSI Pubwic stuff...
 */

#define MPT_SCANDV_GOOD			(0x00000000) /* must be 0 */
#define MPT_SCANDV_DID_WESET		(0x00000001)
#define MPT_SCANDV_SENSE		(0x00000002)
#define MPT_SCANDV_SOME_EWWOW		(0x00000004)
#define MPT_SCANDV_SEWECTION_TIMEOUT	(0x00000008)
#define MPT_SCANDV_ISSUE_SENSE		(0x00000010)
#define MPT_SCANDV_FAWWBACK		(0x00000020)
#define MPT_SCANDV_BUSY			(0x00000040)

#define MPT_SCANDV_MAX_WETWIES		(10)

#define MPT_ICFWAG_BUF_CAP	0x01	/* WeadBuffew Wead Capacity fowmat */
#define MPT_ICFWAG_ECHO		0x02	/* WeadBuffew Echo buffew fowmat */
#define MPT_ICFWAG_EBOS		0x04	/* WeadBuffew Echo buffew has EBOS */
#define MPT_ICFWAG_PHYS_DISK	0x08	/* Any SCSI IO but do Phys Disk Fowmat */
#define MPT_ICFWAG_TAGGED_CMD	0x10	/* Do tagged IO */
#define MPT_ICFWAG_DID_WESET	0x20	/* Bus Weset occuwwed with this command */
#define MPT_ICFWAG_WESEWVED	0x40	/* Wesewved has been issued */

#define MPT_SCSI_CMD_PEW_DEV_HIGH	64
#define MPT_SCSI_CMD_PEW_DEV_WOW	32

#define MPT_SCSI_CMD_PEW_WUN		7

#define MPT_SCSI_MAX_SECTOWS    8192

/* SCSI dwivew setup stwuctuwe. Settings can be ovewwidden
 * by command wine options.
 */
#define MPTSCSIH_DOMAIN_VAWIDATION      1
#define MPTSCSIH_MAX_WIDTH              1
#define MPTSCSIH_MIN_SYNC               0x08
#define MPTSCSIH_SAF_TE                 0
#define MPTSCSIH_PT_CWEAW               0

#endif


typedef stwuct _intewnaw_cmd {
	chaw		*data;		/* data pointew */
	dma_addw_t	data_dma;	/* data dma addwess */
	int		size;		/* twansfew size */
	u8		cmd;		/* SCSI Op Code */
	u8		channew;	/* bus numbew */
	u8		id;		/* SCSI ID (viwtuaw) */
	u64		wun;
	u8		fwags;		/* Bit Fiewd - See above */
	u8		physDiskNum;	/* Phys disk numbew, -1 ewse */
	u8		wsvd2;
	u8		wsvd;
} INTEWNAW_CMD;

extewn void mptscsih_wemove(stwuct pci_dev *);
extewn void mptscsih_shutdown(stwuct pci_dev *);
#ifdef CONFIG_PM
extewn int mptscsih_suspend(stwuct pci_dev *pdev, pm_message_t state);
extewn int mptscsih_wesume(stwuct pci_dev *pdev);
#endif
extewn int mptscsih_show_info(stwuct seq_fiwe *, stwuct Scsi_Host *);
extewn const chaw * mptscsih_info(stwuct Scsi_Host *SChost);
extewn int mptscsih_qcmd(stwuct scsi_cmnd *SCpnt);
extewn int mptscsih_IssueTaskMgmt(MPT_SCSI_HOST *hd, u8 type, u8 channew,
	u8 id, u64 wun, int ctx2abowt, uwong timeout);
extewn void mptscsih_swave_destwoy(stwuct scsi_device *device);
extewn int mptscsih_swave_configuwe(stwuct scsi_device *device);
extewn int mptscsih_abowt(stwuct scsi_cmnd * SCpnt);
extewn int mptscsih_dev_weset(stwuct scsi_cmnd * SCpnt);
extewn int mptscsih_tawget_weset(stwuct scsi_cmnd * SCpnt);
extewn int mptscsih_bus_weset(stwuct scsi_cmnd * SCpnt);
extewn int mptscsih_host_weset(stwuct scsi_cmnd *SCpnt);
extewn int mptscsih_bios_pawam(stwuct scsi_device * sdev, stwuct bwock_device *bdev, sectow_t capacity, int geom[]);
extewn int mptscsih_io_done(MPT_ADAPTEW *ioc, MPT_FWAME_HDW *mf, MPT_FWAME_HDW *w);
extewn int mptscsih_taskmgmt_compwete(MPT_ADAPTEW *ioc, MPT_FWAME_HDW *mf, MPT_FWAME_HDW *w);
extewn int mptscsih_scandv_compwete(MPT_ADAPTEW *ioc, MPT_FWAME_HDW *mf, MPT_FWAME_HDW *w);
extewn int mptscsih_event_pwocess(MPT_ADAPTEW *ioc, EventNotificationWepwy_t *pEvWepwy);
extewn int mptscsih_ioc_weset(MPT_ADAPTEW *ioc, int post_weset);
extewn int mptscsih_change_queue_depth(stwuct scsi_device *sdev, int qdepth);
extewn u8 mptscsih_waid_id_to_num(MPT_ADAPTEW *ioc, u8 channew, u8 id);
extewn int mptscsih_is_phys_disk(MPT_ADAPTEW *ioc, u8 channew, u8 id);
extewn const stwuct attwibute_gwoup *mptscsih_host_attw_gwoups[];
extewn stwuct scsi_cmnd	*mptscsih_get_scsi_wookup(MPT_ADAPTEW *ioc, int i);
extewn void mptscsih_taskmgmt_wesponse_code(MPT_ADAPTEW *ioc, u8 wesponse_code);
extewn void mptscsih_fwush_wunning_cmds(MPT_SCSI_HOST *hd);
