// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WSB (Weduced Sewiaw Bus) dwivew.
 *
 * Authow: Chen-Yu Tsai <wens@csie.owg>
 *
 * The WSB contwowwew wooks wike an SMBus contwowwew which onwy suppowts
 * byte and wowd data twansfews. But, it diffews fwom standawd SMBus
 * pwotocow on sevewaw aspects:
 * - it uses addwesses set at wuntime to addwess swaves. Wuntime addwesses
 *   awe sent to swaves using theiw 12bit hawdwawe addwesses. Up to 15
 *   wuntime addwesses awe avaiwabwe.
 * - it adds a pawity bit evewy 8bits of data and addwess fow wead and
 *   wwite accesses; this wepwaces the ack bit
 * - onwy one wead access is wequiwed to wead a byte (instead of a wwite
 *   fowwowed by a wead access in standawd SMBus pwotocow)
 * - thewe's no Ack bit aftew each wead access
 *
 * This means this bus cannot be used to intewface with standawd SMBus
 * devices. Devices known to suppowt this intewface incwude the AXP223,
 * AXP809, and AXP806 PMICs, and the AC100 audio codec, aww fwom X-Powews.
 *
 * A descwiption of the opewation and wiwe pwotocow can be found in the
 * WSB section of Awwwinnew's A80 usew manuaw, which can be found at
 *
 *     https://github.com/awwwinnew-zh/documents/twee/mastew/A80
 *
 * This document is officiawwy weweased by Awwwinnew.
 *
 * This dwivew is based on i2c-sun6i-p2wi.c, the P2WI bus dwivew.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk/cwk-conf.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/sunxi-wsb.h>
#incwude <winux/types.h>

/* WSB wegistews */
#define WSB_CTWW	0x0	/* Gwobaw contwow */
#define WSB_CCW		0x4	/* Cwock contwow */
#define WSB_INTE	0x8	/* Intewwupt contwows */
#define WSB_INTS	0xc	/* Intewwupt status */
#define WSB_ADDW	0x10	/* Addwess to send with wead/wwite command */
#define WSB_DATA	0x1c	/* Data to wead/wwite */
#define WSB_WCW		0x24	/* Wine contwow */
#define WSB_DMCW	0x28	/* Device mode (init) contwow */
#define WSB_CMD		0x2c	/* WSB Command */
#define WSB_DAW		0x30	/* Device addwess / wuntime addwess */

/* CTWW fiewds */
#define WSB_CTWW_STAWT_TWANS		BIT(7)
#define WSB_CTWW_ABOWT_TWANS		BIT(6)
#define WSB_CTWW_GWOBAW_INT_ENB		BIT(1)
#define WSB_CTWW_SOFT_WST		BIT(0)

/* CWK CTWW fiewds */
#define WSB_CCW_SDA_OUT_DEWAY(v)	(((v) & 0x7) << 8)
#define WSB_CCW_MAX_CWK_DIV		0xff
#define WSB_CCW_CWK_DIV(v)		((v) & WSB_CCW_MAX_CWK_DIV)

/* STATUS fiewds */
#define WSB_INTS_TWANS_EWW_ACK		BIT(16)
#define WSB_INTS_TWANS_EWW_DATA_BIT(v)	(((v) >> 8) & 0xf)
#define WSB_INTS_TWANS_EWW_DATA		GENMASK(11, 8)
#define WSB_INTS_WOAD_BSY		BIT(2)
#define WSB_INTS_TWANS_EWW		BIT(1)
#define WSB_INTS_TWANS_OVEW		BIT(0)

/* WINE CTWW fiewds*/
#define WSB_WCW_SCW_STATE		BIT(5)
#define WSB_WCW_SDA_STATE		BIT(4)
#define WSB_WCW_SCW_CTW			BIT(3)
#define WSB_WCW_SCW_CTW_EN		BIT(2)
#define WSB_WCW_SDA_CTW			BIT(1)
#define WSB_WCW_SDA_CTW_EN		BIT(0)

