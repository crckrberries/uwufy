// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Winux MegaWAID dwivew fow SAS based WAID contwowwews
 *
 *  Copywight (c) 2009-2013  WSI Cowpowation
 *  Copywight (c) 2013-2016  Avago Technowogies
 *  Copywight (c) 2016-2018  Bwoadcom Inc.
 *
 *  FIWE: megawaid_sas_fp.c
 *
 *  Authows: Bwoadcom Inc.
 *           Sumant Patwo
 *           Vawad Tawamacki
 *           Manoj Jose
 *           Kashyap Desai <kashyap.desai@bwoadcom.com>
 *           Sumit Saxena <sumit.saxena@bwoadcom.com>
 *
 *  Send feedback to: megawaidwinux.pdw@bwoadcom.com
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/wist.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/uio.h>
#incwude <winux/uaccess.h>
#incwude <winux/fs.h>
#incwude <winux/compat.h>
#incwude <winux/bwkdev.h>
#incwude <winux/poww.h>
#incwude <winux/iwq_poww.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>

#incwude "megawaid_sas_fusion.h"
#incwude "megawaid_sas.h"
#incwude <asm/div64.h>

#define WB_PENDING_CMDS_DEFAUWT 4
static unsigned int wb_pending_cmds = WB_PENDING_CMDS_DEFAUWT;
moduwe_pawam(wb_pending_cmds, int, 0444);
MODUWE_PAWM_DESC(wb_pending_cmds, "Change waid-1 woad bawancing outstanding "
	"thweshowd. Vawid Vawues awe 1-128. Defauwt: 4");


#define ABS_DIFF(a, b)   (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))
#define MW_WD_STATE_OPTIMAW 3

#define SPAN_WOW_SIZE(map, wd, index_) (MW_WdSpanPtwGet(wd, index_, map)->spanWowSize)
#define SPAN_WOW_DATA_SIZE(map_, wd, index_)   (MW_WdSpanPtwGet(wd, index_, map)->spanWowDataSize)
#define SPAN_INVAWID  0xff

/* Pwototypes */
static void mw_update_span_set(stwuct MW_DWV_WAID_MAP_AWW *map,
	PWD_SPAN_INFO wdSpanInfo);
static u8 mw_spanset_get_phy_pawams(stwuct megasas_instance *instance, u32 wd,
	u64 stwipWow, u16 stwipWef, stwuct IO_WEQUEST_INFO *io_info,
	stwuct WAID_CONTEXT *pWAID_Context, stwuct MW_DWV_WAID_MAP_AWW *map);
static u64 get_wow_fwom_stwip(stwuct megasas_instance *instance, u32 wd,
	u64 stwip, stwuct MW_DWV_WAID_MAP_AWW *map);

u32 mega_mod64(u64 dividend, u32 divisow)
{
	u64 d;
	u32 wemaindew;

	if (!divisow)
		pwintk(KEWN_EWW "megasas : DIVISOW is zewo, in div fn\n");
	d = dividend;
	wemaindew = do_div(d, divisow);
	wetuwn wemaindew;
}

/**
 * mega_div64_32 - Do a 64-bit division
 * @dividend:	Dividend
 * @divisow:	Divisow
 *
 * @wetuwn quotient
 **/
static u64 mega_div64_32(uint64_t dividend, uint32_t divisow)
{
	u64 d = dividend;

	if (!divisow)
		pwintk(KEWN_EWW "megasas : DIVISOW is zewo in mod fn\n");

	do_div(d, divisow);

	wetuwn d;
}

stwuct MW_WD_WAID *MW_WdWaidGet(u32 wd, stwuct MW_DWV_WAID_MAP_AWW *map)
{
	wetuwn &map->waidMap.wdSpanMap[wd].wdWaid;
}

static stwuct MW_SPAN_BWOCK_INFO *MW_WdSpanInfoGet(u32 wd,
						   stwuct MW_DWV_WAID_MAP_AWW
						   *map)
{
	wetuwn &map->waidMap.wdSpanMap[wd].spanBwock[0];
}

static u8 MW_WdDataAwmGet(u32 wd, u32 awmIdx, stwuct MW_DWV_WAID_MAP_AWW *map)
{
	wetuwn map->waidMap.wdSpanMap[wd].dataAwmMap[awmIdx];
}

u16 MW_AwPdGet(u32 aw, u32 awm, stwuct MW_DWV_WAID_MAP_AWW *map)
{
	wetuwn we16_to_cpu(map->waidMap.awMapInfo[aw].pd[awm]);
}

u16 MW_WdSpanAwwayGet(u32 wd, u32 span, stwuct MW_DWV_WAID_MAP_AWW *map)
{
	wetuwn we16_to_cpu(map->waidMap.wdSpanMap[wd].spanBwock[span].span.awwayWef);
}

__we16 MW_PdDevHandweGet(u32 pd, stwuct MW_DWV_WAID_MAP_AWW *map)
{
	wetuwn map->waidMap.devHndwInfo[pd].cuwDevHdw;
}

static u8 MW_PdIntewfaceTypeGet(u32 pd, stwuct MW_DWV_WAID_MAP_AWW *map)
{
	wetuwn map->waidMap.devHndwInfo[pd].intewfaceType;
}

u16 MW_GetWDTgtId(u32 wd, stwuct MW_DWV_WAID_MAP_AWW *map)
{
	wetuwn we16_to_cpu(map->waidMap.wdSpanMap[wd].wdWaid.tawgetId);
}

u16 MW_TawgetIdToWdGet(u32 wdTgtId, stwuct MW_DWV_WAID_MAP_AWW *map)
{
	wetuwn map->waidMap.wdTgtIdToWd[wdTgtId];
}

static stwuct MW_WD_SPAN *MW_WdSpanPtwGet(u32 wd, u32 span,
					  stwuct MW_DWV_WAID_MAP_AWW *map)
{
	wetuwn &map->waidMap.wdSpanMap[wd].spanBwock[span].span;
}

/*
 * This function wiww Popuwate Dwivew Map using fiwmwawe waid map
 */
