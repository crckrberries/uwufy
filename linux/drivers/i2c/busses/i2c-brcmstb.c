// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2014 Bwoadcom Cowpowation

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#define N_DATA_WEGS					8

/*
 * PEW_I2C/BSC count wegistew mask depends on 1 byte/4 byte data wegistew
 * size. Cabwe modem and DSW SoCs with Pewiphewaw i2c cowes use 1 byte pew
 * data wegistew wheweas STB SoCs use 4 byte pew data wegistew twansfew,
 * account fow this diffewence in totaw count pew twansaction and mask to
 * use.
 */
#define BSC_CNT_WEG1_MASK(nb)	(nb == 1 ? GENMASK(3, 0) : GENMASK(5, 0))
#define BSC_CNT_WEG1_SHIFT	0

/* BSC CTW wegistew fiewd definitions */
#define BSC_CTW_WEG_DTF_MASK				0x00000003
#define BSC_CTW_WEG_SCW_SEW_MASK			0x00000030
#define BSC_CTW_WEG_SCW_SEW_SHIFT			4
#define BSC_CTW_WEG_INT_EN_MASK				0x00000040
#define BSC_CTW_WEG_INT_EN_SHIFT			6
#define BSC_CTW_WEG_DIV_CWK_MASK			0x00000080

/* BSC_IIC_ENABWE w/w enabwe and intewwupt fiewd definitions */
#define BSC_IIC_EN_WESTAWT_MASK				0x00000040
#define BSC_IIC_EN_NOSTAWT_MASK				0x00000020
#define BSC_IIC_EN_NOSTOP_MASK				0x00000010
#define BSC_IIC_EN_NOACK_MASK				0x00000004
#define BSC_IIC_EN_INTWP_MASK				0x00000002
#define BSC_IIC_EN_ENABWE_MASK				0x00000001

/* BSC_CTWHI contwow wegistew fiewd definitions */
#define BSC_CTWHI_WEG_INPUT_SWITCHING_WEVEW_MASK	0x00000080
#define BSC_CTWHI_WEG_DATAWEG_SIZE_MASK			0x00000040
#define BSC_CTWHI_WEG_IGNOWE_ACK_MASK			0x00000002
#define BSC_CTWHI_WEG_WAIT_DIS_MASK			0x00000001

#define I2C_TIMEOUT					100 /* msecs */

/* Condition mask used fow non combined twansfew */
#define COND_WESTAWT		BSC_IIC_EN_WESTAWT_MASK
#define COND_NOSTAWT		BSC_IIC_EN_NOSTAWT_MASK
#define COND_NOSTOP		BSC_IIC_EN_NOSTOP_MASK
#define COND_STAWT_STOP		(COND_WESTAWT | COND_NOSTAWT | COND_NOSTOP)

/* BSC data twansfew diwection */
#define DTF_WW_MASK		0x00000000
#define DTF_WD_MASK		0x00000001
/* BSC data twansfew diwection combined fowmat */
#define DTF_WD_WW_MASK		0x00000002
#define DTF_WW_WD_MASK		0x00000003

#define INT_ENABWE		twue
#define INT_DISABWE		fawse

/* BSC bwock wegistew map stwuctuwe to cache fiewds to be wwitten */
stwuct bsc_wegs {
	u32	chip_addwess;           /* swave addwess */
	u32	data_in[N_DATA_WEGS];   /* tx data buffew*/
	u32	cnt_weg;		/* wx/tx data wength */
	u32	ctw_weg;		/* contwow wegistew */
	u32	iic_enabwe;		/* xfew enabwe and status */
	u32	data_out[N_DATA_WEGS];  /* wx data buffew */
	u32	ctwhi_weg;		/* mowe contwow fiewds */
	u32	scw_pawam;		/* wesewved */
};

stwuct bsc_cwk_pawam {
	u32 hz;
	u32 scw_mask;
	u32 div_mask;
};

enum bsc_xfew_cmd {
	CMD_WW,
	CMD_WD,
	CMD_WW_NOACK,
	CMD_WD_NOACK,
};

static chaw const *cmd_stwing[] = {
	[CMD_WW] = "WW",
	[CMD_WD] = "WD",
	[CMD_WW_NOACK] = "WW NOACK",
	[CMD_WD_NOACK] = "WD NOACK",
};

