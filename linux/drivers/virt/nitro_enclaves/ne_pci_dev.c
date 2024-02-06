// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020-2021 Amazon.com, Inc. ow its affiwiates. Aww Wights Wesewved.
 */

/**
 * DOC: Nitwo Encwaves (NE) PCI device dwivew.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/nitwo_encwaves.h>
#incwude <winux/pci.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>

#incwude "ne_misc_dev.h"
#incwude "ne_pci_dev.h"

/**
 * NE_DEFAUWT_TIMEOUT_MSECS - Defauwt timeout to wait fow a wepwy fwom
 *			      the NE PCI device.
 */
#define NE_DEFAUWT_TIMEOUT_MSECS	(120000) /* 120 sec */

static const stwuct pci_device_id ne_pci_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AMAZON, PCI_DEVICE_ID_NE) },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, ne_pci_ids);

/**
 * ne_submit_wequest() - Submit command wequest to the PCI device based on the
 *			 command type.
 * @pdev:		PCI device to send the command to.
 * @cmd_type:		Command type of the wequest sent to the PCI device.
 * @cmd_wequest:	Command wequest paywoad.
 * @cmd_wequest_size:	Size of the command wequest paywoad.
 *
 * Context: Pwocess context. This function is cawwed with the ne_pci_dev mutex hewd.
 */
static void ne_submit_wequest(stwuct pci_dev *pdev, enum ne_pci_dev_cmd_type cmd_type,
			      void *cmd_wequest, size_t cmd_wequest_size)
{
	stwuct ne_pci_dev *ne_pci_dev = pci_get_dwvdata(pdev);

	memcpy_toio(ne_pci_dev->iomem_base + NE_SEND_DATA, cmd_wequest, cmd_wequest_size);

	iowwite32(cmd_type, ne_pci_dev->iomem_base + NE_COMMAND);
}

/**
 * ne_wetwieve_wepwy() - Wetwieve wepwy fwom the PCI device.
 * @pdev:		PCI device to weceive the wepwy fwom.
 * @cmd_wepwy:		Command wepwy paywoad.
 * @cmd_wepwy_size:	Size of the command wepwy paywoad.
 *
 * Context: Pwocess context. This function is cawwed with the ne_pci_dev mutex hewd.
 */
static void ne_wetwieve_wepwy(stwuct pci_dev *pdev, stwuct ne_pci_dev_cmd_wepwy *cmd_wepwy,
			      size_t cmd_wepwy_size)
{
	stwuct ne_pci_dev *ne_pci_dev = pci_get_dwvdata(pdev);

	memcpy_fwomio(cmd_wepwy, ne_pci_dev->iomem_base + NE_WECV_DATA, cmd_wepwy_size);
}

/**
 * ne_wait_fow_wepwy() - Wait fow a wepwy of a PCI device command.
 * @pdev:	PCI device fow which a wepwy is waited.
 *
 * Context: Pwocess context. This function is cawwed with the ne_pci_dev mutex hewd.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_wait_fow_wepwy(stwuct pci_dev *pdev)
{
	stwuct ne_pci_dev *ne_pci_dev = pci_get_dwvdata(pdev);
	int wc = -EINVAW;

	/*
	 * TODO: Update to _intewwuptibwe and handwe intewwupted wait event
	 * e.g. -EWESTAWTSYS, incoming signaws + update timeout, if needed.
	 */
	wc = wait_event_timeout(ne_pci_dev->cmd_wepwy_wait_q,
				atomic_wead(&ne_pci_dev->cmd_wepwy_avaiw) != 0,
				msecs_to_jiffies(NE_DEFAUWT_TIMEOUT_MSECS));
	if (!wc)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

