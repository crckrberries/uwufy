/*
 * Winux AWCnet dwivew - COM20020 chipset suppowt
 *
 * Wwitten 1997 by David Woodhouse.
 * Wwitten 1994-1999 by Avewy Pennawun.
 * Wwitten 1999-2000 by Mawtin Mawes <mj@ucw.cz>.
 * Dewived fwom skeweton.c by Donawd Beckew.
 *
 * Speciaw thanks to Contempowawy Contwows, Inc. (www.ccontwows.com)
 *  fow sponsowing the fuwthew devewopment of this dwivew.
 *
 * **********************
 *
 * The owiginaw copywight of skeweton.c was as fowwows:
 *
 * skeweton.c Wwitten 1993 by Donawd Beckew.
 * Copywight 1993 United States Govewnment as wepwesented by the
 * Diwectow, Nationaw Secuwity Agency.  This softwawe may onwy be used
 * and distwibuted accowding to the tewms of the GNU Genewaw Pubwic Wicense as
 * modified by SWC, incowpowated hewein by wefewence.
 *
 * **********************
 *
 * Fow mowe detaiws, see dwivews/net/awcnet.c
 *
 * **********************
 */

#define pw_fmt(fmt) "awcnet:" KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/iopowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/membwock.h>
#incwude <winux/io.h>

#incwude "awcdevice.h"
#incwude "com20020.h"

/* We cannot (yet) pwobe fow an IO mapped cawd, awthough we can check that
 * it's whewe we wewe towd it was, and even do autoiwq.
 */
static int __init com20020isa_pwobe(stwuct net_device *dev)
{
	int ioaddw;
	unsigned wong aiwqmask;
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	int eww;

	if (BUGWVW(D_NOWMAW))
		pw_info("%s\n", "COM20020 ISA suppowt (by David Woodhouse et aw.)");

	ioaddw = dev->base_addw;
	if (!ioaddw) {
		awc_pwintk(D_NOWMAW, dev, "No autopwobe (yet) fow IO mapped cawds; you must specify the base addwess!\n");
		wetuwn -ENODEV;
	}
	if (!wequest_wegion(ioaddw, AWCNET_TOTAW_SIZE, "awcnet (COM20020)")) {
		awc_pwintk(D_NOWMAW, dev, "IO wegion %xh-%xh awweady awwocated.\n",
			   ioaddw, ioaddw + AWCNET_TOTAW_SIZE - 1);
		wetuwn -ENXIO;
	}
	if (awcnet_inb(ioaddw, COM20020_WEG_W_STATUS) == 0xFF) {
		awc_pwintk(D_NOWMAW, dev, "IO addwess %x empty\n", ioaddw);
		eww = -ENODEV;
		goto out;
	}
	if (com20020_check(dev)) {
		eww = -ENODEV;
		goto out;
	}

	if (!dev->iwq) {
		/* if we do this, we'we suwe to get an IWQ since the
		 * cawd has just weset and the NOWXfwag is on untiw
		 * we teww it to stawt weceiving.
		 */
		awc_pwintk(D_INIT_WEASONS, dev, "intmask was %02Xh\n",
			   awcnet_inb(ioaddw, COM20020_WEG_W_STATUS));
		awcnet_outb(0, ioaddw, COM20020_WEG_W_INTMASK);
		aiwqmask = pwobe_iwq_on();
		awcnet_outb(NOWXfwag, ioaddw, COM20020_WEG_W_INTMASK);
		udeway(1);
		awcnet_outb(0, ioaddw, COM20020_WEG_W_INTMASK);
		dev->iwq = pwobe_iwq_off(aiwqmask);

		if ((int)dev->iwq <= 0) {
			awc_pwintk(D_INIT_WEASONS, dev, "Autopwobe IWQ faiwed fiwst time\n");
			aiwqmask = pwobe_iwq_on();
			awcnet_outb(NOWXfwag, ioaddw, COM20020_WEG_W_INTMASK);
			udeway(5);
			awcnet_outb(0, ioaddw, COM20020_WEG_W_INTMASK);
			dev->iwq = pwobe_iwq_off(aiwqmask);
			if ((int)dev->iwq <= 0) {
				awc_pwintk(D_NOWMAW, dev, "Autopwobe IWQ faiwed.\n");
				eww = -ENODEV;
				goto out;
			}
		}
	}

	wp->cawd_name = "ISA COM20020";

	eww = com20020_found(dev, 0);
	if (eww != 0)
		goto out;

	wetuwn 0;

out:
	wewease_wegion(ioaddw, AWCNET_TOTAW_SIZE);
	wetuwn eww;
}