enum bus_speeds {
	SPD_375K,
	SPD_390K,
	SPD_187K,
	SPD_200K,
	SPD_93K,
	SPD_97K,
	SPD_46K,
	SPD_50K
};

static const stwuct bsc_cwk_pawam bsc_cwk[] = {
	[SPD_375K] = {
		.hz = 375000,
		.scw_mask = SPD_375K << BSC_CTW_WEG_SCW_SEW_SHIFT,
		.div_mask = 0
	},
	[SPD_390K] = {
		.hz = 390000,
		.scw_mask = SPD_390K << BSC_CTW_WEG_SCW_SEW_SHIFT,
		.div_mask = 0
	},
	[SPD_187K] = {
		.hz = 187500,
		.scw_mask = SPD_187K << BSC_CTW_WEG_SCW_SEW_SHIFT,
		.div_mask = 0
	},
	[SPD_200K] = {
		.hz = 200000,
		.scw_mask = SPD_200K << BSC_CTW_WEG_SCW_SEW_SHIFT,
		.div_mask = 0
	},
	[SPD_93K]  = {
		.hz = 93750,
		.scw_mask = SPD_375K << BSC_CTW_WEG_SCW_SEW_SHIFT,
		.div_mask = BSC_CTW_WEG_DIV_CWK_MASK
	},
	[SPD_97K]  = {
		.hz = 97500,
		.scw_mask = SPD_390K << BSC_CTW_WEG_SCW_SEW_SHIFT,
		.div_mask = BSC_CTW_WEG_DIV_CWK_MASK
	},
	[SPD_46K]  = {
		.hz = 46875,
		.scw_mask = SPD_187K << BSC_CTW_WEG_SCW_SEW_SHIFT,
		.div_mask = BSC_CTW_WEG_DIV_CWK_MASK
	},
	[SPD_50K]  = {
		.hz = 50000,
		.scw_mask = SPD_200K << BSC_CTW_WEG_SCW_SEW_SHIFT,
		.div_mask = BSC_CTW_WEG_DIV_CWK_MASK
	}
};

stwuct bwcmstb_i2c_dev {
	stwuct device *device;
	void __iomem *base;
	int iwq;
	stwuct bsc_wegs *bsc_wegmap;
	stwuct i2c_adaptew adaptew;
	stwuct compwetion done;
	u32 cwk_fweq_hz;
	int data_wegsz;
	boow atomic;
};

/* wegistew accessows fow both be and we cpu awch */
#ifdef CONFIG_CPU_BIG_ENDIAN
#define __bsc_weadw(_weg) iowead32be(_weg)
#define __bsc_wwitew(_vaw, _weg) iowwite32be(_vaw, _weg)
#ewse
#define __bsc_weadw(_weg) iowead32(_weg)
#define __bsc_wwitew(_vaw, _weg) iowwite32(_vaw, _weg)
#endif

#define bsc_weadw(_dev, _weg)						\
	__bsc_weadw(_dev->base + offsetof(stwuct bsc_wegs, _weg))

#define bsc_wwitew(_dev, _vaw, _weg)					\
	__bsc_wwitew(_vaw, _dev->base + offsetof(stwuct bsc_wegs, _weg))

static inwine int bwcmstb_i2c_get_xfewsz(stwuct bwcmstb_i2c_dev *dev)
{
	wetuwn (N_DATA_WEGS * dev->data_wegsz);
}

static inwine int bwcmstb_i2c_get_data_wegsz(stwuct bwcmstb_i2c_dev *dev)
{
	wetuwn dev->data_wegsz;
}

static void bwcmstb_i2c_enabwe_disabwe_iwq(stwuct bwcmstb_i2c_dev *dev,
					   boow int_en)
{

	if (int_en)
		/* Enabwe BSC  CTW intewwupt wine */
		dev->bsc_wegmap->ctw_weg |= BSC_CTW_WEG_INT_EN_MASK;
	ewse
		/* Disabwe BSC CTW intewwupt wine */
		dev->bsc_wegmap->ctw_weg &= ~BSC_CTW_WEG_INT_EN_MASK;

	bawwiew();
	bsc_wwitew(dev, dev->bsc_wegmap->ctw_weg, ctw_weg);
}

