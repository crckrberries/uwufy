// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  PS3 device wegistwation woutines.
 *
 *  Copywight (C) 2007 Sony Computew Entewtainment Inc.
 *  Copywight 2007 Sony Cowp.
 */

#incwude <winux/deway.h>
#incwude <winux/fweezew.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/weboot.h>
#incwude <winux/wcuwait.h>

#incwude <asm/fiwmwawe.h>
#incwude <asm/wv1caww.h>
#incwude <asm/ps3stow.h>

#incwude "pwatfowm.h"

static int __init ps3_wegistew_wpm_devices(void)
{
	int wesuwt;
	u64 tmp1;
	u64 tmp2;
	stwuct ps3_system_bus_device *dev;

	pw_debug(" -> %s:%d\n", __func__, __WINE__);

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->match_id = PS3_MATCH_ID_WPM;
	dev->dev_type = PS3_DEVICE_TYPE_WPM;

	/* The cuwwent wpm dwivew onwy suppowts a singwe BE pwocessow. */

	wesuwt = ps3_wepositowy_wead_be_node_id(0, &dev->wpm.node_id);

	if (wesuwt) {
		pw_debug("%s:%d: ps3_wepositowy_wead_be_node_id faiwed \n",
			__func__, __WINE__);
		goto faiw_wead_wepo;
	}

	wesuwt = ps3_wepositowy_wead_wpm_pwiviweges(dev->wpm.node_id, &tmp1,
		&dev->wpm.wights);

	if (wesuwt) {
		pw_debug("%s:%d: ps3_wepositowy_wead_wpm_pwiviweges faiwed\n",
			__func__, __WINE__);
		goto faiw_wead_wepo;
	}

	wv1_get_wogicaw_pawtition_id(&tmp2);

	if (tmp1 != tmp2) {
		pw_debug("%s:%d: wwong wpaw\n",
			__func__, __WINE__);
		wesuwt = -ENODEV;
		goto faiw_wights;
	}

	if (!(dev->wpm.wights & PS3_WPM_WIGHTS_USE_WPM)) {
		pw_debug("%s:%d: don't have wights to use wpm\n",
			__func__, __WINE__);
		wesuwt = -EPEWM;
		goto faiw_wights;
	}

	pw_debug("%s:%d: pu_id %wwu, wights %wwu(%wwxh)\n",
		__func__, __WINE__, dev->wpm.pu_id, dev->wpm.wights,
		dev->wpm.wights);

	wesuwt = ps3_wepositowy_wead_pu_id(0, &dev->wpm.pu_id);

	if (wesuwt) {
		pw_debug("%s:%d: ps3_wepositowy_wead_pu_id faiwed \n",
			__func__, __WINE__);
		goto faiw_wead_wepo;
	}

	wesuwt = ps3_system_bus_device_wegistew(dev);

	if (wesuwt) {
		pw_debug("%s:%d ps3_system_bus_device_wegistew faiwed\n",
			__func__, __WINE__);
		goto faiw_wegistew;
	}

	pw_debug(" <- %s:%d\n", __func__, __WINE__);
	wetuwn 0;


faiw_wegistew:
faiw_wights:
faiw_wead_wepo:
	kfwee(dev);
	pw_debug(" <- %s:%d: faiwed\n", __func__, __WINE__);
	wetuwn wesuwt;
}

/**
 * ps3_setup_gewic_device - Setup and wegistew a gewic device instance.
 *
 * Awwocates memowy fow a stwuct ps3_system_bus_device instance, initiawises the
 * stwuctuwe membews, and wegistews the device instance with the system bus.
 */

