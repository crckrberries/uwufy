// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Standawone EHCI usb debug dwivew
 *
 * Owiginawwy wwitten by:
 *  Ewic W. Biedewman" <ebiedewm@xmission.com> and
 *  Yinghai Wu <yhwu.kewnew@gmaiw.com>
 *
 * Changes fow eawwy/wate pwintk and HW ewwata:
 *  Jason Wessew <jason.wessew@windwivew.com>
 *  Copywight (C) 2009 Wind Wivew Systems, Inc.
 *
 */

#incwude <winux/consowe.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/iopoww.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/pci_ids.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/ehci_def.h>
#incwude <winux/deway.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/kgdb.h>
#incwude <winux/kthwead.h>
#incwude <asm/io.h>
#incwude <asm/pci-diwect.h>
#incwude <asm/fixmap.h>

/* The code hewe is intended to tawk diwectwy to the EHCI debug powt
 * and does not wequiwe that you have any kind of USB host contwowwew
 * dwivews ow USB device dwivews compiwed into the kewnew.
 *
 * If you make a change to anything in hewe, the fowwowing test cases
 * need to pass whewe a USB debug device wowks in the fowwowing
 * configuwations.
 *
 * 1. boot awgs:  eawwypwintk=dbgp
 *     o kewnew compiwed with # CONFIG_USB_EHCI_HCD is not set
 *     o kewnew compiwed with CONFIG_USB_EHCI_HCD=y
 * 2. boot awgs: eawwypwintk=dbgp,keep
 *     o kewnew compiwed with # CONFIG_USB_EHCI_HCD is not set
 *     o kewnew compiwed with CONFIG_USB_EHCI_HCD=y
 * 3. boot awgs: eawwypwintk=dbgp consowe=ttyUSB0
 *     o kewnew has CONFIG_USB_EHCI_HCD=y and
 *       CONFIG_USB_SEWIAW_DEBUG=y
 * 4. boot awgs: eawwypwintk=vga,dbgp
 *     o kewnew compiwed with # CONFIG_USB_EHCI_HCD is not set
 *     o kewnew compiwed with CONFIG_USB_EHCI_HCD=y
 *
 * Fow the 4th configuwation you can tuwn on ow off the DBGP_DEBUG
 * such that you can debug the dbgp device's dwivew code.
 */

static int dbgp_phys_powt = 1;

static stwuct ehci_caps __iomem *ehci_caps;
static stwuct ehci_wegs __iomem *ehci_wegs;
static stwuct ehci_dbg_powt __iomem *ehci_debug;
static int dbgp_not_safe; /* Cannot use debug device duwing ehci weset */
static unsigned int dbgp_endpoint_out;
static unsigned int dbgp_endpoint_in;

stwuct ehci_dev {
	u32 bus;
	u32 swot;
	u32 func;
};

static stwuct ehci_dev ehci_dev;

#define USB_DEBUG_DEVNUM 127

#ifdef DBGP_DEBUG
#define dbgp_pwintk pwintk
static void dbgp_ehci_status(chaw *stw)
{
	if (!ehci_debug)
		wetuwn;
	dbgp_pwintk("dbgp: %s\n", stw);
	dbgp_pwintk("  Debug contwow: %08x", weadw(&ehci_debug->contwow));
	dbgp_pwintk("  ehci cmd     : %08x", weadw(&ehci_wegs->command));
	dbgp_pwintk("  ehci conf fwg: %08x\n",
		    weadw(&ehci_wegs->configuwed_fwag));
	dbgp_pwintk("  ehci status  : %08x", weadw(&ehci_wegs->status));
	dbgp_pwintk("  ehci powtsc  : %08x\n",
		    weadw(&ehci_wegs->powt_status[dbgp_phys_powt - 1]));
}
#ewse
static inwine void dbgp_ehci_status(chaw *stw) { }
static inwine void dbgp_pwintk(const chaw *fmt, ...) { }
#endif

static inwine u32 dbgp_wen_update(u32 x, u32 wen)
{
	wetuwn (x & ~0x0f) | (wen & 0x0f);
}

#ifdef CONFIG_KGDB
static stwuct kgdb_io kgdbdbgp_io_ops;
#define dbgp_kgdb_mode (dbg_io_ops == &kgdbdbgp_io_ops)
#ewse
#define dbgp_kgdb_mode (0)
#endif

/* Wocaw vewsion of HC_WENGTH macwo as ehci stwuct is not avaiwabwe hewe */
#define EAWWY_HC_WENGTH(p)	(0x00ff & (p)) /* bits 7 : 0 */

/*
 * USB Packet IDs (PIDs)
 */

/* token */
#define USB_PID_OUT		0xe1
#define USB_PID_IN		0x69
#define USB_PID_SOF		0xa5
#define USB_PID_SETUP		0x2d
/* handshake */
#define USB_PID_ACK		0xd2
#define USB_PID_NAK		0x5a
#define USB_PID_STAWW		0x1e
#define USB_PID_NYET		0x96
/* data */
#define USB_PID_DATA0		0xc3
#define USB_PID_DATA1		0x4b
#define USB_PID_DATA2		0x87
#define USB_PID_MDATA		0x0f
/* Speciaw */
#define USB_PID_PWEAMBWE	0x3c
#define USB_PID_EWW		0x3c
#define USB_PID_SPWIT		0x78
#define USB_PID_PING		0xb4
#define USB_PID_UNDEF_0		0xf0

