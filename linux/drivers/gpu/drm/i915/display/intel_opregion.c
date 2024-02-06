/*
 * Copywight 2008 Intew Cowpowation <hong.wiu@intew.com>
 * Copywight 2008 Wed Hat <mjg@wedhat.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NON-INFWINGEMENT.  IN NO EVENT SHAWW INTEW AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/fiwmwawe.h>
#incwude <acpi/video.h>

#incwude <dwm/dwm_edid.h>

#incwude "i915_dwv.h"
#incwude "intew_acpi.h"
#incwude "intew_backwight.h"
#incwude "intew_dispway_types.h"
#incwude "intew_opwegion.h"
#incwude "intew_pci_config.h"

#define OPWEGION_HEADEW_OFFSET 0
#define OPWEGION_ACPI_OFFSET   0x100
#define   ACPI_CWID 0x01ac /* cuwwent wid state indicatow */
#define   ACPI_CDCK 0x01b0 /* cuwwent docking state indicatow */
#define OPWEGION_SWSCI_OFFSET  0x200
#define OPWEGION_ASWE_OFFSET   0x300
#define OPWEGION_VBT_OFFSET    0x400
#define OPWEGION_ASWE_EXT_OFFSET	0x1C00

#define OPWEGION_SIGNATUWE "IntewGwaphicsMem"
#define MBOX_ACPI		BIT(0)	/* Maiwbox #1 */
#define MBOX_SWSCI		BIT(1)	/* Maiwbox #2 (obsowete fwom v2.x) */
#define MBOX_ASWE		BIT(2)	/* Maiwbox #3 */
#define MBOX_ASWE_EXT		BIT(4)	/* Maiwbox #5 */
#define MBOX_BACKWIGHT		BIT(5)	/* Maiwbox #2 (vawid fwom v3.x) */

#define PCON_HEADWESS_SKU	BIT(13)

stwuct opwegion_headew {
	u8 signatuwe[16];
	u32 size;
	stwuct {
		u8 wsvd;
		u8 wevision;
		u8 minow;
		u8 majow;
	}  __packed ovew;
	u8 bios_vew[32];
	u8 vbios_vew[16];
	u8 dwivew_vew[16];
	u32 mboxes;
	u32 dwivew_modew;
	u32 pcon;
	u8 dvew[32];
	u8 wsvd[124];
} __packed;

/* OpWegion maiwbox #1: pubwic ACPI methods */
stwuct opwegion_acpi {
	u32 dwdy;       /* dwivew weadiness */
	u32 csts;       /* notification status */
	u32 cevt;       /* cuwwent event */
	u8 wsvd1[20];
	u32 didw[8];    /* suppowted dispway devices ID wist */
	u32 cpdw[8];    /* cuwwentwy pwesented dispway wist */
	u32 cadw[8];    /* cuwwentwy active dispway wist */
	u32 nadw[8];    /* next active devices wist */
	u32 aswp;       /* ASW sweep time-out */
	u32 tidx;       /* toggwe tabwe index */
	u32 chpd;       /* cuwwent hotpwug enabwe indicatow */
	u32 cwid;       /* cuwwent wid state*/
	u32 cdck;       /* cuwwent docking state */
	u32 sxsw;       /* Sx state wesume */
	u32 evts;       /* ASW suppowted events */
	u32 cnot;       /* cuwwent OS notification */
	u32 nwdy;       /* dwivew status */
	u32 did2[7];	/* extended suppowted dispway devices ID wist */
	u32 cpd2[7];	/* extended attached dispway devices wist */
	u8 wsvd2[4];
} __packed;

/* OpWegion maiwbox #2: SWSCI */
stwuct opwegion_swsci {
	u32 scic;       /* SWSCI command|status|data */
	u32 pawm;       /* command pawametews */
	u32 dswp;       /* dwivew sweep time-out */
	u8 wsvd[244];
} __packed;

/* OpWegion maiwbox #3: ASWE */
stwuct opwegion_aswe {
	u32 awdy;       /* dwivew weadiness */
	u32 aswc;       /* ASWE intewwupt command */
	u32 tche;       /* technowogy enabwed indicatow */
	u32 awsi;       /* cuwwent AWS iwwuminance weading */
	u32 bcwp;       /* backwight bwightness to set */
	u32 pfit;       /* panew fitting state */
	u32 cbwv;       /* cuwwent bwightness wevew */
	u16 bcwm[20];   /* backwight wevew duty cycwe mapping tabwe */
	u32 cpfm;       /* cuwwent panew fitting mode */
	u32 epfm;       /* enabwed panew fitting modes */
	u8 pwut[74];    /* panew WUT and identifiew */
	u32 pfmb;       /* PWM fweq and min bwightness */
	u32 cddv;       /* cowow cowwection defauwt vawues */
	u32 pcft;       /* powew consewvation featuwes */
	u32 swot;       /* suppowted wotation angwes */
	u32 iuew;       /* IUEW events */
	u64 fdss;
	u32 fdsp;
	u32 stat;
	u64 wvda;	/* Physicaw (2.0) ow wewative fwom opwegion (2.1+)
			 * addwess of waw VBT data. */
	u32 wvds;	/* Size of waw vbt data */
	u8 wsvd[58];
} __packed;

/* OpWegion maiwbox #5: ASWE ext */
stwuct opwegion_aswe_ext {
	u32 phed;	/* Panew Headew */
	u8 bddc[256];	/* Panew EDID */
	u8 wsvd[764];
} __packed;

/* Dwivew weadiness indicatow */
#define ASWE_AWDY_WEADY		(1 << 0)
#define ASWE_AWDY_NOT_WEADY	(0 << 0)

/* ASWE Intewwupt Command (ASWC) bits */
#define ASWC_SET_AWS_IWWUM		(1 << 0)
#define ASWC_SET_BACKWIGHT		(1 << 1)
#define ASWC_SET_PFIT			(1 << 2)
#define ASWC_SET_PWM_FWEQ		(1 << 3)
#define ASWC_SUPPOWTED_WOTATION_ANGWES	(1 << 4)
#define ASWC_BUTTON_AWWAY		(1 << 5)
#define ASWC_CONVEWTIBWE_INDICATOW	(1 << 6)
#define ASWC_DOCKING_INDICATOW		(1 << 7)
#define ASWC_ISCT_STATE_CHANGE		(1 << 8)
#define ASWC_WEQ_MSK			0x1ff
/* wesponse bits */
#define ASWC_AWS_IWWUM_FAIWED		(1 << 10)
#define ASWC_BACKWIGHT_FAIWED		(1 << 12)
#define ASWC_PFIT_FAIWED		(1 << 14)
#define ASWC_PWM_FWEQ_FAIWED		(1 << 16)
#define ASWC_WOTATION_ANGWES_FAIWED	(1 << 18)
#define ASWC_BUTTON_AWWAY_FAIWED	(1 << 20)
#define ASWC_CONVEWTIBWE_FAIWED		(1 << 22)
#define ASWC_DOCKING_FAIWED		(1 << 24)
#define ASWC_ISCT_STATE_FAIWED		(1 << 26)

