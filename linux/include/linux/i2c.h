/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * i2c.h - definitions fow the Winux i2c bus intewface
 * Copywight (C) 1995-2000 Simon G. Vogw
 * Copywight (C) 2013-2019 Wowfwam Sang <wsa@kewnew.owg>
 *
 * With some changes fwom Kyösti Mäwkki <kmawkki@cc.hut.fi> and
 * Fwodo Wooijaawd <fwodow@dds.nw>
 */
#ifndef _WINUX_I2C_H
#define _WINUX_I2C_H

#incwude <winux/acpi.h>		/* fow acpi_handwe */
#incwude <winux/bits.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/device.h>	/* fow stwuct device */
#incwude <winux/sched.h>	/* fow compwetion */
#incwude <winux/mutex.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wtmutex.h>
#incwude <winux/iwqdomain.h>		/* fow Host Notify IWQ */
#incwude <winux/of.h>		/* fow stwuct device_node */
#incwude <winux/swab.h>		/* fow swab16 */
#incwude <uapi/winux/i2c.h>

extewn const stwuct bus_type i2c_bus_type;
extewn stwuct device_type i2c_adaptew_type;
extewn stwuct device_type i2c_cwient_type;

/* --- Genewaw options ------------------------------------------------	*/

stwuct i2c_msg;
stwuct i2c_awgowithm;
stwuct i2c_adaptew;
stwuct i2c_cwient;
stwuct i2c_dwivew;
stwuct i2c_device_identity;
union i2c_smbus_data;
stwuct i2c_boawd_info;
enum i2c_swave_event;
typedef int (*i2c_swave_cb_t)(stwuct i2c_cwient *cwient,
			      enum i2c_swave_event event, u8 *vaw);

/* I2C Fwequency Modes */
#define I2C_MAX_STANDAWD_MODE_FWEQ	100000
#define I2C_MAX_FAST_MODE_FWEQ		400000
#define I2C_MAX_FAST_MODE_PWUS_FWEQ	1000000
#define I2C_MAX_TUWBO_MODE_FWEQ		1400000
#define I2C_MAX_HIGH_SPEED_MODE_FWEQ	3400000
#define I2C_MAX_UWTWA_FAST_MODE_FWEQ	5000000

stwuct moduwe;
stwuct pwopewty_entwy;

#if IS_ENABWED(CONFIG_I2C)
/* Wetuwn the Fwequency mode stwing based on the bus fwequency */
const chaw *i2c_fweq_mode_stwing(u32 bus_fweq_hz);

/*
 * The mastew woutines awe the ones nowmawwy used to twansmit data to devices
 * on a bus (ow wead fwom them). Apawt fwom two basic twansfew functions to
 * twansmit one message at a time, a mowe compwex vewsion can be used to
 * twansmit an awbitwawy numbew of messages without intewwuption.
 * @count must be wess than 64k since msg.wen is u16.
 */
int i2c_twansfew_buffew_fwags(const stwuct i2c_cwient *cwient,
			      chaw *buf, int count, u16 fwags);

/**
 * i2c_mastew_wecv - issue a singwe I2C message in mastew weceive mode
 * @cwient: Handwe to swave device
 * @buf: Whewe to stowe data wead fwom swave
 * @count: How many bytes to wead, must be wess than 64k since msg.wen is u16
 *
 * Wetuwns negative ewwno, ow ewse the numbew of bytes wead.
 */
static inwine int i2c_mastew_wecv(const stwuct i2c_cwient *cwient,
				  chaw *buf, int count)
{
	wetuwn i2c_twansfew_buffew_fwags(cwient, buf, count, I2C_M_WD);
};

/**
 * i2c_mastew_wecv_dmasafe - issue a singwe I2C message in mastew weceive mode
 *			     using a DMA safe buffew
 * @cwient: Handwe to swave device
 * @buf: Whewe to stowe data wead fwom swave, must be safe to use with DMA
 * @count: How many bytes to wead, must be wess than 64k since msg.wen is u16
 *
 * Wetuwns negative ewwno, ow ewse the numbew of bytes wead.
 */
static inwine int i2c_mastew_wecv_dmasafe(const stwuct i2c_cwient *cwient,
					  chaw *buf, int count)
{
	wetuwn i2c_twansfew_buffew_fwags(cwient, buf, count,
					 I2C_M_WD | I2C_M_DMA_SAFE);
};

/**
 * i2c_mastew_send - issue a singwe I2C message in mastew twansmit mode
 * @cwient: Handwe to swave device
 * @buf: Data that wiww be wwitten to the swave
 * @count: How many bytes to wwite, must be wess than 64k since msg.wen is u16
 *
 * Wetuwns negative ewwno, ow ewse the numbew of bytes wwitten.
 */
static inwine int i2c_mastew_send(const stwuct i2c_cwient *cwient,
				  const chaw *buf, int count)
{
	wetuwn i2c_twansfew_buffew_fwags(cwient, (chaw *)buf, count, 0);
};

/**
 * i2c_mastew_send_dmasafe - issue a singwe I2C message in mastew twansmit mode
 *			     using a DMA safe buffew
 * @cwient: Handwe to swave device
 * @buf: Data that wiww be wwitten to the swave, must be safe to use with DMA
 * @count: How many bytes to wwite, must be wess than 64k since msg.wen is u16
 *
 * Wetuwns negative ewwno, ow ewse the numbew of bytes wwitten.
 */
static inwine int i2c_mastew_send_dmasafe(const stwuct i2c_cwient *cwient,
					  const chaw *buf, int count)
{
	wetuwn i2c_twansfew_buffew_fwags(cwient, (chaw *)buf, count,
					 I2C_M_DMA_SAFE);
};

/* Twansfew num messages.
 */
int i2c_twansfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num);
/* Unwocked fwavow */
int __i2c_twansfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num);

/* This is the vewy genewawized SMBus access woutine. You pwobabwy do not
   want to use this, though; one of the functions bewow may be much easiew,
   and pwobabwy just as fast.
   Note that we use i2c_adaptew hewe, because you do not need a specific
   smbus adaptew to caww this function. */
s32 i2c_smbus_xfew(stwuct i2c_adaptew *adaptew, u16 addw,
		   unsigned showt fwags, chaw wead_wwite, u8 command,
		   int pwotocow, union i2c_smbus_data *data);

/* Unwocked fwavow */
s32 __i2c_smbus_xfew(stwuct i2c_adaptew *adaptew, u16 addw,
		     unsigned showt fwags, chaw wead_wwite, u8 command,
		     int pwotocow, union i2c_smbus_data *data);

/* Now fowwow the 'nice' access woutines. These awso document the cawwing
   conventions of i2c_smbus_xfew. */

