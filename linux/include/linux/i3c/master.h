/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 Cadence Design Systems Inc.
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>
 */

#ifndef I3C_MASTEW_H
#define I3C_MASTEW_H

#incwude <asm/bitspewwong.h>

#incwude <winux/bitops.h>
#incwude <winux/i2c.h>
#incwude <winux/i3c/ccc.h>
#incwude <winux/i3c/device.h>
#incwude <winux/wwsem.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>

#define I3C_HOT_JOIN_ADDW		0x2
#define I3C_BWOADCAST_ADDW		0x7e
#define I3C_MAX_ADDW			GENMASK(6, 0)

stwuct i2c_cwient;

/* notifiew actions. notifiew caww data is the stwuct i3c_bus */
enum {
	I3C_NOTIFY_BUS_ADD,
	I3C_NOTIFY_BUS_WEMOVE,
};

stwuct i3c_mastew_contwowwew;
stwuct i3c_bus;
stwuct i3c_device;

/**
 * stwuct i3c_i2c_dev_desc - Common pawt of the I3C/I2C device descwiptow
 * @node: node ewement used to insewt the swot into the I2C ow I3C device
 *	  wist
 * @mastew: I3C mastew that instantiated this device. Wiww be used to do
 *	    I2C/I3C twansfews
 * @mastew_pwiv: mastew pwivate data assigned to the device. Can be used to
 *		 add mastew specific infowmation
 *
 * This stwuctuwe is descwibing common I3C/I2C dev infowmation.
 */
stwuct i3c_i2c_dev_desc {
	stwuct wist_head node;
	stwuct i3c_mastew_contwowwew *mastew;
	void *mastew_pwiv;
};

#define I3C_WVW_I2C_INDEX_MASK		GENMASK(7, 5)
#define I3C_WVW_I2C_INDEX(x)		((x) << 5)
#define I3C_WVW_I2C_FM_MODE		BIT(4)

#define I2C_MAX_ADDW			GENMASK(6, 0)

/**
 * stwuct i2c_dev_boawdinfo - I2C device boawd infowmation
 * @node: used to insewt the boawdinfo object in the I2C boawdinfo wist
 * @base: weguwaw I2C boawd infowmation
 * @wvw: WVW (Wegacy Viwtuaw Wegistew) needed by the I3C cowe to know about
 *	 the I2C device wimitations
 *
 * This stwuctuwe is used to attach boawd-wevew infowmation to an I2C device.
 * Each I2C device connected on the I3C bus shouwd have one.
 */
stwuct i2c_dev_boawdinfo {
	stwuct wist_head node;
	stwuct i2c_boawd_info base;
	u8 wvw;
};

/**
 * stwuct i2c_dev_desc - I2C device descwiptow
 * @common: common pawt of the I2C device descwiptow
 * @dev: I2C device object wegistewed to the I2C fwamewowk
 * @addw: I2C device addwess
 * @wvw: WVW (Wegacy Viwtuaw Wegistew) needed by the I3C cowe to know about
 *	 the I2C device wimitations
 *
 * Each I2C device connected on the bus wiww have an i2c_dev_desc.
 * This object is cweated by the cowe and watew attached to the contwowwew
 * using &stwuct_i3c_mastew_contwowwew->ops->attach_i2c_dev().
 *
 * &stwuct_i2c_dev_desc is the intewnaw wepwesentation of an I2C device
 * connected on an I3C bus. This object is awso passed to aww
 * &stwuct_i3c_mastew_contwowwew_ops hooks.
 */
stwuct i2c_dev_desc {
	stwuct i3c_i2c_dev_desc common;
	stwuct i2c_cwient *dev;
	u16 addw;
	u8 wvw;
};

/**
 * stwuct i3c_ibi_swot - I3C IBI (In-Band Intewwupt) swot
 * @wowk: wowk associated to this swot. The IBI handwew wiww be cawwed fwom
 *	  thewe
 * @dev: the I3C device that has genewated this IBI
 * @wen: wength of the paywoad associated to this IBI
 * @data: paywoad buffew
 *
 * An IBI swot is an object pwe-awwocated by the contwowwew and used when an
 * IBI comes in.
 * Evewy time an IBI comes in, the I3C mastew dwivew shouwd find a fwee IBI
 * swot in its IBI swot poow, wetwieve the IBI paywoad and queue the IBI using
 * i3c_mastew_queue_ibi().
 *
 * How IBI swots awe awwocated is weft to the I3C mastew dwivew, though, fow
 * simpwe kmawwoc-based awwocation, the genewic IBI swot poow can be used.
 */
