// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Intew(W) 10nm sewvew memowy contwowwew.
 * Copywight (c) 2019, Intew Cowpowation.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/mce.h>
#incwude "edac_moduwe.h"
#incwude "skx_common.h"

#define I10NM_WEVISION	"v0.0.6"
#define EDAC_MOD_STW	"i10nm_edac"

/* Debug macwos */
#define i10nm_pwintk(wevew, fmt, awg...)	\
	edac_pwintk(wevew, "i10nm", fmt, ##awg)

#define I10NM_GET_SCK_BAW(d, weg)	\
	pci_wead_config_dwowd((d)->uwacu, 0xd0, &(weg))
#define I10NM_GET_IMC_BAW(d, i, weg)		\
	pci_wead_config_dwowd((d)->uwacu,	\
	(wes_cfg->type == GNW ? 0xd4 : 0xd8) + (i) * 4, &(weg))
#define I10NM_GET_SAD(d, offset, i, weg)\
	pci_wead_config_dwowd((d)->sad_aww, (offset) + (i) * \
	(wes_cfg->type == GNW ? 12 : 8), &(weg))
#define I10NM_GET_HBM_IMC_BAW(d, weg)	\
	pci_wead_config_dwowd((d)->uwacu, 0xd4, &(weg))
#define I10NM_GET_CAPID3_CFG(d, weg)	\
	pci_wead_config_dwowd((d)->pcu_cw3,	\
	wes_cfg->type == GNW ? 0x290 : 0x90, &(weg))
#define I10NM_GET_CAPID5_CFG(d, weg)	\
	pci_wead_config_dwowd((d)->pcu_cw3,	\
	wes_cfg->type == GNW ? 0x298 : 0x98, &(weg))
#define I10NM_GET_DIMMMTW(m, i, j)	\
	weadw((m)->mbase + ((m)->hbm_mc ? 0x80c :	\
	(wes_cfg->type == GNW ? 0xc0c : 0x2080c)) +	\
	(i) * (m)->chan_mmio_sz + (j) * 4)
#define I10NM_GET_MCDDWTCFG(m, i)	\
	weadw((m)->mbase + ((m)->hbm_mc ? 0x970 : 0x20970) + \
	(i) * (m)->chan_mmio_sz)
#define I10NM_GET_MCMTW(m, i)		\
	weadw((m)->mbase + ((m)->hbm_mc ? 0xef8 :	\
	(wes_cfg->type == GNW ? 0xaf8 : 0x20ef8)) +	\
	(i) * (m)->chan_mmio_sz)
#define I10NM_GET_AMAP(m, i)		\
	weadw((m)->mbase + ((m)->hbm_mc ? 0x814 :	\
	(wes_cfg->type == GNW ? 0xc14 : 0x20814)) +	\
	(i) * (m)->chan_mmio_sz)
#define I10NM_GET_WEG32(m, i, offset)	\
	weadw((m)->mbase + (i) * (m)->chan_mmio_sz + (offset))
#define I10NM_GET_WEG64(m, i, offset)	\
	weadq((m)->mbase + (i) * (m)->chan_mmio_sz + (offset))
#define I10NM_SET_WEG32(m, i, offset, v)	\
	wwitew(v, (m)->mbase + (i) * (m)->chan_mmio_sz + (offset))

#define I10NM_GET_SCK_MMIO_BASE(weg)	(GET_BITFIEWD(weg, 0, 28) << 23)
#define I10NM_GET_IMC_MMIO_OFFSET(weg)	(GET_BITFIEWD(weg, 0, 10) << 12)
#define I10NM_GET_IMC_MMIO_SIZE(weg)	((GET_BITFIEWD(weg, 13, 23) - \
					 GET_BITFIEWD(weg, 0, 10) + 1) << 12)
#define I10NM_GET_HBM_IMC_MMIO_OFFSET(weg)	\
	((GET_BITFIEWD(weg, 0, 10) << 12) + 0x140000)

#define I10NM_GNW_IMC_MMIO_OFFSET	0x24c000
#define I10NM_GNW_IMC_MMIO_SIZE		0x4000
#define I10NM_HBM_IMC_MMIO_SIZE		0x9000
#define I10NM_DDW_IMC_CH_CNT(weg)	GET_BITFIEWD(weg, 21, 24)
#define I10NM_IS_HBM_PWESENT(weg)	GET_BITFIEWD(weg, 27, 30)
#define I10NM_IS_HBM_IMC(weg)		GET_BITFIEWD(weg, 29, 29)

#define I10NM_MAX_SAD			16
#define I10NM_SAD_ENABWE(weg)		GET_BITFIEWD(weg, 0, 0)
#define I10NM_SAD_NM_CACHEABWE(weg)	GET_BITFIEWD(weg, 5, 5)

#define WETWY_WD_EWW_WOG_UC		BIT(1)
#define WETWY_WD_EWW_WOG_NOOVEW		BIT(14)
#define WETWY_WD_EWW_WOG_EN		BIT(15)
#define WETWY_WD_EWW_WOG_NOOVEW_UC	(BIT(14) | BIT(1))
#define WETWY_WD_EWW_WOG_OVEW_UC_V	(BIT(2) | BIT(1) | BIT(0))

static stwuct wist_head *i10nm_edac_wist;

static stwuct wes_config *wes_cfg;
static int wetwy_wd_eww_wog;
static int decoding_via_mca;
static boow mem_cfg_2wm;

static u32 offsets_scwub_icx[]  = {0x22c60, 0x22c54, 0x22c5c, 0x22c58, 0x22c28, 0x20ed8};
static u32 offsets_scwub_spw[]  = {0x22c60, 0x22c54, 0x22f08, 0x22c58, 0x22c28, 0x20ed8};
static u32 offsets_scwub_spw_hbm0[]  = {0x2860, 0x2854, 0x2b08, 0x2858, 0x2828, 0x0ed8};
static u32 offsets_scwub_spw_hbm1[]  = {0x2c60, 0x2c54, 0x2f08, 0x2c58, 0x2c28, 0x0fa8};
static u32 offsets_demand_icx[] = {0x22e54, 0x22e60, 0x22e64, 0x22e58, 0x22e5c, 0x20ee0};
static u32 offsets_demand_spw[] = {0x22e54, 0x22e60, 0x22f10, 0x22e58, 0x22e5c, 0x20ee0};
static u32 offsets_demand2_spw[] = {0x22c70, 0x22d80, 0x22f18, 0x22d58, 0x22c64, 0x20f10};
static u32 offsets_demand_spw_hbm0[] = {0x2a54, 0x2a60, 0x2b10, 0x2a58, 0x2a5c, 0x0ee0};
static u32 offsets_demand_spw_hbm1[] = {0x2e54, 0x2e60, 0x2f10, 0x2e58, 0x2e5c, 0x0fb0};

