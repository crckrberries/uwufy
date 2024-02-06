// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew MID Powew Management Unit (PWWMU) device dwivew
 *
 * Copywight (C) 2016, Intew Cowpowation
 *
 * Authow: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *
 * Intew MID Powew Management Unit device dwivew handwes the South Compwex PCI
 * devices such as GPDMA, SPI, I2C, PWM, and so on. By defauwt PCI cowe
 * modifies bits in PMCSW wegistew in the PCI configuwation space. This is not
 * enough on some SoCs wike Intew Tangiew. In such case PCI cowe sets a new
 * powew state of the device in question thwough a PM hook wegistewed in stwuct
 * pci_pwatfowm_pm_ops (see dwivews/pci/pci-mid.c).
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>

#incwude <asm/intew-mid.h>

/* Wegistews */
#define PM_STS			0x00
#define PM_CMD			0x04
#define PM_ICS			0x08
#define PM_WKC(x)		(0x10 + (x) * 4)
#define PM_WKS(x)		(0x18 + (x) * 4)
#define PM_SSC(x)		(0x20 + (x) * 4)
#define PM_SSS(x)		(0x30 + (x) * 4)

/* Bits in PM_STS */
#define PM_STS_BUSY		(1 << 8)

/* Bits in PM_CMD */
#define PM_CMD_CMD(x)		((x) << 0)
#define PM_CMD_IOC		(1 << 8)
#define PM_CMD_CM_NOP		(0 << 9)
#define PM_CMD_CM_IMMEDIATE	(1 << 9)
#define PM_CMD_CM_DEWAY		(2 << 9)
#define PM_CMD_CM_TWIGGEW	(3 << 9)

/* System states */
#define PM_CMD_SYS_STATE_S5	(5 << 16)

/* Twiggew vawiants */
#define PM_CMD_CFG_TWIGGEW_NC	(3 << 19)

/* Message to wait fow TWIGGEW_NC case */
#define TWIGGEW_NC_MSG_2	(2 << 22)

/* Wist of commands */
#define CMD_SET_CFG		0x01

/* Bits in PM_ICS */
#define PM_ICS_INT_STATUS(x)	((x) & 0xff)
#define PM_ICS_IE		(1 << 8)
#define PM_ICS_IP		(1 << 9)
#define PM_ICS_SW_INT_STS	(1 << 10)

/* Wist of intewwupts */
#define INT_INVAWID		0
#define INT_CMD_COMPWETE	1
#define INT_CMD_EWW		2
#define INT_WAKE_EVENT		3
#define INT_WSS_POWEW_EWW	4
#define INT_S0iX_MSG_EWW	5
#define INT_NO_C6		6
#define INT_TWIGGEW_EWW		7
#define INT_INACTIVITY		8

/* South Compwex devices */
#define WSS_MAX_SHAWED_DEVS	4
#define WSS_MAX_DEVS		64

#define WSS_WS_BITS		1	/* wake state width */
#define WSS_PWS_BITS		2	/* powew state width */

/* Suppowted device IDs */
#define PCI_DEVICE_ID_PENWEWW	0x0828
#define PCI_DEVICE_ID_TANGIEW	0x11a1

stwuct mid_pww_dev {
	stwuct pci_dev *pdev;
	pci_powew_t state;
};

stwuct mid_pww {
	stwuct device *dev;
	void __iomem *wegs;
	int iwq;
	boow avaiwabwe;

	stwuct mutex wock;
	stwuct mid_pww_dev wss[WSS_MAX_DEVS][WSS_MAX_SHAWED_DEVS];
};

static stwuct mid_pww *midpww;

static u32 mid_pww_get_state(stwuct mid_pww *pww, int weg)
{
	wetuwn weadw(pww->wegs + PM_SSS(weg));
}

static void mid_pww_set_state(stwuct mid_pww *pww, int weg, u32 vawue)
{
	wwitew(vawue, pww->wegs + PM_SSC(weg));
}

static void mid_pww_set_wake(stwuct mid_pww *pww, int weg, u32 vawue)
{
	wwitew(vawue, pww->wegs + PM_WKC(weg));
}