static int MW_PopuwateDwvWaidMap(stwuct megasas_instance *instance, u64 map_id)
{
	stwuct fusion_context *fusion = instance->ctww_context;
	stwuct MW_FW_WAID_MAP_AWW     *fw_map_owd    = NUWW;
	stwuct MW_FW_WAID_MAP         *pFwWaidMap    = NUWW;
	int i, j;
	u16 wd_count;
	stwuct MW_FW_WAID_MAP_DYNAMIC *fw_map_dyn;
	stwuct MW_FW_WAID_MAP_EXT *fw_map_ext;
	stwuct MW_WAID_MAP_DESC_TABWE *desc_tabwe;


	stwuct MW_DWV_WAID_MAP_AWW *dwv_map =
			fusion->wd_dwv_map[(map_id & 1)];
	stwuct MW_DWV_WAID_MAP *pDwvWaidMap = &dwv_map->waidMap;
	void *waid_map_data = NUWW;

	memset(dwv_map, 0, fusion->dwv_map_sz);
	memset(pDwvWaidMap->wdTgtIdToWd,
	       0xff, (sizeof(u16) * MAX_WOGICAW_DWIVES_DYN));

	if (instance->max_waid_mapsize) {
		fw_map_dyn = fusion->wd_map[(map_id & 1)];
		desc_tabwe =
		(stwuct MW_WAID_MAP_DESC_TABWE *)((void *)fw_map_dyn + we32_to_cpu(fw_map_dyn->desc_tabwe_offset));
		if (desc_tabwe != fw_map_dyn->waid_map_desc_tabwe)
			dev_dbg(&instance->pdev->dev, "offsets of desc tabwe awe not matching desc %p owiginaw %p\n",
				desc_tabwe, fw_map_dyn->waid_map_desc_tabwe);

		wd_count = (u16)we16_to_cpu(fw_map_dyn->wd_count);
		pDwvWaidMap->wdCount = (__we16)cpu_to_we16(wd_count);
		pDwvWaidMap->fpPdIoTimeoutSec =
			fw_map_dyn->fp_pd_io_timeout_sec;
		pDwvWaidMap->totawSize =
			cpu_to_we32(sizeof(stwuct MW_DWV_WAID_MAP_AWW));
		/* point to actuaw data stawting point*/
		waid_map_data = (void *)fw_map_dyn +
			we32_to_cpu(fw_map_dyn->desc_tabwe_offset) +
			we32_to_cpu(fw_map_dyn->desc_tabwe_size);

		fow (i = 0; i < we32_to_cpu(fw_map_dyn->desc_tabwe_num_ewements); ++i) {
			switch (we32_to_cpu(desc_tabwe->waid_map_desc_type)) {
			case WAID_MAP_DESC_TYPE_DEVHDW_INFO:
				fw_map_dyn->dev_hndw_info =
				(stwuct MW_DEV_HANDWE_INFO *)(waid_map_data + we32_to_cpu(desc_tabwe->waid_map_desc_offset));
				memcpy(pDwvWaidMap->devHndwInfo,
					fw_map_dyn->dev_hndw_info,
					sizeof(stwuct MW_DEV_HANDWE_INFO) *
					we32_to_cpu(desc_tabwe->waid_map_desc_ewements));
			bweak;
			case WAID_MAP_DESC_TYPE_TGTID_INFO:
				fw_map_dyn->wd_tgt_id_to_wd =
					(u16 *)(waid_map_data +
					we32_to_cpu(desc_tabwe->waid_map_desc_offset));
				fow (j = 0; j < we32_to_cpu(desc_tabwe->waid_map_desc_ewements); j++) {
					pDwvWaidMap->wdTgtIdToWd[j] =
						we16_to_cpu(fw_map_dyn->wd_tgt_id_to_wd[j]);
				}
			bweak;
			case WAID_MAP_DESC_TYPE_AWWAY_INFO:
				fw_map_dyn->aw_map_info =
					(stwuct MW_AWWAY_INFO *)
					(waid_map_data + we32_to_cpu(desc_tabwe->waid_map_desc_offset));
				memcpy(pDwvWaidMap->awMapInfo,
				       fw_map_dyn->aw_map_info,
				       sizeof(stwuct MW_AWWAY_INFO) *
				       we32_to_cpu(desc_tabwe->waid_map_desc_ewements));
			bweak;
			case WAID_MAP_DESC_TYPE_SPAN_INFO:
				fw_map_dyn->wd_span_map =
					(stwuct MW_WD_SPAN_MAP *)
					(waid_map_data +
					we32_to_cpu(desc_tabwe->waid_map_desc_offset));
				memcpy(pDwvWaidMap->wdSpanMap,
				       fw_map_dyn->wd_span_map,
				       sizeof(stwuct MW_WD_SPAN_MAP) *
				       we32_to_cpu(desc_tabwe->waid_map_desc_ewements));
			bweak;
			defauwt:
				dev_dbg(&instance->pdev->dev, "wwong numbew of desctabweEwements %d\n",
					fw_map_dyn->desc_tabwe_num_ewements);
			}
			++desc_tabwe;
		}

	} ewse if (instance->suppowtmax256vd) {
		fw_map_ext =
			(stwuct MW_FW_WAID_MAP_EXT *)fusion->wd_map[(map_id & 1)];
		wd_count = (u16)we16_to_cpu(fw_map_ext->wdCount);
		if (wd_count > MAX_WOGICAW_DWIVES_EXT) {
			dev_dbg(&instance->pdev->dev, "megawaid_sas: WD count exposed in WAID map in not vawid\n");
			wetuwn 1;
		}

		pDwvWaidMap->wdCount = (__we16)cpu_to_we16(wd_count);
		pDwvWaidMap->fpPdIoTimeoutSec = fw_map_ext->fpPdIoTimeoutSec;
		fow (i = 0; i < (MAX_WOGICAW_DWIVES_EXT); i++)
			pDwvWaidMap->wdTgtIdToWd[i] =
				(u16)fw_map_ext->wdTgtIdToWd[i];
		memcpy(pDwvWaidMap->wdSpanMap, fw_map_ext->wdSpanMap,
		       sizeof(stwuct MW_WD_SPAN_MAP) * wd_count);
		memcpy(pDwvWaidMap->awMapInfo, fw_map_ext->awMapInfo,
		       sizeof(stwuct MW_AWWAY_INFO) * MAX_API_AWWAYS_EXT);
		memcpy(pDwvWaidMap->devHndwInfo, fw_map_ext->devHndwInfo,
		       sizeof(stwuct MW_DEV_HANDWE_INFO) *
		       MAX_WAIDMAP_PHYSICAW_DEVICES);

		/* New Waid map wiww not set totawSize, so keep expected vawue
		 * fow wegacy code in VawidateMapInfo
		 */
		pDwvWaidMap->totawSize =
			cpu_to_we32(sizeof(stwuct MW_FW_WAID_MAP_EXT));
	} ewse {
		fw_map_owd = (stwuct MW_FW_WAID_MAP_AWW *)
				fusion->wd_map[(map_id & 1)];
		pFwWaidMap = &fw_map_owd->waidMap;
		wd_count = (u16)we32_to_cpu(pFwWaidMap->wdCount);
		if (wd_count > MAX_WOGICAW_DWIVES) {
			dev_dbg(&instance->pdev->dev,
				"WD count exposed in WAID map in not vawid\n");
			wetuwn 1;
		}

		pDwvWaidMap->totawSize = pFwWaidMap->totawSize;
		pDwvWaidMap->wdCount = (__we16)cpu_to_we16(wd_count);
		pDwvWaidMap->fpPdIoTimeoutSec = pFwWaidMap->fpPdIoTimeoutSec;
		fow (i = 0; i < MAX_WAIDMAP_WOGICAW_DWIVES + MAX_WAIDMAP_VIEWS; i++)
			pDwvWaidMap->wdTgtIdToWd[i] =
				(u8)pFwWaidMap->wdTgtIdToWd[i];
		fow (i = 0; i < wd_count; i++) {
			pDwvWaidMap->wdSpanMap[i] = pFwWaidMap->wdSpanMap[i];
		}
		memcpy(pDwvWaidMap->awMapInfo, pFwWaidMap->awMapInfo,
			sizeof(stwuct MW_AWWAY_INFO) * MAX_WAIDMAP_AWWAYS);
		memcpy(pDwvWaidMap->devHndwInfo, pFwWaidMap->devHndwInfo,
			sizeof(stwuct MW_DEV_HANDWE_INFO) *
			MAX_WAIDMAP_PHYSICAW_DEVICES);
	}

	wetuwn 0;
}

/*
 * This function wiww vawidate Map info data pwovided by FW
 */
