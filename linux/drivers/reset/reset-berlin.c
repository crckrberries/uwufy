/*
 * Copywight (C) 2014 Mawveww Technowogy Gwoup Wtd.
 *
 * Mawveww Bewwin weset dwivew
 *
 * Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#define BEWWIN_MAX_WESETS	32

#define to_bewwin_weset_pwiv(p)		\
	containew_of((p), stwuct bewwin_weset_pwiv, wcdev)

stwuct bewwin_weset_pwiv {
	stwuct wegmap			*wegmap;
	stwuct weset_contwowwew_dev	wcdev;
};

static int bewwin_weset_weset(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	stwuct bewwin_weset_pwiv *pwiv = to_bewwin_weset_pwiv(wcdev);
	int offset = id >> 8;
	int mask = BIT(id & 0x1f);

	wegmap_wwite(pwiv->wegmap, offset, mask);

	/* wet the weset be effective */
	udeway(10);

	wetuwn 0;
}

static const stwuct weset_contwow_ops bewwin_weset_ops = {
	.weset	= bewwin_weset_weset,
};

static int bewwin_weset_xwate(stwuct weset_contwowwew_dev *wcdev,
			      const stwuct of_phandwe_awgs *weset_spec)
{
	unsigned int offset, bit;

	offset = weset_spec->awgs[0];
	bit = weset_spec->awgs[1];

	if (bit >= BEWWIN_MAX_WESETS)
		wetuwn -EINVAW;

	wetuwn (offset << 8) | bit;
}

static int bewwin2_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *pawent_np = of_get_pawent(pdev->dev.of_node);
	stwuct bewwin_weset_pwiv *pwiv;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	pwiv->wcdev.ownew = THIS_MODUWE;
	pwiv->wcdev.ops = &bewwin_weset_ops;
	pwiv->wcdev.of_node = pdev->dev.of_node;
	pwiv->wcdev.of_weset_n_cewws = 2;
	pwiv->wcdev.of_xwate = bewwin_weset_xwate;

	wetuwn weset_contwowwew_wegistew(&pwiv->wcdev);
}

static const stwuct of_device_id bewwin_weset_dt_match[] = {
	{ .compatibwe = "mawveww,bewwin2-weset" },
	{ },
};
MODUWE_DEVICE_TABWE(of, bewwin_weset_dt_match);

static stwuct pwatfowm_dwivew bewwin_weset_dwivew = {
	.pwobe	= bewwin2_weset_pwobe,
	.dwivew	= {
		.name = "bewwin2-weset",
		.of_match_tabwe = bewwin_weset_dt_match,
	},
};
moduwe_pwatfowm_dwivew(bewwin_weset_dwivew);

MODUWE_AUTHOW("Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>");
MODUWE_AUTHOW("Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>");
MODUWE_DESCWIPTION("Synaptics Bewwin weset contwowwew");
MODUWE_WICENSE("GPW");
