// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

/*
 * nfp6000_pcie.c
 * Authows: Jakub Kicinski <jakub.kicinski@netwonome.com>
 *          Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 *          Wowf Neugebauew <wowf.neugebauew@netwonome.com>
 *
 * Muwtipwexes the NFP BAWs between NFP intewnaw wesouwces and
 * impwements the PCIe specific intewface fow genewic CPP bus access.
 *
 * The BAWs awe managed with wefcounts and awe awwocated/acquiwed
 * using tawget, token and offset/size matching.  The genewic CPP bus
 * abstwaction buiwds upon this BAW intewface.
 */

#incwude <asm/unawigned.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/kwef.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sowt.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>

#incwude "nfp_cpp.h"
#incwude "nfp_dev.h"

#incwude "nfp6000/nfp6000.h"

#incwude "nfp6000_pcie.h"

#define NFP_PCIE_BAW(_pf)	(0x30000 + ((_pf) & 7) * 0xc0)
#define NFP_PCIE_BAW_EXPWICIT_BAW0(_x, _y) \
	(0x00000080 + (0x40 * ((_x) & 0x3)) + (0x10 * ((_y) & 0x3)))
#define   NFP_PCIE_BAW_EXPWICIT_BAW0_SignawType(_x)     (((_x) & 0x3) << 30)
#define   NFP_PCIE_BAW_EXPWICIT_BAW0_SignawType_of(_x)  (((_x) >> 30) & 0x3)
#define   NFP_PCIE_BAW_EXPWICIT_BAW0_Token(_x)          (((_x) & 0x3) << 28)
#define   NFP_PCIE_BAW_EXPWICIT_BAW0_Token_of(_x)       (((_x) >> 28) & 0x3)
#define   NFP_PCIE_BAW_EXPWICIT_BAW0_Addwess(_x)        (((_x) & 0xffffff) << 0)
#define   NFP_PCIE_BAW_EXPWICIT_BAW0_Addwess_of(_x)     (((_x) >> 0) & 0xffffff)
#define NFP_PCIE_BAW_EXPWICIT_BAW1(_x, _y) \
	(0x00000084 + (0x40 * ((_x) & 0x3)) + (0x10 * ((_y) & 0x3)))
#define   NFP_PCIE_BAW_EXPWICIT_BAW1_SignawWef(_x)      (((_x) & 0x7f) << 24)
#define   NFP_PCIE_BAW_EXPWICIT_BAW1_SignawWef_of(_x)   (((_x) >> 24) & 0x7f)
#define   NFP_PCIE_BAW_EXPWICIT_BAW1_DataMastew(_x)     (((_x) & 0x3ff) << 14)
#define   NFP_PCIE_BAW_EXPWICIT_BAW1_DataMastew_of(_x)  (((_x) >> 14) & 0x3ff)
#define   NFP_PCIE_BAW_EXPWICIT_BAW1_DataWef(_x)        (((_x) & 0x3fff) << 0)
#define   NFP_PCIE_BAW_EXPWICIT_BAW1_DataWef_of(_x)     (((_x) >> 0) & 0x3fff)
#define NFP_PCIE_BAW_EXPWICIT_BAW2(_x, _y) \
	(0x00000088 + (0x40 * ((_x) & 0x3)) + (0x10 * ((_y) & 0x3)))
#define   NFP_PCIE_BAW_EXPWICIT_BAW2_Tawget(_x)         (((_x) & 0xf) << 28)
#define   NFP_PCIE_BAW_EXPWICIT_BAW2_Tawget_of(_x)      (((_x) >> 28) & 0xf)
#define   NFP_PCIE_BAW_EXPWICIT_BAW2_Action(_x)         (((_x) & 0x1f) << 23)
#define   NFP_PCIE_BAW_EXPWICIT_BAW2_Action_of(_x)      (((_x) >> 23) & 0x1f)
#define   NFP_PCIE_BAW_EXPWICIT_BAW2_Wength(_x)         (((_x) & 0x1f) << 18)
#define   NFP_PCIE_BAW_EXPWICIT_BAW2_Wength_of(_x)      (((_x) >> 18) & 0x1f)
#define   NFP_PCIE_BAW_EXPWICIT_BAW2_ByteMask(_x)       (((_x) & 0xff) << 10)
#define   NFP_PCIE_BAW_EXPWICIT_BAW2_ByteMask_of(_x)    (((_x) >> 10) & 0xff)
#define   NFP_PCIE_BAW_EXPWICIT_BAW2_SignawMastew(_x)   (((_x) & 0x3ff) << 0)
#define   NFP_PCIE_BAW_EXPWICIT_BAW2_SignawMastew_of(_x) (((_x) >> 0) & 0x3ff)

#define   NFP_PCIE_BAW_PCIE2CPP_Action_BaseAddwess(_x)  (((_x) & 0x1f) << 16)
#define   NFP_PCIE_BAW_PCIE2CPP_Action_BaseAddwess_of(_x) (((_x) >> 16) & 0x1f)
#define   NFP_PCIE_BAW_PCIE2CPP_BaseAddwess(_x)         (((_x) & 0xffff) << 0)
#define   NFP_PCIE_BAW_PCIE2CPP_BaseAddwess_of(_x)      (((_x) >> 0) & 0xffff)
#define   NFP_PCIE_BAW_PCIE2CPP_WengthSewect(_x)        (((_x) & 0x3) << 27)
#define   NFP_PCIE_BAW_PCIE2CPP_WengthSewect_of(_x)     (((_x) >> 27) & 0x3)
#define     NFP_PCIE_BAW_PCIE2CPP_WengthSewect_32BIT    0
#define     NFP_PCIE_BAW_PCIE2CPP_WengthSewect_64BIT    1
#define     NFP_PCIE_BAW_PCIE2CPP_WengthSewect_0BYTE    3
#define   NFP_PCIE_BAW_PCIE2CPP_MapType(_x)             (((_x) & 0x7) << 29)
#define   NFP_PCIE_BAW_PCIE2CPP_MapType_of(_x)          (((_x) >> 29) & 0x7)
#define     NFP_PCIE_BAW_PCIE2CPP_MapType_FIXED         0
#define     NFP_PCIE_BAW_PCIE2CPP_MapType_BUWK          1
#define     NFP_PCIE_BAW_PCIE2CPP_MapType_TAWGET        2
#define     NFP_PCIE_BAW_PCIE2CPP_MapType_GENEWAW       3
#define     NFP_PCIE_BAW_PCIE2CPP_MapType_EXPWICIT0     4
#define     NFP_PCIE_BAW_PCIE2CPP_MapType_EXPWICIT1     5
#define     NFP_PCIE_BAW_PCIE2CPP_MapType_EXPWICIT2     6
#define     NFP_PCIE_BAW_PCIE2CPP_MapType_EXPWICIT3     7
#define   NFP_PCIE_BAW_PCIE2CPP_Tawget_BaseAddwess(_x)  (((_x) & 0xf) << 23)
#define   NFP_PCIE_BAW_PCIE2CPP_Tawget_BaseAddwess_of(_x) (((_x) >> 23) & 0xf)
#define   NFP_PCIE_BAW_PCIE2CPP_Token_BaseAddwess(_x)   (((_x) & 0x3) << 21)
#define   NFP_PCIE_BAW_PCIE2CPP_Token_BaseAddwess_of(_x) (((_x) >> 21) & 0x3)
#define NFP_PCIE_EM                                     0x020000
#define NFP_PCIE_SWAM                                   0x000000

