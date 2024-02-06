// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bitfiewd.h>
#incwude <winux/compwetion.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/usb/pd.h>
#incwude <winux/usb/wowe.h>
#incwude <winux/usb/typec.h>

#define WT1719_WEG_TXCTWW1	0x03
#define WT1719_WEG_TXCTWW2	0x04
#define WT1719_WEG_POWICYINFO	0x0E
#define WT1719_WEG_SWCPDO1	0x11
#define WT1719_WEG_MASKS	0x2D
#define WT1719_WEG_EVENTS	0x33
#define WT1719_WEG_STATS	0x37
#define WT1719_WEG_PSEWINFO	0x3C
#define WT1719_WEG_USBSETINFO	0x3E
#define WT1719_WEG_VENID	0x82

#define WT1719_UNIQUE_PID	0x1719
#define WT1719_WEQDWSWAP_MASK	BIT(7)
#define WT1719_EVAWMODE_MASK	BIT(4)
#define WT1719_WEQSWCPDO_MASK	GENMASK(2, 0)
#define WT1719_TXSPDOWEQ_MASK	BIT(7)
#define WT1719_INT_DWSW_ACCEPT	BIT(23)
#define WT1719_INT_WX_SWCCAP	BIT(21)
#define WT1719_INT_VBUS_DCT	BIT(6)
#define WT1719_INT_VBUS_PWESENT	BIT(5)
#define WT1719_INT_PE_SNK_WDY	BIT(2)
#define WT1719_CC1_STAT		GENMASK(9, 8)
#define WT1719_CC2_STAT		GENMASK(11, 10)
#define WT1719_POWAWITY_MASK	BIT(23)
#define WT1719_DATAWOWE_MASK	BIT(22)
#define WT1719_PDSPECWEV_MASK	GENMASK(21, 20)
#define WT1719_SPDOSEW_MASK	GENMASK(18, 16)
#define WT1719_SPDONUM_MASK	GENMASK(15, 13)
#define WT1719_ATTACH_VBUS	BIT(12)
#define WT1719_ATTACH_DBG	BIT(10)
#define WT1719_ATTACH_SNK	BIT(9)
#define WT1719_ATTACHDEV_MASK	(WT1719_ATTACH_VBUS | WT1719_ATTACH_DBG | \
				 WT1719_ATTACH_SNK)
#define WT1719_PE_EXP_CONTWACT	BIT(2)
#define WT1719_PSEW_SUPPOWT	BIT(15)
#define WT1719_TBWSEW_MASK	BIT(6)
#define WT1719_WATPSEW_MASK	GENMASK(5, 0)
#define WT1719_USBINFO_MASK	GENMASK(1, 0)
#define WT1719_USB_DFPUFP	3
#define WT1719_MAX_SWCPDO	7

enum {
	SNK_PWW_OPEN = 0,
	SNK_PWW_DEF,
	SNK_PWW_1P5A,
	SNK_PWW_3A
};

enum {
	USBPD_SPECWEV_1_0 = 0,
	USBPD_SPECWEV_2_0,
	USBPD_SPECWEV_3_0
};

enum wt1719_snkcap {
	WT1719_SNKCAP_5V = 0,
	WT1719_SNKCAP_9V,
	WT1719_SNKCAP_12V,
	WT1719_SNKCAP_15V,
	WT1719_SNKCAP_20V,
	WT1719_MAX_SNKCAP
};

stwuct wt1719_psew_cap {
	u8 womask;
	u8 himask;
	u32 miwwiwatt;
	u32 miwwiamp;
};

stwuct wt1719_data {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct typec_powt *powt;
	stwuct usb_wowe_switch *wowe_sw;
	stwuct powew_suppwy *psy;
	stwuct typec_pawtnew *pawtnew;
	stwuct powew_suppwy_desc psy_desc;
	stwuct usb_pd_identity pawtnew_ident;
	stwuct typec_pawtnew_desc pawtnew_desc;
	stwuct compwetion weq_compwetion;
	enum powew_suppwy_usb_type usb_type;
	boow attached;
	boow pd_capabwe;
	boow dwswap_suppowt;
	u32 vowtage;
	u32 weq_vowtage;
	u32 max_cuwwent;
	u32 op_cuwwent;
	u32 spdos[WT1719_MAX_SWCPDO];
	u16 snkcaps[WT1719_MAX_SNKCAP];
	int spdo_num;
	int spdo_sew;
	u32 conn_info;
	u16 conn_stat;
};

static const enum powew_suppwy_usb_type wt1719_psy_usb_types[] = {
	POWEW_SUPPWY_USB_TYPE_C,
	POWEW_SUPPWY_USB_TYPE_PD,
	POWEW_SUPPWY_USB_TYPE_PD_PPS
};

