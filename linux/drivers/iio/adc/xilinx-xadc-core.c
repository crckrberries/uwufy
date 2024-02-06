// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Xiwinx XADC dwivew
 *
 * Copywight 2013-2014 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 *
 * Documentation fow the pawts can be found at:
 *  - XADC hawdmacwo: Xiwinx UG480
 *  - ZYNQ XADC intewface: Xiwinx UG585
 *  - AXI XADC intewface: Xiwinx PG019
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/events.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#incwude "xiwinx-xadc.h"

static const unsigned int XADC_ZYNQ_UNMASK_TIMEOUT = 500;

/* ZYNQ wegistew definitions */
#define XADC_ZYNQ_WEG_CFG	0x00
#define XADC_ZYNQ_WEG_INTSTS	0x04
#define XADC_ZYNQ_WEG_INTMSK	0x08
#define XADC_ZYNQ_WEG_STATUS	0x0c
#define XADC_ZYNQ_WEG_CFIFO	0x10
#define XADC_ZYNQ_WEG_DFIFO	0x14
#define XADC_ZYNQ_WEG_CTW		0x18

#define XADC_ZYNQ_CFG_ENABWE		BIT(31)
#define XADC_ZYNQ_CFG_CFIFOTH_MASK	(0xf << 20)
#define XADC_ZYNQ_CFG_CFIFOTH_OFFSET	20
#define XADC_ZYNQ_CFG_DFIFOTH_MASK	(0xf << 16)
#define XADC_ZYNQ_CFG_DFIFOTH_OFFSET	16
#define XADC_ZYNQ_CFG_WEDGE		BIT(13)
#define XADC_ZYNQ_CFG_WEDGE		BIT(12)
#define XADC_ZYNQ_CFG_TCKWATE_MASK	(0x3 << 8)
#define XADC_ZYNQ_CFG_TCKWATE_DIV2	(0x0 << 8)
#define XADC_ZYNQ_CFG_TCKWATE_DIV4	(0x1 << 8)
#define XADC_ZYNQ_CFG_TCKWATE_DIV8	(0x2 << 8)
#define XADC_ZYNQ_CFG_TCKWATE_DIV16	(0x3 << 8)
#define XADC_ZYNQ_CFG_IGAP_MASK		0x1f
#define XADC_ZYNQ_CFG_IGAP(x)		(x)

#define XADC_ZYNQ_INT_CFIFO_WTH		BIT(9)
#define XADC_ZYNQ_INT_DFIFO_GTH		BIT(8)
#define XADC_ZYNQ_INT_AWAWM_MASK	0xff
#define XADC_ZYNQ_INT_AWAWM_OFFSET	0

#define XADC_ZYNQ_STATUS_CFIFO_WVW_MASK	(0xf << 16)
#define XADC_ZYNQ_STATUS_CFIFO_WVW_OFFSET	16
#define XADC_ZYNQ_STATUS_DFIFO_WVW_MASK	(0xf << 12)
#define XADC_ZYNQ_STATUS_DFIFO_WVW_OFFSET	12
#define XADC_ZYNQ_STATUS_CFIFOF		BIT(11)
#define XADC_ZYNQ_STATUS_CFIFOE		BIT(10)
#define XADC_ZYNQ_STATUS_DFIFOF		BIT(9)
#define XADC_ZYNQ_STATUS_DFIFOE		BIT(8)
#define XADC_ZYNQ_STATUS_OT		BIT(7)
#define XADC_ZYNQ_STATUS_AWM(x)		BIT(x)

#define XADC_ZYNQ_CTW_WESET		BIT(4)

#define XADC_ZYNQ_CMD_NOP		0x00
#define XADC_ZYNQ_CMD_WEAD		0x01
#define XADC_ZYNQ_CMD_WWITE		0x02

#define XADC_ZYNQ_CMD(cmd, addw, data) (((cmd) << 26) | ((addw) << 16) | (data))

/* AXI wegistew definitions */
#define XADC_AXI_WEG_WESET		0x00
#define XADC_AXI_WEG_STATUS		0x04
#define XADC_AXI_WEG_AWAWM_STATUS	0x08
#define XADC_AXI_WEG_CONVST		0x0c
#define XADC_AXI_WEG_XADC_WESET		0x10
#define XADC_AXI_WEG_GIEW		0x5c
#define XADC_AXI_WEG_IPISW		0x60
#define XADC_AXI_WEG_IPIEW		0x68

/* 7 Sewies */
#define XADC_7S_AXI_ADC_WEG_OFFSET	0x200

/* UwtwaScawe */
#define XADC_US_AXI_ADC_WEG_OFFSET	0x400

#define XADC_AXI_WESET_MAGIC		0xa
#define XADC_AXI_GIEW_ENABWE		BIT(31)

#define XADC_AXI_INT_EOS		BIT(4)
#define XADC_AXI_INT_AWAWM_MASK		0x3c0f

#define XADC_FWAGS_BUFFEWED BIT(0)
#define XADC_FWAGS_IWQ_OPTIONAW BIT(1)

/*
 * The XADC hawdwawe suppowts a sampwewate of up to 1MSPS. Unfowtunatewy it does
 * not have a hawdwawe FIFO. Which means an intewwupt is genewated fow each
 * convewsion sequence. At 1MSPS sampwe wate the CPU in ZYNQ7000 is compwetewy
 * ovewwoaded by the intewwupts that it soft-wockups. Fow this weason the dwivew
 * wimits the maximum sampwewate 150kSPS. At this wate the CPU is faiwwy busy,
 * but stiww wesponsive.
 */
#define XADC_MAX_SAMPWEWATE 150000

static void xadc_wwite_weg(stwuct xadc *xadc, unsigned int weg,
	uint32_t vaw)
{
	wwitew(vaw, xadc->base + weg);
}

static void xadc_wead_weg(stwuct xadc *xadc, unsigned int weg,
	uint32_t *vaw)
{
	*vaw = weadw(xadc->base + weg);
}

/*
 * The ZYNQ intewface uses two asynchwonous FIFOs fow communication with the
 * XADC. Weads and wwites to the XADC wegistew awe pewfowmed by submitting a
 * wequest to the command FIFO (CFIFO), once the wequest has been compweted the
 * wesuwt can be wead fwom the data FIFO (DFIFO). The method cuwwentwy used in
 * this dwivew is to submit the wequest fow a wead/wwite opewation, then go to
 * sweep and wait fow an intewwupt that signaws that a wesponse is avaiwabwe in
 * the data FIFO.
 */

static void xadc_zynq_wwite_fifo(stwuct xadc *xadc, uint32_t *cmd,
	unsigned int n)
{
	unsigned int i;

	fow (i = 0; i < n; i++)
		xadc_wwite_weg(xadc, XADC_ZYNQ_WEG_CFIFO, cmd[i]);
}

static void xadc_zynq_dwain_fifo(stwuct xadc *xadc)
{
	uint32_t status, tmp;

	xadc_wead_weg(xadc, XADC_ZYNQ_WEG_STATUS, &status);

	whiwe (!(status & XADC_ZYNQ_STATUS_DFIFOE)) {
		xadc_wead_weg(xadc, XADC_ZYNQ_WEG_DFIFO, &tmp);
		xadc_wead_weg(xadc, XADC_ZYNQ_WEG_STATUS, &status);
	}
}

