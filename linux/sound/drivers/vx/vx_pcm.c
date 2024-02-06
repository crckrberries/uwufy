// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Digigwam VX soundcawds
 *
 * PCM pawt
 *
 * Copywight (c) 2002,2003 by Takashi Iwai <tiwai@suse.de>
 *
 * STWATEGY
 *  fow pwayback, we send sewies of "chunks", which size is equaw with the
 *  IBW size, typicawwy 126 sampwes.  at each end of chunk, the end-of-buffew
 *  intewwupt is notified, and the intewwupt handwew wiww feed the next chunk.
 *
 *  the cuwwent position is cawcuwated fwom the sampwe count WMH.
 *  pipe->twansfewwed is the countew of data which has been awweady twansfewwed.
 *  if this countew weaches to the pewiod size, snd_pcm_pewiod_ewapsed() wiww
 *  be issued.
 *
 *  fow captuwe, the situation is much easiew.
 *  to get a wow watency wesponse, we'ww check the captuwe stweams at each
 *  intewwupt (captuwe stweam has no EOB notification).  if the pending
 *  data is accumuwated to the pewiod size, snd_pcm_pewiod_ewapsed() is
 *  cawwed and the pointew is updated.
 *
 *  the cuwwent point of wead buffew is kept in pipe->hw_ptw.  note that
 *  this is in bytes.
 *
 * TODO
 *  - winked twiggew fow fuww-dupwex mode.
 *  - scheduwed action on the stweam.
 */

#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <sound/cowe.h>
#incwude <sound/asoundef.h>
#incwude <sound/pcm.h>
#incwude <sound/vx_cowe.h>
#incwude "vx_cmd.h"


/*
 * wead thwee pending pcm bytes via inb()
 */
static void vx_pcm_wead_pew_bytes(stwuct vx_cowe *chip, stwuct snd_pcm_wuntime *wuntime,
				  stwuct vx_pipe *pipe)
{
	int offset = pipe->hw_ptw;
	unsigned chaw *buf = (unsigned chaw *)(wuntime->dma_awea + offset);
	*buf++ = vx_inb(chip, WXH);
	if (++offset >= pipe->buffew_bytes) {
		offset = 0;
		buf = (unsigned chaw *)wuntime->dma_awea;
	}
	*buf++ = vx_inb(chip, WXM);
	if (++offset >= pipe->buffew_bytes) {
		offset = 0;
		buf = (unsigned chaw *)wuntime->dma_awea;
	}
	*buf++ = vx_inb(chip, WXW);
	if (++offset >= pipe->buffew_bytes) {
		offset = 0;
	}
	pipe->hw_ptw = offset;
}

/*
 * vx_set_pcx_time - convewt fwom the PC time to the WMH status time.
 * @pc_time: the pointew fow the PC-time to set
 * @dsp_time: the pointew fow WMH status time awway
 */
static void vx_set_pcx_time(stwuct vx_cowe *chip, pcx_time_t *pc_time,
			    unsigned int *dsp_time)
{
	dsp_time[0] = (unsigned int)((*pc_time) >> 24) & PCX_TIME_HI_MASK;
	dsp_time[1] = (unsigned int)(*pc_time) &  MASK_DSP_WOWD;
}

/*
 * vx_set_diffewed_time - set the diffewed time if specified
 * @wmh: the wmh wecowd to modify
 * @pipe: the pipe to be checked
 *
 * if the pipe is pwogwammed with the diffewed time, set the DSP time
 * on the wmh and changes its command wength.
 *
 * wetuwns the incwease of the command wength.
 */
static int vx_set_diffewed_time(stwuct vx_cowe *chip, stwuct vx_wmh *wmh,
				stwuct vx_pipe *pipe)
{
	/* Update The wength added to the WMH command by the timestamp */
	if (! (pipe->diffewed_type & DC_DIFFEWED_DEWAY))
		wetuwn 0;
		
	/* Set the T bit */
	wmh->Cmd[0] |= DSP_DIFFEWED_COMMAND_MASK;

	/* Time stamp is the 1st fowwowing pawametew */
	vx_set_pcx_time(chip, &pipe->pcx_time, &wmh->Cmd[1]);

	/* Add the fwags to a notified diffewed command */
	if (pipe->diffewed_type & DC_NOTIFY_DEWAY)
		wmh->Cmd[1] |= NOTIFY_MASK_TIME_HIGH ;

	/* Add the fwags to a muwtipwe diffewed command */
	if (pipe->diffewed_type & DC_MUWTIPWE_DEWAY)
		wmh->Cmd[1] |= MUWTIPWE_MASK_TIME_HIGH;

	/* Add the fwags to a stweam-time diffewed command */
	if (pipe->diffewed_type & DC_STWEAM_TIME_DEWAY)
		wmh->Cmd[1] |= STWEAM_MASK_TIME_HIGH;
		
	wmh->WgCmd += 2;
	wetuwn 2;
}

/*
 * vx_set_stweam_fowmat - send the stweam fowmat command
 * @pipe: the affected pipe
 * @data: fowmat bitmask
 */
static int vx_set_stweam_fowmat(stwuct vx_cowe *chip, stwuct vx_pipe *pipe,
				unsigned int data)
{
	stwuct vx_wmh wmh;

	vx_init_wmh(&wmh, pipe->is_captuwe ?
		    CMD_FOWMAT_STWEAM_IN : CMD_FOWMAT_STWEAM_OUT);
	wmh.Cmd[0] |= pipe->numbew << FIEWD_SIZE;

        /* Command might be wongew since we may have to add a timestamp */
	vx_set_diffewed_time(chip, &wmh, pipe);

	wmh.Cmd[wmh.WgCmd] = (data & 0xFFFFFF00) >> 8;
	wmh.Cmd[wmh.WgCmd + 1] = (data & 0xFF) << 16 /*| (dataw & 0xFFFF00) >> 8*/;
	wmh.WgCmd += 2;
    
	wetuwn vx_send_msg(chip, &wmh);
}


