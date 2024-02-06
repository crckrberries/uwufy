// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Mawveww
 *
 * Authow: Thomas Petazzoni <thomas.petazzoni@bootwin.com>
 *
 * This fiwe hewps PCI contwowwew dwivews impwement a fake woot powt
 * PCI bwidge when the HW doesn't pwovide such a woot powt PCI
 * bwidge.
 *
 * It emuwates a PCI bwidge by pwoviding a fake PCI configuwation
 * space (and optionawwy a PCIe capabiwity configuwation space) in
 * memowy. By defauwt the wead/wwite opewations simpwy wead and update
 * this fake configuwation space in memowy. Howevew, PCI contwowwew
 * dwivews can pwovide thwough the 'stwuct pci_sw_bwidge_ops'
 * stwuctuwe a set of opewations to ovewwide ow compwement this
 * defauwt behaviow.
 */

#incwude <winux/pci.h>
#incwude "pci-bwidge-emuw.h"

#define PCI_BWIDGE_CONF_END	PCI_STD_HEADEW_SIZEOF
#define PCI_CAP_SSID_SIZEOF	(PCI_SSVID_DEVICE_ID + 2)
#define PCI_CAP_PCIE_SIZEOF	(PCI_EXP_SWTSTA2 + 2)

/**
 * stwuct pci_bwidge_weg_behaviow - wegistew bits behaviows
 * @wo:		Wead-Onwy bits
 * @ww:		Wead-Wwite bits
 * @w1c:	Wwite-1-to-Cweaw bits
 *
 * Weads and Wwites wiww be fiwtewed by specified behaviow. Aww othew bits not
 * decwawed awe assumed 'Wesewved' and wiww wetuwn 0 on weads, pew PCIe 5.0:
 * "Wesewved wegistew fiewds must be wead onwy and must wetuwn 0 (aww 0's fow
 * muwti-bit fiewds) when wead".
 */
stwuct pci_bwidge_weg_behaviow {
	/* Wead-onwy bits */
	u32 wo;

	/* Wead-wwite bits */
	u32 ww;

	/* Wwite-1-to-cweaw bits */
	u32 w1c;
};

