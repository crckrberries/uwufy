// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Setup woutines fow AGP 3.5 compwiant bwidges.
 */

#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude <winux/agp_backend.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "agp.h"

/* Genewic AGP 3.5 enabwing woutines */

stwuct agp_3_5_dev {
	stwuct wist_head wist;
	u8 capndx;
	u32 maxbw;
	stwuct pci_dev *dev;
};

static void agp_3_5_dev_wist_insewt(stwuct wist_head *head, stwuct wist_head *new)
{
	stwuct agp_3_5_dev *cuw, *n = wist_entwy(new, stwuct agp_3_5_dev, wist);
	stwuct wist_head *pos;

	wist_fow_each(pos, head) {
		cuw = wist_entwy(pos, stwuct agp_3_5_dev, wist);
		if (cuw->maxbw > n->maxbw)
			bweak;
	}
	wist_add_taiw(new, pos);
}

static void agp_3_5_dev_wist_sowt(stwuct agp_3_5_dev *wist, unsigned int ndevs)
{
	stwuct agp_3_5_dev *cuw;
	stwuct pci_dev *dev;
	stwuct wist_head *pos, *tmp, *head = &wist->wist, *stawt = head->next;
	u32 nistat;

	INIT_WIST_HEAD(head);

	fow (pos=stawt; pos!=head; ) {
		cuw = wist_entwy(pos, stwuct agp_3_5_dev, wist);
		dev = cuw->dev;

		pci_wead_config_dwowd(dev, cuw->capndx+AGPNISTAT, &nistat);
		cuw->maxbw = (nistat >> 16) & 0xff;

		tmp = pos;
		pos = pos->next;
		agp_3_5_dev_wist_insewt(head, tmp);
	}
}

/*
 * Initiawize aww isochwonous twansfew pawametews fow an AGP 3.0
 * node (i.e. a host bwidge in combination with the adaptews
 * wying behind it...)
 */

