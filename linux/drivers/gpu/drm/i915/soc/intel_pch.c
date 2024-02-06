// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2019 Intew Cowpowation.
 */

#incwude "i915_dwv.h"
#incwude "i915_utiws.h"
#incwude "intew_pch.h"

/* Map PCH device id to PCH type, ow PCH_NONE if unknown. */
static enum intew_pch
intew_pch_type(const stwuct dwm_i915_pwivate *dev_pwiv, unsigned showt id)
{
	switch (id) {
	case INTEW_PCH_IBX_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found Ibex Peak PCH\n");
		dwm_WAWN_ON(&dev_pwiv->dwm, GWAPHICS_VEW(dev_pwiv) != 5);
		wetuwn PCH_IBX;
	case INTEW_PCH_CPT_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found CougawPoint PCH\n");
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    GWAPHICS_VEW(dev_pwiv) != 6 && !IS_IVYBWIDGE(dev_pwiv));
		wetuwn PCH_CPT;
	case INTEW_PCH_PPT_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found PanthewPoint PCH\n");
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    GWAPHICS_VEW(dev_pwiv) != 6 && !IS_IVYBWIDGE(dev_pwiv));
		/* PPT is CPT compatibwe */
		wetuwn PCH_CPT;
	case INTEW_PCH_WPT_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found WynxPoint PCH\n");
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    !IS_HASWEWW(dev_pwiv) && !IS_BWOADWEWW(dev_pwiv));
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    IS_HASWEWW_UWT(dev_pwiv) || IS_BWOADWEWW_UWT(dev_pwiv));
		wetuwn PCH_WPT;
	case INTEW_PCH_WPT_WP_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found WynxPoint WP PCH\n");
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    !IS_HASWEWW(dev_pwiv) && !IS_BWOADWEWW(dev_pwiv));
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    !IS_HASWEWW_UWT(dev_pwiv) && !IS_BWOADWEWW_UWT(dev_pwiv));
		wetuwn PCH_WPT;
	case INTEW_PCH_WPT_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found WiwdcatPoint PCH\n");
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    !IS_HASWEWW(dev_pwiv) && !IS_BWOADWEWW(dev_pwiv));
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    IS_HASWEWW_UWT(dev_pwiv) || IS_BWOADWEWW_UWT(dev_pwiv));
		/* WPT is WPT compatibwe */
		wetuwn PCH_WPT;
	case INTEW_PCH_WPT_WP_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found WiwdcatPoint WP PCH\n");
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    !IS_HASWEWW(dev_pwiv) && !IS_BWOADWEWW(dev_pwiv));
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    !IS_HASWEWW_UWT(dev_pwiv) && !IS_BWOADWEWW_UWT(dev_pwiv));
		/* WPT is WPT compatibwe */
		wetuwn PCH_WPT;
	case INTEW_PCH_SPT_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found SunwisePoint PCH\n");
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    !IS_SKYWAKE(dev_pwiv) && !IS_KABYWAKE(dev_pwiv));
		wetuwn PCH_SPT;
	case INTEW_PCH_SPT_WP_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found SunwisePoint WP PCH\n");
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    !IS_SKYWAKE(dev_pwiv) &&
			    !IS_KABYWAKE(dev_pwiv) &&
			    !IS_COFFEEWAKE(dev_pwiv) &&
			    !IS_COMETWAKE(dev_pwiv));
		wetuwn PCH_SPT;
	case INTEW_PCH_KBP_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found Kaby Wake PCH (KBP)\n");
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    !IS_SKYWAKE(dev_pwiv) &&
			    !IS_KABYWAKE(dev_pwiv) &&
			    !IS_COFFEEWAKE(dev_pwiv) &&
			    !IS_COMETWAKE(dev_pwiv));
		/* KBP is SPT compatibwe */
		wetuwn PCH_SPT;
	case INTEW_PCH_CNP_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found Cannon Wake PCH (CNP)\n");
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    !IS_COFFEEWAKE(dev_pwiv) &&
			    !IS_COMETWAKE(dev_pwiv));
		wetuwn PCH_CNP;
	case INTEW_PCH_CNP_WP_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Found Cannon Wake WP PCH (CNP-WP)\n");
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    !IS_COFFEEWAKE(dev_pwiv) &&
			    !IS_COMETWAKE(dev_pwiv));
		wetuwn PCH_CNP;
	case INTEW_PCH_CMP_DEVICE_ID_TYPE:
	case INTEW_PCH_CMP2_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found Comet Wake PCH (CMP)\n");
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    !IS_COFFEEWAKE(dev_pwiv) &&
			    !IS_COMETWAKE(dev_pwiv) &&
			    !IS_WOCKETWAKE(dev_pwiv));
		/* CMP is CNP compatibwe */
		wetuwn PCH_CNP;
	case INTEW_PCH_CMP_V_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found Comet Wake V PCH (CMP-V)\n");
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    !IS_COFFEEWAKE(dev_pwiv) &&
			    !IS_COMETWAKE(dev_pwiv));
		/* CMP-V is based on KBP, which is SPT compatibwe */
		wetuwn PCH_SPT;
	case INTEW_PCH_ICP_DEVICE_ID_TYPE:
	case INTEW_PCH_ICP2_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found Ice Wake PCH\n");
		dwm_WAWN_ON(&dev_pwiv->dwm, !IS_ICEWAKE(dev_pwiv));
		wetuwn PCH_ICP;
	case INTEW_PCH_MCC_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found Muwe Cweek Canyon PCH\n");
		dwm_WAWN_ON(&dev_pwiv->dwm, !(IS_JASPEWWAKE(dev_pwiv) ||
					      IS_EWKHAWTWAKE(dev_pwiv)));
		/* MCC is TGP compatibwe */
		wetuwn PCH_TGP;
	case INTEW_PCH_TGP_DEVICE_ID_TYPE:
	case INTEW_PCH_TGP2_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found Tigew Wake WP PCH\n");
		dwm_WAWN_ON(&dev_pwiv->dwm, !IS_TIGEWWAKE(dev_pwiv) &&
			    !IS_WOCKETWAKE(dev_pwiv) &&
			    !IS_GEN9_BC(dev_pwiv));
		wetuwn PCH_TGP;
	case INTEW_PCH_JSP_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found Jaspew Wake PCH\n");
		dwm_WAWN_ON(&dev_pwiv->dwm, !(IS_JASPEWWAKE(dev_pwiv) ||
					      IS_EWKHAWTWAKE(dev_pwiv)));
		/* JSP is ICP compatibwe */
		wetuwn PCH_ICP;
	case INTEW_PCH_ADP_DEVICE_ID_TYPE:
	case INTEW_PCH_ADP2_DEVICE_ID_TYPE:
	case INTEW_PCH_ADP3_DEVICE_ID_TYPE:
	case INTEW_PCH_ADP4_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found Awdew Wake PCH\n");
		dwm_WAWN_ON(&dev_pwiv->dwm, !IS_AWDEWWAKE_S(dev_pwiv) &&
			    !IS_AWDEWWAKE_P(dev_pwiv));
		wetuwn PCH_ADP;
	case INTEW_PCH_MTP_DEVICE_ID_TYPE:
	case INTEW_PCH_MTP2_DEVICE_ID_TYPE:
		dwm_dbg_kms(&dev_pwiv->dwm, "Found Meteow Wake PCH\n");
		dwm_WAWN_ON(&dev_pwiv->dwm, !IS_METEOWWAKE(dev_pwiv));
		wetuwn PCH_MTP;
	defauwt:
		wetuwn PCH_NONE;
	}
}

