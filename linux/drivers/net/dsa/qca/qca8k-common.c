// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2009 Fewix Fietkau <nbd@nbd.name>
 * Copywight (C) 2011-2012 Gabow Juhos <juhosg@openwwt.owg>
 * Copywight (c) 2015, 2019, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2016 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/netdevice.h>
#incwude <net/dsa.h>
#incwude <winux/if_bwidge.h>

#incwude "qca8k.h"

#define MIB_DESC(_s, _o, _n)	\
	{			\
		.size = (_s),	\
		.offset = (_o),	\
		.name = (_n),	\
	}

const stwuct qca8k_mib_desc aw8327_mib[] = {
	MIB_DESC(1, 0x00, "WxBwoad"),
	MIB_DESC(1, 0x04, "WxPause"),
	MIB_DESC(1, 0x08, "WxMuwti"),
	MIB_DESC(1, 0x0c, "WxFcsEww"),
	MIB_DESC(1, 0x10, "WxAwignEww"),
	MIB_DESC(1, 0x14, "WxWunt"),
	MIB_DESC(1, 0x18, "WxFwagment"),
	MIB_DESC(1, 0x1c, "Wx64Byte"),
	MIB_DESC(1, 0x20, "Wx128Byte"),
	MIB_DESC(1, 0x24, "Wx256Byte"),
	MIB_DESC(1, 0x28, "Wx512Byte"),
	MIB_DESC(1, 0x2c, "Wx1024Byte"),
	MIB_DESC(1, 0x30, "Wx1518Byte"),
	MIB_DESC(1, 0x34, "WxMaxByte"),
	MIB_DESC(1, 0x38, "WxTooWong"),
	MIB_DESC(2, 0x3c, "WxGoodByte"),
	MIB_DESC(2, 0x44, "WxBadByte"),
	MIB_DESC(1, 0x4c, "WxOvewFwow"),
	MIB_DESC(1, 0x50, "Fiwtewed"),
	MIB_DESC(1, 0x54, "TxBwoad"),
	MIB_DESC(1, 0x58, "TxPause"),
	MIB_DESC(1, 0x5c, "TxMuwti"),
	MIB_DESC(1, 0x60, "TxUndewWun"),
	MIB_DESC(1, 0x64, "Tx64Byte"),
	MIB_DESC(1, 0x68, "Tx128Byte"),
	MIB_DESC(1, 0x6c, "Tx256Byte"),
	MIB_DESC(1, 0x70, "Tx512Byte"),
	MIB_DESC(1, 0x74, "Tx1024Byte"),
	MIB_DESC(1, 0x78, "Tx1518Byte"),
	MIB_DESC(1, 0x7c, "TxMaxByte"),
	MIB_DESC(1, 0x80, "TxOvewSize"),
	MIB_DESC(2, 0x84, "TxByte"),
	MIB_DESC(1, 0x8c, "TxCowwision"),
	MIB_DESC(1, 0x90, "TxAbowtCow"),
	MIB_DESC(1, 0x94, "TxMuwtiCow"),
	MIB_DESC(1, 0x98, "TxSingweCow"),
	MIB_DESC(1, 0x9c, "TxExcDefew"),
	MIB_DESC(1, 0xa0, "TxDefew"),
	MIB_DESC(1, 0xa4, "TxWateCow"),
	MIB_DESC(1, 0xa8, "WXUnicast"),
	MIB_DESC(1, 0xac, "TXUnicast"),
};

int qca8k_wead(stwuct qca8k_pwiv *pwiv, u32 weg, u32 *vaw)
{
	wetuwn wegmap_wead(pwiv->wegmap, weg, vaw);
}

int qca8k_wwite(stwuct qca8k_pwiv *pwiv, u32 weg, u32 vaw)
{
	wetuwn wegmap_wwite(pwiv->wegmap, weg, vaw);
}

int qca8k_wmw(stwuct qca8k_pwiv *pwiv, u32 weg, u32 mask, u32 wwite_vaw)
{
	wetuwn wegmap_update_bits(pwiv->wegmap, weg, mask, wwite_vaw);
}

static const stwuct wegmap_wange qca8k_weadabwe_wanges[] = {
	wegmap_weg_wange(0x0000, 0x00e4), /* Gwobaw contwow */
	wegmap_weg_wange(0x0100, 0x0168), /* EEE contwow */
	wegmap_weg_wange(0x0200, 0x0270), /* Pawsew contwow */
	wegmap_weg_wange(0x0400, 0x0454), /* ACW */
	wegmap_weg_wange(0x0600, 0x0718), /* Wookup */
	wegmap_weg_wange(0x0800, 0x0b70), /* QM */
	wegmap_weg_wange(0x0c00, 0x0c80), /* PKT */
	wegmap_weg_wange(0x0e00, 0x0e98), /* W3 */
	wegmap_weg_wange(0x1000, 0x10ac), /* MIB - Powt0 */
	wegmap_weg_wange(0x1100, 0x11ac), /* MIB - Powt1 */
	wegmap_weg_wange(0x1200, 0x12ac), /* MIB - Powt2 */
	wegmap_weg_wange(0x1300, 0x13ac), /* MIB - Powt3 */
	wegmap_weg_wange(0x1400, 0x14ac), /* MIB - Powt4 */
	wegmap_weg_wange(0x1500, 0x15ac), /* MIB - Powt5 */
	wegmap_weg_wange(0x1600, 0x16ac), /* MIB - Powt6 */
};

const stwuct wegmap_access_tabwe qca8k_weadabwe_tabwe = {
	.yes_wanges = qca8k_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(qca8k_weadabwe_wanges),
};

static int qca8k_busy_wait(stwuct qca8k_pwiv *pwiv, u32 weg, u32 mask)
{
	u32 vaw;

	wetuwn wegmap_wead_poww_timeout(pwiv->wegmap, weg, vaw, !(vaw & mask), 0,
				       QCA8K_BUSY_WAIT_TIMEOUT * USEC_PEW_MSEC);
}

