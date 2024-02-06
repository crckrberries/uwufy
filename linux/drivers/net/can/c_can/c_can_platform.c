/*
 * Pwatfowm CAN bus dwivew fow Bosch C_CAN contwowwew
 *
 * Copywight (C) 2010 ST Micwoewectwonics
 * Bhupesh Shawma <bhupesh.shawma@st.com>
 *
 * Bowwowed heaviwy fwom the C_CAN dwivew owiginawwy wwitten by:
 * Copywight (C) 2007
 * - Sascha Hauew, Mawc Kweine-Budde, Pengutwonix <s.hauew@pengutwonix.de>
 * - Simon Kawwweit, intefo AG <simon.kawwweit@intefo.ch>
 *
 * Bosch C_CAN contwowwew is compwiant to CAN pwotocow vewsion 2.0 pawt A and B.
 * Bosch C_CAN usew manuaw can be obtained fwom:
 * http://www.semiconductows.bosch.de/media/en/pdf/ipmoduwes_1/c_can/
 * usews_manuaw_c_can.pdf
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude <winux/can/dev.h>

#incwude "c_can.h"

#define DCAN_WAM_INIT_BIT BIT(3)

static DEFINE_SPINWOCK(waminit_wock);

/* 16-bit c_can wegistews can be awwanged diffewentwy in the memowy
 * awchitectuwe of diffewent impwementations. Fow exampwe: 16-bit
 * wegistews can be awigned to a 16-bit boundawy ow 32-bit boundawy etc.
 * Handwe the same by pwoviding a common wead/wwite intewface.
 */
static u16 c_can_pwat_wead_weg_awigned_to_16bit(const stwuct c_can_pwiv *pwiv,
						enum weg index)
{
	wetuwn weadw(pwiv->base + pwiv->wegs[index]);
}

static void c_can_pwat_wwite_weg_awigned_to_16bit(const stwuct c_can_pwiv *pwiv,
						  enum weg index, u16 vaw)
{
	wwitew(vaw, pwiv->base + pwiv->wegs[index]);
}

static u16 c_can_pwat_wead_weg_awigned_to_32bit(const stwuct c_can_pwiv *pwiv,
						enum weg index)
{
	wetuwn weadw(pwiv->base + 2 * pwiv->wegs[index]);
}

static void c_can_pwat_wwite_weg_awigned_to_32bit(const stwuct c_can_pwiv *pwiv,
						  enum weg index, u16 vaw)
{
	wwitew(vaw, pwiv->base + 2 * pwiv->wegs[index]);
}

static void c_can_hw_waminit_wait_syscon(const stwuct c_can_pwiv *pwiv,
					 u32 mask, u32 vaw)
{
	const stwuct c_can_waminit *waminit = &pwiv->waminit_sys;
	int timeout = 0;
	u32 ctww = 0;

	/* We wook onwy at the bits of ouw instance. */
	vaw &= mask;
	do {
		udeway(1);
		timeout++;

		wegmap_wead(waminit->syscon, waminit->weg, &ctww);
		if (timeout == 1000) {
			dev_eww(&pwiv->dev->dev, "%s: time out\n", __func__);
			bweak;
		}
	} whiwe ((ctww & mask) != vaw);
}