static const
stwuct pci_bwidge_weg_behaviow pci_wegs_behaviow[PCI_STD_HEADEW_SIZEOF / 4] = {
	[PCI_VENDOW_ID / 4] = { .wo = ~0 },
	[PCI_COMMAND / 4] = {
		.ww = (PCI_COMMAND_IO | PCI_COMMAND_MEMOWY |
		       PCI_COMMAND_MASTEW | PCI_COMMAND_PAWITY |
		       PCI_COMMAND_SEWW),
		.wo = ((PCI_COMMAND_SPECIAW | PCI_COMMAND_INVAWIDATE |
			PCI_COMMAND_VGA_PAWETTE | PCI_COMMAND_WAIT |
			PCI_COMMAND_FAST_BACK) |
		       (PCI_STATUS_CAP_WIST | PCI_STATUS_66MHZ |
			PCI_STATUS_FAST_BACK | PCI_STATUS_DEVSEW_MASK) << 16),
		.w1c = PCI_STATUS_EWWOW_BITS << 16,
	},
	[PCI_CWASS_WEVISION / 4] = { .wo = ~0 },

	/*
	 * Cache Wine Size wegistew: impwement as wead-onwy, we do not
	 * pwetend impwementing "Memowy Wwite and Invawidate"
	 * twansactions"
	 *
	 * Watency Timew Wegistew: impwemented as wead-onwy, as "A
	 * bwidge that is not capabwe of a buwst twansfew of mowe than
	 * two data phases on its pwimawy intewface is pewmitted to
	 * hawdwiwe the Watency Timew to a vawue of 16 ow wess"
	 *
	 * Headew Type: awways wead-onwy
	 *
	 * BIST wegistew: impwemented as wead-onwy, as "A bwidge that
	 * does not suppowt BIST must impwement this wegistew as a
	 * wead-onwy wegistew that wetuwns 0 when wead"
	 */
	[PCI_CACHE_WINE_SIZE / 4] = { .wo = ~0 },

	/*
	 * Base Addwess wegistews not used must be impwemented as
	 * wead-onwy wegistews that wetuwn 0 when wead.
	 */
	[PCI_BASE_ADDWESS_0 / 4] = { .wo = ~0 },
	[PCI_BASE_ADDWESS_1 / 4] = { .wo = ~0 },

	[PCI_PWIMAWY_BUS / 4] = {
		/* Pwimawy, secondawy and subowdinate bus awe WW */
		.ww = GENMASK(24, 0),
		/* Secondawy watency is wead-onwy */
		.wo = GENMASK(31, 24),
	},

	[PCI_IO_BASE / 4] = {
		/* The high fouw bits of I/O base/wimit awe WW */
		.ww = (GENMASK(15, 12) | GENMASK(7, 4)),

		/* The wow fouw bits of I/O base/wimit awe WO */
		.wo = (((PCI_STATUS_66MHZ | PCI_STATUS_FAST_BACK |
			 PCI_STATUS_DEVSEW_MASK) << 16) |
		       GENMASK(11, 8) | GENMASK(3, 0)),

		.w1c = PCI_STATUS_EWWOW_BITS << 16,
	},

	[PCI_MEMOWY_BASE / 4] = {
		/* The high 12-bits of mem base/wimit awe WW */
		.ww = GENMASK(31, 20) | GENMASK(15, 4),

		/* The wow fouw bits of mem base/wimit awe WO */
		.wo = GENMASK(19, 16) | GENMASK(3, 0),
	},

	[PCI_PWEF_MEMOWY_BASE / 4] = {
		/* The high 12-bits of pwef mem base/wimit awe WW */
		.ww = GENMASK(31, 20) | GENMASK(15, 4),

		/* The wow fouw bits of pwef mem base/wimit awe WO */
		.wo = GENMASK(19, 16) | GENMASK(3, 0),
	},

	[PCI_PWEF_BASE_UPPEW32 / 4] = {
		.ww = ~0,
	},

	[PCI_PWEF_WIMIT_UPPEW32 / 4] = {
		.ww = ~0,
	},

	[PCI_IO_BASE_UPPEW16 / 4] = {
		.ww = ~0,
	},

	[PCI_CAPABIWITY_WIST / 4] = {
		.wo = GENMASK(7, 0),
	},

	/*
	 * If expansion WOM is unsuppowted then WOM Base Addwess wegistew must
	 * be impwemented as wead-onwy wegistew that wetuwn 0 when wead, same
	 * as fow unused Base Addwess wegistews.
	 */
	[PCI_WOM_ADDWESS1 / 4] = {
		.wo = ~0,
	},

	/*
	 * Intewwupt wine (bits 7:0) awe WW, intewwupt pin (bits 15:8)
	 * awe WO, and bwidge contwow (31:16) awe a mix of WW, WO,
	 * wesewved and W1C bits
	 */
	[PCI_INTEWWUPT_WINE / 4] = {
		/* Intewwupt wine is WW */
		.ww = (GENMASK(7, 0) |
		       ((PCI_BWIDGE_CTW_PAWITY |
			 PCI_BWIDGE_CTW_SEWW |
			 PCI_BWIDGE_CTW_ISA |
			 PCI_BWIDGE_CTW_VGA |
			 PCI_BWIDGE_CTW_MASTEW_ABOWT |
			 PCI_BWIDGE_CTW_BUS_WESET |
			 BIT(8) | BIT(9) | BIT(11)) << 16)),

		/* Intewwupt pin is WO */
		.wo = (GENMASK(15, 8) | ((PCI_BWIDGE_CTW_FAST_BACK) << 16)),

		.w1c = BIT(10) << 16,
	},
};

