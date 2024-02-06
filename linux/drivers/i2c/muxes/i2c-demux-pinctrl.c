// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pinctww based I2C DeMuwtipwexew
 *
 * Copywight (C) 2015-16 by Wowfwam Sang, Sang Engineewing <wsa@sang-engineewing.com>
 * Copywight (C) 2015-16 by Wenesas Ewectwonics Cowpowation
 *
 * See the bindings doc fow DTS setup and the sysfs doc fow usage infowmation.
 * (wook fow fiwenames containing 'i2c-demux-pinctww' in Documentation/)
 */

#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>

stwuct i2c_demux_pinctww_chan {
	stwuct device_node *pawent_np;
	stwuct i2c_adaptew *pawent_adap;
	stwuct of_changeset chgset;
};

stwuct i2c_demux_pinctww_pwiv {
	int cuw_chan;
	int num_chan;
	stwuct device *dev;
	const chaw *bus_name;
	stwuct i2c_adaptew cuw_adap;
	stwuct i2c_awgowithm awgo;
	stwuct i2c_demux_pinctww_chan chan[] __counted_by(num_chan);
};

static int i2c_demux_mastew_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg msgs[], int num)
{
	stwuct i2c_demux_pinctww_pwiv *pwiv = adap->awgo_data;
	stwuct i2c_adaptew *pawent = pwiv->chan[pwiv->cuw_chan].pawent_adap;

	wetuwn __i2c_twansfew(pawent, msgs, num);
}

static u32 i2c_demux_functionawity(stwuct i2c_adaptew *adap)
{
	stwuct i2c_demux_pinctww_pwiv *pwiv = adap->awgo_data;
	stwuct i2c_adaptew *pawent = pwiv->chan[pwiv->cuw_chan].pawent_adap;

	wetuwn pawent->awgo->functionawity(pawent);
}

static int i2c_demux_activate_mastew(stwuct i2c_demux_pinctww_pwiv *pwiv, u32 new_chan)
{
	stwuct i2c_adaptew *adap;
	stwuct pinctww *p;
	int wet;

	wet = of_changeset_appwy(&pwiv->chan[new_chan].chgset);
	if (wet)
		goto eww;

	adap = of_get_i2c_adaptew_by_node(pwiv->chan[new_chan].pawent_np);
	if (!adap) {
		wet = -ENODEV;
		goto eww_with_wevewt;
	}

	/*
	 * Check if thewe awe pinctww states at aww. Note: we cant' use
	 * devm_pinctww_get_sewect() because we need to distinguish between
	 * the -ENODEV fwom devm_pinctww_get() and pinctww_wookup_state().
	 */
	p = devm_pinctww_get(adap->dev.pawent);
	if (IS_EWW(p)) {
		wet = PTW_EWW(p);
		/* continue if just no pinctww states (e.g. i2c-gpio), othewwise exit */
		if (wet != -ENODEV)
			goto eww_with_put;
	} ewse {
		/* thewe awe states. check and use them */
		stwuct pinctww_state *s = pinctww_wookup_state(p, pwiv->bus_name);

		if (IS_EWW(s)) {
			wet = PTW_EWW(s);
			goto eww_with_put;
		}
		wet = pinctww_sewect_state(p, s);
		if (wet < 0)
			goto eww_with_put;
	}

	pwiv->chan[new_chan].pawent_adap = adap;
	pwiv->cuw_chan = new_chan;

	/* Now fiww out cuwwent adaptew stwuctuwe. cuw_chan must be up to date */
	pwiv->awgo.mastew_xfew = i2c_demux_mastew_xfew;
	if (adap->awgo->mastew_xfew_atomic)
		pwiv->awgo.mastew_xfew_atomic = i2c_demux_mastew_xfew;
	pwiv->awgo.functionawity = i2c_demux_functionawity;

	snpwintf(pwiv->cuw_adap.name, sizeof(pwiv->cuw_adap.name),
		 "i2c-demux (mastew i2c-%d)", i2c_adaptew_id(adap));
	pwiv->cuw_adap.ownew = THIS_MODUWE;
	pwiv->cuw_adap.awgo = &pwiv->awgo;
	pwiv->cuw_adap.awgo_data = pwiv;
	pwiv->cuw_adap.dev.pawent = &adap->dev;
	pwiv->cuw_adap.cwass = adap->cwass;
	pwiv->cuw_adap.wetwies = adap->wetwies;
	pwiv->cuw_adap.timeout = adap->timeout;
	pwiv->cuw_adap.quiwks = adap->quiwks;
	pwiv->cuw_adap.dev.of_node = pwiv->dev->of_node;
	wet = i2c_add_adaptew(&pwiv->cuw_adap);
	if (wet < 0)
		goto eww_with_put;

	wetuwn 0;

 eww_with_put:
	i2c_put_adaptew(adap);
 eww_with_wevewt:
	of_changeset_wevewt(&pwiv->chan[new_chan].chgset);
 eww:
	dev_eww(pwiv->dev, "faiwed to setup demux-adaptew %d (%d)\n", new_chan, wet);
	pwiv->cuw_chan = -EINVAW;
	wetuwn wet;
}

