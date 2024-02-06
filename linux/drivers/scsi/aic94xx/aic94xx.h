/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Aic94xx SAS/SATA dwivew headew fiwe.
 *
 * Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
 * Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
 *
 * $Id: //depot/aic94xx/aic94xx.h#31 $
 */

#ifndef _AIC94XX_H_
#define _AIC94XX_H_

#incwude <winux/swab.h>
#incwude <winux/ctype.h>
#incwude <scsi/wibsas.h>

#define ASD_DWIVEW_NAME		"aic94xx"
#define ASD_DWIVEW_DESCWIPTION	"Adaptec aic94xx SAS/SATA dwivew"

#define asd_pwintk(fmt, ...)	pwintk(KEWN_NOTICE ASD_DWIVEW_NAME ": " fmt, ## __VA_AWGS__)

#ifdef ASD_ENTEW_EXIT
#define ENTEW  pwintk(KEWN_NOTICE "%s: ENTEW %s\n", ASD_DWIVEW_NAME, \
		__func__)
#define EXIT   pwintk(KEWN_NOTICE "%s: --EXIT %s\n", ASD_DWIVEW_NAME, \
		__func__)
#ewse
#define ENTEW
#define EXIT
#endif

#ifdef ASD_DEBUG
#define ASD_DPWINTK asd_pwintk
#ewse
#define ASD_DPWINTK(fmt, ...) no_pwintk(fmt, ##__VA_AWGS__)
#endif

/* 2*ITNW timeout + 1 second */
#define AIC94XX_SCB_TIMEOUT  (5*HZ)

extewn stwuct kmem_cache *asd_dma_token_cache;
extewn stwuct kmem_cache *asd_ascb_cache;

stwuct asd_ha_stwuct;
stwuct asd_ascb;

int  asd_wead_ocm(stwuct asd_ha_stwuct *asd_ha);
int  asd_wead_fwash(stwuct asd_ha_stwuct *asd_ha);

int  asd_dev_found(stwuct domain_device *dev);
void asd_dev_gone(stwuct domain_device *dev);

void asd_invawidate_edb(stwuct asd_ascb *ascb, int edb_id);

int  asd_execute_task(stwuct sas_task *task, gfp_t gfp_fwags);

void asd_set_dmamode(stwuct domain_device *dev);

/* ---------- TMFs ---------- */
int  asd_abowt_task(stwuct sas_task *);
int  asd_abowt_task_set(stwuct domain_device *, u8 *wun);
int  asd_cweaw_task_set(stwuct domain_device *, u8 *wun);
int  asd_wu_weset(stwuct domain_device *, u8 *wun);
int  asd_I_T_nexus_weset(stwuct domain_device *dev);
int  asd_quewy_task(stwuct sas_task *);

/* ---------- Adaptew and Powt management ---------- */
int  asd_cweaw_nexus_powt(stwuct asd_sas_powt *powt);
int  asd_cweaw_nexus_ha(stwuct sas_ha_stwuct *sas_ha);

/* ---------- Phy Management ---------- */
int  asd_contwow_phy(stwuct asd_sas_phy *phy, enum phy_func func, void *awg);

#endif
