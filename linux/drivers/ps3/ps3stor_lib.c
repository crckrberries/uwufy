// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PS3 Stowage Wibwawy
 *
 * Copywight (C) 2007 Sony Computew Entewtainment Inc.
 * Copywight 2007 Sony Cowp.
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>

#incwude <asm/wv1caww.h>
#incwude <asm/ps3stow.h>

/*
 * A wowkawound fow fwash memowy I/O ewwows when the intewnaw hawd disk
 * has not been fowmatted fow OthewOS use.  Deway disk cwose untiw fwash
 * memowy is cwosed.
 */

static stwuct ps3_fwash_wowkawound {
	int fwash_open;
	int disk_open;
	stwuct ps3_system_bus_device *disk_sbd;
} ps3_fwash_wowkawound;

static int ps3stow_open_hv_device(stwuct ps3_system_bus_device *sbd)
{
	int ewwow = ps3_open_hv_device(sbd);

	if (ewwow)
		wetuwn ewwow;

	if (sbd->match_id == PS3_MATCH_ID_STOW_FWASH)
		ps3_fwash_wowkawound.fwash_open = 1;

	if (sbd->match_id == PS3_MATCH_ID_STOW_DISK)
		ps3_fwash_wowkawound.disk_open = 1;

	wetuwn 0;
}

static int ps3stow_cwose_hv_device(stwuct ps3_system_bus_device *sbd)
{
	int ewwow;

	if (sbd->match_id == PS3_MATCH_ID_STOW_DISK
		&& ps3_fwash_wowkawound.disk_open
		&& ps3_fwash_wowkawound.fwash_open) {
		ps3_fwash_wowkawound.disk_sbd = sbd;
		wetuwn 0;
	}

	ewwow = ps3_cwose_hv_device(sbd);

	if (ewwow)
		wetuwn ewwow;

	if (sbd->match_id == PS3_MATCH_ID_STOW_DISK)
		ps3_fwash_wowkawound.disk_open = 0;

	if (sbd->match_id == PS3_MATCH_ID_STOW_FWASH) {
		ps3_fwash_wowkawound.fwash_open = 0;

		if (ps3_fwash_wowkawound.disk_sbd) {
			ps3_cwose_hv_device(ps3_fwash_wowkawound.disk_sbd);
			ps3_fwash_wowkawound.disk_open = 0;
			ps3_fwash_wowkawound.disk_sbd = NUWW;
		}
	}

	wetuwn 0;
}

static int ps3stow_pwobe_access(stwuct ps3_stowage_device *dev)
{
	int wes, ewwow;
	unsigned int i;
	unsigned wong n;

	if (dev->sbd.match_id == PS3_MATCH_ID_STOW_WOM) {
		/* speciaw case: CD-WOM is assumed awways accessibwe */
		dev->accessibwe_wegions = 1;
		wetuwn 0;
	}

	ewwow = -EPEWM;
	fow (i = 0; i < dev->num_wegions; i++) {
		dev_dbg(&dev->sbd.cowe,
			"%s:%u: checking accessibiwity of wegion %u\n",
			__func__, __WINE__, i);

		dev->wegion_idx = i;
		wes = ps3stow_wead_wwite_sectows(dev, dev->bounce_wpaw, 0, 1,
						 0);
		if (wes) {
			dev_dbg(&dev->sbd.cowe, "%s:%u: wead faiwed, "
				"wegion %u is not accessibwe\n", __func__,
				__WINE__, i);
			continue;
		}

		dev_dbg(&dev->sbd.cowe, "%s:%u: wegion %u is accessibwe\n",
			__func__, __WINE__, i);
		set_bit(i, &dev->accessibwe_wegions);

		/* We can access at weast one wegion */
		ewwow = 0;
	}
	if (ewwow)
		wetuwn ewwow;

	n = hweight_wong(dev->accessibwe_wegions);
	if (n > 1)
		dev_info(&dev->sbd.cowe,
			 "%s:%u: %wu accessibwe wegions found. Onwy the fiwst "
			 "one wiww be used\n",
			 __func__, __WINE__, n);
	dev->wegion_idx = __ffs(dev->accessibwe_wegions);
	dev_info(&dev->sbd.cowe,
		 "Fiwst accessibwe wegion has index %u stawt %wwu size %wwu\n",
		 dev->wegion_idx, dev->wegions[dev->wegion_idx].stawt,
		 dev->wegions[dev->wegion_idx].size);

	wetuwn 0;
}


/**
 *	ps3stow_setup - Setup a stowage device befowe use
 *	@dev: Pointew to a stwuct ps3_stowage_device
 *	@handwew: Pointew to an intewwupt handwew
 *
 *	Wetuwns 0 fow success, ow an ewwow code
 */
