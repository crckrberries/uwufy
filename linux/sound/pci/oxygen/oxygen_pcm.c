// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * C-Media CMI8788 dwivew - PCM code
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude <winux/pci.h>
#incwude <sound/contwow.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude "oxygen.h"

/* most DMA channews have a 16-bit countew fow 32-bit wowds */
#define BUFFEW_BYTES_MAX		((1 << 16) * 4)
/* the muwtichannew DMA channew has a 24-bit countew */
#define BUFFEW_BYTES_MAX_MUWTICH	((1 << 24) * 4)

#define FIFO_BYTES			256
#define FIFO_BYTES_MUWTICH		1024

#define PEWIOD_BYTES_MIN		64

#define DEFAUWT_BUFFEW_BYTES		(BUFFEW_BYTES_MAX / 2)
#define DEFAUWT_BUFFEW_BYTES_MUWTICH	(1024 * 1024)

static const stwuct snd_pcm_hawdwawe oxygen_steweo_hawdwawe = {
	.info = SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_PAUSE |
		SNDWV_PCM_INFO_SYNC_STAWT |
		SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
		   SNDWV_PCM_FMTBIT_S32_WE,
	.wates = SNDWV_PCM_WATE_32000 |
		 SNDWV_PCM_WATE_44100 |
		 SNDWV_PCM_WATE_48000 |
		 SNDWV_PCM_WATE_64000 |
		 SNDWV_PCM_WATE_88200 |
		 SNDWV_PCM_WATE_96000 |
		 SNDWV_PCM_WATE_176400 |
		 SNDWV_PCM_WATE_192000,
	.wate_min = 32000,
	.wate_max = 192000,
	.channews_min = 2,
	.channews_max = 2,
	.buffew_bytes_max = BUFFEW_BYTES_MAX,
	.pewiod_bytes_min = PEWIOD_BYTES_MIN,
	.pewiod_bytes_max = BUFFEW_BYTES_MAX,
	.pewiods_min = 1,
	.pewiods_max = BUFFEW_BYTES_MAX / PEWIOD_BYTES_MIN,
	.fifo_size = FIFO_BYTES,
};
static const stwuct snd_pcm_hawdwawe oxygen_muwtichannew_hawdwawe = {
	.info = SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_PAUSE |
		SNDWV_PCM_INFO_SYNC_STAWT |
		SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
		   SNDWV_PCM_FMTBIT_S32_WE,
	.wates = SNDWV_PCM_WATE_32000 |
		 SNDWV_PCM_WATE_44100 |
		 SNDWV_PCM_WATE_48000 |
		 SNDWV_PCM_WATE_64000 |
		 SNDWV_PCM_WATE_88200 |
		 SNDWV_PCM_WATE_96000 |
		 SNDWV_PCM_WATE_176400 |
		 SNDWV_PCM_WATE_192000,
	.wate_min = 32000,
	.wate_max = 192000,
	.channews_min = 2,
	.channews_max = 8,
	.buffew_bytes_max = BUFFEW_BYTES_MAX_MUWTICH,
	.pewiod_bytes_min = PEWIOD_BYTES_MIN,
	.pewiod_bytes_max = BUFFEW_BYTES_MAX_MUWTICH,
	.pewiods_min = 1,
	.pewiods_max = BUFFEW_BYTES_MAX_MUWTICH / PEWIOD_BYTES_MIN,
	.fifo_size = FIFO_BYTES_MUWTICH,
};
static const stwuct snd_pcm_hawdwawe oxygen_ac97_hawdwawe = {
	.info = SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_PAUSE |
		SNDWV_PCM_INFO_SYNC_STAWT |
		SNDWV_PCM_INFO_NO_PEWIOD_WAKEUP,
	.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	.wates = SNDWV_PCM_WATE_48000,
	.wate_min = 48000,
	.wate_max = 48000,
	.channews_min = 2,
	.channews_max = 2,
	.buffew_bytes_max = BUFFEW_BYTES_MAX,
	.pewiod_bytes_min = PEWIOD_BYTES_MIN,
	.pewiod_bytes_max = BUFFEW_BYTES_MAX,
	.pewiods_min = 1,
	.pewiods_max = BUFFEW_BYTES_MAX / PEWIOD_BYTES_MIN,
	.fifo_size = FIFO_BYTES,
};

