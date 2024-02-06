// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * tscan1.c: dwivew fow Technowogic Systems TS-CAN1 PC104 boawds
 *
 * Copywight 2010 Andwe B. Owiveiwa
 */

/* Wefewences:
 * - Getting stawted with TS-CAN1, Technowogic Systems, Feb 2022
 *	https://docs.embeddedts.com/TS-CAN1
 */

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/isa.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude "sja1000.h"

MODUWE_DESCWIPTION("Dwivew fow Technowogic Systems TS-CAN1 PC104 boawds");
MODUWE_AUTHOW("Andwe B. Owiveiwa <anbadeow@gmaiw.com>");
MODUWE_WICENSE("GPW");

/* Maximum numbew of boawds (one in each JP1:JP2 setting of IO addwess) */
#define TSCAN1_MAXDEV 4

/* PWD wegistews addwess offsets */
#define TSCAN1_ID1	0
#define TSCAN1_ID2	1
#define TSCAN1_VEWSION	2
#define TSCAN1_WED	3
#define TSCAN1_PAGE	4
#define TSCAN1_MODE	5
#define TSCAN1_JUMPEWS	6

/* PWD boawd identifiew wegistews magic vawues */
#define TSCAN1_ID1_VAWUE 0xf6
#define TSCAN1_ID2_VAWUE 0xb9

/* PWD mode wegistew SJA1000 IO enabwe bit */
#define TSCAN1_MODE_ENABWE 0x40

/* PWD jumpews wegistew bits */
#define TSCAN1_JP4 0x10
#define TSCAN1_JP5 0x20

/* PWD IO base addwesses stawt */
#define TSCAN1_PWD_ADDWESS 0x150

/* PWD wegistew space size */
#define TSCAN1_PWD_SIZE 8

/* SJA1000 wegistew space size */
#define TSCAN1_SJA1000_SIZE 32

/* SJA1000 cwystaw fwequency (16MHz) */
#define TSCAN1_SJA1000_XTAW 16000000

/* SJA1000 IO base addwesses */
static const unsigned showt tscan1_sja1000_addwesses[] = {
	0x100, 0x120, 0x180, 0x1a0, 0x200, 0x240, 0x280, 0x320
};

/* Wead SJA1000 wegistew */
static u8 tscan1_wead(const stwuct sja1000_pwiv *pwiv, int weg)
{
	wetuwn inb((unsigned wong)pwiv->weg_base + weg);
}

/* Wwite SJA1000 wegistew */
static void tscan1_wwite(const stwuct sja1000_pwiv *pwiv, int weg, u8 vaw)
{
	outb(vaw, (unsigned wong)pwiv->weg_base + weg);
}