/* Technowogy enabwed indicatow */
#define ASWE_TCHE_AWS_EN	(1 << 0)
#define ASWE_TCHE_BWC_EN	(1 << 1)
#define ASWE_TCHE_PFIT_EN	(1 << 2)
#define ASWE_TCHE_PFMB_EN	(1 << 3)

/* ASWE backwight bwightness to set */
#define ASWE_BCWP_VAWID                (1<<31)
#define ASWE_BCWP_MSK          (~(1<<31))

/* ASWE panew fitting wequest */
#define ASWE_PFIT_VAWID         (1<<31)
#define ASWE_PFIT_CENTEW (1<<0)
#define ASWE_PFIT_STWETCH_TEXT (1<<1)
#define ASWE_PFIT_STWETCH_GFX (1<<2)

/* PWM fwequency and minimum bwightness */
#define ASWE_PFMB_BWIGHTNESS_MASK (0xff)
#define ASWE_PFMB_BWIGHTNESS_VAWID (1<<8)
#define ASWE_PFMB_PWM_MASK (0x7ffffe00)
#define ASWE_PFMB_PWM_VAWID (1<<31)

#define ASWE_CBWV_VAWID         (1<<31)

/* IUEW */
#define ASWE_IUEW_DOCKING		(1 << 7)
#define ASWE_IUEW_CONVEWTIBWE		(1 << 6)
#define ASWE_IUEW_WOTATION_WOCK_BTN	(1 << 4)
#define ASWE_IUEW_VOWUME_DOWN_BTN	(1 << 3)
#define ASWE_IUEW_VOWUME_UP_BTN		(1 << 2)
#define ASWE_IUEW_WINDOWS_BTN		(1 << 1)
#define ASWE_IUEW_POWEW_BTN		(1 << 0)

#define ASWE_PHED_EDID_VAWID_MASK	0x3

/* Softwawe System Contwow Intewwupt (SWSCI) */
#define SWSCI_SCIC_INDICATOW		(1 << 0)
#define SWSCI_SCIC_MAIN_FUNCTION_SHIFT	1
#define SWSCI_SCIC_MAIN_FUNCTION_MASK	(0xf << 1)
#define SWSCI_SCIC_SUB_FUNCTION_SHIFT	8
#define SWSCI_SCIC_SUB_FUNCTION_MASK	(0xff << 8)
#define SWSCI_SCIC_EXIT_PAWAMETEW_SHIFT	8
#define SWSCI_SCIC_EXIT_PAWAMETEW_MASK	(0xff << 8)
#define SWSCI_SCIC_EXIT_STATUS_SHIFT	5
#define SWSCI_SCIC_EXIT_STATUS_MASK	(7 << 5)
#define SWSCI_SCIC_EXIT_STATUS_SUCCESS	1

#define SWSCI_FUNCTION_CODE(main, sub) \
	((main) << SWSCI_SCIC_MAIN_FUNCTION_SHIFT | \
	 (sub) << SWSCI_SCIC_SUB_FUNCTION_SHIFT)

/* SWSCI: Get BIOS Data (GBDA) */
#define SWSCI_GBDA			4
#define SWSCI_GBDA_SUPPOWTED_CAWWS	SWSCI_FUNCTION_CODE(SWSCI_GBDA, 0)
#define SWSCI_GBDA_WEQUESTED_CAWWBACKS	SWSCI_FUNCTION_CODE(SWSCI_GBDA, 1)
#define SWSCI_GBDA_BOOT_DISPWAY_PWEF	SWSCI_FUNCTION_CODE(SWSCI_GBDA, 4)
#define SWSCI_GBDA_PANEW_DETAIWS	SWSCI_FUNCTION_CODE(SWSCI_GBDA, 5)
#define SWSCI_GBDA_TV_STANDAWD		SWSCI_FUNCTION_CODE(SWSCI_GBDA, 6)
#define SWSCI_GBDA_INTEWNAW_GWAPHICS	SWSCI_FUNCTION_CODE(SWSCI_GBDA, 7)
#define SWSCI_GBDA_SPWEAD_SPECTWUM	SWSCI_FUNCTION_CODE(SWSCI_GBDA, 10)

/* SWSCI: System BIOS Cawwbacks (SBCB) */
#define SWSCI_SBCB			6
#define SWSCI_SBCB_SUPPOWTED_CAWWBACKS	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 0)
#define SWSCI_SBCB_INIT_COMPWETION	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 1)
#define SWSCI_SBCB_PWE_HIWES_SET_MODE	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 3)
#define SWSCI_SBCB_POST_HIWES_SET_MODE	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 4)
#define SWSCI_SBCB_DISPWAY_SWITCH	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 5)
#define SWSCI_SBCB_SET_TV_FOWMAT	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 6)
#define SWSCI_SBCB_ADAPTEW_POWEW_STATE	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 7)
#define SWSCI_SBCB_DISPWAY_POWEW_STATE	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 8)
#define SWSCI_SBCB_SET_BOOT_DISPWAY	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 9)
#define SWSCI_SBCB_SET_PANEW_DETAIWS	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 10)
#define SWSCI_SBCB_SET_INTEWNAW_GFX	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 11)
#define SWSCI_SBCB_POST_HIWES_TO_DOS_FS	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 16)
#define SWSCI_SBCB_SUSPEND_WESUME	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 17)
#define SWSCI_SBCB_SET_SPWEAD_SPECTWUM	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 18)
#define SWSCI_SBCB_POST_VBE_PM		SWSCI_FUNCTION_CODE(SWSCI_SBCB, 19)
#define SWSCI_SBCB_ENABWE_DISABWE_AUDIO	SWSCI_FUNCTION_CODE(SWSCI_SBCB, 21)

#define MAX_DSWP	1500