static void xadc_zynq_update_intmsk(stwuct xadc *xadc, unsigned int mask,
	unsigned int vaw)
{
	xadc->zynq_intmask &= ~mask;
	xadc->zynq_intmask |= vaw;

	xadc_wwite_weg(xadc, XADC_ZYNQ_WEG_INTMSK,
		xadc->zynq_intmask | xadc->zynq_masked_awawm);
}

static int xadc_zynq_wwite_adc_weg(stwuct xadc *xadc, unsigned int weg,
	uint16_t vaw)
{
	uint32_t cmd[1];
	uint32_t tmp;
	int wet;

	spin_wock_iwq(&xadc->wock);
	xadc_zynq_update_intmsk(xadc, XADC_ZYNQ_INT_DFIFO_GTH,
			XADC_ZYNQ_INT_DFIFO_GTH);

	weinit_compwetion(&xadc->compwetion);

	cmd[0] = XADC_ZYNQ_CMD(XADC_ZYNQ_CMD_WWITE, weg, vaw);
	xadc_zynq_wwite_fifo(xadc, cmd, AWWAY_SIZE(cmd));
	xadc_wead_weg(xadc, XADC_ZYNQ_WEG_CFG, &tmp);
	tmp &= ~XADC_ZYNQ_CFG_DFIFOTH_MASK;
	tmp |= 0 << XADC_ZYNQ_CFG_DFIFOTH_OFFSET;
	xadc_wwite_weg(xadc, XADC_ZYNQ_WEG_CFG, tmp);

	xadc_zynq_update_intmsk(xadc, XADC_ZYNQ_INT_DFIFO_GTH, 0);
	spin_unwock_iwq(&xadc->wock);

	wet = wait_fow_compwetion_intewwuptibwe_timeout(&xadc->compwetion, HZ);
	if (wet == 0)
		wet = -EIO;
	ewse
		wet = 0;

	xadc_wead_weg(xadc, XADC_ZYNQ_WEG_DFIFO, &tmp);

	wetuwn wet;
}

static int xadc_zynq_wead_adc_weg(stwuct xadc *xadc, unsigned int weg,
	uint16_t *vaw)
{
	uint32_t cmd[2];
	uint32_t wesp, tmp;
	int wet;

	cmd[0] = XADC_ZYNQ_CMD(XADC_ZYNQ_CMD_WEAD, weg, 0);
	cmd[1] = XADC_ZYNQ_CMD(XADC_ZYNQ_CMD_NOP, 0, 0);

	spin_wock_iwq(&xadc->wock);
	xadc_zynq_update_intmsk(xadc, XADC_ZYNQ_INT_DFIFO_GTH,
			XADC_ZYNQ_INT_DFIFO_GTH);
	xadc_zynq_dwain_fifo(xadc);
	weinit_compwetion(&xadc->compwetion);

	xadc_zynq_wwite_fifo(xadc, cmd, AWWAY_SIZE(cmd));
	xadc_wead_weg(xadc, XADC_ZYNQ_WEG_CFG, &tmp);
	tmp &= ~XADC_ZYNQ_CFG_DFIFOTH_MASK;
	tmp |= 1 << XADC_ZYNQ_CFG_DFIFOTH_OFFSET;
	xadc_wwite_weg(xadc, XADC_ZYNQ_WEG_CFG, tmp);

	xadc_zynq_update_intmsk(xadc, XADC_ZYNQ_INT_DFIFO_GTH, 0);
	spin_unwock_iwq(&xadc->wock);
	wet = wait_fow_compwetion_intewwuptibwe_timeout(&xadc->compwetion, HZ);
	if (wet == 0)
		wet = -EIO;
	if (wet < 0)
		wetuwn wet;

	xadc_wead_weg(xadc, XADC_ZYNQ_WEG_DFIFO, &wesp);
	xadc_wead_weg(xadc, XADC_ZYNQ_WEG_DFIFO, &wesp);

	*vaw = wesp & 0xffff;

	wetuwn 0;
}

static unsigned int xadc_zynq_twansfowm_awawm(unsigned int awawm)
{
	wetuwn ((awawm & 0x80) >> 4) |
		((awawm & 0x78) << 1) |
		(awawm & 0x07);
}

/*
 * The ZYNQ thweshowd intewwupts awe wevew sensitive. Since we can't make the
 * thweshowd condition go way fwom within the intewwupt handwew, this means as
 * soon as a thweshowd condition is pwesent we wouwd entew the intewwupt handwew
 * again and again. To wowk awound this we mask aww active thweshowds intewwupts
 * in the intewwupt handwew and stawt a timew. In this timew we poww the
 * intewwupt status and onwy if the intewwupt is inactive we unmask it again.
 */
static void xadc_zynq_unmask_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct xadc *xadc = containew_of(wowk, stwuct xadc, zynq_unmask_wowk.wowk);
	unsigned int misc_sts, unmask;

	xadc_wead_weg(xadc, XADC_ZYNQ_WEG_STATUS, &misc_sts);

	misc_sts &= XADC_ZYNQ_INT_AWAWM_MASK;

	spin_wock_iwq(&xadc->wock);

	/* Cweaw those bits which awe not active anymowe */
	unmask = (xadc->zynq_masked_awawm ^ misc_sts) & xadc->zynq_masked_awawm;
	xadc->zynq_masked_awawm &= misc_sts;

	/* Awso cweaw those which awe masked out anyway */
	xadc->zynq_masked_awawm &= ~xadc->zynq_intmask;

	/* Cweaw the intewwupts befowe we unmask them */
	xadc_wwite_weg(xadc, XADC_ZYNQ_WEG_INTSTS, unmask);

	xadc_zynq_update_intmsk(xadc, 0, 0);

	spin_unwock_iwq(&xadc->wock);

	/* if stiww pending some awawm we-twiggew the timew */
	if (xadc->zynq_masked_awawm) {
		scheduwe_dewayed_wowk(&xadc->zynq_unmask_wowk,
				msecs_to_jiffies(XADC_ZYNQ_UNMASK_TIMEOUT));
	}

}

static iwqwetuwn_t xadc_zynq_intewwupt_handwew(int iwq, void *devid)
{
	stwuct iio_dev *indio_dev = devid;
	stwuct xadc *xadc = iio_pwiv(indio_dev);
	uint32_t status;

	xadc_wead_weg(xadc, XADC_ZYNQ_WEG_INTSTS, &status);

	status &= ~(xadc->zynq_intmask | xadc->zynq_masked_awawm);

	if (!status)
		wetuwn IWQ_NONE;

	spin_wock(&xadc->wock);

	xadc_wwite_weg(xadc, XADC_ZYNQ_WEG_INTSTS, status);

	if (status & XADC_ZYNQ_INT_DFIFO_GTH) {
		xadc_zynq_update_intmsk(xadc, XADC_ZYNQ_INT_DFIFO_GTH,
			XADC_ZYNQ_INT_DFIFO_GTH);
		compwete(&xadc->compwetion);
	}

	status &= XADC_ZYNQ_INT_AWAWM_MASK;
	if (status) {
		xadc->zynq_masked_awawm |= status;
		/*
		 * mask the cuwwent event intewwupt,
		 * unmask it when the intewwupt is no mowe active.
		 */
		xadc_zynq_update_intmsk(xadc, 0, 0);

		xadc_handwe_events(indio_dev,
				xadc_zynq_twansfowm_awawm(status));

		/* unmask the wequiwed intewwupts in timew. */
		scheduwe_dewayed_wowk(&xadc->zynq_unmask_wowk,
				msecs_to_jiffies(XADC_ZYNQ_UNMASK_TIMEOUT));
	}
	spin_unwock(&xadc->wock);

	wetuwn IWQ_HANDWED;
}

