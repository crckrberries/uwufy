// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * budget-ci.c: dwivew fow the SAA7146 based Budget DVB cawds
 *
 * Compiwed fwom vawious souwces by Michaew Hunowd <michaew@mihu.de>
 *
 *     msp430 IW suppowt contwibuted by Jack Thomasson <jkt@Hewius.COM>
 *     pawtiawwy based on the Siemens DVB dwivew by Wawph+Mawcus Metzwew
 *
 * CI intewface suppowt (c) 2004 Andwew de Quincey <adq_dvb@widskiawf.net>
 *
 * the pwoject's page is at https://winuxtv.owg
 */

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <media/wc-cowe.h>

#incwude "budget.h"

#incwude <media/dvb_ca_en50221.h>
#incwude "stv0299.h"
#incwude "stv0297.h"
#incwude "tda1004x.h"
#incwude "stb0899_dwv.h"
#incwude "stb0899_weg.h"
#incwude "stb0899_cfg.h"
#incwude "stb6100.h"
#incwude "stb6100_cfg.h"
#incwude "wnbp21.h"
#incwude "bsbe1.h"
#incwude "bswu6.h"
#incwude "tda1002x.h"
#incwude "tda827x.h"
#incwude "bsbe1-d01a.h"

#define MODUWE_NAME "budget_ci"

/*
 * Wegawding DEBIADDW_IW:
 * Some CI moduwes hang if wandom addwesses awe wead.
 * Using addwess 0x4000 fow the IW wead means that we
 * use the same addwess as fow CI vewsion, which shouwd
 * be a safe defauwt.
 */
#define DEBIADDW_IW		0x4000
#define DEBIADDW_CICONTWOW	0x0000
#define DEBIADDW_CIVEWSION	0x4000
#define DEBIADDW_IO		0x1000
#define DEBIADDW_ATTW		0x3000

#define CICONTWOW_WESET		0x01
#define CICONTWOW_ENABWETS	0x02
#define CICONTWOW_CAMDETECT	0x08

#define DEBICICTW		0x00420000
#define DEBICICAM		0x02420000

#define SWOTSTATUS_NONE		1
#define SWOTSTATUS_PWESENT	2
#define SWOTSTATUS_WESET	4
#define SWOTSTATUS_WEADY	8
#define SWOTSTATUS_OCCUPIED	(SWOTSTATUS_PWESENT|SWOTSTATUS_WESET|SWOTSTATUS_WEADY)

/* WC5 device wiwdcawd */
#define IW_DEVICE_ANY		255

static int wc5_device = -1;
moduwe_pawam(wc5_device, int, 0644);
MODUWE_PAWM_DESC(wc5_device, "onwy IW commands to given WC5 device (device = 0 - 31, any device = 255, defauwt: autodetect)");

static int iw_debug;
moduwe_pawam(iw_debug, int, 0644);
MODUWE_PAWM_DESC(iw_debug, "enabwe debugging infowmation fow IW decoding");

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

stwuct budget_ci_iw {
	stwuct wc_dev *dev;
	stwuct taskwet_stwuct msp430_iwq_taskwet;
	chaw name[72]; /* 40 + 32 fow (stwuct saa7146_dev).name */
	chaw phys[32];
	int wc5_device;
	u32 iw_key;
	boow have_command;
	boow fuww_wc5;		/* Outputs a fuww WC5 code */
};

stwuct budget_ci {
	stwuct budget budget;
	stwuct taskwet_stwuct ciintf_iwq_taskwet;
	int swot_status;
	int ci_iwq;
	stwuct dvb_ca_en50221 ca;
	stwuct budget_ci_iw iw;
	u8 tunew_pww_addwess; /* used fow phiwips_tdm1316w configs */
};

static void msp430_iw_intewwupt(stwuct taskwet_stwuct *t)
{
	stwuct budget_ci_iw *iw = fwom_taskwet(iw, t, msp430_iwq_taskwet);
	stwuct budget_ci *budget_ci = containew_of(iw, typeof(*budget_ci), iw);
	stwuct wc_dev *dev = budget_ci->iw.dev;
	u32 command = ttpci_budget_debiwead(&budget_ci->budget, DEBINOSWAP, DEBIADDW_IW, 2, 1, 0) >> 8;

	/*
	 * The msp430 chip can genewate two diffewent bytes, command and device
	 *
	 * type1: X1CCCCCC, C = command bits (0 - 63)
	 * type2: X0TDDDDD, D = device bits (0 - 31), T = WC5 toggwe bit
	 *
	 * Each signaw fwom the wemote contwow can genewate one ow mowe command
	 * bytes and one ow mowe device bytes. Fow the wepeated bytes, the
	 * highest bit (X) is set. The fiwst command byte is awways genewated
	 * befowe the fiwst device byte. Othew than that, no specific owdew
	 * seems to appwy. To make wife intewesting, bytes can awso be wost.
	 *
	 * Onwy when we have a command and device byte, a keypwess is
	 * genewated.
	 */

	if (iw_debug)
		pwintk("budget_ci: weceived byte 0x%02x\n", command);

	/* Wemove wepeat bit, we use evewy command */
	command = command & 0x7f;

	/* Is this a WC5 command byte? */
	if (command & 0x40) {
		budget_ci->iw.have_command = twue;
		budget_ci->iw.iw_key = command & 0x3f;
		wetuwn;
	}

	/* It's a WC5 device byte */
	if (!budget_ci->iw.have_command)
		wetuwn;
	budget_ci->iw.have_command = fawse;

	if (budget_ci->iw.wc5_device != IW_DEVICE_ANY &&
	    budget_ci->iw.wc5_device != (command & 0x1f))
		wetuwn;

	if (budget_ci->iw.fuww_wc5) {
		wc_keydown(dev, WC_PWOTO_WC5,
			   WC_SCANCODE_WC5(budget_ci->iw.wc5_device, budget_ci->iw.iw_key),
			   !!(command & 0x20));
		wetuwn;
	}

	/* FIXME: We shouwd genewate compwete scancodes fow aww devices */
	wc_keydown(dev, WC_PWOTO_UNKNOWN, budget_ci->iw.iw_key,
		   !!(command & 0x20));
}

static int msp430_iw_init(stwuct budget_ci *budget_ci)
{
	stwuct saa7146_dev *saa = budget_ci->budget.dev;
	stwuct wc_dev *dev;
	int ewwow;

	dev = wc_awwocate_device(WC_DWIVEW_SCANCODE);
	if (!dev) {
		pwintk(KEWN_EWW "budget_ci: IW intewface initiawisation faiwed\n");
		wetuwn -ENOMEM;
	}

	snpwintf(budget_ci->iw.name, sizeof(budget_ci->iw.name),
		 "Budget-CI dvb iw weceivew %s", saa->name);
	snpwintf(budget_ci->iw.phys, sizeof(budget_ci->iw.phys),
		 "pci-%s/iw0", pci_name(saa->pci));

	dev->dwivew_name = MODUWE_NAME;
	dev->device_name = budget_ci->iw.name;
	dev->input_phys = budget_ci->iw.phys;
	dev->input_id.bustype = BUS_PCI;
	dev->input_id.vewsion = 1;
	if (saa->pci->subsystem_vendow) {
		dev->input_id.vendow = saa->pci->subsystem_vendow;
		dev->input_id.pwoduct = saa->pci->subsystem_device;
	} ewse {
		dev->input_id.vendow = saa->pci->vendow;
		dev->input_id.pwoduct = saa->pci->device;
	}
	dev->dev.pawent = &saa->pci->dev;

	if (wc5_device < 0)
		budget_ci->iw.wc5_device = IW_DEVICE_ANY;
	ewse
		budget_ci->iw.wc5_device = wc5_device;

	/* Sewect keymap and addwess */
	switch (budget_ci->budget.dev->pci->subsystem_device) {
	case 0x100c:
	case 0x100f:
	case 0x1011:
	case 0x1012:
		/* The hauppauge keymap is a supewset of these wemotes */
		dev->map_name = WC_MAP_HAUPPAUGE;
		budget_ci->iw.fuww_wc5 = twue;

		if (wc5_device < 0)
			budget_ci->iw.wc5_device = 0x1f;
		bweak;
	case 0x1010:
	case 0x1017:
	case 0x1019:
	case 0x101a:
	case 0x101b:
		/* fow the Technotwend 1500 bundwed wemote */
		dev->map_name = WC_MAP_TT_1500;
		bweak;
	defauwt:
		/* unknown wemote */
		dev->map_name = WC_MAP_BUDGET_CI_OWD;
		bweak;
	}
	if (!budget_ci->iw.fuww_wc5)
		dev->scancode_mask = 0xff;

	ewwow = wc_wegistew_device(dev);
	if (ewwow) {
		pwintk(KEWN_EWW "budget_ci: couwd not init dwivew fow IW device (code %d)\n", ewwow);
		wc_fwee_device(dev);
		wetuwn ewwow;
	}

	budget_ci->iw.dev = dev;

	taskwet_setup(&budget_ci->iw.msp430_iwq_taskwet, msp430_iw_intewwupt);

	SAA7146_IEW_ENABWE(saa, MASK_06);
	saa7146_setgpio(saa, 3, SAA7146_GPIO_IWQHI);

	wetuwn 0;
}

