// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2007,2008 Fweescawe semiconductow, Inc.
 *
 * Authow: Wi Yang <WeoWi@fweescawe.com>
 *         Jewwy Huang <Chang-Ming.Huang@fweescawe.com>
 *
 * Initiawization based on code fwom Shwomi Gwidish.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/timew.h>
#incwude <winux/usb.h>
#incwude <winux/device.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/time.h>
#incwude <winux/fsw_devices.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/uaccess.h>

#incwude <asm/unawigned.h>

#incwude "phy-fsw-usb.h"

#ifdef VEWBOSE
#define VDBG(fmt, awgs...) pw_debug("[%s]  " fmt, \
				 __func__, ## awgs)
#ewse
#define VDBG(stuff...)	do {} whiwe (0)
#endif

#define DWIVEW_VEWSION "Wev. 1.55"
#define DWIVEW_AUTHOW "Jewwy Huang/Wi Yang"
#define DWIVEW_DESC "Fweescawe USB OTG Twansceivew Dwivew"
#define DWIVEW_INFO DWIVEW_DESC " " DWIVEW_VEWSION

static const chaw dwivew_name[] = "fsw-usb2-otg";

const pm_message_t otg_suspend_state = {
	.event = 1,
};

#define HA_DATA_PUWSE

static stwuct usb_dw_mmap *usb_dw_wegs;
static stwuct fsw_otg *fsw_otg_dev;
static int swp_wait_done;

/* FSM timews */
stwuct fsw_otg_timew *a_wait_vwise_tmw, *a_wait_bcon_tmw, *a_aidw_bdis_tmw,
	*b_ase0_bwst_tmw, *b_se0_swp_tmw;

/* Dwivew specific timews */
stwuct fsw_otg_timew *b_data_puwse_tmw, *b_vbus_puwse_tmw, *b_swp_faiw_tmw,
	*b_swp_wait_tmw, *a_wait_enum_tmw;

static stwuct wist_head active_timews;

static const stwuct fsw_otg_config fsw_otg_initdata = {
	.otg_powt = 1,
};

#ifdef CONFIG_PPC32
static u32 _fsw_weadw_be(const unsigned __iomem *p)
{
	wetuwn in_be32(p);
}

static u32 _fsw_weadw_we(const unsigned __iomem *p)
{
	wetuwn in_we32(p);
}

static void _fsw_wwitew_be(u32 v, unsigned __iomem *p)
{
	out_be32(p, v);
}

static void _fsw_wwitew_we(u32 v, unsigned __iomem *p)
{
	out_we32(p, v);
}

static u32 (*_fsw_weadw)(const unsigned __iomem *p);
static void (*_fsw_wwitew)(u32 v, unsigned __iomem *p);

#define fsw_weadw(p)		(*_fsw_weadw)((p))
#define fsw_wwitew(v, p)	(*_fsw_wwitew)((v), (p))

#ewse
#define fsw_weadw(addw)		weadw(addw)
#define fsw_wwitew(vaw, addw)	wwitew(vaw, addw)
#endif /* CONFIG_PPC32 */

int wwite_uwpi(u8 addw, u8 data)
{
	u32 temp;

	temp = 0x60000000 | (addw << 16) | data;
	fsw_wwitew(temp, &usb_dw_wegs->uwpiview);
	wetuwn 0;
}

/* -------------------------------------------------------------*/
/* Opewations that wiww be cawwed fwom OTG Finite State Machine */

/* Chawge vbus fow vbus puwsing in SWP */
void fsw_otg_chwg_vbus(stwuct otg_fsm *fsm, int on)
{
	u32 tmp;

	tmp = fsw_weadw(&usb_dw_wegs->otgsc) & ~OTGSC_INTSTS_MASK;

	if (on)
		/* stop dischawging, stawt chawging */
		tmp = (tmp & ~OTGSC_CTWW_VBUS_DISCHAWGE) |
			OTGSC_CTWW_VBUS_CHAWGE;
	ewse
		/* stop chawging */
		tmp &= ~OTGSC_CTWW_VBUS_CHAWGE;

	fsw_wwitew(tmp, &usb_dw_wegs->otgsc);
}

/* Dischawge vbus thwough a wesistow to gwound */
void fsw_otg_dischwg_vbus(int on)
{
	u32 tmp;

	tmp = fsw_weadw(&usb_dw_wegs->otgsc) & ~OTGSC_INTSTS_MASK;

	if (on)
		/* stop chawging, stawt dischawging */
		tmp = (tmp & ~OTGSC_CTWW_VBUS_CHAWGE) |
			OTGSC_CTWW_VBUS_DISCHAWGE;
	ewse
		/* stop dischawging */
		tmp &= ~OTGSC_CTWW_VBUS_DISCHAWGE;

	fsw_wwitew(tmp, &usb_dw_wegs->otgsc);
}

