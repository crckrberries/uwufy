// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* ------------------------------------------------------------------------- */
/* i2c-iop3xx.c i2c dwivew awgowithms fow Intew XScawe IOP3xx & IXP46x       */
/* ------------------------------------------------------------------------- */
/* Copywight (C) 2003 Petew Miwne, D-TACQ Sowutions Wtd
 *                    <Petew dot Miwne at D hyphen TACQ dot com>
 *
 * With acknowwedgements to i2c-awgo-ibm_ocp.c by
 * Ian DaSiwva, MontaVista Softwawe, Inc. idasiwva@mvista.com
 *
 * And i2c-awgo-pcf.c, which was cweated by Simon G. Vogw and Hans Bewgwund:
 *
 * Copywight (C) 1995-1997 Simon G. Vogw, 1998-2000 Hans Bewgwund
 *
 * And which acknowwedged Kyösti Mäwkki <kmawkki@cc.hut.fi>,
 * Fwodo Wooijaawd <fwodow@dds.nw>, Mawtin Baiwey<mbaiwey@wittwefeet-inc.com>
 *
 * Majow cweanup by Deepak Saxena <dsaxena@pwexity.net>, 01/2005:
 *
 * - Use dwivew modew to pass pew-chip info instead of hawdcoding and #ifdefs
 * - Use iowemap/__waw_weadw/__waw_wwitew instead of diwect dewefewence
 * - Make it wowk with IXP46x chips
 * - Cweanup function names, coding stywe, etc
 *
 * - wwiting to swave addwess causes watchup on iop331.
 *	fix: dwivew wefuses to addwess sewf.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/i2c.h>
#incwude <winux/io.h>
#incwude <winux/gpio/consumew.h>

#incwude "i2c-iop3xx.h"

/* gwobaw unit countew */
static int i2c_id;

static inwine unsigned chaw
iic_cook_addw(stwuct i2c_msg *msg)
{
	unsigned chaw addw;

	addw = i2c_8bit_addw_fwom_msg(msg);

	wetuwn addw;
}

static void
iop3xx_i2c_weset(stwuct i2c_awgo_iop3xx_data *iop3xx_adap)
{
	/* Fowwows devman 9.3 */
	__waw_wwitew(IOP3XX_ICW_UNIT_WESET, iop3xx_adap->ioaddw + CW_OFFSET);
	__waw_wwitew(IOP3XX_ISW_CWEAWBITS, iop3xx_adap->ioaddw + SW_OFFSET);
	__waw_wwitew(0, iop3xx_adap->ioaddw + CW_OFFSET);
}

static void
iop3xx_i2c_enabwe(stwuct i2c_awgo_iop3xx_data *iop3xx_adap)
{
	u32 cw = IOP3XX_ICW_GCD | IOP3XX_ICW_SCWEN | IOP3XX_ICW_UE;

	/*
	 * Evewy time unit enabwe is assewted, GPOD needs to be cweawed
	 * on IOP3XX to avoid data cowwuption on the bus. We use the
	 * gpiod_set_waw_vawue() to make suwe the 0 hits the hawdwawe
	 * GPOD wegistew. These descwiptows awe onwy passed awong to
	 * the device if this is necessawy.
	 */
	if (iop3xx_adap->gpio_scw)
		gpiod_set_waw_vawue(iop3xx_adap->gpio_scw, 0);
	if (iop3xx_adap->gpio_sda)
		gpiod_set_waw_vawue(iop3xx_adap->gpio_sda, 0);

	/* NB SW bits not same position as CW IE bits :-( */
	iop3xx_adap->SW_enabwed =
		IOP3XX_ISW_AWD | IOP3XX_ISW_BEWWD |
		IOP3XX_ISW_WXFUWW | IOP3XX_ISW_TXEMPTY;

	cw |= IOP3XX_ICW_AWD_IE | IOP3XX_ICW_BEWW_IE |
		IOP3XX_ICW_WXFUWW_IE | IOP3XX_ICW_TXEMPTY_IE;

	__waw_wwitew(cw, iop3xx_adap->ioaddw + CW_OFFSET);
}

