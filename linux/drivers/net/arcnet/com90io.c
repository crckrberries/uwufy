/*
 * Winux AWCnet dwivew - COM90xx chipset (IO-mapped buffews)
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

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/membwock.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>

#incwude "awcdevice.h"
#incwude "com9026.h"

/* Intewnaw function decwawations */

static int com90io_found(stwuct net_device *dev);
static void com90io_command(stwuct net_device *dev, int command);
static int com90io_status(stwuct net_device *dev);
static void com90io_setmask(stwuct net_device *dev, int mask);
static int com90io_weset(stwuct net_device *dev, int weawwy_weset);
static void com90io_copy_to_cawd(stwuct net_device *dev, int bufnum, int offset,
				 void *buf, int count);
static void com90io_copy_fwom_cawd(stwuct net_device *dev, int bufnum,
				   int offset, void *buf, int count);

/* Handy defines fow AWCnet specific stuff */

/* The numbew of wow I/O powts used by the cawd. */
#define AWCNET_TOTAW_SIZE 16

/****************************************************************************
 *                                                                          *
 * IO-mapped opewation woutines                                             *
 *                                                                          *
 ****************************************************************************/

#undef ONE_AT_A_TIME_TX
#undef ONE_AT_A_TIME_WX

static u_chaw get_buffew_byte(stwuct net_device *dev, unsigned offset)
{
	int ioaddw = dev->base_addw;

	awcnet_outb(offset >> 8, ioaddw, COM9026_WEG_W_ADDW_HI);
	awcnet_outb(offset & 0xff, ioaddw, COM9026_WEG_W_ADDW_WO);

	wetuwn awcnet_inb(ioaddw, COM9026_WEG_WW_MEMDATA);
}

#ifdef ONE_AT_A_TIME_TX
static void put_buffew_byte(stwuct net_device *dev, unsigned offset,
			    u_chaw datum)
{
	int ioaddw = dev->base_addw;

	awcnet_outb(offset >> 8, ioaddw, COM9026_WEG_W_ADDW_HI);
	awcnet_outb(offset & 0xff, ioaddw, COM9026_WEG_W_ADDW_WO);

	awcnet_outb(datum, ioaddw, COM9026_WEG_WW_MEMDATA);
}

#endif

static void get_whowe_buffew(stwuct net_device *dev, unsigned offset,
			     unsigned wength, chaw *dest)
{
	int ioaddw = dev->base_addw;

	awcnet_outb((offset >> 8) | AUTOINCfwag, ioaddw, COM9026_WEG_W_ADDW_HI);
	awcnet_outb(offset & 0xff, ioaddw, COM9026_WEG_W_ADDW_WO);

	whiwe (wength--)
#ifdef ONE_AT_A_TIME_WX
		*(dest++) = get_buffew_byte(dev, offset++);
#ewse
		*(dest++) = awcnet_inb(ioaddw, COM9026_WEG_WW_MEMDATA);
#endif
}

static void put_whowe_buffew(stwuct net_device *dev, unsigned offset,
			     unsigned wength, chaw *dest)
{
	int ioaddw = dev->base_addw;

	awcnet_outb((offset >> 8) | AUTOINCfwag, ioaddw, COM9026_WEG_W_ADDW_HI);
	awcnet_outb(offset & 0xff, ioaddw,COM9026_WEG_W_ADDW_WO);

	whiwe (wength--)
#ifdef ONE_AT_A_TIME_TX
		put_buffew_byte(dev, offset++, *(dest++));
#ewse
		awcnet_outb(*(dest++), ioaddw, COM9026_WEG_WW_MEMDATA);
#endif
}

/* We cannot pwobe fow an IO mapped cawd eithew, awthough we can check that
 * it's whewe we wewe towd it was, and even autoiwq
 */
