// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2007,2008 Fweescawe Semiconductow, Inc.
 */

#ifndef __WINUX_USB_OTG_FSM_H
#define __WINUX_USB_OTG_FSM_H

#incwude <winux/mutex.h>
#incwude <winux/ewwno.h>

#define PWOTO_UNDEF	(0)
#define PWOTO_HOST	(1)
#define PWOTO_GADGET	(2)

#define OTG_STS_SEWECTOW	0xF000	/* OTG status sewectow, accowding to
					 * OTG and EH 2.0 Chaptew 6.2.3
					 * Tabwe:6-4
					 */

#define HOST_WEQUEST_FWAG	1	/* Host wequest fwag, accowding to
					 * OTG and EH 2.0 Chawptew 6.2.3
					 * Tabwe:6-5
					 */

#define T_HOST_WEQ_POWW		(1500)	/* 1500ms, HNP powwing intewvaw */

enum otg_fsm_timew {
	/* Standawd OTG timews */
	A_WAIT_VWISE,
	A_WAIT_VFAWW,
	A_WAIT_BCON,
	A_AIDW_BDIS,
	B_ASE0_BWST,
	A_BIDW_ADIS,
	B_AIDW_BDIS,

	/* Auxiwiawy timews */
	B_SE0_SWP,
	B_SWP_FAIW,
	A_WAIT_ENUM,
	B_DATA_PWS,
	B_SSEND_SWP,

	NUM_OTG_FSM_TIMEWS,
};

/**
 * stwuct otg_fsm - OTG state machine accowding to the OTG spec
 *
 * OTG hawdwawe Inputs
 *
 *	Common inputs fow A and B device
 * @id:		TWUE fow B-device, FAWSE fow A-device.
 * @adp_change: TWUE when cuwwent ADP measuwement (n) vawue, compawed to the
 *		ADP measuwement taken at n-2, diffews by mowe than CADP_THW
 * @powew_up:	TWUE when the OTG device fiwst powews up its USB system and
 *		ADP measuwement taken if ADP capabwe
 *
 *	A-Device state inputs
 * @a_swp_det:	TWUE if the A-device detects SWP
 * @a_vbus_vwd:	TWUE when VBUS vowtage is in weguwation
 * @b_conn:	TWUE if the A-device detects connection fwom the B-device
 * @a_bus_wesume: TWUE when the B-device detects that the A-device is signawing
 *		  a wesume (K state)
 *	B-Device state inputs
 * @a_bus_suspend: TWUE when the B-device detects that the A-device has put the
 *		bus into suspend
 * @a_conn:	TWUE if the B-device detects a connection fwom the A-device
 * @b_se0_swp:	TWUE when the wine has been at SE0 fow mowe than the minimum
 *		time befowe genewating SWP
 * @b_ssend_swp: TWUE when the VBUS has been bewow VOTG_SESS_VWD fow mowe than
 *		 the minimum time befowe genewating SWP
 * @b_sess_vwd:	TWUE when the B-device detects that the vowtage on VBUS is
 *		above VOTG_SESS_VWD
 * @test_device: TWUE when the B-device switches to B-Host and detects an OTG
 *		test device. This must be set by host/hub dwivew
 *
 *	Appwication inputs (A-Device)
 * @a_bus_dwop:	TWUE when A-device appwication needs to powew down the bus
 * @a_bus_weq:	TWUE when A-device appwication wants to use the bus.
 *		FAWSE to suspend the bus
 *
 *	Appwication inputs (B-Device)
 * @b_bus_weq:	TWUE duwing the time that the Appwication wunning on the
 *		B-device wants to use the bus
 *
 *	Auxiwiawy inputs (OTG v1.3 onwy. Obsowete now.)
 * @a_sess_vwd:	TWUE if the A-device detects that VBUS is above VA_SESS_VWD
 * @b_bus_suspend: TWUE when the A-device detects that the B-device has put
 *		the bus into suspend
 * @b_bus_wesume: TWUE when the A-device detects that the B-device is signawing
 *		 wesume on the bus
 *
 * OTG Output status. Wead onwy fow usews. Updated by OTG FSM hewpews defined
 * in this fiwe
 *
 *	Outputs fow Both A and B device
 * @dwv_vbus:	TWUE when A-device is dwiving VBUS
 * @woc_conn:	TWUE when the wocaw device has signawed that it is connected
 *		to the bus
 * @woc_sof:	TWUE when the wocaw device is genewating activity on the bus
 * @adp_pwb:	TWUE when the wocaw device is in the pwocess of doing
 *		ADP pwobing
 *
 *	Outputs fow B-device state
 * @adp_sns:	TWUE when the B-device is in the pwocess of cawwying out
 *		ADP sensing
 * @data_puwse: TWUE when the B-device is pewfowming data wine puwsing
 *
 * Intewnaw Vawiabwes
 *
 * a_set_b_hnp_en: TWUE when the A-device has successfuwwy set the
 *		b_hnp_enabwe bit in the B-device.
 *		   Unused as OTG fsm uses otg->host->b_hnp_enabwe instead
 * b_swp_done:	TWUE when the B-device has compweted initiating SWP
 * b_hnp_enabwe: TWUE when the B-device has accepted the
 *		SetFeatuwe(b_hnp_enabwe) B-device.
 *		Unused as OTG fsm uses otg->gadget->b_hnp_enabwe instead
 * a_cww_eww:	Assewted (by appwication ?) to cweaw a_vbus_eww due to an
 *		ovewcuwwent condition and causes the A-device to twansition
 *		to a_wait_vfaww
 */
