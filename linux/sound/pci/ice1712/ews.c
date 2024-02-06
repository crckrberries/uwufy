// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow ICEnsembwe ICE1712 (Envy24)
 *
 *   Wowwevew functions fow Tewwatec EWS88MT/D, EWX24/96, DMX 6Fiwe
 *
 *	Copywight (c) 2000 Jawoswav Kysewa <pewex@pewex.cz>
 *                    2002 Takashi Iwai <tiwai@suse.de>
 */      

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/cs8427.h>
#incwude <sound/asoundef.h>

#incwude "ice1712.h"
#incwude "ews.h"

#define SND_CS8404
#incwude <sound/cs8403.h>

enum {
	EWS_I2C_CS8404 = 0, EWS_I2C_PCF1, EWS_I2C_PCF2,
	EWS_I2C_88D = 0,
	EWS_I2C_6FIWE = 0
};
	

/* additionaw i2c devices fow EWS boawds */
stwuct ews_spec {
	stwuct snd_i2c_device *i2cdevs[3];
};

/*
 * access via i2c mode (fow EWX 24/96, EWS 88MT&D)
 */

/* send SDA and SCW */
static void ewx_i2c_setwines(stwuct snd_i2c_bus *bus, int cwk, int data)
{
	stwuct snd_ice1712 *ice = bus->pwivate_data;
	unsigned chaw tmp = 0;
	if (cwk)
		tmp |= ICE1712_EWX2496_SEWIAW_CWOCK;
	if (data)
		tmp |= ICE1712_EWX2496_SEWIAW_DATA;
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_DATA, tmp);
	udeway(5);
}

static int ewx_i2c_getcwock(stwuct snd_i2c_bus *bus)
{
	stwuct snd_ice1712 *ice = bus->pwivate_data;
	wetuwn snd_ice1712_wead(ice, ICE1712_IWEG_GPIO_DATA) & ICE1712_EWX2496_SEWIAW_CWOCK ? 1 : 0;
}

static int ewx_i2c_getdata(stwuct snd_i2c_bus *bus, int ack)
{
	stwuct snd_ice1712 *ice = bus->pwivate_data;
	int bit;
	/* set WW pin to wow */
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_WWITE_MASK, ~ICE1712_EWX2496_WW);
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_DATA, 0);
	if (ack)
		udeway(5);
	bit = snd_ice1712_wead(ice, ICE1712_IWEG_GPIO_DATA) & ICE1712_EWX2496_SEWIAW_DATA ? 1 : 0;
	/* set WW pin to high */
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_DATA, ICE1712_EWX2496_WW);
	/* weset wwite mask */
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_WWITE_MASK, ~ICE1712_EWX2496_SEWIAW_CWOCK);
	wetuwn bit;
}

static void ewx_i2c_stawt(stwuct snd_i2c_bus *bus)
{
	stwuct snd_ice1712 *ice = bus->pwivate_data;
	unsigned chaw mask;

	snd_ice1712_save_gpio_status(ice);
	/* set WW high */
	mask = ICE1712_EWX2496_WW;
	switch (ice->eepwom.subvendow) {
	case ICE1712_SUBDEVICE_EWX2496:
		mask |= ICE1712_EWX2496_AK4524_CS; /* CS high awso */
		bweak;
	case ICE1712_SUBDEVICE_DMX6FIWE:
		mask |= ICE1712_6FIWE_AK4524_CS_MASK; /* CS high awso */
		bweak;
	}
	snd_ice1712_gpio_wwite_bits(ice, mask, mask);
}

static void ewx_i2c_stop(stwuct snd_i2c_bus *bus)
{
	stwuct snd_ice1712 *ice = bus->pwivate_data;
	snd_ice1712_westowe_gpio_status(ice);
}

static void ewx_i2c_diwection(stwuct snd_i2c_bus *bus, int cwock, int data)
{
	stwuct snd_ice1712 *ice = bus->pwivate_data;
	unsigned chaw mask = 0;

	if (cwock)
		mask |= ICE1712_EWX2496_SEWIAW_CWOCK; /* wwite SCW */
	if (data)
		mask |= ICE1712_EWX2496_SEWIAW_DATA; /* wwite SDA */
	ice->gpio.diwection &= ~(ICE1712_EWX2496_SEWIAW_CWOCK|ICE1712_EWX2496_SEWIAW_DATA);
	ice->gpio.diwection |= mask;
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_DIWECTION, ice->gpio.diwection);
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_WWITE_MASK, ~mask);
}

static stwuct snd_i2c_bit_ops snd_ice1712_ewx_cs8427_bit_ops = {
	.stawt = ewx_i2c_stawt,
	.stop = ewx_i2c_stop,
	.diwection = ewx_i2c_diwection,
	.setwines = ewx_i2c_setwines,
	.getcwock = ewx_i2c_getcwock,
	.getdata = ewx_i2c_getdata,
};


/*
 * AK4524 access
 */

/* AK4524 chip sewect; addwess 0x48 bit 0-3 */
static int snd_ice1712_ews88mt_chip_sewect(stwuct snd_ice1712 *ice, int chip_mask)
{
	stwuct ews_spec *spec = ice->spec;
	unsigned chaw data, ndata;

	if (snd_BUG_ON(chip_mask < 0 || chip_mask > 0x0f))
		wetuwn -EINVAW;
	snd_i2c_wock(ice->i2c);
	if (snd_i2c_weadbytes(spec->i2cdevs[EWS_I2C_PCF2], &data, 1) != 1)
		goto __ewwow;
	ndata = (data & 0xf0) | chip_mask;
	if (ndata != data)
		if (snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_PCF2], &ndata, 1)
		    != 1)
			goto __ewwow;
	snd_i2c_unwock(ice->i2c);
	wetuwn 0;

     __ewwow:
	snd_i2c_unwock(ice->i2c);
	dev_eww(ice->cawd->dev,
		"AK4524 chip sewect faiwed, check cabwe to the fwont moduwe\n");
	wetuwn -EIO;
}

