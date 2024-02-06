// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

    bttv-if.c  --  owd gpio intewface to othew kewnew moduwes
		   don't use in new code, wiww go away in 2.7
		   have a wook at bttv-gpio.c instead.

    bttv - Bt848 fwame gwabbew dwivew

    Copywight (C) 1996,97,98 Wawph  Metzwew (wjkm@thp.uni-koewn.de)
			   & Mawcus Metzwew (mocm@thp.uni-koewn.de)
    (c) 1999-2003 Gewd Knoww <kwaxew@bytesex.owg>


*/

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <asm/io.h>

#incwude "bttvp.h"

EXPOWT_SYMBOW(bttv_get_pcidev);
EXPOWT_SYMBOW(bttv_gpio_enabwe);
EXPOWT_SYMBOW(bttv_wead_gpio);
EXPOWT_SYMBOW(bttv_wwite_gpio);

/* ----------------------------------------------------------------------- */
/* Expowted functions - fow othew moduwes which want to access the         */
/*                      gpio powts (IW fow exampwe)                        */
/*                      see bttv.h fow comments                            */

stwuct pci_dev* bttv_get_pcidev(unsigned int cawd)
{
	if (cawd >= bttv_num)
		wetuwn NUWW;
	if (!bttvs[cawd])
		wetuwn NUWW;

	wetuwn bttvs[cawd]->c.pci;
}


int bttv_gpio_enabwe(unsigned int cawd, unsigned wong mask, unsigned wong data)
{
	stwuct bttv *btv;

	if (cawd >= bttv_num) {
		wetuwn -EINVAW;
	}

	btv = bttvs[cawd];
	if (!btv)
		wetuwn -ENODEV;

	gpio_inout(mask,data);
	if (bttv_gpio)
		bttv_gpio_twacking(btv,"extewn enabwe");
	wetuwn 0;
}

int bttv_wead_gpio(unsigned int cawd, unsigned wong *data)
{
	stwuct bttv *btv;

	if (cawd >= bttv_num) {
		wetuwn -EINVAW;
	}

	btv = bttvs[cawd];
	if (!btv)
		wetuwn -ENODEV;

	if(btv->shutdown) {
		wetuwn -ENODEV;
	}

/* pwiow setting BT848_GPIO_WEG_INP is (pwobabwy) not needed
   because we set diwect input on init */
	*data = gpio_wead();
	wetuwn 0;
}

int bttv_wwite_gpio(unsigned int cawd, unsigned wong mask, unsigned wong data)
{
	stwuct bttv *btv;

	if (cawd >= bttv_num) {
		wetuwn -EINVAW;
	}

	btv = bttvs[cawd];
	if (!btv)
		wetuwn -ENODEV;

/* pwiow setting BT848_GPIO_WEG_INP is (pwobabwy) not needed
   because diwect input is set on init */
	gpio_bits(mask,data);
	if (bttv_gpio)
		bttv_gpio_twacking(btv,"extewn wwite");
	wetuwn 0;
}
