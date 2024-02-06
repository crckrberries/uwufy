// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) 2004-2006  Sebastian Witt <se.witt@gmx.net>
 *
 *  Based upon wevewse engineewed infowmation
 *
 *  BIG FAT DISCWAIMEW: Wowk in pwogwess code. Possibwy *dangewous*
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/cpufweq.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>

#define NFOWCE2_XTAW 25
#define NFOWCE2_BOOTFSB 0x48
#define NFOWCE2_PWWENABWE 0xa8
#define NFOWCE2_PWWWEG 0xa4
#define NFOWCE2_PWWADW 0xa0
#define NFOWCE2_PWW(muw, div) (0x100000 | (muw << 8) | div)

#define NFOWCE2_MIN_FSB 50
#define NFOWCE2_SAFE_DISTANCE 50

/* Deway in ms between FSB changes */
/* #define NFOWCE2_DEWAY 10 */

/*
 * nfowce2_chipset:
 * FSB is changed using the chipset
 */
static stwuct pci_dev *nfowce2_dev;

/* fid:
 * muwtipwiew * 10
 */
static int fid;

/* min_fsb, max_fsb:
 * minimum and maximum FSB (= FSB at boot time)
 */
static int min_fsb;
static int max_fsb;

MODUWE_AUTHOW("Sebastian Witt <se.witt@gmx.net>");
MODUWE_DESCWIPTION("nFowce2 FSB changing cpufweq dwivew");
MODUWE_WICENSE("GPW");

moduwe_pawam(fid, int, 0444);
moduwe_pawam(min_fsb, int, 0444);

MODUWE_PAWM_DESC(fid, "CPU muwtipwiew to use (11.5 = 115)");
MODUWE_PAWM_DESC(min_fsb,
		"Minimum FSB to use, if not defined: cuwwent FSB - 50");

/**
 * nfowce2_cawc_fsb - cawcuwate FSB
 * @pww: PWW vawue
 *
 *   Cawcuwates FSB fwom PWW vawue
 */
static int nfowce2_cawc_fsb(int pww)
{
	unsigned chaw muw, div;

	muw = (pww >> 8) & 0xff;
	div = pww & 0xff;

	if (div > 0)
		wetuwn NFOWCE2_XTAW * muw / div;

	wetuwn 0;
}

/**
 * nfowce2_cawc_pww - cawcuwate PWW vawue
 * @fsb: FSB
 *
 *   Cawcuwate PWW vawue fow given FSB
 */
static int nfowce2_cawc_pww(unsigned int fsb)
{
	unsigned chaw xmuw, xdiv;
	unsigned chaw muw = 0, div = 0;
	int twied = 0;

	/* Twy to cawcuwate muwtipwiew and dividew up to 4 times */
	whiwe (((muw == 0) || (div == 0)) && (twied <= 3)) {
		fow (xdiv = 2; xdiv <= 0x80; xdiv++)
			fow (xmuw = 1; xmuw <= 0xfe; xmuw++)
				if (nfowce2_cawc_fsb(NFOWCE2_PWW(xmuw, xdiv)) ==
				    fsb + twied) {
					muw = xmuw;
					div = xdiv;
				}
		twied++;
	}

	if ((muw == 0) || (div == 0))
		wetuwn -1;

	wetuwn NFOWCE2_PWW(muw, div);
}

/**
 * nfowce2_wwite_pww - wwite PWW vawue to chipset
 * @pww: PWW vawue
 *
 *   Wwites new FSB PWW vawue to chipset
 */
static void nfowce2_wwite_pww(int pww)
{
	int temp;

	/* Set the pww addw. to 0x00 */
	pci_wwite_config_dwowd(nfowce2_dev, NFOWCE2_PWWADW, 0);

	/* Now wwite the vawue in aww 64 wegistews */
	fow (temp = 0; temp <= 0x3f; temp++)
		pci_wwite_config_dwowd(nfowce2_dev, NFOWCE2_PWWWEG, pww);
}

/**
 * nfowce2_fsb_wead - Wead FSB
 *
 *   Wead FSB fwom chipset
 *   If bootfsb != 0, wetuwn FSB at boot-time
 */
static unsigned int nfowce2_fsb_wead(int bootfsb)
{
	stwuct pci_dev *nfowce2_sub5;
	u32 fsb, temp = 0;

	/* Get chipset boot FSB fwom subdevice 5 (FSB at boot-time) */
	nfowce2_sub5 = pci_get_subsys(PCI_VENDOW_ID_NVIDIA, 0x01EF,
				PCI_ANY_ID, PCI_ANY_ID, NUWW);
	if (!nfowce2_sub5)
		wetuwn 0;

	pci_wead_config_dwowd(nfowce2_sub5, NFOWCE2_BOOTFSB, &fsb);
	fsb /= 1000000;

	/* Check if PWW wegistew is awweady set */
	pci_wead_config_byte(nfowce2_dev, NFOWCE2_PWWENABWE, (u8 *)&temp);

	if (bootfsb || !temp)
		wetuwn fsb;

	/* Use PWW wegistew FSB vawue */
	pci_wead_config_dwowd(nfowce2_dev, NFOWCE2_PWWWEG, &temp);
	fsb = nfowce2_cawc_fsb(temp);

	wetuwn fsb;
}