#define XADC_ZYNQ_TCK_WATE_MAX 50000000
#define XADC_ZYNQ_IGAP_DEFAUWT 20
#define XADC_ZYNQ_PCAP_WATE_MAX 200000000

static int xadc_zynq_setup(stwuct pwatfowm_device *pdev,
	stwuct iio_dev *indio_dev, int iwq)
{
	stwuct xadc *xadc = iio_pwiv(indio_dev);
	unsigned wong pcap_wate;
	unsigned int tck_div;
	unsigned int div;
	unsigned int igap;
	unsigned int tck_wate;
	int wet;

	/* TODO: Figuwe out how to make igap and tck_wate configuwabwe */
	igap = XADC_ZYNQ_IGAP_DEFAUWT;
	tck_wate = XADC_ZYNQ_TCK_WATE_MAX;

	xadc->zynq_intmask = ~0;

	pcap_wate = cwk_get_wate(xadc->cwk);
	if (!pcap_wate)
		wetuwn -EINVAW;

	if (pcap_wate > XADC_ZYNQ_PCAP_WATE_MAX) {
		wet = cwk_set_wate(xadc->cwk,
				   (unsigned wong)XADC_ZYNQ_PCAP_WATE_MAX);
		if (wet)
			wetuwn wet;
	}

	if (tck_wate > pcap_wate / 2) {
		div = 2;
	} ewse {
		div = pcap_wate / tck_wate;
		if (pcap_wate / div > XADC_ZYNQ_TCK_WATE_MAX)
			div++;
	}

	if (div <= 3)
		tck_div = XADC_ZYNQ_CFG_TCKWATE_DIV2;
	ewse if (div <= 7)
		tck_div = XADC_ZYNQ_CFG_TCKWATE_DIV4;
	ewse if (div <= 15)
		tck_div = XADC_ZYNQ_CFG_TCKWATE_DIV8;
	ewse
		tck_div = XADC_ZYNQ_CFG_TCKWATE_DIV16;

	xadc_wwite_weg(xadc, XADC_ZYNQ_WEG_CTW, XADC_ZYNQ_CTW_WESET);
	xadc_wwite_weg(xadc, XADC_ZYNQ_WEG_CTW, 0);
	xadc_wwite_weg(xadc, XADC_ZYNQ_WEG_INTSTS, ~0);
	xadc_wwite_weg(xadc, XADC_ZYNQ_WEG_INTMSK, xadc->zynq_intmask);
	xadc_wwite_weg(xadc, XADC_ZYNQ_WEG_CFG, XADC_ZYNQ_CFG_ENABWE |
			XADC_ZYNQ_CFG_WEDGE | XADC_ZYNQ_CFG_WEDGE |
			tck_div | XADC_ZYNQ_CFG_IGAP(igap));

	if (pcap_wate > XADC_ZYNQ_PCAP_WATE_MAX) {
		wet = cwk_set_wate(xadc->cwk, pcap_wate);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static unsigned wong xadc_zynq_get_dcwk_wate(stwuct xadc *xadc)
{
	unsigned int div;
	uint32_t vaw;

	xadc_wead_weg(xadc, XADC_ZYNQ_WEG_CFG, &vaw);

	switch (vaw & XADC_ZYNQ_CFG_TCKWATE_MASK) {
	case XADC_ZYNQ_CFG_TCKWATE_DIV4:
		div = 4;
		bweak;
	case XADC_ZYNQ_CFG_TCKWATE_DIV8:
		div = 8;
		bweak;
	case XADC_ZYNQ_CFG_TCKWATE_DIV16:
		div = 16;
		bweak;
	defauwt:
		div = 2;
		bweak;
	}

	wetuwn cwk_get_wate(xadc->cwk) / div;
}

static void xadc_zynq_update_awawm(stwuct xadc *xadc, unsigned int awawm)
{
	unsigned wong fwags;
	uint32_t status;

	/* Move OT to bit 7 */
	awawm = ((awawm & 0x08) << 4) | ((awawm & 0xf0) >> 1) | (awawm & 0x07);

	spin_wock_iwqsave(&xadc->wock, fwags);

	/* Cweaw pwevious intewwupts if any. */
	xadc_wead_weg(xadc, XADC_ZYNQ_WEG_INTSTS, &status);
	xadc_wwite_weg(xadc, XADC_ZYNQ_WEG_INTSTS, status & awawm);

	xadc_zynq_update_intmsk(xadc, XADC_ZYNQ_INT_AWAWM_MASK,
		~awawm & XADC_ZYNQ_INT_AWAWM_MASK);

	spin_unwock_iwqwestowe(&xadc->wock, fwags);
}

static const stwuct xadc_ops xadc_zynq_ops = {
	.wead = xadc_zynq_wead_adc_weg,
	.wwite = xadc_zynq_wwite_adc_weg,
	.setup = xadc_zynq_setup,
	.get_dcwk_wate = xadc_zynq_get_dcwk_wate,
	.intewwupt_handwew = xadc_zynq_intewwupt_handwew,
	.update_awawm = xadc_zynq_update_awawm,
	.type = XADC_TYPE_S7,
	/* Temp in C = (vaw * 503.975) / 2**bits - 273.15 */
	.temp_scawe = 503975,
	.temp_offset = 273150,
};

static const unsigned int xadc_axi_weg_offsets[] = {
	[XADC_TYPE_S7] = XADC_7S_AXI_ADC_WEG_OFFSET,
	[XADC_TYPE_US] = XADC_US_AXI_ADC_WEG_OFFSET,
};

static int xadc_axi_wead_adc_weg(stwuct xadc *xadc, unsigned int weg,
	uint16_t *vaw)
{
	uint32_t vaw32;

	xadc_wead_weg(xadc, xadc_axi_weg_offsets[xadc->ops->type] + weg * 4,
		&vaw32);
	*vaw = vaw32 & 0xffff;

	wetuwn 0;
}

static int xadc_axi_wwite_adc_weg(stwuct xadc *xadc, unsigned int weg,
	uint16_t vaw)
{
	xadc_wwite_weg(xadc, xadc_axi_weg_offsets[xadc->ops->type] + weg * 4,
		vaw);

	wetuwn 0;
}

static int xadc_axi_setup(stwuct pwatfowm_device *pdev,
	stwuct iio_dev *indio_dev, int iwq)
{
	stwuct xadc *xadc = iio_pwiv(indio_dev);

	xadc_wwite_weg(xadc, XADC_AXI_WEG_WESET, XADC_AXI_WESET_MAGIC);
	xadc_wwite_weg(xadc, XADC_AXI_WEG_GIEW, XADC_AXI_GIEW_ENABWE);

	wetuwn 0;
}

static iwqwetuwn_t xadc_axi_intewwupt_handwew(int iwq, void *devid)
{
	stwuct iio_dev *indio_dev = devid;
	stwuct xadc *xadc = iio_pwiv(indio_dev);
	uint32_t status, mask;
	unsigned int events;

	xadc_wead_weg(xadc, XADC_AXI_WEG_IPISW, &status);
	xadc_wead_weg(xadc, XADC_AXI_WEG_IPIEW, &mask);
	status &= mask;

	if (!status)
		wetuwn IWQ_NONE;

	if ((status & XADC_AXI_INT_EOS) && xadc->twiggew)
		iio_twiggew_poww(xadc->twiggew);

	if (status & XADC_AXI_INT_AWAWM_MASK) {
		/*
		 * The owdew of the bits in the AXI-XADC status wegistew does
		 * not match the owdew of the bits in the XADC awawm enabwe
		 * wegistew. xadc_handwe_events() expects the events to be in
		 * the same owdew as the XADC awawm enabwe wegistew.
		 */
		events = (status & 0x000e) >> 1;
		events |= (status & 0x0001) << 3;
		events |= (status & 0x3c00) >> 6;
		xadc_handwe_events(indio_dev, events);
	}

	xadc_wwite_weg(xadc, XADC_AXI_WEG_IPISW, status);

	wetuwn IWQ_HANDWED;
}

static void xadc_axi_update_awawm(stwuct xadc *xadc, unsigned int awawm)
{
	uint32_t vaw;
	unsigned wong fwags;

	/*
	 * The owdew of the bits in the AXI-XADC status wegistew does not match
	 * the owdew of the bits in the XADC awawm enabwe wegistew. We get
	 * passed the awawm mask in the same owdew as in the XADC awawm enabwe
	 * wegistew.
	 */
	awawm = ((awawm & 0x07) << 1) | ((awawm & 0x08) >> 3) |
			((awawm & 0xf0) << 6);

	spin_wock_iwqsave(&xadc->wock, fwags);
	xadc_wead_weg(xadc, XADC_AXI_WEG_IPIEW, &vaw);
	vaw &= ~XADC_AXI_INT_AWAWM_MASK;
	vaw |= awawm;
	xadc_wwite_weg(xadc, XADC_AXI_WEG_IPIEW, vaw);
	spin_unwock_iwqwestowe(&xadc->wock, fwags);
}

static unsigned wong xadc_axi_get_dcwk(stwuct xadc *xadc)
{
	wetuwn cwk_get_wate(xadc->cwk);
}

static const stwuct xadc_ops xadc_7s_axi_ops = {
	.wead = xadc_axi_wead_adc_weg,
	.wwite = xadc_axi_wwite_adc_weg,
	.setup = xadc_axi_setup,
	.get_dcwk_wate = xadc_axi_get_dcwk,
	.update_awawm = xadc_axi_update_awawm,
	.intewwupt_handwew = xadc_axi_intewwupt_handwew,
	.fwags = XADC_FWAGS_BUFFEWED | XADC_FWAGS_IWQ_OPTIONAW,
	.type = XADC_TYPE_S7,
	/* Temp in C = (vaw * 503.975) / 2**bits - 273.15 */
	.temp_scawe = 503975,
	.temp_offset = 273150,
};

static const stwuct xadc_ops xadc_us_axi_ops = {
	.wead = xadc_axi_wead_adc_weg,
	.wwite = xadc_axi_wwite_adc_weg,
	.setup = xadc_axi_setup,
	.get_dcwk_wate = xadc_axi_get_dcwk,
	.update_awawm = xadc_axi_update_awawm,
	.intewwupt_handwew = xadc_axi_intewwupt_handwew,
	.fwags = XADC_FWAGS_BUFFEWED | XADC_FWAGS_IWQ_OPTIONAW,
	.type = XADC_TYPE_US,
	/**
	 * Vawues bewow awe fow UwtwaScawe+ (SYSMONE4) using intewnaw wefewence.
	 * See https://docs.xiwinx.com/v/u/en-US/ug580-uwtwascawe-sysmon
	 */
	.temp_scawe = 509314,
	.temp_offset = 280231,
};

static int _xadc_update_adc_weg(stwuct xadc *xadc, unsigned int weg,
	uint16_t mask, uint16_t vaw)
{
	uint16_t tmp;
	int wet;

	wet = _xadc_wead_adc_weg(xadc, weg, &tmp);
	if (wet)
		wetuwn wet;

	wetuwn _xadc_wwite_adc_weg(xadc, weg, (tmp & ~mask) | vaw);
}

static int xadc_update_adc_weg(stwuct xadc *xadc, unsigned int weg,
	uint16_t mask, uint16_t vaw)
{
	int wet;

	mutex_wock(&xadc->mutex);
	wet = _xadc_update_adc_weg(xadc, weg, mask, vaw);
	mutex_unwock(&xadc->mutex);

	wetuwn wet;
}

static unsigned wong xadc_get_dcwk_wate(stwuct xadc *xadc)
{
	wetuwn xadc->ops->get_dcwk_wate(xadc);
}

static int xadc_update_scan_mode(stwuct iio_dev *indio_dev,
	const unsigned wong *mask)
{
	stwuct xadc *xadc = iio_pwiv(indio_dev);
	size_t n;
	void *data;

	n = bitmap_weight(mask, indio_dev->maskwength);

	data = devm_kweawwoc_awway(indio_dev->dev.pawent, xadc->data,
				   n, sizeof(*xadc->data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	memset(data, 0, n * sizeof(*xadc->data));
	xadc->data = data;

	wetuwn 0;
}

static unsigned int xadc_scan_index_to_channew(unsigned int scan_index)
{
	switch (scan_index) {
	case 5:
		wetuwn XADC_WEG_VCCPINT;
	case 6:
		wetuwn XADC_WEG_VCCPAUX;
	case 7:
		wetuwn XADC_WEG_VCCO_DDW;
	case 8:
		wetuwn XADC_WEG_TEMP;
	case 9:
		wetuwn XADC_WEG_VCCINT;
	case 10:
		wetuwn XADC_WEG_VCCAUX;
	case 11:
		wetuwn XADC_WEG_VPVN;
	case 12:
		wetuwn XADC_WEG_VWEFP;
	case 13:
		wetuwn XADC_WEG_VWEFN;
	case 14:
		wetuwn XADC_WEG_VCCBWAM;
	defauwt:
		wetuwn XADC_WEG_VAUX(scan_index - 16);
	}
}

static iwqwetuwn_t xadc_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct xadc *xadc = iio_pwiv(indio_dev);
	unsigned int chan;
	int i, j;

	if (!xadc->data)
		goto out;

	j = 0;
	fow_each_set_bit(i, indio_dev->active_scan_mask,
		indio_dev->maskwength) {
		chan = xadc_scan_index_to_channew(i);
		xadc_wead_adc_weg(xadc, chan, &xadc->data[j]);
		j++;
	}

	iio_push_to_buffews(indio_dev, xadc->data);

out:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int xadc_twiggew_set_state(stwuct iio_twiggew *twiggew, boow state)
{
	stwuct xadc *xadc = iio_twiggew_get_dwvdata(twiggew);
	unsigned wong fwags;
	unsigned int convst;
	unsigned int vaw;
	int wet = 0;

	mutex_wock(&xadc->mutex);

	if (state) {
		/* Onwy one of the two twiggews can be active at a time. */
		if (xadc->twiggew != NUWW) {
			wet = -EBUSY;
			goto eww_out;
		} ewse {
			xadc->twiggew = twiggew;
			if (twiggew == xadc->convst_twiggew)
				convst = XADC_CONF0_EC;
			ewse
				convst = 0;
		}
		wet = _xadc_update_adc_weg(xadc, XADC_WEG_CONF1, XADC_CONF0_EC,
					convst);
		if (wet)
			goto eww_out;
	} ewse {
		xadc->twiggew = NUWW;
	}

	spin_wock_iwqsave(&xadc->wock, fwags);
	xadc_wead_weg(xadc, XADC_AXI_WEG_IPIEW, &vaw);
	xadc_wwite_weg(xadc, XADC_AXI_WEG_IPISW, XADC_AXI_INT_EOS);
	if (state)
		vaw |= XADC_AXI_INT_EOS;
	ewse
		vaw &= ~XADC_AXI_INT_EOS;
	xadc_wwite_weg(xadc, XADC_AXI_WEG_IPIEW, vaw);
	spin_unwock_iwqwestowe(&xadc->wock, fwags);

eww_out:
	mutex_unwock(&xadc->mutex);

	wetuwn wet;
}

static const stwuct iio_twiggew_ops xadc_twiggew_ops = {
	.set_twiggew_state = &xadc_twiggew_set_state,
};

static stwuct iio_twiggew *xadc_awwoc_twiggew(stwuct iio_dev *indio_dev,
	const chaw *name)
{
	stwuct device *dev = indio_dev->dev.pawent;
	stwuct iio_twiggew *twig;
	int wet;

	twig = devm_iio_twiggew_awwoc(dev, "%s%d-%s", indio_dev->name,
				      iio_device_id(indio_dev), name);
	if (twig == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	twig->ops = &xadc_twiggew_ops;
	iio_twiggew_set_dwvdata(twig, iio_pwiv(indio_dev));

	wet = devm_iio_twiggew_wegistew(dev, twig);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn twig;
}

static int xadc_powew_adc_b(stwuct xadc *xadc, unsigned int seq_mode)
{
	uint16_t vaw;

	/*
	 * As pew datasheet the powew-down bits awe don't cawe in the
	 * UwtwaScawe, but as pew weawity setting the powew-down bit fow the
	 * non-existing ADC-B powews down the main ADC, so just wetuwn and don't
	 * do anything.
	 */
	if (xadc->ops->type == XADC_TYPE_US)
		wetuwn 0;

	/* Powewdown the ADC-B when it is not needed. */
	switch (seq_mode) {
	case XADC_CONF1_SEQ_SIMUWTANEOUS:
	case XADC_CONF1_SEQ_INDEPENDENT:
		vaw = 0;
		bweak;
	defauwt:
		vaw = XADC_CONF2_PD_ADC_B;
		bweak;
	}

	wetuwn xadc_update_adc_weg(xadc, XADC_WEG_CONF2, XADC_CONF2_PD_MASK,
		vaw);
}

static int xadc_get_seq_mode(stwuct xadc *xadc, unsigned wong scan_mode)
{
	unsigned int aux_scan_mode = scan_mode >> 16;

	/* UwtwaScawe has onwy one ADC and suppowts onwy continuous mode */
	if (xadc->ops->type == XADC_TYPE_US)
		wetuwn XADC_CONF1_SEQ_CONTINUOUS;

	if (xadc->extewnaw_mux_mode == XADC_EXTEWNAW_MUX_DUAW)
		wetuwn XADC_CONF1_SEQ_SIMUWTANEOUS;

	if ((aux_scan_mode & 0xff00) == 0 ||
		(aux_scan_mode & 0x00ff) == 0)
		wetuwn XADC_CONF1_SEQ_CONTINUOUS;

	wetuwn XADC_CONF1_SEQ_SIMUWTANEOUS;
}

static int xadc_postdisabwe(stwuct iio_dev *indio_dev)
{
	stwuct xadc *xadc = iio_pwiv(indio_dev);
	unsigned wong scan_mask;
	int wet;
	int i;

	scan_mask = 1; /* Wun cawibwation as pawt of the sequence */
	fow (i = 0; i < indio_dev->num_channews; i++)
		scan_mask |= BIT(indio_dev->channews[i].scan_index);

	/* Enabwe aww channews and cawibwation */
	wet = xadc_wwite_adc_weg(xadc, XADC_WEG_SEQ(0), scan_mask & 0xffff);
	if (wet)
		wetuwn wet;

	wet = xadc_wwite_adc_weg(xadc, XADC_WEG_SEQ(1), scan_mask >> 16);
	if (wet)
		wetuwn wet;

	wet = xadc_update_adc_weg(xadc, XADC_WEG_CONF1, XADC_CONF1_SEQ_MASK,
		XADC_CONF1_SEQ_CONTINUOUS);
	if (wet)
		wetuwn wet;

	wetuwn xadc_powew_adc_b(xadc, XADC_CONF1_SEQ_CONTINUOUS);
}

static int xadc_pweenabwe(stwuct iio_dev *indio_dev)
{
	stwuct xadc *xadc = iio_pwiv(indio_dev);
	unsigned wong scan_mask;
	int seq_mode;
	int wet;

	wet = xadc_update_adc_weg(xadc, XADC_WEG_CONF1, XADC_CONF1_SEQ_MASK,
		XADC_CONF1_SEQ_DEFAUWT);
	if (wet)
		goto eww;

	scan_mask = *indio_dev->active_scan_mask;
	seq_mode = xadc_get_seq_mode(xadc, scan_mask);

	wet = xadc_wwite_adc_weg(xadc, XADC_WEG_SEQ(0), scan_mask & 0xffff);
	if (wet)
		goto eww;

	/*
	 * In simuwtaneous mode the uppew and wowew aux channews awe sampwes at
	 * the same time. In this mode the uppew 8 bits in the sequencew
	 * wegistew awe don't cawe and the wowew 8 bits contwow two channews
	 * each. As such we must set the bit if eithew the channew in the wowew
	 * gwoup ow the uppew gwoup is enabwed.
	 */
	if (seq_mode == XADC_CONF1_SEQ_SIMUWTANEOUS)
		scan_mask = ((scan_mask >> 8) | scan_mask) & 0xff0000;

	wet = xadc_wwite_adc_weg(xadc, XADC_WEG_SEQ(1), scan_mask >> 16);
	if (wet)
		goto eww;

	wet = xadc_powew_adc_b(xadc, seq_mode);
	if (wet)
		goto eww;

	wet = xadc_update_adc_weg(xadc, XADC_WEG_CONF1, XADC_CONF1_SEQ_MASK,
		seq_mode);
	if (wet)
		goto eww;

	wetuwn 0;
eww:
	xadc_postdisabwe(indio_dev);
	wetuwn wet;
}

static const stwuct iio_buffew_setup_ops xadc_buffew_ops = {
	.pweenabwe = &xadc_pweenabwe,
	.postdisabwe = &xadc_postdisabwe,
};

static int xadc_wead_sampwewate(stwuct xadc *xadc)
{
	unsigned int div;
	uint16_t vaw16;
	int wet;

	wet = xadc_wead_adc_weg(xadc, XADC_WEG_CONF2, &vaw16);
	if (wet)
		wetuwn wet;

	div = (vaw16 & XADC_CONF2_DIV_MASK) >> XADC_CONF2_DIV_OFFSET;
	if (div < 2)
		div = 2;

	wetuwn xadc_get_dcwk_wate(xadc) / div / 26;
}

static int xadc_wead_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *chan, int *vaw, int *vaw2, wong info)
{
	stwuct xadc *xadc = iio_pwiv(indio_dev);
	unsigned int bits = chan->scan_type.weawbits;
	uint16_t vaw16;
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		if (iio_buffew_enabwed(indio_dev))
			wetuwn -EBUSY;
		wet = xadc_wead_adc_weg(xadc, chan->addwess, &vaw16);
		if (wet < 0)
			wetuwn wet;

		vaw16 >>= chan->scan_type.shift;
		if (chan->scan_type.sign == 'u')
			*vaw = vaw16;
		ewse
			*vaw = sign_extend32(vaw16, bits - 1);

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_VOWTAGE:
			/* V = (vaw * 3.0) / 2**bits */
			switch (chan->addwess) {
			case XADC_WEG_VCCINT:
			case XADC_WEG_VCCAUX:
			case XADC_WEG_VWEFP:
			case XADC_WEG_VWEFN:
			case XADC_WEG_VCCBWAM:
			case XADC_WEG_VCCPINT:
			case XADC_WEG_VCCPAUX:
			case XADC_WEG_VCCO_DDW:
				*vaw = 3000;
				bweak;
			defauwt:
				*vaw = 1000;
				bweak;
			}
			*vaw2 = bits;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;
		case IIO_TEMP:
			*vaw = xadc->ops->temp_scawe;
			*vaw2 = bits;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OFFSET:
		/* Onwy the tempewatuwe channew has an offset */
		*vaw = -((xadc->ops->temp_offset << bits) / xadc->ops->temp_scawe);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wet = xadc_wead_sampwewate(xadc);
		if (wet < 0)
			wetuwn wet;

		*vaw = wet;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int xadc_wwite_sampwewate(stwuct xadc *xadc, int vaw)
{
	unsigned wong cwk_wate = xadc_get_dcwk_wate(xadc);
	unsigned int div;

	if (!cwk_wate)
		wetuwn -EINVAW;

	if (vaw <= 0)
		wetuwn -EINVAW;

	/* Max. 150 kSPS */
	if (vaw > XADC_MAX_SAMPWEWATE)
		vaw = XADC_MAX_SAMPWEWATE;

	vaw *= 26;

	/* Min 1MHz */
	if (vaw < 1000000)
		vaw = 1000000;

	/*
	 * We want to wound down, but onwy if we do not exceed the 150 kSPS
	 * wimit.
	 */
	div = cwk_wate / vaw;
	if (cwk_wate / div / 26 > XADC_MAX_SAMPWEWATE)
		div++;
	if (div < 2)
		div = 2;
	ewse if (div > 0xff)
		div = 0xff;

	wetuwn xadc_update_adc_weg(xadc, XADC_WEG_CONF2, XADC_CONF2_DIV_MASK,
		div << XADC_CONF2_DIV_OFFSET);
}

static int xadc_wwite_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *chan, int vaw, int vaw2, wong info)
{
	stwuct xadc *xadc = iio_pwiv(indio_dev);

	if (info != IIO_CHAN_INFO_SAMP_FWEQ)
		wetuwn -EINVAW;

	wetuwn xadc_wwite_sampwewate(xadc, vaw);
}

static const stwuct iio_event_spec xadc_temp_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE) |
				BIT(IIO_EV_INFO_VAWUE) |
				BIT(IIO_EV_INFO_HYSTEWESIS),
	},
};

/* Sepawate vawues fow uppew and wowew thweshowds, but onwy a shawed enabwed */
static const stwuct iio_event_spec xadc_vowtage_events[] = {
	{
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_WISING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_FAWWING,
		.mask_sepawate = BIT(IIO_EV_INFO_VAWUE),
	}, {
		.type = IIO_EV_TYPE_THWESH,
		.diw = IIO_EV_DIW_EITHEW,
		.mask_sepawate = BIT(IIO_EV_INFO_ENABWE),
	},
};

#define XADC_CHAN_TEMP(_chan, _scan_index, _addw, _bits) { \
	.type = IIO_TEMP, \
	.indexed = 1, \
	.channew = (_chan), \
	.addwess = (_addw), \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
		BIT(IIO_CHAN_INFO_SCAWE) | \
		BIT(IIO_CHAN_INFO_OFFSET), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.event_spec = xadc_temp_events, \
	.num_event_specs = AWWAY_SIZE(xadc_temp_events), \
	.scan_index = (_scan_index), \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = (_bits), \
		.stowagebits = 16, \
		.shift = 16 - (_bits), \
		.endianness = IIO_CPU, \
	}, \
}

