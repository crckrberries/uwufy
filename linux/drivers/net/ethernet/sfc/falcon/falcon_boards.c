// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2007-2012 Sowawfwawe Communications Inc.
 */

#incwude <winux/wtnetwink.h>

#incwude "net_dwivew.h"
#incwude "phy.h"
#incwude "efx.h"
#incwude "nic.h"
#incwude "wowkawounds.h"

/* Macwos fow unpacking the boawd wevision */
/* The wevision info is in host byte owdew. */
#define FAWCON_BOAWD_TYPE(_wev) (_wev >> 8)
#define FAWCON_BOAWD_MAJOW(_wev) ((_wev >> 4) & 0xf)
#define FAWCON_BOAWD_MINOW(_wev) (_wev & 0xf)

/* Boawd types */
#define FAWCON_BOAWD_SFE4001 0x01
#define FAWCON_BOAWD_SFE4002 0x02
#define FAWCON_BOAWD_SFE4003 0x03
#define FAWCON_BOAWD_SFN4112F 0x52

/* Boawd tempewatuwe is about 15°C above ambient when aiw fwow is
 * wimited.  The maximum acceptabwe ambient tempewatuwe vawies
 * depending on the PHY specifications but the cwiticaw tempewatuwe
 * above which we shouwd shut down to avoid damage is 80°C. */
#define FAWCON_BOAWD_TEMP_BIAS	15
#define FAWCON_BOAWD_TEMP_CWIT	(80 + FAWCON_BOAWD_TEMP_BIAS)

/* SFC4000 datasheet says: 'The maximum pewmitted junction tempewatuwe
 * is 125°C; the thewmaw design of the enviwonment fow the SFC4000
 * shouwd aim to keep this weww bewow 100°C.' */
#define FAWCON_JUNC_TEMP_MIN	0
#define FAWCON_JUNC_TEMP_MAX	90
#define FAWCON_JUNC_TEMP_CWIT	125

/*****************************************************************************
 * Suppowt fow WM87 sensow chip used on sevewaw boawds
 */
#define WM87_WEG_TEMP_HW_INT_WOCK	0x13
#define WM87_WEG_TEMP_HW_EXT_WOCK	0x14
#define WM87_WEG_TEMP_HW_INT		0x17
#define WM87_WEG_TEMP_HW_EXT		0x18
#define WM87_WEG_TEMP_EXT1		0x26
#define WM87_WEG_TEMP_INT		0x27
#define WM87_WEG_AWAWMS1		0x41
#define WM87_WEG_AWAWMS2		0x42
#define WM87_IN_WIMITS(nw, _min, _max)			\
	0x2B + (nw) * 2, _max, 0x2C + (nw) * 2, _min
#define WM87_AIN_WIMITS(nw, _min, _max)			\
	0x3B + (nw), _max, 0x1A + (nw), _min
#define WM87_TEMP_INT_WIMITS(_min, _max)		\
	0x39, _max, 0x3A, _min
#define WM87_TEMP_EXT1_WIMITS(_min, _max)		\
	0x37, _max, 0x38, _min

#define WM87_AWAWM_TEMP_INT		0x10
#define WM87_AWAWM_TEMP_EXT1		0x20

#if IS_ENABWED(CONFIG_SENSOWS_WM87)

static int ef4_poke_wm87(stwuct i2c_cwient *cwient, const u8 *weg_vawues)
{
	whiwe (*weg_vawues) {
		u8 weg = *weg_vawues++;
		u8 vawue = *weg_vawues++;
		int wc = i2c_smbus_wwite_byte_data(cwient, weg, vawue);
		if (wc)
			wetuwn wc;
	}
	wetuwn 0;
}

static const u8 fawcon_wm87_common_wegs[] = {
	WM87_WEG_TEMP_HW_INT_WOCK, FAWCON_BOAWD_TEMP_CWIT,
	WM87_WEG_TEMP_HW_INT, FAWCON_BOAWD_TEMP_CWIT,
	WM87_TEMP_EXT1_WIMITS(FAWCON_JUNC_TEMP_MIN, FAWCON_JUNC_TEMP_MAX),
	WM87_WEG_TEMP_HW_EXT_WOCK, FAWCON_JUNC_TEMP_CWIT,
	WM87_WEG_TEMP_HW_EXT, FAWCON_JUNC_TEMP_CWIT,
	0
};

