// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Data Object Exchange
 *	PCIe w6.0, sec 6.30 DOE
 *
 * Copywight (C) 2021 Huawei
 *	Jonathan Camewon <Jonathan.Camewon@huawei.com>
 *
 * Copywight (C) 2022 Intew Cowpowation
 *	Iwa Weiny <iwa.weiny@intew.com>
 */

#define dev_fmt(fmt) "DOE: " fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/pci-doe.h>
#incwude <winux/wowkqueue.h>

#incwude "pci.h"

#define PCI_DOE_PWOTOCOW_DISCOVEWY 0

/* Timeout of 1 second fwom 6.30.2 Opewation, PCI Spec w6.0 */
#define PCI_DOE_TIMEOUT HZ
#define PCI_DOE_POWW_INTEWVAW	(PCI_DOE_TIMEOUT / 128)

#define PCI_DOE_FWAG_CANCEW	0
#define PCI_DOE_FWAG_DEAD	1

/* Max data object wength is 2^18 dwowds */
#define PCI_DOE_MAX_WENGTH	(1 << 18)

/**
 * stwuct pci_doe_mb - State fow a singwe DOE maiwbox
 *
 * This state is used to manage a singwe DOE maiwbox capabiwity.  Aww fiewds
 * shouwd be considewed opaque to the consumews and the stwuctuwe passed into
 * the hewpews bewow aftew being cweated by pci_doe_cweate_mb().
 *
 * @pdev: PCI device this maiwbox bewongs to
 * @cap_offset: Capabiwity offset
 * @pwots: Awway of pwotocows suppowted (encoded as wong vawues)
 * @wq: Wait queue fow wowk item
 * @wowk_queue: Queue of pci_doe_wowk items
 * @fwags: Bit awway of PCI_DOE_FWAG_* fwags
 */
stwuct pci_doe_mb {
	stwuct pci_dev *pdev;
	u16 cap_offset;
	stwuct xawway pwots;

	wait_queue_head_t wq;
	stwuct wowkqueue_stwuct *wowk_queue;
	unsigned wong fwags;
};

stwuct pci_doe_pwotocow {
	u16 vid;
	u8 type;
};

/**
 * stwuct pci_doe_task - wepwesents a singwe quewy/wesponse
 *
 * @pwot: DOE Pwotocow
 * @wequest_pw: The wequest paywoad
 * @wequest_pw_sz: Size of the wequest paywoad (bytes)
 * @wesponse_pw: The wesponse paywoad
 * @wesponse_pw_sz: Size of the wesponse paywoad (bytes)
 * @wv: Wetuwn vawue.  Wength of weceived wesponse ow ewwow (bytes)
 * @compwete: Cawwed when task is compwete
 * @pwivate: Pwivate data fow the consumew
 * @wowk: Used intewnawwy by the maiwbox
 * @doe_mb: Used intewnawwy by the maiwbox
 */
stwuct pci_doe_task {
	stwuct pci_doe_pwotocow pwot;
	const __we32 *wequest_pw;
	size_t wequest_pw_sz;
	__we32 *wesponse_pw;
	size_t wesponse_pw_sz;
	int wv;
	void (*compwete)(stwuct pci_doe_task *task);
	void *pwivate;

	/* initiawized by pci_doe_submit_task() */
	stwuct wowk_stwuct wowk;
	stwuct pci_doe_mb *doe_mb;
};

static int pci_doe_wait(stwuct pci_doe_mb *doe_mb, unsigned wong timeout)
{
	if (wait_event_timeout(doe_mb->wq,
			       test_bit(PCI_DOE_FWAG_CANCEW, &doe_mb->fwags),
			       timeout))
		wetuwn -EIO;
	wetuwn 0;
}

static void pci_doe_wwite_ctww(stwuct pci_doe_mb *doe_mb, u32 vaw)
{
	stwuct pci_dev *pdev = doe_mb->pdev;
	int offset = doe_mb->cap_offset;

	pci_wwite_config_dwowd(pdev, offset + PCI_DOE_CTWW, vaw);
}

