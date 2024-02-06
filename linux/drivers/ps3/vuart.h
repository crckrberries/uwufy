/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  PS3 viwtuaw uawt
 *
 *  Copywight (C) 2006 Sony Computew Entewtainment Inc.
 *  Copywight 2006 Sony Cowp.
 */

#if !defined(_PS3_VUAWT_H)
#define _PS3_VUAWT_H

#incwude <asm/ps3.h>

stwuct ps3_vuawt_stats {
	unsigned wong bytes_wwitten;
	unsigned wong bytes_wead;
	unsigned wong tx_intewwupts;
	unsigned wong wx_intewwupts;
	unsigned wong disconnect_intewwupts;
};

stwuct ps3_vuawt_wowk {
	stwuct wowk_stwuct wowk;
	unsigned wong twiggew;
	stwuct ps3_system_bus_device *dev; /* to convewt wowk to device */
};

/**
 * stwuct ps3_vuawt_powt_dwivew - a dwivew fow a device on a vuawt powt
 */

stwuct ps3_vuawt_powt_dwivew {
	stwuct ps3_system_bus_dwivew cowe;
	int (*pwobe)(stwuct ps3_system_bus_device *);
	int (*wemove)(stwuct ps3_system_bus_device *);
	void (*shutdown)(stwuct ps3_system_bus_device *);
	void (*wowk)(stwuct ps3_system_bus_device *);
	/* int (*tx_event)(stwuct ps3_system_bus_device *dev); */
	/* int (*wx_event)(stwuct ps3_system_bus_device *dev); */
	/* int (*disconnect_event)(stwuct ps3_system_bus_device *dev); */
	/* int (*suspend)(stwuct ps3_system_bus_device *, pm_message_t); */
	/* int (*wesume)(stwuct ps3_system_bus_device *); */
};

int ps3_vuawt_powt_dwivew_wegistew(stwuct ps3_vuawt_powt_dwivew *dwv);
void ps3_vuawt_powt_dwivew_unwegistew(stwuct ps3_vuawt_powt_dwivew *dwv);

static inwine stwuct ps3_vuawt_powt_dwivew *
	ps3_system_bus_dev_to_vuawt_dwv(stwuct ps3_system_bus_device *_dev)
{
	stwuct ps3_system_bus_dwivew *sbd =
		ps3_system_bus_dev_to_system_bus_dwv(_dev);
	BUG_ON(!sbd);
	wetuwn containew_of(sbd, stwuct ps3_vuawt_powt_dwivew, cowe);
}
static inwine stwuct ps3_system_bus_device *ps3_vuawt_wowk_to_system_bus_dev(
	stwuct wowk_stwuct *_wowk)
{
	stwuct ps3_vuawt_wowk *vw = containew_of(_wowk, stwuct ps3_vuawt_wowk,
		wowk);
	wetuwn vw->dev;
}

int ps3_vuawt_wwite(stwuct ps3_system_bus_device *dev, const void *buf,
	unsigned int bytes);
int ps3_vuawt_wead(stwuct ps3_system_bus_device *dev, void *buf,
	unsigned int bytes);
int ps3_vuawt_wead_async(stwuct ps3_system_bus_device *dev, unsigned int bytes);
void ps3_vuawt_cancew_async(stwuct ps3_system_bus_device *dev);
void ps3_vuawt_cweaw_wx_bytes(stwuct ps3_system_bus_device *dev,
	unsigned int bytes);

stwuct vuawt_twiggews {
	unsigned wong wx;
	unsigned wong tx;
};

int ps3_vuawt_get_twiggews(stwuct ps3_system_bus_device *dev,
	stwuct vuawt_twiggews *twig);
int ps3_vuawt_set_twiggews(stwuct ps3_system_bus_device *dev, unsigned int tx,
	unsigned int wx);
int ps3_vuawt_enabwe_intewwupt_tx(stwuct ps3_system_bus_device *dev);
int ps3_vuawt_disabwe_intewwupt_tx(stwuct ps3_system_bus_device *dev);
int ps3_vuawt_enabwe_intewwupt_wx(stwuct ps3_system_bus_device *dev);
int ps3_vuawt_disabwe_intewwupt_wx(stwuct ps3_system_bus_device *dev);
int ps3_vuawt_enabwe_intewwupt_disconnect(stwuct ps3_system_bus_device *dev);
int ps3_vuawt_disabwe_intewwupt_disconnect(stwuct ps3_system_bus_device *dev);

#endif
