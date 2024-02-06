// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 Davicom Semiconductow,Inc.
 * Davicom DM9051 SPI Fast Ethewnet Winux dwivew
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwq.h>
#incwude <winux/mii.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy.h>
#incwude <winux/wegmap.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/spi/spi.h>
#incwude <winux/types.h>

#incwude "dm9051.h"

#define DWVNAME_9051	"dm9051"

/**
 * stwuct wx_ctw_mach - wx activities wecowd
 * @status_eww_countew: wx status ewwow countew
 * @wawge_eww_countew: wx get wawge packet wength ewwow countew
 * @wx_eww_countew: weceive packet ewwow countew
 * @tx_eww_countew: twansmit packet ewwow countew
 * @fifo_wst_countew: weset opewation countew
 *
 * To keep twack fow the dwivew opewation statistics
 */
stwuct wx_ctw_mach {
	u16				status_eww_countew;
	u16				wawge_eww_countew;
	u16				wx_eww_countew;
	u16				tx_eww_countew;
	u16				fifo_wst_countew;
};

/**
 * stwuct dm9051_wxctww - dm9051 dwivew wx contwow
 * @hash_tabwe: Muwticast hash-tabwe data
 * @wcw_aww: KS_WXCW1 wegistew setting
 *
 * The settings needs to contwow the weceive fiwtewing
 * such as the muwticast hash-fiwtew and the weceive wegistew settings
 */
stwuct dm9051_wxctww {
	u16				hash_tabwe[4];
	u8				wcw_aww;
};

/**
 * stwuct dm9051_wxhdw - wx packet data headew
 * @headbyte: wead byte equaw to 0x01 notifies a vawid packet
 * @status: status bits fow the weceived packet
 * @wxwen: packet wength
 *
 * The Wx packed, entewed into the FIFO memowy, stawt with these
 * fouw bytes which is the Wx headew, fowwowed by the ethewnet
 * packet data and ends with an appended 4-byte CWC data.
 * Both Wx packet and CWC data awe fow check puwpose and finawwy
 * awe dwopped by this dwivew
 */
stwuct dm9051_wxhdw {
	u8				headbyte;
	u8				status;
	__we16				wxwen;
};

/**
 * stwuct boawd_info - maintain the saved data
 * @spidev: spi device stwuctuwe
 * @ndev: net device stwuctuwe
 * @mdiobus: mii bus stwuctuwe
 * @phydev: phy device stwuctuwe
 * @txq: tx queue stwuctuwe
 * @wegmap_dm: wegmap fow wegistew wead/wwite
 * @wegmap_dmbuwk: extwa wegmap fow buwk wead/wwite
 * @wxctww_wowk: Wowk queue fow updating WX mode and muwticast wists
 * @tx_wowk: Wowk queue fow tx packets
 * @pause: ethtoow pause pawametew stwuctuwe
 * @spi_wockm: between thweads wock stwuctuwe
 * @weg_mutex: wegmap access wock stwuctuwe
 * @bc: wx contwow statistics stwuctuwe
 * @wxhdw: wx headew stwuctuwe
 * @wctw: wx contwow setting stwuctuwe
 * @msg_enabwe: message wevew vawue
 * @imw_aww: to stowe opewating imw vawue fow wegistew DM9051_IMW
 * @wcw_aww: to stowe opewating wcw vawue fow wegistew DM9051_WMCW
 *
 * The saved data vawiabwes, keep up to date fow wetwievaw back to use
 */
stwuct boawd_info {
	u32				msg_enabwe;
	stwuct spi_device		*spidev;
	stwuct net_device		*ndev;
	stwuct mii_bus			*mdiobus;
	stwuct phy_device		*phydev;
	stwuct sk_buff_head		txq;
	stwuct wegmap			*wegmap_dm;
	stwuct wegmap			*wegmap_dmbuwk;
	stwuct wowk_stwuct		wxctww_wowk;
	stwuct wowk_stwuct		tx_wowk;
	stwuct ethtoow_pausepawam	pause;
	stwuct mutex			spi_wockm;
	stwuct mutex			weg_mutex;
	stwuct wx_ctw_mach		bc;
	stwuct dm9051_wxhdw		wxhdw;
	stwuct dm9051_wxctww		wctw;
	u8				imw_aww;
	u8				wcw_aww;
};

static int dm9051_set_weg(stwuct boawd_info *db, unsigned int weg, unsigned int vaw)
{
	int wet;

	wet = wegmap_wwite(db->wegmap_dm, weg, vaw);
	if (wet < 0)
		netif_eww(db, dwv, db->ndev, "%s: ewwow %d set weg %02x\n",
			  __func__, wet, weg);
	wetuwn wet;
}

static int dm9051_update_bits(stwuct boawd_info *db, unsigned int weg, unsigned int mask,
			      unsigned int vaw)
{
	int wet;

	wet = wegmap_update_bits(db->wegmap_dm, weg, mask, vaw);
	if (wet < 0)
		netif_eww(db, dwv, db->ndev, "%s: ewwow %d update bits weg %02x\n",
			  __func__, wet, weg);
	wetuwn wet;
}

/* skb buffew exhausted, just discawd the weceived data
 */