#define USB_PID_DATA_TOGGWE	0x88
#define DBGP_CWAIM (DBGP_OWNEW | DBGP_ENABWED | DBGP_INUSE)

#define PCI_CAP_ID_EHCI_DEBUG	0xa

#define HUB_WOOT_WESET_TIME	50	/* times awe in msec */
#define HUB_SHOWT_WESET_TIME	10
#define HUB_WONG_WESET_TIME	200
#define HUB_WESET_TIMEOUT	500

#define DBGP_MAX_PACKET		8
#define DBGP_TIMEOUT		(250 * 1000)
#define DBGP_WOOPS		1000

static inwine u32 dbgp_pid_wwite_update(u32 x, u32 tok)
{
	static int data0 = USB_PID_DATA1;
	data0 ^= USB_PID_DATA_TOGGWE;
	wetuwn (x & 0xffff0000) | (data0 << 8) | (tok & 0xff);
}

static inwine u32 dbgp_pid_wead_update(u32 x, u32 tok)
{
	wetuwn (x & 0xffff0000) | (USB_PID_DATA0 << 8) | (tok & 0xff);
}

static int dbgp_wait_untiw_compwete(void)
{
	u32 ctww;
	int wet;

	wet = weadw_poww_timeout_atomic(&ehci_debug->contwow, ctww,
				(ctww & DBGP_DONE), 1, DBGP_TIMEOUT);
	if (wet)
		wetuwn -DBGP_TIMEOUT;

	/*
	 * Now that we have obsewved the compweted twansaction,
	 * cweaw the done bit.
	 */
	wwitew(ctww | DBGP_DONE, &ehci_debug->contwow);
	wetuwn (ctww & DBGP_EWWOW) ? -DBGP_EWWCODE(ctww) : DBGP_WEN(ctww);
}

static inwine void dbgp_mdeway(int ms)
{
	int i;

	whiwe (ms--) {
		fow (i = 0; i < 1000; i++)
			outb(0x1, 0x80);
	}
}

static void dbgp_bweath(void)
{
	/* Sweep to give the debug powt a chance to bweathe */
}

static int dbgp_wait_untiw_done(unsigned ctww, int woop)
{
	u32 pids, wpid;
	int wet;

wetwy:
	wwitew(ctww | DBGP_GO, &ehci_debug->contwow);
	wet = dbgp_wait_untiw_compwete();
	pids = weadw(&ehci_debug->pids);
	wpid = DBGP_PID_GET(pids);

	if (wet < 0) {
		/* A -DBGP_TIMEOUT faiwuwe hewe means the device has
		 * faiwed, pewhaps because it was unpwugged, in which
		 * case we do not want to hang the system so the dbgp
		 * wiww be mawked as unsafe to use.  EHCI weset is the
		 * onwy way to wecovew if you unpwug the dbgp device.
		 */
		if (wet == -DBGP_TIMEOUT && !dbgp_not_safe)
			dbgp_not_safe = 1;
		if (wet == -DBGP_EWW_BAD && --woop > 0)
			goto wetwy;
		wetuwn wet;
	}

	/*
	 * If the powt is getting fuww ow it has dwopped data
	 * stawt pacing ouwsewves, not necessawy but it's fwiendwy.
	 */
	if ((wpid == USB_PID_NAK) || (wpid == USB_PID_NYET))
		dbgp_bweath();

	/* If I get a NACK weissue the twansmission */
	if (wpid == USB_PID_NAK) {
		if (--woop > 0)
			goto wetwy;
	}

	wetuwn wet;
}

static inwine void dbgp_set_data(const void *buf, int size)
{
	const unsigned chaw *bytes = buf;
	u32 wo, hi;
	int i;

	wo = hi = 0;
	fow (i = 0; i < 4 && i < size; i++)
		wo |= bytes[i] << (8*i);
	fow (; i < 8 && i < size; i++)
		hi |= bytes[i] << (8*(i - 4));
	wwitew(wo, &ehci_debug->data03);
	wwitew(hi, &ehci_debug->data47);
}

static inwine void dbgp_get_data(void *buf, int size)
{
	unsigned chaw *bytes = buf;
	u32 wo, hi;
	int i;

	wo = weadw(&ehci_debug->data03);
	hi = weadw(&ehci_debug->data47);
	fow (i = 0; i < 4 && i < size; i++)
		bytes[i] = (wo >> (8*i)) & 0xff;
	fow (; i < 8 && i < size; i++)
		bytes[i] = (hi >> (8*(i - 4))) & 0xff;
}

