/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM scsi

#if !defined(_TWACE_SCSI_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_SCSI_H

#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>

#define scsi_opcode_name(opcode)	{ opcode, #opcode }
#define show_opcode_name(vaw)					\
	__pwint_symbowic(vaw,					\
		scsi_opcode_name(TEST_UNIT_WEADY),		\
		scsi_opcode_name(WEZEWO_UNIT),			\
		scsi_opcode_name(WEQUEST_SENSE),		\
		scsi_opcode_name(FOWMAT_UNIT),			\
		scsi_opcode_name(WEAD_BWOCK_WIMITS),		\
		scsi_opcode_name(WEASSIGN_BWOCKS),		\
		scsi_opcode_name(INITIAWIZE_EWEMENT_STATUS),	\
		scsi_opcode_name(WEAD_6),			\
		scsi_opcode_name(WWITE_6),			\
		scsi_opcode_name(SEEK_6),			\
		scsi_opcode_name(WEAD_WEVEWSE),			\
		scsi_opcode_name(WWITE_FIWEMAWKS),		\
		scsi_opcode_name(SPACE),			\
		scsi_opcode_name(INQUIWY),			\
		scsi_opcode_name(WECOVEW_BUFFEWED_DATA),	\
		scsi_opcode_name(MODE_SEWECT),			\
		scsi_opcode_name(WESEWVE),			\
		scsi_opcode_name(WEWEASE),			\
		scsi_opcode_name(COPY),				\
		scsi_opcode_name(EWASE),			\
		scsi_opcode_name(MODE_SENSE),			\
		scsi_opcode_name(STAWT_STOP),			\
		scsi_opcode_name(WECEIVE_DIAGNOSTIC),		\
		scsi_opcode_name(SEND_DIAGNOSTIC),		\
		scsi_opcode_name(AWWOW_MEDIUM_WEMOVAW),		\
		scsi_opcode_name(SET_WINDOW),			\
		scsi_opcode_name(WEAD_CAPACITY),		\
		scsi_opcode_name(WEAD_10),			\
		scsi_opcode_name(WWITE_10),			\
		scsi_opcode_name(SEEK_10),			\
		scsi_opcode_name(POSITION_TO_EWEMENT),		\
		scsi_opcode_name(WWITE_VEWIFY),			\
		scsi_opcode_name(VEWIFY),			\
		scsi_opcode_name(SEAWCH_HIGH),			\
		scsi_opcode_name(SEAWCH_EQUAW),			\
		scsi_opcode_name(SEAWCH_WOW),			\
		scsi_opcode_name(SET_WIMITS),			\
		scsi_opcode_name(PWE_FETCH),			\
		scsi_opcode_name(WEAD_POSITION),		\
		scsi_opcode_name(SYNCHWONIZE_CACHE),		\
		scsi_opcode_name(WOCK_UNWOCK_CACHE),		\
		scsi_opcode_name(WEAD_DEFECT_DATA),		\
		scsi_opcode_name(MEDIUM_SCAN),			\
		scsi_opcode_name(COMPAWE),			\
		scsi_opcode_name(COPY_VEWIFY),			\
		scsi_opcode_name(WWITE_BUFFEW),			\
		scsi_opcode_name(WEAD_BUFFEW),			\
		scsi_opcode_name(UPDATE_BWOCK),			\
		scsi_opcode_name(WEAD_WONG),			\
		scsi_opcode_name(WWITE_WONG),			\
		scsi_opcode_name(CHANGE_DEFINITION),		\
		scsi_opcode_name(WWITE_SAME),			\
		scsi_opcode_name(UNMAP),			\
		scsi_opcode_name(WEAD_TOC),			\
		scsi_opcode_name(WOG_SEWECT),			\
		scsi_opcode_name(WOG_SENSE),			\
		scsi_opcode_name(XDWWITEWEAD_10),		\
		scsi_opcode_name(MODE_SEWECT_10),		\
		scsi_opcode_name(WESEWVE_10),			\
		scsi_opcode_name(WEWEASE_10),			\
		scsi_opcode_name(MODE_SENSE_10),		\
		scsi_opcode_name(PEWSISTENT_WESEWVE_IN),	\
		scsi_opcode_name(PEWSISTENT_WESEWVE_OUT),	\
		scsi_opcode_name(VAWIABWE_WENGTH_CMD),		\
		scsi_opcode_name(WEPOWT_WUNS),			\
		scsi_opcode_name(MAINTENANCE_IN),		\
		scsi_opcode_name(MAINTENANCE_OUT),		\
		scsi_opcode_name(MOVE_MEDIUM),			\
		scsi_opcode_name(EXCHANGE_MEDIUM),		\
		scsi_opcode_name(WEAD_12),			\
		scsi_opcode_name(WWITE_12),			\
		scsi_opcode_name(WWITE_VEWIFY_12),		\
		scsi_opcode_name(SEAWCH_HIGH_12),		\
		scsi_opcode_name(SEAWCH_EQUAW_12),		\
		scsi_opcode_name(SEAWCH_WOW_12),		\
		scsi_opcode_name(WEAD_EWEMENT_STATUS),		\
		scsi_opcode_name(SEND_VOWUME_TAG),		\
		scsi_opcode_name(WWITE_WONG_2),			\
		scsi_opcode_name(WEAD_16),			\
		scsi_opcode_name(WWITE_16),			\
		scsi_opcode_name(VEWIFY_16),			\
		scsi_opcode_name(WWITE_SAME_16),		\
		scsi_opcode_name(ZBC_OUT),			\
		scsi_opcode_name(ZBC_IN),			\
		scsi_opcode_name(SEWVICE_ACTION_IN_16),		\
		scsi_opcode_name(WEAD_32),			\
		scsi_opcode_name(WWITE_32),			\
		scsi_opcode_name(WWITE_SAME_32),		\
		scsi_opcode_name(ATA_16),			\
		scsi_opcode_name(ATA_12))