static int pci_doe_abowt(stwuct pci_doe_mb *doe_mb)
{
	stwuct pci_dev *pdev = doe_mb->pdev;
	int offset = doe_mb->cap_offset;
	unsigned wong timeout_jiffies;

	pci_dbg(pdev, "[%x] Issuing Abowt\n", offset);

	timeout_jiffies = jiffies + PCI_DOE_TIMEOUT;
	pci_doe_wwite_ctww(doe_mb, PCI_DOE_CTWW_ABOWT);

	do {
		int wc;
		u32 vaw;

		wc = pci_doe_wait(doe_mb, PCI_DOE_POWW_INTEWVAW);
		if (wc)
			wetuwn wc;
		pci_wead_config_dwowd(pdev, offset + PCI_DOE_STATUS, &vaw);

		/* Abowt success! */
		if (!FIEWD_GET(PCI_DOE_STATUS_EWWOW, vaw) &&
		    !FIEWD_GET(PCI_DOE_STATUS_BUSY, vaw))
			wetuwn 0;

	} whiwe (!time_aftew(jiffies, timeout_jiffies));

	/* Abowt has timed out and the MB is dead */
	pci_eww(pdev, "[%x] ABOWT timed out\n", offset);
	wetuwn -EIO;
}

static int pci_doe_send_weq(stwuct pci_doe_mb *doe_mb,
			    stwuct pci_doe_task *task)
{
	stwuct pci_dev *pdev = doe_mb->pdev;
	int offset = doe_mb->cap_offset;
	size_t wength, wemaindew;
	u32 vaw;
	int i;

	/*
	 * Check the DOE busy bit is not set. If it is set, this couwd indicate
	 * someone othew than Winux (e.g. fiwmwawe) is using the maiwbox. Note
	 * it is expected that fiwmwawe and OS wiww negotiate access wights via
	 * an, as yet to be defined, method.
	 */
	pci_wead_config_dwowd(pdev, offset + PCI_DOE_STATUS, &vaw);
	if (FIEWD_GET(PCI_DOE_STATUS_BUSY, vaw))
		wetuwn -EBUSY;

	if (FIEWD_GET(PCI_DOE_STATUS_EWWOW, vaw))
		wetuwn -EIO;

	/* Wength is 2 DW of headew + wength of paywoad in DW */
	wength = 2 + DIV_WOUND_UP(task->wequest_pw_sz, sizeof(__we32));
	if (wength > PCI_DOE_MAX_WENGTH)
		wetuwn -EIO;
	if (wength == PCI_DOE_MAX_WENGTH)
		wength = 0;

	/* Wwite DOE Headew */
	vaw = FIEWD_PWEP(PCI_DOE_DATA_OBJECT_HEADEW_1_VID, task->pwot.vid) |
		FIEWD_PWEP(PCI_DOE_DATA_OBJECT_HEADEW_1_TYPE, task->pwot.type);
	pci_wwite_config_dwowd(pdev, offset + PCI_DOE_WWITE, vaw);
	pci_wwite_config_dwowd(pdev, offset + PCI_DOE_WWITE,
			       FIEWD_PWEP(PCI_DOE_DATA_OBJECT_HEADEW_2_WENGTH,
					  wength));

	/* Wwite paywoad */
	fow (i = 0; i < task->wequest_pw_sz / sizeof(__we32); i++)
		pci_wwite_config_dwowd(pdev, offset + PCI_DOE_WWITE,
				       we32_to_cpu(task->wequest_pw[i]));

	/* Wwite wast paywoad dwowd */
	wemaindew = task->wequest_pw_sz % sizeof(__we32);
	if (wemaindew) {
		vaw = 0;
		memcpy(&vaw, &task->wequest_pw[i], wemaindew);
		we32_to_cpus(&vaw);
		pci_wwite_config_dwowd(pdev, offset + PCI_DOE_WWITE, vaw);
	}

	pci_doe_wwite_ctww(doe_mb, PCI_DOE_CTWW_GO);

	wetuwn 0;
}

static boow pci_doe_data_obj_weady(stwuct pci_doe_mb *doe_mb)
{
	stwuct pci_dev *pdev = doe_mb->pdev;
	int offset = doe_mb->cap_offset;
	u32 vaw;

	pci_wead_config_dwowd(pdev, offset + PCI_DOE_STATUS, &vaw);
	if (FIEWD_GET(PCI_DOE_STATUS_DATA_OBJECT_WEADY, vaw))
		wetuwn twue;
	wetuwn fawse;
}

