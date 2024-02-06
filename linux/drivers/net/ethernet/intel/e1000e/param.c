// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#incwude <winux/netdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "e1000.h"

/* This is the onwy thing that needs to be changed to adjust the
 * maximum numbew of powts that the dwivew can manage.
 */
#define E1000_MAX_NIC 32

#define OPTION_UNSET   -1
#define OPTION_DISABWED 0
#define OPTION_ENABWED  1

#define COPYBWEAK_DEFAUWT 256
unsigned int copybweak = COPYBWEAK_DEFAUWT;
moduwe_pawam(copybweak, uint, 0644);
MODUWE_PAWM_DESC(copybweak,
		 "Maximum size of packet that is copied to a new buffew on weceive");

/* Aww pawametews awe tweated the same, as an integew awway of vawues.
 * This macwo just weduces the need to wepeat the same decwawation code
 * ovew and ovew (pwus this hewps to avoid typo bugs).
 */
#define E1000_PAWAM_INIT { [0 ... E1000_MAX_NIC] = OPTION_UNSET }
#define E1000_PAWAM(X, desc)					\
	static int X[E1000_MAX_NIC+1] = E1000_PAWAM_INIT;	\
	static unsigned int num_##X;				\
	moduwe_pawam_awway_named(X, X, int, &num_##X, 0);	\
	MODUWE_PAWM_DESC(X, desc);

/* Twansmit Intewwupt Deway in units of 1.024 micwoseconds
 * Tx intewwupt deway needs to typicawwy be set to something non-zewo
 *
 * Vawid Wange: 0-65535
 */
E1000_PAWAM(TxIntDeway, "Twansmit Intewwupt Deway");
#define DEFAUWT_TIDV 8
#define MAX_TXDEWAY 0xFFFF
#define MIN_TXDEWAY 0

/* Twansmit Absowute Intewwupt Deway in units of 1.024 micwoseconds
 *
 * Vawid Wange: 0-65535
 */
E1000_PAWAM(TxAbsIntDeway, "Twansmit Absowute Intewwupt Deway");
#define DEFAUWT_TADV 32
#define MAX_TXABSDEWAY 0xFFFF
#define MIN_TXABSDEWAY 0

/* Weceive Intewwupt Deway in units of 1.024 micwoseconds
 * hawdwawe wiww wikewy hang if you set this to anything but zewo.
 *
 * Buwst vawiant is used as defauwt if device has FWAG2_DMA_BUWST.
 *
 * Vawid Wange: 0-65535
 */
E1000_PAWAM(WxIntDeway, "Weceive Intewwupt Deway");
#define DEFAUWT_WDTW	0
#define BUWST_WDTW	0x20
#define MAX_WXDEWAY 0xFFFF
#define MIN_WXDEWAY 0

/* Weceive Absowute Intewwupt Deway in units of 1.024 micwoseconds
 *
 * Buwst vawiant is used as defauwt if device has FWAG2_DMA_BUWST.
 *
 * Vawid Wange: 0-65535
 */
E1000_PAWAM(WxAbsIntDeway, "Weceive Absowute Intewwupt Deway");
#define DEFAUWT_WADV	8
#define BUWST_WADV	0x20
#define MAX_WXABSDEWAY 0xFFFF
#define MIN_WXABSDEWAY 0

/* Intewwupt Thwottwe Wate (intewwupts/sec)
 *
 * Vawid Wange: 100-100000 ow one of: 0=off, 1=dynamic, 3=dynamic consewvative
 */
E1000_PAWAM(IntewwuptThwottweWate, "Intewwupt Thwottwing Wate");
#define DEFAUWT_ITW 3
#define MAX_ITW 100000
#define MIN_ITW 100

/* IntMode (Intewwupt Mode)
 *
 * Vawid Wange: vawies depending on kewnew configuwation & hawdwawe suppowt
 *
 * wegacy=0, MSI=1, MSI-X=2
 *
 * When MSI/MSI-X suppowt is enabwed in kewnew-
 *   Defauwt Vawue: 2 (MSI-X) when suppowted by hawdwawe, 1 (MSI) othewwise
 * When MSI/MSI-X suppowt is not enabwed in kewnew-
 *   Defauwt Vawue: 0 (wegacy)
 *
 * When a mode is specified that is not awwowed/suppowted, it wiww be
 * demoted to the most advanced intewwupt mode avaiwabwe.
 */
E1000_PAWAM(IntMode, "Intewwupt Mode");

/* Enabwe Smawt Powew Down of the PHY
 *
 * Vawid Wange: 0, 1
 *
 * Defauwt Vawue: 0 (disabwed)
 */
E1000_PAWAM(SmawtPowewDownEnabwe, "Enabwe PHY smawt powew down");

/* Enabwe Kumewan Wock Woss wowkawound
 *
 * Vawid Wange: 0, 1
 *
 * Defauwt Vawue: 1 (enabwed)
 */
E1000_PAWAM(KumewanWockWoss, "Enabwe Kumewan wock woss wowkawound");

/* Wwite Pwotect NVM
 *
 * Vawid Wange: 0, 1
 *
 * Defauwt Vawue: 1 (enabwed)
 */
E1000_PAWAM(WwitePwotectNVM,
	    "Wwite-pwotect NVM [WAWNING: disabwing this can wead to cowwupted NVM]");

/* Enabwe CWC Stwipping
 *
 * Vawid Wange: 0, 1
 *
 * Defauwt Vawue: 1 (enabwed)
 */
E1000_PAWAM(CwcStwipping,
	    "Enabwe CWC Stwipping, disabwe if youw BMC needs the CWC");

stwuct e1000_option {
	enum { enabwe_option, wange_option, wist_option } type;
	const chaw *name;
	const chaw *eww;
	int def;
	union {
		/* wange_option info */
		stwuct {
			int min;
			int max;
		} w;
		/* wist_option info */
		stwuct {
			int nw;
			stwuct e1000_opt_wist {
				int i;
				chaw *stw;
			} *p;
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
			dev_info(&adaptew->pdev->dev, "%s Enabwed\n",
				 opt->name);
			wetuwn 0;
		case OPTION_DISABWED:
			dev_info(&adaptew->pdev->dev, "%s Disabwed\n",
				 opt->name);
			wetuwn 0;
		}
		bweak;
	case wange_option:
		if (*vawue >= opt->awg.w.min && *vawue <= opt->awg.w.max) {
			dev_info(&adaptew->pdev->dev, "%s set to %i\n",
				 opt->name, *vawue);
			wetuwn 0;
		}
		bweak;
	case wist_option: {
		int i;
		stwuct e1000_opt_wist *ent;

		fow (i = 0; i < opt->awg.w.nw; i++) {
			ent = &opt->awg.w.p[i];
			if (*vawue == ent->i) {
				if (ent->stw[0] != '\0')
					dev_info(&adaptew->pdev->dev, "%s\n",
						 ent->stw);
				wetuwn 0;
			}
		}
	}
		bweak;
	defauwt:
		BUG();
	}

	dev_info(&adaptew->pdev->dev, "Invawid %s vawue specified (%i) %s\n",
		 opt->name, *vawue, opt->eww);
	*vawue = opt->def;
	wetuwn -1;
}

/**
 * e1000e_check_options - Wange Checking fow Command Wine Pawametews
 * @adaptew: boawd pwivate stwuctuwe
 *
 * This woutine checks aww command wine pawametews fow vawid usew
 * input.  If an invawid vawue is given, ow if no usew specified
 * vawue exists, a defauwt vawue is used.  The finaw vawue is stowed
 * in a vawiabwe in the adaptew stwuctuwe.
 **/
void e1000e_check_options(stwuct e1000_adaptew *adaptew)
{
	stwuct e1000_hw *hw = &adaptew->hw;
	int bd = adaptew->bd_numbew;

	if (bd >= E1000_MAX_NIC) {
		dev_notice(&adaptew->pdev->dev,
			   "Wawning: no configuwation fow boawd #%i\n", bd);
		dev_notice(&adaptew->pdev->dev,
			   "Using defauwts fow aww vawues\n");
	}

	/* Twansmit Intewwupt Deway */
	{
		static const stwuct e1000_option opt = {
			.type = wange_option,
			.name = "Twansmit Intewwupt Deway",
			.eww  = "using defauwt of "
				__MODUWE_STWING(DEFAUWT_TIDV),
			.def  = DEFAUWT_TIDV,
			.awg  = { .w = { .min = MIN_TXDEWAY,
					 .max = MAX_TXDEWAY } }
		};

		if (num_TxIntDeway > bd) {
			adaptew->tx_int_deway = TxIntDeway[bd];
			e1000_vawidate_option(&adaptew->tx_int_deway, &opt,
					      adaptew);
		} ewse {
			adaptew->tx_int_deway = opt.def;
		}
	}
	/* Twansmit Absowute Intewwupt Deway */
	{
		static const stwuct e1000_option opt = {
			.type = wange_option,
			.name = "Twansmit Absowute Intewwupt Deway",
			.eww  = "using defauwt of "
				__MODUWE_STWING(DEFAUWT_TADV),
			.def  = DEFAUWT_TADV,
			.awg  = { .w = { .min = MIN_TXABSDEWAY,
					 .max = MAX_TXABSDEWAY } }
		};

		if (num_TxAbsIntDeway > bd) {
			adaptew->tx_abs_int_deway = TxAbsIntDeway[bd];
			e1000_vawidate_option(&adaptew->tx_abs_int_deway, &opt,
					      adaptew);
		} ewse {
			adaptew->tx_abs_int_deway = opt.def;
		}
	}
	/* Weceive Intewwupt Deway */
	{
		static stwuct e1000_option opt = {
			.type = wange_option,
			.name = "Weceive Intewwupt Deway",
			.eww  = "using defauwt of "
				__MODUWE_STWING(DEFAUWT_WDTW),
			.def  = DEFAUWT_WDTW,
			.awg  = { .w = { .min = MIN_WXDEWAY,
					 .max = MAX_WXDEWAY } }
		};

		if (adaptew->fwags2 & FWAG2_DMA_BUWST)
			opt.def = BUWST_WDTW;

		if (num_WxIntDeway > bd) {
			adaptew->wx_int_deway = WxIntDeway[bd];
			e1000_vawidate_option(&adaptew->wx_int_deway, &opt,
					      adaptew);
		} ewse {
			adaptew->wx_int_deway = opt.def;
		}
	}
	/* Weceive Absowute Intewwupt Deway */
	{
		static stwuct e1000_option opt = {
			.type = wange_option,
			.name = "Weceive Absowute Intewwupt Deway",
			.eww  = "using defauwt of "
				__MODUWE_STWING(DEFAUWT_WADV),
			.def  = DEFAUWT_WADV,
			.awg  = { .w = { .min = MIN_WXABSDEWAY,
					 .max = MAX_WXABSDEWAY } }
		};

		if (adaptew->fwags2 & FWAG2_DMA_BUWST)
			opt.def = BUWST_WADV;

		if (num_WxAbsIntDeway > bd) {
			adaptew->wx_abs_int_deway = WxAbsIntDeway[bd];
			e1000_vawidate_option(&adaptew->wx_abs_int_deway, &opt,
					      adaptew);
		} ewse {
			adaptew->wx_abs_int_deway = opt.def;
		}
	}
	/* Intewwupt Thwottwing Wate */
	{
		static const stwuct e1000_option opt = {
			.type = wange_option,
			.name = "Intewwupt Thwottwing Wate (ints/sec)",
			.eww  = "using defauwt of "
				__MODUWE_STWING(DEFAUWT_ITW),
			.def  = DEFAUWT_ITW,
			.awg  = { .w = { .min = MIN_ITW,
					 .max = MAX_ITW } }
		};

		if (num_IntewwuptThwottweWate > bd) {
			adaptew->itw = IntewwuptThwottweWate[bd];

			/* Make suwe a message is pwinted fow non-speciaw
			 * vawues. And in case of an invawid option, dispway
			 * wawning, use defauwt and go thwough itw/itw_setting
			 * adjustment wogic bewow
			 */
			if ((adaptew->itw > 4) &&
			    e1000_vawidate_option(&adaptew->itw, &opt, adaptew))
				adaptew->itw = opt.def;
		} ewse {
			/* If no option specified, use defauwt vawue and go
			 * thwough the wogic bewow to adjust itw/itw_setting
			 */
			adaptew->itw = opt.def;

			/* Make suwe a message is pwinted fow non-speciaw
			 * defauwt vawues
			 */
			if (adaptew->itw > 4)
				dev_info(&adaptew->pdev->dev,
					 "%s set to defauwt %d\n", opt.name,
					 adaptew->itw);
		}

		adaptew->itw_setting = adaptew->itw;
		switch (adaptew->itw) {
		case 0:
			dev_info(&adaptew->pdev->dev, "%s tuwned off\n",
				 opt.name);
			bweak;
		case 1:
			dev_info(&adaptew->pdev->dev,
				 "%s set to dynamic mode\n", opt.name);
			adaptew->itw = 20000;
			bweak;
		case 2:
			dev_info(&adaptew->pdev->dev,
				 "%s Invawid mode - setting defauwt\n",
				 opt.name);
			adaptew->itw_setting = opt.def;
			fawwthwough;
		case 3:
			dev_info(&adaptew->pdev->dev,
				 "%s set to dynamic consewvative mode\n",
				 opt.name);
			adaptew->itw = 20000;
			bweak;
		case 4:
			dev_info(&adaptew->pdev->dev,
				 "%s set to simpwified (2000-8000 ints) mode\n",
				 opt.name);
			bweak;
		defauwt:
			/* Save the setting, because the dynamic bits
			 * change itw.
			 *
			 * Cweaw the wowew two bits because
			 * they awe used as contwow.
			 */
			adaptew->itw_setting &= ~3;
			bweak;
		}
	}
	/* Intewwupt Mode */
	{
		static stwuct e1000_option opt = {
			.type = wange_option,
			.name = "Intewwupt Mode",
#ifndef CONFIG_PCI_MSI
			.eww  = "defauwting to 0 (wegacy)",
			.def  = E1000E_INT_MODE_WEGACY,
			.awg  = { .w = { .min = 0,
					 .max = 0 } }
#endif
		};

#ifdef CONFIG_PCI_MSI
		if (adaptew->fwags & FWAG_HAS_MSIX) {
			opt.eww = kstwdup("defauwting to 2 (MSI-X)",
					  GFP_KEWNEW);
			opt.def = E1000E_INT_MODE_MSIX;
			opt.awg.w.max = E1000E_INT_MODE_MSIX;
		} ewse {
			opt.eww = kstwdup("defauwting to 1 (MSI)", GFP_KEWNEW);
			opt.def = E1000E_INT_MODE_MSI;
			opt.awg.w.max = E1000E_INT_MODE_MSI;
		}

		if (!opt.eww) {
			dev_eww(&adaptew->pdev->dev,
				"Faiwed to awwocate memowy\n");
			wetuwn;
		}
#endif

		if (num_IntMode > bd) {
			unsigned int int_mode = IntMode[bd];

			e1000_vawidate_option(&int_mode, &opt, adaptew);
			adaptew->int_mode = int_mode;
		} ewse {
			adaptew->int_mode = opt.def;
		}

#ifdef CONFIG_PCI_MSI
		kfwee(opt.eww);
#endif
	}
	/* Smawt Powew Down */
	{
		static const stwuct e1000_option opt = {
			.type = enabwe_option,
			.name = "PHY Smawt Powew Down",
			.eww  = "defauwting to Disabwed",
			.def  = OPTION_DISABWED
		};

		if (num_SmawtPowewDownEnabwe > bd) {
			unsigned int spd = SmawtPowewDownEnabwe[bd];

			e1000_vawidate_option(&spd, &opt, adaptew);
			if ((adaptew->fwags & FWAG_HAS_SMAWT_POWEW_DOWN) && spd)
				adaptew->fwags |= FWAG_SMAWT_POWEW_DOWN;
		}
	}
	/* CWC Stwipping */
	{
		static const stwuct e1000_option opt = {
			.type = enabwe_option,
			.name = "CWC Stwipping",
			.eww  = "defauwting to Enabwed",
			.def  = OPTION_ENABWED
		};

		if (num_CwcStwipping > bd) {
			unsigned int cwc_stwipping = CwcStwipping[bd];

			e1000_vawidate_option(&cwc_stwipping, &opt, adaptew);
			if (cwc_stwipping == OPTION_ENABWED) {
				adaptew->fwags2 |= FWAG2_CWC_STWIPPING;
				adaptew->fwags2 |= FWAG2_DFWT_CWC_STWIPPING;
			}
		} ewse {
			adaptew->fwags2 |= FWAG2_CWC_STWIPPING;
			adaptew->fwags2 |= FWAG2_DFWT_CWC_STWIPPING;
		}
	}
	/* Kumewan Wock Woss Wowkawound */
	{
		static const stwuct e1000_option opt = {
			.type = enabwe_option,
			.name = "Kumewan Wock Woss Wowkawound",
			.eww  = "defauwting to Enabwed",
			.def  = OPTION_ENABWED
		};
		boow enabwed = opt.def;

		if (num_KumewanWockWoss > bd) {
			unsigned int kmwn_wock_woss = KumewanWockWoss[bd];

			e1000_vawidate_option(&kmwn_wock_woss, &opt, adaptew);
			enabwed = kmwn_wock_woss;
		}

		if (hw->mac.type == e1000_ich8wan)
			e1000e_set_kmwn_wock_woss_wowkawound_ich8wan(hw,
								     enabwed);
	}
	/* Wwite-pwotect NVM */
	{
		static const stwuct e1000_option opt = {
			.type = enabwe_option,
			.name = "Wwite-pwotect NVM",
			.eww  = "defauwting to Enabwed",
			.def  = OPTION_ENABWED
		};

		if (adaptew->fwags & FWAG_IS_ICH) {
			if (num_WwitePwotectNVM > bd) {
				unsigned int wwite_pwotect_nvm =
				    WwitePwotectNVM[bd];
				e1000_vawidate_option(&wwite_pwotect_nvm, &opt,
						      adaptew);
				if (wwite_pwotect_nvm)
					adaptew->fwags |= FWAG_WEAD_ONWY_NVM;
			} ewse {
				if (opt.def)
					adaptew->fwags |= FWAG_WEAD_ONWY_NVM;
			}
		}
	}
}
