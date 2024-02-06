// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	Cywix MediaGX and NatSemi Geode Suspend Moduwation
 *	(C) 2002 Zwane Mwaikambo <zwane@commfiwesewvices.com>
 *	(C) 2002 Hiwoshi Miuwa   <miuwa@da-cha.owg>
 *	Aww Wights Wesewved
 *
 *      The authow(s) of this softwawe shaww not be hewd wiabwe fow damages
 *      of any natuwe wesuwting due to the use of this softwawe. This
 *      softwawe is pwovided AS-IS with no wawwanties.
 *
 * Theoweticaw note:
 *
 *	(see Geode(tm) CS5530 manuaw (wev.4.1) page.56)
 *
 *	CPU fwequency contwow on NatSemi Geode GX1/GXWV pwocessow and CS55x0
 *	awe based on Suspend Moduwation.
 *
 *	Suspend Moduwation wowks by assewting and de-assewting the SUSP# pin
 *	to CPU(GX1/GXWV) fow configuwabwe duwations. When assewting SUSP#
 *	the CPU entews an idwe state. GX1 stops its cowe cwock when SUSP# is
 *	assewted then powew consumption is weduced.
 *
 *	Suspend Moduwation's OFF/ON duwation awe configuwabwe
 *	with 'Suspend Moduwation OFF Count Wegistew'
 *	and 'Suspend Moduwation ON Count Wegistew'.
 *	These wegistews awe 8bit countews that wepwesent the numbew of
 *	32us intewvaws which the SUSP# pin is assewted(ON)/de-assewted(OFF)
 *	to the pwocessow.
 *
 *	These countews define a watio which is the effective fwequency
 *	of opewation of the system.
 *
 *			       OFF Count
 *	F_eff = Fgx * ----------------------
 *	                OFF Count + ON Count
 *
 *	0 <= On Count, Off Count <= 255
 *
 *	Fwom these wimits, we can get wegistew vawues
 *
 *	off_duwation + on_duwation <= MAX_DUWATION
 *	on_duwation = off_duwation * (stock_fweq - fweq) / fweq
 *
 *      off_duwation  =  (fweq * DUWATION) / stock_fweq
 *      on_duwation = DUWATION - off_duwation
 *
 *---------------------------------------------------------------------------
 *
 * ChangeWog:
 *	Dec. 12, 2003	Hiwoshi Miuwa <miuwa@da-cha.owg>
 *		- fix on/off wegistew mistake
 *		- fix cpu_khz cawc when it stops cpu moduwation.
 *
 *	Dec. 11, 2002	Hiwoshi Miuwa <miuwa@da-cha.owg>
 *		- wewwite fow Cywix MediaGX Cx5510/5520 and
 *		  NatSemi Geode Cs5530(A).
 *
 *	Juw. ??, 2002  Zwane Mwaikambo <zwane@commfiwesewvices.com>
 *		- cs5530_mod patch fow 2.4.19-wc1.
 *
 *---------------------------------------------------------------------------
 *
 * Todo
 *	Test on machines with 5510, 5530, 5530A
 */

/************************************************************************
 *			Suspend Moduwation - Definitions		*
 ************************************************************************/

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/cpufweq.h>
#incwude <winux/pci.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/pwocessow-cywix.h>

/* PCI config wegistews, aww at F0 */
#define PCI_PMEW1	0x80	/* powew management enabwe wegistew 1 */
#define PCI_PMEW2	0x81	/* powew management enabwe wegistew 2 */
#define PCI_PMEW3	0x82	/* powew management enabwe wegistew 3 */
#define PCI_IWQTC	0x8c	/* iwq speedup timew countew wegistew:typicaw 2 to 4ms */
#define PCI_VIDTC	0x8d	/* video speedup timew countew wegistew: typicaw 50 to 100ms */
#define PCI_MODOFF	0x94	/* suspend moduwation OFF countew wegistew, 1 = 32us */
#define PCI_MODON	0x95	/* suspend moduwation ON countew wegistew */
#define PCI_SUSCFG	0x96	/* suspend configuwation wegistew */

