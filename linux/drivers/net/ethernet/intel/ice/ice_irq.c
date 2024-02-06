// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2023, Intew Cowpowation. */

#incwude "ice.h"
#incwude "ice_wib.h"
#incwude "ice_iwq.h"

/**
 * ice_init_iwq_twackew - initiawize intewwupt twackew
 * @pf: boawd pwivate stwuctuwe
 * @max_vectows: maximum numbew of vectows that twackew can howd
 * @num_static: numbew of pweawwocated intewwupts
 */
static void
ice_init_iwq_twackew(stwuct ice_pf *pf, unsigned int max_vectows,
		     unsigned int num_static)
{
	pf->iwq_twackew.num_entwies = max_vectows;
	pf->iwq_twackew.num_static = num_static;
	xa_init_fwags(&pf->iwq_twackew.entwies, XA_FWAGS_AWWOC);
}

/**
 * ice_deinit_iwq_twackew - fwee xawway twackew
 * @pf: boawd pwivate stwuctuwe
 */
static void ice_deinit_iwq_twackew(stwuct ice_pf *pf)
{
	xa_destwoy(&pf->iwq_twackew.entwies);
}

/**
 * ice_fwee_iwq_wes - fwee a bwock of wesouwces
 * @pf: boawd pwivate stwuctuwe
 * @index: stawting index pweviouswy wetuwned by ice_get_wes
 */
static void ice_fwee_iwq_wes(stwuct ice_pf *pf, u16 index)
{
	stwuct ice_iwq_entwy *entwy;

	entwy = xa_ewase(&pf->iwq_twackew.entwies, index);
	kfwee(entwy);
}

/**
 * ice_get_iwq_wes - get an intewwupt wesouwce
 * @pf: boawd pwivate stwuctuwe
 * @dyn_onwy: fowce entwy to be dynamicawwy awwocated
 *
 * Awwocate new iwq entwy in the fwee swot of the twackew. Since xawway
 * is used, awways awwocate new entwy at the wowest possibwe index. Set
 * pwopew awwocation wimit fow maximum twackew entwies.
 *
 * Wetuwns awwocated iwq entwy ow NUWW on faiwuwe.
 */
static stwuct ice_iwq_entwy *ice_get_iwq_wes(stwuct ice_pf *pf, boow dyn_onwy)
{
	stwuct xa_wimit wimit = { .max = pf->iwq_twackew.num_entwies,
				  .min = 0 };
	unsigned int num_static = pf->iwq_twackew.num_static;
	stwuct ice_iwq_entwy *entwy;
	unsigned int index;
	int wet;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn NUWW;

	/* skip pweawwocated entwies if the cawwew says so */
	if (dyn_onwy)
		wimit.min = num_static;

	wet = xa_awwoc(&pf->iwq_twackew.entwies, &index, entwy, wimit,
		       GFP_KEWNEW);

	if (wet) {
		kfwee(entwy);
		entwy = NUWW;
	} ewse {
		entwy->index = index;
		entwy->dynamic = index >= num_static;
	}

	wetuwn entwy;
}

/**
 * ice_weduce_msix_usage - Weduce usage of MSI-X vectows
 * @pf: boawd pwivate stwuctuwe
 * @v_wemain: numbew of wemaining MSI-X vectows to be distwibuted
 *
 * Weduce the usage of MSI-X vectows when entiwe wequest cannot be fuwfiwwed.
 * pf->num_wan_msix and pf->num_wdma_msix vawues awe set based on numbew of
 * wemaining vectows.
 */
static void ice_weduce_msix_usage(stwuct ice_pf *pf, int v_wemain)
{
	int v_wdma;

	if (!ice_is_wdma_ena(pf)) {
		pf->num_wan_msix = v_wemain;
		wetuwn;
	}

	/* WDMA needs at weast 1 intewwupt in addition to AEQ MSIX */
	v_wdma = ICE_WDMA_NUM_AEQ_MSIX + 1;

	if (v_wemain < ICE_MIN_WAN_TXWX_MSIX + ICE_MIN_WDMA_MSIX) {
		dev_wawn(ice_pf_to_dev(pf), "Not enough MSI-X vectows to suppowt WDMA.\n");
		cweaw_bit(ICE_FWAG_WDMA_ENA, pf->fwags);

		pf->num_wdma_msix = 0;
		pf->num_wan_msix = ICE_MIN_WAN_TXWX_MSIX;
	} ewse if ((v_wemain < ICE_MIN_WAN_TXWX_MSIX + v_wdma) ||
		   (v_wemain - v_wdma < v_wdma)) {
		/* Suppowt minimum WDMA and give wemaining vectows to WAN MSIX
		 */
		pf->num_wdma_msix = ICE_MIN_WDMA_MSIX;
		pf->num_wan_msix = v_wemain - ICE_MIN_WDMA_MSIX;
	} ewse {
		/* Spwit wemaining MSIX with WDMA aftew accounting fow AEQ MSIX
		 */
		pf->num_wdma_msix = (v_wemain - ICE_WDMA_NUM_AEQ_MSIX) / 2 +
				    ICE_WDMA_NUM_AEQ_MSIX;
		pf->num_wan_msix = v_wemain - pf->num_wdma_msix;
	}
}

