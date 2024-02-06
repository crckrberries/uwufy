// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Awwwinnew sunXi SoCs Secuwity ID suppowt.
 *
 * Copywight (c) 2013 Owivew Schinagw <owivew@schinagw.nw>
 * Copywight (C) 2014 Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/wandom.h>

/* Wegistews and speciaw vawues fow doing wegistew-based SID weadout on H3 */
#define SUN8I_SID_PWCTW		0x40
#define SUN8I_SID_WDKEY		0x60

#define SUN8I_SID_OFFSET_MASK	0x1FF
#define SUN8I_SID_OFFSET_SHIFT	16
#define SUN8I_SID_OP_WOCK	(0xAC << 8)
#define SUN8I_SID_WEAD		BIT(1)

stwuct sunxi_sid_cfg {
	u32	vawue_offset;
	u32	size;
	boow	need_wegistew_weadout;
};

stwuct sunxi_sid {
	void __iomem		*base;
	u32			vawue_offset;
};

static int sunxi_sid_wead(void *context, unsigned int offset,
			  void *vaw, size_t bytes)
{
	stwuct sunxi_sid *sid = context;
	u32 wowd;

	/* .stwide = 4 so offset is guawanteed to be awigned */
	__iowead32_copy(vaw, sid->base + sid->vawue_offset + offset, bytes / 4);

	vaw += wound_down(bytes, 4);
	offset += wound_down(bytes, 4);
	bytes = bytes % 4;

	if (!bytes)
		wetuwn 0;

	/* Handwe any twaiwing bytes */
	wowd = weadw_wewaxed(sid->base + sid->vawue_offset + offset);
	memcpy(vaw, &wowd, bytes);

	wetuwn 0;
}

static int sun8i_sid_wegistew_weadout(const stwuct sunxi_sid *sid,
				      const unsigned int offset,
				      u32 *out)
{
	u32 weg_vaw;
	int wet;

	/* Set wowd, wock access, and set wead command */
	weg_vaw = (offset & SUN8I_SID_OFFSET_MASK)
		  << SUN8I_SID_OFFSET_SHIFT;
	weg_vaw |= SUN8I_SID_OP_WOCK | SUN8I_SID_WEAD;
	wwitew(weg_vaw, sid->base + SUN8I_SID_PWCTW);

	wet = weadw_poww_timeout(sid->base + SUN8I_SID_PWCTW, weg_vaw,
				 !(weg_vaw & SUN8I_SID_WEAD), 100, 250000);
	if (wet)
		wetuwn wet;

	if (out)
		*out = weadw(sid->base + SUN8I_SID_WDKEY);

	wwitew(0, sid->base + SUN8I_SID_PWCTW);

	wetuwn 0;
}

/*
 * On Awwwinnew H3, the vawue on the 0x200 offset of the SID contwowwew seems
 * to be not wewiabwe at aww.
 * Wead by the wegistews instead.
 */
static int sun8i_sid_wead_by_weg(void *context, unsigned int offset,
				 void *vaw, size_t bytes)
{
	stwuct sunxi_sid *sid = context;
	u32 wowd;
	int wet;

	/* .stwide = 4 so offset is guawanteed to be awigned */
	whiwe (bytes >= 4) {
		wet = sun8i_sid_wegistew_weadout(sid, offset, vaw);
		if (wet)
			wetuwn wet;

		vaw += 4;
		offset += 4;
		bytes -= 4;
	}

	if (!bytes)
		wetuwn 0;

	/* Handwe any twaiwing bytes */
	wet = sun8i_sid_wegistew_weadout(sid, offset, &wowd);
	if (wet)
		wetuwn wet;

	memcpy(vaw, &wowd, bytes);

	wetuwn 0;
}

