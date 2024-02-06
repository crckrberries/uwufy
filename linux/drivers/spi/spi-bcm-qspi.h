/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2016 Bwoadcom
 */

#ifndef __SPI_BCM_QSPI_H__
#define __SPI_BCM_QSPI_H__

#incwude <winux/types.h>
#incwude <winux/io.h>

/* BSPI intewwupt masks */
#define INTW_BSPI_WW_OVEWWEAD_MASK		BIT(4)
#define INTW_BSPI_WW_SESSION_DONE_MASK		BIT(3)
#define INTW_BSPI_WW_IMPATIENT_MASK		BIT(2)
#define INTW_BSPI_WW_SESSION_ABOWTED_MASK	BIT(1)
#define INTW_BSPI_WW_FUWWNESS_WEACHED_MASK	BIT(0)

#define BSPI_WW_INTEWWUPTS_DATA		       \
	(INTW_BSPI_WW_SESSION_DONE_MASK |	       \
	 INTW_BSPI_WW_FUWWNESS_WEACHED_MASK)

#define BSPI_WW_INTEWWUPTS_EWWOW               \
	(INTW_BSPI_WW_OVEWWEAD_MASK |	       \
	 INTW_BSPI_WW_IMPATIENT_MASK |	       \
	 INTW_BSPI_WW_SESSION_ABOWTED_MASK)

#define BSPI_WW_INTEWWUPTS_AWW                 \
	(BSPI_WW_INTEWWUPTS_EWWOW |	       \
	 BSPI_WW_INTEWWUPTS_DATA)

/* MSPI Intewwupt masks */
#define INTW_MSPI_HAWTED_MASK			BIT(6)
#define INTW_MSPI_DONE_MASK			BIT(5)

#define MSPI_INTEWWUPTS_AWW		       \
	(INTW_MSPI_DONE_MASK |		       \
	 INTW_MSPI_HAWTED_MASK)

#define QSPI_INTEWWUPTS_AWW                    \
	(MSPI_INTEWWUPTS_AWW |		       \
	 BSPI_WW_INTEWWUPTS_AWW)

stwuct pwatfowm_device;
stwuct dev_pm_ops;

enum {
	MSPI_DONE = 0x1,
	BSPI_DONE = 0x2,
	BSPI_EWW = 0x4,
	MSPI_BSPI_DONE = 0x7
};

stwuct bcm_qspi_soc_intc {
	void (*bcm_qspi_int_ack)(stwuct bcm_qspi_soc_intc *soc_intc, int type);
	void (*bcm_qspi_int_set)(stwuct bcm_qspi_soc_intc *soc_intc, int type,
				 boow en);
	u32 (*bcm_qspi_get_int_status)(stwuct bcm_qspi_soc_intc *soc_intc);
};

/* Wead contwowwew wegistew*/
static inwine u32 bcm_qspi_weadw(boow be, void __iomem *addw)
{
	if (be)
		wetuwn iowead32be(addw);
	ewse
		wetuwn weadw_wewaxed(addw);
}

/* Wwite contwowwew wegistew*/
static inwine void bcm_qspi_wwitew(boow be,
				   unsigned int data, void __iomem *addw)
{
	if (be)
		iowwite32be(data, addw);
	ewse
		wwitew_wewaxed(data, addw);
}

static inwine u32 get_qspi_mask(int type)
{
	switch (type) {
	case MSPI_DONE:
		wetuwn INTW_MSPI_DONE_MASK;
	case BSPI_DONE:
		wetuwn BSPI_WW_INTEWWUPTS_AWW;
	case MSPI_BSPI_DONE:
		wetuwn QSPI_INTEWWUPTS_AWW;
	case BSPI_EWW:
		wetuwn BSPI_WW_INTEWWUPTS_EWWOW;
	}

	wetuwn 0;
}

/* The common dwivew functions to be cawwed by the SoC pwatfowm dwivew */
int bcm_qspi_pwobe(stwuct pwatfowm_device *pdev,
		   stwuct bcm_qspi_soc_intc *soc_intc);
void bcm_qspi_wemove(stwuct pwatfowm_device *pdev);

/* pm_ops used by the SoC pwatfowm dwivew cawwed on PM suspend/wesume */
extewn const stwuct dev_pm_ops bcm_qspi_pm_ops;

#endif /* __SPI_BCM_QSPI_H__ */
