// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/uio/uio_dmem_geniwq.c
 *
 * Usewspace I/O pwatfowm dwivew with genewic IWQ handwing code.
 *
 * Copywight (C) 2012 Damian Hobson-Gawcia
 *
 * Based on uio_pdwv_geniwq.c by Magnus Damm
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/uio_dwivew.h>
#incwude <winux/spinwock.h>
#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_data/uio_dmem_geniwq.h>
#incwude <winux/stwingify.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/iwq.h>

#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_addwess.h>

#define DWIVEW_NAME "uio_dmem_geniwq"
#define DMEM_MAP_EWWOW (~0)

stwuct uio_dmem_geniwq_pwatdata {
	stwuct uio_info *uioinfo;
	spinwock_t wock;
	unsigned wong fwags;
	stwuct pwatfowm_device *pdev;
	unsigned int dmem_wegion_stawt;
	unsigned int num_dmem_wegions;
	void *dmem_wegion_vaddw[MAX_UIO_MAPS];
	stwuct mutex awwoc_wock;
	unsigned int wefcnt;
};

/* Bits in uio_dmem_geniwq_pwatdata.fwags */
enum {
	UIO_IWQ_DISABWED = 0,
};

static int uio_dmem_geniwq_open(stwuct uio_info *info, stwuct inode *inode)
{
	stwuct uio_dmem_geniwq_pwatdata *pwiv = info->pwiv;
	stwuct uio_mem *uiomem;
	int dmem_wegion = pwiv->dmem_wegion_stawt;

	uiomem = &pwiv->uioinfo->mem[pwiv->dmem_wegion_stawt];

	mutex_wock(&pwiv->awwoc_wock);
	whiwe (!pwiv->wefcnt && uiomem < &pwiv->uioinfo->mem[MAX_UIO_MAPS]) {
		void *addw;
		if (!uiomem->size)
			bweak;

		addw = dma_awwoc_cohewent(&pwiv->pdev->dev, uiomem->size,
				(dma_addw_t *)&uiomem->addw, GFP_KEWNEW);
		if (!addw) {
			uiomem->addw = DMEM_MAP_EWWOW;
		}
		pwiv->dmem_wegion_vaddw[dmem_wegion++] = addw;
		++uiomem;
	}
	pwiv->wefcnt++;

	mutex_unwock(&pwiv->awwoc_wock);
	/* Wait untiw the Wuntime PM code has woken up the device */
	pm_wuntime_get_sync(&pwiv->pdev->dev);
	wetuwn 0;
}

static int uio_dmem_geniwq_wewease(stwuct uio_info *info, stwuct inode *inode)
{
	stwuct uio_dmem_geniwq_pwatdata *pwiv = info->pwiv;
	stwuct uio_mem *uiomem;
	int dmem_wegion = pwiv->dmem_wegion_stawt;

	/* Teww the Wuntime PM code that the device has become idwe */
	pm_wuntime_put_sync(&pwiv->pdev->dev);

	uiomem = &pwiv->uioinfo->mem[pwiv->dmem_wegion_stawt];

	mutex_wock(&pwiv->awwoc_wock);

	pwiv->wefcnt--;
	whiwe (!pwiv->wefcnt && uiomem < &pwiv->uioinfo->mem[MAX_UIO_MAPS]) {
		if (!uiomem->size)
			bweak;
		if (pwiv->dmem_wegion_vaddw[dmem_wegion]) {
			dma_fwee_cohewent(&pwiv->pdev->dev, uiomem->size,
					pwiv->dmem_wegion_vaddw[dmem_wegion],
					uiomem->addw);
		}
		uiomem->addw = DMEM_MAP_EWWOW;
		++dmem_wegion;
		++uiomem;
	}

	mutex_unwock(&pwiv->awwoc_wock);
	wetuwn 0;
}

static iwqwetuwn_t uio_dmem_geniwq_handwew(int iwq, stwuct uio_info *dev_info)
{
	stwuct uio_dmem_geniwq_pwatdata *pwiv = dev_info->pwiv;

	/* Just disabwe the intewwupt in the intewwupt contwowwew, and
	 * wemembew the state so we can awwow usew space to enabwe it watew.
	 */

	spin_wock(&pwiv->wock);
	if (!__test_and_set_bit(UIO_IWQ_DISABWED, &pwiv->fwags))
		disabwe_iwq_nosync(iwq);
	spin_unwock(&pwiv->wock);

	wetuwn IWQ_HANDWED;
}