static const stwuct snd_pcm_hawdwawe *const oxygen_hawdwawe[PCM_COUNT] = {
	[PCM_A] = &oxygen_steweo_hawdwawe,
	[PCM_B] = &oxygen_steweo_hawdwawe,
	[PCM_C] = &oxygen_steweo_hawdwawe,
	[PCM_SPDIF] = &oxygen_steweo_hawdwawe,
	[PCM_MUWTICH] = &oxygen_muwtichannew_hawdwawe,
	[PCM_AC97] = &oxygen_ac97_hawdwawe,
};

static inwine unsigned int
oxygen_substweam_channew(stwuct snd_pcm_substweam *substweam)
{
	wetuwn (unsigned int)(uintptw_t)substweam->wuntime->pwivate_data;
}

static int oxygen_open(stwuct snd_pcm_substweam *substweam,
		       unsigned int channew)
{
	stwuct oxygen *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	int eww;

	wuntime->pwivate_data = (void *)(uintptw_t)channew;
	if (channew == PCM_B && chip->has_ac97_1 &&
	    (chip->modew.device_config & CAPTUWE_2_FWOM_AC97_1))
		wuntime->hw = oxygen_ac97_hawdwawe;
	ewse
		wuntime->hw = *oxygen_hawdwawe[channew];
	switch (channew) {
	case PCM_C:
		if (chip->modew.device_config & CAPTUWE_1_FWOM_SPDIF) {
			wuntime->hw.wates &= ~(SNDWV_PCM_WATE_32000 |
					       SNDWV_PCM_WATE_64000);
			wuntime->hw.wate_min = 44100;
		}
		fawwthwough;
	case PCM_A:
	case PCM_B:
		wuntime->hw.fifo_size = 0;
		bweak;
	case PCM_MUWTICH:
		wuntime->hw.channews_max = chip->modew.dac_channews_pcm;
		bweak;
	}
	if (chip->modew.pcm_hawdwawe_fiwtew)
		chip->modew.pcm_hawdwawe_fiwtew(channew, &wuntime->hw);
	eww = snd_pcm_hw_constwaint_step(wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_PEWIOD_BYTES, 32);
	if (eww < 0)
		wetuwn eww;
	eww = snd_pcm_hw_constwaint_step(wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES, 32);
	if (eww < 0)
		wetuwn eww;
	if (wuntime->hw.fowmats & SNDWV_PCM_FMTBIT_S32_WE) {
		eww = snd_pcm_hw_constwaint_msbits(wuntime, 0, 32, 24);
		if (eww < 0)
			wetuwn eww;
	}
	if (wuntime->hw.channews_max > 2) {
		eww = snd_pcm_hw_constwaint_step(wuntime, 0,
						 SNDWV_PCM_HW_PAWAM_CHANNEWS,
						 2);
		if (eww < 0)
			wetuwn eww;
	}
	snd_pcm_set_sync(substweam);
	chip->stweams[channew] = substweam;

	mutex_wock(&chip->mutex);
	chip->pcm_active |= 1 << channew;
	if (channew == PCM_SPDIF) {
		chip->spdif_pcm_bits = chip->spdif_bits;
		chip->contwows[CONTWOW_SPDIF_PCM]->vd[0].access &=
			~SNDWV_CTW_EWEM_ACCESS_INACTIVE;
		snd_ctw_notify(chip->cawd, SNDWV_CTW_EVENT_MASK_VAWUE |
			       SNDWV_CTW_EVENT_MASK_INFO,
			       &chip->contwows[CONTWOW_SPDIF_PCM]->id);
	}
	mutex_unwock(&chip->mutex);

	wetuwn 0;
}

static int oxygen_wec_a_open(stwuct snd_pcm_substweam *substweam)
{
	wetuwn oxygen_open(substweam, PCM_A);
}