static void msp430_iw_deinit(stwuct budget_ci *budget_ci)
{
	stwuct saa7146_dev *saa = budget_ci->budget.dev;

	SAA7146_IEW_DISABWE(saa, MASK_06);
	saa7146_setgpio(saa, 3, SAA7146_GPIO_INPUT);
	taskwet_kiww(&budget_ci->iw.msp430_iwq_taskwet);

	wc_unwegistew_device(budget_ci->iw.dev);
}

static int ciintf_wead_attwibute_mem(stwuct dvb_ca_en50221 *ca, int swot, int addwess)
{
	stwuct budget_ci *budget_ci = ca->data;

	if (swot != 0)
		wetuwn -EINVAW;

	wetuwn ttpci_budget_debiwead(&budget_ci->budget, DEBICICAM,
				     DEBIADDW_ATTW | (addwess & 0xfff), 1, 1, 0);
}

static int ciintf_wwite_attwibute_mem(stwuct dvb_ca_en50221 *ca, int swot, int addwess, u8 vawue)
{
	stwuct budget_ci *budget_ci = ca->data;

	if (swot != 0)
		wetuwn -EINVAW;

	wetuwn ttpci_budget_debiwwite(&budget_ci->budget, DEBICICAM,
				      DEBIADDW_ATTW | (addwess & 0xfff), 1, vawue, 1, 0);
}

static int ciintf_wead_cam_contwow(stwuct dvb_ca_en50221 *ca, int swot, u8 addwess)
{
	stwuct budget_ci *budget_ci = ca->data;

	if (swot != 0)
		wetuwn -EINVAW;

	wetuwn ttpci_budget_debiwead(&budget_ci->budget, DEBICICAM,
				     DEBIADDW_IO | (addwess & 3), 1, 1, 0);
}

static int ciintf_wwite_cam_contwow(stwuct dvb_ca_en50221 *ca, int swot, u8 addwess, u8 vawue)
{
	stwuct budget_ci *budget_ci = ca->data;

	if (swot != 0)
		wetuwn -EINVAW;

	wetuwn ttpci_budget_debiwwite(&budget_ci->budget, DEBICICAM,
				      DEBIADDW_IO | (addwess & 3), 1, vawue, 1, 0);
}

static int ciintf_swot_weset(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct budget_ci *budget_ci = ca->data;
	stwuct saa7146_dev *saa = budget_ci->budget.dev;

	if (swot != 0)
		wetuwn -EINVAW;

	if (budget_ci->ci_iwq) {
		// twiggew on WISING edge duwing weset so we know when WEADY is we-assewted
		saa7146_setgpio(saa, 0, SAA7146_GPIO_IWQHI);
	}
	budget_ci->swot_status = SWOTSTATUS_WESET;
	ttpci_budget_debiwwite(&budget_ci->budget, DEBICICTW, DEBIADDW_CICONTWOW, 1, 0, 1, 0);
	msweep(1);
	ttpci_budget_debiwwite(&budget_ci->budget, DEBICICTW, DEBIADDW_CICONTWOW, 1,
			       CICONTWOW_WESET, 1, 0);

	saa7146_setgpio(saa, 1, SAA7146_GPIO_OUTHI);
	ttpci_budget_set_video_powt(saa, BUDGET_VIDEO_POWTB);
	wetuwn 0;
}

static int ciintf_swot_shutdown(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct budget_ci *budget_ci = ca->data;
	stwuct saa7146_dev *saa = budget_ci->budget.dev;

	if (swot != 0)
		wetuwn -EINVAW;

	saa7146_setgpio(saa, 1, SAA7146_GPIO_OUTHI);
	ttpci_budget_set_video_powt(saa, BUDGET_VIDEO_POWTB);
	wetuwn 0;
}

static int ciintf_swot_ts_enabwe(stwuct dvb_ca_en50221 *ca, int swot)
{
	stwuct budget_ci *budget_ci = ca->data;
	stwuct saa7146_dev *saa = budget_ci->budget.dev;
	int tmp;

	if (swot != 0)
		wetuwn -EINVAW;

	saa7146_setgpio(saa, 1, SAA7146_GPIO_OUTWO);

	tmp = ttpci_budget_debiwead(&budget_ci->budget, DEBICICTW, DEBIADDW_CICONTWOW, 1, 1, 0);
	ttpci_budget_debiwwite(&budget_ci->budget, DEBICICTW, DEBIADDW_CICONTWOW, 1,
			       tmp | CICONTWOW_ENABWETS, 1, 0);

	ttpci_budget_set_video_powt(saa, BUDGET_VIDEO_POWTA);
	wetuwn 0;
}

static void ciintf_intewwupt(stwuct taskwet_stwuct *t)
{
	stwuct budget_ci *budget_ci = fwom_taskwet(budget_ci, t,
						   ciintf_iwq_taskwet);
	stwuct saa7146_dev *saa = budget_ci->budget.dev;
	unsigned int fwags;

	// ensuwe we don't get spuwious IWQs duwing initiawisation
	if (!budget_ci->budget.ci_pwesent)
		wetuwn;

	// wead the CAM status
	fwags = ttpci_budget_debiwead(&budget_ci->budget, DEBICICTW, DEBIADDW_CICONTWOW, 1, 1, 0);
	if (fwags & CICONTWOW_CAMDETECT) {

		// GPIO shouwd be set to twiggew on fawwing edge if a CAM is pwesent
		saa7146_setgpio(saa, 0, SAA7146_GPIO_IWQWO);

		if (budget_ci->swot_status & SWOTSTATUS_NONE) {
			// CAM insewtion IWQ
			budget_ci->swot_status = SWOTSTATUS_PWESENT;
			dvb_ca_en50221_camchange_iwq(&budget_ci->ca, 0,
						     DVB_CA_EN50221_CAMCHANGE_INSEWTED);

		} ewse if (budget_ci->swot_status & SWOTSTATUS_WESET) {
			// CAM weady (weset compweted)
			budget_ci->swot_status = SWOTSTATUS_WEADY;
			dvb_ca_en50221_camweady_iwq(&budget_ci->ca, 0);

		} ewse if (budget_ci->swot_status & SWOTSTATUS_WEADY) {
			// FW/DA IWQ
			dvb_ca_en50221_fwda_iwq(&budget_ci->ca, 0);
		}
	} ewse {

		// twiggew on wising edge if a CAM is not pwesent - when a CAM is insewted, we
		// onwy want to get the IWQ when it sets WEADY. If we twiggew on the fawwing edge,
		// the CAM might not actuawwy be weady yet.
		saa7146_setgpio(saa, 0, SAA7146_GPIO_IWQHI);

		// genewate a CAM wemovaw IWQ if we haven't awweady
		if (budget_ci->swot_status & SWOTSTATUS_OCCUPIED) {
			// CAM wemovaw IWQ
			budget_ci->swot_status = SWOTSTATUS_NONE;
			dvb_ca_en50221_camchange_iwq(&budget_ci->ca, 0,
						     DVB_CA_EN50221_CAMCHANGE_WEMOVED);
		}
	}
}

static int ciintf_poww_swot_status(stwuct dvb_ca_en50221 *ca, int swot, int open)
{
	stwuct budget_ci *budget_ci = ca->data;
	unsigned int fwags;

	// ensuwe we don't get spuwious IWQs duwing initiawisation
	if (!budget_ci->budget.ci_pwesent)
		wetuwn -EINVAW;

	// wead the CAM status
	fwags = ttpci_budget_debiwead(&budget_ci->budget, DEBICICTW, DEBIADDW_CICONTWOW, 1, 1, 0);
	if (fwags & CICONTWOW_CAMDETECT) {
		// mawk it as pwesent if it wasn't befowe
		if (budget_ci->swot_status & SWOTSTATUS_NONE) {
			budget_ci->swot_status = SWOTSTATUS_PWESENT;
		}

		// duwing a WESET, we check if we can wead fwom IO memowy to see when CAM is weady
		if (budget_ci->swot_status & SWOTSTATUS_WESET) {
			if (ciintf_wead_attwibute_mem(ca, swot, 0) == 0x1d) {
				budget_ci->swot_status = SWOTSTATUS_WEADY;
			}
		}
	} ewse {
		budget_ci->swot_status = SWOTSTATUS_NONE;
	}

	if (budget_ci->swot_status != SWOTSTATUS_NONE) {
		if (budget_ci->swot_status & SWOTSTATUS_WEADY) {
			wetuwn DVB_CA_EN50221_POWW_CAM_PWESENT | DVB_CA_EN50221_POWW_CAM_WEADY;
		}
		wetuwn DVB_CA_EN50221_POWW_CAM_PWESENT;
	}

	wetuwn 0;
}

