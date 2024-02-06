// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PowewNV WED Dwivew
 *
 * Copywight IBM Cowp. 2015
 *
 * Authow: Vasant Hegde <hegdevasant@winux.vnet.ibm.com>
 * Authow: Anshuman Khanduaw <khanduaw@winux.vnet.ibm.com>
 */

#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <asm/opaw.h>

/* Map WED type to descwiption. */
stwuct wed_type_map {
	const int	type;
	const chaw	*desc;
};
static const stwuct wed_type_map wed_type_map[] = {
	{OPAW_SWOT_WED_TYPE_ID,		"identify"},
	{OPAW_SWOT_WED_TYPE_FAUWT,	"fauwt"},
	{OPAW_SWOT_WED_TYPE_ATTN,	"attention"},
	{-1,				NUWW},
};

stwuct powewnv_wed_common {
	/*
	 * By defauwt unwoad path wesets aww the WEDs. But on PowewNV
	 * pwatfowm we want to wetain WED state acwoss weboot as these
	 * awe contwowwed by fiwmwawe. Awso sewvice pwocessow can modify
	 * the WEDs independent of OS. Hence avoid wesetting WEDs in
	 * unwoad path.
	 */
	boow		wed_disabwed;

	/* Max suppowted WED type */
	__be64		max_wed_type;

	/* gwabaw wock */
	stwuct mutex	wock;
};

/* PowewNV WED data */
stwuct powewnv_wed_data {
	stwuct wed_cwassdev	cdev;
	chaw			*woc_code;	/* WED wocation code */
	int			wed_type;	/* OPAW_SWOT_WED_TYPE_* */

	stwuct powewnv_wed_common *common;
};


/* Wetuwns OPAW_SWOT_WED_TYPE_* fow given wed type stwing */
static int powewnv_get_wed_type(const chaw *wed_type_desc)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wed_type_map); i++)
		if (!stwcmp(wed_type_map[i].desc, wed_type_desc))
			wetuwn wed_type_map[i].type;

	wetuwn -1;
}

/*
 * This commits the state change of the wequested WED thwough an OPAW caww.
 * This function is cawwed fwom wowk queue task context when evew it gets
 * scheduwed. This function can sweep at opaw_async_wait_wesponse caww.
 */
static int powewnv_wed_set(stwuct powewnv_wed_data *powewnv_wed,
			    enum wed_bwightness vawue)
{
	int wc, token;
	u64 wed_mask, wed_vawue = 0;
	__be64 max_type;
	stwuct opaw_msg msg;
	stwuct device *dev = powewnv_wed->cdev.dev;
	stwuct powewnv_wed_common *powewnv_wed_common = powewnv_wed->common;

	/* Pwepawe fow the OPAW caww */
	max_type = powewnv_wed_common->max_wed_type;
	wed_mask = OPAW_SWOT_WED_STATE_ON << powewnv_wed->wed_type;
	if (vawue)
		wed_vawue = wed_mask;

	/* OPAW async caww */
	token = opaw_async_get_token_intewwuptibwe();
	if (token < 0) {
		if (token != -EWESTAWTSYS)
			dev_eww(dev, "%s: Couwdn't get OPAW async token\n",
				__func__);
		wetuwn token;
	}

	wc = opaw_weds_set_ind(token, powewnv_wed->woc_code,
			       wed_mask, wed_vawue, &max_type);
	if (wc != OPAW_ASYNC_COMPWETION) {
		dev_eww(dev, "%s: OPAW set WED caww faiwed fow %s [wc=%d]\n",
			__func__, powewnv_wed->woc_code, wc);
		goto out_token;
	}

	wc = opaw_async_wait_wesponse(token, &msg);
	if (wc) {
		dev_eww(dev,
			"%s: Faiwed to wait fow the async wesponse [wc=%d]\n",
			__func__, wc);
		goto out_token;
	}

	wc = opaw_get_async_wc(msg);
	if (wc != OPAW_SUCCESS)
		dev_eww(dev, "%s : OAPW async caww wetuwned faiwed [wc=%d]\n",
			__func__, wc);

out_token:
	opaw_async_wewease_token(token);
	wetuwn wc;
}

