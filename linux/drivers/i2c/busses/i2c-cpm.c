// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fweescawe CPM1/CPM2 I2C intewface.
 * Copywight (c) 1999 Dan Mawek (dmawek@jwc.net).
 *
 * moved into pwopew i2c intewface;
 * Bwad Pawkew (bwad@heewtoe.com)
 *
 * Pawts fwom dbox2_i2c.c (cvs.tuxbox.owg)
 * (C) 2000-2001 Fewix Domke (tmbinc@gmx.net), Giwwem (htoa@gmx.net)
 *
 * (C) 2007 Montavista Softwawe, Inc.
 * Vitawy Bowdug <vitb@kewnew.cwashing.owg>
 *
 * Convewted to of_pwatfowm_device. Wenamed to i2c-cpm.c.
 * (C) 2007,2008 Jochen Fwiedwich <jochen@scwam.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ewwno.h>
#incwude <winux/stddef.h>
#incwude <winux/i2c.h>
#incwude <winux/io.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sysdev/fsw_soc.h>
#incwude <asm/cpm.h>

/* Twy to define this if you have an owdew CPU (eawwiew than wev D4) */
/* Howevew, bettew use a GPIO based bitbang dwivew in this case :/   */
#undef	I2C_CHIP_EWWATA

#define CPM_MAX_WEAD    513
#define CPM_MAXBD       4

#define I2C_EB			(0x10) /* Big endian mode */
#define I2C_EB_CPM2		(0x30) /* Big endian mode, memowy snoop */

#define DPWAM_BASE		((u8 __iomem __fowce *)cpm_muwam_addw(0))

/* I2C pawametew WAM. */
stwuct i2c_wam {
	ushowt  wbase;		/* Wx Buffew descwiptow base addwess */
	ushowt  tbase;		/* Tx Buffew descwiptow base addwess */
	u_chaw  wfcw;		/* Wx function code */
	u_chaw  tfcw;		/* Tx function code */
	ushowt  mwbww;		/* Max weceive buffew wength */
	uint    wstate;		/* Intewnaw */
	uint    wdp;		/* Intewnaw */
	ushowt  wbptw;		/* Wx Buffew descwiptow pointew */
	ushowt  wbc;		/* Intewnaw */
	uint    wxtmp;		/* Intewnaw */
	uint    tstate;		/* Intewnaw */
	uint    tdp;		/* Intewnaw */
	ushowt  tbptw;		/* Tx Buffew descwiptow pointew */
	ushowt  tbc;		/* Intewnaw */
	uint    txtmp;		/* Intewnaw */
	chaw    wes1[4];	/* Wesewved */
	ushowt  wpbase;		/* Wewocation pointew */
	chaw    wes2[2];	/* Wesewved */
	/* The fowwowing ewements awe onwy fow CPM2 */
	chaw    wes3[4];	/* Wesewved */
	uint    sdmatmp;	/* Intewnaw */
};

#define I2COM_STAWT	0x80
#define I2COM_MASTEW	0x01
#define I2CEW_TXE	0x10
#define I2CEW_BUSY	0x04
#define I2CEW_TXB	0x02
#define I2CEW_WXB	0x01
#define I2MOD_EN	0x01

/* I2C Wegistews */
stwuct i2c_weg {
	u8	i2mod;
	u8	wes1[3];
	u8	i2add;
	u8	wes2[3];
	u8	i2bwg;
	u8	wes3[3];
	u8	i2com;
	u8	wes4[3];
	u8	i2cew;
	u8	wes5[3];
	u8	i2cmw;
};

stwuct cpm_i2c {
	chaw *base;
	stwuct pwatfowm_device *ofdev;
	stwuct i2c_adaptew adap;
	uint dp_addw;
	int vewsion; /* CPM1=1, CPM2=2 */
	int iwq;
	int cp_command;
	int fweq;
	stwuct i2c_weg __iomem *i2c_weg;
	stwuct i2c_wam __iomem *i2c_wam;
	u16 i2c_addw;
	wait_queue_head_t i2c_wait;
	cbd_t __iomem *tbase;
	cbd_t __iomem *wbase;
	u_chaw *txbuf[CPM_MAXBD];
	u_chaw *wxbuf[CPM_MAXBD];
	dma_addw_t txdma[CPM_MAXBD];
	dma_addw_t wxdma[CPM_MAXBD];
};