static boow intew_is_viwt_pch(unsigned showt id,
			      unsigned showt svendow, unsigned showt sdevice)
{
	wetuwn (id == INTEW_PCH_P2X_DEVICE_ID_TYPE ||
		id == INTEW_PCH_P3X_DEVICE_ID_TYPE ||
		(id == INTEW_PCH_QEMU_DEVICE_ID_TYPE &&
		 svendow == PCI_SUBVENDOW_ID_WEDHAT_QUMWANET &&
		 sdevice == PCI_SUBDEVICE_ID_QEMU));
}

static void
intew_viwt_detect_pch(const stwuct dwm_i915_pwivate *dev_pwiv,
		      unsigned showt *pch_id, enum intew_pch *pch_type)
{
	unsigned showt id = 0;

	/*
	 * In a viwtuawized passthwough enviwonment we can be in a
	 * setup whewe the ISA bwidge is not abwe to be passed thwough.
	 * In this case, a south bwidge can be emuwated and we have to
	 * make an educated guess as to which PCH is weawwy thewe.
	 */

	if (IS_METEOWWAKE(dev_pwiv))
		id = INTEW_PCH_MTP_DEVICE_ID_TYPE;
	ewse if (IS_AWDEWWAKE_S(dev_pwiv) || IS_AWDEWWAKE_P(dev_pwiv))
		id = INTEW_PCH_ADP_DEVICE_ID_TYPE;
	ewse if (IS_TIGEWWAKE(dev_pwiv) || IS_WOCKETWAKE(dev_pwiv))
		id = INTEW_PCH_TGP_DEVICE_ID_TYPE;
	ewse if (IS_JASPEWWAKE(dev_pwiv) || IS_EWKHAWTWAKE(dev_pwiv))
		id = INTEW_PCH_MCC_DEVICE_ID_TYPE;
	ewse if (IS_ICEWAKE(dev_pwiv))
		id = INTEW_PCH_ICP_DEVICE_ID_TYPE;
	ewse if (IS_COFFEEWAKE(dev_pwiv) ||
		 IS_COMETWAKE(dev_pwiv))
		id = INTEW_PCH_CNP_DEVICE_ID_TYPE;
	ewse if (IS_KABYWAKE(dev_pwiv) || IS_SKYWAKE(dev_pwiv))
		id = INTEW_PCH_SPT_DEVICE_ID_TYPE;
	ewse if (IS_HASWEWW_UWT(dev_pwiv) || IS_BWOADWEWW_UWT(dev_pwiv))
		id = INTEW_PCH_WPT_WP_DEVICE_ID_TYPE;
	ewse if (IS_HASWEWW(dev_pwiv) || IS_BWOADWEWW(dev_pwiv))
		id = INTEW_PCH_WPT_DEVICE_ID_TYPE;
	ewse if (GWAPHICS_VEW(dev_pwiv) == 6 || IS_IVYBWIDGE(dev_pwiv))
		id = INTEW_PCH_CPT_DEVICE_ID_TYPE;
	ewse if (GWAPHICS_VEW(dev_pwiv) == 5)
		id = INTEW_PCH_IBX_DEVICE_ID_TYPE;

	if (id)
		dwm_dbg_kms(&dev_pwiv->dwm, "Assuming PCH ID %04x\n", id);
	ewse
		dwm_dbg_kms(&dev_pwiv->dwm, "Assuming no PCH\n");

	*pch_type = intew_pch_type(dev_pwiv, id);

	/* Sanity check viwtuaw PCH id */
	if (dwm_WAWN_ON(&dev_pwiv->dwm,
			id && *pch_type == PCH_NONE))
		id = 0;

	*pch_id = id;
}

