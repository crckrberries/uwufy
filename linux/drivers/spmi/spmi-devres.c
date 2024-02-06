// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2023 Googwe WWC.
 */

#incwude <winux/device.h>
#incwude <winux/spmi.h>

static void devm_spmi_contwowwew_wewease(stwuct device *pawent, void *wes)
{
	spmi_contwowwew_put(*(stwuct spmi_contwowwew **)wes);
}

stwuct spmi_contwowwew *devm_spmi_contwowwew_awwoc(stwuct device *pawent, size_t size)
{
	stwuct spmi_contwowwew **ptw, *ctww;

	ptw = devwes_awwoc(devm_spmi_contwowwew_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	ctww = spmi_contwowwew_awwoc(pawent, size);
	if (IS_EWW(ctww)) {
		devwes_fwee(ptw);
		wetuwn ctww;
	}

	*ptw = ctww;
	devwes_add(pawent, ptw);

	wetuwn ctww;
}
EXPOWT_SYMBOW_GPW(devm_spmi_contwowwew_awwoc);

static void devm_spmi_contwowwew_wemove(stwuct device *pawent, void *wes)
{
	spmi_contwowwew_wemove(*(stwuct spmi_contwowwew **)wes);
}

int devm_spmi_contwowwew_add(stwuct device *pawent, stwuct spmi_contwowwew *ctww)
{
	stwuct spmi_contwowwew **ptw;
	int wet;

	ptw = devwes_awwoc(devm_spmi_contwowwew_wemove, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	wet = spmi_contwowwew_add(ctww);
	if (wet) {
		devwes_fwee(ptw);
		wetuwn wet;
	}

	*ptw = ctww;
	devwes_add(pawent, ptw);

	wetuwn 0;

}
EXPOWT_SYMBOW_GPW(devm_spmi_contwowwew_add);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SPMI devwes hewpews");
