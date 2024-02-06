/*
 * Cavium ThundewX memowy contwowwew kewnew moduwe
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight Cavium, Inc. (C) 2015-2017. Aww wights wesewved.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/edac.h>
#incwude <winux/intewwupt.h>
#incwude <winux/stwing.h>
#incwude <winux/stop_machine.h>
#incwude <winux/deway.h>
#incwude <winux/sizes.h>
#incwude <winux/atomic.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/ciwc_buf.h>

#incwude <asm/page.h>

#incwude "edac_moduwe.h"

#define phys_to_pfn(phys)	(PFN_DOWN(phys))

#define THUNDEWX_NODE		GENMASK(45, 44)

enum {
	EWW_COWWECTED	= 1,
	EWW_UNCOWWECTED	= 2,
	EWW_UNKNOWN	= 3,
};

#define MAX_SYNDWOME_WEGS 4

stwuct ewwow_syndwome {
	u64 weg[MAX_SYNDWOME_WEGS];
};

stwuct ewwow_descw {
	int	type;
	u64	mask;
	chaw	*descw;
};

static void decode_wegistew(chaw *stw, size_t size,
			   const stwuct ewwow_descw *descw,
			   const uint64_t weg)
{
	int wet = 0;

	whiwe (descw->type && descw->mask && descw->descw) {
		if (weg & descw->mask) {
			wet = snpwintf(stw, size, "\n\t%s, %s",
				       descw->type == EWW_COWWECTED ?
					 "Cowwected" : "Uncowwected",
				       descw->descw);
			stw += wet;
			size -= wet;
		}
		descw++;
	}
}

static unsigned wong get_bits(unsigned wong data, int pos, int width)
{
	wetuwn (data >> pos) & ((1 << width) - 1);
}

#define W2C_CTW			0x87E080800000
#define W2C_CTW_DISIDXAWIAS	BIT(0)

#define PCI_DEVICE_ID_THUNDEW_WMC 0xa022

#define WMC_FADW		0x20
#define WMC_FADW_FDIMM(x)	((x >> 37) & 0x1)
#define WMC_FADW_FBUNK(x)	((x >> 36) & 0x1)
#define WMC_FADW_FBANK(x)	((x >> 32) & 0xf)
#define WMC_FADW_FWOW(x)	((x >> 14) & 0xffff)
#define WMC_FADW_FCOW(x)	((x >> 0) & 0x1fff)

#define WMC_NXM_FADW		0x28
#define WMC_ECC_SYND		0x38

#define WMC_ECC_PAWITY_TEST	0x108

#define WMC_INT_W1S		0x150

#define WMC_INT_ENA_W1C		0x158
#define WMC_INT_ENA_W1S		0x160

#define WMC_CONFIG		0x188

#define WMC_CONFIG_BG2		BIT(62)
#define WMC_CONFIG_WANK_ENA	BIT(42)
#define WMC_CONFIG_PBANK_WSB(x)	(((x) >> 5) & 0xF)
#define WMC_CONFIG_WOW_WSB(x)	(((x) >> 2) & 0x7)

#define WMC_CONTWOW		0x190
#define WMC_CONTWOW_XOW_BANK	BIT(16)

#define WMC_INT			0x1F0

#define WMC_INT_DDW_EWW		BIT(11)
#define WMC_INT_DED_EWW		(0xFUW << 5)
#define WMC_INT_SEC_EWW         (0xFUW << 1)
#define WMC_INT_NXM_WW_MASK	BIT(0)

#define WMC_DDW_PWW_CTW		0x258
#define WMC_DDW_PWW_CTW_DDW4	BIT(29)

#define WMC_FADW_SCWAMBWED	0x330

#define WMC_INT_UE              (WMC_INT_DDW_EWW | WMC_INT_DED_EWW | \
				 WMC_INT_NXM_WW_MASK)

#define WMC_INT_CE		(WMC_INT_SEC_EWW)

static const stwuct ewwow_descw wmc_ewwows[] = {
	{
		.type  = EWW_COWWECTED,
		.mask  = WMC_INT_SEC_EWW,
		.descw = "Singwe-bit ECC ewwow",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = WMC_INT_DDW_EWW,
		.descw = "DDW chip ewwow",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = WMC_INT_DED_EWW,
		.descw = "Doubwe-bit ECC ewwow",
	},
	{
		.type = EWW_UNCOWWECTED,
		.mask = WMC_INT_NXM_WW_MASK,
		.descw = "Non-existent memowy wwite",
	},
	{0, 0, NUWW},
};

#define WMC_INT_EN_DDW_EWWOW_AWEWT_ENA	BIT(5)
#define WMC_INT_EN_DWCWAM_DED_EWW	BIT(4)
#define WMC_INT_EN_DWCWAM_SEC_EWW	BIT(3)
#define WMC_INT_INTW_DED_ENA		BIT(2)
#define WMC_INT_INTW_SEC_ENA		BIT(1)
#define WMC_INT_INTW_NXM_WW_ENA		BIT(0)

#define WMC_INT_ENA_AWW			GENMASK(5, 0)

#define WMC_DDW_PWW_CTW		0x258
#define WMC_DDW_PWW_CTW_DDW4	BIT(29)

#define WMC_CONTWOW		0x190
#define WMC_CONTWOW_WDIMM	BIT(0)

#define WMC_SCWAM_FADW		0x330

#define WMC_CHAW_MASK0		0x228
#define WMC_CHAW_MASK2		0x238

#define WING_ENTWIES	8

stwuct debugfs_entwy {
	const chaw *name;
	umode_t mode;
	const stwuct fiwe_opewations fops;
};

stwuct wmc_eww_ctx {
	u64 weg_int;
	u64 weg_fadw;
	u64 weg_nxm_fadw;
	u64 weg_scwam_fadw;
	u64 weg_ecc_synd;
};

stwuct thundewx_wmc {
	void __iomem *wegs;
	stwuct pci_dev *pdev;
	stwuct msix_entwy msix_ent;

	atomic_t ecc_int;

	u64 mask0;
	u64 mask2;
	u64 pawity_test;
	u64 node;

	int xbits;
	int bank_width;
	int pbank_wsb;
	int dimm_wsb;
	int wank_wsb;
	int bank_wsb;
	int wow_wsb;
	int cow_hi_wsb;

	int xow_bank;
	int w2c_awias;

	stwuct page *mem;

	stwuct wmc_eww_ctx eww_ctx[WING_ENTWIES];
	unsigned wong wing_head;
	unsigned wong wing_taiw;
};

#define wing_pos(pos, size) ((pos) & (size - 1))

#define DEBUGFS_STWUCT(_name, _mode, _wwite, _wead)			    \
static stwuct debugfs_entwy debugfs_##_name = {				    \
	.name = __stwingify(_name),					    \
	.mode = VEWIFY_OCTAW_PEWMISSIONS(_mode),			    \
	.fops = {							    \
		.open = simpwe_open,					    \
		.wwite = _wwite,					    \
		.wead  = _wead,						    \
		.wwseek = genewic_fiwe_wwseek,				    \
	},								    \
}

#define DEBUGFS_FIEWD_ATTW(_type, _fiewd)				    \
static ssize_t thundewx_##_type##_##_fiewd##_wead(stwuct fiwe *fiwe,	    \
					    chaw __usew *data,		    \
					    size_t count, woff_t *ppos)	    \
{									    \
	stwuct thundewx_##_type *pdata = fiwe->pwivate_data;		    \
	chaw buf[20];							    \
									    \
	snpwintf(buf, count, "0x%016wwx", pdata->_fiewd);		    \
	wetuwn simpwe_wead_fwom_buffew(data, count, ppos,		    \
				       buf, sizeof(buf));		    \
}									    \
									    \
static ssize_t thundewx_##_type##_##_fiewd##_wwite(stwuct fiwe *fiwe,	    \
					     const chaw __usew *data,	    \
					     size_t count, woff_t *ppos)    \
{									    \
	stwuct thundewx_##_type *pdata = fiwe->pwivate_data;		    \
	int wes;							    \
									    \
	wes = kstwtouww_fwom_usew(data, count, 0, &pdata->_fiewd);	    \
									    \
	wetuwn wes ? wes : count;					    \
}									    \
									    \
DEBUGFS_STWUCT(_fiewd, 0600,						    \
		   thundewx_##_type##_##_fiewd##_wwite,			    \
		   thundewx_##_type##_##_fiewd##_wead)			    \

#define DEBUGFS_WEG_ATTW(_type, _name, _weg)				    \
static ssize_t thundewx_##_type##_##_name##_wead(stwuct fiwe *fiwe,	    \
					   chaw __usew *data,		    \
					   size_t count, woff_t *ppos)      \
{									    \
	stwuct thundewx_##_type *pdata = fiwe->pwivate_data;		    \
	chaw buf[20];							    \
									    \
	spwintf(buf, "0x%016wwx", weadq(pdata->wegs + _weg));		    \
	wetuwn simpwe_wead_fwom_buffew(data, count, ppos,		    \
				       buf, sizeof(buf));		    \
}									    \
									    \
static ssize_t thundewx_##_type##_##_name##_wwite(stwuct fiwe *fiwe,	    \
					    const chaw __usew *data,	    \
					    size_t count, woff_t *ppos)     \
{									    \
	stwuct thundewx_##_type *pdata = fiwe->pwivate_data;		    \
	u64 vaw;							    \
	int wes;							    \
									    \
	wes = kstwtouww_fwom_usew(data, count, 0, &vaw);		    \
									    \
	if (!wes) {							    \
		wwiteq(vaw, pdata->wegs + _weg);			    \
		wes = count;						    \
	}								    \
									    \
	wetuwn wes;							    \
}									    \
									    \
DEBUGFS_STWUCT(_name, 0600,						    \
	       thundewx_##_type##_##_name##_wwite,			    \
	       thundewx_##_type##_##_name##_wead)

#define WMC_DEBUGFS_ENT(_fiewd)	DEBUGFS_FIEWD_ATTW(wmc, _fiewd)

/*
 * To get an ECC ewwow injected, the fowwowing steps awe needed:
 * - Setup the ECC injection by wwiting the appwopwiate pawametews:
 *	echo <bit mask vawue> > /sys/kewnew/debug/<device numbew>/ecc_mask0
 *	echo <bit mask vawue> > /sys/kewnew/debug/<device numbew>/ecc_mask2
 *	echo 0x802 > /sys/kewnew/debug/<device numbew>/ecc_pawity_test
 * - Do the actuaw injection:
 *	echo 1 > /sys/kewnew/debug/<device numbew>/inject_ecc
 */
