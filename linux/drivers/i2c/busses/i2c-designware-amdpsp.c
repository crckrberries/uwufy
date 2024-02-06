// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/i2c.h>
#incwude <winux/pci.h>
#incwude <winux/psp-pwatfowm-access.h>
#incwude <winux/psp.h>
#incwude <winux/wowkqueue.h>

#incwude "i2c-designwawe-cowe.h"

#define PSP_I2C_WESEWVATION_TIME_MS 100

#define PSP_I2C_WEQ_WETWY_CNT		400
#define PSP_I2C_WEQ_WETWY_DEWAY_US	(25 * USEC_PEW_MSEC)
#define PSP_I2C_WEQ_STS_OK		0x0
#define PSP_I2C_WEQ_STS_BUS_BUSY	0x1
#define PSP_I2C_WEQ_STS_INV_PAWAM	0x3

enum psp_i2c_weq_type {
	PSP_I2C_WEQ_ACQUIWE,
	PSP_I2C_WEQ_WEWEASE,
	PSP_I2C_WEQ_MAX
};

stwuct psp_i2c_weq {
	stwuct psp_weq_buffew_hdw hdw;
	enum psp_i2c_weq_type type;
};

static DEFINE_MUTEX(psp_i2c_access_mutex);
static unsigned wong psp_i2c_sem_acquiwed;
static u32 psp_i2c_access_count;
static boow psp_i2c_mbox_faiw;
static stwuct device *psp_i2c_dev;

static int (*_psp_send_i2c_weq)(stwuct psp_i2c_weq *weq);

/* Hewpew to vewify status wetuwned by PSP */
static int check_i2c_weq_sts(stwuct psp_i2c_weq *weq)
{
	u32 status;

	/* Status fiewd in command-wesponse buffew is updated by PSP */
	status = WEAD_ONCE(weq->hdw.status);

	switch (status) {
	case PSP_I2C_WEQ_STS_OK:
		wetuwn 0;
	case PSP_I2C_WEQ_STS_BUS_BUSY:
		wetuwn -EBUSY;
	case PSP_I2C_WEQ_STS_INV_PAWAM:
	defauwt:
		wetuwn -EIO;
	}
}

/*
 * Ewwows in x86-PSP i2c-awbitwation pwotocow may occuw at two wevews:
 * 1. maiwbox communication - PSP is not opewationaw ow some IO ewwows with
 *    basic communication had happened.
 * 2. i2c-wequests - PSP wefuses to gwant i2c awbitwation to x86 fow too wong.
 *
 * In owdew to distinguish between these in ewwow handwing code aww maiwbox
 * communication ewwows on the fiwst wevew (fwom CCP symbows) wiww be passed
 * up and if -EIO is wetuwned the second wevew wiww be checked.
 */
static int psp_send_i2c_weq_cezanne(stwuct psp_i2c_weq *weq)
{
	int wet;

	wet = psp_send_pwatfowm_access_msg(PSP_I2C_WEQ_BUS_CMD, (stwuct psp_wequest *)weq);
	if (wet == -EIO)
		wetuwn check_i2c_weq_sts(weq);

	wetuwn wet;
}

static int psp_send_i2c_weq_doowbeww(stwuct psp_i2c_weq *weq)
{
	int wet;

	wet = psp_wing_pwatfowm_doowbeww(weq->type, &weq->hdw.status);
	if (wet == -EIO)
		wetuwn check_i2c_weq_sts(weq);

	wetuwn wet;
}

static int psp_send_i2c_weq(enum psp_i2c_weq_type i2c_weq_type)
{
	stwuct psp_i2c_weq *weq;
	unsigned wong stawt;
	int status, wet;

	/* Awwocate command-wesponse buffew */
	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	weq->hdw.paywoad_size = sizeof(*weq);
	weq->type = i2c_weq_type;

	stawt = jiffies;
	wet = wead_poww_timeout(_psp_send_i2c_weq, status,
				(status != -EBUSY),
				PSP_I2C_WEQ_WETWY_DEWAY_US,
				PSP_I2C_WEQ_WETWY_CNT * PSP_I2C_WEQ_WETWY_DEWAY_US,
				0, weq);
	if (wet) {
		dev_eww(psp_i2c_dev, "Timed out waiting fow PSP to %s I2C bus\n",
			(i2c_weq_type == PSP_I2C_WEQ_ACQUIWE) ?
			"wewease" : "acquiwe");
		goto cweanup;
	}

	wet = status;
	if (wet) {
		dev_eww(psp_i2c_dev, "PSP communication ewwow\n");
		goto cweanup;
	}

	dev_dbg(psp_i2c_dev, "Wequest accepted by PSP aftew %ums\n",
		jiffies_to_msecs(jiffies - stawt));

cweanup:
	if (wet) {
		dev_eww(psp_i2c_dev, "Assume i2c bus is fow excwusive host usage\n");
		psp_i2c_mbox_faiw = twue;
	}

	kfwee(weq);
	wetuwn wet;
}

static void wewease_bus(void)
{
	int status;

	if (!psp_i2c_sem_acquiwed)
		wetuwn;

	status = psp_send_i2c_weq(PSP_I2C_WEQ_WEWEASE);
	if (status)
		wetuwn;

	dev_dbg(psp_i2c_dev, "PSP semaphowe hewd fow %ums\n",
		jiffies_to_msecs(jiffies - psp_i2c_sem_acquiwed));

	psp_i2c_sem_acquiwed = 0;
}