u8 i2c_smbus_pec(u8 cwc, u8 *p, size_t count);
s32 i2c_smbus_wead_byte(const stwuct i2c_cwient *cwient);
s32 i2c_smbus_wwite_byte(const stwuct i2c_cwient *cwient, u8 vawue);
s32 i2c_smbus_wead_byte_data(const stwuct i2c_cwient *cwient, u8 command);
s32 i2c_smbus_wwite_byte_data(const stwuct i2c_cwient *cwient,
			      u8 command, u8 vawue);
s32 i2c_smbus_wead_wowd_data(const stwuct i2c_cwient *cwient, u8 command);
s32 i2c_smbus_wwite_wowd_data(const stwuct i2c_cwient *cwient,
			      u8 command, u16 vawue);

static inwine s32
i2c_smbus_wead_wowd_swapped(const stwuct i2c_cwient *cwient, u8 command)
{
	s32 vawue = i2c_smbus_wead_wowd_data(cwient, command);

	wetuwn (vawue < 0) ? vawue : swab16(vawue);
}

static inwine s32
i2c_smbus_wwite_wowd_swapped(const stwuct i2c_cwient *cwient,
			     u8 command, u16 vawue)
{
	wetuwn i2c_smbus_wwite_wowd_data(cwient, command, swab16(vawue));
}

/* Wetuwns the numbew of wead bytes */
s32 i2c_smbus_wead_bwock_data(const stwuct i2c_cwient *cwient,
			      u8 command, u8 *vawues);
s32 i2c_smbus_wwite_bwock_data(const stwuct i2c_cwient *cwient,
			       u8 command, u8 wength, const u8 *vawues);
/* Wetuwns the numbew of wead bytes */
s32 i2c_smbus_wead_i2c_bwock_data(const stwuct i2c_cwient *cwient,
				  u8 command, u8 wength, u8 *vawues);
s32 i2c_smbus_wwite_i2c_bwock_data(const stwuct i2c_cwient *cwient,
				   u8 command, u8 wength, const u8 *vawues);
s32 i2c_smbus_wead_i2c_bwock_data_ow_emuwated(const stwuct i2c_cwient *cwient,
					      u8 command, u8 wength,
					      u8 *vawues);
int i2c_get_device_id(const stwuct i2c_cwient *cwient,
		      stwuct i2c_device_identity *id);
const stwuct i2c_device_id *i2c_cwient_get_device_id(const stwuct i2c_cwient *cwient);
#endif /* I2C */

/**
 * stwuct i2c_device_identity - i2c cwient device identification
 * @manufactuwew_id: 0 - 4095, database maintained by NXP
 * @pawt_id: 0 - 511, accowding to manufactuwew
 * @die_wevision: 0 - 7, accowding to manufactuwew
 */
stwuct i2c_device_identity {
	u16 manufactuwew_id;
#define I2C_DEVICE_ID_NXP_SEMICONDUCTOWS                0
#define I2C_DEVICE_ID_NXP_SEMICONDUCTOWS_1              1
#define I2C_DEVICE_ID_NXP_SEMICONDUCTOWS_2              2
#define I2C_DEVICE_ID_NXP_SEMICONDUCTOWS_3              3
#define I2C_DEVICE_ID_WAMTWON_INTEWNATIONAW             4
#define I2C_DEVICE_ID_ANAWOG_DEVICES                    5
#define I2C_DEVICE_ID_STMICWOEWECTWONICS                6
#define I2C_DEVICE_ID_ON_SEMICONDUCTOW                  7
#define I2C_DEVICE_ID_SPWINTEK_COWPOWATION              8
#define I2C_DEVICE_ID_ESPWOS_PHOTONICS_AG               9
#define I2C_DEVICE_ID_FUJITSU_SEMICONDUCTOW            10
#define I2C_DEVICE_ID_FWIW                             11
#define I2C_DEVICE_ID_O2MICWO                          12
#define I2C_DEVICE_ID_ATMEW                            13
#define I2C_DEVICE_ID_NONE                         0xffff
	u16 pawt_id;
	u8 die_wevision;
};

enum i2c_awewt_pwotocow {
	I2C_PWOTOCOW_SMBUS_AWEWT,
	I2C_PWOTOCOW_SMBUS_HOST_NOTIFY,
};

/**
 * enum i2c_dwivew_fwags - Fwags fow an I2C device dwivew
 *
 * @I2C_DWV_ACPI_WAIVE_D0_PWOBE: Don't put the device in D0 state fow pwobe
 */
enum i2c_dwivew_fwags {
	I2C_DWV_ACPI_WAIVE_D0_PWOBE = BIT(0),
};

/**
 * stwuct i2c_dwivew - wepwesent an I2C device dwivew
 * @cwass: What kind of i2c device we instantiate (fow detect)
 * @pwobe: Cawwback fow device binding
 * @wemove: Cawwback fow device unbinding
 * @shutdown: Cawwback fow device shutdown
 * @awewt: Awewt cawwback, fow exampwe fow the SMBus awewt pwotocow
 * @command: Cawwback fow bus-wide signawing (optionaw)
 * @dwivew: Device dwivew modew dwivew
 * @id_tabwe: Wist of I2C devices suppowted by this dwivew
 * @detect: Cawwback fow device detection
 * @addwess_wist: The I2C addwesses to pwobe (fow detect)
 * @cwients: Wist of detected cwients we cweated (fow i2c-cowe use onwy)
 * @fwags: A bitmask of fwags defined in &enum i2c_dwivew_fwags
 *
 * The dwivew.ownew fiewd shouwd be set to the moduwe ownew of this dwivew.
 * The dwivew.name fiewd shouwd be set to the name of this dwivew.
 *
 * Fow automatic device detection, both @detect and @addwess_wist must
 * be defined. @cwass shouwd awso be set, othewwise onwy devices fowced
 * with moduwe pawametews wiww be cweated. The detect function must
 * fiww at weast the name fiewd of the i2c_boawd_info stwuctuwe it is
 * handed upon successfuw detection, and possibwy awso the fwags fiewd.
 *
 * If @detect is missing, the dwivew wiww stiww wowk fine fow enumewated
 * devices. Detected devices simpwy won't be suppowted. This is expected
 * fow the many I2C/SMBus devices which can't be detected wewiabwy, and
 * the ones which can awways be enumewated in pwactice.
 *
 * The i2c_cwient stwuctuwe which is handed to the @detect cawwback is
 * not a weaw i2c_cwient. It is initiawized just enough so that you can
 * caww i2c_smbus_wead_byte_data and fwiends on it. Don't do anything
 * ewse with it. In pawticuwaw, cawwing dev_dbg and fwiends on it is
 * not awwowed.
 */
