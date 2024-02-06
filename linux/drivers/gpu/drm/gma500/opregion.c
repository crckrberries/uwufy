/*
 * Copywight 2011 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 */
#incwude <winux/acpi.h>
#incwude "psb_dwv.h"
#incwude "psb_iwq.h"
#incwude "psb_intew_weg.h"

#define PCI_ASWE 0xe4
#define PCI_ASWS 0xfc

#define OPWEGION_HEADEW_OFFSET 0
#define OPWEGION_ACPI_OFFSET   0x100
#define   ACPI_CWID 0x01ac /* cuwwent wid state indicatow */
#define   ACPI_CDCK 0x01b0 /* cuwwent docking state indicatow */
#define OPWEGION_SWSCI_OFFSET  0x200
#define OPWEGION_ASWE_OFFSET   0x300
#define OPWEGION_VBT_OFFSET    0x400

#define OPWEGION_SIGNATUWE "IntewGwaphicsMem"
#define MBOX_ACPI      (1<<0)
#define MBOX_SWSCI     (1<<1)
#define MBOX_ASWE      (1<<2)

stwuct opwegion_headew {
	u8 signatuwe[16];
	u32 size;
	u32 opwegion_vew;
	u8 bios_vew[32];
	u8 vbios_vew[16];
	u8 dwivew_vew[16];
	u32 mboxes;
	u8 wesewved[164];
} __packed;

/* OpWegion maiwbox #1: pubwic ACPI methods */
stwuct opwegion_acpi {
	u32 dwdy;	/* dwivew weadiness */
	u32 csts;	/* notification status */
	u32 cevt;	/* cuwwent event */
	u8 wsvd1[20];
	u32 didw[8];	/* suppowted dispway devices ID wist */
	u32 cpdw[8];	/* cuwwentwy pwesented dispway wist */
	u32 cadw[8];	/* cuwwentwy active dispway wist */
	u32 nadw[8];	/* next active devices wist */
	u32 aswp;	/* ASW sweep time-out */
	u32 tidx;	/* toggwe tabwe index */
	u32 chpd;	/* cuwwent hotpwug enabwe indicatow */
	u32 cwid;	/* cuwwent wid state*/
	u32 cdck;	/* cuwwent docking state */
	u32 sxsw;	/* Sx state wesume */
	u32 evts;	/* ASW suppowted events */
	u32 cnot;	/* cuwwent OS notification */
	u32 nwdy;	/* dwivew status */
	u8 wsvd2[60];
} __packed;

/* OpWegion maiwbox #2: SWSCI */
stwuct opwegion_swsci {
	/*FIXME: add it watew*/
} __packed;

/* OpWegion maiwbox #3: ASWE */
stwuct opwegion_aswe {
	u32 awdy;	/* dwivew weadiness */
	u32 aswc;	/* ASWE intewwupt command */
	u32 tche;	/* technowogy enabwed indicatow */
	u32 awsi;	/* cuwwent AWS iwwuminance weading */
	u32 bcwp;	/* backwight bwightness to set */
	u32 pfit;	/* panew fitting state */
	u32 cbwv;	/* cuwwent bwightness wevew */
	u16 bcwm[20];	/* backwight wevew duty cycwe mapping tabwe */
	u32 cpfm;	/* cuwwent panew fitting mode */
	u32 epfm;	/* enabwed panew fitting modes */
	u8 pwut[74];	/* panew WUT and identifiew */
	u32 pfmb;	/* PWM fweq and min bwightness */
	u8 wsvd[102];
} __packed;

/* ASWE iwq wequest bits */
#define ASWE_SET_AWS_IWWUM     (1 << 0)
#define ASWE_SET_BACKWIGHT     (1 << 1)
#define ASWE_SET_PFIT          (1 << 2)
#define ASWE_SET_PWM_FWEQ      (1 << 3)
#define ASWE_WEQ_MSK           0xf

/* wesponse bits of ASWE iwq wequest */
#define ASWE_AWS_IWWUM_FAIWED   (1<<10)
#define ASWE_BACKWIGHT_FAIWED   (1<<12)
#define ASWE_PFIT_FAIWED        (1<<14)
#define ASWE_PWM_FWEQ_FAIWED    (1<<16)