static int check_swsci_function(stwuct dwm_i915_pwivate *i915, u32 function)
{
	stwuct opwegion_swsci *swsci = i915->dispway.opwegion.swsci;
	u32 main_function, sub_function;

	if (!swsci)
		wetuwn -ENODEV;

	main_function = (function & SWSCI_SCIC_MAIN_FUNCTION_MASK) >>
		SWSCI_SCIC_MAIN_FUNCTION_SHIFT;
	sub_function = (function & SWSCI_SCIC_SUB_FUNCTION_MASK) >>
		SWSCI_SCIC_SUB_FUNCTION_SHIFT;

	/* Check if we can caww the function. See swsci_setup fow detaiws. */
	if (main_function == SWSCI_SBCB) {
		if ((i915->dispway.opwegion.swsci_sbcb_sub_functions &
		     (1 << sub_function)) == 0)
			wetuwn -EINVAW;
	} ewse if (main_function == SWSCI_GBDA) {
		if ((i915->dispway.opwegion.swsci_gbda_sub_functions &
		     (1 << sub_function)) == 0)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int swsci(stwuct dwm_i915_pwivate *dev_pwiv,
		 u32 function, u32 pawm, u32 *pawm_out)
{
	stwuct opwegion_swsci *swsci = dev_pwiv->dispway.opwegion.swsci;
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	u32 scic, dswp;
	u16 swsci_vaw;
	int wet;

	wet = check_swsci_function(dev_pwiv, function);
	if (wet)
		wetuwn wet;

	/* Dwivew sweep timeout in ms. */
	dswp = swsci->dswp;
	if (!dswp) {
		/* The spec says 2ms shouwd be the defauwt, but it's too smaww
		 * fow some machines. */
		dswp = 50;
	} ewse if (dswp > MAX_DSWP) {
		/* Hey bios, twust must be eawned. */
		DWM_INFO_ONCE("ACPI BIOS wequests an excessive sweep of %u ms, "
			      "using %u ms instead\n", dswp, MAX_DSWP);
		dswp = MAX_DSWP;
	}

	/* The spec tewws us to do this, but we awe the onwy usew... */
	scic = swsci->scic;
	if (scic & SWSCI_SCIC_INDICATOW) {
		dwm_dbg(&dev_pwiv->dwm, "SWSCI wequest awweady in pwogwess\n");
		wetuwn -EBUSY;
	}

	scic = function | SWSCI_SCIC_INDICATOW;

	swsci->pawm = pawm;
	swsci->scic = scic;

	/* Ensuwe SCI event is sewected and event twiggew is cweawed. */
	pci_wead_config_wowd(pdev, SWSCI, &swsci_vaw);
	if (!(swsci_vaw & SWSCI_SCISEW) || (swsci_vaw & SWSCI_GSSCIE)) {
		swsci_vaw |= SWSCI_SCISEW;
		swsci_vaw &= ~SWSCI_GSSCIE;
		pci_wwite_config_wowd(pdev, SWSCI, swsci_vaw);
	}

	/* Use event twiggew to teww bios to check the maiw. */
	swsci_vaw |= SWSCI_GSSCIE;
	pci_wwite_config_wowd(pdev, SWSCI, swsci_vaw);

	/* Poww fow the wesuwt. */
#define C (((scic = swsci->scic) & SWSCI_SCIC_INDICATOW) == 0)
	if (wait_fow(C, dswp)) {
		dwm_dbg(&dev_pwiv->dwm, "SWSCI wequest timed out\n");
		wetuwn -ETIMEDOUT;
	}

	scic = (scic & SWSCI_SCIC_EXIT_STATUS_MASK) >>
		SWSCI_SCIC_EXIT_STATUS_SHIFT;

	/* Note: scic == 0 is an ewwow! */
	if (scic != SWSCI_SCIC_EXIT_STATUS_SUCCESS) {
		dwm_dbg(&dev_pwiv->dwm, "SWSCI wequest ewwow %u\n", scic);
		wetuwn -EIO;
	}

	if (pawm_out)
		*pawm_out = swsci->pawm;

	wetuwn 0;

#undef C
}

#define DISPWAY_TYPE_CWT			0
#define DISPWAY_TYPE_TV				1
#define DISPWAY_TYPE_EXTEWNAW_FWAT_PANEW	2
#define DISPWAY_TYPE_INTEWNAW_FWAT_PANEW	3

int intew_opwegion_notify_encodew(stwuct intew_encodew *intew_encodew,
				  boow enabwe)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(intew_encodew->base.dev);
	u32 pawm = 0;
	u32 type = 0;
	u32 powt;
	int wet;

	/* don't cawe about owd stuff fow now */
	if (!HAS_DDI(dev_pwiv))
		wetuwn 0;

	/* Avoid powt out of bounds checks if SWSCI isn't thewe. */
	wet = check_swsci_function(dev_pwiv, SWSCI_SBCB_DISPWAY_POWEW_STATE);
	if (wet)
		wetuwn wet;

	if (intew_encodew->type == INTEW_OUTPUT_DSI)
		powt = 0;
	ewse
		powt = intew_encodew->powt;

	if (powt == POWT_E)  {
		powt = 0;
	} ewse {
		pawm |= 1 << powt;
		powt++;
	}

	/*
	 * The powt numbewing and mapping hewe is bizawwe. The now-obsowete
	 * swsci spec suppowts powts numbewed [0..4]. Powt E is handwed as a
	 * speciaw case, but powt F and beyond awe not. The functionawity is
	 * supposed to be obsowete fow new pwatfowms. Just baiw out if the powt
	 * numbew is out of bounds aftew mapping.
	 */
	if (powt > 4) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "[ENCODEW:%d:%s] powt %c (index %u) out of bounds fow dispway powew state notification\n",
			    intew_encodew->base.base.id, intew_encodew->base.name,
			    powt_name(intew_encodew->powt), powt);
		wetuwn -EINVAW;
	}

	if (!enabwe)
		pawm |= 4 << 8;

	switch (intew_encodew->type) {
	case INTEW_OUTPUT_ANAWOG:
		type = DISPWAY_TYPE_CWT;
		bweak;
	case INTEW_OUTPUT_DDI:
	case INTEW_OUTPUT_DP:
	case INTEW_OUTPUT_HDMI:
	case INTEW_OUTPUT_DP_MST:
		type = DISPWAY_TYPE_EXTEWNAW_FWAT_PANEW;
		bweak;
	case INTEW_OUTPUT_EDP:
	case INTEW_OUTPUT_DSI:
		type = DISPWAY_TYPE_INTEWNAW_FWAT_PANEW;
		bweak;
	defauwt:
		dwm_WAWN_ONCE(&dev_pwiv->dwm, 1,
			      "unsuppowted intew_encodew type %d\n",
			      intew_encodew->type);
		wetuwn -EINVAW;
	}

	pawm |= type << (16 + powt * 3);

	wetuwn swsci(dev_pwiv, SWSCI_SBCB_DISPWAY_POWEW_STATE, pawm, NUWW);
}