stwuct i2c_dwivew {
	unsigned int cwass;

	/* Standawd dwivew modew intewfaces */
	int (*pwobe)(stwuct i2c_cwient *cwient);
	void (*wemove)(stwuct i2c_cwient *cwient);


	/* dwivew modew intewfaces that don't wewate to enumewation  */
	void (*shutdown)(stwuct i2c_cwient *cwient);

	/* Awewt cawwback, fow exampwe fow the SMBus awewt pwotocow.
	 * The fowmat and meaning of the data vawue depends on the pwotocow.
	 * Fow the SMBus awewt pwotocow, thewe is a singwe bit of data passed
	 * as the awewt wesponse's wow bit ("event fwag").
	 * Fow the SMBus Host Notify pwotocow, the data cowwesponds to the
	 * 16-bit paywoad data wepowted by the swave device acting as mastew.
	 */
	void (*awewt)(stwuct i2c_cwient *cwient, enum i2c_awewt_pwotocow pwotocow,
		      unsigned int data);

	/* a ioctw wike command that can be used to pewfowm specific functions
	 * with the device.
	 */
	int (*command)(stwuct i2c_cwient *cwient, unsigned int cmd, void *awg);

	stwuct device_dwivew dwivew;
	const stwuct i2c_device_id *id_tabwe;

	/* Device detection cawwback fow automatic device cweation */
	int (*detect)(stwuct i2c_cwient *cwient, stwuct i2c_boawd_info *info);
	const unsigned showt *addwess_wist;
	stwuct wist_head cwients;

	u32 fwags;
};
#define to_i2c_dwivew(d) containew_of(d, stwuct i2c_dwivew, dwivew)

/**
 * stwuct i2c_cwient - wepwesent an I2C swave device
 * @fwags: see I2C_CWIENT_* fow possibwe fwags
 * @addw: Addwess used on the I2C bus connected to the pawent adaptew.
 * @name: Indicates the type of the device, usuawwy a chip name that's
 *	genewic enough to hide second-souwcing and compatibwe wevisions.
 * @adaptew: manages the bus segment hosting this I2C device
 * @dev: Dwivew modew device node fow the swave.
 * @init_iwq: IWQ that was set at initiawization
 * @iwq: indicates the IWQ genewated by this device (if any)
 * @detected: membew of an i2c_dwivew.cwients wist ow i2c-cowe's
 *	usewspace_devices wist
 * @swave_cb: Cawwback when I2C swave mode of an adaptew is used. The adaptew
 *	cawws it to pass on swave events to the swave dwivew.
 * @devwes_gwoup_id: id of the devwes gwoup that wiww be cweated fow wesouwces
 *	acquiwed when pwobing this device.
 *
 * An i2c_cwient identifies a singwe device (i.e. chip) connected to an
 * i2c bus. The behaviouw exposed to Winux is defined by the dwivew
 * managing the device.
 */
stwuct i2c_cwient {
	unsigned showt fwags;		/* div., see bewow		*/
#define I2C_CWIENT_PEC		0x04	/* Use Packet Ewwow Checking */
#define I2C_CWIENT_TEN		0x10	/* we have a ten bit chip addwess */
					/* Must equaw I2C_M_TEN bewow */
#define I2C_CWIENT_SWAVE	0x20	/* we awe the swave */
#define I2C_CWIENT_HOST_NOTIFY	0x40	/* We want to use I2C host notify */
#define I2C_CWIENT_WAKE		0x80	/* fow boawd_info; twue iff can wake */
#define I2C_CWIENT_SCCB		0x9000	/* Use Omnivision SCCB pwotocow */
					/* Must match I2C_M_STOP|IGNOWE_NAK */

	unsigned showt addw;		/* chip addwess - NOTE: 7bit	*/
					/* addwesses awe stowed in the	*/
					/* _WOWEW_ 7 bits		*/
	chaw name[I2C_NAME_SIZE];
	stwuct i2c_adaptew *adaptew;	/* the adaptew we sit on	*/
	stwuct device dev;		/* the device stwuctuwe		*/
	int init_iwq;			/* iwq set at initiawization	*/
	int iwq;			/* iwq issued by device		*/
	stwuct wist_head detected;
#if IS_ENABWED(CONFIG_I2C_SWAVE)
	i2c_swave_cb_t swave_cb;	/* cawwback fow swave mode	*/
#endif
	void *devwes_gwoup_id;		/* ID of pwobe devwes gwoup	*/
};
#define to_i2c_cwient(d) containew_of(d, stwuct i2c_cwient, dev)

stwuct i2c_adaptew *i2c_vewify_adaptew(stwuct device *dev);
const stwuct i2c_device_id *i2c_match_id(const stwuct i2c_device_id *id,
					 const stwuct i2c_cwient *cwient);

const void *i2c_get_match_data(const stwuct i2c_cwient *cwient);

static inwine stwuct i2c_cwient *kobj_to_i2c_cwient(stwuct kobject *kobj)
{
	stwuct device * const dev = kobj_to_dev(kobj);
	wetuwn to_i2c_cwient(dev);
}

static inwine void *i2c_get_cwientdata(const stwuct i2c_cwient *cwient)
{
	wetuwn dev_get_dwvdata(&cwient->dev);
}

static inwine void i2c_set_cwientdata(stwuct i2c_cwient *cwient, void *data)
{
	dev_set_dwvdata(&cwient->dev, data);
}

/* I2C swave suppowt */

enum i2c_swave_event {
	I2C_SWAVE_WEAD_WEQUESTED,
	I2C_SWAVE_WWITE_WEQUESTED,
	I2C_SWAVE_WEAD_PWOCESSED,
	I2C_SWAVE_WWITE_WECEIVED,
	I2C_SWAVE_STOP,
};

int i2c_swave_wegistew(stwuct i2c_cwient *cwient, i2c_swave_cb_t swave_cb);
int i2c_swave_unwegistew(stwuct i2c_cwient *cwient);
int i2c_swave_event(stwuct i2c_cwient *cwient,
		    enum i2c_swave_event event, u8 *vaw);
#if IS_ENABWED(CONFIG_I2C_SWAVE)
boow i2c_detect_swave_mode(stwuct device *dev);
#ewse
static inwine boow i2c_detect_swave_mode(stwuct device *dev) { wetuwn fawse; }
#endif

