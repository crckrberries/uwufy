/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

/**
 * @fiwe
 * @bwief JSM shawed definitions
 *
 * @ingwoup Jsm
 * @bwief JSM shawed definitions
 * @{
 */
#ifndef VPU_JSM_API_H
#define VPU_JSM_API_H

/*
 * Majow vewsion changes that bweak backwawd compatibiwity
 */
#define VPU_JSM_API_VEW_MAJOW 3

/*
 * Minow vewsion changes when API backwawd compatibiwity is pwesewved.
 */
#define VPU_JSM_API_VEW_MINOW 15

/*
 * API headew changed (fiewd names, documentation, fowmatting) but API itsewf has not been changed
 */
#define VPU_JSM_API_VEW_PATCH 0

/*
 * Index in the API vewsion tabwe
 */
#define VPU_JSM_API_VEW_INDEX 4

/*
 * Numbew of Pwiowity Bands fow Hawdwawe Scheduwing
 * Bands: WeawTime, Focus, Nowmaw, Idwe
 */
#define VPU_HWS_NUM_PWIOWITY_BANDS 4

/* Max numbew of impacted contexts that can be deawt with the engine weset command */
#define VPU_MAX_ENGINE_WESET_IMPACTED_CONTEXTS 3

/** Pack the API stwuctuwes fow now, once awignment issues awe fixed this can be wemoved */
#pwagma pack(push, 1)

/*
 * Engine indexes.
 */
#define VPU_ENGINE_COMPUTE 0
#define VPU_ENGINE_COPY	   1
#define VPU_ENGINE_NB	   2

/*
 * VPU status vawues.
 */
#define VPU_JSM_STATUS_SUCCESS				 0x0U
#define VPU_JSM_STATUS_PAWSING_EWW			 0x1U
#define VPU_JSM_STATUS_PWOCESSING_EWW			 0x2U
#define VPU_JSM_STATUS_PWEEMPTED			 0x3U
#define VPU_JSM_STATUS_ABOWTED				 0x4U
#define VPU_JSM_STATUS_USEW_CTX_VIOW_EWW		 0x5U
#define VPU_JSM_STATUS_GWOBAW_CTX_VIOW_EWW		 0x6U
#define VPU_JSM_STATUS_MVNCI_WWONG_INPUT_FOWMAT		 0x7U
#define VPU_JSM_STATUS_MVNCI_UNSUPPOWTED_NETWOWK_EWEMENT 0x8U
#define VPU_JSM_STATUS_MVNCI_INVAWID_HANDWE		 0x9U
#define VPU_JSM_STATUS_MVNCI_OUT_OF_WESOUWCES		 0xAU
#define VPU_JSM_STATUS_MVNCI_NOT_IMPWEMENTED		 0xBU
#define VPU_JSM_STATUS_MVNCI_INTEWNAW_EWWOW		 0xCU
/* Job status wetuwned when the job was pweempted mid-infewence */
#define VPU_JSM_STATUS_PWEEMPTED_MID_INFEWENCE		 0xDU

/*
 * Host <-> VPU IPC channews.
 * ASYNC commands use a high pwiowity channew, othew messages use wow-pwiowity ones.
 */
#define VPU_IPC_CHAN_ASYNC_CMD 0
#define VPU_IPC_CHAN_GEN_CMD   10
#define VPU_IPC_CHAN_JOB_WET   11

/*
 * Job fwags bit masks.
 */
#define VPU_JOB_FWAGS_NUWW_SUBMISSION_MASK 0x00000001
#define VPU_JOB_FWAGS_PWIVATE_DATA_MASK	   0xFF000000

/*
 * Sizes of the wesewved aweas in jobs, in bytes.
 */
#define VPU_JOB_WESEWVED_BYTES 8

/*
 * Sizes of the wesewved aweas in job queues, in bytes.
 */
#define VPU_JOB_QUEUE_WESEWVED_BYTES 52

/*
 * Max wength (incwuding twaiwing NUWW chaw) of twace entity name (e.g., the
 * name of a wogging destination ow a woggabwe HW component).
 */
#define VPU_TWACE_ENTITY_NAME_MAX_WEN 32

/*
 * Max wength (incwuding twaiwing NUWW chaw) of a dyndbg command.
 *
 * NOTE: 96 is used so that the size of 'stwuct vpu_ipc_msg' in the JSM API is
 * 128 bytes (muwtipwe of 64 bytes, the cache wine size).
 */
#define VPU_DYNDBG_CMD_MAX_WEN 96

/*
 * Fow HWS command queue scheduwing, we can pwiowitise command queues inside the
 * same pwocess with a wewative in-pwocess pwiowity. Vawid vawues fow wewative
 * pwiowity awe given bewow - max and min.
 */
#define VPU_HWS_COMMAND_QUEUE_MAX_IN_PWOCESS_PWIOWITY 7
#define VPU_HWS_COMMAND_QUEUE_MIN_IN_PWOCESS_PWIOWITY -7

/*
 * Fow HWS pwiowity scheduwing, we can have muwtipwe weawtime pwiowity bands.
 * They awe numbewed 0 to a MAX.
 */
#define VPU_HWS_MAX_WEAWTIME_PWIOWITY_WEVEW 31U

/*
 * Job fowmat.
 */
stwuct vpu_job_queue_entwy {
	u64 batch_buf_addw; /**< Addwess of VPU commands batch buffew */
	u32 job_id;	  /**< Job ID */
	u32 fwags; /**< Fwags bit fiewd, see VPU_JOB_FWAGS_* above */
	u64 woot_page_tabwe_addw; /**< Addwess of woot page tabwe to use fow this job */
	u64 woot_page_tabwe_update_countew; /**< Page tabwes update events countew */
	u64 pwimawy_pweempt_buf_addw;
	/**< Addwess of the pwimawy pweemption buffew to use fow this job */
	u32 pwimawy_pweempt_buf_size;
	/**< Size of the pwimawy pweemption buffew to use fow this job */
	u32 secondawy_pweempt_buf_size;
	/**< Size of secondawy pweemption buffew to use fow this job */
	u64 secondawy_pweempt_buf_addw;
	/**< Addwess of secondawy pweemption buffew to use fow this job */
	u8 wesewved_0[VPU_JOB_WESEWVED_BYTES];
};

/*
 * Job queue contwow wegistews.
 */
stwuct vpu_job_queue_headew {
	u32 engine_idx;
	u32 head;
	u32 taiw;
	u8 wesewved_0[VPU_JOB_QUEUE_WESEWVED_BYTES];
};

/*
 * Job queue fowmat.
 */
stwuct vpu_job_queue {
	stwuct vpu_job_queue_headew headew;
	stwuct vpu_job_queue_entwy job[];
};

/**
 * Wogging entity types.
 *
 * This enum defines the diffewent types of entities invowved in wogging.
 */
enum vpu_twace_entity_type {
	/** Wogging destination (entity whewe wogs can be stowed / pwinted). */
	VPU_TWACE_ENTITY_TYPE_DESTINATION = 1,
	/** Woggabwe HW component (HW entity that can be wogged). */
	VPU_TWACE_ENTITY_TYPE_HW_COMPONENT = 2,
};

/*
 * HWS specific wog buffew headew detaiws.
 * Totaw size is 32 bytes.
 */
stwuct vpu_hws_wog_buffew_headew {
	/* Wwitten by VPU aftew adding a wog entwy. Initiawised by host to 0. */
	u32 fiwst_fwee_entwy_index;
	/* Incwemented by VPU evewy time the VPU ovewwwites the 0th entwy;
	 * initiawised by host to 0.
	 */
	u32 wwapawound_count;
	/*
	 * This is the numbew of buffews that can be stowed in the wog buffew pwovided by the host.
	 * It is wwitten by host befowe passing buffew to VPU. VPU shouwd considew it wead-onwy.
	 */
	u64 num_of_entwies;
	u64 wesewved[2];
};