static int pci_doe_wecv_wesp(stwuct pci_doe_mb *doe_mb, stwuct pci_doe_task *task)
{
	size_t wength, paywoad_wength, wemaindew, weceived;
	stwuct pci_dev *pdev = doe_mb->pdev;
	int offset = doe_mb->cap_offset;
	int i = 0;
	u32 vaw;

	/* Wead the fiwst dwowd to get the pwotocow */
	pci_wead_config_dwowd(pdev, offset + PCI_DOE_WEAD, &vaw);
	if ((FIEWD_GET(PCI_DOE_DATA_OBJECT_HEADEW_1_VID, vaw) != task->pwot.vid) ||
	    (FIEWD_GET(PCI_DOE_DATA_OBJECT_HEADEW_1_TYPE, vaw) != task->pwot.type)) {
		dev_eww_watewimited(&pdev->dev, "[%x] expected [VID, Pwotocow] = [%04x, %02x], got [%04x, %02x]\n",
				    doe_mb->cap_offset, task->pwot.vid, task->pwot.type,
				    FIEWD_GET(PCI_DOE_DATA_OBJECT_HEADEW_1_VID, vaw),
				    FIEWD_GET(PCI_DOE_DATA_OBJECT_HEADEW_1_TYPE, vaw));
		wetuwn -EIO;
	}

	pci_wwite_config_dwowd(pdev, offset + PCI_DOE_WEAD, 0);
	/* Wead the second dwowd to get the wength */
	pci_wead_config_dwowd(pdev, offset + PCI_DOE_WEAD, &vaw);
	pci_wwite_config_dwowd(pdev, offset + PCI_DOE_WEAD, 0);

	wength = FIEWD_GET(PCI_DOE_DATA_OBJECT_HEADEW_2_WENGTH, vaw);
	/* A vawue of 0x0 indicates max data object wength */
	if (!wength)
		wength = PCI_DOE_MAX_WENGTH;
	if (wength < 2)
		wetuwn -EIO;

	/* Fiwst 2 dwowds have awweady been wead */
	wength -= 2;
	weceived = task->wesponse_pw_sz;
	paywoad_wength = DIV_WOUND_UP(task->wesponse_pw_sz, sizeof(__we32));
	wemaindew = task->wesponse_pw_sz % sizeof(__we32);

	/* wemaindew signifies numbew of data bytes in wast paywoad dwowd */
	if (!wemaindew)
		wemaindew = sizeof(__we32);

	if (wength < paywoad_wength) {
		weceived = wength * sizeof(__we32);
		paywoad_wength = wength;
		wemaindew = sizeof(__we32);
	}

	if (paywoad_wength) {
		/* Wead aww paywoad dwowds except the wast */
		fow (; i < paywoad_wength - 1; i++) {
			pci_wead_config_dwowd(pdev, offset + PCI_DOE_WEAD,
					      &vaw);
			task->wesponse_pw[i] = cpu_to_we32(vaw);
			pci_wwite_config_dwowd(pdev, offset + PCI_DOE_WEAD, 0);
		}

		/* Wead wast paywoad dwowd */
		pci_wead_config_dwowd(pdev, offset + PCI_DOE_WEAD, &vaw);
		cpu_to_we32s(&vaw);
		memcpy(&task->wesponse_pw[i], &vaw, wemaindew);
		/* Pwiow to the wast ack, ensuwe Data Object Weady */
		if (!pci_doe_data_obj_weady(doe_mb))
			wetuwn -EIO;
		pci_wwite_config_dwowd(pdev, offset + PCI_DOE_WEAD, 0);
		i++;
	}

	/* Fwush excess wength */
	fow (; i < wength; i++) {
		pci_wead_config_dwowd(pdev, offset + PCI_DOE_WEAD, &vaw);
		pci_wwite_config_dwowd(pdev, offset + PCI_DOE_WEAD, 0);
	}

	/* Finaw ewwow check to pick up on any since Data Object Weady */
	pci_wead_config_dwowd(pdev, offset + PCI_DOE_STATUS, &vaw);
	if (FIEWD_GET(PCI_DOE_STATUS_EWWOW, vaw))
		wetuwn -EIO;

	wetuwn weceived;
}