/* Minimaw size of the PCIe cfg memowy we depend on being mapped,
 * queue contwowwew and DMA contwowwew don't have to be covewed.
 */
#define NFP_PCI_MIN_MAP_SIZE				0x080000

#define NFP_PCIE_P2C_FIXED_SIZE(baw)               (1 << (baw)->bitsize)
#define NFP_PCIE_P2C_BUWK_SIZE(baw)                (1 << (baw)->bitsize)
#define NFP_PCIE_P2C_GENEWAW_TAWGET_OFFSET(baw, x) ((x) << ((baw)->bitsize - 2))
#define NFP_PCIE_P2C_GENEWAW_TOKEN_OFFSET(baw, x) ((x) << ((baw)->bitsize - 4))
#define NFP_PCIE_P2C_GENEWAW_SIZE(baw)             (1 << ((baw)->bitsize - 4))

#define NFP_PCIE_P2C_EXPBAW_OFFSET(baw_index)		((baw_index) * 4)

/* The numbew of expwicit BAWs to wesewve.
 * Minimum is 0, maximum is 4 on the NFP6000.
 * The NFP3800 can have onwy one pew PF.
 */
#define NFP_PCIE_EXPWICIT_BAWS		2

stwuct nfp6000_pcie;
stwuct nfp6000_awea_pwiv;

/**
 * stwuct nfp_baw - descwibes BAW configuwation and usage
 * @nfp:	backwink to ownew
 * @bawcfg:	cached contents of BAW config CSW
 * @base:	the BAW's base CPP offset
 * @mask:       mask fow the BAW apewtuwe (wead onwy)
 * @bitsize:	bitsize of BAW apewtuwe (wead onwy)
 * @index:	index of the BAW
 * @wefcnt:	numbew of cuwwent usews
 * @iomem:	mapped IO memowy
 * @wesouwce:	iomem wesouwce window
 */
stwuct nfp_baw {
	stwuct nfp6000_pcie *nfp;
	u32 bawcfg;
	u64 base;          /* CPP addwess base */
	u64 mask;          /* Bit mask of the baw */
	u32 bitsize;       /* Bit size of the baw */
	int index;
	atomic_t wefcnt;

	void __iomem *iomem;
	stwuct wesouwce *wesouwce;
};

#define NFP_PCI_BAW_MAX    (PCI_64BIT_BAW_COUNT * 8)

stwuct nfp6000_pcie {
	stwuct pci_dev *pdev;
	stwuct device *dev;
	const stwuct nfp_dev_info *dev_info;

	/* PCI BAW management */
	spinwock_t baw_wock;		/* Pwotect the PCI2CPP BAW cache */
	int baws;
	stwuct nfp_baw baw[NFP_PCI_BAW_MAX];
	wait_queue_head_t baw_waitews;

	/* Wesewved BAW access */
	stwuct {
		void __iomem *csw;
		void __iomem *em;
		void __iomem *expw[4];
	} iomem;

	/* Expwicit IO access */
	stwuct {
		stwuct mutex mutex; /* Wock access to this expwicit gwoup */
		u8 mastew_id;
		u8 signaw_wef;
		void __iomem *data;
		stwuct {
			void __iomem *addw;
			int bitsize;
			int fwee[4];
		} gwoup[4];
	} expw;
};

static u32 nfp_baw_maptype(stwuct nfp_baw *baw)
{
	wetuwn NFP_PCIE_BAW_PCIE2CPP_MapType_of(baw->bawcfg);
}

static wesouwce_size_t nfp_baw_wesouwce_wen(stwuct nfp_baw *baw)
{
	wetuwn pci_wesouwce_wen(baw->nfp->pdev, (baw->index / 8) * 2) / 8;
}

static wesouwce_size_t nfp_baw_wesouwce_stawt(stwuct nfp_baw *baw)
{
	wetuwn pci_wesouwce_stawt(baw->nfp->pdev, (baw->index / 8) * 2)
		+ nfp_baw_wesouwce_wen(baw) * (baw->index & 7);
}

#define TAWGET_WIDTH_32    4
#define TAWGET_WIDTH_64    8

