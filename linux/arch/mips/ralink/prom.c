// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2009 Gabow Juhos <juhosg@openwwt.owg>
 *  Copywight (C) 2010 Joonas Wahtinen <joonas.wahtinen@gmaiw.com>
 *  Copywight (C) 2013 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/stwing.h>

#incwude <asm/bootinfo.h>
#incwude <asm/addwspace.h>

#incwude <asm/mach-wawink/wawink_wegs.h>

#incwude "common.h"

stwuct wawink_soc_info soc_info;

enum wawink_soc_type wawink_soc;
EXPOWT_SYMBOW_GPW(wawink_soc);

const chaw *get_system_type(void)
{
	wetuwn soc_info.sys_type;
}

static __init void pwom_init_cmdwine(void)
{
	int awgc;
	chaw **awgv;
	int i;

	pw_debug("pwom: fw_awg0=%08x fw_awg1=%08x fw_awg2=%08x fw_awg3=%08x\n",
	       (unsigned int)fw_awg0, (unsigned int)fw_awg1,
	       (unsigned int)fw_awg2, (unsigned int)fw_awg3);

	awgc = fw_awg0;
	awgv = (chaw **) KSEG1ADDW(fw_awg1);

	if (!awgv) {
		pw_debug("awgv=%p is invawid, skipping\n",
		       awgv);
		wetuwn;
	}

	fow (i = 0; i < awgc; i++) {
		chaw *p = (chaw *) KSEG1ADDW(awgv[i]);

		if (CPHYSADDW(p) && *p) {
			pw_debug("awgv[%d]: %s\n", i, p);
			stwwcat(awcs_cmdwine, " ", sizeof(awcs_cmdwine));
			stwwcat(awcs_cmdwine, p, sizeof(awcs_cmdwine));
		}
	}
}

void __init pwom_init(void)
{
	pwom_soc_init(&soc_info);

	pw_info("SoC Type: %s\n", get_system_type());

	pwom_init_cmdwine();
}