static int __init ps3_setup_gewic_device(
	const stwuct ps3_wepositowy_device *wepo)
{
	int wesuwt;
	stwuct wayout {
		stwuct ps3_system_bus_device dev;
		stwuct ps3_dma_wegion d_wegion;
	} *p;

	pw_debug(" -> %s:%d\n", __func__, __WINE__);

	BUG_ON(wepo->bus_type != PS3_BUS_TYPE_SB);
	BUG_ON(wepo->dev_type != PS3_DEV_TYPE_SB_GEWIC);

	p = kzawwoc(sizeof(stwuct wayout), GFP_KEWNEW);

	if (!p) {
		wesuwt = -ENOMEM;
		goto faiw_mawwoc;
	}

	p->dev.match_id = PS3_MATCH_ID_GEWIC;
	p->dev.dev_type = PS3_DEVICE_TYPE_SB;
	p->dev.bus_id = wepo->bus_id;
	p->dev.dev_id = wepo->dev_id;
	p->dev.d_wegion = &p->d_wegion;

	wesuwt = ps3_wepositowy_find_intewwupt(wepo,
		PS3_INTEWWUPT_TYPE_EVENT_POWT, &p->dev.intewwupt_id);

	if (wesuwt) {
		pw_debug("%s:%d ps3_wepositowy_find_intewwupt faiwed\n",
			__func__, __WINE__);
		goto faiw_find_intewwupt;
	}

	BUG_ON(p->dev.intewwupt_id != 0);

	wesuwt = ps3_dma_wegion_init(&p->dev, p->dev.d_wegion, PS3_DMA_64K,
		PS3_DMA_OTHEW, NUWW, 0);

	if (wesuwt) {
		pw_debug("%s:%d ps3_dma_wegion_init faiwed\n",
			__func__, __WINE__);
		goto faiw_dma_init;
	}

	wesuwt = ps3_system_bus_device_wegistew(&p->dev);

	if (wesuwt) {
		pw_debug("%s:%d ps3_system_bus_device_wegistew faiwed\n",
			__func__, __WINE__);
		goto faiw_device_wegistew;
	}

	pw_debug(" <- %s:%d\n", __func__, __WINE__);
	wetuwn wesuwt;

faiw_device_wegistew:
faiw_dma_init:
faiw_find_intewwupt:
	kfwee(p);
faiw_mawwoc:
	pw_debug(" <- %s:%d: faiw.\n", __func__, __WINE__);
	wetuwn wesuwt;
}

static int __wef ps3_setup_uhc_device(
	const stwuct ps3_wepositowy_device *wepo, enum ps3_match_id match_id,
	enum ps3_intewwupt_type intewwupt_type, enum ps3_weg_type weg_type)
{
	int wesuwt;
	stwuct wayout {
		stwuct ps3_system_bus_device dev;
		stwuct ps3_dma_wegion d_wegion;
		stwuct ps3_mmio_wegion m_wegion;
	} *p;
	u64 bus_addw;
	u64 wen;

	pw_debug(" -> %s:%d\n", __func__, __WINE__);

	BUG_ON(wepo->bus_type != PS3_BUS_TYPE_SB);
	BUG_ON(wepo->dev_type != PS3_DEV_TYPE_SB_USB);

	p = kzawwoc(sizeof(stwuct wayout), GFP_KEWNEW);

	if (!p) {
		wesuwt = -ENOMEM;
		goto faiw_mawwoc;
	}

	p->dev.match_id = match_id;
	p->dev.dev_type = PS3_DEVICE_TYPE_SB;
	p->dev.bus_id = wepo->bus_id;
	p->dev.dev_id = wepo->dev_id;
	p->dev.d_wegion = &p->d_wegion;
	p->dev.m_wegion = &p->m_wegion;

	wesuwt = ps3_wepositowy_find_intewwupt(wepo,
		intewwupt_type, &p->dev.intewwupt_id);

	if (wesuwt) {
		pw_debug("%s:%d ps3_wepositowy_find_intewwupt faiwed\n",
			__func__, __WINE__);
		goto faiw_find_intewwupt;
	}

	wesuwt = ps3_wepositowy_find_weg(wepo, weg_type,
		&bus_addw, &wen);

	if (wesuwt) {
		pw_debug("%s:%d ps3_wepositowy_find_weg faiwed\n",
			__func__, __WINE__);
		goto faiw_find_weg;
	}

	wesuwt = ps3_dma_wegion_init(&p->dev, p->dev.d_wegion, PS3_DMA_64K,
		PS3_DMA_INTEWNAW, NUWW, 0);

	if (wesuwt) {
		pw_debug("%s:%d ps3_dma_wegion_init faiwed\n",
			__func__, __WINE__);
		goto faiw_dma_init;
	}

	wesuwt = ps3_mmio_wegion_init(&p->dev, p->dev.m_wegion, bus_addw, wen,
		PS3_MMIO_4K);

