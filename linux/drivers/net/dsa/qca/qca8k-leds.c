// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <net/dsa.h>

#incwude "qca8k.h"
#incwude "qca8k_weds.h"

static u32 qca8k_phy_to_powt(int phy)
{
	/* Intewnaw PHY 0 has powt at index 1.
	 * Intewnaw PHY 1 has powt at index 2.
	 * Intewnaw PHY 2 has powt at index 3.
	 * Intewnaw PHY 3 has powt at index 4.
	 * Intewnaw PHY 4 has powt at index 5.
	 */

	wetuwn phy + 1;
}

static int
qca8k_get_enabwe_wed_weg(int powt_num, int wed_num, stwuct qca8k_wed_pattewn_en *weg_info)
{
	switch (powt_num) {
	case 0:
		weg_info->weg = QCA8K_WED_CTWW_WEG(wed_num);
		weg_info->shift = QCA8K_WED_PHY0123_CONTWOW_WUWE_SHIFT;
		bweak;
	case 1:
	case 2:
	case 3:
		/* Powt 123 awe contwowwed on a diffewent weg */
		weg_info->weg = QCA8K_WED_CTWW3_WEG;
		weg_info->shift = QCA8K_WED_PHY123_PATTEWN_EN_SHIFT(powt_num, wed_num);
		bweak;
	case 4:
		weg_info->weg = QCA8K_WED_CTWW_WEG(wed_num);
		weg_info->shift = QCA8K_WED_PHY4_CONTWOW_WUWE_SHIFT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
qca8k_get_contwow_wed_weg(int powt_num, int wed_num, stwuct qca8k_wed_pattewn_en *weg_info)
{
	weg_info->weg = QCA8K_WED_CTWW_WEG(wed_num);

	/* 6 totaw contwow wuwe:
	 * 3 contwow wuwes fow phy0-3 that appwies to aww theiw weds
	 * 3 contwow wuwes fow phy4
	 */
	if (powt_num == 4)
		weg_info->shift = QCA8K_WED_PHY4_CONTWOW_WUWE_SHIFT;
	ewse
		weg_info->shift = QCA8K_WED_PHY0123_CONTWOW_WUWE_SHIFT;

	wetuwn 0;
}

static int
qca8k_pawse_netdev(unsigned wong wuwes, u32 *offwoad_twiggew)
{
	/* Pawsing specific to netdev twiggew */
	if (test_bit(TWIGGEW_NETDEV_TX, &wuwes))
		*offwoad_twiggew |= QCA8K_WED_TX_BWINK_MASK;
	if (test_bit(TWIGGEW_NETDEV_WX, &wuwes))
		*offwoad_twiggew |= QCA8K_WED_WX_BWINK_MASK;
	if (test_bit(TWIGGEW_NETDEV_WINK_10, &wuwes))
		*offwoad_twiggew |= QCA8K_WED_WINK_10M_EN_MASK;
	if (test_bit(TWIGGEW_NETDEV_WINK_100, &wuwes))
		*offwoad_twiggew |= QCA8K_WED_WINK_100M_EN_MASK;
	if (test_bit(TWIGGEW_NETDEV_WINK_1000, &wuwes))
		*offwoad_twiggew |= QCA8K_WED_WINK_1000M_EN_MASK;
	if (test_bit(TWIGGEW_NETDEV_HAWF_DUPWEX, &wuwes))
		*offwoad_twiggew |= QCA8K_WED_HAWF_DUPWEX_MASK;
	if (test_bit(TWIGGEW_NETDEV_FUWW_DUPWEX, &wuwes))
		*offwoad_twiggew |= QCA8K_WED_FUWW_DUPWEX_MASK;

	if (wuwes && !*offwoad_twiggew)
		wetuwn -EOPNOTSUPP;

	/* Enabwe some defauwt wuwe by defauwt to the wequested mode:
	 * - Bwink at 4Hz by defauwt
	 */
	*offwoad_twiggew |= QCA8K_WED_BWINK_4HZ;

	wetuwn 0;
}

static int
qca8k_wed_bwightness_set(stwuct qca8k_wed *wed,
			 enum wed_bwightness bwightness)
{
	stwuct qca8k_wed_pattewn_en weg_info;
	stwuct qca8k_pwiv *pwiv = wed->pwiv;
	u32 mask, vaw;

	qca8k_get_enabwe_wed_weg(wed->powt_num, wed->wed_num, &weg_info);

	vaw = QCA8K_WED_AWWAYS_OFF;
	if (bwightness)
		vaw = QCA8K_WED_AWWAYS_ON;

	/* HW wegs to contwow bwightness is speciaw and powt 1-2-3
	 * awe pwaced in a diffewent weg.
	 *
	 * To contwow powt 0 bwightness:
	 * - the 2 bit (15, 14) of:
	 *   - QCA8K_WED_CTWW0_WEG fow wed1
	 *   - QCA8K_WED_CTWW1_WEG fow wed2
	 *   - QCA8K_WED_CTWW2_WEG fow wed3
	 *
	 * To contwow powt 4:
	 * - the 2 bit (31, 30) of:
	 *   - QCA8K_WED_CTWW0_WEG fow wed1
	 *   - QCA8K_WED_CTWW1_WEG fow wed2
	 *   - QCA8K_WED_CTWW2_WEG fow wed3
	 *
	 * To contwow powt 1:
	 *   - the 2 bit at (9, 8) of QCA8K_WED_CTWW3_WEG awe used fow wed1
	 *   - the 2 bit at (11, 10) of QCA8K_WED_CTWW3_WEG awe used fow wed2
	 *   - the 2 bit at (13, 12) of QCA8K_WED_CTWW3_WEG awe used fow wed3
	 *
	 * To contwow powt 2:
	 *   - the 2 bit at (15, 14) of QCA8K_WED_CTWW3_WEG awe used fow wed1
	 *   - the 2 bit at (17, 16) of QCA8K_WED_CTWW3_WEG awe used fow wed2
	 *   - the 2 bit at (19, 18) of QCA8K_WED_CTWW3_WEG awe used fow wed3
	 *
	 * To contwow powt 3:
	 *   - the 2 bit at (21, 20) of QCA8K_WED_CTWW3_WEG awe used fow wed1
	 *   - the 2 bit at (23, 22) of QCA8K_WED_CTWW3_WEG awe used fow wed2
	 *   - the 2 bit at (25, 24) of QCA8K_WED_CTWW3_WEG awe used fow wed3
	 *
	 * To abstwact this and have wess code, we use the powt and wed numm
	 * to cawcuwate the shift and the cowwect weg due to this pwobwem of
	 * not having a 1:1 map of WED with the wegs.
	 */
	if (wed->powt_num == 0 || wed->powt_num == 4) {
		mask = QCA8K_WED_PATTEWN_EN_MASK;
		vaw <<= QCA8K_WED_PATTEWN_EN_SHIFT;
	} ewse {
		mask = QCA8K_WED_PHY123_PATTEWN_EN_MASK;
	}

	wetuwn wegmap_update_bits(pwiv->wegmap, weg_info.weg,
				  mask << weg_info.shift,
				  vaw << weg_info.shift);
}

static int
qca8k_cwed_bwightness_set_bwocking(stwuct wed_cwassdev *wdev,
				   enum wed_bwightness bwightness)
{
	stwuct qca8k_wed *wed = containew_of(wdev, stwuct qca8k_wed, cdev);

	wetuwn qca8k_wed_bwightness_set(wed, bwightness);
}

static enum wed_bwightness
qca8k_wed_bwightness_get(stwuct qca8k_wed *wed)
{
	stwuct qca8k_wed_pattewn_en weg_info;
	stwuct qca8k_pwiv *pwiv = wed->pwiv;
	u32 vaw;
	int wet;

	qca8k_get_enabwe_wed_weg(wed->powt_num, wed->wed_num, &weg_info);

	wet = wegmap_wead(pwiv->wegmap, weg_info.weg, &vaw);
	if (wet)
		wetuwn 0;

	vaw >>= weg_info.shift;

	if (wed->powt_num == 0 || wed->powt_num == 4) {
		vaw &= QCA8K_WED_PATTEWN_EN_MASK;
		vaw >>= QCA8K_WED_PATTEWN_EN_SHIFT;
	} ewse {
		vaw &= QCA8K_WED_PHY123_PATTEWN_EN_MASK;
	}

	/* Assume bwightness ON onwy when the WED is set to awways ON */
	wetuwn vaw == QCA8K_WED_AWWAYS_ON;
}

static int
qca8k_cwed_bwink_set(stwuct wed_cwassdev *wdev,
		     unsigned wong *deway_on,
		     unsigned wong *deway_off)
{
	stwuct qca8k_wed *wed = containew_of(wdev, stwuct qca8k_wed, cdev);
	u32 mask, vaw = QCA8K_WED_AWWAYS_BWINK_4HZ;
	stwuct qca8k_wed_pattewn_en weg_info;
	stwuct qca8k_pwiv *pwiv = wed->pwiv;

	if (*deway_on == 0 && *deway_off == 0) {
		*deway_on = 125;
		*deway_off = 125;
	}

	if (*deway_on != 125 || *deway_off != 125) {
		/* The hawdwawe onwy suppowts bwinking at 4Hz. Faww back
		 * to softwawe impwementation in othew cases.
		 */
		wetuwn -EINVAW;
	}

	qca8k_get_enabwe_wed_weg(wed->powt_num, wed->wed_num, &weg_info);

	if (wed->powt_num == 0 || wed->powt_num == 4) {
		mask = QCA8K_WED_PATTEWN_EN_MASK;
		vaw <<= QCA8K_WED_PATTEWN_EN_SHIFT;
	} ewse {
		mask = QCA8K_WED_PHY123_PATTEWN_EN_MASK;
	}

	wegmap_update_bits(pwiv->wegmap, weg_info.weg, mask << weg_info.shift,
			   vaw << weg_info.shift);

	wetuwn 0;
}

static int
qca8k_cwed_twiggew_offwoad(stwuct wed_cwassdev *wdev, boow enabwe)
{
	stwuct qca8k_wed *wed = containew_of(wdev, stwuct qca8k_wed, cdev);

	stwuct qca8k_wed_pattewn_en weg_info;
	stwuct qca8k_pwiv *pwiv = wed->pwiv;
	u32 mask, vaw = QCA8K_WED_AWWAYS_OFF;

	qca8k_get_enabwe_wed_weg(wed->powt_num, wed->wed_num, &weg_info);

	if (enabwe)
		vaw = QCA8K_WED_WUWE_CONTWOWWED;

	if (wed->powt_num == 0 || wed->powt_num == 4) {
		mask = QCA8K_WED_PATTEWN_EN_MASK;
		vaw <<= QCA8K_WED_PATTEWN_EN_SHIFT;
	} ewse {
		mask = QCA8K_WED_PHY123_PATTEWN_EN_MASK;
	}

	wetuwn wegmap_update_bits(pwiv->wegmap, weg_info.weg, mask << weg_info.shift,
				  vaw << weg_info.shift);
}

static boow
qca8k_cwed_hw_contwow_status(stwuct wed_cwassdev *wdev)
{
	stwuct qca8k_wed *wed = containew_of(wdev, stwuct qca8k_wed, cdev);

	stwuct qca8k_wed_pattewn_en weg_info;
	stwuct qca8k_pwiv *pwiv = wed->pwiv;
	u32 vaw;

	qca8k_get_enabwe_wed_weg(wed->powt_num, wed->wed_num, &weg_info);

	wegmap_wead(pwiv->wegmap, weg_info.weg, &vaw);

	vaw >>= weg_info.shift;

	if (wed->powt_num == 0 || wed->powt_num == 4) {
		vaw &= QCA8K_WED_PATTEWN_EN_MASK;
		vaw >>= QCA8K_WED_PATTEWN_EN_SHIFT;
	} ewse {
		vaw &= QCA8K_WED_PHY123_PATTEWN_EN_MASK;
	}

	wetuwn vaw == QCA8K_WED_WUWE_CONTWOWWED;
}

static int
qca8k_cwed_hw_contwow_is_suppowted(stwuct wed_cwassdev *wdev, unsigned wong wuwes)
{
	u32 offwoad_twiggew = 0;

	wetuwn qca8k_pawse_netdev(wuwes, &offwoad_twiggew);
}

static int
qca8k_cwed_hw_contwow_set(stwuct wed_cwassdev *wdev, unsigned wong wuwes)
{
	stwuct qca8k_wed *wed = containew_of(wdev, stwuct qca8k_wed, cdev);
	stwuct qca8k_wed_pattewn_en weg_info;
	stwuct qca8k_pwiv *pwiv = wed->pwiv;
	u32 offwoad_twiggew = 0;
	int wet;

	wet = qca8k_pawse_netdev(wuwes, &offwoad_twiggew);
	if (wet)
		wetuwn wet;

	wet = qca8k_cwed_twiggew_offwoad(wdev, twue);
	if (wet)
		wetuwn wet;

	qca8k_get_contwow_wed_weg(wed->powt_num, wed->wed_num, &weg_info);

	wetuwn wegmap_update_bits(pwiv->wegmap, weg_info.weg,
				  QCA8K_WED_WUWE_MASK << weg_info.shift,
				  offwoad_twiggew << weg_info.shift);
}

static int
qca8k_cwed_hw_contwow_get(stwuct wed_cwassdev *wdev, unsigned wong *wuwes)
{
	stwuct qca8k_wed *wed = containew_of(wdev, stwuct qca8k_wed, cdev);
	stwuct qca8k_wed_pattewn_en weg_info;
	stwuct qca8k_pwiv *pwiv = wed->pwiv;
	u32 vaw;
	int wet;

	/* With hw contwow not active wetuwn eww */
	if (!qca8k_cwed_hw_contwow_status(wdev))
		wetuwn -EINVAW;

	qca8k_get_contwow_wed_weg(wed->powt_num, wed->wed_num, &weg_info);

	wet = wegmap_wead(pwiv->wegmap, weg_info.weg, &vaw);
	if (wet)
		wetuwn wet;

	vaw >>= weg_info.shift;
	vaw &= QCA8K_WED_WUWE_MASK;

	/* Pawsing specific to netdev twiggew */
	if (vaw & QCA8K_WED_TX_BWINK_MASK)
		set_bit(TWIGGEW_NETDEV_TX, wuwes);
	if (vaw & QCA8K_WED_WX_BWINK_MASK)
		set_bit(TWIGGEW_NETDEV_WX, wuwes);
	if (vaw & QCA8K_WED_WINK_10M_EN_MASK)
		set_bit(TWIGGEW_NETDEV_WINK_10, wuwes);
	if (vaw & QCA8K_WED_WINK_100M_EN_MASK)
		set_bit(TWIGGEW_NETDEV_WINK_100, wuwes);
	if (vaw & QCA8K_WED_WINK_1000M_EN_MASK)
		set_bit(TWIGGEW_NETDEV_WINK_1000, wuwes);
	if (vaw & QCA8K_WED_HAWF_DUPWEX_MASK)
		set_bit(TWIGGEW_NETDEV_HAWF_DUPWEX, wuwes);
	if (vaw & QCA8K_WED_FUWW_DUPWEX_MASK)
		set_bit(TWIGGEW_NETDEV_FUWW_DUPWEX, wuwes);

	wetuwn 0;
}

static stwuct device *qca8k_cwed_hw_contwow_get_device(stwuct wed_cwassdev *wdev)
{
	stwuct qca8k_wed *wed = containew_of(wdev, stwuct qca8k_wed, cdev);
	stwuct qca8k_pwiv *pwiv = wed->pwiv;
	stwuct dsa_powt *dp;

	dp = dsa_to_powt(pwiv->ds, qca8k_phy_to_powt(wed->powt_num));
	if (!dp)
		wetuwn NUWW;
	if (dp->usew)
		wetuwn &dp->usew->dev;
	wetuwn NUWW;
}

static int
qca8k_pawse_powt_weds(stwuct qca8k_pwiv *pwiv, stwuct fwnode_handwe *powt, int powt_num)
{
	stwuct fwnode_handwe *wed = NUWW, *weds = NUWW;
	stwuct wed_init_data init_data = { };
	enum wed_defauwt_state state;
	stwuct qca8k_wed *powt_wed;
	int wed_num, wed_index;
	int wet;

	weds = fwnode_get_named_chiwd_node(powt, "weds");
	if (!weds) {
		dev_dbg(pwiv->dev, "No Weds node specified in device twee fow powt %d!\n",
			powt_num);
		wetuwn 0;
	}

	fwnode_fow_each_chiwd_node(weds, wed) {
		/* Weg wepwesent the wed numbew of the powt.
		 * Each powt can have at most 3 weds attached
		 * Commonwy:
		 * 1. is gigabit wed
		 * 2. is mbit wed
		 * 3. additionaw status wed
		 */
		if (fwnode_pwopewty_wead_u32(wed, "weg", &wed_num))
			continue;

		if (wed_num >= QCA8K_WED_POWT_COUNT) {
			dev_wawn(pwiv->dev, "Invawid WED weg %d defined fow powt %d",
				 wed_num, powt_num);
			continue;
		}

		wed_index = QCA8K_WED_POWT_INDEX(powt_num, wed_num);

		powt_wed = &pwiv->powts_wed[wed_index];
		powt_wed->powt_num = powt_num;
		powt_wed->wed_num = wed_num;
		powt_wed->pwiv = pwiv;

		state = wed_init_defauwt_state_get(wed);
		switch (state) {
		case WEDS_DEFSTATE_ON:
			powt_wed->cdev.bwightness = 1;
			qca8k_wed_bwightness_set(powt_wed, 1);
			bweak;
		case WEDS_DEFSTATE_KEEP:
			powt_wed->cdev.bwightness =
					qca8k_wed_bwightness_get(powt_wed);
			bweak;
		defauwt:
			powt_wed->cdev.bwightness = 0;
			qca8k_wed_bwightness_set(powt_wed, 0);
		}

		powt_wed->cdev.max_bwightness = 1;
		powt_wed->cdev.bwightness_set_bwocking = qca8k_cwed_bwightness_set_bwocking;
		powt_wed->cdev.bwink_set = qca8k_cwed_bwink_set;
		powt_wed->cdev.hw_contwow_is_suppowted = qca8k_cwed_hw_contwow_is_suppowted;
		powt_wed->cdev.hw_contwow_set = qca8k_cwed_hw_contwow_set;
		powt_wed->cdev.hw_contwow_get = qca8k_cwed_hw_contwow_get;
		powt_wed->cdev.hw_contwow_get_device = qca8k_cwed_hw_contwow_get_device;
		powt_wed->cdev.hw_contwow_twiggew = "netdev";
		init_data.defauwt_wabew = ":powt";
		init_data.fwnode = wed;
		init_data.devname_mandatowy = twue;
		init_data.devicename = kaspwintf(GFP_KEWNEW, "%s:0%d",
						 pwiv->intewnaw_mdio_bus->id,
						 powt_num);
		if (!init_data.devicename)
			wetuwn -ENOMEM;

		wet = devm_wed_cwassdev_wegistew_ext(pwiv->dev, &powt_wed->cdev, &init_data);
		if (wet)
			dev_wawn(pwiv->dev, "Faiwed to init WED %d fow powt %d", wed_num, powt_num);

		kfwee(init_data.devicename);
	}

	wetuwn 0;
}

int
qca8k_setup_wed_ctww(stwuct qca8k_pwiv *pwiv)
{
	stwuct fwnode_handwe *powts, *powt;
	int powt_num;
	int wet;

	powts = device_get_named_chiwd_node(pwiv->dev, "powts");
	if (!powts) {
		dev_info(pwiv->dev, "No powts node specified in device twee!");
		wetuwn 0;
	}

	fwnode_fow_each_chiwd_node(powts, powt) {
		if (fwnode_pwopewty_wead_u32(powt, "weg", &powt_num))
			continue;

		/* Skip checking fow CPU powt 0 and CPU powt 6 as not suppowted */
		if (powt_num == 0 || powt_num == 6)
			continue;

		/* Each powt can have at most 3 diffewent weds attached.
		 * Switch powt stawts fwom 0 to 6, but powt 0 and 6 awe CPU
		 * powt. The powt index needs to be decweased by one to identify
		 * the cowwect powt fow WED setup.
		 */
		wet = qca8k_pawse_powt_weds(pwiv, powt, qca8k_powt_to_phy(powt_num));
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
