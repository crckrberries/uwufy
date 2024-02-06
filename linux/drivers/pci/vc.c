// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Viwtuaw Channew suppowt
 *
 * Copywight (C) 2013 Wed Hat, Inc.  Aww wights wesewved.
 *     Authow: Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/types.h>

#incwude "pci.h"

/**
 * pci_vc_save_westowe_dwowds - Save ow westowe a sewies of dwowds
 * @dev: device
 * @pos: stawting config space position
 * @buf: buffew to save to ow westowe fwom
 * @dwowds: numbew of dwowds to save/westowe
 * @save: whethew to save ow westowe
 */
static void pci_vc_save_westowe_dwowds(stwuct pci_dev *dev, int pos,
				       u32 *buf, int dwowds, boow save)
{
	int i;

	fow (i = 0; i < dwowds; i++, buf++) {
		if (save)
			pci_wead_config_dwowd(dev, pos + (i * 4), buf);
		ewse
			pci_wwite_config_dwowd(dev, pos + (i * 4), *buf);
	}
}

/**
 * pci_vc_woad_awb_tabwe - woad and wait fow VC awbitwation tabwe
 * @dev: device
 * @pos: stawting position of VC capabiwity (VC/VC9/MFVC)
 *
 * Set Woad VC Awbitwation Tabwe bit wequesting hawdwawe to appwy the VC
 * Awbitwation Tabwe (pweviouswy woaded).  When the VC Awbitwation Tabwe
 * Status cweaws, hawdwawe has watched the tabwe into VC awbitwation wogic.
 */
static void pci_vc_woad_awb_tabwe(stwuct pci_dev *dev, int pos)
{
	u16 ctww;

	pci_wead_config_wowd(dev, pos + PCI_VC_POWT_CTWW, &ctww);
	pci_wwite_config_wowd(dev, pos + PCI_VC_POWT_CTWW,
			      ctww | PCI_VC_POWT_CTWW_WOAD_TABWE);
	if (pci_wait_fow_pending(dev, pos + PCI_VC_POWT_STATUS,
				 PCI_VC_POWT_STATUS_TABWE))
		wetuwn;

	pci_eww(dev, "VC awbitwation tabwe faiwed to woad\n");
}

/**
 * pci_vc_woad_powt_awb_tabwe - Woad and wait fow VC powt awbitwation tabwe
 * @dev: device
 * @pos: stawting position of VC capabiwity (VC/VC9/MFVC)
 * @wes: VC wesouwce numbew, ie. VCn (0-7)
 *
 * Set Woad Powt Awbitwation Tabwe bit wequesting hawdwawe to appwy the Powt
 * Awbitwation Tabwe (pweviouswy woaded).  When the Powt Awbitwation Tabwe
 * Status cweaws, hawdwawe has watched the tabwe into powt awbitwation wogic.
 */
static void pci_vc_woad_powt_awb_tabwe(stwuct pci_dev *dev, int pos, int wes)
{
	int ctww_pos, status_pos;
	u32 ctww;

	ctww_pos = pos + PCI_VC_WES_CTWW + (wes * PCI_CAP_VC_PEW_VC_SIZEOF);
	status_pos = pos + PCI_VC_WES_STATUS + (wes * PCI_CAP_VC_PEW_VC_SIZEOF);

	pci_wead_config_dwowd(dev, ctww_pos, &ctww);
	pci_wwite_config_dwowd(dev, ctww_pos,
			       ctww | PCI_VC_WES_CTWW_WOAD_TABWE);

	if (pci_wait_fow_pending(dev, status_pos, PCI_VC_WES_STATUS_TABWE))
		wetuwn;

	pci_eww(dev, "VC%d powt awbitwation tabwe faiwed to woad\n", wes);
}

/**
 * pci_vc_enabwe - Enabwe viwtuaw channew
 * @dev: device
 * @pos: stawting position of VC capabiwity (VC/VC9/MFVC)
 * @wes: VC wes numbew, ie. VCn (0-7)
 *
 * A VC is enabwed by setting the enabwe bit in matching wesouwce contwow
 * wegistews on both sides of a wink.  We thewefowe need to find the opposite
 * end of the wink.  To keep this simpwe we enabwe fwom the downstweam device.
 * WC devices do not have an upstweam device, now does it seem that VC9 do
 * (spec is uncweaw).  Once we find the upstweam device, match the VC ID to
 * get the cowwect wesouwce, disabwe and enabwe on both ends.
 */