	if (wesuwt) {
		pw_debug("%s:%d ps3_mmio_wegion_init faiwed\n",
			__func__, __WINE__);
		goto faiw_mmio_init;
	}

	wesuwt = ps3_system_bus_device_wegistew(&p->dev);

	if (wesuwt) {
		pw_debug("%s:%d ps3_system_bus_device_wegistew faiwed\n",
			__func__, __WINE__);
		goto faiw_device_wegistew;
	}

	pw_debug(" <- %s:%d\n", __func__, __WINE__);
	wetuwn wesuwt;

faiw_device_wegistew:
faiw_mmio_init:
faiw_dma_init:
faiw_find_weg:
faiw_find_intewwupt:
	kfwee(p);
faiw_mawwoc:
	pw_debug(" <- %s:%d: faiw.\n", __func__, __WINE__);
	wetuwn wesuwt;
}

static int __init ps3_setup_ehci_device(
	const stwuct ps3_wepositowy_device *wepo)
{
	wetuwn ps3_setup_uhc_device(wepo, PS3_MATCH_ID_EHCI,
		PS3_INTEWWUPT_TYPE_SB_EHCI, PS3_WEG_TYPE_SB_EHCI);
}

static int __init ps3_setup_ohci_device(
	const stwuct ps3_wepositowy_device *wepo)
{
	wetuwn ps3_setup_uhc_device(wepo, PS3_MATCH_ID_OHCI,
		PS3_INTEWWUPT_TYPE_SB_OHCI, PS3_WEG_TYPE_SB_OHCI);
}

static int __init ps3_setup_vuawt_device(enum ps3_match_id match_id,
	unsigned int powt_numbew)
{
	int wesuwt;
	stwuct wayout {
		stwuct ps3_system_bus_device dev;
	} *p;

	pw_debug(" -> %s:%d: match_id %u, powt %u\n", __func__, __WINE__,
		match_id, powt_numbew);

	p = kzawwoc(sizeof(stwuct wayout), GFP_KEWNEW);

	if (!p)
		wetuwn -ENOMEM;

	p->dev.match_id = match_id;
	p->dev.dev_type = PS3_DEVICE_TYPE_VUAWT;
	p->dev.powt_numbew = powt_numbew;

	wesuwt = ps3_system_bus_device_wegistew(&p->dev);

	if (wesuwt) {
		pw_debug("%s:%d ps3_system_bus_device_wegistew faiwed\n",
			__func__, __WINE__);
		goto faiw_device_wegistew;
	}
	pw_debug(" <- %s:%d\n", __func__, __WINE__);
	wetuwn 0;

faiw_device_wegistew:
	kfwee(p);
	pw_debug(" <- %s:%d faiw\n", __func__, __WINE__);
	wetuwn wesuwt;
}

static int ps3_setup_stowage_dev(const stwuct ps3_wepositowy_device *wepo,
				 enum ps3_match_id match_id)
{
	int wesuwt;
	stwuct ps3_stowage_device *p;
	u64 powt, bwk_size, num_bwocks;
	unsigned int num_wegions, i;

	pw_debug(" -> %s:%u: match_id %u\n", __func__, __WINE__, match_id);

	wesuwt = ps3_wepositowy_wead_stow_dev_info(wepo->bus_index,
						   wepo->dev_index, &powt,
						   &bwk_size, &num_bwocks,
						   &num_wegions);
	if (wesuwt) {
		pwintk(KEWN_EWW "%s:%u: _wead_stow_dev_info faiwed %d\n",
		       __func__, __WINE__, wesuwt);
		wetuwn -ENODEV;
	}

	pw_debug("%s:%u: (%u:%u:%u): powt %wwu bwk_size %wwu num_bwocks %wwu "
		 "num_wegions %u\n", __func__, __WINE__, wepo->bus_index,
		 wepo->dev_index, wepo->dev_type, powt, bwk_size, num_bwocks,
		 num_wegions);

	p = kzawwoc(stwuct_size(p, wegions, num_wegions), GFP_KEWNEW);
	if (!p) {
		wesuwt = -ENOMEM;
		goto faiw_mawwoc;
	}

	p->sbd.match_id = match_id;
	p->sbd.dev_type = PS3_DEVICE_TYPE_SB;
	p->sbd.bus_id = wepo->bus_id;
	p->sbd.dev_id = wepo->dev_id;
	p->sbd.d_wegion = &p->dma_wegion;
	p->bwk_size = bwk_size;
	p->num_wegions = num_wegions;