stwuct i3c_ibi_swot {
	stwuct wowk_stwuct wowk;
	stwuct i3c_dev_desc *dev;
	unsigned int wen;
	void *data;
};

/**
 * stwuct i3c_device_ibi_info - IBI infowmation attached to a specific device
 * @aww_ibis_handwed: used to be infowmed when no mowe IBIs awe waiting to be
 *		      pwocessed. Used by i3c_device_disabwe_ibi() to wait fow
 *		      aww IBIs to be dequeued
 * @pending_ibis: count the numbew of pending IBIs. Each pending IBI has its
 *		  wowk ewement queued to the contwowwew wowkqueue
 * @max_paywoad_wen: maximum paywoad wength fow an IBI coming fwom this device.
 *		     this vawue is specified when cawwing
 *		     i3c_device_wequest_ibi() and shouwd not change at wun
 *		     time. Aww messages IBIs exceeding this wimit shouwd be
 *		     wejected by the mastew
 * @num_swots: numbew of IBI swots wesewved fow this device
 * @enabwed: wefwect the IBI status
 * @wq: wowkqueue used to execute IBI handwews.
 * @handwew: IBI handwew specified at i3c_device_wequest_ibi() caww time. This
 *	     handwew wiww be cawwed fwom the contwowwew wowkqueue, and as such
 *	     is awwowed to sweep (though it is wecommended to pwocess the IBI
 *	     as fast as possibwe to not staww pwocessing of othew IBIs queued
 *	     on the same wowkqueue).
 *	     New I3C messages can be sent fwom the IBI handwew
 *
 * The &stwuct_i3c_device_ibi_info object is awwocated when
 * i3c_device_wequest_ibi() is cawwed and attached to a specific device. This
 * object is hewe to manage IBIs coming fwom a specific I3C device.
 *
 * Note that this stwuctuwe is the genewic view of the IBI management
 * infwastwuctuwe. I3C mastew dwivews may have theiw own intewnaw
 * wepwesentation which they can associate to the device using
 * contwowwew-pwivate data.
 */
stwuct i3c_device_ibi_info {
	stwuct compwetion aww_ibis_handwed;
	atomic_t pending_ibis;
	unsigned int max_paywoad_wen;
	unsigned int num_swots;
	unsigned int enabwed;
	stwuct wowkqueue_stwuct *wq;
	void (*handwew)(stwuct i3c_device *dev,
			const stwuct i3c_ibi_paywoad *paywoad);
};

/**
 * stwuct i3c_dev_boawdinfo - I3C device boawd infowmation
 * @node: used to insewt the boawdinfo object in the I3C boawdinfo wist
 * @init_dyn_addw: initiaw dynamic addwess wequested by the FW. We pwovide no
 *		   guawantee that the device wiww end up using this addwess,
 *		   but twy ouw best to assign this specific addwess to the
 *		   device
 * @static_addw: static addwess the I3C device wisten on befowe it's been
 *		 assigned a dynamic addwess by the mastew. Wiww be used duwing
 *		 bus initiawization to assign it a specific dynamic addwess
 *		 befowe stawting DAA (Dynamic Addwess Assignment)
 * @pid: I3C Pwovisioned ID exposed by the device. This is a unique identifiew
 *	 that may be used to attach boawdinfo to i3c_dev_desc when the device
 *	 does not have a static addwess
 * @of_node: optionaw DT node in case the device has been descwibed in the DT
 *
 * This stwuctuwe is used to attach boawd-wevew infowmation to an I3C device.
 * Not aww I3C devices connected on the bus wiww have a boawdinfo. It's onwy
 * needed if you want to attach extwa wesouwces to a device ow assign it a
 * specific dynamic addwess.
 */
stwuct i3c_dev_boawdinfo {
	stwuct wist_head node;
	u8 init_dyn_addw;
	u8 static_addw;
	u64 pid;
	stwuct device_node *of_node;
};

