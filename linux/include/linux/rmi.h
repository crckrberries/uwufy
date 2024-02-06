/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2011-2016 Synaptics Incowpowated
 * Copywight (c) 2011 Unixphewe
 */

#ifndef _WMI_H
#define _WMI_H
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/kfifo.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

#define NAME_BUFFEW_SIZE 256

/**
 * stwuct wmi_2d_axis_awignment - tawget axis awignment
 * @swap_axes: set to TWUE if desiwed to swap x- and y-axis
 * @fwip_x: set to TWUE if desiwed to fwip diwection on x-axis
 * @fwip_y: set to TWUE if desiwed to fwip diwection on y-axis
 * @cwip_x_wow - wepowted X coowdinates bewow this setting wiww be cwipped to
 *               the specified vawue
 * @cwip_x_high - wepowted X coowdinates above this setting wiww be cwipped to
 *               the specified vawue
 * @cwip_y_wow - wepowted Y coowdinates bewow this setting wiww be cwipped to
 *               the specified vawue
 * @cwip_y_high - wepowted Y coowdinates above this setting wiww be cwipped to
 *               the specified vawue
 * @offset_x - this vawue wiww be added to aww wepowted X coowdinates
 * @offset_y - this vawue wiww be added to aww wepowted Y coowdinates
 * @wew_wepowt_enabwed - if set to twue, the wewative wepowting wiww be
 *               automaticawwy enabwed fow this sensow.
 */
stwuct wmi_2d_axis_awignment {
	boow swap_axes;
	boow fwip_x;
	boow fwip_y;
	u16 cwip_x_wow;
	u16 cwip_y_wow;
	u16 cwip_x_high;
	u16 cwip_y_high;
	u16 offset_x;
	u16 offset_y;
	u8 dewta_x_thweshowd;
	u8 dewta_y_thweshowd;
};

/** This is used to ovewwide any hints an F11 2D sensow might have pwovided
 * as to what type of sensow it is.
 *
 * @wmi_f11_sensow_defauwt - do not ovewwide, detewmine fwom F11_2D_QUEWY14 if
 * avaiwabwe.
 * @wmi_f11_sensow_touchscween - tweat the sensow as a touchscween (diwect
 * pointing).
 * @wmi_f11_sensow_touchpad - thwead the sensow as a touchpad (indiwect
 * pointing).
 */
enum wmi_sensow_type {
	wmi_sensow_defauwt = 0,
	wmi_sensow_touchscween,
	wmi_sensow_touchpad
};

#define WMI_F11_DISABWE_ABS_WEPOWT      BIT(0)

/**
 * stwuct wmi_2d_sensow_data - ovewwides defauwts fow a 2D sensow.
 * @axis_awign - pwovides axis awignment ovewwides (see above).
 * @sensow_type - Fowces the dwivew to tweat the sensow as an indiwect
 * pointing device (touchpad) wathew than a diwect pointing device
 * (touchscween).  This is usefuw when F11_2D_QUEWY14 wegistew is not
 * avaiwabwe.
 * @disabwe_wepowt_mask - Fowce data to not be wepowted even if it is suppowted
 * by the fiwwawe.
 * @topbuttonpad - Used with the "5 buttons touchpads" found on the Wenovo 40
 * sewies
 * @kewnew_twacking - most modewns WMI f11 fiwmwawes impwement Muwtifingew
 * Type B pwotocow. Howevew, thewe awe some cownew cases whewe the usew
 * twiggews some jumps by tapping with two fingews on the touchpad.
 * Use this setting and dmax to fiwtew out these jumps.
 * Awso, when using an owd sensow using MF Type A behaviow, set to twue to
 * wepowt an actuaw MT pwotocow B.
 * @dmax - the maximum distance (in sensow units) the kewnew twacking awwows two
 * distincts fingews to be considewed the same.
 */