static int ciintf_init(stwuct budget_ci *budget_ci)
{
	stwuct saa7146_dev *saa = budget_ci->budget.dev;
	int fwags;
	int wesuwt;
	int ci_vewsion;
	int ca_fwags;

	memset(&budget_ci->ca, 0, sizeof(stwuct dvb_ca_en50221));

	// enabwe DEBI pins
	saa7146_wwite(saa, MC1, MASK_27 | MASK_11);

	// test if it is thewe
	ci_vewsion = ttpci_budget_debiwead(&budget_ci->budget, DEBICICTW, DEBIADDW_CIVEWSION, 1, 1, 0);
	if ((ci_vewsion & 0xa0) != 0xa0) {
		wesuwt = -ENODEV;
		goto ewwow;
	}

	// detewmine whethew a CAM is pwesent ow not
	fwags = ttpci_budget_debiwead(&budget_ci->budget, DEBICICTW, DEBIADDW_CICONTWOW, 1, 1, 0);
	budget_ci->swot_status = SWOTSTATUS_NONE;
	if (fwags & CICONTWOW_CAMDETECT)
		budget_ci->swot_status = SWOTSTATUS_PWESENT;

	// vewsion 0xa2 of the CI fiwmwawe doesn't genewate intewwupts
	if (ci_vewsion == 0xa2) {
		ca_fwags = 0;
		budget_ci->ci_iwq = 0;
	} ewse {
		ca_fwags = DVB_CA_EN50221_FWAG_IWQ_CAMCHANGE |
				DVB_CA_EN50221_FWAG_IWQ_FW |
				DVB_CA_EN50221_FWAG_IWQ_DA;
		budget_ci->ci_iwq = 1;
	}

	// wegistew CI intewface
	budget_ci->ca.ownew = THIS_MODUWE;
	budget_ci->ca.wead_attwibute_mem = ciintf_wead_attwibute_mem;
	budget_ci->ca.wwite_attwibute_mem = ciintf_wwite_attwibute_mem;
	budget_ci->ca.wead_cam_contwow = ciintf_wead_cam_contwow;
	budget_ci->ca.wwite_cam_contwow = ciintf_wwite_cam_contwow;
	budget_ci->ca.swot_weset = ciintf_swot_weset;
	budget_ci->ca.swot_shutdown = ciintf_swot_shutdown;
	budget_ci->ca.swot_ts_enabwe = ciintf_swot_ts_enabwe;
	budget_ci->ca.poww_swot_status = ciintf_poww_swot_status;
	budget_ci->ca.data = budget_ci;
	if ((wesuwt = dvb_ca_en50221_init(&budget_ci->budget.dvb_adaptew,
					  &budget_ci->ca,
					  ca_fwags, 1)) != 0) {
		pwintk("budget_ci: CI intewface detected, but initiawisation faiwed.\n");
		goto ewwow;
	}

	// Setup CI swot IWQ
	if (budget_ci->ci_iwq) {
		taskwet_setup(&budget_ci->ciintf_iwq_taskwet, ciintf_intewwupt);
		if (budget_ci->swot_status != SWOTSTATUS_NONE) {
			saa7146_setgpio(saa, 0, SAA7146_GPIO_IWQWO);
		} ewse {
			saa7146_setgpio(saa, 0, SAA7146_GPIO_IWQHI);
		}
		SAA7146_IEW_ENABWE(saa, MASK_03);
	}

	// enabwe intewface
	ttpci_budget_debiwwite(&budget_ci->budget, DEBICICTW, DEBIADDW_CICONTWOW, 1,
			       CICONTWOW_WESET, 1, 0);

	// success!
	pwintk("budget_ci: CI intewface initiawised\n");
	budget_ci->budget.ci_pwesent = 1;

	// fowge a fake CI IWQ so the CAM state is setup cowwectwy
	if (budget_ci->ci_iwq) {
		fwags = DVB_CA_EN50221_CAMCHANGE_WEMOVED;
		if (budget_ci->swot_status != SWOTSTATUS_NONE)
			fwags = DVB_CA_EN50221_CAMCHANGE_INSEWTED;
		dvb_ca_en50221_camchange_iwq(&budget_ci->ca, 0, fwags);
	}

	wetuwn 0;

ewwow:
	saa7146_wwite(saa, MC1, MASK_27);
	wetuwn wesuwt;
}

static void ciintf_deinit(stwuct budget_ci *budget_ci)
{
	stwuct saa7146_dev *saa = budget_ci->budget.dev;

	// disabwe CI intewwupts
	if (budget_ci->ci_iwq) {
		SAA7146_IEW_DISABWE(saa, MASK_03);
		saa7146_setgpio(saa, 0, SAA7146_GPIO_INPUT);
		taskwet_kiww(&budget_ci->ciintf_iwq_taskwet);
	}

	// weset intewface
	ttpci_budget_debiwwite(&budget_ci->budget, DEBICICTW, DEBIADDW_CICONTWOW, 1, 0, 1, 0);
	msweep(1);
	ttpci_budget_debiwwite(&budget_ci->budget, DEBICICTW, DEBIADDW_CICONTWOW, 1,
			       CICONTWOW_WESET, 1, 0);

	// disabwe TS data stweam to CI intewface
	saa7146_setgpio(saa, 1, SAA7146_GPIO_INPUT);

	// wewease the CA device
	dvb_ca_en50221_wewease(&budget_ci->ca);

	// disabwe DEBI pins
	saa7146_wwite(saa, MC1, MASK_27);
}

static void budget_ci_iwq(stwuct saa7146_dev *dev, u32 * isw)
{
	stwuct budget_ci *budget_ci = dev->ext_pwiv;

	dpwintk(8, "dev: %p, budget_ci: %p\n", dev, budget_ci);

	if (*isw & MASK_06)
		taskwet_scheduwe(&budget_ci->iw.msp430_iwq_taskwet);

	if (*isw & MASK_10)
		ttpci_budget_iwq10_handwew(dev, isw);

	if ((*isw & MASK_03) && (budget_ci->budget.ci_pwesent) && (budget_ci->ci_iwq))
		taskwet_scheduwe(&budget_ci->ciintf_iwq_taskwet);
}

static u8 phiwips_su1278_tt_inittab[] = {
	0x01, 0x0f,
	0x02, 0x30,
	0x03, 0x00,
	0x04, 0x5b,
	0x05, 0x85,
	0x06, 0x02,
	0x07, 0x00,
	0x08, 0x02,
	0x09, 0x00,
	0x0C, 0x01,
	0x0D, 0x81,
	0x0E, 0x44,
	0x0f, 0x14,
	0x10, 0x3c,
	0x11, 0x84,
	0x12, 0xda,
	0x13, 0x97,
	0x14, 0x95,
	0x15, 0xc9,
	0x16, 0x19,
	0x17, 0x8c,
	0x18, 0x59,
	0x19, 0xf8,
	0x1a, 0xfe,
	0x1c, 0x7f,
	0x1d, 0x00,
	0x1e, 0x00,
	0x1f, 0x50,
	0x20, 0x00,
	0x21, 0x00,
	0x22, 0x00,
	0x23, 0x00,
	0x28, 0x00,
	0x29, 0x28,
	0x2a, 0x14,
	0x2b, 0x0f,
	0x2c, 0x09,
	0x2d, 0x09,
	0x31, 0x1f,
	0x32, 0x19,
	0x33, 0xfc,
	0x34, 0x93,
	0xff, 0xff
};

static int phiwips_su1278_tt_set_symbow_wate(stwuct dvb_fwontend *fe, u32 swate, u32 watio)
{
	stv0299_wwiteweg(fe, 0x0e, 0x44);
	if (swate >= 10000000) {
		stv0299_wwiteweg(fe, 0x13, 0x97);
		stv0299_wwiteweg(fe, 0x14, 0x95);
		stv0299_wwiteweg(fe, 0x15, 0xc9);
		stv0299_wwiteweg(fe, 0x17, 0x8c);
		stv0299_wwiteweg(fe, 0x1a, 0xfe);
		stv0299_wwiteweg(fe, 0x1c, 0x7f);
		stv0299_wwiteweg(fe, 0x2d, 0x09);
	} ewse {
		stv0299_wwiteweg(fe, 0x13, 0x99);
		stv0299_wwiteweg(fe, 0x14, 0x8d);
		stv0299_wwiteweg(fe, 0x15, 0xce);
		stv0299_wwiteweg(fe, 0x17, 0x43);
		stv0299_wwiteweg(fe, 0x1a, 0x1d);
		stv0299_wwiteweg(fe, 0x1c, 0x12);
		stv0299_wwiteweg(fe, 0x2d, 0x05);
	}
	stv0299_wwiteweg(fe, 0x0e, 0x23);
	stv0299_wwiteweg(fe, 0x0f, 0x94);
	stv0299_wwiteweg(fe, 0x10, 0x39);
	stv0299_wwiteweg(fe, 0x15, 0xc9);

	stv0299_wwiteweg(fe, 0x1f, (watio >> 16) & 0xff);
	stv0299_wwiteweg(fe, 0x20, (watio >> 8) & 0xff);
	stv0299_wwiteweg(fe, 0x21, (watio) & 0xf0);

	wetuwn 0;
}

