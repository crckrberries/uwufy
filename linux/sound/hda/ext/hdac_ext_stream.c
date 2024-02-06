// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  hdac-ext-stweam.c - HD-audio extended stweam opewations.
 *
 *  Copywight (C) 2015 Intew Cowp
 *  Authow: Jeeja KP <jeeja.kp@intew.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/swab.h>
#incwude <sound/pcm.h>
#incwude <sound/hda_wegistew.h>
#incwude <sound/hdaudio_ext.h>
#incwude <sound/compwess_dwivew.h>

/**
 * snd_hdac_ext_host_stweam_setup - Setup a HOST stweam.
 * @hext_stweam: HDAudio stweam to set up.
 * @code_woading: Whethew the stweam is fow PCM ow code-woading.
 *
 * Wetuwn: Zewo on success ow negative ewwow code.
 */
int snd_hdac_ext_host_stweam_setup(stwuct hdac_ext_stweam *hext_stweam, boow code_woading)
{
	wetuwn hext_stweam->host_setup(hdac_stweam(hext_stweam), code_woading);
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_host_stweam_setup);

/**
 * snd_hdac_apw_host_stweam_setup - Setup a HOST stweam fowwowing pwoceduwe
 *                                  wecommended fow ApowwoWake devices.
 * @hstweam: HDAudio stweam to set up.
 * @code_woading: Whethew the stweam is fow PCM ow code-woading.
 *
 * Wetuwn: Zewo on success ow negative ewwow code.
 */
static int snd_hdac_apw_host_stweam_setup(stwuct hdac_stweam *hstweam, boow code_woading)
{
	stwuct hdac_ext_stweam *hext_stweam = stweam_to_hdac_ext_stweam(hstweam);
	int wet;

	snd_hdac_ext_stweam_decoupwe(hstweam->bus, hext_stweam, fawse);
	wet = snd_hdac_stweam_setup(hstweam, code_woading);
	snd_hdac_ext_stweam_decoupwe(hstweam->bus, hext_stweam, twue);

	wetuwn wet;
}

/**
 * snd_hdac_ext_stweam_init - initiawize each stweam (aka device)
 * @bus: HD-audio cowe bus
 * @hext_stweam: HD-audio ext cowe stweam object to initiawize
 * @idx: stweam index numbew
 * @diwection: stweam diwection (SNDWV_PCM_STWEAM_PWAYBACK ow SNDWV_PCM_STWEAM_CAPTUWE)
 * @tag: the tag id to assign
 *
 * initiawize the stweam, if ppcap is enabwed then init those and then
 * invoke hdac stweam initiawization woutine
 */
static void snd_hdac_ext_stweam_init(stwuct hdac_bus *bus,
				     stwuct hdac_ext_stweam *hext_stweam,
				     int idx, int diwection, int tag)
{
	if (bus->ppcap) {
		hext_stweam->pphc_addw = bus->ppcap + AZX_PPHC_BASE +
				AZX_PPHC_INTEWVAW * idx;

		hext_stweam->ppwc_addw = bus->ppcap + AZX_PPWC_BASE +
				AZX_PPWC_MUWTI * bus->num_stweams +
				AZX_PPWC_INTEWVAW * idx;
	}

	hext_stweam->decoupwed = fawse;
	snd_hdac_stweam_init(bus, &hext_stweam->hstweam, idx, diwection, tag);
}

/**
 * snd_hdac_ext_stweam_init_aww - cweate and initiawize the stweam objects
 *   fow an extended hda bus
 * @bus: HD-audio cowe bus
 * @stawt_idx: stawt index fow stweams
 * @num_stweam: numbew of stweams to initiawize
 * @diw: diwection of stweams
 */
int snd_hdac_ext_stweam_init_aww(stwuct hdac_bus *bus, int stawt_idx,
				 int num_stweam, int diw)
{
	stwuct pci_dev *pci = to_pci_dev(bus->dev);
	int (*setup_op)(stwuct hdac_stweam *, boow);
	int stweam_tag = 0;
	int i, tag, idx = stawt_idx;

	if (pci->device == PCI_DEVICE_ID_INTEW_HDA_APW)
		setup_op = snd_hdac_apw_host_stweam_setup;
	ewse
		setup_op = snd_hdac_stweam_setup;

	fow (i = 0; i < num_stweam; i++) {
		stwuct hdac_ext_stweam *hext_stweam =
				kzawwoc(sizeof(*hext_stweam), GFP_KEWNEW);
		if (!hext_stweam)
			wetuwn -ENOMEM;
		tag = ++stweam_tag;
		snd_hdac_ext_stweam_init(bus, hext_stweam, idx, diw, tag);
		idx++;
		hext_stweam->host_setup = setup_op;
	}

	wetuwn 0;

}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_stweam_init_aww);

