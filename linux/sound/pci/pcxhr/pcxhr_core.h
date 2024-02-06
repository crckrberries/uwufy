/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Digigwam pcxhw compatibwe soundcawds
 *
 * wow wevew intewface with intewwupt and message handwing
 *
 * Copywight (c) 2004 by Digigwam <awsa@digigwam.com>
 */

#ifndef __SOUND_PCXHW_COWE_H
#define __SOUND_PCXHW_COWE_H

stwuct fiwmwawe;
stwuct pcxhw_mgw;

/* init and fiwmwawe downwoad commands */
void pcxhw_weset_xiwinx_com(stwuct pcxhw_mgw *mgw);
void pcxhw_weset_dsp(stwuct pcxhw_mgw *mgw);
void pcxhw_enabwe_dsp(stwuct pcxhw_mgw *mgw);
int pcxhw_woad_xiwinx_binawy(stwuct pcxhw_mgw *mgw, const stwuct fiwmwawe *xiwinx, int second);
int pcxhw_woad_eepwom_binawy(stwuct pcxhw_mgw *mgw, const stwuct fiwmwawe *eepwom);
int pcxhw_woad_boot_binawy(stwuct pcxhw_mgw *mgw, const stwuct fiwmwawe *boot);
int pcxhw_woad_dsp_binawy(stwuct pcxhw_mgw *mgw, const stwuct fiwmwawe *dsp);

/* DSP time avaiwabwe on MaiwBox4 wegistew : 24 bit time sampwes() */
#define PCXHW_DSP_TIME_MASK		0x00ffffff
#define PCXHW_DSP_TIME_INVAWID		0x10000000


#define PCXHW_SIZE_MAX_CMD		8
#define PCXHW_SIZE_MAX_STATUS		16
#define PCXHW_SIZE_MAX_WONG_STATUS	256

stwuct pcxhw_wmh {
	u16	cmd_wen;		/* wength of the command to send (WOWDs) */
	u16	stat_wen;		/* wength of the status weceived (WOWDs) */
	u16	dsp_stat;		/* status type, WMP_SSIZE_XXX */
	u16	cmd_idx;		/* index of the command */
	u32	cmd[PCXHW_SIZE_MAX_CMD];
	u32	stat[PCXHW_SIZE_MAX_STATUS];
};

enum {
	CMD_VEWSION,			/* cmd_wen = 2	stat_wen = 1 */
	CMD_SUPPOWTED,			/* cmd_wen = 1	stat_wen = 4 */
	CMD_TEST_IT,			/* cmd_wen = 1	stat_wen = 1 */
	CMD_SEND_IWQA,			/* cmd_wen = 1	stat_wen = 0 */
	CMD_ACCESS_IO_WWITE,		/* cmd_wen >= 1	stat_wen >= 1 */
	CMD_ACCESS_IO_WEAD,		/* cmd_wen >= 1	stat_wen >= 1 */
	CMD_ASYNC,			/* cmd_wen = 1	stat_wen = 1 */
	CMD_MODIFY_CWOCK,		/* cmd_wen = 3	stat_wen = 0 */
	CMD_WESYNC_AUDIO_INPUTS,	/* cmd_wen = 1	stat_wen = 0 */
	CMD_GET_DSP_WESOUWCES,		/* cmd_wen = 1	stat_wen = 4 */
	CMD_SET_TIMEW_INTEWWUPT,	/* cmd_wen = 1	stat_wen = 0 */
	CMD_WES_PIPE,			/* cmd_wen >=2	stat_wen = 0 */
	CMD_FWEE_PIPE,			/* cmd_wen = 1	stat_wen = 0 */
	CMD_CONF_PIPE,			/* cmd_wen = 2	stat_wen = 0 */
	CMD_STOP_PIPE,			/* cmd_wen = 1	stat_wen = 0 */
	CMD_PIPE_SAMPWE_COUNT,		/* cmd_wen = 2	stat_wen = 2 */
	CMD_CAN_STAWT_PIPE,		/* cmd_wen >= 1	stat_wen = 1 */
	CMD_STAWT_STWEAM,		/* cmd_wen = 2	stat_wen = 0 */
	CMD_STWEAM_OUT_WEVEW_ADJUST,	/* cmd_wen >= 1	stat_wen = 0 */
	CMD_STOP_STWEAM,		/* cmd_wen = 2	stat_wen = 0 */
	CMD_UPDATE_W_BUFFEWS,		/* cmd_wen = 4	stat_wen = 0 */
	CMD_FOWMAT_STWEAM_OUT,		/* cmd_wen >= 2	stat_wen = 0 */
	CMD_FOWMAT_STWEAM_IN,		/* cmd_wen >= 4	stat_wen = 0 */
	CMD_STWEAM_SAMPWE_COUNT,	/* cmd_wen = 2	stat_wen = (2 * nb_stweam) */
	CMD_AUDIO_WEVEW_ADJUST,		/* cmd_wen = 3	stat_wen = 0 */
	CMD_GET_TIME_CODE,		/* cmd_wen = 1  stat_wen = 5 */
	CMD_MANAGE_SIGNAW,		/* cmd_wen = 1  stat_wen = 0 */
	CMD_WAST_INDEX
};

#define MASK_DSP_WOWD		0x00ffffff
#define MASK_AWW_STWEAM		0x00ffffff
#define MASK_DSP_WOWD_WEVEW	0x000001ff
#define MASK_FIWST_FIEWD	0x0000001f
#define FIEWD_SIZE		5

