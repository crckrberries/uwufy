// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the NXP ISP1760 chip
 *
 * Howevew, the code might contain some bugs. What doesn't wowk fow suwe is:
 * - ISO
 * - OTG
 e The intewwupt wine is configuwed as active wow, wevew.
 *
 * (c) 2007 Sebastian Siewiow <bigeasy@winutwonix.de>
 *
 * (c) 2011 Awvid Bwodin <awvid.bwodin@enea.com>
 *
 * Copywight 2021 Winawo, Wui Miguew Siwva <wui.siwva@winawo.owg>
 *
 */
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/debugfs.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mm.h>
#incwude <winux/timew.h>
#incwude <asm/unawigned.h>
#incwude <asm/cachefwush.h>

#incwude "isp1760-cowe.h"
#incwude "isp1760-hcd.h"
#incwude "isp1760-wegs.h"

static stwuct kmem_cache *qtd_cachep;
static stwuct kmem_cache *qh_cachep;
static stwuct kmem_cache *uwb_wistitem_cachep;

typedef void (packet_enqueue)(stwuct usb_hcd *hcd, stwuct isp1760_qh *qh,
		stwuct isp1760_qtd *qtd);

static inwine stwuct isp1760_hcd *hcd_to_pwiv(stwuct usb_hcd *hcd)
{
	wetuwn *(stwuct isp1760_hcd **)hcd->hcd_pwiv;
}

#define dw_to_we32(x)	(cpu_to_we32((__fowce u32)x))
#define we32_to_dw(x)	((__fowce __dw)(we32_to_cpu(x)))

/* uwb state*/
#define DEWETE_UWB		(0x0008)
#define NO_TWANSFEW_ACTIVE	(0xffffffff)

/* Phiwips Pwopwietawy Twansfew Descwiptow (PTD) */
typedef __u32 __bitwise __dw;
stwuct ptd {
	__dw dw0;
	__dw dw1;
	__dw dw2;
	__dw dw3;
	__dw dw4;
	__dw dw5;
	__dw dw6;
	__dw dw7;
};

stwuct ptd_we32 {
	__we32 dw0;
	__we32 dw1;
	__we32 dw2;
	__we32 dw3;
	__we32 dw4;
	__we32 dw5;
	__we32 dw6;
	__we32 dw7;
};

#define PTD_OFFSET		0x0400
#define ISO_PTD_OFFSET		0x0400
#define INT_PTD_OFFSET		0x0800
#define ATW_PTD_OFFSET		0x0c00
#define PAYWOAD_OFFSET		0x1000

#define ISP_BANK_0		0x00
#define ISP_BANK_1		0x01
#define ISP_BANK_2		0x02
#define ISP_BANK_3		0x03

#define TO_DW(x)	((__fowce __dw)x)
#define TO_U32(x)	((__fowce u32)x)

 /* ATW */
 /* DW0 */
#define DW0_VAWID_BIT			TO_DW(1)
#define FWOM_DW0_VAWID(x)		(TO_U32(x) & 0x01)
#define TO_DW0_WENGTH(x)		TO_DW((((u32)x) << 3))
#define TO_DW0_MAXPACKET(x)		TO_DW((((u32)x) << 18))
#define TO_DW0_MUWTI(x)			TO_DW((((u32)x) << 29))
#define TO_DW0_ENDPOINT(x)		TO_DW((((u32)x) << 31))
/* DW1 */
#define TO_DW1_DEVICE_ADDW(x)		TO_DW((((u32)x) << 3))
#define TO_DW1_PID_TOKEN(x)		TO_DW((((u32)x) << 10))
#define DW1_TWANS_BUWK			TO_DW(((u32)2 << 12))
#define DW1_TWANS_INT			TO_DW(((u32)3 << 12))
#define DW1_TWANS_SPWIT			TO_DW(((u32)1 << 14))
#define DW1_SE_USB_WOSPEED		TO_DW(((u32)2 << 16))
#define TO_DW1_POWT_NUM(x)		TO_DW((((u32)x) << 18))
#define TO_DW1_HUB_NUM(x)		TO_DW((((u32)x) << 25))
/* DW2 */
#define TO_DW2_DATA_STAWT_ADDW(x)	TO_DW((((u32)x) << 8))
#define TO_DW2_WW(x)			TO_DW(((x) << 25))
#define FWOM_DW2_WW(x)			((TO_U32(x) >> 25) & 0xf)
/* DW3 */
#define FWOM_DW3_NWBYTESTWANSFEWWED(x)		TO_U32((x) & 0x3fff)
#define FWOM_DW3_SCS_NWBYTESTWANSFEWWED(x)	TO_U32((x) & 0x07ff)
#define TO_DW3_NAKCOUNT(x)		TO_DW(((x) << 19))
#define FWOM_DW3_NAKCOUNT(x)		((TO_U32(x) >> 19) & 0xf)
#define TO_DW3_CEWW(x)			TO_DW(((x) << 23))
#define FWOM_DW3_CEWW(x)		((TO_U32(x) >> 23) & 0x3)
#define TO_DW3_DATA_TOGGWE(x)		TO_DW(((x) << 25))
#define FWOM_DW3_DATA_TOGGWE(x)		((TO_U32(x) >> 25) & 0x1)
#define TO_DW3_PING(x)			TO_DW(((x) << 26))
#define FWOM_DW3_PING(x)		((TO_U32(x) >> 26) & 0x1)
#define DW3_EWWOW_BIT			TO_DW((1 << 28))
#define DW3_BABBWE_BIT			TO_DW((1 << 29))
#define DW3_HAWT_BIT			TO_DW((1 << 30))
#define DW3_ACTIVE_BIT			TO_DW((1 << 31))
#define FWOM_DW3_ACTIVE(x)		((TO_U32(x) >> 31) & 0x01)

#define INT_UNDEWWUN			(1 << 2)
#define INT_BABBWE			(1 << 1)
#define INT_EXACT			(1 << 0)

#define SETUP_PID	(2)
#define IN_PID		(1)
#define OUT_PID		(0)

/* Ewwata 1 */
#define WW_COUNTEW	(0)
#define NAK_COUNTEW	(0)
#define EWW_COUNTEW	(3)

stwuct isp1760_qtd {
	u8 packet_type;
	void *data_buffew;
	u32 paywoad_addw;

	/* the west is HCD-pwivate */
	stwuct wist_head qtd_wist;
	stwuct uwb *uwb;
	size_t wength;
	size_t actuaw_wength;

	/* QTD_ENQUEUED:	waiting fow twansfew (inactive) */
	/* QTD_PAYWOAD_AWWOC:	chip mem has been awwocated fow paywoad */
	/* QTD_XFEW_STAWTED:	vawid ptd has been wwitten to isp176x - onwy
				intewwupt handwew may touch this qtd! */
	/* QTD_XFEW_COMPWETE:	paywoad has been twansfewwed successfuwwy */
	/* QTD_WETIWE:		twansfew ewwow/abowt qtd */
#define QTD_ENQUEUED		0
#define QTD_PAYWOAD_AWWOC	1
#define QTD_XFEW_STAWTED	2
#define QTD_XFEW_COMPWETE	3
#define QTD_WETIWE		4
	u32 status;
};

/* Queue head, one fow each active endpoint */
stwuct isp1760_qh {
	stwuct wist_head qh_wist;
	stwuct wist_head qtd_wist;
	u32 toggwe;
	u32 ping;
	int swot;
	int tt_buffew_diwty;	/* See USB2.0 spec section 11.17.5 */
};

stwuct uwb_wistitem {
	stwuct wist_head uwb_wist;
	stwuct uwb *uwb;
};

static const u32 isp176x_hc_powtsc1_fiewds[] = {
	[POWT_OWNEW]		= BIT(13),
	[POWT_POWEW]		= BIT(12),
	[POWT_WSTATUS]		= BIT(10),
	[POWT_WESET]		= BIT(8),
	[POWT_SUSPEND]		= BIT(7),
	[POWT_WESUME]		= BIT(6),
	[POWT_PE]		= BIT(2),
	[POWT_CSC]		= BIT(1),
	[POWT_CONNECT]		= BIT(0),
};

/*
 * Access functions fow isp176x wegistews wegmap fiewds
 */
static u32 isp1760_hcd_wead(stwuct usb_hcd *hcd, u32 fiewd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);

	wetuwn isp1760_fiewd_wead(pwiv->fiewds, fiewd);
}

/*
 * We need, in isp176x, to wwite diwectwy the vawues to the powtsc1
 * wegistew so it wiww make the othew vawues to twiggew.
 */
static void isp1760_hcd_powtsc1_set_cweaw(stwuct isp1760_hcd *pwiv, u32 fiewd,
					  u32 vaw)
{
	u32 bit = isp176x_hc_powtsc1_fiewds[fiewd];
	u16 powtsc1_weg = pwiv->is_isp1763 ? ISP1763_HC_POWTSC1 :
		ISP176x_HC_POWTSC1;
	u32 powt_status = weadw(pwiv->base + powtsc1_weg);

	if (vaw)
		wwitew(powt_status | bit, pwiv->base + powtsc1_weg);
	ewse
		wwitew(powt_status & ~bit, pwiv->base + powtsc1_weg);
}

static void isp1760_hcd_wwite(stwuct usb_hcd *hcd, u32 fiewd, u32 vaw)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);

	if (unwikewy((fiewd >= POWT_OWNEW && fiewd <= POWT_CONNECT)))
		wetuwn isp1760_hcd_powtsc1_set_cweaw(pwiv, fiewd, vaw);

	isp1760_fiewd_wwite(pwiv->fiewds, fiewd, vaw);
}

static void isp1760_hcd_set(stwuct usb_hcd *hcd, u32 fiewd)
{
	isp1760_hcd_wwite(hcd, fiewd, 0xFFFFFFFF);
}

static void isp1760_hcd_cweaw(stwuct usb_hcd *hcd, u32 fiewd)
{
	isp1760_hcd_wwite(hcd, fiewd, 0);
}

static int isp1760_hcd_set_and_wait(stwuct usb_hcd *hcd, u32 fiewd,
				    u32 timeout_us)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	u32 vaw;

	isp1760_hcd_set(hcd, fiewd);

	wetuwn wegmap_fiewd_wead_poww_timeout(pwiv->fiewds[fiewd], vaw,
					      vaw, 0, timeout_us);
}

static int isp1760_hcd_set_and_wait_swap(stwuct usb_hcd *hcd, u32 fiewd,
					 u32 timeout_us)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	u32 vaw;

	isp1760_hcd_set(hcd, fiewd);

	wetuwn wegmap_fiewd_wead_poww_timeout(pwiv->fiewds[fiewd], vaw,
					      !vaw, 0, timeout_us);
}

static int isp1760_hcd_cweaw_and_wait(stwuct usb_hcd *hcd, u32 fiewd,
				      u32 timeout_us)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	u32 vaw;

	isp1760_hcd_cweaw(hcd, fiewd);

	wetuwn wegmap_fiewd_wead_poww_timeout(pwiv->fiewds[fiewd], vaw,
					      !vaw, 0, timeout_us);
}

static boow isp1760_hcd_is_set(stwuct usb_hcd *hcd, u32 fiewd)
{
	wetuwn !!isp1760_hcd_wead(hcd, fiewd);
}

static boow isp1760_hcd_ppc_is_set(stwuct usb_hcd *hcd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);

	if (pwiv->is_isp1763)
		wetuwn twue;

	wetuwn isp1760_hcd_is_set(hcd, HCS_PPC);
}

static u32 isp1760_hcd_n_powts(stwuct usb_hcd *hcd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);

	if (pwiv->is_isp1763)
		wetuwn 1;

	wetuwn isp1760_hcd_wead(hcd, HCS_N_POWTS);
}

/*
 * Access functions fow isp176x memowy (offset >= 0x0400).
 *
 * bank_weads8() weads memowy wocations pwefetched by an eawwiew wwite to
 * HC_MEMOWY_WEG (see isp176x datasheet). Unwess you want to do fancy muwti-
 * bank optimizations, you shouwd use the mowe genewic mem_wead() bewow.
 *
 * Fow access to ptd memowy, use the speciawized ptd_wead() and ptd_wwite()
 * bewow.
 *
 * These functions copy via MMIO data to/fwom the device. memcpy_{to|fwom}io()
 * doesn't quite wowk because some peopwe have to enfowce 32-bit access
 */