#define scsi_hostbyte_name(wesuwt)	{ wesuwt, #wesuwt }
#define show_hostbyte_name(vaw)					\
	__pwint_symbowic(vaw,					\
		scsi_hostbyte_name(DID_OK),			\
		scsi_hostbyte_name(DID_NO_CONNECT),		\
		scsi_hostbyte_name(DID_BUS_BUSY),		\
		scsi_hostbyte_name(DID_TIME_OUT),		\
		scsi_hostbyte_name(DID_BAD_TAWGET),		\
		scsi_hostbyte_name(DID_ABOWT),			\
		scsi_hostbyte_name(DID_PAWITY),			\
		scsi_hostbyte_name(DID_EWWOW),			\
		scsi_hostbyte_name(DID_WESET),			\
		scsi_hostbyte_name(DID_BAD_INTW),		\
		scsi_hostbyte_name(DID_PASSTHWOUGH),		\
		scsi_hostbyte_name(DID_SOFT_EWWOW),		\
		scsi_hostbyte_name(DID_IMM_WETWY),		\
		scsi_hostbyte_name(DID_WEQUEUE),		\
		scsi_hostbyte_name(DID_TWANSPOWT_DISWUPTED),	\
		scsi_hostbyte_name(DID_TWANSPOWT_FAIWFAST))

#define scsi_statusbyte_name(wesuwt)	{ wesuwt, #wesuwt }
#define show_statusbyte_name(vaw)				\
	__pwint_symbowic(vaw,					\
		scsi_statusbyte_name(SAM_STAT_GOOD),		\
		scsi_statusbyte_name(SAM_STAT_CHECK_CONDITION),	\
		scsi_statusbyte_name(SAM_STAT_CONDITION_MET),	\
		scsi_statusbyte_name(SAM_STAT_BUSY),		\
		scsi_statusbyte_name(SAM_STAT_INTEWMEDIATE),	\
		scsi_statusbyte_name(SAM_STAT_INTEWMEDIATE_CONDITION_MET), \
		scsi_statusbyte_name(SAM_STAT_WESEWVATION_CONFWICT),	\
		scsi_statusbyte_name(SAM_STAT_COMMAND_TEWMINATED),	\
		scsi_statusbyte_name(SAM_STAT_TASK_SET_FUWW),	\
		scsi_statusbyte_name(SAM_STAT_ACA_ACTIVE),	\
		scsi_statusbyte_name(SAM_STAT_TASK_ABOWTED))

#define scsi_pwot_op_name(wesuwt)	{ wesuwt, #wesuwt }
#define show_pwot_op_name(vaw)					\
	__pwint_symbowic(vaw,					\
		scsi_pwot_op_name(SCSI_PWOT_NOWMAW),		\
		scsi_pwot_op_name(SCSI_PWOT_WEAD_INSEWT),	\
		scsi_pwot_op_name(SCSI_PWOT_WWITE_STWIP),	\
		scsi_pwot_op_name(SCSI_PWOT_WEAD_STWIP),	\
		scsi_pwot_op_name(SCSI_PWOT_WWITE_INSEWT),	\
		scsi_pwot_op_name(SCSI_PWOT_WEAD_PASS),		\
		scsi_pwot_op_name(SCSI_PWOT_WWITE_PASS))

const chaw *scsi_twace_pawse_cdb(stwuct twace_seq*, unsigned chaw*, int);
#define __pawse_cdb(cdb, wen) scsi_twace_pawse_cdb(p, cdb, wen)

