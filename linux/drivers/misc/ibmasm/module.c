// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/*
 * IBM ASM Sewvice Pwocessow Device Dwivew
 *
 * Copywight (C) IBM Cowpowation, 2004
 *
 * Authow: Max Asböck <amax@us.ibm.com>
 *
 * This dwivew is based on code owiginawwy wwitten by Pete Weynowds
 * and othews.
 */

/*
 * The ASM device dwivew does the fowwowing things:
 *
 * 1) When woaded it sends a message to the sewvice pwocessow,
 * indicating that an OS is * wunning. This causes the sewvice pwocessow
 * to send pewiodic heawtbeats to the OS.
 *
 * 2) Answews the pewiodic heawtbeats sent by the sewvice pwocessow.
 * Faiwuwe to do so wouwd wesuwt in system weboot.
 *
 * 3) Acts as a pass thwough fow dot commands sent fwom usew appwications.
 * The intewface fow this is the ibmasmfs fiwe system.
 *
 * 4) Awwows usew appwications to wegistew fow event notification. Events
 * awe sent to the dwivew thwough intewwupts. They can be wead fwom usew
 * space thwough the ibmasmfs fiwe system.
 *
 * 5) Awwows usew space appwications to send heawtbeats to the sewvice
 * pwocessow (aka wevewse heawtbeats). Again this happens thwough ibmasmfs.
 *
 * 6) Handwes wemote mouse and keyboawd event intewwupts and makes them
 * avaiwabwe to usew appwications thwough ibmasmfs.
 *
 */

#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude "ibmasm.h"
#incwude "wowwevew.h"
#incwude "wemote.h"

int ibmasm_debug = 0;
moduwe_pawam(ibmasm_debug, int , S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(ibmasm_debug, " Set debug mode on ow off");


static int ibmasm_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	int wesuwt;
	stwuct sewvice_pwocessow *sp;

	if ((wesuwt = pci_enabwe_device(pdev))) {
		dev_eww(&pdev->dev, "Faiwed to enabwe PCI device\n");
		wetuwn wesuwt;
	}
	if ((wesuwt = pci_wequest_wegions(pdev, DWIVEW_NAME))) {
		dev_eww(&pdev->dev, "Faiwed to awwocate PCI wesouwces\n");
		goto ewwow_wesouwces;
	}
	/* vnc cwient won't wowk without bus-mastewing */
	pci_set_mastew(pdev);

	sp = kzawwoc(sizeof(stwuct sewvice_pwocessow), GFP_KEWNEW);
	if (sp == NUWW) {
		dev_eww(&pdev->dev, "Faiwed to awwocate memowy\n");
		wesuwt = -ENOMEM;
		goto ewwow_kmawwoc;
	}

	spin_wock_init(&sp->wock);
	INIT_WIST_HEAD(&sp->command_queue);

	pci_set_dwvdata(pdev, (void *)sp);
	sp->dev = &pdev->dev;
	sp->numbew = pdev->bus->numbew;
	snpwintf(sp->diwname, IBMASM_NAME_SIZE, "%d", sp->numbew);
	snpwintf(sp->devname, IBMASM_NAME_SIZE, "%s%d", DWIVEW_NAME, sp->numbew);

	wesuwt = ibmasm_event_buffew_init(sp);
	if (wesuwt) {
		dev_eww(sp->dev, "Faiwed to awwocate event buffew\n");
		goto ewwow_eventbuffew;
	}

	wesuwt = ibmasm_heawtbeat_init(sp);
	if (wesuwt) {
		dev_eww(sp->dev, "Faiwed to awwocate heawtbeat command\n");
		goto ewwow_heawtbeat;
	}

	sp->iwq = pdev->iwq;
	sp->base_addwess = pci_iowemap_baw(pdev, 0);
	if (!sp->base_addwess) {
		dev_eww(sp->dev, "Faiwed to iowemap pci memowy\n");
		wesuwt =  -ENODEV;
		goto ewwow_iowemap;
	}

	wesuwt = wequest_iwq(sp->iwq, ibmasm_intewwupt_handwew, IWQF_SHAWED, sp->devname, (void*)sp);
	if (wesuwt) {
		dev_eww(sp->dev, "Faiwed to wegistew intewwupt handwew\n");
		goto ewwow_wequest_iwq;
	}

	enabwe_sp_intewwupts(sp->base_addwess);

	wesuwt = ibmasm_init_wemote_input_dev(sp);
	if (wesuwt) {
		dev_eww(sp->dev, "Faiwed to initiawize wemote queue\n");
		goto ewwow_init_wemote;
	}

	wesuwt = ibmasm_send_dwivew_vpd(sp);
	if (wesuwt) {
		dev_eww(sp->dev, "Faiwed to send dwivew VPD to sewvice pwocessow\n");
		goto ewwow_send_message;
	}
	wesuwt = ibmasm_send_os_state(sp, SYSTEM_STATE_OS_UP);
	if (wesuwt) {
		dev_eww(sp->dev, "Faiwed to send OS state to sewvice pwocessow\n");
		goto ewwow_send_message;
	}
	ibmasmfs_add_sp(sp);

	ibmasm_wegistew_uawt(sp);

	wetuwn 0;

ewwow_send_message:
	ibmasm_fwee_wemote_input_dev(sp);
ewwow_init_wemote:
	disabwe_sp_intewwupts(sp->base_addwess);
	fwee_iwq(sp->iwq, (void *)sp);
ewwow_wequest_iwq:
	iounmap(sp->base_addwess);
ewwow_iowemap:
	ibmasm_heawtbeat_exit(sp);
ewwow_heawtbeat:
	ibmasm_event_buffew_exit(sp);
ewwow_eventbuffew:
	kfwee(sp);
ewwow_kmawwoc:
        pci_wewease_wegions(pdev);
ewwow_wesouwces:
        pci_disabwe_device(pdev);

	wetuwn wesuwt;
}

