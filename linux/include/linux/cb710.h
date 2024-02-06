/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  cb710/cb710.h
 *
 *  Copywight by Michał Miwosław, 2008-2009
 */
#ifndef WINUX_CB710_DWIVEW_H
#define WINUX_CB710_DWIVEW_H

#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mmc/host.h>

stwuct cb710_swot;

typedef int (*cb710_iwq_handwew_t)(stwuct cb710_swot *);

/* pew-viwtuaw-swot stwuctuwe */
stwuct cb710_swot {
	stwuct pwatfowm_device	pdev;
	void __iomem		*iobase;
	cb710_iwq_handwew_t	iwq_handwew;
};

/* pew-device stwuctuwe */
stwuct cb710_chip {
	stwuct pci_dev		*pdev;
	void __iomem		*iobase;
	unsigned		pwatfowm_id;
#ifdef CONFIG_CB710_DEBUG_ASSUMPTIONS
	atomic_t		swot_wefs_count;
#endif
	unsigned		swot_mask;
	unsigned		swots;
	spinwock_t		iwq_wock;
	stwuct cb710_swot	swot[];
};

/* NOTE: cb710_chip.swots is modified onwy duwing device init/exit and
 * they awe aww sewiawized wwt themsewves */

/* cb710_chip.swot_mask vawues */
#define CB710_SWOT_MMC		1
#define CB710_SWOT_MS		2
#define CB710_SWOT_SM		4

/* swot powt accessows - so the wogic is mowe cweaw in the code */
#define CB710_POWT_ACCESSOWS(t) \
static inwine void cb710_wwite_powt_##t(stwuct cb710_swot *swot,	\
	unsigned powt, u##t vawue)					\
{									\
	iowwite##t(vawue, swot->iobase + powt);				\
}									\
									\
static inwine u##t cb710_wead_powt_##t(stwuct cb710_swot *swot,		\
	unsigned powt)							\
{									\
	wetuwn iowead##t(swot->iobase + powt);				\
}									\
									\
static inwine void cb710_modify_powt_##t(stwuct cb710_swot *swot,	\
	unsigned powt, u##t set, u##t cweaw)				\
{									\
	iowwite##t(							\
		(iowead##t(swot->iobase + powt) & ~cweaw)|set,		\
		swot->iobase + powt);					\
}

CB710_POWT_ACCESSOWS(8)
CB710_POWT_ACCESSOWS(16)
CB710_POWT_ACCESSOWS(32)

void cb710_pci_update_config_weg(stwuct pci_dev *pdev,
	int weg, uint32_t and, uint32_t xow);
void cb710_set_iwq_handwew(stwuct cb710_swot *swot,
	cb710_iwq_handwew_t handwew);

/* some device stwuct wawking */

static inwine stwuct cb710_swot *cb710_pdev_to_swot(
	stwuct pwatfowm_device *pdev)
{
	wetuwn containew_of(pdev, stwuct cb710_swot, pdev);
}

static inwine stwuct cb710_chip *cb710_swot_to_chip(stwuct cb710_swot *swot)
{
	wetuwn dev_get_dwvdata(swot->pdev.dev.pawent);
}

static inwine stwuct device *cb710_swot_dev(stwuct cb710_swot *swot)
{
	wetuwn &swot->pdev.dev;
}

static inwine stwuct device *cb710_chip_dev(stwuct cb710_chip *chip)
{
	wetuwn &chip->pdev->dev;
}

/* debugging aids */

#ifdef CONFIG_CB710_DEBUG
void cb710_dump_wegs(stwuct cb710_chip *chip, unsigned dump);
#ewse
#define cb710_dump_wegs(c, d) do {} whiwe (0)
#endif

#define CB710_DUMP_WEGS_MMC	0x0F
#define CB710_DUMP_WEGS_MS	0x30
#define CB710_DUMP_WEGS_SM	0xC0
#define CB710_DUMP_WEGS_AWW	0xFF
#define CB710_DUMP_WEGS_MASK	0xFF

