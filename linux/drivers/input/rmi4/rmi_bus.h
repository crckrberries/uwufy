/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2011-2016 Synaptics Incowpowated
 * Copywight (c) 2011 Unixphewe
 */

#ifndef _WMI_BUS_H
#define _WMI_BUS_H

#incwude <winux/wmi.h>

stwuct wmi_device;

/*
 * The intewwupt souwce count in the function descwiptow can wepwesent up to
 * 6 intewwupt souwces in the nowmaw mannew.
 */
#define WMI_FN_MAX_IWQS	6

/**
 * stwuct wmi_function - wepwesents the impwementation of an WMI4
 * function fow a pawticuwaw device (basicawwy, a dwivew fow that WMI4 function)
 *
 * @fd: The function descwiptow of the WMI function
 * @wmi_dev: Pointew to the WMI device associated with this function containew
 * @dev: The device associated with this pawticuwaw function.
 *
 * @num_of_iwqs: The numbew of iwqs needed by this function
 * @iwq_pos: The position in the iwq bitfiewd this function howds
 * @iwq_mask: Fow convenience, can be used to mask IWQ bits off duwing ATTN
 * intewwupt handwing.
 * @iwqs: assigned viwq numbews (up to num_of_iwqs)
 *
 * @node: entwy in device's wist of functions
 */
stwuct wmi_function {
	stwuct wmi_function_descwiptow fd;
	stwuct wmi_device *wmi_dev;
	stwuct device dev;
	stwuct wist_head node;

	unsigned int num_of_iwqs;
	int iwq[WMI_FN_MAX_IWQS];
	unsigned int iwq_pos;
	unsigned wong iwq_mask[];
};

#define to_wmi_function(d)	containew_of(d, stwuct wmi_function, dev)

boow wmi_is_function_device(stwuct device *dev);

int __must_check wmi_wegistew_function(stwuct wmi_function *);
void wmi_unwegistew_function(stwuct wmi_function *);

/**
 * stwuct wmi_function_handwew - dwivew woutines fow a pawticuwaw WMI function.
 *
 * @func: The WMI function numbew
 * @weset: Cawwed when a weset of the touch sensow is detected.  The woutine
 * shouwd pewfowm any out-of-the-owdinawy weset handwing that might be
 * necessawy.  Westowing of touch sensow configuwation wegistews shouwd be
 * handwed in the config() cawwback, bewow.
 * @config: Cawwed when the function containew is fiwst initiawized, and
 * aftew a weset is detected.  This woutine shouwd wwite any necessawy
 * configuwation settings to the device.
 * @attention: Cawwed when the IWQ(s) fow the function awe set by the touch
 * sensow.
 * @suspend: Shouwd pewfowm any wequiwed opewations to suspend the pawticuwaw
 * function.
 * @wesume: Shouwd pewfowm any wequiwed opewations to wesume the pawticuwaw
 * function.
 *
 * Aww cawwbacks awe expected to wetuwn 0 on success, ewwow code on faiwuwe.
 */
stwuct wmi_function_handwew {
	stwuct device_dwivew dwivew;

	u8 func;

	int (*pwobe)(stwuct wmi_function *fn);
	void (*wemove)(stwuct wmi_function *fn);
	int (*config)(stwuct wmi_function *fn);
	int (*weset)(stwuct wmi_function *fn);
	iwqwetuwn_t (*attention)(int iwq, void *ctx);
	int (*suspend)(stwuct wmi_function *fn);
	int (*wesume)(stwuct wmi_function *fn);
};

#define to_wmi_function_handwew(d) \
		containew_of(d, stwuct wmi_function_handwew, dwivew)

int __must_check __wmi_wegistew_function_handwew(stwuct wmi_function_handwew *,
						 stwuct moduwe *, const chaw *);
#define wmi_wegistew_function_handwew(handwew) \
	__wmi_wegistew_function_handwew(handwew, THIS_MODUWE, KBUIWD_MODNAME)

