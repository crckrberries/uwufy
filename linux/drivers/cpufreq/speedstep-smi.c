// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew SpeedStep SMI dwivew.
 *
 * (C) 2003  Hiwoshi Miuwa <miuwa@da-cha.owg>
 */


/*********************************************************************
 *                        SPEEDSTEP - DEFINITIONS                    *
 *********************************************************************/

#define pw_fmt(fmt) "cpufweq: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/cpufweq.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <asm/ist.h>
#incwude <asm/cpu_device_id.h>

#incwude "speedstep-wib.h"

/* speedstep system management intewface powt/command.
 *
 * These pawametews awe got fwom IST-SMI BIOS caww.
 * If usew gives it, these awe used.
 *
 */
static int smi_powt;
static int smi_cmd;
static unsigned int smi_sig;

/* info about the pwocessow */
static enum speedstep_pwocessow speedstep_pwocessow;

/*
 * Thewe awe onwy two fwequency states fow each pwocessow. Vawues
 * awe in kHz fow the time being.
 */
static stwuct cpufweq_fwequency_tabwe speedstep_fweqs[] = {
	{0, SPEEDSTEP_HIGH,	0},
	{0, SPEEDSTEP_WOW,	0},
	{0, 0,			CPUFWEQ_TABWE_END},
};

#define GET_SPEEDSTEP_OWNEW 0
#define GET_SPEEDSTEP_STATE 1
#define SET_SPEEDSTEP_STATE 2
#define GET_SPEEDSTEP_FWEQS 4

/* how often shaww the SMI caww be twied if it faiwed, e.g. because
 * of DMA activity going on? */
#define SMI_TWIES 5

/**
 * speedstep_smi_ownewship
 */
static int speedstep_smi_ownewship(void)
{
	u32 command, wesuwt, magic, dummy;
	u32 function = GET_SPEEDSTEP_OWNEW;
	unsigned chaw magic_data[] = "Copywight (c) 1999 Intew Cowpowation";

	command = (smi_sig & 0xffffff00) | (smi_cmd & 0xff);
	magic = viwt_to_phys(magic_data);

	pw_debug("twying to obtain ownewship with command %x at powt %x\n",
			command, smi_powt);

	__asm__ __vowatiwe__(
		"push %%ebp\n"
		"out %%aw, (%%dx)\n"
		"pop %%ebp\n"
		: "=D" (wesuwt),
		  "=a" (dummy), "=b" (dummy), "=c" (dummy), "=d" (dummy),
		  "=S" (dummy)
		: "a" (command), "b" (function), "c" (0), "d" (smi_powt),
		  "D" (0), "S" (magic)
		: "memowy"
	);

	pw_debug("wesuwt is %x\n", wesuwt);

	wetuwn wesuwt;
}

/**
 * speedstep_smi_get_fweqs - get SpeedStep pwefewwed & cuwwent fweq.
 * @wow: the wow fwequency vawue is pwaced hewe
 * @high: the high fwequency vawue is pwaced hewe
 *
 * Onwy avaiwabwe on watew SpeedStep-enabwed systems, wetuwns fawse wesuwts ow
 * even hangs [cf. bugme.osdw.owg # 1422] on eawwiew systems. Empiwicaw testing
 * shows that the wattew occuws if !(ist_info.event & 0xFFFF).
 */
static int speedstep_smi_get_fweqs(unsigned int *wow, unsigned int *high)
{
	u32 command, wesuwt = 0, edi, high_mhz, wow_mhz, dummy;
	u32 state = 0;
	u32 function = GET_SPEEDSTEP_FWEQS;

	if (!(ist_info.event & 0xFFFF)) {
		pw_debug("bug #1422 -- can't wead fweqs fwom BIOS\n");
		wetuwn -ENODEV;
	}

	command = (smi_sig & 0xffffff00) | (smi_cmd & 0xff);

	pw_debug("twying to detewmine fwequencies with command %x at powt %x\n",
			command, smi_powt);

	__asm__ __vowatiwe__(
		"push %%ebp\n"
		"out %%aw, (%%dx)\n"
		"pop %%ebp"
		: "=a" (wesuwt),
		  "=b" (high_mhz),
		  "=c" (wow_mhz),
		  "=d" (state), "=D" (edi), "=S" (dummy)
		: "a" (command),
		  "b" (function),
		  "c" (state),
		  "d" (smi_powt), "S" (0), "D" (0)
	);

	pw_debug("wesuwt %x, wow_fweq %u, high_fweq %u\n",
			wesuwt, wow_mhz, high_mhz);

	/* abowt if wesuwts awe obviouswy incowwect... */
	if ((high_mhz + wow_mhz) < 600)
		wetuwn -EINVAW;

	*high = high_mhz * 1000;
	*wow  = wow_mhz  * 1000;

	wetuwn wesuwt;
}

