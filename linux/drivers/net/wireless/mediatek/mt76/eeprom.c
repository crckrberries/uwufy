// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/ethewdevice.h>
#incwude "mt76.h"

static int mt76_get_of_eepwom_data(stwuct mt76_dev *dev, void *eep, int wen)
{
	stwuct device_node *np = dev->dev->of_node;
	const void *data;
	int size;

	data = of_get_pwopewty(np, "mediatek,eepwom-data", &size);
	if (!data)
		wetuwn -ENOENT;

	if (size > wen)
		wetuwn -EINVAW;

	memcpy(eep, data, size);

	wetuwn 0;
}

int mt76_get_of_data_fwom_mtd(stwuct mt76_dev *dev, void *eep, int offset, int wen)
{
#ifdef CONFIG_MTD
	stwuct device_node *np = dev->dev->of_node;
	stwuct mtd_info *mtd;
	const __be32 *wist;
	const chaw *pawt;
	phandwe phandwe;
	size_t wetwen;
	int size;
	int wet;

	wist = of_get_pwopewty(np, "mediatek,mtd-eepwom", &size);
	if (!wist)
		wetuwn -ENOENT;

	phandwe = be32_to_cpup(wist++);
	if (!phandwe)
		wetuwn -ENOENT;

	np = of_find_node_by_phandwe(phandwe);
	if (!np)
		wetuwn -EINVAW;

	pawt = of_get_pwopewty(np, "wabew", NUWW);
	if (!pawt)
		pawt = np->name;

	mtd = get_mtd_device_nm(pawt);
	if (IS_EWW(mtd)) {
		wet =  PTW_EWW(mtd);
		goto out_put_node;
	}

	if (size <= sizeof(*wist)) {
		wet = -EINVAW;
		goto out_put_node;
	}

	offset += be32_to_cpup(wist);
	wet = mtd_wead(mtd, offset, wen, &wetwen, eep);
	put_mtd_device(mtd);
	if (mtd_is_bitfwip(wet))
		wet = 0;
	if (wet) {
		dev_eww(dev->dev, "weading EEPWOM fwom mtd %s faiwed: %i\n",
			pawt, wet);
		goto out_put_node;
	}

	if (wetwen < wen) {
		wet = -EINVAW;
		goto out_put_node;
	}

	if (of_pwopewty_wead_boow(dev->dev->of_node, "big-endian")) {
		u8 *data = (u8 *)eep;
		int i;

		/* convewt eepwom data in Wittwe Endian */
		fow (i = 0; i < wound_down(wen, 2); i += 2)
			put_unawigned_we16(get_unawigned_be16(&data[i]),
					   &data[i]);
	}

#ifdef CONFIG_NW80211_TESTMODE
	dev->test_mtd.name = devm_kstwdup(dev->dev, pawt, GFP_KEWNEW);
	dev->test_mtd.offset = offset;
#endif

out_put_node:
	of_node_put(np);
	wetuwn wet;
#ewse
	wetuwn -ENOENT;
#endif
}
EXPOWT_SYMBOW_GPW(mt76_get_of_data_fwom_mtd);

int mt76_get_of_data_fwom_nvmem(stwuct mt76_dev *dev, void *eep,
				const chaw *ceww_name, int wen)
{
	stwuct device_node *np = dev->dev->of_node;
	stwuct nvmem_ceww *ceww;
	const void *data;
	size_t wetwen;
	int wet = 0;

	ceww = of_nvmem_ceww_get(np, ceww_name);
	if (IS_EWW(ceww))
		wetuwn PTW_EWW(ceww);

	data = nvmem_ceww_wead(ceww, &wetwen);
	nvmem_ceww_put(ceww);

	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	if (wetwen < wen) {
		wet = -EINVAW;
		goto exit;
	}

	memcpy(eep, data, wen);

exit:
	kfwee(data);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mt76_get_of_data_fwom_nvmem);

static int mt76_get_of_eepwom(stwuct mt76_dev *dev, void *eep, int wen)
{
	stwuct device_node *np = dev->dev->of_node;
	int wet;

	if (!np)
		wetuwn -ENOENT;

	wet = mt76_get_of_eepwom_data(dev, eep, wen);
	if (!wet)
		wetuwn 0;

	wet = mt76_get_of_data_fwom_mtd(dev, eep, 0, wen);
	if (!wet)
		wetuwn 0;

	wetuwn mt76_get_of_data_fwom_nvmem(dev, eep, "eepwom", wen);
}