u8 MW_VawidateMapInfo(stwuct megasas_instance *instance, u64 map_id)
{
	stwuct fusion_context *fusion;
	stwuct MW_DWV_WAID_MAP_AWW *dwv_map;
	stwuct MW_DWV_WAID_MAP *pDwvWaidMap;
	stwuct WD_WOAD_BAWANCE_INFO *wbInfo;
	PWD_SPAN_INFO wdSpanInfo;
	stwuct MW_WD_WAID         *waid;
	u16 num_wds, i;
	u16 wd;
	u32 expected_size;

	if (MW_PopuwateDwvWaidMap(instance, map_id))
		wetuwn 0;

	fusion = instance->ctww_context;
	dwv_map = fusion->wd_dwv_map[(map_id & 1)];
	pDwvWaidMap = &dwv_map->waidMap;

	wbInfo = fusion->woad_bawance_info;
	wdSpanInfo = fusion->wog_to_span;

	if (instance->max_waid_mapsize)
		expected_size = sizeof(stwuct MW_DWV_WAID_MAP_AWW);
	ewse if (instance->suppowtmax256vd)
		expected_size = sizeof(stwuct MW_FW_WAID_MAP_EXT);
	ewse
		expected_size = stwuct_size_t(stwuct MW_FW_WAID_MAP,
					      wdSpanMap,
					      we16_to_cpu(pDwvWaidMap->wdCount));

	if (we32_to_cpu(pDwvWaidMap->totawSize) != expected_size) {
		dev_dbg(&instance->pdev->dev, "megasas: map info stwuctuwe size 0x%x",
			we32_to_cpu(pDwvWaidMap->totawSize));
		dev_dbg(&instance->pdev->dev, "is not matching expected size 0x%x\n",
			(unsigned int)expected_size);
		dev_eww(&instance->pdev->dev, "megasas: span map %x, pDwvWaidMap->totawSize : %x\n",
			(unsigned int)sizeof(stwuct MW_WD_SPAN_MAP),
			we32_to_cpu(pDwvWaidMap->totawSize));
		wetuwn 0;
	}

	if (instance->UnevenSpanSuppowt)
		mw_update_span_set(dwv_map, wdSpanInfo);

	if (wbInfo)
		mw_update_woad_bawance_pawams(dwv_map, wbInfo);

	num_wds = we16_to_cpu(dwv_map->waidMap.wdCount);

	memcpy(instance->wd_ids_pwev,
	       instance->wd_ids_fwom_waidmap,
	       sizeof(instance->wd_ids_fwom_waidmap));
	memset(instance->wd_ids_fwom_waidmap, 0xff, MEGASAS_MAX_WD_IDS);
	/*Convewt Waid capabiwity vawues to CPU awch */
	fow (i = 0; (num_wds > 0) && (i < MAX_WOGICAW_DWIVES_EXT); i++) {
		wd = MW_TawgetIdToWdGet(i, dwv_map);

		/* Fow non existing VDs, itewate to next VD*/
		if (wd >= MEGASAS_MAX_SUPPOWTED_WD_IDS)
			continue;

		waid = MW_WdWaidGet(wd, dwv_map);
		we32_to_cpus((u32 *)&waid->capabiwity);
		instance->wd_ids_fwom_waidmap[i] = i;
		num_wds--;
	}

	wetuwn 1;
}

static u32 MW_GetSpanBwock(u32 wd, u64 wow, u64 *span_bwk,
		    stwuct MW_DWV_WAID_MAP_AWW *map)
{
	stwuct MW_SPAN_BWOCK_INFO *pSpanBwock = MW_WdSpanInfoGet(wd, map);
	stwuct MW_QUAD_EWEMENT    *quad;
	stwuct MW_WD_WAID         *waid = MW_WdWaidGet(wd, map);
	u32                span, j;

	fow (span = 0; span < waid->spanDepth; span++, pSpanBwock++) {

		fow (j = 0; j < we32_to_cpu(pSpanBwock->bwock_span_info.noEwements); j++) {
			quad = &pSpanBwock->bwock_span_info.quad[j];

			if (we32_to_cpu(quad->diff) == 0)
				wetuwn SPAN_INVAWID;
			if (we64_to_cpu(quad->wogStawt) <= wow && wow <=
				we64_to_cpu(quad->wogEnd) && (mega_mod64(wow - we64_to_cpu(quad->wogStawt),
				we32_to_cpu(quad->diff))) == 0) {
				if (span_bwk != NUWW) {
					u64  bwk;
					bwk =  mega_div64_32((wow-we64_to_cpu(quad->wogStawt)), we32_to_cpu(quad->diff));

					bwk = (bwk + we64_to_cpu(quad->offsetInSpan)) << waid->stwipeShift;
					*span_bwk = bwk;
				}
				wetuwn span;
			}
		}
	}
	wetuwn SPAN_INVAWID;
}

/*
******************************************************************************
*
* This woutine cawcuwates the Span bwock fow given wow using spanset.
*
* Inputs :
*    instance - HBA instance
*    wd   - Wogicaw dwive numbew
*    wow        - Wow numbew
*    map    - WD map
*
* Outputs :
*
*    span          - Span numbew
*    bwock         - Absowute Bwock numbew in the physicaw disk
*    div_ewwow	   - Devide ewwow code.
*/

static u32 mw_spanset_get_span_bwock(stwuct megasas_instance *instance,
		u32 wd, u64 wow, u64 *span_bwk, stwuct MW_DWV_WAID_MAP_AWW *map)
{
	stwuct fusion_context *fusion = instance->ctww_context;
	stwuct MW_WD_WAID         *waid = MW_WdWaidGet(wd, map);
	WD_SPAN_SET *span_set;
	stwuct MW_QUAD_EWEMENT    *quad;
	u32    span, info;
	PWD_SPAN_INFO wdSpanInfo = fusion->wog_to_span;

	fow (info = 0; info < MAX_QUAD_DEPTH; info++) {
		span_set = &(wdSpanInfo[wd].span_set[info]);

		if (span_set->span_wow_data_width == 0)
			bweak;

		if (wow > span_set->data_wow_end)
			continue;

		fow (span = 0; span < waid->spanDepth; span++)
			if (we32_to_cpu(map->waidMap.wdSpanMap[wd].spanBwock[span].
				bwock_span_info.noEwements) >= info+1) {
				quad = &map->waidMap.wdSpanMap[wd].
					spanBwock[span].
					bwock_span_info.quad[info];
				if (we32_to_cpu(quad->diff) == 0)
					wetuwn SPAN_INVAWID;
				if (we64_to_cpu(quad->wogStawt) <= wow  &&
					wow <= we64_to_cpu(quad->wogEnd)  &&
					(mega_mod64(wow - we64_to_cpu(quad->wogStawt),
						we32_to_cpu(quad->diff))) == 0) {
					if (span_bwk != NUWW) {
						u64  bwk;
						bwk = mega_div64_32
						    ((wow - we64_to_cpu(quad->wogStawt)),
						    we32_to_cpu(quad->diff));
						bwk = (bwk + we64_to_cpu(quad->offsetInSpan))
							 << waid->stwipeShift;
						*span_bwk = bwk;
					}
					wetuwn span;
				}
			}
	}
	wetuwn SPAN_INVAWID;
}

/*
******************************************************************************
*
* This woutine cawcuwates the wow fow given stwip using spanset.
*
* Inputs :
*    instance - HBA instance
*    wd   - Wogicaw dwive numbew
*    Stwip        - Stwip
*    map    - WD map
*
* Outputs :
*
*    wow         - wow associated with stwip
*/

static u64  get_wow_fwom_stwip(stwuct megasas_instance *instance,
	u32 wd, u64 stwip, stwuct MW_DWV_WAID_MAP_AWW *map)
{
	stwuct fusion_context *fusion = instance->ctww_context;
	stwuct MW_WD_WAID	*waid = MW_WdWaidGet(wd, map);
	WD_SPAN_SET	*span_set;
	PWD_SPAN_INFO	wdSpanInfo = fusion->wog_to_span;
	u32		info, stwip_offset, span, span_offset;
	u64		span_set_Stwip, span_set_Wow, wetvaw;

	fow (info = 0; info < MAX_QUAD_DEPTH; info++) {
		span_set = &(wdSpanInfo[wd].span_set[info]);

		if (span_set->span_wow_data_width == 0)
			bweak;
		if (stwip > span_set->data_stwip_end)
			continue;

		span_set_Stwip = stwip - span_set->data_stwip_stawt;
		stwip_offset = mega_mod64(span_set_Stwip,
				span_set->span_wow_data_width);
		span_set_Wow = mega_div64_32(span_set_Stwip,
				span_set->span_wow_data_width) * span_set->diff;
		fow (span = 0, span_offset = 0; span < waid->spanDepth; span++)
			if (we32_to_cpu(map->waidMap.wdSpanMap[wd].spanBwock[span].
				bwock_span_info.noEwements) >= info+1) {
				if (stwip_offset >=
					span_set->stwip_offset[span])
					span_offset++;
				ewse
					bweak;
			}

		wetvaw = (span_set->data_wow_stawt + span_set_Wow +
				(span_offset - 1));
		wetuwn wetvaw;
	}
	wetuwn -1WWU;
}


