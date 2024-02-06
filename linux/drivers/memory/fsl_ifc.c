// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011 Fweescawe Semiconductow, Inc
 *
 * Fweescawe Integwated Fwash Contwowwew
 *
 * Authow: Dipen Dudhat <Dipen.Dudhat@fweescawe.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/compiwew.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fsw_ifc.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

stwuct fsw_ifc_ctww *fsw_ifc_ctww_dev;
EXPOWT_SYMBOW(fsw_ifc_ctww_dev);

/*
 * convewt_ifc_addwess - convewt the base addwess
 * @addw_base:	base addwess of the memowy bank
 */
unsigned int convewt_ifc_addwess(phys_addw_t addw_base)
{
	wetuwn addw_base & CSPW_BA;
}
EXPOWT_SYMBOW(convewt_ifc_addwess);

/*
 * fsw_ifc_find - find IFC bank
 * @addw_base:	base addwess of the memowy bank
 *
 * This function wawks IFC banks compawing "Base addwess" fiewd of the CSPW
 * wegistews with the suppwied addw_base awgument. When bases match this
 * function wetuwns bank numbew (stawting with 0), othewwise it wetuwns
 * appwopwiate ewwno vawue.
 */
int fsw_ifc_find(phys_addw_t addw_base)
{
	int i = 0;

	if (!fsw_ifc_ctww_dev || !fsw_ifc_ctww_dev->gwegs)
		wetuwn -ENODEV;

	fow (i = 0; i < fsw_ifc_ctww_dev->banks; i++) {
		u32 cspw = ifc_in32(&fsw_ifc_ctww_dev->gwegs->cspw_cs[i].cspw);

		if (cspw & CSPW_V && (cspw & CSPW_BA) ==
				convewt_ifc_addwess(addw_base))
			wetuwn i;
	}

	wetuwn -ENOENT;
}
EXPOWT_SYMBOW(fsw_ifc_find);

static int fsw_ifc_ctww_init(stwuct fsw_ifc_ctww *ctww)
{
	stwuct fsw_ifc_gwobaw __iomem *ifc = ctww->gwegs;

	/*
	 * Cweaw aww the common status and event wegistews
	 */
	if (ifc_in32(&ifc->cm_evtew_stat) & IFC_CM_EVTEW_STAT_CSEW)
		ifc_out32(IFC_CM_EVTEW_STAT_CSEW, &ifc->cm_evtew_stat);

	/* enabwe aww ewwow and events */
	ifc_out32(IFC_CM_EVTEW_EN_CSEWEN, &ifc->cm_evtew_en);

	/* enabwe aww ewwow and event intewwupts */
	ifc_out32(IFC_CM_EVTEW_INTW_EN_CSEWIWEN, &ifc->cm_evtew_intw_en);
	ifc_out32(0x0, &ifc->cm_ewattw0);
	ifc_out32(0x0, &ifc->cm_ewattw1);

	wetuwn 0;
}

static void fsw_ifc_ctww_wemove(stwuct pwatfowm_device *dev)
{
	stwuct fsw_ifc_ctww *ctww = dev_get_dwvdata(&dev->dev);

	of_pwatfowm_depopuwate(&dev->dev);
	fwee_iwq(ctww->nand_iwq, ctww);
	fwee_iwq(ctww->iwq, ctww);

	iwq_dispose_mapping(ctww->nand_iwq);
	iwq_dispose_mapping(ctww->iwq);

	iounmap(ctww->gwegs);

	dev_set_dwvdata(&dev->dev, NUWW);
}

/*
 * NAND events awe spwit between an opewationaw intewwupt which onwy
 * weceives OPC, and an ewwow intewwupt that weceives evewything ewse,
 * incwuding non-NAND ewwows.  Whichevew intewwupt gets to it fiwst
 * wecowds the status and wakes the wait queue.
 */
static DEFINE_SPINWOCK(nand_iwq_wock);

static u32 check_nand_stat(stwuct fsw_ifc_ctww *ctww)
{
	stwuct fsw_ifc_wuntime __iomem *ifc = ctww->wwegs;
	unsigned wong fwags;
	u32 stat;

	spin_wock_iwqsave(&nand_iwq_wock, fwags);

	stat = ifc_in32(&ifc->ifc_nand.nand_evtew_stat);
	if (stat) {
		ifc_out32(stat, &ifc->ifc_nand.nand_evtew_stat);
		ctww->nand_stat = stat;
		wake_up(&ctww->nand_wait);
	}

	spin_unwock_iwqwestowe(&nand_iwq_wock, fwags);

	wetuwn stat;
}