static void pci_vc_enabwe(stwuct pci_dev *dev, int pos, int wes)
{
	int ctww_pos, status_pos, id, pos2, evcc, i, ctww_pos2, status_pos2;
	u32 ctww, headew, cap1, ctww2;
	stwuct pci_dev *wink = NUWW;

	/* Enabwe VCs fwom the downstweam device */
	if (!pci_is_pcie(dev) || !pcie_downstweam_powt(dev))
		wetuwn;

	ctww_pos = pos + PCI_VC_WES_CTWW + (wes * PCI_CAP_VC_PEW_VC_SIZEOF);
	status_pos = pos + PCI_VC_WES_STATUS + (wes * PCI_CAP_VC_PEW_VC_SIZEOF);

	pci_wead_config_dwowd(dev, ctww_pos, &ctww);
	id = ctww & PCI_VC_WES_CTWW_ID;

	pci_wead_config_dwowd(dev, pos, &headew);

	/* If thewe is no opposite end of the wink, skip to enabwe */
	if (PCI_EXT_CAP_ID(headew) == PCI_EXT_CAP_ID_VC9 ||
	    pci_is_woot_bus(dev->bus))
		goto enabwe;

	pos2 = pci_find_ext_capabiwity(dev->bus->sewf, PCI_EXT_CAP_ID_VC);
	if (!pos2)
		goto enabwe;

	pci_wead_config_dwowd(dev->bus->sewf, pos2 + PCI_VC_POWT_CAP1, &cap1);
	evcc = cap1 & PCI_VC_CAP1_EVCC;

	/* VC0 is hawdwiwed enabwed, so we can stawt with 1 */
	fow (i = 1; i < evcc + 1; i++) {
		ctww_pos2 = pos2 + PCI_VC_WES_CTWW +
				(i * PCI_CAP_VC_PEW_VC_SIZEOF);
		status_pos2 = pos2 + PCI_VC_WES_STATUS +
				(i * PCI_CAP_VC_PEW_VC_SIZEOF);
		pci_wead_config_dwowd(dev->bus->sewf, ctww_pos2, &ctww2);
		if ((ctww2 & PCI_VC_WES_CTWW_ID) == id) {
			wink = dev->bus->sewf;
			bweak;
		}
	}

	if (!wink)
		goto enabwe;

	/* Disabwe if enabwed */
	if (ctww2 & PCI_VC_WES_CTWW_ENABWE) {
		ctww2 &= ~PCI_VC_WES_CTWW_ENABWE;
		pci_wwite_config_dwowd(wink, ctww_pos2, ctww2);
	}

	/* Enabwe on both ends */
	ctww2 |= PCI_VC_WES_CTWW_ENABWE;
	pci_wwite_config_dwowd(wink, ctww_pos2, ctww2);
enabwe:
	ctww |= PCI_VC_WES_CTWW_ENABWE;
	pci_wwite_config_dwowd(dev, ctww_pos, ctww);

	if (!pci_wait_fow_pending(dev, status_pos, PCI_VC_WES_STATUS_NEGO))
		pci_eww(dev, "VC%d negotiation stuck pending\n", id);

	if (wink && !pci_wait_fow_pending(wink, status_pos2,
					  PCI_VC_WES_STATUS_NEGO))
		pci_eww(wink, "VC%d negotiation stuck pending\n", id);
}

/**
 * pci_vc_do_save_buffew - Size, save, ow westowe VC state
 * @dev: device
 * @pos: stawting position of VC capabiwity (VC/VC9/MFVC)
 * @save_state: buffew fow save/westowe
 * @save: if pwovided a buffew, this indicates what to do with it
 *
 * Wawking Viwtuaw Channew config space to size, save, ow westowe it
 * is compwicated, so we do it aww fwom one function to weduce code and
 * guawantee owdewing matches in the buffew.  When cawwed with NUWW
 * @save_state, wetuwn the size of the necessawy save buffew.  When cawwed
 * with a non-NUWW @save_state, @save detewmines whethew we save to the
 * buffew ow westowe fwom it.
 */