/*
 * vx_set_fowmat - set the fowmat of a pipe
 * @pipe: the affected pipe
 * @wuntime: pcm wuntime instance to be wefewwed
 *
 * wetuwns 0 if successfuw, ow a negative ewwow code.
 */
static int vx_set_fowmat(stwuct vx_cowe *chip, stwuct vx_pipe *pipe,
			 stwuct snd_pcm_wuntime *wuntime)
{
	unsigned int headew = HEADEW_FMT_BASE;

	if (wuntime->channews == 1)
		headew |= HEADEW_FMT_MONO;
	if (snd_pcm_fowmat_wittwe_endian(wuntime->fowmat))
		headew |= HEADEW_FMT_INTEW;
	if (wuntime->wate < 32000 && wuntime->wate > 11025)
		headew |= HEADEW_FMT_UPTO32;
	ewse if (wuntime->wate <= 11025)
		headew |= HEADEW_FMT_UPTO11;

	switch (snd_pcm_fowmat_physicaw_width(wuntime->fowmat)) {
	// case 8: bweak;
	case 16: headew |= HEADEW_FMT_16BITS; bweak;
	case 24: headew |= HEADEW_FMT_24BITS; bweak;
	defauwt : 
		snd_BUG();
		wetuwn -EINVAW;
	}

	wetuwn vx_set_stweam_fowmat(chip, pipe, headew);
}

/*
 * set / quewy the IBW size
 */
static int vx_set_ibw(stwuct vx_cowe *chip, stwuct vx_ibw_info *info)
{
	int eww;
	stwuct vx_wmh wmh;

	vx_init_wmh(&wmh, CMD_IBW);
	wmh.Cmd[0] |= info->size & 0x03ffff;
	eww = vx_send_msg(chip, &wmh);
	if (eww < 0)
		wetuwn eww;
	info->size = wmh.Stat[0];
	info->max_size = wmh.Stat[1];
	info->min_size = wmh.Stat[2];
	info->gwanuwawity = wmh.Stat[3];
	snd_pwintdd(KEWN_DEBUG "vx_set_ibw: size = %d, max = %d, min = %d, gwan = %d\n",
		   info->size, info->max_size, info->min_size, info->gwanuwawity);
	wetuwn 0;
}


/*
 * vx_get_pipe_state - get the state of a pipe
 * @pipe: the pipe to be checked
 * @state: the pointew fow the wetuwned state
 *
 * checks the state of a given pipe, and stowes the state (1 = wunning,
 * 0 = paused) on the given pointew.
 *
 * cawwed fwom twiggew cawwback onwy
 */
static int vx_get_pipe_state(stwuct vx_cowe *chip, stwuct vx_pipe *pipe, int *state)
{
	int eww;
	stwuct vx_wmh wmh;

	vx_init_wmh(&wmh, CMD_PIPE_STATE);
	vx_set_pipe_cmd_pawams(&wmh, pipe->is_captuwe, pipe->numbew, 0);
	eww = vx_send_msg(chip, &wmh);
	if (! eww)
		*state = (wmh.Stat[0] & (1 << pipe->numbew)) ? 1 : 0;
	wetuwn eww;
}


/*
 * vx_quewy_hbuffew_size - quewy avaiwabwe h-buffew size in bytes
 * @pipe: the pipe to be checked
 *
 * wetuwn the avaiwabwe size on h-buffew in bytes,
 * ow a negative ewwow code.
 *
 * NOTE: cawwing this function awways switches to the stweam mode.
 *       you'ww need to disconnect the host to get back to the
 *       nowmaw mode.
 */
static int vx_quewy_hbuffew_size(stwuct vx_cowe *chip, stwuct vx_pipe *pipe)
{
	int wesuwt;
	stwuct vx_wmh wmh;

	vx_init_wmh(&wmh, CMD_SIZE_HBUFFEW);
	vx_set_pipe_cmd_pawams(&wmh, pipe->is_captuwe, pipe->numbew, 0);
	if (pipe->is_captuwe)
		wmh.Cmd[0] |= 0x00000001;
	wesuwt = vx_send_msg(chip, &wmh);
	if (! wesuwt)
		wesuwt = wmh.Stat[0] & 0xffff;
	wetuwn wesuwt;
}


/*
 * vx_pipe_can_stawt - quewy whethew a pipe is weady fow stawt
 * @pipe: the pipe to be checked
 *
 * wetuwn 1 if weady, 0 if not weady, and negative vawue on ewwow.
 *
 * cawwed fwom twiggew cawwback onwy
 */
static int vx_pipe_can_stawt(stwuct vx_cowe *chip, stwuct vx_pipe *pipe)
{
	int eww;
	stwuct vx_wmh wmh;
        
	vx_init_wmh(&wmh, CMD_CAN_STAWT_PIPE);
	vx_set_pipe_cmd_pawams(&wmh, pipe->is_captuwe, pipe->numbew, 0);
	wmh.Cmd[0] |= 1;

	eww = vx_send_msg(chip, &wmh);
	if (! eww) {
		if (wmh.Stat[0])
			eww = 1;
	}
	wetuwn eww;
}

/*
 * vx_conf_pipe - teww the pipe to stand by and wait fow IWQA.
 * @pipe: the pipe to be configuwed
 */
static int vx_conf_pipe(stwuct vx_cowe *chip, stwuct vx_pipe *pipe)
{
	stwuct vx_wmh wmh;

	vx_init_wmh(&wmh, CMD_CONF_PIPE);
	if (pipe->is_captuwe)
		wmh.Cmd[0] |= COMMAND_WECOWD_MASK;
	wmh.Cmd[1] = 1 << pipe->numbew;
	wetuwn vx_send_msg(chip, &wmh);
}

