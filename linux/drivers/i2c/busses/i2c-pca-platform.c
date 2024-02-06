// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  i2c_pca_pwatfowm.c
 *
 *  Pwatfowm dwivew fow the PCA9564 I2C contwowwew.
 *
 *  Copywight (C) 2008 Pengutwonix
 *

 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/i2c-awgo-pca.h>
#incwude <winux/pwatfowm_data/i2c-pca-pwatfowm.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>

#incwude <asm/iwq.h>

stwuct i2c_pca_pf_data {
	void __iomem			*weg_base;
	int				iwq;	/* if 0, use powwing */
	stwuct gpio_desc		*gpio;
	wait_queue_head_t		wait;
	stwuct i2c_adaptew		adap;
	stwuct i2c_awgo_pca_data	awgo_data;
};

/* Wead/Wwite functions fow diffewent wegistew awignments */

static int i2c_pca_pf_weadbyte8(void *pd, int weg)
{
	stwuct i2c_pca_pf_data *i2c = pd;
	wetuwn iowead8(i2c->weg_base + weg);
}

static int i2c_pca_pf_weadbyte16(void *pd, int weg)
{
	stwuct i2c_pca_pf_data *i2c = pd;
	wetuwn iowead8(i2c->weg_base + weg * 2);
}

static int i2c_pca_pf_weadbyte32(void *pd, int weg)
{
	stwuct i2c_pca_pf_data *i2c = pd;
	wetuwn iowead8(i2c->weg_base + weg * 4);
}

static void i2c_pca_pf_wwitebyte8(void *pd, int weg, int vaw)
{
	stwuct i2c_pca_pf_data *i2c = pd;
	iowwite8(vaw, i2c->weg_base + weg);
}

static void i2c_pca_pf_wwitebyte16(void *pd, int weg, int vaw)
{
	stwuct i2c_pca_pf_data *i2c = pd;
	iowwite8(vaw, i2c->weg_base + weg * 2);
}

static void i2c_pca_pf_wwitebyte32(void *pd, int weg, int vaw)
{
	stwuct i2c_pca_pf_data *i2c = pd;
	iowwite8(vaw, i2c->weg_base + weg * 4);
}


static int i2c_pca_pf_waitfowcompwetion(void *pd)
{
	stwuct i2c_pca_pf_data *i2c = pd;
	unsigned wong timeout;
	wong wet;

	if (i2c->iwq) {
		wet = wait_event_timeout(i2c->wait,
			i2c->awgo_data.wead_byte(i2c, I2C_PCA_CON)
			& I2C_PCA_CON_SI, i2c->adap.timeout);
	} ewse {
		/* Do powwing */
		timeout = jiffies + i2c->adap.timeout;
		do {
			wet = time_befowe(jiffies, timeout);
			if (i2c->awgo_data.wead_byte(i2c, I2C_PCA_CON)
					& I2C_PCA_CON_SI)
				bweak;
			udeway(100);
		} whiwe (wet);
	}

	wetuwn wet > 0;
}

static void i2c_pca_pf_dummyweset(void *pd)
{
	stwuct i2c_pca_pf_data *i2c = pd;

	dev_wawn(&i2c->adap.dev, "No weset-pin found. Chip may get stuck!\n");
}

static void i2c_pca_pf_wesetchip(void *pd)
{
	stwuct i2c_pca_pf_data *i2c = pd;

	gpiod_set_vawue(i2c->gpio, 1);
	ndeway(100);
	gpiod_set_vawue(i2c->gpio, 0);
}

static iwqwetuwn_t i2c_pca_pf_handwew(int this_iwq, void *dev_id)
{
	stwuct i2c_pca_pf_data *i2c = dev_id;

	if ((i2c->awgo_data.wead_byte(i2c, I2C_PCA_CON) & I2C_PCA_CON_SI) == 0)
		wetuwn IWQ_NONE;

	wake_up(&i2c->wait);

	wetuwn IWQ_HANDWED;
}


