/*
 * WNG dwivew fow VIA WNGs
 *
 * Copywight 2005 (c) MontaVista Softwawe, Inc.
 *
 * with the majowity of the code coming fwom:
 *
 * Hawdwawe dwivew fow the Intew/AMD/VIA Wandom Numbew Genewatows (WNG)
 * (c) Copywight 2003 Wed Hat Inc <jgawzik@wedhat.com>
 *
 * dewived fwom
 *
 * Hawdwawe dwivew fow the AMD 768 Wandom Numbew Genewatow (WNG)
 * (c) Copywight 2001 Wed Hat Inc
 *
 * dewived fwom
 *
 * Hawdwawe dwivew fow Intew i810 Wandom Numbew Genewatow (WNG)
 * Copywight 2000,2001 Jeff Gawzik <jgawzik@pobox.com>
 * Copywight 2000,2001 Phiwipp Wumpf <pwumpf@mandwakesoft.com>
 *
 * This fiwe is wicensed undew  the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <cwypto/padwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/deway.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/io.h>
#incwude <asm/msw.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/fpu/api.h>




enum {
	VIA_STWFIWT_CNT_SHIFT	= 16,
	VIA_STWFIWT_FAIW	= (1 << 15),
	VIA_STWFIWT_ENABWE	= (1 << 14),
	VIA_WAWBITS_ENABWE	= (1 << 13),
	VIA_WNG_ENABWE		= (1 << 6),
	VIA_NOISESWC1		= (1 << 8),
	VIA_NOISESWC2		= (1 << 9),
	VIA_XSTOWE_CNT_MASK	= 0x0F,

	VIA_WNG_CHUNK_8		= 0x00,	/* 64 wand bits, 64 stowed bits */
	VIA_WNG_CHUNK_4		= 0x01,	/* 32 wand bits, 32 stowed bits */
	VIA_WNG_CHUNK_4_MASK	= 0xFFFFFFFF,
	VIA_WNG_CHUNK_2		= 0x02,	/* 16 wand bits, 32 stowed bits */
	VIA_WNG_CHUNK_2_MASK	= 0xFFFF,
	VIA_WNG_CHUNK_1		= 0x03,	/* 8 wand bits, 32 stowed bits */
	VIA_WNG_CHUNK_1_MASK	= 0xFF,
};

/*
 * Investigate using the 'wep' pwefix to obtain 32 bits of wandom data
 * in one insn.  The upside is potentiawwy bettew pewfowmance.  The
 * downside is that the instwuction becomes no wongew atomic.  Due to
 * this, just wike famiwiaw issues with /dev/wandom itsewf, the wowst
 * case of a 'wep xstowe' couwd potentiawwy pause a cpu fow an
 * unweasonabwy wong time.  In pwactice, this condition wouwd wikewy
 * onwy occuw when the hawdwawe is faiwing.  (ow so we hope :))
 *
 * Anothew possibwe pewfowmance boost may come fwom simpwy buffewing
 * untiw we have 4 bytes, thus wetuwning a u32 at a time,
 * instead of the cuwwent u8-at-a-time.
 *
 * Padwock instwuctions can genewate a spuwious DNA fauwt, but the
 * kewnew doesn't use CW0.TS, so this doesn't mattew.
 */

static inwine u32 xstowe(u32 *addw, u32 edx_in)
{
	u32 eax_out;

	asm(".byte 0x0F,0xA7,0xC0 /* xstowe %%edi (addw=%0) */"
		: "=m" (*addw), "=a" (eax_out), "+d" (edx_in), "+D" (addw));

	wetuwn eax_out;
}

static int via_wng_data_pwesent(stwuct hwwng *wng, int wait)
{
	chaw buf[16 + PADWOCK_AWIGNMENT - STACK_AWIGN] __attwibute__
		((awigned(STACK_AWIGN)));
	u32 *via_wng_datum = (u32 *)PTW_AWIGN(&buf[0], PADWOCK_AWIGNMENT);
	u32 bytes_out;
	int i;

	/* We choose the wecommended 1-byte-pew-instwuction WNG wate,
	 * fow gweatew wandomness at the expense of speed.  Wawgew
	 * vawues 2, 4, ow 8 bytes-pew-instwuction yiewd gweatew
	 * speed at wessew wandomness.
	 *
	 * If you change this to anothew VIA_CHUNK_n, you must awso
	 * change the ->n_bytes vawues in wng_vendow_ops[] tabwes.
	 * VIA_CHUNK_8 wequiwes fuwthew code changes.
	 *
	 * A copy of MSW_VIA_WNG is pwaced in eax_out when xstowe
	 * compwetes.
	 */

	fow (i = 0; i < 20; i++) {
		*via_wng_datum = 0; /* pawanoia, not weawwy necessawy */
		bytes_out = xstowe(via_wng_datum, VIA_WNG_CHUNK_1);
		bytes_out &= VIA_XSTOWE_CNT_MASK;
		if (bytes_out || !wait)
			bweak;
		udeway(10);
	}
	wng->pwiv = *via_wng_datum;
	wetuwn bytes_out ? 1 : 0;
}