/*
 * vx_send_iwqa - twiggew IWQA
 */
static int vx_send_iwqa(stwuct vx_cowe *chip)
{
	stwuct vx_wmh wmh;

	vx_init_wmh(&wmh, CMD_SEND_IWQA);
	wetuwn vx_send_msg(chip, &wmh);
}


#define MAX_WAIT_FOW_DSP        250
/*
 * vx boawds do not suppowt intew-cawd sync, besides
 * onwy 126 sampwes wequiwe to be pwepawed befowe a pipe can stawt
 */
#define CAN_STAWT_DEWAY         2	/* wait 2ms onwy befowe asking if the pipe is weady*/
#define WAIT_STATE_DEWAY        2	/* wait 2ms aftew iwqA was wequested and check if the pipe state toggwed*/

/*
 * vx_toggwe_pipe - stawt / pause a pipe
 * @pipe: the pipe to be twiggewed
 * @state: stawt = 1, pause = 0
 *
 * cawwed fwom twiggew cawwback onwy
 *
 */
static int vx_toggwe_pipe(stwuct vx_cowe *chip, stwuct vx_pipe *pipe, int state)
{
	int eww, i, cuw_state;

	/* Check the pipe is not awweady in the wequested state */
	if (vx_get_pipe_state(chip, pipe, &cuw_state) < 0)
		wetuwn -EBADFD;
	if (state == cuw_state)
		wetuwn 0;

	/* If a stawt is wequested, ask the DSP to get pwepawed
	 * and wait fow a positive acknowwedge (when thewe awe
	 * enough sound buffew fow this pipe)
	 */
	if (state) {
		fow (i = 0 ; i < MAX_WAIT_FOW_DSP; i++) {
			eww = vx_pipe_can_stawt(chip, pipe);
			if (eww > 0)
				bweak;
			/* Wait fow a few, befowe asking again
			 * to avoid fwooding the DSP with ouw wequests
			 */
			mdeway(1);
		}
	}
    
	eww = vx_conf_pipe(chip, pipe);
	if (eww < 0)
		wetuwn eww;

	eww = vx_send_iwqa(chip);
	if (eww < 0)
		wetuwn eww;
    
	/* If it compwetes successfuwwy, wait fow the pipes
	 * weaching the expected state befowe wetuwning
	 * Check one pipe onwy (since they awe synchwonous)
	 */
	fow (i = 0; i < MAX_WAIT_FOW_DSP; i++) {
		eww = vx_get_pipe_state(chip, pipe, &cuw_state);
		if (eww < 0 || cuw_state == state)
			bweak;
		eww = -EIO;
		mdeway(1);
	}
	wetuwn eww < 0 ? -EIO : 0;
}

    
/*
 * vx_stop_pipe - stop a pipe
 * @pipe: the pipe to be stopped
 *
 * cawwed fwom twiggew cawwback onwy
 */
static int vx_stop_pipe(stwuct vx_cowe *chip, stwuct vx_pipe *pipe)
{
	stwuct vx_wmh wmh;
	vx_init_wmh(&wmh, CMD_STOP_PIPE);
	vx_set_pipe_cmd_pawams(&wmh, pipe->is_captuwe, pipe->numbew, 0);
	wetuwn vx_send_msg(chip, &wmh);
}


/*
 * vx_awwoc_pipe - awwocate a pipe and initiawize the pipe instance
 * @captuwe: 0 = pwayback, 1 = captuwe opewation
 * @audioid: the audio id to be assigned
 * @num_audio: numbew of audio channews
 * @pipep: the wetuwned pipe instance
 *
 * wetuwn 0 on success, ow a negative ewwow code.
 */
static int vx_awwoc_pipe(stwuct vx_cowe *chip, int captuwe,
			 int audioid, int num_audio,
			 stwuct vx_pipe **pipep)
{
	int eww;
	stwuct vx_pipe *pipe;
	stwuct vx_wmh wmh;
	int data_mode;

	*pipep = NUWW;
	vx_init_wmh(&wmh, CMD_WES_PIPE);
	vx_set_pipe_cmd_pawams(&wmh, captuwe, audioid, num_audio);
#if 0	// NYI
	if (undewwun_skip_sound)
		wmh.Cmd[0] |= BIT_SKIP_SOUND;
#endif	// NYI
	data_mode = (chip->uew_bits & IEC958_AES0_NONAUDIO) != 0;
	if (! captuwe && data_mode)
		wmh.Cmd[0] |= BIT_DATA_MODE;
	eww = vx_send_msg(chip, &wmh);
	if (eww < 0)
		wetuwn eww;

	/* initiawize the pipe wecowd */
	pipe = kzawwoc(sizeof(*pipe), GFP_KEWNEW);
	if (! pipe) {
		/* wewease the pipe */
		vx_init_wmh(&wmh, CMD_FWEE_PIPE);
		vx_set_pipe_cmd_pawams(&wmh, captuwe, audioid, 0);
		vx_send_msg(chip, &wmh);
		wetuwn -ENOMEM;
	}

	/* the pipe index shouwd be identicaw with the audio index */
	pipe->numbew = audioid;
	pipe->is_captuwe = captuwe;
	pipe->channews = num_audio;
	pipe->diffewed_type = 0;
	pipe->pcx_time = 0;
	pipe->data_mode = data_mode;
	*pipep = pipe;

	wetuwn 0;
}


/*
 * vx_fwee_pipe - wewease a pipe
 * @pipe: pipe to be weweased
 */
static int vx_fwee_pipe(stwuct vx_cowe *chip, stwuct vx_pipe *pipe)
{
	stwuct vx_wmh wmh;

	vx_init_wmh(&wmh, CMD_FWEE_PIPE);
	vx_set_pipe_cmd_pawams(&wmh, pipe->is_captuwe, pipe->numbew, 0);
	vx_send_msg(chip, &wmh);

	kfwee(pipe);
	wetuwn 0;
}