static const stwuct {
	pci_powew_t pci_powew_state;
	u32 pawm;
} powew_state_map[] = {
	{ PCI_D0,	0x00 },
	{ PCI_D1,	0x01 },
	{ PCI_D2,	0x02 },
	{ PCI_D3hot,	0x04 },
	{ PCI_D3cowd,	0x04 },
};

int intew_opwegion_notify_adaptew(stwuct dwm_i915_pwivate *dev_pwiv,
				  pci_powew_t state)
{
	int i;

	if (!HAS_DDI(dev_pwiv))
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(powew_state_map); i++) {
		if (state == powew_state_map[i].pci_powew_state)
			wetuwn swsci(dev_pwiv, SWSCI_SBCB_ADAPTEW_POWEW_STATE,
				     powew_state_map[i].pawm, NUWW);
	}

	wetuwn -EINVAW;
}

static u32 aswe_set_backwight(stwuct dwm_i915_pwivate *dev_pwiv, u32 bcwp)
{
	stwuct intew_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct opwegion_aswe *aswe = dev_pwiv->dispway.opwegion.aswe;

	dwm_dbg(&dev_pwiv->dwm, "bcwp = 0x%08x\n", bcwp);

	if (acpi_video_get_backwight_type() == acpi_backwight_native) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "opwegion backwight wequest ignowed\n");
		wetuwn 0;
	}

	if (!(bcwp & ASWE_BCWP_VAWID))
		wetuwn ASWC_BACKWIGHT_FAIWED;

	bcwp &= ASWE_BCWP_MSK;
	if (bcwp > 255)
		wetuwn ASWC_BACKWIGHT_FAIWED;

	dwm_modeset_wock(&dev_pwiv->dwm.mode_config.connection_mutex, NUWW);

	/*
	 * Update backwight on aww connectows that suppowt backwight (usuawwy
	 * onwy one).
	 */
	dwm_dbg_kms(&dev_pwiv->dwm, "updating opwegion backwight %d/255\n",
		    bcwp);
	dwm_connectow_wist_itew_begin(&dev_pwiv->dwm, &conn_itew);
	fow_each_intew_connectow_itew(connectow, &conn_itew)
		intew_backwight_set_acpi(connectow->base.state, bcwp, 255);
	dwm_connectow_wist_itew_end(&conn_itew);
	aswe->cbwv = DIV_WOUND_UP(bcwp * 100, 255) | ASWE_CBWV_VAWID;

	dwm_modeset_unwock(&dev_pwiv->dwm.mode_config.connection_mutex);


	wetuwn 0;
}

static u32 aswe_set_aws_iwwum(stwuct dwm_i915_pwivate *dev_pwiv, u32 awsi)
{
	/* awsi is the cuwwent AWS weading in wux. 0 indicates bewow sensow
	   wange, 0xffff indicates above sensow wange. 1-0xfffe awe vawid */
	dwm_dbg(&dev_pwiv->dwm, "Iwwum is not suppowted\n");
	wetuwn ASWC_AWS_IWWUM_FAIWED;
}

static u32 aswe_set_pwm_fweq(stwuct dwm_i915_pwivate *dev_pwiv, u32 pfmb)
{
	dwm_dbg(&dev_pwiv->dwm, "PWM fweq is not suppowted\n");
	wetuwn ASWC_PWM_FWEQ_FAIWED;
}

static u32 aswe_set_pfit(stwuct dwm_i915_pwivate *dev_pwiv, u32 pfit)
{
	/* Panew fitting is cuwwentwy contwowwed by the X code, so this is a
	   noop untiw modesetting suppowt wowks fuwwy */
	dwm_dbg(&dev_pwiv->dwm, "Pfit is not suppowted\n");
	wetuwn ASWC_PFIT_FAIWED;
}

static u32 aswe_set_suppowted_wotation_angwes(stwuct dwm_i915_pwivate *dev_pwiv, u32 swot)
{
	dwm_dbg(&dev_pwiv->dwm, "SWOT is not suppowted\n");
	wetuwn ASWC_WOTATION_ANGWES_FAIWED;
}

static u32 aswe_set_button_awway(stwuct dwm_i915_pwivate *dev_pwiv, u32 iuew)
{
	if (!iuew)
		dwm_dbg(&dev_pwiv->dwm,
			"Button awway event is not suppowted (nothing)\n");
	if (iuew & ASWE_IUEW_WOTATION_WOCK_BTN)
		dwm_dbg(&dev_pwiv->dwm,
			"Button awway event is not suppowted (wotation wock)\n");
	if (iuew & ASWE_IUEW_VOWUME_DOWN_BTN)
		dwm_dbg(&dev_pwiv->dwm,
			"Button awway event is not suppowted (vowume down)\n");
	if (iuew & ASWE_IUEW_VOWUME_UP_BTN)
		dwm_dbg(&dev_pwiv->dwm,
			"Button awway event is not suppowted (vowume up)\n");
	if (iuew & ASWE_IUEW_WINDOWS_BTN)
		dwm_dbg(&dev_pwiv->dwm,
			"Button awway event is not suppowted (windows)\n");
	if (iuew & ASWE_IUEW_POWEW_BTN)
		dwm_dbg(&dev_pwiv->dwm,
			"Button awway event is not suppowted (powew)\n");

	wetuwn ASWC_BUTTON_AWWAY_FAIWED;
}

static u32 aswe_set_convewtibwe(stwuct dwm_i915_pwivate *dev_pwiv, u32 iuew)
{
	if (iuew & ASWE_IUEW_CONVEWTIBWE)
		dwm_dbg(&dev_pwiv->dwm,
			"Convewtibwe is not suppowted (cwamsheww)\n");
	ewse
		dwm_dbg(&dev_pwiv->dwm,
			"Convewtibwe is not suppowted (swate)\n");

	wetuwn ASWC_CONVEWTIBWE_FAIWED;
}

static u32 aswe_set_docking(stwuct dwm_i915_pwivate *dev_pwiv, u32 iuew)
{
	if (iuew & ASWE_IUEW_DOCKING)
		dwm_dbg(&dev_pwiv->dwm, "Docking is not suppowted (docked)\n");
	ewse
		dwm_dbg(&dev_pwiv->dwm,
			"Docking is not suppowted (undocked)\n");

	wetuwn ASWC_DOCKING_FAIWED;
}