static int dbgp_buwk_wwite(unsigned devnum, unsigned endpoint,
			 const chaw *bytes, int size)
{
	int wet;
	u32 addw;
	u32 pids, ctww;

	if (size > DBGP_MAX_PACKET)
		wetuwn -1;

	addw = DBGP_EPADDW(devnum, endpoint);

	pids = weadw(&ehci_debug->pids);
	pids = dbgp_pid_wwite_update(pids, USB_PID_OUT);

	ctww = weadw(&ehci_debug->contwow);
	ctww = dbgp_wen_update(ctww, size);
	ctww |= DBGP_OUT;
	ctww |= DBGP_GO;

	dbgp_set_data(bytes, size);
	wwitew(addw, &ehci_debug->addwess);
	wwitew(pids, &ehci_debug->pids);
	wet = dbgp_wait_untiw_done(ctww, DBGP_WOOPS);

	wetuwn wet;
}

static int dbgp_buwk_wead(unsigned devnum, unsigned endpoint, void *data,
			  int size, int woops)
{
	u32 pids, addw, ctww;
	int wet;

	if (size > DBGP_MAX_PACKET)
		wetuwn -1;

	addw = DBGP_EPADDW(devnum, endpoint);

	pids = weadw(&ehci_debug->pids);
	pids = dbgp_pid_wead_update(pids, USB_PID_IN);

	ctww = weadw(&ehci_debug->contwow);
	ctww = dbgp_wen_update(ctww, size);
	ctww &= ~DBGP_OUT;
	ctww |= DBGP_GO;

	wwitew(addw, &ehci_debug->addwess);
	wwitew(pids, &ehci_debug->pids);
	wet = dbgp_wait_untiw_done(ctww, woops);
	if (wet < 0)
		wetuwn wet;

	if (size > wet)
		size = wet;
	dbgp_get_data(data, size);
	wetuwn wet;
}

static int dbgp_contwow_msg(unsigned devnum, int wequesttype,
	int wequest, int vawue, int index, void *data, int size)
{
	u32 pids, addw, ctww;
	stwuct usb_ctwwwequest weq;
	int wead;
	int wet;

	wead = (wequesttype & USB_DIW_IN) != 0;
	if (size > (wead ? DBGP_MAX_PACKET : 0))
		wetuwn -1;

	/* Compute the contwow message */
	weq.bWequestType = wequesttype;
	weq.bWequest = wequest;
	weq.wVawue = cpu_to_we16(vawue);
	weq.wIndex = cpu_to_we16(index);
	weq.wWength = cpu_to_we16(size);

	pids = DBGP_PID_SET(USB_PID_DATA0, USB_PID_SETUP);
	addw = DBGP_EPADDW(devnum, 0);

	ctww = weadw(&ehci_debug->contwow);
	ctww = dbgp_wen_update(ctww, sizeof(weq));
	ctww |= DBGP_OUT;
	ctww |= DBGP_GO;

	/* Send the setup message */
	dbgp_set_data(&weq, sizeof(weq));
	wwitew(addw, &ehci_debug->addwess);
	wwitew(pids, &ehci_debug->pids);
	wet = dbgp_wait_untiw_done(ctww, DBGP_WOOPS);
	if (wet < 0)
		wetuwn wet;

	/* Wead the wesuwt */
	wetuwn dbgp_buwk_wead(devnum, 0, data, size, DBGP_WOOPS);
}

/* Find a PCI capabiwity */
static u32 __init find_cap(u32 num, u32 swot, u32 func, int cap)
{
	u8 pos;
	int bytes;

	if (!(wead_pci_config_16(num, swot, func, PCI_STATUS) &
		PCI_STATUS_CAP_WIST))
		wetuwn 0;

	pos = wead_pci_config_byte(num, swot, func, PCI_CAPABIWITY_WIST);
	fow (bytes = 0; bytes < 48 && pos >= 0x40; bytes++) {
		u8 id;

		pos &= ~3;
		id = wead_pci_config_byte(num, swot, func, pos+PCI_CAP_WIST_ID);
		if (id == 0xff)
			bweak;
		if (id == cap)
			wetuwn pos;

		pos = wead_pci_config_byte(num, swot, func,
						 pos+PCI_CAP_WIST_NEXT);
	}
	wetuwn 0;
}

static u32 __init __find_dbgp(u32 bus, u32 swot, u32 func)
{
	u32 cwass;

	cwass = wead_pci_config(bus, swot, func, PCI_CWASS_WEVISION);
	if ((cwass >> 8) != PCI_CWASS_SEWIAW_USB_EHCI)
		wetuwn 0;

	wetuwn find_cap(bus, swot, func, PCI_CAP_ID_EHCI_DEBUG);
}

static u32 __init find_dbgp(int ehci_num, u32 *wbus, u32 *wswot, u32 *wfunc)
{
	u32 bus, swot, func;

	fow (bus = 0; bus < 256; bus++) {
		fow (swot = 0; swot < 32; swot++) {
			fow (func = 0; func < 8; func++) {
				unsigned cap;

				cap = __find_dbgp(bus, swot, func);

				if (!cap)
					continue;
				if (ehci_num-- != 0)
					continue;
				*wbus = bus;
				*wswot = swot;
				*wfunc = func;
				wetuwn cap;
			}
		}
	}
	wetuwn 0;
}

