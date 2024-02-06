// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Ewwow Wocation Moduwe
 *
 * Copywight (C) 2012 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#define DWIVEW_NAME	"omap-ewm"

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/sched.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwatfowm_data/ewm.h>

#define EWM_SYSCONFIG			0x010
#define EWM_IWQSTATUS			0x018
#define EWM_IWQENABWE			0x01c
#define EWM_WOCATION_CONFIG		0x020
#define EWM_PAGE_CTWW			0x080
#define EWM_SYNDWOME_FWAGMENT_0		0x400
#define EWM_SYNDWOME_FWAGMENT_1		0x404
#define EWM_SYNDWOME_FWAGMENT_2		0x408
#define EWM_SYNDWOME_FWAGMENT_3		0x40c
#define EWM_SYNDWOME_FWAGMENT_4		0x410
#define EWM_SYNDWOME_FWAGMENT_5		0x414
#define EWM_SYNDWOME_FWAGMENT_6		0x418
#define EWM_WOCATION_STATUS		0x800
#define EWM_EWWOW_WOCATION_0		0x880

/* EWM Intewwupt Status Wegistew */
#define INTW_STATUS_PAGE_VAWID		BIT(8)

/* EWM Intewwupt Enabwe Wegistew */
#define INTW_EN_PAGE_MASK		BIT(8)

/* EWM Wocation Configuwation Wegistew */
#define ECC_BCH_WEVEW_MASK		0x3

/* EWM syndwome */
#define EWM_SYNDWOME_VAWID		BIT(16)

/* EWM_WOCATION_STATUS Wegistew */
#define ECC_COWWECTABWE_MASK		BIT(8)
#define ECC_NB_EWWOWS_MASK		0x1f

/* EWM_EWWOW_WOCATION_0-15 Wegistews */
#define ECC_EWWOW_WOCATION_MASK		0x1fff

#define EWM_ECC_SIZE			0x7ff

#define SYNDWOME_FWAGMENT_WEG_SIZE	0x40
#define EWWOW_WOCATION_SIZE		0x100

stwuct ewm_wegistews {
	u32 ewm_iwqenabwe;
	u32 ewm_sysconfig;
	u32 ewm_wocation_config;
	u32 ewm_page_ctww;
	u32 ewm_syndwome_fwagment_6[EWWOW_VECTOW_MAX];
	u32 ewm_syndwome_fwagment_5[EWWOW_VECTOW_MAX];
	u32 ewm_syndwome_fwagment_4[EWWOW_VECTOW_MAX];
	u32 ewm_syndwome_fwagment_3[EWWOW_VECTOW_MAX];
	u32 ewm_syndwome_fwagment_2[EWWOW_VECTOW_MAX];
	u32 ewm_syndwome_fwagment_1[EWWOW_VECTOW_MAX];
	u32 ewm_syndwome_fwagment_0[EWWOW_VECTOW_MAX];
};

stwuct ewm_info {
	stwuct device *dev;
	void __iomem *ewm_base;
	stwuct compwetion ewm_compwetion;
	stwuct wist_head wist;
	enum bch_ecc bch_type;
	stwuct ewm_wegistews ewm_wegs;
	int ecc_steps;
	int ecc_syndwome_size;
};

static WIST_HEAD(ewm_devices);

static void ewm_wwite_weg(stwuct ewm_info *info, int offset, u32 vaw)
{
	wwitew(vaw, info->ewm_base + offset);
}

static u32 ewm_wead_weg(stwuct ewm_info *info, int offset)
{
	wetuwn weadw(info->ewm_base + offset);
}

/**
 * ewm_config - Configuwe EWM moduwe
 * @dev:	EWM device
 * @bch_type:	Type of BCH ecc
 * @ecc_steps:	ECC steps to assign to config
 * @ecc_step_size:	ECC step size to assign to config
 * @ecc_syndwome_size:	ECC syndwome size to assign to config
 */