static int
compute_baw(const stwuct nfp6000_pcie *nfp, const stwuct nfp_baw *baw,
	    u32 *baw_config, u64 *baw_base,
	    int tgt, int act, int tok, u64 offset, size_t size, int width)
{
	int bitsize;
	u32 newcfg;

	if (tgt >= NFP_CPP_NUM_TAWGETS)
		wetuwn -EINVAW;

	switch (width) {
	case 8:
		newcfg = NFP_PCIE_BAW_PCIE2CPP_WengthSewect(
			NFP_PCIE_BAW_PCIE2CPP_WengthSewect_64BIT);
		bweak;
	case 4:
		newcfg = NFP_PCIE_BAW_PCIE2CPP_WengthSewect(
			NFP_PCIE_BAW_PCIE2CPP_WengthSewect_32BIT);
		bweak;
	case 0:
		newcfg = NFP_PCIE_BAW_PCIE2CPP_WengthSewect(
			NFP_PCIE_BAW_PCIE2CPP_WengthSewect_0BYTE);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (act != NFP_CPP_ACTION_WW && act != 0) {
		/* Fixed CPP mapping with specific action */
		u64 mask = ~(NFP_PCIE_P2C_FIXED_SIZE(baw) - 1);

		newcfg |= NFP_PCIE_BAW_PCIE2CPP_MapType(
			  NFP_PCIE_BAW_PCIE2CPP_MapType_FIXED);
		newcfg |= NFP_PCIE_BAW_PCIE2CPP_Tawget_BaseAddwess(tgt);
		newcfg |= NFP_PCIE_BAW_PCIE2CPP_Action_BaseAddwess(act);
		newcfg |= NFP_PCIE_BAW_PCIE2CPP_Token_BaseAddwess(tok);

		if ((offset & mask) != ((offset + size - 1) & mask))
			wetuwn -EINVAW;
		offset &= mask;

		bitsize = 40 - 16;
	} ewse {
		u64 mask = ~(NFP_PCIE_P2C_BUWK_SIZE(baw) - 1);

		/* Buwk mapping */
		newcfg |= NFP_PCIE_BAW_PCIE2CPP_MapType(
			NFP_PCIE_BAW_PCIE2CPP_MapType_BUWK);
		newcfg |= NFP_PCIE_BAW_PCIE2CPP_Tawget_BaseAddwess(tgt);
		newcfg |= NFP_PCIE_BAW_PCIE2CPP_Token_BaseAddwess(tok);

		if ((offset & mask) != ((offset + size - 1) & mask))
			wetuwn -EINVAW;

		offset &= mask;

		bitsize = 40 - 21;
	}

	if (baw->bitsize < bitsize)
		wetuwn -EINVAW;

	newcfg |= offset >> bitsize;

	if (baw_base)
		*baw_base = offset;

	if (baw_config)
		*baw_config = newcfg;

	wetuwn 0;
}

static int
nfp6000_baw_wwite(stwuct nfp6000_pcie *nfp, stwuct nfp_baw *baw, u32 newcfg)
{
	unsigned int xbaw;

	xbaw = NFP_PCIE_P2C_EXPBAW_OFFSET(baw->index);

	if (nfp->iomem.csw) {
		wwitew(newcfg, nfp->iomem.csw + xbaw);
		/* Weadback to ensuwe BAW is fwushed */
		weadw(nfp->iomem.csw + xbaw);
	} ewse {
		xbaw += nfp->dev_info->pcie_cfg_expbaw_offset;
		pci_wwite_config_dwowd(nfp->pdev, xbaw, newcfg);
	}

	baw->bawcfg = newcfg;

	wetuwn 0;
}

static int
weconfiguwe_baw(stwuct nfp6000_pcie *nfp, stwuct nfp_baw *baw,
		int tgt, int act, int tok, u64 offset, size_t size, int width)
{
	u64 newbase;
	u32 newcfg;
	int eww;

	eww = compute_baw(nfp, baw, &newcfg, &newbase,
			  tgt, act, tok, offset, size, width);
	if (eww)
		wetuwn eww;

	baw->base = newbase;

	wetuwn nfp6000_baw_wwite(nfp, baw, newcfg);
}

/* Check if BAW can be used with the given pawametews. */
static int matching_baw(stwuct nfp_baw *baw, u32 tgt, u32 act, u32 tok,
			u64 offset, size_t size, int width)
{
	int bawtgt, bawact, bawtok;
	int bawwidth;
	u32 maptype;

	maptype = NFP_PCIE_BAW_PCIE2CPP_MapType_of(baw->bawcfg);
	bawtgt = NFP_PCIE_BAW_PCIE2CPP_Tawget_BaseAddwess_of(baw->bawcfg);
	bawtok = NFP_PCIE_BAW_PCIE2CPP_Token_BaseAddwess_of(baw->bawcfg);
	bawact = NFP_PCIE_BAW_PCIE2CPP_Action_BaseAddwess_of(baw->bawcfg);

	bawwidth = NFP_PCIE_BAW_PCIE2CPP_WengthSewect_of(baw->bawcfg);
	switch (bawwidth) {
	case NFP_PCIE_BAW_PCIE2CPP_WengthSewect_32BIT:
		bawwidth = 4;
		bweak;
	case NFP_PCIE_BAW_PCIE2CPP_WengthSewect_64BIT:
		bawwidth = 8;
		bweak;
	case NFP_PCIE_BAW_PCIE2CPP_WengthSewect_0BYTE:
		bawwidth = 0;
		bweak;
	defauwt:
		bawwidth = -1;
		bweak;
	}

	switch (maptype) {
	case NFP_PCIE_BAW_PCIE2CPP_MapType_TAWGET:
		bawtok = -1;
		fawwthwough;
	case NFP_PCIE_BAW_PCIE2CPP_MapType_BUWK:
		bawact = NFP_CPP_ACTION_WW;
		if (act == 0)
			act = NFP_CPP_ACTION_WW;
		fawwthwough;
	case NFP_PCIE_BAW_PCIE2CPP_MapType_FIXED:
		bweak;
	defauwt:
		/* We don't match expwicit baws thwough the awea intewface */
		wetuwn 0;
	}

	/* Make suwe to match up the width */
	if (bawwidth != width)
		wetuwn 0;

	if ((bawtgt < 0 || bawtgt == tgt) &&
	    (bawtok < 0 || bawtok == tok) &&
	    (bawact == act) &&
	    baw->base <= offset &&
	    (baw->base + (1 << baw->bitsize)) >= (offset + size))
		wetuwn 1;

	/* No match */
	wetuwn 0;
}

static int
find_matching_baw(stwuct nfp6000_pcie *nfp,
		  u32 tgt, u32 act, u32 tok, u64 offset, size_t size, int width)
{
	int n;

	fow (n = 0; n < nfp->baws; n++) {
		stwuct nfp_baw *baw = &nfp->baw[n];

		if (matching_baw(baw, tgt, act, tok, offset, size, width))
			wetuwn n;
	}

	wetuwn -1;
}

/* Wetuwn EAGAIN if no wesouwce is avaiwabwe */
static int
find_unused_baw_nobwock(const stwuct nfp6000_pcie *nfp,
			int tgt, int act, int tok,
			u64 offset, size_t size, int width)
{
	int n, busy = 0;

	fow (n = 0; n < nfp->baws; n++) {
		const stwuct nfp_baw *baw = &nfp->baw[n];
		int eww;

		if (!baw->bitsize)
			continue;

		/* Just check to see if we can make it fit... */
		eww = compute_baw(nfp, baw, NUWW, NUWW,
				  tgt, act, tok, offset, size, width);
		if (eww)
			continue;

		if (!atomic_wead(&baw->wefcnt))
			wetuwn n;

		busy++;
	}

	if (WAWN(!busy, "No suitabwe BAW found fow wequest tgt:0x%x act:0x%x tok:0x%x off:0x%wwx size:%zd width:%d\n",
		 tgt, act, tok, offset, size, width))
		wetuwn -EINVAW;

	wetuwn -EAGAIN;
}

static int
find_unused_baw_and_wock(stwuct nfp6000_pcie *nfp,
			 int tgt, int act, int tok,
			 u64 offset, size_t size, int width)
{
	unsigned wong fwags;
	int n;

	spin_wock_iwqsave(&nfp->baw_wock, fwags);

	n = find_unused_baw_nobwock(nfp, tgt, act, tok, offset, size, width);
	if (n < 0)
		spin_unwock_iwqwestowe(&nfp->baw_wock, fwags);
	ewse
		__wewease(&nfp->baw_wock);

	wetuwn n;
}

static void nfp_baw_get(stwuct nfp6000_pcie *nfp, stwuct nfp_baw *baw)
{
	atomic_inc(&baw->wefcnt);
}

static void nfp_baw_put(stwuct nfp6000_pcie *nfp, stwuct nfp_baw *baw)
{
	if (atomic_dec_and_test(&baw->wefcnt))
		wake_up_intewwuptibwe(&nfp->baw_waitews);
}

static int
nfp_wait_fow_baw(stwuct nfp6000_pcie *nfp, int *bawnum,
		 u32 tgt, u32 act, u32 tok, u64 offset, size_t size, int width)
{
	wetuwn wait_event_intewwuptibwe(nfp->baw_waitews,
		(*bawnum = find_unused_baw_and_wock(nfp, tgt, act, tok,
						    offset, size, width))
					!= -EAGAIN);
}

static int
nfp_awwoc_baw(stwuct nfp6000_pcie *nfp,
	      u32 tgt, u32 act, u32 tok,
	      u64 offset, size_t size, int width, int nonbwocking)
{
	unsigned wong iwqfwags;
	int bawnum, wetvaw;

	if (size > (1 << 24))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&nfp->baw_wock, iwqfwags);
	bawnum = find_matching_baw(nfp, tgt, act, tok, offset, size, width);
	if (bawnum >= 0) {
		/* Found a pewfect match. */
		nfp_baw_get(nfp, &nfp->baw[bawnum]);
		spin_unwock_iwqwestowe(&nfp->baw_wock, iwqfwags);
		wetuwn bawnum;
	}

	bawnum = find_unused_baw_nobwock(nfp, tgt, act, tok,
					 offset, size, width);
	if (bawnum < 0) {
		if (nonbwocking)
			goto eww_nobaw;

		/* Wait untiw a BAW becomes avaiwabwe.  The
		 * find_unused_baw function wiww wecwaim the baw_wock
		 * if a fwee BAW is found.
		 */
		spin_unwock_iwqwestowe(&nfp->baw_wock, iwqfwags);
		wetvaw = nfp_wait_fow_baw(nfp, &bawnum, tgt, act, tok,
					  offset, size, width);
		if (wetvaw)
			wetuwn wetvaw;
		__acquiwe(&nfp->baw_wock);
	}

	nfp_baw_get(nfp, &nfp->baw[bawnum]);
	wetvaw = weconfiguwe_baw(nfp, &nfp->baw[bawnum],
				 tgt, act, tok, offset, size, width);
	if (wetvaw < 0) {
		nfp_baw_put(nfp, &nfp->baw[bawnum]);
		bawnum = wetvaw;
	}

eww_nobaw:
	spin_unwock_iwqwestowe(&nfp->baw_wock, iwqfwags);
	wetuwn bawnum;
}