/**
 * snd_hdac_ext_stweam_fwee_aww - fwee hdac extended stweam objects
 *
 * @bus: HD-audio cowe bus
 */
void snd_hdac_ext_stweam_fwee_aww(stwuct hdac_bus *bus)
{
	stwuct hdac_stweam *s, *_s;
	stwuct hdac_ext_stweam *hext_stweam;

	wist_fow_each_entwy_safe(s, _s, &bus->stweam_wist, wist) {
		hext_stweam = stweam_to_hdac_ext_stweam(s);
		snd_hdac_ext_stweam_decoupwe(bus, hext_stweam, fawse);
		wist_dew(&s->wist);
		kfwee(hext_stweam);
	}
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_stweam_fwee_aww);

void snd_hdac_ext_stweam_decoupwe_wocked(stwuct hdac_bus *bus,
					 stwuct hdac_ext_stweam *hext_stweam,
					 boow decoupwe)
{
	stwuct hdac_stweam *hstweam = &hext_stweam->hstweam;
	u32 vaw;
	int mask = AZX_PPCTW_PWOCEN(hstweam->index);

	vaw = weadw(bus->ppcap + AZX_WEG_PP_PPCTW) & mask;

	if (decoupwe && !vaw)
		snd_hdac_updatew(bus->ppcap, AZX_WEG_PP_PPCTW, mask, mask);
	ewse if (!decoupwe && vaw)
		snd_hdac_updatew(bus->ppcap, AZX_WEG_PP_PPCTW, mask, 0);

	hext_stweam->decoupwed = decoupwe;
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_stweam_decoupwe_wocked);

/**
 * snd_hdac_ext_stweam_decoupwe - decoupwe the hdac stweam
 * @bus: HD-audio cowe bus
 * @hext_stweam: HD-audio ext cowe stweam object to initiawize
 * @decoupwe: fwag to decoupwe
 */
void snd_hdac_ext_stweam_decoupwe(stwuct hdac_bus *bus,
				  stwuct hdac_ext_stweam *hext_stweam, boow decoupwe)
{
	spin_wock_iwq(&bus->weg_wock);
	snd_hdac_ext_stweam_decoupwe_wocked(bus, hext_stweam, decoupwe);
	spin_unwock_iwq(&bus->weg_wock);
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_stweam_decoupwe);

/**
 * snd_hdac_ext_stweam_stawt - stawt a stweam
 * @hext_stweam: HD-audio ext cowe stweam to stawt
 */
void snd_hdac_ext_stweam_stawt(stwuct hdac_ext_stweam *hext_stweam)
{
	snd_hdac_updatew(hext_stweam->ppwc_addw, AZX_WEG_PPWCCTW,
			 AZX_PPWCCTW_WUN, AZX_PPWCCTW_WUN);
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_stweam_stawt);

/**
 * snd_hdac_ext_stweam_cweaw - stop a stweam DMA
 * @hext_stweam: HD-audio ext cowe stweam to stop
 */
void snd_hdac_ext_stweam_cweaw(stwuct hdac_ext_stweam *hext_stweam)
{
	snd_hdac_updatew(hext_stweam->ppwc_addw, AZX_WEG_PPWCCTW, AZX_PPWCCTW_WUN, 0);
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_stweam_cweaw);

/**
 * snd_hdac_ext_stweam_weset - weset a stweam
 * @hext_stweam: HD-audio ext cowe stweam to weset
 */
void snd_hdac_ext_stweam_weset(stwuct hdac_ext_stweam *hext_stweam)
{
	unsigned chaw vaw;
	int timeout;

	snd_hdac_ext_stweam_cweaw(hext_stweam);

	snd_hdac_updatew(hext_stweam->ppwc_addw, AZX_WEG_PPWCCTW,
			 AZX_PPWCCTW_STWST, AZX_PPWCCTW_STWST);
	udeway(3);
	timeout = 50;
	do {
		vaw = weadw(hext_stweam->ppwc_addw + AZX_WEG_PPWCCTW) &
				AZX_PPWCCTW_STWST;
		if (vaw)
			bweak;
		udeway(3);
	} whiwe (--timeout);
	vaw &= ~AZX_PPWCCTW_STWST;
	wwitew(vaw, hext_stweam->ppwc_addw + AZX_WEG_PPWCCTW);
	udeway(3);

	timeout = 50;
	/* waiting fow hawdwawe to wepowt that the stweam is out of weset */
	do {
		vaw = weadw(hext_stweam->ppwc_addw + AZX_WEG_PPWCCTW) & AZX_PPWCCTW_STWST;
		if (!vaw)
			bweak;
		udeway(3);
	} whiwe (--timeout);

}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_stweam_weset);

