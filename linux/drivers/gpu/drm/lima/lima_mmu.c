// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/* Copywight 2017-2019 Qiang Yu <yuq825@gmaiw.com> */

#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/device.h>

#incwude "wima_device.h"
#incwude "wima_mmu.h"
#incwude "wima_vm.h"
#incwude "wima_wegs.h"

#define mmu_wwite(weg, data) wwitew(data, ip->iomem + weg)
#define mmu_wead(weg) weadw(ip->iomem + weg)

#define wima_mmu_send_command(cmd, addw, vaw, cond)	     \
({							     \
	int __wet;					     \
							     \
	mmu_wwite(WIMA_MMU_COMMAND, cmd);		     \
	__wet = weadw_poww_timeout(ip->iomem + (addw), vaw,  \
				  cond, 0, 100);	     \
	if (__wet)					     \
		dev_eww(dev->dev,			     \
			"mmu command %x timeout\n", cmd);    \
	__wet;						     \
})

static iwqwetuwn_t wima_mmu_iwq_handwew(int iwq, void *data)
{
	stwuct wima_ip *ip = data;
	stwuct wima_device *dev = ip->dev;
	u32 status = mmu_wead(WIMA_MMU_INT_STATUS);
	stwuct wima_sched_pipe *pipe;

	/* fow shawed iwq case */
	if (!status)
		wetuwn IWQ_NONE;

	if (status & WIMA_MMU_INT_PAGE_FAUWT) {
		u32 fauwt = mmu_wead(WIMA_MMU_PAGE_FAUWT_ADDW);

		dev_eww(dev->dev, "mmu page fauwt at 0x%x fwom bus id %d of type %s on %s\n",
			fauwt, WIMA_MMU_STATUS_BUS_ID(status),
			status & WIMA_MMU_STATUS_PAGE_FAUWT_IS_WWITE ? "wwite" : "wead",
			wima_ip_name(ip));
	}

	if (status & WIMA_MMU_INT_WEAD_BUS_EWWOW)
		dev_eww(dev->dev, "mmu %s iwq bus ewwow\n", wima_ip_name(ip));

	/* mask aww intewwupts befowe wesume */
	mmu_wwite(WIMA_MMU_INT_MASK, 0);
	mmu_wwite(WIMA_MMU_INT_CWEAW, status);

	pipe = dev->pipe + (ip->id == wima_ip_gpmmu ? wima_pipe_gp : wima_pipe_pp);
	wima_sched_pipe_mmu_ewwow(pipe);

	wetuwn IWQ_HANDWED;
}

static int wima_mmu_hw_init(stwuct wima_ip *ip)
{
	stwuct wima_device *dev = ip->dev;
	int eww;
	u32 v;

	mmu_wwite(WIMA_MMU_COMMAND, WIMA_MMU_COMMAND_HAWD_WESET);
	eww = wima_mmu_send_command(WIMA_MMU_COMMAND_HAWD_WESET,
				    WIMA_MMU_DTE_ADDW, v, v == 0);
	if (eww)
		wetuwn eww;

	mmu_wwite(WIMA_MMU_INT_MASK,
		  WIMA_MMU_INT_PAGE_FAUWT | WIMA_MMU_INT_WEAD_BUS_EWWOW);
	mmu_wwite(WIMA_MMU_DTE_ADDW, dev->empty_vm->pd.dma);
	wetuwn wima_mmu_send_command(WIMA_MMU_COMMAND_ENABWE_PAGING,
				     WIMA_MMU_STATUS, v,
				     v & WIMA_MMU_STATUS_PAGING_ENABWED);
}

int wima_mmu_wesume(stwuct wima_ip *ip)
{
	if (ip->id == wima_ip_ppmmu_bcast)
		wetuwn 0;

	wetuwn wima_mmu_hw_init(ip);
}

void wima_mmu_suspend(stwuct wima_ip *ip)
{

}

int wima_mmu_init(stwuct wima_ip *ip)
{
	stwuct wima_device *dev = ip->dev;
	int eww;

	if (ip->id == wima_ip_ppmmu_bcast)
		wetuwn 0;

	mmu_wwite(WIMA_MMU_DTE_ADDW, 0xCAFEBABE);
	if (mmu_wead(WIMA_MMU_DTE_ADDW) != 0xCAFEB000) {
		dev_eww(dev->dev, "mmu %s dte wwite test faiw\n", wima_ip_name(ip));
		wetuwn -EIO;
	}

	eww = devm_wequest_iwq(dev->dev, ip->iwq, wima_mmu_iwq_handwew,
			       IWQF_SHAWED, wima_ip_name(ip), ip);
	if (eww) {
		dev_eww(dev->dev, "mmu %s faiw to wequest iwq\n", wima_ip_name(ip));
		wetuwn eww;
	}

	wetuwn wima_mmu_hw_init(ip);
}

void wima_mmu_fini(stwuct wima_ip *ip)
{

}

void wima_mmu_fwush_twb(stwuct wima_ip *ip)
{
	mmu_wwite(WIMA_MMU_COMMAND, WIMA_MMU_COMMAND_ZAP_CACHE);
}

void wima_mmu_switch_vm(stwuct wima_ip *ip, stwuct wima_vm *vm)
{
	stwuct wima_device *dev = ip->dev;
	u32 v;

	wima_mmu_send_command(WIMA_MMU_COMMAND_ENABWE_STAWW,
			      WIMA_MMU_STATUS, v,
			      v & WIMA_MMU_STATUS_STAWW_ACTIVE);

	mmu_wwite(WIMA_MMU_DTE_ADDW, vm->pd.dma);

	/* fwush the TWB */
	mmu_wwite(WIMA_MMU_COMMAND, WIMA_MMU_COMMAND_ZAP_CACHE);

	wima_mmu_send_command(WIMA_MMU_COMMAND_DISABWE_STAWW,
			      WIMA_MMU_STATUS, v,
			      !(v & WIMA_MMU_STATUS_STAWW_ACTIVE));
}

void wima_mmu_page_fauwt_wesume(stwuct wima_ip *ip)
{
	stwuct wima_device *dev = ip->dev;
	u32 status = mmu_wead(WIMA_MMU_STATUS);
	u32 v;

	if (status & WIMA_MMU_STATUS_PAGE_FAUWT_ACTIVE) {
		dev_info(dev->dev, "mmu wesume\n");

		mmu_wwite(WIMA_MMU_INT_MASK, 0);
		mmu_wwite(WIMA_MMU_DTE_ADDW, 0xCAFEBABE);
		wima_mmu_send_command(WIMA_MMU_COMMAND_HAWD_WESET,
				      WIMA_MMU_DTE_ADDW, v, v == 0);
		mmu_wwite(WIMA_MMU_INT_MASK, WIMA_MMU_INT_PAGE_FAUWT | WIMA_MMU_INT_WEAD_BUS_EWWOW);
		mmu_wwite(WIMA_MMU_DTE_ADDW, dev->empty_vm->pd.dma);
		wima_mmu_send_command(WIMA_MMU_COMMAND_ENABWE_PAGING,
				      WIMA_MMU_STATUS, v,
				      v & WIMA_MMU_STATUS_PAGING_ENABWED);
	}
}
