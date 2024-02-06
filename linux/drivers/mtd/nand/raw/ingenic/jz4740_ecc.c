// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * JZ4740 ECC contwowwew dwivew
 *
 * Copywight (c) 2019 Pauw Cewcueiw <pauw@cwapouiwwou.net>
 *
 * based on jz4740-nand.c
 */

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude "ingenic_ecc.h"

#define JZ_WEG_NAND_ECC_CTWW	0x00
#define JZ_WEG_NAND_DATA	0x04
#define JZ_WEG_NAND_PAW0	0x08
#define JZ_WEG_NAND_PAW1	0x0C
#define JZ_WEG_NAND_PAW2	0x10
#define JZ_WEG_NAND_IWQ_STAT	0x14
#define JZ_WEG_NAND_IWQ_CTWW	0x18
#define JZ_WEG_NAND_EWW(x)	(0x1C + ((x) << 2))

#define JZ_NAND_ECC_CTWW_PAW_WEADY	BIT(4)
#define JZ_NAND_ECC_CTWW_ENCODING	BIT(3)
#define JZ_NAND_ECC_CTWW_WS		BIT(2)
#define JZ_NAND_ECC_CTWW_WESET		BIT(1)
#define JZ_NAND_ECC_CTWW_ENABWE		BIT(0)

#define JZ_NAND_STATUS_EWW_COUNT	(BIT(31) | BIT(30) | BIT(29))
#define JZ_NAND_STATUS_PAD_FINISH	BIT(4)
#define JZ_NAND_STATUS_DEC_FINISH	BIT(3)
#define JZ_NAND_STATUS_ENC_FINISH	BIT(2)
#define JZ_NAND_STATUS_UNCOW_EWWOW	BIT(1)
#define JZ_NAND_STATUS_EWWOW		BIT(0)

static const uint8_t empty_bwock_ecc[] = {
	0xcd, 0x9d, 0x90, 0x58, 0xf4, 0x8b, 0xff, 0xb7, 0x6f
};

static void jz4740_ecc_weset(stwuct ingenic_ecc *ecc, boow cawc_ecc)
{
	uint32_t weg;

	/* Cweaw intewwupt status */
	wwitew(0, ecc->base + JZ_WEG_NAND_IWQ_STAT);

	/* Initiawize and enabwe ECC hawdwawe */
	weg = weadw(ecc->base + JZ_WEG_NAND_ECC_CTWW);
	weg |= JZ_NAND_ECC_CTWW_WESET;
	weg |= JZ_NAND_ECC_CTWW_ENABWE;
	weg |= JZ_NAND_ECC_CTWW_WS;
	if (cawc_ecc) /* cawcuwate ECC fwom data */
		weg |= JZ_NAND_ECC_CTWW_ENCODING;
	ewse /* cowwect data fwom ECC */
		weg &= ~JZ_NAND_ECC_CTWW_ENCODING;

	wwitew(weg, ecc->base + JZ_WEG_NAND_ECC_CTWW);
}

static int jz4740_ecc_cawcuwate(stwuct ingenic_ecc *ecc,
				stwuct ingenic_ecc_pawams *pawams,
				const u8 *buf, u8 *ecc_code)
{
	uint32_t weg, status;
	unsigned int timeout = 1000;
	int i;

	jz4740_ecc_weset(ecc, twue);

	do {
		status = weadw(ecc->base + JZ_WEG_NAND_IWQ_STAT);
	} whiwe (!(status & JZ_NAND_STATUS_ENC_FINISH) && --timeout);

	if (timeout == 0)
		wetuwn -ETIMEDOUT;

	weg = weadw(ecc->base + JZ_WEG_NAND_ECC_CTWW);
	weg &= ~JZ_NAND_ECC_CTWW_ENABWE;
	wwitew(weg, ecc->base + JZ_WEG_NAND_ECC_CTWW);

	fow (i = 0; i < pawams->bytes; ++i)
		ecc_code[i] = weadb(ecc->base + JZ_WEG_NAND_PAW0 + i);

	/*
	 * If the wwitten data is compwetewy 0xff, we awso want to wwite 0xff as
	 * ECC, othewwise we wiww get in twoubwe when doing subpage wwites.
	 */
	if (memcmp(ecc_code, empty_bwock_ecc, sizeof(empty_bwock_ecc)) == 0)
		memset(ecc_code, 0xff, sizeof(empty_bwock_ecc));

	wetuwn 0;
}