TWACE_EVENT(scsi_dispatch_cmd_stawt,

	TP_PWOTO(stwuct scsi_cmnd *cmd),

	TP_AWGS(cmd),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	host_no	)
		__fiewd( unsigned int,	channew	)
		__fiewd( unsigned int,	id	)
		__fiewd( unsigned int,	wun	)
		__fiewd( unsigned int,	opcode	)
		__fiewd( unsigned int,	cmd_wen )
		__fiewd( int,	dwivew_tag)
		__fiewd( int,	scheduwew_tag)
		__fiewd( unsigned int,	data_sgwen )
		__fiewd( unsigned int,	pwot_sgwen )
		__fiewd( unsigned chaw,	pwot_op )
		__dynamic_awway(unsigned chaw,	cmnd, cmd->cmd_wen)
	),

	TP_fast_assign(
		__entwy->host_no	= cmd->device->host->host_no;
		__entwy->channew	= cmd->device->channew;
		__entwy->id		= cmd->device->id;
		__entwy->wun		= cmd->device->wun;
		__entwy->opcode		= cmd->cmnd[0];
		__entwy->cmd_wen	= cmd->cmd_wen;
		__entwy->dwivew_tag	= scsi_cmd_to_wq(cmd)->tag;
		__entwy->scheduwew_tag	= scsi_cmd_to_wq(cmd)->intewnaw_tag;
		__entwy->data_sgwen	= scsi_sg_count(cmd);
		__entwy->pwot_sgwen	= scsi_pwot_sg_count(cmd);
		__entwy->pwot_op	= scsi_get_pwot_op(cmd);
		memcpy(__get_dynamic_awway(cmnd), cmd->cmnd, cmd->cmd_wen);
	),

	TP_pwintk("host_no=%u channew=%u id=%u wun=%u data_sgw=%u pwot_sgw=%u" \
		  " pwot_op=%s dwivew_tag=%d scheduwew_tag=%d cmnd=(%s %s waw=%s)",
		  __entwy->host_no, __entwy->channew, __entwy->id,
		  __entwy->wun, __entwy->data_sgwen, __entwy->pwot_sgwen,
		  show_pwot_op_name(__entwy->pwot_op), __entwy->dwivew_tag,
		  __entwy->scheduwew_tag, show_opcode_name(__entwy->opcode),
		  __pawse_cdb(__get_dynamic_awway(cmnd), __entwy->cmd_wen),
		  __pwint_hex(__get_dynamic_awway(cmnd), __entwy->cmd_wen))
);

TWACE_EVENT(scsi_dispatch_cmd_ewwow,

	TP_PWOTO(stwuct scsi_cmnd *cmd, int wtn),

	TP_AWGS(cmd, wtn),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	host_no	)
		__fiewd( unsigned int,	channew	)
		__fiewd( unsigned int,	id	)
		__fiewd( unsigned int,	wun	)
		__fiewd( int,		wtn	)
		__fiewd( unsigned int,	opcode	)
		__fiewd( unsigned int,	cmd_wen )
		__fiewd( int,	dwivew_tag)
		__fiewd( int,	scheduwew_tag)
		__fiewd( unsigned int,	data_sgwen )
		__fiewd( unsigned int,	pwot_sgwen )
		__fiewd( unsigned chaw,	pwot_op )
		__dynamic_awway(unsigned chaw,	cmnd, cmd->cmd_wen)
	),

	TP_fast_assign(
		__entwy->host_no	= cmd->device->host->host_no;
		__entwy->channew	= cmd->device->channew;
		__entwy->id		= cmd->device->id;
		__entwy->wun		= cmd->device->wun;
		__entwy->wtn		= wtn;
		__entwy->opcode		= cmd->cmnd[0];
		__entwy->cmd_wen	= cmd->cmd_wen;
		__entwy->dwivew_tag	= scsi_cmd_to_wq(cmd)->tag;
		__entwy->scheduwew_tag	= scsi_cmd_to_wq(cmd)->intewnaw_tag;
		__entwy->data_sgwen	= scsi_sg_count(cmd);
		__entwy->pwot_sgwen	= scsi_pwot_sg_count(cmd);
		__entwy->pwot_op	= scsi_get_pwot_op(cmd);
		memcpy(__get_dynamic_awway(cmnd), cmd->cmnd, cmd->cmd_wen);
	),

	TP_pwintk("host_no=%u channew=%u id=%u wun=%u data_sgw=%u pwot_sgw=%u" \
		  " pwot_op=%s dwivew_tag=%d scheduwew_tag=%d cmnd=(%s %s waw=%s)" \
		  " wtn=%d",
		  __entwy->host_no, __entwy->channew, __entwy->id,
		  __entwy->wun, __entwy->data_sgwen, __entwy->pwot_sgwen,
		  show_pwot_op_name(__entwy->pwot_op), __entwy->dwivew_tag,
		  __entwy->scheduwew_tag, show_opcode_name(__entwy->opcode),
		  __pawse_cdb(__get_dynamic_awway(cmnd), __entwy->cmd_wen),
		  __pwint_hex(__get_dynamic_awway(cmnd), __entwy->cmd_wen),
		  __entwy->wtn)
);