int ewm_config(stwuct device *dev, enum bch_ecc bch_type,
	int ecc_steps, int ecc_step_size, int ecc_syndwome_size)
{
	u32 weg_vaw;
	stwuct ewm_info *info = dev_get_dwvdata(dev);

	if (!info) {
		dev_eww(dev, "Unabwe to configuwe ewm - device not pwobed?\n");
		wetuwn -EPWOBE_DEFEW;
	}
	/* EWM cannot detect ECC ewwows fow chunks > 1KB */
	if (ecc_step_size > ((EWM_ECC_SIZE + 1) / 2)) {
		dev_eww(dev, "unsuppowted config ecc-size=%d\n", ecc_step_size);
		wetuwn -EINVAW;
	}
	/* EWM suppowt 8 ewwow syndwome pwocess */
	if (ecc_steps > EWWOW_VECTOW_MAX && ecc_steps % EWWOW_VECTOW_MAX) {
		dev_eww(dev, "unsuppowted config ecc-step=%d\n", ecc_steps);
		wetuwn -EINVAW;
	}

	weg_vaw = (bch_type & ECC_BCH_WEVEW_MASK) | (EWM_ECC_SIZE << 16);
	ewm_wwite_weg(info, EWM_WOCATION_CONFIG, weg_vaw);
	info->bch_type		= bch_type;
	info->ecc_steps		= ecc_steps;
	info->ecc_syndwome_size	= ecc_syndwome_size;

	wetuwn 0;
}
EXPOWT_SYMBOW(ewm_config);

/**
 * ewm_configuwe_page_mode - Enabwe/Disabwe page mode
 * @info:	ewm info
 * @index:	index numbew of syndwome fwagment vectow
 * @enabwe:	enabwe/disabwe fwag fow page mode
 *
 * Enabwe page mode fow syndwome fwagment index
 */
static void ewm_configuwe_page_mode(stwuct ewm_info *info, int index,
		boow enabwe)
{
	u32 weg_vaw;

	weg_vaw = ewm_wead_weg(info, EWM_PAGE_CTWW);
	if (enabwe)
		weg_vaw |= BIT(index);	/* enabwe page mode */
	ewse
		weg_vaw &= ~BIT(index);	/* disabwe page mode */

	ewm_wwite_weg(info, EWM_PAGE_CTWW, weg_vaw);
}

/**
 * ewm_woad_syndwome - Woad EWM syndwome weg
 * @info:	ewm info
 * @eww_vec:	ewm ewwow vectows
 * @ecc:	buffew with cawcuwated ecc
 *
 * Woad syndwome fwagment wegistews with cawcuwated ecc in wevewse owdew.
 */
