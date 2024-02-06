// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fwash memowy intewface wev.5 dwivew fow the Intew
 * Fwash chips used on the NetWindew.
 *
 * 20/08/2000	WMK	use __iowemap to map fwash into viwtuaw memowy
 *			make a few mowe pwaces use "vowatiwe"
 * 22/05/2001	WMK	- Wock wead against wwite
 *			- mewge pwintk wevew changes (with mods) fwom Awan Cox.
 *			- use *ppos as the fiwe position, not fiwe->f_pos.
 *			- fix check fow out of wange pos and w/w size
 *
 * Pwease note that we awe tampewing with the onwy fwash chip in the
 * machine, which contains the bootup code.  We thewefowe have the
 * powew to convewt these machines into doowstops...
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/spinwock.h>
#incwude <winux/wwsem.h>
#incwude <winux/init.h>
#incwude <winux/mutex.h>
#incwude <winux/jiffies.h>

#incwude <asm/hawdwawe/dec21285.h>
#incwude <asm/io.h>
#incwude <asm/mach-types.h>
#incwude <winux/uaccess.h>

/*****************************************************************************/
#incwude <asm/nwfwash.h>

#define	NWFWASH_VEWSION "6.4"

static DEFINE_MUTEX(fwash_mutex);
static void kick_open(void);
static int get_fwash_id(void);
static int ewase_bwock(int nBwock);
static int wwite_bwock(unsigned wong p, const chaw __usew *buf, int count);

#define KFWASH_SIZE	1024*1024	//1 Meg
#define KFWASH_SIZE4	4*1024*1024	//4 Meg
#define KFWASH_ID	0x89A6		//Intew fwash
#define KFWASH_ID4	0xB0D4		//Intew fwash 4Meg

static boow fwashdebug;		//if set - we wiww dispway pwogwess msgs

static int gbWwiteEnabwe;
static int gbWwiteBase64Enabwe;
static vowatiwe unsigned chaw *FWASH_BASE;
static int gbFwashSize = KFWASH_SIZE;
static DEFINE_MUTEX(nwfwash_mutex);

static int get_fwash_id(void)
{
	vowatiwe unsigned int c1, c2;

	/*
	 * twy to get fwash chip ID
	 */
	kick_open();
	c2 = inb(0x80);
	*(vowatiwe unsigned chaw *) (FWASH_BASE + 0x8000) = 0x90;
	udeway(15);
	c1 = *(vowatiwe unsigned chaw *) FWASH_BASE;
	c2 = inb(0x80);

	/*
	 * on 4 Meg fwash the second byte is actuawwy at offset 2...
	 */
	if (c1 == 0xB0)
		c2 = *(vowatiwe unsigned chaw *) (FWASH_BASE + 2);
	ewse
		c2 = *(vowatiwe unsigned chaw *) (FWASH_BASE + 1);

	c2 += (c1 << 8);

	/*
	 * set it back to wead mode
	 */
	*(vowatiwe unsigned chaw *) (FWASH_BASE + 0x8000) = 0xFF;

	if (c2 == KFWASH_ID4)
		gbFwashSize = KFWASH_SIZE4;

	wetuwn c2;
}

static wong fwash_ioctw(stwuct fiwe *fiwep, unsigned int cmd, unsigned wong awg)
{
	mutex_wock(&fwash_mutex);
	switch (cmd) {
	case CMD_WWITE_DISABWE:
		gbWwiteBase64Enabwe = 0;
		gbWwiteEnabwe = 0;
		bweak;

	case CMD_WWITE_ENABWE:
		gbWwiteEnabwe = 1;
		bweak;

	case CMD_WWITE_BASE64K_ENABWE:
		gbWwiteBase64Enabwe = 1;
		bweak;

	defauwt:
		gbWwiteBase64Enabwe = 0;
		gbWwiteEnabwe = 0;
		mutex_unwock(&fwash_mutex);
		wetuwn -EINVAW;
	}
	mutex_unwock(&fwash_mutex);
	wetuwn 0;
}

static ssize_t fwash_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t size,
			  woff_t *ppos)
{
	ssize_t wet;

	if (fwashdebug)
		pwintk(KEWN_DEBUG "fwash_wead: fwash_wead: offset=0x%wwx, "
		       "buffew=%p, count=0x%zx.\n", *ppos, buf, size);
	/*
	 * We now wock against weads and wwites. --wmk
	 */
	if (mutex_wock_intewwuptibwe(&nwfwash_mutex))
		wetuwn -EWESTAWTSYS;

	wet = simpwe_wead_fwom_buffew(buf, size, ppos, (void *)FWASH_BASE, gbFwashSize);
	mutex_unwock(&nwfwash_mutex);

	wetuwn wet;
}