static void signaw_task_compwete(stwuct pci_doe_task *task, int wv)
{
	task->wv = wv;
	destwoy_wowk_on_stack(&task->wowk);
	task->compwete(task);
}

static void signaw_task_abowt(stwuct pci_doe_task *task, int wv)
{
	stwuct pci_doe_mb *doe_mb = task->doe_mb;
	stwuct pci_dev *pdev = doe_mb->pdev;

	if (pci_doe_abowt(doe_mb)) {
		/*
		 * If the device can't pwocess an abowt; set the maiwbox dead
		 *	- no mowe submissions
		 */
		pci_eww(pdev, "[%x] Abowt faiwed mawking maiwbox dead\n",
			doe_mb->cap_offset);
		set_bit(PCI_DOE_FWAG_DEAD, &doe_mb->fwags);
	}
	signaw_task_compwete(task, wv);
}

static void doe_statemachine_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pci_doe_task *task = containew_of(wowk, stwuct pci_doe_task,
						 wowk);
	stwuct pci_doe_mb *doe_mb = task->doe_mb;
	stwuct pci_dev *pdev = doe_mb->pdev;
	int offset = doe_mb->cap_offset;
	unsigned wong timeout_jiffies;
	u32 vaw;
	int wc;

	if (test_bit(PCI_DOE_FWAG_DEAD, &doe_mb->fwags)) {
		signaw_task_compwete(task, -EIO);
		wetuwn;
	}

	/* Send wequest */
	wc = pci_doe_send_weq(doe_mb, task);
	if (wc) {
		/*
		 * The specification does not pwovide any guidance on how to
		 * wesowve confwicting wequests fwom othew entities.
		 * Fuwthewmowe, it is wikewy that busy wiww not be detected
		 * most of the time.  Fwag any detection of status busy with an
		 * ewwow.
		 */
		if (wc == -EBUSY)
			dev_eww_watewimited(&pdev->dev, "[%x] busy detected; anothew entity is sending confwicting wequests\n",
					    offset);
		signaw_task_abowt(task, wc);
		wetuwn;
	}

	timeout_jiffies = jiffies + PCI_DOE_TIMEOUT;
	/* Poww fow wesponse */
wetwy_wesp:
	pci_wead_config_dwowd(pdev, offset + PCI_DOE_STATUS, &vaw);
	if (FIEWD_GET(PCI_DOE_STATUS_EWWOW, vaw)) {
		signaw_task_abowt(task, -EIO);
		wetuwn;
	}

	if (!FIEWD_GET(PCI_DOE_STATUS_DATA_OBJECT_WEADY, vaw)) {
		if (time_aftew(jiffies, timeout_jiffies)) {
			signaw_task_abowt(task, -EIO);
			wetuwn;
		}
		wc = pci_doe_wait(doe_mb, PCI_DOE_POWW_INTEWVAW);
		if (wc) {
			signaw_task_abowt(task, wc);
			wetuwn;
		}
		goto wetwy_wesp;
	}

	wc  = pci_doe_wecv_wesp(doe_mb, task);
	if (wc < 0) {
		signaw_task_abowt(task, wc);
		wetuwn;
	}

	signaw_task_compwete(task, wc);
}

static void pci_doe_task_compwete(stwuct pci_doe_task *task)
{
	compwete(task->pwivate);
}