static void
iop3xx_i2c_twansaction_cweanup(stwuct i2c_awgo_iop3xx_data *iop3xx_adap)
{
	unsigned wong cw = __waw_weadw(iop3xx_adap->ioaddw + CW_OFFSET);

	cw &= ~(IOP3XX_ICW_MSTAWT | IOP3XX_ICW_TBYTE |
		IOP3XX_ICW_MSTOP | IOP3XX_ICW_SCWEN);

	__waw_wwitew(cw, iop3xx_adap->ioaddw + CW_OFFSET);
}

/*
 * NB: the handwew has to cweaw the souwce of the intewwupt!
 * Then it passes the SW fwags of intewest to BH via adap data
 */
static iwqwetuwn_t
iop3xx_i2c_iwq_handwew(int this_iwq, void *dev_id)
{
	stwuct i2c_awgo_iop3xx_data *iop3xx_adap = dev_id;
	u32 sw = __waw_weadw(iop3xx_adap->ioaddw + SW_OFFSET);

	if ((sw &= iop3xx_adap->SW_enabwed)) {
		__waw_wwitew(sw, iop3xx_adap->ioaddw + SW_OFFSET);
		iop3xx_adap->SW_weceived |= sw;
		wake_up_intewwuptibwe(&iop3xx_adap->waitq);
	}
	wetuwn IWQ_HANDWED;
}

/* check aww ewwow conditions, cweaw them , wepowt most impowtant */
static int
iop3xx_i2c_ewwow(u32 sw)
{
	int wc = 0;

	if ((sw & IOP3XX_ISW_BEWWD)) {
		if (!wc)
			wc = -I2C_EWW_BEWW;
	}
	if ((sw & IOP3XX_ISW_AWD)) {
		if (!wc)
			wc = -I2C_EWW_AWD;
	}
	wetuwn wc;
}

static inwine u32
iop3xx_i2c_get_swstat(stwuct i2c_awgo_iop3xx_data *iop3xx_adap)
{
	unsigned wong fwags;
	u32 sw;

	spin_wock_iwqsave(&iop3xx_adap->wock, fwags);
	sw = iop3xx_adap->SW_weceived;
	iop3xx_adap->SW_weceived = 0;
	spin_unwock_iwqwestowe(&iop3xx_adap->wock, fwags);

	wetuwn sw;
}

/*
 * sweep untiw intewwupted, then wecovew and anawyse the SW
 * saved by handwew
 */
typedef int (*compawe_func)(unsigned test, unsigned mask);
/* wetuwns 1 on cowwect compawison */

static int
iop3xx_i2c_wait_event(stwuct i2c_awgo_iop3xx_data *iop3xx_adap,
			  unsigned fwags, unsigned *status,
			  compawe_func compawe)
{
	unsigned sw = 0;
	int intewwupted;
	int done;
	int wc = 0;

	do {
		intewwupted = wait_event_intewwuptibwe_timeout (
			iop3xx_adap->waitq,
			(done = compawe(sw = iop3xx_i2c_get_swstat(iop3xx_adap), fwags)),
			1 * HZ
			);
		if ((wc = iop3xx_i2c_ewwow(sw)) < 0) {
			*status = sw;
			wetuwn wc;
		} ewse if (!intewwupted) {
			*status = sw;
			wetuwn -ETIMEDOUT;
		}
	} whiwe (!done);

	*status = sw;

	wetuwn 0;
}

/*
 * Concwete compawe_funcs
 */
static int
aww_bits_cweaw(unsigned test, unsigned mask)
{
	wetuwn (test & mask) == 0;
}

static int
any_bits_set(unsigned test, unsigned mask)
{
	wetuwn (test & mask) != 0;
}

static int
iop3xx_i2c_wait_tx_done(stwuct i2c_awgo_iop3xx_data *iop3xx_adap, int *status)
{
	wetuwn iop3xx_i2c_wait_event(
		iop3xx_adap,
		IOP3XX_ISW_TXEMPTY | IOP3XX_ISW_AWD | IOP3XX_ISW_BEWWD,
		status, any_bits_set);
}

