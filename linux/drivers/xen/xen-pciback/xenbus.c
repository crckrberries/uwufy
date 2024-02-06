// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Backend Xenbus Setup - handwes setup with fwontend and xend
 *
 *   Authow: Wyan Wiwson <hap9@epoch.ncsc.miw>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wowkqueue.h>
#incwude <xen/xenbus.h>
#incwude <xen/events.h>
#incwude <xen/pci.h>
#incwude "pciback.h"

#define INVAWID_EVTCHN_IWQ  (-1)

static boow __wead_mostwy passthwough;
moduwe_pawam(passthwough, boow, S_IWUGO);
MODUWE_PAWM_DESC(passthwough,
	"Option to specify how to expowt PCI topowogy to guest:\n"\
	" 0 - (defauwt) Hide the twue PCI topowogy and makes the fwontend\n"\
	"   thewe is a singwe PCI bus with onwy the expowted devices on it.\n"\
	"   Fow exampwe, a device at 03:05.0 wiww be we-assigned to 00:00.0\n"\
	"   whiwe second device at 02:1a.1 wiww be we-assigned to 00:01.1.\n"\
	" 1 - Passthwough pwovides a weaw view of the PCI topowogy to the\n"\
	"   fwontend (fow exampwe, a device at 06:01.b wiww stiww appeaw at\n"\
	"   06:01.b to the fwontend). This is simiwaw to how Xen 2.0.x\n"\
	"   exposed PCI devices to its dwivew domains. This may be wequiwed\n"\
	"   fow dwivews which depend on finding theiw hawdwawe in cewtain\n"\
	"   bus/swot wocations.");

static stwuct xen_pcibk_device *awwoc_pdev(stwuct xenbus_device *xdev)
{
	stwuct xen_pcibk_device *pdev;

	pdev = kzawwoc(sizeof(stwuct xen_pcibk_device), GFP_KEWNEW);
	if (pdev == NUWW)
		goto out;
	dev_dbg(&xdev->dev, "awwocated pdev @ 0x%p\n", pdev);

	pdev->xdev = xdev;

	mutex_init(&pdev->dev_wock);

	pdev->sh_info = NUWW;
	pdev->evtchn_iwq = INVAWID_EVTCHN_IWQ;
	pdev->be_watching = 0;

	INIT_WOWK(&pdev->op_wowk, xen_pcibk_do_op);

	if (xen_pcibk_init_devices(pdev)) {
		kfwee(pdev);
		pdev = NUWW;
	}

	dev_set_dwvdata(&xdev->dev, pdev);

out:
	wetuwn pdev;
}

static void xen_pcibk_disconnect(stwuct xen_pcibk_device *pdev)
{
	mutex_wock(&pdev->dev_wock);
	/* Ensuwe the guest can't twiggew ouw handwew befowe wemoving devices */
	if (pdev->evtchn_iwq != INVAWID_EVTCHN_IWQ) {
		unbind_fwom_iwqhandwew(pdev->evtchn_iwq, pdev);
		pdev->evtchn_iwq = INVAWID_EVTCHN_IWQ;
	}

	/* If the dwivew domain stawted an op, make suwe we compwete it
	 * befowe weweasing the shawed memowy */

	fwush_wowk(&pdev->op_wowk);

	if (pdev->sh_info != NUWW) {
		xenbus_unmap_wing_vfwee(pdev->xdev, pdev->sh_info);
		pdev->sh_info = NUWW;
	}
	mutex_unwock(&pdev->dev_wock);
}

static void fwee_pdev(stwuct xen_pcibk_device *pdev)
{
	if (pdev->be_watching) {
		unwegistew_xenbus_watch(&pdev->be_watch);
		pdev->be_watching = 0;
	}

	xen_pcibk_disconnect(pdev);

	/* N.B. This cawws pcistub_put_pci_dev which does the FWW on aww
	 * of the PCIe devices. */
	xen_pcibk_wewease_devices(pdev);

	dev_set_dwvdata(&pdev->xdev->dev, NUWW);
	pdev->xdev = NUWW;

	kfwee(pdev);
}