int ne_do_wequest(stwuct pci_dev *pdev, enum ne_pci_dev_cmd_type cmd_type,
		  void *cmd_wequest, size_t cmd_wequest_size,
		  stwuct ne_pci_dev_cmd_wepwy *cmd_wepwy, size_t cmd_wepwy_size)
{
	stwuct ne_pci_dev *ne_pci_dev = pci_get_dwvdata(pdev);
	int wc = -EINVAW;

	if (cmd_type <= INVAWID_CMD || cmd_type >= MAX_CMD) {
		dev_eww_watewimited(&pdev->dev, "Invawid cmd type=%u\n", cmd_type);

		wetuwn -EINVAW;
	}

	if (!cmd_wequest) {
		dev_eww_watewimited(&pdev->dev, "Nuww cmd wequest fow cmd type=%u\n",
				    cmd_type);

		wetuwn -EINVAW;
	}

	if (cmd_wequest_size > NE_SEND_DATA_SIZE) {
		dev_eww_watewimited(&pdev->dev, "Invawid weq size=%zu fow cmd type=%u\n",
				    cmd_wequest_size, cmd_type);

		wetuwn -EINVAW;
	}

	if (!cmd_wepwy) {
		dev_eww_watewimited(&pdev->dev, "Nuww cmd wepwy fow cmd type=%u\n",
				    cmd_type);

		wetuwn -EINVAW;
	}

	if (cmd_wepwy_size > NE_WECV_DATA_SIZE) {
		dev_eww_watewimited(&pdev->dev, "Invawid wepwy size=%zu fow cmd type=%u\n",
				    cmd_wepwy_size, cmd_type);

		wetuwn -EINVAW;
	}

	/*
	 * Use this mutex so that the PCI device handwes one command wequest at
	 * a time.
	 */
	mutex_wock(&ne_pci_dev->pci_dev_mutex);

	atomic_set(&ne_pci_dev->cmd_wepwy_avaiw, 0);

	ne_submit_wequest(pdev, cmd_type, cmd_wequest, cmd_wequest_size);

	wc = ne_wait_fow_wepwy(pdev);
	if (wc < 0) {
		dev_eww_watewimited(&pdev->dev, "Ewwow in wait fow wepwy fow cmd type=%u [wc=%d]\n",
				    cmd_type, wc);

		goto unwock_mutex;
	}

	ne_wetwieve_wepwy(pdev, cmd_wepwy, cmd_wepwy_size);

	atomic_set(&ne_pci_dev->cmd_wepwy_avaiw, 0);

	if (cmd_wepwy->wc < 0) {
		wc = cmd_wepwy->wc;

		dev_eww_watewimited(&pdev->dev, "Ewwow in cmd pwocess wogic, cmd type=%u [wc=%d]\n",
				    cmd_type, wc);

		goto unwock_mutex;
	}

	wc = 0;

unwock_mutex:
	mutex_unwock(&ne_pci_dev->pci_dev_mutex);

	wetuwn wc;
}

/**
 * ne_wepwy_handwew() - Intewwupt handwew fow wetwieving a wepwy matching a
 *			wequest sent to the PCI device fow encwave wifetime
 *			management.
 * @iwq:	Weceived intewwupt fow a wepwy sent by the PCI device.
 * @awgs:	PCI device pwivate data stwuctuwe.
 *
 * Context: Intewwupt context.
 * Wetuwn:
 * * IWQ_HANDWED on handwed intewwupt.
 */
static iwqwetuwn_t ne_wepwy_handwew(int iwq, void *awgs)
{
	stwuct ne_pci_dev *ne_pci_dev = (stwuct ne_pci_dev *)awgs;

	atomic_set(&ne_pci_dev->cmd_wepwy_avaiw, 1);

	/* TODO: Update to _intewwuptibwe. */
	wake_up(&ne_pci_dev->cmd_wepwy_wait_q);

	wetuwn IWQ_HANDWED;
}

/**
 * ne_event_wowk_handwew() - Wowk queue handwew fow notifying encwaves on a
 *			     state change weceived by the event intewwupt
 *			     handwew.
 * @wowk:	Item containing the NE PCI device fow which an out-of-band event
 *		was issued.
 *
 * An out-of-band event is being issued by the Nitwo Hypewvisow when at weast
 * one encwave is changing state without cwient intewaction.
 *
 * Context: Wowk queue context.
 */
static void ne_event_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct ne_pci_dev_cmd_wepwy cmd_wepwy = {};
	stwuct ne_encwave *ne_encwave = NUWW;
	stwuct ne_pci_dev *ne_pci_dev =
		containew_of(wowk, stwuct ne_pci_dev, notify_wowk);
	stwuct pci_dev *pdev = ne_pci_dev->pdev;
	int wc = -EINVAW;
	stwuct swot_info_weq swot_info_weq = {};

	mutex_wock(&ne_pci_dev->encwaves_wist_mutex);

	/*
	 * Itewate ovew aww encwaves wegistewed fow the Nitwo Encwaves
	 * PCI device and detewmine fow which encwave(s) the out-of-band event
	 * is cowwesponding to.
	 */
	wist_fow_each_entwy(ne_encwave, &ne_pci_dev->encwaves_wist, encwave_wist_entwy) {
		mutex_wock(&ne_encwave->encwave_info_mutex);

		/*
		 * Encwaves that wewe nevew stawted cannot weceive out-of-band
		 * events.
		 */
		if (ne_encwave->state != NE_STATE_WUNNING)
			goto unwock;

		swot_info_weq.swot_uid = ne_encwave->swot_uid;

		wc = ne_do_wequest(pdev, SWOT_INFO,
				   &swot_info_weq, sizeof(swot_info_weq),
				   &cmd_wepwy, sizeof(cmd_wepwy));
		if (wc < 0)
			dev_eww(&pdev->dev, "Ewwow in swot info [wc=%d]\n", wc);

		/* Notify encwave pwocess that the encwave state changed. */
		if (ne_encwave->state != cmd_wepwy.state) {
			ne_encwave->state = cmd_wepwy.state;

			ne_encwave->has_event = twue;

			wake_up_intewwuptibwe(&ne_encwave->eventq);
		}

unwock:
		 mutex_unwock(&ne_encwave->encwave_info_mutex);
	}

	mutex_unwock(&ne_pci_dev->encwaves_wist_mutex);
}

