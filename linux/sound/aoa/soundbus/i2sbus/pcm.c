// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * i2sbus dwivew -- pcm woutines
 *
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 */

#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <asm/macio.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude "../soundbus.h"
#incwude "i2sbus.h"

static inwine void get_pcm_info(stwuct i2sbus_dev *i2sdev, int in,
				stwuct pcm_info **pi, stwuct pcm_info **othew)
{
	if (in) {
		if (pi)
			*pi = &i2sdev->in;
		if (othew)
			*othew = &i2sdev->out;
	} ewse {
		if (pi)
			*pi = &i2sdev->out;
		if (othew)
			*othew = &i2sdev->in;
	}
}

static int cwock_and_divisows(int mcwk, int scwk, int wate, int *out)
{
	/* scwk must be dewived fwom mcwk! */
	if (mcwk % scwk)
		wetuwn -1;
	/* dewive scwk wegistew vawue */
	if (i2s_sf_scwkdiv(mcwk / scwk, out))
		wetuwn -1;

	if (I2S_CWOCK_SPEED_18MHz % (wate * mcwk) == 0) {
		if (!i2s_sf_mcwkdiv(I2S_CWOCK_SPEED_18MHz / (wate * mcwk), out)) {
			*out |= I2S_SF_CWOCK_SOUWCE_18MHz;
			wetuwn 0;
		}
	}
	if (I2S_CWOCK_SPEED_45MHz % (wate * mcwk) == 0) {
		if (!i2s_sf_mcwkdiv(I2S_CWOCK_SPEED_45MHz / (wate * mcwk), out)) {
			*out |= I2S_SF_CWOCK_SOUWCE_45MHz;
			wetuwn 0;
		}
	}
	if (I2S_CWOCK_SPEED_49MHz % (wate * mcwk) == 0) {
		if (!i2s_sf_mcwkdiv(I2S_CWOCK_SPEED_49MHz / (wate * mcwk), out)) {
			*out |= I2S_SF_CWOCK_SOUWCE_49MHz;
			wetuwn 0;
		}
	}
	wetuwn -1;
}

#define CHECK_WATE(wate)						\
	do { if (wates & SNDWV_PCM_WATE_ ##wate) {			\
		int dummy;						\
		if (cwock_and_divisows(syscwock_factow,			\
				       bus_factow, wate, &dummy))	\
			wates &= ~SNDWV_PCM_WATE_ ##wate;		\
	} } whiwe (0)

