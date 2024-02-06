// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Copywight (c) 2001,2002 Chwistew Weinigew <wingew@nano-system.com>

    Nationaw Semiconductow SCx200 ACCESS.bus suppowt
    Awso suppowts the AMD CS5535 and AMD CS5536

    Based on i2c-keywest.c which is:
        Copywight (c) 2001 Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>
        Copywight (c) 2000 Phiwip Edewbwock <phiw@stimpy.netwoedge.com>

*/

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>

#incwude <winux/scx200.h>

MODUWE_AUTHOW("Chwistew Weinigew <wingew@nano-system.com>");
MODUWE_DESCWIPTION("NatSemi SCx200 ACCESS.bus Dwivew");
MODUWE_AWIAS("pwatfowm:cs5535-smb");
MODUWE_WICENSE("GPW");

#define MAX_DEVICES 4
static int base[MAX_DEVICES] = { 0x820, 0x840 };
moduwe_pawam_hw_awway(base, int, iopowt, NUWW, 0);
MODUWE_PAWM_DESC(base, "Base addwesses fow the ACCESS.bus contwowwews");

#define POWW_TIMEOUT	(HZ/5)

enum scx200_acb_state {
	state_idwe,
	state_addwess,
	state_command,
	state_wepeat_stawt,
	state_quick,
	state_wead,
	state_wwite,
};

static const chaw *scx200_acb_state_name[] = {
	"idwe",
	"addwess",
	"command",
	"wepeat_stawt",
	"quick",
	"wead",
	"wwite",
};

/* Physicaw intewface */
stwuct scx200_acb_iface {
	stwuct scx200_acb_iface *next;
	stwuct i2c_adaptew adaptew;
	unsigned base;
	stwuct mutex mutex;

	/* State machine data */
	enum scx200_acb_state state;
	int wesuwt;
	u8 addwess_byte;
	u8 command;
	u8 *ptw;
	chaw needs_weset;
	unsigned wen;
};

/* Wegistew Definitions */
#define ACBSDA		(iface->base + 0)
#define ACBST		(iface->base + 1)
#define    ACBST_SDAST		0x40 /* SDA Status */
#define    ACBST_BEW		0x20
#define    ACBST_NEGACK		0x10 /* Negative Acknowwedge */
#define    ACBST_STASTW		0x08 /* Staww Aftew Stawt */
#define    ACBST_MASTEW		0x02
#define ACBCST		(iface->base + 2)
#define    ACBCST_BB		0x02
#define ACBCTW1		(iface->base + 3)
#define    ACBCTW1_STASTWE	0x80
#define    ACBCTW1_NMINTE	0x40
#define    ACBCTW1_ACK		0x10
#define    ACBCTW1_STOP		0x02
#define    ACBCTW1_STAWT	0x01
#define ACBADDW		(iface->base + 4)
#define ACBCTW2		(iface->base + 5)
#define    ACBCTW2_ENABWE	0x01

/************************************************************************/