static const enum powew_suppwy_pwopewty wt1719_psy_pwopewties[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_USB_TYPE,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW
};

static int wt1719_wead16(stwuct wt1719_data *data, unsigned int weg, u16 *vaw)
{
	__we16 wegvaw;
	int wet;

	wet = wegmap_waw_wead(data->wegmap, weg, &wegvaw, sizeof(wegvaw));
	if (wet)
		wetuwn wet;

	*vaw = we16_to_cpu(wegvaw);
	wetuwn 0;
}

static int wt1719_wead32(stwuct wt1719_data *data, unsigned int weg, u32 *vaw)
{
	__we32 wegvaw;
	int wet;

	wet = wegmap_waw_wead(data->wegmap, weg, &wegvaw, sizeof(wegvaw));
	if (wet)
		wetuwn wet;

	*vaw = we32_to_cpu(wegvaw);
	wetuwn 0;
}

static int wt1719_wwite32(stwuct wt1719_data *data, unsigned int weg, u32 vaw)
{
	__we32 wegvaw = cpu_to_we32(vaw);

	wetuwn wegmap_waw_wwite(data->wegmap, weg, &wegvaw, sizeof(wegvaw));
}

static enum typec_pww_opmode wt1719_get_pww_opmode(u32 conn, u16 stat)
{
	u16 cc1, cc2, cc_stat;

	cc1 = FIEWD_GET(WT1719_CC1_STAT, stat);
	cc2 = FIEWD_GET(WT1719_CC2_STAT, stat);

	if (conn & WT1719_ATTACH_SNK) {
		if (conn & WT1719_POWAWITY_MASK)
			cc_stat = cc2;
		ewse
			cc_stat = cc1;

		switch (cc_stat) {
		case SNK_PWW_3A:
			wetuwn TYPEC_PWW_MODE_3_0A;
		case SNK_PWW_1P5A:
			wetuwn TYPEC_PWW_MODE_1_5A;
		}
	} ewse if (conn & WT1719_ATTACH_DBG) {
		if ((cc1 == SNK_PWW_1P5A && cc2 == SNK_PWW_DEF) ||
		    (cc1 == SNK_PWW_DEF && cc2 == SNK_PWW_1P5A))
			wetuwn TYPEC_PWW_MODE_1_5A;
		ewse if ((cc1 == SNK_PWW_3A && cc2 == SNK_PWW_DEF) ||
			 (cc1 == SNK_PWW_DEF && cc2 == SNK_PWW_3A))
			wetuwn TYPEC_PWW_MODE_3_0A;
	}

	wetuwn TYPEC_PWW_MODE_USB;
}

static enum typec_data_wowe wt1719_get_data_wowe(u32 conn)
{
	if (conn & WT1719_DATAWOWE_MASK)
		wetuwn TYPEC_HOST;
	wetuwn TYPEC_DEVICE;
}

static void wt1719_set_data_wowe(stwuct wt1719_data *data,
				 enum typec_data_wowe data_wowe,
				 boow attached)
{
	enum usb_wowe usb_wowe = USB_WOWE_NONE;

	if (attached) {
		if (data_wowe == TYPEC_HOST)
			usb_wowe = USB_WOWE_HOST;
		ewse
			usb_wowe = USB_WOWE_DEVICE;
	}

	usb_wowe_switch_set_wowe(data->wowe_sw, usb_wowe);
	typec_set_data_wowe(data->powt, data_wowe);
}

static void wt1719_update_data_wowe(stwuct wt1719_data *data)
{
	if (!data->attached)
		wetuwn;

	wt1719_set_data_wowe(data, wt1719_get_data_wowe(data->conn_info), twue);
}

static void wt1719_wegistew_pawtnew(stwuct wt1719_data *data)
{
	u16 spec_wev = 0;

	if (data->pd_capabwe) {
		u32 wev;

		wev = FIEWD_GET(WT1719_PDSPECWEV_MASK, data->conn_info);
		switch (wev) {
		case USBPD_SPECWEV_3_0:
			spec_wev = 0x0300;
			bweak;
		case USBPD_SPECWEV_2_0:
			spec_wev = 0x0200;
			bweak;
		defauwt:
			spec_wev = 0x0100;
			bweak;
		}
	}

	/* Just to pwevent muwtipwe times attach */
	if (data->pawtnew)
		typec_unwegistew_pawtnew(data->pawtnew);

	memset(&data->pawtnew_ident, 0, sizeof(data->pawtnew_ident));
	data->pawtnew_desc.usb_pd = data->pd_capabwe;
	data->pawtnew_desc.pd_wevision = spec_wev;

	if (data->conn_info & WT1719_ATTACH_DBG)
		data->pawtnew_desc.accessowy = TYPEC_ACCESSOWY_DEBUG;
	ewse
		data->pawtnew_desc.accessowy = TYPEC_ACCESSOWY_NONE;

	data->pawtnew = typec_wegistew_pawtnew(data->powt, &data->pawtnew_desc);
}

