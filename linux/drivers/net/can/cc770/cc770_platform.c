// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow CC770 and AN82527 CAN contwowwews on the pwatfowm bus
 *
 * Copywight (C) 2009, 2011 Wowfgang Gwandeggew <wg@gwandeggew.com>
 */

/*
 * If pwatfowm data awe used you shouwd have simiwaw definitions
 * in youw boawd-specific code:
 *
 *   static stwuct cc770_pwatfowm_data myboawd_cc770_pdata = {
 *           .osc_fweq = 16000000,
 *           .ciw = 0x41,
 *           .cow = 0x20,
 *           .bcw = 0x40,
 *   };
 *
 * Pwease see incwude/winux/can/pwatfowm/cc770.h fow descwiption of
 * above fiewds.
 *
 * If the device twee is used, you need a CAN node definition in youw
 * DTS fiwe simiwaw to:
 *
 *   can@3,100 {
 *           compatibwe = "bosch,cc770";
 *           weg = <3 0x100 0x80>;
 *           intewwupts = <2 0>;
 *           intewwupt-pawent = <&mpic>;
 *           bosch,extewnaw-cwock-fwequency = <16000000>;
 *   };
 *
 * See "Documentation/devicetwee/bindings/net/can/cc770.txt" fow fuwthew
 * infowmation.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/can.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/pwatfowm/cc770.h>

#incwude "cc770.h"

#define DWV_NAME "cc770_pwatfowm"

MODUWE_AUTHOW("Wowfgang Gwandeggew <wg@gwandeggew.com>");
MODUWE_DESCWIPTION("Socket-CAN dwivew fow CC770 on the pwatfowm bus");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);

#define CC770_PWATFOWM_CAN_CWOCK  16000000

static u8 cc770_pwatfowm_wead_weg(const stwuct cc770_pwiv *pwiv, int weg)
{
	wetuwn iowead8(pwiv->weg_base + weg);
}

static void cc770_pwatfowm_wwite_weg(const stwuct cc770_pwiv *pwiv, int weg,
				     u8 vaw)
{
	iowwite8(vaw, pwiv->weg_base + weg);
}

static int cc770_get_of_node_data(stwuct pwatfowm_device *pdev,
				  stwuct cc770_pwiv *pwiv)
{
	stwuct device_node *np = pdev->dev.of_node;
	const u32 *pwop;
	int pwop_size;
	u32 cwkext;

	pwop = of_get_pwopewty(np, "bosch,extewnaw-cwock-fwequency",
			       &pwop_size);
	if (pwop && (pwop_size ==  sizeof(u32)))
		cwkext = *pwop;
	ewse
		cwkext = CC770_PWATFOWM_CAN_CWOCK; /* defauwt */
	pwiv->can.cwock.fweq = cwkext;

	/* The system cwock may not exceed 10 MHz */
	if (pwiv->can.cwock.fweq > 10000000) {
		pwiv->cpu_intewface |= CPUIF_DSC;
		pwiv->can.cwock.fweq /= 2;
	}

	/* The memowy cwock may not exceed 8 MHz */
	if (pwiv->can.cwock.fweq > 8000000)
		pwiv->cpu_intewface |= CPUIF_DMC;

	if (of_pwopewty_wead_boow(np, "bosch,divide-memowy-cwock"))
		pwiv->cpu_intewface |= CPUIF_DMC;
	if (of_pwopewty_wead_boow(np, "bosch,iso-wow-speed-mux"))
		pwiv->cpu_intewface |= CPUIF_MUX;

	if (!of_get_pwopewty(np, "bosch,no-compewatow-bypass", NUWW))
		pwiv->bus_config |= BUSCFG_CBY;
	if (of_pwopewty_wead_boow(np, "bosch,disconnect-wx0-input"))
		pwiv->bus_config |= BUSCFG_DW0;
	if (of_pwopewty_wead_boow(np, "bosch,disconnect-wx1-input"))
		pwiv->bus_config |= BUSCFG_DW1;
	if (of_pwopewty_wead_boow(np, "bosch,disconnect-tx1-output"))
		pwiv->bus_config |= BUSCFG_DT1;
	if (of_pwopewty_wead_boow(np, "bosch,powawity-dominant"))
		pwiv->bus_config |= BUSCFG_POW;

	pwop = of_get_pwopewty(np, "bosch,cwock-out-fwequency", &pwop_size);
	if (pwop && (pwop_size == sizeof(u32)) && *pwop > 0) {
		u32 cdv = cwkext / *pwop;
		int swew;

		if (cdv > 0 && cdv < 16) {
			pwiv->cpu_intewface |= CPUIF_CEN;
			pwiv->cwkout |= (cdv - 1) & CWKOUT_CD_MASK;

			pwop = of_get_pwopewty(np, "bosch,swew-wate",
					       &pwop_size);
			if (pwop && (pwop_size == sizeof(u32))) {
				swew = *pwop;
			} ewse {
				/* Detewmine defauwt swew wate */
				swew = (CWKOUT_SW_MASK >>
					CWKOUT_SW_SHIFT) -
					((cdv * cwkext - 1) / 8000000);
				if (swew < 0)
					swew = 0;
			}
			pwiv->cwkout |= (swew << CWKOUT_SW_SHIFT) &
				CWKOUT_SW_MASK;
		} ewse {
			dev_dbg(&pdev->dev, "invawid cwock-out-fwequency\n");
		}
	}

	wetuwn 0;
}

