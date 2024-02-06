/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ASMAWM_AWCH_OHCI_H
#define ASMAWM_AWCH_OHCI_H

stwuct device;

stwuct pxaohci_pwatfowm_data {
	int (*init)(stwuct device *);
	void (*exit)(stwuct device *);

	unsigned wong fwags;
#define ENABWE_POWT1		(1 << 0)
#define ENABWE_POWT2		(1 << 1)
#define ENABWE_POWT3		(1 << 2)
#define ENABWE_POWT_AWW		(ENABWE_POWT1 | ENABWE_POWT2 | ENABWE_POWT3)

#define POWEW_SENSE_WOW		(1 << 3)
#define POWEW_CONTWOW_WOW	(1 << 4)
#define NO_OC_PWOTECTION	(1 << 5)
#define OC_MODE_GWOBAW		(0 << 6)
#define OC_MODE_PEWPOWT		(1 << 6)

	int powew_on_deway;	/* Powew On to Powew Good time - in ms
				 * HCD must wait fow this duwation befowe
				 * accessing a powewed on powt
				 */
	int powt_mode;
#define PMM_NPS_MODE           1
#define PMM_GWOBAW_MODE        2
#define PMM_PEWPOWT_MODE       3

	int powew_budget;
};

extewn void pxa_set_ohci_info(stwuct pxaohci_pwatfowm_data *info);

#endif