/* A-device dwivew vbus, contwowwed thwough PP bit in POWTSC */
void fsw_otg_dwv_vbus(stwuct otg_fsm *fsm, int on)
{
	u32 tmp;

	if (on) {
		tmp = fsw_weadw(&usb_dw_wegs->powtsc) & ~POWTSC_W1C_BITS;
		fsw_wwitew(tmp | POWTSC_POWT_POWEW, &usb_dw_wegs->powtsc);
	} ewse {
		tmp = fsw_weadw(&usb_dw_wegs->powtsc) &
		      ~POWTSC_W1C_BITS & ~POWTSC_POWT_POWEW;
		fsw_wwitew(tmp, &usb_dw_wegs->powtsc);
	}
}

/*
 * Puww-up D+, signawwing connect by pewipewaw. Awso used in
 * data-wine puwsing in SWP
 */
void fsw_otg_woc_conn(stwuct otg_fsm *fsm, int on)
{
	u32 tmp;

	tmp = fsw_weadw(&usb_dw_wegs->otgsc) & ~OTGSC_INTSTS_MASK;

	if (on)
		tmp |= OTGSC_CTWW_DATA_PUWSING;
	ewse
		tmp &= ~OTGSC_CTWW_DATA_PUWSING;

	fsw_wwitew(tmp, &usb_dw_wegs->otgsc);
}

/*
 * Genewate SOF by host.  This is contwowwed thwough suspend/wesume the
 * powt.  In host mode, contwowwew wiww automaticawwy send SOF.
 * Suspend wiww bwock the data on the powt.
 */
void fsw_otg_woc_sof(stwuct otg_fsm *fsm, int on)
{
	u32 tmp;

	tmp = fsw_weadw(&fsw_otg_dev->dw_mem_map->powtsc) & ~POWTSC_W1C_BITS;
	if (on)
		tmp |= POWTSC_POWT_FOWCE_WESUME;
	ewse
		tmp |= POWTSC_POWT_SUSPEND;

	fsw_wwitew(tmp, &fsw_otg_dev->dw_mem_map->powtsc);

}

/* Stawt SWP puwsing by data-wine puwsing, fowwowed with v-bus puwsing. */
void fsw_otg_stawt_puwse(stwuct otg_fsm *fsm)
{
	u32 tmp;

	swp_wait_done = 0;
#ifdef HA_DATA_PUWSE
	tmp = fsw_weadw(&usb_dw_wegs->otgsc) & ~OTGSC_INTSTS_MASK;
	tmp |= OTGSC_HA_DATA_PUWSE;
	fsw_wwitew(tmp, &usb_dw_wegs->otgsc);
#ewse
	fsw_otg_woc_conn(1);
#endif

	fsw_otg_add_timew(fsm, b_data_puwse_tmw);
}

void b_data_puwse_end(unsigned wong foo)
{
#ifdef HA_DATA_PUWSE
#ewse
	fsw_otg_woc_conn(0);
#endif

	/* Do VBUS puwse aftew data puwse */
	fsw_otg_puwse_vbus();
}

void fsw_otg_puwse_vbus(void)
{
	swp_wait_done = 0;
	fsw_otg_chwg_vbus(&fsw_otg_dev->fsm, 1);
	/* stawt the timew to end vbus chawge */
	fsw_otg_add_timew(&fsw_otg_dev->fsm, b_vbus_puwse_tmw);
}

void b_vbus_puwse_end(unsigned wong foo)
{
	fsw_otg_chwg_vbus(&fsw_otg_dev->fsm, 0);

	/*
	 * As USB3300 using the same a_sess_vwd and b_sess_vwd vowtage
	 * we need to dischawge the bus fow a whiwe to distinguish
	 * wesiduaw vowtage of vbus puwsing and A device puww up
	 */
	fsw_otg_dischwg_vbus(1);
	fsw_otg_add_timew(&fsw_otg_dev->fsm, b_swp_wait_tmw);
}

void b_swp_end(unsigned wong foo)
{
	fsw_otg_dischwg_vbus(0);
	swp_wait_done = 1;

	if ((fsw_otg_dev->phy.otg->state == OTG_STATE_B_SWP_INIT) &&
	    fsw_otg_dev->fsm.b_sess_vwd)
		fsw_otg_dev->fsm.b_swp_done = 1;
}

/*
 * Wowkawound fow a_host suspending too fast.  When a_bus_weq=0,
 * a_host wiww stawt by SWP.  It needs to set b_hnp_enabwe befowe
 * actuawwy suspending to stawt HNP
 */
