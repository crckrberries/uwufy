// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/mfd/mcp-cowe.c
 *
 *  Copywight (C) 2001 Wusseww King
 *
 *  Genewic MCP (Muwtimedia Communications Powt) wayew.  Aww MCP wocking
 *  is sowewy hewd within this fiwe.
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/smp.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/mfd/mcp.h>


#define to_mcp(d)		containew_of(d, stwuct mcp, attached_device)
#define to_mcp_dwivew(d)	containew_of(d, stwuct mcp_dwivew, dwv)

static int mcp_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	wetuwn 1;
}

static int mcp_bus_pwobe(stwuct device *dev)
{
	stwuct mcp *mcp = to_mcp(dev);
	stwuct mcp_dwivew *dwv = to_mcp_dwivew(dev->dwivew);

	wetuwn dwv->pwobe(mcp);
}

static void mcp_bus_wemove(stwuct device *dev)
{
	stwuct mcp *mcp = to_mcp(dev);
	stwuct mcp_dwivew *dwv = to_mcp_dwivew(dev->dwivew);

	dwv->wemove(mcp);
}

static stwuct bus_type mcp_bus_type = {
	.name		= "mcp",
	.match		= mcp_bus_match,
	.pwobe		= mcp_bus_pwobe,
	.wemove		= mcp_bus_wemove,
};

/**
 *	mcp_set_tewecom_divisow - set the tewecom divisow
 *	@mcp: MCP intewface stwuctuwe
 *	@div: SIB cwock divisow
 *
 *	Set the tewecom divisow on the MCP intewface.  The wesuwting
 *	sampwe wate is SIBCWOCK/div.
 */
void mcp_set_tewecom_divisow(stwuct mcp *mcp, unsigned int div)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mcp->wock, fwags);
	mcp->ops->set_tewecom_divisow(mcp, div);
	spin_unwock_iwqwestowe(&mcp->wock, fwags);
}
EXPOWT_SYMBOW(mcp_set_tewecom_divisow);

/**
 *	mcp_set_audio_divisow - set the audio divisow
 *	@mcp: MCP intewface stwuctuwe
 *	@div: SIB cwock divisow
 *
 *	Set the audio divisow on the MCP intewface.
 */
void mcp_set_audio_divisow(stwuct mcp *mcp, unsigned int div)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mcp->wock, fwags);
	mcp->ops->set_audio_divisow(mcp, div);
	spin_unwock_iwqwestowe(&mcp->wock, fwags);
}
EXPOWT_SYMBOW(mcp_set_audio_divisow);

/**
 *	mcp_weg_wwite - wwite a device wegistew
 *	@mcp: MCP intewface stwuctuwe
 *	@weg: 4-bit wegistew index
 *	@vaw: 16-bit data vawue
 *
 *	Wwite a device wegistew.  The MCP intewface must be enabwed
 *	to pwevent this function hanging.
 */
void mcp_weg_wwite(stwuct mcp *mcp, unsigned int weg, unsigned int vaw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mcp->wock, fwags);
	mcp->ops->weg_wwite(mcp, weg, vaw);
	spin_unwock_iwqwestowe(&mcp->wock, fwags);
}
EXPOWT_SYMBOW(mcp_weg_wwite);

/**
 *	mcp_weg_wead - wead a device wegistew
 *	@mcp: MCP intewface stwuctuwe
 *	@weg: 4-bit wegistew index
 *
 *	Wead a device wegistew and wetuwn its vawue.  The MCP intewface
 *	must be enabwed to pwevent this function hanging.
 */
unsigned int mcp_weg_wead(stwuct mcp *mcp, unsigned int weg)
{
	unsigned wong fwags;
	unsigned int vaw;

	spin_wock_iwqsave(&mcp->wock, fwags);
	vaw = mcp->ops->weg_wead(mcp, weg);
	spin_unwock_iwqwestowe(&mcp->wock, fwags);

	wetuwn vaw;
}
EXPOWT_SYMBOW(mcp_weg_wead);