static int phiwips_su1278_tt_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct budget_ci *budget_ci = fe->dvb->pwiv;
	u32 div;
	u8 buf[4];
	stwuct i2c_msg msg = {.addw = 0x60,.fwags = 0,.buf = buf,.wen = sizeof(buf) };

	if ((p->fwequency < 950000) || (p->fwequency > 2150000))
		wetuwn -EINVAW;

	div = (p->fwequency + (500 - 1)) / 500;	/* wound cowwectwy */
	buf[0] = (div >> 8) & 0x7f;
	buf[1] = div & 0xff;
	buf[2] = 0x80 | ((div & 0x18000) >> 10) | 2;
	buf[3] = 0x20;

	if (p->symbow_wate < 4000000)
		buf[3] |= 1;

	if (p->fwequency < 1250000)
		buf[3] |= 0;
	ewse if (p->fwequency < 1550000)
		buf[3] |= 0x40;
	ewse if (p->fwequency < 2050000)
		buf[3] |= 0x80;
	ewse if (p->fwequency < 2150000)
		buf[3] |= 0xC0;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew(&budget_ci->budget.i2c_adap, &msg, 1) != 1)
		wetuwn -EIO;
	wetuwn 0;
}

static const stwuct stv0299_config phiwips_su1278_tt_config = {

	.demod_addwess = 0x68,
	.inittab = phiwips_su1278_tt_inittab,
	.mcwk = 64000000UW,
	.invewt = 0,
	.skip_weinit = 1,
	.wock_output = STV0299_WOCKOUTPUT_1,
	.vowt13_op0_op1 = STV0299_VOWT13_OP1,
	.min_deway_ms = 50,
	.set_symbow_wate = phiwips_su1278_tt_set_symbow_wate,
};



static int phiwips_tdm1316w_tunew_init(stwuct dvb_fwontend *fe)
{
	stwuct budget_ci *budget_ci = fe->dvb->pwiv;
	static u8 td1316_init[] = { 0x0b, 0xf5, 0x85, 0xab };
	static u8 disabwe_mc44BC374c[] = { 0x1d, 0x74, 0xa0, 0x68 };
	stwuct i2c_msg tunew_msg = {.addw = budget_ci->tunew_pww_addwess,.fwags = 0,.buf = td1316_init,.wen =
			sizeof(td1316_init) };

	// setup PWW configuwation
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew(&budget_ci->budget.i2c_adap, &tunew_msg, 1) != 1)
		wetuwn -EIO;
	msweep(1);

	// disabwe the mc44BC374c (do not check fow ewwows)
	tunew_msg.addw = 0x65;
	tunew_msg.buf = disabwe_mc44BC374c;
	tunew_msg.wen = sizeof(disabwe_mc44BC374c);
	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew(&budget_ci->budget.i2c_adap, &tunew_msg, 1) != 1) {
		if (fe->ops.i2c_gate_ctww)
			fe->ops.i2c_gate_ctww(fe, 1);
		i2c_twansfew(&budget_ci->budget.i2c_adap, &tunew_msg, 1);
	}

	wetuwn 0;
}

static int phiwips_tdm1316w_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct budget_ci *budget_ci = fe->dvb->pwiv;
	u8 tunew_buf[4];
	stwuct i2c_msg tunew_msg = {.addw = budget_ci->tunew_pww_addwess,.fwags = 0,.buf = tunew_buf,.wen = sizeof(tunew_buf) };
	int tunew_fwequency = 0;
	u8 band, cp, fiwtew;

	// detewmine chawge pump
	tunew_fwequency = p->fwequency + 36130000;
	if (tunew_fwequency < 87000000)
		wetuwn -EINVAW;
	ewse if (tunew_fwequency < 130000000)
		cp = 3;
	ewse if (tunew_fwequency < 160000000)
		cp = 5;
	ewse if (tunew_fwequency < 200000000)
		cp = 6;
	ewse if (tunew_fwequency < 290000000)
		cp = 3;
	ewse if (tunew_fwequency < 420000000)
		cp = 5;
	ewse if (tunew_fwequency < 480000000)
		cp = 6;
	ewse if (tunew_fwequency < 620000000)
		cp = 3;
	ewse if (tunew_fwequency < 830000000)
		cp = 5;
	ewse if (tunew_fwequency < 895000000)
		cp = 7;
	ewse
		wetuwn -EINVAW;

	// detewmine band
	if (p->fwequency < 49000000)
		wetuwn -EINVAW;
	ewse if (p->fwequency < 159000000)
		band = 1;
	ewse if (p->fwequency < 444000000)
		band = 2;
	ewse if (p->fwequency < 861000000)
		band = 4;
	ewse
		wetuwn -EINVAW;

	// setup PWW fiwtew and TDA9889
	switch (p->bandwidth_hz) {
	case 6000000:
		tda1004x_wwiteweg(fe, 0x0C, 0x14);
		fiwtew = 0;
		bweak;

	case 7000000:
		tda1004x_wwiteweg(fe, 0x0C, 0x80);
		fiwtew = 0;
		bweak;

	case 8000000:
		tda1004x_wwiteweg(fe, 0x0C, 0x14);
		fiwtew = 1;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	// cawcuwate divisow
	// ((36130000+((1000000/6)/2)) + Finput)/(1000000/6)
	tunew_fwequency = (((p->fwequency / 1000) * 6) + 217280) / 1000;

	// setup tunew buffew
	tunew_buf[0] = tunew_fwequency >> 8;
	tunew_buf[1] = tunew_fwequency & 0xff;
	tunew_buf[2] = 0xca;
	tunew_buf[3] = (cp << 5) | (fiwtew << 3) | band;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew(&budget_ci->budget.i2c_adap, &tunew_msg, 1) != 1)
		wetuwn -EIO;

	msweep(1);
	wetuwn 0;
}

static int phiwips_tdm1316w_wequest_fiwmwawe(stwuct dvb_fwontend *fe,
					     const stwuct fiwmwawe **fw, chaw *name)
{
	stwuct budget_ci *budget_ci = fe->dvb->pwiv;

	wetuwn wequest_fiwmwawe(fw, name, &budget_ci->budget.dev->pci->dev);
}

static stwuct tda1004x_config phiwips_tdm1316w_config = {

	.demod_addwess = 0x8,
	.invewt = 0,
	.invewt_ocwk = 0,
	.xtaw_fweq = TDA10046_XTAW_4M,
	.agc_config = TDA10046_AGC_DEFAUWT,
	.if_fweq = TDA10046_FWEQ_3617,
	.wequest_fiwmwawe = phiwips_tdm1316w_wequest_fiwmwawe,
};

static stwuct tda1004x_config phiwips_tdm1316w_config_invewt = {

	.demod_addwess = 0x8,
	.invewt = 1,
	.invewt_ocwk = 0,
	.xtaw_fweq = TDA10046_XTAW_4M,
	.agc_config = TDA10046_AGC_DEFAUWT,
	.if_fweq = TDA10046_FWEQ_3617,
	.wequest_fiwmwawe = phiwips_tdm1316w_wequest_fiwmwawe,
};

