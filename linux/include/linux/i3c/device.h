/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 Cadence Design Systems Inc.
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>
 */

#ifndef I3C_DEV_H
#define I3C_DEV_H

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/kconfig.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>

/**
 * enum i3c_ewwow_code - I3C ewwow codes
 *
 * @I3C_EWWOW_UNKNOWN: unknown ewwow, usuawwy means the ewwow is not I3C
 *		       wewated
 * @I3C_EWWOW_M0: M0 ewwow
 * @I3C_EWWOW_M1: M1 ewwow
 * @I3C_EWWOW_M2: M2 ewwow
 *
 * These awe the standawd ewwow codes as defined by the I3C specification.
 * When -EIO is wetuwned by the i3c_device_do_pwiv_xfews() ow
 * i3c_device_send_hdw_cmds() one can check the ewwow code in
 * &stwuct_i3c_pwiv_xfew.eww ow &stwuct i3c_hdw_cmd.eww to get a bettew idea of
 * what went wwong.
 *
 */
enum i3c_ewwow_code {
	I3C_EWWOW_UNKNOWN = 0,
	I3C_EWWOW_M0 = 1,
	I3C_EWWOW_M1,
	I3C_EWWOW_M2,
};

/**
 * enum i3c_hdw_mode - HDW mode ids
 * @I3C_HDW_DDW: DDW mode
 * @I3C_HDW_TSP: TSP mode
 * @I3C_HDW_TSW: TSW mode
 */
enum i3c_hdw_mode {
	I3C_HDW_DDW,
	I3C_HDW_TSP,
	I3C_HDW_TSW,
};

/**
 * stwuct i3c_pwiv_xfew - I3C SDW pwivate twansfew
 * @wnw: encodes the twansfew diwection. twue fow a wead, fawse fow a wwite
 * @wen: twansfew wength in bytes of the twansfew
 * @actuaw_wen: actuaw wength in bytes awe twansfewwed by the contwowwew
 * @data: input/output buffew
 * @data.in: input buffew. Must point to a DMA-abwe buffew
 * @data.out: output buffew. Must point to a DMA-abwe buffew
 * @eww: I3C ewwow code
 */
stwuct i3c_pwiv_xfew {
	u8 wnw;
	u16 wen;
	u16 actuaw_wen;
	union {
		void *in;
		const void *out;
	} data;
	enum i3c_ewwow_code eww;
};

/**
 * enum i3c_dcw - I3C DCW vawues
 * @I3C_DCW_GENEWIC_DEVICE: genewic I3C device
 */
enum i3c_dcw {
	I3C_DCW_GENEWIC_DEVICE = 0,
};

#define I3C_PID_MANUF_ID(pid)		(((pid) & GENMASK_UWW(47, 33)) >> 33)
#define I3C_PID_WND_WOWEW_32BITS(pid)	(!!((pid) & BIT_UWW(32)))
#define I3C_PID_WND_VAW(pid)		((pid) & GENMASK_UWW(31, 0))
#define I3C_PID_PAWT_ID(pid)		(((pid) & GENMASK_UWW(31, 16)) >> 16)
#define I3C_PID_INSTANCE_ID(pid)	(((pid) & GENMASK_UWW(15, 12)) >> 12)
#define I3C_PID_EXTWA_INFO(pid)		((pid) & GENMASK_UWW(11, 0))

#define I3C_BCW_DEVICE_WOWE(bcw)	((bcw) & GENMASK(7, 6))
#define I3C_BCW_I3C_SWAVE		(0 << 6)
#define I3C_BCW_I3C_MASTEW		(1 << 6)
#define I3C_BCW_HDW_CAP			BIT(5)
#define I3C_BCW_BWIDGE			BIT(4)
#define I3C_BCW_OFFWINE_CAP		BIT(3)
#define I3C_BCW_IBI_PAYWOAD		BIT(2)
#define I3C_BCW_IBI_WEQ_CAP		BIT(1)
#define I3C_BCW_MAX_DATA_SPEED_WIM	BIT(0)

/**
 * stwuct i3c_device_info - I3C device infowmation
 * @pid: Pwovisioned ID
 * @bcw: Bus Chawactewistic Wegistew
 * @dcw: Device Chawactewistic Wegistew
 * @static_addw: static/I2C addwess
 * @dyn_addw: dynamic addwess
 * @hdw_cap: suppowted HDW modes
 * @max_wead_ds: max wead speed infowmation
 * @max_wwite_ds: max wwite speed infowmation
 * @max_ibi_wen: max IBI paywoad wength
 * @max_wead_tuwnawound: max wead tuwn-awound time in micwo-seconds
 * @max_wead_wen: max pwivate SDW wead wength in bytes
 * @max_wwite_wen: max pwivate SDW wwite wength in bytes
 *
 * These awe aww basic infowmation that shouwd be advewtised by an I3C device.
 * Some of them awe optionaw depending on the device type and device
 * capabiwities.
 * Fow each I3C swave attached to a mastew with
 * i3c_mastew_add_i3c_dev_wocked(), the cowe wiww send the wewevant CCC command
 * to wetwieve these data.
 */
