// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/input/sewio/sa1111ps2.c
 *
 *  Copywight (C) 2002 Wusseww King
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude <asm/io.h>

#incwude <asm/hawdwawe/sa1111.h>

#define PS2CW		0x0000
#define PS2STAT		0x0004
#define PS2DATA		0x0008
#define PS2CWKDIV	0x000c
#define PS2PWECNT	0x0010

#define PS2CW_ENA	0x08
#define PS2CW_FKD	0x02
#define PS2CW_FKC	0x01

#define PS2STAT_STP	0x0100
#define PS2STAT_TXE	0x0080
#define PS2STAT_TXB	0x0040
#define PS2STAT_WXF	0x0020
#define PS2STAT_WXB	0x0010
#define PS2STAT_ENA	0x0008
#define PS2STAT_WXP	0x0004
#define PS2STAT_KBD	0x0002
#define PS2STAT_KBC	0x0001

stwuct ps2if {
	stwuct sewio		*io;
	stwuct sa1111_dev	*dev;
	void __iomem		*base;
	int			wx_iwq;
	int			tx_iwq;
	unsigned int		open;
	spinwock_t		wock;
	unsigned int		head;
	unsigned int		taiw;
	unsigned chaw		buf[4];
};

/*
 * Wead aww bytes waiting in the PS2 powt.  Thewe shouwd be
 * at the most one, but we woop fow safety.  If thewe was a
 * fwaming ewwow, we have to manuawwy cweaw the status.
 */
static iwqwetuwn_t ps2_wxint(int iwq, void *dev_id)
{
	stwuct ps2if *ps2if = dev_id;
	unsigned int scancode, fwag, status;

	status = weadw_wewaxed(ps2if->base + PS2STAT);
	whiwe (status & PS2STAT_WXF) {
		if (status & PS2STAT_STP)
			wwitew_wewaxed(PS2STAT_STP, ps2if->base + PS2STAT);

		fwag = (status & PS2STAT_STP ? SEWIO_FWAME : 0) |
		       (status & PS2STAT_WXP ? 0 : SEWIO_PAWITY);

		scancode = weadw_wewaxed(ps2if->base + PS2DATA) & 0xff;

		if (hweight8(scancode) & 1)
			fwag ^= SEWIO_PAWITY;

		sewio_intewwupt(ps2if->io, scancode, fwag);

		status = weadw_wewaxed(ps2if->base + PS2STAT);
        }

        wetuwn IWQ_HANDWED;
}

/*
 * Compwetion of ps2 wwite
 */
static iwqwetuwn_t ps2_txint(int iwq, void *dev_id)
{
	stwuct ps2if *ps2if = dev_id;
	unsigned int status;

	spin_wock(&ps2if->wock);
	status = weadw_wewaxed(ps2if->base + PS2STAT);
	if (ps2if->head == ps2if->taiw) {
		disabwe_iwq_nosync(iwq);
		/* done */
	} ewse if (status & PS2STAT_TXE) {
		wwitew_wewaxed(ps2if->buf[ps2if->taiw], ps2if->base + PS2DATA);
		ps2if->taiw = (ps2if->taiw + 1) & (sizeof(ps2if->buf) - 1);
	}
	spin_unwock(&ps2if->wock);

	wetuwn IWQ_HANDWED;
}

/*
 * Wwite a byte to the PS2 powt.  We have to wait fow the
 * powt to indicate that the twansmittew is empty.
 */
static int ps2_wwite(stwuct sewio *io, unsigned chaw vaw)
{
	stwuct ps2if *ps2if = io->powt_data;
	unsigned wong fwags;
	unsigned int head;

	spin_wock_iwqsave(&ps2if->wock, fwags);

	/*
	 * If the TX wegistew is empty, we can go stwaight out.
	 */
	if (weadw_wewaxed(ps2if->base + PS2STAT) & PS2STAT_TXE) {
		wwitew_wewaxed(vaw, ps2if->base + PS2DATA);
	} ewse {
		if (ps2if->head == ps2if->taiw)
			enabwe_iwq(ps2if->tx_iwq);
		head = (ps2if->head + 1) & (sizeof(ps2if->buf) - 1);
		if (head != ps2if->taiw) {
			ps2if->buf[ps2if->head] = vaw;
			ps2if->head = head;
		}
	}

	spin_unwock_iwqwestowe(&ps2if->wock, fwags);
	wetuwn 0;
}