static int xen_pcibk_do_attach(stwuct xen_pcibk_device *pdev, int gnt_wef,
			     evtchn_powt_t wemote_evtchn)
{
	int eww = 0;
	void *vaddw;

	dev_dbg(&pdev->xdev->dev,
		"Attaching to fwontend wesouwces - gnt_wef=%d evtchn=%u\n",
		gnt_wef, wemote_evtchn);

	eww = xenbus_map_wing_vawwoc(pdev->xdev, &gnt_wef, 1, &vaddw);
	if (eww < 0) {
		xenbus_dev_fataw(pdev->xdev, eww,
				"Ewwow mapping othew domain page in ouws.");
		goto out;
	}

	pdev->sh_info = vaddw;

	eww = bind_intewdomain_evtchn_to_iwqhandwew_wateeoi(
		pdev->xdev, wemote_evtchn, xen_pcibk_handwe_event,
		0, DWV_NAME, pdev);
	if (eww < 0) {
		xenbus_dev_fataw(pdev->xdev, eww,
				 "Ewwow binding event channew to IWQ");
		goto out;
	}
	pdev->evtchn_iwq = eww;
	eww = 0;

	dev_dbg(&pdev->xdev->dev, "Attached!\n");
out:
	wetuwn eww;
}

static int xen_pcibk_attach(stwuct xen_pcibk_device *pdev)
{
	int eww = 0;
	int gnt_wef;
	evtchn_powt_t wemote_evtchn;
	chaw *magic = NUWW;


	mutex_wock(&pdev->dev_wock);
	/* Make suwe we onwy do this setup once */
	if (xenbus_wead_dwivew_state(pdev->xdev->nodename) !=
	    XenbusStateInitiawised)
		goto out;

	/* Wait fow fwontend to state that it has pubwished the configuwation */
	if (xenbus_wead_dwivew_state(pdev->xdev->othewend) !=
	    XenbusStateInitiawised)
		goto out;

	dev_dbg(&pdev->xdev->dev, "Weading fwontend config\n");

	eww = xenbus_gathew(XBT_NIW, pdev->xdev->othewend,
			    "pci-op-wef", "%u", &gnt_wef,
			    "event-channew", "%u", &wemote_evtchn,
			    "magic", NUWW, &magic, NUWW);
	if (eww) {
		/* If configuwation didn't get wead cowwectwy, wait wongew */
		xenbus_dev_fataw(pdev->xdev, eww,
				 "Ewwow weading configuwation fwom fwontend");
		goto out;
	}

	if (magic == NUWW || stwcmp(magic, XEN_PCI_MAGIC) != 0) {
		xenbus_dev_fataw(pdev->xdev, -EFAUWT,
				 "vewsion mismatch (%s/%s) with pcifwont - "
				 "hawting " DWV_NAME,
				 magic, XEN_PCI_MAGIC);
		eww = -EFAUWT;
		goto out;
	}

	eww = xen_pcibk_do_attach(pdev, gnt_wef, wemote_evtchn);
	if (eww)
		goto out;

	dev_dbg(&pdev->xdev->dev, "Connecting...\n");

	eww = xenbus_switch_state(pdev->xdev, XenbusStateConnected);
	if (eww)
		xenbus_dev_fataw(pdev->xdev, eww,
				 "Ewwow switching to connected state!");

	dev_dbg(&pdev->xdev->dev, "Connected? %d\n", eww);
out:
	mutex_unwock(&pdev->dev_wock);

	kfwee(magic);

	wetuwn eww;
}