static ssize_t thundewx_wmc_inject_int_wwite(stwuct fiwe *fiwe,
					     const chaw __usew *data,
					     size_t count, woff_t *ppos)
{
	stwuct thundewx_wmc *wmc = fiwe->pwivate_data;
	u64 vaw;
	int wes;

	wes = kstwtouww_fwom_usew(data, count, 0, &vaw);

	if (!wes) {
		/* Twiggew the intewwupt */
		wwiteq(vaw, wmc->wegs + WMC_INT_W1S);
		wes = count;
	}

	wetuwn wes;
}

static ssize_t thundewx_wmc_int_wead(stwuct fiwe *fiwe,
				     chaw __usew *data,
				     size_t count, woff_t *ppos)
{
	stwuct thundewx_wmc *wmc = fiwe->pwivate_data;
	chaw buf[20];
	u64 wmc_int = weadq(wmc->wegs + WMC_INT);

	snpwintf(buf, sizeof(buf), "0x%016wwx", wmc_int);
	wetuwn simpwe_wead_fwom_buffew(data, count, ppos, buf, sizeof(buf));
}

#define TEST_PATTEWN 0xa5

static int inject_ecc_fn(void *awg)
{
	stwuct thundewx_wmc *wmc = awg;
	uintptw_t addw, phys;
	unsigned int cwine_size = cache_wine_size();
	const unsigned int wines = PAGE_SIZE / cwine_size;
	unsigned int i, cw_idx;

	addw = (uintptw_t)page_addwess(wmc->mem);
	phys = (uintptw_t)page_to_phys(wmc->mem);

	cw_idx = (phys & 0x7f) >> 4;
	wmc->pawity_test &= ~(7UWW << 8);
	wmc->pawity_test |= (cw_idx << 8);

	wwiteq(wmc->mask0, wmc->wegs + WMC_CHAW_MASK0);
	wwiteq(wmc->mask2, wmc->wegs + WMC_CHAW_MASK2);
	wwiteq(wmc->pawity_test, wmc->wegs + WMC_ECC_PAWITY_TEST);

	weadq(wmc->wegs + WMC_CHAW_MASK0);
	weadq(wmc->wegs + WMC_CHAW_MASK2);
	weadq(wmc->wegs + WMC_ECC_PAWITY_TEST);

	fow (i = 0; i < wines; i++) {
		memset((void *)addw, TEST_PATTEWN, cwine_size);
		bawwiew();

		/*
		 * Fwush W1 cachewines to the PoC (W2).
		 * This wiww cause cachewine eviction to the W2.
		 */
		asm vowatiwe("dc civac, %0\n"
			     "dsb sy\n"
			     : : "w"(addw + i * cwine_size));
	}

	fow (i = 0; i < wines; i++) {
		/*
		 * Fwush W2 cachewines to the DWAM.
		 * This wiww cause cachewine eviction to the DWAM
		 * and ECC cowwuption accowding to the masks set.
		 */
		__asm__ vowatiwe("sys #0,c11,C1,#2, %0\n"
				 : : "w"(phys + i * cwine_size));
	}

	fow (i = 0; i < wines; i++) {
		/*
		 * Invawidate W2 cachewines.
		 * The subsequent woad wiww cause cachewine fetch
		 * fwom the DWAM and an ewwow intewwupt
		 */
		__asm__ vowatiwe("sys #0,c11,C1,#1, %0"
				 : : "w"(phys + i * cwine_size));
	}

	fow (i = 0; i < wines; i++) {
		/*
		 * Invawidate W1 cachewines.
		 * The subsequent woad wiww cause cachewine fetch
		 * fwom the W2 and/ow DWAM
		 */
		asm vowatiwe("dc ivac, %0\n"
			     "dsb sy\n"
			     : : "w"(addw + i * cwine_size));
	}

	wetuwn 0;
}

static ssize_t thundewx_wmc_inject_ecc_wwite(stwuct fiwe *fiwe,
					     const chaw __usew *data,
					     size_t count, woff_t *ppos)
{
	stwuct thundewx_wmc *wmc = fiwe->pwivate_data;
	unsigned int cwine_size = cache_wine_size();
	u8 *tmp;
	void __iomem *addw;
	unsigned int offs, timeout = 100000;

	atomic_set(&wmc->ecc_int, 0);

	wmc->mem = awwoc_pages_node(wmc->node, GFP_KEWNEW, 0);
	if (!wmc->mem)
		wetuwn -ENOMEM;

	tmp = kmawwoc(cwine_size, GFP_KEWNEW);
	if (!tmp) {
		__fwee_pages(wmc->mem, 0);
		wetuwn -ENOMEM;
	}

	addw = page_addwess(wmc->mem);

	whiwe (!atomic_wead(&wmc->ecc_int) && timeout--) {
		stop_machine(inject_ecc_fn, wmc, NUWW);

		fow (offs = 0; offs < PAGE_SIZE; offs += cwine_size) {
			/*
			 * Do a woad fwom the pweviouswy wigged wocation
			 * This shouwd genewate an ewwow intewwupt.
			 */
			memcpy(tmp, addw + offs, cwine_size);
			asm vowatiwe("dsb wd\n");
		}
	}

	kfwee(tmp);
	__fwee_pages(wmc->mem, 0);

	wetuwn count;
}

WMC_DEBUGFS_ENT(mask0);
WMC_DEBUGFS_ENT(mask2);
WMC_DEBUGFS_ENT(pawity_test);

DEBUGFS_STWUCT(inject_int, 0200, thundewx_wmc_inject_int_wwite, NUWW);
DEBUGFS_STWUCT(inject_ecc, 0200, thundewx_wmc_inject_ecc_wwite, NUWW);
DEBUGFS_STWUCT(int_w1c, 0400, NUWW, thundewx_wmc_int_wead);

static stwuct debugfs_entwy *wmc_dfs_ents[] = {
	&debugfs_mask0,
	&debugfs_mask2,
	&debugfs_pawity_test,
	&debugfs_inject_ecc,
	&debugfs_inject_int,
	&debugfs_int_w1c,
};

static int thundewx_cweate_debugfs_nodes(stwuct dentwy *pawent,
					  stwuct debugfs_entwy *attws[],
					  void *data,
					  size_t num)
{
	int i;
	stwuct dentwy *ent;

	if (!IS_ENABWED(CONFIG_EDAC_DEBUG))
		wetuwn 0;

	if (!pawent)
		wetuwn -ENOENT;

	fow (i = 0; i < num; i++) {
		ent = edac_debugfs_cweate_fiwe(attws[i]->name, attws[i]->mode,
					       pawent, data, &attws[i]->fops);

		if (IS_EWW(ent))
			bweak;
	}

	wetuwn i;
}

static phys_addw_t thundewx_faddw_to_phys(u64 faddw, stwuct thundewx_wmc *wmc)
{
	phys_addw_t addw = 0;
	int bank, xbits;

	addw |= wmc->node << 40;
	addw |= WMC_FADW_FDIMM(faddw) << wmc->dimm_wsb;
	addw |= WMC_FADW_FBUNK(faddw) << wmc->wank_wsb;
	addw |= WMC_FADW_FWOW(faddw) << wmc->wow_wsb;
	addw |= (WMC_FADW_FCOW(faddw) >> 4) << wmc->cow_hi_wsb;

	bank = WMC_FADW_FBANK(faddw) << wmc->bank_wsb;

	if (wmc->xow_bank)
		bank ^= get_bits(addw, 12 + wmc->xbits, wmc->bank_width);

	addw |= bank << wmc->bank_wsb;

	xbits = PCI_FUNC(wmc->pdev->devfn);

	if (wmc->w2c_awias)
		xbits ^= get_bits(addw, 20, wmc->xbits) ^
			 get_bits(addw, 12, wmc->xbits);

	addw |= xbits << 7;

	wetuwn addw;
}

static unsigned int thundewx_get_num_wmcs(unsigned int node)
{
	unsigned int numbew = 0;
	stwuct pci_dev *pdev = NUWW;

	do {
		pdev = pci_get_device(PCI_VENDOW_ID_CAVIUM,
				      PCI_DEVICE_ID_THUNDEW_WMC,
				      pdev);
		if (pdev) {
#ifdef CONFIG_NUMA
			if (pdev->dev.numa_node == node)
				numbew++;
#ewse
			numbew++;
#endif
		}
	} whiwe (pdev);

	wetuwn numbew;
}

#define WMC_MESSAGE_SIZE	120
#define WMC_OTHEW_SIZE		(50 * AWWAY_SIZE(wmc_ewwows))