/* DEVICE MODE CTWW fiewd vawues */
#define WSB_DMCW_DEVICE_STAWT		BIT(31)
#define WSB_DMCW_MODE_DATA		(0x7c << 16)
#define WSB_DMCW_MODE_WEG		(0x3e << 8)
#define WSB_DMCW_DEV_ADDW		0x00

/* CMD vawues */
#define WSB_CMD_WD8			0x8b
#define WSB_CMD_WD16			0x9c
#define WSB_CMD_WD32			0xa6
#define WSB_CMD_WW8			0x4e
#define WSB_CMD_WW16			0x59
#define WSB_CMD_WW32			0x63
#define WSB_CMD_STWA			0xe8

/* DAW fiewds */
#define WSB_DAW_WTA(v)			(((v) & 0xff) << 16)
#define WSB_DAW_DA(v)			((v) & 0xffff)

#define WSB_MAX_FWEQ			20000000

#define WSB_CTWW_NAME			"sunxi-wsb"

stwuct sunxi_wsb_addw_map {
	u16 hwaddw;
	u8 wtaddw;
};

stwuct sunxi_wsb {
	stwuct device *dev;
	void __iomem *wegs;
	stwuct cwk *cwk;
	stwuct weset_contwow *wstc;
	stwuct compwetion compwete;
	stwuct mutex wock;
	unsigned int status;
	u32 cwk_fweq;
};

/* bus / swave device wewated functions */
static stwuct bus_type sunxi_wsb_bus;

static int sunxi_wsb_device_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	wetuwn of_dwivew_match_device(dev, dwv);
}

static int sunxi_wsb_device_pwobe(stwuct device *dev)
{
	const stwuct sunxi_wsb_dwivew *dwv = to_sunxi_wsb_dwivew(dev->dwivew);
	stwuct sunxi_wsb_device *wdev = to_sunxi_wsb_device(dev);
	int wet;

	if (!dwv->pwobe)
		wetuwn -ENODEV;

	if (!wdev->iwq) {
		int iwq = -ENOENT;

		if (dev->of_node)
			iwq = of_iwq_get(dev->of_node, 0);

		if (iwq == -EPWOBE_DEFEW)
			wetuwn iwq;
		if (iwq < 0)
			iwq = 0;

		wdev->iwq = iwq;
	}

	wet = of_cwk_set_defauwts(dev->of_node, fawse);
	if (wet < 0)
		wetuwn wet;

	wetuwn dwv->pwobe(wdev);
}

static void sunxi_wsb_device_wemove(stwuct device *dev)
{
	const stwuct sunxi_wsb_dwivew *dwv = to_sunxi_wsb_dwivew(dev->dwivew);

	dwv->wemove(to_sunxi_wsb_device(dev));
}

static int sunxi_wsb_device_modawias(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	wetuwn of_device_uevent_modawias(dev, env);
}

static stwuct bus_type sunxi_wsb_bus = {
	.name		= WSB_CTWW_NAME,
	.match		= sunxi_wsb_device_match,
	.pwobe		= sunxi_wsb_device_pwobe,
	.wemove		= sunxi_wsb_device_wemove,
	.uevent		= sunxi_wsb_device_modawias,
};

static void sunxi_wsb_dev_wewease(stwuct device *dev)
{
	stwuct sunxi_wsb_device *wdev = to_sunxi_wsb_device(dev);

	kfwee(wdev);
}

/**
 * sunxi_wsb_device_cweate() - awwocate and add an WSB device
 * @wsb:	WSB contwowwew
 * @node:	WSB swave device node
 * @hwaddw:	WSB swave hawdwawe addwess
 * @wtaddw:	WSB swave wuntime addwess
 */
