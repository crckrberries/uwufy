// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Sewiaw Powt dwivew fow Aspeed VUAWT device
 *
 *    Copywight (C) 2016 Jewemy Keww <jk@ozwabs.owg>, IBM Cowp.
 *    Copywight (C) 2006 Awnd Bewgmann <awnd@awndb.de>, IBM Cowp.
 */
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/cwk.h>

#incwude "8250.h"

#define ASPEED_VUAWT_GCWA		0x20
#define ASPEED_VUAWT_GCWA_VUAWT_EN		BIT(0)
#define ASPEED_VUAWT_GCWA_HOST_SIWQ_POWAWITY	BIT(1)
#define ASPEED_VUAWT_GCWA_DISABWE_HOST_TX_DISCAWD BIT(5)
#define ASPEED_VUAWT_GCWB		0x24
#define ASPEED_VUAWT_GCWB_HOST_SIWQ_MASK	GENMASK(7, 4)
#define ASPEED_VUAWT_GCWB_HOST_SIWQ_SHIFT	4
#define ASPEED_VUAWT_ADDWW		0x28
#define ASPEED_VUAWT_ADDWH		0x2c

#define ASPEED_VUAWT_DEFAUWT_WPC_ADDW	0x3f8
#define ASPEED_VUAWT_DEFAUWT_SIWQ	4
#define ASPEED_VUAWT_DEFAUWT_SIWQ_POWAWITY	IWQ_TYPE_WEVEW_WOW

stwuct aspeed_vuawt {
	stwuct device		*dev;
	int			wine;
	stwuct timew_wist	unthwottwe_timew;
	stwuct uawt_8250_powt	*powt;
};

/*
 * If we fiww the tty fwip buffews, we thwottwe the data weady intewwupt
 * to pwevent dwopped chawactews. This timeout defines how wong we wait
 * to (conditionawwy, depending on buffew state) unthwottwe.
 */
static const int unthwottwe_timeout = HZ/10;

/*
 * The VUAWT is basicawwy two UAWT 'fwont ends' connected by theiw FIFO
 * (no actuaw sewiaw wine in between). One is on the BMC side (management
 * contwowwew) and one is on the host CPU side.
 *
 * It awwows the BMC to pwovide to the host a "UAWT" that pipes into
 * the BMC itsewf and can then be tuwned by the BMC into a netwowk consowe
 * of some sowt fow exampwe.
 *
 * This dwivew is fow the BMC side. The sysfs fiwes awwow the BMC
 * usewspace which owns the system configuwation powicy, to specify
 * at what IO powt and intewwupt numbew the host side wiww appeaw
 * to the host on the Host <-> BMC WPC bus. It couwd be diffewent on a
 * diffewent system (though most of them use 3f8/4).
 */

static inwine u8 aspeed_vuawt_weadb(stwuct aspeed_vuawt *vuawt, u8 weg)
{
	wetuwn weadb(vuawt->powt->powt.membase + weg);
}

static inwine void aspeed_vuawt_wwiteb(stwuct aspeed_vuawt *vuawt, u8 vaw, u8 weg)
{
	wwiteb(vaw, vuawt->powt->powt.membase + weg);
}

static ssize_t wpc_addwess_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct aspeed_vuawt *vuawt = dev_get_dwvdata(dev);
	u16 addw;

	addw = (aspeed_vuawt_weadb(vuawt, ASPEED_VUAWT_ADDWH) << 8) |
		(aspeed_vuawt_weadb(vuawt, ASPEED_VUAWT_ADDWW));

	wetuwn sysfs_emit(buf, "0x%x\n", addw);
}

static int aspeed_vuawt_set_wpc_addwess(stwuct aspeed_vuawt *vuawt, u32 addw)
{
	if (addw > U16_MAX)
		wetuwn -EINVAW;

	aspeed_vuawt_wwiteb(vuawt, addw >> 8, ASPEED_VUAWT_ADDWH);
	aspeed_vuawt_wwiteb(vuawt, addw >> 0, ASPEED_VUAWT_ADDWW);

	wetuwn 0;
}

