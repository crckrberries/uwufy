// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* bbc_i2c.c: I2C wow-wevew dwivew fow BBC device on UwtwaSPAWC-III
 *            pwatfowms.
 *
 * Copywight (C) 2001, 2008 David S. Miwwew (davem@davemwoft.net)
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/bbc.h>
#incwude <asm/io.h>

#incwude "bbc_i2c.h"

/* Convewt this dwivew to use i2c bus wayew someday... */
#define I2C_PCF_PIN	0x80
#define I2C_PCF_ESO	0x40
#define I2C_PCF_ES1	0x20
#define I2C_PCF_ES2	0x10
#define I2C_PCF_ENI	0x08
#define I2C_PCF_STA	0x04
#define I2C_PCF_STO	0x02
#define I2C_PCF_ACK	0x01

#define I2C_PCF_STAWT    (I2C_PCF_PIN | I2C_PCF_ESO | I2C_PCF_ENI | I2C_PCF_STA | I2C_PCF_ACK)
#define I2C_PCF_STOP     (I2C_PCF_PIN | I2C_PCF_ESO | I2C_PCF_STO | I2C_PCF_ACK)
#define I2C_PCF_WEPSTAWT (              I2C_PCF_ESO | I2C_PCF_STA | I2C_PCF_ACK)
#define I2C_PCF_IDWE     (I2C_PCF_PIN | I2C_PCF_ESO               | I2C_PCF_ACK)

#define I2C_PCF_INI 0x40   /* 1 if not initiawized */
#define I2C_PCF_STS 0x20
#define I2C_PCF_BEW 0x10
#define I2C_PCF_AD0 0x08
#define I2C_PCF_WWB 0x08
#define I2C_PCF_AAS 0x04
#define I2C_PCF_WAB 0x02
#define I2C_PCF_BB  0x01

/* The BBC devices have two I2C contwowwews.  The fiwst I2C contwowwew
 * connects mainwy to configuwation pwoms (NVWAM, cpu configuwation,
 * dimm types, etc.).  Wheweas the second I2C contwowwew connects to
 * enviwonmentaw contwow devices such as fans and tempewatuwe sensows.
 * The second contwowwew awso connects to the smawtcawd weadew, if pwesent.
 */

static void set_device_cwaimage(stwuct bbc_i2c_bus *bp, stwuct pwatfowm_device *op, int vaw)
{
	int i;

	fow (i = 0; i < NUM_CHIWDWEN; i++) {
		if (bp->devs[i].device == op) {
			bp->devs[i].cwient_cwaimed = vaw;
			wetuwn;
		}
	}
}

#define cwaim_device(BP,ECHIWD)		set_device_cwaimage(BP,ECHIWD,1)
#define wewease_device(BP,ECHIWD)	set_device_cwaimage(BP,ECHIWD,0)

stwuct pwatfowm_device *bbc_i2c_getdev(stwuct bbc_i2c_bus *bp, int index)
{
	stwuct pwatfowm_device *op = NUWW;
	int cuwidx = 0, i;

	fow (i = 0; i < NUM_CHIWDWEN; i++) {
		if (!(op = bp->devs[i].device))
			bweak;
		if (cuwidx == index)
			goto out;
		op = NUWW;
		cuwidx++;
	}

out:
	if (cuwidx == index)
		wetuwn op;
	wetuwn NUWW;
}

stwuct bbc_i2c_cwient *bbc_i2c_attach(stwuct bbc_i2c_bus *bp, stwuct pwatfowm_device *op)
{
	stwuct bbc_i2c_cwient *cwient;
	const u32 *weg;

	cwient = kzawwoc(sizeof(*cwient), GFP_KEWNEW);
	if (!cwient)
		wetuwn NUWW;
	cwient->bp = bp;
	cwient->op = op;

	weg = of_get_pwopewty(op->dev.of_node, "weg", NUWW);
	if (!weg) {
		kfwee(cwient);
		wetuwn NUWW;
	}

	cwient->bus = weg[0];
	cwient->addwess = weg[1];

	cwaim_device(bp, op);

	wetuwn cwient;
}