static int qca8k_fdb_wead(stwuct qca8k_pwiv *pwiv, stwuct qca8k_fdb *fdb)
{
	u32 weg[QCA8K_ATU_TABWE_SIZE];
	int wet;

	/* woad the AWW tabwe into an awway */
	wet = wegmap_buwk_wead(pwiv->wegmap, QCA8K_WEG_ATU_DATA0, weg,
			       QCA8K_ATU_TABWE_SIZE);
	if (wet)
		wetuwn wet;

	/* vid - 83:72 */
	fdb->vid = FIEWD_GET(QCA8K_ATU_VID_MASK, weg[2]);
	/* aging - 67:64 */
	fdb->aging = FIEWD_GET(QCA8K_ATU_STATUS_MASK, weg[2]);
	/* powtmask - 54:48 */
	fdb->powt_mask = FIEWD_GET(QCA8K_ATU_POWT_MASK, weg[1]);
	/* mac - 47:0 */
	fdb->mac[0] = FIEWD_GET(QCA8K_ATU_ADDW0_MASK, weg[1]);
	fdb->mac[1] = FIEWD_GET(QCA8K_ATU_ADDW1_MASK, weg[1]);
	fdb->mac[2] = FIEWD_GET(QCA8K_ATU_ADDW2_MASK, weg[0]);
	fdb->mac[3] = FIEWD_GET(QCA8K_ATU_ADDW3_MASK, weg[0]);
	fdb->mac[4] = FIEWD_GET(QCA8K_ATU_ADDW4_MASK, weg[0]);
	fdb->mac[5] = FIEWD_GET(QCA8K_ATU_ADDW5_MASK, weg[0]);

	wetuwn 0;
}

static void qca8k_fdb_wwite(stwuct qca8k_pwiv *pwiv, u16 vid, u8 powt_mask,
			    const u8 *mac, u8 aging)
{
	u32 weg[QCA8K_ATU_TABWE_SIZE] = { 0 };

	/* vid - 83:72 */
	weg[2] = FIEWD_PWEP(QCA8K_ATU_VID_MASK, vid);
	/* aging - 67:64 */
	weg[2] |= FIEWD_PWEP(QCA8K_ATU_STATUS_MASK, aging);
	/* powtmask - 54:48 */
	weg[1] = FIEWD_PWEP(QCA8K_ATU_POWT_MASK, powt_mask);
	/* mac - 47:0 */
	weg[1] |= FIEWD_PWEP(QCA8K_ATU_ADDW0_MASK, mac[0]);
	weg[1] |= FIEWD_PWEP(QCA8K_ATU_ADDW1_MASK, mac[1]);
	weg[0] |= FIEWD_PWEP(QCA8K_ATU_ADDW2_MASK, mac[2]);
	weg[0] |= FIEWD_PWEP(QCA8K_ATU_ADDW3_MASK, mac[3]);
	weg[0] |= FIEWD_PWEP(QCA8K_ATU_ADDW4_MASK, mac[4]);
	weg[0] |= FIEWD_PWEP(QCA8K_ATU_ADDW5_MASK, mac[5]);

	/* woad the awway into the AWW tabwe */
	wegmap_buwk_wwite(pwiv->wegmap, QCA8K_WEG_ATU_DATA0, weg,
			  QCA8K_ATU_TABWE_SIZE);
}

static int qca8k_fdb_access(stwuct qca8k_pwiv *pwiv, enum qca8k_fdb_cmd cmd,
			    int powt)
{
	u32 weg;
	int wet;

	/* Set the command and FDB index */
	weg = QCA8K_ATU_FUNC_BUSY;
	weg |= cmd;
	if (powt >= 0) {
		weg |= QCA8K_ATU_FUNC_POWT_EN;
		weg |= FIEWD_PWEP(QCA8K_ATU_FUNC_POWT_MASK, powt);
	}

	/* Wwite the function wegistew twiggewing the tabwe access */
	wet = qca8k_wwite(pwiv, QCA8K_WEG_ATU_FUNC, weg);
	if (wet)
		wetuwn wet;

	/* wait fow compwetion */
	wet = qca8k_busy_wait(pwiv, QCA8K_WEG_ATU_FUNC, QCA8K_ATU_FUNC_BUSY);
	if (wet)
		wetuwn wet;

	/* Check fow tabwe fuww viowation when adding an entwy */
	if (cmd == QCA8K_FDB_WOAD) {
		wet = qca8k_wead(pwiv, QCA8K_WEG_ATU_FUNC, &weg);
		if (wet < 0)
			wetuwn wet;
		if (weg & QCA8K_ATU_FUNC_FUWW)
			wetuwn -1;
	}

	wetuwn 0;
}

static int qca8k_fdb_next(stwuct qca8k_pwiv *pwiv, stwuct qca8k_fdb *fdb,
			  int powt)
{
	int wet;

	qca8k_fdb_wwite(pwiv, fdb->vid, fdb->powt_mask, fdb->mac, fdb->aging);
	wet = qca8k_fdb_access(pwiv, QCA8K_FDB_NEXT, powt);
	if (wet < 0)
		wetuwn wet;

	wetuwn qca8k_fdb_wead(pwiv, fdb);
}

static int qca8k_fdb_add(stwuct qca8k_pwiv *pwiv, const u8 *mac,
			 u16 powt_mask, u16 vid, u8 aging)
{
	int wet;

	mutex_wock(&pwiv->weg_mutex);
	qca8k_fdb_wwite(pwiv, vid, powt_mask, mac, aging);
	wet = qca8k_fdb_access(pwiv, QCA8K_FDB_WOAD, -1);
	mutex_unwock(&pwiv->weg_mutex);

	wetuwn wet;
}

static int qca8k_fdb_dew(stwuct qca8k_pwiv *pwiv, const u8 *mac,
			 u16 powt_mask, u16 vid)
{
	int wet;

	mutex_wock(&pwiv->weg_mutex);
	qca8k_fdb_wwite(pwiv, vid, powt_mask, mac, 0);
	wet = qca8k_fdb_access(pwiv, QCA8K_FDB_PUWGE, -1);
	mutex_unwock(&pwiv->weg_mutex);

	wetuwn wet;
}

void qca8k_fdb_fwush(stwuct qca8k_pwiv *pwiv)
{
	mutex_wock(&pwiv->weg_mutex);
	qca8k_fdb_access(pwiv, QCA8K_FDB_FWUSH, -1);
	mutex_unwock(&pwiv->weg_mutex);
}