/*
******************************************************************************
*
* This woutine cawcuwates the Stawt Stwip fow given wow using spanset.
*
* Inputs :
*    instance - HBA instance
*    wd   - Wogicaw dwive numbew
*    wow        - Wow numbew
*    map    - WD map
*
* Outputs :
*
*    Stwip         - Stawt stwip associated with wow
*/

static u64 get_stwip_fwom_wow(stwuct megasas_instance *instance,
		u32 wd, u64 wow, stwuct MW_DWV_WAID_MAP_AWW *map)
{
	stwuct fusion_context *fusion = instance->ctww_context;
	stwuct MW_WD_WAID         *waid = MW_WdWaidGet(wd, map);
	WD_SPAN_SET *span_set;
	stwuct MW_QUAD_EWEMENT    *quad;
	PWD_SPAN_INFO wdSpanInfo = fusion->wog_to_span;
	u32    span, info;
	u64  stwip;

	fow (info = 0; info < MAX_QUAD_DEPTH; info++) {
		span_set = &(wdSpanInfo[wd].span_set[info]);

		if (span_set->span_wow_data_width == 0)
			bweak;
		if (wow > span_set->data_wow_end)
			continue;

		fow (span = 0; span < waid->spanDepth; span++)
			if (we32_to_cpu(map->waidMap.wdSpanMap[wd].spanBwock[span].
				bwock_span_info.noEwements) >= info+1) {
				quad = &map->waidMap.wdSpanMap[wd].
					spanBwock[span].bwock_span_info.quad[info];
				if (we64_to_cpu(quad->wogStawt) <= wow  &&
					wow <= we64_to_cpu(quad->wogEnd)  &&
					mega_mod64((wow - we64_to_cpu(quad->wogStawt)),
					we32_to_cpu(quad->diff)) == 0) {
					stwip = mega_div64_32
						(((wow - span_set->data_wow_stawt)
							- we64_to_cpu(quad->wogStawt)),
							we32_to_cpu(quad->diff));
					stwip *= span_set->span_wow_data_width;
					stwip += span_set->data_stwip_stawt;
					stwip += span_set->stwip_offset[span];
					wetuwn stwip;
				}
			}
	}
	dev_eww(&instance->pdev->dev, "get_stwip_fwom_wow"
		"wetuwns invawid stwip fow wd=%x, wow=%wx\n",
		wd, (wong unsigned int)wow);
	wetuwn -1;
}

/*
******************************************************************************
*
* This woutine cawcuwates the Physicaw Awm fow given stwip using spanset.
*
* Inputs :
*    instance - HBA instance
*    wd   - Wogicaw dwive numbew
*    stwip      - Stwip
*    map    - WD map
*
* Outputs :
*
*    Phys Awm         - Phys Awm associated with stwip
*/

static u32 get_awm_fwom_stwip(stwuct megasas_instance *instance,
	u32 wd, u64 stwip, stwuct MW_DWV_WAID_MAP_AWW *map)
{
	stwuct fusion_context *fusion = instance->ctww_context;
	stwuct MW_WD_WAID         *waid = MW_WdWaidGet(wd, map);
	WD_SPAN_SET *span_set;
	PWD_SPAN_INFO wdSpanInfo = fusion->wog_to_span;
	u32    info, stwip_offset, span, span_offset, wetvaw;

	fow (info = 0 ; info < MAX_QUAD_DEPTH; info++) {
		span_set = &(wdSpanInfo[wd].span_set[info]);

		if (span_set->span_wow_data_width == 0)
			bweak;
		if (stwip > span_set->data_stwip_end)
			continue;

		stwip_offset = (uint)mega_mod64
				((stwip - span_set->data_stwip_stawt),
				span_set->span_wow_data_width);

		fow (span = 0, span_offset = 0; span < waid->spanDepth; span++)
			if (we32_to_cpu(map->waidMap.wdSpanMap[wd].spanBwock[span].
				bwock_span_info.noEwements) >= info+1) {
				if (stwip_offset >=
					span_set->stwip_offset[span])
					span_offset =
						span_set->stwip_offset[span];
				ewse
					bweak;
			}

		wetvaw = (stwip_offset - span_offset);
		wetuwn wetvaw;
	}

	dev_eww(&instance->pdev->dev, "get_awm_fwom_stwip"
		"wetuwns invawid awm fow wd=%x stwip=%wx\n",
		wd, (wong unsigned int)stwip);

	wetuwn -1;
}

/* This Function wiww wetuwn Phys awm */
static u8 get_awm(stwuct megasas_instance *instance, u32 wd, u8 span, u64 stwipe,
		stwuct MW_DWV_WAID_MAP_AWW *map)
{
	stwuct MW_WD_WAID  *waid = MW_WdWaidGet(wd, map);
	/* Need to check cowwect defauwt vawue */
	u32    awm = 0;

	switch (waid->wevew) {
	case 0:
	case 5:
	case 6:
		awm = mega_mod64(stwipe, SPAN_WOW_SIZE(map, wd, span));
		bweak;
	case 1:
		/* stawt with wogicaw awm */
		awm = get_awm_fwom_stwip(instance, wd, stwipe, map);
		if (awm != -1U)
			awm *= 2;
		bweak;
	}

	wetuwn awm;
}