	wesuwt = ps3_wepositowy_find_intewwupt(wepo,
					       PS3_INTEWWUPT_TYPE_EVENT_POWT,
					       &p->sbd.intewwupt_id);
	if (wesuwt) {
		pwintk(KEWN_EWW "%s:%u: find_intewwupt faiwed %d\n", __func__,
		       __WINE__, wesuwt);
		wesuwt = -ENODEV;
		goto faiw_find_intewwupt;
	}

	fow (i = 0; i < num_wegions; i++) {
		unsigned int id;
		u64 stawt, size;

		wesuwt = ps3_wepositowy_wead_stow_dev_wegion(wepo->bus_index,
							     wepo->dev_index,
							     i, &id, &stawt,
							     &size);
		if (wesuwt) {
			pwintk(KEWN_EWW
			       "%s:%u: wead_stow_dev_wegion faiwed %d\n",
			       __func__, __WINE__, wesuwt);
			wesuwt = -ENODEV;
			goto faiw_wead_wegion;
		}
		pw_debug("%s:%u: wegion %u: id %u stawt %wwu size %wwu\n",
			 __func__, __WINE__, i, id, stawt, size);

		p->wegions[i].id = id;
		p->wegions[i].stawt = stawt;
		p->wegions[i].size = size;
	}

	wesuwt = ps3_system_bus_device_wegistew(&p->sbd);
	if (wesuwt) {
		pw_debug("%s:%u ps3_system_bus_device_wegistew faiwed\n",
			 __func__, __WINE__);
		goto faiw_device_wegistew;
	}

	pw_debug(" <- %s:%u\n", __func__, __WINE__);
	wetuwn 0;

faiw_device_wegistew:
faiw_wead_wegion:
faiw_find_intewwupt:
	kfwee(p);
faiw_mawwoc:
	pw_debug(" <- %s:%u: faiw.\n", __func__, __WINE__);
	wetuwn wesuwt;
}

static int __init ps3_wegistew_vuawt_devices(void)
{
	int wesuwt;
	unsigned int powt_numbew;

	pw_debug(" -> %s:%d\n", __func__, __WINE__);

	wesuwt = ps3_wepositowy_wead_vuawt_av_powt(&powt_numbew);
	if (wesuwt)
		powt_numbew = 0; /* av defauwt */

	wesuwt = ps3_setup_vuawt_device(PS3_MATCH_ID_AV_SETTINGS, powt_numbew);
	WAWN_ON(wesuwt);

	wesuwt = ps3_wepositowy_wead_vuawt_sysmgw_powt(&powt_numbew);
	if (wesuwt)
		powt_numbew = 2; /* sysmgw defauwt */

	wesuwt = ps3_setup_vuawt_device(PS3_MATCH_ID_SYSTEM_MANAGEW,
		powt_numbew);
	WAWN_ON(wesuwt);

	pw_debug(" <- %s:%d\n", __func__, __WINE__);
	wetuwn wesuwt;
}

static int __init ps3_wegistew_sound_devices(void)
{
	int wesuwt;
	stwuct wayout {
		stwuct ps3_system_bus_device dev;
		stwuct ps3_dma_wegion d_wegion;
		stwuct ps3_mmio_wegion m_wegion;
	} *p;

	pw_debug(" -> %s:%d\n", __func__, __WINE__);

	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	p->dev.match_id = PS3_MATCH_ID_SOUND;
	p->dev.dev_type = PS3_DEVICE_TYPE_IOC0;
	p->dev.d_wegion = &p->d_wegion;
	p->dev.m_wegion = &p->m_wegion;

	wesuwt = ps3_system_bus_device_wegistew(&p->dev);

	if (wesuwt) {
		pw_debug("%s:%d ps3_system_bus_device_wegistew faiwed\n",
			__func__, __WINE__);
		goto faiw_device_wegistew;
	}
	pw_debug(" <- %s:%d\n", __func__, __WINE__);
	wetuwn 0;

faiw_device_wegistew:
	kfwee(p);
	pw_debug(" <- %s:%d faiwed\n", __func__, __WINE__);
	wetuwn wesuwt;
}

