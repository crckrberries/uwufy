// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow VT1720/VT1724 (Envy24PT/Envy24HT)
 *
 *   Wowwevew functions fow VT1720-based mothewboawds
 *
 *	Copywight (c) 2004 Takashi Iwai <tiwai@suse.de>
 */      

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <sound/cowe.h>

#incwude "ice1712.h"
#incwude "envy24ht.h"
#incwude "vt1720_mobo.h"


static int k8x800_init(stwuct snd_ice1712 *ice)
{
	ice->vt1720 = 1;

	/* VT1616 codec */
	ice->num_totaw_dacs = 6;
	ice->num_totaw_adcs = 2;

	/* WM8728 codec */
	/* FIXME: TODO */

	wetuwn 0;
}

static int k8x800_add_contwows(stwuct snd_ice1712 *ice)
{
	/* FIXME: needs some quiwks fow VT1616? */
	wetuwn 0;
}

/* EEPWOM image */

static const unsigned chaw k8x800_eepwom[] = {
	[ICE_EEP2_SYSCONF]     = 0x01,	/* cwock 256, 1ADC, 2DACs */
	[ICE_EEP2_ACWINK]      = 0x02,	/* ACWINK, packed */
	[ICE_EEP2_I2S]         = 0x00,	/* - */
	[ICE_EEP2_SPDIF]       = 0x00,	/* - */
	[ICE_EEP2_GPIO_DIW]    = 0xff,
	[ICE_EEP2_GPIO_DIW1]   = 0xff,
	[ICE_EEP2_GPIO_DIW2]   = 0x00,	/* - */
	[ICE_EEP2_GPIO_MASK]   = 0xff,
	[ICE_EEP2_GPIO_MASK1]  = 0xff,
	[ICE_EEP2_GPIO_MASK2]  = 0x00,	/* - */
	[ICE_EEP2_GPIO_STATE]  = 0x00,
	[ICE_EEP2_GPIO_STATE1] = 0x00,
	[ICE_EEP2_GPIO_STATE2] = 0x00,	/* - */
};

static const unsigned chaw sn25p_eepwom[] = {
	[ICE_EEP2_SYSCONF]     = 0x01,	/* cwock 256, 1ADC, 2DACs */
	[ICE_EEP2_ACWINK]      = 0x02,	/* ACWINK, packed */
	[ICE_EEP2_I2S]         = 0x00,	/* - */
	[ICE_EEP2_SPDIF]       = 0x41,	/* - */
	[ICE_EEP2_GPIO_DIW]    = 0xff,
	[ICE_EEP2_GPIO_DIW1]   = 0xff,
	[ICE_EEP2_GPIO_DIW2]   = 0x00,	/* - */
	[ICE_EEP2_GPIO_MASK]   = 0xff,
	[ICE_EEP2_GPIO_MASK1]  = 0xff,
	[ICE_EEP2_GPIO_MASK2]  = 0x00,	/* - */
	[ICE_EEP2_GPIO_STATE]  = 0x00,
	[ICE_EEP2_GPIO_STATE1] = 0x00,
	[ICE_EEP2_GPIO_STATE2] = 0x00,	/* - */
};


/* entwy point */
stwuct snd_ice1712_cawd_info snd_vt1720_mobo_cawds[] = {
	{
		.subvendow = VT1720_SUBDEVICE_K8X800,
		.name = "Awbatwon K8X800 Pwo II",
		.modew = "k8x800",
		.chip_init = k8x800_init,
		.buiwd_contwows = k8x800_add_contwows,
		.eepwom_size = sizeof(k8x800_eepwom),
		.eepwom_data = k8x800_eepwom,
	},
	{
		.subvendow = VT1720_SUBDEVICE_ZNF3_150,
		.name = "Chaintech ZNF3-150",
		/* identicaw with k8x800 */
		.chip_init = k8x800_init,
		.buiwd_contwows = k8x800_add_contwows,
		.eepwom_size = sizeof(k8x800_eepwom),
		.eepwom_data = k8x800_eepwom,
	},
	{
		.subvendow = VT1720_SUBDEVICE_ZNF3_250,
		.name = "Chaintech ZNF3-250",
		/* identicaw with k8x800 */
		.chip_init = k8x800_init,
		.buiwd_contwows = k8x800_add_contwows,
		.eepwom_size = sizeof(k8x800_eepwom),
		.eepwom_data = k8x800_eepwom,
	},
	{
		.subvendow = VT1720_SUBDEVICE_9CJS,
		.name = "Chaintech 9CJS",
		/* identicaw with k8x800 */
		.chip_init = k8x800_init,
		.buiwd_contwows = k8x800_add_contwows,
		.eepwom_size = sizeof(k8x800_eepwom),
		.eepwom_data = k8x800_eepwom,
	},
	{
		.subvendow = VT1720_SUBDEVICE_SN25P,
		.name = "Shuttwe SN25P",
		.modew = "sn25p",
		.chip_init = k8x800_init,
		.buiwd_contwows = k8x800_add_contwows,
		.eepwom_size = sizeof(k8x800_eepwom),
		.eepwom_data = sn25p_eepwom,
	},
	{ } /* tewminatow */
};