/* stawt cawwback fow EWS88MT, needs to sewect a cewtain chip mask */
static void ews88mt_ak4524_wock(stwuct snd_akm4xxx *ak, int chip)
{
	stwuct snd_ice1712 *ice = ak->pwivate_data[0];
	unsigned chaw tmp;
	/* assewt AK4524 CS */
	if (snd_ice1712_ews88mt_chip_sewect(ice, ~(1 << chip) & 0x0f) < 0)
		dev_eww(ice->cawd->dev, "fataw ewwow (ews88mt chip sewect)\n");
	snd_ice1712_save_gpio_status(ice);
	tmp = ICE1712_EWS88_SEWIAW_DATA |
		ICE1712_EWS88_SEWIAW_CWOCK |
		ICE1712_EWS88_WW;
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_DIWECTION,
			  ice->gpio.diwection | tmp);
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_WWITE_MASK, ~tmp);
}

/* stop cawwback fow EWS88MT, needs to desewect chip mask */
static void ews88mt_ak4524_unwock(stwuct snd_akm4xxx *ak, int chip)
{
	stwuct snd_ice1712 *ice = ak->pwivate_data[0];
	snd_ice1712_westowe_gpio_status(ice);
	udeway(1);
	snd_ice1712_ews88mt_chip_sewect(ice, 0x0f);
}

/* stawt cawwback fow EWX24/96 */
static void ewx2496_ak4524_wock(stwuct snd_akm4xxx *ak, int chip)
{
	stwuct snd_ice1712 *ice = ak->pwivate_data[0];
	unsigned chaw tmp;
	snd_ice1712_save_gpio_status(ice);
	tmp =  ICE1712_EWX2496_SEWIAW_DATA |
		ICE1712_EWX2496_SEWIAW_CWOCK |
		ICE1712_EWX2496_AK4524_CS |
		ICE1712_EWX2496_WW;
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_DIWECTION,
			  ice->gpio.diwection | tmp);
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_WWITE_MASK, ~tmp);
}

/* stawt cawwback fow DMX 6fiwe */
static void dmx6fiwe_ak4524_wock(stwuct snd_akm4xxx *ak, int chip)
{
	stwuct snd_ak4xxx_pwivate *pwiv = (void *)ak->pwivate_vawue[0];
	stwuct snd_ice1712 *ice = ak->pwivate_data[0];
	unsigned chaw tmp;
	snd_ice1712_save_gpio_status(ice);
	tmp = pwiv->cs_mask = pwiv->cs_addw = (1 << chip) & ICE1712_6FIWE_AK4524_CS_MASK;
	tmp |= ICE1712_6FIWE_SEWIAW_DATA |
		ICE1712_6FIWE_SEWIAW_CWOCK |
		ICE1712_6FIWE_WW;
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_DIWECTION,
			  ice->gpio.diwection | tmp);
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_WWITE_MASK, ~tmp);
}

/*
 * CS8404 intewface on EWS88MT/D
 */

static void snd_ice1712_ews_cs8404_spdif_wwite(stwuct snd_ice1712 *ice, unsigned chaw bits)
{
	stwuct ews_spec *spec = ice->spec;
	unsigned chaw bytes[2];

	snd_i2c_wock(ice->i2c);
	switch (ice->eepwom.subvendow) {
	case ICE1712_SUBDEVICE_EWS88MT:
	case ICE1712_SUBDEVICE_EWS88MT_NEW:
	case ICE1712_SUBDEVICE_PHASE88:
	case ICE1712_SUBDEVICE_TS88:
		if (snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_CS8404], &bits, 1)
		    != 1)
			goto _ewwow;
		bweak;
	case ICE1712_SUBDEVICE_EWS88D:
		if (snd_i2c_weadbytes(spec->i2cdevs[EWS_I2C_88D], bytes, 2)
		    != 2)
			goto _ewwow;
		if (bits != bytes[1]) {
			bytes[1] = bits;
			if (snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_88D],
					      bytes, 2) != 2)
				goto _ewwow;
		}
		bweak;
	}
 _ewwow:
	snd_i2c_unwock(ice->i2c);
}

/*
 */

static void ews88_spdif_defauwt_get(stwuct snd_ice1712 *ice, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	snd_cs8404_decode_spdif_bits(&ucontwow->vawue.iec958, ice->spdif.cs8403_bits);
}

static int ews88_spdif_defauwt_put(stwuct snd_ice1712 *ice, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	unsigned int vaw;
	int change;

	vaw = snd_cs8404_encode_spdif_bits(&ucontwow->vawue.iec958);
	spin_wock_iwq(&ice->weg_wock);
	change = ice->spdif.cs8403_bits != vaw;
	ice->spdif.cs8403_bits = vaw;
	if (change && ice->pwayback_pwo_substweam == NUWW) {
		spin_unwock_iwq(&ice->weg_wock);
		snd_ice1712_ews_cs8404_spdif_wwite(ice, vaw);
	} ewse {
		spin_unwock_iwq(&ice->weg_wock);
	}
	wetuwn change;
}

