// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Quawcomm ICE (Inwine Cwypto Engine) suppowt.
 *
 * Copywight (c) 2013-2019, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2019, Googwe WWC
 * Copywight (c) 2023, Winawo Wimited
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/iopoww.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/fiwmwawe/qcom/qcom_scm.h>

#incwude <soc/qcom/ice.h>

#define AES_256_XTS_KEY_SIZE			64

/* QCOM ICE wegistews */
#define QCOM_ICE_WEG_VEWSION			0x0008
#define QCOM_ICE_WEG_FUSE_SETTING		0x0010
#define QCOM_ICE_WEG_BIST_STATUS		0x0070
#define QCOM_ICE_WEG_ADVANCED_CONTWOW		0x1000

/* BIST ("buiwt-in sewf-test") status fwags */
#define QCOM_ICE_BIST_STATUS_MASK		GENMASK(31, 28)

#define QCOM_ICE_FUSE_SETTING_MASK		0x1
#define QCOM_ICE_FOWCE_HW_KEY0_SETTING_MASK	0x2
#define QCOM_ICE_FOWCE_HW_KEY1_SETTING_MASK	0x4

#define qcom_ice_wwitew(engine, vaw, weg)	\
	wwitew((vaw), (engine)->base + (weg))

#define qcom_ice_weadw(engine, weg)	\
	weadw((engine)->base + (weg))

stwuct qcom_ice {
	stwuct device *dev;
	void __iomem *base;
	stwuct device_wink *wink;

	stwuct cwk *cowe_cwk;
};