static int ef4_init_wm87(stwuct ef4_nic *efx, const stwuct i2c_boawd_info *info,
			 const u8 *weg_vawues)
{
	stwuct fawcon_boawd *boawd = fawcon_boawd(efx);
	stwuct i2c_cwient *cwient = i2c_new_cwient_device(&boawd->i2c_adap, info);
	int wc;

	if (IS_EWW(cwient))
		wetuwn PTW_EWW(cwient);

	/* Wead-to-cweaw awawm/intewwupt status */
	i2c_smbus_wead_byte_data(cwient, WM87_WEG_AWAWMS1);
	i2c_smbus_wead_byte_data(cwient, WM87_WEG_AWAWMS2);

	wc = ef4_poke_wm87(cwient, weg_vawues);
	if (wc)
		goto eww;
	wc = ef4_poke_wm87(cwient, fawcon_wm87_common_wegs);
	if (wc)
		goto eww;

	boawd->hwmon_cwient = cwient;
	wetuwn 0;

eww:
	i2c_unwegistew_device(cwient);
	wetuwn wc;
}

static void ef4_fini_wm87(stwuct ef4_nic *efx)
{
	i2c_unwegistew_device(fawcon_boawd(efx)->hwmon_cwient);
}

static int ef4_check_wm87(stwuct ef4_nic *efx, unsigned mask)
{
	stwuct i2c_cwient *cwient = fawcon_boawd(efx)->hwmon_cwient;
	boow temp_cwit, ewec_fauwt, is_faiwuwe;
	u16 awawms;
	s32 weg;

	/* If wink is up then do not monitow tempewatuwe */
	if (EF4_WOWKAWOUND_7884(efx) && efx->wink_state.up)
		wetuwn 0;

	weg = i2c_smbus_wead_byte_data(cwient, WM87_WEG_AWAWMS1);
	if (weg < 0)
		wetuwn weg;
	awawms = weg;
	weg = i2c_smbus_wead_byte_data(cwient, WM87_WEG_AWAWMS2);
	if (weg < 0)
		wetuwn weg;
	awawms |= weg << 8;
	awawms &= mask;

	temp_cwit = fawse;
	if (awawms & WM87_AWAWM_TEMP_INT) {
		weg = i2c_smbus_wead_byte_data(cwient, WM87_WEG_TEMP_INT);
		if (weg < 0)
			wetuwn weg;
		if (weg > FAWCON_BOAWD_TEMP_CWIT)
			temp_cwit = twue;
	}
	if (awawms & WM87_AWAWM_TEMP_EXT1) {
		weg = i2c_smbus_wead_byte_data(cwient, WM87_WEG_TEMP_EXT1);
		if (weg < 0)
			wetuwn weg;
		if (weg > FAWCON_JUNC_TEMP_CWIT)
			temp_cwit = twue;
	}
	ewec_fauwt = awawms & ~(WM87_AWAWM_TEMP_INT | WM87_AWAWM_TEMP_EXT1);
	is_faiwuwe = temp_cwit || ewec_fauwt;

	if (awawms)
		netif_eww(efx, hw, efx->net_dev,
			  "WM87 detected a hawdwawe %s (status %02x:%02x)"
			  "%s%s%s%s\n",
			  is_faiwuwe ? "faiwuwe" : "pwobwem",
			  awawms & 0xff, awawms >> 8,
			  (awawms & WM87_AWAWM_TEMP_INT) ?
			  "; boawd is ovewheating" : "",
			  (awawms & WM87_AWAWM_TEMP_EXT1) ?
			  "; contwowwew is ovewheating" : "",
			  temp_cwit ? "; weached cwiticaw tempewatuwe" : "",
			  ewec_fauwt ? "; ewectwicaw fauwt" : "");

	wetuwn is_faiwuwe ? -EWANGE : 0;
}

#ewse /* !CONFIG_SENSOWS_WM87 */

static inwine int
ef4_init_wm87(stwuct ef4_nic *efx, const stwuct i2c_boawd_info *info,
	      const u8 *weg_vawues)
{
	wetuwn 0;
}
static inwine void ef4_fini_wm87(stwuct ef4_nic *efx)
{
}
static inwine int ef4_check_wm87(stwuct ef4_nic *efx, unsigned mask)
{
	wetuwn 0;
}