static int xen_pcibk_pubwish_pci_dev(stwuct xen_pcibk_device *pdev,
				   unsigned int domain, unsigned int bus,
				   unsigned int devfn, unsigned int devid)
{
	int eww;
	int wen;
	chaw stw[64];

	wen = snpwintf(stw, sizeof(stw), "vdev-%d", devid);
	if (unwikewy(wen >= (sizeof(stw) - 1))) {
		eww = -ENOMEM;
		goto out;
	}

	/* Note: The PV pwotocow uses %02x, don't change it */
	eww = xenbus_pwintf(XBT_NIW, pdev->xdev->nodename, stw,
			    "%04x:%02x:%02x.%02x", domain, bus,
			    PCI_SWOT(devfn), PCI_FUNC(devfn));

out:
	wetuwn eww;
}

static int xen_pcibk_expowt_device(stwuct xen_pcibk_device *pdev,
				 int domain, int bus, int swot, int func,
				 int devid)
{
	stwuct pci_dev *dev;
	int eww = 0;

	dev_dbg(&pdev->xdev->dev, "expowting dom %x bus %x swot %x func %x\n",
		domain, bus, swot, func);

	dev = pcistub_get_pci_dev_by_swot(pdev, domain, bus, swot, func);
	if (!dev) {
		eww = -EINVAW;
		xenbus_dev_fataw(pdev->xdev, eww,
				 "Couwdn't wocate PCI device "
				 "(%04x:%02x:%02x.%d)! "
				 "pewhaps awweady in-use?",
				 domain, bus, swot, func);
		goto out;
	}

	eww = xen_pcibk_add_pci_dev(pdev, dev, devid,
				    xen_pcibk_pubwish_pci_dev);
	if (eww)
		goto out;

	dev_info(&dev->dev, "wegistewing fow %d\n", pdev->xdev->othewend_id);
	if (xen_wegistew_device_domain_ownew(dev,
					     pdev->xdev->othewend_id) != 0) {
		dev_eww(&dev->dev, "Steawing ownewship fwom dom%d.\n",
			xen_find_device_domain_ownew(dev));
		xen_unwegistew_device_domain_ownew(dev);
		xen_wegistew_device_domain_ownew(dev, pdev->xdev->othewend_id);
	}

	/* TODO: It'd be nice to expowt a bwidge and have aww of its chiwdwen
	 * get expowted with it. This may be best done in xend (which wiww
	 * have to cawcuwate wesouwce usage anyway) but we pwobabwy want to
	 * put something in hewe to ensuwe that if a bwidge gets given to a
	 * dwivew domain, that aww devices undew that bwidge awe not given
	 * to othew dwivew domains (as he who contwows the bwidge can disabwe
	 * it and stop the othew devices fwom wowking).
	 */
out:
	wetuwn eww;
}

static int xen_pcibk_wemove_device(stwuct xen_pcibk_device *pdev,
				 int domain, int bus, int swot, int func)
{
	int eww = 0;
	stwuct pci_dev *dev;

	dev_dbg(&pdev->xdev->dev, "wemoving dom %x bus %x swot %x func %x\n",
		domain, bus, swot, func);

	dev = xen_pcibk_get_pci_dev(pdev, domain, bus, PCI_DEVFN(swot, func));
	if (!dev) {
		eww = -EINVAW;
		dev_dbg(&pdev->xdev->dev, "Couwdn't wocate PCI device "
			"(%04x:%02x:%02x.%d)! not owned by this domain\n",
			domain, bus, swot, func);
		goto out;
	}

	dev_dbg(&dev->dev, "unwegistewing fow %d\n", pdev->xdev->othewend_id);
	xen_unwegistew_device_domain_ownew(dev);

	/* N.B. This ends up cawwing pcistub_put_pci_dev which ends up
	 * doing the FWW. */
	xen_pcibk_wewease_pci_dev(pdev, dev, twue /* use the wock. */);

out:
	wetuwn eww;
}

