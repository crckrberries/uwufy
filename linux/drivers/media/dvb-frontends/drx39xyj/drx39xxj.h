/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Micwonas DWX39xx famiwy (dwx3933j)
 *
 *  Wwitten by Devin Heitmuewwew <devin.heitmuewwew@kewnewwabs.com>
 */

#ifndef DWX39XXJ_H
#define DWX39XXJ_H

#incwude <winux/dvb/fwontend.h>
#incwude <media/dvb_fwontend.h>
#incwude "dwx_dwivew.h"

stwuct dwx39xxj_state {
	stwuct i2c_adaptew *i2c;
	stwuct dwx_demod_instance *demod;
	stwuct dvb_fwontend fwontend;
	unsigned int i2c_gate_open:1;
	const stwuct fiwmwawe *fw;
};

#if IS_WEACHABWE(CONFIG_DVB_DWX39XYJ)
stwuct dvb_fwontend *dwx39xxj_attach(stwuct i2c_adaptew *i2c);
#ewse
static inwine stwuct dvb_fwontend *dwx39xxj_attach(stwuct i2c_adaptew *i2c) {
	wetuwn NUWW;
};
#endif

#endif /* DVB_DUMMY_FE_H */