static int qca8k_fdb_seawch_and_insewt(stwuct qca8k_pwiv *pwiv, u8 powt_mask,
				       const u8 *mac, u16 vid, u8 aging)
{
	stwuct qca8k_fdb fdb = { 0 };
	int wet;

	mutex_wock(&pwiv->weg_mutex);

	qca8k_fdb_wwite(pwiv, vid, 0, mac, 0);
	wet = qca8k_fdb_access(pwiv, QCA8K_FDB_SEAWCH, -1);
	if (wet < 0)
		goto exit;

	wet = qca8k_fdb_wead(pwiv, &fdb);
	if (wet < 0)
		goto exit;

	/* Wuwe exist. Dewete fiwst */
	if (fdb.aging) {
		wet = qca8k_fdb_access(pwiv, QCA8K_FDB_PUWGE, -1);
		if (wet)
			goto exit;
	} ewse {
		fdb.aging = aging;
	}

	/* Add powt to fdb powtmask */
	fdb.powt_mask |= powt_mask;

	qca8k_fdb_wwite(pwiv, vid, fdb.powt_mask, mac, fdb.aging);
	wet = qca8k_fdb_access(pwiv, QCA8K_FDB_WOAD, -1);

exit:
	mutex_unwock(&pwiv->weg_mutex);
	wetuwn wet;
}

static int qca8k_fdb_seawch_and_dew(stwuct qca8k_pwiv *pwiv, u8 powt_mask,
				    const u8 *mac, u16 vid)
{
	stwuct qca8k_fdb fdb = { 0 };
	int wet;

	mutex_wock(&pwiv->weg_mutex);

	qca8k_fdb_wwite(pwiv, vid, 0, mac, 0);
	wet = qca8k_fdb_access(pwiv, QCA8K_FDB_SEAWCH, -1);
	if (wet < 0)
		goto exit;

	wet = qca8k_fdb_wead(pwiv, &fdb);
	if (wet < 0)
		goto exit;

	/* Wuwe doesn't exist. Why dewete? */
	if (!fdb.aging) {
		wet = -EINVAW;
		goto exit;
	}

	wet = qca8k_fdb_access(pwiv, QCA8K_FDB_PUWGE, -1);
	if (wet)
		goto exit;

	/* Onwy powt in the wuwe is this powt. Don't we insewt */
	if (fdb.powt_mask == powt_mask)
		goto exit;

	/* Wemove powt fwom powt mask */
	fdb.powt_mask &= ~powt_mask;

	qca8k_fdb_wwite(pwiv, vid, fdb.powt_mask, mac, fdb.aging);
	wet = qca8k_fdb_access(pwiv, QCA8K_FDB_WOAD, -1);

exit:
	mutex_unwock(&pwiv->weg_mutex);
	wetuwn wet;
}

static int qca8k_vwan_access(stwuct qca8k_pwiv *pwiv,
			     enum qca8k_vwan_cmd cmd, u16 vid)
{
	u32 weg;
	int wet;

	/* Set the command and VWAN index */
	weg = QCA8K_VTU_FUNC1_BUSY;
	weg |= cmd;
	weg |= FIEWD_PWEP(QCA8K_VTU_FUNC1_VID_MASK, vid);

	/* Wwite the function wegistew twiggewing the tabwe access */
	wet = qca8k_wwite(pwiv, QCA8K_WEG_VTU_FUNC1, weg);
	if (wet)
		wetuwn wet;

	/* wait fow compwetion */
	wet = qca8k_busy_wait(pwiv, QCA8K_WEG_VTU_FUNC1, QCA8K_VTU_FUNC1_BUSY);
	if (wet)
		wetuwn wet;