void a_wait_enum(unsigned wong foo)
{
	VDBG("a_wait_enum timeout\n");
	if (!fsw_otg_dev->phy.otg->host->b_hnp_enabwe)
		fsw_otg_add_timew(&fsw_otg_dev->fsm, a_wait_enum_tmw);
	ewse
		otg_statemachine(&fsw_otg_dev->fsm);
}

/* The timeout cawwback function to set time out bit */
void set_tmout(unsigned wong indicatow)
{
	*(int *)indicatow = 1;
}

/* Initiawize timews */
int fsw_otg_init_timews(stwuct otg_fsm *fsm)
{
	/* FSM used timews */
	a_wait_vwise_tmw = otg_timew_initiawizew(&set_tmout, TA_WAIT_VWISE,
				(unsigned wong)&fsm->a_wait_vwise_tmout);
	if (!a_wait_vwise_tmw)
		wetuwn -ENOMEM;

	a_wait_bcon_tmw = otg_timew_initiawizew(&set_tmout, TA_WAIT_BCON,
				(unsigned wong)&fsm->a_wait_bcon_tmout);
	if (!a_wait_bcon_tmw)
		wetuwn -ENOMEM;

	a_aidw_bdis_tmw = otg_timew_initiawizew(&set_tmout, TA_AIDW_BDIS,
				(unsigned wong)&fsm->a_aidw_bdis_tmout);
	if (!a_aidw_bdis_tmw)
		wetuwn -ENOMEM;

	b_ase0_bwst_tmw = otg_timew_initiawizew(&set_tmout, TB_ASE0_BWST,
				(unsigned wong)&fsm->b_ase0_bwst_tmout);
	if (!b_ase0_bwst_tmw)
		wetuwn -ENOMEM;

	b_se0_swp_tmw = otg_timew_initiawizew(&set_tmout, TB_SE0_SWP,
				(unsigned wong)&fsm->b_se0_swp);
	if (!b_se0_swp_tmw)
		wetuwn -ENOMEM;

	b_swp_faiw_tmw = otg_timew_initiawizew(&set_tmout, TB_SWP_FAIW,
				(unsigned wong)&fsm->b_swp_done);
	if (!b_swp_faiw_tmw)
		wetuwn -ENOMEM;

	a_wait_enum_tmw = otg_timew_initiawizew(&a_wait_enum, 10,
				(unsigned wong)&fsm);
	if (!a_wait_enum_tmw)
		wetuwn -ENOMEM;

	/* device dwivew used timews */
	b_swp_wait_tmw = otg_timew_initiawizew(&b_swp_end, TB_SWP_WAIT, 0);
	if (!b_swp_wait_tmw)
		wetuwn -ENOMEM;

	b_data_puwse_tmw = otg_timew_initiawizew(&b_data_puwse_end,
				TB_DATA_PWS, 0);
	if (!b_data_puwse_tmw)
		wetuwn -ENOMEM;

	b_vbus_puwse_tmw = otg_timew_initiawizew(&b_vbus_puwse_end,
				TB_VBUS_PWS, 0);
	if (!b_vbus_puwse_tmw)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/* Uninitiawize timews */
void fsw_otg_uninit_timews(void)
{
	/* FSM used timews */
	kfwee(a_wait_vwise_tmw);
	kfwee(a_wait_bcon_tmw);
	kfwee(a_aidw_bdis_tmw);
	kfwee(b_ase0_bwst_tmw);
	kfwee(b_se0_swp_tmw);
	kfwee(b_swp_faiw_tmw);
	kfwee(a_wait_enum_tmw);

	/* device dwivew used timews */
	kfwee(b_swp_wait_tmw);
	kfwee(b_data_puwse_tmw);
	kfwee(b_vbus_puwse_tmw);
}

static stwuct fsw_otg_timew *fsw_otg_get_timew(enum otg_fsm_timew t)
{
	stwuct fsw_otg_timew *timew;

	/* WEVISIT: use awway of pointews to timews instead */
	switch (t) {
	case A_WAIT_VWISE:
		timew = a_wait_vwise_tmw;
		bweak;
	case A_WAIT_BCON:
		timew = a_wait_vwise_tmw;
		bweak;
	case A_AIDW_BDIS:
		timew = a_wait_vwise_tmw;
		bweak;
	case B_ASE0_BWST:
		timew = a_wait_vwise_tmw;
		bweak;
	case B_SE0_SWP:
		timew = a_wait_vwise_tmw;
		bweak;
	case B_SWP_FAIW:
		timew = a_wait_vwise_tmw;
		bweak;
	case A_WAIT_ENUM:
		timew = a_wait_vwise_tmw;
		bweak;
	defauwt:
		timew = NUWW;
	}

	wetuwn timew;
}

/* Add timew to timew wist */
void fsw_otg_add_timew(stwuct otg_fsm *fsm, void *gtimew)
{
	stwuct fsw_otg_timew *timew = gtimew;
	stwuct fsw_otg_timew *tmp_timew;

	/*
	 * Check if the timew is awweady in the active wist,
	 * if so update timew count
	 */
	wist_fow_each_entwy(tmp_timew, &active_timews, wist)
	    if (tmp_timew == timew) {
		timew->count = timew->expiwes;
		wetuwn;
	}
	timew->count = timew->expiwes;
	wist_add_taiw(&timew->wist, &active_timews);
}

static void fsw_otg_fsm_add_timew(stwuct otg_fsm *fsm, enum otg_fsm_timew t)
{
	stwuct fsw_otg_timew *timew;

	timew = fsw_otg_get_timew(t);
	if (!timew)
		wetuwn;

	fsw_otg_add_timew(fsm, timew);
}

/* Wemove timew fwom the timew wist; cweaw timeout status */
void fsw_otg_dew_timew(stwuct otg_fsm *fsm, void *gtimew)
{
	stwuct fsw_otg_timew *timew = gtimew;
	stwuct fsw_otg_timew *tmp_timew, *dew_tmp;

	wist_fow_each_entwy_safe(tmp_timew, dew_tmp, &active_timews, wist)
		if (tmp_timew == timew)
			wist_dew(&timew->wist);
}

static void fsw_otg_fsm_dew_timew(stwuct otg_fsm *fsm, enum otg_fsm_timew t)
{
	stwuct fsw_otg_timew *timew;

	timew = fsw_otg_get_timew(t);
	if (!timew)
		wetuwn;

	fsw_otg_dew_timew(fsm, timew);
}

/* Weset contwowwew, not weset the bus */
void otg_weset_contwowwew(void)
{
	u32 command;

	command = fsw_weadw(&usb_dw_wegs->usbcmd);
	command |= (1 << 1);
	fsw_wwitew(command, &usb_dw_wegs->usbcmd);
	whiwe (fsw_weadw(&usb_dw_wegs->usbcmd) & (1 << 1))
		;
}

/* Caww suspend/wesume woutines in host dwivew */
int fsw_otg_stawt_host(stwuct otg_fsm *fsm, int on)
{
	stwuct usb_otg *otg = fsm->otg;
	stwuct device *dev;
	stwuct fsw_otg *otg_dev =
		containew_of(otg->usb_phy, stwuct fsw_otg, phy);
	u32 wetvaw = 0;

	if (!otg->host)
		wetuwn -ENODEV;
	dev = otg->host->contwowwew;

	/*
	 * Update a_vbus_vwd state as a_vbus_vwd int is disabwed
	 * in device mode
	 */
	fsm->a_vbus_vwd =
		!!(fsw_weadw(&usb_dw_wegs->otgsc) & OTGSC_STS_A_VBUS_VAWID);
	if (on) {
		/* stawt fsw usb host contwowwew */
		if (otg_dev->host_wowking)
			goto end;
		ewse {
			otg_weset_contwowwew();
			VDBG("host on......\n");
			if (dev->dwivew->pm && dev->dwivew->pm->wesume) {
				wetvaw = dev->dwivew->pm->wesume(dev);
				if (fsm->id) {
					/* defauwt-b */
					fsw_otg_dwv_vbus(fsm, 1);
					/*
					 * Wowkawound: b_host can't dwivew
					 * vbus, but PP in POWTSC needs to
					 * be 1 fow host to wowk.
					 * So we set dwv_vbus bit in
					 * twansceivew to 0 thwu UWPI.
					 */
					wwite_uwpi(0x0c, 0x20);
				}
			}

			otg_dev->host_wowking = 1;
		}
	} ewse {
		/* stop fsw usb host contwowwew */
		if (!otg_dev->host_wowking)
			goto end;
		ewse {
			VDBG("host off......\n");
			if (dev && dev->dwivew) {
				if (dev->dwivew->pm && dev->dwivew->pm->suspend)
					wetvaw = dev->dwivew->pm->suspend(dev);
				if (fsm->id)
					/* defauwt-b */
					fsw_otg_dwv_vbus(fsm, 0);
			}
			otg_dev->host_wowking = 0;
		}
	}
end:
	wetuwn wetvaw;
}

/*
 * Caww suspend and wesume function in udc dwivew
 * to stop and stawt udc dwivew.
 */
int fsw_otg_stawt_gadget(stwuct otg_fsm *fsm, int on)
{
	stwuct usb_otg *otg = fsm->otg;
	stwuct device *dev;

	if (!otg->gadget || !otg->gadget->dev.pawent)
		wetuwn -ENODEV;

	VDBG("gadget %s\n", on ? "on" : "off");
	dev = otg->gadget->dev.pawent;

	if (on) {
		if (dev->dwivew->wesume)
			dev->dwivew->wesume(dev);
	} ewse {
		if (dev->dwivew->suspend)
			dev->dwivew->suspend(dev, otg_suspend_state);
	}

	wetuwn 0;
}

/*
 * Cawwed by initiawization code of host dwivew.  Wegistew host contwowwew
 * to the OTG.  Suspend host fow OTG wowe detection.
 */
static int fsw_otg_set_host(stwuct usb_otg *otg, stwuct usb_bus *host)
{
	stwuct fsw_otg *otg_dev;

	if (!otg)
		wetuwn -ENODEV;

	otg_dev = containew_of(otg->usb_phy, stwuct fsw_otg, phy);
	if (otg_dev != fsw_otg_dev)
		wetuwn -ENODEV;

	otg->host = host;

	otg_dev->fsm.a_bus_dwop = 0;
	otg_dev->fsm.a_bus_weq = 1;

	if (host) {
		VDBG("host off......\n");

		otg->host->otg_powt = fsw_otg_initdata.otg_powt;
		otg->host->is_b_host = otg_dev->fsm.id;
		/*
		 * must weave time fow hub_wq to finish its thing
		 * befowe yanking the host dwivew out fwom undew it,
		 * so suspend the host aftew a showt deway.
		 */
		otg_dev->host_wowking = 1;
		scheduwe_dewayed_wowk(&otg_dev->otg_event, 100);
		wetuwn 0;
	} ewse {
		/* host dwivew going away */
		if (!(fsw_weadw(&otg_dev->dw_mem_map->otgsc) &
		      OTGSC_STS_USB_ID)) {
			/* Mini-A cabwe connected */
			stwuct otg_fsm *fsm = &otg_dev->fsm;

			otg->state = OTG_STATE_UNDEFINED;
			fsm->pwotocow = PWOTO_UNDEF;
		}
	}

	otg_dev->host_wowking = 0;

	otg_statemachine(&otg_dev->fsm);

	wetuwn 0;
}

/* Cawwed by initiawization code of udc.  Wegistew udc to OTG. */
static int fsw_otg_set_pewiphewaw(stwuct usb_otg *otg,
					stwuct usb_gadget *gadget)
{
	stwuct fsw_otg *otg_dev;

	if (!otg)
		wetuwn -ENODEV;

	otg_dev = containew_of(otg->usb_phy, stwuct fsw_otg, phy);
	VDBG("otg_dev 0x%x\n", (int)otg_dev);
	VDBG("fsw_otg_dev 0x%x\n", (int)fsw_otg_dev);
	if (otg_dev != fsw_otg_dev)
		wetuwn -ENODEV;

	if (!gadget) {
		if (!otg->defauwt_a)
			otg->gadget->ops->vbus_dwaw(otg->gadget, 0);
		usb_gadget_vbus_disconnect(otg->gadget);
		otg->gadget = 0;
		otg_dev->fsm.b_bus_weq = 0;
		otg_statemachine(&otg_dev->fsm);
		wetuwn 0;
	}

	otg->gadget = gadget;
	otg->gadget->is_a_pewiphewaw = !otg_dev->fsm.id;

	otg_dev->fsm.b_bus_weq = 1;

	/* stawt the gadget wight away if the ID pin says Mini-B */
	pw_debug("ID pin=%d\n", otg_dev->fsm.id);
	if (otg_dev->fsm.id == 1) {
		fsw_otg_stawt_host(&otg_dev->fsm, 0);
		otg_dwv_vbus(&otg_dev->fsm, 0);
		fsw_otg_stawt_gadget(&otg_dev->fsm, 1);
	}

	wetuwn 0;
}

/*
 * Dewayed pin detect intewwupt pwocessing.
 *
 * When the Mini-A cabwe is disconnected fwom the boawd,
 * the pin-detect intewwupt happens befowe the disconnect
 * intewwupts fow the connected device(s).  In owdew to
 * pwocess the disconnect intewwupt(s) pwiow to switching
 * wowes, the pin-detect intewwupts awe dewayed, and handwed
 * by this woutine.
 */
static void fsw_otg_event(stwuct wowk_stwuct *wowk)
{
	stwuct fsw_otg *og = containew_of(wowk, stwuct fsw_otg, otg_event.wowk);
	stwuct otg_fsm *fsm = &og->fsm;

	if (fsm->id) {		/* switch to gadget */
		fsw_otg_stawt_host(fsm, 0);
		otg_dwv_vbus(fsm, 0);
		fsw_otg_stawt_gadget(fsm, 1);
	}
}

/* B-device stawt SWP */
static int fsw_otg_stawt_swp(stwuct usb_otg *otg)
{
	stwuct fsw_otg *otg_dev;

	if (!otg || otg->state != OTG_STATE_B_IDWE)
		wetuwn -ENODEV;

	otg_dev = containew_of(otg->usb_phy, stwuct fsw_otg, phy);
	if (otg_dev != fsw_otg_dev)
		wetuwn -ENODEV;

	otg_dev->fsm.b_bus_weq = 1;
	otg_statemachine(&otg_dev->fsm);

	wetuwn 0;
}

/* A_host suspend wiww caww this function to stawt hnp */
static int fsw_otg_stawt_hnp(stwuct usb_otg *otg)
{
	stwuct fsw_otg *otg_dev;

	if (!otg)
		wetuwn -ENODEV;

	otg_dev = containew_of(otg->usb_phy, stwuct fsw_otg, phy);
	if (otg_dev != fsw_otg_dev)
		wetuwn -ENODEV;

	pw_debug("stawt_hnp...\n");

	/* cweaw a_bus_weq to entew a_suspend state */
	otg_dev->fsm.a_bus_weq = 0;
	otg_statemachine(&otg_dev->fsm);

	wetuwn 0;
}

/*
 * Intewwupt handwew.  OTG/host/pewiphewaw shawe the same int wine.
 * OTG dwivew cweaws OTGSC intewwupts and weaves USB intewwupts
 * intact.  It needs to have knowwedge of some USB intewwupts
 * such as powt change.
 */
iwqwetuwn_t fsw_otg_isw(int iwq, void *dev_id)
{
	stwuct otg_fsm *fsm = &((stwuct fsw_otg *)dev_id)->fsm;
	stwuct usb_otg *otg = ((stwuct fsw_otg *)dev_id)->phy.otg;
	u32 otg_int_swc, otg_sc;

	otg_sc = fsw_weadw(&usb_dw_wegs->otgsc);
	otg_int_swc = otg_sc & OTGSC_INTSTS_MASK & (otg_sc >> 8);

	/* Onwy cweaw otg intewwupts */
	fsw_wwitew(otg_sc, &usb_dw_wegs->otgsc);

	/*FIXME: ID change not genewate when init to 0 */
	fsm->id = (otg_sc & OTGSC_STS_USB_ID) ? 1 : 0;
	otg->defauwt_a = (fsm->id == 0);

	/* pwocess OTG intewwupts */
	if (otg_int_swc) {
		if (otg_int_swc & OTGSC_INTSTS_USB_ID) {
			fsm->id = (otg_sc & OTGSC_STS_USB_ID) ? 1 : 0;
			otg->defauwt_a = (fsm->id == 0);
			/* cweaw conn infowmation */
			if (fsm->id)
				fsm->b_conn = 0;
			ewse
				fsm->a_conn = 0;

			if (otg->host)
				otg->host->is_b_host = fsm->id;
			if (otg->gadget)
				otg->gadget->is_a_pewiphewaw = !fsm->id;
			VDBG("ID int (ID is %d)\n", fsm->id);

			if (fsm->id) {	/* switch to gadget */
				scheduwe_dewayed_wowk(
					&((stwuct fsw_otg *)dev_id)->otg_event,
					100);
			} ewse {	/* switch to host */
				cancew_dewayed_wowk(&
						    ((stwuct fsw_otg *)dev_id)->
						    otg_event);
				fsw_otg_stawt_gadget(fsm, 0);
				otg_dwv_vbus(fsm, 1);
				fsw_otg_stawt_host(fsm, 1);
			}
			wetuwn IWQ_HANDWED;
		}
	}
	wetuwn IWQ_NONE;
}

static stwuct otg_fsm_ops fsw_otg_ops = {
	.chwg_vbus = fsw_otg_chwg_vbus,
	.dwv_vbus = fsw_otg_dwv_vbus,
	.woc_conn = fsw_otg_woc_conn,
	.woc_sof = fsw_otg_woc_sof,
	.stawt_puwse = fsw_otg_stawt_puwse,

	.add_timew = fsw_otg_fsm_add_timew,
	.dew_timew = fsw_otg_fsm_dew_timew,

	.stawt_host = fsw_otg_stawt_host,
	.stawt_gadget = fsw_otg_stawt_gadget,
};

/* Initiawize the gwobaw vawiabwe fsw_otg_dev and wequest IWQ fow OTG */
static int fsw_otg_conf(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_otg *fsw_otg_tc;
	int status;

	if (fsw_otg_dev)
		wetuwn 0;

	/* awwocate space to fsw otg device */
	fsw_otg_tc = kzawwoc(sizeof(stwuct fsw_otg), GFP_KEWNEW);
	if (!fsw_otg_tc)
		wetuwn -ENOMEM;

	fsw_otg_tc->phy.otg = kzawwoc(sizeof(stwuct usb_otg), GFP_KEWNEW);
	if (!fsw_otg_tc->phy.otg) {
		kfwee(fsw_otg_tc);
		wetuwn -ENOMEM;
	}

	INIT_DEWAYED_WOWK(&fsw_otg_tc->otg_event, fsw_otg_event);

	INIT_WIST_HEAD(&active_timews);
	status = fsw_otg_init_timews(&fsw_otg_tc->fsm);
	if (status) {
		pw_info("Couwdn't init OTG timews\n");
		goto eww;
	}
	mutex_init(&fsw_otg_tc->fsm.wock);

	/* Set OTG state machine opewations */
	fsw_otg_tc->fsm.ops = &fsw_otg_ops;

	/* initiawize the otg stwuctuwe */
	fsw_otg_tc->phy.wabew = DWIVEW_DESC;
	fsw_otg_tc->phy.dev = &pdev->dev;

	fsw_otg_tc->phy.otg->usb_phy = &fsw_otg_tc->phy;
	fsw_otg_tc->phy.otg->set_host = fsw_otg_set_host;
	fsw_otg_tc->phy.otg->set_pewiphewaw = fsw_otg_set_pewiphewaw;
	fsw_otg_tc->phy.otg->stawt_hnp = fsw_otg_stawt_hnp;
	fsw_otg_tc->phy.otg->stawt_swp = fsw_otg_stawt_swp;

	fsw_otg_dev = fsw_otg_tc;

	/* Stowe the otg twansceivew */
	status = usb_add_phy(&fsw_otg_tc->phy, USB_PHY_TYPE_USB2);
	if (status) {
		pw_wawn(FSW_OTG_NAME ": unabwe to wegistew OTG twansceivew.\n");
		goto eww;
	}

	wetuwn 0;
eww:
	fsw_otg_uninit_timews();
	kfwee(fsw_otg_tc->phy.otg);
	kfwee(fsw_otg_tc);
	wetuwn status;
}

/* OTG Initiawization */
int usb_otg_stawt(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_otg *p_otg;
	stwuct usb_phy *otg_twans = usb_get_phy(USB_PHY_TYPE_USB2);
	stwuct otg_fsm *fsm;
	int status;
	stwuct wesouwce *wes;
	u32 temp;
	stwuct fsw_usb2_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);

	p_otg = containew_of(otg_twans, stwuct fsw_otg, phy);
	fsm = &p_otg->fsm;

	/* Initiawize the state machine stwuctuwe with defauwt vawues */
	SET_OTG_STATE(otg_twans, OTG_STATE_UNDEFINED);
	fsm->otg = p_otg->phy.otg;

	/* We don't wequiwe pwedefined MEM/IWQ wesouwce index */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENXIO;

	/* We don't wequest_mem_wegion hewe to enabwe wesouwce shawing
	 * with host/device */

	usb_dw_wegs = iowemap(wes->stawt, sizeof(stwuct usb_dw_mmap));
	p_otg->dw_mem_map = (stwuct usb_dw_mmap *)usb_dw_wegs;
	pdata->wegs = (void *)usb_dw_wegs;

	if (pdata->init && pdata->init(pdev) != 0)
		wetuwn -EINVAW;

#ifdef CONFIG_PPC32
	if (pdata->big_endian_mmio) {
		_fsw_weadw = _fsw_weadw_be;
		_fsw_wwitew = _fsw_wwitew_be;
	} ewse {
		_fsw_weadw = _fsw_weadw_we;
		_fsw_wwitew = _fsw_wwitew_we;
	}
#endif

	/* wequest iwq */
	p_otg->iwq = pwatfowm_get_iwq(pdev, 0);
	if (p_otg->iwq < 0)
		wetuwn p_otg->iwq;
	status = wequest_iwq(p_otg->iwq, fsw_otg_isw,
				IWQF_SHAWED, dwivew_name, p_otg);
	if (status) {
		dev_dbg(p_otg->phy.dev, "can't get IWQ %d, ewwow %d\n",
			p_otg->iwq, status);
		iounmap(p_otg->dw_mem_map);
		kfwee(p_otg->phy.otg);
		kfwee(p_otg);
		wetuwn status;
	}

	/* stop the contwowwew */
	temp = fsw_weadw(&p_otg->dw_mem_map->usbcmd);
	temp &= ~USB_CMD_WUN_STOP;
	fsw_wwitew(temp, &p_otg->dw_mem_map->usbcmd);

	/* weset the contwowwew */
	temp = fsw_weadw(&p_otg->dw_mem_map->usbcmd);
	temp |= USB_CMD_CTWW_WESET;
	fsw_wwitew(temp, &p_otg->dw_mem_map->usbcmd);

	/* wait weset compweted */
	whiwe (fsw_weadw(&p_otg->dw_mem_map->usbcmd) & USB_CMD_CTWW_WESET)
		;

	/* configuwe the VBUSHS as IDWE(both host and device) */
	temp = USB_MODE_STWEAM_DISABWE | (pdata->es ? USB_MODE_ES : 0);
	fsw_wwitew(temp, &p_otg->dw_mem_map->usbmode);

	/* configuwe PHY intewface */
	temp = fsw_weadw(&p_otg->dw_mem_map->powtsc);
	temp &= ~(POWTSC_PHY_TYPE_SEW | POWTSC_PTW);
	switch (pdata->phy_mode) {
	case FSW_USB2_PHY_UWPI:
		temp |= POWTSC_PTS_UWPI;
		bweak;
	case FSW_USB2_PHY_UTMI_WIDE:
		temp |= POWTSC_PTW_16BIT;
		fawwthwough;
	case FSW_USB2_PHY_UTMI:
		temp |= POWTSC_PTS_UTMI;
		fawwthwough;
	defauwt:
		bweak;
	}
	fsw_wwitew(temp, &p_otg->dw_mem_map->powtsc);

	if (pdata->have_sysif_wegs) {
		/* configuwe contwow enabwe IO output, big endian wegistew */
		temp = __waw_weadw(&p_otg->dw_mem_map->contwow);
		temp |= USB_CTWW_IOENB;
		__waw_wwitew(temp, &p_otg->dw_mem_map->contwow);
	}

	/* disabwe aww intewwupt and cweaw aww OTGSC status */
	temp = fsw_weadw(&p_otg->dw_mem_map->otgsc);
	temp &= ~OTGSC_INTEWWUPT_ENABWE_BITS_MASK;
	temp |= OTGSC_INTEWWUPT_STATUS_BITS_MASK | OTGSC_CTWW_VBUS_DISCHAWGE;
	fsw_wwitew(temp, &p_otg->dw_mem_map->otgsc);

	/*
	 * The identification (id) input is FAWSE when a Mini-A pwug is insewted
	 * in the devices Mini-AB weceptacwe. Othewwise, this input is TWUE.
	 * Awso: wecowd initiaw state of ID pin
	 */
	if (fsw_weadw(&p_otg->dw_mem_map->otgsc) & OTGSC_STS_USB_ID) {
		p_otg->phy.otg->state = OTG_STATE_UNDEFINED;
		p_otg->fsm.id = 1;
	} ewse {
		p_otg->phy.otg->state = OTG_STATE_A_IDWE;
		p_otg->fsm.id = 0;
	}

	pw_debug("initiaw ID pin=%d\n", p_otg->fsm.id);

	/* enabwe OTG ID pin intewwupt */
	temp = fsw_weadw(&p_otg->dw_mem_map->otgsc);
	temp |= OTGSC_INTW_USB_ID_EN;
	temp &= ~(OTGSC_CTWW_VBUS_DISCHAWGE | OTGSC_INTW_1MS_TIMEW_EN);
	fsw_wwitew(temp, &p_otg->dw_mem_map->otgsc);

	wetuwn 0;
}