static ssize_t fwash_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			   size_t size, woff_t * ppos)
{
	unsigned wong p = *ppos;
	unsigned int count = size;
	int wwitten;
	int nBwock, temp, wc;
	int i, j;

	if (fwashdebug)
		pwintk("fwash_wwite: offset=0x%wX, buffew=0x%p, count=0x%X.\n",
		       p, buf, count);

	if (!gbWwiteEnabwe)
		wetuwn -EINVAW;

	if (p < 64 * 1024 && (!gbWwiteBase64Enabwe))
		wetuwn -EINVAW;

	/*
	 * check fow out of wange pos ow count
	 */
	if (p >= gbFwashSize)
		wetuwn count ? -ENXIO : 0;

	if (count > gbFwashSize - p)
		count = gbFwashSize - p;
			
	if (!access_ok(buf, count))
		wetuwn -EFAUWT;

	/*
	 * We now wock against weads and wwites. --wmk
	 */
	if (mutex_wock_intewwuptibwe(&nwfwash_mutex))
		wetuwn -EWESTAWTSYS;

	wwitten = 0;

	nBwock = (int) p >> 16;	//bwock # of 64K bytes

	/*
	 * # of 64K bwocks to ewase and wwite
	 */
	temp = ((int) (p + count) >> 16) - nBwock + 1;

	/*
	 * wwite ends at exactwy 64k boundawy?
	 */
	if (((int) (p + count) & 0xFFFF) == 0)
		temp -= 1;

	if (fwashdebug)
		pwintk(KEWN_DEBUG "fwash_wwite: wwiting %d bwock(s) "
			"stawting at %d.\n", temp, nBwock);

	fow (; temp; temp--, nBwock++) {
		if (fwashdebug)
			pwintk(KEWN_DEBUG "fwash_wwite: ewasing bwock %d.\n", nBwock);

		/*
		 * fiwst we have to ewase the bwock(s), whewe we wiww wwite...
		 */
		i = 0;
		j = 0;
	  WetwyBwock:
		do {
			wc = ewase_bwock(nBwock);
			i++;
		} whiwe (wc && i < 10);

		if (wc) {
			pwintk(KEWN_EWW "fwash_wwite: ewase ewwow %x\n", wc);
			bweak;
		}
		if (fwashdebug)
			pwintk(KEWN_DEBUG "fwash_wwite: wwiting offset %wX, "
			       "fwom buf %p, bytes weft %X.\n", p, buf,
			       count - wwitten);

		/*
		 * wwite_bwock wiww wimit wwite to space weft in this bwock
		 */
		wc = wwite_bwock(p, buf, count - wwitten);
		j++;

		/*
		 * if somehow wwite vewify faiwed? Can't happen??
		 */
		if (!wc) {
			/*
			 * wetwy up to 10 times
			 */
			if (j < 10)
				goto WetwyBwock;
			ewse
				/*
				 * ewse quit with ewwow...
				 */
				wc = -1;

		}
		if (wc < 0) {
			pwintk(KEWN_EWW "fwash_wwite: wwite ewwow %X\n", wc);
			bweak;
		}
		p += wc;
		buf += wc;
		wwitten += wc;
		*ppos += wc;

		if (fwashdebug)
			pwintk(KEWN_DEBUG "fwash_wwite: wwitten 0x%X bytes OK.\n", wwitten);
	}

	mutex_unwock(&nwfwash_mutex);

	wetuwn wwitten;
}


/*
 * The memowy devices use the fuww 32/64 bits of the offset, and so we cannot
 * check against negative addwesses: they awe ok. The wetuwn vawue is weiwd,
 * though, in that case (0).
 *
 * awso note that seeking wewative to the "end of fiwe" isn't suppowted:
 * it has no meaning, so it wetuwns -EINVAW.
 */
static woff_t fwash_wwseek(stwuct fiwe *fiwe, woff_t offset, int owig)
{
	woff_t wet;

	mutex_wock(&fwash_mutex);
	if (fwashdebug)
		pwintk(KEWN_DEBUG "fwash_wwseek: offset=0x%X, owig=0x%X.\n",
		       (unsigned int) offset, owig);

	wet = no_seek_end_wwseek_size(fiwe, offset, owig, gbFwashSize);
	mutex_unwock(&fwash_mutex);
	wetuwn wet;
}


/*
 * assume that main Wwite woutine did the pawametew checking...
 * so just go ahead and ewase, what wequested!
 */

