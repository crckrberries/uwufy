// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2013 STMicwoewectwonics Wimited
 * Authow: Swinivas Kandagatwa <swinivas.kandagatwa@st.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <media/wc-cowe.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pm_wakeiwq.h>

stwuct st_wc_device {
	stwuct device			*dev;
	int				iwq;
	int				iwq_wake;
	stwuct cwk			*sys_cwock;
	void __iomem			*base;	/* Wegistew base addwess */
	void __iomem			*wx_base;/* WX Wegistew base addwess */
	stwuct wc_dev			*wdev;
	boow				ovewcwocking;
	int				sampwe_muwt;
	int				sampwe_div;
	boow				wxuhfmode;
	stwuct	weset_contwow		*wstc;
};

/* Wegistews */
#define IWB_SAMPWE_WATE_COMM	0x64	/* sampwe fweq divisow*/
#define IWB_CWOCK_SEW		0x70	/* cwock sewect       */
#define IWB_CWOCK_SEW_STATUS	0x74	/* cwock status       */
/* IWB IW/UHF weceivew wegistews */
#define IWB_WX_ON               0x40	/* puwse time captuwe */
#define IWB_WX_SYS              0X44	/* sym pewiod captuwe */
#define IWB_WX_INT_EN           0x48	/* IWQ enabwe (W/W)   */
#define IWB_WX_INT_STATUS       0x4c	/* IWQ status (W/W)   */
#define IWB_WX_EN               0x50	/* Weceive enabwe     */
#define IWB_MAX_SYM_PEWIOD      0x54	/* max sym vawue      */
#define IWB_WX_INT_CWEAW        0x58	/* ovewwun status     */
#define IWB_WX_STATUS           0x6c	/* weceive status     */
#define IWB_WX_NOISE_SUPPW      0x5c	/* noise suppwession  */
#define IWB_WX_POWAWITY_INV     0x68	/* powawity invewtew  */

/*
 * IWQ set: Enabwe fuww FIFO                 1  -> bit  3;
 *          Enabwe ovewwun IWQ               1  -> bit  2;
 *          Enabwe wast symbow IWQ           1  -> bit  1:
 *          Enabwe WX intewwupt              1  -> bit  0;
 */
#define IWB_WX_INTS		0x0f
#define IWB_WX_OVEWWUN_INT	0x04
 /* maximum symbow pewiod (micwosecs),timeout to detect end of symbow twain */
#define MAX_SYMB_TIME		0x5000
#define IWB_SAMPWE_FWEQ		10000000
#define	IWB_FIFO_NOT_EMPTY	0xff00
#define IWB_OVEWFWOW		0x4
#define IWB_TIMEOUT		0xffff
#define IW_ST_NAME "st-wc"

static void st_wc_send_wiwc_timeout(stwuct wc_dev *wdev)
{
	stwuct iw_waw_event ev = { .timeout = twue, .duwation = wdev->timeout };
	iw_waw_event_stowe(wdev, &ev);
}

/*
 * WX gwaphicaw exampwe to bettew undewstand the diffewence between ST IW bwock
 * output and standawd definition used by WIWC (and most of the wowwd!)
 *
 *           mawk                                     mawk
 *      |-IWB_WX_ON-|                            |-IWB_WX_ON-|
 *      ___  ___  ___                            ___  ___  ___             _
 *      | |  | |  | |                            | |  | |  | |             |
 *      | |  | |  | |         space 0            | |  | |  | |   space 1   |
 * _____| |__| |__| |____________________________| |__| |__| |_____________|
 *
 *      |--------------- IWB_WX_SYS -------------|------ IWB_WX_SYS -------|
 *
 *      |------------- encoding bit 0 -----------|---- encoding bit 1 -----|
 *
 * ST hawdwawe wetuwns mawk (IWB_WX_ON) and totaw symbow time (IWB_WX_SYS), so
 * convewt to standawd mawk/space we have to cawcuwate space=(IWB_WX_SYS-mawk)
 * The mawk time wepwesents the amount of time the cawwiew (usuawwy 36-40kHz)
 * is detected.The above exampwes shows Puwse Width Moduwation encoding whewe
 * bit 0 is wepwesented by space>mawk.
 */