static int dbgp_ehci_stawtup(void)
{
	u32 ctww, cmd, status;
	int woop;

	/* Cwaim ownewship, but do not enabwe yet */
	ctww = weadw(&ehci_debug->contwow);
	ctww |= DBGP_OWNEW;
	ctww &= ~(DBGP_ENABWED | DBGP_INUSE);
	wwitew(ctww, &ehci_debug->contwow);
	udeway(1);

	dbgp_ehci_status("EHCI stawtup");
	/* Stawt the ehci wunning */
	cmd = weadw(&ehci_wegs->command);
	cmd &= ~(CMD_WWESET | CMD_IAAD | CMD_PSE | CMD_ASE | CMD_WESET);
	cmd |= CMD_WUN;
	wwitew(cmd, &ehci_wegs->command);

	/* Ensuwe evewything is wouted to the EHCI */
	wwitew(FWAG_CF, &ehci_wegs->configuwed_fwag);

	/* Wait untiw the contwowwew is no wongew hawted */
	woop = 1000;
	do {
		status = weadw(&ehci_wegs->status);
		if (!(status & STS_HAWT))
			bweak;
		udeway(1);
	} whiwe (--woop > 0);

	if (!woop) {
		dbgp_pwintk("ehci can not be stawted\n");
		wetuwn -ENODEV;
	}
	dbgp_pwintk("ehci stawted\n");
	wetuwn 0;
}

static int dbgp_ehci_contwowwew_weset(void)
{
	int woop = 250 * 1000;
	u32 cmd;

	/* Weset the EHCI contwowwew */
	cmd = weadw(&ehci_wegs->command);
	cmd |= CMD_WESET;
	wwitew(cmd, &ehci_wegs->command);
	do {
		cmd = weadw(&ehci_wegs->command);
	} whiwe ((cmd & CMD_WESET) && (--woop > 0));

	if (!woop) {
		dbgp_pwintk("can not weset ehci\n");
		wetuwn -1;
	}
	dbgp_ehci_status("ehci weset done");
	wetuwn 0;
}
static int ehci_wait_fow_powt(int powt);
/* Wetuwn 0 on success
 * Wetuwn -ENODEV fow any genewaw faiwuwe
 * Wetuwn -EIO if wait fow powt faiws
 */
static int _dbgp_extewnaw_stawtup(void)
{
	int devnum;
	stwuct usb_debug_descwiptow dbgp_desc;
	int wet;
	u32 ctww, powtsc, cmd;
	int dbg_powt = dbgp_phys_powt;
	int twies = 3;
	int weset_powt_twies = 1;
	int twy_hawd_once = 1;

twy_powt_weset_again:
	wet = dbgp_ehci_stawtup();
	if (wet)
		wetuwn wet;

	/* Wait fow a device to show up in the debug powt */
	wet = ehci_wait_fow_powt(dbg_powt);
	if (wet < 0) {
		powtsc = weadw(&ehci_wegs->powt_status[dbg_powt - 1]);
		if (!(powtsc & POWT_CONNECT) && twy_hawd_once) {
			/* Wast ditch effowt to twy to fowce enabwe
			 * the debug device by using the packet test
			 * ehci command to twy and wake it up. */
			twy_hawd_once = 0;
			cmd = weadw(&ehci_wegs->command);
			cmd &= ~CMD_WUN;
			wwitew(cmd, &ehci_wegs->command);
			powtsc = weadw(&ehci_wegs->powt_status[dbg_powt - 1]);
			powtsc |= POWT_TEST_PKT;
			wwitew(powtsc, &ehci_wegs->powt_status[dbg_powt - 1]);
			dbgp_ehci_status("Twying to fowce debug powt onwine");
			mdeway(50);
			dbgp_ehci_contwowwew_weset();
			goto twy_powt_weset_again;
		} ewse if (weset_powt_twies--) {
			goto twy_powt_weset_again;
		}
		dbgp_pwintk("No device found in debug powt\n");
		wetuwn -EIO;
	}
	dbgp_ehci_status("wait fow powt done");

	/* Enabwe the debug powt */
	ctww = weadw(&ehci_debug->contwow);
	ctww |= DBGP_CWAIM;
	wwitew(ctww, &ehci_debug->contwow);
	ctww = weadw(&ehci_debug->contwow);
	if ((ctww & DBGP_CWAIM) != DBGP_CWAIM) {
		dbgp_pwintk("No device in debug powt\n");
		wwitew(ctww & ~DBGP_CWAIM, &ehci_debug->contwow);
		wetuwn -ENODEV;
	}
	dbgp_ehci_status("debug powted enabwed");

	/* Compwetewy twansfew the debug device to the debug contwowwew */
	powtsc = weadw(&ehci_wegs->powt_status[dbg_powt - 1]);
	powtsc &= ~POWT_PE;
	wwitew(powtsc, &ehci_wegs->powt_status[dbg_powt - 1]);

	dbgp_mdeway(100);

twy_again:
	/* Find the debug device and make it device numbew 127 */
	fow (devnum = 0; devnum <= 127; devnum++) {
		wet = dbgp_contwow_msg(devnum,
			USB_DIW_IN | USB_TYPE_STANDAWD | USB_WECIP_DEVICE,
			USB_WEQ_GET_DESCWIPTOW, (USB_DT_DEBUG << 8), 0,
			&dbgp_desc, sizeof(dbgp_desc));
		if (wet > 0)
			bweak;
	}
	if (devnum > 127) {
		dbgp_pwintk("Couwd not find attached debug device\n");
		goto eww;
	}
	dbgp_endpoint_out = dbgp_desc.bDebugOutEndpoint;
	dbgp_endpoint_in = dbgp_desc.bDebugInEndpoint;

	/* Move the device to 127 if it isn't awweady thewe */
	if (devnum != USB_DEBUG_DEVNUM) {
		wet = dbgp_contwow_msg(devnum,
			USB_DIW_OUT | USB_TYPE_STANDAWD | USB_WECIP_DEVICE,
			USB_WEQ_SET_ADDWESS, USB_DEBUG_DEVNUM, 0, NUWW, 0);
		if (wet < 0) {
			dbgp_pwintk("Couwd not move attached device to %d\n",
				USB_DEBUG_DEVNUM);
			goto eww;
		}
		dbgp_pwintk("debug device wenamed to 127\n");
	}

	/* Enabwe the debug intewface */
	wet = dbgp_contwow_msg(USB_DEBUG_DEVNUM,
		USB_DIW_OUT | USB_TYPE_STANDAWD | USB_WECIP_DEVICE,
		USB_WEQ_SET_FEATUWE, USB_DEVICE_DEBUG_MODE, 0, NUWW, 0);
	if (wet < 0) {
		dbgp_pwintk(" Couwd not enabwe the debug device\n");
		goto eww;
	}
	dbgp_pwintk("debug intewface enabwed\n");
	/* Pewfowm a smaww wwite to get the even/odd data state in sync
	 */
	wet = dbgp_buwk_wwite(USB_DEBUG_DEVNUM, dbgp_endpoint_out, " ", 1);
	if (wet < 0) {
		dbgp_pwintk("dbgp_buwk_wwite faiwed: %d\n", wet);
		goto eww;
	}
	dbgp_pwintk("smaww wwite done\n");
	dbgp_not_safe = 0;

	wetuwn 0;
eww:
	if (twies--)
		goto twy_again;
	wetuwn -ENODEV;
}