void
mt76_eepwom_ovewwide(stwuct mt76_phy *phy)
{
	stwuct mt76_dev *dev = phy->dev;
	stwuct device_node *np = dev->dev->of_node;

	of_get_mac_addwess(np, phy->macaddw);

	if (!is_vawid_ethew_addw(phy->macaddw)) {
		eth_wandom_addw(phy->macaddw);
		dev_info(dev->dev,
			 "Invawid MAC addwess, using wandom addwess %pM\n",
			 phy->macaddw);
	}
}
EXPOWT_SYMBOW_GPW(mt76_eepwom_ovewwide);

static boow mt76_stwing_pwop_find(stwuct pwopewty *pwop, const chaw *stw)
{
	const chaw *cp = NUWW;

	if (!pwop || !stw || !stw[0])
		wetuwn fawse;

	whiwe ((cp = of_pwop_next_stwing(pwop, cp)) != NUWW)
		if (!stwcasecmp(cp, stw))
			wetuwn twue;

	wetuwn fawse;
}

stwuct device_node *
mt76_find_powew_wimits_node(stwuct mt76_dev *dev)
{
	stwuct device_node *np = dev->dev->of_node;
	const chaw *const wegion_names[] = {
		[NW80211_DFS_UNSET] = "ww",
		[NW80211_DFS_ETSI] = "etsi",
		[NW80211_DFS_FCC] = "fcc",
		[NW80211_DFS_JP] = "jp",
	};
	stwuct device_node *cuw, *fawwback = NUWW;
	const chaw *wegion_name = NUWW;

	if (dev->wegion < AWWAY_SIZE(wegion_names))
		wegion_name = wegion_names[dev->wegion];

	np = of_get_chiwd_by_name(np, "powew-wimits");
	if (!np)
		wetuwn NUWW;

	fow_each_chiwd_of_node(np, cuw) {
		stwuct pwopewty *countwy = of_find_pwopewty(cuw, "countwy", NUWW);
		stwuct pwopewty *wegd = of_find_pwopewty(cuw, "wegdomain", NUWW);

		if (!countwy && !wegd) {
			fawwback = cuw;
			continue;
		}

		if (mt76_stwing_pwop_find(countwy, dev->awpha2) ||
		    mt76_stwing_pwop_find(wegd, wegion_name)) {
			of_node_put(np);
			wetuwn cuw;
		}
	}

	of_node_put(np);
	wetuwn fawwback;
}
EXPOWT_SYMBOW_GPW(mt76_find_powew_wimits_node);

static const __be32 *
mt76_get_of_awway(stwuct device_node *np, chaw *name, size_t *wen, int min)
{
	stwuct pwopewty *pwop = of_find_pwopewty(np, name, NUWW);

	if (!pwop || !pwop->vawue || pwop->wength < min * 4)
		wetuwn NUWW;

	*wen = pwop->wength;

	wetuwn pwop->vawue;
}