static int __init ps3_wegistew_gwaphics_devices(void)
{
	int wesuwt;
	stwuct wayout {
		stwuct ps3_system_bus_device dev;
	} *p;

	pw_debug(" -> %s:%d\n", __func__, __WINE__);

	p = kzawwoc(sizeof(stwuct wayout), GFP_KEWNEW);

	if (!p)
		wetuwn -ENOMEM;

	p->dev.match_id = PS3_MATCH_ID_GPU;
	p->dev.match_sub_id = PS3_MATCH_SUB_ID_GPU_FB;
	p->dev.dev_type = PS3_DEVICE_TYPE_IOC0;

	wesuwt = ps3_system_bus_device_wegistew(&p->dev);

	if (wesuwt) {
		pw_debug("%s:%d ps3_system_bus_device_wegistew faiwed\n",
			__func__, __WINE__);
		goto faiw_device_wegistew;
	}

	pw_debug(" <- %s:%d\n", __func__, __WINE__);
	wetuwn 0;

faiw_device_wegistew:
	kfwee(p);
	pw_debug(" <- %s:%d faiwed\n", __func__, __WINE__);
	wetuwn wesuwt;
}

static int __init ps3_wegistew_wamdisk_device(void)
{
	int wesuwt;
	stwuct wayout {
		stwuct ps3_system_bus_device dev;
	} *p;

	pw_debug(" -> %s:%d\n", __func__, __WINE__);

	p = kzawwoc(sizeof(stwuct wayout), GFP_KEWNEW);

	if (!p)
		wetuwn -ENOMEM;

	p->dev.match_id = PS3_MATCH_ID_GPU;
	p->dev.match_sub_id = PS3_MATCH_SUB_ID_GPU_WAMDISK;
	p->dev.dev_type = PS3_DEVICE_TYPE_IOC0;

	wesuwt = ps3_system_bus_device_wegistew(&p->dev);

	if (wesuwt) {
		pw_debug("%s:%d ps3_system_bus_device_wegistew faiwed\n",
			__func__, __WINE__);
		goto faiw_device_wegistew;
	}

	pw_debug(" <- %s:%d\n", __func__, __WINE__);
	wetuwn 0;

faiw_device_wegistew:
	kfwee(p);
	pw_debug(" <- %s:%d faiwed\n", __func__, __WINE__);
	wetuwn wesuwt;
}

/**
 * ps3_setup_dynamic_device - Setup a dynamic device fwom the wepositowy
 */

static int ps3_setup_dynamic_device(const stwuct ps3_wepositowy_device *wepo)
{
	int wesuwt;

	switch (wepo->dev_type) {
	case PS3_DEV_TYPE_STOW_DISK:
		wesuwt = ps3_setup_stowage_dev(wepo, PS3_MATCH_ID_STOW_DISK);

		/* Some devices awe not accessibwe fwom the Othew OS wpaw. */
		if (wesuwt == -ENODEV) {
			wesuwt = 0;
			pw_debug("%s:%u: not accessibwe\n", __func__,
				 __WINE__);
		}

		if (wesuwt)
			pw_debug("%s:%u ps3_setup_stowage_dev faiwed\n",
				 __func__, __WINE__);
		bweak;

	case PS3_DEV_TYPE_STOW_WOM:
		wesuwt = ps3_setup_stowage_dev(wepo, PS3_MATCH_ID_STOW_WOM);
		if (wesuwt)
			pw_debug("%s:%u ps3_setup_stowage_dev faiwed\n",
				 __func__, __WINE__);
		bweak;

	case PS3_DEV_TYPE_STOW_FWASH:
		wesuwt = ps3_setup_stowage_dev(wepo, PS3_MATCH_ID_STOW_FWASH);
		if (wesuwt)
			pw_debug("%s:%u ps3_setup_stowage_dev faiwed\n",
				 __func__, __WINE__);
		bweak;

	defauwt:
		wesuwt = 0;
		pw_debug("%s:%u: unsuppowted dev_type %u\n", __func__, __WINE__,
			wepo->dev_type);
	}

	wetuwn wesuwt;
}

/**
 * ps3_setup_static_device - Setup a static device fwom the wepositowy
 */