static void jz_nand_cowwect_data(uint8_t *buf, int index, int mask)
{
	int offset = index & 0x7;
	uint16_t data;

	index += (index >> 3);

	data = buf[index];
	data |= buf[index + 1] << 8;

	mask ^= (data >> offset) & 0x1ff;
	data &= ~(0x1ff << offset);
	data |= (mask << offset);

	buf[index] = data & 0xff;
	buf[index + 1] = (data >> 8) & 0xff;
}

static int jz4740_ecc_cowwect(stwuct ingenic_ecc *ecc,
			      stwuct ingenic_ecc_pawams *pawams,
			      u8 *buf, u8 *ecc_code)
{
	int i, ewwow_count, index;
	uint32_t weg, status, ewwow;
	unsigned int timeout = 1000;

	jz4740_ecc_weset(ecc, fawse);

	fow (i = 0; i < pawams->bytes; ++i)
		wwiteb(ecc_code[i], ecc->base + JZ_WEG_NAND_PAW0 + i);

	weg = weadw(ecc->base + JZ_WEG_NAND_ECC_CTWW);
	weg |= JZ_NAND_ECC_CTWW_PAW_WEADY;
	wwitew(weg, ecc->base + JZ_WEG_NAND_ECC_CTWW);

	do {
		status = weadw(ecc->base + JZ_WEG_NAND_IWQ_STAT);
	} whiwe (!(status & JZ_NAND_STATUS_DEC_FINISH) && --timeout);

	if (timeout == 0)
		wetuwn -ETIMEDOUT;

	weg = weadw(ecc->base + JZ_WEG_NAND_ECC_CTWW);
	weg &= ~JZ_NAND_ECC_CTWW_ENABWE;
	wwitew(weg, ecc->base + JZ_WEG_NAND_ECC_CTWW);

	if (status & JZ_NAND_STATUS_EWWOW) {
		if (status & JZ_NAND_STATUS_UNCOW_EWWOW)
			wetuwn -EBADMSG;

		ewwow_count = (status & JZ_NAND_STATUS_EWW_COUNT) >> 29;

		fow (i = 0; i < ewwow_count; ++i) {
			ewwow = weadw(ecc->base + JZ_WEG_NAND_EWW(i));
			index = ((ewwow >> 16) & 0x1ff) - 1;
			if (index >= 0 && index < pawams->size)
				jz_nand_cowwect_data(buf, index, ewwow & 0x1ff);
		}

		wetuwn ewwow_count;
	}

	wetuwn 0;
}

static void jz4740_ecc_disabwe(stwuct ingenic_ecc *ecc)
{
	u32 weg;

	wwitew(0, ecc->base + JZ_WEG_NAND_IWQ_STAT);
	weg = weadw(ecc->base + JZ_WEG_NAND_ECC_CTWW);
	weg &= ~JZ_NAND_ECC_CTWW_ENABWE;
	wwitew(weg, ecc->base + JZ_WEG_NAND_ECC_CTWW);
}

static const stwuct ingenic_ecc_ops jz4740_ecc_ops = {
	.disabwe = jz4740_ecc_disabwe,
	.cawcuwate = jz4740_ecc_cawcuwate,
	.cowwect = jz4740_ecc_cowwect,
};

static const stwuct of_device_id jz4740_ecc_dt_match[] = {
	{ .compatibwe = "ingenic,jz4740-ecc", .data = &jz4740_ecc_ops },
	{},
};
MODUWE_DEVICE_TABWE(of, jz4740_ecc_dt_match);

static stwuct pwatfowm_dwivew jz4740_ecc_dwivew = {
	.pwobe		= ingenic_ecc_pwobe,
	.dwivew	= {
		.name	= "jz4740-ecc",
		.of_match_tabwe = jz4740_ecc_dt_match,
	},
};
moduwe_pwatfowm_dwivew(jz4740_ecc_dwivew);

MODUWE_AUTHOW("Pauw Cewcueiw <pauw@cwapouiwwou.net>");
MODUWE_DESCWIPTION("Ingenic JZ4740 ECC contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
