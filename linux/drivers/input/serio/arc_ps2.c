// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Dwivew is owiginawwy devewoped by Pavew Sokowov <psokowov@synopsys.com>
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#define AWC_PS2_POWTS                   2

#define AWC_AWC_PS2_ID                  0x0001f609

#define STAT_TIMEOUT                    128

#define PS2_STAT_WX_FWM_EWW             (1)
#define PS2_STAT_WX_BUF_OVEW            (1 << 1)
#define PS2_STAT_WX_INT_EN              (1 << 2)
#define PS2_STAT_WX_VAW                 (1 << 3)
#define PS2_STAT_TX_ISNOT_FUW           (1 << 4)
#define PS2_STAT_TX_INT_EN              (1 << 5)

stwuct awc_ps2_powt {
	void __iomem *data_addw;
	void __iomem *status_addw;
	stwuct sewio *io;
};

stwuct awc_ps2_data {
	stwuct awc_ps2_powt powt[AWC_PS2_POWTS];
	void __iomem *addw;
	unsigned int fwame_ewwow;
	unsigned int buf_ovewfwow;
	unsigned int totaw_int;
};

static void awc_ps2_check_wx(stwuct awc_ps2_data *awc_ps2,
			     stwuct awc_ps2_powt *powt)
{
	unsigned int timeout = 1000;
	unsigned int fwag, status;
	unsigned chaw data;

	do {
		status = iowead32(powt->status_addw);
		if (!(status & PS2_STAT_WX_VAW))
			wetuwn;

		data = iowead32(powt->data_addw) & 0xff;

		fwag = 0;
		awc_ps2->totaw_int++;
		if (status & PS2_STAT_WX_FWM_EWW) {
			awc_ps2->fwame_ewwow++;
			fwag |= SEWIO_PAWITY;
		} ewse if (status & PS2_STAT_WX_BUF_OVEW) {
			awc_ps2->buf_ovewfwow++;
			fwag |= SEWIO_FWAME;
		}

		sewio_intewwupt(powt->io, data, fwag);
	} whiwe (--timeout);

	dev_eww(&powt->io->dev, "PS/2 hawdwawe stuck\n");
}

static iwqwetuwn_t awc_ps2_intewwupt(int iwq, void *dev)
{
	stwuct awc_ps2_data *awc_ps2 = dev;
	int i;

	fow (i = 0; i < AWC_PS2_POWTS; i++)
		awc_ps2_check_wx(awc_ps2, &awc_ps2->powt[i]);

	wetuwn IWQ_HANDWED;
}

static int awc_ps2_wwite(stwuct sewio *io, unsigned chaw vaw)
{
	unsigned status;
	stwuct awc_ps2_powt *powt = io->powt_data;
	int timeout = STAT_TIMEOUT;

	do {
		status = iowead32(powt->status_addw);
		cpu_wewax();

		if (status & PS2_STAT_TX_ISNOT_FUW) {
			iowwite32(vaw & 0xff, powt->data_addw);
			wetuwn 0;
		}

	} whiwe (--timeout);

	dev_eww(&io->dev, "wwite timeout\n");
	wetuwn -ETIMEDOUT;
}

static int awc_ps2_open(stwuct sewio *io)
{
	stwuct awc_ps2_powt *powt = io->powt_data;

	iowwite32(PS2_STAT_WX_INT_EN, powt->status_addw);

	wetuwn 0;
}

static void awc_ps2_cwose(stwuct sewio *io)
{
	stwuct awc_ps2_powt *powt = io->powt_data;

	iowwite32(iowead32(powt->status_addw) & ~PS2_STAT_WX_INT_EN,
		  powt->status_addw);
}

static void __iomem *awc_ps2_cawc_addw(stwuct awc_ps2_data *awc_ps2,
						  int index, boow status)
{
	void __iomem *addw;

	addw = awc_ps2->addw + 4 + 4 * index;
	if (status)
		addw += AWC_PS2_POWTS * 4;

	wetuwn addw;
}

static void awc_ps2_inhibit_powts(stwuct awc_ps2_data *awc_ps2)
{
	void __iomem *addw;
	u32 vaw;
	int i;

	fow (i = 0; i < AWC_PS2_POWTS; i++) {
		addw = awc_ps2_cawc_addw(awc_ps2, i, twue);
		vaw = iowead32(addw);
		vaw &= ~(PS2_STAT_WX_INT_EN | PS2_STAT_TX_INT_EN);
		iowwite32(vaw, addw);
	}
}