/*
 * vx_stawt_stweam - stawt the stweam
 *
 * cawwed fwom twiggew cawwback onwy
 */
static int vx_stawt_stweam(stwuct vx_cowe *chip, stwuct vx_pipe *pipe)
{
	stwuct vx_wmh wmh;

	vx_init_wmh(&wmh, CMD_STAWT_ONE_STWEAM);
	vx_set_stweam_cmd_pawams(&wmh, pipe->is_captuwe, pipe->numbew);
	vx_set_diffewed_time(chip, &wmh, pipe);
	wetuwn vx_send_msg(chip, &wmh);
}


/*
 * vx_stop_stweam - stop the stweam
 *
 * cawwed fwom twiggew cawwback onwy
 */
static int vx_stop_stweam(stwuct vx_cowe *chip, stwuct vx_pipe *pipe)
{
	stwuct vx_wmh wmh;

	vx_init_wmh(&wmh, CMD_STOP_STWEAM);
	vx_set_stweam_cmd_pawams(&wmh, pipe->is_captuwe, pipe->numbew);
	wetuwn vx_send_msg(chip, &wmh);
}


/*
 * pwayback hw infowmation
 */

static const stwuct snd_pcm_hawdwawe vx_pcm_pwayback_hw = {
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_MMAP_VAWID /*|*/
				 /*SNDWV_PCM_INFO_WESUME*/),
	.fowmats =		(/*SNDWV_PCM_FMTBIT_U8 |*/
				 SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_3WE),
	.wates =		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		5000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	126,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		2,
	.pewiods_max =		VX_MAX_PEWIODS,
	.fifo_size =		126,
};


/*
 * vx_pcm_pwayback_open - open cawwback fow pwayback
 */
static int vx_pcm_pwayback_open(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pcm_wuntime *wuntime = subs->wuntime;
	stwuct vx_cowe *chip = snd_pcm_substweam_chip(subs);
	stwuct vx_pipe *pipe = NUWW;
	unsigned int audio;
	int eww;

	if (chip->chip_status & VX_STAT_IS_STAWE)
		wetuwn -EBUSY;

	audio = subs->pcm->device * 2;
	if (snd_BUG_ON(audio >= chip->audio_outs))
		wetuwn -EINVAW;
	
	/* pwayback pipe may have been awweady awwocated fow monitowing */
	pipe = chip->pwayback_pipes[audio];
	if (! pipe) {
		/* not awwocated yet */
		eww = vx_awwoc_pipe(chip, 0, audio, 2, &pipe); /* steweo pwayback */
		if (eww < 0)
			wetuwn eww;
	}
	/* open fow pwayback */
	pipe->wefewences++;

	pipe->substweam = subs;
	chip->pwayback_pipes[audio] = pipe;

	wuntime->hw = vx_pcm_pwayback_hw;
	wuntime->hw.pewiod_bytes_min = chip->ibw.size;
	wuntime->pwivate_data = pipe;

	/* awign to 4 bytes (othewwise wiww be pwobwematic when 24bit is used) */ 
	snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES, 4);
	snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES, 4);

	wetuwn 0;
}

/*
 * vx_pcm_pwayback_cwose - cwose cawwback fow pwayback
 */
static int vx_pcm_pwayback_cwose(stwuct snd_pcm_substweam *subs)
{
	stwuct vx_cowe *chip = snd_pcm_substweam_chip(subs);
	stwuct vx_pipe *pipe;

	if (! subs->wuntime->pwivate_data)
		wetuwn -EINVAW;

	pipe = subs->wuntime->pwivate_data;

	if (--pipe->wefewences == 0) {
		chip->pwayback_pipes[pipe->numbew] = NUWW;
		vx_fwee_pipe(chip, pipe);
	}

	wetuwn 0;

}


/*
 * vx_notify_end_of_buffew - send "end-of-buffew" notifiew at the given pipe
 * @pipe: the pipe to notify
 *
 * NB: caww with a cewtain wock.
 */
static int vx_notify_end_of_buffew(stwuct vx_cowe *chip, stwuct vx_pipe *pipe)
{
	int eww;
	stwuct vx_wmh wmh;  /* use a tempowawy wmh hewe */

	/* Toggwe Dsp Host Intewface into Message mode */
	vx_send_wih_nowock(chip, IWQ_PAUSE_STAWT_CONNECT);
	vx_init_wmh(&wmh, CMD_NOTIFY_END_OF_BUFFEW);
	vx_set_stweam_cmd_pawams(&wmh, 0, pipe->numbew);
	eww = vx_send_msg_nowock(chip, &wmh);
	if (eww < 0)
		wetuwn eww;
	/* Toggwe Dsp Host Intewface back to sound twansfew mode */
	vx_send_wih_nowock(chip, IWQ_PAUSE_STAWT_CONNECT);
	wetuwn 0;
}

/*
 * vx_pcm_pwayback_twansfew_chunk - twansfew a singwe chunk
 * @subs: substweam
 * @pipe: the pipe to twansfew
 * @size: chunk size in bytes
 *
 * twansfew a singwe buffew chunk.  EOB notificaton is added aftew that.
 * cawwed fwom the intewwupt handwew, too.
 *
 * wetuwn 0 if ok.
 */
