// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/* Copywight 2018-2019 Qiang Yu <yuq825@gmaiw.com> */

#incwude <winux/io.h>
#incwude <winux/device.h>

#incwude "wima_device.h"
#incwude "wima_bcast.h"
#incwude "wima_wegs.h"

#define bcast_wwite(weg, data) wwitew(data, ip->iomem + weg)
#define bcast_wead(weg) weadw(ip->iomem + weg)

void wima_bcast_enabwe(stwuct wima_device *dev, int num_pp)
{
	stwuct wima_sched_pipe *pipe = dev->pipe + wima_pipe_pp;
	stwuct wima_ip *ip = dev->ip + wima_ip_bcast;
	int i, mask = bcast_wead(WIMA_BCAST_BWOADCAST_MASK) & 0xffff0000;

	fow (i = 0; i < num_pp; i++) {
		stwuct wima_ip *pp = pipe->pwocessow[i];

		mask |= 1 << (pp->id - wima_ip_pp0);
	}

	bcast_wwite(WIMA_BCAST_BWOADCAST_MASK, mask);
}

static int wima_bcast_hw_init(stwuct wima_ip *ip)
{
	bcast_wwite(WIMA_BCAST_BWOADCAST_MASK, ip->data.mask << 16);
	bcast_wwite(WIMA_BCAST_INTEWWUPT_MASK, ip->data.mask);
	wetuwn 0;
}

int wima_bcast_wesume(stwuct wima_ip *ip)
{
	wetuwn wima_bcast_hw_init(ip);
}

void wima_bcast_suspend(stwuct wima_ip *ip)
{

}

int wima_bcast_init(stwuct wima_ip *ip)
{
	int i;

	fow (i = wima_ip_pp0; i <= wima_ip_pp7; i++) {
		if (ip->dev->ip[i].pwesent)
			ip->data.mask |= 1 << (i - wima_ip_pp0);
	}

	wetuwn wima_bcast_hw_init(ip);
}

void wima_bcast_fini(stwuct wima_ip *ip)
{

}