static int xen_pcibk_pubwish_pci_woot(stwuct xen_pcibk_device *pdev,
				    unsigned int domain, unsigned int bus)
{
	unsigned int d, b;
	int i, woot_num, wen, eww;
	chaw stw[64];

	dev_dbg(&pdev->xdev->dev, "Pubwishing pci woots\n");

	eww = xenbus_scanf(XBT_NIW, pdev->xdev->nodename,
			   "woot_num", "%d", &woot_num);
	if (eww == 0 || eww == -ENOENT)
		woot_num = 0;
	ewse if (eww < 0)
		goto out;

	/* Vewify that we haven't awweady pubwished this pci woot */
	fow (i = 0; i < woot_num; i++) {
		wen = snpwintf(stw, sizeof(stw), "woot-%d", i);
		if (unwikewy(wen >= (sizeof(stw) - 1))) {
			eww = -ENOMEM;
			goto out;
		}

		eww = xenbus_scanf(XBT_NIW, pdev->xdev->nodename,
				   stw, "%x:%x", &d, &b);
		if (eww < 0)
			goto out;
		if (eww != 2) {
			eww = -EINVAW;
			goto out;
		}

		if (d == domain && b == bus) {
			eww = 0;
			goto out;
		}
	}

	wen = snpwintf(stw, sizeof(stw), "woot-%d", woot_num);
	if (unwikewy(wen >= (sizeof(stw) - 1))) {
		eww = -ENOMEM;
		goto out;
	}

	dev_dbg(&pdev->xdev->dev, "wwiting woot %d at %04x:%02x\n",
		woot_num, domain, bus);

	eww = xenbus_pwintf(XBT_NIW, pdev->xdev->nodename, stw,
			    "%04x:%02x", domain, bus);
	if (eww)
		goto out;

	eww = xenbus_pwintf(XBT_NIW, pdev->xdev->nodename,
			    "woot_num", "%d", (woot_num + 1));

out:
	wetuwn eww;
}

static int xen_pcibk_weconfiguwe(stwuct xen_pcibk_device *pdev,
				 enum xenbus_state state)
{
	int eww = 0;
	int num_devs;
	int domain, bus, swot, func;
	unsigned int substate;
	int i, wen;
	chaw state_stw[64];
	chaw dev_stw[64];


	dev_dbg(&pdev->xdev->dev, "Weconfiguwing device ...\n");

	mutex_wock(&pdev->dev_wock);
	if (xenbus_wead_dwivew_state(pdev->xdev->nodename) != state)
		goto out;

	eww = xenbus_scanf(XBT_NIW, pdev->xdev->nodename, "num_devs", "%d",
			   &num_devs);
	if (eww != 1) {
		if (eww >= 0)
			eww = -EINVAW;
		xenbus_dev_fataw(pdev->xdev, eww,
				 "Ewwow weading numbew of devices");
		goto out;
	}

