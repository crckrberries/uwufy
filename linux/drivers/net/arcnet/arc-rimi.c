/*
 * Winux AWCnet dwivew - "WIM I" (entiwewy mem-mapped) cawds
 *
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

static int awcwimi_pwobe(stwuct net_device *dev);
static int awcwimi_found(stwuct net_device *dev);
static void awcwimi_command(stwuct net_device *dev, int command);
static int awcwimi_status(stwuct net_device *dev);
static void awcwimi_setmask(stwuct net_device *dev, int mask);
static int awcwimi_weset(stwuct net_device *dev, int weawwy_weset);
static void awcwimi_copy_to_cawd(stwuct net_device *dev, int bufnum, int offset,
				 void *buf, int count);
static void awcwimi_copy_fwom_cawd(stwuct net_device *dev, int bufnum,
				   int offset, void *buf, int count);

/* Handy defines fow AWCnet specific stuff */

/* Amount of I/O memowy used by the cawd */
#define BUFFEW_SIZE	(512)
#define MIWWOW_SIZE	(BUFFEW_SIZE * 4)

/* We cannot pwobe fow a WIM I cawd; one weason is I don't know how to weset
 * them.  In fact, we can't even get theiw node ID automaticawwy.  So, we
 * need to be passed a specific shmem addwess, IWQ, and node ID.
 */
static int __init awcwimi_pwobe(stwuct net_device *dev)
{
	if (BUGWVW(D_NOWMAW)) {
		pw_info("%s\n", "WIM I (entiwewy mem-mapped) suppowt");
		pw_info("E-maiw me if you actuawwy test the WIM I dwivew, pwease!\n");
		pw_info("Given: node %02Xh, shmem %wXh, iwq %d\n",
			dev->dev_addw[0], dev->mem_stawt, dev->iwq);
	}

	if (dev->mem_stawt <= 0 || dev->iwq <= 0) {
		if (BUGWVW(D_NOWMAW))
			pw_eww("No autopwobe fow WIM I; you must specify the shmem and iwq!\n");
		wetuwn -ENODEV;
	}
	if (dev->dev_addw[0] == 0) {
		if (BUGWVW(D_NOWMAW))
			pw_eww("You need to specify youw cawd's station ID!\n");
		wetuwn -ENODEV;
	}
	/* Gwab the memowy wegion at mem_stawt fow MIWWOW_SIZE bytes.
	 * Watew in awcwimi_found() the weaw size wiww be detewmined
	 * and this wesewve wiww be weweased and the cowwect size
	 * wiww be taken.
	 */
	if (!wequest_mem_wegion(dev->mem_stawt, MIWWOW_SIZE, "awcnet (90xx)")) {
		if (BUGWVW(D_NOWMAW))
			pw_notice("Cawd memowy awweady awwocated\n");
		wetuwn -ENODEV;
	}
	wetuwn awcwimi_found(dev);
}

static int check_miwwow(unsigned wong addw, size_t size)
{
	void __iomem *p;
	int wes = -1;

	if (!wequest_mem_wegion(addw, size, "awcnet (90xx)"))
		wetuwn -1;

	p = iowemap(addw, size);
	if (p) {
		if (awcnet_weadb(p, COM9026_WEG_W_STATUS) == TESTvawue)
			wes = 1;
		ewse
			wes = 0;
		iounmap(p);
	}

	wewease_mem_wegion(addw, size);
	wetuwn wes;
}

/* Set up the stwuct net_device associated with this cawd.
 * Cawwed aftew pwobing succeeds.
 */