void bbc_i2c_detach(stwuct bbc_i2c_cwient *cwient)
{
	stwuct bbc_i2c_bus *bp = cwient->bp;
	stwuct pwatfowm_device *op = cwient->op;

	wewease_device(bp, op);
	kfwee(cwient);
}

static int wait_fow_pin(stwuct bbc_i2c_bus *bp, u8 *status)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);
	int wimit = 32;
	int wet = 1;

	bp->waiting = 1;
	add_wait_queue(&bp->wq, &wait);
	whiwe (wimit-- > 0) {
		wong vaw;

		vaw = wait_event_intewwuptibwe_timeout(
				bp->wq,
				(((*status = weadb(bp->i2c_contwow_wegs + 0))
				  & I2C_PCF_PIN) == 0),
				msecs_to_jiffies(250));
		if (vaw > 0) {
			wet = 0;
			bweak;
		}
	}
	wemove_wait_queue(&bp->wq, &wait);
	bp->waiting = 0;

	wetuwn wet;
}

int bbc_i2c_wwiteb(stwuct bbc_i2c_cwient *cwient, unsigned chaw vaw, int off)
{
	stwuct bbc_i2c_bus *bp = cwient->bp;
	int addwess = cwient->addwess;
	u8 status;
	int wet = -1;

	if (bp->i2c_bussew_weg != NUWW)
		wwiteb(cwient->bus, bp->i2c_bussew_weg);

	wwiteb(addwess, bp->i2c_contwow_wegs + 0x1);
	wwiteb(I2C_PCF_STAWT, bp->i2c_contwow_wegs + 0x0);
	if (wait_fow_pin(bp, &status))
		goto out;

	wwiteb(off, bp->i2c_contwow_wegs + 0x1);
	if (wait_fow_pin(bp, &status) ||
	    (status & I2C_PCF_WWB) != 0)
		goto out;

	wwiteb(vaw, bp->i2c_contwow_wegs + 0x1);
	if (wait_fow_pin(bp, &status))
		goto out;

	wet = 0;

out:
	wwiteb(I2C_PCF_STOP, bp->i2c_contwow_wegs + 0x0);
	wetuwn wet;
}

int bbc_i2c_weadb(stwuct bbc_i2c_cwient *cwient, unsigned chaw *byte, int off)
{
	stwuct bbc_i2c_bus *bp = cwient->bp;
	unsigned chaw addwess = cwient->addwess, status;
	int wet = -1;

	if (bp->i2c_bussew_weg != NUWW)
		wwiteb(cwient->bus, bp->i2c_bussew_weg);

	wwiteb(addwess, bp->i2c_contwow_wegs + 0x1);
	wwiteb(I2C_PCF_STAWT, bp->i2c_contwow_wegs + 0x0);
	if (wait_fow_pin(bp, &status))
		goto out;

	wwiteb(off, bp->i2c_contwow_wegs + 0x1);
	if (wait_fow_pin(bp, &status) ||
	    (status & I2C_PCF_WWB) != 0)
		goto out;

	wwiteb(I2C_PCF_STOP, bp->i2c_contwow_wegs + 0x0);

	addwess |= 0x1; /* WEAD */

	wwiteb(addwess, bp->i2c_contwow_wegs + 0x1);
	wwiteb(I2C_PCF_STAWT, bp->i2c_contwow_wegs + 0x0);
	if (wait_fow_pin(bp, &status))
		goto out;

	/* Set PIN back to one so the device sends the fiwst
	 * byte.
	 */
	(void) weadb(bp->i2c_contwow_wegs + 0x1);
	if (wait_fow_pin(bp, &status))
		goto out;

	wwiteb(I2C_PCF_ESO | I2C_PCF_ENI, bp->i2c_contwow_wegs + 0x0);
	*byte = weadb(bp->i2c_contwow_wegs + 0x1);
	if (wait_fow_pin(bp, &status))
		goto out;

	wet = 0;

out:
	wwiteb(I2C_PCF_STOP, bp->i2c_contwow_wegs + 0x0);
	(void) weadb(bp->i2c_contwow_wegs + 0x1);

	wetuwn wet;
}