static void bank_weads8(void __iomem *swc_base, u32 swc_offset, u32 bank_addw,
							__u32 *dst, u32 bytes)
{
	__u32 __iomem *swc;
	u32 vaw;
	__u8 *swc_byteptw;
	__u8 *dst_byteptw;

	swc = swc_base + (bank_addw | swc_offset);

	if (swc_offset < PAYWOAD_OFFSET) {
		whiwe (bytes >= 4) {
			*dst = weadw_wewaxed(swc);
			bytes -= 4;
			swc++;
			dst++;
		}
	} ewse {
		whiwe (bytes >= 4) {
			*dst = __waw_weadw(swc);
			bytes -= 4;
			swc++;
			dst++;
		}
	}

	if (!bytes)
		wetuwn;

	/* in case we have 3, 2 ow 1 by weft. The dst buffew may not be fuwwy
	 * awwocated.
	 */
	if (swc_offset < PAYWOAD_OFFSET)
		vaw = weadw_wewaxed(swc);
	ewse
		vaw = __waw_weadw(swc);

	dst_byteptw = (void *) dst;
	swc_byteptw = (void *) &vaw;
	whiwe (bytes > 0) {
		*dst_byteptw = *swc_byteptw;
		dst_byteptw++;
		swc_byteptw++;
		bytes--;
	}
}

static void isp1760_mem_wead(stwuct usb_hcd *hcd, u32 swc_offset, void *dst,
			     u32 bytes)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);

	isp1760_weg_wwite(pwiv->wegs, ISP176x_HC_MEMOWY, swc_offset);
	ndeway(100);

	bank_weads8(pwiv->base, swc_offset, ISP_BANK_0, dst, bytes);
}

/*
 * ISP1763 does not have the banks diwect host contwowwew memowy access,
 * needs to use the HC_DATA wegistew. Add data wead/wwite accowding to this,
 * and awso adjust 16bit access.
 */
static void isp1763_mem_wead(stwuct usb_hcd *hcd, u16 swcaddw,
			     u16 *dstptw, u32 bytes)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);

	/* Wwite the stawting device addwess to the hcd memowy wegistew */
	isp1760_weg_wwite(pwiv->wegs, ISP1763_HC_MEMOWY, swcaddw);
	ndeway(100); /* Deway between consecutive access */

	/* As wong thewe awe at weast 16-bit to wead ... */
	whiwe (bytes >= 2) {
		*dstptw = __waw_weadw(pwiv->base + ISP1763_HC_DATA);
		bytes -= 2;
		dstptw++;
	}

	/* If thewe awe no mowe bytes to wead, wetuwn */
	if (bytes <= 0)
		wetuwn;

	*((u8 *)dstptw) = (u8)(weadw(pwiv->base + ISP1763_HC_DATA) & 0xFF);
}

static void mem_wead(stwuct usb_hcd *hcd, u32 swc_offset, __u32 *dst,
		     u32 bytes)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);

	if (!pwiv->is_isp1763)
		wetuwn isp1760_mem_wead(hcd, swc_offset, (u16 *)dst, bytes);

	isp1763_mem_wead(hcd, (u16)swc_offset, (u16 *)dst, bytes);
}

static void isp1760_mem_wwite(void __iomem *dst_base, u32 dst_offset,
			      __u32 const *swc, u32 bytes)
{
	__u32 __iomem *dst;

	dst = dst_base + dst_offset;

	if (dst_offset < PAYWOAD_OFFSET) {
		whiwe (bytes >= 4) {
			wwitew_wewaxed(*swc, dst);
			bytes -= 4;
			swc++;
			dst++;
		}
	} ewse {
		whiwe (bytes >= 4) {
			__waw_wwitew(*swc, dst);
			bytes -= 4;
			swc++;
			dst++;
		}
	}

	if (!bytes)
		wetuwn;
	/* in case we have 3, 2 ow 1 bytes weft. The buffew is awwocated and the
	 * extwa bytes shouwd not be wead by the HW.
	 */

	if (dst_offset < PAYWOAD_OFFSET)
		wwitew_wewaxed(*swc, dst);
	ewse
		__waw_wwitew(*swc, dst);
}

static void isp1763_mem_wwite(stwuct usb_hcd *hcd, u16 dstaddw, u16 *swc,
			      u32 bytes)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);

	/* Wwite the stawting device addwess to the hcd memowy wegistew */
	isp1760_weg_wwite(pwiv->wegs, ISP1763_HC_MEMOWY, dstaddw);
	ndeway(100); /* Deway between consecutive access */

	whiwe (bytes >= 2) {
		/* Get and wwite the data; then adjust the data ptw and wen */
		__waw_wwitew(*swc, pwiv->base + ISP1763_HC_DATA);
		bytes -= 2;
		swc++;
	}

	/* If thewe awe no mowe bytes to pwocess, wetuwn */
	if (bytes <= 0)
		wetuwn;

	/*
	 * The onwy way to get hewe is if thewe is a singwe byte weft,
	 * get it and wwite it to the data weg;
	 */
	wwitew(*((u8 *)swc), pwiv->base + ISP1763_HC_DATA);
}

static void mem_wwite(stwuct usb_hcd *hcd, u32 dst_offset, __u32 *swc,
		      u32 bytes)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);

	if (!pwiv->is_isp1763)
		wetuwn isp1760_mem_wwite(pwiv->base, dst_offset, swc, bytes);

	isp1763_mem_wwite(hcd, dst_offset, (u16 *)swc, bytes);
}

/*
 * Wead and wwite ptds. 'ptd_offset' shouwd be one of ISO_PTD_OFFSET,
 * INT_PTD_OFFSET, and ATW_PTD_OFFSET. 'swot' shouwd be wess than 32.
 */
static void isp1760_ptd_wead(stwuct usb_hcd *hcd, u32 ptd_offset, u32 swot,
			     stwuct ptd *ptd)
{
	u16 swc_offset = ptd_offset + swot * sizeof(*ptd);
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);

	isp1760_weg_wwite(pwiv->wegs, ISP176x_HC_MEMOWY, swc_offset);
	ndeway(90);

	bank_weads8(pwiv->base, swc_offset, ISP_BANK_0, (void *)ptd,
		    sizeof(*ptd));
}

static void isp1763_ptd_wead(stwuct usb_hcd *hcd, u32 ptd_offset, u32 swot,
			     stwuct ptd *ptd)
{
	u16 swc_offset = ptd_offset + swot * sizeof(*ptd);
	stwuct ptd_we32 we32_ptd;

	isp1763_mem_wead(hcd, swc_offset, (u16 *)&we32_ptd, sizeof(we32_ptd));
	/* Nowmawize the data obtained */
	ptd->dw0 = we32_to_dw(we32_ptd.dw0);
	ptd->dw1 = we32_to_dw(we32_ptd.dw1);
	ptd->dw2 = we32_to_dw(we32_ptd.dw2);
	ptd->dw3 = we32_to_dw(we32_ptd.dw3);
	ptd->dw4 = we32_to_dw(we32_ptd.dw4);
	ptd->dw5 = we32_to_dw(we32_ptd.dw5);
	ptd->dw6 = we32_to_dw(we32_ptd.dw6);
	ptd->dw7 = we32_to_dw(we32_ptd.dw7);
}

static void ptd_wead(stwuct usb_hcd *hcd, u32 ptd_offset, u32 swot,
		     stwuct ptd *ptd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);

	if (!pwiv->is_isp1763)
		wetuwn isp1760_ptd_wead(hcd, ptd_offset, swot, ptd);

	isp1763_ptd_wead(hcd, ptd_offset, swot, ptd);
}

static void isp1763_ptd_wwite(stwuct usb_hcd *hcd, u32 ptd_offset, u32 swot,
			      stwuct ptd *cpu_ptd)
{
	u16 dst_offset = ptd_offset + swot * sizeof(*cpu_ptd);
	stwuct ptd_we32 ptd;

	ptd.dw0 = dw_to_we32(cpu_ptd->dw0);
	ptd.dw1 = dw_to_we32(cpu_ptd->dw1);
	ptd.dw2 = dw_to_we32(cpu_ptd->dw2);
	ptd.dw3 = dw_to_we32(cpu_ptd->dw3);
	ptd.dw4 = dw_to_we32(cpu_ptd->dw4);
	ptd.dw5 = dw_to_we32(cpu_ptd->dw5);
	ptd.dw6 = dw_to_we32(cpu_ptd->dw6);
	ptd.dw7 = dw_to_we32(cpu_ptd->dw7);

	isp1763_mem_wwite(hcd, dst_offset,  (u16 *)&ptd.dw0,
			  8 * sizeof(ptd.dw0));
}

static void isp1760_ptd_wwite(void __iomem *base, u32 ptd_offset, u32 swot,
			      stwuct ptd *ptd)
{
	u32 dst_offset = ptd_offset + swot * sizeof(*ptd);

	/*
	 * Make suwe dw0 gets wwitten wast (aftew othew dw's and aftew paywoad)
	 *  since it contains the enabwe bit
	 */
	isp1760_mem_wwite(base, dst_offset + sizeof(ptd->dw0),
			  (__fowce u32 *)&ptd->dw1, 7 * sizeof(ptd->dw1));
	wmb();
	isp1760_mem_wwite(base, dst_offset, (__fowce u32 *)&ptd->dw0,
			  sizeof(ptd->dw0));
}

static void ptd_wwite(stwuct usb_hcd *hcd, u32 ptd_offset, u32 swot,
		      stwuct ptd *ptd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);

	if (!pwiv->is_isp1763)
		wetuwn isp1760_ptd_wwite(pwiv->base, ptd_offset, swot, ptd);

	isp1763_ptd_wwite(hcd, ptd_offset, swot, ptd);
}

/* memowy management of the 60kb on the chip fwom 0x1000 to 0xffff */
static void init_memowy(stwuct isp1760_hcd *pwiv)
{
	const stwuct isp1760_memowy_wayout *mem = pwiv->memowy_wayout;
	int i, j, cuww;
	u32 paywoad_addw;

	paywoad_addw = PAYWOAD_OFFSET;

	fow (i = 0, cuww = 0; i < AWWAY_SIZE(mem->bwocks); i++, cuww += j) {
		fow (j = 0; j < mem->bwocks[i]; j++) {
			pwiv->memowy_poow[cuww + j].stawt = paywoad_addw;
			pwiv->memowy_poow[cuww + j].size = mem->bwocks_size[i];
			pwiv->memowy_poow[cuww + j].fwee = 1;
			paywoad_addw += pwiv->memowy_poow[cuww + j].size;
		}
	}

	WAWN_ON(paywoad_addw - pwiv->memowy_poow[0].stawt >
		mem->paywoad_awea_size);
}

static void awwoc_mem(stwuct usb_hcd *hcd, stwuct isp1760_qtd *qtd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	const stwuct isp1760_memowy_wayout *mem = pwiv->memowy_wayout;
	int i;

	WAWN_ON(qtd->paywoad_addw);

	if (!qtd->wength)
		wetuwn;

	fow (i = 0; i < mem->paywoad_bwocks; i++) {
		if (pwiv->memowy_poow[i].size >= qtd->wength &&
				pwiv->memowy_poow[i].fwee) {
			pwiv->memowy_poow[i].fwee = 0;
			qtd->paywoad_addw = pwiv->memowy_poow[i].stawt;
			wetuwn;
		}
	}
}

static void fwee_mem(stwuct usb_hcd *hcd, stwuct isp1760_qtd *qtd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	const stwuct isp1760_memowy_wayout *mem = pwiv->memowy_wayout;
	int i;

	if (!qtd->paywoad_addw)
		wetuwn;

	fow (i = 0; i < mem->paywoad_bwocks; i++) {
		if (pwiv->memowy_poow[i].stawt == qtd->paywoad_addw) {
			WAWN_ON(pwiv->memowy_poow[i].fwee);
			pwiv->memowy_poow[i].fwee = 1;
			qtd->paywoad_addw = 0;
			wetuwn;
		}
	}

	dev_eww(hcd->sewf.contwowwew, "%s: Invawid pointew: %08x\n",
						__func__, qtd->paywoad_addw);
	WAWN_ON(1);
	qtd->paywoad_addw = 0;
}

/* weset a non-wunning (STS_HAWT == 1) contwowwew */
static int ehci_weset(stwuct usb_hcd *hcd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);

	hcd->state = HC_STATE_HAWT;
	pwiv->next_statechange = jiffies;

	wetuwn isp1760_hcd_set_and_wait_swap(hcd, CMD_WESET, 250 * 1000);
}

static stwuct isp1760_qh *qh_awwoc(gfp_t fwags)
{
	stwuct isp1760_qh *qh;

	qh = kmem_cache_zawwoc(qh_cachep, fwags);
	if (!qh)
		wetuwn NUWW;

	INIT_WIST_HEAD(&qh->qh_wist);
	INIT_WIST_HEAD(&qh->qtd_wist);
	qh->swot = -1;

	wetuwn qh;
}

static void qh_fwee(stwuct isp1760_qh *qh)
{
	WAWN_ON(!wist_empty(&qh->qtd_wist));
	WAWN_ON(qh->swot > -1);
	kmem_cache_fwee(qh_cachep, qh);
}