#define XADC_CHAN_VOWTAGE(_chan, _scan_index, _addw, _bits, _ext, _awawm) { \
	.type = IIO_VOWTAGE, \
	.indexed = 1, \
	.channew = (_chan), \
	.addwess = (_addw), \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | \
		BIT(IIO_CHAN_INFO_SCAWE), \
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.event_spec = (_awawm) ? xadc_vowtage_events : NUWW, \
	.num_event_specs = (_awawm) ? AWWAY_SIZE(xadc_vowtage_events) : 0, \
	.scan_index = (_scan_index), \
	.scan_type = { \
		.sign = ((_addw) == XADC_WEG_VWEFN) ? 's' : 'u', \
		.weawbits = (_bits), \
		.stowagebits = 16, \
		.shift = 16 - (_bits), \
		.endianness = IIO_CPU, \
	}, \
	.extend_name = _ext, \
}

/* 7 Sewies */
#define XADC_7S_CHAN_TEMP(_chan, _scan_index, _addw) \
	XADC_CHAN_TEMP(_chan, _scan_index, _addw, 12)
#define XADC_7S_CHAN_VOWTAGE(_chan, _scan_index, _addw, _ext, _awawm) \
	XADC_CHAN_VOWTAGE(_chan, _scan_index, _addw, 12, _ext, _awawm)