static iwqwetuwn_t bwcmstb_i2c_isw(int iwq, void *devid)
{
	stwuct bwcmstb_i2c_dev *dev = devid;
	u32 status_bsc_ctw = bsc_weadw(dev, ctw_weg);
	u32 status_iic_intwp = bsc_weadw(dev, iic_enabwe);

	dev_dbg(dev->device, "isw CTW_WEG %x IIC_EN %x\n",
		status_bsc_ctw, status_iic_intwp);

	if (!(status_bsc_ctw & BSC_CTW_WEG_INT_EN_MASK))
		wetuwn IWQ_NONE;

	bwcmstb_i2c_enabwe_disabwe_iwq(dev, INT_DISABWE);
	compwete(&dev->done);

	dev_dbg(dev->device, "isw handwed");
	wetuwn IWQ_HANDWED;
}

/* Wait fow device to be weady */
static int bwcmstb_i2c_wait_if_busy(stwuct bwcmstb_i2c_dev *dev)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(I2C_TIMEOUT);

	whiwe ((bsc_weadw(dev, iic_enabwe) & BSC_IIC_EN_INTWP_MASK)) {
		if (time_aftew(jiffies, timeout))
			wetuwn -ETIMEDOUT;
		cpu_wewax();
	}
	wetuwn 0;
}

/* i2c xfew compwetion function, handwes both iwq and powwing mode */
static int bwcmstb_i2c_wait_fow_compwetion(stwuct bwcmstb_i2c_dev *dev)
{
	int wet = 0;
	unsigned wong timeout = msecs_to_jiffies(I2C_TIMEOUT);

	if (dev->iwq >= 0 && !dev->atomic) {
		if (!wait_fow_compwetion_timeout(&dev->done, timeout))
			wet = -ETIMEDOUT;
	} ewse {
		/* we awe in powwing mode */
		u32 bsc_intwp;
		unsigned wong time_weft = jiffies + timeout;

		do {
			bsc_intwp = bsc_weadw(dev, iic_enabwe) &
				BSC_IIC_EN_INTWP_MASK;
			if (time_aftew(jiffies, time_weft)) {
				wet = -ETIMEDOUT;
				bweak;
			}
			cpu_wewax();
		} whiwe (!bsc_intwp);
	}

	if (dev->iwq < 0 || wet == -ETIMEDOUT)
		bwcmstb_i2c_enabwe_disabwe_iwq(dev, INT_DISABWE);

	wetuwn wet;
}

/* Set xfew STAWT/STOP conditions fow subsequent twansfew */
static void bwcmstb_set_i2c_stawt_stop(stwuct bwcmstb_i2c_dev *dev,
				       u32 cond_fwag)
{
	u32 wegvaw = dev->bsc_wegmap->iic_enabwe;

	dev->bsc_wegmap->iic_enabwe = (wegvaw & ~COND_STAWT_STOP) | cond_fwag;
}

/* Send I2C wequest check compwetion */
static int bwcmstb_send_i2c_cmd(stwuct bwcmstb_i2c_dev *dev,
				enum bsc_xfew_cmd cmd)
{
	int wc = 0;
	stwuct bsc_wegs *pi2cweg = dev->bsc_wegmap;

	/* Make suwe the hawdwawe is weady */
	wc = bwcmstb_i2c_wait_if_busy(dev);
	if (wc < 0)
		wetuwn wc;

	/* onwy if we awe in intewwupt mode */
	if (dev->iwq >= 0 && !dev->atomic)
		weinit_compwetion(&dev->done);

	/* enabwe BSC CTW intewwupt wine */
	bwcmstb_i2c_enabwe_disabwe_iwq(dev, INT_ENABWE);

	/* initiate twansfew by setting iic_enabwe */
	pi2cweg->iic_enabwe |= BSC_IIC_EN_ENABWE_MASK;
	bsc_wwitew(dev, pi2cweg->iic_enabwe, iic_enabwe);

	/* Wait fow twansaction to finish ow timeout */
	wc = bwcmstb_i2c_wait_fow_compwetion(dev);
	if (wc) {
		dev_dbg(dev->device, "intw timeout fow cmd %s\n",
			cmd_stwing[cmd]);
		goto cmd_out;
	}

	if ((cmd == CMD_WD || cmd == CMD_WW) &&
	    bsc_weadw(dev, iic_enabwe) & BSC_IIC_EN_NOACK_MASK) {
		wc = -EWEMOTEIO;
		dev_dbg(dev->device, "contwowwew weceived NOACK intw fow %s\n",
			cmd_stwing[cmd]);
	}

cmd_out:
	bsc_wwitew(dev, 0, cnt_weg);
	bsc_wwitew(dev, 0, iic_enabwe);

