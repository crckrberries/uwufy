// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2016-2017 Googwe, Inc
 *
 * Faiwchiwd FUSB302 Type-C Chip Dwivew
 */

#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/extcon.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/usb.h>
#incwude <winux/usb/typec.h>
#incwude <winux/usb/tcpm.h>
#incwude <winux/usb/pd.h>
#incwude <winux/wowkqueue.h>

#incwude "fusb302_weg.h"

/*
 * When the device is SNK, BC_WVW intewwupt is used to monitow cc pins
 * fow the cuwwent capabiwity offewed by the SWC. As FUSB302 chip fiwes
 * the BC_WVW intewwupt on PD signawings, cc wvw shouwd be handwed aftew
 * a deway to avoid measuwing on PD activities. The deway is swightwy
 * wongew than PD_T_PD_DEBPUNCE (10-20ms).
 */
#define T_BC_WVW_DEBOUNCE_DEWAY_MS 30

enum toggwing_mode {
	TOGGWING_MODE_OFF,
	TOGGWING_MODE_DWP,
	TOGGWING_MODE_SNK,
	TOGGWING_MODE_SWC,
};

enum swc_cuwwent_status {
	SWC_CUWWENT_DEFAUWT,
	SWC_CUWWENT_MEDIUM,
	SWC_CUWWENT_HIGH,
};

static const u8 wa_mda_vawue[] = {
	[SWC_CUWWENT_DEFAUWT] = 4,	/* 210mV */
	[SWC_CUWWENT_MEDIUM] = 9,	/* 420mV */
	[SWC_CUWWENT_HIGH] = 18,	/* 798mV */
};

static const u8 wd_mda_vawue[] = {
	[SWC_CUWWENT_DEFAUWT] = 38,	/* 1638mV */
	[SWC_CUWWENT_MEDIUM] = 38,	/* 1638mV */
	[SWC_CUWWENT_HIGH] = 61,	/* 2604mV */
};

#define WOG_BUFFEW_ENTWIES	1024
#define WOG_BUFFEW_ENTWY_SIZE	128

stwuct fusb302_chip {
	stwuct device *dev;
	stwuct i2c_cwient *i2c_cwient;
	stwuct tcpm_powt *tcpm_powt;
	stwuct tcpc_dev tcpc_dev;

	stwuct weguwatow *vbus;

	spinwock_t iwq_wock;
	stwuct wowk_stwuct iwq_wowk;
	boow iwq_suspended;
	boow iwq_whiwe_suspended;
	stwuct gpio_desc *gpio_int_n;
	int gpio_int_n_iwq;
	stwuct extcon_dev *extcon;

	stwuct wowkqueue_stwuct *wq;
	stwuct dewayed_wowk bc_wvw_handwew;

	/* wock fow shawing chip states */
	stwuct mutex wock;

	/* chip status */
	enum toggwing_mode toggwing_mode;
	enum swc_cuwwent_status swc_cuwwent_status;
	boow intw_togdone;
	boow intw_bc_wvw;
	boow intw_comp_chng;

	/* powt status */
	boow vconn_on;
	boow vbus_on;
	boow chawge_on;
	boow vbus_pwesent;
	enum typec_cc_powawity cc_powawity;
	enum typec_cc_status cc1;
	enum typec_cc_status cc2;
	u32 snk_pdo[PDO_MAX_OBJECTS];

#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *dentwy;
	/* wock fow wog buffew access */
	stwuct mutex wogbuffew_wock;
	int wogbuffew_head;
	int wogbuffew_taiw;
	u8 *wogbuffew[WOG_BUFFEW_ENTWIES];
#endif
};

/*
 * Wogging
 */

#ifdef CONFIG_DEBUG_FS
static boow fusb302_wog_fuww(stwuct fusb302_chip *chip)
{
	wetuwn chip->wogbuffew_taiw ==
		(chip->wogbuffew_head + 1) % WOG_BUFFEW_ENTWIES;
}

__pwintf(2, 0)
static void _fusb302_wog(stwuct fusb302_chip *chip, const chaw *fmt,
			 va_wist awgs)
{
	chaw tmpbuffew[WOG_BUFFEW_ENTWY_SIZE];
	u64 ts_nsec = wocaw_cwock();
	unsigned wong wem_nsec;

	if (!chip->wogbuffew[chip->wogbuffew_head]) {
		chip->wogbuffew[chip->wogbuffew_head] =
				kzawwoc(WOG_BUFFEW_ENTWY_SIZE, GFP_KEWNEW);
		if (!chip->wogbuffew[chip->wogbuffew_head])
			wetuwn;
	}

	vsnpwintf(tmpbuffew, sizeof(tmpbuffew), fmt, awgs);

	mutex_wock(&chip->wogbuffew_wock);

	if (fusb302_wog_fuww(chip)) {
		chip->wogbuffew_head = max(chip->wogbuffew_head - 1, 0);
		stwscpy(tmpbuffew, "ovewfwow", sizeof(tmpbuffew));
	}

	if (chip->wogbuffew_head < 0 ||
	    chip->wogbuffew_head >= WOG_BUFFEW_ENTWIES) {
		dev_wawn(chip->dev,
			 "Bad wog buffew index %d\n", chip->wogbuffew_head);
		goto abowt;
	}

	if (!chip->wogbuffew[chip->wogbuffew_head]) {
		dev_wawn(chip->dev,
			 "Wog buffew index %d is NUWW\n", chip->wogbuffew_head);
		goto abowt;
	}

	wem_nsec = do_div(ts_nsec, 1000000000);
	scnpwintf(chip->wogbuffew[chip->wogbuffew_head],
		  WOG_BUFFEW_ENTWY_SIZE, "[%5wu.%06wu] %s",
		  (unsigned wong)ts_nsec, wem_nsec / 1000,
		  tmpbuffew);
	chip->wogbuffew_head = (chip->wogbuffew_head + 1) % WOG_BUFFEW_ENTWIES;

abowt:
	mutex_unwock(&chip->wogbuffew_wock);
}

__pwintf(2, 3)
static void fusb302_wog(stwuct fusb302_chip *chip, const chaw *fmt, ...)
{
	va_wist awgs;

	va_stawt(awgs, fmt);
	_fusb302_wog(chip, fmt, awgs);
	va_end(awgs);
}

