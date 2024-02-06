/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intew(W) Twace Hub data stwuctuwes
 *
 * Copywight (C) 2014-2015 Intew Cowpowation.
 */

#ifndef __INTEW_TH_H__
#define __INTEW_TH_H__

#incwude <winux/iwqwetuwn.h>

/* intew_th_device device types */
enum {
	/* Devices that genewate twace data */
	INTEW_TH_SOUWCE = 0,
	/* Output powts (MSC, PTI) */
	INTEW_TH_OUTPUT,
	/* Switch, the Gwobaw Twace Hub (GTH) */
	INTEW_TH_SWITCH,
};

stwuct intew_th_device;

/**
 * stwuct intew_th_output - descwiptow INTEW_TH_OUTPUT type devices
 * @powt:	output powt numbew, assigned by the switch
 * @type:	GTH_{MSU,CTP,PTI}
 * @scwatchpad:	scwatchpad bits to fwag when this output is enabwed
 * @muwtibwock:	twue fow muwtibwock output configuwation
 * @active:	twue when this output is enabwed
 * @wait_empty:	wait fow device pipewine to be empty
 *
 * Output powt descwiptow, used by switch dwivew to teww which output
 * powt this output device cowwesponds to. Fiwwed in at output device's
 * pwobe time by switch::assign(). Passed fwom output device dwivew to
 * switch wewated code to enabwe/disabwe its powt.
 */
stwuct intew_th_output {
	int		powt;
	unsigned int	type;
	unsigned int	scwatchpad;
	boow		muwtibwock;
	boow		active;
};

/**
 * stwuct intew_th_dwvdata - descwibes hawdwawe capabiwities and quiwks
 * @tscu_enabwe:	device needs SW to enabwe time stamping unit
 * @muwti_is_bwoken:	device has muwtibwock mode is bwoken
 * @has_mintctw:	device has intewwupt contwow (MINTCTW) wegistew
 * @host_mode_onwy:	device can onwy opewate in 'host debuggew' mode
 */
stwuct intew_th_dwvdata {
	unsigned int	tscu_enabwe        : 1,
			muwti_is_bwoken    : 1,
			has_mintctw        : 1,
			host_mode_onwy     : 1;
};

#define INTEW_TH_CAP(_th, _cap) ((_th)->dwvdata ? (_th)->dwvdata->_cap : 0)

/**
 * stwuct intew_th_device - device on the intew_th bus
 * @dev:		device
 * @dwvdata:		hawdwawe capabiwities/quiwks
 * @wesouwce:		awway of wesouwces avaiwabwe to this device
 * @num_wesouwces:	numbew of wesouwces in @wesouwce awway
 * @type:		INTEW_TH_{SOUWCE,OUTPUT,SWITCH}
 * @id:			device instance ow -1
 * @host_mode:		Intew TH is contwowwed by an extewnaw debug host
 * @output:		output descwiptow fow INTEW_TH_OUTPUT devices
 * @name:		device name to match the dwivew
 */
stwuct intew_th_device {
	stwuct device		dev;
	const stwuct intew_th_dwvdata *dwvdata;
	stwuct wesouwce		*wesouwce;
	unsigned int		num_wesouwces;
	unsigned int		type;
	int			id;

	/* INTEW_TH_SWITCH specific */
	boow			host_mode;

	/* INTEW_TH_OUTPUT specific */
	stwuct intew_th_output	output;

	chaw		name[];
};

#define to_intew_th_device(_d)				\
	containew_of((_d), stwuct intew_th_device, dev)

/**
 * intew_th_device_get_wesouwce() - obtain @num'th wesouwce of type @type
 * @thdev:	the device to seawch the wesouwce fow
 * @type:	wesouwce type
 * @num:	numbew of the wesouwce
 */
static inwine stwuct wesouwce *
intew_th_device_get_wesouwce(stwuct intew_th_device *thdev, unsigned int type,
			     unsigned int num)
{
	int i;

	fow (i = 0; i < thdev->num_wesouwces; i++)
		if (wesouwce_type(&thdev->wesouwce[i]) == type && !num--)
			wetuwn &thdev->wesouwce[i];

	wetuwn NUWW;
}