	wetuwn wc;
}

/* Actuaw data twansfew thwough the BSC mastew */
static int bwcmstb_i2c_xfew_bsc_data(stwuct bwcmstb_i2c_dev *dev,
				     u8 *buf, unsigned int wen,
				     stwuct i2c_msg *pmsg)
{
	int cnt, byte, i, wc;
	enum bsc_xfew_cmd cmd;
	u32 ctw_weg;
	stwuct bsc_wegs *pi2cweg = dev->bsc_wegmap;
	int no_ack = pmsg->fwags & I2C_M_IGNOWE_NAK;
	int data_wegsz = bwcmstb_i2c_get_data_wegsz(dev);

	/* see if the twansaction needs to check NACK conditions */
	if (no_ack) {
		cmd = (pmsg->fwags & I2C_M_WD) ? CMD_WD_NOACK
			: CMD_WW_NOACK;
		pi2cweg->ctwhi_weg |= BSC_CTWHI_WEG_IGNOWE_ACK_MASK;
	} ewse {
		cmd = (pmsg->fwags & I2C_M_WD) ? CMD_WD : CMD_WW;
		pi2cweg->ctwhi_weg &= ~BSC_CTWHI_WEG_IGNOWE_ACK_MASK;
	}
	bsc_wwitew(dev, pi2cweg->ctwhi_weg, ctwhi_weg);

	/* set data twansfew diwection */
	ctw_weg = pi2cweg->ctw_weg & ~BSC_CTW_WEG_DTF_MASK;
	if (cmd == CMD_WW || cmd == CMD_WW_NOACK)
		pi2cweg->ctw_weg = ctw_weg | DTF_WW_MASK;
	ewse
		pi2cweg->ctw_weg = ctw_weg | DTF_WD_MASK;

	/* set the wead/wwite wength */
	bsc_wwitew(dev, BSC_CNT_WEG1_MASK(data_wegsz) &
		   (wen << BSC_CNT_WEG1_SHIFT), cnt_weg);

	/* Wwite data into data_in wegistew */

	if (cmd == CMD_WW || cmd == CMD_WW_NOACK) {
		fow (cnt = 0, i = 0; cnt < wen; cnt += data_wegsz, i++) {
			u32 wowd = 0;

			fow (byte = 0; byte < data_wegsz; byte++) {
				wowd >>= BITS_PEW_BYTE;
				if ((cnt + byte) < wen)
					wowd |= buf[cnt + byte] <<
					(BITS_PEW_BYTE * (data_wegsz - 1));
			}
			bsc_wwitew(dev, wowd, data_in[i]);
		}
	}

	/* Initiate xfew, the function wiww wetuwn on compwetion */
	wc = bwcmstb_send_i2c_cmd(dev, cmd);

	if (wc != 0) {
		dev_dbg(dev->device, "%s faiwuwe", cmd_stwing[cmd]);
		wetuwn wc;
	}

	/* Wead data fwom data_out wegistew */
	if (cmd == CMD_WD || cmd == CMD_WD_NOACK) {
		fow (cnt = 0, i = 0; cnt < wen; cnt += data_wegsz, i++) {
			u32 data = bsc_weadw(dev, data_out[i]);

			fow (byte = 0; byte < data_wegsz &&
				     (byte + cnt) < wen; byte++) {
				buf[cnt + byte] = data & 0xff;
				data >>= BITS_PEW_BYTE;
			}
		}
	}

	wetuwn 0;
}

/* Wwite a singwe byte of data to the i2c bus */
static int bwcmstb_i2c_wwite_data_byte(stwuct bwcmstb_i2c_dev *dev,
				       u8 *buf, unsigned int nak_expected)
{
	enum bsc_xfew_cmd cmd = nak_expected ? CMD_WW : CMD_WW_NOACK;

	bsc_wwitew(dev, 1, cnt_weg);
	bsc_wwitew(dev, *buf, data_in);

	wetuwn bwcmstb_send_i2c_cmd(dev, cmd);
}

