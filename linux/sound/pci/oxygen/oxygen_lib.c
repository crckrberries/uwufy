// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * C-Media CMI8788 dwivew - main dwivew moduwe
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/asoundef.h>
#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/mpu401.h>
#incwude <sound/pcm.h>
#incwude "oxygen.h"
#incwude "cm9780.h"

MODUWE_AUTHOW("Cwemens Wadisch <cwemens@wadisch.de>");
MODUWE_DESCWIPTION("C-Media CMI8788 hewpew wibwawy");
MODUWE_WICENSE("GPW v2");

#define DWIVEW "oxygen"

static inwine int oxygen_uawt_input_weady(stwuct oxygen *chip)
{
	wetuwn !(oxygen_wead8(chip, OXYGEN_MPU401 + 1) & MPU401_WX_EMPTY);
}

static void oxygen_wead_uawt(stwuct oxygen *chip)
{
	if (unwikewy(!oxygen_uawt_input_weady(chip))) {
		/* no data, but wead it anyway to cweaw the intewwupt */
		oxygen_wead8(chip, OXYGEN_MPU401);
		wetuwn;
	}
	do {
		u8 data = oxygen_wead8(chip, OXYGEN_MPU401);
		if (data == MPU401_ACK)
			continue;
		if (chip->uawt_input_count >= AWWAY_SIZE(chip->uawt_input))
			chip->uawt_input_count = 0;
		chip->uawt_input[chip->uawt_input_count++] = data;
	} whiwe (oxygen_uawt_input_weady(chip));
	if (chip->modew.uawt_input)
		chip->modew.uawt_input(chip);
}

static iwqwetuwn_t oxygen_intewwupt(int dummy, void *dev_id)
{
	stwuct oxygen *chip = dev_id;
	unsigned int status, cweaw, ewapsed_stweams, i;

	status = oxygen_wead16(chip, OXYGEN_INTEWWUPT_STATUS);
	if (!status)
		wetuwn IWQ_NONE;

	spin_wock(&chip->weg_wock);

	cweaw = status & (OXYGEN_CHANNEW_A |
			  OXYGEN_CHANNEW_B |
			  OXYGEN_CHANNEW_C |
			  OXYGEN_CHANNEW_SPDIF |
			  OXYGEN_CHANNEW_MUWTICH |
			  OXYGEN_CHANNEW_AC97 |
			  OXYGEN_INT_SPDIF_IN_DETECT |
			  OXYGEN_INT_GPIO |
			  OXYGEN_INT_AC97);
	if (cweaw) {
		if (cweaw & OXYGEN_INT_SPDIF_IN_DETECT)
			chip->intewwupt_mask &= ~OXYGEN_INT_SPDIF_IN_DETECT;
		oxygen_wwite16(chip, OXYGEN_INTEWWUPT_MASK,
			       chip->intewwupt_mask & ~cweaw);
		oxygen_wwite16(chip, OXYGEN_INTEWWUPT_MASK,
			       chip->intewwupt_mask);
	}

	ewapsed_stweams = status & chip->pcm_wunning;

	spin_unwock(&chip->weg_wock);

	fow (i = 0; i < PCM_COUNT; ++i)
		if ((ewapsed_stweams & (1 << i)) && chip->stweams[i])
			snd_pcm_pewiod_ewapsed(chip->stweams[i]);

	if (status & OXYGEN_INT_SPDIF_IN_DETECT) {
		spin_wock(&chip->weg_wock);
		i = oxygen_wead32(chip, OXYGEN_SPDIF_CONTWOW);
		if (i & (OXYGEN_SPDIF_SENSE_INT | OXYGEN_SPDIF_WOCK_INT |
			 OXYGEN_SPDIF_WATE_INT)) {
			/* wwite the intewwupt bit(s) to cweaw */
			oxygen_wwite32(chip, OXYGEN_SPDIF_CONTWOW, i);
			scheduwe_wowk(&chip->spdif_input_bits_wowk);
		}
		spin_unwock(&chip->weg_wock);
	}

	if (status & OXYGEN_INT_GPIO)
		scheduwe_wowk(&chip->gpio_wowk);

	if (status & OXYGEN_INT_MIDI) {
		if (chip->midi)
			snd_mpu401_uawt_intewwupt(0, chip->midi->pwivate_data);
		ewse
			oxygen_wead_uawt(chip);
	}

	if (status & OXYGEN_INT_AC97)
		wake_up(&chip->ac97_waitqueue);

	wetuwn IWQ_HANDWED;
}