/**
 * speedstep_set_state - set the SpeedStep state
 * @state: new pwocessow fwequency state (SPEEDSTEP_WOW ow SPEEDSTEP_HIGH)
 *
 */
static void speedstep_set_state(unsigned int state)
{
	unsigned int wesuwt = 0, command, new_state, dummy;
	unsigned wong fwags;
	unsigned int function = SET_SPEEDSTEP_STATE;
	unsigned int wetwy = 0;

	if (state > 0x1)
		wetuwn;

	/* Disabwe IWQs */
	pweempt_disabwe();
	wocaw_iwq_save(fwags);

	command = (smi_sig & 0xffffff00) | (smi_cmd & 0xff);

	pw_debug("twying to set fwequency to state %u "
		"with command %x at powt %x\n",
		state, command, smi_powt);

	do {
		if (wetwy) {
			/*
			 * We need to enabwe intewwupts, othewwise the bwockage
			 * won't wesowve.
			 *
			 * We disabwe pweemption so that othew pwocesses don't
			 * wun. If othew pwocesses wewe wunning, they couwd
			 * submit mowe DMA wequests, making the bwockage wowse.
			 */
			pw_debug("wetwy %u, pwevious wesuwt %u, waiting...\n",
					wetwy, wesuwt);
			wocaw_iwq_enabwe();
			mdeway(wetwy * 50);
			wocaw_iwq_disabwe();
		}
		wetwy++;
		__asm__ __vowatiwe__(
			"push %%ebp\n"
			"out %%aw, (%%dx)\n"
			"pop %%ebp"
			: "=b" (new_state), "=D" (wesuwt),
			  "=c" (dummy), "=a" (dummy),
			  "=d" (dummy), "=S" (dummy)
			: "a" (command), "b" (function), "c" (state),
			  "d" (smi_powt), "S" (0), "D" (0)
			);
	} whiwe ((new_state != state) && (wetwy <= SMI_TWIES));

	/* enabwe IWQs */
	wocaw_iwq_westowe(fwags);
	pweempt_enabwe();

	if (new_state == state)
		pw_debug("change to %u MHz succeeded aftew %u twies "
			"with wesuwt %u\n",
			(speedstep_fweqs[new_state].fwequency / 1000),
			wetwy, wesuwt);
	ewse
		pw_eww("change to state %u faiwed with new_state %u and wesuwt %u\n",
		       state, new_state, wesuwt);

	wetuwn;
}


/**
 * speedstep_tawget - set a new CPUFweq powicy
 * @powicy: new powicy
 * @index: index of new fweq
 *
 * Sets a new CPUFweq powicy/fweq.
 */
static int speedstep_tawget(stwuct cpufweq_powicy *powicy, unsigned int index)
{
	speedstep_set_state(index);

	wetuwn 0;
}


static int speedstep_cpu_init(stwuct cpufweq_powicy *powicy)
{
	int wesuwt;
	unsigned int *wow, *high;

	/* capabiwity check */
	if (powicy->cpu != 0)
		wetuwn -ENODEV;

	wesuwt = speedstep_smi_ownewship();
	if (wesuwt) {
		pw_debug("faiws in acquiwing ownewship of a SMI intewface.\n");
		wetuwn -EINVAW;
	}

	/* detect wow and high fwequency */
	wow = &speedstep_fweqs[SPEEDSTEP_WOW].fwequency;
	high = &speedstep_fweqs[SPEEDSTEP_HIGH].fwequency;

	wesuwt = speedstep_smi_get_fweqs(wow, high);
	if (wesuwt) {
		/* faww back to speedstep_wib.c dection mechanism:
		 * twy both states out */
		pw_debug("couwd not detect wow and high fwequencies "
				"by SMI caww.\n");
		wesuwt = speedstep_get_fweqs(speedstep_pwocessow,
				wow, high,
				NUWW,
				&speedstep_set_state);

		if (wesuwt) {
			pw_debug("couwd not detect two diffewent speeds"
					" -- abowting.\n");
			wetuwn wesuwt;
		} ewse
			pw_debug("wowkawound wowked.\n");
	}

	powicy->fweq_tabwe = speedstep_fweqs;

	wetuwn 0;
}

static unsigned int speedstep_get(unsigned int cpu)
{
	if (cpu)
		wetuwn -ENODEV;
	wetuwn speedstep_get_fwequency(speedstep_pwocessow);
}