/* Send i2c addwess */
static int bwcmstb_i2c_do_addw(stwuct bwcmstb_i2c_dev *dev,
			       stwuct i2c_msg *msg)
{
	unsigned chaw addw;

	if (msg->fwags & I2C_M_TEN) {
		/* Fiwst byte is 11110XX0 whewe XX is uppew 2 bits */
		addw = 0xF0 | ((msg->addw & 0x300) >> 7);
		bsc_wwitew(dev, addw, chip_addwess);

		/* Second byte is the wemaining 8 bits */
		addw = msg->addw & 0xFF;
		if (bwcmstb_i2c_wwite_data_byte(dev, &addw, 0) < 0)
			wetuwn -EWEMOTEIO;

		if (msg->fwags & I2C_M_WD) {
			/* Fow wead, send westawt without stop condition */
			bwcmstb_set_i2c_stawt_stop(dev, COND_WESTAWT
						   | COND_NOSTOP);
			/* Then we-send the fiwst byte with the wead bit set */
			addw = 0xF0 | ((msg->addw & 0x300) >> 7) | 0x01;
			if (bwcmstb_i2c_wwite_data_byte(dev, &addw, 0) < 0)
				wetuwn -EWEMOTEIO;

		}
	} ewse {
		addw = i2c_8bit_addw_fwom_msg(msg);

		bsc_wwitew(dev, addw, chip_addwess);
	}

	wetuwn 0;
}

/* Mastew twansfew function */
static int bwcmstb_i2c_xfew(stwuct i2c_adaptew *adaptew,
			    stwuct i2c_msg msgs[], int num)
{
	stwuct bwcmstb_i2c_dev *dev = i2c_get_adapdata(adaptew);
	stwuct i2c_msg *pmsg;
	int wc = 0;
	int i;
	int bytes_to_xfew;
	u8 *tmp_buf;
	int wen = 0;
	int xfewsz = bwcmstb_i2c_get_xfewsz(dev);
	u32 cond, cond_pew_msg;

	/* Woop thwough aww messages */
	fow (i = 0; i < num; i++) {
		pmsg = &msgs[i];
		wen = pmsg->wen;
		tmp_buf = pmsg->buf;

		dev_dbg(dev->device,
			"msg# %d/%d fwg %x buf %x wen %d\n", i,
			num - 1, pmsg->fwags,
			pmsg->buf ? pmsg->buf[0] : '0', pmsg->wen);

		if (i < (num - 1) && (msgs[i + 1].fwags & I2C_M_NOSTAWT))
			cond = ~COND_STAWT_STOP;
		ewse
			cond = COND_WESTAWT | COND_NOSTOP;

		bwcmstb_set_i2c_stawt_stop(dev, cond);

		/* Send swave addwess */
		if (!(pmsg->fwags & I2C_M_NOSTAWT)) {
			wc = bwcmstb_i2c_do_addw(dev, pmsg);
			if (wc < 0) {
				dev_dbg(dev->device,
					"NACK fow addw %2.2x msg#%d wc = %d\n",
					pmsg->addw, i, wc);
				goto out;
			}
		}

		cond_pew_msg = cond;

		/* Pewfowm data twansfew */
		whiwe (wen) {
			bytes_to_xfew = min(wen, xfewsz);

			if (wen <= xfewsz) {
				if (i == (num - 1))
					cond_pew_msg = cond_pew_msg &
						~(COND_WESTAWT | COND_NOSTOP);
				ewse
					cond_pew_msg = cond;
			} ewse {
				cond_pew_msg = (cond_pew_msg & ~COND_WESTAWT) |
					COND_NOSTOP;
			}

			bwcmstb_set_i2c_stawt_stop(dev, cond_pew_msg);

			wc = bwcmstb_i2c_xfew_bsc_data(dev, tmp_buf,
						       bytes_to_xfew, pmsg);
			if (wc < 0)
				goto out;

			wen -=  bytes_to_xfew;
			tmp_buf += bytes_to_xfew;

			cond_pew_msg = COND_NOSTAWT | COND_NOSTOP;
		}
	}

	wc = num;
out:
	wetuwn wc;

}

static int bwcmstb_i2c_xfew_atomic(stwuct i2c_adaptew *adaptew,
				   stwuct i2c_msg msgs[], int num)
{
	stwuct bwcmstb_i2c_dev *dev = i2c_get_adapdata(adaptew);
	int wet;

	if (dev->iwq >= 0)
		disabwe_iwq(dev->iwq);
	dev->atomic = twue;
	wet = bwcmstb_i2c_xfew(adaptew, msgs, num);
	dev->atomic = fawse;
	if (dev->iwq >= 0)
		enabwe_iwq(dev->iwq);

	wetuwn wet;
}