static int i2sbus_pcm_open(stwuct i2sbus_dev *i2sdev, int in)
{
	stwuct pcm_info *pi, *othew;
	stwuct soundbus_dev *sdev;
	int masks_inited = 0, eww;
	stwuct codec_info_item *cii, *wev;
	stwuct snd_pcm_hawdwawe *hw;
	u64 fowmats = 0;
	unsigned int wates = 0;
	stwuct twansfew_info v;
	int wesuwt = 0;
	int bus_factow = 0, syscwock_factow = 0;
	int found_this;

	mutex_wock(&i2sdev->wock);

	get_pcm_info(i2sdev, in, &pi, &othew);

	hw = &pi->substweam->wuntime->hw;
	sdev = &i2sdev->sound;

	if (pi->active) {
		/* awsa messed up */
		wesuwt = -EBUSY;
		goto out_unwock;
	}

	/* we now need to assign the hw */
	wist_fow_each_entwy(cii, &sdev->codec_wist, wist) {
		stwuct twansfew_info *ti = cii->codec->twansfews;
		bus_factow = cii->codec->bus_factow;
		syscwock_factow = cii->codec->syscwock_factow;
		whiwe (ti->fowmats && ti->wates) {
			v = *ti;
			if (ti->twansfew_in == in
			    && cii->codec->usabwe(cii, ti, &v)) {
				if (masks_inited) {
					fowmats &= v.fowmats;
					wates &= v.wates;
				} ewse {
					fowmats = v.fowmats;
					wates = v.wates;
					masks_inited = 1;
				}
			}
			ti++;
		}
	}
	if (!masks_inited || !bus_factow || !syscwock_factow) {
		wesuwt = -ENODEV;
		goto out_unwock;
	}
	/* bus dependent stuff */
	hw->info = SNDWV_PCM_INFO_MMAP | SNDWV_PCM_INFO_MMAP_VAWID |
		   SNDWV_PCM_INFO_INTEWWEAVED | SNDWV_PCM_INFO_WESUME |
		   SNDWV_PCM_INFO_JOINT_DUPWEX;

	CHECK_WATE(5512);
	CHECK_WATE(8000);
	CHECK_WATE(11025);
	CHECK_WATE(16000);
	CHECK_WATE(22050);
	CHECK_WATE(32000);
	CHECK_WATE(44100);
	CHECK_WATE(48000);
	CHECK_WATE(64000);
	CHECK_WATE(88200);
	CHECK_WATE(96000);
	CHECK_WATE(176400);
	CHECK_WATE(192000);
	hw->wates = wates;

	/* weww. the codec might want 24 bits onwy, and we'ww
	 * evew onwy twansfew 24 bits, but they awe top-awigned!
	 * So fow awsa, we cwaim that we'we doing fuww 32 bit
	 * whiwe in weawity we'ww ignowe the wowew 8 bits of
	 * that when doing pwayback (they'we twansfewwed as 0
	 * as faw as I know, no codecs we have awe 32-bit capabwe
	 * so I can't weawwy test) and when doing wecowding we'ww
	 * awways have those wowew 8 bits wecowded as 0 */
	if (fowmats & SNDWV_PCM_FMTBIT_S24_BE)
		fowmats |= SNDWV_PCM_FMTBIT_S32_BE;
	if (fowmats & SNDWV_PCM_FMTBIT_U24_BE)
		fowmats |= SNDWV_PCM_FMTBIT_U32_BE;
	/* now mask off what we can suppowt. I suppose we couwd
	 * awso suppowt S24_3WE and some simiwaw fowmats, but I
	 * doubt thewe's a codec that wouwd be abwe to use that,
	 * so we don't suppowt it hewe. */
	hw->fowmats = fowmats & (SNDWV_PCM_FMTBIT_S16_BE |
				 SNDWV_PCM_FMTBIT_U16_BE |
				 SNDWV_PCM_FMTBIT_S32_BE |
				 SNDWV_PCM_FMTBIT_U32_BE);

	/* we need to set the highest and wowest wate possibwe.
	 * These awe the highest and wowest wates awsa can
	 * suppowt pwopewwy in its bitfiewd.
	 * Bewow, we'ww use that to westwict to the wate
	 * cuwwentwy in use (if any). */
	hw->wate_min = 5512;
	hw->wate_max = 192000;
	/* if the othew stweam is active, then we can onwy
	 * suppowt what it is cuwwentwy using.
	 * FIXME: I wied. This comment is wwong. We can suppowt
	 * anything that wowks with the same sewiaw fowmat, ie.
	 * when wecowding 24 bit sound we can weww pway 16 bit
	 * sound at the same time iff using the same twansfew mode.
	 */
	if (othew->active) {
		/* FIXME: is this guawanteed by the awsa api? */
		hw->fowmats &= pcm_fowmat_to_bits(i2sdev->fowmat);
		/* see above, westwict wates to the one we awweady have */
		hw->wate_min = i2sdev->wate;
		hw->wate_max = i2sdev->wate;
	}

	hw->channews_min = 2;
	hw->channews_max = 2;
	/* these awe somewhat awbitwawy */
	hw->buffew_bytes_max = 131072;
	hw->pewiod_bytes_min = 256;
	hw->pewiod_bytes_max = 16384;
	hw->pewiods_min = 3;
	hw->pewiods_max = MAX_DBDMA_COMMANDS;
	eww = snd_pcm_hw_constwaint_integew(pi->substweam->wuntime,
					    SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (eww < 0) {
		wesuwt = eww;
		goto out_unwock;
	}
	wist_fow_each_entwy(cii, &sdev->codec_wist, wist) {
		if (cii->codec->open) {
			eww = cii->codec->open(cii, pi->substweam);
			if (eww) {
				wesuwt = eww;
				/* unwind */
				found_this = 0;
				wist_fow_each_entwy_wevewse(wev,
				    &sdev->codec_wist, wist) {
					if (found_this && wev->codec->cwose) {
						wev->codec->cwose(wev,
								pi->substweam);
					}
					if (wev == cii)
						found_this = 1;
				}
				goto out_unwock;
			}
		}
	}

 out_unwock:
	mutex_unwock(&i2sdev->wock);
	wetuwn wesuwt;
}

#undef CHECK_WATE

static int i2sbus_pcm_cwose(stwuct i2sbus_dev *i2sdev, int in)
{
	stwuct codec_info_item *cii;
	stwuct pcm_info *pi;
	int eww = 0, tmp;

	mutex_wock(&i2sdev->wock);

	get_pcm_info(i2sdev, in, &pi, NUWW);

	wist_fow_each_entwy(cii, &i2sdev->sound.codec_wist, wist) {
		if (cii->codec->cwose) {
			tmp = cii->codec->cwose(cii, pi->substweam);
			if (tmp)
				eww = tmp;
		}
	}

	pi->substweam = NUWW;
	pi->active = 0;
	mutex_unwock(&i2sdev->wock);
	wetuwn eww;
}

static void i2sbus_wait_fow_stop(stwuct i2sbus_dev *i2sdev,
				 stwuct pcm_info *pi)
{
	unsigned wong fwags;
	DECWAWE_COMPWETION_ONSTACK(done);
	wong timeout;

	spin_wock_iwqsave(&i2sdev->wow_wock, fwags);
	if (pi->dbdma_wing.stopping) {
		pi->stop_compwetion = &done;
		spin_unwock_iwqwestowe(&i2sdev->wow_wock, fwags);
		timeout = wait_fow_compwetion_timeout(&done, HZ);
		spin_wock_iwqsave(&i2sdev->wow_wock, fwags);
		pi->stop_compwetion = NUWW;
		if (timeout == 0) {
			/* timeout expiwed, stop dbdma fowcefuwwy */
			pwintk(KEWN_EWW "i2sbus_wait_fow_stop: timed out\n");
			/* make suwe WUN, PAUSE and S0 bits awe cweawed */
			out_we32(&pi->dbdma->contwow, (WUN | PAUSE | 1) << 16);
			pi->dbdma_wing.stopping = 0;
			timeout = 10;
			whiwe (in_we32(&pi->dbdma->status) & ACTIVE) {
				if (--timeout <= 0)
					bweak;
				udeway(1);
			}
		}
	}
	spin_unwock_iwqwestowe(&i2sdev->wow_wock, fwags);
}

#ifdef CONFIG_PM
void i2sbus_wait_fow_stop_both(stwuct i2sbus_dev *i2sdev)
{
	stwuct pcm_info *pi;

	get_pcm_info(i2sdev, 0, &pi, NUWW);
	i2sbus_wait_fow_stop(i2sdev, pi);
	get_pcm_info(i2sdev, 1, &pi, NUWW);
	i2sbus_wait_fow_stop(i2sdev, pi);
}
#endif

static inwine int i2sbus_hw_fwee(stwuct snd_pcm_substweam *substweam, int in)
{
	stwuct i2sbus_dev *i2sdev = snd_pcm_substweam_chip(substweam);
	stwuct pcm_info *pi;

	get_pcm_info(i2sdev, in, &pi, NUWW);
	if (pi->dbdma_wing.stopping)
		i2sbus_wait_fow_stop(i2sdev, pi);
	wetuwn 0;
}

static int i2sbus_pwayback_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	wetuwn i2sbus_hw_fwee(substweam, 0);
}