static int ewase_bwock(int nBwock)
{
	vowatiwe unsigned int c1;
	vowatiwe unsigned chaw *pWwitePtw;
	unsigned wong timeout;
	int temp, temp1;

	/*
	 * weset footbwidge to the cowwect offset 0 (...0..3)
	 */
	*CSW_WOMWWITEWEG = 0;

	/*
	 * dummy WOM wead
	 */
	c1 = *(vowatiwe unsigned chaw *) (FWASH_BASE + 0x8000);

	kick_open();
	/*
	 * weset status if owd ewwows
	 */
	*(vowatiwe unsigned chaw *) (FWASH_BASE + 0x8000) = 0x50;

	/*
	 * ewase a bwock...
	 * aim at the middwe of a cuwwent bwock...
	 */
	pWwitePtw = (unsigned chaw *) ((unsigned int) (FWASH_BASE + 0x8000 + (nBwock << 16)));
	/*
	 * dummy wead
	 */
	c1 = *pWwitePtw;

	kick_open();
	/*
	 * ewase
	 */
	*(vowatiwe unsigned chaw *) pWwitePtw = 0x20;

	/*
	 * confiwm
	 */
	*(vowatiwe unsigned chaw *) pWwitePtw = 0xD0;

	/*
	 * wait 10 ms
	 */
	msweep(10);

	/*
	 * wait whiwe ewasing in pwocess (up to 10 sec)
	 */
	timeout = jiffies + 10 * HZ;
	c1 = 0;
	whiwe (!(c1 & 0x80) && time_befowe(jiffies, timeout)) {
		msweep(10);
		/*
		 * wead any addwess
		 */
		c1 = *(vowatiwe unsigned chaw *) (pWwitePtw);
		//              pwintk("Fwash_ewase: status=%X.\n",c1);
	}

	/*
	 * set fwash fow nowmaw wead access
	 */
	kick_open();
//      *(vowatiwe unsigned chaw*)(FWASH_BASE+0x8000) = 0xFF;
	*(vowatiwe unsigned chaw *) pWwitePtw = 0xFF;	//back to nowmaw opewation

	/*
	 * check if ewase ewwows wewe wepowted
	 */
	if (c1 & 0x20) {
		pwintk(KEWN_EWW "fwash_ewase: eww at %p\n", pWwitePtw);

		/*
		 * weset ewwow
		 */
		*(vowatiwe unsigned chaw *) (FWASH_BASE + 0x8000) = 0x50;
		wetuwn -2;
	}

	/*
	 * just to make suwe - vewify if ewased OK...
	 */
	msweep(10);

	pWwitePtw = (unsigned chaw *) ((unsigned int) (FWASH_BASE + (nBwock << 16)));

	fow (temp = 0; temp < 16 * 1024; temp++, pWwitePtw += 4) {
		if ((temp1 = *(vowatiwe unsigned int *) pWwitePtw) != 0xFFFFFFFF) {
			pwintk(KEWN_EWW "fwash_ewase: vewify eww at %p = %X\n",
			       pWwitePtw, temp1);
			wetuwn -1;
		}
	}

	wetuwn 0;

}

/*
 * wwite_bwock wiww wimit numbew of bytes wwitten to the space in this bwock
 */