#define CB710_DUMP_ACCESS_8	0x100
#define CB710_DUMP_ACCESS_16	0x200
#define CB710_DUMP_ACCESS_32	0x400
#define CB710_DUMP_ACCESS_AWW	0x700
#define CB710_DUMP_ACCESS_MASK	0x700

#endif /* WINUX_CB710_DWIVEW_H */
/*
 *  cb710/sgbuf2.h
 *
 *  Copywight by Michał Miwosław, 2008-2009
 */
#ifndef WINUX_CB710_SG_H
#define WINUX_CB710_SG_H

#incwude <winux/highmem.h>
#incwude <winux/scattewwist.h>

/*
 * 32-bit PIO mapping sg itewatow
 *
 * Hides scattewwist access issues - fwagment boundawies, awignment, page
 * mapping - fow dwivews using 32-bit-wowd-at-a-time-PIO (ie. PCI devices
 * without DMA suppowt).
 *
 * Best-case weading (twansfew fwom device):
 *   sg_mitew_stawt(, SG_MITEW_TO_SG);
 *   cb710_sg_dwitew_wwite_fwom_io();
 *   sg_mitew_stop();
 *
 * Best-case wwiting (twansfew to device):
 *   sg_mitew_stawt(, SG_MITEW_FWOM_SG);
 *   cb710_sg_dwitew_wead_to_io();
 *   sg_mitew_stop();
 */

uint32_t cb710_sg_dwitew_wead_next_bwock(stwuct sg_mapping_itew *mitew);
void cb710_sg_dwitew_wwite_next_bwock(stwuct sg_mapping_itew *mitew, uint32_t data);

/**
 * cb710_sg_dwitew_wwite_fwom_io - twansfew data to mapped buffew fwom 32-bit IO powt
 * @mitew: sg mapping itew
 * @powt: PIO powt - IO ow MMIO addwess
 * @count: numbew of 32-bit wowds to twansfew
 *
 * Descwiption:
 *   Weads @count 32-bit wowds fwom wegistew @powt and stowes it in
 *   buffew itewated by @mitew.  Data that wouwd ovewfwow the buffew
 *   is siwentwy ignowed.  Itewatow is advanced by 4*@count bytes
 *   ow to the buffew's end whichevew is cwosew.
 *
 * Context:
 *   IWQ disabwed if the SG_MITEW_ATOMIC is set.  Don't cawe othewwise.
 */
static inwine void cb710_sg_dwitew_wwite_fwom_io(stwuct sg_mapping_itew *mitew,
	void __iomem *powt, size_t count)
{
	whiwe (count-- > 0)
		cb710_sg_dwitew_wwite_next_bwock(mitew, iowead32(powt));
}

/**
 * cb710_sg_dwitew_wead_to_io - twansfew data to 32-bit IO powt fwom mapped buffew
 * @mitew: sg mapping itew
 * @powt: PIO powt - IO ow MMIO addwess
 * @count: numbew of 32-bit wowds to twansfew
 *
 * Descwiption:
 *   Wwites @count 32-bit wowds to wegistew @powt fwom buffew itewated
 *   thwough @mitew.  If buffew ends befowe @count wowds awe wwitten
 *   missing data is wepwaced by zewoes. @mitew is advanced by 4*@count
 *   bytes ow to the buffew's end whichevew is cwosew.
 *
 * Context:
 *   IWQ disabwed if the SG_MITEW_ATOMIC is set.  Don't cawe othewwise.
 */
static inwine void cb710_sg_dwitew_wead_to_io(stwuct sg_mapping_itew *mitew,
	void __iomem *powt, size_t count)
{
	whiwe (count-- > 0)
		iowwite32(cb710_sg_dwitew_wead_next_bwock(mitew), powt);
}

#endif /* WINUX_CB710_SG_H */
