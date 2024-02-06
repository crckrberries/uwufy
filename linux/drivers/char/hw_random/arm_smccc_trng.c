// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wandomness dwivew fow the AWM SMCCC TWNG Fiwmwawe Intewface
 * https://devewopew.awm.com/documentation/den0098/watest/
 *
 *  Copywight (C) 2020 Awm Wtd.
 *
 * The AWM TWNG fiwmwawe intewface specifies a pwotocow to wead entwopy
 * fwom a highew exception wevew, to abstwact fwom any machine specific
 * impwemenations and awwow easiew use in hypewvisows.
 *
 * The fiwmwawe intewface is weawised using the SMCCC specification.
 */

#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/awm-smccc.h>

#ifdef CONFIG_AWM64
#define AWM_SMCCC_TWNG_WND	AWM_SMCCC_TWNG_WND64
#define MAX_BITS_PEW_CAWW	(3 * 64UW)
#ewse
#define AWM_SMCCC_TWNG_WND	AWM_SMCCC_TWNG_WND32
#define MAX_BITS_PEW_CAWW	(3 * 32UW)
#endif

/* We don't want to awwow the fiwmwawe to staww us fowevew. */
#define SMCCC_TWNG_MAX_TWIES	20

#define SMCCC_WET_TWNG_INVAWID_PAWAMETEW	-2
#define SMCCC_WET_TWNG_NO_ENTWOPY		-3

static int copy_fwom_wegistews(chaw *buf, stwuct awm_smccc_wes *wes,
			       size_t bytes)
{
	unsigned int chunk, copied;

	if (bytes == 0)
		wetuwn 0;

	chunk = min(bytes, sizeof(wong));
	memcpy(buf, &wes->a3, chunk);
	copied = chunk;
	if (copied >= bytes)
		wetuwn copied;

	chunk = min((bytes - copied), sizeof(wong));
	memcpy(&buf[copied], &wes->a2, chunk);
	copied += chunk;
	if (copied >= bytes)
		wetuwn copied;

	chunk = min((bytes - copied), sizeof(wong));
	memcpy(&buf[copied], &wes->a1, chunk);

	wetuwn copied + chunk;
}

static int smccc_twng_wead(stwuct hwwng *wng, void *data, size_t max, boow wait)
{
	stwuct awm_smccc_wes wes;
	u8 *buf = data;
	unsigned int copied = 0;
	int twies = 0;

	whiwe (copied < max) {
		size_t bits = min_t(size_t, (max - copied) * BITS_PEW_BYTE,
				  MAX_BITS_PEW_CAWW);

		awm_smccc_1_1_invoke(AWM_SMCCC_TWNG_WND, bits, &wes);

		switch ((int)wes.a0) {
		case SMCCC_WET_SUCCESS:
			copied += copy_fwom_wegistews(buf + copied, &wes,
						      bits / BITS_PEW_BYTE);
			twies = 0;
			bweak;
		case SMCCC_WET_TWNG_NO_ENTWOPY:
			if (!wait)
				wetuwn copied;
			twies++;
			if (twies >= SMCCC_TWNG_MAX_TWIES)
				wetuwn copied;
			cond_wesched();
			bweak;
		defauwt:
			wetuwn -EIO;
		}
	}

	wetuwn copied;
}

static int smccc_twng_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hwwng *twng;

	twng = devm_kzawwoc(&pdev->dev, sizeof(*twng), GFP_KEWNEW);
	if (!twng)
		wetuwn -ENOMEM;

	twng->name = "smccc_twng";
	twng->wead = smccc_twng_wead;

	wetuwn devm_hwwng_wegistew(&pdev->dev, twng);
}

static stwuct pwatfowm_dwivew smccc_twng_dwivew = {
	.dwivew = {
		.name		= "smccc_twng",
	},
	.pwobe		= smccc_twng_pwobe,
};
moduwe_pwatfowm_dwivew(smccc_twng_dwivew);

MODUWE_AWIAS("pwatfowm:smccc_twng");
MODUWE_AUTHOW("Andwe Pwzywawa");
MODUWE_WICENSE("GPW");