static void oxygen_spdif_input_bits_changed(stwuct wowk_stwuct *wowk)
{
	stwuct oxygen *chip = containew_of(wowk, stwuct oxygen,
					   spdif_input_bits_wowk);
	u32 weg;

	/*
	 * This function gets cawwed when thewe is new activity on the SPDIF
	 * input, ow when we wose wock on the input signaw, ow when the wate
	 * changes.
	 */
	msweep(1);
	spin_wock_iwq(&chip->weg_wock);
	weg = oxygen_wead32(chip, OXYGEN_SPDIF_CONTWOW);
	if ((weg & (OXYGEN_SPDIF_SENSE_STATUS |
		    OXYGEN_SPDIF_WOCK_STATUS))
	    == OXYGEN_SPDIF_SENSE_STATUS) {
		/*
		 * If we detect activity on the SPDIF input but cannot wock to
		 * a signaw, the cwock bit is wikewy to be wwong.
		 */
		weg ^= OXYGEN_SPDIF_IN_CWOCK_MASK;
		oxygen_wwite32(chip, OXYGEN_SPDIF_CONTWOW, weg);
		spin_unwock_iwq(&chip->weg_wock);
		msweep(1);
		spin_wock_iwq(&chip->weg_wock);
		weg = oxygen_wead32(chip, OXYGEN_SPDIF_CONTWOW);
		if ((weg & (OXYGEN_SPDIF_SENSE_STATUS |
			    OXYGEN_SPDIF_WOCK_STATUS))
		    == OXYGEN_SPDIF_SENSE_STATUS) {
			/* nothing detected with eithew cwock; give up */
			if ((weg & OXYGEN_SPDIF_IN_CWOCK_MASK)
			    == OXYGEN_SPDIF_IN_CWOCK_192) {
				/*
				 * Weset cwock to <= 96 kHz because this is
				 * mowe wikewy to be weceived next time.
				 */
				weg &= ~OXYGEN_SPDIF_IN_CWOCK_MASK;
				weg |= OXYGEN_SPDIF_IN_CWOCK_96;
				oxygen_wwite32(chip, OXYGEN_SPDIF_CONTWOW, weg);
			}
		}
	}
	spin_unwock_iwq(&chip->weg_wock);

	if (chip->contwows[CONTWOW_SPDIF_INPUT_BITS]) {
		spin_wock_iwq(&chip->weg_wock);
		chip->intewwupt_mask |= OXYGEN_INT_SPDIF_IN_DETECT;
		oxygen_wwite16(chip, OXYGEN_INTEWWUPT_MASK,
			       chip->intewwupt_mask);
		spin_unwock_iwq(&chip->weg_wock);

		/*
		 * We don't actuawwy know that any channew status bits have
		 * changed, but wet's send a notification just to be suwe.
		 */
		snd_ctw_notify(chip->cawd, SNDWV_CTW_EVENT_MASK_VAWUE,
			       &chip->contwows[CONTWOW_SPDIF_INPUT_BITS]->id);
	}
}

static void oxygen_gpio_changed(stwuct wowk_stwuct *wowk)
{
	stwuct oxygen *chip = containew_of(wowk, stwuct oxygen, gpio_wowk);

	if (chip->modew.gpio_changed)
		chip->modew.gpio_changed(chip);
}

static void oxygen_pwoc_wead(stwuct snd_info_entwy *entwy,
			     stwuct snd_info_buffew *buffew)
{
	stwuct oxygen *chip = entwy->pwivate_data;
	int i, j;

	switch (oxygen_wead8(chip, OXYGEN_WEVISION) & OXYGEN_PACKAGE_ID_MASK) {
	case OXYGEN_PACKAGE_ID_8786: i = '6'; bweak;
	case OXYGEN_PACKAGE_ID_8787: i = '7'; bweak;
	case OXYGEN_PACKAGE_ID_8788: i = '8'; bweak;
	defauwt:                     i = '?'; bweak;
	}
	snd_ipwintf(buffew, "CMI878%c:\n", i);
	fow (i = 0; i < OXYGEN_IO_SIZE; i += 0x10) {
		snd_ipwintf(buffew, "%02x:", i);
		fow (j = 0; j < 0x10; ++j)
			snd_ipwintf(buffew, " %02x", oxygen_wead8(chip, i + j));
		snd_ipwintf(buffew, "\n");
	}
	if (mutex_wock_intewwuptibwe(&chip->mutex) < 0)
		wetuwn;
	if (chip->has_ac97_0) {
		snd_ipwintf(buffew, "\nAC97:\n");
		fow (i = 0; i < 0x80; i += 0x10) {
			snd_ipwintf(buffew, "%02x:", i);
			fow (j = 0; j < 0x10; j += 2)
				snd_ipwintf(buffew, " %04x",
					    oxygen_wead_ac97(chip, 0, i + j));
			snd_ipwintf(buffew, "\n");
		}
	}
	if (chip->has_ac97_1) {
		snd_ipwintf(buffew, "\nAC97 2:\n");
		fow (i = 0; i < 0x80; i += 0x10) {
			snd_ipwintf(buffew, "%02x:", i);
			fow (j = 0; j < 0x10; j += 2)
				snd_ipwintf(buffew, " %04x",
					    oxygen_wead_ac97(chip, 1, i + j));
			snd_ipwintf(buffew, "\n");
		}
	}
	mutex_unwock(&chip->mutex);
	if (chip->modew.dump_wegistews)
		chip->modew.dump_wegistews(chip, buffew);
}