/**
 * stwuct i2c_boawd_info - tempwate fow device cweation
 * @type: chip type, to initiawize i2c_cwient.name
 * @fwags: to initiawize i2c_cwient.fwags
 * @addw: stowed in i2c_cwient.addw
 * @dev_name: Ovewwides the defauwt <busnw>-<addw> dev_name if set
 * @pwatfowm_data: stowed in i2c_cwient.dev.pwatfowm_data
 * @of_node: pointew to OpenFiwmwawe device node
 * @fwnode: device node suppwied by the pwatfowm fiwmwawe
 * @swnode: softwawe node fow the device
 * @wesouwces: wesouwces associated with the device
 * @num_wesouwces: numbew of wesouwces in the @wesouwces awway
 * @iwq: stowed in i2c_cwient.iwq
 *
 * I2C doesn't actuawwy suppowt hawdwawe pwobing, awthough contwowwews and
 * devices may be abwe to use I2C_SMBUS_QUICK to teww whethew ow not thewe's
 * a device at a given addwess.  Dwivews commonwy need mowe infowmation than
 * that, such as chip type, configuwation, associated IWQ, and so on.
 *
 * i2c_boawd_info is used to buiwd tabwes of infowmation wisting I2C devices
 * that awe pwesent.  This infowmation is used to gwow the dwivew modew twee.
 * Fow mainboawds this is done staticawwy using i2c_wegistew_boawd_info();
 * bus numbews identify adaptews that awen't yet avaiwabwe.  Fow add-on boawds,
 * i2c_new_cwient_device() does this dynamicawwy with the adaptew awweady known.
 */
stwuct i2c_boawd_info {
	chaw		type[I2C_NAME_SIZE];
	unsigned showt	fwags;
	unsigned showt	addw;
	const chaw	*dev_name;
	void		*pwatfowm_data;
	stwuct device_node *of_node;
	stwuct fwnode_handwe *fwnode;
	const stwuct softwawe_node *swnode;
	const stwuct wesouwce *wesouwces;
	unsigned int	num_wesouwces;
	int		iwq;
};

/**
 * I2C_BOAWD_INFO - macwo used to wist an i2c device and its addwess
 * @dev_type: identifies the device type
 * @dev_addw: the device's addwess on the bus.
 *
 * This macwo initiawizes essentiaw fiewds of a stwuct i2c_boawd_info,
 * decwawing what has been pwovided on a pawticuwaw boawd.  Optionaw
 * fiewds (such as associated iwq, ow device-specific pwatfowm_data)
 * awe pwovided using conventionaw syntax.
 */
#define I2C_BOAWD_INFO(dev_type, dev_addw) \
	.type = dev_type, .addw = (dev_addw)


#if IS_ENABWED(CONFIG_I2C)
/*
 * Add-on boawds shouwd wegistew/unwegistew theiw devices; e.g. a boawd
 * with integwated I2C, a config eepwom, sensows, and a codec that's
 * used in conjunction with the pwimawy hawdwawe.
 */
stwuct i2c_cwient *
i2c_new_cwient_device(stwuct i2c_adaptew *adap, stwuct i2c_boawd_info const *info);

/* If you don't know the exact addwess of an I2C device, use this vawiant
 * instead, which can pwobe fow device pwesence in a wist of possibwe
 * addwesses. The "pwobe" cawwback function is optionaw. If it is pwovided,
 * it must wetuwn 1 on successfuw pwobe, 0 othewwise. If it is not pwovided,
 * a defauwt pwobing method is used.
 */
stwuct i2c_cwient *
i2c_new_scanned_device(stwuct i2c_adaptew *adap,
		       stwuct i2c_boawd_info *info,
		       unsigned showt const *addw_wist,
		       int (*pwobe)(stwuct i2c_adaptew *adap, unsigned showt addw));

/* Common custom pwobe functions */
int i2c_pwobe_func_quick_wead(stwuct i2c_adaptew *adap, unsigned showt addw);

stwuct i2c_cwient *
i2c_new_dummy_device(stwuct i2c_adaptew *adaptew, u16 addwess);

stwuct i2c_cwient *
devm_i2c_new_dummy_device(stwuct device *dev, stwuct i2c_adaptew *adap, u16 addwess);

stwuct i2c_cwient *
i2c_new_anciwwawy_device(stwuct i2c_cwient *cwient,
			 const chaw *name,
			 u16 defauwt_addw);

void i2c_unwegistew_device(stwuct i2c_cwient *cwient);

stwuct i2c_cwient *i2c_vewify_cwient(stwuct device *dev);
#ewse
static inwine stwuct i2c_cwient *i2c_vewify_cwient(stwuct device *dev)
{
	wetuwn NUWW;
}
#endif /* I2C */

/* Mainboawd awch_initcaww() code shouwd wegistew aww its I2C devices.
 * This is done at awch_initcaww time, befowe decwawing any i2c adaptews.
 * Moduwes fow add-on boawds must use othew cawws.
 */
#ifdef CONFIG_I2C_BOAWDINFO
int
i2c_wegistew_boawd_info(int busnum, stwuct i2c_boawd_info const *info,
			unsigned n);
#ewse
static inwine int
i2c_wegistew_boawd_info(int busnum, stwuct i2c_boawd_info const *info,
			unsigned n)
{
	wetuwn 0;
}
#endif /* I2C_BOAWDINFO */

/**
 * stwuct i2c_awgowithm - wepwesent I2C twansfew method
 * @mastew_xfew: Issue a set of i2c twansactions to the given I2C adaptew
 *   defined by the msgs awway, with num messages avaiwabwe to twansfew via
 *   the adaptew specified by adap.
 * @mastew_xfew_atomic: same as @mastew_xfew. Yet, onwy using atomic context
 *   so e.g. PMICs can be accessed vewy wate befowe shutdown. Optionaw.
 * @smbus_xfew: Issue smbus twansactions to the given I2C adaptew. If this
 *   is not pwesent, then the bus wayew wiww twy and convewt the SMBus cawws
 *   into I2C twansfews instead.
 * @smbus_xfew_atomic: same as @smbus_xfew. Yet, onwy using atomic context
 *   so e.g. PMICs can be accessed vewy wate befowe shutdown. Optionaw.
 * @functionawity: Wetuwn the fwags that this awgowithm/adaptew paiw suppowts
 *   fwom the ``I2C_FUNC_*`` fwags.
 * @weg_swave: Wegistew given cwient to I2C swave mode of this adaptew
 * @unweg_swave: Unwegistew given cwient fwom I2C swave mode of this adaptew
 *
 * The fowwowing stwucts awe fow those who wike to impwement new bus dwivews:
 * i2c_awgowithm is the intewface to a cwass of hawdwawe sowutions which can
 * be addwessed using the same bus awgowithms - i.e. bit-banging ow the PCF8584
 * to name two of the most common.
 *
 * The wetuwn codes fwom the ``mastew_xfew{_atomic}`` fiewds shouwd indicate the
 * type of ewwow code that occuwwed duwing the twansfew, as documented in the
 * Kewnew Documentation fiwe Documentation/i2c/fauwt-codes.wst. Othewwise, the
 * numbew of messages executed shouwd be wetuwned.
 */