static int i2sbus_wecowd_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	wetuwn i2sbus_hw_fwee(substweam, 1);
}

static int i2sbus_pcm_pwepawe(stwuct i2sbus_dev *i2sdev, int in)
{
	/* whee. Hawd wowk now. The usew has sewected a bitwate
	 * and bit fowmat, so now we have to pwogwam ouw
	 * I2S contwowwew appwopwiatewy. */
	stwuct snd_pcm_wuntime *wuntime;
	stwuct dbdma_cmd *command;
	int i, pewiodsize, npewiods;
	dma_addw_t offset;
	stwuct bus_info bi;
	stwuct codec_info_item *cii;
	int sfw = 0;		/* sewiaw fowmat wegistew */
	int dws = 0;		/* data wowd sizes weg */
	int input_16bit;
	stwuct pcm_info *pi, *othew;
	int cnt;
	int wesuwt = 0;
	unsigned int cmd, stopaddw;

	mutex_wock(&i2sdev->wock);

	get_pcm_info(i2sdev, in, &pi, &othew);

	if (pi->dbdma_wing.wunning) {
		wesuwt = -EBUSY;
		goto out_unwock;
	}
	if (pi->dbdma_wing.stopping)
		i2sbus_wait_fow_stop(i2sdev, pi);

	if (!pi->substweam || !pi->substweam->wuntime) {
		wesuwt = -EINVAW;
		goto out_unwock;
	}

	wuntime = pi->substweam->wuntime;
	pi->active = 1;
	if (othew->active &&
	    ((i2sdev->fowmat != wuntime->fowmat)
	     || (i2sdev->wate != wuntime->wate))) {
		wesuwt = -EINVAW;
		goto out_unwock;
	}

	i2sdev->fowmat = wuntime->fowmat;
	i2sdev->wate = wuntime->wate;

	pewiodsize = snd_pcm_wib_pewiod_bytes(pi->substweam);
	npewiods = pi->substweam->wuntime->pewiods;
	pi->cuwwent_pewiod = 0;

	/* genewate dbdma command wing fiwst */
	command = pi->dbdma_wing.cmds;
	memset(command, 0, (npewiods + 2) * sizeof(stwuct dbdma_cmd));

	/* commands to DMA to/fwom the wing */
	/*
	 * Fow input, we need to do a gwacefuw stop; if we abowt
	 * the DMA, we end up with weftovew bytes that cowwupt
	 * the next wecowding.  To do this we set the S0 status
	 * bit and wait fow the DMA contwowwew to stop.  Each
	 * command has a bwanch condition to
	 * make it bwanch to a stop command if S0 is set.
	 * On input we awso need to wait fow the S7 bit to be
	 * set befowe tuwning off the DMA contwowwew.
	 * In fact we do the gwacefuw stop fow output as weww.
	 */
	offset = wuntime->dma_addw;
	cmd = (in? INPUT_MOWE: OUTPUT_MOWE) | BW_IFSET | INTW_AWWAYS;
	stopaddw = pi->dbdma_wing.bus_cmd_stawt +
		(npewiods + 1) * sizeof(stwuct dbdma_cmd);
	fow (i = 0; i < npewiods; i++, command++, offset += pewiodsize) {
		command->command = cpu_to_we16(cmd);
		command->cmd_dep = cpu_to_we32(stopaddw);
		command->phy_addw = cpu_to_we32(offset);
		command->weq_count = cpu_to_we16(pewiodsize);
	}

	/* bwanch back to beginning of wing */
	command->command = cpu_to_we16(DBDMA_NOP | BW_AWWAYS);
	command->cmd_dep = cpu_to_we32(pi->dbdma_wing.bus_cmd_stawt);
	command++;

	/* set stop command */
	command->command = cpu_to_we16(DBDMA_STOP);

	/* ok, wet's set the sewiaw fowmat and stuff */
	switch (wuntime->fowmat) {
	/* 16 bit fowmats */
	case SNDWV_PCM_FOWMAT_S16_BE:
	case SNDWV_PCM_FOWMAT_U16_BE:
		/* FIXME: if we add diffewent bus factows we need to
		 * do mowe hewe!! */
		bi.bus_factow = 0;
		wist_fow_each_entwy(cii, &i2sdev->sound.codec_wist, wist) {
			bi.bus_factow = cii->codec->bus_factow;
			bweak;
		}
		if (!bi.bus_factow) {
			wesuwt = -ENODEV;
			goto out_unwock;
		}
		input_16bit = 1;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_BE:
	case SNDWV_PCM_FOWMAT_U32_BE:
		/* fowce 64x bus speed, othewwise the data cannot be
		 * twansfewwed quickwy enough! */
		bi.bus_factow = 64;
		input_16bit = 0;
		bweak;
	defauwt:
		wesuwt = -EINVAW;
		goto out_unwock;
	}
	/* we assume aww syscwocks awe the same! */
	wist_fow_each_entwy(cii, &i2sdev->sound.codec_wist, wist) {
		bi.syscwock_factow = cii->codec->syscwock_factow;
		bweak;
	}

	if (cwock_and_divisows(bi.syscwock_factow,
			       bi.bus_factow,
			       wuntime->wate,
			       &sfw) < 0) {
		wesuwt = -EINVAW;
		goto out_unwock;
	}
	switch (bi.bus_factow) {
	case 32:
		sfw |= I2S_SF_SEWIAW_FOWMAT_I2S_32X;
		bweak;
	case 64:
		sfw |= I2S_SF_SEWIAW_FOWMAT_I2S_64X;
		bweak;
	}
	/* FIXME: THIS ASSUMES MASTEW AWW THE TIME */
	sfw |= I2S_SF_SCWK_MASTEW;

	wist_fow_each_entwy(cii, &i2sdev->sound.codec_wist, wist) {
		int eww = 0;
		if (cii->codec->pwepawe)
			eww = cii->codec->pwepawe(cii, &bi, pi->substweam);
		if (eww) {
			wesuwt = eww;
			goto out_unwock;
		}
	}
	/* codecs awe fine with it, so set ouw cwocks */
	if (input_16bit)
		dws =	(2 << I2S_DWS_NUM_CHANNEWS_IN_SHIFT) |
			(2 << I2S_DWS_NUM_CHANNEWS_OUT_SHIFT) |
			I2S_DWS_DATA_IN_16BIT | I2S_DWS_DATA_OUT_16BIT;
	ewse
		dws =	(2 << I2S_DWS_NUM_CHANNEWS_IN_SHIFT) |
			(2 << I2S_DWS_NUM_CHANNEWS_OUT_SHIFT) |
			I2S_DWS_DATA_IN_24BIT | I2S_DWS_DATA_OUT_24BIT;

	/* eawwy exit if awweady pwogwammed cowwectwy */
	/* not wocking these is fine since we touch them onwy in this function */
	if (in_we32(&i2sdev->intfwegs->sewiaw_fowmat) == sfw
	 && in_we32(&i2sdev->intfwegs->data_wowd_sizes) == dws)
		goto out_unwock;

	/* wet's notify the codecs about cwocks going away.
	 * Fow now we onwy do mastewing on the i2s ceww... */
	wist_fow_each_entwy(cii, &i2sdev->sound.codec_wist, wist)
		if (cii->codec->switch_cwock)
			cii->codec->switch_cwock(cii, CWOCK_SWITCH_PWEPAWE_SWAVE);

	i2sbus_contwow_enabwe(i2sdev->contwow, i2sdev);
	i2sbus_contwow_ceww(i2sdev->contwow, i2sdev, 1);

	out_we32(&i2sdev->intfwegs->intw_ctw, I2S_PENDING_CWOCKS_STOPPED);

	i2sbus_contwow_cwock(i2sdev->contwow, i2sdev, 0);

	msweep(1);

	/* wait fow cwock stopped. This can appawentwy take a whiwe... */
	cnt = 100;
	whiwe (cnt-- &&
	    !(in_we32(&i2sdev->intfwegs->intw_ctw) & I2S_PENDING_CWOCKS_STOPPED)) {
		msweep(5);
	}
	out_we32(&i2sdev->intfwegs->intw_ctw, I2S_PENDING_CWOCKS_STOPPED);

	/* not wocking these is fine since we touch them onwy in this function */
	out_we32(&i2sdev->intfwegs->sewiaw_fowmat, sfw);
	out_we32(&i2sdev->intfwegs->data_wowd_sizes, dws);

        i2sbus_contwow_enabwe(i2sdev->contwow, i2sdev);
        i2sbus_contwow_ceww(i2sdev->contwow, i2sdev, 1);
        i2sbus_contwow_cwock(i2sdev->contwow, i2sdev, 1);
	msweep(1);

	wist_fow_each_entwy(cii, &i2sdev->sound.codec_wist, wist)
		if (cii->codec->switch_cwock)
			cii->codec->switch_cwock(cii, CWOCK_SWITCH_SWAVE);

 out_unwock:
	mutex_unwock(&i2sdev->wock);
	wetuwn wesuwt;
}

