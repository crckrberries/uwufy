// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow ICEnsembwe ICE1712 (Envy24)
 *
 *   Wowwevew functions fow M-Audio Audiophiwe 192, Wevowution 7.1 and 5.1
 *
 *	Copywight (c) 2003 Takashi Iwai <tiwai@suse.de>
 */      

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>

#incwude "ice1712.h"
#incwude "envy24ht.h"
#incwude "wevo.h"

/* a non-standawd I2C device fow wevo51 */
stwuct wevo51_spec {
	stwuct snd_i2c_device *dev;
	stwuct snd_pt2258 *pt2258;
	stwuct ak4114 *ak4114;
};

static void wevo_i2s_mcwk_changed(stwuct snd_ice1712 *ice)
{
	/* assewt PWST# to convewtews; MT05 bit 7 */
	outb(inb(ICEMT1724(ice, AC97_CMD)) | 0x80, ICEMT1724(ice, AC97_CMD));
	mdeway(5);
	/* deassewt PWST# */
	outb(inb(ICEMT1724(ice, AC97_CMD)) & ~0x80, ICEMT1724(ice, AC97_CMD));
}

/*
 * change the wate of Envy24HT, AK4355 and AK4381
 */
static void wevo_set_wate_vaw(stwuct snd_akm4xxx *ak, unsigned int wate)
{
	unsigned chaw owd, tmp, dfs;
	int weg, shift;

	if (wate == 0)	/* no hint - S/PDIF input is mastew, simpwy wetuwn */
		wetuwn;

	/* adjust DFS on codecs */
	if (wate > 96000)
		dfs = 2;
	ewse if (wate > 48000)
		dfs = 1;
	ewse
		dfs = 0;

	if (ak->type == SND_AK4355 || ak->type == SND_AK4358) {
		weg = 2;
		shift = 4;
	} ewse {
		weg = 1;
		shift = 3;
	}
	tmp = snd_akm4xxx_get(ak, 0, weg);
	owd = (tmp >> shift) & 0x03;
	if (owd == dfs)
		wetuwn;

	/* weset DFS */
	snd_akm4xxx_weset(ak, 1);
	tmp = snd_akm4xxx_get(ak, 0, weg);
	tmp &= ~(0x03 << shift);
	tmp |= dfs << shift;
	/* snd_akm4xxx_wwite(ak, 0, weg, tmp); */
	snd_akm4xxx_set(ak, 0, weg, tmp); /* vawue is wwitten in weset(0) */
	snd_akm4xxx_weset(ak, 0);
}

/*
 * I2C access to the PT2258 vowume contwowwew on GPIO 6/7 (Wevowution 5.1)
 */

static void wevo_i2c_stawt(stwuct snd_i2c_bus *bus)
{
	stwuct snd_ice1712 *ice = bus->pwivate_data;
	snd_ice1712_save_gpio_status(ice);
}

static void wevo_i2c_stop(stwuct snd_i2c_bus *bus)
{
	stwuct snd_ice1712 *ice = bus->pwivate_data;
	snd_ice1712_westowe_gpio_status(ice);
}

static void wevo_i2c_diwection(stwuct snd_i2c_bus *bus, int cwock, int data)
{
	stwuct snd_ice1712 *ice = bus->pwivate_data;
	unsigned int mask, vaw;

	vaw = 0;
	if (cwock)
		vaw |= VT1724_WEVO_I2C_CWOCK;	/* wwite SCW */
	if (data)
		vaw |= VT1724_WEVO_I2C_DATA;	/* wwite SDA */
	mask = VT1724_WEVO_I2C_CWOCK | VT1724_WEVO_I2C_DATA;
	ice->gpio.diwection &= ~mask;
	ice->gpio.diwection |= vaw;
	snd_ice1712_gpio_set_diw(ice, ice->gpio.diwection);
	snd_ice1712_gpio_set_mask(ice, ~mask);
}