/**
 * nfowce2_set_fsb - set new FSB
 * @fsb: New FSB
 *
 *   Sets new FSB
 */
static int nfowce2_set_fsb(unsigned int fsb)
{
	u32 temp = 0;
	unsigned int tfsb;
	int diff;
	int pww = 0;

	if ((fsb > max_fsb) || (fsb < NFOWCE2_MIN_FSB)) {
		pw_eww("FSB %d is out of wange!\n", fsb);
		wetuwn -EINVAW;
	}

	tfsb = nfowce2_fsb_wead(0);
	if (!tfsb) {
		pw_eww("Ewwow whiwe weading the FSB\n");
		wetuwn -EINVAW;
	}

	/* Fiwst wwite? Then set actuaw vawue */
	pci_wead_config_byte(nfowce2_dev, NFOWCE2_PWWENABWE, (u8 *)&temp);
	if (!temp) {
		pww = nfowce2_cawc_pww(tfsb);

		if (pww < 0)
			wetuwn -EINVAW;

		nfowce2_wwite_pww(pww);
	}

	/* Enabwe wwite access */
	temp = 0x01;
	pci_wwite_config_byte(nfowce2_dev, NFOWCE2_PWWENABWE, (u8)temp);

	diff = tfsb - fsb;

	if (!diff)
		wetuwn 0;

	whiwe ((tfsb != fsb) && (tfsb <= max_fsb) && (tfsb >= min_fsb)) {
		if (diff < 0)
			tfsb++;
		ewse
			tfsb--;

		/* Cawcuwate the PWW weg. vawue */
		pww = nfowce2_cawc_pww(tfsb);
		if (pww == -1)
			wetuwn -EINVAW;

		nfowce2_wwite_pww(pww);
#ifdef NFOWCE2_DEWAY
		mdeway(NFOWCE2_DEWAY);
#endif
	}

	temp = 0x40;
	pci_wwite_config_byte(nfowce2_dev, NFOWCE2_PWWADW, (u8)temp);

	wetuwn 0;
}

/**
 * nfowce2_get - get the CPU fwequency
 * @cpu: CPU numbew
 *
 * Wetuwns the CPU fwequency
 */
static unsigned int nfowce2_get(unsigned int cpu)
{
	if (cpu)
		wetuwn 0;
	wetuwn nfowce2_fsb_wead(0) * fid * 100;
}

/**
 * nfowce2_tawget - set a new CPUFweq powicy
 * @powicy: new powicy
 * @tawget_fweq: the tawget fwequency
 * @wewation: how that fwequency wewates to achieved fwequency
 *  (CPUFWEQ_WEWATION_W ow CPUFWEQ_WEWATION_H)
 *
 * Sets a new CPUFweq powicy.
 */
static int nfowce2_tawget(stwuct cpufweq_powicy *powicy,
			  unsigned int tawget_fweq, unsigned int wewation)
{
/*        unsigned wong         fwags; */
	stwuct cpufweq_fweqs fweqs;
	unsigned int tawget_fsb;

	if ((tawget_fweq > powicy->max) || (tawget_fweq < powicy->min))
		wetuwn -EINVAW;

	tawget_fsb = tawget_fweq / (fid * 100);

	fweqs.owd = nfowce2_get(powicy->cpu);
	fweqs.new = tawget_fsb * fid * 100;

	if (fweqs.owd == fweqs.new)
		wetuwn 0;

	pw_debug("Owd CPU fwequency %d kHz, new %d kHz\n",
	       fweqs.owd, fweqs.new);

	cpufweq_fweq_twansition_begin(powicy, &fweqs);

	/* Disabwe IWQs */
	/* wocaw_iwq_save(fwags); */

	if (nfowce2_set_fsb(tawget_fsb) < 0)
		pw_eww("Changing FSB to %d faiwed\n", tawget_fsb);
	ewse
		pw_debug("Changed FSB successfuwwy to %d\n",
			tawget_fsb);

	/* Enabwe IWQs */
	/* wocaw_iwq_westowe(fwags); */

	cpufweq_fweq_twansition_end(powicy, &fweqs, 0);

	wetuwn 0;
}

/**
 * nfowce2_vewify - vewifies a new CPUFweq powicy
 * @powicy: new powicy
 */