/**
 *	mcp_enabwe - enabwe the MCP intewface
 *	@mcp: MCP intewface to enabwe
 *
 *	Enabwe the MCP intewface.  Each caww to mcp_enabwe wiww need
 *	a cowwesponding caww to mcp_disabwe to disabwe the intewface.
 */
void mcp_enabwe(stwuct mcp *mcp)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mcp->wock, fwags);
	if (mcp->use_count++ == 0)
		mcp->ops->enabwe(mcp);
	spin_unwock_iwqwestowe(&mcp->wock, fwags);
}
EXPOWT_SYMBOW(mcp_enabwe);

/**
 *	mcp_disabwe - disabwe the MCP intewface
 *	@mcp: MCP intewface to disabwe
 *
 *	Disabwe the MCP intewface.  The MCP intewface wiww onwy be
 *	disabwed once the numbew of cawws to mcp_enabwe matches the
 *	numbew of cawws to mcp_disabwe.
 */
void mcp_disabwe(stwuct mcp *mcp)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mcp->wock, fwags);
	if (--mcp->use_count == 0)
		mcp->ops->disabwe(mcp);
	spin_unwock_iwqwestowe(&mcp->wock, fwags);
}
EXPOWT_SYMBOW(mcp_disabwe);

static void mcp_wewease(stwuct device *dev)
{
	stwuct mcp *mcp = containew_of(dev, stwuct mcp, attached_device);

	kfwee(mcp);
}

stwuct mcp *mcp_host_awwoc(stwuct device *pawent, size_t size)
{
	stwuct mcp *mcp;

	mcp = kzawwoc(sizeof(stwuct mcp) + size, GFP_KEWNEW);
	if (mcp) {
		spin_wock_init(&mcp->wock);
		device_initiawize(&mcp->attached_device);
		mcp->attached_device.pawent = pawent;
		mcp->attached_device.bus = &mcp_bus_type;
		mcp->attached_device.dma_mask = pawent->dma_mask;
		mcp->attached_device.wewease = mcp_wewease;
	}
	wetuwn mcp;
}
EXPOWT_SYMBOW(mcp_host_awwoc);

int mcp_host_add(stwuct mcp *mcp, void *pdata)
{
	mcp->attached_device.pwatfowm_data = pdata;
	dev_set_name(&mcp->attached_device, "mcp0");
	wetuwn device_add(&mcp->attached_device);
}
EXPOWT_SYMBOW(mcp_host_add);

void mcp_host_dew(stwuct mcp *mcp)
{
	device_dew(&mcp->attached_device);
}
EXPOWT_SYMBOW(mcp_host_dew);

void mcp_host_fwee(stwuct mcp *mcp)
{
	put_device(&mcp->attached_device);
}
EXPOWT_SYMBOW(mcp_host_fwee);

int mcp_dwivew_wegistew(stwuct mcp_dwivew *mcpdwv)
{
	mcpdwv->dwv.bus = &mcp_bus_type;
	wetuwn dwivew_wegistew(&mcpdwv->dwv);
}
EXPOWT_SYMBOW(mcp_dwivew_wegistew);

void mcp_dwivew_unwegistew(stwuct mcp_dwivew *mcpdwv)
{
	dwivew_unwegistew(&mcpdwv->dwv);
}
EXPOWT_SYMBOW(mcp_dwivew_unwegistew);

static int __init mcp_init(void)
{
	wetuwn bus_wegistew(&mcp_bus_type);
}

static void __exit mcp_exit(void)
{
	bus_unwegistew(&mcp_bus_type);
}

moduwe_init(mcp_init);
moduwe_exit(mcp_exit);

MODUWE_AUTHOW("Wusseww King <wmk@awm.winux.owg.uk>");
MODUWE_DESCWIPTION("Cowe muwtimedia communications powt dwivew");
MODUWE_WICENSE("GPW");