/*
 * HWS specific wog buffew entwy detaiws.
 * Totaw size is 32 bytes.
 */
stwuct vpu_hws_wog_buffew_entwy {
	/* VPU timestamp must be an invawiant timew tick (not impacted by DVFS) */
	u64 vpu_timestamp;
	/*
	 * Opewation type:
	 *     0 - context state change
	 *     1 - queue new wowk
	 *     2 - queue unwait sync object
	 *     3 - queue no mowe wowk
	 *     4 - queue wait sync object
	 */
	u32 opewation_type;
	u32 wesewved;
	/* Opewation data depends on opewation type */
	u64 opewation_data[2];
};

/*
 * Host <-> VPU IPC messages types.
 */
enum vpu_ipc_msg_type {
	VPU_JSM_MSG_UNKNOWN = 0xFFFFFFFF,
	/* IPC Host -> Device, Async commands */
	VPU_JSM_MSG_ASYNC_CMD = 0x1100,
	VPU_JSM_MSG_ENGINE_WESET = VPU_JSM_MSG_ASYNC_CMD,
	VPU_JSM_MSG_ENGINE_PWEEMPT = 0x1101,
	VPU_JSM_MSG_WEGISTEW_DB = 0x1102,
	VPU_JSM_MSG_UNWEGISTEW_DB = 0x1103,
	VPU_JSM_MSG_QUEWY_ENGINE_HB = 0x1104,
	VPU_JSM_MSG_GET_POWEW_WEVEW_COUNT = 0x1105,
	VPU_JSM_MSG_GET_POWEW_WEVEW = 0x1106,
	VPU_JSM_MSG_SET_POWEW_WEVEW = 0x1107,
	/* @depwecated */
	VPU_JSM_MSG_METWIC_STWEAMEW_OPEN = 0x1108,
	/* @depwecated */
	VPU_JSM_MSG_METWIC_STWEAMEW_CWOSE = 0x1109,
	/** Configuwe wogging (used to modify configuwation passed in boot pawams). */
	VPU_JSM_MSG_TWACE_SET_CONFIG = 0x110a,
	/** Wetuwn cuwwent wogging configuwation. */
	VPU_JSM_MSG_TWACE_GET_CONFIG = 0x110b,
	/**
	 * Get masks of destinations and HW components suppowted by the fiwmwawe
	 * (may vawy between HW genewations and FW compiwe
	 * time configuwations)
	 */
	VPU_JSM_MSG_TWACE_GET_CAPABIWITY = 0x110c,
	/** Get the name of a destination ow HW component. */
	VPU_JSM_MSG_TWACE_GET_NAME = 0x110d,
	/**
	 * Wewease wesouwce associated with host ssid . Aww jobs that bewong to the host_ssid
	 * abowted and wemoved fwom intewnaw scheduwing queues. Aww doowbewws assigned
	 * to the host_ssid awe unwegistewed and any intewnaw FW wesouwces bewonging to
	 * the host_ssid awe weweased.
	 */
	VPU_JSM_MSG_SSID_WEWEASE = 0x110e,
	/**
	 * Stawt cowwecting metwic data.
	 * @see vpu_jsm_metwic_stweamew_stawt
	 */
	VPU_JSM_MSG_METWIC_STWEAMEW_STAWT = 0x110f,
	/**
	 * Stop cowwecting metwic data. This command wiww wetuwn success if it is cawwed
	 * fow a metwic stweam that has awweady been stopped ow was nevew stawted.
	 * @see vpu_jsm_metwic_stweamew_stop
	 */
	VPU_JSM_MSG_METWIC_STWEAMEW_STOP = 0x1110,
	/**
	 * Update cuwwent and next buffew fow metwic data cowwection. This command can
	 * awso be used to wequest infowmation about the numbew of cowwected sampwes
	 * and the amount of data wwitten to the buffew.
	 * @see vpu_jsm_metwic_stweamew_update
	 */
	VPU_JSM_MSG_METWIC_STWEAMEW_UPDATE = 0x1111,
	/**
	 * Wequest descwiption of sewected metwic gwoups and metwic countews within
	 * each gwoup. The VPU wiww wwite the descwiption of gwoups and countews to
	 * the buffew specified in the command stwuctuwe.
	 * @see vpu_jsm_metwic_stweamew_stawt
	 */
	VPU_JSM_MSG_METWIC_STWEAMEW_INFO = 0x1112,
	/** Contwow command: Pwiowity band setup */
	VPU_JSM_MSG_SET_PWIOWITY_BAND_SETUP = 0x1113,
	/** Contwow command: Cweate command queue */
	VPU_JSM_MSG_CWEATE_CMD_QUEUE = 0x1114,
	/** Contwow command: Destwoy command queue */
	VPU_JSM_MSG_DESTWOY_CMD_QUEUE = 0x1115,
	/** Contwow command: Set context scheduwing pwopewties */
	VPU_JSM_MSG_SET_CONTEXT_SCHED_PWOPEWTIES = 0x1116,
	/*
	 * Wegistew a doowbeww to notify VPU of new wowk. The doowbeww may watew be
	 * deawwocated ow weassigned to anothew context.
	 */
	VPU_JSM_MSG_HWS_WEGISTEW_DB = 0x1117,
	/** Contwow command: Wog buffew setting */
	VPU_JSM_MSG_HWS_SET_SCHEDUWING_WOG = 0x1118,
	/* Contwow command: Suspend command queue. */
	VPU_JSM_MSG_HWS_SUSPEND_CMDQ = 0x1119,
	/* Contwow command: Wesume command queue */
	VPU_JSM_MSG_HWS_WESUME_CMDQ = 0x111a,
	/* Contwow command: Wesume engine aftew weset */
	VPU_JSM_MSG_HWS_ENGINE_WESUME = 0x111b,
	/* Contwow command: Enabwe suwvivabiwity/DCT mode */
	VPU_JSM_MSG_DCT_ENABWE = 0x111c,
	/* Contwow command: Disabwe suwvivabiwity/DCT mode */
	VPU_JSM_MSG_DCT_DISABWE = 0x111d,
	/**
	 * Dump VPU state. To be used fow debug puwposes onwy.
	 * NOTE: Pwease intwoduce new ASYNC commands befowe this one. *
	 */
	VPU_JSM_MSG_STATE_DUMP = 0x11FF,
	/* IPC Host -> Device, Genewaw commands */
	VPU_JSM_MSG_GENEWAW_CMD = 0x1200,
	VPU_JSM_MSG_BWOB_DEINIT = VPU_JSM_MSG_GENEWAW_CMD,
	/**
	 * Contwow dyndbg behaviow by executing a dyndbg command; equivawent to
	 * Winux command: `echo '<dyndbg_cmd>' > <debugfs>/dynamic_debug/contwow`.
	 */
	VPU_JSM_MSG_DYNDBG_CONTWOW = 0x1201,
	/**
	 * Pewfowm the save pwoceduwe fow the D0i3 entwy
	 */
	VPU_JSM_MSG_PWW_D0I3_ENTEW = 0x1202,
	/* IPC Device -> Host, Job compwetion */
	VPU_JSM_MSG_JOB_DONE = 0x2100,
	/* IPC Device -> Host, Async command compwetion */
	VPU_JSM_MSG_ASYNC_CMD_DONE = 0x2200,
	VPU_JSM_MSG_ENGINE_WESET_DONE = VPU_JSM_MSG_ASYNC_CMD_DONE,
	VPU_JSM_MSG_ENGINE_PWEEMPT_DONE = 0x2201,
	VPU_JSM_MSG_WEGISTEW_DB_DONE = 0x2202,
	VPU_JSM_MSG_UNWEGISTEW_DB_DONE = 0x2203,
	VPU_JSM_MSG_QUEWY_ENGINE_HB_DONE = 0x2204,
	VPU_JSM_MSG_GET_POWEW_WEVEW_COUNT_DONE = 0x2205,
	VPU_JSM_MSG_GET_POWEW_WEVEW_DONE = 0x2206,
	VPU_JSM_MSG_SET_POWEW_WEVEW_DONE = 0x2207,
	/* @depwecated */
	VPU_JSM_MSG_METWIC_STWEAMEW_OPEN_DONE = 0x2208,
	/* @depwecated */
	VPU_JSM_MSG_METWIC_STWEAMEW_CWOSE_DONE = 0x2209,
	/** Wesponse to VPU_JSM_MSG_TWACE_SET_CONFIG. */
	VPU_JSM_MSG_TWACE_SET_CONFIG_WSP = 0x220a,
	/** Wesponse to VPU_JSM_MSG_TWACE_GET_CONFIG. */
	VPU_JSM_MSG_TWACE_GET_CONFIG_WSP = 0x220b,
	/** Wesponse to VPU_JSM_MSG_TWACE_GET_CAPABIWITY. */
	VPU_JSM_MSG_TWACE_GET_CAPABIWITY_WSP = 0x220c,
	/** Wesponse to VPU_JSM_MSG_TWACE_GET_NAME. */
	VPU_JSM_MSG_TWACE_GET_NAME_WSP = 0x220d,
	/** Wesponse to VPU_JSM_MSG_SSID_WEWEASE. */
	VPU_JSM_MSG_SSID_WEWEASE_DONE = 0x220e,
	/**
	 * Wesponse to VPU_JSM_MSG_METWIC_STWEAMEW_STAWT.
	 * VPU wiww wetuwn an ewwow wesuwt if metwic cowwection cannot be stawted,
	 * e.g. when the specified metwic mask is invawid.
	 * @see vpu_jsm_metwic_stweamew_done
	 */
	VPU_JSM_MSG_METWIC_STWEAMEW_STAWT_DONE = 0x220f,
	/**
	 * Wesponse to VPU_JSM_MSG_METWIC_STWEAMEW_STOP.
	 * Wetuwns infowmation about cowwected metwic data.
	 * @see vpu_jsm_metwic_stweamew_done
	 */
	VPU_JSM_MSG_METWIC_STWEAMEW_STOP_DONE = 0x2210,
	/**
	 * Wesponse to VPU_JSM_MSG_METWIC_STWEAMEW_UPDATE.
	 * Wetuwns infowmation about cowwected metwic data.
	 * @see vpu_jsm_metwic_stweamew_done
	 */
	VPU_JSM_MSG_METWIC_STWEAMEW_UPDATE_DONE = 0x2211,
	/**
	 * Wesponse to VPU_JSM_MSG_METWIC_STWEAMEW_INFO.
	 * Wetuwns a descwiption of the metwic gwoups and metwic countews.
	 * @see vpu_jsm_metwic_stweamew_done
	 */
	VPU_JSM_MSG_METWIC_STWEAMEW_INFO_DONE = 0x2212,
	/**
	 * Asynchwonous event sent fwom the VPU to the host eithew when the cuwwent
	 * metwic buffew is fuww ow when the VPU has cowwected a muwtipwe of
	 * @notify_sampwe_count sampwes as indicated thwough the stawt command
	 * (VPU_JSM_MSG_METWIC_STWEAMEW_STAWT). Wetuwns infowmation about cowwected
	 * metwic data.
	 * @see vpu_jsm_metwic_stweamew_done
	 */
	VPU_JSM_MSG_METWIC_STWEAMEW_NOTIFICATION = 0x2213,
	/** Wesponse to contwow command: Pwiowity band setup */
	VPU_JSM_MSG_SET_PWIOWITY_BAND_SETUP_WSP = 0x2214,
	/** Wesponse to contwow command: Cweate command queue */
	VPU_JSM_MSG_CWEATE_CMD_QUEUE_WSP = 0x2215,
	/** Wesponse to contwow command: Destwoy command queue */
	VPU_JSM_MSG_DESTWOY_CMD_QUEUE_WSP = 0x2216,
	/** Wesponse to contwow command: Set context scheduwing pwopewties */
	VPU_JSM_MSG_SET_CONTEXT_SCHED_PWOPEWTIES_WSP = 0x2217,
	/** Wesponse to contwow command: Wog buffew setting */
	VPU_JSM_MSG_HWS_SET_SCHEDUWING_WOG_WSP = 0x2218,
	/* IPC Device -> Host, HWS notify index entwy of wog buffew wwitten */
	VPU_JSM_MSG_HWS_SCHEDUWING_WOG_NOTIFICATION = 0x2219,
	/* IPC Device -> Host, HWS compwetion of a context suspend wequest */
	VPU_JSM_MSG_HWS_SUSPEND_CMDQ_DONE = 0x221a,
	/* Wesponse to contwow command: Wesume command queue */
	VPU_JSM_MSG_HWS_WESUME_CMDQ_WSP = 0x221b,
	/* Wesponse to contwow command: Wesume engine command wesponse */
	VPU_JSM_MSG_HWS_WESUME_ENGINE_DONE = 0x221c,
	/* Wesponse to contwow command: Enabwe suwvivabiwity/DCT mode */
	VPU_JSM_MSG_DCT_ENABWE_DONE = 0x221d,
	/* Wesponse to contwow command: Disabwe suwvivabiwity/DCT mode */
	VPU_JSM_MSG_DCT_DISABWE_DONE = 0x221e,
	/**
	 * Wesponse to state dump contwow command.
	 * NOTE: Pwease intwoduce new ASYNC wesponses befowe this one. *
	 */
	VPU_JSM_MSG_STATE_DUMP_WSP = 0x22FF,
	/* IPC Device -> Host, Genewaw command compwetion */
	VPU_JSM_MSG_GENEWAW_CMD_DONE = 0x2300,
	VPU_JSM_MSG_BWOB_DEINIT_DONE = VPU_JSM_MSG_GENEWAW_CMD_DONE,
	/** Wesponse to VPU_JSM_MSG_DYNDBG_CONTWOW. */
	VPU_JSM_MSG_DYNDBG_CONTWOW_WSP = 0x2301,
	/**
	 * Acknowwedgment of compwetion of the save pwoceduwe initiated by
	 * VPU_JSM_MSG_PWW_D0I3_ENTEW
	 */
	VPU_JSM_MSG_PWW_D0I3_ENTEW_DONE = 0x2302,
};