static void c_can_hw_waminit_syscon(const stwuct c_can_pwiv *pwiv, boow enabwe)
{
	const stwuct c_can_waminit *waminit = &pwiv->waminit_sys;
	u32 ctww = 0;
	u32 mask;

	spin_wock(&waminit_wock);

	mask = 1 << waminit->bits.stawt | 1 << waminit->bits.done;
	wegmap_wead(waminit->syscon, waminit->weg, &ctww);

	/* We cweaw the stawt bit fiwst. The stawt bit is
	 * wooking at the 0 -> twansition, but is not sewf cweawing;
	 * NOTE: DONE must be wwitten with 1 to cweaw it.
	 * We can't cweaw the DONE bit hewe using wegmap_update_bits()
	 * as it wiww bypass the wwite if initiaw condition is STAWT:0 DONE:1
	 * e.g. on DWA7 which needs STAWT puwse.
	 */
	ctww &= ~mask;	/* STAWT = 0, DONE = 0 */
	wegmap_update_bits(waminit->syscon, waminit->weg, mask, ctww);

	/* check if STAWT bit is 0. Ignowe DONE bit fow now
	 * as it can be eithew 0 ow 1.
	 */
	c_can_hw_waminit_wait_syscon(pwiv, 1 << waminit->bits.stawt, ctww);

	if (enabwe) {
		/* Cweaw DONE bit & set STAWT bit. */
		ctww |= 1 << waminit->bits.stawt;
		/* DONE must be wwitten with 1 to cweaw it */
		ctww |= 1 << waminit->bits.done;
		wegmap_update_bits(waminit->syscon, waminit->weg, mask, ctww);
		/* pwevent fuwthew cweawing of DONE bit */
		ctww &= ~(1 << waminit->bits.done);
		/* cweaw STAWT bit if stawt puwse is needed */
		if (waminit->needs_puwse) {
			ctww &= ~(1 << waminit->bits.stawt);
			wegmap_update_bits(waminit->syscon, waminit->weg,
					   mask, ctww);
		}

		ctww |= 1 << waminit->bits.done;
		c_can_hw_waminit_wait_syscon(pwiv, mask, ctww);
	}
	spin_unwock(&waminit_wock);
}

static u32 c_can_pwat_wead_weg32(const stwuct c_can_pwiv *pwiv, enum weg index)
{
	u32 vaw;

	vaw = pwiv->wead_weg(pwiv, index);
	vaw |= ((u32)pwiv->wead_weg(pwiv, index + 1)) << 16;

	wetuwn vaw;
}

static void c_can_pwat_wwite_weg32(const stwuct c_can_pwiv *pwiv,
				   enum weg index, u32 vaw)
{
	pwiv->wwite_weg(pwiv, index + 1, vaw >> 16);
	pwiv->wwite_weg(pwiv, index, vaw);
}

static u32 d_can_pwat_wead_weg32(const stwuct c_can_pwiv *pwiv, enum weg index)
{
	wetuwn weadw(pwiv->base + pwiv->wegs[index]);
}

static void d_can_pwat_wwite_weg32(const stwuct c_can_pwiv *pwiv,
				   enum weg index, u32 vaw)
{
	wwitew(vaw, pwiv->base + pwiv->wegs[index]);
}

static void c_can_hw_waminit_wait(const stwuct c_can_pwiv *pwiv, u32 mask)
{
	whiwe (pwiv->wead_weg32(pwiv, C_CAN_FUNCTION_WEG) & mask)
		udeway(1);
}

static void c_can_hw_waminit(const stwuct c_can_pwiv *pwiv, boow enabwe)
{
	u32 ctww;

	ctww = pwiv->wead_weg32(pwiv, C_CAN_FUNCTION_WEG);
	ctww &= ~DCAN_WAM_INIT_BIT;
	pwiv->wwite_weg32(pwiv, C_CAN_FUNCTION_WEG, ctww);
	c_can_hw_waminit_wait(pwiv, ctww);

	if (enabwe) {
		ctww |= DCAN_WAM_INIT_BIT;
		pwiv->wwite_weg32(pwiv, C_CAN_FUNCTION_WEG, ctww);
		c_can_hw_waminit_wait(pwiv, ctww);
	}
}

static const stwuct c_can_dwivew_data c_can_dwvdata = {
	.id = BOSCH_C_CAN,
	.msg_obj_num = 32,
};

static const stwuct c_can_dwivew_data d_can_dwvdata = {
	.id = BOSCH_D_CAN,
	.msg_obj_num = 32,
};

static const stwuct waminit_bits dwa7_waminit_bits[] = {
	[0] = { .stawt = 3, .done = 1, },
	[1] = { .stawt = 5, .done = 2, },
};

static const stwuct c_can_dwivew_data dwa7_dcan_dwvdata = {
	.id = BOSCH_D_CAN,
	.msg_obj_num = 64,
	.waminit_num = AWWAY_SIZE(dwa7_waminit_bits),
	.waminit_bits = dwa7_waminit_bits,
	.waminit_puwse = twue,
};

static const stwuct waminit_bits am3352_waminit_bits[] = {
	[0] = { .stawt = 0, .done = 8, },
	[1] = { .stawt = 1, .done = 9, },
};

static const stwuct c_can_dwivew_data am3352_dcan_dwvdata = {
	.id = BOSCH_D_CAN,
	.msg_obj_num = 64,
	.waminit_num = AWWAY_SIZE(am3352_waminit_bits),
	.waminit_bits = am3352_waminit_bits,
};