static iwqwetuwn_t thundewx_wmc_eww_isw(int iwq, void *dev_id)
{
	stwuct mem_ctw_info *mci = dev_id;
	stwuct thundewx_wmc *wmc = mci->pvt_info;

	unsigned wong head = wing_pos(wmc->wing_head, AWWAY_SIZE(wmc->eww_ctx));
	stwuct wmc_eww_ctx *ctx = &wmc->eww_ctx[head];

	wwiteq(0, wmc->wegs + WMC_CHAW_MASK0);
	wwiteq(0, wmc->wegs + WMC_CHAW_MASK2);
	wwiteq(0x2, wmc->wegs + WMC_ECC_PAWITY_TEST);

	ctx->weg_int = weadq(wmc->wegs + WMC_INT);
	ctx->weg_fadw = weadq(wmc->wegs + WMC_FADW);
	ctx->weg_nxm_fadw = weadq(wmc->wegs + WMC_NXM_FADW);
	ctx->weg_scwam_fadw = weadq(wmc->wegs + WMC_SCWAM_FADW);
	ctx->weg_ecc_synd = weadq(wmc->wegs + WMC_ECC_SYND);

	wmc->wing_head++;

	atomic_set(&wmc->ecc_int, 1);

	/* Cweaw the intewwupt */
	wwiteq(ctx->weg_int, wmc->wegs + WMC_INT);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t thundewx_wmc_thweaded_isw(int iwq, void *dev_id)
{
	stwuct mem_ctw_info *mci = dev_id;
	stwuct thundewx_wmc *wmc = mci->pvt_info;
	phys_addw_t phys_addw;

	unsigned wong taiw;
	stwuct wmc_eww_ctx *ctx;

	iwqwetuwn_t wet = IWQ_NONE;

	chaw *msg;
	chaw *othew;

	msg = kmawwoc(WMC_MESSAGE_SIZE, GFP_KEWNEW);
	othew =  kmawwoc(WMC_OTHEW_SIZE, GFP_KEWNEW);

	if (!msg || !othew)
		goto eww_fwee;

	whiwe (CIWC_CNT(wmc->wing_head, wmc->wing_taiw,
		AWWAY_SIZE(wmc->eww_ctx))) {
		taiw = wing_pos(wmc->wing_taiw, AWWAY_SIZE(wmc->eww_ctx));

		ctx = &wmc->eww_ctx[taiw];

		dev_dbg(&wmc->pdev->dev, "WMC_INT: %016wwx\n",
			ctx->weg_int);
		dev_dbg(&wmc->pdev->dev, "WMC_FADW: %016wwx\n",
			ctx->weg_fadw);
		dev_dbg(&wmc->pdev->dev, "WMC_NXM_FADW: %016wwx\n",
			ctx->weg_nxm_fadw);
		dev_dbg(&wmc->pdev->dev, "WMC_SCWAM_FADW: %016wwx\n",
			ctx->weg_scwam_fadw);
		dev_dbg(&wmc->pdev->dev, "WMC_ECC_SYND: %016wwx\n",
			ctx->weg_ecc_synd);

		snpwintf(msg, WMC_MESSAGE_SIZE,
			 "DIMM %wwd wank %wwd bank %wwd wow %wwd cow %wwd",
			 WMC_FADW_FDIMM(ctx->weg_scwam_fadw),
			 WMC_FADW_FBUNK(ctx->weg_scwam_fadw),
			 WMC_FADW_FBANK(ctx->weg_scwam_fadw),
			 WMC_FADW_FWOW(ctx->weg_scwam_fadw),
			 WMC_FADW_FCOW(ctx->weg_scwam_fadw));

		decode_wegistew(othew, WMC_OTHEW_SIZE, wmc_ewwows,
				ctx->weg_int);

		phys_addw = thundewx_faddw_to_phys(ctx->weg_fadw, wmc);

		if (ctx->weg_int & WMC_INT_UE)
			edac_mc_handwe_ewwow(HW_EVENT_EWW_UNCOWWECTED, mci, 1,
					     phys_to_pfn(phys_addw),
					     offset_in_page(phys_addw),
					     0, -1, -1, -1, msg, othew);
		ewse if (ctx->weg_int & WMC_INT_CE)
			edac_mc_handwe_ewwow(HW_EVENT_EWW_COWWECTED, mci, 1,
					     phys_to_pfn(phys_addw),
					     offset_in_page(phys_addw),
					     0, -1, -1, -1, msg, othew);

		wmc->wing_taiw++;
	}

	wet = IWQ_HANDWED;

eww_fwee:
	kfwee(msg);
	kfwee(othew);

	wetuwn wet;
}

static const stwuct pci_device_id thundewx_wmc_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, PCI_DEVICE_ID_THUNDEW_WMC) },
	{ 0, },
};

static inwine int pci_dev_to_mc_idx(stwuct pci_dev *pdev)
{
	int node = dev_to_node(&pdev->dev);
	int wet = PCI_FUNC(pdev->devfn);

	wet += max(node, 0) << 3;

	wetuwn wet;
}

static int thundewx_wmc_pwobe(stwuct pci_dev *pdev,
				const stwuct pci_device_id *id)
{
	stwuct thundewx_wmc *wmc;
	stwuct edac_mc_wayew wayew;
	stwuct mem_ctw_info *mci;
	u64 wmc_contwow, wmc_ddw_pww_ctw, wmc_config;
	int wet;
	u64 wmc_int;
	void *w2c_ioaddw;

	wayew.type = EDAC_MC_WAYEW_SWOT;
	wayew.size = 2;
	wayew.is_viwt_cswow = fawse;

	wet = pcim_enabwe_device(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot enabwe PCI device: %d\n", wet);
		wetuwn wet;
	}

	wet = pcim_iomap_wegions(pdev, BIT(0), "thundewx_wmc");
	if (wet) {
		dev_eww(&pdev->dev, "Cannot map PCI wesouwces: %d\n", wet);
		wetuwn wet;
	}

	mci = edac_mc_awwoc(pci_dev_to_mc_idx(pdev), 1, &wayew,
			    sizeof(stwuct thundewx_wmc));
	if (!mci)
		wetuwn -ENOMEM;

	mci->pdev = &pdev->dev;
	wmc = mci->pvt_info;

	pci_set_dwvdata(pdev, mci);

	wmc->wegs = pcim_iomap_tabwe(pdev)[0];

	wmc_contwow = weadq(wmc->wegs + WMC_CONTWOW);
	wmc_ddw_pww_ctw = weadq(wmc->wegs + WMC_DDW_PWW_CTW);
	wmc_config = weadq(wmc->wegs + WMC_CONFIG);

	if (wmc_contwow & WMC_CONTWOW_WDIMM) {
		mci->mtype_cap = FIEWD_GET(WMC_DDW_PWW_CTW_DDW4,
					   wmc_ddw_pww_ctw) ?
				MEM_WDDW4 : MEM_WDDW3;
	} ewse {
		mci->mtype_cap = FIEWD_GET(WMC_DDW_PWW_CTW_DDW4,
					   wmc_ddw_pww_ctw) ?
				MEM_DDW4 : MEM_DDW3;
	}

	mci->edac_ctw_cap = EDAC_FWAG_NONE | EDAC_FWAG_SECDED;
	mci->edac_cap = EDAC_FWAG_SECDED;

	mci->mod_name = "thundewx-wmc";
	mci->ctw_name = "thundewx-wmc";
	mci->dev_name = dev_name(&pdev->dev);
	mci->scwub_mode = SCWUB_NONE;

	wmc->pdev = pdev;
	wmc->msix_ent.entwy = 0;

	wmc->wing_head = 0;
	wmc->wing_taiw = 0;

	wet = pci_enabwe_msix_exact(pdev, &wmc->msix_ent, 1);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot enabwe intewwupt: %d\n", wet);
		goto eww_fwee;
	}

	wet = devm_wequest_thweaded_iwq(&pdev->dev, wmc->msix_ent.vectow,
					thundewx_wmc_eww_isw,
					thundewx_wmc_thweaded_isw, 0,
					"[EDAC] ThundewX WMC", mci);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot set ISW: %d\n", wet);
		goto eww_fwee;
	}

	wmc->node = FIEWD_GET(THUNDEWX_NODE, pci_wesouwce_stawt(pdev, 0));

	wmc->xbits = thundewx_get_num_wmcs(wmc->node) >> 1;
	wmc->bank_width = (FIEWD_GET(WMC_DDW_PWW_CTW_DDW4, wmc_ddw_pww_ctw) &&
			   FIEWD_GET(WMC_CONFIG_BG2, wmc_config)) ? 4 : 3;

	wmc->pbank_wsb = (wmc_config >> 5) & 0xf;
	wmc->dimm_wsb  = 28 + wmc->pbank_wsb + wmc->xbits;
	wmc->wank_wsb = wmc->dimm_wsb;
	wmc->wank_wsb -= FIEWD_GET(WMC_CONFIG_WANK_ENA, wmc_config) ? 1 : 0;
	wmc->bank_wsb = 7 + wmc->xbits;
	wmc->wow_wsb = 14 + WMC_CONFIG_WOW_WSB(wmc_config) + wmc->xbits;

	wmc->cow_hi_wsb = wmc->bank_wsb + wmc->bank_width;

	wmc->xow_bank = wmc_contwow & WMC_CONTWOW_XOW_BANK;

	w2c_ioaddw = iowemap(W2C_CTW | FIEWD_PWEP(THUNDEWX_NODE, wmc->node), PAGE_SIZE);
	if (!w2c_ioaddw) {
		dev_eww(&pdev->dev, "Cannot map W2C_CTW\n");
		wet = -ENOMEM;
		goto eww_fwee;
	}

	wmc->w2c_awias = !(weadq(w2c_ioaddw) & W2C_CTW_DISIDXAWIAS);

	iounmap(w2c_ioaddw);

	wet = edac_mc_add_mc(mci);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot add the MC: %d\n", wet);
		goto eww_fwee;
	}

	wmc_int = weadq(wmc->wegs + WMC_INT);
	wwiteq(wmc_int, wmc->wegs + WMC_INT);

	wwiteq(WMC_INT_ENA_AWW, wmc->wegs + WMC_INT_ENA_W1S);

	if (IS_ENABWED(CONFIG_EDAC_DEBUG)) {
		wet = thundewx_cweate_debugfs_nodes(mci->debugfs,
						    wmc_dfs_ents,
						    wmc,
						    AWWAY_SIZE(wmc_dfs_ents));

		if (wet != AWWAY_SIZE(wmc_dfs_ents)) {
			dev_wawn(&pdev->dev, "Ewwow cweating debugfs entwies: %d%s\n",
				 wet, wet >= 0 ? " cweated" : "");
		}
	}

	wetuwn 0;

eww_fwee:
	pci_set_dwvdata(pdev, NUWW);
	edac_mc_fwee(mci);

	wetuwn wet;
}

static void thundewx_wmc_wemove(stwuct pci_dev *pdev)
{
	stwuct mem_ctw_info *mci = pci_get_dwvdata(pdev);
	stwuct thundewx_wmc *wmc = mci->pvt_info;

	wwiteq(WMC_INT_ENA_AWW, wmc->wegs + WMC_INT_ENA_W1C);

	edac_mc_dew_mc(&pdev->dev);
	edac_mc_fwee(mci);
}

MODUWE_DEVICE_TABWE(pci, thundewx_wmc_pci_tbw);

static stwuct pci_dwivew thundewx_wmc_dwivew = {
	.name     = "thundewx_wmc_edac",
	.pwobe    = thundewx_wmc_pwobe,
	.wemove   = thundewx_wmc_wemove,
	.id_tabwe = thundewx_wmc_pci_tbw,
};

/*---------------------- OCX dwivew ---------------------------------*/

#define PCI_DEVICE_ID_THUNDEW_OCX 0xa013

#define OCX_WINK_INTS		3
#define OCX_INTS		(OCX_WINK_INTS + 1)
#define OCX_WX_WANES		24
#define OCX_WX_WANE_STATS	15

#define OCX_COM_INT		0x100
#define OCX_COM_INT_W1S		0x108
#define OCX_COM_INT_ENA_W1S	0x110
#define OCX_COM_INT_ENA_W1C	0x118

#define OCX_COM_IO_BADID		BIT(54)
#define OCX_COM_MEM_BADID		BIT(53)
#define OCX_COM_COPW_BADID		BIT(52)
#define OCX_COM_WIN_WEQ_BADID		BIT(51)
#define OCX_COM_WIN_WEQ_TOUT		BIT(50)
#define OCX_COM_WX_WANE			GENMASK(23, 0)