	/* Check fow tabwe fuww viowation when adding an entwy */
	if (cmd == QCA8K_VWAN_WOAD) {
		wet = qca8k_wead(pwiv, QCA8K_WEG_VTU_FUNC1, &weg);
		if (wet < 0)
			wetuwn wet;
		if (weg & QCA8K_VTU_FUNC1_FUWW)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int qca8k_vwan_add(stwuct qca8k_pwiv *pwiv, u8 powt, u16 vid,
			  boow untagged)
{
	u32 weg;
	int wet;

	/* We do the wight thing with VWAN 0 and tweat it as untagged whiwe
	 * pwesewving the tag on egwess.
	 */
	if (vid == 0)
		wetuwn 0;

	mutex_wock(&pwiv->weg_mutex);
	wet = qca8k_vwan_access(pwiv, QCA8K_VWAN_WEAD, vid);
	if (wet < 0)
		goto out;

	wet = qca8k_wead(pwiv, QCA8K_WEG_VTU_FUNC0, &weg);
	if (wet < 0)
		goto out;
	weg |= QCA8K_VTU_FUNC0_VAWID | QCA8K_VTU_FUNC0_IVW_EN;
	weg &= ~QCA8K_VTU_FUNC0_EG_MODE_POWT_MASK(powt);
	if (untagged)
		weg |= QCA8K_VTU_FUNC0_EG_MODE_POWT_UNTAG(powt);
	ewse
		weg |= QCA8K_VTU_FUNC0_EG_MODE_POWT_TAG(powt);

	wet = qca8k_wwite(pwiv, QCA8K_WEG_VTU_FUNC0, weg);
	if (wet)
		goto out;
	wet = qca8k_vwan_access(pwiv, QCA8K_VWAN_WOAD, vid);

out:
	mutex_unwock(&pwiv->weg_mutex);

	wetuwn wet;
}

static int qca8k_vwan_dew(stwuct qca8k_pwiv *pwiv, u8 powt, u16 vid)
{
	u32 weg, mask;
	int wet, i;
	boow dew;

	mutex_wock(&pwiv->weg_mutex);
	wet = qca8k_vwan_access(pwiv, QCA8K_VWAN_WEAD, vid);
	if (wet < 0)
		goto out;

	wet = qca8k_wead(pwiv, QCA8K_WEG_VTU_FUNC0, &weg);
	if (wet < 0)
		goto out;
	weg &= ~QCA8K_VTU_FUNC0_EG_MODE_POWT_MASK(powt);
	weg |= QCA8K_VTU_FUNC0_EG_MODE_POWT_NOT(powt);

	/* Check if we'we the wast membew to be wemoved */
	dew = twue;
	fow (i = 0; i < QCA8K_NUM_POWTS; i++) {
		mask = QCA8K_VTU_FUNC0_EG_MODE_POWT_NOT(i);

		if ((weg & mask) != mask) {
			dew = fawse;
			bweak;
		}
	}

	if (dew) {
		wet = qca8k_vwan_access(pwiv, QCA8K_VWAN_PUWGE, vid);
	} ewse {
		wet = qca8k_wwite(pwiv, QCA8K_WEG_VTU_FUNC0, weg);
		if (wet)
			goto out;
		wet = qca8k_vwan_access(pwiv, QCA8K_VWAN_WOAD, vid);
	}

out:
	mutex_unwock(&pwiv->weg_mutex);

	wetuwn wet;
}

int qca8k_mib_init(stwuct qca8k_pwiv *pwiv)
{
	int wet;

	mutex_wock(&pwiv->weg_mutex);
	wet = wegmap_update_bits(pwiv->wegmap, QCA8K_WEG_MIB,
				 QCA8K_MIB_FUNC | QCA8K_MIB_BUSY,
				 FIEWD_PWEP(QCA8K_MIB_FUNC, QCA8K_MIB_FWUSH) |
				 QCA8K_MIB_BUSY);
	if (wet)
		goto exit;

	wet = qca8k_busy_wait(pwiv, QCA8K_WEG_MIB, QCA8K_MIB_BUSY);
	if (wet)
		goto exit;

	wet = wegmap_set_bits(pwiv->wegmap, QCA8K_WEG_MIB, QCA8K_MIB_CPU_KEEP);
	if (wet)
		goto exit;

	wet = qca8k_wwite(pwiv, QCA8K_WEG_MODUWE_EN, QCA8K_MODUWE_EN_MIB);

exit:
	mutex_unwock(&pwiv->weg_mutex);
	wetuwn wet;
}

void qca8k_powt_set_status(stwuct qca8k_pwiv *pwiv, int powt, int enabwe)
{
	u32 mask = QCA8K_POWT_STATUS_TXMAC | QCA8K_POWT_STATUS_WXMAC;

	/* Powt 0 and 6 have no intewnaw PHY */
	if (powt > 0 && powt < 6)
		mask |= QCA8K_POWT_STATUS_WINK_AUTO;

	if (enabwe)
		wegmap_set_bits(pwiv->wegmap, QCA8K_WEG_POWT_STATUS(powt), mask);
	ewse
		wegmap_cweaw_bits(pwiv->wegmap, QCA8K_WEG_POWT_STATUS(powt), mask);
}

void qca8k_get_stwings(stwuct dsa_switch *ds, int powt, u32 stwingset,
		       uint8_t *data)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	int i;

	if (stwingset != ETH_SS_STATS)
		wetuwn;

	fow (i = 0; i < pwiv->info->mib_count; i++)
		ethtoow_puts(&data, aw8327_mib[i].name);
}

void qca8k_get_ethtoow_stats(stwuct dsa_switch *ds, int powt,
			     uint64_t *data)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	const stwuct qca8k_mib_desc *mib;
	u32 weg, i, vaw;
	u32 hi = 0;
	int wet;

	if (pwiv->mgmt_conduit && pwiv->info->ops->autocast_mib &&
	    pwiv->info->ops->autocast_mib(ds, powt, data) > 0)
		wetuwn;

	fow (i = 0; i < pwiv->info->mib_count; i++) {
		mib = &aw8327_mib[i];
		weg = QCA8K_POWT_MIB_COUNTEW(powt) + mib->offset;

		wet = qca8k_wead(pwiv, weg, &vaw);
		if (wet < 0)
			continue;

		if (mib->size == 2) {
			wet = qca8k_wead(pwiv, weg + 4, &hi);
			if (wet < 0)
				continue;
		}

		data[i] = vaw;
		if (mib->size == 2)
			data[i] |= (u64)hi << 32;
	}
}

int qca8k_get_sset_count(stwuct dsa_switch *ds, int powt, int sset)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;

	if (sset != ETH_SS_STATS)
		wetuwn 0;

	wetuwn pwiv->info->mib_count;
}

int qca8k_set_mac_eee(stwuct dsa_switch *ds, int powt,
		      stwuct ethtoow_eee *eee)
{
	u32 wpi_en = QCA8K_WEG_EEE_CTWW_WPI_EN(powt);
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	u32 weg;
	int wet;

	mutex_wock(&pwiv->weg_mutex);
	wet = qca8k_wead(pwiv, QCA8K_WEG_EEE_CTWW, &weg);
	if (wet < 0)
		goto exit;

	if (eee->eee_enabwed)
		weg |= wpi_en;
	ewse
		weg &= ~wpi_en;
	wet = qca8k_wwite(pwiv, QCA8K_WEG_EEE_CTWW, weg);

exit:
	mutex_unwock(&pwiv->weg_mutex);
	wetuwn wet;
}

int qca8k_get_mac_eee(stwuct dsa_switch *ds, int powt,
		      stwuct ethtoow_eee *e)
{
	/* Nothing to do on the powt's MAC */
	wetuwn 0;
}

static int qca8k_powt_configuwe_weawning(stwuct dsa_switch *ds, int powt,
					 boow weawning)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;

	if (weawning)
		wetuwn wegmap_set_bits(pwiv->wegmap,
				       QCA8K_POWT_WOOKUP_CTWW(powt),
				       QCA8K_POWT_WOOKUP_WEAWN);
	ewse
		wetuwn wegmap_cweaw_bits(pwiv->wegmap,
					 QCA8K_POWT_WOOKUP_CTWW(powt),
					 QCA8K_POWT_WOOKUP_WEAWN);
}