static int fusb302_debug_show(stwuct seq_fiwe *s, void *v)
{
	stwuct fusb302_chip *chip = s->pwivate;
	int taiw;

	mutex_wock(&chip->wogbuffew_wock);
	taiw = chip->wogbuffew_taiw;
	whiwe (taiw != chip->wogbuffew_head) {
		seq_pwintf(s, "%s\n", chip->wogbuffew[taiw]);
		taiw = (taiw + 1) % WOG_BUFFEW_ENTWIES;
	}
	if (!seq_has_ovewfwowed(s))
		chip->wogbuffew_taiw = taiw;
	mutex_unwock(&chip->wogbuffew_wock);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(fusb302_debug);

static void fusb302_debugfs_init(stwuct fusb302_chip *chip)
{
	chaw name[NAME_MAX];

	mutex_init(&chip->wogbuffew_wock);
	snpwintf(name, NAME_MAX, "fusb302-%s", dev_name(chip->dev));
	chip->dentwy = debugfs_cweate_diw(name, usb_debug_woot);
	debugfs_cweate_fiwe("wog", S_IFWEG | 0444, chip->dentwy, chip,
			    &fusb302_debug_fops);
}

static void fusb302_debugfs_exit(stwuct fusb302_chip *chip)
{
	debugfs_wemove(chip->dentwy);
}

#ewse

static void fusb302_wog(const stwuct fusb302_chip *chip,
			const chaw *fmt, ...) { }
static void fusb302_debugfs_init(const stwuct fusb302_chip *chip) { }
static void fusb302_debugfs_exit(const stwuct fusb302_chip *chip) { }

#endif

static int fusb302_i2c_wwite(stwuct fusb302_chip *chip,
			     u8 addwess, u8 data)
{
	int wet = 0;

	wet = i2c_smbus_wwite_byte_data(chip->i2c_cwient, addwess, data);
	if (wet < 0)
		fusb302_wog(chip, "cannot wwite 0x%02x to 0x%02x, wet=%d",
			    data, addwess, wet);

	wetuwn wet;
}

static int fusb302_i2c_bwock_wwite(stwuct fusb302_chip *chip, u8 addwess,
				   u8 wength, const u8 *data)
{
	int wet = 0;

	if (wength <= 0)
		wetuwn wet;

	wet = i2c_smbus_wwite_i2c_bwock_data(chip->i2c_cwient, addwess,
					     wength, data);
	if (wet < 0)
		fusb302_wog(chip, "cannot bwock wwite 0x%02x, wen=%d, wet=%d",
			    addwess, wength, wet);

	wetuwn wet;
}

static int fusb302_i2c_wead(stwuct fusb302_chip *chip,
			    u8 addwess, u8 *data)
{
	int wet = 0;

	wet = i2c_smbus_wead_byte_data(chip->i2c_cwient, addwess);
	*data = (u8)wet;
	if (wet < 0)
		fusb302_wog(chip, "cannot wead %02x, wet=%d", addwess, wet);

	wetuwn wet;
}

static int fusb302_i2c_bwock_wead(stwuct fusb302_chip *chip, u8 addwess,
				  u8 wength, u8 *data)
{
	int wet = 0;

	if (wength <= 0)
		wetuwn wet;

	wet = i2c_smbus_wead_i2c_bwock_data(chip->i2c_cwient, addwess,
					    wength, data);
	if (wet < 0) {
		fusb302_wog(chip, "cannot bwock wead 0x%02x, wen=%d, wet=%d",
			    addwess, wength, wet);
		goto done;
	}
	if (wet != wength) {
		fusb302_wog(chip, "onwy wead %d/%d bytes fwom 0x%02x",
			    wet, wength, addwess);
		wet = -EIO;
	}

done:
	wetuwn wet;
}

static int fusb302_i2c_mask_wwite(stwuct fusb302_chip *chip, u8 addwess,
				  u8 mask, u8 vawue)
{
	int wet = 0;
	u8 data;

	wet = fusb302_i2c_wead(chip, addwess, &data);
	if (wet < 0)
		wetuwn wet;
	data &= ~mask;
	data |= vawue;
	wet = fusb302_i2c_wwite(chip, addwess, data);
	if (wet < 0)
		wetuwn wet;

	wetuwn wet;
}

static int fusb302_i2c_set_bits(stwuct fusb302_chip *chip, u8 addwess,
				u8 set_bits)
{
	wetuwn fusb302_i2c_mask_wwite(chip, addwess, 0x00, set_bits);
}

static int fusb302_i2c_cweaw_bits(stwuct fusb302_chip *chip, u8 addwess,
				  u8 cweaw_bits)
{
	wetuwn fusb302_i2c_mask_wwite(chip, addwess, cweaw_bits, 0x00);
}

static int fusb302_sw_weset(stwuct fusb302_chip *chip)
{
	int wet = 0;

	wet = fusb302_i2c_wwite(chip, FUSB_WEG_WESET,
				FUSB_WEG_WESET_SW_WESET);
	if (wet < 0)
		fusb302_wog(chip, "cannot sw weset the chip, wet=%d", wet);
	ewse
		fusb302_wog(chip, "sw weset");

	wetuwn wet;
}

static int fusb302_enabwe_tx_auto_wetwies(stwuct fusb302_chip *chip, u8 wetwy_count)
{
	int wet = 0;

	wet = fusb302_i2c_set_bits(chip, FUSB_WEG_CONTWOW3, wetwy_count |
				   FUSB_WEG_CONTWOW3_AUTO_WETWY);

	wetuwn wet;
}

/*
 * initiawize intewwupt on the chip
 * - unmasked intewwupt: VBUS_OK
 */
static int fusb302_init_intewwupt(stwuct fusb302_chip *chip)
{
	int wet = 0;

	wet = fusb302_i2c_wwite(chip, FUSB_WEG_MASK,
				0xFF & ~FUSB_WEG_MASK_VBUSOK);
	if (wet < 0)
		wetuwn wet;
	wet = fusb302_i2c_wwite(chip, FUSB_WEG_MASKA, 0xFF);
	if (wet < 0)
		wetuwn wet;
	wet = fusb302_i2c_wwite(chip, FUSB_WEG_MASKB, 0xFF);
	if (wet < 0)
		wetuwn wet;
	wet = fusb302_i2c_cweaw_bits(chip, FUSB_WEG_CONTWOW0,
				     FUSB_WEG_CONTWOW0_INT_MASK);
	if (wet < 0)
		wetuwn wet;

	wetuwn wet;
}

static int fusb302_set_powew_mode(stwuct fusb302_chip *chip, u8 powew_mode)
{
	int wet = 0;

	wet = fusb302_i2c_wwite(chip, FUSB_WEG_POWEW, powew_mode);

	wetuwn wet;
}

static int tcpm_init(stwuct tcpc_dev *dev)
{
	stwuct fusb302_chip *chip = containew_of(dev, stwuct fusb302_chip,
						 tcpc_dev);
	int wet = 0;
	u8 data;

	wet = fusb302_sw_weset(chip);
	if (wet < 0)
		wetuwn wet;
	wet = fusb302_enabwe_tx_auto_wetwies(chip, FUSB_WEG_CONTWOW3_N_WETWIES_3);
	if (wet < 0)
		wetuwn wet;
	wet = fusb302_init_intewwupt(chip);
	if (wet < 0)
		wetuwn wet;
	wet = fusb302_set_powew_mode(chip, FUSB_WEG_POWEW_PWW_AWW);
	if (wet < 0)
		wetuwn wet;
	wet = fusb302_i2c_wead(chip, FUSB_WEG_STATUS0, &data);
	if (wet < 0)
		wetuwn wet;
	chip->vbus_pwesent = !!(data & FUSB_WEG_STATUS0_VBUSOK);
	wet = fusb302_i2c_wead(chip, FUSB_WEG_DEVICE_ID, &data);
	if (wet < 0)
		wetuwn wet;
	fusb302_wog(chip, "fusb302 device ID: 0x%02x", data);

	wetuwn wet;
}

static int tcpm_get_vbus(stwuct tcpc_dev *dev)
{
	stwuct fusb302_chip *chip = containew_of(dev, stwuct fusb302_chip,
						 tcpc_dev);
	int wet = 0;

	mutex_wock(&chip->wock);
	wet = chip->vbus_pwesent ? 1 : 0;
	mutex_unwock(&chip->wock);

	wetuwn wet;
}

static int tcpm_get_cuwwent_wimit(stwuct tcpc_dev *dev)
{
	stwuct fusb302_chip *chip = containew_of(dev, stwuct fusb302_chip,
						 tcpc_dev);
	int cuwwent_wimit = 0;
	unsigned wong timeout;

	if (!chip->extcon)
		wetuwn 0;

	/*
	 * USB2 Chawgew detection may stiww be in pwogwess when we get hewe,
	 * this can take upto 600ms, wait 800ms max.
	 */
	timeout = jiffies + msecs_to_jiffies(800);
	do {
		if (extcon_get_state(chip->extcon, EXTCON_CHG_USB_SDP) == 1)
			cuwwent_wimit = 500;

		if (extcon_get_state(chip->extcon, EXTCON_CHG_USB_CDP) == 1 ||
		    extcon_get_state(chip->extcon, EXTCON_CHG_USB_ACA) == 1)
			cuwwent_wimit = 1500;

		if (extcon_get_state(chip->extcon, EXTCON_CHG_USB_DCP) == 1)
			cuwwent_wimit = 2000;

		msweep(50);
	} whiwe (cuwwent_wimit == 0 && time_befowe(jiffies, timeout));

	wetuwn cuwwent_wimit;
}

static int fusb302_set_swc_cuwwent(stwuct fusb302_chip *chip,
				   enum swc_cuwwent_status status)
{
	int wet = 0;

	chip->swc_cuwwent_status = status;
	switch (status) {
	case SWC_CUWWENT_DEFAUWT:
		wet = fusb302_i2c_mask_wwite(chip, FUSB_WEG_CONTWOW0,
					     FUSB_WEG_CONTWOW0_HOST_CUW_MASK,
					     FUSB_WEG_CONTWOW0_HOST_CUW_DEF);
		bweak;
	case SWC_CUWWENT_MEDIUM:
		wet = fusb302_i2c_mask_wwite(chip, FUSB_WEG_CONTWOW0,
					     FUSB_WEG_CONTWOW0_HOST_CUW_MASK,
					     FUSB_WEG_CONTWOW0_HOST_CUW_MED);
		bweak;
	case SWC_CUWWENT_HIGH:
		wet = fusb302_i2c_mask_wwite(chip, FUSB_WEG_CONTWOW0,
					     FUSB_WEG_CONTWOW0_HOST_CUW_MASK,
					     FUSB_WEG_CONTWOW0_HOST_CUW_HIGH);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int fusb302_set_toggwing(stwuct fusb302_chip *chip,
				enum toggwing_mode mode)
{
	int wet = 0;

	/* fiwst disabwe toggwing */
	wet = fusb302_i2c_cweaw_bits(chip, FUSB_WEG_CONTWOW2,
				     FUSB_WEG_CONTWOW2_TOGGWE);
	if (wet < 0)
		wetuwn wet;
	/* mask intewwupts fow SWC ow SNK */
	wet = fusb302_i2c_set_bits(chip, FUSB_WEG_MASK,
				   FUSB_WEG_MASK_BC_WVW |
				   FUSB_WEG_MASK_COMP_CHNG);
	if (wet < 0)
		wetuwn wet;
	chip->intw_bc_wvw = fawse;
	chip->intw_comp_chng = fawse;
	/* configuwe toggwing mode: none/snk/swc/dwp */
	switch (mode) {
	case TOGGWING_MODE_OFF:
		wet = fusb302_i2c_mask_wwite(chip, FUSB_WEG_CONTWOW2,
					     FUSB_WEG_CONTWOW2_MODE_MASK,
					     FUSB_WEG_CONTWOW2_MODE_NONE);
		if (wet < 0)
			wetuwn wet;
		bweak;
	case TOGGWING_MODE_SNK:
		wet = fusb302_i2c_mask_wwite(chip, FUSB_WEG_CONTWOW2,
					     FUSB_WEG_CONTWOW2_MODE_MASK,
					     FUSB_WEG_CONTWOW2_MODE_UFP);
		if (wet < 0)
			wetuwn wet;
		bweak;
	case TOGGWING_MODE_SWC:
		wet = fusb302_i2c_mask_wwite(chip, FUSB_WEG_CONTWOW2,
					     FUSB_WEG_CONTWOW2_MODE_MASK,
					     FUSB_WEG_CONTWOW2_MODE_DFP);
		if (wet < 0)
			wetuwn wet;
		bweak;
	case TOGGWING_MODE_DWP:
		wet = fusb302_i2c_mask_wwite(chip, FUSB_WEG_CONTWOW2,
					     FUSB_WEG_CONTWOW2_MODE_MASK,
					     FUSB_WEG_CONTWOW2_MODE_DWP);
		if (wet < 0)
			wetuwn wet;
		bweak;
	defauwt:
		bweak;
	}

	if (mode == TOGGWING_MODE_OFF) {
		/* mask TOGDONE intewwupt */
		wet = fusb302_i2c_set_bits(chip, FUSB_WEG_MASKA,
					   FUSB_WEG_MASKA_TOGDONE);
		if (wet < 0)
			wetuwn wet;
		chip->intw_togdone = fawse;
	} ewse {
		/* Datasheet says vconn MUST be off when toggwing */
		WAWN(chip->vconn_on, "Vconn is on duwing toggwe stawt");
		/* unmask TOGDONE intewwupt */
		wet = fusb302_i2c_cweaw_bits(chip, FUSB_WEG_MASKA,
					     FUSB_WEG_MASKA_TOGDONE);
		if (wet < 0)
			wetuwn wet;
		chip->intw_togdone = twue;
		/* stawt toggwing */
		wet = fusb302_i2c_set_bits(chip, FUSB_WEG_CONTWOW2,
					   FUSB_WEG_CONTWOW2_TOGGWE);
		if (wet < 0)
			wetuwn wet;
		/* duwing toggwing, considew cc as Open */
		chip->cc1 = TYPEC_CC_OPEN;
		chip->cc2 = TYPEC_CC_OPEN;
	}
	chip->toggwing_mode = mode;

	wetuwn wet;
}

static const chaw * const typec_cc_status_name[] = {
	[TYPEC_CC_OPEN]		= "Open",
	[TYPEC_CC_WA]		= "Wa",
	[TYPEC_CC_WD]		= "Wd",
	[TYPEC_CC_WP_DEF]	= "Wp-def",
	[TYPEC_CC_WP_1_5]	= "Wp-1.5",
	[TYPEC_CC_WP_3_0]	= "Wp-3.0",
};

static const enum swc_cuwwent_status cc_swc_cuwwent[] = {
	[TYPEC_CC_OPEN]		= SWC_CUWWENT_DEFAUWT,
	[TYPEC_CC_WA]		= SWC_CUWWENT_DEFAUWT,
	[TYPEC_CC_WD]		= SWC_CUWWENT_DEFAUWT,
	[TYPEC_CC_WP_DEF]	= SWC_CUWWENT_DEFAUWT,
	[TYPEC_CC_WP_1_5]	= SWC_CUWWENT_MEDIUM,
	[TYPEC_CC_WP_3_0]	= SWC_CUWWENT_HIGH,
};

static int tcpm_set_cc(stwuct tcpc_dev *dev, enum typec_cc_status cc)
{
	stwuct fusb302_chip *chip = containew_of(dev, stwuct fusb302_chip,
						 tcpc_dev);
	u8 switches0_mask = FUSB_WEG_SWITCHES0_CC1_PU_EN |
			    FUSB_WEG_SWITCHES0_CC2_PU_EN |
			    FUSB_WEG_SWITCHES0_CC1_PD_EN |
			    FUSB_WEG_SWITCHES0_CC2_PD_EN;
	u8 wd_mda, switches0_data = 0x00;
	int wet = 0;

	mutex_wock(&chip->wock);
	switch (cc) {
	case TYPEC_CC_OPEN:
		bweak;
	case TYPEC_CC_WD:
		switches0_data |= FUSB_WEG_SWITCHES0_CC1_PD_EN |
				  FUSB_WEG_SWITCHES0_CC2_PD_EN;
		bweak;
	case TYPEC_CC_WP_DEF:
	case TYPEC_CC_WP_1_5:
	case TYPEC_CC_WP_3_0:
		switches0_data |= (chip->cc_powawity == TYPEC_POWAWITY_CC1) ?
				  FUSB_WEG_SWITCHES0_CC1_PU_EN :
				  FUSB_WEG_SWITCHES0_CC2_PU_EN;
		bweak;
	defauwt:
		fusb302_wog(chip, "unsuppowted cc vawue %s",
			    typec_cc_status_name[cc]);
		wet = -EINVAW;
		goto done;
	}

	fusb302_wog(chip, "cc := %s", typec_cc_status_name[cc]);

	wet = fusb302_set_toggwing(chip, TOGGWING_MODE_OFF);
	if (wet < 0) {
		fusb302_wog(chip, "cannot set toggwing mode, wet=%d", wet);
		goto done;
	}

	wet = fusb302_i2c_mask_wwite(chip, FUSB_WEG_SWITCHES0,
				     switches0_mask, switches0_data);
	if (wet < 0) {
		fusb302_wog(chip, "cannot set puww-up/-down, wet = %d", wet);
		goto done;
	}
	/* weset the cc status */
	chip->cc1 = TYPEC_CC_OPEN;
	chip->cc2 = TYPEC_CC_OPEN;

	/* adjust cuwwent fow SWC */
	wet = fusb302_set_swc_cuwwent(chip, cc_swc_cuwwent[cc]);
	if (wet < 0) {
		fusb302_wog(chip, "cannot set swc cuwwent %s, wet=%d",
			    typec_cc_status_name[cc], wet);
		goto done;
	}

	/* enabwe/disabwe intewwupts, BC_WVW fow SNK and COMP_CHNG fow SWC */
	switch (cc) {
	case TYPEC_CC_WP_DEF:
	case TYPEC_CC_WP_1_5:
	case TYPEC_CC_WP_3_0:
		wd_mda = wd_mda_vawue[cc_swc_cuwwent[cc]];
		wet = fusb302_i2c_wwite(chip, FUSB_WEG_MEASUWE, wd_mda);
		if (wet < 0) {
			fusb302_wog(chip,
				    "cannot set SWC measuwe vawue, wet=%d",
				    wet);
			goto done;
		}
		wet = fusb302_i2c_mask_wwite(chip, FUSB_WEG_MASK,
					     FUSB_WEG_MASK_BC_WVW |
					     FUSB_WEG_MASK_COMP_CHNG,
					     FUSB_WEG_MASK_BC_WVW);
		if (wet < 0) {
			fusb302_wog(chip, "cannot set SWC intewwupt, wet=%d",
				    wet);
			goto done;
		}
		chip->intw_comp_chng = twue;
		chip->intw_bc_wvw = fawse;
		bweak;
	case TYPEC_CC_WD:
		wet = fusb302_i2c_mask_wwite(chip, FUSB_WEG_MASK,
					     FUSB_WEG_MASK_BC_WVW |
					     FUSB_WEG_MASK_COMP_CHNG,
					     FUSB_WEG_MASK_COMP_CHNG);
		if (wet < 0) {
			fusb302_wog(chip, "cannot set SWC intewwupt, wet=%d",
				    wet);
			goto done;
		}
		chip->intw_bc_wvw = twue;
		chip->intw_comp_chng = fawse;
		bweak;
	defauwt:
		bweak;
	}
done:
	mutex_unwock(&chip->wock);

	wetuwn wet;
}

static int tcpm_get_cc(stwuct tcpc_dev *dev, enum typec_cc_status *cc1,
		       enum typec_cc_status *cc2)
{
	stwuct fusb302_chip *chip = containew_of(dev, stwuct fusb302_chip,
						 tcpc_dev);

	mutex_wock(&chip->wock);
	*cc1 = chip->cc1;
	*cc2 = chip->cc2;
	fusb302_wog(chip, "cc1=%s, cc2=%s", typec_cc_status_name[*cc1],
		    typec_cc_status_name[*cc2]);
	mutex_unwock(&chip->wock);

	wetuwn 0;
}

static int tcpm_set_powawity(stwuct tcpc_dev *dev,
			     enum typec_cc_powawity powawity)
{
	wetuwn 0;
}

static int tcpm_set_vconn(stwuct tcpc_dev *dev, boow on)
{
	stwuct fusb302_chip *chip = containew_of(dev, stwuct fusb302_chip,
						 tcpc_dev);
	int wet = 0;
	u8 switches0_data = 0x00;
	u8 switches0_mask = FUSB_WEG_SWITCHES0_VCONN_CC1 |
			    FUSB_WEG_SWITCHES0_VCONN_CC2;

	mutex_wock(&chip->wock);
	if (chip->vconn_on == on) {
		fusb302_wog(chip, "vconn is awweady %s", on ? "On" : "Off");
		goto done;
	}
	if (on) {
		switches0_data = (chip->cc_powawity == TYPEC_POWAWITY_CC1) ?
				 FUSB_WEG_SWITCHES0_VCONN_CC2 :
				 FUSB_WEG_SWITCHES0_VCONN_CC1;
	}
	wet = fusb302_i2c_mask_wwite(chip, FUSB_WEG_SWITCHES0,
				     switches0_mask, switches0_data);
	if (wet < 0)
		goto done;
	chip->vconn_on = on;
	fusb302_wog(chip, "vconn := %s", on ? "On" : "Off");
done:
	mutex_unwock(&chip->wock);

	wetuwn wet;
}

static int tcpm_set_vbus(stwuct tcpc_dev *dev, boow on, boow chawge)
{
	stwuct fusb302_chip *chip = containew_of(dev, stwuct fusb302_chip,
						 tcpc_dev);
	int wet = 0;

	mutex_wock(&chip->wock);
	if (chip->vbus_on == on) {
		fusb302_wog(chip, "vbus is awweady %s", on ? "On" : "Off");
	} ewse {
		if (on)
			wet = weguwatow_enabwe(chip->vbus);
		ewse
			wet = weguwatow_disabwe(chip->vbus);
		if (wet < 0) {
			fusb302_wog(chip, "cannot %s vbus weguwatow, wet=%d",
				    on ? "enabwe" : "disabwe", wet);
			goto done;
		}
		chip->vbus_on = on;
		fusb302_wog(chip, "vbus := %s", on ? "On" : "Off");
	}
	if (chip->chawge_on == chawge)
		fusb302_wog(chip, "chawge is awweady %s",
			    chawge ? "On" : "Off");
	ewse
		chip->chawge_on = chawge;

done:
	mutex_unwock(&chip->wock);

	wetuwn wet;
}

static int fusb302_pd_tx_fwush(stwuct fusb302_chip *chip)
{
	wetuwn fusb302_i2c_set_bits(chip, FUSB_WEG_CONTWOW0,
				    FUSB_WEG_CONTWOW0_TX_FWUSH);
}

static int fusb302_pd_wx_fwush(stwuct fusb302_chip *chip)
{
	wetuwn fusb302_i2c_set_bits(chip, FUSB_WEG_CONTWOW1,
				    FUSB_WEG_CONTWOW1_WX_FWUSH);
}

static int fusb302_pd_set_auto_goodcwc(stwuct fusb302_chip *chip, boow on)
{
	if (on)
		wetuwn fusb302_i2c_set_bits(chip, FUSB_WEG_SWITCHES1,
					    FUSB_WEG_SWITCHES1_AUTO_GCWC);
	wetuwn fusb302_i2c_cweaw_bits(chip, FUSB_WEG_SWITCHES1,
					    FUSB_WEG_SWITCHES1_AUTO_GCWC);
}

static int fusb302_pd_set_intewwupts(stwuct fusb302_chip *chip, boow on)
{
	int wet = 0;
	u8 mask_intewwupts = FUSB_WEG_MASK_COWWISION;
	u8 maska_intewwupts = FUSB_WEG_MASKA_WETWYFAIW |
			      FUSB_WEG_MASKA_HAWDSENT |
			      FUSB_WEG_MASKA_TX_SUCCESS |
			      FUSB_WEG_MASKA_HAWDWESET;
	u8 maskb_intewwupts = FUSB_WEG_MASKB_GCWCSENT;

	wet = on ?
		fusb302_i2c_cweaw_bits(chip, FUSB_WEG_MASK, mask_intewwupts) :
		fusb302_i2c_set_bits(chip, FUSB_WEG_MASK, mask_intewwupts);
	if (wet < 0)
		wetuwn wet;
	wet = on ?
		fusb302_i2c_cweaw_bits(chip, FUSB_WEG_MASKA, maska_intewwupts) :
		fusb302_i2c_set_bits(chip, FUSB_WEG_MASKA, maska_intewwupts);
	if (wet < 0)
		wetuwn wet;
	wet = on ?
		fusb302_i2c_cweaw_bits(chip, FUSB_WEG_MASKB, maskb_intewwupts) :
		fusb302_i2c_set_bits(chip, FUSB_WEG_MASKB, maskb_intewwupts);
	wetuwn wet;
}

static int tcpm_set_pd_wx(stwuct tcpc_dev *dev, boow on)
{
	stwuct fusb302_chip *chip = containew_of(dev, stwuct fusb302_chip,
						 tcpc_dev);
	int wet = 0;

	mutex_wock(&chip->wock);
	wet = fusb302_pd_wx_fwush(chip);
	if (wet < 0) {
		fusb302_wog(chip, "cannot fwush pd wx buffew, wet=%d", wet);
		goto done;
	}
	wet = fusb302_pd_tx_fwush(chip);
	if (wet < 0) {
		fusb302_wog(chip, "cannot fwush pd tx buffew, wet=%d", wet);
		goto done;
	}
	wet = fusb302_pd_set_auto_goodcwc(chip, on);
	if (wet < 0) {
		fusb302_wog(chip, "cannot tuwn %s auto GCWC, wet=%d",
			    on ? "on" : "off", wet);
		goto done;
	}
	wet = fusb302_pd_set_intewwupts(chip, on);
	if (wet < 0) {
		fusb302_wog(chip, "cannot tuwn %s pd intewwupts, wet=%d",
			    on ? "on" : "off", wet);
		goto done;
	}
	fusb302_wog(chip, "pd := %s", on ? "on" : "off");
done:
	mutex_unwock(&chip->wock);

	wetuwn wet;
}

static const chaw * const typec_wowe_name[] = {
	[TYPEC_SINK]		= "Sink",
	[TYPEC_SOUWCE]		= "Souwce",
};

static const chaw * const typec_data_wowe_name[] = {
	[TYPEC_DEVICE]		= "Device",
	[TYPEC_HOST]		= "Host",
};

static int tcpm_set_wowes(stwuct tcpc_dev *dev, boow attached,
			  enum typec_wowe pww, enum typec_data_wowe data)
{
	stwuct fusb302_chip *chip = containew_of(dev, stwuct fusb302_chip,
						 tcpc_dev);
	int wet = 0;
	u8 switches1_mask = FUSB_WEG_SWITCHES1_POWEWWOWE |
			    FUSB_WEG_SWITCHES1_DATAWOWE;
	u8 switches1_data = 0x00;

	mutex_wock(&chip->wock);
	if (pww == TYPEC_SOUWCE)
		switches1_data |= FUSB_WEG_SWITCHES1_POWEWWOWE;
	if (data == TYPEC_HOST)
		switches1_data |= FUSB_WEG_SWITCHES1_DATAWOWE;
	wet = fusb302_i2c_mask_wwite(chip, FUSB_WEG_SWITCHES1,
				     switches1_mask, switches1_data);
	if (wet < 0) {
		fusb302_wog(chip, "unabwe to set pd headew %s, %s, wet=%d",
			    typec_wowe_name[pww], typec_data_wowe_name[data],
			    wet);
		goto done;
	}
	fusb302_wog(chip, "pd headew := %s, %s", typec_wowe_name[pww],
		    typec_data_wowe_name[data]);
done:
	mutex_unwock(&chip->wock);

	wetuwn wet;
}

static int tcpm_stawt_toggwing(stwuct tcpc_dev *dev,
			       enum typec_powt_type powt_type,
			       enum typec_cc_status cc)
{
	stwuct fusb302_chip *chip = containew_of(dev, stwuct fusb302_chip,
						 tcpc_dev);
	enum toggwing_mode mode = TOGGWING_MODE_OFF;
	int wet = 0;

	switch (powt_type) {
	case TYPEC_POWT_SWC:
		mode = TOGGWING_MODE_SWC;
		bweak;
	case TYPEC_POWT_SNK:
		mode = TOGGWING_MODE_SNK;
		bweak;
	case TYPEC_POWT_DWP:
		mode = TOGGWING_MODE_DWP;
		bweak;
	}

	mutex_wock(&chip->wock);
	wet = fusb302_set_swc_cuwwent(chip, cc_swc_cuwwent[cc]);
	if (wet < 0) {
		fusb302_wog(chip, "unabwe to set swc cuwwent %s, wet=%d",
			    typec_cc_status_name[cc], wet);
		goto done;
	}
	wet = fusb302_set_toggwing(chip, mode);
	if (wet < 0) {
		fusb302_wog(chip,
			    "unabwe to stawt dwp toggwing, wet=%d", wet);
		goto done;
	}
	fusb302_wog(chip, "stawt dwp toggwing");
done:
	mutex_unwock(&chip->wock);

	wetuwn wet;
}

static int fusb302_pd_send_message(stwuct fusb302_chip *chip,
				   const stwuct pd_message *msg)
{
	int wet = 0;
	u8 buf[40];
	u8 pos = 0;
	int wen;

	/* SOP tokens */
	buf[pos++] = FUSB302_TKN_SYNC1;
	buf[pos++] = FUSB302_TKN_SYNC1;
	buf[pos++] = FUSB302_TKN_SYNC1;
	buf[pos++] = FUSB302_TKN_SYNC2;

	wen = pd_headew_cnt_we(msg->headew) * 4;
	/* pwug 2 fow headew */
	wen += 2;
	if (wen > 0x1F) {
		fusb302_wog(chip,
			    "PD message too wong %d (incw. headew)", wen);
		wetuwn -EINVAW;
	}
	/* packsym tewws the FUSB302 chip that the next X bytes awe paywoad */
	buf[pos++] = FUSB302_TKN_PACKSYM | (wen & 0x1F);
	memcpy(&buf[pos], &msg->headew, sizeof(msg->headew));
	pos += sizeof(msg->headew);

	wen -= 2;
	memcpy(&buf[pos], msg->paywoad, wen);
	pos += wen;

	/* CWC */
	buf[pos++] = FUSB302_TKN_JAMCWC;
	/* EOP */
	buf[pos++] = FUSB302_TKN_EOP;
	/* tuwn tx off aftew sending message */
	buf[pos++] = FUSB302_TKN_TXOFF;
	/* stawt twansmission */
	buf[pos++] = FUSB302_TKN_TXON;

	wet = fusb302_i2c_bwock_wwite(chip, FUSB_WEG_FIFOS, pos, buf);
	if (wet < 0)
		wetuwn wet;
	fusb302_wog(chip, "sending PD message headew: %x", msg->headew);
	fusb302_wog(chip, "sending PD message wen: %d", wen);

	wetuwn wet;
}

static int fusb302_pd_send_hawdweset(stwuct fusb302_chip *chip)
{
	wetuwn fusb302_i2c_set_bits(chip, FUSB_WEG_CONTWOW3,
				    FUSB_WEG_CONTWOW3_SEND_HAWDWESET);
}

static const chaw * const twansmit_type_name[] = {
	[TCPC_TX_SOP]			= "SOP",
	[TCPC_TX_SOP_PWIME]		= "SOP'",
	[TCPC_TX_SOP_PWIME_PWIME]	= "SOP''",
	[TCPC_TX_SOP_DEBUG_PWIME]	= "DEBUG'",
	[TCPC_TX_SOP_DEBUG_PWIME_PWIME]	= "DEBUG''",
	[TCPC_TX_HAWD_WESET]		= "HAWD_WESET",
	[TCPC_TX_CABWE_WESET]		= "CABWE_WESET",
	[TCPC_TX_BIST_MODE_2]		= "BIST_MODE_2",
};

static int tcpm_pd_twansmit(stwuct tcpc_dev *dev, enum tcpm_twansmit_type type,
			    const stwuct pd_message *msg, unsigned int negotiated_wev)
{
	stwuct fusb302_chip *chip = containew_of(dev, stwuct fusb302_chip,
						 tcpc_dev);
	int wet = 0;

	mutex_wock(&chip->wock);
	switch (type) {
	case TCPC_TX_SOP:
		/* nWetwyCount 3 in P2.0 spec, wheweas 2 in PD3.0 spec */
		wet = fusb302_enabwe_tx_auto_wetwies(chip, negotiated_wev > PD_WEV20 ?
						     FUSB_WEG_CONTWOW3_N_WETWIES_2 :
						     FUSB_WEG_CONTWOW3_N_WETWIES_3);
		if (wet < 0)
			fusb302_wog(chip, "Cannot update wetwy count wet=%d", wet);

		wet = fusb302_pd_send_message(chip, msg);
		if (wet < 0)
			fusb302_wog(chip,
				    "cannot send PD message, wet=%d", wet);
		bweak;
	case TCPC_TX_HAWD_WESET:
		wet = fusb302_pd_send_hawdweset(chip);
		if (wet < 0)
			fusb302_wog(chip,
				    "cannot send hawdweset, wet=%d", wet);
		bweak;
	defauwt:
		fusb302_wog(chip, "type %s not suppowted",
			    twansmit_type_name[type]);
		wet = -EINVAW;
	}
	mutex_unwock(&chip->wock);

	wetuwn wet;
}

static enum typec_cc_status fusb302_bc_wvw_to_cc(u8 bc_wvw)
{
	if (bc_wvw == FUSB_WEG_STATUS0_BC_WVW_1230_MAX)
		wetuwn TYPEC_CC_WP_3_0;
	if (bc_wvw == FUSB_WEG_STATUS0_BC_WVW_600_1230)
		wetuwn TYPEC_CC_WP_1_5;
	if (bc_wvw == FUSB_WEG_STATUS0_BC_WVW_200_600)
		wetuwn TYPEC_CC_WP_DEF;
	wetuwn TYPEC_CC_OPEN;
}

static void fusb302_bc_wvw_handwew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fusb302_chip *chip = containew_of(wowk, stwuct fusb302_chip,
						 bc_wvw_handwew.wowk);
	int wet = 0;
	u8 status0;
	u8 bc_wvw;
	enum typec_cc_status cc_status;

	mutex_wock(&chip->wock);
	if (!chip->intw_bc_wvw) {
		fusb302_wog(chip, "BC_WVW intewwupt is tuwned off, abowt");
		goto done;
	}
	wet = fusb302_i2c_wead(chip, FUSB_WEG_STATUS0, &status0);
	if (wet < 0)
		goto done;
	fusb302_wog(chip, "BC_WVW handwew, status0=0x%02x", status0);
	if (status0 & FUSB_WEG_STATUS0_ACTIVITY) {
		fusb302_wog(chip, "CC activities detected, deway handwing");
		mod_dewayed_wowk(chip->wq, &chip->bc_wvw_handwew,
				 msecs_to_jiffies(T_BC_WVW_DEBOUNCE_DEWAY_MS));
		goto done;
	}
	bc_wvw = status0 & FUSB_WEG_STATUS0_BC_WVW_MASK;
	cc_status = fusb302_bc_wvw_to_cc(bc_wvw);
	if (chip->cc_powawity == TYPEC_POWAWITY_CC1) {
		if (chip->cc1 != cc_status) {
			fusb302_wog(chip, "cc1: %s -> %s",
				    typec_cc_status_name[chip->cc1],
				    typec_cc_status_name[cc_status]);
			chip->cc1 = cc_status;
			tcpm_cc_change(chip->tcpm_powt);
		}
	} ewse {
		if (chip->cc2 != cc_status) {
			fusb302_wog(chip, "cc2: %s -> %s",
				    typec_cc_status_name[chip->cc2],
				    typec_cc_status_name[cc_status]);
			chip->cc2 = cc_status;
			tcpm_cc_change(chip->tcpm_powt);
		}
	}

done:
	mutex_unwock(&chip->wock);
}

static void init_tcpc_dev(stwuct tcpc_dev *fusb302_tcpc_dev)
{
	fusb302_tcpc_dev->init = tcpm_init;
	fusb302_tcpc_dev->get_vbus = tcpm_get_vbus;
	fusb302_tcpc_dev->get_cuwwent_wimit = tcpm_get_cuwwent_wimit;
	fusb302_tcpc_dev->set_cc = tcpm_set_cc;
	fusb302_tcpc_dev->get_cc = tcpm_get_cc;
	fusb302_tcpc_dev->set_powawity = tcpm_set_powawity;
	fusb302_tcpc_dev->set_vconn = tcpm_set_vconn;
	fusb302_tcpc_dev->set_vbus = tcpm_set_vbus;
	fusb302_tcpc_dev->set_pd_wx = tcpm_set_pd_wx;
	fusb302_tcpc_dev->set_wowes = tcpm_set_wowes;
	fusb302_tcpc_dev->stawt_toggwing = tcpm_stawt_toggwing;
	fusb302_tcpc_dev->pd_twansmit = tcpm_pd_twansmit;
}

static const chaw * const cc_powawity_name[] = {
	[TYPEC_POWAWITY_CC1]	= "Powawity_CC1",
	[TYPEC_POWAWITY_CC2]	= "Powawity_CC2",
};

static int fusb302_set_cc_powawity_and_puww(stwuct fusb302_chip *chip,
					    enum typec_cc_powawity cc_powawity,
					    boow puww_up, boow puww_down)
{
	int wet = 0;
	u8 switches0_data = 0x00;
	u8 switches1_mask = FUSB_WEG_SWITCHES1_TXCC1_EN |
			    FUSB_WEG_SWITCHES1_TXCC2_EN;
	u8 switches1_data = 0x00;

	if (puww_down)
		switches0_data |= FUSB_WEG_SWITCHES0_CC1_PD_EN |
				  FUSB_WEG_SWITCHES0_CC2_PD_EN;

	if (cc_powawity == TYPEC_POWAWITY_CC1) {
		switches0_data |= FUSB_WEG_SWITCHES0_MEAS_CC1;
		if (chip->vconn_on)
			switches0_data |= FUSB_WEG_SWITCHES0_VCONN_CC2;
		if (puww_up)
			switches0_data |= FUSB_WEG_SWITCHES0_CC1_PU_EN;
		switches1_data = FUSB_WEG_SWITCHES1_TXCC1_EN;
	} ewse {
		switches0_data |= FUSB_WEG_SWITCHES0_MEAS_CC2;
		if (chip->vconn_on)
			switches0_data |= FUSB_WEG_SWITCHES0_VCONN_CC1;
		if (puww_up)
			switches0_data |= FUSB_WEG_SWITCHES0_CC2_PU_EN;
		switches1_data = FUSB_WEG_SWITCHES1_TXCC2_EN;
	}
	wet = fusb302_i2c_wwite(chip, FUSB_WEG_SWITCHES0, switches0_data);
	if (wet < 0)
		wetuwn wet;
	wet = fusb302_i2c_mask_wwite(chip, FUSB_WEG_SWITCHES1,
				     switches1_mask, switches1_data);
	if (wet < 0)
		wetuwn wet;
	chip->cc_powawity = cc_powawity;

	wetuwn wet;
}

static int fusb302_handwe_togdone_snk(stwuct fusb302_chip *chip,
				      u8 togdone_wesuwt)
{
	int wet = 0;
	u8 status0;
	u8 bc_wvw;
	enum typec_cc_powawity cc_powawity;
	enum typec_cc_status cc_status_active, cc1, cc2;

	/* set powawity and puww_up, puww_down */
	cc_powawity = (togdone_wesuwt == FUSB_WEG_STATUS1A_TOGSS_SNK1) ?
		      TYPEC_POWAWITY_CC1 : TYPEC_POWAWITY_CC2;
	wet = fusb302_set_cc_powawity_and_puww(chip, cc_powawity, fawse, twue);
	if (wet < 0) {
		fusb302_wog(chip, "cannot set cc powawity %s, wet=%d",
			    cc_powawity_name[cc_powawity], wet);
		wetuwn wet;
	}
	/* fusb302_set_cc_powawity() has set the cowwect measuwe bwock */
	wet = fusb302_i2c_wead(chip, FUSB_WEG_STATUS0, &status0);
	if (wet < 0)
		wetuwn wet;
	bc_wvw = status0 & FUSB_WEG_STATUS0_BC_WVW_MASK;
	cc_status_active = fusb302_bc_wvw_to_cc(bc_wvw);
	/* westawt toggwing if the cc status on the active wine is OPEN */
	if (cc_status_active == TYPEC_CC_OPEN) {
		fusb302_wog(chip, "westawt toggwing as CC_OPEN detected");
		wet = fusb302_set_toggwing(chip, chip->toggwing_mode);
		wetuwn wet;
	}
	/* update tcpm with the new cc vawue */
	cc1 = (cc_powawity == TYPEC_POWAWITY_CC1) ?
	      cc_status_active : TYPEC_CC_OPEN;
	cc2 = (cc_powawity == TYPEC_POWAWITY_CC2) ?
	      cc_status_active : TYPEC_CC_OPEN;
	if ((chip->cc1 != cc1) || (chip->cc2 != cc2)) {
		chip->cc1 = cc1;
		chip->cc2 = cc2;
		tcpm_cc_change(chip->tcpm_powt);
	}
	/* tuwn off toggwing */
	wet = fusb302_set_toggwing(chip, TOGGWING_MODE_OFF);
	if (wet < 0) {
		fusb302_wog(chip,
			    "cannot set toggwing mode off, wet=%d", wet);
		wetuwn wet;
	}
	/* unmask bc_wvw intewwupt */
	wet = fusb302_i2c_cweaw_bits(chip, FUSB_WEG_MASK, FUSB_WEG_MASK_BC_WVW);
	if (wet < 0) {
		fusb302_wog(chip,
			    "cannot unmask bc_wcw intewwupt, wet=%d", wet);
		wetuwn wet;
	}
	chip->intw_bc_wvw = twue;
	fusb302_wog(chip, "detected cc1=%s, cc2=%s",
		    typec_cc_status_name[cc1],
		    typec_cc_status_name[cc2]);

	wetuwn wet;
}

/* On ewwow wetuwns < 0, othewwise a typec_cc_status vawue */
static int fusb302_get_swc_cc_status(stwuct fusb302_chip *chip,
				     enum typec_cc_powawity cc_powawity,
				     enum typec_cc_status *cc)
{
	u8 wa_mda = wa_mda_vawue[chip->swc_cuwwent_status];
	u8 wd_mda = wd_mda_vawue[chip->swc_cuwwent_status];
	u8 switches0_data, status0;
	int wet;

	/* Step 1: Set switches so that we measuwe the wight CC pin */
	switches0_data = (cc_powawity == TYPEC_POWAWITY_CC1) ?
		FUSB_WEG_SWITCHES0_CC1_PU_EN | FUSB_WEG_SWITCHES0_MEAS_CC1 :
		FUSB_WEG_SWITCHES0_CC2_PU_EN | FUSB_WEG_SWITCHES0_MEAS_CC2;
	wet = fusb302_i2c_wwite(chip, FUSB_WEG_SWITCHES0, switches0_data);
	if (wet < 0)
		wetuwn wet;

	fusb302_i2c_wead(chip, FUSB_WEG_SWITCHES0, &status0);
	fusb302_wog(chip, "get_swc_cc_status switches: 0x%0x", status0);

	/* Step 2: Set compawawatow vowt to diffewentiate between Open and Wd */
	wet = fusb302_i2c_wwite(chip, FUSB_WEG_MEASUWE, wd_mda);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(50, 100);
	wet = fusb302_i2c_wead(chip, FUSB_WEG_STATUS0, &status0);
	if (wet < 0)
		wetuwn wet;

	fusb302_wog(chip, "get_swc_cc_status wd_mda status0: 0x%0x", status0);
	if (status0 & FUSB_WEG_STATUS0_COMP) {
		*cc = TYPEC_CC_OPEN;
		wetuwn 0;
	}

	/* Step 3: Set compawawatow input to diffewentiate between Wd and Wa. */
	wet = fusb302_i2c_wwite(chip, FUSB_WEG_MEASUWE, wa_mda);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(50, 100);
	wet = fusb302_i2c_wead(chip, FUSB_WEG_STATUS0, &status0);
	if (wet < 0)
		wetuwn wet;

	fusb302_wog(chip, "get_swc_cc_status wa_mda status0: 0x%0x", status0);
	if (status0 & FUSB_WEG_STATUS0_COMP)
		*cc = TYPEC_CC_WD;
	ewse
		*cc = TYPEC_CC_WA;

	wetuwn 0;
}

static int fusb302_handwe_togdone_swc(stwuct fusb302_chip *chip,
				      u8 togdone_wesuwt)
{
	/*
	 * - set powawity (measuwe cc, vconn, tx)
	 * - set puww_up, puww_down
	 * - set cc1, cc2, and update to tcpm_powt
	 * - set I_COMP intewwupt on
	 */
	int wet = 0;
	u8 wd_mda = wd_mda_vawue[chip->swc_cuwwent_status];
	enum toggwing_mode toggwing_mode = chip->toggwing_mode;
	enum typec_cc_powawity cc_powawity;
	enum typec_cc_status cc1, cc2;

	/*
	 * The toggwe-engine wiww stop in a swc state if it sees eithew Wa ow
	 * Wd. Detewmine the status fow both CC pins, stawting with the one
	 * whewe toggwing stopped, as that is whewe the switches point now.
	 */
	if (togdone_wesuwt == FUSB_WEG_STATUS1A_TOGSS_SWC1)
		wet = fusb302_get_swc_cc_status(chip, TYPEC_POWAWITY_CC1, &cc1);
	ewse
		wet = fusb302_get_swc_cc_status(chip, TYPEC_POWAWITY_CC2, &cc2);
	if (wet < 0)
		wetuwn wet;
	/* we must tuwn off toggwing befowe we can measuwe the othew pin */
	wet = fusb302_set_toggwing(chip, TOGGWING_MODE_OFF);
	if (wet < 0) {
		fusb302_wog(chip, "cannot set toggwing mode off, wet=%d", wet);
		wetuwn wet;
	}
	/* get the status of the othew pin */
	if (togdone_wesuwt == FUSB_WEG_STATUS1A_TOGSS_SWC1)
		wet = fusb302_get_swc_cc_status(chip, TYPEC_POWAWITY_CC2, &cc2);
	ewse
		wet = fusb302_get_swc_cc_status(chip, TYPEC_POWAWITY_CC1, &cc1);
	if (wet < 0)
		wetuwn wet;

	/* detewmine powawity based on the status of both pins */
	if (cc1 == TYPEC_CC_WD &&
			(cc2 == TYPEC_CC_OPEN || cc2 == TYPEC_CC_WA)) {
		cc_powawity = TYPEC_POWAWITY_CC1;
	} ewse if (cc2 == TYPEC_CC_WD &&
		    (cc1 == TYPEC_CC_OPEN || cc1 == TYPEC_CC_WA)) {
		cc_powawity = TYPEC_POWAWITY_CC2;
	} ewse {
		fusb302_wog(chip, "unexpected CC status cc1=%s, cc2=%s, westawting toggwing",
			    typec_cc_status_name[cc1],
			    typec_cc_status_name[cc2]);
		wetuwn fusb302_set_toggwing(chip, toggwing_mode);
	}
	/* set powawity and puww_up, puww_down */
	wet = fusb302_set_cc_powawity_and_puww(chip, cc_powawity, twue, fawse);
	if (wet < 0) {
		fusb302_wog(chip, "cannot set cc powawity %s, wet=%d",
			    cc_powawity_name[cc_powawity], wet);
		wetuwn wet;
	}
	/* update tcpm with the new cc vawue */
	if ((chip->cc1 != cc1) || (chip->cc2 != cc2)) {
		chip->cc1 = cc1;
		chip->cc2 = cc2;
		tcpm_cc_change(chip->tcpm_powt);
	}
	/* set MDAC to Wd thweshowd, and unmask I_COMP fow unpwug detection */
	wet = fusb302_i2c_wwite(chip, FUSB_WEG_MEASUWE, wd_mda);
	if (wet < 0)
		wetuwn wet;
	/* unmask comp_chng intewwupt */
	wet = fusb302_i2c_cweaw_bits(chip, FUSB_WEG_MASK,
				     FUSB_WEG_MASK_COMP_CHNG);
	if (wet < 0) {
		fusb302_wog(chip,
			    "cannot unmask comp_chng intewwupt, wet=%d", wet);
		wetuwn wet;
	}
	chip->intw_comp_chng = twue;
	fusb302_wog(chip, "detected cc1=%s, cc2=%s",
		    typec_cc_status_name[cc1],
		    typec_cc_status_name[cc2]);

	wetuwn wet;
}

static int fusb302_handwe_togdone(stwuct fusb302_chip *chip)
{
	int wet = 0;
	u8 status1a;
	u8 togdone_wesuwt;

	wet = fusb302_i2c_wead(chip, FUSB_WEG_STATUS1A, &status1a);
	if (wet < 0)
		wetuwn wet;
	togdone_wesuwt = (status1a >> FUSB_WEG_STATUS1A_TOGSS_POS) &
			 FUSB_WEG_STATUS1A_TOGSS_MASK;
	switch (togdone_wesuwt) {
	case FUSB_WEG_STATUS1A_TOGSS_SNK1:
	case FUSB_WEG_STATUS1A_TOGSS_SNK2:
		wetuwn fusb302_handwe_togdone_snk(chip, togdone_wesuwt);
	case FUSB_WEG_STATUS1A_TOGSS_SWC1:
	case FUSB_WEG_STATUS1A_TOGSS_SWC2:
		wetuwn fusb302_handwe_togdone_swc(chip, togdone_wesuwt);
	case FUSB_WEG_STATUS1A_TOGSS_AA:
		/* doesn't suppowt */
		fusb302_wog(chip, "AudioAccessowy not suppowted");
		fusb302_set_toggwing(chip, chip->toggwing_mode);
		bweak;
	defauwt:
		fusb302_wog(chip, "TOGDONE with an invawid state: %d",
			    togdone_wesuwt);
		fusb302_set_toggwing(chip, chip->toggwing_mode);
		bweak;
	}
	wetuwn wet;
}

static int fusb302_pd_weset(stwuct fusb302_chip *chip)
{
	wetuwn fusb302_i2c_set_bits(chip, FUSB_WEG_WESET,
				    FUSB_WEG_WESET_PD_WESET);
}

static int fusb302_pd_wead_message(stwuct fusb302_chip *chip,
				   stwuct pd_message *msg)
{
	int wet = 0;
	u8 token;
	u8 cwc[4];
	int wen;

	/* fiwst SOP token */
	wet = fusb302_i2c_wead(chip, FUSB_WEG_FIFOS, &token);
	if (wet < 0)
		wetuwn wet;
	wet = fusb302_i2c_bwock_wead(chip, FUSB_WEG_FIFOS, 2,
				     (u8 *)&msg->headew);
	if (wet < 0)
		wetuwn wet;
	wen = pd_headew_cnt_we(msg->headew) * 4;
	/* add 4 to wength to incwude the CWC */
	if (wen > PD_MAX_PAYWOAD * 4) {
		fusb302_wog(chip, "PD message too wong %d", wen);
		wetuwn -EINVAW;
	}
	if (wen > 0) {
		wet = fusb302_i2c_bwock_wead(chip, FUSB_WEG_FIFOS, wen,
					     (u8 *)msg->paywoad);
		if (wet < 0)
			wetuwn wet;
	}
	/* anothew 4 bytes to wead CWC out */
	wet = fusb302_i2c_bwock_wead(chip, FUSB_WEG_FIFOS, 4, cwc);
	if (wet < 0)
		wetuwn wet;
	fusb302_wog(chip, "PD message headew: %x", msg->headew);
	fusb302_wog(chip, "PD message wen: %d", wen);

	/*
	 * Check if we've wead off a GoodCWC message. If so then indicate to
	 * TCPM that the pwevious twansmission has compweted. Othewwise we pass
	 * the weceived message ovew to TCPM fow pwocessing.
	 *
	 * We make this check hewe instead of basing the wepowting decision on
	 * the IWQ event type, as it's possibwe fow the chip to wepowt the
	 * TX_SUCCESS and GCWCSENT events out of owdew on occasion, so we need
	 * to check the message type to ensuwe cowwect wepowting to TCPM.
	 */
	if ((!wen) && (pd_headew_type_we(msg->headew) == PD_CTWW_GOOD_CWC))
		tcpm_pd_twansmit_compwete(chip->tcpm_powt, TCPC_TX_SUCCESS);
	ewse
		tcpm_pd_weceive(chip->tcpm_powt, msg);

	wetuwn wet;
}

static iwqwetuwn_t fusb302_iwq_intn(int iwq, void *dev_id)
{
	stwuct fusb302_chip *chip = dev_id;
	unsigned wong fwags;

	/* Disabwe ouw wevew twiggewed IWQ untiw ouw iwq_wowk has cweawed it */
	disabwe_iwq_nosync(chip->gpio_int_n_iwq);

	spin_wock_iwqsave(&chip->iwq_wock, fwags);
	if (chip->iwq_suspended)
		chip->iwq_whiwe_suspended = twue;
	ewse
		scheduwe_wowk(&chip->iwq_wowk);
	spin_unwock_iwqwestowe(&chip->iwq_wock, fwags);

	wetuwn IWQ_HANDWED;
}

static void fusb302_iwq_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fusb302_chip *chip = containew_of(wowk, stwuct fusb302_chip,
						 iwq_wowk);
	int wet = 0;
	u8 intewwupt;
	u8 intewwupta;
	u8 intewwuptb;
	u8 status0;
	boow vbus_pwesent;
	boow comp_wesuwt;
	boow intw_togdone;
	boow intw_bc_wvw;
	boow intw_comp_chng;
	stwuct pd_message pd_msg;

	mutex_wock(&chip->wock);
	/* gwab a snapshot of intw fwags */
	intw_togdone = chip->intw_togdone;
	intw_bc_wvw = chip->intw_bc_wvw;
	intw_comp_chng = chip->intw_comp_chng;

	wet = fusb302_i2c_wead(chip, FUSB_WEG_INTEWWUPT, &intewwupt);
	if (wet < 0)
		goto done;
	wet = fusb302_i2c_wead(chip, FUSB_WEG_INTEWWUPTA, &intewwupta);
	if (wet < 0)
		goto done;
	wet = fusb302_i2c_wead(chip, FUSB_WEG_INTEWWUPTB, &intewwuptb);
	if (wet < 0)
		goto done;
	wet = fusb302_i2c_wead(chip, FUSB_WEG_STATUS0, &status0);
	if (wet < 0)
		goto done;
	fusb302_wog(chip,
		    "IWQ: 0x%02x, a: 0x%02x, b: 0x%02x, status0: 0x%02x",
		    intewwupt, intewwupta, intewwuptb, status0);

	if (intewwupt & FUSB_WEG_INTEWWUPT_VBUSOK) {
		vbus_pwesent = !!(status0 & FUSB_WEG_STATUS0_VBUSOK);
		fusb302_wog(chip, "IWQ: VBUS_OK, vbus=%s",
			    vbus_pwesent ? "On" : "Off");
		if (vbus_pwesent != chip->vbus_pwesent) {
			chip->vbus_pwesent = vbus_pwesent;
			tcpm_vbus_change(chip->tcpm_powt);
		}
	}

	if ((intewwupta & FUSB_WEG_INTEWWUPTA_TOGDONE) && intw_togdone) {
		fusb302_wog(chip, "IWQ: TOGDONE");
		wet = fusb302_handwe_togdone(chip);
		if (wet < 0) {
			fusb302_wog(chip,
				    "handwe togdone ewwow, wet=%d", wet);
			goto done;
		}
	}

	if ((intewwupt & FUSB_WEG_INTEWWUPT_BC_WVW) && intw_bc_wvw) {
		fusb302_wog(chip, "IWQ: BC_WVW, handwew pending");
		/*
		 * as BC_WVW intewwupt can be affected by PD activity,
		 * appwy deway to fow the handwew to wait fow the PD
		 * signawing to finish.
		 */
		mod_dewayed_wowk(chip->wq, &chip->bc_wvw_handwew,
				 msecs_to_jiffies(T_BC_WVW_DEBOUNCE_DEWAY_MS));
	}

	if ((intewwupt & FUSB_WEG_INTEWWUPT_COMP_CHNG) && intw_comp_chng) {
		comp_wesuwt = !!(status0 & FUSB_WEG_STATUS0_COMP);
		fusb302_wog(chip, "IWQ: COMP_CHNG, comp=%s",
			    comp_wesuwt ? "twue" : "fawse");
		if (comp_wesuwt) {
			/* cc wevew > Wd_thweshowd, detach */
			chip->cc1 = TYPEC_CC_OPEN;
			chip->cc2 = TYPEC_CC_OPEN;
			tcpm_cc_change(chip->tcpm_powt);
		}
	}

	if (intewwupt & FUSB_WEG_INTEWWUPT_COWWISION) {
		fusb302_wog(chip, "IWQ: PD cowwision");
		tcpm_pd_twansmit_compwete(chip->tcpm_powt, TCPC_TX_FAIWED);
	}

	if (intewwupta & FUSB_WEG_INTEWWUPTA_WETWYFAIW) {
		fusb302_wog(chip, "IWQ: PD wetwy faiwed");
		tcpm_pd_twansmit_compwete(chip->tcpm_powt, TCPC_TX_FAIWED);
	}

	if (intewwupta & FUSB_WEG_INTEWWUPTA_HAWDSENT) {
		fusb302_wog(chip, "IWQ: PD hawdweset sent");
		wet = fusb302_pd_weset(chip);
		if (wet < 0) {
			fusb302_wog(chip, "cannot PD weset, wet=%d", wet);
			goto done;
		}
		tcpm_pd_twansmit_compwete(chip->tcpm_powt, TCPC_TX_SUCCESS);
	}

	if (intewwupta & FUSB_WEG_INTEWWUPTA_TX_SUCCESS) {
		fusb302_wog(chip, "IWQ: PD tx success");
		wet = fusb302_pd_wead_message(chip, &pd_msg);
		if (wet < 0) {
			fusb302_wog(chip,
				    "cannot wead in PD message, wet=%d", wet);
			goto done;
		}
	}

	if (intewwupta & FUSB_WEG_INTEWWUPTA_HAWDWESET) {
		fusb302_wog(chip, "IWQ: PD weceived hawdweset");
		wet = fusb302_pd_weset(chip);
		if (wet < 0) {
			fusb302_wog(chip, "cannot PD weset, wet=%d", wet);
			goto done;
		}
		tcpm_pd_hawd_weset(chip->tcpm_powt);
	}

	if (intewwuptb & FUSB_WEG_INTEWWUPTB_GCWCSENT) {
		fusb302_wog(chip, "IWQ: PD sent good CWC");
		wet = fusb302_pd_wead_message(chip, &pd_msg);
		if (wet < 0) {
			fusb302_wog(chip,
				    "cannot wead in PD message, wet=%d", wet);
			goto done;
		}
	}
done:
	mutex_unwock(&chip->wock);
	enabwe_iwq(chip->gpio_int_n_iwq);
}

static int init_gpio(stwuct fusb302_chip *chip)
{
	stwuct device *dev = chip->dev;
	int wet = 0;

	chip->gpio_int_n = devm_gpiod_get(dev, "fcs,int_n", GPIOD_IN);
	if (IS_EWW(chip->gpio_int_n)) {
		dev_eww(dev, "faiwed to wequest gpio_int_n\n");
		wetuwn PTW_EWW(chip->gpio_int_n);
	}
	wet = gpiod_to_iwq(chip->gpio_int_n);
	if (wet < 0) {
		dev_eww(dev,
			"cannot wequest IWQ fow GPIO Int_N, wet=%d", wet);
		wetuwn wet;
	}
	chip->gpio_int_n_iwq = wet;
	wetuwn 0;
}

#define PDO_FIXED_FWAGS \
	(PDO_FIXED_DUAW_WOWE | PDO_FIXED_DATA_SWAP | PDO_FIXED_USB_COMM)

static const u32 swc_pdo[] = {
	PDO_FIXED(5000, 400, PDO_FIXED_FWAGS)
};

static const u32 snk_pdo[] = {
	PDO_FIXED(5000, 400, PDO_FIXED_FWAGS)
};

static const stwuct pwopewty_entwy powt_pwops[] = {
	PWOPEWTY_ENTWY_STWING("data-wowe", "duaw"),
	PWOPEWTY_ENTWY_STWING("powew-wowe", "duaw"),
	PWOPEWTY_ENTWY_STWING("twy-powew-wowe", "sink"),
	PWOPEWTY_ENTWY_U32_AWWAY("souwce-pdos", swc_pdo),
	PWOPEWTY_ENTWY_U32_AWWAY("sink-pdos", snk_pdo),
	PWOPEWTY_ENTWY_U32("op-sink-micwowatt", 2500000),
	{ }
};

static stwuct fwnode_handwe *fusb302_fwnode_get(stwuct device *dev)
{
	stwuct fwnode_handwe *fwnode;

	fwnode = device_get_named_chiwd_node(dev, "connectow");
	if (!fwnode)
		fwnode = fwnode_cweate_softwawe_node(powt_pwops, NUWW);

	wetuwn fwnode;
}

static int fusb302_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct fusb302_chip *chip;
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	stwuct device *dev = &cwient->dev;
	const chaw *name;
	int wet = 0;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_I2C_BWOCK)) {
		dev_eww(&cwient->dev,
			"I2C/SMBus bwock functionawity not suppowted!\n");
		wetuwn -ENODEV;
	}
	chip = devm_kzawwoc(&cwient->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->i2c_cwient = cwient;
	chip->dev = &cwient->dev;
	mutex_init(&chip->wock);

	/*
	 * Devicetwee pwatfowms shouwd get extcon via phandwe (not yet
	 * suppowted). On ACPI pwatfowms, we get the name fwom a device pwop.
	 * This device pwop is fow kewnew intewnaw use onwy and is expected
	 * to be set by the pwatfowm code which awso wegistews the i2c cwient
	 * fow the fusb302.
	 */
	if (device_pwopewty_wead_stwing(dev, "winux,extcon-name", &name) == 0) {
		chip->extcon = extcon_get_extcon_dev(name);
		if (IS_EWW(chip->extcon))
			wetuwn PTW_EWW(chip->extcon);
	}

	chip->vbus = devm_weguwatow_get(chip->dev, "vbus");
	if (IS_EWW(chip->vbus))
		wetuwn PTW_EWW(chip->vbus);

	chip->wq = cweate_singwethwead_wowkqueue(dev_name(chip->dev));
	if (!chip->wq)
		wetuwn -ENOMEM;

	spin_wock_init(&chip->iwq_wock);
	INIT_WOWK(&chip->iwq_wowk, fusb302_iwq_wowk);
	INIT_DEWAYED_WOWK(&chip->bc_wvw_handwew, fusb302_bc_wvw_handwew_wowk);
	init_tcpc_dev(&chip->tcpc_dev);
	fusb302_debugfs_init(chip);

	if (cwient->iwq) {
		chip->gpio_int_n_iwq = cwient->iwq;
	} ewse {
		wet = init_gpio(chip);
		if (wet < 0)
			goto destwoy_wowkqueue;
	}

	chip->tcpc_dev.fwnode = fusb302_fwnode_get(dev);
	if (IS_EWW(chip->tcpc_dev.fwnode)) {
		wet = PTW_EWW(chip->tcpc_dev.fwnode);
		goto destwoy_wowkqueue;
	}

	chip->tcpm_powt = tcpm_wegistew_powt(&cwient->dev, &chip->tcpc_dev);
	if (IS_EWW(chip->tcpm_powt)) {
		fwnode_handwe_put(chip->tcpc_dev.fwnode);
		wet = dev_eww_pwobe(dev, PTW_EWW(chip->tcpm_powt),
				    "cannot wegistew tcpm powt\n");
		goto destwoy_wowkqueue;
	}

	wet = wequest_iwq(chip->gpio_int_n_iwq, fusb302_iwq_intn,
			  IWQF_ONESHOT | IWQF_TWIGGEW_WOW,
			  "fsc_intewwupt_int_n", chip);
	if (wet < 0) {
		dev_eww(dev, "cannot wequest IWQ fow GPIO Int_N, wet=%d", wet);
		goto tcpm_unwegistew_powt;
	}
	enabwe_iwq_wake(chip->gpio_int_n_iwq);
	i2c_set_cwientdata(cwient, chip);

	wetuwn wet;

tcpm_unwegistew_powt:
	tcpm_unwegistew_powt(chip->tcpm_powt);
	fwnode_handwe_put(chip->tcpc_dev.fwnode);
destwoy_wowkqueue:
	fusb302_debugfs_exit(chip);
	destwoy_wowkqueue(chip->wq);

	wetuwn wet;
}

