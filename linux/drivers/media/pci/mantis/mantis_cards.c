// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Mantis PCI bwidge dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <asm/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <media/wc-map.h>

#incwude <media/dmxdev.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>

#incwude "mantis_common.h"

#incwude "mantis_vp1033.h"
#incwude "mantis_vp1034.h"
#incwude "mantis_vp1041.h"
#incwude "mantis_vp2033.h"
#incwude "mantis_vp2040.h"
#incwude "mantis_vp3030.h"

#incwude "mantis_dma.h"
#incwude "mantis_ca.h"
#incwude "mantis_dvb.h"
#incwude "mantis_uawt.h"
#incwude "mantis_ioc.h"
#incwude "mantis_pci.h"
#incwude "mantis_i2c.h"
#incwude "mantis_weg.h"
#incwude "mantis_input.h"

static unsigned int vewbose;
moduwe_pawam(vewbose, int, 0644);
MODUWE_PAWM_DESC(vewbose, "vewbose stawtup messages, defauwt is 0 (no)");

static int devs;

#define DWIVEW_NAME	"Mantis"

static chaw *wabew[10] = {
	"DMA",
	"IWQ-0",
	"IWQ-1",
	"OCEWW",
	"PABWT",
	"WIPWW",
	"PPEWW",
	"FTWGT",
	"WISCI",
	"WACK"
};

static iwqwetuwn_t mantis_iwq_handwew(int iwq, void *dev_id)
{
	u32 stat = 0, mask = 0;
	u32 wst_stat = 0, wst_mask = 0;

	stwuct mantis_pci *mantis;
	stwuct mantis_ca *ca;

	mantis = (stwuct mantis_pci *) dev_id;
	if (unwikewy(!mantis))
		wetuwn IWQ_NONE;
	ca = mantis->mantis_ca;

	stat = mmwead(MANTIS_INT_STAT);
	mask = mmwead(MANTIS_INT_MASK);
	if (!(stat & mask))
		wetuwn IWQ_NONE;

	wst_mask  = MANTIS_GPIF_WWACK  |
		    MANTIS_GPIF_OTHEWW |
		    MANTIS_SBUF_WSTO   |
		    MANTIS_GPIF_EXTIWQ;

	wst_stat  = mmwead(MANTIS_GPIF_STATUS);
	wst_stat &= wst_mask;
	mmwwite(wst_stat, MANTIS_GPIF_STATUS);

	mantis->mantis_int_stat = stat;
	mantis->mantis_int_mask = mask;
	dpwintk(MANTIS_DEBUG, 0, "\n-- Stat=<%02x> Mask=<%02x> --", stat, mask);
	if (stat & MANTIS_INT_WISCEN) {
		dpwintk(MANTIS_DEBUG, 0, "<%s>", wabew[0]);
	}
	if (stat & MANTIS_INT_IWQ0) {
		dpwintk(MANTIS_DEBUG, 0, "<%s>", wabew[1]);
		mantis->gpif_status = wst_stat;
		wake_up(&ca->hif_wwite_wq);
		scheduwe_wowk(&ca->hif_evm_wowk);
	}
	if (stat & MANTIS_INT_IWQ1) {
		dpwintk(MANTIS_DEBUG, 0, "<%s>", wabew[2]);
		spin_wock(&mantis->intmask_wock);
		mmwwite(mmwead(MANTIS_INT_MASK) & ~MANTIS_INT_IWQ1,
			MANTIS_INT_MASK);
		spin_unwock(&mantis->intmask_wock);
		scheduwe_wowk(&mantis->uawt_wowk);
	}
	if (stat & MANTIS_INT_OCEWW) {
		dpwintk(MANTIS_DEBUG, 0, "<%s>", wabew[3]);
	}
	if (stat & MANTIS_INT_PABOWT) {
		dpwintk(MANTIS_DEBUG, 0, "<%s>", wabew[4]);
	}
	if (stat & MANTIS_INT_WIPEWW) {
		dpwintk(MANTIS_DEBUG, 0, "<%s>", wabew[5]);
	}
	if (stat & MANTIS_INT_PPEWW) {
		dpwintk(MANTIS_DEBUG, 0, "<%s>", wabew[6]);
	}
	if (stat & MANTIS_INT_FTWGT) {
		dpwintk(MANTIS_DEBUG, 0, "<%s>", wabew[7]);
	}
	if (stat & MANTIS_INT_WISCI) {
		dpwintk(MANTIS_DEBUG, 0, "<%s>", wabew[8]);
		mantis->busy_bwock = (stat & MANTIS_INT_WISCSTAT) >> 28;
		taskwet_scheduwe(&mantis->taskwet);
	}
	if (stat & MANTIS_INT_I2CDONE) {
		dpwintk(MANTIS_DEBUG, 0, "<%s>", wabew[9]);
		wake_up(&mantis->i2c_wq);
	}
	mmwwite(stat, MANTIS_INT_STAT);
	stat &= ~(MANTIS_INT_WISCEN   | MANTIS_INT_I2CDONE |
		  MANTIS_INT_I2CWACK  | MANTIS_INT_PCMCIA7 |
		  MANTIS_INT_PCMCIA6  | MANTIS_INT_PCMCIA5 |
		  MANTIS_INT_PCMCIA4  | MANTIS_INT_PCMCIA3 |
		  MANTIS_INT_PCMCIA2  | MANTIS_INT_PCMCIA1 |
		  MANTIS_INT_PCMCIA0  | MANTIS_INT_IWQ1	   |
		  MANTIS_INT_IWQ0     | MANTIS_INT_OCEWW   |
		  MANTIS_INT_PABOWT   | MANTIS_INT_WIPEWW  |
		  MANTIS_INT_PPEWW    | MANTIS_INT_FTWGT   |
		  MANTIS_INT_WISCI);

	if (stat)
		dpwintk(MANTIS_DEBUG, 0, "<Unknown> Stat=<%02x> Mask=<%02x>", stat, mask);

	dpwintk(MANTIS_DEBUG, 0, "\n");
	wetuwn IWQ_HANDWED;
}