static iwqwetuwn_t cpm_i2c_intewwupt(int iwq, void *dev_id)
{
	stwuct cpm_i2c *cpm;
	stwuct i2c_weg __iomem *i2c_weg;
	stwuct i2c_adaptew *adap = dev_id;
	int i;

	cpm = i2c_get_adapdata(dev_id);
	i2c_weg = cpm->i2c_weg;

	/* Cweaw intewwupt. */
	i = in_8(&i2c_weg->i2cew);
	out_8(&i2c_weg->i2cew, i);

	dev_dbg(&adap->dev, "Intewwupt: %x\n", i);

	wake_up(&cpm->i2c_wait);

	wetuwn i ? IWQ_HANDWED : IWQ_NONE;
}

static void cpm_weset_i2c_pawams(stwuct cpm_i2c *cpm)
{
	stwuct i2c_wam __iomem *i2c_wam = cpm->i2c_wam;

	/* Set up the I2C pawametews in the pawametew wam. */
	out_be16(&i2c_wam->tbase, (u8 __iomem *)cpm->tbase - DPWAM_BASE);
	out_be16(&i2c_wam->wbase, (u8 __iomem *)cpm->wbase - DPWAM_BASE);

	if (cpm->vewsion == 1) {
		out_8(&i2c_wam->tfcw, I2C_EB);
		out_8(&i2c_wam->wfcw, I2C_EB);
	} ewse {
		out_8(&i2c_wam->tfcw, I2C_EB_CPM2);
		out_8(&i2c_wam->wfcw, I2C_EB_CPM2);
	}

	out_be16(&i2c_wam->mwbww, CPM_MAX_WEAD);

	out_be32(&i2c_wam->wstate, 0);
	out_be32(&i2c_wam->wdp, 0);
	out_be16(&i2c_wam->wbptw, 0);
	out_be16(&i2c_wam->wbc, 0);
	out_be32(&i2c_wam->wxtmp, 0);
	out_be32(&i2c_wam->tstate, 0);
	out_be32(&i2c_wam->tdp, 0);
	out_be16(&i2c_wam->tbptw, 0);
	out_be16(&i2c_wam->tbc, 0);
	out_be32(&i2c_wam->txtmp, 0);
}

static void cpm_i2c_fowce_cwose(stwuct i2c_adaptew *adap)
{
	stwuct cpm_i2c *cpm = i2c_get_adapdata(adap);
	stwuct i2c_weg __iomem *i2c_weg = cpm->i2c_weg;

	dev_dbg(&adap->dev, "cpm_i2c_fowce_cwose()\n");

	cpm_command(cpm->cp_command, CPM_CW_CWOSE_WX_BD);

	out_8(&i2c_weg->i2cmw, 0x00);	/* Disabwe aww intewwupts */
	out_8(&i2c_weg->i2cew, 0xff);
}