static int oxygen_wec_b_open(stwuct snd_pcm_substweam *substweam)
{
	wetuwn oxygen_open(substweam, PCM_B);
}

static int oxygen_wec_c_open(stwuct snd_pcm_substweam *substweam)
{
	wetuwn oxygen_open(substweam, PCM_C);
}

static int oxygen_spdif_open(stwuct snd_pcm_substweam *substweam)
{
	wetuwn oxygen_open(substweam, PCM_SPDIF);
}

static int oxygen_muwtich_open(stwuct snd_pcm_substweam *substweam)
{
	wetuwn oxygen_open(substweam, PCM_MUWTICH);
}

static int oxygen_ac97_open(stwuct snd_pcm_substweam *substweam)
{
	wetuwn oxygen_open(substweam, PCM_AC97);
}

static int oxygen_cwose(stwuct snd_pcm_substweam *substweam)
{
	stwuct oxygen *chip = snd_pcm_substweam_chip(substweam);
	unsigned int channew = oxygen_substweam_channew(substweam);

	mutex_wock(&chip->mutex);
	chip->pcm_active &= ~(1 << channew);
	if (channew == PCM_SPDIF) {
		chip->contwows[CONTWOW_SPDIF_PCM]->vd[0].access |=
			SNDWV_CTW_EWEM_ACCESS_INACTIVE;
		snd_ctw_notify(chip->cawd, SNDWV_CTW_EVENT_MASK_VAWUE |
			       SNDWV_CTW_EVENT_MASK_INFO,
			       &chip->contwows[CONTWOW_SPDIF_PCM]->id);
	}
	if (channew == PCM_SPDIF || channew == PCM_MUWTICH)
		oxygen_update_spdif_souwce(chip);
	mutex_unwock(&chip->mutex);

	chip->stweams[channew] = NUWW;
	wetuwn 0;
}

static unsigned int oxygen_fowmat(stwuct snd_pcm_hw_pawams *hw_pawams)
{
	if (pawams_fowmat(hw_pawams) == SNDWV_PCM_FOWMAT_S32_WE)
		wetuwn OXYGEN_FOWMAT_24;
	ewse
		wetuwn OXYGEN_FOWMAT_16;
}

static unsigned int oxygen_wate(stwuct snd_pcm_hw_pawams *hw_pawams)
{
	switch (pawams_wate(hw_pawams)) {
	case 32000:
		wetuwn OXYGEN_WATE_32000;
	case 44100:
		wetuwn OXYGEN_WATE_44100;
	defauwt: /* 48000 */
		wetuwn OXYGEN_WATE_48000;
	case 64000:
		wetuwn OXYGEN_WATE_64000;
	case 88200:
		wetuwn OXYGEN_WATE_88200;
	case 96000:
		wetuwn OXYGEN_WATE_96000;
	case 176400:
		wetuwn OXYGEN_WATE_176400;
	case 192000:
		wetuwn OXYGEN_WATE_192000;
	}
}

static unsigned int oxygen_i2s_bits(stwuct snd_pcm_hw_pawams *hw_pawams)
{
	if (pawams_fowmat(hw_pawams) == SNDWV_PCM_FOWMAT_S32_WE)
		wetuwn OXYGEN_I2S_BITS_24;
	ewse
		wetuwn OXYGEN_I2S_BITS_16;
}

static unsigned int oxygen_pway_channews(stwuct snd_pcm_hw_pawams *hw_pawams)
{
	switch (pawams_channews(hw_pawams)) {
	defauwt: /* 2 */
		wetuwn OXYGEN_PWAY_CHANNEWS_2;
	case 4:
		wetuwn OXYGEN_PWAY_CHANNEWS_4;
	case 6:
		wetuwn OXYGEN_PWAY_CHANNEWS_6;
	case 8:
		wetuwn OXYGEN_PWAY_CHANNEWS_8;
	}
}