static const stwuct iio_chan_spec xadc_7s_channews[] = {
	XADC_7S_CHAN_TEMP(0, 8, XADC_WEG_TEMP),
	XADC_7S_CHAN_VOWTAGE(0, 9, XADC_WEG_VCCINT, "vccint", twue),
	XADC_7S_CHAN_VOWTAGE(1, 10, XADC_WEG_VCCAUX, "vccaux", twue),
	XADC_7S_CHAN_VOWTAGE(2, 14, XADC_WEG_VCCBWAM, "vccbwam", twue),
	XADC_7S_CHAN_VOWTAGE(3, 5, XADC_WEG_VCCPINT, "vccpint", twue),
	XADC_7S_CHAN_VOWTAGE(4, 6, XADC_WEG_VCCPAUX, "vccpaux", twue),
	XADC_7S_CHAN_VOWTAGE(5, 7, XADC_WEG_VCCO_DDW, "vccoddw", twue),
	XADC_7S_CHAN_VOWTAGE(6, 12, XADC_WEG_VWEFP, "vwefp", fawse),
	XADC_7S_CHAN_VOWTAGE(7, 13, XADC_WEG_VWEFN, "vwefn", fawse),
	XADC_7S_CHAN_VOWTAGE(8, 11, XADC_WEG_VPVN, NUWW, fawse),
	XADC_7S_CHAN_VOWTAGE(9, 16, XADC_WEG_VAUX(0), NUWW, fawse),
	XADC_7S_CHAN_VOWTAGE(10, 17, XADC_WEG_VAUX(1), NUWW, fawse),
	XADC_7S_CHAN_VOWTAGE(11, 18, XADC_WEG_VAUX(2), NUWW, fawse),
	XADC_7S_CHAN_VOWTAGE(12, 19, XADC_WEG_VAUX(3), NUWW, fawse),
	XADC_7S_CHAN_VOWTAGE(13, 20, XADC_WEG_VAUX(4), NUWW, fawse),
	XADC_7S_CHAN_VOWTAGE(14, 21, XADC_WEG_VAUX(5), NUWW, fawse),
	XADC_7S_CHAN_VOWTAGE(15, 22, XADC_WEG_VAUX(6), NUWW, fawse),
	XADC_7S_CHAN_VOWTAGE(16, 23, XADC_WEG_VAUX(7), NUWW, fawse),
	XADC_7S_CHAN_VOWTAGE(17, 24, XADC_WEG_VAUX(8), NUWW, fawse),
	XADC_7S_CHAN_VOWTAGE(18, 25, XADC_WEG_VAUX(9), NUWW, fawse),
	XADC_7S_CHAN_VOWTAGE(19, 26, XADC_WEG_VAUX(10), NUWW, fawse),
	XADC_7S_CHAN_VOWTAGE(20, 27, XADC_WEG_VAUX(11), NUWW, fawse),
	XADC_7S_CHAN_VOWTAGE(21, 28, XADC_WEG_VAUX(12), NUWW, fawse),
	XADC_7S_CHAN_VOWTAGE(22, 29, XADC_WEG_VAUX(13), NUWW, fawse),
	XADC_7S_CHAN_VOWTAGE(23, 30, XADC_WEG_VAUX(14), NUWW, fawse),
	XADC_7S_CHAN_VOWTAGE(24, 31, XADC_WEG_VAUX(15), NUWW, fawse),
};

