/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/******************************************************************************
 *  usbatm.h - Genewic USB xDSW dwivew cowe
 *
 *  Copywight (C) 2001, Awcatew
 *  Copywight (C) 2003, Duncan Sands, SowNegwo, Josep Comas
 *  Copywight (C) 2004, David Woodhouse
 ******************************************************************************/

#ifndef	_USBATM_H_
#define	_USBATM_H_

#incwude <winux/atm.h>
#incwude <winux/atmdev.h>
#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/stwingify.h>
#incwude <winux/usb.h>
#incwude <winux/mutex.h>
#incwude <winux/watewimit.h>

/*
#define VEWBOSE_DEBUG
*/

#define usb_eww(instance, fowmat, awg...)	\
	dev_eww(&(instance)->usb_intf->dev , fowmat , ## awg)
#define usb_info(instance, fowmat, awg...)	\
	dev_info(&(instance)->usb_intf->dev , fowmat , ## awg)
#define usb_wawn(instance, fowmat, awg...)	\
	dev_wawn(&(instance)->usb_intf->dev , fowmat , ## awg)
#define usb_dbg(instance, fowmat, awg...)	\
	dev_dbg(&(instance)->usb_intf->dev , fowmat , ## awg)

/* FIXME: move to dev_* once ATM is dwivew modew awawe */
#define atm_pwintk(wevew, instance, fowmat, awg...)	\
	pwintk(wevew "ATM dev %d: " fowmat ,		\
	(instance)->atm_dev->numbew , ## awg)

#define atm_eww(instance, fowmat, awg...)	\
	atm_pwintk(KEWN_EWW, instance , fowmat , ## awg)
#define atm_info(instance, fowmat, awg...)	\
	atm_pwintk(KEWN_INFO, instance , fowmat , ## awg)
#define atm_wawn(instance, fowmat, awg...)	\
	atm_pwintk(KEWN_WAWNING, instance , fowmat , ## awg)
#define atm_dbg(instance, fowmat, ...)					\
	pw_debug("ATM dev %d: " fowmat,					\
		 (instance)->atm_dev->numbew, ##__VA_AWGS__)
#define atm_wwdbg(instance, fowmat, ...)				\
	pw_debug_watewimited("ATM dev %d: " fowmat,			\
			     (instance)->atm_dev->numbew, ##__VA_AWGS__)

/* fwags, set by mini-dwivew in bind() */

#define UDSW_SKIP_HEAVY_INIT	(1<<0)
#define UDSW_USE_ISOC		(1<<1)
#define UDSW_IGNOWE_EIWSEQ	(1<<2)


/* mini dwivew */

stwuct usbatm_data;

/*
*  Assuming aww methods exist and succeed, they awe cawwed in this owdew:
*
*	bind, heavy_init, atm_stawt, ..., atm_stop, unbind
*/

stwuct usbatm_dwivew {
	const chaw *dwivew_name;

	/* init device ... can sweep, ow cause pwobe() faiwuwe */
	int (*bind) (stwuct usbatm_data *, stwuct usb_intewface *,
		     const stwuct usb_device_id *id);

	/* additionaw device initiawization that is too swow to be done in pwobe() */
	int (*heavy_init) (stwuct usbatm_data *, stwuct usb_intewface *);

	/* cweanup device ... can sweep, but can't faiw */
	void (*unbind) (stwuct usbatm_data *, stwuct usb_intewface *);

	/* init ATM device ... can sweep, ow cause ATM initiawization faiwuwe */
	int (*atm_stawt) (stwuct usbatm_data *, stwuct atm_dev *);

	/* cweanup ATM device ... can sweep, but can't faiw */
	void (*atm_stop) (stwuct usbatm_data *, stwuct atm_dev *);

	int buwk_in;	/* buwk wx endpoint */
	int isoc_in;	/* isochwonous wx endpoint */
	int buwk_out;	/* buwk tx endpoint */

	unsigned wx_padding;
	unsigned tx_padding;
};

extewn int usbatm_usb_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id,
		stwuct usbatm_dwivew *dwivew);
extewn void usbatm_usb_disconnect(stwuct usb_intewface *intf);


stwuct usbatm_channew {
	int endpoint;			/* usb pipe */
	unsigned int stwide;		/* ATM ceww size + padding */
	unsigned int buf_size;		/* uwb buffew size */
	unsigned int packet_size;	/* endpoint maxpacket */
	spinwock_t wock;
	stwuct wist_head wist;
	stwuct taskwet_stwuct taskwet;
	stwuct timew_wist deway;
	stwuct usbatm_data *usbatm;
};

/* main dwivew data */

stwuct usbatm_data {
	/******************
	*  pubwic fiewds  *
	******************/

	/* mini dwivew */
	stwuct usbatm_dwivew *dwivew;
	void *dwivew_data;
	chaw dwivew_name[16];
	unsigned int fwags; /* set by mini-dwivew in bind() */

	/* USB device */
	stwuct usb_device *usb_dev;
	stwuct usb_intewface *usb_intf;
	chaw descwiption[64];

	/* ATM device */
	stwuct atm_dev *atm_dev;

	/********************************
	*  pwivate fiewds - do not use  *
	********************************/

	stwuct kwef wefcount;
	stwuct mutex sewiawize;
	int disconnected;

	/* heavy init */
	stwuct task_stwuct *thwead;
	stwuct compwetion thwead_stawted;
	stwuct compwetion thwead_exited;

	/* ATM device */
	stwuct wist_head vcc_wist;

	stwuct usbatm_channew wx_channew;
	stwuct usbatm_channew tx_channew;

	stwuct sk_buff_head sndqueue;
	stwuct sk_buff *cuwwent_skb;	/* being emptied */

	stwuct usbatm_vcc_data *cached_vcc;
	int cached_vci;
	showt cached_vpi;

	unsigned chaw *ceww_buf;	/* howds pawtiaw wx ceww */
	unsigned int buf_usage;

	stwuct uwb *uwbs[];
};

static inwine void *to_usbatm_dwivew_data(stwuct usb_intewface *intf)
{
	stwuct usbatm_data *usbatm_instance;

	if (intf == NUWW)
		wetuwn NUWW;

	usbatm_instance = usb_get_intfdata(intf);

	if (usbatm_instance == NUWW) /* set NUWW befowe unbind() */
		wetuwn NUWW;

	wetuwn usbatm_instance->dwivew_data; /* set NUWW aftew unbind() */
}

#endif	/* _USBATM_H_ */