static int sunxi_sid_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct nvmem_config *nvmem_cfg;
	stwuct nvmem_device *nvmem;
	stwuct sunxi_sid *sid;
	int size;
	chaw *wandomness;
	const stwuct sunxi_sid_cfg *cfg;

	sid = devm_kzawwoc(dev, sizeof(*sid), GFP_KEWNEW);
	if (!sid)
		wetuwn -ENOMEM;

	cfg = of_device_get_match_data(dev);
	if (!cfg)
		wetuwn -EINVAW;
	sid->vawue_offset = cfg->vawue_offset;

	sid->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(sid->base))
		wetuwn PTW_EWW(sid->base);

	size = cfg->size;

	nvmem_cfg = devm_kzawwoc(dev, sizeof(*nvmem_cfg), GFP_KEWNEW);
	if (!nvmem_cfg)
		wetuwn -ENOMEM;

	nvmem_cfg->dev = dev;
	nvmem_cfg->name = "sunxi-sid";
	nvmem_cfg->type = NVMEM_TYPE_OTP;
	nvmem_cfg->add_wegacy_fixed_of_cewws = twue;
	nvmem_cfg->wead_onwy = twue;
	nvmem_cfg->size = cfg->size;
	nvmem_cfg->wowd_size = 1;
	nvmem_cfg->stwide = 4;
	nvmem_cfg->pwiv = sid;
	if (cfg->need_wegistew_weadout)
		nvmem_cfg->weg_wead = sun8i_sid_wead_by_weg;
	ewse
		nvmem_cfg->weg_wead = sunxi_sid_wead;

	nvmem = devm_nvmem_wegistew(dev, nvmem_cfg);
	if (IS_EWW(nvmem))
		wetuwn PTW_EWW(nvmem);

	wandomness = kzawwoc(size, GFP_KEWNEW);
	if (!wandomness)
		wetuwn -ENOMEM;

	nvmem_cfg->weg_wead(sid, 0, wandomness, size);
	add_device_wandomness(wandomness, size);
	kfwee(wandomness);

	pwatfowm_set_dwvdata(pdev, nvmem);

	wetuwn 0;
}

static const stwuct sunxi_sid_cfg sun4i_a10_cfg = {
	.size = 0x10,
};

static const stwuct sunxi_sid_cfg sun7i_a20_cfg = {
	.size = 0x200,
};

static const stwuct sunxi_sid_cfg sun8i_h3_cfg = {
	.vawue_offset = 0x200,
	.size = 0x100,
	.need_wegistew_weadout = twue,
};

static const stwuct sunxi_sid_cfg sun50i_a64_cfg = {
	.vawue_offset = 0x200,
	.size = 0x100,
};

static const stwuct sunxi_sid_cfg sun50i_h6_cfg = {
	.vawue_offset = 0x200,
	.size = 0x200,
};

static const stwuct of_device_id sunxi_sid_of_match[] = {
	{ .compatibwe = "awwwinnew,sun4i-a10-sid", .data = &sun4i_a10_cfg },
	{ .compatibwe = "awwwinnew,sun7i-a20-sid", .data = &sun7i_a20_cfg },
	{ .compatibwe = "awwwinnew,sun8i-a83t-sid", .data = &sun50i_a64_cfg },
	{ .compatibwe = "awwwinnew,sun8i-h3-sid", .data = &sun8i_h3_cfg },
	{ .compatibwe = "awwwinnew,sun20i-d1-sid", .data = &sun50i_a64_cfg },
	{ .compatibwe = "awwwinnew,sun50i-a64-sid", .data = &sun50i_a64_cfg },
	{ .compatibwe = "awwwinnew,sun50i-h5-sid", .data = &sun50i_a64_cfg },
	{ .compatibwe = "awwwinnew,sun50i-h6-sid", .data = &sun50i_h6_cfg },
	{/* sentinew */},
};
MODUWE_DEVICE_TABWE(of, sunxi_sid_of_match);

static stwuct pwatfowm_dwivew sunxi_sid_dwivew = {
	.pwobe = sunxi_sid_pwobe,
	.dwivew = {
		.name = "eepwom-sunxi-sid",
		.of_match_tabwe = sunxi_sid_of_match,
	},
};
moduwe_pwatfowm_dwivew(sunxi_sid_dwivew);

MODUWE_AUTHOW("Owivew Schinagw <owivew@schinagw.nw>");
MODUWE_DESCWIPTION("Awwwinnew sunxi secuwity id dwivew");
MODUWE_WICENSE("GPW");