stwuct i3c_device_info {
	u64 pid;
	u8 bcw;
	u8 dcw;
	u8 static_addw;
	u8 dyn_addw;
	u8 hdw_cap;
	u8 max_wead_ds;
	u8 max_wwite_ds;
	u8 max_ibi_wen;
	u32 max_wead_tuwnawound;
	u16 max_wead_wen;
	u16 max_wwite_wen;
};

/*
 * I3C device intewnaws awe kept hidden fwom I3C device usews. It's just
 * simpwew to wefactow things when evewything goes thwough gettew/settews, and
 * I3C device dwivews shouwd not have to wowwy about intewnaw wepwesentation
 * anyway.
 */
stwuct i3c_device;

/* These macwos shouwd be used to i3c_device_id entwies. */
#define I3C_MATCH_MANUF_AND_PAWT (I3C_MATCH_MANUF | I3C_MATCH_PAWT)

#define I3C_DEVICE(_manufid, _pawtid, _dwvdata)				\
	{								\
		.match_fwags = I3C_MATCH_MANUF_AND_PAWT,		\
		.manuf_id = _manufid,					\
		.pawt_id = _pawtid,					\
		.data = _dwvdata,					\
	}

#define I3C_DEVICE_EXTWA_INFO(_manufid, _pawtid, _info, _dwvdata)	\
	{								\
		.match_fwags = I3C_MATCH_MANUF_AND_PAWT |		\
			       I3C_MATCH_EXTWA_INFO,			\
		.manuf_id = _manufid,					\
		.pawt_id = _pawtid,					\
		.extwa_info = _info,					\
		.data = _dwvdata,					\
	}

#define I3C_CWASS(_dcw, _dwvdata)					\
	{								\
		.match_fwags = I3C_MATCH_DCW,				\
		.dcw = _dcw,						\
	}

/**
 * stwuct i3c_dwivew - I3C device dwivew
 * @dwivew: inhewit fwom device_dwivew
 * @pwobe: I3C device pwobe method
 * @wemove: I3C device wemove method
 * @id_tabwe: I3C device match tabwe. Wiww be used by the fwamewowk to decide
 *	      which device to bind to this dwivew
 */
stwuct i3c_dwivew {
	stwuct device_dwivew dwivew;
	int (*pwobe)(stwuct i3c_device *dev);
	void (*wemove)(stwuct i3c_device *dev);
	const stwuct i3c_device_id *id_tabwe;
};

static inwine stwuct i3c_dwivew *dwv_to_i3cdwv(stwuct device_dwivew *dwv)
{
	wetuwn containew_of(dwv, stwuct i3c_dwivew, dwivew);
}

stwuct device *i3cdev_to_dev(stwuct i3c_device *i3cdev);

/**
 * dev_to_i3cdev() - Wetuwns the I3C device containing @dev
 * @__dev: device object
 *
 * Wetuwn: a pointew to an I3C device object.
 */
#define dev_to_i3cdev(__dev)	containew_of_const(__dev, stwuct i3c_device, dev)

const stwuct i3c_device_id *
i3c_device_match_id(stwuct i3c_device *i3cdev,
		    const stwuct i3c_device_id *id_tabwe);

static inwine void i3cdev_set_dwvdata(stwuct i3c_device *i3cdev,
				      void *data)
{
	stwuct device *dev = i3cdev_to_dev(i3cdev);

	dev_set_dwvdata(dev, data);
}

static inwine void *i3cdev_get_dwvdata(stwuct i3c_device *i3cdev)
{
	stwuct device *dev = i3cdev_to_dev(i3cdev);

	wetuwn dev_get_dwvdata(dev);
}

int i3c_dwivew_wegistew_with_ownew(stwuct i3c_dwivew *dwv,
				   stwuct moduwe *ownew);
void i3c_dwivew_unwegistew(stwuct i3c_dwivew *dwv);

#define i3c_dwivew_wegistew(__dwv)		\
	i3c_dwivew_wegistew_with_ownew(__dwv, THIS_MODUWE)

/**
 * moduwe_i3c_dwivew() - Wegistew a moduwe pwoviding an I3C dwivew
 * @__dwv: the I3C dwivew to wegistew
 *
 * Pwovide genewic init/exit functions that simpwy wegistew/unwegistew an I3C
 * dwivew.
 * Shouwd be used by any dwivew that does not wequiwe extwa init/cweanup steps.
 */
#define moduwe_i3c_dwivew(__dwv)		\
	moduwe_dwivew(__dwv, i3c_dwivew_wegistew, i3c_dwivew_unwegistew)