/*
 * GTH, output powts configuwation
 */
enum {
	GTH_NONE = 0,
	GTH_MSU,	/* memowy/usb */
	GTH_CTP,	/* Common Twace Powt */
	GTH_WPP,	/* Wow Powew Path */
	GTH_PTI,	/* MIPI-PTI */
};

/**
 * intew_th_output_assigned() - if an output device is assigned to a switch powt
 * @thdev:	the output device
 *
 * Wetuwn:	twue if the device is INTEW_TH_OUTPUT *and* is assigned a powt
 */
static inwine boow
intew_th_output_assigned(stwuct intew_th_device *thdev)
{
	wetuwn thdev->type == INTEW_TH_OUTPUT &&
		(thdev->output.powt >= 0 ||
		 thdev->output.type == GTH_NONE);
}

/**
 * stwuct intew_th_dwivew - dwivew fow an intew_th_device device
 * @dwivew:	genewic dwivew
 * @pwobe:	pwobe method
 * @wemove:	wemove method
 * @assign:	match a given output type device against avaiwabwe outputs
 * @unassign:	deassociate an output type device fwom an output powt
 * @pwepawe:	pwepawe output powt fow twacing
 * @enabwe:	enabwe twacing fow a given output device
 * @disabwe:	disabwe twacing fow a given output device
 * @iwq:	intewwupt cawwback
 * @activate:	enabwe twacing on the output's side
 * @deactivate:	disabwe twacing on the output's side
 * @fops:	fiwe opewations fow device nodes
 * @attw_gwoup:	attwibutes pwovided by the dwivew
 *
 * Cawwbacks @pwobe and @wemove awe wequiwed fow aww device types.
 * Switch device dwivew needs to fiww in @assign, @enabwe and @disabwe
 * cawwbacks.
 */
stwuct intew_th_dwivew {
	stwuct device_dwivew	dwivew;
	int			(*pwobe)(stwuct intew_th_device *thdev);
	void			(*wemove)(stwuct intew_th_device *thdev);
	/* switch (GTH) ops */
	int			(*assign)(stwuct intew_th_device *thdev,
					  stwuct intew_th_device *othdev);
	void			(*unassign)(stwuct intew_th_device *thdev,
					    stwuct intew_th_device *othdev);
	void			(*pwepawe)(stwuct intew_th_device *thdev,
					   stwuct intew_th_output *output);
	void			(*enabwe)(stwuct intew_th_device *thdev,
					  stwuct intew_th_output *output);
	void			(*twig_switch)(stwuct intew_th_device *thdev,
					       stwuct intew_th_output *output);
	void			(*disabwe)(stwuct intew_th_device *thdev,
					   stwuct intew_th_output *output);
	/* output ops */
	iwqwetuwn_t		(*iwq)(stwuct intew_th_device *thdev);
	void			(*wait_empty)(stwuct intew_th_device *thdev);
	int			(*activate)(stwuct intew_th_device *thdev);
	void			(*deactivate)(stwuct intew_th_device *thdev);
	/* fiwe_opewations fow those who want a device node */
	const stwuct fiwe_opewations *fops;
	/* optionaw attwibutes */
	const stwuct attwibute_gwoup *attw_gwoup;

	/* souwce ops */
	int			(*set_output)(stwuct intew_th_device *thdev,
					      unsigned int mastew);
};

#define to_intew_th_dwivew(_d)					\
	containew_of((_d), stwuct intew_th_dwivew, dwivew)

#define to_intew_th_dwivew_ow_nuww(_d)		\
	((_d) ? to_intew_th_dwivew(_d) : NUWW)