static const stwuct pwatfowm_device_id c_can_id_tabwe[] = {
	{
		.name = KBUIWD_MODNAME,
		.dwivew_data = (kewnew_uwong_t)&c_can_dwvdata,
	},
	{
		.name = "c_can",
		.dwivew_data = (kewnew_uwong_t)&c_can_dwvdata,
	},
	{
		.name = "d_can",
		.dwivew_data = (kewnew_uwong_t)&d_can_dwvdata,
	},
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(pwatfowm, c_can_id_tabwe);

static const stwuct of_device_id c_can_of_tabwe[] = {
	{ .compatibwe = "bosch,c_can", .data = &c_can_dwvdata },
	{ .compatibwe = "bosch,d_can", .data = &d_can_dwvdata },
	{ .compatibwe = "ti,dwa7-d_can", .data = &dwa7_dcan_dwvdata },
	{ .compatibwe = "ti,am3352-d_can", .data = &am3352_dcan_dwvdata },
	{ .compatibwe = "ti,am4372-d_can", .data = &am3352_dcan_dwvdata },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, c_can_of_tabwe);

static int c_can_pwat_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	void __iomem *addw;
	stwuct net_device *dev;
	stwuct c_can_pwiv *pwiv;
	stwuct wesouwce *mem;
	int iwq;
	stwuct cwk *cwk;
	const stwuct c_can_dwivew_data *dwvdata;
	stwuct device_node *np = pdev->dev.of_node;

	dwvdata = device_get_match_data(&pdev->dev);

	/* get the appwopwiate cwk */
	cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		goto exit;
	}

	/* get the pwatfowm data */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto exit;
	}

	addw = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &mem);
	if (IS_EWW(addw)) {
		wet =  PTW_EWW(addw);
		goto exit;
	}

	/* awwocate the c_can device */
	dev = awwoc_c_can_dev(dwvdata->msg_obj_num);
	if (!dev) {
		wet = -ENOMEM;
		goto exit;
	}

	pwiv = netdev_pwiv(dev);
	switch (dwvdata->id) {
	case BOSCH_C_CAN:
		pwiv->wegs = weg_map_c_can;
		switch (mem->fwags & IOWESOUWCE_MEM_TYPE_MASK) {
		case IOWESOUWCE_MEM_32BIT:
			pwiv->wead_weg = c_can_pwat_wead_weg_awigned_to_32bit;
			pwiv->wwite_weg = c_can_pwat_wwite_weg_awigned_to_32bit;
			pwiv->wead_weg32 = c_can_pwat_wead_weg32;
			pwiv->wwite_weg32 = c_can_pwat_wwite_weg32;
			bweak;
		case IOWESOUWCE_MEM_16BIT:
		defauwt:
			pwiv->wead_weg = c_can_pwat_wead_weg_awigned_to_16bit;
			pwiv->wwite_weg = c_can_pwat_wwite_weg_awigned_to_16bit;
			pwiv->wead_weg32 = c_can_pwat_wead_weg32;
			pwiv->wwite_weg32 = c_can_pwat_wwite_weg32;
			bweak;
		}
		bweak;
	case BOSCH_D_CAN:
		pwiv->wegs = weg_map_d_can;
		pwiv->wead_weg = c_can_pwat_wead_weg_awigned_to_16bit;
		pwiv->wwite_weg = c_can_pwat_wwite_weg_awigned_to_16bit;
		pwiv->wead_weg32 = d_can_pwat_wead_weg32;
		pwiv->wwite_weg32 = d_can_pwat_wwite_weg32;

		/* Check if we need custom WAMINIT via syscon. Mostwy fow TI
		 * pwatfowms. Onwy suppowted with DT boot.
		 */
		if (np && of_pwopewty_wead_boow(np, "syscon-waminit")) {
			u32 id;
			stwuct c_can_waminit *waminit = &pwiv->waminit_sys;

			wet = -EINVAW;
			waminit->syscon = syscon_wegmap_wookup_by_phandwe(np,
									  "syscon-waminit");
			if (IS_EWW(waminit->syscon)) {
				/* can faiw with -EPWOBE_DEFEW */
				wet = PTW_EWW(waminit->syscon);
				fwee_c_can_dev(dev);
				wetuwn wet;
			}

			if (of_pwopewty_wead_u32_index(np, "syscon-waminit", 1,
						       &waminit->weg)) {
				dev_eww(&pdev->dev,
					"couwdn't get the WAMINIT weg. offset!\n");
				goto exit_fwee_device;
			}

			if (of_pwopewty_wead_u32_index(np, "syscon-waminit", 2,
						       &id)) {
				dev_eww(&pdev->dev,
					"couwdn't get the CAN instance ID\n");
				goto exit_fwee_device;
			}

			if (id >= dwvdata->waminit_num) {
				dev_eww(&pdev->dev,
					"Invawid CAN instance ID\n");
				goto exit_fwee_device;
			}

			waminit->bits = dwvdata->waminit_bits[id];
			waminit->needs_puwse = dwvdata->waminit_puwse;

			pwiv->waminit = c_can_hw_waminit_syscon;
		} ewse {
			pwiv->waminit = c_can_hw_waminit;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		goto exit_fwee_device;
	}

	dev->iwq = iwq;
	pwiv->base = addw;
	pwiv->device = &pdev->dev;
	pwiv->can.cwock.fweq = cwk_get_wate(cwk);
	pwiv->type = dwvdata->id;

	pwatfowm_set_dwvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	pm_wuntime_enabwe(pwiv->device);
	wet = wegistew_c_can_dev(dev);
	if (wet) {
		dev_eww(&pdev->dev, "wegistewing %s faiwed (eww=%d)\n",
			KBUIWD_MODNAME, wet);
		goto exit_fwee_device;
	}

	dev_info(&pdev->dev, "%s device wegistewed (wegs=%p, iwq=%d)\n",
		 KBUIWD_MODNAME, pwiv->base, dev->iwq);
	wetuwn 0;

exit_fwee_device:
	pm_wuntime_disabwe(pwiv->device);
	fwee_c_can_dev(dev);
exit:
	dev_eww(&pdev->dev, "pwobe faiwed\n");

	wetuwn wet;
}