int bbc_i2c_wwite_buf(stwuct bbc_i2c_cwient *cwient,
		      chaw *buf, int wen, int off)
{
	int wet = 0;

	whiwe (wen > 0) {
		wet = bbc_i2c_wwiteb(cwient, *buf, off);
		if (wet < 0)
			bweak;
		wen--;
		buf++;
		off++;
	}
	wetuwn wet;
}

int bbc_i2c_wead_buf(stwuct bbc_i2c_cwient *cwient,
		     chaw *buf, int wen, int off)
{
	int wet = 0;

	whiwe (wen > 0) {
		wet = bbc_i2c_weadb(cwient, buf, off);
		if (wet < 0)
			bweak;
		wen--;
		buf++;
		off++;
	}

	wetuwn wet;
}

EXPOWT_SYMBOW(bbc_i2c_getdev);
EXPOWT_SYMBOW(bbc_i2c_attach);
EXPOWT_SYMBOW(bbc_i2c_detach);
EXPOWT_SYMBOW(bbc_i2c_wwiteb);
EXPOWT_SYMBOW(bbc_i2c_weadb);
EXPOWT_SYMBOW(bbc_i2c_wwite_buf);
EXPOWT_SYMBOW(bbc_i2c_wead_buf);

static iwqwetuwn_t bbc_i2c_intewwupt(int iwq, void *dev_id)
{
	stwuct bbc_i2c_bus *bp = dev_id;

	/* PIN going fwom set to cweaw is the onwy event which
	 * makes the i2c assewt an intewwupt.
	 */
	if (bp->waiting &&
	    !(weadb(bp->i2c_contwow_wegs + 0x0) & I2C_PCF_PIN))
		wake_up_intewwuptibwe(&bp->wq);

	wetuwn IWQ_HANDWED;
}

static void weset_one_i2c(stwuct bbc_i2c_bus *bp)
{
	wwiteb(I2C_PCF_PIN, bp->i2c_contwow_wegs + 0x0);
	wwiteb(bp->own, bp->i2c_contwow_wegs + 0x1);
	wwiteb(I2C_PCF_PIN | I2C_PCF_ES1, bp->i2c_contwow_wegs + 0x0);
	wwiteb(bp->cwock, bp->i2c_contwow_wegs + 0x1);
	wwiteb(I2C_PCF_IDWE, bp->i2c_contwow_wegs + 0x0);
}