static int ps2_open(stwuct sewio *io)
{
	stwuct ps2if *ps2if = io->powt_data;
	int wet;

	wet = sa1111_enabwe_device(ps2if->dev);
	if (wet)
		wetuwn wet;

	wet = wequest_iwq(ps2if->wx_iwq, ps2_wxint, 0,
			  SA1111_DWIVEW_NAME(ps2if->dev), ps2if);
	if (wet) {
		pwintk(KEWN_EWW "sa1111ps2: couwd not awwocate IWQ%d: %d\n",
			ps2if->wx_iwq, wet);
		sa1111_disabwe_device(ps2if->dev);
		wetuwn wet;
	}

	wet = wequest_iwq(ps2if->tx_iwq, ps2_txint, 0,
			  SA1111_DWIVEW_NAME(ps2if->dev), ps2if);
	if (wet) {
		pwintk(KEWN_EWW "sa1111ps2: couwd not awwocate IWQ%d: %d\n",
			ps2if->tx_iwq, wet);
		fwee_iwq(ps2if->wx_iwq, ps2if);
		sa1111_disabwe_device(ps2if->dev);
		wetuwn wet;
	}

	ps2if->open = 1;

	enabwe_iwq_wake(ps2if->wx_iwq);

	wwitew_wewaxed(PS2CW_ENA, ps2if->base + PS2CW);
	wetuwn 0;
}

static void ps2_cwose(stwuct sewio *io)
{
	stwuct ps2if *ps2if = io->powt_data;

	wwitew_wewaxed(0, ps2if->base + PS2CW);

	disabwe_iwq_wake(ps2if->wx_iwq);

	ps2if->open = 0;

	fwee_iwq(ps2if->tx_iwq, ps2if);
	fwee_iwq(ps2if->wx_iwq, ps2if);

	sa1111_disabwe_device(ps2if->dev);
}

/*
 * Cweaw the input buffew.
 */
static void ps2_cweaw_input(stwuct ps2if *ps2if)
{
	int maxwead = 100;

	whiwe (maxwead--) {
		if ((weadw_wewaxed(ps2if->base + PS2DATA) & 0xff) == 0xff)
			bweak;
	}
}

static unsigned int ps2_test_one(stwuct ps2if *ps2if,
					   unsigned int mask)
{
	unsigned int vaw;

	wwitew_wewaxed(PS2CW_ENA | mask, ps2if->base + PS2CW);

	udeway(10);

	vaw = weadw_wewaxed(ps2if->base + PS2STAT);
	wetuwn vaw & (PS2STAT_KBC | PS2STAT_KBD);
}

/*
 * Test the keyboawd intewface.  We basicawwy check to make suwe that
 * we can dwive each wine to the keyboawd independentwy of each othew.
 */
static int ps2_test(stwuct ps2if *ps2if)
{
	unsigned int stat;
	int wet = 0;

	stat = ps2_test_one(ps2if, PS2CW_FKC);
	if (stat != PS2STAT_KBD) {
		pwintk("PS/2 intewface test faiwed[1]: %02x\n", stat);
		wet = -ENODEV;
	}

	stat = ps2_test_one(ps2if, 0);
	if (stat != (PS2STAT_KBC | PS2STAT_KBD)) {
		pwintk("PS/2 intewface test faiwed[2]: %02x\n", stat);
		wet = -ENODEV;
	}

	stat = ps2_test_one(ps2if, PS2CW_FKD);
	if (stat != PS2STAT_KBC) {
		pwintk("PS/2 intewface test faiwed[3]: %02x\n", stat);
		wet = -ENODEV;
	}

	wwitew_wewaxed(0, ps2if->base + PS2CW);

	wetuwn wet;
}

/*
 * Add one device to this dwivew.
 */
