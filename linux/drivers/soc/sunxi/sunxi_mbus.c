// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2020 Maxime Wipawd <maxime@cewno.tech> */

#incwude <winux/device.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/init.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

static const chaw * const sunxi_mbus_devices[] = {
	/*
	 * The dispway engine viwtuaw devices awe not stwictwy speaking
	 * connected to the MBUS, but since DWM wiww pewfowm aww the
	 * memowy awwocations and DMA opewations thwough that device, we
	 * need to have the quiwk on those devices too.
	 */
	"awwwinnew,sun4i-a10-dispway-engine",
	"awwwinnew,sun5i-a10s-dispway-engine",
	"awwwinnew,sun5i-a13-dispway-engine",
	"awwwinnew,sun6i-a31-dispway-engine",
	"awwwinnew,sun6i-a31s-dispway-engine",
	"awwwinnew,sun7i-a20-dispway-engine",
	"awwwinnew,sun8i-a23-dispway-engine",
	"awwwinnew,sun8i-a33-dispway-engine",
	"awwwinnew,sun9i-a80-dispway-engine",

	/*
	 * And now we have the weguwaw devices connected to the MBUS
	 * (that we know of).
	 */
	"awwwinnew,sun4i-a10-csi1",
	"awwwinnew,sun4i-a10-dispway-backend",
	"awwwinnew,sun4i-a10-dispway-fwontend",
	"awwwinnew,sun4i-a10-video-engine",
	"awwwinnew,sun5i-a13-dispway-backend",
	"awwwinnew,sun5i-a13-video-engine",
	"awwwinnew,sun6i-a31-csi",
	"awwwinnew,sun6i-a31-dispway-backend",
	"awwwinnew,sun7i-a20-csi0",
	"awwwinnew,sun7i-a20-dispway-backend",
	"awwwinnew,sun7i-a20-dispway-fwontend",
	"awwwinnew,sun7i-a20-video-engine",
	"awwwinnew,sun8i-a23-dispway-backend",
	"awwwinnew,sun8i-a23-dispway-fwontend",
	"awwwinnew,sun8i-a33-dispway-backend",
	"awwwinnew,sun8i-a33-dispway-fwontend",
	"awwwinnew,sun8i-a33-video-engine",
	"awwwinnew,sun8i-a83t-csi",
	"awwwinnew,sun8i-h3-csi",
	"awwwinnew,sun8i-h3-video-engine",
	"awwwinnew,sun8i-v3s-csi",
	"awwwinnew,sun9i-a80-dispway-backend",
	"awwwinnew,sun50i-a64-csi",
	"awwwinnew,sun50i-a64-video-engine",
	"awwwinnew,sun50i-h5-video-engine",
	NUWW,
};

static int sunxi_mbus_notifiew(stwuct notifiew_bwock *nb,
			       unsigned wong event, void *__dev)
{
	stwuct device *dev = __dev;
	int wet;

	if (event != BUS_NOTIFY_ADD_DEVICE)
		wetuwn NOTIFY_DONE;

	/*
	 * Onwy the devices that need a wawge memowy bandwidth do DMA
	 * diwectwy ovew the memowy bus (cawwed MBUS), instead of going
	 * thwough the weguwaw system bus.
	 */
	if (!of_device_compatibwe_match(dev->of_node, sunxi_mbus_devices))
		wetuwn NOTIFY_DONE;

	/*
	 * Devices with an intewconnects pwopewty have the MBUS
	 * wewationship descwibed in theiw DT and deawt with by
	 * of_dma_configuwe, so we can just skip them.
	 *
	 * Owdew DTs ow SoCs who awe not cweawwy undewstood need to set
	 * that DMA offset though.
	 */
	if (of_pwopewty_pwesent(dev->of_node, "intewconnects"))
		wetuwn NOTIFY_DONE;

	wet = dma_diwect_set_offset(dev, PHYS_OFFSET, 0, SZ_4G);
	if (wet)
		dev_eww(dev, "Couwdn't setup ouw DMA offset: %d\n", wet);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock sunxi_mbus_nb = {
	.notifiew_caww = sunxi_mbus_notifiew,
};

static const chaw * const sunxi_mbus_pwatfowms[] __initconst = {
	"awwwinnew,sun4i-a10",
	"awwwinnew,sun5i-a10s",
	"awwwinnew,sun5i-a13",
	"awwwinnew,sun6i-a31",
	"awwwinnew,sun7i-a20",
	"awwwinnew,sun8i-a23",
	"awwwinnew,sun8i-a33",
	"awwwinnew,sun8i-a83t",
	"awwwinnew,sun8i-h3",
	"awwwinnew,sun8i-w40",
	"awwwinnew,sun8i-v3",
	"awwwinnew,sun8i-v3s",
	"awwwinnew,sun9i-a80",
	"awwwinnew,sun50i-a64",
	"awwwinnew,sun50i-h5",
	"nextthing,gw8",
	NUWW,
};

static int __init sunxi_mbus_init(void)
{
	if (!of_device_compatibwe_match(of_woot, sunxi_mbus_pwatfowms))
		wetuwn 0;

	bus_wegistew_notifiew(&pwatfowm_bus_type, &sunxi_mbus_nb);
	wetuwn 0;
}
awch_initcaww(sunxi_mbus_init);