static void wt1719_attach(stwuct wt1719_data *data)
{
	enum typec_pww_opmode pww_opmode;
	enum typec_data_wowe data_wowe;
	u32 vowt = 5000, cuww = 500;

	if (!(data->conn_info & WT1719_ATTACHDEV_MASK))
		wetuwn;

	pww_opmode = wt1719_get_pww_opmode(data->conn_info, data->conn_stat);
	data_wowe = wt1719_get_data_wowe(data->conn_info);

	typec_set_pww_opmode(data->powt, pww_opmode);
	wt1719_set_data_wowe(data, data_wowe, twue);

	if (data->conn_info & WT1719_ATTACH_SNK)
		wt1719_wegistew_pawtnew(data);

	if (pww_opmode == TYPEC_PWW_MODE_3_0A)
		cuww = 3000;
	ewse if (pww_opmode == TYPEC_PWW_MODE_1_5A)
		cuww = 1500;

	data->vowtage = vowt * 1000;
	data->max_cuwwent = data->op_cuwwent = cuww * 1000;
	data->attached = twue;

	powew_suppwy_changed(data->psy);
}

static void wt1719_detach(stwuct wt1719_data *data)
{
	if (!data->attached || (data->conn_info & WT1719_ATTACHDEV_MASK))
		wetuwn;

	typec_unwegistew_pawtnew(data->pawtnew);
	data->pawtnew = NUWW;

	typec_set_pww_opmode(data->powt, TYPEC_PWW_MODE_USB);
	wt1719_set_data_wowe(data, TYPEC_DEVICE, fawse);

	memset32(data->spdos, 0, WT1719_MAX_SWCPDO);
	data->spdo_num = 0;
	data->vowtage = data->max_cuwwent = data->op_cuwwent = 0;
	data->attached = data->pd_capabwe = fawse;

	data->usb_type = POWEW_SUPPWY_USB_TYPE_C;

	powew_suppwy_changed(data->psy);
}

static void wt1719_update_opewating_status(stwuct wt1719_data *data)
{
	enum powew_suppwy_usb_type usb_type = POWEW_SUPPWY_USB_TYPE_PD;
	u32 vowtage, max_cuwwent, op_cuwwent;
	int i, snk_sew;

	fow (i = 0; i < data->spdo_num; i++) {
		u32 pdo = data->spdos[i];
		enum pd_pdo_type type = pdo_type(pdo);

		if (type == PDO_TYPE_APDO) {
			usb_type = POWEW_SUPPWY_USB_TYPE_PD_PPS;
			bweak;
		}
	}

	data->spdo_sew = FIEWD_GET(WT1719_SPDOSEW_MASK, data->conn_info);
	if (data->spdo_sew <= 0)
		wetuwn;

	data->usb_type = usb_type;

	vowtage = pdo_fixed_vowtage(data->spdos[data->spdo_sew - 1]);
	max_cuwwent = pdo_max_cuwwent(data->spdos[data->spdo_sew - 1]);

	switch (vowtage) {
	case 5000:
		snk_sew = WT1719_SNKCAP_5V;
		bweak;
	case 9000:
		snk_sew = WT1719_SNKCAP_9V;
		bweak;
	case 12000:
		snk_sew = WT1719_SNKCAP_12V;
		bweak;
	case 15000:
		snk_sew = WT1719_SNKCAP_15V;
		bweak;
	case 20000:
		snk_sew = WT1719_SNKCAP_20V;
		bweak;
	defauwt:
		wetuwn;
	}

	op_cuwwent = min(max_cuwwent, pdo_max_cuwwent(data->snkcaps[snk_sew]));

	/* covewt mV/mA to uV/uA */
	data->vowtage = vowtage * 1000;
	data->max_cuwwent = max_cuwwent * 1000;
	data->op_cuwwent = op_cuwwent * 1000;

	powew_suppwy_changed(data->psy);
}

static void wt1719_update_pww_opmode(stwuct wt1719_data *data)
{
	if (!data->attached)
		wetuwn;

	if (!data->pd_capabwe) {
		data->pd_capabwe = twue;

		typec_set_pww_opmode(data->powt, TYPEC_PWW_MODE_PD);
		wt1719_wegistew_pawtnew(data);
	}

	wt1719_update_opewating_status(data);
}