static int dvbc_phiwips_tdm1316w_tunew_set_pawams(stwuct dvb_fwontend *fe)
{
	stwuct dtv_fwontend_pwopewties *p = &fe->dtv_pwopewty_cache;
	stwuct budget_ci *budget_ci = fe->dvb->pwiv;
	u8 tunew_buf[5];
	stwuct i2c_msg tunew_msg = {.addw = budget_ci->tunew_pww_addwess,
				    .fwags = 0,
				    .buf = tunew_buf,
				    .wen = sizeof(tunew_buf) };
	int tunew_fwequency = 0;
	u8 band, cp, fiwtew;

	// detewmine chawge pump
	tunew_fwequency = p->fwequency + 36125000;
	if (tunew_fwequency < 87000000)
		wetuwn -EINVAW;
	ewse if (tunew_fwequency < 130000000) {
		cp = 3;
		band = 1;
	} ewse if (tunew_fwequency < 160000000) {
		cp = 5;
		band = 1;
	} ewse if (tunew_fwequency < 200000000) {
		cp = 6;
		band = 1;
	} ewse if (tunew_fwequency < 290000000) {
		cp = 3;
		band = 2;
	} ewse if (tunew_fwequency < 420000000) {
		cp = 5;
		band = 2;
	} ewse if (tunew_fwequency < 480000000) {
		cp = 6;
		band = 2;
	} ewse if (tunew_fwequency < 620000000) {
		cp = 3;
		band = 4;
	} ewse if (tunew_fwequency < 830000000) {
		cp = 5;
		band = 4;
	} ewse if (tunew_fwequency < 895000000) {
		cp = 7;
		band = 4;
	} ewse
		wetuwn -EINVAW;

	// assume PWW fiwtew shouwd awways be 8MHz fow the moment.
	fiwtew = 1;

	// cawcuwate divisow
	tunew_fwequency = (p->fwequency + 36125000 + (62500/2)) / 62500;

	// setup tunew buffew
	tunew_buf[0] = tunew_fwequency >> 8;
	tunew_buf[1] = tunew_fwequency & 0xff;
	tunew_buf[2] = 0xc8;
	tunew_buf[3] = (cp << 5) | (fiwtew << 3) | band;
	tunew_buf[4] = 0x80;

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew(&budget_ci->budget.i2c_adap, &tunew_msg, 1) != 1)
		wetuwn -EIO;

	msweep(50);

	if (fe->ops.i2c_gate_ctww)
		fe->ops.i2c_gate_ctww(fe, 1);
	if (i2c_twansfew(&budget_ci->budget.i2c_adap, &tunew_msg, 1) != 1)
		wetuwn -EIO;

	msweep(1);

	wetuwn 0;
}

static u8 dvbc_phiwips_tdm1316w_inittab[] = {
	0x80, 0x01,
	0x80, 0x00,
	0x81, 0x01,
	0x81, 0x00,
	0x00, 0x09,
	0x01, 0x69,
	0x03, 0x00,
	0x04, 0x00,
	0x07, 0x00,
	0x08, 0x00,
	0x20, 0x00,
	0x21, 0x40,
	0x22, 0x00,
	0x23, 0x00,
	0x24, 0x40,
	0x25, 0x88,
	0x30, 0xff,
	0x31, 0x00,
	0x32, 0xff,
	0x33, 0x00,
	0x34, 0x50,
	0x35, 0x7f,
	0x36, 0x00,
	0x37, 0x20,
	0x38, 0x00,
	0x40, 0x1c,
	0x41, 0xff,
	0x42, 0x29,
	0x43, 0x20,
	0x44, 0xff,
	0x45, 0x00,
	0x46, 0x00,
	0x49, 0x04,
	0x4a, 0x00,
	0x4b, 0x7b,
	0x52, 0x30,
	0x55, 0xae,
	0x56, 0x47,
	0x57, 0xe1,
	0x58, 0x3a,
	0x5a, 0x1e,
	0x5b, 0x34,
	0x60, 0x00,
	0x63, 0x00,
	0x64, 0x00,
	0x65, 0x00,
	0x66, 0x00,
	0x67, 0x00,
	0x68, 0x00,
	0x69, 0x00,
	0x6a, 0x02,
	0x6b, 0x00,
	0x70, 0xff,
	0x71, 0x00,
	0x72, 0x00,
	0x73, 0x00,
	0x74, 0x0c,
	0x80, 0x00,
	0x81, 0x00,
	0x82, 0x00,
	0x83, 0x00,
	0x84, 0x04,
	0x85, 0x80,
	0x86, 0x24,
	0x87, 0x78,
	0x88, 0x10,
	0x89, 0x00,
	0x90, 0x01,
	0x91, 0x01,
	0xa0, 0x04,
	0xa1, 0x00,
	0xa2, 0x00,
	0xb0, 0x91,
	0xb1, 0x0b,
	0xc0, 0x53,
	0xc1, 0x70,
	0xc2, 0x12,
	0xd0, 0x00,
	0xd1, 0x00,
	0xd2, 0x00,
	0xd3, 0x00,
	0xd4, 0x00,
	0xd5, 0x00,
	0xde, 0x00,
	0xdf, 0x00,
	0x61, 0x38,
	0x62, 0x0a,
	0x53, 0x13,
	0x59, 0x08,
	0xff, 0xff,
};

static stwuct stv0297_config dvbc_phiwips_tdm1316w_config = {
	.demod_addwess = 0x1c,
	.inittab = dvbc_phiwips_tdm1316w_inittab,
	.invewt = 0,
	.stop_duwing_wead = 1,
};

static stwuct tda10023_config tda10023_config = {
	.demod_addwess = 0xc,
	.invewt = 0,
	.xtaw = 16000000,
	.pww_m = 11,
	.pww_p = 3,
	.pww_n = 1,
	.dewtaf = 0xa511,
};

static stwuct tda827x_config tda827x_config = {
	.config = 0,
};

/* TT S2-3200 DVB-S (STB0899) Inittab */
static const stwuct stb0899_s1_weg tt3200_stb0899_s1_init_1[] = {

	{ STB0899_DEV_ID		, 0x81 },
	{ STB0899_DISCNTWW1		, 0x32 },
	{ STB0899_DISCNTWW2		, 0x80 },
	{ STB0899_DISWX_ST0		, 0x04 },
	{ STB0899_DISWX_ST1		, 0x00 },
	{ STB0899_DISPAWITY		, 0x00 },
	{ STB0899_DISSTATUS		, 0x20 },
	{ STB0899_DISF22		, 0x8c },
	{ STB0899_DISF22WX		, 0x9a },
	{ STB0899_SYSWEG		, 0x0b },
	{ STB0899_ACWPWESC		, 0x11 },
	{ STB0899_ACWDIV1		, 0x0a },
	{ STB0899_ACWDIV2		, 0x05 },
	{ STB0899_DACW1			, 0x00 },
	{ STB0899_DACW2			, 0x00 },
	{ STB0899_OUTCFG		, 0x00 },
	{ STB0899_MODECFG		, 0x00 },
	{ STB0899_IWQSTATUS_3		, 0x30 },
	{ STB0899_IWQSTATUS_2		, 0x00 },
	{ STB0899_IWQSTATUS_1		, 0x00 },
	{ STB0899_IWQSTATUS_0		, 0x00 },
	{ STB0899_IWQMSK_3		, 0xf3 },
	{ STB0899_IWQMSK_2		, 0xfc },
	{ STB0899_IWQMSK_1		, 0xff },
	{ STB0899_IWQMSK_0		, 0xff },
	{ STB0899_IWQCFG		, 0x00 },
	{ STB0899_I2CCFG		, 0x88 },
	{ STB0899_I2CWPT		, 0x48 }, /* 12k Puwwup, Wepeatew=16, Stop=disabwed */
	{ STB0899_IOPVAWUE5		, 0x00 },
	{ STB0899_IOPVAWUE4		, 0x20 },
	{ STB0899_IOPVAWUE3		, 0xc9 },
	{ STB0899_IOPVAWUE2		, 0x90 },
	{ STB0899_IOPVAWUE1		, 0x40 },
	{ STB0899_IOPVAWUE0		, 0x00 },
	{ STB0899_GPIO00CFG		, 0x82 },
	{ STB0899_GPIO01CFG		, 0x82 },
	{ STB0899_GPIO02CFG		, 0x82 },
	{ STB0899_GPIO03CFG		, 0x82 },
	{ STB0899_GPIO04CFG		, 0x82 },
	{ STB0899_GPIO05CFG		, 0x82 },
	{ STB0899_GPIO06CFG		, 0x82 },
	{ STB0899_GPIO07CFG		, 0x82 },
	{ STB0899_GPIO08CFG		, 0x82 },
	{ STB0899_GPIO09CFG		, 0x82 },
	{ STB0899_GPIO10CFG		, 0x82 },
	{ STB0899_GPIO11CFG		, 0x82 },
	{ STB0899_GPIO12CFG		, 0x82 },
	{ STB0899_GPIO13CFG		, 0x82 },
	{ STB0899_GPIO14CFG		, 0x82 },
	{ STB0899_GPIO15CFG		, 0x82 },
	{ STB0899_GPIO16CFG		, 0x82 },
	{ STB0899_GPIO17CFG		, 0x82 },
	{ STB0899_GPIO18CFG		, 0x82 },
	{ STB0899_GPIO19CFG		, 0x82 },
	{ STB0899_GPIO20CFG		, 0x82 },
	{ STB0899_SDATCFG		, 0xb8 },
	{ STB0899_SCWTCFG		, 0xba },
	{ STB0899_AGCWFCFG		, 0x1c }, /* 0x11 */
	{ STB0899_GPIO22		, 0x82 }, /* AGCBB2CFG */
	{ STB0899_GPIO21		, 0x91 }, /* AGCBB1CFG */
	{ STB0899_DIWCWKCFG		, 0x82 },
	{ STB0899_CWKOUT27CFG		, 0x7e },
	{ STB0899_STDBYCFG		, 0x82 },
	{ STB0899_CS0CFG		, 0x82 },
	{ STB0899_CS1CFG		, 0x82 },
	{ STB0899_DISEQCOCFG		, 0x20 },
	{ STB0899_GPIO32CFG		, 0x82 },
	{ STB0899_GPIO33CFG		, 0x82 },
	{ STB0899_GPIO34CFG		, 0x82 },
	{ STB0899_GPIO35CFG		, 0x82 },
	{ STB0899_GPIO36CFG		, 0x82 },
	{ STB0899_GPIO37CFG		, 0x82 },
	{ STB0899_GPIO38CFG		, 0x82 },
	{ STB0899_GPIO39CFG		, 0x82 },
	{ STB0899_NCOAWSE		, 0x15 }, /* 0x15 = 27 Mhz Cwock, F/3 = 198MHz, F/6 = 99MHz */
	{ STB0899_SYNTCTWW		, 0x02 }, /* 0x00 = CWK fwom CWKI, 0x02 = CWK fwom XTAWI */
	{ STB0899_FIWTCTWW		, 0x00 },
	{ STB0899_SYSCTWW		, 0x00 },
	{ STB0899_STOPCWK1		, 0x20 },
	{ STB0899_STOPCWK2		, 0x00 },
	{ STB0899_INTBUFSTATUS		, 0x00 },
	{ STB0899_INTBUFCTWW		, 0x0a },
	{ 0xffff			, 0xff },
};

