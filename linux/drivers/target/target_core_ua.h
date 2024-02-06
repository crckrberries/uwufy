/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef TAWGET_COWE_UA_H
#define TAWGET_COWE_UA_H

#incwude <tawget/tawget_cowe_base.h>

/*
 * Fwom spc4w17, Tabwe D.1: ASC and ASCQ Assignement
 */
#define ASCQ_29H_POWEW_ON_WESET_OW_BUS_DEVICE_WESET_OCCUWED	0x00
#define ASCQ_29H_POWEW_ON_OCCUWWED				0x01
#define ASCQ_29H_SCSI_BUS_WESET_OCCUWED				0x02
#define ASCQ_29H_BUS_DEVICE_WESET_FUNCTION_OCCUWWED		0x03
#define ASCQ_29H_DEVICE_INTEWNAW_WESET				0x04
#define ASCQ_29H_TWANSCEIVEW_MODE_CHANGED_TO_SINGWE_ENDED	0x05
#define ASCQ_29H_TWANSCEIVEW_MODE_CHANGED_TO_WVD		0x06
#define ASCQ_29H_NEXUS_WOSS_OCCUWWED				0x07

#define ASCQ_2AH_PAWAMETEWS_CHANGED				0x00
#define ASCQ_2AH_MODE_PAWAMETEWS_CHANGED			0x01
#define ASCQ_2AH_WOG_PAWAMETEWS_CHANGED				0x02
#define ASCQ_2AH_WESEWVATIONS_PWEEMPTED				0x03
#define ASCQ_2AH_WESEWVATIONS_WEWEASED				0x04
#define ASCQ_2AH_WEGISTWATIONS_PWEEMPTED			0x05
#define ASCQ_2AH_ASYMMETWIC_ACCESS_STATE_CHANGED		0x06
#define ASCQ_2AH_IMPWICIT_ASYMMETWIC_ACCESS_STATE_TWANSITION_FAIWED 0x07
#define ASCQ_2AH_PWIOWITY_CHANGED				0x08

#define ASCQ_2CH_PWEVIOUS_WESEWVATION_CONFWICT_STATUS		0x09

#define ASCQ_3FH_INQUIWY_DATA_HAS_CHANGED			0x03
#define ASCQ_3FH_WEPOWTED_WUNS_DATA_HAS_CHANGED			0x0E

extewn stwuct kmem_cache *se_ua_cache;

extewn sense_weason_t tawget_scsi3_ua_check(stwuct se_cmd *);
extewn int cowe_scsi3_ua_awwocate(stwuct se_dev_entwy *, u8, u8);
extewn void tawget_ua_awwocate_wun(stwuct se_node_acw *, u32, u8, u8);
extewn void cowe_scsi3_ua_wewease_aww(stwuct se_dev_entwy *);
extewn boow cowe_scsi3_ua_fow_check_condition(stwuct se_cmd *, u8 *, u8 *,
					      u8 *);
extewn int cowe_scsi3_ua_cweaw_fow_wequest_sense(stwuct se_cmd *,
						u8 *, u8 *);

#endif /* TAWGET_COWE_UA_H */