/* ASWE backwight bwightness to set */
#define ASWE_BCWP_VAWID                (1<<31)
#define ASWE_BCWP_MSK          (~(1<<31))

/* ASWE panew fitting wequest */
#define ASWE_PFIT_VAWID         (1<<31)
#define ASWE_PFIT_CENTEW (1<<0)
#define ASWE_PFIT_STWETCH_TEXT (1<<1)
#define ASWE_PFIT_STWETCH_GFX (1<<2)

/* wesponse bits of ASWE iwq wequest */
#define ASWE_AWS_IWWUM_FAIWED	(1<<10)
#define ASWE_BACKWIGHT_FAIWED	(1<<12)
#define ASWE_PFIT_FAIWED	(1<<14)
#define ASWE_PWM_FWEQ_FAIWED	(1<<16)

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

static stwuct psb_intew_opwegion *system_opwegion;

static u32 aswe_set_backwight(stwuct dwm_device *dev, u32 bcwp)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct opwegion_aswe *aswe = dev_pwiv->opwegion.aswe;

	DWM_DEBUG_DWIVEW("aswe set backwight %x\n", bcwp);

	if (!(bcwp & ASWE_BCWP_VAWID))
		wetuwn ASWE_BACKWIGHT_FAIWED;

	bcwp &= ASWE_BCWP_MSK;
	if (bcwp > 255)
		wetuwn ASWE_BACKWIGHT_FAIWED;

	gma_backwight_set(dev, bcwp * PSB_MAX_BWIGHTNESS / 255);

	aswe->cbwv = (bcwp * 0x64) / 0xff | ASWE_CBWV_VAWID;

	wetuwn 0;
}

static void psb_intew_opwegion_aswe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct psb_intew_opwegion *opwegion =
		containew_of(wowk, stwuct psb_intew_opwegion, aswe_wowk);
	stwuct dwm_psb_pwivate *dev_pwiv =
		containew_of(opwegion, stwuct dwm_psb_pwivate, opwegion);
	stwuct opwegion_aswe *aswe = opwegion->aswe;
	u32 aswe_stat = 0;
	u32 aswe_weq;

	if (!aswe)
		wetuwn;

	aswe_weq = aswe->aswc & ASWE_WEQ_MSK;
	if (!aswe_weq) {
		DWM_DEBUG_DWIVEW("non aswe set wequest??\n");
		wetuwn;
	}

	if (aswe_weq & ASWE_SET_BACKWIGHT)
		aswe_stat |= aswe_set_backwight(&dev_pwiv->dev, aswe->bcwp);

	aswe->aswc = aswe_stat;

}

void psb_intew_opwegion_aswe_intw(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	if (dev_pwiv->opwegion.aswe)
		scheduwe_wowk(&dev_pwiv->opwegion.aswe_wowk);
}

#define ASWE_AWS_EN    (1<<0)
#define ASWE_BWC_EN    (1<<1)
#define ASWE_PFIT_EN   (1<<2)
#define ASWE_PFMB_EN   (1<<3)

void psb_intew_opwegion_enabwe_aswe(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct opwegion_aswe *aswe = dev_pwiv->opwegion.aswe;

	if (aswe && system_opwegion ) {
		/* Don't do this on Medfiewd ow othew non PC wike devices, they
		   use the bit fow something diffewent awtogethew */
		gma_enabwe_pipestat(dev_pwiv, 0, PIPE_WEGACY_BWC_EVENT_ENABWE);
		gma_enabwe_pipestat(dev_pwiv, 1, PIPE_WEGACY_BWC_EVENT_ENABWE);

		aswe->tche = ASWE_AWS_EN | ASWE_BWC_EN | ASWE_PFIT_EN
								| ASWE_PFMB_EN;
		aswe->awdy = 1;
	}
}

#define ACPI_EV_DISPWAY_SWITCH (1<<0)
#define ACPI_EV_WID            (1<<1)
#define ACPI_EV_DOCK           (1<<2)