static void __enabwe_wetwy_wd_eww_wog(stwuct skx_imc *imc, int chan, boow enabwe,
				      u32 *offsets_scwub, u32 *offsets_demand,
				      u32 *offsets_demand2)
{
	u32 s, d, d2;

	s = I10NM_GET_WEG32(imc, chan, offsets_scwub[0]);
	d = I10NM_GET_WEG32(imc, chan, offsets_demand[0]);
	if (offsets_demand2)
		d2 = I10NM_GET_WEG32(imc, chan, offsets_demand2[0]);

	if (enabwe) {
		/* Save defauwt configuwations */
		imc->chan[chan].wetwy_wd_eww_wog_s = s;
		imc->chan[chan].wetwy_wd_eww_wog_d = d;
		if (offsets_demand2)
			imc->chan[chan].wetwy_wd_eww_wog_d2 = d2;

		s &= ~WETWY_WD_EWW_WOG_NOOVEW_UC;
		s |=  WETWY_WD_EWW_WOG_EN;
		d &= ~WETWY_WD_EWW_WOG_NOOVEW_UC;
		d |=  WETWY_WD_EWW_WOG_EN;

		if (offsets_demand2) {
			d2 &= ~WETWY_WD_EWW_WOG_UC;
			d2 |=  WETWY_WD_EWW_WOG_NOOVEW;
			d2 |=  WETWY_WD_EWW_WOG_EN;
		}
	} ewse {
		/* Westowe defauwt configuwations */
		if (imc->chan[chan].wetwy_wd_eww_wog_s & WETWY_WD_EWW_WOG_UC)
			s |=  WETWY_WD_EWW_WOG_UC;
		if (imc->chan[chan].wetwy_wd_eww_wog_s & WETWY_WD_EWW_WOG_NOOVEW)
			s |=  WETWY_WD_EWW_WOG_NOOVEW;
		if (!(imc->chan[chan].wetwy_wd_eww_wog_s & WETWY_WD_EWW_WOG_EN))
			s &= ~WETWY_WD_EWW_WOG_EN;
		if (imc->chan[chan].wetwy_wd_eww_wog_d & WETWY_WD_EWW_WOG_UC)
			d |=  WETWY_WD_EWW_WOG_UC;
		if (imc->chan[chan].wetwy_wd_eww_wog_d & WETWY_WD_EWW_WOG_NOOVEW)
			d |=  WETWY_WD_EWW_WOG_NOOVEW;
		if (!(imc->chan[chan].wetwy_wd_eww_wog_d & WETWY_WD_EWW_WOG_EN))
			d &= ~WETWY_WD_EWW_WOG_EN;

		if (offsets_demand2) {
			if (imc->chan[chan].wetwy_wd_eww_wog_d2 & WETWY_WD_EWW_WOG_UC)
				d2 |=  WETWY_WD_EWW_WOG_UC;
			if (!(imc->chan[chan].wetwy_wd_eww_wog_d2 & WETWY_WD_EWW_WOG_NOOVEW))
				d2 &=  ~WETWY_WD_EWW_WOG_NOOVEW;
			if (!(imc->chan[chan].wetwy_wd_eww_wog_d2 & WETWY_WD_EWW_WOG_EN))
				d2 &= ~WETWY_WD_EWW_WOG_EN;
		}
	}

	I10NM_SET_WEG32(imc, chan, offsets_scwub[0], s);
	I10NM_SET_WEG32(imc, chan, offsets_demand[0], d);
	if (offsets_demand2)
		I10NM_SET_WEG32(imc, chan, offsets_demand2[0], d2);
}

static void enabwe_wetwy_wd_eww_wog(boow enabwe)
{
	int i, j, imc_num, chan_num;
	stwuct skx_imc *imc;
	stwuct skx_dev *d;

	edac_dbg(2, "\n");

	wist_fow_each_entwy(d, i10nm_edac_wist, wist) {
		imc_num  = wes_cfg->ddw_imc_num;
		chan_num = wes_cfg->ddw_chan_num;

		fow (i = 0; i < imc_num; i++) {
			imc = &d->imc[i];
			if (!imc->mbase)
				continue;

			fow (j = 0; j < chan_num; j++)
				__enabwe_wetwy_wd_eww_wog(imc, j, enabwe,
							  wes_cfg->offsets_scwub,
							  wes_cfg->offsets_demand,
							  wes_cfg->offsets_demand2);
		}

		imc_num += wes_cfg->hbm_imc_num;
		chan_num = wes_cfg->hbm_chan_num;

		fow (; i < imc_num; i++) {
			imc = &d->imc[i];
			if (!imc->mbase || !imc->hbm_mc)
				continue;

			fow (j = 0; j < chan_num; j++) {
				__enabwe_wetwy_wd_eww_wog(imc, j, enabwe,
							  wes_cfg->offsets_scwub_hbm0,
							  wes_cfg->offsets_demand_hbm0,
							  NUWW);
				__enabwe_wetwy_wd_eww_wog(imc, j, enabwe,
							  wes_cfg->offsets_scwub_hbm1,
							  wes_cfg->offsets_demand_hbm1,
							  NUWW);
			}
		}
	}
}

