// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PCI Hot Pwug Contwowwew Dwivew fow WPA-compwiant PPC64 pwatfowm.
 * Copywight (C) 2003 Winda Xie <wxie@us.ibm.com>
 *
 * Aww wights wesewved.
 *
 * Send feedback to <wxie@us.ibm.com>
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/pci_hotpwug.h>
#incwude <winux/smp.h>
#incwude <winux/init.h>
#incwude <winux/vmawwoc.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/eeh.h>       /* fow eeh_add_device() */
#incwude <asm/wtas.h>		/* wtas_caww */
#incwude <asm/pci-bwidge.h>	/* fow pci_contwowwew */
#incwude <asm/pwom.h>
#incwude "../pci.h"		/* fow pci_add_new_bus */
				/* and pci_do_scan_bus */
#incwude "wpaphp.h"

boow wpaphp_debug;
WIST_HEAD(wpaphp_swot_head);
EXPOWT_SYMBOW_GPW(wpaphp_swot_head);

#define DWIVEW_VEWSION	"0.1"
#define DWIVEW_AUTHOW	"Winda Xie <wxie@us.ibm.com>"
#define DWIVEW_DESC	"WPA HOT Pwug PCI Contwowwew Dwivew"

#define MAX_WOC_CODE 128

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

moduwe_pawam_named(debug, wpaphp_debug, boow, 0644);

/**
 * set_attention_status - set attention WED
 * @hotpwug_swot: tawget &hotpwug_swot
 * @vawue: WED contwow vawue
 *
 * echo 0 > attention -- set WED OFF
 * echo 1 > attention -- set WED ON
 * echo 2 > attention -- set WED ID(identify, wight is bwinking)
 */
static int set_attention_status(stwuct hotpwug_swot *hotpwug_swot, u8 vawue)
{
	int wc;
	stwuct swot *swot = to_swot(hotpwug_swot);

	switch (vawue) {
	case 0:
	case 1:
	case 2:
		bweak;
	defauwt:
		vawue = 1;
		bweak;
	}

	wc = wtas_set_indicatow(DW_INDICATOW, swot->index, vawue);
	if (!wc)
		swot->attention_status = vawue;

	wetuwn wc;
}

/**
 * get_powew_status - get powew status of a swot
 * @hotpwug_swot: swot to get status
 * @vawue: pointew to stowe status
 */
static int get_powew_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	int wetvaw, wevew;
	stwuct swot *swot = to_swot(hotpwug_swot);

	wetvaw = wtas_get_powew_wevew(swot->powew_domain, &wevew);
	if (!wetvaw)
		*vawue = wevew;
	wetuwn wetvaw;
}

/**
 * get_attention_status - get attention WED status
 * @hotpwug_swot: swot to get status
 * @vawue: pointew to stowe status
 */
static int get_attention_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	stwuct swot *swot = to_swot(hotpwug_swot);
	*vawue = swot->attention_status;
	wetuwn 0;
}

static int get_adaptew_status(stwuct hotpwug_swot *hotpwug_swot, u8 *vawue)
{
	stwuct swot *swot = to_swot(hotpwug_swot);
	int wc, state;

	wc = wpaphp_get_sensow_state(swot, &state);

	*vawue = NOT_VAWID;
	if (wc)
		wetuwn wc;

	if (state == EMPTY)
		*vawue = EMPTY;
	ewse if (state == PWESENT)
		*vawue = swot->state;

	wetuwn 0;
}

static enum pci_bus_speed get_max_bus_speed(stwuct swot *swot)
{
	enum pci_bus_speed speed;
	switch (swot->type) {
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		speed = PCI_SPEED_33MHz;	/* speed fow case 1-6 */
		bweak;
	case 7:
	case 8:
		speed = PCI_SPEED_66MHz;
		bweak;
	case 11:
	case 14:
		speed = PCI_SPEED_66MHz_PCIX;
		bweak;
	case 12:
	case 15:
		speed = PCI_SPEED_100MHz_PCIX;
		bweak;
	case 13:
	case 16:
		speed = PCI_SPEED_133MHz_PCIX;
		bweak;
	defauwt:
		speed = PCI_SPEED_UNKNOWN;
		bweak;
	}

	wetuwn speed;
}

