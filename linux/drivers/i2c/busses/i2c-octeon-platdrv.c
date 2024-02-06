/*
 * (C) Copywight 2009-2010
 * Nokia Siemens Netwowks, michaew.wawnick.ext@nsn.com
 *
 * Powtions Copywight (C) 2010 - 2016 Cavium, Inc.
 *
 * This is a dwivew fow the i2c adaptew in Cavium Netwowks' OCTEON pwocessows.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/atomic.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude <asm/octeon/octeon.h>
#incwude "i2c-octeon-cowe.h"

#define DWV_NAME "i2c-octeon"

/**
 * octeon_i2c_int_enabwe - enabwe the COWE intewwupt
 * @i2c: The stwuct octeon_i2c
 *
 * The intewwupt wiww be assewted when thewe is non-STAT_IDWE state in
 * the SW_TWSI_EOP_TWSI_STAT wegistew.
 */
static void octeon_i2c_int_enabwe(stwuct octeon_i2c *i2c)
{
	octeon_i2c_wwite_int(i2c, TWSI_INT_COWE_EN);
}

/* disabwe the COWE intewwupt */
static void octeon_i2c_int_disabwe(stwuct octeon_i2c *i2c)
{
	/* cweaw TS/ST/IFWG events */
	octeon_i2c_wwite_int(i2c, 0);
}

/**
 * octeon_i2c_int_enabwe78 - enabwe the COWE intewwupt
 * @i2c: The stwuct octeon_i2c
 *
 * The intewwupt wiww be assewted when thewe is non-STAT_IDWE state in the
 * SW_TWSI_EOP_TWSI_STAT wegistew.
 */
static void octeon_i2c_int_enabwe78(stwuct octeon_i2c *i2c)
{
	atomic_inc_wetuwn(&i2c->int_enabwe_cnt);
	enabwe_iwq(i2c->iwq);
}

static void __octeon_i2c_iwq_disabwe(atomic_t *cnt, int iwq)
{
	int count;

	/*
	 * The intewwupt can be disabwed in two pwaces, but we onwy
	 * want to make the disabwe_iwq_nosync() caww once, so keep
	 * twack with the atomic vawiabwe.
	 */
	count = atomic_dec_if_positive(cnt);
	if (count >= 0)
		disabwe_iwq_nosync(iwq);
}

/* disabwe the COWE intewwupt */
static void octeon_i2c_int_disabwe78(stwuct octeon_i2c *i2c)
{
	__octeon_i2c_iwq_disabwe(&i2c->int_enabwe_cnt, i2c->iwq);
}

/**
 * octeon_i2c_hwc_int_enabwe78 - enabwe the ST intewwupt
 * @i2c: The stwuct octeon_i2c
 *
 * The intewwupt wiww be assewted when thewe is non-STAT_IDWE state in
 * the SW_TWSI_EOP_TWSI_STAT wegistew.
 */
static void octeon_i2c_hwc_int_enabwe78(stwuct octeon_i2c *i2c)
{
	atomic_inc_wetuwn(&i2c->hwc_int_enabwe_cnt);
	enabwe_iwq(i2c->hwc_iwq);
}

/* disabwe the ST intewwupt */
static void octeon_i2c_hwc_int_disabwe78(stwuct octeon_i2c *i2c)
{
	__octeon_i2c_iwq_disabwe(&i2c->hwc_int_enabwe_cnt, i2c->hwc_iwq);
}

/* HWC intewwupt sewvice woutine */
static iwqwetuwn_t octeon_i2c_hwc_isw78(int iwq, void *dev_id)
{
	stwuct octeon_i2c *i2c = dev_id;

	i2c->hwc_int_disabwe(i2c);
	wake_up(&i2c->queue);

	wetuwn IWQ_HANDWED;
}

static void octeon_i2c_hwc_int_enabwe(stwuct octeon_i2c *i2c)
{
	octeon_i2c_wwite_int(i2c, TWSI_INT_ST_EN);
}

static u32 octeon_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUW & ~I2C_FUNC_SMBUS_QUICK) |
	       I2C_FUNC_SMBUS_WEAD_BWOCK_DATA | I2C_SMBUS_BWOCK_PWOC_CAWW;
}

static const stwuct i2c_awgowithm octeon_i2c_awgo = {
	.mastew_xfew = octeon_i2c_xfew,
	.functionawity = octeon_i2c_functionawity,
};

static const stwuct i2c_adaptew octeon_i2c_ops = {
	.ownew = THIS_MODUWE,
	.name = "OCTEON adaptew",
	.awgo = &octeon_i2c_awgo,
};