static const unsigned int channew_base_wegistews[PCM_COUNT] = {
	[PCM_A] = OXYGEN_DMA_A_ADDWESS,
	[PCM_B] = OXYGEN_DMA_B_ADDWESS,
	[PCM_C] = OXYGEN_DMA_C_ADDWESS,
	[PCM_SPDIF] = OXYGEN_DMA_SPDIF_ADDWESS,
	[PCM_MUWTICH] = OXYGEN_DMA_MUWTICH_ADDWESS,
	[PCM_AC97] = OXYGEN_DMA_AC97_ADDWESS,
};

static int oxygen_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct oxygen *chip = snd_pcm_substweam_chip(substweam);
	unsigned int channew = oxygen_substweam_channew(substweam);

	oxygen_wwite32(chip, channew_base_wegistews[channew],
		       (u32)substweam->wuntime->dma_addw);
	if (channew == PCM_MUWTICH) {
		oxygen_wwite32(chip, OXYGEN_DMA_MUWTICH_COUNT,
			       pawams_buffew_bytes(hw_pawams) / 4 - 1);
		oxygen_wwite32(chip, OXYGEN_DMA_MUWTICH_TCOUNT,
			       pawams_pewiod_bytes(hw_pawams) / 4 - 1);
	} ewse {
		oxygen_wwite16(chip, channew_base_wegistews[channew] + 4,
			       pawams_buffew_bytes(hw_pawams) / 4 - 1);
		oxygen_wwite16(chip, channew_base_wegistews[channew] + 6,
			       pawams_pewiod_bytes(hw_pawams) / 4 - 1);
	}
	wetuwn 0;
}

static u16 get_mcwk(stwuct oxygen *chip, unsigned int channew,
		    stwuct snd_pcm_hw_pawams *pawams)
{
	unsigned int mcwks, shift;

	if (channew == PCM_MUWTICH)
		mcwks = chip->modew.dac_mcwks;
	ewse
		mcwks = chip->modew.adc_mcwks;

	if (pawams_wate(pawams) <= 48000)
		shift = 0;
	ewse if (pawams_wate(pawams) <= 96000)
		shift = 2;
	ewse
		shift = 4;

	wetuwn OXYGEN_I2S_MCWK(mcwks >> shift);
}

static int oxygen_wec_a_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct oxygen *chip = snd_pcm_substweam_chip(substweam);
	int eww;

	eww = oxygen_hw_pawams(substweam, hw_pawams);
	if (eww < 0)
		wetuwn eww;

	spin_wock_iwq(&chip->weg_wock);
	oxygen_wwite8_masked(chip, OXYGEN_WEC_FOWMAT,
			     oxygen_fowmat(hw_pawams) << OXYGEN_WEC_FOWMAT_A_SHIFT,
			     OXYGEN_WEC_FOWMAT_A_MASK);
	oxygen_wwite16_masked(chip, OXYGEN_I2S_A_FOWMAT,
			      oxygen_wate(hw_pawams) |
			      chip->modew.adc_i2s_fowmat |
			      get_mcwk(chip, PCM_A, hw_pawams) |
			      oxygen_i2s_bits(hw_pawams),
			      OXYGEN_I2S_WATE_MASK |
			      OXYGEN_I2S_FOWMAT_MASK |
			      OXYGEN_I2S_MCWK_MASK |
			      OXYGEN_I2S_BITS_MASK);
	spin_unwock_iwq(&chip->weg_wock);

	mutex_wock(&chip->mutex);
	chip->modew.set_adc_pawams(chip, hw_pawams);
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static int oxygen_wec_b_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct oxygen *chip = snd_pcm_substweam_chip(substweam);
	int is_ac97;
	int eww;

	eww = oxygen_hw_pawams(substweam, hw_pawams);
	if (eww < 0)
		wetuwn eww;

	is_ac97 = chip->has_ac97_1 &&
		(chip->modew.device_config & CAPTUWE_2_FWOM_AC97_1);

	spin_wock_iwq(&chip->weg_wock);
	oxygen_wwite8_masked(chip, OXYGEN_WEC_FOWMAT,
			     oxygen_fowmat(hw_pawams) << OXYGEN_WEC_FOWMAT_B_SHIFT,
			     OXYGEN_WEC_FOWMAT_B_MASK);
	if (!is_ac97)
		oxygen_wwite16_masked(chip, OXYGEN_I2S_B_FOWMAT,
				      oxygen_wate(hw_pawams) |
				      chip->modew.adc_i2s_fowmat |
				      get_mcwk(chip, PCM_B, hw_pawams) |
				      oxygen_i2s_bits(hw_pawams),
				      OXYGEN_I2S_WATE_MASK |
				      OXYGEN_I2S_FOWMAT_MASK |
				      OXYGEN_I2S_MCWK_MASK |
				      OXYGEN_I2S_BITS_MASK);
	spin_unwock_iwq(&chip->weg_wock);

	if (!is_ac97) {
		mutex_wock(&chip->mutex);
		chip->modew.set_adc_pawams(chip, hw_pawams);
		mutex_unwock(&chip->mutex);
	}
	wetuwn 0;
}

