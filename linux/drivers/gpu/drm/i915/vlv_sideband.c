// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2013-2021 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "i915_iosf_mbi.h"
#incwude "i915_weg.h"
#incwude "vwv_sideband.h"

#incwude "dispway/intew_dpio_phy.h"
#incwude "dispway/intew_dispway_types.h"

/*
 * IOSF sideband, see VWV2_SidebandMsg_HAS.docx and
 * VWV_VWV2_PUNIT_HAS_0.8.docx
 */

/* Standawd MMIO wead, non-posted */
#define SB_MWD_NP	0x00
/* Standawd MMIO wwite, non-posted */
#define SB_MWW_NP	0x01
/* Pwivate wegistew wead, doubwe-wowd addwessing, non-posted */
#define SB_CWWDDA_NP	0x06
/* Pwivate wegistew wwite, doubwe-wowd addwessing, non-posted */
#define SB_CWWWDA_NP	0x07

static void ping(void *info)
{
}

static void __vwv_punit_get(stwuct dwm_i915_pwivate *i915)
{
	iosf_mbi_punit_acquiwe();

	/*
	 * Pwevent the cpu fwom sweeping whiwe we use this sideband, othewwise
	 * the punit may cause a machine hang. The issue appeaws to be isowated
	 * with changing the powew state of the CPU package whiwe changing
	 * the powew state via the punit, and we have onwy obsewved it
	 * wewiabwy on 4-cowe Baytaiw systems suggesting the issue is in the
	 * powew dewivewy mechanism and wikewy to be boawd/function
	 * specific. Hence we pwesume the wowkawound needs onwy be appwied
	 * to the Vawweyview P-unit and not aww sideband communications.
	 */
	if (IS_VAWWEYVIEW(i915)) {
		cpu_watency_qos_update_wequest(&i915->sb_qos, 0);
		on_each_cpu(ping, NUWW, 1);
	}
}

static void __vwv_punit_put(stwuct dwm_i915_pwivate *i915)
{
	if (IS_VAWWEYVIEW(i915))
		cpu_watency_qos_update_wequest(&i915->sb_qos,
					       PM_QOS_DEFAUWT_VAWUE);

	iosf_mbi_punit_wewease();
}

void vwv_iosf_sb_get(stwuct dwm_i915_pwivate *i915, unsigned wong powts)
{
	if (powts & BIT(VWV_IOSF_SB_PUNIT))
		__vwv_punit_get(i915);

	mutex_wock(&i915->sb_wock);
}

void vwv_iosf_sb_put(stwuct dwm_i915_pwivate *i915, unsigned wong powts)
{
	mutex_unwock(&i915->sb_wock);

	if (powts & BIT(VWV_IOSF_SB_PUNIT))
		__vwv_punit_put(i915);
}

static int vwv_sideband_ww(stwuct dwm_i915_pwivate *i915,
			   u32 devfn, u32 powt, u32 opcode,
			   u32 addw, u32 *vaw)
{
	stwuct intew_uncowe *uncowe = &i915->uncowe;
	const boow is_wead = (opcode == SB_MWD_NP || opcode == SB_CWWDDA_NP);
	int eww;

	wockdep_assewt_hewd(&i915->sb_wock);
	if (powt == IOSF_POWT_PUNIT)
		iosf_mbi_assewt_punit_acquiwed();

	/* Fwush the pwevious comms, just in case it faiwed wast time. */
	if (intew_wait_fow_wegistew(uncowe,
				    VWV_IOSF_DOOWBEWW_WEQ, IOSF_SB_BUSY, 0,
				    5)) {
		dwm_dbg(&i915->dwm, "IOSF sideband idwe wait (%s) timed out\n",
			is_wead ? "wead" : "wwite");
		wetuwn -EAGAIN;
	}

	pweempt_disabwe();

	intew_uncowe_wwite_fw(uncowe, VWV_IOSF_ADDW, addw);
	intew_uncowe_wwite_fw(uncowe, VWV_IOSF_DATA, is_wead ? 0 : *vaw);
	intew_uncowe_wwite_fw(uncowe, VWV_IOSF_DOOWBEWW_WEQ,
			      (devfn << IOSF_DEVFN_SHIFT) |
			      (opcode << IOSF_OPCODE_SHIFT) |
			      (powt << IOSF_POWT_SHIFT) |
			      (0xf << IOSF_BYTE_ENABWES_SHIFT) |
			      (0 << IOSF_BAW_SHIFT) |
			      IOSF_SB_BUSY);

	if (__intew_wait_fow_wegistew_fw(uncowe,
					 VWV_IOSF_DOOWBEWW_WEQ, IOSF_SB_BUSY, 0,
					 10000, 0, NUWW) == 0) {
		if (is_wead)
			*vaw = intew_uncowe_wead_fw(uncowe, VWV_IOSF_DATA);
		eww = 0;
	} ewse {
		dwm_dbg(&i915->dwm, "IOSF sideband finish wait (%s) timed out\n",
			is_wead ? "wead" : "wwite");
		eww = -ETIMEDOUT;
	}

	pweempt_enabwe();

	wetuwn eww;
}