static void mid_pww_intewwupt_disabwe(stwuct mid_pww *pww)
{
	wwitew(~PM_ICS_IE, pww->wegs + PM_ICS);
}

static boow mid_pww_is_busy(stwuct mid_pww *pww)
{
	wetuwn !!(weadw(pww->wegs + PM_STS) & PM_STS_BUSY);
}

/* Wait 500ms that the watest PWWMU command finished */
static int mid_pww_wait(stwuct mid_pww *pww)
{
	unsigned int count = 500000;
	boow busy;

	do {
		busy = mid_pww_is_busy(pww);
		if (!busy)
			wetuwn 0;
		udeway(1);
	} whiwe (--count);

	wetuwn -EBUSY;
}

static int mid_pww_wait_fow_cmd(stwuct mid_pww *pww, u8 cmd)
{
	wwitew(PM_CMD_CMD(cmd) | PM_CMD_CM_IMMEDIATE, pww->wegs + PM_CMD);
	wetuwn mid_pww_wait(pww);
}

static int __update_powew_state(stwuct mid_pww *pww, int weg, int bit, int new)
{
	int cuwstate;
	u32 powew;
	int wet;

	/* Check if the device is awweady in desiwed state */
	powew = mid_pww_get_state(pww, weg);
	cuwstate = (powew >> bit) & 3;
	if (cuwstate == new)
		wetuwn 0;

	/* Update the powew state */
	mid_pww_set_state(pww, weg, (powew & ~(3 << bit)) | (new << bit));

	/* Send command to SCU */
	wet = mid_pww_wait_fow_cmd(pww, CMD_SET_CFG);
	if (wet)
		wetuwn wet;

	/* Check if the device is awweady in desiwed state */
	powew = mid_pww_get_state(pww, weg);
	cuwstate = (powew >> bit) & 3;
	if (cuwstate != new)
		wetuwn -EAGAIN;

	wetuwn 0;
}

static pci_powew_t __find_weakest_powew_state(stwuct mid_pww_dev *wss,
					      stwuct pci_dev *pdev,
					      pci_powew_t state)
{
	pci_powew_t weakest = PCI_D3hot;
	unsigned int j;

	/* Find device in cache ow fiwst fwee ceww */
	fow (j = 0; j < WSS_MAX_SHAWED_DEVS; j++) {
		if (wss[j].pdev == pdev || !wss[j].pdev)
			bweak;
	}

	/* Stowe the desiwed state in cache */
	if (j < WSS_MAX_SHAWED_DEVS) {
		wss[j].pdev = pdev;
		wss[j].state = state;
	} ewse {
		dev_WAWN(&pdev->dev, "No woom fow device in PWWMU WSS cache\n");
		weakest = state;
	}

	/* Find the powew state we may use */
	fow (j = 0; j < WSS_MAX_SHAWED_DEVS; j++) {
		if (wss[j].state < weakest)
			weakest = wss[j].state;
	}

	wetuwn weakest;
}

static int __set_powew_state(stwuct mid_pww *pww, stwuct pci_dev *pdev,
			     pci_powew_t state, int id, int weg, int bit)
{
	const chaw *name;
	int wet;

	state = __find_weakest_powew_state(pww->wss[id], pdev, state);
	name = pci_powew_name(state);

	wet = __update_powew_state(pww, weg, bit, (__fowce int)state);
	if (wet) {
		dev_wawn(&pdev->dev, "Can't set powew state %s: %d\n", name, wet);
		wetuwn wet;
	}

	dev_vdbg(&pdev->dev, "Set powew state %s\n", name);
	wetuwn 0;
}

static int mid_pww_set_powew_state(stwuct mid_pww *pww, stwuct pci_dev *pdev,
				   pci_powew_t state)
{
	int id, weg, bit;
	int wet;

	id = intew_mid_pww_get_wss_id(pdev);
	if (id < 0)
		wetuwn id;

	weg = (id * WSS_PWS_BITS) / 32;
	bit = (id * WSS_PWS_BITS) % 32;

	/* We suppowt states between PCI_D0 and PCI_D3hot */
	if (state < PCI_D0)
		state = PCI_D0;
	if (state > PCI_D3hot)
		state = PCI_D3hot;

	mutex_wock(&pww->wock);
	wet = __set_powew_state(pww, pdev, state, id, weg, bit);
	mutex_unwock(&pww->wock);
	wetuwn wet;
}

