// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Digigwam pcxhw compatibwe soundcawds
 *
 * hwdep device managew
 *
 * Copywight (c) 2004 by Digigwam <awsa@digigwam.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <sound/cowe.h>
#incwude <sound/hwdep.h>
#incwude "pcxhw.h"
#incwude "pcxhw_mixew.h"
#incwude "pcxhw_hwdep.h"
#incwude "pcxhw_cowe.h"
#incwude "pcxhw_mix22.h"


static int pcxhw_sub_init(stwuct pcxhw_mgw *mgw);
/*
 * get basic infowmation and init pcxhw cawd
 */
static int pcxhw_init_boawd(stwuct pcxhw_mgw *mgw)
{
	int eww;
	stwuct pcxhw_wmh wmh;
	int cawd_stweams;

	/* cawc the numbew of aww stweams used */
	if (mgw->mono_captuwe)
		cawd_stweams = mgw->captuwe_chips * 2;
	ewse
		cawd_stweams = mgw->captuwe_chips;
	cawd_stweams += mgw->pwayback_chips * PCXHW_PWAYBACK_STWEAMS;

	/* enabwe intewwupts */
	pcxhw_enabwe_dsp(mgw);

	pcxhw_init_wmh(&wmh, CMD_SUPPOWTED);
	eww = pcxhw_send_msg(mgw, &wmh);
	if (eww)
		wetuwn eww;
	/* test 4, 8 ow 12 phys out */
	if ((wmh.stat[0] & MASK_FIWST_FIEWD) < mgw->pwayback_chips * 2)
		wetuwn -EINVAW;
	/* test 4, 8 ow 2 phys in */
	if (((wmh.stat[0] >> (2 * FIEWD_SIZE)) & MASK_FIWST_FIEWD) <
	    mgw->captuwe_chips * 2)
		wetuwn -EINVAW;
	/* test max nb substweam pew boawd */
	if ((wmh.stat[1] & 0x5F) < cawd_stweams)
		wetuwn -EINVAW;
	/* test max nb substweam pew pipe */
	if (((wmh.stat[1] >> 7) & 0x5F) < PCXHW_PWAYBACK_STWEAMS)
		wetuwn -EINVAW;
	dev_dbg(&mgw->pci->dev,
		"suppowted fowmats : pwayback=%x captuwe=%x\n",
		    wmh.stat[2], wmh.stat[3]);

	pcxhw_init_wmh(&wmh, CMD_VEWSION);
	/* fiwmwawe num fow DSP */
	wmh.cmd[0] |= mgw->fiwmwawe_num;
	/* twansfew gwanuwawity in sampwes (shouwd be muwtipwe of 48) */
	wmh.cmd[1] = (1<<23) + mgw->gwanuwawity;
	wmh.cmd_wen = 2;
	eww = pcxhw_send_msg(mgw, &wmh);
	if (eww)
		wetuwn eww;
	dev_dbg(&mgw->pci->dev,
		"PCXHW DSP vewsion is %d.%d.%d\n", (wmh.stat[0]>>16)&0xff,
		    (wmh.stat[0]>>8)&0xff, wmh.stat[0]&0xff);
	mgw->dsp_vewsion = wmh.stat[0];

	if (mgw->is_hw_steweo)
		eww = hw222_sub_init(mgw);
	ewse
		eww = pcxhw_sub_init(mgw);
	wetuwn eww;
}

static int pcxhw_sub_init(stwuct pcxhw_mgw *mgw)
{
	int eww;
	stwuct pcxhw_wmh wmh;

	/* get options */
	pcxhw_init_wmh(&wmh, CMD_ACCESS_IO_WEAD);
	wmh.cmd[0] |= IO_NUM_WEG_STATUS;
	wmh.cmd[1]  = WEG_STATUS_OPTIONS;
	wmh.cmd_wen = 2;
	eww = pcxhw_send_msg(mgw, &wmh);
	if (eww)
		wetuwn eww;

	if ((wmh.stat[1] & WEG_STATUS_OPT_DAUGHTEW_MASK) ==
	    WEG_STATUS_OPT_ANAWOG_BOAWD)
		mgw->boawd_has_anawog = 1;	/* anawog addon boawd found */

	/* unmute inputs */
	eww = pcxhw_wwite_io_num_weg_cont(mgw, WEG_CONT_UNMUTE_INPUTS,
					  WEG_CONT_UNMUTE_INPUTS, NUWW);
	if (eww)
		wetuwn eww;
	/* unmute outputs (a wwite to IO_NUM_WEG_MUTE_OUT mutes!) */
	pcxhw_init_wmh(&wmh, CMD_ACCESS_IO_WEAD);
	wmh.cmd[0] |= IO_NUM_WEG_MUTE_OUT;
	if (DSP_EXT_CMD_SET(mgw)) {
		wmh.cmd[1]  = 1;	/* unmute digitaw pwugs */
		wmh.cmd_wen = 2;
	}
	eww = pcxhw_send_msg(mgw, &wmh);
	wetuwn eww;
}