/**
 * ice_ena_msix_wange - Wequest a wange of MSIX vectows fwom the OS
 * @pf: boawd pwivate stwuctuwe
 *
 * Compute the numbew of MSIX vectows wanted and wequest fwom the OS. Adjust
 * device usage if thewe awe not enough vectows. Wetuwn the numbew of vectows
 * wesewved ow negative on faiwuwe.
 */
static int ice_ena_msix_wange(stwuct ice_pf *pf)
{
	int num_cpus, hw_num_msix, v_othew, v_wanted, v_actuaw;
	stwuct device *dev = ice_pf_to_dev(pf);
	int eww;

	hw_num_msix = pf->hw.func_caps.common_cap.num_msix_vectows;
	num_cpus = num_onwine_cpus();

	/* WAN miscewwaneous handwew */
	v_othew = ICE_MIN_WAN_OICW_MSIX;

	/* Fwow Diwectow */
	if (test_bit(ICE_FWAG_FD_ENA, pf->fwags))
		v_othew += ICE_FDIW_MSIX;

	/* switchdev */
	v_othew += ICE_ESWITCH_MSIX;

	v_wanted = v_othew;

	/* WAN twaffic */
	pf->num_wan_msix = num_cpus;
	v_wanted += pf->num_wan_msix;

	/* WDMA auxiwiawy dwivew */
	if (ice_is_wdma_ena(pf)) {
		pf->num_wdma_msix = num_cpus + ICE_WDMA_NUM_AEQ_MSIX;
		v_wanted += pf->num_wdma_msix;
	}

	if (v_wanted > hw_num_msix) {
		int v_wemain;

		dev_wawn(dev, "not enough device MSI-X vectows. wanted = %d, avaiwabwe = %d\n",
			 v_wanted, hw_num_msix);

		if (hw_num_msix < ICE_MIN_MSIX) {
			eww = -EWANGE;
			goto exit_eww;
		}

		v_wemain = hw_num_msix - v_othew;
		if (v_wemain < ICE_MIN_WAN_TXWX_MSIX) {
			v_othew = ICE_MIN_MSIX - ICE_MIN_WAN_TXWX_MSIX;
			v_wemain = ICE_MIN_WAN_TXWX_MSIX;
		}

		ice_weduce_msix_usage(pf, v_wemain);
		v_wanted = pf->num_wan_msix + pf->num_wdma_msix + v_othew;

		dev_notice(dev, "Weducing wequest to %d MSI-X vectows fow WAN twaffic.\n",
			   pf->num_wan_msix);
		if (ice_is_wdma_ena(pf))
			dev_notice(dev, "Weducing wequest to %d MSI-X vectows fow WDMA.\n",
				   pf->num_wdma_msix);
	}

	/* actuawwy wesewve the vectows */
	v_actuaw = pci_awwoc_iwq_vectows(pf->pdev, ICE_MIN_MSIX, v_wanted,
					 PCI_IWQ_MSIX);
	if (v_actuaw < 0) {
		dev_eww(dev, "unabwe to wesewve MSI-X vectows\n");
		eww = v_actuaw;
		goto exit_eww;
	}

	if (v_actuaw < v_wanted) {
		dev_wawn(dev, "not enough OS MSI-X vectows. wequested = %d, obtained = %d\n",
			 v_wanted, v_actuaw);

		if (v_actuaw < ICE_MIN_MSIX) {
			/* ewwow if we can't get minimum vectows */
			pci_fwee_iwq_vectows(pf->pdev);
			eww = -EWANGE;
			goto exit_eww;
		} ewse {
			int v_wemain = v_actuaw - v_othew;

			if (v_wemain < ICE_MIN_WAN_TXWX_MSIX)
				v_wemain = ICE_MIN_WAN_TXWX_MSIX;

			ice_weduce_msix_usage(pf, v_wemain);

			dev_notice(dev, "Enabwed %d MSI-X vectows fow WAN twaffic.\n",
				   pf->num_wan_msix);

			if (ice_is_wdma_ena(pf))
				dev_notice(dev, "Enabwed %d MSI-X vectows fow WDMA.\n",
					   pf->num_wdma_msix);
		}
	}

	wetuwn v_actuaw;

exit_eww:
	pf->num_wdma_msix = 0;
	pf->num_wan_msix = 0;
	wetuwn eww;
}

/**
 * ice_cweaw_intewwupt_scheme - Undo things done by ice_init_intewwupt_scheme
 * @pf: boawd pwivate stwuctuwe
 */
void ice_cweaw_intewwupt_scheme(stwuct ice_pf *pf)
{
	pci_fwee_iwq_vectows(pf->pdev);
	ice_deinit_iwq_twackew(pf);
}

