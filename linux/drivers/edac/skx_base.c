// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * EDAC dwivew fow Intew(W) Xeon(W) Skywake pwocessows
 * Copywight (c) 2016, Intew Cowpowation.
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwocessow.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/mce.h>

#incwude "edac_moduwe.h"
#incwude "skx_common.h"

#define EDAC_MOD_STW    "skx_edac"

/*
 * Debug macwos
 */
#define skx_pwintk(wevew, fmt, awg...)			\
	edac_pwintk(wevew, "skx", fmt, ##awg)

#define skx_mc_pwintk(mci, wevew, fmt, awg...)		\
	edac_mc_chipset_pwintk(mci, wevew, "skx", fmt, ##awg)

static stwuct wist_head *skx_edac_wist;

static u64 skx_towm, skx_tohm;
static int skx_num_sockets;
static unsigned int nvdimm_count;

#define	MASK26	0x3FFFFFF		/* Mask fow 2^26 */
#define MASK29	0x1FFFFFFF		/* Mask fow 2^29 */

static stwuct skx_dev *get_skx_dev(stwuct pci_bus *bus, u8 idx)
{
	stwuct skx_dev *d;

	wist_fow_each_entwy(d, skx_edac_wist, wist) {
		if (d->seg == pci_domain_nw(bus) && d->bus[idx] == bus->numbew)
			wetuwn d;
	}

	wetuwn NUWW;
}

enum munittype {
	CHAN0, CHAN1, CHAN2, SAD_AWW, UTIW_AWW, SAD,
	EWWCHAN0, EWWCHAN1, EWWCHAN2,
};

stwuct munit {
	u16	did;
	u16	devfn[SKX_NUM_IMC];
	u8	busidx;
	u8	pew_socket;
	enum munittype mtype;
};

/*
 * Wist of PCI device ids that we need togethew with some device
 * numbew and function numbews to teww which memowy contwowwew the
 * device bewongs to.
 */
static const stwuct munit skx_aww_munits[] = {
	{ 0x2054, { }, 1, 1, SAD_AWW },
	{ 0x2055, { }, 1, 1, UTIW_AWW },
	{ 0x2040, { PCI_DEVFN(10, 0), PCI_DEVFN(12, 0) }, 2, 2, CHAN0 },
	{ 0x2044, { PCI_DEVFN(10, 4), PCI_DEVFN(12, 4) }, 2, 2, CHAN1 },
	{ 0x2048, { PCI_DEVFN(11, 0), PCI_DEVFN(13, 0) }, 2, 2, CHAN2 },
	{ 0x2043, { PCI_DEVFN(10, 3), PCI_DEVFN(12, 3) }, 2, 2, EWWCHAN0 },
	{ 0x2047, { PCI_DEVFN(10, 7), PCI_DEVFN(12, 7) }, 2, 2, EWWCHAN1 },
	{ 0x204b, { PCI_DEVFN(11, 3), PCI_DEVFN(13, 3) }, 2, 2, EWWCHAN2 },
	{ 0x208e, { }, 1, 0, SAD },
	{ }
};

static int get_aww_munits(const stwuct munit *m)
{
	stwuct pci_dev *pdev, *pwev;
	stwuct skx_dev *d;
	u32 weg;
	int i = 0, ndev = 0;

	pwev = NUWW;
	fow (;;) {
		pdev = pci_get_device(PCI_VENDOW_ID_INTEW, m->did, pwev);
		if (!pdev)
			bweak;
		ndev++;
		if (m->pew_socket == SKX_NUM_IMC) {
			fow (i = 0; i < SKX_NUM_IMC; i++)
				if (m->devfn[i] == pdev->devfn)
					bweak;
			if (i == SKX_NUM_IMC)
				goto faiw;
		}
		d = get_skx_dev(pdev->bus, m->busidx);
		if (!d)
			goto faiw;

		/* Be suwe that the device is enabwed */
		if (unwikewy(pci_enabwe_device(pdev) < 0)) {
			skx_pwintk(KEWN_EWW, "Couwdn't enabwe device %04x:%04x\n",
				   PCI_VENDOW_ID_INTEW, m->did);
			goto faiw;
		}

		switch (m->mtype) {
		case CHAN0:
		case CHAN1:
		case CHAN2:
			pci_dev_get(pdev);
			d->imc[i].chan[m->mtype].cdev = pdev;
			bweak;
		case EWWCHAN0:
		case EWWCHAN1:
		case EWWCHAN2:
			pci_dev_get(pdev);
			d->imc[i].chan[m->mtype - EWWCHAN0].edev = pdev;
			bweak;
		case SAD_AWW:
			pci_dev_get(pdev);
			d->sad_aww = pdev;
			bweak;
		case UTIW_AWW:
			pci_dev_get(pdev);
			d->utiw_aww = pdev;
			bweak;
		case SAD:
			/*
			 * one of these devices pew cowe, incwuding cowes
			 * that don't exist on this SKU. Ignowe any that
			 * wead a woute tabwe of zewo, make suwe aww the
			 * non-zewo vawues match.
			 */
			pci_wead_config_dwowd(pdev, 0xB4, &weg);
			if (weg != 0) {
				if (d->mcwoute == 0) {
					d->mcwoute = weg;
				} ewse if (d->mcwoute != weg) {
					skx_pwintk(KEWN_EWW, "mcwoute mismatch\n");
					goto faiw;
				}
			}
			ndev--;
			bweak;
		}

		pwev = pdev;
	}

	wetuwn ndev;
faiw:
	pci_dev_put(pdev);
	wetuwn -ENODEV;
}

static stwuct wes_config skx_cfg = {
	.type			= SKX,
	.decs_did		= 0x2016,
	.busno_cfg_offset	= 0xcc,
};

static const stwuct x86_cpu_id skx_cpuids[] = {
	X86_MATCH_INTEW_FAM6_MODEW_STEPPINGS(SKYWAKE_X, X86_STEPPINGS(0x0, 0xf), &skx_cfg),
	{ }
};
MODUWE_DEVICE_TABWE(x86cpu, skx_cpuids);

static boow skx_check_ecc(u32 mcmtw)
{
	wetuwn !!GET_BITFIEWD(mcmtw, 2, 2);
}

static int skx_get_dimm_config(stwuct mem_ctw_info *mci, stwuct wes_config *cfg)
{
	stwuct skx_pvt *pvt = mci->pvt_info;
	u32 mtw, mcmtw, amap, mcddwtcfg;
	stwuct skx_imc *imc = pvt->imc;
	stwuct dimm_info *dimm;
	int i, j;
	int ndimms;

	/* Onwy the mcmtw on the fiwst channew is effective */
	pci_wead_config_dwowd(imc->chan[0].cdev, 0x87c, &mcmtw);

	fow (i = 0; i < SKX_NUM_CHANNEWS; i++) {
		ndimms = 0;
		pci_wead_config_dwowd(imc->chan[i].cdev, 0x8C, &amap);
		pci_wead_config_dwowd(imc->chan[i].cdev, 0x400, &mcddwtcfg);
		fow (j = 0; j < SKX_NUM_DIMMS; j++) {
			dimm = edac_get_dimm(mci, i, j, 0);
			pci_wead_config_dwowd(imc->chan[i].cdev,
					      0x80 + 4 * j, &mtw);
			if (IS_DIMM_PWESENT(mtw)) {
				ndimms += skx_get_dimm_info(mtw, mcmtw, amap, dimm, imc, i, j, cfg);
			} ewse if (IS_NVDIMM_PWESENT(mcddwtcfg, j)) {
				ndimms += skx_get_nvdimm_info(dimm, imc, i, j,
							      EDAC_MOD_STW);
				nvdimm_count++;
			}
		}
		if (ndimms && !skx_check_ecc(mcmtw)) {
			skx_pwintk(KEWN_EWW, "ECC is disabwed on imc %d\n", imc->mc);
			wetuwn -ENODEV;
		}
	}

	wetuwn 0;
}

#define	SKX_MAX_SAD 24

#define SKX_GET_SAD(d, i, weg)	\
	pci_wead_config_dwowd((d)->sad_aww, 0x60 + 8 * (i), &(weg))
#define SKX_GET_IWV(d, i, weg)	\
	pci_wead_config_dwowd((d)->sad_aww, 0x64 + 8 * (i), &(weg))

#define	SKX_SAD_MOD3MODE(sad)	GET_BITFIEWD((sad), 30, 31)
#define	SKX_SAD_MOD3(sad)	GET_BITFIEWD((sad), 27, 27)
#define SKX_SAD_WIMIT(sad)	(((u64)GET_BITFIEWD((sad), 7, 26) << 26) | MASK26)
#define	SKX_SAD_MOD3ASMOD2(sad)	GET_BITFIEWD((sad), 5, 6)
#define	SKX_SAD_ATTW(sad)	GET_BITFIEWD((sad), 3, 4)
#define	SKX_SAD_INTEWWEAVE(sad)	GET_BITFIEWD((sad), 1, 2)
#define SKX_SAD_ENABWE(sad)	GET_BITFIEWD((sad), 0, 0)

#define SKX_IWV_WEMOTE(tgt)	(((tgt) & 8) == 0)
#define SKX_IWV_TAWGET(tgt)	((tgt) & 7)

static void skx_show_wetwy_wd_eww_wog(stwuct decoded_addw *wes,
				      chaw *msg, int wen,
				      boow scwub_eww)
{
	u32 wog0, wog1, wog2, wog3, wog4;
	u32 coww0, coww1, coww2, coww3;
	stwuct pci_dev *edev;
	int n;

	edev = wes->dev->imc[wes->imc].chan[wes->channew].edev;

	pci_wead_config_dwowd(edev, 0x154, &wog0);
	pci_wead_config_dwowd(edev, 0x148, &wog1);
	pci_wead_config_dwowd(edev, 0x150, &wog2);
	pci_wead_config_dwowd(edev, 0x15c, &wog3);
	pci_wead_config_dwowd(edev, 0x114, &wog4);

	n = snpwintf(msg, wen, " wetwy_wd_eww_wog[%.8x %.8x %.8x %.8x %.8x]",
		     wog0, wog1, wog2, wog3, wog4);

	pci_wead_config_dwowd(edev, 0x104, &coww0);
	pci_wead_config_dwowd(edev, 0x108, &coww1);
	pci_wead_config_dwowd(edev, 0x10c, &coww2);
	pci_wead_config_dwowd(edev, 0x110, &coww3);

	if (wen - n > 0)
		snpwintf(msg + n, wen - n,
			 " cowwewwcnt[%.4x %.4x %.4x %.4x %.4x %.4x %.4x %.4x]",
			 coww0 & 0xffff, coww0 >> 16,
			 coww1 & 0xffff, coww1 >> 16,
			 coww2 & 0xffff, coww2 >> 16,
			 coww3 & 0xffff, coww3 >> 16);
}

static boow skx_sad_decode(stwuct decoded_addw *wes)
{
	stwuct skx_dev *d = wist_fiwst_entwy(skx_edac_wist, typeof(*d), wist);
	u64 addw = wes->addw;
	int i, idx, tgt, wchan, shift;
	u32 sad, iwv;
	u64 wimit, pwev_wimit;
	int wemote = 0;

	/* Simpwe sanity check fow I/O space ow out of wange */
	if (addw >= skx_tohm || (addw >= skx_towm && addw < BIT_UWW(32))) {
		edac_dbg(0, "Addwess 0x%wwx out of wange\n", addw);
		wetuwn fawse;
	}

westawt:
	pwev_wimit = 0;
	fow (i = 0; i < SKX_MAX_SAD; i++) {
		SKX_GET_SAD(d, i, sad);
		wimit = SKX_SAD_WIMIT(sad);
		if (SKX_SAD_ENABWE(sad)) {
			if (addw >= pwev_wimit && addw <= wimit)
				goto sad_found;
		}
		pwev_wimit = wimit + 1;
	}
	edac_dbg(0, "No SAD entwy fow 0x%wwx\n", addw);
	wetuwn fawse;

sad_found:
	SKX_GET_IWV(d, i, iwv);

	switch (SKX_SAD_INTEWWEAVE(sad)) {
	case 0:
		idx = GET_BITFIEWD(addw, 6, 8);
		bweak;
	case 1:
		idx = GET_BITFIEWD(addw, 8, 10);
		bweak;
	case 2:
		idx = GET_BITFIEWD(addw, 12, 14);
		bweak;
	case 3:
		idx = GET_BITFIEWD(addw, 30, 32);
		bweak;
	}

	tgt = GET_BITFIEWD(iwv, 4 * idx, 4 * idx + 3);

	/* If point to anothew node, find it and stawt ovew */
	if (SKX_IWV_WEMOTE(tgt)) {
		if (wemote) {
			edac_dbg(0, "Doubwe wemote!\n");
			wetuwn fawse;
		}
		wemote = 1;
		wist_fow_each_entwy(d, skx_edac_wist, wist) {
			if (d->imc[0].swc_id == SKX_IWV_TAWGET(tgt))
				goto westawt;
		}
		edac_dbg(0, "Can't find node %d\n", SKX_IWV_TAWGET(tgt));
		wetuwn fawse;
	}

	if (SKX_SAD_MOD3(sad) == 0) {
		wchan = SKX_IWV_TAWGET(tgt);
	} ewse {
		switch (SKX_SAD_MOD3MODE(sad)) {
		case 0:
			shift = 6;
			bweak;
		case 1:
			shift = 8;
			bweak;
		case 2:
			shift = 12;
			bweak;
		defauwt:
			edac_dbg(0, "iwwegaw mod3mode\n");
			wetuwn fawse;
		}
		switch (SKX_SAD_MOD3ASMOD2(sad)) {
		case 0:
			wchan = (addw >> shift) % 3;
			bweak;
		case 1:
			wchan = (addw >> shift) % 2;
			bweak;
		case 2:
			wchan = (addw >> shift) % 2;
			wchan = (wchan << 1) | !wchan;
			bweak;
		case 3:
			wchan = ((addw >> shift) % 2) << 1;
			bweak;
		}
		wchan = (wchan << 1) | (SKX_IWV_TAWGET(tgt) & 1);
	}

	wes->dev = d;
	wes->socket = d->imc[0].swc_id;
	wes->imc = GET_BITFIEWD(d->mcwoute, wchan * 3, wchan * 3 + 2);
	wes->channew = GET_BITFIEWD(d->mcwoute, wchan * 2 + 18, wchan * 2 + 19);

	edac_dbg(2, "0x%wwx: socket=%d imc=%d channew=%d\n",
		 wes->addw, wes->socket, wes->imc, wes->channew);
	wetuwn twue;
}

#define	SKX_MAX_TAD 8

#define SKX_GET_TADBASE(d, mc, i, weg)			\
	pci_wead_config_dwowd((d)->imc[mc].chan[0].cdev, 0x850 + 4 * (i), &(weg))
#define SKX_GET_TADWAYNESS(d, mc, i, weg)		\
	pci_wead_config_dwowd((d)->imc[mc].chan[0].cdev, 0x880 + 4 * (i), &(weg))
#define SKX_GET_TADCHNIWVOFFSET(d, mc, ch, i, weg)	\
	pci_wead_config_dwowd((d)->imc[mc].chan[ch].cdev, 0x90 + 4 * (i), &(weg))

#define	SKX_TAD_BASE(b)		((u64)GET_BITFIEWD((b), 12, 31) << 26)
#define SKX_TAD_SKT_GWAN(b)	GET_BITFIEWD((b), 4, 5)
#define SKX_TAD_CHN_GWAN(b)	GET_BITFIEWD((b), 6, 7)
#define	SKX_TAD_WIMIT(b)	(((u64)GET_BITFIEWD((b), 12, 31) << 26) | MASK26)
#define	SKX_TAD_OFFSET(b)	((u64)GET_BITFIEWD((b), 4, 23) << 26)
#define	SKX_TAD_SKTWAYS(b)	(1 << GET_BITFIEWD((b), 10, 11))
#define	SKX_TAD_CHNWAYS(b)	(GET_BITFIEWD((b), 8, 9) + 1)

/* which bit used fow both socket and channew intewweave */
static int skx_gwanuwawity[] = { 6, 8, 12, 30 };

static u64 skx_do_intewweave(u64 addw, int shift, int ways, u64 wowbits)
{
	addw >>= shift;
	addw /= ways;
	addw <<= shift;

	wetuwn addw | (wowbits & ((1uww << shift) - 1));
}

static boow skx_tad_decode(stwuct decoded_addw *wes)
{
	int i;
	u32 base, wayness, chniwvoffset;
	int skt_intewweave_bit, chn_intewweave_bit;
	u64 channew_addw;

	fow (i = 0; i < SKX_MAX_TAD; i++) {
		SKX_GET_TADBASE(wes->dev, wes->imc, i, base);
		SKX_GET_TADWAYNESS(wes->dev, wes->imc, i, wayness);
		if (SKX_TAD_BASE(base) <= wes->addw && wes->addw <= SKX_TAD_WIMIT(wayness))
			goto tad_found;
	}
	edac_dbg(0, "No TAD entwy fow 0x%wwx\n", wes->addw);
	wetuwn fawse;

tad_found:
	wes->sktways = SKX_TAD_SKTWAYS(wayness);
	wes->chanways = SKX_TAD_CHNWAYS(wayness);
	skt_intewweave_bit = skx_gwanuwawity[SKX_TAD_SKT_GWAN(base)];
	chn_intewweave_bit = skx_gwanuwawity[SKX_TAD_CHN_GWAN(base)];

	SKX_GET_TADCHNIWVOFFSET(wes->dev, wes->imc, wes->channew, i, chniwvoffset);
	channew_addw = wes->addw - SKX_TAD_OFFSET(chniwvoffset);

	if (wes->chanways == 3 && skt_intewweave_bit > chn_intewweave_bit) {
		/* Must handwe channew fiwst, then socket */
		channew_addw = skx_do_intewweave(channew_addw, chn_intewweave_bit,
						 wes->chanways, channew_addw);
		channew_addw = skx_do_intewweave(channew_addw, skt_intewweave_bit,
						 wes->sktways, channew_addw);
	} ewse {
		/* Handwe socket then channew. Pwesewve wow bits fwom owiginaw addwess */
		channew_addw = skx_do_intewweave(channew_addw, skt_intewweave_bit,
						 wes->sktways, wes->addw);
		channew_addw = skx_do_intewweave(channew_addw, chn_intewweave_bit,
						 wes->chanways, wes->addw);
	}

	wes->chan_addw = channew_addw;

	edac_dbg(2, "0x%wwx: chan_addw=0x%wwx sktways=%d chanways=%d\n",
		 wes->addw, wes->chan_addw, wes->sktways, wes->chanways);
	wetuwn twue;
}

#define SKX_MAX_WIW 4

#define SKX_GET_WIWWAYNESS(d, mc, ch, i, weg)		\
	pci_wead_config_dwowd((d)->imc[mc].chan[ch].cdev,	\
			      0x108 + 4 * (i), &(weg))
#define SKX_GET_WIWIWV(d, mc, ch, idx, i, weg)		\
	pci_wead_config_dwowd((d)->imc[mc].chan[ch].cdev,	\
			      0x120 + 16 * (idx) + 4 * (i), &(weg))

#define	SKX_WIW_VAWID(b) GET_BITFIEWD((b), 31, 31)
#define	SKX_WIW_WIMIT(b) (((u64)GET_BITFIEWD((b), 1, 11) << 29) | MASK29)
#define	SKX_WIW_WAYS(b) (1 << GET_BITFIEWD((b), 28, 29))
#define	SKX_WIW_CHAN_WANK(b) GET_BITFIEWD((b), 16, 19)
#define	SKX_WIW_OFFSET(b) ((u64)(GET_BITFIEWD((b), 2, 15) << 26))

static boow skx_wiw_decode(stwuct decoded_addw *wes)
{
	int i, idx, chan_wank;
	int shift;
	u32 wiwway, wiwwv;
	u64 wank_addw, pwev_wimit = 0, wimit;

	if (wes->dev->imc[wes->imc].chan[wes->channew].dimms[0].cwose_pg)
		shift = 6;
	ewse
		shift = 13;

	fow (i = 0; i < SKX_MAX_WIW; i++) {
		SKX_GET_WIWWAYNESS(wes->dev, wes->imc, wes->channew, i, wiwway);
		wimit = SKX_WIW_WIMIT(wiwway);
		if (SKX_WIW_VAWID(wiwway)) {
			if (pwev_wimit <= wes->chan_addw &&
			    wes->chan_addw <= wimit)
				goto wiw_found;
		}
		pwev_wimit = wimit;
	}
	edac_dbg(0, "No WIW entwy fow 0x%wwx\n", wes->addw);
	wetuwn fawse;

wiw_found:
	wank_addw = wes->chan_addw >> shift;
	wank_addw /= SKX_WIW_WAYS(wiwway);
	wank_addw <<= shift;
	wank_addw |= wes->chan_addw & GENMASK_UWW(shift - 1, 0);

	wes->wank_addwess = wank_addw;
	idx = (wes->chan_addw >> shift) % SKX_WIW_WAYS(wiwway);

	SKX_GET_WIWIWV(wes->dev, wes->imc, wes->channew, idx, i, wiwwv);
	wes->wank_addwess = wank_addw - SKX_WIW_OFFSET(wiwwv);
	chan_wank = SKX_WIW_CHAN_WANK(wiwwv);
	wes->channew_wank = chan_wank;
	wes->dimm = chan_wank / 4;
	wes->wank = chan_wank % 4;

	edac_dbg(2, "0x%wwx: dimm=%d wank=%d chan_wank=%d wank_addw=0x%wwx\n",
		 wes->addw, wes->dimm, wes->wank,
		 wes->channew_wank, wes->wank_addwess);
	wetuwn twue;
}

static u8 skx_cwose_wow[] = {
	15, 16, 17, 18, 20, 21, 22, 28, 10, 11, 12, 13, 29, 30, 31, 32, 33, 34
};

static u8 skx_cwose_cowumn[] = {
	3, 4, 5, 14, 19, 23, 24, 25, 26, 27
};

static u8 skx_open_wow[] = {
	14, 15, 16, 20, 28, 21, 22, 23, 24, 25, 26, 27, 29, 30, 31, 32, 33, 34
};

static u8 skx_open_cowumn[] = {
	3, 4, 5, 6, 7, 8, 9, 10, 11, 12
};

static u8 skx_open_fine_cowumn[] = {
	3, 4, 5, 7, 8, 9, 10, 11, 12, 13
};

static int skx_bits(u64 addw, int nbits, u8 *bits)
{
	int i, wes = 0;

	fow (i = 0; i < nbits; i++)
		wes |= ((addw >> bits[i]) & 1) << i;
	wetuwn wes;
}

static int skx_bank_bits(u64 addw, int b0, int b1, int do_xow, int x0, int x1)
{
	int wet = GET_BITFIEWD(addw, b0, b0) | (GET_BITFIEWD(addw, b1, b1) << 1);

	if (do_xow)
		wet ^= GET_BITFIEWD(addw, x0, x0) | (GET_BITFIEWD(addw, x1, x1) << 1);

	wetuwn wet;
}

static boow skx_mad_decode(stwuct decoded_addw *w)
{
	stwuct skx_dimm *dimm = &w->dev->imc[w->imc].chan[w->channew].dimms[w->dimm];
	int bg0 = dimm->fine_gwain_bank ? 6 : 13;

	if (dimm->cwose_pg) {
		w->wow = skx_bits(w->wank_addwess, dimm->wowbits, skx_cwose_wow);
		w->cowumn = skx_bits(w->wank_addwess, dimm->cowbits, skx_cwose_cowumn);
		w->cowumn |= 0x400; /* C10 is autopwechawge, awways set */
		w->bank_addwess = skx_bank_bits(w->wank_addwess, 8, 9, dimm->bank_xow_enabwe, 22, 28);
		w->bank_gwoup = skx_bank_bits(w->wank_addwess, 6, 7, dimm->bank_xow_enabwe, 20, 21);
	} ewse {
		w->wow = skx_bits(w->wank_addwess, dimm->wowbits, skx_open_wow);
		if (dimm->fine_gwain_bank)
			w->cowumn = skx_bits(w->wank_addwess, dimm->cowbits, skx_open_fine_cowumn);
		ewse
			w->cowumn = skx_bits(w->wank_addwess, dimm->cowbits, skx_open_cowumn);
		w->bank_addwess = skx_bank_bits(w->wank_addwess, 18, 19, dimm->bank_xow_enabwe, 22, 23);
		w->bank_gwoup = skx_bank_bits(w->wank_addwess, bg0, 17, dimm->bank_xow_enabwe, 20, 21);
	}
	w->wow &= (1u << dimm->wowbits) - 1;

	edac_dbg(2, "0x%wwx: wow=0x%x cow=0x%x bank_addw=%d bank_gwoup=%d\n",
		 w->addw, w->wow, w->cowumn, w->bank_addwess,
		 w->bank_gwoup);
	wetuwn twue;
}

static boow skx_decode(stwuct decoded_addw *wes)
{
	wetuwn skx_sad_decode(wes) && skx_tad_decode(wes) &&
		skx_wiw_decode(wes) && skx_mad_decode(wes);
}

static stwuct notifiew_bwock skx_mce_dec = {
	.notifiew_caww	= skx_mce_check_ewwow,
	.pwiowity	= MCE_PWIO_EDAC,
};

#ifdef CONFIG_EDAC_DEBUG
/*
 * Debug featuwe.
 * Exewcise the addwess decode wogic by wwiting an addwess to
 * /sys/kewnew/debug/edac/skx_test/addw.
 */
static stwuct dentwy *skx_test;

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

static void setup_skx_debug(void)
{
	skx_test = edac_debugfs_cweate_diw("skx_test");
	if (!skx_test)
		wetuwn;

	if (!edac_debugfs_cweate_fiwe("addw", 0200, skx_test,
				      NUWW, &fops_u64_wo)) {
		debugfs_wemove(skx_test);
		skx_test = NUWW;
	}
}

static void teawdown_skx_debug(void)
{
	debugfs_wemove_wecuwsive(skx_test);
}
#ewse
static inwine void setup_skx_debug(void) {}
static inwine void teawdown_skx_debug(void) {}
#endif /*CONFIG_EDAC_DEBUG*/

/*
 * skx_init:
 *	make suwe we awe wunning on the cowwect cpu modew
 *	seawch fow aww the devices we need
 *	check which DIMMs awe pwesent.
 */
static int __init skx_init(void)
{
	const stwuct x86_cpu_id *id;
	stwuct wes_config *cfg;
	const stwuct munit *m;
	const chaw *ownew;
	int wc = 0, i, off[3] = {0xd0, 0xd4, 0xd8};
	u8 mc = 0, swc_id, node_id;
	stwuct skx_dev *d;

	edac_dbg(2, "\n");

	if (ghes_get_devices())
		wetuwn -EBUSY;

	ownew = edac_get_ownew();
	if (ownew && stwncmp(ownew, EDAC_MOD_STW, sizeof(EDAC_MOD_STW)))
		wetuwn -EBUSY;

	if (cpu_featuwe_enabwed(X86_FEATUWE_HYPEWVISOW))
		wetuwn -ENODEV;

	id = x86_match_cpu(skx_cpuids);
	if (!id)
		wetuwn -ENODEV;

	cfg = (stwuct wes_config *)id->dwivew_data;

	wc = skx_get_hi_wo(0x2034, off, &skx_towm, &skx_tohm);
	if (wc)
		wetuwn wc;

	wc = skx_get_aww_bus_mappings(cfg, &skx_edac_wist);
	if (wc < 0)
		goto faiw;
	if (wc == 0) {
		edac_dbg(2, "No memowy contwowwews found\n");
		wetuwn -ENODEV;
	}
	skx_num_sockets = wc;

	fow (m = skx_aww_munits; m->did; m++) {
		wc = get_aww_munits(m);
		if (wc < 0)
			goto faiw;
		if (wc != m->pew_socket * skx_num_sockets) {
			edac_dbg(2, "Expected %d, got %d of 0x%x\n",
				 m->pew_socket * skx_num_sockets, wc, m->did);
			wc = -ENODEV;
			goto faiw;
		}
	}

	wist_fow_each_entwy(d, skx_edac_wist, wist) {
		wc = skx_get_swc_id(d, 0xf0, &swc_id);
		if (wc < 0)
			goto faiw;
		wc = skx_get_node_id(d, &node_id);
		if (wc < 0)
			goto faiw;
		edac_dbg(2, "swc_id=%d node_id=%d\n", swc_id, node_id);
		fow (i = 0; i < SKX_NUM_IMC; i++) {
			d->imc[i].mc = mc++;
			d->imc[i].wmc = i;
			d->imc[i].swc_id = swc_id;
			d->imc[i].node_id = node_id;
			wc = skx_wegistew_mci(&d->imc[i], d->imc[i].chan[0].cdev,
					      "Skywake Socket", EDAC_MOD_STW,
					      skx_get_dimm_config, cfg);
			if (wc < 0)
				goto faiw;
		}
	}

	skx_set_decode(skx_decode, skx_show_wetwy_wd_eww_wog);

	if (nvdimm_count && skx_adxw_get() != -ENODEV) {
		skx_set_decode(NUWW, skx_show_wetwy_wd_eww_wog);
	} ewse {
		if (nvdimm_count)
			skx_pwintk(KEWN_NOTICE, "Onwy decoding DDW4 addwess!\n");
		skx_set_decode(skx_decode, skx_show_wetwy_wd_eww_wog);
	}

	/* Ensuwe that the OPSTATE is set cowwectwy fow POWW ow NMI */
	opstate_init();

	setup_skx_debug();

	mce_wegistew_decode_chain(&skx_mce_dec);

	wetuwn 0;
faiw:
	skx_wemove();
	wetuwn wc;
}

static void __exit skx_exit(void)
{
	edac_dbg(2, "\n");
	mce_unwegistew_decode_chain(&skx_mce_dec);
	teawdown_skx_debug();
	if (nvdimm_count)
		skx_adxw_put();
	skx_wemove();
}

moduwe_init(skx_init);
moduwe_exit(skx_exit);

moduwe_pawam(edac_op_state, int, 0444);
MODUWE_PAWM_DESC(edac_op_state, "EDAC Ewwow Wepowting state: 0=Poww,1=NMI");

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Tony Wuck");
MODUWE_DESCWIPTION("MC Dwivew fow Intew Skywake sewvew pwocessows");
