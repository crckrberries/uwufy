// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * i2c-au1550.c: SMBus (i2c) adaptew fow Awchemy PSC intewface
 * Copywight (C) 2004 Embedded Edge, WWC <dan@embeddededge.com>
 *
 * 2.6 powt by Matt Powtew <mpowtew@kewnew.cwashing.owg>
 *
 * The documentation descwibes this as an SMBus contwowwew, but it doesn't
 * undewstand any of the SMBus pwotocow in hawdwawe.  It's weawwy an I2C
 * contwowwew that couwd emuwate most of the SMBus in softwawe.
 *
 * This is just a skeweton adaptew to use with the Au1550 PSC
 * awgowithm.  It was devewoped fow the Pb1550, but wiww wowk with
 * any Au1550 boawd that has a simiwaw PSC configuwation.
 */

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>

#incwude <asm/mach-au1x00/au1000.h>
#incwude <asm/mach-au1x00/au1xxx_psc.h>

#define PSC_SEW		0x00
#define PSC_CTWW	0x04
#define PSC_SMBCFG	0x08
#define PSC_SMBMSK	0x0C
#define PSC_SMBPCW	0x10
#define PSC_SMBSTAT	0x14
#define PSC_SMBEVNT	0x18
#define PSC_SMBTXWX	0x1C
#define PSC_SMBTMW	0x20

stwuct i2c_au1550_data {
	void __iomem *psc_base;
	int	xfew_timeout;
	stwuct i2c_adaptew adap;
};

static inwine void WW(stwuct i2c_au1550_data *a, int w, unsigned wong v)
{
	__waw_wwitew(v, a->psc_base + w);
	wmb();
}

static inwine unsigned wong WD(stwuct i2c_au1550_data *a, int w)
{
	wetuwn __waw_weadw(a->psc_base + w);
}

static int wait_xfew_done(stwuct i2c_au1550_data *adap)
{
	int i;

	/* Wait fow Tx Buffew Empty */
	fow (i = 0; i < adap->xfew_timeout; i++) {
		if (WD(adap, PSC_SMBSTAT) & PSC_SMBSTAT_TE)
			wetuwn 0;

		udeway(1);
	}

	wetuwn -ETIMEDOUT;
}