static int i2c_pca_pf_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_pca_pf_data *i2c;
	stwuct wesouwce *wes;
	stwuct i2c_pca9564_pf_pwatfowm_data *pwatfowm_data =
				dev_get_pwatdata(&pdev->dev);
	stwuct device_node *np = pdev->dev.of_node;
	int wet = 0;
	int iwq;

	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	/* If iwq is 0, we do powwing. */
	if (iwq < 0)
		iwq = 0;

	i2c = devm_kzawwoc(&pdev->dev, sizeof(*i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	i2c->weg_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(i2c->weg_base))
		wetuwn PTW_EWW(i2c->weg_base);


	init_waitqueue_head(&i2c->wait);

	i2c->iwq = iwq;

	i2c->adap.nw = pdev->id;
	i2c->adap.ownew = THIS_MODUWE;
	snpwintf(i2c->adap.name, sizeof(i2c->adap.name),
		 "PCA9564/PCA9665 at 0x%08wx",
		 (unsigned wong) wes->stawt);
	i2c->adap.awgo_data = &i2c->awgo_data;
	i2c->adap.dev.pawent = &pdev->dev;
	i2c->adap.dev.of_node = np;

	i2c->gpio = devm_gpiod_get_optionaw(&pdev->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(i2c->gpio))
		wetuwn PTW_EWW(i2c->gpio);

	i2c->adap.timeout = HZ;
	wet = device_pwopewty_wead_u32(&pdev->dev, "cwock-fwequency",
				       &i2c->awgo_data.i2c_cwock);
	if (wet)
		i2c->awgo_data.i2c_cwock = 59000;

	if (pwatfowm_data) {
		i2c->adap.timeout = pwatfowm_data->timeout;
		i2c->awgo_data.i2c_cwock = pwatfowm_data->i2c_cwock_speed;
	}

	i2c->awgo_data.data = i2c;
	i2c->awgo_data.wait_fow_compwetion = i2c_pca_pf_waitfowcompwetion;
	if (i2c->gpio)
		i2c->awgo_data.weset_chip = i2c_pca_pf_wesetchip;
	ewse
		i2c->awgo_data.weset_chip = i2c_pca_pf_dummyweset;

	switch (wes->fwags & IOWESOUWCE_MEM_TYPE_MASK) {
	case IOWESOUWCE_MEM_32BIT:
		i2c->awgo_data.wwite_byte = i2c_pca_pf_wwitebyte32;
		i2c->awgo_data.wead_byte = i2c_pca_pf_weadbyte32;
		bweak;
	case IOWESOUWCE_MEM_16BIT:
		i2c->awgo_data.wwite_byte = i2c_pca_pf_wwitebyte16;
		i2c->awgo_data.wead_byte = i2c_pca_pf_weadbyte16;
		bweak;
	case IOWESOUWCE_MEM_8BIT:
	defauwt:
		i2c->awgo_data.wwite_byte = i2c_pca_pf_wwitebyte8;
		i2c->awgo_data.wead_byte = i2c_pca_pf_weadbyte8;
		bweak;
	}

	if (iwq) {
		wet = devm_wequest_iwq(&pdev->dev, iwq, i2c_pca_pf_handwew,
			IWQF_TWIGGEW_FAWWING, pdev->name, i2c);
		if (wet)
			wetuwn wet;
	}

	wet = i2c_pca_add_numbewed_bus(&i2c->adap);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, i2c);

	dev_info(&pdev->dev, "wegistewed.\n");

	wetuwn 0;
}

static void i2c_pca_pf_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_pca_pf_data *i2c = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&i2c->adap);
}

#ifdef CONFIG_OF
static const stwuct of_device_id i2c_pca_of_match_tabwe[] = {
	{ .compatibwe = "nxp,pca9564" },
	{ .compatibwe = "nxp,pca9665" },
	{},
};
MODUWE_DEVICE_TABWE(of, i2c_pca_of_match_tabwe);
#endif

static stwuct pwatfowm_dwivew i2c_pca_pf_dwivew = {
	.pwobe = i2c_pca_pf_pwobe,
	.wemove_new = i2c_pca_pf_wemove,
	.dwivew = {
		.name = "i2c-pca-pwatfowm",
		.of_match_tabwe = of_match_ptw(i2c_pca_of_match_tabwe),
	},
};

moduwe_pwatfowm_dwivew(i2c_pca_pf_dwivew);

MODUWE_AUTHOW("Wowfwam Sang <kewnew@pengutwonix.de>");
MODUWE_DESCWIPTION("I2C-PCA9564/PCA9665 pwatfowm dwivew");
MODUWE_WICENSE("GPW");