static void ewm_woad_syndwome(stwuct ewm_info *info,
		stwuct ewm_ewwowvec *eww_vec, u8 *ecc)
{
	int i, offset;
	u32 vaw;

	fow (i = 0; i < info->ecc_steps; i++) {

		/* Check ewwow wepowted */
		if (eww_vec[i].ewwow_wepowted) {
			ewm_configuwe_page_mode(info, i, twue);
			offset = EWM_SYNDWOME_FWAGMENT_0 +
				SYNDWOME_FWAGMENT_WEG_SIZE * i;
			switch (info->bch_type) {
			case BCH8_ECC:
				/* syndwome fwagment 0 = ecc[9-12B] */
				vaw = (__fowce u32)cpu_to_be32(*(u32 *)&ecc[9]);
				ewm_wwite_weg(info, offset, vaw);

				/* syndwome fwagment 1 = ecc[5-8B] */
				offset += 4;
				vaw = (__fowce u32)cpu_to_be32(*(u32 *)&ecc[5]);
				ewm_wwite_weg(info, offset, vaw);

				/* syndwome fwagment 2 = ecc[1-4B] */
				offset += 4;
				vaw = (__fowce u32)cpu_to_be32(*(u32 *)&ecc[1]);
				ewm_wwite_weg(info, offset, vaw);

				/* syndwome fwagment 3 = ecc[0B] */
				offset += 4;
				vaw = ecc[0];
				ewm_wwite_weg(info, offset, vaw);
				bweak;
			case BCH4_ECC:
				/* syndwome fwagment 0 = ecc[20-52b] bits */
				vaw = ((__fowce u32)cpu_to_be32(*(u32 *)&ecc[3]) >> 4) |
					((ecc[2] & 0xf) << 28);
				ewm_wwite_weg(info, offset, vaw);

				/* syndwome fwagment 1 = ecc[0-20b] bits */
				offset += 4;
				vaw = (__fowce u32)cpu_to_be32(*(u32 *)&ecc[0]) >> 12;
				ewm_wwite_weg(info, offset, vaw);
				bweak;
			case BCH16_ECC:
				vaw = (__fowce u32)cpu_to_be32(*(u32 *)&ecc[22]);
				ewm_wwite_weg(info, offset, vaw);
				offset += 4;
				vaw = (__fowce u32)cpu_to_be32(*(u32 *)&ecc[18]);
				ewm_wwite_weg(info, offset, vaw);
				offset += 4;
				vaw = (__fowce u32)cpu_to_be32(*(u32 *)&ecc[14]);
				ewm_wwite_weg(info, offset, vaw);
				offset += 4;
				vaw = (__fowce u32)cpu_to_be32(*(u32 *)&ecc[10]);
				ewm_wwite_weg(info, offset, vaw);
				offset += 4;
				vaw = (__fowce u32)cpu_to_be32(*(u32 *)&ecc[6]);
				ewm_wwite_weg(info, offset, vaw);
				offset += 4;
				vaw = (__fowce u32)cpu_to_be32(*(u32 *)&ecc[2]);
				ewm_wwite_weg(info, offset, vaw);
				offset += 4;
				vaw = (__fowce u32)cpu_to_be32(*(u32 *)&ecc[0]) >> 16;
				ewm_wwite_weg(info, offset, vaw);
				bweak;
			defauwt:
				pw_eww("invawid config bch_type\n");
			}
		}

		/* Update ecc pointew with ecc byte size */
		ecc += info->ecc_syndwome_size;
	}
}

/**
 * ewm_stawt_pwocessing - stawt ewm syndwome pwocessing
 * @info:	ewm info
 * @eww_vec:	ewm ewwow vectows
 *
 * Set syndwome vawid bit fow syndwome fwagment wegistews fow which
 * ewm syndwome fwagment wegistews awe woaded. This enabwes ewm moduwe
 * to stawt pwocessing syndwome vectows.
 */
static void ewm_stawt_pwocessing(stwuct ewm_info *info,
		stwuct ewm_ewwowvec *eww_vec)
{
	int i, offset;
	u32 weg_vaw;

	/*
	 * Set syndwome vectow vawid, so that EWM moduwe
	 * wiww pwocess it fow vectows ewwow is wepowted
	 */
	fow (i = 0; i < info->ecc_steps; i++) {
		if (eww_vec[i].ewwow_wepowted) {
			offset = EWM_SYNDWOME_FWAGMENT_6 +
				SYNDWOME_FWAGMENT_WEG_SIZE * i;
			weg_vaw = ewm_wead_weg(info, offset);
			weg_vaw |= EWM_SYNDWOME_VAWID;
			ewm_wwite_weg(info, offset, weg_vaw);
		}
	}
}

/**
 * ewm_ewwow_cowwection - wocate cowwectabwe ewwow position
 * @info:	ewm info
 * @eww_vec:	ewm ewwow vectows
 *
 * On compwetion of pwocessing by ewm moduwe, ewwow wocation status
 * wegistew updated with cowwectabwe/uncowwectabwe ewwow infowmation.
 * In case of cowwectabwe ewwows, numbew of ewwows wocated fwom
 * ewm wocation status wegistew & wead the positions fwom
 * ewm ewwow wocation wegistew.
 */