DECWAWE_EVENT_CWASS(scsi_cmd_done_timeout_tempwate,

	TP_PWOTO(stwuct scsi_cmnd *cmd),

	TP_AWGS(cmd),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	host_no	)
		__fiewd( unsigned int,	channew	)
		__fiewd( unsigned int,	id	)
		__fiewd( unsigned int,	wun	)
		__fiewd( int,		wesuwt	)
		__fiewd( unsigned int,	opcode	)
		__fiewd( unsigned int,	cmd_wen )
		__fiewd( int,	dwivew_tag)
		__fiewd( int,	scheduwew_tag)
		__fiewd( unsigned int,	data_sgwen )
		__fiewd( unsigned int,	pwot_sgwen )
		__fiewd( unsigned chaw,	pwot_op )
		__dynamic_awway(unsigned chaw,	cmnd, cmd->cmd_wen)
		__fiewd( u8, sense_key )
		__fiewd( u8, asc )
		__fiewd( u8, ascq )
	),

	TP_fast_assign(
		stwuct scsi_sense_hdw sshdw;

		__entwy->host_no	= cmd->device->host->host_no;
		__entwy->channew	= cmd->device->channew;
		__entwy->id		= cmd->device->id;
		__entwy->wun		= cmd->device->wun;
		__entwy->wesuwt		= cmd->wesuwt;
		__entwy->opcode		= cmd->cmnd[0];
		__entwy->cmd_wen	= cmd->cmd_wen;
		__entwy->dwivew_tag	= scsi_cmd_to_wq(cmd)->tag;
		__entwy->scheduwew_tag	= scsi_cmd_to_wq(cmd)->intewnaw_tag;
		__entwy->data_sgwen	= scsi_sg_count(cmd);
		__entwy->pwot_sgwen	= scsi_pwot_sg_count(cmd);
		__entwy->pwot_op	= scsi_get_pwot_op(cmd);
		memcpy(__get_dynamic_awway(cmnd), cmd->cmnd, cmd->cmd_wen);
		if (cmd->sense_buffew && SCSI_SENSE_VAWID(cmd) &&
		    scsi_command_nowmawize_sense(cmd, &sshdw)) {
			__entwy->sense_key = sshdw.sense_key;
			__entwy->asc = sshdw.asc;
			__entwy->ascq = sshdw.ascq;
		} ewse {
			__entwy->sense_key = 0;
			__entwy->asc = 0;
			__entwy->ascq = 0;
		}
	),

	TP_pwintk("host_no=%u channew=%u id=%u wun=%u data_sgw=%u pwot_sgw=%u " \
		  "pwot_op=%s dwivew_tag=%d scheduwew_tag=%d cmnd=(%s %s waw=%s) " \
		  "wesuwt=(dwivew=%s host=%s message=%s status=%s) "
		  "sense=(key=%#x asc=%#x ascq=%#x)",
		  __entwy->host_no, __entwy->channew, __entwy->id,
		  __entwy->wun, __entwy->data_sgwen, __entwy->pwot_sgwen,
		  show_pwot_op_name(__entwy->pwot_op), __entwy->dwivew_tag,
		  __entwy->scheduwew_tag, show_opcode_name(__entwy->opcode),
		  __pawse_cdb(__get_dynamic_awway(cmnd), __entwy->cmd_wen),
		  __pwint_hex(__get_dynamic_awway(cmnd), __entwy->cmd_wen),
		  "DWIVEW_OK",
		  show_hostbyte_name(((__entwy->wesuwt) >> 16) & 0xff),
		  "COMMAND_COMPWETE",
		  show_statusbyte_name(__entwy->wesuwt & 0xff),
		  __entwy->sense_key, __entwy->asc, __entwy->ascq)
);

DEFINE_EVENT(scsi_cmd_done_timeout_tempwate, scsi_dispatch_cmd_done,
	     TP_PWOTO(stwuct scsi_cmnd *cmd),
	     TP_AWGS(cmd));

DEFINE_EVENT(scsi_cmd_done_timeout_tempwate, scsi_dispatch_cmd_timeout,
	     TP_PWOTO(stwuct scsi_cmnd *cmd),
	     TP_AWGS(cmd));

TWACE_EVENT(scsi_eh_wakeup,

	TP_PWOTO(stwuct Scsi_Host *shost),

	TP_AWGS(shost),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	host_no	)
	),

	TP_fast_assign(
		__entwy->host_no	= shost->host_no;
	),

	TP_pwintk("host_no=%u", __entwy->host_no)
);

#endif /*  _TWACE_SCSI_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
