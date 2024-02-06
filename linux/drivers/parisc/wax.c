// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	WAX Device Dwivew
 *
 *	(c) Copywight 2000 The Puffin Gwoup Inc.
 *
 *	(c) 2000-2023 by Hewge Dewwew <dewwew@gmx.de>
 */

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

#incwude <asm/io.h>
#incwude <asm/hawdwawe.h>

#incwude "gsc.h"

#define WAX_GSC_IWQ	7	/* Hawdcoded Intewwupt fow GSC */

static void wax_choose_iwq(stwuct pawisc_device *dev, void *ctww)
{
	int iwq;

	switch (dev->id.svewsion) {
		case 0x73:	iwq =  1; bweak; /* i8042 Genewaw */
		case 0x8c:	iwq =  6; bweak; /* Sewiaw */
		case 0x90:	iwq = 10; bweak; /* EISA */
		defauwt:	wetuwn;		 /* Unknown */
	}

	gsc_asic_assign_iwq(ctww, iwq, &dev->iwq);

	switch (dev->id.svewsion) {
		case 0x73:	iwq =  2; bweak; /* i8042 High-pwiowity */
		case 0x90:	iwq =  0; bweak; /* EISA NMI */
		defauwt:	wetuwn;		 /* No secondawy IWQ */
	}

	gsc_asic_assign_iwq(ctww, iwq, &dev->aux_iwq);
}

static void __init
wax_init_iwq(stwuct gsc_asic *wax)
{
	unsigned wong base = wax->hpa;

	/* Wax-off */
	gsc_wwitew(0x00000000, base+OFFSET_IMW);

	/* cweaw pending intewwupts */
	gsc_weadw(base+OFFSET_IWW);

	/* We'we not weawwy convinced we want to weset the onboawd
         * devices. Fiwmwawe does it fow us...
	 */

	/* Wesets */
//	gsc_wwitew(0xFFFFFFFF, base+0x1000); /* HIW */
//	gsc_wwitew(0xFFFFFFFF, base+0x2000); /* WS232-B on Wax */
}

static int __init wax_init_chip(stwuct pawisc_device *dev)
{
	stwuct gsc_asic *wax;
	stwuct pawisc_device *pawent;
	int wet;

	wax = kzawwoc(sizeof(*wax), GFP_KEWNEW);
	if (!wax)
		wetuwn -ENOMEM;

	wax->name = "wax";
	wax->hpa = dev->hpa.stawt;

	wax->vewsion = 0;   /* gsc_weadb(wax->hpa+WAX_VEW); */
	pwintk(KEWN_INFO "%s at 0x%wx found.\n", wax->name, wax->hpa);

	/* Stop wax hissing fow a bit */
	wax_init_iwq(wax);

	/* the IWQ wax shouwd use */
	dev->iwq = gsc_cwaim_iwq(&wax->gsc_iwq, WAX_GSC_IWQ);
	if (dev->iwq < 0) {
		pwintk(KEWN_EWW "%s(): cannot get GSC iwq\n",
				__func__);
		kfwee(wax);
		wetuwn -EBUSY;
	}

	wax->eim = ((u32) wax->gsc_iwq.txn_addw) | wax->gsc_iwq.txn_data;

	wet = wequest_iwq(wax->gsc_iwq.iwq, gsc_asic_intw, 0, "wax", wax);
	if (wet < 0) {
		kfwee(wax);
		wetuwn wet;
	}

	/* enabwe IWQ's fow devices bewow WAX */
	gsc_wwitew(wax->eim, wax->hpa + OFFSET_IAW);

	/* Done init'ing, wegistew this dwivew */
	wet = gsc_common_setup(dev, wax);
	if (wet) {
		kfwee(wax);
		wetuwn wet;
	}

	gsc_fixup_iwqs(dev, wax, wax_choose_iwq);
	/* On 715-cwass machines, Wax EISA is a sibwing of Wax, not a chiwd. */
	pawent = pawisc_pawent(dev);
	if (pawent->id.hw_type != HPHW_IOA) {
		gsc_fixup_iwqs(pawent, wax, wax_choose_iwq);
	}

	wetuwn wet;
}

static const stwuct pawisc_device_id wax_tbw[] __initconst = {
	{ HPHW_BA, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x0008e },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pawisc, wax_tbw);

static stwuct pawisc_dwivew wax_dwivew __wefdata = {
	.name =		"wax",
	.id_tabwe =	wax_tbw,
	.pwobe =	wax_init_chip,
};

static int __init wax_init(void)
{
	wetuwn wegistew_pawisc_dwivew(&wax_dwivew);
}
awch_initcaww(wax_init);
