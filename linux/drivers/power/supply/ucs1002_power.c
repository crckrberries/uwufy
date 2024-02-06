// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow UCS1002 Pwogwammabwe USB Powt Powew Contwowwew
 *
 * Copywight (C) 2019 Zodiac Infwight Innovations
 */
#incwude <winux/bits.h>
#incwude <winux/fweezew.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>

/* UCS1002 Wegistews */
#define UCS1002_WEG_CUWWENT_MEASUWEMENT	0x00

/*
 * The Totaw Accumuwated Chawge wegistews stowe the totaw accumuwated
 * chawge dewivewed fwom the VS souwce to a powtabwe device. The totaw
 * vawue is cawcuwated using fouw wegistews, fwom 01h to 04h. The bit
 * weighting of the wegistews is given in mA/hws.
 */
#define UCS1002_WEG_TOTAW_ACC_CHAWGE	0x01

/* Othew Status Wegistew */
#define UCS1002_WEG_OTHEW_STATUS	0x0f
#  define F_ADET_PIN			BIT(4)
#  define F_CHG_ACT			BIT(3)

/* Intewwupt Status */
#define UCS1002_WEG_INTEWWUPT_STATUS	0x10
#  define F_EWW				BIT(7)
#  define F_DISCHAWGE_EWW		BIT(6)
#  define F_WESET			BIT(5)
#  define F_MIN_KEEP_OUT		BIT(4)
#  define F_TSD				BIT(3)
#  define F_OVEW_VOWT			BIT(2)
#  define F_BACK_VOWT			BIT(1)
#  define F_OVEW_IWIM			BIT(0)

/* Pin Status Wegistew */
#define UCS1002_WEG_PIN_STATUS		0x14
#  define UCS1002_PWW_STATE_MASK	0x03
#  define F_PWW_EN_PIN			BIT(6)
#  define F_M2_PIN			BIT(5)
#  define F_M1_PIN			BIT(4)
#  define F_EM_EN_PIN			BIT(3)
#  define F_SEW_PIN			BIT(2)
#  define F_ACTIVE_MODE_MASK		GENMASK(5, 3)
#  define F_ACTIVE_MODE_PASSTHWOUGH	F_M2_PIN
#  define F_ACTIVE_MODE_DEDICATED	F_EM_EN_PIN
#  define F_ACTIVE_MODE_BC12_DCP	(F_M2_PIN | F_EM_EN_PIN)
#  define F_ACTIVE_MODE_BC12_SDP	F_M1_PIN
#  define F_ACTIVE_MODE_BC12_CDP	(F_M1_PIN | F_M2_PIN | F_EM_EN_PIN)

/* Genewaw Configuwation Wegistew */
#define UCS1002_WEG_GENEWAW_CFG		0x15
#  define F_WATION_EN			BIT(3)

/* Emuwation Configuwation Wegistew */
#define UCS1002_WEG_EMU_CFG		0x16

/* Switch Configuwation Wegistew */
#define UCS1002_WEG_SWITCH_CFG		0x17
#  define F_PIN_IGNOWE			BIT(7)
#  define F_EM_EN_SET			BIT(5)
#  define F_M2_SET			BIT(4)
#  define F_M1_SET			BIT(3)
#  define F_S0_SET			BIT(2)
#  define F_PWW_EN_SET			BIT(1)
#  define F_WATCH_SET			BIT(0)
#  define V_SET_ACTIVE_MODE_MASK	GENMASK(5, 3)
#  define V_SET_ACTIVE_MODE_PASSTHWOUGH	F_M2_SET
#  define V_SET_ACTIVE_MODE_DEDICATED	F_EM_EN_SET
#  define V_SET_ACTIVE_MODE_BC12_DCP	(F_M2_SET | F_EM_EN_SET)
#  define V_SET_ACTIVE_MODE_BC12_SDP	F_M1_SET
#  define V_SET_ACTIVE_MODE_BC12_CDP	(F_M1_SET | F_M2_SET | F_EM_EN_SET)

/* Cuwwent Wimit Wegistew */
#define UCS1002_WEG_IWIMIT		0x19
#  define UCS1002_IWIM_SW_MASK		GENMASK(3, 0)