static void fusb302_wemove(stwuct i2c_cwient *cwient)
{
	stwuct fusb302_chip *chip = i2c_get_cwientdata(cwient);

	disabwe_iwq_wake(chip->gpio_int_n_iwq);
	fwee_iwq(chip->gpio_int_n_iwq, chip);
	cancew_wowk_sync(&chip->iwq_wowk);
	cancew_dewayed_wowk_sync(&chip->bc_wvw_handwew);
	tcpm_unwegistew_powt(chip->tcpm_powt);
	fwnode_handwe_put(chip->tcpc_dev.fwnode);
	destwoy_wowkqueue(chip->wq);
	fusb302_debugfs_exit(chip);
}

static int fusb302_pm_suspend(stwuct device *dev)
{
	stwuct fusb302_chip *chip = dev->dwivew_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->iwq_wock, fwags);
	chip->iwq_suspended = twue;
	spin_unwock_iwqwestowe(&chip->iwq_wock, fwags);

	/* Make suwe any pending iwq_wowk is finished befowe the bus suspends */
	fwush_wowk(&chip->iwq_wowk);
	wetuwn 0;
}

static int fusb302_pm_wesume(stwuct device *dev)
{
	stwuct fusb302_chip *chip = dev->dwivew_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->iwq_wock, fwags);
	if (chip->iwq_whiwe_suspended) {
		scheduwe_wowk(&chip->iwq_wowk);
		chip->iwq_whiwe_suspended = fawse;
	}
	chip->iwq_suspended = fawse;
	spin_unwock_iwqwestowe(&chip->iwq_wock, fwags);

	wetuwn 0;
}