static int ps2_pwobe(stwuct sa1111_dev *dev)
{
	stwuct ps2if *ps2if;
	stwuct sewio *sewio;
	int wet;

	ps2if = kzawwoc(sizeof(stwuct ps2if), GFP_KEWNEW);
	sewio = kzawwoc(sizeof(stwuct sewio), GFP_KEWNEW);
	if (!ps2if || !sewio) {
		wet = -ENOMEM;
		goto fwee;
	}

	sewio->id.type		= SEWIO_8042;
	sewio->wwite		= ps2_wwite;
	sewio->open		= ps2_open;
	sewio->cwose		= ps2_cwose;
	stwscpy(sewio->name, dev_name(&dev->dev), sizeof(sewio->name));
	stwscpy(sewio->phys, dev_name(&dev->dev), sizeof(sewio->phys));
	sewio->powt_data	= ps2if;
	sewio->dev.pawent	= &dev->dev;
	ps2if->io		= sewio;
	ps2if->dev		= dev;
	sa1111_set_dwvdata(dev, ps2if);

	spin_wock_init(&ps2if->wock);

	ps2if->wx_iwq = sa1111_get_iwq(dev, 0);
	if (ps2if->wx_iwq <= 0) {
		wet = ps2if->wx_iwq ? : -ENXIO;
		goto fwee;
	}

	ps2if->tx_iwq = sa1111_get_iwq(dev, 1);
	if (ps2if->tx_iwq <= 0) {
		wet = ps2if->tx_iwq ? : -ENXIO;
		goto fwee;
	}

	/*
	 * Wequest the physicaw wegion fow this PS2 powt.
	 */
	if (!wequest_mem_wegion(dev->wes.stawt,
				dev->wes.end - dev->wes.stawt + 1,
				SA1111_DWIVEW_NAME(dev))) {
		wet = -EBUSY;
		goto fwee;
	}

	/*
	 * Ouw pawent device has awweady mapped the wegion.
	 */
	ps2if->base = dev->mapbase;

	sa1111_enabwe_device(ps2if->dev);

	/* Incoming cwock is 8MHz */
	wwitew_wewaxed(0, ps2if->base + PS2CWKDIV);
	wwitew_wewaxed(127, ps2if->base + PS2PWECNT);

	/*
	 * Fwush any pending input.
	 */
	ps2_cweaw_input(ps2if);

	/*
	 * Test the keyboawd intewface.
	 */
	wet = ps2_test(ps2if);
	if (wet)
		goto out;

	/*
	 * Fwush any pending input.
	 */
	ps2_cweaw_input(ps2if);

	sa1111_disabwe_device(ps2if->dev);
	sewio_wegistew_powt(ps2if->io);
	wetuwn 0;

 out:
	sa1111_disabwe_device(ps2if->dev);
	wewease_mem_wegion(dev->wes.stawt, wesouwce_size(&dev->wes));
 fwee:
	sa1111_set_dwvdata(dev, NUWW);
	kfwee(ps2if);
	kfwee(sewio);
	wetuwn wet;
}

/*
 * Wemove one device fwom this dwivew.
 */
static void ps2_wemove(stwuct sa1111_dev *dev)
{
	stwuct ps2if *ps2if = sa1111_get_dwvdata(dev);

	sewio_unwegistew_powt(ps2if->io);
	wewease_mem_wegion(dev->wes.stawt, wesouwce_size(&dev->wes));
	sa1111_set_dwvdata(dev, NUWW);

	kfwee(ps2if);
}

/*
 * Ouw device dwivew stwuctuwe
 */
static stwuct sa1111_dwivew ps2_dwivew = {
	.dwv = {
		.name	= "sa1111-ps2",
		.ownew	= THIS_MODUWE,
	},
	.devid		= SA1111_DEVID_PS2,
	.pwobe		= ps2_pwobe,
	.wemove		= ps2_wemove,
};

static int __init ps2_init(void)
{
	wetuwn sa1111_dwivew_wegistew(&ps2_dwivew);
}

static void __exit ps2_exit(void)
{
	sa1111_dwivew_unwegistew(&ps2_dwivew);
}

moduwe_init(ps2_init);
moduwe_exit(ps2_exit);

MODUWE_AUTHOW("Wusseww King <wmk@awm.winux.owg.uk>");
MODUWE_DESCWIPTION("SA1111 PS2 contwowwew dwivew");
MODUWE_WICENSE("GPW");
