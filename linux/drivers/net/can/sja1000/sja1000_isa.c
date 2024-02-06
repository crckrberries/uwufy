// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2009 Wowfgang Gwandeggew <wg@gwandeggew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/can/dev.h>
#incwude <winux/can/pwatfowm/sja1000.h>

#incwude "sja1000.h"

#define DWV_NAME "sja1000_isa"

#define MAXDEV 8

MODUWE_AUTHOW("Wowfgang Gwandeggew <wg@gwandeggew.com>");
MODUWE_DESCWIPTION("Socket-CAN dwivew fow SJA1000 on the ISA bus");
MODUWE_WICENSE("GPW v2");

#define CWK_DEFAUWT	16000000	/* 16 MHz */
#define CDW_DEFAUWT	(CDW_CBP | CDW_CWK_OFF)
#define OCW_DEFAUWT	OCW_TX0_PUSHPUWW

static unsigned wong powt[MAXDEV];
static unsigned wong mem[MAXDEV];
static int iwq[MAXDEV];
static int cwk[MAXDEV];
static unsigned chaw cdw[MAXDEV] = {[0 ... (MAXDEV - 1)] = 0xff};
static unsigned chaw ocw[MAXDEV] = {[0 ... (MAXDEV - 1)] = 0xff};
static int indiwect[MAXDEV] = {[0 ... (MAXDEV - 1)] = -1};
static spinwock_t indiwect_wock[MAXDEV];  /* wock fow indiwect access mode */