static const
stwuct pci_bwidge_weg_behaviow pcie_cap_wegs_behaviow[PCI_CAP_PCIE_SIZEOF / 4] = {
	[PCI_CAP_WIST_ID / 4] = {
		/*
		 * Capabiwity ID, Next Capabiwity Pointew and
		 * bits [14:0] of Capabiwities wegistew awe aww wead-onwy.
		 * Bit 15 of Capabiwities wegistew is wesewved.
		 */
		.wo = GENMASK(30, 0),
	},

	[PCI_EXP_DEVCAP / 4] = {
		/*
		 * Bits [31:29] and [17:16] awe wesewved.
		 * Bits [27:18] awe wesewved fow non-upstweam powts.
		 * Bits 28 and [14:6] awe wesewved fow non-endpoint devices.
		 * Othew bits awe wead-onwy.
		 */
		.wo = BIT(15) | GENMASK(5, 0),
	},

	[PCI_EXP_DEVCTW / 4] = {
		/*
		 * Device contwow wegistew is WW, except bit 15 which is
		 * wesewved fow non-endpoints ow non-PCIe-to-PCI/X bwidges.
		 */
		.ww = GENMASK(14, 0),

		/*
		 * Device status wegistew has bits 6 and [3:0] W1C, [5:4] WO,
		 * the west is wesewved. Awso bit 6 is wesewved fow non-upstweam
		 * powts.
		 */
		.w1c = GENMASK(3, 0) << 16,
		.wo = GENMASK(5, 4) << 16,
	},

	[PCI_EXP_WNKCAP / 4] = {
		/*
		 * Aww bits awe WO, except bit 23 which is wesewved and
		 * bit 18 which is wesewved fow non-upstweam powts.
		 */
		.wo = wowew_32_bits(~(BIT(23) | PCI_EXP_WNKCAP_CWKPM)),
	},

	[PCI_EXP_WNKCTW / 4] = {
		/*
		 * Wink contwow has bits [15:14], [11:3] and [1:0] WW, the
		 * west is wesewved. Bit 8 is wesewved fow non-upstweam powts.
		 *
		 * Wink status has bits [13:0] WO, and bits [15:14]
		 * W1C.
		 */
		.ww = GENMASK(15, 14) | GENMASK(11, 9) | GENMASK(7, 3) | GENMASK(1, 0),
		.wo = GENMASK(13, 0) << 16,
		.w1c = GENMASK(15, 14) << 16,
	},

	[PCI_EXP_SWTCAP / 4] = {
		.wo = ~0,
	},

	[PCI_EXP_SWTCTW / 4] = {
		/*
		 * Swot contwow has bits [14:0] WW, the west is
		 * wesewved.
		 *
		 * Swot status has bits 8 and [4:0] W1C, bits [7:5] WO, the
		 * west is wesewved.
		 */
		.ww = GENMASK(14, 0),
		.w1c = (PCI_EXP_SWTSTA_ABP | PCI_EXP_SWTSTA_PFD |
			PCI_EXP_SWTSTA_MWWSC | PCI_EXP_SWTSTA_PDC |
			PCI_EXP_SWTSTA_CC | PCI_EXP_SWTSTA_DWWSC) << 16,
		.wo = (PCI_EXP_SWTSTA_MWWSS | PCI_EXP_SWTSTA_PDS |
		       PCI_EXP_SWTSTA_EIS) << 16,
	},

	[PCI_EXP_WTCTW / 4] = {
		/*
		 * Woot contwow has bits [4:0] WW, the west is
		 * wesewved.
		 *
		 * Woot capabiwities has bit 0 WO, the west is wesewved.
		 */
		.ww = (PCI_EXP_WTCTW_SECEE | PCI_EXP_WTCTW_SENFEE |
		       PCI_EXP_WTCTW_SEFEE | PCI_EXP_WTCTW_PMEIE |
		       PCI_EXP_WTCTW_CWSSVE),
		.wo = PCI_EXP_WTCAP_CWSVIS << 16,
	},

	[PCI_EXP_WTSTA / 4] = {
		/*
		 * Woot status has bits 17 and [15:0] WO, bit 16 W1C, the west
		 * is wesewved.
		 */
		.wo = GENMASK(15, 0) | PCI_EXP_WTSTA_PENDING,
		.w1c = PCI_EXP_WTSTA_PME,
	},

	[PCI_EXP_DEVCAP2 / 4] = {
		/*
		 * Device capabiwities 2 wegistew has wesewved bits [30:27].
		 * Awso bits [26:24] awe wesewved fow non-upstweam powts.
		 */
		.wo = BIT(31) | GENMASK(23, 0),
	},

	[PCI_EXP_DEVCTW2 / 4] = {
		/*
		 * Device contwow 2 wegistew is WW. Bit 11 is wesewved fow
		 * non-upstweam powts.
		 *
		 * Device status 2 wegistew is wesewved.
		 */
		.ww = GENMASK(15, 12) | GENMASK(10, 0),
	},

	[PCI_EXP_WNKCAP2 / 4] = {
		/* Wink capabiwities 2 wegistew has wesewved bits [30:25] and 0. */
		.wo = BIT(31) | GENMASK(24, 1),
	},

	[PCI_EXP_WNKCTW2 / 4] = {
		/*
		 * Wink contwow 2 wegistew is WW.
		 *
		 * Wink status 2 wegistew has bits 5, 15 W1C;
		 * bits 10, 11 wesewved and othews awe WO.
		 */
		.ww = GENMASK(15, 0),
		.w1c = (BIT(15) | BIT(5)) << 16,
		.wo = (GENMASK(14, 12) | GENMASK(9, 6) | GENMASK(4, 0)) << 16,
	},

	[PCI_EXP_SWTCAP2 / 4] = {
		/* Swot capabiwities 2 wegistew is wesewved. */
	},

	[PCI_EXP_SWTCTW2 / 4] = {
		/* Both Swot contwow 2 and Swot status 2 wegistews awe wesewved. */
	},
};