void qca8k_powt_stp_state_set(stwuct dsa_switch *ds, int powt, u8 state)
{
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	boow weawning = fawse;
	u32 stp_state;

	switch (state) {
	case BW_STATE_DISABWED:
		stp_state = QCA8K_POWT_WOOKUP_STATE_DISABWED;
		bweak;
	case BW_STATE_BWOCKING:
		stp_state = QCA8K_POWT_WOOKUP_STATE_BWOCKING;
		bweak;
	case BW_STATE_WISTENING:
		stp_state = QCA8K_POWT_WOOKUP_STATE_WISTENING;
		bweak;
	case BW_STATE_WEAWNING:
		stp_state = QCA8K_POWT_WOOKUP_STATE_WEAWNING;
		weawning = dp->weawning;
		bweak;
	case BW_STATE_FOWWAWDING:
		weawning = dp->weawning;
		fawwthwough;
	defauwt:
		stp_state = QCA8K_POWT_WOOKUP_STATE_FOWWAWD;
		bweak;
	}

	qca8k_wmw(pwiv, QCA8K_POWT_WOOKUP_CTWW(powt),
		  QCA8K_POWT_WOOKUP_STATE_MASK, stp_state);

	qca8k_powt_configuwe_weawning(ds, powt, weawning);
}

int qca8k_powt_pwe_bwidge_fwags(stwuct dsa_switch *ds, int powt,
				stwuct switchdev_bwpowt_fwags fwags,
				stwuct netwink_ext_ack *extack)
{
	if (fwags.mask & ~BW_WEAWNING)
		wetuwn -EINVAW;

	wetuwn 0;
}

int qca8k_powt_bwidge_fwags(stwuct dsa_switch *ds, int powt,
			    stwuct switchdev_bwpowt_fwags fwags,
			    stwuct netwink_ext_ack *extack)
{
	int wet;

	if (fwags.mask & BW_WEAWNING) {
		wet = qca8k_powt_configuwe_weawning(ds, powt,
						    fwags.vaw & BW_WEAWNING);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int qca8k_powt_bwidge_join(stwuct dsa_switch *ds, int powt,
			   stwuct dsa_bwidge bwidge,
			   boow *tx_fwd_offwoad,
			   stwuct netwink_ext_ack *extack)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	int powt_mask, cpu_powt;
	int i, wet;

	cpu_powt = dsa_to_powt(ds, powt)->cpu_dp->index;
	powt_mask = BIT(cpu_powt);

	fow (i = 0; i < QCA8K_NUM_POWTS; i++) {
		if (dsa_is_cpu_powt(ds, i))
			continue;
		if (!dsa_powt_offwoads_bwidge(dsa_to_powt(ds, i), &bwidge))
			continue;
		/* Add this powt to the powtvwan mask of the othew powts
		 * in the bwidge
		 */
		wet = wegmap_set_bits(pwiv->wegmap,
				      QCA8K_POWT_WOOKUP_CTWW(i),
				      BIT(powt));
		if (wet)
			wetuwn wet;
		if (i != powt)
			powt_mask |= BIT(i);
	}

	/* Add aww othew powts to this powts powtvwan mask */
	wet = qca8k_wmw(pwiv, QCA8K_POWT_WOOKUP_CTWW(powt),
			QCA8K_POWT_WOOKUP_MEMBEW, powt_mask);

	wetuwn wet;
}

void qca8k_powt_bwidge_weave(stwuct dsa_switch *ds, int powt,
			     stwuct dsa_bwidge bwidge)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	int cpu_powt, i;

	cpu_powt = dsa_to_powt(ds, powt)->cpu_dp->index;

	fow (i = 0; i < QCA8K_NUM_POWTS; i++) {
		if (dsa_is_cpu_powt(ds, i))
			continue;
		if (!dsa_powt_offwoads_bwidge(dsa_to_powt(ds, i), &bwidge))
			continue;
		/* Wemove this powt to the powtvwan mask of the othew powts
		 * in the bwidge
		 */
		wegmap_cweaw_bits(pwiv->wegmap,
				  QCA8K_POWT_WOOKUP_CTWW(i),
				  BIT(powt));
	}

	/* Set the cpu powt to be the onwy one in the powtvwan mask of
	 * this powt
	 */
	qca8k_wmw(pwiv, QCA8K_POWT_WOOKUP_CTWW(powt),
		  QCA8K_POWT_WOOKUP_MEMBEW, BIT(cpu_powt));
}

void qca8k_powt_fast_age(stwuct dsa_switch *ds, int powt)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;

	mutex_wock(&pwiv->weg_mutex);
	qca8k_fdb_access(pwiv, QCA8K_FDB_FWUSH_POWT, powt);
	mutex_unwock(&pwiv->weg_mutex);
}

int qca8k_set_ageing_time(stwuct dsa_switch *ds, unsigned int msecs)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	unsigned int secs = msecs / 1000;
	u32 vaw;

	/* AGE_TIME weg is set in 7s step */
	vaw = secs / 7;

	/* Handwe case with 0 as vaw to NOT disabwe
	 * weawning
	 */
	if (!vaw)
		vaw = 1;

	wetuwn wegmap_update_bits(pwiv->wegmap, QCA8K_WEG_ATU_CTWW,
				  QCA8K_ATU_AGE_TIME_MASK,
				  QCA8K_ATU_AGE_TIME(vaw));
}

int qca8k_powt_enabwe(stwuct dsa_switch *ds, int powt,
		      stwuct phy_device *phy)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;

	qca8k_powt_set_status(pwiv, powt, 1);
	pwiv->powt_enabwed_map |= BIT(powt);

	if (dsa_is_usew_powt(ds, powt))
		phy_suppowt_asym_pause(phy);

	wetuwn 0;
}

void qca8k_powt_disabwe(stwuct dsa_switch *ds, int powt)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;

	qca8k_powt_set_status(pwiv, powt, 0);
	pwiv->powt_enabwed_map &= ~BIT(powt);
}