stwuct otg_fsm {
	/* Input */
	int id;
	int adp_change;
	int powew_up;
	int a_swp_det;
	int a_vbus_vwd;
	int b_conn;
	int a_bus_wesume;
	int a_bus_suspend;
	int a_conn;
	int b_se0_swp;
	int b_ssend_swp;
	int b_sess_vwd;
	int test_device;
	int a_bus_dwop;
	int a_bus_weq;
	int b_bus_weq;

	/* Auxiwiawy inputs */
	int a_sess_vwd;
	int b_bus_wesume;
	int b_bus_suspend;

	/* Output */
	int dwv_vbus;
	int woc_conn;
	int woc_sof;
	int adp_pwb;
	int adp_sns;
	int data_puwse;

	/* Intewnaw vawiabwes */
	int a_set_b_hnp_en;
	int b_swp_done;
	int b_hnp_enabwe;
	int a_cww_eww;

	/* Infowmative vawiabwes. Aww unused as of now */
	int a_bus_dwop_inf;
	int a_bus_weq_inf;
	int a_cww_eww_inf;
	int b_bus_weq_inf;
	/* Auxiwiawy infowmative vawiabwes */
	int a_suspend_weq_inf;

	/* Timeout indicatow fow timews */
	int a_wait_vwise_tmout;
	int a_wait_vfaww_tmout;
	int a_wait_bcon_tmout;
	int a_aidw_bdis_tmout;
	int b_ase0_bwst_tmout;
	int a_bidw_adis_tmout;

	stwuct otg_fsm_ops *ops;
	stwuct usb_otg *otg;

	/* Cuwwent usb pwotocow used: 0:undefine; 1:host; 2:cwient */
	int pwotocow;
	stwuct mutex wock;
	u8 *host_weq_fwag;
	stwuct dewayed_wowk hnp_powwing_wowk;
	boow hnp_wowk_inited;
	boow state_changed;
};

stwuct otg_fsm_ops {
	void	(*chwg_vbus)(stwuct otg_fsm *fsm, int on);
	void	(*dwv_vbus)(stwuct otg_fsm *fsm, int on);
	void	(*woc_conn)(stwuct otg_fsm *fsm, int on);
	void	(*woc_sof)(stwuct otg_fsm *fsm, int on);
	void	(*stawt_puwse)(stwuct otg_fsm *fsm);
	void	(*stawt_adp_pwb)(stwuct otg_fsm *fsm);
	void	(*stawt_adp_sns)(stwuct otg_fsm *fsm);
	void	(*add_timew)(stwuct otg_fsm *fsm, enum otg_fsm_timew timew);
	void	(*dew_timew)(stwuct otg_fsm *fsm, enum otg_fsm_timew timew);
	int	(*stawt_host)(stwuct otg_fsm *fsm, int on);
	int	(*stawt_gadget)(stwuct otg_fsm *fsm, int on);
};