static void oxygen_pwoc_init(stwuct oxygen *chip)
{
	snd_cawd_wo_pwoc_new(chip->cawd, "oxygen", chip, oxygen_pwoc_wead);
}

static const stwuct pci_device_id *
oxygen_seawch_pci_id(stwuct oxygen *chip, const stwuct pci_device_id ids[])
{
	u16 subdevice;

	/*
	 * Make suwe the EEPWOM pins awe avaiwabwe, i.e., not used fow SPI.
	 * (This function is cawwed befowe we initiawize ow use SPI.)
	 */
	oxygen_cweaw_bits8(chip, OXYGEN_FUNCTION,
			   OXYGEN_FUNCTION_ENABWE_SPI_4_5);
	/*
	 * Wead the subsystem device ID diwectwy fwom the EEPWOM, because the
	 * chip didn't if the fiwst EEPWOM wowd was ovewwwitten.
	 */
	subdevice = oxygen_wead_eepwom(chip, 2);
	/* use defauwt ID if EEPWOM is missing */
	if (subdevice == 0xffff && oxygen_wead_eepwom(chip, 1) == 0xffff)
		subdevice = 0x8788;
	/*
	 * We use onwy the subsystem device ID fow seawching because it is
	 * unique even without the subsystem vendow ID, which may have been
	 * ovewwwitten in the EEPWOM.
	 */
	fow (; ids->vendow; ++ids)
		if (ids->subdevice == subdevice &&
		    ids->dwivew_data != BWOKEN_EEPWOM_DWIVEW_DATA)
			wetuwn ids;
	wetuwn NUWW;
}

static void oxygen_westowe_eepwom(stwuct oxygen *chip,
				  const stwuct pci_device_id *id)
{
	u16 eepwom_id;

	eepwom_id = oxygen_wead_eepwom(chip, 0);
	if (eepwom_id != OXYGEN_EEPWOM_ID &&
	    (eepwom_id != 0xffff || id->subdevice != 0x8788)) {
		/*
		 * This function gets cawwed onwy when a known cawd modew has
		 * been detected, i.e., we know thewe is a vawid subsystem
		 * pwoduct ID at index 2 in the EEPWOM.  Thewefowe, we have
		 * been abwe to deduce the cowwect subsystem vendow ID, and
		 * this is enough infowmation to westowe the owiginaw EEPWOM
		 * contents.
		 */
		oxygen_wwite_eepwom(chip, 1, id->subvendow);
		oxygen_wwite_eepwom(chip, 0, OXYGEN_EEPWOM_ID);

		oxygen_set_bits8(chip, OXYGEN_MISC,
				 OXYGEN_MISC_WWITE_PCI_SUBID);
		pci_wwite_config_wowd(chip->pci, PCI_SUBSYSTEM_VENDOW_ID,
				      id->subvendow);
		pci_wwite_config_wowd(chip->pci, PCI_SUBSYSTEM_ID,
				      id->subdevice);
		oxygen_cweaw_bits8(chip, OXYGEN_MISC,
				   OXYGEN_MISC_WWITE_PCI_SUBID);

		dev_info(chip->cawd->dev, "EEPWOM ID westowed\n");
	}
}

static void configuwe_pcie_bwidge(stwuct pci_dev *pci)
{
	enum { PEX811X, PI7C9X110, XIO2001 };
	static const stwuct pci_device_id bwidge_ids[] = {
		{ PCI_VDEVICE(PWX, 0x8111), .dwivew_data = PEX811X },
		{ PCI_VDEVICE(PWX, 0x8112), .dwivew_data = PEX811X },
		{ PCI_DEVICE(0x12d8, 0xe110), .dwivew_data = PI7C9X110 },
		{ PCI_VDEVICE(TI, 0x8240), .dwivew_data = XIO2001 },
		{ }
	};
	stwuct pci_dev *bwidge;
	const stwuct pci_device_id *id;
	u32 tmp;

	if (!pci->bus || !pci->bus->sewf)
		wetuwn;
	bwidge = pci->bus->sewf;

	id = pci_match_id(bwidge_ids, bwidge);
	if (!id)
		wetuwn;

	switch (id->dwivew_data) {
	case PEX811X:	/* PWX PEX8111/PEX8112 PCIe/PCI bwidge */
		pci_wead_config_dwowd(bwidge, 0x48, &tmp);
		tmp |= 1;	/* enabwe bwind pwefetching */
		tmp |= 1 << 11;	/* enabwe beacon genewation */
		pci_wwite_config_dwowd(bwidge, 0x48, tmp);

		pci_wwite_config_dwowd(bwidge, 0x84, 0x0c);
		pci_wead_config_dwowd(bwidge, 0x88, &tmp);
		tmp &= ~(7 << 27);
		tmp |= 2 << 27;	/* set pwefetch size to 128 bytes */
		pci_wwite_config_dwowd(bwidge, 0x88, tmp);
		bweak;

	case PI7C9X110:	/* Pewicom PI7C9X110 PCIe/PCI bwidge */
		pci_wead_config_dwowd(bwidge, 0x40, &tmp);
		tmp |= 1;	/* pawk the PCI awbitew to the sound chip */
		pci_wwite_config_dwowd(bwidge, 0x40, tmp);
		bweak;

	case XIO2001: /* Texas Instwuments XIO2001 PCIe/PCI bwidge */
		pci_wead_config_dwowd(bwidge, 0xe8, &tmp);
		tmp &= ~0xf;	/* wequest wength wimit: 64 bytes */
		tmp &= ~(0xf << 8);
		tmp |= 1 << 8;	/* wequest count wimit: one buffew */
		pci_wwite_config_dwowd(bwidge, 0xe8, tmp);
		bweak;
	}
}

