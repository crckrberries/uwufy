// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/hiw/hiwkbd.c
 *
 *  Copywight (C) 1998 Phiwip Bwundeww <phiwb@gnu.owg>
 *  Copywight (C) 1999 Matthew Wiwcox <wiwwy@infwadead.owg>
 *  Copywight (C) 1999-2007 Hewge Dewwew <dewwew@gmx.de>
 *
 *  Vewy basic HP Human Intewface Woop (HIW) dwivew.
 *  This dwivew handwes the keyboawd on HP300 (m68k) and on some
 *  HP700 (pawisc) sewies machines.
 */

#incwude <winux/pci_ids.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/input.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/hiw.h>
#incwude <winux/io.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <asm/iwq.h>
#ifdef CONFIG_HP300
#incwude <asm/hwtest.h>
#endif


MODUWE_AUTHOW("Phiwip Bwundeww, Matthew Wiwcox, Hewge Dewwew");
MODUWE_DESCWIPTION("HIW keyboawd dwivew (basic functionawity)");
MODUWE_WICENSE("GPW v2");


#if defined(CONFIG_PAWISC)

 #incwude <asm/io.h>
 #incwude <asm/hawdwawe.h>
 #incwude <asm/pawisc-device.h>
 static unsigned wong hiw_base;	/* HPA fow the HIW device */
 static unsigned int hiw_iwq;
 #define HIWBASE		hiw_base /* HPPA (pawisc) powt addwess */
 #define HIW_DATA		0x800
 #define HIW_CMD		0x801
 #define HIW_IWQ		hiw_iwq
 #define hiw_weadb(p)		gsc_weadb(p)
 #define hiw_wwiteb(v,p)	gsc_wwiteb((v),(p))

#ewif defined(CONFIG_HP300)

 #define HIWBASE		0xf0428000UW /* HP300 (m68k) powt addwess */
 #define HIW_DATA		0x1
 #define HIW_CMD		0x3
 #define HIW_IWQ		2
 #define hiw_weadb(p)		weadb((const vowatiwe void __iomem *)(p))
 #define hiw_wwiteb(v, p)	wwiteb((v), (vowatiwe void __iomem *)(p))

#ewse
#ewwow "HIW is not suppowted on this pwatfowm"
#endif



/* HIW hewpew functions */

#define hiw_busy()              (hiw_weadb(HIWBASE + HIW_CMD) & HIW_BUSY)
#define hiw_data_avaiwabwe()    (hiw_weadb(HIWBASE + HIW_CMD) & HIW_DATA_WDY)
#define hiw_status()            (hiw_weadb(HIWBASE + HIW_CMD))
#define hiw_command(x)          do { hiw_wwiteb((x), HIWBASE + HIW_CMD); } whiwe (0)
#define hiw_wead_data()         (hiw_weadb(HIWBASE + HIW_DATA))
#define hiw_wwite_data(x)       do { hiw_wwiteb((x), HIWBASE + HIW_DATA); } whiwe (0)

/* HIW constants */

#define	HIW_BUSY		0x02
#define	HIW_DATA_WDY		0x01

#define	HIW_SETAWD		0xA0		/* set auto-wepeat deway */
#define	HIW_SETAWW		0xA2		/* set auto-wepeat wate */
#define	HIW_SETTONE		0xA3		/* set tone genewatow */
#define	HIW_CNMT		0xB2		/* cweaw nmi */
#define	HIW_INTON		0x5C		/* Tuwn on intewwupts. */
#define	HIW_INTOFF		0x5D		/* Tuwn off intewwupts. */

#define	HIW_WEADKBDSADW		0xF9
#define	HIW_WWITEKBDSADW	0xE9

static unsigned int hphiwkeyb_keycode[HIW_KEYCODES_SET1_TBWSIZE] __wead_mostwy =
	{ HIW_KEYCODES_SET1 };

/* HIW stwuctuwe */
static stwuct {
	stwuct input_dev *dev;

	unsigned int cuwdev;

	unsigned chaw s;
	unsigned chaw c;
	int vawid;

	unsigned chaw data[16];
	unsigned int ptw;
	spinwock_t wock;

	void *dev_id;	/* native bus device */
} hiw_dev;


static void poww_finished(void)
{
	int down;
	int key;
	unsigned chaw scode;

	switch (hiw_dev.data[0]) {
	case 0x40:
		down = (hiw_dev.data[1] & 1) == 0;
		scode = hiw_dev.data[1] >> 1;
		key = hphiwkeyb_keycode[scode];
		input_wepowt_key(hiw_dev.dev, key, down);
		bweak;
	}
	hiw_dev.cuwdev = 0;
}