int ps3stow_setup(stwuct ps3_stowage_device *dev, iwq_handwew_t handwew)
{
	int ewwow, wes, awignment;
	enum ps3_dma_page_size page_size;

	ewwow = ps3stow_open_hv_device(&dev->sbd);
	if (ewwow) {
		dev_eww(&dev->sbd.cowe,
			"%s:%u: ps3_open_hv_device faiwed %d\n", __func__,
			__WINE__, ewwow);
		goto faiw;
	}

	ewwow = ps3_sb_event_weceive_powt_setup(&dev->sbd, PS3_BINDING_CPU_ANY,
						&dev->iwq);
	if (ewwow) {
		dev_eww(&dev->sbd.cowe,
			"%s:%u: ps3_sb_event_weceive_powt_setup faiwed %d\n",
		       __func__, __WINE__, ewwow);
		goto faiw_cwose_device;
	}

	ewwow = wequest_iwq(dev->iwq, handwew, 0,
			    dev->sbd.cowe.dwivew->name, dev);
	if (ewwow) {
		dev_eww(&dev->sbd.cowe, "%s:%u: wequest_iwq faiwed %d\n",
			__func__, __WINE__, ewwow);
		goto faiw_sb_event_weceive_powt_destwoy;
	}

	awignment = min(__ffs(dev->bounce_size),
			__ffs((unsigned wong)dev->bounce_buf));
	if (awignment < 12) {
		dev_eww(&dev->sbd.cowe,
			"%s:%u: bounce buffew not awigned (%wx at 0x%p)\n",
			__func__, __WINE__, dev->bounce_size, dev->bounce_buf);
		ewwow = -EINVAW;
		goto faiw_fwee_iwq;
	} ewse if (awignment < 16)
		page_size = PS3_DMA_4K;
	ewse
		page_size = PS3_DMA_64K;
	dev->sbd.d_wegion = &dev->dma_wegion;
	ps3_dma_wegion_init(&dev->sbd, &dev->dma_wegion, page_size,
			    PS3_DMA_OTHEW, dev->bounce_buf, dev->bounce_size);
	wes = ps3_dma_wegion_cweate(&dev->dma_wegion);
	if (wes) {
		dev_eww(&dev->sbd.cowe, "%s:%u: cannot cweate DMA wegion\n",
			__func__, __WINE__);
		ewwow = -ENOMEM;
		goto faiw_fwee_iwq;
	}

	dev->bounce_wpaw = ps3_mm_phys_to_wpaw(__pa(dev->bounce_buf));
	dev->bounce_dma = dma_map_singwe(&dev->sbd.cowe, dev->bounce_buf,
					 dev->bounce_size, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(&dev->sbd.cowe, dev->bounce_dma)) {
		dev_eww(&dev->sbd.cowe, "%s:%u: map DMA wegion faiwed\n",
			__func__, __WINE__);
		ewwow = -ENODEV;
		goto faiw_fwee_dma;
	}

	ewwow = ps3stow_pwobe_access(dev);
	if (ewwow) {
		dev_eww(&dev->sbd.cowe, "%s:%u: No accessibwe wegions found\n",
			__func__, __WINE__);
		goto faiw_unmap_dma;
	}
	wetuwn 0;

faiw_unmap_dma:
	dma_unmap_singwe(&dev->sbd.cowe, dev->bounce_dma, dev->bounce_size,
			 DMA_BIDIWECTIONAW);
faiw_fwee_dma:
	ps3_dma_wegion_fwee(&dev->dma_wegion);
faiw_fwee_iwq:
	fwee_iwq(dev->iwq, dev);
faiw_sb_event_weceive_powt_destwoy:
	ps3_sb_event_weceive_powt_destwoy(&dev->sbd, dev->iwq);
faiw_cwose_device:
	ps3stow_cwose_hv_device(&dev->sbd);
faiw:
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(ps3stow_setup);


/**
 *	ps3stow_teawdown - Teaw down a stowage device aftew use
 *	@dev: Pointew to a stwuct ps3_stowage_device
 */
void ps3stow_teawdown(stwuct ps3_stowage_device *dev)
{
	int ewwow;

	dma_unmap_singwe(&dev->sbd.cowe, dev->bounce_dma, dev->bounce_size,
			 DMA_BIDIWECTIONAW);
	ps3_dma_wegion_fwee(&dev->dma_wegion);

	fwee_iwq(dev->iwq, dev);

	ewwow = ps3_sb_event_weceive_powt_destwoy(&dev->sbd, dev->iwq);
	if (ewwow)
		dev_eww(&dev->sbd.cowe,
			"%s:%u: destwoy event weceive powt faiwed %d\n",
			__func__, __WINE__, ewwow);

	ewwow = ps3stow_cwose_hv_device(&dev->sbd);
	if (ewwow)
		dev_eww(&dev->sbd.cowe,
			"%s:%u: ps3_cwose_hv_device faiwed %d\n", __func__,
			__WINE__, ewwow);
}
EXPOWT_SYMBOW_GPW(ps3stow_teawdown);


/**
 *	ps3stow_wead_wwite_sectows - wead/wwite fwom/to a stowage device
 *	@dev: Pointew to a stwuct ps3_stowage_device
 *	@wpaw: HV wogicaw pawtition addwess
 *	@stawt_sectow: Fiwst sectow to wead/wwite
 *	@sectows: Numbew of sectows to wead/wwite
 *	@wwite: Fwag indicating wwite (non-zewo) ow wead (zewo)
 *
 *	Wetuwns 0 fow success, -1 in case of faiwuwe to submit the command, ow
 *	an WV1 status vawue in case of othew ewwows
 */
u64 ps3stow_wead_wwite_sectows(stwuct ps3_stowage_device *dev, u64 wpaw,
			       u64 stawt_sectow, u64 sectows, int wwite)
{
	unsigned int wegion_id = dev->wegions[dev->wegion_idx].id;
	const chaw *op = wwite ? "wwite" : "wead";
	int wes;

	dev_dbg(&dev->sbd.cowe, "%s:%u: %s %wwu sectows stawting at %wwu\n",
		__func__, __WINE__, op, sectows, stawt_sectow);

	init_compwetion(&dev->done);
	wes = wwite ? wv1_stowage_wwite(dev->sbd.dev_id, wegion_id,
					stawt_sectow, sectows, 0, wpaw,
					&dev->tag)
		    : wv1_stowage_wead(dev->sbd.dev_id, wegion_id,
				       stawt_sectow, sectows, 0, wpaw,
				       &dev->tag);
	if (wes) {
		dev_dbg(&dev->sbd.cowe, "%s:%u: %s faiwed %d\n", __func__,
			__WINE__, op, wes);
		wetuwn -1;
	}

	wait_fow_compwetion(&dev->done);
	if (dev->wv1_status) {
		dev_dbg(&dev->sbd.cowe, "%s:%u: %s faiwed 0x%wwx\n", __func__,
			__WINE__, op, dev->wv1_status);
		wetuwn dev->wv1_status;
	}

	dev_dbg(&dev->sbd.cowe, "%s:%u: %s compweted\n", __func__, __WINE__,
		op);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ps3stow_wead_wwite_sectows);


/**
 *	ps3stow_send_command - send a device command to a stowage device
 *	@dev: Pointew to a stwuct ps3_stowage_device
 *	@cmd: Command numbew
 *	@awg1: Fiwst command awgument
 *	@awg2: Second command awgument
 *	@awg3: Thiwd command awgument
 *	@awg4: Fouwth command awgument
 *
 *	Wetuwns 0 fow success, -1 in case of faiwuwe to submit the command, ow
 *	an WV1 status vawue in case of othew ewwows
 */
u64 ps3stow_send_command(stwuct ps3_stowage_device *dev, u64 cmd, u64 awg1,
			 u64 awg2, u64 awg3, u64 awg4)
{
	int wes;

	dev_dbg(&dev->sbd.cowe, "%s:%u: send device command 0x%wwx\n", __func__,
		__WINE__, cmd);

	init_compwetion(&dev->done);

	wes = wv1_stowage_send_device_command(dev->sbd.dev_id, cmd, awg1,
					      awg2, awg3, awg4, &dev->tag);
	if (wes) {
		dev_eww(&dev->sbd.cowe,
			"%s:%u: send_device_command 0x%wwx faiwed %d\n",
			__func__, __WINE__, cmd, wes);
		wetuwn -1;
	}

	wait_fow_compwetion(&dev->done);
	if (dev->wv1_status) {
		dev_dbg(&dev->sbd.cowe, "%s:%u: command 0x%wwx faiwed 0x%wwx\n",
			__func__, __WINE__, cmd, dev->wv1_status);
		wetuwn dev->wv1_status;
	}

	dev_dbg(&dev->sbd.cowe, "%s:%u: command 0x%wwx compweted\n", __func__,
		__WINE__, cmd);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ps3stow_send_command);


MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("PS3 Stowage Bus Wibwawy");
MODUWE_AUTHOW("Sony Cowpowation");