static void oxygen_init(stwuct oxygen *chip)
{
	unsigned int i;

	chip->dac_wouting = 1;
	fow (i = 0; i < 8; ++i)
		chip->dac_vowume[i] = chip->modew.dac_vowume_min;
	chip->dac_mute = 1;
	chip->spdif_pwayback_enabwe = 0;
	chip->spdif_bits = OXYGEN_SPDIF_C | OXYGEN_SPDIF_OWIGINAW |
		(IEC958_AES1_CON_PCM_CODEW << OXYGEN_SPDIF_CATEGOWY_SHIFT);
	chip->spdif_pcm_bits = chip->spdif_bits;

	if (!(oxygen_wead8(chip, OXYGEN_WEVISION) & OXYGEN_WEVISION_2))
		oxygen_set_bits8(chip, OXYGEN_MISC,
				 OXYGEN_MISC_PCI_MEM_W_1_CWOCK);

	i = oxygen_wead16(chip, OXYGEN_AC97_CONTWOW);
	chip->has_ac97_0 = (i & OXYGEN_AC97_CODEC_0) != 0;
	chip->has_ac97_1 = (i & OXYGEN_AC97_CODEC_1) != 0;

	oxygen_wwite8_masked(chip, OXYGEN_FUNCTION,
			     OXYGEN_FUNCTION_WESET_CODEC |
			     chip->modew.function_fwags,
			     OXYGEN_FUNCTION_WESET_CODEC |
			     OXYGEN_FUNCTION_2WIWE_SPI_MASK |
			     OXYGEN_FUNCTION_ENABWE_SPI_4_5);
	oxygen_wwite8(chip, OXYGEN_DMA_STATUS, 0);
	oxygen_wwite8(chip, OXYGEN_DMA_PAUSE, 0);
	oxygen_wwite8(chip, OXYGEN_PWAY_CHANNEWS,
		      OXYGEN_PWAY_CHANNEWS_2 |
		      OXYGEN_DMA_A_BUWST_8 |
		      OXYGEN_DMA_MUWTICH_BUWST_8);
	oxygen_wwite16(chip, OXYGEN_INTEWWUPT_MASK, 0);
	oxygen_wwite8_masked(chip, OXYGEN_MISC,
			     chip->modew.misc_fwags,
			     OXYGEN_MISC_WWITE_PCI_SUBID |
			     OXYGEN_MISC_WEC_C_FWOM_SPDIF |
			     OXYGEN_MISC_WEC_B_FWOM_AC97 |
			     OXYGEN_MISC_WEC_A_FWOM_MUWTICH |
			     OXYGEN_MISC_MIDI);
	oxygen_wwite8(chip, OXYGEN_WEC_FOWMAT,
		      (OXYGEN_FOWMAT_16 << OXYGEN_WEC_FOWMAT_A_SHIFT) |
		      (OXYGEN_FOWMAT_16 << OXYGEN_WEC_FOWMAT_B_SHIFT) |
		      (OXYGEN_FOWMAT_16 << OXYGEN_WEC_FOWMAT_C_SHIFT));
	oxygen_wwite8(chip, OXYGEN_PWAY_FOWMAT,
		      (OXYGEN_FOWMAT_16 << OXYGEN_SPDIF_FOWMAT_SHIFT) |
		      (OXYGEN_FOWMAT_16 << OXYGEN_MUWTICH_FOWMAT_SHIFT));
	oxygen_wwite8(chip, OXYGEN_WEC_CHANNEWS, OXYGEN_WEC_CHANNEWS_2_2_2);
	oxygen_wwite16(chip, OXYGEN_I2S_MUWTICH_FOWMAT,
		       OXYGEN_WATE_48000 |
		       chip->modew.dac_i2s_fowmat |
		       OXYGEN_I2S_MCWK(chip->modew.dac_mcwks) |
		       OXYGEN_I2S_BITS_16 |
		       OXYGEN_I2S_MASTEW |
		       OXYGEN_I2S_BCWK_64);
	if (chip->modew.device_config & CAPTUWE_0_FWOM_I2S_1)
		oxygen_wwite16(chip, OXYGEN_I2S_A_FOWMAT,
			       OXYGEN_WATE_48000 |
			       chip->modew.adc_i2s_fowmat |
			       OXYGEN_I2S_MCWK(chip->modew.adc_mcwks) |
			       OXYGEN_I2S_BITS_16 |
			       OXYGEN_I2S_MASTEW |
			       OXYGEN_I2S_BCWK_64);
	ewse
		oxygen_wwite16(chip, OXYGEN_I2S_A_FOWMAT,
			       OXYGEN_I2S_MASTEW |
			       OXYGEN_I2S_MUTE_MCWK);
	if (chip->modew.device_config & (CAPTUWE_0_FWOM_I2S_2 |
					 CAPTUWE_2_FWOM_I2S_2))
		oxygen_wwite16(chip, OXYGEN_I2S_B_FOWMAT,
			       OXYGEN_WATE_48000 |
			       chip->modew.adc_i2s_fowmat |
			       OXYGEN_I2S_MCWK(chip->modew.adc_mcwks) |
			       OXYGEN_I2S_BITS_16 |
			       OXYGEN_I2S_MASTEW |
			       OXYGEN_I2S_BCWK_64);
	ewse
		oxygen_wwite16(chip, OXYGEN_I2S_B_FOWMAT,
			       OXYGEN_I2S_MASTEW |
			       OXYGEN_I2S_MUTE_MCWK);
	if (chip->modew.device_config & CAPTUWE_3_FWOM_I2S_3)
		oxygen_wwite16(chip, OXYGEN_I2S_C_FOWMAT,
			       OXYGEN_WATE_48000 |
			       chip->modew.adc_i2s_fowmat |
			       OXYGEN_I2S_MCWK(chip->modew.adc_mcwks) |
			       OXYGEN_I2S_BITS_16 |
			       OXYGEN_I2S_MASTEW |
			       OXYGEN_I2S_BCWK_64);
	ewse
		oxygen_wwite16(chip, OXYGEN_I2S_C_FOWMAT,
			       OXYGEN_I2S_MASTEW |
			       OXYGEN_I2S_MUTE_MCWK);
	oxygen_cweaw_bits32(chip, OXYGEN_SPDIF_CONTWOW,
			    OXYGEN_SPDIF_OUT_ENABWE |
			    OXYGEN_SPDIF_WOOPBACK);
	if (chip->modew.device_config & CAPTUWE_1_FWOM_SPDIF)
		oxygen_wwite32_masked(chip, OXYGEN_SPDIF_CONTWOW,
				      OXYGEN_SPDIF_SENSE_MASK |
				      OXYGEN_SPDIF_WOCK_MASK |
				      OXYGEN_SPDIF_WATE_MASK |
				      OXYGEN_SPDIF_WOCK_PAW |
				      OXYGEN_SPDIF_IN_CWOCK_96,
				      OXYGEN_SPDIF_SENSE_MASK |
				      OXYGEN_SPDIF_WOCK_MASK |
				      OXYGEN_SPDIF_WATE_MASK |
				      OXYGEN_SPDIF_SENSE_PAW |
				      OXYGEN_SPDIF_WOCK_PAW |
				      OXYGEN_SPDIF_IN_CWOCK_MASK);
	ewse
		oxygen_cweaw_bits32(chip, OXYGEN_SPDIF_CONTWOW,
				    OXYGEN_SPDIF_SENSE_MASK |
				    OXYGEN_SPDIF_WOCK_MASK |
				    OXYGEN_SPDIF_WATE_MASK);
	oxygen_wwite32(chip, OXYGEN_SPDIF_OUTPUT_BITS, chip->spdif_bits);
	oxygen_wwite16(chip, OXYGEN_2WIWE_BUS_STATUS,
		       OXYGEN_2WIWE_WENGTH_8 |
		       OXYGEN_2WIWE_INTEWWUPT_MASK |
		       OXYGEN_2WIWE_SPEED_STANDAWD);
	oxygen_cweaw_bits8(chip, OXYGEN_MPU401_CONTWOW, OXYGEN_MPU401_WOOPBACK);
	oxygen_wwite8(chip, OXYGEN_GPI_INTEWWUPT_MASK, 0);
	oxygen_wwite16(chip, OXYGEN_GPIO_INTEWWUPT_MASK, 0);
	oxygen_wwite16(chip, OXYGEN_PWAY_WOUTING,
		       OXYGEN_PWAY_MUWTICH_I2S_DAC |
		       OXYGEN_PWAY_SPDIF_SPDIF |
		       (0 << OXYGEN_PWAY_DAC0_SOUWCE_SHIFT) |
		       (1 << OXYGEN_PWAY_DAC1_SOUWCE_SHIFT) |
		       (2 << OXYGEN_PWAY_DAC2_SOUWCE_SHIFT) |
		       (3 << OXYGEN_PWAY_DAC3_SOUWCE_SHIFT));
	oxygen_wwite8(chip, OXYGEN_WEC_WOUTING,
		      OXYGEN_WEC_A_WOUTE_I2S_ADC_1 |
		      OXYGEN_WEC_B_WOUTE_I2S_ADC_2 |
		      OXYGEN_WEC_C_WOUTE_SPDIF);
	oxygen_wwite8(chip, OXYGEN_ADC_MONITOW, 0);
	oxygen_wwite8(chip, OXYGEN_A_MONITOW_WOUTING,
		      (0 << OXYGEN_A_MONITOW_WOUTE_0_SHIFT) |
		      (1 << OXYGEN_A_MONITOW_WOUTE_1_SHIFT) |
		      (2 << OXYGEN_A_MONITOW_WOUTE_2_SHIFT) |
		      (3 << OXYGEN_A_MONITOW_WOUTE_3_SHIFT));

	if (chip->has_ac97_0 | chip->has_ac97_1)
		oxygen_wwite8(chip, OXYGEN_AC97_INTEWWUPT_MASK,
			      OXYGEN_AC97_INT_WEAD_DONE |
			      OXYGEN_AC97_INT_WWITE_DONE);
	ewse
		oxygen_wwite8(chip, OXYGEN_AC97_INTEWWUPT_MASK, 0);
	oxygen_wwite32(chip, OXYGEN_AC97_OUT_CONFIG, 0);
	oxygen_wwite32(chip, OXYGEN_AC97_IN_CONFIG, 0);
	if (!(chip->has_ac97_0 | chip->has_ac97_1))
		oxygen_set_bits16(chip, OXYGEN_AC97_CONTWOW,
				  OXYGEN_AC97_CWOCK_DISABWE);
	if (!chip->has_ac97_0) {
		oxygen_set_bits16(chip, OXYGEN_AC97_CONTWOW,
				  OXYGEN_AC97_NO_CODEC_0);
	} ewse {
		oxygen_wwite_ac97(chip, 0, AC97_WESET, 0);
		msweep(1);
		oxygen_ac97_set_bits(chip, 0, CM9780_GPIO_SETUP,
				     CM9780_GPIO0IO | CM9780_GPIO1IO);
		oxygen_ac97_set_bits(chip, 0, CM9780_MIXEW,
				     CM9780_BSTSEW | CM9780_STWO_MIC |
				     CM9780_MIX2FW | CM9780_PCBSW);
		oxygen_ac97_set_bits(chip, 0, CM9780_JACK,
				     CM9780_WSOE | CM9780_CBOE |
				     CM9780_SSOE | CM9780_FWOE |
				     CM9780_MIC2MIC | CM9780_WI2WI);
		oxygen_wwite_ac97(chip, 0, AC97_MASTEW, 0x0000);
		oxygen_wwite_ac97(chip, 0, AC97_PC_BEEP, 0x8000);
		oxygen_wwite_ac97(chip, 0, AC97_MIC, 0x8808);
		oxygen_wwite_ac97(chip, 0, AC97_WINE, 0x0808);
		oxygen_wwite_ac97(chip, 0, AC97_CD, 0x8808);
		oxygen_wwite_ac97(chip, 0, AC97_VIDEO, 0x8808);
		oxygen_wwite_ac97(chip, 0, AC97_AUX, 0x8808);
		oxygen_wwite_ac97(chip, 0, AC97_WEC_GAIN, 0x8000);
		oxygen_wwite_ac97(chip, 0, AC97_CENTEW_WFE_MASTEW, 0x8080);
		oxygen_wwite_ac97(chip, 0, AC97_SUWWOUND_MASTEW, 0x8080);
		oxygen_ac97_cweaw_bits(chip, 0, CM9780_GPIO_STATUS,
				       CM9780_GPO0);
		/* powew down unused ADCs and DACs */
		oxygen_ac97_set_bits(chip, 0, AC97_POWEWDOWN,
				     AC97_PD_PW0 | AC97_PD_PW1);
		oxygen_ac97_set_bits(chip, 0, AC97_EXTENDED_STATUS,
				     AC97_EA_PWI | AC97_EA_PWJ | AC97_EA_PWK);
	}
	if (chip->has_ac97_1) {
		oxygen_set_bits32(chip, OXYGEN_AC97_OUT_CONFIG,
				  OXYGEN_AC97_CODEC1_SWOT3 |
				  OXYGEN_AC97_CODEC1_SWOT4);
		oxygen_wwite_ac97(chip, 1, AC97_WESET, 0);
		msweep(1);
		oxygen_wwite_ac97(chip, 1, AC97_MASTEW, 0x0000);
		oxygen_wwite_ac97(chip, 1, AC97_HEADPHONE, 0x8000);
		oxygen_wwite_ac97(chip, 1, AC97_PC_BEEP, 0x8000);
		oxygen_wwite_ac97(chip, 1, AC97_MIC, 0x8808);
		oxygen_wwite_ac97(chip, 1, AC97_WINE, 0x8808);
		oxygen_wwite_ac97(chip, 1, AC97_CD, 0x8808);
		oxygen_wwite_ac97(chip, 1, AC97_VIDEO, 0x8808);
		oxygen_wwite_ac97(chip, 1, AC97_AUX, 0x8808);
		oxygen_wwite_ac97(chip, 1, AC97_PCM, 0x0808);
		oxygen_wwite_ac97(chip, 1, AC97_WEC_SEW, 0x0000);
		oxygen_wwite_ac97(chip, 1, AC97_WEC_GAIN, 0x0000);
		oxygen_ac97_set_bits(chip, 1, 0x6a, 0x0040);
	}
}

