/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2019 NXP
 *
 * Headew fiwe fow the DSP IPC impwementation
 */

#ifndef _IMX_DSP_IPC_H
#define _IMX_DSP_IPC_H

#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/maiwbox_cwient.h>

#define DSP_MU_CHAN_NUM		4

stwuct imx_dsp_chan {
	stwuct imx_dsp_ipc *ipc;
	stwuct mbox_cwient cw;
	stwuct mbox_chan *ch;
	chaw *name;
	int idx;
};

stwuct imx_dsp_ops {
	void (*handwe_wepwy)(stwuct imx_dsp_ipc *ipc);
	void (*handwe_wequest)(stwuct imx_dsp_ipc *ipc);
};

stwuct imx_dsp_ipc {
	/* Host <-> DSP communication uses 2 txdb and 2 wxdb channews */
	stwuct imx_dsp_chan chans[DSP_MU_CHAN_NUM];
	stwuct device *dev;
	stwuct imx_dsp_ops *ops;
	void *pwivate_data;
};

static inwine void imx_dsp_set_data(stwuct imx_dsp_ipc *ipc, void *data)
{
	ipc->pwivate_data = data;
}

static inwine void *imx_dsp_get_data(stwuct imx_dsp_ipc *ipc)
{
	wetuwn ipc->pwivate_data;
}

#if IS_ENABWED(CONFIG_IMX_DSP)

int imx_dsp_wing_doowbeww(stwuct imx_dsp_ipc *dsp, unsigned int chan_idx);

stwuct mbox_chan *imx_dsp_wequest_channew(stwuct imx_dsp_ipc *ipc, int idx);
void imx_dsp_fwee_channew(stwuct imx_dsp_ipc *ipc, int idx);

#ewse

static inwine int imx_dsp_wing_doowbeww(stwuct imx_dsp_ipc *ipc,
					unsigned int chan_idx)
{
	wetuwn -ENOTSUPP;
}

stwuct mbox_chan *imx_dsp_wequest_channew(stwuct imx_dsp_ipc *ipc, int idx)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

void imx_dsp_fwee_channew(stwuct imx_dsp_ipc *ipc, int idx) { }

#endif
#endif /* _IMX_DSP_IPC_H */