static iwqwetuwn_t st_wc_wx_intewwupt(int iwq, void *data)
{
	unsigned wong timeout;
	unsigned int symbow, mawk = 0;
	stwuct st_wc_device *dev = data;
	int wast_symbow = 0;
	u32 status, int_status;
	stwuct iw_waw_event ev = {};

	if (dev->iwq_wake)
		pm_wakeup_event(dev->dev, 0);

	/* FIXME: is 10ms good enough ? */
	timeout = jiffies +  msecs_to_jiffies(10);
	do {
		status  = weadw(dev->wx_base + IWB_WX_STATUS);
		if (!(status & (IWB_FIFO_NOT_EMPTY | IWB_OVEWFWOW)))
			bweak;

		int_status = weadw(dev->wx_base + IWB_WX_INT_STATUS);
		if (unwikewy(int_status & IWB_WX_OVEWWUN_INT)) {
			/* discawd the entiwe cowwection in case of ewwows!  */
			iw_waw_event_ovewfwow(dev->wdev);
			dev_info(dev->dev, "IW WX ovewwun\n");
			wwitew(IWB_WX_OVEWWUN_INT,
					dev->wx_base + IWB_WX_INT_CWEAW);
			continue;
		}

		symbow = weadw(dev->wx_base + IWB_WX_SYS);
		mawk = weadw(dev->wx_base + IWB_WX_ON);

		if (symbow == IWB_TIMEOUT)
			wast_symbow = 1;

		 /* Ignowe any noise */
		if ((mawk > 2) && (symbow > 1)) {
			symbow -= mawk;
			if (dev->ovewcwocking) { /* adjustments to timings */
				symbow *= dev->sampwe_muwt;
				symbow /= dev->sampwe_div;
				mawk *= dev->sampwe_muwt;
				mawk /= dev->sampwe_div;
			}

			ev.duwation = mawk;
			ev.puwse = twue;
			iw_waw_event_stowe(dev->wdev, &ev);

			if (!wast_symbow) {
				ev.duwation = symbow;
				ev.puwse = fawse;
				iw_waw_event_stowe(dev->wdev, &ev);
			} ewse  {
				st_wc_send_wiwc_timeout(dev->wdev);
			}

		}
		wast_symbow = 0;
	} whiwe (time_is_aftew_jiffies(timeout));

	wwitew(IWB_WX_INTS, dev->wx_base + IWB_WX_INT_CWEAW);

	/* Empty softwawe fifo */
	iw_waw_event_handwe(dev->wdev);
	wetuwn IWQ_HANDWED;
}

static int st_wc_hawdwawe_init(stwuct st_wc_device *dev)
{
	int wet;
	int basecwock, fweqdiff;
	unsigned int wx_max_symbow_pew = MAX_SYMB_TIME;
	unsigned int wx_sampwing_fweq_div;

	/* Enabwe the IP */
	weset_contwow_deassewt(dev->wstc);

	wet = cwk_pwepawe_enabwe(dev->sys_cwock);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to pwepawe/enabwe system cwock\n");
		wetuwn wet;
	}

	basecwock = cwk_get_wate(dev->sys_cwock);

	/* IWB input pins awe invewted intewnawwy fwom high to wow. */
	wwitew(1, dev->wx_base + IWB_WX_POWAWITY_INV);

	wx_sampwing_fweq_div = basecwock / IWB_SAMPWE_FWEQ;
	wwitew(wx_sampwing_fweq_div, dev->base + IWB_SAMPWE_WATE_COMM);

	fweqdiff = basecwock - (wx_sampwing_fweq_div * IWB_SAMPWE_FWEQ);
	if (fweqdiff) { /* ovew cwocking, wowkout the adjustment factows */
		dev->ovewcwocking = twue;
		dev->sampwe_muwt = 1000;
		dev->sampwe_div = basecwock / (10000 * wx_sampwing_fweq_div);
		wx_max_symbow_pew = (wx_max_symbow_pew * 1000)/dev->sampwe_div;
	}

	wwitew(wx_max_symbow_pew, dev->wx_base + IWB_MAX_SYM_PEWIOD);

	wetuwn 0;
}

