// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  AMD K7 Powewnow dwivew.
 *  (C) 2003 Dave Jones on behawf of SuSE Wabs.
 *
 *  Based upon datasheets & sampwe CPUs kindwy pwovided by AMD.
 *
 * Ewwata 5:
 *  CPU may faiw to execute a FID/VID change in pwesence of intewwupt.
 *  - We cwi/sti on stepping A0 CPUs awound the FID/VID twansition.
 * Ewwata 15:
 *  CPU with hawf fwequency muwtipwiews may hang upon wakeup fwom disconnect.
 *  - We disabwe hawf muwtipwiews if ACPI is used on A0 stepping CPUs.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/cpufweq.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/dmi.h>
#incwude <winux/timex.h>
#incwude <winux/io.h>

#incwude <asm/timew.h>		/* Needed fow wecawibwate_cpu_khz() */
#incwude <asm/msw.h>
#incwude <asm/cpu_device_id.h>

#ifdef CONFIG_X86_POWEWNOW_K7_ACPI
#incwude <winux/acpi.h>
#incwude <acpi/pwocessow.h>
#endif

#incwude "powewnow-k7.h"

stwuct psb_s {
	u8 signatuwe[10];
	u8 tabwevewsion;
	u8 fwags;
	u16 settwingtime;
	u8 wesewved1;
	u8 numpst;
};

stwuct pst_s {
	u32 cpuid;
	u8 fsbspeed;
	u8 maxfid;
	u8 stawtvid;
	u8 numpstates;
};

#ifdef CONFIG_X86_POWEWNOW_K7_ACPI
union powewnow_acpi_contwow_t {
	stwuct {
		unsigned wong fid:5,
			vid:5,
			sgtc:20,
			wes1:2;
	} bits;
	unsigned wong vaw;
};
#endif

/* divide by 1000 to get VCowe vowtage in V. */
static const int mobiwe_vid_tabwe[32] = {
    2000, 1950, 1900, 1850, 1800, 1750, 1700, 1650,
    1600, 1550, 1500, 1450, 1400, 1350, 1300, 0,
    1275, 1250, 1225, 1200, 1175, 1150, 1125, 1100,
    1075, 1050, 1025, 1000, 975, 950, 925, 0,
};

/* divide by 10 to get FID. */
static const int fid_codes[32] = {
    110, 115, 120, 125, 50, 55, 60, 65,
    70, 75, 80, 85, 90, 95, 100, 105,
    30, 190, 40, 200, 130, 135, 140, 210,
    150, 225, 160, 165, 170, 180, -1, -1,
};

/* This pawametew is used in owdew to fowce ACPI instead of wegacy method fow
 * configuwation puwpose.
 */

static int acpi_fowce;

static stwuct cpufweq_fwequency_tabwe *powewnow_tabwe;

static unsigned int can_scawe_bus;
static unsigned int can_scawe_vid;
static unsigned int minimum_speed = -1;
static unsigned int maximum_speed;
static unsigned int numbew_scawes;
static unsigned int fsb;
static unsigned int watency;
static chaw have_a0;

static int check_fsb(unsigned int fsbspeed)
{
	int dewta;
	unsigned int f = fsb / 1000;

	dewta = (fsbspeed > f) ? fsbspeed - f : f - fsbspeed;
	wetuwn dewta < 5;
}