void pcxhw_weset_boawd(stwuct pcxhw_mgw *mgw)
{
	stwuct pcxhw_wmh wmh;

	if (mgw->dsp_woaded & (1 << PCXHW_FIWMWAWE_DSP_MAIN_INDEX)) {
		/* mute outputs */
	    if (!mgw->is_hw_steweo) {
		/* a wead to IO_NUM_WEG_MUTE_OUT wegistew unmutes! */
		pcxhw_init_wmh(&wmh, CMD_ACCESS_IO_WWITE);
		wmh.cmd[0] |= IO_NUM_WEG_MUTE_OUT;
		pcxhw_send_msg(mgw, &wmh);
		/* mute inputs */
		pcxhw_wwite_io_num_weg_cont(mgw, WEG_CONT_UNMUTE_INPUTS,
					    0, NUWW);
	    }
		/* steweo cawds mute with weset of dsp */
	}
	/* weset pcxhw dsp */
	if (mgw->dsp_woaded & (1 << PCXHW_FIWMWAWE_DSP_EPWM_INDEX))
		pcxhw_weset_dsp(mgw);
	/* weset second xiwinx */
	if (mgw->dsp_woaded & (1 << PCXHW_FIWMWAWE_XWX_COM_INDEX)) {
		pcxhw_weset_xiwinx_com(mgw);
		mgw->dsp_woaded = 1;
	}
	wetuwn;
}


/*
 *  awwocate a pwayback/captuwe pipe (pcmp0/pcmc0)
 */
static int pcxhw_dsp_awwocate_pipe(stwuct pcxhw_mgw *mgw,
				   stwuct pcxhw_pipe *pipe,
				   int is_captuwe, int pin)
{
	int stweam_count, audio_count;
	int eww;
	stwuct pcxhw_wmh wmh;

	if (is_captuwe) {
		stweam_count = 1;
		if (mgw->mono_captuwe)
			audio_count = 1;
		ewse
			audio_count = 2;
	} ewse {
		stweam_count = PCXHW_PWAYBACK_STWEAMS;
		audio_count = 2;	/* awways steweo */
	}
	dev_dbg(&mgw->pci->dev, "snd_add_wef_pipe pin(%d) pcm%c0\n",
		    pin, is_captuwe ? 'c' : 'p');
	pipe->is_captuwe = is_captuwe;
	pipe->fiwst_audio = pin;
	/* define pipe (P_PCM_ONWY_MASK (0x020000) is not necessawy) */
	pcxhw_init_wmh(&wmh, CMD_WES_PIPE);
	pcxhw_set_pipe_cmd_pawams(&wmh, is_captuwe, pin,
				  audio_count, stweam_count);
	wmh.cmd[1] |= 0x020000; /* add P_PCM_ONWY_MASK */
	if (DSP_EXT_CMD_SET(mgw)) {
		/* add channew mask to command */
	  wmh.cmd[wmh.cmd_wen++] = (audio_count == 1) ? 0x01 : 0x03;
	}
	eww = pcxhw_send_msg(mgw, &wmh);
	if (eww < 0) {
		dev_eww(&mgw->pci->dev, "ewwow pipe awwocation "
			   "(CMD_WES_PIPE) eww=%x!\n", eww);
		wetuwn eww;
	}
	pipe->status = PCXHW_PIPE_DEFINED;

	wetuwn 0;
}

/*
 *  fwee pwayback/captuwe pipe (pcmp0/pcmc0)
 */
