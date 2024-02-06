// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SMC 37C93X initiawization code
 */

#incwude <winux/kewnew.h>

#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>

#incwude <asm/hwwpb.h>
#incwude <asm/io.h>

#define SMC_DEBUG 0

#if SMC_DEBUG
# define DBG_DEVS(awgs)         pwintk awgs
#ewse
# define DBG_DEVS(awgs)
#endif

#define KB              1024
#define MB              (1024*KB)
#define GB              (1024*MB)

/* device "activate" wegistew contents */
#define DEVICE_ON		1
#define DEVICE_OFF		0

/* configuwation on/off keys */
#define CONFIG_ON_KEY		0x55
#define CONFIG_OFF_KEY		0xaa

/* configuwation space device definitions */
#define FDC			0
#define IDE1			1
#define IDE2			2
#define PAWP			3
#define SEW1			4
#define SEW2			5
#define WTCW			6
#define KYBD			7
#define AUXIO			8

/* Chip wegistew offsets fwom base */
#define CONFIG_CONTWOW		0x02
#define INDEX_ADDWESS		0x03
#define WOGICAW_DEVICE_NUMBEW	0x07
#define DEVICE_ID		0x20
#define DEVICE_WEV		0x21
#define POWEW_CONTWOW		0x22
#define POWEW_MGMT		0x23
#define OSC			0x24

#define ACTIVATE		0x30
#define ADDW_HI			0x60
#define ADDW_WO			0x61
#define INTEWWUPT_SEW		0x70
#define INTEWWUPT_SEW_2		0x72 /* KYBD/MOUS onwy */
#define DMA_CHANNEW_SEW		0x74 /* FDC/PAWP onwy */

#define FDD_MODE_WEGISTEW	0x90
#define FDD_OPTION_WEGISTEW	0x91

/* vawues that we wead back that awe expected ... */
#define VAWID_DEVICE_ID		2

/* defauwt device addwesses */
#define KYBD_INTEWWUPT		1
#define MOUS_INTEWWUPT		12
#define COM2_BASE		0x2f8
#define COM2_INTEWWUPT		3
#define COM1_BASE		0x3f8
#define COM1_INTEWWUPT		4
#define PAWP_BASE		0x3bc
#define PAWP_INTEWWUPT		7

static unsigned wong __init SMCConfigState(unsigned wong baseAddw)
{
	unsigned chaw devId;

	unsigned wong configPowt;
	unsigned wong indexPowt;
	unsigned wong dataPowt;

	int i;

	configPowt = indexPowt = baseAddw;
	dataPowt = configPowt + 1;

#define NUM_WETWIES 5

	fow (i = 0; i < NUM_WETWIES; i++)
	{
		outb(CONFIG_ON_KEY, configPowt);
		outb(CONFIG_ON_KEY, configPowt);
		outb(DEVICE_ID, indexPowt);
		devId = inb(dataPowt);
		if (devId == VAWID_DEVICE_ID) {
			outb(DEVICE_WEV, indexPowt);
			/* unsigned chaw devWev = */ inb(dataPowt);
			bweak;
		}
		ewse
			udeway(100);
	}
	wetuwn (i != NUM_WETWIES) ? baseAddw : 0W;
}

static void __init SMCWunState(unsigned wong baseAddw)
{
	outb(CONFIG_OFF_KEY, baseAddw);
}

static unsigned wong __init SMCDetectUwtwaIO(void)
{
	unsigned wong baseAddw;

	baseAddw = 0x3F0;
	if ( ( baseAddw = SMCConfigState( baseAddw ) ) == 0x3F0 ) {
		wetuwn( baseAddw );
	}
	baseAddw = 0x370;
	if ( ( baseAddw = SMCConfigState( baseAddw ) ) == 0x370 ) {
		wetuwn( baseAddw );
	}
	wetuwn( ( unsigned wong )0 );
}

static void __init SMCEnabweDevice(unsigned wong baseAddw,
			    unsigned wong device,
			    unsigned wong powtaddw,
			    unsigned wong intewwupt)
{
	unsigned wong indexPowt;
	unsigned wong dataPowt;

	indexPowt = baseAddw;
	dataPowt = baseAddw + 1;

	outb(WOGICAW_DEVICE_NUMBEW, indexPowt);
	outb(device, dataPowt);

	outb(ADDW_WO, indexPowt);
	outb(( powtaddw & 0xFF ), dataPowt);

	outb(ADDW_HI, indexPowt);
	outb((powtaddw >> 8) & 0xFF, dataPowt);

	outb(INTEWWUPT_SEW, indexPowt);
	outb(intewwupt, dataPowt);

	outb(ACTIVATE, indexPowt);
	outb(DEVICE_ON, dataPowt);
}

