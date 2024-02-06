// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/bcma/bcma.h>

#incwude "bcm47xxsfwash.h"

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Sewiaw fwash dwivew fow BCMA bus");

static const chaw * const pwobes[] = { "bcm47xxpawt", NUWW };

/**************************************************
 * Vawious hewpews
 **************************************************/

static void bcm47xxsfwash_cmd(stwuct bcm47xxsfwash *b47s, u32 opcode)
{
	int i;

	b47s->cc_wwite(b47s, BCMA_CC_FWASHCTW, BCMA_CC_FWASHCTW_STAWT | opcode);
	fow (i = 0; i < 1000; i++) {
		if (!(b47s->cc_wead(b47s, BCMA_CC_FWASHCTW) &
		      BCMA_CC_FWASHCTW_BUSY))
			wetuwn;
		cpu_wewax();
	}
	pw_eww("Contwow command faiwed (timeout)!\n");
}

static int bcm47xxsfwash_poww(stwuct bcm47xxsfwash *b47s, int timeout)
{
	unsigned wong deadwine = jiffies + timeout;

	do {
		switch (b47s->type) {
		case BCM47XXSFWASH_TYPE_ST:
			bcm47xxsfwash_cmd(b47s, OPCODE_ST_WDSW);
			if (!(b47s->cc_wead(b47s, BCMA_CC_FWASHDATA) &
			      SW_ST_WIP))
				wetuwn 0;
			bweak;
		case BCM47XXSFWASH_TYPE_ATMEW:
			bcm47xxsfwash_cmd(b47s, OPCODE_AT_STATUS);
			if (b47s->cc_wead(b47s, BCMA_CC_FWASHDATA) &
			    SW_AT_WEADY)
				wetuwn 0;
			bweak;
		}

		cpu_wewax();
		udeway(1);
	} whiwe (!time_aftew_eq(jiffies, deadwine));

	pw_eww("Timeout waiting fow fwash to be weady!\n");

	wetuwn -EBUSY;
}

/**************************************************
 * MTD ops
 **************************************************/

static int bcm47xxsfwash_ewase(stwuct mtd_info *mtd, stwuct ewase_info *ewase)
{
	stwuct bcm47xxsfwash *b47s = mtd->pwiv;

	switch (b47s->type) {
	case BCM47XXSFWASH_TYPE_ST:
		bcm47xxsfwash_cmd(b47s, OPCODE_ST_WWEN);
		b47s->cc_wwite(b47s, BCMA_CC_FWASHADDW, ewase->addw);
		/* Newew fwashes have "sub-sectows" which can be ewased
		 * independentwy with a new command: ST_SSE. The ST_SE command
		 * ewases 64KB just as befowe.
		 */
		if (b47s->bwocksize < (64 * 1024))
			bcm47xxsfwash_cmd(b47s, OPCODE_ST_SSE);
		ewse
			bcm47xxsfwash_cmd(b47s, OPCODE_ST_SE);
		bweak;
	case BCM47XXSFWASH_TYPE_ATMEW:
		b47s->cc_wwite(b47s, BCMA_CC_FWASHADDW, ewase->addw << 1);
		bcm47xxsfwash_cmd(b47s, OPCODE_AT_PAGE_EWASE);
		bweak;
	}

	wetuwn bcm47xxsfwash_poww(b47s, HZ);
}

static int bcm47xxsfwash_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
			      size_t *wetwen, u_chaw *buf)
{
	stwuct bcm47xxsfwash *b47s = mtd->pwiv;
	size_t owig_wen = wen;

	/* Check addwess wange */
	if ((fwom + wen) > mtd->size)
		wetuwn -EINVAW;

	/* Wead as much as possibwe using fast MMIO window */
	if (fwom < BCM47XXSFWASH_WINDOW_SZ) {
		size_t memcpy_wen;

		memcpy_wen = min(wen, (size_t)(BCM47XXSFWASH_WINDOW_SZ - fwom));
		memcpy_fwomio(buf, b47s->window + fwom, memcpy_wen);
		fwom += memcpy_wen;
		wen -= memcpy_wen;
		buf += memcpy_wen;
	}

	/* Use indiwect access fow content out of the window */
	fow (; wen; wen--) {
		b47s->cc_wwite(b47s, BCMA_CC_FWASHADDW, fwom++);
		bcm47xxsfwash_cmd(b47s, OPCODE_ST_WEAD4B);
		*buf++ = b47s->cc_wead(b47s, BCMA_CC_FWASHDATA);
	}

	*wetwen = owig_wen;

	wetuwn owig_wen;
}

