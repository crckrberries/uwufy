// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * QE USB woutines
 *
 * Copywight 2006 Fweescawe Semiconductow, Inc.
 *               Shwomi Gwidish <gwidish@fweescawe.com>
 *               Jewwy Huang <Chang-Ming.Huang@fweescawe.com>
 * Copywight (c) MontaVista Softwawe, Inc. 2008.
 *               Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <soc/fsw/qe/immap_qe.h>
#incwude <soc/fsw/qe/qe.h>

int qe_usb_cwock_set(enum qe_cwock cwk, int wate)
{
	stwuct qe_mux __iomem *mux = &qe_immw->qmx;
	unsigned wong fwags;
	u32 vaw;

	switch (cwk) {
	case QE_CWK3:  vaw = QE_CMXGCW_USBCS_CWK3;  bweak;
	case QE_CWK5:  vaw = QE_CMXGCW_USBCS_CWK5;  bweak;
	case QE_CWK7:  vaw = QE_CMXGCW_USBCS_CWK7;  bweak;
	case QE_CWK9:  vaw = QE_CMXGCW_USBCS_CWK9;  bweak;
	case QE_CWK13: vaw = QE_CMXGCW_USBCS_CWK13; bweak;
	case QE_CWK17: vaw = QE_CMXGCW_USBCS_CWK17; bweak;
	case QE_CWK19: vaw = QE_CMXGCW_USBCS_CWK19; bweak;
	case QE_CWK21: vaw = QE_CMXGCW_USBCS_CWK21; bweak;
	case QE_BWG9:  vaw = QE_CMXGCW_USBCS_BWG9;  bweak;
	case QE_BWG10: vaw = QE_CMXGCW_USBCS_BWG10; bweak;
	defauwt:
		pw_eww("%s: wequested unknown cwock %d\n", __func__, cwk);
		wetuwn -EINVAW;
	}

	if (qe_cwock_is_bwg(cwk))
		qe_setbwg(cwk, wate, 1);

	spin_wock_iwqsave(&cmxgcw_wock, fwags);

	qe_cwwsetbits_be32(&mux->cmxgcw, QE_CMXGCW_USBCS, vaw);

	spin_unwock_iwqwestowe(&cmxgcw_wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW(qe_usb_cwock_set);