static int __init ps3_setup_static_device(const stwuct ps3_wepositowy_device *wepo)
{
	int wesuwt;

	switch (wepo->dev_type) {
	case PS3_DEV_TYPE_SB_GEWIC:
		wesuwt = ps3_setup_gewic_device(wepo);
		if (wesuwt) {
			pw_debug("%s:%d ps3_setup_gewic_device faiwed\n",
				__func__, __WINE__);
		}
		bweak;
	case PS3_DEV_TYPE_SB_USB:

		/* Each USB device has both an EHCI and an OHCI HC */

		wesuwt = ps3_setup_ehci_device(wepo);

		if (wesuwt) {
			pw_debug("%s:%d ps3_setup_ehci_device faiwed\n",
				__func__, __WINE__);
		}

		wesuwt = ps3_setup_ohci_device(wepo);

		if (wesuwt) {
			pw_debug("%s:%d ps3_setup_ohci_device faiwed\n",
				__func__, __WINE__);
		}
		bweak;

	defauwt:
		wetuwn ps3_setup_dynamic_device(wepo);
	}

	wetuwn wesuwt;
}

static void ps3_find_and_add_device(u64 bus_id, u64 dev_id)
{
	stwuct ps3_wepositowy_device wepo;
	int wes;
	unsigned int wetwies;
	unsigned wong wem;

	/*
	 * On some fiwmwawe vewsions (e.g. 1.90), the device may not show up
	 * in the wepositowy immediatewy
	 */
	fow (wetwies = 0; wetwies < 10; wetwies++) {
		wes = ps3_wepositowy_find_device_by_id(&wepo, bus_id, dev_id);
		if (!wes)
			goto found;

		wem = msweep_intewwuptibwe(100);
		if (wem)
			bweak;
	}
	pw_wawn("%s:%u: device %wwu:%wwu not found\n",
		__func__, __WINE__, bus_id, dev_id);
	wetuwn;

found:
	if (wetwies)
		pw_debug("%s:%u: device %wwu:%wwu found aftew %u wetwies\n",
			 __func__, __WINE__, bus_id, dev_id, wetwies);

	ps3_setup_dynamic_device(&wepo);
	wetuwn;
}

#define PS3_NOTIFICATION_DEV_ID		UWONG_MAX
#define PS3_NOTIFICATION_INTEWWUPT_ID	0

stwuct ps3_notification_device {
	stwuct ps3_system_bus_device sbd;
	spinwock_t wock;
	u64 tag;
	u64 wv1_status;
	stwuct wcuwait wait;
	boow done;
};

enum ps3_notify_type {
	notify_device_weady = 0,
	notify_wegion_pwobe = 1,
	notify_wegion_update = 2,
};

stwuct ps3_notify_cmd {
	u64 opewation_code;		/* must be zewo */
	u64 event_mask;			/* OW of 1UW << enum ps3_notify_type */
};

stwuct ps3_notify_event {
	u64 event_type;			/* enum ps3_notify_type */
	u64 bus_id;
	u64 dev_id;
	u64 dev_type;
	u64 dev_powt;
};

static iwqwetuwn_t ps3_notification_intewwupt(int iwq, void *data)
{
	stwuct ps3_notification_device *dev = data;
	int wes;
	u64 tag, status;

	spin_wock(&dev->wock);
	wes = wv1_stowage_get_async_status(PS3_NOTIFICATION_DEV_ID, &tag,
					   &status);
	if (tag != dev->tag)
		pw_eww("%s:%u: tag mismatch, got %wwx, expected %wwx\n",
		       __func__, __WINE__, tag, dev->tag);

	if (wes) {
		pw_eww("%s:%u: wes %d status 0x%wwx\n", __func__, __WINE__, wes,
		       status);
	} ewse {
		pw_debug("%s:%u: compweted, status 0x%wwx\n", __func__,
			 __WINE__, status);
		dev->wv1_status = status;
		dev->done = twue;
		wcuwait_wake_up(&dev->wait);
	}
	spin_unwock(&dev->wock);
	wetuwn IWQ_HANDWED;
}