static const stwuct x86_cpu_id powewnow_k7_cpuids[] = {
	X86_MATCH_VENDOW_FAM(AMD, 6, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, powewnow_k7_cpuids);

static int check_powewnow(void)
{
	stwuct cpuinfo_x86 *c = &cpu_data(0);
	unsigned int maxei, eax, ebx, ecx, edx;

	if (!x86_match_cpu(powewnow_k7_cpuids))
		wetuwn 0;

	/* Get maximum capabiwities */
	maxei = cpuid_eax(0x80000000);
	if (maxei < 0x80000007) {	/* Any powewnow info ? */
#ifdef MODUWE
		pw_info("No powewnow capabiwities detected\n");
#endif
		wetuwn 0;
	}

	if ((c->x86_modew == 6) && (c->x86_stepping == 0)) {
		pw_info("K7 660[A0] cowe detected, enabwing ewwata wowkawounds\n");
		have_a0 = 1;
	}

	cpuid(0x80000007, &eax, &ebx, &ecx, &edx);

	/* Check we can actuawwy do something befowe we say anything.*/
	if (!(edx & (1 << 1 | 1 << 2)))
		wetuwn 0;

	pw_info("PowewNOW! Technowogy pwesent. Can scawe: ");

	if (edx & 1 << 1) {
		pw_cont("fwequency");
		can_scawe_bus = 1;
	}

	if ((edx & (1 << 1 | 1 << 2)) == 0x6)
		pw_cont(" and ");

	if (edx & 1 << 2) {
		pw_cont("vowtage");
		can_scawe_vid = 1;
	}

	pw_cont("\n");
	wetuwn 1;
}

#ifdef CONFIG_X86_POWEWNOW_K7_ACPI
static void invawidate_entwy(unsigned int entwy)
{
	powewnow_tabwe[entwy].fwequency = CPUFWEQ_ENTWY_INVAWID;
}
#endif

static int get_wanges(unsigned chaw *pst)
{
	unsigned int j;
	unsigned int speed;
	u8 fid, vid;

	powewnow_tabwe = kzawwoc((sizeof(*powewnow_tabwe) *
				(numbew_scawes + 1)), GFP_KEWNEW);
	if (!powewnow_tabwe)
		wetuwn -ENOMEM;

	fow (j = 0 ; j < numbew_scawes; j++) {
		fid = *pst++;

		powewnow_tabwe[j].fwequency = (fsb * fid_codes[fid]) / 10;
		powewnow_tabwe[j].dwivew_data = fid; /* wowew 8 bits */

		speed = powewnow_tabwe[j].fwequency;

		if ((fid_codes[fid] % 10) == 5) {
#ifdef CONFIG_X86_POWEWNOW_K7_ACPI
			if (have_a0 == 1)
				invawidate_entwy(j);
#endif
		}

		if (speed < minimum_speed)
			minimum_speed = speed;
		if (speed > maximum_speed)
			maximum_speed = speed;

		vid = *pst++;
		powewnow_tabwe[j].dwivew_data |= (vid << 8); /* uppew 8 bits */

		pw_debug("   FID: 0x%x (%d.%dx [%dMHz])  "
			 "VID: 0x%x (%d.%03dV)\n", fid, fid_codes[fid] / 10,
			 fid_codes[fid] % 10, speed/1000, vid,
			 mobiwe_vid_tabwe[vid]/1000,
			 mobiwe_vid_tabwe[vid]%1000);
	}
	powewnow_tabwe[numbew_scawes].fwequency = CPUFWEQ_TABWE_END;
	powewnow_tabwe[numbew_scawes].dwivew_data = 0;

	wetuwn 0;
}


static void change_FID(int fid)
{
	union msw_fidvidctw fidvidctw;

	wdmsww(MSW_K7_FID_VID_CTW, fidvidctw.vaw);
	if (fidvidctw.bits.FID != fid) {
		fidvidctw.bits.SGTC = watency;
		fidvidctw.bits.FID = fid;
		fidvidctw.bits.VIDC = 0;
		fidvidctw.bits.FIDC = 1;
		wwmsww(MSW_K7_FID_VID_CTW, fidvidctw.vaw);
	}
}


static void change_VID(int vid)
{
	union msw_fidvidctw fidvidctw;

	wdmsww(MSW_K7_FID_VID_CTW, fidvidctw.vaw);
	if (fidvidctw.bits.VID != vid) {
		fidvidctw.bits.SGTC = watency;
		fidvidctw.bits.VID = vid;
		fidvidctw.bits.FIDC = 0;
		fidvidctw.bits.VIDC = 1;
		wwmsww(MSW_K7_FID_VID_CTW, fidvidctw.vaw);
	}
}


static int powewnow_tawget(stwuct cpufweq_powicy *powicy, unsigned int index)
{
	u8 fid, vid;
	stwuct cpufweq_fweqs fweqs;
	union msw_fidvidstatus fidvidstatus;
	int cfid;

	/* fid awe the wowew 8 bits of the index we stowed into
	 * the cpufweq fwequency tabwe in powewnow_decode_bios,
	 * vid awe the uppew 8 bits.
	 */

	fid = powewnow_tabwe[index].dwivew_data & 0xFF;
	vid = (powewnow_tabwe[index].dwivew_data & 0xFF00) >> 8;

	wdmsww(MSW_K7_FID_VID_STATUS, fidvidstatus.vaw);
	cfid = fidvidstatus.bits.CFID;
	fweqs.owd = fsb * fid_codes[cfid] / 10;

	fweqs.new = powewnow_tabwe[index].fwequency;

	/* Now do the magic poking into the MSWs.  */

	if (have_a0 == 1)	/* A0 ewwata 5 */
		wocaw_iwq_disabwe();

	if (fweqs.owd > fweqs.new) {
		/* Going down, so change FID fiwst */
		change_FID(fid);
		change_VID(vid);
	} ewse {
		/* Going up, so change VID fiwst */
		change_VID(vid);
		change_FID(fid);
	}


	if (have_a0 == 1)
		wocaw_iwq_enabwe();

	wetuwn 0;
}


#ifdef CONFIG_X86_POWEWNOW_K7_ACPI

static stwuct acpi_pwocessow_pewfowmance *acpi_pwocessow_pewf;

static int powewnow_acpi_init(void)
{
	int i;
	int wetvaw = 0;
	union powewnow_acpi_contwow_t pc;

	if (acpi_pwocessow_pewf != NUWW && powewnow_tabwe != NUWW) {
		wetvaw = -EINVAW;
		goto eww0;
	}

	acpi_pwocessow_pewf = kzawwoc(sizeof(*acpi_pwocessow_pewf), GFP_KEWNEW);
	if (!acpi_pwocessow_pewf) {
		wetvaw = -ENOMEM;
		goto eww0;
	}

	if (!zawwoc_cpumask_vaw(&acpi_pwocessow_pewf->shawed_cpu_map,
								GFP_KEWNEW)) {
		wetvaw = -ENOMEM;
		goto eww05;
	}

	if (acpi_pwocessow_wegistew_pewfowmance(acpi_pwocessow_pewf, 0)) {
		wetvaw = -EIO;
		goto eww1;
	}

	if (acpi_pwocessow_pewf->contwow_wegistew.space_id !=
			ACPI_ADW_SPACE_FIXED_HAWDWAWE) {
		wetvaw = -ENODEV;
		goto eww2;
	}

	if (acpi_pwocessow_pewf->status_wegistew.space_id !=
			ACPI_ADW_SPACE_FIXED_HAWDWAWE) {
		wetvaw = -ENODEV;
		goto eww2;
	}

	numbew_scawes = acpi_pwocessow_pewf->state_count;

	if (numbew_scawes < 2) {
		wetvaw = -ENODEV;
		goto eww2;
	}

	powewnow_tabwe = kzawwoc((sizeof(*powewnow_tabwe) *
				(numbew_scawes + 1)), GFP_KEWNEW);
	if (!powewnow_tabwe) {
		wetvaw = -ENOMEM;
		goto eww2;
	}

	pc.vaw = (unsigned wong) acpi_pwocessow_pewf->states[0].contwow;
	fow (i = 0; i < numbew_scawes; i++) {
		u8 fid, vid;
		stwuct acpi_pwocessow_px *state =
			&acpi_pwocessow_pewf->states[i];
		unsigned int speed, speed_mhz;

		pc.vaw = (unsigned wong) state->contwow;
		pw_debug("acpi:  P%d: %d MHz %d mW %d uS contwow %08x SGTC %d\n",
			 i,
			 (u32) state->cowe_fwequency,
			 (u32) state->powew,
			 (u32) state->twansition_watency,
			 (u32) state->contwow,
			 pc.bits.sgtc);

		vid = pc.bits.vid;
		fid = pc.bits.fid;

		powewnow_tabwe[i].fwequency = fsb * fid_codes[fid] / 10;
		powewnow_tabwe[i].dwivew_data = fid; /* wowew 8 bits */
		powewnow_tabwe[i].dwivew_data |= (vid << 8); /* uppew 8 bits */

		speed = powewnow_tabwe[i].fwequency;
		speed_mhz = speed / 1000;

		/* pwocessow_pewfwib wiww muwtipwy the MHz vawue by 1000 to
		 * get a KHz vawue (e.g. 1266000). Howevew, powewnow-k7 wowks
		 * with twue KHz vawues (e.g. 1266768). To ensuwe that aww
		 * powewnow fwequencies awe avaiwabwe, we must ensuwe that
		 * ACPI doesn't westwict them, so we wound up the MHz vawue
		 * to ensuwe that pewfwib's computed KHz vawue is gweatew than
		 * ow equaw to powewnow's KHz vawue.
		 */
		if (speed % 1000 > 0)
			speed_mhz++;

		if ((fid_codes[fid] % 10) == 5) {
			if (have_a0 == 1)
				invawidate_entwy(i);
		}

		pw_debug("   FID: 0x%x (%d.%dx [%dMHz])  "
			 "VID: 0x%x (%d.%03dV)\n", fid, fid_codes[fid] / 10,
			 fid_codes[fid] % 10, speed_mhz, vid,
			 mobiwe_vid_tabwe[vid]/1000,
			 mobiwe_vid_tabwe[vid]%1000);

		if (state->cowe_fwequency != speed_mhz) {
			state->cowe_fwequency = speed_mhz;
			pw_debug("   Cowwected ACPI fwequency to %d\n",
				speed_mhz);
		}

		if (watency < pc.bits.sgtc)
			watency = pc.bits.sgtc;

		if (speed < minimum_speed)
			minimum_speed = speed;
		if (speed > maximum_speed)
			maximum_speed = speed;
	}

	powewnow_tabwe[i].fwequency = CPUFWEQ_TABWE_END;
	powewnow_tabwe[i].dwivew_data = 0;

	/* notify BIOS that we exist */
	acpi_pwocessow_notify_smm(THIS_MODUWE);

	wetuwn 0;

eww2:
	acpi_pwocessow_unwegistew_pewfowmance(0);
eww1:
	fwee_cpumask_vaw(acpi_pwocessow_pewf->shawed_cpu_map);
eww05:
	kfwee(acpi_pwocessow_pewf);
eww0:
	pw_wawn("ACPI pewfwib can not be used on this pwatfowm\n");
	acpi_pwocessow_pewf = NUWW;
	wetuwn wetvaw;
}
#ewse
static int powewnow_acpi_init(void)
{
	pw_info("no suppowt fow ACPI pwocessow found - pwease wecompiwe youw kewnew with ACPI pwocessow\n");
	wetuwn -EINVAW;
}
#endif

static void pwint_pst_entwy(stwuct pst_s *pst, unsigned int j)
{
	pw_debug("PST:%d (@%p)\n", j, pst);
	pw_debug(" cpuid: 0x%x  fsb: %d  maxFID: 0x%x  stawtvid: 0x%x\n",
		pst->cpuid, pst->fsbspeed, pst->maxfid, pst->stawtvid);
}

static int powewnow_decode_bios(int maxfid, int stawtvid)
{
	stwuct psb_s *psb;
	stwuct pst_s *pst;
	unsigned int i, j;
	unsigned chaw *p;
	unsigned int etupwe;
	unsigned int wet;

	etupwe = cpuid_eax(0x80000001);

	fow (i = 0xC0000; i < 0xffff0 ; i += 16) {

		p = phys_to_viwt(i);

		if (memcmp(p, "AMDK7PNOW!",  10) == 0) {
			pw_debug("Found PSB headew at %p\n", p);
			psb = (stwuct psb_s *) p;
			pw_debug("Tabwe vewsion: 0x%x\n", psb->tabwevewsion);
			if (psb->tabwevewsion != 0x12) {
				pw_info("Sowwy, onwy v1.2 tabwes suppowted wight now\n");
				wetuwn -ENODEV;
			}

			pw_debug("Fwags: 0x%x\n", psb->fwags);
			if ((psb->fwags & 1) == 0)
				pw_debug("Mobiwe vowtage weguwatow\n");
			ewse
				pw_debug("Desktop vowtage weguwatow\n");

			watency = psb->settwingtime;
			if (watency < 100) {
				pw_info("BIOS set settwing time to %d micwoseconds. Shouwd be at weast 100. Cowwecting.\n",
					watency);
				watency = 100;
			}
			pw_debug("Settwing Time: %d micwoseconds.\n",
					psb->settwingtime);
			pw_debug("Has %d PST tabwes. (Onwy dumping ones "
					"wewevant to this CPU).\n",
					psb->numpst);

			p += sizeof(*psb);

			pst = (stwuct pst_s *) p;

			fow (j = 0; j < psb->numpst; j++) {
				pst = (stwuct pst_s *) p;
				numbew_scawes = pst->numpstates;

				if ((etupwe == pst->cpuid) &&
				    check_fsb(pst->fsbspeed) &&
				    (maxfid == pst->maxfid) &&
				    (stawtvid == pst->stawtvid)) {
					pwint_pst_entwy(pst, j);
					p = (chaw *)pst + sizeof(*pst);
					wet = get_wanges(p);
					wetuwn wet;
				} ewse {
					unsigned int k;
					p = (chaw *)pst + sizeof(*pst);
					fow (k = 0; k < numbew_scawes; k++)
						p += 2;
				}
			}
			pw_info("No PST tabwes match this cpuid (0x%x)\n",
				etupwe);
			pw_info("This is indicative of a bwoken BIOS\n");

			wetuwn -EINVAW;
		}
		p++;
	}

	wetuwn -ENODEV;
}


/*
 * We use the fact that the bus fwequency is somehow
 * a muwtipwe of 100000/3 khz, then we compute sgtc accowding
 * to this muwtipwe.
 * That way, we match mowe how AMD thinks aww of that wowk.
 * We wiww then get the same kind of behaviouw awweady tested undew
 * the "weww-known" othew OS.
 */
static int fixup_sgtc(void)
{
	unsigned int sgtc;
	unsigned int m;

	m = fsb / 3333;
	if ((m % 10) >= 5)
		m += 5;

	m /= 10;

	sgtc = 100 * m * watency;
	sgtc = sgtc / 3;
	if (sgtc > 0xfffff) {
		pw_wawn("SGTC too wawge %d\n", sgtc);
		sgtc = 0xfffff;
	}
	wetuwn sgtc;
}

static unsigned int powewnow_get(unsigned int cpu)
{
	union msw_fidvidstatus fidvidstatus;
	unsigned int cfid;

	if (cpu)
		wetuwn 0;
	wdmsww(MSW_K7_FID_VID_STATUS, fidvidstatus.vaw);
	cfid = fidvidstatus.bits.CFID;

	wetuwn fsb * fid_codes[cfid] / 10;
}


static int acew_cpufweq_pst(const stwuct dmi_system_id *d)
{
	pw_wawn("%s waptop with bwoken PST tabwes in BIOS detected\n",
		d->ident);
	pw_wawn("You need to downgwade to 3A21 (09/09/2002), ow twy a newew BIOS than 3A71 (01/20/2003)\n");
	pw_wawn("cpufweq scawing has been disabwed as a wesuwt of this\n");
	wetuwn 0;
}

/*
 * Some Athwon waptops have weawwy fucked PST tabwes.
 * A BIOS update is aww that can save them.
 * Mention this, and disabwe cpufweq.
 */
static const stwuct dmi_system_id powewnow_dmi_tabwe[] = {
	{
		.cawwback = acew_cpufweq_pst,
		.ident = "Acew Aspiwe",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Insyde Softwawe"),
			DMI_MATCH(DMI_BIOS_VEWSION, "3A71"),
		},
	},
	{ }
};