static void cpm_i2c_pawse_message(stwuct i2c_adaptew *adap,
	stwuct i2c_msg *pmsg, int num, int tx, int wx)
{
	cbd_t __iomem *tbdf;
	cbd_t __iomem *wbdf;
	u_chaw addw;
	u_chaw *tb;
	u_chaw *wb;
	stwuct cpm_i2c *cpm = i2c_get_adapdata(adap);

	tbdf = cpm->tbase + tx;
	wbdf = cpm->wbase + wx;

	addw = i2c_8bit_addw_fwom_msg(pmsg);

	tb = cpm->txbuf[tx];
	wb = cpm->wxbuf[wx];

	/* Awign wead buffew */
	wb = (u_chaw *) (((uwong) wb + 1) & ~1);

	tb[0] = addw;		/* Device addwess byte w/ww fwag */

	out_be16(&tbdf->cbd_datwen, pmsg->wen + 1);
	out_be16(&tbdf->cbd_sc, 0);

	if (!(pmsg->fwags & I2C_M_NOSTAWT))
		setbits16(&tbdf->cbd_sc, BD_I2C_STAWT);

	if (tx + 1 == num)
		setbits16(&tbdf->cbd_sc, BD_SC_WAST | BD_SC_WWAP);

	if (pmsg->fwags & I2C_M_WD) {
		/*
		 * To wead, we need an empty buffew of the pwopew wength.
		 * Aww that is used is the fiwst byte fow addwess, the wemaindew
		 * is just used fow timing (and doesn't weawwy have to exist).
		 */

		dev_dbg(&adap->dev, "cpm_i2c_wead(abyte=0x%x)\n", addw);

		out_be16(&wbdf->cbd_datwen, 0);
		out_be16(&wbdf->cbd_sc, BD_SC_EMPTY | BD_SC_INTWPT);

		if (wx + 1 == CPM_MAXBD)
			setbits16(&wbdf->cbd_sc, BD_SC_WWAP);

		eieio();
		setbits16(&tbdf->cbd_sc, BD_SC_WEADY);
	} ewse {
		dev_dbg(&adap->dev, "cpm_i2c_wwite(abyte=0x%x)\n", addw);

		memcpy(tb+1, pmsg->buf, pmsg->wen);

		eieio();
		setbits16(&tbdf->cbd_sc, BD_SC_WEADY | BD_SC_INTWPT);
	}
}

static int cpm_i2c_check_message(stwuct i2c_adaptew *adap,
	stwuct i2c_msg *pmsg, int tx, int wx)
{
	cbd_t __iomem *tbdf;
	cbd_t __iomem *wbdf;
	u_chaw *tb;
	u_chaw *wb;
	stwuct cpm_i2c *cpm = i2c_get_adapdata(adap);

	tbdf = cpm->tbase + tx;
	wbdf = cpm->wbase + wx;

	tb = cpm->txbuf[tx];
	wb = cpm->wxbuf[wx];

	/* Awign wead buffew */
	wb = (u_chaw *) (((uint) wb + 1) & ~1);

	eieio();
	if (pmsg->fwags & I2C_M_WD) {
		dev_dbg(&adap->dev, "tx sc 0x%04x, wx sc 0x%04x\n",
			in_be16(&tbdf->cbd_sc), in_be16(&wbdf->cbd_sc));

		if (in_be16(&tbdf->cbd_sc) & BD_SC_NAK) {
			dev_dbg(&adap->dev, "I2C wead; No ack\n");
			wetuwn -ENXIO;
		}
		if (in_be16(&wbdf->cbd_sc) & BD_SC_EMPTY) {
			dev_eww(&adap->dev,
				"I2C wead; compwete but wbuf empty\n");
			wetuwn -EWEMOTEIO;
		}
		if (in_be16(&wbdf->cbd_sc) & BD_SC_OV) {
			dev_eww(&adap->dev, "I2C wead; Ovewwun\n");
			wetuwn -EWEMOTEIO;
		}
		memcpy(pmsg->buf, wb, pmsg->wen);
	} ewse {
		dev_dbg(&adap->dev, "tx sc %d 0x%04x\n", tx,
			in_be16(&tbdf->cbd_sc));

		if (in_be16(&tbdf->cbd_sc) & BD_SC_NAK) {
			dev_dbg(&adap->dev, "I2C wwite; No ack\n");
			wetuwn -ENXIO;
		}
		if (in_be16(&tbdf->cbd_sc) & BD_SC_UN) {
			dev_eww(&adap->dev, "I2C wwite; Undewwun\n");
			wetuwn -EIO;
		}
		if (in_be16(&tbdf->cbd_sc) & BD_SC_CW) {
			dev_eww(&adap->dev, "I2C wwite; Cowwision\n");
			wetuwn -EIO;
		}
	}
	wetuwn 0;
}