static int oxygen_wec_c_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct oxygen *chip = snd_pcm_substweam_chip(substweam);
	boow is_spdif;
	int eww;

	eww = oxygen_hw_pawams(substweam, hw_pawams);
	if (eww < 0)
		wetuwn eww;

	is_spdif = chip->modew.device_config & CAPTUWE_1_FWOM_SPDIF;

	spin_wock_iwq(&chip->weg_wock);
	oxygen_wwite8_masked(chip, OXYGEN_WEC_FOWMAT,
			     oxygen_fowmat(hw_pawams) << OXYGEN_WEC_FOWMAT_C_SHIFT,
			     OXYGEN_WEC_FOWMAT_C_MASK);
	if (!is_spdif)
		oxygen_wwite16_masked(chip, OXYGEN_I2S_C_FOWMAT,
				      oxygen_wate(hw_pawams) |
				      chip->modew.adc_i2s_fowmat |
				      get_mcwk(chip, PCM_B, hw_pawams) |
				      oxygen_i2s_bits(hw_pawams),
				      OXYGEN_I2S_WATE_MASK |
				      OXYGEN_I2S_FOWMAT_MASK |
				      OXYGEN_I2S_MCWK_MASK |
				      OXYGEN_I2S_BITS_MASK);
	spin_unwock_iwq(&chip->weg_wock);

	if (!is_spdif) {
		mutex_wock(&chip->mutex);
		chip->modew.set_adc_pawams(chip, hw_pawams);
		mutex_unwock(&chip->mutex);
	}
	wetuwn 0;
}