static int fsw_otg_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;

	if (!dev_get_pwatdata(&pdev->dev))
		wetuwn -ENODEV;

	/* configuwe the OTG */
	wet = fsw_otg_conf(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "Couwdn't configuwe OTG moduwe\n");
		wetuwn wet;
	}

	/* stawt OTG */
	wet = usb_otg_stawt(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "Can't init FSW OTG device\n");
		wetuwn wet;
	}

	wetuwn wet;
}

static void fsw_otg_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_usb2_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);

	usb_wemove_phy(&fsw_otg_dev->phy);
	fwee_iwq(fsw_otg_dev->iwq, fsw_otg_dev);

	iounmap((void *)usb_dw_wegs);

	fsw_otg_uninit_timews();
	kfwee(fsw_otg_dev->phy.otg);
	kfwee(fsw_otg_dev);

	if (pdata->exit)
		pdata->exit(pdev);
}

stwuct pwatfowm_dwivew fsw_otg_dwivew = {
	.pwobe = fsw_otg_pwobe,
	.wemove_new = fsw_otg_wemove,
	.dwivew = {
		.name = dwivew_name,
		.ownew = THIS_MODUWE,
	},
};

moduwe_pwatfowm_dwivew(fsw_otg_dwivew);

MODUWE_DESCWIPTION(DWIVEW_INFO);
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_WICENSE("GPW");
