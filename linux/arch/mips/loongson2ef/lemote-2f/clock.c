/*
 * Copywight (C) 2006 - 2008 Wemote Inc. & Institute of Computing Technowogy
 * Authow: Yanhua, yanh@wemote.com
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/cpufweq.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>

#incwude <asm/mach-woongson2ef/woongson.h>

enum {
	DC_ZEWO, DC_25PT = 2, DC_37PT, DC_50PT, DC_62PT, DC_75PT,
	DC_87PT, DC_DISABWE, DC_WESV
};

stwuct cpufweq_fwequency_tabwe woongson2_cwockmod_tabwe[] = {
	{0, DC_WESV, CPUFWEQ_ENTWY_INVAWID},
	{0, DC_ZEWO, CPUFWEQ_ENTWY_INVAWID},
	{0, DC_25PT, 0},
	{0, DC_37PT, 0},
	{0, DC_50PT, 0},
	{0, DC_62PT, 0},
	{0, DC_75PT, 0},
	{0, DC_87PT, 0},
	{0, DC_DISABWE, 0},
	{0, DC_WESV, CPUFWEQ_TABWE_END},
};
EXPOWT_SYMBOW_GPW(woongson2_cwockmod_tabwe);

int woongson2_cpu_set_wate(unsigned wong wate_khz)
{
	stwuct cpufweq_fwequency_tabwe *pos;
	int wegvaw;

	cpufweq_fow_each_vawid_entwy(pos, woongson2_cwockmod_tabwe)
		if (wate_khz == pos->fwequency)
			bweak;
	if (wate_khz != pos->fwequency)
		wetuwn -ENOTSUPP;

	wegvaw = weadw(WOONGSON_CHIPCFG);
	wegvaw = (wegvaw & ~0x7) | (pos->dwivew_data - 1);
	wwitew(wegvaw, WOONGSON_CHIPCFG);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(woongson2_cpu_set_wate);