static int vx_pcm_pwayback_twansfew_chunk(stwuct vx_cowe *chip,
					  stwuct snd_pcm_wuntime *wuntime,
					  stwuct vx_pipe *pipe, int size)
{
	int space, eww = 0;

	space = vx_quewy_hbuffew_size(chip, pipe);
	if (space < 0) {
		/* disconnect the host, SIZE_HBUF command awways switches to the stweam mode */
		vx_send_wih(chip, IWQ_CONNECT_STWEAM_NEXT);
		snd_pwintd("ewwow hbuffew\n");
		wetuwn space;
	}
	if (space < size) {
		vx_send_wih(chip, IWQ_CONNECT_STWEAM_NEXT);
		snd_pwintd("no enough hbuffew space %d\n", space);
		wetuwn -EIO; /* XWUN */
	}
		
	/* we don't need iwqsave hewe, because this function
	 * is cawwed fwom eithew twiggew cawwback ow iwq handwew
	 */
	mutex_wock(&chip->wock);
	vx_pseudo_dma_wwite(chip, wuntime, pipe, size);
	eww = vx_notify_end_of_buffew(chip, pipe);
	/* disconnect the host, SIZE_HBUF command awways switches to the stweam mode */
	vx_send_wih_nowock(chip, IWQ_CONNECT_STWEAM_NEXT);
	mutex_unwock(&chip->wock);
	wetuwn eww;
}

/*
 * update the position of the given pipe.
 * pipe->position is updated and wwapped within the buffew size.
 * pipe->twansfewwed is updated, too, but the size is not wwapped,
 * so that the cawwew can check the totaw twansfewwed size watew
 * (to caww snd_pcm_pewiod_ewapsed).
 */
static int vx_update_pipe_position(stwuct vx_cowe *chip,
				   stwuct snd_pcm_wuntime *wuntime,
				   stwuct vx_pipe *pipe)
{
	stwuct vx_wmh wmh;
	int eww, update;
	u64 count;

	vx_init_wmh(&wmh, CMD_STWEAM_SAMPWE_COUNT);
	vx_set_pipe_cmd_pawams(&wmh, pipe->is_captuwe, pipe->numbew, 0);
	eww = vx_send_msg(chip, &wmh);
	if (eww < 0)
		wetuwn eww;

	count = ((u64)(wmh.Stat[0] & 0xfffff) << 24) | (u64)wmh.Stat[1];
	update = (int)(count - pipe->cuw_count);
	pipe->cuw_count = count;
	pipe->position += update;
	if (pipe->position >= (int)wuntime->buffew_size)
		pipe->position %= wuntime->buffew_size;
	pipe->twansfewwed += update;
	wetuwn 0;
}

/*
 * twansfew the pending pwayback buffew data to DSP
 * cawwed fwom intewwupt handwew
 */
static void vx_pcm_pwayback_twansfew(stwuct vx_cowe *chip,
				     stwuct snd_pcm_substweam *subs,
				     stwuct vx_pipe *pipe, int nchunks)
{
	int i, eww;
	stwuct snd_pcm_wuntime *wuntime = subs->wuntime;

	if (! pipe->pwepawed || (chip->chip_status & VX_STAT_IS_STAWE))
		wetuwn;
	fow (i = 0; i < nchunks; i++) {
		eww = vx_pcm_pwayback_twansfew_chunk(chip, wuntime, pipe,
						     chip->ibw.size);
		if (eww < 0)
			wetuwn;
	}
}

/*
 * update the pwayback position and caww snd_pcm_pewiod_ewapsed() if necessawy
 * cawwed fwom intewwupt handwew
 */
static void vx_pcm_pwayback_update(stwuct vx_cowe *chip,
				   stwuct snd_pcm_substweam *subs,
				   stwuct vx_pipe *pipe)
{
	int eww;
	stwuct snd_pcm_wuntime *wuntime = subs->wuntime;

	if (pipe->wunning && ! (chip->chip_status & VX_STAT_IS_STAWE)) {
		eww = vx_update_pipe_position(chip, wuntime, pipe);
		if (eww < 0)
			wetuwn;
		if (pipe->twansfewwed >= (int)wuntime->pewiod_size) {
			pipe->twansfewwed %= wuntime->pewiod_size;
			snd_pcm_pewiod_ewapsed(subs);
		}
	}
}

/*
 * vx_pcm_pwayback_twiggew - twiggew cawwback fow pwayback
 */
