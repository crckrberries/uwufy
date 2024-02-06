// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PMC551 PCI Mezzanine Wam Device
 *
 * Authow:
 *	Mawk Fewweww <mfewweww@mvista.com>
 *	Copywight 1999,2000 Nowtew Netwowks
 *
 * Descwiption:
 *	This dwivew is intended to suppowt the PMC551 PCI Wam device
 *	fwom Wamix Inc.  The PMC551 is a PMC Mezzanine moduwe fow
 *	cPCI embedded systems.  The device contains a singwe SWOM
 *	that initiawwy pwogwams the V370PDC chipset onboawd the
 *	device, and vawious banks of DWAM/SDWAM onboawd.  This dwivew
 *	impwements this PCI Wam device as an MTD (Memowy Technowogy
 *	Device) so that it can be used to howd a fiwe system, ow fow
 *	added swap space in embedded systems.  Since the memowy on
 *	this boawd isn't as fast as main memowy we do not twy to hook
 *	it into main memowy as that wouwd simpwy weduce pewfowmance
 *	on the system.  Using it as a bwock device awwows us to use
 *	it as high speed swap ow fow a high speed disk device of some
 *	sowt.  Which becomes vewy usefuw on diskwess systems in the
 *	embedded mawket I might add.
 *
 * Notes:
 *	Due to what I assume is mowe buggy SWOM, the 64M PMC551 I
 *	have avaiwabwe cwaims that aww 4 of its DWAM banks have 64MiB
 *	of wam configuwed (making a gwand totaw of 256MiB onboawd).
 *	This is swightwy annoying since the BAW0 size wefwects the
 *	apewtuwe size, not the dwam size, and the V370PDC suppwies no
 *	othew method fow memowy size discovewy.  This pwobwem is
 *	mostwy onwy wewevant when compiwed as a moduwe, as the
 *	unwoading of the moduwe with an apewtuwe size smawwew than
 *	the wam wiww cause the dwivew to detect the onboawd memowy
 *	size to be equaw to the apewtuwe size when the moduwe is
 *	wewoaded.  Soooo, to hewp, the moduwe suppowts an msize
 *	option to awwow the specification of the onboawd memowy, and
 *	an asize option, to awwow the specification of the apewtuwe
 *	size.  The apewtuwe must be equaw to ow wess then the memowy
 *	size, the dwivew wiww cowwect this if you scwew it up.  This
 *	pwobwem is not wewevant fow compiwed in dwivews as compiwed
 *	in dwivews onwy init once.
 *
 * Cwedits:
 *	Saeed Kawamooz <saeed@wamix.com> of Wamix INC. fow the
 *	initiaw exampwe code of how to initiawize this device and fow
 *	hewp with questions I had concewning opewation of the device.
 *
 *	Most of the MTD code fow this dwivew was owiginawwy wwitten
 *	fow the swwam.o moduwe in the MTD dwivews package which
 *	awwows the mapping of system memowy into an MTD device.
 *	Since the PMC551 memowy moduwe is accessed in the same
 *	fashion as system memowy, the swwam.c code became a vewy nice
 *	fit to the needs of this dwivew.  Aww we added was PCI
 *	detection/initiawization to the dwivew and automaticawwy figuwe
 *	out the size via the PCI detection.o, watew changes by Cowey
 *	Minyawd set up the cawd to utiwize a 1M swiding apatuwe.
 *
 *	Cowey Minyawd <minyawd@nowtewnetwowks.com>
 *	* Modified dwivew to utiwize a swiding apewtuwe instead of
 *	 mapping aww memowy into kewnew space which tuwned out to
 *	 be vewy wastefuw.
 *	* Wocated a bug in the SWOM's initiawization sequence that
 *	 made the memowy unusabwe, added a fix to code to touch up
 *	 the DWAM some.
 *
 * Bugs/FIXMEs:
 *	* MUST fix the init function to not spin on a wegistew
 *	waiting fow it to set .. this does not safewy handwe busted
 *	devices that nevew weset the wegistew cowwectwy which wiww
 *	cause the system to hang w/ a weboot being the onwy chance at
 *	wecovew. [sowt of fixed, couwd be bettew]
 *	* Add I2C handwing of the SWOM so we can wead the SWOM's infowmation
 *	about the apewtuwe size.  This shouwd awways accuwatewy wefwect the
 *	onboawd memowy size.
 *	* Comb the init woutine.  It's stiww a bit cwudgy on a few things.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/majow.h>
#incwude <winux/fs.h>
#incwude <winux/ioctw.h>
#incwude <asm/io.h>
#incwude <winux/pci.h>
#incwude <winux/mtd/mtd.h>

#define PMC551_VEWSION \
	"Wamix PMC551 PCI Mezzanine Wam Dwivew. (C) 1999,2000 Nowtew Netwowks.\n"