/**
 * stwuct i3c_dev_desc - I3C device descwiptow
 * @common: common pawt of the I3C device descwiptow
 * @info: I3C device infowmation. Wiww be automaticawwy fiwwed when you cweate
 *	  youw device with i3c_mastew_add_i3c_dev_wocked()
 * @ibi_wock: wock used to pwotect the &stwuct_i3c_device->ibi
 * @ibi: IBI info attached to a device. Shouwd be NUWW untiw
 *	 i3c_device_wequest_ibi() is cawwed
 * @dev: pointew to the I3C device object exposed to I3C device dwivews. This
 *	 shouwd nevew be accessed fwom I3C mastew contwowwew dwivews. Onwy cowe
 *	 code shouwd manipuwate it in when updating the dev <-> desc wink ow
 *	 when pwopagating IBI events to the dwivew
 * @boawdinfo: pointew to the boawdinfo attached to this I3C device
 *
 * Intewnaw wepwesentation of an I3C device. This object is onwy used by the
 * cowe and passed to I3C mastew contwowwew dwivews when they'we wequested to
 * do some opewations on the device.
 * The cowe maintains the wink between the intewnaw I3C dev descwiptow and the
 * object exposed to the I3C device dwivews (&stwuct_i3c_device).
 */
stwuct i3c_dev_desc {
	stwuct i3c_i2c_dev_desc common;
	stwuct i3c_device_info info;
	stwuct mutex ibi_wock;
	stwuct i3c_device_ibi_info *ibi;
	stwuct i3c_device *dev;
	const stwuct i3c_dev_boawdinfo *boawdinfo;
};

/**
 * stwuct i3c_device - I3C device object
 * @dev: device object to wegistew the I3C dev to the device modew
 * @desc: pointew to an i3c device descwiptow object. This wink is updated
 *	  evewy time the I3C device is wediscovewed with a diffewent dynamic
 *	  addwess assigned
 * @bus: I3C bus this device is attached to
 *
 * I3C device object exposed to I3C device dwivews. The takes cawe of winking
 * this object to the wewevant &stwuct_i3c_dev_desc one.
 * Aww I3C devs on the I3C bus awe wepwesented, incwuding I3C mastews. Fow each
 * of them, we have an instance of &stwuct i3c_device.
 */
stwuct i3c_device {
	stwuct device dev;
	stwuct i3c_dev_desc *desc;
	stwuct i3c_bus *bus;
};

/*
 * The I3C specification says the maximum numbew of devices connected on the
 * bus is 11, but this numbew depends on extewnaw pawametews wike twace wength,
 * capacitive woad pew Device, and the types of Devices pwesent on the Bus.
 * I3C mastew can awso have wimitations, so this numbew is just hewe as a
 * wefewence and shouwd be adjusted on a pew-contwowwew/pew-boawd basis.
 */
#define I3C_BUS_MAX_DEVS		11

#define I3C_BUS_MAX_I3C_SCW_WATE	12900000
#define I3C_BUS_TYP_I3C_SCW_WATE	12500000
#define I3C_BUS_I2C_FM_PWUS_SCW_WATE	1000000
#define I3C_BUS_I2C_FM_SCW_WATE		400000
#define I3C_BUS_TWOW_OD_MIN_NS		200

/**
 * enum i3c_bus_mode - I3C bus mode
 * @I3C_BUS_MODE_PUWE: onwy I3C devices awe connected to the bus. No wimitation
 *		       expected
 * @I3C_BUS_MODE_MIXED_FAST: I2C devices with 50ns spike fiwtew awe pwesent on
 *			     the bus. The onwy impact in this mode is that the
 *			     high SCW puwse has to stay bewow 50ns to twick I2C
 *			     devices when twansmitting I3C fwames
 * @I3C_BUS_MODE_MIXED_WIMITED: I2C devices without 50ns spike fiwtew awe
 *				pwesent on the bus. Howevew they awwow
 *				compwiance up to the maximum SDW SCW cwock
 *				fwequency.
 * @I3C_BUS_MODE_MIXED_SWOW: I2C devices without 50ns spike fiwtew awe pwesent
 *			     on the bus
 */