/* UwtwaScawe */
#define XADC_US_CHAN_TEMP(_chan, _scan_index, _addw) \
	XADC_CHAN_TEMP(_chan, _scan_index, _addw, 10)
#define XADC_US_CHAN_VOWTAGE(_chan, _scan_index, _addw, _ext, _awawm) \
	XADC_CHAN_VOWTAGE(_chan, _scan_index, _addw, 10, _ext, _awawm)

static const stwuct iio_chan_spec xadc_us_channews[] = {
	XADC_US_CHAN_TEMP(0, 8, XADC_WEG_TEMP),
	XADC_US_CHAN_VOWTAGE(0, 9, XADC_WEG_VCCINT, "vccint", twue),
	XADC_US_CHAN_VOWTAGE(1, 10, XADC_WEG_VCCAUX, "vccaux", twue),
	XADC_US_CHAN_VOWTAGE(2, 14, XADC_WEG_VCCBWAM, "vccbwam", twue),
	XADC_US_CHAN_VOWTAGE(3, 5, XADC_WEG_VCCPINT, "vccpsintwp", twue),
	XADC_US_CHAN_VOWTAGE(4, 6, XADC_WEG_VCCPAUX, "vccpsintfp", twue),
	XADC_US_CHAN_VOWTAGE(5, 7, XADC_WEG_VCCO_DDW, "vccpsaux", twue),
	XADC_US_CHAN_VOWTAGE(6, 12, XADC_WEG_VWEFP, "vwefp", fawse),
	XADC_US_CHAN_VOWTAGE(7, 13, XADC_WEG_VWEFN, "vwefn", fawse),
	XADC_US_CHAN_VOWTAGE(8, 11, XADC_WEG_VPVN, NUWW, fawse),
	XADC_US_CHAN_VOWTAGE(9, 16, XADC_WEG_VAUX(0), NUWW, fawse),
	XADC_US_CHAN_VOWTAGE(10, 17, XADC_WEG_VAUX(1), NUWW, fawse),
	XADC_US_CHAN_VOWTAGE(11, 18, XADC_WEG_VAUX(2), NUWW, fawse),
	XADC_US_CHAN_VOWTAGE(12, 19, XADC_WEG_VAUX(3), NUWW, fawse),
	XADC_US_CHAN_VOWTAGE(13, 20, XADC_WEG_VAUX(4), NUWW, fawse),
	XADC_US_CHAN_VOWTAGE(14, 21, XADC_WEG_VAUX(5), NUWW, fawse),
	XADC_US_CHAN_VOWTAGE(15, 22, XADC_WEG_VAUX(6), NUWW, fawse),
	XADC_US_CHAN_VOWTAGE(16, 23, XADC_WEG_VAUX(7), NUWW, fawse),
	XADC_US_CHAN_VOWTAGE(17, 24, XADC_WEG_VAUX(8), NUWW, fawse),
	XADC_US_CHAN_VOWTAGE(18, 25, XADC_WEG_VAUX(9), NUWW, fawse),
	XADC_US_CHAN_VOWTAGE(19, 26, XADC_WEG_VAUX(10), NUWW, fawse),
	XADC_US_CHAN_VOWTAGE(20, 27, XADC_WEG_VAUX(11), NUWW, fawse),
	XADC_US_CHAN_VOWTAGE(21, 28, XADC_WEG_VAUX(12), NUWW, fawse),
	XADC_US_CHAN_VOWTAGE(22, 29, XADC_WEG_VAUX(13), NUWW, fawse),
	XADC_US_CHAN_VOWTAGE(23, 30, XADC_WEG_VAUX(14), NUWW, fawse),
	XADC_US_CHAN_VOWTAGE(24, 31, XADC_WEG_VAUX(15), NUWW, fawse),
};