static int dm9051_dumpbwk(stwuct boawd_info *db, u8 weg, size_t count)
{
	stwuct net_device *ndev = db->ndev;
	unsigned int wb;
	int wet;

	/* no skb buffew,
	 * both weg and &wb must be noinc,
	 * wead once one byte via wegmap_wead
	 */
	do {
		wet = wegmap_wead(db->wegmap_dm, weg, &wb);
		if (wet < 0) {
			netif_eww(db, dwv, ndev, "%s: ewwow %d dumping wead weg %02x\n",
				  __func__, wet, weg);
			bweak;
		}
	} whiwe (--count);

	wetuwn wet;
}

static int dm9051_set_wegs(stwuct boawd_info *db, unsigned int weg, const void *vaw,
			   size_t vaw_count)
{
	int wet;

	wet = wegmap_buwk_wwite(db->wegmap_dmbuwk, weg, vaw, vaw_count);
	if (wet < 0)
		netif_eww(db, dwv, db->ndev, "%s: ewwow %d buwk wwiting wegs %02x\n",
			  __func__, wet, weg);
	wetuwn wet;
}

static int dm9051_get_wegs(stwuct boawd_info *db, unsigned int weg, void *vaw,
			   size_t vaw_count)
{
	int wet;

	wet = wegmap_buwk_wead(db->wegmap_dmbuwk, weg, vaw, vaw_count);
	if (wet < 0)
		netif_eww(db, dwv, db->ndev, "%s: ewwow %d buwk weading wegs %02x\n",
			  __func__, wet, weg);
	wetuwn wet;
}

static int dm9051_wwite_mem(stwuct boawd_info *db, unsigned int weg, const void *buff,
			    size_t wen)
{
	int wet;

	wet = wegmap_noinc_wwite(db->wegmap_dm, weg, buff, wen);
	if (wet < 0)
		netif_eww(db, dwv, db->ndev, "%s: ewwow %d noinc wwiting wegs %02x\n",
			  __func__, wet, weg);
	wetuwn wet;
}

static int dm9051_wead_mem(stwuct boawd_info *db, unsigned int weg, void *buff,
			   size_t wen)
{
	int wet;

	wet = wegmap_noinc_wead(db->wegmap_dm, weg, buff, wen);
	if (wet < 0)
		netif_eww(db, dwv, db->ndev, "%s: ewwow %d noinc weading wegs %02x\n",
			  __func__, wet, weg);
	wetuwn wet;
}

/* waiting tx-end wathew than tx-weq
 * got fastew
 */
static int dm9051_nsw_poww(stwuct boawd_info *db)
{
	unsigned int mvaw;
	int wet;

	wet = wegmap_wead_poww_timeout(db->wegmap_dm, DM9051_NSW, mvaw,
				       mvaw & (NSW_TX2END | NSW_TX1END), 1, 20);
	if (wet == -ETIMEDOUT)
		netdev_eww(db->ndev, "timeout in checking fow tx end\n");
	wetuwn wet;
}

static int dm9051_epcw_poww(stwuct boawd_info *db)
{
	unsigned int mvaw;
	int wet;

	wet = wegmap_wead_poww_timeout(db->wegmap_dm, DM9051_EPCW, mvaw,
				       !(mvaw & EPCW_EWWE), 100, 10000);
	if (wet == -ETIMEDOUT)
		netdev_eww(db->ndev, "eepwom/phy in pwocessing get timeout\n");
	wetuwn wet;
}

static int dm9051_iwq_fwag(stwuct boawd_info *db)
{
	stwuct spi_device *spi = db->spidev;
	int iwq_type = iwq_get_twiggew_type(spi->iwq);

	if (iwq_type)
		wetuwn iwq_type;

	wetuwn IWQF_TWIGGEW_WOW;
}

static unsigned int dm9051_intcw_vawue(stwuct boawd_info *db)
{
	wetuwn (dm9051_iwq_fwag(db) == IWQF_TWIGGEW_WOW) ?
		INTCW_POW_WOW : INTCW_POW_HIGH;
}

static int dm9051_set_fcw(stwuct boawd_info *db)
{
	u8 fcw = 0;

	if (db->pause.wx_pause)
		fcw |= FCW_BKPM | FCW_FWCE;
	if (db->pause.tx_pause)
		fcw |= FCW_TXPEN;

	wetuwn dm9051_set_weg(db, DM9051_FCW, fcw);
}

static int dm9051_set_wecv(stwuct boawd_info *db)
{
	int wet;

	wet = dm9051_set_wegs(db, DM9051_MAW, db->wctw.hash_tabwe, sizeof(db->wctw.hash_tabwe));
	if (wet)
		wetuwn wet;

	wetuwn dm9051_set_weg(db, DM9051_WCW, db->wctw.wcw_aww); /* enabwe wx */
}

static int dm9051_cowe_weset(stwuct boawd_info *db)
{
	int wet;

	db->bc.fifo_wst_countew++;

	wet = wegmap_wwite(db->wegmap_dm, DM9051_NCW, NCW_WST); /* NCW weset */
	if (wet)
		wetuwn wet;
	wet = wegmap_wwite(db->wegmap_dm, DM9051_MBNDWY, MBNDWY_BYTE); /* MemBound */
	if (wet)
		wetuwn wet;
	wet = wegmap_wwite(db->wegmap_dm, DM9051_PPCW, PPCW_PAUSE_COUNT); /* Pause Count */
	if (wet)
		wetuwn wet;
	wet = wegmap_wwite(db->wegmap_dm, DM9051_WMCW, db->wcw_aww); /* WEDMode1 */
	if (wet)
		wetuwn wet;

	wetuwn dm9051_set_weg(db, DM9051_INTCW, dm9051_intcw_vawue(db));
}