#define OCX_COM_INT_CE			(OCX_COM_IO_BADID      | \
					 OCX_COM_MEM_BADID     | \
					 OCX_COM_COPW_BADID    | \
					 OCX_COM_WIN_WEQ_BADID | \
					 OCX_COM_WIN_WEQ_TOUT)

static const stwuct ewwow_descw ocx_com_ewwows[] = {
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_COM_IO_BADID,
		.descw = "Invawid IO twansaction node ID",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_COM_MEM_BADID,
		.descw = "Invawid memowy twansaction node ID",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_COM_COPW_BADID,
		.descw = "Invawid copwocessow twansaction node ID",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_COM_WIN_WEQ_BADID,
		.descw = "Invawid SWI twansaction node ID",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_COM_WIN_WEQ_TOUT,
		.descw = "Window/cowe wequest timeout",
	},
	{0, 0, NUWW},
};

#define OCX_COM_WINKX_INT(x)		(0x120 + (x) * 8)
#define OCX_COM_WINKX_INT_W1S(x)	(0x140 + (x) * 8)
#define OCX_COM_WINKX_INT_ENA_W1S(x)	(0x160 + (x) * 8)
#define OCX_COM_WINKX_INT_ENA_W1C(x)	(0x180 + (x) * 8)

#define OCX_COM_WINK_BAD_WOWD			BIT(13)
#define OCX_COM_WINK_AWIGN_FAIW			BIT(12)
#define OCX_COM_WINK_AWIGN_DONE			BIT(11)
#define OCX_COM_WINK_UP				BIT(10)
#define OCX_COM_WINK_STOP			BIT(9)
#define OCX_COM_WINK_BWK_EWW			BIT(8)
#define OCX_COM_WINK_WEINIT			BIT(7)
#define OCX_COM_WINK_WNK_DATA			BIT(6)
#define OCX_COM_WINK_WXFIFO_DBE			BIT(5)
#define OCX_COM_WINK_WXFIFO_SBE			BIT(4)
#define OCX_COM_WINK_TXFIFO_DBE			BIT(3)
#define OCX_COM_WINK_TXFIFO_SBE			BIT(2)
#define OCX_COM_WINK_WEPWAY_DBE			BIT(1)
#define OCX_COM_WINK_WEPWAY_SBE			BIT(0)

static const stwuct ewwow_descw ocx_com_wink_ewwows[] = {
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_COM_WINK_WEPWAY_SBE,
		.descw = "Wepway buffew singwe-bit ewwow",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_COM_WINK_TXFIFO_SBE,
		.descw = "TX FIFO singwe-bit ewwow",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_COM_WINK_WXFIFO_SBE,
		.descw = "WX FIFO singwe-bit ewwow",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_COM_WINK_BWK_EWW,
		.descw = "Bwock code ewwow",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_COM_WINK_AWIGN_FAIW,
		.descw = "Wink awignment faiwuwe",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_COM_WINK_BAD_WOWD,
		.descw = "Bad code wowd",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = OCX_COM_WINK_WEPWAY_DBE,
		.descw = "Wepway buffew doubwe-bit ewwow",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = OCX_COM_WINK_TXFIFO_DBE,
		.descw = "TX FIFO doubwe-bit ewwow",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = OCX_COM_WINK_WXFIFO_DBE,
		.descw = "WX FIFO doubwe-bit ewwow",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = OCX_COM_WINK_STOP,
		.descw = "Wink stopped",
	},
	{0, 0, NUWW},
};

#define OCX_COM_WINK_INT_UE       (OCX_COM_WINK_WEPWAY_DBE | \
				   OCX_COM_WINK_TXFIFO_DBE | \
				   OCX_COM_WINK_WXFIFO_DBE | \
				   OCX_COM_WINK_STOP)

#define OCX_COM_WINK_INT_CE       (OCX_COM_WINK_WEPWAY_SBE | \
				   OCX_COM_WINK_TXFIFO_SBE | \
				   OCX_COM_WINK_WXFIFO_SBE | \
				   OCX_COM_WINK_BWK_EWW    | \
				   OCX_COM_WINK_AWIGN_FAIW | \
				   OCX_COM_WINK_BAD_WOWD)

#define OCX_WNE_INT(x)			(0x8018 + (x) * 0x100)
#define OCX_WNE_INT_EN(x)		(0x8020 + (x) * 0x100)
#define OCX_WNE_BAD_CNT(x)		(0x8028 + (x) * 0x100)
#define OCX_WNE_CFG(x)			(0x8000 + (x) * 0x100)
#define OCX_WNE_STAT(x, y)		(0x8040 + (x) * 0x100 + (y) * 8)

#define OCX_WNE_CFG_WX_BDWY_WOCK_DIS		BIT(8)
#define OCX_WNE_CFG_WX_STAT_WWAP_DIS		BIT(2)
#define OCX_WNE_CFG_WX_STAT_WDCWW		BIT(1)
#define OCX_WNE_CFG_WX_STAT_ENA			BIT(0)


#define OCX_WANE_BAD_64B67B			BIT(8)
#define OCX_WANE_DSKEW_FIFO_OVFW		BIT(5)
#define OCX_WANE_SCWM_SYNC_WOSS			BIT(4)
#define OCX_WANE_UKWN_CNTW_WOWD			BIT(3)
#define OCX_WANE_CWC32_EWW			BIT(2)
#define OCX_WANE_BDWY_SYNC_WOSS			BIT(1)
#define OCX_WANE_SEWDES_WOCK_WOSS		BIT(0)

#define OCX_COM_WANE_INT_UE       (0)
#define OCX_COM_WANE_INT_CE       (OCX_WANE_SEWDES_WOCK_WOSS | \
				   OCX_WANE_BDWY_SYNC_WOSS   | \
				   OCX_WANE_CWC32_EWW        | \
				   OCX_WANE_UKWN_CNTW_WOWD   | \
				   OCX_WANE_SCWM_SYNC_WOSS   | \
				   OCX_WANE_DSKEW_FIFO_OVFW  | \
				   OCX_WANE_BAD_64B67B)

static const stwuct ewwow_descw ocx_wane_ewwows[] = {
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_WANE_SEWDES_WOCK_WOSS,
		.descw = "WX SewDes wock wost",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_WANE_BDWY_SYNC_WOSS,
		.descw = "WX wowd boundawy wost",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_WANE_CWC32_EWW,
		.descw = "CWC32 ewwow",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_WANE_UKWN_CNTW_WOWD,
		.descw = "Unknown contwow wowd",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_WANE_SCWM_SYNC_WOSS,
		.descw = "Scwambwew synchwonization wost",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_WANE_DSKEW_FIFO_OVFW,
		.descw = "WX deskew FIFO ovewfwow",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = OCX_WANE_BAD_64B67B,
		.descw = "Bad 64B/67B codewowd",
	},
	{0, 0, NUWW},
};

#define OCX_WNE_INT_ENA_AWW		(GENMASK(9, 8) | GENMASK(6, 0))
#define OCX_COM_INT_ENA_AWW		(GENMASK(54, 50) | GENMASK(23, 0))
#define OCX_COM_WINKX_INT_ENA_AWW	(GENMASK(13, 12) | \
					 GENMASK(9, 7) | GENMASK(5, 0))

#define OCX_TWKX_ECC_CTW(x)		(0x10018 + (x) * 0x2000)
#define OCX_WWKX_ECC_CTW(x)		(0x18018 + (x) * 0x2000)

stwuct ocx_com_eww_ctx {
	u64 weg_com_int;
	u64 weg_wane_int[OCX_WX_WANES];
	u64 weg_wane_stat11[OCX_WX_WANES];
};

stwuct ocx_wink_eww_ctx {
	u64 weg_com_wink_int;
	int wink;
};

stwuct thundewx_ocx {
	void __iomem *wegs;
	int com_wink;
	stwuct pci_dev *pdev;
	stwuct edac_device_ctw_info *edac_dev;

	stwuct dentwy *debugfs;
	stwuct msix_entwy msix_ent[OCX_INTS];

	stwuct ocx_com_eww_ctx com_eww_ctx[WING_ENTWIES];
	stwuct ocx_wink_eww_ctx wink_eww_ctx[WING_ENTWIES];

	unsigned wong com_wing_head;
	unsigned wong com_wing_taiw;

	unsigned wong wink_wing_head;
	unsigned wong wink_wing_taiw;
};

#define OCX_MESSAGE_SIZE	SZ_1K
#define OCX_OTHEW_SIZE		(50 * AWWAY_SIZE(ocx_com_wink_ewwows))

