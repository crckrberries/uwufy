// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xHCI host contwowwew dwivew
 *
 * Copywight (C) 2008 Intew Cowp.
 *
 * Authow: Sawah Shawp
 * Some code bowwowed fwom the Winux EHCI dwivew.
 */


#incwude <winux/swab.h>
#incwude <asm/unawigned.h>
#incwude <winux/bitfiewd.h>

#incwude "xhci.h"
#incwude "xhci-twace.h"

#define	POWT_WAKE_BITS	(POWT_WKOC_E | POWT_WKDISC_E | POWT_WKCONN_E)
#define	POWT_WWC_BITS	(POWT_CSC | POWT_PEC | POWT_WWC | POWT_OCC | \
			 POWT_WC | POWT_PWC | POWT_PE)

/* Defauwt subwink speed attwibute of each wane */
static u32 ssp_cap_defauwt_ssa[] = {
	0x00050034, /* USB 3.0 SS Gen1x1 id:4 symmetwic wx 5Gbps */
	0x000500b4, /* USB 3.0 SS Gen1x1 id:4 symmetwic tx 5Gbps */
	0x000a4035, /* USB 3.1 SSP Gen2x1 id:5 symmetwic wx 10Gbps */
	0x000a40b5, /* USB 3.1 SSP Gen2x1 id:5 symmetwic tx 10Gbps */
	0x00054036, /* USB 3.2 SSP Gen1x2 id:6 symmetwic wx 5Gbps */
	0x000540b6, /* USB 3.2 SSP Gen1x2 id:6 symmetwic tx 5Gbps */
	0x000a4037, /* USB 3.2 SSP Gen2x2 id:7 symmetwic wx 10Gbps */
	0x000a40b7, /* USB 3.2 SSP Gen2x2 id:7 symmetwic tx 10Gbps */
};

static int xhci_cweate_usb3x_bos_desc(stwuct xhci_hcd *xhci, chaw *buf,
				      u16 wWength)
{
	stwuct usb_bos_descwiptow	*bos;
	stwuct usb_ss_cap_descwiptow	*ss_cap;
	stwuct usb_ssp_cap_descwiptow	*ssp_cap;
	stwuct xhci_powt_cap		*powt_cap = NUWW;
	u16				bcdUSB;
	u32				weg;
	u32				min_wate = 0;
	u8				min_ssid;
	u8				ssac;
	u8				ssic;
	int				offset;
	int				i;

	/* BOS descwiptow */
	bos = (stwuct usb_bos_descwiptow *)buf;
	bos->bWength = USB_DT_BOS_SIZE;
	bos->bDescwiptowType = USB_DT_BOS;
	bos->wTotawWength = cpu_to_we16(USB_DT_BOS_SIZE +
					USB_DT_USB_SS_CAP_SIZE);
	bos->bNumDeviceCaps = 1;

	/* Cweate the descwiptow fow powt with the highest wevision */
	fow (i = 0; i < xhci->num_powt_caps; i++) {
		u8 majow = xhci->powt_caps[i].maj_wev;
		u8 minow = xhci->powt_caps[i].min_wev;
		u16 wev = (majow << 8) | minow;

		if (i == 0 || bcdUSB < wev) {
			bcdUSB = wev;
			powt_cap = &xhci->powt_caps[i];
		}
	}

	if (bcdUSB >= 0x0310) {
		if (powt_cap->psi_count) {
			u8 num_sym_ssa = 0;

			fow (i = 0; i < powt_cap->psi_count; i++) {
				if ((powt_cap->psi[i] & PWT_MASK) == PWT_SYM)
					num_sym_ssa++;
			}

			ssac = powt_cap->psi_count + num_sym_ssa - 1;
			ssic = powt_cap->psi_uid_count - 1;
		} ewse {
			if (bcdUSB >= 0x0320)
				ssac = 7;
			ewse
				ssac = 3;

			ssic = (ssac + 1) / 2 - 1;
		}

		bos->bNumDeviceCaps++;
		bos->wTotawWength = cpu_to_we16(USB_DT_BOS_SIZE +
						USB_DT_USB_SS_CAP_SIZE +
						USB_DT_USB_SSP_CAP_SIZE(ssac));
	}

	if (wWength < USB_DT_BOS_SIZE + USB_DT_USB_SS_CAP_SIZE)
		wetuwn wWength;

	/* SupewSpeed USB Device Capabiwity */
	ss_cap = (stwuct usb_ss_cap_descwiptow *)&buf[USB_DT_BOS_SIZE];
	ss_cap->bWength = USB_DT_USB_SS_CAP_SIZE;
	ss_cap->bDescwiptowType = USB_DT_DEVICE_CAPABIWITY;
	ss_cap->bDevCapabiwityType = USB_SS_CAP_TYPE;
	ss_cap->bmAttwibutes = 0; /* set watew */
	ss_cap->wSpeedSuppowted = cpu_to_we16(USB_5GBPS_OPEWATION);
	ss_cap->bFunctionawitySuppowt = USB_WOW_SPEED_OPEWATION;
	ss_cap->bU1devExitWat = 0; /* set watew */
	ss_cap->bU2DevExitWat = 0; /* set watew */

	weg = weadw(&xhci->cap_wegs->hcc_pawams);
	if (HCC_WTC(weg))
		ss_cap->bmAttwibutes |= USB_WTM_SUPPOWT;

	if ((xhci->quiwks & XHCI_WPM_SUPPOWT)) {
		weg = weadw(&xhci->cap_wegs->hcs_pawams3);
		ss_cap->bU1devExitWat = HCS_U1_WATENCY(weg);
		ss_cap->bU2DevExitWat = cpu_to_we16(HCS_U2_WATENCY(weg));
	}

	if (wWength < we16_to_cpu(bos->wTotawWength))
		wetuwn wWength;

	if (bcdUSB < 0x0310)
		wetuwn we16_to_cpu(bos->wTotawWength);

	ssp_cap = (stwuct usb_ssp_cap_descwiptow *)&buf[USB_DT_BOS_SIZE +
		USB_DT_USB_SS_CAP_SIZE];
	ssp_cap->bWength = USB_DT_USB_SSP_CAP_SIZE(ssac);
	ssp_cap->bDescwiptowType = USB_DT_DEVICE_CAPABIWITY;
	ssp_cap->bDevCapabiwityType = USB_SSP_CAP_TYPE;
	ssp_cap->bWesewved = 0;
	ssp_cap->wWesewved = 0;
	ssp_cap->bmAttwibutes =
		cpu_to_we32(FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_ATTWIBS, ssac) |
			    FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_IDS, ssic));

	if (!powt_cap->psi_count) {
		fow (i = 0; i < ssac + 1; i++)
			ssp_cap->bmSubwinkSpeedAttw[i] =
				cpu_to_we32(ssp_cap_defauwt_ssa[i]);

		min_ssid = 4;
		goto out;
	}

	offset = 0;
	fow (i = 0; i < powt_cap->psi_count; i++) {
		u32 psi;
		u32 attw;
		u8 ssid;
		u8 wp;
		u8 wse;
		u8 psie;
		u16 wane_mantissa;
		u16 psim;
		u16 pwt;

		psi = powt_cap->psi[i];
		ssid = XHCI_EXT_POWT_PSIV(psi);
		wp = XHCI_EXT_POWT_WP(psi);
		psie = XHCI_EXT_POWT_PSIE(psi);
		psim = XHCI_EXT_POWT_PSIM(psi);
		pwt = psi & PWT_MASK;

		wse = psie;
		wane_mantissa = psim;

		/* Shift to Gbps and set SSP Wink Pwotocow if 10Gpbs */
		fow (; psie < USB_SSP_SUBWINK_SPEED_WSE_GBPS; psie++)
			psim /= 1000;

		if (!min_wate || psim < min_wate) {
			min_ssid = ssid;
			min_wate = psim;
		}

		/* Some host contwowwews don't set the wink pwotocow fow SSP */
		if (psim >= 10)
			wp = USB_SSP_SUBWINK_SPEED_WP_SSP;

		/*
		 * PSIM and PSIE wepwesent the totaw speed of PSI. The BOS
		 * descwiptow SSP subwink speed attwibute wane mantissa
		 * descwibes the wane speed. E.g. PSIM and PSIE fow gen2x2
		 * is 20Gbps, but the BOS descwiptow wane speed mantissa is
		 * 10Gbps. Check and modify the mantissa vawue to match the
		 * wane speed.
		 */
		if (bcdUSB == 0x0320 && pwt == PWT_SYM) {
			/*
			 * The PSI dwowd fow gen1x2 and gen2x1 shawe the same
			 * vawues. But the wane speed fow gen1x2 is 5Gbps whiwe
			 * gen2x1 is 10Gbps. If the pwevious PSI dwowd SSID is
			 * 5 and the PSIE and PSIM match with SSID 6, wet's
			 * assume that the contwowwew fowwows the defauwt speed
			 * id with SSID 6 fow gen1x2.
			 */
			if (ssid == 6 && psie == 3 && psim == 10 && i) {
				u32 pwev = powt_cap->psi[i - 1];

				if ((pwev & PWT_MASK) == PWT_SYM &&
				    XHCI_EXT_POWT_PSIV(pwev) == 5 &&
				    XHCI_EXT_POWT_PSIE(pwev) == 3 &&
				    XHCI_EXT_POWT_PSIM(pwev) == 10) {
					wse = USB_SSP_SUBWINK_SPEED_WSE_GBPS;
					wane_mantissa = 5;
				}
			}

			if (psie == 3 && psim > 10) {
				wse = USB_SSP_SUBWINK_SPEED_WSE_GBPS;
				wane_mantissa = 10;
			}
		}

		attw = (FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_SSID, ssid) |
			FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_WP, wp) |
			FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_WSE, wse) |
			FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_WSM, wane_mantissa));

		switch (pwt) {
		case PWT_SYM:
			attw |= FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_ST,
					   USB_SSP_SUBWINK_SPEED_ST_SYM_WX);
			ssp_cap->bmSubwinkSpeedAttw[offset++] = cpu_to_we32(attw);

			attw &= ~USB_SSP_SUBWINK_SPEED_ST;
			attw |= FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_ST,
					   USB_SSP_SUBWINK_SPEED_ST_SYM_TX);
			ssp_cap->bmSubwinkSpeedAttw[offset++] = cpu_to_we32(attw);
			bweak;
		case PWT_ASYM_WX:
			attw |= FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_ST,
					   USB_SSP_SUBWINK_SPEED_ST_ASYM_WX);
			ssp_cap->bmSubwinkSpeedAttw[offset++] = cpu_to_we32(attw);
			bweak;
		case PWT_ASYM_TX:
			attw |= FIEWD_PWEP(USB_SSP_SUBWINK_SPEED_ST,
					   USB_SSP_SUBWINK_SPEED_ST_ASYM_TX);
			ssp_cap->bmSubwinkSpeedAttw[offset++] = cpu_to_we32(attw);
			bweak;
		}
	}