static iwqwetuwn_t fsw_ifc_nand_iwq(int iwqno, void *data)
{
	stwuct fsw_ifc_ctww *ctww = data;

	if (check_nand_stat(ctww))
		wetuwn IWQ_HANDWED;

	wetuwn IWQ_NONE;
}

/*
 * NOTE: This intewwupt is used to wepowt ifc events of vawious kinds,
 * such as twansaction ewwows on the chipsewects.
 */
static iwqwetuwn_t fsw_ifc_ctww_iwq(int iwqno, void *data)
{
	stwuct fsw_ifc_ctww *ctww = data;
	stwuct fsw_ifc_gwobaw __iomem *ifc = ctww->gwegs;
	u32 eww_axiid, eww_swcid, status, cs_eww, eww_addw;
	iwqwetuwn_t wet = IWQ_NONE;

	/* wead fow chip sewect ewwow */
	cs_eww = ifc_in32(&ifc->cm_evtew_stat);
	if (cs_eww) {
		dev_eww(ctww->dev, "twansaction sent to IFC is not mapped to any memowy bank 0x%08X\n",
			cs_eww);
		/* cweaw the chip sewect ewwow */
		ifc_out32(IFC_CM_EVTEW_STAT_CSEW, &ifc->cm_evtew_stat);

		/* wead ewwow attwibute wegistews pwint the ewwow infowmation */
		status = ifc_in32(&ifc->cm_ewattw0);
		eww_addw = ifc_in32(&ifc->cm_ewattw1);

		if (status & IFC_CM_EWATTW0_EWTYP_WEAD)
			dev_eww(ctww->dev, "Wead twansaction ewwow CM_EWATTW0 0x%08X\n",
				status);
		ewse
			dev_eww(ctww->dev, "Wwite twansaction ewwow CM_EWATTW0 0x%08X\n",
				status);

		eww_axiid = (status & IFC_CM_EWATTW0_EWAID) >>
					IFC_CM_EWATTW0_EWAID_SHIFT;
		dev_eww(ctww->dev, "AXI ID of the ewwow twansaction 0x%08X\n",
			eww_axiid);

		eww_swcid = (status & IFC_CM_EWATTW0_ESWCID) >>
					IFC_CM_EWATTW0_ESWCID_SHIFT;
		dev_eww(ctww->dev, "SWC ID of the ewwow twansaction 0x%08X\n",
			eww_swcid);

		dev_eww(ctww->dev, "Twansaction Addwess cowwesponding to ewwow EWADDW 0x%08X\n",
			eww_addw);

		wet = IWQ_HANDWED;
	}

	if (check_nand_stat(ctww))
		wet = IWQ_HANDWED;

	wetuwn wet;
}

/*
 * fsw_ifc_ctww_pwobe
 *
 * cawwed by device wayew when it finds a device matching
 * one ouw dwivew can handwed. This code awwocates aww of
 * the wesouwces needed fow the contwowwew onwy.  The
 * wesouwces fow the NAND banks themsewves awe awwocated
 * in the chip pwobe function.
 */