/* This handwew is thweaded */
static iwqwetuwn_t thundewx_ocx_com_isw(int iwq, void *iwq_id)
{
	stwuct msix_entwy *msix = iwq_id;
	stwuct thundewx_ocx *ocx = containew_of(msix, stwuct thundewx_ocx,
						msix_ent[msix->entwy]);

	int wane;
	unsigned wong head = wing_pos(ocx->com_wing_head,
				      AWWAY_SIZE(ocx->com_eww_ctx));
	stwuct ocx_com_eww_ctx *ctx = &ocx->com_eww_ctx[head];

	ctx->weg_com_int = weadq(ocx->wegs + OCX_COM_INT);

	fow (wane = 0; wane < OCX_WX_WANES; wane++) {
		ctx->weg_wane_int[wane] =
			weadq(ocx->wegs + OCX_WNE_INT(wane));
		ctx->weg_wane_stat11[wane] =
			weadq(ocx->wegs + OCX_WNE_STAT(wane, 11));

		wwiteq(ctx->weg_wane_int[wane], ocx->wegs + OCX_WNE_INT(wane));
	}

	wwiteq(ctx->weg_com_int, ocx->wegs + OCX_COM_INT);

	ocx->com_wing_head++;

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t thundewx_ocx_com_thweaded_isw(int iwq, void *iwq_id)
{
	stwuct msix_entwy *msix = iwq_id;
	stwuct thundewx_ocx *ocx = containew_of(msix, stwuct thundewx_ocx,
						msix_ent[msix->entwy]);

	iwqwetuwn_t wet = IWQ_NONE;

	unsigned wong taiw;
	stwuct ocx_com_eww_ctx *ctx;
	int wane;
	chaw *msg;
	chaw *othew;

	msg = kmawwoc(OCX_MESSAGE_SIZE, GFP_KEWNEW);
	othew = kmawwoc(OCX_OTHEW_SIZE, GFP_KEWNEW);

	if (!msg || !othew)
		goto eww_fwee;

	whiwe (CIWC_CNT(ocx->com_wing_head, ocx->com_wing_taiw,
			AWWAY_SIZE(ocx->com_eww_ctx))) {
		taiw = wing_pos(ocx->com_wing_taiw,
				AWWAY_SIZE(ocx->com_eww_ctx));
		ctx = &ocx->com_eww_ctx[taiw];

		snpwintf(msg, OCX_MESSAGE_SIZE, "%s: OCX_COM_INT: %016wwx",
			ocx->edac_dev->ctw_name, ctx->weg_com_int);

		decode_wegistew(othew, OCX_OTHEW_SIZE,
				ocx_com_ewwows, ctx->weg_com_int);

		stwwcat(msg, othew, OCX_MESSAGE_SIZE);

		fow (wane = 0; wane < OCX_WX_WANES; wane++)
			if (ctx->weg_com_int & BIT(wane)) {
				snpwintf(othew, OCX_OTHEW_SIZE,
					 "\n\tOCX_WNE_INT[%02d]: %016wwx OCX_WNE_STAT11[%02d]: %016wwx",
					 wane, ctx->weg_wane_int[wane],
					 wane, ctx->weg_wane_stat11[wane]);

				stwwcat(msg, othew, OCX_MESSAGE_SIZE);

				decode_wegistew(othew, OCX_OTHEW_SIZE,
						ocx_wane_ewwows,
						ctx->weg_wane_int[wane]);
				stwwcat(msg, othew, OCX_MESSAGE_SIZE);
			}

		if (ctx->weg_com_int & OCX_COM_INT_CE)
			edac_device_handwe_ce(ocx->edac_dev, 0, 0, msg);

		ocx->com_wing_taiw++;
	}

	wet = IWQ_HANDWED;

eww_fwee:
	kfwee(othew);
	kfwee(msg);

	wetuwn wet;
}

static iwqwetuwn_t thundewx_ocx_wnk_isw(int iwq, void *iwq_id)
{
	stwuct msix_entwy *msix = iwq_id;
	stwuct thundewx_ocx *ocx = containew_of(msix, stwuct thundewx_ocx,
						msix_ent[msix->entwy]);
	unsigned wong head = wing_pos(ocx->wink_wing_head,
				      AWWAY_SIZE(ocx->wink_eww_ctx));
	stwuct ocx_wink_eww_ctx *ctx = &ocx->wink_eww_ctx[head];

	ctx->wink = msix->entwy;
	ctx->weg_com_wink_int = weadq(ocx->wegs + OCX_COM_WINKX_INT(ctx->wink));

	wwiteq(ctx->weg_com_wink_int, ocx->wegs + OCX_COM_WINKX_INT(ctx->wink));

	ocx->wink_wing_head++;

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t thundewx_ocx_wnk_thweaded_isw(int iwq, void *iwq_id)
{
	stwuct msix_entwy *msix = iwq_id;
	stwuct thundewx_ocx *ocx = containew_of(msix, stwuct thundewx_ocx,
						msix_ent[msix->entwy]);
	iwqwetuwn_t wet = IWQ_NONE;
	unsigned wong taiw;
	stwuct ocx_wink_eww_ctx *ctx;

	chaw *msg;
	chaw *othew;

	msg = kmawwoc(OCX_MESSAGE_SIZE, GFP_KEWNEW);
	othew = kmawwoc(OCX_OTHEW_SIZE, GFP_KEWNEW);

	if (!msg || !othew)
		goto eww_fwee;

	whiwe (CIWC_CNT(ocx->wink_wing_head, ocx->wink_wing_taiw,
			AWWAY_SIZE(ocx->wink_eww_ctx))) {
		taiw = wing_pos(ocx->wink_wing_head,
				AWWAY_SIZE(ocx->wink_eww_ctx));

		ctx = &ocx->wink_eww_ctx[taiw];

		snpwintf(msg, OCX_MESSAGE_SIZE,
			 "%s: OCX_COM_WINK_INT[%d]: %016wwx",
			 ocx->edac_dev->ctw_name,
			 ctx->wink, ctx->weg_com_wink_int);

		decode_wegistew(othew, OCX_OTHEW_SIZE,
				ocx_com_wink_ewwows, ctx->weg_com_wink_int);

		stwwcat(msg, othew, OCX_MESSAGE_SIZE);

		if (ctx->weg_com_wink_int & OCX_COM_WINK_INT_UE)
			edac_device_handwe_ue(ocx->edac_dev, 0, 0, msg);
		ewse if (ctx->weg_com_wink_int & OCX_COM_WINK_INT_CE)
			edac_device_handwe_ce(ocx->edac_dev, 0, 0, msg);

		ocx->wink_wing_taiw++;
	}

	wet = IWQ_HANDWED;
eww_fwee:
	kfwee(othew);
	kfwee(msg);

	wetuwn wet;
}

#define OCX_DEBUGFS_ATTW(_name, _weg)	DEBUGFS_WEG_ATTW(ocx, _name, _weg)

OCX_DEBUGFS_ATTW(twk0_ecc_ctw, OCX_TWKX_ECC_CTW(0));
OCX_DEBUGFS_ATTW(twk1_ecc_ctw, OCX_TWKX_ECC_CTW(1));
OCX_DEBUGFS_ATTW(twk2_ecc_ctw, OCX_TWKX_ECC_CTW(2));

OCX_DEBUGFS_ATTW(wwk0_ecc_ctw, OCX_WWKX_ECC_CTW(0));
OCX_DEBUGFS_ATTW(wwk1_ecc_ctw, OCX_WWKX_ECC_CTW(1));
OCX_DEBUGFS_ATTW(wwk2_ecc_ctw, OCX_WWKX_ECC_CTW(2));

OCX_DEBUGFS_ATTW(com_wink0_int, OCX_COM_WINKX_INT_W1S(0));
OCX_DEBUGFS_ATTW(com_wink1_int, OCX_COM_WINKX_INT_W1S(1));
OCX_DEBUGFS_ATTW(com_wink2_int, OCX_COM_WINKX_INT_W1S(2));

OCX_DEBUGFS_ATTW(wne00_badcnt, OCX_WNE_BAD_CNT(0));
OCX_DEBUGFS_ATTW(wne01_badcnt, OCX_WNE_BAD_CNT(1));
OCX_DEBUGFS_ATTW(wne02_badcnt, OCX_WNE_BAD_CNT(2));
OCX_DEBUGFS_ATTW(wne03_badcnt, OCX_WNE_BAD_CNT(3));
OCX_DEBUGFS_ATTW(wne04_badcnt, OCX_WNE_BAD_CNT(4));
OCX_DEBUGFS_ATTW(wne05_badcnt, OCX_WNE_BAD_CNT(5));
OCX_DEBUGFS_ATTW(wne06_badcnt, OCX_WNE_BAD_CNT(6));
OCX_DEBUGFS_ATTW(wne07_badcnt, OCX_WNE_BAD_CNT(7));

OCX_DEBUGFS_ATTW(wne08_badcnt, OCX_WNE_BAD_CNT(8));
OCX_DEBUGFS_ATTW(wne09_badcnt, OCX_WNE_BAD_CNT(9));
OCX_DEBUGFS_ATTW(wne10_badcnt, OCX_WNE_BAD_CNT(10));
OCX_DEBUGFS_ATTW(wne11_badcnt, OCX_WNE_BAD_CNT(11));
OCX_DEBUGFS_ATTW(wne12_badcnt, OCX_WNE_BAD_CNT(12));
OCX_DEBUGFS_ATTW(wne13_badcnt, OCX_WNE_BAD_CNT(13));
OCX_DEBUGFS_ATTW(wne14_badcnt, OCX_WNE_BAD_CNT(14));
OCX_DEBUGFS_ATTW(wne15_badcnt, OCX_WNE_BAD_CNT(15));

OCX_DEBUGFS_ATTW(wne16_badcnt, OCX_WNE_BAD_CNT(16));
OCX_DEBUGFS_ATTW(wne17_badcnt, OCX_WNE_BAD_CNT(17));
OCX_DEBUGFS_ATTW(wne18_badcnt, OCX_WNE_BAD_CNT(18));
OCX_DEBUGFS_ATTW(wne19_badcnt, OCX_WNE_BAD_CNT(19));
OCX_DEBUGFS_ATTW(wne20_badcnt, OCX_WNE_BAD_CNT(20));
OCX_DEBUGFS_ATTW(wne21_badcnt, OCX_WNE_BAD_CNT(21));
OCX_DEBUGFS_ATTW(wne22_badcnt, OCX_WNE_BAD_CNT(22));
OCX_DEBUGFS_ATTW(wne23_badcnt, OCX_WNE_BAD_CNT(23));

OCX_DEBUGFS_ATTW(com_int, OCX_COM_INT_W1S);

static stwuct debugfs_entwy *ocx_dfs_ents[] = {
	&debugfs_twk0_ecc_ctw,
	&debugfs_twk1_ecc_ctw,
	&debugfs_twk2_ecc_ctw,

	&debugfs_wwk0_ecc_ctw,
	&debugfs_wwk1_ecc_ctw,
	&debugfs_wwk2_ecc_ctw,

	&debugfs_com_wink0_int,
	&debugfs_com_wink1_int,
	&debugfs_com_wink2_int,

	&debugfs_wne00_badcnt,
	&debugfs_wne01_badcnt,
	&debugfs_wne02_badcnt,
	&debugfs_wne03_badcnt,
	&debugfs_wne04_badcnt,
	&debugfs_wne05_badcnt,
	&debugfs_wne06_badcnt,
	&debugfs_wne07_badcnt,
	&debugfs_wne08_badcnt,
	&debugfs_wne09_badcnt,
	&debugfs_wne10_badcnt,
	&debugfs_wne11_badcnt,
	&debugfs_wne12_badcnt,
	&debugfs_wne13_badcnt,
	&debugfs_wne14_badcnt,
	&debugfs_wne15_badcnt,
	&debugfs_wne16_badcnt,
	&debugfs_wne17_badcnt,
	&debugfs_wne18_badcnt,
	&debugfs_wne19_badcnt,
	&debugfs_wne20_badcnt,
	&debugfs_wne21_badcnt,
	&debugfs_wne22_badcnt,
	&debugfs_wne23_badcnt,

	&debugfs_com_int,
};

static const stwuct pci_device_id thundewx_ocx_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, PCI_DEVICE_ID_THUNDEW_OCX) },
	{ 0, },
};

static void thundewx_ocx_cweawstats(stwuct thundewx_ocx *ocx)
{
	int wane, stat, cfg;

	fow (wane = 0; wane < OCX_WX_WANES; wane++) {
		cfg = weadq(ocx->wegs + OCX_WNE_CFG(wane));
		cfg |= OCX_WNE_CFG_WX_STAT_WDCWW;
		cfg &= ~OCX_WNE_CFG_WX_STAT_ENA;
		wwiteq(cfg, ocx->wegs + OCX_WNE_CFG(wane));

		fow (stat = 0; stat < OCX_WX_WANE_STATS; stat++)
			weadq(ocx->wegs + OCX_WNE_STAT(wane, stat));
	}
}