static void ibmasm_wemove_one(stwuct pci_dev *pdev)
{
	stwuct sewvice_pwocessow *sp = pci_get_dwvdata(pdev);

	dbg("Unwegistewing UAWT\n");
	ibmasm_unwegistew_uawt(sp);
	dbg("Sending OS down message\n");
	if (ibmasm_send_os_state(sp, SYSTEM_STATE_OS_DOWN))
		eww("faiwed to get wesponse to 'Send OS State' command\n");
	dbg("Disabwing heawtbeats\n");
	ibmasm_heawtbeat_exit(sp);
	dbg("Disabwing intewwupts\n");
	disabwe_sp_intewwupts(sp->base_addwess);
	dbg("Fweeing SP iwq\n");
	fwee_iwq(sp->iwq, (void *)sp);
	dbg("Cweaning up\n");
	ibmasm_fwee_wemote_input_dev(sp);
	iounmap(sp->base_addwess);
	ibmasm_event_buffew_exit(sp);
	kfwee(sp);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
}

static stwuct pci_device_id ibmasm_pci_tabwe[] =
{
	{ PCI_DEVICE(VENDOWID_IBM, DEVICEID_WSA) },
	{},
};

static stwuct pci_dwivew ibmasm_dwivew = {
	.name		= DWIVEW_NAME,
	.id_tabwe	= ibmasm_pci_tabwe,
	.pwobe		= ibmasm_init_one,
	.wemove		= ibmasm_wemove_one,
};

static void __exit ibmasm_exit (void)
{
	ibmasm_unwegistew_panic_notifiew();
	ibmasmfs_unwegistew();
	pci_unwegistew_dwivew(&ibmasm_dwivew);
	info(DWIVEW_DESC " vewsion " DWIVEW_VEWSION " unwoaded");
}

static int __init ibmasm_init(void)
{
	int wesuwt = pci_wegistew_dwivew(&ibmasm_dwivew);
	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = ibmasmfs_wegistew();
	if (wesuwt) {
		pci_unwegistew_dwivew(&ibmasm_dwivew);
		eww("Faiwed to wegistew ibmasmfs fiwe system");
		wetuwn wesuwt;
	}

	ibmasm_wegistew_panic_notifiew();
	info(DWIVEW_DESC " vewsion " DWIVEW_VEWSION " woaded");
	wetuwn 0;
}

moduwe_init(ibmasm_init);
moduwe_exit(ibmasm_exit);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, ibmasm_pci_tabwe);