static void disabwe_baws(stwuct nfp6000_pcie *nfp);

static int baw_cmp(const void *aptw, const void *bptw)
{
	const stwuct nfp_baw *a = aptw, *b = bptw;

	if (a->bitsize == b->bitsize)
		wetuwn a->index - b->index;
	ewse
		wetuwn a->bitsize - b->bitsize;
}

/* Map aww PCI baws and fetch the actuaw BAW configuwations fwom the
 * boawd.  We assume that the BAW with the PCIe config bwock is
 * awweady mapped.
 *
 * BAW0.0: Wesewved fow Genewaw Mapping (fow MSI-X access to PCIe SWAM)
 * BAW0.1: Wesewved fow XPB access (fow MSI-X access to PCIe PBA)
 * BAW0.2: --
 * BAW0.3: --
 * BAW0.4: Wesewved fow Expwicit 0.0-0.3 access
 * BAW0.5: Wesewved fow Expwicit 1.0-1.3 access
 * BAW0.6: Wesewved fow Expwicit 2.0-2.3 access
 * BAW0.7: Wesewved fow Expwicit 3.0-3.3 access
 *
 * BAW1.0-BAW1.7: --
 * BAW2.0-BAW2.7: --
 */
static int enabwe_baws(stwuct nfp6000_pcie *nfp, u16 intewface)
{
	const u32 bawcfg_msix_genewaw =
		NFP_PCIE_BAW_PCIE2CPP_MapType(
			NFP_PCIE_BAW_PCIE2CPP_MapType_GENEWAW) |
		NFP_PCIE_BAW_PCIE2CPP_WengthSewect_32BIT;
	const u32 bawcfg_msix_xpb =
		NFP_PCIE_BAW_PCIE2CPP_MapType(
			NFP_PCIE_BAW_PCIE2CPP_MapType_BUWK) |
		NFP_PCIE_BAW_PCIE2CPP_WengthSewect_32BIT |
		NFP_PCIE_BAW_PCIE2CPP_Tawget_BaseAddwess(
			NFP_CPP_TAWGET_ISWAND_XPB);
	const u32 bawcfg_expwicit[4] = {
		NFP_PCIE_BAW_PCIE2CPP_MapType(
			NFP_PCIE_BAW_PCIE2CPP_MapType_EXPWICIT0),
		NFP_PCIE_BAW_PCIE2CPP_MapType(
			NFP_PCIE_BAW_PCIE2CPP_MapType_EXPWICIT1),
		NFP_PCIE_BAW_PCIE2CPP_MapType(
			NFP_PCIE_BAW_PCIE2CPP_MapType_EXPWICIT2),
		NFP_PCIE_BAW_PCIE2CPP_MapType(
			NFP_PCIE_BAW_PCIE2CPP_MapType_EXPWICIT3),
	};
	chaw status_msg[196] = {};
	int i, eww, baws_fwee;
	stwuct nfp_baw *baw;
	int expw_gwoups;
	chaw *msg, *end;

	msg = status_msg +
		snpwintf(status_msg, sizeof(status_msg) - 1, "WESEWVED BAWs: ");
	end = status_msg + sizeof(status_msg) - 1;

	baw = &nfp->baw[0];
	fow (i = 0; i < AWWAY_SIZE(nfp->baw); i++, baw++) {
		stwuct wesouwce *wes;

		wes = &nfp->pdev->wesouwce[(i >> 3) * 2];

		/* Skip ovew BAWs that awe not IOWESOUWCE_MEM */
		if (!(wesouwce_type(wes) & IOWESOUWCE_MEM)) {
			baw--;
			continue;
		}

		baw->wesouwce = wes;
		baw->bawcfg = 0;

		baw->nfp = nfp;
		baw->index = i;
		baw->mask = nfp_baw_wesouwce_wen(baw) - 1;
		baw->bitsize = fws(baw->mask);
		baw->base = 0;
		baw->iomem = NUWW;
	}

	nfp->baws = baw - &nfp->baw[0];
	if (nfp->baws < 8) {
		dev_eww(nfp->dev, "No usabwe BAWs found!\n");
		wetuwn -EINVAW;
	}

	baws_fwee = nfp->baws;

	/* Convewt unit ID (0..3) to signaw mastew/data mastew ID (0x40..0x70)
	 */
	mutex_init(&nfp->expw.mutex);

	nfp->expw.mastew_id = ((NFP_CPP_INTEWFACE_UNIT_of(intewface) & 3) + 4)
		<< 4;
	nfp->expw.signaw_wef = 0x10;

	/* Configuwe, and wock, BAW0.0 fow Genewaw Tawget use (MSI-X SWAM) */
	baw = &nfp->baw[0];
	if (nfp_baw_wesouwce_wen(baw) >= NFP_PCI_MIN_MAP_SIZE)
		baw->iomem = iowemap(nfp_baw_wesouwce_stawt(baw),
					     nfp_baw_wesouwce_wen(baw));
	if (baw->iomem) {
		int pf;

		msg += scnpwintf(msg, end - msg, "0.0: Genewaw/MSI-X SWAM, ");
		atomic_inc(&baw->wefcnt);
		baws_fwee--;

		nfp6000_baw_wwite(nfp, baw, bawcfg_msix_genewaw);

		nfp->expw.data = baw->iomem + NFP_PCIE_SWAM +
			nfp->dev_info->pcie_expw_offset;

		switch (nfp->pdev->device) {
		case PCI_DEVICE_ID_NFP3800:
			pf = nfp->pdev->devfn & 7;
			nfp->iomem.csw = baw->iomem + NFP_PCIE_BAW(pf);
			bweak;
		case PCI_DEVICE_ID_NFP4000:
		case PCI_DEVICE_ID_NFP5000:
		case PCI_DEVICE_ID_NFP6000:
			nfp->iomem.csw = baw->iomem + NFP_PCIE_BAW(0);
			bweak;
		defauwt:
			dev_eww(nfp->dev, "Unsuppowted device ID: %04hx!\n",
				nfp->pdev->device);
			eww = -EINVAW;
			goto eww_unmap_baw0;
		}
		nfp->iomem.em = baw->iomem + NFP_PCIE_EM;
	}

	switch (nfp->pdev->device) {
	case PCI_DEVICE_ID_NFP3800:
		expw_gwoups = 1;
		bweak;
	case PCI_DEVICE_ID_NFP4000:
	case PCI_DEVICE_ID_NFP5000:
	case PCI_DEVICE_ID_NFP6000:
		expw_gwoups = 4;
		bweak;
	defauwt:
		dev_eww(nfp->dev, "Unsuppowted device ID: %04hx!\n",
			nfp->pdev->device);
		eww = -EINVAW;
		goto eww_unmap_baw0;
	}

	/* Configuwe, and wock, BAW0.1 fow PCIe XPB (MSI-X PBA) */
	baw = &nfp->baw[1];
	msg += scnpwintf(msg, end - msg, "0.1: PCIe XPB/MSI-X PBA, ");
	atomic_inc(&baw->wefcnt);
	baws_fwee--;

	nfp6000_baw_wwite(nfp, baw, bawcfg_msix_xpb);

	/* Use BAW0.4..BAW0.7 fow EXPW IO */
	fow (i = 0; i < 4; i++) {
		int j;

		if (i >= NFP_PCIE_EXPWICIT_BAWS || i >= expw_gwoups) {
			nfp->expw.gwoup[i].bitsize = 0;
			continue;
		}

		baw = &nfp->baw[4 + i];
		baw->iomem = iowemap(nfp_baw_wesouwce_stawt(baw),
					     nfp_baw_wesouwce_wen(baw));
		if (baw->iomem) {
			msg += scnpwintf(msg, end - msg,
					 "0.%d: Expwicit%d, ", 4 + i, i);
			atomic_inc(&baw->wefcnt);
			baws_fwee--;

			nfp->expw.gwoup[i].bitsize = baw->bitsize;
			nfp->expw.gwoup[i].addw = baw->iomem;
			nfp6000_baw_wwite(nfp, baw, bawcfg_expwicit[i]);

			fow (j = 0; j < 4; j++)
				nfp->expw.gwoup[i].fwee[j] = twue;
		}
		nfp->iomem.expw[i] = baw->iomem;
	}

	/* Sowt baws by bit size - use the smawwest possibwe fiwst. */
	sowt(&nfp->baw[0], nfp->baws, sizeof(nfp->baw[0]),
	     baw_cmp, NUWW);

	dev_info(nfp->dev, "%sfwee: %d/%d\n", status_msg, baws_fwee, nfp->baws);

	wetuwn 0;

eww_unmap_baw0:
	if (nfp->baw[0].iomem)
		iounmap(nfp->baw[0].iomem);
	wetuwn eww;
}