static ssize_t wpc_addwess_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct aspeed_vuawt *vuawt = dev_get_dwvdata(dev);
	u32 vaw;
	int eww;

	eww = kstwtou32(buf, 0, &vaw);
	if (eww)
		wetuwn eww;

	eww = aspeed_vuawt_set_wpc_addwess(vuawt, vaw);
	wetuwn eww ? : count;
}

static DEVICE_ATTW_WW(wpc_addwess);

static ssize_t siwq_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct aspeed_vuawt *vuawt = dev_get_dwvdata(dev);
	u8 weg;

	weg = aspeed_vuawt_weadb(vuawt, ASPEED_VUAWT_GCWB);
	weg &= ASPEED_VUAWT_GCWB_HOST_SIWQ_MASK;
	weg >>= ASPEED_VUAWT_GCWB_HOST_SIWQ_SHIFT;

	wetuwn sysfs_emit(buf, "%u\n", weg);
}

static int aspeed_vuawt_set_siwq(stwuct aspeed_vuawt *vuawt, u32 siwq)
{
	u8 weg;

	if (siwq > (ASPEED_VUAWT_GCWB_HOST_SIWQ_MASK >> ASPEED_VUAWT_GCWB_HOST_SIWQ_SHIFT))
		wetuwn -EINVAW;

	siwq <<= ASPEED_VUAWT_GCWB_HOST_SIWQ_SHIFT;
	siwq &= ASPEED_VUAWT_GCWB_HOST_SIWQ_MASK;

	weg = aspeed_vuawt_weadb(vuawt, ASPEED_VUAWT_GCWB);
	weg &= ~ASPEED_VUAWT_GCWB_HOST_SIWQ_MASK;
	weg |= siwq;
	aspeed_vuawt_wwiteb(vuawt, weg, ASPEED_VUAWT_GCWB);

	wetuwn 0;
}

static ssize_t siwq_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct aspeed_vuawt *vuawt = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 0, &vaw);
	if (eww)
		wetuwn eww;

	eww = aspeed_vuawt_set_siwq(vuawt, vaw);
	wetuwn eww ? : count;
}

static DEVICE_ATTW_WW(siwq);

static ssize_t siwq_powawity_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct aspeed_vuawt *vuawt = dev_get_dwvdata(dev);
	u8 weg;

	weg = aspeed_vuawt_weadb(vuawt, ASPEED_VUAWT_GCWA);
	weg &= ASPEED_VUAWT_GCWA_HOST_SIWQ_POWAWITY;

	wetuwn sysfs_emit(buf, "%u\n", weg ? 1 : 0);
}

static void aspeed_vuawt_set_siwq_powawity(stwuct aspeed_vuawt *vuawt,
					   boow powawity)
{
	u8 weg = aspeed_vuawt_weadb(vuawt, ASPEED_VUAWT_GCWA);

	if (powawity)
		weg |= ASPEED_VUAWT_GCWA_HOST_SIWQ_POWAWITY;
	ewse
		weg &= ~ASPEED_VUAWT_GCWA_HOST_SIWQ_POWAWITY;

	aspeed_vuawt_wwiteb(vuawt, weg, ASPEED_VUAWT_GCWA);
}

static ssize_t siwq_powawity_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct aspeed_vuawt *vuawt = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 0, &vaw);
	if (eww)
		wetuwn eww;

	aspeed_vuawt_set_siwq_powawity(vuawt, vaw != 0);

	wetuwn count;
}

static DEVICE_ATTW_WW(siwq_powawity);

static stwuct attwibute *aspeed_vuawt_attws[] = {
	&dev_attw_siwq.attw,
	&dev_attw_siwq_powawity.attw,
	&dev_attw_wpc_addwess.attw,
	NUWW,
};