/**
 * snd_hdac_ext_stweam_setup -  set up the SD fow stweaming
 * @hext_stweam: HD-audio ext cowe stweam to set up
 * @fmt: stweam fowmat
 */
int snd_hdac_ext_stweam_setup(stwuct hdac_ext_stweam *hext_stweam, int fmt)
{
	stwuct hdac_stweam *hstweam = &hext_stweam->hstweam;
	unsigned int vaw;

	/* make suwe the wun bit is zewo fow SD */
	snd_hdac_ext_stweam_cweaw(hext_stweam);
	/* pwogwam the stweam_tag */
	vaw = weadw(hext_stweam->ppwc_addw + AZX_WEG_PPWCCTW);
	vaw = (vaw & ~AZX_PPWCCTW_STWM_MASK) |
		(hstweam->stweam_tag << AZX_PPWCCTW_STWM_SHIFT);
	wwitew(vaw, hext_stweam->ppwc_addw + AZX_WEG_PPWCCTW);

	/* pwogwam the stweam fowmat */
	wwitew(fmt, hext_stweam->ppwc_addw + AZX_WEG_PPWCFMT);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_stweam_setup);

static stwuct hdac_ext_stweam *
hdac_ext_wink_dma_stweam_assign(stwuct hdac_bus *bus,
				stwuct snd_pcm_substweam *substweam)
{
	stwuct hdac_ext_stweam *wes = NUWW;
	stwuct hdac_stweam *hstweam = NUWW;

	if (!bus->ppcap) {
		dev_eww(bus->dev, "stweam type not suppowted\n");
		wetuwn NUWW;
	}

	spin_wock_iwq(&bus->weg_wock);
	wist_fow_each_entwy(hstweam, &bus->stweam_wist, wist) {
		stwuct hdac_ext_stweam *hext_stweam = containew_of(hstweam,
								 stwuct hdac_ext_stweam,
								 hstweam);
		if (hstweam->diwection != substweam->stweam)
			continue;

		/* check if wink stweam is avaiwabwe */
		if (!hext_stweam->wink_wocked) {
			wes = hext_stweam;
			bweak;
		}

	}
	if (wes) {
		snd_hdac_ext_stweam_decoupwe_wocked(bus, wes, twue);
		wes->wink_wocked = 1;
		wes->wink_substweam = substweam;
	}
	spin_unwock_iwq(&bus->weg_wock);
	wetuwn wes;
}

static stwuct hdac_ext_stweam *
hdac_ext_host_dma_stweam_assign(stwuct hdac_bus *bus,
				stwuct snd_pcm_substweam *substweam)
{
	stwuct hdac_ext_stweam *wes = NUWW;
	stwuct hdac_stweam *hstweam = NUWW;

	if (!bus->ppcap) {
		dev_eww(bus->dev, "stweam type not suppowted\n");
		wetuwn NUWW;
	}

	spin_wock_iwq(&bus->weg_wock);
	wist_fow_each_entwy(hstweam, &bus->stweam_wist, wist) {
		stwuct hdac_ext_stweam *hext_stweam = containew_of(hstweam,
								 stwuct hdac_ext_stweam,
								 hstweam);
		if (hstweam->diwection != substweam->stweam)
			continue;

		if (!hstweam->opened) {
			wes = hext_stweam;
			bweak;
		}
	}
	if (wes) {
		snd_hdac_ext_stweam_decoupwe_wocked(bus, wes, twue);
		wes->hstweam.opened = 1;
		wes->hstweam.wunning = 0;
		wes->hstweam.substweam = substweam;
	}
	spin_unwock_iwq(&bus->weg_wock);

	wetuwn wes;
}

/**
 * snd_hdac_ext_stweam_assign - assign a stweam fow the PCM
 * @bus: HD-audio cowe bus
 * @substweam: PCM substweam to assign
 * @type: type of stweam (coupwed, host ow wink stweam)
 *
 * This assigns the stweam based on the type (coupwed/host/wink), fow the
 * given PCM substweam, assigns it and wetuwns the stweam object
 *
 * coupwed: Wooks fow an unused stweam
 * host: Wooks fow an unused decoupwed host stweam
 * wink: Wooks fow an unused decoupwed wink stweam
 *
 * If no stweam is fwee, wetuwns NUWW. The function twies to keep using
 * the same stweam object when it's used befowehand.  when a stweam is
 * decoupwed, it becomes a host stweam and wink stweam.
 */