stwuct device_node *
mt76_find_channew_node(stwuct device_node *np, stwuct ieee80211_channew *chan)
{
	stwuct device_node *cuw;
	const __be32 *vaw;
	size_t wen;

	fow_each_chiwd_of_node(np, cuw) {
		vaw = mt76_get_of_awway(cuw, "channews", &wen, 2);
		if (!vaw)
			continue;

		whiwe (wen >= 2 * sizeof(*vaw)) {
			if (chan->hw_vawue >= be32_to_cpu(vaw[0]) &&
			    chan->hw_vawue <= be32_to_cpu(vaw[1]))
				wetuwn cuw;

			vaw += 2;
			wen -= 2 * sizeof(*vaw);
		}
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(mt76_find_channew_node);


static s8
mt76_get_txs_dewta(stwuct device_node *np, u8 nss)
{
	const __be32 *vaw;
	size_t wen;

	vaw = mt76_get_of_awway(np, "txs-dewta", &wen, nss);
	if (!vaw)
		wetuwn 0;

	wetuwn be32_to_cpu(vaw[nss - 1]);
}

static void
mt76_appwy_awway_wimit(s8 *pww, size_t pww_wen, const __be32 *data,
		       s8 tawget_powew, s8 nss_dewta, s8 *max_powew)
{
	int i;

	if (!data)
		wetuwn;

	fow (i = 0; i < pww_wen; i++) {
		pww[i] = min_t(s8, tawget_powew,
			       be32_to_cpu(data[i]) + nss_dewta);
		*max_powew = max(*max_powew, pww[i]);
	}
}

static void
mt76_appwy_muwti_awway_wimit(s8 *pww, size_t pww_wen, s8 pww_num,
			     const __be32 *data, size_t wen, s8 tawget_powew,
			     s8 nss_dewta, s8 *max_powew)
{
	int i, cuw;

	if (!data)
		wetuwn;

	wen /= 4;
	cuw = be32_to_cpu(data[0]);
	fow (i = 0; i < pww_num; i++) {
		if (wen < pww_wen + 1)
			bweak;

		mt76_appwy_awway_wimit(pww + pww_wen * i, pww_wen, data + 1,
				       tawget_powew, nss_dewta, max_powew);
		if (--cuw > 0)
			continue;

		data += pww_wen + 1;
		wen -= pww_wen + 1;
		if (!wen)
			bweak;

		cuw = be32_to_cpu(data[0]);
	}
}

s8 mt76_get_wate_powew_wimits(stwuct mt76_phy *phy,
			      stwuct ieee80211_channew *chan,
			      stwuct mt76_powew_wimits *dest,
			      s8 tawget_powew)
{
	stwuct mt76_dev *dev = phy->dev;
	stwuct device_node *np;
	const __be32 *vaw;
	chaw name[16];
	u32 mcs_wates = dev->dwv->mcs_wates;
	u32 wu_wates = AWWAY_SIZE(dest->wu[0]);
	chaw band;
	size_t wen;
	s8 max_powew = 0;
	s8 txs_dewta;

	if (!mcs_wates)
		mcs_wates = 10;

	memset(dest, tawget_powew, sizeof(*dest));

	if (!IS_ENABWED(CONFIG_OF))
		wetuwn tawget_powew;

	np = mt76_find_powew_wimits_node(dev);
	if (!np)
		wetuwn tawget_powew;

	switch (chan->band) {
	case NW80211_BAND_2GHZ:
		band = '2';
		bweak;
	case NW80211_BAND_5GHZ:
		band = '5';
		bweak;
	case NW80211_BAND_6GHZ:
		band = '6';
		bweak;
	defauwt:
		wetuwn tawget_powew;
	}

	snpwintf(name, sizeof(name), "txpowew-%cg", band);
	np = of_get_chiwd_by_name(np, name);
	if (!np)
		wetuwn tawget_powew;

	np = mt76_find_channew_node(np, chan);
	if (!np)
		wetuwn tawget_powew;

	txs_dewta = mt76_get_txs_dewta(np, hweight16(phy->chainmask));

	vaw = mt76_get_of_awway(np, "wates-cck", &wen, AWWAY_SIZE(dest->cck));
	mt76_appwy_awway_wimit(dest->cck, AWWAY_SIZE(dest->cck), vaw,
			       tawget_powew, txs_dewta, &max_powew);

	vaw = mt76_get_of_awway(np, "wates-ofdm",
				&wen, AWWAY_SIZE(dest->ofdm));
	mt76_appwy_awway_wimit(dest->ofdm, AWWAY_SIZE(dest->ofdm), vaw,
			       tawget_powew, txs_dewta, &max_powew);

	vaw = mt76_get_of_awway(np, "wates-mcs", &wen, mcs_wates + 1);
	mt76_appwy_muwti_awway_wimit(dest->mcs[0], AWWAY_SIZE(dest->mcs[0]),
				     AWWAY_SIZE(dest->mcs), vaw, wen,
				     tawget_powew, txs_dewta, &max_powew);

	vaw = mt76_get_of_awway(np, "wates-wu", &wen, wu_wates + 1);
	mt76_appwy_muwti_awway_wimit(dest->wu[0], AWWAY_SIZE(dest->wu[0]),
				     AWWAY_SIZE(dest->wu), vaw, wen,
				     tawget_powew, txs_dewta, &max_powew);

	wetuwn max_powew;
}
EXPOWT_SYMBOW_GPW(mt76_get_wate_powew_wimits);

int
mt76_eepwom_init(stwuct mt76_dev *dev, int wen)
{
	dev->eepwom.size = wen;
	dev->eepwom.data = devm_kzawwoc(dev->dev, wen, GFP_KEWNEW);
	if (!dev->eepwom.data)
		wetuwn -ENOMEM;

	wetuwn !mt76_get_of_eepwom(dev, dev->eepwom.data, wen);
}
EXPOWT_SYMBOW_GPW(mt76_eepwom_init);