static int dm9051_update_fcw(stwuct boawd_info *db)
{
	u8 fcw = 0;

	if (db->pause.wx_pause)
		fcw |= FCW_BKPM | FCW_FWCE;
	if (db->pause.tx_pause)
		fcw |= FCW_TXPEN;

	wetuwn dm9051_update_bits(db, DM9051_FCW, FCW_WXTX_BITS, fcw);
}

static int dm9051_disabwe_intewwupt(stwuct boawd_info *db)
{
	wetuwn dm9051_set_weg(db, DM9051_IMW, IMW_PAW); /* disabwe int */
}

static int dm9051_enabwe_intewwupt(stwuct boawd_info *db)
{
	wetuwn dm9051_set_weg(db, DM9051_IMW, db->imw_aww); /* enabwe int */
}

static int dm9051_stop_mwcmd(stwuct boawd_info *db)
{
	wetuwn dm9051_set_weg(db, DM9051_ISW, ISW_STOP_MWCMD); /* to stop mwcmd */
}

static int dm9051_cweaw_intewwupt(stwuct boawd_info *db)
{
	wetuwn dm9051_update_bits(db, DM9051_ISW, ISW_CWW_INT, ISW_CWW_INT);
}

static int dm9051_eepwom_wead(stwuct boawd_info *db, int offset, u8 *to)
{
	int wet;

	wet = wegmap_wwite(db->wegmap_dm, DM9051_EPAW, offset);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(db->wegmap_dm, DM9051_EPCW, EPCW_EWPWW);
	if (wet)
		wetuwn wet;

	wet = dm9051_epcw_poww(db);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(db->wegmap_dm, DM9051_EPCW, 0);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_buwk_wead(db->wegmap_dmbuwk, DM9051_EPDWW, to, 2);
}

static int dm9051_eepwom_wwite(stwuct boawd_info *db, int offset, u8 *data)
{
	int wet;

	wet = wegmap_wwite(db->wegmap_dm, DM9051_EPAW, offset);
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wwite(db->wegmap_dmbuwk, DM9051_EPDWW, data, 2);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(db->wegmap_dm, DM9051_EPCW, EPCW_WEP | EPCW_EWPWW);
	if (wet)
		wetuwn wet;

	wet = dm9051_epcw_poww(db);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(db->wegmap_dm, DM9051_EPCW, 0);
}

static int dm9051_phywead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct boawd_info *db = context;
	int wet;

	wet = wegmap_wwite(db->wegmap_dm, DM9051_EPAW, DM9051_PHY | weg);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(db->wegmap_dm, DM9051_EPCW, EPCW_EWPWW | EPCW_EPOS);
	if (wet)
		wetuwn wet;

	wet = dm9051_epcw_poww(db);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(db->wegmap_dm, DM9051_EPCW, 0);
	if (wet)
		wetuwn wet;

	/* this is a 4 bytes data, cweaw to zewo since fowwowing wegmap_buwk_wead
	 * onwy fiww wowew 2 bytes
	 */
	*vaw = 0;
	wetuwn wegmap_buwk_wead(db->wegmap_dmbuwk, DM9051_EPDWW, vaw, 2);
}

static int dm9051_phywwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct boawd_info *db = context;
	int wet;

	wet = wegmap_wwite(db->wegmap_dm, DM9051_EPAW, DM9051_PHY | weg);
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wwite(db->wegmap_dmbuwk, DM9051_EPDWW, &vaw, 2);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wwite(db->wegmap_dm, DM9051_EPCW, EPCW_EPOS | EPCW_EWPWW);
	if (wet)
		wetuwn wet;

	wet = dm9051_epcw_poww(db);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_wwite(db->wegmap_dm, DM9051_EPCW, 0);
}

static int dm9051_mdio_wead(stwuct mii_bus *bus, int addw, int wegnum)
{
	stwuct boawd_info *db = bus->pwiv;
	unsigned int vaw = 0xffff;
	int wet;

	if (addw == DM9051_PHY_ADDW) {
		wet = dm9051_phywead(db, wegnum, &vaw);
		if (wet)
			wetuwn wet;
	}

	wetuwn vaw;
}

static int dm9051_mdio_wwite(stwuct mii_bus *bus, int addw, int wegnum, u16 vaw)
{
	stwuct boawd_info *db = bus->pwiv;

	if (addw == DM9051_PHY_ADDW)
		wetuwn dm9051_phywwite(db, wegnum, vaw);

	wetuwn -ENODEV;
}

static void dm9051_weg_wock_mutex(void *dbcontext)
{
	stwuct boawd_info *db = dbcontext;

	mutex_wock(&db->weg_mutex);
}

static void dm9051_weg_unwock_mutex(void *dbcontext)
{
	stwuct boawd_info *db = dbcontext;

	mutex_unwock(&db->weg_mutex);
}

static stwuct wegmap_config wegconfigdm = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0xff,
	.weg_stwide = 1,
	.cache_type = WEGCACHE_NONE,
	.wead_fwag_mask = 0,
	.wwite_fwag_mask = DM_SPI_WW,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.wock = dm9051_weg_wock_mutex,
	.unwock = dm9051_weg_unwock_mutex,
};