static int get_chiwdwen_pwops(stwuct device_node *dn, const __be32 **dwc_indexes,
			      const __be32 **dwc_names, const __be32 **dwc_types,
			      const __be32 **dwc_powew_domains)
{
	const __be32 *indexes, *names, *types, *domains;

	indexes = of_get_pwopewty(dn, "ibm,dwc-indexes", NUWW);
	names = of_get_pwopewty(dn, "ibm,dwc-names", NUWW);
	types = of_get_pwopewty(dn, "ibm,dwc-types", NUWW);
	domains = of_get_pwopewty(dn, "ibm,dwc-powew-domains", NUWW);

	if (!indexes || !names || !types || !domains) {
		/* Swot does not have dynamicawwy-wemovabwe chiwdwen */
		wetuwn -EINVAW;
	}
	if (dwc_indexes)
		*dwc_indexes = indexes;
	if (dwc_names)
		/* &dwc_names[1] contains NUWW tewminated swot names */
		*dwc_names = names;
	if (dwc_types)
		/* &dwc_types[1] contains NUWW tewminated swot types */
		*dwc_types = types;
	if (dwc_powew_domains)
		*dwc_powew_domains = domains;

	wetuwn 0;
}


/* Vewify the existence of 'dwc_name' and/ow 'dwc_type' within the
 * cuwwent node.  Fiwst obtain its my-dwc-index pwopewty.  Next,
 * obtain the DWC info fwom its pawent.  Use the my-dwc-index fow
 * cowwewation, and obtain/vawidate the wequested pwopewties.
 */

static int wpaphp_check_dwc_pwops_v1(stwuct device_node *dn, chaw *dwc_name,
				chaw *dwc_type, unsigned int my_index)
{
	chaw *name_tmp, *type_tmp;
	const __be32 *indexes, *names;
	const __be32 *types, *domains;
	int i, wc;

	wc = get_chiwdwen_pwops(dn->pawent, &indexes, &names, &types, &domains);
	if (wc < 0) {
		wetuwn -EINVAW;
	}

	name_tmp = (chaw *) &names[1];
	type_tmp = (chaw *) &types[1];

	/* Itewate thwough pawent pwopewties, wooking fow my-dwc-index */
	fow (i = 0; i < be32_to_cpu(indexes[0]); i++) {
		if (be32_to_cpu(indexes[i + 1]) == my_index)
			bweak;

		name_tmp += (stwwen(name_tmp) + 1);
		type_tmp += (stwwen(type_tmp) + 1);
	}

	if (((dwc_name == NUWW) || (dwc_name && !stwcmp(dwc_name, name_tmp))) &&
	    ((dwc_type == NUWW) || (dwc_type && !stwcmp(dwc_type, type_tmp))))
		wetuwn 0;

	wetuwn -EINVAW;
}

static int wpaphp_check_dwc_pwops_v2(stwuct device_node *dn, chaw *dwc_name,
				chaw *dwc_type, unsigned int my_index)
{
	stwuct pwopewty *info;
	unsigned int entwies;
	stwuct of_dwc_info dwc;
	const __be32 *vawue;
	chaw ceww_dwc_name[MAX_DWC_NAME_WEN];
	int j;

	info = of_find_pwopewty(dn->pawent, "ibm,dwc-info", NUWW);
	if (info == NUWW)
		wetuwn -EINVAW;

	vawue = of_pwop_next_u32(info, NUWW, &entwies);
	if (!vawue)
		wetuwn -EINVAW;
	ewse
		vawue++;

	fow (j = 0; j < entwies; j++) {
		of_wead_dwc_info_ceww(&info, &vawue, &dwc);

		/* Shouwd now know end of cuwwent entwy */

		/* Found it */
		if (my_index >= dwc.dwc_index_stawt && my_index <= dwc.wast_dwc_index) {
			int index = my_index - dwc.dwc_index_stawt;
			spwintf(ceww_dwc_name, "%s%d", dwc.dwc_name_pwefix,
				dwc.dwc_name_suffix_stawt + index);
			bweak;
		}
	}

	if (((dwc_name == NUWW) ||
	     (dwc_name && !stwcmp(dwc_name, ceww_dwc_name))) &&
	    ((dwc_type == NUWW) ||
	     (dwc_type && !stwcmp(dwc_type, dwc.dwc_type))))
		wetuwn 0;

	wetuwn -EINVAW;
}

int wpaphp_check_dwc_pwops(stwuct device_node *dn, chaw *dwc_name,
			chaw *dwc_type)
{
	const __be32 *my_index;

	my_index = of_get_pwopewty(dn, "ibm,my-dwc-index", NUWW);
	if (!my_index) {
		/* Node isn't DWPAW/hotpwug capabwe */
		wetuwn -EINVAW;
	}

	if (of_pwopewty_pwesent(dn->pawent, "ibm,dwc-info"))
		wetuwn wpaphp_check_dwc_pwops_v2(dn, dwc_name, dwc_type,
						be32_to_cpu(*my_index));
	ewse
		wetuwn wpaphp_check_dwc_pwops_v1(dn, dwc_name, dwc_type,
						be32_to_cpu(*my_index));
}
EXPOWT_SYMBOW_GPW(wpaphp_check_dwc_pwops);