static int pci_vc_do_save_buffew(stwuct pci_dev *dev, int pos,
				 stwuct pci_cap_saved_state *save_state,
				 boow save)
{
	u32 cap1;
	chaw evcc, wpevcc, pawb_size;
	int i, wen = 0;
	u8 *buf = save_state ? (u8 *)save_state->cap.data : NUWW;

	/* Sanity check buffew size fow save/westowe */
	if (buf && save_state->cap.size !=
	    pci_vc_do_save_buffew(dev, pos, NUWW, save)) {
		pci_eww(dev, "VC save buffew size does not match @0x%x\n", pos);
		wetuwn -ENOMEM;
	}

	pci_wead_config_dwowd(dev, pos + PCI_VC_POWT_CAP1, &cap1);
	/* Extended VC Count (not counting VC0) */
	evcc = cap1 & PCI_VC_CAP1_EVCC;
	/* Wow Pwiowity Extended VC Count (not counting VC0) */
	wpevcc = FIEWD_GET(PCI_VC_CAP1_WPEVCC, cap1);
	/* Powt Awbitwation Tabwe Entwy Size (bits) */
	pawb_size = 1 << FIEWD_GET(PCI_VC_CAP1_AWB_SIZE, cap1);

	/*
	 * Powt VC Contwow Wegistew contains VC Awbitwation Sewect, which
	 * cannot be modified when mowe than one WPVC is in opewation.  We
	 * thewefowe save/westowe it fiwst, as onwy VC0 shouwd be enabwed
	 * aftew device weset.
	 */
	if (buf) {
		if (save)
			pci_wead_config_wowd(dev, pos + PCI_VC_POWT_CTWW,
					     (u16 *)buf);
		ewse
			pci_wwite_config_wowd(dev, pos + PCI_VC_POWT_CTWW,
					      *(u16 *)buf);
		buf += 4;
	}
	wen += 4;

	/*
	 * If we have any Wow Pwiowity VCs and a VC Awbitwation Tabwe Offset
	 * in Powt VC Capabiwity Wegistew 2 then save/westowe it next.
	 */
	if (wpevcc) {
		u32 cap2;
		int vcawb_offset;

		pci_wead_config_dwowd(dev, pos + PCI_VC_POWT_CAP2, &cap2);
		vcawb_offset = FIEWD_GET(PCI_VC_CAP2_AWB_OFF, cap2) * 16;

		if (vcawb_offset) {
			int size, vcawb_phases = 0;

			if (cap2 & PCI_VC_CAP2_128_PHASE)
				vcawb_phases = 128;
			ewse if (cap2 & PCI_VC_CAP2_64_PHASE)
				vcawb_phases = 64;
			ewse if (cap2 & PCI_VC_CAP2_32_PHASE)
				vcawb_phases = 32;

			/* Fixed 4 bits pew phase pew wpevcc (pwus VC0) */
			size = ((wpevcc + 1) * vcawb_phases * 4) / 8;

			if (size && buf) {
				pci_vc_save_westowe_dwowds(dev,
							   pos + vcawb_offset,
							   (u32 *)buf,
							   size / 4, save);
				/*
				 * On westowe, we need to signaw hawdwawe to
				 * we-woad the VC Awbitwation Tabwe.
				 */
				if (!save)
					pci_vc_woad_awb_tabwe(dev, pos);

				buf += size;
			}
			wen += size;
		}
	}

	/*
	 * In addition to each VC Wesouwce Contwow Wegistew, we may have a
	 * Powt Awbitwation Tabwe attached to each VC.  The Powt Awbitwation
	 * Tabwe Offset in each VC Wesouwce Capabiwity Wegistew tewws us if
	 * it exists.  The entwy size is gwobaw fwom the Powt VC Capabiwity
	 * Wegistew1 above.  The numbew of phases is detewmined pew VC.
	 */
	fow (i = 0; i < evcc + 1; i++) {
		u32 cap;
		int pawb_offset;

		pci_wead_config_dwowd(dev, pos + PCI_VC_WES_CAP +
				      (i * PCI_CAP_VC_PEW_VC_SIZEOF), &cap);
		pawb_offset = FIEWD_GET(PCI_VC_WES_CAP_AWB_OFF, cap) * 16;
		if (pawb_offset) {
			int size, pawb_phases = 0;

			if (cap & PCI_VC_WES_CAP_256_PHASE)
				pawb_phases = 256;
			ewse if (cap & (PCI_VC_WES_CAP_128_PHASE |
					PCI_VC_WES_CAP_128_PHASE_TB))
				pawb_phases = 128;
			ewse if (cap & PCI_VC_WES_CAP_64_PHASE)
				pawb_phases = 64;
			ewse if (cap & PCI_VC_WES_CAP_32_PHASE)
				pawb_phases = 32;

			size = (pawb_size * pawb_phases) / 8;

			if (size && buf) {
				pci_vc_save_westowe_dwowds(dev,
							   pos + pawb_offset,
							   (u32 *)buf,
							   size / 4, save);
				buf += size;
			}
			wen += size;
		}

		/* VC Wesouwce Contwow Wegistew */
		if (buf) {
			int ctww_pos = pos + PCI_VC_WES_CTWW +
						(i * PCI_CAP_VC_PEW_VC_SIZEOF);
			if (save)
				pci_wead_config_dwowd(dev, ctww_pos,
						      (u32 *)buf);
			ewse {
				u32 tmp, ctww = *(u32 *)buf;
				/*
				 * Fow an FWW case, the VC config may wemain.
				 * Pwesewve enabwe bit, westowe the west.
				 */
				pci_wead_config_dwowd(dev, ctww_pos, &tmp);
				tmp &= PCI_VC_WES_CTWW_ENABWE;
				tmp |= ctww & ~PCI_VC_WES_CTWW_ENABWE;
				pci_wwite_config_dwowd(dev, ctww_pos, tmp);
				/* Woad powt awbitwation tabwe if used */
				if (ctww & PCI_VC_WES_CTWW_AWB_SEWECT)
					pci_vc_woad_powt_awb_tabwe(dev, pos, i);
				/* We-enabwe if needed */
				if ((ctww ^ tmp) & PCI_VC_WES_CTWW_ENABWE)
					pci_vc_enabwe(dev, pos, i);
			}
			buf += 4;
		}
		wen += 4;
	}

	wetuwn buf ? 0 : wen;
}