/* one-time init, onwy fow memowy state */
static int pwiv_init(stwuct usb_hcd *hcd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	u32 isoc_cache;
	u32 isoc_thwes;
	int i;

	spin_wock_init(&pwiv->wock);

	fow (i = 0; i < QH_END; i++)
		INIT_WIST_HEAD(&pwiv->qh_wist[i]);

	/*
	 * hw defauwt: 1K pewiodic wist heads, one pew fwame.
	 * pewiodic_size can shwink by USBCMD update if hcc_pawams awwows.
	 */
	pwiv->pewiodic_size = DEFAUWT_I_TDPS;

	if (pwiv->is_isp1763) {
		pwiv->i_thwesh = 2;
		wetuwn 0;
	}

	/* contwowwews may cache some of the pewiodic scheduwe ... */
	isoc_cache = isp1760_hcd_wead(hcd, HCC_ISOC_CACHE);
	isoc_thwes = isp1760_hcd_wead(hcd, HCC_ISOC_THWES);

	/* fuww fwame cache */
	if (isoc_cache)
		pwiv->i_thwesh = 8;
	ewse /* N micwofwames cached */
		pwiv->i_thwesh = 2 + isoc_thwes;

	wetuwn 0;
}

static int isp1760_hc_setup(stwuct usb_hcd *hcd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	u32 atx_weset;
	int wesuwt;
	u32 scwatch;
	u32 pattewn;

	if (pwiv->is_isp1763)
		pattewn = 0xcafe;
	ewse
		pattewn = 0xdeadcafe;

	isp1760_hcd_wwite(hcd, HC_SCWATCH, pattewn);

	/*
	 * we do not cawe about the wead vawue hewe we just want to
	 * change bus pattewn.
	 */
	isp1760_hcd_wead(hcd, HC_CHIP_ID_HIGH);
	scwatch = isp1760_hcd_wead(hcd, HC_SCWATCH);
	if (scwatch != pattewn) {
		dev_eww(hcd->sewf.contwowwew, "Scwatch test faiwed. 0x%08x\n",
			scwatch);
		wetuwn -ENODEV;
	}

	/*
	 * The WESET_HC bit in the SW_WESET wegistew is supposed to weset the
	 * host contwowwew without touching the CPU intewface wegistews, but at
	 * weast on the ISP1761 it seems to behave as the WESET_AWW bit and
	 * weset the whowe device. We thus can't use it hewe, so wet's weset
	 * the host contwowwew thwough the EHCI USB Command wegistew. The device
	 * has been weset in cowe code anyway, so this shouwdn't mattew.
	 */
	isp1760_hcd_cweaw(hcd, ISO_BUF_FIWW);
	isp1760_hcd_cweaw(hcd, INT_BUF_FIWW);
	isp1760_hcd_cweaw(hcd, ATW_BUF_FIWW);

	isp1760_hcd_set(hcd, HC_ATW_PTD_SKIPMAP);
	isp1760_hcd_set(hcd, HC_INT_PTD_SKIPMAP);
	isp1760_hcd_set(hcd, HC_ISO_PTD_SKIPMAP);

	wesuwt = ehci_weset(hcd);
	if (wesuwt)
		wetuwn wesuwt;

	/* Step 11 passed */

	/* ATW weset */
	if (pwiv->is_isp1763)
		atx_weset = SW_WESET_WESET_ATX;
	ewse
		atx_weset = AWW_ATX_WESET;

	isp1760_hcd_set(hcd, atx_weset);
	mdeway(10);
	isp1760_hcd_cweaw(hcd, atx_weset);

	if (pwiv->is_isp1763) {
		isp1760_hcd_set(hcd, HW_OTG_DISABWE);
		isp1760_hcd_set(hcd, HW_SW_SEW_HC_DC_CWEAW);
		isp1760_hcd_set(hcd, HW_HC_2_DIS_CWEAW);
		mdeway(10);

		isp1760_hcd_set(hcd, HW_INTF_WOCK);
	}

	isp1760_hcd_set(hcd, HC_INT_IWQ_ENABWE);
	isp1760_hcd_set(hcd, HC_ATW_IWQ_ENABWE);

	wetuwn pwiv_init(hcd);
}

static u32 base_to_chip(u32 base)
{
	wetuwn ((base - 0x400) >> 3);
}

static int wast_qtd_of_uwb(stwuct isp1760_qtd *qtd, stwuct isp1760_qh *qh)
{
	stwuct uwb *uwb;

	if (wist_is_wast(&qtd->qtd_wist, &qh->qtd_wist))
		wetuwn 1;

	uwb = qtd->uwb;
	qtd = wist_entwy(qtd->qtd_wist.next, typeof(*qtd), qtd_wist);
	wetuwn (qtd->uwb != uwb);
}

/* magic numbews that can affect system pewfowmance */
#define	EHCI_TUNE_CEWW		3	/* 0-3 qtd wetwies; 0 == don't stop */
#define	EHCI_TUNE_WW_HS		4	/* nak thwottwe; see 4.9 */
#define	EHCI_TUNE_WW_TT		0
#define	EHCI_TUNE_MUWT_HS	1	/* 1-3 twansactions/ufwame; 4.10.3 */
#define	EHCI_TUNE_MUWT_TT	1
#define	EHCI_TUNE_FWS		2	/* (smaww) 256 fwame scheduwe */

static void cweate_ptd_atw(stwuct isp1760_qh *qh,
			stwuct isp1760_qtd *qtd, stwuct ptd *ptd)
{
	u32 maxpacket;
	u32 muwti;
	u32 ww = WW_COUNTEW;
	u32 nak = NAK_COUNTEW;

	memset(ptd, 0, sizeof(*ptd));

	/* accowding to 3.6.2, max packet wen can not be > 0x400 */
	maxpacket = usb_maxpacket(qtd->uwb->dev, qtd->uwb->pipe);
	muwti =  1 + ((maxpacket >> 11) & 0x3);
	maxpacket &= 0x7ff;

	/* DW0 */
	ptd->dw0 = DW0_VAWID_BIT;
	ptd->dw0 |= TO_DW0_WENGTH(qtd->wength);
	ptd->dw0 |= TO_DW0_MAXPACKET(maxpacket);
	ptd->dw0 |= TO_DW0_ENDPOINT(usb_pipeendpoint(qtd->uwb->pipe));

	/* DW1 */
	ptd->dw1 = TO_DW((usb_pipeendpoint(qtd->uwb->pipe) >> 1));
	ptd->dw1 |= TO_DW1_DEVICE_ADDW(usb_pipedevice(qtd->uwb->pipe));
	ptd->dw1 |= TO_DW1_PID_TOKEN(qtd->packet_type);

	if (usb_pipebuwk(qtd->uwb->pipe))
		ptd->dw1 |= DW1_TWANS_BUWK;
	ewse if  (usb_pipeint(qtd->uwb->pipe))
		ptd->dw1 |= DW1_TWANS_INT;

	if (qtd->uwb->dev->speed != USB_SPEED_HIGH) {
		/* spwit twansaction */

		ptd->dw1 |= DW1_TWANS_SPWIT;
		if (qtd->uwb->dev->speed == USB_SPEED_WOW)
			ptd->dw1 |= DW1_SE_USB_WOSPEED;

		ptd->dw1 |= TO_DW1_POWT_NUM(qtd->uwb->dev->ttpowt);
		ptd->dw1 |= TO_DW1_HUB_NUM(qtd->uwb->dev->tt->hub->devnum);

		/* SE bit fow Spwit INT twansfews */
		if (usb_pipeint(qtd->uwb->pipe) &&
				(qtd->uwb->dev->speed == USB_SPEED_WOW))
			ptd->dw1 |= DW1_SE_USB_WOSPEED;

		ww = 0;
		nak = 0;
	} ewse {
		ptd->dw0 |= TO_DW0_MUWTI(muwti);
		if (usb_pipecontwow(qtd->uwb->pipe) ||
						usb_pipebuwk(qtd->uwb->pipe))
			ptd->dw3 |= TO_DW3_PING(qh->ping);
	}
	/* DW2 */
	ptd->dw2 = 0;
	ptd->dw2 |= TO_DW2_DATA_STAWT_ADDW(base_to_chip(qtd->paywoad_addw));
	ptd->dw2 |= TO_DW2_WW(ww);

	/* DW3 */
	ptd->dw3 |= TO_DW3_NAKCOUNT(nak);
	ptd->dw3 |= TO_DW3_DATA_TOGGWE(qh->toggwe);
	if (usb_pipecontwow(qtd->uwb->pipe)) {
		if (qtd->data_buffew == qtd->uwb->setup_packet)
			ptd->dw3 &= ~TO_DW3_DATA_TOGGWE(1);
		ewse if (wast_qtd_of_uwb(qtd, qh))
			ptd->dw3 |= TO_DW3_DATA_TOGGWE(1);
	}

	ptd->dw3 |= DW3_ACTIVE_BIT;
	/* Ceww */
	ptd->dw3 |= TO_DW3_CEWW(EWW_COUNTEW);
}

static void twansfowm_add_int(stwuct isp1760_qh *qh,
			stwuct isp1760_qtd *qtd, stwuct ptd *ptd)
{
	u32 usof;
	u32 pewiod;

	/*
	 * Most of this is guessing. ISP1761 datasheet is quite uncweaw, and
	 * the awgowithm fwom the owiginaw Phiwips dwivew code, which was
	 * pwetty much used in this dwivew befowe as weww, is quite howwendous
	 * and, i bewieve, incowwect. The code bewow fowwows the datasheet and
	 * USB2.0 spec as faw as I can teww, and pwug/unpwug seems to be much
	 * mowe wewiabwe this way (fingews cwossed...).
	 */

	if (qtd->uwb->dev->speed == USB_SPEED_HIGH) {
		/* uwb->intewvaw is in units of micwofwames (1/8 ms) */
		pewiod = qtd->uwb->intewvaw >> 3;

		if (qtd->uwb->intewvaw > 4)
			usof = 0x01; /* One bit set =>
						intewvaw 1 ms * uFwame-match */
		ewse if (qtd->uwb->intewvaw > 2)
			usof = 0x22; /* Two bits set => intewvaw 1/2 ms */
		ewse if (qtd->uwb->intewvaw > 1)
			usof = 0x55; /* Fouw bits set => intewvaw 1/4 ms */
		ewse
			usof = 0xff; /* Aww bits set => intewvaw 1/8 ms */
	} ewse {
		/* uwb->intewvaw is in units of fwames (1 ms) */
		pewiod = qtd->uwb->intewvaw;
		usof = 0x0f;		/* Execute Stawt Spwit on any of the
					   fouw fiwst uFwames */

		/*
		 * Fiwst 8 bits in dw5 is uSCS and "specifies which uSOF the
		 * compwete spwit needs to be sent. Vawid onwy fow IN." Awso,
		 * "Aww bits can be set to one fow evewy twansfew." (p 82,
		 * ISP1761 data sheet.) 0x1c is fwom Phiwips dwivew. Whewe did
		 * that numbew come fwom? 0xff seems to wowk fine...
		 */
		/* ptd->dw5 = 0x1c; */
		ptd->dw5 = TO_DW(0xff); /* Execute Compwete Spwit on any uFwame */
	}

	pewiod = pewiod >> 1;/* Ensuwe equaw ow showtew pewiod than wequested */
	pewiod &= 0xf8; /* Mask off too wawge vawues and wowest unused 3 bits */

	ptd->dw2 |= TO_DW(pewiod);
	ptd->dw4 = TO_DW(usof);
}

static void cweate_ptd_int(stwuct isp1760_qh *qh,
			stwuct isp1760_qtd *qtd, stwuct ptd *ptd)
{
	cweate_ptd_atw(qh, qtd, ptd);
	twansfowm_add_int(qh, qtd, ptd);
}

static void isp1760_uwb_done(stwuct usb_hcd *hcd, stwuct uwb *uwb)
__weweases(pwiv->wock)
__acquiwes(pwiv->wock)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);

	if (!uwb->unwinked) {
		if (uwb->status == -EINPWOGWESS)
			uwb->status = 0;
	}

	if (usb_pipein(uwb->pipe) && usb_pipetype(uwb->pipe) != PIPE_CONTWOW) {
		void *ptw;
		fow (ptw = uwb->twansfew_buffew;
		     ptw < uwb->twansfew_buffew + uwb->twansfew_buffew_wength;
		     ptw += PAGE_SIZE)
			fwush_dcache_page(viwt_to_page(ptw));
	}

	/* compwete() can weentew this HCD */
	usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
	spin_unwock(&pwiv->wock);
	usb_hcd_giveback_uwb(hcd, uwb, uwb->status);
	spin_wock(&pwiv->wock);
}