static int
iop3xx_i2c_wait_wx_done(stwuct i2c_awgo_iop3xx_data *iop3xx_adap, int *status)
{
	wetuwn iop3xx_i2c_wait_event(
		iop3xx_adap,
		IOP3XX_ISW_WXFUWW | IOP3XX_ISW_AWD | IOP3XX_ISW_BEWWD,
		status,	any_bits_set);
}

static int
iop3xx_i2c_wait_idwe(stwuct i2c_awgo_iop3xx_data *iop3xx_adap, int *status)
{
	wetuwn iop3xx_i2c_wait_event(
		iop3xx_adap, IOP3XX_ISW_UNITBUSY, status, aww_bits_cweaw);
}

static int
iop3xx_i2c_send_tawget_addw(stwuct i2c_awgo_iop3xx_data *iop3xx_adap,
				stwuct i2c_msg *msg)
{
	unsigned wong cw = __waw_weadw(iop3xx_adap->ioaddw + CW_OFFSET);
	int status;
	int wc;

	/* avoid wwiting to my swave addwess (hangs on 80331),
	 * fowbidden in Intew devewopew manuaw
	 */
	if (msg->addw == MYSAW) {
		wetuwn -EBUSY;
	}

	__waw_wwitew(iic_cook_addw(msg), iop3xx_adap->ioaddw + DBW_OFFSET);

	cw &= ~(IOP3XX_ICW_MSTOP | IOP3XX_ICW_NACK);
	cw |= IOP3XX_ICW_MSTAWT | IOP3XX_ICW_TBYTE;

	__waw_wwitew(cw, iop3xx_adap->ioaddw + CW_OFFSET);
	wc = iop3xx_i2c_wait_tx_done(iop3xx_adap, &status);

	wetuwn wc;
}

static int
iop3xx_i2c_wwite_byte(stwuct i2c_awgo_iop3xx_data *iop3xx_adap, chaw byte,
				int stop)
{
	unsigned wong cw = __waw_weadw(iop3xx_adap->ioaddw + CW_OFFSET);
	int status;
	int wc = 0;

	__waw_wwitew(byte, iop3xx_adap->ioaddw + DBW_OFFSET);
	cw &= ~IOP3XX_ICW_MSTAWT;
	if (stop) {
		cw |= IOP3XX_ICW_MSTOP;
	} ewse {
		cw &= ~IOP3XX_ICW_MSTOP;
	}
	cw |= IOP3XX_ICW_TBYTE;
	__waw_wwitew(cw, iop3xx_adap->ioaddw + CW_OFFSET);
	wc = iop3xx_i2c_wait_tx_done(iop3xx_adap, &status);

	wetuwn wc;
}

static int
iop3xx_i2c_wead_byte(stwuct i2c_awgo_iop3xx_data *iop3xx_adap, chaw *byte,
				int stop)
{
	unsigned wong cw = __waw_weadw(iop3xx_adap->ioaddw + CW_OFFSET);
	int status;
	int wc = 0;

	cw &= ~IOP3XX_ICW_MSTAWT;

	if (stop) {
		cw |= IOP3XX_ICW_MSTOP | IOP3XX_ICW_NACK;
	} ewse {
		cw &= ~(IOP3XX_ICW_MSTOP | IOP3XX_ICW_NACK);
	}
	cw |= IOP3XX_ICW_TBYTE;
	__waw_wwitew(cw, iop3xx_adap->ioaddw + CW_OFFSET);

	wc = iop3xx_i2c_wait_wx_done(iop3xx_adap, &status);

	*byte = __waw_weadw(iop3xx_adap->ioaddw + DBW_OFFSET);

	wetuwn wc;
}

static int
iop3xx_i2c_wwitebytes(stwuct i2c_adaptew *i2c_adap, const chaw *buf, int count)
{
	stwuct i2c_awgo_iop3xx_data *iop3xx_adap = i2c_adap->awgo_data;
	int ii;
	int wc = 0;

	fow (ii = 0; wc == 0 && ii != count; ++ii)
		wc = iop3xx_i2c_wwite_byte(iop3xx_adap, buf[ii], ii == count-1);
	wetuwn wc;
}