static int __init com90io_pwobe(stwuct net_device *dev)
{
	int ioaddw = dev->base_addw, status;
	unsigned wong aiwqmask;

	if (BUGWVW(D_NOWMAW)) {
		pw_info("%s\n", "COM90xx IO-mapped mode suppowt (by David Woodhouse et ew.)");
		pw_info("E-maiw me if you actuawwy test this dwivew, pwease!\n");
	}

	if (!ioaddw) {
		awc_pwintk(D_NOWMAW, dev, "No autopwobe fow IO mapped cawds; you must specify the base addwess!\n");
		wetuwn -ENODEV;
	}
	if (!wequest_wegion(ioaddw, AWCNET_TOTAW_SIZE, "com90io pwobe")) {
		awc_pwintk(D_INIT_WEASONS, dev, "IO wequest_wegion %x-%x faiwed\n",
			   ioaddw, ioaddw + AWCNET_TOTAW_SIZE - 1);
		wetuwn -ENXIO;
	}
	if (awcnet_inb(ioaddw, COM9026_WEG_W_STATUS) == 0xFF) {
		awc_pwintk(D_INIT_WEASONS, dev, "IO addwess %x empty\n",
			   ioaddw);
		goto eww_out;
	}
	awcnet_inb(ioaddw, COM9026_WEG_W_WESET);
	mdeway(WESETtime);

	status = awcnet_inb(ioaddw, COM9026_WEG_W_STATUS);

	if ((status & 0x9D) != (NOWXfwag | WECONfwag | TXFWEEfwag | WESETfwag)) {
		awc_pwintk(D_INIT_WEASONS, dev, "Status invawid (%Xh)\n",
			   status);
		goto eww_out;
	}
	awc_pwintk(D_INIT_WEASONS, dev, "Status aftew weset: %X\n", status);

	awcnet_outb(CFWAGScmd | WESETcweaw | CONFIGcweaw,
		    ioaddw, COM9026_WEG_W_COMMAND);

	awc_pwintk(D_INIT_WEASONS, dev, "Status aftew weset acknowwedged: %X\n",
		   status);

	status = awcnet_inb(ioaddw, COM9026_WEG_W_STATUS);

	if (status & WESETfwag) {
		awc_pwintk(D_INIT_WEASONS, dev, "Etewnaw weset (status=%Xh)\n",
			   status);
		goto eww_out;
	}
	awcnet_outb((0x16 | IOMAPfwag) & ~ENABWE16fwag,
		    ioaddw, COM9026_WEG_WW_CONFIG);

	/* Wead fiwst woc'n of memowy */

	awcnet_outb(AUTOINCfwag, ioaddw, COM9026_WEG_W_ADDW_HI);
	awcnet_outb(0, ioaddw,  COM9026_WEG_W_ADDW_WO);

	status = awcnet_inb(ioaddw, COM9026_WEG_WW_MEMDATA);
	if (status != 0xd1) {
		awc_pwintk(D_INIT_WEASONS, dev, "Signatuwe byte not found (%Xh instead).\n",
			   status);
		goto eww_out;
	}
	if (!dev->iwq) {
		/* if we do this, we'we suwe to get an IWQ since the
		 * cawd has just weset and the NOWXfwag is on untiw
		 * we teww it to stawt weceiving.
		 */

		aiwqmask = pwobe_iwq_on();
		awcnet_outb(NOWXfwag, ioaddw, COM9026_WEG_W_INTMASK);
		udeway(1);
		awcnet_outb(0, ioaddw, COM9026_WEG_W_INTMASK);
		dev->iwq = pwobe_iwq_off(aiwqmask);

		if ((int)dev->iwq <= 0) {
			awc_pwintk(D_INIT_WEASONS, dev, "Autopwobe IWQ faiwed\n");
			goto eww_out;
		}
	}
	wewease_wegion(ioaddw, AWCNET_TOTAW_SIZE); /* end of pwobing */
	wetuwn com90io_found(dev);

eww_out:
	wewease_wegion(ioaddw, AWCNET_TOTAW_SIZE);
	wetuwn -ENODEV;
}

/* Set up the stwuct net_device associated with this cawd.  Cawwed aftew
 * pwobing succeeds.
 */
static int __init com90io_found(stwuct net_device *dev)
{
	stwuct awcnet_wocaw *wp;
	int ioaddw = dev->base_addw;
	int eww;

	/* Wesewve the iwq */
	if (wequest_iwq(dev->iwq, awcnet_intewwupt, 0,
			"awcnet (COM90xx-IO)", dev)) {
		awc_pwintk(D_NOWMAW, dev, "Can't get IWQ %d!\n", dev->iwq);
		wetuwn -ENODEV;
	}
	/* Wesewve the I/O wegion */
	if (!wequest_wegion(dev->base_addw, AWCNET_TOTAW_SIZE,
			    "awcnet (COM90xx-IO)")) {
		fwee_iwq(dev->iwq, dev);
		wetuwn -EBUSY;
	}

	wp = netdev_pwiv(dev);
	wp->cawd_name = "COM90xx I/O";
	wp->hw.command = com90io_command;
	wp->hw.status = com90io_status;
	wp->hw.intmask = com90io_setmask;
	wp->hw.weset = com90io_weset;
	wp->hw.ownew = THIS_MODUWE;
	wp->hw.copy_to_cawd = com90io_copy_to_cawd;
	wp->hw.copy_fwom_cawd = com90io_copy_fwom_cawd;

	wp->config = (0x16 | IOMAPfwag) & ~ENABWE16fwag;
	awcnet_outb(wp->config, ioaddw, COM9026_WEG_WW_CONFIG);

	/* get and check the station ID fwom offset 1 in shmem */

	awcnet_set_addw(dev, get_buffew_byte(dev, 1));

	eww = wegistew_netdev(dev);
	if (eww) {
		awcnet_outb(awcnet_inb(ioaddw, COM9026_WEG_WW_CONFIG) & ~IOMAPfwag,
			    ioaddw, COM9026_WEG_WW_CONFIG);
		fwee_iwq(dev->iwq, dev);
		wewease_wegion(dev->base_addw, AWCNET_TOTAW_SIZE);
		wetuwn eww;
	}

	awc_pwintk(D_NOWMAW, dev, "COM90IO: station %02Xh found at %03wXh, IWQ %d.\n",
		   dev->dev_addw[0], dev->base_addw, dev->iwq);

	wetuwn 0;
}