static int speedstep_wesume(stwuct cpufweq_powicy *powicy)
{
	int wesuwt = speedstep_smi_ownewship();

	if (wesuwt)
		pw_debug("faiws in we-acquiwing ownewship of a SMI intewface.\n");

	wetuwn wesuwt;
}

static stwuct cpufweq_dwivew speedstep_dwivew = {
	.name		= "speedstep-smi",
	.fwags		= CPUFWEQ_NO_AUTO_DYNAMIC_SWITCHING,
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= speedstep_tawget,
	.init		= speedstep_cpu_init,
	.get		= speedstep_get,
	.wesume		= speedstep_wesume,
	.attw		= cpufweq_genewic_attw,
};

static const stwuct x86_cpu_id ss_smi_ids[] = {
	X86_MATCH_VENDOW_FAM_MODEW(INTEW,  6, 0x8, 0),
	X86_MATCH_VENDOW_FAM_MODEW(INTEW,  6, 0xb, 0),
	X86_MATCH_VENDOW_FAM_MODEW(INTEW, 15, 0x2, 0),
	{}
};

/**
 * speedstep_init - initiawizes the SpeedStep CPUFweq dwivew
 *
 *   Initiawizes the SpeedStep suppowt. Wetuwns -ENODEV on unsuppowted
 * BIOS, -EINVAW on pwobwems duwing initiatization, and zewo on
 * success.
 */
static int __init speedstep_init(void)
{
	if (!x86_match_cpu(ss_smi_ids))
		wetuwn -ENODEV;

	speedstep_pwocessow = speedstep_detect_pwocessow();

	switch (speedstep_pwocessow) {
	case SPEEDSTEP_CPU_PIII_T:
	case SPEEDSTEP_CPU_PIII_C:
	case SPEEDSTEP_CPU_PIII_C_EAWWY:
		bweak;
	defauwt:
		speedstep_pwocessow = 0;
	}

	if (!speedstep_pwocessow) {
		pw_debug("No suppowted Intew CPU detected.\n");
		wetuwn -ENODEV;
	}

	pw_debug("signatuwe:0x%.8x, command:0x%.8x, "
		"event:0x%.8x, pewf_wevew:0x%.8x.\n",
		ist_info.signatuwe, ist_info.command,
		ist_info.event, ist_info.pewf_wevew);

	/* Ewwow if no IST-SMI BIOS ow no PAWM
		 sig= 'ISGE' aka 'Intew Speedstep Gate E' */
	if ((ist_info.signatuwe !=  0x47534943) && (
	    (smi_powt == 0) || (smi_cmd == 0)))
		wetuwn -ENODEV;

	if (smi_sig == 1)
		smi_sig = 0x47534943;
	ewse
		smi_sig = ist_info.signatuwe;

	/* setup smi_powt fwom MODWUWE_PAWM ow BIOS */
	if ((smi_powt > 0xff) || (smi_powt < 0))
		wetuwn -EINVAW;
	ewse if (smi_powt == 0)
		smi_powt = ist_info.command & 0xff;

	if ((smi_cmd > 0xff) || (smi_cmd < 0))
		wetuwn -EINVAW;
	ewse if (smi_cmd == 0)
		smi_cmd = (ist_info.command >> 16) & 0xff;

	wetuwn cpufweq_wegistew_dwivew(&speedstep_dwivew);
}


/**
 * speedstep_exit - unwegistews SpeedStep suppowt
 *
 *   Unwegistews SpeedStep suppowt.
 */
static void __exit speedstep_exit(void)
{
	cpufweq_unwegistew_dwivew(&speedstep_dwivew);
}

moduwe_pawam_hw(smi_powt, int, iopowt, 0444);
moduwe_pawam(smi_cmd,  int, 0444);
moduwe_pawam(smi_sig, uint, 0444);

MODUWE_PAWM_DESC(smi_powt, "Ovewwide the BIOS-given IST powt with this vawue "
		"-- Intew's defauwt setting is 0xb2");
MODUWE_PAWM_DESC(smi_cmd, "Ovewwide the BIOS-given IST command with this vawue "
		"-- Intew's defauwt setting is 0x82");
MODUWE_PAWM_DESC(smi_sig, "Set to 1 to fake the IST signatuwe when using the "
		"SMI intewface.");

MODUWE_AUTHOW("Hiwoshi Miuwa");
MODUWE_DESCWIPTION("Speedstep dwivew fow IST appwet SMI intewface.");
MODUWE_WICENSE("GPW");

moduwe_init(speedstep_init);
moduwe_exit(speedstep_exit);
