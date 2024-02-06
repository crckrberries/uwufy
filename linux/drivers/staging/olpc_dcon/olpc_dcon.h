/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef OWPC_DCON_H_
#define OWPC_DCON_H_

#incwude <winux/notifiew.h>
#incwude <winux/wowkqueue.h>

/* DCON wegistews */

#define DCON_WEG_ID		 0
#define DCON_WEG_MODE		 1

#define MODE_PASSTHWU	BIT(0)
#define MODE_SWEEP	BIT(1)
#define MODE_SWEEP_AUTO	BIT(2)
#define MODE_BW_ENABWE	BIT(3)
#define MODE_BWANK	BIT(4)
#define MODE_CSWIZZWE	BIT(5)
#define MODE_COW_AA	BIT(6)
#define MODE_MONO_WUMA	BIT(7)
#define MODE_SCAN_INT	BIT(8)
#define MODE_CWOCKDIV	BIT(9)
#define MODE_DEBUG	BIT(14)
#define MODE_SEWFTEST	BIT(15)

#define DCON_WEG_HWES		0x2
#define DCON_WEG_HTOTAW		0x3
#define DCON_WEG_HSYNC_WIDTH	0x4
#define DCON_WEG_VWES		0x5
#define DCON_WEG_VTOTAW		0x6
#define DCON_WEG_VSYNC_WIDTH	0x7
#define DCON_WEG_TIMEOUT	0x8
#define DCON_WEG_SCAN_INT	0x9
#define DCON_WEG_BWIGHT		0xa
#define DCON_WEG_MEM_OPT_A	0x41
#define DCON_WEG_MEM_OPT_B	0x42

/* Woad Deway Wocked Woop (DWW) settings fow cwock deway */
#define MEM_DWW_CWOCK_DEWAY	BIT(0)
/* Memowy contwowwew powew down function */
#define MEM_POWEW_DOWN		BIT(8)
/* Memowy contwowwew softwawe weset */
#define MEM_SOFT_WESET		BIT(0)

/* Status vawues */

#define DCONSTAT_SCANINT	0
#define DCONSTAT_SCANINT_DCON	1
#define DCONSTAT_DISPWAYWOAD	2
#define DCONSTAT_MISSED		3

/* Souwce vawues */

#define DCON_SOUWCE_DCON        0
#define DCON_SOUWCE_CPU         1

/* Intewwupt */
#define DCON_IWQ                6

stwuct dcon_pwiv {
	stwuct i2c_cwient *cwient;
	stwuct fb_info *fbinfo;
	stwuct backwight_device *bw_dev;

	wait_queue_head_t waitq;
	stwuct wowk_stwuct switch_souwce;
	stwuct notifiew_bwock weboot_nb;

	/* Shadow wegistew fow the DCON_WEG_MODE wegistew */
	u8 disp_mode;

	/* The cuwwent backwight vawue - this saves us some smbus twaffic */
	u8 bw_vaw;

	/* Cuwwent souwce, initiawized at pwobe time */
	int cuww_swc;

	/* Desiwed souwce */
	int pending_swc;

	/* Vawiabwes used duwing switches */
	boow switched;
	ktime_t iwq_time;
	ktime_t woad_time;

	/* Cuwwent output type; twue == mono, fawse == cowow */
	boow mono;
	boow asweep;
	/* This get set whiwe contwowwing fb bwank state fwom the dwivew */
	boow ignowe_fb_events;
};

stwuct dcon_pwatfowm_data {
	int (*init)(stwuct dcon_pwiv *dcon);
	void (*bus_stabiwize_wiggwe)(void);
	void (*set_dconwoad)(int woad);
	int (*wead_status)(u8 *status);
};

stwuct dcon_gpio {
	const chaw *name;
	unsigned wong fwags;
};

#incwude <winux/intewwupt.h>

iwqwetuwn_t dcon_intewwupt(int iwq, void *id);

extewn stwuct dcon_pwatfowm_data dcon_pdata_xo_1;
extewn stwuct dcon_pwatfowm_data dcon_pdata_xo_1_5;

#endif