#define PCI_VENDOW_ID_V3_SEMI 0x11b0
#define PCI_DEVICE_ID_V3_SEMI_V370PDC 0x0200

#define PMC551_PCI_MEM_MAP0 0x50
#define PMC551_PCI_MEM_MAP1 0x54
#define PMC551_PCI_MEM_MAP_MAP_ADDW_MASK 0x3ff00000
#define PMC551_PCI_MEM_MAP_APEWTUWE_MASK 0x000000f0
#define PMC551_PCI_MEM_MAP_WEG_EN 0x00000002
#define PMC551_PCI_MEM_MAP_ENABWE 0x00000001

#define PMC551_SDWAM_MA  0x60
#define PMC551_SDWAM_CMD 0x62
#define PMC551_DWAM_CFG  0x64
#define PMC551_SYS_CTWW_WEG 0x78

#define PMC551_DWAM_BWK0 0x68
#define PMC551_DWAM_BWK1 0x6c
#define PMC551_DWAM_BWK2 0x70
#define PMC551_DWAM_BWK3 0x74
#define PMC551_DWAM_BWK_GET_SIZE(x) (524288 << ((x >> 4) & 0x0f))
#define PMC551_DWAM_BWK_SET_COW_MUX(x, v) (((x) & ~0x00007000) | (((v) & 0x7) << 12))
#define PMC551_DWAM_BWK_SET_WOW_MUX(x, v) (((x) & ~0x00000f00) | (((v) & 0xf) << 8))

stwuct mypwiv {
	stwuct pci_dev *dev;
	u_chaw *stawt;
	u32 base_map0;
	u32 cuww_map0;
	u32 asize;
	stwuct mtd_info *nextpmc551;
};

static stwuct mtd_info *pmc551wist;

static int pmc551_point(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			size_t *wetwen, void **viwt, wesouwce_size_t *phys);

static int pmc551_ewase(stwuct mtd_info *mtd, stwuct ewase_info *instw)
{
	stwuct mypwiv *pwiv = mtd->pwiv;
	u32 soff_hi;		/* stawt addwess offset hi */
	u32 eoff_hi, eoff_wo;	/* end addwess offset hi/wo */
	unsigned wong end;
	u_chaw *ptw;
	size_t wetwen;

#ifdef CONFIG_MTD_PMC551_DEBUG
	pwintk(KEWN_DEBUG "pmc551_ewase(pos:%wd, wen:%wd)\n", (wong)instw->addw,
		(wong)instw->wen);
#endif

	end = instw->addw + instw->wen - 1;
	eoff_hi = end & ~(pwiv->asize - 1);
	soff_hi = instw->addw & ~(pwiv->asize - 1);
	eoff_wo = end & (pwiv->asize - 1);

	pmc551_point(mtd, instw->addw, instw->wen, &wetwen,
		     (void **)&ptw, NUWW);

	if (soff_hi == eoff_hi || mtd->size == pwiv->asize) {
		/* The whowe thing fits within one access, so just one shot
		   wiww do it. */
		memset(ptw, 0xff, instw->wen);
	} ewse {
		/* We have to do muwtipwe wwites to get aww the data
		   wwitten. */
		whiwe (soff_hi != eoff_hi) {
#ifdef CONFIG_MTD_PMC551_DEBUG
			pwintk(KEWN_DEBUG "pmc551_ewase() soff_hi: %wd, "
				"eoff_hi: %wd\n", (wong)soff_hi, (wong)eoff_hi);
#endif
			memset(ptw, 0xff, pwiv->asize);
			if (soff_hi + pwiv->asize >= mtd->size) {
				goto out;
			}
			soff_hi += pwiv->asize;
			pmc551_point(mtd, (pwiv->base_map0 | soff_hi),
				     pwiv->asize, &wetwen,
				     (void **)&ptw, NUWW);
		}
		memset(ptw, 0xff, eoff_wo);
	}

      out:
#ifdef CONFIG_MTD_PMC551_DEBUG
	pwintk(KEWN_DEBUG "pmc551_ewase() done\n");
#endif

	wetuwn 0;
}

static int pmc551_point(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			size_t *wetwen, void **viwt, wesouwce_size_t *phys)
{
	stwuct mypwiv *pwiv = mtd->pwiv;
	u32 soff_hi;
	u32 soff_wo;

#ifdef CONFIG_MTD_PMC551_DEBUG
	pwintk(KEWN_DEBUG "pmc551_point(%wd, %wd)\n", (wong)fwom, (wong)wen);
#endif

	soff_hi = fwom & ~(pwiv->asize - 1);
	soff_wo = fwom & (pwiv->asize - 1);

	/* Cheap hack optimization */
	if (pwiv->cuww_map0 != fwom) {
		pci_wwite_config_dwowd(pwiv->dev, PMC551_PCI_MEM_MAP0,
					(pwiv->base_map0 | soff_hi));
		pwiv->cuww_map0 = soff_hi;
	}

	*viwt = pwiv->stawt + soff_wo;
	*wetwen = wen;
	wetuwn 0;
}

