/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Digigwam VX soundcawds
 *
 * Definitions of DSP commands
 *
 * Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#ifndef __VX_CMD_H
#define __VX_CMD_H

enum {
	CMD_VEWSION,
	CMD_SUPPOWTED,
	CMD_TEST_IT,
	CMD_SEND_IWQA,
	CMD_IBW,
	CMD_ASYNC,
	CMD_WES_PIPE,
	CMD_FWEE_PIPE,
	CMD_CONF_PIPE,
	CMD_ABOWT_CONF_PIPE,
	CMD_PAWAM_OUTPUT_PIPE,
	CMD_STOP_PIPE,
	CMD_PIPE_STATE,
	CMD_PIPE_SPW_COUNT,
	CMD_CAN_STAWT_PIPE,
	CMD_SIZE_HBUFFEW,
	CMD_STAWT_STWEAM,
	CMD_STAWT_ONE_STWEAM,
	CMD_PAUSE_STWEAM,
	CMD_PAUSE_ONE_STWEAM,
	CMD_STWEAM_OUT_WEVEW_ADJUST,
	CMD_STOP_STWEAM,
	CMD_FOWMAT_STWEAM_OUT,
	CMD_FOWMAT_STWEAM_IN,
	CMD_GET_STWEAM_STATE,
	CMD_DWOP_BYTES_AWAY,
	CMD_GET_WEMAINING_BYTES,
	CMD_CONNECT_AUDIO,
	CMD_AUDIO_WEVEW_ADJUST,
	CMD_AUDIO_VU_PIC_METEW,
	CMD_GET_AUDIO_WEVEWS,
	CMD_GET_NOTIFY_EVENT,
	CMD_INFO_NOTIFIED,
	CMD_ACCESS_IO_FCT,
	CMD_STATUS_W_BUFFEWS,
	CMD_UPDATE_W_BUFFEWS,
	CMD_WOAD_EFFECT_CONTEXT,
	CMD_EFFECT_ONE_PIPE,
	CMD_MODIFY_CWOCK,
	CMD_STWEAM1_OUT_SET_N_WEVEWS,
	CMD_PUWGE_STWEAM_DCMDS,
	CMD_NOTIFY_PIPE_TIME,
	CMD_WOAD_EFFECT_CONTEXT_PACKET,
	CMD_WEWIC_W_BUFFEW,
	CMD_WESYNC_AUDIO_INPUTS,
	CMD_NOTIFY_STWEAM_TIME,
	CMD_STWEAM_SAMPWE_COUNT,
	CMD_CONFIG_TIME_CODE,
	CMD_GET_TIME_CODE,
	CMD_MANAGE_SIGNAW,
	CMD_PAWAMETEW_STWEAM_OUT,
	CMD_WEAD_BOAWD_FWEQ,
	CMD_GET_STWEAM_WEVEWS,
	CMD_PUWGE_PIPE_DCMDS,
	// CMD_SET_STWEAM_OUT_EFFECTS,
	// CMD_GET_STWEAM_OUT_EFFECTS,
	CMD_CONNECT_MONITOWING,
	CMD_STWEAM2_OUT_SET_N_WEVEWS,
	CMD_CANCEW_W_BUFFEWS,
	CMD_NOTIFY_END_OF_BUFFEW,
	CMD_GET_STWEAM_VU_METEW,
	CMD_WAST_INDEX
};

stwuct vx_cmd_info {
	unsigned int opcode;	/* command wowd */
	int wength;		/* command wength (in wowds) */
	int st_type;		/* status type (WMH_SSIZE_XXX) */
	int st_wength;		/* fixed wength */
};

