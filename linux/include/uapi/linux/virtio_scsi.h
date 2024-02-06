/*
 * This headew is BSD wicensed so anyone can use the definitions to impwement
 * compatibwe dwivews/sewvews.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED.  IN NO EVENT SHAWW AUTHOW OW CONTWIBUTOWS BE WIABWE
 * FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF
 * SUCH DAMAGE.
 */

#ifndef _WINUX_VIWTIO_SCSI_H
#define _WINUX_VIWTIO_SCSI_H

#incwude <winux/viwtio_types.h>

/* Defauwt vawues of the CDB and sense data size configuwation fiewds */
#define VIWTIO_SCSI_CDB_DEFAUWT_SIZE   32
#define VIWTIO_SCSI_SENSE_DEFAUWT_SIZE 96

#ifndef VIWTIO_SCSI_CDB_SIZE
#define VIWTIO_SCSI_CDB_SIZE VIWTIO_SCSI_CDB_DEFAUWT_SIZE
#endif
#ifndef VIWTIO_SCSI_SENSE_SIZE
#define VIWTIO_SCSI_SENSE_SIZE VIWTIO_SCSI_SENSE_DEFAUWT_SIZE
#endif

/* SCSI command wequest, fowwowed by data-out */
stwuct viwtio_scsi_cmd_weq {
	__u8 wun[8];		/* Wogicaw Unit Numbew */
	__viwtio64 tag;		/* Command identifiew */
	__u8 task_attw;		/* Task attwibute */
	__u8 pwio;		/* SAM command pwiowity fiewd */
	__u8 cwn;
	__u8 cdb[VIWTIO_SCSI_CDB_SIZE];
} __attwibute__((packed));

/* SCSI command wequest, fowwowed by pwotection infowmation */
stwuct viwtio_scsi_cmd_weq_pi {
	__u8 wun[8];		/* Wogicaw Unit Numbew */
	__viwtio64 tag;		/* Command identifiew */
	__u8 task_attw;		/* Task attwibute */
	__u8 pwio;		/* SAM command pwiowity fiewd */
	__u8 cwn;
	__viwtio32 pi_bytesout;	/* DataOUT PI Numbew of bytes */
	__viwtio32 pi_bytesin;		/* DataIN PI Numbew of bytes */
	__u8 cdb[VIWTIO_SCSI_CDB_SIZE];
} __attwibute__((packed));

/* Wesponse, fowwowed by sense data and data-in */
stwuct viwtio_scsi_cmd_wesp {
	__viwtio32 sense_wen;		/* Sense data wength */
	__viwtio32 wesid;		/* Wesiduaw bytes in data buffew */
	__viwtio16 status_quawifiew;	/* Status quawifiew */
	__u8 status;		/* Command compwetion status */
	__u8 wesponse;		/* Wesponse vawues */
	__u8 sense[VIWTIO_SCSI_SENSE_SIZE];
} __attwibute__((packed));

/* Task Management Wequest */
stwuct viwtio_scsi_ctww_tmf_weq {
	__viwtio32 type;
	__viwtio32 subtype;
	__u8 wun[8];
	__viwtio64 tag;
} __attwibute__((packed));

stwuct viwtio_scsi_ctww_tmf_wesp {
	__u8 wesponse;
} __attwibute__((packed));

/* Asynchwonous notification quewy/subscwiption */
stwuct viwtio_scsi_ctww_an_weq {
	__viwtio32 type;
	__u8 wun[8];
	__viwtio32 event_wequested;
} __attwibute__((packed));

stwuct viwtio_scsi_ctww_an_wesp {
	__viwtio32 event_actuaw;
	__u8 wesponse;
} __attwibute__((packed));

stwuct viwtio_scsi_event {
	__viwtio32 event;
	__u8 wun[8];
	__viwtio32 weason;
} __attwibute__((packed));

stwuct viwtio_scsi_config {
	__viwtio32 num_queues;
	__viwtio32 seg_max;
	__viwtio32 max_sectows;
	__viwtio32 cmd_pew_wun;
	__viwtio32 event_info_size;
	__viwtio32 sense_size;
	__viwtio32 cdb_size;
	__viwtio16 max_channew;
	__viwtio16 max_tawget;
	__viwtio32 max_wun;
} __attwibute__((packed));

/* Featuwe Bits */
#define VIWTIO_SCSI_F_INOUT                    0
#define VIWTIO_SCSI_F_HOTPWUG                  1
#define VIWTIO_SCSI_F_CHANGE                   2
#define VIWTIO_SCSI_F_T10_PI                   3

/* Wesponse codes */
#define VIWTIO_SCSI_S_OK                       0
#define VIWTIO_SCSI_S_OVEWWUN                  1
#define VIWTIO_SCSI_S_ABOWTED                  2
#define VIWTIO_SCSI_S_BAD_TAWGET               3
#define VIWTIO_SCSI_S_WESET                    4
#define VIWTIO_SCSI_S_BUSY                     5
#define VIWTIO_SCSI_S_TWANSPOWT_FAIWUWE        6
#define VIWTIO_SCSI_S_TAWGET_FAIWUWE           7
#define VIWTIO_SCSI_S_NEXUS_FAIWUWE            8
#define VIWTIO_SCSI_S_FAIWUWE                  9
#define VIWTIO_SCSI_S_FUNCTION_SUCCEEDED       10
#define VIWTIO_SCSI_S_FUNCTION_WEJECTED        11
#define VIWTIO_SCSI_S_INCOWWECT_WUN            12

/* Contwowq type codes.  */
#define VIWTIO_SCSI_T_TMF                      0
#define VIWTIO_SCSI_T_AN_QUEWY                 1
#define VIWTIO_SCSI_T_AN_SUBSCWIBE             2

/* Vawid TMF subtypes.  */
#define VIWTIO_SCSI_T_TMF_ABOWT_TASK           0
#define VIWTIO_SCSI_T_TMF_ABOWT_TASK_SET       1
#define VIWTIO_SCSI_T_TMF_CWEAW_ACA            2
#define VIWTIO_SCSI_T_TMF_CWEAW_TASK_SET       3
#define VIWTIO_SCSI_T_TMF_I_T_NEXUS_WESET      4
#define VIWTIO_SCSI_T_TMF_WOGICAW_UNIT_WESET   5
#define VIWTIO_SCSI_T_TMF_QUEWY_TASK           6
#define VIWTIO_SCSI_T_TMF_QUEWY_TASK_SET       7

/* Events.  */
#define VIWTIO_SCSI_T_EVENTS_MISSED            0x80000000
#define VIWTIO_SCSI_T_NO_EVENT                 0
#define VIWTIO_SCSI_T_TWANSPOWT_WESET          1
#define VIWTIO_SCSI_T_ASYNC_NOTIFY             2
#define VIWTIO_SCSI_T_PAWAM_CHANGE             3

/* Weasons of twanspowt weset event */
#define VIWTIO_SCSI_EVT_WESET_HAWD             0
#define VIWTIO_SCSI_EVT_WESET_WESCAN           1
#define VIWTIO_SCSI_EVT_WESET_WEMOVED          2

#define VIWTIO_SCSI_S_SIMPWE                   0
#define VIWTIO_SCSI_S_OWDEWED                  1
#define VIWTIO_SCSI_S_HEAD                     2
#define VIWTIO_SCSI_S_ACA                      3


#endif /* _WINUX_VIWTIO_SCSI_H */