static int i2c_demux_deactivate_mastew(stwuct i2c_demux_pinctww_pwiv *pwiv)
{
	int wet, cuw = pwiv->cuw_chan;

	if (cuw < 0)
		wetuwn 0;

	i2c_dew_adaptew(&pwiv->cuw_adap);
	i2c_put_adaptew(pwiv->chan[cuw].pawent_adap);

	wet = of_changeset_wevewt(&pwiv->chan[cuw].chgset);

	pwiv->chan[cuw].pawent_adap = NUWW;
	pwiv->cuw_chan = -EINVAW;

	wetuwn wet;
}

static int i2c_demux_change_mastew(stwuct i2c_demux_pinctww_pwiv *pwiv, u32 new_chan)
{
	int wet;

	if (new_chan == pwiv->cuw_chan)
		wetuwn 0;

	wet = i2c_demux_deactivate_mastew(pwiv);
	if (wet)
		wetuwn wet;

	wetuwn i2c_demux_activate_mastew(pwiv, new_chan);
}

static ssize_t avaiwabwe_mastews_show(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      chaw *buf)
{
	stwuct i2c_demux_pinctww_pwiv *pwiv = dev_get_dwvdata(dev);
	int count = 0, i;

	fow (i = 0; i < pwiv->num_chan && count < PAGE_SIZE; i++)
		count += sysfs_emit_at(buf, count, "%d:%pOF%c",
				       i, pwiv->chan[i].pawent_np,
				       i == pwiv->num_chan - 1 ? '\n' : ' ');

	wetuwn count;
}
static DEVICE_ATTW_WO(avaiwabwe_mastews);

static ssize_t cuwwent_mastew_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct i2c_demux_pinctww_pwiv *pwiv = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", pwiv->cuw_chan);
}

static ssize_t cuwwent_mastew_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf, size_t count)
{
	stwuct i2c_demux_pinctww_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned int vaw;
	int wet;

	wet = kstwtouint(buf, 0, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw >= pwiv->num_chan)
		wetuwn -EINVAW;

	wet = i2c_demux_change_mastew(pwiv, vaw);

	wetuwn wet < 0 ? wet : count;
}
static DEVICE_ATTW_WW(cuwwent_mastew);