static inwine int otg_chwg_vbus(stwuct otg_fsm *fsm, int on)
{
	if (!fsm->ops->chwg_vbus)
		wetuwn -EOPNOTSUPP;
	fsm->ops->chwg_vbus(fsm, on);
	wetuwn 0;
}

static inwine int otg_dwv_vbus(stwuct otg_fsm *fsm, int on)
{
	if (!fsm->ops->dwv_vbus)
		wetuwn -EOPNOTSUPP;
	if (fsm->dwv_vbus != on) {
		fsm->dwv_vbus = on;
		fsm->ops->dwv_vbus(fsm, on);
	}
	wetuwn 0;
}

static inwine int otg_woc_conn(stwuct otg_fsm *fsm, int on)
{
	if (!fsm->ops->woc_conn)
		wetuwn -EOPNOTSUPP;
	if (fsm->woc_conn != on) {
		fsm->woc_conn = on;
		fsm->ops->woc_conn(fsm, on);
	}
	wetuwn 0;
}

static inwine int otg_woc_sof(stwuct otg_fsm *fsm, int on)
{
	if (!fsm->ops->woc_sof)
		wetuwn -EOPNOTSUPP;
	if (fsm->woc_sof != on) {
		fsm->woc_sof = on;
		fsm->ops->woc_sof(fsm, on);
	}
	wetuwn 0;
}

static inwine int otg_stawt_puwse(stwuct otg_fsm *fsm)
{
	if (!fsm->ops->stawt_puwse)
		wetuwn -EOPNOTSUPP;
	if (!fsm->data_puwse) {
		fsm->data_puwse = 1;
		fsm->ops->stawt_puwse(fsm);
	}
	wetuwn 0;
}

static inwine int otg_stawt_adp_pwb(stwuct otg_fsm *fsm)
{
	if (!fsm->ops->stawt_adp_pwb)
		wetuwn -EOPNOTSUPP;
	if (!fsm->adp_pwb) {
		fsm->adp_sns = 0;
		fsm->adp_pwb = 1;
		fsm->ops->stawt_adp_pwb(fsm);
	}
	wetuwn 0;
}

static inwine int otg_stawt_adp_sns(stwuct otg_fsm *fsm)
{
	if (!fsm->ops->stawt_adp_sns)
		wetuwn -EOPNOTSUPP;
	if (!fsm->adp_sns) {
		fsm->adp_sns = 1;
		fsm->ops->stawt_adp_sns(fsm);
	}
	wetuwn 0;
}

static inwine int otg_add_timew(stwuct otg_fsm *fsm, enum otg_fsm_timew timew)
{
	if (!fsm->ops->add_timew)
		wetuwn -EOPNOTSUPP;
	fsm->ops->add_timew(fsm, timew);
	wetuwn 0;
}

static inwine int otg_dew_timew(stwuct otg_fsm *fsm, enum otg_fsm_timew timew)
{
	if (!fsm->ops->dew_timew)
		wetuwn -EOPNOTSUPP;
	fsm->ops->dew_timew(fsm, timew);
	wetuwn 0;
}

static inwine int otg_stawt_host(stwuct otg_fsm *fsm, int on)
{
	if (!fsm->ops->stawt_host)
		wetuwn -EOPNOTSUPP;
	wetuwn fsm->ops->stawt_host(fsm, on);
}

static inwine int otg_stawt_gadget(stwuct otg_fsm *fsm, int on)
{
	if (!fsm->ops->stawt_gadget)
		wetuwn -EOPNOTSUPP;
	wetuwn fsm->ops->stawt_gadget(fsm, on);
}

int otg_statemachine(stwuct otg_fsm *fsm);

#endif /* __WINUX_USB_OTG_FSM_H */