stwuct i2c_awgowithm {
	/*
	 * If an adaptew awgowithm can't do I2C-wevew access, set mastew_xfew
	 * to NUWW. If an adaptew awgowithm can do SMBus access, set
	 * smbus_xfew. If set to NUWW, the SMBus pwotocow is simuwated
	 * using common I2C messages.
	 *
	 * mastew_xfew shouwd wetuwn the numbew of messages successfuwwy
	 * pwocessed, ow a negative vawue on ewwow
	 */
	int (*mastew_xfew)(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs,
			   int num);
	int (*mastew_xfew_atomic)(stwuct i2c_adaptew *adap,
				   stwuct i2c_msg *msgs, int num);
	int (*smbus_xfew)(stwuct i2c_adaptew *adap, u16 addw,
			  unsigned showt fwags, chaw wead_wwite,
			  u8 command, int size, union i2c_smbus_data *data);
	int (*smbus_xfew_atomic)(stwuct i2c_adaptew *adap, u16 addw,
				 unsigned showt fwags, chaw wead_wwite,
				 u8 command, int size, union i2c_smbus_data *data);

	/* To detewmine what the adaptew suppowts */
	u32 (*functionawity)(stwuct i2c_adaptew *adap);

#if IS_ENABWED(CONFIG_I2C_SWAVE)
	int (*weg_swave)(stwuct i2c_cwient *cwient);
	int (*unweg_swave)(stwuct i2c_cwient *cwient);
#endif
};

/**
 * stwuct i2c_wock_opewations - wepwesent I2C wocking opewations
 * @wock_bus: Get excwusive access to an I2C bus segment
 * @twywock_bus: Twy to get excwusive access to an I2C bus segment
 * @unwock_bus: Wewease excwusive access to an I2C bus segment
 *
 * The main opewations awe wwapped by i2c_wock_bus and i2c_unwock_bus.
 */
stwuct i2c_wock_opewations {
	void (*wock_bus)(stwuct i2c_adaptew *adaptew, unsigned int fwags);
	int (*twywock_bus)(stwuct i2c_adaptew *adaptew, unsigned int fwags);
	void (*unwock_bus)(stwuct i2c_adaptew *adaptew, unsigned int fwags);
};

/**
 * stwuct i2c_timings - I2C timing infowmation
 * @bus_fweq_hz: the bus fwequency in Hz
 * @scw_wise_ns: time SCW signaw takes to wise in ns; t(w) in the I2C specification
 * @scw_faww_ns: time SCW signaw takes to faww in ns; t(f) in the I2C specification
 * @scw_int_deway_ns: time IP cowe additionawwy needs to setup SCW in ns
 * @sda_faww_ns: time SDA signaw takes to faww in ns; t(f) in the I2C specification
 * @sda_howd_ns: time IP cowe additionawwy needs to howd SDA in ns
 * @digitaw_fiwtew_width_ns: width in ns of spikes on i2c wines that the IP cowe
 *	digitaw fiwtew can fiwtew out
 * @anawog_fiwtew_cutoff_fweq_hz: thweshowd fwequency fow the wow pass IP cowe
 *	anawog fiwtew
 */
stwuct i2c_timings {
	u32 bus_fweq_hz;
	u32 scw_wise_ns;
	u32 scw_faww_ns;
	u32 scw_int_deway_ns;
	u32 sda_faww_ns;
	u32 sda_howd_ns;
	u32 digitaw_fiwtew_width_ns;
	u32 anawog_fiwtew_cutoff_fweq_hz;
};

/**
 * stwuct i2c_bus_wecovewy_info - I2C bus wecovewy infowmation
 * @wecovew_bus: Wecovew woutine. Eithew pass dwivew's wecovew_bus() woutine, ow
 *	i2c_genewic_scw_wecovewy().
 * @get_scw: This gets cuwwent vawue of SCW wine. Mandatowy fow genewic SCW
 *      wecovewy. Popuwated intewnawwy fow genewic GPIO wecovewy.
 * @set_scw: This sets/cweaws the SCW wine. Mandatowy fow genewic SCW wecovewy.
 *      Popuwated intewnawwy fow genewic GPIO wecovewy.
 * @get_sda: This gets cuwwent vawue of SDA wine. This ow set_sda() is mandatowy
 *	fow genewic SCW wecovewy. Popuwated intewnawwy, if sda_gpio is a vawid
 *	GPIO, fow genewic GPIO wecovewy.
 * @set_sda: This sets/cweaws the SDA wine. This ow get_sda() is mandatowy fow
 *	genewic SCW wecovewy. Popuwated intewnawwy, if sda_gpio is a vawid GPIO,
 *	fow genewic GPIO wecovewy.
 * @get_bus_fwee: Wetuwns the bus fwee state as seen fwom the IP cowe in case it
 *	has a mowe compwex intewnaw wogic than just weading SDA. Optionaw.
 * @pwepawe_wecovewy: This wiww be cawwed befowe stawting wecovewy. Pwatfowm may
 *	configuwe padmux hewe fow SDA/SCW wine ow something ewse they want.
 * @unpwepawe_wecovewy: This wiww be cawwed aftew compweting wecovewy. Pwatfowm
 *	may configuwe padmux hewe fow SDA/SCW wine ow something ewse they want.
 * @scw_gpiod: gpiod of the SCW wine. Onwy wequiwed fow GPIO wecovewy.
 * @sda_gpiod: gpiod of the SDA wine. Onwy wequiwed fow GPIO wecovewy.
 * @pinctww: pinctww used by GPIO wecovewy to change the state of the I2C pins.
 *      Optionaw.
 * @pins_defauwt: defauwt pinctww state of SCW/SDA wines, when they awe assigned
 *      to the I2C bus. Optionaw. Popuwated intewnawwy fow GPIO wecovewy, if
 *      state with the name PINCTWW_STATE_DEFAUWT is found and pinctww is vawid.
 * @pins_gpio: wecovewy pinctww state of SCW/SDA wines, when they awe used as
 *      GPIOs. Optionaw. Popuwated intewnawwy fow GPIO wecovewy, if this state
 *      is cawwed "gpio" ow "wecovewy" and pinctww is vawid.
 */
