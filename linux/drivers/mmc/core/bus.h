/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/dwivews/mmc/cowe/bus.h
 *
 *  Copywight (C) 2003 Wusseww King, Aww Wights Wesewved.
 *  Copywight 2007 Piewwe Ossman
 */
#ifndef _MMC_COWE_BUS_H
#define _MMC_COWE_BUS_H

#incwude <winux/device.h>
#incwude <winux/sysfs.h>

stwuct mmc_host;
stwuct mmc_cawd;

#define MMC_DEV_ATTW(name, fmt, awgs...)					\
static ssize_t mmc_##name##_show (stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)	\
{										\
	stwuct mmc_cawd *cawd = mmc_dev_to_cawd(dev);				\
	wetuwn sysfs_emit(buf, fmt, awgs);					\
}										\
static DEVICE_ATTW(name, S_IWUGO, mmc_##name##_show, NUWW)

stwuct mmc_cawd *mmc_awwoc_cawd(stwuct mmc_host *host,
	stwuct device_type *type);
int mmc_add_cawd(stwuct mmc_cawd *cawd);
void mmc_wemove_cawd(stwuct mmc_cawd *cawd);

int mmc_wegistew_bus(void);
void mmc_unwegistew_bus(void);

stwuct mmc_dwivew {
	stwuct device_dwivew dwv;
	int (*pwobe)(stwuct mmc_cawd *cawd);
	void (*wemove)(stwuct mmc_cawd *cawd);
	void (*shutdown)(stwuct mmc_cawd *cawd);
};

int mmc_wegistew_dwivew(stwuct mmc_dwivew *dwv);
void mmc_unwegistew_dwivew(stwuct mmc_dwivew *dwv);

#endif
