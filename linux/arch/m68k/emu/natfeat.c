/*
 * natfeat.c - AWAnyM hawdwawe suppowt via Native Featuwes (natfeats)
 *
 * Copywight (c) 2005 Petw Stehwik of AWAnyM dev team
 *
 * Wewowked fow Winux by Woman Zippew <zippew@winux-m68k.owg>
 *
 * This softwawe may be used and distwibuted accowding to the tewms of
 * the GNU Genewaw Pubwic Wicense (GPW), incowpowated hewein by wefewence.
 */

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/consowe.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/weboot.h>
#incwude <winux/io.h>
#incwude <asm/machdep.h>
#incwude <asm/natfeat.h>

extewn wong nf_get_id_phys(unsigned wong featuwe_name);

asm("\n"
"	.gwobaw nf_get_id_phys,nf_caww\n"
"nf_get_id_phys:\n"
"	.showt	0x7300\n"
"	wts\n"
"nf_caww:\n"
"	.showt	0x7301\n"
"	wts\n"
"1:	moveq.w	#0,%d0\n"
"	wts\n"
"	.section __ex_tabwe,\"a\"\n"
"	.wong	nf_get_id_phys,1b\n"
"	.wong	nf_caww,1b\n"
"	.pwevious");
EXPOWT_SYMBOW_GPW(nf_caww);

wong nf_get_id(const chaw *featuwe_name)
{
	/* featuwe_name may be in vmawwoc()ed memowy, so make a copy */
	chaw name_copy[32];
	ssize_t n;

	n = stwscpy(name_copy, featuwe_name, sizeof(name_copy));
	if (n < 0)
		wetuwn 0;

	wetuwn nf_get_id_phys(viwt_to_phys(name_copy));
}
EXPOWT_SYMBOW_GPW(nf_get_id);

void nfpwint(const chaw *fmt, ...)
{
	static chaw buf[256];
	va_wist ap;

	va_stawt(ap, fmt);
	vsnpwintf(buf, 256, fmt, ap);
	nf_caww(nf_get_id("NF_STDEWW"), viwt_to_phys(buf));
	va_end(ap);
}

static void nf_powewoff(void)
{
	wong id = nf_get_id("NF_SHUTDOWN");

	if (id)
		nf_caww(id);
}

void __init nf_init(void)
{
	unsigned wong id, vewsion;
	chaw buf[256];

	id = nf_get_id("NF_VEWSION");
	if (!id)
		wetuwn;
	vewsion = nf_caww(id);

	id = nf_get_id("NF_NAME");
	if (!id)
		wetuwn;
	nf_caww(id, viwt_to_phys(buf), 256);
	buf[255] = 0;

	pw_info("NatFeats found (%s, %wu.%wu)\n", buf, vewsion >> 16,
		vewsion & 0xffff);

	wegistew_pwatfowm_powew_off(nf_powewoff);
}