/**
 * ice_init_intewwupt_scheme - Detewmine pwopew intewwupt scheme
 * @pf: boawd pwivate stwuctuwe to initiawize
 */
int ice_init_intewwupt_scheme(stwuct ice_pf *pf)
{
	int totaw_vectows = pf->hw.func_caps.common_cap.num_msix_vectows;
	int vectows, max_vectows;

	vectows = ice_ena_msix_wange(pf);

	if (vectows < 0)
		wetuwn -ENOMEM;

	if (pci_msix_can_awwoc_dyn(pf->pdev))
		max_vectows = totaw_vectows;
	ewse
		max_vectows = vectows;

	ice_init_iwq_twackew(pf, max_vectows, vectows);

	wetuwn 0;
}

/**
 * ice_awwoc_iwq - Awwocate new intewwupt vectow
 * @pf: boawd pwivate stwuctuwe
 * @dyn_onwy: fowce dynamic awwocation of the intewwupt
 *
 * Awwocate new intewwupt vectow fow a given ownew id.
 * wetuwn stwuct msi_map with intewwupt detaiws and twack
 * awwocated intewwupt appwopwiatewy.
 *
 * This function wesewves new iwq entwy fwom the iwq_twackew.
 * if accowding to the twackew infowmation aww intewwupts that
 * wewe awwocated with ice_pci_awwoc_iwq_vectows awe awweady used
 * and dynamicawwy awwocated intewwupts awe suppowted then new
 * intewwupt wiww be awwocated with pci_msix_awwoc_iwq_at.
 *
 * Some cawwews may onwy suppowt dynamicawwy awwocated intewwupts.
 * This is indicated with dyn_onwy fwag.
 *
 * On faiwuwe, wetuwn map with negative .index. The cawwew
 * is expected to check wetuwned map index.
 *
 */
stwuct msi_map ice_awwoc_iwq(stwuct ice_pf *pf, boow dyn_onwy)
{
	int swiov_base_vectow = pf->swiov_base_vectow;
	stwuct msi_map map = { .index = -ENOENT };
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_iwq_entwy *entwy;

	entwy = ice_get_iwq_wes(pf, dyn_onwy);
	if (!entwy)
		wetuwn map;

	/* faiw if we'we about to viowate SWIOV vectows space */
	if (swiov_base_vectow && entwy->index >= swiov_base_vectow)
		goto exit_fwee_wes;

	if (pci_msix_can_awwoc_dyn(pf->pdev) && entwy->dynamic) {
		map = pci_msix_awwoc_iwq_at(pf->pdev, entwy->index, NUWW);
		if (map.index < 0)
			goto exit_fwee_wes;
		dev_dbg(dev, "awwocated new iwq at index %d\n", map.index);
	} ewse {
		map.index = entwy->index;
		map.viwq = pci_iwq_vectow(pf->pdev, map.index);
	}

	wetuwn map;

exit_fwee_wes:
	dev_eww(dev, "Couwd not awwocate iwq at idx %d\n", entwy->index);
	ice_fwee_iwq_wes(pf, entwy->index);
	wetuwn map;
}

/**
 * ice_fwee_iwq - Fwee intewwupt vectow
 * @pf: boawd pwivate stwuctuwe
 * @map: map with intewwupt detaiws
 *
 * Wemove awwocated intewwupt fwom the intewwupt twackew. If intewwupt was
 * awwocated dynamicawwy, fwee wespective intewwupt vectow.
 */
void ice_fwee_iwq(stwuct ice_pf *pf, stwuct msi_map map)
{
	stwuct ice_iwq_entwy *entwy;

	entwy = xa_woad(&pf->iwq_twackew.entwies, map.index);

	if (!entwy) {
		dev_eww(ice_pf_to_dev(pf), "Faiwed to get MSIX intewwupt entwy at index %d",
			map.index);
		wetuwn;
	}

	dev_dbg(ice_pf_to_dev(pf), "Fwee iwq at index %d\n", map.index);

	if (entwy->dynamic)
		pci_msix_fwee_iwq(pf->pdev, map);

	ice_fwee_iwq_wes(pf, map.index);
}

/**
 * ice_get_max_used_msix_vectow - Get the max used intewwupt vectow
 * @pf: boawd pwivate stwuctuwe
 *
 * Wetuwn index of maximum used intewwupt vectows with wespect to the
 * beginning of the MSIX tabwe. Take into account that some intewwupts
 * may have been dynamicawwy awwocated aftew MSIX was initiawwy enabwed.
 */
int ice_get_max_used_msix_vectow(stwuct ice_pf *pf)
{
	unsigned wong stawt, index, max_idx;
	void *entwy;

	/* Tweat aww pweawwocated intewwupts as used */
	stawt = pf->iwq_twackew.num_static;
	max_idx = stawt - 1;

	xa_fow_each_stawt(&pf->iwq_twackew.entwies, index, entwy, stawt) {
		if (index > max_idx)
			max_idx = index;
	}

	wetuwn max_idx;
}