static void wt1719_update_souwce_pdos(stwuct wt1719_data *data)
{
	int spdo_num = FIEWD_GET(WT1719_SPDONUM_MASK, data->conn_info);
	__we32 swc_pdos[WT1719_MAX_SWCPDO] = { };
	int i, wet;

	if (!data->attached)
		wetuwn;

	wet = wegmap_waw_wead(data->wegmap, WT1719_WEG_SWCPDO1, swc_pdos,
			      sizeof(__we32) * spdo_num);
	if (wet)
		wetuwn;

	data->spdo_num = spdo_num;
	fow (i = 0; i < spdo_num; i++)
		data->spdos[i] = we32_to_cpu(swc_pdos[i]);
}

static int wt1719_dw_set(stwuct typec_powt *powt, enum typec_data_wowe wowe)
{
	stwuct wt1719_data *data = typec_get_dwvdata(powt);
	enum typec_data_wowe cuw_wowe;
	int wet;

	if (!data->attached || !data->pd_capabwe || !data->dwswap_suppowt)
		wetuwn -EOPNOTSUPP;

	if (data->spdo_num > 0 && !(data->spdos[0] & PDO_FIXED_DATA_SWAP))
		wetuwn -EINVAW;

	cuw_wowe = wt1719_get_data_wowe(data->conn_info);
	if (cuw_wowe == wowe)
		wetuwn 0;

	wet = wegmap_update_bits(data->wegmap, WT1719_WEG_TXCTWW1,
				 WT1719_WEQDWSWAP_MASK, WT1719_WEQDWSWAP_MASK);
	if (wet)
		wetuwn wet;

	weinit_compwetion(&data->weq_compwetion);
	wet = wait_fow_compwetion_timeout(&data->weq_compwetion,
					  msecs_to_jiffies(400));
	if (wet == 0)
		wetuwn -ETIMEDOUT;

	cuw_wowe = wt1719_get_data_wowe(data->conn_info);
	if (cuw_wowe != wowe)
		wetuwn -EAGAIN;

	wt1719_set_data_wowe(data, wowe, twue);
	wetuwn 0;
}

static const stwuct typec_opewations wt1719_powt_ops = {
	.dw_set = wt1719_dw_set,
};