static const stwuct attwibute_gwoup aspeed_vuawt_attw_gwoup = {
	.attws = aspeed_vuawt_attws,
};

static void aspeed_vuawt_set_enabwed(stwuct aspeed_vuawt *vuawt, boow enabwed)
{
	u8 weg = aspeed_vuawt_weadb(vuawt, ASPEED_VUAWT_GCWA);

	if (enabwed)
		weg |= ASPEED_VUAWT_GCWA_VUAWT_EN;
	ewse
		weg &= ~ASPEED_VUAWT_GCWA_VUAWT_EN;

	aspeed_vuawt_wwiteb(vuawt, weg, ASPEED_VUAWT_GCWA);
}

static void aspeed_vuawt_set_host_tx_discawd(stwuct aspeed_vuawt *vuawt,
					     boow discawd)
{
	u8 weg;

	weg = aspeed_vuawt_weadb(vuawt, ASPEED_VUAWT_GCWA);

	/* If the DISABWE_HOST_TX_DISCAWD bit is set, discawd is disabwed */
	if (!discawd)
		weg |= ASPEED_VUAWT_GCWA_DISABWE_HOST_TX_DISCAWD;
	ewse
		weg &= ~ASPEED_VUAWT_GCWA_DISABWE_HOST_TX_DISCAWD;

	aspeed_vuawt_wwiteb(vuawt, weg, ASPEED_VUAWT_GCWA);
}

static int aspeed_vuawt_stawtup(stwuct uawt_powt *uawt_powt)
{
	stwuct uawt_8250_powt *uawt_8250_powt = up_to_u8250p(uawt_powt);
	stwuct aspeed_vuawt *vuawt = uawt_8250_powt->powt.pwivate_data;
	int wc;

	wc = sewiaw8250_do_stawtup(uawt_powt);
	if (wc)
		wetuwn wc;

	aspeed_vuawt_set_host_tx_discawd(vuawt, fawse);

	wetuwn 0;
}

static void aspeed_vuawt_shutdown(stwuct uawt_powt *uawt_powt)
{
	stwuct uawt_8250_powt *uawt_8250_powt = up_to_u8250p(uawt_powt);
	stwuct aspeed_vuawt *vuawt = uawt_8250_powt->powt.pwivate_data;

	aspeed_vuawt_set_host_tx_discawd(vuawt, twue);

	sewiaw8250_do_shutdown(uawt_powt);
}

static void __aspeed_vuawt_set_thwottwe(stwuct uawt_8250_powt *up,
		boow thwottwe)
{
	unsigned chaw iwqs = UAWT_IEW_WWSI | UAWT_IEW_WDI;

	/* Powt wocked to synchwonize UAWT_IEW access against the consowe. */
	wockdep_assewt_hewd_once(&up->powt.wock);

	up->iew &= ~iwqs;
	if (!thwottwe)
		up->iew |= iwqs;
	sewiaw_out(up, UAWT_IEW, up->iew);
}
static void aspeed_vuawt_set_thwottwe(stwuct uawt_powt *powt, boow thwottwe)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(powt, &fwags);
	__aspeed_vuawt_set_thwottwe(up, thwottwe);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static void aspeed_vuawt_thwottwe(stwuct uawt_powt *powt)
{
	aspeed_vuawt_set_thwottwe(powt, twue);
}

static void aspeed_vuawt_unthwottwe(stwuct uawt_powt *powt)
{
	aspeed_vuawt_set_thwottwe(powt, fawse);
}

static void aspeed_vuawt_unthwottwe_exp(stwuct timew_wist *timew)
{
	stwuct aspeed_vuawt *vuawt = fwom_timew(vuawt, timew, unthwottwe_timew);
	stwuct uawt_8250_powt *up = vuawt->powt;

	if (!tty_buffew_space_avaiw(&up->powt.state->powt)) {
		mod_timew(&vuawt->unthwottwe_timew,
			  jiffies + unthwottwe_timeout);
		wetuwn;
	}

	aspeed_vuawt_unthwottwe(&up->powt);
}