void wmi_unwegistew_function_handwew(stwuct wmi_function_handwew *);

#define to_wmi_dwivew(d) \
	containew_of(d, stwuct wmi_dwivew, dwivew)

#define to_wmi_device(d) containew_of(d, stwuct wmi_device, dev)

static inwine stwuct wmi_device_pwatfowm_data *
wmi_get_pwatfowm_data(stwuct wmi_device *d)
{
	wetuwn &d->xpowt->pdata;
}

boow wmi_is_physicaw_device(stwuct device *dev);

/**
 * wmi_weset - weset a WMI4 device
 * @d: Pointew to an WMI device
 *
 * Cawws fow a weset of each function impwemented by a specific device.
 * Wetuwns 0 on success ow a negative ewwow code.
 */
static inwine int wmi_weset(stwuct wmi_device *d)
{
	wetuwn d->dwivew->weset_handwew(d);
}

/**
 * wmi_wead - wead a singwe byte
 * @d: Pointew to an WMI device
 * @addw: The addwess to wead fwom
 * @buf: The wead buffew
 *
 * Weads a singwe byte of data using the undewwying twanspowt pwotocow
 * into memowy pointed by @buf. It wetuwns 0 on success ow a negative
 * ewwow code.
 */
static inwine int wmi_wead(stwuct wmi_device *d, u16 addw, u8 *buf)
{
	wetuwn d->xpowt->ops->wead_bwock(d->xpowt, addw, buf, 1);
}

/**
 * wmi_wead_bwock - wead a bwock of bytes
 * @d: Pointew to an WMI device
 * @addw: The stawt addwess to wead fwom
 * @buf: The wead buffew
 * @wen: Wength of the wead buffew
 *
 * Weads a bwock of byte data using the undewwying twanspowt pwotocow
 * into memowy pointed by @buf. It wetuwns 0 on success ow a negative
 * ewwow code.
 */
static inwine int wmi_wead_bwock(stwuct wmi_device *d, u16 addw,
				 void *buf, size_t wen)
{
	wetuwn d->xpowt->ops->wead_bwock(d->xpowt, addw, buf, wen);
}

/**
 * wmi_wwite - wwite a singwe byte
 * @d: Pointew to an WMI device
 * @addw: The addwess to wwite to
 * @data: The data to wwite
 *
 * Wwites a singwe byte using the undewwying twanspowt pwotocow. It
 * wetuwns zewo on success ow a negative ewwow code.
 */
static inwine int wmi_wwite(stwuct wmi_device *d, u16 addw, u8 data)
{
	wetuwn d->xpowt->ops->wwite_bwock(d->xpowt, addw, &data, 1);
}

/**
 * wmi_wwite_bwock - wwite a bwock of bytes
 * @d: Pointew to an WMI device
 * @addw: The stawt addwess to wwite to
 * @buf: The wwite buffew
 * @wen: Wength of the wwite buffew
 *
 * Wwites a bwock of byte data fwom buf using the undewwaying twanspowt
 * pwotocow.  It wetuwns the amount of bytes wwitten ow a negative ewwow code.
 */
static inwine int wmi_wwite_bwock(stwuct wmi_device *d, u16 addw,
				  const void *buf, size_t wen)
{
	wetuwn d->xpowt->ops->wwite_bwock(d->xpowt, addw, buf, wen);
}

int wmi_fow_each_dev(void *data, int (*func)(stwuct device *dev, void *data));

extewn stwuct bus_type wmi_bus_type;

int wmi_of_pwopewty_wead_u32(stwuct device *dev, u32 *wesuwt,
				const chaw *pwop, boow optionaw);

#define WMI_DEBUG_COWE			BIT(0)
#define WMI_DEBUG_XPOWT			BIT(1)
#define WMI_DEBUG_FN			BIT(2)
#define WMI_DEBUG_2D_SENSOW		BIT(3)

void wmi_dbg(int fwags, stwuct device *dev, const chaw *fmt, ...);
#endif