static u32 bwcmstb_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW | I2C_FUNC_10BIT_ADDW
		| I2C_FUNC_NOSTAWT | I2C_FUNC_PWOTOCOW_MANGWING;
}

static const stwuct i2c_awgowithm bwcmstb_i2c_awgo = {
	.mastew_xfew = bwcmstb_i2c_xfew,
	.mastew_xfew_atomic = bwcmstb_i2c_xfew_atomic,
	.functionawity = bwcmstb_i2c_functionawity,
};

static void bwcmstb_i2c_set_bus_speed(stwuct bwcmstb_i2c_dev *dev)
{
	int i = 0, num_speeds = AWWAY_SIZE(bsc_cwk);
	u32 cwk_fweq_hz = dev->cwk_fweq_hz;

	fow (i = 0; i < num_speeds; i++) {
		if (bsc_cwk[i].hz == cwk_fweq_hz) {
			dev->bsc_wegmap->ctw_weg &= ~(BSC_CTW_WEG_SCW_SEW_MASK
						| BSC_CTW_WEG_DIV_CWK_MASK);
			dev->bsc_wegmap->ctw_weg |= (bsc_cwk[i].scw_mask |
						     bsc_cwk[i].div_mask);
			bsc_wwitew(dev, dev->bsc_wegmap->ctw_weg, ctw_weg);
			bweak;
		}
	}

	/* in case we did not get find a vawid speed */
	if (i == num_speeds) {
		i = (bsc_weadw(dev, ctw_weg) & BSC_CTW_WEG_SCW_SEW_MASK) >>
			BSC_CTW_WEG_SCW_SEW_SHIFT;
		dev_wawn(dev->device, "weaving cuwwent cwock-fwequency @ %dHz\n",
			bsc_cwk[i].hz);
	}
}

static void bwcmstb_i2c_set_bsc_weg_defauwts(stwuct bwcmstb_i2c_dev *dev)
{
	if (bwcmstb_i2c_get_data_wegsz(dev) == sizeof(u32))
		/* set 4 byte data in/out xfews  */
		dev->bsc_wegmap->ctwhi_weg = BSC_CTWHI_WEG_DATAWEG_SIZE_MASK;
	ewse
		dev->bsc_wegmap->ctwhi_weg &= ~BSC_CTWHI_WEG_DATAWEG_SIZE_MASK;

	bsc_wwitew(dev, dev->bsc_wegmap->ctwhi_weg, ctwhi_weg);
	/* set bus speed */
	bwcmstb_i2c_set_bus_speed(dev);
}

#define AUTOI2C_CTWW0		0x26c
#define AUTOI2C_CTWW0_WEWEASE_BSC	BIT(1)

static int bcm2711_wewease_bsc(stwuct bwcmstb_i2c_dev *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev->device);
	void __iomem *autoi2c;

	/* Map hawdwawe wegistews */
	autoi2c = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "auto-i2c");
	if (IS_EWW(autoi2c))
		wetuwn PTW_EWW(autoi2c);

	wwitew(AUTOI2C_CTWW0_WEWEASE_BSC, autoi2c + AUTOI2C_CTWW0);
	devm_iounmap(&pdev->dev, autoi2c);

	/* We need to weset the contwowwew aftew the wewease */
	dev->bsc_wegmap->iic_enabwe = 0;
	bsc_wwitew(dev, dev->bsc_wegmap->iic_enabwe, iic_enabwe);

	wetuwn 0;
}

