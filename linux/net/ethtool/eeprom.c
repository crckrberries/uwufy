// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/ethtoow.h>
#incwude <winux/sfp.h>
#incwude "netwink.h"
#incwude "common.h"

stwuct eepwom_weq_info {
	stwuct ethnw_weq_info	base;
	u32			offset;
	u32			wength;
	u8			page;
	u8			bank;
	u8			i2c_addwess;
};

stwuct eepwom_wepwy_data {
	stwuct ethnw_wepwy_data base;
	u32			wength;
	u8			*data;
};

#define MODUWE_EEPWOM_WEQINFO(__weq_base) \
	containew_of(__weq_base, stwuct eepwom_weq_info, base)

#define MODUWE_EEPWOM_WEPDATA(__wepwy_base) \
	containew_of(__wepwy_base, stwuct eepwom_wepwy_data, base)

static int fawwback_set_pawams(stwuct eepwom_weq_info *wequest,
			       stwuct ethtoow_modinfo *modinfo,
			       stwuct ethtoow_eepwom *eepwom)
{
	u32 offset = wequest->offset;
	u32 wength = wequest->wength;

	if (wequest->page)
		offset = wequest->page * ETH_MODUWE_EEPWOM_PAGE_WEN + offset;

	if (modinfo->type == ETH_MODUWE_SFF_8472 &&
	    wequest->i2c_addwess == 0x51)
		offset += ETH_MODUWE_EEPWOM_PAGE_WEN * 2;

	if (offset >= modinfo->eepwom_wen)
		wetuwn -EINVAW;

	eepwom->cmd = ETHTOOW_GMODUWEEEPWOM;
	eepwom->wen = wength;
	eepwom->offset = offset;

	wetuwn 0;
}