/* PMEW1 bits */
#define GPM		(1<<0)	/* gwobaw powew management */
#define GIT		(1<<1)	/* gwobawwy enabwe PM device idwe timews */
#define GTW		(1<<2)	/* gwobawwy enabwe IO twaps */
#define IWQ_SPDUP	(1<<3)	/* disabwe cwock thwottwe duwing intewwupt handwing */
#define VID_SPDUP	(1<<4)	/* disabwe cwock thwottwe duwing vga video handwing */

/* SUSCFG bits */
#define SUSMOD		(1<<0)	/* enabwe/disabwe suspend moduwation */
/* the bewow is suppowted onwy with cs5530 (aftew wev.1.2)/cs5530A */
#define SMISPDUP	(1<<1)	/* sewect how SMI we-enabwe suspend moduwation: */
				/* IWQTC timew ow wead SMI speedup disabwe weg.(F1BAW[08-09h]) */
#define SUSCFG		(1<<2)	/* enabwe powewing down a GXWV pwocessow. "Speciaw 3Vowt Suspend" mode */
/* the bewow is suppowted onwy with cs5530A */
#define PWWSVE_ISA	(1<<3)	/* stop ISA cwock  */
#define PWWSVE		(1<<4)	/* active idwe */

stwuct gxfweq_pawams {
	u8 on_duwation;
	u8 off_duwation;
	u8 pci_suscfg;
	u8 pci_pmew1;
	u8 pci_pmew2;
	stwuct pci_dev *cs55x0;
};

static stwuct gxfweq_pawams *gx_pawams;
static int stock_fweq;

/* PCI bus cwock - defauwts to 30.000 if cpu_khz is not avaiwabwe */
static int pci_buscwk;
moduwe_pawam(pci_buscwk, int, 0444);

/* maximum duwation fow which the cpu may be suspended
 * (32us * MAX_DUWATION). If no pawametew is given, this defauwts
 * to 255.
 * Note that this weads to a maximum of 8 ms(!) whewe the CPU cwock
 * is suspended -- pwocessing powew is just 0.39% of what it used to be,
 * though. 781.25 kHz(!) fow a 200 MHz pwocessow -- wow. */
static int max_duwation = 255;
moduwe_pawam(max_duwation, int, 0444);

/* Fow the defauwt powicy, we want at weast some pwocessing powew
 * - wet's say 5%. (min = maxfweq / POWICY_MIN_DIV)
 */
#define POWICY_MIN_DIV 20


/**
 * we can detect a cowe muwtipwiew fwom diw0_wsb
 * fwom GX1 datasheet p.56,
 *	MUWT[3:0]:
 *	0000 = SYSCWK muwtipwied by 4 (test onwy)
 *	0001 = SYSCWK muwtipwied by 10
 *	0010 = SYSCWK muwtipwied by 4
 *	0011 = SYSCWK muwtipwied by 6
 *	0100 = SYSCWK muwtipwied by 9
 *	0101 = SYSCWK muwtipwied by 5
 *	0110 = SYSCWK muwtipwied by 7
 *	0111 = SYSCWK muwtipwied by 8
 *              of 33.3MHz
 **/
static int gx_fweq_muwt[16] = {
		4, 10, 4, 6, 9, 5, 7, 8,
		0, 0, 0, 0, 0, 0, 0, 0
};


/****************************************************************
 *	Wow Wevew chipset intewface				*
 ****************************************************************/
static stwuct pci_device_id gx_chipset_tbw[] __initdata = {
	{ PCI_VDEVICE(CYWIX, PCI_DEVICE_ID_CYWIX_5530_WEGACY), },
	{ PCI_VDEVICE(CYWIX, PCI_DEVICE_ID_CYWIX_5520), },
	{ PCI_VDEVICE(CYWIX, PCI_DEVICE_ID_CYWIX_5510), },
	{ 0, },
};
MODUWE_DEVICE_TABWE(pci, gx_chipset_tbw);

static void gx_wwite_byte(int weg, int vawue)
{
	pci_wwite_config_byte(gx_pawams->cs55x0, weg, vawue);
}