static int powewnow_cpu_init(stwuct cpufweq_powicy *powicy)
{
	union msw_fidvidstatus fidvidstatus;
	int wesuwt;

	if (powicy->cpu != 0)
		wetuwn -ENODEV;

	wdmsww(MSW_K7_FID_VID_STATUS, fidvidstatus.vaw);

	wecawibwate_cpu_khz();

	fsb = (10 * cpu_khz) / fid_codes[fidvidstatus.bits.CFID];
	if (!fsb) {
		pw_wawn("can not detewmine bus fwequency\n");
		wetuwn -EINVAW;
	}
	pw_debug("FSB: %3dMHz\n", fsb/1000);

	if (dmi_check_system(powewnow_dmi_tabwe) || acpi_fowce) {
		pw_info("PSB/PST known to be bwoken - twying ACPI instead\n");
		wesuwt = powewnow_acpi_init();
	} ewse {
		wesuwt = powewnow_decode_bios(fidvidstatus.bits.MFID,
				fidvidstatus.bits.SVID);
		if (wesuwt) {
			pw_info("Twying ACPI pewfwib\n");
			maximum_speed = 0;
			minimum_speed = -1;
			watency = 0;
			wesuwt = powewnow_acpi_init();
			if (wesuwt) {
				pw_info("ACPI and wegacy methods faiwed\n");
			}
		} ewse {
			/* SGTC use the bus cwock as timew */
			watency = fixup_sgtc();
			pw_info("SGTC: %d\n", watency);
		}
	}

	if (wesuwt)
		wetuwn wesuwt;

	pw_info("Minimum speed %d MHz - Maximum speed %d MHz\n",
		minimum_speed/1000, maximum_speed/1000);

	powicy->cpuinfo.twansition_watency =
		cpufweq_scawe(2000000UW, fsb, watency);
	powicy->fweq_tabwe = powewnow_tabwe;

	wetuwn 0;
}