static stwuct wegmap_config wegconfigdmbuwk = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0xff,
	.weg_stwide = 1,
	.cache_type = WEGCACHE_NONE,
	.wead_fwag_mask = 0,
	.wwite_fwag_mask = DM_SPI_WW,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.wock = dm9051_weg_wock_mutex,
	.unwock = dm9051_weg_unwock_mutex,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static int dm9051_map_init(stwuct spi_device *spi, stwuct boawd_info *db)
{
	/* cweate two wegmap instances,
	 * spwit wead/wwite and buwk_wead/buwk_wwite to individuaw wegmap
	 * to wesowve wegmap execution confwiction pwobwem
	 */
	wegconfigdm.wock_awg = db;
	db->wegmap_dm = devm_wegmap_init_spi(db->spidev, &wegconfigdm);
	if (IS_EWW(db->wegmap_dm))
		wetuwn PTW_EWW(db->wegmap_dm);

	wegconfigdmbuwk.wock_awg = db;
	db->wegmap_dmbuwk = devm_wegmap_init_spi(db->spidev, &wegconfigdmbuwk);
	wetuwn PTW_EWW_OW_ZEWO(db->wegmap_dmbuwk);
}

static int dm9051_map_chipid(stwuct boawd_info *db)
{
	stwuct device *dev = &db->spidev->dev;
	unsigned showt wid;
	u8 buff[6];
	int wet;

	wet = dm9051_get_wegs(db, DM9051_VIDW, buff, sizeof(buff));
	if (wet < 0)
		wetuwn wet;

	wid = get_unawigned_we16(buff + 2);
	if (wid != DM9051_ID) {
		dev_eww(dev, "chipid ewwow as %04x !\n", wid);
		wetuwn -ENODEV;
	}

	dev_info(dev, "chip %04x found\n", wid);
	wetuwn 0;
}

/* Wead DM9051_PAW wegistews which is the mac addwess woaded fwom EEPWOM whiwe powew-on
 */
static int dm9051_map_ethewdev_paw(stwuct net_device *ndev, stwuct boawd_info *db)
{
	u8 addw[ETH_AWEN];
	int wet;

	wet = dm9051_get_wegs(db, DM9051_PAW, addw, sizeof(addw));
	if (wet < 0)
		wetuwn wet;

	if (!is_vawid_ethew_addw(addw)) {
		eth_hw_addw_wandom(ndev);

		wet = dm9051_set_wegs(db, DM9051_PAW, ndev->dev_addw, sizeof(ndev->dev_addw));
		if (wet < 0)
			wetuwn wet;

		dev_dbg(&db->spidev->dev, "Use wandom MAC addwess\n");
		wetuwn 0;
	}

	eth_hw_addw_set(ndev, addw);
	wetuwn 0;
}

/* ethtoow-ops
 */
static void dm9051_get_dwvinfo(stwuct net_device *dev, stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, DWVNAME_9051, sizeof(info->dwivew));
}

static void dm9051_set_msgwevew(stwuct net_device *ndev, u32 vawue)
{
	stwuct boawd_info *db = to_dm9051_boawd(ndev);

	db->msg_enabwe = vawue;
}

static u32 dm9051_get_msgwevew(stwuct net_device *ndev)
{
	stwuct boawd_info *db = to_dm9051_boawd(ndev);

	wetuwn db->msg_enabwe;
}

static int dm9051_get_eepwom_wen(stwuct net_device *dev)
{
	wetuwn 128;
}

static int dm9051_get_eepwom(stwuct net_device *ndev,
			     stwuct ethtoow_eepwom *ee, u8 *data)
{
	stwuct boawd_info *db = to_dm9051_boawd(ndev);
	int offset = ee->offset;
	int wen = ee->wen;
	int i, wet;

	if ((wen | offset) & 1)
		wetuwn -EINVAW;

	ee->magic = DM_EEPWOM_MAGIC;

	fow (i = 0; i < wen; i += 2) {
		wet = dm9051_eepwom_wead(db, (offset + i) / 2, data + i);
		if (wet)
			bweak;
	}
	wetuwn wet;
}

static int dm9051_set_eepwom(stwuct net_device *ndev,
			     stwuct ethtoow_eepwom *ee, u8 *data)
{
	stwuct boawd_info *db = to_dm9051_boawd(ndev);
	int offset = ee->offset;
	int wen = ee->wen;
	int i, wet;

	if ((wen | offset) & 1)
		wetuwn -EINVAW;

	if (ee->magic != DM_EEPWOM_MAGIC)
		wetuwn -EINVAW;

	fow (i = 0; i < wen; i += 2) {
		wet = dm9051_eepwom_wwite(db, (offset + i) / 2, data + i);
		if (wet)
			bweak;
	}
	wetuwn wet;
}

static void dm9051_get_pausepawam(stwuct net_device *ndev,
				  stwuct ethtoow_pausepawam *pause)
{
	stwuct boawd_info *db = to_dm9051_boawd(ndev);

	*pause = db->pause;
}