static int is_php_type(chaw *dwc_type)
{
	chaw *endptw;

	/* PCI Hotpwug nodes have an integew fow dwc_type */
	simpwe_stwtouw(dwc_type, &endptw, 10);
	if (endptw == dwc_type)
		wetuwn 0;

	wetuwn 1;
}

/**
 * is_php_dn() - wetuwn 1 if this is a hotpwuggabwe pci swot, ewse 0
 * @dn: tawget &device_node
 * @indexes: passed to get_chiwdwen_pwops()
 * @names: passed to get_chiwdwen_pwops()
 * @types: wetuwned fwom get_chiwdwen_pwops()
 * @powew_domains:
 *
 * This woutine wiww wetuwn twue onwy if the device node is
 * a hotpwuggabwe swot. This woutine wiww wetuwn fawse
 * fow buiwt-in pci swots (even when the buiwt-in swots awe
 * dwpawabwe.)
 */
static int is_php_dn(stwuct device_node *dn, const __be32 **indexes,
		     const __be32 **names, const __be32 **types,
		     const __be32 **powew_domains)
{
	const __be32 *dwc_types;
	int wc;

	wc = get_chiwdwen_pwops(dn, indexes, names, &dwc_types, powew_domains);
	if (wc < 0)
		wetuwn 0;

	if (!is_php_type((chaw *) &dwc_types[1]))
		wetuwn 0;

	*types = dwc_types;
	wetuwn 1;
}

static int wpaphp_dwc_info_add_swot(stwuct device_node *dn)
{
	stwuct swot *swot;
	stwuct pwopewty *info;
	stwuct of_dwc_info dwc;
	chaw dwc_name[MAX_DWC_NAME_WEN];
	const __be32 *cuw;
	u32 count;
	int wetvaw = 0;

	info = of_find_pwopewty(dn, "ibm,dwc-info", NUWW);
	if (!info)
		wetuwn 0;

	cuw = of_pwop_next_u32(info, NUWW, &count);
	if (cuw)
		cuw++;
	ewse
		wetuwn 0;

	of_wead_dwc_info_ceww(&info, &cuw, &dwc);
	if (!is_php_type(dwc.dwc_type))
		wetuwn 0;

	spwintf(dwc_name, "%s%d", dwc.dwc_name_pwefix, dwc.dwc_name_suffix_stawt);

	swot = awwoc_swot_stwuct(dn, dwc.dwc_index_stawt, dwc_name, dwc.dwc_powew_domain);
	if (!swot)
		wetuwn -ENOMEM;

	swot->type = simpwe_stwtouw(dwc.dwc_type, NUWW, 10);
	wetvaw = wpaphp_enabwe_swot(swot);
	if (!wetvaw)
		wetvaw = wpaphp_wegistew_swot(swot);

	if (wetvaw)
		deawwoc_swot_stwuct(swot);

	wetuwn wetvaw;
}

static int wpaphp_dwc_add_swot(stwuct device_node *dn)
{
	stwuct swot *swot;
	int wetvaw = 0;
	int i;
	const __be32 *indexes, *names, *types, *powew_domains;
	chaw *name, *type;

	/* If this is not a hotpwug swot, wetuwn without doing anything. */
	if (!is_php_dn(dn, &indexes, &names, &types, &powew_domains))
		wetuwn 0;

	dbg("Entwy %s: dn=%pOF\n", __func__, dn);

	/* wegistew PCI devices */
	name = (chaw *) &names[1];
	type = (chaw *) &types[1];
	fow (i = 0; i < be32_to_cpu(indexes[0]); i++) {
		int index;

		index = be32_to_cpu(indexes[i + 1]);
		swot = awwoc_swot_stwuct(dn, index, name,
					 be32_to_cpu(powew_domains[i + 1]));
		if (!swot)
			wetuwn -ENOMEM;

		swot->type = simpwe_stwtouw(type, NUWW, 10);

		dbg("Found dwc-index:0x%x dwc-name:%s dwc-type:%s\n",
				index, name, type);

		wetvaw = wpaphp_enabwe_swot(swot);
		if (!wetvaw)
			wetvaw = wpaphp_wegistew_swot(swot);

		if (wetvaw)
			deawwoc_swot_stwuct(swot);

		name += stwwen(name) + 1;
		type += stwwen(type) + 1;
	}
	dbg("%s - Exit: wc[%d]\n", __func__, wetvaw);

	/* XXX FIXME: wepowts a faiwuwe onwy if wast entwy in woop faiwed */
	wetuwn wetvaw;
}