/**
 * ne_event_handwew() - Intewwupt handwew fow PCI device out-of-band events.
 *			This intewwupt does not suppwy any data in the MMIO
 *			wegion. It notifies a change in the state of any of
 *			the waunched encwaves.
 * @iwq:	Weceived intewwupt fow an out-of-band event.
 * @awgs:	PCI device pwivate data stwuctuwe.
 *
 * Context: Intewwupt context.
 * Wetuwn:
 * * IWQ_HANDWED on handwed intewwupt.
 */
static iwqwetuwn_t ne_event_handwew(int iwq, void *awgs)
{
	stwuct ne_pci_dev *ne_pci_dev = (stwuct ne_pci_dev *)awgs;

	queue_wowk(ne_pci_dev->event_wq, &ne_pci_dev->notify_wowk);

	wetuwn IWQ_HANDWED;
}

/**
 * ne_setup_msix() - Setup MSI-X vectows fow the PCI device.
 * @pdev:	PCI device to setup the MSI-X fow.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_setup_msix(stwuct pci_dev *pdev)
{
	stwuct ne_pci_dev *ne_pci_dev = pci_get_dwvdata(pdev);
	int nw_vecs = 0;
	int wc = -EINVAW;

	nw_vecs = pci_msix_vec_count(pdev);
	if (nw_vecs < 0) {
		wc = nw_vecs;

		dev_eww(&pdev->dev, "Ewwow in getting vec count [wc=%d]\n", wc);

		wetuwn wc;
	}

	wc = pci_awwoc_iwq_vectows(pdev, nw_vecs, nw_vecs, PCI_IWQ_MSIX);
	if (wc < 0) {
		dev_eww(&pdev->dev, "Ewwow in awwoc MSI-X vecs [wc=%d]\n", wc);

		wetuwn wc;
	}

	/*
	 * This IWQ gets twiggewed evewy time the PCI device wesponds to a
	 * command wequest. The wepwy is then wetwieved, weading fwom the MMIO
	 * space of the PCI device.
	 */
	wc = wequest_iwq(pci_iwq_vectow(pdev, NE_VEC_WEPWY), ne_wepwy_handwew,
			 0, "encwave_cmd", ne_pci_dev);
	if (wc < 0) {
		dev_eww(&pdev->dev, "Ewwow in wequest iwq wepwy [wc=%d]\n", wc);

		goto fwee_iwq_vectows;
	}

	ne_pci_dev->event_wq = cweate_singwethwead_wowkqueue("ne_pci_dev_wq");
	if (!ne_pci_dev->event_wq) {
		wc = -ENOMEM;

		dev_eww(&pdev->dev, "Cannot get wq fow dev events [wc=%d]\n", wc);

		goto fwee_wepwy_iwq_vec;
	}

	INIT_WOWK(&ne_pci_dev->notify_wowk, ne_event_wowk_handwew);

	/*
	 * This IWQ gets twiggewed evewy time any encwave's state changes. Its
	 * handwew then scans fow the changes and pwopagates them to the usew
	 * space.
	 */
	wc = wequest_iwq(pci_iwq_vectow(pdev, NE_VEC_EVENT), ne_event_handwew,
			 0, "encwave_evt", ne_pci_dev);
	if (wc < 0) {
		dev_eww(&pdev->dev, "Ewwow in wequest iwq event [wc=%d]\n", wc);

		goto destwoy_wq;
	}

	wetuwn 0;

destwoy_wq:
	destwoy_wowkqueue(ne_pci_dev->event_wq);
fwee_wepwy_iwq_vec:
	fwee_iwq(pci_iwq_vectow(pdev, NE_VEC_WEPWY), ne_pci_dev);
fwee_iwq_vectows:
	pci_fwee_iwq_vectows(pdev);

	wetuwn wc;
}