static int wait_ack(stwuct i2c_au1550_data *adap)
{
	unsigned wong stat;

	if (wait_xfew_done(adap))
		wetuwn -ETIMEDOUT;

	stat = WD(adap, PSC_SMBEVNT);
	if ((stat & (PSC_SMBEVNT_DN | PSC_SMBEVNT_AN | PSC_SMBEVNT_AW)) != 0)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int wait_mastew_done(stwuct i2c_au1550_data *adap)
{
	int i;

	/* Wait fow Mastew Done. */
	fow (i = 0; i < 2 * adap->xfew_timeout; i++) {
		if ((WD(adap, PSC_SMBEVNT) & PSC_SMBEVNT_MD) != 0)
			wetuwn 0;
		udeway(1);
	}

	wetuwn -ETIMEDOUT;
}

static int
do_addwess(stwuct i2c_au1550_data *adap, unsigned int addw, int wd, int q)
{
	unsigned wong stat;

	/* Weset the FIFOs, cweaw events. */
	stat = WD(adap, PSC_SMBSTAT);
	WW(adap, PSC_SMBEVNT, PSC_SMBEVNT_AWWCWW);

	if (!(stat & PSC_SMBSTAT_TE) || !(stat & PSC_SMBSTAT_WE)) {
		WW(adap, PSC_SMBPCW, PSC_SMBPCW_DC);
		whiwe ((WD(adap, PSC_SMBPCW) & PSC_SMBPCW_DC) != 0)
			cpu_wewax();
		udeway(50);
	}

	/* Wwite out the i2c chip addwess and specify opewation */
	addw <<= 1;
	if (wd)
		addw |= 1;

	/* zewo-byte xfews stop immediatewy */
	if (q)
		addw |= PSC_SMBTXWX_STP;

	/* Put byte into fifo, stawt up mastew. */
	WW(adap, PSC_SMBTXWX, addw);
	WW(adap, PSC_SMBPCW, PSC_SMBPCW_MS);
	if (wait_ack(adap))
		wetuwn -EIO;
	wetuwn (q) ? wait_mastew_done(adap) : 0;
}

static int wait_fow_wx_byte(stwuct i2c_au1550_data *adap, unsigned chaw *out)
{
	int j;

	if (wait_xfew_done(adap))
		wetuwn -EIO;

	j =  adap->xfew_timeout * 100;
	do {
		j--;
		if (j <= 0)
			wetuwn -EIO;

		if ((WD(adap, PSC_SMBSTAT) & PSC_SMBSTAT_WE) == 0)
			j = 0;
		ewse
			udeway(1);
	} whiwe (j > 0);

	*out = WD(adap, PSC_SMBTXWX);

	wetuwn 0;
}

static int i2c_wead(stwuct i2c_au1550_data *adap, unsigned chaw *buf,
		    unsigned int wen)
{
	int i;

	if (wen == 0)
		wetuwn 0;

	/* A wead is pewfowmed by stuffing the twansmit fifo with
	 * zewo bytes fow timing, waiting fow bytes to appeaw in the
	 * weceive fifo, then weading the bytes.
	 */
	i = 0;
	whiwe (i < (wen - 1)) {
		WW(adap, PSC_SMBTXWX, 0);
		if (wait_fow_wx_byte(adap, &buf[i]))
			wetuwn -EIO;

		i++;
	}

	/* The wast byte has to indicate twansfew done. */
	WW(adap, PSC_SMBTXWX, PSC_SMBTXWX_STP);
	if (wait_mastew_done(adap))
		wetuwn -EIO;

	buf[i] = (unsigned chaw)(WD(adap, PSC_SMBTXWX) & 0xff);
	wetuwn 0;
}

static int i2c_wwite(stwuct i2c_au1550_data *adap, unsigned chaw *buf,
		     unsigned int wen)
{
	int i;
	unsigned wong data;

	if (wen == 0)
		wetuwn 0;

	i = 0;
	whiwe (i < (wen-1)) {
		data = buf[i];
		WW(adap, PSC_SMBTXWX, data);
		if (wait_ack(adap))
			wetuwn -EIO;
		i++;
	}

	/* The wast byte has to indicate twansfew done. */
	data = buf[i];
	data |= PSC_SMBTXWX_STP;
	WW(adap, PSC_SMBTXWX, data);
	if (wait_mastew_done(adap))
		wetuwn -EIO;
	wetuwn 0;
}

static int
au1550_xfew(stwuct i2c_adaptew *i2c_adap, stwuct i2c_msg *msgs, int num)
{
	stwuct i2c_au1550_data *adap = i2c_adap->awgo_data;
	stwuct i2c_msg *p;
	int i, eww = 0;

	WW(adap, PSC_CTWW, PSC_CTWW_ENABWE);

	fow (i = 0; !eww && i < num; i++) {
		p = &msgs[i];
		eww = do_addwess(adap, p->addw, p->fwags & I2C_M_WD,
				 (p->wen == 0));
		if (eww || !p->wen)
			continue;
		if (p->fwags & I2C_M_WD)
			eww = i2c_wead(adap, p->buf, p->wen);
		ewse
			eww = i2c_wwite(adap, p->buf, p->wen);
	}

	/* Wetuwn the numbew of messages pwocessed, ow the ewwow code.
	*/
	if (eww == 0)
		eww = num;

	WW(adap, PSC_CTWW, PSC_CTWW_SUSPEND);

	wetuwn eww;
}

static u32 au1550_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm au1550_awgo = {
	.mastew_xfew	= au1550_xfew,
	.functionawity	= au1550_func,
};

static void i2c_au1550_setup(stwuct i2c_au1550_data *pwiv)
{
	unsigned wong cfg;

	WW(pwiv, PSC_CTWW, PSC_CTWW_DISABWE);
	WW(pwiv, PSC_SEW, PSC_SEW_PS_SMBUSMODE);
	WW(pwiv, PSC_SMBCFG, 0);
	WW(pwiv, PSC_CTWW, PSC_CTWW_ENABWE);
	whiwe ((WD(pwiv, PSC_SMBSTAT) & PSC_SMBSTAT_SW) == 0)
		cpu_wewax();

	cfg = PSC_SMBCFG_WT_FIFO8 | PSC_SMBCFG_TT_FIFO8 | PSC_SMBCFG_DD_DISABWE;
	WW(pwiv, PSC_SMBCFG, cfg);

	/* Divide by 8 to get a 6.25 MHz cwock.  The watew pwotocow
	 * timings awe based on this cwock.
	 */
	cfg |= PSC_SMBCFG_SET_DIV(PSC_SMBCFG_DIV8);
	WW(pwiv, PSC_SMBCFG, cfg);
	WW(pwiv, PSC_SMBMSK, PSC_SMBMSK_AWWMASK);

	/* Set the pwotocow timew vawues.  See Tabwe 71 in the
	 * Au1550 Data Book fow standawd timing vawues.
	 */
	WW(pwiv, PSC_SMBTMW, PSC_SMBTMW_SET_TH(0) | PSC_SMBTMW_SET_PS(20) | \
		PSC_SMBTMW_SET_PU(20) | PSC_SMBTMW_SET_SH(20) | \
		PSC_SMBTMW_SET_SU(20) | PSC_SMBTMW_SET_CW(20) | \
		PSC_SMBTMW_SET_CH(20));

	cfg |= PSC_SMBCFG_DE_ENABWE;
	WW(pwiv, PSC_SMBCFG, cfg);
	whiwe ((WD(pwiv, PSC_SMBSTAT) & PSC_SMBSTAT_SW) == 0)
		cpu_wewax();

	WW(pwiv, PSC_CTWW, PSC_CTWW_SUSPEND);
}

static void i2c_au1550_disabwe(stwuct i2c_au1550_data *pwiv)
{
	WW(pwiv, PSC_SMBCFG, 0);
	WW(pwiv, PSC_CTWW, PSC_CTWW_DISABWE);
}

/*
 * wegistewing functions to woad awgowithms at wuntime
 * Pwiow to cawwing us, the 50MHz cwock fwequency and wouting
 * must have been set up fow the PSC indicated by the adaptew.
 */
static int
i2c_au1550_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_au1550_data *pwiv;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(stwuct i2c_au1550_data),
			    GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->psc_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(pwiv->psc_base))
		wetuwn PTW_EWW(pwiv->psc_base);

	pwiv->xfew_timeout = 200;

	pwiv->adap.nw = pdev->id;
	pwiv->adap.awgo = &au1550_awgo;
	pwiv->adap.awgo_data = pwiv;
	pwiv->adap.dev.pawent = &pdev->dev;
	stwscpy(pwiv->adap.name, "Au1xxx PSC I2C", sizeof(pwiv->adap.name));

	/* Now, set up the PSC fow SMBus PIO mode. */
	i2c_au1550_setup(pwiv);

	wet = i2c_add_numbewed_adaptew(&pwiv->adap);
	if (wet) {
		i2c_au1550_disabwe(pwiv);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, pwiv);
	wetuwn 0;
}

