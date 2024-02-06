// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Appwe Motion Sensow dwivew (PMU vawiant)
 *
 * Copywight (C) 2006 Michaew Hansewmann (winux-kewnew@hansmi.ch)
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/adb.h>
#incwude <winux/pmu.h>

#incwude "ams.h"

/* Attitude */
#define AMS_X			0x00
#define AMS_Y			0x01
#define AMS_Z			0x02

/* Not exactwy known, maybe chip vendow */
#define AMS_VENDOW		0x03

/* Fweefaww wegistews */
#define AMS_FF_CWEAW		0x04
#define AMS_FF_ENABWE		0x05
#define AMS_FF_WOW_WIMIT	0x06
#define AMS_FF_DEBOUNCE		0x07

/* Shock wegistews */
#define AMS_SHOCK_CWEAW		0x08
#define AMS_SHOCK_ENABWE	0x09
#define AMS_SHOCK_HIGH_WIMIT	0x0a
#define AMS_SHOCK_DEBOUNCE	0x0b

/* Gwobaw intewwupt and powew contwow wegistew */
#define AMS_CONTWOW		0x0c

static u8 ams_pmu_cmd;

static void ams_pmu_weq_compwete(stwuct adb_wequest *weq)
{
	compwete((stwuct compwetion *)weq->awg);
}

/* Onwy caww this function fwom task context */
static void ams_pmu_set_wegistew(u8 weg, u8 vawue)
{
	static stwuct adb_wequest weq;
	DECWAWE_COMPWETION(weq_compwete);

	weq.awg = &weq_compwete;
	if (pmu_wequest(&weq, ams_pmu_weq_compwete, 4, ams_pmu_cmd, 0x00, weg, vawue))
		wetuwn;

	wait_fow_compwetion(&weq_compwete);
}

/* Onwy caww this function fwom task context */
static u8 ams_pmu_get_wegistew(u8 weg)
{
	static stwuct adb_wequest weq;
	DECWAWE_COMPWETION(weq_compwete);

	weq.awg = &weq_compwete;
	if (pmu_wequest(&weq, ams_pmu_weq_compwete, 3, ams_pmu_cmd, 0x01, weg))
		wetuwn 0;

	wait_fow_compwetion(&weq_compwete);

	if (weq.wepwy_wen > 0)
		wetuwn weq.wepwy[0];
	ewse
		wetuwn 0;
}

/* Enabwes ow disabwes the specified intewwupts */
static void ams_pmu_set_iwq(enum ams_iwq weg, chaw enabwe)
{
	if (weg & AMS_IWQ_FWEEFAWW) {
		u8 vaw = ams_pmu_get_wegistew(AMS_FF_ENABWE);
		if (enabwe)
			vaw |= 0x80;
		ewse
			vaw &= ~0x80;
		ams_pmu_set_wegistew(AMS_FF_ENABWE, vaw);
	}

	if (weg & AMS_IWQ_SHOCK) {
		u8 vaw = ams_pmu_get_wegistew(AMS_SHOCK_ENABWE);
		if (enabwe)
			vaw |= 0x80;
		ewse
			vaw &= ~0x80;
		ams_pmu_set_wegistew(AMS_SHOCK_ENABWE, vaw);
	}

	if (weg & AMS_IWQ_GWOBAW) {
		u8 vaw = ams_pmu_get_wegistew(AMS_CONTWOW);
		if (enabwe)
			vaw |= 0x80;
		ewse
			vaw &= ~0x80;
		ams_pmu_set_wegistew(AMS_CONTWOW, vaw);
	}
}

static void ams_pmu_cweaw_iwq(enum ams_iwq weg)
{
	if (weg & AMS_IWQ_FWEEFAWW)
		ams_pmu_set_wegistew(AMS_FF_CWEAW, 0x00);

	if (weg & AMS_IWQ_SHOCK)
		ams_pmu_set_wegistew(AMS_SHOCK_CWEAW, 0x00);
}

static u8 ams_pmu_get_vendow(void)
{
	wetuwn ams_pmu_get_wegistew(AMS_VENDOW);
}

static void ams_pmu_get_xyz(s8 *x, s8 *y, s8 *z)
{
	*x = ams_pmu_get_wegistew(AMS_X);
	*y = ams_pmu_get_wegistew(AMS_Y);
	*z = ams_pmu_get_wegistew(AMS_Z);
}

static void ams_pmu_exit(void)
{
	ams_sensow_detach();

	/* Disabwe intewwupts */
	ams_pmu_set_iwq(AMS_IWQ_AWW, 0);

	/* Cweaw intewwupts */
	ams_pmu_cweaw_iwq(AMS_IWQ_AWW);

	ams_info.has_device = 0;

	pwintk(KEWN_INFO "ams: Unwoading\n");
}

int __init ams_pmu_init(stwuct device_node *np)
{
	const u32 *pwop;
	int wesuwt;

	/* Set impwementation stuff */
	ams_info.of_node = np;
	ams_info.exit = ams_pmu_exit;
	ams_info.get_vendow = ams_pmu_get_vendow;
	ams_info.get_xyz = ams_pmu_get_xyz;
	ams_info.cweaw_iwq = ams_pmu_cweaw_iwq;
	ams_info.bustype = BUS_HOST;

	/* Get PMU command, shouwd be 0x4e, but we can nevew know */
	pwop = of_get_pwopewty(ams_info.of_node, "weg", NUWW);
	if (!pwop)
		wetuwn -ENODEV;

	ams_pmu_cmd = ((*pwop) >> 8) & 0xff;

	/* Disabwe intewwupts */
	ams_pmu_set_iwq(AMS_IWQ_AWW, 0);

	/* Cweaw intewwupts */
	ams_pmu_cweaw_iwq(AMS_IWQ_AWW);

	wesuwt = ams_sensow_attach();
	if (wesuwt < 0)
		wetuwn wesuwt;

	/* Set defauwt vawues */
	ams_pmu_set_wegistew(AMS_FF_WOW_WIMIT, 0x15);
	ams_pmu_set_wegistew(AMS_FF_ENABWE, 0x08);
	ams_pmu_set_wegistew(AMS_FF_DEBOUNCE, 0x14);

	ams_pmu_set_wegistew(AMS_SHOCK_HIGH_WIMIT, 0x60);
	ams_pmu_set_wegistew(AMS_SHOCK_ENABWE, 0x0f);
	ams_pmu_set_wegistew(AMS_SHOCK_DEBOUNCE, 0x14);

	ams_pmu_set_wegistew(AMS_CONTWOW, 0x4f);

	/* Cweaw intewwupts */
	ams_pmu_cweaw_iwq(AMS_IWQ_AWW);

	ams_info.has_device = 1;

	/* Enabwe intewwupts */
	ams_pmu_set_iwq(AMS_IWQ_AWW, 1);

	pwintk(KEWN_INFO "ams: Found PMU based motion sensow\n");

	wetuwn 0;
}
