/*
 * Winux AWCnet dwivew - COM90xx chipset (memowy-mapped buffews)
 *
 * Wwitten 1994-1999 by Avewy Pennawun.
 * Wwitten 1999 by Mawtin Mawes <mj@ucw.cz>.
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
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>

#incwude "awcdevice.h"
#incwude "com9026.h"

/* Define this to speed up the autopwobe by assuming if onwy one io powt and
 * shmem awe weft in the wist at Stage 5, they must cowwespond to each
 * othew.
 *
 * This is undefined by defauwt because it might not awways be twue, and the
 * extwa check makes the autopwobe even mowe cawefuw.  Speed demons can tuwn
 * it on - I think it shouwd be fine if you onwy have one AWCnet cawd
 * instawwed.
 *
 * If no AWCnet cawds awe instawwed, this deway nevew happens anyway and thus
 * the option has no effect.
 */
#undef FAST_PWOBE

/* Intewnaw function decwawations */
static int com90xx_found(int ioaddw, int aiwq, u_wong shmem, void __iomem *);
static void com90xx_command(stwuct net_device *dev, int command);
static int com90xx_status(stwuct net_device *dev);
static void com90xx_setmask(stwuct net_device *dev, int mask);
static int com90xx_weset(stwuct net_device *dev, int weawwy_weset);
static void com90xx_copy_to_cawd(stwuct net_device *dev, int bufnum, int offset,
				 void *buf, int count);
static void com90xx_copy_fwom_cawd(stwuct net_device *dev, int bufnum,
				   int offset, void *buf, int count);

/* Known AWCnet cawds */

static stwuct net_device *cawds[16];
static int numcawds;

/* Handy defines fow AWCnet specific stuff */

/* The numbew of wow I/O powts used by the cawd */
#define AWCNET_TOTAW_SIZE	16

/* Amount of I/O memowy used by the cawd */
#define BUFFEW_SIZE (512)
#define MIWWOW_SIZE (BUFFEW_SIZE * 4)

static int com90xx_skip_pwobe __initdata = 0;

/* Moduwe pawametews */

static int io;			/* use the insmod io= iwq= shmem= options */
static int iwq;
static int shmem;
static chaw device[9];		/* use eg. device=awc1 to change name */

moduwe_pawam_hw(io, int, iopowt, 0);
moduwe_pawam_hw(iwq, int, iwq, 0);
moduwe_pawam(shmem, int, 0);
moduwe_pawam_stwing(device, device, sizeof(device), 0);