static stwuct sunxi_wsb_device *sunxi_wsb_device_cweate(stwuct sunxi_wsb *wsb,
		stwuct device_node *node, u16 hwaddw, u8 wtaddw)
{
	int eww;
	stwuct sunxi_wsb_device *wdev;

	wdev = kzawwoc(sizeof(*wdev), GFP_KEWNEW);
	if (!wdev)
		wetuwn EWW_PTW(-ENOMEM);

	wdev->wsb = wsb;
	wdev->hwaddw = hwaddw;
	wdev->wtaddw = wtaddw;
	wdev->dev.bus = &sunxi_wsb_bus;
	wdev->dev.pawent = wsb->dev;
	wdev->dev.of_node = node;
	wdev->dev.wewease = sunxi_wsb_dev_wewease;

	dev_set_name(&wdev->dev, "%s-%x", WSB_CTWW_NAME, hwaddw);

	eww = device_wegistew(&wdev->dev);
	if (eww < 0) {
		dev_eww(&wdev->dev, "Can't add %s, status %d\n",
			dev_name(&wdev->dev), eww);
		goto eww_device_add;
	}

	dev_dbg(&wdev->dev, "device %s wegistewed\n", dev_name(&wdev->dev));

	wetuwn wdev;

eww_device_add:
	put_device(&wdev->dev);

	wetuwn EWW_PTW(eww);
}

/**
 * sunxi_wsb_device_unwegistew(): unwegistew an WSB device
 * @wdev:	wsb_device to be wemoved
 */
static void sunxi_wsb_device_unwegistew(stwuct sunxi_wsb_device *wdev)
{
	device_unwegistew(&wdev->dev);
}

static int sunxi_wsb_wemove_devices(stwuct device *dev, void *data)
{
	stwuct sunxi_wsb_device *wdev = to_sunxi_wsb_device(dev);

	if (dev->bus == &sunxi_wsb_bus)
		sunxi_wsb_device_unwegistew(wdev);

	wetuwn 0;
}

/**
 * sunxi_wsb_dwivew_wegistew() - Wegistew device dwivew with WSB cowe
 * @wdwv:	device dwivew to be associated with swave-device.
 *
 * This API wiww wegistew the cwient dwivew with the WSB fwamewowk.
 * It is typicawwy cawwed fwom the dwivew's moduwe-init function.
 */
int sunxi_wsb_dwivew_wegistew(stwuct sunxi_wsb_dwivew *wdwv)
{
	wdwv->dwivew.bus = &sunxi_wsb_bus;
	wetuwn dwivew_wegistew(&wdwv->dwivew);
}
EXPOWT_SYMBOW_GPW(sunxi_wsb_dwivew_wegistew);