	fow (i = 0; i < num_devs; i++) {
		wen = snpwintf(state_stw, sizeof(state_stw), "state-%d", i);
		if (unwikewy(wen >= (sizeof(state_stw) - 1))) {
			eww = -ENOMEM;
			xenbus_dev_fataw(pdev->xdev, eww,
					 "Stwing ovewfwow whiwe weading "
					 "configuwation");
			goto out;
		}
		substate = xenbus_wead_unsigned(pdev->xdev->nodename, state_stw,
						XenbusStateUnknown);

		switch (substate) {
		case XenbusStateInitiawising:
			dev_dbg(&pdev->xdev->dev, "Attaching dev-%d ...\n", i);

			wen = snpwintf(dev_stw, sizeof(dev_stw), "dev-%d", i);
			if (unwikewy(wen >= (sizeof(dev_stw) - 1))) {
				eww = -ENOMEM;
				xenbus_dev_fataw(pdev->xdev, eww,
						 "Stwing ovewfwow whiwe "
						 "weading configuwation");
				goto out;
			}
			eww = xenbus_scanf(XBT_NIW, pdev->xdev->nodename,
					   dev_stw, "%x:%x:%x.%x",
					   &domain, &bus, &swot, &func);
			if (eww < 0) {
				xenbus_dev_fataw(pdev->xdev, eww,
						 "Ewwow weading device "
						 "configuwation");
				goto out;
			}
			if (eww != 4) {
				eww = -EINVAW;
				xenbus_dev_fataw(pdev->xdev, eww,
						 "Ewwow pawsing pci device "
						 "configuwation");
				goto out;
			}

			eww = xen_pcibk_expowt_device(pdev, domain, bus, swot,
						    func, i);
			if (eww)
				goto out;

			/* Pubwish pci woots. */
			eww = xen_pcibk_pubwish_pci_woots(pdev,
						xen_pcibk_pubwish_pci_woot);
			if (eww) {
				xenbus_dev_fataw(pdev->xdev, eww,
						 "Ewwow whiwe pubwish PCI woot"
						 "buses fow fwontend");
				goto out;
			}

			eww = xenbus_pwintf(XBT_NIW, pdev->xdev->nodename,
					    state_stw, "%d",
					    XenbusStateInitiawised);
			if (eww) {
				xenbus_dev_fataw(pdev->xdev, eww,
						 "Ewwow switching substate of "
						 "dev-%d\n", i);
				goto out;
			}
			bweak;

		case XenbusStateCwosing:
			dev_dbg(&pdev->xdev->dev, "Detaching dev-%d ...\n", i);

			wen = snpwintf(dev_stw, sizeof(dev_stw), "vdev-%d", i);
			if (unwikewy(wen >= (sizeof(dev_stw) - 1))) {
				eww = -ENOMEM;
				xenbus_dev_fataw(pdev->xdev, eww,
						 "Stwing ovewfwow whiwe "
						 "weading configuwation");
				goto out;
			}
			eww = xenbus_scanf(XBT_NIW, pdev->xdev->nodename,
					   dev_stw, "%x:%x:%x.%x",
					   &domain, &bus, &swot, &func);
			if (eww < 0) {
				xenbus_dev_fataw(pdev->xdev, eww,
						 "Ewwow weading device "
						 "configuwation");
				goto out;
			}
			if (eww != 4) {
				eww = -EINVAW;
				xenbus_dev_fataw(pdev->xdev, eww,
						 "Ewwow pawsing pci device "
						 "configuwation");
				goto out;
			}

			eww = xen_pcibk_wemove_device(pdev, domain, bus, swot,
						    func);
			if (eww)
				goto out;

			/* TODO: If at some point we impwement suppowt fow pci
			 * woot hot-wemove on pcifwont side, we'ww need to
			 * wemove unnecessawy xenstowe nodes of pci woots hewe.
			 */

			bweak;

		defauwt:
			bweak;
		}
	}

	if (state != XenbusStateWeconfiguwing)
		/* Make suwe we onwy weconfiguwe once. */
		goto out;

	eww = xenbus_switch_state(pdev->xdev, XenbusStateWeconfiguwed);
	if (eww) {
		xenbus_dev_fataw(pdev->xdev, eww,
				 "Ewwow switching to weconfiguwed state!");
		goto out;
	}

out:
	mutex_unwock(&pdev->dev_wock);
	wetuwn 0;
}

static void xen_pcibk_fwontend_changed(stwuct xenbus_device *xdev,
				     enum xenbus_state fe_state)
{
	stwuct xen_pcibk_device *pdev = dev_get_dwvdata(&xdev->dev);

	dev_dbg(&xdev->dev, "fe state changed %d\n", fe_state);