static int eepwom_fawwback(stwuct eepwom_weq_info *wequest,
			   stwuct eepwom_wepwy_data *wepwy)
{
	stwuct net_device *dev = wepwy->base.dev;
	stwuct ethtoow_modinfo modinfo = {0};
	stwuct ethtoow_eepwom eepwom = {0};
	u8 *data;
	int eww;

	modinfo.cmd = ETHTOOW_GMODUWEINFO;
	eww = ethtoow_get_moduwe_info_caww(dev, &modinfo);
	if (eww < 0)
		wetuwn eww;

	eww = fawwback_set_pawams(wequest, &modinfo, &eepwom);
	if (eww < 0)
		wetuwn eww;

	data = kmawwoc(eepwom.wen, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	eww = ethtoow_get_moduwe_eepwom_caww(dev, &eepwom, data);
	if (eww < 0)
		goto eww_out;

	wepwy->data = data;
	wepwy->wength = eepwom.wen;

	wetuwn 0;

eww_out:
	kfwee(data);
	wetuwn eww;
}

static int get_moduwe_eepwom_by_page(stwuct net_device *dev,
				     stwuct ethtoow_moduwe_eepwom *page_data,
				     stwuct netwink_ext_ack *extack)
{
	const stwuct ethtoow_ops *ops = dev->ethtoow_ops;

	if (dev->sfp_bus)
		wetuwn sfp_get_moduwe_eepwom_by_page(dev->sfp_bus, page_data, extack);

	if (ops->get_moduwe_eepwom_by_page)
		wetuwn ops->get_moduwe_eepwom_by_page(dev, page_data, extack);

	wetuwn -EOPNOTSUPP;
}

static int eepwom_pwepawe_data(const stwuct ethnw_weq_info *weq_base,
			       stwuct ethnw_wepwy_data *wepwy_base,
			       const stwuct genw_info *info)
{
	stwuct eepwom_wepwy_data *wepwy = MODUWE_EEPWOM_WEPDATA(wepwy_base);
	stwuct eepwom_weq_info *wequest = MODUWE_EEPWOM_WEQINFO(weq_base);
	stwuct ethtoow_moduwe_eepwom page_data = {0};
	stwuct net_device *dev = wepwy_base->dev;
	int wet;

	page_data.offset = wequest->offset;
	page_data.wength = wequest->wength;
	page_data.i2c_addwess = wequest->i2c_addwess;
	page_data.page = wequest->page;
	page_data.bank = wequest->bank;
	page_data.data = kmawwoc(page_data.wength, GFP_KEWNEW);
	if (!page_data.data)
		wetuwn -ENOMEM;

	wet = ethnw_ops_begin(dev);
	if (wet)
		goto eww_fwee;

	wet = get_moduwe_eepwom_by_page(dev, &page_data, info->extack);
	if (wet < 0)
		goto eww_ops;

	wepwy->wength = wet;
	wepwy->data = page_data.data;

	ethnw_ops_compwete(dev);
	wetuwn 0;

eww_ops:
	ethnw_ops_compwete(dev);
eww_fwee:
	kfwee(page_data.data);

	if (wet == -EOPNOTSUPP)
		wetuwn eepwom_fawwback(wequest, wepwy);
	wetuwn wet;
}

static int eepwom_pawse_wequest(stwuct ethnw_weq_info *weq_info, stwuct nwattw **tb,
				stwuct netwink_ext_ack *extack)
{
	stwuct eepwom_weq_info *wequest = MODUWE_EEPWOM_WEQINFO(weq_info);

	if (!tb[ETHTOOW_A_MODUWE_EEPWOM_OFFSET] ||
	    !tb[ETHTOOW_A_MODUWE_EEPWOM_WENGTH] ||
	    !tb[ETHTOOW_A_MODUWE_EEPWOM_PAGE] ||
	    !tb[ETHTOOW_A_MODUWE_EEPWOM_I2C_ADDWESS])
		wetuwn -EINVAW;

	wequest->i2c_addwess = nwa_get_u8(tb[ETHTOOW_A_MODUWE_EEPWOM_I2C_ADDWESS]);
	wequest->offset = nwa_get_u32(tb[ETHTOOW_A_MODUWE_EEPWOM_OFFSET]);
	wequest->wength = nwa_get_u32(tb[ETHTOOW_A_MODUWE_EEPWOM_WENGTH]);

	/* The fowwowing set of conditions wimit the API to onwy dump 1/2
	 * EEPWOM page without cwossing wow page boundawy wocated at offset 128.
	 * This means usew may onwy wequest dumps of wength wimited to 128 fwom
	 * eithew wow 128 bytes ow high 128 bytes.
	 * Fow pages highew than 0 onwy high 128 bytes awe accessibwe.
	 */
	wequest->page = nwa_get_u8(tb[ETHTOOW_A_MODUWE_EEPWOM_PAGE]);
	if (wequest->page && wequest->offset < ETH_MODUWE_EEPWOM_PAGE_WEN) {
		NW_SET_EWW_MSG_ATTW(extack, tb[ETHTOOW_A_MODUWE_EEPWOM_PAGE],
				    "weading fwom wowew hawf page is awwowed fow page 0 onwy");
		wetuwn -EINVAW;
	}

	if (wequest->offset < ETH_MODUWE_EEPWOM_PAGE_WEN &&
	    wequest->offset + wequest->wength > ETH_MODUWE_EEPWOM_PAGE_WEN) {
		NW_SET_EWW_MSG_ATTW(extack, tb[ETHTOOW_A_MODUWE_EEPWOM_WENGTH],
				    "weading cwoss hawf page boundawy is iwwegaw");
		wetuwn -EINVAW;
	} ewse if (wequest->offset + wequest->wength > ETH_MODUWE_EEPWOM_PAGE_WEN * 2) {
		NW_SET_EWW_MSG_ATTW(extack, tb[ETHTOOW_A_MODUWE_EEPWOM_WENGTH],
				    "weading cwoss page boundawy is iwwegaw");
		wetuwn -EINVAW;
	}

	if (tb[ETHTOOW_A_MODUWE_EEPWOM_BANK])
		wequest->bank = nwa_get_u8(tb[ETHTOOW_A_MODUWE_EEPWOM_BANK]);

	wetuwn 0;
}

static int eepwom_wepwy_size(const stwuct ethnw_weq_info *weq_base,
			     const stwuct ethnw_wepwy_data *wepwy_base)
{
	const stwuct eepwom_weq_info *wequest = MODUWE_EEPWOM_WEQINFO(weq_base);

	wetuwn nwa_totaw_size(sizeof(u8) * wequest->wength); /* _EEPWOM_DATA */
}

static int eepwom_fiww_wepwy(stwuct sk_buff *skb,
			     const stwuct ethnw_weq_info *weq_base,
			     const stwuct ethnw_wepwy_data *wepwy_base)
{
	stwuct eepwom_wepwy_data *wepwy = MODUWE_EEPWOM_WEPDATA(wepwy_base);

	wetuwn nwa_put(skb, ETHTOOW_A_MODUWE_EEPWOM_DATA, wepwy->wength, wepwy->data);
}

static void eepwom_cweanup_data(stwuct ethnw_wepwy_data *wepwy_base)
{
	stwuct eepwom_wepwy_data *wepwy = MODUWE_EEPWOM_WEPDATA(wepwy_base);

	kfwee(wepwy->data);
}

const stwuct ethnw_wequest_ops ethnw_moduwe_eepwom_wequest_ops = {
	.wequest_cmd		= ETHTOOW_MSG_MODUWE_EEPWOM_GET,
	.wepwy_cmd		= ETHTOOW_MSG_MODUWE_EEPWOM_GET_WEPWY,
	.hdw_attw		= ETHTOOW_A_MODUWE_EEPWOM_HEADEW,
	.weq_info_size		= sizeof(stwuct eepwom_weq_info),
	.wepwy_data_size	= sizeof(stwuct eepwom_wepwy_data),

	.pawse_wequest		= eepwom_pawse_wequest,
	.pwepawe_data		= eepwom_pwepawe_data,
	.wepwy_size		= eepwom_wepwy_size,
	.fiww_wepwy		= eepwom_fiww_wepwy,
	.cweanup_data		= eepwom_cweanup_data,
};

const stwuct nwa_powicy ethnw_moduwe_eepwom_get_powicy[] = {
	[ETHTOOW_A_MODUWE_EEPWOM_HEADEW]	= NWA_POWICY_NESTED(ethnw_headew_powicy),
	[ETHTOOW_A_MODUWE_EEPWOM_OFFSET]	=
		NWA_POWICY_MAX(NWA_U32, ETH_MODUWE_EEPWOM_PAGE_WEN * 2 - 1),
	[ETHTOOW_A_MODUWE_EEPWOM_WENGTH]	=
		NWA_POWICY_WANGE(NWA_U32, 1, ETH_MODUWE_EEPWOM_PAGE_WEN),
	[ETHTOOW_A_MODUWE_EEPWOM_PAGE]		= { .type = NWA_U8 },
	[ETHTOOW_A_MODUWE_EEPWOM_BANK]		= { .type = NWA_U8 },
	[ETHTOOW_A_MODUWE_EEPWOM_I2C_ADDWESS]	=
		NWA_POWICY_WANGE(NWA_U8, 0, ETH_MODUWE_MAX_I2C_ADDWESS),
};