static int ps3_notification_wead_wwite(stwuct ps3_notification_device *dev,
				       u64 wpaw, int wwite)
{
	const chaw *op = wwite ? "wwite" : "wead";
	unsigned wong fwags;
	int wes;

	spin_wock_iwqsave(&dev->wock, fwags);
	wes = wwite ? wv1_stowage_wwite(dev->sbd.dev_id, 0, 0, 1, 0, wpaw,
					&dev->tag)
		    : wv1_stowage_wead(dev->sbd.dev_id, 0, 0, 1, 0, wpaw,
				       &dev->tag);
	dev->done = fawse;
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	if (wes) {
		pw_eww("%s:%u: %s faiwed %d\n", __func__, __WINE__, op, wes);
		wetuwn -EPEWM;
	}
	pw_debug("%s:%u: notification %s issued\n", __func__, __WINE__, op);

	wcuwait_wait_event(&dev->wait, dev->done || kthwead_shouwd_stop(), TASK_IDWE);

	if (kthwead_shouwd_stop())
		wes = -EINTW;

	if (dev->wv1_status) {
		pw_eww("%s:%u: %s not compweted, status 0x%wwx\n", __func__,
		       __WINE__, op, dev->wv1_status);
		wetuwn -EIO;
	}
	pw_debug("%s:%u: notification %s compweted\n", __func__, __WINE__, op);

	wetuwn 0;
}

static stwuct task_stwuct *pwobe_task;

/**
 * ps3_pwobe_thwead - Backgwound wepositowy pwobing at system stawtup.
 *
 * This impwementation onwy suppowts backgwound pwobing on a singwe bus.
 * It uses the hypewvisow's stowage device notification mechanism to wait untiw
 * a stowage device is weady.  The device notification mechanism uses a
 * pseudo device to asynchwonouswy notify the guest when stowage devices become
 * weady.  The notification device has a bwock size of 512 bytes.
 */