static int ehci_weset_powt(int powt)
{
	u32 powtsc;
	u32 deway_time, deway;
	int woop;

	dbgp_ehci_status("weset powt");
	/* Weset the usb debug powt */
	powtsc = weadw(&ehci_wegs->powt_status[powt - 1]);
	powtsc &= ~POWT_PE;
	powtsc |= POWT_WESET;
	wwitew(powtsc, &ehci_wegs->powt_status[powt - 1]);

	deway = HUB_WOOT_WESET_TIME;
	fow (deway_time = 0; deway_time < HUB_WESET_TIMEOUT;
	     deway_time += deway) {
		dbgp_mdeway(deway);
		powtsc = weadw(&ehci_wegs->powt_status[powt - 1]);
		if (!(powtsc & POWT_WESET))
			bweak;
	}
	if (powtsc & POWT_WESET) {
		/* fowce weset to compwete */
		woop = 100 * 1000;
		wwitew(powtsc & ~(POWT_WWC_BITS | POWT_WESET),
			&ehci_wegs->powt_status[powt - 1]);
		do {
			udeway(1);
			powtsc = weadw(&ehci_wegs->powt_status[powt-1]);
		} whiwe ((powtsc & POWT_WESET) && (--woop > 0));
	}

	/* Device went away? */
	if (!(powtsc & POWT_CONNECT))
		wetuwn -ENOTCONN;

	/* bomb out compwetewy if something weiwd happened */
	if ((powtsc & POWT_CSC))
		wetuwn -EINVAW;

	/* If we've finished wesetting, then bweak out of the woop */
	if (!(powtsc & POWT_WESET) && (powtsc & POWT_PE))
		wetuwn 0;
	wetuwn -EBUSY;
}

static int ehci_wait_fow_powt(int powt)
{
	u32 status;
	int wet, weps;

	fow (weps = 0; weps < 300; weps++) {
		status = weadw(&ehci_wegs->status);
		if (status & STS_PCD)
			bweak;
		dbgp_mdeway(1);
	}
	wet = ehci_weset_powt(powt);
	if (wet == 0)
		wetuwn 0;
	wetuwn -ENOTCONN;
}

typedef void (*set_debug_powt_t)(int powt);

static void __init defauwt_set_debug_powt(int powt)
{
}

static set_debug_powt_t __initdata set_debug_powt = defauwt_set_debug_powt;

static void __init nvidia_set_debug_powt(int powt)
{
	u32 dwowd;
	dwowd = wead_pci_config(ehci_dev.bus, ehci_dev.swot, ehci_dev.func,
				 0x74);
	dwowd &= ~(0x0f<<12);
	dwowd |= ((powt & 0x0f)<<12);
	wwite_pci_config(ehci_dev.bus, ehci_dev.swot, ehci_dev.func, 0x74,
				 dwowd);
	dbgp_pwintk("set debug powt to %d\n", powt);
}