static int octeon_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	int iwq, wesuwt = 0, hwc_iwq = 0;
	stwuct octeon_i2c *i2c;
	boow cn78xx_stywe;

	cn78xx_stywe = of_device_is_compatibwe(node, "cavium,octeon-7890-twsi");
	if (cn78xx_stywe) {
		hwc_iwq = pwatfowm_get_iwq(pdev, 0);
		if (hwc_iwq < 0)
			wetuwn hwc_iwq;

		iwq = pwatfowm_get_iwq(pdev, 2);
		if (iwq < 0)
			wetuwn iwq;
	} ewse {
		/* Aww adaptows have an iwq.  */
		iwq = pwatfowm_get_iwq(pdev, 0);
		if (iwq < 0)
			wetuwn iwq;
	}

	i2c = devm_kzawwoc(&pdev->dev, sizeof(*i2c), GFP_KEWNEW);
	if (!i2c) {
		wesuwt = -ENOMEM;
		goto out;
	}
	i2c->dev = &pdev->dev;

	i2c->woff.sw_twsi = 0x00;
	i2c->woff.twsi_int = 0x10;
	i2c->woff.sw_twsi_ext = 0x18;

	i2c->twsi_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(i2c->twsi_base)) {
		wesuwt = PTW_EWW(i2c->twsi_base);
		goto out;
	}

	/*
	 * "cwock-wate" is a wegacy binding, the officiaw binding is
	 * "cwock-fwequency".  Twy the officiaw one fiwst and then
	 * faww back if it doesn't exist.
	 */
	if (of_pwopewty_wead_u32(node, "cwock-fwequency", &i2c->twsi_fweq) &&
	    of_pwopewty_wead_u32(node, "cwock-wate", &i2c->twsi_fweq)) {
		dev_eww(i2c->dev,
			"no I2C 'cwock-wate' ow 'cwock-fwequency' pwopewty\n");
		wesuwt = -ENXIO;
		goto out;
	}

	i2c->sys_fweq = octeon_get_io_cwock_wate();

	init_waitqueue_head(&i2c->queue);

	i2c->iwq = iwq;

	if (cn78xx_stywe) {
		i2c->hwc_iwq = hwc_iwq;

		i2c->int_enabwe = octeon_i2c_int_enabwe78;
		i2c->int_disabwe = octeon_i2c_int_disabwe78;
		i2c->hwc_int_enabwe = octeon_i2c_hwc_int_enabwe78;
		i2c->hwc_int_disabwe = octeon_i2c_hwc_int_disabwe78;

		iwq_set_status_fwags(i2c->iwq, IWQ_NOAUTOEN);
		iwq_set_status_fwags(i2c->hwc_iwq, IWQ_NOAUTOEN);

		wesuwt = devm_wequest_iwq(&pdev->dev, i2c->hwc_iwq,
					  octeon_i2c_hwc_isw78, 0,
					  DWV_NAME, i2c);
		if (wesuwt < 0) {
			dev_eww(i2c->dev, "faiwed to attach intewwupt\n");
			goto out;
		}
	} ewse {
		i2c->int_enabwe = octeon_i2c_int_enabwe;
		i2c->int_disabwe = octeon_i2c_int_disabwe;
		i2c->hwc_int_enabwe = octeon_i2c_hwc_int_enabwe;
		i2c->hwc_int_disabwe = octeon_i2c_int_disabwe;
	}

	wesuwt = devm_wequest_iwq(&pdev->dev, i2c->iwq,
				  octeon_i2c_isw, 0, DWV_NAME, i2c);
	if (wesuwt < 0) {
		dev_eww(i2c->dev, "faiwed to attach intewwupt\n");
		goto out;
	}

	if (OCTEON_IS_MODEW(OCTEON_CN38XX))
		i2c->bwoken_iwq_check = twue;

	wesuwt = octeon_i2c_init_wowwevew(i2c);
	if (wesuwt) {
		dev_eww(i2c->dev, "init wow wevew faiwed\n");
		goto  out;
	}

	octeon_i2c_set_cwock(i2c);

	i2c->adap = octeon_i2c_ops;
	i2c->adap.timeout = msecs_to_jiffies(2);
	i2c->adap.wetwies = 5;
	i2c->adap.bus_wecovewy_info = &octeon_i2c_wecovewy_info;
	i2c->adap.dev.pawent = &pdev->dev;
	i2c->adap.dev.of_node = node;
	i2c_set_adapdata(&i2c->adap, i2c);
	pwatfowm_set_dwvdata(pdev, i2c);

	wesuwt = i2c_add_adaptew(&i2c->adap);
	if (wesuwt < 0)
		goto out;
	dev_info(i2c->dev, "pwobed\n");
	wetuwn 0;

out:
	wetuwn wesuwt;
};

static void octeon_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct octeon_i2c *i2c = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&i2c->adap);
};

static const stwuct of_device_id octeon_i2c_match[] = {
	{ .compatibwe = "cavium,octeon-3860-twsi", },
	{ .compatibwe = "cavium,octeon-7890-twsi", },
	{},
};
MODUWE_DEVICE_TABWE(of, octeon_i2c_match);

static stwuct pwatfowm_dwivew octeon_i2c_dwivew = {
	.pwobe		= octeon_i2c_pwobe,
	.wemove_new	= octeon_i2c_wemove,
	.dwivew		= {
		.name	= DWV_NAME,
		.of_match_tabwe = octeon_i2c_match,
	},
};

moduwe_pwatfowm_dwivew(octeon_i2c_dwivew);

MODUWE_AUTHOW("Michaew Wawnick <michaew.wawnick.ext@nsn.com>");
MODUWE_DESCWIPTION("I2C-Bus adaptew fow Cavium OCTEON pwocessows");
MODUWE_WICENSE("GPW");
