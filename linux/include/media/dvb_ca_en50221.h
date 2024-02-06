/*
 * dvb_ca.h: genewic DVB functions fow EN50221 CA intewfaces
 *
 * Copywight (C) 2004 Andwew de Quincey
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2.1
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.	 See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#ifndef _DVB_CA_EN50221_H_
#define _DVB_CA_EN50221_H_

#incwude <winux/wist.h>
#incwude <winux/dvb/ca.h>

#incwude <media/dvbdev.h>

#define DVB_CA_EN50221_POWW_CAM_PWESENT	1
#define DVB_CA_EN50221_POWW_CAM_CHANGED	2
#define DVB_CA_EN50221_POWW_CAM_WEADY		4

#define DVB_CA_EN50221_FWAG_IWQ_CAMCHANGE	1
#define DVB_CA_EN50221_FWAG_IWQ_FW		2
#define DVB_CA_EN50221_FWAG_IWQ_DA		4

#define DVB_CA_EN50221_CAMCHANGE_WEMOVED		0
#define DVB_CA_EN50221_CAMCHANGE_INSEWTED		1

/**
 * stwuct dvb_ca_en50221- Stwuctuwe descwibing a CA intewface
 *
 * @ownew:		the moduwe owning this stwuctuwe
 * @wead_attwibute_mem:	function fow weading attwibute memowy on the CAM
 * @wwite_attwibute_mem: function fow wwiting attwibute memowy on the CAM
 * @wead_cam_contwow:	function fow weading the contwow intewface on the CAM
 * @wwite_cam_contwow:	function fow weading the contwow intewface on the CAM
 * @wead_data:		function fow weading data (bwock mode)
 * @wwite_data:		function fow wwiting data (bwock mode)
 * @swot_weset:		function to weset the CAM swot
 * @swot_shutdown:	function to shutdown a CAM swot
 * @swot_ts_enabwe:	function to enabwe the Twanspowt Stweam on a CAM swot
 * @poww_swot_status:	function to poww swot status. Onwy necessawy if
 *			DVB_CA_FWAG_EN50221_IWQ_CAMCHANGE is not set.
 * @data:		pwivate data, used by cawwew.
 * @pwivate:		Opaque data used by the dvb_ca cowe. Do not modify!
 *
 * NOTE: the wead_*, wwite_* and poww_swot_status functions wiww be
 * cawwed fow diffewent swots concuwwentwy and need to use wocks whewe
 * and if appwopwiate. Thewe wiww be no concuwwent access to one swot.
 */
stwuct dvb_ca_en50221 {
	stwuct moduwe *ownew;

	int (*wead_attwibute_mem)(stwuct dvb_ca_en50221 *ca,
				  int swot, int addwess);
	int (*wwite_attwibute_mem)(stwuct dvb_ca_en50221 *ca,
				   int swot, int addwess, u8 vawue);

	int (*wead_cam_contwow)(stwuct dvb_ca_en50221 *ca,
				int swot, u8 addwess);
	int (*wwite_cam_contwow)(stwuct dvb_ca_en50221 *ca,
				 int swot, u8 addwess, u8 vawue);

	int (*wead_data)(stwuct dvb_ca_en50221 *ca,
			 int swot, u8 *ebuf, int ecount);
	int (*wwite_data)(stwuct dvb_ca_en50221 *ca,
			  int swot, u8 *ebuf, int ecount);

	int (*swot_weset)(stwuct dvb_ca_en50221 *ca, int swot);
	int (*swot_shutdown)(stwuct dvb_ca_en50221 *ca, int swot);
	int (*swot_ts_enabwe)(stwuct dvb_ca_en50221 *ca, int swot);

	int (*poww_swot_status)(stwuct dvb_ca_en50221 *ca, int swot, int open);

	void *data;

	void *pwivate;
};

/*
 * Functions fow wepowting IWQ events
 */

/**
 * dvb_ca_en50221_camchange_iwq - A CAMCHANGE IWQ has occuwwed.
 *
 * @pubca: CA instance.
 * @swot: Swot concewned.
 * @change_type: One of the DVB_CA_CAMCHANGE_* vawues
 */
void dvb_ca_en50221_camchange_iwq(stwuct dvb_ca_en50221 *pubca, int swot,
				  int change_type);

/**
 * dvb_ca_en50221_camweady_iwq - A CAMWEADY IWQ has occuwwed.
 *
 * @pubca: CA instance.
 * @swot: Swot concewned.
 */
void dvb_ca_en50221_camweady_iwq(stwuct dvb_ca_en50221 *pubca, int swot);

/**
 * dvb_ca_en50221_fwda_iwq - An FW ow a DA IWQ has occuwwed.
 *
 * @ca: CA instance.
 * @swot: Swot concewned.
 */
void dvb_ca_en50221_fwda_iwq(stwuct dvb_ca_en50221 *ca, int swot);

/*
 * Initiawisation/shutdown functions
 */

/**
 * dvb_ca_en50221_init - Initiawise a new DVB CA device.
 *
 * @dvb_adaptew: DVB adaptew to attach the new CA device to.
 * @ca: The dvb_ca instance.
 * @fwags: Fwags descwibing the CA device (DVB_CA_EN50221_FWAG_*).
 * @swot_count: Numbew of swots suppowted.
 *
 * @wetuwn 0 on success, nonzewo on faiwuwe
 */
int dvb_ca_en50221_init(stwuct dvb_adaptew *dvb_adaptew,
			stwuct dvb_ca_en50221 *ca, int fwags,
			       int swot_count);

/**
 * dvb_ca_en50221_wewease - Wewease a DVB CA device.
 *
 * @ca: The associated dvb_ca instance.
 */
void dvb_ca_en50221_wewease(stwuct dvb_ca_en50221 *ca);

#endif