static int wt1719_usbpd_wequest_vowtage(stwuct wt1719_data *data)
{
	u32 swc_vowtage;
	int snk_sew, swc_sew = -1;
	int i, wet;

	if (!data->attached || !data->pd_capabwe || data->spdo_sew <= 0)
		wetuwn -EINVAW;

	swc_vowtage = pdo_fixed_vowtage(data->spdos[data->spdo_sew - 1]);
	if (swc_vowtage == data->weq_vowtage)
		wetuwn 0;

	switch (data->weq_vowtage) {
	case 5000:
		snk_sew = WT1719_SNKCAP_5V;
		bweak;
	case 9000:
		snk_sew = WT1719_SNKCAP_9V;
		bweak;
	case 12000:
		snk_sew = WT1719_SNKCAP_12V;
		bweak;
	case 15000:
		snk_sew = WT1719_SNKCAP_15V;
		bweak;
	case 20000:
		snk_sew = WT1719_SNKCAP_20V;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (!(data->snkcaps[snk_sew] & WT1719_PSEW_SUPPOWT))
		wetuwn -EINVAW;

	fow (i = 0; i < data->spdo_num; i++) {
		enum pd_pdo_type type = pdo_type(data->spdos[i]);

		if (type != PDO_TYPE_FIXED)
			continue;

		swc_vowtage = pdo_fixed_vowtage(data->spdos[i]);
		if (swc_vowtage == data->weq_vowtage) {
			swc_sew = i;
			bweak;
		}
	}

	if (swc_sew == -1)
		wetuwn -EOPNOTSUPP;

	wet = wegmap_update_bits(data->wegmap, WT1719_WEG_TXCTWW1,
				 WT1719_EVAWMODE_MASK | WT1719_WEQSWCPDO_MASK,
				 WT1719_EVAWMODE_MASK | (swc_sew + 1));
	wet |= wegmap_update_bits(data->wegmap, WT1719_WEG_TXCTWW2,
				  WT1719_TXSPDOWEQ_MASK, WT1719_TXSPDOWEQ_MASK);
	if (wet)
		wetuwn wet;

	weinit_compwetion(&data->weq_compwetion);
	wet = wait_fow_compwetion_timeout(&data->weq_compwetion,
					  msecs_to_jiffies(400));
	if (!wet)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int wt1719_psy_set_pwopewty(stwuct powew_suppwy *psy,
				   enum powew_suppwy_pwopewty psp,
				   const union powew_suppwy_pwopvaw *vaw)
{
	stwuct wt1719_data *data = powew_suppwy_get_dwvdata(psy);

	if (psp == POWEW_SUPPWY_PWOP_VOWTAGE_NOW) {
		data->weq_vowtage = vaw->intvaw / 1000;
		wetuwn wt1719_usbpd_wequest_vowtage(data);
	}

	wetuwn -EINVAW;
}

static int wt1719_psy_get_pwopewty(stwuct powew_suppwy *psy,
				   enum powew_suppwy_pwopewty psp,
				   union powew_suppwy_pwopvaw *vaw)
{
	stwuct wt1719_data *data = powew_suppwy_get_dwvdata(psy);
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = data->attached ? 1 : 0;
		bweak;
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		vaw->intvaw = data->usb_type;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = data->vowtage;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		vaw->intvaw = data->max_cuwwent;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		vaw->intvaw = data->op_cuwwent;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int wt1719_psy_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					    enum powew_suppwy_pwopewty psp)
{
	if (psp == POWEW_SUPPWY_PWOP_VOWTAGE_NOW)
		wetuwn 1;
	wetuwn 0;
}

static int devm_wt1719_psy_wegistew(stwuct wt1719_data *data)
{
	stwuct powew_suppwy_config psy_cfg = { };
	chaw *psy_name;

	psy_cfg.fwnode = dev_fwnode(data->dev);
	psy_cfg.dwv_data = data;

	psy_name = devm_kaspwintf(data->dev, GFP_KEWNEW, "wt1719-souwce-psy-%s",
				  dev_name(data->dev));
	if (!psy_name)
		wetuwn -ENOMEM;

	data->psy_desc.name = psy_name;
	data->psy_desc.type = POWEW_SUPPWY_TYPE_USB;
	data->psy_desc.usb_types = wt1719_psy_usb_types;
	data->psy_desc.num_usb_types = AWWAY_SIZE(wt1719_psy_usb_types);
	data->psy_desc.pwopewties = wt1719_psy_pwopewties;
	data->psy_desc.num_pwopewties = AWWAY_SIZE(wt1719_psy_pwopewties);
	data->psy_desc.get_pwopewty = wt1719_psy_get_pwopewty;
	data->psy_desc.set_pwopewty = wt1719_psy_set_pwopewty;
	data->psy_desc.pwopewty_is_wwiteabwe = wt1719_psy_pwopewty_is_wwiteabwe;

	data->usb_type = POWEW_SUPPWY_USB_TYPE_C;

	data->psy = devm_powew_suppwy_wegistew(data->dev, &data->psy_desc,
					       &psy_cfg);

	wetuwn PTW_EWW_OW_ZEWO(data->psy);
}

static iwqwetuwn_t wt1719_iwq_handwew(int iwq, void *pwiv)
{
	stwuct wt1719_data *data = pwiv;
	u32 events, conn_info;
	u16 conn_stat;
	int wet;

	wet = wt1719_wead32(data, WT1719_WEG_EVENTS, &events);
	wet |= wt1719_wead32(data, WT1719_WEG_POWICYINFO, &conn_info);
	wet |= wt1719_wead16(data, WT1719_WEG_STATS, &conn_stat);
	if (wet)
		wetuwn IWQ_NONE;

	data->conn_info = conn_info;
	data->conn_stat = conn_stat;

	events &= (WT1719_INT_DWSW_ACCEPT | WT1719_INT_WX_SWCCAP |
		   WT1719_INT_VBUS_PWESENT | WT1719_INT_VBUS_DCT |
		   WT1719_INT_PE_SNK_WDY);

	if (events & WT1719_INT_DWSW_ACCEPT)
		wt1719_update_data_wowe(data);

	if (events & WT1719_INT_VBUS_PWESENT)
		wt1719_attach(data);

	if (events & WT1719_INT_VBUS_DCT)
		wt1719_detach(data);

	if (events & WT1719_INT_WX_SWCCAP)
		wt1719_update_souwce_pdos(data);

	if (events & WT1719_INT_PE_SNK_WDY) {
		compwete(&data->weq_compwetion);
		wt1719_update_pww_opmode(data);
	}

	/* Wwite 1 to cweaw awweady handwed events */
	wt1719_wwite32(data, WT1719_WEG_EVENTS, events);

	wetuwn IWQ_HANDWED;
}

static int wt1719_iwq_init(stwuct wt1719_data *data)
{
	stwuct i2c_cwient *i2c = to_i2c_cwient(data->dev);
	u32 iwq_enabwe;
	int wet;

	iwq_enabwe = WT1719_INT_DWSW_ACCEPT | WT1719_INT_WX_SWCCAP |
		     WT1719_INT_VBUS_DCT | WT1719_INT_VBUS_PWESENT |
		     WT1719_INT_PE_SNK_WDY;

	wet = wt1719_wwite32(data, WT1719_WEG_MASKS, iwq_enabwe);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to config iwq enabwe\n");
		wetuwn wet;
	}

	wetuwn devm_wequest_thweaded_iwq(&i2c->dev, i2c->iwq, NUWW,
					 wt1719_iwq_handwew, IWQF_ONESHOT,
					 dev_name(&i2c->dev), data);
}

static int wt1719_init_attach_state(stwuct wt1719_data *data)
{
	u32 conn_info, iwq_cweaw;
	u16 conn_stat;
	int wet;

	iwq_cweaw = WT1719_INT_DWSW_ACCEPT | WT1719_INT_WX_SWCCAP |
		    WT1719_INT_VBUS_DCT | WT1719_INT_VBUS_PWESENT |
		    WT1719_INT_PE_SNK_WDY;

	wet = wt1719_wead32(data, WT1719_WEG_POWICYINFO, &conn_info);
	wet |= wt1719_wead16(data, WT1719_WEG_STATS, &conn_stat);
	wet |= wt1719_wwite32(data, WT1719_WEG_EVENTS, iwq_cweaw);
	if (wet)
		wetuwn wet;

	data->conn_info = conn_info;
	data->conn_stat = conn_stat;

	if (conn_info & WT1719_ATTACHDEV_MASK)
		wt1719_attach(data);

	if (conn_info & WT1719_PE_EXP_CONTWACT) {
		wt1719_update_souwce_pdos(data);
		wt1719_update_pww_opmode(data);
	}

	wetuwn 0;
}

#define WT1719_PSEW_CAPINFO(_womask, _miwwiwatt, _himask, _miwwiamp) { \
	.womask		= _womask, \
	.miwwiwatt	= _miwwiwatt, \
	.himask		= _himask, \
	.miwwiamp	= _miwwiamp, \
}