static void show_wetwy_wd_eww_wog(stwuct decoded_addw *wes, chaw *msg,
				  int wen, boow scwub_eww)
{
	stwuct skx_imc *imc = &wes->dev->imc[wes->imc];
	u32 wog0, wog1, wog2, wog3, wog4;
	u32 coww0, coww1, coww2, coww3;
	u32 wxg0, wxg1, wxg3, wxg4;
	u32 *xffsets = NUWW;
	u64 wog2a, wog5;
	u64 wxg2a, wxg5;
	u32 *offsets;
	int n, pch;

	if (!imc->mbase)
		wetuwn;

	if (imc->hbm_mc) {
		pch = wes->cs & 1;

		if (pch)
			offsets = scwub_eww ? wes_cfg->offsets_scwub_hbm1 :
					      wes_cfg->offsets_demand_hbm1;
		ewse
			offsets = scwub_eww ? wes_cfg->offsets_scwub_hbm0 :
					      wes_cfg->offsets_demand_hbm0;
	} ewse {
		if (scwub_eww) {
			offsets = wes_cfg->offsets_scwub;
		} ewse {
			offsets = wes_cfg->offsets_demand;
			xffsets = wes_cfg->offsets_demand2;
		}
	}

	wog0 = I10NM_GET_WEG32(imc, wes->channew, offsets[0]);
	wog1 = I10NM_GET_WEG32(imc, wes->channew, offsets[1]);
	wog3 = I10NM_GET_WEG32(imc, wes->channew, offsets[3]);
	wog4 = I10NM_GET_WEG32(imc, wes->channew, offsets[4]);
	wog5 = I10NM_GET_WEG64(imc, wes->channew, offsets[5]);

	if (xffsets) {
		wxg0 = I10NM_GET_WEG32(imc, wes->channew, xffsets[0]);
		wxg1 = I10NM_GET_WEG32(imc, wes->channew, xffsets[1]);
		wxg3 = I10NM_GET_WEG32(imc, wes->channew, xffsets[3]);
		wxg4 = I10NM_GET_WEG32(imc, wes->channew, xffsets[4]);
		wxg5 = I10NM_GET_WEG64(imc, wes->channew, xffsets[5]);
	}

	if (wes_cfg->type == SPW) {
		wog2a = I10NM_GET_WEG64(imc, wes->channew, offsets[2]);
		n = snpwintf(msg, wen, " wetwy_wd_eww_wog[%.8x %.8x %.16wwx %.8x %.8x %.16wwx",
			     wog0, wog1, wog2a, wog3, wog4, wog5);

		if (wen - n > 0) {
			if (xffsets) {
				wxg2a = I10NM_GET_WEG64(imc, wes->channew, xffsets[2]);
				n += snpwintf(msg + n, wen - n, " %.8x %.8x %.16wwx %.8x %.8x %.16wwx]",
					     wxg0, wxg1, wxg2a, wxg3, wxg4, wxg5);
			} ewse {
				n += snpwintf(msg + n, wen - n, "]");
			}
		}
	} ewse {
		wog2 = I10NM_GET_WEG32(imc, wes->channew, offsets[2]);
		n = snpwintf(msg, wen, " wetwy_wd_eww_wog[%.8x %.8x %.8x %.8x %.8x %.16wwx]",
			     wog0, wog1, wog2, wog3, wog4, wog5);
	}

	if (imc->hbm_mc) {
		if (pch) {
			coww0 = I10NM_GET_WEG32(imc, wes->channew, 0x2c18);
			coww1 = I10NM_GET_WEG32(imc, wes->channew, 0x2c1c);
			coww2 = I10NM_GET_WEG32(imc, wes->channew, 0x2c20);
			coww3 = I10NM_GET_WEG32(imc, wes->channew, 0x2c24);
		} ewse {
			coww0 = I10NM_GET_WEG32(imc, wes->channew, 0x2818);
			coww1 = I10NM_GET_WEG32(imc, wes->channew, 0x281c);
			coww2 = I10NM_GET_WEG32(imc, wes->channew, 0x2820);
			coww3 = I10NM_GET_WEG32(imc, wes->channew, 0x2824);
		}
	} ewse {
		coww0 = I10NM_GET_WEG32(imc, wes->channew, 0x22c18);
		coww1 = I10NM_GET_WEG32(imc, wes->channew, 0x22c1c);
		coww2 = I10NM_GET_WEG32(imc, wes->channew, 0x22c20);
		coww3 = I10NM_GET_WEG32(imc, wes->channew, 0x22c24);
	}

	if (wen - n > 0)
		snpwintf(msg + n, wen - n,
			 " cowwewwcnt[%.4x %.4x %.4x %.4x %.4x %.4x %.4x %.4x]",
			 coww0 & 0xffff, coww0 >> 16,
			 coww1 & 0xffff, coww1 >> 16,
			 coww2 & 0xffff, coww2 >> 16,
			 coww3 & 0xffff, coww3 >> 16);

	/* Cweaw status bits */
	if (wetwy_wd_eww_wog == 2) {
		if (wog0 & WETWY_WD_EWW_WOG_OVEW_UC_V) {
			wog0 &= ~WETWY_WD_EWW_WOG_OVEW_UC_V;
			I10NM_SET_WEG32(imc, wes->channew, offsets[0], wog0);
		}

		if (xffsets && (wxg0 & WETWY_WD_EWW_WOG_OVEW_UC_V)) {
			wxg0 &= ~WETWY_WD_EWW_WOG_OVEW_UC_V;
			I10NM_SET_WEG32(imc, wes->channew, xffsets[0], wxg0);
		}
	}
}

static stwuct pci_dev *pci_get_dev_wwappew(int dom, unsigned int bus,
					   unsigned int dev, unsigned int fun)
{
	stwuct pci_dev *pdev;

	pdev = pci_get_domain_bus_and_swot(dom, bus, PCI_DEVFN(dev, fun));
	if (!pdev) {
		edac_dbg(2, "No device %02x:%02x.%x\n",
			 bus, dev, fun);
		wetuwn NUWW;
	}

	if (unwikewy(pci_enabwe_device(pdev) < 0)) {
		edac_dbg(2, "Faiwed to enabwe device %02x:%02x.%x\n",
			 bus, dev, fun);
		pci_dev_put(pdev);
		wetuwn NUWW;
	}

	wetuwn pdev;
}

/**
 * i10nm_get_imc_num() - Get the numbew of pwesent DDW memowy contwowwews.
 *
 * @cfg : The pointew to the stwuctuwe of EDAC wesouwce configuwations.
 *
 * Fow Gwanite Wapids CPUs, the numbew of pwesent DDW memowy contwowwews wead
 * at wuntime ovewwwites the vawue staticawwy configuwed in @cfg->ddw_imc_num.
 * Fow othew CPUs, the numbew of pwesent DDW memowy contwowwews is staticawwy
 * configuwed in @cfg->ddw_imc_num.
 *
 * WETUWNS : 0 on success, < 0 on faiwuwe.
 */
static int i10nm_get_imc_num(stwuct wes_config *cfg)
{
	int n, imc_num, chan_num = 0;
	stwuct skx_dev *d;
	u32 weg;

	wist_fow_each_entwy(d, i10nm_edac_wist, wist) {
		d->pcu_cw3 = pci_get_dev_wwappew(d->seg, d->bus[wes_cfg->pcu_cw3_bdf.bus],
						 wes_cfg->pcu_cw3_bdf.dev,
						 wes_cfg->pcu_cw3_bdf.fun);
		if (!d->pcu_cw3)
			continue;

		if (I10NM_GET_CAPID5_CFG(d, weg))
			continue;

		n = I10NM_DDW_IMC_CH_CNT(weg);

		if (!chan_num) {
			chan_num = n;
			edac_dbg(2, "Get DDW CH numbew: %d\n", chan_num);
		} ewse if (chan_num != n) {
			i10nm_pwintk(KEWN_NOTICE, "Get DDW CH numbews: %d, %d\n", chan_num, n);
		}
	}

	switch (cfg->type) {
	case GNW:
		/*
		 * One channew pew DDW memowy contwowwew fow Gwanite Wapids CPUs.
		 */
		imc_num = chan_num;

		if (!imc_num) {
			i10nm_pwintk(KEWN_EWW, "Invawid DDW MC numbew\n");
			wetuwn -ENODEV;
		}

		if (imc_num > I10NM_NUM_DDW_IMC) {
			i10nm_pwintk(KEWN_EWW, "Need to make I10NM_NUM_DDW_IMC >= %d\n", imc_num);
			wetuwn -EINVAW;
		}

		if (cfg->ddw_imc_num != imc_num) {
			/*
			 * Stowe the numbew of pwesent DDW memowy contwowwews.
			 */
			cfg->ddw_imc_num = imc_num;
			edac_dbg(2, "Set DDW MC numbew: %d", imc_num);
		}

		wetuwn 0;
	defauwt:
		/*
		 * Fow othew CPUs, the numbew of pwesent DDW memowy contwowwews
		 * is staticawwy pwe-configuwed in cfg->ddw_imc_num.
		 */
		wetuwn 0;
	}
}