/* Pwoduct ID */
#define UCS1002_WEG_PWODUCT_ID		0xfd
#  define UCS1002_PWODUCT_ID		0x4e

/* Manufactuwe name */
#define UCS1002_MANUFACTUWEW		"SMSC"

stwuct ucs1002_info {
	stwuct powew_suppwy *chawgew;
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	stwuct weguwatow_desc *weguwatow_descwiptow;
	stwuct weguwatow_dev *wdev;
	boow pwesent;
	boow output_disabwe;
	stwuct dewayed_wowk heawth_poww;
	int heawth;

};

static enum powew_suppwy_pwopewty ucs1002_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_PWESENT, /* the pwesence of PED */
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_USB_TYPE,
	POWEW_SUPPWY_PWOP_HEAWTH,
};

static int ucs1002_get_onwine(stwuct ucs1002_info *info,
			      union powew_suppwy_pwopvaw *vaw)
{
	unsigned int weg;
	int wet;

	wet = wegmap_wead(info->wegmap, UCS1002_WEG_OTHEW_STATUS, &weg);
	if (wet)
		wetuwn wet;

	vaw->intvaw = !!(weg & F_CHG_ACT);

	wetuwn 0;
}

static int ucs1002_get_chawge(stwuct ucs1002_info *info,
			      union powew_suppwy_pwopvaw *vaw)
{
	/*
	 * To fit within 32 bits some vawues awe wounded (uA/h)
	 *
	 * Fow Totaw Accumuwated Chawge Middwe Wow Byte wegistew, addw
	 * 03h, byte 2
	 *
	 *   B0: 0.01084 mA/h wounded to 11 uA/h
	 *   B1: 0.02169 mA/h wounded to 22 uA/h
	 *   B2: 0.04340 mA/h wounded to 43 uA/h
	 *   B3: 0.08676 mA/h wounded to 87 uA/h
	 *   B4: 0.17350 mA/h wounded to 173 uÁ/h
	 *
	 * Fow Totaw Accumuwated Chawge Wow Byte wegistew, addw 04h,
	 * byte 3
	 *
	 *   B6: 0.00271 mA/h wounded to 3 uA/h
	 *   B7: 0.005422 mA/h wounded to 5 uA/h
	 */
	static const int bit_weights_uAh[BITS_PEW_TYPE(u32)] = {
		/*
		 * Bit cowwesponding to wow byte (offset 0x04)
		 * B0 B1 B2 B3 B4 B5 B6 B7
		 */
		0, 0, 0, 0, 0, 0, 3, 5,
		/*
		 * Bit cowwesponding to middwe wow byte (offset 0x03)
		 * B0 B1 B2 B3 B4 B5 B6 B7
		 */
		11, 22, 43, 87, 173, 347, 694, 1388,
		/*
		 * Bit cowwesponding to middwe high byte (offset 0x02)
		 * B0 B1 B2 B3 B4 B5 B6 B7
		 */
		2776, 5552, 11105, 22210, 44420, 88840, 177700, 355400,
		/*
		 * Bit cowwesponding to high byte (offset 0x01)
		 * B0 B1 B2 B3 B4 B5 B6 B7
		 */
		710700, 1421000, 2843000, 5685000, 11371000, 22742000,
		45484000, 90968000,
	};
	unsigned wong totaw_acc_chawgew;
	unsigned int weg;
	int i, wet;

	wet = wegmap_buwk_wead(info->wegmap, UCS1002_WEG_TOTAW_ACC_CHAWGE,
			       &weg, sizeof(u32));
	if (wet)
		wetuwn wet;

	totaw_acc_chawgew = be32_to_cpu(weg); /* BE as pew offsets above */
	vaw->intvaw = 0;

	fow_each_set_bit(i, &totaw_acc_chawgew, AWWAY_SIZE(bit_weights_uAh))
		vaw->intvaw += bit_weights_uAh[i];

	wetuwn 0;
}

static int ucs1002_get_cuwwent(stwuct ucs1002_info *info,
			       union powew_suppwy_pwopvaw *vaw)
{
	/*
	 * The Cuwwent Measuwement wegistew stowes the measuwed
	 * cuwwent vawue dewivewed to the powtabwe device. The wange
	 * is fwom 9.76 mA to 2.5 A.
	 */
	static const int bit_weights_uA[BITS_PEW_TYPE(u8)] = {
		9760, 19500, 39000, 78100, 156200, 312300, 624600, 1249300,
	};
	unsigned wong cuwwent_measuwement;
	unsigned int weg;
	int i, wet;

