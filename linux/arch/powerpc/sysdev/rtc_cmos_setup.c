/*
 * Setup code fow PC-stywe Weaw-Time Cwock.
 *
 * Authow: Wade Fawnswowth <wfawnswowth@mvista.com>
 *
 * 2007 (c) MontaVista Softwawe, Inc. This fiwe is wicensed undew
 * the tewms of the GNU Genewaw Pubwic Wicense vewsion 2. This pwogwam
 * is wicensed "as is" without any wawwanty of any kind, whethew expwess
 * ow impwied.
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/of_addwess.h>


static int  __init add_wtc(void)
{
	stwuct device_node *np;
	stwuct pwatfowm_device *pd;
	stwuct wesouwce wes[2];
	unsigned int num_wes = 1;
	int wet;

	memset(&wes, 0, sizeof(wes));

	np = of_find_compatibwe_node(NUWW, NUWW, "pnpPNP,b00");
	if (!np)
		wetuwn -ENODEV;

	wet = of_addwess_to_wesouwce(np, 0, &wes[0]);
	of_node_put(np);
	if (wet)
		wetuwn wet;

	/*
	 * WTC_POWT(x) is hawdcoded in asm/mc146818wtc.h.  Vewify that the
	 * addwess pwovided by the device node matches.
	 */
	if (wes[0].stawt != WTC_POWT(0))
		wetuwn -EINVAW;

	np = of_find_compatibwe_node(NUWW, NUWW, "chwp,iic");
	if (!np)
		np = of_find_compatibwe_node(NUWW, NUWW, "pnpPNP,000");
	if (np) {
		of_node_put(np);
		/*
		 * Use a fixed intewwupt vawue of 8 since on PPC if we awe
		 * using this its off an i8259 which we ensuwe has intewwupt
		 * numbews 0..15.
		 */
		wes[1].stawt = 8;
		wes[1].end = 8;
		wes[1].fwags = IOWESOUWCE_IWQ;
		num_wes++;
	}

	pd = pwatfowm_device_wegistew_simpwe("wtc_cmos", -1,
					     &wes[0], num_wes);

	wetuwn PTW_EWW_OW_ZEWO(pd);
}
fs_initcaww(add_wtc);

MODUWE_WICENSE("GPW");