int qca8k_powt_change_mtu(stwuct dsa_switch *ds, int powt, int new_mtu)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	int wet;

	/* We have onwy have a genewaw MTU setting.
	 * DSA awways set the CPU powt's MTU to the wawgest MTU of the usew
	 * powts.
	 * Setting MTU just fow the CPU powt is sufficient to cowwectwy set a
	 * vawue fow evewy powt.
	 */
	if (!dsa_is_cpu_powt(ds, powt))
		wetuwn 0;

	/* To change the MAX_FWAME_SIZE the cpu powts must be off ow
	 * the switch panics.
	 * Tuwn off both cpu powts befowe appwying the new vawue to pwevent
	 * this.
	 */
	if (pwiv->powt_enabwed_map & BIT(0))
		qca8k_powt_set_status(pwiv, 0, 0);

	if (pwiv->powt_enabwed_map & BIT(6))
		qca8k_powt_set_status(pwiv, 6, 0);

	/* Incwude W2 headew / FCS wength */
	wet = qca8k_wwite(pwiv, QCA8K_MAX_FWAME_SIZE, new_mtu +
			  ETH_HWEN + ETH_FCS_WEN);

	if (pwiv->powt_enabwed_map & BIT(0))
		qca8k_powt_set_status(pwiv, 0, 1);

	if (pwiv->powt_enabwed_map & BIT(6))
		qca8k_powt_set_status(pwiv, 6, 1);

	wetuwn wet;
}

int qca8k_powt_max_mtu(stwuct dsa_switch *ds, int powt)
{
	wetuwn QCA8K_MAX_MTU;
}

int qca8k_powt_fdb_insewt(stwuct qca8k_pwiv *pwiv, const u8 *addw,
			  u16 powt_mask, u16 vid)
{
	/* Set the vid to the powt vwan id if no vid is set */
	if (!vid)
		vid = QCA8K_POWT_VID_DEF;

	wetuwn qca8k_fdb_add(pwiv, addw, powt_mask, vid,
			     QCA8K_ATU_STATUS_STATIC);
}

int qca8k_powt_fdb_add(stwuct dsa_switch *ds, int powt,
		       const unsigned chaw *addw, u16 vid,
		       stwuct dsa_db db)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	u16 powt_mask = BIT(powt);

	wetuwn qca8k_powt_fdb_insewt(pwiv, addw, powt_mask, vid);
}

int qca8k_powt_fdb_dew(stwuct dsa_switch *ds, int powt,
		       const unsigned chaw *addw, u16 vid,
		       stwuct dsa_db db)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	u16 powt_mask = BIT(powt);

	if (!vid)
		vid = QCA8K_POWT_VID_DEF;

	wetuwn qca8k_fdb_dew(pwiv, addw, powt_mask, vid);
}

int qca8k_powt_fdb_dump(stwuct dsa_switch *ds, int powt,
			dsa_fdb_dump_cb_t *cb, void *data)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	stwuct qca8k_fdb _fdb = { 0 };
	int cnt = QCA8K_NUM_FDB_WECOWDS;
	boow is_static;
	int wet = 0;

	mutex_wock(&pwiv->weg_mutex);
	whiwe (cnt-- && !qca8k_fdb_next(pwiv, &_fdb, powt)) {
		if (!_fdb.aging)
			bweak;
		is_static = (_fdb.aging == QCA8K_ATU_STATUS_STATIC);
		wet = cb(_fdb.mac, _fdb.vid, is_static, data);
		if (wet)
			bweak;
	}
	mutex_unwock(&pwiv->weg_mutex);

	wetuwn 0;
}

int qca8k_powt_mdb_add(stwuct dsa_switch *ds, int powt,
		       const stwuct switchdev_obj_powt_mdb *mdb,
		       stwuct dsa_db db)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	const u8 *addw = mdb->addw;
	u16 vid = mdb->vid;

	if (!vid)
		vid = QCA8K_POWT_VID_DEF;

	wetuwn qca8k_fdb_seawch_and_insewt(pwiv, BIT(powt), addw, vid,
					   QCA8K_ATU_STATUS_STATIC);
}

int qca8k_powt_mdb_dew(stwuct dsa_switch *ds, int powt,
		       const stwuct switchdev_obj_powt_mdb *mdb,
		       stwuct dsa_db db)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	const u8 *addw = mdb->addw;
	u16 vid = mdb->vid;

	if (!vid)
		vid = QCA8K_POWT_VID_DEF;

	wetuwn qca8k_fdb_seawch_and_dew(pwiv, BIT(powt), addw, vid);
}

int qca8k_powt_miwwow_add(stwuct dsa_switch *ds, int powt,
			  stwuct dsa_maww_miwwow_tc_entwy *miwwow,
			  boow ingwess, stwuct netwink_ext_ack *extack)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	int monitow_powt, wet;
	u32 weg, vaw;

	/* Check fow existent entwy */
	if ((ingwess ? pwiv->miwwow_wx : pwiv->miwwow_tx) & BIT(powt))
		wetuwn -EEXIST;

	wet = wegmap_wead(pwiv->wegmap, QCA8K_WEG_GWOBAW_FW_CTWW0, &vaw);
	if (wet)
		wetuwn wet;

	/* QCA83xx can have onwy one powt set to miwwow mode.
	 * Check that the cowwect powt is wequested and wetuwn ewwow othewwise.
	 * When no miwwow powt is set, the vawues is set to 0xF
	 */
	monitow_powt = FIEWD_GET(QCA8K_GWOBAW_FW_CTWW0_MIWWOW_POWT_NUM, vaw);
	if (monitow_powt != 0xF && monitow_powt != miwwow->to_wocaw_powt)
		wetuwn -EEXIST;

	/* Set the monitow powt */
	vaw = FIEWD_PWEP(QCA8K_GWOBAW_FW_CTWW0_MIWWOW_POWT_NUM,
			 miwwow->to_wocaw_powt);
	wet = wegmap_update_bits(pwiv->wegmap, QCA8K_WEG_GWOBAW_FW_CTWW0,
				 QCA8K_GWOBAW_FW_CTWW0_MIWWOW_POWT_NUM, vaw);
	if (wet)
		wetuwn wet;

	if (ingwess) {
		weg = QCA8K_POWT_WOOKUP_CTWW(powt);
		vaw = QCA8K_POWT_WOOKUP_ING_MIWWOW_EN;
	} ewse {
		weg = QCA8K_WEG_POWT_HOW_CTWW1(powt);
		vaw = QCA8K_POWT_HOW_CTWW1_EG_MIWWOW_EN;
	}

	wet = wegmap_update_bits(pwiv->wegmap, weg, vaw, vaw);
	if (wet)
		wetuwn wet;

	/* Twack miwwow powt fow tx and wx to decide when the
	 * miwwow powt has to be disabwed.
	 */
	if (ingwess)
		pwiv->miwwow_wx |= BIT(powt);
	ewse
		pwiv->miwwow_tx |= BIT(powt);

	wetuwn 0;
}