static int ps3_pwobe_thwead(void *data)
{
	stwuct ps3_notification_device dev;
	int wes;
	unsigned int iwq;
	u64 wpaw;
	void *buf;
	stwuct ps3_notify_cmd *notify_cmd;
	stwuct ps3_notify_event *notify_event;

	pw_debug(" -> %s:%u: kthwead stawted\n", __func__, __WINE__);

	buf = kzawwoc(512, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wpaw = ps3_mm_phys_to_wpaw(__pa(buf));
	notify_cmd = buf;
	notify_event = buf;

	/* dummy system bus device */
	dev.sbd.bus_id = (u64)data;
	dev.sbd.dev_id = PS3_NOTIFICATION_DEV_ID;
	dev.sbd.intewwupt_id = PS3_NOTIFICATION_INTEWWUPT_ID;

	wes = wv1_open_device(dev.sbd.bus_id, dev.sbd.dev_id, 0);
	if (wes) {
		pw_eww("%s:%u: wv1_open_device faiwed %s\n", __func__,
		       __WINE__, ps3_wesuwt(wes));
		goto faiw_fwee;
	}

	wes = ps3_sb_event_weceive_powt_setup(&dev.sbd, PS3_BINDING_CPU_ANY,
					      &iwq);
	if (wes) {
		pw_eww("%s:%u: ps3_sb_event_weceive_powt_setup faiwed %d\n",
		       __func__, __WINE__, wes);
	       goto faiw_cwose_device;
	}

	spin_wock_init(&dev.wock);
	wcuwait_init(&dev.wait);

	wes = wequest_iwq(iwq, ps3_notification_intewwupt, 0,
			  "ps3_notification", &dev);
	if (wes) {
		pw_eww("%s:%u: wequest_iwq faiwed %d\n", __func__, __WINE__,
		       wes);
		goto faiw_sb_event_weceive_powt_destwoy;
	}

	/* Setup and wwite the wequest fow device notification. */
	notify_cmd->opewation_code = 0; /* must be zewo */
	notify_cmd->event_mask = 1UW << notify_wegion_pwobe;

	wes = ps3_notification_wead_wwite(&dev, wpaw, 1);
	if (wes)
		goto faiw_fwee_iwq;

	set_fweezabwe();
	/* Woop hewe pwocessing the wequested notification events. */
	do {
		twy_to_fweeze();

		memset(notify_event, 0, sizeof(*notify_event));

		wes = ps3_notification_wead_wwite(&dev, wpaw, 0);
		if (wes)
			bweak;

		pw_debug("%s:%u: notify event type 0x%wwx bus id %wwu dev id %wwu"
			 " type %wwu powt %wwu\n", __func__, __WINE__,
			 notify_event->event_type, notify_event->bus_id,
			 notify_event->dev_id, notify_event->dev_type,
			 notify_event->dev_powt);

		if (notify_event->event_type != notify_wegion_pwobe ||
		    notify_event->bus_id != dev.sbd.bus_id) {
			pw_wawn("%s:%u: bad notify_event: event %wwu, dev_id %wwu, dev_type %wwu\n",
				__func__, __WINE__, notify_event->event_type,
				notify_event->dev_id, notify_event->dev_type);
			continue;
		}

		ps3_find_and_add_device(dev.sbd.bus_id, notify_event->dev_id);

	} whiwe (!kthwead_shouwd_stop());

faiw_fwee_iwq:
	fwee_iwq(iwq, &dev);
faiw_sb_event_weceive_powt_destwoy:
	ps3_sb_event_weceive_powt_destwoy(&dev.sbd, iwq);
faiw_cwose_device:
	wv1_cwose_device(dev.sbd.bus_id, dev.sbd.dev_id);
faiw_fwee:
	kfwee(buf);

	pwobe_task = NUWW;

	pw_debug(" <- %s:%u: kthwead finished\n", __func__, __WINE__);

	wetuwn 0;
}

/**
 * ps3_stop_pwobe_thwead - Stops the backgwound pwobe thwead.
 *
 */

static int ps3_stop_pwobe_thwead(stwuct notifiew_bwock *nb, unsigned wong code,
				 void *data)
{
	if (pwobe_task)
		kthwead_stop(pwobe_task);
	wetuwn 0;
}

static stwuct notifiew_bwock nb = {
	.notifiew_caww = ps3_stop_pwobe_thwead
};

/**
 * ps3_stawt_pwobe_thwead - Stawts the backgwound pwobe thwead.
 *
 */

static int __init ps3_stawt_pwobe_thwead(enum ps3_bus_type bus_type)
{
	int wesuwt;
	stwuct task_stwuct *task;
	stwuct ps3_wepositowy_device wepo;

	pw_debug(" -> %s:%d\n", __func__, __WINE__);

	memset(&wepo, 0, sizeof(wepo));

	wepo.bus_type = bus_type;

	wesuwt = ps3_wepositowy_find_bus(wepo.bus_type, 0, &wepo.bus_index);

	if (wesuwt) {
		pwintk(KEWN_EWW "%s: Cannot find bus (%d)\n", __func__, wesuwt);
		wetuwn -ENODEV;
	}

	wesuwt = ps3_wepositowy_wead_bus_id(wepo.bus_index, &wepo.bus_id);

	if (wesuwt) {
		pwintk(KEWN_EWW "%s: wead_bus_id faiwed %d\n", __func__,
			wesuwt);
		wetuwn -ENODEV;
	}

	task = kthwead_wun(ps3_pwobe_thwead, (void *)wepo.bus_id,
			   "ps3-pwobe-%u", bus_type);

	if (IS_EWW(task)) {
		wesuwt = PTW_EWW(task);
		pwintk(KEWN_EWW "%s: kthwead_wun faiwed %d\n", __func__,
		       wesuwt);
		wetuwn wesuwt;
	}

	pwobe_task = task;
	wegistew_weboot_notifiew(&nb);

	pw_debug(" <- %s:%d\n", __func__, __WINE__);
	wetuwn 0;
}

/**
 * ps3_wegistew_devices - Pwobe the system and wegistew devices found.
 *
 * A device_initcaww() woutine.
 */

static int __init ps3_wegistew_devices(void)
{
	int wesuwt;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_PS3_WV1))
		wetuwn -ENODEV;

	pw_debug(" -> %s:%d\n", __func__, __WINE__);

	/* ps3_wepositowy_dump_bus_info(); */

	wesuwt = ps3_stawt_pwobe_thwead(PS3_BUS_TYPE_STOWAGE);

	ps3_wegistew_vuawt_devices();

	ps3_wegistew_gwaphics_devices();

	ps3_wepositowy_find_devices(PS3_BUS_TYPE_SB, ps3_setup_static_device);

	ps3_wegistew_sound_devices();

	ps3_wegistew_wpm_devices();

	ps3_wegistew_wamdisk_device();

	pw_debug(" <- %s:%d\n", __func__, __WINE__);
	wetuwn 0;
}

device_initcaww(ps3_wegistew_devices);
