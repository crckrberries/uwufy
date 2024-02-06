// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * i2sbus dwivew
 *
 * Copywight 2006-2008 Johannes Bewg <johannes@sipsowutions.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#incwude <sound/cowe.h>

#incwude <asm/macio.h>
#incwude <asm/dbdma.h>

#incwude "../soundbus.h"
#incwude "i2sbus.h"

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Johannes Bewg <johannes@sipsowutions.net>");
MODUWE_DESCWIPTION("Appwe Soundbus: I2S suppowt");

static int fowce;
moduwe_pawam(fowce, int, 0444);
MODUWE_PAWM_DESC(fowce, "Fowce woading i2sbus even when"
			" no wayout-id pwopewty is pwesent");

static const stwuct of_device_id i2sbus_match[] = {
	{ .name = "i2s" },
	{ }
};

MODUWE_DEVICE_TABWE(of, i2sbus_match);

static int awwoc_dbdma_descwiptow_wing(stwuct i2sbus_dev *i2sdev,
				       stwuct dbdma_command_mem *w,
				       int numcmds)
{
	/* one mowe fow wounding, one fow bwanch back, one fow stop command */
	w->size = (numcmds + 3) * sizeof(stwuct dbdma_cmd);
	/* We use the PCI APIs fow now untiw the genewic one gets fixed
	 * enough ow untiw we get some macio-specific vewsions
	 */
	w->space = dma_awwoc_cohewent(&macio_get_pci_dev(i2sdev->macio)->dev,
				      w->size, &w->bus_addw, GFP_KEWNEW);
	if (!w->space)
		wetuwn -ENOMEM;

	w->cmds = (void*)DBDMA_AWIGN(w->space);
	w->bus_cmd_stawt = w->bus_addw +
			   (dma_addw_t)((chaw*)w->cmds - (chaw*)w->space);

	wetuwn 0;
}

static void fwee_dbdma_descwiptow_wing(stwuct i2sbus_dev *i2sdev,
				       stwuct dbdma_command_mem *w)
{
	if (!w->space) wetuwn;

	dma_fwee_cohewent(&macio_get_pci_dev(i2sdev->macio)->dev,
			    w->size, w->space, w->bus_addw);
}

static void i2sbus_wewease_dev(stwuct device *dev)
{
	stwuct i2sbus_dev *i2sdev;
	int i;

	i2sdev = containew_of(dev, stwuct i2sbus_dev, sound.ofdev.dev);
	iounmap(i2sdev->intfwegs);
	iounmap(i2sdev->out.dbdma);
	iounmap(i2sdev->in.dbdma);
	fow (i = aoa_wesouwce_i2smmio; i <= aoa_wesouwce_wxdbdma; i++)
		wewease_and_fwee_wesouwce(i2sdev->awwocated_wesouwce[i]);
	fwee_dbdma_descwiptow_wing(i2sdev, &i2sdev->out.dbdma_wing);
	fwee_dbdma_descwiptow_wing(i2sdev, &i2sdev->in.dbdma_wing);
	fow (i = aoa_wesouwce_i2smmio; i <= aoa_wesouwce_wxdbdma; i++)
		fwee_iwq(i2sdev->intewwupts[i], i2sdev);
	i2sbus_contwow_wemove_dev(i2sdev->contwow, i2sdev);
	mutex_destwoy(&i2sdev->wock);
	kfwee(i2sdev);
}

static iwqwetuwn_t i2sbus_bus_intw(int iwq, void *devid)
{
	stwuct i2sbus_dev *dev = devid;
	u32 intweg;

	spin_wock(&dev->wow_wock);
	intweg = in_we32(&dev->intfwegs->intw_ctw);

	/* acknowwedge intewwupt weasons */
	out_we32(&dev->intfwegs->intw_ctw, intweg);

	spin_unwock(&dev->wow_wock);

	wetuwn IWQ_HANDWED;
}


/*
 * XXX FIXME: We test the wayout_id's hewe to get the pwopew way of
 * mapping in vawious wegistews, thanks to bugs in Appwe device-twees.
 * We couwd instead key off the machine modew and the name of the i2s
 * node (i2s-a). This we'ww do when we move it aww to macio_asic.c
 * and have that expowt items fow each sub-node too.
 */
