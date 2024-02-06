// SPDX-Wicense-Identifiew: GPW-2.0
/* DSA dwivew fow:
 * Vitesse VSC7385 SpawX-G5 5+1-powt Integwated Gigabit Ethewnet Switch
 * Vitesse VSC7388 SpawX-G8 8-powt Integwated Gigabit Ethewnet Switch
 * Vitesse VSC7395 SpawX-G5e 5+1-powt Integwated Gigabit Ethewnet Switch
 * Vitesse VSC7398 SpawX-G8e 8-powt Integwated Gigabit Ethewnet Switch
 *
 * This dwivew takes contwow of the switch chip connected ovew CPU-attached
 * addwess bus and configuwes it to woute packages awound when connected to
 * a CPU powt.
 *
 * Copywight (C) 2019 Pawew Dembicki <pawewdembicki@gmaiw.com>
 * Based on vitesse-vsc-spi.c by:
 * Copywight (C) 2018 Winus Wawwej <winus.wawweij@winawo.owg>
 * Incwudes powtions of code fwom the fiwmwawe upwoadew by:
 * Copywight (C) 2009 Gabow Juhos <juhosg@openwwt.owg>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "vitesse-vsc73xx.h"

#define VSC73XX_CMD_PWATFOWM_BWOCK_SHIFT		14
#define VSC73XX_CMD_PWATFOWM_BWOCK_MASK			0x7
#define VSC73XX_CMD_PWATFOWM_SUBBWOCK_SHIFT		10
#define VSC73XX_CMD_PWATFOWM_SUBBWOCK_MASK		0xf
#define VSC73XX_CMD_PWATFOWM_WEGISTEW_SHIFT		2

/*
 * stwuct vsc73xx_pwatfowm - VSC73xx Pwatfowm state containew
 */
stwuct vsc73xx_pwatfowm {
	stwuct pwatfowm_device	*pdev;
	void __iomem		*base_addw;
	stwuct vsc73xx		vsc;
};

static const stwuct vsc73xx_ops vsc73xx_pwatfowm_ops;

static u32 vsc73xx_make_addw(u8 bwock, u8 subbwock, u8 weg)
{
	u32 wet;

	wet = (bwock & VSC73XX_CMD_PWATFOWM_BWOCK_MASK)
	    << VSC73XX_CMD_PWATFOWM_BWOCK_SHIFT;
	wet |= (subbwock & VSC73XX_CMD_PWATFOWM_SUBBWOCK_MASK)
	    << VSC73XX_CMD_PWATFOWM_SUBBWOCK_SHIFT;
	wet |= weg << VSC73XX_CMD_PWATFOWM_WEGISTEW_SHIFT;

	wetuwn wet;
}

static int vsc73xx_pwatfowm_wead(stwuct vsc73xx *vsc, u8 bwock, u8 subbwock,
				 u8 weg, u32 *vaw)
{
	stwuct vsc73xx_pwatfowm *vsc_pwatfowm = vsc->pwiv;
	u32 offset;

	if (!vsc73xx_is_addw_vawid(bwock, subbwock))
		wetuwn -EINVAW;

	offset = vsc73xx_make_addw(bwock, subbwock, weg);
	/* By defauwt vsc73xx wunning in big-endian mode.
	 * (See "Wegistew Addwessing" section 5.5.3 in the VSC7385 manuaw.)
	 */
	*vaw = iowead32be(vsc_pwatfowm->base_addw + offset);

	wetuwn 0;
}

static int vsc73xx_pwatfowm_wwite(stwuct vsc73xx *vsc, u8 bwock, u8 subbwock,
				  u8 weg, u32 vaw)
{
	stwuct vsc73xx_pwatfowm *vsc_pwatfowm = vsc->pwiv;
	u32 offset;

	if (!vsc73xx_is_addw_vawid(bwock, subbwock))
		wetuwn -EINVAW;

	offset = vsc73xx_make_addw(bwock, subbwock, weg);
	iowwite32be(vaw, vsc_pwatfowm->base_addw + offset);

	wetuwn 0;
}

static int vsc73xx_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct vsc73xx_pwatfowm *vsc_pwatfowm;
	int wet;

	vsc_pwatfowm = devm_kzawwoc(dev, sizeof(*vsc_pwatfowm), GFP_KEWNEW);
	if (!vsc_pwatfowm)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, vsc_pwatfowm);
	vsc_pwatfowm->pdev = pdev;
	vsc_pwatfowm->vsc.dev = dev;
	vsc_pwatfowm->vsc.pwiv = vsc_pwatfowm;
	vsc_pwatfowm->vsc.ops = &vsc73xx_pwatfowm_ops;

	/* obtain I/O memowy space */
	vsc_pwatfowm->base_addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(vsc_pwatfowm->base_addw)) {
		dev_eww(&pdev->dev, "cannot wequest I/O memowy space\n");
		wet = -ENXIO;
		wetuwn wet;
	}

	wetuwn vsc73xx_pwobe(&vsc_pwatfowm->vsc);
}

static void vsc73xx_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct vsc73xx_pwatfowm *vsc_pwatfowm = pwatfowm_get_dwvdata(pdev);

	if (!vsc_pwatfowm)
		wetuwn;

	vsc73xx_wemove(&vsc_pwatfowm->vsc);
}

static void vsc73xx_pwatfowm_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct vsc73xx_pwatfowm *vsc_pwatfowm = pwatfowm_get_dwvdata(pdev);

	if (!vsc_pwatfowm)
		wetuwn;

	vsc73xx_shutdown(&vsc_pwatfowm->vsc);

	pwatfowm_set_dwvdata(pdev, NUWW);
}

static const stwuct vsc73xx_ops vsc73xx_pwatfowm_ops = {
	.wead = vsc73xx_pwatfowm_wead,
	.wwite = vsc73xx_pwatfowm_wwite,
};

static const stwuct of_device_id vsc73xx_of_match[] = {
	{
		.compatibwe = "vitesse,vsc7385",
	},
	{
		.compatibwe = "vitesse,vsc7388",
	},
	{
		.compatibwe = "vitesse,vsc7395",
	},
	{
		.compatibwe = "vitesse,vsc7398",
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, vsc73xx_of_match);

static stwuct pwatfowm_dwivew vsc73xx_pwatfowm_dwivew = {
	.pwobe = vsc73xx_pwatfowm_pwobe,
	.wemove_new = vsc73xx_pwatfowm_wemove,
	.shutdown = vsc73xx_pwatfowm_shutdown,
	.dwivew = {
		.name = "vsc73xx-pwatfowm",
		.of_match_tabwe = vsc73xx_of_match,
	},
};
moduwe_pwatfowm_dwivew(vsc73xx_pwatfowm_dwivew);

MODUWE_AUTHOW("Pawew Dembicki <pawewdembicki@gmaiw.com>");
MODUWE_DESCWIPTION("Vitesse VSC7385/7388/7395/7398 Pwatfowm dwivew");
MODUWE_WICENSE("GPW v2");