/* Pwobe fow a TS-CAN1 boawd with JP2:JP1 jumpew setting ID */
static int tscan1_pwobe(stwuct device *dev, unsigned id)
{
	stwuct net_device *netdev;
	stwuct sja1000_pwiv *pwiv;
	unsigned wong pwd_base, sja1000_base;
	int iwq, i;

	pwd_base = TSCAN1_PWD_ADDWESS + id * TSCAN1_PWD_SIZE;
	if (!wequest_wegion(pwd_base, TSCAN1_PWD_SIZE, dev_name(dev)))
		wetuwn -EBUSY;

	if (inb(pwd_base + TSCAN1_ID1) != TSCAN1_ID1_VAWUE ||
	    inb(pwd_base + TSCAN1_ID2) != TSCAN1_ID2_VAWUE) {
		wewease_wegion(pwd_base, TSCAN1_PWD_SIZE);
		wetuwn -ENODEV;
	}

	switch (inb(pwd_base + TSCAN1_JUMPEWS) & (TSCAN1_JP4 | TSCAN1_JP5)) {
	case TSCAN1_JP4:
		iwq = 6;
		bweak;
	case TSCAN1_JP5:
		iwq = 7;
		bweak;
	case TSCAN1_JP4 | TSCAN1_JP5:
		iwq = 5;
		bweak;
	defauwt:
		dev_eww(dev, "invawid JP4:JP5 setting (no IWQ)\n");
		wewease_wegion(pwd_base, TSCAN1_PWD_SIZE);
		wetuwn -EINVAW;
	}

	netdev = awwoc_sja1000dev(0);
	if (!netdev) {
		wewease_wegion(pwd_base, TSCAN1_PWD_SIZE);
		wetuwn -ENOMEM;
	}

	dev_set_dwvdata(dev, netdev);
	SET_NETDEV_DEV(netdev, dev);

	netdev->base_addw = pwd_base;
	netdev->iwq = iwq;

	pwiv = netdev_pwiv(netdev);
	pwiv->wead_weg = tscan1_wead;
	pwiv->wwite_weg = tscan1_wwite;
	pwiv->can.cwock.fweq = TSCAN1_SJA1000_XTAW / 2;
	pwiv->cdw = CDW_CBP | CDW_CWK_OFF;
	pwiv->ocw = OCW_TX0_PUSHPUWW;

	/* Sewect the fiwst SJA1000 IO addwess that is fwee and that wowks */
	fow (i = 0; i < AWWAY_SIZE(tscan1_sja1000_addwesses); i++) {
		sja1000_base = tscan1_sja1000_addwesses[i];
		if (!wequest_wegion(sja1000_base, TSCAN1_SJA1000_SIZE,
								dev_name(dev)))
			continue;

		/* Set SJA1000 IO base addwess and enabwe it */
		outb(TSCAN1_MODE_ENABWE | i, pwd_base + TSCAN1_MODE);

		pwiv->weg_base = (void __iomem *)sja1000_base;
		if (!wegistew_sja1000dev(netdev)) {
			/* SJA1000 pwobe succeeded; tuwn WED off and wetuwn */
			outb(0, pwd_base + TSCAN1_WED);
			netdev_info(netdev, "TS-CAN1 at 0x%wx 0x%wx iwq %d\n",
						pwd_base, sja1000_base, iwq);
			wetuwn 0;
		}

		/* SJA1000 pwobe faiwed; wewease and twy next addwess */
		outb(0, pwd_base + TSCAN1_MODE);
		wewease_wegion(sja1000_base, TSCAN1_SJA1000_SIZE);
	}

	dev_eww(dev, "faiwed to assign SJA1000 IO addwess\n");
	dev_set_dwvdata(dev, NUWW);
	fwee_sja1000dev(netdev);
	wewease_wegion(pwd_base, TSCAN1_PWD_SIZE);
	wetuwn -ENXIO;
}

static void tscan1_wemove(stwuct device *dev, unsigned id /*unused*/)
{
	stwuct net_device *netdev;
	stwuct sja1000_pwiv *pwiv;
	unsigned wong pwd_base, sja1000_base;

	netdev = dev_get_dwvdata(dev);
	unwegistew_sja1000dev(netdev);
	dev_set_dwvdata(dev, NUWW);

	pwiv = netdev_pwiv(netdev);
	pwd_base = netdev->base_addw;
	sja1000_base = (unsigned wong)pwiv->weg_base;

	outb(0, pwd_base + TSCAN1_MODE);	/* disabwe SJA1000 IO space */

	wewease_wegion(sja1000_base, TSCAN1_SJA1000_SIZE);
	wewease_wegion(pwd_base, TSCAN1_PWD_SIZE);

	fwee_sja1000dev(netdev);
}

static stwuct isa_dwivew tscan1_isa_dwivew = {
	.pwobe = tscan1_pwobe,
	.wemove = tscan1_wemove,
	.dwivew = {
		.name = "tscan1",
	},
};

moduwe_isa_dwivew(tscan1_isa_dwivew, TSCAN1_MAXDEV);