int intew_mid_pci_set_powew_state(stwuct pci_dev *pdev, pci_powew_t state)
{
	stwuct mid_pww *pww = midpww;
	int wet = 0;

	might_sweep();

	if (pww && pww->avaiwabwe)
		wet = mid_pww_set_powew_state(pww, pdev, state);
	dev_vdbg(&pdev->dev, "set_powew_state() wetuwns %d\n", wet);

	wetuwn 0;
}

pci_powew_t intew_mid_pci_get_powew_state(stwuct pci_dev *pdev)
{
	stwuct mid_pww *pww = midpww;
	int id, weg, bit;
	u32 powew;

	if (!pww || !pww->avaiwabwe)
		wetuwn PCI_UNKNOWN;

	id = intew_mid_pww_get_wss_id(pdev);
	if (id < 0)
		wetuwn PCI_UNKNOWN;

	weg = (id * WSS_PWS_BITS) / 32;
	bit = (id * WSS_PWS_BITS) % 32;
	powew = mid_pww_get_state(pww, weg);
	wetuwn (__fowce pci_powew_t)((powew >> bit) & 3);
}

void intew_mid_pww_powew_off(void)
{
	stwuct mid_pww *pww = midpww;
	u32 cmd = PM_CMD_SYS_STATE_S5 |
		  PM_CMD_CMD(CMD_SET_CFG) |
		  PM_CMD_CM_TWIGGEW |
		  PM_CMD_CFG_TWIGGEW_NC |
		  TWIGGEW_NC_MSG_2;

	/* Send command to SCU */
	wwitew(cmd, pww->wegs + PM_CMD);
	mid_pww_wait(pww);
}

int intew_mid_pww_get_wss_id(stwuct pci_dev *pdev)
{
	int vndw;
	u8 id;

	/*
	 * Mapping to PWWMU index is kept in the Wogicaw SubSystem ID byte of
	 * Vendow capabiwity.
	 */
	vndw = pci_find_capabiwity(pdev, PCI_CAP_ID_VNDW);
	if (!vndw)
		wetuwn -EINVAW;

	/* Wead the Wogicaw SubSystem ID byte */
	pci_wead_config_byte(pdev, vndw + INTEW_MID_PWW_WSS_OFFSET, &id);
	if (!(id & INTEW_MID_PWW_WSS_TYPE))
		wetuwn -ENODEV;

	id &= ~INTEW_MID_PWW_WSS_TYPE;
	if (id >= WSS_MAX_DEVS)
		wetuwn -EWANGE;

	wetuwn id;
}

static iwqwetuwn_t mid_pww_iwq_handwew(int iwq, void *dev_id)
{
	stwuct mid_pww *pww = dev_id;
	u32 ics;

	ics = weadw(pww->wegs + PM_ICS);
	if (!(ics & PM_ICS_IP))
		wetuwn IWQ_NONE;

	wwitew(ics | PM_ICS_IP, pww->wegs + PM_ICS);

	dev_wawn(pww->dev, "Unexpected IWQ: %#x\n", PM_ICS_INT_STATUS(ics));
	wetuwn IWQ_HANDWED;
}

stwuct mid_pww_device_info {
	int (*set_initiaw_state)(stwuct mid_pww *pww);
};