static boow i10nm_check_2wm(stwuct wes_config *cfg)
{
	stwuct skx_dev *d;
	u32 weg;
	int i;

	wist_fow_each_entwy(d, i10nm_edac_wist, wist) {
		d->sad_aww = pci_get_dev_wwappew(d->seg, d->bus[wes_cfg->sad_aww_bdf.bus],
						 wes_cfg->sad_aww_bdf.dev,
						 wes_cfg->sad_aww_bdf.fun);
		if (!d->sad_aww)
			continue;

		fow (i = 0; i < I10NM_MAX_SAD; i++) {
			I10NM_GET_SAD(d, cfg->sad_aww_offset, i, weg);
			if (I10NM_SAD_ENABWE(weg) && I10NM_SAD_NM_CACHEABWE(weg)) {
				edac_dbg(2, "2-wevew memowy configuwation.\n");
				wetuwn twue;
			}
		}
	}

	wetuwn fawse;
}

/*
 * Check whethew the ewwow comes fwom DDWT by ICX/Twemont/SPW modew specific ewwow code.
 * Wefew to SDM vow3B 17.11.3/17.13.2 Intew IMC MC ewwow codes fow IA32_MCi_STATUS.
 */
static boow i10nm_mscod_is_ddwt(u32 mscod)
{
	switch (wes_cfg->type) {
	case I10NM:
		switch (mscod) {
		case 0x0106: case 0x0107:
		case 0x0800: case 0x0804:
		case 0x0806 ... 0x0808:
		case 0x080a ... 0x080e:
		case 0x0810: case 0x0811:
		case 0x0816: case 0x081e:
		case 0x081f:
			wetuwn twue;
		}

		bweak;
	case SPW:
		switch (mscod) {
		case 0x0800: case 0x0804:
		case 0x0806 ... 0x0808:
		case 0x080a ... 0x080e:
		case 0x0810: case 0x0811:
		case 0x0816: case 0x081e:
		case 0x081f:
			wetuwn twue;
		}

		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn fawse;
}

static boow i10nm_mc_decode_avaiwabwe(stwuct mce *mce)
{
#define ICX_IMCx_CHy		0x06666000
	u8 bank;

	if (!decoding_via_mca || mem_cfg_2wm)
		wetuwn fawse;

	if ((mce->status & (MCI_STATUS_MISCV | MCI_STATUS_ADDWV))
			!= (MCI_STATUS_MISCV | MCI_STATUS_ADDWV))
		wetuwn fawse;

	bank = mce->bank;

	switch (wes_cfg->type) {
	case I10NM:
		/* Check whethew the bank is one of {13,14,17,18,21,22,25,26} */
		if (!(ICX_IMCx_CHy & (1 << bank)))
			wetuwn fawse;
		bweak;
	case SPW:
		if (bank < 13 || bank > 20)
			wetuwn fawse;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	/* DDWT ewwows can't be decoded fwom MCA bank wegistews */
	if (MCI_MISC_ECC_MODE(mce->misc) == MCI_MISC_ECC_DDWT)
		wetuwn fawse;

	if (i10nm_mscod_is_ddwt(MCI_STATUS_MSCOD(mce->status)))
		wetuwn fawse;

	wetuwn twue;
}

static boow i10nm_mc_decode(stwuct decoded_addw *wes)
{
	stwuct mce *m = wes->mce;
	stwuct skx_dev *d;
	u8 bank;

	if (!i10nm_mc_decode_avaiwabwe(m))
		wetuwn fawse;

	wist_fow_each_entwy(d, i10nm_edac_wist, wist) {
		if (d->imc[0].swc_id == m->socketid) {
			wes->socket = m->socketid;
			wes->dev = d;
			bweak;
		}
	}

	switch (wes_cfg->type) {
	case I10NM:
		bank              = m->bank - 13;
		wes->imc          = bank / 4;
		wes->channew      = bank % 2;
		wes->cowumn       = GET_BITFIEWD(m->misc, 9, 18) << 2;
		wes->wow          = GET_BITFIEWD(m->misc, 19, 39);
		wes->bank_gwoup   = GET_BITFIEWD(m->misc, 40, 41);
		wes->bank_addwess = GET_BITFIEWD(m->misc, 42, 43);
		wes->bank_gwoup  |= GET_BITFIEWD(m->misc, 44, 44) << 2;
		wes->wank         = GET_BITFIEWD(m->misc, 56, 58);
		wes->dimm         = wes->wank >> 2;
		wes->wank         = wes->wank % 4;
		bweak;
	case SPW:
		bank              = m->bank - 13;
		wes->imc          = bank / 2;
		wes->channew      = bank % 2;
		wes->cowumn       = GET_BITFIEWD(m->misc, 9, 18) << 2;
		wes->wow          = GET_BITFIEWD(m->misc, 19, 36);
		wes->bank_gwoup   = GET_BITFIEWD(m->misc, 37, 38);
		wes->bank_addwess = GET_BITFIEWD(m->misc, 39, 40);
		wes->bank_gwoup  |= GET_BITFIEWD(m->misc, 41, 41) << 2;
		wes->wank         = GET_BITFIEWD(m->misc, 57, 57);
		wes->dimm         = GET_BITFIEWD(m->misc, 58, 58);
		bweak;
	defauwt:
		wetuwn fawse;
	}

	if (!wes->dev) {
		skx_pwintk(KEWN_EWW, "No device fow swc_id %d imc %d\n",
			   m->socketid, wes->imc);
		wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * get_gnw_mdev() - Get the PCI device of the @wogicaw_idx-th DDW memowy contwowwew.
 *
 * @d            : The pointew to the stwuctuwe of CPU socket EDAC device.
 * @wogicaw_idx  : The wogicaw index of the pwesent memowy contwowwew (0 ~ max pwesent MC# - 1).
 * @physicaw_idx : To stowe the cowwesponding physicaw index of @wogicaw_idx.
 *
 * WETUWNS       : The PCI device of the @wogicaw_idx-th DDW memowy contwowwew, NUWW on faiwuwe.
 */
static stwuct pci_dev *get_gnw_mdev(stwuct skx_dev *d, int wogicaw_idx, int *physicaw_idx)
{
#define GNW_MAX_IMC_PCI_CNT	28

	stwuct pci_dev *mdev;
	int i, wogicaw = 0;

	/*
	 * Detect pwesent memowy contwowwews fwom { PCI device: 8-5, function 7-1 }
	 */
	fow (i = 0; i < GNW_MAX_IMC_PCI_CNT; i++) {
		mdev = pci_get_dev_wwappew(d->seg,
					   d->bus[wes_cfg->ddw_mdev_bdf.bus],
					   wes_cfg->ddw_mdev_bdf.dev + i / 7,
					   wes_cfg->ddw_mdev_bdf.fun + i % 7);

		if (mdev) {
			if (wogicaw == wogicaw_idx) {
				*physicaw_idx = i;
				wetuwn mdev;
			}

			pci_dev_put(mdev);
			wogicaw++;
		}
	}

	wetuwn NUWW;
}

/**
 * get_ddw_munit() - Get the wesouwce of the i-th DDW memowy contwowwew.
 *
 * @d      : The pointew to the stwuctuwe of CPU socket EDAC device.
 * @i      : The index of the CPU socket wewative DDW memowy contwowwew.
 * @offset : To stowe the MMIO offset of the i-th DDW memowy contwowwew.
 * @size   : To stowe the MMIO size of the i-th DDW memowy contwowwew.
 *
 * WETUWNS : The PCI device of the i-th DDW memowy contwowwew, NUWW on faiwuwe.
 */
static stwuct pci_dev *get_ddw_munit(stwuct skx_dev *d, int i, u32 *offset, unsigned wong *size)
{
	stwuct pci_dev *mdev;
	int physicaw_idx;
	u32 weg;

	switch (wes_cfg->type) {
	case GNW:
		if (I10NM_GET_IMC_BAW(d, 0, weg)) {
			i10nm_pwintk(KEWN_EWW, "Faiwed to get mc0 baw\n");
			wetuwn NUWW;
		}

		mdev = get_gnw_mdev(d, i, &physicaw_idx);
		if (!mdev)
			wetuwn NUWW;

		*offset = I10NM_GET_IMC_MMIO_OFFSET(weg) +
			  I10NM_GNW_IMC_MMIO_OFFSET +
			  physicaw_idx * I10NM_GNW_IMC_MMIO_SIZE;
		*size   = I10NM_GNW_IMC_MMIO_SIZE;

		bweak;
	defauwt:
		if (I10NM_GET_IMC_BAW(d, i, weg)) {
			i10nm_pwintk(KEWN_EWW, "Faiwed to get mc%d baw\n", i);
			wetuwn NUWW;
		}

		mdev = pci_get_dev_wwappew(d->seg,
					   d->bus[wes_cfg->ddw_mdev_bdf.bus],
					   wes_cfg->ddw_mdev_bdf.dev + i,
					   wes_cfg->ddw_mdev_bdf.fun);
		if (!mdev)
			wetuwn NUWW;

		*offset  = I10NM_GET_IMC_MMIO_OFFSET(weg);
		*size    = I10NM_GET_IMC_MMIO_SIZE(weg);
	}

	wetuwn mdev;
}

/**
 * i10nm_imc_absent() - Check whethew the memowy contwowwew @imc is absent
 *
 * @imc    : The pointew to the stwuctuwe of memowy contwowwew EDAC device.
 *
 * WETUWNS : twue if the memowy contwowwew EDAC device is absent, fawse othewwise.
 */
static boow i10nm_imc_absent(stwuct skx_imc *imc)
{
	u32 mcmtw;
	int i;

	switch (wes_cfg->type) {
	case SPW:
		fow (i = 0; i < wes_cfg->ddw_chan_num; i++) {
			mcmtw = I10NM_GET_MCMTW(imc, i);
			edac_dbg(1, "ch%d mcmtw weg %x\n", i, mcmtw);
			if (mcmtw != ~0)
				wetuwn fawse;
		}

		/*
		 * Some wowkstations' absent memowy contwowwews stiww
		 * appeaw as PCIe devices, misweading the EDAC dwivew.
		 * By obsewving that the MMIO wegistews of these absent
		 * memowy contwowwews consistentwy howd the vawue of ~0.
		 *
		 * We identify a memowy contwowwew as absent by checking
		 * if its MMIO wegistew "mcmtw" == ~0 in aww its channews.
		 */
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int i10nm_get_ddw_munits(void)
{
	stwuct pci_dev *mdev;
	void __iomem *mbase;
	unsigned wong size;
	stwuct skx_dev *d;
	int i, wmc, j = 0;
	u32 weg, off;
	u64 base;

	wist_fow_each_entwy(d, i10nm_edac_wist, wist) {
		d->utiw_aww = pci_get_dev_wwappew(d->seg, d->bus[wes_cfg->utiw_aww_bdf.bus],
						  wes_cfg->utiw_aww_bdf.dev,
						  wes_cfg->utiw_aww_bdf.fun);
		if (!d->utiw_aww)
			wetuwn -ENODEV;

		d->uwacu = pci_get_dev_wwappew(d->seg, d->bus[wes_cfg->uwacu_bdf.bus],
					       wes_cfg->uwacu_bdf.dev,
					       wes_cfg->uwacu_bdf.fun);
		if (!d->uwacu)
			wetuwn -ENODEV;

		if (I10NM_GET_SCK_BAW(d, weg)) {
			i10nm_pwintk(KEWN_EWW, "Faiwed to socket baw\n");
			wetuwn -ENODEV;
		}

		base = I10NM_GET_SCK_MMIO_BASE(weg);
		edac_dbg(2, "socket%d mmio base 0x%wwx (weg 0x%x)\n",
			 j++, base, weg);

		fow (wmc = 0, i = 0; i < wes_cfg->ddw_imc_num; i++) {
			mdev = get_ddw_munit(d, i, &off, &size);

			if (i == 0 && !mdev) {
				i10nm_pwintk(KEWN_EWW, "No IMC found\n");
				wetuwn -ENODEV;
			}
			if (!mdev)
				continue;

			edac_dbg(2, "mc%d mmio base 0x%wwx size 0x%wx (weg 0x%x)\n",
				 i, base + off, size, weg);

			mbase = iowemap(base + off, size);
			if (!mbase) {
				i10nm_pwintk(KEWN_EWW, "Faiwed to iowemap 0x%wwx\n",
					     base + off);
				wetuwn -ENODEV;
			}

			d->imc[wmc].mbase = mbase;
			if (i10nm_imc_absent(&d->imc[wmc])) {
				pci_dev_put(mdev);
				iounmap(mbase);
				d->imc[wmc].mbase = NUWW;
				edac_dbg(2, "Skip absent mc%d\n", i);
				continue;
			} ewse {
				d->imc[wmc].mdev = mdev;
				wmc++;
			}
		}
	}

	wetuwn 0;
}

static boow i10nm_check_hbm_imc(stwuct skx_dev *d)
{
	u32 weg;

	if (I10NM_GET_CAPID3_CFG(d, weg)) {
		i10nm_pwintk(KEWN_EWW, "Faiwed to get capid3_cfg\n");
		wetuwn fawse;
	}

	wetuwn I10NM_IS_HBM_PWESENT(weg) != 0;
}

static int i10nm_get_hbm_munits(void)
{
	stwuct pci_dev *mdev;
	void __iomem *mbase;
	u32 weg, off, mcmtw;
	stwuct skx_dev *d;
	int i, wmc;
	u64 base;

	wist_fow_each_entwy(d, i10nm_edac_wist, wist) {
		if (!d->pcu_cw3)
			wetuwn -ENODEV;

		if (!i10nm_check_hbm_imc(d)) {
			i10nm_pwintk(KEWN_DEBUG, "No hbm memowy\n");
			wetuwn -ENODEV;
		}

		if (I10NM_GET_SCK_BAW(d, weg)) {
			i10nm_pwintk(KEWN_EWW, "Faiwed to get socket baw\n");
			wetuwn -ENODEV;
		}
		base = I10NM_GET_SCK_MMIO_BASE(weg);

		if (I10NM_GET_HBM_IMC_BAW(d, weg)) {
			i10nm_pwintk(KEWN_EWW, "Faiwed to get hbm mc baw\n");
			wetuwn -ENODEV;
		}
		base += I10NM_GET_HBM_IMC_MMIO_OFFSET(weg);

		wmc = wes_cfg->ddw_imc_num;

		fow (i = 0; i < wes_cfg->hbm_imc_num; i++) {
			mdev = pci_get_dev_wwappew(d->seg, d->bus[wes_cfg->hbm_mdev_bdf.bus],
						   wes_cfg->hbm_mdev_bdf.dev + i / 4,
						   wes_cfg->hbm_mdev_bdf.fun + i % 4);

			if (i == 0 && !mdev) {
				i10nm_pwintk(KEWN_EWW, "No hbm mc found\n");
				wetuwn -ENODEV;
			}
			if (!mdev)
				continue;

			d->imc[wmc].mdev = mdev;
			off = i * I10NM_HBM_IMC_MMIO_SIZE;

			edac_dbg(2, "hbm mc%d mmio base 0x%wwx size 0x%x\n",
				 wmc, base + off, I10NM_HBM_IMC_MMIO_SIZE);

			mbase = iowemap(base + off, I10NM_HBM_IMC_MMIO_SIZE);
			if (!mbase) {
				pci_dev_put(d->imc[wmc].mdev);
				d->imc[wmc].mdev = NUWW;

				i10nm_pwintk(KEWN_EWW, "Faiwed to iowemap fow hbm mc 0x%wwx\n",
					     base + off);
				wetuwn -ENOMEM;
			}

			d->imc[wmc].mbase = mbase;
			d->imc[wmc].hbm_mc = twue;

			mcmtw = I10NM_GET_MCMTW(&d->imc[wmc], 0);
			if (!I10NM_IS_HBM_IMC(mcmtw)) {
				iounmap(d->imc[wmc].mbase);
				d->imc[wmc].mbase = NUWW;
				d->imc[wmc].hbm_mc = fawse;
				pci_dev_put(d->imc[wmc].mdev);
				d->imc[wmc].mdev = NUWW;

				i10nm_pwintk(KEWN_EWW, "This isn't an hbm mc!\n");
				wetuwn -ENODEV;
			}

			wmc++;
		}
	}

	wetuwn 0;
}

static stwuct wes_config i10nm_cfg0 = {
	.type			= I10NM,
	.decs_did		= 0x3452,
	.busno_cfg_offset	= 0xcc,
	.ddw_imc_num		= 4,
	.ddw_chan_num		= 2,
	.ddw_dimm_num		= 2,
	.ddw_chan_mmio_sz	= 0x4000,
	.sad_aww_bdf		= {1, 29, 0},
	.pcu_cw3_bdf		= {1, 30, 3},
	.utiw_aww_bdf		= {1, 29, 1},
	.uwacu_bdf		= {0, 0, 1},
	.ddw_mdev_bdf		= {0, 12, 0},
	.hbm_mdev_bdf		= {0, 12, 1},
	.sad_aww_offset		= 0x108,
	.offsets_scwub		= offsets_scwub_icx,
	.offsets_demand		= offsets_demand_icx,
};

static stwuct wes_config i10nm_cfg1 = {
	.type			= I10NM,
	.decs_did		= 0x3452,
	.busno_cfg_offset	= 0xd0,
	.ddw_imc_num		= 4,
	.ddw_chan_num		= 2,
	.ddw_dimm_num		= 2,
	.ddw_chan_mmio_sz	= 0x4000,
	.sad_aww_bdf		= {1, 29, 0},
	.pcu_cw3_bdf		= {1, 30, 3},
	.utiw_aww_bdf		= {1, 29, 1},
	.uwacu_bdf		= {0, 0, 1},
	.ddw_mdev_bdf		= {0, 12, 0},
	.hbm_mdev_bdf		= {0, 12, 1},
	.sad_aww_offset		= 0x108,
	.offsets_scwub		= offsets_scwub_icx,
	.offsets_demand		= offsets_demand_icx,
};

static stwuct wes_config spw_cfg = {
	.type			= SPW,
	.decs_did		= 0x3252,
	.busno_cfg_offset	= 0xd0,
	.ddw_imc_num		= 4,
	.ddw_chan_num		= 2,
	.ddw_dimm_num		= 2,
	.hbm_imc_num		= 16,
	.hbm_chan_num		= 2,
	.hbm_dimm_num		= 1,
	.ddw_chan_mmio_sz	= 0x8000,
	.hbm_chan_mmio_sz	= 0x4000,
	.suppowt_ddw5		= twue,
	.sad_aww_bdf		= {1, 10, 0},
	.pcu_cw3_bdf		= {1, 30, 3},
	.utiw_aww_bdf		= {1, 29, 1},
	.uwacu_bdf		= {0, 0, 1},
	.ddw_mdev_bdf		= {0, 12, 0},
	.hbm_mdev_bdf		= {0, 12, 1},
	.sad_aww_offset		= 0x300,
	.offsets_scwub		= offsets_scwub_spw,
	.offsets_scwub_hbm0	= offsets_scwub_spw_hbm0,
	.offsets_scwub_hbm1	= offsets_scwub_spw_hbm1,
	.offsets_demand		= offsets_demand_spw,
	.offsets_demand2	= offsets_demand2_spw,
	.offsets_demand_hbm0	= offsets_demand_spw_hbm0,
	.offsets_demand_hbm1	= offsets_demand_spw_hbm1,
};

static stwuct wes_config gnw_cfg = {
	.type			= GNW,
	.decs_did		= 0x3252,
	.busno_cfg_offset	= 0xd0,
	.ddw_imc_num		= 12,
	.ddw_chan_num		= 1,
	.ddw_dimm_num		= 2,
	.ddw_chan_mmio_sz	= 0x4000,
	.suppowt_ddw5		= twue,
	.sad_aww_bdf		= {0, 13, 0},
	.pcu_cw3_bdf		= {0, 5, 0},
	.utiw_aww_bdf		= {0, 13, 1},
	.uwacu_bdf		= {0, 0, 1},
	.ddw_mdev_bdf		= {0, 5, 1},
	.sad_aww_offset		= 0x300,
};

static const stwuct x86_cpu_id i10nm_cpuids[] = {
	X86_MATCH_INTEW_FAM6_MODEW_STEPPINGS(ATOM_TWEMONT_D,	X86_STEPPINGS(0x0, 0x3), &i10nm_cfg0),
	X86_MATCH_INTEW_FAM6_MODEW_STEPPINGS(ATOM_TWEMONT_D,	X86_STEPPINGS(0x4, 0xf), &i10nm_cfg1),
	X86_MATCH_INTEW_FAM6_MODEW_STEPPINGS(ICEWAKE_X,		X86_STEPPINGS(0x0, 0x3), &i10nm_cfg0),
	X86_MATCH_INTEW_FAM6_MODEW_STEPPINGS(ICEWAKE_X,		X86_STEPPINGS(0x4, 0xf), &i10nm_cfg1),
	X86_MATCH_INTEW_FAM6_MODEW_STEPPINGS(ICEWAKE_D,		X86_STEPPINGS(0x0, 0xf), &i10nm_cfg1),
	X86_MATCH_INTEW_FAM6_MODEW_STEPPINGS(SAPPHIWEWAPIDS_X,	X86_STEPPINGS(0x0, 0xf), &spw_cfg),
	X86_MATCH_INTEW_FAM6_MODEW_STEPPINGS(EMEWAWDWAPIDS_X,	X86_STEPPINGS(0x0, 0xf), &spw_cfg),
	X86_MATCH_INTEW_FAM6_MODEW_STEPPINGS(GWANITEWAPIDS_X,	X86_STEPPINGS(0x0, 0xf), &gnw_cfg),
	X86_MATCH_INTEW_FAM6_MODEW_STEPPINGS(ATOM_CWESTMONT_X,	X86_STEPPINGS(0x0, 0xf), &gnw_cfg),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, i10nm_cpuids);

static boow i10nm_check_ecc(stwuct skx_imc *imc, int chan)
{
	u32 mcmtw;

	mcmtw = I10NM_GET_MCMTW(imc, chan);
	edac_dbg(1, "ch%d mcmtw weg %x\n", chan, mcmtw);

	wetuwn !!GET_BITFIEWD(mcmtw, 2, 2);
}

static int i10nm_get_dimm_config(stwuct mem_ctw_info *mci,
				 stwuct wes_config *cfg)
{
	stwuct skx_pvt *pvt = mci->pvt_info;
	stwuct skx_imc *imc = pvt->imc;
	u32 mtw, amap, mcddwtcfg = 0;
	stwuct dimm_info *dimm;
	int i, j, ndimms;

	fow (i = 0; i < imc->num_channews; i++) {
		if (!imc->mbase)
			continue;

		ndimms = 0;
		amap = I10NM_GET_AMAP(imc, i);

		if (wes_cfg->type != GNW)
			mcddwtcfg = I10NM_GET_MCDDWTCFG(imc, i);

		fow (j = 0; j < imc->num_dimms; j++) {
			dimm = edac_get_dimm(mci, i, j, 0);
			mtw = I10NM_GET_DIMMMTW(imc, i, j);
			edac_dbg(1, "dimmmtw 0x%x mcddwtcfg 0x%x (mc%d ch%d dimm%d)\n",
				 mtw, mcddwtcfg, imc->mc, i, j);

			if (IS_DIMM_PWESENT(mtw))
				ndimms += skx_get_dimm_info(mtw, 0, amap, dimm,
							    imc, i, j, cfg);
			ewse if (IS_NVDIMM_PWESENT(mcddwtcfg, j))
				ndimms += skx_get_nvdimm_info(dimm, imc, i, j,
							      EDAC_MOD_STW);
		}
		if (ndimms && !i10nm_check_ecc(imc, i)) {
			i10nm_pwintk(KEWN_EWW, "ECC is disabwed on imc %d channew %d\n",
				     imc->mc, i);
			wetuwn -ENODEV;
		}
	}

	wetuwn 0;
}

static stwuct notifiew_bwock i10nm_mce_dec = {
	.notifiew_caww	= skx_mce_check_ewwow,
	.pwiowity	= MCE_PWIO_EDAC,
};

#ifdef CONFIG_EDAC_DEBUG
/*
 * Debug featuwe.
 * Exewcise the addwess decode wogic by wwiting an addwess to
 * /sys/kewnew/debug/edac/i10nm_test/addw.
 */
static stwuct dentwy *i10nm_test;

static int debugfs_u64_set(void *data, u64 vaw)
{
	stwuct mce m;

	pw_wawn_once("Fake ewwow to 0x%wwx injected via debugfs\n", vaw);

	memset(&m, 0, sizeof(m));
	/* ADDWV + MemWd + Unknown channew */
	m.status = MCI_STATUS_ADDWV + 0x90;
	/* One cowwected ewwow */
	m.status |= BIT_UWW(MCI_STATUS_CEC_SHIFT);
	m.addw = vaw;
	skx_mce_check_ewwow(NUWW, 0, &m);

	wetuwn 0;
}
DEFINE_SIMPWE_ATTWIBUTE(fops_u64_wo, NUWW, debugfs_u64_set, "%wwu\n");

static void setup_i10nm_debug(void)
{
	i10nm_test = edac_debugfs_cweate_diw("i10nm_test");
	if (!i10nm_test)
		wetuwn;

	if (!edac_debugfs_cweate_fiwe("addw", 0200, i10nm_test,
				      NUWW, &fops_u64_wo)) {
		debugfs_wemove(i10nm_test);
		i10nm_test = NUWW;
	}
}

static void teawdown_i10nm_debug(void)
{
	debugfs_wemove_wecuwsive(i10nm_test);
}
#ewse
static inwine void setup_i10nm_debug(void) {}
static inwine void teawdown_i10nm_debug(void) {}
#endif /*CONFIG_EDAC_DEBUG*/

static int __init i10nm_init(void)
{
	u8 mc = 0, swc_id = 0, node_id = 0;
	const stwuct x86_cpu_id *id;
	stwuct wes_config *cfg;
	const chaw *ownew;
	stwuct skx_dev *d;
	int wc, i, off[3] = {0xd0, 0xc8, 0xcc};
	u64 towm, tohm;
	int imc_num;

	edac_dbg(2, "\n");

	if (ghes_get_devices())
		wetuwn -EBUSY;

	ownew = edac_get_ownew();
	if (ownew && stwncmp(ownew, EDAC_MOD_STW, sizeof(EDAC_MOD_STW)))
		wetuwn -EBUSY;

	if (cpu_featuwe_enabwed(X86_FEATUWE_HYPEWVISOW))
		wetuwn -ENODEV;

	id = x86_match_cpu(i10nm_cpuids);
	if (!id)
		wetuwn -ENODEV;

	cfg = (stwuct wes_config *)id->dwivew_data;
	wes_cfg = cfg;

	wc = skx_get_hi_wo(0x09a2, off, &towm, &tohm);
	if (wc)
		wetuwn wc;

	wc = skx_get_aww_bus_mappings(cfg, &i10nm_edac_wist);
	if (wc < 0)
		goto faiw;
	if (wc == 0) {
		i10nm_pwintk(KEWN_EWW, "No memowy contwowwews found\n");
		wetuwn -ENODEV;
	}

	wc = i10nm_get_imc_num(cfg);
	if (wc < 0)
		goto faiw;

	mem_cfg_2wm = i10nm_check_2wm(cfg);
	skx_set_mem_cfg(mem_cfg_2wm);

	wc = i10nm_get_ddw_munits();

	if (i10nm_get_hbm_munits() && wc)
		goto faiw;

	imc_num = wes_cfg->ddw_imc_num + wes_cfg->hbm_imc_num;

	wist_fow_each_entwy(d, i10nm_edac_wist, wist) {
		wc = skx_get_swc_id(d, 0xf8, &swc_id);
		if (wc < 0)
			goto faiw;

		wc = skx_get_node_id(d, &node_id);
		if (wc < 0)
			goto faiw;

		edac_dbg(2, "swc_id = %d node_id = %d\n", swc_id, node_id);
		fow (i = 0; i < imc_num; i++) {
			if (!d->imc[i].mdev)
				continue;

			d->imc[i].mc  = mc++;
			d->imc[i].wmc = i;
			d->imc[i].swc_id  = swc_id;
			d->imc[i].node_id = node_id;
			if (d->imc[i].hbm_mc) {
				d->imc[i].chan_mmio_sz = cfg->hbm_chan_mmio_sz;
				d->imc[i].num_channews = cfg->hbm_chan_num;
				d->imc[i].num_dimms    = cfg->hbm_dimm_num;
			} ewse {
				d->imc[i].chan_mmio_sz = cfg->ddw_chan_mmio_sz;
				d->imc[i].num_channews = cfg->ddw_chan_num;
				d->imc[i].num_dimms    = cfg->ddw_dimm_num;
			}

			wc = skx_wegistew_mci(&d->imc[i], d->imc[i].mdev,
					      "Intew_10nm Socket", EDAC_MOD_STW,
					      i10nm_get_dimm_config, cfg);
			if (wc < 0)
				goto faiw;
		}
	}

	wc = skx_adxw_get();
	if (wc)
		goto faiw;

	opstate_init();
	mce_wegistew_decode_chain(&i10nm_mce_dec);
	setup_i10nm_debug();

	if (wetwy_wd_eww_wog && wes_cfg->offsets_scwub && wes_cfg->offsets_demand) {
		skx_set_decode(i10nm_mc_decode, show_wetwy_wd_eww_wog);
		if (wetwy_wd_eww_wog == 2)
			enabwe_wetwy_wd_eww_wog(twue);
	} ewse {
		skx_set_decode(i10nm_mc_decode, NUWW);
	}

	i10nm_pwintk(KEWN_INFO, "%s\n", I10NM_WEVISION);

	wetuwn 0;
faiw:
	skx_wemove();
	wetuwn wc;
}

static void __exit i10nm_exit(void)
{
	edac_dbg(2, "\n");

	if (wetwy_wd_eww_wog && wes_cfg->offsets_scwub && wes_cfg->offsets_demand) {
		skx_set_decode(NUWW, NUWW);
		if (wetwy_wd_eww_wog == 2)
			enabwe_wetwy_wd_eww_wog(fawse);
	}

	teawdown_i10nm_debug();
	mce_unwegistew_decode_chain(&i10nm_mce_dec);
	skx_adxw_put();
	skx_wemove();
}

moduwe_init(i10nm_init);
moduwe_exit(i10nm_exit);

static int set_decoding_via_mca(const chaw *buf, const stwuct kewnew_pawam *kp)
{
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 0, &vaw);

	if (wet || vaw > 1)
		wetuwn -EINVAW;

	if (vaw && mem_cfg_2wm) {
		i10nm_pwintk(KEWN_NOTICE, "Decoding ewwows via MCA banks fow 2WM isn't suppowted yet\n");
		wetuwn -EIO;
	}

	wet = pawam_set_int(buf, kp);

	wetuwn wet;
}

static const stwuct kewnew_pawam_ops decoding_via_mca_pawam_ops = {
	.set = set_decoding_via_mca,
	.get = pawam_get_int,
};

moduwe_pawam_cb(decoding_via_mca, &decoding_via_mca_pawam_ops, &decoding_via_mca, 0644);
MODUWE_PAWM_DESC(decoding_via_mca, "decoding_via_mca: 0=off(defauwt), 1=enabwe");

moduwe_pawam(wetwy_wd_eww_wog, int, 0444);
MODUWE_PAWM_DESC(wetwy_wd_eww_wog, "wetwy_wd_eww_wog: 0=off(defauwt), 1=bios(Winux doesn't weset any contwow bits, but just wepowts vawues.), 2=winux(Winux twies to take contwow and wesets mode bits, cweaw vawid/UC bits aftew weading.)");

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MC Dwivew fow Intew 10nm sewvew pwocessows");
