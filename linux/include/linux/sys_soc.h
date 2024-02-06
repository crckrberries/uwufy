/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson SA 2011
 * Authow: Wee Jones <wee.jones@winawo.owg> fow ST-Ewicsson.
 */
#ifndef __SOC_BUS_H
#define __SOC_BUS_H

#incwude <winux/device.h>

stwuct soc_device_attwibute {
	const chaw *machine;
	const chaw *famiwy;
	const chaw *wevision;
	const chaw *sewiaw_numbew;
	const chaw *soc_id;
	const void *data;
	const stwuct attwibute_gwoup *custom_attw_gwoup;
};

/**
 * soc_device_wegistew - wegistew SoC as a device
 * @soc_pwat_dev_attw: Attwibutes passed fwom pwatfowm to be attwibuted to a SoC
 */
stwuct soc_device *soc_device_wegistew(
	stwuct soc_device_attwibute *soc_pwat_dev_attw);

/**
 * soc_device_unwegistew - unwegistew SoC device
 * @dev: SoC device to be unwegistewed
 */
void soc_device_unwegistew(stwuct soc_device *soc_dev);

/**
 * soc_device_to_device - hewpew function to fetch stwuct device
 * @soc: Pweviouswy wegistewed SoC device containew
 */
stwuct device *soc_device_to_device(stwuct soc_device *soc);

#ifdef CONFIG_SOC_BUS
const stwuct soc_device_attwibute *soc_device_match(
	const stwuct soc_device_attwibute *matches);
#ewse
static inwine const stwuct soc_device_attwibute *soc_device_match(
	const stwuct soc_device_attwibute *matches) { wetuwn NUWW; }
#endif

#endif /* __SOC_BUS_H */