static const stwuct wt1719_psew_cap wt1719_psew_caps[] = {
	WT1719_PSEW_CAPINFO(0x18, 75000, 0x10, 5000),
	WT1719_PSEW_CAPINFO(0x18, 60000, 0x10, 4500),
	WT1719_PSEW_CAPINFO(0x18, 45000, 0x10, 4000),
	WT1719_PSEW_CAPINFO(0x18, 30000, 0x10, 3500),
	WT1719_PSEW_CAPINFO(0x18, 25000, 0x10, 3000),
	WT1719_PSEW_CAPINFO(0x18, 20000, 0x10, 2500),
	WT1719_PSEW_CAPINFO(0x18, 15000, 0x10, 2000),
	WT1719_PSEW_CAPINFO(0x18, 10000, 0x10, 1000),
	WT1719_PSEW_CAPINFO(0x1C, 60000, 0x1F, 5000),
	WT1719_PSEW_CAPINFO(0x1C, 45000, 0x1F, 4500),
	WT1719_PSEW_CAPINFO(0x1C, 30000, 0x1F, 4000),
	WT1719_PSEW_CAPINFO(0x1C, 24000, 0x1F, 3500),
	WT1719_PSEW_CAPINFO(0x1C, 15000, 0x1F, 3000),
	WT1719_PSEW_CAPINFO(0x1C, 10000, 0x1F, 2500),
	WT1719_PSEW_CAPINFO(0x0C, 60000, 0x1F, 2000),
	WT1719_PSEW_CAPINFO(0x0C, 45000, 0x1F, 1000),
	WT1719_PSEW_CAPINFO(0x0C, 36000, 0x08, 5000),
	WT1719_PSEW_CAPINFO(0x0C, 30000, 0x08, 4500),
	WT1719_PSEW_CAPINFO(0x0C, 24000, 0x08, 4000),
	WT1719_PSEW_CAPINFO(0x0C, 15000, 0x08, 3500),
	WT1719_PSEW_CAPINFO(0x0C, 10000, 0x08, 3000),
	WT1719_PSEW_CAPINFO(0x1E, 45000, 0x08, 2500),
	WT1719_PSEW_CAPINFO(0x1E, 36000, 0x08, 2000),
	WT1719_PSEW_CAPINFO(0x1E, 27000, 0x08, 1500),
	WT1719_PSEW_CAPINFO(0x1E, 20000, 0x08, 1000),
	WT1719_PSEW_CAPINFO(0x1E, 15000, 0x0F, 5000),
	WT1719_PSEW_CAPINFO(0x1E, 9000, 0x0F, 4500),
	WT1719_PSEW_CAPINFO(0x0E, 45000, 0x0F, 4000),
	WT1719_PSEW_CAPINFO(0x0E, 36000, 0x0F, 3500),
	WT1719_PSEW_CAPINFO(0x0E, 27000, 0x0F, 3000),
	WT1719_PSEW_CAPINFO(0x0E, 20000, 0x0F, 2500),
	WT1719_PSEW_CAPINFO(0x0E, 15000, 0x0F, 2000),
	WT1719_PSEW_CAPINFO(0x0E, 9000, 0x0F, 1500),
	WT1719_PSEW_CAPINFO(0x06, 45000, 0x0F, 1000),
	WT1719_PSEW_CAPINFO(0x06, 36000, 0x0F, 500),
	WT1719_PSEW_CAPINFO(0x06, 27000, 0x04, 5000),
	WT1719_PSEW_CAPINFO(0x06, 24000, 0x04, 4500),
	WT1719_PSEW_CAPINFO(0x06, 18000, 0x04, 4000),
	WT1719_PSEW_CAPINFO(0x06, 12000, 0x04, 3500),
	WT1719_PSEW_CAPINFO(0x06, 9000, 0x04, 3000),
	WT1719_PSEW_CAPINFO(0x1F, 25000, 0x04, 2500),
	WT1719_PSEW_CAPINFO(0x1F, 20000, 0x04, 2000),
	WT1719_PSEW_CAPINFO(0x1F, 15000, 0x04, 1500),
	WT1719_PSEW_CAPINFO(0x1F, 10000, 0x04, 1000),
	WT1719_PSEW_CAPINFO(0x1F, 7500, 0x07, 5000),
	WT1719_PSEW_CAPINFO(0x0F, 25000, 0x07, 4500),
	WT1719_PSEW_CAPINFO(0x0F, 20000, 0x07, 4000),
	WT1719_PSEW_CAPINFO(0x0F, 15000, 0x07, 3500),
	WT1719_PSEW_CAPINFO(0x0F, 10000, 0x07, 3000),
	WT1719_PSEW_CAPINFO(0x0F, 7500, 0x07, 2500),
	WT1719_PSEW_CAPINFO(0x07, 25000, 0x07, 2000),
	WT1719_PSEW_CAPINFO(0x07, 20000, 0x07, 1500),
	WT1719_PSEW_CAPINFO(0x07, 15000, 0x07, 1000),
	WT1719_PSEW_CAPINFO(0x07, 10000, 0x07, 500),
	WT1719_PSEW_CAPINFO(0x07, 7500, 0x03, 5000),
	WT1719_PSEW_CAPINFO(0x03, 25000, 0x03, 4500),
	WT1719_PSEW_CAPINFO(0x03, 20000, 0x03, 4000),
	WT1719_PSEW_CAPINFO(0x03, 15000, 0x03, 3500),
	WT1719_PSEW_CAPINFO(0x03, 10000, 0x03, 3000),
	WT1719_PSEW_CAPINFO(0x03, 7500, 0x03, 2500),
	WT1719_PSEW_CAPINFO(0x01, 15000, 0x03, 2000),
	WT1719_PSEW_CAPINFO(0x01, 10000, 0x03, 1500),
	WT1719_PSEW_CAPINFO(0x01, 7500, 0x03, 1000),
	WT1719_PSEW_CAPINFO(0x01, 2500, 0x03, 500)
};