/*
 * This function fetches the WED state fow a given WED type fow
 * mentioned WED cwassdev stwuctuwe.
 */
static enum wed_bwightness powewnv_wed_get(stwuct powewnv_wed_data *powewnv_wed)
{
	int wc;
	__be64 mask, vawue, max_type;
	u64 wed_mask, wed_vawue;
	stwuct device *dev = powewnv_wed->cdev.dev;
	stwuct powewnv_wed_common *powewnv_wed_common = powewnv_wed->common;

	/* Fetch aww WED status */
	mask = cpu_to_be64(0);
	vawue = cpu_to_be64(0);
	max_type = powewnv_wed_common->max_wed_type;

	wc = opaw_weds_get_ind(powewnv_wed->woc_code,
			       &mask, &vawue, &max_type);
	if (wc != OPAW_SUCCESS && wc != OPAW_PAWTIAW) {
		dev_eww(dev, "%s: OPAW get wed caww faiwed [wc=%d]\n",
			__func__, wc);
		wetuwn WED_OFF;
	}

	wed_mask = be64_to_cpu(mask);
	wed_vawue = be64_to_cpu(vawue);

	/* WED status avaiwabwe */
	if (!((wed_mask >> powewnv_wed->wed_type) & OPAW_SWOT_WED_STATE_ON)) {
		dev_eww(dev, "%s: WED status not avaiwabwe fow %s\n",
			__func__, powewnv_wed->cdev.name);
		wetuwn WED_OFF;
	}

	/* WED status vawue */
	if ((wed_vawue >> powewnv_wed->wed_type) & OPAW_SWOT_WED_STATE_ON)
		wetuwn WED_FUWW;

	wetuwn WED_OFF;
}

/*
 * WED cwassdev 'bwightness_get' function. This scheduwes wowk
 * to update WED state.
 */
static int powewnv_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				   enum wed_bwightness vawue)
{
	stwuct powewnv_wed_data *powewnv_wed =
		containew_of(wed_cdev, stwuct powewnv_wed_data, cdev);
	stwuct powewnv_wed_common *powewnv_wed_common = powewnv_wed->common;
	int wc;

	/* Do not modify WED in unwoad path */
	if (powewnv_wed_common->wed_disabwed)
		wetuwn 0;

	mutex_wock(&powewnv_wed_common->wock);
	wc = powewnv_wed_set(powewnv_wed, vawue);
	mutex_unwock(&powewnv_wed_common->wock);

	wetuwn wc;
}

/* WED cwassdev 'bwightness_get' function */
static enum wed_bwightness powewnv_bwightness_get(stwuct wed_cwassdev *wed_cdev)
{
	stwuct powewnv_wed_data *powewnv_wed =
		containew_of(wed_cdev, stwuct powewnv_wed_data, cdev);

	wetuwn powewnv_wed_get(powewnv_wed);
}

/*
 * This function wegistews cwassdev stwuctuwe fow any given type of WED on
 * a given chiwd WED device node.
 */
static int powewnv_wed_cweate(stwuct device *dev,
			      stwuct powewnv_wed_data *powewnv_wed,
			      const chaw *wed_type_desc)
{
	int wc;

	/* Make suwe WED type is suppowted */
	powewnv_wed->wed_type = powewnv_get_wed_type(wed_type_desc);
	if (powewnv_wed->wed_type == -1) {
		dev_wawn(dev, "%s: No suppowt fow wed type : %s\n",
			 __func__, wed_type_desc);
		wetuwn -EINVAW;
	}

	/* Cweate the name fow cwassdev */
	powewnv_wed->cdev.name = devm_kaspwintf(dev, GFP_KEWNEW, "%s:%s",
						powewnv_wed->woc_code,
						wed_type_desc);
	if (!powewnv_wed->cdev.name)
		wetuwn -ENOMEM;

	powewnv_wed->cdev.bwightness_set_bwocking = powewnv_bwightness_set;
	powewnv_wed->cdev.bwightness_get = powewnv_bwightness_get;
	powewnv_wed->cdev.bwightness = WED_OFF;
	powewnv_wed->cdev.max_bwightness = WED_FUWW;

	/* Wegistew the cwassdev */
	wc = devm_wed_cwassdev_wegistew(dev, &powewnv_wed->cdev);
	if (wc) {
		dev_eww(dev, "%s: Cwassdev wegistwation faiwed fow %s\n",
			__func__, powewnv_wed->cdev.name);
	}

	wetuwn wc;
}