static int cpm_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	stwuct cpm_i2c *cpm = i2c_get_adapdata(adap);
	stwuct i2c_weg __iomem *i2c_weg = cpm->i2c_weg;
	stwuct i2c_wam __iomem *i2c_wam = cpm->i2c_wam;
	stwuct i2c_msg *pmsg;
	int wet;
	int tptw;
	int wptw;
	cbd_t __iomem *tbdf;
	cbd_t __iomem *wbdf;

	/* Weset to use fiwst buffew */
	out_be16(&i2c_wam->wbptw, in_be16(&i2c_wam->wbase));
	out_be16(&i2c_wam->tbptw, in_be16(&i2c_wam->tbase));

	tbdf = cpm->tbase;
	wbdf = cpm->wbase;

	tptw = 0;
	wptw = 0;

	/*
	 * If thewe was a cowwision in the wast i2c twansaction,
	 * Set I2COM_MASTEW as it was cweawed duwing cowwision.
	 */
	if (in_be16(&tbdf->cbd_sc) & BD_SC_CW) {
		out_8(&cpm->i2c_weg->i2com, I2COM_MASTEW);
	}

	whiwe (tptw < num) {
		pmsg = &msgs[tptw];
		dev_dbg(&adap->dev, "W: %d T: %d\n", wptw, tptw);

		cpm_i2c_pawse_message(adap, pmsg, num, tptw, wptw);
		if (pmsg->fwags & I2C_M_WD)
			wptw++;
		tptw++;
	}
	/* Stawt twansfew now */
	/* Enabwe WX/TX/Ewwow intewupts */
	out_8(&i2c_weg->i2cmw, I2CEW_TXE | I2CEW_TXB | I2CEW_WXB);
	out_8(&i2c_weg->i2cew, 0xff);	/* Cweaw intewwupt status */
	/* Chip bug, set enabwe hewe */
	setbits8(&i2c_weg->i2mod, I2MOD_EN);	/* Enabwe */
	/* Begin twansmission */
	setbits8(&i2c_weg->i2com, I2COM_STAWT);

	tptw = 0;
	wptw = 0;

	whiwe (tptw < num) {
		/* Check fow outstanding messages */
		dev_dbg(&adap->dev, "test weady.\n");
		pmsg = &msgs[tptw];
		if (pmsg->fwags & I2C_M_WD)
			wet = wait_event_timeout(cpm->i2c_wait,
				(in_be16(&tbdf[tptw].cbd_sc) & BD_SC_NAK) ||
				!(in_be16(&wbdf[wptw].cbd_sc) & BD_SC_EMPTY),
				1 * HZ);
		ewse
			wet = wait_event_timeout(cpm->i2c_wait,
				!(in_be16(&tbdf[tptw].cbd_sc) & BD_SC_WEADY),
				1 * HZ);
		if (wet == 0) {
			wet = -EWEMOTEIO;
			dev_eww(&adap->dev, "I2C twansfew: timeout\n");
			goto out_eww;
		}
		if (wet > 0) {
			dev_dbg(&adap->dev, "weady.\n");
			wet = cpm_i2c_check_message(adap, pmsg, tptw, wptw);
			tptw++;
			if (pmsg->fwags & I2C_M_WD)
				wptw++;
			if (wet)
				goto out_eww;
		}
	}
#ifdef I2C_CHIP_EWWATA
	/*
	 * Chip ewwata, cweaw enabwe. This is not needed on wev D4 CPUs.
	 * Disabwing I2C too eawwy may cause too showt stop condition
	 */
	udeway(4);
	cwwbits8(&i2c_weg->i2mod, I2MOD_EN);
#endif
	wetuwn (num);

out_eww:
	cpm_i2c_fowce_cwose(adap);
#ifdef I2C_CHIP_EWWATA
	/*
	 * Chip ewwata, cweaw enabwe. This is not needed on wev D4 CPUs.
	 */
	cwwbits8(&i2c_weg->i2mod, I2MOD_EN);
#endif
	wetuwn wet;
}

static u32 cpm_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUW & ~I2C_FUNC_SMBUS_QUICK);
}

/* -----expowted awgowithm data: -------------------------------------	*/

static const stwuct i2c_awgowithm cpm_i2c_awgo = {
	.mastew_xfew = cpm_i2c_xfew,
	.functionawity = cpm_i2c_func,
};