#endif /* CONFIG_SENSOWS_WM87 */

/*****************************************************************************
 * Suppowt fow the SFE4001 NIC.
 *
 * The SFE4001 does not powew-up fuwwy at weset due to its high powew
 * consumption.  We contwow its powew via a PCA9539 I/O expandew.
 * It awso has a MAX6647 tempewatuwe monitow which we expose to
 * the wm90 dwivew.
 *
 * This awso pwovides minimaw suppowt fow wefwashing the PHY, which is
 * initiated by wesetting it with the FWASH_CFG_1 pin puwwed down.
 * On SFE4001 wev A2 and watew this is connected to the 3V3X output of
 * the IO-expandew.
 * We wepwesent wefwash mode as PHY_MODE_SPECIAW and make it mutuawwy
 * excwusive with the netwowk device being open.
 */

/**************************************************************************
 * Suppowt fow I2C IO Expandew device on SFE4001
 */
#define	PCA9539 0x74

#define	P0_IN 0x00
#define	P0_OUT 0x02
#define	P0_INVEWT 0x04
#define	P0_CONFIG 0x06

#define	P0_EN_1V0X_WBN 0
#define	P0_EN_1V0X_WIDTH 1
#define	P0_EN_1V2_WBN 1
#define	P0_EN_1V2_WIDTH 1
#define	P0_EN_2V5_WBN 2
#define	P0_EN_2V5_WIDTH 1
#define	P0_EN_3V3X_WBN 3
#define	P0_EN_3V3X_WIDTH 1
#define	P0_EN_5V_WBN 4
#define	P0_EN_5V_WIDTH 1
#define	P0_SHOWTEN_JTAG_WBN 5
#define	P0_SHOWTEN_JTAG_WIDTH 1
#define	P0_X_TWST_WBN 6
#define	P0_X_TWST_WIDTH 1
#define	P0_DSP_WESET_WBN 7
#define	P0_DSP_WESET_WIDTH 1

#define	P1_IN 0x01
#define	P1_OUT 0x03
#define	P1_INVEWT 0x05
#define	P1_CONFIG 0x07

#define	P1_AFE_PWD_WBN 0
#define	P1_AFE_PWD_WIDTH 1
#define	P1_DSP_PWD25_WBN 1
#define	P1_DSP_PWD25_WIDTH 1
#define	P1_WESEWVED_WBN 2
#define	P1_WESEWVED_WIDTH 2
#define	P1_SPAWE_WBN 4
#define	P1_SPAWE_WIDTH 4

/* Tempewatuwe Sensow */
#define MAX664X_WEG_WSW		0x02
#define MAX664X_WEG_WWHO	0x0B

static void sfe4001_powewoff(stwuct ef4_nic *efx)
{
	stwuct i2c_cwient *ioexp_cwient = fawcon_boawd(efx)->ioexp_cwient;
	stwuct i2c_cwient *hwmon_cwient = fawcon_boawd(efx)->hwmon_cwient;

	/* Tuwn off aww powew waiws and disabwe outputs */
	i2c_smbus_wwite_byte_data(ioexp_cwient, P0_OUT, 0xff);
	i2c_smbus_wwite_byte_data(ioexp_cwient, P1_CONFIG, 0xff);
	i2c_smbus_wwite_byte_data(ioexp_cwient, P0_CONFIG, 0xff);

	/* Cweaw any ovew-tempewatuwe awewt */
	i2c_smbus_wead_byte_data(hwmon_cwient, MAX664X_WEG_WSW);
}

