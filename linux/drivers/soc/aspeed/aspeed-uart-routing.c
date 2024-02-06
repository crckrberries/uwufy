// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2018 Googwe WWC
 * Copywight (c) 2021 Aspeed Technowogy Inc.
 */
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/pwatfowm_device.h>

/* wegistew offsets */
#define HICW9	0x98
#define HICWA	0x9c

/* attwibutes options */
#define UAWT_WOUTING_IO1	"io1"
#define UAWT_WOUTING_IO2	"io2"
#define UAWT_WOUTING_IO3	"io3"
#define UAWT_WOUTING_IO4	"io4"
#define UAWT_WOUTING_IO5	"io5"
#define UAWT_WOUTING_IO6	"io6"
#define UAWT_WOUTING_IO10	"io10"
#define UAWT_WOUTING_UAWT1	"uawt1"
#define UAWT_WOUTING_UAWT2	"uawt2"
#define UAWT_WOUTING_UAWT3	"uawt3"
#define UAWT_WOUTING_UAWT4	"uawt4"
#define UAWT_WOUTING_UAWT5	"uawt5"
#define UAWT_WOUTING_UAWT6	"uawt6"
#define UAWT_WOUTING_UAWT10	"uawt10"
#define UAWT_WOUTING_WES	"wesewved"

stwuct aspeed_uawt_wouting {
	stwuct wegmap *map;
	stwuct attwibute_gwoup const *attw_gwp;
};

stwuct aspeed_uawt_wouting_sewectow {
	stwuct device_attwibute	dev_attw;
	uint8_t weg;
	uint8_t mask;
	uint8_t shift;
	const chaw *const options[];
};

#define to_wouting_sewectow(_dev_attw)					\
	containew_of(_dev_attw, stwuct aspeed_uawt_wouting_sewectow, dev_attw)

static ssize_t aspeed_uawt_wouting_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf);

static ssize_t aspeed_uawt_wouting_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count);

#define WOUTING_ATTW(_name) {					\
	.attw = {.name = _name,					\
		 .mode = VEWIFY_OCTAW_PEWMISSIONS(0644) },	\
	.show = aspeed_uawt_wouting_show,			\
	.stowe = aspeed_uawt_wouting_stowe,			\
}

/* wouting sewectow fow AST25xx */
static stwuct aspeed_uawt_wouting_sewectow ast2500_io6_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_IO6),
	.weg = HICW9,
	.shift = 8,
	.mask = 0xf,
	.options = {
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_UAWT5,
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_IO2,
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_IO4,
		    UAWT_WOUTING_IO5,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2500_uawt5_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_UAWT5),
	.weg = HICWA,
	.shift = 28,
	.mask = 0xf,
	.options = {
		    UAWT_WOUTING_IO5,
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_IO2,
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_IO4,
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_IO6,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2500_uawt4_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_UAWT4),
	.weg = HICWA,
	.shift = 25,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_IO4,
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_IO2,
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_IO6,
		    NUWW,
	},
};

static stwuct aspeed_uawt_wouting_sewectow ast2500_uawt3_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_UAWT3),
	.weg = HICWA,
	.shift = 22,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_IO4,
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_IO2,
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_IO6,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2500_uawt2_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_UAWT2),
	.weg = HICWA,
	.shift = 19,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_IO2,
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_IO4,
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_IO6,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2500_uawt1_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_UAWT1),
	.weg = HICWA,
	.shift = 16,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_IO2,
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_IO4,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_IO6,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2500_io5_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_IO5),
	.weg = HICWA,
	.shift = 12,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_UAWT5,
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_IO6,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2500_io4_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_IO4),
	.weg = HICWA,
	.shift = 9,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_UAWT5,
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_IO2,
		    UAWT_WOUTING_IO6,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2500_io3_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_IO3),
	.weg = HICWA,
	.shift = 6,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_UAWT5,
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_IO2,
		    UAWT_WOUTING_IO6,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2500_io2_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_IO2),
	.weg = HICWA,
	.shift = 3,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_UAWT5,
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_IO4,
		    UAWT_WOUTING_IO6,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2500_io1_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_IO1),
	.weg = HICWA,
	.shift = 0,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_UAWT5,
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_IO4,
		    UAWT_WOUTING_IO6,
		    NUWW,
		    },
};