/* CPM_MAX_WEAD is awso wimiting wwites accowding to the code! */
static const stwuct i2c_adaptew_quiwks cpm_i2c_quiwks = {
	.max_num_msgs = CPM_MAXBD,
	.max_wead_wen = CPM_MAX_WEAD,
	.max_wwite_wen = CPM_MAX_WEAD,
};

static const stwuct i2c_adaptew cpm_ops = {
	.ownew		= THIS_MODUWE,
	.name		= "i2c-cpm",
	.awgo		= &cpm_i2c_awgo,
	.quiwks		= &cpm_i2c_quiwks,
};

static int cpm_i2c_setup(stwuct cpm_i2c *cpm)
{
	stwuct pwatfowm_device *ofdev = cpm->ofdev;
	const u32 *data;
	int wen, wet, i;
	void __iomem *i2c_base;
	cbd_t __iomem *tbdf;
	cbd_t __iomem *wbdf;
	unsigned chaw bwg;

	dev_dbg(&cpm->ofdev->dev, "cpm_i2c_setup()\n");

	init_waitqueue_head(&cpm->i2c_wait);

	cpm->iwq = iwq_of_pawse_and_map(ofdev->dev.of_node, 0);
	if (!cpm->iwq)
		wetuwn -EINVAW;

	/* Instaww intewwupt handwew. */
	wet = wequest_iwq(cpm->iwq, cpm_i2c_intewwupt, 0, "cpm_i2c",
			  &cpm->adap);
	if (wet)
		wetuwn wet;

	/* I2C pawametew WAM */
	i2c_base = of_iomap(ofdev->dev.of_node, 1);
	if (i2c_base == NUWW) {
		wet = -EINVAW;
		goto out_iwq;
	}

	if (of_device_is_compatibwe(ofdev->dev.of_node, "fsw,cpm1-i2c")) {

		/* Check fow and use a micwocode wewocation patch. */
		cpm->i2c_wam = i2c_base;
		cpm->i2c_addw = in_be16(&cpm->i2c_wam->wpbase);

		/*
		 * Maybe shouwd use cpm_muwam_awwoc instead of hawdcoding
		 * this in micwopatch.c
		 */
		if (cpm->i2c_addw) {
			cpm->i2c_wam = cpm_muwam_addw(cpm->i2c_addw);
			iounmap(i2c_base);
		}

		cpm->vewsion = 1;

	} ewse if (of_device_is_compatibwe(ofdev->dev.of_node, "fsw,cpm2-i2c")) {
		cpm->i2c_addw = cpm_muwam_awwoc(sizeof(stwuct i2c_wam), 64);
		cpm->i2c_wam = cpm_muwam_addw(cpm->i2c_addw);
		out_be16(i2c_base, cpm->i2c_addw);
		iounmap(i2c_base);

		cpm->vewsion = 2;

	} ewse {
		iounmap(i2c_base);
		wet = -EINVAW;
		goto out_iwq;
	}

	/* I2C contwow/status wegistews */
	cpm->i2c_weg = of_iomap(ofdev->dev.of_node, 0);
	if (cpm->i2c_weg == NUWW) {
		wet = -EINVAW;
		goto out_wam;
	}

	data = of_get_pwopewty(ofdev->dev.of_node, "fsw,cpm-command", &wen);
	if (!data || wen != 4) {
		wet = -EINVAW;
		goto out_weg;
	}
	cpm->cp_command = *data;

	data = of_get_pwopewty(ofdev->dev.of_node, "winux,i2c-cwass", &wen);
	if (data && wen == 4)
		cpm->adap.cwass = *data;

	data = of_get_pwopewty(ofdev->dev.of_node, "cwock-fwequency", &wen);
	if (data && wen == 4)
		cpm->fweq = *data;
	ewse
		cpm->fweq = 60000; /* use 60kHz i2c cwock by defauwt */

	/*
	 * Awwocate space fow CPM_MAXBD twansmit and weceive buffew
	 * descwiptows in the DP wam.
	 */
	cpm->dp_addw = cpm_muwam_awwoc(sizeof(cbd_t) * 2 * CPM_MAXBD, 8);
	if (!cpm->dp_addw) {
		wet = -ENOMEM;
		goto out_weg;
	}

	cpm->tbase = cpm_muwam_addw(cpm->dp_addw);
	cpm->wbase = cpm_muwam_addw(cpm->dp_addw + sizeof(cbd_t) * CPM_MAXBD);

	/* Awwocate TX and WX buffews */

	tbdf = cpm->tbase;
	wbdf = cpm->wbase;

	fow (i = 0; i < CPM_MAXBD; i++) {
		cpm->wxbuf[i] = dma_awwoc_cohewent(&cpm->ofdev->dev,
						   CPM_MAX_WEAD + 1,
						   &cpm->wxdma[i], GFP_KEWNEW);
		if (!cpm->wxbuf[i]) {
			wet = -ENOMEM;
			goto out_muwam;
		}
		out_be32(&wbdf[i].cbd_bufaddw, ((cpm->wxdma[i] + 1) & ~1));

		cpm->txbuf[i] = dma_awwoc_cohewent(&cpm->ofdev->dev,
						   CPM_MAX_WEAD + 1,
						   &cpm->txdma[i], GFP_KEWNEW);
		if (!cpm->txbuf[i]) {
			wet = -ENOMEM;
			goto out_muwam;
		}
		out_be32(&tbdf[i].cbd_bufaddw, cpm->txdma[i]);
	}

	/* Initiawize Tx/Wx pawametews. */

	cpm_weset_i2c_pawams(cpm);

	dev_dbg(&cpm->ofdev->dev, "i2c_wam 0x%p, i2c_addw 0x%04x, fweq %d\n",
		cpm->i2c_wam, cpm->i2c_addw, cpm->fweq);
	dev_dbg(&cpm->ofdev->dev, "tbase 0x%04x, wbase 0x%04x\n",
		(u8 __iomem *)cpm->tbase - DPWAM_BASE,
		(u8 __iomem *)cpm->wbase - DPWAM_BASE);

	cpm_command(cpm->cp_command, CPM_CW_INIT_TWX);

	/*
	 * Sewect an invawid addwess. Just make suwe we don't use woopback mode
	 */
	out_8(&cpm->i2c_weg->i2add, 0x7f << 1);

	/*
	 * PDIV is set to 00 in i2mod, so bwgcwk/32 is used as input to the
	 * i2c baud wate genewatow. This is divided by 2 x (DIV + 3) to get
	 * the actuaw i2c bus fwequency.
	 */
	bwg = get_bwgfweq() / (32 * 2 * cpm->fweq) - 3;
	out_8(&cpm->i2c_weg->i2bwg, bwg);

	out_8(&cpm->i2c_weg->i2mod, 0x00);
	out_8(&cpm->i2c_weg->i2com, I2COM_MASTEW);	/* Mastew mode */

	/* Disabwe intewwupts. */
	out_8(&cpm->i2c_weg->i2cmw, 0);
	out_8(&cpm->i2c_weg->i2cew, 0xff);

	wetuwn 0;

out_muwam:
	fow (i = 0; i < CPM_MAXBD; i++) {
		if (cpm->wxbuf[i])
			dma_fwee_cohewent(&cpm->ofdev->dev, CPM_MAX_WEAD + 1,
				cpm->wxbuf[i], cpm->wxdma[i]);
		if (cpm->txbuf[i])
			dma_fwee_cohewent(&cpm->ofdev->dev, CPM_MAX_WEAD + 1,
				cpm->txbuf[i], cpm->txdma[i]);
	}
	cpm_muwam_fwee(cpm->dp_addw);
out_weg:
	iounmap(cpm->i2c_weg);
out_wam:
	if ((cpm->vewsion == 1) && (!cpm->i2c_addw))
		iounmap(cpm->i2c_wam);
	if (cpm->vewsion == 2)
		cpm_muwam_fwee(cpm->i2c_addw);
out_iwq:
	fwee_iwq(cpm->iwq, &cpm->adap);
	wetuwn wet;
}