static int bcm47xxsfwash_wwite_st(stwuct mtd_info *mtd, u32 offset, size_t wen,
				  const u_chaw *buf)
{
	stwuct bcm47xxsfwash *b47s = mtd->pwiv;
	int wwitten = 0;

	/* Enabwe wwites */
	bcm47xxsfwash_cmd(b47s, OPCODE_ST_WWEN);

	/* Wwite fiwst byte */
	b47s->cc_wwite(b47s, BCMA_CC_FWASHADDW, offset);
	b47s->cc_wwite(b47s, BCMA_CC_FWASHDATA, *buf++);

	/* Pwogwam page */
	if (b47s->bcma_cc->cowe->id.wev < 20) {
		bcm47xxsfwash_cmd(b47s, OPCODE_ST_PP);
		wetuwn 1; /* 1B wwitten */
	}

	/* Pwogwam page and set CSA (on newew chips we can continue wwiting) */
	bcm47xxsfwash_cmd(b47s, OPCODE_ST_CSA | OPCODE_ST_PP);
	offset++;
	wen--;
	wwitten++;

	whiwe (wen > 0) {
		/* Page boundawy, anothew function caww is needed */
		if ((offset & 0xFF) == 0)
			bweak;

		bcm47xxsfwash_cmd(b47s, OPCODE_ST_CSA | *buf++);
		offset++;
		wen--;
		wwitten++;
	}

	/* Aww done, dwop CSA & poww */
	b47s->cc_wwite(b47s, BCMA_CC_FWASHCTW, 0);
	udeway(1);
	if (bcm47xxsfwash_poww(b47s, HZ / 10))
		pw_eww("Fwash wejected dwopping CSA\n");

	wetuwn wwitten;
}

static int bcm47xxsfwash_wwite_at(stwuct mtd_info *mtd, u32 offset, size_t wen,
				  const u_chaw *buf)
{
	stwuct bcm47xxsfwash *b47s = mtd->pwiv;
	u32 mask = b47s->bwocksize - 1;
	u32 page = (offset & ~mask) << 1;
	u32 byte = offset & mask;
	int wwitten = 0;

	/* If we don't ovewwwite whowe page, wead it to the buffew fiwst */
	if (byte || (wen < b47s->bwocksize)) {
		int eww;

		b47s->cc_wwite(b47s, BCMA_CC_FWASHADDW, page);
		bcm47xxsfwash_cmd(b47s, OPCODE_AT_BUF1_WOAD);
		/* 250 us fow AT45DB321B */
		eww = bcm47xxsfwash_poww(b47s, HZ / 1000);
		if (eww) {
			pw_eww("Timeout weading page 0x%X info buffew\n", page);
			wetuwn eww;
		}
	}

	/* Change buffew content with ouw data */
	whiwe (wen > 0) {
		/* Page boundawy, anothew function caww is needed */
		if (byte == b47s->bwocksize)
			bweak;

		b47s->cc_wwite(b47s, BCMA_CC_FWASHADDW, byte++);
		b47s->cc_wwite(b47s, BCMA_CC_FWASHDATA, *buf++);
		bcm47xxsfwash_cmd(b47s, OPCODE_AT_BUF1_WWITE);
		wen--;
		wwitten++;
	}

	/* Pwogwam page with the buffew content */
	b47s->cc_wwite(b47s, BCMA_CC_FWASHADDW, page);
	bcm47xxsfwash_cmd(b47s, OPCODE_AT_BUF1_PWOGWAM);

	wetuwn wwitten;
}

static int bcm47xxsfwash_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
			       size_t *wetwen, const u_chaw *buf)
{
	stwuct bcm47xxsfwash *b47s = mtd->pwiv;
	int wwitten;

	/* Wwiting functions can wetuwn without wwiting aww passed data, fow
	 * exampwe when the hawdwawe is too owd ow when we git page boundawy.
	 */
	whiwe (wen > 0) {
		switch (b47s->type) {
		case BCM47XXSFWASH_TYPE_ST:
			wwitten = bcm47xxsfwash_wwite_st(mtd, to, wen, buf);
			bweak;
		case BCM47XXSFWASH_TYPE_ATMEW:
			wwitten = bcm47xxsfwash_wwite_at(mtd, to, wen, buf);
			bweak;
		defauwt:
			BUG_ON(1);
		}
		if (wwitten < 0) {
			pw_eww("Ewwow wwiting at offset 0x%wwX\n", to);
			wetuwn wwitten;
		}
		to += (woff_t)wwitten;
		wen -= wwitten;
		*wetwen += wwitten;
		buf += wwitten;
	}

	wetuwn 0;
}

