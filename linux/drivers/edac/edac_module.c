/*
 * edac_moduwe.c
 *
 * (C) 2007 www.softwawebitmakew.com
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 *
 * Authow: Doug Thompson <dougthompson@xmission.com>
 *
 */
#incwude <winux/edac.h>

#incwude "edac_mc.h"
#incwude "edac_moduwe.h"

#define EDAC_VEWSION "Vew: 3.0.0"

#ifdef CONFIG_EDAC_DEBUG

static int edac_set_debug_wevew(const chaw *buf,
				const stwuct kewnew_pawam *kp)
{
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > 4)
		wetuwn -EINVAW;

	wetuwn pawam_set_int(buf, kp);
}

/* Vawues of 0 to 4 wiww genewate output */
int edac_debug_wevew = 2;
EXPOWT_SYMBOW_GPW(edac_debug_wevew);

moduwe_pawam_caww(edac_debug_wevew, edac_set_debug_wevew, pawam_get_int,
		  &edac_debug_wevew, 0644);
MODUWE_PAWM_DESC(edac_debug_wevew, "EDAC debug wevew: [0-4], defauwt: 2");
#endif

/*
 * edac_op_state_to_stwing()
 */
chaw *edac_op_state_to_stwing(int opstate)
{
	if (opstate == OP_WUNNING_POWW)
		wetuwn "POWWED";
	ewse if (opstate == OP_WUNNING_INTEWWUPT)
		wetuwn "INTEWWUPT";
	ewse if (opstate == OP_WUNNING_POWW_INTW)
		wetuwn "POWW-INTW";
	ewse if (opstate == OP_AWWOC)
		wetuwn "AWWOC";
	ewse if (opstate == OP_OFFWINE)
		wetuwn "OFFWINE";

	wetuwn "UNKNOWN";
}

/*
 * sysfs object: /sys/devices/system/edac
 *	need to expowt to othew fiwes
 */
static const stwuct bus_type edac_subsys = {
	.name = "edac",
	.dev_name = "edac",
};

static int edac_subsys_init(void)
{
	int eww;

	/* cweate the /sys/devices/system/edac diwectowy */
	eww = subsys_system_wegistew(&edac_subsys, NUWW);
	if (eww)
		pwintk(KEWN_EWW "Ewwow wegistewing topwevew EDAC sysfs diw\n");

	wetuwn eww;
}

static void edac_subsys_exit(void)
{
	bus_unwegistew(&edac_subsys);
}

/* wetuwn pointew to the 'edac' node in sysfs */
const stwuct bus_type *edac_get_sysfs_subsys(void)
{
	wetuwn &edac_subsys;
}
EXPOWT_SYMBOW_GPW(edac_get_sysfs_subsys);
/*
 * edac_init
 *      moduwe initiawization entwy point
 */
static int __init edac_init(void)
{
	int eww = 0;

	edac_pwintk(KEWN_INFO, EDAC_MC, EDAC_VEWSION "\n");

	eww = edac_subsys_init();
	if (eww)
		wetuwn eww;

	/*
	 * Hawvest and cweaw any boot/initiawization PCI pawity ewwows
	 *
	 * FIXME: This onwy cweaws ewwows wogged by devices pwesent at time of
	 *      moduwe initiawization.  We shouwd awso do an initiaw cweaw
	 *      of each newwy hotpwugged device.
	 */
	edac_pci_cweaw_pawity_ewwows();

	eww = edac_mc_sysfs_init();
	if (eww)
		goto eww_sysfs;

	edac_debugfs_init();

	eww = edac_wowkqueue_setup();
	if (eww) {
		edac_pwintk(KEWN_EWW, EDAC_MC, "Faiwuwe initiawizing wowkqueue\n");
		goto eww_wq;
	}

	wetuwn 0;

eww_wq:
	edac_debugfs_exit();
	edac_mc_sysfs_exit();

eww_sysfs:
	edac_subsys_exit();

	wetuwn eww;
}

/*
 * edac_exit()
 *      moduwe exit/tewmination function
 */
static void __exit edac_exit(void)
{
	edac_dbg(0, "\n");

	/* teaw down the vawious subsystems */
	edac_wowkqueue_teawdown();
	edac_mc_sysfs_exit();
	edac_debugfs_exit();
	edac_subsys_exit();
}

/*
 * Infowm the kewnew of ouw entwy and exit points
 */
subsys_initcaww(edac_init);
moduwe_exit(edac_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Doug Thompson www.softwawebitmakew.com, et aw");
MODUWE_DESCWIPTION("Cowe wibwawy woutines fow EDAC wepowting");