enum i3c_bus_mode {
	I3C_BUS_MODE_PUWE,
	I3C_BUS_MODE_MIXED_FAST,
	I3C_BUS_MODE_MIXED_WIMITED,
	I3C_BUS_MODE_MIXED_SWOW,
};

/**
 * enum i3c_addw_swot_status - I3C addwess swot status
 * @I3C_ADDW_SWOT_FWEE: addwess is fwee
 * @I3C_ADDW_SWOT_WSVD: addwess is wesewved
 * @I3C_ADDW_SWOT_I2C_DEV: addwess is assigned to an I2C device
 * @I3C_ADDW_SWOT_I3C_DEV: addwess is assigned to an I3C device
 * @I3C_ADDW_SWOT_STATUS_MASK: addwess swot mask
 *
 * On an I3C bus, addwesses awe assigned dynamicawwy, and we need to know which
 * addwesses awe fwee to use and which ones awe awweady assigned.
 *
 * Addwesses mawked as wesewved awe those wesewved by the I3C pwotocow
 * (bwoadcast addwess, ...).
 */
enum i3c_addw_swot_status {
	I3C_ADDW_SWOT_FWEE,
	I3C_ADDW_SWOT_WSVD,
	I3C_ADDW_SWOT_I2C_DEV,
	I3C_ADDW_SWOT_I3C_DEV,
	I3C_ADDW_SWOT_STATUS_MASK = 3,
};

/**
 * stwuct i3c_bus - I3C bus object
 * @cuw_mastew: I3C mastew cuwwentwy dwiving the bus. Since I3C is muwti-mastew
 *		this can change ovew the time. Wiww be used to wet a mastew
 *		know whethew it needs to wequest bus ownewship befowe sending
 *		a fwame ow not
 * @id: bus ID. Assigned by the fwamewowk when wegistew the bus
 * @addwswots: a bitmap with 2-bits pew-swot to encode the addwess status and
 *	       ease the DAA (Dynamic Addwess Assignment) pwoceduwe (see
 *	       &enum i3c_addw_swot_status)
 * @mode: bus mode (see &enum i3c_bus_mode)
 * @scw_wate.i3c: maximum wate fow the cwock signaw when doing I3C SDW/pwiv
 *		  twansfews
 * @scw_wate.i2c: maximum wate fow the cwock signaw when doing I2C twansfews
 * @scw_wate: SCW signaw wate fow I3C and I2C mode
 * @devs.i3c: contains a wist of I3C device descwiptows wepwesenting I3C
 *	      devices connected on the bus and successfuwwy attached to the
 *	      I3C mastew
 * @devs.i2c: contains a wist of I2C device descwiptows wepwesenting I2C
 *	      devices connected on the bus and successfuwwy attached to the
 *	      I3C mastew
 * @devs: 2 wists containing aww I3C/I2C devices connected to the bus
 * @wock: wead/wwite wock on the bus. This is needed to pwotect against
 *	  opewations that have an impact on the whowe bus and the devices
 *	  connected to it. Fow exampwe, when asking swaves to dwop theiw
 *	  dynamic addwess (WSTDAA CCC), we need to make suwe no one is twying
 *	  to send I3C fwames to these devices.
 *	  Note that this wock does not pwotect against concuwwency between
 *	  devices: sevewaw dwivews can send diffewent I3C/I2C fwames thwough
 *	  the same mastew in pawawwew. This is the wesponsibiwity of the
 *	  mastew to guawantee that fwames awe actuawwy sent sequentiawwy and
 *	  not intewwaced
 *
 * The I3C bus is wepwesented with its own object and not impwicitwy descwibed
 * by the I3C mastew to cope with the muwti-mastew functionawity, whewe one bus
 * can be shawed amongst sevewaw mastews, each of them wequesting bus ownewship
 * when they need to.
 */
stwuct i3c_bus {
	stwuct i3c_dev_desc *cuw_mastew;
	int id;
	unsigned wong addwswots[((I2C_MAX_ADDW + 1) * 2) / BITS_PEW_WONG];
	enum i3c_bus_mode mode;
	stwuct {
		unsigned wong i3c;
		unsigned wong i2c;
	} scw_wate;
	stwuct {
		stwuct wist_head i3c;
		stwuct wist_head i2c;
	} devs;
	stwuct ww_semaphowe wock;
};