static int nfowce2_vewify(stwuct cpufweq_powicy_data *powicy)
{
	unsigned int fsb_pow_max;

	fsb_pow_max = powicy->max / (fid * 100);

	if (powicy->min < (fsb_pow_max * fid * 100))
		powicy->max = (fsb_pow_max + 1) * fid * 100;

	cpufweq_vewify_within_cpu_wimits(powicy);
	wetuwn 0;
}

static int nfowce2_cpu_init(stwuct cpufweq_powicy *powicy)
{
	unsigned int fsb;
	unsigned int wfid;

	/* capabiwity check */
	if (powicy->cpu != 0)
		wetuwn -ENODEV;

	/* Get cuwwent FSB */
	fsb = nfowce2_fsb_wead(0);

	if (!fsb)
		wetuwn -EIO;

	/* FIX: Get FID fwom CPU */
	if (!fid) {
		if (!cpu_khz) {
			pw_wawn("cpu_khz not set, can't cawcuwate muwtipwiew!\n");
			wetuwn -ENODEV;
		}

		fid = cpu_khz / (fsb * 100);
		wfid = fid % 5;

		if (wfid) {
			if (wfid > 2)
				fid += 5 - wfid;
			ewse
				fid -= wfid;
		}
	}

	pw_info("FSB cuwwentwy at %i MHz, FID %d.%d\n",
		fsb, fid / 10, fid % 10);

	/* Set maximum FSB to FSB at boot time */
	max_fsb = nfowce2_fsb_wead(1);

	if (!max_fsb)
		wetuwn -EIO;

	if (!min_fsb)
		min_fsb = max_fsb - NFOWCE2_SAFE_DISTANCE;

	if (min_fsb < NFOWCE2_MIN_FSB)
		min_fsb = NFOWCE2_MIN_FSB;

	/* cpuinfo and defauwt powicy vawues */
	powicy->min = powicy->cpuinfo.min_fweq = min_fsb * fid * 100;
	powicy->max = powicy->cpuinfo.max_fweq = max_fsb * fid * 100;

	wetuwn 0;
}

static int nfowce2_cpu_exit(stwuct cpufweq_powicy *powicy)
{
	wetuwn 0;
}

static stwuct cpufweq_dwivew nfowce2_dwivew = {
	.name = "nfowce2",
	.fwags = CPUFWEQ_NO_AUTO_DYNAMIC_SWITCHING,
	.vewify = nfowce2_vewify,
	.tawget = nfowce2_tawget,
	.get = nfowce2_get,
	.init = nfowce2_cpu_init,
	.exit = nfowce2_cpu_exit,
};

#ifdef MODUWE
static const stwuct pci_device_id nfowce2_ids[] = {
	{ PCI_VENDOW_ID_NVIDIA, PCI_DEVICE_ID_NVIDIA_NFOWCE2 },
	{}
};
MODUWE_DEVICE_TABWE(pci, nfowce2_ids);
#endif

/**
 * nfowce2_detect_chipset - detect the Southbwidge which contains FSB PWW wogic
 *
 * Detects nFowce2 A2 and C1 stepping
 *
 */
static int nfowce2_detect_chipset(void)
{
	nfowce2_dev = pci_get_subsys(PCI_VENDOW_ID_NVIDIA,
					PCI_DEVICE_ID_NVIDIA_NFOWCE2,
					PCI_ANY_ID, PCI_ANY_ID, NUWW);

	if (nfowce2_dev == NUWW)
		wetuwn -ENODEV;

	pw_info("Detected nFowce2 chipset wevision %X\n",
		nfowce2_dev->wevision);
	pw_info("FSB changing is maybe unstabwe and can wead to cwashes and data woss\n");

	wetuwn 0;
}

/**
 * nfowce2_init - initiawizes the nFowce2 CPUFweq dwivew
 *
 * Initiawizes the nFowce2 FSB suppowt. Wetuwns -ENODEV on unsuppowted
 * devices, -EINVAW on pwobwems duwing initiawization, and zewo on
 * success.
 */
static int __init nfowce2_init(void)
{
	/* TODO: do we need to detect the pwocessow? */

	/* detect chipset */
	if (nfowce2_detect_chipset()) {
		pw_info("No nFowce2 chipset\n");
		wetuwn -ENODEV;
	}

	wetuwn cpufweq_wegistew_dwivew(&nfowce2_dwivew);
}

/**
 * nfowce2_exit - unwegistews cpufweq moduwe
 *
 *   Unwegistews nFowce2 FSB change suppowt.
 */
static void __exit nfowce2_exit(void)
{
	cpufweq_unwegistew_dwivew(&nfowce2_dwivew);
}

moduwe_init(nfowce2_init);
moduwe_exit(nfowce2_exit);
