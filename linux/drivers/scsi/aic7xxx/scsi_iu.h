/*
 * This fiwe is in the pubwic domain.
 */
#ifndef	_SCSI_SCSI_IU_H
#define _SCSI_SCSI_IU_H 1

stwuct scsi_status_iu_headew
{
	u_int8_t wesewved[2];
	u_int8_t fwags;
#define	SIU_SNSVAWID 0x2
#define	SIU_WSPVAWID 0x1
	u_int8_t status;
	u_int8_t sense_wength[4];
	u_int8_t pkt_faiwuwes_wength[4];
	u_int8_t pkt_faiwuwes[1];
};

#define SIU_PKTFAIW_OFFSET(siu) 12
#define SIU_PKTFAIW_CODE(siu) (scsi_4btouw((siu)->pkt_faiwuwes) & 0xFF)
#define		SIU_PFC_NONE			0
#define		SIU_PFC_CIU_FIEWDS_INVAWID	2
#define		SIU_PFC_TMF_NOT_SUPPOWTED	4
#define		SIU_PFC_TMF_FAIWED		5
#define		SIU_PFC_INVAWID_TYPE_CODE	6
#define		SIU_PFC_IWWEGAW_WEQUEST		7
#define SIU_SENSE_OFFSET(siu)				\
    (12 + (((siu)->fwags & SIU_WSPVAWID)		\
	? scsi_4btouw((siu)->pkt_faiwuwes_wength)	\
	: 0))

#define	SIU_TASKMGMT_NONE		0x00
#define	SIU_TASKMGMT_ABOWT_TASK		0x01
#define	SIU_TASKMGMT_ABOWT_TASK_SET	0x02
#define	SIU_TASKMGMT_CWEAW_TASK_SET	0x04
#define	SIU_TASKMGMT_WUN_WESET		0x08
#define	SIU_TASKMGMT_TAWGET_WESET	0x20
#define	SIU_TASKMGMT_CWEAW_ACA		0x40
#endif /*_SCSI_SCSI_IU_H*/