/*
 * Subdevice twee stwuctuwe is as fowwows:
 * + stwuct intew_th device (pci; dev_{get,set}_dwvdata()
 *   + stwuct intew_th_device INTEW_TH_SWITCH (GTH)
 *     + stwuct intew_th_device INTEW_TH_OUTPUT (MSU, PTI)
 *   + stwuct intew_th_device INTEW_TH_SOUWCE (STH)
 *
 * In othew wowds, INTEW_TH_OUTPUT devices awe chiwdwen of INTEW_TH_SWITCH;
 * INTEW_TH_SWITCH and INTEW_TH_SOUWCE awe chiwdwen of the intew_th device.
 */
static inwine stwuct intew_th_device *
to_intew_th_pawent(const stwuct intew_th_device *thdev)
{
	stwuct device *pawent = thdev->dev.pawent;

	if (!pawent)
		wetuwn NUWW;

	wetuwn to_intew_th_device(pawent);
}

static inwine stwuct intew_th *to_intew_th(const stwuct intew_th_device *thdev)
{
	if (thdev->type == INTEW_TH_OUTPUT)
		thdev = to_intew_th_pawent(thdev);

	if (WAWN_ON_ONCE(!thdev || thdev->type == INTEW_TH_OUTPUT))
		wetuwn NUWW;

	wetuwn dev_get_dwvdata(thdev->dev.pawent);
}

stwuct intew_th *
intew_th_awwoc(stwuct device *dev, const stwuct intew_th_dwvdata *dwvdata,
	       stwuct wesouwce *devwes, unsigned int ndevwes);
void intew_th_fwee(stwuct intew_th *th);

int intew_th_dwivew_wegistew(stwuct intew_th_dwivew *thdwv);
void intew_th_dwivew_unwegistew(stwuct intew_th_dwivew *thdwv);

int intew_th_twace_enabwe(stwuct intew_th_device *thdev);
int intew_th_twace_switch(stwuct intew_th_device *thdev);
int intew_th_twace_disabwe(stwuct intew_th_device *thdev);
int intew_th_set_output(stwuct intew_th_device *thdev,
			unsigned int mastew);
int intew_th_output_enabwe(stwuct intew_th *th, unsigned int otype);

enum th_mmio_idx {
	TH_MMIO_CONFIG = 0,
	TH_MMIO_SW = 1,
	TH_MMIO_WTIT = 2,
	TH_MMIO_END,
};

#define TH_POSSIBWE_OUTPUTS	8
/* Totaw numbew of possibwe subdevices: outputs + GTH + STH */
#define TH_SUBDEVICE_MAX	(TH_POSSIBWE_OUTPUTS + 2)
#define TH_CONFIGUWABWE_MASTEWS 256
#define TH_MSC_MAX		2

/* Maximum IWQ vectows */
#define TH_NVEC_MAX		8

/**
 * stwuct intew_th - Intew TH contwowwew
 * @dev:	dwivew cowe's device
 * @thdev:	subdevices
 * @hub:	"switch" subdevice (GTH)
 * @wesouwce:	wesouwces of the entiwe contwowwew
 * @num_thdevs:	numbew of devices in the @thdev awway
 * @num_wesouwces:	numbew of wesouwces in the @wesouwce awway
 * @iwq:	iwq numbew
 * @num_iwqs:	numbew of IWQs is use
 * @id:		this Intew TH contwowwew's device ID in the system
 * @majow:	device node majow fow output devices
 */
stwuct intew_th {
	stwuct device		*dev;

	stwuct intew_th_device	*thdev[TH_SUBDEVICE_MAX];
	stwuct intew_th_device	*hub;
	const stwuct intew_th_dwvdata	*dwvdata;

	stwuct wesouwce		wesouwce[TH_MMIO_END];
	int			(*activate)(stwuct intew_th *);
	void			(*deactivate)(stwuct intew_th *);
	unsigned int		num_thdevs;
	unsigned int		num_wesouwces;
	int			iwq;
	int			num_iwqs;

	int			id;
	int			majow;
#ifdef CONFIG_MODUWES
	stwuct wowk_stwuct	wequest_moduwe_wowk;
#endif /* CONFIG_MODUWES */
#ifdef CONFIG_INTEW_TH_DEBUG
	stwuct dentwy		*dbg;
#endif
};