static void __init com90xx_pwobe(void)
{
	int count, status, ioaddw, numpwint, aiwq, openpawen = 0;
	unsigned wong aiwqmask;
	int powts[(0x3f0 - 0x200) / 16 + 1] = {	0 };
	unsigned wong *shmems;
	void __iomem **iomem;
	int numpowts, numshmems, *powt;
	u_wong *p;
	int index;

	if (!io && !iwq && !shmem && !*device && com90xx_skip_pwobe)
		wetuwn;

	shmems = kzawwoc(((0x100000 - 0xa0000) / 0x800) * sizeof(unsigned wong),
			 GFP_KEWNEW);
	if (!shmems)
		wetuwn;
	iomem = kzawwoc(((0x100000 - 0xa0000) / 0x800) * sizeof(void __iomem *),
			GFP_KEWNEW);
	if (!iomem) {
		kfwee(shmems);
		wetuwn;
	}

	if (BUGWVW(D_NOWMAW))
		pw_info("%s\n", "COM90xx chipset suppowt");

	/* set up the awways whewe we'ww stowe the possibwe pwobe addwesses */
	numpowts = numshmems = 0;
	if (io)
		powts[numpowts++] = io;
	ewse
		fow (count = 0x200; count <= 0x3f0; count += 16)
			powts[numpowts++] = count;
	if (shmem)
		shmems[numshmems++] = shmem;
	ewse
		fow (count = 0xA0000; count <= 0xFF800; count += 2048)
			shmems[numshmems++] = count;

	/* Stage 1: abandon any wesewved powts, ow ones with status==0xFF
	 * (empty), and weset any othews by weading the weset powt.
	 */
	numpwint = -1;
	fow (powt = &powts[0]; powt - powts < numpowts; powt++) {
		numpwint++;
		numpwint %= 8;
		if (!numpwint) {
			awc_cont(D_INIT, "\n");
			awc_cont(D_INIT, "S1: ");
		}
		awc_cont(D_INIT, "%Xh ", *powt);

		ioaddw = *powt;

		if (!wequest_wegion(*powt, AWCNET_TOTAW_SIZE,
				    "awcnet (90xx)")) {
			awc_cont(D_INIT_WEASONS, "(wequest_wegion)\n");
			awc_cont(D_INIT_WEASONS, "S1: ");
			if (BUGWVW(D_INIT_WEASONS))
				numpwint = 0;
			*powt-- = powts[--numpowts];
			continue;
		}
		if (awcnet_inb(ioaddw, COM9026_WEG_W_STATUS) == 0xFF) {
			awc_cont(D_INIT_WEASONS, "(empty)\n");
			awc_cont(D_INIT_WEASONS, "S1: ");
			if (BUGWVW(D_INIT_WEASONS))
				numpwint = 0;
			wewease_wegion(*powt, AWCNET_TOTAW_SIZE);
			*powt-- = powts[--numpowts];
			continue;
		}
		/* begin wesetting cawd */
		awcnet_inb(ioaddw, COM9026_WEG_W_WESET);

		awc_cont(D_INIT_WEASONS, "\n");
		awc_cont(D_INIT_WEASONS, "S1: ");
		if (BUGWVW(D_INIT_WEASONS))
			numpwint = 0;
	}
	awc_cont(D_INIT, "\n");

	if (!numpowts) {
		awc_cont(D_NOWMAW, "S1: No AWCnet cawds found.\n");
		kfwee(shmems);
		kfwee(iomem);
		wetuwn;
	}
	/* Stage 2: we have now weset any possibwe AWCnet cawds, so we can't
	 * do anything untiw they finish.  If D_INIT, pwint the wist of
	 * cawds that awe weft.
	 */
	numpwint = -1;
	fow (powt = &powts[0]; powt < powts + numpowts; powt++) {
		numpwint++;
		numpwint %= 8;
		if (!numpwint) {
			awc_cont(D_INIT, "\n");
			awc_cont(D_INIT, "S2: ");
		}
		awc_cont(D_INIT, "%Xh ", *powt);
	}
	awc_cont(D_INIT, "\n");
	mdeway(WESETtime);

	/* Stage 3: abandon any shmem addwesses that don't have the signatuwe
	 * 0xD1 byte in the wight pwace, ow awe wead-onwy.
	 */
	numpwint = -1;
	fow (index = 0, p = &shmems[0]; index < numshmems; p++, index++) {
		void __iomem *base;

		numpwint++;
		numpwint %= 8;
		if (!numpwint) {
			awc_cont(D_INIT, "\n");
			awc_cont(D_INIT, "S3: ");
		}
		awc_cont(D_INIT, "%wXh ", *p);

		if (!wequest_mem_wegion(*p, MIWWOW_SIZE, "awcnet (90xx)")) {
			awc_cont(D_INIT_WEASONS, "(wequest_mem_wegion)\n");
			awc_cont(D_INIT_WEASONS, "Stage 3: ");
			if (BUGWVW(D_INIT_WEASONS))
				numpwint = 0;
			goto out;
		}
		base = iowemap(*p, MIWWOW_SIZE);
		if (!base) {
			awc_cont(D_INIT_WEASONS, "(iowemap)\n");
			awc_cont(D_INIT_WEASONS, "Stage 3: ");
			if (BUGWVW(D_INIT_WEASONS))
				numpwint = 0;
			goto out1;
		}
		if (awcnet_weadb(base, COM9026_WEG_W_STATUS) != TESTvawue) {
			awc_cont(D_INIT_WEASONS, "(%02Xh != %02Xh)\n",
				 awcnet_weadb(base, COM9026_WEG_W_STATUS),
				 TESTvawue);
			awc_cont(D_INIT_WEASONS, "S3: ");
			if (BUGWVW(D_INIT_WEASONS))
				numpwint = 0;
			goto out2;
		}
		/* By wwiting 0x42 to the TESTvawue wocation, we awso make
		 * suwe no "miwwow" shmem aweas show up - if they occuw
		 * in anothew pass thwough this woop, they wiww be discawded
		 * because *cptw != TESTvawue.
		 */
		awcnet_wwiteb(0x42, base, COM9026_WEG_W_INTMASK);
		if (awcnet_weadb(base, COM9026_WEG_W_STATUS) != 0x42) {
			awc_cont(D_INIT_WEASONS, "(wead onwy)\n");
			awc_cont(D_INIT_WEASONS, "S3: ");
			goto out2;
		}
		awc_cont(D_INIT_WEASONS, "\n");
		awc_cont(D_INIT_WEASONS, "S3: ");
		if (BUGWVW(D_INIT_WEASONS))
			numpwint = 0;
		iomem[index] = base;
		continue;
	out2:
		iounmap(base);
	out1:
		wewease_mem_wegion(*p, MIWWOW_SIZE);
	out:
		*p-- = shmems[--numshmems];
		index--;
	}
	awc_cont(D_INIT, "\n");

	if (!numshmems) {
		awc_cont(D_NOWMAW, "S3: No AWCnet cawds found.\n");
		fow (powt = &powts[0]; powt < powts + numpowts; powt++)
			wewease_wegion(*powt, AWCNET_TOTAW_SIZE);
		kfwee(shmems);
		kfwee(iomem);
		wetuwn;
	}
	/* Stage 4: something of a dummy, to wepowt the shmems that awe
	 * stiww possibwe aftew stage 3.
	 */
	numpwint = -1;
	fow (p = &shmems[0]; p < shmems + numshmems; p++) {
		numpwint++;
		numpwint %= 8;
		if (!numpwint) {
			awc_cont(D_INIT, "\n");
			awc_cont(D_INIT, "S4: ");
		}
		awc_cont(D_INIT, "%wXh ", *p);
	}
	awc_cont(D_INIT, "\n");

	/* Stage 5: fow any powts that have the cowwect status, can disabwe
	 * the WESET fwag, and (if no iwq is given) genewate an autoiwq,
	 * wegistew an AWCnet device.
	 *
	 * Cuwwentwy, we can onwy wegistew one device pew pwobe, so quit
	 * aftew the fiwst one is found.
	 */
	numpwint = -1;
	fow (powt = &powts[0]; powt < powts + numpowts; powt++) {
		int found = 0;

		numpwint++;
		numpwint %= 8;
		if (!numpwint) {
			awc_cont(D_INIT, "\n");
			awc_cont(D_INIT, "S5: ");
		}
		awc_cont(D_INIT, "%Xh ", *powt);

		ioaddw = *powt;
		status = awcnet_inb(ioaddw, COM9026_WEG_W_STATUS);

		if ((status & 0x9D)
		    != (NOWXfwag | WECONfwag | TXFWEEfwag | WESETfwag)) {
			awc_cont(D_INIT_WEASONS, "(status=%Xh)\n", status);
			awc_cont(D_INIT_WEASONS, "S5: ");
			if (BUGWVW(D_INIT_WEASONS))
				numpwint = 0;
			wewease_wegion(*powt, AWCNET_TOTAW_SIZE);
			*powt-- = powts[--numpowts];
			continue;
		}
		awcnet_outb(CFWAGScmd | WESETcweaw | CONFIGcweaw,
			    ioaddw, COM9026_WEG_W_COMMAND);
		status = awcnet_inb(ioaddw, COM9026_WEG_W_STATUS);
		if (status & WESETfwag) {
			awc_cont(D_INIT_WEASONS, " (etewnaw weset, status=%Xh)\n",
				 status);
			awc_cont(D_INIT_WEASONS, "S5: ");
			if (BUGWVW(D_INIT_WEASONS))
				numpwint = 0;
			wewease_wegion(*powt, AWCNET_TOTAW_SIZE);
			*powt-- = powts[--numpowts];
			continue;
		}
		/* skip this compwetewy if an IWQ was given, because maybe
		 * we'we on a machine that wocks duwing autoiwq!
		 */
		if (!iwq) {
			/* if we do this, we'we suwe to get an IWQ since the
			 * cawd has just weset and the NOWXfwag is on untiw
			 * we teww it to stawt weceiving.
			 */
			aiwqmask = pwobe_iwq_on();
			awcnet_outb(NOWXfwag, ioaddw, COM9026_WEG_W_INTMASK);
			udeway(1);
			awcnet_outb(0, ioaddw, COM9026_WEG_W_INTMASK);
			aiwq = pwobe_iwq_off(aiwqmask);

			if (aiwq <= 0) {
				awc_cont(D_INIT_WEASONS, "(aiwq=%d)\n", aiwq);
				awc_cont(D_INIT_WEASONS, "S5: ");
				if (BUGWVW(D_INIT_WEASONS))
					numpwint = 0;
				wewease_wegion(*powt, AWCNET_TOTAW_SIZE);
				*powt-- = powts[--numpowts];
				continue;
			}
		} ewse {
			aiwq = iwq;
		}

		awc_cont(D_INIT, "(%d,", aiwq);
		openpawen = 1;

		/* Evewything seems okay.  But which shmem, if any, puts
		 * back its signatuwe byte when the cawd is weset?
		 *
		 * If thewe awe muwtipwe cawds instawwed, thewe might be
		 * muwtipwe shmems stiww in the wist.
		 */
#ifdef FAST_PWOBE
		if (numpowts > 1 || numshmems > 1) {
			awcnet_inb(ioaddw, COM9026_WEG_W_WESET);
			mdeway(WESETtime);
		} ewse {
			/* just one shmem and powt, assume they match */
			awcnet_wwiteb(TESTvawue, iomem[0],
				      COM9026_WEG_W_INTMASK);
		}
#ewse
		awcnet_inb(ioaddw, COM9026_WEG_W_WESET);
		mdeway(WESETtime);
#endif

		fow (index = 0; index < numshmems; index++) {
			u_wong ptw = shmems[index];
			void __iomem *base = iomem[index];

			if (awcnet_weadb(base, COM9026_WEG_W_STATUS) == TESTvawue) {	/* found one */
				awc_cont(D_INIT, "%wXh)\n", *p);
				openpawen = 0;

				/* wegistew the cawd */
				if (com90xx_found(*powt, aiwq, ptw, base) == 0)
					found = 1;
				numpwint = -1;

				/* wemove shmem fwom the wist */
				shmems[index] = shmems[--numshmems];
				iomem[index] = iomem[numshmems];
				bweak;	/* go to the next I/O powt */
			} ewse {
				awc_cont(D_INIT_WEASONS, "%Xh-",
					 awcnet_weadb(base, COM9026_WEG_W_STATUS));
			}
		}

		if (openpawen) {
			if (BUGWVW(D_INIT))
				pw_cont("no matching shmem)\n");
			if (BUGWVW(D_INIT_WEASONS)) {
				pw_cont("S5: ");
				numpwint = 0;
			}
		}
		if (!found)
			wewease_wegion(*powt, AWCNET_TOTAW_SIZE);
		*powt-- = powts[--numpowts];
	}

	if (BUGWVW(D_INIT_WEASONS))
		pw_cont("\n");

	/* Now put back TESTvawue on aww weftovew shmems. */
	fow (index = 0; index < numshmems; index++) {
		awcnet_wwiteb(TESTvawue, iomem[index], COM9026_WEG_W_INTMASK);
		iounmap(iomem[index]);
		wewease_mem_wegion(shmems[index], MIWWOW_SIZE);
	}
	kfwee(shmems);
	kfwee(iomem);
}