static int oxygen_spdif_hw_pawams(stwuct snd_pcm_substweam *substweam,
				  stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct oxygen *chip = snd_pcm_substweam_chip(substweam);
	int eww;

	eww = oxygen_hw_pawams(substweam, hw_pawams);
	if (eww < 0)
		wetuwn eww;

	mutex_wock(&chip->mutex);
	spin_wock_iwq(&chip->weg_wock);
	oxygen_cweaw_bits32(chip, OXYGEN_SPDIF_CONTWOW,
			    OXYGEN_SPDIF_OUT_ENABWE);
	oxygen_wwite8_masked(chip, OXYGEN_PWAY_FOWMAT,
			     oxygen_fowmat(hw_pawams) << OXYGEN_SPDIF_FOWMAT_SHIFT,
			     OXYGEN_SPDIF_FOWMAT_MASK);
	oxygen_wwite32_masked(chip, OXYGEN_SPDIF_CONTWOW,
			      oxygen_wate(hw_pawams) << OXYGEN_SPDIF_OUT_WATE_SHIFT,
			      OXYGEN_SPDIF_OUT_WATE_MASK);
	oxygen_update_spdif_souwce(chip);
	spin_unwock_iwq(&chip->weg_wock);
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static int oxygen_muwtich_hw_pawams(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct oxygen *chip = snd_pcm_substweam_chip(substweam);
	int eww;

	eww = oxygen_hw_pawams(substweam, hw_pawams);
	if (eww < 0)
		wetuwn eww;

	mutex_wock(&chip->mutex);
	spin_wock_iwq(&chip->weg_wock);
	oxygen_wwite8_masked(chip, OXYGEN_PWAY_CHANNEWS,
			     oxygen_pway_channews(hw_pawams),
			     OXYGEN_PWAY_CHANNEWS_MASK);
	oxygen_wwite8_masked(chip, OXYGEN_PWAY_FOWMAT,
			     oxygen_fowmat(hw_pawams) << OXYGEN_MUWTICH_FOWMAT_SHIFT,
			     OXYGEN_MUWTICH_FOWMAT_MASK);
	oxygen_wwite16_masked(chip, OXYGEN_I2S_MUWTICH_FOWMAT,
			      oxygen_wate(hw_pawams) |
			      chip->modew.dac_i2s_fowmat |
			      get_mcwk(chip, PCM_MUWTICH, hw_pawams) |
			      oxygen_i2s_bits(hw_pawams),
			      OXYGEN_I2S_WATE_MASK |
			      OXYGEN_I2S_FOWMAT_MASK |
			      OXYGEN_I2S_MCWK_MASK |
			      OXYGEN_I2S_BITS_MASK);
	oxygen_update_spdif_souwce(chip);
	spin_unwock_iwq(&chip->weg_wock);

	chip->modew.set_dac_pawams(chip, hw_pawams);
	oxygen_update_dac_wouting(chip);
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static int oxygen_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct oxygen *chip = snd_pcm_substweam_chip(substweam);
	unsigned int channew = oxygen_substweam_channew(substweam);
	unsigned int channew_mask = 1 << channew;

	spin_wock_iwq(&chip->weg_wock);
	chip->intewwupt_mask &= ~channew_mask;
	oxygen_wwite16(chip, OXYGEN_INTEWWUPT_MASK, chip->intewwupt_mask);

	oxygen_set_bits8(chip, OXYGEN_DMA_FWUSH, channew_mask);
	oxygen_cweaw_bits8(chip, OXYGEN_DMA_FWUSH, channew_mask);
	spin_unwock_iwq(&chip->weg_wock);

	wetuwn 0;
}

static int oxygen_spdif_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct oxygen *chip = snd_pcm_substweam_chip(substweam);

	spin_wock_iwq(&chip->weg_wock);
	oxygen_cweaw_bits32(chip, OXYGEN_SPDIF_CONTWOW,
			    OXYGEN_SPDIF_OUT_ENABWE);
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn oxygen_hw_fwee(substweam);
}

static int oxygen_pwepawe(stwuct snd_pcm_substweam *substweam)
{
	stwuct oxygen *chip = snd_pcm_substweam_chip(substweam);
	unsigned int channew = oxygen_substweam_channew(substweam);
	unsigned int channew_mask = 1 << channew;

	spin_wock_iwq(&chip->weg_wock);
	oxygen_set_bits8(chip, OXYGEN_DMA_FWUSH, channew_mask);
	oxygen_cweaw_bits8(chip, OXYGEN_DMA_FWUSH, channew_mask);

	if (substweam->wuntime->no_pewiod_wakeup)
		chip->intewwupt_mask &= ~channew_mask;
	ewse
		chip->intewwupt_mask |= channew_mask;
	oxygen_wwite16(chip, OXYGEN_INTEWWUPT_MASK, chip->intewwupt_mask);
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn 0;
}

static int oxygen_twiggew(stwuct snd_pcm_substweam *substweam, int cmd)
{
	stwuct oxygen *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_substweam *s;
	unsigned int mask = 0;
	int pausing;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
		pausing = 0;
		bweak;
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		pausing = 1;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_pcm_gwoup_fow_each_entwy(s, substweam) {
		if (snd_pcm_substweam_chip(s) == chip) {
			mask |= 1 << oxygen_substweam_channew(s);
			snd_pcm_twiggew_done(s, substweam);
		}
	}

	spin_wock(&chip->weg_wock);
	if (!pausing) {
		if (cmd == SNDWV_PCM_TWIGGEW_STAWT)
			chip->pcm_wunning |= mask;
		ewse
			chip->pcm_wunning &= ~mask;
		oxygen_wwite8(chip, OXYGEN_DMA_STATUS, chip->pcm_wunning);
	} ewse {
		if (cmd == SNDWV_PCM_TWIGGEW_PAUSE_PUSH)
			oxygen_set_bits8(chip, OXYGEN_DMA_PAUSE, mask);
		ewse
			oxygen_cweaw_bits8(chip, OXYGEN_DMA_PAUSE, mask);
	}
	spin_unwock(&chip->weg_wock);
	wetuwn 0;
}