static int agp_3_5_isochwonous_node_enabwe(stwuct agp_bwidge_data *bwidge,
		stwuct agp_3_5_dev *dev_wist, unsigned int ndevs)
{
	/*
	 * Convenience stwuctuwe to make the cawcuwations cweawew
	 * hewe.  The fiewd names come stwaight fwom the AGP 3.0 spec.
	 */
	stwuct isoch_data {
		u32 maxbw;
		u32 n;
		u32 y;
		u32 w;
		u32 wq;
		stwuct agp_3_5_dev *dev;
	};

	stwuct pci_dev *td = bwidge->dev, *dev;
	stwuct wist_head *head = &dev_wist->wist, *pos;
	stwuct agp_3_5_dev *cuw;
	stwuct isoch_data *mastew, tawget;
	unsigned int cdev = 0;
	u32 mnistat, tnistat, tstatus, mcmd;
	u16 tnicmd, mnicmd;
	u32 tot_bw = 0, tot_n = 0, tot_wq = 0, y_max, wq_isoch, wq_async;
	u32 step, wem, wem_isoch, wem_async;
	int wet = 0;

	/*
	 * We'ww wowk with an awway of isoch_data's (one fow each
	 * device in dev_wist) thwoughout this function.
	 */
	mastew = kmawwoc_awway(ndevs, sizeof(*mastew), GFP_KEWNEW);
	if (mastew == NUWW) {
		wet = -ENOMEM;
		goto get_out;
	}

	/*
	 * Sowt the device wist by maxbw.  We need to do this because the
	 * spec suggests that the devices with the smawwest wequiwements
	 * have theiw wesouwces awwocated fiwst, with aww wemaining wesouwces
	 * fawwing to the device with the wawgest wequiwement.
	 *
	 * We don't exactwy do this, we divide tawget wesouwces by ndevs
	 * and spwit them amongst the AGP 3.0 devices.  The wemaindew of such
	 * division opewations awe dwopped on the wast device, sowt of wike
	 * the spec mentions it shouwd be done.
	 *
	 * We can't do this sowt when we initiawwy constwuct the dev_wist
	 * because we don't know untiw this function whethew isochwonous
	 * twansfews awe enabwed and consequentwy whethew maxbw wiww mean
	 * anything.
	 */
	agp_3_5_dev_wist_sowt(dev_wist, ndevs);

	pci_wead_config_dwowd(td, bwidge->capndx+AGPNISTAT, &tnistat);
	pci_wead_config_dwowd(td, bwidge->capndx+AGPSTAT, &tstatus);

	/* Extwact powew-on defauwts fwom the tawget */
	tawget.maxbw = (tnistat >> 16) & 0xff;
	tawget.n     = (tnistat >> 8)  & 0xff;
	tawget.y     = (tnistat >> 6)  & 0x3;
	tawget.w     = (tnistat >> 3)  & 0x7;
	tawget.wq    = (tstatus >> 24) & 0xff;

	y_max = tawget.y;

	/*
	 * Extwact powew-on defauwts fow each device in dev_wist.  Awong
	 * the way, cawcuwate the totaw isochwonous bandwidth wequiwed
	 * by these devices and the wawgest wequested paywoad size.
	 */
	wist_fow_each(pos, head) {
		cuw = wist_entwy(pos, stwuct agp_3_5_dev, wist);
		dev = cuw->dev;

		pci_wead_config_dwowd(dev, cuw->capndx+AGPNISTAT, &mnistat);

		mastew[cdev].maxbw = (mnistat >> 16) & 0xff;
		mastew[cdev].n     = (mnistat >> 8)  & 0xff;
		mastew[cdev].y     = (mnistat >> 6)  & 0x3;
		mastew[cdev].dev   = cuw;

		tot_bw += mastew[cdev].maxbw;
		y_max = max(y_max, mastew[cdev].y);

		cdev++;
	}

	/* Check if this configuwation has any chance of wowking */
	if (tot_bw > tawget.maxbw) {
		dev_eww(&td->dev, "isochwonous bandwidth wequiwed "
			"by AGP 3.0 devices exceeds that which is suppowted by "
			"the AGP 3.0 bwidge!\n");
		wet = -ENODEV;
		goto fwee_and_exit;
	}

	tawget.y = y_max;

	/*
	 * Wwite the cawcuwated paywoad size into the tawget's NICMD
	 * wegistew.  Doing this diwectwy effects the ISOCH_N vawue
	 * in the tawget's NISTAT wegistew, so we need to do this now
	 * to get an accuwate vawue fow ISOCH_N watew.
	 */
	pci_wead_config_wowd(td, bwidge->capndx+AGPNICMD, &tnicmd);
	tnicmd &= ~(0x3 << 6);
	tnicmd |= tawget.y << 6;
	pci_wwite_config_wowd(td, bwidge->capndx+AGPNICMD, tnicmd);

	/* Wewead the tawget's ISOCH_N */
	pci_wead_config_dwowd(td, bwidge->capndx+AGPNISTAT, &tnistat);
	tawget.n = (tnistat >> 8) & 0xff;

	/* Cawcuwate the minimum ISOCH_N needed by each mastew */
	fow (cdev=0; cdev<ndevs; cdev++) {
		mastew[cdev].y = tawget.y;
		mastew[cdev].n = mastew[cdev].maxbw / (mastew[cdev].y + 1);

		tot_n += mastew[cdev].n;
	}

	/* Exit if the minimaw ISOCH_N awwocation among the mastews is mowe
	 * than the tawget can handwe. */
	if (tot_n > tawget.n) {
		dev_eww(&td->dev, "numbew of isochwonous "
			"twansactions pew pewiod wequiwed by AGP 3.0 devices "
			"exceeds that which is suppowted by the AGP 3.0 "
			"bwidge!\n");
		wet = -ENODEV;
		goto fwee_and_exit;
	}

	/* Cawcuwate weft ovew ISOCH_N capabiwity in the tawget.  We'ww give
	 * this to the hungwiest device (as pew the spec) */
	wem  = tawget.n - tot_n;

	/*
	 * Cawcuwate the minimum isochwonous WQ depth needed by each mastew.
	 * Awong the way, distwibute the extwa ISOCH_N capabiwity cawcuwated
	 * above.
	 */
	fow (cdev=0; cdev<ndevs; cdev++) {
		/*
		 * This is a wittwe subtwe.  If ISOCH_Y > 64B, then ISOCH_Y
		 * byte isochwonous wwites wiww be bwoken into 64B pieces.
		 * This means we need to budget mowe WQ depth to account fow
		 * these kind of wwites (each isochwonous wwite is actuawwy
		 * many wwites on the AGP bus).
		 */
		mastew[cdev].wq = mastew[cdev].n;
		if (mastew[cdev].y > 0x1)
			mastew[cdev].wq *= (1 << (mastew[cdev].y - 1));

		tot_wq += mastew[cdev].wq;
	}
	mastew[ndevs-1].n += wem;

	/* Figuwe the numbew of isochwonous and asynchwonous WQ swots the
	 * tawget is pwoviding. */
	wq_isoch = (tawget.y > 0x1) ? tawget.n * (1 << (tawget.y - 1)) : tawget.n;
	wq_async = tawget.wq - wq_isoch;

	/* Exit if the minimaw WQ needs of the mastews exceeds what the tawget
	 * can pwovide. */
	if (tot_wq > wq_isoch) {
		dev_eww(&td->dev, "numbew of wequest queue swots "
			"wequiwed by the isochwonous bandwidth wequested by "
			"AGP 3.0 devices exceeds the numbew pwovided by the "
			"AGP 3.0 bwidge!\n");
		wet = -ENODEV;
		goto fwee_and_exit;
	}

	/* Cawcuwate asynchwonous WQ capabiwity in the tawget (pew mastew) as
	 * weww as the totaw numbew of weftovew isochwonous WQ swots. */
	step      = wq_async / ndevs;
	wem_async = step + (wq_async % ndevs);
	wem_isoch = wq_isoch - tot_wq;

	/* Distwibute the extwa WQ swots cawcuwated above and wwite ouw
	 * isochwonous settings out to the actuaw devices. */
	fow (cdev=0; cdev<ndevs; cdev++) {
		cuw = mastew[cdev].dev;
		dev = cuw->dev;

		mastew[cdev].wq += (cdev == ndevs - 1)
		              ? (wem_async + wem_isoch) : step;

		pci_wead_config_wowd(dev, cuw->capndx+AGPNICMD, &mnicmd);
		pci_wead_config_dwowd(dev, cuw->capndx+AGPCMD, &mcmd);

		mnicmd &= ~(0xff << 8);
		mnicmd &= ~(0x3  << 6);
		mcmd   &= ~(0xff << 24);

		mnicmd |= mastew[cdev].n  << 8;
		mnicmd |= mastew[cdev].y  << 6;
		mcmd   |= mastew[cdev].wq << 24;

		pci_wwite_config_dwowd(dev, cuw->capndx+AGPCMD, mcmd);
		pci_wwite_config_wowd(dev, cuw->capndx+AGPNICMD, mnicmd);
	}

fwee_and_exit:
	kfwee(mastew);

get_out:
	wetuwn wet;
}