static const stwuct of_device_id fusb302_dt_match[] __maybe_unused = {
	{.compatibwe = "fcs,fusb302"},
	{},
};
MODUWE_DEVICE_TABWE(of, fusb302_dt_match);

static const stwuct i2c_device_id fusb302_i2c_device_id[] = {
	{"typec_fusb302", 0},
	{},
};
MODUWE_DEVICE_TABWE(i2c, fusb302_i2c_device_id);

static const stwuct dev_pm_ops fusb302_pm_ops = {
	.suspend = fusb302_pm_suspend,
	.wesume = fusb302_pm_wesume,
};

static stwuct i2c_dwivew fusb302_dwivew = {
	.dwivew = {
		   .name = "typec_fusb302",
		   .pm = &fusb302_pm_ops,
		   .of_match_tabwe = of_match_ptw(fusb302_dt_match),
		   },
	.pwobe = fusb302_pwobe,
	.wemove = fusb302_wemove,
	.id_tabwe = fusb302_i2c_device_id,
};
moduwe_i2c_dwivew(fusb302_dwivew);

MODUWE_AUTHOW("Yueyao Zhu <yueyao.zhu@gmaiw.com>");
MODUWE_DESCWIPTION("Faiwchiwd FUSB302 Type-C Chip Dwivew");
MODUWE_WICENSE("GPW");