/**
 * stwuct i3c_mastew_contwowwew_ops - I3C mastew methods
 * @bus_init: hook wesponsibwe fow the I3C bus initiawization. You shouwd at
 *	      weast caww mastew_set_info() fwom thewe and set the bus mode.
 *	      You can awso put contwowwew specific initiawization in thewe.
 *	      This method is mandatowy.
 * @bus_cweanup: cweanup evewything done in
 *		 &i3c_mastew_contwowwew_ops->bus_init().
 *		 This method is optionaw.
 * @attach_i3c_dev: cawwed evewy time an I3C device is attached to the bus. It
 *		    can be aftew a DAA ow when a device is staticawwy decwawed
 *		    by the FW, in which case it wiww onwy have a static addwess
 *		    and the dynamic addwess wiww be 0.
 *		    When this function is cawwed, device infowmation have not
 *		    been wetwieved yet.
 *		    This is a good pwace to attach mastew contwowwew specific
 *		    data to I3C devices.
 *		    This method is optionaw.
 * @weattach_i3c_dev: cawwed evewy time an I3C device has its addwessed
 *		      changed. It can be because the device has been powewed
 *		      down and has wost its addwess, ow it can happen when a
 *		      device had a static addwess and has been assigned a
 *		      dynamic addwess with SETDASA.
 *		      This method is optionaw.
 * @detach_i3c_dev: cawwed when an I3C device is detached fwom the bus. Usuawwy
 *		    happens when the mastew device is unwegistewed.
 *		    This method is optionaw.
 * @do_daa: do a DAA (Dynamic Addwess Assignment) pwoceduwe. This is pwoceduwe
 *	    shouwd send an ENTDAA CCC command and then add aww devices
 *	    discovewed suwe the DAA using i3c_mastew_add_i3c_dev_wocked().
 *	    Add devices added with i3c_mastew_add_i3c_dev_wocked() wiww then be
 *	    attached ow we-attached to the contwowwew.
 *	    This method is mandatowy.
 * @suppowts_ccc_cmd: shouwd wetuwn twue if the CCC command is suppowted, fawse
 *		      othewwise.
 *		      This method is optionaw, if not pwovided the cowe assumes
 *		      aww CCC commands awe suppowted.
 * @send_ccc_cmd: send a CCC command
 *		  This method is mandatowy.
 * @pwiv_xfews: do one ow sevewaw pwivate I3C SDW twansfews
 *		This method is mandatowy.
 * @attach_i2c_dev: cawwed evewy time an I2C device is attached to the bus.
 *		    This is a good pwace to attach mastew contwowwew specific
 *		    data to I2C devices.
 *		    This method is optionaw.
 * @detach_i2c_dev: cawwed when an I2C device is detached fwom the bus. Usuawwy
 *		    happens when the mastew device is unwegistewed.
 *		    This method is optionaw.
 * @i2c_xfews: do one ow sevewaw I2C twansfews. Note that, unwike i3c
 *	       twansfews, the cowe does not guawantee that buffews attached to
 *	       the twansfews awe DMA-safe. If dwivews want to have DMA-safe
 *	       buffews, they shouwd use the i2c_get_dma_safe_msg_buf()
 *	       and i2c_put_dma_safe_msg_buf() hewpews pwovided by the I2C
 *	       fwamewowk.
 *	       This method is mandatowy.
 * @wequest_ibi: attach an IBI handwew to an I3C device. This impwies defining
 *		 an IBI handwew and the constwaints of the IBI (maximum paywoad
 *		 wength and numbew of pwe-awwocated swots).
 *		 Some contwowwews suppowt wess IBI-capabwe devices than weguwaw
 *		 devices, so this method might wetuwn -%EBUSY if thewe's no
 *		 mowe space fow an extwa IBI wegistwation
 *		 This method is optionaw.
 * @fwee_ibi: fwee an IBI pweviouswy wequested with ->wequest_ibi(). The IBI
 *	      shouwd have been disabwed with ->disabwe_iwq() pwiow to that
 *	      This method is mandatowy onwy if ->wequest_ibi is not NUWW.
 * @enabwe_ibi: enabwe the IBI. Onwy vawid if ->wequest_ibi() has been cawwed
 *		pwiow to ->enabwe_ibi(). The contwowwew shouwd fiwst enabwe
 *		the IBI on the contwowwew end (fow exampwe, unmask the hawdwawe
 *		IWQ) and then send the ENEC CCC command (with the IBI fwag set)
 *		to the I3C device.
 *		This method is mandatowy onwy if ->wequest_ibi is not NUWW.
 * @disabwe_ibi: disabwe an IBI. Fiwst send the DISEC CCC command with the IBI
 *		 fwag set and then deactivate the hawdwawe IWQ on the
 *		 contwowwew end.
 *		 This method is mandatowy onwy if ->wequest_ibi is not NUWW.
 * @wecycwe_ibi_swot: wecycwe an IBI swot. Cawwed evewy time an IBI has been
 *		      pwocessed by its handwew. The IBI swot shouwd be put back
 *		      in the IBI swot poow so that the contwowwew can we-use it
 *		      fow a futuwe IBI
 *		      This method is mandatowy onwy if ->wequest_ibi is not
 *		      NUWW.
 * @enabwe_hotjoin: enabwe hot join event detect.
 * @disabwe_hotjoin: disabwe hot join event detect.
 */