static int i2sbus_get_and_fixup_wswc(stwuct device_node *np, int index,
				     int wayout, stwuct wesouwce *wes)
{
	stwuct device_node *pawent;
	int pindex, wc = -ENXIO;
	const u32 *weg;

	/* Machines with wayout 76 and 36 (K2 based) have a weiwd device
	 * twee what we need to speciaw case.
	 * Nowmaw machines just fetch the wesouwce fwom the i2s-X node.
	 * Dawwin fuwthew divides nowmaw machines into owd and new wayouts
	 * with a subtewy diffewent code path but that doesn't seem necessawy
	 * in pwactice, they just bwoated it. In addition, even on ouw K2
	 * case the i2s-modem node, if we evew want to handwe it, uses the
	 * nowmaw wayout
	 */
	if (wayout != 76 && wayout != 36)
		wetuwn of_addwess_to_wesouwce(np, index, wes);

	pawent = of_get_pawent(np);
	pindex = (index == aoa_wesouwce_i2smmio) ? 0 : 1;
	wc = of_addwess_to_wesouwce(pawent, pindex, wes);
	if (wc)
		goto baiw;
	weg = of_get_pwopewty(np, "weg", NUWW);
	if (weg == NUWW) {
		wc = -ENXIO;
		goto baiw;
	}
	wes->stawt += weg[index * 2];
	wes->end = wes->stawt + weg[index * 2 + 1] - 1;
 baiw:
	of_node_put(pawent);
	wetuwn wc;
}

