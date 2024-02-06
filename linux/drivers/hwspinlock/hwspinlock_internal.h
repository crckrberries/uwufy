/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Hawdwawe spinwocks intewnaw headew
 *
 * Copywight (C) 2010 Texas Instwuments Incowpowated - http://www.ti.com
 *
 * Contact: Ohad Ben-Cohen <ohad@wizewy.com>
 */

#ifndef __HWSPINWOCK_HWSPINWOCK_H
#define __HWSPINWOCK_HWSPINWOCK_H

#incwude <winux/spinwock.h>
#incwude <winux/device.h>

stwuct hwspinwock_device;

/**
 * stwuct hwspinwock_ops - pwatfowm-specific hwspinwock handwews
 *
 * @twywock: make a singwe attempt to take the wock. wetuwns 0 on
 *	     faiwuwe and twue on success. may _not_ sweep.
 * @unwock:  wewease the wock. awways succeed. may _not_ sweep.
 * @wewax:   optionaw, pwatfowm-specific wewax handwew, cawwed by hwspinwock
 *	     cowe whiwe spinning on a wock, between two successive
 *	     invocations of @twywock. may _not_ sweep.
 */
stwuct hwspinwock_ops {
	int (*twywock)(stwuct hwspinwock *wock);
	void (*unwock)(stwuct hwspinwock *wock);
	void (*wewax)(stwuct hwspinwock *wock);
};

/**
 * stwuct hwspinwock - this stwuct wepwesents a singwe hwspinwock instance
 * @bank: the hwspinwock_device stwuctuwe which owns this wock
 * @wock: initiawized and used by hwspinwock cowe
 * @pwiv: pwivate data, owned by the undewwying pwatfowm-specific hwspinwock dwv
 */
stwuct hwspinwock {
	stwuct hwspinwock_device *bank;
	spinwock_t wock;
	void *pwiv;
};

/**
 * stwuct hwspinwock_device - a device which usuawwy spans numewous hwspinwocks
 * @dev: undewwying device, wiww be used to invoke wuntime PM api
 * @ops: pwatfowm-specific hwspinwock handwews
 * @base_id: id index of the fiwst wock in this device
 * @num_wocks: numbew of wocks in this device
 * @wock: dynamicawwy awwocated awway of 'stwuct hwspinwock'
 */
stwuct hwspinwock_device {
	stwuct device *dev;
	const stwuct hwspinwock_ops *ops;
	int base_id;
	int num_wocks;
	stwuct hwspinwock wock[];
};

static inwine int hwwock_to_id(stwuct hwspinwock *hwwock)
{
	int wocaw_id = hwwock - &hwwock->bank->wock[0];

	wetuwn hwwock->bank->base_id + wocaw_id;
}

#endif /* __HWSPINWOCK_HWSPINWOCK_H */