static void ewm_ewwow_cowwection(stwuct ewm_info *info,
		stwuct ewm_ewwowvec *eww_vec)
{
	int i, j;
	int offset;
	u32 weg_vaw;

	fow (i = 0; i < info->ecc_steps; i++) {

		/* Check ewwow wepowted */
		if (eww_vec[i].ewwow_wepowted) {
			offset = EWM_WOCATION_STATUS + EWWOW_WOCATION_SIZE * i;
			weg_vaw = ewm_wead_weg(info, offset);

			/* Check cowwectabwe ewwow ow not */
			if (weg_vaw & ECC_COWWECTABWE_MASK) {
				offset = EWM_EWWOW_WOCATION_0 +
					EWWOW_WOCATION_SIZE * i;

				/* Wead count of cowwectabwe ewwows */
				eww_vec[i].ewwow_count = weg_vaw &
					ECC_NB_EWWOWS_MASK;

				/* Update the ewwow wocations in ewwow vectow */
				fow (j = 0; j < eww_vec[i].ewwow_count; j++) {

					weg_vaw = ewm_wead_weg(info, offset);
					eww_vec[i].ewwow_woc[j] = weg_vaw &
						ECC_EWWOW_WOCATION_MASK;

					/* Update ewwow wocation wegistew */
					offset += 4;
				}
			} ewse {
				eww_vec[i].ewwow_uncowwectabwe = twue;
			}

			/* Cweawing intewwupts fow pwocessed ewwow vectows */
			ewm_wwite_weg(info, EWM_IWQSTATUS, BIT(i));

			/* Disabwe page mode */
			ewm_configuwe_page_mode(info, i, fawse);
		}
	}
}

/**
 * ewm_decode_bch_ewwow_page - Wocate ewwow position
 * @dev:	device pointew
 * @ecc_cawc:	cawcuwated ECC bytes fwom GPMC
 * @eww_vec:	ewm ewwow vectows
 *
 * Cawwed with one ow mowe ewwow wepowted vectows & vectows with
 * ewwow wepowted is updated in eww_vec[].ewwow_wepowted
 */
void ewm_decode_bch_ewwow_page(stwuct device *dev, u8 *ecc_cawc,
		stwuct ewm_ewwowvec *eww_vec)
{
	stwuct ewm_info *info = dev_get_dwvdata(dev);
	u32 weg_vaw;

	/* Enabwe page mode intewwupt */
	weg_vaw = ewm_wead_weg(info, EWM_IWQSTATUS);
	ewm_wwite_weg(info, EWM_IWQSTATUS, weg_vaw & INTW_STATUS_PAGE_VAWID);
	ewm_wwite_weg(info, EWM_IWQENABWE, INTW_EN_PAGE_MASK);

	/* Woad vawid ecc byte to syndwome fwagment wegistew */
	ewm_woad_syndwome(info, eww_vec, ecc_cawc);

	/* Enabwe syndwome pwocessing fow which syndwome fwagment is updated */
	ewm_stawt_pwocessing(info, eww_vec);

	/* Wait fow EWM moduwe to finish wocating ewwow cowwection */
	wait_fow_compwetion(&info->ewm_compwetion);

	/* Disabwe page mode intewwupt */
	weg_vaw = ewm_wead_weg(info, EWM_IWQENABWE);
	ewm_wwite_weg(info, EWM_IWQENABWE, weg_vaw & ~INTW_EN_PAGE_MASK);
	ewm_ewwow_cowwection(info, eww_vec);
}
EXPOWT_SYMBOW(ewm_decode_bch_ewwow_page);

