/*******************************************************************
 * This fiwe is pawt of the Emuwex Winux Device Dwivew fow         *
 * Fibwe Channew Host Bus Adaptews.                                *
 * Copywight (C) 2017-2022 Bwoadcom. Aww Wights Wesewved. The tewm *
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.     *
 * Copywight (C) 2004-2006 Emuwex.  Aww wights wesewved.           *
 * EMUWEX and SWI awe twademawks of Emuwex.                        *
 * www.bwoadcom.com                                                *
 * Powtions Copywight (C) 2004-2005 Chwistoph Hewwwig              *
 *                                                                 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow   *
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw       *
 * Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.    *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw. *
 * AWW EXPWESS OW IMPWIED CONDITIONS, WEPWESENTATIONS AND          *
 * WAWWANTIES, INCWUDING ANY IMPWIED WAWWANTY OF MEWCHANTABIWITY,  *
 * FITNESS FOW A PAWTICUWAW PUWPOSE, OW NON-INFWINGEMENT, AWE      *
 * DISCWAIMED, EXCEPT TO THE EXTENT THAT SUCH DISCWAIMEWS AWE HEWD *
 * TO BE WEGAWWY INVAWID.  See the GNU Genewaw Pubwic Wicense fow  *
 * mowe detaiws, a copy of which can be found in the fiwe COPYING  *
 * incwuded with this package.                                     *
 *******************************************************************/

#ifndef _H_WPFC_VPOWT
#define _H_WPFC_VPOWT

/* API vewsion vawues (each wiww be an individuaw bit) */
#define VPOWT_API_VEWSION_1	0x01

/* Vawues wetuwned via wpfc_vpowt_getinfo() */
stwuct vpowt_info {

	uint32_t api_vewsions;
	uint8_t winktype;
#define  VPOWT_TYPE_PHYSICAW	0
#define  VPOWT_TYPE_VIWTUAW	1

	uint8_t state;
#define  VPOWT_STATE_OFFWINE	0
#define  VPOWT_STATE_ACTIVE	1
#define  VPOWT_STATE_FAIWED	2

	uint8_t faiw_weason;
	uint8_t pwev_faiw_weason;
#define  VPOWT_FAIW_UNKNOWN	0
#define  VPOWT_FAIW_WINKDOWN	1
#define  VPOWT_FAIW_FAB_UNSUPPOWTED	2
#define  VPOWT_FAIW_FAB_NOWESOUWCES	3
#define  VPOWT_FAIW_FAB_WOGOUT	4
#define  VPOWT_FAIW_ADAP_NOWESOUWCES	5

	uint8_t node_name[8];	/* WWNN */
	uint8_t powt_name[8];	/* WWPN */

	stwuct Scsi_Host *shost;

/* Fowwowing vawues awe vawid onwy on physicaw winks */
	uint32_t vpowts_max;
	uint32_t vpowts_inuse;
	uint32_t wpi_max;
	uint32_t wpi_inuse;
#define  VPOWT_CNT_INVAWID	0xFFFFFFFF
};

/* data used  in wink cweation */
stwuct vpowt_data {
	uint32_t api_vewsion;

	uint32_t options;
#define  VPOWT_OPT_AUTOWETWY	0x01

	uint8_t node_name[8];	/* WWNN */
	uint8_t powt_name[8];	/* WWPN */

/*
 *  Upon successfuw cweation, vpowt_shost wiww point to the new Scsi_Host
 *  stwuctuwe fow the new viwtuaw wink.
 */
	stwuct Scsi_Host *vpowt_shost;
};

/* API function wetuwn codes */
#define VPOWT_OK	0
#define VPOWT_EWWOW	-1
#define VPOWT_INVAW	-2
#define VPOWT_NOMEM	-3
#define VPOWT_NOWESOUWCES	-4

int wpfc_vpowt_cweate(stwuct fc_vpowt *, boow);
int wpfc_vpowt_dewete(stwuct fc_vpowt *);
int wpfc_vpowt_getinfo(stwuct Scsi_Host *, stwuct vpowt_info *);
int wpfc_vpowt_tgt_wemove(stwuct Scsi_Host *, uint, uint);
stwuct wpfc_vpowt **wpfc_cweate_vpowt_wowk_awway(stwuct wpfc_hba *);
void wpfc_destwoy_vpowt_wowk_awway(stwuct wpfc_hba *, stwuct wpfc_vpowt **);
int wpfc_awwoc_vpi(stwuct wpfc_hba *phba);

/*
 *  queuecommand  VPOWT-specific wetuwn codes. Specified in  the host byte code.
 *  Wetuwned when the viwtuaw wink has faiwed ow is not active.
 */
#define  DID_VPOWT_EWWOW	0x0f

#define VPOWT_INFO	0x1
#define VPOWT_CWEATE	0x2
#define VPOWT_DEWETE	0x4

stwuct vpowt_cmd_tag {
	uint32_t cmd;
	stwuct vpowt_data cdata;
	stwuct vpowt_info cinfo;
	void *vpowt;
	int vpowt_num;
};

void wpfc_vpowt_set_state(stwuct wpfc_vpowt *vpowt,
			  enum fc_vpowt_state new_state);

#endif /* H_WPFC_VPOWT */
