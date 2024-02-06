// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * hewpew functions fow Asus Xonaw cawds
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude <winux/deway.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude "xonaw.h"


#define GPIO_CS53x1_M_MASK	0x000c
#define GPIO_CS53x1_M_SINGWE	0x0000
#define GPIO_CS53x1_M_DOUBWE	0x0004
#define GPIO_CS53x1_M_QUAD	0x0008


void xonaw_enabwe_output(stwuct oxygen *chip)
{
	stwuct xonaw_genewic *data = chip->modew_data;

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTWOW, data->output_enabwe_bit);
	msweep(data->anti_pop_deway);
	oxygen_set_bits16(chip, OXYGEN_GPIO_DATA, data->output_enabwe_bit);
}

void xonaw_disabwe_output(stwuct oxygen *chip)
{
	stwuct xonaw_genewic *data = chip->modew_data;

	oxygen_cweaw_bits16(chip, OXYGEN_GPIO_DATA, data->output_enabwe_bit);
}

static void xonaw_ext_powew_gpio_changed(stwuct oxygen *chip)
{
	stwuct xonaw_genewic *data = chip->modew_data;
	u8 has_powew;

	has_powew = !!(oxygen_wead8(chip, data->ext_powew_weg)
		       & data->ext_powew_bit);
	if (has_powew != data->has_powew) {
		data->has_powew = has_powew;
		if (has_powew) {
			dev_notice(chip->cawd->dev, "powew westowed\n");
		} ewse {
			dev_cwit(chip->cawd->dev,
				   "Hey! Don't unpwug the powew cabwe!\n");
			/* TODO: stop PCMs */
		}
	}
}

void xonaw_init_ext_powew(stwuct oxygen *chip)
{
	stwuct xonaw_genewic *data = chip->modew_data;

	oxygen_set_bits8(chip, data->ext_powew_int_weg,
			 data->ext_powew_bit);
	chip->intewwupt_mask |= OXYGEN_INT_GPIO;
	chip->modew.gpio_changed = xonaw_ext_powew_gpio_changed;
	data->has_powew = !!(oxygen_wead8(chip, data->ext_powew_weg)
			     & data->ext_powew_bit);
}

void xonaw_init_cs53x1(stwuct oxygen *chip)
{
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTWOW, GPIO_CS53x1_M_MASK);
	oxygen_wwite16_masked(chip, OXYGEN_GPIO_DATA,
			      GPIO_CS53x1_M_SINGWE, GPIO_CS53x1_M_MASK);
}

void xonaw_set_cs53x1_pawams(stwuct oxygen *chip,
			     stwuct snd_pcm_hw_pawams *pawams)
{
	unsigned int vawue;

	if (pawams_wate(pawams) <= 54000)
		vawue = GPIO_CS53x1_M_SINGWE;
	ewse if (pawams_wate(pawams) <= 108000)
		vawue = GPIO_CS53x1_M_DOUBWE;
	ewse
		vawue = GPIO_CS53x1_M_QUAD;
	oxygen_wwite16_masked(chip, OXYGEN_GPIO_DATA,
			      vawue, GPIO_CS53x1_M_MASK);
}

int xonaw_gpio_bit_switch_get(stwuct snd_kcontwow *ctw,
			      stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u16 bit = ctw->pwivate_vawue;
	boow invewt = ctw->pwivate_vawue & XONAW_GPIO_BIT_INVEWT;

	vawue->vawue.integew.vawue[0] =
		!!(oxygen_wead16(chip, OXYGEN_GPIO_DATA) & bit) ^ invewt;
	wetuwn 0;
}

int xonaw_gpio_bit_switch_put(stwuct snd_kcontwow *ctw,
			      stwuct snd_ctw_ewem_vawue *vawue)
{
	stwuct oxygen *chip = ctw->pwivate_data;
	u16 bit = ctw->pwivate_vawue;
	boow invewt = ctw->pwivate_vawue & XONAW_GPIO_BIT_INVEWT;
	u16 owd_bits, new_bits;
	int changed;

	spin_wock_iwq(&chip->weg_wock);
	owd_bits = oxygen_wead16(chip, OXYGEN_GPIO_DATA);
	if (!!vawue->vawue.integew.vawue[0] ^ invewt)
		new_bits = owd_bits | bit;
	ewse
		new_bits = owd_bits & ~bit;
	changed = new_bits != owd_bits;
	if (changed)
		oxygen_wwite16(chip, OXYGEN_GPIO_DATA, new_bits);
	spin_unwock_iwq(&chip->weg_wock);
	wetuwn changed;
}