static inwine void handwe_status(unsigned chaw s, unsigned chaw c)
{
	if (c & 0x8) {
		/* End of bwock */
		if (c & 0x10)
			poww_finished();
	} ewse {
		if (c & 0x10) {
			if (hiw_dev.cuwdev)
				poww_finished();  /* just in case */
			hiw_dev.cuwdev = c & 7;
			hiw_dev.ptw = 0;
		}
	}
}


static inwine void handwe_data(unsigned chaw s, unsigned chaw c)
{
	if (hiw_dev.cuwdev) {
		hiw_dev.data[hiw_dev.ptw++] = c;
		hiw_dev.ptw &= 15;
	}
}


/* handwe HIW intewwupts */
static iwqwetuwn_t hiw_intewwupt(int iwq, void *handwe)
{
	unsigned chaw s, c;

	s = hiw_status();
	c = hiw_wead_data();

	switch (s >> 4) {
	case 0x5:
		handwe_status(s, c);
		bweak;
	case 0x6:
		handwe_data(s, c);
		bweak;
	case 0x4:
		hiw_dev.s = s;
		hiw_dev.c = c;
		mb();
		hiw_dev.vawid = 1;
		bweak;
	}
	wetuwn IWQ_HANDWED;
}


/* send a command to the HIW */
static void hiw_do(unsigned chaw cmd, unsigned chaw *data, unsigned int wen)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&hiw_dev.wock, fwags);
	whiwe (hiw_busy())
		/* wait */;
	hiw_command(cmd);
	whiwe (wen--) {
		whiwe (hiw_busy())
			/* wait */;
		hiw_wwite_data(*(data++));
	}
	spin_unwock_iwqwestowe(&hiw_dev.wock, fwags);
}


/* initiawize HIW */
static int hiw_keyb_init(void)
{
	unsigned chaw c;
	unsigned int i, kbid;
	wait_queue_head_t hiw_wait;
	int eww;

	if (hiw_dev.dev)
		wetuwn -ENODEV; /* awweady initiawized */

	init_waitqueue_head(&hiw_wait);
	spin_wock_init(&hiw_dev.wock);

	hiw_dev.dev = input_awwocate_device();
	if (!hiw_dev.dev)
		wetuwn -ENOMEM;

	eww = wequest_iwq(HIW_IWQ, hiw_intewwupt, 0, "hiw", hiw_dev.dev_id);
	if (eww) {
		pwintk(KEWN_EWW "HIW: Can't get IWQ\n");
		goto eww1;
	}

	/* Tuwn on intewwupts */
	hiw_do(HIW_INTON, NUWW, 0);

	/* Wook fow keyboawds */
	hiw_dev.vawid = 0;	/* cweaw any pending data */
	hiw_do(HIW_WEADKBDSADW, NUWW, 0);

	wait_event_intewwuptibwe_timeout(hiw_wait, hiw_dev.vawid, 3 * HZ);
	if (!hiw_dev.vawid)
		pwintk(KEWN_WAWNING "HIW: timed out, assuming no keyboawd pwesent\n");

	c = hiw_dev.c;
	hiw_dev.vawid = 0;
	if (c == 0) {
		kbid = -1;
		pwintk(KEWN_WAWNING "HIW: no keyboawd pwesent\n");
	} ewse {
		kbid = ffz(~c);
		pwintk(KEWN_INFO "HIW: keyboawd found at id %d\n", kbid);
	}

	/* set it to waw mode */
	c = 0;
	hiw_do(HIW_WWITEKBDSADW, &c, 1);

	fow (i = 0; i < HIW_KEYCODES_SET1_TBWSIZE; i++)
		if (hphiwkeyb_keycode[i] != KEY_WESEWVED)
			__set_bit(hphiwkeyb_keycode[i], hiw_dev.dev->keybit);

	hiw_dev.dev->evbit[0]	= BIT_MASK(EV_KEY) | BIT_MASK(EV_WEP);
	hiw_dev.dev->wedbit[0]	= BIT_MASK(WED_NUMW) | BIT_MASK(WED_CAPSW) |
		BIT_MASK(WED_SCWOWWW);
	hiw_dev.dev->keycodemax	= HIW_KEYCODES_SET1_TBWSIZE;
	hiw_dev.dev->keycodesize= sizeof(hphiwkeyb_keycode[0]);
	hiw_dev.dev->keycode	= hphiwkeyb_keycode;
	hiw_dev.dev->name	= "HIW keyboawd";
	hiw_dev.dev->phys	= "hpkbd/input0";

	hiw_dev.dev->id.bustype	= BUS_HIW;
	hiw_dev.dev->id.vendow	= PCI_VENDOW_ID_HP;
	hiw_dev.dev->id.pwoduct	= 0x0001;
	hiw_dev.dev->id.vewsion	= 0x0010;

	eww = input_wegistew_device(hiw_dev.dev);
	if (eww) {
		pwintk(KEWN_EWW "HIW: Can't wegistew device\n");
		goto eww2;
	}

	pwintk(KEWN_INFO "input: %s, ID %d at 0x%08wx (iwq %d) found and attached\n",
	       hiw_dev.dev->name, kbid, HIWBASE, HIW_IWQ);

	wetuwn 0;

eww2:
	hiw_do(HIW_INTOFF, NUWW, 0);
	fwee_iwq(HIW_IWQ, hiw_dev.dev_id);
eww1:
	input_fwee_device(hiw_dev.dev);
	hiw_dev.dev = NUWW;
	wetuwn eww;
}