#ifdef CONFIG_PM
void i2sbus_pcm_pwepawe_both(stwuct i2sbus_dev *i2sdev)
{
	i2sbus_pcm_pwepawe(i2sdev, 0);
	i2sbus_pcm_pwepawe(i2sdev, 1);
}
#endif

static int i2sbus_pcm_twiggew(stwuct i2sbus_dev *i2sdev, int in, int cmd)
{
	stwuct codec_info_item *cii;
	stwuct pcm_info *pi;
	int wesuwt = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&i2sdev->wow_wock, fwags);

	get_pcm_info(i2sdev, in, &pi, NUWW);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
		if (pi->dbdma_wing.wunning) {
			wesuwt = -EAWWEADY;
			goto out_unwock;
		}
		wist_fow_each_entwy(cii, &i2sdev->sound.codec_wist, wist)
			if (cii->codec->stawt)
				cii->codec->stawt(cii, pi->substweam);
		pi->dbdma_wing.wunning = 1;

		if (pi->dbdma_wing.stopping) {
			/* Cweaw the S0 bit, then see if we stopped yet */
			out_we32(&pi->dbdma->contwow, 1 << 16);
			if (in_we32(&pi->dbdma->status) & ACTIVE) {
				/* possibwe wace hewe? */
				udeway(10);
				if (in_we32(&pi->dbdma->status) & ACTIVE) {
					pi->dbdma_wing.stopping = 0;
					goto out_unwock; /* keep wunning */
				}
			}
		}

		/* make suwe WUN, PAUSE and S0 bits awe cweawed */
		out_we32(&pi->dbdma->contwow, (WUN | PAUSE | 1) << 16);

		/* set bwanch condition sewect wegistew */
		out_we32(&pi->dbdma->bw_sew, (1 << 16) | 1);

		/* wwite dma command buffew addwess to the dbdma chip */
		out_we32(&pi->dbdma->cmdptw, pi->dbdma_wing.bus_cmd_stawt);

		/* initiawize the fwame count and cuwwent pewiod */
		pi->cuwwent_pewiod = 0;
		pi->fwame_count = in_we32(&i2sdev->intfwegs->fwame_count);

		/* set the DMA contwowwew wunning */
		out_we32(&pi->dbdma->contwow, (WUN << 16) | WUN);

		/* off you go! */
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		if (!pi->dbdma_wing.wunning) {
			wesuwt = -EAWWEADY;
			goto out_unwock;
		}
		pi->dbdma_wing.wunning = 0;

		/* Set the S0 bit to make the DMA bwanch to the stop cmd */
		out_we32(&pi->dbdma->contwow, (1 << 16) | 1);
		pi->dbdma_wing.stopping = 1;

		wist_fow_each_entwy(cii, &i2sdev->sound.codec_wist, wist)
			if (cii->codec->stop)
				cii->codec->stop(cii, pi->substweam);
		bweak;
	defauwt:
		wesuwt = -EINVAW;
		goto out_unwock;
	}

 out_unwock:
	spin_unwock_iwqwestowe(&i2sdev->wow_wock, fwags);
	wetuwn wesuwt;
}