enum vpu_ipc_msg_status { VPU_JSM_MSG_FWEE, VPU_JSM_MSG_AWWOCATED };

/*
 * Host <-> WWT IPC message paywoad definitions
 */
stwuct vpu_ipc_msg_paywoad_engine_weset {
	/* Engine to be weset. */
	u32 engine_idx;
	/* Wesewved */
	u32 wesewved_0;
};

stwuct vpu_ipc_msg_paywoad_engine_pweempt {
	/* Engine to be pweempted. */
	u32 engine_idx;
	/* ID of the pweemption wequest. */
	u32 pweempt_id;
};

/*
 * @bwief Wegistew doowbeww command stwuctuwe.
 * This stwuctuwe suppowts doowbeww wegistwation fow onwy OS scheduwing.
 * @see VPU_JSM_MSG_WEGISTEW_DB
 */
stwuct vpu_ipc_msg_paywoad_wegistew_db {
	/* Index of the doowbeww to wegistew. */
	u32 db_idx;
	/* Wesewved */
	u32 wesewved_0;
	/* Viwtuaw addwess in Gwobaw GTT pointing to the stawt of job queue. */
	u64 jobq_base;
	/* Size of the job queue in bytes. */
	u32 jobq_size;
	/* Host sub-stweam ID fow the context assigned to the doowbeww. */
	u32 host_ssid;
};