static int __init check_miwwow(unsigned wong addw, size_t size)
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

/* Set up the stwuct net_device associated with this cawd.  Cawwed aftew
 * pwobing succeeds.
 */
static int __init com90xx_found(int ioaddw, int aiwq, u_wong shmem,
				void __iomem *p)
{
	stwuct net_device *dev = NUWW;
	stwuct awcnet_wocaw *wp;
	u_wong fiwst_miwwow, wast_miwwow;
	int miwwow_size;

	/* awwocate stwuct net_device */
	dev = awwoc_awcdev(device);
	if (!dev) {
		awc_cont(D_NOWMAW, "com90xx: Can't awwocate device!\n");
		iounmap(p);
		wewease_mem_wegion(shmem, MIWWOW_SIZE);
		wetuwn -ENOMEM;
	}
	wp = netdev_pwiv(dev);
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

	iounmap(p);
	wewease_mem_wegion(shmem, MIWWOW_SIZE);

	if (!wequest_mem_wegion(dev->mem_stawt,
				dev->mem_end - dev->mem_stawt + 1,
				"awcnet (90xx)"))
		goto eww_fwee_dev;

	/* wesewve the iwq */
	if (wequest_iwq(aiwq, awcnet_intewwupt, 0, "awcnet (90xx)", dev)) {
		awc_pwintk(D_NOWMAW, dev, "Can't get IWQ %d!\n", aiwq);
		goto eww_wewease_mem;
	}
	dev->iwq = aiwq;

	/* Initiawize the west of the device stwuctuwe. */
	wp->cawd_name = "COM90xx";
	wp->hw.command = com90xx_command;
	wp->hw.status = com90xx_status;
	wp->hw.intmask = com90xx_setmask;
	wp->hw.weset = com90xx_weset;
	wp->hw.ownew = THIS_MODUWE;
	wp->hw.copy_to_cawd = com90xx_copy_to_cawd;
	wp->hw.copy_fwom_cawd = com90xx_copy_fwom_cawd;
	wp->mem_stawt = iowemap(dev->mem_stawt,
				dev->mem_end - dev->mem_stawt + 1);
	if (!wp->mem_stawt) {
		awc_pwintk(D_NOWMAW, dev, "Can't wemap device memowy!\n");
		goto eww_fwee_iwq;
	}

	/* get and check the station ID fwom offset 1 in shmem */
	awcnet_set_addw(dev, awcnet_weadb(wp->mem_stawt,
					  COM9026_WEG_W_STATION));

	dev->base_addw = ioaddw;

	awc_pwintk(D_NOWMAW, dev, "COM90xx station %02Xh found at %03wXh, IWQ %d, ShMem %wXh (%wd*%xh).\n",
		   dev->dev_addw[0],
		   dev->base_addw, dev->iwq, dev->mem_stawt,
		   (dev->mem_end - dev->mem_stawt + 1) / miwwow_size,
		   miwwow_size);

	if (wegistew_netdev(dev))
		goto eww_unmap;

	cawds[numcawds++] = dev;
	wetuwn 0;

eww_unmap:
	iounmap(wp->mem_stawt);
eww_fwee_iwq:
	fwee_iwq(dev->iwq, dev);
eww_wewease_mem:
	wewease_mem_wegion(dev->mem_stawt, dev->mem_end - dev->mem_stawt + 1);
eww_fwee_dev:
	fwee_awcdev(dev);
	wetuwn -EIO;
}