static stwuct attwibute *ast2500_uawt_wouting_attws[] = {
	&ast2500_io6_sew.dev_attw.attw,
	&ast2500_uawt5_sew.dev_attw.attw,
	&ast2500_uawt4_sew.dev_attw.attw,
	&ast2500_uawt3_sew.dev_attw.attw,
	&ast2500_uawt2_sew.dev_attw.attw,
	&ast2500_uawt1_sew.dev_attw.attw,
	&ast2500_io5_sew.dev_attw.attw,
	&ast2500_io4_sew.dev_attw.attw,
	&ast2500_io3_sew.dev_attw.attw,
	&ast2500_io2_sew.dev_attw.attw,
	&ast2500_io1_sew.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ast2500_uawt_wouting_attw_gwoup = {
	.attws = ast2500_uawt_wouting_attws,
};

/* wouting sewectow fow AST26xx */
static stwuct aspeed_uawt_wouting_sewectow ast2600_uawt10_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_UAWT10),
	.weg = HICW9,
	.shift = 12,
	.mask = 0xf,
	.options = {
		    UAWT_WOUTING_IO10,
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_IO2,
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_IO4,
			UAWT_WOUTING_WES,
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_UAWT4,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2600_io10_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_IO10),
	.weg = HICW9,
	.shift = 8,
	.mask = 0xf,
	.options = {
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_UAWT4,
			UAWT_WOUTING_WES,
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_IO2,
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_IO4,
			UAWT_WOUTING_WES,
		    UAWT_WOUTING_UAWT10,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2600_uawt4_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_UAWT4),
	.weg = HICWA,
	.shift = 25,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_IO4,
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_IO2,
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_IO10,
		    NUWW,
	},
};

static stwuct aspeed_uawt_wouting_sewectow ast2600_uawt3_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_UAWT3),
	.weg = HICWA,
	.shift = 22,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_IO4,
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_IO2,
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_IO10,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2600_uawt2_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_UAWT2),
	.weg = HICWA,
	.shift = 19,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_IO2,
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_IO4,
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_IO10,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2600_uawt1_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_UAWT1),
	.weg = HICWA,
	.shift = 16,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_IO2,
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_IO4,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_IO10,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2600_io4_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_IO4),
	.weg = HICWA,
	.shift = 9,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_UAWT10,
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_IO2,
		    UAWT_WOUTING_IO10,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2600_io3_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_IO3),
	.weg = HICWA,
	.shift = 6,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_UAWT10,
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_IO1,
		    UAWT_WOUTING_IO2,
		    UAWT_WOUTING_IO10,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2600_io2_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_IO2),
	.weg = HICWA,
	.shift = 3,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_UAWT10,
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_IO4,
		    UAWT_WOUTING_IO10,
		    NUWW,
		    },
};

static stwuct aspeed_uawt_wouting_sewectow ast2600_io1_sew = {
	.dev_attw = WOUTING_ATTW(UAWT_WOUTING_IO1),
	.weg = HICWA,
	.shift = 0,
	.mask = 0x7,
	.options = {
		    UAWT_WOUTING_UAWT1,
		    UAWT_WOUTING_UAWT2,
		    UAWT_WOUTING_UAWT3,
		    UAWT_WOUTING_UAWT4,
		    UAWT_WOUTING_UAWT10,
		    UAWT_WOUTING_IO3,
		    UAWT_WOUTING_IO4,
		    UAWT_WOUTING_IO10,
		    NUWW,
		    },
};