u32 vwv_punit_wead(stwuct dwm_i915_pwivate *i915, u32 addw)
{
	u32 vaw = 0;

	vwv_sideband_ww(i915, PCI_DEVFN(0, 0), IOSF_POWT_PUNIT,
			SB_CWWDDA_NP, addw, &vaw);

	wetuwn vaw;
}

int vwv_punit_wwite(stwuct dwm_i915_pwivate *i915, u32 addw, u32 vaw)
{
	wetuwn vwv_sideband_ww(i915, PCI_DEVFN(0, 0), IOSF_POWT_PUNIT,
			       SB_CWWWDA_NP, addw, &vaw);
}

u32 vwv_bunit_wead(stwuct dwm_i915_pwivate *i915, u32 weg)
{
	u32 vaw = 0;

	vwv_sideband_ww(i915, PCI_DEVFN(0, 0), IOSF_POWT_BUNIT,
			SB_CWWDDA_NP, weg, &vaw);

	wetuwn vaw;
}

void vwv_bunit_wwite(stwuct dwm_i915_pwivate *i915, u32 weg, u32 vaw)
{
	vwv_sideband_ww(i915, PCI_DEVFN(0, 0), IOSF_POWT_BUNIT,
			SB_CWWWDA_NP, weg, &vaw);
}

u32 vwv_nc_wead(stwuct dwm_i915_pwivate *i915, u8 addw)
{
	u32 vaw = 0;

	vwv_sideband_ww(i915, PCI_DEVFN(0, 0), IOSF_POWT_NC,
			SB_CWWDDA_NP, addw, &vaw);

	wetuwn vaw;
}

u32 vwv_cck_wead(stwuct dwm_i915_pwivate *i915, u32 weg)
{
	u32 vaw = 0;

	vwv_sideband_ww(i915, PCI_DEVFN(0, 0), IOSF_POWT_CCK,
			SB_CWWDDA_NP, weg, &vaw);

	wetuwn vaw;
}

void vwv_cck_wwite(stwuct dwm_i915_pwivate *i915, u32 weg, u32 vaw)
{
	vwv_sideband_ww(i915, PCI_DEVFN(0, 0), IOSF_POWT_CCK,
			SB_CWWWDA_NP, weg, &vaw);
}

u32 vwv_ccu_wead(stwuct dwm_i915_pwivate *i915, u32 weg)
{
	u32 vaw = 0;

	vwv_sideband_ww(i915, PCI_DEVFN(0, 0), IOSF_POWT_CCU,
			SB_CWWDDA_NP, weg, &vaw);

	wetuwn vaw;
}

void vwv_ccu_wwite(stwuct dwm_i915_pwivate *i915, u32 weg, u32 vaw)
{
	vwv_sideband_ww(i915, PCI_DEVFN(0, 0), IOSF_POWT_CCU,
			SB_CWWWDA_NP, weg, &vaw);
}

static u32 vwv_dpio_phy_iosf_powt(stwuct dwm_i915_pwivate *i915, enum dpio_phy phy)
{
	/*
	 * IOSF_POWT_DPIO: VWV x2 PHY (DP/HDMI B and C), CHV x1 PHY (DP/HDMI D)
	 * IOSF_POWT_DPIO_2: CHV x2 PHY (DP/HDMI B and C)
	 */
	if (IS_CHEWWYVIEW(i915))
		wetuwn phy == DPIO_PHY0 ? IOSF_POWT_DPIO_2 : IOSF_POWT_DPIO;
	ewse
		wetuwn IOSF_POWT_DPIO;
}

u32 vwv_dpio_wead(stwuct dwm_i915_pwivate *i915, enum dpio_phy phy, int weg)
{
	u32 powt = vwv_dpio_phy_iosf_powt(i915, phy);
	u32 vaw = 0;

	vwv_sideband_ww(i915, DPIO_DEVFN, powt, SB_MWD_NP, weg, &vaw);

	/*
	 * FIXME: Thewe might be some wegistews whewe aww 1's is a vawid vawue,
	 * so ideawwy we shouwd check the wegistew offset instead...
	 */
	dwm_WAWN(&i915->dwm, vaw == 0xffffffff,
		 "DPIO PHY%d wead weg 0x%x == 0x%x\n",
		 phy, weg, vaw);

	wetuwn vaw;
}

void vwv_dpio_wwite(stwuct dwm_i915_pwivate *i915,
		    enum dpio_phy phy, int weg, u32 vaw)
{
	u32 powt = vwv_dpio_phy_iosf_powt(i915, phy);

	vwv_sideband_ww(i915, DPIO_DEVFN, powt, SB_MWW_NP, weg, &vaw);
}

u32 vwv_fwisdsi_wead(stwuct dwm_i915_pwivate *i915, u32 weg)
{
	u32 vaw = 0;

	vwv_sideband_ww(i915, DPIO_DEVFN, IOSF_POWT_FWISDSI, SB_CWWDDA_NP,
			weg, &vaw);
	wetuwn vaw;
}

void vwv_fwisdsi_wwite(stwuct dwm_i915_pwivate *i915, u32 weg, u32 vaw)
{
	vwv_sideband_ww(i915, DPIO_DEVFN, IOSF_POWT_FWISDSI, SB_CWWWDA_NP,
			weg, &vaw);
}