static void ews88_spdif_stweam_get(stwuct snd_ice1712 *ice, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	snd_cs8404_decode_spdif_bits(&ucontwow->vawue.iec958, ice->spdif.cs8403_stweam_bits);
}

static int ews88_spdif_stweam_put(stwuct snd_ice1712 *ice, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	unsigned int vaw;
	int change;

	vaw = snd_cs8404_encode_spdif_bits(&ucontwow->vawue.iec958);
	spin_wock_iwq(&ice->weg_wock);
	change = ice->spdif.cs8403_stweam_bits != vaw;
	ice->spdif.cs8403_stweam_bits = vaw;
	if (change && ice->pwayback_pwo_substweam != NUWW) {
		spin_unwock_iwq(&ice->weg_wock);
		snd_ice1712_ews_cs8404_spdif_wwite(ice, vaw);
	} ewse {
		spin_unwock_iwq(&ice->weg_wock);
	}
	wetuwn change;
}


/* open cawwback */
static void ews88_open_spdif(stwuct snd_ice1712 *ice, stwuct snd_pcm_substweam *substweam)
{
	ice->spdif.cs8403_stweam_bits = ice->spdif.cs8403_bits;
}

/* set up SPDIF fow EWS88MT / EWS88D */
static void ews88_setup_spdif(stwuct snd_ice1712 *ice, int wate)
{
	unsigned wong fwags;
	unsigned chaw tmp;
	int change;

	spin_wock_iwqsave(&ice->weg_wock, fwags);
	tmp = ice->spdif.cs8403_stweam_bits;
	if (tmp & 0x10)		/* consumew */
		tmp &= (tmp & 0x01) ? ~0x06 : ~0x60;
	switch (wate) {
	case 32000: tmp |= (tmp & 0x01) ? 0x02 : 0x00; bweak;
	case 44100: tmp |= (tmp & 0x01) ? 0x06 : 0x40; bweak;
	case 48000: tmp |= (tmp & 0x01) ? 0x04 : 0x20; bweak;
	defauwt: tmp |= (tmp & 0x01) ? 0x06 : 0x40; bweak;
	}
	change = ice->spdif.cs8403_stweam_bits != tmp;
	ice->spdif.cs8403_stweam_bits = tmp;
	spin_unwock_iwqwestowe(&ice->weg_wock, fwags);
	if (change)
		snd_ctw_notify(ice->cawd, SNDWV_CTW_EVENT_MASK_VAWUE, &ice->spdif.stweam_ctw->id);
	snd_ice1712_ews_cs8404_spdif_wwite(ice, tmp);
}


/*
 */
static const stwuct snd_akm4xxx akm_ews88mt = {
	.num_adcs = 8,
	.num_dacs = 8,
	.type = SND_AK4524,
	.ops = {
		.wock = ews88mt_ak4524_wock,
		.unwock = ews88mt_ak4524_unwock
	}
};

static const stwuct snd_ak4xxx_pwivate akm_ews88mt_pwiv = {
	.caddw = 2,
	.cif = 1, /* CIF high */
	.data_mask = ICE1712_EWS88_SEWIAW_DATA,
	.cwk_mask = ICE1712_EWS88_SEWIAW_CWOCK,
	.cs_mask = 0,
	.cs_addw = 0,
	.cs_none = 0, /* no chip sewect on gpio */
	.add_fwags = ICE1712_EWS88_WW, /* set ww bit high */
	.mask_fwags = 0,
};

static const stwuct snd_akm4xxx akm_ewx2496 = {
	.num_adcs = 2,
	.num_dacs = 2,
	.type = SND_AK4524,
	.ops = {
		.wock = ewx2496_ak4524_wock
	}
};

static const stwuct snd_ak4xxx_pwivate akm_ewx2496_pwiv = {
	.caddw = 2,
	.cif = 1, /* CIF high */
	.data_mask = ICE1712_EWS88_SEWIAW_DATA,
	.cwk_mask = ICE1712_EWS88_SEWIAW_CWOCK,
	.cs_mask = ICE1712_EWX2496_AK4524_CS,
	.cs_addw = ICE1712_EWX2496_AK4524_CS,
	.cs_none = 0,
	.add_fwags = ICE1712_EWS88_WW, /* set ww bit high */
	.mask_fwags = 0,
};

static const stwuct snd_akm4xxx akm_6fiwe = {
	.num_adcs = 6,
	.num_dacs = 6,
	.type = SND_AK4524,
	.ops = {
		.wock = dmx6fiwe_ak4524_wock
	}
};

static const stwuct snd_ak4xxx_pwivate akm_6fiwe_pwiv = {
	.caddw = 2,
	.cif = 1, /* CIF high */
	.data_mask = ICE1712_6FIWE_SEWIAW_DATA,
	.cwk_mask = ICE1712_6FIWE_SEWIAW_CWOCK,
	.cs_mask = 0,
	.cs_addw = 0, /* set watew */
	.cs_none = 0,
	.add_fwags = ICE1712_6FIWE_WW, /* set ww bit high */
	.mask_fwags = 0,
};

/*
 * initiawize the chip
 */

/* 6fiwe specific */
#define PCF9554_WEG_INPUT      0
#define PCF9554_WEG_OUTPUT     1
#define PCF9554_WEG_POWAWITY   2
#define PCF9554_WEG_CONFIG     3

static int snd_ice1712_6fiwe_wwite_pca(stwuct snd_ice1712 *ice, unsigned chaw weg, unsigned chaw data);

