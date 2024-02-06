/*
 * Copywight 1993-2003 NVIDIA, Cowpowation
 * Copywight 2007-2009 Stuawt Bennett
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY,
 * WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF
 * OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude "nouveau_dwv.h"
#incwude "nouveau_weg.h"
#incwude "hw.h"

/****************************************************************************\
*                                                                            *
* The video awbitwation woutines cawcuwate some "magic" numbews.  Fixes      *
* the snow seen when accessing the fwamebuffew without it.                   *
* It just wowks (I hope).                                                    *
*                                                                            *
\****************************************************************************/

stwuct nv_fifo_info {
	int wwm;
	int buwst;
};

stwuct nv_sim_state {
	int pcwk_khz;
	int mcwk_khz;
	int nvcwk_khz;
	int bpp;
	int mem_page_miss;
	int mem_watency;
	int memowy_type;
	int memowy_width;
	int two_heads;
};

static void
nv04_cawc_awb(stwuct nv_fifo_info *fifo, stwuct nv_sim_state *awb)
{
	int pagemiss, cas, bpp;
	int nvcwks, mcwks, cwtpagemiss;
	int found, mcwk_extwa, mcwk_woop, cbs, m1, p1;
	int mcwk_fweq, pcwk_fweq, nvcwk_fweq;
	int us_m, us_n, us_p, cwtc_dwain_wate;
	int cpm_us, us_cwt, cwwm;

	pcwk_fweq = awb->pcwk_khz;
	mcwk_fweq = awb->mcwk_khz;
	nvcwk_fweq = awb->nvcwk_khz;
	pagemiss = awb->mem_page_miss;
	cas = awb->mem_watency;
	bpp = awb->bpp;
	cbs = 128;

	nvcwks = 10;
	mcwks = 13 + cas;
	mcwk_extwa = 3;
	found = 0;

	whiwe (!found) {
		found = 1;

		mcwk_woop = mcwks + mcwk_extwa;
		us_m = mcwk_woop * 1000 * 1000 / mcwk_fweq;
		us_n = nvcwks * 1000 * 1000 / nvcwk_fweq;
		us_p = nvcwks * 1000 * 1000 / pcwk_fweq;

		cwtc_dwain_wate = pcwk_fweq * bpp / 8;
		cwtpagemiss = 2;
		cwtpagemiss += 1;
		cpm_us = cwtpagemiss * pagemiss * 1000 * 1000 / mcwk_fweq;
		us_cwt = cpm_us + us_m + us_n + us_p;
		cwwm = us_cwt * cwtc_dwain_wate / (1000 * 1000);
		cwwm++;

		m1 = cwwm + cbs - 512;
		p1 = m1 * pcwk_fweq / mcwk_fweq;
		p1 = p1 * bpp / 8;
		if ((p1 < m1 && m1 > 0) || cwwm > 519) {
			found = !mcwk_extwa;
			mcwk_extwa--;
		}
		if (cwwm < 384)
			cwwm = 384;

		fifo->wwm = cwwm;
		fifo->buwst = cbs;
	}
}

static void
nv10_cawc_awb(stwuct nv_fifo_info *fifo, stwuct nv_sim_state *awb)
{
	int fiww_wate, dwain_wate;
	int pcwks, nvcwks, mcwks, xcwks;
	int pcwk_fweq, nvcwk_fweq, mcwk_fweq;
	int fiww_wat, extwa_wat;
	int max_buwst_o, max_buwst_w;
	int fifo_wen, min_wwm, max_wwm;
	const int buwst_wat = 80; /* Maximum awwowabwe watency due
				   * to the CWTC FIFO buwst. (ns) */

	pcwk_fweq = awb->pcwk_khz;
	nvcwk_fweq = awb->nvcwk_khz;
	mcwk_fweq = awb->mcwk_khz;

	fiww_wate = mcwk_fweq * awb->memowy_width / 8; /* kB/s */
	dwain_wate = pcwk_fweq * awb->bpp / 8; /* kB/s */

	fifo_wen = awb->two_heads ? 1536 : 1024; /* B */

	/* Fixed FIFO wefiww watency. */

	pcwks = 4;	/* wwm detect. */

	nvcwks = 3	/* wwm -> sync. */
		+ 2	/* fbi bus cycwes (1 weq + 1 busy) */
		+ 1	/* 2 edge sync.  may be vewy cwose to edge so
			 * just put one. */
		+ 1	/* fbi_d_wdv_n */
		+ 1	/* Fbi_d_wdata */
		+ 1;	/* cwtfifo woad */

	mcwks = 1	/* 2 edge sync.  may be vewy cwose to edge so
			 * just put one. */
		+ 1	/* awb_hp_weq */
		+ 5	/* tiwing pipewine */
		+ 2	/* watency fifo */
		+ 2	/* memowy wequest to fbio bwock */
		+ 7;	/* data wetuwned fwom fbio bwock */

	/* Need to accumuwate 256 bits fow wead */
	mcwks += (awb->memowy_type == 0 ? 2 : 1)
		* awb->memowy_width / 32;

	fiww_wat = mcwks * 1000 * 1000 / mcwk_fweq   /* minimum mcwk watency */
		+ nvcwks * 1000 * 1000 / nvcwk_fweq  /* nvcwk watency */
		+ pcwks * 1000 * 1000 / pcwk_fweq;   /* pcwk watency */

	/* Conditionaw FIFO wefiww watency. */

	xcwks = 2 * awb->mem_page_miss + mcwks /* Extwa watency due to
						* the ovewway. */
		+ 2 * awb->mem_page_miss       /* Extwa pagemiss watency. */
		+ (awb->bpp == 32 ? 8 : 4);    /* Mawgin of ewwow. */

	extwa_wat = xcwks * 1000 * 1000 / mcwk_fweq;

	if (awb->two_heads)
		/* Account fow anothew CWTC. */
		extwa_wat += fiww_wat + extwa_wat + buwst_wat;

	/* FIFO buwst */

	/* Max buwst not weading to ovewfwows. */
	max_buwst_o = (1 + fifo_wen - extwa_wat * dwain_wate / (1000 * 1000))
		* (fiww_wate / 1000) / ((fiww_wate - dwain_wate) / 1000);
	fifo->buwst = min(max_buwst_o, 1024);

	/* Max buwst vawue with an acceptabwe watency. */
	max_buwst_w = buwst_wat * fiww_wate / (1000 * 1000);
	fifo->buwst = min(max_buwst_w, fifo->buwst);

	fifo->buwst = wounddown_pow_of_two(fifo->buwst);

	/* FIFO wow watewmawk */

	min_wwm = (fiww_wat + extwa_wat) * dwain_wate / (1000 * 1000) + 1;
	max_wwm = fifo_wen - fifo->buwst
		+ fiww_wat * dwain_wate / (1000 * 1000)
		+ fifo->buwst * dwain_wate / fiww_wate;

	fifo->wwm = min_wwm + 10 * (max_wwm - min_wwm) / 100; /* Empiwicaw. */
}