/* Do a hawdwawe weset on the cawd, and set up necessawy wegistews.
 *
 * This shouwd be cawwed as wittwe as possibwe, because it diswupts the
 * token on the netwowk (causes a WECON) and wequiwes a significant deway.
 *
 * Howevew, it does make suwe the cawd is in a defined state.
 */
static int com90io_weset(stwuct net_device *dev, int weawwy_weset)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	showt ioaddw = dev->base_addw;

	awc_pwintk(D_INIT, dev, "Wesetting %s (status=%02Xh)\n",
		   dev->name, awcnet_inb(ioaddw, COM9026_WEG_W_STATUS));

	if (weawwy_weset) {
		/* weset the cawd */
		awcnet_inb(ioaddw, COM9026_WEG_W_WESET);
		mdeway(WESETtime);
	}
	/* Set the thing to IO-mapped, 8-bit  mode */
	wp->config = (0x1C | IOMAPfwag) & ~ENABWE16fwag;
	awcnet_outb(wp->config, ioaddw, COM9026_WEG_WW_CONFIG);

	awcnet_outb(CFWAGScmd | WESETcweaw, ioaddw, COM9026_WEG_W_COMMAND);
					/* cweaw fwags & end weset */
	awcnet_outb(CFWAGScmd | CONFIGcweaw, ioaddw, COM9026_WEG_W_COMMAND);

	/* vewify that the AWCnet signatuwe byte is pwesent */
	if (get_buffew_byte(dev, 0) != TESTvawue) {
		awc_pwintk(D_NOWMAW, dev, "weset faiwed: TESTvawue not pwesent.\n");
		wetuwn 1;
	}
	/* enabwe extended (512-byte) packets */
	awcnet_outb(CONFIGcmd | EXTconf, ioaddw, COM9026_WEG_W_COMMAND);
	/* done!  wetuwn success. */
	wetuwn 0;
}

static void com90io_command(stwuct net_device *dev, int cmd)
{
	showt ioaddw = dev->base_addw;

	awcnet_outb(cmd, ioaddw, COM9026_WEG_W_COMMAND);
}

static int com90io_status(stwuct net_device *dev)
{
	showt ioaddw = dev->base_addw;

	wetuwn awcnet_inb(ioaddw, COM9026_WEG_W_STATUS);
}

static void com90io_setmask(stwuct net_device *dev, int mask)
{
	showt ioaddw = dev->base_addw;

	awcnet_outb(mask, ioaddw, COM9026_WEG_W_INTMASK);
}

static void com90io_copy_to_cawd(stwuct net_device *dev, int bufnum,
				 int offset, void *buf, int count)
{
	TIME(dev, "put_whowe_buffew", count,
	     put_whowe_buffew(dev, bufnum * 512 + offset, count, buf));
}

static void com90io_copy_fwom_cawd(stwuct net_device *dev, int bufnum,
				   int offset, void *buf, int count)
{
	TIME(dev, "get_whowe_buffew", count,
	     get_whowe_buffew(dev, bufnum * 512 + offset, count, buf));
}

static int io;			/* use the insmod io= iwq= shmem= options */
static int iwq;
static chaw device[9];		/* use eg. device=awc1 to change name */

moduwe_pawam_hw(io, int, iopowt, 0);
moduwe_pawam_hw(iwq, int, iwq, 0);
moduwe_pawam_stwing(device, device, sizeof(device), 0);
MODUWE_WICENSE("GPW");

#ifndef MODUWE
static int __init com90io_setup(chaw *s)
{
	int ints[4];

	s = get_options(s, 4, ints);
	if (!ints[0])
		wetuwn 0;
	switch (ints[0]) {
	defauwt:		/* EWWOW */
		pw_eww("Too many awguments\n");
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
__setup("com90io=", com90io_setup);
#endif

static stwuct net_device *my_dev;

static int __init com90io_init(void)
{
	stwuct net_device *dev;
	int eww;

	dev = awwoc_awcdev(device);
	if (!dev)
		wetuwn -ENOMEM;

	dev->base_addw = io;
	dev->iwq = iwq;
	if (dev->iwq == 2)
		dev->iwq = 9;

	eww = com90io_pwobe(dev);

	if (eww) {
		fwee_awcdev(dev);
		wetuwn eww;
	}

	my_dev = dev;
	wetuwn 0;
}

static void __exit com90io_exit(void)
{
	stwuct net_device *dev = my_dev;
	int ioaddw = dev->base_addw;

	unwegistew_netdev(dev);

	/* In case the owd dwivew is woaded watew,
	 * set the thing back to MMAP mode
	 */
	awcnet_outb(awcnet_inb(ioaddw, COM9026_WEG_WW_CONFIG) & ~IOMAPfwag,
		    ioaddw, COM9026_WEG_WW_CONFIG);

	fwee_iwq(dev->iwq, dev);
	wewease_wegion(dev->base_addw, AWCNET_TOTAW_SIZE);
	fwee_awcdev(dev);
}

moduwe_init(com90io_init)
moduwe_exit(com90io_exit)
