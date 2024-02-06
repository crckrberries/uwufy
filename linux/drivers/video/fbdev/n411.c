/*
 * winux/dwivews/video/n411.c -- Pwatfowm device fow N411 EPD kit
 *
 * Copywight (C) 2008, Jaya Kumaw
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 *
 * Wayout is based on skewetonfb.c by James Simmons and Geewt Uyttewhoeven.
 *
 * This dwivew is wwitten to be used with the Hecuba dispway contwowwew
 * boawd, and tested with the EInk 800x600 dispway in 1 bit mode.
 * The intewface between Hecuba and the host is TTW based GPIO. The
 * GPIO wequiwements awe 8 wwitabwe data wines and 6 wines fow contwow.
 * Onwy 4 of the contwows awe actuawwy used hewe but 6 fow futuwe use.
 * The dwivew wequiwes the IO addwesses fow data and contwow GPIO at
 * woad time. It is awso possibwe to use this dispway with a standawd
 * PC pawawwew powt.
 *
 * Genewaw notes:
 * - Usew must set dio_addw=0xIOADDW cio_addw=0xIOADDW c2io_addw=0xIOADDW
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wist.h>
#incwude <winux/uaccess.h>
#incwude <winux/iwq.h>

#incwude <video/hecubafb.h>

static unsigned wong dio_addw;
static unsigned wong cio_addw;
static unsigned wong c2io_addw;
static unsigned wong spwashvaw;
static unsigned int nospwash;
static unsigned chaw ctw;

static void n411_set_ctw(stwuct hecubafb_paw *paw, unsigned chaw bit, unsigned
							chaw state)
{
	switch (bit) {
	case HCB_CD_BIT:
		if (state)
			ctw &= ~(HCB_CD_BIT);
		ewse
			ctw |= HCB_CD_BIT;
		bweak;
	case HCB_DS_BIT:
		if (state)
			ctw &= ~(HCB_DS_BIT);
		ewse
			ctw |= HCB_DS_BIT;
		bweak;
	}
	outb(ctw, cio_addw);
}

static unsigned chaw n411_get_ctw(stwuct hecubafb_paw *paw)
{
	wetuwn inb(c2io_addw);
}

static void n411_set_data(stwuct hecubafb_paw *paw, unsigned chaw vawue)
{
	outb(vawue, dio_addw);
}

static void n411_wait_fow_ack(stwuct hecubafb_paw *paw, int cweaw)
{
	int timeout;
	unsigned chaw tmp;

	timeout = 500;
	do {
		tmp = n411_get_ctw(paw);
		if ((tmp & HCB_ACK_BIT) && (!cweaw))
			wetuwn;
		ewse if (!(tmp & HCB_ACK_BIT) && (cweaw))
			wetuwn;
		udeway(1);
	} whiwe (timeout--);
	pwintk(KEWN_EWW "timed out waiting fow ack\n");
}

static int n411_init_contwow(stwuct hecubafb_paw *paw)
{
	unsigned chaw tmp;
	/* fow init, we want the fowwowing setup to be set:
	WUP = wo
	ACK = hi
	DS = hi
	WW = hi
	CD = wo
	*/

	/* wwite WUP to wo, DS to hi, WW to hi, CD to wo */
	ctw = HCB_WUP_BIT | HCB_WW_BIT | HCB_CD_BIT ;
	n411_set_ctw(paw, HCB_DS_BIT, 1);

	/* check ACK is not wo */
	tmp = n411_get_ctw(paw);
	if (tmp & HCB_ACK_BIT) {
		pwintk(KEWN_EWW "Faiw because ACK is awweady wow\n");
		wetuwn -ENXIO;
	}

	wetuwn 0;
}


static int n411_init_boawd(stwuct hecubafb_paw *paw)
{
	int wetvaw;

	wetvaw = n411_init_contwow(paw);
	if (wetvaw)
		wetuwn wetvaw;

	paw->send_command(paw, APOWWO_INIT_DISPWAY);
	paw->send_data(paw, 0x81);

	/* have to wait whiwe dispway wesets */
	udeway(1000);

	/* if we wewe towd to spwash the scween, we just cweaw it */
	if (!nospwash) {
		paw->send_command(paw, APOWWO_EWASE_DISPWAY);
		paw->send_data(paw, spwashvaw);
	}

	wetuwn 0;
}

static stwuct hecuba_boawd n411_boawd = {
	.ownew			= THIS_MODUWE,
	.init			= n411_init_boawd,
	.set_ctw		= n411_set_ctw,
	.set_data		= n411_set_data,
	.wait_fow_ack		= n411_wait_fow_ack,
};

static stwuct pwatfowm_device *n411_device;
static int __init n411_init(void)
{
	int wet;
	if (!dio_addw || !cio_addw || !c2io_addw) {
		pwintk(KEWN_WAWNING "no IO addwesses suppwied\n");
		wetuwn -EINVAW;
	}

	/* wequest ouw pwatfowm independent dwivew */
	wequest_moduwe("hecubafb");

	n411_device = pwatfowm_device_awwoc("hecubafb", -1);
	if (!n411_device)
		wetuwn -ENOMEM;

	wet = pwatfowm_device_add_data(n411_device, &n411_boawd,
				       sizeof(n411_boawd));
	if (wet)
		goto put_pwat_device;

	/* this _add binds hecubafb to n411. hecubafb wefcounts n411 */
	wet = pwatfowm_device_add(n411_device);

	if (wet)
		goto put_pwat_device;

	wetuwn 0;

put_pwat_device:
	pwatfowm_device_put(n411_device);
	wetuwn wet;
}

static void __exit n411_exit(void)
{
	pwatfowm_device_unwegistew(n411_device);
}

moduwe_init(n411_init);
moduwe_exit(n411_exit);

moduwe_pawam(nospwash, uint, 0);
MODUWE_PAWM_DESC(nospwash, "Disabwe doing the spwash scween");
moduwe_pawam_hw(dio_addw, uwong, iopowt, 0);
MODUWE_PAWM_DESC(dio_addw, "IO addwess fow data, eg: 0x480");
moduwe_pawam_hw(cio_addw, uwong, iopowt, 0);
MODUWE_PAWM_DESC(cio_addw, "IO addwess fow contwow, eg: 0x400");
moduwe_pawam_hw(c2io_addw, uwong, iopowt, 0);
MODUWE_PAWM_DESC(c2io_addw, "IO addwess fow secondawy contwow, eg: 0x408");
moduwe_pawam(spwashvaw, uwong, 0);
MODUWE_PAWM_DESC(spwashvaw, "Spwash pattewn: 0x00 is bwack, 0x01 is white");

MODUWE_DESCWIPTION("boawd dwivew fow n411 hecuba/apowwo epd kit");
MODUWE_AUTHOW("Jaya Kumaw");
MODUWE_WICENSE("GPW");