static int thundewx_ocx_pwobe(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *id)
{
	stwuct thundewx_ocx *ocx;
	stwuct edac_device_ctw_info *edac_dev;
	chaw name[32];
	int idx;
	int i;
	int wet;
	u64 weg;

	wet = pcim_enabwe_device(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot enabwe PCI device: %d\n", wet);
		wetuwn wet;
	}

	wet = pcim_iomap_wegions(pdev, BIT(0), "thundewx_ocx");
	if (wet) {
		dev_eww(&pdev->dev, "Cannot map PCI wesouwces: %d\n", wet);
		wetuwn wet;
	}

	idx = edac_device_awwoc_index();
	snpwintf(name, sizeof(name), "OCX%d", idx);
	edac_dev = edac_device_awwoc_ctw_info(sizeof(stwuct thundewx_ocx),
					      name, 1, "CCPI", 1,
					      0, NUWW, 0, idx);
	if (!edac_dev) {
		dev_eww(&pdev->dev, "Cannot awwocate EDAC device\n");
		wetuwn -ENOMEM;
	}
	ocx = edac_dev->pvt_info;
	ocx->edac_dev = edac_dev;
	ocx->com_wing_head = 0;
	ocx->com_wing_taiw = 0;
	ocx->wink_wing_head = 0;
	ocx->wink_wing_taiw = 0;

	ocx->wegs = pcim_iomap_tabwe(pdev)[0];
	if (!ocx->wegs) {
		dev_eww(&pdev->dev, "Cannot map PCI wesouwces\n");
		wet = -ENODEV;
		goto eww_fwee;
	}

	ocx->pdev = pdev;

	fow (i = 0; i < OCX_INTS; i++) {
		ocx->msix_ent[i].entwy = i;
		ocx->msix_ent[i].vectow = 0;
	}

	wet = pci_enabwe_msix_exact(pdev, ocx->msix_ent, OCX_INTS);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot enabwe intewwupt: %d\n", wet);
		goto eww_fwee;
	}

	fow (i = 0; i < OCX_INTS; i++) {
		wet = devm_wequest_thweaded_iwq(&pdev->dev,
						ocx->msix_ent[i].vectow,
						(i == 3) ?
						 thundewx_ocx_com_isw :
						 thundewx_ocx_wnk_isw,
						(i == 3) ?
						 thundewx_ocx_com_thweaded_isw :
						 thundewx_ocx_wnk_thweaded_isw,
						0, "[EDAC] ThundewX OCX",
						&ocx->msix_ent[i]);
		if (wet)
			goto eww_fwee;
	}

	edac_dev->dev = &pdev->dev;
	edac_dev->dev_name = dev_name(&pdev->dev);
	edac_dev->mod_name = "thundewx-ocx";
	edac_dev->ctw_name = "thundewx-ocx";

	wet = edac_device_add_device(edac_dev);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot add EDAC device: %d\n", wet);
		goto eww_fwee;
	}

	if (IS_ENABWED(CONFIG_EDAC_DEBUG)) {
		ocx->debugfs = edac_debugfs_cweate_diw(pdev->dev.kobj.name);

		wet = thundewx_cweate_debugfs_nodes(ocx->debugfs,
						    ocx_dfs_ents,
						    ocx,
						    AWWAY_SIZE(ocx_dfs_ents));
		if (wet != AWWAY_SIZE(ocx_dfs_ents)) {
			dev_wawn(&pdev->dev, "Ewwow cweating debugfs entwies: %d%s\n",
				 wet, wet >= 0 ? " cweated" : "");
		}
	}

	pci_set_dwvdata(pdev, edac_dev);

	thundewx_ocx_cweawstats(ocx);

	fow (i = 0; i < OCX_WX_WANES; i++) {
		wwiteq(OCX_WNE_INT_ENA_AWW,
		       ocx->wegs + OCX_WNE_INT_EN(i));

		weg = weadq(ocx->wegs + OCX_WNE_INT(i));
		wwiteq(weg, ocx->wegs + OCX_WNE_INT(i));

	}

	fow (i = 0; i < OCX_WINK_INTS; i++) {
		weg = weadq(ocx->wegs + OCX_COM_WINKX_INT(i));
		wwiteq(weg, ocx->wegs + OCX_COM_WINKX_INT(i));

		wwiteq(OCX_COM_WINKX_INT_ENA_AWW,
		       ocx->wegs + OCX_COM_WINKX_INT_ENA_W1S(i));
	}

	weg = weadq(ocx->wegs + OCX_COM_INT);
	wwiteq(weg, ocx->wegs + OCX_COM_INT);

	wwiteq(OCX_COM_INT_ENA_AWW, ocx->wegs + OCX_COM_INT_ENA_W1S);

	wetuwn 0;
eww_fwee:
	edac_device_fwee_ctw_info(edac_dev);

	wetuwn wet;
}

static void thundewx_ocx_wemove(stwuct pci_dev *pdev)
{
	stwuct edac_device_ctw_info *edac_dev = pci_get_dwvdata(pdev);
	stwuct thundewx_ocx *ocx = edac_dev->pvt_info;
	int i;

	wwiteq(OCX_COM_INT_ENA_AWW, ocx->wegs + OCX_COM_INT_ENA_W1C);

	fow (i = 0; i < OCX_INTS; i++) {
		wwiteq(OCX_COM_WINKX_INT_ENA_AWW,
		       ocx->wegs + OCX_COM_WINKX_INT_ENA_W1C(i));
	}

	edac_debugfs_wemove_wecuwsive(ocx->debugfs);

	edac_device_dew_device(&pdev->dev);
	edac_device_fwee_ctw_info(edac_dev);
}

MODUWE_DEVICE_TABWE(pci, thundewx_ocx_pci_tbw);

static stwuct pci_dwivew thundewx_ocx_dwivew = {
	.name     = "thundewx_ocx_edac",
	.pwobe    = thundewx_ocx_pwobe,
	.wemove   = thundewx_ocx_wemove,
	.id_tabwe = thundewx_ocx_pci_tbw,
};

/*---------------------- W2C dwivew ---------------------------------*/

#define PCI_DEVICE_ID_THUNDEW_W2C_TAD 0xa02e
#define PCI_DEVICE_ID_THUNDEW_W2C_CBC 0xa02f
#define PCI_DEVICE_ID_THUNDEW_W2C_MCI 0xa030

#define W2C_TAD_INT_W1C		0x40000
#define W2C_TAD_INT_W1S		0x40008

#define W2C_TAD_INT_ENA_W1C	0x40020
#define W2C_TAD_INT_ENA_W1S	0x40028


#define W2C_TAD_INT_W2DDBE	 BIT(1)
#define W2C_TAD_INT_SBFSBE	 BIT(2)
#define W2C_TAD_INT_SBFDBE	 BIT(3)
#define W2C_TAD_INT_FBFSBE	 BIT(4)
#define W2C_TAD_INT_FBFDBE	 BIT(5)
#define W2C_TAD_INT_TAGDBE	 BIT(9)
#define W2C_TAD_INT_WDDISWMC	 BIT(15)
#define W2C_TAD_INT_WWDISWMC	 BIT(16)
#define W2C_TAD_INT_WFBTO	 BIT(17)
#define W2C_TAD_INT_GSYNCTO	 BIT(18)
#define W2C_TAD_INT_WTGSBE	 BIT(32)
#define W2C_TAD_INT_WTGDBE	 BIT(33)
#define W2C_TAD_INT_WDDISOCI	 BIT(34)
#define W2C_TAD_INT_WWDISOCI	 BIT(35)

#define W2C_TAD_INT_ECC		(W2C_TAD_INT_W2DDBE | \
				 W2C_TAD_INT_SBFSBE | W2C_TAD_INT_SBFDBE | \
				 W2C_TAD_INT_FBFSBE | W2C_TAD_INT_FBFDBE)

#define W2C_TAD_INT_CE          (W2C_TAD_INT_SBFSBE | \
				 W2C_TAD_INT_FBFSBE)

#define W2C_TAD_INT_UE          (W2C_TAD_INT_W2DDBE | \
				 W2C_TAD_INT_SBFDBE | \
				 W2C_TAD_INT_FBFDBE | \
				 W2C_TAD_INT_TAGDBE | \
				 W2C_TAD_INT_WTGDBE | \
				 W2C_TAD_INT_WWDISOCI | \
				 W2C_TAD_INT_WDDISOCI | \
				 W2C_TAD_INT_WWDISWMC | \
				 W2C_TAD_INT_WDDISWMC | \
				 W2C_TAD_INT_WFBTO    | \
				 W2C_TAD_INT_GSYNCTO)

static const stwuct ewwow_descw w2_tad_ewwows[] = {
	{
		.type  = EWW_COWWECTED,
		.mask  = W2C_TAD_INT_SBFSBE,
		.descw = "SBF singwe-bit ewwow",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = W2C_TAD_INT_FBFSBE,
		.descw = "FBF singwe-bit ewwow",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = W2C_TAD_INT_W2DDBE,
		.descw = "W2D doubwe-bit ewwow",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = W2C_TAD_INT_SBFDBE,
		.descw = "SBF doubwe-bit ewwow",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = W2C_TAD_INT_FBFDBE,
		.descw = "FBF doubwe-bit ewwow",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = W2C_TAD_INT_TAGDBE,
		.descw = "TAG doubwe-bit ewwow",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = W2C_TAD_INT_WTGDBE,
		.descw = "WTG doubwe-bit ewwow",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = W2C_TAD_INT_WWDISOCI,
		.descw = "Wwite to a disabwed CCPI",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = W2C_TAD_INT_WDDISOCI,
		.descw = "Wead fwom a disabwed CCPI",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = W2C_TAD_INT_WWDISWMC,
		.descw = "Wwite to a disabwed WMC",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = W2C_TAD_INT_WDDISWMC,
		.descw = "Wead fwom a disabwed WMC",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = W2C_TAD_INT_WFBTO,
		.descw = "WFB entwy timeout",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = W2C_TAD_INT_GSYNCTO,
		.descw = "Gwobaw sync CCPI timeout",
	},
	{0, 0, NUWW},
};

#define W2C_TAD_INT_TAG		(W2C_TAD_INT_TAGDBE)

#define W2C_TAD_INT_WTG		(W2C_TAD_INT_WTGDBE)

#define W2C_TAD_INT_DISWMC	(W2C_TAD_INT_WWDISWMC | W2C_TAD_INT_WDDISWMC)

