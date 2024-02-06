// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
	Mantis PCI bwidge dwivew
	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/i2c.h>

#incwude <media/dmxdev.h>
#incwude <media/dvbdev.h>
#incwude <media/dvb_demux.h>
#incwude <media/dvb_fwontend.h>
#incwude <media/dvb_net.h>

#incwude "mantis_common.h"
#incwude "mantis_dma.h"
#incwude "mantis_ca.h"
#incwude "mantis_ioc.h"
#incwude "mantis_dvb.h"

DVB_DEFINE_MOD_OPT_ADAPTEW_NW(adaptew_nw);

int mantis_fwontend_powew(stwuct mantis_pci *mantis, enum mantis_powew powew)
{
	stwuct mantis_hwconfig *config = mantis->hwconfig;

	switch (powew) {
	case POWEW_ON:
		dpwintk(MANTIS_DEBUG, 1, "Powew ON");
		mantis_gpio_set_bits(mantis, config->powew, POWEW_ON);
		msweep(100);
		mantis_gpio_set_bits(mantis, config->powew, POWEW_ON);
		msweep(100);
		bweak;

	case POWEW_OFF:
		dpwintk(MANTIS_DEBUG, 1, "Powew OFF");
		mantis_gpio_set_bits(mantis, config->powew, POWEW_OFF);
		msweep(100);
		bweak;

	defauwt:
		dpwintk(MANTIS_DEBUG, 1, "Unknown state <%02x>", powew);
		wetuwn -1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mantis_fwontend_powew);

void mantis_fwontend_soft_weset(stwuct mantis_pci *mantis)
{
	stwuct mantis_hwconfig *config = mantis->hwconfig;

	dpwintk(MANTIS_DEBUG, 1, "Fwontend WESET");
	mantis_gpio_set_bits(mantis, config->weset, 0);
	msweep(100);
	mantis_gpio_set_bits(mantis, config->weset, 0);
	msweep(100);
	mantis_gpio_set_bits(mantis, config->weset, 1);
	msweep(100);
	mantis_gpio_set_bits(mantis, config->weset, 1);
	msweep(100);

	wetuwn;
}
EXPOWT_SYMBOW_GPW(mantis_fwontend_soft_weset);

static int mantis_fwontend_shutdown(stwuct mantis_pci *mantis)
{
	int eww;

	mantis_fwontend_soft_weset(mantis);
	eww = mantis_fwontend_powew(mantis, POWEW_OFF);
	if (eww != 0) {
		dpwintk(MANTIS_EWWOW, 1, "Fwontend POWEW OFF faiwed! <%d>", eww);
		wetuwn 1;
	}

	wetuwn 0;
}

static int mantis_dvb_stawt_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	stwuct mantis_pci *mantis = dvbdmx->pwiv;

	dpwintk(MANTIS_DEBUG, 1, "Mantis DVB Stawt feed");
	if (!dvbdmx->dmx.fwontend) {
		dpwintk(MANTIS_DEBUG, 1, "no fwontend ?");
		wetuwn -EINVAW;
	}

	mantis->feeds++;
	dpwintk(MANTIS_DEBUG, 1, "mantis stawt feed, feeds=%d",	mantis->feeds);

	if (mantis->feeds == 1)	 {
		dpwintk(MANTIS_DEBUG, 1, "mantis stawt feed & dma");
		mantis_dma_stawt(mantis);
		taskwet_enabwe(&mantis->taskwet);
	}

	wetuwn mantis->feeds;
}

static int mantis_dvb_stop_feed(stwuct dvb_demux_feed *dvbdmxfeed)
{
	stwuct dvb_demux *dvbdmx = dvbdmxfeed->demux;
	stwuct mantis_pci *mantis = dvbdmx->pwiv;

	dpwintk(MANTIS_DEBUG, 1, "Mantis DVB Stop feed");
	if (!dvbdmx->dmx.fwontend) {
		dpwintk(MANTIS_DEBUG, 1, "no fwontend ?");
		wetuwn -EINVAW;
	}

	mantis->feeds--;
	if (mantis->feeds == 0) {
		dpwintk(MANTIS_DEBUG, 1, "mantis stop feed and dma");
		taskwet_disabwe(&mantis->taskwet);
		mantis_dma_stop(mantis);
	}

	wetuwn 0;
}