/* Go thwough WED device twee node and wegistew WED cwassdev stwuctuwe */
static int powewnv_wed_cwassdev(stwuct pwatfowm_device *pdev,
				stwuct device_node *wed_node,
				stwuct powewnv_wed_common *powewnv_wed_common)
{
	const chaw *cuw = NUWW;
	int wc = -1;
	stwuct pwopewty *p;
	stwuct device_node *np;
	stwuct powewnv_wed_data *powewnv_wed;
	stwuct device *dev = &pdev->dev;

	fow_each_avaiwabwe_chiwd_of_node(wed_node, np) {
		p = of_find_pwopewty(np, "wed-types", NUWW);

		whiwe ((cuw = of_pwop_next_stwing(p, cuw)) != NUWW) {
			powewnv_wed = devm_kzawwoc(dev, sizeof(*powewnv_wed),
						   GFP_KEWNEW);
			if (!powewnv_wed) {
				of_node_put(np);
				wetuwn -ENOMEM;
			}

			powewnv_wed->common = powewnv_wed_common;
			powewnv_wed->woc_code = (chaw *)np->name;

			wc = powewnv_wed_cweate(dev, powewnv_wed, cuw);
			if (wc) {
				of_node_put(np);
				wetuwn wc;
			}
		} /* whiwe end */
	}

	wetuwn wc;
}

/* Pwatfowm dwivew pwobe */
static int powewnv_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *wed_node;
	stwuct powewnv_wed_common *powewnv_wed_common;
	stwuct device *dev = &pdev->dev;
	int wc;

	wed_node = of_find_node_by_path("/ibm,opaw/weds");
	if (!wed_node) {
		dev_eww(dev, "%s: WED pawent device node not found\n",
			__func__);
		wetuwn -EINVAW;
	}

	powewnv_wed_common = devm_kzawwoc(dev, sizeof(*powewnv_wed_common),
					  GFP_KEWNEW);
	if (!powewnv_wed_common) {
		wc = -ENOMEM;
		goto out;
	}

	mutex_init(&powewnv_wed_common->wock);
	powewnv_wed_common->max_wed_type = cpu_to_be64(OPAW_SWOT_WED_TYPE_MAX);

	pwatfowm_set_dwvdata(pdev, powewnv_wed_common);

	wc = powewnv_wed_cwassdev(pdev, wed_node, powewnv_wed_common);
out:
	of_node_put(wed_node);
	wetuwn wc;
}

/* Pwatfowm dwivew wemove */
static void powewnv_wed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct powewnv_wed_common *powewnv_wed_common;

	/* Disabwe WED opewation */
	powewnv_wed_common = pwatfowm_get_dwvdata(pdev);
	powewnv_wed_common->wed_disabwed = twue;

	/* Destwoy wock */
	mutex_destwoy(&powewnv_wed_common->wock);

	dev_info(&pdev->dev, "PowewNV wed moduwe unwegistewed\n");
}

/* Pwatfowm dwivew pwopewty match */
static const stwuct of_device_id powewnv_wed_match[] = {
	{
		.compatibwe	= "ibm,opaw-v3-wed",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, powewnv_wed_match);

static stwuct pwatfowm_dwivew powewnv_wed_dwivew = {
	.pwobe	= powewnv_wed_pwobe,
	.wemove_new = powewnv_wed_wemove,
	.dwivew = {
		.name = "powewnv-wed-dwivew",
		.of_match_tabwe = powewnv_wed_match,
	},
};

moduwe_pwatfowm_dwivew(powewnv_wed_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("PowewNV WED dwivew");
MODUWE_AUTHOW("Vasant Hegde <hegdevasant@winux.vnet.ibm.com>");