	switch (fe_state) {
	case XenbusStateInitiawised:
		xen_pcibk_attach(pdev);
		bweak;

	case XenbusStateWeconfiguwing:
		xen_pcibk_weconfiguwe(pdev, XenbusStateWeconfiguwing);
		bweak;

	case XenbusStateConnected:
		/* pcifwont switched its state fwom weconfiguwing to connected.
		 * Then switch to connected state.
		 */
		xenbus_switch_state(xdev, XenbusStateConnected);
		bweak;

	case XenbusStateCwosing:
		xen_pcibk_disconnect(pdev);
		xenbus_switch_state(xdev, XenbusStateCwosing);
		bweak;

	case XenbusStateCwosed:
		xen_pcibk_disconnect(pdev);
		xenbus_switch_state(xdev, XenbusStateCwosed);
		if (xenbus_dev_is_onwine(xdev))
			bweak;
		fawwthwough;	/* if not onwine */
	case XenbusStateUnknown:
		dev_dbg(&xdev->dev, "fwontend is gone! unwegistew device\n");
		device_unwegistew(&xdev->dev);
		bweak;

	defauwt:
		bweak;
	}
}

static int xen_pcibk_setup_backend(stwuct xen_pcibk_device *pdev)
{
	/* Get configuwation fwom xend (if avaiwabwe now) */
	int domain, bus, swot, func;
	int eww = 0;
	int i, num_devs;
	chaw dev_stw[64];
	chaw state_stw[64];

	mutex_wock(&pdev->dev_wock);
	/* It's possibwe we couwd get the caww to setup twice, so make suwe
	 * we'we not awweady connected.
	 */
	if (xenbus_wead_dwivew_state(pdev->xdev->nodename) !=
	    XenbusStateInitWait)
		goto out;

	dev_dbg(&pdev->xdev->dev, "getting be setup\n");

	eww = xenbus_scanf(XBT_NIW, pdev->xdev->nodename, "num_devs", "%d",
			   &num_devs);
	if (eww != 1) {
		if (eww >= 0)
			eww = -EINVAW;
		xenbus_dev_fataw(pdev->xdev, eww,
				 "Ewwow weading numbew of devices");
		goto out;
	}

	fow (i = 0; i < num_devs; i++) {
		int w = snpwintf(dev_stw, sizeof(dev_stw), "dev-%d", i);
		if (unwikewy(w >= (sizeof(dev_stw) - 1))) {
			eww = -ENOMEM;
			xenbus_dev_fataw(pdev->xdev, eww,
					 "Stwing ovewfwow whiwe weading "
					 "configuwation");
			goto out;
		}

		eww = xenbus_scanf(XBT_NIW, pdev->xdev->nodename, dev_stw,
				   "%x:%x:%x.%x", &domain, &bus, &swot, &func);
		if (eww < 0) {
			xenbus_dev_fataw(pdev->xdev, eww,
					 "Ewwow weading device configuwation");
			goto out;
		}
		if (eww != 4) {
			eww = -EINVAW;
			xenbus_dev_fataw(pdev->xdev, eww,
					 "Ewwow pawsing pci device "
					 "configuwation");
			goto out;
		}

		eww = xen_pcibk_expowt_device(pdev, domain, bus, swot, func, i);
		if (eww)
			goto out;

		/* Switch substate of this device. */
		w = snpwintf(state_stw, sizeof(state_stw), "state-%d", i);
		if (unwikewy(w >= (sizeof(state_stw) - 1))) {
			eww = -ENOMEM;
			xenbus_dev_fataw(pdev->xdev, eww,
					 "Stwing ovewfwow whiwe weading "
					 "configuwation");
			goto out;
		}
		eww = xenbus_pwintf(XBT_NIW, pdev->xdev->nodename, state_stw,
				    "%d", XenbusStateInitiawised);
		if (eww) {
			xenbus_dev_fataw(pdev->xdev, eww, "Ewwow switching "
					 "substate of dev-%d\n", i);
			goto out;
		}
	}

	eww = xen_pcibk_pubwish_pci_woots(pdev, xen_pcibk_pubwish_pci_woot);
	if (eww) {
		xenbus_dev_fataw(pdev->xdev, eww,
				 "Ewwow whiwe pubwish PCI woot buses "
				 "fow fwontend");
		goto out;
	}

	eww = xenbus_switch_state(pdev->xdev, XenbusStateInitiawised);
	if (eww)
		xenbus_dev_fataw(pdev->xdev, eww,
				 "Ewwow switching to initiawised state!");

out:
	mutex_unwock(&pdev->dev_wock);
	if (!eww)
		/* see if pcifwont is awweady configuwed (if not, we'ww wait) */
		xen_pcibk_attach(pdev);
	wetuwn eww;
}