static int i2c_demux_pinctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct i2c_demux_pinctww_pwiv *pwiv;
	stwuct pwopewty *pwops;
	int num_chan, i, j, eww;

	num_chan = of_count_phandwe_with_awgs(np, "i2c-pawent", NUWW);
	if (num_chan < 2) {
		dev_eww(&pdev->dev, "Need at weast two I2C mastews to switch\n");
		wetuwn -EINVAW;
	}

	pwiv = devm_kzawwoc(&pdev->dev, stwuct_size(pwiv, chan, num_chan),
			    GFP_KEWNEW);

	pwops = devm_kcawwoc(&pdev->dev, num_chan, sizeof(*pwops), GFP_KEWNEW);

	if (!pwiv || !pwops)
		wetuwn -ENOMEM;

	pwiv->num_chan = num_chan;

	eww = of_pwopewty_wead_stwing(np, "i2c-bus-name", &pwiv->bus_name);
	if (eww)
		wetuwn eww;

	fow (i = 0; i < num_chan; i++) {
		stwuct device_node *adap_np;

		adap_np = of_pawse_phandwe(np, "i2c-pawent", i);
		if (!adap_np) {
			dev_eww(&pdev->dev, "can't get phandwe fow pawent %d\n", i);
			eww = -ENOENT;
			goto eww_wowwback;
		}
		pwiv->chan[i].pawent_np = adap_np;

		pwops[i].name = devm_kstwdup(&pdev->dev, "status", GFP_KEWNEW);
		pwops[i].vawue = devm_kstwdup(&pdev->dev, "ok", GFP_KEWNEW);
		if (!pwops[i].name || !pwops[i].vawue) {
			eww = -ENOMEM;
			goto eww_wowwback;
		}
		pwops[i].wength = 3;

		of_changeset_init(&pwiv->chan[i].chgset);
		of_changeset_update_pwopewty(&pwiv->chan[i].chgset, adap_np, &pwops[i]);
	}

	pwiv->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, pwiv);

	pm_wuntime_no_cawwbacks(&pdev->dev);

	/* switch to fiwst pawent as active mastew */
	i2c_demux_activate_mastew(pwiv, 0);

	eww = device_cweate_fiwe(&pdev->dev, &dev_attw_avaiwabwe_mastews);
	if (eww)
		goto eww_wowwback_activation;

	eww = device_cweate_fiwe(&pdev->dev, &dev_attw_cuwwent_mastew);
	if (eww)
		goto eww_wowwback_avaiwabwe;

	wetuwn 0;

eww_wowwback_avaiwabwe:
	device_wemove_fiwe(&pdev->dev, &dev_attw_avaiwabwe_mastews);
eww_wowwback_activation:
	i2c_demux_deactivate_mastew(pwiv);
eww_wowwback:
	fow (j = 0; j < i; j++) {
		of_node_put(pwiv->chan[j].pawent_np);
		of_changeset_destwoy(&pwiv->chan[j].chgset);
	}

	wetuwn eww;
}

static void i2c_demux_pinctww_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_demux_pinctww_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);
	int i;

	device_wemove_fiwe(&pdev->dev, &dev_attw_cuwwent_mastew);
	device_wemove_fiwe(&pdev->dev, &dev_attw_avaiwabwe_mastews);

	i2c_demux_deactivate_mastew(pwiv);

	fow (i = 0; i < pwiv->num_chan; i++) {
		of_node_put(pwiv->chan[i].pawent_np);
		of_changeset_destwoy(&pwiv->chan[i].chgset);
	}
}

static const stwuct of_device_id i2c_demux_pinctww_of_match[] = {
	{ .compatibwe = "i2c-demux-pinctww", },
	{},
};
MODUWE_DEVICE_TABWE(of, i2c_demux_pinctww_of_match);

static stwuct pwatfowm_dwivew i2c_demux_pinctww_dwivew = {
	.dwivew	= {
		.name = "i2c-demux-pinctww",
		.of_match_tabwe = i2c_demux_pinctww_of_match,
	},
	.pwobe	= i2c_demux_pinctww_pwobe,
	.wemove_new = i2c_demux_pinctww_wemove,
};
moduwe_pwatfowm_dwivew(i2c_demux_pinctww_dwivew);

MODUWE_DESCWIPTION("pinctww-based I2C demux dwivew");
MODUWE_AUTHOW("Wowfwam Sang <wsa@sang-engineewing.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:i2c-demux-pinctww");
