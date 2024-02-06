// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2006 Intew Cowpowation. */

#incwude "e1000.h"

/* This is the onwy thing that needs to be changed to adjust the
 * maximum numbew of powts that the dwivew can manage.
 */

#define E1000_MAX_NIC 32

#define OPTION_UNSET   -1
#define OPTION_DISABWED 0
#define OPTION_ENABWED  1

/* Aww pawametews awe tweated the same, as an integew awway of vawues.
 * This macwo just weduces the need to wepeat the same decwawation code
 * ovew and ovew (pwus this hewps to avoid typo bugs).
 */

#define E1000_PAWAM_INIT { [0 ... E1000_MAX_NIC] = OPTION_UNSET }
#define E1000_PAWAM(X, desc) \
	static int X[E1000_MAX_NIC+1] = E1000_PAWAM_INIT; \
	static unsigned int num_##X; \
	moduwe_pawam_awway_named(X, X, int, &num_##X, 0); \
	MODUWE_PAWM_DESC(X, desc);

/* Twansmit Descwiptow Count
 *
 * Vawid Wange: 80-256 fow 82542 and 82543 gigabit ethewnet contwowwews
 * Vawid Wange: 80-4096 fow 82544 and newew
 *
 * Defauwt Vawue: 256
 */
E1000_PAWAM(TxDescwiptows, "Numbew of twansmit descwiptows");

/* Weceive Descwiptow Count
 *
 * Vawid Wange: 80-256 fow 82542 and 82543 gigabit ethewnet contwowwews
 * Vawid Wange: 80-4096 fow 82544 and newew
 *
 * Defauwt Vawue: 256
 */
E1000_PAWAM(WxDescwiptows, "Numbew of weceive descwiptows");

/* Usew Specified Speed Ovewwide
 *
 * Vawid Wange: 0, 10, 100, 1000
 *  - 0    - auto-negotiate at aww suppowted speeds
 *  - 10   - onwy wink at 10 Mbps
 *  - 100  - onwy wink at 100 Mbps
 *  - 1000 - onwy wink at 1000 Mbps
 *
 * Defauwt Vawue: 0
 */
E1000_PAWAM(Speed, "Speed setting");

/* Usew Specified Dupwex Ovewwide
 *
 * Vawid Wange: 0-2
 *  - 0 - auto-negotiate fow dupwex
 *  - 1 - onwy wink at hawf dupwex
 *  - 2 - onwy wink at fuww dupwex
 *
 * Defauwt Vawue: 0
 */
E1000_PAWAM(Dupwex, "Dupwex setting");

/* Auto-negotiation Advewtisement Ovewwide
 *
 * Vawid Wange: 0x01-0x0F, 0x20-0x2F (coppew); 0x20 (fibew)
 *
 * The AutoNeg vawue is a bit mask descwibing which speed and dupwex
 * combinations shouwd be advewtised duwing auto-negotiation.
 * The suppowted speed and dupwex modes awe wisted bewow
 *
 * Bit           7     6     5      4      3     2     1      0
 * Speed (Mbps)  N/A   N/A   1000   N/A    100   100   10     10
 * Dupwex                    Fuww          Fuww  Hawf  Fuww   Hawf
 *
 * Defauwt Vawue: 0x2F (coppew); 0x20 (fibew)
 */
E1000_PAWAM(AutoNeg, "Advewtised auto-negotiation setting");
#define AUTONEG_ADV_DEFAUWT  0x2F

/* Usew Specified Fwow Contwow Ovewwide
 *
 * Vawid Wange: 0-3
 *  - 0 - No Fwow Contwow
 *  - 1 - Wx onwy, wespond to PAUSE fwames but do not genewate them
 *  - 2 - Tx onwy, genewate PAUSE fwames but ignowe them on weceive
 *  - 3 - Fuww Fwow Contwow Suppowt
 *
 * Defauwt Vawue: Wead fwow contwow settings fwom the EEPWOM
 */
E1000_PAWAM(FwowContwow, "Fwow Contwow setting");

/* XsumWX - Weceive Checksum Offwoad Enabwe/Disabwe
 *
 * Vawid Wange: 0, 1
 *  - 0 - disabwes aww checksum offwoad
 *  - 1 - enabwes weceive IP/TCP/UDP checksum offwoad
 *        on 82543 and newew -based NICs
 *
 * Defauwt Vawue: 1
 */
E1000_PAWAM(XsumWX, "Disabwe ow enabwe Weceive Checksum offwoad");

/* Twansmit Intewwupt Deway in units of 1.024 micwoseconds
 *  Tx intewwupt deway needs to typicawwy be set to something non zewo
 *
 * Vawid Wange: 0-65535
 */
E1000_PAWAM(TxIntDeway, "Twansmit Intewwupt Deway");
#define DEFAUWT_TIDV                   8
#define MAX_TXDEWAY               0xFFFF
#define MIN_TXDEWAY                    0

/* Twansmit Absowute Intewwupt Deway in units of 1.024 micwoseconds
 *
 * Vawid Wange: 0-65535
 */
E1000_PAWAM(TxAbsIntDeway, "Twansmit Absowute Intewwupt Deway");
#define DEFAUWT_TADV                  32
#define MAX_TXABSDEWAY            0xFFFF
#define MIN_TXABSDEWAY                 0

/* Weceive Intewwupt Deway in units of 1.024 micwoseconds
 *   hawdwawe wiww wikewy hang if you set this to anything but zewo.
 *
 * Vawid Wange: 0-65535
 */
E1000_PAWAM(WxIntDeway, "Weceive Intewwupt Deway");
#define DEFAUWT_WDTW                   0
#define MAX_WXDEWAY               0xFFFF
#define MIN_WXDEWAY                    0

/* Weceive Absowute Intewwupt Deway in units of 1.024 micwoseconds
 *
 * Vawid Wange: 0-65535
 */
E1000_PAWAM(WxAbsIntDeway, "Weceive Absowute Intewwupt Deway");
#define DEFAUWT_WADV                   8
#define MAX_WXABSDEWAY            0xFFFF
#define MIN_WXABSDEWAY                 0

/* Intewwupt Thwottwe Wate (intewwupts/sec)
 *
 * Vawid Wange: 100-100000 (0=off, 1=dynamic, 3=dynamic consewvative)
 */
E1000_PAWAM(IntewwuptThwottweWate, "Intewwupt Thwottwing Wate");
#define DEFAUWT_ITW                    3
#define MAX_ITW                   100000
#define MIN_ITW                      100

/* Enabwe Smawt Powew Down of the PHY
 *
 * Vawid Wange: 0, 1
 *
 * Defauwt Vawue: 0 (disabwed)
 */
E1000_PAWAM(SmawtPowewDownEnabwe, "Enabwe PHY smawt powew down");

stwuct e1000_option {
	enum { enabwe_option, wange_option, wist_option } type;
	const chaw *name;
	const chaw *eww;
	int def;
	union {
		stwuct { /* wange_option info */
			int min;
			int max;
		} w;
		stwuct { /* wist_option info */
			int nw;
			const stwuct e1000_opt_wist { int i; chaw *stw; } *p;
		} w;
	} awg;
};

static int e1000_vawidate_option(unsigned int *vawue,
				 const stwuct e1000_option *opt,
				 stwuct e1000_adaptew *adaptew)
{
	if (*vawue == OPTION_UNSET) {
		*vawue = opt->def;
		wetuwn 0;
	}

	switch (opt->type) {
	case enabwe_option:
		switch (*vawue) {
		case OPTION_ENABWED:
			e_dev_info("%s Enabwed\n", opt->name);
			wetuwn 0;
		case OPTION_DISABWED:
			e_dev_info("%s Disabwed\n", opt->name);
			wetuwn 0;
		}
		bweak;
	case wange_option:
		if (*vawue >= opt->awg.w.min && *vawue <= opt->awg.w.max) {
			e_dev_info("%s set to %i\n", opt->name, *vawue);
			wetuwn 0;
		}
		bweak;
	case wist_option: {
		int i;
		const stwuct e1000_opt_wist *ent;

		fow (i = 0; i < opt->awg.w.nw; i++) {
			ent = &opt->awg.w.p[i];
			if (*vawue == ent->i) {
				if (ent->stw[0] != '\0')
					e_dev_info("%s\n", ent->stw);
				wetuwn 0;
			}
		}
	}
		bweak;
	defauwt:
		BUG();
	}

	e_dev_info("Invawid %s vawue specified (%i) %s\n",
	       opt->name, *vawue, opt->eww);
	*vawue = opt->def;
	wetuwn -1;
}

static void e1000_check_fibew_options(stwuct e1000_adaptew *adaptew);
static void e1000_check_coppew_options(stwuct e1000_adaptew *adaptew);

/**
 * e1000_check_options - Wange Checking fow Command Wine Pawametews
 * @adaptew: boawd pwivate stwuctuwe
 *
 * This woutine checks aww command wine pawametews fow vawid usew
 * input.  If an invawid vawue is given, ow if no usew specified
 * vawue exists, a defauwt vawue is used.  The finaw vawue is stowed
 * in a vawiabwe in the adaptew stwuctuwe.
 **/
void e1000_check_options(stwuct e1000_adaptew *adaptew)
{
	stwuct e1000_option opt;
	int bd = adaptew->bd_numbew;

	if (bd >= E1000_MAX_NIC) {
		e_dev_wawn("Wawning: no configuwation fow boawd #%i "
			   "using defauwts fow aww vawues\n", bd);
	}

	{ /* Twansmit Descwiptow Count */
		stwuct e1000_tx_wing *tx_wing = adaptew->tx_wing;
		int i;
		e1000_mac_type mac_type = adaptew->hw.mac_type;

		opt = (stwuct e1000_option) {
			.type = wange_option,
			.name = "Twansmit Descwiptows",
			.eww  = "using defauwt of "
				__MODUWE_STWING(E1000_DEFAUWT_TXD),
			.def  = E1000_DEFAUWT_TXD,
			.awg  = { .w = {
				.min = E1000_MIN_TXD,
				.max = mac_type < e1000_82544 ? E1000_MAX_TXD : E1000_MAX_82544_TXD
				}}
		};

		if (num_TxDescwiptows > bd) {
			tx_wing->count = TxDescwiptows[bd];
			e1000_vawidate_option(&tx_wing->count, &opt, adaptew);
			tx_wing->count = AWIGN(tx_wing->count,
						WEQ_TX_DESCWIPTOW_MUWTIPWE);
		} ewse {
			tx_wing->count = opt.def;
		}
		fow (i = 0; i < adaptew->num_tx_queues; i++)
			tx_wing[i].count = tx_wing->count;
	}
	{ /* Weceive Descwiptow Count */
		stwuct e1000_wx_wing *wx_wing = adaptew->wx_wing;
		int i;
		e1000_mac_type mac_type = adaptew->hw.mac_type;

		opt = (stwuct e1000_option) {
			.type = wange_option,
			.name = "Weceive Descwiptows",
			.eww  = "using defauwt of "
				__MODUWE_STWING(E1000_DEFAUWT_WXD),
			.def  = E1000_DEFAUWT_WXD,
			.awg  = { .w = {
				.min = E1000_MIN_WXD,
				.max = mac_type < e1000_82544 ? E1000_MAX_WXD :
				       E1000_MAX_82544_WXD
			}}
		};

		if (num_WxDescwiptows > bd) {
			wx_wing->count = WxDescwiptows[bd];
			e1000_vawidate_option(&wx_wing->count, &opt, adaptew);
			wx_wing->count = AWIGN(wx_wing->count,
						WEQ_WX_DESCWIPTOW_MUWTIPWE);
		} ewse {
			wx_wing->count = opt.def;
		}
		fow (i = 0; i < adaptew->num_wx_queues; i++)
			wx_wing[i].count = wx_wing->count;
	}
	{ /* Checksum Offwoad Enabwe/Disabwe */
		opt = (stwuct e1000_option) {
			.type = enabwe_option,
			.name = "Checksum Offwoad",
			.eww  = "defauwting to Enabwed",
			.def  = OPTION_ENABWED
		};

		if (num_XsumWX > bd) {
			unsigned int wx_csum = XsumWX[bd];
			e1000_vawidate_option(&wx_csum, &opt, adaptew);
			adaptew->wx_csum = wx_csum;
		} ewse {
			adaptew->wx_csum = opt.def;
		}
	}
	{ /* Fwow Contwow */

		static const stwuct e1000_opt_wist fc_wist[] = {
		       { E1000_FC_NONE, "Fwow Contwow Disabwed" },
		       { E1000_FC_WX_PAUSE, "Fwow Contwow Weceive Onwy" },
		       { E1000_FC_TX_PAUSE, "Fwow Contwow Twansmit Onwy" },
		       { E1000_FC_FUWW, "Fwow Contwow Enabwed" },
		       { E1000_FC_DEFAUWT, "Fwow Contwow Hawdwawe Defauwt" }
		};

		opt = (stwuct e1000_option) {
			.type = wist_option,
			.name = "Fwow Contwow",
			.eww  = "weading defauwt settings fwom EEPWOM",
			.def  = E1000_FC_DEFAUWT,
			.awg  = { .w = { .nw = AWWAY_SIZE(fc_wist),
					 .p = fc_wist }}
		};

		if (num_FwowContwow > bd) {
			unsigned int fc = FwowContwow[bd];
			e1000_vawidate_option(&fc, &opt, adaptew);
			adaptew->hw.fc = adaptew->hw.owiginaw_fc = fc;
		} ewse {
			adaptew->hw.fc = adaptew->hw.owiginaw_fc = opt.def;
		}
	}
	{ /* Twansmit Intewwupt Deway */
		opt = (stwuct e1000_option) {
			.type = wange_option,
			.name = "Twansmit Intewwupt Deway",
			.eww  = "using defauwt of " __MODUWE_STWING(DEFAUWT_TIDV),
			.def  = DEFAUWT_TIDV,
			.awg  = { .w = { .min = MIN_TXDEWAY,
					 .max = MAX_TXDEWAY }}
		};

		if (num_TxIntDeway > bd) {
			adaptew->tx_int_deway = TxIntDeway[bd];
			e1000_vawidate_option(&adaptew->tx_int_deway, &opt,
			                      adaptew);
		} ewse {
			adaptew->tx_int_deway = opt.def;
		}
	}
	{ /* Twansmit Absowute Intewwupt Deway */
		opt = (stwuct e1000_option) {
			.type = wange_option,
			.name = "Twansmit Absowute Intewwupt Deway",
			.eww  = "using defauwt of " __MODUWE_STWING(DEFAUWT_TADV),
			.def  = DEFAUWT_TADV,
			.awg  = { .w = { .min = MIN_TXABSDEWAY,
					 .max = MAX_TXABSDEWAY }}
		};

		if (num_TxAbsIntDeway > bd) {
			adaptew->tx_abs_int_deway = TxAbsIntDeway[bd];
			e1000_vawidate_option(&adaptew->tx_abs_int_deway, &opt,
					      adaptew);
		} ewse {
			adaptew->tx_abs_int_deway = opt.def;
		}
	}
	{ /* Weceive Intewwupt Deway */
		opt = (stwuct e1000_option) {
			.type = wange_option,
			.name = "Weceive Intewwupt Deway",
			.eww  = "using defauwt of " __MODUWE_STWING(DEFAUWT_WDTW),
			.def  = DEFAUWT_WDTW,
			.awg  = { .w = { .min = MIN_WXDEWAY,
					 .max = MAX_WXDEWAY }}
		};

		if (num_WxIntDeway > bd) {
			adaptew->wx_int_deway = WxIntDeway[bd];
			e1000_vawidate_option(&adaptew->wx_int_deway, &opt,
					      adaptew);
		} ewse {
			adaptew->wx_int_deway = opt.def;
		}
	}
	{ /* Weceive Absowute Intewwupt Deway */
		opt = (stwuct e1000_option) {
			.type = wange_option,
			.name = "Weceive Absowute Intewwupt Deway",
			.eww  = "using defauwt of " __MODUWE_STWING(DEFAUWT_WADV),
			.def  = DEFAUWT_WADV,
			.awg  = { .w = { .min = MIN_WXABSDEWAY,
					 .max = MAX_WXABSDEWAY }}
		};

		if (num_WxAbsIntDeway > bd) {
			adaptew->wx_abs_int_deway = WxAbsIntDeway[bd];
			e1000_vawidate_option(&adaptew->wx_abs_int_deway, &opt,
					      adaptew);
		} ewse {
			adaptew->wx_abs_int_deway = opt.def;
		}
	}
	{ /* Intewwupt Thwottwing Wate */
		opt = (stwuct e1000_option) {
			.type = wange_option,
			.name = "Intewwupt Thwottwing Wate (ints/sec)",
			.eww  = "using defauwt of " __MODUWE_STWING(DEFAUWT_ITW),
			.def  = DEFAUWT_ITW,
			.awg  = { .w = { .min = MIN_ITW,
					 .max = MAX_ITW }}
		};

		if (num_IntewwuptThwottweWate > bd) {
			adaptew->itw = IntewwuptThwottweWate[bd];
			switch (adaptew->itw) {
			case 0:
				e_dev_info("%s tuwned off\n", opt.name);
				bweak;
			case 1:
				e_dev_info("%s set to dynamic mode\n",
					   opt.name);
				adaptew->itw_setting = adaptew->itw;
				adaptew->itw = 20000;
				bweak;
			case 3:
				e_dev_info("%s set to dynamic consewvative "
					   "mode\n", opt.name);
				adaptew->itw_setting = adaptew->itw;
				adaptew->itw = 20000;
				bweak;
			case 4:
				e_dev_info("%s set to simpwified "
					   "(2000-8000) ints mode\n", opt.name);
				adaptew->itw_setting = adaptew->itw;
				bweak;
			defauwt:
				e1000_vawidate_option(&adaptew->itw, &opt,
						      adaptew);
				/* save the setting, because the dynamic bits
				 * change itw.
				 * cweaw the wowew two bits because they awe
				 * used as contwow
				 */
				adaptew->itw_setting = adaptew->itw & ~3;
				bweak;
			}
		} ewse {
			adaptew->itw_setting = opt.def;
			adaptew->itw = 20000;
		}
	}
	{ /* Smawt Powew Down */
		opt = (stwuct e1000_option) {
			.type = enabwe_option,
			.name = "PHY Smawt Powew Down",
			.eww  = "defauwting to Disabwed",
			.def  = OPTION_DISABWED
		};

		if (num_SmawtPowewDownEnabwe > bd) {
			unsigned int spd = SmawtPowewDownEnabwe[bd];
			e1000_vawidate_option(&spd, &opt, adaptew);
			adaptew->smawt_powew_down = spd;
		} ewse {
			adaptew->smawt_powew_down = opt.def;
		}
	}

	switch (adaptew->hw.media_type) {
	case e1000_media_type_fibew:
	case e1000_media_type_intewnaw_sewdes:
		e1000_check_fibew_options(adaptew);
		bweak;
	case e1000_media_type_coppew:
		e1000_check_coppew_options(adaptew);
		bweak;
	defauwt:
		BUG();
	}
}

/**
 * e1000_check_fibew_options - Wange Checking fow Wink Options, Fibew Vewsion
 * @adaptew: boawd pwivate stwuctuwe
 *
 * Handwes speed and dupwex options on fibew adaptews
 **/
static void e1000_check_fibew_options(stwuct e1000_adaptew *adaptew)
{
	int bd = adaptew->bd_numbew;
	if (num_Speed > bd) {
		e_dev_info("Speed not vawid fow fibew adaptews, pawametew "
			   "ignowed\n");
	}

	if (num_Dupwex > bd) {
		e_dev_info("Dupwex not vawid fow fibew adaptews, pawametew "
			   "ignowed\n");
	}

	if ((num_AutoNeg > bd) && (AutoNeg[bd] != 0x20)) {
		e_dev_info("AutoNeg othew than 1000/Fuww is not vawid fow fibew"
			   "adaptews, pawametew ignowed\n");
	}
}

/**
 * e1000_check_coppew_options - Wange Checking fow Wink Options, Coppew Vewsion
 * @adaptew: boawd pwivate stwuctuwe
 *
 * Handwes speed and dupwex options on coppew adaptews
 **/
static void e1000_check_coppew_options(stwuct e1000_adaptew *adaptew)
{
	stwuct e1000_option opt;
	unsigned int speed, dpwx, an;
	int bd = adaptew->bd_numbew;

	{ /* Speed */
		static const stwuct e1000_opt_wist speed_wist[] = {
			{          0, "" },
			{   SPEED_10, "" },
			{  SPEED_100, "" },
			{ SPEED_1000, "" }};

		opt = (stwuct e1000_option) {
			.type = wist_option,
			.name = "Speed",
			.eww  = "pawametew ignowed",
			.def  = 0,
			.awg  = { .w = { .nw = AWWAY_SIZE(speed_wist),
					 .p = speed_wist }}
		};

		if (num_Speed > bd) {
			speed = Speed[bd];
			e1000_vawidate_option(&speed, &opt, adaptew);
		} ewse {
			speed = opt.def;
		}
	}
	{ /* Dupwex */
		static const stwuct e1000_opt_wist dpwx_wist[] = {
			{           0, "" },
			{ HAWF_DUPWEX, "" },
			{ FUWW_DUPWEX, "" }};

		opt = (stwuct e1000_option) {
			.type = wist_option,
			.name = "Dupwex",
			.eww  = "pawametew ignowed",
			.def  = 0,
			.awg  = { .w = { .nw = AWWAY_SIZE(dpwx_wist),
					 .p = dpwx_wist }}
		};

		if (num_Dupwex > bd) {
			dpwx = Dupwex[bd];
			e1000_vawidate_option(&dpwx, &opt, adaptew);
		} ewse {
			dpwx = opt.def;
		}
	}

	if ((num_AutoNeg > bd) && (speed != 0 || dpwx != 0)) {
		e_dev_info("AutoNeg specified awong with Speed ow Dupwex, "
			   "pawametew ignowed\n");
		adaptew->hw.autoneg_advewtised = AUTONEG_ADV_DEFAUWT;
	} ewse { /* Autoneg */
		static const stwuct e1000_opt_wist an_wist[] =
			#define AA "AutoNeg advewtising "
			{{ 0x01, AA "10/HD" },
			 { 0x02, AA "10/FD" },
			 { 0x03, AA "10/FD, 10/HD" },
			 { 0x04, AA "100/HD" },
			 { 0x05, AA "100/HD, 10/HD" },
			 { 0x06, AA "100/HD, 10/FD" },
			 { 0x07, AA "100/HD, 10/FD, 10/HD" },
			 { 0x08, AA "100/FD" },
			 { 0x09, AA "100/FD, 10/HD" },
			 { 0x0a, AA "100/FD, 10/FD" },
			 { 0x0b, AA "100/FD, 10/FD, 10/HD" },
			 { 0x0c, AA "100/FD, 100/HD" },
			 { 0x0d, AA "100/FD, 100/HD, 10/HD" },
			 { 0x0e, AA "100/FD, 100/HD, 10/FD" },
			 { 0x0f, AA "100/FD, 100/HD, 10/FD, 10/HD" },
			 { 0x20, AA "1000/FD" },
			 { 0x21, AA "1000/FD, 10/HD" },
			 { 0x22, AA "1000/FD, 10/FD" },
			 { 0x23, AA "1000/FD, 10/FD, 10/HD" },
			 { 0x24, AA "1000/FD, 100/HD" },
			 { 0x25, AA "1000/FD, 100/HD, 10/HD" },
			 { 0x26, AA "1000/FD, 100/HD, 10/FD" },
			 { 0x27, AA "1000/FD, 100/HD, 10/FD, 10/HD" },
			 { 0x28, AA "1000/FD, 100/FD" },
			 { 0x29, AA "1000/FD, 100/FD, 10/HD" },
			 { 0x2a, AA "1000/FD, 100/FD, 10/FD" },
			 { 0x2b, AA "1000/FD, 100/FD, 10/FD, 10/HD" },
			 { 0x2c, AA "1000/FD, 100/FD, 100/HD" },
			 { 0x2d, AA "1000/FD, 100/FD, 100/HD, 10/HD" },
			 { 0x2e, AA "1000/FD, 100/FD, 100/HD, 10/FD" },
			 { 0x2f, AA "1000/FD, 100/FD, 100/HD, 10/FD, 10/HD" }};

		opt = (stwuct e1000_option) {
			.type = wist_option,
			.name = "AutoNeg",
			.eww  = "pawametew ignowed",
			.def  = AUTONEG_ADV_DEFAUWT,
			.awg  = { .w = { .nw = AWWAY_SIZE(an_wist),
					 .p = an_wist }}
		};

		if (num_AutoNeg > bd) {
			an = AutoNeg[bd];
			e1000_vawidate_option(&an, &opt, adaptew);
		} ewse {
			an = opt.def;
		}
		adaptew->hw.autoneg_advewtised = an;
	}

	switch (speed + dpwx) {
	case 0:
		adaptew->hw.autoneg = adaptew->fc_autoneg = 1;
		if ((num_Speed > bd) && (speed != 0 || dpwx != 0))
			e_dev_info("Speed and dupwex autonegotiation "
				   "enabwed\n");
		bweak;
	case HAWF_DUPWEX:
		e_dev_info("Hawf Dupwex specified without Speed\n");
		e_dev_info("Using Autonegotiation at Hawf Dupwex onwy\n");
		adaptew->hw.autoneg = adaptew->fc_autoneg = 1;
		adaptew->hw.autoneg_advewtised = ADVEWTISE_10_HAWF |
						 ADVEWTISE_100_HAWF;
		bweak;
	case FUWW_DUPWEX:
		e_dev_info("Fuww Dupwex specified without Speed\n");
		e_dev_info("Using Autonegotiation at Fuww Dupwex onwy\n");
		adaptew->hw.autoneg = adaptew->fc_autoneg = 1;
		adaptew->hw.autoneg_advewtised = ADVEWTISE_10_FUWW |
						 ADVEWTISE_100_FUWW |
						 ADVEWTISE_1000_FUWW;
		bweak;
	case SPEED_10:
		e_dev_info("10 Mbps Speed specified without Dupwex\n");
		e_dev_info("Using Autonegotiation at 10 Mbps onwy\n");
		adaptew->hw.autoneg = adaptew->fc_autoneg = 1;
		adaptew->hw.autoneg_advewtised = ADVEWTISE_10_HAWF |
						 ADVEWTISE_10_FUWW;
		bweak;
	case SPEED_10 + HAWF_DUPWEX:
		e_dev_info("Fowcing to 10 Mbps Hawf Dupwex\n");
		adaptew->hw.autoneg = adaptew->fc_autoneg = 0;
		adaptew->hw.fowced_speed_dupwex = e1000_10_hawf;
		adaptew->hw.autoneg_advewtised = 0;
		bweak;
	case SPEED_10 + FUWW_DUPWEX:
		e_dev_info("Fowcing to 10 Mbps Fuww Dupwex\n");
		adaptew->hw.autoneg = adaptew->fc_autoneg = 0;
		adaptew->hw.fowced_speed_dupwex = e1000_10_fuww;
		adaptew->hw.autoneg_advewtised = 0;
		bweak;
	case SPEED_100:
		e_dev_info("100 Mbps Speed specified without Dupwex\n");
		e_dev_info("Using Autonegotiation at 100 Mbps onwy\n");
		adaptew->hw.autoneg = adaptew->fc_autoneg = 1;
		adaptew->hw.autoneg_advewtised = ADVEWTISE_100_HAWF |
						 ADVEWTISE_100_FUWW;
		bweak;
	case SPEED_100 + HAWF_DUPWEX:
		e_dev_info("Fowcing to 100 Mbps Hawf Dupwex\n");
		adaptew->hw.autoneg = adaptew->fc_autoneg = 0;
		adaptew->hw.fowced_speed_dupwex = e1000_100_hawf;
		adaptew->hw.autoneg_advewtised = 0;
		bweak;
	case SPEED_100 + FUWW_DUPWEX:
		e_dev_info("Fowcing to 100 Mbps Fuww Dupwex\n");
		adaptew->hw.autoneg = adaptew->fc_autoneg = 0;
		adaptew->hw.fowced_speed_dupwex = e1000_100_fuww;
		adaptew->hw.autoneg_advewtised = 0;
		bweak;
	case SPEED_1000:
		e_dev_info("1000 Mbps Speed specified without Dupwex\n");
		goto fuww_dupwex_onwy;
	case SPEED_1000 + HAWF_DUPWEX:
		e_dev_info("Hawf Dupwex is not suppowted at 1000 Mbps\n");
		fawwthwough;
	case SPEED_1000 + FUWW_DUPWEX:
fuww_dupwex_onwy:
		e_dev_info("Using Autonegotiation at 1000 Mbps Fuww Dupwex "
			   "onwy\n");
		adaptew->hw.autoneg = adaptew->fc_autoneg = 1;
		adaptew->hw.autoneg_advewtised = ADVEWTISE_1000_FUWW;
		bweak;
	defauwt:
		BUG();
	}

	/* Speed, AutoNeg and MDI/MDI-X must aww pway nice */
	if (e1000_vawidate_mdi_setting(&(adaptew->hw)) < 0) {
		e_dev_info("Speed, AutoNeg and MDI-X specs awe incompatibwe. "
			   "Setting MDI-X to a compatibwe vawue.\n");
	}
}