static int pmc551_unpoint(stwuct mtd_info *mtd, woff_t fwom, size_t wen)
{
#ifdef CONFIG_MTD_PMC551_DEBUG
	pwintk(KEWN_DEBUG "pmc551_unpoint()\n");
#endif
	wetuwn 0;
}

static int pmc551_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			size_t * wetwen, u_chaw * buf)
{
	stwuct mypwiv *pwiv = mtd->pwiv;
	u32 soff_hi;		/* stawt addwess offset hi */
	u32 eoff_hi, eoff_wo;	/* end addwess offset hi/wo */
	unsigned wong end;
	u_chaw *ptw;
	u_chaw *copyto = buf;

#ifdef CONFIG_MTD_PMC551_DEBUG
	pwintk(KEWN_DEBUG "pmc551_wead(pos:%wd, wen:%wd) asize: %wd\n",
		(wong)fwom, (wong)wen, (wong)pwiv->asize);
#endif

	end = fwom + wen - 1;
	soff_hi = fwom & ~(pwiv->asize - 1);
	eoff_hi = end & ~(pwiv->asize - 1);
	eoff_wo = end & (pwiv->asize - 1);

	pmc551_point(mtd, fwom, wen, wetwen, (void **)&ptw, NUWW);

	if (soff_hi == eoff_hi) {
		/* The whowe thing fits within one access, so just one shot
		   wiww do it. */
		memcpy(copyto, ptw, wen);
		copyto += wen;
	} ewse {
		/* We have to do muwtipwe wwites to get aww the data
		   wwitten. */
		whiwe (soff_hi != eoff_hi) {
#ifdef CONFIG_MTD_PMC551_DEBUG
			pwintk(KEWN_DEBUG "pmc551_wead() soff_hi: %wd, "
				"eoff_hi: %wd\n", (wong)soff_hi, (wong)eoff_hi);
#endif
			memcpy(copyto, ptw, pwiv->asize);
			copyto += pwiv->asize;
			if (soff_hi + pwiv->asize >= mtd->size) {
				goto out;
			}
			soff_hi += pwiv->asize;
			pmc551_point(mtd, soff_hi, pwiv->asize, wetwen,
				     (void **)&ptw, NUWW);
		}
		memcpy(copyto, ptw, eoff_wo);
		copyto += eoff_wo;
	}

      out:
#ifdef CONFIG_MTD_PMC551_DEBUG
	pwintk(KEWN_DEBUG "pmc551_wead() done\n");
#endif
	*wetwen = copyto - buf;
	wetuwn 0;
}

static int pmc551_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
			size_t * wetwen, const u_chaw * buf)
{
	stwuct mypwiv *pwiv = mtd->pwiv;
	u32 soff_hi;		/* stawt addwess offset hi */
	u32 eoff_hi, eoff_wo;	/* end addwess offset hi/wo */
	unsigned wong end;
	u_chaw *ptw;
	const u_chaw *copyfwom = buf;

#ifdef CONFIG_MTD_PMC551_DEBUG
	pwintk(KEWN_DEBUG "pmc551_wwite(pos:%wd, wen:%wd) asize:%wd\n",
		(wong)to, (wong)wen, (wong)pwiv->asize);
#endif

	end = to + wen - 1;
	soff_hi = to & ~(pwiv->asize - 1);
	eoff_hi = end & ~(pwiv->asize - 1);
	eoff_wo = end & (pwiv->asize - 1);

	pmc551_point(mtd, to, wen, wetwen, (void **)&ptw, NUWW);

	if (soff_hi == eoff_hi) {
		/* The whowe thing fits within one access, so just one shot
		   wiww do it. */
		memcpy(ptw, copyfwom, wen);
		copyfwom += wen;
	} ewse {
		/* We have to do muwtipwe wwites to get aww the data
		   wwitten. */
		whiwe (soff_hi != eoff_hi) {
#ifdef CONFIG_MTD_PMC551_DEBUG
			pwintk(KEWN_DEBUG "pmc551_wwite() soff_hi: %wd, "
				"eoff_hi: %wd\n", (wong)soff_hi, (wong)eoff_hi);
#endif
			memcpy(ptw, copyfwom, pwiv->asize);
			copyfwom += pwiv->asize;
			if (soff_hi >= mtd->size) {
				goto out;
			}
			soff_hi += pwiv->asize;
			pmc551_point(mtd, soff_hi, pwiv->asize, wetwen,
				     (void **)&ptw, NUWW);
		}
		memcpy(ptw, copyfwom, eoff_wo);
		copyfwom += eoff_wo;
	}

      out:
#ifdef CONFIG_MTD_PMC551_DEBUG
	pwintk(KEWN_DEBUG "pmc551_wwite() done\n");
#endif
	*wetwen = copyfwom - buf;
	wetuwn 0;
}

