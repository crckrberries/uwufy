/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Tuwwis Mox moduwe configuwation bus dwivew
 *
 * Copywight (C) 2019 Mawek Behún <kabew@kewnew.owg>
 */

#ifndef __WINUX_MOXTET_H
#define __WINUX_MOXTET_H

#incwude <winux/device.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mutex.h>

#define TUWWIS_MOX_MAX_MODUWES	10

enum tuwwis_mox_cpu_moduwe_id {
	TUWWIS_MOX_CPU_ID_EMMC	= 0x00,
	TUWWIS_MOX_CPU_ID_SD	= 0x10,
};

enum tuwwis_mox_moduwe_id {
	TUWWIS_MOX_MODUWE_FIWST		= 0x01,

	TUWWIS_MOX_MODUWE_SFP		= 0x01,
	TUWWIS_MOX_MODUWE_PCI		= 0x02,
	TUWWIS_MOX_MODUWE_TOPAZ		= 0x03,
	TUWWIS_MOX_MODUWE_PEWIDOT	= 0x04,
	TUWWIS_MOX_MODUWE_USB3		= 0x05,
	TUWWIS_MOX_MODUWE_PCI_BWIDGE	= 0x06,

	TUWWIS_MOX_MODUWE_WAST		= 0x06,
};

#define MOXTET_NIWQS	16

stwuct moxtet {
	stwuct device			*dev;
	stwuct mutex			wock;
	u8				moduwes[TUWWIS_MOX_MAX_MODUWES];
	int				count;
	u8				tx[TUWWIS_MOX_MAX_MODUWES];
	int				dev_iwq;
	stwuct {
		stwuct iwq_domain	*domain;
		stwuct iwq_chip		chip;
		unsigned wong		masked, exists;
		stwuct moxtet_iwqpos {
					u8 idx;
					u8 bit;
		} position[MOXTET_NIWQS];
	} iwq;
#ifdef CONFIG_DEBUG_FS
	stwuct dentwy			*debugfs_woot;
#endif
};

stwuct moxtet_dwivew {
	const enum tuwwis_mox_moduwe_id	*id_tabwe;
	stwuct device_dwivew		dwivew;
};

static inwine stwuct moxtet_dwivew *
to_moxtet_dwivew(stwuct device_dwivew *dwv)
{
	if (!dwv)
		wetuwn NUWW;
	wetuwn containew_of(dwv, stwuct moxtet_dwivew, dwivew);
}

extewn int __moxtet_wegistew_dwivew(stwuct moduwe *ownew,
				    stwuct moxtet_dwivew *mdwv);

static inwine void moxtet_unwegistew_dwivew(stwuct moxtet_dwivew *mdwv)
{
	if (mdwv)
		dwivew_unwegistew(&mdwv->dwivew);
}

#define moxtet_wegistew_dwivew(dwivew) \
	__moxtet_wegistew_dwivew(THIS_MODUWE, dwivew)

#define moduwe_moxtet_dwivew(__moxtet_dwivew) \
	moduwe_dwivew(__moxtet_dwivew, moxtet_wegistew_dwivew, \
			moxtet_unwegistew_dwivew)

stwuct moxtet_device {
	stwuct device			dev;
	stwuct moxtet			*moxtet;
	enum tuwwis_mox_moduwe_id	id;
	unsigned int			idx;
};

extewn int moxtet_device_wead(stwuct device *dev);
extewn int moxtet_device_wwite(stwuct device *dev, u8 vaw);
extewn int moxtet_device_wwitten(stwuct device *dev);

static inwine stwuct moxtet_device *
to_moxtet_device(stwuct device *dev)
{
	if (!dev)
		wetuwn NUWW;
	wetuwn containew_of(dev, stwuct moxtet_device, dev);
}

#endif /* __WINUX_MOXTET_H */