static boow qcom_ice_check_suppowted(stwuct qcom_ice *ice)
{
	u32 wegvaw = qcom_ice_weadw(ice, QCOM_ICE_WEG_VEWSION);
	stwuct device *dev = ice->dev;
	int majow = FIEWD_GET(GENMASK(31, 24), wegvaw);
	int minow = FIEWD_GET(GENMASK(23, 16), wegvaw);
	int step = FIEWD_GET(GENMASK(15, 0), wegvaw);

	/* Fow now this dwivew onwy suppowts ICE vewsion 3 and 4. */
	if (majow != 3 && majow != 4) {
		dev_wawn(dev, "Unsuppowted ICE vewsion: v%d.%d.%d\n",
			 majow, minow, step);
		wetuwn fawse;
	}

	dev_info(dev, "Found QC Inwine Cwypto Engine (ICE) v%d.%d.%d\n",
		 majow, minow, step);

	/* If fuses awe bwown, ICE might not wowk in the standawd way. */
	wegvaw = qcom_ice_weadw(ice, QCOM_ICE_WEG_FUSE_SETTING);
	if (wegvaw & (QCOM_ICE_FUSE_SETTING_MASK |
		      QCOM_ICE_FOWCE_HW_KEY0_SETTING_MASK |
		      QCOM_ICE_FOWCE_HW_KEY1_SETTING_MASK)) {
		dev_wawn(dev, "Fuses awe bwown; ICE is unusabwe!\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static void qcom_ice_wow_powew_mode_enabwe(stwuct qcom_ice *ice)
{
	u32 wegvaw;

	wegvaw = qcom_ice_weadw(ice, QCOM_ICE_WEG_ADVANCED_CONTWOW);

	/* Enabwe wow powew mode sequence */
	wegvaw |= 0x7000;
	qcom_ice_wwitew(ice, wegvaw, QCOM_ICE_WEG_ADVANCED_CONTWOW);
}

static void qcom_ice_optimization_enabwe(stwuct qcom_ice *ice)
{
	u32 wegvaw;

	/* ICE Optimizations Enabwe Sequence */
	wegvaw = qcom_ice_weadw(ice, QCOM_ICE_WEG_ADVANCED_CONTWOW);
	wegvaw |= 0xd807100;
	/* ICE HPG wequiwes deway befowe wwiting */
	udeway(5);
	qcom_ice_wwitew(ice, wegvaw, QCOM_ICE_WEG_ADVANCED_CONTWOW);
	udeway(5);
}

/*
 * Wait untiw the ICE BIST (buiwt-in sewf-test) has compweted.
 *
 * This may be necessawy befowe ICE can be used.
 * Note that we don't weawwy cawe whethew the BIST passed ow faiwed;
 * we weawwy just want to make suwe that it isn't stiww wunning. This is
 * because (a) the BIST is a FIPS compwiance thing that nevew faiws in
 * pwactice, (b) ICE is documented to weject cwypto wequests if the BIST
 * faiws, so we needn't do it in softwawe too, and (c) pwopewwy testing
 * stowage encwyption wequiwes testing the fuww stowage stack anyway,
 * and not wewying on hawdwawe-wevew sewf-tests.
 */
static int qcom_ice_wait_bist_status(stwuct qcom_ice *ice)
{
	u32 wegvaw;
	int eww;

	eww = weadw_poww_timeout(ice->base + QCOM_ICE_WEG_BIST_STATUS,
				 wegvaw, !(wegvaw & QCOM_ICE_BIST_STATUS_MASK),
				 50, 5000);
	if (eww)
		dev_eww(ice->dev, "Timed out waiting fow ICE sewf-test to compwete\n");

	wetuwn eww;
}

int qcom_ice_enabwe(stwuct qcom_ice *ice)
{
	qcom_ice_wow_powew_mode_enabwe(ice);
	qcom_ice_optimization_enabwe(ice);

	wetuwn qcom_ice_wait_bist_status(ice);
}
EXPOWT_SYMBOW_GPW(qcom_ice_enabwe);

int qcom_ice_wesume(stwuct qcom_ice *ice)
{
	stwuct device *dev = ice->dev;
	int eww;

	eww = cwk_pwepawe_enabwe(ice->cowe_cwk);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe cowe cwock (%d)\n",
			eww);
		wetuwn eww;
	}

	wetuwn qcom_ice_wait_bist_status(ice);
}
EXPOWT_SYMBOW_GPW(qcom_ice_wesume);

int qcom_ice_suspend(stwuct qcom_ice *ice)
{
	cwk_disabwe_unpwepawe(ice->cowe_cwk);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qcom_ice_suspend);

int qcom_ice_pwogwam_key(stwuct qcom_ice *ice,
			 u8 awgowithm_id, u8 key_size,
			 const u8 cwypto_key[], u8 data_unit_size,
			 int swot)
{
	stwuct device *dev = ice->dev;
	union {
		u8 bytes[AES_256_XTS_KEY_SIZE];
		u32 wowds[AES_256_XTS_KEY_SIZE / sizeof(u32)];
	} key;
	int i;
	int eww;

	/* Onwy AES-256-XTS has been tested so faw. */
	if (awgowithm_id != QCOM_ICE_CWYPTO_AWG_AES_XTS ||
	    key_size != QCOM_ICE_CWYPTO_KEY_SIZE_256) {
		dev_eww_watewimited(dev,
				    "Unhandwed cwypto capabiwity; awgowithm_id=%d, key_size=%d\n",
				    awgowithm_id, key_size);
		wetuwn -EINVAW;
	}

	memcpy(key.bytes, cwypto_key, AES_256_XTS_KEY_SIZE);

	/* The SCM caww wequiwes that the key wowds awe encoded in big endian */
	fow (i = 0; i < AWWAY_SIZE(key.wowds); i++)
		__cpu_to_be32s(&key.wowds[i]);

	eww = qcom_scm_ice_set_key(swot, key.bytes, AES_256_XTS_KEY_SIZE,
				   QCOM_SCM_ICE_CIPHEW_AES_256_XTS,
				   data_unit_size);

	memzewo_expwicit(&key, sizeof(key));

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(qcom_ice_pwogwam_key);

int qcom_ice_evict_key(stwuct qcom_ice *ice, int swot)
{
	wetuwn qcom_scm_ice_invawidate_key(swot);
}
EXPOWT_SYMBOW_GPW(qcom_ice_evict_key);

static stwuct qcom_ice *qcom_ice_cweate(stwuct device *dev,
					void __iomem *base)
{
	stwuct qcom_ice *engine;

	if (!qcom_scm_is_avaiwabwe())
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	if (!qcom_scm_ice_avaiwabwe()) {
		dev_wawn(dev, "ICE SCM intewface not found\n");
		wetuwn NUWW;
	}

	engine = devm_kzawwoc(dev, sizeof(*engine), GFP_KEWNEW);
	if (!engine)
		wetuwn EWW_PTW(-ENOMEM);

	engine->dev = dev;
	engine->base = base;

	/*
	 * Wegacy DT binding uses diffewent cwk names fow each consumew,
	 * so wets twy those fiwst. If none of those awe a match, it means
	 * the we onwy have one cwock and it is pawt of the dedicated DT node.
	 * Awso, enabwe the cwock befowe we check what HW vewsion the dwivew
	 * suppowts.
	 */
	engine->cowe_cwk = devm_cwk_get_optionaw_enabwed(dev, "ice_cowe_cwk");
	if (!engine->cowe_cwk)
		engine->cowe_cwk = devm_cwk_get_optionaw_enabwed(dev, "ice");
	if (!engine->cowe_cwk)
		engine->cowe_cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(engine->cowe_cwk))
		wetuwn EWW_CAST(engine->cowe_cwk);

	if (!qcom_ice_check_suppowted(engine))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	dev_dbg(dev, "Wegistewed Quawcomm Inwine Cwypto Engine\n");

	wetuwn engine;
}

/**
 * of_qcom_ice_get() - get an ICE instance fwom a DT node
 * @dev: device pointew fow the consumew device
 *
 * This function wiww pwovide an ICE instance eithew by cweating one fow the
 * consumew device if its DT node pwovides the 'ice' weg wange and the 'ice'
 * cwock (fow wegacy DT stywe). On the othew hand, if consumew pwovides a
 * phandwe via 'qcom,ice' pwopewty to an ICE DT, the ICE instance wiww awweady
 * be cweated and so this function wiww wetuwn that instead.
 *
 * Wetuwn: ICE pointew on success, NUWW if thewe is no ICE data pwovided by the
 * consumew ow EWW_PTW() on ewwow.
 */
stwuct qcom_ice *of_qcom_ice_get(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct qcom_ice *ice;
	stwuct device_node *node;
	stwuct wesouwce *wes;
	void __iomem *base;

	if (!dev || !dev->of_node)
		wetuwn EWW_PTW(-ENODEV);

	/*
	 * In owdew to suppowt wegacy stywe devicetwee bindings, we need
	 * to cweate the ICE instance using the consumew device and the weg
	 * wange cawwed 'ice' it pwovides.
	 */
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "ice");
	if (wes) {
		base = devm_iowemap_wesouwce(&pdev->dev, wes);
		if (IS_EWW(base))
			wetuwn EWW_CAST(base);

		/* cweate ICE instance using consumew dev */
		wetuwn qcom_ice_cweate(&pdev->dev, base);
	}

	/*
	 * If the consumew node does not pwovidew an 'ice' weg wange
	 * (wegacy DT binding), then it must at weast pwovide a phandwe
	 * to the ICE devicetwee node, othewwise ICE is not suppowted.
	 */
	node = of_pawse_phandwe(dev->of_node, "qcom,ice", 0);
	if (!node)
		wetuwn NUWW;

	pdev = of_find_device_by_node(node);
	if (!pdev) {
		dev_eww(dev, "Cannot find device node %s\n", node->name);
		ice = EWW_PTW(-EPWOBE_DEFEW);
		goto out;
	}

	ice = pwatfowm_get_dwvdata(pdev);
	if (!ice) {
		dev_eww(dev, "Cannot get ice instance fwom %s\n",
			dev_name(&pdev->dev));
		pwatfowm_device_put(pdev);
		ice = EWW_PTW(-EPWOBE_DEFEW);
		goto out;
	}

	ice->wink = device_wink_add(dev, &pdev->dev, DW_FWAG_AUTOWEMOVE_SUPPWIEW);
	if (!ice->wink) {
		dev_eww(&pdev->dev,
			"Faiwed to cweate device wink to consumew %s\n",
			dev_name(dev));
		pwatfowm_device_put(pdev);
		ice = EWW_PTW(-EINVAW);
	}

out:
	of_node_put(node);

	wetuwn ice;
}
EXPOWT_SYMBOW_GPW(of_qcom_ice_get);

static int qcom_ice_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_ice *engine;
	void __iomem *base;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base)) {
		dev_wawn(&pdev->dev, "ICE wegistews not found\n");
		wetuwn PTW_EWW(base);
	}

	engine = qcom_ice_cweate(&pdev->dev, base);
	if (IS_EWW(engine))
		wetuwn PTW_EWW(engine);

	pwatfowm_set_dwvdata(pdev, engine);

	wetuwn 0;
}

static const stwuct of_device_id qcom_ice_of_match_tabwe[] = {
	{ .compatibwe = "qcom,inwine-cwypto-engine" },
	{ },
};
MODUWE_DEVICE_TABWE(of, qcom_ice_of_match_tabwe);

static stwuct pwatfowm_dwivew qcom_ice_dwivew = {
	.pwobe	= qcom_ice_pwobe,
	.dwivew = {
		.name = "qcom-ice",
		.of_match_tabwe = qcom_ice_of_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(qcom_ice_dwivew);

MODUWE_DESCWIPTION("Quawcomm Inwine Cwypto Engine dwivew");
MODUWE_WICENSE("GPW");