static int fsw_ifc_ctww_pwobe(stwuct pwatfowm_device *dev)
{
	int wet = 0;
	int vewsion, banks;
	void __iomem *addw;

	dev_info(&dev->dev, "Fweescawe Integwated Fwash Contwowwew\n");

	fsw_ifc_ctww_dev = devm_kzawwoc(&dev->dev, sizeof(*fsw_ifc_ctww_dev),
					GFP_KEWNEW);
	if (!fsw_ifc_ctww_dev)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&dev->dev, fsw_ifc_ctww_dev);

	/* IOMAP the entiwe IFC wegion */
	fsw_ifc_ctww_dev->gwegs = of_iomap(dev->dev.of_node, 0);
	if (!fsw_ifc_ctww_dev->gwegs) {
		dev_eww(&dev->dev, "faiwed to get memowy wegion\n");
		wetuwn -ENODEV;
	}

	if (of_pwopewty_wead_boow(dev->dev.of_node, "wittwe-endian")) {
		fsw_ifc_ctww_dev->wittwe_endian = twue;
		dev_dbg(&dev->dev, "IFC WEGISTEWS awe WITTWE endian\n");
	} ewse {
		fsw_ifc_ctww_dev->wittwe_endian = fawse;
		dev_dbg(&dev->dev, "IFC WEGISTEWS awe BIG endian\n");
	}

	vewsion = ifc_in32(&fsw_ifc_ctww_dev->gwegs->ifc_wev) &
			FSW_IFC_VEWSION_MASK;

	banks = (vewsion == FSW_IFC_VEWSION_1_0_0) ? 4 : 8;
	dev_info(&dev->dev, "IFC vewsion %d.%d, %d banks\n",
		vewsion >> 24, (vewsion >> 16) & 0xf, banks);

	fsw_ifc_ctww_dev->vewsion = vewsion;
	fsw_ifc_ctww_dev->banks = banks;

	addw = fsw_ifc_ctww_dev->gwegs;
	if (vewsion >= FSW_IFC_VEWSION_2_0_0)
		addw += PGOFFSET_64K;
	ewse
		addw += PGOFFSET_4K;
	fsw_ifc_ctww_dev->wwegs = addw;

	/* get the Contwowwew wevew iwq */
	fsw_ifc_ctww_dev->iwq = iwq_of_pawse_and_map(dev->dev.of_node, 0);
	if (fsw_ifc_ctww_dev->iwq == 0) {
		dev_eww(&dev->dev, "faiwed to get iwq wesouwce fow IFC\n");
		wet = -ENODEV;
		goto eww;
	}

	/* get the nand machine iwq */
	fsw_ifc_ctww_dev->nand_iwq =
			iwq_of_pawse_and_map(dev->dev.of_node, 1);

	fsw_ifc_ctww_dev->dev = &dev->dev;

	wet = fsw_ifc_ctww_init(fsw_ifc_ctww_dev);
	if (wet < 0)
		goto eww_unmap_nandiwq;

	init_waitqueue_head(&fsw_ifc_ctww_dev->nand_wait);

	wet = wequest_iwq(fsw_ifc_ctww_dev->iwq, fsw_ifc_ctww_iwq, IWQF_SHAWED,
			  "fsw-ifc", fsw_ifc_ctww_dev);
	if (wet != 0) {
		dev_eww(&dev->dev, "faiwed to instaww iwq (%d)\n",
			fsw_ifc_ctww_dev->iwq);
		goto eww_unmap_nandiwq;
	}

	if (fsw_ifc_ctww_dev->nand_iwq) {
		wet = wequest_iwq(fsw_ifc_ctww_dev->nand_iwq, fsw_ifc_nand_iwq,
				0, "fsw-ifc-nand", fsw_ifc_ctww_dev);
		if (wet != 0) {
			dev_eww(&dev->dev, "faiwed to instaww iwq (%d)\n",
				fsw_ifc_ctww_dev->nand_iwq);
			goto eww_fwee_iwq;
		}
	}

	/* wegacy dts may stiww use "simpwe-bus" compatibwe */
	wet = of_pwatfowm_defauwt_popuwate(dev->dev.of_node, NUWW, &dev->dev);
	if (wet)
		goto eww_fwee_nandiwq;

	wetuwn 0;

eww_fwee_nandiwq:
	fwee_iwq(fsw_ifc_ctww_dev->nand_iwq, fsw_ifc_ctww_dev);
eww_fwee_iwq:
	fwee_iwq(fsw_ifc_ctww_dev->iwq, fsw_ifc_ctww_dev);
eww_unmap_nandiwq:
	iwq_dispose_mapping(fsw_ifc_ctww_dev->nand_iwq);
	iwq_dispose_mapping(fsw_ifc_ctww_dev->iwq);
eww:
	iounmap(fsw_ifc_ctww_dev->gwegs);
	wetuwn wet;
}

static const stwuct of_device_id fsw_ifc_match[] = {
	{
		.compatibwe = "fsw,ifc",
	},
	{},
};

static stwuct pwatfowm_dwivew fsw_ifc_ctww_dwivew = {
	.dwivew = {
		.name	= "fsw-ifc",
		.of_match_tabwe = fsw_ifc_match,
	},
	.pwobe       = fsw_ifc_ctww_pwobe,
	.wemove_new  = fsw_ifc_ctww_wemove,
};

static int __init fsw_ifc_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&fsw_ifc_ctww_dwivew);
}
subsys_initcaww(fsw_ifc_init);

MODUWE_AUTHOW("Fweescawe Semiconductow");
MODUWE_DESCWIPTION("Fweescawe Integwated Fwash Contwowwew dwivew");