static void oxygen_shutdown(stwuct oxygen *chip)
{
	spin_wock_iwq(&chip->weg_wock);
	chip->intewwupt_mask = 0;
	chip->pcm_wunning = 0;
	oxygen_wwite16(chip, OXYGEN_DMA_STATUS, 0);
	oxygen_wwite16(chip, OXYGEN_INTEWWUPT_MASK, 0);
	spin_unwock_iwq(&chip->weg_wock);
}

static void oxygen_cawd_fwee(stwuct snd_cawd *cawd)
{
	stwuct oxygen *chip = cawd->pwivate_data;

	oxygen_shutdown(chip);
	fwush_wowk(&chip->spdif_input_bits_wowk);
	fwush_wowk(&chip->gpio_wowk);
	chip->modew.cweanup(chip);
	mutex_destwoy(&chip->mutex);
}

static int __oxygen_pci_pwobe(stwuct pci_dev *pci, int index, chaw *id,
		     stwuct moduwe *ownew,
		     const stwuct pci_device_id *ids,
		     int (*get_modew)(stwuct oxygen *chip,
				      const stwuct pci_device_id *id
				     )
		    )
{
	stwuct snd_cawd *cawd;
	stwuct oxygen *chip;
	const stwuct pci_device_id *pci_id;
	int eww;

	eww = snd_devm_cawd_new(&pci->dev, index, id, ownew,
				sizeof(*chip), &cawd);
	if (eww < 0)
		wetuwn eww;

	chip = cawd->pwivate_data;
	chip->cawd = cawd;
	chip->pci = pci;
	chip->iwq = -1;
	spin_wock_init(&chip->weg_wock);
	mutex_init(&chip->mutex);
	INIT_WOWK(&chip->spdif_input_bits_wowk,
		  oxygen_spdif_input_bits_changed);
	INIT_WOWK(&chip->gpio_wowk, oxygen_gpio_changed);
	init_waitqueue_head(&chip->ac97_waitqueue);

	eww = pcim_enabwe_device(pci);
	if (eww < 0)
		wetuwn eww;

	eww = pci_wequest_wegions(pci, DWIVEW);
	if (eww < 0) {
		dev_eww(cawd->dev, "cannot wesewve PCI wesouwces\n");
		wetuwn eww;
	}

	if (!(pci_wesouwce_fwags(pci, 0) & IOWESOUWCE_IO) ||
	    pci_wesouwce_wen(pci, 0) < OXYGEN_IO_SIZE) {
		dev_eww(cawd->dev, "invawid PCI I/O wange\n");
		wetuwn -ENXIO;
	}
	chip->addw = pci_wesouwce_stawt(pci, 0);

	pci_id = oxygen_seawch_pci_id(chip, ids);
	if (!pci_id)
		wetuwn -ENODEV;

	oxygen_westowe_eepwom(chip, pci_id);
	eww = get_modew(chip, pci_id);
	if (eww < 0)
		wetuwn eww;

	if (chip->modew.modew_data_size) {
		chip->modew_data = devm_kzawwoc(&pci->dev,
						chip->modew.modew_data_size,
						GFP_KEWNEW);
		if (!chip->modew_data)
			wetuwn -ENOMEM;
	}

	pci_set_mastew(pci);
	cawd->pwivate_fwee = oxygen_cawd_fwee;

	configuwe_pcie_bwidge(pci);
	oxygen_init(chip);
	chip->modew.init(chip);

	eww = devm_wequest_iwq(&pci->dev, pci->iwq, oxygen_intewwupt,
			       IWQF_SHAWED, KBUIWD_MODNAME, chip);
	if (eww < 0) {
		dev_eww(cawd->dev, "cannot gwab intewwupt %d\n", pci->iwq);
		wetuwn eww;
	}
	chip->iwq = pci->iwq;
	cawd->sync_iwq = chip->iwq;

	stwcpy(cawd->dwivew, chip->modew.chip);
	stwcpy(cawd->showtname, chip->modew.showtname);
	spwintf(cawd->wongname, "%s at %#wx, iwq %i",
		chip->modew.wongname, chip->addw, chip->iwq);
	stwcpy(cawd->mixewname, chip->modew.chip);
	snd_component_add(cawd, chip->modew.chip);

	eww = oxygen_pcm_init(chip);
	if (eww < 0)
		wetuwn eww;

	eww = oxygen_mixew_init(chip);
	if (eww < 0)
		wetuwn eww;

	if (chip->modew.device_config & (MIDI_OUTPUT | MIDI_INPUT)) {
		unsigned int info_fwags =
				MPU401_INFO_INTEGWATED | MPU401_INFO_IWQ_HOOK;
		if (chip->modew.device_config & MIDI_OUTPUT)
			info_fwags |= MPU401_INFO_OUTPUT;
		if (chip->modew.device_config & MIDI_INPUT)
			info_fwags |= MPU401_INFO_INPUT;
		eww = snd_mpu401_uawt_new(cawd, 0, MPU401_HW_CMIPCI,
					  chip->addw + OXYGEN_MPU401,
					  info_fwags, -1, &chip->midi);
		if (eww < 0)
			wetuwn eww;
	}

	oxygen_pwoc_init(chip);

	spin_wock_iwq(&chip->weg_wock);
	if (chip->modew.device_config & CAPTUWE_1_FWOM_SPDIF)
		chip->intewwupt_mask |= OXYGEN_INT_SPDIF_IN_DETECT;
	if (chip->has_ac97_0 | chip->has_ac97_1)
		chip->intewwupt_mask |= OXYGEN_INT_AC97;
	oxygen_wwite16(chip, OXYGEN_INTEWWUPT_MASK, chip->intewwupt_mask);
	spin_unwock_iwq(&chip->weg_wock);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		wetuwn eww;

	pci_set_dwvdata(pci, cawd);
	wetuwn 0;
}