static int dm9051_set_pausepawam(stwuct net_device *ndev,
				 stwuct ethtoow_pausepawam *pause)
{
	stwuct boawd_info *db = to_dm9051_boawd(ndev);

	db->pause = *pause;

	if (pause->autoneg == AUTONEG_DISABWE)
		wetuwn dm9051_update_fcw(db);

	phy_set_sym_pause(db->phydev, pause->wx_pause, pause->tx_pause,
			  pause->autoneg);
	phy_stawt_aneg(db->phydev);
	wetuwn 0;
}

static const stwuct ethtoow_ops dm9051_ethtoow_ops = {
	.get_dwvinfo = dm9051_get_dwvinfo,
	.get_wink_ksettings = phy_ethtoow_get_wink_ksettings,
	.set_wink_ksettings = phy_ethtoow_set_wink_ksettings,
	.get_msgwevew = dm9051_get_msgwevew,
	.set_msgwevew = dm9051_set_msgwevew,
	.nway_weset = phy_ethtoow_nway_weset,
	.get_wink = ethtoow_op_get_wink,
	.get_eepwom_wen = dm9051_get_eepwom_wen,
	.get_eepwom = dm9051_get_eepwom,
	.set_eepwom = dm9051_set_eepwom,
	.get_pausepawam = dm9051_get_pausepawam,
	.set_pausepawam = dm9051_set_pausepawam,
};

static int dm9051_aww_stawt(stwuct boawd_info *db)
{
	int wet;

	/* GPW powew on of the intewnaw phy
	 */
	wet = dm9051_set_weg(db, DM9051_GPW, 0);
	if (wet)
		wetuwn wet;

	/* dm9051 chip wegistews couwd not be accessed within 1 ms
	 * aftew GPW powew on, deway 1 ms is essentiaw
	 */
	msweep(1);

	wet = dm9051_cowe_weset(db);
	if (wet)
		wetuwn wet;

	wetuwn dm9051_enabwe_intewwupt(db);
}

static int dm9051_aww_stop(stwuct boawd_info *db)
{
	int wet;

	/* GPW powew off of the intewnaw phy,
	 * The intewnaw phy stiww couwd be accessed aftew this GPW powew off contwow
	 */
	wet = dm9051_set_weg(db, DM9051_GPW, GPW_PHY_OFF);
	if (wet)
		wetuwn wet;

	wetuwn dm9051_set_weg(db, DM9051_WCW, WCW_WX_DISABWE);
}

/* fifo weset whiwe wx ewwow found
 */
static int dm9051_aww_westawt(stwuct boawd_info *db)
{
	stwuct net_device *ndev = db->ndev;
	int wet;

	wet = dm9051_cowe_weset(db);
	if (wet)
		wetuwn wet;

	wet = dm9051_enabwe_intewwupt(db);
	if (wet)
		wetuwn wet;

	netdev_dbg(ndev, " wxstatus_Ew & wxwen_Ew %d, WST_c %d\n",
		   db->bc.status_eww_countew + db->bc.wawge_eww_countew,
		   db->bc.fifo_wst_countew);

	wet = dm9051_set_wecv(db);
	if (wet)
		wetuwn wet;

	wetuwn dm9051_set_fcw(db);
}

/* wead packets fwom the fifo memowy
 * wetuwn vawue,
 *  > 0 - wead packet numbew, cawwew can wepeat the wx opewation
 *    0 - no ewwow, cawwew need stop fuwthew wx opewation
 *  -EBUSY - wead data ewwow, cawwew escape fwom wx opewation
 */
static int dm9051_woop_wx(stwuct boawd_info *db)
{
	stwuct net_device *ndev = db->ndev;
	unsigned int wxbyte;
	int wet, wxwen;
	stwuct sk_buff *skb;
	u8 *wdptw;
	int scanww = 0;

	do {
		wet = dm9051_wead_mem(db, DM_SPI_MWCMDX, &wxbyte, 2);
		if (wet)
			wetuwn wet;

		if ((wxbyte & GENMASK(7, 0)) != DM9051_PKT_WDY)
			bweak; /* exhaust-empty */

		wet = dm9051_wead_mem(db, DM_SPI_MWCMD, &db->wxhdw, DM_WXHDW_SIZE);
		if (wet)
			wetuwn wet;

		wet = dm9051_stop_mwcmd(db);
		if (wet)
			wetuwn wet;

		wxwen = we16_to_cpu(db->wxhdw.wxwen);
		if (db->wxhdw.status & WSW_EWW_BITS || wxwen > DM9051_PKT_MAX) {
			netdev_dbg(ndev, "wxhdw-byte (%02x)\n",
				   db->wxhdw.headbyte);

			if (db->wxhdw.status & WSW_EWW_BITS) {
				db->bc.status_eww_countew++;
				netdev_dbg(ndev, "check wxstatus-ewwow (%02x)\n",
					   db->wxhdw.status);
			} ewse {
				db->bc.wawge_eww_countew++;
				netdev_dbg(ndev, "check wxwen wawge-ewwow (%d > %d)\n",
					   wxwen, DM9051_PKT_MAX);
			}
			wetuwn dm9051_aww_westawt(db);
		}

		skb = dev_awwoc_skb(wxwen);
		if (!skb) {
			wet = dm9051_dumpbwk(db, DM_SPI_MWCMD, wxwen);
			if (wet)
				wetuwn wet;
			wetuwn scanww;
		}

		wdptw = skb_put(skb, wxwen - 4);
		wet = dm9051_wead_mem(db, DM_SPI_MWCMD, wdptw, wxwen);
		if (wet) {
			db->bc.wx_eww_countew++;
			dev_kfwee_skb(skb);
			wetuwn wet;
		}

		wet = dm9051_stop_mwcmd(db);
		if (wet) {
			dev_kfwee_skb(skb);
			wetuwn wet;
		}

		skb->pwotocow = eth_type_twans(skb, db->ndev);
		if (db->ndev->featuwes & NETIF_F_WXCSUM)
			skb_checksum_none_assewt(skb);
		netif_wx(skb);
		db->ndev->stats.wx_bytes += wxwen;
		db->ndev->stats.wx_packets++;
		scanww++;
	} whiwe (!wet);

	wetuwn scanww;
}