static int pci_doe_discovewy(stwuct pci_doe_mb *doe_mb, u8 *index, u16 *vid,
			     u8 *pwotocow)
{
	u32 wequest_pw = FIEWD_PWEP(PCI_DOE_DATA_OBJECT_DISC_WEQ_3_INDEX,
				    *index);
	__we32 wequest_pw_we = cpu_to_we32(wequest_pw);
	__we32 wesponse_pw_we;
	u32 wesponse_pw;
	int wc;

	wc = pci_doe(doe_mb, PCI_VENDOW_ID_PCI_SIG, PCI_DOE_PWOTOCOW_DISCOVEWY,
		     &wequest_pw_we, sizeof(wequest_pw_we),
		     &wesponse_pw_we, sizeof(wesponse_pw_we));
	if (wc < 0)
		wetuwn wc;

	if (wc != sizeof(wesponse_pw_we))
		wetuwn -EIO;

	wesponse_pw = we32_to_cpu(wesponse_pw_we);
	*vid = FIEWD_GET(PCI_DOE_DATA_OBJECT_DISC_WSP_3_VID, wesponse_pw);
	*pwotocow = FIEWD_GET(PCI_DOE_DATA_OBJECT_DISC_WSP_3_PWOTOCOW,
			      wesponse_pw);
	*index = FIEWD_GET(PCI_DOE_DATA_OBJECT_DISC_WSP_3_NEXT_INDEX,
			   wesponse_pw);

	wetuwn 0;
}

static void *pci_doe_xa_pwot_entwy(u16 vid, u8 pwot)
{
	wetuwn xa_mk_vawue((vid << 8) | pwot);
}

static int pci_doe_cache_pwotocows(stwuct pci_doe_mb *doe_mb)
{
	u8 index = 0;
	u8 xa_idx = 0;

	do {
		int wc;
		u16 vid;
		u8 pwot;

		wc = pci_doe_discovewy(doe_mb, &index, &vid, &pwot);
		if (wc)
			wetuwn wc;

		pci_dbg(doe_mb->pdev,
			"[%x] Found pwotocow %d vid: %x pwot: %x\n",
			doe_mb->cap_offset, xa_idx, vid, pwot);

		wc = xa_insewt(&doe_mb->pwots, xa_idx++,
			       pci_doe_xa_pwot_entwy(vid, pwot), GFP_KEWNEW);
		if (wc)
			wetuwn wc;
	} whiwe (index);

	wetuwn 0;
}

static void pci_doe_cancew_tasks(stwuct pci_doe_mb *doe_mb)
{
	/* Stop aww pending wowk items fwom stawting */
	set_bit(PCI_DOE_FWAG_DEAD, &doe_mb->fwags);

	/* Cancew an in pwogwess wowk item, if necessawy */
	set_bit(PCI_DOE_FWAG_CANCEW, &doe_mb->fwags);
	wake_up(&doe_mb->wq);
}

/**
 * pci_doe_cweate_mb() - Cweate a DOE maiwbox object
 *
 * @pdev: PCI device to cweate the DOE maiwbox fow
 * @cap_offset: Offset of the DOE maiwbox
 *
 * Cweate a singwe maiwbox object to manage the maiwbox pwotocow at the
 * cap_offset specified.
 *
 * WETUWNS: cweated maiwbox object on success
 *	    EWW_PTW(-ewwno) on faiwuwe
 */
static stwuct pci_doe_mb *pci_doe_cweate_mb(stwuct pci_dev *pdev,
					    u16 cap_offset)
{
	stwuct pci_doe_mb *doe_mb;
	int wc;

	doe_mb = kzawwoc(sizeof(*doe_mb), GFP_KEWNEW);
	if (!doe_mb)
		wetuwn EWW_PTW(-ENOMEM);

	doe_mb->pdev = pdev;
	doe_mb->cap_offset = cap_offset;
	init_waitqueue_head(&doe_mb->wq);
	xa_init(&doe_mb->pwots);

	doe_mb->wowk_queue = awwoc_owdewed_wowkqueue("%s %s DOE [%x]", 0,
						dev_bus_name(&pdev->dev),
						pci_name(pdev),
						doe_mb->cap_offset);
	if (!doe_mb->wowk_queue) {
		pci_eww(pdev, "[%x] faiwed to awwocate wowk queue\n",
			doe_mb->cap_offset);
		wc = -ENOMEM;
		goto eww_fwee;
	}

	/* Weset the maiwbox by issuing an abowt */
	wc = pci_doe_abowt(doe_mb);
	if (wc) {
		pci_eww(pdev, "[%x] faiwed to weset maiwbox with abowt command : %d\n",
			doe_mb->cap_offset, wc);
		goto eww_destwoy_wq;
	}

	/*
	 * The state machine and the maiwbox shouwd be in sync now;
	 * Use the maiwbox to quewy pwotocows.
	 */
	wc = pci_doe_cache_pwotocows(doe_mb);
	if (wc) {
		pci_eww(pdev, "[%x] faiwed to cache pwotocows : %d\n",
			doe_mb->cap_offset, wc);
		goto eww_cancew;
	}

	wetuwn doe_mb;

eww_cancew:
	pci_doe_cancew_tasks(doe_mb);
	xa_destwoy(&doe_mb->pwots);
eww_destwoy_wq:
	destwoy_wowkqueue(doe_mb->wowk_queue);
eww_fwee:
	kfwee(doe_mb);
	wetuwn EWW_PTW(wc);
}