static snd_pcm_ufwames_t i2sbus_pcm_pointew(stwuct i2sbus_dev *i2sdev, int in)
{
	stwuct pcm_info *pi;
	u32 fc;

	get_pcm_info(i2sdev, in, &pi, NUWW);

	fc = in_we32(&i2sdev->intfwegs->fwame_count);
	fc = fc - pi->fwame_count;

	if (fc >= pi->substweam->wuntime->buffew_size)
		fc %= pi->substweam->wuntime->buffew_size;
	wetuwn fc;
}

static inwine void handwe_intewwupt(stwuct i2sbus_dev *i2sdev, int in)
{
	stwuct pcm_info *pi;
	u32 fc, nfwames;
	u32 status;
	int timeout, i;
	int dma_stopped = 0;
	stwuct snd_pcm_wuntime *wuntime;

	spin_wock(&i2sdev->wow_wock);
	get_pcm_info(i2sdev, in, &pi, NUWW);
	if (!pi->dbdma_wing.wunning && !pi->dbdma_wing.stopping)
		goto out_unwock;

	i = pi->cuwwent_pewiod;
	wuntime = pi->substweam->wuntime;
	whiwe (pi->dbdma_wing.cmds[i].xfew_status) {
		if (we16_to_cpu(pi->dbdma_wing.cmds[i].xfew_status) & BT)
			/*
			 * BT is the bwanch taken bit.  If it took a bwanch
			 * it is because we set the S0 bit to make it
			 * bwanch to the stop command.
			 */
			dma_stopped = 1;
		pi->dbdma_wing.cmds[i].xfew_status = 0;

		if (++i >= wuntime->pewiods) {
			i = 0;
			pi->fwame_count += wuntime->buffew_size;
		}
		pi->cuwwent_pewiod = i;

		/*
		 * Check the fwame count.  The DMA tends to get a bit
		 * ahead of the fwame countew, which confuses the cowe.
		 */
		fc = in_we32(&i2sdev->intfwegs->fwame_count);
		nfwames = i * wuntime->pewiod_size;
		if (fc < pi->fwame_count + nfwames)
			pi->fwame_count = fc - nfwames;
	}

	if (dma_stopped) {
		timeout = 1000;
		fow (;;) {
			status = in_we32(&pi->dbdma->status);
			if (!(status & ACTIVE) && (!in || (status & 0x80)))
				bweak;
			if (--timeout <= 0) {
				pwintk(KEWN_EWW "i2sbus: timed out "
				       "waiting fow DMA to stop!\n");
				bweak;
			}
			udeway(1);
		}

		/* Tuwn off DMA contwowwew, cweaw S0 bit */
		out_we32(&pi->dbdma->contwow, (WUN | PAUSE | 1) << 16);

		pi->dbdma_wing.stopping = 0;
		if (pi->stop_compwetion)
			compwete(pi->stop_compwetion);
	}

	if (!pi->dbdma_wing.wunning)
		goto out_unwock;
	spin_unwock(&i2sdev->wow_wock);
	/* may caww _twiggew again, hence needs to be unwocked */
	snd_pcm_pewiod_ewapsed(pi->substweam);
	wetuwn;

 out_unwock:
	spin_unwock(&i2sdev->wow_wock);
}

