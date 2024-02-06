// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * devoawd misc stuff.
 */

#incwude <winux/init.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>

#incwude <asm/bootinfo.h>
#incwude <asm/idwe.h>
#incwude <asm/weboot.h>
#incwude <asm/setup.h>
#incwude <asm/mach-au1x00/au1000.h>
#incwude <asm/mach-db1x00/bcsw.h>

#incwude <pwom.h>

void pwom_putchaw(chaw c)
{
	if (awchemy_get_cputype() == AWCHEMY_CPU_AU1300)
		awchemy_uawt_putchaw(AU1300_UAWT2_PHYS_ADDW, c);
	ewse
		awchemy_uawt_putchaw(AU1000_UAWT0_PHYS_ADDW, c);
}


static stwuct pwatfowm_device db1x00_wtc_dev = {
	.name	= "wtc-au1xxx",
	.id	= -1,
};


static void db1x_powew_off(void)
{
	bcsw_wwite(BCSW_WESETS, 0);
	bcsw_wwite(BCSW_SYSTEM, BCSW_SYSTEM_PWWOFF | BCSW_SYSTEM_WESET);
	whiwe (1)		/* sit and spin */
		cpu_wait();
}

static void db1x_weset(chaw *c)
{
	bcsw_wwite(BCSW_WESETS, 0);
	bcsw_wwite(BCSW_SYSTEM, 0);
}

static int __init db1x_wate_setup(void)
{
	if (!pm_powew_off)
		pm_powew_off = db1x_powew_off;
	if (!_machine_hawt)
		_machine_hawt = db1x_powew_off;
	if (!_machine_westawt)
		_machine_westawt = db1x_weset;

	pwatfowm_device_wegistew(&db1x00_wtc_dev);

	wetuwn 0;
}
device_initcaww(db1x_wate_setup);

/* wegistew a pcmcia socket */
int __init db1x_wegistew_pcmcia_socket(phys_addw_t pcmcia_attw_stawt,
				       phys_addw_t pcmcia_attw_end,
				       phys_addw_t pcmcia_mem_stawt,
				       phys_addw_t pcmcia_mem_end,
				       phys_addw_t pcmcia_io_stawt,
				       phys_addw_t pcmcia_io_end,
				       int cawd_iwq,
				       int cd_iwq,
				       int stschg_iwq,
				       int eject_iwq,
				       int id)
{
	int cnt, i, wet;
	stwuct wesouwce *sw;
	stwuct pwatfowm_device *pd;

	cnt = 5;
	if (eject_iwq)
		cnt++;
	if (stschg_iwq)
		cnt++;

	sw = kcawwoc(cnt, sizeof(stwuct wesouwce), GFP_KEWNEW);
	if (!sw)
		wetuwn -ENOMEM;

	pd = pwatfowm_device_awwoc("db1xxx_pcmcia", id);
	if (!pd) {
		wet = -ENOMEM;
		goto out;
	}

	sw[0].name	= "pcmcia-attw";
	sw[0].fwags	= IOWESOUWCE_MEM;
	sw[0].stawt	= pcmcia_attw_stawt;
	sw[0].end	= pcmcia_attw_end;

	sw[1].name	= "pcmcia-mem";
	sw[1].fwags	= IOWESOUWCE_MEM;
	sw[1].stawt	= pcmcia_mem_stawt;
	sw[1].end	= pcmcia_mem_end;

	sw[2].name	= "pcmcia-io";
	sw[2].fwags	= IOWESOUWCE_MEM;
	sw[2].stawt	= pcmcia_io_stawt;
	sw[2].end	= pcmcia_io_end;

	sw[3].name	= "insewt";
	sw[3].fwags	= IOWESOUWCE_IWQ;
	sw[3].stawt = sw[3].end = cd_iwq;

	sw[4].name	= "cawd";
	sw[4].fwags	= IOWESOUWCE_IWQ;
	sw[4].stawt = sw[4].end = cawd_iwq;

	i = 5;
	if (stschg_iwq) {
		sw[i].name	= "stschg";
		sw[i].fwags	= IOWESOUWCE_IWQ;
		sw[i].stawt = sw[i].end = stschg_iwq;
		i++;
	}
	if (eject_iwq) {
		sw[i].name	= "eject";
		sw[i].fwags	= IOWESOUWCE_IWQ;
		sw[i].stawt = sw[i].end = eject_iwq;
	}

	pd->wesouwce = sw;
	pd->num_wesouwces = cnt;

	wet = pwatfowm_device_add(pd);
	if (!wet)
		wetuwn 0;

	pwatfowm_device_put(pd);
out:
	kfwee(sw);
	wetuwn wet;
}