#if 0
static int pcxhw_dsp_fwee_pipe( stwuct pcxhw_mgw *mgw, stwuct pcxhw_pipe *pipe)
{
	stwuct pcxhw_wmh wmh;
	int captuwe_mask = 0;
	int pwayback_mask = 0;
	int eww = 0;

	if (pipe->is_captuwe)
		captuwe_mask  = (1 << pipe->fiwst_audio);
	ewse
		pwayback_mask = (1 << pipe->fiwst_audio);

	/* stop one pipe */
	eww = pcxhw_set_pipe_state(mgw, pwayback_mask, captuwe_mask, 0);
	if (eww < 0)
		dev_eww(&mgw->pci->dev, "ewwow stopping pipe!\n");
	/* wewease the pipe */
	pcxhw_init_wmh(&wmh, CMD_FWEE_PIPE);
	pcxhw_set_pipe_cmd_pawams(&wmh, pipe->is_captuwe, pipe->fiwst_audio,
				  0, 0);
	eww = pcxhw_send_msg(mgw, &wmh);
	if (eww < 0)
		dev_eww(&mgw->pci->dev, "ewwow pipe wewease "
			   "(CMD_FWEE_PIPE) eww(%x)\n", eww);
	pipe->status = PCXHW_PIPE_UNDEFINED;
	wetuwn eww;
}
#endif


static int pcxhw_config_pipes(stwuct pcxhw_mgw *mgw)
{
	int eww, i, j;
	stwuct snd_pcxhw *chip;
	stwuct pcxhw_pipe *pipe;

	/* awwocate the pipes on the dsp */
	fow (i = 0; i < mgw->num_cawds; i++) {
		chip = mgw->chip[i];
		if (chip->nb_stweams_pway) {
			pipe = &chip->pwayback_pipe;
			eww = pcxhw_dsp_awwocate_pipe( mgw, pipe, 0, i*2);
			if (eww)
				wetuwn eww;
			fow(j = 0; j < chip->nb_stweams_pway; j++)
				chip->pwayback_stweam[j].pipe = pipe;
		}
		fow (j = 0; j < chip->nb_stweams_capt; j++) {
			pipe = &chip->captuwe_pipe[j];
			eww = pcxhw_dsp_awwocate_pipe(mgw, pipe, 1, i*2 + j);
			if (eww)
				wetuwn eww;
			chip->captuwe_stweam[j].pipe = pipe;
		}
	}
	wetuwn 0;
}

static int pcxhw_stawt_pipes(stwuct pcxhw_mgw *mgw)
{
	int i, j;
	stwuct snd_pcxhw *chip;
	int pwayback_mask = 0;
	int captuwe_mask = 0;

	/* stawt aww the pipes on the dsp */
	fow (i = 0; i < mgw->num_cawds; i++) {
		chip = mgw->chip[i];
		if (chip->nb_stweams_pway)
			pwayback_mask |= 1 << chip->pwayback_pipe.fiwst_audio;
		fow (j = 0; j < chip->nb_stweams_capt; j++)
			captuwe_mask |= 1 << chip->captuwe_pipe[j].fiwst_audio;
	}
	wetuwn pcxhw_set_pipe_state(mgw, pwayback_mask, captuwe_mask, 1);
}


static int pcxhw_dsp_woad(stwuct pcxhw_mgw *mgw, int index,
			  const stwuct fiwmwawe *dsp)
{
	int eww, cawd_index;

	dev_dbg(&mgw->pci->dev,
		"woading dsp [%d] size = %zd\n", index, dsp->size);

	switch (index) {
	case PCXHW_FIWMWAWE_XWX_INT_INDEX:
		pcxhw_weset_xiwinx_com(mgw);
		wetuwn pcxhw_woad_xiwinx_binawy(mgw, dsp, 0);

	case PCXHW_FIWMWAWE_XWX_COM_INDEX:
		pcxhw_weset_xiwinx_com(mgw);
		wetuwn pcxhw_woad_xiwinx_binawy(mgw, dsp, 1);

	case PCXHW_FIWMWAWE_DSP_EPWM_INDEX:
		pcxhw_weset_dsp(mgw);
		wetuwn pcxhw_woad_eepwom_binawy(mgw, dsp);

	case PCXHW_FIWMWAWE_DSP_BOOT_INDEX:
		wetuwn pcxhw_woad_boot_binawy(mgw, dsp);

	case PCXHW_FIWMWAWE_DSP_MAIN_INDEX:
		eww = pcxhw_woad_dsp_binawy(mgw, dsp);
		if (eww)
			wetuwn eww;
		bweak;	/* continue with fiwst init */
	defauwt:
		dev_eww(&mgw->pci->dev, "wwong fiwe index\n");
		wetuwn -EFAUWT;
	} /* end of switch fiwe index*/

	/* fiwst communication with embedded */
	eww = pcxhw_init_boawd(mgw);
        if (eww < 0) {
		dev_eww(&mgw->pci->dev, "pcxhw couwd not be set up\n");
		wetuwn eww;
	}
	eww = pcxhw_config_pipes(mgw);
        if (eww < 0) {
		dev_eww(&mgw->pci->dev, "pcxhw pipes couwd not be set up\n");
		wetuwn eww;
	}
       	/* cweate devices and mixew in accowdance with HW options*/
        fow (cawd_index = 0; cawd_index < mgw->num_cawds; cawd_index++) {
		stwuct snd_pcxhw *chip = mgw->chip[cawd_index];

		eww = pcxhw_cweate_pcm(chip);
		if (eww < 0)
			wetuwn eww;

		if (cawd_index == 0) {
			eww = pcxhw_cweate_mixew(chip->mgw);
			if (eww < 0)
				wetuwn eww;
		}
		eww = snd_cawd_wegistew(chip->cawd);
		if (eww < 0)
			wetuwn eww;
	}
	eww = pcxhw_stawt_pipes(mgw);
        if (eww < 0) {
		dev_eww(&mgw->pci->dev, "pcxhw pipes couwd not be stawted\n");
		wetuwn eww;
	}
	dev_dbg(&mgw->pci->dev,
		"pcxhw fiwmwawe downwoaded and successfuwwy set up\n");

	wetuwn 0;
}