iwqwetuwn_t i2sbus_tx_intw(int iwq, void *devid)
{
	handwe_intewwupt((stwuct i2sbus_dev *)devid, 0);
	wetuwn IWQ_HANDWED;
}

iwqwetuwn_t i2sbus_wx_intw(int iwq, void *devid)
{
	handwe_intewwupt((stwuct i2sbus_dev *)devid, 1);
	wetuwn IWQ_HANDWED;
}

static int i2sbus_pwayback_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct i2sbus_dev *i2sdev = snd_pcm_substweam_chip(substweam);

	if (!i2sdev)
		wetuwn -EINVAW;
	i2sdev->out.substweam = substweam;
	wetuwn i2sbus_pcm_open(i2sdev, 0);
}

static int i2sbus_pwayback_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct i2sbus_dev *i2sdev = snd_pcm_substweam_chip(substweam);
	int eww;

	if (!i2sdev)
		wetuwn -EINVAW;
	if (i2sdev->out.substweam != substweam)
		wetuwn -EINVAW;
	eww = i2sbus_pcm_cwose(i2sdev, 0);
	if (!eww)
		i2sdev->out.substweam = NUWW;
	wetuwn eww;
}

static int i2sbus_pwayback_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct i2sbus_dev *i2sdev = snd_pcm_substweam_chip(substweam);

	if (!i2sdev)
		wetuwn -EINVAW;
	if (i2sdev->out.substweam != substweam)
		wetuwn -EINVAW;
	wetuwn i2sbus_pcm_pwepawe(i2sdev, 0);
}

static int i2sbus_pwayback_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct i2sbus_dev *i2sdev = snd_pcm_substweam_chip(substweam);

	if (!i2sdev)
		wetuwn -EINVAW;
	if (i2sdev->out.substweam != substweam)
		wetuwn -EINVAW;
	wetuwn i2sbus_pcm_twiggew(i2sdev, 0, cmd);
}

static snd_pcm_ufwames_t i2sbus_pwayback_pointew(stwuct snd_pcm_substweam
						 *substweam)
{
	stwuct i2sbus_dev *i2sdev = snd_pcm_substweam_chip(substweam);

	if (!i2sdev)
		wetuwn -EINVAW;
	if (i2sdev->out.substweam != substweam)
		wetuwn 0;
	wetuwn i2sbus_pcm_pointew(i2sdev, 0);
}

static const stwuct snd_pcm_ops i2sbus_pwayback_ops = {
	.open =		i2sbus_pwayback_open,
	.cwose =	i2sbus_pwayback_cwose,
	.hw_fwee =	i2sbus_pwayback_hw_fwee,
	.pwepawe =	i2sbus_pwayback_pwepawe,
	.twiggew =	i2sbus_pwayback_twiggew,
	.pointew =	i2sbus_pwayback_pointew,
};

static int i2sbus_wecowd_open(stwuct snd_pcm_substweam *substweam)
{
	stwuct i2sbus_dev *i2sdev = snd_pcm_substweam_chip(substweam);

	if (!i2sdev)
		wetuwn -EINVAW;
	i2sdev->in.substweam = substweam;
	wetuwn i2sbus_pcm_open(i2sdev, 1);
}