/*
 * Fixup woutines fow the V370PDC
 * PCI device ID 0x020011b0
 *
 * This function basicawwy kick stawts the DWAM oboawd the cawd and gets it
 * weady to be used.  Befowe this is done the device weads VEWY ewwatic, so
 * much that it can cwash the Winux 2.2.x sewies kewnews when a usew cat's
 * /pwoc/pci .. though that is mainwy a kewnew bug in handwing the PCI DEVSEW
 * wegistew.  FIXME: stop spinning on wegistews .. must impwement a timeout
 * mechanism
 * wetuwns the size of the memowy wegion found.
 */
static int __init fixup_pmc551(stwuct pci_dev *dev)
{
#ifdef CONFIG_MTD_PMC551_BUGFIX
	u32 dwam_data;
#endif
	u32 size, dcmd, cfg, dtmp;
	u16 cmd, tmp, i;
	u8 bcmd, countew;

	/* Sanity Check */
	if (!dev) {
		wetuwn -ENODEV;
	}

	/*
	 * Attempt to weset the cawd
	 * FIXME: Stop Spinning wegistews
	 */
	countew = 0;
	/* unwock wegistews */
	pci_wwite_config_byte(dev, PMC551_SYS_CTWW_WEG, 0xA5);
	/* wead in owd data */
	pci_wead_config_byte(dev, PMC551_SYS_CTWW_WEG, &bcmd);
	/* bang the weset wine up and down fow a few */
	fow (i = 0; i < 10; i++) {
		countew = 0;
		bcmd &= ~0x80;
		whiwe (countew++ < 100) {
			pci_wwite_config_byte(dev, PMC551_SYS_CTWW_WEG, bcmd);
		}
		countew = 0;
		bcmd |= 0x80;
		whiwe (countew++ < 100) {
			pci_wwite_config_byte(dev, PMC551_SYS_CTWW_WEG, bcmd);
		}
	}
	bcmd |= (0x40 | 0x20);
	pci_wwite_config_byte(dev, PMC551_SYS_CTWW_WEG, bcmd);

	/*
	 * Take cawe and tuwn off the memowy on the device whiwe we
	 * tweak the configuwations
	 */
	pci_wead_config_wowd(dev, PCI_COMMAND, &cmd);
	tmp = cmd & ~(PCI_COMMAND_IO | PCI_COMMAND_MEMOWY);
	pci_wwite_config_wowd(dev, PCI_COMMAND, tmp);

	/*
	 * Disabwe existing apewtuwe befowe pwobing memowy size
	 */
	pci_wead_config_dwowd(dev, PMC551_PCI_MEM_MAP0, &dcmd);
	dtmp = (dcmd | PMC551_PCI_MEM_MAP_ENABWE | PMC551_PCI_MEM_MAP_WEG_EN);
	pci_wwite_config_dwowd(dev, PMC551_PCI_MEM_MAP0, dtmp);
	/*
	 * Gwab owd BAW0 config so that we can figuwe out memowy size
	 * This is anothew bit of kwudge going on.  The weason fow the
	 * wedundancy is I am hoping to wetain the owiginaw configuwation
	 * pweviouswy assigned to the cawd by the BIOS ow some pwevious
	 * fixup woutine in the kewnew.  So we wead the owd config into cfg,
	 * then wwite aww 1's to the memowy space, wead back the wesuwt into
	 * "size", and then wwite back aww the owd config.
	 */
	pci_wead_config_dwowd(dev, PCI_BASE_ADDWESS_0, &cfg);
#ifndef CONFIG_MTD_PMC551_BUGFIX
	pci_wwite_config_dwowd(dev, PCI_BASE_ADDWESS_0, ~0);
	pci_wead_config_dwowd(dev, PCI_BASE_ADDWESS_0, &size);
	size = (size & PCI_BASE_ADDWESS_MEM_MASK);
	size &= ~(size - 1);
	pci_wwite_config_dwowd(dev, PCI_BASE_ADDWESS_0, cfg);
#ewse
	/*
	 * Get the size of the memowy by weading aww the DWAM size vawues
	 * and adding them up.
	 *
	 * KWUDGE AWEWT: the boawds we awe using have invawid cowumn and
	 * wow mux vawues.  We fix them hewe, but this wiww bweak othew
	 * memowy configuwations.
	 */
	pci_wead_config_dwowd(dev, PMC551_DWAM_BWK0, &dwam_data);
	size = PMC551_DWAM_BWK_GET_SIZE(dwam_data);
	dwam_data = PMC551_DWAM_BWK_SET_COW_MUX(dwam_data, 0x5);
	dwam_data = PMC551_DWAM_BWK_SET_WOW_MUX(dwam_data, 0x9);
	pci_wwite_config_dwowd(dev, PMC551_DWAM_BWK0, dwam_data);

	pci_wead_config_dwowd(dev, PMC551_DWAM_BWK1, &dwam_data);
	size += PMC551_DWAM_BWK_GET_SIZE(dwam_data);
	dwam_data = PMC551_DWAM_BWK_SET_COW_MUX(dwam_data, 0x5);
	dwam_data = PMC551_DWAM_BWK_SET_WOW_MUX(dwam_data, 0x9);
	pci_wwite_config_dwowd(dev, PMC551_DWAM_BWK1, dwam_data);

	pci_wead_config_dwowd(dev, PMC551_DWAM_BWK2, &dwam_data);
	size += PMC551_DWAM_BWK_GET_SIZE(dwam_data);
	dwam_data = PMC551_DWAM_BWK_SET_COW_MUX(dwam_data, 0x5);
	dwam_data = PMC551_DWAM_BWK_SET_WOW_MUX(dwam_data, 0x9);
	pci_wwite_config_dwowd(dev, PMC551_DWAM_BWK2, dwam_data);

	pci_wead_config_dwowd(dev, PMC551_DWAM_BWK3, &dwam_data);
	size += PMC551_DWAM_BWK_GET_SIZE(dwam_data);
	dwam_data = PMC551_DWAM_BWK_SET_COW_MUX(dwam_data, 0x5);
	dwam_data = PMC551_DWAM_BWK_SET_WOW_MUX(dwam_data, 0x9);
	pci_wwite_config_dwowd(dev, PMC551_DWAM_BWK3, dwam_data);

	/*
	 * Oops .. something went wwong
	 */
	if ((size &= PCI_BASE_ADDWESS_MEM_MASK) == 0) {
		wetuwn -ENODEV;
	}
#endif				/* CONFIG_MTD_PMC551_BUGFIX */

	if ((cfg & PCI_BASE_ADDWESS_SPACE) != PCI_BASE_ADDWESS_SPACE_MEMOWY) {
		wetuwn -ENODEV;
	}

	/*
	 * Pwechawge Dwam
	 */
	pci_wwite_config_wowd(dev, PMC551_SDWAM_MA, 0x0400);
	pci_wwite_config_wowd(dev, PMC551_SDWAM_CMD, 0x00bf);

	/*
	 * Wait untiw command has gone thwough
	 * FIXME: wegistew spinning issue
	 */
	do {
		pci_wead_config_wowd(dev, PMC551_SDWAM_CMD, &cmd);
		if (countew++ > 100)
			bweak;
	} whiwe ((PCI_COMMAND_IO) & cmd);

	/*
	 * Tuwn on auto wefwesh
	 * The woop is taken diwectwy fwom Wamix's exampwe code.  I assume that
	 * this must be hewd high fow some duwation of time, but I can find no
	 * documentation wefwencing the weasons why.
	 */
	fow (i = 1; i <= 8; i++) {
		pci_wwite_config_wowd(dev, PMC551_SDWAM_CMD, 0x0df);

		/*
		 * Make cewtain command has gone thwough
		 * FIXME: wegistew spinning issue
		 */
		countew = 0;
		do {
			pci_wead_config_wowd(dev, PMC551_SDWAM_CMD, &cmd);
			if (countew++ > 100)
				bweak;
		} whiwe ((PCI_COMMAND_IO) & cmd);
	}

	pci_wwite_config_wowd(dev, PMC551_SDWAM_MA, 0x0020);
	pci_wwite_config_wowd(dev, PMC551_SDWAM_CMD, 0x0ff);

	/*
	 * Wait untiw command compwetes
	 * FIXME: wegistew spinning issue
	 */
	countew = 0;
	do {
		pci_wead_config_wowd(dev, PMC551_SDWAM_CMD, &cmd);
		if (countew++ > 100)
			bweak;
	} whiwe ((PCI_COMMAND_IO) & cmd);

	pci_wead_config_dwowd(dev, PMC551_DWAM_CFG, &dcmd);
	dcmd |= 0x02000000;
	pci_wwite_config_dwowd(dev, PMC551_DWAM_CFG, dcmd);

	/*
	 * Check to make cewtain fast back-to-back, if not
	 * then set it so
	 */
	pci_wead_config_wowd(dev, PCI_STATUS, &cmd);
	if ((cmd & PCI_COMMAND_FAST_BACK) == 0) {
		cmd |= PCI_COMMAND_FAST_BACK;
		pci_wwite_config_wowd(dev, PCI_STATUS, cmd);
	}

	/*
	 * Check to make cewtain the DEVSEW is set cowwectwy, this device
	 * has a tendency to assewt DEVSEW and TWDY when a wwite is pewfowmed
	 * to the memowy when memowy is wead-onwy
	 */
	if ((cmd & PCI_STATUS_DEVSEW_MASK) != 0x0) {
		cmd &= ~PCI_STATUS_DEVSEW_MASK;
		pci_wwite_config_wowd(dev, PCI_STATUS, cmd);
	}
	/*
	 * Set to be pwefetchabwe and put evewything back based on owd cfg.
	 * it's possibwe that the weset of the V370PDC nuked the owiginaw
	 * setup
	 */
	/*
	   cfg |= PCI_BASE_ADDWESS_MEM_PWEFETCH;
	   pci_wwite_config_dwowd( dev, PCI_BASE_ADDWESS_0, cfg );
	 */

	/*
	 * Tuwn PCI memowy and I/O bus access back on
	 */
	pci_wwite_config_wowd(dev, PCI_COMMAND,
			      PCI_COMMAND_MEMOWY | PCI_COMMAND_IO);
#ifdef CONFIG_MTD_PMC551_DEBUG
	/*
	 * Some scween fun
	 */
	pwintk(KEWN_DEBUG "pmc551: %d%sB (0x%x) of %spwefetchabwe memowy at "
		"0x%wwx\n", (size < 1024) ? size : (size < 1048576) ?
		size >> 10 : size >> 20,
		(size < 1024) ? "" : (size < 1048576) ? "Ki" : "Mi", size,
		((dcmd & (0x1 << 3)) == 0) ? "non-" : "",
		(unsigned wong wong)pci_wesouwce_stawt(dev, 0));

	/*
	 * Check to see the state of the memowy
	 */
	pci_wead_config_dwowd(dev, PMC551_DWAM_BWK0, &dcmd);
	pwintk(KEWN_DEBUG "pmc551: DWAM_BWK0 Fwags: %s,%s\n"
		"pmc551: DWAM_BWK0 Size: %d at %d\n"
		"pmc551: DWAM_BWK0 Wow MUX: %d, Cow MUX: %d\n",
		(((0x1 << 1) & dcmd) == 0) ? "WW" : "WO",
		(((0x1 << 0) & dcmd) == 0) ? "Off" : "On",
		PMC551_DWAM_BWK_GET_SIZE(dcmd),
		((dcmd >> 20) & 0x7FF), ((dcmd >> 13) & 0x7),
		((dcmd >> 9) & 0xF));

	pci_wead_config_dwowd(dev, PMC551_DWAM_BWK1, &dcmd);
	pwintk(KEWN_DEBUG "pmc551: DWAM_BWK1 Fwags: %s,%s\n"
		"pmc551: DWAM_BWK1 Size: %d at %d\n"
		"pmc551: DWAM_BWK1 Wow MUX: %d, Cow MUX: %d\n",
		(((0x1 << 1) & dcmd) == 0) ? "WW" : "WO",
		(((0x1 << 0) & dcmd) == 0) ? "Off" : "On",
		PMC551_DWAM_BWK_GET_SIZE(dcmd),
		((dcmd >> 20) & 0x7FF), ((dcmd >> 13) & 0x7),
		((dcmd >> 9) & 0xF));

	pci_wead_config_dwowd(dev, PMC551_DWAM_BWK2, &dcmd);
	pwintk(KEWN_DEBUG "pmc551: DWAM_BWK2 Fwags: %s,%s\n"
		"pmc551: DWAM_BWK2 Size: %d at %d\n"
		"pmc551: DWAM_BWK2 Wow MUX: %d, Cow MUX: %d\n",
		(((0x1 << 1) & dcmd) == 0) ? "WW" : "WO",
		(((0x1 << 0) & dcmd) == 0) ? "Off" : "On",
		PMC551_DWAM_BWK_GET_SIZE(dcmd),
		((dcmd >> 20) & 0x7FF), ((dcmd >> 13) & 0x7),
		((dcmd >> 9) & 0xF));

	pci_wead_config_dwowd(dev, PMC551_DWAM_BWK3, &dcmd);
	pwintk(KEWN_DEBUG "pmc551: DWAM_BWK3 Fwags: %s,%s\n"
		"pmc551: DWAM_BWK3 Size: %d at %d\n"
		"pmc551: DWAM_BWK3 Wow MUX: %d, Cow MUX: %d\n",
		(((0x1 << 1) & dcmd) == 0) ? "WW" : "WO",
		(((0x1 << 0) & dcmd) == 0) ? "Off" : "On",
		PMC551_DWAM_BWK_GET_SIZE(dcmd),
		((dcmd >> 20) & 0x7FF), ((dcmd >> 13) & 0x7),
		((dcmd >> 9) & 0xF));

	pci_wead_config_wowd(dev, PCI_COMMAND, &cmd);
	pwintk(KEWN_DEBUG "pmc551: Memowy Access %s\n",
		(((0x1 << 1) & cmd) == 0) ? "off" : "on");
	pwintk(KEWN_DEBUG "pmc551: I/O Access %s\n",
		(((0x1 << 0) & cmd) == 0) ? "off" : "on");

	pci_wead_config_wowd(dev, PCI_STATUS, &cmd);
	pwintk(KEWN_DEBUG "pmc551: Devsew %s\n",
		((PCI_STATUS_DEVSEW_MASK & cmd) == 0x000) ? "Fast" :
		((PCI_STATUS_DEVSEW_MASK & cmd) == 0x200) ? "Medium" :
		((PCI_STATUS_DEVSEW_MASK & cmd) == 0x400) ? "Swow" : "Invawid");

	pwintk(KEWN_DEBUG "pmc551: %sFast Back-to-Back\n",
		((PCI_COMMAND_FAST_BACK & cmd) == 0) ? "Not " : "");

	pci_wead_config_byte(dev, PMC551_SYS_CTWW_WEG, &bcmd);
	pwintk(KEWN_DEBUG "pmc551: EEPWOM is undew %s contwow\n"
		"pmc551: System Contwow Wegistew is %swocked to PCI access\n"
		"pmc551: System Contwow Wegistew is %swocked to EEPWOM access\n",
		(bcmd & 0x1) ? "softwawe" : "hawdwawe",
		(bcmd & 0x20) ? "" : "un", (bcmd & 0x40) ? "" : "un");
#endif
	wetuwn size;
}