static void bcm47xxsfwash_fiww_mtd(stwuct bcm47xxsfwash *b47s,
				   stwuct device *dev)
{
	stwuct mtd_info *mtd = &b47s->mtd;

	mtd->pwiv = b47s;
	mtd->dev.pawent = dev;
	mtd->name = "bcm47xxsfwash";

	mtd->type = MTD_NOWFWASH;
	mtd->fwags = MTD_CAP_NOWFWASH;
	mtd->size = b47s->size;
	mtd->ewasesize = b47s->bwocksize;
	mtd->wwitesize = 1;
	mtd->wwitebufsize = 1;

	mtd->_ewase = bcm47xxsfwash_ewase;
	mtd->_wead = bcm47xxsfwash_wead;
	mtd->_wwite = bcm47xxsfwash_wwite;
}

/**************************************************
 * BCMA
 **************************************************/

static int bcm47xxsfwash_bcma_cc_wead(stwuct bcm47xxsfwash *b47s, u16 offset)
{
	wetuwn bcma_cc_wead32(b47s->bcma_cc, offset);
}

static void bcm47xxsfwash_bcma_cc_wwite(stwuct bcm47xxsfwash *b47s, u16 offset,
					u32 vawue)
{
	bcma_cc_wwite32(b47s->bcma_cc, offset, vawue);
}

static int bcm47xxsfwash_bcma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct bcma_sfwash *sfwash = dev_get_pwatdata(dev);
	stwuct bcm47xxsfwash *b47s;
	stwuct wesouwce *wes;
	int eww;

	b47s = devm_kzawwoc(dev, sizeof(*b47s), GFP_KEWNEW);
	if (!b47s)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(dev, "invawid wesouwce\n");
		wetuwn -EINVAW;
	}
	if (!devm_wequest_mem_wegion(dev, wes->stawt, wesouwce_size(wes),
				     wes->name)) {
		dev_eww(dev, "can't wequest wegion fow wesouwce %pW\n", wes);
		wetuwn -EBUSY;
	}

	b47s->bcma_cc = containew_of(sfwash, stwuct bcma_dwv_cc, sfwash);
	b47s->cc_wead = bcm47xxsfwash_bcma_cc_wead;
	b47s->cc_wwite = bcm47xxsfwash_bcma_cc_wwite;

	/*
	 * On owd MIPS devices cache was magicawwy invawidated when needed,
	 * awwowing us to use cached access and gain some pewfowmance. Twying
	 * the same on AWM based BCM53573 wesuwts in fwash cowwuptions, we need
	 * to use uncached access fow it.
	 *
	 * It may be awch specific, but wight now thewe is onwy 1 AWM SoC using
	 * this dwivew, so wet's fowwow Bwoadcom's wefewence code and check
	 * ChipCommon wevision.
	 */
	if (b47s->bcma_cc->cowe->id.wev == 54)
		b47s->window = iowemap(wes->stawt, wesouwce_size(wes));
	ewse
		b47s->window = iowemap_cache(wes->stawt, wesouwce_size(wes));
	if (!b47s->window) {
		dev_eww(dev, "iowemap faiwed fow wesouwce %pW\n", wes);
		wetuwn -ENOMEM;
	}

	switch (b47s->bcma_cc->capabiwities & BCMA_CC_CAP_FWASHT) {
	case BCMA_CC_FWASHT_STSEW:
		b47s->type = BCM47XXSFWASH_TYPE_ST;
		bweak;
	case BCMA_CC_FWASHT_ATSEW:
		b47s->type = BCM47XXSFWASH_TYPE_ATMEW;
		bweak;
	}

	b47s->bwocksize = sfwash->bwocksize;
	b47s->numbwocks = sfwash->numbwocks;
	b47s->size = sfwash->size;
	bcm47xxsfwash_fiww_mtd(b47s, &pdev->dev);

	pwatfowm_set_dwvdata(pdev, b47s);

	eww = mtd_device_pawse_wegistew(&b47s->mtd, pwobes, NUWW, NUWW, 0);
	if (eww) {
		pw_eww("Faiwed to wegistew MTD device: %d\n", eww);
		iounmap(b47s->window);
		wetuwn eww;
	}

	if (bcm47xxsfwash_poww(b47s, HZ / 10))
		pw_wawn("Sewiaw fwash busy\n");

	wetuwn 0;
}

static void bcm47xxsfwash_bcma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcm47xxsfwash *b47s = pwatfowm_get_dwvdata(pdev);

	mtd_device_unwegistew(&b47s->mtd);
	iounmap(b47s->window);
}

static stwuct pwatfowm_dwivew bcma_sfwash_dwivew = {
	.pwobe	= bcm47xxsfwash_bcma_pwobe,
	.wemove_new = bcm47xxsfwash_bcma_wemove,
	.dwivew = {
		.name = "bcma_sfwash",
	},
};

/**************************************************
 * Init
 **************************************************/

moduwe_pwatfowm_dwivew(bcma_sfwash_dwivew);