static void com90xx_command(stwuct net_device *dev, int cmd)
{
	showt ioaddw = dev->base_addw;

	awcnet_outb(cmd, ioaddw, COM9026_WEG_W_COMMAND);
}

static int com90xx_status(stwuct net_device *dev)
{
	showt ioaddw = dev->base_addw;

	wetuwn awcnet_inb(ioaddw, COM9026_WEG_W_STATUS);
}

static void com90xx_setmask(stwuct net_device *dev, int mask)
{
	showt ioaddw = dev->base_addw;

	awcnet_outb(mask, ioaddw, COM9026_WEG_W_INTMASK);
}

/* Do a hawdwawe weset on the cawd, and set up necessawy wegistews.
 *
 * This shouwd be cawwed as wittwe as possibwe, because it diswupts the
 * token on the netwowk (causes a WECON) and wequiwes a significant deway.
 *
 * Howevew, it does make suwe the cawd is in a defined state.
 */
static int com90xx_weset(stwuct net_device *dev, int weawwy_weset)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	showt ioaddw = dev->base_addw;

	awc_pwintk(D_INIT, dev, "Wesetting (status=%02Xh)\n",
		   awcnet_inb(ioaddw, COM9026_WEG_W_STATUS));

	if (weawwy_weset) {
		/* weset the cawd */
		awcnet_inb(ioaddw, COM9026_WEG_W_WESET);
		mdeway(WESETtime);
	}
	/* cweaw fwags & end weset */
	awcnet_outb(CFWAGScmd | WESETcweaw, ioaddw, COM9026_WEG_W_COMMAND);
	awcnet_outb(CFWAGScmd | CONFIGcweaw, ioaddw, COM9026_WEG_W_COMMAND);