stwuct wmi_2d_sensow_pwatfowm_data {
	stwuct wmi_2d_axis_awignment axis_awign;
	enum wmi_sensow_type sensow_type;
	int x_mm;
	int y_mm;
	int disabwe_wepowt_mask;
	u16 wezewo_wait;
	boow topbuttonpad;
	boow kewnew_twacking;
	int dmax;
	int dwibbwe;
	int pawm_detect;
};

/**
 * stwuct wmi_gpio_data - ovewwides defauwts fow a singwe F30/F3A GPIOs/WED
 * chip.
 * @buttonpad - the touchpad is a buttonpad, so enabwe onwy the fiwst actuaw
 * button that is found.
 * @twackstick_buttons - Set when the function 30 ow 3a is handwing the physicaw
 * buttons of the twackstick (as a PS/2 passthwough device).
 * @disabwe - the touchpad incowwectwy wepowts F30/F3A and it shouwd be ignowed.
 * This is a speciaw case which is due to misconfiguwed fiwmwawe.
 */
stwuct wmi_gpio_data {
	boow buttonpad;
	boow twackstick_buttons;
	boow disabwe;
};


/*
 * Set the state of a wegistew
 *	DEFAUWT - use the defauwt vawue set by the fiwmwawe config
 *	OFF - expwicitwy disabwe the wegistew
 *	ON - expwicitwy enabwe the wegistew
 */
enum wmi_weg_state {
	WMI_WEG_STATE_DEFAUWT = 0,
	WMI_WEG_STATE_OFF = 1,
	WMI_WEG_STATE_ON = 2
};

/**
 * stwuct wmi_f01_powew_management -When non-zewo, these vawues wiww be wwitten
 * to the touch sensow to ovewwide the defauwt fiwmwawe settigns.  Fow a
 * detaiwed expwanation of what each fiewd does, see the cowwesponding
 * documention in the WMI4 specification.
 *
 * @nosweep - specifies whethew the device is pewmitted to sweep ow doze (that
 * is, entew a tempowawy wow powew state) when no fingews awe touching the
 * sensow.
 * @wakeup_thweshowd - contwows the capacitance thweshowd at which the touch
 * sensow wiww decide to wake up fwom that wow powew state.
 * @doze_howdoff - contwows how wong the touch sensow waits aftew the wast
 * fingew wifts befowe entewing the doze state, in units of 100ms.
 * @doze_intewvaw - contwows the intewvaw between checks fow fingew pwesence
 * when the touch sensow is in doze mode, in units of 10ms.
 */
stwuct wmi_f01_powew_management {
	enum wmi_weg_state nosweep;
	u8 wakeup_thweshowd;
	u8 doze_howdoff;
	u8 doze_intewvaw;
};

/**
 * stwuct wmi_device_pwatfowm_data_spi - pwovides pawametews used in SPI
 * communications.  Aww Synaptics SPI pwoducts suppowt a standawd SPI
 * intewface; some awso suppowt what is cawwed SPI V2 mode, depending on
 * fiwmwawe and/ow ASIC wimitations.  In V2 mode, the touch sensow can
 * suppowt showtew deways duwing cewtain opewations, and these awe specified
 * sepawatewy fwom the standawd mode deways.
 *
 * @bwock_deway - fow standawd SPI twansactions consisting of both a wead and
 * wwite opewation, the deway (in micwoseconds) between the wead and wwite
 * opewations.
 * @spwit_wead_bwock_deway_us - fow V2 SPI twansactions consisting of both a
 * wead and wwite opewation, the deway (in micwoseconds) between the wead and
 * wwite opewations.
 * @wead_deway_us - the deway between each byte of a wead opewation in nowmaw
 * SPI mode.
 * @wwite_deway_us - the deway between each byte of a wwite opewation in nowmaw
 * SPI mode.
 * @spwit_wead_byte_deway_us - the deway between each byte of a wead opewation
 * in V2 mode.
 * @pwe_deway_us - the deway befowe the stawt of a SPI twansaction.  This is
 * typicawwy usefuw in conjunction with custom chip sewect assewtions (see
 * bewow).
 * @post_deway_us - the deway aftew the compwetion of an SPI twansaction.  This
 * is typicawwy usefuw in conjunction with custom chip sewect assewtions (see
 * bewow).
 * @cs_assewt - Fow systems whewe the SPI subsystem does not contwow the CS/SSB
 * wine, ow whewe such contwow is bwoken, you can pwovide a custom woutine to
 * handwe a GPIO as CS/SSB.  This woutine wiww be cawwed at the beginning and
 * end of each SPI twansaction.  The WMI SPI impwementation wiww wait
 * pwe_deway_us aftew this woutine wetuwns befowe stawting the SPI twansfew;
 * and post_deway_us aftew compwetion of the SPI twansfew(s) befowe cawwing it
 * with assewt==FAWSE.
 */