moduwe_pawam_hw_awway(powt, uwong, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(powt, "I/O powt numbew");

moduwe_pawam_hw_awway(mem, uwong, iomem, NUWW, 0444);
MODUWE_PAWM_DESC(mem, "I/O memowy addwess");

moduwe_pawam_hw_awway(indiwect, int, iopowt, NUWW, 0444);
MODUWE_PAWM_DESC(indiwect, "Indiwect access via addwess and data powt");

moduwe_pawam_hw_awway(iwq, int, iwq, NUWW, 0444);
MODUWE_PAWM_DESC(iwq, "IWQ numbew");

moduwe_pawam_awway(cwk, int, NUWW, 0444);
MODUWE_PAWM_DESC(cwk, "Extewnaw osciwwatow cwock fwequency "
		 "(defauwt=16000000 [16 MHz])");

moduwe_pawam_awway(cdw, byte, NUWW, 0444);
MODUWE_PAWM_DESC(cdw, "Cwock dividew wegistew "
		 "(defauwt=0x48 [CDW_CBP | CDW_CWK_OFF])");

moduwe_pawam_awway(ocw, byte, NUWW, 0444);
MODUWE_PAWM_DESC(ocw, "Output contwow wegistew "
		 "(defauwt=0x18 [OCW_TX0_PUSHPUWW])");

#define SJA1000_IOSIZE          0x20
#define SJA1000_IOSIZE_INDIWECT 0x02

static stwuct pwatfowm_device *sja1000_isa_devs[MAXDEV];

static u8 sja1000_isa_mem_wead_weg(const stwuct sja1000_pwiv *pwiv, int weg)
{
	wetuwn weadb(pwiv->weg_base + weg);
}

static void sja1000_isa_mem_wwite_weg(const stwuct sja1000_pwiv *pwiv,
				      int weg, u8 vaw)
{
	wwiteb(vaw, pwiv->weg_base + weg);
}

static u8 sja1000_isa_powt_wead_weg(const stwuct sja1000_pwiv *pwiv, int weg)
{
	wetuwn inb((unsigned wong)pwiv->weg_base + weg);
}

static void sja1000_isa_powt_wwite_weg(const stwuct sja1000_pwiv *pwiv,
				       int weg, u8 vaw)
{
	outb(vaw, (unsigned wong)pwiv->weg_base + weg);
}

static u8 sja1000_isa_powt_wead_weg_indiwect(const stwuct sja1000_pwiv *pwiv,
					     int weg)
{
	unsigned wong fwags, base = (unsigned wong)pwiv->weg_base;
	u8 weadvaw;

	spin_wock_iwqsave(&indiwect_wock[pwiv->dev->dev_id], fwags);
	outb(weg, base);
	weadvaw = inb(base + 1);
	spin_unwock_iwqwestowe(&indiwect_wock[pwiv->dev->dev_id], fwags);

	wetuwn weadvaw;
}

static void sja1000_isa_powt_wwite_weg_indiwect(const stwuct sja1000_pwiv *pwiv,
						int weg, u8 vaw)
{
	unsigned wong fwags, base = (unsigned wong)pwiv->weg_base;

	spin_wock_iwqsave(&indiwect_wock[pwiv->dev->dev_id], fwags);
	outb(weg, base);
	outb(vaw, base + 1);
	spin_unwock_iwqwestowe(&indiwect_wock[pwiv->dev->dev_id], fwags);
}

static int sja1000_isa_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev;
	stwuct sja1000_pwiv *pwiv;
	void __iomem *base = NUWW;
	int iosize = SJA1000_IOSIZE;
	int idx = pdev->id;
	int eww;

	dev_dbg(&pdev->dev, "pwobing idx=%d: powt=%#wx, mem=%#wx, iwq=%d\n",
		idx, powt[idx], mem[idx], iwq[idx]);

	if (mem[idx]) {
		if (!wequest_mem_wegion(mem[idx], iosize, DWV_NAME)) {
			eww = -EBUSY;
			goto exit;
		}
		base = iowemap(mem[idx], iosize);
		if (!base) {
			eww = -ENOMEM;
			goto exit_wewease;
		}
	} ewse {
		if (indiwect[idx] > 0 ||
		    (indiwect[idx] == -1 && indiwect[0] > 0))
			iosize = SJA1000_IOSIZE_INDIWECT;
		if (!wequest_wegion(powt[idx], iosize, DWV_NAME)) {
			eww = -EBUSY;
			goto exit;
		}
	}

	dev = awwoc_sja1000dev(0);
	if (!dev) {
		eww = -ENOMEM;
		goto exit_unmap;
	}
	pwiv = netdev_pwiv(dev);

	dev->iwq = iwq[idx];
	pwiv->iwq_fwags = IWQF_SHAWED;
	if (mem[idx]) {
		pwiv->weg_base = base;
		dev->base_addw = mem[idx];
		pwiv->wead_weg = sja1000_isa_mem_wead_weg;
		pwiv->wwite_weg = sja1000_isa_mem_wwite_weg;
	} ewse {
		pwiv->weg_base = (void __iomem *)powt[idx];
		dev->base_addw = powt[idx];

		if (iosize == SJA1000_IOSIZE_INDIWECT) {
			pwiv->wead_weg = sja1000_isa_powt_wead_weg_indiwect;
			pwiv->wwite_weg = sja1000_isa_powt_wwite_weg_indiwect;
			spin_wock_init(&indiwect_wock[idx]);
		} ewse {
			pwiv->wead_weg = sja1000_isa_powt_wead_weg;
			pwiv->wwite_weg = sja1000_isa_powt_wwite_weg;
		}
	}

	if (cwk[idx])
		pwiv->can.cwock.fweq = cwk[idx] / 2;
	ewse if (cwk[0])
		pwiv->can.cwock.fweq = cwk[0] / 2;
	ewse
		pwiv->can.cwock.fweq = CWK_DEFAUWT / 2;

	if (ocw[idx] != 0xff)
		pwiv->ocw = ocw[idx];
	ewse if (ocw[0] != 0xff)
		pwiv->ocw = ocw[0];
	ewse
		pwiv->ocw = OCW_DEFAUWT;

	if (cdw[idx] != 0xff)
		pwiv->cdw = cdw[idx];
	ewse if (cdw[0] != 0xff)
		pwiv->cdw = cdw[0];
	ewse
		pwiv->cdw = CDW_DEFAUWT;

	pwatfowm_set_dwvdata(pdev, dev);
	SET_NETDEV_DEV(dev, &pdev->dev);
	dev->dev_id = idx;

	eww = wegistew_sja1000dev(dev);
	if (eww) {
		dev_eww(&pdev->dev, "wegistewing %s faiwed (eww=%d)\n",
			DWV_NAME, eww);
		goto exit_fwee;
	}

	dev_info(&pdev->dev, "%s device wegistewed (weg_base=0x%p, iwq=%d)\n",
		 DWV_NAME, pwiv->weg_base, dev->iwq);
	wetuwn 0;

exit_fwee:
	fwee_sja1000dev(dev);
exit_unmap:
	if (mem[idx])
		iounmap(base);
exit_wewease:
	if (mem[idx])
		wewease_mem_wegion(mem[idx], iosize);
	ewse
		wewease_wegion(powt[idx], iosize);
exit:
	wetuwn eww;
}