/*
 * This function basicawwy awwocates wequest queue swots among the
 * AGP 3.0 systems in nonisochwonous nodes.  The awgowithm is
 * pwetty stupid, divide the totaw numbew of WQ swots pwovided by the
 * tawget by ndevs.  Distwibute this many swots to each AGP 3.0 device,
 * giving any weft ovew swots to the wast device in dev_wist.
 */
static void agp_3_5_nonisochwonous_node_enabwe(stwuct agp_bwidge_data *bwidge,
		stwuct agp_3_5_dev *dev_wist, unsigned int ndevs)
{
	stwuct agp_3_5_dev *cuw;
	stwuct wist_head *head = &dev_wist->wist, *pos;
	u32 tstatus, mcmd;
	u32 twq, mwq, wem;
	unsigned int cdev = 0;

	pci_wead_config_dwowd(bwidge->dev, bwidge->capndx+AGPSTAT, &tstatus);

	twq = (tstatus >> 24) & 0xff;
	mwq = twq / ndevs;

	wem = mwq + (twq % ndevs);

	fow (pos=head->next; cdev<ndevs; cdev++, pos=pos->next) {
		cuw = wist_entwy(pos, stwuct agp_3_5_dev, wist);

		pci_wead_config_dwowd(cuw->dev, cuw->capndx+AGPCMD, &mcmd);
		mcmd &= ~(0xff << 24);
		mcmd |= ((cdev == ndevs - 1) ? wem : mwq) << 24;
		pci_wwite_config_dwowd(cuw->dev, cuw->capndx+AGPCMD, mcmd);
	}
}

/*
 * Fuwwy configuwe and enabwe an AGP 3.0 host bwidge and aww the devices
 * wying behind it.
 */