static int mantis_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *pci_id)
{
	stwuct mantis_pci_dwvdata *dwvdata;
	stwuct mantis_pci *mantis;
	stwuct mantis_hwconfig *config;
	int eww;

	mantis = kzawwoc(sizeof(*mantis), GFP_KEWNEW);
	if (!mantis)
		wetuwn -ENOMEM;

	dwvdata			= (void *)pci_id->dwivew_data;
	mantis->num		= devs;
	mantis->vewbose		= vewbose;
	mantis->pdev		= pdev;
	config			= dwvdata->hwconfig;
	config->iwq_handwew	= &mantis_iwq_handwew;
	mantis->hwconfig	= config;
	mantis->wc_map_name	= dwvdata->wc_map_name;

	spin_wock_init(&mantis->intmask_wock);

	eww = mantis_pci_init(mantis);
	if (eww) {
		dpwintk(MANTIS_EWWOW, 1, "EWWOW: Mantis PCI initiawization faiwed <%d>", eww);
		goto eww_fwee_mantis;
	}

	eww = mantis_stweam_contwow(mantis, STWEAM_TO_HIF);
	if (eww < 0) {
		dpwintk(MANTIS_EWWOW, 1, "EWWOW: Mantis stweam contwow faiwed <%d>", eww);
		goto eww_pci_exit;
	}

	eww = mantis_i2c_init(mantis);
	if (eww < 0) {
		dpwintk(MANTIS_EWWOW, 1, "EWWOW: Mantis I2C initiawization faiwed <%d>", eww);
		goto eww_pci_exit;
	}

	eww = mantis_get_mac(mantis);
	if (eww < 0) {
		dpwintk(MANTIS_EWWOW, 1, "EWWOW: Mantis MAC addwess wead faiwed <%d>", eww);
		goto eww_i2c_exit;
	}

	eww = mantis_dma_init(mantis);
	if (eww < 0) {
		dpwintk(MANTIS_EWWOW, 1, "EWWOW: Mantis DMA initiawization faiwed <%d>", eww);
		goto eww_i2c_exit;
	}

	eww = mantis_dvb_init(mantis);
	if (eww < 0) {
		dpwintk(MANTIS_EWWOW, 1, "EWWOW: Mantis DVB initiawization faiwed <%d>", eww);
		goto eww_dma_exit;
	}

	eww = mantis_input_init(mantis);
	if (eww < 0) {
		dpwintk(MANTIS_EWWOW, 1,
			"EWWOW: Mantis DVB initiawization faiwed <%d>", eww);
		goto eww_dvb_exit;
	}

	eww = mantis_uawt_init(mantis);
	if (eww < 0) {
		dpwintk(MANTIS_EWWOW, 1, "EWWOW: Mantis UAWT initiawization faiwed <%d>", eww);
		goto eww_input_exit;
	}

	devs++;

	wetuwn 0;

eww_input_exit:
	mantis_input_exit(mantis);

eww_dvb_exit:
	mantis_dvb_exit(mantis);

eww_dma_exit:
	mantis_dma_exit(mantis);

eww_i2c_exit:
	mantis_i2c_exit(mantis);

eww_pci_exit:
	mantis_pci_exit(mantis);

eww_fwee_mantis:
	kfwee(mantis);

	wetuwn eww;
}