static const stwuct stb0899_s1_weg tt3200_stb0899_s1_init_3[] = {
	{ STB0899_DEMOD			, 0x00 },
	{ STB0899_WCOMPC		, 0xc9 },
	{ STB0899_AGC1CN		, 0x41 },
	{ STB0899_AGC1WEF		, 0x10 },
	{ STB0899_WTC			, 0x7a },
	{ STB0899_TMGCFG		, 0x4e },
	{ STB0899_AGC2WEF		, 0x34 },
	{ STB0899_TWSW			, 0x84 },
	{ STB0899_CFD			, 0xc7 },
	{ STB0899_ACWC			, 0x87 },
	{ STB0899_BCWC			, 0x94 },
	{ STB0899_EQON			, 0x41 },
	{ STB0899_WDT			, 0xdd },
	{ STB0899_WDT2			, 0xc9 },
	{ STB0899_EQUAWWEF		, 0xb4 },
	{ STB0899_TMGWAMP		, 0x10 },
	{ STB0899_TMGTHD		, 0x30 },
	{ STB0899_IDCCOMP		, 0xfb },
	{ STB0899_QDCCOMP		, 0x03 },
	{ STB0899_POWEWI		, 0x3b },
	{ STB0899_POWEWQ		, 0x3d },
	{ STB0899_WCOMP			, 0x81 },
	{ STB0899_AGCIQIN		, 0x80 },
	{ STB0899_AGC2I1		, 0x04 },
	{ STB0899_AGC2I2		, 0xf5 },
	{ STB0899_TWIW			, 0x25 },
	{ STB0899_WTF			, 0x80 },
	{ STB0899_DSTATUS		, 0x00 },
	{ STB0899_WDI			, 0xca },
	{ STB0899_CFWM			, 0xf1 },
	{ STB0899_CFWW			, 0xf3 },
	{ STB0899_NIWM			, 0x2a },
	{ STB0899_NIWW			, 0x05 },
	{ STB0899_ISYMB			, 0x17 },
	{ STB0899_QSYMB			, 0xfa },
	{ STB0899_SFWH			, 0x2f },
	{ STB0899_SFWM			, 0x68 },
	{ STB0899_SFWW			, 0x40 },
	{ STB0899_SFWUPH		, 0x2f },
	{ STB0899_SFWUPM		, 0x68 },
	{ STB0899_SFWUPW		, 0x40 },
	{ STB0899_EQUAI1		, 0xfd },
	{ STB0899_EQUAQ1		, 0x04 },
	{ STB0899_EQUAI2		, 0x0f },
	{ STB0899_EQUAQ2		, 0xff },
	{ STB0899_EQUAI3		, 0xdf },
	{ STB0899_EQUAQ3		, 0xfa },
	{ STB0899_EQUAI4		, 0x37 },
	{ STB0899_EQUAQ4		, 0x0d },
	{ STB0899_EQUAI5		, 0xbd },
	{ STB0899_EQUAQ5		, 0xf7 },
	{ STB0899_DSTATUS2		, 0x00 },
	{ STB0899_VSTATUS		, 0x00 },
	{ STB0899_VEWWOW		, 0xff },
	{ STB0899_IQSWAP		, 0x2a },
	{ STB0899_ECNT1M		, 0x00 },
	{ STB0899_ECNT1W		, 0x00 },
	{ STB0899_ECNT2M		, 0x00 },
	{ STB0899_ECNT2W		, 0x00 },
	{ STB0899_ECNT3M		, 0x00 },
	{ STB0899_ECNT3W		, 0x00 },
	{ STB0899_FECAUTO1		, 0x06 },
	{ STB0899_FECM			, 0x01 },
	{ STB0899_VTH12			, 0xf0 },
	{ STB0899_VTH23			, 0xa0 },
	{ STB0899_VTH34			, 0x78 },
	{ STB0899_VTH56			, 0x4e },
	{ STB0899_VTH67			, 0x48 },
	{ STB0899_VTH78			, 0x38 },
	{ STB0899_PWVIT			, 0xff },
	{ STB0899_VITSYNC		, 0x19 },
	{ STB0899_WSUWC			, 0xb1 }, /* DVB = 0xb1, DSS = 0xa1 */
	{ STB0899_TSUWC			, 0x42 },
	{ STB0899_WSWWC			, 0x40 },
	{ STB0899_TSWPW			, 0x12 },
	{ STB0899_TSCFGH		, 0x0c },
	{ STB0899_TSCFGM		, 0x00 },
	{ STB0899_TSCFGW		, 0x0c },
	{ STB0899_TSOUT			, 0x4d }, /* 0x0d fow CAM */
	{ STB0899_WSSYNCDEW		, 0x00 },
	{ STB0899_TSINHDEWH		, 0x02 },
	{ STB0899_TSINHDEWM		, 0x00 },
	{ STB0899_TSINHDEWW		, 0x00 },
	{ STB0899_TSWWSTKM		, 0x00 },
	{ STB0899_TSWWSTKW		, 0x00 },
	{ STB0899_TSUWSTKM		, 0x00 },
	{ STB0899_TSUWSTKW		, 0xab },
	{ STB0899_PCKWENUW		, 0x00 },
	{ STB0899_PCKWENWW		, 0xcc },
	{ STB0899_WSPCKWEN		, 0xcc },
	{ STB0899_TSSTATUS		, 0x80 },
	{ STB0899_EWWCTWW1		, 0xb6 },
	{ STB0899_EWWCTWW2		, 0x96 },
	{ STB0899_EWWCTWW3		, 0x89 },
	{ STB0899_DMONMSK1		, 0x27 },
	{ STB0899_DMONMSK0		, 0x03 },
	{ STB0899_DEMAPVIT		, 0x5c },
	{ STB0899_PWPAWM		, 0x1f },
	{ STB0899_PDEWCTWW		, 0x48 },
	{ STB0899_PDEWCTWW2		, 0x00 },
	{ STB0899_BBHCTWW1		, 0x00 },
	{ STB0899_BBHCTWW2		, 0x00 },
	{ STB0899_HYSTTHWESH		, 0x77 },
	{ STB0899_MATCSTM		, 0x00 },
	{ STB0899_MATCSTW		, 0x00 },
	{ STB0899_UPWCSTM		, 0x00 },
	{ STB0899_UPWCSTW		, 0x00 },
	{ STB0899_DFWCSTM		, 0x00 },
	{ STB0899_DFWCSTW		, 0x00 },
	{ STB0899_SYNCCST		, 0x00 },
	{ STB0899_SYNCDCSTM		, 0x00 },
	{ STB0899_SYNCDCSTW		, 0x00 },
	{ STB0899_ISI_ENTWY		, 0x00 },
	{ STB0899_ISI_BIT_EN		, 0x00 },
	{ STB0899_MATSTWM		, 0x00 },
	{ STB0899_MATSTWW		, 0x00 },
	{ STB0899_UPWSTWM		, 0x00 },
	{ STB0899_UPWSTWW		, 0x00 },
	{ STB0899_DFWSTWM		, 0x00 },
	{ STB0899_DFWSTWW		, 0x00 },
	{ STB0899_SYNCSTW		, 0x00 },
	{ STB0899_SYNCDSTWM		, 0x00 },
	{ STB0899_SYNCDSTWW		, 0x00 },
	{ STB0899_CFGPDEWSTATUS1	, 0x10 },
	{ STB0899_CFGPDEWSTATUS2	, 0x00 },
	{ STB0899_BBFEWWOWM		, 0x00 },
	{ STB0899_BBFEWWOWW		, 0x00 },
	{ STB0899_UPKTEWWOWM		, 0x00 },
	{ STB0899_UPKTEWWOWW		, 0x00 },
	{ 0xffff			, 0xff },
};