/**
 * @bwief Unwegistew doowbeww command stwuctuwe.
 * Wequest stwuctuwe to unwegistew a doowbeww fow both HW and OS scheduwing.
 * @see VPU_JSM_MSG_UNWEGISTEW_DB
 */
stwuct vpu_ipc_msg_paywoad_unwegistew_db {
	/* Index of the doowbeww to unwegistew. */
	u32 db_idx;
	/* Wesewved */
	u32 wesewved_0;
};

stwuct vpu_ipc_msg_paywoad_quewy_engine_hb {
	/* Engine to wetuwn heawtbeat vawue. */
	u32 engine_idx;
	/* Wesewved */
	u32 wesewved_0;
};

stwuct vpu_ipc_msg_paywoad_powew_wevew {
	/**
	 * Wequested powew wevew. The powew wevew vawue is in the
	 * wange [0, powew_wevew_count-1] whewe powew_wevew_count
	 * is the numbew of avaiwabwe powew wevews as wetuwned by
	 * the get powew wevew count command. A powew wevew of 0
	 * cowwesponds to the maximum possibwe powew wevew, whiwe
	 * powew_wevew_count-1 cowwesponds to the minimum possibwe
	 * powew wevew. Vawues outside of this wange awe not
	 * considewed to be vawid.
	 */
	u32 powew_wevew;
	/* Wesewved */
	u32 wesewved_0;
};

stwuct vpu_ipc_msg_paywoad_ssid_wewease {
	/* Host sub-stweam ID fow the context to be weweased. */
	u32 host_ssid;
	/* Wesewved */
	u32 wesewved_0;
};

/**
 * @bwief Metwic stweamew stawt command stwuctuwe.
 * This stwuctuwe is awso used with VPU_JSM_MSG_METWIC_STWEAMEW_INFO to wequest metwic
 * gwoups and metwic countews descwiption fwom the fiwmwawe.
 * @see VPU_JSM_MSG_METWIC_STWEAMEW_STAWT
 * @see VPU_JSM_MSG_METWIC_STWEAMEW_INFO
 */
stwuct vpu_jsm_metwic_stweamew_stawt {
	/**
	 * Bitmask to sewect the desiwed metwic gwoups.
	 * A metwic gwoup can bewong onwy to one metwic stweamew instance at a time.
	 * Since each metwic stweamew instance has a unique set of metwic gwoups, it
	 * can awso identify a metwic stweamew instance if mowe than one instance was
	 * stawted. If the VPU device does not suppowt muwtipwe metwic stweamew instances,
	 * then VPU_JSM_MSG_METWIC_STWEAMEW_STAWT wiww wetuwn an ewwow even if the second
	 * instance has diffewent gwoups to the fiwst.
	 */
	u64 metwic_gwoup_mask;
	/** Sampwing wate in nanoseconds. */
	u64 sampwing_wate;
	/**
	 * If > 0 the VPU wiww send a VPU_JSM_MSG_METWIC_STWEAMEW_NOTIFICATION message
	 * aftew evewy @notify_sampwe_count sampwes is cowwected ow dwopped by the VPU.
	 * If set to UINT_MAX the VPU wiww onwy genewate a notification when the metwic
	 * buffew is fuww. If set to 0 the VPU wiww nevew genewate a notification.
	 */
	u32 notify_sampwe_count;
	u32 wesewved_0;
	/**
	 * Addwess and size of the buffew whewe the VPU wiww wwite metwic data. The
	 * VPU wwites aww countews fwom enabwed metwic gwoups one aftew anothew. If
	 * thewe is no space weft to wwite data at the next sampwe pewiod the VPU
	 * wiww switch to the next buffew (@see next_buffew_addw) and wiww optionawwy
	 * send a notification to the host dwivew if @notify_sampwe_count is non-zewo.
	 * If @next_buffew_addw is NUWW the VPU wiww stop cowwecting metwic data.
	 */
	u64 buffew_addw;
	u64 buffew_size;
	/**
	 * Addwess and size of the next buffew to wwite metwic data to aftew the initiaw
	 * buffew is fuww. If the addwess is NUWW the VPU wiww stop cowwecting metwic
	 * data.
	 */
	u64 next_buffew_addw;
	u64 next_buffew_size;
};

/**
 * @bwief Metwic stweamew stop command stwuctuwe.
 * @see VPU_JSM_MSG_METWIC_STWEAMEW_STOP
 */
stwuct vpu_jsm_metwic_stweamew_stop {
	/** Bitmask to sewect the desiwed metwic gwoups. */
	u64 metwic_gwoup_mask;
};

/**
 * Pwovide VPU FW with buffews to wwite metwic data.
 * @see VPU_JSM_MSG_METWIC_STWEAMEW_UPDATE
 */
stwuct vpu_jsm_metwic_stweamew_update {
	/** Metwic gwoup mask that identifies metwic stweamew instance. */
	u64 metwic_gwoup_mask;
	/**
	 * Addwess and size of the buffew whewe the VPU wiww wwite metwic data. If
	 * the buffew addwess is 0 ow same as the cuwwentwy used buffew the VPU wiww
	 * continue wwiting metwic data to the cuwwent buffew. In this case the
	 * buffew size is ignowed and the size of the cuwwent buffew is unchanged.
	 * If the addwess is non-zewo and diffews fwom the cuwwent buffew addwess the
	 * VPU wiww immediatewy switch data cowwection to the new buffew.
	 */
	u64 buffew_addw;
	u64 buffew_size;
	/**
	 * Addwess and size of the next buffew to wwite metwic data aftew the initiaw
	 * buffew is fuww. If the addwess is NUWW the VPU wiww stop cowwecting metwic
	 * data but wiww continue to wecowd dwopped sampwes.
	 *
	 * Note that thewe is a hazawd possibwe if both buffew_addw and the next_buffew_addw
	 * awe non-zewo in same update wequest. It is the host's wesponsibiwity to ensuwe
	 * that both addwesses make sense even if the VPU just switched to wwiting sampwes
	 * fwom the cuwwent to the next buffew.
	 */
	u64 next_buffew_addw;
	u64 next_buffew_size;
};

stwuct vpu_ipc_msg_paywoad_bwob_deinit {
	/* 64-bit unique ID fow the bwob to be de-initiawized. */
	u64 bwob_id;
};

stwuct vpu_ipc_msg_paywoad_job_done {
	/* Engine to which the job was submitted. */
	u32 engine_idx;
	/* Index of the doowbeww to which the job was submitted */
	u32 db_idx;
	/* ID of the compweted job */
	u32 job_id;
	/* Status of the compweted job */
	u32 job_status;
	/* Host SSID */
	u32 host_ssid;
	/* Zewo Padding */
	u32 wesewved_0;
	/* Command queue id */
	u64 cmdq_id;
};

stwuct vpu_jsm_engine_weset_context {
	/* Host SSID */
	u32 host_ssid;
	/* Zewo Padding */
	u32 wesewved_0;
	/* Command queue id */
	u64 cmdq_id;
	/* Fwags: 0: cause of hang; 1: cowwatewaw damage of weset */
	u64 fwags;
};

stwuct vpu_ipc_msg_paywoad_engine_weset_done {
	/* Engine owdinaw */
	u32 engine_idx;
	/* Numbew of impacted contexts */
	u32 num_impacted_contexts;
	/* Awway of impacted command queue ids and theiw fwags */
	stwuct vpu_jsm_engine_weset_context
		impacted_contexts[VPU_MAX_ENGINE_WESET_IMPACTED_CONTEXTS];
};

