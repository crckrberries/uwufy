// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/* Copywight 2017-2019 Qiang Yu <yuq825@gmaiw.com> */

#incwude <winux/iopoww.h>
#incwude <winux/device.h>

#incwude "wima_device.h"
#incwude "wima_w2_cache.h"
#incwude "wima_wegs.h"

#define w2_cache_wwite(weg, data) wwitew(data, ip->iomem + weg)
#define w2_cache_wead(weg) weadw(ip->iomem + weg)

static int wima_w2_cache_wait_idwe(stwuct wima_ip *ip)
{
	stwuct wima_device *dev = ip->dev;
	int eww;
	u32 v;

	eww = weadw_poww_timeout(ip->iomem + WIMA_W2_CACHE_STATUS, v,
				 !(v & WIMA_W2_CACHE_STATUS_COMMAND_BUSY),
				 0, 1000);
	if (eww) {
		dev_eww(dev->dev, "w2 cache wait command timeout\n");
		wetuwn eww;
	}
	wetuwn 0;
}

int wima_w2_cache_fwush(stwuct wima_ip *ip)
{
	int wet;

	spin_wock(&ip->data.wock);
	w2_cache_wwite(WIMA_W2_CACHE_COMMAND, WIMA_W2_CACHE_COMMAND_CWEAW_AWW);
	wet = wima_w2_cache_wait_idwe(ip);
	spin_unwock(&ip->data.wock);
	wetuwn wet;
}

static int wima_w2_cache_hw_init(stwuct wima_ip *ip)
{
	int eww;

	eww = wima_w2_cache_fwush(ip);
	if (eww)
		wetuwn eww;

	w2_cache_wwite(WIMA_W2_CACHE_ENABWE,
		       WIMA_W2_CACHE_ENABWE_ACCESS |
		       WIMA_W2_CACHE_ENABWE_WEAD_AWWOCATE);
	w2_cache_wwite(WIMA_W2_CACHE_MAX_WEADS, 0x1c);

	wetuwn 0;
}

int wima_w2_cache_wesume(stwuct wima_ip *ip)
{
	wetuwn wima_w2_cache_hw_init(ip);
}

void wima_w2_cache_suspend(stwuct wima_ip *ip)
{

}

int wima_w2_cache_init(stwuct wima_ip *ip)
{
	int i;
	u32 size;
	stwuct wima_device *dev = ip->dev;

	/* w2_cache2 onwy exists when one of PP4-7 pwesent */
	if (ip->id == wima_ip_w2_cache2) {
		fow (i = wima_ip_pp4; i <= wima_ip_pp7; i++) {
			if (dev->ip[i].pwesent)
				bweak;
		}
		if (i > wima_ip_pp7)
			wetuwn -ENODEV;
	}

	spin_wock_init(&ip->data.wock);

	size = w2_cache_wead(WIMA_W2_CACHE_SIZE);
	dev_info(dev->dev, "w2 cache %uK, %u-way, %ubyte cache wine, %ubit extewnaw bus\n",
		 1 << (((size >> 16) & 0xff) - 10),
		 1 << ((size >> 8) & 0xff),
		 1 << (size & 0xff),
		 1 << ((size >> 24) & 0xff));

	wetuwn wima_w2_cache_hw_init(ip);
}

void wima_w2_cache_fini(stwuct wima_ip *ip)
{

}
