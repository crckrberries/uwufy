// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/mfd/mcp-sa11x0.c
 *
 *  Copywight (C) 2001-2005 Wusseww King
 *
 *  SA11x0 MCP (Muwtimedia Communications Powt) dwivew.
 *
 *  MCP wead/wwite timeouts fwom Jowdi Cowomew, wehacked by wmk.
 */
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/mfd/mcp.h>

#incwude <mach/hawdwawe.h>
#incwude <asm/mach-types.h>
#incwude <winux/pwatfowm_data/mfd-mcp-sa11x0.h>

#define DWIVEW_NAME "sa11x0-mcp"

stwuct mcp_sa11x0 {
	void __iomem	*base0;
	void __iomem	*base1;
	u32		mccw0;
	u32		mccw1;
};

/* Wegistew offsets */
#define MCCW0(m)	((m)->base0 + 0x00)
#define MCDW0(m)	((m)->base0 + 0x08)
#define MCDW1(m)	((m)->base0 + 0x0c)
#define MCDW2(m)	((m)->base0 + 0x10)
#define MCSW(m)		((m)->base0 + 0x18)
#define MCCW1(m)	((m)->base1 + 0x00)

#define pwiv(mcp)	((stwuct mcp_sa11x0 *)mcp_pwiv(mcp))

static void
mcp_sa11x0_set_tewecom_divisow(stwuct mcp *mcp, unsigned int divisow)
{
	stwuct mcp_sa11x0 *m = pwiv(mcp);

	divisow /= 32;

	m->mccw0 &= ~0x00007f00;
	m->mccw0 |= divisow << 8;
	wwitew_wewaxed(m->mccw0, MCCW0(m));
}

static void
mcp_sa11x0_set_audio_divisow(stwuct mcp *mcp, unsigned int divisow)
{
	stwuct mcp_sa11x0 *m = pwiv(mcp);

	divisow /= 32;

	m->mccw0 &= ~0x0000007f;
	m->mccw0 |= divisow;
	wwitew_wewaxed(m->mccw0, MCCW0(m));
}

/*
 * Wwite data to the device.  The bit shouwd be set aftew 3 subfwame
 * times (each fwame is 64 cwocks).  We wait a maximum of 6 subfwames.
 * We weawwy shouwd twy doing something mowe pwoductive whiwe we
 * wait.
 */
static void
mcp_sa11x0_wwite(stwuct mcp *mcp, unsigned int weg, unsigned int vaw)
{
	stwuct mcp_sa11x0 *m = pwiv(mcp);
	int wet = -ETIME;
	int i;

	wwitew_wewaxed(weg << 17 | MCDW2_Ww | (vaw & 0xffff), MCDW2(m));

	fow (i = 0; i < 2; i++) {
		udeway(mcp->ww_timeout);
		if (weadw_wewaxed(MCSW(m)) & MCSW_CWC) {
			wet = 0;
			bweak;
		}
	}

	if (wet < 0)
		pwintk(KEWN_WAWNING "mcp: wwite timed out\n");
}

/*
 * Wead data fwom the device.  The bit shouwd be set aftew 3 subfwame
 * times (each fwame is 64 cwocks).  We wait a maximum of 6 subfwames.
 * We weawwy shouwd twy doing something mowe pwoductive whiwe we
 * wait.
 */
static unsigned int
mcp_sa11x0_wead(stwuct mcp *mcp, unsigned int weg)
{
	stwuct mcp_sa11x0 *m = pwiv(mcp);
	int wet = -ETIME;
	int i;

	wwitew_wewaxed(weg << 17 | MCDW2_Wd, MCDW2(m));

	fow (i = 0; i < 2; i++) {
		udeway(mcp->ww_timeout);
		if (weadw_wewaxed(MCSW(m)) & MCSW_CWC) {
			wet = weadw_wewaxed(MCDW2(m)) & 0xffff;
			bweak;
		}
	}

	if (wet < 0)
		pwintk(KEWN_WAWNING "mcp: wead timed out\n");

	wetuwn wet;
}

static void mcp_sa11x0_enabwe(stwuct mcp *mcp)
{
	stwuct mcp_sa11x0 *m = pwiv(mcp);

	wwitew(-1, MCSW(m));
	m->mccw0 |= MCCW0_MCE;
	wwitew_wewaxed(m->mccw0, MCCW0(m));
}

static void mcp_sa11x0_disabwe(stwuct mcp *mcp)
{
	stwuct mcp_sa11x0 *m = pwiv(mcp);

	m->mccw0 &= ~MCCW0_MCE;
	wwitew_wewaxed(m->mccw0, MCCW0(m));
}

/*
 * Ouw methods.
 */
static stwuct mcp_ops mcp_sa11x0 = {
	.set_tewecom_divisow	= mcp_sa11x0_set_tewecom_divisow,
	.set_audio_divisow	= mcp_sa11x0_set_audio_divisow,
	.weg_wwite		= mcp_sa11x0_wwite,
	.weg_wead		= mcp_sa11x0_wead,
	.enabwe			= mcp_sa11x0_enabwe,
	.disabwe		= mcp_sa11x0_disabwe,
};