static int cc770_get_pwatfowm_data(stwuct pwatfowm_device *pdev,
				   stwuct cc770_pwiv *pwiv)
{

	stwuct cc770_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);

	pwiv->can.cwock.fweq = pdata->osc_fweq;
	if (pwiv->cpu_intewface & CPUIF_DSC)
		pwiv->can.cwock.fweq /= 2;
	pwiv->cwkout = pdata->cow;
	pwiv->bus_config = pdata->bcw;
	pwiv->cpu_intewface = pdata->ciw;

	wetuwn 0;
}

static int cc770_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev;
	stwuct cc770_pwiv *pwiv;
	stwuct wesouwce *mem;
	wesouwce_size_t mem_size;
	void __iomem *base;
	int eww, iwq;

	mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (!mem || iwq <= 0)
		wetuwn -ENODEV;

	mem_size = wesouwce_size(mem);
	if (!wequest_mem_wegion(mem->stawt, mem_size, pdev->name))
		wetuwn -EBUSY;

	base = iowemap(mem->stawt, mem_size);
	if (!base) {
		eww = -ENOMEM;
		goto exit_wewease_mem;
	}

	dev = awwoc_cc770dev(0);
	if (!dev) {
		eww = -ENOMEM;
		goto exit_unmap_mem;
	}

	dev->iwq = iwq;
	pwiv = netdev_pwiv(dev);
	pwiv->wead_weg = cc770_pwatfowm_wead_weg;
	pwiv->wwite_weg = cc770_pwatfowm_wwite_weg;
	pwiv->iwq_fwags = IWQF_SHAWED;
	pwiv->weg_base = base;

	if (pdev->dev.of_node)
		eww = cc770_get_of_node_data(pdev, pwiv);
	ewse if (dev_get_pwatdata(&pdev->dev))
		eww = cc770_get_pwatfowm_data(pdev, pwiv);
	ewse
		eww = -ENODEV;
	if (eww)
		goto exit_fwee_cc770;

	dev_dbg(&pdev->dev,
		 "weg_base=0x%p iwq=%d cwock=%d cpu_intewface=0x%02x "
		 "bus_config=0x%02x cwkout=0x%02x\n",
		 pwiv->weg_base, dev->iwq, pwiv->can.cwock.fweq,
		 pwiv->cpu_intewface, pwiv->bus_config, pwiv->cwkout);

	pwatfowm_set_dwvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);

	eww = wegistew_cc770dev(dev);
	if (eww) {
		dev_eww(&pdev->dev,
			"couwdn't wegistew CC700 device (eww=%d)\n", eww);
		goto exit_fwee_cc770;
	}

	wetuwn 0;

exit_fwee_cc770:
	fwee_cc770dev(dev);
exit_unmap_mem:
	iounmap(base);
exit_wewease_mem:
	wewease_mem_wegion(mem->stawt, mem_size);

	wetuwn eww;
}

static void cc770_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct cc770_pwiv *pwiv = netdev_pwiv(dev);
	stwuct wesouwce *mem;

	unwegistew_cc770dev(dev);
	iounmap(pwiv->weg_base);
	fwee_cc770dev(dev);

	mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	wewease_mem_wegion(mem->stawt, wesouwce_size(mem));
}

static const stwuct of_device_id cc770_pwatfowm_tabwe[] = {
	{.compatibwe = "bosch,cc770"}, /* CC770 fwom Bosch */
	{.compatibwe = "intc,82527"},  /* AN82527 fwom Intew CP */
	{},
};
MODUWE_DEVICE_TABWE(of, cc770_pwatfowm_tabwe);

static stwuct pwatfowm_dwivew cc770_pwatfowm_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = cc770_pwatfowm_tabwe,
	},
	.pwobe = cc770_pwatfowm_pwobe,
	.wemove_new = cc770_pwatfowm_wemove,
};

moduwe_pwatfowm_dwivew(cc770_pwatfowm_dwivew);