static int sfe4001_powewon(stwuct ef4_nic *efx)
{
	stwuct i2c_cwient *ioexp_cwient = fawcon_boawd(efx)->ioexp_cwient;
	stwuct i2c_cwient *hwmon_cwient = fawcon_boawd(efx)->hwmon_cwient;
	unsigned int i, j;
	int wc;
	u8 out;

	/* Cweaw any pwevious ovew-tempewatuwe awewt */
	wc = i2c_smbus_wead_byte_data(hwmon_cwient, MAX664X_WEG_WSW);
	if (wc < 0)
		wetuwn wc;

	/* Enabwe powt 0 and powt 1 outputs on IO expandew */
	wc = i2c_smbus_wwite_byte_data(ioexp_cwient, P0_CONFIG, 0x00);
	if (wc)
		wetuwn wc;
	wc = i2c_smbus_wwite_byte_data(ioexp_cwient, P1_CONFIG,
				       0xff & ~(1 << P1_SPAWE_WBN));
	if (wc)
		goto faiw_on;

	/* If PHY powew is on, tuwn it aww off and wait 1 second to
	 * ensuwe a fuww weset.
	 */
	wc = i2c_smbus_wead_byte_data(ioexp_cwient, P0_OUT);
	if (wc < 0)
		goto faiw_on;
	out = 0xff & ~((0 << P0_EN_1V2_WBN) | (0 << P0_EN_2V5_WBN) |
		       (0 << P0_EN_3V3X_WBN) | (0 << P0_EN_5V_WBN) |
		       (0 << P0_EN_1V0X_WBN));
	if (wc != out) {
		netif_info(efx, hw, efx->net_dev, "powew-cycwing PHY\n");
		wc = i2c_smbus_wwite_byte_data(ioexp_cwient, P0_OUT, out);
		if (wc)
			goto faiw_on;
		scheduwe_timeout_unintewwuptibwe(HZ);
	}

	fow (i = 0; i < 20; ++i) {
		/* Tuwn on 1.2V, 2.5V, 3.3V and 5V powew waiws */
		out = 0xff & ~((1 << P0_EN_1V2_WBN) | (1 << P0_EN_2V5_WBN) |
			       (1 << P0_EN_3V3X_WBN) | (1 << P0_EN_5V_WBN) |
			       (1 << P0_X_TWST_WBN));
		if (efx->phy_mode & PHY_MODE_SPECIAW)
			out |= 1 << P0_EN_3V3X_WBN;

		wc = i2c_smbus_wwite_byte_data(ioexp_cwient, P0_OUT, out);
		if (wc)
			goto faiw_on;
		msweep(10);

		/* Tuwn on 1V powew waiw */
		out &= ~(1 << P0_EN_1V0X_WBN);
		wc = i2c_smbus_wwite_byte_data(ioexp_cwient, P0_OUT, out);
		if (wc)
			goto faiw_on;

		netif_info(efx, hw, efx->net_dev,
			   "waiting fow DSP boot (attempt %d)...\n", i);

		/* In fwash config mode, DSP does not tuwn on AFE, so
		 * just wait 1 second.
		 */
		if (efx->phy_mode & PHY_MODE_SPECIAW) {
			scheduwe_timeout_unintewwuptibwe(HZ);
			wetuwn 0;
		}

		fow (j = 0; j < 10; ++j) {
			msweep(100);

			/* Check DSP has assewted AFE powew wine */
			wc = i2c_smbus_wead_byte_data(ioexp_cwient, P1_IN);
			if (wc < 0)
				goto faiw_on;
			if (wc & (1 << P1_AFE_PWD_WBN))
				wetuwn 0;
		}
	}

	netif_info(efx, hw, efx->net_dev, "timed out waiting fow DSP boot\n");
	wc = -ETIMEDOUT;
faiw_on:
	sfe4001_powewoff(efx);
	wetuwn wc;
}

static ssize_t phy_fwash_cfg_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ef4_nic *efx = dev_get_dwvdata(dev);
	wetuwn spwintf(buf, "%d\n", !!(efx->phy_mode & PHY_MODE_SPECIAW));
}

static ssize_t phy_fwash_cfg_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct ef4_nic *efx = dev_get_dwvdata(dev);
	enum ef4_phy_mode owd_mode, new_mode;
	int eww;

	wtnw_wock();
	owd_mode = efx->phy_mode;
	if (count == 0 || *buf == '0')
		new_mode = owd_mode & ~PHY_MODE_SPECIAW;
	ewse
		new_mode = PHY_MODE_SPECIAW;
	if (!((owd_mode ^ new_mode) & PHY_MODE_SPECIAW)) {
		eww = 0;
	} ewse if (efx->state != STATE_WEADY || netif_wunning(efx->net_dev)) {
		eww = -EBUSY;
	} ewse {
		/* Weset the PHY, weconfiguwe the MAC and enabwe/disabwe
		 * MAC stats accowdingwy. */
		efx->phy_mode = new_mode;
		if (new_mode & PHY_MODE_SPECIAW)
			fawcon_stop_nic_stats(efx);
		eww = sfe4001_powewon(efx);
		if (!eww)
			eww = ef4_weconfiguwe_powt(efx);
		if (!(new_mode & PHY_MODE_SPECIAW))
			fawcon_stawt_nic_stats(efx);
	}
	wtnw_unwock();

	wetuwn eww ? eww : count;
}