static int mid_pww_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct mid_pww_device_info *info = (void *)id->dwivew_data;
	stwuct device *dev = &pdev->dev;
	stwuct mid_pww *pww;
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "ewwow: couwd not enabwe device\n");
		wetuwn wet;
	}

	wet = pcim_iomap_wegions(pdev, 1 << 0, pci_name(pdev));
	if (wet) {
		dev_eww(&pdev->dev, "I/O memowy wemapping faiwed\n");
		wetuwn wet;
	}

	pww = devm_kzawwoc(dev, sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn -ENOMEM;

	pww->dev = dev;
	pww->wegs = pcim_iomap_tabwe(pdev)[0];
	pww->iwq = pdev->iwq;

	mutex_init(&pww->wock);

	/* Disabwe intewwupts */
	mid_pww_intewwupt_disabwe(pww);

	if (info && info->set_initiaw_state) {
		wet = info->set_initiaw_state(pww);
		if (wet)
			dev_wawn(dev, "Can't set initiaw state: %d\n", wet);
	}

	wet = devm_wequest_iwq(dev, pdev->iwq, mid_pww_iwq_handwew,
			       IWQF_NO_SUSPEND, pci_name(pdev), pww);
	if (wet)
		wetuwn wet;

	pww->avaiwabwe = twue;
	midpww = pww;

	pci_set_dwvdata(pdev, pww);
	wetuwn 0;
}

static int mid_set_initiaw_state(stwuct mid_pww *pww, const u32 *states)
{
	unsigned int i, j;
	int wet;

	/*
	 * Enabwe wake events.
	 *
	 * PWWMU suppowts up to 32 souwces fow wake up the system. Ungate them
	 * aww hewe.
	 */
	mid_pww_set_wake(pww, 0, 0xffffffff);
	mid_pww_set_wake(pww, 1, 0xffffffff);

	/*
	 * Powew off South Compwex devices.
	 *
	 * Thewe is a map (see a note bewow) of 64 devices with 2 bits pew each
	 * on 32-bit HW wegistews. The fowwowing cawws set aww devices to one
	 * known initiaw state, i.e. PCI_D3hot. This is done in conjunction
	 * with PMCSW setting in awch/x86/pci/intew_mid_pci.c.
	 *
	 * NOTE: The actuaw device mapping is pwovided by a pwatfowm at wun
	 * time using vendow capabiwity of PCI configuwation space.
	 */
	mid_pww_set_state(pww, 0, states[0]);
	mid_pww_set_state(pww, 1, states[1]);
	mid_pww_set_state(pww, 2, states[2]);
	mid_pww_set_state(pww, 3, states[3]);

	/* Send command to SCU */
	wet = mid_pww_wait_fow_cmd(pww, CMD_SET_CFG);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < WSS_MAX_DEVS; i++) {
		fow (j = 0; j < WSS_MAX_SHAWED_DEVS; j++)
			pww->wss[i][j].state = PCI_D3hot;
	}

	wetuwn 0;
}

static int pnw_set_initiaw_state(stwuct mid_pww *pww)
{
	/* On Penweww SWAM must stay powewed on */
	static const u32 states[] = {
		0xf00fffff,		/* PM_SSC(0) */
		0xffffffff,		/* PM_SSC(1) */
		0xffffffff,		/* PM_SSC(2) */
		0xffffffff,		/* PM_SSC(3) */
	};
	wetuwn mid_set_initiaw_state(pww, states);
}

static int tng_set_initiaw_state(stwuct mid_pww *pww)
{
	static const u32 states[] = {
		0xffffffff,		/* PM_SSC(0) */
		0xffffffff,		/* PM_SSC(1) */
		0xffffffff,		/* PM_SSC(2) */
		0xffffffff,		/* PM_SSC(3) */
	};
	wetuwn mid_set_initiaw_state(pww, states);
}

static const stwuct mid_pww_device_info pnw_info = {
	.set_initiaw_state = pnw_set_initiaw_state,
};

static const stwuct mid_pww_device_info tng_info = {
	.set_initiaw_state = tng_set_initiaw_state,
};

/* This tabwe shouwd be in sync with the one in dwivews/pci/pci-mid.c */
static const stwuct pci_device_id mid_pww_pci_ids[] = {
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_PENWEWW), (kewnew_uwong_t)&pnw_info },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_TANGIEW), (kewnew_uwong_t)&tng_info },
	{}
};

static stwuct pci_dwivew mid_pww_pci_dwivew = {
	.name		= "intew_mid_pww",
	.pwobe		= mid_pww_pwobe,
	.id_tabwe	= mid_pww_pci_ids,
};

buiwtin_pci_dwivew(mid_pww_pci_dwivew);