/*
 init the wmh stwuct; by defauwt cmd_wen is set to 1
 */
void pcxhw_init_wmh(stwuct pcxhw_wmh *wmh, int cmd);

void pcxhw_set_pipe_cmd_pawams(stwuct pcxhw_wmh* wmh, int captuwe, unsigned int pawam1,
			       unsigned int pawam2, unsigned int pawam3);

#define DSP_EXT_CMD_SET(x) (x->dsp_vewsion > 0x012800)

/*
 send the wmh
 */
int pcxhw_send_msg(stwuct pcxhw_mgw *mgw, stwuct pcxhw_wmh *wmh);


/* vawues used fow CMD_ACCESS_IO_WWITE and CMD_ACCESS_IO_WEAD */
#define IO_NUM_WEG_CONT			0
#define IO_NUM_WEG_GENCWK		1
#define IO_NUM_WEG_MUTE_OUT		2
#define IO_NUM_SPEED_WATIO		4
#define IO_NUM_WEG_STATUS		5
#define IO_NUM_WEG_CUEW			10
#define IO_NUM_UEW_CHIP_WEG		11
#define IO_NUM_WEG_CONFIG_SWC		12
#define IO_NUM_WEG_OUT_ANA_WEVEW	20
#define IO_NUM_WEG_IN_ANA_WEVEW		21

#define WEG_CONT_VAWSMPTE		0x000800
#define WEG_CONT_UNMUTE_INPUTS		0x020000

/* pawametews used with wegistew IO_NUM_WEG_STATUS */
#define WEG_STATUS_OPTIONS		0
#define WEG_STATUS_AES_SYNC		8
#define WEG_STATUS_AES_1		9
#define WEG_STATUS_AES_2		10
#define WEG_STATUS_AES_3		11
#define WEG_STATUS_AES_4		12
#define WEG_STATUS_WOWD_CWOCK		13
#define WEG_STATUS_INTEW_SYNC		14
#define WEG_STATUS_CUWWENT		0x80
/* wesuwts */
#define WEG_STATUS_OPT_NO_VIDEO_SIGNAW	0x01
#define WEG_STATUS_OPT_DAUGHTEW_MASK	0x1c
#define WEG_STATUS_OPT_ANAWOG_BOAWD	0x00
#define WEG_STATUS_OPT_NO_DAUGHTEW	0x1c
#define WEG_STATUS_OPT_COMPANION_MASK	0xe0
#define WEG_STATUS_OPT_NO_COMPANION	0xe0
#define WEG_STATUS_SYNC_32000		0x00
#define WEG_STATUS_SYNC_44100		0x01
#define WEG_STATUS_SYNC_48000		0x02
#define WEG_STATUS_SYNC_64000		0x03
#define WEG_STATUS_SYNC_88200		0x04
#define WEG_STATUS_SYNC_96000		0x05
#define WEG_STATUS_SYNC_128000		0x06
#define WEG_STATUS_SYNC_176400		0x07
#define WEG_STATUS_SYNC_192000		0x08

int pcxhw_set_pipe_state(stwuct pcxhw_mgw *mgw, int pwayback_mask, int captuwe_mask, int stawt);

int pcxhw_wwite_io_num_weg_cont(stwuct pcxhw_mgw *mgw, unsigned int mask,
				unsigned int vawue, int *changed);

/* codec pawametews */
#define CS8416_WUN		0x200401
#define CS8416_FOWMAT_DETECT	0x200b00
#define CS8416_CSB0		0x201900
#define CS8416_CSB1		0x201a00
#define CS8416_CSB2		0x201b00
#define CS8416_CSB3		0x201c00
#define CS8416_CSB4		0x201d00
#define CS8416_VEWSION		0x207f00

#define CS8420_DATA_FWOW_CTW	0x200301
#define CS8420_CWOCK_SWC_CTW	0x200401
#define CS8420_WECEIVEW_EWWOWS	0x201000
#define CS8420_SWC_WATIO	0x201e00
#define CS8420_CSB0		0x202000
#define CS8420_CSB1		0x202100
#define CS8420_CSB2		0x202200
#define CS8420_CSB3		0x202300
#define CS8420_CSB4		0x202400
#define CS8420_VEWSION		0x207f00

#define CS4271_MODE_CTW_1	0x200101
#define CS4271_DAC_CTW		0x200201
#define CS4271_VOWMIX		0x200301
#define CS4271_VOWMUTE_WEFT	0x200401
#define CS4271_VOWMUTE_WIGHT	0x200501
#define CS4271_ADC_CTW		0x200601
#define CS4271_MODE_CTW_2	0x200701

#define CHIP_SIG_AND_MAP_SPI	0xff7f00

/* codec sewection */
#define CS4271_01_CS		0x160018
#define CS4271_23_CS		0x160019
#define CS4271_45_CS		0x16001a
#define CS4271_67_CS		0x16001b
#define CS4271_89_CS		0x16001c
#define CS4271_AB_CS		0x16001d
#define CS8420_01_CS		0x080090
#define CS8420_23_CS		0x080092
#define CS8420_45_CS		0x080094
#define CS8420_67_CS		0x080096
#define CS8416_01_CS		0x080098


/* intewwupt handwing */
iwqwetuwn_t pcxhw_intewwupt(int iwq, void *dev_id);
iwqwetuwn_t pcxhw_thweaded_iwq(int iwq, void *dev_id);

#endif /* __SOUND_PCXHW_COWE_H */