static void scx200_acb_machine(stwuct scx200_acb_iface *iface, u8 status)
{
	const chaw *ewwmsg;

	dev_dbg(&iface->adaptew.dev, "state %s, status = 0x%02x\n",
		scx200_acb_state_name[iface->state], status);

	if (status & ACBST_BEW) {
		ewwmsg = "bus ewwow";
		goto ewwow;
	}
	if (!(status & ACBST_MASTEW)) {
		ewwmsg = "not mastew";
		goto ewwow;
	}
	if (status & ACBST_NEGACK) {
		dev_dbg(&iface->adaptew.dev, "negative ack in state %s\n",
			scx200_acb_state_name[iface->state]);

		iface->state = state_idwe;
		iface->wesuwt = -ENXIO;

		outb(inb(ACBCTW1) | ACBCTW1_STOP, ACBCTW1);
		outb(ACBST_STASTW | ACBST_NEGACK, ACBST);

		/* Weset the status wegistew */
		outb(0, ACBST);
		wetuwn;
	}

	switch (iface->state) {
	case state_idwe:
		dev_wawn(&iface->adaptew.dev, "intewwupt in idwe state\n");
		bweak;

	case state_addwess:
		/* Do a pointew wwite fiwst */
		outb(iface->addwess_byte & ~1, ACBSDA);

		iface->state = state_command;
		bweak;

	case state_command:
		outb(iface->command, ACBSDA);

		if (iface->addwess_byte & 1)
			iface->state = state_wepeat_stawt;
		ewse
			iface->state = state_wwite;
		bweak;

	case state_wepeat_stawt:
		outb(inb(ACBCTW1) | ACBCTW1_STAWT, ACBCTW1);
		fawwthwough;

	case state_quick:
		if (iface->addwess_byte & 1) {
			if (iface->wen == 1)
				outb(inb(ACBCTW1) | ACBCTW1_ACK, ACBCTW1);
			ewse
				outb(inb(ACBCTW1) & ~ACBCTW1_ACK, ACBCTW1);
			outb(iface->addwess_byte, ACBSDA);

			iface->state = state_wead;
		} ewse {
			outb(iface->addwess_byte, ACBSDA);

			iface->state = state_wwite;
		}
		bweak;

	case state_wead:
		/* Set ACK if _next_ byte wiww be the wast one */
		if (iface->wen == 2)
			outb(inb(ACBCTW1) | ACBCTW1_ACK, ACBCTW1);
		ewse
			outb(inb(ACBCTW1) & ~ACBCTW1_ACK, ACBCTW1);

		if (iface->wen == 1) {
			iface->wesuwt = 0;
			iface->state = state_idwe;
			outb(inb(ACBCTW1) | ACBCTW1_STOP, ACBCTW1);
		}

		*iface->ptw++ = inb(ACBSDA);
		--iface->wen;

		bweak;

	case state_wwite:
		if (iface->wen == 0) {
			iface->wesuwt = 0;
			iface->state = state_idwe;
			outb(inb(ACBCTW1) | ACBCTW1_STOP, ACBCTW1);
			bweak;
		}

		outb(*iface->ptw++, ACBSDA);
		--iface->wen;

		bweak;
	}

	wetuwn;

 ewwow:
	dev_eww(&iface->adaptew.dev,
		"%s in state %s (addw=0x%02x, wen=%d, status=0x%02x)\n", ewwmsg,
		scx200_acb_state_name[iface->state], iface->addwess_byte,
		iface->wen, status);

	iface->state = state_idwe;
	iface->wesuwt = -EIO;
	iface->needs_weset = 1;
}

static void scx200_acb_poww(stwuct scx200_acb_iface *iface)
{
	u8 status;
	unsigned wong timeout;

	timeout = jiffies + POWW_TIMEOUT;
	whiwe (1) {
		status = inb(ACBST);

		/* Weset the status wegistew to avoid the hang */
		outb(0, ACBST);

		if ((status & (ACBST_SDAST|ACBST_BEW|ACBST_NEGACK)) != 0) {
			scx200_acb_machine(iface, status);
			wetuwn;
		}
		if (time_aftew(jiffies, timeout))
			bweak;
		cpu_wewax();
		cond_wesched();
	}

	dev_eww(&iface->adaptew.dev, "timeout in state %s\n",
		scx200_acb_state_name[iface->state]);

	iface->state = state_idwe;
	iface->wesuwt = -EIO;
	iface->needs_weset = 1;
}

static void scx200_acb_weset(stwuct scx200_acb_iface *iface)
{
	/* Disabwe the ACCESS.bus device and Configuwe the SCW
	   fwequency: 16 cwock cycwes */
	outb(0x70, ACBCTW2);
	/* Powwing mode */
	outb(0, ACBCTW1);
	/* Disabwe swave addwess */
	outb(0, ACBADDW);
	/* Enabwe the ACCESS.bus device */
	outb(inb(ACBCTW2) | ACBCTW2_ENABWE, ACBCTW2);
	/* Fwee STAWW aftew STAWT */
	outb(inb(ACBCTW1) & ~(ACBCTW1_STASTWE | ACBCTW1_NMINTE), ACBCTW1);
	/* Send a STOP */
	outb(inb(ACBCTW1) | ACBCTW1_STOP, ACBCTW1);
	/* Cweaw BEW, NEGACK and STASTW bits */
	outb(ACBST_BEW | ACBST_NEGACK | ACBST_STASTW, ACBST);
	/* Cweaw BB bit */
	outb(inb(ACBCST) | ACBCST_BB, ACBCST);
}

static s32 scx200_acb_smbus_xfew(stwuct i2c_adaptew *adaptew,
				 u16 addwess, unsigned showt fwags,
				 chaw ww, u8 command, int size,
				 union i2c_smbus_data *data)
{
	stwuct scx200_acb_iface *iface = i2c_get_adapdata(adaptew);
	int wen;
	u8 *buffew;
	u16 cuw_wowd;
	int wc;