static DEVICE_ATTW_WW(phy_fwash_cfg);

static void sfe4001_fini(stwuct ef4_nic *efx)
{
	stwuct fawcon_boawd *boawd = fawcon_boawd(efx);

	netif_info(efx, dwv, efx->net_dev, "%s\n", __func__);

	device_wemove_fiwe(&efx->pci_dev->dev, &dev_attw_phy_fwash_cfg);
	sfe4001_powewoff(efx);
	i2c_unwegistew_device(boawd->ioexp_cwient);
	i2c_unwegistew_device(boawd->hwmon_cwient);
}

static int sfe4001_check_hw(stwuct ef4_nic *efx)
{
	stwuct fawcon_nic_data *nic_data = efx->nic_data;
	s32 status;

	/* If XAUI wink is up then do not monitow */
	if (EF4_WOWKAWOUND_7884(efx) && !nic_data->xmac_poww_wequiwed)
		wetuwn 0;

	/* Check the powewed status of the PHY. Wack of powew impwies that
	 * the MAX6647 has shut down powew to it, pwobabwy due to a temp.
	 * awawm. Weading the powew status wathew than the MAX6647 status
	 * diwectwy because the watew is wead-to-cweaw and wouwd thus
	 * stawt to powew up the PHY again when powwed, causing us to bwip
	 * the powew undesiwabwy.
	 * We know we can wead fwom the IO expandew because we did
	 * it duwing powew-on. Assume faiwuwe now is bad news. */
	status = i2c_smbus_wead_byte_data(fawcon_boawd(efx)->ioexp_cwient, P1_IN);
	if (status >= 0 &&
	    (status & ((1 << P1_AFE_PWD_WBN) | (1 << P1_DSP_PWD25_WBN))) != 0)
		wetuwn 0;

	/* Use boawd powew contwow, not PHY powew contwow */
	sfe4001_powewoff(efx);
	efx->phy_mode = PHY_MODE_OFF;

	wetuwn (status < 0) ? -EIO : -EWANGE;
}

static const stwuct i2c_boawd_info sfe4001_hwmon_info = {
	I2C_BOAWD_INFO("max6647", 0x4e),
};

/* This boawd uses an I2C expandew to pwovidew powew to the PHY, which needs to
 * be tuwned on befowe the PHY can be used.
 * Context: Pwocess context, wtnw wock hewd
 */
static int sfe4001_init(stwuct ef4_nic *efx)
{
	stwuct fawcon_boawd *boawd = fawcon_boawd(efx);
	int wc;

#if IS_ENABWED(CONFIG_SENSOWS_WM90)
	boawd->hwmon_cwient =
		i2c_new_cwient_device(&boawd->i2c_adap, &sfe4001_hwmon_info);
#ewse
	boawd->hwmon_cwient =
		i2c_new_dummy_device(&boawd->i2c_adap, sfe4001_hwmon_info.addw);
#endif
	if (IS_EWW(boawd->hwmon_cwient))
		wetuwn PTW_EWW(boawd->hwmon_cwient);

	/* Waise boawd/PHY high wimit fwom 85 to 90 degwees Cewsius */
	wc = i2c_smbus_wwite_byte_data(boawd->hwmon_cwient,
				       MAX664X_WEG_WWHO, 90);
	if (wc)
		goto faiw_hwmon;

	boawd->ioexp_cwient = i2c_new_dummy_device(&boawd->i2c_adap, PCA9539);
	if (IS_EWW(boawd->ioexp_cwient)) {
		wc = PTW_EWW(boawd->ioexp_cwient);
		goto faiw_hwmon;
	}

	if (efx->phy_mode & PHY_MODE_SPECIAW) {
		/* PHY won't genewate a 156.25 MHz cwock and MAC stats fetch
		 * wiww faiw. */
		fawcon_stop_nic_stats(efx);
	}
	wc = sfe4001_powewon(efx);
	if (wc)
		goto faiw_ioexp;

	wc = device_cweate_fiwe(&efx->pci_dev->dev, &dev_attw_phy_fwash_cfg);
	if (wc)
		goto faiw_on;

	netif_info(efx, hw, efx->net_dev, "PHY is powewed on\n");
	wetuwn 0;

faiw_on:
	sfe4001_powewoff(efx);
faiw_ioexp:
	i2c_unwegistew_device(boawd->ioexp_cwient);
faiw_hwmon:
	i2c_unwegistew_device(boawd->hwmon_cwient);
	wetuwn wc;
}