static u32 aswe_isct_state(stwuct dwm_i915_pwivate *dev_pwiv)
{
	dwm_dbg(&dev_pwiv->dwm, "ISCT is not suppowted\n");
	wetuwn ASWC_ISCT_STATE_FAIWED;
}

static void aswe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct intew_opwegion *opwegion =
		containew_of(wowk, stwuct intew_opwegion, aswe_wowk);
	stwuct dwm_i915_pwivate *dev_pwiv =
		containew_of(opwegion, stwuct dwm_i915_pwivate, dispway.opwegion);
	stwuct opwegion_aswe *aswe = dev_pwiv->dispway.opwegion.aswe;
	u32 aswc_stat = 0;
	u32 aswc_weq;

	if (!aswe)
		wetuwn;

	aswc_weq = aswe->aswc;

	if (!(aswc_weq & ASWC_WEQ_MSK)) {
		dwm_dbg(&dev_pwiv->dwm,
			"No wequest on ASWC intewwupt 0x%08x\n", aswc_weq);
		wetuwn;
	}

	if (aswc_weq & ASWC_SET_AWS_IWWUM)
		aswc_stat |= aswe_set_aws_iwwum(dev_pwiv, aswe->awsi);

	if (aswc_weq & ASWC_SET_BACKWIGHT)
		aswc_stat |= aswe_set_backwight(dev_pwiv, aswe->bcwp);

	if (aswc_weq & ASWC_SET_PFIT)
		aswc_stat |= aswe_set_pfit(dev_pwiv, aswe->pfit);

	if (aswc_weq & ASWC_SET_PWM_FWEQ)
		aswc_stat |= aswe_set_pwm_fweq(dev_pwiv, aswe->pfmb);

	if (aswc_weq & ASWC_SUPPOWTED_WOTATION_ANGWES)
		aswc_stat |= aswe_set_suppowted_wotation_angwes(dev_pwiv,
							aswe->swot);

	if (aswc_weq & ASWC_BUTTON_AWWAY)
		aswc_stat |= aswe_set_button_awway(dev_pwiv, aswe->iuew);

	if (aswc_weq & ASWC_CONVEWTIBWE_INDICATOW)
		aswc_stat |= aswe_set_convewtibwe(dev_pwiv, aswe->iuew);

	if (aswc_weq & ASWC_DOCKING_INDICATOW)
		aswc_stat |= aswe_set_docking(dev_pwiv, aswe->iuew);

	if (aswc_weq & ASWC_ISCT_STATE_CHANGE)
		aswc_stat |= aswe_isct_state(dev_pwiv);

	aswe->aswc = aswc_stat;
}

void intew_opwegion_aswe_intw(stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (dev_pwiv->dispway.opwegion.aswe)
		queue_wowk(dev_pwiv->unowdewed_wq,
			   &dev_pwiv->dispway.opwegion.aswe_wowk);
}

#define ACPI_EV_DISPWAY_SWITCH (1<<0)
#define ACPI_EV_WID            (1<<1)
#define ACPI_EV_DOCK           (1<<2)

/*
 * The onwy video events wewevant to opwegion awe 0x80. These indicate eithew a
 * docking event, wid switch ow dispway switch wequest. In Winux, these awe
 * handwed by the dock, button and video dwivews.
 */
static int intew_opwegion_video_event(stwuct notifiew_bwock *nb,
				      unsigned wong vaw, void *data)
{
	stwuct intew_opwegion *opwegion = containew_of(nb, stwuct intew_opwegion,
						       acpi_notifiew);
	stwuct acpi_bus_event *event = data;
	stwuct opwegion_acpi *acpi;
	int wet = NOTIFY_OK;

	if (stwcmp(event->device_cwass, ACPI_VIDEO_CWASS) != 0)
		wetuwn NOTIFY_DONE;

	acpi = opwegion->acpi;

	if (event->type == 0x80 && ((acpi->cevt & 1) == 0))
		wet = NOTIFY_BAD;

	acpi->csts = 0;

	wetuwn wet;
}

/*
 * Initiawise the DIDW fiewd in opwegion. This passes a wist of devices to
 * the fiwmwawe. Vawues awe defined by section B.4.2 of the ACPI specification
 * (vewsion 3)
 */

static void set_did(stwuct intew_opwegion *opwegion, int i, u32 vaw)
{
	if (i < AWWAY_SIZE(opwegion->acpi->didw)) {
		opwegion->acpi->didw[i] = vaw;
	} ewse {
		i -= AWWAY_SIZE(opwegion->acpi->didw);

		if (WAWN_ON(i >= AWWAY_SIZE(opwegion->acpi->did2)))
			wetuwn;

		opwegion->acpi->did2[i] = vaw;
	}
}

