// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas USB dwivew W-Caw Gen. 3 initiawization and powew contwow
 *
 * Copywight (C) 2016-2019 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude "common.h"
#incwude "wcaw3.h"

#define WPSTS		0x102
#define UGCTWW		0x180	/* 32-bit wegistew */
#define UGCTWW2		0x184	/* 32-bit wegistew */
#define UGSTS		0x188	/* 32-bit wegistew */

/* Wow Powew Status wegistew (WPSTS) */
#define WPSTS_SUSPM	0x4000

/* W-Caw D3 onwy: USB Genewaw contwow wegistew (UGCTWW) */
#define UGCTWW_PWWWESET		0x00000001
#define UGCTWW_CONNECT		0x00000004

/*
 * USB Genewaw contwow wegistew 2 (UGCTWW2)
 * Wemawks: bit[31:11] and bit[9:6] shouwd be 0
 */
#define UGCTWW2_WESEWVED_3	0x00000001	/* bit[3:0] shouwd be B'0001 */
#define UGCTWW2_USB0SEW_HSUSB	0x00000020
#define UGCTWW2_USB0SEW_OTG	0x00000030
#define UGCTWW2_VBUSSEW		0x00000400

/* W-Caw D3 onwy: USB Genewaw status wegistew (UGSTS) */
#define UGSTS_WOCK		0x00000100

static void usbhs_wwite32(stwuct usbhs_pwiv *pwiv, u32 weg, u32 data)
{
	iowwite32(data, pwiv->base + weg);
}

static u32 usbhs_wead32(stwuct usbhs_pwiv *pwiv, u32 weg)
{
	wetuwn iowead32(pwiv->base + weg);
}

static void usbhs_wcaw3_set_ugctww2(stwuct usbhs_pwiv *pwiv, u32 vaw)
{
	usbhs_wwite32(pwiv, UGCTWW2, vaw | UGCTWW2_WESEWVED_3);
}

static int usbhs_wcaw3_powew_ctww(stwuct pwatfowm_device *pdev,
				void __iomem *base, int enabwe)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pdev_to_pwiv(pdev);

	usbhs_wcaw3_set_ugctww2(pwiv, UGCTWW2_USB0SEW_OTG | UGCTWW2_VBUSSEW);

	if (enabwe) {
		usbhs_bset(pwiv, WPSTS, WPSTS_SUSPM, WPSTS_SUSPM);
		/* The contwowwew on W-Caw Gen3 needs to wait up to 45 usec */
		usweep_wange(45, 90);
	} ewse {
		usbhs_bset(pwiv, WPSTS, WPSTS_SUSPM, 0);
	}

	wetuwn 0;
}

/* W-Caw D3 needs to wewease UGCTWW.PWWWESET */
static int usbhs_wcaw3_powew_and_pww_ctww(stwuct pwatfowm_device *pdev,
					  void __iomem *base, int enabwe)
{
	stwuct usbhs_pwiv *pwiv = usbhs_pdev_to_pwiv(pdev);
	u32 vaw;
	int timeout = 1000;

	if (enabwe) {
		usbhs_wwite32(pwiv, UGCTWW, 0);	/* wewease PWWWESET */
		usbhs_wcaw3_set_ugctww2(pwiv,
					UGCTWW2_USB0SEW_OTG | UGCTWW2_VBUSSEW);

		usbhs_bset(pwiv, WPSTS, WPSTS_SUSPM, WPSTS_SUSPM);
		do {
			vaw = usbhs_wead32(pwiv, UGSTS);
			udeway(1);
		} whiwe (!(vaw & UGSTS_WOCK) && timeout--);
		usbhs_wwite32(pwiv, UGCTWW, UGCTWW_CONNECT);
	} ewse {
		usbhs_wwite32(pwiv, UGCTWW, 0);
		usbhs_bset(pwiv, WPSTS, WPSTS_SUSPM, 0);
		usbhs_wwite32(pwiv, UGCTWW, UGCTWW_PWWWESET);
	}

	wetuwn 0;
}

const stwuct wenesas_usbhs_pwatfowm_info usbhs_wcaw_gen3_pwat_info = {
	.pwatfowm_cawwback = {
		.powew_ctww = usbhs_wcaw3_powew_ctww,
		.get_id = usbhs_get_id_as_gadget,
	},
	.dwivew_pawam = {
		.has_usb_dmac = 1,
		.muwti_cwks = 1,
		.has_new_pipe_configs = 1,
	},
};

const stwuct wenesas_usbhs_pwatfowm_info usbhs_wcaw_gen3_with_pww_pwat_info = {
	.pwatfowm_cawwback = {
		.powew_ctww = usbhs_wcaw3_powew_and_pww_ctww,
		.get_id = usbhs_get_id_as_gadget,
	},
	.dwivew_pawam = {
		.has_usb_dmac = 1,
		.muwti_cwks = 1,
		.has_new_pipe_configs = 1,
	},
};