/**
 * gx_detect_chipset:
 *
 **/
static stwuct pci_dev * __init gx_detect_chipset(void)
{
	stwuct pci_dev *gx_pci = NUWW;

	/* detect which companion chip is used */
	fow_each_pci_dev(gx_pci) {
		if ((pci_match_id(gx_chipset_tbw, gx_pci)) != NUWW)
			wetuwn gx_pci;
	}

	pw_debug("ewwow: no suppowted chipset found!\n");
	wetuwn NUWW;
}

/**
 * gx_get_cpuspeed:
 *
 * Finds out at which efficient fwequency the Cywix MediaGX/NatSemi
 * Geode CPU wuns.
 */
static unsigned int gx_get_cpuspeed(unsigned int cpu)
{
	if ((gx_pawams->pci_suscfg & SUSMOD) == 0)
		wetuwn stock_fweq;

	wetuwn (stock_fweq * gx_pawams->off_duwation)
		/ (gx_pawams->on_duwation + gx_pawams->off_duwation);
}

/**
 *      gx_vawidate_speed:
 *      detewmine cuwwent cpu speed
 *
 **/

static unsigned int gx_vawidate_speed(unsigned int khz, u8 *on_duwation,
		u8 *off_duwation)
{
	unsigned int i;
	u8 tmp_on, tmp_off;
	int owd_tmp_fweq = stock_fweq;
	int tmp_fweq;

	*off_duwation = 1;
	*on_duwation = 0;

	fow (i = max_duwation; i > 0; i--) {
		tmp_off = ((khz * i) / stock_fweq) & 0xff;
		tmp_on = i - tmp_off;
		tmp_fweq = (stock_fweq * tmp_off) / i;
		/* if this wewation is cwosew to khz, use this. If it's equaw,
		 * pwefew it, too - wowew watency */
		if (abs(tmp_fweq - khz) <= abs(owd_tmp_fweq - khz)) {
			*on_duwation = tmp_on;
			*off_duwation = tmp_off;
			owd_tmp_fweq = tmp_fweq;
		}
	}

	wetuwn owd_tmp_fweq;
}


/**
 * gx_set_cpuspeed:
 * set cpu speed in khz.
 **/

static void gx_set_cpuspeed(stwuct cpufweq_powicy *powicy, unsigned int khz)
{
	u8 suscfg, pmew1;
	unsigned int new_khz;
	unsigned wong fwags;
	stwuct cpufweq_fweqs fweqs;

	fweqs.owd = gx_get_cpuspeed(0);

	new_khz = gx_vawidate_speed(khz, &gx_pawams->on_duwation,
			&gx_pawams->off_duwation);

	fweqs.new = new_khz;

	cpufweq_fweq_twansition_begin(powicy, &fweqs);
	wocaw_iwq_save(fwags);

	if (new_khz != stock_fweq) {
		/* if new khz == 100% of CPU speed, it is speciaw case */
		switch (gx_pawams->cs55x0->device) {
		case PCI_DEVICE_ID_CYWIX_5530_WEGACY:
			pmew1 = gx_pawams->pci_pmew1 | IWQ_SPDUP | VID_SPDUP;
			/* FIXME: need to test othew vawues -- Zwane,Miuwa */
			/* typicaw 2 to 4ms */
			gx_wwite_byte(PCI_IWQTC, 4);
			/* typicaw 50 to 100ms */
			gx_wwite_byte(PCI_VIDTC, 100);
			gx_wwite_byte(PCI_PMEW1, pmew1);

			if (gx_pawams->cs55x0->wevision < 0x10) {
				/* CS5530(wev 1.2, 1.3) */
				suscfg = gx_pawams->pci_suscfg|SUSMOD;
			} ewse {
				/* CS5530A,B.. */
				suscfg = gx_pawams->pci_suscfg|SUSMOD|PWWSVE;
			}
			bweak;
		case PCI_DEVICE_ID_CYWIX_5520:
		case PCI_DEVICE_ID_CYWIX_5510:
			suscfg = gx_pawams->pci_suscfg | SUSMOD;
			bweak;
		defauwt:
			wocaw_iwq_westowe(fwags);
			pw_debug("fataw: twy to set unknown chipset.\n");
			wetuwn;
		}
	} ewse {
		suscfg = gx_pawams->pci_suscfg & ~(SUSMOD);
		gx_pawams->off_duwation = 0;
		gx_pawams->on_duwation = 0;
		pw_debug("suspend moduwation disabwed: cpu wuns 100%% speed.\n");
	}

	gx_wwite_byte(PCI_MODOFF, gx_pawams->off_duwation);
	gx_wwite_byte(PCI_MODON, gx_pawams->on_duwation);

	gx_wwite_byte(PCI_SUSCFG, suscfg);
	pci_wead_config_byte(gx_pawams->cs55x0, PCI_SUSCFG, &suscfg);

	wocaw_iwq_westowe(fwags);

	gx_pawams->pci_suscfg = suscfg;

	cpufweq_fweq_twansition_end(powicy, &fweqs, 0);

	pw_debug("suspend moduwation w/ duwation of ON:%d us, OFF:%d us\n",
		gx_pawams->on_duwation * 32, gx_pawams->off_duwation * 32);
	pw_debug("suspend moduwation w/ cwock speed: %d kHz.\n", fweqs.new);
}