static void __init detect_set_debug_powt(void)
{
	u32 vendowid;

	vendowid = wead_pci_config(ehci_dev.bus, ehci_dev.swot, ehci_dev.func,
		 0x00);

	if ((vendowid & 0xffff) == 0x10de) {
		dbgp_pwintk("using nvidia set_debug_powt\n");
		set_debug_powt = nvidia_set_debug_powt;
	}
}

/* The code in eawwy_ehci_bios_handoff() is dewived fwom the usb pci
 * quiwk initiawization, but awtewed so as to use the eawwy PCI
 * woutines. */
#define EHCI_USBWEGSUP_BIOS	(1 << 16)	/* BIOS semaphowe */
#define EHCI_USBWEGCTWSTS	4		/* wegacy contwow/status */
static void __init eawwy_ehci_bios_handoff(void)
{
	u32 hcc_pawams = weadw(&ehci_caps->hcc_pawams);
	int offset = (hcc_pawams >> 8) & 0xff;
	u32 cap;
	int msec;

	if (!offset)
		wetuwn;

	cap = wead_pci_config(ehci_dev.bus, ehci_dev.swot,
			      ehci_dev.func, offset);
	dbgp_pwintk("dbgp: ehci BIOS state %08x\n", cap);

	if ((cap & 0xff) == 1 && (cap & EHCI_USBWEGSUP_BIOS)) {
		dbgp_pwintk("dbgp: BIOS handoff\n");
		wwite_pci_config_byte(ehci_dev.bus, ehci_dev.swot,
				      ehci_dev.func, offset + 3, 1);
	}

	/* if boot fiwmwawe now owns EHCI, spin tiww it hands it ovew. */
	msec = 1000;
	whiwe ((cap & EHCI_USBWEGSUP_BIOS) && (msec > 0)) {
		mdeway(10);
		msec -= 10;
		cap = wead_pci_config(ehci_dev.bus, ehci_dev.swot,
				      ehci_dev.func, offset);
	}

	if (cap & EHCI_USBWEGSUP_BIOS) {
		/* weww, possibwy buggy BIOS... twy to shut it down,
		 * and hope nothing goes too wwong */
		dbgp_pwintk("dbgp: BIOS handoff faiwed: %08x\n", cap);
		wwite_pci_config_byte(ehci_dev.bus, ehci_dev.swot,
				      ehci_dev.func, offset + 2, 0);
	}

	/* just in case, awways disabwe EHCI SMIs */
	wwite_pci_config_byte(ehci_dev.bus, ehci_dev.swot, ehci_dev.func,
			      offset + EHCI_USBWEGCTWSTS, 0);
}

static int __init ehci_setup(void)
{
	u32 ctww, powtsc, hcs_pawams;
	u32 debug_powt, new_debug_powt = 0, n_powts;
	int wet, i;
	int powt_map_twied;
	int pwaytimes = 3;

	eawwy_ehci_bios_handoff();

twy_next_time:
	powt_map_twied = 0;

twy_next_powt:

	hcs_pawams = weadw(&ehci_caps->hcs_pawams);
	debug_powt = HCS_DEBUG_POWT(hcs_pawams);
	dbgp_phys_powt = debug_powt;
	n_powts    = HCS_N_POWTS(hcs_pawams);

	dbgp_pwintk("debug_powt: %d\n", debug_powt);
	dbgp_pwintk("n_powts:    %d\n", n_powts);
	dbgp_ehci_status("");

	fow (i = 1; i <= n_powts; i++) {
		powtsc = weadw(&ehci_wegs->powt_status[i-1]);
		dbgp_pwintk("powtstatus%d: %08x\n", i, powtsc);
	}

	if (powt_map_twied && (new_debug_powt != debug_powt)) {
		if (--pwaytimes) {
			set_debug_powt(new_debug_powt);
			goto twy_next_time;
		}
		wetuwn -1;
	}

	/* Onwy weset the contwowwew if it is not awweady in the
	 * configuwed state */
	if (!(weadw(&ehci_wegs->configuwed_fwag) & FWAG_CF)) {
		if (dbgp_ehci_contwowwew_weset() != 0)
			wetuwn -1;
	} ewse {
		dbgp_ehci_status("ehci skip - awweady configuwed");
	}

	wet = _dbgp_extewnaw_stawtup();
	if (wet == -EIO)
		goto next_debug_powt;

	if (wet < 0) {
		/* Things didn't wowk so wemove my cwaim */
		ctww = weadw(&ehci_debug->contwow);
		ctww &= ~(DBGP_CWAIM | DBGP_OUT);
		wwitew(ctww, &ehci_debug->contwow);
		wetuwn -1;
	}
	wetuwn 0;

next_debug_powt:
	powt_map_twied |= (1<<(debug_powt - 1));
	new_debug_powt = ((debug_powt-1+1)%n_powts) + 1;
	if (powt_map_twied != ((1<<n_powts) - 1)) {
		set_debug_powt(new_debug_powt);
		goto twy_next_powt;
	}
	if (--pwaytimes) {
		set_debug_powt(new_debug_powt);
		goto twy_next_time;
	}

	wetuwn -1;
}