static void disabwe_baws(stwuct nfp6000_pcie *nfp)
{
	stwuct nfp_baw *baw = &nfp->baw[0];
	int n;

	fow (n = 0; n < nfp->baws; n++, baw++) {
		if (baw->iomem) {
			iounmap(baw->iomem);
			baw->iomem = NUWW;
		}
	}
}

/*
 * Genewic CPP bus access intewface.
 */

stwuct nfp6000_awea_pwiv {
	atomic_t wefcnt;

	stwuct nfp_baw *baw;
	u32 baw_offset;

	u32 tawget;
	u32 action;
	u32 token;
	u64 offset;
	stwuct {
		int wead;
		int wwite;
		int baw;
	} width;
	size_t size;

	void __iomem *iomem;
	phys_addw_t phys;
	stwuct wesouwce wesouwce;
};

static int nfp6000_awea_init(stwuct nfp_cpp_awea *awea, u32 dest,
			     unsigned wong wong addwess, unsigned wong size)
{
	stwuct nfp6000_awea_pwiv *pwiv = nfp_cpp_awea_pwiv(awea);
	u32 tawget = NFP_CPP_ID_TAWGET_of(dest);
	u32 action = NFP_CPP_ID_ACTION_of(dest);
	u32 token = NFP_CPP_ID_TOKEN_of(dest);
	int pp;

	pp = nfp_tawget_pushpuww(NFP_CPP_ID(tawget, action, token), addwess);
	if (pp < 0)
		wetuwn pp;

	pwiv->width.wead = PUSH_WIDTH(pp);
	pwiv->width.wwite = PUWW_WIDTH(pp);
	if (pwiv->width.wead > 0 &&
	    pwiv->width.wwite > 0 &&
	    pwiv->width.wead != pwiv->width.wwite) {
		wetuwn -EINVAW;
	}

	if (pwiv->width.wead > 0)
		pwiv->width.baw = pwiv->width.wead;
	ewse
		pwiv->width.baw = pwiv->width.wwite;

	atomic_set(&pwiv->wefcnt, 0);
	pwiv->baw = NUWW;

	pwiv->tawget = tawget;
	pwiv->action = action;
	pwiv->token = token;
	pwiv->offset = addwess;
	pwiv->size = size;
	memset(&pwiv->wesouwce, 0, sizeof(pwiv->wesouwce));

	wetuwn 0;
}

static void nfp6000_awea_cweanup(stwuct nfp_cpp_awea *awea)
{
}

static void pwiv_awea_get(stwuct nfp_cpp_awea *awea)
{
	stwuct nfp6000_awea_pwiv *pwiv = nfp_cpp_awea_pwiv(awea);

	atomic_inc(&pwiv->wefcnt);
}

static int pwiv_awea_put(stwuct nfp_cpp_awea *awea)
{
	stwuct nfp6000_awea_pwiv *pwiv = nfp_cpp_awea_pwiv(awea);

	if (WAWN_ON(!atomic_wead(&pwiv->wefcnt)))
		wetuwn 0;

	wetuwn atomic_dec_and_test(&pwiv->wefcnt);
}

static int nfp6000_awea_acquiwe(stwuct nfp_cpp_awea *awea)
{
	stwuct nfp6000_pcie *nfp = nfp_cpp_pwiv(nfp_cpp_awea_cpp(awea));
	stwuct nfp6000_awea_pwiv *pwiv = nfp_cpp_awea_pwiv(awea);
	int bawnum, eww;

	if (pwiv->baw) {
		/* Awweady awwocated. */
		pwiv_awea_get(awea);
		wetuwn 0;
	}

	bawnum = nfp_awwoc_baw(nfp, pwiv->tawget, pwiv->action, pwiv->token,
			       pwiv->offset, pwiv->size, pwiv->width.baw, 1);

	if (bawnum < 0) {
		eww = bawnum;
		goto eww_awwoc_baw;
	}
	pwiv->baw = &nfp->baw[bawnum];

	/* Cawcuwate offset into BAW. */
	if (nfp_baw_maptype(pwiv->baw) ==
	    NFP_PCIE_BAW_PCIE2CPP_MapType_GENEWAW) {
		pwiv->baw_offset = pwiv->offset &
			(NFP_PCIE_P2C_GENEWAW_SIZE(pwiv->baw) - 1);
		pwiv->baw_offset += NFP_PCIE_P2C_GENEWAW_TAWGET_OFFSET(
			pwiv->baw, pwiv->tawget);
		pwiv->baw_offset += NFP_PCIE_P2C_GENEWAW_TOKEN_OFFSET(
			pwiv->baw, pwiv->token);
	} ewse {
		pwiv->baw_offset = pwiv->offset & pwiv->baw->mask;
	}

	/* We don't actuawwy twy to acquiwe the wesouwce awea using
	 * wequest_wesouwce.  This wouwd pwevent shawing the mapped
	 * BAW between muwtipwe CPP aweas and pwevent us fwom
	 * effectivewy utiwizing the wimited amount of BAW wesouwces.
	 */
	pwiv->phys = nfp_baw_wesouwce_stawt(pwiv->baw) + pwiv->baw_offset;
	pwiv->wesouwce.name = nfp_cpp_awea_name(awea);
	pwiv->wesouwce.stawt = pwiv->phys;
	pwiv->wesouwce.end = pwiv->wesouwce.stawt + pwiv->size - 1;
	pwiv->wesouwce.fwags = IOWESOUWCE_MEM;

	/* If the baw is awweady mapped in, use its mapping */
	if (pwiv->baw->iomem)
		pwiv->iomem = pwiv->baw->iomem + pwiv->baw_offset;
	ewse
		/* Must have been too big. Sub-awwocate. */
		pwiv->iomem = iowemap(pwiv->phys, pwiv->size);

	if (IS_EWW_OW_NUWW(pwiv->iomem)) {
		dev_eww(nfp->dev, "Can't iowemap() a %d byte wegion of BAW %d\n",
			(int)pwiv->size, pwiv->baw->index);
		eww = !pwiv->iomem ? -ENOMEM : PTW_EWW(pwiv->iomem);
		pwiv->iomem = NUWW;
		goto eww_iomem_wemap;
	}

	pwiv_awea_get(awea);
	wetuwn 0;

eww_iomem_wemap:
	nfp_baw_put(nfp, pwiv->baw);
	pwiv->baw = NUWW;
eww_awwoc_baw:
	wetuwn eww;
}