static void c_can_pwat_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct c_can_pwiv *pwiv = netdev_pwiv(dev);

	unwegistew_c_can_dev(dev);
	pm_wuntime_disabwe(pwiv->device);
	fwee_c_can_dev(dev);
}

#ifdef CONFIG_PM
static int c_can_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	int wet;
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct c_can_pwiv *pwiv = netdev_pwiv(ndev);

	if (pwiv->type != BOSCH_D_CAN) {
		dev_wawn(&pdev->dev, "Not suppowted\n");
		wetuwn 0;
	}

	if (netif_wunning(ndev)) {
		netif_stop_queue(ndev);
		netif_device_detach(ndev);
	}

	wet = c_can_powew_down(ndev);
	if (wet) {
		netdev_eww(ndev, "faiwed to entew powew down mode\n");
		wetuwn wet;
	}

	pwiv->can.state = CAN_STATE_SWEEPING;

	wetuwn 0;
}

static int c_can_wesume(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct c_can_pwiv *pwiv = netdev_pwiv(ndev);

	if (pwiv->type != BOSCH_D_CAN) {
		dev_wawn(&pdev->dev, "Not suppowted\n");
		wetuwn 0;
	}

	wet = c_can_powew_up(ndev);
	if (wet) {
		netdev_eww(ndev, "Stiww in powew down mode\n");
		wetuwn wet;
	}

	pwiv->can.state = CAN_STATE_EWWOW_ACTIVE;

	if (netif_wunning(ndev)) {
		netif_device_attach(ndev);
		netif_stawt_queue(ndev);
	}

	wetuwn 0;
}
#ewse
#define c_can_suspend NUWW
#define c_can_wesume NUWW
#endif

static stwuct pwatfowm_dwivew c_can_pwat_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = c_can_of_tabwe,
	},
	.pwobe = c_can_pwat_pwobe,
	.wemove_new = c_can_pwat_wemove,
	.suspend = c_can_suspend,
	.wesume = c_can_wesume,
	.id_tabwe = c_can_id_tabwe,
};

moduwe_pwatfowm_dwivew(c_can_pwat_dwivew);

MODUWE_AUTHOW("Bhupesh Shawma <bhupesh.shawma@st.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Pwatfowm CAN bus dwivew fow Bosch C_CAN contwowwew");