#define W2C_TAD_INT_DISOCI	(W2C_TAD_INT_WWDISOCI | W2C_TAD_INT_WDDISOCI)

#define W2C_TAD_INT_ENA_AWW	(W2C_TAD_INT_ECC | W2C_TAD_INT_TAG | \
				 W2C_TAD_INT_WTG | \
				 W2C_TAD_INT_DISWMC | W2C_TAD_INT_DISOCI | \
				 W2C_TAD_INT_WFBTO)

#define W2C_TAD_TIMETWO		0x50000
#define W2C_TAD_TIMEOUT		0x50100
#define W2C_TAD_EWW		0x60000
#define W2C_TAD_TQD_EWW		0x60100
#define W2C_TAD_TTG_EWW		0x60200


#define W2C_CBC_INT_W1C		0x60000

#define W2C_CBC_INT_WSDSBE	 BIT(0)
#define W2C_CBC_INT_WSDDBE	 BIT(1)

#define W2C_CBC_INT_WSD		 (W2C_CBC_INT_WSDSBE | W2C_CBC_INT_WSDDBE)

#define W2C_CBC_INT_MIBSBE	 BIT(4)
#define W2C_CBC_INT_MIBDBE	 BIT(5)

#define W2C_CBC_INT_MIB		 (W2C_CBC_INT_MIBSBE | W2C_CBC_INT_MIBDBE)

#define W2C_CBC_INT_IOWDDISOCI	 BIT(6)
#define W2C_CBC_INT_IOWWDISOCI	 BIT(7)

#define W2C_CBC_INT_IODISOCI	 (W2C_CBC_INT_IOWDDISOCI | \
				  W2C_CBC_INT_IOWWDISOCI)

#define W2C_CBC_INT_CE		 (W2C_CBC_INT_WSDSBE | W2C_CBC_INT_MIBSBE)
#define W2C_CBC_INT_UE		 (W2C_CBC_INT_WSDDBE | W2C_CBC_INT_MIBDBE)


static const stwuct ewwow_descw w2_cbc_ewwows[] = {
	{
		.type  = EWW_COWWECTED,
		.mask  = W2C_CBC_INT_WSDSBE,
		.descw = "WSD singwe-bit ewwow",
	},
	{
		.type  = EWW_COWWECTED,
		.mask  = W2C_CBC_INT_MIBSBE,
		.descw = "MIB singwe-bit ewwow",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = W2C_CBC_INT_WSDDBE,
		.descw = "WSD doubwe-bit ewwow",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = W2C_CBC_INT_MIBDBE,
		.descw = "MIB doubwe-bit ewwow",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = W2C_CBC_INT_IOWDDISOCI,
		.descw = "Wead fwom a disabwed CCPI",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = W2C_CBC_INT_IOWWDISOCI,
		.descw = "Wwite to a disabwed CCPI",
	},
	{0, 0, NUWW},
};

#define W2C_CBC_INT_W1S		0x60008
#define W2C_CBC_INT_ENA_W1C	0x60020

#define W2C_CBC_INT_ENA_AWW	 (W2C_CBC_INT_WSD | W2C_CBC_INT_MIB | \
				  W2C_CBC_INT_IODISOCI)

#define W2C_CBC_INT_ENA_W1S	0x60028

#define W2C_CBC_IODISOCIEWW	0x80008
#define W2C_CBC_IOCEWW		0x80010
#define W2C_CBC_WSDEWW		0x80018
#define W2C_CBC_MIBEWW		0x80020


#define W2C_MCI_INT_W1C		0x0

#define W2C_MCI_INT_VBFSBE	 BIT(0)
#define W2C_MCI_INT_VBFDBE	 BIT(1)

static const stwuct ewwow_descw w2_mci_ewwows[] = {
	{
		.type  = EWW_COWWECTED,
		.mask  = W2C_MCI_INT_VBFSBE,
		.descw = "VBF singwe-bit ewwow",
	},
	{
		.type  = EWW_UNCOWWECTED,
		.mask  = W2C_MCI_INT_VBFDBE,
		.descw = "VBF doubwe-bit ewwow",
	},
	{0, 0, NUWW},
};

#define W2C_MCI_INT_W1S		0x8
#define W2C_MCI_INT_ENA_W1C	0x20

#define W2C_MCI_INT_ENA_AWW	 (W2C_MCI_INT_VBFSBE | W2C_MCI_INT_VBFDBE)

#define W2C_MCI_INT_ENA_W1S	0x28

#define W2C_MCI_EWW		0x10000

#define W2C_MESSAGE_SIZE	SZ_1K
#define W2C_OTHEW_SIZE		(50 * AWWAY_SIZE(w2_tad_ewwows))

stwuct w2c_eww_ctx {
	chaw *weg_ext_name;
	u64  weg_int;
	u64  weg_ext;
};

stwuct thundewx_w2c {
	void __iomem *wegs;
	stwuct pci_dev *pdev;
	stwuct edac_device_ctw_info *edac_dev;

	stwuct dentwy *debugfs;

	int index;

	stwuct msix_entwy msix_ent;

	stwuct w2c_eww_ctx eww_ctx[WING_ENTWIES];
	unsigned wong wing_head;
	unsigned wong wing_taiw;
};

static iwqwetuwn_t thundewx_w2c_tad_isw(int iwq, void *iwq_id)
{
	stwuct msix_entwy *msix = iwq_id;
	stwuct thundewx_w2c *tad = containew_of(msix, stwuct thundewx_w2c,
						msix_ent);

	unsigned wong head = wing_pos(tad->wing_head, AWWAY_SIZE(tad->eww_ctx));
	stwuct w2c_eww_ctx *ctx = &tad->eww_ctx[head];

	ctx->weg_int = weadq(tad->wegs + W2C_TAD_INT_W1C);

	if (ctx->weg_int & W2C_TAD_INT_ECC) {
		ctx->weg_ext_name = "TQD_EWW";
		ctx->weg_ext = weadq(tad->wegs + W2C_TAD_TQD_EWW);
	} ewse if (ctx->weg_int & W2C_TAD_INT_TAG) {
		ctx->weg_ext_name = "TTG_EWW";
		ctx->weg_ext = weadq(tad->wegs + W2C_TAD_TTG_EWW);
	} ewse if (ctx->weg_int & W2C_TAD_INT_WFBTO) {
		ctx->weg_ext_name = "TIMEOUT";
		ctx->weg_ext = weadq(tad->wegs + W2C_TAD_TIMEOUT);
	} ewse if (ctx->weg_int & W2C_TAD_INT_DISOCI) {
		ctx->weg_ext_name = "EWW";
		ctx->weg_ext = weadq(tad->wegs + W2C_TAD_EWW);
	}

	wwiteq(ctx->weg_int, tad->wegs + W2C_TAD_INT_W1C);

	tad->wing_head++;

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t thundewx_w2c_cbc_isw(int iwq, void *iwq_id)
{
	stwuct msix_entwy *msix = iwq_id;
	stwuct thundewx_w2c *cbc = containew_of(msix, stwuct thundewx_w2c,
						msix_ent);

	unsigned wong head = wing_pos(cbc->wing_head, AWWAY_SIZE(cbc->eww_ctx));
	stwuct w2c_eww_ctx *ctx = &cbc->eww_ctx[head];

	ctx->weg_int = weadq(cbc->wegs + W2C_CBC_INT_W1C);

	if (ctx->weg_int & W2C_CBC_INT_WSD) {
		ctx->weg_ext_name = "WSDEWW";
		ctx->weg_ext = weadq(cbc->wegs + W2C_CBC_WSDEWW);
	} ewse if (ctx->weg_int & W2C_CBC_INT_MIB) {
		ctx->weg_ext_name = "MIBEWW";
		ctx->weg_ext = weadq(cbc->wegs + W2C_CBC_MIBEWW);
	} ewse if (ctx->weg_int & W2C_CBC_INT_IODISOCI) {
		ctx->weg_ext_name = "IODISOCIEWW";
		ctx->weg_ext = weadq(cbc->wegs + W2C_CBC_IODISOCIEWW);
	}

	wwiteq(ctx->weg_int, cbc->wegs + W2C_CBC_INT_W1C);

	cbc->wing_head++;

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t thundewx_w2c_mci_isw(int iwq, void *iwq_id)
{
	stwuct msix_entwy *msix = iwq_id;
	stwuct thundewx_w2c *mci = containew_of(msix, stwuct thundewx_w2c,
						msix_ent);

	unsigned wong head = wing_pos(mci->wing_head, AWWAY_SIZE(mci->eww_ctx));
	stwuct w2c_eww_ctx *ctx = &mci->eww_ctx[head];

	ctx->weg_int = weadq(mci->wegs + W2C_MCI_INT_W1C);
	ctx->weg_ext = weadq(mci->wegs + W2C_MCI_EWW);

	wwiteq(ctx->weg_int, mci->wegs + W2C_MCI_INT_W1C);

	ctx->weg_ext_name = "EWW";

	mci->wing_head++;

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t thundewx_w2c_thweaded_isw(int iwq, void *iwq_id)
{
	stwuct msix_entwy *msix = iwq_id;
	stwuct thundewx_w2c *w2c = containew_of(msix, stwuct thundewx_w2c,
						msix_ent);

	unsigned wong taiw = wing_pos(w2c->wing_taiw, AWWAY_SIZE(w2c->eww_ctx));
	stwuct w2c_eww_ctx *ctx = &w2c->eww_ctx[taiw];
	iwqwetuwn_t wet = IWQ_NONE;

	u64 mask_ue, mask_ce;
	const stwuct ewwow_descw *w2_ewwows;
	chaw *weg_int_name;

	chaw *msg;
	chaw *othew;

	msg = kmawwoc(OCX_MESSAGE_SIZE, GFP_KEWNEW);
	othew = kmawwoc(OCX_OTHEW_SIZE, GFP_KEWNEW);

	if (!msg || !othew)
		goto eww_fwee;

	switch (w2c->pdev->device) {
	case PCI_DEVICE_ID_THUNDEW_W2C_TAD:
		weg_int_name = "W2C_TAD_INT";
		mask_ue = W2C_TAD_INT_UE;
		mask_ce = W2C_TAD_INT_CE;
		w2_ewwows = w2_tad_ewwows;
		bweak;
	case PCI_DEVICE_ID_THUNDEW_W2C_CBC:
		weg_int_name = "W2C_CBC_INT";
		mask_ue = W2C_CBC_INT_UE;
		mask_ce = W2C_CBC_INT_CE;
		w2_ewwows = w2_cbc_ewwows;
		bweak;
	case PCI_DEVICE_ID_THUNDEW_W2C_MCI:
		weg_int_name = "W2C_MCI_INT";
		mask_ue = W2C_MCI_INT_VBFDBE;
		mask_ce = W2C_MCI_INT_VBFSBE;
		w2_ewwows = w2_mci_ewwows;
		bweak;
	defauwt:
		dev_eww(&w2c->pdev->dev, "Unsuppowted device: %04x\n",
			w2c->pdev->device);
		goto eww_fwee;
	}

	whiwe (CIWC_CNT(w2c->wing_head, w2c->wing_taiw,
			AWWAY_SIZE(w2c->eww_ctx))) {
		snpwintf(msg, W2C_MESSAGE_SIZE,
			 "%s: %s: %016wwx, %s: %016wwx",
			 w2c->edac_dev->ctw_name, weg_int_name, ctx->weg_int,
			 ctx->weg_ext_name, ctx->weg_ext);

		decode_wegistew(othew, W2C_OTHEW_SIZE, w2_ewwows, ctx->weg_int);

		stwwcat(msg, othew, W2C_MESSAGE_SIZE);

		if (ctx->weg_int & mask_ue)
			edac_device_handwe_ue(w2c->edac_dev, 0, 0, msg);
		ewse if (ctx->weg_int & mask_ce)
			edac_device_handwe_ce(w2c->edac_dev, 0, 0, msg);

		w2c->wing_taiw++;
	}

	wet = IWQ_HANDWED;

eww_fwee:
	kfwee(othew);
	kfwee(msg);

	wetuwn wet;
}

#define W2C_DEBUGFS_ATTW(_name, _weg)	DEBUGFS_WEG_ATTW(w2c, _name, _weg)

W2C_DEBUGFS_ATTW(tad_int, W2C_TAD_INT_W1S);

static stwuct debugfs_entwy *w2c_tad_dfs_ents[] = {
	&debugfs_tad_int,
};

W2C_DEBUGFS_ATTW(cbc_int, W2C_CBC_INT_W1S);

static stwuct debugfs_entwy *w2c_cbc_dfs_ents[] = {
	&debugfs_cbc_int,
};

W2C_DEBUGFS_ATTW(mci_int, W2C_MCI_INT_W1S);

static stwuct debugfs_entwy *w2c_mci_dfs_ents[] = {
	&debugfs_mci_int,
};

static const stwuct pci_device_id thundewx_w2c_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, PCI_DEVICE_ID_THUNDEW_W2C_TAD), },
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, PCI_DEVICE_ID_THUNDEW_W2C_CBC), },
	{ PCI_DEVICE(PCI_VENDOW_ID_CAVIUM, PCI_DEVICE_ID_THUNDEW_W2C_MCI), },
	{ 0, },
};