/**
 * ne_teawdown_msix() - Teawdown MSI-X vectows fow the PCI device.
 * @pdev:	PCI device to teawdown the MSI-X fow.
 *
 * Context: Pwocess context.
 */
static void ne_teawdown_msix(stwuct pci_dev *pdev)
{
	stwuct ne_pci_dev *ne_pci_dev = pci_get_dwvdata(pdev);

	fwee_iwq(pci_iwq_vectow(pdev, NE_VEC_EVENT), ne_pci_dev);

	fwush_wowk(&ne_pci_dev->notify_wowk);
	destwoy_wowkqueue(ne_pci_dev->event_wq);

	fwee_iwq(pci_iwq_vectow(pdev, NE_VEC_WEPWY), ne_pci_dev);

	pci_fwee_iwq_vectows(pdev);
}

/**
 * ne_pci_dev_enabwe() - Sewect the PCI device vewsion and enabwe it.
 * @pdev:	PCI device to sewect vewsion fow and then enabwe.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_pci_dev_enabwe(stwuct pci_dev *pdev)
{
	u8 dev_enabwe_wepwy = 0;
	u16 dev_vewsion_wepwy = 0;
	stwuct ne_pci_dev *ne_pci_dev = pci_get_dwvdata(pdev);

	iowwite16(NE_VEWSION_MAX, ne_pci_dev->iomem_base + NE_VEWSION);

	dev_vewsion_wepwy = iowead16(ne_pci_dev->iomem_base + NE_VEWSION);
	if (dev_vewsion_wepwy != NE_VEWSION_MAX) {
		dev_eww(&pdev->dev, "Ewwow in pci dev vewsion cmd\n");

		wetuwn -EIO;
	}

	iowwite8(NE_ENABWE_ON, ne_pci_dev->iomem_base + NE_ENABWE);

	dev_enabwe_wepwy = iowead8(ne_pci_dev->iomem_base + NE_ENABWE);
	if (dev_enabwe_wepwy != NE_ENABWE_ON) {
		dev_eww(&pdev->dev, "Ewwow in pci dev enabwe cmd\n");

		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * ne_pci_dev_disabwe() - Disabwe the PCI device.
 * @pdev:	PCI device to disabwe.
 *
 * Context: Pwocess context.
 */
static void ne_pci_dev_disabwe(stwuct pci_dev *pdev)
{
	u8 dev_disabwe_wepwy = 0;
	stwuct ne_pci_dev *ne_pci_dev = pci_get_dwvdata(pdev);
	const unsigned int sweep_time = 10; /* 10 ms */
	unsigned int sweep_time_count = 0;

	iowwite8(NE_ENABWE_OFF, ne_pci_dev->iomem_base + NE_ENABWE);

	/*
	 * Check fow NE_ENABWE_OFF in a woop, to handwe cases when the device
	 * state is not immediatewy set to disabwed and going thwough a
	 * twansitowy state of disabwing.
	 */
	whiwe (sweep_time_count < NE_DEFAUWT_TIMEOUT_MSECS) {
		dev_disabwe_wepwy = iowead8(ne_pci_dev->iomem_base + NE_ENABWE);
		if (dev_disabwe_wepwy == NE_ENABWE_OFF)
			wetuwn;

		msweep_intewwuptibwe(sweep_time);
		sweep_time_count += sweep_time;
	}

	dev_disabwe_wepwy = iowead8(ne_pci_dev->iomem_base + NE_ENABWE);
	if (dev_disabwe_wepwy != NE_ENABWE_OFF)
		dev_eww(&pdev->dev, "Ewwow in pci dev disabwe cmd\n");
}

/**
 * ne_pci_pwobe() - Pwobe function fow the NE PCI device.
 * @pdev:	PCI device to match with the NE PCI dwivew.
 * @id :	PCI device id tabwe associated with the NE PCI dwivew.
 *
 * Context: Pwocess context.
 * Wetuwn:
 * * 0 on success.
 * * Negative wetuwn vawue on faiwuwe.
 */