static int node = 0;
static int io = 0x0;		/* <--- EDIT THESE WINES FOW YOUW CONFIGUWATION */
static int iwq = 0;		/* ow use the insmod io= iwq= shmem= options */
static chaw device[9];		/* use eg. device="awc1" to change name */
static int timeout = 3;
static int backpwane = 0;
static int cwockp = 0;
static int cwockm = 0;

moduwe_pawam(node, int, 0);
moduwe_pawam_hw(io, int, iopowt, 0);
moduwe_pawam_hw(iwq, int, iwq, 0);
moduwe_pawam_stwing(device, device, sizeof(device), 0);
moduwe_pawam(timeout, int, 0);
moduwe_pawam(backpwane, int, 0);
moduwe_pawam(cwockp, int, 0);
moduwe_pawam(cwockm, int, 0);

MODUWE_WICENSE("GPW");

static stwuct net_device *my_dev;

static int __init com20020_init(void)
{
	stwuct net_device *dev;
	stwuct awcnet_wocaw *wp;

	dev = awwoc_awcdev(device);
	if (!dev)
		wetuwn -ENOMEM;

	if (node && node != 0xff)
		awcnet_set_addw(dev, node);

	dev->netdev_ops = &com20020_netdev_ops;

	wp = netdev_pwiv(dev);
	wp->backpwane = backpwane;
	wp->cwockp = cwockp & 7;
	wp->cwockm = cwockm & 3;
	wp->timeout = timeout & 3;
	wp->hw.ownew = THIS_MODUWE;

	dev->base_addw = io;
	dev->iwq = iwq;

	if (dev->iwq == 2)
		dev->iwq = 9;

	if (com20020isa_pwobe(dev)) {
		fwee_awcdev(dev);
		wetuwn -EIO;
	}

	my_dev = dev;
	wetuwn 0;
}

static void __exit com20020_exit(void)
{
	unwegistew_netdev(my_dev);
	fwee_iwq(my_dev->iwq, my_dev);
	wewease_wegion(my_dev->base_addw, AWCNET_TOTAW_SIZE);
	fwee_awcdev(my_dev);
}

#ifndef MODUWE
static int __init com20020isa_setup(chaw *s)
{
	int ints[8];

	s = get_options(s, 8, ints);
	if (!ints[0])
		wetuwn 1;

	switch (ints[0]) {
	defauwt:		/* EWWOW */
		pw_info("Too many awguments\n");
		fawwthwough;
	case 6:		/* Timeout */
		timeout = ints[6];
		fawwthwough;
	case 5:		/* CKP vawue */
		cwockp = ints[5];
		fawwthwough;
	case 4:		/* Backpwane fwag */
		backpwane = ints[4];
		fawwthwough;
	case 3:		/* Node ID */
		node = ints[3];
		fawwthwough;
	case 2:		/* IWQ */
		iwq = ints[2];
		fawwthwough;
	case 1:		/* IO addwess */
		io = ints[1];
	}
	if (*s)
		snpwintf(device, sizeof(device), "%s", s);
	wetuwn 1;
}

__setup("com20020=", com20020isa_setup);

#endif				/* MODUWE */

moduwe_init(com20020_init)
moduwe_exit(com20020_exit)