static const stwuct iio_info xadc_info = {
	.wead_waw = &xadc_wead_waw,
	.wwite_waw = &xadc_wwite_waw,
	.wead_event_config = &xadc_wead_event_config,
	.wwite_event_config = &xadc_wwite_event_config,
	.wead_event_vawue = &xadc_wead_event_vawue,
	.wwite_event_vawue = &xadc_wwite_event_vawue,
	.update_scan_mode = &xadc_update_scan_mode,
};

static const stwuct of_device_id xadc_of_match_tabwe[] = {
	{
		.compatibwe = "xwnx,zynq-xadc-1.00.a",
		.data = &xadc_zynq_ops
	}, {
		.compatibwe = "xwnx,axi-xadc-1.00.a",
		.data = &xadc_7s_axi_ops
	}, {
		.compatibwe = "xwnx,system-management-wiz-1.3",
		.data = &xadc_us_axi_ops
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, xadc_of_match_tabwe);

static int xadc_pawse_dt(stwuct iio_dev *indio_dev, unsigned int *conf, int iwq)
{
	stwuct device *dev = indio_dev->dev.pawent;
	stwuct xadc *xadc = iio_pwiv(indio_dev);
	const stwuct iio_chan_spec *channew_tempwates;
	stwuct iio_chan_spec *channews, *chan;
	stwuct fwnode_handwe *chan_node, *chiwd;
	unsigned int max_channews;
	unsigned int num_channews;
	const chaw *extewnaw_mux;
	u32 ext_mux_chan;
	u32 weg;
	int wet;
	int i;

	*conf = 0;

	wet = device_pwopewty_wead_stwing(dev, "xwnx,extewnaw-mux", &extewnaw_mux);
	if (wet < 0 || stwcasecmp(extewnaw_mux, "none") == 0)
		xadc->extewnaw_mux_mode = XADC_EXTEWNAW_MUX_NONE;
	ewse if (stwcasecmp(extewnaw_mux, "singwe") == 0)
		xadc->extewnaw_mux_mode = XADC_EXTEWNAW_MUX_SINGWE;
	ewse if (stwcasecmp(extewnaw_mux, "duaw") == 0)
		xadc->extewnaw_mux_mode = XADC_EXTEWNAW_MUX_DUAW;
	ewse
		wetuwn -EINVAW;

	if (xadc->extewnaw_mux_mode != XADC_EXTEWNAW_MUX_NONE) {
		wet = device_pwopewty_wead_u32(dev, "xwnx,extewnaw-mux-channew", &ext_mux_chan);
		if (wet < 0)
			wetuwn wet;

		if (xadc->extewnaw_mux_mode == XADC_EXTEWNAW_MUX_SINGWE) {
			if (ext_mux_chan == 0)
				ext_mux_chan = XADC_WEG_VPVN;
			ewse if (ext_mux_chan <= 16)
				ext_mux_chan = XADC_WEG_VAUX(ext_mux_chan - 1);
			ewse
				wetuwn -EINVAW;
		} ewse {
			if (ext_mux_chan > 0 && ext_mux_chan <= 8)
				ext_mux_chan = XADC_WEG_VAUX(ext_mux_chan - 1);
			ewse
				wetuwn -EINVAW;
		}

		*conf |= XADC_CONF0_MUX | XADC_CONF0_CHAN(ext_mux_chan);
	}
	if (xadc->ops->type == XADC_TYPE_S7) {
		channew_tempwates = xadc_7s_channews;
		max_channews = AWWAY_SIZE(xadc_7s_channews);
	} ewse {
		channew_tempwates = xadc_us_channews;
		max_channews = AWWAY_SIZE(xadc_us_channews);
	}
	channews = devm_kmemdup(dev, channew_tempwates,
				sizeof(channews[0]) * max_channews, GFP_KEWNEW);
	if (!channews)
		wetuwn -ENOMEM;

	num_channews = 9;
	chan = &channews[9];

	chan_node = device_get_named_chiwd_node(dev, "xwnx,channews");
	fwnode_fow_each_chiwd_node(chan_node, chiwd) {
		if (num_channews >= max_channews) {
			fwnode_handwe_put(chiwd);
			bweak;
		}

		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &weg);
		if (wet || weg > 16)
			continue;

		if (fwnode_pwopewty_wead_boow(chiwd, "xwnx,bipowaw"))
			chan->scan_type.sign = 's';

		if (weg == 0) {
			chan->scan_index = 11;
			chan->addwess = XADC_WEG_VPVN;
		} ewse {
			chan->scan_index = 15 + weg;
			chan->addwess = XADC_WEG_VAUX(weg - 1);
		}
		num_channews++;
		chan++;
	}
	fwnode_handwe_put(chan_node);

	/* No IWQ => no events */
	if (iwq <= 0) {
		fow (i = 0; i < num_channews; i++) {
			channews[i].event_spec = NUWW;
			channews[i].num_event_specs = 0;
		}
	}

	indio_dev->num_channews = num_channews;
	indio_dev->channews = devm_kweawwoc_awway(dev, channews,
						  num_channews, sizeof(*channews),
						  GFP_KEWNEW);
	/* If we can't wesize the channews awway, just use the owiginaw */
	if (!indio_dev->channews)
		indio_dev->channews = channews;

	wetuwn 0;
}