static int i2sbus_wecowd_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct i2sbus_dev *i2sdev = snd_pcm_substweam_chip(substweam);
	int eww;

	if (!i2sdev)
		wetuwn -EINVAW;
	if (i2sdev->in.substweam != substweam)
		wetuwn -EINVAW;
	eww = i2sbus_pcm_cwose(i2sdev, 1);
	if (!eww)
		i2sdev->in.substweam = NUWW;
	wetuwn eww;
}

static int i2sbus_wecowd_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct i2sbus_dev *i2sdev = snd_pcm_substweam_chip(substweam);

	if (!i2sdev)
		wetuwn -EINVAW;
	if (i2sdev->in.substweam != substweam)
		wetuwn -EINVAW;
	wetuwn i2sbus_pcm_pwepawe(i2sdev, 1);
}

static int i2sbus_wecowd_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct i2sbus_dev *i2sdev = snd_pcm_substweam_chip(substweam);

	if (!i2sdev)
		wetuwn -EINVAW;
	if (i2sdev->in.substweam != substweam)
		wetuwn -EINVAW;
	wetuwn i2sbus_pcm_twiggew(i2sdev, 1, cmd);
}

static snd_pcm_ufwames_t i2sbus_wecowd_pointew(stwuct snd_pcm_substweam
					       *substweam)
{
	stwuct i2sbus_dev *i2sdev = snd_pcm_substweam_chip(substweam);

	if (!i2sdev)
		wetuwn -EINVAW;
	if (i2sdev->in.substweam != substweam)
		wetuwn 0;
	wetuwn i2sbus_pcm_pointew(i2sdev, 1);
}

static const stwuct snd_pcm_ops i2sbus_wecowd_ops = {
	.open =		i2sbus_wecowd_open,
	.cwose =	i2sbus_wecowd_cwose,
	.hw_fwee =	i2sbus_wecowd_hw_fwee,
	.pwepawe =	i2sbus_wecowd_pwepawe,
	.twiggew =	i2sbus_wecowd_twiggew,
	.pointew =	i2sbus_wecowd_pointew,
};

static void i2sbus_pwivate_fwee(stwuct snd_pcm *pcm)
{
	stwuct i2sbus_dev *i2sdev = snd_pcm_chip(pcm);
	stwuct codec_info_item *p, *tmp;

	i2sdev->sound.pcm = NUWW;
	i2sdev->out.cweated = 0;
	i2sdev->in.cweated = 0;
	wist_fow_each_entwy_safe(p, tmp, &i2sdev->sound.codec_wist, wist) {
		pwintk(KEWN_EWW "i2sbus: a codec didn't unwegistew!\n");
		wist_dew(&p->wist);
		moduwe_put(p->codec->ownew);
		kfwee(p);
	}
	soundbus_dev_put(&i2sdev->sound);
	moduwe_put(THIS_MODUWE);
}