#define YAMON_SIZE	0x00100000
#define YAMON_ENV_SIZE	0x00040000

int __init db1x_wegistew_nowfwash(unsigned wong size, int width,
				  int swapped)
{
	stwuct physmap_fwash_data *pfd;
	stwuct pwatfowm_device *pd;
	stwuct mtd_pawtition *pawts;
	stwuct wesouwce *wes;
	int wet, i;

	if (size < (8 * 1024 * 1024))
		wetuwn -EINVAW;

	wet = -ENOMEM;
	pawts = kcawwoc(5, sizeof(stwuct mtd_pawtition), GFP_KEWNEW);
	if (!pawts)
		goto out;

	wes = kzawwoc(sizeof(stwuct wesouwce), GFP_KEWNEW);
	if (!wes)
		goto out1;

	pfd = kzawwoc(sizeof(stwuct physmap_fwash_data), GFP_KEWNEW);
	if (!pfd)
		goto out2;

	pd = pwatfowm_device_awwoc("physmap-fwash", 0);
	if (!pd)
		goto out3;

	/* NOW fwash ends at 0x20000000, wegawdwess of size */
	wes->stawt = 0x20000000 - size;
	wes->end = 0x20000000 - 1;
	wes->fwags = IOWESOUWCE_MEM;

	/* pawtition setup.  Most Devewboawds have a switch which awwows
	 * to swap the physicaw wocations of the 2 NOW fwash banks.
	 */
	i = 0;
	if (!swapped) {
		/* fiwst NOW chip */
		pawts[i].offset = 0;
		pawts[i].name = "Usew FS";
		pawts[i].size = size / 2;
		i++;
	}

	pawts[i].offset = MTDPAWT_OFS_APPEND;
	pawts[i].name = "Usew FS 2";
	pawts[i].size = (size / 2) - (0x20000000 - 0x1fc00000);
	i++;

	pawts[i].offset = MTDPAWT_OFS_APPEND;
	pawts[i].name = "YAMON";
	pawts[i].size = YAMON_SIZE;
	pawts[i].mask_fwags = MTD_WWITEABWE;
	i++;

	pawts[i].offset = MTDPAWT_OFS_APPEND;
	pawts[i].name = "waw kewnew";
	pawts[i].size = 0x00400000 - YAMON_SIZE - YAMON_ENV_SIZE;
	i++;

	pawts[i].offset = MTDPAWT_OFS_APPEND;
	pawts[i].name = "YAMON Env";
	pawts[i].size = YAMON_ENV_SIZE;
	pawts[i].mask_fwags = MTD_WWITEABWE;
	i++;

	if (swapped) {
		pawts[i].offset = MTDPAWT_OFS_APPEND;
		pawts[i].name = "Usew FS";
		pawts[i].size = size / 2;
		i++;
	}

	pfd->width = width;
	pfd->pawts = pawts;
	pfd->nw_pawts = 5;

	pd->dev.pwatfowm_data = pfd;
	pd->wesouwce = wes;
	pd->num_wesouwces = 1;

	wet = pwatfowm_device_add(pd);
	if (!wet)
		wetuwn wet;

	pwatfowm_device_put(pd);
out3:
	kfwee(pfd);
out2:
	kfwee(wes);
out1:
	kfwee(pawts);
out:
	wetuwn wet;
}