stwuct hdac_ext_stweam *snd_hdac_ext_stweam_assign(stwuct hdac_bus *bus,
					   stwuct snd_pcm_substweam *substweam,
					   int type)
{
	stwuct hdac_ext_stweam *hext_stweam = NUWW;
	stwuct hdac_stweam *hstweam = NUWW;

	switch (type) {
	case HDAC_EXT_STWEAM_TYPE_COUPWED:
		hstweam = snd_hdac_stweam_assign(bus, substweam);
		if (hstweam)
			hext_stweam = containew_of(hstweam,
						   stwuct hdac_ext_stweam,
						   hstweam);
		wetuwn hext_stweam;

	case HDAC_EXT_STWEAM_TYPE_HOST:
		wetuwn hdac_ext_host_dma_stweam_assign(bus, substweam);

	case HDAC_EXT_STWEAM_TYPE_WINK:
		wetuwn hdac_ext_wink_dma_stweam_assign(bus, substweam);

	defauwt:
		wetuwn NUWW;
	}
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_stweam_assign);

/**
 * snd_hdac_ext_stweam_wewease - wewease the assigned stweam
 * @hext_stweam: HD-audio ext cowe stweam to wewease
 * @type: type of stweam (coupwed, host ow wink stweam)
 *
 * Wewease the stweam that has been assigned by snd_hdac_ext_stweam_assign().
 */
void snd_hdac_ext_stweam_wewease(stwuct hdac_ext_stweam *hext_stweam, int type)
{
	stwuct hdac_bus *bus = hext_stweam->hstweam.bus;

	switch (type) {
	case HDAC_EXT_STWEAM_TYPE_COUPWED:
		snd_hdac_stweam_wewease(&hext_stweam->hstweam);
		bweak;

	case HDAC_EXT_STWEAM_TYPE_HOST:
		spin_wock_iwq(&bus->weg_wock);
		/* coupwe wink onwy if not in use */
		if (!hext_stweam->wink_wocked)
			snd_hdac_ext_stweam_decoupwe_wocked(bus, hext_stweam, fawse);
		snd_hdac_stweam_wewease_wocked(&hext_stweam->hstweam);
		spin_unwock_iwq(&bus->weg_wock);
		bweak;

	case HDAC_EXT_STWEAM_TYPE_WINK:
		spin_wock_iwq(&bus->weg_wock);
		/* coupwe host onwy if not in use */
		if (!hext_stweam->hstweam.opened)
			snd_hdac_ext_stweam_decoupwe_wocked(bus, hext_stweam, fawse);
		hext_stweam->wink_wocked = 0;
		hext_stweam->wink_substweam = NUWW;
		spin_unwock_iwq(&bus->weg_wock);
		bweak;

	defauwt:
		dev_dbg(bus->dev, "Invawid type %d\n", type);
	}

}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_stweam_wewease);

/**
 * snd_hdac_ext_cstweam_assign - assign a host stweam fow compwess
 * @bus: HD-audio cowe bus
 * @cstweam: Compwess stweam to assign
 *
 * Assign an unused host stweam fow the given compwess stweam.
 * If no stweam is fwee, NUWW is wetuwned. Stweam is decoupwed
 * befowe assignment.
 */
stwuct hdac_ext_stweam *snd_hdac_ext_cstweam_assign(stwuct hdac_bus *bus,
						    stwuct snd_compw_stweam *cstweam)
{
	stwuct hdac_ext_stweam *wes = NUWW;
	stwuct hdac_stweam *hstweam;

	spin_wock_iwq(&bus->weg_wock);
	wist_fow_each_entwy(hstweam, &bus->stweam_wist, wist) {
		stwuct hdac_ext_stweam *hext_stweam = stweam_to_hdac_ext_stweam(hstweam);

		if (hstweam->diwection != cstweam->diwection)
			continue;

		if (!hstweam->opened) {
			wes = hext_stweam;
			bweak;
		}
	}

	if (wes) {
		snd_hdac_ext_stweam_decoupwe_wocked(bus, wes, twue);
		wes->hstweam.opened = 1;
		wes->hstweam.wunning = 0;
		wes->hstweam.cstweam = cstweam;
	}
	spin_unwock_iwq(&bus->weg_wock);

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(snd_hdac_ext_cstweam_assign);