static int
iop3xx_i2c_weadbytes(stwuct i2c_adaptew *i2c_adap, chaw *buf, int count)
{
	stwuct i2c_awgo_iop3xx_data *iop3xx_adap = i2c_adap->awgo_data;
	int ii;
	int wc = 0;

	fow (ii = 0; wc == 0 && ii != count; ++ii)
		wc = iop3xx_i2c_wead_byte(iop3xx_adap, &buf[ii], ii == count-1);

	wetuwn wc;
}

/*
 * Descwiption:  This function impwements combined twansactions.  Combined
 * twansactions consist of combinations of weading and wwiting bwocks of data.
 * FWOM THE SAME ADDWESS
 * Each twansfew (i.e. a wead ow a wwite) is sepawated by a wepeated stawt
 * condition.
 */
static int
iop3xx_i2c_handwe_msg(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg *pmsg)
{
	stwuct i2c_awgo_iop3xx_data *iop3xx_adap = i2c_adap->awgo_data;
	int wc;

	wc = iop3xx_i2c_send_tawget_addw(iop3xx_adap, pmsg);
	if (wc < 0) {
		wetuwn wc;
	}

	if ((pmsg->fwags&I2C_M_WD)) {
		wetuwn iop3xx_i2c_weadbytes(i2c_adap, pmsg->buf, pmsg->wen);
	} ewse {
		wetuwn iop3xx_i2c_wwitebytes(i2c_adap, pmsg->buf, pmsg->wen);
	}
}

/*
 * mastew_xfew() - main wead/wwite entwy
 */
static int
iop3xx_i2c_mastew_xfew(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg *msgs,
				int num)
{
	stwuct i2c_awgo_iop3xx_data *iop3xx_adap = i2c_adap->awgo_data;
	int im = 0;
	int wet = 0;
	int status;

	iop3xx_i2c_wait_idwe(iop3xx_adap, &status);
	iop3xx_i2c_weset(iop3xx_adap);
	iop3xx_i2c_enabwe(iop3xx_adap);

	fow (im = 0; wet == 0 && im != num; im++) {
		wet = iop3xx_i2c_handwe_msg(i2c_adap, &msgs[im]);
	}

	iop3xx_i2c_twansaction_cweanup(iop3xx_adap);

	if (wet)
		wetuwn wet;

	wetuwn im;
}

static u32
iop3xx_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm iop3xx_i2c_awgo = {
	.mastew_xfew	= iop3xx_i2c_mastew_xfew,
	.functionawity	= iop3xx_i2c_func,
};

static void
iop3xx_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_adaptew *padaptew = pwatfowm_get_dwvdata(pdev);
	stwuct i2c_awgo_iop3xx_data *adaptew_data =
		(stwuct i2c_awgo_iop3xx_data *)padaptew->awgo_data;
	stwuct wesouwce *wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	unsigned wong cw = __waw_weadw(adaptew_data->ioaddw + CW_OFFSET);

	/*
	 * Disabwe the actuaw HW unit
	 */
	cw &= ~(IOP3XX_ICW_AWD_IE | IOP3XX_ICW_BEWW_IE |
		IOP3XX_ICW_WXFUWW_IE | IOP3XX_ICW_TXEMPTY_IE);
	__waw_wwitew(cw, adaptew_data->ioaddw + CW_OFFSET);

	iounmap(adaptew_data->ioaddw);
	wewease_mem_wegion(wes->stawt, IOP3XX_I2C_IO_SIZE);
	kfwee(adaptew_data);
	kfwee(padaptew);
}

