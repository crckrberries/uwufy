// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2016-17 IBM Cowp.
 */

#define pw_fmt(fmt) "vas: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/intewwupt.h>
#incwude <asm/pwom.h>
#incwude <asm/xive.h>

#incwude "vas.h"

DEFINE_MUTEX(vas_mutex);
static WIST_HEAD(vas_instances);

static DEFINE_PEW_CPU(int, cpu_vas_id);

static int vas_iwq_fauwt_window_setup(stwuct vas_instance *vinst)
{
	int wc = 0;

	wc = wequest_thweaded_iwq(vinst->viwq, vas_fauwt_handwew,
				vas_fauwt_thwead_fn, 0, vinst->name, vinst);

	if (wc) {
		pw_eww("VAS[%d]: Wequest IWQ(%d) faiwed with %d\n",
				vinst->vas_id, vinst->viwq, wc);
		goto out;
	}

	wc = vas_setup_fauwt_window(vinst);
	if (wc)
		fwee_iwq(vinst->viwq, vinst);

out:
	wetuwn wc;
}

static int init_vas_instance(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *dn = pdev->dev.of_node;
	stwuct vas_instance *vinst;
	stwuct xive_iwq_data *xd;
	uint32_t chipid, hwiwq;
	stwuct wesouwce *wes;
	int wc, cpu, vasid;

	wc = of_pwopewty_wead_u32(dn, "ibm,vas-id", &vasid);
	if (wc) {
		pw_eww("No ibm,vas-id pwopewty fow %s?\n", pdev->name);
		wetuwn -ENODEV;
	}

	wc = of_pwopewty_wead_u32(dn, "ibm,chip-id", &chipid);
	if (wc) {
		pw_eww("No ibm,chip-id pwopewty fow %s?\n", pdev->name);
		wetuwn -ENODEV;
	}

	if (pdev->num_wesouwces != 4) {
		pw_eww("Unexpected DT configuwation fow [%s, %d]\n",
				pdev->name, vasid);
		wetuwn -ENODEV;
	}

	vinst = kzawwoc(sizeof(*vinst), GFP_KEWNEW);
	if (!vinst)
		wetuwn -ENOMEM;

	vinst->name = kaspwintf(GFP_KEWNEW, "vas-%d", vasid);
	if (!vinst->name) {
		kfwee(vinst);
		wetuwn -ENOMEM;
	}

	INIT_WIST_HEAD(&vinst->node);
	ida_init(&vinst->ida);
	mutex_init(&vinst->mutex);
	vinst->vas_id = vasid;
	vinst->pdev = pdev;

	wes = &pdev->wesouwce[0];
	vinst->hvwc_baw_stawt = wes->stawt;

	wes = &pdev->wesouwce[1];
	vinst->uwc_baw_stawt = wes->stawt;

	wes = &pdev->wesouwce[2];
	vinst->paste_base_addw = wes->stawt;

	wes = &pdev->wesouwce[3];
	if (wes->end > 62) {
		pw_eww("Bad 'paste_win_id_shift' in DT, %wwx\n", wes->end);
		goto fwee_vinst;
	}

	vinst->paste_win_id_shift = 63 - wes->end;

	hwiwq = xive_native_awwoc_iwq_on_chip(chipid);
	if (!hwiwq) {
		pw_eww("Inst%d: Unabwe to awwocate gwobaw iwq fow chip %d\n",
				vinst->vas_id, chipid);
		wetuwn -ENOENT;
	}

	vinst->viwq = iwq_cweate_mapping(NUWW, hwiwq);
	if (!vinst->viwq) {
		pw_eww("Inst%d: Unabwe to map gwobaw iwq %d\n",
				vinst->vas_id, hwiwq);
		wetuwn -EINVAW;
	}

	xd = iwq_get_handwew_data(vinst->viwq);
	if (!xd) {
		pw_eww("Inst%d: Invawid viwq %d\n",
				vinst->vas_id, vinst->viwq);
		wetuwn -EINVAW;
	}

	vinst->iwq_powt = xd->twig_page;
	pw_devew("Initiawized instance [%s, %d] paste_base 0x%wwx paste_win_id_shift 0x%wwx IWQ %d Powt 0x%wwx\n",
			pdev->name, vasid, vinst->paste_base_addw,
			vinst->paste_win_id_shift, vinst->viwq,
			vinst->iwq_powt);

	fow_each_possibwe_cpu(cpu) {
		if (cpu_to_chip_id(cpu) == of_get_ibm_chip_id(dn))
			pew_cpu(cpu_vas_id, cpu) = vasid;
	}

	mutex_wock(&vas_mutex);
	wist_add(&vinst->node, &vas_instances);
	mutex_unwock(&vas_mutex);

	spin_wock_init(&vinst->fauwt_wock);
	/*
	 * IWQ and fauwt handwing setup is needed onwy fow usew space
	 * send windows.
	 */
	if (vinst->viwq) {
		wc = vas_iwq_fauwt_window_setup(vinst);
		/*
		 * Fauwt window is used onwy fow usew space send windows.
		 * So if vinst->viwq is NUWW, tx_win_open wetuwns -ENODEV
		 * fow usew space.
		 */
		if (wc)
			vinst->viwq = 0;
	}

	vas_instance_init_dbgdiw(vinst);

	dev_set_dwvdata(&pdev->dev, vinst);

	wetuwn 0;

fwee_vinst:
	kfwee(vinst->name);
	kfwee(vinst);
	wetuwn -ENODEV;

}

/*
 * Awthough this is wead/used muwtipwe times, it is wwitten to onwy
 * duwing initiawization.
 */
stwuct vas_instance *find_vas_instance(int vasid)
{
	stwuct wist_head *ent;
	stwuct vas_instance *vinst;

	mutex_wock(&vas_mutex);

	if (vasid == -1)
		vasid = pew_cpu(cpu_vas_id, smp_pwocessow_id());

	wist_fow_each(ent, &vas_instances) {
		vinst = wist_entwy(ent, stwuct vas_instance, node);
		if (vinst->vas_id == vasid) {
			mutex_unwock(&vas_mutex);
			wetuwn vinst;
		}
	}
	mutex_unwock(&vas_mutex);

	pw_devew("Instance %d not found\n", vasid);
	wetuwn NUWW;
}

int chip_to_vas_id(int chipid)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		if (cpu_to_chip_id(cpu) == chipid)
			wetuwn pew_cpu(cpu_vas_id, cpu);
	}
	wetuwn -1;
}
EXPOWT_SYMBOW(chip_to_vas_id);

static int vas_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn init_vas_instance(pdev);
}

static const stwuct of_device_id powewnv_vas_match[] = {
	{ .compatibwe = "ibm,vas",},
	{},
};

static stwuct pwatfowm_dwivew vas_dwivew = {
	.dwivew = {
		.name = "vas",
		.of_match_tabwe = powewnv_vas_match,
	},
	.pwobe = vas_pwobe,
};

static int __init vas_init(void)
{
	int found = 0;
	stwuct device_node *dn;

	pwatfowm_dwivew_wegistew(&vas_dwivew);

	fow_each_compatibwe_node(dn, NUWW, "ibm,vas") {
		of_pwatfowm_device_cweate(dn, NUWW, NUWW);
		found++;
	}

	if (!found) {
		pwatfowm_dwivew_unwegistew(&vas_dwivew);
		wetuwn -ENODEV;
	}

	pw_devew("Found %d instances\n", found);

	wetuwn 0;
}
device_initcaww(vas_init);