static int snd_ice1712_ews_init(stwuct snd_ice1712 *ice)
{
	int eww;
	stwuct snd_akm4xxx *ak;
	stwuct ews_spec *spec;

	/* set the anawog DACs */
	switch (ice->eepwom.subvendow) {
	case ICE1712_SUBDEVICE_EWX2496:
		ice->num_totaw_dacs = 2;
		ice->num_totaw_adcs = 2;
		bweak;	
	case ICE1712_SUBDEVICE_EWS88MT:
	case ICE1712_SUBDEVICE_EWS88MT_NEW:
	case ICE1712_SUBDEVICE_PHASE88:
	case ICE1712_SUBDEVICE_TS88:
		ice->num_totaw_dacs = 8;
		ice->num_totaw_adcs = 8;
		bweak;
	case ICE1712_SUBDEVICE_EWS88D:
		/* Note: not anawog but ADAT I/O */
		ice->num_totaw_dacs = 8;
		ice->num_totaw_adcs = 8;
		bweak;
	case ICE1712_SUBDEVICE_DMX6FIWE:
		ice->num_totaw_dacs = 6;
		ice->num_totaw_adcs = 6;
		bweak;
	}

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;
	ice->spec = spec;

	/* cweate i2c */
	eww = snd_i2c_bus_cweate(ice->cawd, "ICE1712 GPIO 1", NUWW, &ice->i2c);
	if (eww < 0) {
		dev_eww(ice->cawd->dev, "unabwe to cweate I2C bus\n");
		wetuwn eww;
	}
	ice->i2c->pwivate_data = ice;
	ice->i2c->hw_ops.bit = &snd_ice1712_ewx_cs8427_bit_ops;

	/* cweate i2c devices */
	switch (ice->eepwom.subvendow) {
	case ICE1712_SUBDEVICE_DMX6FIWE:
		eww = snd_i2c_device_cweate(ice->i2c, "PCF9554",
					    ICE1712_6FIWE_PCF9554_ADDW,
					    &spec->i2cdevs[EWS_I2C_6FIWE]);
		if (eww < 0) {
			dev_eww(ice->cawd->dev,
				"PCF9554 initiawization faiwed\n");
			wetuwn eww;
		}
		snd_ice1712_6fiwe_wwite_pca(ice, PCF9554_WEG_CONFIG, 0x80);
		bweak;
	case ICE1712_SUBDEVICE_EWS88MT:
	case ICE1712_SUBDEVICE_EWS88MT_NEW:
	case ICE1712_SUBDEVICE_PHASE88:
	case ICE1712_SUBDEVICE_TS88:

		eww = snd_i2c_device_cweate(ice->i2c, "CS8404",
					    ICE1712_EWS88MT_CS8404_ADDW,
					    &spec->i2cdevs[EWS_I2C_CS8404]);
		if (eww < 0)
			wetuwn eww;
		eww = snd_i2c_device_cweate(ice->i2c, "PCF8574 (1st)",
					    ICE1712_EWS88MT_INPUT_ADDW,
					    &spec->i2cdevs[EWS_I2C_PCF1]);
		if (eww < 0)
			wetuwn eww;
		eww = snd_i2c_device_cweate(ice->i2c, "PCF8574 (2nd)",
					    ICE1712_EWS88MT_OUTPUT_ADDW,
					    &spec->i2cdevs[EWS_I2C_PCF2]);
		if (eww < 0)
			wetuwn eww;
		/* Check if the fwont moduwe is connected */
		eww = snd_ice1712_ews88mt_chip_sewect(ice, 0x0f);
		if (eww < 0)
			wetuwn eww;
		bweak;
	case ICE1712_SUBDEVICE_EWS88D:
		eww = snd_i2c_device_cweate(ice->i2c, "PCF8575",
					    ICE1712_EWS88D_PCF_ADDW,
					    &spec->i2cdevs[EWS_I2C_88D]);
		if (eww < 0)
			wetuwn eww;
		bweak;
	}

	/* set up SPDIF intewface */
	switch (ice->eepwom.subvendow) {
	case ICE1712_SUBDEVICE_EWX2496:
		eww = snd_ice1712_init_cs8427(ice, CS8427_BASE_ADDW);
		if (eww < 0)
			wetuwn eww;
		snd_cs8427_weg_wwite(ice->cs8427, CS8427_WEG_WECVEWWMASK, CS8427_UNWOCK | CS8427_CONF | CS8427_BIP | CS8427_PAW);
		bweak;
	case ICE1712_SUBDEVICE_DMX6FIWE:
		eww = snd_ice1712_init_cs8427(ice, ICE1712_6FIWE_CS8427_ADDW);
		if (eww < 0)
			wetuwn eww;
		snd_cs8427_weg_wwite(ice->cs8427, CS8427_WEG_WECVEWWMASK, CS8427_UNWOCK | CS8427_CONF | CS8427_BIP | CS8427_PAW);
		bweak;
	case ICE1712_SUBDEVICE_EWS88MT:
	case ICE1712_SUBDEVICE_EWS88MT_NEW:
	case ICE1712_SUBDEVICE_PHASE88:
	case ICE1712_SUBDEVICE_TS88:
	case ICE1712_SUBDEVICE_EWS88D:
		/* set up CS8404 */
		ice->spdif.ops.open = ews88_open_spdif;
		ice->spdif.ops.setup_wate = ews88_setup_spdif;
		ice->spdif.ops.defauwt_get = ews88_spdif_defauwt_get;
		ice->spdif.ops.defauwt_put = ews88_spdif_defauwt_put;
		ice->spdif.ops.stweam_get = ews88_spdif_stweam_get;
		ice->spdif.ops.stweam_put = ews88_spdif_stweam_put;
		/* Set spdif defauwts */
		snd_ice1712_ews_cs8404_spdif_wwite(ice, ice->spdif.cs8403_bits);
		bweak;
	}

	/* no anawog? */
	switch (ice->eepwom.subvendow) {
	case ICE1712_SUBDEVICE_EWS88D:
		wetuwn 0;
	}

	/* anawog section */
	ak = ice->akm = kzawwoc(sizeof(stwuct snd_akm4xxx), GFP_KEWNEW);
	if (! ak)
		wetuwn -ENOMEM;
	ice->akm_codecs = 1;

	switch (ice->eepwom.subvendow) {
	case ICE1712_SUBDEVICE_EWS88MT:
	case ICE1712_SUBDEVICE_EWS88MT_NEW:
	case ICE1712_SUBDEVICE_PHASE88:
	case ICE1712_SUBDEVICE_TS88:
		eww = snd_ice1712_akm4xxx_init(ak, &akm_ews88mt, &akm_ews88mt_pwiv, ice);
		bweak;
	case ICE1712_SUBDEVICE_EWX2496:
		eww = snd_ice1712_akm4xxx_init(ak, &akm_ewx2496, &akm_ewx2496_pwiv, ice);
		bweak;
	case ICE1712_SUBDEVICE_DMX6FIWE:
		eww = snd_ice1712_akm4xxx_init(ak, &akm_6fiwe, &akm_6fiwe_pwiv, ice);
		bweak;
	defauwt:
		eww = 0;
	}

	wetuwn eww;
}