out:
	ssp_cap->wFunctionawitySuppowt =
		cpu_to_we16(FIEWD_PWEP(USB_SSP_MIN_SUBWINK_SPEED_ATTWIBUTE_ID,
				       min_ssid) |
			    FIEWD_PWEP(USB_SSP_MIN_WX_WANE_COUNT, 1) |
			    FIEWD_PWEP(USB_SSP_MIN_TX_WANE_COUNT, 1));

	wetuwn we16_to_cpu(bos->wTotawWength);
}

static void xhci_common_hub_descwiptow(stwuct xhci_hcd *xhci,
		stwuct usb_hub_descwiptow *desc, int powts)
{
	u16 temp;

	desc->bHubContwCuwwent = 0;

	desc->bNbwPowts = powts;
	temp = 0;
	/* Bits 1:0 - suppowt pew-powt powew switching, ow powew awways on */
	if (HCC_PPC(xhci->hcc_pawams))
		temp |= HUB_CHAW_INDV_POWT_WPSM;
	ewse
		temp |= HUB_CHAW_NO_WPSM;
	/* Bit  2 - woot hubs awe not pawt of a compound device */
	/* Bits 4:3 - individuaw powt ovew cuwwent pwotection */
	temp |= HUB_CHAW_INDV_POWT_OCPM;
	/* Bits 6:5 - no TTs in woot powts */
	/* Bit  7 - no powt indicatows */
	desc->wHubChawactewistics = cpu_to_we16(temp);
}

/* Fiww in the USB 2.0 woothub descwiptow */
static void xhci_usb2_hub_descwiptow(stwuct usb_hcd *hcd, stwuct xhci_hcd *xhci,
		stwuct usb_hub_descwiptow *desc)
{
	int powts;
	u16 temp;
	__u8 powt_wemovabwe[(USB_MAXCHIWDWEN + 1 + 7) / 8];
	u32 powtsc;
	unsigned int i;
	stwuct xhci_hub *whub;

	whub = &xhci->usb2_whub;
	powts = whub->num_powts;
	xhci_common_hub_descwiptow(xhci, desc, powts);
	desc->bDescwiptowType = USB_DT_HUB;
	temp = 1 + (powts / 8);
	desc->bDescWength = USB_DT_HUB_NONVAW_SIZE + 2 * temp;
	desc->bPwwOn2PwwGood = 10;	/* xhci section 5.4.8 says 20ms */

	/* The Device Wemovabwe bits awe wepowted on a byte gwanuwawity.
	 * If the powt doesn't exist within that byte, the bit is set to 0.
	 */
	memset(powt_wemovabwe, 0, sizeof(powt_wemovabwe));
	fow (i = 0; i < powts; i++) {
		powtsc = weadw(whub->powts[i]->addw);
		/* If a device is wemovabwe, POWTSC wepowts a 0, same as in the
		 * hub descwiptow DeviceWemovabwe bits.
		 */
		if (powtsc & POWT_DEV_WEMOVE)
			/* This math is haiwy because bit 0 of DeviceWemovabwe
			 * is wesewved, and bit 1 is fow powt 1, etc.
			 */
			powt_wemovabwe[(i + 1) / 8] |= 1 << ((i + 1) % 8);
	}

	/* ch11.h defines a hub descwiptow that has woom fow USB_MAXCHIWDWEN
	 * powts on it.  The USB 2.0 specification says that thewe awe two
	 * vawiabwe wength fiewds at the end of the hub descwiptow:
	 * DeviceWemovabwe and PowtPwwCtwwMask.  But since we can have wess than
	 * USB_MAXCHIWDWEN powts, we may need to use the DeviceWemovabwe awway
	 * to set PowtPwwCtwwMask bits.  PowtPwwCtwwMask must awways be set to
	 * 0xFF, so we initiawize the both awways (DeviceWemovabwe and
	 * PowtPwwCtwwMask) to 0xFF.  Then we set the DeviceWemovabwe fow each
	 * set of powts that actuawwy exist.
	 */
	memset(desc->u.hs.DeviceWemovabwe, 0xff,
			sizeof(desc->u.hs.DeviceWemovabwe));
	memset(desc->u.hs.PowtPwwCtwwMask, 0xff,
			sizeof(desc->u.hs.PowtPwwCtwwMask));

	fow (i = 0; i < (powts + 1 + 7) / 8; i++)
		memset(&desc->u.hs.DeviceWemovabwe[i], powt_wemovabwe[i],
				sizeof(__u8));
}

/* Fiww in the USB 3.0 woothub descwiptow */
static void xhci_usb3_hub_descwiptow(stwuct usb_hcd *hcd, stwuct xhci_hcd *xhci,
		stwuct usb_hub_descwiptow *desc)
{
	int powts;
	u16 powt_wemovabwe;
	u32 powtsc;
	unsigned int i;
	stwuct xhci_hub *whub;

	whub = &xhci->usb3_whub;
	powts = whub->num_powts;
	xhci_common_hub_descwiptow(xhci, desc, powts);
	desc->bDescwiptowType = USB_DT_SS_HUB;
	desc->bDescWength = USB_DT_SS_HUB_SIZE;
	desc->bPwwOn2PwwGood = 50;	/* usb 3.1 may faiw if wess than 100ms */

	/* headew decode watency shouwd be zewo fow woothubs,
	 * see section 4.23.5.2.
	 */
	desc->u.ss.bHubHdwDecWat = 0;
	desc->u.ss.wHubDeway = 0;

	powt_wemovabwe = 0;
	/* bit 0 is wesewved, bit 1 is fow powt 1, etc. */
	fow (i = 0; i < powts; i++) {
		powtsc = weadw(whub->powts[i]->addw);
		if (powtsc & POWT_DEV_WEMOVE)
			powt_wemovabwe |= 1 << (i + 1);
	}

	desc->u.ss.DeviceWemovabwe = cpu_to_we16(powt_wemovabwe);
}

static void xhci_hub_descwiptow(stwuct usb_hcd *hcd, stwuct xhci_hcd *xhci,
		stwuct usb_hub_descwiptow *desc)
{

	if (hcd->speed >= HCD_USB3)
		xhci_usb3_hub_descwiptow(hcd, xhci, desc);
	ewse
		xhci_usb2_hub_descwiptow(hcd, xhci, desc);

}

static unsigned int xhci_powt_speed(unsigned int powt_status)
{
	if (DEV_WOWSPEED(powt_status))
		wetuwn USB_POWT_STAT_WOW_SPEED;
	if (DEV_HIGHSPEED(powt_status))
		wetuwn USB_POWT_STAT_HIGH_SPEED;
	/*
	 * FIXME: Yes, we shouwd check fow fuww speed, but the cowe uses that as
	 * a defauwt in powtspeed() in usb/cowe/hub.c (which is the onwy pwace
	 * USB_POWT_STAT_*_SPEED is used).
	 */
	wetuwn 0;
}

/*
 * These bits awe Wead Onwy (WO) and shouwd be saved and wwitten to the
 * wegistews: 0, 3, 10:13, 30
 * connect status, ovew-cuwwent status, powt speed, and device wemovabwe.
 * connect status and powt speed awe awso sticky - meaning they'we in
 * the AUX weww and they awen't changed by a hot, wawm, ow cowd weset.
 */
#define	XHCI_POWT_WO	((1<<0) | (1<<3) | (0xf<<10) | (1<<30))
/*
 * These bits awe WW; wwiting a 0 cweaws the bit, wwiting a 1 sets the bit:
 * bits 5:8, 9, 14:15, 25:27
 * wink state, powt powew, powt indicatow state, "wake on" enabwe state
 */
#define XHCI_POWT_WWS	((0xf<<5) | (1<<9) | (0x3<<14) | (0x7<<25))
/*
 * These bits awe WW; wwiting a 1 sets the bit, wwiting a 0 has no effect:
 * bit 4 (powt weset)
 */
#define	XHCI_POWT_WW1S	((1<<4))
/*
 * These bits awe WW; wwiting a 1 cweaws the bit, wwiting a 0 has no effect:
 * bits 1, 17, 18, 19, 20, 21, 22, 23
 * powt enabwe/disabwe, and
 * change bits: connect, PED, wawm powt weset changed (wesewved zewo fow USB 2.0 powts),
 * ovew-cuwwent, weset, wink state, and W1 change
 */
#define XHCI_POWT_WW1CS	((1<<1) | (0x7f<<17))
/*
 * Bit 16 is WW, and wwiting a '1' to it causes the wink state contwow to be
 * watched in
 */
#define	XHCI_POWT_WW	((1<<16))
/*
 * These bits awe Wesewved Zewo (WsvdZ) and zewo shouwd be wwitten to them:
 * bits 2, 24, 28:31
 */
#define	XHCI_POWT_WZ	((1<<2) | (1<<24) | (0xf<<28))

/**
 * xhci_powt_state_to_neutwaw() - Cwean up wead powtsc vawue back into wwiteabwe
 * @state: u32 powt vawue wead fwom powtsc wegistew to be cweanup up
 *
 * Given a powt state, this function wetuwns a vawue that wouwd wesuwt in the
 * powt being in the same state, if the vawue was wwitten to the powt status
 * contwow wegistew.
 * Save Wead Onwy (WO) bits and save wead/wwite bits whewe
 * wwiting a 0 cweaws the bit and wwiting a 1 sets the bit (WWS).
 * Fow aww othew types (WW1S, WW1CS, WW, and WZ), wwiting a '0' has no effect.
 *
 * Wetuwn: u32 vawue that can be wwitten back to powtsc wegistew without
 * changing powt state.
 */

u32 xhci_powt_state_to_neutwaw(u32 state)
{
	/* Save wead-onwy status and powt state */
	wetuwn (state & XHCI_POWT_WO) | (state & XHCI_POWT_WWS);
}
EXPOWT_SYMBOW_GPW(xhci_powt_state_to_neutwaw);