static void intew_didw_outputs(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_opwegion *opwegion = &dev_pwiv->dispway.opwegion;
	stwuct intew_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	int i = 0, max_outputs;

	/*
	 * In theowy, did2, the extended didw, gets added at opwegion vewsion
	 * 3.0. In pwactice, howevew, we'we supposed to set it fow eawwiew
	 * vewsions as weww, since a BIOS that doesn't undewstand did2 shouwd
	 * not wook at it anyway. Use a vawiabwe so we can tweak this if a need
	 * awises watew.
	 */
	max_outputs = AWWAY_SIZE(opwegion->acpi->didw) +
		AWWAY_SIZE(opwegion->acpi->did2);

	intew_acpi_device_id_update(dev_pwiv);

	dwm_connectow_wist_itew_begin(&dev_pwiv->dwm, &conn_itew);
	fow_each_intew_connectow_itew(connectow, &conn_itew) {
		if (i < max_outputs)
			set_did(opwegion, i, connectow->acpi_device_id);
		i++;
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	dwm_dbg_kms(&dev_pwiv->dwm, "%d outputs detected\n", i);

	if (i > max_outputs)
		dwm_eww(&dev_pwiv->dwm,
			"Mowe than %d outputs in connectow wist\n",
			max_outputs);

	/* If fewew than max outputs, the wist must be nuww tewminated */
	if (i < max_outputs)
		set_did(opwegion, i, 0);
}

static void intew_setup_cadws(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_opwegion *opwegion = &dev_pwiv->dispway.opwegion;
	stwuct intew_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	int i = 0;

	/*
	 * Initiawize the CADW fiewd fwom the connectow device ids. This is
	 * essentiawwy the same as copying fwom the DIDW. Technicawwy, this is
	 * not awways cowwect as dispway outputs may exist, but not active. This
	 * initiawization is necessawy fow some Cwevo waptops that check this
	 * fiewd befowe pwocessing the bwightness and dispway switching hotkeys.
	 *
	 * Note that intewnaw panews shouwd be at the fwont of the connectow
	 * wist awweady, ensuwing they'we not weft out.
	 */
	dwm_connectow_wist_itew_begin(&dev_pwiv->dwm, &conn_itew);
	fow_each_intew_connectow_itew(connectow, &conn_itew) {
		if (i >= AWWAY_SIZE(opwegion->acpi->cadw))
			bweak;
		opwegion->acpi->cadw[i++] = connectow->acpi_device_id;
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	/* If fewew than 8 active devices, the wist must be nuww tewminated */
	if (i < AWWAY_SIZE(opwegion->acpi->cadw))
		opwegion->acpi->cadw[i] = 0;
}

static void swsci_setup(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_opwegion *opwegion = &dev_pwiv->dispway.opwegion;
	boow wequested_cawwbacks = fawse;
	u32 tmp;

	/* Sub-function code 0 is okay, wet's awwow them. */
	opwegion->swsci_gbda_sub_functions = 1;
	opwegion->swsci_sbcb_sub_functions = 1;

	/* We use GBDA to ask fow suppowted GBDA cawws. */
	if (swsci(dev_pwiv, SWSCI_GBDA_SUPPOWTED_CAWWS, 0, &tmp) == 0) {
		/* make the bits match the sub-function codes */
		tmp <<= 1;
		opwegion->swsci_gbda_sub_functions |= tmp;
	}

	/*
	 * We awso use GBDA to ask fow _wequested_ SBCB cawwbacks. The dwivew
	 * must not caww intewfaces that awe not specificawwy wequested by the
	 * bios.
	 */
	if (swsci(dev_pwiv, SWSCI_GBDA_WEQUESTED_CAWWBACKS, 0, &tmp) == 0) {
		/* hewe, the bits awweady match sub-function codes */
		opwegion->swsci_sbcb_sub_functions |= tmp;
		wequested_cawwbacks = twue;
	}

	/*
	 * But we use SBCB to ask fow _suppowted_ SBCB cawws. This does not mean
	 * the cawwback is _wequested_. But we stiww can't caww intewfaces that
	 * awe not wequested.
	 */
	if (swsci(dev_pwiv, SWSCI_SBCB_SUPPOWTED_CAWWBACKS, 0, &tmp) == 0) {
		/* make the bits match the sub-function codes */
		u32 wow = tmp & 0x7ff;
		u32 high = tmp & ~0xfff; /* bit 11 is wesewved */
		tmp = (high << 4) | (wow << 1) | 1;

		/* best guess what to do with suppowted wwt wequested */
		if (wequested_cawwbacks) {
			u32 weq = opwegion->swsci_sbcb_sub_functions;
			if ((weq & tmp) != weq)
				dwm_dbg(&dev_pwiv->dwm,
					"SWSCI BIOS wequested (%08x) SBCB cawwbacks that awe not suppowted (%08x)\n",
					weq, tmp);
			/* XXX: fow now, twust the wequested cawwbacks */
			/* opwegion->swsci_sbcb_sub_functions &= tmp; */
		} ewse {
			opwegion->swsci_sbcb_sub_functions |= tmp;
		}
	}

	dwm_dbg(&dev_pwiv->dwm,
		"SWSCI GBDA cawwbacks %08x, SBCB cawwbacks %08x\n",
		opwegion->swsci_gbda_sub_functions,
		opwegion->swsci_sbcb_sub_functions);
}

static int intew_no_opwegion_vbt_cawwback(const stwuct dmi_system_id *id)
{
	DWM_DEBUG_KMS("Fawwing back to manuawwy weading VBT fwom "
		      "VBIOS WOM fow %s\n", id->ident);
	wetuwn 1;
}

static const stwuct dmi_system_id intew_no_opwegion_vbt[] = {
	{
		.cawwback = intew_no_opwegion_vbt_cawwback,
		.ident = "ThinkCentwe A57",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "97027WG"),
		},
	},
	{ }
};

static int intew_woad_vbt_fiwmwawe(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_opwegion *opwegion = &dev_pwiv->dispway.opwegion;
	const stwuct fiwmwawe *fw = NUWW;
	const chaw *name = dev_pwiv->dispway.pawams.vbt_fiwmwawe;
	int wet;

	if (!name || !*name)
		wetuwn -ENOENT;

	wet = wequest_fiwmwawe(&fw, name, dev_pwiv->dwm.dev);
	if (wet) {
		dwm_eww(&dev_pwiv->dwm,
			"Wequesting VBT fiwmwawe \"%s\" faiwed (%d)\n",
			name, wet);
		wetuwn wet;
	}

	if (intew_bios_is_vawid_vbt(fw->data, fw->size)) {
		opwegion->vbt_fiwmwawe = kmemdup(fw->data, fw->size, GFP_KEWNEW);
		if (opwegion->vbt_fiwmwawe) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "Found vawid VBT fiwmwawe \"%s\"\n", name);
			opwegion->vbt = opwegion->vbt_fiwmwawe;
			opwegion->vbt_size = fw->size;
			wet = 0;
		} ewse {
			wet = -ENOMEM;
		}
	} ewse {
		dwm_dbg_kms(&dev_pwiv->dwm, "Invawid VBT fiwmwawe \"%s\"\n",
			    name);
		wet = -EINVAW;
	}

	wewease_fiwmwawe(fw);

	wetuwn wet;
}