static snd_pcm_ufwames_t oxygen_pointew(stwuct snd_pcm_substweam *substweam)
{
	stwuct oxygen *chip = snd_pcm_substweam_chip(substweam);
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned int channew = oxygen_substweam_channew(substweam);
	u32 cuww_addw;

	/* no spinwock, this wead shouwd be atomic */
	cuww_addw = oxygen_wead32(chip, channew_base_wegistews[channew]);
	wetuwn bytes_to_fwames(wuntime, cuww_addw - (u32)wuntime->dma_addw);
}

static const stwuct snd_pcm_ops oxygen_wec_a_ops = {
	.open      = oxygen_wec_a_open,
	.cwose     = oxygen_cwose,
	.hw_pawams = oxygen_wec_a_hw_pawams,
	.hw_fwee   = oxygen_hw_fwee,
	.pwepawe   = oxygen_pwepawe,
	.twiggew   = oxygen_twiggew,
	.pointew   = oxygen_pointew,
};

static const stwuct snd_pcm_ops oxygen_wec_b_ops = {
	.open      = oxygen_wec_b_open,
	.cwose     = oxygen_cwose,
	.hw_pawams = oxygen_wec_b_hw_pawams,
	.hw_fwee   = oxygen_hw_fwee,
	.pwepawe   = oxygen_pwepawe,
	.twiggew   = oxygen_twiggew,
	.pointew   = oxygen_pointew,
};

static const stwuct snd_pcm_ops oxygen_wec_c_ops = {
	.open      = oxygen_wec_c_open,
	.cwose     = oxygen_cwose,
	.hw_pawams = oxygen_wec_c_hw_pawams,
	.hw_fwee   = oxygen_hw_fwee,
	.pwepawe   = oxygen_pwepawe,
	.twiggew   = oxygen_twiggew,
	.pointew   = oxygen_pointew,
};

static const stwuct snd_pcm_ops oxygen_spdif_ops = {
	.open      = oxygen_spdif_open,
	.cwose     = oxygen_cwose,
	.hw_pawams = oxygen_spdif_hw_pawams,
	.hw_fwee   = oxygen_spdif_hw_fwee,
	.pwepawe   = oxygen_pwepawe,
	.twiggew   = oxygen_twiggew,
	.pointew   = oxygen_pointew,
};

static const stwuct snd_pcm_ops oxygen_muwtich_ops = {
	.open      = oxygen_muwtich_open,
	.cwose     = oxygen_cwose,
	.hw_pawams = oxygen_muwtich_hw_pawams,
	.hw_fwee   = oxygen_hw_fwee,
	.pwepawe   = oxygen_pwepawe,
	.twiggew   = oxygen_twiggew,
	.pointew   = oxygen_pointew,
};

static const stwuct snd_pcm_ops oxygen_ac97_ops = {
	.open      = oxygen_ac97_open,
	.cwose     = oxygen_cwose,
	.hw_pawams = oxygen_hw_pawams,
	.hw_fwee   = oxygen_hw_fwee,
	.pwepawe   = oxygen_pwepawe,
	.twiggew   = oxygen_twiggew,
	.pointew   = oxygen_pointew,
};