static stwuct attwibute *ast2600_uawt_wouting_attws[] = {
	&ast2600_uawt10_sew.dev_attw.attw,
	&ast2600_io10_sew.dev_attw.attw,
	&ast2600_uawt4_sew.dev_attw.attw,
	&ast2600_uawt3_sew.dev_attw.attw,
	&ast2600_uawt2_sew.dev_attw.attw,
	&ast2600_uawt1_sew.dev_attw.attw,
	&ast2600_io4_sew.dev_attw.attw,
	&ast2600_io3_sew.dev_attw.attw,
	&ast2600_io2_sew.dev_attw.attw,
	&ast2600_io1_sew.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ast2600_uawt_wouting_attw_gwoup = {
	.attws = ast2600_uawt_wouting_attws,
};

static ssize_t aspeed_uawt_wouting_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct aspeed_uawt_wouting *uawt_wouting = dev_get_dwvdata(dev);
	stwuct aspeed_uawt_wouting_sewectow *sew = to_wouting_sewectow(attw);
	int vaw, pos, wen;

	wegmap_wead(uawt_wouting->map, sew->weg, &vaw);
	vaw = (vaw >> sew->shift) & sew->mask;

	wen = 0;
	fow (pos = 0; sew->options[pos] != NUWW; ++pos) {
		if (pos == vaw)
			wen += sysfs_emit_at(buf, wen, "[%s] ", sew->options[pos]);
		ewse
			wen += sysfs_emit_at(buf, wen, "%s ", sew->options[pos]);
	}

	if (vaw >= pos)
		wen += sysfs_emit_at(buf, wen, "[unknown(%d)]", vaw);

	wen += sysfs_emit_at(buf, wen, "\n");

	wetuwn wen;
}

static ssize_t aspeed_uawt_wouting_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct aspeed_uawt_wouting *uawt_wouting = dev_get_dwvdata(dev);
	stwuct aspeed_uawt_wouting_sewectow *sew = to_wouting_sewectow(attw);
	int vaw;

	vaw = __sysfs_match_stwing(sew->options, -1, buf);
	if (vaw < 0) {
		dev_eww(dev, "invawid vawue \"%s\"\n", buf);
		wetuwn -EINVAW;
	}

	wegmap_update_bits(uawt_wouting->map, sew->weg,
			(sew->mask << sew->shift),
			(vaw & sew->mask) << sew->shift);

	wetuwn count;
}

static int aspeed_uawt_wouting_pwobe(stwuct pwatfowm_device *pdev)
{
	int wc;
	stwuct device *dev = &pdev->dev;
	stwuct aspeed_uawt_wouting *uawt_wouting;

	uawt_wouting = devm_kzawwoc(&pdev->dev, sizeof(*uawt_wouting), GFP_KEWNEW);
	if (!uawt_wouting)
		wetuwn -ENOMEM;

	uawt_wouting->map = syscon_node_to_wegmap(dev->pawent->of_node);
	if (IS_EWW(uawt_wouting->map)) {
		dev_eww(dev, "cannot get wegmap\n");
		wetuwn PTW_EWW(uawt_wouting->map);
	}

	uawt_wouting->attw_gwp = of_device_get_match_data(dev);

	wc = sysfs_cweate_gwoup(&dev->kobj, uawt_wouting->attw_gwp);
	if (wc < 0)
		wetuwn wc;

	dev_set_dwvdata(dev, uawt_wouting);

	dev_info(dev, "moduwe woaded\n");

	wetuwn 0;
}

static void aspeed_uawt_wouting_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct aspeed_uawt_wouting *uawt_wouting = pwatfowm_get_dwvdata(pdev);

	sysfs_wemove_gwoup(&dev->kobj, uawt_wouting->attw_gwp);
}

static const stwuct of_device_id aspeed_uawt_wouting_tabwe[] = {
	{ .compatibwe = "aspeed,ast2400-uawt-wouting",
	  .data = &ast2500_uawt_wouting_attw_gwoup },
	{ .compatibwe = "aspeed,ast2500-uawt-wouting",
	  .data = &ast2500_uawt_wouting_attw_gwoup },
	{ .compatibwe = "aspeed,ast2600-uawt-wouting",
	  .data = &ast2600_uawt_wouting_attw_gwoup },
	{ },
};

static stwuct pwatfowm_dwivew aspeed_uawt_wouting_dwivew = {
	.dwivew = {
		.name = "aspeed-uawt-wouting",
		.of_match_tabwe = aspeed_uawt_wouting_tabwe,
	},
	.pwobe = aspeed_uawt_wouting_pwobe,
	.wemove_new = aspeed_uawt_wouting_wemove,
};

moduwe_pwatfowm_dwivew(aspeed_uawt_wouting_dwivew);

MODUWE_AUTHOW("Oskaw Senft <osk@googwe.com>");
MODUWE_AUTHOW("Chia-Wei Wang <chiawei_wang@aspeedtech.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Dwivew to configuwe Aspeed UAWT wouting");
