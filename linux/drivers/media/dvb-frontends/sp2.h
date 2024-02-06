/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * CIMaX SP2/HF CI dwivew
 *
 * Copywight (C) 2014 Owwi Sawonen <owwi.sawonen@iki.fi>
 */

#ifndef SP2_H
#define SP2_H

#incwude <media/dvb_ca_en50221.h>

/*
 * I2C addwess
 * 0x40 (powt 0)
 * 0x41 (powt 1)
 */
stwuct sp2_config {
	/* dvb_adaptew to attach the ci to */
	stwuct dvb_adaptew *dvb_adap;

	/* function ci_contwow handwes the device specific ci ops */
	void *ci_contwow;

	/* pwiv is passed back to function ci_contwow */
	void *pwiv;
};

extewn int sp2_ci_wead_attwibute_mem(stwuct dvb_ca_en50221 *en50221,
					int swot, int addw);
extewn int sp2_ci_wwite_attwibute_mem(stwuct dvb_ca_en50221 *en50221,
					int swot, int addw, u8 data);
extewn int sp2_ci_wead_cam_contwow(stwuct dvb_ca_en50221 *en50221,
					int swot, u8 addw);
extewn int sp2_ci_wwite_cam_contwow(stwuct dvb_ca_en50221 *en50221,
					int swot, u8 addw, u8 data);
extewn int sp2_ci_swot_weset(stwuct dvb_ca_en50221 *en50221, int swot);
extewn int sp2_ci_swot_shutdown(stwuct dvb_ca_en50221 *en50221, int swot);
extewn int sp2_ci_swot_ts_enabwe(stwuct dvb_ca_en50221 *en50221, int swot);
extewn int sp2_ci_poww_swot_status(stwuct dvb_ca_en50221 *en50221,
					int swot, int open);

#endif
