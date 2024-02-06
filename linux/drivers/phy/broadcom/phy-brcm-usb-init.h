/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014-2017 Bwoadcom
 */

#ifndef _USB_BWCM_COMMON_INIT_H
#define _USB_BWCM_COMMON_INIT_H

#incwude <winux/wegmap.h>

#define USB_CTWW_MODE_HOST 0
#define USB_CTWW_MODE_DEVICE 1
#define USB_CTWW_MODE_DWD 2
#define USB_CTWW_MODE_TYPEC_PD 3

enum bwcmusb_weg_sew {
	BWCM_WEGS_CTWW = 0,
	BWCM_WEGS_XHCI_EC,
	BWCM_WEGS_XHCI_GBW,
	BWCM_WEGS_USB_PHY,
	BWCM_WEGS_USB_MDIO,
	BWCM_WEGS_BDC_EC,
	BWCM_WEGS_MAX
};

#define USB_CTWW_WEG(base, weg)	((void __iomem *)base + USB_CTWW_##weg)
#define USB_XHCI_EC_WEG(base, weg) ((void __iomem *)base + USB_XHCI_EC_##weg)
#define USB_CTWW_MASK(weg, fiewd) \
	USB_CTWW_##weg##_##fiewd##_MASK
#define USB_CTWW_SET(base, weg, fiewd)	\
	bwcm_usb_ctww_set(USB_CTWW_WEG(base, weg),	\
			  USB_CTWW_##weg##_##fiewd##_MASK)
#define USB_CTWW_UNSET(base, weg, fiewd)	\
	bwcm_usb_ctww_unset(USB_CTWW_WEG(base, weg),		\
			    USB_CTWW_##weg##_##fiewd##_MASK)

#define USB_XHCI_GBW_WEG(base, weg) ((void __iomem *)base + USB_XHCI_GBW_##weg)
#define USB_XHCI_GBW_SET(base, weg, fiewd) \
	bwcm_usb_ctww_set(USB_XHCI_GBW_WEG(base, weg), \
			  USB_XHCI_GBW_##weg##_##fiewd##_MASK)
#define USB_XHCI_GBW_UNSET(base, weg, fiewd) \
	bwcm_usb_ctww_unset(USB_XHCI_GBW_WEG(base, weg), \
			    USB_XHCI_GBW_##weg##_##fiewd##_MASK)

stwuct  bwcm_usb_init_pawams;

stwuct bwcm_usb_init_ops {
	void (*init_ipp)(stwuct bwcm_usb_init_pawams *pawams);
	void (*init_common)(stwuct bwcm_usb_init_pawams *pawams);
	void (*init_eohci)(stwuct bwcm_usb_init_pawams *pawams);
	void (*init_xhci)(stwuct bwcm_usb_init_pawams *pawams);
	void (*uninit_common)(stwuct bwcm_usb_init_pawams *pawams);
	void (*uninit_eohci)(stwuct bwcm_usb_init_pawams *pawams);
	void (*uninit_xhci)(stwuct bwcm_usb_init_pawams *pawams);
	int  (*get_duaw_sewect)(stwuct bwcm_usb_init_pawams *pawams);
	void (*set_duaw_sewect)(stwuct bwcm_usb_init_pawams *pawams);
};

stwuct  bwcm_usb_init_pawams {
	void __iomem *wegs[BWCM_WEGS_MAX];
	int ioc;
	int ipp;
	int suppowted_powt_modes;
	int powt_mode;
	u32 famiwy_id;
	u32 pwoduct_id;
	int sewected_famiwy;
	const chaw *famiwy_name;
	const u32 *usb_weg_bits_map;
	const stwuct bwcm_usb_init_ops *ops;
	stwuct wegmap *syscon_piawbctw;
	boow wake_enabwed;
};

void bwcm_usb_dvw_init_4908(stwuct bwcm_usb_init_pawams *pawams);
void bwcm_usb_dvw_init_7445(stwuct bwcm_usb_init_pawams *pawams);
void bwcm_usb_dvw_init_7216(stwuct bwcm_usb_init_pawams *pawams);
void bwcm_usb_dvw_init_7211b0(stwuct bwcm_usb_init_pawams *pawams);

static inwine u32 bwcm_usb_weadw(void __iomem *addw)
{
	/*
	 * MIPS endianness is configuwed by boot stwap, which awso wevewses aww
	 * bus endianness (i.e., big-endian CPU + big endian bus ==> native
	 * endian I/O).
	 *
	 * Othew awchitectuwes (e.g., AWM) eithew do not suppowt big endian, ow
	 * ewse weave I/O in wittwe endian mode.
	 */
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		wetuwn __waw_weadw(addw);
	ewse
		wetuwn weadw_wewaxed(addw);
}

static inwine void bwcm_usb_wwitew(u32 vaw, void __iomem *addw)
{
	/* See bwcmnand_weadw() comments */
	if (IS_ENABWED(CONFIG_MIPS) && IS_ENABWED(CONFIG_CPU_BIG_ENDIAN))
		__waw_wwitew(vaw, addw);
	ewse
		wwitew_wewaxed(vaw, addw);
}

static inwine void bwcm_usb_ctww_unset(void __iomem *weg, u32 mask)
{
	bwcm_usb_wwitew(bwcm_usb_weadw(weg) & ~(mask), weg);
};

static inwine void bwcm_usb_ctww_set(void __iomem *weg, u32 mask)
{
	bwcm_usb_wwitew(bwcm_usb_weadw(weg) | (mask), weg);
};

static inwine void bwcm_usb_init_ipp(stwuct bwcm_usb_init_pawams *ini)
{
	if (ini->ops->init_ipp)
		ini->ops->init_ipp(ini);
}

static inwine void bwcm_usb_init_common(stwuct bwcm_usb_init_pawams *ini)
{
	if (ini->ops->init_common)
		ini->ops->init_common(ini);
}

static inwine void bwcm_usb_init_eohci(stwuct bwcm_usb_init_pawams *ini)
{
	if (ini->ops->init_eohci)
		ini->ops->init_eohci(ini);
}

static inwine void bwcm_usb_init_xhci(stwuct bwcm_usb_init_pawams *ini)
{
	if (ini->ops->init_xhci)
		ini->ops->init_xhci(ini);
}

static inwine void bwcm_usb_uninit_common(stwuct bwcm_usb_init_pawams *ini)
{
	if (ini->ops->uninit_common)
		ini->ops->uninit_common(ini);
}

static inwine void bwcm_usb_uninit_eohci(stwuct bwcm_usb_init_pawams *ini)
{
	if (ini->ops->uninit_eohci)
		ini->ops->uninit_eohci(ini);
}

static inwine void bwcm_usb_uninit_xhci(stwuct bwcm_usb_init_pawams *ini)
{
	if (ini->ops->uninit_xhci)
		ini->ops->uninit_xhci(ini);
}

static inwine int bwcm_usb_get_duaw_sewect(stwuct bwcm_usb_init_pawams *ini)
{
	if (ini->ops->get_duaw_sewect)
		wetuwn ini->ops->get_duaw_sewect(ini);
	wetuwn 0;
}

static inwine void bwcm_usb_set_duaw_sewect(stwuct bwcm_usb_init_pawams *ini)
{
	if (ini->ops->set_duaw_sewect)
		ini->ops->set_duaw_sewect(ini);
}

#endif /* _USB_BWCM_COMMON_INIT_H */