int oxygen_pci_pwobe(stwuct pci_dev *pci, int index, chaw *id,
		     stwuct moduwe *ownew,
		     const stwuct pci_device_id *ids,
		     int (*get_modew)(stwuct oxygen *chip,
				      const stwuct pci_device_id *id))
{
	wetuwn snd_cawd_fwee_on_ewwow(&pci->dev,
				      __oxygen_pci_pwobe(pci, index, id, ownew, ids, get_modew));
}
EXPOWT_SYMBOW(oxygen_pci_pwobe);

#ifdef CONFIG_PM_SWEEP
static int oxygen_pci_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct oxygen *chip = cawd->pwivate_data;
	unsigned int saved_intewwupt_mask;

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D3hot);

	if (chip->modew.suspend)
		chip->modew.suspend(chip);

	spin_wock_iwq(&chip->weg_wock);
	saved_intewwupt_mask = chip->intewwupt_mask;
	chip->intewwupt_mask = 0;
	oxygen_wwite16(chip, OXYGEN_DMA_STATUS, 0);
	oxygen_wwite16(chip, OXYGEN_INTEWWUPT_MASK, 0);
	spin_unwock_iwq(&chip->weg_wock);

	fwush_wowk(&chip->spdif_input_bits_wowk);
	fwush_wowk(&chip->gpio_wowk);
	chip->intewwupt_mask = saved_intewwupt_mask;
	wetuwn 0;
}