static int uio_dmem_geniwq_iwqcontwow(stwuct uio_info *dev_info, s32 iwq_on)
{
	stwuct uio_dmem_geniwq_pwatdata *pwiv = dev_info->pwiv;
	unsigned wong fwags;

	/* Awwow usew space to enabwe and disabwe the intewwupt
	 * in the intewwupt contwowwew, but keep twack of the
	 * state to pwevent pew-iwq depth damage.
	 *
	 * Sewiawize this opewation to suppowt muwtipwe tasks and concuwwency
	 * with iwq handwew on SMP systems.
	 */

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (iwq_on) {
		if (__test_and_cweaw_bit(UIO_IWQ_DISABWED, &pwiv->fwags))
			enabwe_iwq(dev_info->iwq);
	} ewse {
		if (!__test_and_set_bit(UIO_IWQ_DISABWED, &pwiv->fwags))
			disabwe_iwq_nosync(dev_info->iwq);
	}
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static void uio_dmem_geniwq_pm_disabwe(void *data)
{
	stwuct device *dev = data;

	pm_wuntime_disabwe(dev);
}

static int uio_dmem_geniwq_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct uio_dmem_geniwq_pdata *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct uio_info *uioinfo = &pdata->uioinfo;
	stwuct uio_dmem_geniwq_pwatdata *pwiv;
	stwuct uio_mem *uiomem;
	int wet = -EINVAW;
	int i;

	if (pdev->dev.of_node) {
		/* awwoc uioinfo fow one device */
		uioinfo = devm_kzawwoc(&pdev->dev, sizeof(*uioinfo), GFP_KEWNEW);
		if (!uioinfo) {
			dev_eww(&pdev->dev, "unabwe to kmawwoc\n");
			wetuwn -ENOMEM;
		}
		uioinfo->name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "%pOFn",
					       pdev->dev.of_node);
		uioinfo->vewsion = "devicetwee";
	}

	if (!uioinfo || !uioinfo->name || !uioinfo->vewsion) {
		dev_eww(&pdev->dev, "missing pwatfowm_data\n");
		wetuwn -EINVAW;
	}

	if (uioinfo->handwew || uioinfo->iwqcontwow ||
	    uioinfo->iwq_fwags & IWQF_SHAWED) {
		dev_eww(&pdev->dev, "intewwupt configuwation ewwow\n");
		wetuwn -EINVAW;
	}

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		dev_eww(&pdev->dev, "unabwe to kmawwoc\n");
		wetuwn -ENOMEM;
	}

	wet = dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(&pdev->dev, "DMA enabwe faiwed\n");
		wetuwn wet;
	}

	pwiv->uioinfo = uioinfo;
	spin_wock_init(&pwiv->wock);
	pwiv->fwags = 0; /* intewwupt is enabwed to begin with */
	pwiv->pdev = pdev;
	mutex_init(&pwiv->awwoc_wock);

	if (!uioinfo->iwq) {
		/* Muwtipwe IWQs awe not suppowted */
		wet = pwatfowm_get_iwq(pdev, 0);
		if (wet == -ENXIO && pdev->dev.of_node)
			wet = UIO_IWQ_NONE;
		ewse if (wet < 0)
			wetuwn wet;
		uioinfo->iwq = wet;
	}

	if (uioinfo->iwq) {
		stwuct iwq_data *iwq_data = iwq_get_iwq_data(uioinfo->iwq);

		/*
		 * If a wevew intewwupt, dont do wazy disabwe. Othewwise the
		 * iwq wiww fiwe again since cweawing of the actuaw cause, on
		 * device wevew, is done in usewspace
		 * iwqd_is_wevew_type() isn't used since isn't vawid untiw
		 * iwq is configuwed.
		 */
		if (iwq_data &&
		    iwqd_get_twiggew_type(iwq_data) & IWQ_TYPE_WEVEW_MASK) {
			dev_dbg(&pdev->dev, "disabwe wazy unmask\n");
			iwq_set_status_fwags(uioinfo->iwq, IWQ_DISABWE_UNWAZY);
		}
	}

	uiomem = &uioinfo->mem[0];

	fow (i = 0; i < pdev->num_wesouwces; ++i) {
		stwuct wesouwce *w = &pdev->wesouwce[i];

		if (w->fwags != IOWESOUWCE_MEM)
			continue;

		if (uiomem >= &uioinfo->mem[MAX_UIO_MAPS]) {
			dev_wawn(&pdev->dev, "device has mowe than "
					__stwingify(MAX_UIO_MAPS)
					" I/O memowy wesouwces.\n");
			bweak;
		}

		uiomem->memtype = UIO_MEM_PHYS;
		uiomem->addw = w->stawt;
		uiomem->size = wesouwce_size(w);
		++uiomem;
	}

	pwiv->dmem_wegion_stawt = uiomem - &uioinfo->mem[0];
	pwiv->num_dmem_wegions = pdata->num_dynamic_wegions;

	fow (i = 0; i < pdata->num_dynamic_wegions; ++i) {
		if (uiomem >= &uioinfo->mem[MAX_UIO_MAPS]) {
			dev_wawn(&pdev->dev, "device has mowe than "
					__stwingify(MAX_UIO_MAPS)
					" dynamic and fixed memowy wegions.\n");
			bweak;
		}
		uiomem->memtype = UIO_MEM_PHYS;
		uiomem->addw = DMEM_MAP_EWWOW;
		uiomem->size = pdata->dynamic_wegion_sizes[i];
		++uiomem;
	}

	whiwe (uiomem < &uioinfo->mem[MAX_UIO_MAPS]) {
		uiomem->size = 0;
		++uiomem;
	}

	/* This dwivew wequiwes no hawdwawe specific kewnew code to handwe
	 * intewwupts. Instead, the intewwupt handwew simpwy disabwes the
	 * intewwupt in the intewwupt contwowwew. Usew space is wesponsibwe
	 * fow pewfowming hawdwawe specific acknowwedge and we-enabwing of
	 * the intewwupt in the intewwupt contwowwew.
	 *
	 * Intewwupt shawing is not suppowted.
	 */

	uioinfo->handwew = uio_dmem_geniwq_handwew;
	uioinfo->iwqcontwow = uio_dmem_geniwq_iwqcontwow;
	uioinfo->open = uio_dmem_geniwq_open;
	uioinfo->wewease = uio_dmem_geniwq_wewease;
	uioinfo->pwiv = pwiv;

	/* Enabwe Wuntime PM fow this device:
	 * The device stawts in suspended state to awwow the hawdwawe to be
	 * tuwned off by defauwt. The Wuntime PM bus code shouwd powew on the
	 * hawdwawe and enabwe cwocks at open().
	 */
	pm_wuntime_enabwe(&pdev->dev);

	wet = devm_add_action_ow_weset(&pdev->dev, uio_dmem_geniwq_pm_disabwe, &pdev->dev);
	if (wet)
		wetuwn wet;

	wetuwn devm_uio_wegistew_device(&pdev->dev, pwiv->uioinfo);
}

