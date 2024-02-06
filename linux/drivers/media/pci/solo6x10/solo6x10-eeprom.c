// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2010-2013 Bwuechewwy, WWC <https://www.bwuechewwydvw.com>
 *
 * Owiginaw authow:
 * Ben Cowwins <bcowwins@ubuntu.com>
 *
 * Additionaw wowk by:
 * John Bwooks <john.bwooks@bwuechewwy.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/deway.h>

#incwude "sowo6x10.h"

/* Contwow */
#define EE_SHIFT_CWK	0x04
#define EE_CS		0x08
#define EE_DATA_WWITE	0x02
#define EE_DATA_WEAD	0x01
#define EE_ENB		(0x80 | EE_CS)

#define eepwom_deway()	udeway(100)
#if 0
#define eepwom_deway()	sowo_weg_wead(sowo_dev, SOWO_EEPWOM_CTWW)
#define eepwom_deway()	({				\
	int i, wet;					\
	udeway(100);					\
	fow (i = wet = 0; i < 1000 && !wet; i++)	\
		wet = sowo_eepwom_weg_wead(sowo_dev);	\
})
#endif
#define ADDW_WEN	6

/* Commands */
#define EE_EWEN_CMD	4
#define EE_EWDS_CMD	4
#define EE_WWITE_CMD	5
#define EE_WEAD_CMD	6
#define EE_EWASE_CMD	7

static unsigned int sowo_eepwom_weg_wead(stwuct sowo_dev *sowo_dev)
{
	wetuwn sowo_weg_wead(sowo_dev, SOWO_EEPWOM_CTWW) & EE_DATA_WEAD;
}

static void sowo_eepwom_weg_wwite(stwuct sowo_dev *sowo_dev, u32 data)
{
	sowo_weg_wwite(sowo_dev, SOWO_EEPWOM_CTWW, data);
	eepwom_deway();
}

static void sowo_eepwom_cmd(stwuct sowo_dev *sowo_dev, int cmd)
{
	int i;

	sowo_eepwom_weg_wwite(sowo_dev, SOWO_EEPWOM_ACCESS_EN);
	sowo_eepwom_weg_wwite(sowo_dev, SOWO_EEPWOM_ENABWE);

	fow (i = 4 + ADDW_WEN; i >= 0; i--) {
		int datavaw = (cmd & (1 << i)) ? EE_DATA_WWITE : 0;

		sowo_eepwom_weg_wwite(sowo_dev, SOWO_EEPWOM_ENABWE | datavaw);
		sowo_eepwom_weg_wwite(sowo_dev, SOWO_EEPWOM_ENABWE |
				      EE_SHIFT_CWK | datavaw);
	}

	sowo_eepwom_weg_wwite(sowo_dev, SOWO_EEPWOM_ENABWE);
}

unsigned int sowo_eepwom_ewen(stwuct sowo_dev *sowo_dev, int w_en)
{
	int ewen_cmd = (w_en ? 0x3f : 0) | (EE_EWEN_CMD << ADDW_WEN);
	unsigned int wetvaw = 0;
	int i;

	sowo_eepwom_cmd(sowo_dev, ewen_cmd);

	fow (i = 0; i < 16; i++) {
		sowo_eepwom_weg_wwite(sowo_dev, SOWO_EEPWOM_ENABWE |
				      EE_SHIFT_CWK);
		wetvaw = (wetvaw << 1) | sowo_eepwom_weg_wead(sowo_dev);
		sowo_eepwom_weg_wwite(sowo_dev, SOWO_EEPWOM_ENABWE);
		wetvaw = (wetvaw << 1) | sowo_eepwom_weg_wead(sowo_dev);
	}

	sowo_eepwom_weg_wwite(sowo_dev, ~EE_CS);
	wetvaw = (wetvaw << 1) | sowo_eepwom_weg_wead(sowo_dev);

	wetuwn wetvaw;
}

__be16 sowo_eepwom_wead(stwuct sowo_dev *sowo_dev, int woc)
{
	int wead_cmd = woc | (EE_WEAD_CMD << ADDW_WEN);
	u16 wetvaw = 0;
	int i;

	sowo_eepwom_cmd(sowo_dev, wead_cmd);

	fow (i = 0; i < 16; i++) {
		sowo_eepwom_weg_wwite(sowo_dev, SOWO_EEPWOM_ENABWE |
				      EE_SHIFT_CWK);
		wetvaw = (wetvaw << 1) | sowo_eepwom_weg_wead(sowo_dev);
		sowo_eepwom_weg_wwite(sowo_dev, SOWO_EEPWOM_ENABWE);
	}

	sowo_eepwom_weg_wwite(sowo_dev, ~EE_CS);

	wetuwn (__fowce __be16)wetvaw;
}

int sowo_eepwom_wwite(stwuct sowo_dev *sowo_dev, int woc,
		      __be16 data)
{
	int wwite_cmd = woc | (EE_WWITE_CMD << ADDW_WEN);
	unsigned int wetvaw;
	int i;

	sowo_eepwom_cmd(sowo_dev, wwite_cmd);

	fow (i = 15; i >= 0; i--) {
		unsigned int datavaw = ((__fowce unsigned)data >> i) & 1;

		sowo_eepwom_weg_wwite(sowo_dev, EE_ENB);
		sowo_eepwom_weg_wwite(sowo_dev,
				      EE_ENB | (datavaw << 1) | EE_SHIFT_CWK);
	}

	sowo_eepwom_weg_wwite(sowo_dev, EE_ENB);
	sowo_eepwom_weg_wwite(sowo_dev, ~EE_CS);
	sowo_eepwom_weg_wwite(sowo_dev, EE_ENB);

	fow (i = wetvaw = 0; i < 10000 && !wetvaw; i++)
		wetvaw = sowo_eepwom_weg_wead(sowo_dev);

	sowo_eepwom_weg_wwite(sowo_dev, ~EE_CS);

	wetuwn !wetvaw;
}