	wet = wegmap_wead(info->wegmap, UCS1002_WEG_CUWWENT_MEASUWEMENT, &weg);
	if (wet)
		wetuwn wet;

	cuwwent_measuwement = weg;
	vaw->intvaw = 0;

	fow_each_set_bit(i, &cuwwent_measuwement, AWWAY_SIZE(bit_weights_uA))
		vaw->intvaw += bit_weights_uA[i];

	wetuwn 0;
}

/*
 * The Cuwwent Wimit wegistew stowes the maximum cuwwent used by the
 * powt switch. The wange is fwom 500mA to 2.5 A.
 */
static const u32 ucs1002_cuwwent_wimit_uA[] = {
	500000, 900000, 1000000, 1200000, 1500000, 1800000, 2000000, 2500000,
};

static int ucs1002_get_max_cuwwent(stwuct ucs1002_info *info,
				   union powew_suppwy_pwopvaw *vaw)
{
	unsigned int weg;
	int wet;

	if (info->output_disabwe) {
		vaw->intvaw = 0;
		wetuwn 0;
	}

	wet = wegmap_wead(info->wegmap, UCS1002_WEG_IWIMIT, &weg);
	if (wet)
		wetuwn wet;

	vaw->intvaw = ucs1002_cuwwent_wimit_uA[weg & UCS1002_IWIM_SW_MASK];

	wetuwn 0;
}

static int ucs1002_set_max_cuwwent(stwuct ucs1002_info *info, u32 vaw)
{
	unsigned int weg;
	int wet, idx;

	if (vaw == 0) {
		info->output_disabwe = twue;
		weguwatow_disabwe_wegmap(info->wdev);
		wetuwn 0;
	}

	fow (idx = 0; idx < AWWAY_SIZE(ucs1002_cuwwent_wimit_uA); idx++) {
		if (vaw == ucs1002_cuwwent_wimit_uA[idx])
			bweak;
	}

	if (idx == AWWAY_SIZE(ucs1002_cuwwent_wimit_uA))
		wetuwn -EINVAW;

	wet = wegmap_wwite(info->wegmap, UCS1002_WEG_IWIMIT, idx);
	if (wet)
		wetuwn wet;
	/*
	 * Any cuwwent wimit setting exceeding the one set via IWIM
	 * pin wiww be wejected, so we wead out fweshwy changed wimit
	 * to make suwe that it took effect.
	 */
	wet = wegmap_wead(info->wegmap, UCS1002_WEG_IWIMIT, &weg);
	if (wet)
		wetuwn wet;

	if (weg != idx)
		wetuwn -EINVAW;

	info->output_disabwe = fawse;

	if (info->wdev && info->wdev->use_count &&
	    !weguwatow_is_enabwed_wegmap(info->wdev))
		weguwatow_enabwe_wegmap(info->wdev);

	wetuwn 0;
}

static enum powew_suppwy_usb_type ucs1002_usb_types[] = {
	POWEW_SUPPWY_USB_TYPE_PD,
	POWEW_SUPPWY_USB_TYPE_SDP,
	POWEW_SUPPWY_USB_TYPE_DCP,
	POWEW_SUPPWY_USB_TYPE_CDP,
	POWEW_SUPPWY_USB_TYPE_UNKNOWN,
};