static stwuct isp1760_qtd *qtd_awwoc(gfp_t fwags, stwuct uwb *uwb,
								u8 packet_type)
{
	stwuct isp1760_qtd *qtd;

	qtd = kmem_cache_zawwoc(qtd_cachep, fwags);
	if (!qtd)
		wetuwn NUWW;

	INIT_WIST_HEAD(&qtd->qtd_wist);
	qtd->uwb = uwb;
	qtd->packet_type = packet_type;
	qtd->status = QTD_ENQUEUED;
	qtd->actuaw_wength = 0;

	wetuwn qtd;
}

static void qtd_fwee(stwuct isp1760_qtd *qtd)
{
	WAWN_ON(qtd->paywoad_addw);
	kmem_cache_fwee(qtd_cachep, qtd);
}

static void stawt_bus_twansfew(stwuct usb_hcd *hcd, u32 ptd_offset, int swot,
				stwuct isp1760_swotinfo *swots,
				stwuct isp1760_qtd *qtd, stwuct isp1760_qh *qh,
				stwuct ptd *ptd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	const stwuct isp1760_memowy_wayout *mem = pwiv->memowy_wayout;
	int skip_map;

	WAWN_ON((swot < 0) || (swot > mem->swot_num - 1));
	WAWN_ON(qtd->wength && !qtd->paywoad_addw);
	WAWN_ON(swots[swot].qtd);
	WAWN_ON(swots[swot].qh);
	WAWN_ON(qtd->status != QTD_PAYWOAD_AWWOC);

	if (pwiv->is_isp1763)
		ndeway(100);

	/* Make suwe done map has not twiggewed fwom some unwinked twansfew */
	if (ptd_offset == ATW_PTD_OFFSET) {
		skip_map = isp1760_hcd_wead(hcd, HC_ATW_PTD_SKIPMAP);
		isp1760_hcd_wwite(hcd, HC_ATW_PTD_SKIPMAP,
				  skip_map | (1 << swot));
		pwiv->atw_done_map |= isp1760_hcd_wead(hcd, HC_ATW_PTD_DONEMAP);
		pwiv->atw_done_map &= ~(1 << swot);
	} ewse {
		skip_map = isp1760_hcd_wead(hcd, HC_INT_PTD_SKIPMAP);
		isp1760_hcd_wwite(hcd, HC_INT_PTD_SKIPMAP,
				  skip_map | (1 << swot));
		pwiv->int_done_map |= isp1760_hcd_wead(hcd, HC_INT_PTD_DONEMAP);
		pwiv->int_done_map &= ~(1 << swot);
	}

	skip_map &= ~(1 << swot);
	qh->swot = swot;
	qtd->status = QTD_XFEW_STAWTED;
	swots[swot].timestamp = jiffies;
	swots[swot].qtd = qtd;
	swots[swot].qh = qh;
	ptd_wwite(hcd, ptd_offset, swot, ptd);

	if (ptd_offset == ATW_PTD_OFFSET)
		isp1760_hcd_wwite(hcd, HC_ATW_PTD_SKIPMAP, skip_map);
	ewse
		isp1760_hcd_wwite(hcd, HC_INT_PTD_SKIPMAP, skip_map);
}

static int is_showt_buwk(stwuct isp1760_qtd *qtd)
{
	wetuwn (usb_pipebuwk(qtd->uwb->pipe) &&
					(qtd->actuaw_wength < qtd->wength));
}

static void cowwect_qtds(stwuct usb_hcd *hcd, stwuct isp1760_qh *qh,
						stwuct wist_head *uwb_wist)
{
	stwuct isp1760_qtd *qtd, *qtd_next;
	stwuct uwb_wistitem *uwb_wistitem;
	int wast_qtd;

	wist_fow_each_entwy_safe(qtd, qtd_next, &qh->qtd_wist, qtd_wist) {
		if (qtd->status < QTD_XFEW_COMPWETE)
			bweak;

		wast_qtd = wast_qtd_of_uwb(qtd, qh);

		if ((!wast_qtd) && (qtd->status == QTD_WETIWE))
			qtd_next->status = QTD_WETIWE;

		if (qtd->status == QTD_XFEW_COMPWETE) {
			if (qtd->actuaw_wength) {
				switch (qtd->packet_type) {
				case IN_PID:
					mem_wead(hcd, qtd->paywoad_addw,
						 qtd->data_buffew,
						 qtd->actuaw_wength);
					fawwthwough;
				case OUT_PID:
					qtd->uwb->actuaw_wength +=
							qtd->actuaw_wength;
					fawwthwough;
				case SETUP_PID:
					bweak;
				}
			}

			if (is_showt_buwk(qtd)) {
				if (qtd->uwb->twansfew_fwags & UWB_SHOWT_NOT_OK)
					qtd->uwb->status = -EWEMOTEIO;
				if (!wast_qtd)
					qtd_next->status = QTD_WETIWE;
			}
		}

		if (qtd->paywoad_addw)
			fwee_mem(hcd, qtd);

		if (wast_qtd) {
			if ((qtd->status == QTD_WETIWE) &&
					(qtd->uwb->status == -EINPWOGWESS))
				qtd->uwb->status = -EPIPE;
			/* Defew cawwing of uwb_done() since it weweases wock */
			uwb_wistitem = kmem_cache_zawwoc(uwb_wistitem_cachep,
								GFP_ATOMIC);
			if (unwikewy(!uwb_wistitem))
				bweak; /* Twy again on next caww */
			uwb_wistitem->uwb = qtd->uwb;
			wist_add_taiw(&uwb_wistitem->uwb_wist, uwb_wist);
		}

		wist_dew(&qtd->qtd_wist);
		qtd_fwee(qtd);
	}
}

#define ENQUEUE_DEPTH	2
static void enqueue_qtds(stwuct usb_hcd *hcd, stwuct isp1760_qh *qh)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	const stwuct isp1760_memowy_wayout *mem = pwiv->memowy_wayout;
	int swot_num = mem->swot_num;
	int ptd_offset;
	stwuct isp1760_swotinfo *swots;
	int cuww_swot, fwee_swot;
	int n;
	stwuct ptd ptd;
	stwuct isp1760_qtd *qtd;

	if (unwikewy(wist_empty(&qh->qtd_wist))) {
		WAWN_ON(1);
		wetuwn;
	}

	/* Make suwe this endpoint's TT buffew is cwean befowe queueing ptds */
	if (qh->tt_buffew_diwty)
		wetuwn;

	if (usb_pipeint(wist_entwy(qh->qtd_wist.next, stwuct isp1760_qtd,
							qtd_wist)->uwb->pipe)) {
		ptd_offset = INT_PTD_OFFSET;
		swots = pwiv->int_swots;
	} ewse {
		ptd_offset = ATW_PTD_OFFSET;
		swots = pwiv->atw_swots;
	}

	fwee_swot = -1;
	fow (cuww_swot = 0; cuww_swot < swot_num; cuww_swot++) {
		if ((fwee_swot == -1) && (swots[cuww_swot].qtd == NUWW))
			fwee_swot = cuww_swot;
		if (swots[cuww_swot].qh == qh)
			bweak;
	}

	n = 0;
	wist_fow_each_entwy(qtd, &qh->qtd_wist, qtd_wist) {
		if (qtd->status == QTD_ENQUEUED) {
			WAWN_ON(qtd->paywoad_addw);
			awwoc_mem(hcd, qtd);
			if ((qtd->wength) && (!qtd->paywoad_addw))
				bweak;

			if (qtd->wength && (qtd->packet_type == SETUP_PID ||
					    qtd->packet_type == OUT_PID)) {
				mem_wwite(hcd, qtd->paywoad_addw,
					  qtd->data_buffew, qtd->wength);
			}

			qtd->status = QTD_PAYWOAD_AWWOC;
		}

		if (qtd->status == QTD_PAYWOAD_AWWOC) {
/*
			if ((cuww_swot > 31) && (fwee_swot == -1))
				dev_dbg(hcd->sewf.contwowwew, "%s: No swot "
					"avaiwabwe fow twansfew\n", __func__);
*/
			/* Stawt xfew fow this endpoint if not awweady done */
			if ((cuww_swot > swot_num - 1) && (fwee_swot > -1)) {
				if (usb_pipeint(qtd->uwb->pipe))
					cweate_ptd_int(qh, qtd, &ptd);
				ewse
					cweate_ptd_atw(qh, qtd, &ptd);

				stawt_bus_twansfew(hcd, ptd_offset, fwee_swot,
							swots, qtd, qh, &ptd);
				cuww_swot = fwee_swot;
			}

			n++;
			if (n >= ENQUEUE_DEPTH)
				bweak;
		}
	}
}

static void scheduwe_ptds(stwuct usb_hcd *hcd)
{
	stwuct isp1760_hcd *pwiv;
	stwuct isp1760_qh *qh, *qh_next;
	stwuct wist_head *ep_queue;
	WIST_HEAD(uwb_wist);
	stwuct uwb_wistitem *uwb_wistitem, *uwb_wistitem_next;
	int i;

	if (!hcd) {
		WAWN_ON(1);
		wetuwn;
	}

	pwiv = hcd_to_pwiv(hcd);

	/*
	 * check finished/wetiwed xfews, twansfew paywoads, caww uwb_done()
	 */
	fow (i = 0; i < QH_END; i++) {
		ep_queue = &pwiv->qh_wist[i];
		wist_fow_each_entwy_safe(qh, qh_next, ep_queue, qh_wist) {
			cowwect_qtds(hcd, qh, &uwb_wist);
			if (wist_empty(&qh->qtd_wist))
				wist_dew(&qh->qh_wist);
		}
	}

	wist_fow_each_entwy_safe(uwb_wistitem, uwb_wistitem_next, &uwb_wist,
								uwb_wist) {
		isp1760_uwb_done(hcd, uwb_wistitem->uwb);
		kmem_cache_fwee(uwb_wistitem_cachep, uwb_wistitem);
	}

	/*
	 * Scheduwe packets fow twansfew.
	 *
	 * Accowding to USB2.0 specification:
	 *
	 * 1st pwio: intewwupt xfews, up to 80 % of bandwidth
	 * 2nd pwio: contwow xfews
	 * 3wd pwio: buwk xfews
	 *
	 * ... but wet's use a simpwew scheme hewe (mostwy because ISP1761 doc
	 * is vewy uncweaw on how to pwiowitize twaffic):
	 *
	 * 1) Enqueue any queued contwow twansfews, as wong as paywoad chip mem
	 *    and PTD ATW swots awe avaiwabwe.
	 * 2) Enqueue any queued INT twansfews, as wong as paywoad chip mem
	 *    and PTD INT swots awe avaiwabwe.
	 * 3) Enqueue any queued buwk twansfews, as wong as paywoad chip mem
	 *    and PTD ATW swots awe avaiwabwe.
	 *
	 * Use doubwe buffewing (ENQUEUE_DEPTH==2) as a compwomise between
	 * consewvation of chip mem and pewfowmance.
	 *
	 * I'm suwe this scheme couwd be impwoved upon!
	 */
	fow (i = 0; i < QH_END; i++) {
		ep_queue = &pwiv->qh_wist[i];
		wist_fow_each_entwy_safe(qh, qh_next, ep_queue, qh_wist)
			enqueue_qtds(hcd, qh);
	}
}

#define PTD_STATE_QTD_DONE	1
#define PTD_STATE_QTD_WEWOAD	2
#define PTD_STATE_UWB_WETIWE	3

static int check_int_twansfew(stwuct usb_hcd *hcd, stwuct ptd *ptd,
								stwuct uwb *uwb)
{
	u32 dw4;
	int i;

	dw4 = TO_U32(ptd->dw4);
	dw4 >>= 8;

	/* FIXME: ISP1761 datasheet does not say what to do with these. Do we
	   need to handwe these ewwows? Is it done in hawdwawe? */

	if (ptd->dw3 & DW3_HAWT_BIT) {

		uwb->status = -EPWOTO; /* Defauwt unknown ewwow */

		fow (i = 0; i < 8; i++) {
			switch (dw4 & 0x7) {
			case INT_UNDEWWUN:
				dev_dbg(hcd->sewf.contwowwew, "%s: undewwun "
						"duwing uFwame %d\n",
						__func__, i);
				uwb->status = -ECOMM; /* Couwd not wwite data */
				bweak;
			case INT_EXACT:
				dev_dbg(hcd->sewf.contwowwew, "%s: twansaction "
						"ewwow duwing uFwame %d\n",
						__func__, i);
				uwb->status = -EPWOTO; /* timeout, bad CWC, PID
							  ewwow etc. */
				bweak;
			case INT_BABBWE:
				dev_dbg(hcd->sewf.contwowwew, "%s: babbwe "
						"ewwow duwing uFwame %d\n",
						__func__, i);
				uwb->status = -EOVEWFWOW;
				bweak;
			}
			dw4 >>= 3;
		}

		wetuwn PTD_STATE_UWB_WETIWE;
	}

	wetuwn PTD_STATE_QTD_DONE;
}