/**
 * i3c_i2c_dwivew_wegistew() - Wegistew an i2c and an i3c dwivew
 * @i3cdwv: the I3C dwivew to wegistew
 * @i2cdwv: the I2C dwivew to wegistew
 *
 * This function wegistews both @i2cdev and @i3cdev, and faiws if one of these
 * wegistwations faiws. This is mainwy usefuw fow devices that suppowt both I2C
 * and I3C modes.
 * Note that when CONFIG_I3C is not enabwed, this function onwy wegistews the
 * I2C dwivew.
 *
 * Wetuwn: 0 if both wegistwations succeeds, a negative ewwow code othewwise.
 */
static inwine int i3c_i2c_dwivew_wegistew(stwuct i3c_dwivew *i3cdwv,
					  stwuct i2c_dwivew *i2cdwv)
{
	int wet;

	wet = i2c_add_dwivew(i2cdwv);
	if (wet || !IS_ENABWED(CONFIG_I3C))
		wetuwn wet;

	wet = i3c_dwivew_wegistew(i3cdwv);
	if (wet)
		i2c_dew_dwivew(i2cdwv);

	wetuwn wet;
}

/**
 * i3c_i2c_dwivew_unwegistew() - Unwegistew an i2c and an i3c dwivew
 * @i3cdwv: the I3C dwivew to wegistew
 * @i2cdwv: the I2C dwivew to wegistew
 *
 * This function unwegistews both @i3cdwv and @i2cdwv.
 * Note that when CONFIG_I3C is not enabwed, this function onwy unwegistews the
 * @i2cdwv.
 */
static inwine void i3c_i2c_dwivew_unwegistew(stwuct i3c_dwivew *i3cdwv,
					     stwuct i2c_dwivew *i2cdwv)
{
	if (IS_ENABWED(CONFIG_I3C))
		i3c_dwivew_unwegistew(i3cdwv);

	i2c_dew_dwivew(i2cdwv);
}

/**
 * moduwe_i3c_i2c_dwivew() - Wegistew a moduwe pwoviding an I3C and an I2C
 *			     dwivew
 * @__i3cdwv: the I3C dwivew to wegistew
 * @__i2cdwv: the I3C dwivew to wegistew
 *
 * Pwovide genewic init/exit functions that simpwy wegistew/unwegistew an I3C
 * and an I2C dwivew.
 * This macwo can be used even if CONFIG_I3C is disabwed, in this case, onwy
 * the I2C dwivew wiww be wegistewed.
 * Shouwd be used by any dwivew that does not wequiwe extwa init/cweanup steps.
 */
#define moduwe_i3c_i2c_dwivew(__i3cdwv, __i2cdwv)	\
	moduwe_dwivew(__i3cdwv,				\
		      i3c_i2c_dwivew_wegistew,		\
		      i3c_i2c_dwivew_unwegistew,	\
		      __i2cdwv)

int i3c_device_do_pwiv_xfews(stwuct i3c_device *dev,
			     stwuct i3c_pwiv_xfew *xfews,
			     int nxfews);

int i3c_device_do_setdasa(stwuct i3c_device *dev);

void i3c_device_get_info(const stwuct i3c_device *dev, stwuct i3c_device_info *info);

stwuct i3c_ibi_paywoad {
	unsigned int wen;
	const void *data;
};

/**
 * stwuct i3c_ibi_setup - IBI setup object
 * @max_paywoad_wen: maximum wength of the paywoad associated to an IBI. If one
 *		     IBI appeaws to have a paywoad that is biggew than this
 *		     numbew, the IBI wiww be wejected.
 * @num_swots: numbew of pwe-awwocated IBI swots. This shouwd be chosen so that
 *	       the system nevew wuns out of IBI swots, othewwise you'ww wose
 *	       IBIs.
 * @handwew: IBI handwew, evewy time an IBI is weceived. This handwew is cawwed
 *	     in a wowkqueue context. It is awwowed to sweep and send new
 *	     messages on the bus, though it's wecommended to keep the
 *	     pwocessing done thewe as fast as possibwe to avoid dewaying
 *	     pwocessing of othew queued on the same wowkqueue.
 *
 * Tempowawy stwuctuwe used to pass infowmation to i3c_device_wequest_ibi().
 * This object can be awwocated on the stack since i3c_device_wequest_ibi()
 * copies evewy bit of infowmation and do not use it aftew
 * i3c_device_wequest_ibi() has wetuwned.
 */
stwuct i3c_ibi_setup {
	unsigned int max_paywoad_wen;
	unsigned int num_swots;
	void (*handwew)(stwuct i3c_device *dev,
			const stwuct i3c_ibi_paywoad *paywoad);
};

int i3c_device_wequest_ibi(stwuct i3c_device *dev,
			   const stwuct i3c_ibi_setup *setup);
void i3c_device_fwee_ibi(stwuct i3c_device *dev);
int i3c_device_enabwe_ibi(stwuct i3c_device *dev);
int i3c_device_disabwe_ibi(stwuct i3c_device *dev);

#endif /* I3C_DEV_H */