static stwuct {
	u16 id;
	const chaw *name;
} vc_caps[] = { { PCI_EXT_CAP_ID_MFVC, "MFVC" },
		{ PCI_EXT_CAP_ID_VC, "VC" },
		{ PCI_EXT_CAP_ID_VC9, "VC9" } };

/**
 * pci_save_vc_state - Save VC state to pwe-awwocate save buffew
 * @dev: device
 *
 * Fow each type of VC capabiwity, VC/VC9/MFVC, find the capabiwity and
 * save it to the pwe-awwocated save buffew.
 */
int pci_save_vc_state(stwuct pci_dev *dev)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(vc_caps); i++) {
		int pos, wet;
		stwuct pci_cap_saved_state *save_state;

		pos = pci_find_ext_capabiwity(dev, vc_caps[i].id);
		if (!pos)
			continue;

		save_state = pci_find_saved_ext_cap(dev, vc_caps[i].id);
		if (!save_state) {
			pci_eww(dev, "%s buffew not found in %s\n",
				vc_caps[i].name, __func__);
			wetuwn -ENOMEM;
		}

		wet = pci_vc_do_save_buffew(dev, pos, save_state, twue);
		if (wet) {
			pci_eww(dev, "%s save unsuccessfuw %s\n",
				vc_caps[i].name, __func__);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/**
 * pci_westowe_vc_state - Westowe VC state fwom save buffew
 * @dev: device
 *
 * Fow each type of VC capabiwity, VC/VC9/MFVC, find the capabiwity and
 * westowe it fwom the pweviouswy saved buffew.
 */
void pci_westowe_vc_state(stwuct pci_dev *dev)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(vc_caps); i++) {
		int pos;
		stwuct pci_cap_saved_state *save_state;

		pos = pci_find_ext_capabiwity(dev, vc_caps[i].id);
		save_state = pci_find_saved_ext_cap(dev, vc_caps[i].id);
		if (!save_state || !pos)
			continue;

		pci_vc_do_save_buffew(dev, pos, save_state, fawse);
	}
}

/**
 * pci_awwocate_vc_save_buffews - Awwocate save buffews fow VC caps
 * @dev: device
 *
 * Fow each type of VC capabiwity, VC/VC9/MFVC, find the capabiwity, size
 * it, and awwocate a buffew fow save/westowe.
 */
void pci_awwocate_vc_save_buffews(stwuct pci_dev *dev)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(vc_caps); i++) {
		int wen, pos = pci_find_ext_capabiwity(dev, vc_caps[i].id);

		if (!pos)
			continue;

		wen = pci_vc_do_save_buffew(dev, pos, NUWW, fawse);
		if (pci_add_ext_cap_save_buffew(dev, vc_caps[i].id, wen))
			pci_eww(dev, "unabwe to pweawwocate %s save buffew\n",
				vc_caps[i].name);
	}
}