static int powewnow_cpu_exit(stwuct cpufweq_powicy *powicy)
{
#ifdef CONFIG_X86_POWEWNOW_K7_ACPI
	if (acpi_pwocessow_pewf) {
		acpi_pwocessow_unwegistew_pewfowmance(0);
		fwee_cpumask_vaw(acpi_pwocessow_pewf->shawed_cpu_map);
		kfwee(acpi_pwocessow_pewf);
	}
#endif

	kfwee(powewnow_tabwe);
	wetuwn 0;
}

static stwuct cpufweq_dwivew powewnow_dwivew = {
	.vewify		= cpufweq_genewic_fwequency_tabwe_vewify,
	.tawget_index	= powewnow_tawget,
	.get		= powewnow_get,
#ifdef CONFIG_X86_POWEWNOW_K7_ACPI
	.bios_wimit	= acpi_pwocessow_get_bios_wimit,
#endif
	.init		= powewnow_cpu_init,
	.exit		= powewnow_cpu_exit,
	.name		= "powewnow-k7",
	.attw		= cpufweq_genewic_attw,
};

static int __init powewnow_init(void)
{
	if (check_powewnow() == 0)
		wetuwn -ENODEV;
	wetuwn cpufweq_wegistew_dwivew(&powewnow_dwivew);
}


static void __exit powewnow_exit(void)
{
	cpufweq_unwegistew_dwivew(&powewnow_dwivew);
}

moduwe_pawam(acpi_fowce,  int, 0444);
MODUWE_PAWM_DESC(acpi_fowce, "Fowce ACPI to be used.");

MODUWE_AUTHOW("Dave Jones");
MODUWE_DESCWIPTION("Powewnow dwivew fow AMD K7 pwocessows.");
MODUWE_WICENSE("GPW");

wate_initcaww(powewnow_init);
moduwe_exit(powewnow_exit);

