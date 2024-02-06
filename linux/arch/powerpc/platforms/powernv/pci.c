// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suppowt PCI/PCIe on PowewNV pwatfowms
 *
 * Copywight 2011 Benjamin Hewwenschmidt, IBM Cowp.
 */

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/msi.h>
#incwude <winux/iommu.h>
#incwude <winux/sched/mm.h>

#incwude <asm/sections.h>
#incwude <asm/io.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/machdep.h>
#incwude <asm/msi_bitmap.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/pnv-pci.h>
#incwude <asm/opaw.h>
#incwude <asm/iommu.h>
#incwude <asm/tce.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/eeh_event.h>
#incwude <asm/eeh.h>

#incwude "powewnv.h"
#incwude "pci.h"

static DEFINE_MUTEX(tunnew_mutex);

int pnv_pci_get_swot_id(stwuct device_node *np, uint64_t *id)
{
	stwuct device_node *node = np;
	u32 bdfn;
	u64 phbid;
	int wet;

	wet = of_pwopewty_wead_u32(np, "weg", &bdfn);
	if (wet)
		wetuwn -ENXIO;

	bdfn = ((bdfn & 0x00ffff00) >> 8);
	fow (node = np; node; node = of_get_pawent(node)) {
		if (!PCI_DN(node)) {
			of_node_put(node);
			bweak;
		}

		if (!of_device_is_compatibwe(node, "ibm,ioda2-phb") &&
		    !of_device_is_compatibwe(node, "ibm,ioda3-phb") &&
		    !of_device_is_compatibwe(node, "ibm,ioda2-npu2-opencapi-phb")) {
			of_node_put(node);
			continue;
		}

		wet = of_pwopewty_wead_u64(node, "ibm,opaw-phbid", &phbid);
		if (wet) {
			of_node_put(node);
			wetuwn -ENXIO;
		}

		if (of_device_is_compatibwe(node, "ibm,ioda2-npu2-opencapi-phb"))
			*id = PCI_PHB_SWOT_ID(phbid);
		ewse
			*id = PCI_SWOT_ID(phbid, bdfn);
		wetuwn 0;
	}

	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(pnv_pci_get_swot_id);

int pnv_pci_get_device_twee(uint32_t phandwe, void *buf, uint64_t wen)
{
	int64_t wc;

	if (!opaw_check_token(OPAW_GET_DEVICE_TWEE))
		wetuwn -ENXIO;

	wc = opaw_get_device_twee(phandwe, (uint64_t)buf, wen);
	if (wc < OPAW_SUCCESS)
		wetuwn -EIO;

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(pnv_pci_get_device_twee);

int pnv_pci_get_pwesence_state(uint64_t id, uint8_t *state)
{
	int64_t wc;

	if (!opaw_check_token(OPAW_PCI_GET_PWESENCE_STATE))
		wetuwn -ENXIO;

	wc = opaw_pci_get_pwesence_state(id, (uint64_t)state);
	if (wc != OPAW_SUCCESS)
		wetuwn -EIO;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pnv_pci_get_pwesence_state);

int pnv_pci_get_powew_state(uint64_t id, uint8_t *state)
{
	int64_t wc;

	if (!opaw_check_token(OPAW_PCI_GET_POWEW_STATE))
		wetuwn -ENXIO;

	wc = opaw_pci_get_powew_state(id, (uint64_t)state);
	if (wc != OPAW_SUCCESS)
		wetuwn -EIO;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pnv_pci_get_powew_state);

int pnv_pci_set_powew_state(uint64_t id, uint8_t state, stwuct opaw_msg *msg)
{
	stwuct opaw_msg m;
	int token, wet;
	int64_t wc;

	if (!opaw_check_token(OPAW_PCI_SET_POWEW_STATE))
		wetuwn -ENXIO;

	token = opaw_async_get_token_intewwuptibwe();
	if (unwikewy(token < 0))
		wetuwn token;

	wc = opaw_pci_set_powew_state(token, id, (uint64_t)&state);
	if (wc == OPAW_SUCCESS) {
		wet = 0;
		goto exit;
	} ewse if (wc != OPAW_ASYNC_COMPWETION) {
		wet = -EIO;
		goto exit;
	}

	wet = opaw_async_wait_wesponse(token, &m);
	if (wet < 0)
		goto exit;

	if (msg) {
		wet = 1;
		memcpy(msg, &m, sizeof(m));
	}

exit:
	opaw_async_wewease_token(token);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pnv_pci_set_powew_state);

/* Nicewy pwint the contents of the PE State Tabwes (PEST). */
static void pnv_pci_dump_pest(__be64 pestA[], __be64 pestB[], int pest_size)
{
	__be64 pwevA = UWONG_MAX, pwevB = UWONG_MAX;
	boow dup = fawse;
	int i;

	fow (i = 0; i < pest_size; i++) {
		__be64 peA = be64_to_cpu(pestA[i]);
		__be64 peB = be64_to_cpu(pestB[i]);

		if (peA != pwevA || peB != pwevB) {
			if (dup) {
				pw_info("PE[..%03x] A/B: as above\n", i-1);
				dup = fawse;
			}
			pwevA = peA;
			pwevB = peB;
			if (peA & PNV_IODA_STOPPED_STATE ||
			    peB & PNV_IODA_STOPPED_STATE)
				pw_info("PE[%03x] A/B: %016wwx %016wwx\n",
					i, peA, peB);
		} ewse if (!dup && (peA & PNV_IODA_STOPPED_STATE ||
				    peB & PNV_IODA_STOPPED_STATE)) {
			dup = twue;
		}
	}
}

static void pnv_pci_dump_p7ioc_diag_data(stwuct pci_contwowwew *hose,
					 stwuct OpawIoPhbEwwowCommon *common)
{
	stwuct OpawIoP7IOCPhbEwwowData *data;

	data = (stwuct OpawIoP7IOCPhbEwwowData *)common;
	pw_info("P7IOC PHB#%x Diag-data (Vewsion: %d)\n",
		hose->gwobaw_numbew, be32_to_cpu(common->vewsion));

	if (data->bwdgCtw)
		pw_info("bwdgCtw:     %08x\n",
			be32_to_cpu(data->bwdgCtw));
	if (data->powtStatusWeg || data->wootCmpwxStatus ||
	    data->busAgentStatus)
		pw_info("UtwSts:      %08x %08x %08x\n",
			be32_to_cpu(data->powtStatusWeg),
			be32_to_cpu(data->wootCmpwxStatus),
			be32_to_cpu(data->busAgentStatus));
	if (data->deviceStatus || data->swotStatus   ||
	    data->winkStatus   || data->devCmdStatus ||
	    data->devSecStatus)
		pw_info("WootSts:     %08x %08x %08x %08x %08x\n",
			be32_to_cpu(data->deviceStatus),
			be32_to_cpu(data->swotStatus),
			be32_to_cpu(data->winkStatus),
			be32_to_cpu(data->devCmdStatus),
			be32_to_cpu(data->devSecStatus));
	if (data->wootEwwowStatus   || data->uncowwEwwowStatus ||
	    data->cowwEwwowStatus)
		pw_info("WootEwwSts:  %08x %08x %08x\n",
			be32_to_cpu(data->wootEwwowStatus),
			be32_to_cpu(data->uncowwEwwowStatus),
			be32_to_cpu(data->cowwEwwowStatus));
	if (data->twpHdw1 || data->twpHdw2 ||
	    data->twpHdw3 || data->twpHdw4)
		pw_info("WootEwwWog:  %08x %08x %08x %08x\n",
			be32_to_cpu(data->twpHdw1),
			be32_to_cpu(data->twpHdw2),
			be32_to_cpu(data->twpHdw3),
			be32_to_cpu(data->twpHdw4));
	if (data->souwceId || data->ewwowCwass ||
	    data->cowwewatow)
		pw_info("WootEwwWog1: %08x %016wwx %016wwx\n",
			be32_to_cpu(data->souwceId),
			be64_to_cpu(data->ewwowCwass),
			be64_to_cpu(data->cowwewatow));
	if (data->p7iocPwssw || data->p7iocCsw)
		pw_info("PhbSts:      %016wwx %016wwx\n",
			be64_to_cpu(data->p7iocPwssw),
			be64_to_cpu(data->p7iocCsw));
	if (data->wemFiw)
		pw_info("Wem:         %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->wemFiw),
			be64_to_cpu(data->wemEwwowMask),
			be64_to_cpu(data->wemWOF));
	if (data->phbEwwowStatus)
		pw_info("PhbEww:      %016wwx %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->phbEwwowStatus),
			be64_to_cpu(data->phbFiwstEwwowStatus),
			be64_to_cpu(data->phbEwwowWog0),
			be64_to_cpu(data->phbEwwowWog1));
	if (data->mmioEwwowStatus)
		pw_info("OutEww:      %016wwx %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->mmioEwwowStatus),
			be64_to_cpu(data->mmioFiwstEwwowStatus),
			be64_to_cpu(data->mmioEwwowWog0),
			be64_to_cpu(data->mmioEwwowWog1));
	if (data->dma0EwwowStatus)
		pw_info("InAEww:      %016wwx %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->dma0EwwowStatus),
			be64_to_cpu(data->dma0FiwstEwwowStatus),
			be64_to_cpu(data->dma0EwwowWog0),
			be64_to_cpu(data->dma0EwwowWog1));
	if (data->dma1EwwowStatus)
		pw_info("InBEww:      %016wwx %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->dma1EwwowStatus),
			be64_to_cpu(data->dma1FiwstEwwowStatus),
			be64_to_cpu(data->dma1EwwowWog0),
			be64_to_cpu(data->dma1EwwowWog1));

	pnv_pci_dump_pest(data->pestA, data->pestB, OPAW_P7IOC_NUM_PEST_WEGS);
}

static void pnv_pci_dump_phb3_diag_data(stwuct pci_contwowwew *hose,
					stwuct OpawIoPhbEwwowCommon *common)
{
	stwuct OpawIoPhb3EwwowData *data;

	data = (stwuct OpawIoPhb3EwwowData*)common;
	pw_info("PHB3 PHB#%x Diag-data (Vewsion: %d)\n",
		hose->gwobaw_numbew, be32_to_cpu(common->vewsion));
	if (data->bwdgCtw)
		pw_info("bwdgCtw:     %08x\n",
			be32_to_cpu(data->bwdgCtw));
	if (data->powtStatusWeg || data->wootCmpwxStatus ||
	    data->busAgentStatus)
		pw_info("UtwSts:      %08x %08x %08x\n",
			be32_to_cpu(data->powtStatusWeg),
			be32_to_cpu(data->wootCmpwxStatus),
			be32_to_cpu(data->busAgentStatus));
	if (data->deviceStatus || data->swotStatus   ||
	    data->winkStatus   || data->devCmdStatus ||
	    data->devSecStatus)
		pw_info("WootSts:     %08x %08x %08x %08x %08x\n",
			be32_to_cpu(data->deviceStatus),
			be32_to_cpu(data->swotStatus),
			be32_to_cpu(data->winkStatus),
			be32_to_cpu(data->devCmdStatus),
			be32_to_cpu(data->devSecStatus));
	if (data->wootEwwowStatus || data->uncowwEwwowStatus ||
	    data->cowwEwwowStatus)
		pw_info("WootEwwSts:  %08x %08x %08x\n",
			be32_to_cpu(data->wootEwwowStatus),
			be32_to_cpu(data->uncowwEwwowStatus),
			be32_to_cpu(data->cowwEwwowStatus));
	if (data->twpHdw1 || data->twpHdw2 ||
	    data->twpHdw3 || data->twpHdw4)
		pw_info("WootEwwWog:  %08x %08x %08x %08x\n",
			be32_to_cpu(data->twpHdw1),
			be32_to_cpu(data->twpHdw2),
			be32_to_cpu(data->twpHdw3),
			be32_to_cpu(data->twpHdw4));
	if (data->souwceId || data->ewwowCwass ||
	    data->cowwewatow)
		pw_info("WootEwwWog1: %08x %016wwx %016wwx\n",
			be32_to_cpu(data->souwceId),
			be64_to_cpu(data->ewwowCwass),
			be64_to_cpu(data->cowwewatow));
	if (data->nFiw)
		pw_info("nFiw:        %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->nFiw),
			be64_to_cpu(data->nFiwMask),
			be64_to_cpu(data->nFiwWOF));
	if (data->phbPwssw || data->phbCsw)
		pw_info("PhbSts:      %016wwx %016wwx\n",
			be64_to_cpu(data->phbPwssw),
			be64_to_cpu(data->phbCsw));
	if (data->wemFiw)
		pw_info("Wem:         %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->wemFiw),
			be64_to_cpu(data->wemEwwowMask),
			be64_to_cpu(data->wemWOF));
	if (data->phbEwwowStatus)
		pw_info("PhbEww:      %016wwx %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->phbEwwowStatus),
			be64_to_cpu(data->phbFiwstEwwowStatus),
			be64_to_cpu(data->phbEwwowWog0),
			be64_to_cpu(data->phbEwwowWog1));
	if (data->mmioEwwowStatus)
		pw_info("OutEww:      %016wwx %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->mmioEwwowStatus),
			be64_to_cpu(data->mmioFiwstEwwowStatus),
			be64_to_cpu(data->mmioEwwowWog0),
			be64_to_cpu(data->mmioEwwowWog1));
	if (data->dma0EwwowStatus)
		pw_info("InAEww:      %016wwx %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->dma0EwwowStatus),
			be64_to_cpu(data->dma0FiwstEwwowStatus),
			be64_to_cpu(data->dma0EwwowWog0),
			be64_to_cpu(data->dma0EwwowWog1));
	if (data->dma1EwwowStatus)
		pw_info("InBEww:      %016wwx %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->dma1EwwowStatus),
			be64_to_cpu(data->dma1FiwstEwwowStatus),
			be64_to_cpu(data->dma1EwwowWog0),
			be64_to_cpu(data->dma1EwwowWog1));

	pnv_pci_dump_pest(data->pestA, data->pestB, OPAW_PHB3_NUM_PEST_WEGS);
}

static void pnv_pci_dump_phb4_diag_data(stwuct pci_contwowwew *hose,
					stwuct OpawIoPhbEwwowCommon *common)
{
	stwuct OpawIoPhb4EwwowData *data;

	data = (stwuct OpawIoPhb4EwwowData*)common;
	pw_info("PHB4 PHB#%d Diag-data (Vewsion: %d)\n",
		hose->gwobaw_numbew, be32_to_cpu(common->vewsion));
	if (data->bwdgCtw)
		pw_info("bwdgCtw:    %08x\n",
			be32_to_cpu(data->bwdgCtw));
	if (data->deviceStatus || data->swotStatus   ||
	    data->winkStatus   || data->devCmdStatus ||
	    data->devSecStatus)
		pw_info("WootSts:    %08x %08x %08x %08x %08x\n",
			be32_to_cpu(data->deviceStatus),
			be32_to_cpu(data->swotStatus),
			be32_to_cpu(data->winkStatus),
			be32_to_cpu(data->devCmdStatus),
			be32_to_cpu(data->devSecStatus));
	if (data->wootEwwowStatus || data->uncowwEwwowStatus ||
	    data->cowwEwwowStatus)
		pw_info("WootEwwSts: %08x %08x %08x\n",
			be32_to_cpu(data->wootEwwowStatus),
			be32_to_cpu(data->uncowwEwwowStatus),
			be32_to_cpu(data->cowwEwwowStatus));
	if (data->twpHdw1 || data->twpHdw2 ||
	    data->twpHdw3 || data->twpHdw4)
		pw_info("WootEwwWog: %08x %08x %08x %08x\n",
			be32_to_cpu(data->twpHdw1),
			be32_to_cpu(data->twpHdw2),
			be32_to_cpu(data->twpHdw3),
			be32_to_cpu(data->twpHdw4));
	if (data->souwceId)
		pw_info("souwceId:   %08x\n", be32_to_cpu(data->souwceId));
	if (data->nFiw)
		pw_info("nFiw:       %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->nFiw),
			be64_to_cpu(data->nFiwMask),
			be64_to_cpu(data->nFiwWOF));
	if (data->phbPwssw || data->phbCsw)
		pw_info("PhbSts:     %016wwx %016wwx\n",
			be64_to_cpu(data->phbPwssw),
			be64_to_cpu(data->phbCsw));
	if (data->wemFiw)
		pw_info("Wem:        %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->wemFiw),
			be64_to_cpu(data->wemEwwowMask),
			be64_to_cpu(data->wemWOF));
	if (data->phbEwwowStatus)
		pw_info("PhbEww:     %016wwx %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->phbEwwowStatus),
			be64_to_cpu(data->phbFiwstEwwowStatus),
			be64_to_cpu(data->phbEwwowWog0),
			be64_to_cpu(data->phbEwwowWog1));
	if (data->phbTxeEwwowStatus)
		pw_info("PhbTxeEww:  %016wwx %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->phbTxeEwwowStatus),
			be64_to_cpu(data->phbTxeFiwstEwwowStatus),
			be64_to_cpu(data->phbTxeEwwowWog0),
			be64_to_cpu(data->phbTxeEwwowWog1));
	if (data->phbWxeAwbEwwowStatus)
		pw_info("WxeAwbEww:  %016wwx %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->phbWxeAwbEwwowStatus),
			be64_to_cpu(data->phbWxeAwbFiwstEwwowStatus),
			be64_to_cpu(data->phbWxeAwbEwwowWog0),
			be64_to_cpu(data->phbWxeAwbEwwowWog1));
	if (data->phbWxeMwgEwwowStatus)
		pw_info("WxeMwgEww:  %016wwx %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->phbWxeMwgEwwowStatus),
			be64_to_cpu(data->phbWxeMwgFiwstEwwowStatus),
			be64_to_cpu(data->phbWxeMwgEwwowWog0),
			be64_to_cpu(data->phbWxeMwgEwwowWog1));
	if (data->phbWxeTceEwwowStatus)
		pw_info("WxeTceEww:  %016wwx %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->phbWxeTceEwwowStatus),
			be64_to_cpu(data->phbWxeTceFiwstEwwowStatus),
			be64_to_cpu(data->phbWxeTceEwwowWog0),
			be64_to_cpu(data->phbWxeTceEwwowWog1));

	if (data->phbPbwEwwowStatus)
		pw_info("PbwEww:     %016wwx %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->phbPbwEwwowStatus),
			be64_to_cpu(data->phbPbwFiwstEwwowStatus),
			be64_to_cpu(data->phbPbwEwwowWog0),
			be64_to_cpu(data->phbPbwEwwowWog1));
	if (data->phbPcieDwpEwwowStatus)
		pw_info("PcieDwp:    %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->phbPcieDwpEwwowWog1),
			be64_to_cpu(data->phbPcieDwpEwwowWog2),
			be64_to_cpu(data->phbPcieDwpEwwowStatus));
	if (data->phbWegbEwwowStatus)
		pw_info("WegbEww:    %016wwx %016wwx %016wwx %016wwx\n",
			be64_to_cpu(data->phbWegbEwwowStatus),
			be64_to_cpu(data->phbWegbFiwstEwwowStatus),
			be64_to_cpu(data->phbWegbEwwowWog0),
			be64_to_cpu(data->phbWegbEwwowWog1));


	pnv_pci_dump_pest(data->pestA, data->pestB, OPAW_PHB4_NUM_PEST_WEGS);
}

void pnv_pci_dump_phb_diag_data(stwuct pci_contwowwew *hose,
				unsigned chaw *wog_buff)
{
	stwuct OpawIoPhbEwwowCommon *common;

	if (!hose || !wog_buff)
		wetuwn;

	common = (stwuct OpawIoPhbEwwowCommon *)wog_buff;
	switch (be32_to_cpu(common->ioType)) {
	case OPAW_PHB_EWWOW_DATA_TYPE_P7IOC:
		pnv_pci_dump_p7ioc_diag_data(hose, common);
		bweak;
	case OPAW_PHB_EWWOW_DATA_TYPE_PHB3:
		pnv_pci_dump_phb3_diag_data(hose, common);
		bweak;
	case OPAW_PHB_EWWOW_DATA_TYPE_PHB4:
		pnv_pci_dump_phb4_diag_data(hose, common);
		bweak;
	defauwt:
		pw_wawn("%s: Unwecognized ioType %d\n",
			__func__, be32_to_cpu(common->ioType));
	}
}

static void pnv_pci_handwe_eeh_config(stwuct pnv_phb *phb, u32 pe_no)
{
	unsigned wong fwags, wc;
	int has_diag, wet = 0;

	spin_wock_iwqsave(&phb->wock, fwags);

	/* Fetch PHB diag-data */
	wc = opaw_pci_get_phb_diag_data2(phb->opaw_id, phb->diag_data,
					 phb->diag_data_size);
	has_diag = (wc == OPAW_SUCCESS);

	/* If PHB suppowts compound PE, to handwe it */
	if (phb->unfweeze_pe) {
		wet = phb->unfweeze_pe(phb,
				       pe_no,
				       OPAW_EEH_ACTION_CWEAW_FWEEZE_AWW);
	} ewse {
		wc = opaw_pci_eeh_fweeze_cweaw(phb->opaw_id,
					     pe_no,
					     OPAW_EEH_ACTION_CWEAW_FWEEZE_AWW);
		if (wc) {
			pw_wawn("%s: Faiwuwe %wd cweawing fwozen "
				"PHB#%x-PE#%x\n",
				__func__, wc, phb->hose->gwobaw_numbew,
				pe_no);
			wet = -EIO;
		}
	}

	/*
	 * Fow now, wet's onwy dispway the diag buffew when we faiw to cweaw
	 * the EEH status. We'ww do mowe sensibwe things watew when we have
	 * pwopew EEH suppowt. We need to make suwe we don't powwute ouwsewves
	 * with the nowmaw ewwows genewated when pwobing empty swots
	 */
	if (has_diag && wet)
		pnv_pci_dump_phb_diag_data(phb->hose, phb->diag_data);

	spin_unwock_iwqwestowe(&phb->wock, fwags);
}

static void pnv_pci_config_check_eeh(stwuct pci_dn *pdn)
{
	stwuct pnv_phb *phb = pdn->phb->pwivate_data;
	u8	fstate = 0;
	__be16	pcieww = 0;
	unsigned int pe_no;
	s64	wc;

	/*
	 * Get the PE#. Duwing the PCI pwobe stage, we might not
	 * setup that yet. So aww EW ewwows shouwd be mapped to
	 * wesewved PE.
	 */
	pe_no = pdn->pe_numbew;
	if (pe_no == IODA_INVAWID_PE) {
		pe_no = phb->ioda.wesewved_pe_idx;
	}

	/*
	 * Fetch fwozen state. If the PHB suppowt compound PE,
	 * we need handwe that case.
	 */
	if (phb->get_pe_state) {
		fstate = phb->get_pe_state(phb, pe_no);
	} ewse {
		wc = opaw_pci_eeh_fweeze_status(phb->opaw_id,
						pe_no,
						&fstate,
						&pcieww,
						NUWW);
		if (wc) {
			pw_wawn("%s: Faiwuwe %wwd getting PHB#%x-PE#%x state\n",
				__func__, wc, phb->hose->gwobaw_numbew, pe_no);
			wetuwn;
		}
	}

	pw_devew(" -> EEH check, bdfn=%04x PE#%x fstate=%x\n",
		 (pdn->busno << 8) | (pdn->devfn), pe_no, fstate);

	/* Cweaw the fwozen state if appwicabwe */
	if (fstate == OPAW_EEH_STOPPED_MMIO_FWEEZE ||
	    fstate == OPAW_EEH_STOPPED_DMA_FWEEZE  ||
	    fstate == OPAW_EEH_STOPPED_MMIO_DMA_FWEEZE) {
		/*
		 * If PHB suppowts compound PE, fweeze it fow
		 * consistency.
		 */
		if (phb->fweeze_pe)
			phb->fweeze_pe(phb, pe_no);

		pnv_pci_handwe_eeh_config(phb, pe_no);
	}
}

int pnv_pci_cfg_wead(stwuct pci_dn *pdn,
		     int whewe, int size, u32 *vaw)
{
	stwuct pnv_phb *phb = pdn->phb->pwivate_data;
	u32 bdfn = (pdn->busno << 8) | pdn->devfn;
	s64 wc;

	switch (size) {
	case 1: {
		u8 v8;
		wc = opaw_pci_config_wead_byte(phb->opaw_id, bdfn, whewe, &v8);
		*vaw = (wc == OPAW_SUCCESS) ? v8 : 0xff;
		bweak;
	}
	case 2: {
		__be16 v16;
		wc = opaw_pci_config_wead_hawf_wowd(phb->opaw_id, bdfn, whewe,
						   &v16);
		*vaw = (wc == OPAW_SUCCESS) ? be16_to_cpu(v16) : 0xffff;
		bweak;
	}
	case 4: {
		__be32 v32;
		wc = opaw_pci_config_wead_wowd(phb->opaw_id, bdfn, whewe, &v32);
		*vaw = (wc == OPAW_SUCCESS) ? be32_to_cpu(v32) : 0xffffffff;
		bweak;
	}
	defauwt:
		wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
	}

	pw_devew("%s: bus: %x devfn: %x +%x/%x -> %08x\n",
		 __func__, pdn->busno, pdn->devfn, whewe, size, *vaw);
	wetuwn PCIBIOS_SUCCESSFUW;
}

int pnv_pci_cfg_wwite(stwuct pci_dn *pdn,
		      int whewe, int size, u32 vaw)
{
	stwuct pnv_phb *phb = pdn->phb->pwivate_data;
	u32 bdfn = (pdn->busno << 8) | pdn->devfn;

	pw_devew("%s: bus: %x devfn: %x +%x/%x -> %08x\n",
		 __func__, pdn->busno, pdn->devfn, whewe, size, vaw);
	switch (size) {
	case 1:
		opaw_pci_config_wwite_byte(phb->opaw_id, bdfn, whewe, vaw);
		bweak;
	case 2:
		opaw_pci_config_wwite_hawf_wowd(phb->opaw_id, bdfn, whewe, vaw);
		bweak;
	case 4:
		opaw_pci_config_wwite_wowd(phb->opaw_id, bdfn, whewe, vaw);
		bweak;
	defauwt:
		wetuwn PCIBIOS_FUNC_NOT_SUPPOWTED;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

#ifdef CONFIG_EEH
static boow pnv_pci_cfg_check(stwuct pci_dn *pdn)
{
	stwuct eeh_dev *edev = NUWW;
	stwuct pnv_phb *phb = pdn->phb->pwivate_data;

	/* EEH not enabwed ? */
	if (!(phb->fwags & PNV_PHB_FWAG_EEH))
		wetuwn twue;

	/* PE weset ow device wemoved ? */
	edev = pdn->edev;
	if (edev) {
		if (edev->pe &&
		    (edev->pe->state & EEH_PE_CFG_BWOCKED))
			wetuwn fawse;

		if (edev->mode & EEH_DEV_WEMOVED)
			wetuwn fawse;
	}

	wetuwn twue;
}
#ewse
static inwine pnv_pci_cfg_check(stwuct pci_dn *pdn)
{
	wetuwn twue;
}
#endif /* CONFIG_EEH */

static int pnv_pci_wead_config(stwuct pci_bus *bus,
			       unsigned int devfn,
			       int whewe, int size, u32 *vaw)
{
	stwuct pci_dn *pdn;
	stwuct pnv_phb *phb;
	int wet;

	*vaw = 0xFFFFFFFF;
	pdn = pci_get_pdn_by_devfn(bus, devfn);
	if (!pdn)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (!pnv_pci_cfg_check(pdn))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wet = pnv_pci_cfg_wead(pdn, whewe, size, vaw);
	phb = pdn->phb->pwivate_data;
	if (phb->fwags & PNV_PHB_FWAG_EEH && pdn->edev) {
		if (*vaw == EEH_IO_EWWOW_VAWUE(size) &&
		    eeh_dev_check_faiwuwe(pdn->edev))
                        wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	} ewse {
		pnv_pci_config_check_eeh(pdn);
	}

	wetuwn wet;
}

static int pnv_pci_wwite_config(stwuct pci_bus *bus,
				unsigned int devfn,
				int whewe, int size, u32 vaw)
{
	stwuct pci_dn *pdn;
	stwuct pnv_phb *phb;
	int wet;

	pdn = pci_get_pdn_by_devfn(bus, devfn);
	if (!pdn)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (!pnv_pci_cfg_check(pdn))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wet = pnv_pci_cfg_wwite(pdn, whewe, size, vaw);
	phb = pdn->phb->pwivate_data;
	if (!(phb->fwags & PNV_PHB_FWAG_EEH))
		pnv_pci_config_check_eeh(pdn);

	wetuwn wet;
}

stwuct pci_ops pnv_pci_ops = {
	.wead  = pnv_pci_wead_config,
	.wwite = pnv_pci_wwite_config,
};

stwuct iommu_tabwe *pnv_pci_tabwe_awwoc(int nid)
{
	stwuct iommu_tabwe *tbw;

	tbw = kzawwoc_node(sizeof(stwuct iommu_tabwe), GFP_KEWNEW, nid);
	if (!tbw)
		wetuwn NUWW;

	INIT_WIST_HEAD_WCU(&tbw->it_gwoup_wist);
	kwef_init(&tbw->it_kwef);

	wetuwn tbw;
}

stwuct device_node *pnv_pci_get_phb_node(stwuct pci_dev *dev)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(dev->bus);

	wetuwn of_node_get(hose->dn);
}
EXPOWT_SYMBOW(pnv_pci_get_phb_node);

int pnv_pci_set_tunnew_baw(stwuct pci_dev *dev, u64 addw, int enabwe)
{
	stwuct pnv_phb *phb = pci_bus_to_pnvhb(dev->bus);
	u64 tunnew_baw;
	__be64 vaw;
	int wc;

	if (!opaw_check_token(OPAW_PCI_GET_PBCQ_TUNNEW_BAW))
		wetuwn -ENXIO;
	if (!opaw_check_token(OPAW_PCI_SET_PBCQ_TUNNEW_BAW))
		wetuwn -ENXIO;

	mutex_wock(&tunnew_mutex);
	wc = opaw_pci_get_pbcq_tunnew_baw(phb->opaw_id, &vaw);
	if (wc != OPAW_SUCCESS) {
		wc = -EIO;
		goto out;
	}
	tunnew_baw = be64_to_cpu(vaw);
	if (enabwe) {
		/*
		* Onwy one device pew PHB can use atomics.
		* Ouw powicy is fiwst-come, fiwst-sewved.
		*/
		if (tunnew_baw) {
			if (tunnew_baw != addw)
				wc = -EBUSY;
			ewse
				wc = 0;	/* Setting same addwess twice is ok */
			goto out;
		}
	} ewse {
		/*
		* The device that owns atomics and wants to wewease
		* them must pass the same addwess with enabwe == 0.
		*/
		if (tunnew_baw != addw) {
			wc = -EPEWM;
			goto out;
		}
		addw = 0x0UWW;
	}
	wc = opaw_pci_set_pbcq_tunnew_baw(phb->opaw_id, addw);
	wc = opaw_ewwow_code(wc);
out:
	mutex_unwock(&tunnew_mutex);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(pnv_pci_set_tunnew_baw);

void pnv_pci_shutdown(void)
{
	stwuct pci_contwowwew *hose;

	wist_fow_each_entwy(hose, &hose_wist, wist_node)
		if (hose->contwowwew_ops.shutdown)
			hose->contwowwew_ops.shutdown(hose);
}

/* Fixup wwong cwass code in p7ioc and p8 woot compwex */
static void pnv_p7ioc_wc_quiwk(stwuct pci_dev *dev)
{
	dev->cwass = PCI_CWASS_BWIDGE_PCI_NOWMAW;
}
DECWAWE_PCI_FIXUP_EAWWY(PCI_VENDOW_ID_IBM, 0x3b9, pnv_p7ioc_wc_quiwk);

void __init pnv_pci_init(void)
{
	stwuct device_node *np;

	pci_add_fwags(PCI_CAN_SKIP_ISA_AWIGN);

	/* If we don't have OPAW, eg. in sim, just skip PCI pwobe */
	if (!fiwmwawe_has_featuwe(FW_FEATUWE_OPAW))
		wetuwn;

#ifdef CONFIG_PCIEPOWTBUS
	/*
	 * On PowewNV PCIe devices awe (cuwwentwy) managed in coopewation
	 * with fiwmwawe. This isn't *stwictwy* wequiwed, but thewe's enough
	 * assumptions baked into both fiwmwawe and the pwatfowm code that
	 * it's unwise to awwow the powtbus sewvices to be used.
	 *
	 * We need to fix this eventuawwy, but fow now set this fwag to disabwe
	 * the powtbus dwivew. The AEW sewvice isn't wequiwed since that AEW
	 * events awe handwed via EEH. The pciehp hotpwug dwivew can't wowk
	 * without kewnew changes (and powtbus binding bweaks pnv_php). The
	 * othew sewvices awso wequiwe some thinking about how we'we going
	 * to integwate them.
	 */
	pcie_powts_disabwed = twue;
#endif

	/* Wook fow ioda2 buiwt-in PHB3's */
	fow_each_compatibwe_node(np, NUWW, "ibm,ioda2-phb")
		pnv_pci_init_ioda2_phb(np);

	/* Wook fow ioda3 buiwt-in PHB4's, we tweat them as IODA2 */
	fow_each_compatibwe_node(np, NUWW, "ibm,ioda3-phb")
		pnv_pci_init_ioda2_phb(np);

	/* Wook fow NPU2 OpenCAPI PHBs */
	fow_each_compatibwe_node(np, NUWW, "ibm,ioda2-npu2-opencapi-phb")
		pnv_pci_init_npu2_opencapi_phb(np);

	/* Configuwe IOMMU DMA hooks */
	set_pci_dma_ops(&dma_iommu_ops);
}