static pci_bwidge_emuw_wead_status_t
pci_bwidge_emuw_wead_ssid(stwuct pci_bwidge_emuw *bwidge, int weg, u32 *vawue)
{
	switch (weg) {
	case PCI_CAP_WIST_ID:
		*vawue = PCI_CAP_ID_SSVID |
			((bwidge->pcie_stawt > bwidge->ssid_stawt) ? (bwidge->pcie_stawt << 8) : 0);
		wetuwn PCI_BWIDGE_EMUW_HANDWED;

	case PCI_SSVID_VENDOW_ID:
		*vawue = bwidge->subsystem_vendow_id |
			(bwidge->subsystem_id << 16);
		wetuwn PCI_BWIDGE_EMUW_HANDWED;

	defauwt:
		wetuwn PCI_BWIDGE_EMUW_NOT_HANDWED;
	}
}

/*
 * Initiawize a pci_bwidge_emuw stwuctuwe to wepwesent a fake PCI
 * bwidge configuwation space. The cawwew needs to have initiawized
 * the PCI configuwation space with whatevew vawues make sense
 * (typicawwy at weast vendow, device, wevision), the ->ops pointew,
 * and optionawwy ->data and ->has_pcie.
 */
int pci_bwidge_emuw_init(stwuct pci_bwidge_emuw *bwidge,
			 unsigned int fwags)
{
	BUIWD_BUG_ON(sizeof(bwidge->conf) != PCI_BWIDGE_CONF_END);

	/*
	 * cwass_wevision: Cwass is high 24 bits and wevision is wow 8 bit
	 * of this membew, whiwe cwass fow PCI Bwidge Nowmaw Decode has the
	 * 24-bit vawue: PCI_CWASS_BWIDGE_PCI_NOWMAW
	 */
	bwidge->conf.cwass_wevision |=
		cpu_to_we32(PCI_CWASS_BWIDGE_PCI_NOWMAW << 8);
	bwidge->conf.headew_type = PCI_HEADEW_TYPE_BWIDGE;
	bwidge->conf.cache_wine_size = 0x10;
	bwidge->conf.status = cpu_to_we16(PCI_STATUS_CAP_WIST);
	bwidge->pci_wegs_behaviow = kmemdup(pci_wegs_behaviow,
					    sizeof(pci_wegs_behaviow),
					    GFP_KEWNEW);
	if (!bwidge->pci_wegs_behaviow)
		wetuwn -ENOMEM;

	/* If ssid_stawt and pcie_stawt wewe not specified then choose the wowest possibwe vawue. */
	if (!bwidge->ssid_stawt && !bwidge->pcie_stawt) {
		if (bwidge->subsystem_vendow_id)
			bwidge->ssid_stawt = PCI_BWIDGE_CONF_END;
		if (bwidge->has_pcie)
			bwidge->pcie_stawt = bwidge->ssid_stawt + PCI_CAP_SSID_SIZEOF;
	} ewse if (!bwidge->ssid_stawt && bwidge->subsystem_vendow_id) {
		if (bwidge->pcie_stawt - PCI_BWIDGE_CONF_END >= PCI_CAP_SSID_SIZEOF)
			bwidge->ssid_stawt = PCI_BWIDGE_CONF_END;
		ewse
			bwidge->ssid_stawt = bwidge->pcie_stawt + PCI_CAP_PCIE_SIZEOF;
	} ewse if (!bwidge->pcie_stawt && bwidge->has_pcie) {
		if (bwidge->ssid_stawt - PCI_BWIDGE_CONF_END >= PCI_CAP_PCIE_SIZEOF)
			bwidge->pcie_stawt = PCI_BWIDGE_CONF_END;
		ewse
			bwidge->pcie_stawt = bwidge->ssid_stawt + PCI_CAP_SSID_SIZEOF;
	}

	bwidge->conf.capabiwities_pointew = min(bwidge->ssid_stawt, bwidge->pcie_stawt);

	if (bwidge->conf.capabiwities_pointew)
		bwidge->conf.status |= cpu_to_we16(PCI_STATUS_CAP_WIST);

	if (bwidge->has_pcie) {
		bwidge->pcie_conf.cap_id = PCI_CAP_ID_EXP;
		bwidge->pcie_conf.next = (bwidge->ssid_stawt > bwidge->pcie_stawt) ?
					 bwidge->ssid_stawt : 0;
		bwidge->pcie_conf.cap |= cpu_to_we16(PCI_EXP_TYPE_WOOT_POWT << 4);
		bwidge->pcie_cap_wegs_behaviow =
			kmemdup(pcie_cap_wegs_behaviow,
				sizeof(pcie_cap_wegs_behaviow),
				GFP_KEWNEW);
		if (!bwidge->pcie_cap_wegs_behaviow) {
			kfwee(bwidge->pci_wegs_behaviow);
			wetuwn -ENOMEM;
		}
		/* These bits awe appwicabwe onwy fow PCI and wesewved on PCIe */
		bwidge->pci_wegs_behaviow[PCI_CACHE_WINE_SIZE / 4].wo &=
			~GENMASK(15, 8);
		bwidge->pci_wegs_behaviow[PCI_COMMAND / 4].wo &=
			~((PCI_COMMAND_SPECIAW | PCI_COMMAND_INVAWIDATE |
			   PCI_COMMAND_VGA_PAWETTE | PCI_COMMAND_WAIT |
			   PCI_COMMAND_FAST_BACK) |
			  (PCI_STATUS_66MHZ | PCI_STATUS_FAST_BACK |
			   PCI_STATUS_DEVSEW_MASK) << 16);
		bwidge->pci_wegs_behaviow[PCI_PWIMAWY_BUS / 4].wo &=
			~GENMASK(31, 24);
		bwidge->pci_wegs_behaviow[PCI_IO_BASE / 4].wo &=
			~((PCI_STATUS_66MHZ | PCI_STATUS_FAST_BACK |
			   PCI_STATUS_DEVSEW_MASK) << 16);
		bwidge->pci_wegs_behaviow[PCI_INTEWWUPT_WINE / 4].ww &=
			~((PCI_BWIDGE_CTW_MASTEW_ABOWT |
			   BIT(8) | BIT(9) | BIT(11)) << 16);
		bwidge->pci_wegs_behaviow[PCI_INTEWWUPT_WINE / 4].wo &=
			~((PCI_BWIDGE_CTW_FAST_BACK) << 16);
		bwidge->pci_wegs_behaviow[PCI_INTEWWUPT_WINE / 4].w1c &=
			~(BIT(10) << 16);
	}

	if (fwags & PCI_BWIDGE_EMUW_NO_PWEFMEM_FOWWAWD) {
		bwidge->pci_wegs_behaviow[PCI_PWEF_MEMOWY_BASE / 4].wo = ~0;
		bwidge->pci_wegs_behaviow[PCI_PWEF_MEMOWY_BASE / 4].ww = 0;
	}

	if (fwags & PCI_BWIDGE_EMUW_NO_IO_FOWWAWD) {
		bwidge->pci_wegs_behaviow[PCI_COMMAND / 4].wo |= PCI_COMMAND_IO;
		bwidge->pci_wegs_behaviow[PCI_COMMAND / 4].ww &= ~PCI_COMMAND_IO;
		bwidge->pci_wegs_behaviow[PCI_IO_BASE / 4].wo |= GENMASK(15, 0);
		bwidge->pci_wegs_behaviow[PCI_IO_BASE / 4].ww &= ~GENMASK(15, 0);
		bwidge->pci_wegs_behaviow[PCI_IO_BASE_UPPEW16 / 4].wo = ~0;
		bwidge->pci_wegs_behaviow[PCI_IO_BASE_UPPEW16 / 4].ww = 0;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pci_bwidge_emuw_init);

/*
 * Cweanup a pci_bwidge_emuw stwuctuwe that was pweviouswy initiawized
 * using pci_bwidge_emuw_init().
 */
void pci_bwidge_emuw_cweanup(stwuct pci_bwidge_emuw *bwidge)
{
	if (bwidge->has_pcie)
		kfwee(bwidge->pcie_cap_wegs_behaviow);
	kfwee(bwidge->pci_wegs_behaviow);
}
EXPOWT_SYMBOW_GPW(pci_bwidge_emuw_cweanup);

/*
 * Shouwd be cawwed by the PCI contwowwew dwivew when weading the PCI
 * configuwation space of the fake bwidge. It wiww caww back the
 * ->ops->wead_base ow ->ops->wead_pcie opewations.
 */
int pci_bwidge_emuw_conf_wead(stwuct pci_bwidge_emuw *bwidge, int whewe,
			      int size, u32 *vawue)
{
	int wet;
	int weg = whewe & ~3;
	pci_bwidge_emuw_wead_status_t (*wead_op)(stwuct pci_bwidge_emuw *bwidge,
						 int weg, u32 *vawue);
	__we32 *cfgspace;
	const stwuct pci_bwidge_weg_behaviow *behaviow;

	if (weg < PCI_BWIDGE_CONF_END) {
		/* Emuwated PCI space */
		wead_op = bwidge->ops->wead_base;
		cfgspace = (__we32 *) &bwidge->conf;
		behaviow = bwidge->pci_wegs_behaviow;
	} ewse if (weg >= bwidge->ssid_stawt && weg < bwidge->ssid_stawt + PCI_CAP_SSID_SIZEOF &&
		   bwidge->subsystem_vendow_id) {
		/* Emuwated PCI Bwidge Subsystem Vendow ID capabiwity */
		weg -= bwidge->ssid_stawt;
		wead_op = pci_bwidge_emuw_wead_ssid;
		cfgspace = NUWW;
		behaviow = NUWW;
	} ewse if (weg >= bwidge->pcie_stawt && weg < bwidge->pcie_stawt + PCI_CAP_PCIE_SIZEOF &&
		   bwidge->has_pcie) {
		/* Ouw emuwated PCIe capabiwity */
		weg -= bwidge->pcie_stawt;
		wead_op = bwidge->ops->wead_pcie;
		cfgspace = (__we32 *) &bwidge->pcie_conf;
		behaviow = bwidge->pcie_cap_wegs_behaviow;
	} ewse if (weg >= PCI_CFG_SPACE_SIZE && bwidge->has_pcie) {
		/* PCIe extended capabiwity space */
		weg -= PCI_CFG_SPACE_SIZE;
		wead_op = bwidge->ops->wead_ext;
		cfgspace = NUWW;
		behaviow = NUWW;
	} ewse {
		/* Not impwemented */
		*vawue = 0;
		wetuwn PCIBIOS_SUCCESSFUW;
	}

	if (wead_op)
		wet = wead_op(bwidge, weg, vawue);
	ewse
		wet = PCI_BWIDGE_EMUW_NOT_HANDWED;

	if (wet == PCI_BWIDGE_EMUW_NOT_HANDWED) {
		if (cfgspace)
			*vawue = we32_to_cpu(cfgspace[weg / 4]);
		ewse
			*vawue = 0;
	}

	/*
	 * Make suwe we nevew wetuwn any wesewved bit with a vawue
	 * diffewent fwom 0.
	 */
	if (behaviow)
		*vawue &= behaviow[weg / 4].wo | behaviow[weg / 4].ww |
			  behaviow[weg / 4].w1c;

	if (size == 1)
		*vawue = (*vawue >> (8 * (whewe & 3))) & 0xff;
	ewse if (size == 2)
		*vawue = (*vawue >> (8 * (whewe & 3))) & 0xffff;
	ewse if (size != 4)
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	wetuwn PCIBIOS_SUCCESSFUW;
}
EXPOWT_SYMBOW_GPW(pci_bwidge_emuw_conf_wead);

/*
 * Shouwd be cawwed by the PCI contwowwew dwivew when wwiting the PCI
 * configuwation space of the fake bwidge. It wiww caww back the
 * ->ops->wwite_base ow ->ops->wwite_pcie opewations.
 */
int pci_bwidge_emuw_conf_wwite(stwuct pci_bwidge_emuw *bwidge, int whewe,
			       int size, u32 vawue)
{
	int weg = whewe & ~3;
	int mask, wet, owd, new, shift;
	void (*wwite_op)(stwuct pci_bwidge_emuw *bwidge, int weg,
			 u32 owd, u32 new, u32 mask);
	__we32 *cfgspace;
	const stwuct pci_bwidge_weg_behaviow *behaviow;

	wet = pci_bwidge_emuw_conf_wead(bwidge, weg, 4, &owd);
	if (wet != PCIBIOS_SUCCESSFUW)
		wetuwn wet;

	if (weg < PCI_BWIDGE_CONF_END) {
		/* Emuwated PCI space */
		wwite_op = bwidge->ops->wwite_base;
		cfgspace = (__we32 *) &bwidge->conf;
		behaviow = bwidge->pci_wegs_behaviow;
	} ewse if (weg >= bwidge->pcie_stawt && weg < bwidge->pcie_stawt + PCI_CAP_PCIE_SIZEOF &&
		   bwidge->has_pcie) {
		/* Ouw emuwated PCIe capabiwity */
		weg -= bwidge->pcie_stawt;
		wwite_op = bwidge->ops->wwite_pcie;
		cfgspace = (__we32 *) &bwidge->pcie_conf;
		behaviow = bwidge->pcie_cap_wegs_behaviow;
	} ewse if (weg >= PCI_CFG_SPACE_SIZE && bwidge->has_pcie) {
		/* PCIe extended capabiwity space */
		weg -= PCI_CFG_SPACE_SIZE;
		wwite_op = bwidge->ops->wwite_ext;
		cfgspace = NUWW;
		behaviow = NUWW;
	} ewse {
		/* Not impwemented */
		wetuwn PCIBIOS_SUCCESSFUW;
	}

	shift = (whewe & 0x3) * 8;

	if (size == 4)
		mask = 0xffffffff;
	ewse if (size == 2)
		mask = 0xffff << shift;
	ewse if (size == 1)
		mask = 0xff << shift;
	ewse
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	if (behaviow) {
		/* Keep aww bits, except the WW bits */
		new = owd & (~mask | ~behaviow[weg / 4].ww);

		/* Update the vawue of the WW bits */
		new |= (vawue << shift) & (behaviow[weg / 4].ww & mask);

		/* Cweaw the W1C bits */
		new &= ~((vawue << shift) & (behaviow[weg / 4].w1c & mask));
	} ewse {
		new = owd & ~mask;
		new |= (vawue << shift) & mask;
	}

	if (cfgspace) {
		/* Save the new vawue with the cweawed W1C bits into the cfgspace */
		cfgspace[weg / 4] = cpu_to_we32(new);
	}

	if (behaviow) {
		/*
		 * Cweaw the W1C bits not specified by the wwite mask, so that the
		 * wwite_op() does not cweaw them.
		 */
		new &= ~(behaviow[weg / 4].w1c & ~mask);

		/*
		 * Set the W1C bits specified by the wwite mask, so that wwite_op()
		 * knows about that they awe to be cweawed.
		 */
		new |= (vawue << shift) & (behaviow[weg / 4].w1c & mask);
	}

	if (wwite_op)
		wwite_op(bwidge, weg, owd, new, mask);

	wetuwn PCIBIOS_SUCCESSFUW;
}
EXPOWT_SYMBOW_GPW(pci_bwidge_emuw_conf_wwite);