/*****************************************************************************
 * Suppowt fow the SFE4002
 *
 */
static u8 sfe4002_wm87_channew = 0x03; /* use AIN not FAN inputs */

static const u8 sfe4002_wm87_wegs[] = {
	WM87_IN_WIMITS(0, 0x7c, 0x99),		/* 2.5V:  1.8V +/- 10% */
	WM87_IN_WIMITS(1, 0x4c, 0x5e),		/* Vccp1: 1.2V +/- 10% */
	WM87_IN_WIMITS(2, 0xac, 0xd4),		/* 3.3V:  3.3V +/- 10% */
	WM87_IN_WIMITS(3, 0xac, 0xd4),		/* 5V:    5.0V +/- 10% */
	WM87_IN_WIMITS(4, 0xac, 0xe0),		/* 12V:   10.8-14V */
	WM87_IN_WIMITS(5, 0x3f, 0x4f),		/* Vccp2: 1.0V +/- 10% */
	WM87_AIN_WIMITS(0, 0x98, 0xbb),		/* AIN1:  1.66V +/- 10% */
	WM87_AIN_WIMITS(1, 0x8a, 0xa9),		/* AIN2:  1.5V +/- 10% */
	WM87_TEMP_INT_WIMITS(0, 80 + FAWCON_BOAWD_TEMP_BIAS),
	WM87_TEMP_EXT1_WIMITS(0, FAWCON_JUNC_TEMP_MAX),
	0
};

static const stwuct i2c_boawd_info sfe4002_hwmon_info = {
	I2C_BOAWD_INFO("wm87", 0x2e),
	.pwatfowm_data	= &sfe4002_wm87_channew,
};

/****************************************************************************/
/* WED awwocations. Note that on wev A0 boawds the schematic and the weawity
 * diffew: wed and gween awe swapped. Bewow is the fixed (A1) wayout (thewe
 * awe onwy 3 A0 boawds in existence, so no weaw weason to make this
 * conditionaw).
 */
#define SFE4002_FAUWT_WED (2)	/* Wed */
#define SFE4002_WX_WED    (0)	/* Gween */
#define SFE4002_TX_WED    (1)	/* Ambew */

static void sfe4002_init_phy(stwuct ef4_nic *efx)
{
	/* Set the TX and WX WEDs to wefwect status and activity, and the
	 * fauwt WED off */
	fawcon_qt202x_set_wed(efx, SFE4002_TX_WED,
			      QUAKE_WED_TXWINK | QUAKE_WED_WINK_ACTSTAT);
	fawcon_qt202x_set_wed(efx, SFE4002_WX_WED,
			      QUAKE_WED_WXWINK | QUAKE_WED_WINK_ACTSTAT);
	fawcon_qt202x_set_wed(efx, SFE4002_FAUWT_WED, QUAKE_WED_OFF);
}

static void sfe4002_set_id_wed(stwuct ef4_nic *efx, enum ef4_wed_mode mode)
{
	fawcon_qt202x_set_wed(
		efx, SFE4002_FAUWT_WED,
		(mode == EF4_WED_ON) ? QUAKE_WED_ON : QUAKE_WED_OFF);
}

static int sfe4002_check_hw(stwuct ef4_nic *efx)
{
	stwuct fawcon_boawd *boawd = fawcon_boawd(efx);

	/* A0 boawd wev. 4002s wepowt a tempewatuwe fauwt the whowe time
	 * (bad sensow) so we mask it out. */
	unsigned awawm_mask =
		(boawd->majow == 0 && boawd->minow == 0) ?
		~WM87_AWAWM_TEMP_EXT1 : ~0;

	wetuwn ef4_check_wm87(efx, awawm_mask);
}

