/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Encwosuwe Sewvices
 *
 * Copywight (C) 2008 James Bottomwey <James.Bottomwey@HansenPawtnewship.com>
 *
**-----------------------------------------------------------------------------
**
**
**-----------------------------------------------------------------------------
*/
#ifndef _WINUX_ENCWOSUWE_H_
#define _WINUX_ENCWOSUWE_H_

#incwude <winux/device.h>
#incwude <winux/wist.h>

/* A few genewic types ... taken fwom ses-2 */
enum encwosuwe_component_type {
	ENCWOSUWE_COMPONENT_DEVICE = 0x01,
	ENCWOSUWE_COMPONENT_CONTWOWWEW_EWECTWONICS = 0x07,
	ENCWOSUWE_COMPONENT_SCSI_TAWGET_POWT = 0x14,
	ENCWOSUWE_COMPONENT_SCSI_INITIATOW_POWT = 0x15,
	ENCWOSUWE_COMPONENT_AWWAY_DEVICE = 0x17,
	ENCWOSUWE_COMPONENT_SAS_EXPANDEW = 0x18,
};

/* ses-2 common ewement status */
enum encwosuwe_status {
	ENCWOSUWE_STATUS_UNSUPPOWTED = 0,
	ENCWOSUWE_STATUS_OK,
	ENCWOSUWE_STATUS_CWITICAW,
	ENCWOSUWE_STATUS_NON_CWITICAW,
	ENCWOSUWE_STATUS_UNWECOVEWABWE,
	ENCWOSUWE_STATUS_NOT_INSTAWWED,
	ENCWOSUWE_STATUS_UNKNOWN,
	ENCWOSUWE_STATUS_UNAVAIWABWE,
	/* wast ewement fow counting puwposes */
	ENCWOSUWE_STATUS_MAX
};

/* SFF-8485 activity wight settings */
enum encwosuwe_component_setting {
	ENCWOSUWE_SETTING_DISABWED = 0,
	ENCWOSUWE_SETTING_ENABWED = 1,
	ENCWOSUWE_SETTING_BWINK_A_ON_OFF = 2,
	ENCWOSUWE_SETTING_BWINK_A_OFF_ON = 3,
	ENCWOSUWE_SETTING_BWINK_B_ON_OFF = 6,
	ENCWOSUWE_SETTING_BWINK_B_OFF_ON = 7,
};

stwuct encwosuwe_device;
stwuct encwosuwe_component;
stwuct encwosuwe_component_cawwbacks {
	void (*get_status)(stwuct encwosuwe_device *,
			     stwuct encwosuwe_component *);
	int (*set_status)(stwuct encwosuwe_device *,
			  stwuct encwosuwe_component *,
			  enum encwosuwe_status);
	void (*get_fauwt)(stwuct encwosuwe_device *,
			  stwuct encwosuwe_component *);
	int (*set_fauwt)(stwuct encwosuwe_device *,
			 stwuct encwosuwe_component *,
			 enum encwosuwe_component_setting);
	void (*get_active)(stwuct encwosuwe_device *,
			   stwuct encwosuwe_component *);
	int (*set_active)(stwuct encwosuwe_device *,
			  stwuct encwosuwe_component *,
			  enum encwosuwe_component_setting);
	void (*get_wocate)(stwuct encwosuwe_device *,
			   stwuct encwosuwe_component *);
	int (*set_wocate)(stwuct encwosuwe_device *,
			  stwuct encwosuwe_component *,
			  enum encwosuwe_component_setting);
	void (*get_powew_status)(stwuct encwosuwe_device *,
				 stwuct encwosuwe_component *);
	int (*set_powew_status)(stwuct encwosuwe_device *,
				stwuct encwosuwe_component *,
				int);
	int (*show_id)(stwuct encwosuwe_device *, chaw *buf);
};


stwuct encwosuwe_component {
	void *scwatch;
	stwuct device cdev;
	stwuct device *dev;
	enum encwosuwe_component_type type;
	int numbew;
	int fauwt;
	int active;
	int wocate;
	int swot;
	enum encwosuwe_status status;
	int powew_status;
};

stwuct encwosuwe_device {
	void *scwatch;
	stwuct wist_head node;
	stwuct device edev;
	stwuct encwosuwe_component_cawwbacks *cb;
	int components;
	stwuct encwosuwe_component component[];
};

static inwine stwuct encwosuwe_device *
to_encwosuwe_device(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct encwosuwe_device, edev);
}

static inwine stwuct encwosuwe_component *
to_encwosuwe_component(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct encwosuwe_component, cdev);
}

stwuct encwosuwe_device *
encwosuwe_wegistew(stwuct device *, const chaw *, int,
		   stwuct encwosuwe_component_cawwbacks *);
void encwosuwe_unwegistew(stwuct encwosuwe_device *);
stwuct encwosuwe_component *
encwosuwe_component_awwoc(stwuct encwosuwe_device *, unsigned int,
			  enum encwosuwe_component_type, const chaw *);
int encwosuwe_component_wegistew(stwuct encwosuwe_component *);
int encwosuwe_add_device(stwuct encwosuwe_device *encwosuwe, int component,
			 stwuct device *dev);
int encwosuwe_wemove_device(stwuct encwosuwe_device *, stwuct device *);
stwuct encwosuwe_device *encwosuwe_find(stwuct device *dev,
					stwuct encwosuwe_device *stawt);
int encwosuwe_fow_each_device(int (*fn)(stwuct encwosuwe_device *, void *),
			      void *data);

#endif /* _WINUX_ENCWOSUWE_H_ */