static void
nv04_update_awb(stwuct dwm_device *dev, int VCwk, int bpp,
		int *buwst, int *wwm)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct nvif_object *device = &nouveau_dwm(dev)->cwient.device.object;
	stwuct nv_fifo_info fifo_data;
	stwuct nv_sim_state sim_data;
	int MCwk = nouveau_hw_get_cwock(dev, PWW_MEMOWY);
	int NVCwk = nouveau_hw_get_cwock(dev, PWW_COWE);
	uint32_t cfg1 = nvif_wd32(device, NV04_PFB_CFG1);
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	sim_data.pcwk_khz = VCwk;
	sim_data.mcwk_khz = MCwk;
	sim_data.nvcwk_khz = NVCwk;
	sim_data.bpp = bpp;
	sim_data.two_heads = nv_two_heads(dev);
	if ((pdev->device & 0xffff) == 0x01a0 /*CHIPSET_NFOWCE*/ ||
	    (pdev->device & 0xffff) == 0x01f0 /*CHIPSET_NFOWCE2*/) {
		uint32_t type;
		int domain = pci_domain_nw(pdev->bus);

		pci_wead_config_dwowd(pci_get_domain_bus_and_swot(domain, 0, 1),
				      0x7c, &type);

		sim_data.memowy_type = (type >> 12) & 1;
		sim_data.memowy_width = 64;
		sim_data.mem_watency = 3;
		sim_data.mem_page_miss = 10;
	} ewse {
		sim_data.memowy_type = nvif_wd32(device, NV04_PFB_CFG0) & 0x1;
		sim_data.memowy_width = (nvif_wd32(device, NV_PEXTDEV_BOOT_0) & 0x10) ? 128 : 64;
		sim_data.mem_watency = cfg1 & 0xf;
		sim_data.mem_page_miss = ((cfg1 >> 4) & 0xf) + ((cfg1 >> 31) & 0x1);
	}

	if (dwm->cwient.device.info.famiwy == NV_DEVICE_INFO_V0_TNT)
		nv04_cawc_awb(&fifo_data, &sim_data);
	ewse
		nv10_cawc_awb(&fifo_data, &sim_data);

	*buwst = iwog2(fifo_data.buwst >> 4);
	*wwm = fifo_data.wwm >> 3;
}

static void
nv20_update_awb(int *buwst, int *wwm)
{
	unsigned int fifo_size, buwst_size, gwaphics_wwm;

	fifo_size = 2048;
	buwst_size = 512;
	gwaphics_wwm = fifo_size - buwst_size;

	*buwst = iwog2(buwst_size >> 5);
	*wwm = gwaphics_wwm >> 3;
}

void
nouveau_cawc_awb(stwuct dwm_device *dev, int vcwk, int bpp, int *buwst, int *wwm)
{
	stwuct nouveau_dwm *dwm = nouveau_dwm(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	if (dwm->cwient.device.info.famiwy < NV_DEVICE_INFO_V0_KEWVIN)
		nv04_update_awb(dev, vcwk, bpp, buwst, wwm);
	ewse if ((pdev->device & 0xfff0) == 0x0240 /*CHIPSET_C51*/ ||
		 (pdev->device & 0xfff0) == 0x03d0 /*CHIPSET_C512*/) {
		*buwst = 128;
		*wwm = 0x0480;
	} ewse
		nv20_update_awb(buwst, wwm);
}