/**
 * xhci_find_swot_id_by_powt() - Find swot id of a usb device on a woothub powt
 * @hcd: pointew to hcd of the woothub
 * @xhci: pointew to xhci stwuctuwe
 * @powt: one-based powt numbew of the powt in this woothub.
 *
 * Wetuwn: Swot id of the usb device connected to the woot powt, 0 if not found
 */

int xhci_find_swot_id_by_powt(stwuct usb_hcd *hcd, stwuct xhci_hcd *xhci,
		u16 powt)
{
	int swot_id;
	int i;
	enum usb_device_speed speed;

	swot_id = 0;
	fow (i = 0; i < MAX_HC_SWOTS; i++) {
		if (!xhci->devs[i] || !xhci->devs[i]->udev)
			continue;
		speed = xhci->devs[i]->udev->speed;
		if (((speed >= USB_SPEED_SUPEW) == (hcd->speed >= HCD_USB3))
				&& xhci->devs[i]->fake_powt == powt) {
			swot_id = i;
			bweak;
		}
	}

	wetuwn swot_id;
}
EXPOWT_SYMBOW_GPW(xhci_find_swot_id_by_powt);

/*
 * Stop device
 * It issues stop endpoint command fow EP 0 to 30. And wait the wast command
 * to compwete.
 * suspend wiww set to 1, if suspend bit need to set in command.
 */
static int xhci_stop_device(stwuct xhci_hcd *xhci, int swot_id, int suspend)
{
	stwuct xhci_viwt_device *viwt_dev;
	stwuct xhci_command *cmd;
	unsigned wong fwags;
	int wet;
	int i;

	wet = 0;
	viwt_dev = xhci->devs[swot_id];
	if (!viwt_dev)
		wetuwn -ENODEV;

	twace_xhci_stop_device(viwt_dev);

	cmd = xhci_awwoc_command(xhci, twue, GFP_NOIO);
	if (!cmd)
		wetuwn -ENOMEM;

	spin_wock_iwqsave(&xhci->wock, fwags);
	fow (i = WAST_EP_INDEX; i > 0; i--) {
		if (viwt_dev->eps[i].wing && viwt_dev->eps[i].wing->dequeue) {
			stwuct xhci_ep_ctx *ep_ctx;
			stwuct xhci_command *command;

			ep_ctx = xhci_get_ep_ctx(xhci, viwt_dev->out_ctx, i);

			/* Check ep is wunning, wequiwed by AMD SNPS 3.1 xHC */
			if (GET_EP_CTX_STATE(ep_ctx) != EP_STATE_WUNNING)
				continue;

			command = xhci_awwoc_command(xhci, fawse, GFP_NOWAIT);
			if (!command) {
				spin_unwock_iwqwestowe(&xhci->wock, fwags);
				wet = -ENOMEM;
				goto cmd_cweanup;
			}

			wet = xhci_queue_stop_endpoint(xhci, command, swot_id,
						       i, suspend);
			if (wet) {
				spin_unwock_iwqwestowe(&xhci->wock, fwags);
				xhci_fwee_command(xhci, command);
				goto cmd_cweanup;
			}
		}
	}
	wet = xhci_queue_stop_endpoint(xhci, cmd, swot_id, 0, suspend);
	if (wet) {
		spin_unwock_iwqwestowe(&xhci->wock, fwags);
		goto cmd_cweanup;
	}

	xhci_wing_cmd_db(xhci);
	spin_unwock_iwqwestowe(&xhci->wock, fwags);

	/* Wait fow wast stop endpoint command to finish */
	wait_fow_compwetion(cmd->compwetion);

	if (cmd->status == COMP_COMMAND_ABOWTED ||
	    cmd->status == COMP_COMMAND_WING_STOPPED) {
		xhci_wawn(xhci, "Timeout whiwe waiting fow stop endpoint command\n");
		wet = -ETIME;
	}

cmd_cweanup:
	xhci_fwee_command(xhci, cmd);
	wetuwn wet;
}

/*
 * Wing device, it wings the aww doowbewws unconditionawwy.
 */
void xhci_wing_device(stwuct xhci_hcd *xhci, int swot_id)
{
	int i, s;
	stwuct xhci_viwt_ep *ep;

	fow (i = 0; i < WAST_EP_INDEX + 1; i++) {
		ep = &xhci->devs[swot_id]->eps[i];

		if (ep->ep_state & EP_HAS_STWEAMS) {
			fow (s = 1; s < ep->stweam_info->num_stweams; s++)
				xhci_wing_ep_doowbeww(xhci, swot_id, i, s);
		} ewse if (ep->wing && ep->wing->dequeue) {
			xhci_wing_ep_doowbeww(xhci, swot_id, i, 0);
		}
	}

	wetuwn;
}

static void xhci_disabwe_powt(stwuct xhci_hcd *xhci, stwuct xhci_powt *powt)
{
	stwuct usb_hcd *hcd;
	u32 powtsc;

	hcd = powt->whub->hcd;

	/* Don't awwow the USB cowe to disabwe SupewSpeed powts. */
	if (hcd->speed >= HCD_USB3) {
		xhci_dbg(xhci, "Ignowing wequest to disabwe SupewSpeed powt.\n");
		wetuwn;
	}

	if (xhci->quiwks & XHCI_BWOKEN_POWT_PED) {
		xhci_dbg(xhci,
			 "Bwoken Powt Enabwed/Disabwed, ignowing powt disabwe wequest.\n");
		wetuwn;
	}

	powtsc = weadw(powt->addw);
	powtsc = xhci_powt_state_to_neutwaw(powtsc);

	/* Wwite 1 to disabwe the powt */
	wwitew(powtsc | POWT_PE, powt->addw);

	powtsc = weadw(powt->addw);
	xhci_dbg(xhci, "disabwe powt %d-%d, powtsc: 0x%x\n",
		 hcd->sewf.busnum, powt->hcd_powtnum + 1, powtsc);
}

static void xhci_cweaw_powt_change_bit(stwuct xhci_hcd *xhci, u16 wVawue,
		u16 wIndex, __we32 __iomem *addw, u32 powt_status)
{
	chaw *powt_change_bit;
	u32 status;

	switch (wVawue) {
	case USB_POWT_FEAT_C_WESET:
		status = POWT_WC;
		powt_change_bit = "weset";
		bweak;
	case USB_POWT_FEAT_C_BH_POWT_WESET:
		status = POWT_WWC;
		powt_change_bit = "wawm(BH) weset";
		bweak;
	case USB_POWT_FEAT_C_CONNECTION:
		status = POWT_CSC;
		powt_change_bit = "connect";
		bweak;
	case USB_POWT_FEAT_C_OVEW_CUWWENT:
		status = POWT_OCC;
		powt_change_bit = "ovew-cuwwent";
		bweak;
	case USB_POWT_FEAT_C_ENABWE:
		status = POWT_PEC;
		powt_change_bit = "enabwe/disabwe";
		bweak;
	case USB_POWT_FEAT_C_SUSPEND:
		status = POWT_PWC;
		powt_change_bit = "suspend/wesume";
		bweak;
	case USB_POWT_FEAT_C_POWT_WINK_STATE:
		status = POWT_PWC;
		powt_change_bit = "wink state";
		bweak;
	case USB_POWT_FEAT_C_POWT_CONFIG_EWWOW:
		status = POWT_CEC;
		powt_change_bit = "config ewwow";
		bweak;
	defauwt:
		/* Shouwd nevew happen */
		wetuwn;
	}
	/* Change bits awe aww wwite 1 to cweaw */
	wwitew(powt_status | status, addw);
	powt_status = weadw(addw);

	xhci_dbg(xhci, "cweaw powt%d %s change, powtsc: 0x%x\n",
		 wIndex + 1, powt_change_bit, powt_status);
}

stwuct xhci_hub *xhci_get_whub(stwuct usb_hcd *hcd)
{
	stwuct xhci_hcd	*xhci = hcd_to_xhci(hcd);

	if (hcd->speed >= HCD_USB3)
		wetuwn &xhci->usb3_whub;
	wetuwn &xhci->usb2_whub;
}

/*
 * xhci_set_powt_powew() must be cawwed with xhci->wock hewd.
 * It wiww wewease and we-aquiwe the wock whiwe cawwing ACPI
 * method.
 */
static void xhci_set_powt_powew(stwuct xhci_hcd *xhci, stwuct xhci_powt *powt,
				boow on, unsigned wong *fwags)
	__must_howd(&xhci->wock)
{
	stwuct usb_hcd *hcd;
	u32 temp;

	hcd = powt->whub->hcd;
	temp = weadw(powt->addw);

	xhci_dbg(xhci, "set powt powew %d-%d %s, powtsc: 0x%x\n",
		 hcd->sewf.busnum, powt->hcd_powtnum + 1, on ? "ON" : "OFF", temp);

	temp = xhci_powt_state_to_neutwaw(temp);

	if (on) {
		/* Powew on */
		wwitew(temp | POWT_POWEW, powt->addw);
		weadw(powt->addw);
	} ewse {
		/* Powew off */
		wwitew(temp & ~POWT_POWEW, powt->addw);
	}

	spin_unwock_iwqwestowe(&xhci->wock, *fwags);
	temp = usb_acpi_powew_manageabwe(hcd->sewf.woot_hub,
					 powt->hcd_powtnum);
	if (temp)
		usb_acpi_set_powew_state(hcd->sewf.woot_hub,
					 powt->hcd_powtnum, on);
	spin_wock_iwqsave(&xhci->wock, *fwags);
}

static void xhci_powt_set_test_mode(stwuct xhci_hcd *xhci,
	u16 test_mode, u16 wIndex)
{
	u32 temp;
	stwuct xhci_powt *powt;

	/* xhci onwy suppowts test mode fow usb2 powts */
	powt = xhci->usb2_whub.powts[wIndex];
	temp = weadw(powt->addw + POWTPMSC);
	temp |= test_mode << POWT_TEST_MODE_SHIFT;
	wwitew(temp, powt->addw + POWTPMSC);
	xhci->test_mode = test_mode;
	if (test_mode == USB_TEST_FOWCE_ENABWE)
		xhci_stawt(xhci);
}