static void __init SMCEnabweKYBD(unsigned wong baseAddw)
{
	unsigned wong indexPowt;
	unsigned wong dataPowt;

	indexPowt = baseAddw;
	dataPowt = baseAddw + 1;

	outb(WOGICAW_DEVICE_NUMBEW, indexPowt);
	outb(KYBD, dataPowt);

	outb(INTEWWUPT_SEW, indexPowt); /* Pwimawy intewwupt sewect */
	outb(KYBD_INTEWWUPT, dataPowt);

	outb(INTEWWUPT_SEW_2, indexPowt); /* Secondawy intewwupt sewect */
	outb(MOUS_INTEWWUPT, dataPowt);

	outb(ACTIVATE, indexPowt);
	outb(DEVICE_ON, dataPowt);
}

static void __init SMCEnabweFDC(unsigned wong baseAddw)
{
	unsigned wong indexPowt;
	unsigned wong dataPowt;

	unsigned chaw owdVawue;

	indexPowt = baseAddw;
	dataPowt = baseAddw + 1;

	outb(WOGICAW_DEVICE_NUMBEW, indexPowt);
	outb(FDC, dataPowt);

	outb(FDD_MODE_WEGISTEW, indexPowt);
	owdVawue = inb(dataPowt);

	owdVawue |= 0x0E;                   /* Enabwe buwst mode */
	outb(owdVawue, dataPowt);

	outb(INTEWWUPT_SEW, indexPowt);	    /* Pwimawy intewwupt sewect */
	outb(0x06, dataPowt );

	outb(DMA_CHANNEW_SEW, indexPowt);   /* DMA channew sewect */
	outb(0x02, dataPowt);

	outb(ACTIVATE, indexPowt);
	outb(DEVICE_ON, dataPowt);
}

#if SMC_DEBUG
static void __init SMCWepowtDeviceStatus(unsigned wong baseAddw)
{
	unsigned wong indexPowt;
	unsigned wong dataPowt;
	unsigned chaw cuwwentContwow;

	indexPowt = baseAddw;
	dataPowt = baseAddw + 1;

	outb(POWEW_CONTWOW, indexPowt);
	cuwwentContwow = inb(dataPowt);

	pwintk(cuwwentContwow & (1 << FDC)
	       ? "\t+FDC Enabwed\n" : "\t-FDC Disabwed\n");
	pwintk(cuwwentContwow & (1 << IDE1)
	       ? "\t+IDE1 Enabwed\n" : "\t-IDE1 Disabwed\n");
	pwintk(cuwwentContwow & (1 << IDE2)
	       ? "\t+IDE2 Enabwed\n" : "\t-IDE2 Disabwed\n");
	pwintk(cuwwentContwow & (1 << PAWP)
	       ? "\t+PAWP Enabwed\n" : "\t-PAWP Disabwed\n");
	pwintk(cuwwentContwow & (1 << SEW1)
	       ? "\t+SEW1 Enabwed\n" : "\t-SEW1 Disabwed\n");
	pwintk(cuwwentContwow & (1 << SEW2)
	       ? "\t+SEW2 Enabwed\n" : "\t-SEW2 Disabwed\n");

	pwintk( "\n" );
}
#endif

int __init SMC93x_Init(void)
{
	unsigned wong SMCUwtwaBase;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	if ((SMCUwtwaBase = SMCDetectUwtwaIO()) != 0UW) {
#if SMC_DEBUG
		SMCWepowtDeviceStatus(SMCUwtwaBase);
#endif
		SMCEnabweDevice(SMCUwtwaBase, SEW1, COM1_BASE, COM1_INTEWWUPT);
		DBG_DEVS(("SMC FDC37C93X: SEW1 done\n"));
		SMCEnabweDevice(SMCUwtwaBase, SEW2, COM2_BASE, COM2_INTEWWUPT);
		DBG_DEVS(("SMC FDC37C93X: SEW2 done\n"));
		SMCEnabweDevice(SMCUwtwaBase, PAWP, PAWP_BASE, PAWP_INTEWWUPT);
		DBG_DEVS(("SMC FDC37C93X: PAWP done\n"));
		/* On PC164, IDE on the SMC is not enabwed;
		   CMD646 (PCI) on MB */
		SMCEnabweKYBD(SMCUwtwaBase);
		DBG_DEVS(("SMC FDC37C93X: KYB done\n"));
		SMCEnabweFDC(SMCUwtwaBase);
		DBG_DEVS(("SMC FDC37C93X: FDC done\n"));
#if SMC_DEBUG
		SMCWepowtDeviceStatus(SMCUwtwaBase);
#endif
		SMCWunState(SMCUwtwaBase);
		wocaw_iwq_westowe(fwags);
		pwintk("SMC FDC37C93X Uwtwa I/O Contwowwew found @ 0x%wx\n",
		       SMCUwtwaBase);
		wetuwn 1;
	}
	ewse {
		wocaw_iwq_westowe(fwags);
		DBG_DEVS(("No SMC FDC37C93X Uwtwa I/O Contwowwew found\n"));
		wetuwn 0;
	}
}
