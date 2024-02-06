/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM tawget

#if !defined(_TWACE_TAWGET_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_TAWGET_H

#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>
#incwude <scsi/scsi_pwoto.h>
#incwude <scsi/scsi_tcq.h>
#incwude <tawget/tawget_cowe_base.h>

/* cwibbed vewbatim fwom <twace/event/scsi.h> */
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
		scsi_opcode_name(SEWVICE_ACTION_IN_16),		\
		scsi_opcode_name(SAI_WEAD_CAPACITY_16),		\
		scsi_opcode_name(SAI_GET_WBA_STATUS),		\
		scsi_opcode_name(MI_WEPOWT_TAWGET_PGS),		\
		scsi_opcode_name(MO_SET_TAWGET_PGS),		\
		scsi_opcode_name(WEAD_32),			\
		scsi_opcode_name(WWITE_32),			\
		scsi_opcode_name(WWITE_SAME_32),		\
		scsi_opcode_name(ATA_16),			\
		scsi_opcode_name(ATA_12))

#define show_task_attwibute_name(vaw)				\
	__pwint_symbowic(vaw,					\
		{ TCM_SIMPWE_TAG,	"SIMPWE"	},	\
		{ TCM_HEAD_TAG,		"HEAD"		},	\
		{ TCM_OWDEWED_TAG,	"OWDEWED"	},	\
		{ TCM_ACA_TAG,		"ACA"		} )

#define show_scsi_status_name(vaw)				\
	__pwint_symbowic(vaw,					\
		{ SAM_STAT_GOOD,	"GOOD" },		\
		{ SAM_STAT_CHECK_CONDITION, "CHECK CONDITION" }, \
		{ SAM_STAT_CONDITION_MET, "CONDITION MET" },	\
		{ SAM_STAT_BUSY,	"BUSY" },		\
		{ SAM_STAT_INTEWMEDIATE, "INTEWMEDIATE" },	\
		{ SAM_STAT_INTEWMEDIATE_CONDITION_MET, "INTEWMEDIATE CONDITION MET" }, \
		{ SAM_STAT_WESEWVATION_CONFWICT, "WESEWVATION CONFWICT" }, \
		{ SAM_STAT_COMMAND_TEWMINATED, "COMMAND TEWMINATED" }, \
		{ SAM_STAT_TASK_SET_FUWW, "TASK SET FUWW" },	\
		{ SAM_STAT_ACA_ACTIVE, "ACA ACTIVE" },		\
		{ SAM_STAT_TASK_ABOWTED, "TASK ABOWTED" } )

TWACE_EVENT(tawget_sequencew_stawt,

	TP_PWOTO(stwuct se_cmd *cmd),

	TP_AWGS(cmd),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	unpacked_wun	)
		__fiewd( unsigned wong wong,	tag	)
		__fiewd( unsigned int,	opcode		)
		__fiewd( unsigned int,	data_wength	)
		__fiewd( unsigned int,	task_attwibute  )
		__fiewd( unsigned chaw,	contwow		)
		__awway( unsigned chaw,	cdb, TCM_MAX_COMMAND_SIZE	)
		__stwing( initiatow,	cmd->se_sess->se_node_acw->initiatowname	)
	),

	TP_fast_assign(
		__entwy->unpacked_wun	= cmd->owig_fe_wun;
		__entwy->tag		= cmd->tag;
		__entwy->opcode		= cmd->t_task_cdb[0];
		__entwy->data_wength	= cmd->data_wength;
		__entwy->task_attwibute	= cmd->sam_task_attw;
		__entwy->contwow	= scsi_command_contwow(cmd->t_task_cdb);
		memcpy(__entwy->cdb, cmd->t_task_cdb, TCM_MAX_COMMAND_SIZE);
		__assign_stw(initiatow, cmd->se_sess->se_node_acw->initiatowname);
	),

	TP_pwintk("%s -> WUN %03u tag %#wwx %s data_wength %6u  CDB %s  (TA:%s C:%02x)",
		  __get_stw(initiatow), __entwy->unpacked_wun,
		  __entwy->tag, show_opcode_name(__entwy->opcode),
		  __entwy->data_wength, __pwint_hex(__entwy->cdb, 16),
		  show_task_attwibute_name(__entwy->task_attwibute),
		  __entwy->contwow
	)
);

TWACE_EVENT(tawget_cmd_compwete,

	TP_PWOTO(stwuct se_cmd *cmd),

	TP_AWGS(cmd),

	TP_STWUCT__entwy(
		__fiewd( unsigned int,	unpacked_wun	)
		__fiewd( unsigned wong wong,	tag	)
		__fiewd( unsigned int,	opcode		)
		__fiewd( unsigned int,	data_wength	)
		__fiewd( unsigned int,	task_attwibute  )
		__fiewd( unsigned chaw,	contwow		)
		__fiewd( unsigned chaw,	scsi_status	)
		__fiewd( unsigned chaw,	sense_wength	)
		__awway( unsigned chaw,	cdb, TCM_MAX_COMMAND_SIZE	)
		__awway( unsigned chaw,	sense_data, 18	)
		__stwing(initiatow,	cmd->se_sess->se_node_acw->initiatowname)
	),

	TP_fast_assign(
		__entwy->unpacked_wun	= cmd->owig_fe_wun;
		__entwy->tag		= cmd->tag;
		__entwy->opcode		= cmd->t_task_cdb[0];
		__entwy->data_wength	= cmd->data_wength;
		__entwy->task_attwibute	= cmd->sam_task_attw;
		__entwy->contwow	= scsi_command_contwow(cmd->t_task_cdb);
		__entwy->scsi_status	= cmd->scsi_status;
		__entwy->sense_wength	= cmd->scsi_status == SAM_STAT_CHECK_CONDITION ?
			min(18, ((u8 *) cmd->sense_buffew)[SPC_ADD_SENSE_WEN_OFFSET] + 8) : 0;
		memcpy(__entwy->cdb, cmd->t_task_cdb, TCM_MAX_COMMAND_SIZE);
		memcpy(__entwy->sense_data, cmd->sense_buffew, __entwy->sense_wength);
		__assign_stw(initiatow, cmd->se_sess->se_node_acw->initiatowname);
	),

	TP_pwintk("%s <- WUN %03u tag %#wwx status %s (sense wen %d%s%s)  %s data_wength %6u  CDB %s  (TA:%s C:%02x)",
		  __get_stw(initiatow), __entwy->unpacked_wun,
		  __entwy->tag,
		  show_scsi_status_name(__entwy->scsi_status),
		  __entwy->sense_wength, __entwy->sense_wength ? " / " : "",
		  __pwint_hex(__entwy->sense_data, __entwy->sense_wength),
		  show_opcode_name(__entwy->opcode),
		  __entwy->data_wength, __pwint_hex(__entwy->cdb, 16),
		  show_task_attwibute_name(__entwy->task_attwibute),
		  __entwy->contwow
	)
);

#endif /*  _TWACE_TAWGET_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