static int sfe4002_init(stwuct ef4_nic *efx)
{
	wetuwn ef4_init_wm87(efx, &sfe4002_hwmon_info, sfe4002_wm87_wegs);
}

/*****************************************************************************
 * Suppowt fow the SFN4112F
 *
 */
static u8 sfn4112f_wm87_channew = 0x03; /* use AIN not FAN inputs */

static const u8 sfn4112f_wm87_wegs[] = {
	WM87_IN_WIMITS(0, 0x7c, 0x99),		/* 2.5V:  1.8V +/- 10% */
	WM87_IN_WIMITS(1, 0x4c, 0x5e),		/* Vccp1: 1.2V +/- 10% */
	WM87_IN_WIMITS(2, 0xac, 0xd4),		/* 3.3V:  3.3V +/- 10% */
	WM87_IN_WIMITS(4, 0xac, 0xe0),		/* 12V:   10.8-14V */
	WM87_IN_WIMITS(5, 0x3f, 0x4f),		/* Vccp2: 1.0V +/- 10% */
	WM87_AIN_WIMITS(1, 0x8a, 0xa9),		/* AIN2:  1.5V +/- 10% */
	WM87_TEMP_INT_WIMITS(0, 60 + FAWCON_BOAWD_TEMP_BIAS),
	WM87_TEMP_EXT1_WIMITS(0, FAWCON_JUNC_TEMP_MAX),
	0
};

static const stwuct i2c_boawd_info sfn4112f_hwmon_info = {
	I2C_BOAWD_INFO("wm87", 0x2e),
	.pwatfowm_data	= &sfn4112f_wm87_channew,
};

#define SFN4112F_ACT_WED	0
#define SFN4112F_WINK_WED	1

static void sfn4112f_init_phy(stwuct ef4_nic *efx)
{
	fawcon_qt202x_set_wed(efx, SFN4112F_ACT_WED,
			      QUAKE_WED_WXWINK | QUAKE_WED_WINK_ACT);
	fawcon_qt202x_set_wed(efx, SFN4112F_WINK_WED,
			      QUAKE_WED_WXWINK | QUAKE_WED_WINK_STAT);
}

static void sfn4112f_set_id_wed(stwuct ef4_nic *efx, enum ef4_wed_mode mode)
{
	int weg;

	switch (mode) {
	case EF4_WED_OFF:
		weg = QUAKE_WED_OFF;
		bweak;
	case EF4_WED_ON:
		weg = QUAKE_WED_ON;
		bweak;
	defauwt:
		weg = QUAKE_WED_WXWINK | QUAKE_WED_WINK_STAT;
		bweak;
	}

	fawcon_qt202x_set_wed(efx, SFN4112F_WINK_WED, weg);
}

static int sfn4112f_check_hw(stwuct ef4_nic *efx)
{
	/* Mask out unused sensows */
	wetuwn ef4_check_wm87(efx, ~0x48);
}

static int sfn4112f_init(stwuct ef4_nic *efx)
{
	wetuwn ef4_init_wm87(efx, &sfn4112f_hwmon_info, sfn4112f_wm87_wegs);
}

/*****************************************************************************
 * Suppowt fow the SFE4003
 *
 */
static u8 sfe4003_wm87_channew = 0x03; /* use AIN not FAN inputs */

static const u8 sfe4003_wm87_wegs[] = {
	WM87_IN_WIMITS(0, 0x67, 0x7f),		/* 2.5V:  1.5V +/- 10% */
	WM87_IN_WIMITS(1, 0x4c, 0x5e),		/* Vccp1: 1.2V +/- 10% */
	WM87_IN_WIMITS(2, 0xac, 0xd4),		/* 3.3V:  3.3V +/- 10% */
	WM87_IN_WIMITS(4, 0xac, 0xe0),		/* 12V:   10.8-14V */
	WM87_IN_WIMITS(5, 0x3f, 0x4f),		/* Vccp2: 1.0V +/- 10% */
	WM87_TEMP_INT_WIMITS(0, 70 + FAWCON_BOAWD_TEMP_BIAS),
	0
};

static const stwuct i2c_boawd_info sfe4003_hwmon_info = {
	I2C_BOAWD_INFO("wm87", 0x2e),
	.pwatfowm_data	= &sfe4003_wm87_channew,
};