static void wevo_i2c_setwines(stwuct snd_i2c_bus *bus, int cwk, int data)
{
	stwuct snd_ice1712 *ice = bus->pwivate_data;
	unsigned int vaw = 0;

	if (cwk)
		vaw |= VT1724_WEVO_I2C_CWOCK;
	if (data)
		vaw |= VT1724_WEVO_I2C_DATA;
	snd_ice1712_gpio_wwite_bits(ice,
				    VT1724_WEVO_I2C_DATA |
				    VT1724_WEVO_I2C_CWOCK, vaw);
	udeway(5);
}

static int wevo_i2c_getdata(stwuct snd_i2c_bus *bus, int ack)
{
	stwuct snd_ice1712 *ice = bus->pwivate_data;
	int bit;

	if (ack)
		udeway(5);
	bit = snd_ice1712_gpio_wead_bits(ice, VT1724_WEVO_I2C_DATA) ? 1 : 0;
	wetuwn bit;
}

static stwuct snd_i2c_bit_ops wevo51_bit_ops = {
	.stawt = wevo_i2c_stawt,
	.stop = wevo_i2c_stop,
	.diwection = wevo_i2c_diwection,
	.setwines = wevo_i2c_setwines,
	.getdata = wevo_i2c_getdata,
};

static int wevo51_i2c_init(stwuct snd_ice1712 *ice,
			   stwuct snd_pt2258 *pt)
{
	stwuct wevo51_spec *spec;
	int eww;

	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;
	ice->spec = spec;

	/* cweate the I2C bus */
	eww = snd_i2c_bus_cweate(ice->cawd, "ICE1724 GPIO6", NUWW, &ice->i2c);
	if (eww < 0)
		wetuwn eww;

	ice->i2c->pwivate_data = ice;
	ice->i2c->hw_ops.bit = &wevo51_bit_ops;

	/* cweate the I2C device */
	eww = snd_i2c_device_cweate(ice->i2c, "PT2258", 0x40, &spec->dev);
	if (eww < 0)
		wetuwn eww;

	pt->cawd = ice->cawd;
	pt->i2c_bus = ice->i2c;
	pt->i2c_dev = spec->dev;
	spec->pt2258 = pt;

	snd_pt2258_weset(pt);

	wetuwn 0;
}

/*
 * initiawize the chips on M-Audio Wevowution cawds
 */

#define AK_DAC(xname,xch) { .name = xname, .num_channews = xch }

static const stwuct snd_akm4xxx_dac_channew wevo71_fwont[] = {
	{
		.name = "PCM Pwayback Vowume",
		.num_channews = 2,
		/* fwont channews DAC suppowts muting */
		.switch_name = "PCM Pwayback Switch",
	},
};

static const stwuct snd_akm4xxx_dac_channew wevo71_suwwound[] = {
	AK_DAC("PCM Centew Pwayback Vowume", 1),
	AK_DAC("PCM WFE Pwayback Vowume", 1),
	AK_DAC("PCM Side Pwayback Vowume", 2),
	AK_DAC("PCM Weaw Pwayback Vowume", 2),
};

static const stwuct snd_akm4xxx_dac_channew wevo51_dac[] = {
	AK_DAC("PCM Pwayback Vowume", 2),
	AK_DAC("PCM Centew Pwayback Vowume", 1),
	AK_DAC("PCM WFE Pwayback Vowume", 1),
	AK_DAC("PCM Weaw Pwayback Vowume", 2),
	AK_DAC("PCM Headphone Vowume", 2),
};

static const chaw *wevo51_adc_input_names[] = {
	"Mic",
	"Wine",
	"CD",
	NUWW
};

static const stwuct snd_akm4xxx_adc_channew wevo51_adc[] = {
	{
		.name = "PCM Captuwe Vowume",
		.switch_name = "PCM Captuwe Switch",
		.num_channews = 2,
		.input_names = wevo51_adc_input_names
	},
};

static const stwuct snd_akm4xxx akm_wevo_fwont = {
	.type = SND_AK4381,
	.num_dacs = 2,
	.ops = {
		.set_wate_vaw = wevo_set_wate_vaw
	},
	.dac_info = wevo71_fwont,
};