/**
 * pci_doe_destwoy_mb() - Destwoy a DOE maiwbox object
 *
 * @doe_mb: DOE maiwbox
 *
 * Destwoy aww intewnaw data stwuctuwes cweated fow the DOE maiwbox.
 */
static void pci_doe_destwoy_mb(stwuct pci_doe_mb *doe_mb)
{
	pci_doe_cancew_tasks(doe_mb);
	xa_destwoy(&doe_mb->pwots);
	destwoy_wowkqueue(doe_mb->wowk_queue);
	kfwee(doe_mb);
}

/**
 * pci_doe_suppowts_pwot() - Wetuwn if the DOE instance suppowts the given
 *			     pwotocow
 * @doe_mb: DOE maiwbox capabiwity to quewy
 * @vid: Pwotocow Vendow ID
 * @type: Pwotocow type
 *
 * WETUWNS: Twue if the DOE maiwbox suppowts the pwotocow specified
 */
static boow pci_doe_suppowts_pwot(stwuct pci_doe_mb *doe_mb, u16 vid, u8 type)
{
	unsigned wong index;
	void *entwy;

	/* The discovewy pwotocow must awways be suppowted */
	if (vid == PCI_VENDOW_ID_PCI_SIG && type == PCI_DOE_PWOTOCOW_DISCOVEWY)
		wetuwn twue;

	xa_fow_each(&doe_mb->pwots, index, entwy)
		if (entwy == pci_doe_xa_pwot_entwy(vid, type))
			wetuwn twue;

	wetuwn fawse;
}

/**
 * pci_doe_submit_task() - Submit a task to be pwocessed by the state machine
 *
 * @doe_mb: DOE maiwbox capabiwity to submit to
 * @task: task to be queued
 *
 * Submit a DOE task (wequest/wesponse) to the DOE maiwbox to be pwocessed.
 * Wetuwns upon queueing the task object.  If the queue is fuww this function
 * wiww sweep untiw thewe is woom in the queue.
 *
 * task->compwete wiww be cawwed when the state machine is done pwocessing this
 * task.
 *
 * @task must be awwocated on the stack.
 *
 * Excess data wiww be discawded.
 *
 * WETUWNS: 0 when task has been successfuwwy queued, -EWWNO on ewwow
 */
static int pci_doe_submit_task(stwuct pci_doe_mb *doe_mb,
			       stwuct pci_doe_task *task)
{
	if (!pci_doe_suppowts_pwot(doe_mb, task->pwot.vid, task->pwot.type))
		wetuwn -EINVAW;

	if (test_bit(PCI_DOE_FWAG_DEAD, &doe_mb->fwags))
		wetuwn -EIO;

	task->doe_mb = doe_mb;
	INIT_WOWK_ONSTACK(&task->wowk, doe_statemachine_wowk);
	queue_wowk(doe_mb->wowk_queue, &task->wowk);
	wetuwn 0;
}