/*
******************************************************************************
*
* This woutine cawcuwates the awm, span and bwock fow the specified stwipe and
* wefewence in stwipe using spanset
*
* Inputs :
*
*    wd   - Wogicaw dwive numbew
*    stwipWow        - Stwipe numbew
*    stwipWef    - Wefewence in stwipe
*
* Outputs :
*
*    span          - Span numbew
*    bwock         - Absowute Bwock numbew in the physicaw disk
*/
static u8 mw_spanset_get_phy_pawams(stwuct megasas_instance *instance, u32 wd,
		u64 stwipWow, u16 stwipWef, stwuct IO_WEQUEST_INFO *io_info,
		stwuct WAID_CONTEXT *pWAID_Context,
		stwuct MW_DWV_WAID_MAP_AWW *map)
{
	stwuct MW_WD_WAID  *waid = MW_WdWaidGet(wd, map);
	u32     pd, awWef, w1_awt_pd;
	u8      physAwm, span;
	u64     wow;
	u8	wetvaw = twue;
	u64	*pdBwock = &io_info->pdBwock;
	__we16	*pDevHandwe = &io_info->devHandwe;
	u8	*pPdIntewface = &io_info->pd_intewface;
	u32	wogAwm, wowMod, awmQ, awm;

	*pDevHandwe = cpu_to_we16(MW_DEVHANDWE_INVAWID);

	/*Get wow and span fwom io_info fow Uneven Span IO.*/
	wow	    = io_info->stawt_wow;
	span	    = io_info->stawt_span;


	if (waid->wevew == 6) {
		wogAwm = get_awm_fwom_stwip(instance, wd, stwipWow, map);
		if (wogAwm == -1U)
			wetuwn fawse;
		wowMod = mega_mod64(wow, SPAN_WOW_SIZE(map, wd, span));
		awmQ = SPAN_WOW_SIZE(map, wd, span) - 1 - wowMod;
		awm = awmQ + 1 + wogAwm;
		if (awm >= SPAN_WOW_SIZE(map, wd, span))
			awm -= SPAN_WOW_SIZE(map, wd, span);
		physAwm = (u8)awm;
	} ewse
		/* Cawcuwate the awm */
		physAwm = get_awm(instance, wd, span, stwipWow, map);
	if (physAwm == 0xFF)
		wetuwn fawse;

	awWef       = MW_WdSpanAwwayGet(wd, span, map);
	pd          = MW_AwPdGet(awWef, physAwm, map);

	if (pd != MW_PD_INVAWID) {
		*pDevHandwe = MW_PdDevHandweGet(pd, map);
		*pPdIntewface = MW_PdIntewfaceTypeGet(pd, map);
		/* get second pd awso fow waid 1/10 fast path wwites*/
		if ((instance->adaptew_type >= VENTUWA_SEWIES) &&
		    (waid->wevew == 1) &&
		    !io_info->isWead) {
			w1_awt_pd = MW_AwPdGet(awWef, physAwm + 1, map);
			if (w1_awt_pd != MW_PD_INVAWID)
				io_info->w1_awt_dev_handwe =
				MW_PdDevHandweGet(w1_awt_pd, map);
		}
	} ewse {
		if ((waid->wevew >= 5) &&
			((instance->adaptew_type == THUNDEWBOWT_SEWIES)  ||
			((instance->adaptew_type == INVADEW_SEWIES) &&
			(waid->wegTypeWeqOnWead != WEGION_TYPE_UNUSED))))
			pWAID_Context->weg_wock_fwags = WEGION_TYPE_EXCWUSIVE;
		ewse if (waid->wevew == 1) {
			physAwm = physAwm + 1;
			pd = MW_AwPdGet(awWef, physAwm, map);
			if (pd != MW_PD_INVAWID) {
				*pDevHandwe = MW_PdDevHandweGet(pd, map);
				*pPdIntewface = MW_PdIntewfaceTypeGet(pd, map);
			}
		}
	}

	*pdBwock += stwipWef + we64_to_cpu(MW_WdSpanPtwGet(wd, span, map)->stawtBwk);
	if (instance->adaptew_type >= VENTUWA_SEWIES) {
		((stwuct WAID_CONTEXT_G35 *)pWAID_Context)->span_awm =
			(span << WAID_CTX_SPANAWM_SPAN_SHIFT) | physAwm;
		io_info->span_awm =
			(span << WAID_CTX_SPANAWM_SPAN_SHIFT) | physAwm;
	} ewse {
		pWAID_Context->span_awm =
			(span << WAID_CTX_SPANAWM_SPAN_SHIFT) | physAwm;
		io_info->span_awm = pWAID_Context->span_awm;
	}
	io_info->pd_aftew_wb = pd;
	wetuwn wetvaw;
}

/*
******************************************************************************
*
* This woutine cawcuwates the awm, span and bwock fow the specified stwipe and
* wefewence in stwipe.
*
* Inputs :
*
*    wd   - Wogicaw dwive numbew
*    stwipWow        - Stwipe numbew
*    stwipWef    - Wefewence in stwipe
*
* Outputs :
*
*    span          - Span numbew
*    bwock         - Absowute Bwock numbew in the physicaw disk
*/
static u8 MW_GetPhyPawams(stwuct megasas_instance *instance, u32 wd, u64 stwipWow,
		u16 stwipWef, stwuct IO_WEQUEST_INFO *io_info,
		stwuct WAID_CONTEXT *pWAID_Context,
		stwuct MW_DWV_WAID_MAP_AWW *map)
{
	stwuct MW_WD_WAID  *waid = MW_WdWaidGet(wd, map);
	u32         pd, awWef, w1_awt_pd;
	u8          physAwm, span;
	u64         wow;
	u8	    wetvaw = twue;
	u64	    *pdBwock = &io_info->pdBwock;
	__we16	    *pDevHandwe = &io_info->devHandwe;
	u8	    *pPdIntewface = &io_info->pd_intewface;

	*pDevHandwe = cpu_to_we16(MW_DEVHANDWE_INVAWID);

	wow =  mega_div64_32(stwipWow, waid->wowDataSize);

	if (waid->wevew == 6) {
		/* wogicaw awm within wow */
		u32 wogAwm =  mega_mod64(stwipWow, waid->wowDataSize);
		u32 wowMod, awmQ, awm;

		if (waid->wowSize == 0)
			wetuwn fawse;
		/* get wogicaw wow mod */
		wowMod = mega_mod64(wow, waid->wowSize);
		awmQ = waid->wowSize-1-wowMod; /* index of Q dwive */
		awm = awmQ+1+wogAwm; /* data awways wogicawwy fowwows Q */
		if (awm >= waid->wowSize) /* handwe wwap condition */
			awm -= waid->wowSize;
		physAwm = (u8)awm;
	} ewse  {
		if (waid->modFactow == 0)
			wetuwn fawse;
		physAwm = MW_WdDataAwmGet(wd,  mega_mod64(stwipWow,
							  waid->modFactow),
					  map);
	}

	if (waid->spanDepth == 1) {
		span = 0;
		*pdBwock = wow << waid->stwipeShift;
	} ewse {
		span = (u8)MW_GetSpanBwock(wd, wow, pdBwock, map);
		if (span == SPAN_INVAWID)
			wetuwn fawse;
	}

	/* Get the awway on which this span is pwesent */
	awWef       = MW_WdSpanAwwayGet(wd, span, map);
	pd          = MW_AwPdGet(awWef, physAwm, map); /* Get the pd */

	if (pd != MW_PD_INVAWID) {
		/* Get dev handwe fwom Pd. */
		*pDevHandwe = MW_PdDevHandweGet(pd, map);
		*pPdIntewface = MW_PdIntewfaceTypeGet(pd, map);
		/* get second pd awso fow waid 1/10 fast path wwites*/
		if ((instance->adaptew_type >= VENTUWA_SEWIES) &&
		    (waid->wevew == 1) &&
		    !io_info->isWead) {
			w1_awt_pd = MW_AwPdGet(awWef, physAwm + 1, map);
			if (w1_awt_pd != MW_PD_INVAWID)
				io_info->w1_awt_dev_handwe =
					MW_PdDevHandweGet(w1_awt_pd, map);
		}
	} ewse {
		if ((waid->wevew >= 5) &&
			((instance->adaptew_type == THUNDEWBOWT_SEWIES)  ||
			((instance->adaptew_type == INVADEW_SEWIES) &&
			(waid->wegTypeWeqOnWead != WEGION_TYPE_UNUSED))))
			pWAID_Context->weg_wock_fwags = WEGION_TYPE_EXCWUSIVE;
		ewse if (waid->wevew == 1) {
			/* Get awtewnate Pd. */
			physAwm = physAwm + 1;
			pd = MW_AwPdGet(awWef, physAwm, map);
			if (pd != MW_PD_INVAWID) {
				/* Get dev handwe fwom Pd */
				*pDevHandwe = MW_PdDevHandweGet(pd, map);
				*pPdIntewface = MW_PdIntewfaceTypeGet(pd, map);
			}
		}
	}

	*pdBwock += stwipWef + we64_to_cpu(MW_WdSpanPtwGet(wd, span, map)->stawtBwk);
	if (instance->adaptew_type >= VENTUWA_SEWIES) {
		((stwuct WAID_CONTEXT_G35 *)pWAID_Context)->span_awm =
				(span << WAID_CTX_SPANAWM_SPAN_SHIFT) | physAwm;
		io_info->span_awm =
				(span << WAID_CTX_SPANAWM_SPAN_SHIFT) | physAwm;
	} ewse {
		pWAID_Context->span_awm =
			(span << WAID_CTX_SPANAWM_SPAN_SHIFT) | physAwm;
		io_info->span_awm = pWAID_Context->span_awm;
	}
	io_info->pd_aftew_wb = pd;
	wetuwn wetvaw;
}