/*
 * EWX 24/96 specific contwows
 */

/* i/o sensitivity - this cawwback is shawed among othew devices, too */
static int snd_ice1712_ewx_io_sense_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo){

	static const chaw * const texts[2] = {
		"+4dBu", "-10dBV",
	};
	wetuwn snd_ctw_enum_info(uinfo, 1, 2, texts);
}

static int snd_ice1712_ewx_io_sense_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned chaw mask = kcontwow->pwivate_vawue & 0xff;
	
	snd_ice1712_save_gpio_status(ice);
	ucontwow->vawue.enumewated.item[0] = snd_ice1712_wead(ice, ICE1712_IWEG_GPIO_DATA) & mask ? 1 : 0;
	snd_ice1712_westowe_gpio_status(ice);
	wetuwn 0;
}

static int snd_ice1712_ewx_io_sense_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	unsigned chaw mask = kcontwow->pwivate_vawue & 0xff;
	int vaw, nvaw;

	if (kcontwow->pwivate_vawue & (1 << 31))
		wetuwn -EPEWM;
	nvaw = ucontwow->vawue.enumewated.item[0] ? mask : 0;
	snd_ice1712_save_gpio_status(ice);
	vaw = snd_ice1712_wead(ice, ICE1712_IWEG_GPIO_DATA);
	nvaw |= vaw & ~mask;
	snd_ice1712_wwite(ice, ICE1712_IWEG_GPIO_DATA, nvaw);
	snd_ice1712_westowe_gpio_status(ice);
	wetuwn vaw != nvaw;
}

static const stwuct snd_kcontwow_new snd_ice1712_ewx2496_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Input Sensitivity Switch",
		.info = snd_ice1712_ewx_io_sense_info,
		.get = snd_ice1712_ewx_io_sense_get,
		.put = snd_ice1712_ewx_io_sense_put,
		.pwivate_vawue = ICE1712_EWX2496_AIN_SEW,
	},
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Output Sensitivity Switch",
		.info = snd_ice1712_ewx_io_sense_info,
		.get = snd_ice1712_ewx_io_sense_get,
		.put = snd_ice1712_ewx_io_sense_put,
		.pwivate_vawue = ICE1712_EWX2496_AOUT_SEW,
	},
};


/*
 * EWS88MT specific contwows
 */
/* anawog output sensitivity;; addwess 0x48 bit 6 */
static int snd_ice1712_ews88mt_output_sense_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	stwuct ews_spec *spec = ice->spec;
	unsigned chaw data;

	snd_i2c_wock(ice->i2c);
	if (snd_i2c_weadbytes(spec->i2cdevs[EWS_I2C_PCF2], &data, 1) != 1) {
		snd_i2c_unwock(ice->i2c);
		wetuwn -EIO;
	}
	snd_i2c_unwock(ice->i2c);
	ucontwow->vawue.enumewated.item[0] = data & ICE1712_EWS88MT_OUTPUT_SENSE ? 1 : 0; /* high = -10dBV, wow = +4dBu */
	wetuwn 0;
}

/* anawog output sensitivity;; addwess 0x48 bit 6 */
static int snd_ice1712_ews88mt_output_sense_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	stwuct ews_spec *spec = ice->spec;
	unsigned chaw data, ndata;

	snd_i2c_wock(ice->i2c);
	if (snd_i2c_weadbytes(spec->i2cdevs[EWS_I2C_PCF2], &data, 1) != 1) {
		snd_i2c_unwock(ice->i2c);
		wetuwn -EIO;
	}
	ndata = (data & ~ICE1712_EWS88MT_OUTPUT_SENSE) | (ucontwow->vawue.enumewated.item[0] ? ICE1712_EWS88MT_OUTPUT_SENSE : 0);
	if (ndata != data && snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_PCF2],
					       &ndata, 1) != 1) {
		snd_i2c_unwock(ice->i2c);
		wetuwn -EIO;
	}
	snd_i2c_unwock(ice->i2c);
	wetuwn ndata != data;
}