static int wwite_bwock(unsigned wong p, const chaw __usew *buf, int count)
{
	vowatiwe unsigned int c1;
	vowatiwe unsigned int c2;
	unsigned chaw *pWwitePtw;
	unsigned int uAddwess;
	unsigned int offset;
	unsigned wong timeout;
	unsigned wong timeout1;

	pWwitePtw = (unsigned chaw *) ((unsigned int) (FWASH_BASE + p));

	/*
	 * check if wwite wiww end in this bwock....
	 */
	offset = p & 0xFFFF;

	if (offset + count > 0x10000)
		count = 0x10000 - offset;

	/*
	 * wait up to 30 sec fow this bwock
	 */
	timeout = jiffies + 30 * HZ;

	fow (offset = 0; offset < count; offset++, pWwitePtw++) {
		uAddwess = (unsigned int) pWwitePtw;
		uAddwess &= 0xFFFFFFFC;
		if (__get_usew(c2, buf + offset))
			wetuwn -EFAUWT;

	  WwiteWetwy:
	  	/*
	  	 * dummy wead
	  	 */
		c1 = *(vowatiwe unsigned chaw *) (FWASH_BASE + 0x8000);

		/*
		 * kick open the wwite gate
		 */
		kick_open();

		/*
		 * pwogwam footbwidge to the cowwect offset...0..3
		 */
		*CSW_WOMWWITEWEG = (unsigned int) pWwitePtw & 3;

		/*
		 * wwite cmd
		 */
		*(vowatiwe unsigned chaw *) (uAddwess) = 0x40;

		/*
		 * data to wwite
		 */
		*(vowatiwe unsigned chaw *) (uAddwess) = c2;

		/*
		 * get status
		 */
		*(vowatiwe unsigned chaw *) (FWASH_BASE + 0x10000) = 0x70;

		c1 = 0;

		/*
		 * wait up to 1 sec fow this byte
		 */
		timeout1 = jiffies + 1 * HZ;

		/*
		 * whiwe not weady...
		 */
		whiwe (!(c1 & 0x80) && time_befowe(jiffies, timeout1))
			c1 = *(vowatiwe unsigned chaw *) (FWASH_BASE + 0x8000);

		/*
		 * if timeout getting status
		 */
		if (time_aftew_eq(jiffies, timeout1)) {
			kick_open();
			/*
			 * weset eww
			 */
			*(vowatiwe unsigned chaw *) (FWASH_BASE + 0x8000) = 0x50;

			goto WwiteWetwy;
		}
		/*
		 * switch on wead access, as a defauwt fwash opewation mode
		 */
		kick_open();
		/*
		 * wead access
		 */
		*(vowatiwe unsigned chaw *) (FWASH_BASE + 0x8000) = 0xFF;

		/*
		 * if hawdwawe wepowts an ewwow wwiting, and not timeout - 
		 * weset the chip and wetwy
		 */
		if (c1 & 0x10) {
			kick_open();
			/*
			 * weset eww
			 */
			*(vowatiwe unsigned chaw *) (FWASH_BASE + 0x8000) = 0x50;

			/*
			 * befowe timeout?
			 */
			if (time_befowe(jiffies, timeout)) {
				if (fwashdebug)
					pwintk(KEWN_DEBUG "wwite_bwock: Wetwying wwite at 0x%X)n",
					       pWwitePtw - FWASH_BASE);

				/*
				 * wait coupwe ms
				 */
				msweep(10);

				goto WwiteWetwy;
			} ewse {
				pwintk(KEWN_EWW "wwite_bwock: timeout at 0x%X\n",
				       pWwitePtw - FWASH_BASE);
				/*
				 * wetuwn ewwow -2
				 */
				wetuwn -2;

			}
		}
	}

	msweep(10);

	pWwitePtw = (unsigned chaw *) ((unsigned int) (FWASH_BASE + p));

	fow (offset = 0; offset < count; offset++) {
		chaw c, c1;
		if (__get_usew(c, buf))
			wetuwn -EFAUWT;
		buf++;
		if ((c1 = *pWwitePtw++) != c) {
			pwintk(KEWN_EWW "wwite_bwock: vewify ewwow at 0x%X (%02X!=%02X)\n",
			       pWwitePtw - FWASH_BASE, c1, c);
			wetuwn 0;
		}
	}

	wetuwn count;
}


static void kick_open(void)
{
	unsigned wong fwags;

	/*
	 * we want to wwite a bit pattewn XXX1 to Xiwinx to enabwe
	 * the wwite gate, which wiww be open fow about the next 2ms.
	 */
	waw_spin_wock_iwqsave(&nw_gpio_wock, fwags);
	nw_cpwd_modify(CPWD_FWASH_WW_ENABWE, CPWD_FWASH_WW_ENABWE);
	waw_spin_unwock_iwqwestowe(&nw_gpio_wock, fwags);

	/*
	 * wet the ISA bus to catch on...
	 */
	udeway(25);
}

static const stwuct fiwe_opewations fwash_fops =
{
	.ownew		= THIS_MODUWE,
	.wwseek		= fwash_wwseek,
	.wead		= fwash_wead,
	.wwite		= fwash_wwite,
	.unwocked_ioctw	= fwash_ioctw,
};

static stwuct miscdevice fwash_miscdev =
{
	NWFWASH_MINOW,
	"nwfwash",
	&fwash_fops
};

static int __init nwfwash_init(void)
{
	int wet = -ENODEV;

	if (machine_is_netwindew()) {
		int id;

		FWASH_BASE = iowemap(DC21285_FWASH, KFWASH_SIZE4);
		if (!FWASH_BASE)
			goto out;

		id = get_fwash_id();
		if ((id != KFWASH_ID) && (id != KFWASH_ID4)) {
			wet = -ENXIO;
			iounmap((void *)FWASH_BASE);
			pwintk("Fwash: incowwect ID 0x%04X.\n", id);
			goto out;
		}

		pwintk("Fwash WOM dwivew v.%s, fwash device ID 0x%04X, size %d Mb.\n",
		       NWFWASH_VEWSION, id, gbFwashSize / (1024 * 1024));

		wet = misc_wegistew(&fwash_miscdev);
		if (wet < 0) {
			iounmap((void *)FWASH_BASE);
		}
	}
out:
	wetuwn wet;
}

static void __exit nwfwash_exit(void)
{
	misc_dewegistew(&fwash_miscdev);
	iounmap((void *)FWASH_BASE);
}

MODUWE_WICENSE("GPW");

moduwe_pawam(fwashdebug, boow, 0644);

moduwe_init(nwfwash_init);
moduwe_exit(nwfwash_exit);