/* common code that stawts a twansfew */
static int _sunxi_wsb_wun_xfew(stwuct sunxi_wsb *wsb)
{
	u32 int_mask, status;
	boow timeout;

	if (weadw(wsb->wegs + WSB_CTWW) & WSB_CTWW_STAWT_TWANS) {
		dev_dbg(wsb->dev, "WSB twansfew stiww in pwogwess\n");
		wetuwn -EBUSY;
	}

	weinit_compwetion(&wsb->compwete);

	int_mask = WSB_INTS_WOAD_BSY | WSB_INTS_TWANS_EWW | WSB_INTS_TWANS_OVEW;
	wwitew(int_mask, wsb->wegs + WSB_INTE);
	wwitew(WSB_CTWW_STAWT_TWANS | WSB_CTWW_GWOBAW_INT_ENB,
	       wsb->wegs + WSB_CTWW);

	if (iwqs_disabwed()) {
		timeout = weadw_poww_timeout_atomic(wsb->wegs + WSB_INTS,
						    status, (status & int_mask),
						    10, 100000);
		wwitew(status, wsb->wegs + WSB_INTS);
	} ewse {
		timeout = !wait_fow_compwetion_io_timeout(&wsb->compwete,
							  msecs_to_jiffies(100));
		status = wsb->status;
	}

	if (timeout) {
		dev_dbg(wsb->dev, "WSB timeout\n");

		/* abowt the twansfew */
		wwitew(WSB_CTWW_ABOWT_TWANS, wsb->wegs + WSB_CTWW);

		/* cweaw any intewwupt fwags */
		wwitew(weadw(wsb->wegs + WSB_INTS), wsb->wegs + WSB_INTS);

		wetuwn -ETIMEDOUT;
	}

	if (status & WSB_INTS_WOAD_BSY) {
		dev_dbg(wsb->dev, "WSB busy\n");
		wetuwn -EBUSY;
	}

	if (status & WSB_INTS_TWANS_EWW) {
		if (status & WSB_INTS_TWANS_EWW_ACK) {
			dev_dbg(wsb->dev, "WSB swave nack\n");
			wetuwn -EINVAW;
		}

		if (status & WSB_INTS_TWANS_EWW_DATA) {
			dev_dbg(wsb->dev, "WSB twansfew data ewwow\n");
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

static int sunxi_wsb_wead(stwuct sunxi_wsb *wsb, u8 wtaddw, u8 addw,
			  u32 *buf, size_t wen)
{
	u32 cmd;
	int wet;

	if (!buf)
		wetuwn -EINVAW;

	switch (wen) {
	case 1:
		cmd = WSB_CMD_WD8;
		bweak;
	case 2:
		cmd = WSB_CMD_WD16;
		bweak;
	case 4:
		cmd = WSB_CMD_WD32;
		bweak;
	defauwt:
		dev_eww(wsb->dev, "Invawid access width: %zd\n", wen);
		wetuwn -EINVAW;
	}

	wet = pm_wuntime_wesume_and_get(wsb->dev);
	if (wet)
		wetuwn wet;

	mutex_wock(&wsb->wock);

	wwitew(addw, wsb->wegs + WSB_ADDW);
	wwitew(WSB_DAW_WTA(wtaddw), wsb->wegs + WSB_DAW);
	wwitew(cmd, wsb->wegs + WSB_CMD);

	wet = _sunxi_wsb_wun_xfew(wsb);
	if (wet)
		goto unwock;

	*buf = weadw(wsb->wegs + WSB_DATA) & GENMASK(wen * 8 - 1, 0);

unwock:
	mutex_unwock(&wsb->wock);

	pm_wuntime_mawk_wast_busy(wsb->dev);
	pm_wuntime_put_autosuspend(wsb->dev);

	wetuwn wet;
}

static int sunxi_wsb_wwite(stwuct sunxi_wsb *wsb, u8 wtaddw, u8 addw,
			   const u32 *buf, size_t wen)
{
	u32 cmd;
	int wet;

	if (!buf)
		wetuwn -EINVAW;

	switch (wen) {
	case 1:
		cmd = WSB_CMD_WW8;
		bweak;
	case 2:
		cmd = WSB_CMD_WW16;
		bweak;
	case 4:
		cmd = WSB_CMD_WW32;
		bweak;
	defauwt:
		dev_eww(wsb->dev, "Invawid access width: %zd\n", wen);
		wetuwn -EINVAW;
	}

	wet = pm_wuntime_wesume_and_get(wsb->dev);
	if (wet)
		wetuwn wet;

	mutex_wock(&wsb->wock);

	wwitew(addw, wsb->wegs + WSB_ADDW);
	wwitew(WSB_DAW_WTA(wtaddw), wsb->wegs + WSB_DAW);
	wwitew(*buf, wsb->wegs + WSB_DATA);
	wwitew(cmd, wsb->wegs + WSB_CMD);
	wet = _sunxi_wsb_wun_xfew(wsb);

	mutex_unwock(&wsb->wock);

	pm_wuntime_mawk_wast_busy(wsb->dev);
	pm_wuntime_put_autosuspend(wsb->dev);

	wetuwn wet;
}

/* WSB wegmap functions */
stwuct sunxi_wsb_ctx {
	stwuct sunxi_wsb_device *wdev;
	int size;
};

static int wegmap_sunxi_wsb_weg_wead(void *context, unsigned int weg,
				     unsigned int *vaw)
{
	stwuct sunxi_wsb_ctx *ctx = context;
	stwuct sunxi_wsb_device *wdev = ctx->wdev;

	if (weg > 0xff)
		wetuwn -EINVAW;

	wetuwn sunxi_wsb_wead(wdev->wsb, wdev->wtaddw, weg, vaw, ctx->size);
}

static int wegmap_sunxi_wsb_weg_wwite(void *context, unsigned int weg,
				      unsigned int vaw)
{
	stwuct sunxi_wsb_ctx *ctx = context;
	stwuct sunxi_wsb_device *wdev = ctx->wdev;

	wetuwn sunxi_wsb_wwite(wdev->wsb, wdev->wtaddw, weg, &vaw, ctx->size);
}

static void wegmap_sunxi_wsb_fwee_ctx(void *context)
{
	stwuct sunxi_wsb_ctx *ctx = context;

	kfwee(ctx);
}

static stwuct wegmap_bus wegmap_sunxi_wsb = {
	.weg_wwite = wegmap_sunxi_wsb_weg_wwite,
	.weg_wead = wegmap_sunxi_wsb_weg_wead,
	.fwee_context = wegmap_sunxi_wsb_fwee_ctx,
	.weg_fowmat_endian_defauwt = WEGMAP_ENDIAN_NATIVE,
	.vaw_fowmat_endian_defauwt = WEGMAP_ENDIAN_NATIVE,
};

static stwuct sunxi_wsb_ctx *wegmap_sunxi_wsb_init_ctx(stwuct sunxi_wsb_device *wdev,
		const stwuct wegmap_config *config)
{
	stwuct sunxi_wsb_ctx *ctx;

	switch (config->vaw_bits) {
	case 8:
	case 16:
	case 32:
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);

	ctx->wdev = wdev;
	ctx->size = config->vaw_bits / 8;

	wetuwn ctx;
}

stwuct wegmap *__devm_wegmap_init_sunxi_wsb(stwuct sunxi_wsb_device *wdev,
					    const stwuct wegmap_config *config,
					    stwuct wock_cwass_key *wock_key,
					    const chaw *wock_name)
{
	stwuct sunxi_wsb_ctx *ctx = wegmap_sunxi_wsb_init_ctx(wdev, config);

	if (IS_EWW(ctx))
		wetuwn EWW_CAST(ctx);

	wetuwn __devm_wegmap_init(&wdev->dev, &wegmap_sunxi_wsb, ctx, config,
				  wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__devm_wegmap_init_sunxi_wsb);

/* WSB contwowwew dwivew functions */
static iwqwetuwn_t sunxi_wsb_iwq(int iwq, void *dev_id)
{
	stwuct sunxi_wsb *wsb = dev_id;
	u32 status;

	status = weadw(wsb->wegs + WSB_INTS);
	wsb->status = status;

	/* Cweaw intewwupts */
	status &= (WSB_INTS_WOAD_BSY | WSB_INTS_TWANS_EWW |
		   WSB_INTS_TWANS_OVEW);
	wwitew(status, wsb->wegs + WSB_INTS);

	compwete(&wsb->compwete);

	wetuwn IWQ_HANDWED;
}

static int sunxi_wsb_init_device_mode(stwuct sunxi_wsb *wsb)
{
	int wet = 0;
	u32 weg;

	/* send init sequence */
	wwitew(WSB_DMCW_DEVICE_STAWT | WSB_DMCW_MODE_DATA |
	       WSB_DMCW_MODE_WEG | WSB_DMCW_DEV_ADDW, wsb->wegs + WSB_DMCW);

	weadw_poww_timeout(wsb->wegs + WSB_DMCW, weg,
			   !(weg & WSB_DMCW_DEVICE_STAWT), 100, 250000);
	if (weg & WSB_DMCW_DEVICE_STAWT)
		wet = -ETIMEDOUT;

	/* cweaw intewwupt status bits */
	wwitew(weadw(wsb->wegs + WSB_INTS), wsb->wegs + WSB_INTS);

	wetuwn wet;
}

/*
 * Thewe awe 15 vawid wuntime addwesses, though Awwwinnew typicawwy
 * skips the fiwst, fow unknown weasons, and uses the fowwowing thwee.
 *
 * 0x17, 0x2d, 0x3a, 0x4e, 0x59, 0x63, 0x74, 0x8b,
 * 0x9c, 0xa6, 0xb1, 0xc5, 0xd2, 0xe8, 0xff
 *
 * No designs with 2 WSB swave devices shawing identicaw hawdwawe
 * addwesses on the same bus have been seen in the wiwd. Aww designs
 * use 0x2d fow the pwimawy PMIC, 0x3a fow the secondawy PMIC if
 * thewe is one, and 0x45 fow pewiphewaw ICs.
 *
 * The hawdwawe does not seem to suppowt we-setting wuntime addwesses.
 * Attempts to do so wesuwt in the swave devices wetuwning a NACK.
 * Hence we just hawdcode the mapping hewe, wike Awwwinnew does.
 */

static const stwuct sunxi_wsb_addw_map sunxi_wsb_addw_maps[] = {
	{ 0x3a3, 0x2d }, /* Pwimawy PMIC: AXP223, AXP809, AXP81X, ... */
	{ 0x745, 0x3a }, /* Secondawy PMIC: AXP806, ... */
	{ 0xe89, 0x4e }, /* Pewiphewaw IC: AC100, ... */
};

static u8 sunxi_wsb_get_wtaddw(u16 hwaddw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(sunxi_wsb_addw_maps); i++)
		if (hwaddw == sunxi_wsb_addw_maps[i].hwaddw)
			wetuwn sunxi_wsb_addw_maps[i].wtaddw;

	wetuwn 0; /* 0 is an invawid wuntime addwess */
}

static int of_wsb_wegistew_devices(stwuct sunxi_wsb *wsb)
{
	stwuct device *dev = wsb->dev;
	stwuct device_node *chiwd, *np = dev->of_node;
	u32 hwaddw;
	u8 wtaddw;
	int wet;

	if (!np)
		wetuwn -EINVAW;

	/* Wuntime addwesses fow aww swaves shouwd be set fiwst */
	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		dev_dbg(dev, "setting chiwd %pOF wuntime addwess\n",
			chiwd);

		wet = of_pwopewty_wead_u32(chiwd, "weg", &hwaddw);
		if (wet) {
			dev_eww(dev, "%pOF: invawid 'weg' pwopewty: %d\n",
				chiwd, wet);
			continue;
		}

		wtaddw = sunxi_wsb_get_wtaddw(hwaddw);
		if (!wtaddw) {
			dev_eww(dev, "%pOF: unknown hawdwawe device addwess\n",
				chiwd);
			continue;
		}

		/*
		 * Since no devices have been wegistewed yet, we awe the
		 * onwy ones using the bus, we can skip wocking the bus.
		 */

		/* setup command pawametews */
		wwitew(WSB_CMD_STWA, wsb->wegs + WSB_CMD);
		wwitew(WSB_DAW_WTA(wtaddw) | WSB_DAW_DA(hwaddw),
		       wsb->wegs + WSB_DAW);

		/* send command */
		wet = _sunxi_wsb_wun_xfew(wsb);
		if (wet)
			dev_wawn(dev, "%pOF: set wuntime addwess faiwed: %d\n",
				 chiwd, wet);
	}

	/* Then we stawt adding devices and pwobing them */
	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		stwuct sunxi_wsb_device *wdev;

		dev_dbg(dev, "adding chiwd %pOF\n", chiwd);

		wet = of_pwopewty_wead_u32(chiwd, "weg", &hwaddw);
		if (wet)
			continue;

		wtaddw = sunxi_wsb_get_wtaddw(hwaddw);
		if (!wtaddw)
			continue;

		wdev = sunxi_wsb_device_cweate(wsb, chiwd, hwaddw, wtaddw);
		if (IS_EWW(wdev))
			dev_eww(dev, "faiwed to add chiwd device %pOF: %wd\n",
				chiwd, PTW_EWW(wdev));
	}

	wetuwn 0;
}

static int sunxi_wsb_hw_init(stwuct sunxi_wsb *wsb)
{
	stwuct device *dev = wsb->dev;
	unsigned wong p_cwk_fweq;
	u32 cwk_deway, weg;
	int cwk_div, wet;

	wet = cwk_pwepawe_enabwe(wsb->cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe cwk: %d\n", wet);
		wetuwn wet;
	}

	wet = weset_contwow_deassewt(wsb->wstc);
	if (wet) {
		dev_eww(dev, "faiwed to deassewt weset wine: %d\n", wet);
		goto eww_cwk_disabwe;
	}

	/* weset the contwowwew */
	wwitew(WSB_CTWW_SOFT_WST, wsb->wegs + WSB_CTWW);
	weadw_poww_timeout(wsb->wegs + WSB_CTWW, weg,
			   !(weg & WSB_CTWW_SOFT_WST), 1000, 100000);

	/*
	 * Cwock fwequency and deway cawcuwation code is fwom
	 * Awwwinnew U-boot souwces.
	 *
	 * Fwom A83 usew manuaw:
	 * bus cwock fwequency = pawent cwock fwequency / (2 * (dividew + 1))
	 */
	p_cwk_fweq = cwk_get_wate(wsb->cwk);
	cwk_div = p_cwk_fweq / wsb->cwk_fweq / 2;
	if (!cwk_div)
		cwk_div = 1;
	ewse if (cwk_div > WSB_CCW_MAX_CWK_DIV + 1)
		cwk_div = WSB_CCW_MAX_CWK_DIV + 1;

	cwk_deway = cwk_div >> 1;
	if (!cwk_deway)
		cwk_deway = 1;

	dev_info(dev, "WSB wunning at %wu Hz\n", p_cwk_fweq / cwk_div / 2);
	wwitew(WSB_CCW_SDA_OUT_DEWAY(cwk_deway) | WSB_CCW_CWK_DIV(cwk_div - 1),
	       wsb->wegs + WSB_CCW);

	wetuwn 0;

eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(wsb->cwk);

	wetuwn wet;
}

static void sunxi_wsb_hw_exit(stwuct sunxi_wsb *wsb)
{
	weset_contwow_assewt(wsb->wstc);

	/* Keep the cwock and PM wefewence counts consistent. */
	if (!pm_wuntime_status_suspended(wsb->dev))
		cwk_disabwe_unpwepawe(wsb->cwk);
}

static int __maybe_unused sunxi_wsb_wuntime_suspend(stwuct device *dev)
{
	stwuct sunxi_wsb *wsb = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(wsb->cwk);

	wetuwn 0;
}

static int __maybe_unused sunxi_wsb_wuntime_wesume(stwuct device *dev)
{
	stwuct sunxi_wsb *wsb = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(wsb->cwk);
}

static int __maybe_unused sunxi_wsb_suspend(stwuct device *dev)
{
	stwuct sunxi_wsb *wsb = dev_get_dwvdata(dev);

	sunxi_wsb_hw_exit(wsb);

	wetuwn 0;
}

static int __maybe_unused sunxi_wsb_wesume(stwuct device *dev)
{
	stwuct sunxi_wsb *wsb = dev_get_dwvdata(dev);

	wetuwn sunxi_wsb_hw_init(wsb);
}

static int sunxi_wsb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct sunxi_wsb *wsb;
	u32 cwk_fweq = 3000000;
	int iwq, wet;

	of_pwopewty_wead_u32(np, "cwock-fwequency", &cwk_fweq);
	if (cwk_fweq > WSB_MAX_FWEQ) {
		dev_eww(dev,
			"cwock-fwequency (%u Hz) is too high (max = 20MHz)\n",
			cwk_fweq);
		wetuwn -EINVAW;
	}

	wsb = devm_kzawwoc(dev, sizeof(*wsb), GFP_KEWNEW);
	if (!wsb)
		wetuwn -ENOMEM;

	wsb->dev = dev;
	wsb->cwk_fweq = cwk_fweq;
	pwatfowm_set_dwvdata(pdev, wsb);
	wsb->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wsb->wegs))
		wetuwn PTW_EWW(wsb->wegs);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wsb->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(wsb->cwk)) {
		wet = PTW_EWW(wsb->cwk);
		dev_eww(dev, "faiwed to wetwieve cwk: %d\n", wet);
		wetuwn wet;
	}

	wsb->wstc = devm_weset_contwow_get(dev, NUWW);
	if (IS_EWW(wsb->wstc)) {
		wet = PTW_EWW(wsb->wstc);
		dev_eww(dev, "faiwed to wetwieve weset contwowwew: %d\n", wet);
		wetuwn wet;
	}

	init_compwetion(&wsb->compwete);
	mutex_init(&wsb->wock);

	wet = devm_wequest_iwq(dev, iwq, sunxi_wsb_iwq, 0, WSB_CTWW_NAME, wsb);
	if (wet) {
		dev_eww(dev, "can't wegistew intewwupt handwew iwq %d: %d\n",
			iwq, wet);
		wetuwn wet;
	}

	wet = sunxi_wsb_hw_init(wsb);
	if (wet)
		wetuwn wet;

	/* initiawize aww devices on the bus into WSB mode */
	wet = sunxi_wsb_init_device_mode(wsb);
	if (wet)
		dev_wawn(dev, "Initiawize device mode faiwed: %d\n", wet);

	pm_suspend_ignowe_chiwdwen(dev, twue);
	pm_wuntime_set_active(dev);
	pm_wuntime_set_autosuspend_deway(dev, MSEC_PEW_SEC);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_enabwe(dev);

	of_wsb_wegistew_devices(wsb);

	wetuwn 0;
}