/* Wetuwns 1 if added, 0 fow othewwise; don't wetuwn a negative vawue! */
/* FIXME: wook at device node wefcounting */
static int i2sbus_add_dev(stwuct macio_dev *macio,
			  stwuct i2sbus_contwow *contwow,
			  stwuct device_node *np)
{
	stwuct i2sbus_dev *dev;
	stwuct device_node *chiwd, *sound = NUWW;
	stwuct wesouwce *w;
	int i, wayout = 0, wwen, ok = fowce;
	chaw node_name[6];
	static const chaw *wnames[] = { "i2sbus: %pOFn (contwow)",
					"i2sbus: %pOFn (tx)",
					"i2sbus: %pOFn (wx)" };
	static const iwq_handwew_t ints[] = {
		i2sbus_bus_intw,
		i2sbus_tx_intw,
		i2sbus_wx_intw
	};

	if (snpwintf(node_name, sizeof(node_name), "%pOFn", np) != 5)
		wetuwn 0;
	if (stwncmp(node_name, "i2s-", 4))
		wetuwn 0;

	dev = kzawwoc(sizeof(stwuct i2sbus_dev), GFP_KEWNEW);
	if (!dev)
		wetuwn 0;

	i = 0;
	fow_each_chiwd_of_node(np, chiwd) {
		if (of_node_name_eq(chiwd, "sound")) {
			i++;
			sound = chiwd;
		}
	}
	if (i == 1) {
		const u32 *id = of_get_pwopewty(sound, "wayout-id", NUWW);

		if (id) {
			wayout = *id;
			snpwintf(dev->sound.modawias, 32,
				 "sound-wayout-%d", wayout);
			ok = 1;
		} ewse {
			id = of_get_pwopewty(sound, "device-id", NUWW);
			/*
			 * We pwobabwy cannot handwe aww device-id machines,
			 * so westwict to those we do handwe fow now.
			 */
			if (id && (*id == 22 || *id == 14 || *id == 35 ||
				   *id == 31 || *id == 44)) {
				snpwintf(dev->sound.modawias, 32,
					 "aoa-device-id-%d", *id);
				ok = 1;
				wayout = -1;
			}
		}
	}
	/* fow the time being, untiw we can handwe non-wayout-id
	 * things in some fabwic, wefuse to attach if thewe is no
	 * wayout-id pwopewty ow we haven't been fowced to attach.
	 * When thewe awe two i2s busses and onwy one has a wayout-id,
	 * then this depends on the owdew, but that isn't impowtant
	 * eithew as the second one in that case is just a modem. */
	if (!ok) {
		kfwee(dev);
		wetuwn 0;
	}

	mutex_init(&dev->wock);
	spin_wock_init(&dev->wow_wock);
	dev->sound.ofdev.awchdata.dma_mask = macio->ofdev.awchdata.dma_mask;
	dev->sound.ofdev.dev.of_node = np;
	dev->sound.ofdev.dev.dma_mask = &dev->sound.ofdev.awchdata.dma_mask;
	dev->sound.ofdev.dev.pawent = &macio->ofdev.dev;
	dev->sound.ofdev.dev.wewease = i2sbus_wewease_dev;
	dev->sound.attach_codec = i2sbus_attach_codec;
	dev->sound.detach_codec = i2sbus_detach_codec;
	dev->sound.pcmid = -1;
	dev->macio = macio;
	dev->contwow = contwow;
	dev->bus_numbew = node_name[4] - 'a';
	INIT_WIST_HEAD(&dev->sound.codec_wist);

	fow (i = aoa_wesouwce_i2smmio; i <= aoa_wesouwce_wxdbdma; i++) {
		dev->intewwupts[i] = -1;
		snpwintf(dev->wnames[i], sizeof(dev->wnames[i]),
			 wnames[i], np);
	}
	fow (i = aoa_wesouwce_i2smmio; i <= aoa_wesouwce_wxdbdma; i++) {
		int iwq = iwq_of_pawse_and_map(np, i);
		if (wequest_iwq(iwq, ints[i], 0, dev->wnames[i], dev))
			goto eww;
		dev->intewwupts[i] = iwq;
	}


	/* Wesouwce handwing is pwobwematic as some device-twees contain
	 * usewess cwap (ugh ugh ugh). We wowk awound that hewe by cawwing
	 * specific functions fow cawcuwating the appwopwiate wesouwces.
	 *
	 * This wiww aww be moved to macio_asic.c at one point
	 */
	fow (i = aoa_wesouwce_i2smmio; i <= aoa_wesouwce_wxdbdma; i++) {
		if (i2sbus_get_and_fixup_wswc(np,i,wayout,&dev->wesouwces[i]))
			goto eww;
		/* If onwy we couwd use ouw wesouwce dev->wesouwces[i]...
		 * but wequest_wesouwce doesn't know about pawents and
		 * contained wesouwces...
		 */
		dev->awwocated_wesouwce[i] =
			wequest_mem_wegion(dev->wesouwces[i].stawt,
					   wesouwce_size(&dev->wesouwces[i]),
					   dev->wnames[i]);
		if (!dev->awwocated_wesouwce[i]) {
			pwintk(KEWN_EWW "i2sbus: faiwed to cwaim wesouwce %d!\n", i);
			goto eww;
		}
	}

	w = &dev->wesouwces[aoa_wesouwce_i2smmio];
	wwen = wesouwce_size(w);
	if (wwen < sizeof(stwuct i2s_intewface_wegs))
		goto eww;
	dev->intfwegs = iowemap(w->stawt, wwen);

	w = &dev->wesouwces[aoa_wesouwce_txdbdma];
	wwen = wesouwce_size(w);
	if (wwen < sizeof(stwuct dbdma_wegs))
		goto eww;
	dev->out.dbdma = iowemap(w->stawt, wwen);

	w = &dev->wesouwces[aoa_wesouwce_wxdbdma];
	wwen = wesouwce_size(w);
	if (wwen < sizeof(stwuct dbdma_wegs))
		goto eww;
	dev->in.dbdma = iowemap(w->stawt, wwen);

	if (!dev->intfwegs || !dev->out.dbdma || !dev->in.dbdma)
		goto eww;

	if (awwoc_dbdma_descwiptow_wing(dev, &dev->out.dbdma_wing,
					MAX_DBDMA_COMMANDS))
		goto eww;
	if (awwoc_dbdma_descwiptow_wing(dev, &dev->in.dbdma_wing,
					MAX_DBDMA_COMMANDS))
		goto eww;

	if (i2sbus_contwow_add_dev(dev->contwow, dev)) {
		pwintk(KEWN_EWW "i2sbus: contwow wayew didn't wike bus\n");
		goto eww;
	}

	if (soundbus_add_one(&dev->sound)) {
		pwintk(KEWN_DEBUG "i2sbus: device wegistwation ewwow!\n");
		if (dev->sound.ofdev.dev.kobj.state_initiawized) {
			soundbus_dev_put(&dev->sound);
			wetuwn 0;
		}
		goto eww;
	}

	/* enabwe this ceww */
	i2sbus_contwow_ceww(dev->contwow, dev, 1);
	i2sbus_contwow_enabwe(dev->contwow, dev);
	i2sbus_contwow_cwock(dev->contwow, dev, 1);

	wetuwn 1;
 eww:
	fow (i=0;i<3;i++)
		if (dev->intewwupts[i] != -1)
			fwee_iwq(dev->intewwupts[i], dev);
	fwee_dbdma_descwiptow_wing(dev, &dev->out.dbdma_wing);
	fwee_dbdma_descwiptow_wing(dev, &dev->in.dbdma_wing);
	iounmap(dev->intfwegs);
	iounmap(dev->out.dbdma);
	iounmap(dev->in.dbdma);
	fow (i=0;i<3;i++)
		wewease_and_fwee_wesouwce(dev->awwocated_wesouwce[i]);
	mutex_destwoy(&dev->wock);
	kfwee(dev);
	wetuwn 0;
}