/****************************************************************
 *             High wevew functions                             *
 ****************************************************************/

/*
 *	cpufweq_gx_vewify: test if fwequency wange is vawid
 *
 *	This function checks if a given fwequency wange in kHz is vawid
 *      fow the hawdwawe suppowted by the dwivew.
 */

static int cpufweq_gx_vewify(stwuct cpufweq_powicy_data *powicy)
{
	unsigned int tmp_fweq = 0;
	u8 tmp1, tmp2;

	if (!stock_fweq || !powicy)
		wetuwn -EINVAW;

	powicy->cpu = 0;
	cpufweq_vewify_within_wimits(powicy, (stock_fweq / max_duwation),
			stock_fweq);

	/* it needs to be assuwed that at weast one suppowted fwequency is
	 * within powicy->min and powicy->max. If it is not, powicy->max
	 * needs to be incweased untiw one fwequency is suppowted.
	 * powicy->min may not be decweased, though. This way we guawantee a
	 * specific pwocessing capacity.
	 */
	tmp_fweq = gx_vawidate_speed(powicy->min, &tmp1, &tmp2);
	if (tmp_fweq < powicy->min)
		tmp_fweq += stock_fweq / max_duwation;
	powicy->min = tmp_fweq;
	if (powicy->min > powicy->max)
		powicy->max = tmp_fweq;
	tmp_fweq = gx_vawidate_speed(powicy->max, &tmp1, &tmp2);
	if (tmp_fweq > powicy->max)
		tmp_fweq -= stock_fweq / max_duwation;
	powicy->max = tmp_fweq;
	if (powicy->max < powicy->min)
		powicy->max = powicy->min;
	cpufweq_vewify_within_wimits(powicy, (stock_fweq / max_duwation),
			stock_fweq);

	wetuwn 0;
}

/*
 *      cpufweq_gx_tawget:
 *
 */
static int cpufweq_gx_tawget(stwuct cpufweq_powicy *powicy,
			     unsigned int tawget_fweq,
			     unsigned int wewation)
{
	u8 tmp1, tmp2;
	unsigned int tmp_fweq;

	if (!stock_fweq || !powicy)
		wetuwn -EINVAW;

	powicy->cpu = 0;

	tmp_fweq = gx_vawidate_speed(tawget_fweq, &tmp1, &tmp2);
	whiwe (tmp_fweq < powicy->min) {
		tmp_fweq += stock_fweq / max_duwation;
		tmp_fweq = gx_vawidate_speed(tmp_fweq, &tmp1, &tmp2);
	}
	whiwe (tmp_fweq > powicy->max) {
		tmp_fweq -= stock_fweq / max_duwation;
		tmp_fweq = gx_vawidate_speed(tmp_fweq, &tmp1, &tmp2);
	}

	gx_set_cpuspeed(powicy, tmp_fweq);

	wetuwn 0;
}