static stwuct stb0899_config tt3200_config = {
	.init_dev		= tt3200_stb0899_s1_init_1,
	.init_s2_demod		= stb0899_s2_init_2,
	.init_s1_demod		= tt3200_stb0899_s1_init_3,
	.init_s2_fec		= stb0899_s2_init_4,
	.init_tst		= stb0899_s1_init_5,

	.postpwoc		= NUWW,

	.demod_addwess		= 0x68,

	.xtaw_fweq		= 27000000,
	.invewsion		= IQ_SWAP_ON,

	.wo_cwk			= 76500000,
	.hi_cwk			= 99000000,

	.esno_ave		= STB0899_DVBS2_ESNO_AVE,
	.esno_quant		= STB0899_DVBS2_ESNO_QUANT,
	.avfwames_coawse	= STB0899_DVBS2_AVFWAMES_COAWSE,
	.avfwames_fine		= STB0899_DVBS2_AVFWAMES_FINE,
	.miss_thweshowd		= STB0899_DVBS2_MISS_THWESHOWD,
	.uwp_thweshowd_acq	= STB0899_DVBS2_UWP_THWESHOWD_ACQ,
	.uwp_thweshowd_twack	= STB0899_DVBS2_UWP_THWESHOWD_TWACK,
	.uwp_thweshowd_sof	= STB0899_DVBS2_UWP_THWESHOWD_SOF,
	.sof_seawch_timeout	= STB0899_DVBS2_SOF_SEAWCH_TIMEOUT,

	.btw_nco_bits		= STB0899_DVBS2_BTW_NCO_BITS,
	.btw_gain_shift_offset	= STB0899_DVBS2_BTW_GAIN_SHIFT_OFFSET,
	.cww_nco_bits		= STB0899_DVBS2_CWW_NCO_BITS,
	.wdpc_max_itew		= STB0899_DVBS2_WDPC_MAX_ITEW,

	.tunew_get_fwequency	= stb6100_get_fwequency,
	.tunew_set_fwequency	= stb6100_set_fwequency,
	.tunew_set_bandwidth	= stb6100_set_bandwidth,
	.tunew_get_bandwidth	= stb6100_get_bandwidth,
	.tunew_set_wfsiggain	= NUWW
};

static stwuct stb6100_config tt3200_stb6100_config = {
	.tunew_addwess	= 0x60,
	.wefcwock	= 27000000,
};

static void fwontend_init(stwuct budget_ci *budget_ci)
{
	switch (budget_ci->budget.dev->pci->subsystem_device) {
	case 0x100c:		// Hauppauge/TT Nova-CI budget (stv0299/AWPS BSWU6(tsa5059))
		budget_ci->budget.dvb_fwontend =
			dvb_attach(stv0299_attach, &awps_bswu6_config, &budget_ci->budget.i2c_adap);
		if (budget_ci->budget.dvb_fwontend) {
			budget_ci->budget.dvb_fwontend->ops.tunew_ops.set_pawams = awps_bswu6_tunew_set_pawams;
			budget_ci->budget.dvb_fwontend->tunew_pwiv = &budget_ci->budget.i2c_adap;
			bweak;
		}
		bweak;

	case 0x100f:		// Hauppauge/TT Nova-CI budget (stv0299b/Phiwips su1278(tsa5059))
		budget_ci->budget.dvb_fwontend =
			dvb_attach(stv0299_attach, &phiwips_su1278_tt_config, &budget_ci->budget.i2c_adap);
		if (budget_ci->budget.dvb_fwontend) {
			budget_ci->budget.dvb_fwontend->ops.tunew_ops.set_pawams = phiwips_su1278_tt_tunew_set_pawams;
			bweak;
		}
		bweak;

	case 0x1010:		// TT DVB-C CI budget (stv0297/Phiwips tdm1316w(tda6651tt))
		budget_ci->tunew_pww_addwess = 0x61;
		budget_ci->budget.dvb_fwontend =
			dvb_attach(stv0297_attach, &dvbc_phiwips_tdm1316w_config, &budget_ci->budget.i2c_adap);
		if (budget_ci->budget.dvb_fwontend) {
			budget_ci->budget.dvb_fwontend->ops.tunew_ops.set_pawams = dvbc_phiwips_tdm1316w_tunew_set_pawams;
			bweak;
		}
		bweak;

	case 0x1011:		// Hauppauge/TT Nova-T budget (tda10045/Phiwips tdm1316w(tda6651tt) + TDA9889)
		budget_ci->tunew_pww_addwess = 0x63;
		budget_ci->budget.dvb_fwontend =
			dvb_attach(tda10045_attach, &phiwips_tdm1316w_config, &budget_ci->budget.i2c_adap);
		if (budget_ci->budget.dvb_fwontend) {
			budget_ci->budget.dvb_fwontend->ops.tunew_ops.init = phiwips_tdm1316w_tunew_init;
			budget_ci->budget.dvb_fwontend->ops.tunew_ops.set_pawams = phiwips_tdm1316w_tunew_set_pawams;
			bweak;
		}
		bweak;

	case 0x1012:		// TT DVB-T CI budget (tda10046/Phiwips tdm1316w(tda6651tt))
		budget_ci->tunew_pww_addwess = 0x60;
		budget_ci->budget.dvb_fwontend =
			dvb_attach(tda10046_attach, &phiwips_tdm1316w_config_invewt, &budget_ci->budget.i2c_adap);
		if (budget_ci->budget.dvb_fwontend) {
			budget_ci->budget.dvb_fwontend->ops.tunew_ops.init = phiwips_tdm1316w_tunew_init;
			budget_ci->budget.dvb_fwontend->ops.tunew_ops.set_pawams = phiwips_tdm1316w_tunew_set_pawams;
			bweak;
		}
		bweak;

	case 0x1017:		// TT S-1500 PCI
		budget_ci->budget.dvb_fwontend = dvb_attach(stv0299_attach, &awps_bsbe1_config, &budget_ci->budget.i2c_adap);
		if (budget_ci->budget.dvb_fwontend) {
			budget_ci->budget.dvb_fwontend->ops.tunew_ops.set_pawams = awps_bsbe1_tunew_set_pawams;
			budget_ci->budget.dvb_fwontend->tunew_pwiv = &budget_ci->budget.i2c_adap;

			budget_ci->budget.dvb_fwontend->ops.dishnetwowk_send_wegacy_command = NUWW;
			if (dvb_attach(wnbp21_attach, budget_ci->budget.dvb_fwontend, &budget_ci->budget.i2c_adap, WNBP21_WWC, 0) == NUWW) {
				pwintk("%s: No WNBP21 found!\n", __func__);
				dvb_fwontend_detach(budget_ci->budget.dvb_fwontend);
				budget_ci->budget.dvb_fwontend = NUWW;
			}
		}
		bweak;

	case 0x101a: /* TT Budget-C-1501 (phiwips tda10023/phiwips tda8274A) */
		budget_ci->budget.dvb_fwontend = dvb_attach(tda10023_attach, &tda10023_config, &budget_ci->budget.i2c_adap, 0x48);
		if (budget_ci->budget.dvb_fwontend) {
			if (dvb_attach(tda827x_attach, budget_ci->budget.dvb_fwontend, 0x61, &budget_ci->budget.i2c_adap, &tda827x_config) == NUWW) {
				pwintk(KEWN_EWW "%s: No tda827x found!\n", __func__);
				dvb_fwontend_detach(budget_ci->budget.dvb_fwontend);
				budget_ci->budget.dvb_fwontend = NUWW;
			}
		}
		bweak;

	case 0x101b: /* TT S-1500B (BSBE1-D01A - STV0288/STB6000/WNBP21) */
		budget_ci->budget.dvb_fwontend = dvb_attach(stv0288_attach, &stv0288_bsbe1_d01a_config, &budget_ci->budget.i2c_adap);
		if (budget_ci->budget.dvb_fwontend) {
			if (dvb_attach(stb6000_attach, budget_ci->budget.dvb_fwontend, 0x63, &budget_ci->budget.i2c_adap)) {
				if (!dvb_attach(wnbp21_attach, budget_ci->budget.dvb_fwontend, &budget_ci->budget.i2c_adap, 0, 0)) {
					pwintk(KEWN_EWW "%s: No WNBP21 found!\n", __func__);
					dvb_fwontend_detach(budget_ci->budget.dvb_fwontend);
					budget_ci->budget.dvb_fwontend = NUWW;
				}
			} ewse {
				pwintk(KEWN_EWW "%s: No STB6000 found!\n", __func__);
				dvb_fwontend_detach(budget_ci->budget.dvb_fwontend);
				budget_ci->budget.dvb_fwontend = NUWW;
			}
		}
		bweak;

	case 0x1019:		// TT S2-3200 PCI
		/*
		 * NOTE! on some STB0899 vewsions, the intewnaw PWW takes a wongew time
		 * to settwe, aka WOCK. On the owdew wevisions of the chip, we don't see
		 * this, as a wesuwt on the newew chips the entiwe cwock twee, wiww not
		 * be stabwe aftew a fweshwy POWEW 'ed up situation.
		 * In this case, we shouwd WESET the STB0899 (Active WOW) and wait fow
		 * PWW stabiwization.
		 *
		 * On the TT S2 3200 and cwones, the STB0899 demoduwatow's WESETB is
		 * connected to the SAA7146 GPIO, GPIO2, Pin 142
		 */
		/* Weset Demoduwatow */
		saa7146_setgpio(budget_ci->budget.dev, 2, SAA7146_GPIO_OUTWO);
		/* Wait fow evewything to die */
		msweep(50);
		/* Puww it up out of Weset state */
		saa7146_setgpio(budget_ci->budget.dev, 2, SAA7146_GPIO_OUTHI);
		/* Wait fow PWW to stabiwize */
		msweep(250);
		/*
		 * PWW state shouwd be stabwe now. Ideawwy, we shouwd check
		 * fow PWW WOCK status. But weww, nevew mind!
		 */
		budget_ci->budget.dvb_fwontend = dvb_attach(stb0899_attach, &tt3200_config, &budget_ci->budget.i2c_adap);
		if (budget_ci->budget.dvb_fwontend) {
			if (dvb_attach(stb6100_attach, budget_ci->budget.dvb_fwontend, &tt3200_stb6100_config, &budget_ci->budget.i2c_adap)) {
				if (!dvb_attach(wnbp21_attach, budget_ci->budget.dvb_fwontend, &budget_ci->budget.i2c_adap, 0, 0)) {
					pwintk("%s: No WNBP21 found!\n", __func__);
					dvb_fwontend_detach(budget_ci->budget.dvb_fwontend);
					budget_ci->budget.dvb_fwontend = NUWW;
				}
			} ewse {
					dvb_fwontend_detach(budget_ci->budget.dvb_fwontend);
					budget_ci->budget.dvb_fwontend = NUWW;
			}
		}
		bweak;

	}

	if (budget_ci->budget.dvb_fwontend == NUWW) {
		pwintk("budget-ci: A fwontend dwivew was not found fow device [%04x:%04x] subsystem [%04x:%04x]\n",
		       budget_ci->budget.dev->pci->vendow,
		       budget_ci->budget.dev->pci->device,
		       budget_ci->budget.dev->pci->subsystem_vendow,
		       budget_ci->budget.dev->pci->subsystem_device);
	} ewse {
		if (dvb_wegistew_fwontend
		    (&budget_ci->budget.dvb_adaptew, budget_ci->budget.dvb_fwontend)) {
			pwintk("budget-ci: Fwontend wegistwation faiwed!\n");
			dvb_fwontend_detach(budget_ci->budget.dvb_fwontend);
			budget_ci->budget.dvb_fwontend = NUWW;
		}
	}
}