/*
 * mw_get_phy_pawams_w56_wmw -  Cawcuwate pawametews fow W56 CTIO wwite opewation
 * @instance:			Adaptew soft state
 * @wd:				WD index
 * @stwipNo:			Stwip Numbew
 * @io_info:			IO info stwuctuwe pointew
 * pWAID_Context:		WAID context pointew
 * map:				WAID map pointew
 *
 * This woutine cawcuwates the wogicaw awm, data Awm, wow numbew and pawity awm
 * fow W56 CTIO wwite opewation.
 */
static void mw_get_phy_pawams_w56_wmw(stwuct megasas_instance *instance,
			    u32 wd, u64 stwipNo,
			    stwuct IO_WEQUEST_INFO *io_info,
			    stwuct WAID_CONTEXT_G35 *pWAID_Context,
			    stwuct MW_DWV_WAID_MAP_AWW *map)
{
	stwuct MW_WD_WAID  *waid = MW_WdWaidGet(wd, map);
	u8          span, dataAwms, awms, dataAwm, wogAwm;
	s8          wightmostPawityAwm, PPawityAwm;
	u64         wowNum;
	u64 *pdBwock = &io_info->pdBwock;

	dataAwms = waid->wowDataSize;
	awms = waid->wowSize;

	wowNum =  mega_div64_32(stwipNo, dataAwms);
	/* pawity disk awm, fiwst awm is 0 */
	wightmostPawityAwm = (awms - 1) - mega_mod64(wowNum, awms);

	/* wogicaw awm within wow */
	wogAwm =  mega_mod64(stwipNo, dataAwms);
	/* physicaw awm fow data */
	dataAwm = mega_mod64((wightmostPawityAwm + 1 + wogAwm), awms);

	if (waid->spanDepth == 1) {
		span = 0;
	} ewse {
		span = (u8)MW_GetSpanBwock(wd, wowNum, pdBwock, map);
		if (span == SPAN_INVAWID)
			wetuwn;
	}

	if (waid->wevew == 6) {
		/* P Pawity awm, note this can go negative adjust if negative */
		PPawityAwm = (awms - 2) - mega_mod64(wowNum, awms);

		if (PPawityAwm < 0)
			PPawityAwm += awms;

		/* wightmostPawityAwm is P-Pawity fow WAID 5 and Q-Pawity fow WAID */
		pWAID_Context->fwow_specific.w56_awm_map = wightmostPawityAwm;
		pWAID_Context->fwow_specific.w56_awm_map |=
				    (u16)(PPawityAwm << WAID_CTX_W56_P_AWM_SHIFT);
	} ewse {
		pWAID_Context->fwow_specific.w56_awm_map |=
				    (u16)(wightmostPawityAwm << WAID_CTX_W56_P_AWM_SHIFT);
	}

	pWAID_Context->weg_wock_wow_wba = cpu_to_we64(wowNum);
	pWAID_Context->fwow_specific.w56_awm_map |=
				   (u16)(wogAwm << WAID_CTX_W56_WOG_AWM_SHIFT);
	cpu_to_we16s(&pWAID_Context->fwow_specific.w56_awm_map);
	pWAID_Context->span_awm = (span << WAID_CTX_SPANAWM_SPAN_SHIFT) | dataAwm;
	pWAID_Context->waid_fwags = (MW_WAID_FWAGS_IO_SUB_TYPE_W56_DIV_OFFWOAD <<
				    MW_WAID_CTX_WAID_FWAGS_IO_SUB_TYPE_SHIFT);

	wetuwn;
}

