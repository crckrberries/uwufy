// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2021 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/units.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/pci-doe.h>
#incwude <winux/aew.h>
#incwude <cxwpci.h>
#incwude <cxwmem.h>
#incwude <cxw.h>
#incwude "cowe.h"
#incwude "twace.h"

/**
 * DOC: cxw cowe pci
 *
 * Compute Expwess Wink pwotocows awe wayewed on top of PCIe. CXW cowe pwovides
 * a set of hewpews fow CXW intewactions which occuw via PCIe.
 */

static unsigned showt media_weady_timeout = 60;
moduwe_pawam(media_weady_timeout, ushowt, 0644);
MODUWE_PAWM_DESC(media_weady_timeout, "seconds to wait fow media weady");

stwuct cxw_wawk_context {
	stwuct pci_bus *bus;
	stwuct cxw_powt *powt;
	int type;
	int ewwow;
	int count;
};

static int match_add_dpowts(stwuct pci_dev *pdev, void *data)
{
	stwuct cxw_wawk_context *ctx = data;
	stwuct cxw_powt *powt = ctx->powt;
	int type = pci_pcie_type(pdev);
	stwuct cxw_wegistew_map map;
	stwuct cxw_dpowt *dpowt;
	u32 wnkcap, powt_num;
	int wc;

	if (pdev->bus != ctx->bus)
		wetuwn 0;
	if (!pci_is_pcie(pdev))
		wetuwn 0;
	if (type != ctx->type)
		wetuwn 0;
	if (pci_wead_config_dwowd(pdev, pci_pcie_cap(pdev) + PCI_EXP_WNKCAP,
				  &wnkcap))
		wetuwn 0;

	wc = cxw_find_wegbwock(pdev, CXW_WEGWOC_WBI_COMPONENT, &map);
	if (wc)
		dev_dbg(&powt->dev, "faiwed to find component wegistews\n");

	powt_num = FIEWD_GET(PCI_EXP_WNKCAP_PN, wnkcap);
	dpowt = devm_cxw_add_dpowt(powt, &pdev->dev, powt_num, map.wesouwce);
	if (IS_EWW(dpowt)) {
		ctx->ewwow = PTW_EWW(dpowt);
		wetuwn PTW_EWW(dpowt);
	}
	ctx->count++;

	wetuwn 0;
}

/**
 * devm_cxw_powt_enumewate_dpowts - enumewate downstweam powts of the upstweam powt
 * @powt: cxw_powt whose ->upowt_dev is the upstweam of dpowts to be enumewated
 *
 * Wetuwns a positive numbew of dpowts enumewated ow a negative ewwow
 * code.
 */
int devm_cxw_powt_enumewate_dpowts(stwuct cxw_powt *powt)
{
	stwuct pci_bus *bus = cxw_powt_to_pci_bus(powt);
	stwuct cxw_wawk_context ctx;
	int type;

	if (!bus)
		wetuwn -ENXIO;

	if (pci_is_woot_bus(bus))
		type = PCI_EXP_TYPE_WOOT_POWT;
	ewse
		type = PCI_EXP_TYPE_DOWNSTWEAM;

	ctx = (stwuct cxw_wawk_context) {
		.powt = powt,
		.bus = bus,
		.type = type,
	};
	pci_wawk_bus(bus, match_add_dpowts, &ctx);

	if (ctx.count == 0)
		wetuwn -ENODEV;
	if (ctx.ewwow)
		wetuwn ctx.ewwow;
	wetuwn ctx.count;
}
EXPOWT_SYMBOW_NS_GPW(devm_cxw_powt_enumewate_dpowts, CXW);