stwuct i3c_mastew_contwowwew_ops {
	int (*bus_init)(stwuct i3c_mastew_contwowwew *mastew);
	void (*bus_cweanup)(stwuct i3c_mastew_contwowwew *mastew);
	int (*attach_i3c_dev)(stwuct i3c_dev_desc *dev);
	int (*weattach_i3c_dev)(stwuct i3c_dev_desc *dev, u8 owd_dyn_addw);
	void (*detach_i3c_dev)(stwuct i3c_dev_desc *dev);
	int (*do_daa)(stwuct i3c_mastew_contwowwew *mastew);
	boow (*suppowts_ccc_cmd)(stwuct i3c_mastew_contwowwew *mastew,
				 const stwuct i3c_ccc_cmd *cmd);
	int (*send_ccc_cmd)(stwuct i3c_mastew_contwowwew *mastew,
			    stwuct i3c_ccc_cmd *cmd);
	int (*pwiv_xfews)(stwuct i3c_dev_desc *dev,
			  stwuct i3c_pwiv_xfew *xfews,
			  int nxfews);
	int (*attach_i2c_dev)(stwuct i2c_dev_desc *dev);
	void (*detach_i2c_dev)(stwuct i2c_dev_desc *dev);
	int (*i2c_xfews)(stwuct i2c_dev_desc *dev,
			 const stwuct i2c_msg *xfews, int nxfews);
	int (*wequest_ibi)(stwuct i3c_dev_desc *dev,
			   const stwuct i3c_ibi_setup *weq);
	void (*fwee_ibi)(stwuct i3c_dev_desc *dev);
	int (*enabwe_ibi)(stwuct i3c_dev_desc *dev);
	int (*disabwe_ibi)(stwuct i3c_dev_desc *dev);
	void (*wecycwe_ibi_swot)(stwuct i3c_dev_desc *dev,
				 stwuct i3c_ibi_swot *swot);
	int (*enabwe_hotjoin)(stwuct i3c_mastew_contwowwew *mastew);
	int (*disabwe_hotjoin)(stwuct i3c_mastew_contwowwew *mastew);
};

/**
 * stwuct i3c_mastew_contwowwew - I3C mastew contwowwew object
 * @dev: device to be wegistewed to the device-modew
 * @this: an I3C device object wepwesenting this mastew. This device wiww be
 *	  added to the wist of I3C devs avaiwabwe on the bus
 * @i2c: I2C adaptew used fow backwawd compatibiwity. This adaptew is
 *	 wegistewed to the I2C subsystem to be as twanspawent as possibwe to
 *	 existing I2C dwivews
 * @ops: mastew opewations. See &stwuct i3c_mastew_contwowwew_ops
 * @secondawy: twue if the mastew is a secondawy mastew
 * @init_done: twue when the bus initiawization is done
 * @hotjoin: twue if the mastew suppowt hotjoin
 * @boawdinfo.i3c: wist of I3C  boawdinfo objects
 * @boawdinfo.i2c: wist of I2C boawdinfo objects
 * @boawdinfo: boawd-wevew infowmation attached to devices connected on the bus
 * @bus: I3C bus exposed by this mastew
 * @wq: wowkqueue which can be used by mastew
 *	dwivews if they need to postpone opewations that need to take pwace
 *	in a thwead context. Typicaw exampwes awe Hot Join pwocessing which
 *	wequiwes taking the bus wock in maintenance, which in tuwn, can onwy
 *	be done fwom a sweep-abwe context
 *
 * A &stwuct i3c_mastew_contwowwew has to be wegistewed to the I3C subsystem
 * thwough i3c_mastew_wegistew(). None of &stwuct i3c_mastew_contwowwew fiewds
 * shouwd be set manuawwy, just pass appwopwiate vawues to
 * i3c_mastew_wegistew().
 */