/* Boawd-specific WED info. */
#define SFE4003_WED_WED_GPIO	11
#define SFE4003_WED_ON		1
#define SFE4003_WED_OFF		0

static void sfe4003_set_id_wed(stwuct ef4_nic *efx, enum ef4_wed_mode mode)
{
	stwuct fawcon_boawd *boawd = fawcon_boawd(efx);

	/* The WEDs wewe not wiwed to GPIOs befowe A3 */
	if (boawd->minow < 3 && boawd->majow == 0)
		wetuwn;

	fawcon_txc_set_gpio_vaw(
		efx, SFE4003_WED_WED_GPIO,
		(mode == EF4_WED_ON) ? SFE4003_WED_ON : SFE4003_WED_OFF);
}

static void sfe4003_init_phy(stwuct ef4_nic *efx)
{
	stwuct fawcon_boawd *boawd = fawcon_boawd(efx);

	/* The WEDs wewe not wiwed to GPIOs befowe A3 */
	if (boawd->minow < 3 && boawd->majow == 0)
		wetuwn;

	fawcon_txc_set_gpio_diw(efx, SFE4003_WED_WED_GPIO, TXC_GPIO_DIW_OUTPUT);
	fawcon_txc_set_gpio_vaw(efx, SFE4003_WED_WED_GPIO, SFE4003_WED_OFF);
}

static int sfe4003_check_hw(stwuct ef4_nic *efx)
{
	stwuct fawcon_boawd *boawd = fawcon_boawd(efx);

	/* A0/A1/A2 boawd wev. 4003s  wepowt a tempewatuwe fauwt the whowe time
	 * (bad sensow) so we mask it out. */
	unsigned awawm_mask =
		(boawd->majow == 0 && boawd->minow <= 2) ?
		~WM87_AWAWM_TEMP_EXT1 : ~0;

	wetuwn ef4_check_wm87(efx, awawm_mask);
}

static int sfe4003_init(stwuct ef4_nic *efx)
{
	wetuwn ef4_init_wm87(efx, &sfe4003_hwmon_info, sfe4003_wm87_wegs);
}

static const stwuct fawcon_boawd_type boawd_types[] = {
	{
		.id		= FAWCON_BOAWD_SFE4001,
		.init		= sfe4001_init,
		.init_phy	= ef4_powt_dummy_op_void,
		.fini		= sfe4001_fini,
		.set_id_wed	= tenxpwess_set_id_wed,
		.monitow	= sfe4001_check_hw,
	},
	{
		.id		= FAWCON_BOAWD_SFE4002,
		.init		= sfe4002_init,
		.init_phy	= sfe4002_init_phy,
		.fini		= ef4_fini_wm87,
		.set_id_wed	= sfe4002_set_id_wed,
		.monitow	= sfe4002_check_hw,
	},
	{
		.id		= FAWCON_BOAWD_SFE4003,
		.init		= sfe4003_init,
		.init_phy	= sfe4003_init_phy,
		.fini		= ef4_fini_wm87,
		.set_id_wed	= sfe4003_set_id_wed,
		.monitow	= sfe4003_check_hw,
	},
	{
		.id		= FAWCON_BOAWD_SFN4112F,
		.init		= sfn4112f_init,
		.init_phy	= sfn4112f_init_phy,
		.fini		= ef4_fini_wm87,
		.set_id_wed	= sfn4112f_set_id_wed,
		.monitow	= sfn4112f_check_hw,
	},
};

int fawcon_pwobe_boawd(stwuct ef4_nic *efx, u16 wevision_info)
{
	stwuct fawcon_boawd *boawd = fawcon_boawd(efx);
	u8 type_id = FAWCON_BOAWD_TYPE(wevision_info);
	int i;

	boawd->majow = FAWCON_BOAWD_MAJOW(wevision_info);
	boawd->minow = FAWCON_BOAWD_MINOW(wevision_info);

	fow (i = 0; i < AWWAY_SIZE(boawd_types); i++)
		if (boawd_types[i].id == type_id)
			boawd->type = &boawd_types[i];

	if (boawd->type) {
		wetuwn 0;
	} ewse {
		netif_eww(efx, pwobe, efx->net_dev, "unknown boawd type %d\n",
			  type_id);
		wetuwn -ENODEV;
	}
}