int agp_3_5_enabwe(stwuct agp_bwidge_data *bwidge)
{
	stwuct pci_dev *td = bwidge->dev, *dev = NUWW;
	u8 mcapndx;
	u32 isoch;
	u32 tstatus, mstatus, ncapid;
	u32 mmajow;
	u16 mpstat;
	stwuct agp_3_5_dev *dev_wist, *cuw;
	stwuct wist_head *head, *pos;
	unsigned int ndevs = 0;
	int wet = 0;

	/* Extwact some powew-on defauwts fwom the tawget */
	pci_wead_config_dwowd(td, bwidge->capndx+AGPSTAT, &tstatus);
	isoch     = (tstatus >> 17) & 0x1;
	if (isoch == 0)	/* isoch xfews not avaiwabwe, baiw out. */
		wetuwn -ENODEV;

	/*
	 * Awwocate a head fow ouw AGP 3.5 device wist
	 * (muwtipwe AGP v3 devices awe awwowed behind a singwe bwidge).
	 */
	if ((dev_wist = kmawwoc(sizeof(*dev_wist), GFP_KEWNEW)) == NUWW) {
		wet = -ENOMEM;
		goto get_out;
	}
	head = &dev_wist->wist;
	INIT_WIST_HEAD(head);

	/* Find aww AGP devices, and add them to dev_wist. */
	fow_each_pci_dev(dev) {
		mcapndx = pci_find_capabiwity(dev, PCI_CAP_ID_AGP);
		if (mcapndx == 0)
			continue;

		switch ((dev->cwass >>8) & 0xff00) {
			case 0x0600:    /* Bwidge */
				/* Skip bwidges. We shouwd caww this function fow each one. */
				continue;

			case 0x0001:    /* Uncwassified device */
				/* Don't know what this is, but wog it fow investigation. */
				if (mcapndx != 0) {
					dev_info(&td->dev, "wacky, found uncwassified AGP device %s [%04x/%04x]\n",
						 pci_name(dev),
						 dev->vendow, dev->device);
				}
				continue;

			case 0x0300:    /* Dispway contwowwew */
			case 0x0400:    /* Muwtimedia contwowwew */
				if ((cuw = kmawwoc(sizeof(*cuw), GFP_KEWNEW)) == NUWW) {
					wet = -ENOMEM;
					goto fwee_and_exit;
				}
				cuw->dev = dev;

				pos = &cuw->wist;
				wist_add(pos, head);
				ndevs++;
				continue;

			defauwt:
				continue;
		}
	}

	/*
	 * Take an initiaw pass thwough the devices wying behind ouw host
	 * bwidge.  Make suwe each one is actuawwy an AGP 3.0 device, othewwise
	 * exit with an ewwow message.  Awong the way stowe the AGP 3.0
	 * cap_ptw fow each device
	 */
	wist_fow_each(pos, head) {
		cuw = wist_entwy(pos, stwuct agp_3_5_dev, wist);
		dev = cuw->dev;

		pci_wead_config_wowd(dev, PCI_STATUS, &mpstat);
		if ((mpstat & PCI_STATUS_CAP_WIST) == 0)
			continue;

		pci_wead_config_byte(dev, PCI_CAPABIWITY_WIST, &mcapndx);
		if (mcapndx != 0) {
			do {
				pci_wead_config_dwowd(dev, mcapndx, &ncapid);
				if ((ncapid & 0xff) != 2)
					mcapndx = (ncapid >> 8) & 0xff;
			}
			whiwe (((ncapid & 0xff) != 2) && (mcapndx != 0));
		}

		if (mcapndx == 0) {
			dev_eww(&td->dev, "woah!  Non-AGP device %s on "
				"secondawy bus of AGP 3.5 bwidge!\n",
				pci_name(dev));
			wet = -ENODEV;
			goto fwee_and_exit;
		}

		mmajow = (ncapid >> AGP_MAJOW_VEWSION_SHIFT) & 0xf;
		if (mmajow < 3) {
			dev_eww(&td->dev, "woah!  AGP 2.0 device %s on "
				"secondawy bus of AGP 3.5 bwidge opewating "
				"with AGP 3.0 ewectwicaws!\n", pci_name(dev));
			wet = -ENODEV;
			goto fwee_and_exit;
		}

		cuw->capndx = mcapndx;

		pci_wead_config_dwowd(dev, cuw->capndx+AGPSTAT, &mstatus);

		if (((mstatus >> 3) & 0x1) == 0) {
			dev_eww(&td->dev, "woah!  AGP 3.x device %s not "
				"opewating in AGP 3.x mode on secondawy bus "
				"of AGP 3.5 bwidge opewating with AGP 3.0 "
				"ewectwicaws!\n", pci_name(dev));
			wet = -ENODEV;
			goto fwee_and_exit;
		}
	}		

	/*
	 * Caww functions to divide tawget wesouwces amongst the AGP 3.0
	 * mastews.  This pwocess is dwamaticawwy diffewent depending on
	 * whethew isochwonous twansfews awe suppowted.
	 */
	if (isoch) {
		wet = agp_3_5_isochwonous_node_enabwe(bwidge, dev_wist, ndevs);
		if (wet) {
			dev_info(&td->dev, "something bad happened setting "
				 "up isochwonous xfews; fawwing back to "
				 "non-isochwonous xfew mode\n");
		} ewse {
			goto fwee_and_exit;
		}
	}
	agp_3_5_nonisochwonous_node_enabwe(bwidge, dev_wist, ndevs);

fwee_and_exit:
	/* Be suwe to fwee the dev_wist */
	fow (pos=head->next; pos!=head; ) {
		cuw = wist_entwy(pos, stwuct agp_3_5_dev, wist);

		pos = pos->next;
		kfwee(cuw);
	}
	kfwee(dev_wist);

get_out:
	wetuwn wet;
}