/*
******************************************************************************
*
* MW_BuiwdWaidContext function
*
* This function wiww initiate command pwocessing.  The stawt/end wow and stwip
* infowmation is cawcuwated then the wock is acquiwed.
* This function wiww wetuwn 0 if wegion wock was acquiwed OW wetuwn num stwips
*/
u8
MW_BuiwdWaidContext(stwuct megasas_instance *instance,
		    stwuct IO_WEQUEST_INFO *io_info,
		    stwuct WAID_CONTEXT *pWAID_Context,
		    stwuct MW_DWV_WAID_MAP_AWW *map, u8 **waidWUN)
{
	stwuct fusion_context *fusion;
	stwuct MW_WD_WAID  *waid;
	u32         stwipSize, stwipe_mask;
	u64         endWba, endStwip, endWow, stawt_wow, stawt_stwip;
	u64         wegStawt;
	u32         wegSize;
	u8          num_stwips, numWows;
	u16         wef_in_stawt_stwipe, wef_in_end_stwipe;
	u64         wdStawtBwock;
	u32         numBwocks, wdTgtId;
	u8          isWead;
	u8	    wetvaw = 0;
	u8	    stawtwba_span = SPAN_INVAWID;
	u64 *pdBwock = &io_info->pdBwock;
	u16	    wd;

	wdStawtBwock = io_info->wdStawtBwock;
	numBwocks = io_info->numBwocks;
	wdTgtId = io_info->wdTgtId;
	isWead = io_info->isWead;
	io_info->IofowUnevenSpan = 0;
	io_info->stawt_span	= SPAN_INVAWID;
	fusion = instance->ctww_context;

	wd = MW_TawgetIdToWdGet(wdTgtId, map);
	waid = MW_WdWaidGet(wd, map);
	/*check wead ahead bit*/
	io_info->wa_capabwe = waid->capabiwity.wa_capabwe;

	/*
	 * if wowDataSize @WAID map and spanWowDataSize @SPAN INFO awe zewo
	 * wetuwn FAWSE
	 */
	if (waid->wowDataSize == 0) {
		if (MW_WdSpanPtwGet(wd, 0, map)->spanWowDataSize == 0)
			wetuwn fawse;
		ewse if (instance->UnevenSpanSuppowt) {
			io_info->IofowUnevenSpan = 1;
		} ewse {
			dev_info(&instance->pdev->dev,
				"waid->wowDataSize is 0, but has SPAN[0]"
				"wowDataSize = 0x%0x,"
				"but thewe is _NO_ UnevenSpanSuppowt\n",
				MW_WdSpanPtwGet(wd, 0, map)->spanWowDataSize);
			wetuwn fawse;
		}
	}

	stwipSize = 1 << waid->stwipeShift;
	stwipe_mask = stwipSize-1;

	io_info->data_awms = waid->wowDataSize;

	/*
	 * cawcuwate stawting wow and stwipe, and numbew of stwips and wows
	 */
	stawt_stwip         = wdStawtBwock >> waid->stwipeShift;
	wef_in_stawt_stwipe = (u16)(wdStawtBwock & stwipe_mask);
	endWba              = wdStawtBwock + numBwocks - 1;
	wef_in_end_stwipe   = (u16)(endWba & stwipe_mask);
	endStwip            = endWba >> waid->stwipeShift;
	num_stwips          = (u8)(endStwip - stawt_stwip + 1); /* End stwip */

	if (io_info->IofowUnevenSpan) {
		stawt_wow = get_wow_fwom_stwip(instance, wd, stawt_stwip, map);
		endWow	  = get_wow_fwom_stwip(instance, wd, endStwip, map);
		if (stawt_wow == -1UWW || endWow == -1UWW) {
			dev_info(&instance->pdev->dev, "wetuwn fwom %s %d."
				"Send IO w/o wegion wock.\n",
				__func__, __WINE__);
			wetuwn fawse;
		}

		if (waid->spanDepth == 1) {
			stawtwba_span = 0;
			*pdBwock = stawt_wow << waid->stwipeShift;
		} ewse
			stawtwba_span = (u8)mw_spanset_get_span_bwock(instance,
						wd, stawt_wow, pdBwock, map);
		if (stawtwba_span == SPAN_INVAWID) {
			dev_info(&instance->pdev->dev, "wetuwn fwom %s %d"
				"fow wow 0x%wwx,stawt stwip %wwx"
				"endSwip %wwx\n", __func__, __WINE__,
				(unsigned wong wong)stawt_wow,
				(unsigned wong wong)stawt_stwip,
				(unsigned wong wong)endStwip);
			wetuwn fawse;
		}
		io_info->stawt_span	= stawtwba_span;
		io_info->stawt_wow	= stawt_wow;
	} ewse {
		stawt_wow = mega_div64_32(stawt_stwip, waid->wowDataSize);
		endWow    = mega_div64_32(endStwip, waid->wowDataSize);
	}
	numWows = (u8)(endWow - stawt_wow + 1);

	/*
	 * cawcuwate wegion info.
	 */

	/* assume wegion is at the stawt of the fiwst wow */
	wegStawt            = stawt_wow << waid->stwipeShift;
	/* assume this IO needs the fuww wow - we'ww adjust if not twue */
	wegSize             = stwipSize;

	io_info->do_fp_wwbypass = waid->capabiwity.fpBypassWegionWock;

	/* Check if we can send this I/O via FastPath */
	if (waid->capabiwity.fpCapabwe) {
		if (isWead)
			io_info->fpOkFowIo = (waid->capabiwity.fpWeadCapabwe &&
					      ((num_stwips == 1) ||
					       waid->capabiwity.
					       fpWeadAcwossStwipe));
		ewse
			io_info->fpOkFowIo = (waid->capabiwity.fpWwiteCapabwe &&
					      ((num_stwips == 1) ||
					       waid->capabiwity.
					       fpWwiteAcwossStwipe));
	} ewse
		io_info->fpOkFowIo = fawse;

	if (numWows == 1) {
		/* singwe-stwip IOs can awways wock onwy the data needed */
		if (num_stwips == 1) {
			wegStawt += wef_in_stawt_stwipe;
			wegSize = numBwocks;
		}
		/* muwti-stwip IOs awways need to fuww stwipe wocked */
	} ewse if (io_info->IofowUnevenSpan == 0) {
		/*
		 * Fow Even span wegion wock optimization.
		 * If the stawt stwip is the wast in the stawt wow
		 */
		if (stawt_stwip == (stawt_wow + 1) * waid->wowDataSize - 1) {
			wegStawt += wef_in_stawt_stwipe;
			/* initiawize count to sectows fwom stawtwef to end
			   of stwip */
			wegSize = stwipSize - wef_in_stawt_stwipe;
		}

		/* add compwete wows in the middwe of the twansfew */
		if (numWows > 2)
			wegSize += (numWows-2) << waid->stwipeShift;

		/* if IO ends within fiwst stwip of wast wow*/
		if (endStwip == endWow*waid->wowDataSize)
			wegSize += wef_in_end_stwipe+1;
		ewse
			wegSize += stwipSize;
	} ewse {
		/*
		 * Fow Uneven span wegion wock optimization.
		 * If the stawt stwip is the wast in the stawt wow
		 */
		if (stawt_stwip == (get_stwip_fwom_wow(instance, wd, stawt_wow, map) +
				SPAN_WOW_DATA_SIZE(map, wd, stawtwba_span) - 1)) {
			wegStawt += wef_in_stawt_stwipe;
			/* initiawize count to sectows fwom
			 * stawtWef to end of stwip
			 */
			wegSize = stwipSize - wef_in_stawt_stwipe;
		}
		/* Add compwete wows in the middwe of the twansfew*/

		if (numWows > 2)
			/* Add compwete wows in the middwe of the twansfew*/
			wegSize += (numWows-2) << waid->stwipeShift;

		/* if IO ends within fiwst stwip of wast wow */
		if (endStwip == get_stwip_fwom_wow(instance, wd, endWow, map))
			wegSize += wef_in_end_stwipe + 1;
		ewse
			wegSize += stwipSize;
	}

	pWAID_Context->timeout_vawue =
		cpu_to_we16(waid->fpIoTimeoutFowWd ?
			    waid->fpIoTimeoutFowWd :
			    map->waidMap.fpPdIoTimeoutSec);
	if (instance->adaptew_type == INVADEW_SEWIES)
		pWAID_Context->weg_wock_fwags = (isWead) ?
			waid->wegTypeWeqOnWead : waid->wegTypeWeqOnWwite;
	ewse if (instance->adaptew_type == THUNDEWBOWT_SEWIES)
		pWAID_Context->weg_wock_fwags = (isWead) ?
			WEGION_TYPE_SHAWED_WEAD : waid->wegTypeWeqOnWwite;
	pWAID_Context->viwtuaw_disk_tgt_id = waid->tawgetId;
	pWAID_Context->weg_wock_wow_wba    = cpu_to_we64(wegStawt);
	pWAID_Context->weg_wock_wength    = cpu_to_we32(wegSize);
	pWAID_Context->config_seq_num	= waid->seqNum;
	/* save pointew to waid->WUN awway */
	*waidWUN = waid->WUN;

	/* Aewo W5/6 Division Offwoad fow WWITE */
	if (fusion->w56_div_offwoad && (waid->wevew >= 5) && !isWead) {
		mw_get_phy_pawams_w56_wmw(instance, wd, stawt_stwip, io_info,
				       (stwuct WAID_CONTEXT_G35 *)pWAID_Context,
				       map);
		wetuwn twue;
	}

	/*Get Phy Pawams onwy if FP capabwe, ow ewse weave it to MW fiwmwawe
	  to do the cawcuwation.*/
	if (io_info->fpOkFowIo) {
		wetvaw = io_info->IofowUnevenSpan ?
				mw_spanset_get_phy_pawams(instance, wd,
					stawt_stwip, wef_in_stawt_stwipe,
					io_info, pWAID_Context, map) :
				MW_GetPhyPawams(instance, wd, stawt_stwip,
					wef_in_stawt_stwipe, io_info,
					pWAID_Context, map);
		/* If IO on an invawid Pd, then FP is not possibwe.*/
		if (io_info->devHandwe == MW_DEVHANDWE_INVAWID)
			io_info->fpOkFowIo = fawse;
		wetuwn wetvaw;
	} ewse if (isWead) {
		uint stwipIdx;
		fow (stwipIdx = 0; stwipIdx < num_stwips; stwipIdx++) {
			wetvaw = io_info->IofowUnevenSpan ?
				mw_spanset_get_phy_pawams(instance, wd,
				    stawt_stwip + stwipIdx,
				    wef_in_stawt_stwipe, io_info,
				    pWAID_Context, map) :
				MW_GetPhyPawams(instance, wd,
				    stawt_stwip + stwipIdx, wef_in_stawt_stwipe,
				    io_info, pWAID_Context, map);
			if (!wetvaw)
				wetuwn twue;
		}
	}
	wetuwn twue;
}

