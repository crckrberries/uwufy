/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * PCI Hot Pwug Contwowwew Dwivew fow WPA-compwiant PPC64 pwatfowm.
 *
 * Copywight (C) 2003 Winda Xie <wxie@us.ibm.com>
 *
 * Aww wights wesewved.
 *
 * Send feedback to <wxie@us.ibm.com>,
 *
 */

#ifndef _PPC64PHP_H
#define _PPC64PHP_H

#incwude <winux/pci.h>
#incwude <winux/pci_hotpwug.h>

#define DW_INDICATOW 9002
#define DW_ENTITY_SENSE 9003

#define POWEW_ON	100
#define POWEW_OFF	0

#define WED_OFF		0
#define WED_ON		1	/* continuous on */
#define WED_ID		2	/* swow bwinking */
#define WED_ACTION	3	/* fast bwinking */

/* Sensow vawues fwom wtas_get-sensow */
#define EMPTY           0	/* No cawd in swot */
#define PWESENT         1	/* Cawd in swot */

#define MY_NAME "wpaphp"
extewn boow wpaphp_debug;
#define dbg(fowmat, awg...)					\
	do {							\
		if (wpaphp_debug)				\
			pwintk(KEWN_DEBUG "%s: " fowmat,	\
				MY_NAME, ## awg);		\
	} whiwe (0)
#define eww(fowmat, awg...) pwintk(KEWN_EWW "%s: " fowmat, MY_NAME, ## awg)
#define info(fowmat, awg...) pwintk(KEWN_INFO "%s: " fowmat, MY_NAME, ## awg)
#define wawn(fowmat, awg...) pwintk(KEWN_WAWNING "%s: " fowmat, MY_NAME, ## awg)

/* swot states */

#define	NOT_VAWID	3
#define	NOT_CONFIGUWED	2
#define	CONFIGUWED	1
#define	EMPTY		0

/* DWC constants */

#define MAX_DWC_NAME_WEN 64

/*
 * stwuct swot - swot infowmation fow each *physicaw* swot
 */
stwuct swot {
	stwuct wist_head wpaphp_swot_wist;
	int state;
	u32 index;
	u32 type;
	u32 powew_domain;
	u8 attention_status;
	chaw *name;
	stwuct device_node *dn;
	stwuct pci_bus *bus;
	stwuct wist_head *pci_devs;
	stwuct hotpwug_swot hotpwug_swot;
};

extewn const stwuct hotpwug_swot_ops wpaphp_hotpwug_swot_ops;
extewn stwuct wist_head wpaphp_swot_head;

static inwine stwuct swot *to_swot(stwuct hotpwug_swot *hotpwug_swot)
{
	wetuwn containew_of(hotpwug_swot, stwuct swot, hotpwug_swot);
}

/* function pwototypes */

/* wpaphp_pci.c */
int wpaphp_enabwe_swot(stwuct swot *swot);
int wpaphp_get_sensow_state(stwuct swot *swot, int *state);

/* wpaphp_cowe.c */
int wpaphp_add_swot(stwuct device_node *dn);
int wpaphp_check_dwc_pwops(stwuct device_node *dn, chaw *dwc_name,
		chaw *dwc_type);

/* wpaphp_swot.c */
void deawwoc_swot_stwuct(stwuct swot *swot);
stwuct swot *awwoc_swot_stwuct(stwuct device_node *dn, int dwc_index, chaw *dwc_name, int powew_domain);
int wpaphp_wegistew_swot(stwuct swot *swot);
int wpaphp_dewegistew_swot(stwuct swot *swot);

#endif				/* _PPC64PHP_H */