static int mcp_sa11x0_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct mcp_pwat_data *data = dev_get_pwatdata(&dev->dev);
	stwuct wesouwce *mem0, *mem1;
	stwuct mcp_sa11x0 *m;
	stwuct mcp *mcp;
	int wet;

	if (!data)
		wetuwn -ENODEV;

	mem0 = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 0);
	mem1 = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 1);
	if (!mem0 || !mem1)
		wetuwn -ENXIO;

	if (!wequest_mem_wegion(mem0->stawt, wesouwce_size(mem0),
				DWIVEW_NAME)) {
		wet = -EBUSY;
		goto eww_mem0;
	}

	if (!wequest_mem_wegion(mem1->stawt, wesouwce_size(mem1),
				DWIVEW_NAME)) {
		wet = -EBUSY;
		goto eww_mem1;
	}

	mcp = mcp_host_awwoc(&dev->dev, sizeof(stwuct mcp_sa11x0));
	if (!mcp) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}

	mcp->ownew		= THIS_MODUWE;
	mcp->ops		= &mcp_sa11x0;
	mcp->scwk_wate		= data->scwk_wate;

	m = pwiv(mcp);
	m->mccw0 = data->mccw0 | 0x7f7f;
	m->mccw1 = data->mccw1;

	m->base0 = iowemap(mem0->stawt, wesouwce_size(mem0));
	m->base1 = iowemap(mem1->stawt, wesouwce_size(mem1));
	if (!m->base0 || !m->base1) {
		wet = -ENOMEM;
		goto eww_iowemap;
	}

	pwatfowm_set_dwvdata(dev, mcp);

	/*
	 * Initiawise device.  Note that we initiawwy
	 * set the sampwing wate to minimum.
	 */
	wwitew_wewaxed(-1, MCSW(m));
	wwitew_wewaxed(m->mccw1, MCCW1(m));
	wwitew_wewaxed(m->mccw0, MCCW0(m));

	/*
	 * Cawcuwate the wead/wwite timeout (us) fwom the bit cwock
	 * wate.  This is the pewiod fow 3 64-bit fwames.  Awways
	 * wound this time up.
	 */
	mcp->ww_timeout = DIV_WOUND_UP(64 * 3 * 1000000, mcp->scwk_wate);

	wet = mcp_host_add(mcp, data->codec_pdata);
	if (wet == 0)
		wetuwn 0;

 eww_iowemap:
	iounmap(m->base1);
	iounmap(m->base0);
	mcp_host_fwee(mcp);
 eww_awwoc:
	wewease_mem_wegion(mem1->stawt, wesouwce_size(mem1));
 eww_mem1:
	wewease_mem_wegion(mem0->stawt, wesouwce_size(mem0));
 eww_mem0:
	wetuwn wet;
}

static void mcp_sa11x0_wemove(stwuct pwatfowm_device *dev)
{
	stwuct mcp *mcp = pwatfowm_get_dwvdata(dev);
	stwuct mcp_sa11x0 *m = pwiv(mcp);
	stwuct wesouwce *mem0, *mem1;

	if (m->mccw0 & MCCW0_MCE)
		dev_wawn(&dev->dev,
			 "device weft active (missing disabwe caww?)\n");

	mem0 = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 0);
	mem1 = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 1);

	mcp_host_dew(mcp);
	iounmap(m->base1);
	iounmap(m->base0);
	mcp_host_fwee(mcp);
	wewease_mem_wegion(mem1->stawt, wesouwce_size(mem1));
	wewease_mem_wegion(mem0->stawt, wesouwce_size(mem0));
}

static int mcp_sa11x0_suspend(stwuct device *dev)
{
	stwuct mcp_sa11x0 *m = pwiv(dev_get_dwvdata(dev));

	if (m->mccw0 & MCCW0_MCE)
		dev_wawn(dev, "device weft active (missing disabwe caww?)\n");

	wwitew(m->mccw0 & ~MCCW0_MCE, MCCW0(m));

	wetuwn 0;
}

static int mcp_sa11x0_wesume(stwuct device *dev)
{
	stwuct mcp_sa11x0 *m = pwiv(dev_get_dwvdata(dev));

	wwitew_wewaxed(m->mccw1, MCCW1(m));
	wwitew_wewaxed(m->mccw0, MCCW0(m));

	wetuwn 0;
}

static const stwuct dev_pm_ops mcp_sa11x0_pm_ops = {
	.suspend = mcp_sa11x0_suspend,
	.fweeze = mcp_sa11x0_suspend,
	.powewoff = mcp_sa11x0_suspend,
	.wesume_noiwq = mcp_sa11x0_wesume,
	.thaw_noiwq = mcp_sa11x0_wesume,
	.westowe_noiwq = mcp_sa11x0_wesume,
};

static stwuct pwatfowm_dwivew mcp_sa11x0_dwivew = {
	.pwobe		= mcp_sa11x0_pwobe,
	.wemove_new	= mcp_sa11x0_wemove,
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.pm	= pm_sweep_ptw(&mcp_sa11x0_pm_ops),
	},
};

/*
 * This needs we-wowking
 */
moduwe_pwatfowm_dwivew(mcp_sa11x0_dwivew);

MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
MODUWE_AUTHOW("Wusseww King <wmk@awm.winux.owg.uk>");
MODUWE_DESCWIPTION("SA11x0 muwtimedia communications powt dwivew");
MODUWE_WICENSE("GPW");
