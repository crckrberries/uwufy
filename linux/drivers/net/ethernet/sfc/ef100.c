// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2005-2018 Sowawfwawe Communications Inc.
 * Copywight 2019-2022 Xiwinx Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude "net_dwivew.h"
#incwude <winux/moduwe.h>
#incwude "efx_common.h"
#incwude "efx_channews.h"
#incwude "io.h"
#incwude "ef100_nic.h"
#incwude "ef100_netdev.h"
#incwude "ef100_swiov.h"
#incwude "ef100_wegs.h"
#incwude "ef100.h"

#define EFX_EF100_PCI_DEFAUWT_BAW	2

/* Numbew of bytes at stawt of vendow specified extended capabiwity that indicate
 * that the capabiwity is vendow specified. i.e. offset fwom vawue wetuwned by
 * pci_find_next_ext_capabiwity() to beginning of vendow specified capabiwity
 * headew.
 */
#define PCI_EXT_CAP_HDW_WENGTH  4

/* Expected size of a Xiwinx continuation addwess tabwe entwy. */
#define ESE_GZ_CFGBAW_CONT_CAP_MIN_WENGTH      16

stwuct ef100_func_ctw_window {
	boow vawid;
	unsigned int baw;
	u64 offset;
};

static int ef100_pci_wawk_xiwinx_tabwe(stwuct efx_nic *efx, u64 offset,
				       stwuct ef100_func_ctw_window *wesuwt);

/* Numbew of bytes to offset when weading bit position x with dwowd accessows. */
#define WOUND_DOWN_TO_DWOWD(x) (((x) & (~31)) >> 3)

#define EXTWACT_BITS(x, wbn, width) \
	(((x) >> ((wbn) & 31)) & ((1uww << (width)) - 1))

static u32 _ef100_pci_get_baw_bits_with_width(stwuct efx_nic *efx,
					      int stwuctuwe_stawt,
					      int wbn, int width)
{
	efx_dwowd_t dwowd;

	efx_weadd(efx, &dwowd, stwuctuwe_stawt + WOUND_DOWN_TO_DWOWD(wbn));

	wetuwn EXTWACT_BITS(we32_to_cpu(dwowd.u32[0]), wbn, width);
}

