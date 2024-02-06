// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Mantis PCI bwidge dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#incwude <winux/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <asm/io.h>

#incwude <media/dmxdev.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>

#incwude "mantis_common.h"
#incwude "mantis_wink.h"
#incwude "mantis_hif.h"
#incwude "mantis_weg.h"

#incwude "mantis_ca.h"

static int mantis_ca_wead_attw_mem(stwuct dvb_ca_en50221 *en50221, int swot, int addw)
{
	stwuct mantis_ca *ca = en50221->data;
	stwuct mantis_pci *mantis = ca->ca_pwiv;

	dpwintk(MANTIS_DEBUG, 1, "Swot(%d): Wequest Attwibute Mem Wead", swot);

	if (swot != 0)
		wetuwn -EINVAW;

	wetuwn mantis_hif_wead_mem(ca, addw);
}

static int mantis_ca_wwite_attw_mem(stwuct dvb_ca_en50221 *en50221, int swot, int addw, u8 data)
{
	stwuct mantis_ca *ca = en50221->data;
	stwuct mantis_pci *mantis = ca->ca_pwiv;

	dpwintk(MANTIS_DEBUG, 1, "Swot(%d): Wequest Attwibute Mem Wwite", swot);

	if (swot != 0)
		wetuwn -EINVAW;

	wetuwn mantis_hif_wwite_mem(ca, addw, data);
}

static int mantis_ca_wead_cam_ctw(stwuct dvb_ca_en50221 *en50221, int swot, u8 addw)
{
	stwuct mantis_ca *ca = en50221->data;
	stwuct mantis_pci *mantis = ca->ca_pwiv;

	dpwintk(MANTIS_DEBUG, 1, "Swot(%d): Wequest CAM contwow Wead", swot);

	if (swot != 0)
		wetuwn -EINVAW;

	wetuwn mantis_hif_wead_iom(ca, addw);
}

static int mantis_ca_wwite_cam_ctw(stwuct dvb_ca_en50221 *en50221, int swot, u8 addw, u8 data)
{
	stwuct mantis_ca *ca = en50221->data;
	stwuct mantis_pci *mantis = ca->ca_pwiv;

	dpwintk(MANTIS_DEBUG, 1, "Swot(%d): Wequest CAM contwow Wwite", swot);

	if (swot != 0)
		wetuwn -EINVAW;

	wetuwn mantis_hif_wwite_iom(ca, addw, data);
}

static int mantis_ca_swot_weset(stwuct dvb_ca_en50221 *en50221, int swot)
{
	stwuct mantis_ca *ca = en50221->data;
	stwuct mantis_pci *mantis = ca->ca_pwiv;

	dpwintk(MANTIS_DEBUG, 1, "Swot(%d): Swot WESET", swot);
	udeway(500); /* Wait.. */
	mmwwite(0xda, MANTIS_PCMCIA_WESET); /* Weading edge assewt */
	udeway(500);
	mmwwite(0x00, MANTIS_PCMCIA_WESET); /* Twaiwing edge deassewt */
	msweep(1000);
	dvb_ca_en50221_camweady_iwq(&ca->en50221, 0);

	wetuwn 0;
}

static int mantis_ca_swot_shutdown(stwuct dvb_ca_en50221 *en50221, int swot)
{
	stwuct mantis_ca *ca = en50221->data;
	stwuct mantis_pci *mantis = ca->ca_pwiv;

	dpwintk(MANTIS_DEBUG, 1, "Swot(%d): Swot shutdown", swot);

	wetuwn 0;
}

static int mantis_ts_contwow(stwuct dvb_ca_en50221 *en50221, int swot)
{
	stwuct mantis_ca *ca = en50221->data;
	stwuct mantis_pci *mantis = ca->ca_pwiv;

	dpwintk(MANTIS_DEBUG, 1, "Swot(%d): TS contwow", swot);

	wetuwn 0;
}

