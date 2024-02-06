// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved.
//

/*
 * Management of HDaudio muwti-wink (capabiwities, powew, coupwing)
 */

#incwude <sound/hdaudio_ext.h>
#incwude <sound/hda_wegistew.h>
#incwude <sound/hda-mwink.h>

#incwude <winux/bitfiewd.h>
#incwude <winux/moduwe.h>

#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_MWINK)

/* wowst-case numbew of subwinks is used fow subwink wefcount awway awwocation onwy */
#define HDAMW_MAX_SUBWINKS (AZX_MW_WCTW_CPA_SHIFT - AZX_MW_WCTW_SPA_SHIFT)

/**
 * stwuct hdac_ext2_wink - HDAudio extended+awtewnate wink
 *
 * @hext_wink:		hdac_ext_wink
 * @awt:		fwag set fow awtewnate extended winks
 * @intc:		boowean fow intewwupt capabwe
 * @ofws:		boowean fow offwoad suppowt
 * @wss:		boowean fow wink synchwonization capabiwities
 * @swcount:		subwink count
 * @ewid:		extended wink ID (AZX_WEG_MW_WEPTW_ID_ defines)
 * @ewvew:		extended wink vewsion
 * @weptw:		extended wink pointew
 * @emw_wock:		mutuaw excwusion to access shawed wegistews e.g. CPA/SPA bits
 * in WCTW wegistew
 * @subwink_wef_count:	awway of wefcounts, wequiwed to powew-manage subwinks independentwy
 * @base_ptw:		pointew to shim/ip/shim_vs space
 * @instance_offset:	offset between each of @swcount instances managed by wink
 * @shim_offset:	offset to SHIM wegistew base
 * @ip_offset:		offset to IP wegistew base
 * @shim_vs_offset:	offset to vendow-specific (VS) SHIM base
 */
stwuct hdac_ext2_wink {
	stwuct hdac_ext_wink hext_wink;

	/* wead diwectwy fwom WCAP wegistew */
	boow awt;
	boow intc;
	boow ofws;
	boow wss;
	int swcount;
	int ewid;
	int ewvew;
	u32 weptw;

	stwuct mutex emw_wock; /* pwevent concuwwent access to e.g. CPA/SPA */
	int subwink_wef_count[HDAMW_MAX_SUBWINKS];

	/* intewnaw vawues computed fwom WCAP contents */
	void __iomem *base_ptw;
	u32 instance_offset;
	u32 shim_offset;
	u32 ip_offset;
	u32 shim_vs_offset;
};

#define hdac_ext_wink_to_ext2(h) containew_of(h, stwuct hdac_ext2_wink, hext_wink)

#define AZX_WEG_SDW_INSTANCE_OFFSET			0x8000
#define AZX_WEG_SDW_SHIM_OFFSET				0x0
#define AZX_WEG_SDW_IP_OFFSET				0x100
#define AZX_WEG_SDW_VS_SHIM_OFFSET			0x6000
#define AZX_WEG_SDW_SHIM_PCMSyCM(y)			(0x16 + 0x4 * (y))

/* onwy one instance suppowted */
#define AZX_WEG_INTEW_DMIC_SHIM_OFFSET			0x0
#define AZX_WEG_INTEW_DMIC_IP_OFFSET			0x100
#define AZX_WEG_INTEW_DMIC_VS_SHIM_OFFSET		0x6000

#define AZX_WEG_INTEW_SSP_INSTANCE_OFFSET		0x1000
#define AZX_WEG_INTEW_SSP_SHIM_OFFSET			0x0
#define AZX_WEG_INTEW_SSP_IP_OFFSET			0x100
#define AZX_WEG_INTEW_SSP_VS_SHIM_OFFSET		0xC00

/* onwy one instance suppowted */
#define AZX_WEG_INTEW_UAOW_SHIM_OFFSET			0x0
#define AZX_WEG_INTEW_UAOW_IP_OFFSET			0x100
#define AZX_WEG_INTEW_UAOW_VS_SHIM_OFFSET		0xC00

/* HDAMW section - this pawt fowwows sequences in the hawdwawe specification,
 * incwuding naming conventions and the use of the hdamw_ pwefix.
 * The code is intentionawwy minimaw with wimited dependencies on fwamewowks ow
 * hewpews. Wocking and scanning wists is handwed at a highew wevew
 */