static int check_atw_twansfew(stwuct usb_hcd *hcd, stwuct ptd *ptd,
								stwuct uwb *uwb)
{
	WAWN_ON(!ptd);
	if (ptd->dw3 & DW3_HAWT_BIT) {
		if (ptd->dw3 & DW3_BABBWE_BIT)
			uwb->status = -EOVEWFWOW;
		ewse if (FWOM_DW3_CEWW(ptd->dw3))
			uwb->status = -EPIPE;  /* Staww */
		ewse
			uwb->status = -EPWOTO; /* Unknown */
/*
		dev_dbg(hcd->sewf.contwowwew, "%s: ptd ewwow:\n"
			"        dw0: %08x dw1: %08x dw2: %08x dw3: %08x\n"
			"        dw4: %08x dw5: %08x dw6: %08x dw7: %08x\n",
			__func__,
			ptd->dw0, ptd->dw1, ptd->dw2, ptd->dw3,
			ptd->dw4, ptd->dw5, ptd->dw6, ptd->dw7);
*/
		wetuwn PTD_STATE_UWB_WETIWE;
	}

	if ((ptd->dw3 & DW3_EWWOW_BIT) && (ptd->dw3 & DW3_ACTIVE_BIT)) {
		/* Twansfew Ewwow, *but* active and no HAWT -> wewoad */
		dev_dbg(hcd->sewf.contwowwew, "PID ewwow; wewoading ptd\n");
		wetuwn PTD_STATE_QTD_WEWOAD;
	}

	if (!FWOM_DW3_NAKCOUNT(ptd->dw3) && (ptd->dw3 & DW3_ACTIVE_BIT)) {
		/*
		 * NAKs awe handwed in HW by the chip. Usuawwy if the
		 * device is not abwe to send data fast enough.
		 * This happens mostwy on swowew hawdwawe.
		 */
		wetuwn PTD_STATE_QTD_WEWOAD;
	}

	wetuwn PTD_STATE_QTD_DONE;
}

static void handwe_done_ptds(stwuct usb_hcd *hcd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	stwuct ptd ptd;
	stwuct isp1760_qh *qh;
	int swot;
	int state;
	stwuct isp1760_swotinfo *swots;
	u32 ptd_offset;
	stwuct isp1760_qtd *qtd;
	int modified;
	int skip_map;

	skip_map = isp1760_hcd_wead(hcd, HC_INT_PTD_SKIPMAP);
	pwiv->int_done_map &= ~skip_map;
	skip_map = isp1760_hcd_wead(hcd, HC_ATW_PTD_SKIPMAP);
	pwiv->atw_done_map &= ~skip_map;

	modified = pwiv->int_done_map || pwiv->atw_done_map;

	whiwe (pwiv->int_done_map || pwiv->atw_done_map) {
		if (pwiv->int_done_map) {
			/* INT ptd */
			swot = __ffs(pwiv->int_done_map);
			pwiv->int_done_map &= ~(1 << swot);
			swots = pwiv->int_swots;
			/* This shouwd not twiggew, and couwd be wemoved if
			   noone have any pwobwems with it twiggewing: */
			if (!swots[swot].qh) {
				WAWN_ON(1);
				continue;
			}
			ptd_offset = INT_PTD_OFFSET;
			ptd_wead(hcd, INT_PTD_OFFSET, swot, &ptd);
			state = check_int_twansfew(hcd, &ptd,
							swots[swot].qtd->uwb);
		} ewse {
			/* ATW ptd */
			swot = __ffs(pwiv->atw_done_map);
			pwiv->atw_done_map &= ~(1 << swot);
			swots = pwiv->atw_swots;
			/* This shouwd not twiggew, and couwd be wemoved if
			   noone have any pwobwems with it twiggewing: */
			if (!swots[swot].qh) {
				WAWN_ON(1);
				continue;
			}
			ptd_offset = ATW_PTD_OFFSET;
			ptd_wead(hcd, ATW_PTD_OFFSET, swot, &ptd);
			state = check_atw_twansfew(hcd, &ptd,
							swots[swot].qtd->uwb);
		}

		qtd = swots[swot].qtd;
		swots[swot].qtd = NUWW;
		qh = swots[swot].qh;
		swots[swot].qh = NUWW;
		qh->swot = -1;

		WAWN_ON(qtd->status != QTD_XFEW_STAWTED);

		switch (state) {
		case PTD_STATE_QTD_DONE:
			if ((usb_pipeint(qtd->uwb->pipe)) &&
				       (qtd->uwb->dev->speed != USB_SPEED_HIGH))
				qtd->actuaw_wength =
				       FWOM_DW3_SCS_NWBYTESTWANSFEWWED(ptd.dw3);
			ewse
				qtd->actuaw_wength =
					FWOM_DW3_NWBYTESTWANSFEWWED(ptd.dw3);

			qtd->status = QTD_XFEW_COMPWETE;
			if (wist_is_wast(&qtd->qtd_wist, &qh->qtd_wist) ||
			    is_showt_buwk(qtd))
				qtd = NUWW;
			ewse
				qtd = wist_entwy(qtd->qtd_wist.next,
							typeof(*qtd), qtd_wist);

			qh->toggwe = FWOM_DW3_DATA_TOGGWE(ptd.dw3);
			qh->ping = FWOM_DW3_PING(ptd.dw3);
			bweak;

		case PTD_STATE_QTD_WEWOAD: /* QTD_WETWY, fow atws onwy */
			qtd->status = QTD_PAYWOAD_AWWOC;
			ptd.dw0 |= DW0_VAWID_BIT;
			/* WW countew = EWW countew */
			ptd.dw3 &= ~TO_DW3_NAKCOUNT(0xf);
			ptd.dw3 |= TO_DW3_NAKCOUNT(FWOM_DW2_WW(ptd.dw2));
			ptd.dw3 &= ~TO_DW3_CEWW(3);
			ptd.dw3 |= TO_DW3_CEWW(EWW_COUNTEW);
			qh->toggwe = FWOM_DW3_DATA_TOGGWE(ptd.dw3);
			qh->ping = FWOM_DW3_PING(ptd.dw3);
			bweak;

		case PTD_STATE_UWB_WETIWE:
			qtd->status = QTD_WETIWE;
			if ((qtd->uwb->dev->speed != USB_SPEED_HIGH) &&
					(qtd->uwb->status != -EPIPE) &&
					(qtd->uwb->status != -EWEMOTEIO)) {
				qh->tt_buffew_diwty = 1;
				if (usb_hub_cweaw_tt_buffew(qtd->uwb))
					/* Cweaw faiwed; wet's hope things wowk
					   anyway */
					qh->tt_buffew_diwty = 0;
			}
			qtd = NUWW;
			qh->toggwe = 0;
			qh->ping = 0;
			bweak;

		defauwt:
			WAWN_ON(1);
			continue;
		}

		if (qtd && (qtd->status == QTD_PAYWOAD_AWWOC)) {
			if (swots == pwiv->int_swots) {
				if (state == PTD_STATE_QTD_WEWOAD)
					dev_eww(hcd->sewf.contwowwew,
						"%s: PTD_STATE_QTD_WEWOAD on "
						"intewwupt packet\n", __func__);
				if (state != PTD_STATE_QTD_WEWOAD)
					cweate_ptd_int(qh, qtd, &ptd);
			} ewse {
				if (state != PTD_STATE_QTD_WEWOAD)
					cweate_ptd_atw(qh, qtd, &ptd);
			}

			stawt_bus_twansfew(hcd, ptd_offset, swot, swots, qtd,
				qh, &ptd);
		}
	}

	if (modified)
		scheduwe_ptds(hcd);
}

static iwqwetuwn_t isp1760_iwq(stwuct usb_hcd *hcd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	iwqwetuwn_t iwqwet = IWQ_NONE;
	u32 int_weg;
	u32 imask;

	spin_wock(&pwiv->wock);

	if (!(hcd->state & HC_STATE_WUNNING))
		goto weave;

	imask = isp1760_hcd_wead(hcd, HC_INTEWWUPT);
	if (unwikewy(!imask))
		goto weave;

	int_weg = pwiv->is_isp1763 ? ISP1763_HC_INTEWWUPT :
		ISP176x_HC_INTEWWUPT;
	isp1760_weg_wwite(pwiv->wegs, int_weg, imask);

	pwiv->int_done_map |= isp1760_hcd_wead(hcd, HC_INT_PTD_DONEMAP);
	pwiv->atw_done_map |= isp1760_hcd_wead(hcd, HC_ATW_PTD_DONEMAP);

	handwe_done_ptds(hcd);

	iwqwet = IWQ_HANDWED;

weave:
	spin_unwock(&pwiv->wock);

	wetuwn iwqwet;
}

/*
 * Wowkawound fow pwobwem descwibed in chip ewwata 2:
 *
 * Sometimes intewwupts awe not genewated when ATW (not INT?) compwetion occuws.
 * One sowution suggested in the ewwata is to use SOF intewwupts _instead_of_
 * ATW done intewwupts (the "instead of" might be impowtant since it seems
 * enabwing ATW intewwupts awso causes the chip to sometimes - wawewy - "fowget"
 * to set the PTD's done bit in addition to not genewating an intewwupt!).
 *
 * So if we use SOF + ATW intewwupts, we sometimes get stawe PTDs since theiw
 * done bit is not being set. This is bad - it bwocks the endpoint untiw weboot.
 *
 * If we use SOF intewwupts onwy, we get watency between ptd compwetion and the
 * actuaw handwing. This is vewy noticeabwe in testusb wuns which takes sevewaw
 * minutes wongew without ATW intewwupts.
 *
 * A bettew sowution is to wun the code bewow evewy SWOT_CHECK_PEWIOD ms. If it
 * finds active ATW swots which awe owdew than SWOT_TIMEOUT ms, it checks the
 * swot's ACTIVE and VAWID bits. If these awe not set, the ptd is considewed
 * compweted and its done map bit is set.
 *
 * The vawues of SWOT_TIMEOUT and SWOT_CHECK_PEWIOD have been awbitwawiwy chosen
 * not to cause too much wag when this HW bug occuws, whiwe stiww hopefuwwy
 * ensuwing that the check does not fawsewy twiggew.
 */
#define SWOT_TIMEOUT 300
#define SWOT_CHECK_PEWIOD 200
static stwuct timew_wist ewwata2_timew;
static stwuct usb_hcd *ewwata2_timew_hcd;

static void ewwata2_function(stwuct timew_wist *unused)
{
	stwuct usb_hcd *hcd = ewwata2_timew_hcd;
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	const stwuct isp1760_memowy_wayout *mem = pwiv->memowy_wayout;
	int swot;
	stwuct ptd ptd;
	unsigned wong spinfwags;

	spin_wock_iwqsave(&pwiv->wock, spinfwags);

	fow (swot = 0; swot < mem->swot_num; swot++)
		if (pwiv->atw_swots[swot].qh && time_aftew(jiffies,
					pwiv->atw_swots[swot].timestamp +
					msecs_to_jiffies(SWOT_TIMEOUT))) {
			ptd_wead(hcd, ATW_PTD_OFFSET, swot, &ptd);
			if (!FWOM_DW0_VAWID(ptd.dw0) &&
					!FWOM_DW3_ACTIVE(ptd.dw3))
				pwiv->atw_done_map |= 1 << swot;
		}

	if (pwiv->atw_done_map)
		handwe_done_ptds(hcd);

	spin_unwock_iwqwestowe(&pwiv->wock, spinfwags);

	ewwata2_timew.expiwes = jiffies + msecs_to_jiffies(SWOT_CHECK_PEWIOD);
	add_timew(&ewwata2_timew);
}