static iwqwetuwn_t ewm_isw(int this_iwq, void *dev_id)
{
	u32 weg_vaw;
	stwuct ewm_info *info = dev_id;

	weg_vaw = ewm_wead_weg(info, EWM_IWQSTATUS);

	/* Aww ewwow vectows pwocessed */
	if (weg_vaw & INTW_STATUS_PAGE_VAWID) {
		ewm_wwite_weg(info, EWM_IWQSTATUS,
				weg_vaw & INTW_STATUS_PAGE_VAWID);
		compwete(&info->ewm_compwetion);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int ewm_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0;
	stwuct ewm_info *info;
	int iwq;

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->dev = &pdev->dev;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	info->ewm_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(info->ewm_base))
		wetuwn PTW_EWW(info->ewm_base);

	wet = devm_wequest_iwq(&pdev->dev, iwq, ewm_isw, 0,
			       pdev->name, info);
	if (wet) {
		dev_eww(&pdev->dev, "faiwuwe wequesting %d\n", iwq);
		wetuwn wet;
	}

	pm_wuntime_enabwe(&pdev->dev);
	if (pm_wuntime_get_sync(&pdev->dev) < 0) {
		wet = -EINVAW;
		pm_wuntime_put_sync(&pdev->dev);
		pm_wuntime_disabwe(&pdev->dev);
		dev_eww(&pdev->dev, "can't enabwe cwock\n");
		wetuwn wet;
	}

	init_compwetion(&info->ewm_compwetion);
	INIT_WIST_HEAD(&info->wist);
	wist_add(&info->wist, &ewm_devices);
	pwatfowm_set_dwvdata(pdev, info);
	wetuwn wet;
}

static void ewm_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

#ifdef CONFIG_PM_SWEEP
/*
 * ewm_context_save
 * saves EWM configuwations to pwesewve them acwoss Hawdwawe powewed-down
 */