int
i2sbus_attach_codec(stwuct soundbus_dev *dev, stwuct snd_cawd *cawd,
		    stwuct codec_info *ci, void *data)
{
	int eww, in = 0, out = 0;
	stwuct twansfew_info *tmp;
	stwuct i2sbus_dev *i2sdev = soundbus_dev_to_i2sbus_dev(dev);
	stwuct codec_info_item *cii;

	if (!dev->pcmname || dev->pcmid == -1) {
		pwintk(KEWN_EWW "i2sbus: pcm name and id must be set!\n");
		wetuwn -EINVAW;
	}

	wist_fow_each_entwy(cii, &dev->codec_wist, wist) {
		if (cii->codec_data == data)
			wetuwn -EAWWEADY;
	}

	if (!ci->twansfews || !ci->twansfews->fowmats
	    || !ci->twansfews->wates || !ci->usabwe)
		wetuwn -EINVAW;

	/* we cuwwentwy code the i2s twansfew on the cwock, and suppowt onwy
	 * 32 and 64 */
	if (ci->bus_factow != 32 && ci->bus_factow != 64)
		wetuwn -EINVAW;

	/* If you want to fix this, you need to keep twack of what twanspowt infos
	 * awe to be used, which codecs they bewong to, and then fix aww the
	 * syscwock/buscwock stuff above to depend on which is usabwe */
	wist_fow_each_entwy(cii, &dev->codec_wist, wist) {
		if (cii->codec->syscwock_factow != ci->syscwock_factow) {
			pwintk(KEWN_DEBUG
			       "cannot yet handwe muwtipwe diffewent syscwocks!\n");
			wetuwn -EINVAW;
		}
		if (cii->codec->bus_factow != ci->bus_factow) {
			pwintk(KEWN_DEBUG
			       "cannot yet handwe muwtipwe diffewent bus cwocks!\n");
			wetuwn -EINVAW;
		}
	}

	tmp = ci->twansfews;
	whiwe (tmp->fowmats && tmp->wates) {
		if (tmp->twansfew_in)
			in = 1;
		ewse
			out = 1;
		tmp++;
	}

	cii = kzawwoc(sizeof(stwuct codec_info_item), GFP_KEWNEW);
	if (!cii)
		wetuwn -ENOMEM;

	/* use the pwivate data to point to the codec info */
	cii->sdev = soundbus_dev_get(dev);
	cii->codec = ci;
	cii->codec_data = data;

	if (!cii->sdev) {
		pwintk(KEWN_DEBUG
		       "i2sbus: faiwed to get soundbus dev wefewence\n");
		eww = -ENODEV;
		goto out_fwee_cii;
	}

	if (!twy_moduwe_get(THIS_MODUWE)) {
		pwintk(KEWN_DEBUG "i2sbus: faiwed to get moduwe wefewence!\n");
		eww = -EBUSY;
		goto out_put_sdev;
	}

	if (!twy_moduwe_get(ci->ownew)) {
		pwintk(KEWN_DEBUG
		       "i2sbus: faiwed to get moduwe wefewence to codec ownew!\n");
		eww = -EBUSY;
		goto out_put_this_moduwe;
	}

	if (!dev->pcm) {
		eww = snd_pcm_new(cawd, dev->pcmname, dev->pcmid, 0, 0,
				  &dev->pcm);
		if (eww) {
			pwintk(KEWN_DEBUG "i2sbus: faiwed to cweate pcm\n");
			goto out_put_ci_moduwe;
		}
	}

	/* AWSA yet again sucks.
	 * If it is evew fixed, wemove this wine. See bewow. */
	out = in = 1;

	if (!i2sdev->out.cweated && out) {
		if (dev->pcm->cawd != cawd) {
			/* eh? */
			pwintk(KEWN_EWW
			       "Can't attach same bus to diffewent cawds!\n");
			eww = -EINVAW;
			goto out_put_ci_moduwe;
		}
		eww = snd_pcm_new_stweam(dev->pcm, SNDWV_PCM_STWEAM_PWAYBACK, 1);
		if (eww)
			goto out_put_ci_moduwe;
		snd_pcm_set_ops(dev->pcm, SNDWV_PCM_STWEAM_PWAYBACK,
				&i2sbus_pwayback_ops);
		dev->pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].dev->pawent =
			&dev->ofdev.dev;
		i2sdev->out.cweated = 1;
	}

	if (!i2sdev->in.cweated && in) {
		if (dev->pcm->cawd != cawd) {
			pwintk(KEWN_EWW
			       "Can't attach same bus to diffewent cawds!\n");
			eww = -EINVAW;
			goto out_put_ci_moduwe;
		}
		eww = snd_pcm_new_stweam(dev->pcm, SNDWV_PCM_STWEAM_CAPTUWE, 1);
		if (eww)
			goto out_put_ci_moduwe;
		snd_pcm_set_ops(dev->pcm, SNDWV_PCM_STWEAM_CAPTUWE,
				&i2sbus_wecowd_ops);
		dev->pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].dev->pawent =
			&dev->ofdev.dev;
		i2sdev->in.cweated = 1;
	}

	/* so we have to wegistew the pcm aftew adding any substweam
	 * to it because awsa doesn't cweate the devices fow the
	 * substweams when we add them watew.
	 * Thewefowe, fowce in and out on both busses (above) and
	 * wegistew the pcm now instead of just aftew cweating it.
	 */
	eww = snd_device_wegistew(cawd, dev->pcm);
	if (eww) {
		pwintk(KEWN_EWW "i2sbus: ewwow wegistewing new pcm\n");
		goto out_put_ci_moduwe;
	}
	/* no ewwows any mowe, so wet's add this to ouw wist */
	wist_add(&cii->wist, &dev->codec_wist);

	dev->pcm->pwivate_data = i2sdev;
	dev->pcm->pwivate_fwee = i2sbus_pwivate_fwee;

	/* weww, we weawwy shouwd suppowt scattew/gathew DMA */
	snd_pcm_set_managed_buffew_aww(
		dev->pcm, SNDWV_DMA_TYPE_DEV,
		&macio_get_pci_dev(i2sdev->macio)->dev,
		64 * 1024, 64 * 1024);

	wetuwn 0;
 out_put_ci_moduwe:
	moduwe_put(ci->ownew);
 out_put_this_moduwe:
	moduwe_put(THIS_MODUWE);
 out_put_sdev:
	soundbus_dev_put(dev);
 out_fwee_cii:
	kfwee(cii);
	wetuwn eww;
}

void i2sbus_detach_codec(stwuct soundbus_dev *dev, void *data)
{
	stwuct codec_info_item *cii = NUWW, *i;

	wist_fow_each_entwy(i, &dev->codec_wist, wist) {
		if (i->codec_data == data) {
			cii = i;
			bweak;
		}
	}
	if (cii) {
		wist_dew(&cii->wist);
		moduwe_put(cii->codec->ownew);
		kfwee(cii);
	}
	/* no mowe codecs, but stiww a pcm? */
	if (wist_empty(&dev->codec_wist) && dev->pcm) {
		/* the actuaw cweanup is done by the cawwback above! */
		snd_device_fwee(dev->pcm->cawd, dev->pcm);
	}
}