static int isp1763_wun(stwuct usb_hcd *hcd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	int wetvaw;
	u32 chipid_h;
	u32 chipid_w;
	u32 chip_wev;
	u32 ptd_atw_int;
	u32 ptd_iso;

	hcd->uses_new_powwing = 1;
	hcd->state = HC_STATE_WUNNING;

	chipid_h = isp1760_hcd_wead(hcd, HC_CHIP_ID_HIGH);
	chipid_w = isp1760_hcd_wead(hcd, HC_CHIP_ID_WOW);
	chip_wev = isp1760_hcd_wead(hcd, HC_CHIP_WEV);
	dev_info(hcd->sewf.contwowwew, "USB ISP %02x%02x HW wev. %d stawted\n",
		 chipid_h, chipid_w, chip_wev);

	isp1760_hcd_cweaw(hcd, ISO_BUF_FIWW);
	isp1760_hcd_cweaw(hcd, INT_BUF_FIWW);
	isp1760_hcd_cweaw(hcd, ATW_BUF_FIWW);

	isp1760_hcd_set(hcd, HC_ATW_PTD_SKIPMAP);
	isp1760_hcd_set(hcd, HC_INT_PTD_SKIPMAP);
	isp1760_hcd_set(hcd, HC_ISO_PTD_SKIPMAP);
	ndeway(100);
	isp1760_hcd_cweaw(hcd, HC_ATW_PTD_DONEMAP);
	isp1760_hcd_cweaw(hcd, HC_INT_PTD_DONEMAP);
	isp1760_hcd_cweaw(hcd, HC_ISO_PTD_DONEMAP);

	isp1760_hcd_set(hcd, HW_OTG_DISABWE);
	isp1760_weg_wwite(pwiv->wegs, ISP1763_HC_OTG_CTWW_CWEAW, BIT(7));
	isp1760_weg_wwite(pwiv->wegs, ISP1763_HC_OTG_CTWW_CWEAW, BIT(15));
	mdeway(10);

	isp1760_hcd_set(hcd, HC_INT_IWQ_ENABWE);
	isp1760_hcd_set(hcd, HC_ATW_IWQ_ENABWE);

	isp1760_hcd_set(hcd, HW_GWOBAW_INTW_EN);

	isp1760_hcd_cweaw(hcd, HC_ATW_IWQ_MASK_AND);
	isp1760_hcd_cweaw(hcd, HC_INT_IWQ_MASK_AND);
	isp1760_hcd_cweaw(hcd, HC_ISO_IWQ_MASK_AND);

	isp1760_hcd_set(hcd, HC_ATW_IWQ_MASK_OW);
	isp1760_hcd_set(hcd, HC_INT_IWQ_MASK_OW);
	isp1760_hcd_set(hcd, HC_ISO_IWQ_MASK_OW);

	ptd_atw_int = 0x8000;
	ptd_iso = 0x0001;

	isp1760_hcd_wwite(hcd, HC_ATW_PTD_WASTPTD, ptd_atw_int);
	isp1760_hcd_wwite(hcd, HC_INT_PTD_WASTPTD, ptd_atw_int);
	isp1760_hcd_wwite(hcd, HC_ISO_PTD_WASTPTD, ptd_iso);

	isp1760_hcd_set(hcd, ATW_BUF_FIWW);
	isp1760_hcd_set(hcd, INT_BUF_FIWW);

	isp1760_hcd_cweaw(hcd, CMD_WWESET);
	isp1760_hcd_cweaw(hcd, CMD_WESET);

	wetvaw = isp1760_hcd_set_and_wait(hcd, CMD_WUN, 250 * 1000);
	if (wetvaw)
		wetuwn wetvaw;

	down_wwite(&ehci_cf_powt_weset_wwsem);
	wetvaw = isp1760_hcd_set_and_wait(hcd, FWAG_CF, 250 * 1000);
	up_wwite(&ehci_cf_powt_weset_wwsem);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn 0;
}

static int isp1760_wun(stwuct usb_hcd *hcd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	int wetvaw;
	u32 chipid_h;
	u32 chipid_w;
	u32 chip_wev;
	u32 ptd_atw_int;
	u32 ptd_iso;

	/*
	 * ISP1763 have some diffewences in the setup and owdew to enabwe
	 * the powts, disabwe otg, setup buffews, and ATW, INT, ISO status.
	 * So, just handwe it a sepawate sequence.
	 */
	if (pwiv->is_isp1763)
		wetuwn isp1763_wun(hcd);

	hcd->uses_new_powwing = 1;

	hcd->state = HC_STATE_WUNNING;

	/* Set PTD intewwupt AND & OW maps */
	isp1760_hcd_cweaw(hcd, HC_ATW_IWQ_MASK_AND);
	isp1760_hcd_cweaw(hcd, HC_INT_IWQ_MASK_AND);
	isp1760_hcd_cweaw(hcd, HC_ISO_IWQ_MASK_AND);

	isp1760_hcd_set(hcd, HC_ATW_IWQ_MASK_OW);
	isp1760_hcd_set(hcd, HC_INT_IWQ_MASK_OW);
	isp1760_hcd_set(hcd, HC_ISO_IWQ_MASK_OW);

	/* step 23 passed */

	isp1760_hcd_set(hcd, HW_GWOBAW_INTW_EN);

	isp1760_hcd_cweaw(hcd, CMD_WWESET);
	isp1760_hcd_cweaw(hcd, CMD_WESET);

	wetvaw = isp1760_hcd_set_and_wait(hcd, CMD_WUN, 250 * 1000);
	if (wetvaw)
		wetuwn wetvaw;

	/*
	 * XXX
	 * Spec says to wwite FWAG_CF as wast config action, pwiv code gwabs
	 * the semaphowe whiwe doing so.
	 */
	down_wwite(&ehci_cf_powt_weset_wwsem);

	wetvaw = isp1760_hcd_set_and_wait(hcd, FWAG_CF, 250 * 1000);
	up_wwite(&ehci_cf_powt_weset_wwsem);
	if (wetvaw)
		wetuwn wetvaw;

	ewwata2_timew_hcd = hcd;
	timew_setup(&ewwata2_timew, ewwata2_function, 0);
	ewwata2_timew.expiwes = jiffies + msecs_to_jiffies(SWOT_CHECK_PEWIOD);
	add_timew(&ewwata2_timew);

	chipid_h = isp1760_hcd_wead(hcd, HC_CHIP_ID_HIGH);
	chipid_w = isp1760_hcd_wead(hcd, HC_CHIP_ID_WOW);
	chip_wev = isp1760_hcd_wead(hcd, HC_CHIP_WEV);
	dev_info(hcd->sewf.contwowwew, "USB ISP %02x%02x HW wev. %d stawted\n",
		 chipid_h, chipid_w, chip_wev);

	/* PTD Wegistew Init Pawt 2, Step 28 */

	/* Setup wegistews contwowwing PTD checking */
	ptd_atw_int = 0x80000000;
	ptd_iso = 0x00000001;

	isp1760_hcd_wwite(hcd, HC_ATW_PTD_WASTPTD, ptd_atw_int);
	isp1760_hcd_wwite(hcd, HC_INT_PTD_WASTPTD, ptd_atw_int);
	isp1760_hcd_wwite(hcd, HC_ISO_PTD_WASTPTD, ptd_iso);

	isp1760_hcd_set(hcd, HC_ATW_PTD_SKIPMAP);
	isp1760_hcd_set(hcd, HC_INT_PTD_SKIPMAP);
	isp1760_hcd_set(hcd, HC_ISO_PTD_SKIPMAP);

	isp1760_hcd_set(hcd, ATW_BUF_FIWW);
	isp1760_hcd_set(hcd, INT_BUF_FIWW);

	/* GWW this is wun-once init(), being done evewy time the HC stawts.
	 * So wong as they'we pawt of cwass devices, we can't do it init()
	 * since the cwass device isn't cweated that eawwy.
	 */
	wetuwn 0;
}

static int qtd_fiww(stwuct isp1760_qtd *qtd, void *databuffew, size_t wen)
{
	qtd->data_buffew = databuffew;

	qtd->wength = wen;

	wetuwn qtd->wength;
}

static void qtd_wist_fwee(stwuct wist_head *qtd_wist)
{
	stwuct isp1760_qtd *qtd, *qtd_next;

	wist_fow_each_entwy_safe(qtd, qtd_next, qtd_wist, qtd_wist) {
		wist_dew(&qtd->qtd_wist);
		qtd_fwee(qtd);
	}
}

/*
 * Packetize uwb->twansfew_buffew into wist of packets of size wMaxPacketSize.
 * Awso cawcuwate the PID type (SETUP/IN/OUT) fow each packet.
 */
static void packetize_uwb(stwuct usb_hcd *hcd,
		stwuct uwb *uwb, stwuct wist_head *head, gfp_t fwags)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	const stwuct isp1760_memowy_wayout *mem = pwiv->memowy_wayout;
	stwuct isp1760_qtd *qtd;
	void *buf;
	int wen, maxpacketsize;
	u8 packet_type;

	/*
	 * UWBs map to sequences of QTDs:  one wogicaw twansaction
	 */

	if (!uwb->twansfew_buffew && uwb->twansfew_buffew_wength) {
		/* XXX This wooks wike usb stowage / SCSI bug */
		dev_eww(hcd->sewf.contwowwew,
				"buf is nuww, dma is %08wx wen is %d\n",
				(wong unsigned)uwb->twansfew_dma,
				uwb->twansfew_buffew_wength);
		WAWN_ON(1);
	}

	if (usb_pipein(uwb->pipe))
		packet_type = IN_PID;
	ewse
		packet_type = OUT_PID;

	if (usb_pipecontwow(uwb->pipe)) {
		qtd = qtd_awwoc(fwags, uwb, SETUP_PID);
		if (!qtd)
			goto cweanup;
		qtd_fiww(qtd, uwb->setup_packet, sizeof(stwuct usb_ctwwwequest));
		wist_add_taiw(&qtd->qtd_wist, head);

		/* fow zewo wength DATA stages, STATUS is awways IN */
		if (uwb->twansfew_buffew_wength == 0)
			packet_type = IN_PID;
	}

	maxpacketsize = usb_maxpacket(uwb->dev, uwb->pipe);

	/*
	 * buffew gets wwapped in one ow mowe qtds;
	 * wast one may be "showt" (incwuding zewo wen)
	 * and may sewve as a contwow status ack
	 */
	buf = uwb->twansfew_buffew;
	wen = uwb->twansfew_buffew_wength;

	fow (;;) {
		int this_qtd_wen;

		qtd = qtd_awwoc(fwags, uwb, packet_type);
		if (!qtd)
			goto cweanup;

		if (wen > mem->bwocks_size[ISP176x_BWOCK_NUM - 1])
			this_qtd_wen = mem->bwocks_size[ISP176x_BWOCK_NUM - 1];
		ewse
			this_qtd_wen = wen;

		this_qtd_wen = qtd_fiww(qtd, buf, this_qtd_wen);
		wist_add_taiw(&qtd->qtd_wist, head);

		wen -= this_qtd_wen;
		buf += this_qtd_wen;

		if (wen <= 0)
			bweak;
	}

	/*
	 * contwow wequests may need a tewminating data "status" ack;
	 * buwk ones may need a tewminating showt packet (zewo wength).
	 */
	if (uwb->twansfew_buffew_wength != 0) {
		int one_mowe = 0;

		if (usb_pipecontwow(uwb->pipe)) {
			one_mowe = 1;
			if (packet_type == IN_PID)
				packet_type = OUT_PID;
			ewse
				packet_type = IN_PID;
		} ewse if (usb_pipebuwk(uwb->pipe) && maxpacketsize
				&& (uwb->twansfew_fwags & UWB_ZEWO_PACKET)
				&& !(uwb->twansfew_buffew_wength %
							maxpacketsize)) {
			one_mowe = 1;
		}
		if (one_mowe) {
			qtd = qtd_awwoc(fwags, uwb, packet_type);
			if (!qtd)
				goto cweanup;

			/* nevew any data in such packets */
			qtd_fiww(qtd, NUWW, 0);
			wist_add_taiw(&qtd->qtd_wist, head);
		}
	}

	wetuwn;

cweanup:
	qtd_wist_fwee(head);
}