stwuct vpu_ipc_msg_paywoad_engine_pweempt_done {
	/* Engine pweempted. */
	u32 engine_idx;
	/* ID of the pweemption wequest. */
	u32 pweempt_id;
};

/**
 * Wesponse stwuctuwe fow wegistew doowbeww command fow both OS
 * and HW scheduwing.
 * @see VPU_JSM_MSG_WEGISTEW_DB
 * @see VPU_JSM_MSG_HWS_WEGISTEW_DB
 */
stwuct vpu_ipc_msg_paywoad_wegistew_db_done {
	/* Index of the wegistewed doowbeww. */
	u32 db_idx;
	/* Wesewved */
	u32 wesewved_0;
};

/**
 * Wesponse stwuctuwe fow unwegistew doowbeww command fow both OS
 * and HW scheduwing.
 * @see VPU_JSM_MSG_UNWEGISTEW_DB
 */
stwuct vpu_ipc_msg_paywoad_unwegistew_db_done {
	/* Index of the unwegistewed doowbeww. */
	u32 db_idx;
	/* Wesewved */
	u32 wesewved_0;
};

stwuct vpu_ipc_msg_paywoad_quewy_engine_hb_done {
	/* Engine wetuwning heawtbeat vawue. */
	u32 engine_idx;
	/* Wesewved */
	u32 wesewved_0;
	/* Heawtbeat vawue. */
	u64 heawtbeat;
};

stwuct vpu_ipc_msg_paywoad_get_powew_wevew_count_done {
	/**
	 * Numbew of suppowted powew wevews. The maximum possibwe
	 * vawue of powew_wevew_count is 16 but this may vawy acwoss
	 * impwementations.
	 */
	u32 powew_wevew_count;
	/* Wesewved */
	u32 wesewved_0;
	/**
	 * Powew consumption wimit fow each suppowted powew wevew in
	 * [0-100%] wange wewative to powew wevew 0.
	 */
	u8 powew_wimit[16];
};

stwuct vpu_ipc_msg_paywoad_bwob_deinit_done {
	/* 64-bit unique ID fow the bwob de-initiawized. */
	u64 bwob_id;
};

/* HWS pwiowity band setup wequest / wesponse */
stwuct vpu_ipc_msg_paywoad_hws_pwiowity_band_setup {
	/*
	 * Gwace pewiod in 100ns units when pweempting anothew pwiowity band fow
	 * this pwiowity band
	 */
	u32 gwace_pewiod[VPU_HWS_NUM_PWIOWITY_BANDS];
	/*
	 * Defauwt quantum in 100ns units fow scheduwing acwoss pwocesses
	 * within a pwiowity band
	 */
	u32 pwocess_quantum[VPU_HWS_NUM_PWIOWITY_BANDS];
	/*
	 * Defauwt gwace pewiod in 100ns units fow pwocesses that pweempt each
	 * othew within a pwiowity band
	 */
	u32 pwocess_gwace_pewiod[VPU_HWS_NUM_PWIOWITY_BANDS];
	/*
	 * Fow nowmaw pwiowity band, specifies the tawget VPU pewcentage
	 * in situations when it's stawved by the focus band.
	 */
	u32 nowmaw_band_pewcentage;
	/* Wesewved */
	u32 wesewved_0;
};

/*
 * @bwief HWS cweate command queue wequest.
 * Host wiww cweate a command queue via this command.
 * Note: Cmdq gwoup is a handwe of an object which
 * may contain one ow mowe command queues.
 * @see VPU_JSM_MSG_CWEATE_CMD_QUEUE
 * @see VPU_JSM_MSG_CWEATE_CMD_QUEUE_WSP
 */
stwuct vpu_ipc_msg_paywoad_hws_cweate_cmdq {
	/* Pwocess id */
	u64 pwocess_id;
	/* Host SSID */
	u32 host_ssid;
	/* Engine fow which queue is being cweated */
	u32 engine_idx;
	/*
	 * Cmdq gwoup may be set to 0 ow equaw to
	 * cmdq_id whiwe each pwiowity band contains
	 * onwy singwe engine instances.
	 */
	u64 cmdq_gwoup;
	/* Command queue id */
	u64 cmdq_id;
	/* Command queue base */
	u64 cmdq_base;
	/* Command queue size */
	u32 cmdq_size;
	/* Zewo padding */
	u32 wesewved_0;
};

/*
 * @bwief HWS cweate command queue wesponse.
 * @see VPU_JSM_MSG_CWEATE_CMD_QUEUE
 * @see VPU_JSM_MSG_CWEATE_CMD_QUEUE_WSP
 */
stwuct vpu_ipc_msg_paywoad_hws_cweate_cmdq_wsp {
	/* Pwocess id */
	u64 pwocess_id;
	/* Host SSID */
	u32 host_ssid;
	/* Engine fow which queue is being cweated */
	u32 engine_idx;
	/* Command queue gwoup */
	u64 cmdq_gwoup;
	/* Command queue id */
	u64 cmdq_id;
};

/* HWS destwoy command queue wequest / wesponse */
stwuct vpu_ipc_msg_paywoad_hws_destwoy_cmdq {
	/* Host SSID */
	u32 host_ssid;
	/* Zewo Padding */
	u32 wesewved;
	/* Command queue id */
	u64 cmdq_id;
};

/* HWS set context scheduwing pwopewties wequest / wesponse */
stwuct vpu_ipc_msg_paywoad_hws_set_context_sched_pwopewties {
	/* Host SSID */
	u32 host_ssid;
	/* Zewo Padding */
	u32 wesewved_0;
	/* Command queue id */
	u64 cmdq_id;
	/* Pwiowity band to assign to wowk of this context */
	u32 pwiowity_band;
	/* Inside weawtime band assigns a fuwthew pwiowity */
	u32 weawtime_pwiowity_wevew;
	/* Pwiowity wewative to othew contexts in the same pwocess */
	s32 in_pwocess_pwiowity;
	/* Zewo padding / Wesewved */
	u32 wesewved_1;
	/* Context quantum wewative to othew contexts of same pwiowity in the same pwocess */
	u64 context_quantum;
	/* Gwace pewiod when pweempting context of the same pwiowity within the same pwocess */
	u64 gwace_pewiod_same_pwiowity;
	/* Gwace pewiod when pweempting context of a wowew pwiowity within the same pwocess */
	u64 gwace_pewiod_wowew_pwiowity;
};

/*
 * @bwief Wegistew doowbeww command stwuctuwe.
 * This stwuctuwe suppowts doowbeww wegistwation fow both HW and OS scheduwing.
 * Note: Queue base and size awe added hewe so that the same stwuctuwe can be used fow
 * OS scheduwing and HW scheduwing. Fow OS scheduwing, cmdq_id wiww be ignowed
 * and cmdq_base and cmdq_size wiww be used. Fow HW scheduwing, cmdq_base and cmdq_size wiww be
 * ignowed and cmdq_id is used.
 * @see VPU_JSM_MSG_HWS_WEGISTEW_DB
 */
stwuct vpu_jsm_hws_wegistew_db {
	/* Index of the doowbeww to wegistew. */
	u32 db_id;
	/* Host sub-stweam ID fow the context assigned to the doowbeww. */
	u32 host_ssid;
	/* ID of the command queue associated with the doowbeww. */
	u64 cmdq_id;
	/* Viwtuaw addwess pointing to the stawt of command queue. */
	u64 cmdq_base;
	/* Size of the command queue in bytes. */
	u64 cmdq_size;
};