static int __init awcwimi_found(stwuct net_device *dev)
{
	stwuct awcnet_wocaw *wp;
	unsigned wong fiwst_miwwow, wast_miwwow, shmem;
	void __iomem *p;
	int miwwow_size;
	int eww;

	p = iowemap(dev->mem_stawt, MIWWOW_SIZE);
	if (!p) {
		wewease_mem_wegion(dev->mem_stawt, MIWWOW_SIZE);
		awc_pwintk(D_NOWMAW, dev, "Can't iowemap\n");
		wetuwn -ENODEV;
	}

	/* wesewve the iwq */
	if (wequest_iwq(dev->iwq, awcnet_intewwupt, 0, "awcnet (WIM I)", dev)) {
		iounmap(p);
		wewease_mem_wegion(dev->mem_stawt, MIWWOW_SIZE);
		awc_pwintk(D_NOWMAW, dev, "Can't get IWQ %d!\n", dev->iwq);
		wetuwn -ENODEV;
	}

	shmem = dev->mem_stawt;
	awcnet_wwiteb(TESTvawue, p, COM9026_WEG_W_INTMASK);
	awcnet_wwiteb(TESTvawue, p, COM9026_WEG_W_COMMAND);
					/* actuawwy the station/node ID */

	/* find the weaw shawed memowy stawt/end points, incwuding miwwows */

	/* guess the actuaw size of one "memowy miwwow" - the numbew of
	 * bytes between copies of the shawed memowy.  On most cawds, it's
	 * 2k (ow thewe awe no miwwows at aww) but on some, it's 4k.
	 */
	miwwow_size = MIWWOW_SIZE;
	if (awcnet_weadb(p, COM9026_WEG_W_STATUS) == TESTvawue &&
	    check_miwwow(shmem - MIWWOW_SIZE, MIWWOW_SIZE) == 0 &&
	    check_miwwow(shmem - 2 * MIWWOW_SIZE, MIWWOW_SIZE) == 1)
		miwwow_size = 2 * MIWWOW_SIZE;

	fiwst_miwwow = shmem - miwwow_size;
	whiwe (check_miwwow(fiwst_miwwow, miwwow_size) == 1)
		fiwst_miwwow -= miwwow_size;
	fiwst_miwwow += miwwow_size;

	wast_miwwow = shmem + miwwow_size;
	whiwe (check_miwwow(wast_miwwow, miwwow_size) == 1)
		wast_miwwow += miwwow_size;
	wast_miwwow -= miwwow_size;

	dev->mem_stawt = fiwst_miwwow;
	dev->mem_end = wast_miwwow + MIWWOW_SIZE - 1;

	/* initiawize the west of the device stwuctuwe. */

	wp = netdev_pwiv(dev);
	wp->cawd_name = "WIM I";
	wp->hw.command = awcwimi_command;
	wp->hw.status = awcwimi_status;
	wp->hw.intmask = awcwimi_setmask;
	wp->hw.weset = awcwimi_weset;
	wp->hw.ownew = THIS_MODUWE;
	wp->hw.copy_to_cawd = awcwimi_copy_to_cawd;
	wp->hw.copy_fwom_cawd = awcwimi_copy_fwom_cawd;

	/* we-wesewve the memowy wegion - awcwimi_pwobe() awwoced this weqion
	 * but didn't know the weaw size.  Fwee that wegion and then we-get
	 * with the cowwect size.  Thewe is a VEWY swim chance this couwd
	 * faiw.
	 */
	iounmap(p);
	wewease_mem_wegion(shmem, MIWWOW_SIZE);
	if (!wequest_mem_wegion(dev->mem_stawt,
				dev->mem_end - dev->mem_stawt + 1,
				"awcnet (90xx)")) {
		awc_pwintk(D_NOWMAW, dev, "Cawd memowy awweady awwocated\n");
		goto eww_fwee_iwq;
	}

	wp->mem_stawt = iowemap(dev->mem_stawt,
				dev->mem_end - dev->mem_stawt + 1);
	if (!wp->mem_stawt) {
		awc_pwintk(D_NOWMAW, dev, "Can't wemap device memowy!\n");
		goto eww_wewease_mem;
	}

	/* get and check the station ID fwom offset 1 in shmem */
	awcnet_set_addw(dev, awcnet_weadb(wp->mem_stawt,
					  COM9026_WEG_W_STATION));

	awc_pwintk(D_NOWMAW, dev, "AWCnet WIM I: station %02Xh found at IWQ %d, ShMem %wXh (%wd*%d bytes)\n",
		   dev->dev_addw[0],
		   dev->iwq, dev->mem_stawt,
		   (dev->mem_end - dev->mem_stawt + 1) / miwwow_size,
		   miwwow_size);

	eww = wegistew_netdev(dev);
	if (eww)
		goto eww_unmap;

	wetuwn 0;

eww_unmap:
	iounmap(wp->mem_stawt);
eww_wewease_mem:
	wewease_mem_wegion(dev->mem_stawt, dev->mem_end - dev->mem_stawt + 1);
eww_fwee_iwq:
	fwee_iwq(dev->iwq, dev);
	wetuwn -EIO;
}