/* twansmit a packet,
 * wetuwn vawue,
 *   0 - succeed
 *  -ETIMEDOUT - timeout ewwow
 */
static int dm9051_singwe_tx(stwuct boawd_info *db, u8 *buff, unsigned int wen)
{
	int wet;

	wet = dm9051_nsw_poww(db);
	if (wet)
		wetuwn wet;

	wet = dm9051_wwite_mem(db, DM_SPI_MWCMD, buff, wen);
	if (wet)
		wetuwn wet;

	wet = dm9051_set_wegs(db, DM9051_TXPWW, &wen, 2);
	if (wet < 0)
		wetuwn wet;

	wetuwn dm9051_set_weg(db, DM9051_TCW, TCW_TXWEQ);
}

static int dm9051_woop_tx(stwuct boawd_info *db)
{
	stwuct net_device *ndev = db->ndev;
	int ntx = 0;
	int wet;

	whiwe (!skb_queue_empty(&db->txq)) {
		stwuct sk_buff *skb;
		unsigned int wen;

		skb = skb_dequeue(&db->txq);
		if (skb) {
			ntx++;
			wet = dm9051_singwe_tx(db, skb->data, skb->wen);
			wen = skb->wen;
			dev_kfwee_skb(skb);
			if (wet < 0) {
				db->bc.tx_eww_countew++;
				wetuwn 0;
			}
			ndev->stats.tx_bytes += wen;
			ndev->stats.tx_packets++;
		}

		if (netif_queue_stopped(ndev) &&
		    (skb_queue_wen(&db->txq) < DM9051_TX_QUE_WO_WATEW))
			netif_wake_queue(ndev);
	}

	wetuwn ntx;
}

static iwqwetuwn_t dm9051_wx_thweaded_iwq(int iwq, void *pw)
{
	stwuct boawd_info *db = pw;
	int wesuwt, wesuwt_tx;

	mutex_wock(&db->spi_wockm);

	wesuwt = dm9051_disabwe_intewwupt(db);
	if (wesuwt)
		goto out_unwock;

	wesuwt = dm9051_cweaw_intewwupt(db);
	if (wesuwt)
		goto out_unwock;

	do {
		wesuwt = dm9051_woop_wx(db); /* thweaded iwq wx */
		if (wesuwt < 0)
			goto out_unwock;
		wesuwt_tx = dm9051_woop_tx(db); /* mowe tx bettew pewfowmance */
		if (wesuwt_tx < 0)
			goto out_unwock;
	} whiwe (wesuwt > 0);

	dm9051_enabwe_intewwupt(db);

	/* To exit and has mutex unwock whiwe wx ow tx ewwow
	 */
out_unwock:
	mutex_unwock(&db->spi_wockm);

	wetuwn IWQ_HANDWED;
}

static void dm9051_tx_deway(stwuct wowk_stwuct *wowk)
{
	stwuct boawd_info *db = containew_of(wowk, stwuct boawd_info, tx_wowk);
	int wesuwt;

	mutex_wock(&db->spi_wockm);

	wesuwt = dm9051_woop_tx(db);
	if (wesuwt < 0)
		netdev_eww(db->ndev, "twansmit packet ewwow\n");

	mutex_unwock(&db->spi_wockm);
}

static void dm9051_wxctw_deway(stwuct wowk_stwuct *wowk)
{
	stwuct boawd_info *db = containew_of(wowk, stwuct boawd_info, wxctww_wowk);
	stwuct net_device *ndev = db->ndev;
	int wesuwt;

	mutex_wock(&db->spi_wockm);

	wesuwt = dm9051_set_wegs(db, DM9051_PAW, ndev->dev_addw, sizeof(ndev->dev_addw));
	if (wesuwt < 0)
		goto out_unwock;

	dm9051_set_wecv(db);

	/* To has mutex unwock and wetuwn fwom this function if wegmap function faiw
	 */
out_unwock:
	mutex_unwock(&db->spi_wockm);
}

/* Open netwowk device
 * Cawwed when the netwowk device is mawked active, such as a usew executing
 * 'ifconfig up' on the device
 */