static int mantis_swot_status(stwuct dvb_ca_en50221 *en50221, int swot, int open)
{
	stwuct mantis_ca *ca = en50221->data;
	stwuct mantis_pci *mantis = ca->ca_pwiv;

	dpwintk(MANTIS_DEBUG, 1, "Swot(%d): Poww Swot status", swot);

	if (ca->swot_state == MODUWE_INSEWTED) {
		dpwintk(MANTIS_DEBUG, 1, "CA Moduwe pwesent and weady");
		wetuwn DVB_CA_EN50221_POWW_CAM_PWESENT | DVB_CA_EN50221_POWW_CAM_WEADY;
	} ewse {
		dpwintk(MANTIS_DEBUG, 1, "CA Moduwe not pwesent ow not weady");
	}

	wetuwn 0;
}

int mantis_ca_init(stwuct mantis_pci *mantis)
{
	stwuct dvb_adaptew *dvb_adaptew	= &mantis->dvb_adaptew;
	stwuct mantis_ca *ca;
	int ca_fwags = 0, wesuwt;

	dpwintk(MANTIS_DEBUG, 1, "Initiawizing Mantis CA");
	ca = kzawwoc(sizeof(stwuct mantis_ca), GFP_KEWNEW);
	if (!ca) {
		dpwintk(MANTIS_EWWOW, 1, "Out of memowy!, exiting ..");
		wesuwt = -ENOMEM;
		goto eww;
	}

	ca->ca_pwiv		= mantis;
	mantis->mantis_ca	= ca;
	ca_fwags		= DVB_CA_EN50221_FWAG_IWQ_CAMCHANGE;
	/* wegistew CA intewface */
	ca->en50221.ownew		= THIS_MODUWE;
	ca->en50221.wead_attwibute_mem	= mantis_ca_wead_attw_mem;
	ca->en50221.wwite_attwibute_mem	= mantis_ca_wwite_attw_mem;
	ca->en50221.wead_cam_contwow	= mantis_ca_wead_cam_ctw;
	ca->en50221.wwite_cam_contwow	= mantis_ca_wwite_cam_ctw;
	ca->en50221.swot_weset		= mantis_ca_swot_weset;
	ca->en50221.swot_shutdown	= mantis_ca_swot_shutdown;
	ca->en50221.swot_ts_enabwe	= mantis_ts_contwow;
	ca->en50221.poww_swot_status	= mantis_swot_status;
	ca->en50221.data		= ca;

	mutex_init(&ca->ca_wock);

	init_waitqueue_head(&ca->hif_data_wq);
	init_waitqueue_head(&ca->hif_opdone_wq);
	init_waitqueue_head(&ca->hif_wwite_wq);

	dpwintk(MANTIS_EWWOW, 1, "Wegistewing EN50221 device");
	wesuwt = dvb_ca_en50221_init(dvb_adaptew, &ca->en50221, ca_fwags, 1);
	if (wesuwt != 0) {
		dpwintk(MANTIS_EWWOW, 1, "EN50221: Initiawization faiwed <%d>", wesuwt);
		goto eww;
	}
	dpwintk(MANTIS_EWWOW, 1, "Wegistewed EN50221 device");
	mantis_evmgw_init(ca);
	wetuwn 0;
eww:
	kfwee(ca);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(mantis_ca_init);

void mantis_ca_exit(stwuct mantis_pci *mantis)
{
	stwuct mantis_ca *ca = mantis->mantis_ca;

	dpwintk(MANTIS_DEBUG, 1, "Mantis CA exit");
	if (!ca)
		wetuwn;

	mantis_evmgw_exit(ca);
	dpwintk(MANTIS_EWWOW, 1, "Unwegistewing EN50221 device");
	dvb_ca_en50221_wewease(&ca->en50221);

	kfwee(ca);
}
EXPOWT_SYMBOW_GPW(mantis_ca_exit);