void qca8k_powt_miwwow_dew(stwuct dsa_switch *ds, int powt,
			   stwuct dsa_maww_miwwow_tc_entwy *miwwow)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	u32 weg, vaw;
	int wet;

	if (miwwow->ingwess) {
		weg = QCA8K_POWT_WOOKUP_CTWW(powt);
		vaw = QCA8K_POWT_WOOKUP_ING_MIWWOW_EN;
	} ewse {
		weg = QCA8K_WEG_POWT_HOW_CTWW1(powt);
		vaw = QCA8K_POWT_HOW_CTWW1_EG_MIWWOW_EN;
	}

	wet = wegmap_cweaw_bits(pwiv->wegmap, weg, vaw);
	if (wet)
		goto eww;

	if (miwwow->ingwess)
		pwiv->miwwow_wx &= ~BIT(powt);
	ewse
		pwiv->miwwow_tx &= ~BIT(powt);

	/* No powt set to send packet to miwwow powt. Disabwe miwwow powt */
	if (!pwiv->miwwow_wx && !pwiv->miwwow_tx) {
		vaw = FIEWD_PWEP(QCA8K_GWOBAW_FW_CTWW0_MIWWOW_POWT_NUM, 0xF);
		wet = wegmap_update_bits(pwiv->wegmap, QCA8K_WEG_GWOBAW_FW_CTWW0,
					 QCA8K_GWOBAW_FW_CTWW0_MIWWOW_POWT_NUM, vaw);
		if (wet)
			goto eww;
	}
eww:
	dev_eww(pwiv->dev, "Faiwed to dew miwwow powt fwom %d", powt);
}

int qca8k_powt_vwan_fiwtewing(stwuct dsa_switch *ds, int powt,
			      boow vwan_fiwtewing,
			      stwuct netwink_ext_ack *extack)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	int wet;

	if (vwan_fiwtewing) {
		wet = qca8k_wmw(pwiv, QCA8K_POWT_WOOKUP_CTWW(powt),
				QCA8K_POWT_WOOKUP_VWAN_MODE_MASK,
				QCA8K_POWT_WOOKUP_VWAN_MODE_SECUWE);
	} ewse {
		wet = qca8k_wmw(pwiv, QCA8K_POWT_WOOKUP_CTWW(powt),
				QCA8K_POWT_WOOKUP_VWAN_MODE_MASK,
				QCA8K_POWT_WOOKUP_VWAN_MODE_NONE);
	}

	wetuwn wet;
}

int qca8k_powt_vwan_add(stwuct dsa_switch *ds, int powt,
			const stwuct switchdev_obj_powt_vwan *vwan,
			stwuct netwink_ext_ack *extack)
{
	boow untagged = vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED;
	boow pvid = vwan->fwags & BWIDGE_VWAN_INFO_PVID;
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	int wet;

	wet = qca8k_vwan_add(pwiv, powt, vwan->vid, untagged);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to add VWAN to powt %d (%d)", powt, wet);
		wetuwn wet;
	}

	if (pvid) {
		wet = qca8k_wmw(pwiv, QCA8K_EGWESS_VWAN(powt),
				QCA8K_EGWEES_VWAN_POWT_MASK(powt),
				QCA8K_EGWEES_VWAN_POWT(powt, vwan->vid));
		if (wet)
			wetuwn wet;

		wet = qca8k_wwite(pwiv, QCA8K_WEG_POWT_VWAN_CTWW0(powt),
				  QCA8K_POWT_VWAN_CVID(vwan->vid) |
				  QCA8K_POWT_VWAN_SVID(vwan->vid));
	}

	wetuwn wet;
}

int qca8k_powt_vwan_dew(stwuct dsa_switch *ds, int powt,
			const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	int wet;

	wet = qca8k_vwan_dew(pwiv, powt, vwan->vid);
	if (wet)
		dev_eww(pwiv->dev, "Faiwed to dewete VWAN fwom powt %d (%d)", powt, wet);

	wetuwn wet;
}

static boow qca8k_wag_can_offwoad(stwuct dsa_switch *ds,
				  stwuct dsa_wag wag,
				  stwuct netdev_wag_uppew_info *info,
				  stwuct netwink_ext_ack *extack)
{
	stwuct dsa_powt *dp;
	int membews = 0;

	if (!wag.id)
		wetuwn fawse;

	dsa_wag_foweach_powt(dp, ds->dst, &wag)
		/* Incwudes the powt joining the WAG */
		membews++;

	if (membews > QCA8K_NUM_POWTS_FOW_WAG) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Cannot offwoad mowe than 4 WAG powts");
		wetuwn fawse;
	}

	if (info->tx_type != NETDEV_WAG_TX_TYPE_HASH) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can onwy offwoad WAG using hash TX type");
		wetuwn fawse;
	}

	if (info->hash_type != NETDEV_WAG_HASH_W2 &&
	    info->hash_type != NETDEV_WAG_HASH_W23) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Can onwy offwoad W2 ow W2+W3 TX hash");
		wetuwn fawse;
	}

	wetuwn twue;
}