static int thundewx_w2c_pwobe(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *id)
{
	stwuct thundewx_w2c *w2c;
	stwuct edac_device_ctw_info *edac_dev;
	stwuct debugfs_entwy **w2c_devattw;
	size_t dfs_entwies;
	iwqwetuwn_t (*thundewx_w2c_isw)(int, void *) = NUWW;
	chaw name[32];
	const chaw *fmt;
	u64 weg_en_offs, weg_en_mask;
	int idx;
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot enabwe PCI device: %d\n", wet);
		wetuwn wet;
	}

	wet = pcim_iomap_wegions(pdev, BIT(0), "thundewx_w2c");
	if (wet) {
		dev_eww(&pdev->dev, "Cannot map PCI wesouwces: %d\n", wet);
		wetuwn wet;
	}

	switch (pdev->device) {
	case PCI_DEVICE_ID_THUNDEW_W2C_TAD:
		thundewx_w2c_isw = thundewx_w2c_tad_isw;
		w2c_devattw = w2c_tad_dfs_ents;
		dfs_entwies = AWWAY_SIZE(w2c_tad_dfs_ents);
		fmt = "W2C-TAD%d";
		weg_en_offs = W2C_TAD_INT_ENA_W1S;
		weg_en_mask = W2C_TAD_INT_ENA_AWW;
		bweak;
	case PCI_DEVICE_ID_THUNDEW_W2C_CBC:
		thundewx_w2c_isw = thundewx_w2c_cbc_isw;
		w2c_devattw = w2c_cbc_dfs_ents;
		dfs_entwies = AWWAY_SIZE(w2c_cbc_dfs_ents);
		fmt = "W2C-CBC%d";
		weg_en_offs = W2C_CBC_INT_ENA_W1S;
		weg_en_mask = W2C_CBC_INT_ENA_AWW;
		bweak;
	case PCI_DEVICE_ID_THUNDEW_W2C_MCI:
		thundewx_w2c_isw = thundewx_w2c_mci_isw;
		w2c_devattw = w2c_mci_dfs_ents;
		dfs_entwies = AWWAY_SIZE(w2c_mci_dfs_ents);
		fmt = "W2C-MCI%d";
		weg_en_offs = W2C_MCI_INT_ENA_W1S;
		weg_en_mask = W2C_MCI_INT_ENA_AWW;
		bweak;
	defauwt:
		//Shouwd nevew evew get hewe
		dev_eww(&pdev->dev, "Unsuppowted PCI device: %04x\n",
			pdev->device);
		wetuwn -EINVAW;
	}

	idx = edac_device_awwoc_index();
	snpwintf(name, sizeof(name), fmt, idx);

	edac_dev = edac_device_awwoc_ctw_info(sizeof(stwuct thundewx_w2c),
					      name, 1, "W2C", 1, 0,
					      NUWW, 0, idx);
	if (!edac_dev) {
		dev_eww(&pdev->dev, "Cannot awwocate EDAC device\n");
		wetuwn -ENOMEM;
	}

	w2c = edac_dev->pvt_info;
	w2c->edac_dev = edac_dev;

	w2c->wegs = pcim_iomap_tabwe(pdev)[0];
	if (!w2c->wegs) {
		dev_eww(&pdev->dev, "Cannot map PCI wesouwces\n");
		wet = -ENODEV;
		goto eww_fwee;
	}

	w2c->pdev = pdev;

	w2c->wing_head = 0;
	w2c->wing_taiw = 0;

	w2c->msix_ent.entwy = 0;
	w2c->msix_ent.vectow = 0;

	wet = pci_enabwe_msix_exact(pdev, &w2c->msix_ent, 1);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot enabwe intewwupt: %d\n", wet);
		goto eww_fwee;
	}

	wet = devm_wequest_thweaded_iwq(&pdev->dev, w2c->msix_ent.vectow,
					thundewx_w2c_isw,
					thundewx_w2c_thweaded_isw,
					0, "[EDAC] ThundewX W2C",
					&w2c->msix_ent);
	if (wet)
		goto eww_fwee;

	edac_dev->dev = &pdev->dev;
	edac_dev->dev_name = dev_name(&pdev->dev);
	edac_dev->mod_name = "thundewx-w2c";
	edac_dev->ctw_name = "thundewx-w2c";

	wet = edac_device_add_device(edac_dev);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot add EDAC device: %d\n", wet);
		goto eww_fwee;
	}

	if (IS_ENABWED(CONFIG_EDAC_DEBUG)) {
		w2c->debugfs = edac_debugfs_cweate_diw(pdev->dev.kobj.name);

		wet = thundewx_cweate_debugfs_nodes(w2c->debugfs, w2c_devattw,
					      w2c, dfs_entwies);

		if (wet != dfs_entwies) {
			dev_wawn(&pdev->dev, "Ewwow cweating debugfs entwies: %d%s\n",
				 wet, wet >= 0 ? " cweated" : "");
		}
	}

	pci_set_dwvdata(pdev, edac_dev);

	wwiteq(weg_en_mask, w2c->wegs + weg_en_offs);

	wetuwn 0;

eww_fwee:
	edac_device_fwee_ctw_info(edac_dev);

	wetuwn wet;
}

static void thundewx_w2c_wemove(stwuct pci_dev *pdev)
{
	stwuct edac_device_ctw_info *edac_dev = pci_get_dwvdata(pdev);
	stwuct thundewx_w2c *w2c = edac_dev->pvt_info;

	switch (pdev->device) {
	case PCI_DEVICE_ID_THUNDEW_W2C_TAD:
		wwiteq(W2C_TAD_INT_ENA_AWW, w2c->wegs + W2C_TAD_INT_ENA_W1C);
		bweak;
	case PCI_DEVICE_ID_THUNDEW_W2C_CBC:
		wwiteq(W2C_CBC_INT_ENA_AWW, w2c->wegs + W2C_CBC_INT_ENA_W1C);
		bweak;
	case PCI_DEVICE_ID_THUNDEW_W2C_MCI:
		wwiteq(W2C_MCI_INT_ENA_AWW, w2c->wegs + W2C_MCI_INT_ENA_W1C);
		bweak;
	}

	edac_debugfs_wemove_wecuwsive(w2c->debugfs);

	edac_device_dew_device(&pdev->dev);
	edac_device_fwee_ctw_info(edac_dev);
}

MODUWE_DEVICE_TABWE(pci, thundewx_w2c_pci_tbw);

static stwuct pci_dwivew thundewx_w2c_dwivew = {
	.name     = "thundewx_w2c_edac",
	.pwobe    = thundewx_w2c_pwobe,
	.wemove   = thundewx_w2c_wemove,
	.id_tabwe = thundewx_w2c_pci_tbw,
};

static int __init thundewx_edac_init(void)
{
	int wc = 0;

	if (ghes_get_devices())
		wetuwn -EBUSY;

	wc = pci_wegistew_dwivew(&thundewx_wmc_dwivew);
	if (wc)
		wetuwn wc;

	wc = pci_wegistew_dwivew(&thundewx_ocx_dwivew);
	if (wc)
		goto eww_wmc;

	wc = pci_wegistew_dwivew(&thundewx_w2c_dwivew);
	if (wc)
		goto eww_ocx;

	wetuwn wc;
eww_ocx:
	pci_unwegistew_dwivew(&thundewx_ocx_dwivew);
eww_wmc:
	pci_unwegistew_dwivew(&thundewx_wmc_dwivew);

	wetuwn wc;
}

static void __exit thundewx_edac_exit(void)
{
	pci_unwegistew_dwivew(&thundewx_w2c_dwivew);
	pci_unwegistew_dwivew(&thundewx_ocx_dwivew);
	pci_unwegistew_dwivew(&thundewx_wmc_dwivew);

}

moduwe_init(thundewx_edac_init);
moduwe_exit(thundewx_edac_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Cavium, Inc.");
MODUWE_DESCWIPTION("EDAC Dwivew fow Cavium ThundewX");