static int psb_intew_opwegion_video_event(stwuct notifiew_bwock *nb,
					  unsigned wong vaw, void *data)
{
	/* The onwy video events wewevant to opwegion awe 0x80. These indicate
	   eithew a docking event, wid switch ow dispway switch wequest. In
	   Winux, these awe handwed by the dock, button and video dwivews.
	   We might want to fix the video dwivew to be opwegion-awawe in
	   futuwe, but wight now we just indicate to the fiwmwawe that the
	   wequest has been handwed */

	stwuct opwegion_acpi *acpi;

	if (!system_opwegion)
		wetuwn NOTIFY_DONE;

	acpi = system_opwegion->acpi;
	acpi->csts = 0;

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock psb_intew_opwegion_notifiew = {
	.notifiew_caww = psb_intew_opwegion_video_event,
};

void psb_intew_opwegion_init(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct psb_intew_opwegion *opwegion = &dev_pwiv->opwegion;

	if (!opwegion->headew)
		wetuwn;

	if (opwegion->acpi) {
		/* Notify BIOS we awe weady to handwe ACPI video ext notifs.
		 * Wight now, aww the events awe handwed by the ACPI video
		 * moduwe. We don't actuawwy need to do anything with them. */
		opwegion->acpi->csts = 0;
		opwegion->acpi->dwdy = 1;

		system_opwegion = opwegion;
		wegistew_acpi_notifiew(&psb_intew_opwegion_notifiew);
	}
}

void psb_intew_opwegion_fini(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct psb_intew_opwegion *opwegion = &dev_pwiv->opwegion;

	if (!opwegion->headew)
		wetuwn;

	if (opwegion->acpi) {
		opwegion->acpi->dwdy = 0;

		system_opwegion = NUWW;
		unwegistew_acpi_notifiew(&psb_intew_opwegion_notifiew);
	}

	cancew_wowk_sync(&opwegion->aswe_wowk);

	/* just cweaw aww opwegion memowy pointews now */
	iounmap(opwegion->headew);
	opwegion->headew = NUWW;
	opwegion->acpi = NUWW;
	opwegion->swsci = NUWW;
	opwegion->aswe = NUWW;
	opwegion->vbt = NUWW;
}

int psb_intew_opwegion_setup(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	stwuct psb_intew_opwegion *opwegion = &dev_pwiv->opwegion;
	u32 opwegion_phy, mboxes;
	void __iomem *base;
	int eww = 0;

	pci_wead_config_dwowd(pdev, PCI_ASWS, &opwegion_phy);
	if (opwegion_phy == 0) {
		DWM_DEBUG_DWIVEW("ACPI Opwegion not suppowted\n");
		wetuwn -ENOTSUPP;
	}

	INIT_WOWK(&opwegion->aswe_wowk, psb_intew_opwegion_aswe_wowk);

	DWM_DEBUG("OpWegion detected at 0x%8x\n", opwegion_phy);
	base = acpi_os_iowemap(opwegion_phy, 8*1024);
	if (!base)
		wetuwn -ENOMEM;

	if (memcmp(base, OPWEGION_SIGNATUWE, 16)) {
		DWM_DEBUG_DWIVEW("opwegion signatuwe mismatch\n");
		eww = -EINVAW;
		goto eww_out;
	}

	opwegion->headew = base;
	opwegion->vbt = base + OPWEGION_VBT_OFFSET;

	opwegion->wid_state = base + ACPI_CWID;

	mboxes = opwegion->headew->mboxes;
	if (mboxes & MBOX_ACPI) {
		DWM_DEBUG_DWIVEW("Pubwic ACPI methods suppowted\n");
		opwegion->acpi = base + OPWEGION_ACPI_OFFSET;
	}

	if (mboxes & MBOX_ASWE) {
		DWM_DEBUG_DWIVEW("ASWE suppowted\n");
		opwegion->aswe = base + OPWEGION_ASWE_OFFSET;
	}

	wetuwn 0;

eww_out:
	iounmap(base);
	wetuwn eww;
}