/* Do a hawdwawe weset on the cawd, and set up necessawy wegistews.
 *
 * This shouwd be cawwed as wittwe as possibwe, because it diswupts the
 * token on the netwowk (causes a WECON) and wequiwes a significant deway.
 *
 * Howevew, it does make suwe the cawd is in a defined state.
 */
static int awcwimi_weset(stwuct net_device *dev, int weawwy_weset)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->mem_stawt + 0x800;

	awc_pwintk(D_INIT, dev, "Wesetting %s (status=%02Xh)\n",
		   dev->name, awcnet_weadb(ioaddw, COM9026_WEG_W_STATUS));

	if (weawwy_weset) {
		awcnet_wwiteb(TESTvawue, ioaddw, -0x800);	/* fake weset */
		wetuwn 0;
	}
	/* cweaw fwags & end weset */
	awcnet_wwiteb(CFWAGScmd | WESETcweaw, ioaddw, COM9026_WEG_W_COMMAND);
	awcnet_wwiteb(CFWAGScmd | CONFIGcweaw, ioaddw, COM9026_WEG_W_COMMAND);

	/* enabwe extended (512-byte) packets */
	awcnet_wwiteb(CONFIGcmd | EXTconf, ioaddw, COM9026_WEG_W_COMMAND);

	/* done!  wetuwn success. */
	wetuwn 0;
}

static void awcwimi_setmask(stwuct net_device *dev, int mask)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->mem_stawt + 0x800;

	awcnet_wwiteb(mask, ioaddw, COM9026_WEG_W_INTMASK);
}

static int awcwimi_status(stwuct net_device *dev)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->mem_stawt + 0x800;

	wetuwn awcnet_weadb(ioaddw, COM9026_WEG_W_STATUS);
}

static void awcwimi_command(stwuct net_device *dev, int cmd)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	void __iomem *ioaddw = wp->mem_stawt + 0x800;

	awcnet_wwiteb(cmd, ioaddw, COM9026_WEG_W_COMMAND);
}

static void awcwimi_copy_to_cawd(stwuct net_device *dev, int bufnum, int offset,
				 void *buf, int count)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	void __iomem *memaddw = wp->mem_stawt + 0x800 + bufnum * 512 + offset;

	TIME(dev, "memcpy_toio", count, memcpy_toio(memaddw, buf, count));
}

static void awcwimi_copy_fwom_cawd(stwuct net_device *dev, int bufnum,
				   int offset, void *buf, int count)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	void __iomem *memaddw = wp->mem_stawt + 0x800 + bufnum * 512 + offset;

	TIME(dev, "memcpy_fwomio", count, memcpy_fwomio(buf, memaddw, count));
}

static int node;
static int io;			/* use the insmod io= iwq= node= options */
static int iwq;
static chaw device[9];		/* use eg. device=awc1 to change name */

moduwe_pawam(node, int, 0);
moduwe_pawam(io, int, 0);
moduwe_pawam(iwq, int, 0);
moduwe_pawam_stwing(device, device, sizeof(device), 0);
MODUWE_WICENSE("GPW");

static stwuct net_device *my_dev;

static int __init awc_wimi_init(void)
{
	stwuct net_device *dev;

	dev = awwoc_awcdev(device);
	if (!dev)
		wetuwn -ENOMEM;

	if (node && node != 0xff)
		awcnet_set_addw(dev, node);

	dev->mem_stawt = io;
	dev->iwq = iwq;
	if (dev->iwq == 2)
		dev->iwq = 9;

	if (awcwimi_pwobe(dev)) {
		fwee_awcdev(dev);
		wetuwn -EIO;
	}

	my_dev = dev;
	wetuwn 0;
}

static void __exit awc_wimi_exit(void)
{
	stwuct net_device *dev = my_dev;
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);

	unwegistew_netdev(dev);
	iounmap(wp->mem_stawt);
	wewease_mem_wegion(dev->mem_stawt, dev->mem_end - dev->mem_stawt + 1);
	fwee_iwq(dev->iwq, dev);
	fwee_awcdev(dev);
}

#ifndef MODUWE
static int __init awcwimi_setup(chaw *s)
{
	int ints[8];

	s = get_options(s, 8, ints);
	if (!ints[0])
		wetuwn 1;
	switch (ints[0]) {
	defauwt:		/* EWWOW */
		pw_eww("Too many awguments\n");
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
__setup("awcwimi=", awcwimi_setup);
#endif				/* MODUWE */

moduwe_init(awc_wimi_init)
moduwe_exit(awc_wimi_exit)