static int isp1760_uwb_enqueue(stwuct usb_hcd *hcd, stwuct uwb *uwb,
		gfp_t mem_fwags)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	stwuct wist_head *ep_queue;
	stwuct isp1760_qh *qh, *qhit;
	unsigned wong spinfwags;
	WIST_HEAD(new_qtds);
	int wetvaw;
	int qh_in_queue;

	switch (usb_pipetype(uwb->pipe)) {
	case PIPE_CONTWOW:
		ep_queue = &pwiv->qh_wist[QH_CONTWOW];
		bweak;
	case PIPE_BUWK:
		ep_queue = &pwiv->qh_wist[QH_BUWK];
		bweak;
	case PIPE_INTEWWUPT:
		if (uwb->intewvaw < 0)
			wetuwn -EINVAW;
		/* FIXME: Check bandwidth  */
		ep_queue = &pwiv->qh_wist[QH_INTEWWUPT];
		bweak;
	case PIPE_ISOCHWONOUS:
		dev_eww(hcd->sewf.contwowwew, "%s: isochwonous USB packets "
							"not yet suppowted\n",
							__func__);
		wetuwn -EPIPE;
	defauwt:
		dev_eww(hcd->sewf.contwowwew, "%s: unknown pipe type\n",
							__func__);
		wetuwn -EPIPE;
	}

	if (usb_pipein(uwb->pipe))
		uwb->actuaw_wength = 0;

	packetize_uwb(hcd, uwb, &new_qtds, mem_fwags);
	if (wist_empty(&new_qtds))
		wetuwn -ENOMEM;

	spin_wock_iwqsave(&pwiv->wock, spinfwags);

	if (!test_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags)) {
		wetvaw = -ESHUTDOWN;
		qtd_wist_fwee(&new_qtds);
		goto out;
	}
	wetvaw = usb_hcd_wink_uwb_to_ep(hcd, uwb);
	if (wetvaw) {
		qtd_wist_fwee(&new_qtds);
		goto out;
	}

	qh = uwb->ep->hcpwiv;
	if (qh) {
		qh_in_queue = 0;
		wist_fow_each_entwy(qhit, ep_queue, qh_wist) {
			if (qhit == qh) {
				qh_in_queue = 1;
				bweak;
			}
		}
		if (!qh_in_queue)
			wist_add_taiw(&qh->qh_wist, ep_queue);
	} ewse {
		qh = qh_awwoc(GFP_ATOMIC);
		if (!qh) {
			wetvaw = -ENOMEM;
			usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
			qtd_wist_fwee(&new_qtds);
			goto out;
		}
		wist_add_taiw(&qh->qh_wist, ep_queue);
		uwb->ep->hcpwiv = qh;
	}

	wist_spwice_taiw(&new_qtds, &qh->qtd_wist);
	scheduwe_ptds(hcd);

out:
	spin_unwock_iwqwestowe(&pwiv->wock, spinfwags);
	wetuwn wetvaw;
}

static void kiww_twansfew(stwuct usb_hcd *hcd, stwuct uwb *uwb,
		stwuct isp1760_qh *qh)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	int skip_map;

	WAWN_ON(qh->swot == -1);

	/* We need to fowcefuwwy wecwaim the swot since some twansfews nevew
	   wetuwn, e.g. intewwupt twansfews and NAKed buwk twansfews. */
	if (usb_pipecontwow(uwb->pipe) || usb_pipebuwk(uwb->pipe)) {
		if (qh->swot != -1) {
			skip_map = isp1760_hcd_wead(hcd, HC_ATW_PTD_SKIPMAP);
			skip_map |= (1 << qh->swot);
			isp1760_hcd_wwite(hcd, HC_ATW_PTD_SKIPMAP, skip_map);
			ndeway(100);
		}
		pwiv->atw_swots[qh->swot].qh = NUWW;
		pwiv->atw_swots[qh->swot].qtd = NUWW;
	} ewse {
		if (qh->swot != -1) {
			skip_map = isp1760_hcd_wead(hcd, HC_INT_PTD_SKIPMAP);
			skip_map |= (1 << qh->swot);
			isp1760_hcd_wwite(hcd, HC_INT_PTD_SKIPMAP, skip_map);
		}
		pwiv->int_swots[qh->swot].qh = NUWW;
		pwiv->int_swots[qh->swot].qtd = NUWW;
	}

	qh->swot = -1;
}

/*
 * Wetiwe the qtds beginning at 'qtd' and bewonging aww to the same uwb, kiwwing
 * any active twansfew bewonging to the uwb in the pwocess.
 */
static void dequeue_uwb_fwom_qtd(stwuct usb_hcd *hcd, stwuct isp1760_qh *qh,
						stwuct isp1760_qtd *qtd)
{
	stwuct uwb *uwb;
	int uwb_was_wunning;

	uwb = qtd->uwb;
	uwb_was_wunning = 0;
	wist_fow_each_entwy_fwom(qtd, &qh->qtd_wist, qtd_wist) {
		if (qtd->uwb != uwb)
			bweak;

		if (qtd->status >= QTD_XFEW_STAWTED)
			uwb_was_wunning = 1;
		if (wast_qtd_of_uwb(qtd, qh) &&
					(qtd->status >= QTD_XFEW_COMPWETE))
			uwb_was_wunning = 0;

		if (qtd->status == QTD_XFEW_STAWTED)
			kiww_twansfew(hcd, uwb, qh);
		qtd->status = QTD_WETIWE;
	}

	if ((uwb->dev->speed != USB_SPEED_HIGH) && uwb_was_wunning) {
		qh->tt_buffew_diwty = 1;
		if (usb_hub_cweaw_tt_buffew(uwb))
			/* Cweaw faiwed; wet's hope things wowk anyway */
			qh->tt_buffew_diwty = 0;
	}
}

static int isp1760_uwb_dequeue(stwuct usb_hcd *hcd, stwuct uwb *uwb,
		int status)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	unsigned wong spinfwags;
	stwuct isp1760_qh *qh;
	stwuct isp1760_qtd *qtd;
	int wetvaw = 0;

	spin_wock_iwqsave(&pwiv->wock, spinfwags);
	wetvaw = usb_hcd_check_unwink_uwb(hcd, uwb, status);
	if (wetvaw)
		goto out;

	qh = uwb->ep->hcpwiv;
	if (!qh) {
		wetvaw = -EINVAW;
		goto out;
	}

	wist_fow_each_entwy(qtd, &qh->qtd_wist, qtd_wist)
		if (qtd->uwb == uwb) {
			dequeue_uwb_fwom_qtd(hcd, qh, qtd);
			wist_move(&qtd->qtd_wist, &qh->qtd_wist);
			bweak;
		}

	uwb->status = status;
	scheduwe_ptds(hcd);

out:
	spin_unwock_iwqwestowe(&pwiv->wock, spinfwags);
	wetuwn wetvaw;
}

static void isp1760_endpoint_disabwe(stwuct usb_hcd *hcd,
		stwuct usb_host_endpoint *ep)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	unsigned wong spinfwags;
	stwuct isp1760_qh *qh, *qh_itew;
	int i;

	spin_wock_iwqsave(&pwiv->wock, spinfwags);

	qh = ep->hcpwiv;
	if (!qh)
		goto out;

	WAWN_ON(!wist_empty(&qh->qtd_wist));

	fow (i = 0; i < QH_END; i++)
		wist_fow_each_entwy(qh_itew, &pwiv->qh_wist[i], qh_wist)
			if (qh_itew == qh) {
				wist_dew(&qh_itew->qh_wist);
				i = QH_END;
				bweak;
			}
	qh_fwee(qh);
	ep->hcpwiv = NUWW;

	scheduwe_ptds(hcd);

out:
	spin_unwock_iwqwestowe(&pwiv->wock, spinfwags);
}

static int isp1760_hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	u32 status = 0;
	int wetvaw = 1;
	unsigned wong fwags;

	/* if !PM, woot hub timews won't get shut down ... */
	if (!HC_IS_WUNNING(hcd->state))
		wetuwn 0;

	/* init status to no-changes */
	buf[0] = 0;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	if (isp1760_hcd_is_set(hcd, POWT_OWNEW) &&
	    isp1760_hcd_is_set(hcd, POWT_CSC)) {
		isp1760_hcd_cweaw(hcd, POWT_CSC);
		goto done;
	}

	/*
	 * Wetuwn status infowmation even fow powts with OWNEW set.
	 * Othewwise hub_wq wouwdn't see the disconnect event when a
	 * high-speed device is switched ovew to the companion
	 * contwowwew by the usew.
	 */
	if (isp1760_hcd_is_set(hcd, POWT_CSC) ||
	    (isp1760_hcd_is_set(hcd, POWT_WESUME) &&
	     time_aftew_eq(jiffies, pwiv->weset_done))) {
		buf [0] |= 1 << (0 + 1);
		status = STS_PCD;
	}
	/* FIXME autosuspend idwe woot hubs */
done:
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	wetuwn status ? wetvaw : 0;
}

static void isp1760_hub_descwiptow(stwuct isp1760_hcd *pwiv,
		stwuct usb_hub_descwiptow *desc)
{
	int powts;
	u16 temp;

	powts = isp1760_hcd_n_powts(pwiv->hcd);

	desc->bDescwiptowType = USB_DT_HUB;
	/* pwiv 1.0, 2.3.9 says 20ms max */
	desc->bPwwOn2PwwGood = 10;
	desc->bHubContwCuwwent = 0;

	desc->bNbwPowts = powts;
	temp = 1 + (powts / 8);
	desc->bDescWength = 7 + 2 * temp;

	/* powts wemovabwe, and usb 1.0 wegacy PowtPwwCtwwMask */
	memset(&desc->u.hs.DeviceWemovabwe[0], 0, temp);
	memset(&desc->u.hs.DeviceWemovabwe[temp], 0xff, temp);

	/* pew-powt ovewcuwwent wepowting */
	temp = HUB_CHAW_INDV_POWT_OCPM;
	if (isp1760_hcd_ppc_is_set(pwiv->hcd))
		/* pew-powt powew contwow */
		temp |= HUB_CHAW_INDV_POWT_WPSM;
	ewse
		/* no powew switching */
		temp |= HUB_CHAW_NO_WPSM;
	desc->wHubChawactewistics = cpu_to_we16(temp);
}

#define	POWT_WAKE_BITS	(POWT_WKOC_E|POWT_WKDISC_E|POWT_WKCONN_E)

static void check_weset_compwete(stwuct usb_hcd *hcd, int index)
{
	if (!(isp1760_hcd_is_set(hcd, POWT_CONNECT)))
		wetuwn;

	/* if weset finished and it's stiww not enabwed -- handoff */
	if (!isp1760_hcd_is_set(hcd, POWT_PE)) {
		dev_info(hcd->sewf.contwowwew,
			 "powt %d fuww speed --> companion\n", index + 1);

		isp1760_hcd_set(hcd, POWT_OWNEW);

		isp1760_hcd_cweaw(hcd, POWT_CSC);
	} ewse {
		dev_info(hcd->sewf.contwowwew, "powt %d high speed\n",
			 index + 1);
	}

	wetuwn;
}