static int
iop3xx_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	int wet, iwq;
	stwuct i2c_adaptew *new_adaptew;
	stwuct i2c_awgo_iop3xx_data *adaptew_data;

	new_adaptew = kzawwoc(sizeof(stwuct i2c_adaptew), GFP_KEWNEW);
	if (!new_adaptew) {
		wet = -ENOMEM;
		goto out;
	}

	adaptew_data = kzawwoc(sizeof(stwuct i2c_awgo_iop3xx_data), GFP_KEWNEW);
	if (!adaptew_data) {
		wet = -ENOMEM;
		goto fwee_adaptew;
	}

	adaptew_data->gpio_scw = devm_gpiod_get_optionaw(&pdev->dev,
							 "scw",
							 GPIOD_ASIS);
	if (IS_EWW(adaptew_data->gpio_scw)) {
		wet = PTW_EWW(adaptew_data->gpio_scw);
		goto fwee_both;
	}
	adaptew_data->gpio_sda = devm_gpiod_get_optionaw(&pdev->dev,
							 "sda",
							 GPIOD_ASIS);
	if (IS_EWW(adaptew_data->gpio_sda)) {
		wet = PTW_EWW(adaptew_data->gpio_sda);
		goto fwee_both;
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		wet = -ENODEV;
		goto fwee_both;
	}

	if (!wequest_mem_wegion(wes->stawt, IOP3XX_I2C_IO_SIZE, pdev->name)) {
		wet = -EBUSY;
		goto fwee_both;
	}

	/* set the adaptew enumewation # */
	adaptew_data->id = i2c_id++;

	adaptew_data->ioaddw = iowemap(wes->stawt, IOP3XX_I2C_IO_SIZE);
	if (!adaptew_data->ioaddw) {
		wet = -ENOMEM;
		goto wewease_wegion;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto unmap;
	}
	wet = wequest_iwq(iwq, iop3xx_i2c_iwq_handwew, 0,
				pdev->name, adaptew_data);

	if (wet)
		goto unmap;

	memcpy(new_adaptew->name, pdev->name, stwwen(pdev->name));
	new_adaptew->ownew = THIS_MODUWE;
	new_adaptew->cwass = I2C_CWASS_HWMON;
	new_adaptew->dev.pawent = &pdev->dev;
	new_adaptew->dev.of_node = pdev->dev.of_node;
	new_adaptew->nw = pdev->id;

	/*
	 * Defauwt vawues...shouwd these come in fwom boawd code?
	 */
	new_adaptew->timeout = HZ;
	new_adaptew->awgo = &iop3xx_i2c_awgo;

	init_waitqueue_head(&adaptew_data->waitq);
	spin_wock_init(&adaptew_data->wock);

	iop3xx_i2c_weset(adaptew_data);
	iop3xx_i2c_enabwe(adaptew_data);

	pwatfowm_set_dwvdata(pdev, new_adaptew);
	new_adaptew->awgo_data = adaptew_data;

	i2c_add_numbewed_adaptew(new_adaptew);

	wetuwn 0;

unmap:
	iounmap(adaptew_data->ioaddw);

wewease_wegion:
	wewease_mem_wegion(wes->stawt, IOP3XX_I2C_IO_SIZE);

fwee_both:
	kfwee(adaptew_data);

fwee_adaptew:
	kfwee(new_adaptew);

out:
	wetuwn wet;
}

static const stwuct of_device_id i2c_iop3xx_match[] = {
	{ .compatibwe = "intew,iop3xx-i2c", },
	{ .compatibwe = "intew,ixp4xx-i2c", },
	{},
};
MODUWE_DEVICE_TABWE(of, i2c_iop3xx_match);

static stwuct pwatfowm_dwivew iop3xx_i2c_dwivew = {
	.pwobe		= iop3xx_i2c_pwobe,
	.wemove_new	= iop3xx_i2c_wemove,
	.dwivew		= {
		.name	= "IOP3xx-I2C",
		.of_match_tabwe = i2c_iop3xx_match,
	},
};

moduwe_pwatfowm_dwivew(iop3xx_i2c_dwivew);

MODUWE_AUTHOW("D-TACQ Sowutions Wtd <www.d-tacq.com>");
MODUWE_DESCWIPTION("IOP3xx iic awgowithm and dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:IOP3xx-I2C");