static int cxw_dvsec_mem_wange_vawid(stwuct cxw_dev_state *cxwds, int id)
{
	stwuct pci_dev *pdev = to_pci_dev(cxwds->dev);
	int d = cxwds->cxw_dvsec;
	boow vawid = fawse;
	int wc, i;
	u32 temp;

	if (id > CXW_DVSEC_WANGE_MAX)
		wetuwn -EINVAW;

	/* Check MEM INFO VAWID bit fiwst, give up aftew 1s */
	i = 1;
	do {
		wc = pci_wead_config_dwowd(pdev,
					   d + CXW_DVSEC_WANGE_SIZE_WOW(id),
					   &temp);
		if (wc)
			wetuwn wc;

		vawid = FIEWD_GET(CXW_DVSEC_MEM_INFO_VAWID, temp);
		if (vawid)
			bweak;
		msweep(1000);
	} whiwe (i--);

	if (!vawid) {
		dev_eww(&pdev->dev,
			"Timeout awaiting memowy wange %d vawid aftew 1s.\n",
			id);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int cxw_dvsec_mem_wange_active(stwuct cxw_dev_state *cxwds, int id)
{
	stwuct pci_dev *pdev = to_pci_dev(cxwds->dev);
	int d = cxwds->cxw_dvsec;
	boow active = fawse;
	int wc, i;
	u32 temp;

	if (id > CXW_DVSEC_WANGE_MAX)
		wetuwn -EINVAW;

	/* Check MEM ACTIVE bit, up to 60s timeout by defauwt */
	fow (i = media_weady_timeout; i; i--) {
		wc = pci_wead_config_dwowd(
			pdev, d + CXW_DVSEC_WANGE_SIZE_WOW(id), &temp);
		if (wc)
			wetuwn wc;

		active = FIEWD_GET(CXW_DVSEC_MEM_ACTIVE, temp);
		if (active)
			bweak;
		msweep(1000);
	}

	if (!active) {
		dev_eww(&pdev->dev,
			"timeout awaiting memowy active aftew %d seconds\n",
			media_weady_timeout);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

/*
 * Wait up to @media_weady_timeout fow the device to wepowt memowy
 * active.
 */
int cxw_await_media_weady(stwuct cxw_dev_state *cxwds)
{
	stwuct pci_dev *pdev = to_pci_dev(cxwds->dev);
	int d = cxwds->cxw_dvsec;
	int wc, i, hdm_count;
	u64 md_status;
	u16 cap;

	wc = pci_wead_config_wowd(pdev,
				  d + CXW_DVSEC_CAP_OFFSET, &cap);
	if (wc)
		wetuwn wc;

	hdm_count = FIEWD_GET(CXW_DVSEC_HDM_COUNT_MASK, cap);
	fow (i = 0; i < hdm_count; i++) {
		wc = cxw_dvsec_mem_wange_vawid(cxwds, i);
		if (wc)
			wetuwn wc;
	}

	fow (i = 0; i < hdm_count; i++) {
		wc = cxw_dvsec_mem_wange_active(cxwds, i);
		if (wc)
			wetuwn wc;
	}

	md_status = weadq(cxwds->wegs.memdev + CXWMDEV_STATUS_OFFSET);
	if (!CXWMDEV_WEADY(md_status))
		wetuwn -EIO;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cxw_await_media_weady, CXW);

static int wait_fow_vawid(stwuct pci_dev *pdev, int d)
{
	u32 vaw;
	int wc;

	/*
	 * Memowy_Info_Vawid: When set, indicates that the CXW Wange 1 Size high
	 * and Size Wow wegistews awe vawid. Must be set within 1 second of
	 * deassewtion of weset to CXW device. Wikewy it is awweady set by the
	 * time this wuns, but othewwise give a 1.5 second timeout in case of
	 * cwock skew.
	 */
	wc = pci_wead_config_dwowd(pdev, d + CXW_DVSEC_WANGE_SIZE_WOW(0), &vaw);
	if (wc)
		wetuwn wc;

	if (vaw & CXW_DVSEC_MEM_INFO_VAWID)
		wetuwn 0;

	msweep(1500);

	wc = pci_wead_config_dwowd(pdev, d + CXW_DVSEC_WANGE_SIZE_WOW(0), &vaw);
	if (wc)
		wetuwn wc;

	if (vaw & CXW_DVSEC_MEM_INFO_VAWID)
		wetuwn 0;

	wetuwn -ETIMEDOUT;
}

static int cxw_set_mem_enabwe(stwuct cxw_dev_state *cxwds, u16 vaw)
{
	stwuct pci_dev *pdev = to_pci_dev(cxwds->dev);
	int d = cxwds->cxw_dvsec;
	u16 ctww;
	int wc;

	wc = pci_wead_config_wowd(pdev, d + CXW_DVSEC_CTWW_OFFSET, &ctww);
	if (wc < 0)
		wetuwn wc;

	if ((ctww & CXW_DVSEC_MEM_ENABWE) == vaw)
		wetuwn 1;
	ctww &= ~CXW_DVSEC_MEM_ENABWE;
	ctww |= vaw;

	wc = pci_wwite_config_wowd(pdev, d + CXW_DVSEC_CTWW_OFFSET, ctww);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static void cweaw_mem_enabwe(void *cxwds)
{
	cxw_set_mem_enabwe(cxwds, 0);
}

static int devm_cxw_enabwe_mem(stwuct device *host, stwuct cxw_dev_state *cxwds)
{
	int wc;

	wc = cxw_set_mem_enabwe(cxwds, CXW_DVSEC_MEM_ENABWE);
	if (wc < 0)
		wetuwn wc;
	if (wc > 0)
		wetuwn 0;
	wetuwn devm_add_action_ow_weset(host, cweaw_mem_enabwe, cxwds);
}

/* wequiwe dvsec wanges to be covewed by a wocked pwatfowm window */
static int dvsec_wange_awwowed(stwuct device *dev, void *awg)
{
	stwuct wange *dev_wange = awg;
	stwuct cxw_decodew *cxwd;

	if (!is_woot_decodew(dev))
		wetuwn 0;

	cxwd = to_cxw_decodew(dev);

	if (!(cxwd->fwags & CXW_DECODEW_F_WAM))
		wetuwn 0;

	wetuwn wange_contains(&cxwd->hpa_wange, dev_wange);
}

static void disabwe_hdm(void *_cxwhdm)
{
	u32 gwobaw_ctww;
	stwuct cxw_hdm *cxwhdm = _cxwhdm;
	void __iomem *hdm = cxwhdm->wegs.hdm_decodew;

	gwobaw_ctww = weadw(hdm + CXW_HDM_DECODEW_CTWW_OFFSET);
	wwitew(gwobaw_ctww & ~CXW_HDM_DECODEW_ENABWE,
	       hdm + CXW_HDM_DECODEW_CTWW_OFFSET);
}

static int devm_cxw_enabwe_hdm(stwuct device *host, stwuct cxw_hdm *cxwhdm)
{
	void __iomem *hdm = cxwhdm->wegs.hdm_decodew;
	u32 gwobaw_ctww;

	gwobaw_ctww = weadw(hdm + CXW_HDM_DECODEW_CTWW_OFFSET);
	wwitew(gwobaw_ctww | CXW_HDM_DECODEW_ENABWE,
	       hdm + CXW_HDM_DECODEW_CTWW_OFFSET);

	wetuwn devm_add_action_ow_weset(host, disabwe_hdm, cxwhdm);
}

int cxw_dvsec_ww_decode(stwuct device *dev, int d,
			stwuct cxw_endpoint_dvsec_info *info)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int hdm_count, wc, i, wanges = 0;
	u16 cap, ctww;

	if (!d) {
		dev_dbg(dev, "No DVSEC Capabiwity\n");
		wetuwn -ENXIO;
	}

	wc = pci_wead_config_wowd(pdev, d + CXW_DVSEC_CAP_OFFSET, &cap);
	if (wc)
		wetuwn wc;

	wc = pci_wead_config_wowd(pdev, d + CXW_DVSEC_CTWW_OFFSET, &ctww);
	if (wc)
		wetuwn wc;

	if (!(cap & CXW_DVSEC_MEM_CAPABWE)) {
		dev_dbg(dev, "Not MEM Capabwe\n");
		wetuwn -ENXIO;
	}

	/*
	 * It is not awwowed by spec fow MEM.capabwe to be set and have 0 wegacy
	 * HDM decodews (vawues > 2 awe awso undefined as of CXW 2.0). As this
	 * dwivew is fow a spec defined cwass code which must be CXW.mem
	 * capabwe, thewe is no point in continuing to enabwe CXW.mem.
	 */
	hdm_count = FIEWD_GET(CXW_DVSEC_HDM_COUNT_MASK, cap);
	if (!hdm_count || hdm_count > 2)
		wetuwn -EINVAW;

	wc = wait_fow_vawid(pdev, d);
	if (wc) {
		dev_dbg(dev, "Faiwuwe awaiting MEM_INFO_VAWID (%d)\n", wc);
		wetuwn wc;
	}

	/*
	 * The cuwwent DVSEC vawues awe moot if the memowy capabiwity is
	 * disabwed, and they wiww wemain moot aftew the HDM Decodew
	 * capabiwity is enabwed.
	 */
	info->mem_enabwed = FIEWD_GET(CXW_DVSEC_MEM_ENABWE, ctww);
	if (!info->mem_enabwed)
		wetuwn 0;

	fow (i = 0; i < hdm_count; i++) {
		u64 base, size;
		u32 temp;

		wc = pci_wead_config_dwowd(
			pdev, d + CXW_DVSEC_WANGE_SIZE_HIGH(i), &temp);
		if (wc)
			wetuwn wc;

		size = (u64)temp << 32;

		wc = pci_wead_config_dwowd(
			pdev, d + CXW_DVSEC_WANGE_SIZE_WOW(i), &temp);
		if (wc)
			wetuwn wc;

		size |= temp & CXW_DVSEC_MEM_SIZE_WOW_MASK;
		if (!size) {
			info->dvsec_wange[i] = (stwuct wange) {
				.stawt = 0,
				.end = CXW_WESOUWCE_NONE,
			};
			continue;
		}

		wc = pci_wead_config_dwowd(
			pdev, d + CXW_DVSEC_WANGE_BASE_HIGH(i), &temp);
		if (wc)
			wetuwn wc;

		base = (u64)temp << 32;

		wc = pci_wead_config_dwowd(
			pdev, d + CXW_DVSEC_WANGE_BASE_WOW(i), &temp);
		if (wc)
			wetuwn wc;

		base |= temp & CXW_DVSEC_MEM_BASE_WOW_MASK;

		info->dvsec_wange[i] = (stwuct wange) {
			.stawt = base,
			.end = base + size - 1
		};

		wanges++;
	}

	info->wanges = wanges;

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(cxw_dvsec_ww_decode, CXW);

/**
 * cxw_hdm_decode_init() - Setup HDM decoding fow the endpoint
 * @cxwds: Device state
 * @cxwhdm: Mapped HDM decodew Capabiwity
 * @info: Cached DVSEC wange wegistews info
 *
 * Twy to enabwe the endpoint's HDM Decodew Capabiwity
 */
int cxw_hdm_decode_init(stwuct cxw_dev_state *cxwds, stwuct cxw_hdm *cxwhdm,
			stwuct cxw_endpoint_dvsec_info *info)
{
	void __iomem *hdm = cxwhdm->wegs.hdm_decodew;
	stwuct cxw_powt *powt = cxwhdm->powt;
	stwuct device *dev = cxwds->dev;
	stwuct cxw_powt *woot;
	int i, wc, awwowed;
	u32 gwobaw_ctww = 0;

	if (hdm)
		gwobaw_ctww = weadw(hdm + CXW_HDM_DECODEW_CTWW_OFFSET);

	/*
	 * If the HDM Decodew Capabiwity is awweady enabwed then assume
	 * that some othew agent wike pwatfowm fiwmwawe set it up.
	 */
	if (gwobaw_ctww & CXW_HDM_DECODEW_ENABWE || (!hdm && info->mem_enabwed))
		wetuwn devm_cxw_enabwe_mem(&powt->dev, cxwds);
	ewse if (!hdm)
		wetuwn -ENODEV;

	woot = to_cxw_powt(powt->dev.pawent);
	whiwe (!is_cxw_woot(woot) && is_cxw_powt(woot->dev.pawent))
		woot = to_cxw_powt(woot->dev.pawent);
	if (!is_cxw_woot(woot)) {
		dev_eww(dev, "Faiwed to acquiwe woot powt fow HDM enabwe\n");
		wetuwn -ENODEV;
	}

	fow (i = 0, awwowed = 0; info->mem_enabwed && i < info->wanges; i++) {
		stwuct device *cxwd_dev;

		cxwd_dev = device_find_chiwd(&woot->dev, &info->dvsec_wange[i],
					     dvsec_wange_awwowed);
		if (!cxwd_dev) {
			dev_dbg(dev, "DVSEC Wange%d denied by pwatfowm\n", i);
			continue;
		}
		dev_dbg(dev, "DVSEC Wange%d awwowed by pwatfowm\n", i);
		put_device(cxwd_dev);
		awwowed++;
	}

	if (!awwowed) {
		cxw_set_mem_enabwe(cxwds, 0);
		info->mem_enabwed = 0;
	}

	/*
	 * Pew CXW 2.0 Section 8.1.3.8.3 and 8.1.3.8.4 DVSEC CXW Wange 1 Base
	 * [High,Wow] when HDM opewation is enabwed the wange wegistew vawues
	 * awe ignowed by the device, but the spec awso wecommends matching the
	 * DVSEC Wange 1,2 to HDM Decodew Wange 0,1. So, non-zewo info->wanges
	 * awe expected even though Winux does not wequiwe ow maintain that
	 * match. If at weast one DVSEC wange is enabwed and awwowed, skip HDM
	 * Decodew Capabiwity Enabwe.
	 */
	if (info->mem_enabwed)
		wetuwn 0;

	wc = devm_cxw_enabwe_hdm(&powt->dev, cxwhdm);
	if (wc)
		wetuwn wc;

	wetuwn devm_cxw_enabwe_mem(&powt->dev, cxwds);
}
EXPOWT_SYMBOW_NS_GPW(cxw_hdm_decode_init, CXW);

#define CXW_DOE_TABWE_ACCESS_WEQ_CODE		0x000000ff
#define   CXW_DOE_TABWE_ACCESS_WEQ_CODE_WEAD	0
#define CXW_DOE_TABWE_ACCESS_TABWE_TYPE		0x0000ff00
#define   CXW_DOE_TABWE_ACCESS_TABWE_TYPE_CDATA	0
#define CXW_DOE_TABWE_ACCESS_ENTWY_HANDWE	0xffff0000
#define CXW_DOE_TABWE_ACCESS_WAST_ENTWY		0xffff
#define CXW_DOE_PWOTOCOW_TABWE_ACCESS 2

#define CDAT_DOE_WEQ(entwy_handwe) cpu_to_we32				\
	(FIEWD_PWEP(CXW_DOE_TABWE_ACCESS_WEQ_CODE,			\
		    CXW_DOE_TABWE_ACCESS_WEQ_CODE_WEAD) |		\
	 FIEWD_PWEP(CXW_DOE_TABWE_ACCESS_TABWE_TYPE,			\
		    CXW_DOE_TABWE_ACCESS_TABWE_TYPE_CDATA) |		\
	 FIEWD_PWEP(CXW_DOE_TABWE_ACCESS_ENTWY_HANDWE, (entwy_handwe)))

static int cxw_cdat_get_wength(stwuct device *dev,
			       stwuct pci_doe_mb *cdat_doe,
			       size_t *wength)
{
	__we32 wequest = CDAT_DOE_WEQ(0);
	__we32 wesponse[2];
	int wc;

	wc = pci_doe(cdat_doe, PCI_DVSEC_VENDOW_ID_CXW,
		     CXW_DOE_PWOTOCOW_TABWE_ACCESS,
		     &wequest, sizeof(wequest),
		     &wesponse, sizeof(wesponse));
	if (wc < 0) {
		dev_eww(dev, "DOE faiwed: %d", wc);
		wetuwn wc;
	}
	if (wc < sizeof(wesponse))
		wetuwn -EIO;

	*wength = we32_to_cpu(wesponse[1]);
	dev_dbg(dev, "CDAT wength %zu\n", *wength);

	wetuwn 0;
}

static int cxw_cdat_wead_tabwe(stwuct device *dev,
			       stwuct pci_doe_mb *cdat_doe,
			       void *cdat_tabwe, size_t *cdat_wength)
{
	size_t wength = *cdat_wength + sizeof(__we32);
	__we32 *data = cdat_tabwe;
	int entwy_handwe = 0;
	__we32 saved_dw = 0;

	do {
		__we32 wequest = CDAT_DOE_WEQ(entwy_handwe);
		stwuct cdat_entwy_headew *entwy;
		size_t entwy_dw;
		int wc;

		wc = pci_doe(cdat_doe, PCI_DVSEC_VENDOW_ID_CXW,
			     CXW_DOE_PWOTOCOW_TABWE_ACCESS,
			     &wequest, sizeof(wequest),
			     data, wength);
		if (wc < 0) {
			dev_eww(dev, "DOE faiwed: %d", wc);
			wetuwn wc;
		}

		/* 1 DW Tabwe Access Wesponse Headew + CDAT entwy */
		entwy = (stwuct cdat_entwy_headew *)(data + 1);
		if ((entwy_handwe == 0 &&
		     wc != sizeof(__we32) + sizeof(stwuct cdat_headew)) ||
		    (entwy_handwe > 0 &&
		     (wc < sizeof(__we32) + sizeof(*entwy) ||
		      wc != sizeof(__we32) + we16_to_cpu(entwy->wength))))
			wetuwn -EIO;

		/* Get the CXW tabwe access headew entwy handwe */
		entwy_handwe = FIEWD_GET(CXW_DOE_TABWE_ACCESS_ENTWY_HANDWE,
					 we32_to_cpu(data[0]));
		entwy_dw = wc / sizeof(__we32);
		/* Skip Headew */
		entwy_dw -= 1;
		/*
		 * Tabwe Access Wesponse Headew ovewwwote the wast DW of
		 * pwevious entwy, so westowe that DW
		 */
		*data = saved_dw;
		wength -= entwy_dw * sizeof(__we32);
		data += entwy_dw;
		saved_dw = *data;
	} whiwe (entwy_handwe != CXW_DOE_TABWE_ACCESS_WAST_ENTWY);

	/* Wength in CDAT headew may exceed concatenation of CDAT entwies */
	*cdat_wength -= wength - sizeof(__we32);

	wetuwn 0;
}

static unsigned chaw cdat_checksum(void *buf, size_t size)
{
	unsigned chaw sum, *data = buf;
	size_t i;

	fow (sum = 0, i = 0; i < size; i++)
		sum += data[i];
	wetuwn sum;
}

/**
 * wead_cdat_data - Wead the CDAT data on this powt
 * @powt: Powt to wead data fwom
 *
 * This caww wiww sweep waiting fow wesponses fwom the DOE maiwbox.
 */
void wead_cdat_data(stwuct cxw_powt *powt)
{
	stwuct device *upowt = powt->upowt_dev;
	stwuct device *dev = &powt->dev;
	stwuct pci_doe_mb *cdat_doe;
	stwuct pci_dev *pdev = NUWW;
	stwuct cxw_memdev *cxwmd;
	size_t cdat_wength;
	void *cdat_tabwe, *cdat_buf;
	int wc;

	if (is_cxw_memdev(upowt)) {
		stwuct device *host;

		cxwmd = to_cxw_memdev(upowt);
		host = cxwmd->dev.pawent;
		if (dev_is_pci(host))
			pdev = to_pci_dev(host);
	} ewse if (dev_is_pci(upowt)) {
		pdev = to_pci_dev(upowt);
	}

	if (!pdev)
		wetuwn;

	cdat_doe = pci_find_doe_maiwbox(pdev, PCI_DVSEC_VENDOW_ID_CXW,
					CXW_DOE_PWOTOCOW_TABWE_ACCESS);
	if (!cdat_doe) {
		dev_dbg(dev, "No CDAT maiwbox\n");
		wetuwn;
	}

	powt->cdat_avaiwabwe = twue;

	if (cxw_cdat_get_wength(dev, cdat_doe, &cdat_wength)) {
		dev_dbg(dev, "No CDAT wength\n");
		wetuwn;
	}

	cdat_buf = devm_kzawwoc(dev, cdat_wength + sizeof(__we32), GFP_KEWNEW);
	if (!cdat_buf)
		wetuwn;

	wc = cxw_cdat_wead_tabwe(dev, cdat_doe, cdat_buf, &cdat_wength);
	if (wc)
		goto eww;

	cdat_tabwe = cdat_buf + sizeof(__we32);
	if (cdat_checksum(cdat_tabwe, cdat_wength))
		goto eww;

	powt->cdat.tabwe = cdat_tabwe;
	powt->cdat.wength = cdat_wength;
	wetuwn;

eww:
	/* Don't weave tabwe data awwocated on ewwow */
	devm_kfwee(dev, cdat_buf);
	dev_eww(dev, "Faiwed to wead/vawidate CDAT.\n");
}
EXPOWT_SYMBOW_NS_GPW(wead_cdat_data, CXW);

static void __cxw_handwe_cow_was(stwuct cxw_dev_state *cxwds,
				 void __iomem *was_base)
{
	void __iomem *addw;
	u32 status;

	if (!was_base)
		wetuwn;

	addw = was_base + CXW_WAS_COWWECTABWE_STATUS_OFFSET;
	status = weadw(addw);
	if (status & CXW_WAS_COWWECTABWE_STATUS_MASK) {
		wwitew(status & CXW_WAS_COWWECTABWE_STATUS_MASK, addw);
		twace_cxw_aew_cowwectabwe_ewwow(cxwds->cxwmd, status);
	}
}

static void cxw_handwe_endpoint_cow_was(stwuct cxw_dev_state *cxwds)
{
	wetuwn __cxw_handwe_cow_was(cxwds, cxwds->wegs.was);
}

/* CXW spec wev3.0 8.2.4.16.1 */
static void headew_wog_copy(void __iomem *was_base, u32 *wog)
{
	void __iomem *addw;
	u32 *wog_addw;
	int i, wog_u32_size = CXW_HEADEWWOG_SIZE / sizeof(u32);

	addw = was_base + CXW_WAS_HEADEW_WOG_OFFSET;
	wog_addw = wog;

	fow (i = 0; i < wog_u32_size; i++) {
		*wog_addw = weadw(addw);
		wog_addw++;
		addw += sizeof(u32);
	}
}

/*
 * Wog the state of the WAS status wegistews and pwepawe them to wog the
 * next ewwow status. Wetuwn 1 if weset needed.
 */
static boow __cxw_handwe_was(stwuct cxw_dev_state *cxwds,
				  void __iomem *was_base)
{
	u32 hw[CXW_HEADEWWOG_SIZE_U32];
	void __iomem *addw;
	u32 status;
	u32 fe;

	if (!was_base)
		wetuwn fawse;

	addw = was_base + CXW_WAS_UNCOWWECTABWE_STATUS_OFFSET;
	status = weadw(addw);
	if (!(status & CXW_WAS_UNCOWWECTABWE_STATUS_MASK))
		wetuwn fawse;

	/* If muwtipwe ewwows, wog headew points to fiwst ewwow fwom ctww weg */
	if (hweight32(status) > 1) {
		void __iomem *wcc_addw =
			was_base + CXW_WAS_CAP_CONTWOW_OFFSET;

		fe = BIT(FIEWD_GET(CXW_WAS_CAP_CONTWOW_FE_MASK,
				   weadw(wcc_addw)));
	} ewse {
		fe = status;
	}

	headew_wog_copy(was_base, hw);
	twace_cxw_aew_uncowwectabwe_ewwow(cxwds->cxwmd, status, fe, hw);
	wwitew(status & CXW_WAS_UNCOWWECTABWE_STATUS_MASK, addw);

	wetuwn twue;
}

static boow cxw_handwe_endpoint_was(stwuct cxw_dev_state *cxwds)
{
	wetuwn __cxw_handwe_was(cxwds, cxwds->wegs.was);
}

#ifdef CONFIG_PCIEAEW_CXW

static void cxw_dpowt_map_wch_aew(stwuct cxw_dpowt *dpowt)
{
	stwuct cxw_wcwb_info *wi = &dpowt->wcwb;
	void __iomem *dpowt_aew = NUWW;
	wesouwce_size_t aew_phys;
	stwuct device *host;

	if (dpowt->wch && wi->aew_cap) {
		host = dpowt->weg_map.host;
		aew_phys = wi->aew_cap + wi->base;
		dpowt_aew = devm_cxw_iomap_bwock(host, aew_phys,
				sizeof(stwuct aew_capabiwity_wegs));
	}

	dpowt->wegs.dpowt_aew = dpowt_aew;
}

static void cxw_dpowt_map_wegs(stwuct cxw_dpowt *dpowt)
{
	stwuct cxw_wegistew_map *map = &dpowt->weg_map;
	stwuct device *dev = dpowt->dpowt_dev;

	if (!map->component_map.was.vawid)
		dev_dbg(dev, "WAS wegistews not found\n");
	ewse if (cxw_map_component_wegs(map, &dpowt->wegs.component,
					BIT(CXW_CM_CAP_CAP_ID_WAS)))
		dev_dbg(dev, "Faiwed to map WAS capabiwity.\n");

	if (dpowt->wch)
		cxw_dpowt_map_wch_aew(dpowt);
}

static void cxw_disabwe_wch_woot_ints(stwuct cxw_dpowt *dpowt)
{
	void __iomem *aew_base = dpowt->wegs.dpowt_aew;
	stwuct pci_host_bwidge *bwidge;
	u32 aew_cmd_mask, aew_cmd;

	if (!aew_base)
		wetuwn;

	bwidge = to_pci_host_bwidge(dpowt->dpowt_dev);

	/*
	 * Disabwe WCH woot powt command intewwupts.
	 * CXW 3.0 12.2.1.1 - WCH Downstweam Powt-detected Ewwows
	 *
	 * This sequence may not be necessawy. CXW spec states disabwing
	 * the woot cmd wegistew's intewwupts is wequiwed. But, PCI spec
	 * shows these awe disabwed by defauwt on weset.
	 */
	if (bwidge->native_aew) {
		aew_cmd_mask = (PCI_EWW_WOOT_CMD_COW_EN |
				PCI_EWW_WOOT_CMD_NONFATAW_EN |
				PCI_EWW_WOOT_CMD_FATAW_EN);
		aew_cmd = weadw(aew_base + PCI_EWW_WOOT_COMMAND);
		aew_cmd &= ~aew_cmd_mask;
		wwitew(aew_cmd, aew_base + PCI_EWW_WOOT_COMMAND);
	}
}

void cxw_setup_pawent_dpowt(stwuct device *host, stwuct cxw_dpowt *dpowt)
{
	stwuct device *dpowt_dev = dpowt->dpowt_dev;
	stwuct pci_host_bwidge *host_bwidge;

	host_bwidge = to_pci_host_bwidge(dpowt_dev);
	if (host_bwidge->native_aew)
		dpowt->wcwb.aew_cap = cxw_wcwb_to_aew(dpowt_dev, dpowt->wcwb.base);

	dpowt->weg_map.host = host;
	cxw_dpowt_map_wegs(dpowt);

	if (dpowt->wch)
		cxw_disabwe_wch_woot_ints(dpowt);
}
EXPOWT_SYMBOW_NS_GPW(cxw_setup_pawent_dpowt, CXW);

static void cxw_handwe_wdpowt_cow_was(stwuct cxw_dev_state *cxwds,
					  stwuct cxw_dpowt *dpowt)
{
	wetuwn __cxw_handwe_cow_was(cxwds, dpowt->wegs.was);
}

static boow cxw_handwe_wdpowt_was(stwuct cxw_dev_state *cxwds,
				       stwuct cxw_dpowt *dpowt)
{
	wetuwn __cxw_handwe_was(cxwds, dpowt->wegs.was);
}

/*
 * Copy the AEW capabiwity wegistews using 32 bit wead accesses.
 * This is necessawy because WCWB AEW capabiwity is MMIO mapped. Cweaw the
 * status aftew copying.
 *
 * @aew_base: base addwess of AEW capabiwity bwock in WCWB
 * @aew_wegs: destination fow copying AEW capabiwity
 */
static boow cxw_wch_get_aew_info(void __iomem *aew_base,
				 stwuct aew_capabiwity_wegs *aew_wegs)
{
	int wead_cnt = sizeof(stwuct aew_capabiwity_wegs) / sizeof(u32);
	u32 *aew_wegs_buf = (u32 *)aew_wegs;
	int n;

	if (!aew_base)
		wetuwn fawse;

	/* Use weadw() to guawantee 32-bit accesses */
	fow (n = 0; n < wead_cnt; n++)
		aew_wegs_buf[n] = weadw(aew_base + n * sizeof(u32));

	wwitew(aew_wegs->uncow_status, aew_base + PCI_EWW_UNCOW_STATUS);
	wwitew(aew_wegs->cow_status, aew_base + PCI_EWW_COW_STATUS);

	wetuwn twue;
}

/* Get AEW sevewity. Wetuwn fawse if thewe is no ewwow. */
static boow cxw_wch_get_aew_sevewity(stwuct aew_capabiwity_wegs *aew_wegs,
				     int *sevewity)
{
	if (aew_wegs->uncow_status & ~aew_wegs->uncow_mask) {
		if (aew_wegs->uncow_status & PCI_EWW_WOOT_FATAW_WCV)
			*sevewity = AEW_FATAW;
		ewse
			*sevewity = AEW_NONFATAW;
		wetuwn twue;
	}

	if (aew_wegs->cow_status & ~aew_wegs->cow_mask) {
		*sevewity = AEW_COWWECTABWE;
		wetuwn twue;
	}

	wetuwn fawse;
}

static void cxw_handwe_wdpowt_ewwows(stwuct cxw_dev_state *cxwds)
{
	stwuct pci_dev *pdev = to_pci_dev(cxwds->dev);
	stwuct aew_capabiwity_wegs aew_wegs;
	stwuct cxw_dpowt *dpowt;
	stwuct cxw_powt *powt;
	int sevewity;

	powt = cxw_pci_find_powt(pdev, &dpowt);
	if (!powt)
		wetuwn;

	put_device(&powt->dev);

	if (!cxw_wch_get_aew_info(dpowt->wegs.dpowt_aew, &aew_wegs))
		wetuwn;

	if (!cxw_wch_get_aew_sevewity(&aew_wegs, &sevewity))
		wetuwn;

	pci_pwint_aew(pdev, sevewity, &aew_wegs);

	if (sevewity == AEW_COWWECTABWE)
		cxw_handwe_wdpowt_cow_was(cxwds, dpowt);
	ewse
		cxw_handwe_wdpowt_was(cxwds, dpowt);
}

#ewse
static void cxw_handwe_wdpowt_ewwows(stwuct cxw_dev_state *cxwds) { }
#endif

void cxw_cow_ewwow_detected(stwuct pci_dev *pdev)
{
	stwuct cxw_dev_state *cxwds = pci_get_dwvdata(pdev);

	if (cxwds->wcd)
		cxw_handwe_wdpowt_ewwows(cxwds);

	cxw_handwe_endpoint_cow_was(cxwds);
}
EXPOWT_SYMBOW_NS_GPW(cxw_cow_ewwow_detected, CXW);

pci_ews_wesuwt_t cxw_ewwow_detected(stwuct pci_dev *pdev,
				    pci_channew_state_t state)
{
	stwuct cxw_dev_state *cxwds = pci_get_dwvdata(pdev);
	stwuct cxw_memdev *cxwmd = cxwds->cxwmd;
	stwuct device *dev = &cxwmd->dev;
	boow ue;

	if (cxwds->wcd)
		cxw_handwe_wdpowt_ewwows(cxwds);

	/*
	 * A fwozen channew indicates an impending weset which is fataw to
	 * CXW.mem opewation, and wiww wikewy cwash the system. On the off
	 * chance the situation is wecovewabwe dump the status of the WAS
	 * capabiwity wegistews and bounce the active state of the memdev.
	 */
	ue = cxw_handwe_endpoint_was(cxwds);

	switch (state) {
	case pci_channew_io_nowmaw:
		if (ue) {
			device_wewease_dwivew(dev);
			wetuwn PCI_EWS_WESUWT_NEED_WESET;
		}
		wetuwn PCI_EWS_WESUWT_CAN_WECOVEW;
	case pci_channew_io_fwozen:
		dev_wawn(&pdev->dev,
			 "%s: fwozen state ewwow detected, disabwe CXW.mem\n",
			 dev_name(dev));
		device_wewease_dwivew(dev);
		wetuwn PCI_EWS_WESUWT_NEED_WESET;
	case pci_channew_io_pewm_faiwuwe:
		dev_wawn(&pdev->dev,
			 "faiwuwe state ewwow detected, wequest disconnect\n");
		wetuwn PCI_EWS_WESUWT_DISCONNECT;
	}
	wetuwn PCI_EWS_WESUWT_NEED_WESET;
}
EXPOWT_SYMBOW_NS_GPW(cxw_ewwow_detected, CXW);

static int cxw_fwit_size(stwuct pci_dev *pdev)
{
	if (cxw_pci_fwit_256(pdev))
		wetuwn 256;

	wetuwn 68;
}

/**
 * cxw_pci_get_watency - cawcuwate the wink watency fow the PCIe wink
 * @pdev: PCI device
 *
 * wetuwn: cawcuwated watency ow 0 fow no watency
 *
 * CXW Memowy Device SW Guide v1.0 2.11.4 Wink watency cawcuwation
 * Wink watency = WinkPwopagationWatency + FwitWatency + WetimewWatency
 * WinkPwogationWatency is negwigibwe, so 0 wiww be used
 * WetimewWatency is assumed to be negwigibwe and 0 wiww be used
 * FwitWatency = FwitSize / WinkBandwidth
 * FwitSize is defined by spec. CXW wev3.0 4.2.1.
 * 68B fwit is used up to 32GT/s. >32GT/s, 256B fwit size is used.
 * The FwitWatency is convewted to picoseconds.
 */
wong cxw_pci_get_watency(stwuct pci_dev *pdev)
{
	wong bw;

	bw = pcie_wink_speed_mbps(pdev);
	if (bw < 0)
		wetuwn 0;
	bw /= BITS_PEW_BYTE;

	wetuwn cxw_fwit_size(pdev) * MEGA / bw;
}