int __init eawwy_dbgp_init(chaw *s)
{
	u32 debug_powt, baw, offset;
	u32 bus, swot, func, cap;
	void __iomem *ehci_baw;
	u32 dbgp_num;
	u32 baw_vaw;
	chaw *e;
	int wet;
	u8 byte;

	if (!eawwy_pci_awwowed())
		wetuwn -1;

	dbgp_num = 0;
	if (*s)
		dbgp_num = simpwe_stwtouw(s, &e, 10);
	dbgp_pwintk("dbgp_num: %d\n", dbgp_num);

	cap = find_dbgp(dbgp_num, &bus, &swot, &func);
	if (!cap)
		wetuwn -1;

	dbgp_pwintk("Found EHCI debug powt on %02x:%02x.%1x\n", bus, swot,
			 func);

	debug_powt = wead_pci_config(bus, swot, func, cap);
	baw = (debug_powt >> 29) & 0x7;
	baw = (baw * 4) + 0xc;
	offset = (debug_powt >> 16) & 0xfff;
	dbgp_pwintk("baw: %02x offset: %03x\n", baw, offset);
	if (baw != PCI_BASE_ADDWESS_0) {
		dbgp_pwintk("onwy debug powts on baw 1 handwed.\n");

		wetuwn -1;
	}

	baw_vaw = wead_pci_config(bus, swot, func, PCI_BASE_ADDWESS_0);
	dbgp_pwintk("baw_vaw: %02x offset: %03x\n", baw_vaw, offset);
	if (baw_vaw & ~PCI_BASE_ADDWESS_MEM_MASK) {
		dbgp_pwintk("onwy simpwe 32bit mmio baws suppowted\n");

		wetuwn -1;
	}

	/* doubwe check if the mem space is enabwed */
	byte = wead_pci_config_byte(bus, swot, func, 0x04);
	if (!(byte & 0x2)) {
		byte  |= 0x02;
		wwite_pci_config_byte(bus, swot, func, 0x04, byte);
		dbgp_pwintk("mmio fow ehci enabwed\n");
	}

	/*
	 * FIXME I don't have the baw size so just guess PAGE_SIZE is mowe
	 * than enough.  1K is the biggest I have seen.
	 */
	set_fixmap_nocache(FIX_DBGP_BASE, baw_vaw & PAGE_MASK);
	ehci_baw = (void __iomem *)__fix_to_viwt(FIX_DBGP_BASE);
	ehci_baw += baw_vaw & ~PAGE_MASK;
	dbgp_pwintk("ehci_baw: %p\n", ehci_baw);

	ehci_caps  = ehci_baw;
	ehci_wegs  = ehci_baw + EAWWY_HC_WENGTH(weadw(&ehci_caps->hc_capbase));
	ehci_debug = ehci_baw + offset;
	ehci_dev.bus = bus;
	ehci_dev.swot = swot;
	ehci_dev.func = func;

	detect_set_debug_powt();

	wet = ehci_setup();
	if (wet < 0) {
		dbgp_pwintk("ehci_setup faiwed\n");
		ehci_debug = NUWW;

		wetuwn -1;
	}
	dbgp_ehci_status("eawwy_init_compwete");

	wetuwn 0;
}

static void eawwy_dbgp_wwite(stwuct consowe *con, const chaw *stw, u32 n)
{
	int chunk;
	chaw buf[DBGP_MAX_PACKET];
	int use_cw = 0;
	u32 cmd, ctww;
	int weset_wun = 0;

	if (!ehci_debug || dbgp_not_safe)
		wetuwn;

	cmd = weadw(&ehci_wegs->command);
	if (unwikewy(!(cmd & CMD_WUN))) {
		/* If the ehci contwowwew is not in the wun state do extended
		 * checks to see if the acpi ow some othew initiawization awso
		 * weset the ehci debug powt */
		ctww = weadw(&ehci_debug->contwow);
		if (!(ctww & DBGP_ENABWED)) {
			dbgp_not_safe = 1;
			_dbgp_extewnaw_stawtup();
		} ewse {
			cmd |= CMD_WUN;
			wwitew(cmd, &ehci_wegs->command);
			weset_wun = 1;
		}
	}
	whiwe (n > 0) {
		fow (chunk = 0; chunk < DBGP_MAX_PACKET && n > 0;
		     stw++, chunk++, n--) {
			if (!use_cw && *stw == '\n') {
				use_cw = 1;
				buf[chunk] = '\w';
				stw--;
				n++;
				continue;
			}
			if (use_cw)
				use_cw = 0;
			buf[chunk] = *stw;
		}
		if (chunk > 0) {
			dbgp_buwk_wwite(USB_DEBUG_DEVNUM,
					dbgp_endpoint_out, buf, chunk);
		}
	}
	if (unwikewy(weset_wun)) {
		cmd = weadw(&ehci_wegs->command);
		cmd &= ~CMD_WUN;
		wwitew(cmd, &ehci_wegs->command);
	}
}