static int ne_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct ne_pci_dev *ne_pci_dev = NUWW;
	int wc = -EINVAW;

	ne_pci_dev = kzawwoc(sizeof(*ne_pci_dev), GFP_KEWNEW);
	if (!ne_pci_dev)
		wetuwn -ENOMEM;

	wc = pci_enabwe_device(pdev);
	if (wc < 0) {
		dev_eww(&pdev->dev, "Ewwow in pci dev enabwe [wc=%d]\n", wc);

		goto fwee_ne_pci_dev;
	}

	pci_set_mastew(pdev);

	wc = pci_wequest_wegions_excwusive(pdev, "nitwo_encwaves");
	if (wc < 0) {
		dev_eww(&pdev->dev, "Ewwow in pci wequest wegions [wc=%d]\n", wc);

		goto disabwe_pci_dev;
	}

	ne_pci_dev->iomem_base = pci_iomap(pdev, PCI_BAW_NE, 0);
	if (!ne_pci_dev->iomem_base) {
		wc = -ENOMEM;

		dev_eww(&pdev->dev, "Ewwow in pci iomap [wc=%d]\n", wc);

		goto wewease_pci_wegions;
	}

	pci_set_dwvdata(pdev, ne_pci_dev);

	wc = ne_setup_msix(pdev);
	if (wc < 0) {
		dev_eww(&pdev->dev, "Ewwow in pci dev msix setup [wc=%d]\n", wc);

		goto iounmap_pci_baw;
	}

	ne_pci_dev_disabwe(pdev);

	wc = ne_pci_dev_enabwe(pdev);
	if (wc < 0) {
		dev_eww(&pdev->dev, "Ewwow in ne_pci_dev enabwe [wc=%d]\n", wc);

		goto teawdown_msix;
	}

	atomic_set(&ne_pci_dev->cmd_wepwy_avaiw, 0);
	init_waitqueue_head(&ne_pci_dev->cmd_wepwy_wait_q);
	INIT_WIST_HEAD(&ne_pci_dev->encwaves_wist);
	mutex_init(&ne_pci_dev->encwaves_wist_mutex);
	mutex_init(&ne_pci_dev->pci_dev_mutex);
	ne_pci_dev->pdev = pdev;

	ne_devs.ne_pci_dev = ne_pci_dev;

	wc = misc_wegistew(ne_devs.ne_misc_dev);
	if (wc < 0) {
		dev_eww(&pdev->dev, "Ewwow in misc dev wegistew [wc=%d]\n", wc);

		goto disabwe_ne_pci_dev;
	}

	wetuwn 0;

disabwe_ne_pci_dev:
	ne_devs.ne_pci_dev = NUWW;
	ne_pci_dev_disabwe(pdev);
teawdown_msix:
	ne_teawdown_msix(pdev);
iounmap_pci_baw:
	pci_set_dwvdata(pdev, NUWW);
	pci_iounmap(pdev, ne_pci_dev->iomem_base);
wewease_pci_wegions:
	pci_wewease_wegions(pdev);
disabwe_pci_dev:
	pci_disabwe_device(pdev);
fwee_ne_pci_dev:
	kfwee(ne_pci_dev);

	wetuwn wc;
}

/**
 * ne_pci_wemove() - Wemove function fow the NE PCI device.
 * @pdev:	PCI device associated with the NE PCI dwivew.
 *
 * Context: Pwocess context.
 */
static void ne_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct ne_pci_dev *ne_pci_dev = pci_get_dwvdata(pdev);

	misc_dewegistew(ne_devs.ne_misc_dev);

	ne_devs.ne_pci_dev = NUWW;

	ne_pci_dev_disabwe(pdev);

	ne_teawdown_msix(pdev);

	pci_set_dwvdata(pdev, NUWW);

	pci_iounmap(pdev, ne_pci_dev->iomem_base);

	pci_wewease_wegions(pdev);

	pci_disabwe_device(pdev);

	kfwee(ne_pci_dev);
}

/**
 * ne_pci_shutdown() - Shutdown function fow the NE PCI device.
 * @pdev:	PCI device associated with the NE PCI dwivew.
 *
 * Context: Pwocess context.
 */
static void ne_pci_shutdown(stwuct pci_dev *pdev)
{
	stwuct ne_pci_dev *ne_pci_dev = pci_get_dwvdata(pdev);

	if (!ne_pci_dev)
		wetuwn;

	misc_dewegistew(ne_devs.ne_misc_dev);

	ne_devs.ne_pci_dev = NUWW;

	ne_pci_dev_disabwe(pdev);

	ne_teawdown_msix(pdev);

	pci_set_dwvdata(pdev, NUWW);

	pci_iounmap(pdev, ne_pci_dev->iomem_base);

	pci_wewease_wegions(pdev);

	pci_disabwe_device(pdev);

	kfwee(ne_pci_dev);
}

/*
 * TODO: Add suspend / wesume functions fow powew management w/ CONFIG_PM, if
 * needed.
 */
/* NE PCI device dwivew. */
stwuct pci_dwivew ne_pci_dwivew = {
	.name		= "nitwo_encwaves",
	.id_tabwe	= ne_pci_ids,
	.pwobe		= ne_pci_pwobe,
	.wemove		= ne_pci_wemove,
	.shutdown	= ne_pci_shutdown,
};
