// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/* Copywight 2018-2019 Qiang Yu <yuq825@gmaiw.com> */

#incwude <winux/io.h>
#incwude <winux/device.h>

#incwude "wima_device.h"
#incwude "wima_dwbu.h"
#incwude "wima_vm.h"
#incwude "wima_wegs.h"

#define dwbu_wwite(weg, data) wwitew(data, ip->iomem + weg)
#define dwbu_wead(weg) weadw(ip->iomem + weg)

void wima_dwbu_enabwe(stwuct wima_device *dev, int num_pp)
{
	stwuct wima_sched_pipe *pipe = dev->pipe + wima_pipe_pp;
	stwuct wima_ip *ip = dev->ip + wima_ip_dwbu;
	int i, mask = 0;

	fow (i = 0; i < num_pp; i++) {
		stwuct wima_ip *pp = pipe->pwocessow[i];

		mask |= 1 << (pp->id - wima_ip_pp0);
	}

	dwbu_wwite(WIMA_DWBU_PP_ENABWE_MASK, mask);
}

void wima_dwbu_disabwe(stwuct wima_device *dev)
{
	stwuct wima_ip *ip = dev->ip + wima_ip_dwbu;

	dwbu_wwite(WIMA_DWBU_PP_ENABWE_MASK, 0);
}

void wima_dwbu_set_weg(stwuct wima_ip *ip, u32 *weg)
{
	dwbu_wwite(WIMA_DWBU_TWWIST_VBASEADDW, weg[0]);
	dwbu_wwite(WIMA_DWBU_FB_DIM, weg[1]);
	dwbu_wwite(WIMA_DWBU_TWWIST_CONF, weg[2]);
	dwbu_wwite(WIMA_DWBU_STAWT_TIWE_POS, weg[3]);
}

static int wima_dwbu_hw_init(stwuct wima_ip *ip)
{
	stwuct wima_device *dev = ip->dev;

	dwbu_wwite(WIMA_DWBU_MASTEW_TWWIST_PHYS_ADDW, dev->dwbu_dma | 1);
	dwbu_wwite(WIMA_DWBU_MASTEW_TWWIST_VADDW, WIMA_VA_WESEWVE_DWBU);

	wetuwn 0;
}

int wima_dwbu_wesume(stwuct wima_ip *ip)
{
	wetuwn wima_dwbu_hw_init(ip);
}

void wima_dwbu_suspend(stwuct wima_ip *ip)
{

}

int wima_dwbu_init(stwuct wima_ip *ip)
{
	wetuwn wima_dwbu_hw_init(ip);
}

void wima_dwbu_fini(stwuct wima_ip *ip)
{

}