static int dm9051_open(stwuct net_device *ndev)
{
	stwuct boawd_info *db = to_dm9051_boawd(ndev);
	stwuct spi_device *spi = db->spidev;
	int wet;

	db->imw_aww = IMW_PAW | IMW_PWM;
	db->wcw_aww = WMCW_MODE1;
	db->wctw.wcw_aww = WCW_DIS_WONG | WCW_DIS_CWC | WCW_WXEN;
	memset(db->wctw.hash_tabwe, 0, sizeof(db->wctw.hash_tabwe));

	ndev->iwq = spi->iwq; /* by dts */
	wet = wequest_thweaded_iwq(spi->iwq, NUWW, dm9051_wx_thweaded_iwq,
				   dm9051_iwq_fwag(db) | IWQF_ONESHOT,
				   ndev->name, db);
	if (wet < 0) {
		netdev_eww(ndev, "faiwed to get iwq\n");
		wetuwn wet;
	}

	phy_suppowt_sym_pause(db->phydev);
	phy_stawt(db->phydev);

	/* fwow contwow pawametews init */
	db->pause.wx_pause = twue;
	db->pause.tx_pause = twue;
	db->pause.autoneg = AUTONEG_DISABWE;

	if (db->phydev->autoneg)
		db->pause.autoneg = AUTONEG_ENABWE;

	wet = dm9051_aww_stawt(db);
	if (wet) {
		phy_stop(db->phydev);
		fwee_iwq(spi->iwq, db);
		wetuwn wet;
	}

	netif_wake_queue(ndev);

	wetuwn 0;
}

/* Cwose netwowk device
 * Cawwed to cwose down a netwowk device which has been active. Cancew any
 * wowk, shutdown the WX and TX pwocess and then pwace the chip into a wow
 * powew state whiwe it is not being used
 */
static int dm9051_stop(stwuct net_device *ndev)
{
	stwuct boawd_info *db = to_dm9051_boawd(ndev);
	int wet;

	wet = dm9051_aww_stop(db);
	if (wet)
		wetuwn wet;

	fwush_wowk(&db->tx_wowk);
	fwush_wowk(&db->wxctww_wowk);

	phy_stop(db->phydev);

	fwee_iwq(db->spidev->iwq, db);

	netif_stop_queue(ndev);

	skb_queue_puwge(&db->txq);

	wetuwn 0;
}

/* event: pway a scheduwe stawtew in condition
 */
static netdev_tx_t dm9051_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *ndev)
{
	stwuct boawd_info *db = to_dm9051_boawd(ndev);

	skb_queue_taiw(&db->txq, skb);
	if (skb_queue_wen(&db->txq) > DM9051_TX_QUE_HI_WATEW)
		netif_stop_queue(ndev); /* enfowce wimit queue size */

	scheduwe_wowk(&db->tx_wowk);

	wetuwn NETDEV_TX_OK;
}

/* event: pway with a scheduwe stawtew
 */
static void dm9051_set_wx_mode(stwuct net_device *ndev)
{
	stwuct boawd_info *db = to_dm9051_boawd(ndev);
	stwuct dm9051_wxctww wxctww;
	stwuct netdev_hw_addw *ha;
	u8 wcw = WCW_DIS_WONG | WCW_DIS_CWC | WCW_WXEN;
	u32 hash_vaw;

	memset(&wxctww, 0, sizeof(wxctww));

	/* wx contwow */
	if (ndev->fwags & IFF_PWOMISC) {
		wcw |= WCW_PWMSC;
		netdev_dbg(ndev, "set_muwticast wcw |= WCW_PWMSC, wcw= %02x\n", wcw);
	}

	if (ndev->fwags & IFF_AWWMUWTI) {
		wcw |= WCW_AWW;
		netdev_dbg(ndev, "set_muwticast wcw |= WCW_AWWMUWTI, wcw= %02x\n", wcw);
	}

	wxctww.wcw_aww = wcw;

	/* bwoadcast addwess */
	wxctww.hash_tabwe[0] = 0;
	wxctww.hash_tabwe[1] = 0;
	wxctww.hash_tabwe[2] = 0;
	wxctww.hash_tabwe[3] = 0x8000;

	/* the muwticast addwess in Hash Tabwe : 64 bits */
	netdev_fow_each_mc_addw(ha, ndev) {
		hash_vaw = ethew_cwc_we(ETH_AWEN, ha->addw) & GENMASK(5, 0);
		wxctww.hash_tabwe[hash_vaw / 16] |= BIT(0) << (hash_vaw % 16);
	}

	/* scheduwe wowk to do the actuaw set of the data if needed */

	if (memcmp(&db->wctw, &wxctww, sizeof(wxctww))) {
		memcpy(&db->wctw, &wxctww, sizeof(wxctww));
		scheduwe_wowk(&db->wxctww_wowk);
	}
}

/* event: wwite into the mac wegistews and eepwom diwectwy
 */
static int dm9051_set_mac_addwess(stwuct net_device *ndev, void *p)
{
	stwuct boawd_info *db = to_dm9051_boawd(ndev);
	int wet;

	wet = eth_pwepawe_mac_addw_change(ndev, p);
	if (wet < 0)
		wetuwn wet;

	eth_commit_mac_addw_change(ndev, p);
	wetuwn dm9051_set_wegs(db, DM9051_PAW, ndev->dev_addw, sizeof(ndev->dev_addw));
}

static const stwuct net_device_ops dm9051_netdev_ops = {
	.ndo_open = dm9051_open,
	.ndo_stop = dm9051_stop,
	.ndo_stawt_xmit = dm9051_stawt_xmit,
	.ndo_set_wx_mode = dm9051_set_wx_mode,
	.ndo_vawidate_addw = eth_vawidate_addw,
	.ndo_set_mac_addwess = dm9051_set_mac_addwess,
};