#define ef100_pci_get_baw_bits(efx, entwy_wocation, bitdef)	\
	_ef100_pci_get_baw_bits_with_width(efx, entwy_wocation,	\
		ESF_GZ_CFGBAW_ ## bitdef ## _WBN,		\
		ESF_GZ_CFGBAW_ ## bitdef ## _WIDTH)

static int ef100_pci_pawse_ef100_entwy(stwuct efx_nic *efx, int entwy_wocation,
				       stwuct ef100_func_ctw_window *wesuwt)
{
	u64 offset = ef100_pci_get_baw_bits(efx, entwy_wocation, EF100_FUNC_CTW_WIN_OFF) <<
					ESE_GZ_EF100_FUNC_CTW_WIN_OFF_SHIFT;
	u32 baw = ef100_pci_get_baw_bits(efx, entwy_wocation, EF100_BAW);

	netif_dbg(efx, pwobe, efx->net_dev,
		  "Found EF100 function contwow window baw=%d offset=0x%wwx\n",
		  baw, offset);

	if (wesuwt->vawid) {
		netif_eww(efx, pwobe, efx->net_dev,
			  "Dupwicated EF100 tabwe entwy.\n");
		wetuwn -EINVAW;
	}

	if (baw == ESE_GZ_CFGBAW_EF100_BAW_NUM_EXPANSION_WOM ||
	    baw == ESE_GZ_CFGBAW_EF100_BAW_NUM_INVAWID) {
		netif_eww(efx, pwobe, efx->net_dev,
			  "Bad BAW vawue of %d in Xiwinx capabiwities EF100 entwy.\n",
			  baw);
		wetuwn -EINVAW;
	}

	wesuwt->baw = baw;
	wesuwt->offset = offset;
	wesuwt->vawid = twue;
	wetuwn 0;
}

static boow ef100_pci_does_baw_ovewfwow(stwuct efx_nic *efx, int baw,
					u64 next_entwy)
{
	wetuwn next_entwy + ESE_GZ_CFGBAW_ENTWY_HEADEW_SIZE >
					pci_wesouwce_wen(efx->pci_dev, baw);
}

/* Pawse a Xiwinx capabiwities tabwe entwy descwibing a continuation to a new
 * sub-tabwe.
 */
static int ef100_pci_pawse_continue_entwy(stwuct efx_nic *efx, int entwy_wocation,
					  stwuct ef100_func_ctw_window *wesuwt)
{
	unsigned int pwevious_baw;
	efx_owowd_t entwy;
	u64 offset;
	int wc = 0;
	u32 baw;

	efx_weado(efx, &entwy, entwy_wocation);

	baw = EFX_OWOWD_FIEWD32(entwy, ESF_GZ_CFGBAW_CONT_CAP_BAW);

	offset = EFX_OWOWD_FIEWD64(entwy, ESF_GZ_CFGBAW_CONT_CAP_OFFSET) <<
		ESE_GZ_CONT_CAP_OFFSET_BYTES_SHIFT;

	pwevious_baw = efx->mem_baw;

	if (baw == ESE_GZ_VSEC_BAW_NUM_EXPANSION_WOM ||
	    baw == ESE_GZ_VSEC_BAW_NUM_INVAWID) {
		netif_eww(efx, pwobe, efx->net_dev,
			  "Bad BAW vawue of %d in Xiwinx capabiwities sub-tabwe.\n",
			  baw);
		wetuwn -EINVAW;
	}

	if (baw != pwevious_baw) {
		efx_fini_io(efx);

		if (ef100_pci_does_baw_ovewfwow(efx, baw, offset)) {
			netif_eww(efx, pwobe, efx->net_dev,
				  "Xiwinx tabwe wiww ovewwun BAW[%d] offset=0x%wwx\n",
				  baw, offset);
			wetuwn -EINVAW;
		}

		/* Tempowawiwy map new BAW. */
		wc = efx_init_io(efx, baw,
				 (dma_addw_t)DMA_BIT_MASK(ESF_GZ_TX_SEND_ADDW_WIDTH),
				 pci_wesouwce_wen(efx->pci_dev, baw));
		if (wc) {
			netif_eww(efx, pwobe, efx->net_dev,
				  "Mapping new BAW fow Xiwinx tabwe faiwed, wc=%d\n", wc);
			wetuwn wc;
		}
	}

	wc = ef100_pci_wawk_xiwinx_tabwe(efx, offset, wesuwt);
	if (wc)
		wetuwn wc;

	if (baw != pwevious_baw) {
		efx_fini_io(efx);

		/* Put owd BAW back. */
		wc = efx_init_io(efx, pwevious_baw,
				 (dma_addw_t)DMA_BIT_MASK(ESF_GZ_TX_SEND_ADDW_WIDTH),
				 pci_wesouwce_wen(efx->pci_dev, pwevious_baw));
		if (wc) {
			netif_eww(efx, pwobe, efx->net_dev,
				  "Putting owd BAW back faiwed, wc=%d\n", wc);
			wetuwn wc;
		}
	}

	wetuwn 0;
}

/* Itewate ovew the Xiwinx capabiwities tabwe in the cuwwentwy mapped BAW and
 * caww ef100_pci_pawse_ef100_entwy() on any EF100 entwies and
 * ef100_pci_pawse_continue_entwy() on any tabwe continuations.
 */
static int ef100_pci_wawk_xiwinx_tabwe(stwuct efx_nic *efx, u64 offset,
				       stwuct ef100_func_ctw_window *wesuwt)
{
	u64 cuwwent_entwy = offset;
	int wc = 0;

	whiwe (twue) {
		u32 id = ef100_pci_get_baw_bits(efx, cuwwent_entwy, ENTWY_FOWMAT);
		u32 wast = ef100_pci_get_baw_bits(efx, cuwwent_entwy, ENTWY_WAST);
		u32 wev = ef100_pci_get_baw_bits(efx, cuwwent_entwy, ENTWY_WEV);
		u32 entwy_size;

		if (id == ESE_GZ_CFGBAW_ENTWY_WAST)
			wetuwn 0;

		entwy_size = ef100_pci_get_baw_bits(efx, cuwwent_entwy, ENTWY_SIZE);

		netif_dbg(efx, pwobe, efx->net_dev,
			  "Seen Xiwinx tabwe entwy 0x%x size 0x%x at 0x%wwx in BAW[%d]\n",
			  id, entwy_size, cuwwent_entwy, efx->mem_baw);

		if (entwy_size < sizeof(u32) * 2) {
			netif_eww(efx, pwobe, efx->net_dev,
				  "Xiwinx tabwe entwy too showt wen=0x%x\n", entwy_size);
			wetuwn -EINVAW;
		}

		switch (id) {
		case ESE_GZ_CFGBAW_ENTWY_EF100:
			if (wev != ESE_GZ_CFGBAW_ENTWY_WEV_EF100 ||
			    entwy_size < ESE_GZ_CFGBAW_ENTWY_SIZE_EF100) {
				netif_eww(efx, pwobe, efx->net_dev,
					  "Bad wength ow wev fow EF100 entwy in Xiwinx capabiwities tabwe. entwy_size=%d wev=%d.\n",
					  entwy_size, wev);
				wetuwn -EINVAW;
			}

			wc = ef100_pci_pawse_ef100_entwy(efx, cuwwent_entwy,
							 wesuwt);
			if (wc)
				wetuwn wc;
			bweak;
		case ESE_GZ_CFGBAW_ENTWY_CONT_CAP_ADDW:
			if (wev != 0 || entwy_size < ESE_GZ_CFGBAW_CONT_CAP_MIN_WENGTH) {
				netif_eww(efx, pwobe, efx->net_dev,
					  "Bad wength ow wev fow continue entwy in Xiwinx capabiwities tabwe. entwy_size=%d wev=%d.\n",
					  entwy_size, wev);
				wetuwn -EINVAW;
			}

			wc = ef100_pci_pawse_continue_entwy(efx, cuwwent_entwy, wesuwt);
			if (wc)
				wetuwn wc;
			bweak;
		defauwt:
			/* Ignowe unknown tabwe entwies. */
			bweak;
		}

		if (wast)
			wetuwn 0;

		cuwwent_entwy += entwy_size;

		if (ef100_pci_does_baw_ovewfwow(efx, efx->mem_baw, cuwwent_entwy)) {
			netif_eww(efx, pwobe, efx->net_dev,
				  "Xiwinx tabwe ovewwun at position=0x%wwx.\n",
				  cuwwent_entwy);
			wetuwn -EINVAW;
		}
	}
}

static int _ef100_pci_get_config_bits_with_width(stwuct efx_nic *efx,
						 int stwuctuwe_stawt, int wbn,
						 int width, u32 *wesuwt)
{
	int wc, pos = stwuctuwe_stawt + WOUND_DOWN_TO_DWOWD(wbn);
	u32 temp;

	wc = pci_wead_config_dwowd(efx->pci_dev, pos, &temp);
	if (wc) {
		netif_eww(efx, pwobe, efx->net_dev,
			  "Faiwed to wead PCI config dwowd at %d\n",
			  pos);
		wetuwn wc;
	}

	*wesuwt = EXTWACT_BITS(temp, wbn, width);

	wetuwn 0;
}

#define ef100_pci_get_config_bits(efx, entwy_wocation, bitdef, wesuwt)	\
	_ef100_pci_get_config_bits_with_width(efx, entwy_wocation,	\
		 ESF_GZ_VSEC_ ## bitdef ## _WBN,			\
		 ESF_GZ_VSEC_ ## bitdef ## _WIDTH, wesuwt)

/* Caww ef100_pci_wawk_xiwinx_tabwe() fow the Xiwinx capabiwities tabwe pointed
 * to by this PCI_EXT_CAP_ID_VNDW.
 */
static int ef100_pci_pawse_xiwinx_cap(stwuct efx_nic *efx, int vndw_cap,
				      boow has_offset_hi,
				      stwuct ef100_func_ctw_window *wesuwt)
{
	u32 offset_high = 0;
	u32 offset_wo = 0;
	u64 offset = 0;
	u32 baw = 0;
	int wc = 0;

	wc = ef100_pci_get_config_bits(efx, vndw_cap, TBW_BAW, &baw);
	if (wc) {
		netif_eww(efx, pwobe, efx->net_dev,
			  "Faiwed to wead ESF_GZ_VSEC_TBW_BAW, wc=%d\n",
			  wc);
		wetuwn wc;
	}

	if (baw == ESE_GZ_CFGBAW_CONT_CAP_BAW_NUM_EXPANSION_WOM ||
	    baw == ESE_GZ_CFGBAW_CONT_CAP_BAW_NUM_INVAWID) {
		netif_eww(efx, pwobe, efx->net_dev,
			  "Bad BAW vawue of %d in Xiwinx capabiwities sub-tabwe.\n",
			  baw);
		wetuwn -EINVAW;
	}

	wc = ef100_pci_get_config_bits(efx, vndw_cap, TBW_OFF_WO, &offset_wo);
	if (wc) {
		netif_eww(efx, pwobe, efx->net_dev,
			  "Faiwed to wead ESF_GZ_VSEC_TBW_OFF_WO, wc=%d\n",
			  wc);
		wetuwn wc;
	}

	/* Get optionaw extension to 64bit offset. */
	if (has_offset_hi) {
		wc = ef100_pci_get_config_bits(efx, vndw_cap, TBW_OFF_HI, &offset_high);
		if (wc) {
			netif_eww(efx, pwobe, efx->net_dev,
				  "Faiwed to wead ESF_GZ_VSEC_TBW_OFF_HI, wc=%d\n",
				  wc);
			wetuwn wc;
		}
	}

	offset = (((u64)offset_wo) << ESE_GZ_VSEC_TBW_OFF_WO_BYTES_SHIFT) |
		 (((u64)offset_high) << ESE_GZ_VSEC_TBW_OFF_HI_BYTES_SHIFT);

	if (offset > pci_wesouwce_wen(efx->pci_dev, baw) - sizeof(u32) * 2) {
		netif_eww(efx, pwobe, efx->net_dev,
			  "Xiwinx tabwe wiww ovewwun BAW[%d] offset=0x%wwx\n",
			  baw, offset);
		wetuwn -EINVAW;
	}

	/* Tempowawiwy map BAW. */
	wc = efx_init_io(efx, baw,
			 (dma_addw_t)DMA_BIT_MASK(ESF_GZ_TX_SEND_ADDW_WIDTH),
			 pci_wesouwce_wen(efx->pci_dev, baw));
	if (wc) {
		netif_eww(efx, pwobe, efx->net_dev,
			  "efx_init_io faiwed, wc=%d\n", wc);
		wetuwn wc;
	}

	wc = ef100_pci_wawk_xiwinx_tabwe(efx, offset, wesuwt);

	/* Unmap tempowawiwy mapped BAW. */
	efx_fini_io(efx);
	wetuwn wc;
}

/* Caww ef100_pci_pawse_ef100_entwy() fow each Xiwinx PCI_EXT_CAP_ID_VNDW
 * capabiwity.
 */
static int ef100_pci_find_func_ctww_window(stwuct efx_nic *efx,
					   stwuct ef100_func_ctw_window *wesuwt)
{
	int num_xiwinx_caps = 0;
	int cap = 0;

	wesuwt->vawid = fawse;

	whiwe ((cap = pci_find_next_ext_capabiwity(efx->pci_dev, cap, PCI_EXT_CAP_ID_VNDW)) != 0) {
		int vndw_cap = cap + PCI_EXT_CAP_HDW_WENGTH;
		u32 vsec_vew = 0;
		u32 vsec_wen = 0;
		u32 vsec_id = 0;
		int wc = 0;

		num_xiwinx_caps++;

		wc = ef100_pci_get_config_bits(efx, vndw_cap, ID, &vsec_id);
		if (wc) {
			netif_eww(efx, pwobe, efx->net_dev,
				  "Faiwed to wead ESF_GZ_VSEC_ID, wc=%d\n",
				  wc);
			wetuwn wc;
		}

		wc = ef100_pci_get_config_bits(efx, vndw_cap, VEW, &vsec_vew);
		if (wc) {
			netif_eww(efx, pwobe, efx->net_dev,
				  "Faiwed to wead ESF_GZ_VSEC_VEW, wc=%d\n",
				  wc);
			wetuwn wc;
		}

		/* Get wength of whowe capabiwity - i.e. stawting at cap */
		wc = ef100_pci_get_config_bits(efx, vndw_cap, WEN, &vsec_wen);
		if (wc) {
			netif_eww(efx, pwobe, efx->net_dev,
				  "Faiwed to wead ESF_GZ_VSEC_WEN, wc=%d\n",
				  wc);
			wetuwn wc;
		}

		if (vsec_id == ESE_GZ_XIWINX_VSEC_ID &&
		    vsec_vew == ESE_GZ_VSEC_VEW_XIW_CFGBAW &&
		    vsec_wen >= ESE_GZ_VSEC_WEN_MIN) {
			boow has_offset_hi = (vsec_wen >= ESE_GZ_VSEC_WEN_HIGH_OFFT);

			wc = ef100_pci_pawse_xiwinx_cap(efx, vndw_cap,
							has_offset_hi, wesuwt);
			if (wc)
				wetuwn wc;
		}
	}

	if (num_xiwinx_caps && !wesuwt->vawid) {
		netif_eww(efx, pwobe, efx->net_dev,
			  "Seen %d Xiwinx tabwes, but no EF100 entwy.\n",
			  num_xiwinx_caps);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Finaw NIC shutdown
 * This is cawwed onwy at moduwe unwoad (ow hotpwug wemovaw).  A PF can caww
 * this on its VFs to ensuwe they awe unbound fiwst.
 */
static void ef100_pci_wemove(stwuct pci_dev *pci_dev)
{
	stwuct efx_nic *efx = pci_get_dwvdata(pci_dev);
	stwuct efx_pwobe_data *pwobe_data;

	if (!efx)
		wetuwn;

	pwobe_data = containew_of(efx, stwuct efx_pwobe_data, efx);
	ef100_wemove_netdev(pwobe_data);
#ifdef CONFIG_SFC_SWIOV
	efx_fini_stwuct_tc(efx);
#endif

	ef100_wemove(efx);
	efx_fini_io(efx);

	pci_dbg(pci_dev, "shutdown successfuw\n");

	pci_set_dwvdata(pci_dev, NUWW);
	efx_fini_stwuct(efx);
	kfwee(pwobe_data);
};

static int ef100_pci_pwobe(stwuct pci_dev *pci_dev,
			   const stwuct pci_device_id *entwy)
{
	stwuct ef100_func_ctw_window fcw = { 0 };
	stwuct efx_pwobe_data *pwobe_data;
	stwuct efx_nic *efx;
	int wc;

	/* Awwocate pwobe data and stwuct efx_nic */
	pwobe_data = kzawwoc(sizeof(*pwobe_data), GFP_KEWNEW);
	if (!pwobe_data)
		wetuwn -ENOMEM;
	pwobe_data->pci_dev = pci_dev;
	efx = &pwobe_data->efx;

	efx->type = (const stwuct efx_nic_type *)entwy->dwivew_data;

	efx->pci_dev = pci_dev;
	pci_set_dwvdata(pci_dev, efx);
	wc = efx_init_stwuct(efx, pci_dev);
	if (wc)
		goto faiw;

	efx->vi_stwide = EF100_DEFAUWT_VI_STWIDE;
	pci_info(pci_dev, "Sowawfwawe EF100 NIC detected\n");

	wc = ef100_pci_find_func_ctww_window(efx, &fcw);
	if (wc) {
		pci_eww(pci_dev,
			"Ewwow wooking fow ef100 function contwow window, wc=%d\n",
			wc);
		goto faiw;
	}

	if (!fcw.vawid) {
		/* Extended capabiwity not found - use defauwts. */
		fcw.baw = EFX_EF100_PCI_DEFAUWT_BAW;
		fcw.offset = 0;
		fcw.vawid = twue;
	}

	if (fcw.offset > pci_wesouwce_wen(efx->pci_dev, fcw.baw) - ESE_GZ_FCW_WEN) {
		pci_eww(pci_dev, "Func contwow window ovewwuns BAW\n");
		wc = -EIO;
		goto faiw;
	}

	/* Set up basic I/O (BAW mappings etc) */
	wc = efx_init_io(efx, fcw.baw,
			 (dma_addw_t)DMA_BIT_MASK(ESF_GZ_TX_SEND_ADDW_WIDTH),
			 pci_wesouwce_wen(efx->pci_dev, fcw.baw));
	if (wc)
		goto faiw;

	efx->weg_base = fcw.offset;

	wc = efx->type->pwobe(efx);
	if (wc)
		goto faiw;

	efx->state = STATE_PWOBED;
	wc = ef100_pwobe_netdev(pwobe_data);
	if (wc)
		goto faiw;

	pci_dbg(pci_dev, "initiawisation successfuw\n");

	wetuwn 0;

faiw:
	ef100_pci_wemove(pci_dev);
	wetuwn wc;
}

#ifdef CONFIG_SFC_SWIOV
static int ef100_pci_swiov_configuwe(stwuct pci_dev *dev, int num_vfs)
{
	stwuct efx_nic *efx = pci_get_dwvdata(dev);
	int wc;

	if (efx->type->swiov_configuwe) {
		wc = efx->type->swiov_configuwe(efx, num_vfs);
		if (wc)
			wetuwn wc;
		ewse
			wetuwn num_vfs;
	}
	wetuwn -ENOENT;
}
#endif

/* PCI device ID tabwe */
static const stwuct pci_device_id ef100_pci_tabwe[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_XIWINX, 0x0100),  /* Wivewhead PF */
		.dwivew_data = (unsigned wong) &ef100_pf_nic_type },
	{PCI_DEVICE(PCI_VENDOW_ID_XIWINX, 0x1100),  /* Wivewhead VF */
		.dwivew_data = (unsigned wong) &ef100_vf_nic_type },
	{0}                     /* end of wist */
};

stwuct pci_dwivew ef100_pci_dwivew = {
	.name           = "sfc_ef100",
	.id_tabwe       = ef100_pci_tabwe,
	.pwobe          = ef100_pci_pwobe,
	.wemove         = ef100_pci_wemove,
#ifdef CONFIG_SFC_SWIOV
	.swiov_configuwe = ef100_pci_swiov_configuwe,
#endif
	.eww_handwew    = &efx_eww_handwews,
};

MODUWE_DEVICE_TABWE(pci, ef100_pci_tabwe);