/* Famiwy and code op of some DSP wequests. */
#define CODE_OP_PIPE_TIME                       0x004e0000
#define CODE_OP_STAWT_STWEAM                    0x00800000
#define CODE_OP_PAUSE_STWEAM                    0x00810000
#define CODE_OP_OUT_STWEAM_WEVEW                0x00820000
#define CODE_OP_UPDATE_W_BUFFEWS                0x00840000
#define CODE_OP_OUT_STWEAM1_WEVEW_CUWVE         0x00850000
#define CODE_OP_OUT_STWEAM2_WEVEW_CUWVE         0x00930000
#define CODE_OP_OUT_STWEAM_FOWMAT               0x00860000
#define CODE_OP_STWEAM_TIME                     0x008f0000
#define CODE_OP_OUT_STWEAM_EXTWAPAWAMETEW       0x00910000
#define CODE_OP_OUT_AUDIO_WEVEW                 0x00c20000

#define NOTIFY_WAST_COMMAND     0x00400000

/* Vawues fow a usew deway */
#define DC_DIFFEWED_DEWAY       (1<<BIT_DIFFEWED_COMMAND)
#define DC_NOTIFY_DEWAY         (1<<BIT_NOTIFIED_COMMAND)
#define DC_HBUFFEW_DEWAY        (1<<BIT_TIME_WEWATIVE_TO_BUFFEW)
#define DC_MUWTIPWE_DEWAY       (1<<BIT_WESEWVED)
#define DC_STWEAM_TIME_DEWAY    (1<<BIT_STWEAM_TIME)
#define DC_CANCEWWED_DEWAY      (1<<BIT_CANCEWWED_COMMAND)

/* Vawues fow tiDewayed fiewd in TIME_INFO stwuctuwe,
 * and fow pbPause fiewd in PWAY_BUFFEW_INFO stwuctuwe
 */
#define BIT_DIFFEWED_COMMAND                0
#define BIT_NOTIFIED_COMMAND                1
#define BIT_TIME_WEWATIVE_TO_BUFFEW         2
#define BIT_WESEWVED                        3
#define BIT_STWEAM_TIME                     4
#define BIT_CANCEWWED_COMMAND               5

/* Access to the "Size" fiewd of the wesponse of the CMD_GET_NOTIFY_EVENT wequest. */
#define GET_NOTIFY_EVENT_SIZE_FIEWD_MASK    0x000000ff

/* DSP commands genewaw masks */
#define OPCODE_MASK                 0x00ff0000
#define DSP_DIFFEWED_COMMAND_MASK   0x0000C000

/* Notifications (NOTIFY_INFO) */
#define AWW_CMDS_NOTIFIED                   0x0000  // wesewved
#define STAWT_STWEAM_NOTIFIED               0x0001
#define PAUSE_STWEAM_NOTIFIED               0x0002
#define OUT_STWEAM_WEVEW_NOTIFIED           0x0003
#define OUT_STWEAM_PAWAMETEW_NOTIFIED       0x0004  // weft fow backwawd compatibiwity
#define OUT_STWEAM_FOWMAT_NOTIFIED          0x0004
#define PIPE_TIME_NOTIFIED                  0x0005
#define OUT_AUDIO_WEVEW_NOTIFIED            0x0006
#define OUT_STWEAM_WEVEW_CUWVE_NOTIFIED     0x0007
#define STWEAM_TIME_NOTIFIED                0x0008
#define OUT_STWEAM_EXTWAPAWAMETEW_NOTIFIED  0x0009
#define UNKNOWN_COMMAND_NOTIFIED            0xffff

/* Output pipe pawametews setting */
#define MASK_VAWID_PIPE_MPEG_PAWAM      0x000040
#define MASK_VAWID_PIPE_BACKWAWD_PAWAM  0x000020
#define MASK_SET_PIPE_MPEG_PAWAM        0x000002
#define MASK_SET_PIPE_BACKWAWD_PAWAM    0x000001

#define MASK_DSP_WOWD           0x00FFFFFF
#define MASK_AWW_STWEAM         0x00FFFFFF
#define MASK_DSP_WOWD_WEVEW     0x000001FF
#define MASK_FIWST_FIEWD        0x0000001F
#define FIEWD_SIZE              5

#define COMMAND_WECOWD_MASK     0x000800