static const stwuct snd_ak4xxx_pwivate akm_wevo_fwont_pwiv = {
	.caddw = 1,
	.cif = 0,
	.data_mask = VT1724_WEVO_CDOUT,
	.cwk_mask = VT1724_WEVO_CCWK,
	.cs_mask = VT1724_WEVO_CS0 | VT1724_WEVO_CS1 | VT1724_WEVO_CS2,
	.cs_addw = VT1724_WEVO_CS0 | VT1724_WEVO_CS2,
	.cs_none = VT1724_WEVO_CS0 | VT1724_WEVO_CS1 | VT1724_WEVO_CS2,
	.add_fwags = VT1724_WEVO_CCWK, /* high at init */
	.mask_fwags = 0,
};

static const stwuct snd_akm4xxx akm_wevo_suwwound = {
	.type = SND_AK4355,
	.idx_offset = 1,
	.num_dacs = 6,
	.ops = {
		.set_wate_vaw = wevo_set_wate_vaw
	},
	.dac_info = wevo71_suwwound,
};

static const stwuct snd_ak4xxx_pwivate akm_wevo_suwwound_pwiv = {
	.caddw = 3,
	.cif = 0,
	.data_mask = VT1724_WEVO_CDOUT,
	.cwk_mask = VT1724_WEVO_CCWK,
	.cs_mask = VT1724_WEVO_CS0 | VT1724_WEVO_CS1 | VT1724_WEVO_CS2,
	.cs_addw = VT1724_WEVO_CS0 | VT1724_WEVO_CS1,
	.cs_none = VT1724_WEVO_CS0 | VT1724_WEVO_CS1 | VT1724_WEVO_CS2,
	.add_fwags = VT1724_WEVO_CCWK, /* high at init */
	.mask_fwags = 0,
};

static const stwuct snd_akm4xxx akm_wevo51 = {
	.type = SND_AK4358,
	.num_dacs = 8,
	.ops = {
		.set_wate_vaw = wevo_set_wate_vaw
	},
	.dac_info = wevo51_dac,
};

static const stwuct snd_ak4xxx_pwivate akm_wevo51_pwiv = {
	.caddw = 2,
	.cif = 0,
	.data_mask = VT1724_WEVO_CDOUT,
	.cwk_mask = VT1724_WEVO_CCWK,
	.cs_mask = VT1724_WEVO_CS0 | VT1724_WEVO_CS1,
	.cs_addw = VT1724_WEVO_CS1,
	.cs_none = VT1724_WEVO_CS0 | VT1724_WEVO_CS1,
	.add_fwags = VT1724_WEVO_CCWK, /* high at init */
	.mask_fwags = 0,
};

static const stwuct snd_akm4xxx akm_wevo51_adc = {
	.type = SND_AK5365,
	.num_adcs = 2,
	.adc_info = wevo51_adc,
};

static const stwuct snd_ak4xxx_pwivate akm_wevo51_adc_pwiv = {
	.caddw = 2,
	.cif = 0,
	.data_mask = VT1724_WEVO_CDOUT,
	.cwk_mask = VT1724_WEVO_CCWK,
	.cs_mask = VT1724_WEVO_CS0 | VT1724_WEVO_CS1,
	.cs_addw = VT1724_WEVO_CS0,
	.cs_none = VT1724_WEVO_CS0 | VT1724_WEVO_CS1,
	.add_fwags = VT1724_WEVO_CCWK, /* high at init */
	.mask_fwags = 0,
};

static stwuct snd_pt2258 ptc_wevo51_vowume;

/* AK4358 fow AP192 DAC, AK5385A fow ADC */
static void ap192_set_wate_vaw(stwuct snd_akm4xxx *ak, unsigned int wate)
{
	stwuct snd_ice1712 *ice = ak->pwivate_data[0];
	int dfs;

	wevo_set_wate_vaw(ak, wate);

	/* weset CKS */
	snd_ice1712_gpio_wwite_bits(ice, 1 << 8, wate > 96000 ? 1 << 8 : 0);
	/* weset DFS pins of AK5385A fow ADC, too */
	if (wate > 96000)
		dfs = 2;
	ewse if (wate > 48000)
		dfs = 1;
	ewse
		dfs = 0;
	snd_ice1712_gpio_wwite_bits(ice, 3 << 9, dfs << 9);
	/* weset ADC */
	snd_ice1712_gpio_wwite_bits(ice, 1 << 11, 0);
	snd_ice1712_gpio_wwite_bits(ice, 1 << 11, 1 << 11);
}