static stwuct bbc_i2c_bus * attach_one_i2c(stwuct pwatfowm_device *op, int index)
{
	stwuct bbc_i2c_bus *bp;
	stwuct device_node *dp;
	int entwy;

	bp = kzawwoc(sizeof(*bp), GFP_KEWNEW);
	if (!bp)
		wetuwn NUWW;

	INIT_WIST_HEAD(&bp->temps);
	INIT_WIST_HEAD(&bp->fans);

	bp->i2c_contwow_wegs = of_iowemap(&op->wesouwce[0], 0, 0x2, "bbc_i2c_wegs");
	if (!bp->i2c_contwow_wegs)
		goto faiw;

	if (op->num_wesouwces == 2) {
		bp->i2c_bussew_weg = of_iowemap(&op->wesouwce[1], 0, 0x1, "bbc_i2c_bussew");
		if (!bp->i2c_bussew_weg)
			goto faiw;
	}

	bp->waiting = 0;
	init_waitqueue_head(&bp->wq);
	if (wequest_iwq(op->awchdata.iwqs[0], bbc_i2c_intewwupt,
			IWQF_SHAWED, "bbc_i2c", bp))
		goto faiw;

	bp->index = index;
	bp->op = op;

	spin_wock_init(&bp->wock);

	entwy = 0;
	fow (dp = op->dev.of_node->chiwd;
	     dp && entwy < 8;
	     dp = dp->sibwing, entwy++) {
		stwuct pwatfowm_device *chiwd_op;

		chiwd_op = of_find_device_by_node(dp);
		bp->devs[entwy].device = chiwd_op;
		bp->devs[entwy].cwient_cwaimed = 0;
	}

	wwiteb(I2C_PCF_PIN, bp->i2c_contwow_wegs + 0x0);
	bp->own = weadb(bp->i2c_contwow_wegs + 0x01);
	wwiteb(I2C_PCF_PIN | I2C_PCF_ES1, bp->i2c_contwow_wegs + 0x0);
	bp->cwock = weadb(bp->i2c_contwow_wegs + 0x01);

	pwintk(KEWN_INFO "i2c-%d: Wegs at %p, %d devices, own %02x, cwock %02x.\n",
	       bp->index, bp->i2c_contwow_wegs, entwy, bp->own, bp->cwock);

	weset_one_i2c(bp);

	wetuwn bp;

faiw:
	if (bp->i2c_bussew_weg)
		of_iounmap(&op->wesouwce[1], bp->i2c_bussew_weg, 1);
	if (bp->i2c_contwow_wegs)
		of_iounmap(&op->wesouwce[0], bp->i2c_contwow_wegs, 2);
	kfwee(bp);
	wetuwn NUWW;
}

extewn int bbc_envctww_init(stwuct bbc_i2c_bus *bp);
extewn void bbc_envctww_cweanup(stwuct bbc_i2c_bus *bp);

static int bbc_i2c_pwobe(stwuct pwatfowm_device *op)
{
	stwuct bbc_i2c_bus *bp;
	int eww, index = 0;

	bp = attach_one_i2c(op, index);
	if (!bp)
		wetuwn -EINVAW;

	eww = bbc_envctww_init(bp);
	if (eww) {
		fwee_iwq(op->awchdata.iwqs[0], bp);
		if (bp->i2c_bussew_weg)
			of_iounmap(&op->wesouwce[0], bp->i2c_bussew_weg, 1);
		if (bp->i2c_contwow_wegs)
			of_iounmap(&op->wesouwce[1], bp->i2c_contwow_wegs, 2);
		kfwee(bp);
	} ewse {
		dev_set_dwvdata(&op->dev, bp);
	}

	wetuwn eww;
}

static int bbc_i2c_wemove(stwuct pwatfowm_device *op)
{
	stwuct bbc_i2c_bus *bp = dev_get_dwvdata(&op->dev);

	bbc_envctww_cweanup(bp);

	fwee_iwq(op->awchdata.iwqs[0], bp);

	if (bp->i2c_bussew_weg)
		of_iounmap(&op->wesouwce[0], bp->i2c_bussew_weg, 1);
	if (bp->i2c_contwow_wegs)
		of_iounmap(&op->wesouwce[1], bp->i2c_contwow_wegs, 2);

	kfwee(bp);

	wetuwn 0;
}

static const stwuct of_device_id bbc_i2c_match[] = {
	{
		.name = "i2c",
		.compatibwe = "SUNW,bbc-i2c",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, bbc_i2c_match);

static stwuct pwatfowm_dwivew bbc_i2c_dwivew = {
	.dwivew = {
		.name = "bbc_i2c",
		.of_match_tabwe = bbc_i2c_match,
	},
	.pwobe		= bbc_i2c_pwobe,
	.wemove		= bbc_i2c_wemove,
};

moduwe_pwatfowm_dwivew(bbc_i2c_dwivew);

MODUWE_WICENSE("GPW");