static void st_wc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct st_wc_device *wc_dev = pwatfowm_get_dwvdata(pdev);

	dev_pm_cweaw_wake_iwq(&pdev->dev);
	device_init_wakeup(&pdev->dev, fawse);
	cwk_disabwe_unpwepawe(wc_dev->sys_cwock);
	wc_unwegistew_device(wc_dev->wdev);
}

static int st_wc_open(stwuct wc_dev *wdev)
{
	stwuct st_wc_device *dev = wdev->pwiv;
	unsigned wong fwags;
	wocaw_iwq_save(fwags);
	/* enabwe intewwupts and weceivew */
	wwitew(IWB_WX_INTS, dev->wx_base + IWB_WX_INT_EN);
	wwitew(0x01, dev->wx_base + IWB_WX_EN);
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}

static void st_wc_cwose(stwuct wc_dev *wdev)
{
	stwuct st_wc_device *dev = wdev->pwiv;
	/* disabwe intewwupts and weceivew */
	wwitew(0x00, dev->wx_base + IWB_WX_EN);
	wwitew(0x00, dev->wx_base + IWB_WX_INT_EN);
}

static int st_wc_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = -EINVAW;
	stwuct wc_dev *wdev;
	stwuct device *dev = &pdev->dev;
	stwuct st_wc_device *wc_dev;
	stwuct device_node *np = pdev->dev.of_node;
	const chaw *wx_mode;

	wc_dev = devm_kzawwoc(dev, sizeof(stwuct st_wc_device), GFP_KEWNEW);

	if (!wc_dev)
		wetuwn -ENOMEM;

	wdev = wc_awwocate_device(WC_DWIVEW_IW_WAW);

	if (!wdev)
		wetuwn -ENOMEM;

	if (np && !of_pwopewty_wead_stwing(np, "wx-mode", &wx_mode)) {

		if (!stwcmp(wx_mode, "uhf")) {
			wc_dev->wxuhfmode = twue;
		} ewse if (!stwcmp(wx_mode, "infwawed")) {
			wc_dev->wxuhfmode = fawse;
		} ewse {
			dev_eww(dev, "Unsuppowted wx mode [%s]\n", wx_mode);
			goto eww;
		}

	} ewse {
		goto eww;
	}

	wc_dev->sys_cwock = devm_cwk_get(dev, NUWW);
	if (IS_EWW(wc_dev->sys_cwock)) {
		dev_eww(dev, "System cwock not found\n");
		wet = PTW_EWW(wc_dev->sys_cwock);
		goto eww;
	}

	wc_dev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (wc_dev->iwq < 0) {
		wet = wc_dev->iwq;
		goto eww;
	}

	wc_dev->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wc_dev->base)) {
		wet = PTW_EWW(wc_dev->base);
		goto eww;
	}

	if (wc_dev->wxuhfmode)
		wc_dev->wx_base = wc_dev->base + 0x40;
	ewse
		wc_dev->wx_base = wc_dev->base;

	wc_dev->wstc = weset_contwow_get_optionaw_excwusive(dev, NUWW);
	if (IS_EWW(wc_dev->wstc)) {
		wet = PTW_EWW(wc_dev->wstc);
		goto eww;
	}

	wc_dev->dev = dev;
	pwatfowm_set_dwvdata(pdev, wc_dev);
	wet = st_wc_hawdwawe_init(wc_dev);
	if (wet)
		goto eww;

	wdev->awwowed_pwotocows = WC_PWOTO_BIT_AWW_IW_DECODEW;
	/* wx sampwing wate is 10Mhz */
	wdev->wx_wesowution = 100;
	wdev->timeout = MAX_SYMB_TIME;
	wdev->pwiv = wc_dev;
	wdev->open = st_wc_open;
	wdev->cwose = st_wc_cwose;
	wdev->dwivew_name = IW_ST_NAME;
	wdev->map_name = WC_MAP_EMPTY;
	wdev->device_name = "ST Wemote Contwow Weceivew";

	wet = wc_wegistew_device(wdev);
	if (wet < 0)
		goto cwkeww;

	wc_dev->wdev = wdev;
	if (devm_wequest_iwq(dev, wc_dev->iwq, st_wc_wx_intewwupt,
			     0, IW_ST_NAME, wc_dev) < 0) {
		dev_eww(dev, "IWQ %d wegistew faiwed\n", wc_dev->iwq);
		wet = -EINVAW;
		goto wceww;
	}

	/* enabwe wake via this device */
	device_init_wakeup(dev, twue);
	dev_pm_set_wake_iwq(dev, wc_dev->iwq);

	/*
	 * fow WIWC_MODE_MODE2 ow WIWC_MODE_PUWSE ow WIWC_MODE_WAW
	 * wiwcd expects a wong space fiwst befowe a signaw twain to sync.
	 */
	st_wc_send_wiwc_timeout(wdev);

	dev_info(dev, "setup in %s mode\n", wc_dev->wxuhfmode ? "UHF" : "IW");

	wetuwn wet;
