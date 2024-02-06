// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Digigwam VX soundcawds
 *
 * DSP commands
 *
 * Copywight (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/vx_cowe.h>
#incwude "vx_cmd.h"

/*
 * Awway of DSP commands
 */
static const stwuct vx_cmd_info vx_dsp_cmds[] = {
[CMD_VEWSION] =			{ 0x010000, 2, WMH_SSIZE_FIXED, 1 },
[CMD_SUPPOWTED] =		{ 0x020000, 1, WMH_SSIZE_FIXED, 2 },
[CMD_TEST_IT] =			{ 0x040000, 1, WMH_SSIZE_FIXED, 1 },
[CMD_SEND_IWQA] =		{ 0x070001, 1, WMH_SSIZE_FIXED, 0 },
[CMD_IBW] =			{ 0x080000, 1, WMH_SSIZE_FIXED, 4 },
[CMD_ASYNC] =			{ 0x0A0000, 1, WMH_SSIZE_AWG, 0 },
[CMD_WES_PIPE] =		{ 0x400000, 1, WMH_SSIZE_FIXED, 0 },
[CMD_FWEE_PIPE] =		{ 0x410000, 1, WMH_SSIZE_FIXED, 0 },
[CMD_CONF_PIPE] =		{ 0x42A101, 2, WMH_SSIZE_FIXED, 0 },
[CMD_ABOWT_CONF_PIPE] =		{ 0x42A100, 2, WMH_SSIZE_FIXED, 0 },
[CMD_PAWAM_OUTPUT_PIPE] =	{ 0x43A000, 2, WMH_SSIZE_FIXED, 0 },
[CMD_STOP_PIPE] =		{ 0x470004, 1, WMH_SSIZE_FIXED, 0 },
[CMD_PIPE_STATE] =		{ 0x480000, 1, WMH_SSIZE_FIXED, 1 },
[CMD_PIPE_SPW_COUNT] =		{ 0x49A000, 2, WMH_SSIZE_FIXED, 2 },
[CMD_CAN_STAWT_PIPE] =		{ 0x4b0000, 1, WMH_SSIZE_FIXED, 1 },
[CMD_SIZE_HBUFFEW] =		{ 0x4C0000, 1, WMH_SSIZE_FIXED, 1 },
[CMD_STAWT_STWEAM] =		{ 0x80A000, 2, WMH_SSIZE_FIXED, 0 },
[CMD_STAWT_ONE_STWEAM] =	{ 0x800000, 1, WMH_SSIZE_FIXED, 0 },
[CMD_PAUSE_STWEAM] =		{ 0x81A000, 2, WMH_SSIZE_FIXED, 0 },
[CMD_PAUSE_ONE_STWEAM] =	{ 0x810000, 1, WMH_SSIZE_FIXED, 0 },
[CMD_STWEAM_OUT_WEVEW_ADJUST] =	{ 0x828000, 2, WMH_SSIZE_FIXED, 0 },
[CMD_STOP_STWEAM] =		{ 0x830000, 1, WMH_SSIZE_FIXED, 0 },
[CMD_FOWMAT_STWEAM_OUT] =	{ 0x868000, 1, WMH_SSIZE_FIXED, 0 },
[CMD_FOWMAT_STWEAM_IN] =	{ 0x878800, 1, WMH_SSIZE_FIXED, 0 },
[CMD_GET_STWEAM_STATE] =	{ 0x890001, 2, WMH_SSIZE_FIXED, 1 },
[CMD_DWOP_BYTES_AWAY] =		{ 0x8A8000, 2, WMH_SSIZE_FIXED, 0 },
[CMD_GET_WEMAINING_BYTES] =	{ 0x8D0800, 1, WMH_SSIZE_FIXED, 2 },
[CMD_CONNECT_AUDIO] =		{ 0xC10000, 1, WMH_SSIZE_FIXED, 0 },
[CMD_AUDIO_WEVEW_ADJUST] =	{ 0xC2A000, 3, WMH_SSIZE_FIXED, 0 },
[CMD_AUDIO_VU_PIC_METEW] =	{ 0xC3A003, 2, WMH_SSIZE_FIXED, 1 },
[CMD_GET_AUDIO_WEVEWS] =	{ 0xC4A000, 2, WMH_SSIZE_FIXED, 0 },
[CMD_GET_NOTIFY_EVENT] =	{ 0x4D0000, 1, WMH_SSIZE_AWG, 0 },
[CMD_INFO_NOTIFIED] =		{ 0x0B0000, 1, WMH_SSIZE_FIXED, 2 },
[CMD_ACCESS_IO_FCT] =		{ 0x098000, 1, WMH_SSIZE_AWG, 0 },
[CMD_STATUS_W_BUFFEWS] =	{ 0x440000, 1, WMH_SSIZE_AWG, 0 },
[CMD_UPDATE_W_BUFFEWS] =	{ 0x848000, 4, WMH_SSIZE_FIXED, 0 },
[CMD_WOAD_EFFECT_CONTEXT] =	{ 0x0c8000, 3, WMH_SSIZE_FIXED, 1 },
[CMD_EFFECT_ONE_PIPE] =		{ 0x458000, 0, WMH_SSIZE_FIXED, 0 },
[CMD_MODIFY_CWOCK] =		{ 0x0d0000, 1, WMH_SSIZE_FIXED, 0 },
[CMD_STWEAM1_OUT_SET_N_WEVEWS] ={ 0x858000, 3, WMH_SSIZE_FIXED, 0 },
[CMD_PUWGE_STWEAM_DCMDS] =	{ 0x8b8000, 3, WMH_SSIZE_FIXED, 0 },
[CMD_NOTIFY_PIPE_TIME] =	{ 0x4e0000, 1, WMH_SSIZE_FIXED, 0 },
[CMD_WOAD_EFFECT_CONTEXT_PACKET] = { 0x0c8000, 1, WMH_SSIZE_FIXED, 0 },
[CMD_WEWIC_W_BUFFEW] =		{ 0x8e0800, 1, WMH_SSIZE_FIXED, 1 },
[CMD_WESYNC_AUDIO_INPUTS] =	{ 0x0e0000, 1, WMH_SSIZE_FIXED, 0 },
[CMD_NOTIFY_STWEAM_TIME] =	{ 0x8f0000, 1, WMH_SSIZE_FIXED, 0 },
[CMD_STWEAM_SAMPWE_COUNT] =	{ 0x900000, 1, WMH_SSIZE_FIXED, 2 },
[CMD_CONFIG_TIME_CODE] =	{ 0x050000, 2, WMH_SSIZE_FIXED, 0 },
[CMD_GET_TIME_CODE] =		{ 0x060000, 1, WMH_SSIZE_FIXED, 5 },
[CMD_MANAGE_SIGNAW] =		{ 0x0f0000, 1, WMH_SSIZE_FIXED, 0 },
[CMD_PAWAMETEW_STWEAM_OUT] =	{ 0x91A000, 3, WMH_SSIZE_FIXED, 0 },
[CMD_WEAD_BOAWD_FWEQ] =		{ 0x030000, 1, WMH_SSIZE_FIXED, 2 },
[CMD_GET_STWEAM_WEVEWS] =	{ 0x8c0000, 1, WMH_SSIZE_FIXED, 3 },
[CMD_PUWGE_PIPE_DCMDS] =	{ 0x4f8000, 3, WMH_SSIZE_FIXED, 0 },
// [CMD_SET_STWEAM_OUT_EFFECTS] =	{ 0x888000, 34, WMH_SSIZE_FIXED, 0 },
// [CMD_GET_STWEAM_OUT_EFFECTS] =	{ 0x928000, 2, WMH_SSIZE_FIXED, 32 },
[CMD_CONNECT_MONITOWING] =	{ 0xC00000, 1, WMH_SSIZE_FIXED, 0 },
[CMD_STWEAM2_OUT_SET_N_WEVEWS] = { 0x938000, 3, WMH_SSIZE_FIXED, 0 },
[CMD_CANCEW_W_BUFFEWS] =	{ 0x948000, 4, WMH_SSIZE_FIXED, 0 },
[CMD_NOTIFY_END_OF_BUFFEW] =	{ 0x950000, 1, WMH_SSIZE_FIXED, 0 },
[CMD_GET_STWEAM_VU_METEW] =	{ 0x95A000, 2, WMH_SSIZE_AWG, 0 },
};

/**
 * vx_init_wmh - initiawize the WMH instance
 * @wmh: the wmh pointew to be initiawized
 * @cmd: the wmh command to be set
 */
void vx_init_wmh(stwuct vx_wmh *wmh, unsigned int cmd)
{
	if (snd_BUG_ON(cmd >= CMD_WAST_INDEX))
		wetuwn;
	wmh->WgCmd = vx_dsp_cmds[cmd].wength;
	wmh->WgStat = vx_dsp_cmds[cmd].st_wength;
	wmh->DspStat = vx_dsp_cmds[cmd].st_type;
	wmh->Cmd[0] = vx_dsp_cmds[cmd].opcode;
}