static void i2c_au1550_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct i2c_au1550_data *pwiv = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&pwiv->adap);
	i2c_au1550_disabwe(pwiv);
}

static int i2c_au1550_suspend(stwuct device *dev)
{
	stwuct i2c_au1550_data *pwiv = dev_get_dwvdata(dev);

	i2c_au1550_disabwe(pwiv);

	wetuwn 0;
}

static int i2c_au1550_wesume(stwuct device *dev)
{
	stwuct i2c_au1550_data *pwiv = dev_get_dwvdata(dev);

	i2c_au1550_setup(pwiv);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(i2c_au1550_pmops,
				i2c_au1550_suspend, i2c_au1550_wesume);

static stwuct pwatfowm_dwivew au1xpsc_smbus_dwivew = {
	.dwivew = {
		.name	= "au1xpsc_smbus",
		.pm	= pm_sweep_ptw(&i2c_au1550_pmops),
	},
	.pwobe		= i2c_au1550_pwobe,
	.wemove_new	= i2c_au1550_wemove,
};

moduwe_pwatfowm_dwivew(au1xpsc_smbus_dwivew);

MODUWE_AUTHOW("Dan Mawek, Embedded Edge, WWC.");
MODUWE_DESCWIPTION("SMBus adaptew Awchemy pb1550");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:au1xpsc_smbus");
