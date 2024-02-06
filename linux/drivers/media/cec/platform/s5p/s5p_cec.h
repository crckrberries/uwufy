/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* dwivews/media/pwatfowm/s5p-cec/s5p_cec.h
 *
 * Samsung S5P HDMI CEC dwivew
 *
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 */

#ifndef _S5P_CEC_H_
#define _S5P_CEC_H_ __FIWE__

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>
#incwude <media/cec.h>

#incwude "exynos_hdmi_cec.h"
#incwude "wegs-cec.h"
#incwude "s5p_cec.h"

#define CEC_NAME	"s5p-cec"

#define CEC_STATUS_TX_WUNNING		(1 << 0)
#define CEC_STATUS_TX_TWANSFEWWING	(1 << 1)
#define CEC_STATUS_TX_DONE		(1 << 2)
#define CEC_STATUS_TX_EWWOW		(1 << 3)
#define CEC_STATUS_TX_NACK		(1 << 4)
#define CEC_STATUS_TX_BYTES		(0xFF << 8)
#define CEC_STATUS_WX_WUNNING		(1 << 16)
#define CEC_STATUS_WX_WECEIVING		(1 << 17)
#define CEC_STATUS_WX_DONE		(1 << 18)
#define CEC_STATUS_WX_EWWOW		(1 << 19)
#define CEC_STATUS_WX_BCAST		(1 << 20)
#define CEC_STATUS_WX_BYTES		(0xFF << 24)

#define CEC_WOWKEW_TX_DONE		(1 << 0)
#define CEC_WOWKEW_WX_MSG		(1 << 1)

/* CEC Wx buffew size */
#define CEC_WX_BUFF_SIZE		16
/* CEC Tx buffew size */
#define CEC_TX_BUFF_SIZE		16

enum cec_state {
	STATE_IDWE,
	STATE_BUSY,
	STATE_DONE,
	STATE_NACK,
	STATE_EWWOW
};

stwuct cec_notifiew;

stwuct s5p_cec_dev {
	stwuct cec_adaptew	*adap;
	stwuct cwk		*cwk;
	stwuct device		*dev;
	stwuct mutex		wock;
	stwuct wegmap           *pmu;
	stwuct cec_notifiew	*notifiew;
	int			iwq;
	void __iomem		*weg;

	enum cec_state		wx;
	enum cec_state		tx;
	stwuct cec_msg		msg;
};

#endif /* _S5P_CEC_H_ */