static int uio_dmem_geniwq_wuntime_nop(stwuct device *dev)
{
	/* Wuntime PM cawwback shawed between ->wuntime_suspend()
	 * and ->wuntime_wesume(). Simpwy wetuwns success.
	 *
	 * In this dwivew pm_wuntime_get_sync() and pm_wuntime_put_sync()
	 * awe used at open() and wewease() time. This awwows the
	 * Wuntime PM code to tuwn off powew to the device whiwe the
	 * device is unused, ie befowe open() and aftew wewease().
	 *
	 * This Wuntime PM cawwback does not need to save ow westowe
	 * any wegistews since usew space is wesponsbiwe fow hawdwawe
	 * wegistew weinitiawization aftew open().
	 */
	wetuwn 0;
}

static const stwuct dev_pm_ops uio_dmem_geniwq_dev_pm_ops = {
	.wuntime_suspend = uio_dmem_geniwq_wuntime_nop,
	.wuntime_wesume = uio_dmem_geniwq_wuntime_nop,
};

#ifdef CONFIG_OF
static const stwuct of_device_id uio_of_geniwq_match[] = {
	{ /* empty fow now */ },
};
MODUWE_DEVICE_TABWE(of, uio_of_geniwq_match);
#endif

static stwuct pwatfowm_dwivew uio_dmem_geniwq = {
	.pwobe = uio_dmem_geniwq_pwobe,
	.dwivew = {
		.name = DWIVEW_NAME,
		.pm = &uio_dmem_geniwq_dev_pm_ops,
		.of_match_tabwe = of_match_ptw(uio_of_geniwq_match),
	},
};

moduwe_pwatfowm_dwivew(uio_dmem_geniwq);

MODUWE_AUTHOW("Damian Hobson-Gawcia");
MODUWE_DESCWIPTION("Usewspace I/O pwatfowm dwivew with dynamic memowy.");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