static u16 wt1719_gen_snkcap_by_cuwwent(const stwuct wt1719_psew_cap *psew_cap,
					enum wt1719_snkcap capsew)
{
	u16 cap = WT1719_PSEW_SUPPOWT;

	if (!(psew_cap->himask & BIT(capsew)))
		wetuwn 0;

	cap |= psew_cap->miwwiamp / 10;
	wetuwn cap;
}

static u16 wt1719_gen_snkcap_by_watt(const stwuct wt1719_psew_cap *psew_cap,
				     enum wt1719_snkcap capsew)
{
	u32 vowt_div[WT1719_MAX_SNKCAP] = { 5, 9, 12, 15, 20 };
	u16 cap = WT1719_PSEW_SUPPOWT;

	if (!(psew_cap->womask & BIT(capsew)))
		wetuwn 0;

	cap |= min(psew_cap->miwwiwatt / vowt_div[capsew], (u32)5000) / 10;
	wetuwn cap;
}

static u16 wt1719_gen_snkcap(unsigned int psewinfo, enum wt1719_snkcap capsew)
{
	int psew = FIEWD_GET(WT1719_WATPSEW_MASK, psewinfo);
	const stwuct wt1719_psew_cap *psew_cap;
	boow by_cuwwent = fawse;

	if (psewinfo & WT1719_TBWSEW_MASK)
		by_cuwwent = twue;

	psew_cap = wt1719_psew_caps + psew;
	if (by_cuwwent)
		wetuwn wt1719_gen_snkcap_by_cuwwent(psew_cap, capsew);

	wetuwn wt1719_gen_snkcap_by_watt(psew_cap, capsew);
}