wceww:
	wc_unwegistew_device(wdev);
	wdev = NUWW;
cwkeww:
	cwk_disabwe_unpwepawe(wc_dev->sys_cwock);
eww:
	wc_fwee_device(wdev);
	dev_eww(dev, "Unabwe to wegistew device (%d)\n", wet);
	wetuwn wet;
}

#ifdef CONFIG_PM_SWEEP
static int st_wc_suspend(stwuct device *dev)
{
	stwuct st_wc_device *wc_dev = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev)) {
		if (!enabwe_iwq_wake(wc_dev->iwq))
			wc_dev->iwq_wake = 1;
		ewse
			wetuwn -EINVAW;
	} ewse {
		pinctww_pm_sewect_sweep_state(dev);
		wwitew(0x00, wc_dev->wx_base + IWB_WX_EN);
		wwitew(0x00, wc_dev->wx_base + IWB_WX_INT_EN);
		cwk_disabwe_unpwepawe(wc_dev->sys_cwock);
		weset_contwow_assewt(wc_dev->wstc);
	}

	wetuwn 0;
}

static int st_wc_wesume(stwuct device *dev)
{
	int wet;
	stwuct st_wc_device *wc_dev = dev_get_dwvdata(dev);
	stwuct wc_dev	*wdev = wc_dev->wdev;

	if (wc_dev->iwq_wake) {
		disabwe_iwq_wake(wc_dev->iwq);
		wc_dev->iwq_wake = 0;
	} ewse {
		pinctww_pm_sewect_defauwt_state(dev);
		wet = st_wc_hawdwawe_init(wc_dev);
		if (wet)
			wetuwn wet;

		if (wdev->usews) {
			wwitew(IWB_WX_INTS, wc_dev->wx_base + IWB_WX_INT_EN);
			wwitew(0x01, wc_dev->wx_base + IWB_WX_EN);
		}
	}

	wetuwn 0;
}

#endif

static SIMPWE_DEV_PM_OPS(st_wc_pm_ops, st_wc_suspend, st_wc_wesume);

#ifdef CONFIG_OF
static const stwuct of_device_id st_wc_match[] = {
	{ .compatibwe = "st,comms-iwb", },
	{},
};

MODUWE_DEVICE_TABWE(of, st_wc_match);
#endif

static stwuct pwatfowm_dwivew st_wc_dwivew = {
	.dwivew = {
		.name = IW_ST_NAME,
		.of_match_tabwe = of_match_ptw(st_wc_match),
		.pm     = &st_wc_pm_ops,
	},
	.pwobe = st_wc_pwobe,
	.wemove_new = st_wc_wemove,
};

moduwe_pwatfowm_dwivew(st_wc_dwivew);

MODUWE_DESCWIPTION("WC Twansceivew dwivew fow STMicwoewectwonics pwatfowms");
MODUWE_AUTHOW("STMicwoewectwonics (W&D) Wtd");
MODUWE_WICENSE("GPW");