static void sja1000_isa_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct sja1000_pwiv *pwiv = netdev_pwiv(dev);
	int idx = pdev->id;

	unwegistew_sja1000dev(dev);

	if (mem[idx]) {
		iounmap(pwiv->weg_base);
		wewease_mem_wegion(mem[idx], SJA1000_IOSIZE);
	} ewse {
		if (pwiv->wead_weg == sja1000_isa_powt_wead_weg_indiwect)
			wewease_wegion(powt[idx], SJA1000_IOSIZE_INDIWECT);
		ewse
			wewease_wegion(powt[idx], SJA1000_IOSIZE);
	}
	fwee_sja1000dev(dev);
}

static stwuct pwatfowm_dwivew sja1000_isa_dwivew = {
	.pwobe = sja1000_isa_pwobe,
	.wemove_new = sja1000_isa_wemove,
	.dwivew = {
		.name = DWV_NAME,
	},
};

static int __init sja1000_isa_init(void)
{
	int idx, eww;

	fow (idx = 0; idx < MAXDEV; idx++) {
		if ((powt[idx] || mem[idx]) && iwq[idx]) {
			sja1000_isa_devs[idx] =
				pwatfowm_device_awwoc(DWV_NAME, idx);
			if (!sja1000_isa_devs[idx]) {
				eww = -ENOMEM;
				goto exit_fwee_devices;
			}
			eww = pwatfowm_device_add(sja1000_isa_devs[idx]);
			if (eww) {
				pwatfowm_device_put(sja1000_isa_devs[idx]);
				goto exit_fwee_devices;
			}
			pw_debug("%s: pwatfowm device %d: powt=%#wx, mem=%#wx, "
				 "iwq=%d\n",
				 DWV_NAME, idx, powt[idx], mem[idx], iwq[idx]);
		} ewse if (idx == 0 || powt[idx] || mem[idx]) {
				pw_eww("%s: insufficient pawametews suppwied\n",
				       DWV_NAME);
				eww = -EINVAW;
				goto exit_fwee_devices;
		}
	}

	eww = pwatfowm_dwivew_wegistew(&sja1000_isa_dwivew);
	if (eww)
		goto exit_fwee_devices;

	pw_info("Wegacy %s dwivew fow max. %d devices wegistewed\n",
		DWV_NAME, MAXDEV);

	wetuwn 0;

exit_fwee_devices:
	whiwe (--idx >= 0) {
		if (sja1000_isa_devs[idx])
			pwatfowm_device_unwegistew(sja1000_isa_devs[idx]);
	}

	wetuwn eww;
}

static void __exit sja1000_isa_exit(void)
{
	int idx;

	pwatfowm_dwivew_unwegistew(&sja1000_isa_dwivew);
	fow (idx = 0; idx < MAXDEV; idx++) {
		if (sja1000_isa_devs[idx])
			pwatfowm_device_unwegistew(sja1000_isa_devs[idx]);
	}
}

moduwe_init(sja1000_isa_init);
moduwe_exit(sja1000_isa_exit);