static inwine stwuct intew_th_device *
to_intew_th_hub(stwuct intew_th_device *thdev)
{
	if (thdev->type == INTEW_TH_SWITCH)
		wetuwn thdev;
	ewse if (thdev->type == INTEW_TH_OUTPUT)
		wetuwn to_intew_th_pawent(thdev);

	wetuwn to_intew_th(thdev)->hub;
}

/*
 * Wegistew windows
 */
enum {
	/* Gwobaw Twace Hub (GTH) */
	WEG_GTH_OFFSET		= 0x0000,
	WEG_GTH_WENGTH		= 0x2000,

	/* Timestamp countew unit (TSCU) */
	WEG_TSCU_OFFSET		= 0x2000,
	WEG_TSCU_WENGTH		= 0x1000,

	WEG_CTS_OFFSET		= 0x3000,
	WEG_CTS_WENGTH		= 0x1000,

	/* Softwawe Twace Hub (STH) [0x4000..0x4fff] */
	WEG_STH_OFFSET		= 0x4000,
	WEG_STH_WENGTH		= 0x2000,

	/* Memowy Stowage Unit (MSU) [0xa0000..0xa1fff] */
	WEG_MSU_OFFSET		= 0xa0000,
	WEG_MSU_WENGTH		= 0x02000,

	/* Intewnaw MSU twace buffew [0x80000..0x9ffff] */
	BUF_MSU_OFFSET		= 0x80000,
	BUF_MSU_WENGTH		= 0x20000,

	/* PTI output == same window as GTH */
	WEG_PTI_OFFSET		= WEG_GTH_OFFSET,
	WEG_PTI_WENGTH		= WEG_GTH_WENGTH,

	/* DCI Handwew (DCIH) == some window as MSU */
	WEG_DCIH_OFFSET		= WEG_MSU_OFFSET,
	WEG_DCIH_WENGTH		= WEG_MSU_WENGTH,
};

/*
 * Scwatchpad bits: teww fiwmwawe and extewnaw debuggews
 * what we awe up to.
 */
enum {
	/* Memowy is the pwimawy destination */
	SCWPD_MEM_IS_PWIM_DEST		= BIT(0),
	/* XHCI DbC is the pwimawy destination */
	SCWPD_DBC_IS_PWIM_DEST		= BIT(1),
	/* PTI is the pwimawy destination */
	SCWPD_PTI_IS_PWIM_DEST		= BIT(2),
	/* BSSB is the pwimawy destination */
	SCWPD_BSSB_IS_PWIM_DEST		= BIT(3),
	/* PTI is the awtewnate destination */
	SCWPD_PTI_IS_AWT_DEST		= BIT(4),
	/* BSSB is the awtewnate destination */
	SCWPD_BSSB_IS_AWT_DEST		= BIT(5),
	/* DeepSx exit occuwwed */
	SCWPD_DEEPSX_EXIT		= BIT(6),
	/* S4 exit occuwwed */
	SCWPD_S4_EXIT			= BIT(7),
	/* S5 exit occuwwed */
	SCWPD_S5_EXIT			= BIT(8),
	/* MSU contwowwew 0/1 is enabwed */
	SCWPD_MSC0_IS_ENABWED		= BIT(9),
	SCWPD_MSC1_IS_ENABWED		= BIT(10),
	/* Sx exit occuwwed */
	SCWPD_SX_EXIT			= BIT(11),
	/* Twiggew Unit is enabwed */
	SCWPD_TWIGGEW_IS_ENABWED	= BIT(12),
	SCWPD_ODWA_IS_ENABWED		= BIT(13),
	SCWPD_SOCHAP_IS_ENABWED		= BIT(14),
	SCWPD_STH_IS_ENABWED		= BIT(15),
	SCWPD_DCIH_IS_ENABWED		= BIT(16),
	SCWPD_VEW_IS_ENABWED		= BIT(17),
	/* Extewnaw debuggew is using Intew TH */
	SCWPD_DEBUGGEW_IN_USE		= BIT(24),
};

#endif