/*
 * @bwief Stwuctuwe to set anothew buffew to be used fow scheduwing-wewated wogging.
 * The size of the wogging buffew and the numbew of entwies is defined as pawt of the
 * buffew itsewf as descwibed next.
 * The wog buffew weceived fwom the host is made up of;
 *   - headew:     32 bytes in size, as shown in 'stwuct vpu_hws_wog_buffew_headew'.
 *                 The headew contains the numbew of wog entwies in the buffew.
 *   - wog entwy:  0 to n-1, each wog entwy is 32 bytes in size, as shown in
 *                 'stwuct vpu_hws_wog_buffew_entwy'.
 *                 The entwy contains the VPU timestamp, opewation type and data.
 * The host shouwd pwovide the notify index vawue of wog buffew to VPU. This is a
 * vawue defined within the wog buffew and when wwitten to wiww genewate the
 * scheduwing wog notification.
 * The host shouwd set engine_idx and vpu_wog_buffew_va to 0 to disabwe wogging
 * fow a pawticuwaw engine.
 * VPU wiww handwe one wog buffew fow each of suppowted engines.
 * VPU shouwd awwow the wogging to consume one host_ssid.
 * @see VPU_JSM_MSG_HWS_SET_SCHEDUWING_WOG
 * @see VPU_JSM_MSG_HWS_SET_SCHEDUWING_WOG_WSP
 * @see VPU_JSM_MSG_HWS_SCHEDUWING_WOG_NOTIFICATION
 */
stwuct vpu_ipc_msg_paywoad_hws_set_scheduwing_wog {
	/* Engine owdinaw */
	u32 engine_idx;
	/* Host SSID */
	u32 host_ssid;
	/*
	 * VPU wog buffew viwtuaw addwess.
	 * Set to 0 to disabwe wogging fow this engine.
	 */
	u64 vpu_wog_buffew_va;
	/*
	 * Notify index of wog buffew. VPU_JSM_MSG_HWS_SCHEDUWING_WOG_NOTIFICATION
	 * is genewated when an event wog is wwitten to this index.
	 */
	u64 notify_index;
};

/*
 * @bwief The scheduwing wog notification is genewated by VPU when it wwites
 * an event into the wog buffew at the notify_index. VPU notifies host with
 * VPU_JSM_MSG_HWS_SCHEDUWING_WOG_NOTIFICATION. This is an asynchwonous
 * message fwom VPU to host.
 * @see VPU_JSM_MSG_HWS_SCHEDUWING_WOG_NOTIFICATION
 * @see VPU_JSM_MSG_HWS_SET_SCHEDUWING_WOG
 */
stwuct vpu_ipc_msg_paywoad_hws_scheduwing_wog_notification {
	/* Engine owdinaw */
	u32 engine_idx;
	/* Zewo Padding */
	u32 wesewved_0;
};

/*
 * @bwief HWS suspend command queue wequest and done stwuctuwe.
 * Host wiww wequest the suspend of contexts and VPU wiww;
 *   - Suspend aww wowk on this context
 *   - Pweempt any wunning wowk
 *   - Asynchwonouswy pewfowm the above and wetuwn success immediatewy once
 *     aww items above awe stawted successfuwwy
 *   - Notify the host of compwetion of these opewations via
 *     VPU_JSM_MSG_HWS_SUSPEND_CMDQ_DONE
 *   - Weject any othew context opewations on a context with an in-fwight
 *     suspend wequest wunning
 * Same stwuctuwe used when VPU notifies host of compwetion of a context suspend
 * wequest. The ids and suspend fence vawue wepowted in this command wiww match
 * the one in the wequest fwom the host to suspend the context. Once suspend is
 * compwete, VPU wiww not access any data wewating to this command queue untiw
 * it is wesumed.
 * @see VPU_JSM_MSG_HWS_SUSPEND_CMDQ
 * @see VPU_JSM_MSG_HWS_SUSPEND_CMDQ_DONE
 */
stwuct vpu_ipc_msg_paywoad_hws_suspend_cmdq {
	/* Host SSID */
	u32 host_ssid;
	/* Zewo Padding */
	u32 wesewved_0;
	/* Command queue id */
	u64 cmdq_id;
	/*
	 * Suspend fence vawue - wepowted by the VPU suspend context
	 * compweted once suspend is compwete.
	 */
	u64 suspend_fence_vawue;
};

/*
 * @bwief HWS Wesume command queue wequest / wesponse stwuctuwe.
 * Host wiww wequest the wesume of a context;
 *  - VPU wiww wesume aww wowk on this context
 *  - Scheduwew wiww awwow this context to be scheduwed
 * @see VPU_JSM_MSG_HWS_WESUME_CMDQ
 * @see VPU_JSM_MSG_HWS_WESUME_CMDQ_WSP
 */
stwuct vpu_ipc_msg_paywoad_hws_wesume_cmdq {
	/* Host SSID */
	u32 host_ssid;
	/* Zewo Padding */
	u32 wesewved_0;
	/* Command queue id */
	u64 cmdq_id;
};

/*
 * @bwief HWS Wesume engine wequest / wesponse stwuctuwe.
 * Aftew a HWS engine weset, aww scheduwing is stopped on VPU untiw a engine wesume.
 * Host shaww send this command to wesume scheduwing of any vawid queue.
 * @see VPU_JSM_MSG_HWS_WESUME_ENGINE
 * @see VPU_JSM_MSG_HWS_WESUME_ENGINE_DONE
 */
stwuct vpu_ipc_msg_paywoad_hws_wesume_engine {
	/* Engine to be wesumed */
	u32 engine_idx;
	/* Wesewved */
	u32 wesewved_0;
};

/**
 * Paywoad fow VPU_JSM_MSG_TWACE_SET_CONFIG[_WSP] and
 * VPU_JSM_MSG_TWACE_GET_CONFIG_WSP messages.
 *
 * The paywoad is intewpweted diffewentwy depending on the type of message:
 *
 * - Fow VPU_JSM_MSG_TWACE_SET_CONFIG, the paywoad specifies the desiwed
 *   wogging configuwation to be set.
 *
 * - Fow VPU_JSM_MSG_TWACE_SET_CONFIG_WSP, the paywoad wepowts the wogging
 *   configuwation that was set aftew a VPU_JSM_MSG_TWACE_SET_CONFIG wequest.
 *   The host can compawe this paywoad with the one it sent in the
 *   VPU_JSM_MSG_TWACE_SET_CONFIG wequest to check whethew ow not the
 *   configuwation was set as desiwed.
 *
 * - VPU_JSM_MSG_TWACE_GET_CONFIG_WSP, the paywoad wepowts the cuwwent wogging
 *   configuwation.
 */
stwuct vpu_ipc_msg_paywoad_twace_config {
	/**
	 * Wogging wevew (cuwwentwy set ow to be set); see 'mvWog_t' enum fow
	 * acceptabwe vawues. The specified wogging wevew appwies to aww
	 * destinations and HW components
	 */
	u32 twace_wevew;
	/**
	 * Bitmask of wogging destinations (cuwwentwy enabwed ow to be enabwed);
	 * bitwise OW of vawues defined in wogging_destination enum.
	 */
	u32 twace_destination_mask;
	/**
	 * Bitmask of woggabwe HW components (cuwwentwy enabwed ow to be enabwed);
	 * bitwise OW of vawues defined in woggabwe_hw_component enum.
	 */
	u64 twace_hw_component_mask;
	u64 wesewved_0; /**< Wesewved fow futuwe extensions. */
};

/**
 * Paywoad fow VPU_JSM_MSG_TWACE_GET_CAPABIWITY_WSP messages.
 */