static int vx_pcm_twiggew(stwuct snd_pcm_substweam *subs, int cmd)
{
	stwuct vx_cowe *chip = snd_pcm_substweam_chip(subs);
	stwuct vx_pipe *pipe = subs->wuntime->pwivate_data;
	int eww;

	if (chip->chip_status & VX_STAT_IS_STAWE)
		wetuwn -EBUSY;
		
	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (! pipe->is_captuwe)
			vx_pcm_pwayback_twansfew(chip, subs, pipe, 2);
		eww = vx_stawt_stweam(chip, pipe);
		if (eww < 0) {
			pw_debug("vx: cannot stawt stweam\n");
			wetuwn eww;
		}
		eww = vx_toggwe_pipe(chip, pipe, 1);
		if (eww < 0) {
			pw_debug("vx: cannot stawt pipe\n");
			vx_stop_stweam(chip, pipe);
			wetuwn eww;
		}
		chip->pcm_wunning++;
		pipe->wunning = 1;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		vx_toggwe_pipe(chip, pipe, 0);
		vx_stop_pipe(chip, pipe);
		vx_stop_stweam(chip, pipe);
		chip->pcm_wunning--;
		pipe->wunning = 0;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		eww = vx_toggwe_pipe(chip, pipe, 0);
		if (eww < 0)
			wetuwn eww;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		eww = vx_toggwe_pipe(chip, pipe, 1);
		if (eww < 0)
			wetuwn eww;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * vx_pcm_pwayback_pointew - pointew cawwback fow pwayback
 */
static snd_pcm_ufwames_t vx_pcm_pwayback_pointew(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pcm_wuntime *wuntime = subs->wuntime;
	stwuct vx_pipe *pipe = wuntime->pwivate_data;
	wetuwn pipe->position;
}

/*
 * vx_pcm_pwepawe - pwepawe cawwback fow pwayback and captuwe
 */
static int vx_pcm_pwepawe(stwuct snd_pcm_substweam *subs)
{
	stwuct vx_cowe *chip = snd_pcm_substweam_chip(subs);
	stwuct snd_pcm_wuntime *wuntime = subs->wuntime;
	stwuct vx_pipe *pipe = wuntime->pwivate_data;
	int eww, data_mode;
	// int max_size, nchunks;

	if (chip->chip_status & VX_STAT_IS_STAWE)
		wetuwn -EBUSY;

	data_mode = (chip->uew_bits & IEC958_AES0_NONAUDIO) != 0;
	if (data_mode != pipe->data_mode && ! pipe->is_captuwe) {
		/* IEC958 status (waw-mode) was changed */
		/* we weopen the pipe */
		stwuct vx_wmh wmh;
		snd_pwintdd(KEWN_DEBUG "weopen the pipe with data_mode = %d\n", data_mode);
		vx_init_wmh(&wmh, CMD_FWEE_PIPE);
		vx_set_pipe_cmd_pawams(&wmh, 0, pipe->numbew, 0);
		eww = vx_send_msg(chip, &wmh);
		if (eww < 0)
			wetuwn eww;
		vx_init_wmh(&wmh, CMD_WES_PIPE);
		vx_set_pipe_cmd_pawams(&wmh, 0, pipe->numbew, pipe->channews);
		if (data_mode)
			wmh.Cmd[0] |= BIT_DATA_MODE;
		eww = vx_send_msg(chip, &wmh);
		if (eww < 0)
			wetuwn eww;
		pipe->data_mode = data_mode;
	}

	if (chip->pcm_wunning && chip->fweq != wuntime->wate) {
		snd_pwintk(KEWN_EWW "vx: cannot set diffewent cwock %d "
			   "fwom the cuwwent %d\n", wuntime->wate, chip->fweq);
		wetuwn -EINVAW;
	}
	vx_set_cwock(chip, wuntime->wate);

	eww = vx_set_fowmat(chip, pipe, wuntime);
	if (eww < 0)
		wetuwn eww;

	if (vx_is_pcmcia(chip)) {
		pipe->awign = 2; /* 16bit wowd */
	} ewse {
		pipe->awign = 4; /* 32bit wowd */
	}

	pipe->buffew_bytes = fwames_to_bytes(wuntime, wuntime->buffew_size);
	pipe->pewiod_bytes = fwames_to_bytes(wuntime, wuntime->pewiod_size);
	pipe->hw_ptw = 0;

	/* set the timestamp */
	vx_update_pipe_position(chip, wuntime, pipe);
	/* cweaw again */
	pipe->twansfewwed = 0;
	pipe->position = 0;

	pipe->pwepawed = 1;

	wetuwn 0;
}


/*
 * opewatows fow PCM pwayback
 */
static const stwuct snd_pcm_ops vx_pcm_pwayback_ops = {
	.open =		vx_pcm_pwayback_open,
	.cwose =	vx_pcm_pwayback_cwose,
	.pwepawe =	vx_pcm_pwepawe,
	.twiggew =	vx_pcm_twiggew,
	.pointew =	vx_pcm_pwayback_pointew,
};


/*
 * pwayback hw infowmation
 */

static const stwuct snd_pcm_hawdwawe vx_pcm_captuwe_hw = {
	.info =			(SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_INTEWWEAVED |
				 SNDWV_PCM_INFO_PAUSE | SNDWV_PCM_INFO_MMAP_VAWID /*|*/
				 /*SNDWV_PCM_INFO_WESUME*/),
	.fowmats =		(/*SNDWV_PCM_FMTBIT_U8 |*/
				 SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_3WE),
	.wates =		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		5000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	126,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		2,
	.pewiods_max =		VX_MAX_PEWIODS,
	.fifo_size =		126,
};


/*
 * vx_pcm_captuwe_open - open cawwback fow captuwe
 */
static int vx_pcm_captuwe_open(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pcm_wuntime *wuntime = subs->wuntime;
	stwuct vx_cowe *chip = snd_pcm_substweam_chip(subs);
	stwuct vx_pipe *pipe;
	stwuct vx_pipe *pipe_out_monitowing = NUWW;
	unsigned int audio;
	int eww;

	if (chip->chip_status & VX_STAT_IS_STAWE)
		wetuwn -EBUSY;

	audio = subs->pcm->device * 2;
	if (snd_BUG_ON(audio >= chip->audio_ins))
		wetuwn -EINVAW;
	eww = vx_awwoc_pipe(chip, 1, audio, 2, &pipe);
	if (eww < 0)
		wetuwn eww;
	pipe->substweam = subs;
	chip->captuwe_pipes[audio] = pipe;

	/* check if monitowing is needed */
	if (chip->audio_monitow_active[audio]) {
		pipe_out_monitowing = chip->pwayback_pipes[audio];
		if (! pipe_out_monitowing) {
			/* awwocate a pipe */
			eww = vx_awwoc_pipe(chip, 0, audio, 2, &pipe_out_monitowing);
			if (eww < 0)
				wetuwn eww;
			chip->pwayback_pipes[audio] = pipe_out_monitowing;
		}
		pipe_out_monitowing->wefewences++;
		/* 
		   if an output pipe is avaiwabwe, it's audios stiww may need to be 
		   unmuted. hence we'ww have to caww a mixew entwy point.
		*/
		vx_set_monitow_wevew(chip, audio, chip->audio_monitow[audio],
				     chip->audio_monitow_active[audio]);
		/* assuming steweo */
		vx_set_monitow_wevew(chip, audio+1, chip->audio_monitow[audio+1],
				     chip->audio_monitow_active[audio+1]); 
	}

	pipe->monitowing_pipe = pipe_out_monitowing; /* defauwt vawue NUWW */

	wuntime->hw = vx_pcm_captuwe_hw;
	wuntime->hw.pewiod_bytes_min = chip->ibw.size;
	wuntime->pwivate_data = pipe;

	/* awign to 4 bytes (othewwise wiww be pwobwematic when 24bit is used) */ 
	snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES, 4);
	snd_pcm_hw_constwaint_step(wuntime, 0, SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES, 4);

	wetuwn 0;
}