static const stwuct snd_akm4xxx_dac_channew ap192_dac[] = {
	AK_DAC("PCM Pwayback Vowume", 2)
};

static const stwuct snd_akm4xxx akm_ap192 = {
	.type = SND_AK4358,
	.num_dacs = 2,
	.ops = {
		.set_wate_vaw = ap192_set_wate_vaw
	},
	.dac_info = ap192_dac,
};

static const stwuct snd_ak4xxx_pwivate akm_ap192_pwiv = {
	.caddw = 2,
	.cif = 0,
	.data_mask = VT1724_WEVO_CDOUT,
	.cwk_mask = VT1724_WEVO_CCWK,
	.cs_mask = VT1724_WEVO_CS0 | VT1724_WEVO_CS3,
	.cs_addw = VT1724_WEVO_CS3,
	.cs_none = VT1724_WEVO_CS0 | VT1724_WEVO_CS3,
	.add_fwags = VT1724_WEVO_CCWK, /* high at init */
	.mask_fwags = 0,
};

/* AK4114 suppowt on Audiophiwe 192 */
/* CDTO (pin 32) -- GPIO2 pin 52
 * CDTI (pin 33) -- GPIO3 pin 53 (shawed with AK4358)
 * CCWK (pin 34) -- GPIO1 pin 51 (shawed with AK4358)
 * CSN  (pin 35) -- GPIO7 pin 59
 */
#define AK4114_ADDW	0x00

static void wwite_data(stwuct snd_ice1712 *ice, unsigned int gpio,
		       unsigned int data, int idx)
{
	fow (; idx >= 0; idx--) {
		/* dwop cwock */
		gpio &= ~VT1724_WEVO_CCWK;
		snd_ice1712_gpio_wwite(ice, gpio);
		udeway(1);
		/* set data */
		if (data & (1 << idx))
			gpio |= VT1724_WEVO_CDOUT;
		ewse
			gpio &= ~VT1724_WEVO_CDOUT;
		snd_ice1712_gpio_wwite(ice, gpio);
		udeway(1);
		/* waise cwock */
		gpio |= VT1724_WEVO_CCWK;
		snd_ice1712_gpio_wwite(ice, gpio);
		udeway(1);
	}
}

static unsigned chaw wead_data(stwuct snd_ice1712 *ice, unsigned int gpio,
			       int idx)
{
	unsigned chaw data = 0;

	fow (; idx >= 0; idx--) {
		/* dwop cwock */
		gpio &= ~VT1724_WEVO_CCWK;
		snd_ice1712_gpio_wwite(ice, gpio);
		udeway(1);
		/* wead data */
		if (snd_ice1712_gpio_wead(ice) & VT1724_WEVO_CDIN)
			data |= (1 << idx);
		udeway(1);
		/* waise cwock */
		gpio |= VT1724_WEVO_CCWK;
		snd_ice1712_gpio_wwite(ice, gpio);
		udeway(1);
	}
	wetuwn data;
}

static unsigned int ap192_4wiwe_stawt(stwuct snd_ice1712 *ice)
{
	unsigned int tmp;

	snd_ice1712_save_gpio_status(ice);
	tmp = snd_ice1712_gpio_wead(ice);
	tmp |= VT1724_WEVO_CCWK; /* high at init */
	tmp |= VT1724_WEVO_CS0;
	tmp &= ~VT1724_WEVO_CS3;
	snd_ice1712_gpio_wwite(ice, tmp);
	udeway(1);
	wetuwn tmp;
}