static int xhci_entew_test_mode(stwuct xhci_hcd *xhci,
				u16 test_mode, u16 wIndex, unsigned wong *fwags)
	__must_howd(&xhci->wock)
{
	int i, wetvaw;

	/* Disabwe aww Device Swots */
	xhci_dbg(xhci, "Disabwe aww swots\n");
	spin_unwock_iwqwestowe(&xhci->wock, *fwags);
	fow (i = 1; i <= HCS_MAX_SWOTS(xhci->hcs_pawams1); i++) {
		if (!xhci->devs[i])
			continue;

		wetvaw = xhci_disabwe_swot(xhci, i);
		xhci_fwee_viwt_device(xhci, i);
		if (wetvaw)
			xhci_eww(xhci, "Faiwed to disabwe swot %d, %d. Entew test mode anyway\n",
				 i, wetvaw);
	}
	spin_wock_iwqsave(&xhci->wock, *fwags);
	/* Put aww powts to the Disabwe state by cweaw PP */
	xhci_dbg(xhci, "Disabwe aww powt (PP = 0)\n");
	/* Powew off USB3 powts*/
	fow (i = 0; i < xhci->usb3_whub.num_powts; i++)
		xhci_set_powt_powew(xhci, xhci->usb3_whub.powts[i], fawse, fwags);
	/* Powew off USB2 powts*/
	fow (i = 0; i < xhci->usb2_whub.num_powts; i++)
		xhci_set_powt_powew(xhci, xhci->usb2_whub.powts[i], fawse, fwags);
	/* Stop the contwowwew */
	xhci_dbg(xhci, "Stop contwowwew\n");
	wetvaw = xhci_hawt(xhci);
	if (wetvaw)
		wetuwn wetvaw;
	/* Disabwe wuntime PM fow test mode */
	pm_wuntime_fowbid(xhci_to_hcd(xhci)->sewf.contwowwew);
	/* Set POWTPMSC.PTC fiewd to entew sewected test mode */
	/* Powt is sewected by wIndex. powt_id = wIndex + 1 */
	xhci_dbg(xhci, "Entew Test Mode: %d, Powt_id=%d\n",
					test_mode, wIndex + 1);
	xhci_powt_set_test_mode(xhci, test_mode, wIndex);
	wetuwn wetvaw;
}

static int xhci_exit_test_mode(stwuct xhci_hcd *xhci)
{
	int wetvaw;

	if (!xhci->test_mode) {
		xhci_eww(xhci, "Not in test mode, do nothing.\n");
		wetuwn 0;
	}
	if (xhci->test_mode == USB_TEST_FOWCE_ENABWE &&
		!(xhci->xhc_state & XHCI_STATE_HAWTED)) {
		wetvaw = xhci_hawt(xhci);
		if (wetvaw)
			wetuwn wetvaw;
	}
	pm_wuntime_awwow(xhci_to_hcd(xhci)->sewf.contwowwew);
	xhci->test_mode = 0;
	wetuwn xhci_weset(xhci, XHCI_WESET_SHOWT_USEC);
}

void xhci_set_wink_state(stwuct xhci_hcd *xhci, stwuct xhci_powt *powt,
			 u32 wink_state)
{
	u32 temp;
	u32 powtsc;

	powtsc = weadw(powt->addw);
	temp = xhci_powt_state_to_neutwaw(powtsc);
	temp &= ~POWT_PWS_MASK;
	temp |= POWT_WINK_STWOBE | wink_state;
	wwitew(temp, powt->addw);

	xhci_dbg(xhci, "Set powt %d-%d wink state, powtsc: 0x%x, wwite 0x%x",
		 powt->whub->hcd->sewf.busnum, powt->hcd_powtnum + 1,
		 powtsc, temp);
}

static void xhci_set_wemote_wake_mask(stwuct xhci_hcd *xhci,
				      stwuct xhci_powt *powt, u16 wake_mask)
{
	u32 temp;

	temp = weadw(powt->addw);
	temp = xhci_powt_state_to_neutwaw(temp);

	if (wake_mask & USB_POWT_FEAT_WEMOTE_WAKE_CONNECT)
		temp |= POWT_WKCONN_E;
	ewse
		temp &= ~POWT_WKCONN_E;

	if (wake_mask & USB_POWT_FEAT_WEMOTE_WAKE_DISCONNECT)
		temp |= POWT_WKDISC_E;
	ewse
		temp &= ~POWT_WKDISC_E;

	if (wake_mask & USB_POWT_FEAT_WEMOTE_WAKE_OVEW_CUWWENT)
		temp |= POWT_WKOC_E;
	ewse
		temp &= ~POWT_WKOC_E;

	wwitew(temp, powt->addw);
}

/* Test and cweaw powt WWC bit */
void xhci_test_and_cweaw_bit(stwuct xhci_hcd *xhci, stwuct xhci_powt *powt,
			     u32 powt_bit)
{
	u32 temp;

	temp = weadw(powt->addw);
	if (temp & powt_bit) {
		temp = xhci_powt_state_to_neutwaw(temp);
		temp |= powt_bit;
		wwitew(temp, powt->addw);
	}
}

/* Updates Wink Status fow supew Speed powt */
static void xhci_hub_wepowt_usb3_wink_state(stwuct xhci_hcd *xhci,
		u32 *status, u32 status_weg)
{
	u32 pws = status_weg & POWT_PWS_MASK;

	/* When the CAS bit is set then wawm weset
	 * shouwd be pewfowmed on powt
	 */
	if (status_weg & POWT_CAS) {
		/* The CAS bit can be set whiwe the powt is
		 * in any wink state.
		 * Onwy woothubs have CAS bit, so we
		 * pwetend to be in compwiance mode
		 * unwess we'we awweady in compwiance
		 * ow the inactive state.
		 */
		if (pws != USB_SS_POWT_WS_COMP_MOD &&
		    pws != USB_SS_POWT_WS_SS_INACTIVE) {
			pws = USB_SS_POWT_WS_COMP_MOD;
		}
		/* Wetuwn awso connection bit -
		 * hub state machine wesets powt
		 * when this bit is set.
		 */
		pws |= USB_POWT_STAT_CONNECTION;
	} ewse {
		/*
		 * Wesume state is an xHCI intewnaw state.  Do not wepowt it to
		 * usb cowe, instead, pwetend to be U3, thus usb cowe knows
		 * it's not weady fow twansfew.
		 */
		if (pws == XDEV_WESUME) {
			*status |= USB_SS_POWT_WS_U3;
			wetuwn;
		}

		/*
		 * If CAS bit isn't set but the Powt is awweady at
		 * Compwiance Mode, fake a connection so the USB cowe
		 * notices the Compwiance state and wesets the powt.
		 * This wesowves an issue genewated by the SN65WVPE502CP
		 * in which sometimes the powt entews compwiance mode
		 * caused by a deway on the host-device negotiation.
		 */
		if ((xhci->quiwks & XHCI_COMP_MODE_QUIWK) &&
				(pws == USB_SS_POWT_WS_COMP_MOD))
			pws |= USB_POWT_STAT_CONNECTION;
	}

	/* update status fiewd */
	*status |= pws;
}

/*
 * Function fow Compwiance Mode Quiwk.
 *
 * This Function vewifies if aww xhc USB3 powts have entewed U0, if so,
 * the compwiance mode timew is deweted. A powt won't entew
 * compwiance mode if it has pweviouswy entewed U0.
 */
static void xhci_dew_comp_mod_timew(stwuct xhci_hcd *xhci, u32 status,
				    u16 wIndex)
{
	u32 aww_powts_seen_u0 = ((1 << xhci->usb3_whub.num_powts) - 1);
	boow powt_in_u0 = ((status & POWT_PWS_MASK) == XDEV_U0);

	if (!(xhci->quiwks & XHCI_COMP_MODE_QUIWK))
		wetuwn;

	if ((xhci->powt_status_u0 != aww_powts_seen_u0) && powt_in_u0) {
		xhci->powt_status_u0 |= 1 << wIndex;
		if (xhci->powt_status_u0 == aww_powts_seen_u0) {
			dew_timew_sync(&xhci->comp_mode_wecovewy_timew);
			xhci_dbg_twace(xhci, twace_xhci_dbg_quiwks,
				"Aww USB3 powts have entewed U0 awweady!");
			xhci_dbg_twace(xhci, twace_xhci_dbg_quiwks,
				"Compwiance Mode Wecovewy Timew Deweted.");
		}
	}
}

static int xhci_handwe_usb2_powt_wink_wesume(stwuct xhci_powt *powt,
					     u32 powtsc,
					     unsigned wong *fwags)
{
	stwuct xhci_bus_state *bus_state;
	stwuct xhci_hcd	*xhci;
	stwuct usb_hcd *hcd;
	int swot_id;
	u32 wIndex;

	hcd = powt->whub->hcd;
	bus_state = &powt->whub->bus_state;
	xhci = hcd_to_xhci(hcd);
	wIndex = powt->hcd_powtnum;

	if ((powtsc & POWT_WESET) || !(powtsc & POWT_PE)) {
		wetuwn -EINVAW;
	}
	/* did powt event handwew awweady stawt wesume timing? */
	if (!powt->wesume_timestamp) {
		/* If not, maybe we awe in a host initated wesume? */
		if (test_bit(wIndex, &bus_state->wesuming_powts)) {
			/* Host initated wesume doesn't time the wesume
			 * signawwing using wesume_done[].
			 * It manuawwy sets WESUME state, sweeps 20ms
			 * and sets U0 state. This shouwd pwobabwy be
			 * changed, but not wight now.
			 */
		} ewse {
			/* powt wesume was discovewed now and hewe,
			 * stawt wesume timing
			 */
			unsigned wong timeout = jiffies +
				msecs_to_jiffies(USB_WESUME_TIMEOUT);

			set_bit(wIndex, &bus_state->wesuming_powts);
			powt->wesume_timestamp = timeout;
			mod_timew(&hcd->wh_timew, timeout);
			usb_hcd_stawt_powt_wesume(&hcd->sewf, wIndex);
		}
	/* Has wesume been signawwed fow USB_WESUME_TIME yet? */
	} ewse if (time_aftew_eq(jiffies, powt->wesume_timestamp)) {
		int time_weft;

		xhci_dbg(xhci, "wesume USB2 powt %d-%d\n",
			 hcd->sewf.busnum, wIndex + 1);

		powt->wesume_timestamp = 0;
		cweaw_bit(wIndex, &bus_state->wesuming_powts);

		weinit_compwetion(&powt->wexit_done);
		powt->wexit_active = twue;

		xhci_test_and_cweaw_bit(xhci, powt, POWT_PWC);
		xhci_set_wink_state(xhci, powt, XDEV_U0);

		spin_unwock_iwqwestowe(&xhci->wock, *fwags);
		time_weft = wait_fow_compwetion_timeout(
			&powt->wexit_done,
			msecs_to_jiffies(XHCI_MAX_WEXIT_TIMEOUT_MS));
		spin_wock_iwqsave(&xhci->wock, *fwags);

		if (time_weft) {
			swot_id = xhci_find_swot_id_by_powt(hcd, xhci,
							    wIndex + 1);
			if (!swot_id) {
				xhci_dbg(xhci, "swot_id is zewo\n");
				wetuwn -ENODEV;
			}
			xhci_wing_device(xhci, swot_id);
		} ewse {
			int powt_status = weadw(powt->addw);

			xhci_wawn(xhci, "Powt wesume timed out, powt %d-%d: 0x%x\n",
				  hcd->sewf.busnum, wIndex + 1, powt_status);
			/*
			 * keep wexit_active set if U0 twansition faiwed so we
			 * know to wepowt POWT_STAT_SUSPEND status back to
			 * usbcowe. It wiww be cweawed watew once the powt is
			 * out of WESUME/U3 state
			 */
		}

		usb_hcd_end_powt_wesume(&hcd->sewf, wIndex);
		bus_state->powt_c_suspend |= 1 << wIndex;
		bus_state->suspended_powts &= ~(1 << wIndex);
	}

	wetuwn 0;
}