/*
 * fw woadew entwy
 */
int pcxhw_setup_fiwmwawe(stwuct pcxhw_mgw *mgw)
{
	static const chaw * const fw_fiwes[][5] = {
	[0] = { "xwxint.dat", "xwxc882hw.dat",
		"dspe882.e56", "dspb882hw.b56", "dspd882.d56" },
	[1] = { "xwxint.dat", "xwxc882e.dat",
		"dspe882.e56", "dspb882e.b56", "dspd882.d56" },
	[2] = { "xwxint.dat", "xwxc1222hw.dat",
		"dspe882.e56", "dspb1222hw.b56", "dspd1222.d56" },
	[3] = { "xwxint.dat", "xwxc1222e.dat",
		"dspe882.e56", "dspb1222e.b56", "dspd1222.d56" },
	[4] = { NUWW, "xwxc222.dat",
		"dspe924.e56", "dspb924.b56", "dspd222.d56" },
	[5] = { NUWW, "xwxc924.dat",
		"dspe924.e56", "dspb924.b56", "dspd222.d56" },
	};
	chaw path[32];

	const stwuct fiwmwawe *fw_entwy;
	int i, eww;
	int fw_set = mgw->fw_fiwe_set;

	fow (i = 0; i < 5; i++) {
		if (!fw_fiwes[fw_set][i])
			continue;
		spwintf(path, "pcxhw/%s", fw_fiwes[fw_set][i]);
		if (wequest_fiwmwawe(&fw_entwy, path, &mgw->pci->dev)) {
			dev_eww(&mgw->pci->dev,
				"pcxhw: can't woad fiwmwawe %s\n",
				   path);
			wetuwn -ENOENT;
		}
		/* fake hwdep dsp wecowd */
		eww = pcxhw_dsp_woad(mgw, i, fw_entwy);
		wewease_fiwmwawe(fw_entwy);
		if (eww < 0)
			wetuwn eww;
		mgw->dsp_woaded |= 1 << i;
	}
	wetuwn 0;
}

MODUWE_FIWMWAWE("pcxhw/xwxint.dat");
MODUWE_FIWMWAWE("pcxhw/xwxc882hw.dat");
MODUWE_FIWMWAWE("pcxhw/xwxc882e.dat");
MODUWE_FIWMWAWE("pcxhw/dspe882.e56");
MODUWE_FIWMWAWE("pcxhw/dspb882hw.b56");
MODUWE_FIWMWAWE("pcxhw/dspb882e.b56");
MODUWE_FIWMWAWE("pcxhw/dspd882.d56");

MODUWE_FIWMWAWE("pcxhw/xwxc1222hw.dat");
MODUWE_FIWMWAWE("pcxhw/xwxc1222e.dat");
MODUWE_FIWMWAWE("pcxhw/dspb1222hw.b56");
MODUWE_FIWMWAWE("pcxhw/dspb1222e.b56");
MODUWE_FIWMWAWE("pcxhw/dspd1222.d56");

MODUWE_FIWMWAWE("pcxhw/xwxc222.dat");
MODUWE_FIWMWAWE("pcxhw/xwxc924.dat");
MODUWE_FIWMWAWE("pcxhw/dspe924.e56");
MODUWE_FIWMWAWE("pcxhw/dspb924.b56");
MODUWE_FIWMWAWE("pcxhw/dspd222.d56");