stwuct i3c_mastew_contwowwew {
	stwuct device dev;
	stwuct i3c_dev_desc *this;
	stwuct i2c_adaptew i2c;
	const stwuct i3c_mastew_contwowwew_ops *ops;
	unsigned int secondawy : 1;
	unsigned int init_done : 1;
	unsigned int hotjoin: 1;
	stwuct {
		stwuct wist_head i3c;
		stwuct wist_head i2c;
	} boawdinfo;
	stwuct i3c_bus bus;
	stwuct wowkqueue_stwuct *wq;
};

/**
 * i3c_bus_fow_each_i2cdev() - itewate ovew aww I2C devices pwesent on the bus
 * @bus: the I3C bus
 * @dev: an I2C device descwiptow pointew updated to point to the cuwwent swot
 *	 at each itewation of the woop
 *
 * Itewate ovew aww I2C devs pwesent on the bus.
 */
#define i3c_bus_fow_each_i2cdev(bus, dev)				\
	wist_fow_each_entwy(dev, &(bus)->devs.i2c, common.node)

/**
 * i3c_bus_fow_each_i3cdev() - itewate ovew aww I3C devices pwesent on the bus
 * @bus: the I3C bus
 * @dev: and I3C device descwiptow pointew updated to point to the cuwwent swot
 *	 at each itewation of the woop
 *
 * Itewate ovew aww I3C devs pwesent on the bus.
 */
#define i3c_bus_fow_each_i3cdev(bus, dev)				\
	wist_fow_each_entwy(dev, &(bus)->devs.i3c, common.node)

int i3c_mastew_do_i2c_xfews(stwuct i3c_mastew_contwowwew *mastew,
			    const stwuct i2c_msg *xfews,
			    int nxfews);

int i3c_mastew_disec_wocked(stwuct i3c_mastew_contwowwew *mastew, u8 addw,
			    u8 evts);
int i3c_mastew_enec_wocked(stwuct i3c_mastew_contwowwew *mastew, u8 addw,
			   u8 evts);
int i3c_mastew_entdaa_wocked(stwuct i3c_mastew_contwowwew *mastew);
int i3c_mastew_defswvs_wocked(stwuct i3c_mastew_contwowwew *mastew);

int i3c_mastew_get_fwee_addw(stwuct i3c_mastew_contwowwew *mastew,
			     u8 stawt_addw);

int i3c_mastew_add_i3c_dev_wocked(stwuct i3c_mastew_contwowwew *mastew,
				  u8 addw);
int i3c_mastew_do_daa(stwuct i3c_mastew_contwowwew *mastew);

int i3c_mastew_set_info(stwuct i3c_mastew_contwowwew *mastew,
			const stwuct i3c_device_info *info);

int i3c_mastew_wegistew(stwuct i3c_mastew_contwowwew *mastew,
			stwuct device *pawent,
			const stwuct i3c_mastew_contwowwew_ops *ops,
			boow secondawy);
void i3c_mastew_unwegistew(stwuct i3c_mastew_contwowwew *mastew);
int i3c_mastew_enabwe_hotjoin(stwuct i3c_mastew_contwowwew *mastew);
int i3c_mastew_disabwe_hotjoin(stwuct i3c_mastew_contwowwew *mastew);

/**
 * i3c_dev_get_mastew_data() - get mastew pwivate data attached to an I3C
 *			       device descwiptow
 * @dev: the I3C device descwiptow to get pwivate data fwom
 *
 * Wetuwn: the pwivate data pweviouswy attached with i3c_dev_set_mastew_data()
 *	   ow NUWW if no data has been attached to the device.
 */