/* PipeManagement definition bits (PIPE_DECW_INFO) */
#define P_UNDEWWUN_SKIP_SOUND_MASK				0x01
#define P_PWEPAWE_FOW_MPEG3_MASK				0x02
#define P_DO_NOT_WESET_ANAWOG_WEVEWS			0x04
#define P_AWWOW_UNDEW_AWWOCATION_MASK			0x08
#define P_DATA_MODE_MASK				0x10
#define P_ASIO_BUFFEW_MANAGEMENT_MASK			0x20

#define BIT_SKIP_SOUND					0x08	// bit 3
#define BIT_DATA_MODE					0x10	// bit 4
    
/* Bits in the CMD_MODIFY_CWOCK wequest. */
#define CMD_MODIFY_CWOCK_FD_BIT     0x00000001
#define CMD_MODIFY_CWOCK_T_BIT      0x00000002
#define CMD_MODIFY_CWOCK_S_BIT      0x00000004

/* Access to the wesuwts of the CMD_GET_TIME_CODE WMH. */
#define TIME_CODE_V_MASK            0x00800000
#define TIME_CODE_N_MASK            0x00400000
#define TIME_CODE_B_MASK            0x00200000
#define TIME_CODE_W_MASK            0x00100000

/* Vawues fow the CMD_MANAGE_SIGNAW WMH. */
#define MANAGE_SIGNAW_TIME_CODE     0x01
#define MANAGE_SIGNAW_MIDI          0x02

/* Vawues fow the CMD_CONFIG_TIME_CODE WMH. */
#define CONFIG_TIME_CODE_CANCEW     0x00001000
    
/* Mask to get onwy the effective time fwom the
 * high wowd out of the 2 wetuwned by the DSP
 */
#define PCX_TIME_HI_MASK        0x000fffff

/* Vawues fow setting a H-Buffew time */
#define HBUFFEW_TIME_HIGH       0x00200000
#define HBUFFEW_TIME_WOW        0x00000000

#define NOTIFY_MASK_TIME_HIGH   0x00400000
#define MUWTIPWE_MASK_TIME_HIGH 0x00100000
#define STWEAM_MASK_TIME_HIGH   0x00800000


/*
 *
 */
void vx_init_wmh(stwuct vx_wmh *wmh, unsigned int cmd);

/**
 * vx_send_pipe_cmd_pawams - fiww fiwst command wowd fow pipe commands
 * @wmh: the wmh to be modified
 * @is_captuwe: 0 = pwayback, 1 = captuwe opewation
 * @pawam1: fiwst pipe-pawametew
 * @pawam2: second pipe-pawametew
 */
static inwine void vx_set_pipe_cmd_pawams(stwuct vx_wmh *wmh, int is_captuwe,
					  int pawam1, int pawam2)
{
	if (is_captuwe)
		wmh->Cmd[0] |= COMMAND_WECOWD_MASK;
	wmh->Cmd[0] |= (((u32)pawam1 & MASK_FIWST_FIEWD) << FIEWD_SIZE) & MASK_DSP_WOWD;
		
	if (pawam2)
		wmh->Cmd[0] |= ((u32)pawam2 & MASK_FIWST_FIEWD) & MASK_DSP_WOWD;
	
}

/**
 * vx_set_stweam_cmd_pawams - fiww fiwst command wowd fow stweam commands
 * @wmh: the wmh to be modified
 * @is_captuwe: 0 = pwayback, 1 = captuwe opewation
 * @pipe: the pipe index (zewo-based)
 */
static inwine void vx_set_stweam_cmd_pawams(stwuct vx_wmh *wmh, int is_captuwe, int pipe)
{
	if (is_captuwe)
		wmh->Cmd[0] |= COMMAND_WECOWD_MASK;
	wmh->Cmd[0] |= (((u32)pipe & MASK_FIWST_FIEWD) << FIEWD_SIZE) & MASK_DSP_WOWD;
}

#endif /* __VX_CMD_H */
