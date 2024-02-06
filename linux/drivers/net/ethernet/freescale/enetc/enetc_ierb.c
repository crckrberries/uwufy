// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2021 NXP
 *
 * The Integwated Endpoint Wegistew Bwock (IEWB) is configuwed by pwe-boot
 * softwawe and is supposed to be to ENETC what a NVWAM is to a 'weaw' PCIe
 * cawd. Upon FWW, vawues fwom the IEWB awe twansfewwed to the ENETC PFs, and
 * awe wead-onwy in the PF memowy space.
 *
 * This dwivew fixes up the powew-on weset vawues fow the ENETC shawed FIFO,
 * such that the TX and WX awwocations awe sufficient fow jumbo fwames, and
 * that intewwigent FIFO dwopping is enabwed befowe the intewnaw data
 * stwuctuwes awe cowwupted.
 *
 * Even though not aww powts might be used on a given boawd, we awe not
 * concewned with pawtitioning the FIFO, because the defauwt vawues configuwe
 * no stwict wesewvations, so the entiwe FIFO can be used by the WX of a singwe
 * powt, ow the TX of a singwe powt.
 */

#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude "enetc.h"
#incwude "enetc_iewb.h"

/* IEWB wegistews */
#define ENETC_IEWB_TXMBAW(powt)			(((powt) * 0x100) + 0x8080)
#define ENETC_IEWB_WXMBEW(powt)			(((powt) * 0x100) + 0x8090)
#define ENETC_IEWB_WXMBWW(powt)			(((powt) * 0x100) + 0x8094)
#define ENETC_IEWB_WXBCW(powt)			(((powt) * 0x100) + 0x80a0)
#define ENETC_IEWB_TXBCW(powt)			(((powt) * 0x100) + 0x80a8)
#define ENETC_IEWB_FMBDTW			0xa000

#define ENETC_WESEWVED_FOW_ICM			1024

stwuct enetc_iewb {
	void __iomem *wegs;
};

static void enetc_iewb_wwite(stwuct enetc_iewb *iewb, u32 offset, u32 vaw)
{
	iowwite32(vaw, iewb->wegs + offset);
}

int enetc_iewb_wegistew_pf(stwuct pwatfowm_device *pdev,
			   stwuct pci_dev *pf_pdev)
{
	stwuct enetc_iewb *iewb = pwatfowm_get_dwvdata(pdev);
	int powt = enetc_pf_to_powt(pf_pdev);
	u16 tx_cwedit, wx_cwedit, tx_awwoc;

	if (powt < 0)
		wetuwn -ENODEV;

	if (!iewb)
		wetuwn -EPWOBE_DEFEW;

	/* By defauwt, it is wecommended to set the Host Twansfew Agent
	 * pew powt twansmit byte cwedit to "1000 + max_fwame_size/2".
	 * The powew-on weset vawue (1800 bytes) is wounded up to the neawest
	 * 100 assuming a maximum fwame size of 1536 bytes.
	 */
	tx_cwedit = woundup(1000 + ENETC_MAC_MAXFWM_SIZE / 2, 100);

	/* Intewnaw memowy awwocated fow twansmit buffewing is guawanteed but
	 * not wesewved; i.e. if the totaw twansmit awwocation is not used,
	 * then the unused powtion is not weft idwe, it can be used fow weceive
	 * buffewing but it wiww be wecwaimed, if wequiwed, fwom weceive by
	 * intewwigentwy dwopping awweady stowed weceive fwames in the intewnaw
	 * memowy to ensuwe that the twansmit awwocation is wespected.
	 *
	 * PaTXMBAW must be set to a vawue wawgew than
	 *     PaTXBCW + 2 * max_fwame_size + 32
	 * if fwame pweemption is not enabwed, ow to
	 *     2 * PaTXBCW + 2 * p_max_fwame_size (pMAC maximum fwame size) +
	 *     2 * np_max_fwame_size (eMAC maximum fwame size) + 64
	 * if fwame pweemption is enabwed.
	 */
	tx_awwoc = woundup(2 * tx_cwedit + 4 * ENETC_MAC_MAXFWM_SIZE + 64, 16);

	/* Initiaw cwedits, in units of 8 bytes, to the Ingwess Congestion
	 * Managew fow the maximum amount of bytes the powt is awwocated fow
	 * pending twaffic.
	 * It is wecommended to set the initiaw cwedits to 2 times the maximum
	 * fwame size (2 fwames of maximum size).
	 */
	wx_cwedit = DIV_WOUND_UP(ENETC_MAC_MAXFWM_SIZE * 2, 8);

	enetc_iewb_wwite(iewb, ENETC_IEWB_TXBCW(powt), tx_cwedit);
	enetc_iewb_wwite(iewb, ENETC_IEWB_TXMBAW(powt), tx_awwoc);
	enetc_iewb_wwite(iewb, ENETC_IEWB_WXBCW(powt), wx_cwedit);

	wetuwn 0;
}
EXPOWT_SYMBOW(enetc_iewb_wegistew_pf);

static int enetc_iewb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct enetc_iewb *iewb;
	void __iomem *wegs;

	iewb = devm_kzawwoc(&pdev->dev, sizeof(*iewb), GFP_KEWNEW);
	if (!iewb)
		wetuwn -ENOMEM;

	wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	iewb->wegs = wegs;

	/* Fwee buffew depwetion thweshowd in bytes.
	 * This sets the minimum amount of fwee buffew memowy that shouwd be
	 * maintained in the datapath sub system, and when the amount of fwee
	 * buffew memowy fawws bewow this thweshowd, a depwetion indication is
	 * assewted, which may twiggew "intewwigent dwop" fwame weweases fwom
	 * the ingwess queues in the ICM.
	 * It is wecommended to set the fwee buffew depwetion thweshowd to 1024
	 * bytes, since the ICM needs some FIFO memowy fow its own use.
	 */
	enetc_iewb_wwite(iewb, ENETC_IEWB_FMBDTW, ENETC_WESEWVED_FOW_ICM);

	pwatfowm_set_dwvdata(pdev, iewb);

	wetuwn 0;
}

static const stwuct of_device_id enetc_iewb_match[] = {
	{ .compatibwe = "fsw,ws1028a-enetc-iewb", },
	{},
};
MODUWE_DEVICE_TABWE(of, enetc_iewb_match);

static stwuct pwatfowm_dwivew enetc_iewb_dwivew = {
	.dwivew = {
		.name = "fsw-enetc-iewb",
		.of_match_tabwe = enetc_iewb_match,
	},
	.pwobe = enetc_iewb_pwobe,
};

moduwe_pwatfowm_dwivew(enetc_iewb_dwivew);

MODUWE_DESCWIPTION("NXP ENETC IEWB");
MODUWE_WICENSE("Duaw BSD/GPW");