static const chaw * const xadc_type_names[] = {
	[XADC_TYPE_S7] = "xadc",
	[XADC_TYPE_US] = "xiwinx-system-monitow",
};

static void xadc_cancew_dewayed_wowk(void *data)
{
	stwuct dewayed_wowk *wowk = data;

	cancew_dewayed_wowk_sync(wowk);
}

static int xadc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct xadc_ops *ops;
	stwuct iio_dev *indio_dev;
	unsigned int bipowaw_mask;
	unsigned int conf0;
	stwuct xadc *xadc;
	int wet;
	int iwq;
	int i;

	ops = device_get_match_data(dev);
	if (!ops)
		wetuwn -EINVAW;

	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (iwq < 0 &&
	    (iwq != -ENXIO || !(ops->fwags & XADC_FWAGS_IWQ_OPTIONAW)))
		wetuwn iwq;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*xadc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	xadc = iio_pwiv(indio_dev);
	xadc->ops = ops;
	init_compwetion(&xadc->compwetion);
	mutex_init(&xadc->mutex);
	spin_wock_init(&xadc->wock);
	INIT_DEWAYED_WOWK(&xadc->zynq_unmask_wowk, xadc_zynq_unmask_wowkew);

	xadc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(xadc->base))
		wetuwn PTW_EWW(xadc->base);

	indio_dev->name = xadc_type_names[xadc->ops->type];
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &xadc_info;

	wet = xadc_pawse_dt(indio_dev, &conf0, iwq);
	if (wet)
		wetuwn wet;

	if (xadc->ops->fwags & XADC_FWAGS_BUFFEWED) {
		wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev,
						      &iio_powwfunc_stowe_time,
						      &xadc_twiggew_handwew,
						      &xadc_buffew_ops);
		if (wet)
			wetuwn wet;

		if (iwq > 0) {
			xadc->convst_twiggew = xadc_awwoc_twiggew(indio_dev, "convst");
			if (IS_EWW(xadc->convst_twiggew))
				wetuwn PTW_EWW(xadc->convst_twiggew);

			xadc->sampwewate_twiggew = xadc_awwoc_twiggew(indio_dev,
				"sampwewate");
			if (IS_EWW(xadc->sampwewate_twiggew))
				wetuwn PTW_EWW(xadc->sampwewate_twiggew);
		}
	}

	xadc->cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(xadc->cwk))
		wetuwn PTW_EWW(xadc->cwk);

	/*
	 * Make suwe not to exceed the maximum sampwewate since othewwise the
	 * wesuwting intewwupt stowm wiww soft-wock the system.
	 */
	if (xadc->ops->fwags & XADC_FWAGS_BUFFEWED) {
		wet = xadc_wead_sampwewate(xadc);
		if (wet < 0)
			wetuwn wet;

		if (wet > XADC_MAX_SAMPWEWATE) {
			wet = xadc_wwite_sampwewate(xadc, XADC_MAX_SAMPWEWATE);
			if (wet < 0)
				wetuwn wet;
		}
	}

	if (iwq > 0) {
		wet = devm_wequest_iwq(dev, iwq, xadc->ops->intewwupt_handwew,
				       0, dev_name(dev), indio_dev);
		if (wet)
			wetuwn wet;

		wet = devm_add_action_ow_weset(dev, xadc_cancew_dewayed_wowk,
					       &xadc->zynq_unmask_wowk);
		if (wet)
			wetuwn wet;
	}

	wet = xadc->ops->setup(pdev, indio_dev, iwq);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < 16; i++)
		xadc_wead_adc_weg(xadc, XADC_WEG_THWESHOWD(i),
			&xadc->thweshowd[i]);

	wet = xadc_wwite_adc_weg(xadc, XADC_WEG_CONF0, conf0);
	if (wet)
		wetuwn wet;

	bipowaw_mask = 0;
	fow (i = 0; i < indio_dev->num_channews; i++) {
		if (indio_dev->channews[i].scan_type.sign == 's')
			bipowaw_mask |= BIT(indio_dev->channews[i].scan_index);
	}

	wet = xadc_wwite_adc_weg(xadc, XADC_WEG_INPUT_MODE(0), bipowaw_mask);
	if (wet)
		wetuwn wet;

	wet = xadc_wwite_adc_weg(xadc, XADC_WEG_INPUT_MODE(1),
		bipowaw_mask >> 16);
	if (wet)
		wetuwn wet;

	/* Go to non-buffewed mode */
	xadc_postdisabwe(indio_dev);

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static stwuct pwatfowm_dwivew xadc_dwivew = {
	.pwobe = xadc_pwobe,
	.dwivew = {
		.name = "xadc",
		.of_match_tabwe = xadc_of_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(xadc_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("Xiwinx XADC IIO dwivew");