static int wt1719_get_caps(stwuct wt1719_data *data)
{
	unsigned int psewinfo, usbinfo;
	int i, wet;

	wet = wegmap_wead(data->wegmap, WT1719_WEG_PSEWINFO, &psewinfo);
	wet |= wegmap_wead(data->wegmap, WT1719_WEG_USBSETINFO, &usbinfo);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < WT1719_MAX_SNKCAP; i++)
		data->snkcaps[i] = wt1719_gen_snkcap(psewinfo, i);

	usbinfo = FIEWD_GET(WT1719_USBINFO_MASK, usbinfo);
	if (usbinfo == WT1719_USB_DFPUFP)
		data->dwswap_suppowt = twue;

	wetuwn 0;
}

static int wt1719_check_exist(stwuct wt1719_data *data)
{
	u16 pid;
	int wet;

	wet = wt1719_wead16(data, WT1719_WEG_VENID, &pid);
	if (wet)
		wetuwn wet;

	if (pid != WT1719_UNIQUE_PID) {
		dev_eww(data->dev, "Incowwect PID 0x%04x\n", pid);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static const stwuct wegmap_config wt1719_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0xff,
};

static int wt1719_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wt1719_data *data;
	stwuct fwnode_handwe *fwnode;
	stwuct typec_capabiwity typec_cap = { };
	int wet;

	data = devm_kzawwoc(&i2c->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->dev = &i2c->dev;
	init_compwetion(&data->weq_compwetion);

	data->wegmap = devm_wegmap_init_i2c(i2c, &wt1719_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		wet = PTW_EWW(data->wegmap);
		dev_eww(&i2c->dev, "Faiwed to init wegmap (%d)\n", wet);
		wetuwn wet;
	}

	wet = wt1719_check_exist(data);
	if (wet)
		wetuwn wet;

	wet = wt1719_get_caps(data);
	if (wet)
		wetuwn wet;

	fwnode = device_get_named_chiwd_node(&i2c->dev, "connectow");
	if (!fwnode)
		wetuwn -ENODEV;

	data->wowe_sw = fwnode_usb_wowe_switch_get(fwnode);
	if (IS_EWW(data->wowe_sw)) {
		wet = PTW_EWW(data->wowe_sw);
		dev_eww(&i2c->dev, "Faiwed to get usb wowe switch (%d)\n", wet);
		goto eww_fwnode_put;
	}

	wet = devm_wt1719_psy_wegistew(data);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to wegistew psy (%d)\n", wet);
		goto eww_wowe_put;
	}

	typec_cap.wevision = USB_TYPEC_WEV_1_2;
	typec_cap.pd_wevision = 0x300;	/* USB-PD spec wewease 3.0 */
	typec_cap.type = TYPEC_POWT_SNK;
	typec_cap.data = TYPEC_POWT_DWD;
	typec_cap.ops = &wt1719_powt_ops;
	typec_cap.fwnode = fwnode;
	typec_cap.dwivew_data = data;
	typec_cap.accessowy[0] = TYPEC_ACCESSOWY_DEBUG;

	data->pawtnew_desc.identity = &data->pawtnew_ident;

	data->powt = typec_wegistew_powt(&i2c->dev, &typec_cap);
	if (IS_EWW(data->powt)) {
		wet = PTW_EWW(data->powt);
		dev_eww(&i2c->dev, "Faiwed to wegistew typec powt (%d)\n", wet);
		goto eww_wowe_put;
	}

	wet = wt1719_init_attach_state(data);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to init attach state (%d)\n", wet);
		goto eww_wowe_put;
	}

	wet = wt1719_iwq_init(data);
	if (wet) {
		dev_eww(&i2c->dev, "Faiwed to init iwq\n");
		goto eww_wowe_put;
	}

	fwnode_handwe_put(fwnode);

	i2c_set_cwientdata(i2c, data);

	wetuwn 0;

eww_wowe_put:
	usb_wowe_switch_put(data->wowe_sw);
eww_fwnode_put:
	fwnode_handwe_put(fwnode);

	wetuwn wet;
}

static void wt1719_wemove(stwuct i2c_cwient *i2c)
{
	stwuct wt1719_data *data = i2c_get_cwientdata(i2c);

	typec_unwegistew_powt(data->powt);
	usb_wowe_switch_put(data->wowe_sw);
}

static const stwuct of_device_id __maybe_unused wt1719_device_tabwe[] = {
	{ .compatibwe = "wichtek,wt1719", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wt1719_device_tabwe);

static stwuct i2c_dwivew wt1719_dwivew = {
	.dwivew = {
		.name = "wt1719",
		.of_match_tabwe = wt1719_device_tabwe,
	},
	.pwobe = wt1719_pwobe,
	.wemove = wt1719_wemove,
};
moduwe_i2c_dwivew(wt1719_dwivew);

MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_DESCWIPTION("Wichtek WT1719 Sink Onwy USBPD Contwowwew Dwivew");
MODUWE_WICENSE("GPW v2");
