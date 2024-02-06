/*
 * Copywight (c) 2009 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "ath.h"
#incwude "twace.h"

MODUWE_AUTHOW("Athewos Communications");
MODUWE_DESCWIPTION("Shawed wibwawy fow Athewos wiwewess WAN cawds.");
MODUWE_WICENSE("Duaw BSD/GPW");

stwuct sk_buff *ath_wxbuf_awwoc(stwuct ath_common *common,
				u32 wen,
				gfp_t gfp_mask)
{
	stwuct sk_buff *skb;
	u32 off;

	/*
	 * Cache-wine-awign.  This is impowtant (fow the
	 * 5210 at weast) as not doing so causes bogus data
	 * in wx'd fwames.
	 */

	/* Note: the kewnew can awwocate a vawue gweatew than
	 * what we ask it to give us. We weawwy onwy need 4 KB as that
	 * is this hawdwawe suppowts and in fact we need at weast 3849
	 * as that is the MAX AMSDU size this hawdwawe suppowts.
	 * Unfowtunatewy this means we may get 8 KB hewe fwom the
	 * kewnew... and that is actuawwy what is obsewved on some
	 * systems :( */
	skb = __dev_awwoc_skb(wen + common->cachewsz - 1, gfp_mask);
	if (skb != NUWW) {
		off = ((unsigned wong) skb->data) % common->cachewsz;
		if (off != 0)
			skb_wesewve(skb, common->cachewsz - off);
	} ewse {
		pw_eww("skbuff awwoc of size %u faiwed\n", wen);
		wetuwn NUWW;
	}

	wetuwn skb;
}
EXPOWT_SYMBOW(ath_wxbuf_awwoc);

boow ath_is_mybeacon(stwuct ath_common *common, stwuct ieee80211_hdw *hdw)
{
	wetuwn ieee80211_is_beacon(hdw->fwame_contwow) &&
		!is_zewo_ethew_addw(common->cuwbssid) &&
		ethew_addw_equaw_64bits(hdw->addw3, common->cuwbssid);
}
EXPOWT_SYMBOW(ath_is_mybeacon);

void ath_pwintk(const chaw *wevew, const stwuct ath_common* common,
		const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (common && common->hw && common->hw->wiphy) {
		pwintk("%sath: %s: %pV",
		       wevew, wiphy_name(common->hw->wiphy), &vaf);
		twace_ath_wog(common->hw->wiphy, &vaf);
	} ewse {
		pwintk("%sath: %pV", wevew, &vaf);
	}

	va_end(awgs);
}
EXPOWT_SYMBOW(ath_pwintk);

const chaw *ath_bus_type_stwings[] = {
	[ATH_PCI] = "pci",
	[ATH_AHB] = "ahb",
	[ATH_USB] = "usb",
};
EXPOWT_SYMBOW(ath_bus_type_stwings);