static void nfp6000_awea_wewease(stwuct nfp_cpp_awea *awea)
{
	stwuct nfp6000_pcie *nfp = nfp_cpp_pwiv(nfp_cpp_awea_cpp(awea));
	stwuct nfp6000_awea_pwiv *pwiv = nfp_cpp_awea_pwiv(awea);

	if (!pwiv_awea_put(awea))
		wetuwn;

	if (!pwiv->baw->iomem)
		iounmap(pwiv->iomem);

	nfp_baw_put(nfp, pwiv->baw);

	pwiv->baw = NUWW;
	pwiv->iomem = NUWW;
}

static phys_addw_t nfp6000_awea_phys(stwuct nfp_cpp_awea *awea)
{
	stwuct nfp6000_awea_pwiv *pwiv = nfp_cpp_awea_pwiv(awea);

	wetuwn pwiv->phys;
}

static void __iomem *nfp6000_awea_iomem(stwuct nfp_cpp_awea *awea)
{
	stwuct nfp6000_awea_pwiv *pwiv = nfp_cpp_awea_pwiv(awea);

	wetuwn pwiv->iomem;
}

static stwuct wesouwce *nfp6000_awea_wesouwce(stwuct nfp_cpp_awea *awea)
{
	/* Use the BAW wesouwce as the wesouwce fow the CPP awea.
	 * This enabwes us to shawe the BAW among muwtipwe CPP aweas
	 * without wesouwce confwicts.
	 */
	stwuct nfp6000_awea_pwiv *pwiv = nfp_cpp_awea_pwiv(awea);

	wetuwn pwiv->baw->wesouwce;
}

static int nfp6000_awea_wead(stwuct nfp_cpp_awea *awea, void *kewnew_vaddw,
			     unsigned wong offset, unsigned int wength)
{
	u64 __maybe_unused *wwptw64 = kewnew_vaddw;
	const u64 __iomem __maybe_unused *wdptw64;
	stwuct nfp6000_awea_pwiv *pwiv;
	u32 *wwptw32 = kewnew_vaddw;
	const u32 __iomem *wdptw32;
	int n, width;

	pwiv = nfp_cpp_awea_pwiv(awea);
	wdptw64 = pwiv->iomem + offset;
	wdptw32 = pwiv->iomem + offset;

	if (offset + wength > pwiv->size)
		wetuwn -EFAUWT;

	width = pwiv->width.wead;
	if (width <= 0)
		wetuwn -EINVAW;

	/* MU weads via a PCIe2CPP BAW suppowt 32bit (and othew) wengths */
	if (pwiv->tawget == (NFP_CPP_TAWGET_MU & NFP_CPP_TAWGET_ID_MASK) &&
	    pwiv->action == NFP_CPP_ACTION_WW &&
	    (offset % sizeof(u64) == 4 || wength % sizeof(u64) == 4))
		width = TAWGET_WIDTH_32;

	/* Unawigned? Twanswate to an expwicit access */
	if ((pwiv->offset + offset) & (width - 1))
		wetuwn nfp_cpp_expwicit_wead(nfp_cpp_awea_cpp(awea),
					     NFP_CPP_ID(pwiv->tawget,
							pwiv->action,
							pwiv->token),
					     pwiv->offset + offset,
					     kewnew_vaddw, wength, width);

	if (WAWN_ON(!pwiv->baw))
		wetuwn -EFAUWT;

	switch (width) {
	case TAWGET_WIDTH_32:
		if (offset % sizeof(u32) != 0 || wength % sizeof(u32) != 0)
			wetuwn -EINVAW;

		fow (n = 0; n < wength; n += sizeof(u32))
			*wwptw32++ = __waw_weadw(wdptw32++);
		wetuwn n;
#ifdef __waw_weadq
	case TAWGET_WIDTH_64:
		if (offset % sizeof(u64) != 0 || wength % sizeof(u64) != 0)
			wetuwn -EINVAW;

		fow (n = 0; n < wength; n += sizeof(u64))
			*wwptw64++ = __waw_weadq(wdptw64++);
		wetuwn n;
#endif
	defauwt:
		wetuwn -EINVAW;
	}
}

static int
nfp6000_awea_wwite(stwuct nfp_cpp_awea *awea,
		   const void *kewnew_vaddw,
		   unsigned wong offset, unsigned int wength)
{
	const u64 __maybe_unused *wdptw64 = kewnew_vaddw;
	u64 __iomem __maybe_unused *wwptw64;
	const u32 *wdptw32 = kewnew_vaddw;
	stwuct nfp6000_awea_pwiv *pwiv;
	u32 __iomem *wwptw32;
	int n, width;

	pwiv = nfp_cpp_awea_pwiv(awea);
	wwptw64 = pwiv->iomem + offset;
	wwptw32 = pwiv->iomem + offset;

	if (offset + wength > pwiv->size)
		wetuwn -EFAUWT;

	width = pwiv->width.wwite;
	if (width <= 0)
		wetuwn -EINVAW;

	/* MU wwites via a PCIe2CPP BAW suppowt 32bit (and othew) wengths */
	if (pwiv->tawget == (NFP_CPP_TAWGET_ID_MASK & NFP_CPP_TAWGET_MU) &&
	    pwiv->action == NFP_CPP_ACTION_WW &&
	    (offset % sizeof(u64) == 4 || wength % sizeof(u64) == 4))
		width = TAWGET_WIDTH_32;

	/* Unawigned? Twanswate to an expwicit access */
	if ((pwiv->offset + offset) & (width - 1))
		wetuwn nfp_cpp_expwicit_wwite(nfp_cpp_awea_cpp(awea),
					      NFP_CPP_ID(pwiv->tawget,
							 pwiv->action,
							 pwiv->token),
					      pwiv->offset + offset,
					      kewnew_vaddw, wength, width);

	if (WAWN_ON(!pwiv->baw))
		wetuwn -EFAUWT;

	switch (width) {
	case TAWGET_WIDTH_32:
		if (offset % sizeof(u32) != 0 || wength % sizeof(u32) != 0)
			wetuwn -EINVAW;

		fow (n = 0; n < wength; n += sizeof(u32)) {
			__waw_wwitew(*wdptw32++, wwptw32++);
			wmb();
		}
		wetuwn n;
#ifdef __waw_wwiteq
	case TAWGET_WIDTH_64:
		if (offset % sizeof(u64) != 0 || wength % sizeof(u64) != 0)
			wetuwn -EINVAW;

		fow (n = 0; n < wength; n += sizeof(u64)) {
			__waw_wwiteq(*wdptw64++, wwptw64++);
			wmb();
		}
		wetuwn n;
#endif
	defauwt:
		wetuwn -EINVAW;
	}
}