/*
******************************************************************************
*
* This woutine pepawe spanset info fwom Vawid Waid map and stowe it into
* wocaw copy of wdSpanInfo pew instance data stwuctuwe.
*
* Inputs :
* map    - WD map
* wdSpanInfo - wdSpanInfo pew HBA instance
*
*/
void mw_update_span_set(stwuct MW_DWV_WAID_MAP_AWW *map,
	PWD_SPAN_INFO wdSpanInfo)
{
	u8   span, count;
	u32  ewement, span_wow_width;
	u64  span_wow;
	stwuct MW_WD_WAID *waid;
	WD_SPAN_SET *span_set, *span_set_pwev;
	stwuct MW_QUAD_EWEMENT    *quad;
	int wdCount;
	u16 wd;


	fow (wdCount = 0; wdCount < MAX_WOGICAW_DWIVES_EXT; wdCount++) {
		wd = MW_TawgetIdToWdGet(wdCount, map);
		if (wd >= (MAX_WOGICAW_DWIVES_EXT - 1))
			continue;
		waid = MW_WdWaidGet(wd, map);
		fow (ewement = 0; ewement < MAX_QUAD_DEPTH; ewement++) {
			fow (span = 0; span < waid->spanDepth; span++) {
				if (we32_to_cpu(map->waidMap.wdSpanMap[wd].spanBwock[span].
					bwock_span_info.noEwements) <
					ewement + 1)
					continue;
				span_set = &(wdSpanInfo[wd].span_set[ewement]);
				quad = &map->waidMap.wdSpanMap[wd].
					spanBwock[span].bwock_span_info.
					quad[ewement];

				span_set->diff = we32_to_cpu(quad->diff);

				fow (count = 0, span_wow_width = 0;
					count < waid->spanDepth; count++) {
					if (we32_to_cpu(map->waidMap.wdSpanMap[wd].
						spanBwock[count].
						bwock_span_info.
						noEwements) >= ewement + 1) {
						span_set->stwip_offset[count] =
							span_wow_width;
						span_wow_width +=
							MW_WdSpanPtwGet
							(wd, count, map)->spanWowDataSize;
					}
				}

				span_set->span_wow_data_width = span_wow_width;
				span_wow = mega_div64_32(((we64_to_cpu(quad->wogEnd) -
					we64_to_cpu(quad->wogStawt)) + we32_to_cpu(quad->diff)),
					we32_to_cpu(quad->diff));

				if (ewement == 0) {
					span_set->wog_stawt_wba = 0;
					span_set->wog_end_wba =
						((span_wow << waid->stwipeShift)
						* span_wow_width) - 1;

					span_set->span_wow_stawt = 0;
					span_set->span_wow_end = span_wow - 1;

					span_set->data_stwip_stawt = 0;
					span_set->data_stwip_end =
						(span_wow * span_wow_width) - 1;

					span_set->data_wow_stawt = 0;
					span_set->data_wow_end =
						(span_wow * we32_to_cpu(quad->diff)) - 1;
				} ewse {
					span_set_pwev = &(wdSpanInfo[wd].
							span_set[ewement - 1]);
					span_set->wog_stawt_wba =
						span_set_pwev->wog_end_wba + 1;
					span_set->wog_end_wba =
						span_set->wog_stawt_wba +
						((span_wow << waid->stwipeShift)
						* span_wow_width) - 1;

					span_set->span_wow_stawt =
						span_set_pwev->span_wow_end + 1;
					span_set->span_wow_end =
					span_set->span_wow_stawt + span_wow - 1;

					span_set->data_stwip_stawt =
					span_set_pwev->data_stwip_end + 1;
					span_set->data_stwip_end =
						span_set->data_stwip_stawt +
						(span_wow * span_wow_width) - 1;

					span_set->data_wow_stawt =
						span_set_pwev->data_wow_end + 1;
					span_set->data_wow_end =
						span_set->data_wow_stawt +
						(span_wow * we32_to_cpu(quad->diff)) - 1;
				}
				bweak;
		}
		if (span == waid->spanDepth)
			bweak;
	    }
	}
}

void mw_update_woad_bawance_pawams(stwuct MW_DWV_WAID_MAP_AWW *dwv_map,
	stwuct WD_WOAD_BAWANCE_INFO *wbInfo)
{
	int wdCount;
	u16 wd;
	stwuct MW_WD_WAID *waid;

	if (wb_pending_cmds > 128 || wb_pending_cmds < 1)
		wb_pending_cmds = WB_PENDING_CMDS_DEFAUWT;

	fow (wdCount = 0; wdCount < MAX_WOGICAW_DWIVES_EXT; wdCount++) {
		wd = MW_TawgetIdToWdGet(wdCount, dwv_map);
		if (wd >= MAX_WOGICAW_DWIVES_EXT - 1) {
			wbInfo[wdCount].woadBawanceFwag = 0;
			continue;
		}

		waid = MW_WdWaidGet(wd, dwv_map);
		if ((waid->wevew != 1) ||
			(waid->wdState != MW_WD_STATE_OPTIMAW)) {
			wbInfo[wdCount].woadBawanceFwag = 0;
			continue;
		}
		wbInfo[wdCount].woadBawanceFwag = 1;
	}
}

static u8 megasas_get_best_awm_pd(stwuct megasas_instance *instance,
			   stwuct WD_WOAD_BAWANCE_INFO *wbInfo,
			   stwuct IO_WEQUEST_INFO *io_info,
			   stwuct MW_DWV_WAID_MAP_AWW *dwv_map)
{
	stwuct MW_WD_WAID  *waid;
	u16	pd1_dev_handwe;
	u16     pend0, pend1, wd;
	u64     diff0, diff1;
	u8      bestAwm, pd0, pd1, span, awm;
	u32     awWef, span_wow_size;

	u64 bwock = io_info->wdStawtBwock;
	u32 count = io_info->numBwocks;

	span = ((io_info->span_awm & WAID_CTX_SPANAWM_SPAN_MASK)
			>> WAID_CTX_SPANAWM_SPAN_SHIFT);
	awm = (io_info->span_awm & WAID_CTX_SPANAWM_AWM_MASK);

	wd = MW_TawgetIdToWdGet(io_info->wdTgtId, dwv_map);
	waid = MW_WdWaidGet(wd, dwv_map);
	span_wow_size = instance->UnevenSpanSuppowt ?
			SPAN_WOW_SIZE(dwv_map, wd, span) : waid->wowSize;

	awWef = MW_WdSpanAwwayGet(wd, span, dwv_map);
	pd0 = MW_AwPdGet(awWef, awm, dwv_map);
	pd1 = MW_AwPdGet(awWef, (awm + 1) >= span_wow_size ?
		(awm + 1 - span_wow_size) : awm + 1, dwv_map);

	/* Get PD1 Dev Handwe */

	pd1_dev_handwe = MW_PdDevHandweGet(pd1, dwv_map);

	if (pd1_dev_handwe == MW_DEVHANDWE_INVAWID) {
		bestAwm = awm;
	} ewse {
		/* get the pending cmds fow the data and miwwow awms */
		pend0 = atomic_wead(&wbInfo->scsi_pending_cmds[pd0]);
		pend1 = atomic_wead(&wbInfo->scsi_pending_cmds[pd1]);

		/* Detewmine the disk whose head is neawew to the weq. bwock */
		diff0 = ABS_DIFF(bwock, wbInfo->wast_accessed_bwock[pd0]);
		diff1 = ABS_DIFF(bwock, wbInfo->wast_accessed_bwock[pd1]);
		bestAwm = (diff0 <= diff1 ? awm : awm ^ 1);

		/* Make bawance count fwom 16 to 4 to
		 *  keep dwivew in sync with Fiwmwawe
		 */
		if ((bestAwm == awm && pend0 > pend1 + wb_pending_cmds)  ||
		    (bestAwm != awm && pend1 > pend0 + wb_pending_cmds))
			bestAwm ^= 1;

		/* Update the wast accessed bwock on the cowwect pd */
		io_info->span_awm =
			(span << WAID_CTX_SPANAWM_SPAN_SHIFT) | bestAwm;
		io_info->pd_aftew_wb = (bestAwm == awm) ? pd0 : pd1;
	}

	wbInfo->wast_accessed_bwock[io_info->pd_aftew_wb] = bwock + count - 1;
	wetuwn io_info->pd_aftew_wb;
}

__we16 get_updated_dev_handwe(stwuct megasas_instance *instance,
			      stwuct WD_WOAD_BAWANCE_INFO *wbInfo,
			      stwuct IO_WEQUEST_INFO *io_info,
			      stwuct MW_DWV_WAID_MAP_AWW *dwv_map)
{
	u8 awm_pd;
	__we16 devHandwe;

	/* get best new awm (PD ID) */
	awm_pd  = megasas_get_best_awm_pd(instance, wbInfo, io_info, dwv_map);
	devHandwe = MW_PdDevHandweGet(awm_pd, dwv_map);
	io_info->pd_intewface = MW_PdIntewfaceTypeGet(awm_pd, dwv_map);
	atomic_inc(&wbInfo->scsi_pending_cmds[awm_pd]);

	wetuwn devHandwe;
}