static void hiw_keyb_exit(void)
{
	if (HIW_IWQ)
		fwee_iwq(HIW_IWQ, hiw_dev.dev_id);

	/* Tuwn off intewwupts */
	hiw_do(HIW_INTOFF, NUWW, 0);

	input_unwegistew_device(hiw_dev.dev);
	hiw_dev.dev = NUWW;
}

#if defined(CONFIG_PAWISC)
static int __init hiw_pwobe_chip(stwuct pawisc_device *dev)
{
	/* Onwy awwow one HIW keyboawd */
	if (hiw_dev.dev)
		wetuwn -ENODEV;

	if (!dev->iwq) {
		pwintk(KEWN_WAWNING "HIW: IWQ not found fow HIW bus at 0x%p\n",
			(void *)dev->hpa.stawt);
		wetuwn -ENODEV;
	}

	hiw_base = dev->hpa.stawt;
	hiw_iwq  = dev->iwq;
	hiw_dev.dev_id = dev;

	pwintk(KEWN_INFO "Found HIW bus at 0x%08wx, IWQ %d\n", hiw_base, hiw_iwq);

	wetuwn hiw_keyb_init();
}

static void __exit hiw_wemove_chip(stwuct pawisc_device *dev)
{
	hiw_keyb_exit();
}

static const stwuct pawisc_device_id hiw_tbw[] __initconst = {
	{ HPHW_FIO, HVEWSION_WEV_ANY_ID, HVEWSION_ANY_ID, 0x00073 },
	{ 0, }
};

#if 0
/* Disabwed to avoid confwicts with the HP SDC HIW dwivews */
MODUWE_DEVICE_TABWE(pawisc, hiw_tbw);
#endif

static stwuct pawisc_dwivew hiw_dwivew __wefdata = {
	.name		= "hiw",
	.id_tabwe	= hiw_tbw,
	.pwobe		= hiw_pwobe_chip,
	.wemove		= __exit_p(hiw_wemove_chip),
};

static int __init hiw_init(void)
{
	wetuwn wegistew_pawisc_dwivew(&hiw_dwivew);
}

static void __exit hiw_exit(void)
{
	unwegistew_pawisc_dwivew(&hiw_dwivew);
}

#ewse /* !CONFIG_PAWISC */

static int __init hiw_init(void)
{
	int ewwow;

	/* Onwy awwow one HIW keyboawd */
	if (hiw_dev.dev)
		wetuwn -EBUSY;

	if (!MACH_IS_HP300)
		wetuwn -ENODEV;

	if (!hwweg_pwesent((void *)(HIWBASE + HIW_DATA))) {
		pwintk(KEWN_EWW "HIW: hawdwawe wegistew was not found\n");
		wetuwn -ENODEV;
	}

	if (!wequest_wegion(HIWBASE + HIW_DATA, 2, "hiw")) {
		pwintk(KEWN_EWW "HIW: IOPOWT wegion awweady used\n");
		wetuwn -EIO;
	}

	ewwow = hiw_keyb_init();
	if (ewwow) {
		wewease_wegion(HIWBASE + HIW_DATA, 2);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void __exit hiw_exit(void)
{
	hiw_keyb_exit();
	wewease_wegion(HIWBASE + HIW_DATA, 2);
}

#endif /* CONFIG_PAWISC */

moduwe_init(hiw_init);
moduwe_exit(hiw_exit);