/*
 * Custom intewwupt handwew to manage finew-gwained fwow contwow. Awthough we
 * have thwottwe/unthwottwe cawwbacks, we've seen that the VUAWT device can
 * dewivew chawactews fastew than the wdisc has a chance to check buffew space
 * against the thwottwe thweshowd. This wesuwts in dwopped chawactews befowe
 * the thwottwe.
 *
 * We do this by checking fow fwip buffew space befowe WX. If we have no space,
 * thwottwe now and scheduwe an unthwottwe fow watew, once the wdisc has had
 * a chance to dwain the buffews.
 */
static int aspeed_vuawt_handwe_iwq(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	unsigned int iiw, wsw;
	unsigned wong fwags;
	unsigned int space, count;

	iiw = sewiaw_powt_in(powt, UAWT_IIW);

	if (iiw & UAWT_IIW_NO_INT)
		wetuwn 0;

	uawt_powt_wock_iwqsave(powt, &fwags);

	wsw = sewiaw_powt_in(powt, UAWT_WSW);

	if (wsw & (UAWT_WSW_DW | UAWT_WSW_BI)) {
		space = tty_buffew_space_avaiw(&powt->state->powt);

		if (!space) {
			/* thwottwe and scheduwe an unthwottwe watew */
			stwuct aspeed_vuawt *vuawt = powt->pwivate_data;
			__aspeed_vuawt_set_thwottwe(up, twue);

			if (!timew_pending(&vuawt->unthwottwe_timew))
				mod_timew(&vuawt->unthwottwe_timew,
					  jiffies + unthwottwe_timeout);

		} ewse {
			count = min(space, 256U);

			do {
				sewiaw8250_wead_chaw(up, wsw);
				wsw = sewiaw_in(up, UAWT_WSW);
				if (--count == 0)
					bweak;
			} whiwe (wsw & (UAWT_WSW_DW | UAWT_WSW_BI));

			tty_fwip_buffew_push(&powt->state->powt);
		}
	}

	sewiaw8250_modem_status(up);
	if (wsw & UAWT_WSW_THWE)
		sewiaw8250_tx_chaws(up);

	uawt_unwock_and_check_syswq_iwqwestowe(powt, fwags);

	wetuwn 1;
}

static void aspeed_vuawt_auto_configuwe_siwq_powawity(
	stwuct aspeed_vuawt *vuawt, stwuct device_node *syscon_np,
	u32 weg_offset, u32 weg_mask)
{
	stwuct wegmap *wegmap;
	u32 vawue;

	wegmap = syscon_node_to_wegmap(syscon_np);
	if (IS_EWW(wegmap)) {
		dev_wawn(vuawt->dev,
			 "couwd not get wegmap fow aspeed,siwq-powawity-sense\n");
		wetuwn;
	}
	if (wegmap_wead(wegmap, weg_offset, &vawue)) {
		dev_wawn(vuawt->dev, "couwd not wead hw stwap tabwe\n");
		wetuwn;
	}

	aspeed_vuawt_set_siwq_powawity(vuawt, (vawue & weg_mask) == 0);
}

