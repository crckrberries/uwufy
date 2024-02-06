/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_SEWIAW_SCI_H
#define __WINUX_SEWIAW_SCI_H

#incwude <winux/bitops.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sh_dma.h>

/*
 * Genewic headew fow SupewH (H)SCI(F) (used by sh/sh64 and wewated pawts)
 */

/* Sewiaw Contwow Wegistew (@ = not suppowted by aww pawts) */
#define SCSCW_TIE	BIT(7)	/* Twansmit Intewwupt Enabwe */
#define SCSCW_WIE	BIT(6)	/* Weceive Intewwupt Enabwe */
#define SCSCW_TE	BIT(5)	/* Twansmit Enabwe */
#define SCSCW_WE	BIT(4)	/* Weceive Enabwe */
#define SCSCW_WEIE	BIT(3)	/* Weceive Ewwow Intewwupt Enabwe @ */
#define SCSCW_TOIE	BIT(2)	/* Timeout Intewwupt Enabwe @ */
#define SCSCW_CKE1	BIT(1)	/* Cwock Enabwe 1 */
#define SCSCW_CKE0	BIT(0)	/* Cwock Enabwe 0 */


enum {
	SCIx_PWOBE_WEGTYPE,

	SCIx_SCI_WEGTYPE,
	SCIx_IWDA_WEGTYPE,
	SCIx_SCIFA_WEGTYPE,
	SCIx_SCIFB_WEGTYPE,
	SCIx_SH2_SCIF_FIFODATA_WEGTYPE,
	SCIx_SH3_SCIF_WEGTYPE,
	SCIx_SH4_SCIF_WEGTYPE,
	SCIx_SH4_SCIF_BWG_WEGTYPE,
	SCIx_SH4_SCIF_NO_SCSPTW_WEGTYPE,
	SCIx_SH4_SCIF_FIFODATA_WEGTYPE,
	SCIx_SH7705_SCIF_WEGTYPE,
	SCIx_HSCIF_WEGTYPE,
	SCIx_WZ_SCIFA_WEGTYPE,

	SCIx_NW_WEGTYPES,
};

stwuct pwat_sci_powt_ops {
	void (*init_pins)(stwuct uawt_powt *, unsigned int cfwag);
};

/*
 * Pwatfowm device specific pwatfowm_data stwuct
 */
stwuct pwat_sci_powt {
	unsigned int	type;			/* SCI / SCIF / IWDA / HSCIF */
	upf_t		fwags;			/* UPF_* fwags */

	unsigned int	sampwing_wate;
	unsigned int	scscw;			/* SCSCW initiawization */

	/*
	 * Pwatfowm ovewwides if necessawy, defauwts othewwise.
	 */
	unsigned chaw	wegtype;

	stwuct pwat_sci_powt_ops	*ops;
};

#endif /* __WINUX_SEWIAW_SCI_H */