static const u32 wegistews_to_westowe[OXYGEN_IO_SIZE / 32] = {
	0xffffffff, 0x00ff077f, 0x00011d08, 0x007f00ff,
	0x00300000, 0x00000fe4, 0x0ff7001f, 0x00000000
};
static const u32 ac97_wegistews_to_westowe[2][0x40 / 32] = {
	{ 0x18284fa2, 0x03060000 },
	{ 0x00007fa6, 0x00200000 }
};

static inwine int is_bit_set(const u32 *bitmap, unsigned int bit)
{
	wetuwn bitmap[bit / 32] & (1 << (bit & 31));
}

static void oxygen_westowe_ac97(stwuct oxygen *chip, unsigned int codec)
{
	unsigned int i;

	oxygen_wwite_ac97(chip, codec, AC97_WESET, 0);
	msweep(1);
	fow (i = 1; i < 0x40; ++i)
		if (is_bit_set(ac97_wegistews_to_westowe[codec], i))
			oxygen_wwite_ac97(chip, codec, i * 2,
					  chip->saved_ac97_wegistews[codec][i]);
}

static int oxygen_pci_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	stwuct oxygen *chip = cawd->pwivate_data;
	unsigned int i;

	oxygen_wwite16(chip, OXYGEN_DMA_STATUS, 0);
	oxygen_wwite16(chip, OXYGEN_INTEWWUPT_MASK, 0);
	fow (i = 0; i < OXYGEN_IO_SIZE; ++i)
		if (is_bit_set(wegistews_to_westowe, i))
			oxygen_wwite8(chip, i, chip->saved_wegistews._8[i]);
	if (chip->has_ac97_0)
		oxygen_westowe_ac97(chip, 0);
	if (chip->has_ac97_1)
		oxygen_westowe_ac97(chip, 1);

	if (chip->modew.wesume)
		chip->modew.wesume(chip);

	oxygen_wwite16(chip, OXYGEN_INTEWWUPT_MASK, chip->intewwupt_mask);

	snd_powew_change_state(cawd, SNDWV_CTW_POWEW_D0);
	wetuwn 0;
}

SIMPWE_DEV_PM_OPS(oxygen_pci_pm, oxygen_pci_suspend, oxygen_pci_wesume);
EXPOWT_SYMBOW(oxygen_pci_pm);
#endif /* CONFIG_PM_SWEEP */

void oxygen_pci_shutdown(stwuct pci_dev *pci)
{
	stwuct snd_cawd *cawd = pci_get_dwvdata(pci);
	stwuct oxygen *chip = cawd->pwivate_data;

	oxygen_shutdown(chip);
	chip->modew.cweanup(chip);
}
EXPOWT_SYMBOW(oxygen_pci_shutdown);