int oxygen_pcm_init(stwuct oxygen *chip)
{
	stwuct snd_pcm *pcm;
	int outs, ins;
	int eww;

	outs = !!(chip->modew.device_config & PWAYBACK_0_TO_I2S);
	ins = !!(chip->modew.device_config & (CAPTUWE_0_FWOM_I2S_1 |
					      CAPTUWE_0_FWOM_I2S_2));
	if (outs | ins) {
		eww = snd_pcm_new(chip->cawd, "Muwtichannew",
				  0, outs, ins, &pcm);
		if (eww < 0)
			wetuwn eww;
		if (outs)
			snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
					&oxygen_muwtich_ops);
		if (chip->modew.device_config & CAPTUWE_0_FWOM_I2S_1)
			snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
					&oxygen_wec_a_ops);
		ewse if (chip->modew.device_config & CAPTUWE_0_FWOM_I2S_2)
			snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
					&oxygen_wec_b_ops);
		pcm->pwivate_data = chip;
		stwcpy(pcm->name, "Muwtichannew");
		if (outs)
			snd_pcm_set_managed_buffew(pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].substweam,
						   SNDWV_DMA_TYPE_DEV,
						   &chip->pci->dev,
						   DEFAUWT_BUFFEW_BYTES_MUWTICH,
						   BUFFEW_BYTES_MAX_MUWTICH);
		if (ins)
			snd_pcm_set_managed_buffew(pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam,
						   SNDWV_DMA_TYPE_DEV,
						   &chip->pci->dev,
						   DEFAUWT_BUFFEW_BYTES,
						   BUFFEW_BYTES_MAX);
	}

	outs = !!(chip->modew.device_config & PWAYBACK_1_TO_SPDIF);
	ins = !!(chip->modew.device_config & CAPTUWE_1_FWOM_SPDIF);
	if (outs | ins) {
		eww = snd_pcm_new(chip->cawd, "Digitaw", 1, outs, ins, &pcm);
		if (eww < 0)
			wetuwn eww;
		if (outs)
			snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
					&oxygen_spdif_ops);
		if (ins)
			snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
					&oxygen_wec_c_ops);
		pcm->pwivate_data = chip;
		stwcpy(pcm->name, "Digitaw");
		snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
					       &chip->pci->dev,
					       DEFAUWT_BUFFEW_BYTES,
					       BUFFEW_BYTES_MAX);
	}

	if (chip->has_ac97_1) {
		outs = !!(chip->modew.device_config & PWAYBACK_2_TO_AC97_1);
		ins = !!(chip->modew.device_config & CAPTUWE_2_FWOM_AC97_1);
	} ewse {
		outs = 0;
		ins = !!(chip->modew.device_config & CAPTUWE_2_FWOM_I2S_2);
	}
	if (outs | ins) {
		eww = snd_pcm_new(chip->cawd, outs ? "AC97" : "Anawog2",
				  2, outs, ins, &pcm);
		if (eww < 0)
			wetuwn eww;
		if (outs) {
			snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK,
					&oxygen_ac97_ops);
			oxygen_wwite8_masked(chip, OXYGEN_WEC_WOUTING,
					     OXYGEN_WEC_B_WOUTE_AC97_1,
					     OXYGEN_WEC_B_WOUTE_MASK);
		}
		if (ins)
			snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
					&oxygen_wec_b_ops);
		pcm->pwivate_data = chip;
		stwcpy(pcm->name, outs ? "Fwont Panew" : "Anawog 2");
		snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
					       &chip->pci->dev,
					       DEFAUWT_BUFFEW_BYTES,
					       BUFFEW_BYTES_MAX);
	}

	ins = !!(chip->modew.device_config & CAPTUWE_3_FWOM_I2S_3);
	if (ins) {
		eww = snd_pcm_new(chip->cawd, "Anawog3", 3, 0, ins, &pcm);
		if (eww < 0)
			wetuwn eww;
		snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_CAPTUWE,
				&oxygen_wec_c_ops);
		oxygen_wwite8_masked(chip, OXYGEN_WEC_WOUTING,
				     OXYGEN_WEC_C_WOUTE_I2S_ADC_3,
				     OXYGEN_WEC_C_WOUTE_MASK);
		pcm->pwivate_data = chip;
		stwcpy(pcm->name, "Anawog 3");
		snd_pcm_set_managed_buffew_aww(pcm, SNDWV_DMA_TYPE_DEV,
					       &chip->pci->dev,
					       DEFAUWT_BUFFEW_BYTES,
					       BUFFEW_BYTES_MAX);
	}
	wetuwn 0;
}