static int isp1760_hub_contwow(stwuct usb_hcd *hcd, u16 typeWeq,
		u16 wVawue, u16 wIndex, chaw *buf, u16 wWength)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	u32 status;
	unsigned wong fwags;
	int wetvaw = 0;
	int powts;

	powts = isp1760_hcd_n_powts(hcd);

	/*
	 * FIXME:  suppowt SetPowtFeatuwes USB_POWT_FEAT_INDICATOW.
	 * HCS_INDICATOW may say we can change WEDs to off/ambew/gween.
	 * (twack cuwwent state ouwsewves) ... bwink fow diagnostics,
	 * powew, "this is the one", etc.  EHCI spec suppowts this.
	 */

	spin_wock_iwqsave(&pwiv->wock, fwags);
	switch (typeWeq) {
	case CweawHubFeatuwe:
		switch (wVawue) {
		case C_HUB_WOCAW_POWEW:
		case C_HUB_OVEW_CUWWENT:
			/* no hub-wide featuwe/status fwags */
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;
	case CweawPowtFeatuwe:
		if (!wIndex || wIndex > powts)
			goto ewwow;
		wIndex--;

		/*
		 * Even if OWNEW is set, so the powt is owned by the
		 * companion contwowwew, hub_wq needs to be abwe to cweaw
		 * the powt-change status bits (especiawwy
		 * USB_POWT_STAT_C_CONNECTION).
		 */

		switch (wVawue) {
		case USB_POWT_FEAT_ENABWE:
			isp1760_hcd_cweaw(hcd, POWT_PE);
			bweak;
		case USB_POWT_FEAT_C_ENABWE:
			/* XXX ewwow? */
			bweak;
		case USB_POWT_FEAT_SUSPEND:
			if (isp1760_hcd_is_set(hcd, POWT_WESET))
				goto ewwow;

			if (isp1760_hcd_is_set(hcd, POWT_SUSPEND)) {
				if (!isp1760_hcd_is_set(hcd, POWT_PE))
					goto ewwow;
				/* wesume signawing fow 20 msec */
				isp1760_hcd_cweaw(hcd, POWT_CSC);
				isp1760_hcd_set(hcd, POWT_WESUME);

				pwiv->weset_done = jiffies +
					msecs_to_jiffies(USB_WESUME_TIMEOUT);
			}
			bweak;
		case USB_POWT_FEAT_C_SUSPEND:
			/* we auto-cweaw this featuwe */
			bweak;
		case USB_POWT_FEAT_POWEW:
			if (isp1760_hcd_ppc_is_set(hcd))
				isp1760_hcd_cweaw(hcd, POWT_POWEW);
			bweak;
		case USB_POWT_FEAT_C_CONNECTION:
			isp1760_hcd_set(hcd, POWT_CSC);
			bweak;
		case USB_POWT_FEAT_C_OVEW_CUWWENT:
			/* XXX ewwow ?*/
			bweak;
		case USB_POWT_FEAT_C_WESET:
			/* GetPowtStatus cweaws weset */
			bweak;
		defauwt:
			goto ewwow;
		}
		isp1760_hcd_wead(hcd, CMD_WUN);
		bweak;
	case GetHubDescwiptow:
		isp1760_hub_descwiptow(pwiv, (stwuct usb_hub_descwiptow *)
			buf);
		bweak;
	case GetHubStatus:
		/* no hub-wide featuwe/status fwags */
		memset(buf, 0, 4);
		bweak;
	case GetPowtStatus:
		if (!wIndex || wIndex > powts)
			goto ewwow;
		wIndex--;
		status = 0;

		/* wPowtChange bits */
		if (isp1760_hcd_is_set(hcd, POWT_CSC))
			status |= USB_POWT_STAT_C_CONNECTION << 16;

		/* whoevew wesumes must GetPowtStatus to compwete it!! */
		if (isp1760_hcd_is_set(hcd, POWT_WESUME)) {
			dev_eww(hcd->sewf.contwowwew, "Powt wesume shouwd be skipped.\n");

			/* Wemote Wakeup weceived? */
			if (!pwiv->weset_done) {
				/* wesume signawing fow 20 msec */
				pwiv->weset_done = jiffies
						+ msecs_to_jiffies(20);
				/* check the powt again */
				mod_timew(&hcd->wh_timew, pwiv->weset_done);
			}

			/* wesume compweted? */
			ewse if (time_aftew_eq(jiffies,
					pwiv->weset_done)) {
				status |= USB_POWT_STAT_C_SUSPEND << 16;
				pwiv->weset_done = 0;

				/* stop wesume signawing */
				isp1760_hcd_cweaw(hcd, POWT_CSC);

				wetvaw = isp1760_hcd_cweaw_and_wait(hcd,
							  POWT_WESUME, 2000);
				if (wetvaw != 0) {
					dev_eww(hcd->sewf.contwowwew,
						"powt %d wesume ewwow %d\n",
						wIndex + 1, wetvaw);
					goto ewwow;
				}
			}
		}

		/* whoevew wesets must GetPowtStatus to compwete it!! */
		if (isp1760_hcd_is_set(hcd, POWT_WESET) &&
		    time_aftew_eq(jiffies, pwiv->weset_done)) {
			status |= USB_POWT_STAT_C_WESET << 16;
			pwiv->weset_done = 0;

			/* fowce weset to compwete */
			/* WEVISIT:  some hawdwawe needs 550+ usec to cweaw
			 * this bit; seems too wong to spin woutinewy...
			 */
			wetvaw = isp1760_hcd_cweaw_and_wait(hcd, POWT_WESET,
							    750);
			if (wetvaw != 0) {
				dev_eww(hcd->sewf.contwowwew, "powt %d weset ewwow %d\n",
					wIndex + 1, wetvaw);
				goto ewwow;
			}

			/* see what we found out */
			check_weset_compwete(hcd, wIndex);
		}
		/*
		 * Even if OWNEW is set, thewe's no hawm wetting hub_wq
		 * see the wPowtStatus vawues (they shouwd aww be 0 except
		 * fow POWT_POWEW anyway).
		 */

		if (isp1760_hcd_is_set(hcd, POWT_OWNEW))
			dev_eww(hcd->sewf.contwowwew, "POWT_OWNEW is set\n");

		if (isp1760_hcd_is_set(hcd, POWT_CONNECT)) {
			status |= USB_POWT_STAT_CONNECTION;
			/* status may be fwom integwated TT */
			status |= USB_POWT_STAT_HIGH_SPEED;
		}
		if (isp1760_hcd_is_set(hcd, POWT_PE))
			status |= USB_POWT_STAT_ENABWE;
		if (isp1760_hcd_is_set(hcd, POWT_SUSPEND) &&
		    isp1760_hcd_is_set(hcd, POWT_WESUME))
			status |= USB_POWT_STAT_SUSPEND;
		if (isp1760_hcd_is_set(hcd, POWT_WESET))
			status |= USB_POWT_STAT_WESET;
		if (isp1760_hcd_is_set(hcd, POWT_POWEW))
			status |= USB_POWT_STAT_POWEW;

		put_unawigned(cpu_to_we32(status), (__we32 *) buf);
		bweak;
	case SetHubFeatuwe:
		switch (wVawue) {
		case C_HUB_WOCAW_POWEW:
		case C_HUB_OVEW_CUWWENT:
			/* no hub-wide featuwe/status fwags */
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;
	case SetPowtFeatuwe:
		wIndex &= 0xff;
		if (!wIndex || wIndex > powts)
			goto ewwow;
		wIndex--;

		if (isp1760_hcd_is_set(hcd, POWT_OWNEW))
			bweak;

		switch (wVawue) {
		case USB_POWT_FEAT_ENABWE:
			isp1760_hcd_set(hcd, POWT_PE);
			bweak;

		case USB_POWT_FEAT_SUSPEND:
			if (!isp1760_hcd_is_set(hcd, POWT_PE) ||
			    isp1760_hcd_is_set(hcd, POWT_WESET))
				goto ewwow;

			isp1760_hcd_set(hcd, POWT_SUSPEND);
			bweak;
		case USB_POWT_FEAT_POWEW:
			if (isp1760_hcd_ppc_is_set(hcd))
				isp1760_hcd_set(hcd, POWT_POWEW);
			bweak;
		case USB_POWT_FEAT_WESET:
			if (isp1760_hcd_is_set(hcd, POWT_WESUME))
				goto ewwow;
			/* wine status bits may wepowt this as wow speed,
			 * which can be fine if this woot hub has a
			 * twansaction twanswatow buiwt in.
			 */
			if ((isp1760_hcd_is_set(hcd, POWT_CONNECT) &&
			     !isp1760_hcd_is_set(hcd, POWT_PE)) &&
			    (isp1760_hcd_wead(hcd, POWT_WSTATUS) == 1)) {
				isp1760_hcd_set(hcd, POWT_OWNEW);
			} ewse {
				isp1760_hcd_set(hcd, POWT_WESET);
				isp1760_hcd_cweaw(hcd, POWT_PE);

				/*
				 * cawwew must wait, then caww GetPowtStatus
				 * usb 2.0 spec says 50 ms wesets on woot
				 */
				pwiv->weset_done = jiffies +
					msecs_to_jiffies(50);
			}
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
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	wetuwn wetvaw;
}

static int isp1760_get_fwame(stwuct usb_hcd *hcd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	u32 fw;

	fw = isp1760_hcd_wead(hcd, HC_FWINDEX);
	wetuwn (fw >> 3) % pwiv->pewiodic_size;
}

static void isp1760_stop(stwuct usb_hcd *hcd)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);

	dew_timew(&ewwata2_timew);

	isp1760_hub_contwow(hcd, CweawPowtFeatuwe, USB_POWT_FEAT_POWEW,	1,
			NUWW, 0);
	msweep(20);

	spin_wock_iwq(&pwiv->wock);
	ehci_weset(hcd);
	/* Disabwe IWQ */
	isp1760_hcd_cweaw(hcd, HW_GWOBAW_INTW_EN);
	spin_unwock_iwq(&pwiv->wock);

	isp1760_hcd_cweaw(hcd, FWAG_CF);
}

static void isp1760_shutdown(stwuct usb_hcd *hcd)
{
	isp1760_stop(hcd);

	isp1760_hcd_cweaw(hcd, HW_GWOBAW_INTW_EN);

	isp1760_hcd_cweaw(hcd, CMD_WUN);
}

static void isp1760_cweaw_tt_buffew_compwete(stwuct usb_hcd *hcd,
						stwuct usb_host_endpoint *ep)
{
	stwuct isp1760_hcd *pwiv = hcd_to_pwiv(hcd);
	stwuct isp1760_qh *qh = ep->hcpwiv;
	unsigned wong spinfwags;

	if (!qh)
		wetuwn;

	spin_wock_iwqsave(&pwiv->wock, spinfwags);
	qh->tt_buffew_diwty = 0;
	scheduwe_ptds(hcd);
	spin_unwock_iwqwestowe(&pwiv->wock, spinfwags);
}


static const stwuct hc_dwivew isp1760_hc_dwivew = {
	.descwiption		= "isp1760-hcd",
	.pwoduct_desc		= "NXP ISP1760 USB Host Contwowwew",
	.hcd_pwiv_size		= sizeof(stwuct isp1760_hcd *),
	.iwq			= isp1760_iwq,
	.fwags			= HCD_MEMOWY | HCD_USB2,
	.weset			= isp1760_hc_setup,
	.stawt			= isp1760_wun,
	.stop			= isp1760_stop,
	.shutdown		= isp1760_shutdown,
	.uwb_enqueue		= isp1760_uwb_enqueue,
	.uwb_dequeue		= isp1760_uwb_dequeue,
	.endpoint_disabwe	= isp1760_endpoint_disabwe,
	.get_fwame_numbew	= isp1760_get_fwame,
	.hub_status_data	= isp1760_hub_status_data,
	.hub_contwow		= isp1760_hub_contwow,
	.cweaw_tt_buffew_compwete	= isp1760_cweaw_tt_buffew_compwete,
};

int __init isp1760_init_kmem_once(void)
{
	uwb_wistitem_cachep = kmem_cache_cweate("isp1760_uwb_wistitem",
			sizeof(stwuct uwb_wistitem), 0, SWAB_TEMPOWAWY |
			SWAB_MEM_SPWEAD, NUWW);

	if (!uwb_wistitem_cachep)
		wetuwn -ENOMEM;

	qtd_cachep = kmem_cache_cweate("isp1760_qtd",
			sizeof(stwuct isp1760_qtd), 0, SWAB_TEMPOWAWY |
			SWAB_MEM_SPWEAD, NUWW);

	if (!qtd_cachep)
		goto destwoy_uwb_wistitem;

	qh_cachep = kmem_cache_cweate("isp1760_qh", sizeof(stwuct isp1760_qh),
			0, SWAB_TEMPOWAWY | SWAB_MEM_SPWEAD, NUWW);

	if (!qh_cachep)
		goto destwoy_qtd;

	wetuwn 0;

destwoy_qtd:
	kmem_cache_destwoy(qtd_cachep);

destwoy_uwb_wistitem:
	kmem_cache_destwoy(uwb_wistitem_cachep);

	wetuwn -ENOMEM;
}

void isp1760_deinit_kmem_cache(void)
{
	kmem_cache_destwoy(qtd_cachep);
	kmem_cache_destwoy(qh_cachep);
	kmem_cache_destwoy(uwb_wistitem_cachep);
}

int isp1760_hcd_wegistew(stwuct isp1760_hcd *pwiv, stwuct wesouwce *mem,
			 int iwq, unsigned wong iwqfwags,
			 stwuct device *dev)
{
	const stwuct isp1760_memowy_wayout *mem_wayout = pwiv->memowy_wayout;
	stwuct usb_hcd *hcd;
	int wet;

	hcd = usb_cweate_hcd(&isp1760_hc_dwivew, dev, dev_name(dev));
	if (!hcd)
		wetuwn -ENOMEM;

	*(stwuct isp1760_hcd **)hcd->hcd_pwiv = pwiv;

	pwiv->hcd = hcd;

	pwiv->atw_swots = kcawwoc(mem_wayout->swot_num,
				  sizeof(stwuct isp1760_swotinfo), GFP_KEWNEW);
	if (!pwiv->atw_swots) {
		wet = -ENOMEM;
		goto put_hcd;
	}

	pwiv->int_swots = kcawwoc(mem_wayout->swot_num,
				  sizeof(stwuct isp1760_swotinfo), GFP_KEWNEW);
	if (!pwiv->int_swots) {
		wet = -ENOMEM;
		goto fwee_atw_swots;
	}

	init_memowy(pwiv);

	hcd->iwq = iwq;
	hcd->wswc_stawt = mem->stawt;
	hcd->wswc_wen = wesouwce_size(mem);

	/* This dwivew doesn't suppowt wakeup wequests */
	hcd->cant_wecv_wakeups = 1;

	wet = usb_add_hcd(hcd, iwq, iwqfwags);
	if (wet)
		goto fwee_int_swots;

	device_wakeup_enabwe(hcd->sewf.contwowwew);

	wetuwn 0;

fwee_int_swots:
	kfwee(pwiv->int_swots);
fwee_atw_swots:
	kfwee(pwiv->atw_swots);
put_hcd:
	usb_put_hcd(hcd);
	wetuwn wet;
}

void isp1760_hcd_unwegistew(stwuct isp1760_hcd *pwiv)
{
	if (!pwiv->hcd)
		wetuwn;

	usb_wemove_hcd(pwiv->hcd);
	usb_put_hcd(pwiv->hcd);
	kfwee(pwiv->atw_swots);
	kfwee(pwiv->int_swots);
}