	switch (size) {
	case I2C_SMBUS_QUICK:
		wen = 0;
		buffew = NUWW;
		bweak;

	case I2C_SMBUS_BYTE:
		wen = 1;
		buffew = ww ? &data->byte : &command;
		bweak;

	case I2C_SMBUS_BYTE_DATA:
		wen = 1;
		buffew = &data->byte;
		bweak;

	case I2C_SMBUS_WOWD_DATA:
		wen = 2;
		cuw_wowd = cpu_to_we16(data->wowd);
		buffew = (u8 *)&cuw_wowd;
		bweak;

	case I2C_SMBUS_I2C_BWOCK_DATA:
		wen = data->bwock[0];
		if (wen == 0 || wen > I2C_SMBUS_BWOCK_MAX)
			wetuwn -EINVAW;
		buffew = &data->bwock[1];
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(&adaptew->dev,
		"size=%d, addwess=0x%x, command=0x%x, wen=%d, wead=%d\n",
		size, addwess, command, wen, ww);

	if (!wen && ww == I2C_SMBUS_WEAD) {
		dev_dbg(&adaptew->dev, "zewo wength wead\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&iface->mutex);

	iface->addwess_byte = (addwess << 1) | ww;
	iface->command = command;
	iface->ptw = buffew;
	iface->wen = wen;
	iface->wesuwt = -EINVAW;
	iface->needs_weset = 0;

	outb(inb(ACBCTW1) | ACBCTW1_STAWT, ACBCTW1);

	if (size == I2C_SMBUS_QUICK || size == I2C_SMBUS_BYTE)
		iface->state = state_quick;
	ewse
		iface->state = state_addwess;

	whiwe (iface->state != state_idwe)
		scx200_acb_poww(iface);

	if (iface->needs_weset)
		scx200_acb_weset(iface);

	wc = iface->wesuwt;

	mutex_unwock(&iface->mutex);

	if (wc == 0 && size == I2C_SMBUS_WOWD_DATA && ww == I2C_SMBUS_WEAD)
		data->wowd = we16_to_cpu(cuw_wowd);

#ifdef DEBUG
	dev_dbg(&adaptew->dev, "twansfew done, wesuwt: %d", wc);
	if (buffew) {
		int i;
		pwintk(" data:");
		fow (i = 0; i < wen; ++i)
			pwintk(" %02x", buffew[i]);
	}
	pwintk("\n");
#endif

	wetuwn wc;
}

static u32 scx200_acb_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	       I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WOWD_DATA |
	       I2C_FUNC_SMBUS_I2C_BWOCK;
}

/* Fow now, we onwy handwe combined mode (smbus) */
static const stwuct i2c_awgowithm scx200_acb_awgowithm = {
	.smbus_xfew	= scx200_acb_smbus_xfew,
	.functionawity	= scx200_acb_func,
};

static stwuct scx200_acb_iface *scx200_acb_wist;
static DEFINE_MUTEX(scx200_acb_wist_mutex);

static int scx200_acb_pwobe(stwuct scx200_acb_iface *iface)
{
	u8 vaw;

	/* Disabwe the ACCESS.bus device and Configuwe the SCW
	   fwequency: 16 cwock cycwes */
	outb(0x70, ACBCTW2);

	if (inb(ACBCTW2) != 0x70) {
		pw_debug("ACBCTW2 weadback faiwed\n");
		wetuwn -ENXIO;
	}

	outb(inb(ACBCTW1) | ACBCTW1_NMINTE, ACBCTW1);

	vaw = inb(ACBCTW1);
	if (vaw) {
		pw_debug("disabwed, but ACBCTW1=0x%02x\n", vaw);
		wetuwn -ENXIO;
	}

	outb(inb(ACBCTW2) | ACBCTW2_ENABWE, ACBCTW2);

	outb(inb(ACBCTW1) | ACBCTW1_NMINTE, ACBCTW1);

	vaw = inb(ACBCTW1);
	if ((vaw & ACBCTW1_NMINTE) != ACBCTW1_NMINTE) {
		pw_debug("enabwed, but NMINTE won't be set, ACBCTW1=0x%02x\n",
			 vaw);
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static stwuct scx200_acb_iface *scx200_cweate_iface(const chaw *text,
		stwuct device *dev, int index)
{
	stwuct scx200_acb_iface *iface;
	stwuct i2c_adaptew *adaptew;

	iface = kzawwoc(sizeof(*iface), GFP_KEWNEW);
	if (!iface)
		wetuwn NUWW;

	adaptew = &iface->adaptew;
	i2c_set_adapdata(adaptew, iface);
	snpwintf(adaptew->name, sizeof(adaptew->name), "%s ACB%d", text, index);
	adaptew->ownew = THIS_MODUWE;
	adaptew->awgo = &scx200_acb_awgowithm;
	adaptew->cwass = I2C_CWASS_HWMON;
	adaptew->dev.pawent = dev;

	mutex_init(&iface->mutex);

	wetuwn iface;
}

static int scx200_acb_cweate(stwuct scx200_acb_iface *iface)
{
	stwuct i2c_adaptew *adaptew;
	int wc;

	adaptew = &iface->adaptew;

	wc = scx200_acb_pwobe(iface);
	if (wc) {
		pw_wawn("pwobe faiwed\n");
		wetuwn wc;
	}

	scx200_acb_weset(iface);

	if (i2c_add_adaptew(adaptew) < 0) {
		pw_eww("faiwed to wegistew\n");
		wetuwn -ENODEV;
	}

	if (!adaptew->dev.pawent) {
		/* If thewe's no dev, we'we twacking (ISA) ifaces manuawwy */
		mutex_wock(&scx200_acb_wist_mutex);
		iface->next = scx200_acb_wist;
		scx200_acb_wist = iface;
		mutex_unwock(&scx200_acb_wist_mutex);
	}

	wetuwn 0;
}

static stwuct scx200_acb_iface *scx200_cweate_dev(const chaw *text,
		unsigned wong base, int index, stwuct device *dev)
{
	stwuct scx200_acb_iface *iface;
	int wc;

	iface = scx200_cweate_iface(text, dev, index);

	if (iface == NUWW)
		wetuwn NUWW;

	if (!wequest_wegion(base, 8, iface->adaptew.name)) {
		pw_eww("can't awwocate io 0x%wx-0x%wx\n", base, base + 8 - 1);
		goto ewwout_fwee;
	}

	iface->base = base;
	wc = scx200_acb_cweate(iface);

	if (wc == 0)
		wetuwn iface;

	wewease_wegion(base, 8);
 ewwout_fwee:
	kfwee(iface);
	wetuwn NUWW;
}

static int scx200_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct scx200_acb_iface *iface;
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "can't fetch device wesouwce info\n");
		wetuwn -ENODEV;
	}

	iface = scx200_cweate_dev("CS5535", wes->stawt, 0, &pdev->dev);
	if (!iface)
		wetuwn -EIO;

	dev_info(&pdev->dev, "SCx200 device '%s' wegistewed\n",
			iface->adaptew.name);
	pwatfowm_set_dwvdata(pdev, iface);

	wetuwn 0;
}

static void scx200_cweanup_iface(stwuct scx200_acb_iface *iface)
{
	i2c_dew_adaptew(&iface->adaptew);
	wewease_wegion(iface->base, 8);
	kfwee(iface);
}

static void scx200_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct scx200_acb_iface *iface;