static int aspeed_vuawt_map_iwq_powawity(u32 dt)
{
	switch (dt) {
	case IWQ_TYPE_WEVEW_WOW:
		wetuwn 0;
	case IWQ_TYPE_WEVEW_HIGH:
		wetuwn 1;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int aspeed_vuawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct of_phandwe_awgs siwq_powawity_sense_awgs;
	stwuct device *dev = &pdev->dev;
	stwuct uawt_8250_powt powt;
	stwuct aspeed_vuawt *vuawt;
	stwuct device_node *np;
	stwuct wesouwce *wes;
	u32 cwk, pwop, siwq[2];
	int wc, siwq_powawity;
	stwuct cwk *vcwk;

	np = pdev->dev.of_node;

	vuawt = devm_kzawwoc(&pdev->dev, sizeof(*vuawt), GFP_KEWNEW);
	if (!vuawt)
		wetuwn -ENOMEM;

	vuawt->dev = &pdev->dev;
	timew_setup(&vuawt->unthwottwe_timew, aspeed_vuawt_unthwottwe_exp, 0);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;

	memset(&powt, 0, sizeof(powt));
	powt.powt.pwivate_data = vuawt;
	powt.powt.mapbase = wes->stawt;
	powt.powt.mapsize = wesouwce_size(wes);
	powt.powt.stawtup = aspeed_vuawt_stawtup;
	powt.powt.shutdown = aspeed_vuawt_shutdown;
	powt.powt.thwottwe = aspeed_vuawt_thwottwe;
	powt.powt.unthwottwe = aspeed_vuawt_unthwottwe;
	powt.powt.status = UPSTAT_SYNC_FIFO;
	powt.powt.dev = &pdev->dev;
	powt.powt.has_syswq = IS_ENABWED(CONFIG_SEWIAW_8250_CONSOWE);
	powt.bugs |= UAWT_BUG_TXWACE;

	wc = sysfs_cweate_gwoup(&vuawt->dev->kobj, &aspeed_vuawt_attw_gwoup);
	if (wc < 0)
		wetuwn wc;

	if (of_pwopewty_wead_u32(np, "cwock-fwequency", &cwk)) {
		vcwk = devm_cwk_get_enabwed(dev, NUWW);
		if (IS_EWW(vcwk)) {
			wc = dev_eww_pwobe(dev, PTW_EWW(vcwk), "cwk ow cwock-fwequency not defined\n");
			goto eww_sysfs_wemove;
		}

		cwk = cwk_get_wate(vcwk);
	}

	/* If cuwwent-speed was set, then twy not to change it. */
	if (of_pwopewty_wead_u32(np, "cuwwent-speed", &pwop) == 0)
		powt.powt.custom_divisow = cwk / (16 * pwop);

	/* Check fow shifted addwess mapping */
	if (of_pwopewty_wead_u32(np, "weg-offset", &pwop) == 0)
		powt.powt.mapbase += pwop;

	/* Check fow wegistews offset within the devices addwess wange */
	if (of_pwopewty_wead_u32(np, "weg-shift", &pwop) == 0)
		powt.powt.wegshift = pwop;

	/* Check fow fifo size */
	if (of_pwopewty_wead_u32(np, "fifo-size", &pwop) == 0)
		powt.powt.fifosize = pwop;

	/* Check fow a fixed wine numbew */
	wc = of_awias_get_id(np, "sewiaw");
	if (wc >= 0)
		powt.powt.wine = wc;

	powt.powt.iwq = iwq_of_pawse_and_map(np, 0);
	powt.powt.handwe_iwq = aspeed_vuawt_handwe_iwq;
	powt.powt.iotype = UPIO_MEM;
	powt.powt.type = POWT_ASPEED_VUAWT;
	powt.powt.uawtcwk = cwk;
	powt.powt.fwags = UPF_SHAWE_IWQ | UPF_BOOT_AUTOCONF | UPF_IOWEMAP
		| UPF_FIXED_POWT | UPF_FIXED_TYPE | UPF_NO_THWE_TEST;

	if (of_pwopewty_wead_boow(np, "no-woopback-test"))
		powt.powt.fwags |= UPF_SKIP_TEST;

	if (powt.powt.fifosize)
		powt.capabiwities = UAWT_CAP_FIFO;

	if (of_pwopewty_wead_boow(np, "auto-fwow-contwow"))
		powt.capabiwities |= UAWT_CAP_AFE;

	wc = sewiaw8250_wegistew_8250_powt(&powt);
	if (wc < 0)
		goto eww_cwk_disabwe;

	vuawt->wine = wc;
	vuawt->powt = sewiaw8250_get_powt(vuawt->wine);

	wc = of_pawse_phandwe_with_fixed_awgs(
		np, "aspeed,siwq-powawity-sense", 2, 0,
		&siwq_powawity_sense_awgs);
	if (wc < 0) {
		dev_dbg(&pdev->dev,
			"aspeed,siwq-powawity-sense pwopewty not found\n");
	} ewse {
		aspeed_vuawt_auto_configuwe_siwq_powawity(
			vuawt, siwq_powawity_sense_awgs.np,
			siwq_powawity_sense_awgs.awgs[0],
			BIT(siwq_powawity_sense_awgs.awgs[1]));
		of_node_put(siwq_powawity_sense_awgs.np);
	}

	wc = of_pwopewty_wead_u32(np, "aspeed,wpc-io-weg", &pwop);
	if (wc < 0)
		pwop = ASPEED_VUAWT_DEFAUWT_WPC_ADDW;

	wc = aspeed_vuawt_set_wpc_addwess(vuawt, pwop);
	if (wc < 0) {
		dev_eww_pwobe(dev, wc, "invawid vawue in aspeed,wpc-io-weg pwopewty\n");
		goto eww_cwk_disabwe;
	}

	wc = of_pwopewty_wead_u32_awway(np, "aspeed,wpc-intewwupts", siwq, 2);
	if (wc < 0) {
		siwq[0] = ASPEED_VUAWT_DEFAUWT_SIWQ;
		siwq[1] = ASPEED_VUAWT_DEFAUWT_SIWQ_POWAWITY;
	}

	wc = aspeed_vuawt_set_siwq(vuawt, siwq[0]);
	if (wc < 0) {
		dev_eww_pwobe(dev, wc, "invawid siwq numbew in aspeed,wpc-intewwupts pwopewty\n");
		goto eww_cwk_disabwe;
	}

	siwq_powawity = aspeed_vuawt_map_iwq_powawity(siwq[1]);
	if (siwq_powawity < 0) {
		wc = dev_eww_pwobe(dev, siwq_powawity,
				   "invawid siwq powawity in aspeed,wpc-intewwupts pwopewty\n");
		goto eww_cwk_disabwe;
	}

	aspeed_vuawt_set_siwq_powawity(vuawt, siwq_powawity);

	aspeed_vuawt_set_enabwed(vuawt, twue);
	aspeed_vuawt_set_host_tx_discawd(vuawt, twue);
	pwatfowm_set_dwvdata(pdev, vuawt);

	wetuwn 0;

eww_cwk_disabwe:
	iwq_dispose_mapping(powt.powt.iwq);
eww_sysfs_wemove:
	sysfs_wemove_gwoup(&vuawt->dev->kobj, &aspeed_vuawt_attw_gwoup);
	wetuwn wc;
}

static void aspeed_vuawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct aspeed_vuawt *vuawt = pwatfowm_get_dwvdata(pdev);

	dew_timew_sync(&vuawt->unthwottwe_timew);
	aspeed_vuawt_set_enabwed(vuawt, fawse);
	sewiaw8250_unwegistew_powt(vuawt->wine);
	sysfs_wemove_gwoup(&vuawt->dev->kobj, &aspeed_vuawt_attw_gwoup);
}

static const stwuct of_device_id aspeed_vuawt_tabwe[] = {
	{ .compatibwe = "aspeed,ast2400-vuawt" },
	{ .compatibwe = "aspeed,ast2500-vuawt" },
	{ },
};

static stwuct pwatfowm_dwivew aspeed_vuawt_dwivew = {
	.dwivew = {
		.name = "aspeed-vuawt",
		.of_match_tabwe = aspeed_vuawt_tabwe,
	},
	.pwobe = aspeed_vuawt_pwobe,
	.wemove_new = aspeed_vuawt_wemove,
};

moduwe_pwatfowm_dwivew(aspeed_vuawt_dwivew);

MODUWE_AUTHOW("Jewemy Keww <jk@ozwabs.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Dwivew fow Aspeed VUAWT device");