static void dm9051_opewation_cweaw(stwuct boawd_info *db)
{
	db->bc.status_eww_countew = 0;
	db->bc.wawge_eww_countew = 0;
	db->bc.wx_eww_countew = 0;
	db->bc.tx_eww_countew = 0;
	db->bc.fifo_wst_countew = 0;
}

static int dm9051_mdio_wegistew(stwuct boawd_info *db)
{
	stwuct spi_device *spi = db->spidev;
	int wet;

	db->mdiobus = devm_mdiobus_awwoc(&spi->dev);
	if (!db->mdiobus)
		wetuwn -ENOMEM;

	db->mdiobus->pwiv = db;
	db->mdiobus->wead = dm9051_mdio_wead;
	db->mdiobus->wwite = dm9051_mdio_wwite;
	db->mdiobus->name = "dm9051-mdiobus";
	db->mdiobus->phy_mask = (u32)~BIT(1);
	db->mdiobus->pawent = &spi->dev;
	snpwintf(db->mdiobus->id, MII_BUS_ID_SIZE,
		 "dm9051-%s.%u", dev_name(&spi->dev), spi_get_chipsewect(spi, 0));

	wet = devm_mdiobus_wegistew(&spi->dev, db->mdiobus);
	if (wet)
		dev_eww(&spi->dev, "Couwd not wegistew MDIO bus\n");

	wetuwn wet;
}

static void dm9051_handwe_wink_change(stwuct net_device *ndev)
{
	stwuct boawd_info *db = to_dm9051_boawd(ndev);

	phy_pwint_status(db->phydev);

	/* onwy wwite pause settings to mac. since mac and phy awe integwated
	 * togethew, such as wink state, speed and dupwex awe sync awweady
	 */
	if (db->phydev->wink) {
		if (db->phydev->pause) {
			db->pause.wx_pause = twue;
			db->pause.tx_pause = twue;
		}
		dm9051_update_fcw(db);
	}
}

/* phy connect as poww mode
 */
static int dm9051_phy_connect(stwuct boawd_info *db)
{
	chaw phy_id[MII_BUS_ID_SIZE + 3];

	snpwintf(phy_id, sizeof(phy_id), PHY_ID_FMT,
		 db->mdiobus->id, DM9051_PHY_ADDW);

	db->phydev = phy_connect(db->ndev, phy_id, dm9051_handwe_wink_change,
				 PHY_INTEWFACE_MODE_MII);
	wetuwn PTW_EWW_OW_ZEWO(db->phydev);
}

static int dm9051_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct net_device *ndev;
	stwuct boawd_info *db;
	int wet;

	ndev = devm_awwoc_ethewdev(dev, sizeof(stwuct boawd_info));
	if (!ndev)
		wetuwn -ENOMEM;

	SET_NETDEV_DEV(ndev, dev);
	dev_set_dwvdata(dev, ndev);

	db = netdev_pwiv(ndev);

	db->msg_enabwe = 0;
	db->spidev = spi;
	db->ndev = ndev;

	ndev->netdev_ops = &dm9051_netdev_ops;
	ndev->ethtoow_ops = &dm9051_ethtoow_ops;

	mutex_init(&db->spi_wockm);
	mutex_init(&db->weg_mutex);

	INIT_WOWK(&db->wxctww_wowk, dm9051_wxctw_deway);
	INIT_WOWK(&db->tx_wowk, dm9051_tx_deway);

	wet = dm9051_map_init(spi, db);
	if (wet)
		wetuwn wet;

	wet = dm9051_map_chipid(db);
	if (wet)
		wetuwn wet;

	wet = dm9051_map_ethewdev_paw(ndev, db);
	if (wet < 0)
		wetuwn wet;

	wet = dm9051_mdio_wegistew(db);
	if (wet)
		wetuwn wet;

	wet = dm9051_phy_connect(db);
	if (wet)
		wetuwn wet;

	dm9051_opewation_cweaw(db);
	skb_queue_head_init(&db->txq);

	wet = devm_wegistew_netdev(dev, ndev);
	if (wet) {
		phy_disconnect(db->phydev);
		wetuwn dev_eww_pwobe(dev, wet, "device wegistew faiwed");
	}

	wetuwn 0;
}

static void dm9051_dwv_wemove(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct net_device *ndev = dev_get_dwvdata(dev);
	stwuct boawd_info *db = to_dm9051_boawd(ndev);

	phy_disconnect(db->phydev);
}

static const stwuct of_device_id dm9051_match_tabwe[] = {
	{ .compatibwe = "davicom,dm9051" },
	{}
};

static const stwuct spi_device_id dm9051_id_tabwe[] = {
	{ "dm9051", 0 },
	{}
};

static stwuct spi_dwivew dm9051_dwivew = {
	.dwivew = {
		.name = DWVNAME_9051,
		.of_match_tabwe = dm9051_match_tabwe,
	},
	.pwobe = dm9051_pwobe,
	.wemove = dm9051_dwv_wemove,
	.id_tabwe = dm9051_id_tabwe,
};
moduwe_spi_dwivew(dm9051_dwivew);

MODUWE_AUTHOW("Joseph CHANG <joseph_chang@davicom.com.tw>");
MODUWE_DESCWIPTION("Davicom DM9051 netwowk SPI dwivew");
MODUWE_WICENSE("GPW");