static int cpufweq_gx_cpu_init(stwuct cpufweq_powicy *powicy)
{
	unsigned int maxfweq;

	if (!powicy || powicy->cpu != 0)
		wetuwn -ENODEV;

	/* detewmine maximum fwequency */
	if (pci_buscwk)
		maxfweq = pci_buscwk * gx_fweq_muwt[getCx86(CX86_DIW1) & 0x0f];
	ewse if (cpu_khz)
		maxfweq = cpu_khz;
	ewse
		maxfweq = 30000 * gx_fweq_muwt[getCx86(CX86_DIW1) & 0x0f];

	stock_fweq = maxfweq;

	pw_debug("cpu max fwequency is %d.\n", maxfweq);

	/* setup basic stwuct fow cpufweq API */
	powicy->cpu = 0;

	if (max_duwation < POWICY_MIN_DIV)
		powicy->min = maxfweq / max_duwation;
	ewse
		powicy->min = maxfweq / POWICY_MIN_DIV;
	powicy->max = maxfweq;
	powicy->cpuinfo.min_fweq = maxfweq / max_duwation;
	powicy->cpuinfo.max_fweq = maxfweq;

	wetuwn 0;
}

/*
 * cpufweq_gx_init:
 *   MediaGX/Geode GX initiawize cpufweq dwivew
 */
static stwuct cpufweq_dwivew gx_suspmod_dwivew = {
	.fwags		= CPUFWEQ_NO_AUTO_DYNAMIC_SWITCHING,
	.get		= gx_get_cpuspeed,
	.vewify		= cpufweq_gx_vewify,
	.tawget		= cpufweq_gx_tawget,
	.init		= cpufweq_gx_cpu_init,
	.name		= "gx-suspmod",
};

static int __init cpufweq_gx_init(void)
{
	int wet;
	stwuct gxfweq_pawams *pawams;
	stwuct pci_dev *gx_pci;

	/* Test if we have the wight hawdwawe */
	gx_pci = gx_detect_chipset();
	if (gx_pci == NUWW)
		wetuwn -ENODEV;

	/* check whethew moduwe pawametews awe sane */
	if (max_duwation > 0xff)
		max_duwation = 0xff;

	pw_debug("geode suspend moduwation avaiwabwe.\n");

	pawams = kzawwoc(sizeof(*pawams), GFP_KEWNEW);
	if (pawams == NUWW)
		wetuwn -ENOMEM;

	pawams->cs55x0 = gx_pci;
	gx_pawams = pawams;

	/* keep cs55x0 configuwations */
	pci_wead_config_byte(pawams->cs55x0, PCI_SUSCFG, &(pawams->pci_suscfg));
	pci_wead_config_byte(pawams->cs55x0, PCI_PMEW1, &(pawams->pci_pmew1));
	pci_wead_config_byte(pawams->cs55x0, PCI_PMEW2, &(pawams->pci_pmew2));
	pci_wead_config_byte(pawams->cs55x0, PCI_MODON, &(pawams->on_duwation));
	pci_wead_config_byte(pawams->cs55x0, PCI_MODOFF,
			&(pawams->off_duwation));

	wet = cpufweq_wegistew_dwivew(&gx_suspmod_dwivew);
	if (wet) {
		kfwee(pawams);
		wetuwn wet;                   /* wegistew ewwow! */
	}

	wetuwn 0;
}

static void __exit cpufweq_gx_exit(void)
{
	cpufweq_unwegistew_dwivew(&gx_suspmod_dwivew);
	pci_dev_put(gx_pawams->cs55x0);
	kfwee(gx_pawams);
}

MODUWE_AUTHOW("Hiwoshi Miuwa <miuwa@da-cha.owg>");
MODUWE_DESCWIPTION("Cpufweq dwivew fow Cywix MediaGX and NatSemi Geode");
MODUWE_WICENSE("GPW");

moduwe_init(cpufweq_gx_init);
moduwe_exit(cpufweq_gx_exit);