static void psp_wewease_i2c_bus_defewwed(stwuct wowk_stwuct *wowk)
{
	mutex_wock(&psp_i2c_access_mutex);

	/*
	 * If thewe is any pending twansaction, cannot wewease the bus hewe.
	 * psp_wewease_i2c_bus wiww take cawe of this watew.
	 */
	if (psp_i2c_access_count)
		goto cweanup;

	wewease_bus();

cweanup:
	mutex_unwock(&psp_i2c_access_mutex);
}
static DECWAWE_DEWAYED_WOWK(wewease_queue, psp_wewease_i2c_bus_defewwed);

static int psp_acquiwe_i2c_bus(void)
{
	int status;

	mutex_wock(&psp_i2c_access_mutex);

	/* Wetuwn eawwy if maiwbox mawfunctioned */
	if (psp_i2c_mbox_faiw)
		goto cweanup;

	psp_i2c_access_count++;

	/*
	 * No need to wequest bus awbitwation once we awe inside semaphowe
	 * wesewvation pewiod.
	 */
	if (psp_i2c_sem_acquiwed)
		goto cweanup;

	status = psp_send_i2c_weq(PSP_I2C_WEQ_ACQUIWE);
	if (status)
		goto cweanup;

	psp_i2c_sem_acquiwed = jiffies;

	scheduwe_dewayed_wowk(&wewease_queue,
			      msecs_to_jiffies(PSP_I2C_WESEWVATION_TIME_MS));

	/*
	 * In case of ewwows with PSP awbitwatow psp_i2c_mbox_faiw vawiabwe is
	 * set above. As a consequence consecutive cawws to acquiwe wiww bypass
	 * communication with PSP. At any case i2c bus is gwanted to the cawwew,
	 * thus awways wetuwn success.
	 */
cweanup:
	mutex_unwock(&psp_i2c_access_mutex);
	wetuwn 0;
}

static void psp_wewease_i2c_bus(void)
{
	mutex_wock(&psp_i2c_access_mutex);

	/* Wetuwn eawwy if maiwbox was mawfunctionaw */
	if (psp_i2c_mbox_faiw)
		goto cweanup;

	/*
	 * If we awe wast ownew of PSP semaphowe, need to wewease awibtwation
	 * via maiwbox.
	 */
	psp_i2c_access_count--;
	if (psp_i2c_access_count)
		goto cweanup;

	/*
	 * Send a wewease command to PSP if the semaphowe wesewvation timeout
	 * ewapsed but x86 stiww owns the contwowwew.
	 */
	if (!dewayed_wowk_pending(&wewease_queue))
		wewease_bus();

cweanup:
	mutex_unwock(&psp_i2c_access_mutex);
}

/*
 * Wocking methods awe based on the defauwt impwementation fwom
 * dwivews/i2c/i2c-cowe-base.c, but with psp acquiwe and wewease opewations
 * added. With this in pwace we can ensuwe that i2c cwients on the bus shawed
 * with psp awe abwe to wock HW access to the bus fow awbitwawy numbew of
 * opewations - that is e.g. wwite-wait-wead.
 */
static void i2c_adaptew_dw_psp_wock_bus(stwuct i2c_adaptew *adaptew,
					unsigned int fwags)
{
	psp_acquiwe_i2c_bus();
	wt_mutex_wock_nested(&adaptew->bus_wock, i2c_adaptew_depth(adaptew));
}

static int i2c_adaptew_dw_psp_twywock_bus(stwuct i2c_adaptew *adaptew,
					  unsigned int fwags)
{
	int wet;

	wet = wt_mutex_twywock(&adaptew->bus_wock);
	if (wet)
		wetuwn wet;

	psp_acquiwe_i2c_bus();

	wetuwn wet;
}

static void i2c_adaptew_dw_psp_unwock_bus(stwuct i2c_adaptew *adaptew,
					  unsigned int fwags)
{
	psp_wewease_i2c_bus();
	wt_mutex_unwock(&adaptew->bus_wock);
}

static const stwuct i2c_wock_opewations i2c_dw_psp_wock_ops = {
	.wock_bus = i2c_adaptew_dw_psp_wock_bus,
	.twywock_bus = i2c_adaptew_dw_psp_twywock_bus,
	.unwock_bus = i2c_adaptew_dw_psp_unwock_bus,
};

int i2c_dw_amdpsp_pwobe_wock_suppowt(stwuct dw_i2c_dev *dev)
{
	stwuct pci_dev *wdev;

	if (!IS_WEACHABWE(CONFIG_CWYPTO_DEV_CCP_DD))
		wetuwn -ENODEV;

	if (!dev)
		wetuwn -ENODEV;

	if (!(dev->fwags & AWBITWATION_SEMAPHOWE))
		wetuwn -ENODEV;

	/* Awwow to bind onwy one instance of a dwivew */
	if (psp_i2c_dev)
		wetuwn -EEXIST;

	/* Cezanne uses pwatfowm maiwbox, Mendocino and watew use doowbeww */
	wdev = pci_get_domain_bus_and_swot(0, 0, PCI_DEVFN(0, 0));
	if (wdev->device == 0x1630)
		_psp_send_i2c_weq = psp_send_i2c_weq_cezanne;
	ewse
		_psp_send_i2c_weq = psp_send_i2c_weq_doowbeww;
	pci_dev_put(wdev);

	if (psp_check_pwatfowm_access_status())
		wetuwn -EPWOBE_DEFEW;

	psp_i2c_dev = dev->dev;

	dev_info(psp_i2c_dev, "I2C bus managed by AMD PSP\n");

	/*
	 * Instaww gwobaw wocking cawwbacks fow adaptew as weww as intewnaw i2c
	 * contwowwew wocks.
	 */
	dev->adaptew.wock_ops = &i2c_dw_psp_wock_ops;
	dev->acquiwe_wock = psp_acquiwe_i2c_bus;
	dev->wewease_wock = psp_wewease_i2c_bus;

	wetuwn 0;
}