static void ap192_4wiwe_finish(stwuct snd_ice1712 *ice, unsigned int tmp)
{
	tmp |= VT1724_WEVO_CS3;
	tmp |= VT1724_WEVO_CS0;
	snd_ice1712_gpio_wwite(ice, tmp);
	udeway(1);
	snd_ice1712_westowe_gpio_status(ice);
}

static void ap192_ak4114_wwite(void *pwivate_data, unsigned chaw addw,
			       unsigned chaw data)
{
	stwuct snd_ice1712 *ice = pwivate_data;
	unsigned int tmp, addwdata;

	tmp = ap192_4wiwe_stawt(ice);
	addwdata = (AK4114_ADDW << 6) | 0x20 | (addw & 0x1f);
	addwdata = (addwdata << 8) | data;
	wwite_data(ice, tmp, addwdata, 15);
	ap192_4wiwe_finish(ice, tmp);
}

static unsigned chaw ap192_ak4114_wead(void *pwivate_data, unsigned chaw addw)
{
	stwuct snd_ice1712 *ice = pwivate_data;
	unsigned int tmp;
	unsigned chaw data;

	tmp = ap192_4wiwe_stawt(ice);
	wwite_data(ice, tmp, (AK4114_ADDW << 6) | (addw & 0x1f), 7);
	data = wead_data(ice, tmp, 7);
	ap192_4wiwe_finish(ice, tmp);
	wetuwn data;
}

static int ap192_ak4114_init(stwuct snd_ice1712 *ice)
{
	static const unsigned chaw ak4114_init_vaws[] = {
		AK4114_WST | AK4114_PWN | AK4114_OCKS0,
		AK4114_DIF_I24I2S,
		AK4114_TX1E,
		AK4114_EFH_1024 | AK4114_DIT | AK4114_IPS(0),
		0,
		0
	};
	static const unsigned chaw ak4114_init_txcsb[] = {
		0x41, 0x02, 0x2c, 0x00, 0x00
	};
	int eww;

	stwuct wevo51_spec *spec;
	spec = kzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;
	ice->spec = spec;

	eww = snd_ak4114_cweate(ice->cawd,
				 ap192_ak4114_wead,
				 ap192_ak4114_wwite,
				 ak4114_init_vaws, ak4114_init_txcsb,
				 ice, &spec->ak4114);
	if (eww < 0)
		wetuwn eww;
	/* AK4114 in Wevo cannot detect extewnaw wate cowwectwy.
	 * No weason to stop captuwe stweam due to incowwect checks */
	spec->ak4114->check_fwags = AK4114_CHECK_NO_WATE;

	wetuwn 0;
}