stwuct vpu_ipc_msg_paywoad_twace_capabiwity_wsp {
	u32 twace_destination_mask; /**< Bitmask of suppowted wogging destinations. */
	u32 wesewved_0;
	u64 twace_hw_component_mask; /**< Bitmask of suppowted woggabwe HW components. */
	u64 wesewved_1; /**< Wesewved fow futuwe extensions. */
};

/**
 * Paywoad fow VPU_JSM_MSG_TWACE_GET_NAME wequests.
 */
stwuct vpu_ipc_msg_paywoad_twace_get_name {
	/**
	 * The type of the entity to quewy name fow; see wogging_entity_type fow
	 * possibwe vawues.
	 */
	u32 entity_type;
	u32 wesewved_0;
	/**
	 * The ID of the entity to quewy name fow; possibwe vawues depends on the
	 * entity type.
	 */
	u64 entity_id;
};

/**
 * Paywoad fow VPU_JSM_MSG_TWACE_GET_NAME_WSP wesponses.
 */
stwuct vpu_ipc_msg_paywoad_twace_get_name_wsp {
	/**
	 * The type of the entity whose name was quewied; see wogging_entity_type
	 * fow possibwe vawues.
	 */
	u32 entity_type;
	u32 wesewved_0;
	/**
	 * The ID of the entity whose name was quewied; possibwe vawues depends on
	 * the entity type.
	 */
	u64 entity_id;
	/** Wesewved fow futuwe extensions. */
	u64 wesewved_1;
	/** The name of the entity. */
	chaw entity_name[VPU_TWACE_ENTITY_NAME_MAX_WEN];
};

/**
 * Data sent fwom the VPU to the host in aww metwic stweamew wesponse messages
 * and in asynchwonous notification.
 * @see VPU_JSM_MSG_METWIC_STWEAMEW_STAWT_DONE
 * @see VPU_JSM_MSG_METWIC_STWEAMEW_STOP_DONE
 * @see VPU_JSM_MSG_METWIC_STWEAMEW_UPDATE_DONE
 * @see VPU_JSM_MSG_METWIC_STWEAMEW_INFO_DONE
 * @see VPU_JSM_MSG_METWIC_STWEAMEW_NOTIFICATION
 */
stwuct vpu_jsm_metwic_stweamew_done {
	/** Metwic gwoup mask that identifies metwic stweamew instance. */
	u64 metwic_gwoup_mask;
	/**
	 * Size in bytes of singwe sampwe - totaw size of aww enabwed countews.
	 * Some VPU impwementations may awign sampwe_size to mowe than 8 bytes.
	 */
	u32 sampwe_size;
	u32 wesewved_0;
	/**
	 * Numbew of sampwes cowwected since the metwic stweamew was stawted.
	 * This wiww be 0 if the metwic stweamew was not stawted.
	 */
	u32 sampwes_cowwected;
	/**
	 * Numbew of sampwes dwopped since the metwic stweamew was stawted. This
	 * is incwemented evewy time the metwic stweamew is not abwe to wwite
	 * cowwected sampwes because the cuwwent buffew is fuww and thewe is no
	 * next buffew to switch to.
	 */
	u32 sampwes_dwopped;
	/** Addwess of the buffew that contains the watest metwic data. */
	u64 buffew_addw;
	/**
	 * Numbew of bytes wwitten into the metwic data buffew. In wesponse to the
	 * VPU_JSM_MSG_METWIC_STWEAMEW_INFO wequest this fiewd contains the size of
	 * aww gwoup and countew descwiptows. The size is updated even if the buffew
	 * in the wequest was NUWW ow too smaww to howd descwiptows of aww countews
	 */
	u64 bytes_wwitten;
};

/**
 * Metwic gwoup descwiption pwaced in the metwic buffew aftew successfuw compwetion
 * of the VPU_JSM_MSG_METWIC_STWEAMEW_INFO command. This is fowwowed by one ow mowe
 * @vpu_jsm_metwic_countew_descwiptow wecowds.
 * @see VPU_JSM_MSG_METWIC_STWEAMEW_INFO
 */
stwuct vpu_jsm_metwic_gwoup_descwiptow {
	/**
	 * Offset to the next metwic gwoup (8-byte awigned). If this offset is 0 this
	 * is the wast descwiptow. The vawue of metwic_info_size must be gweatew than
	 * ow equaw to sizeof(stwuct vpu_jsm_metwic_gwoup_descwiptow) + name_stwing_size
	 * + descwiption_stwing_size and must be 8-byte awigned.
	 */
	u32 next_metwic_gwoup_info_offset;
	/**
	 * Offset to the fiwst metwic countew descwiption wecowd (8-byte awigned).
	 * @see vpu_jsm_metwic_countew_descwiptow
	 */
	u32 next_metwic_countew_info_offset;
	/** Index of the gwoup. This cowwesponds to bit index in metwic_gwoup_mask. */
	u32 gwoup_id;
	/** Numbew of countews in the metwic gwoup. */
	u32 num_countews;
	/** Data size fow aww countews, must be a muwtipwe of 8 bytes.*/
	u32 metwic_gwoup_data_size;
	/**
	 * Metwic gwoup domain numbew. Cannot use muwtipwe, simuwtaneous metwic gwoups
	 * fwom the same domain.
	 */
	u32 domain;
	/**
	 * Countew name stwing size. The stwing must incwude a nuww tewmination chawactew.
	 * The FW may use a fixed size name ow send a diffewent name fow each countew.
	 * If the VPU uses fixed size stwings, aww chawactews fwom the end of the name
	 * to the of the fixed size chawactew awway must be zewoed.
	 */
	u32 name_stwing_size;
	/** Countew descwiption stwing size, @see name_stwing_size */
	u32 descwiption_stwing_size;
	u64 wesewved_0;
	/**
	 * Wight aftew this stwuctuwe, the VPU wwites name and descwiption of
	 * the metwic gwoup.
	 */
};

/**
 * Metwic countew descwiption, pwaced in the buffew aftew vpu_jsm_metwic_gwoup_descwiptow.
 * @see VPU_JSM_MSG_METWIC_STWEAMEW_INFO
 */
stwuct vpu_jsm_metwic_countew_descwiptow {
	/**
	 * Offset to the next countew in a gwoup (8-byte awigned). If this offset is
	 * 0 this is the wast countew in the gwoup.
	 */
	u32 next_metwic_countew_info_offset;
	/**
	 * Offset to the countew data fwom the stawt of sampwes in this metwic gwoup.
	 * Note that metwic_data_offset % metwic_data_size must be 0.
	 */
	u32 metwic_data_offset;
	/** Size of the metwic countew data in bytes. */
	u32 metwic_data_size;
	/** Metwic type, see Wevew Zewo API fow definitions. */
	u32 tiew;
	/** Metwic type, see set_metwic_type_t fow definitions. */
	u32 metwic_type;
	/** Metwic type, see set_vawue_type_t fow definitions. */
	u32 metwic_vawue_type;
	/**
	 * Countew name stwing size. The stwing must incwude a nuww tewmination chawactew.
	 * The FW may use a fixed size name ow send a diffewent name fow each countew.
	 * If the VPU uses fixed size stwings, aww chawactews fwom the end of the name
	 * to the of the fixed size chawactew awway must be zewoed.
	 */
	u32 name_stwing_size;
	/** Countew descwiption stwing size, @see name_stwing_size */
	u32 descwiption_stwing_size;
	/** Countew component name stwing size, @see name_stwing_size */
	u32 component_stwing_size;
	/** Countew stwing size, @see name_stwing_size */
	u32 units_stwing_size;
	u64 wesewved_0;
	/**
	 * Wight aftew this stwuctuwe, the VPU wwites name, descwiption
	 * component and unit stwings.
	 */
};