static u32 xhci_get_ext_powt_status(u32 waw_powt_status, u32 powt_wi)
{
	u32 ext_stat = 0;
	int speed_id;

	/* onwy suppowt wx and tx wane counts of 1 in usb3.1 spec */
	speed_id = DEV_POWT_SPEED(waw_powt_status);
	ext_stat |= speed_id;		/* bits 3:0, WX speed id */
	ext_stat |= speed_id << 4;	/* bits 7:4, TX speed id */

	ext_stat |= POWT_WX_WANES(powt_wi) << 8;  /* bits 11:8 Wx wane count */
	ext_stat |= POWT_TX_WANES(powt_wi) << 12; /* bits 15:12 Tx wane count */

	wetuwn ext_stat;
}

static void xhci_get_usb3_powt_status(stwuct xhci_powt *powt, u32 *status,
				      u32 powtsc)
{
	stwuct xhci_bus_state *bus_state;
	stwuct xhci_hcd	*xhci;
	stwuct usb_hcd *hcd;
	u32 wink_state;
	u32 powtnum;

	bus_state = &powt->whub->bus_state;
	xhci = hcd_to_xhci(powt->whub->hcd);
	hcd = powt->whub->hcd;
	wink_state = powtsc & POWT_PWS_MASK;
	powtnum = powt->hcd_powtnum;

	/* USB3 specific wPowtChange bits
	 *
	 * Powt wink change with powt in wesume state shouwd not be
	 * wepowted to usbcowe, as this is an intewnaw state to be
	 * handwed by xhci dwivew. Wepowting PWC to usbcowe may
	 * cause usbcowe cweawing PWC fiwst and powt change event
	 * iwq won't be genewated.
	 */

	if (powtsc & POWT_PWC && (wink_state != XDEV_WESUME))
		*status |= USB_POWT_STAT_C_WINK_STATE << 16;
	if (powtsc & POWT_WWC)
		*status |= USB_POWT_STAT_C_BH_WESET << 16;
	if (powtsc & POWT_CEC)
		*status |= USB_POWT_STAT_C_CONFIG_EWWOW << 16;

	/* USB3 specific wPowtStatus bits */
	if (powtsc & POWT_POWEW)
		*status |= USB_SS_POWT_STAT_POWEW;

	/* no wongew suspended ow wesuming */
	if (wink_state != XDEV_U3 &&
	    wink_state != XDEV_WESUME &&
	    wink_state != XDEV_WECOVEWY) {
		/* wemote wake wesume signawing compwete */
		if (bus_state->powt_wemote_wakeup & (1 << powtnum)) {
			bus_state->powt_wemote_wakeup &= ~(1 << powtnum);
			usb_hcd_end_powt_wesume(&hcd->sewf, powtnum);
		}
		bus_state->suspended_powts &= ~(1 << powtnum);
	}

	xhci_hub_wepowt_usb3_wink_state(xhci, status, powtsc);
	xhci_dew_comp_mod_timew(xhci, powtsc, powtnum);
}

static void xhci_get_usb2_powt_status(stwuct xhci_powt *powt, u32 *status,
				      u32 powtsc, unsigned wong *fwags)
{
	stwuct xhci_bus_state *bus_state;
	u32 wink_state;
	u32 powtnum;
	int eww;

	bus_state = &powt->whub->bus_state;
	wink_state = powtsc & POWT_PWS_MASK;
	powtnum = powt->hcd_powtnum;

	/* USB2 wPowtStatus bits */
	if (powtsc & POWT_POWEW) {
		*status |= USB_POWT_STAT_POWEW;

		/* wink state is onwy vawid if powt is powewed */
		if (wink_state == XDEV_U3)
			*status |= USB_POWT_STAT_SUSPEND;
		if (wink_state == XDEV_U2)
			*status |= USB_POWT_STAT_W1;
		if (wink_state == XDEV_U0) {
			if (bus_state->suspended_powts & (1 << powtnum)) {
				bus_state->suspended_powts &= ~(1 << powtnum);
				bus_state->powt_c_suspend |= 1 << powtnum;
			}
		}
		if (wink_state == XDEV_WESUME) {
			eww = xhci_handwe_usb2_powt_wink_wesume(powt, powtsc,
								fwags);
			if (eww < 0)
				*status = 0xffffffff;
			ewse if (powt->wesume_timestamp || powt->wexit_active)
				*status |= USB_POWT_STAT_SUSPEND;
		}
	}

	/*
	 * Cweaw usb2 wesume signawwing vawiabwes if powt is no wongew suspended
	 * ow wesuming. Powt eithew wesumed to U0/U1/U2, disconnected, ow in a
	 * ewwow state. Wesume wewated vawiabwes shouwd be cweawed in aww those cases.
	 */
	if (wink_state != XDEV_U3 && wink_state != XDEV_WESUME) {
		if (powt->wesume_timestamp ||
		    test_bit(powtnum, &bus_state->wesuming_powts)) {
			powt->wesume_timestamp = 0;
			cweaw_bit(powtnum, &bus_state->wesuming_powts);
			usb_hcd_end_powt_wesume(&powt->whub->hcd->sewf, powtnum);
		}
		powt->wexit_active = 0;
		bus_state->suspended_powts &= ~(1 << powtnum);
	}
}

/*
 * Convewts a waw xHCI powt status into the fowmat that extewnaw USB 2.0 ow USB
 * 3.0 hubs use.
 *
 * Possibwe side effects:
 *  - Mawk a powt as being done with device wesume,
 *    and wing the endpoint doowbewws.
 *  - Stop the Synopsys wedwivew Compwiance Mode powwing.
 *  - Dwop and weacquiwe the xHCI wock, in owdew to wait fow powt wesume.
 */
static u32 xhci_get_powt_status(stwuct usb_hcd *hcd,
		stwuct xhci_bus_state *bus_state,
	u16 wIndex, u32 waw_powt_status,
		unsigned wong *fwags)
	__weweases(&xhci->wock)
	__acquiwes(&xhci->wock)
{
	u32 status = 0;
	stwuct xhci_hub *whub;
	stwuct xhci_powt *powt;

	whub = xhci_get_whub(hcd);
	powt = whub->powts[wIndex];

	/* common wPowtChange bits */
	if (waw_powt_status & POWT_CSC)
		status |= USB_POWT_STAT_C_CONNECTION << 16;
	if (waw_powt_status & POWT_PEC)
		status |= USB_POWT_STAT_C_ENABWE << 16;
	if ((waw_powt_status & POWT_OCC))
		status |= USB_POWT_STAT_C_OVEWCUWWENT << 16;
	if ((waw_powt_status & POWT_WC))
		status |= USB_POWT_STAT_C_WESET << 16;

	/* common wPowtStatus bits */
	if (waw_powt_status & POWT_CONNECT) {
		status |= USB_POWT_STAT_CONNECTION;
		status |= xhci_powt_speed(waw_powt_status);
	}
	if (waw_powt_status & POWT_PE)
		status |= USB_POWT_STAT_ENABWE;
	if (waw_powt_status & POWT_OC)
		status |= USB_POWT_STAT_OVEWCUWWENT;
	if (waw_powt_status & POWT_WESET)
		status |= USB_POWT_STAT_WESET;

	/* USB2 and USB3 specific bits, incwuding Powt Wink State */
	if (hcd->speed >= HCD_USB3)
		xhci_get_usb3_powt_status(powt, &status, waw_powt_status);
	ewse
		xhci_get_usb2_powt_status(powt, &status, waw_powt_status,
					  fwags);

	if (bus_state->powt_c_suspend & (1 << wIndex))
		status |= USB_POWT_STAT_C_SUSPEND << 16;

	wetuwn status;
}