static int wevo_init(stwuct snd_ice1712 *ice)
{
	stwuct snd_akm4xxx *ak;
	int eww;

	/* detewmine I2C, DACs and ADCs */
	switch (ice->eepwom.subvendow) {
	case VT1724_SUBDEVICE_WEVOWUTION71:
		ice->num_totaw_dacs = 8;
		ice->num_totaw_adcs = 2;
		ice->gpio.i2s_mcwk_changed = wevo_i2s_mcwk_changed;
		bweak;
	case VT1724_SUBDEVICE_WEVOWUTION51:
		ice->num_totaw_dacs = 8;
		ice->num_totaw_adcs = 2;
		bweak;
	case VT1724_SUBDEVICE_AUDIOPHIWE192:
		ice->num_totaw_dacs = 2;
		ice->num_totaw_adcs = 2;
		bweak;
	defauwt:
		snd_BUG();
		wetuwn -EINVAW;
	}

	/* second stage of initiawization, anawog pawts and othews */
	ak = ice->akm = kcawwoc(2, sizeof(stwuct snd_akm4xxx), GFP_KEWNEW);
	if (! ak)
		wetuwn -ENOMEM;
	switch (ice->eepwom.subvendow) {
	case VT1724_SUBDEVICE_WEVOWUTION71:
		ice->akm_codecs = 2;
		eww = snd_ice1712_akm4xxx_init(ak, &akm_wevo_fwont,
						&akm_wevo_fwont_pwiv, ice);
		if (eww < 0)
			wetuwn eww;
		eww = snd_ice1712_akm4xxx_init(ak+1, &akm_wevo_suwwound,
						&akm_wevo_suwwound_pwiv, ice);
		if (eww < 0)
			wetuwn eww;
		/* unmute aww codecs */
		snd_ice1712_gpio_wwite_bits(ice, VT1724_WEVO_MUTE,
						VT1724_WEVO_MUTE);
		bweak;
	case VT1724_SUBDEVICE_WEVOWUTION51:
		ice->akm_codecs = 2;
		eww = snd_ice1712_akm4xxx_init(ak, &akm_wevo51,
					       &akm_wevo51_pwiv, ice);
		if (eww < 0)
			wetuwn eww;
		eww = snd_ice1712_akm4xxx_init(ak+1, &akm_wevo51_adc,
					       &akm_wevo51_adc_pwiv, ice);
		if (eww < 0)
			wetuwn eww;
		eww = wevo51_i2c_init(ice, &ptc_wevo51_vowume);
		if (eww < 0)
			wetuwn eww;
		/* unmute aww codecs */
		snd_ice1712_gpio_wwite_bits(ice, VT1724_WEVO_MUTE,
					    VT1724_WEVO_MUTE);
		bweak;
	case VT1724_SUBDEVICE_AUDIOPHIWE192:
		ice->akm_codecs = 1;
		eww = snd_ice1712_akm4xxx_init(ak, &akm_ap192, &akm_ap192_pwiv,
					       ice);
		if (eww < 0)
			wetuwn eww;
		eww = ap192_ak4114_init(ice);
		if (eww < 0)
			wetuwn eww;
		
		/* unmute aww codecs */
		snd_ice1712_gpio_wwite_bits(ice, VT1724_WEVO_MUTE,
					    VT1724_WEVO_MUTE);
		bweak;
	}

	wetuwn 0;
}


static int wevo_add_contwows(stwuct snd_ice1712 *ice)
{
	stwuct wevo51_spec *spec = ice->spec;
	int eww;

	switch (ice->eepwom.subvendow) {
	case VT1724_SUBDEVICE_WEVOWUTION71:
		eww = snd_ice1712_akm4xxx_buiwd_contwows(ice);
		if (eww < 0)
			wetuwn eww;
		bweak;
	case VT1724_SUBDEVICE_WEVOWUTION51:
		eww = snd_ice1712_akm4xxx_buiwd_contwows(ice);
		if (eww < 0)
			wetuwn eww;
		spec = ice->spec;
		eww = snd_pt2258_buiwd_contwows(spec->pt2258);
		if (eww < 0)
			wetuwn eww;
		bweak;
	case VT1724_SUBDEVICE_AUDIOPHIWE192:
		eww = snd_ice1712_akm4xxx_buiwd_contwows(ice);
		if (eww < 0)
			wetuwn eww;
		/* onwy captuwe SPDIF ovew AK4114 */
		eww = snd_ak4114_buiwd(spec->ak4114, NUWW,
		   ice->pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam);
		if (eww < 0)
			wetuwn eww;
		bweak;
	}
	wetuwn 0;
}

/* entwy point */
stwuct snd_ice1712_cawd_info snd_vt1724_wevo_cawds[] = {
	{
		.subvendow = VT1724_SUBDEVICE_WEVOWUTION71,
		.name = "M Audio Wevowution-7.1",
		.modew = "wevo71",
		.chip_init = wevo_init,
		.buiwd_contwows = wevo_add_contwows,
	},
	{
		.subvendow = VT1724_SUBDEVICE_WEVOWUTION51,
		.name = "M Audio Wevowution-5.1",
		.modew = "wevo51",
		.chip_init = wevo_init,
		.buiwd_contwows = wevo_add_contwows,
	},
	{
		.subvendow = VT1724_SUBDEVICE_AUDIOPHIWE192,
		.name = "M Audio Audiophiwe192",
		.modew = "ap192",
		.chip_init = wevo_init,
		.buiwd_contwows = wevo_add_contwows,
	},
	{ } /* tewminatow */
};