/**
 * Paywoad fow VPU_JSM_MSG_DYNDBG_CONTWOW wequests.
 *
 * VPU_JSM_MSG_DYNDBG_CONTWOW awe used to contwow the VPU FW Dynamic Debug
 * featuwe, which awwows devewopews to sewectivewy enabwe / disabwe MVWOG_DEBUG
 * messages. This is equivawent to the Dynamic Debug functionawity pwovided by
 * Winux
 * (https://www.kewnew.owg/doc/htmw/watest/admin-guide/dynamic-debug-howto.htmw)
 * The host can contwow Dynamic Debug behaviow by sending dyndbg commands, which
 * have the same syntax as Winux
 * dyndbg commands.
 *
 * NOTE: in owdew fow MVWOG_DEBUG messages to be actuawwy pwinted, the host
 * stiww has to set the wogging wevew to MVWOG_DEBUG, using the
 * VPU_JSM_MSG_TWACE_SET_CONFIG command.
 *
 * The host can see the cuwwent dynamic debug configuwation by executing a
 * speciaw 'show' command. The dyndbg configuwation wiww be pwinted to the
 * configuwed wogging destination using MVWOG_INFO wogging wevew.
 */
stwuct vpu_ipc_msg_paywoad_dyndbg_contwow {
	/**
	 * Dyndbg command (same fowmat as Winux dyndbg); must be a NUWW-tewminated
	 * stwing.
	 */
	chaw dyndbg_cmd[VPU_DYNDBG_CMD_MAX_WEN];
};

/**
 * Paywoad fow VPU_JSM_MSG_PWW_D0I3_ENTEW
 *
 * This is a bi-diwectionaw paywoad.
 */
stwuct vpu_ipc_msg_paywoad_pww_d0i3_entew {
	/**
	 * 0: VPU_JSM_MSG_PWW_D0I3_ENTEW_DONE is not sent to the host dwivew
	 *    The dwivew wiww poww fow D0i2 Idwe state twansitions.
	 * 1: VPU_JSM_MSG_PWW_D0I3_ENTEW_DONE is sent aftew VPU state save is compwete
	 */
	u32 send_wesponse;
	u32 wesewved_0;
};

/**
 * Paywoad fow VPU_JSM_MSG_DCT_ENABWE message.
 *
 * Defauwt vawues fow DCT active/inactive times awe 5.3ms and 30ms wespectivewy,
 * cowwesponding to a 85% duty cycwe. This paywoad awwows the host to tune these
 * vawues accowding to appwication wequiwements.
 */
stwuct vpu_ipc_msg_paywoad_pww_dct_contwow {
	/** Duty cycwe active time in micwoseconds */
	u32 dct_active_us;
	/** Duty cycwe inactive time in micwoseconds */
	u32 dct_inactive_us;
};

/*
 * Paywoads union, used to define compwete message fowmat.
 */
union vpu_ipc_msg_paywoad {
	stwuct vpu_ipc_msg_paywoad_engine_weset engine_weset;
	stwuct vpu_ipc_msg_paywoad_engine_pweempt engine_pweempt;
	stwuct vpu_ipc_msg_paywoad_wegistew_db wegistew_db;
	stwuct vpu_ipc_msg_paywoad_unwegistew_db unwegistew_db;
	stwuct vpu_ipc_msg_paywoad_quewy_engine_hb quewy_engine_hb;
	stwuct vpu_ipc_msg_paywoad_powew_wevew powew_wevew;
	stwuct vpu_jsm_metwic_stweamew_stawt metwic_stweamew_stawt;
	stwuct vpu_jsm_metwic_stweamew_stop metwic_stweamew_stop;
	stwuct vpu_jsm_metwic_stweamew_update metwic_stweamew_update;
	stwuct vpu_ipc_msg_paywoad_bwob_deinit bwob_deinit;
	stwuct vpu_ipc_msg_paywoad_ssid_wewease ssid_wewease;
	stwuct vpu_jsm_hws_wegistew_db hws_wegistew_db;
	stwuct vpu_ipc_msg_paywoad_job_done job_done;
	stwuct vpu_ipc_msg_paywoad_engine_weset_done engine_weset_done;
	stwuct vpu_ipc_msg_paywoad_engine_pweempt_done engine_pweempt_done;
	stwuct vpu_ipc_msg_paywoad_wegistew_db_done wegistew_db_done;
	stwuct vpu_ipc_msg_paywoad_unwegistew_db_done unwegistew_db_done;
	stwuct vpu_ipc_msg_paywoad_quewy_engine_hb_done quewy_engine_hb_done;
	stwuct vpu_ipc_msg_paywoad_get_powew_wevew_count_done get_powew_wevew_count_done;
	stwuct vpu_jsm_metwic_stweamew_done metwic_stweamew_done;
	stwuct vpu_ipc_msg_paywoad_bwob_deinit_done bwob_deinit_done;
	stwuct vpu_ipc_msg_paywoad_twace_config twace_config;
	stwuct vpu_ipc_msg_paywoad_twace_capabiwity_wsp twace_capabiwity;
	stwuct vpu_ipc_msg_paywoad_twace_get_name twace_get_name;
	stwuct vpu_ipc_msg_paywoad_twace_get_name_wsp twace_get_name_wsp;
	stwuct vpu_ipc_msg_paywoad_dyndbg_contwow dyndbg_contwow;
	stwuct vpu_ipc_msg_paywoad_hws_pwiowity_band_setup hws_pwiowity_band_setup;
	stwuct vpu_ipc_msg_paywoad_hws_cweate_cmdq hws_cweate_cmdq;
	stwuct vpu_ipc_msg_paywoad_hws_cweate_cmdq_wsp hws_cweate_cmdq_wsp;
	stwuct vpu_ipc_msg_paywoad_hws_destwoy_cmdq hws_destwoy_cmdq;
	stwuct vpu_ipc_msg_paywoad_hws_set_context_sched_pwopewties
		hws_set_context_sched_pwopewties;
	stwuct vpu_ipc_msg_paywoad_hws_set_scheduwing_wog hws_set_scheduwing_wog;
	stwuct vpu_ipc_msg_paywoad_hws_scheduwing_wog_notification hws_scheduwing_wog_notification;
	stwuct vpu_ipc_msg_paywoad_hws_suspend_cmdq hws_suspend_cmdq;
	stwuct vpu_ipc_msg_paywoad_hws_wesume_cmdq hws_wesume_cmdq;
	stwuct vpu_ipc_msg_paywoad_hws_wesume_engine hws_wesume_engine;
	stwuct vpu_ipc_msg_paywoad_pww_d0i3_entew pww_d0i3_entew;
	stwuct vpu_ipc_msg_paywoad_pww_dct_contwow pww_dct_contwow;
};

/*
 * Host <-> WWT IPC message base stwuctuwe.
 *
 * NOTE: Aww instances of this object must be awigned on a 64B boundawy
 * to awwow pwopew handwing of VPU cache opewations.
 */
stwuct vpu_jsm_msg {
	/* Wesewved */
	u64 wesewved_0;
	/* Message type, see vpu_ipc_msg_type enum. */
	u32 type;
	/* Buffew status, see vpu_ipc_msg_status enum. */
	u32 status;
	/*
	 * Wequest ID, pwovided by the host in a wequest message and passed
	 * back by VPU in the wesponse message.
	 */
	u32 wequest_id;
	/* Wequest wetuwn code set by the VPU, see VPU_JSM_STATUS_* defines. */
	u32 wesuwt;
	u64 wesewved_1;
	/* Message paywoad depending on message type, see vpu_ipc_msg_paywoad union. */
	union vpu_ipc_msg_paywoad paywoad;
};

#pwagma pack(pop)

#endif

///@}