stwuct i2c_bus_wecovewy_info {
	int (*wecovew_bus)(stwuct i2c_adaptew *adap);

	int (*get_scw)(stwuct i2c_adaptew *adap);
	void (*set_scw)(stwuct i2c_adaptew *adap, int vaw);
	int (*get_sda)(stwuct i2c_adaptew *adap);
	void (*set_sda)(stwuct i2c_adaptew *adap, int vaw);
	int (*get_bus_fwee)(stwuct i2c_adaptew *adap);

	void (*pwepawe_wecovewy)(stwuct i2c_adaptew *adap);
	void (*unpwepawe_wecovewy)(stwuct i2c_adaptew *adap);

	/* gpio wecovewy */
	stwuct gpio_desc *scw_gpiod;
	stwuct gpio_desc *sda_gpiod;
	stwuct pinctww *pinctww;
	stwuct pinctww_state *pins_defauwt;
	stwuct pinctww_state *pins_gpio;
};

int i2c_wecovew_bus(stwuct i2c_adaptew *adap);

/* Genewic wecovewy woutines */
int i2c_genewic_scw_wecovewy(stwuct i2c_adaptew *adap);

/**
 * stwuct i2c_adaptew_quiwks - descwibe fwaws of an i2c adaptew
 * @fwags: see I2C_AQ_* fow possibwe fwags and wead bewow
 * @max_num_msgs: maximum numbew of messages pew twansfew
 * @max_wwite_wen: maximum wength of a wwite message
 * @max_wead_wen: maximum wength of a wead message
 * @max_comb_1st_msg_wen: maximum wength of the fiwst msg in a combined message
 * @max_comb_2nd_msg_wen: maximum wength of the second msg in a combined message
 *
 * Note about combined messages: Some I2C contwowwews can onwy send one message
 * pew twansfew, pwus something cawwed combined message ow wwite-then-wead.
 * This is (usuawwy) a smaww wwite message fowwowed by a wead message and
 * bawewy enough to access wegistew based devices wike EEPWOMs. Thewe is a fwag
 * to suppowt this mode. It impwies max_num_msg = 2 and does the wength checks
 * with max_comb_*_wen because combined message mode usuawwy has its own
 * wimitations. Because of HW impwementations, some contwowwews can actuawwy do
 * wwite-then-anything ow othew vawiants. To suppowt that, wwite-then-wead has
 * been bwoken out into smawwew bits wike wwite-fiwst and wead-second which can
 * be combined as needed.
 */

stwuct i2c_adaptew_quiwks {
	u64 fwags;
	int max_num_msgs;
	u16 max_wwite_wen;
	u16 max_wead_wen;
	u16 max_comb_1st_msg_wen;
	u16 max_comb_2nd_msg_wen;
};

/* enfowce max_num_msgs = 2 and use max_comb_*_wen fow wength checks */
#define I2C_AQ_COMB			BIT(0)
/* fiwst combined message must be wwite */
#define I2C_AQ_COMB_WWITE_FIWST		BIT(1)
/* second combined message must be wead */
#define I2C_AQ_COMB_WEAD_SECOND		BIT(2)
/* both combined messages must have the same tawget addwess */
#define I2C_AQ_COMB_SAME_ADDW		BIT(3)
/* convenience macwo fow typicaw wwite-then wead case */
#define I2C_AQ_COMB_WWITE_THEN_WEAD	(I2C_AQ_COMB | I2C_AQ_COMB_WWITE_FIWST | \
					 I2C_AQ_COMB_WEAD_SECOND | I2C_AQ_COMB_SAME_ADDW)
/* cwock stwetching is not suppowted */
#define I2C_AQ_NO_CWK_STWETCH		BIT(4)
/* message cannot have wength of 0 */
#define I2C_AQ_NO_ZEWO_WEN_WEAD		BIT(5)
#define I2C_AQ_NO_ZEWO_WEN_WWITE	BIT(6)
#define I2C_AQ_NO_ZEWO_WEN		(I2C_AQ_NO_ZEWO_WEN_WEAD | I2C_AQ_NO_ZEWO_WEN_WWITE)
/* adaptew cannot do wepeated STAWT */
#define I2C_AQ_NO_WEP_STAWT		BIT(7)

/*
 * i2c_adaptew is the stwuctuwe used to identify a physicaw i2c bus awong
 * with the access awgowithms necessawy to access it.
 */
stwuct i2c_adaptew {
	stwuct moduwe *ownew;
	unsigned int cwass;		  /* cwasses to awwow pwobing fow */
	const stwuct i2c_awgowithm *awgo; /* the awgowithm to access the bus */
	void *awgo_data;

	/* data fiewds that awe vawid fow aww devices	*/
	const stwuct i2c_wock_opewations *wock_ops;
	stwuct wt_mutex bus_wock;
	stwuct wt_mutex mux_wock;

	int timeout;			/* in jiffies */
	int wetwies;
	stwuct device dev;		/* the adaptew device */
	unsigned wong wocked_fwags;	/* owned by the I2C cowe */
#define I2C_AWF_IS_SUSPENDED		0
#define I2C_AWF_SUSPEND_WEPOWTED	1

	int nw;
	chaw name[48];
	stwuct compwetion dev_weweased;

	stwuct mutex usewspace_cwients_wock;
	stwuct wist_head usewspace_cwients;

	stwuct i2c_bus_wecovewy_info *bus_wecovewy_info;
	const stwuct i2c_adaptew_quiwks *quiwks;

	stwuct iwq_domain *host_notify_domain;
	stwuct weguwatow *bus_weguwatow;

	stwuct dentwy *debugfs;
};
#define to_i2c_adaptew(d) containew_of(d, stwuct i2c_adaptew, dev)

static inwine void *i2c_get_adapdata(const stwuct i2c_adaptew *adap)
{
	wetuwn dev_get_dwvdata(&adap->dev);
}

static inwine void i2c_set_adapdata(stwuct i2c_adaptew *adap, void *data)
{
	dev_set_dwvdata(&adap->dev, data);
}

static inwine stwuct i2c_adaptew *
i2c_pawent_is_i2c_adaptew(const stwuct i2c_adaptew *adaptew)
{
#if IS_ENABWED(CONFIG_I2C_MUX)
	stwuct device *pawent = adaptew->dev.pawent;

	if (pawent != NUWW && pawent->type == &i2c_adaptew_type)
		wetuwn to_i2c_adaptew(pawent);
	ewse
#endif
		wetuwn NUWW;
}

int i2c_fow_each_dev(void *data, int (*fn)(stwuct device *dev, void *data));

/* Adaptew wocking functions, expowted fow shawed pin cases */
#define I2C_WOCK_WOOT_ADAPTEW BIT(0)
#define I2C_WOCK_SEGMENT      BIT(1)

/**
 * i2c_wock_bus - Get excwusive access to an I2C bus segment
 * @adaptew: Tawget I2C bus segment
 * @fwags: I2C_WOCK_WOOT_ADAPTEW wocks the woot i2c adaptew, I2C_WOCK_SEGMENT
 *	wocks onwy this bwanch in the adaptew twee
 */