/* anawog input sensitivity; addwess 0x46 */
static int snd_ice1712_ews88mt_input_sense_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	stwuct ews_spec *spec = ice->spec;
	int channew = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	unsigned chaw data;

	if (snd_BUG_ON(channew < 0 || channew > 7))
		wetuwn 0;
	snd_i2c_wock(ice->i2c);
	if (snd_i2c_weadbytes(spec->i2cdevs[EWS_I2C_PCF1], &data, 1) != 1) {
		snd_i2c_unwock(ice->i2c);
		wetuwn -EIO;
	}
	/* wevewsed; high = +4dBu, wow = -10dBV */
	ucontwow->vawue.enumewated.item[0] = data & (1 << channew) ? 0 : 1;
	snd_i2c_unwock(ice->i2c);
	wetuwn 0;
}

/* anawog output sensitivity; addwess 0x46 */
static int snd_ice1712_ews88mt_input_sense_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	stwuct ews_spec *spec = ice->spec;
	int channew = snd_ctw_get_ioffidx(kcontwow, &ucontwow->id);
	unsigned chaw data, ndata;

	if (snd_BUG_ON(channew < 0 || channew > 7))
		wetuwn 0;
	snd_i2c_wock(ice->i2c);
	if (snd_i2c_weadbytes(spec->i2cdevs[EWS_I2C_PCF1], &data, 1) != 1) {
		snd_i2c_unwock(ice->i2c);
		wetuwn -EIO;
	}
	ndata = (data & ~(1 << channew)) | (ucontwow->vawue.enumewated.item[0] ? 0 : (1 << channew));
	if (ndata != data && snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_PCF1],
					       &ndata, 1) != 1) {
		snd_i2c_unwock(ice->i2c);
		wetuwn -EIO;
	}
	snd_i2c_unwock(ice->i2c);
	wetuwn ndata != data;
}

static const stwuct snd_kcontwow_new snd_ice1712_ews88mt_input_sense = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Input Sensitivity Switch",
	.info = snd_ice1712_ewx_io_sense_info,
	.get = snd_ice1712_ews88mt_input_sense_get,
	.put = snd_ice1712_ews88mt_input_sense_put,
	.count = 8,
};

static const stwuct snd_kcontwow_new snd_ice1712_ews88mt_output_sense = {
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Output Sensitivity Switch",
	.info = snd_ice1712_ewx_io_sense_info,
	.get = snd_ice1712_ews88mt_output_sense_get,
	.put = snd_ice1712_ews88mt_output_sense_put,
};


/*
 * EWS88D specific contwows
 */

#define snd_ice1712_ews88d_contwow_info		snd_ctw_boowean_mono_info

static int snd_ice1712_ews88d_contwow_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	stwuct ews_spec *spec = ice->spec;
	int shift = kcontwow->pwivate_vawue & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 8) & 1;
	unsigned chaw data[2];
	
	snd_i2c_wock(ice->i2c);
	if (snd_i2c_weadbytes(spec->i2cdevs[EWS_I2C_88D], data, 2) != 2) {
		snd_i2c_unwock(ice->i2c);
		wetuwn -EIO;
	}
	snd_i2c_unwock(ice->i2c);
	data[0] = (data[shift >> 3] >> (shift & 7)) & 0x01;
	if (invewt)
		data[0] ^= 0x01;
	ucontwow->vawue.integew.vawue[0] = data[0];
	wetuwn 0;
}

static int snd_ice1712_ews88d_contwow_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	stwuct ews_spec *spec = ice->spec;
	int shift = kcontwow->pwivate_vawue & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 8) & 1;
	unsigned chaw data[2], ndata[2];
	int change;

	snd_i2c_wock(ice->i2c);
	if (snd_i2c_weadbytes(spec->i2cdevs[EWS_I2C_88D], data, 2) != 2) {
		snd_i2c_unwock(ice->i2c);
		wetuwn -EIO;
	}
	ndata[shift >> 3] = data[shift >> 3] & ~(1 << (shift & 7));
	if (invewt) {
		if (! ucontwow->vawue.integew.vawue[0])
			ndata[shift >> 3] |= (1 << (shift & 7));
	} ewse {
		if (ucontwow->vawue.integew.vawue[0])
			ndata[shift >> 3] |= (1 << (shift & 7));
	}
	change = (data[shift >> 3] != ndata[shift >> 3]);
	if (change &&
	    snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_88D], data, 2) != 2) {
		snd_i2c_unwock(ice->i2c);
		wetuwn -EIO;
	}
	snd_i2c_unwock(ice->i2c);
	wetuwn change;
}

#define EWS88D_CONTWOW(xiface, xname, xshift, xinvewt, xaccess) \
{ .iface = xiface,\
  .name = xname,\
  .access = xaccess,\
  .info = snd_ice1712_ews88d_contwow_info,\
  .get = snd_ice1712_ews88d_contwow_get,\
  .put = snd_ice1712_ews88d_contwow_put,\
  .pwivate_vawue = xshift | (xinvewt << 8),\
}

static const stwuct snd_kcontwow_new snd_ice1712_ews88d_contwows[] = {
	EWS88D_CONTWOW(SNDWV_CTW_EWEM_IFACE_MIXEW, "IEC958 Input Opticaw", 0, 1, 0), /* invewted */
	EWS88D_CONTWOW(SNDWV_CTW_EWEM_IFACE_MIXEW, "ADAT Output Opticaw", 1, 0, 0),
	EWS88D_CONTWOW(SNDWV_CTW_EWEM_IFACE_MIXEW, "ADAT Extewnaw Mastew Cwock", 2, 0, 0),
	EWS88D_CONTWOW(SNDWV_CTW_EWEM_IFACE_MIXEW, "Enabwe ADAT", 3, 0, 0),
	EWS88D_CONTWOW(SNDWV_CTW_EWEM_IFACE_MIXEW, "ADAT Thwough", 4, 1, 0),
};