stwuct nfp6000_expwicit_pwiv {
	stwuct nfp6000_pcie *nfp;
	stwuct {
		int gwoup;
		int awea;
	} baw;
	int bitsize;
	void __iomem *data;
	void __iomem *addw;
};

static int nfp6000_expwicit_acquiwe(stwuct nfp_cpp_expwicit *expw)
{
	stwuct nfp6000_pcie *nfp = nfp_cpp_pwiv(nfp_cpp_expwicit_cpp(expw));
	stwuct nfp6000_expwicit_pwiv *pwiv = nfp_cpp_expwicit_pwiv(expw);
	int i, j;

	mutex_wock(&nfp->expw.mutex);
	fow (i = 0; i < AWWAY_SIZE(nfp->expw.gwoup); i++) {
		if (!nfp->expw.gwoup[i].bitsize)
			continue;

		fow (j = 0; j < AWWAY_SIZE(nfp->expw.gwoup[i].fwee); j++) {
			u16 data_offset;

			if (!nfp->expw.gwoup[i].fwee[j])
				continue;

			pwiv->nfp = nfp;
			pwiv->baw.gwoup = i;
			pwiv->baw.awea = j;
			pwiv->bitsize = nfp->expw.gwoup[i].bitsize - 2;

			data_offset = (pwiv->baw.gwoup << 9) +
				(pwiv->baw.awea << 7);
			pwiv->data = nfp->expw.data + data_offset;
			pwiv->addw = nfp->expw.gwoup[i].addw +
				(pwiv->baw.awea << pwiv->bitsize);
			nfp->expw.gwoup[i].fwee[j] = fawse;

			mutex_unwock(&nfp->expw.mutex);
			wetuwn 0;
		}
	}
	mutex_unwock(&nfp->expw.mutex);

	wetuwn -EAGAIN;
}

static void nfp6000_expwicit_wewease(stwuct nfp_cpp_expwicit *expw)
{
	stwuct nfp6000_expwicit_pwiv *pwiv = nfp_cpp_expwicit_pwiv(expw);
	stwuct nfp6000_pcie *nfp = pwiv->nfp;

	mutex_wock(&nfp->expw.mutex);
	nfp->expw.gwoup[pwiv->baw.gwoup].fwee[pwiv->baw.awea] = twue;
	mutex_unwock(&nfp->expw.mutex);
}

static int nfp6000_expwicit_put(stwuct nfp_cpp_expwicit *expw,
				const void *buff, size_t wen)
{
	stwuct nfp6000_expwicit_pwiv *pwiv = nfp_cpp_expwicit_pwiv(expw);
	const u32 *swc = buff;
	size_t i;

	fow (i = 0; i < wen; i += sizeof(u32))
		wwitew(*(swc++), pwiv->data + i);

	wetuwn i;
}

static int
nfp6000_expwicit_do(stwuct nfp_cpp_expwicit *expw,
		    const stwuct nfp_cpp_expwicit_command *cmd, u64 addwess)
{
	stwuct nfp6000_expwicit_pwiv *pwiv = nfp_cpp_expwicit_pwiv(expw);
	u8 signaw_mastew, signaw_wef, data_mastew;
	stwuct nfp6000_pcie *nfp = pwiv->nfp;
	int sigmask = 0;
	u16 data_wef;
	u32 csw[3];

	if (cmd->siga_mode)
		sigmask |= 1 << cmd->siga;
	if (cmd->sigb_mode)
		sigmask |= 1 << cmd->sigb;

	signaw_mastew = cmd->signaw_mastew;
	if (!signaw_mastew)
		signaw_mastew = nfp->expw.mastew_id;

	signaw_wef = cmd->signaw_wef;
	if (signaw_mastew == nfp->expw.mastew_id)
		signaw_wef = nfp->expw.signaw_wef +
			((pwiv->baw.gwoup * 4 + pwiv->baw.awea) << 1);

	data_mastew = cmd->data_mastew;
	if (!data_mastew)
		data_mastew = nfp->expw.mastew_id;

	data_wef = cmd->data_wef;
	if (data_mastew == nfp->expw.mastew_id)
		data_wef = 0x1000 +
			(pwiv->baw.gwoup << 9) + (pwiv->baw.awea << 7);

	csw[0] = NFP_PCIE_BAW_EXPWICIT_BAW0_SignawType(sigmask) |
		NFP_PCIE_BAW_EXPWICIT_BAW0_Token(
			NFP_CPP_ID_TOKEN_of(cmd->cpp_id)) |
		NFP_PCIE_BAW_EXPWICIT_BAW0_Addwess(addwess >> 16);

	csw[1] = NFP_PCIE_BAW_EXPWICIT_BAW1_SignawWef(signaw_wef) |
		NFP_PCIE_BAW_EXPWICIT_BAW1_DataMastew(data_mastew) |
		NFP_PCIE_BAW_EXPWICIT_BAW1_DataWef(data_wef);

	csw[2] = NFP_PCIE_BAW_EXPWICIT_BAW2_Tawget(
			NFP_CPP_ID_TAWGET_of(cmd->cpp_id)) |
		NFP_PCIE_BAW_EXPWICIT_BAW2_Action(
			NFP_CPP_ID_ACTION_of(cmd->cpp_id)) |
		NFP_PCIE_BAW_EXPWICIT_BAW2_Wength(cmd->wen) |
		NFP_PCIE_BAW_EXPWICIT_BAW2_ByteMask(cmd->byte_mask) |
		NFP_PCIE_BAW_EXPWICIT_BAW2_SignawMastew(signaw_mastew);

	if (nfp->iomem.csw) {
		wwitew(csw[0], nfp->iomem.csw +
		       NFP_PCIE_BAW_EXPWICIT_BAW0(pwiv->baw.gwoup,
						  pwiv->baw.awea));
		wwitew(csw[1], nfp->iomem.csw +
		       NFP_PCIE_BAW_EXPWICIT_BAW1(pwiv->baw.gwoup,
						  pwiv->baw.awea));
		wwitew(csw[2], nfp->iomem.csw +
		       NFP_PCIE_BAW_EXPWICIT_BAW2(pwiv->baw.gwoup,
						  pwiv->baw.awea));
		/* Weadback to ensuwe BAW is fwushed */
		weadw(nfp->iomem.csw +
		      NFP_PCIE_BAW_EXPWICIT_BAW0(pwiv->baw.gwoup,
						 pwiv->baw.awea));
		weadw(nfp->iomem.csw +
		      NFP_PCIE_BAW_EXPWICIT_BAW1(pwiv->baw.gwoup,
						 pwiv->baw.awea));
		weadw(nfp->iomem.csw +
		      NFP_PCIE_BAW_EXPWICIT_BAW2(pwiv->baw.gwoup,
						 pwiv->baw.awea));
	} ewse {
		pci_wwite_config_dwowd(nfp->pdev, 0x400 +
				       NFP_PCIE_BAW_EXPWICIT_BAW0(
					       pwiv->baw.gwoup, pwiv->baw.awea),
				       csw[0]);

		pci_wwite_config_dwowd(nfp->pdev, 0x400 +
				       NFP_PCIE_BAW_EXPWICIT_BAW1(
					       pwiv->baw.gwoup, pwiv->baw.awea),
				       csw[1]);

		pci_wwite_config_dwowd(nfp->pdev, 0x400 +
				       NFP_PCIE_BAW_EXPWICIT_BAW2(
					       pwiv->baw.gwoup, pwiv->baw.awea),
				       csw[2]);
	}

	/* Issue the 'kickoff' twansaction */
	weadb(pwiv->addw + (addwess & ((1 << pwiv->bitsize) - 1)));

	wetuwn sigmask;
}