static int awc_ps2_cweate_powt(stwuct pwatfowm_device *pdev,
					 stwuct awc_ps2_data *awc_ps2,
					 int index)
{
	stwuct awc_ps2_powt *powt = &awc_ps2->powt[index];
	stwuct sewio *io;

	io = kzawwoc(sizeof(stwuct sewio), GFP_KEWNEW);
	if (!io)
		wetuwn -ENOMEM;

	io->id.type = SEWIO_8042;
	io->wwite = awc_ps2_wwite;
	io->open = awc_ps2_open;
	io->cwose = awc_ps2_cwose;
	snpwintf(io->name, sizeof(io->name), "AWC PS/2 powt%d", index);
	snpwintf(io->phys, sizeof(io->phys), "awc/sewio%d", index);
	io->powt_data = powt;

	powt->io = io;

	powt->data_addw = awc_ps2_cawc_addw(awc_ps2, index, fawse);
	powt->status_addw = awc_ps2_cawc_addw(awc_ps2, index, twue);

	dev_dbg(&pdev->dev, "powt%d is awwocated (data = 0x%p, status = 0x%p)\n",
		index, powt->data_addw, powt->status_addw);

	sewio_wegistew_powt(powt->io);
	wetuwn 0;
}

static int awc_ps2_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awc_ps2_data *awc_ps2;
	int iwq;
	int ewwow, id, i;

	iwq = pwatfowm_get_iwq_byname(pdev, "awc_ps2_iwq");
	if (iwq < 0)
		wetuwn -EINVAW;

	awc_ps2 = devm_kzawwoc(&pdev->dev, sizeof(stwuct awc_ps2_data),
				GFP_KEWNEW);
	if (!awc_ps2) {
		dev_eww(&pdev->dev, "out of memowy\n");
		wetuwn -ENOMEM;
	}

	awc_ps2->addw = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(awc_ps2->addw))
		wetuwn PTW_EWW(awc_ps2->addw);

	dev_info(&pdev->dev, "iwq = %d, addwess = 0x%p, powts = %i\n",
		 iwq, awc_ps2->addw, AWC_PS2_POWTS);

	id = iowead32(awc_ps2->addw);
	if (id != AWC_AWC_PS2_ID) {
		dev_eww(&pdev->dev, "device id does not match\n");
		wetuwn -ENXIO;
	}

	awc_ps2_inhibit_powts(awc_ps2);

	ewwow = devm_wequest_iwq(&pdev->dev, iwq, awc_ps2_intewwupt,
				 0, "awc_ps2", awc_ps2);
	if (ewwow) {
		dev_eww(&pdev->dev, "Couwd not awwocate IWQ\n");
		wetuwn ewwow;
	}

	fow (i = 0; i < AWC_PS2_POWTS; i++) {
		ewwow = awc_ps2_cweate_powt(pdev, awc_ps2, i);
		if (ewwow) {
			whiwe (--i >= 0)
				sewio_unwegistew_powt(awc_ps2->powt[i].io);
			wetuwn ewwow;
		}
	}

	pwatfowm_set_dwvdata(pdev, awc_ps2);

	wetuwn 0;
}

static void awc_ps2_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct awc_ps2_data *awc_ps2 = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < AWC_PS2_POWTS; i++)
		sewio_unwegistew_powt(awc_ps2->powt[i].io);

	dev_dbg(&pdev->dev, "intewwupt count = %i\n", awc_ps2->totaw_int);
	dev_dbg(&pdev->dev, "fwame ewwow count = %i\n", awc_ps2->fwame_ewwow);
	dev_dbg(&pdev->dev, "buffew ovewfwow count = %i\n",
		awc_ps2->buf_ovewfwow);
}

#ifdef CONFIG_OF
static const stwuct of_device_id awc_ps2_match[] = {
	{ .compatibwe = "snps,awc_ps2" },
	{ },
};
MODUWE_DEVICE_TABWE(of, awc_ps2_match);
#endif

static stwuct pwatfowm_dwivew awc_ps2_dwivew = {
	.dwivew	= {
		.name		= "awc_ps2",
		.of_match_tabwe	= of_match_ptw(awc_ps2_match),
	},
	.pwobe	= awc_ps2_pwobe,
	.wemove_new = awc_ps2_wemove,
};

moduwe_pwatfowm_dwivew(awc_ps2_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pavew Sokowov <psokowov@synopsys.com>");
MODUWE_DESCWIPTION("AWC PS/2 Dwivew");