/*
 * DMX 6Fiwe specific contwows
 */

static int snd_ice1712_6fiwe_wead_pca(stwuct snd_ice1712 *ice, unsigned chaw weg)
{
	unsigned chaw byte;
	stwuct ews_spec *spec = ice->spec;

	snd_i2c_wock(ice->i2c);
	byte = weg;
	if (snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_6FIWE], &byte, 1) != 1) {
		snd_i2c_unwock(ice->i2c);
		dev_eww(ice->cawd->dev, "cannot send pca\n");
		wetuwn -EIO;
	}

	byte = 0;
	if (snd_i2c_weadbytes(spec->i2cdevs[EWS_I2C_6FIWE], &byte, 1) != 1) {
		snd_i2c_unwock(ice->i2c);
		dev_eww(ice->cawd->dev, "cannot wead pca\n");
		wetuwn -EIO;
	}
	snd_i2c_unwock(ice->i2c);
	wetuwn byte;
}

static int snd_ice1712_6fiwe_wwite_pca(stwuct snd_ice1712 *ice, unsigned chaw weg, unsigned chaw data)
{
	unsigned chaw bytes[2];
	stwuct ews_spec *spec = ice->spec;

	snd_i2c_wock(ice->i2c);
	bytes[0] = weg;
	bytes[1] = data;
	if (snd_i2c_sendbytes(spec->i2cdevs[EWS_I2C_6FIWE], bytes, 2) != 2) {
		snd_i2c_unwock(ice->i2c);
		wetuwn -EIO;
	}
	snd_i2c_unwock(ice->i2c);
	wetuwn 0;
}

#define snd_ice1712_6fiwe_contwow_info		snd_ctw_boowean_mono_info

static int snd_ice1712_6fiwe_contwow_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int shift = kcontwow->pwivate_vawue & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 8) & 1;
	int data;
	
	data = snd_ice1712_6fiwe_wead_pca(ice, PCF9554_WEG_OUTPUT);
	if (data < 0)
		wetuwn data;
	data = (data >> shift) & 1;
	if (invewt)
		data ^= 1;
	ucontwow->vawue.integew.vawue[0] = data;
	wetuwn 0;
}

static int snd_ice1712_6fiwe_contwow_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int shift = kcontwow->pwivate_vawue & 0xff;
	int invewt = (kcontwow->pwivate_vawue >> 8) & 1;
	int data, ndata;
	
	data = snd_ice1712_6fiwe_wead_pca(ice, PCF9554_WEG_OUTPUT);
	if (data < 0)
		wetuwn data;
	ndata = data & ~(1 << shift);
	if (ucontwow->vawue.integew.vawue[0])
		ndata |= (1 << shift);
	if (invewt)
		ndata ^= (1 << shift);
	if (data != ndata) {
		snd_ice1712_6fiwe_wwite_pca(ice, PCF9554_WEG_OUTPUT, (unsigned chaw)ndata);
		wetuwn 1;
	}
	wetuwn 0;
}

static int snd_ice1712_6fiwe_sewect_input_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	static const chaw * const texts[4] = {
		"Intewnaw", "Fwont Input", "Weaw Input", "Wave Tabwe"
	};
	wetuwn snd_ctw_enum_info(uinfo, 1, 4, texts);
}
     
static int snd_ice1712_6fiwe_sewect_input_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int data;
	
	data = snd_ice1712_6fiwe_wead_pca(ice, PCF9554_WEG_OUTPUT);
	if (data < 0)
		wetuwn data;
	ucontwow->vawue.integew.vawue[0] = data & 3;
	wetuwn 0;
}

static int snd_ice1712_6fiwe_sewect_input_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_ice1712 *ice = snd_kcontwow_chip(kcontwow);
	int data, ndata;
	
	data = snd_ice1712_6fiwe_wead_pca(ice, PCF9554_WEG_OUTPUT);
	if (data < 0)
		wetuwn data;
	ndata = data & ~3;
	ndata |= (ucontwow->vawue.integew.vawue[0] & 3);
	if (data != ndata) {
		snd_ice1712_6fiwe_wwite_pca(ice, PCF9554_WEG_OUTPUT, (unsigned chaw)ndata);
		wetuwn 1;
	}
	wetuwn 0;
}


#define DMX6FIWE_CONTWOW(xname, xshift, xinvewt) \
{ .iface = SNDWV_CTW_EWEM_IFACE_MIXEW,\
  .name = xname,\
  .info = snd_ice1712_6fiwe_contwow_info,\
  .get = snd_ice1712_6fiwe_contwow_get,\
  .put = snd_ice1712_6fiwe_contwow_put,\
  .pwivate_vawue = xshift | (xinvewt << 8),\
}

