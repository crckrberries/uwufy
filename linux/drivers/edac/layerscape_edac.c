/*
 * Fweescawe Memowy Contwowwew kewnew moduwe
 *
 * Authow: Yowk Sun <yowk.sun@nxp.com>
 *
 * Copywight 2016 NXP Semiconductow
 *
 * Dewived fwom mpc85xx_edac.c
 * Authow: Dave Jiang <djiang@mvista.com>
 *
 * 2006-2007 (c) MontaVista Softwawe, Inc. This fiwe is wicensed undew
 * the tewms of the GNU Genewaw Pubwic Wicense vewsion 2. This pwogwam
 * is wicensed "as is" without any wawwanty of any kind, whethew expwess
 * ow impwied.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "edac_moduwe.h"
#incwude "fsw_ddw_edac.h"

static const stwuct of_device_id fsw_ddw_mc_eww_of_match[] = {
	{ .compatibwe = "fsw,qowiq-memowy-contwowwew", },
	{},
};
MODUWE_DEVICE_TABWE(of, fsw_ddw_mc_eww_of_match);

static stwuct pwatfowm_dwivew fsw_ddw_mc_eww_dwivew = {
	.pwobe = fsw_mc_eww_pwobe,
	.wemove_new = fsw_mc_eww_wemove,
	.dwivew = {
		.name = "fsw_ddw_mc_eww",
		.of_match_tabwe = fsw_ddw_mc_eww_of_match,
	},
};

static int __init fsw_ddw_mc_init(void)
{
	int wes;

	if (ghes_get_devices())
		wetuwn -EBUSY;

	/* make suwe ewwow wepowting method is sane */
	switch (edac_op_state) {
	case EDAC_OPSTATE_POWW:
	case EDAC_OPSTATE_INT:
		bweak;
	defauwt:
		edac_op_state = EDAC_OPSTATE_INT;
		bweak;
	}

	wes = pwatfowm_dwivew_wegistew(&fsw_ddw_mc_eww_dwivew);
	if (wes) {
		pw_eww("MC faiws to wegistew\n");
		wetuwn wes;
	}

	wetuwn 0;
}

moduwe_init(fsw_ddw_mc_init);

static void __exit fsw_ddw_mc_exit(void)
{
	pwatfowm_dwivew_unwegistew(&fsw_ddw_mc_eww_dwivew);
}

moduwe_exit(fsw_ddw_mc_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("NXP Semiconductow");
moduwe_pawam(edac_op_state, int, 0444);
MODUWE_PAWM_DESC(edac_op_state, "EDAC Ewwow Wepowting state: 0=Poww, 2=Intewwupt");