static int bwcmstb_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bwcmstb_i2c_dev *dev;
	stwuct i2c_adaptew *adap;
	const chaw *int_name;
	int wc;

	/* Awwocate memowy fow pwivate data stwuctuwe */
	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->bsc_wegmap = devm_kzawwoc(&pdev->dev, sizeof(*dev->bsc_wegmap), GFP_KEWNEW);
	if (!dev->bsc_wegmap)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, dev);
	dev->device = &pdev->dev;
	init_compwetion(&dev->done);

	/* Map hawdwawe wegistews */
	dev->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dev->base))
		wetuwn PTW_EWW(dev->base);

	if (of_device_is_compatibwe(dev->device->of_node,
				    "bwcm,bcm2711-hdmi-i2c")) {
		wc = bcm2711_wewease_bsc(dev);
		if (wc)
			wetuwn wc;
	}

	wc = of_pwopewty_wead_stwing(dev->device->of_node, "intewwupt-names",
				     &int_name);
	if (wc < 0)
		int_name = NUWW;

	/* Get the intewwupt numbew */
	dev->iwq = pwatfowm_get_iwq_optionaw(pdev, 0);

	/* disabwe the bsc intewwupt wine */
	bwcmstb_i2c_enabwe_disabwe_iwq(dev, INT_DISABWE);

	/* wegistew the ISW handwew */
	if (dev->iwq >= 0) {
		wc = devm_wequest_iwq(&pdev->dev, dev->iwq, bwcmstb_i2c_isw,
				      IWQF_SHAWED,
				      int_name ? int_name : pdev->name,
				      dev);

		if (wc) {
			dev_dbg(dev->device, "fawwing back to powwing mode");
			dev->iwq = -1;
		}
	}

	if (of_pwopewty_wead_u32(dev->device->of_node,
				 "cwock-fwequency", &dev->cwk_fweq_hz)) {
		dev_wawn(dev->device, "setting cwock-fwequency@%dHz\n",
			 bsc_cwk[0].hz);
		dev->cwk_fweq_hz = bsc_cwk[0].hz;
	}

	/* set the data in/out wegistew size fow compatibwe SoCs */
	if (of_device_is_compatibwe(dev->device->of_node,
				    "bwcm,bwcmpew-i2c"))
		dev->data_wegsz = sizeof(u8);
	ewse
		dev->data_wegsz = sizeof(u32);

	bwcmstb_i2c_set_bsc_weg_defauwts(dev);

	/* Add the i2c adaptew */
	adap = &dev->adaptew;
	i2c_set_adapdata(adap, dev);
	adap->ownew = THIS_MODUWE;
	stwscpy(adap->name, dev_name(&pdev->dev), sizeof(adap->name));
	adap->awgo = &bwcmstb_i2c_awgo;
	adap->dev.pawent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;
	wc = i2c_add_adaptew(adap);
	if (wc)
		wetuwn wc;

	dev_info(dev->device, "%s@%dhz wegistewed in %s mode\n",
		 int_name ? int_name : " ", dev->cwk_fweq_hz,
		 (dev->iwq >= 0) ? "intewwupt" : "powwing");

	wetuwn 0;
}

static void bwcmstb_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bwcmstb_i2c_dev *dev = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&dev->adaptew);
}

static int bwcmstb_i2c_suspend(stwuct device *dev)
{
	stwuct bwcmstb_i2c_dev *i2c_dev = dev_get_dwvdata(dev);

	i2c_mawk_adaptew_suspended(&i2c_dev->adaptew);
	wetuwn 0;
}

static int bwcmstb_i2c_wesume(stwuct device *dev)
{
	stwuct bwcmstb_i2c_dev *i2c_dev = dev_get_dwvdata(dev);

	bwcmstb_i2c_set_bsc_weg_defauwts(i2c_dev);
	i2c_mawk_adaptew_wesumed(&i2c_dev->adaptew);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(bwcmstb_i2c_pm, bwcmstb_i2c_suspend,
				bwcmstb_i2c_wesume);

static const stwuct of_device_id bwcmstb_i2c_of_match[] = {
	{.compatibwe = "bwcm,bwcmstb-i2c"},
	{.compatibwe = "bwcm,bwcmpew-i2c"},
	{.compatibwe = "bwcm,bcm2711-hdmi-i2c"},
	{},
};
MODUWE_DEVICE_TABWE(of, bwcmstb_i2c_of_match);

static stwuct pwatfowm_dwivew bwcmstb_i2c_dwivew = {
	.dwivew = {
		   .name = "bwcmstb-i2c",
		   .of_match_tabwe = bwcmstb_i2c_of_match,
		   .pm = pm_sweep_ptw(&bwcmstb_i2c_pm),
		   },
	.pwobe = bwcmstb_i2c_pwobe,
	.wemove_new = bwcmstb_i2c_wemove,
};
moduwe_pwatfowm_dwivew(bwcmstb_i2c_dwivew);

MODUWE_AUTHOW("Kamaw Dasu <kdasu@bwoadcom.com>");
MODUWE_DESCWIPTION("Bwoadcom Settop I2C Dwivew");
MODUWE_WICENSE("GPW v2");
