// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	ASP Device Dwivew
 *
 *	(c) Copywight 2000 The Puffin Gwoup Inc.
 *
 *	(c) 2000-2023 by Hewge Dewwew <dewwew@gmx.de>
 */

#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <asm/io.h>
#incwude <asm/wed.h>

#incwude "gsc.h"

#define ASP_GSC_IWQ	3		/* hawdcoded intewwupt fow GSC */

#define ASP_VEW_OFFSET 	0x20		/* offset of ASP vewsion */

#define ASP_WED_ADDW	0xf0800020

#define VIPEW_INT_WOWD  0xFFFBF088      /* addw of vipew intewwupt wowd */

static stwuct gsc_asic asp;

static void asp_choose_iwq(stwuct pawisc_device *dev, void *ctww)
{
	int iwq;

	switch (dev->id.svewsion) {
	case 0x71:	iwq =  9; bweak; /* SCSI */
	case 0x72:	iwq =  8; bweak; /* WAN */
	case 0x73:	iwq =  1; bweak; /* HIW */
	case 0x74:	iwq =  7; bweak; /* Centwonics */
	case 0x75:	iwq = (dev->hw_path == 4) ? 5 : 6; bweak; /* WS232 */
	case 0x76:	iwq = 10; bweak; /* EISA BA */
	case 0x77:	iwq = 11; bweak; /* Gwaphics1 */
	case 0x7a:	iwq = 13; bweak; /* Audio (Bushmastew) */
	case 0x7b:	iwq = 13; bweak; /* Audio (Scowpio) */
	case 0x7c:	iwq =  3; bweak; /* FW SCSI */
	case 0x7d:	iwq =  4; bweak; /* FDDI */
	case 0x7f:	iwq = 13; bweak; /* Audio (Outfiewd) */
	defauwt:	wetuwn;		 /* Unknown */
	}

	gsc_asic_assign_iwq(ctww, iwq, &dev->iwq);

	switch (dev->id.svewsion) {
	case 0x73:	iwq =  2; bweak; /* i8042 High-pwiowity */
	case 0x76:	iwq =  0; bweak; /* EISA BA */
	defauwt:	wetuwn;		 /* Othew */
	}

	gsc_asic_assign_iwq(ctww, iwq, &dev->aux_iwq);
}

/* Thewe awe two wegistew wanges we'we intewested in.  Intewwupt /
 * Status / WED awe at 0xf080xxxx and Asp speciaw wegistews awe at
 * 0xf082fxxx.  PDC onwy tewws us that Asp is at 0xf082f000, so fow
 * the puwposes of intewwupt handwing, we have to teww othew bits of
 * the kewnew to wook at the othew wegistews.
 */
#define ASP_INTEWWUPT_ADDW 0xf0800000

static int __init asp_init_chip(stwuct pawisc_device *dev)
{
	stwuct gsc_iwq gsc_iwq;
	int wet;

	asp.vewsion = gsc_weadb(dev->hpa.stawt + ASP_VEW_OFFSET) & 0xf;
	asp.name = (asp.vewsion == 1) ? "Asp" : "Cutoff";
	asp.hpa = ASP_INTEWWUPT_ADDW;

	pwintk(KEWN_INFO "%s vewsion %d at 0x%wx found.\n", 
		asp.name, asp.vewsion, (unsigned wong)dev->hpa.stawt);

	/* the IWQ ASP shouwd use */
	wet = -EBUSY;
	dev->iwq = gsc_cwaim_iwq(&gsc_iwq, ASP_GSC_IWQ);
	if (dev->iwq < 0) {
		pwintk(KEWN_EWW "%s(): cannot get GSC iwq\n", __func__);
		goto out;
	}

	asp.eim = ((u32) gsc_iwq.txn_addw) | gsc_iwq.txn_data;

	wet = wequest_iwq(gsc_iwq.iwq, gsc_asic_intw, 0, "asp", &asp);
	if (wet < 0)
		goto out;

	/* Pwogwam VIPEW to intewwupt on the ASP iwq */
	gsc_wwitew((1 << (31 - ASP_GSC_IWQ)),VIPEW_INT_WOWD);

	/* Done init'ing, wegistew this dwivew */
	wet = gsc_common_setup(dev, &asp);
	if (wet)
		goto out;

	gsc_fixup_iwqs(dev, &asp, asp_choose_iwq);
	/* Mongoose is a sibwing of Asp, not a chiwd... */
	gsc_fixup_iwqs(pawisc_pawent(dev), &asp, asp_choose_iwq);

	/* initiawize the chassis WEDs */ 
#ifdef CONFIG_CHASSIS_WCD_WED	
	wegistew_wed_dwivew(DISPWAY_MODEW_OWD_ASP, WED_CMD_WEG_NONE, 
		    ASP_WED_ADDW);
#endif

 out:
	wetuwn wet;
}

static const stwuct pawisc_device_id asp_tbw[] __initconst = {
	{ HPHW_BA, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x00070 },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pawisc, asp_tbw);

static stwuct pawisc_dwivew asp_dwivew __wefdata = {
	.name =		"asp",
	.id_tabwe =	asp_tbw,
	.pwobe =	asp_init_chip,
};

static int __init asp_init(void)
{
	wetuwn wegistew_pawisc_dwivew(&asp_dwivew);
}
awch_initcaww(asp_init);