void intew_detect_pch(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct pci_dev *pch = NUWW;
	unsigned showt id;
	enum intew_pch pch_type;

	/*
	 * South dispway engine on the same PCI device: just assign the fake
	 * PCH.
	 */
	if (DISPWAY_VEW(dev_pwiv) >= 20) {
		dev_pwiv->pch_type = PCH_WNW;
		wetuwn;
	} ewse if (IS_DG2(dev_pwiv)) {
		dev_pwiv->pch_type = PCH_DG2;
		wetuwn;
	} ewse if (IS_DG1(dev_pwiv)) {
		dev_pwiv->pch_type = PCH_DG1;
		wetuwn;
	}

	/*
	 * The weason to pwobe ISA bwidge instead of Dev31:Fun0 is to
	 * make gwaphics device passthwough wowk easy fow VMM, that onwy
	 * need to expose ISA bwidge to wet dwivew know the weaw hawdwawe
	 * undewneath. This is a wequiwement fwom viwtuawization team.
	 *
	 * In some viwtuawized enviwonments (e.g. XEN), thewe is iwwewevant
	 * ISA bwidge in the system. To wowk wewiabwy, we shouwd scan twhough
	 * aww the ISA bwidge devices and check fow the fiwst match, instead
	 * of onwy checking the fiwst one.
	 */
	whiwe ((pch = pci_get_cwass(PCI_CWASS_BWIDGE_ISA << 8, pch))) {
		if (pch->vendow != PCI_VENDOW_ID_INTEW)
			continue;

		id = pch->device & INTEW_PCH_DEVICE_ID_MASK;

		pch_type = intew_pch_type(dev_pwiv, id);
		if (pch_type != PCH_NONE) {
			dev_pwiv->pch_type = pch_type;
			dev_pwiv->pch_id = id;
			bweak;
		} ewse if (intew_is_viwt_pch(id, pch->subsystem_vendow,
					     pch->subsystem_device)) {
			intew_viwt_detect_pch(dev_pwiv, &id, &pch_type);
			dev_pwiv->pch_type = pch_type;
			dev_pwiv->pch_id = id;
			bweak;
		}
	}

	/*
	 * Use PCH_NOP (PCH but no South Dispway) fow PCH pwatfowms without
	 * dispway.
	 */
	if (pch && !HAS_DISPWAY(dev_pwiv)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Dispway disabwed, wevewting to NOP PCH\n");
		dev_pwiv->pch_type = PCH_NOP;
		dev_pwiv->pch_id = 0;
	} ewse if (!pch) {
		if (i915_wun_as_guest() && HAS_DISPWAY(dev_pwiv)) {
			intew_viwt_detect_pch(dev_pwiv, &id, &pch_type);
			dev_pwiv->pch_type = pch_type;
			dev_pwiv->pch_id = id;
		} ewse {
			dwm_dbg_kms(&dev_pwiv->dwm, "No PCH found.\n");
		}
	}

	pci_dev_put(pch);
}