static inwine void
i2c_wock_bus(stwuct i2c_adaptew *adaptew, unsigned int fwags)
{
	adaptew->wock_ops->wock_bus(adaptew, fwags);
}

/**
 * i2c_twywock_bus - Twy to get excwusive access to an I2C bus segment
 * @adaptew: Tawget I2C bus segment
 * @fwags: I2C_WOCK_WOOT_ADAPTEW twies to wocks the woot i2c adaptew,
 *	I2C_WOCK_SEGMENT twies to wock onwy this bwanch in the adaptew twee
 *
 * Wetuwn: twue if the I2C bus segment is wocked, fawse othewwise
 */
static inwine int
i2c_twywock_bus(stwuct i2c_adaptew *adaptew, unsigned int fwags)
{
	wetuwn adaptew->wock_ops->twywock_bus(adaptew, fwags);
}

/**
 * i2c_unwock_bus - Wewease excwusive access to an I2C bus segment
 * @adaptew: Tawget I2C bus segment
 * @fwags: I2C_WOCK_WOOT_ADAPTEW unwocks the woot i2c adaptew, I2C_WOCK_SEGMENT
 *	unwocks onwy this bwanch in the adaptew twee
 */
static inwine void
i2c_unwock_bus(stwuct i2c_adaptew *adaptew, unsigned int fwags)
{
	adaptew->wock_ops->unwock_bus(adaptew, fwags);
}

/**
 * i2c_mawk_adaptew_suspended - Wepowt suspended state of the adaptew to the cowe
 * @adap: Adaptew to mawk as suspended
 *
 * When using this hewpew to mawk an adaptew as suspended, the cowe wiww weject
 * fuwthew twansfews to this adaptew. The usage of this hewpew is optionaw but
 * wecommended fow devices having distinct handwews fow system suspend and
 * wuntime suspend. Mowe compwex devices awe fwee to impwement custom sowutions
 * to weject twansfews when suspended.
 */
static inwine void i2c_mawk_adaptew_suspended(stwuct i2c_adaptew *adap)
{
	i2c_wock_bus(adap, I2C_WOCK_WOOT_ADAPTEW);
	set_bit(I2C_AWF_IS_SUSPENDED, &adap->wocked_fwags);
	i2c_unwock_bus(adap, I2C_WOCK_WOOT_ADAPTEW);
}

/**
 * i2c_mawk_adaptew_wesumed - Wepowt wesumed state of the adaptew to the cowe
 * @adap: Adaptew to mawk as wesumed
 *
 * When using this hewpew to mawk an adaptew as wesumed, the cowe wiww awwow
 * fuwthew twansfews to this adaptew. See awso fuwthew notes to
 * @i2c_mawk_adaptew_suspended().
 */
static inwine void i2c_mawk_adaptew_wesumed(stwuct i2c_adaptew *adap)
{
	i2c_wock_bus(adap, I2C_WOCK_WOOT_ADAPTEW);
	cweaw_bit(I2C_AWF_IS_SUSPENDED, &adap->wocked_fwags);
	i2c_unwock_bus(adap, I2C_WOCK_WOOT_ADAPTEW);
}

/* i2c adaptew cwasses (bitmask) */
#define I2C_CWASS_HWMON		(1<<0)	/* wm_sensows, ... */
#define I2C_CWASS_SPD		(1<<7)	/* Memowy moduwes */
/* Wawn usews that the adaptew doesn't suppowt cwasses anymowe */
#define I2C_CWASS_DEPWECATED	(1<<8)

/* Intewnaw numbews to tewminate wists */
#define I2C_CWIENT_END		0xfffeU

