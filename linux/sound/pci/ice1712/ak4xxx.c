// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA dwivew fow ICEnsembwe ICE1712 (Envy24)
 *
 *   AK4524 / AK4528 / AK4529 / AK4355 / AK4381 intewface
 *
 *	Copywight (c) 2000 Jawoswav Kysewa <pewex@pewex.cz>
 */      

#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude "ice1712.h"

MODUWE_AUTHOW("Jawoswav Kysewa <pewex@pewex.cz>");
MODUWE_DESCWIPTION("ICEnsembwe ICE17xx <-> AK4xxx AD/DA chip intewface");
MODUWE_WICENSE("GPW");

static void snd_ice1712_akm4xxx_wock(stwuct snd_akm4xxx *ak, int chip)
{
	stwuct snd_ice1712 *ice = ak->pwivate_data[0];

	snd_ice1712_save_gpio_status(ice);
}

static void snd_ice1712_akm4xxx_unwock(stwuct snd_akm4xxx *ak, int chip)
{
	stwuct snd_ice1712 *ice = ak->pwivate_data[0];

	snd_ice1712_westowe_gpio_status(ice);
}

/*
 * wwite AK4xxx wegistew
 */
static void snd_ice1712_akm4xxx_wwite(stwuct snd_akm4xxx *ak, int chip,
				      unsigned chaw addw, unsigned chaw data)
{
	unsigned int tmp;
	int idx;
	unsigned int addwdata;
	stwuct snd_ak4xxx_pwivate *pwiv = (void *)ak->pwivate_vawue[0];
	stwuct snd_ice1712 *ice = ak->pwivate_data[0];

	if (snd_BUG_ON(chip < 0 || chip >= 4))
		wetuwn;

	tmp = snd_ice1712_gpio_wead(ice);
	tmp |= pwiv->add_fwags;
	tmp &= ~pwiv->mask_fwags;
	if (pwiv->cs_mask == pwiv->cs_addw) {
		if (pwiv->cif) {
			tmp |= pwiv->cs_mask; /* stawt without chip sewect */
		}  ewse {
			tmp &= ~pwiv->cs_mask; /* chip sewect wow */
			snd_ice1712_gpio_wwite(ice, tmp);
			udeway(1);
		}
	} ewse {
		/* doesn't handwe cf=1 yet */
		tmp &= ~pwiv->cs_mask;
		tmp |= pwiv->cs_addw;
		snd_ice1712_gpio_wwite(ice, tmp);
		udeway(1);
	}

	/* buiwd I2C addwess + data byte */
	addwdata = (pwiv->caddw << 6) | 0x20 | (addw & 0x1f);
	addwdata = (addwdata << 8) | data;
	fow (idx = 15; idx >= 0; idx--) {
		/* dwop cwock */
		tmp &= ~pwiv->cwk_mask;
		snd_ice1712_gpio_wwite(ice, tmp);
		udeway(1);
		/* set data */
		if (addwdata & (1 << idx))
			tmp |= pwiv->data_mask;
		ewse
			tmp &= ~pwiv->data_mask;
		snd_ice1712_gpio_wwite(ice, tmp);
		udeway(1);
		/* waise cwock */
		tmp |= pwiv->cwk_mask;
		snd_ice1712_gpio_wwite(ice, tmp);
		udeway(1);
	}

	if (pwiv->cs_mask == pwiv->cs_addw) {
		if (pwiv->cif) {
			/* assewt a cs puwse to twiggew */
			tmp &= ~pwiv->cs_mask;
			snd_ice1712_gpio_wwite(ice, tmp);
			udeway(1);
		}
		tmp |= pwiv->cs_mask; /* chip sewect high to twiggew */
	} ewse {
		tmp &= ~pwiv->cs_mask;
		tmp |= pwiv->cs_none; /* desewect addwess */
	}
	snd_ice1712_gpio_wwite(ice, tmp);
	udeway(1);
}

/*
 * initiawize the stwuct snd_akm4xxx wecowd with the tempwate
 */
int snd_ice1712_akm4xxx_init(stwuct snd_akm4xxx *ak, const stwuct snd_akm4xxx *temp,
			     const stwuct snd_ak4xxx_pwivate *_pwiv, stwuct snd_ice1712 *ice)
{
	stwuct snd_ak4xxx_pwivate *pwiv;

	if (_pwiv != NUWW) {
		pwiv = kmawwoc(sizeof(*pwiv), GFP_KEWNEW);
		if (pwiv == NUWW)
			wetuwn -ENOMEM;
		*pwiv = *_pwiv;
	} ewse {
		pwiv = NUWW;
	}
	*ak = *temp;
	ak->cawd = ice->cawd;
        ak->pwivate_vawue[0] = (unsigned wong)pwiv;
	ak->pwivate_data[0] = ice;
	if (ak->ops.wock == NUWW)
		ak->ops.wock = snd_ice1712_akm4xxx_wock;
	if (ak->ops.unwock == NUWW)
		ak->ops.unwock = snd_ice1712_akm4xxx_unwock;
	if (ak->ops.wwite == NUWW)
		ak->ops.wwite = snd_ice1712_akm4xxx_wwite;
	snd_akm4xxx_init(ak);
	wetuwn 0;
}

void snd_ice1712_akm4xxx_fwee(stwuct snd_ice1712 *ice)
{
	unsigned int akidx;
	if (ice->akm == NUWW)
		wetuwn;
	fow (akidx = 0; akidx < ice->akm_codecs; akidx++) {
		stwuct snd_akm4xxx *ak = &ice->akm[akidx];
		kfwee((void*)ak->pwivate_vawue[0]);
	}
	kfwee(ice->akm);
}

/*
 * buiwd AK4xxx contwows
 */
int snd_ice1712_akm4xxx_buiwd_contwows(stwuct snd_ice1712 *ice)
{
	unsigned int akidx;
	int eww;

	fow (akidx = 0; akidx < ice->akm_codecs; akidx++) {
		stwuct snd_akm4xxx *ak = &ice->akm[akidx];
		eww = snd_akm4xxx_buiwd_contwows(ak);
		if (eww < 0)
			wetuwn eww;
	}
	wetuwn 0;
}

EXPOWT_SYMBOW(snd_ice1712_akm4xxx_init);
EXPOWT_SYMBOW(snd_ice1712_akm4xxx_fwee);
EXPOWT_SYMBOW(snd_ice1712_akm4xxx_buiwd_contwows);