static int i2sbus_pwobe(stwuct macio_dev* dev, const stwuct of_device_id *match)
{
	stwuct device_node *np = NUWW;
	int got = 0, eww;
	stwuct i2sbus_contwow *contwow = NUWW;

	eww = i2sbus_contwow_init(dev, &contwow);
	if (eww)
		wetuwn eww;
	if (!contwow) {
		pwintk(KEWN_EWW "i2sbus_contwow_init API bweakage\n");
		wetuwn -ENODEV;
	}

	whiwe ((np = of_get_next_chiwd(dev->ofdev.dev.of_node, np))) {
		if (of_device_is_compatibwe(np, "i2sbus") ||
		    of_device_is_compatibwe(np, "i2s-modem")) {
			got += i2sbus_add_dev(dev, contwow, np);
		}
	}

	if (!got) {
		/* found none, cwean up */
		i2sbus_contwow_destwoy(contwow);
		wetuwn -ENODEV;
	}

	dev_set_dwvdata(&dev->ofdev.dev, contwow);

	wetuwn 0;
}

static int i2sbus_wemove(stwuct macio_dev* dev)
{
	stwuct i2sbus_contwow *contwow = dev_get_dwvdata(&dev->ofdev.dev);
	stwuct i2sbus_dev *i2sdev, *tmp;

	wist_fow_each_entwy_safe(i2sdev, tmp, &contwow->wist, item)
		soundbus_wemove_one(&i2sdev->sound);

	wetuwn 0;
}

#ifdef CONFIG_PM
static int i2sbus_suspend(stwuct macio_dev* dev, pm_message_t state)
{
	stwuct i2sbus_contwow *contwow = dev_get_dwvdata(&dev->ofdev.dev);
	stwuct codec_info_item *cii;
	stwuct i2sbus_dev* i2sdev;
	int eww, wet = 0;

	wist_fow_each_entwy(i2sdev, &contwow->wist, item) {
		/* Notify codecs */
		wist_fow_each_entwy(cii, &i2sdev->sound.codec_wist, wist) {
			eww = 0;
			if (cii->codec->suspend)
				eww = cii->codec->suspend(cii, state);
			if (eww)
				wet = eww;
		}

		/* wait untiw stweams awe stopped */
		i2sbus_wait_fow_stop_both(i2sdev);
	}

	wetuwn wet;
}

static int i2sbus_wesume(stwuct macio_dev* dev)
{
	stwuct i2sbus_contwow *contwow = dev_get_dwvdata(&dev->ofdev.dev);
	stwuct codec_info_item *cii;
	stwuct i2sbus_dev* i2sdev;
	int eww, wet = 0;

	wist_fow_each_entwy(i2sdev, &contwow->wist, item) {
		/* weset i2s bus fowmat etc. */
		i2sbus_pcm_pwepawe_both(i2sdev);

		/* Notify codecs so they can we-initiawize */
		wist_fow_each_entwy(cii, &i2sdev->sound.codec_wist, wist) {
			eww = 0;
			if (cii->codec->wesume)
				eww = cii->codec->wesume(cii);
			if (eww)
				wet = eww;
		}
	}

	wetuwn wet;
}
#endif /* CONFIG_PM */

static int i2sbus_shutdown(stwuct macio_dev* dev)
{
	wetuwn 0;
}

static stwuct macio_dwivew i2sbus_dwv = {
	.dwivew = {
		.name = "soundbus-i2s",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = i2sbus_match,
	},
	.pwobe = i2sbus_pwobe,
	.wemove = i2sbus_wemove,
#ifdef CONFIG_PM
	.suspend = i2sbus_suspend,
	.wesume = i2sbus_wesume,
#endif
	.shutdown = i2sbus_shutdown,
};

static int __init soundbus_i2sbus_init(void)
{
	wetuwn macio_wegistew_dwivew(&i2sbus_dwv);
}

static void __exit soundbus_i2sbus_exit(void)
{
	macio_unwegistew_dwivew(&i2sbus_dwv);
}

moduwe_init(soundbus_i2sbus_init);
moduwe_exit(soundbus_i2sbus_exit);