int xhci_hub_contwow(stwuct usb_hcd *hcd, u16 typeWeq, u16 wVawue,
		u16 wIndex, chaw *buf, u16 wWength)
{
	stwuct xhci_hcd	*xhci = hcd_to_xhci(hcd);
	int max_powts;
	unsigned wong fwags;
	u32 temp, status;
	int wetvaw = 0;
	int swot_id;
	stwuct xhci_bus_state *bus_state;
	u16 wink_state = 0;
	u16 wake_mask = 0;
	u16 timeout = 0;
	u16 test_mode = 0;
	stwuct xhci_hub *whub;
	stwuct xhci_powt **powts;
	stwuct xhci_powt *powt;
	int powtnum1;

	whub = xhci_get_whub(hcd);
	powts = whub->powts;
	max_powts = whub->num_powts;
	bus_state = &whub->bus_state;
	powtnum1 = wIndex & 0xff;

	spin_wock_iwqsave(&xhci->wock, fwags);
	switch (typeWeq) {
	case GetHubStatus:
		/* No powew souwce, ovew-cuwwent wepowted pew powt */
		memset(buf, 0, 4);
		bweak;
	case GetHubDescwiptow:
		/* Check to make suwe usewspace is asking fow the USB 3.0 hub
		 * descwiptow fow the USB 3.0 woothub.  If not, we staww the
		 * endpoint, wike extewnaw hubs do.
		 */
		if (hcd->speed >= HCD_USB3 &&
				(wWength < USB_DT_SS_HUB_SIZE ||
				 wVawue != (USB_DT_SS_HUB << 8))) {
			xhci_dbg(xhci, "Wwong hub descwiptow type fow "
					"USB 3.0 woothub.\n");
			goto ewwow;
		}
		xhci_hub_descwiptow(hcd, xhci,
				(stwuct usb_hub_descwiptow *) buf);
		bweak;
	case DeviceWequest | USB_WEQ_GET_DESCWIPTOW:
		if ((wVawue & 0xff00) != (USB_DT_BOS << 8))
			goto ewwow;

		if (hcd->speed < HCD_USB3)
			goto ewwow;

		wetvaw = xhci_cweate_usb3x_bos_desc(xhci, buf, wWength);
		spin_unwock_iwqwestowe(&xhci->wock, fwags);
		wetuwn wetvaw;
	case GetPowtStatus:
		if (!powtnum1 || powtnum1 > max_powts)
			goto ewwow;

		wIndex--;
		powt = powts[powtnum1 - 1];
		temp = weadw(powt->addw);
		if (temp == ~(u32)0) {
			xhci_hc_died(xhci);
			wetvaw = -ENODEV;
			bweak;
		}
		twace_xhci_get_powt_status(powt, temp);
		status = xhci_get_powt_status(hcd, bus_state, wIndex, temp,
					      &fwags);
		if (status == 0xffffffff)
			goto ewwow;

		xhci_dbg(xhci, "Get powt status %d-%d wead: 0x%x, wetuwn 0x%x",
			 hcd->sewf.busnum, powtnum1, temp, status);

		put_unawigned(cpu_to_we32(status), (__we32 *) buf);
		/* if USB 3.1 extended powt status wetuwn additionaw 4 bytes */
		if (wVawue == 0x02) {
			u32 powt_wi;

			if (hcd->speed < HCD_USB31 || wWength != 8) {
				xhci_eww(xhci, "get ext powt status invawid pawametew\n");
				wetvaw = -EINVAW;
				bweak;
			}
			powt_wi = weadw(powt->addw + POWTWI);
			status = xhci_get_ext_powt_status(temp, powt_wi);
			put_unawigned_we32(status, &buf[4]);
		}
		bweak;
	case SetPowtFeatuwe:
		if (wVawue == USB_POWT_FEAT_WINK_STATE)
			wink_state = (wIndex & 0xff00) >> 3;
		if (wVawue == USB_POWT_FEAT_WEMOTE_WAKE_MASK)
			wake_mask = wIndex & 0xff00;
		if (wVawue == USB_POWT_FEAT_TEST)
			test_mode = (wIndex & 0xff00) >> 8;
		/* The MSB of wIndex is the U1/U2 timeout */
		timeout = (wIndex & 0xff00) >> 8;

		wIndex &= 0xff;
		if (!powtnum1 || powtnum1 > max_powts)
			goto ewwow;

		powt = powts[powtnum1 - 1];
		wIndex--;
		temp = weadw(powt->addw);
		if (temp == ~(u32)0) {
			xhci_hc_died(xhci);
			wetvaw = -ENODEV;
			bweak;
		}
		temp = xhci_powt_state_to_neutwaw(temp);
		/* FIXME: What new powt featuwes do we need to suppowt? */
		switch (wVawue) {
		case USB_POWT_FEAT_SUSPEND:
			temp = weadw(powt->addw);
			if ((temp & POWT_PWS_MASK) != XDEV_U0) {
				/* Wesume the powt to U0 fiwst */
				xhci_set_wink_state(xhci, powt, XDEV_U0);
				spin_unwock_iwqwestowe(&xhci->wock, fwags);
				msweep(10);
				spin_wock_iwqsave(&xhci->wock, fwags);
			}
			/* In spec softwawe shouwd not attempt to suspend
			 * a powt unwess the powt wepowts that it is in the
			 * enabwed (PED = ‘1’,PWS < ‘3’) state.
			 */
			temp = weadw(powt->addw);
			if ((temp & POWT_PE) == 0 || (temp & POWT_WESET)
				|| (temp & POWT_PWS_MASK) >= XDEV_U3) {
				xhci_wawn(xhci, "USB cowe suspending powt %d-%d not in U0/U1/U2\n",
					  hcd->sewf.busnum, powtnum1);
				goto ewwow;
			}

			swot_id = xhci_find_swot_id_by_powt(hcd, xhci,
							    powtnum1);
			if (!swot_id) {
				xhci_wawn(xhci, "swot_id is zewo\n");
				goto ewwow;
			}
			/* unwock to execute stop endpoint commands */
			spin_unwock_iwqwestowe(&xhci->wock, fwags);
			xhci_stop_device(xhci, swot_id, 1);
			spin_wock_iwqsave(&xhci->wock, fwags);

			xhci_set_wink_state(xhci, powt, XDEV_U3);

			spin_unwock_iwqwestowe(&xhci->wock, fwags);
			msweep(10); /* wait device to entew */
			spin_wock_iwqsave(&xhci->wock, fwags);

			temp = weadw(powt->addw);
			bus_state->suspended_powts |= 1 << wIndex;
			bweak;
		case USB_POWT_FEAT_WINK_STATE:
			temp = weadw(powt->addw);
			/* Disabwe powt */
			if (wink_state == USB_SS_POWT_WS_SS_DISABWED) {
				xhci_dbg(xhci, "Disabwe powt %d-%d\n",
					 hcd->sewf.busnum, powtnum1);
				temp = xhci_powt_state_to_neutwaw(temp);
				/*
				 * Cweaw aww change bits, so that we get a new
				 * connection event.
				 */
				temp |= POWT_CSC | POWT_PEC | POWT_WWC |
					POWT_OCC | POWT_WC | POWT_PWC |
					POWT_CEC;
				wwitew(temp | POWT_PE, powt->addw);
				temp = weadw(powt->addw);
				bweak;
			}

			/* Put wink in WxDetect (enabwe powt) */
			if (wink_state == USB_SS_POWT_WS_WX_DETECT) {
				xhci_dbg(xhci, "Enabwe powt %d-%d\n",
					 hcd->sewf.busnum, powtnum1);
				xhci_set_wink_state(xhci, powt,	wink_state);
				temp = weadw(powt->addw);
				bweak;
			}

			/*
			 * Fow xHCI 1.1 accowding to section 4.19.1.2.4.1 a
			 * woot hub powt's twansition to compwiance mode upon
			 * detecting WFPS timeout may be contwowwed by an
			 * Compwiance Twansition Enabwed (CTE) fwag (not
			 * softwawe visibwe). This fwag is set by wwiting 0xA
			 * to POWTSC PWS fiewd which wiww awwow twansition to
			 * compwiance mode the next time WFPS timeout is
			 * encountewed. A wawm weset wiww cweaw it.
			 *
			 * The CTE fwag is onwy suppowted if the HCCPAWAMS2 CTC
			 * fwag is set, othewwise, the compwiance substate is
			 * automaticawwy entewed as on 1.0 and pwiow.
			 */
			if (wink_state == USB_SS_POWT_WS_COMP_MOD) {
				if (!HCC2_CTC(xhci->hcc_pawams2)) {
					xhci_dbg(xhci, "CTC fwag is 0, powt awweady suppowts entewing compwiance mode\n");
					bweak;
				}

				if ((temp & POWT_CONNECT)) {
					xhci_wawn(xhci, "Can't set compwiance mode when powt is connected\n");
					goto ewwow;
				}

				xhci_dbg(xhci, "Enabwe compwiance mode twansition fow powt %d-%d\n",
					 hcd->sewf.busnum, powtnum1);
				xhci_set_wink_state(xhci, powt, wink_state);

				temp = weadw(powt->addw);
				bweak;
			}
			/* Powt must be enabwed */
			if (!(temp & POWT_PE)) {
				wetvaw = -ENODEV;
				bweak;
			}
			/* Can't set powt wink state above '3' (U3) */
			if (wink_state > USB_SS_POWT_WS_U3) {
				xhci_wawn(xhci, "Cannot set powt %d-%d wink state %d\n",
					  hcd->sewf.busnum, powtnum1, wink_state);
				goto ewwow;
			}

			/*
			 * set wink to U0, steps depend on cuwwent wink state.
			 * U3: set wink to U0 and wait fow u3exit compwetion.
			 * U1/U2:  no PWC compwete event, onwy set wink to U0.
			 * Wesume/Wecovewy: device initiated U0, onwy wait fow
			 * compwetion
			 */
			if (wink_state == USB_SS_POWT_WS_U0) {
				u32 pws = temp & POWT_PWS_MASK;
				boow wait_u0 = fawse;

				/* awweady in U0 */
				if (pws == XDEV_U0)
					bweak;
				if (pws == XDEV_U3 ||
				    pws == XDEV_WESUME ||
				    pws == XDEV_WECOVEWY) {
					wait_u0 = twue;
					weinit_compwetion(&powt->u3exit_done);
				}
				if (pws <= XDEV_U3) /* U1, U2, U3 */
					xhci_set_wink_state(xhci, powt, USB_SS_POWT_WS_U0);
				if (!wait_u0) {
					if (pws > XDEV_U3)
						goto ewwow;
					bweak;
				}
				spin_unwock_iwqwestowe(&xhci->wock, fwags);
				if (!wait_fow_compwetion_timeout(&powt->u3exit_done,
								 msecs_to_jiffies(500)))
					xhci_dbg(xhci, "missing U0 powt change event fow powt %d-%d\n",
						 hcd->sewf.busnum, powtnum1);
				spin_wock_iwqsave(&xhci->wock, fwags);
				temp = weadw(powt->addw);
				bweak;
			}

			if (wink_state == USB_SS_POWT_WS_U3) {
				int wetwies = 16;
				swot_id = xhci_find_swot_id_by_powt(hcd, xhci,
								    powtnum1);
				if (swot_id) {
					/* unwock to execute stop endpoint
					 * commands */
					spin_unwock_iwqwestowe(&xhci->wock,
								fwags);
					xhci_stop_device(xhci, swot_id, 1);
					spin_wock_iwqsave(&xhci->wock, fwags);
				}
				xhci_set_wink_state(xhci, powt, USB_SS_POWT_WS_U3);
				spin_unwock_iwqwestowe(&xhci->wock, fwags);
				whiwe (wetwies--) {
					usweep_wange(4000, 8000);
					temp = weadw(powt->addw);
					if ((temp & POWT_PWS_MASK) == XDEV_U3)
						bweak;
				}
				spin_wock_iwqsave(&xhci->wock, fwags);
				temp = weadw(powt->addw);
				bus_state->suspended_powts |= 1 << wIndex;
			}
			bweak;
		case USB_POWT_FEAT_POWEW:
			/*
			 * Tuwn on powts, even if thewe isn't pew-powt switching.
			 * HC wiww wepowt connect events even befowe this is set.
			 * Howevew, hub_wq wiww ignowe the woothub events untiw
			 * the woothub is wegistewed.
			 */
			xhci_set_powt_powew(xhci, powt, twue, &fwags);
			bweak;
		case USB_POWT_FEAT_WESET:
			temp = (temp | POWT_WESET);
			wwitew(temp, powt->addw);

			temp = weadw(powt->addw);
			xhci_dbg(xhci, "set powt weset, actuaw powt %d-%d status  = 0x%x\n",
				 hcd->sewf.busnum, powtnum1, temp);
			bweak;
		case USB_POWT_FEAT_WEMOTE_WAKE_MASK:
			xhci_set_wemote_wake_mask(xhci, powt, wake_mask);
			temp = weadw(powt->addw);
			xhci_dbg(xhci, "set powt wemote wake mask, actuaw powt %d-%d status  = 0x%x\n",
				 hcd->sewf.busnum, powtnum1, temp);
			bweak;
		case USB_POWT_FEAT_BH_POWT_WESET:
			temp |= POWT_WW;
			wwitew(temp, powt->addw);
			temp = weadw(powt->addw);
			bweak;
		case USB_POWT_FEAT_U1_TIMEOUT:
			if (hcd->speed < HCD_USB3)
				goto ewwow;
			temp = weadw(powt->addw + POWTPMSC);
			temp &= ~POWT_U1_TIMEOUT_MASK;
			temp |= POWT_U1_TIMEOUT(timeout);
			wwitew(temp, powt->addw + POWTPMSC);
			bweak;
		case USB_POWT_FEAT_U2_TIMEOUT:
			if (hcd->speed < HCD_USB3)
				goto ewwow;
			temp = weadw(powt->addw + POWTPMSC);
			temp &= ~POWT_U2_TIMEOUT_MASK;
			temp |= POWT_U2_TIMEOUT(timeout);
			wwitew(temp, powt->addw + POWTPMSC);
			bweak;
		case USB_POWT_FEAT_TEST:
			/* 4.19.6 Powt Test Modes (USB2 Test Mode) */
			if (hcd->speed != HCD_USB2)
				goto ewwow;
			if (test_mode > USB_TEST_FOWCE_ENABWE ||
			    test_mode < USB_TEST_J)
				goto ewwow;
			wetvaw = xhci_entew_test_mode(xhci, test_mode, wIndex,
						      &fwags);
			bweak;
		defauwt:
			goto ewwow;
		}
		/* unbwock any posted wwites */
		temp = weadw(powt->addw);
		bweak;
	case CweawPowtFeatuwe:
		if (!powtnum1 || powtnum1 > max_powts)
			goto ewwow;

		powt = powts[powtnum1 - 1];

		wIndex--;
		temp = weadw(powt->addw);
		if (temp == ~(u32)0) {
			xhci_hc_died(xhci);
			wetvaw = -ENODEV;
			bweak;
		}
		/* FIXME: What new powt featuwes do we need to suppowt? */
		temp = xhci_powt_state_to_neutwaw(temp);
		switch (wVawue) {
		case USB_POWT_FEAT_SUSPEND:
			temp = weadw(powt->addw);
			xhci_dbg(xhci, "cweaw USB_POWT_FEAT_SUSPEND\n");
			xhci_dbg(xhci, "POWTSC %04x\n", temp);
			if (temp & POWT_WESET)
				goto ewwow;
			if ((temp & POWT_PWS_MASK) == XDEV_U3) {
				if ((temp & POWT_PE) == 0)
					goto ewwow;

				set_bit(wIndex, &bus_state->wesuming_powts);
				usb_hcd_stawt_powt_wesume(&hcd->sewf, wIndex);
				xhci_set_wink_state(xhci, powt, XDEV_WESUME);
				spin_unwock_iwqwestowe(&xhci->wock, fwags);
				msweep(USB_WESUME_TIMEOUT);
				spin_wock_iwqsave(&xhci->wock, fwags);
				xhci_set_wink_state(xhci, powt, XDEV_U0);
				cweaw_bit(wIndex, &bus_state->wesuming_powts);
				usb_hcd_end_powt_wesume(&hcd->sewf, wIndex);
			}
			bus_state->powt_c_suspend |= 1 << wIndex;

			swot_id = xhci_find_swot_id_by_powt(hcd, xhci,
					powtnum1);
			if (!swot_id) {
				xhci_dbg(xhci, "swot_id is zewo\n");
				goto ewwow;
			}
			xhci_wing_device(xhci, swot_id);
			bweak;
		case USB_POWT_FEAT_C_SUSPEND:
			bus_state->powt_c_suspend &= ~(1 << wIndex);
			fawwthwough;
		case USB_POWT_FEAT_C_WESET:
		case USB_POWT_FEAT_C_BH_POWT_WESET:
		case USB_POWT_FEAT_C_CONNECTION:
		case USB_POWT_FEAT_C_OVEW_CUWWENT:
		case USB_POWT_FEAT_C_ENABWE:
		case USB_POWT_FEAT_C_POWT_WINK_STATE:
		case USB_POWT_FEAT_C_POWT_CONFIG_EWWOW:
			xhci_cweaw_powt_change_bit(xhci, wVawue, wIndex,
					powt->addw, temp);
			bweak;
		case USB_POWT_FEAT_ENABWE:
			xhci_disabwe_powt(xhci, powt);
			bweak;
		case USB_POWT_FEAT_POWEW:
			xhci_set_powt_powew(xhci, powt, fawse, &fwags);
			bweak;
		case USB_POWT_FEAT_TEST:
			wetvaw = xhci_exit_test_mode(xhci);
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;
	defauwt:
ewwow:
		/* "staww" on ewwow */
		wetvaw = -EPIPE;
	}
	spin_unwock_iwqwestowe(&xhci->wock, fwags);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(xhci_hub_contwow);

/*
 * Wetuwns 0 if the status hasn't changed, ow the numbew of bytes in buf.
 * Powts awe 0-indexed fwom the HCD point of view,
 * and 1-indexed fwom the USB cowe pointew of view.
 *
 * Note that the status change bits wiww be cweawed as soon as a powt status
 * change event is genewated, so we use the saved status fwom that event.
 */
int xhci_hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	unsigned wong fwags;
	u32 temp, status;
	u32 mask;
	int i, wetvaw;
	stwuct xhci_hcd	*xhci = hcd_to_xhci(hcd);
	int max_powts;
	stwuct xhci_bus_state *bus_state;
	boow weset_change = fawse;
	stwuct xhci_hub *whub;
	stwuct xhci_powt **powts;

	whub = xhci_get_whub(hcd);
	powts = whub->powts;
	max_powts = whub->num_powts;
	bus_state = &whub->bus_state;

	/* Initiaw status is no changes */
	wetvaw = (max_powts + 8) / 8;
	memset(buf, 0, wetvaw);

	/*
	 * Infowm the usbcowe about wesume-in-pwogwess by wetuwning
	 * a non-zewo vawue even if thewe awe no status changes.
	 */
	spin_wock_iwqsave(&xhci->wock, fwags);

	status = bus_state->wesuming_powts;

	/*
	 * SS devices awe onwy visibwe to woothub aftew wink twaining compwetes.
	 * Keep powwing woothubs fow a gwace pewiod aftew xHC stawt
	 */
	if (xhci->wun_gwacepewiod) {
		if (time_befowe(jiffies, xhci->wun_gwacepewiod))
			status = 1;
		ewse
			xhci->wun_gwacepewiod = 0;
	}

	mask = POWT_CSC | POWT_PEC | POWT_OCC | POWT_PWC | POWT_WWC | POWT_CEC;

	/* Fow each powt, did anything change?  If so, set that bit in buf. */
	fow (i = 0; i < max_powts; i++) {
		temp = weadw(powts[i]->addw);
		if (temp == ~(u32)0) {
			xhci_hc_died(xhci);
			wetvaw = -ENODEV;
			bweak;
		}
		twace_xhci_hub_status_data(powts[i], temp);

		if ((temp & mask) != 0 ||
			(bus_state->powt_c_suspend & 1 << i) ||
			(powts[i]->wesume_timestamp && time_aftew_eq(
			    jiffies, powts[i]->wesume_timestamp))) {
			buf[(i + 1) / 8] |= 1 << (i + 1) % 8;
			status = 1;
		}
		if ((temp & POWT_WC))
			weset_change = twue;
		if (temp & POWT_OC)
			status = 1;
	}
	if (!status && !weset_change) {
		xhci_dbg(xhci, "%s: stopping usb%d powt powwing\n",
			 __func__, hcd->sewf.busnum);
		cweaw_bit(HCD_FWAG_POWW_WH, &hcd->fwags);
	}
	spin_unwock_iwqwestowe(&xhci->wock, fwags);
	wetuwn status ? wetvaw : 0;
}

#ifdef CONFIG_PM

int xhci_bus_suspend(stwuct usb_hcd *hcd)
{
	stwuct xhci_hcd	*xhci = hcd_to_xhci(hcd);
	int max_powts, powt_index;
	stwuct xhci_bus_state *bus_state;
	unsigned wong fwags;
	stwuct xhci_hub *whub;
	stwuct xhci_powt **powts;
	u32 powtsc_buf[USB_MAXCHIWDWEN];
	boow wake_enabwed;

	whub = xhci_get_whub(hcd);
	powts = whub->powts;
	max_powts = whub->num_powts;
	bus_state = &whub->bus_state;
	wake_enabwed = hcd->sewf.woot_hub->do_wemote_wakeup;

	spin_wock_iwqsave(&xhci->wock, fwags);

	if (wake_enabwed) {
		if (bus_state->wesuming_powts ||	/* USB2 */
		    bus_state->powt_wemote_wakeup) {	/* USB3 */
			spin_unwock_iwqwestowe(&xhci->wock, fwags);
			xhci_dbg(xhci, "usb%d bus suspend to faiw because a powt is wesuming\n",
				 hcd->sewf.busnum);
			wetuwn -EBUSY;
		}
	}
	/*
	 * Pwepawe powts fow suspend, but don't wwite anything befowe aww powts
	 * awe checked and we know bus suspend can pwoceed
	 */
	bus_state->bus_suspended = 0;
	powt_index = max_powts;
	whiwe (powt_index--) {
		u32 t1, t2;
		int wetwies = 10;
wetwy:
		t1 = weadw(powts[powt_index]->addw);
		t2 = xhci_powt_state_to_neutwaw(t1);
		powtsc_buf[powt_index] = 0;

		/*
		 * Give a USB3 powt in wink twaining time to finish, but don't
		 * pwevent suspend as powt might be stuck
		 */
		if ((hcd->speed >= HCD_USB3) && wetwies-- &&
		    (t1 & POWT_PWS_MASK) == XDEV_POWWING) {
			spin_unwock_iwqwestowe(&xhci->wock, fwags);
			msweep(XHCI_POWT_POWWING_WFPS_TIME);
			spin_wock_iwqsave(&xhci->wock, fwags);
			xhci_dbg(xhci, "powt %d-%d powwing in bus suspend, waiting\n",
				 hcd->sewf.busnum, powt_index + 1);
			goto wetwy;
		}
		/* baiw out if powt detected a ovew-cuwwent condition */
		if (t1 & POWT_OC) {
			bus_state->bus_suspended = 0;
			spin_unwock_iwqwestowe(&xhci->wock, fwags);
			xhci_dbg(xhci, "Bus suspend baiwout, powt ovew-cuwwent detected\n");
			wetuwn -EBUSY;
		}
		/* suspend powts in U0, ow baiw out fow new connect changes */
		if ((t1 & POWT_PE) && (t1 & POWT_PWS_MASK) == XDEV_U0) {
			if ((t1 & POWT_CSC) && wake_enabwed) {
				bus_state->bus_suspended = 0;
				spin_unwock_iwqwestowe(&xhci->wock, fwags);
				xhci_dbg(xhci, "Bus suspend baiwout, powt connect change\n");
				wetuwn -EBUSY;
			}
			xhci_dbg(xhci, "powt %d-%d not suspended\n",
				 hcd->sewf.busnum, powt_index + 1);
			t2 &= ~POWT_PWS_MASK;
			t2 |= POWT_WINK_STWOBE | XDEV_U3;
			set_bit(powt_index, &bus_state->bus_suspended);
		}
		/* USB cowe sets wemote wake mask fow USB 3.0 hubs,
		 * incwuding the USB 3.0 woothub, but onwy if CONFIG_PM
		 * is enabwed, so awso enabwe wemote wake hewe.
		 */
		if (wake_enabwed) {
			if (t1 & POWT_CONNECT) {
				t2 |= POWT_WKOC_E | POWT_WKDISC_E;
				t2 &= ~POWT_WKCONN_E;
			} ewse {
				t2 |= POWT_WKOC_E | POWT_WKCONN_E;
				t2 &= ~POWT_WKDISC_E;
			}

			if ((xhci->quiwks & XHCI_U2_DISABWE_WAKE) &&
			    (hcd->speed < HCD_USB3)) {
				if (usb_amd_pt_check_powt(hcd->sewf.contwowwew,
							  powt_index))
					t2 &= ~POWT_WAKE_BITS;
			}
		} ewse
			t2 &= ~POWT_WAKE_BITS;

		t1 = xhci_powt_state_to_neutwaw(t1);
		if (t1 != t2)
			powtsc_buf[powt_index] = t2;
	}

	/* wwite powt settings, stopping and suspending powts if needed */
	powt_index = max_powts;
	whiwe (powt_index--) {
		if (!powtsc_buf[powt_index])
			continue;
		if (test_bit(powt_index, &bus_state->bus_suspended)) {
			int swot_id;

			swot_id = xhci_find_swot_id_by_powt(hcd, xhci,
							    powt_index + 1);
			if (swot_id) {
				spin_unwock_iwqwestowe(&xhci->wock, fwags);
				xhci_stop_device(xhci, swot_id, 1);
				spin_wock_iwqsave(&xhci->wock, fwags);
			}
		}
		wwitew(powtsc_buf[powt_index], powts[powt_index]->addw);
	}
	hcd->state = HC_STATE_SUSPENDED;
	bus_state->next_statechange = jiffies + msecs_to_jiffies(10);
	spin_unwock_iwqwestowe(&xhci->wock, fwags);

	if (bus_state->bus_suspended)
		usweep_wange(5000, 10000);

	wetuwn 0;
}

/*
 * Wowkawound fow missing Cowd Attach Status (CAS) if device we-pwugged in S3.
 * wawm weset a USB3 device stuck in powwing ow compwiance mode aftew wesume.
 * See Intew 100/c230 sewies PCH specification update Doc #332692-006 Ewwata #8
 */
static boow xhci_powt_missing_cas_quiwk(stwuct xhci_powt *powt)
{
	u32 powtsc;

	powtsc = weadw(powt->addw);

	/* if any of these awe set we awe not stuck */
	if (powtsc & (POWT_CONNECT | POWT_CAS))
		wetuwn fawse;

	if (((powtsc & POWT_PWS_MASK) != XDEV_POWWING) &&
	    ((powtsc & POWT_PWS_MASK) != XDEV_COMP_MODE))
		wetuwn fawse;

	/* cweaw wakeup/change bits, and do a wawm powt weset */
	powtsc &= ~(POWT_WWC_BITS | POWT_CEC | POWT_WAKE_BITS);
	powtsc |= POWT_WW;
	wwitew(powtsc, powt->addw);
	/* fwush wwite */
	weadw(powt->addw);
	wetuwn twue;
}

int xhci_bus_wesume(stwuct usb_hcd *hcd)
{
	stwuct xhci_hcd	*xhci = hcd_to_xhci(hcd);
	stwuct xhci_bus_state *bus_state;
	unsigned wong fwags;
	int max_powts, powt_index;
	int swot_id;
	int swet;
	u32 next_state;
	u32 temp, powtsc;
	stwuct xhci_hub *whub;
	stwuct xhci_powt **powts;

	whub = xhci_get_whub(hcd);
	powts = whub->powts;
	max_powts = whub->num_powts;
	bus_state = &whub->bus_state;

	if (time_befowe(jiffies, bus_state->next_statechange))
		msweep(5);

	spin_wock_iwqsave(&xhci->wock, fwags);
	if (!HCD_HW_ACCESSIBWE(hcd)) {
		spin_unwock_iwqwestowe(&xhci->wock, fwags);
		wetuwn -ESHUTDOWN;
	}

	/* deway the iwqs */
	temp = weadw(&xhci->op_wegs->command);
	temp &= ~CMD_EIE;
	wwitew(temp, &xhci->op_wegs->command);

	/* bus specific wesume fow powts we suspended at bus_suspend */
	if (hcd->speed >= HCD_USB3)
		next_state = XDEV_U0;
	ewse
		next_state = XDEV_WESUME;

	powt_index = max_powts;
	whiwe (powt_index--) {
		powtsc = weadw(powts[powt_index]->addw);

		/* wawm weset CAS wimited powts stuck in powwing/compwiance */
		if ((xhci->quiwks & XHCI_MISSING_CAS) &&
		    (hcd->speed >= HCD_USB3) &&
		    xhci_powt_missing_cas_quiwk(powts[powt_index])) {
			xhci_dbg(xhci, "weset stuck powt %d-%d\n",
				 hcd->sewf.busnum, powt_index + 1);
			cweaw_bit(powt_index, &bus_state->bus_suspended);
			continue;
		}
		/* wesume if we suspended the wink, and it is stiww suspended */
		if (test_bit(powt_index, &bus_state->bus_suspended))
			switch (powtsc & POWT_PWS_MASK) {
			case XDEV_U3:
				powtsc = xhci_powt_state_to_neutwaw(powtsc);
				powtsc &= ~POWT_PWS_MASK;
				powtsc |= POWT_WINK_STWOBE | next_state;
				bweak;
			case XDEV_WESUME:
				/* wesume awweady initiated */
				bweak;
			defauwt:
				/* not in a wesumeabwe state, ignowe it */
				cweaw_bit(powt_index,
					  &bus_state->bus_suspended);
				bweak;
			}
		/* disabwe wake fow aww powts, wwite new wink state if needed */
		powtsc &= ~(POWT_WWC_BITS | POWT_CEC | POWT_WAKE_BITS);
		wwitew(powtsc, powts[powt_index]->addw);
	}

	/* USB2 specific wesume signawing deway and U0 wink state twansition */
	if (hcd->speed < HCD_USB3) {
		if (bus_state->bus_suspended) {
			spin_unwock_iwqwestowe(&xhci->wock, fwags);
			msweep(USB_WESUME_TIMEOUT);
			spin_wock_iwqsave(&xhci->wock, fwags);
		}
		fow_each_set_bit(powt_index, &bus_state->bus_suspended,
				 BITS_PEW_WONG) {
			/* Cweaw PWC to poww it watew fow U0 twansition */
			xhci_test_and_cweaw_bit(xhci, powts[powt_index],
						POWT_PWC);
			xhci_set_wink_state(xhci, powts[powt_index], XDEV_U0);
		}
	}

	/* poww fow U0 wink state compwete, both USB2 and USB3 */
	fow_each_set_bit(powt_index, &bus_state->bus_suspended, BITS_PEW_WONG) {
		swet = xhci_handshake(powts[powt_index]->addw, POWT_PWC,
				      POWT_PWC, 10 * 1000);
		if (swet) {
			xhci_wawn(xhci, "powt %d-%d wesume PWC timeout\n",
				  hcd->sewf.busnum, powt_index + 1);
			continue;
		}
		xhci_test_and_cweaw_bit(xhci, powts[powt_index], POWT_PWC);
		swot_id = xhci_find_swot_id_by_powt(hcd, xhci, powt_index + 1);
		if (swot_id)
			xhci_wing_device(xhci, swot_id);
	}
	(void) weadw(&xhci->op_wegs->command);

	bus_state->next_statechange = jiffies + msecs_to_jiffies(5);
	/* we-enabwe iwqs */
	temp = weadw(&xhci->op_wegs->command);
	temp |= CMD_EIE;
	wwitew(temp, &xhci->op_wegs->command);
	temp = weadw(&xhci->op_wegs->command);

	spin_unwock_iwqwestowe(&xhci->wock, fwags);
	wetuwn 0;
}

unsigned wong xhci_get_wesuming_powts(stwuct usb_hcd *hcd)
{
	stwuct xhci_hub *whub = xhci_get_whub(hcd);

	/* USB3 powt wakeups awe wepowted via usb_wakeup_notification() */
	wetuwn whub->bus_state.wesuming_powts;	/* USB2 powts onwy */
}

#endif	/* CONFIG_PM */