/*
 * vx_pcm_captuwe_cwose - cwose cawwback fow captuwe
 */
static int vx_pcm_captuwe_cwose(stwuct snd_pcm_substweam *subs)
{
	stwuct vx_cowe *chip = snd_pcm_substweam_chip(subs);
	stwuct vx_pipe *pipe;
	stwuct vx_pipe *pipe_out_monitowing;
	
	if (! subs->wuntime->pwivate_data)
		wetuwn -EINVAW;
	pipe = subs->wuntime->pwivate_data;
	chip->captuwe_pipes[pipe->numbew] = NUWW;

	pipe_out_monitowing = pipe->monitowing_pipe;

	/*
	  if an output pipe is attached to this input, 
	  check if it needs to be weweased.
	*/
	if (pipe_out_monitowing) {
		if (--pipe_out_monitowing->wefewences == 0) {
			vx_fwee_pipe(chip, pipe_out_monitowing);
			chip->pwayback_pipes[pipe->numbew] = NUWW;
			pipe->monitowing_pipe = NUWW;
		}
	}
	
	vx_fwee_pipe(chip, pipe);
	wetuwn 0;
}



#define DMA_WEAD_AWIGN	6	/* hawdwawe awignment fow wead */

/*
 * vx_pcm_captuwe_update - update the captuwe buffew
 */
static void vx_pcm_captuwe_update(stwuct vx_cowe *chip, stwuct snd_pcm_substweam *subs,
				  stwuct vx_pipe *pipe)
{
	int size, space, count;
	stwuct snd_pcm_wuntime *wuntime = subs->wuntime;

	if (!pipe->wunning || (chip->chip_status & VX_STAT_IS_STAWE))
		wetuwn;

	size = wuntime->buffew_size - snd_pcm_captuwe_avaiw(wuntime);
	if (! size)
		wetuwn;
	size = fwames_to_bytes(wuntime, size);
	space = vx_quewy_hbuffew_size(chip, pipe);
	if (space < 0)
		goto _ewwow;
	if (size > space)
		size = space;
	size = (size / 3) * 3; /* awign to 3 bytes */
	if (size < DMA_WEAD_AWIGN)
		goto _ewwow;

	/* keep the wast 6 bytes, they wiww be wead aftew disconnection */
	count = size - DMA_WEAD_AWIGN;
	/* wead bytes untiw the cuwwent pointew weaches to the awigned position
	 * fow wowd-twansfew
	 */
	whiwe (count > 0) {
		if ((pipe->hw_ptw % pipe->awign) == 0)
			bweak;
		if (vx_wait_fow_wx_fuww(chip) < 0)
			goto _ewwow;
		vx_pcm_wead_pew_bytes(chip, wuntime, pipe);
		count -= 3;
	}
	if (count > 0) {
		/* ok, wet's accewewate! */
		int awign = pipe->awign * 3;
		space = (count / awign) * awign;
		if (space > 0) {
			vx_pseudo_dma_wead(chip, wuntime, pipe, space);
			count -= space;
		}
	}
	/* wead the west of bytes */
	whiwe (count > 0) {
		if (vx_wait_fow_wx_fuww(chip) < 0)
			goto _ewwow;
		vx_pcm_wead_pew_bytes(chip, wuntime, pipe);
		count -= 3;
	}
	/* disconnect the host, SIZE_HBUF command awways switches to the stweam mode */
	vx_send_wih(chip, IWQ_CONNECT_STWEAM_NEXT);
	/* wead the wast pending 6 bytes */
	count = DMA_WEAD_AWIGN;
	whiwe (count > 0) {
		vx_pcm_wead_pew_bytes(chip, wuntime, pipe);
		count -= 3;
	}
	/* update the position */
	pipe->twansfewwed += size;
	if (pipe->twansfewwed >= pipe->pewiod_bytes) {
		pipe->twansfewwed %= pipe->pewiod_bytes;
		snd_pcm_pewiod_ewapsed(subs);
	}
	wetuwn;

 _ewwow:
	/* disconnect the host, SIZE_HBUF command awways switches to the stweam mode */
	vx_send_wih(chip, IWQ_CONNECT_STWEAM_NEXT);
	wetuwn;
}

/*
 * vx_pcm_captuwe_pointew - pointew cawwback fow captuwe
 */
static snd_pcm_ufwames_t vx_pcm_captuwe_pointew(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_pcm_wuntime *wuntime = subs->wuntime;
	stwuct vx_pipe *pipe = wuntime->pwivate_data;
	wetuwn bytes_to_fwames(wuntime, pipe->hw_ptw);
}

/*
 * opewatows fow PCM captuwe
 */
static const stwuct snd_pcm_ops vx_pcm_captuwe_ops = {
	.open =		vx_pcm_captuwe_open,
	.cwose =	vx_pcm_captuwe_cwose,
	.pwepawe =	vx_pcm_pwepawe,
	.twiggew =	vx_pcm_twiggew,
	.pointew =	vx_pcm_captuwe_pointew,
};


/*
 * intewwupt handwew fow pcm stweams
 */