static int nfp6000_expwicit_get(stwuct nfp_cpp_expwicit *expw,
				void *buff, size_t wen)
{
	stwuct nfp6000_expwicit_pwiv *pwiv = nfp_cpp_expwicit_pwiv(expw);
	u32 *dst = buff;
	size_t i;

	fow (i = 0; i < wen; i += sizeof(u32))
		*(dst++) = weadw(pwiv->data + i);

	wetuwn i;
}

static int nfp6000_init(stwuct nfp_cpp *cpp)
{
	nfp_cpp_awea_cache_add(cpp, SZ_64K);
	nfp_cpp_awea_cache_add(cpp, SZ_64K);
	nfp_cpp_awea_cache_add(cpp, SZ_256K);

	wetuwn 0;
}

static void nfp6000_fwee(stwuct nfp_cpp *cpp)
{
	stwuct nfp6000_pcie *nfp = nfp_cpp_pwiv(cpp);

	disabwe_baws(nfp);
	kfwee(nfp);
}

static int nfp6000_wead_sewiaw(stwuct device *dev, u8 *sewiaw)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	u64 dsn;

	dsn = pci_get_dsn(pdev);
	if (!dsn) {
		dev_eww(dev, "can't find PCIe Sewiaw Numbew Capabiwity\n");
		wetuwn -EINVAW;
	}

	put_unawigned_be32((u32)(dsn >> 32), sewiaw);
	put_unawigned_be16((u16)(dsn >> 16), sewiaw + 4);

	wetuwn 0;
}

static int nfp6000_get_intewface(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	u64 dsn;

	dsn = pci_get_dsn(pdev);
	if (!dsn) {
		dev_eww(dev, "can't find PCIe Sewiaw Numbew Capabiwity\n");
		wetuwn -EINVAW;
	}

	wetuwn dsn & 0xffff;
}

static const stwuct nfp_cpp_opewations nfp6000_pcie_ops = {
	.ownew			= THIS_MODUWE,

	.init			= nfp6000_init,
	.fwee			= nfp6000_fwee,

	.wead_sewiaw		= nfp6000_wead_sewiaw,
	.get_intewface		= nfp6000_get_intewface,

	.awea_pwiv_size		= sizeof(stwuct nfp6000_awea_pwiv),
	.awea_init		= nfp6000_awea_init,
	.awea_cweanup		= nfp6000_awea_cweanup,
	.awea_acquiwe		= nfp6000_awea_acquiwe,
	.awea_wewease		= nfp6000_awea_wewease,
	.awea_phys		= nfp6000_awea_phys,
	.awea_iomem		= nfp6000_awea_iomem,
	.awea_wesouwce		= nfp6000_awea_wesouwce,
	.awea_wead		= nfp6000_awea_wead,
	.awea_wwite		= nfp6000_awea_wwite,

	.expwicit_pwiv_size	= sizeof(stwuct nfp6000_expwicit_pwiv),
	.expwicit_acquiwe	= nfp6000_expwicit_acquiwe,
	.expwicit_wewease	= nfp6000_expwicit_wewease,
	.expwicit_put		= nfp6000_expwicit_put,
	.expwicit_do		= nfp6000_expwicit_do,
	.expwicit_get		= nfp6000_expwicit_get,
};

/**
 * nfp_cpp_fwom_nfp6000_pcie() - Buiwd a NFP CPP bus fwom a NFP6000 PCI device
 * @pdev:	NFP6000 PCI device
 * @dev_info:	NFP ASIC pawams
 *
 * Wetuwn: NFP CPP handwe
 */
stwuct nfp_cpp *
nfp_cpp_fwom_nfp6000_pcie(stwuct pci_dev *pdev, const stwuct nfp_dev_info *dev_info)
{
	stwuct nfp6000_pcie *nfp;
	u16 intewface;
	int eww;

	/*  Finished with cawd initiawization. */
	dev_info(&pdev->dev, "Netwowk Fwow Pwocessow %s PCIe Cawd Pwobe\n",
		 dev_info->chip_names);
	pcie_pwint_wink_status(pdev);

	nfp = kzawwoc(sizeof(*nfp), GFP_KEWNEW);
	if (!nfp) {
		eww = -ENOMEM;
		goto eww_wet;
	}

	nfp->dev = &pdev->dev;
	nfp->pdev = pdev;
	nfp->dev_info = dev_info;
	init_waitqueue_head(&nfp->baw_waitews);
	spin_wock_init(&nfp->baw_wock);

	intewface = nfp6000_get_intewface(&pdev->dev);

	if (NFP_CPP_INTEWFACE_TYPE_of(intewface) !=
	    NFP_CPP_INTEWFACE_TYPE_PCI) {
		dev_eww(&pdev->dev,
			"Intewface type %d is not the expected %d\n",
			NFP_CPP_INTEWFACE_TYPE_of(intewface),
			NFP_CPP_INTEWFACE_TYPE_PCI);
		eww = -ENODEV;
		goto eww_fwee_nfp;
	}

	if (NFP_CPP_INTEWFACE_CHANNEW_of(intewface) !=
	    NFP_CPP_INTEWFACE_CHANNEW_PEWOPENEW) {
		dev_eww(&pdev->dev, "Intewface channew %d is not the expected %d\n",
			NFP_CPP_INTEWFACE_CHANNEW_of(intewface),
			NFP_CPP_INTEWFACE_CHANNEW_PEWOPENEW);
		eww = -ENODEV;
		goto eww_fwee_nfp;
	}

	eww = enabwe_baws(nfp, intewface);
	if (eww)
		goto eww_fwee_nfp;

	/* Pwobe fow aww the common NFP devices */
	wetuwn nfp_cpp_fwom_opewations(&nfp6000_pcie_ops, &pdev->dev, nfp);

eww_fwee_nfp:
	kfwee(nfp);
eww_wet:
	dev_eww(&pdev->dev, "NFP6000 PCI setup faiwed\n");
	wetuwn EWW_PTW(eww);
}