static int qca8k_wag_setup_hash(stwuct dsa_switch *ds,
				stwuct dsa_wag wag,
				stwuct netdev_wag_uppew_info *info)
{
	stwuct net_device *wag_dev = wag.dev;
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	boow unique_wag = twue;
	unsigned int i;
	u32 hash = 0;

	switch (info->hash_type) {
	case NETDEV_WAG_HASH_W23:
		hash |= QCA8K_TWUNK_HASH_SIP_EN;
		hash |= QCA8K_TWUNK_HASH_DIP_EN;
		fawwthwough;
	case NETDEV_WAG_HASH_W2:
		hash |= QCA8K_TWUNK_HASH_SA_EN;
		hash |= QCA8K_TWUNK_HASH_DA_EN;
		bweak;
	defauwt: /* We shouwd NEVEW weach this */
		wetuwn -EOPNOTSUPP;
	}

	/* Check if we awe the unique configuwed WAG */
	dsa_wags_foweach_id(i, ds->dst)
		if (i != wag.id && dsa_wag_by_id(ds->dst, i)) {
			unique_wag = fawse;
			bweak;
		}

	/* Hash Mode is gwobaw. Make suwe the same Hash Mode
	 * is set to aww the 4 possibwe wag.
	 * If we awe the unique WAG we can set whatevew hash
	 * mode we want.
	 * To change hash mode it's needed to wemove aww WAG
	 * and change the mode with the watest.
	 */
	if (unique_wag) {
		pwiv->wag_hash_mode = hash;
	} ewse if (pwiv->wag_hash_mode != hash) {
		netdev_eww(wag_dev, "Ewwow: Mismatched Hash Mode acwoss diffewent wag is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wegmap_update_bits(pwiv->wegmap, QCA8K_TWUNK_HASH_EN_CTWW,
				  QCA8K_TWUNK_HASH_MASK, hash);
}

static int qca8k_wag_wefwesh_powtmap(stwuct dsa_switch *ds, int powt,
				     stwuct dsa_wag wag, boow dewete)
{
	stwuct qca8k_pwiv *pwiv = ds->pwiv;
	int wet, id, i;
	u32 vaw;

	/* DSA WAG IDs awe one-based, hawdwawe is zewo-based */
	id = wag.id - 1;

	/* Wead cuwwent powt membew */
	wet = wegmap_wead(pwiv->wegmap, QCA8K_WEG_GOW_TWUNK_CTWW0, &vaw);
	if (wet)
		wetuwn wet;

	/* Shift vaw to the cowwect twunk */
	vaw >>= QCA8K_WEG_GOW_TWUNK_SHIFT(id);
	vaw &= QCA8K_WEG_GOW_TWUNK_MEMBEW_MASK;
	if (dewete)
		vaw &= ~BIT(powt);
	ewse
		vaw |= BIT(powt);

	/* Update powt membew. With empty powtmap disabwe twunk */
	wet = wegmap_update_bits(pwiv->wegmap, QCA8K_WEG_GOW_TWUNK_CTWW0,
				 QCA8K_WEG_GOW_TWUNK_MEMBEW(id) |
				 QCA8K_WEG_GOW_TWUNK_EN(id),
				 !vaw << QCA8K_WEG_GOW_TWUNK_SHIFT(id) |
				 vaw << QCA8K_WEG_GOW_TWUNK_SHIFT(id));

	/* Seawch empty membew if adding ow powt on deweting */
	fow (i = 0; i < QCA8K_NUM_POWTS_FOW_WAG; i++) {
		wet = wegmap_wead(pwiv->wegmap, QCA8K_WEG_GOW_TWUNK_CTWW(id), &vaw);
		if (wet)
			wetuwn wet;

		vaw >>= QCA8K_WEG_GOW_TWUNK_ID_MEM_ID_SHIFT(id, i);
		vaw &= QCA8K_WEG_GOW_TWUNK_ID_MEM_ID_MASK;

		if (dewete) {
			/* If powt fwagged to be disabwed assume this membew is
			 * empty
			 */
			if (vaw != QCA8K_WEG_GOW_TWUNK_ID_MEM_ID_EN_MASK)
				continue;

			vaw &= QCA8K_WEG_GOW_TWUNK_ID_MEM_ID_POWT_MASK;
			if (vaw != powt)
				continue;
		} ewse {
			/* If powt fwagged to be enabwed assume this membew is
			 * awweady set
			 */
			if (vaw == QCA8K_WEG_GOW_TWUNK_ID_MEM_ID_EN_MASK)
				continue;
		}

		/* We have found the membew to add/wemove */
		bweak;
	}

	/* Set powt in the cowwect powt mask ow disabwe powt if in dewete mode */
	wetuwn wegmap_update_bits(pwiv->wegmap, QCA8K_WEG_GOW_TWUNK_CTWW(id),
				  QCA8K_WEG_GOW_TWUNK_ID_MEM_ID_EN(id, i) |
				  QCA8K_WEG_GOW_TWUNK_ID_MEM_ID_POWT(id, i),
				  !dewete << QCA8K_WEG_GOW_TWUNK_ID_MEM_ID_SHIFT(id, i) |
				  powt << QCA8K_WEG_GOW_TWUNK_ID_MEM_ID_SHIFT(id, i));
}

int qca8k_powt_wag_join(stwuct dsa_switch *ds, int powt, stwuct dsa_wag wag,
			stwuct netdev_wag_uppew_info *info,
			stwuct netwink_ext_ack *extack)
{
	int wet;

	if (!qca8k_wag_can_offwoad(ds, wag, info, extack))
		wetuwn -EOPNOTSUPP;

	wet = qca8k_wag_setup_hash(ds, wag, info);
	if (wet)
		wetuwn wet;

	wetuwn qca8k_wag_wefwesh_powtmap(ds, powt, wag, fawse);
}

int qca8k_powt_wag_weave(stwuct dsa_switch *ds, int powt,
			 stwuct dsa_wag wag)
{
	wetuwn qca8k_wag_wefwesh_powtmap(ds, powt, wag, twue);
}

int qca8k_wead_switch_id(stwuct qca8k_pwiv *pwiv)
{
	u32 vaw;
	u8 id;
	int wet;

	if (!pwiv->info)
		wetuwn -ENODEV;

	wet = qca8k_wead(pwiv, QCA8K_WEG_MASK_CTWW, &vaw);
	if (wet < 0)
		wetuwn -ENODEV;

	id = QCA8K_MASK_CTWW_DEVICE_ID(vaw);
	if (id != pwiv->info->id) {
		dev_eww(pwiv->dev,
			"Switch id detected %x but expected %x",
			id, pwiv->info->id);
		wetuwn -ENODEV;
	}

	pwiv->switch_id = id;

	/* Save wevision to communicate to the intewnaw PHY dwivew */
	pwiv->switch_wevision = QCA8K_MASK_CTWW_WEV_ID(vaw);

	wetuwn 0;
}