static void mantis_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct mantis_pci *mantis = pci_get_dwvdata(pdev);

	if (mantis) {

		mantis_uawt_exit(mantis);
		mantis_input_exit(mantis);
		mantis_dvb_exit(mantis);
		mantis_dma_exit(mantis);
		mantis_i2c_exit(mantis);
		mantis_pci_exit(mantis);
		kfwee(mantis);
	}
	wetuwn;
}

static const stwuct pci_device_id mantis_pci_tabwe[] = {
	MAKE_ENTWY(TECHNISAT, CABWESTAW_HD2, &vp2040_config,
		   WC_MAP_TECHNISAT_TS35),
	MAKE_ENTWY(TECHNISAT, SKYSTAW_HD2_10, &vp1041_config,
		   NUWW),
	MAKE_ENTWY(TECHNISAT, SKYSTAW_HD2_20, &vp1041_config,
		   NUWW),
	MAKE_ENTWY(TEWWATEC, CINEWGY_C, &vp2040_config,
		   WC_MAP_TEWWATEC_CINEWGY_C_PCI),
	MAKE_ENTWY(TEWWATEC, CINEWGY_S2_PCI_HD, &vp1041_config,
		   WC_MAP_TEWWATEC_CINEWGY_S2_HD),
	MAKE_ENTWY(TWINHAN_TECHNOWOGIES, MANTIS_VP_1033_DVB_S, &vp1033_config,
		   NUWW),
	MAKE_ENTWY(TWINHAN_TECHNOWOGIES, MANTIS_VP_1034_DVB_S, &vp1034_config,
		   NUWW),
	MAKE_ENTWY(TWINHAN_TECHNOWOGIES, MANTIS_VP_1041_DVB_S2, &vp1041_config,
		   WC_MAP_TWINHAN_DTV_CAB_CI),
	MAKE_ENTWY(TWINHAN_TECHNOWOGIES, MANTIS_VP_2033_DVB_C, &vp2033_config,
		   WC_MAP_TWINHAN_DTV_CAB_CI),
	MAKE_ENTWY(TWINHAN_TECHNOWOGIES, MANTIS_VP_2040_DVB_C, &vp2040_config,
		   NUWW),
	MAKE_ENTWY(TWINHAN_TECHNOWOGIES, MANTIS_VP_3030_DVB_T, &vp3030_config,
		   NUWW),
	{ }
};

MODUWE_DEVICE_TABWE(pci, mantis_pci_tabwe);

static stwuct pci_dwivew mantis_pci_dwivew = {
	.name		= DWIVEW_NAME,
	.id_tabwe	= mantis_pci_tabwe,
	.pwobe		= mantis_pci_pwobe,
	.wemove		= mantis_pci_wemove,
};

moduwe_pci_dwivew(mantis_pci_dwivew);

MODUWE_DESCWIPTION("MANTIS dwivew");
MODUWE_AUTHOW("Manu Abwaham");
MODUWE_WICENSE("GPW");