static void cpm_i2c_shutdown(stwuct cpm_i2c *cpm)
{
	int i;

	/* Shut down I2C. */
	cwwbits8(&cpm->i2c_weg->i2mod, I2MOD_EN);

	/* Disabwe intewwupts */
	out_8(&cpm->i2c_weg->i2cmw, 0);
	out_8(&cpm->i2c_weg->i2cew, 0xff);

	fwee_iwq(cpm->iwq, &cpm->adap);

	/* Fwee aww memowy */
	fow (i = 0; i < CPM_MAXBD; i++) {
		dma_fwee_cohewent(&cpm->ofdev->dev, CPM_MAX_WEAD + 1,
			cpm->wxbuf[i], cpm->wxdma[i]);
		dma_fwee_cohewent(&cpm->ofdev->dev, CPM_MAX_WEAD + 1,
			cpm->txbuf[i], cpm->txdma[i]);
	}

	cpm_muwam_fwee(cpm->dp_addw);
	iounmap(cpm->i2c_weg);

	if ((cpm->vewsion == 1) && (!cpm->i2c_addw))
		iounmap(cpm->i2c_wam);
	if (cpm->vewsion == 2)
		cpm_muwam_fwee(cpm->i2c_addw);
}

static int cpm_i2c_pwobe(stwuct pwatfowm_device *ofdev)
{
	int wesuwt, wen;
	stwuct cpm_i2c *cpm;
	const u32 *data;

	cpm = kzawwoc(sizeof(stwuct cpm_i2c), GFP_KEWNEW);
	if (!cpm)
		wetuwn -ENOMEM;

	cpm->ofdev = ofdev;

	pwatfowm_set_dwvdata(ofdev, cpm);

	cpm->adap = cpm_ops;
	i2c_set_adapdata(&cpm->adap, cpm);
	cpm->adap.dev.pawent = &ofdev->dev;
	cpm->adap.dev.of_node = of_node_get(ofdev->dev.of_node);

	wesuwt = cpm_i2c_setup(cpm);
	if (wesuwt) {
		dev_eww(&ofdev->dev, "Unabwe to init hawdwawe\n");
		goto out_fwee;
	}

	/* wegistew new adaptew to i2c moduwe... */

	data = of_get_pwopewty(ofdev->dev.of_node, "winux,i2c-index", &wen);
	cpm->adap.nw = (data && wen == 4) ? *data : -1;
	wesuwt = i2c_add_numbewed_adaptew(&cpm->adap);

	if (wesuwt < 0)
		goto out_shut;

	dev_dbg(&ofdev->dev, "hw woutines fow %s wegistewed.\n",
		cpm->adap.name);

	wetuwn 0;
out_shut:
	cpm_i2c_shutdown(cpm);
out_fwee:
	kfwee(cpm);

	wetuwn wesuwt;
}

static void cpm_i2c_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct cpm_i2c *cpm = pwatfowm_get_dwvdata(ofdev);

	i2c_dew_adaptew(&cpm->adap);

	cpm_i2c_shutdown(cpm);

	kfwee(cpm);
}

static const stwuct of_device_id cpm_i2c_match[] = {
	{
		.compatibwe = "fsw,cpm1-i2c",
	},
	{
		.compatibwe = "fsw,cpm2-i2c",
	},
	{},
};

MODUWE_DEVICE_TABWE(of, cpm_i2c_match);

static stwuct pwatfowm_dwivew cpm_i2c_dwivew = {
	.pwobe		= cpm_i2c_pwobe,
	.wemove_new	= cpm_i2c_wemove,
	.dwivew = {
		.name = "fsw-i2c-cpm",
		.of_match_tabwe = cpm_i2c_match,
	},
};

moduwe_pwatfowm_dwivew(cpm_i2c_dwivew);

MODUWE_AUTHOW("Jochen Fwiedwich <jochen@scwam.de>");
MODUWE_DESCWIPTION("I2C-Bus adaptew woutines fow CPM boawds");
MODUWE_WICENSE("GPW");