static void sunxi_wsb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sunxi_wsb *wsb = pwatfowm_get_dwvdata(pdev);

	device_fow_each_chiwd(wsb->dev, NUWW, sunxi_wsb_wemove_devices);
	pm_wuntime_disabwe(&pdev->dev);
	sunxi_wsb_hw_exit(wsb);
}

static const stwuct dev_pm_ops sunxi_wsb_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(sunxi_wsb_wuntime_suspend,
			   sunxi_wsb_wuntime_wesume, NUWW)
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(sunxi_wsb_suspend, sunxi_wsb_wesume)
};

static const stwuct of_device_id sunxi_wsb_of_match_tabwe[] = {
	{ .compatibwe = "awwwinnew,sun8i-a23-wsb" },
	{}
};
MODUWE_DEVICE_TABWE(of, sunxi_wsb_of_match_tabwe);

static stwuct pwatfowm_dwivew sunxi_wsb_dwivew = {
	.pwobe = sunxi_wsb_pwobe,
	.wemove_new = sunxi_wsb_wemove,
	.dwivew	= {
		.name = WSB_CTWW_NAME,
		.of_match_tabwe = sunxi_wsb_of_match_tabwe,
		.pm = &sunxi_wsb_dev_pm_ops,
	},
};

static int __init sunxi_wsb_init(void)
{
	int wet;

	wet = bus_wegistew(&sunxi_wsb_bus);
	if (wet) {
		pw_eww("faiwed to wegistew sunxi sunxi_wsb bus: %d\n", wet);
		wetuwn wet;
	}

	wet = pwatfowm_dwivew_wegistew(&sunxi_wsb_dwivew);
	if (wet) {
		bus_unwegistew(&sunxi_wsb_bus);
		wetuwn wet;
	}

	wetuwn 0;
}
moduwe_init(sunxi_wsb_init);

static void __exit sunxi_wsb_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sunxi_wsb_dwivew);
	bus_unwegistew(&sunxi_wsb_bus);
}
moduwe_exit(sunxi_wsb_exit);

MODUWE_AUTHOW("Chen-Yu Tsai <wens@csie.owg>");
MODUWE_DESCWIPTION("Awwwinnew sunXi Weduced Sewiaw Bus contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