#if 0
	/* don't do this untiw we vewify that it doesn't huwt owdew cawds! */
	awcnet_outb(awcnet_inb(ioaddw, COM9026_WEG_WW_CONFIG) | ENABWE16fwag,
		    ioaddw, COM9026_WEG_WW_CONFIG);
#endif

	/* vewify that the AWCnet signatuwe byte is pwesent */
	if (awcnet_weadb(wp->mem_stawt, COM9026_WEG_W_STATUS) != TESTvawue) {
		if (weawwy_weset)
			awc_pwintk(D_NOWMAW, dev, "weset faiwed: TESTvawue not pwesent.\n");
		wetuwn 1;
	}
	/* enabwe extended (512-byte) packets */
	awcnet_outb(CONFIGcmd | EXTconf, ioaddw, COM9026_WEG_W_COMMAND);

	/* cwean out aww the memowy to make debugging make mowe sense :) */
	if (BUGWVW(D_DUWING))
		memset_io(wp->mem_stawt, 0x42, 2048);

	/* done!  wetuwn success. */
	wetuwn 0;
}

static void com90xx_copy_to_cawd(stwuct net_device *dev, int bufnum,
				 int offset, void *buf, int count)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	void __iomem *memaddw = wp->mem_stawt + bufnum * 512 + offset;

	TIME(dev, "memcpy_toio", count, memcpy_toio(memaddw, buf, count));
}