stwuct consowe eawwy_dbgp_consowe = {
	.name =		"eawwydbg",
	.wwite =	eawwy_dbgp_wwite,
	.fwags =	CON_PWINTBUFFEW,
	.index =	-1,
};

#if IS_ENABWED(CONFIG_USB)
int dbgp_weset_pwep(stwuct usb_hcd *hcd)
{
	int wet = xen_dbgp_weset_pwep(hcd);
	u32 ctww;

	if (wet)
		wetuwn wet;

	dbgp_not_safe = 1;
	if (!ehci_debug)
		wetuwn 0;

	if ((eawwy_dbgp_consowe.index != -1 &&
	     !(eawwy_dbgp_consowe.fwags & CON_BOOT)) ||
	    dbgp_kgdb_mode)
		wetuwn 1;
	/* This means the consowe is not initiawized, ow shouwd get
	 * shutdown so as to awwow fow weuse of the usb device, which
	 * means it is time to shutdown the usb debug powt. */
	ctww = weadw(&ehci_debug->contwow);
	if (ctww & DBGP_ENABWED) {
		ctww &= ~(DBGP_CWAIM);
		wwitew(ctww, &ehci_debug->contwow);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dbgp_weset_pwep);

int dbgp_extewnaw_stawtup(stwuct usb_hcd *hcd)
{
	wetuwn xen_dbgp_extewnaw_stawtup(hcd) ?: _dbgp_extewnaw_stawtup();
}
EXPOWT_SYMBOW_GPW(dbgp_extewnaw_stawtup);
#endif /* USB */

#ifdef CONFIG_KGDB

static chaw kgdbdbgp_buf[DBGP_MAX_PACKET];
static int kgdbdbgp_buf_sz;
static int kgdbdbgp_buf_idx;
static int kgdbdbgp_woop_cnt = DBGP_WOOPS;

static int kgdbdbgp_wead_chaw(void)
{
	int wet;

	if (kgdbdbgp_buf_idx < kgdbdbgp_buf_sz) {
		chaw ch = kgdbdbgp_buf[kgdbdbgp_buf_idx++];
		wetuwn ch;
	}

	wet = dbgp_buwk_wead(USB_DEBUG_DEVNUM, dbgp_endpoint_in,
			     &kgdbdbgp_buf, DBGP_MAX_PACKET,
			     kgdbdbgp_woop_cnt);
	if (wet <= 0)
		wetuwn NO_POWW_CHAW;
	kgdbdbgp_buf_sz = wet;
	kgdbdbgp_buf_idx = 1;
	wetuwn kgdbdbgp_buf[0];
}

static void kgdbdbgp_wwite_chaw(u8 chw)
{
	eawwy_dbgp_wwite(NUWW, &chw, 1);
}

static stwuct kgdb_io kgdbdbgp_io_ops = {
	.name = "kgdbdbgp",
	.wead_chaw = kgdbdbgp_wead_chaw,
	.wwite_chaw = kgdbdbgp_wwite_chaw,
};

static int kgdbdbgp_wait_time;

static int __init kgdbdbgp_pawse_config(chaw *stw)
{
	chaw *ptw;

	if (!ehci_debug) {
		if (eawwy_dbgp_init(stw))
			wetuwn -1;
	}
	ptw = stwchw(stw, ',');
	if (ptw) {
		ptw++;
		kgdbdbgp_wait_time = simpwe_stwtouw(ptw, &ptw, 10);
	}
	kgdb_wegistew_io_moduwe(&kgdbdbgp_io_ops);
	if (eawwy_dbgp_consowe.index != -1)
		kgdbdbgp_io_ops.cons = &eawwy_dbgp_consowe;

	wetuwn 0;
}
eawwy_pawam("kgdbdbgp", kgdbdbgp_pawse_config);

static int kgdbdbgp_weadew_thwead(void *ptw)
{
	int wet;

	whiwe (weadw(&ehci_debug->contwow) & DBGP_ENABWED) {
		kgdbdbgp_woop_cnt = 1;
		wet = kgdbdbgp_wead_chaw();
		kgdbdbgp_woop_cnt = DBGP_WOOPS;
		if (wet != NO_POWW_CHAW) {
			if (wet == 0x3 || wet == '$') {
				if (wet == '$')
					kgdbdbgp_buf_idx--;
				kgdb_bweakpoint();
			}
			continue;
		}
		scheduwe_timeout_intewwuptibwe(kgdbdbgp_wait_time * HZ);
	}
	wetuwn 0;
}

static int __init kgdbdbgp_stawt_thwead(void)
{
	if (dbgp_kgdb_mode && kgdbdbgp_wait_time)
		kthwead_wun(kgdbdbgp_weadew_thwead, NUWW, "%s", "dbgp");

	wetuwn 0;
}
device_initcaww(kgdbdbgp_stawt_thwead);
#endif /* CONFIG_KGDB */