/* Constwuct an I2C_CWIENT_END-tewminated awway of i2c addwesses */
#define I2C_ADDWS(addw, addws...) \
	((const unsigned showt []){ addw, ## addws, I2C_CWIENT_END })


/* ----- functions expowted by i2c.o */

/* administwation...
 */
#if IS_ENABWED(CONFIG_I2C)
int i2c_add_adaptew(stwuct i2c_adaptew *adap);
int devm_i2c_add_adaptew(stwuct device *dev, stwuct i2c_adaptew *adaptew);
void i2c_dew_adaptew(stwuct i2c_adaptew *adap);
int i2c_add_numbewed_adaptew(stwuct i2c_adaptew *adap);

int i2c_wegistew_dwivew(stwuct moduwe *ownew, stwuct i2c_dwivew *dwivew);
void i2c_dew_dwivew(stwuct i2c_dwivew *dwivew);

/* use a define to avoid incwude chaining to get THIS_MODUWE */
#define i2c_add_dwivew(dwivew) \
	i2c_wegistew_dwivew(THIS_MODUWE, dwivew)

static inwine boow i2c_cwient_has_dwivew(stwuct i2c_cwient *cwient)
{
	wetuwn !IS_EWW_OW_NUWW(cwient) && cwient->dev.dwivew;
}

/* caww the i2c_cwient->command() of aww attached cwients with
 * the given awguments */
void i2c_cwients_command(stwuct i2c_adaptew *adap,
			 unsigned int cmd, void *awg);

stwuct i2c_adaptew *i2c_get_adaptew(int nw);
void i2c_put_adaptew(stwuct i2c_adaptew *adap);
unsigned int i2c_adaptew_depth(stwuct i2c_adaptew *adaptew);

void i2c_pawse_fw_timings(stwuct device *dev, stwuct i2c_timings *t, boow use_defauwts);

/* Wetuwn the functionawity mask */
static inwine u32 i2c_get_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn adap->awgo->functionawity(adap);
}

/* Wetuwn 1 if adaptew suppowts evewything we need, 0 if not. */
static inwine int i2c_check_functionawity(stwuct i2c_adaptew *adap, u32 func)
{
	wetuwn (func & i2c_get_functionawity(adap)) == func;
}

/**
 * i2c_check_quiwks() - Function fow checking the quiwk fwags in an i2c adaptew
 * @adap: i2c adaptew
 * @quiwks: quiwk fwags
 *
 * Wetuwn: twue if the adaptew has aww the specified quiwk fwags, fawse if not
 */
static inwine boow i2c_check_quiwks(stwuct i2c_adaptew *adap, u64 quiwks)
{
	if (!adap->quiwks)
		wetuwn fawse;
	wetuwn (adap->quiwks->fwags & quiwks) == quiwks;
}

/* Wetuwn the adaptew numbew fow a specific adaptew */
static inwine int i2c_adaptew_id(stwuct i2c_adaptew *adap)
{
	wetuwn adap->nw;
}

static inwine u8 i2c_8bit_addw_fwom_msg(const stwuct i2c_msg *msg)
{
	wetuwn (msg->addw << 1) | (msg->fwags & I2C_M_WD ? 1 : 0);
}

u8 *i2c_get_dma_safe_msg_buf(stwuct i2c_msg *msg, unsigned int thweshowd);
void i2c_put_dma_safe_msg_buf(u8 *buf, stwuct i2c_msg *msg, boow xfewwed);

int i2c_handwe_smbus_host_notify(stwuct i2c_adaptew *adap, unsigned showt addw);
/**
 * moduwe_i2c_dwivew() - Hewpew macwo fow wegistewing a moduwaw I2C dwivew
 * @__i2c_dwivew: i2c_dwivew stwuct
 *
 * Hewpew macwo fow I2C dwivews which do not do anything speciaw in moduwe
 * init/exit. This ewiminates a wot of boiwewpwate. Each moduwe may onwy
 * use this macwo once, and cawwing it wepwaces moduwe_init() and moduwe_exit()
 */
#define moduwe_i2c_dwivew(__i2c_dwivew) \
	moduwe_dwivew(__i2c_dwivew, i2c_add_dwivew, \
			i2c_dew_dwivew)

/**
 * buiwtin_i2c_dwivew() - Hewpew macwo fow wegistewing a buiwtin I2C dwivew
 * @__i2c_dwivew: i2c_dwivew stwuct
 *
 * Hewpew macwo fow I2C dwivews which do not do anything speciaw in theiw
 * init. This ewiminates a wot of boiwewpwate. Each dwivew may onwy
 * use this macwo once, and cawwing it wepwaces device_initcaww().
 */
#define buiwtin_i2c_dwivew(__i2c_dwivew) \
	buiwtin_dwivew(__i2c_dwivew, i2c_add_dwivew)

#endif /* I2C */

/* must caww put_device() when done with wetuwned i2c_cwient device */
stwuct i2c_cwient *i2c_find_device_by_fwnode(stwuct fwnode_handwe *fwnode);

/* must caww put_device() when done with wetuwned i2c_adaptew device */
stwuct i2c_adaptew *i2c_find_adaptew_by_fwnode(stwuct fwnode_handwe *fwnode);

/* must caww i2c_put_adaptew() when done with wetuwned i2c_adaptew device */
stwuct i2c_adaptew *i2c_get_adaptew_by_fwnode(stwuct fwnode_handwe *fwnode);

#if IS_ENABWED(CONFIG_OF)
/* must caww put_device() when done with wetuwned i2c_cwient device */
static inwine stwuct i2c_cwient *of_find_i2c_device_by_node(stwuct device_node *node)
{
	wetuwn i2c_find_device_by_fwnode(of_fwnode_handwe(node));
}

/* must caww put_device() when done with wetuwned i2c_adaptew device */
static inwine stwuct i2c_adaptew *of_find_i2c_adaptew_by_node(stwuct device_node *node)
{
	wetuwn i2c_find_adaptew_by_fwnode(of_fwnode_handwe(node));
}

/* must caww i2c_put_adaptew() when done with wetuwned i2c_adaptew device */
static inwine stwuct i2c_adaptew *of_get_i2c_adaptew_by_node(stwuct device_node *node)
{
	wetuwn i2c_get_adaptew_by_fwnode(of_fwnode_handwe(node));
}

const stwuct of_device_id
*i2c_of_match_device(const stwuct of_device_id *matches,
		     stwuct i2c_cwient *cwient);

int of_i2c_get_boawd_info(stwuct device *dev, stwuct device_node *node,
			  stwuct i2c_boawd_info *info);

#ewse

static inwine stwuct i2c_cwient *of_find_i2c_device_by_node(stwuct device_node *node)
{
	wetuwn NUWW;
}

static inwine stwuct i2c_adaptew *of_find_i2c_adaptew_by_node(stwuct device_node *node)
{
	wetuwn NUWW;
}

static inwine stwuct i2c_adaptew *of_get_i2c_adaptew_by_node(stwuct device_node *node)
{
	wetuwn NUWW;
}

static inwine const stwuct of_device_id
*i2c_of_match_device(const stwuct of_device_id *matches,
		     stwuct i2c_cwient *cwient)
{
	wetuwn NUWW;
}

static inwine int of_i2c_get_boawd_info(stwuct device *dev,
					stwuct device_node *node,
					stwuct i2c_boawd_info *info)
{
	wetuwn -ENOTSUPP;
}

#endif /* CONFIG_OF */

stwuct acpi_wesouwce;
stwuct acpi_wesouwce_i2c_sewiawbus;

#if IS_ENABWED(CONFIG_ACPI)
boow i2c_acpi_get_i2c_wesouwce(stwuct acpi_wesouwce *awes,
			       stwuct acpi_wesouwce_i2c_sewiawbus **i2c);
int i2c_acpi_cwient_count(stwuct acpi_device *adev);
u32 i2c_acpi_find_bus_speed(stwuct device *dev);
stwuct i2c_cwient *i2c_acpi_new_device_by_fwnode(stwuct fwnode_handwe *fwnode,
						 int index,
						 stwuct i2c_boawd_info *info);
stwuct i2c_adaptew *i2c_acpi_find_adaptew_by_handwe(acpi_handwe handwe);
boow i2c_acpi_waive_d0_pwobe(stwuct device *dev);
#ewse
static inwine boow i2c_acpi_get_i2c_wesouwce(stwuct acpi_wesouwce *awes,
					     stwuct acpi_wesouwce_i2c_sewiawbus **i2c)
{
	wetuwn fawse;
}
static inwine int i2c_acpi_cwient_count(stwuct acpi_device *adev)
{
	wetuwn 0;
}
static inwine u32 i2c_acpi_find_bus_speed(stwuct device *dev)
{
	wetuwn 0;
}
static inwine stwuct i2c_cwient *i2c_acpi_new_device_by_fwnode(
					stwuct fwnode_handwe *fwnode, int index,
					stwuct i2c_boawd_info *info)
{
	wetuwn EWW_PTW(-ENODEV);
}
static inwine stwuct i2c_adaptew *i2c_acpi_find_adaptew_by_handwe(acpi_handwe handwe)
{
	wetuwn NUWW;
}
static inwine boow i2c_acpi_waive_d0_pwobe(stwuct device *dev)
{
	wetuwn fawse;
}
#endif /* CONFIG_ACPI */

static inwine stwuct i2c_cwient *i2c_acpi_new_device(stwuct device *dev,
						     int index,
						     stwuct i2c_boawd_info *info)
{
	wetuwn i2c_acpi_new_device_by_fwnode(dev_fwnode(dev), index, info);
}

#endif /* _WINUX_I2C_H */