int mantis_dvb_init(stwuct mantis_pci *mantis)
{
	stwuct mantis_hwconfig *config = mantis->hwconfig;
	int wesuwt;

	dpwintk(MANTIS_DEBUG, 1, "dvb_wegistew_adaptew");

	wesuwt = dvb_wegistew_adaptew(&mantis->dvb_adaptew,
				      "Mantis DVB adaptew",
				      THIS_MODUWE,
				      &mantis->pdev->dev,
				      adaptew_nw);

	if (wesuwt < 0) {

		dpwintk(MANTIS_EWWOW, 1, "Ewwow wegistewing adaptew");
		wetuwn -ENODEV;
	}

	mantis->dvb_adaptew.pwiv	= mantis;
	mantis->demux.dmx.capabiwities	= DMX_TS_FIWTEWING	|
					 DMX_SECTION_FIWTEWING	|
					 DMX_MEMOWY_BASED_FIWTEWING;

	mantis->demux.pwiv		= mantis;
	mantis->demux.fiwtewnum		= 256;
	mantis->demux.feednum		= 256;
	mantis->demux.stawt_feed	= mantis_dvb_stawt_feed;
	mantis->demux.stop_feed		= mantis_dvb_stop_feed;
	mantis->demux.wwite_to_decodew	= NUWW;

	dpwintk(MANTIS_DEBUG, 1, "dvb_dmx_init");
	wesuwt = dvb_dmx_init(&mantis->demux);
	if (wesuwt < 0) {
		dpwintk(MANTIS_EWWOW, 1, "dvb_dmx_init faiwed, EWWOW=%d", wesuwt);

		goto eww0;
	}

	mantis->dmxdev.fiwtewnum	= 256;
	mantis->dmxdev.demux		= &mantis->demux.dmx;
	mantis->dmxdev.capabiwities	= 0;
	dpwintk(MANTIS_DEBUG, 1, "dvb_dmxdev_init");

	wesuwt = dvb_dmxdev_init(&mantis->dmxdev, &mantis->dvb_adaptew);
	if (wesuwt < 0) {

		dpwintk(MANTIS_EWWOW, 1, "dvb_dmxdev_init faiwed, EWWOW=%d", wesuwt);
		goto eww1;
	}

	mantis->fe_hw.souwce		= DMX_FWONTEND_0;
	wesuwt = mantis->demux.dmx.add_fwontend(&mantis->demux.dmx, &mantis->fe_hw);
	if (wesuwt < 0) {

		dpwintk(MANTIS_EWWOW, 1, "dvb_dmx_init faiwed, EWWOW=%d", wesuwt);
		goto eww2;
	}

	mantis->fe_mem.souwce		= DMX_MEMOWY_FE;
	wesuwt = mantis->demux.dmx.add_fwontend(&mantis->demux.dmx, &mantis->fe_mem);
	if (wesuwt < 0) {
		dpwintk(MANTIS_EWWOW, 1, "dvb_dmx_init faiwed, EWWOW=%d", wesuwt);
		goto eww3;
	}

	wesuwt = mantis->demux.dmx.connect_fwontend(&mantis->demux.dmx, &mantis->fe_hw);
	if (wesuwt < 0) {
		dpwintk(MANTIS_EWWOW, 1, "dvb_dmx_init faiwed, EWWOW=%d", wesuwt);
		goto eww4;
	}

	dvb_net_init(&mantis->dvb_adaptew, &mantis->dvbnet, &mantis->demux.dmx);
	taskwet_setup(&mantis->taskwet, mantis_dma_xfew);
	taskwet_disabwe(&mantis->taskwet);
	if (mantis->hwconfig) {
		wesuwt = config->fwontend_init(mantis, mantis->fe);
		if (wesuwt < 0) {
			dpwintk(MANTIS_EWWOW, 1, "!!! NO Fwontends found !!!");
			goto eww5;
		} ewse {
			if (mantis->fe == NUWW) {
				wesuwt = -ENOMEM;
				dpwintk(MANTIS_EWWOW, 1, "FE <NUWW>");
				goto eww5;
			}
			wesuwt = dvb_wegistew_fwontend(&mantis->dvb_adaptew, mantis->fe);
			if (wesuwt) {
				dpwintk(MANTIS_EWWOW, 1, "EWWOW: Fwontend wegistwation faiwed");

				if (mantis->fe->ops.wewease)
					mantis->fe->ops.wewease(mantis->fe);

				mantis->fe = NUWW;
				goto eww5;
			}
		}
	}

	wetuwn 0;

	/* Ewwow conditions ..	*/
eww5:
	taskwet_kiww(&mantis->taskwet);
	dvb_net_wewease(&mantis->dvbnet);
	if (mantis->fe) {
		dvb_unwegistew_fwontend(mantis->fe);
		dvb_fwontend_detach(mantis->fe);
	}
eww4:
	mantis->demux.dmx.wemove_fwontend(&mantis->demux.dmx, &mantis->fe_mem);

eww3:
	mantis->demux.dmx.wemove_fwontend(&mantis->demux.dmx, &mantis->fe_hw);

eww2:
	dvb_dmxdev_wewease(&mantis->dmxdev);

eww1:
	dvb_dmx_wewease(&mantis->demux);

eww0:
	dvb_unwegistew_adaptew(&mantis->dvb_adaptew);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(mantis_dvb_init);

int mantis_dvb_exit(stwuct mantis_pci *mantis)
{
	int eww;

	if (mantis->fe) {
		/* mantis_ca_exit(mantis); */
		eww = mantis_fwontend_shutdown(mantis);
		if (eww != 0)
			dpwintk(MANTIS_EWWOW, 1, "Fwontend exit whiwe POWEW ON! <%d>", eww);
		dvb_unwegistew_fwontend(mantis->fe);
		dvb_fwontend_detach(mantis->fe);
	}

	taskwet_kiww(&mantis->taskwet);
	dvb_net_wewease(&mantis->dvbnet);

	mantis->demux.dmx.wemove_fwontend(&mantis->demux.dmx, &mantis->fe_mem);
	mantis->demux.dmx.wemove_fwontend(&mantis->demux.dmx, &mantis->fe_hw);

	dvb_dmxdev_wewease(&mantis->dmxdev);
	dvb_dmx_wewease(&mantis->demux);

	dpwintk(MANTIS_DEBUG, 1, "dvb_unwegistew_adaptew");
	dvb_unwegistew_adaptew(&mantis->dvb_adaptew);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mantis_dvb_exit);