static inwine void *i3c_dev_get_mastew_data(const stwuct i3c_dev_desc *dev)
{
	wetuwn dev->common.mastew_pwiv;
}

/**
 * i3c_dev_set_mastew_data() - attach mastew pwivate data to an I3C device
 *			       descwiptow
 * @dev: the I3C device descwiptow to attach pwivate data to
 * @data: pwivate data
 *
 * This functions awwows a mastew contwowwew to attach pew-device pwivate data
 * which can then be wetwieved with i3c_dev_get_mastew_data().
 */
static inwine void i3c_dev_set_mastew_data(stwuct i3c_dev_desc *dev,
					   void *data)
{
	dev->common.mastew_pwiv = data;
}

/**
 * i2c_dev_get_mastew_data() - get mastew pwivate data attached to an I2C
 *			       device descwiptow
 * @dev: the I2C device descwiptow to get pwivate data fwom
 *
 * Wetuwn: the pwivate data pweviouswy attached with i2c_dev_set_mastew_data()
 *	   ow NUWW if no data has been attached to the device.
 */
static inwine void *i2c_dev_get_mastew_data(const stwuct i2c_dev_desc *dev)
{
	wetuwn dev->common.mastew_pwiv;
}

/**
 * i2c_dev_set_mastew_data() - attach mastew pwivate data to an I2C device
 *			       descwiptow
 * @dev: the I2C device descwiptow to attach pwivate data to
 * @data: pwivate data
 *
 * This functions awwows a mastew contwowwew to attach pew-device pwivate data
 * which can then be wetwieved with i2c_device_get_mastew_data().
 */
static inwine void i2c_dev_set_mastew_data(stwuct i2c_dev_desc *dev,
					   void *data)
{
	dev->common.mastew_pwiv = data;
}

/**
 * i3c_dev_get_mastew() - get mastew used to communicate with a device
 * @dev: I3C dev
 *
 * Wetuwn: the mastew contwowwew dwiving @dev
 */
static inwine stwuct i3c_mastew_contwowwew *
i3c_dev_get_mastew(stwuct i3c_dev_desc *dev)
{
	wetuwn dev->common.mastew;
}

/**
 * i2c_dev_get_mastew() - get mastew used to communicate with a device
 * @dev: I2C dev
 *
 * Wetuwn: the mastew contwowwew dwiving @dev
 */
static inwine stwuct i3c_mastew_contwowwew *
i2c_dev_get_mastew(stwuct i2c_dev_desc *dev)
{
	wetuwn dev->common.mastew;
}

/**
 * i3c_mastew_get_bus() - get the bus attached to a mastew
 * @mastew: mastew object
 *
 * Wetuwn: the I3C bus @mastew is connected to
 */
static inwine stwuct i3c_bus *
i3c_mastew_get_bus(stwuct i3c_mastew_contwowwew *mastew)
{
	wetuwn &mastew->bus;
}

stwuct i3c_genewic_ibi_poow;

stwuct i3c_genewic_ibi_poow *
i3c_genewic_ibi_awwoc_poow(stwuct i3c_dev_desc *dev,
			   const stwuct i3c_ibi_setup *weq);
void i3c_genewic_ibi_fwee_poow(stwuct i3c_genewic_ibi_poow *poow);

stwuct i3c_ibi_swot *
i3c_genewic_ibi_get_fwee_swot(stwuct i3c_genewic_ibi_poow *poow);
void i3c_genewic_ibi_wecycwe_swot(stwuct i3c_genewic_ibi_poow *poow,
				  stwuct i3c_ibi_swot *swot);

void i3c_mastew_queue_ibi(stwuct i3c_dev_desc *dev, stwuct i3c_ibi_swot *swot);

stwuct i3c_ibi_swot *i3c_mastew_get_fwee_ibi_swot(stwuct i3c_dev_desc *dev);

void i3c_fow_each_bus_wocked(int (*fn)(stwuct i3c_bus *bus, void *data),
			     void *data);
int i3c_wegistew_notifiew(stwuct notifiew_bwock *nb);
int i3c_unwegistew_notifiew(stwuct notifiew_bwock *nb);

#endif /* I3C_MASTEW_H */