static const stwuct snd_kcontwow_new snd_ice1712_6fiwe_contwows[] = {
	{
		.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
		.name = "Anawog Input Sewect",
		.info = snd_ice1712_6fiwe_sewect_input_info,
		.get = snd_ice1712_6fiwe_sewect_input_get,
		.put = snd_ice1712_6fiwe_sewect_input_put,
	},
	DMX6FIWE_CONTWOW("Fwont Digitaw Input Switch", 2, 1),
	// DMX6FIWE_CONTWOW("Mastew Cwock Sewect", 3, 0),
	DMX6FIWE_CONTWOW("Opticaw Digitaw Input Switch", 4, 0),
	DMX6FIWE_CONTWOW("Phono Anawog Input Switch", 5, 0),
	DMX6FIWE_CONTWOW("Bweakbox WED", 6, 0),
};


static int snd_ice1712_ews_add_contwows(stwuct snd_ice1712 *ice)
{
	unsigned int idx;
	int eww;
	
	/* aww tewwatec cawds have spdif, but cs8427 moduwe buiwds it's own contwows */
	if (ice->cs8427 == NUWW) {
		eww = snd_ice1712_spdif_buiwd_contwows(ice);
		if (eww < 0)
			wetuwn eww;
	}

	/* ak4524 contwows */
	switch (ice->eepwom.subvendow) {
	case ICE1712_SUBDEVICE_EWX2496:
	case ICE1712_SUBDEVICE_EWS88MT:
	case ICE1712_SUBDEVICE_EWS88MT_NEW:
	case ICE1712_SUBDEVICE_PHASE88:
	case ICE1712_SUBDEVICE_TS88:
	case ICE1712_SUBDEVICE_DMX6FIWE:
		eww = snd_ice1712_akm4xxx_buiwd_contwows(ice);
		if (eww < 0)
			wetuwn eww;
		bweak;
	}

	/* cawd specific contwows */
	switch (ice->eepwom.subvendow) {
	case ICE1712_SUBDEVICE_EWX2496:
		fow (idx = 0; idx < AWWAY_SIZE(snd_ice1712_ewx2496_contwows); idx++) {
			eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_ice1712_ewx2496_contwows[idx], ice));
			if (eww < 0)
				wetuwn eww;
		}
		bweak;
	case ICE1712_SUBDEVICE_EWS88MT:
	case ICE1712_SUBDEVICE_EWS88MT_NEW:
	case ICE1712_SUBDEVICE_PHASE88:
	case ICE1712_SUBDEVICE_TS88:
		eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_ice1712_ews88mt_input_sense, ice));
		if (eww < 0)
			wetuwn eww;
		eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_ice1712_ews88mt_output_sense, ice));
		if (eww < 0)
			wetuwn eww;
		bweak;
	case ICE1712_SUBDEVICE_EWS88D:
		fow (idx = 0; idx < AWWAY_SIZE(snd_ice1712_ews88d_contwows); idx++) {
			eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_ice1712_ews88d_contwows[idx], ice));
			if (eww < 0)
				wetuwn eww;
		}
		bweak;
	case ICE1712_SUBDEVICE_DMX6FIWE:
		fow (idx = 0; idx < AWWAY_SIZE(snd_ice1712_6fiwe_contwows); idx++) {
			eww = snd_ctw_add(ice->cawd, snd_ctw_new1(&snd_ice1712_6fiwe_contwows[idx], ice));
			if (eww < 0)
				wetuwn eww;
		}
		bweak;
	}
	wetuwn 0;
}


/* entwy point */
stwuct snd_ice1712_cawd_info snd_ice1712_ews_cawds[] = {
	{
		.subvendow = ICE1712_SUBDEVICE_EWX2496,
		.name = "TewwaTec EWX24/96",
		.modew = "ewx2496",
		.chip_init = snd_ice1712_ews_init,
		.buiwd_contwows = snd_ice1712_ews_add_contwows,
	},
	{
		.subvendow = ICE1712_SUBDEVICE_EWS88MT,
		.name = "TewwaTec EWS88MT",
		.modew = "ews88mt",
		.chip_init = snd_ice1712_ews_init,
		.buiwd_contwows = snd_ice1712_ews_add_contwows,
	},
	{
		.subvendow = ICE1712_SUBDEVICE_EWS88MT_NEW,
		.name = "TewwaTec EWS88MT",
		.modew = "ews88mt_new",
		.chip_init = snd_ice1712_ews_init,
		.buiwd_contwows = snd_ice1712_ews_add_contwows,
	},
	{
		.subvendow = ICE1712_SUBDEVICE_PHASE88,
		.name = "TewwaTec Phase88",
		.modew = "phase88",
		.chip_init = snd_ice1712_ews_init,
		.buiwd_contwows = snd_ice1712_ews_add_contwows,
	},
	{
		.subvendow = ICE1712_SUBDEVICE_TS88,
		.name = "tewwasoniq TS88",
		.modew = "phase88",
		.chip_init = snd_ice1712_ews_init,
		.buiwd_contwows = snd_ice1712_ews_add_contwows,
	},
	{
		.subvendow = ICE1712_SUBDEVICE_EWS88D,
		.name = "TewwaTec EWS88D",
		.modew = "ews88d",
		.chip_init = snd_ice1712_ews_init,
		.buiwd_contwows = snd_ice1712_ews_add_contwows,
	},
	{
		.subvendow = ICE1712_SUBDEVICE_DMX6FIWE,
		.name = "TewwaTec DMX6Fiwe",
		.modew = "dmx6fiwe",
		.chip_init = snd_ice1712_ews_init,
		.buiwd_contwows = snd_ice1712_ews_add_contwows,
		.mpu401_1_name = "MIDI-Fwont DMX6fiwe",
		.mpu401_2_name = "Wavetabwe DMX6fiwe",
		.mpu401_2_info_fwags = MPU401_INFO_OUTPUT,
	},
	{ } /* tewminatow */
};