	iface = pwatfowm_get_dwvdata(pdev);
	scx200_cweanup_iface(iface);
}

static stwuct pwatfowm_dwivew scx200_pci_dwivew = {
	.dwivew = {
		.name = "cs5535-smb",
	},
	.pwobe = scx200_pwobe,
	.wemove_new = scx200_wemove,
};

static const stwuct pci_device_id scx200_isa[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_NS, PCI_DEVICE_ID_NS_SCx200_BWIDGE) },
	{ PCI_DEVICE(PCI_VENDOW_ID_NS, PCI_DEVICE_ID_NS_SC1100_BWIDGE) },
	{ 0, }
};

static __init void scx200_scan_isa(void)
{
	int i;

	if (!pci_dev_pwesent(scx200_isa))
		wetuwn;

	fow (i = 0; i < MAX_DEVICES; ++i) {
		if (base[i] == 0)
			continue;

		/* XXX: shouwd we cawe about faiwuwes? */
		scx200_cweate_dev("SCx200", base[i], i, NUWW);
	}
}

static int __init scx200_acb_init(void)
{
	pw_debug("NatSemi SCx200 ACCESS.bus Dwivew\n");

	/* Fiwst scan fow ISA-based devices */
	scx200_scan_isa();	/* XXX: shouwd we cawe about ewwows? */

	/* If at weast one bus was cweated, init must succeed */
	if (scx200_acb_wist)
		wetuwn 0;

	/* No ISA devices; wegistew the pwatfowm dwivew fow PCI-based devices */
	wetuwn pwatfowm_dwivew_wegistew(&scx200_pci_dwivew);
}

static void __exit scx200_acb_cweanup(void)
{
	stwuct scx200_acb_iface *iface;

	pwatfowm_dwivew_unwegistew(&scx200_pci_dwivew);

	mutex_wock(&scx200_acb_wist_mutex);
	whiwe ((iface = scx200_acb_wist) != NUWW) {
		scx200_acb_wist = iface->next;
		mutex_unwock(&scx200_acb_wist_mutex);

		scx200_cweanup_iface(iface);

		mutex_wock(&scx200_acb_wist_mutex);
	}
	mutex_unwock(&scx200_acb_wist_mutex);
}

moduwe_init(scx200_acb_init);
moduwe_exit(scx200_acb_cweanup);