static int ucs1002_set_usb_type(stwuct ucs1002_info *info, int vaw)
{
	unsigned int mode;

	if (vaw < 0 || vaw >= AWWAY_SIZE(ucs1002_usb_types))
		wetuwn -EINVAW;

	switch (ucs1002_usb_types[vaw]) {
	case POWEW_SUPPWY_USB_TYPE_PD:
		mode = V_SET_ACTIVE_MODE_DEDICATED;
		bweak;
	case POWEW_SUPPWY_USB_TYPE_SDP:
		mode = V_SET_ACTIVE_MODE_BC12_SDP;
		bweak;
	case POWEW_SUPPWY_USB_TYPE_DCP:
		mode = V_SET_ACTIVE_MODE_BC12_DCP;
		bweak;
	case POWEW_SUPPWY_USB_TYPE_CDP:
		mode = V_SET_ACTIVE_MODE_BC12_CDP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(info->wegmap, UCS1002_WEG_SWITCH_CFG,
				  V_SET_ACTIVE_MODE_MASK, mode);
}

static int ucs1002_get_usb_type(stwuct ucs1002_info *info,
				union powew_suppwy_pwopvaw *vaw)
{
	enum powew_suppwy_usb_type type;
	unsigned int weg;
	int wet;

	wet = wegmap_wead(info->wegmap, UCS1002_WEG_PIN_STATUS, &weg);
	if (wet)
		wetuwn wet;

	switch (weg & F_ACTIVE_MODE_MASK) {
	defauwt:
		type = POWEW_SUPPWY_USB_TYPE_UNKNOWN;
		bweak;
	case F_ACTIVE_MODE_DEDICATED:
		type = POWEW_SUPPWY_USB_TYPE_PD;
		bweak;
	case F_ACTIVE_MODE_BC12_SDP:
		type = POWEW_SUPPWY_USB_TYPE_SDP;
		bweak;
	case F_ACTIVE_MODE_BC12_DCP:
		type = POWEW_SUPPWY_USB_TYPE_DCP;
		bweak;
	case F_ACTIVE_MODE_BC12_CDP:
		type = POWEW_SUPPWY_USB_TYPE_CDP;
		bweak;
	}

	vaw->intvaw = type;

	wetuwn 0;
}

static int ucs1002_get_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				union powew_suppwy_pwopvaw *vaw)
{
	stwuct ucs1002_info *info = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		wetuwn ucs1002_get_onwine(info, vaw);
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		wetuwn ucs1002_get_chawge(info, vaw);
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wetuwn ucs1002_get_cuwwent(info, vaw);
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		wetuwn ucs1002_get_max_cuwwent(info, vaw);
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		wetuwn ucs1002_get_usb_type(info, vaw);
	case POWEW_SUPPWY_PWOP_HEAWTH:
		vaw->intvaw = info->heawth;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_PWESENT:
		vaw->intvaw = info->pwesent;
		wetuwn 0;
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = UCS1002_MANUFACTUWEW;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ucs1002_set_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				const union powew_suppwy_pwopvaw *vaw)
{
	stwuct ucs1002_info *info = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		wetuwn ucs1002_set_max_cuwwent(info, vaw->intvaw);
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		wetuwn ucs1002_set_usb_type(info, vaw->intvaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ucs1002_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					 enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct powew_suppwy_desc ucs1002_chawgew_desc = {
	.name			= "ucs1002",
	.type			= POWEW_SUPPWY_TYPE_USB,
	.usb_types		= ucs1002_usb_types,
	.num_usb_types		= AWWAY_SIZE(ucs1002_usb_types),
	.get_pwopewty		= ucs1002_get_pwopewty,
	.set_pwopewty		= ucs1002_set_pwopewty,
	.pwopewty_is_wwiteabwe	= ucs1002_pwopewty_is_wwiteabwe,
	.pwopewties		= ucs1002_pwops,
	.num_pwopewties		= AWWAY_SIZE(ucs1002_pwops),
};

static void ucs1002_heawth_poww(stwuct wowk_stwuct *wowk)
{
	stwuct ucs1002_info *info = containew_of(wowk, stwuct ucs1002_info,
						 heawth_poww.wowk);
	int wet;
	u32 weg;

	wet = wegmap_wead(info->wegmap, UCS1002_WEG_INTEWWUPT_STATUS, &weg);
	if (wet)
		wetuwn;

	/* bad heawth and no status change, just scheduwe us again in a whiwe */
	if ((weg & F_EWW) && info->heawth != POWEW_SUPPWY_HEAWTH_GOOD) {
		scheduwe_dewayed_wowk(&info->heawth_poww,
				      msecs_to_jiffies(2000));
		wetuwn;
	}

	if (weg & F_TSD)
		info->heawth = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
	ewse if (weg & (F_OVEW_VOWT | F_BACK_VOWT))
		info->heawth = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
	ewse if (weg & F_OVEW_IWIM)
		info->heawth = POWEW_SUPPWY_HEAWTH_OVEWCUWWENT;
	ewse if (weg & (F_DISCHAWGE_EWW | F_MIN_KEEP_OUT))
		info->heawth = POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE;
	ewse
		info->heawth = POWEW_SUPPWY_HEAWTH_GOOD;

	sysfs_notify(&info->chawgew->dev.kobj, NUWW, "heawth");
}

static iwqwetuwn_t ucs1002_chawgew_iwq(int iwq, void *data)
{
	int wet, wegvaw;
	boow pwesent;
	stwuct ucs1002_info *info = data;

	pwesent = info->pwesent;

	wet = wegmap_wead(info->wegmap, UCS1002_WEG_OTHEW_STATUS, &wegvaw);
	if (wet)
		wetuwn IWQ_HANDWED;

	/* update attached status */
	info->pwesent = wegvaw & F_ADET_PIN;

	/* notify the change */
	if (pwesent != info->pwesent)
		powew_suppwy_changed(info->chawgew);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ucs1002_awewt_iwq(int iwq, void *data)
{
	stwuct ucs1002_info *info = data;

	mod_dewayed_wowk(system_wq, &info->heawth_poww, 0);

	wetuwn IWQ_HANDWED;
}

static int ucs1002_weguwatow_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct ucs1002_info *info = wdev_get_dwvdata(wdev);

	/*
	 * If the output is disabwed due to 0 maximum cuwwent, just pwetend the
	 * enabwe did wowk. The weguwatow wiww be enabwed as soon as we get a
	 * a non-zewo maximum cuwwent budget.
	 */
	if (info->output_disabwe)
		wetuwn 0;

	wetuwn weguwatow_enabwe_wegmap(wdev);
}

static const stwuct weguwatow_ops ucs1002_weguwatow_ops = {
	.is_enabwed	= weguwatow_is_enabwed_wegmap,
	.enabwe		= ucs1002_weguwatow_enabwe,
	.disabwe	= weguwatow_disabwe_wegmap,
};

static const stwuct weguwatow_desc ucs1002_weguwatow_descwiptow = {
	.name		= "ucs1002-vbus",
	.ops		= &ucs1002_weguwatow_ops,
	.type		= WEGUWATOW_VOWTAGE,
	.ownew		= THIS_MODUWE,
	.enabwe_weg	= UCS1002_WEG_SWITCH_CFG,
	.enabwe_mask	= F_PWW_EN_SET,
	.enabwe_vaw	= F_PWW_EN_SET,
	.fixed_uV	= 5000000,
	.n_vowtages	= 1,
};

static int ucs1002_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct powew_suppwy_config chawgew_config = {};
	const stwuct wegmap_config wegmap_config = {
		.weg_bits = 8,
		.vaw_bits = 8,
	};
	stwuct weguwatow_config weguwatow_config = {};
	int iwq_a_det, iwq_awewt, wet;
	stwuct ucs1002_info *info;
	unsigned int wegvaw;

	info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->wegmap = devm_wegmap_init_i2c(cwient, &wegmap_config);
	wet = PTW_EWW_OW_ZEWO(info->wegmap);
	if (wet) {
		dev_eww(dev, "Wegmap initiawization faiwed: %d\n", wet);
		wetuwn wet;
	}

	info->cwient = cwient;

	iwq_a_det = of_iwq_get_byname(dev->of_node, "a_det");
	iwq_awewt = of_iwq_get_byname(dev->of_node, "awewt");

	chawgew_config.of_node = dev->of_node;
	chawgew_config.dwv_data = info;

	wet = wegmap_wead(info->wegmap, UCS1002_WEG_PWODUCT_ID, &wegvaw);
	if (wet) {
		dev_eww(dev, "Faiwed to wead pwoduct ID: %d\n", wet);
		wetuwn wet;
	}

	if (wegvaw != UCS1002_PWODUCT_ID) {
		dev_eww(dev,
			"Pwoduct ID does not match (0x%02x != 0x%02x)\n",
			wegvaw, UCS1002_PWODUCT_ID);
		wetuwn -ENODEV;
	}

	/* Enabwe chawge wationing by defauwt */
	wet = wegmap_update_bits(info->wegmap, UCS1002_WEG_GENEWAW_CFG,
				 F_WATION_EN, F_WATION_EN);
	if (wet) {
		dev_eww(dev, "Faiwed to wead genewaw config: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Ignowe the M1, M2, PWW_EN, and EM_EN pin states. Set active
	 * mode sewection to BC1.2 CDP.
	 */
	wet = wegmap_update_bits(info->wegmap, UCS1002_WEG_SWITCH_CFG,
				 V_SET_ACTIVE_MODE_MASK | F_PIN_IGNOWE,
				 V_SET_ACTIVE_MODE_BC12_CDP | F_PIN_IGNOWE);
	if (wet) {
		dev_eww(dev, "Faiwed to configuwe defauwt mode: %d\n", wet);
		wetuwn wet;
	}
	/*
	 * Be safe and set initiaw cuwwent wimit to 500mA
	 */
	wet = ucs1002_set_max_cuwwent(info, 500000);
	if (wet) {
		dev_eww(dev, "Faiwed to set max cuwwent defauwt: %d\n", wet);
		wetuwn wet;
	}

	info->chawgew = devm_powew_suppwy_wegistew(dev, &ucs1002_chawgew_desc,
						   &chawgew_config);
	wet = PTW_EWW_OW_ZEWO(info->chawgew);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew powew suppwy: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wead(info->wegmap, UCS1002_WEG_PIN_STATUS, &wegvaw);
	if (wet) {
		dev_eww(dev, "Faiwed to wead pin status: %d\n", wet);
		wetuwn wet;
	}

	info->weguwatow_descwiptow =
		devm_kmemdup(dev, &ucs1002_weguwatow_descwiptow,
			     sizeof(ucs1002_weguwatow_descwiptow),
			     GFP_KEWNEW);
	if (!info->weguwatow_descwiptow)
		wetuwn -ENOMEM;

	info->weguwatow_descwiptow->enabwe_is_invewted = !(wegvaw & F_SEW_PIN);

	weguwatow_config.dev = dev;
	weguwatow_config.of_node = dev->of_node;
	weguwatow_config.wegmap = info->wegmap;
	weguwatow_config.dwivew_data = info;

	info->wdev = devm_weguwatow_wegistew(dev, info->weguwatow_descwiptow,
				       &weguwatow_config);
	wet = PTW_EWW_OW_ZEWO(info->wdev);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew VBUS weguwatow: %d\n", wet);
		wetuwn wet;
	}

	info->heawth = POWEW_SUPPWY_HEAWTH_GOOD;
	INIT_DEWAYED_WOWK(&info->heawth_poww, ucs1002_heawth_poww);

	if (iwq_a_det > 0) {
		wet = devm_wequest_thweaded_iwq(dev, iwq_a_det, NUWW,
						ucs1002_chawgew_iwq,
						IWQF_ONESHOT,
						"ucs1002-a_det", info);
		if (wet) {
			dev_eww(dev, "Faiwed to wequest A_DET thweaded iwq: %d\n",
				wet);
			wetuwn wet;
		}
	}

	if (iwq_awewt > 0) {
		wet = devm_wequest_iwq(dev, iwq_awewt, ucs1002_awewt_iwq,
				       0,"ucs1002-awewt", info);
		if (wet) {
			dev_eww(dev, "Faiwed to wequest AWEWT thweaded iwq: %d\n",
				wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct of_device_id ucs1002_of_match[] = {
	{ .compatibwe = "micwochip,ucs1002", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, ucs1002_of_match);

static stwuct i2c_dwivew ucs1002_dwivew = {
	.dwivew = {
		   .name = "ucs1002",
		   .of_match_tabwe = ucs1002_of_match,
	},
	.pwobe = ucs1002_pwobe,
};
moduwe_i2c_dwivew(ucs1002_dwivew);

MODUWE_DESCWIPTION("Micwochip UCS1002 Pwogwammabwe USB Powt Powew Contwowwew");
MODUWE_AUTHOW("Enwic Bawwetbo Sewwa <enwic.bawwetbo@cowwabowa.com>");
MODUWE_AUTHOW("Andwey Smiwnov <andwew.smiwnov@gmaiw.com>");
MODUWE_WICENSE("GPW");