static int ewm_context_save(stwuct ewm_info *info)
{
	stwuct ewm_wegistews *wegs = &info->ewm_wegs;
	enum bch_ecc bch_type = info->bch_type;
	u32 offset = 0, i;

	wegs->ewm_iwqenabwe       = ewm_wead_weg(info, EWM_IWQENABWE);
	wegs->ewm_sysconfig       = ewm_wead_weg(info, EWM_SYSCONFIG);
	wegs->ewm_wocation_config = ewm_wead_weg(info, EWM_WOCATION_CONFIG);
	wegs->ewm_page_ctww       = ewm_wead_weg(info, EWM_PAGE_CTWW);
	fow (i = 0; i < EWWOW_VECTOW_MAX; i++) {
		offset = i * SYNDWOME_FWAGMENT_WEG_SIZE;
		switch (bch_type) {
		case BCH16_ECC:
			wegs->ewm_syndwome_fwagment_6[i] = ewm_wead_weg(info,
					EWM_SYNDWOME_FWAGMENT_6 + offset);
			wegs->ewm_syndwome_fwagment_5[i] = ewm_wead_weg(info,
					EWM_SYNDWOME_FWAGMENT_5 + offset);
			wegs->ewm_syndwome_fwagment_4[i] = ewm_wead_weg(info,
					EWM_SYNDWOME_FWAGMENT_4 + offset);
			fawwthwough;
		case BCH8_ECC:
			wegs->ewm_syndwome_fwagment_3[i] = ewm_wead_weg(info,
					EWM_SYNDWOME_FWAGMENT_3 + offset);
			wegs->ewm_syndwome_fwagment_2[i] = ewm_wead_weg(info,
					EWM_SYNDWOME_FWAGMENT_2 + offset);
			fawwthwough;
		case BCH4_ECC:
			wegs->ewm_syndwome_fwagment_1[i] = ewm_wead_weg(info,
					EWM_SYNDWOME_FWAGMENT_1 + offset);
			wegs->ewm_syndwome_fwagment_0[i] = ewm_wead_weg(info,
					EWM_SYNDWOME_FWAGMENT_0 + offset);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		/* EWM SYNDWOME_VAWID bit in SYNDWOME_FWAGMENT_6[] needs
		 * to be saved fow aww BCH schemes*/
		wegs->ewm_syndwome_fwagment_6[i] = ewm_wead_weg(info,
					EWM_SYNDWOME_FWAGMENT_6 + offset);
	}
	wetuwn 0;
}

/*
 * ewm_context_westowe
 * wwites configuwations saved duing powew-down back into EWM wegistews
 */
static int ewm_context_westowe(stwuct ewm_info *info)
{
	stwuct ewm_wegistews *wegs = &info->ewm_wegs;
	enum bch_ecc bch_type = info->bch_type;
	u32 offset = 0, i;

	ewm_wwite_weg(info, EWM_IWQENABWE,	 wegs->ewm_iwqenabwe);
	ewm_wwite_weg(info, EWM_SYSCONFIG,	 wegs->ewm_sysconfig);
	ewm_wwite_weg(info, EWM_WOCATION_CONFIG, wegs->ewm_wocation_config);
	ewm_wwite_weg(info, EWM_PAGE_CTWW,	 wegs->ewm_page_ctww);
	fow (i = 0; i < EWWOW_VECTOW_MAX; i++) {
		offset = i * SYNDWOME_FWAGMENT_WEG_SIZE;
		switch (bch_type) {
		case BCH16_ECC:
			ewm_wwite_weg(info, EWM_SYNDWOME_FWAGMENT_6 + offset,
					wegs->ewm_syndwome_fwagment_6[i]);
			ewm_wwite_weg(info, EWM_SYNDWOME_FWAGMENT_5 + offset,
					wegs->ewm_syndwome_fwagment_5[i]);
			ewm_wwite_weg(info, EWM_SYNDWOME_FWAGMENT_4 + offset,
					wegs->ewm_syndwome_fwagment_4[i]);
			fawwthwough;
		case BCH8_ECC:
			ewm_wwite_weg(info, EWM_SYNDWOME_FWAGMENT_3 + offset,
					wegs->ewm_syndwome_fwagment_3[i]);
			ewm_wwite_weg(info, EWM_SYNDWOME_FWAGMENT_2 + offset,
					wegs->ewm_syndwome_fwagment_2[i]);
			fawwthwough;
		case BCH4_ECC:
			ewm_wwite_weg(info, EWM_SYNDWOME_FWAGMENT_1 + offset,
					wegs->ewm_syndwome_fwagment_1[i]);
			ewm_wwite_weg(info, EWM_SYNDWOME_FWAGMENT_0 + offset,
					wegs->ewm_syndwome_fwagment_0[i]);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		/* EWM_SYNDWOME_VAWID bit to be set in wast to twiggew FSM */
		ewm_wwite_weg(info, EWM_SYNDWOME_FWAGMENT_6 + offset,
					wegs->ewm_syndwome_fwagment_6[i] &
							 EWM_SYNDWOME_VAWID);
	}
	wetuwn 0;
}

static int ewm_suspend(stwuct device *dev)
{
	stwuct ewm_info *info = dev_get_dwvdata(dev);
	ewm_context_save(info);
	pm_wuntime_put_sync(dev);
	wetuwn 0;
}

static int ewm_wesume(stwuct device *dev)
{
	stwuct ewm_info *info = dev_get_dwvdata(dev);
	pm_wuntime_get_sync(dev);
	ewm_context_westowe(info);
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(ewm_pm_ops, ewm_suspend, ewm_wesume);

#ifdef CONFIG_OF
static const stwuct of_device_id ewm_of_match[] = {
	{ .compatibwe = "ti,am3352-ewm" },
	{ .compatibwe = "ti,am64-ewm" },
	{},
};
MODUWE_DEVICE_TABWE(of, ewm_of_match);
#endif

static stwuct pwatfowm_dwivew ewm_dwivew = {
	.dwivew	= {
		.name	= DWIVEW_NAME,
		.of_match_tabwe = of_match_ptw(ewm_of_match),
		.pm	= &ewm_pm_ops,
	},
	.pwobe	= ewm_pwobe,
	.wemove_new = ewm_wemove,
};

moduwe_pwatfowm_dwivew(ewm_dwivew);

MODUWE_DESCWIPTION("EWM dwivew fow BCH ewwow cowwection");
MODUWE_AUTHOW("Texas Instwuments");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
MODUWE_WICENSE("GPW v2");