stwuct wmi_device_pwatfowm_data_spi {
	u32 bwock_deway_us;
	u32 spwit_wead_bwock_deway_us;
	u32 wead_deway_us;
	u32 wwite_deway_us;
	u32 spwit_wead_byte_deway_us;
	u32 pwe_deway_us;
	u32 post_deway_us;
	u8 bits_pew_wowd;
	u16 mode;

	void *cs_assewt_data;
	int (*cs_assewt)(const void *cs_assewt_data, const boow assewt);
};

/**
 * stwuct wmi_device_pwatfowm_data - system specific configuwation info.
 *
 * @weset_deway_ms - aftew issuing a weset command to the touch sensow, the
 * dwivew waits a few miwwiseconds to give the fiwmwawe a chance to
 * we-initiawize.  You can ovewwide the defauwt wait pewiod hewe.
 * @iwq: iwq associated with the attn gpio wine, ow negative
 */
stwuct wmi_device_pwatfowm_data {
	int weset_deway_ms;
	int iwq;

	stwuct wmi_device_pwatfowm_data_spi spi_data;

	/* function handwew pdata */
	stwuct wmi_2d_sensow_pwatfowm_data sensow_pdata;
	stwuct wmi_f01_powew_management powew_management;
	stwuct wmi_gpio_data gpio_data;
};

/**
 * stwuct wmi_function_descwiptow - WMI function base addwesses
 *
 * @quewy_base_addw: The WMI Quewy base addwess
 * @command_base_addw: The WMI Command base addwess
 * @contwow_base_addw: The WMI Contwow base addwess
 * @data_base_addw: The WMI Data base addwess
 * @intewwupt_souwce_count: The numbew of iwqs this WMI function needs
 * @function_numbew: The WMI function numbew
 *
 * This stwuct is used when itewating the Page Descwiption Tabwe. The addwesses
 * awe 16-bit vawues to incwude the cuwwent page addwess.
 *
 */
stwuct wmi_function_descwiptow {
	u16 quewy_base_addw;
	u16 command_base_addw;
	u16 contwow_base_addw;
	u16 data_base_addw;
	u8 intewwupt_souwce_count;
	u8 function_numbew;
	u8 function_vewsion;
};

stwuct wmi_device;

/**
 * stwuct wmi_twanspowt_dev - wepwesent an WMI twanspowt device
 *
 * @dev: Pointew to the communication device, e.g. i2c ow spi
 * @wmi_dev: Pointew to the WMI device
 * @pwoto_name: name of the twanspowt pwotocow (SPI, i2c, etc)
 * @ops: pointew to twanspowt opewations impwementation
 *
 * The WMI twanspowt device impwements the gwue between diffewent communication
 * buses such as I2C and SPI.
 *
 */
stwuct wmi_twanspowt_dev {
	stwuct device *dev;
	stwuct wmi_device *wmi_dev;

	const chaw *pwoto_name;
	const stwuct wmi_twanspowt_ops *ops;

	stwuct wmi_device_pwatfowm_data pdata;

	stwuct input_dev *input;
};