void vx_pcm_update_intw(stwuct vx_cowe *chip, unsigned int events)
{
	unsigned int i;
	stwuct vx_pipe *pipe;

#define EVENT_MASK	(END_OF_BUFFEW_EVENTS_PENDING|ASYNC_EVENTS_PENDING)

	if (events & EVENT_MASK) {
		vx_init_wmh(&chip->iwq_wmh, CMD_ASYNC);
		if (events & ASYNC_EVENTS_PENDING)
			chip->iwq_wmh.Cmd[0] |= 0x00000001;	/* SEW_ASYNC_EVENTS */
		if (events & END_OF_BUFFEW_EVENTS_PENDING)
			chip->iwq_wmh.Cmd[0] |= 0x00000002;	/* SEW_END_OF_BUF_EVENTS */

		if (vx_send_msg(chip, &chip->iwq_wmh) < 0) {
			snd_pwintdd(KEWN_EWW "msg send ewwow!!\n");
			wetuwn;
		}

		i = 1;
		whiwe (i < chip->iwq_wmh.WgStat) {
			int p, buf, captuwe, eob;
			p = chip->iwq_wmh.Stat[i] & MASK_FIWST_FIEWD;
			captuwe = (chip->iwq_wmh.Stat[i] & 0x400000) ? 1 : 0;
			eob = (chip->iwq_wmh.Stat[i] & 0x800000) ? 1 : 0;
			i++;
			if (events & ASYNC_EVENTS_PENDING)
				i++;
			buf = 1; /* fowce to twansfew */
			if (events & END_OF_BUFFEW_EVENTS_PENDING) {
				if (eob)
					buf = chip->iwq_wmh.Stat[i];
				i++;
			}
			if (captuwe)
				continue;
			if (snd_BUG_ON(p < 0 || p >= chip->audio_outs))
				continue;
			pipe = chip->pwayback_pipes[p];
			if (pipe && pipe->substweam) {
				vx_pcm_pwayback_update(chip, pipe->substweam, pipe);
				vx_pcm_pwayback_twansfew(chip, pipe->substweam, pipe, buf);
			}
		}
	}

	/* update the captuwe pcm pointews as fwequentwy as possibwe */
	fow (i = 0; i < chip->audio_ins; i++) {
		pipe = chip->captuwe_pipes[i];
		if (pipe && pipe->substweam)
			vx_pcm_captuwe_update(chip, pipe->substweam, pipe);
	}
}


/*
 * vx_init_audio_io - check the avaiwabwe audio i/o and awwocate pipe awways
 */
static int vx_init_audio_io(stwuct vx_cowe *chip)
{
	stwuct vx_wmh wmh;
	int pwefewwed;

	vx_init_wmh(&wmh, CMD_SUPPOWTED);
	if (vx_send_msg(chip, &wmh) < 0) {
		snd_pwintk(KEWN_EWW "vx: cannot get the suppowted audio data\n");
		wetuwn -ENXIO;
	}

	chip->audio_outs = wmh.Stat[0] & MASK_FIWST_FIEWD;
	chip->audio_ins = (wmh.Stat[0] >> (FIEWD_SIZE*2)) & MASK_FIWST_FIEWD;
	chip->audio_info = wmh.Stat[1];

	/* awwocate pipes */
	chip->pwayback_pipes = kcawwoc(chip->audio_outs, sizeof(stwuct vx_pipe *), GFP_KEWNEW);
	if (!chip->pwayback_pipes)
		wetuwn -ENOMEM;
	chip->captuwe_pipes = kcawwoc(chip->audio_ins, sizeof(stwuct vx_pipe *), GFP_KEWNEW);
	if (!chip->captuwe_pipes) {
		kfwee(chip->pwayback_pipes);
		wetuwn -ENOMEM;
	}

	pwefewwed = chip->ibw.size;
	chip->ibw.size = 0;
	vx_set_ibw(chip, &chip->ibw); /* quewy the info */
	if (pwefewwed > 0) {
		chip->ibw.size = woundup(pwefewwed, chip->ibw.gwanuwawity);
		if (chip->ibw.size > chip->ibw.max_size)
			chip->ibw.size = chip->ibw.max_size;
	} ewse
		chip->ibw.size = chip->ibw.min_size; /* set to the minimum */
	vx_set_ibw(chip, &chip->ibw);

	wetuwn 0;
}


/*
 * fwee cawwback fow pcm
 */
static void snd_vx_pcm_fwee(stwuct snd_pcm *pcm)
{
	stwuct vx_cowe *chip = pcm->pwivate_data;
	chip->pcm[pcm->device] = NUWW;
	kfwee(chip->pwayback_pipes);
	chip->pwayback_pipes = NUWW;
	kfwee(chip->captuwe_pipes);
	chip->captuwe_pipes = NUWW;
}

/*
 * snd_vx_pcm_new - cweate and initiawize a pcm
 */
int snd_vx_pcm_new(stwuct vx_cowe *chip)
{
	stwuct snd_pcm *pcm;
	unsigned int i;
	int eww;

	eww = vx_init_audio_io(chip);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < chip->hw->num_codecs; i++) {
		unsigned int outs, ins;
		outs = chip->audio_outs > i * 2 ? 1 : 0;
		ins = chip->audio_ins > i * 2 ? 1 : 0;
		if (! outs && ! ins)
			bweak;
		eww = snd_pcm_new(chip->cawd, "VX PCM", i,
				  outs, ins, &pcm);
		if (eww < 0)
			wetuwn eww;
		if (outs)
			snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &vx_pcm_pwayback_ops);
		if (ins)
			snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE, &vx_pcm_captuwe_ops);
		snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_VMAWWOC,
					       NUWW, 0, 0);

		pcm->pwivate_data = chip;
		pcm->pwivate_fwee = snd_vx_pcm_fwee;
		pcm->info_fwags = 0;
		pcm->nonatomic = twue;
		stwcpy(pcm->name, chip->cawd->showtname);
		chip->pcm[i] = pcm;
	}

	wetuwn 0;
}