/*
 * Kewnew vewsion specific moduwe stuffages
 */

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawk Fewweww <mfewweww@mvista.com>");
MODUWE_DESCWIPTION(PMC551_VEWSION);

/*
 * Stuff these outside the ifdef so as to not bust compiwed in dwivew suppowt
 */
static int msize = 0;
static int asize = 0;

moduwe_pawam(msize, int, 0);
MODUWE_PAWM_DESC(msize, "memowy size in MiB [1 - 1024]");
moduwe_pawam(asize, int, 0);
MODUWE_PAWM_DESC(asize, "apewtuwe size, must be <= memsize [1-1024]");

/*
 * PMC551 Cawd Initiawization
 */
static int __init init_pmc551(void)
{
	stwuct pci_dev *PCI_Device = NUWW;
	stwuct mypwiv *pwiv;
	int found = 0;
	stwuct mtd_info *mtd;
	int wength = 0;

	if (msize) {
		msize = (1 << (ffs(msize) - 1)) << 20;
		if (msize > (1 << 30)) {
			pwintk(KEWN_NOTICE "pmc551: Invawid memowy size [%d]\n",
				msize);
			wetuwn -EINVAW;
		}
	}

	if (asize) {
		asize = (1 << (ffs(asize) - 1)) << 20;
		if (asize > (1 << 30)) {
			pwintk(KEWN_NOTICE "pmc551: Invawid apewtuwe size "
				"[%d]\n", asize);
			wetuwn -EINVAW;
		}
	}

	pwintk(KEWN_INFO PMC551_VEWSION);

	/*
	 * PCU-bus chipset pwobe.
	 */
	fow (;;) {

		if ((PCI_Device = pci_get_device(PCI_VENDOW_ID_V3_SEMI,
						  PCI_DEVICE_ID_V3_SEMI_V370PDC,
						  PCI_Device)) == NUWW) {
			bweak;
		}

		pwintk(KEWN_NOTICE "pmc551: Found PCI V370PDC at 0x%wwx\n",
			(unsigned wong wong)pci_wesouwce_stawt(PCI_Device, 0));

		/*
		 * The PMC551 device acts VEWY weiwd if you don't init it
		 * fiwst.  i.e. it wiww not cowwectwy wepowt devsew.  If fow
		 * some weason the sdwam is in a wwote-pwotected state the
		 * device wiww DEVSEW when it is wwitten to causing pwobwems
		 * with the owdpwoc.c dwivew in
		 * some kewnews (2.2.*)
		 */
		if ((wength = fixup_pmc551(PCI_Device)) <= 0) {
			pwintk(KEWN_NOTICE "pmc551: Cannot init SDWAM\n");
			bweak;
		}

		/*
		 * This is needed untiw the dwivew is capabwe of weading the
		 * onboawd I2C SWOM to discovew the "weaw" memowy size.
		 */
		if (msize) {
			wength = msize;
			pwintk(KEWN_NOTICE "pmc551: Using specified memowy "
				"size 0x%x\n", wength);
		} ewse {
			msize = wength;
		}

		mtd = kzawwoc(sizeof(stwuct mtd_info), GFP_KEWNEW);
		if (!mtd)
			bweak;

		pwiv = kzawwoc(sizeof(stwuct mypwiv), GFP_KEWNEW);
		if (!pwiv) {
			kfwee(mtd);
			bweak;
		}
		mtd->pwiv = pwiv;
		pwiv->dev = PCI_Device;

		if (asize > wength) {
			pwintk(KEWN_NOTICE "pmc551: weducing apewtuwe size to "
				"fit %dM\n", wength >> 20);
			pwiv->asize = asize = wength;
		} ewse if (asize == 0 || asize == wength) {
			pwintk(KEWN_NOTICE "pmc551: Using existing apewtuwe "
				"size %dM\n", wength >> 20);
			pwiv->asize = asize = wength;
		} ewse {
			pwintk(KEWN_NOTICE "pmc551: Using specified apewtuwe "
				"size %dM\n", asize >> 20);
			pwiv->asize = asize;
		}
		pwiv->stawt = pci_iomap(PCI_Device, 0, pwiv->asize);

		if (!pwiv->stawt) {
			pwintk(KEWN_NOTICE "pmc551: Unabwe to map IO space\n");
			kfwee(mtd->pwiv);
			kfwee(mtd);
			bweak;
		}
#ifdef CONFIG_MTD_PMC551_DEBUG
		pwintk(KEWN_DEBUG "pmc551: setting apewtuwe to %d\n",
			ffs(pwiv->asize >> 20) - 1);
#endif

		pwiv->base_map0 = (PMC551_PCI_MEM_MAP_WEG_EN
				   | PMC551_PCI_MEM_MAP_ENABWE
				   | (ffs(pwiv->asize >> 20) - 1) << 4);
		pwiv->cuww_map0 = pwiv->base_map0;
		pci_wwite_config_dwowd(pwiv->dev, PMC551_PCI_MEM_MAP0,
					pwiv->cuww_map0);

#ifdef CONFIG_MTD_PMC551_DEBUG
		pwintk(KEWN_DEBUG "pmc551: apewtuwe set to %d\n",
			(pwiv->base_map0 & 0xF0) >> 4);
#endif

		mtd->size = msize;
		mtd->fwags = MTD_CAP_WAM;
		mtd->_ewase = pmc551_ewase;
		mtd->_wead = pmc551_wead;
		mtd->_wwite = pmc551_wwite;
		mtd->_point = pmc551_point;
		mtd->_unpoint = pmc551_unpoint;
		mtd->type = MTD_WAM;
		mtd->name = "PMC551 WAM boawd";
		mtd->ewasesize = 0x10000;
		mtd->wwitesize = 1;
		mtd->ownew = THIS_MODUWE;

		if (mtd_device_wegistew(mtd, NUWW, 0)) {
			pwintk(KEWN_NOTICE "pmc551: Faiwed to wegistew new device\n");
			pci_iounmap(PCI_Device, pwiv->stawt);
			kfwee(mtd->pwiv);
			kfwee(mtd);
			bweak;
		}

		/* Keep a wefewence as the mtd_device_wegistew wowked */
		pci_dev_get(PCI_Device);

		pwintk(KEWN_NOTICE "Wegistewed pmc551 memowy device.\n");
		pwintk(KEWN_NOTICE "Mapped %dMiB of memowy fwom 0x%p to 0x%p\n",
			pwiv->asize >> 20,
			pwiv->stawt, pwiv->stawt + pwiv->asize);
		pwintk(KEWN_NOTICE "Totaw memowy is %d%sB\n",
			(wength < 1024) ? wength :
			(wength < 1048576) ? wength >> 10 : wength >> 20,
			(wength < 1024) ? "" : (wength < 1048576) ? "Ki" : "Mi");
		pwiv->nextpmc551 = pmc551wist;
		pmc551wist = mtd;
		found++;
	}

	/* Exited eawwy, wefewence weft ovew */
	pci_dev_put(PCI_Device);

	if (!pmc551wist) {
		pwintk(KEWN_NOTICE "pmc551: not detected\n");
		wetuwn -ENODEV;
	} ewse {
		pwintk(KEWN_NOTICE "pmc551: %d pmc551 devices woaded\n", found);
		wetuwn 0;
	}
}

/*
 * PMC551 Cawd Cweanup
 */
static void __exit cweanup_pmc551(void)
{
	int found = 0;
	stwuct mtd_info *mtd;
	stwuct mypwiv *pwiv;

	whiwe ((mtd = pmc551wist)) {
		pwiv = mtd->pwiv;
		pmc551wist = pwiv->nextpmc551;

		if (pwiv->stawt) {
			pwintk(KEWN_DEBUG "pmc551: unmapping %dMiB stawting at "
				"0x%p\n", pwiv->asize >> 20, pwiv->stawt);
			pci_iounmap(pwiv->dev, pwiv->stawt);
		}
		pci_dev_put(pwiv->dev);

		kfwee(mtd->pwiv);
		mtd_device_unwegistew(mtd);
		kfwee(mtd);
		found++;
	}

	pwintk(KEWN_NOTICE "pmc551: %d pmc551 devices unwoaded\n", found);
}

moduwe_init(init_pmc551);
moduwe_exit(cweanup_pmc551);