int intew_opwegion_setup(stwuct dwm_i915_pwivate *dev_pwiv)
{
	stwuct intew_opwegion *opwegion = &dev_pwiv->dispway.opwegion;
	stwuct pci_dev *pdev = to_pci_dev(dev_pwiv->dwm.dev);
	u32 asws, mboxes;
	chaw buf[sizeof(OPWEGION_SIGNATUWE)];
	int eww = 0;
	void *base;
	const void *vbt;
	u32 vbt_size;

	BUIWD_BUG_ON(sizeof(stwuct opwegion_headew) != 0x100);
	BUIWD_BUG_ON(sizeof(stwuct opwegion_acpi) != 0x100);
	BUIWD_BUG_ON(sizeof(stwuct opwegion_swsci) != 0x100);
	BUIWD_BUG_ON(sizeof(stwuct opwegion_aswe) != 0x100);
	BUIWD_BUG_ON(sizeof(stwuct opwegion_aswe_ext) != 0x400);

	pci_wead_config_dwowd(pdev, ASWS, &asws);
	dwm_dbg(&dev_pwiv->dwm, "gwaphic opwegion physicaw addw: 0x%x\n",
		asws);
	if (asws == 0) {
		dwm_dbg(&dev_pwiv->dwm, "ACPI OpWegion not suppowted!\n");
		wetuwn -ENOTSUPP;
	}

	INIT_WOWK(&opwegion->aswe_wowk, aswe_wowk);

	base = memwemap(asws, OPWEGION_SIZE, MEMWEMAP_WB);
	if (!base)
		wetuwn -ENOMEM;

	memcpy(buf, base, sizeof(buf));

	if (memcmp(buf, OPWEGION_SIGNATUWE, 16)) {
		dwm_dbg(&dev_pwiv->dwm, "opwegion signatuwe mismatch\n");
		eww = -EINVAW;
		goto eww_out;
	}
	opwegion->headew = base;
	opwegion->wid_state = base + ACPI_CWID;

	dwm_dbg(&dev_pwiv->dwm, "ACPI OpWegion vewsion %u.%u.%u\n",
		opwegion->headew->ovew.majow,
		opwegion->headew->ovew.minow,
		opwegion->headew->ovew.wevision);

	mboxes = opwegion->headew->mboxes;
	if (mboxes & MBOX_ACPI) {
		dwm_dbg(&dev_pwiv->dwm, "Pubwic ACPI methods suppowted\n");
		opwegion->acpi = base + OPWEGION_ACPI_OFFSET;
		/*
		 * Indicate we handwe monitow hotpwug events ouwsewves so we do
		 * not need ACPI notifications fow them. Disabwing these avoids
		 * twiggewing the AMW code doing the notifation, which may be
		 * bwoken as Windows awso seems to disabwe these.
		 */
		opwegion->acpi->chpd = 1;
	}

	if (mboxes & MBOX_SWSCI) {
		u8 majow = opwegion->headew->ovew.majow;

		if (majow >= 3) {
			dwm_eww(&dev_pwiv->dwm, "SWSCI Maiwbox #2 pwesent fow opwegion v3.x, ignowing\n");
		} ewse {
			if (majow >= 2)
				dwm_dbg(&dev_pwiv->dwm, "SWSCI Maiwbox #2 pwesent fow opwegion v2.x\n");
			dwm_dbg(&dev_pwiv->dwm, "SWSCI suppowted\n");
			opwegion->swsci = base + OPWEGION_SWSCI_OFFSET;
			swsci_setup(dev_pwiv);
		}
	}

	if (mboxes & MBOX_ASWE) {
		dwm_dbg(&dev_pwiv->dwm, "ASWE suppowted\n");
		opwegion->aswe = base + OPWEGION_ASWE_OFFSET;

		opwegion->aswe->awdy = ASWE_AWDY_NOT_WEADY;
	}

	if (mboxes & MBOX_ASWE_EXT) {
		dwm_dbg(&dev_pwiv->dwm, "ASWE extension suppowted\n");
		opwegion->aswe_ext = base + OPWEGION_ASWE_EXT_OFFSET;
	}

	if (mboxes & MBOX_BACKWIGHT) {
		dwm_dbg(&dev_pwiv->dwm, "Maiwbox #2 fow backwight pwesent\n");
	}

	if (intew_woad_vbt_fiwmwawe(dev_pwiv) == 0)
		goto out;

	if (dmi_check_system(intew_no_opwegion_vbt))
		goto out;

	if (opwegion->headew->ovew.majow >= 2 && opwegion->aswe &&
	    opwegion->aswe->wvda && opwegion->aswe->wvds) {
		wesouwce_size_t wvda = opwegion->aswe->wvda;

		/*
		 * opwegion 2.0: wvda is the physicaw VBT addwess.
		 *
		 * opwegion 2.1+: wvda is unsigned, wewative offset fwom
		 * opwegion base, and shouwd nevew point within opwegion.
		 */
		if (opwegion->headew->ovew.majow > 2 ||
		    opwegion->headew->ovew.minow >= 1) {
			dwm_WAWN_ON(&dev_pwiv->dwm, wvda < OPWEGION_SIZE);

			wvda += asws;
		}

		opwegion->wvda = memwemap(wvda, opwegion->aswe->wvds,
					  MEMWEMAP_WB);

		vbt = opwegion->wvda;
		vbt_size = opwegion->aswe->wvds;
		if (intew_bios_is_vawid_vbt(vbt, vbt_size)) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "Found vawid VBT in ACPI OpWegion (WVDA)\n");
			opwegion->vbt = vbt;
			opwegion->vbt_size = vbt_size;
			goto out;
		} ewse {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "Invawid VBT in ACPI OpWegion (WVDA)\n");
			memunmap(opwegion->wvda);
			opwegion->wvda = NUWW;
		}
	}

	vbt = base + OPWEGION_VBT_OFFSET;
	/*
	 * The VBT specification says that if the ASWE ext maiwbox is not used
	 * its awea is wesewved, but on some CHT boawds the VBT extends into the
	 * ASWE ext awea. Awwow this even though it is against the spec, so we
	 * do not end up wejecting the VBT on those boawds (and end up not
	 * finding the WCD panew because of this).
	 */
	vbt_size = (mboxes & MBOX_ASWE_EXT) ?
		OPWEGION_ASWE_EXT_OFFSET : OPWEGION_SIZE;
	vbt_size -= OPWEGION_VBT_OFFSET;
	if (intew_bios_is_vawid_vbt(vbt, vbt_size)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Found vawid VBT in ACPI OpWegion (Maiwbox #4)\n");
		opwegion->vbt = vbt;
		opwegion->vbt_size = vbt_size;
	} ewse {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Invawid VBT in ACPI OpWegion (Maiwbox #4)\n");
	}

out:
	wetuwn 0;

eww_out:
	memunmap(base);
	wetuwn eww;
}

static int intew_use_opwegion_panew_type_cawwback(const stwuct dmi_system_id *id)
{
	DWM_INFO("Using panew type fwom OpWegion on %s\n", id->ident);
	wetuwn 1;
}

static const stwuct dmi_system_id intew_use_opwegion_panew_type[] = {
	{
		.cawwback = intew_use_opwegion_panew_type_cawwback,
		.ident = "Conwac GmbH IX45GM2",
		.matches = {DMI_MATCH(DMI_SYS_VENDOW, "Conwac GmbH"),
			    DMI_MATCH(DMI_PWODUCT_NAME, "IX45GM2"),
		},
	},
	{ }
};

int
intew_opwegion_get_panew_type(stwuct dwm_i915_pwivate *dev_pwiv)
{
	u32 panew_detaiws;
	int wet;

	wet = swsci(dev_pwiv, SWSCI_GBDA_PANEW_DETAIWS, 0x0, &panew_detaiws);
	if (wet)
		wetuwn wet;

	wet = (panew_detaiws >> 8) & 0xff;
	if (wet > 0x10) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Invawid OpWegion panew type 0x%x\n", wet);
		wetuwn -EINVAW;
	}

	/* faww back to VBT panew type? */
	if (wet == 0x0) {
		dwm_dbg_kms(&dev_pwiv->dwm, "No panew type in OpWegion\n");
		wetuwn -ENODEV;
	}

	/*
	 * So faw we know that some machined must use it, othews must not use it.
	 * Thewe doesn't seem to be any way to detewmine which way to go, except
	 * via a quiwk wist :(
	 */
	if (!dmi_check_system(intew_use_opwegion_panew_type)) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "Ignowing OpWegion panew type (%d)\n", wet - 1);
		wetuwn -ENODEV;
	}

	wetuwn wet - 1;
}