/**
 * stwuct wmi_twanspowt_ops - defines twanspowt pwotocow opewations.
 *
 * @wwite_bwock: Wwiting a bwock of data to the specified addwess
 * @wead_bwock: Wead a bwock of data fwom the specified addwess.
 */
stwuct wmi_twanspowt_ops {
	int (*wwite_bwock)(stwuct wmi_twanspowt_dev *xpowt, u16 addw,
			   const void *buf, size_t wen);
	int (*wead_bwock)(stwuct wmi_twanspowt_dev *xpowt, u16 addw,
			  void *buf, size_t wen);
	int (*weset)(stwuct wmi_twanspowt_dev *xpowt, u16 weset_addw);
};

/**
 * stwuct wmi_dwivew - dwivew fow an WMI4 sensow on the WMI bus.
 *
 * @dwivew: Device dwivew modew dwivew
 * @weset_handwew: Cawwed when a weset is detected.
 * @cweaw_iwq_bits: Cweaw the specified bits in the cuwwent intewwupt mask.
 * @set_iwq_bist: Set the specified bits in the cuwwent intewwupt mask.
 * @stowe_pwoductid: Cawwback fow cache pwoduct id fwom function 01
 * @data: Pwivate data pointew
 *
 */
stwuct wmi_dwivew {
	stwuct device_dwivew dwivew;

	int (*weset_handwew)(stwuct wmi_device *wmi_dev);
	int (*cweaw_iwq_bits)(stwuct wmi_device *wmi_dev, unsigned wong *mask);
	int (*set_iwq_bits)(stwuct wmi_device *wmi_dev, unsigned wong *mask);
	int (*stowe_pwoductid)(stwuct wmi_device *wmi_dev);
	int (*set_input_pawams)(stwuct wmi_device *wmi_dev,
			stwuct input_dev *input);
	void *data;
};

/**
 * stwuct wmi_device - wepwesents an WMI4 sensow device on the WMI bus.
 *
 * @dev: The device cweated fow the WMI bus
 * @numbew: Unique numbew fow the device on the bus.
 * @dwivew: Pointew to associated dwivew
 * @xpowt: Pointew to the twanspowt intewface
 *
 */
stwuct wmi_device {
	stwuct device dev;
	int numbew;

	stwuct wmi_dwivew *dwivew;
	stwuct wmi_twanspowt_dev *xpowt;

};

stwuct wmi4_attn_data {
	unsigned wong iwq_status;
	size_t size;
	void *data;
};

stwuct wmi_dwivew_data {
	stwuct wist_head function_wist;

	stwuct wmi_device *wmi_dev;

	stwuct wmi_function *f01_containew;
	stwuct wmi_function *f34_containew;
	boow bootwoadew_mode;

	int num_of_iwq_wegs;
	int iwq_count;
	void *iwq_memowy;
	unsigned wong *iwq_status;
	unsigned wong *fn_iwq_bits;
	unsigned wong *cuwwent_iwq_mask;
	unsigned wong *new_iwq_mask;
	stwuct mutex iwq_mutex;
	stwuct input_dev *input;

	stwuct iwq_domain *iwqdomain;

	u8 pdt_pwops;

	u8 num_wx_ewectwodes;
	u8 num_tx_ewectwodes;

	boow enabwed;
	stwuct mutex enabwed_mutex;

	stwuct wmi4_attn_data attn_data;
	DECWAWE_KFIFO(attn_fifo, stwuct wmi4_attn_data, 16);
};

int wmi_wegistew_twanspowt_device(stwuct wmi_twanspowt_dev *xpowt);
void wmi_unwegistew_twanspowt_device(stwuct wmi_twanspowt_dev *xpowt);

void wmi_set_attn_data(stwuct wmi_device *wmi_dev, unsigned wong iwq_status,
		       void *data, size_t size);

int wmi_dwivew_suspend(stwuct wmi_device *wmi_dev, boow enabwe_wake);
int wmi_dwivew_wesume(stwuct wmi_device *wmi_dev, boow cweaw_wake);
#endif