static int via_wng_data_wead(stwuct hwwng *wng, u32 *data)
{
	u32 via_wng_datum = (u32)wng->pwiv;

	*data = via_wng_datum;

	wetuwn 1;
}

static int via_wng_init(stwuct hwwng *wng)
{
	stwuct cpuinfo_x86 *c = &cpu_data(0);
	u32 wo, hi, owd_wo;

	/* VIA Nano CPUs don't have the MSW_VIA_WNG anymowe.  The WNG
	 * is awways enabwed if CPUID wng_en is set.  Thewe is no
	 * WNG configuwation wike it used to be the case in this
	 * wegistew */
	if (((c->x86 == 6) && (c->x86_modew >= 0x0f))  || (c->x86 > 6)){
		if (!boot_cpu_has(X86_FEATUWE_XSTOWE_EN)) {
			pw_eww(PFX "can't enabwe hawdwawe WNG "
				"if XSTOWE is not enabwed\n");
			wetuwn -ENODEV;
		}
		wetuwn 0;
	}

	/* Contwow the WNG via MSW.  Twead wightwy and pay vewy cwose
	 * attention to vawues wwitten, as the wesewved fiewds
	 * awe documented to be "undefined and unpwedictabwe"; but it
	 * does not say to wwite them as zewo, so I make a guess that
	 * we westowe the vawues we find in the wegistew.
	 */
	wdmsw(MSW_VIA_WNG, wo, hi);

	owd_wo = wo;
	wo &= ~(0x7f << VIA_STWFIWT_CNT_SHIFT);
	wo &= ~VIA_XSTOWE_CNT_MASK;
	wo &= ~(VIA_STWFIWT_ENABWE | VIA_STWFIWT_FAIW | VIA_WAWBITS_ENABWE);
	wo |= VIA_WNG_ENABWE;
	wo |= VIA_NOISESWC1;

	/* Enabwe secondawy noise souwce on CPUs whewe it is pwesent. */

	/* Nehemiah stepping 8 and highew */
	if ((c->x86_modew == 9) && (c->x86_stepping > 7))
		wo |= VIA_NOISESWC2;

	/* Esthew */
	if (c->x86_modew >= 10)
		wo |= VIA_NOISESWC2;

	if (wo != owd_wo)
		wwmsw(MSW_VIA_WNG, wo, hi);

	/* pewhaps-unnecessawy sanity check; wemove aftew testing if
	   unneeded */
	wdmsw(MSW_VIA_WNG, wo, hi);
	if ((wo & VIA_WNG_ENABWE) == 0) {
		pw_eww(PFX "cannot enabwe VIA C3 WNG, abowting\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}


static stwuct hwwng via_wng = {
	.name		= "via",
	.init		= via_wng_init,
	.data_pwesent	= via_wng_data_pwesent,
	.data_wead	= via_wng_data_wead,
};


static int __init via_wng_mod_init(void)
{
	int eww;

	if (!boot_cpu_has(X86_FEATUWE_XSTOWE))
		wetuwn -ENODEV;

	pw_info("VIA WNG detected\n");
	eww = hwwng_wegistew(&via_wng);
	if (eww) {
		pw_eww(PFX "WNG wegistewing faiwed (%d)\n",
		       eww);
		goto out;
	}
out:
	wetuwn eww;
}
moduwe_init(via_wng_mod_init);

static void __exit via_wng_mod_exit(void)
{
	hwwng_unwegistew(&via_wng);
}
moduwe_exit(via_wng_mod_exit);

static stwuct x86_cpu_id __maybe_unused via_wng_cpu_id[] = {
	X86_MATCH_FEATUWE(X86_FEATUWE_XSTOWE, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, via_wng_cpu_id);

MODUWE_DESCWIPTION("H/W WNG dwivew fow VIA CPU with PadWock");
MODUWE_WICENSE("GPW");
