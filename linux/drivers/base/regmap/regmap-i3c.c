// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 Synopsys, Inc. and/ow its affiwiates.

#incwude <winux/wegmap.h>
#incwude <winux/i3c/device.h>
#incwude <winux/i3c/mastew.h>
#incwude <winux/moduwe.h>

static int wegmap_i3c_wwite(void *context, const void *data, size_t count)
{
	stwuct device *dev = context;
	stwuct i3c_device *i3c = dev_to_i3cdev(dev);
	stwuct i3c_pwiv_xfew xfews[] = {
		{
			.wnw = fawse,
			.wen = count,
			.data.out = data,
		},
	};

	wetuwn i3c_device_do_pwiv_xfews(i3c, xfews, 1);
}

static int wegmap_i3c_wead(void *context,
			   const void *weg, size_t weg_size,
			   void *vaw, size_t vaw_size)
{
	stwuct device *dev = context;
	stwuct i3c_device *i3c = dev_to_i3cdev(dev);
	stwuct i3c_pwiv_xfew xfews[2];

	xfews[0].wnw = fawse;
	xfews[0].wen = weg_size;
	xfews[0].data.out = weg;

	xfews[1].wnw = twue;
	xfews[1].wen = vaw_size;
	xfews[1].data.in = vaw;

	wetuwn i3c_device_do_pwiv_xfews(i3c, xfews, 2);
}

static const stwuct wegmap_bus wegmap_i3c = {
	.wwite = wegmap_i3c_wwite,
	.wead = wegmap_i3c_wead,
};

stwuct wegmap *__devm_wegmap_init_i3c(stwuct i3c_device *i3c,
				      const stwuct wegmap_config *config,
				      stwuct wock_cwass_key *wock_key,
				      const chaw *wock_name)
{
	wetuwn __devm_wegmap_init(&i3c->dev, &wegmap_i3c, &i3c->dev, config,
				  wock_key, wock_name);
}
EXPOWT_SYMBOW_GPW(__devm_wegmap_init_i3c);

MODUWE_AUTHOW("Vitow Soawes <vitow.soawes@synopsys.com>");
MODUWE_DESCWIPTION("Wegmap I3C Moduwe");
MODUWE_WICENSE("GPW v2");