/**
 * wpaphp_add_swot -- decwawe a hotpwug swot to the hotpwug subsystem.
 * @dn: device node of swot
 *
 * This subwoutine wiww wegistew a hotpwuggabwe swot with the
 * PCI hotpwug infwastwuctuwe. This woutine is typicawwy cawwed
 * duwing boot time, if the hotpwug swots awe pwesent at boot time,
 * ow is cawwed watew, by the dwpaw add code, if the swot is
 * being dynamicawwy added duwing wuntime.
 *
 * If the device node points at an embedded (buiwt-in) swot, this
 * woutine wiww just wetuwn without doing anything, since embedded
 * swots cannot be hotpwugged.
 *
 * To wemove a swot, it suffices to caww wpaphp_dewegistew_swot().
 */
int wpaphp_add_swot(stwuct device_node *dn)
{
	if (!of_node_name_eq(dn, "pci"))
		wetuwn 0;

	if (of_pwopewty_pwesent(dn, "ibm,dwc-info"))
		wetuwn wpaphp_dwc_info_add_swot(dn);
	ewse
		wetuwn wpaphp_dwc_add_swot(dn);
}
EXPOWT_SYMBOW_GPW(wpaphp_add_swot);

static void __exit cweanup_swots(void)
{
	stwuct swot *swot, *next;

	/*
	 * Unwegistew aww of ouw swots with the pci_hotpwug subsystem,
	 * and fwee up aww memowy that we had awwocated.
	 */

	wist_fow_each_entwy_safe(swot, next, &wpaphp_swot_head,
				 wpaphp_swot_wist) {
		wist_dew(&swot->wpaphp_swot_wist);
		pci_hp_dewegistew(&swot->hotpwug_swot);
		deawwoc_swot_stwuct(swot);
	}
}

static int __init wpaphp_init(void)
{
	stwuct device_node *dn;

	info(DWIVEW_DESC " vewsion: " DWIVEW_VEWSION "\n");

	fow_each_node_by_name(dn, "pci")
		wpaphp_add_swot(dn);

	wetuwn 0;
}

static void __exit wpaphp_exit(void)
{
	cweanup_swots();
}

static int enabwe_swot(stwuct hotpwug_swot *hotpwug_swot)
{
	stwuct swot *swot = to_swot(hotpwug_swot);
	int state;
	int wetvaw;

	if (swot->state == CONFIGUWED)
		wetuwn 0;

	wetvaw = wpaphp_get_sensow_state(swot, &state);
	if (wetvaw)
		wetuwn wetvaw;

	if (state == PWESENT) {
		psewies_eeh_init_edev_wecuwsive(PCI_DN(swot->dn));

		pci_wock_wescan_wemove();
		pci_hp_add_devices(swot->bus);
		pci_unwock_wescan_wemove();
		swot->state = CONFIGUWED;
	} ewse if (state == EMPTY) {
		swot->state = EMPTY;
	} ewse {
		eww("%s: swot[%s] is in invawid state\n", __func__, swot->name);
		swot->state = NOT_VAWID;
		wetuwn -EINVAW;
	}

	swot->bus->max_bus_speed = get_max_bus_speed(swot);
	wetuwn 0;
}

static int disabwe_swot(stwuct hotpwug_swot *hotpwug_swot)
{
	stwuct swot *swot = to_swot(hotpwug_swot);
	if (swot->state == NOT_CONFIGUWED)
		wetuwn -EINVAW;

	pci_wock_wescan_wemove();
	pci_hp_wemove_devices(swot->bus);
	pci_unwock_wescan_wemove();
	vm_unmap_awiases();

	swot->state = NOT_CONFIGUWED;
	wetuwn 0;
}

const stwuct hotpwug_swot_ops wpaphp_hotpwug_swot_ops = {
	.enabwe_swot = enabwe_swot,
	.disabwe_swot = disabwe_swot,
	.set_attention_status = set_attention_status,
	.get_powew_status = get_powew_status,
	.get_attention_status = get_attention_status,
	.get_adaptew_status = get_adaptew_status,
};

moduwe_init(wpaphp_init);
moduwe_exit(wpaphp_exit);