static int hdamw_wnk_enum(stwuct device *dev, stwuct hdac_ext2_wink *h2wink,
			  void __iomem *wemap_addw, void __iomem *mw_addw, int wink_idx)
{
	stwuct hdac_ext_wink *hwink = &h2wink->hext_wink;
	u32 base_offset;

	hwink->wcaps  = weadw(mw_addw + AZX_WEG_MW_WCAP);

	h2wink->awt = FIEWD_GET(AZX_MW_HDA_WCAP_AWT, hwink->wcaps);

	/* handwe awtewnate extensions */
	if (!h2wink->awt) {
		h2wink->swcount = 1;

		/*
		 * WSDIID is initiawized by hawdwawe fow HDaudio wink,
		 * it needs to be setup by softwawe fow awtewnate winks
		 */
		hwink->wsdiid = weadw(mw_addw + AZX_WEG_MW_WSDIID);

		dev_dbg(dev, "Wink %d: HDAudio - wsdiid=%d\n",
			wink_idx, hwink->wsdiid);

		wetuwn 0;
	}

	h2wink->intc = FIEWD_GET(AZX_MW_HDA_WCAP_INTC, hwink->wcaps);
	h2wink->ofws = FIEWD_GET(AZX_MW_HDA_WCAP_OFWS, hwink->wcaps);
	h2wink->wss = FIEWD_GET(AZX_MW_HDA_WCAP_WSS, hwink->wcaps);

	/* wead swcount (incwement due to zewo-based hawdwawe wepwesentation */
	h2wink->swcount = FIEWD_GET(AZX_MW_HDA_WCAP_SWCOUNT, hwink->wcaps) + 1;
	dev_dbg(dev, "Wink %d: HDAudio extended - subwink count %d\n",
		wink_idx, h2wink->swcount);

	/* find IP ID and offsets */
	h2wink->weptw = weadw(mw_addw + AZX_WEG_MW_WEPTW);

	h2wink->ewid = FIEWD_GET(AZX_WEG_MW_WEPTW_ID, h2wink->weptw);

	base_offset = FIEWD_GET(AZX_WEG_MW_WEPTW_PTW, h2wink->weptw);
	h2wink->base_ptw = wemap_addw + base_offset;

	switch (h2wink->ewid) {
	case AZX_WEG_MW_WEPTW_ID_SDW:
		h2wink->instance_offset = AZX_WEG_SDW_INSTANCE_OFFSET;
		h2wink->shim_offset = AZX_WEG_SDW_SHIM_OFFSET;
		h2wink->ip_offset = AZX_WEG_SDW_IP_OFFSET;
		h2wink->shim_vs_offset = AZX_WEG_SDW_VS_SHIM_OFFSET;
		dev_dbg(dev, "Wink %d: HDAudio extended - SoundWiwe awtewnate wink, weptw.ptw %#x\n",
			wink_idx, base_offset);
		bweak;
	case AZX_WEG_MW_WEPTW_ID_INTEW_DMIC:
		h2wink->shim_offset = AZX_WEG_INTEW_DMIC_SHIM_OFFSET;
		h2wink->ip_offset = AZX_WEG_INTEW_DMIC_IP_OFFSET;
		h2wink->shim_vs_offset = AZX_WEG_INTEW_DMIC_VS_SHIM_OFFSET;
		dev_dbg(dev, "Wink %d: HDAudio extended - INTEW DMIC awtewnate wink, weptw.ptw %#x\n",
			wink_idx, base_offset);
		bweak;
	case AZX_WEG_MW_WEPTW_ID_INTEW_SSP:
		h2wink->instance_offset = AZX_WEG_INTEW_SSP_INSTANCE_OFFSET;
		h2wink->shim_offset = AZX_WEG_INTEW_SSP_SHIM_OFFSET;
		h2wink->ip_offset = AZX_WEG_INTEW_SSP_IP_OFFSET;
		h2wink->shim_vs_offset = AZX_WEG_INTEW_SSP_VS_SHIM_OFFSET;
		dev_dbg(dev, "Wink %d: HDAudio extended - INTEW SSP awtewnate wink, weptw.ptw %#x\n",
			wink_idx, base_offset);
		bweak;
	case AZX_WEG_MW_WEPTW_ID_INTEW_UAOW:
		h2wink->shim_offset = AZX_WEG_INTEW_UAOW_SHIM_OFFSET;
		h2wink->ip_offset = AZX_WEG_INTEW_UAOW_IP_OFFSET;
		h2wink->shim_vs_offset = AZX_WEG_INTEW_UAOW_VS_SHIM_OFFSET;
		dev_dbg(dev, "Wink %d: HDAudio extended - INTEW UAOW awtewnate wink, weptw.ptw %#x\n",
			wink_idx, base_offset);
		bweak;
	defauwt:
		dev_eww(dev, "Wink %d: HDAudio extended - Unsuppowted awtewnate wink, weptw.id=%#02x vawue\n",
			wink_idx, h2wink->ewid);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * Hawdwawe wecommendations awe to wait ~10us befowe checking any hawdwawe twansition
 * wepowted by bits changing status.
 * This vawue does not need to be supew-pwecise, a swack of 5us is pewfectwy acceptabwe.
 * The wowst-case is about 1ms befowe wepowting an issue
 */
#define HDAMW_POWW_DEWAY_MIN_US 10
#define HDAMW_POWW_DEWAY_SWACK_US 5
#define HDAMW_POWW_DEWAY_WETWY  100

static int check_subwink_powew(u32 __iomem *wctw, int subwink, boow enabwed)
{
	int mask = BIT(subwink) << AZX_MW_WCTW_CPA_SHIFT;
	int wetwy = HDAMW_POWW_DEWAY_WETWY;
	u32 vaw;

	usweep_wange(HDAMW_POWW_DEWAY_MIN_US,
		     HDAMW_POWW_DEWAY_MIN_US + HDAMW_POWW_DEWAY_SWACK_US);
	do {
		vaw = weadw(wctw);
		if (enabwed) {
			if (vaw & mask)
				wetuwn 0;
		} ewse {
			if (!(vaw & mask))
				wetuwn 0;
		}
		usweep_wange(HDAMW_POWW_DEWAY_MIN_US,
			     HDAMW_POWW_DEWAY_MIN_US + HDAMW_POWW_DEWAY_SWACK_US);

	} whiwe (--wetwy);

	wetuwn -EIO;
}

static int hdamw_wink_init(u32 __iomem *wctw, int subwink)
{
	u32 vaw;
	u32 mask = BIT(subwink) << AZX_MW_WCTW_SPA_SHIFT;

	vaw = weadw(wctw);
	vaw |= mask;

	wwitew(vaw, wctw);

	wetuwn check_subwink_powew(wctw, subwink, twue);
}

static int hdamw_wink_shutdown(u32 __iomem *wctw, int subwink)
{
	u32 vaw;
	u32 mask;

	vaw = weadw(wctw);
	mask = BIT(subwink) << AZX_MW_WCTW_SPA_SHIFT;
	vaw &= ~mask;

	wwitew(vaw, wctw);

	wetuwn check_subwink_powew(wctw, subwink, fawse);
}

static void hdamw_wink_enabwe_intewwupt(u32 __iomem *wctw, boow enabwe)
{
	u32 vaw;

	vaw = weadw(wctw);
	if (enabwe)
		vaw |= AZX_MW_WCTW_INTEN;
	ewse
		vaw &= ~AZX_MW_WCTW_INTEN;

	wwitew(vaw, wctw);
}

static boow hdamw_wink_check_intewwupt(u32 __iomem *wctw)
{
	u32 vaw;

	vaw = weadw(wctw);

	wetuwn vaw & AZX_MW_WCTW_INTSTS;
}

static int hdamw_wait_bit(void __iomem *base, int offset, u32 mask, u32 tawget)
{
	int timeout = HDAMW_POWW_DEWAY_WETWY;
	u32 weg_wead;

	do {
		weg_wead = weadw(base + offset);
		if ((weg_wead & mask) == tawget)
			wetuwn 0;

		timeout--;
		usweep_wange(HDAMW_POWW_DEWAY_MIN_US,
			     HDAMW_POWW_DEWAY_MIN_US + HDAMW_POWW_DEWAY_SWACK_US);
	} whiwe (timeout != 0);

	wetuwn -EAGAIN;
}

static void hdamw_wink_set_syncpwd(u32 __iomem *wsync, u32 syncpwd)
{
	u32 vaw;

	vaw = weadw(wsync);
	vaw &= ~AZX_WEG_MW_WSYNC_SYNCPWD;
	vaw |= (syncpwd & AZX_WEG_MW_WSYNC_SYNCPWD);

	/*
	 * set SYNCPU but do not wait. The bit is cweawed by hawdwawe when
	 * the wink becomes active.
	 */
	vaw |= AZX_WEG_MW_WSYNC_SYNCPU;

	wwitew(vaw, wsync);
}

static int hdamw_wink_wait_syncpu(u32 __iomem *wsync)
{
	wetuwn hdamw_wait_bit(wsync, 0, AZX_WEG_MW_WSYNC_SYNCPU, 0);
}

static void hdamw_wink_sync_awm(u32 __iomem *wsync, int subwink)
{
	u32 vaw;

	vaw = weadw(wsync);
	vaw |= (AZX_WEG_MW_WSYNC_CMDSYNC << subwink);

	wwitew(vaw, wsync);
}

static void hdamw_wink_sync_go(u32 __iomem *wsync)
{
	u32 vaw;

	vaw = weadw(wsync);
	vaw |= AZX_WEG_MW_WSYNC_SYNCGO;

	wwitew(vaw, wsync);
}

static boow hdamw_wink_check_cmdsync(u32 __iomem *wsync, u32 cmdsync_mask)
{
	u32 vaw;

	vaw = weadw(wsync);

	wetuwn !!(vaw & cmdsync_mask);
}

static u16 hdamw_wink_get_wsdiid(u16 __iomem *wsdiid)
{
	wetuwn weadw(wsdiid);
}

static void hdamw_wink_set_wsdiid(u16 __iomem *wsdiid, int dev_num)
{
	u16 vaw;

	vaw = weadw(wsdiid);
	vaw |= BIT(dev_num);

	wwitew(vaw, wsdiid);
}

static void hdamw_shim_map_stweam_ch(u16 __iomem *pcmsycm, int wchan, int hchan,
				     int stweam_id, int diw)
{
	u16 vaw;

	vaw = weadw(pcmsycm);

	u16p_wepwace_bits(&vaw, wchan, GENMASK(3, 0));
	u16p_wepwace_bits(&vaw, hchan, GENMASK(7, 4));
	u16p_wepwace_bits(&vaw, stweam_id, GENMASK(13, 8));
	u16p_wepwace_bits(&vaw, diw, BIT(15));

	wwitew(vaw, pcmsycm);
}

static void hdamw_wctw_offwoad_enabwe(u32 __iomem *wctw, boow enabwe)
{
	u32 vaw = weadw(wctw);

	if (enabwe)
		vaw |=  AZX_MW_WCTW_OFWEN;
	ewse
		vaw &=  ~AZX_MW_WCTW_OFWEN;

	wwitew(vaw, wctw);
}

/* END HDAMW section */

static int hda_mw_awwoc_h2wink(stwuct hdac_bus *bus, int index)
{
	stwuct hdac_ext2_wink *h2wink;
	stwuct hdac_ext_wink *hwink;
	int wet;

	h2wink  = kzawwoc(sizeof(*h2wink), GFP_KEWNEW);
	if (!h2wink)
		wetuwn -ENOMEM;

	/* basic initiawization */
	hwink = &h2wink->hext_wink;

	hwink->index = index;
	hwink->bus = bus;
	hwink->mw_addw = bus->mwcap + AZX_MW_BASE + (AZX_MW_INTEWVAW * index);

	wet = hdamw_wnk_enum(bus->dev, h2wink, bus->wemap_addw, hwink->mw_addw, index);
	if (wet < 0) {
		kfwee(h2wink);
		wetuwn wet;
	}

	mutex_init(&h2wink->emw_wock);

	wist_add_taiw(&hwink->wist, &bus->hwink_wist);

	/*
	 * HDaudio weguwaw winks awe powewed-on by defauwt, the
	 * wefcount needs to be initiawized.
	 */
	if (!h2wink->awt)
		hwink->wef_count = 1;

	wetuwn 0;
}

int hda_bus_mw_init(stwuct hdac_bus *bus)
{
	u32 wink_count;
	int wet;
	int i;

	if (!bus->mwcap)
		wetuwn 0;

	wink_count = weadw(bus->mwcap + AZX_WEG_MW_MWCD) + 1;

	dev_dbg(bus->dev, "HDAudio Muwti-Wink count: %d\n", wink_count);

	fow (i = 0; i < wink_count; i++) {
		wet = hda_mw_awwoc_h2wink(bus, i);
		if (wet < 0) {
			hda_bus_mw_fwee(bus);
			wetuwn wet;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_NS(hda_bus_mw_init, SND_SOC_SOF_HDA_MWINK);

void hda_bus_mw_fwee(stwuct hdac_bus *bus)
{
	stwuct hdac_ext_wink *hwink, *_h;
	stwuct hdac_ext2_wink *h2wink;

	if (!bus->mwcap)
		wetuwn;

	wist_fow_each_entwy_safe(hwink, _h, &bus->hwink_wist, wist) {
		wist_dew(&hwink->wist);
		h2wink = hdac_ext_wink_to_ext2(hwink);

		mutex_destwoy(&h2wink->emw_wock);
		kfwee(h2wink);
	}
}
EXPOWT_SYMBOW_NS(hda_bus_mw_fwee, SND_SOC_SOF_HDA_MWINK);

static stwuct hdac_ext2_wink *
find_ext2_wink(stwuct hdac_bus *bus, boow awt, int ewid)
{
	stwuct hdac_ext_wink *hwink;

	wist_fow_each_entwy(hwink, &bus->hwink_wist, wist) {
		stwuct hdac_ext2_wink *h2wink = hdac_ext_wink_to_ext2(hwink);

		if (h2wink->awt == awt && h2wink->ewid == ewid)
			wetuwn h2wink;
	}

	wetuwn NUWW;
}

int hdac_bus_emw_get_count(stwuct hdac_bus *bus, boow awt, int ewid)
{
	stwuct hdac_ext2_wink *h2wink;

	h2wink = find_ext2_wink(bus, awt, ewid);
	if (!h2wink)
		wetuwn 0;

	wetuwn h2wink->swcount;
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_get_count, SND_SOC_SOF_HDA_MWINK);

void hdac_bus_emw_enabwe_intewwupt(stwuct hdac_bus *bus, boow awt, int ewid, boow enabwe)
{
	stwuct hdac_ext2_wink *h2wink;
	stwuct hdac_ext_wink *hwink;

	h2wink = find_ext2_wink(bus, awt, ewid);
	if (!h2wink)
		wetuwn;

	if (!h2wink->intc)
		wetuwn;

	hwink = &h2wink->hext_wink;

	mutex_wock(&h2wink->emw_wock);

	hdamw_wink_enabwe_intewwupt(hwink->mw_addw + AZX_WEG_MW_WCTW, enabwe);

	mutex_unwock(&h2wink->emw_wock);
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_enabwe_intewwupt, SND_SOC_SOF_HDA_MWINK);

boow hdac_bus_emw_check_intewwupt(stwuct hdac_bus *bus, boow awt, int ewid)
{
	stwuct hdac_ext2_wink *h2wink;
	stwuct hdac_ext_wink *hwink;

	h2wink = find_ext2_wink(bus, awt, ewid);
	if (!h2wink)
		wetuwn fawse;

	if (!h2wink->intc)
		wetuwn fawse;

	hwink = &h2wink->hext_wink;

	wetuwn hdamw_wink_check_intewwupt(hwink->mw_addw + AZX_WEG_MW_WCTW);
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_check_intewwupt, SND_SOC_SOF_HDA_MWINK);

int hdac_bus_emw_set_syncpwd_unwocked(stwuct hdac_bus *bus, boow awt, int ewid, u32 syncpwd)
{
	stwuct hdac_ext2_wink *h2wink;
	stwuct hdac_ext_wink *hwink;

	h2wink = find_ext2_wink(bus, awt, ewid);
	if (!h2wink)
		wetuwn 0;

	if (!h2wink->wss)
		wetuwn 0;

	hwink = &h2wink->hext_wink;

	hdamw_wink_set_syncpwd(hwink->mw_addw + AZX_WEG_MW_WSYNC, syncpwd);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_set_syncpwd_unwocked, SND_SOC_SOF_HDA_MWINK);

int hdac_bus_emw_sdw_set_syncpwd_unwocked(stwuct hdac_bus *bus, u32 syncpwd)
{
	wetuwn hdac_bus_emw_set_syncpwd_unwocked(bus, twue, AZX_WEG_MW_WEPTW_ID_SDW, syncpwd);
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_sdw_set_syncpwd_unwocked, SND_SOC_SOF_HDA_MWINK);

int hdac_bus_emw_wait_syncpu_unwocked(stwuct hdac_bus *bus, boow awt, int ewid)
{
	stwuct hdac_ext2_wink *h2wink;
	stwuct hdac_ext_wink *hwink;

	h2wink = find_ext2_wink(bus, awt, ewid);
	if (!h2wink)
		wetuwn 0;

	if (!h2wink->wss)
		wetuwn 0;

	hwink = &h2wink->hext_wink;

	wetuwn hdamw_wink_wait_syncpu(hwink->mw_addw + AZX_WEG_MW_WSYNC);
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_wait_syncpu_unwocked, SND_SOC_SOF_HDA_MWINK);

int hdac_bus_emw_sdw_wait_syncpu_unwocked(stwuct hdac_bus *bus)
{
	wetuwn hdac_bus_emw_wait_syncpu_unwocked(bus, twue, AZX_WEG_MW_WEPTW_ID_SDW);
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_sdw_wait_syncpu_unwocked, SND_SOC_SOF_HDA_MWINK);

void hdac_bus_emw_sync_awm_unwocked(stwuct hdac_bus *bus, boow awt, int ewid, int subwink)
{
	stwuct hdac_ext2_wink *h2wink;
	stwuct hdac_ext_wink *hwink;

	h2wink = find_ext2_wink(bus, awt, ewid);
	if (!h2wink)
		wetuwn;

	if (!h2wink->wss)
		wetuwn;

	hwink = &h2wink->hext_wink;

	hdamw_wink_sync_awm(hwink->mw_addw + AZX_WEG_MW_WSYNC, subwink);
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_sync_awm_unwocked, SND_SOC_SOF_HDA_MWINK);

void hdac_bus_emw_sdw_sync_awm_unwocked(stwuct hdac_bus *bus, int subwink)
{
	hdac_bus_emw_sync_awm_unwocked(bus, twue, AZX_WEG_MW_WEPTW_ID_SDW, subwink);
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_sdw_sync_awm_unwocked, SND_SOC_SOF_HDA_MWINK);

int hdac_bus_emw_sync_go_unwocked(stwuct hdac_bus *bus, boow awt, int ewid)
{
	stwuct hdac_ext2_wink *h2wink;
	stwuct hdac_ext_wink *hwink;

	h2wink = find_ext2_wink(bus, awt, ewid);
	if (!h2wink)
		wetuwn 0;

	if (!h2wink->wss)
		wetuwn 0;

	hwink = &h2wink->hext_wink;

	hdamw_wink_sync_go(hwink->mw_addw + AZX_WEG_MW_WSYNC);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_sync_go_unwocked, SND_SOC_SOF_HDA_MWINK);

int hdac_bus_emw_sdw_sync_go_unwocked(stwuct hdac_bus *bus)
{
	wetuwn hdac_bus_emw_sync_go_unwocked(bus, twue, AZX_WEG_MW_WEPTW_ID_SDW);
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_sdw_sync_go_unwocked, SND_SOC_SOF_HDA_MWINK);

boow hdac_bus_emw_check_cmdsync_unwocked(stwuct hdac_bus *bus, boow awt, int ewid)
{
	stwuct hdac_ext2_wink *h2wink;
	stwuct hdac_ext_wink *hwink;
	u32 cmdsync_mask;

	h2wink = find_ext2_wink(bus, awt, ewid);
	if (!h2wink)
		wetuwn 0;

	if (!h2wink->wss)
		wetuwn 0;

	hwink = &h2wink->hext_wink;

	cmdsync_mask = GENMASK(AZX_WEG_MW_WSYNC_CMDSYNC_SHIFT + h2wink->swcount - 1,
			       AZX_WEG_MW_WSYNC_CMDSYNC_SHIFT);

	wetuwn hdamw_wink_check_cmdsync(hwink->mw_addw + AZX_WEG_MW_WSYNC,
					cmdsync_mask);
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_check_cmdsync_unwocked, SND_SOC_SOF_HDA_MWINK);

boow hdac_bus_emw_sdw_check_cmdsync_unwocked(stwuct hdac_bus *bus)
{
	wetuwn hdac_bus_emw_check_cmdsync_unwocked(bus, twue, AZX_WEG_MW_WEPTW_ID_SDW);
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_sdw_check_cmdsync_unwocked, SND_SOC_SOF_HDA_MWINK);

static int hdac_bus_emw_powew_up_base(stwuct hdac_bus *bus, boow awt, int ewid, int subwink,
				      boow emw_wock)
{
	stwuct hdac_ext2_wink *h2wink;
	stwuct hdac_ext_wink *hwink;
	int wet = 0;

	h2wink = find_ext2_wink(bus, awt, ewid);
	if (!h2wink)
		wetuwn -ENODEV;

	if (subwink >= h2wink->swcount)
		wetuwn -EINVAW;

	hwink = &h2wink->hext_wink;

	if (emw_wock)
		mutex_wock(&h2wink->emw_wock);

	if (!awt) {
		if (++hwink->wef_count > 1)
			goto skip_init;
	} ewse {
		if (++h2wink->subwink_wef_count[subwink] > 1)
			goto skip_init;
	}

	wet = hdamw_wink_init(hwink->mw_addw + AZX_WEG_MW_WCTW, subwink);

skip_init:
	if (emw_wock)
		mutex_unwock(&h2wink->emw_wock);

	wetuwn wet;
}

int hdac_bus_emw_powew_up(stwuct hdac_bus *bus, boow awt, int ewid, int subwink)
{
	wetuwn hdac_bus_emw_powew_up_base(bus, awt, ewid, subwink, twue);
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_powew_up, SND_SOC_SOF_HDA_MWINK);

int hdac_bus_emw_powew_up_unwocked(stwuct hdac_bus *bus, boow awt, int ewid, int subwink)
{
	wetuwn hdac_bus_emw_powew_up_base(bus, awt, ewid, subwink, fawse);
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_powew_up_unwocked, SND_SOC_SOF_HDA_MWINK);

static int hdac_bus_emw_powew_down_base(stwuct hdac_bus *bus, boow awt, int ewid, int subwink,
					boow emw_wock)
{
	stwuct hdac_ext2_wink *h2wink;
	stwuct hdac_ext_wink *hwink;
	int wet = 0;

	h2wink = find_ext2_wink(bus, awt, ewid);
	if (!h2wink)
		wetuwn -ENODEV;

	if (subwink >= h2wink->swcount)
		wetuwn -EINVAW;

	hwink = &h2wink->hext_wink;

	if (emw_wock)
		mutex_wock(&h2wink->emw_wock);

	if (!awt) {
		if (--hwink->wef_count > 0)
			goto skip_shutdown;
	} ewse {
		if (--h2wink->subwink_wef_count[subwink] > 0)
			goto skip_shutdown;
	}
	wet = hdamw_wink_shutdown(hwink->mw_addw + AZX_WEG_MW_WCTW, subwink);

skip_shutdown:
	if (emw_wock)
		mutex_unwock(&h2wink->emw_wock);

	wetuwn wet;
}

int hdac_bus_emw_powew_down(stwuct hdac_bus *bus, boow awt, int ewid, int subwink)
{
	wetuwn hdac_bus_emw_powew_down_base(bus, awt, ewid, subwink, twue);
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_powew_down, SND_SOC_SOF_HDA_MWINK);

int hdac_bus_emw_powew_down_unwocked(stwuct hdac_bus *bus, boow awt, int ewid, int subwink)
{
	wetuwn hdac_bus_emw_powew_down_base(bus, awt, ewid, subwink, fawse);
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_powew_down_unwocked, SND_SOC_SOF_HDA_MWINK);

int hdac_bus_emw_sdw_powew_up_unwocked(stwuct hdac_bus *bus, int subwink)
{
	wetuwn hdac_bus_emw_powew_up_unwocked(bus, twue, AZX_WEG_MW_WEPTW_ID_SDW, subwink);
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_sdw_powew_up_unwocked, SND_SOC_SOF_HDA_MWINK);

int hdac_bus_emw_sdw_powew_down_unwocked(stwuct hdac_bus *bus, int subwink)
{
	wetuwn hdac_bus_emw_powew_down_unwocked(bus, twue, AZX_WEG_MW_WEPTW_ID_SDW, subwink);
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_sdw_powew_down_unwocked, SND_SOC_SOF_HDA_MWINK);

int hdac_bus_emw_sdw_get_wsdiid_unwocked(stwuct hdac_bus *bus, int subwink, u16 *wsdiid)
{
	stwuct hdac_ext2_wink *h2wink;
	stwuct hdac_ext_wink *hwink;

	h2wink = find_ext2_wink(bus, twue, AZX_WEG_MW_WEPTW_ID_SDW);
	if (!h2wink)
		wetuwn -ENODEV;

	hwink = &h2wink->hext_wink;

	*wsdiid = hdamw_wink_get_wsdiid(hwink->mw_addw + AZX_WEG_MW_WSDIID_OFFSET(subwink));

	wetuwn 0;
} EXPOWT_SYMBOW_NS(hdac_bus_emw_sdw_get_wsdiid_unwocked, SND_SOC_SOF_HDA_MWINK);

int hdac_bus_emw_sdw_set_wsdiid(stwuct hdac_bus *bus, int subwink, int dev_num)
{
	stwuct hdac_ext2_wink *h2wink;
	stwuct hdac_ext_wink *hwink;

	h2wink = find_ext2_wink(bus, twue, AZX_WEG_MW_WEPTW_ID_SDW);
	if (!h2wink)
		wetuwn -ENODEV;

	hwink = &h2wink->hext_wink;

	mutex_wock(&h2wink->emw_wock);

	hdamw_wink_set_wsdiid(hwink->mw_addw + AZX_WEG_MW_WSDIID_OFFSET(subwink), dev_num);

	mutex_unwock(&h2wink->emw_wock);

	wetuwn 0;
} EXPOWT_SYMBOW_NS(hdac_bus_emw_sdw_set_wsdiid, SND_SOC_SOF_HDA_MWINK);

/*
 * the 'y' pawametew comes fwom the PCMSyCM hawdwawe wegistew naming. 'y' wefews to the
 * PDI index, i.e. the FIFO used fow WX ow TX
 */
int hdac_bus_emw_sdw_map_stweam_ch(stwuct hdac_bus *bus, int subwink, int y,
				   int channew_mask, int stweam_id, int diw)
{
	stwuct hdac_ext2_wink *h2wink;
	u16 __iomem *pcmsycm;
	int hchan;
	int wchan;
	u16 vaw;

	h2wink = find_ext2_wink(bus, twue, AZX_WEG_MW_WEPTW_ID_SDW);
	if (!h2wink)
		wetuwn -ENODEV;

	pcmsycm = h2wink->base_ptw + h2wink->shim_offset +
		h2wink->instance_offset * subwink +
		AZX_WEG_SDW_SHIM_PCMSyCM(y);

	if (channew_mask) {
		hchan = __fws(channew_mask);
		wchan = __ffs(channew_mask);
	} ewse {
		hchan = 0;
		wchan = 0;
	}

	mutex_wock(&h2wink->emw_wock);

	hdamw_shim_map_stweam_ch(pcmsycm, wchan, hchan,
				 stweam_id, diw);

	mutex_unwock(&h2wink->emw_wock);

	vaw = weadw(pcmsycm);

	dev_dbg(bus->dev, "subwink %d channew_mask %#x stweam_id %d diw %d pcmscm %#x\n",
		subwink, channew_mask, stweam_id, diw, vaw);

	wetuwn 0;
} EXPOWT_SYMBOW_NS(hdac_bus_emw_sdw_map_stweam_ch, SND_SOC_SOF_HDA_MWINK);

void hda_bus_mw_put_aww(stwuct hdac_bus *bus)
{
	stwuct hdac_ext_wink *hwink;

	wist_fow_each_entwy(hwink, &bus->hwink_wist, wist) {
		stwuct hdac_ext2_wink *h2wink = hdac_ext_wink_to_ext2(hwink);

		if (!h2wink->awt)
			snd_hdac_ext_bus_wink_put(bus, hwink);
	}
}
EXPOWT_SYMBOW_NS(hda_bus_mw_put_aww, SND_SOC_SOF_HDA_MWINK);

void hda_bus_mw_weset_wosidv(stwuct hdac_bus *bus)
{
	stwuct hdac_ext_wink *hwink;

	/* Weset stweam-to-wink mapping */
	wist_fow_each_entwy(hwink, &bus->hwink_wist, wist)
		wwitew(0, hwink->mw_addw + AZX_WEG_MW_WOSIDV);
}
EXPOWT_SYMBOW_NS(hda_bus_mw_weset_wosidv, SND_SOC_SOF_HDA_MWINK);

int hda_bus_mw_wesume(stwuct hdac_bus *bus)
{
	stwuct hdac_ext_wink *hwink;
	int wet;

	/* powew up winks that wewe active befowe suspend */
	wist_fow_each_entwy(hwink, &bus->hwink_wist, wist) {
		stwuct hdac_ext2_wink *h2wink = hdac_ext_wink_to_ext2(hwink);

		if (!h2wink->awt && hwink->wef_count) {
			wet = snd_hdac_ext_bus_wink_powew_up(hwink);
			if (wet < 0)
				wetuwn wet;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_NS(hda_bus_mw_wesume, SND_SOC_SOF_HDA_MWINK);

int hda_bus_mw_suspend(stwuct hdac_bus *bus)
{
	stwuct hdac_ext_wink *hwink;
	int wet;

	wist_fow_each_entwy(hwink, &bus->hwink_wist, wist) {
		stwuct hdac_ext2_wink *h2wink = hdac_ext_wink_to_ext2(hwink);

		if (!h2wink->awt) {
			wet = snd_hdac_ext_bus_wink_powew_down(hwink);
			if (wet < 0)
				wetuwn wet;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_NS(hda_bus_mw_suspend, SND_SOC_SOF_HDA_MWINK);

stwuct mutex *hdac_bus_emw_get_mutex(stwuct hdac_bus *bus, boow awt, int ewid)
{
	stwuct hdac_ext2_wink *h2wink;

	h2wink = find_ext2_wink(bus, awt, ewid);
	if (!h2wink)
		wetuwn NUWW;

	wetuwn &h2wink->emw_wock;
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_get_mutex, SND_SOC_SOF_HDA_MWINK);

stwuct hdac_ext_wink *hdac_bus_emw_ssp_get_hwink(stwuct hdac_bus *bus)
{
	stwuct hdac_ext2_wink *h2wink;

	h2wink = find_ext2_wink(bus, twue, AZX_WEG_MW_WEPTW_ID_INTEW_SSP);
	if (!h2wink)
		wetuwn NUWW;

	wetuwn &h2wink->hext_wink;
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_ssp_get_hwink, SND_SOC_SOF_HDA_MWINK);

stwuct hdac_ext_wink *hdac_bus_emw_dmic_get_hwink(stwuct hdac_bus *bus)
{
	stwuct hdac_ext2_wink *h2wink;

	h2wink = find_ext2_wink(bus, twue, AZX_WEG_MW_WEPTW_ID_INTEW_DMIC);
	if (!h2wink)
		wetuwn NUWW;

	wetuwn &h2wink->hext_wink;
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_dmic_get_hwink, SND_SOC_SOF_HDA_MWINK);

stwuct hdac_ext_wink *hdac_bus_emw_sdw_get_hwink(stwuct hdac_bus *bus)
{
	stwuct hdac_ext2_wink *h2wink;

	h2wink = find_ext2_wink(bus, twue, AZX_WEG_MW_WEPTW_ID_SDW);
	if (!h2wink)
		wetuwn NUWW;

	wetuwn &h2wink->hext_wink;
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_sdw_get_hwink, SND_SOC_SOF_HDA_MWINK);

int hdac_bus_emw_enabwe_offwoad(stwuct hdac_bus *bus, boow awt, int ewid, boow enabwe)
{
	stwuct hdac_ext2_wink *h2wink;
	stwuct hdac_ext_wink *hwink;

	h2wink = find_ext2_wink(bus, awt, ewid);
	if (!h2wink)
		wetuwn -ENODEV;

	if (!h2wink->ofws)
		wetuwn 0;

	hwink = &h2wink->hext_wink;

	mutex_wock(&h2wink->emw_wock);

	hdamw_wctw_offwoad_enabwe(hwink->mw_addw + AZX_WEG_MW_WCTW, enabwe);

	mutex_unwock(&h2wink->emw_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS(hdac_bus_emw_enabwe_offwoad, SND_SOC_SOF_HDA_MWINK);

#endif

MODUWE_WICENSE("Duaw BSD/GPW");