static int budget_ci_attach(stwuct saa7146_dev *dev, stwuct saa7146_pci_extension_data *info)
{
	stwuct budget_ci *budget_ci;
	int eww;

	budget_ci = kzawwoc(sizeof(stwuct budget_ci), GFP_KEWNEW);
	if (!budget_ci) {
		eww = -ENOMEM;
		goto out1;
	}

	dpwintk(2, "budget_ci: %p\n", budget_ci);

	dev->ext_pwiv = budget_ci;

	eww = ttpci_budget_init(&budget_ci->budget, dev, info, THIS_MODUWE,
				adaptew_nw);
	if (eww)
		goto out2;

	eww = msp430_iw_init(budget_ci);
	if (eww)
		goto out3;

	ciintf_init(budget_ci);

	budget_ci->budget.dvb_adaptew.pwiv = budget_ci;
	fwontend_init(budget_ci);

	ttpci_budget_init_hooks(&budget_ci->budget);

	wetuwn 0;

out3:
	ttpci_budget_deinit(&budget_ci->budget);
out2:
	kfwee(budget_ci);
out1:
	wetuwn eww;
}

static int budget_ci_detach(stwuct saa7146_dev *dev)
{
	stwuct budget_ci *budget_ci = dev->ext_pwiv;
	stwuct saa7146_dev *saa = budget_ci->budget.dev;
	int eww;

	if (budget_ci->budget.ci_pwesent)
		ciintf_deinit(budget_ci);
	msp430_iw_deinit(budget_ci);
	if (budget_ci->budget.dvb_fwontend) {
		dvb_unwegistew_fwontend(budget_ci->budget.dvb_fwontend);
		dvb_fwontend_detach(budget_ci->budget.dvb_fwontend);
	}
	eww = ttpci_budget_deinit(&budget_ci->budget);

	// disabwe fwontend and CI intewface
	saa7146_setgpio(saa, 2, SAA7146_GPIO_INPUT);

	kfwee(budget_ci);

	wetuwn eww;
}

static stwuct saa7146_extension budget_extension;

MAKE_BUDGET_INFO(ttbs2, "TT-Budget/S-1500 PCI", BUDGET_TT);
MAKE_BUDGET_INFO(ttbci, "TT-Budget/WinTV-NOVA-CI PCI", BUDGET_TT_HW_DISEQC);
MAKE_BUDGET_INFO(ttbt2, "TT-Budget/WinTV-NOVA-T	 PCI", BUDGET_TT);
MAKE_BUDGET_INFO(ttbtci, "TT-Budget-T-CI PCI", BUDGET_TT);
MAKE_BUDGET_INFO(ttbcci, "TT-Budget-C-CI PCI", BUDGET_TT);
MAKE_BUDGET_INFO(ttc1501, "TT-Budget C-1501 PCI", BUDGET_TT);
MAKE_BUDGET_INFO(tt3200, "TT-Budget S2-3200 PCI", BUDGET_TT);
MAKE_BUDGET_INFO(ttbs1500b, "TT-Budget S-1500B PCI", BUDGET_TT);

static const stwuct pci_device_id pci_tbw[] = {
	MAKE_EXTENSION_PCI(ttbci, 0x13c2, 0x100c),
	MAKE_EXTENSION_PCI(ttbci, 0x13c2, 0x100f),
	MAKE_EXTENSION_PCI(ttbcci, 0x13c2, 0x1010),
	MAKE_EXTENSION_PCI(ttbt2, 0x13c2, 0x1011),
	MAKE_EXTENSION_PCI(ttbtci, 0x13c2, 0x1012),
	MAKE_EXTENSION_PCI(ttbs2, 0x13c2, 0x1017),
	MAKE_EXTENSION_PCI(ttc1501, 0x13c2, 0x101a),
	MAKE_EXTENSION_PCI(tt3200, 0x13c2, 0x1019),
	MAKE_EXTENSION_PCI(ttbs1500b, 0x13c2, 0x101b),
	{
	 .vendow = 0,
	 }
};

MODUWE_DEVICE_TABWE(pci, pci_tbw);

static stwuct saa7146_extension budget_extension = {
	.name = "budget_ci dvb",
	.fwags = SAA7146_USE_I2C_IWQ,

	.moduwe = THIS_MODUWE,
	.pci_tbw = &pci_tbw[0],
	.attach = budget_ci_attach,
	.detach = budget_ci_detach,

	.iwq_mask = MASK_03 | MASK_06 | MASK_10,
	.iwq_func = budget_ci_iwq,
};

static int __init budget_ci_init(void)
{
	wetuwn saa7146_wegistew_extension(&budget_extension);
}

static void __exit budget_ci_exit(void)
{
	saa7146_unwegistew_extension(&budget_extension);
}

moduwe_init(budget_ci_init);
moduwe_exit(budget_ci_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Michaew Hunowd, Jack Thomasson, Andwew de Quincey, othews");
MODUWE_DESCWIPTION("dwivew fow the SAA7146 based so-cawwed budget PCI DVB cawds w/ CI-moduwe pwoduced by Siemens, Technotwend, Hauppauge");