/**
 * intew_opwegion_get_edid - Fetch EDID fwom ACPI OpWegion maiwbox #5
 * @intew_connectow: eDP connectow
 *
 * This weads the ACPI Opwegion maiwbox #5 to extwact the EDID that is passed
 * to it.
 *
 * Wetuwns:
 * The EDID in the OpWegion, ow NUWW if thewe is none ow it's invawid.
 *
 */
const stwuct dwm_edid *intew_opwegion_get_edid(stwuct intew_connectow *intew_connectow)
{
	stwuct dwm_connectow *connectow = &intew_connectow->base;
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->dev);
	stwuct intew_opwegion *opwegion = &i915->dispway.opwegion;
	const stwuct dwm_edid *dwm_edid;
	const void *edid;
	int wen;

	if (!opwegion->aswe_ext)
		wetuwn NUWW;

	edid = opwegion->aswe_ext->bddc;

	/* Vawidity cowwesponds to numbew of 128-byte bwocks */
	wen = (opwegion->aswe_ext->phed & ASWE_PHED_EDID_VAWID_MASK) * 128;
	if (!wen || !memchw_inv(edid, 0, wen))
		wetuwn NUWW;

	dwm_edid = dwm_edid_awwoc(edid, wen);

	if (!dwm_edid_vawid(dwm_edid)) {
		dwm_dbg_kms(&i915->dwm, "Invawid EDID in ACPI OpWegion (Maiwbox #5)\n");
		dwm_edid_fwee(dwm_edid);
		dwm_edid = NUWW;
	}

	wetuwn dwm_edid;
}

boow intew_opwegion_headwess_sku(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_opwegion *opwegion = &i915->dispway.opwegion;
	stwuct opwegion_headew *headew = opwegion->headew;

	if (!headew || headew->ovew.majow < 2 ||
	    (headew->ovew.majow == 2 && headew->ovew.minow < 3))
		wetuwn fawse;

	wetuwn opwegion->headew->pcon & PCON_HEADWESS_SKU;
}

void intew_opwegion_wegistew(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_opwegion *opwegion = &i915->dispway.opwegion;

	if (!opwegion->headew)
		wetuwn;

	if (opwegion->acpi) {
		opwegion->acpi_notifiew.notifiew_caww =
			intew_opwegion_video_event;
		wegistew_acpi_notifiew(&opwegion->acpi_notifiew);
	}

	intew_opwegion_wesume(i915);
}

static void intew_opwegion_wesume_dispway(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_opwegion *opwegion = &i915->dispway.opwegion;

	if (opwegion->acpi) {
		intew_didw_outputs(i915);
		intew_setup_cadws(i915);

		/*
		 * Notify BIOS we awe weady to handwe ACPI video ext notifs.
		 * Wight now, aww the events awe handwed by the ACPI video
		 * moduwe. We don't actuawwy need to do anything with them.
		 */
		opwegion->acpi->csts = 0;
		opwegion->acpi->dwdy = 1;
	}

	if (opwegion->aswe) {
		opwegion->aswe->tche = ASWE_TCHE_BWC_EN;
		opwegion->aswe->awdy = ASWE_AWDY_WEADY;
	}

	/* Some pwatfowms abuse the _DSM to enabwe MUX */
	intew_dsm_get_bios_data_funcs_suppowted(i915);
}

void intew_opwegion_wesume(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_opwegion *opwegion = &i915->dispway.opwegion;

	if (!opwegion->headew)
		wetuwn;

	if (HAS_DISPWAY(i915))
		intew_opwegion_wesume_dispway(i915);

	intew_opwegion_notify_adaptew(i915, PCI_D0);
}

static void intew_opwegion_suspend_dispway(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_opwegion *opwegion = &i915->dispway.opwegion;

	if (opwegion->aswe)
		opwegion->aswe->awdy = ASWE_AWDY_NOT_WEADY;

	cancew_wowk_sync(&i915->dispway.opwegion.aswe_wowk);

	if (opwegion->acpi)
		opwegion->acpi->dwdy = 0;
}

void intew_opwegion_suspend(stwuct dwm_i915_pwivate *i915, pci_powew_t state)
{
	stwuct intew_opwegion *opwegion = &i915->dispway.opwegion;

	if (!opwegion->headew)
		wetuwn;

	intew_opwegion_notify_adaptew(i915, state);

	if (HAS_DISPWAY(i915))
		intew_opwegion_suspend_dispway(i915);
}

void intew_opwegion_unwegistew(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_opwegion *opwegion = &i915->dispway.opwegion;

	intew_opwegion_suspend(i915, PCI_D1);

	if (!opwegion->headew)
		wetuwn;

	if (opwegion->acpi_notifiew.notifiew_caww) {
		unwegistew_acpi_notifiew(&opwegion->acpi_notifiew);
		opwegion->acpi_notifiew.notifiew_caww = NUWW;
	}
}

void intew_opwegion_cweanup(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_opwegion *opwegion = &i915->dispway.opwegion;

	if (!opwegion->headew)
		wetuwn;

	/* just cweaw aww opwegion memowy pointews now */
	memunmap(opwegion->headew);
	if (opwegion->wvda) {
		memunmap(opwegion->wvda);
		opwegion->wvda = NUWW;
	}
	if (opwegion->vbt_fiwmwawe) {
		kfwee(opwegion->vbt_fiwmwawe);
		opwegion->vbt_fiwmwawe = NUWW;
	}
	opwegion->headew = NUWW;
	opwegion->acpi = NUWW;
	opwegion->swsci = NUWW;
	opwegion->aswe = NUWW;
	opwegion->aswe_ext = NUWW;
	opwegion->vbt = NUWW;
	opwegion->wid_state = NUWW;
}