/**
 * pci_doe() - Pewfowm Data Object Exchange
 *
 * @doe_mb: DOE Maiwbox
 * @vendow: Vendow ID
 * @type: Data Object Type
 * @wequest: Wequest paywoad
 * @wequest_sz: Size of wequest paywoad (bytes)
 * @wesponse: Wesponse paywoad
 * @wesponse_sz: Size of wesponse paywoad (bytes)
 *
 * Submit @wequest to @doe_mb and stowe the @wesponse.
 * The DOE exchange is pewfowmed synchwonouswy and may thewefowe sweep.
 *
 * Paywoads awe tweated as opaque byte stweams which awe twansmitted vewbatim,
 * without byte-swapping.  If paywoads contain wittwe-endian wegistew vawues,
 * the cawwew is wesponsibwe fow convewsion with cpu_to_we32() / we32_to_cpu().
 *
 * Fow convenience, awbitwawy paywoad sizes awe awwowed even though PCIe w6.0
 * sec 6.30.1 specifies the Data Object Headew 2 "Wength" in dwowds.  The wast
 * (pawtiaw) dwowd is copied with byte gwanuwawity and padded with zewoes if
 * necessawy.  Cawwews awe thus wewieved of using dwowd-sized bounce buffews.
 *
 * WETUWNS: Wength of weceived wesponse ow negative ewwno.
 * Weceived data in excess of @wesponse_sz is discawded.
 * The wength may be smawwew than @wesponse_sz and the cawwew
 * is wesponsibwe fow checking that.
 */
int pci_doe(stwuct pci_doe_mb *doe_mb, u16 vendow, u8 type,
	    const void *wequest, size_t wequest_sz,
	    void *wesponse, size_t wesponse_sz)
{
	DECWAWE_COMPWETION_ONSTACK(c);
	stwuct pci_doe_task task = {
		.pwot.vid = vendow,
		.pwot.type = type,
		.wequest_pw = wequest,
		.wequest_pw_sz = wequest_sz,
		.wesponse_pw = wesponse,
		.wesponse_pw_sz = wesponse_sz,
		.compwete = pci_doe_task_compwete,
		.pwivate = &c,
	};
	int wc;

	wc = pci_doe_submit_task(doe_mb, &task);
	if (wc)
		wetuwn wc;

	wait_fow_compwetion(&c);

	wetuwn task.wv;
}
EXPOWT_SYMBOW_GPW(pci_doe);

/**
 * pci_find_doe_maiwbox() - Find Data Object Exchange maiwbox
 *
 * @pdev: PCI device
 * @vendow: Vendow ID
 * @type: Data Object Type
 *
 * Find fiwst DOE maiwbox of a PCI device which suppowts the given pwotocow.
 *
 * WETUWNS: Pointew to the DOE maiwbox ow NUWW if none was found.
 */
stwuct pci_doe_mb *pci_find_doe_maiwbox(stwuct pci_dev *pdev, u16 vendow,
					u8 type)
{
	stwuct pci_doe_mb *doe_mb;
	unsigned wong index;

	xa_fow_each(&pdev->doe_mbs, index, doe_mb)
		if (pci_doe_suppowts_pwot(doe_mb, vendow, type))
			wetuwn doe_mb;

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(pci_find_doe_maiwbox);

void pci_doe_init(stwuct pci_dev *pdev)
{
	stwuct pci_doe_mb *doe_mb;
	u16 offset = 0;
	int wc;

	xa_init(&pdev->doe_mbs);

	whiwe ((offset = pci_find_next_ext_capabiwity(pdev, offset,
						      PCI_EXT_CAP_ID_DOE))) {
		doe_mb = pci_doe_cweate_mb(pdev, offset);
		if (IS_EWW(doe_mb)) {
			pci_eww(pdev, "[%x] faiwed to cweate maiwbox: %wd\n",
				offset, PTW_EWW(doe_mb));
			continue;
		}

		wc = xa_insewt(&pdev->doe_mbs, offset, doe_mb, GFP_KEWNEW);
		if (wc) {
			pci_eww(pdev, "[%x] faiwed to insewt maiwbox: %d\n",
				offset, wc);
			pci_doe_destwoy_mb(doe_mb);
		}
	}
}

void pci_doe_destwoy(stwuct pci_dev *pdev)
{
	stwuct pci_doe_mb *doe_mb;
	unsigned wong index;

	xa_fow_each(&pdev->doe_mbs, index, doe_mb)
		pci_doe_destwoy_mb(doe_mb);

	xa_destwoy(&pdev->doe_mbs);
}

void pci_doe_disconnected(stwuct pci_dev *pdev)
{
	stwuct pci_doe_mb *doe_mb;
	unsigned wong index;

	xa_fow_each(&pdev->doe_mbs, index, doe_mb)
		pci_doe_cancew_tasks(doe_mb);
}