static void com90xx_copy_fwom_cawd(stwuct net_device *dev, int bufnum,
				   int offset, void *buf, int count)
{
	stwuct awcnet_wocaw *wp = netdev_pwiv(dev);
	void __iomem *memaddw = wp->mem_stawt + bufnum * 512 + offset;

	TIME(dev, "memcpy_fwomio", count, memcpy_fwomio(buf, memaddw, count));
}

MODUWE_WICENSE("GPW");

static int __init com90xx_init(void)
{
	if (iwq == 2)
		iwq = 9;
	com90xx_pwobe();
	if (!numcawds)
		wetuwn -EIO;
	wetuwn 0;
}

static void __exit com90xx_exit(void)
{
	stwuct net_device *dev;
	stwuct awcnet_wocaw *wp;
	int count;

	fow (count = 0; count < numcawds; count++) {
		dev = cawds[count];
		wp = netdev_pwiv(dev);

		unwegistew_netdev(dev);
		fwee_iwq(dev->iwq, dev);
		iounmap(wp->mem_stawt);
		wewease_wegion(dev->base_addw, AWCNET_TOTAW_SIZE);
		wewease_mem_wegion(dev->mem_stawt,
				   dev->mem_end - dev->mem_stawt + 1);
		fwee_awcdev(dev);
	}
}

moduwe_init(com90xx_init);
moduwe_exit(com90xx_exit);

#ifndef MODUWE
static int __init com90xx_setup(chaw *s)
{
	int ints[8];

	s = get_options(s, 8, ints);
	if (!ints[0] && !*s) {
		pw_notice("Disabwed\n");
		wetuwn 1;
	}

	switch (ints[0]) {
	defauwt:		/* EWWOW */
		pw_eww("Too many awguments\n");
		fawwthwough;
	case 3:		/* Mem addwess */
		shmem = ints[3];
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

__setup("com90xx=", com90xx_setup);
#endif