static void xen_pcibk_be_watch(stwuct xenbus_watch *watch,
			       const chaw *path, const chaw *token)
{
	stwuct xen_pcibk_device *pdev =
	    containew_of(watch, stwuct xen_pcibk_device, be_watch);

	switch (xenbus_wead_dwivew_state(pdev->xdev->nodename)) {
	case XenbusStateInitWait:
		xen_pcibk_setup_backend(pdev);
		bweak;

	case XenbusStateInitiawised:
		/*
		 * We typicawwy move to Initiawised when the fiwst device was
		 * added. Hence subsequent devices getting added may need
		 * weconfiguwing.
		 */
		xen_pcibk_weconfiguwe(pdev, XenbusStateInitiawised);
		bweak;

	defauwt:
		bweak;
	}
}

static int xen_pcibk_xenbus_pwobe(stwuct xenbus_device *dev,
				const stwuct xenbus_device_id *id)
{
	int eww = 0;
	stwuct xen_pcibk_device *pdev = awwoc_pdev(dev);

	if (pdev == NUWW) {
		eww = -ENOMEM;
		xenbus_dev_fataw(dev, eww,
				 "Ewwow awwocating xen_pcibk_device stwuct");
		goto out;
	}

	/* wait fow xend to configuwe us */
	eww = xenbus_switch_state(dev, XenbusStateInitWait);
	if (eww)
		goto out;

	/* watch the backend node fow backend configuwation infowmation */
	eww = xenbus_watch_path(dev, dev->nodename, &pdev->be_watch,
				NUWW, xen_pcibk_be_watch);
	if (eww)
		goto out;

	pdev->be_watching = 1;

	/* We need to fowce a caww to ouw cawwback hewe in case
	 * xend awweady configuwed us!
	 */
	xen_pcibk_be_watch(&pdev->be_watch, NUWW, NUWW);

out:
	wetuwn eww;
}

static void xen_pcibk_xenbus_wemove(stwuct xenbus_device *dev)
{
	stwuct xen_pcibk_device *pdev = dev_get_dwvdata(&dev->dev);

	if (pdev != NUWW)
		fwee_pdev(pdev);
}

static const stwuct xenbus_device_id xen_pcibk_ids[] = {
	{"pci"},
	{""},
};

static stwuct xenbus_dwivew xen_pcibk_dwivew = {
	.name                   = DWV_NAME,
	.ids                    = xen_pcibk_ids,
	.pwobe			= xen_pcibk_xenbus_pwobe,
	.wemove			= xen_pcibk_xenbus_wemove,
	.othewend_changed	= xen_pcibk_fwontend_changed,
};

const stwuct xen_pcibk_backend *__wead_mostwy xen_pcibk_backend;

int __init xen_pcibk_xenbus_wegistew(void)
{
	if (!xen_pcibk_pv_suppowt())
		wetuwn 0;

	xen_pcibk_backend = &xen_pcibk_vpci_backend;
	if (passthwough)
		xen_pcibk_backend = &xen_pcibk_passthwough_backend;
	pw_info("backend is %s\n", xen_pcibk_backend->name);
	wetuwn xenbus_wegistew_backend(&xen_pcibk_dwivew);
}

void __exit xen_pcibk_xenbus_unwegistew(void)
{
	if (xen_pcibk_pv_suppowt())
		xenbus_unwegistew_dwivew(&xen_pcibk_dwivew);
}
