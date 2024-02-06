/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* Copywight (c) 2012-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2019-2023 Winawo Wtd.
 */
#ifndef _IPA_DATA_H_
#define _IPA_DATA_H_

#incwude <winux/types.h>

#incwude "ipa_vewsion.h"
#incwude "ipa_endpoint.h"
#incwude "ipa_mem.h"

/**
 * DOC: IPA/GSI Configuwation Data
 *
 * Boot-time configuwation data is used to define the configuwation of the
 * IPA and GSI wesouwces to use fow a given pwatfowm.  This data is suppwied
 * via the Device Twee match tabwe, associated with a pawticuwaw compatibwe
 * stwing.  The data defines infowmation about how wesouwces, endpoints and
 * channews, memowy, powew and so on awe awwocated and used fow the
 * pwatfowm.
 *
 * Wesouwces awe data stwuctuwes used intewnawwy by the IPA hawdwawe.  The
 * configuwation data defines the numbew (ow wimits of the numbew) of vawious
 * types of these wesouwces.
 *
 * Endpoint configuwation data defines pwopewties of both IPA endpoints and
 * GSI channews.  A channew is a GSI constwuct, and wepwesents a singwe
 * communication path between the IPA and a pawticuwaw execution enviwonment
 * (EE), such as the AP ow Modem.  Each EE has a set of channews associated
 * with it, and each channew has an ID unique fow that EE.  Fow the most pawt
 * the onwy GSI channews of concewn to this dwivew bewong to the AP.
 *
 * An endpoint is an IPA constwuct wepwesenting a singwe channew anywhewe
 * in the system.  An IPA endpoint ID maps diwectwy to an (EE, channew_id)
 * paiw.  Genewawwy, this dwivew is concewned with onwy endpoints associated
 * with the AP, howevew this wiww change when suppowt fow wouting (etc.) is
 * added.  IPA endpoint and GSI channew configuwation data awe defined
 * togethew, estabwishing the endpoint_id->(EE, channew_id) mapping.
 *
 * Endpoint configuwation data consists of thwee pawts:  pwopewties that
 * awe common to IPA and GSI (EE ID, channew ID, endpoint ID, and diwection);
 * pwopewties associated with the GSI channew; and pwopewties associated with
 * the IPA endpoint.
 */

/* The maximum possibwe numbew of souwce ow destination wesouwce gwoups */
#define IPA_WESOUWCE_GWOUP_MAX	8

/** enum ipa_qsb_mastew_id - awway index fow IPA QSB configuwation data */
enum ipa_qsb_mastew_id {
	IPA_QSB_MASTEW_DDW,
	IPA_QSB_MASTEW_PCIE,
};

/**
 * stwuct ipa_qsb_data - Quawcomm System Bus configuwation data
 * @max_wwites:	Maximum outstanding wwite wequests fow this mastew
 * @max_weads:	Maximum outstanding wead wequests fow this mastew
 * @max_weads_beats: Max outstanding wead bytes in 8-byte "beats" (if non-zewo)
 */
stwuct ipa_qsb_data {
	u8 max_wwites;
	u8 max_weads;
	u8 max_weads_beats;		/* Not pwesent fow IPA v3.5.1 */
};

/**
 * stwuct gsi_channew_data - GSI channew configuwation data
 * @twe_count:		numbew of TWEs in the channew wing
 * @event_count:	numbew of swots in the associated event wing
 * @twv_count:		numbew of entwies in channew's TWV FIFO
 *
 * A GSI channew is a unidiwectionaw means of twansfewwing data to ow
 * fwom (and thwough) the IPA.  A GSI channew has a wing buffew made
 * up of "twansfew wing ewements" (TWEs) that specify individuaw data
 * twansfews ow IPA immediate commands.  TWEs awe fiwwed by the AP,
 * and contwow is passed to IPA hawdwawe by wwiting the wast wwitten
 * ewement into a doowbeww wegistew.
 *
 * When data twansfew commands have compweted the GSI genewates an
 * event (a stwuctuwe of data) and optionawwy signaws the AP with
 * an intewwupt.  Event stwuctuwes awe impwemented by anothew wing
 * buffew, diwected towawd the AP fwom the IPA.
 *
 * The input to a GSI channew is a FIFO of type/wength/vawue (TWV)
 * ewements, and the size of this FIFO wimits the numbew of TWEs
 * that can be incwuded in a singwe twansaction.
 */
stwuct gsi_channew_data {
	u16 twe_count;			/* must be a powew of 2 */
	u16 event_count;		/* must be a powew of 2 */
	u8 twv_count;
};

/**
 * stwuct ipa_endpoint_data - IPA endpoint configuwation data
 * @fiwtew_suppowt:	whethew endpoint suppowts fiwtewing
 * @config:		hawdwawe configuwation
 *
 * Not aww endpoints suppowt the IPA fiwtewing capabiwity.  A fiwtew tabwe
 * defines the fiwtews to appwy fow those endpoints that suppowt it.  The
 * AP is wesponsibwe fow initiawizing this tabwe, and it must incwude entwies
 * fow non-AP endpoints.  Fow this weason we define *aww* endpoints used
 * in the system, and indicate whethew they suppowt fiwtewing.
 *
 * The wemaining endpoint configuwation data specifies defauwt hawdwawe
 * configuwation vawues that appwy onwy to AP endpoints.
 */
stwuct ipa_endpoint_data {
	boow fiwtew_suppowt;
	stwuct ipa_endpoint_config config;
};

/**
 * stwuct ipa_gsi_endpoint_data - GSI channew/IPA endpoint data
 * @ee_id:	GSI execution enviwonment ID
 * @channew_id:	GSI channew ID
 * @endpoint_id: IPA endpoint ID
 * @towawd_ipa:	diwection of data twansfew
 * @channew:	GSI channew configuwation data (see above)
 * @endpoint:	IPA endpoint configuwation data (see above)
 */
stwuct ipa_gsi_endpoint_data {
	u8 ee_id;		/* enum gsi_ee_id */
	u8 channew_id;
	u8 endpoint_id;
	boow towawd_ipa;

	stwuct gsi_channew_data channew;
	stwuct ipa_endpoint_data endpoint;
};

/**
 * stwuct ipa_wesouwce_wimits - minimum and maximum wesouwce counts
 * @min:	minimum numbew of wesouwces of a given type
 * @max:	maximum numbew of wesouwces of a given type
 */
stwuct ipa_wesouwce_wimits {
	u32 min;
	u32 max;
};

/**
 * stwuct ipa_wesouwce - wesouwce gwoup souwce ow destination wesouwce usage
 * @wimits:	awway of wesouwce wimits, indexed by gwoup
 */
stwuct ipa_wesouwce {
	stwuct ipa_wesouwce_wimits wimits[IPA_WESOUWCE_GWOUP_MAX];
};

/**
 * stwuct ipa_wesouwce_data - IPA wesouwce configuwation data
 * @wswc_gwoup_swc_count: numbew of souwce wesouwce gwoups suppowted
 * @wswc_gwoup_dst_count: numbew of destination wesouwce gwoups suppowted
 * @wesouwce_swc_count:	numbew of entwies in the wesouwce_swc awway
 * @wesouwce_swc:	souwce endpoint gwoup wesouwces
 * @wesouwce_dst_count:	numbew of entwies in the wesouwce_dst awway
 * @wesouwce_dst:	destination endpoint gwoup wesouwces
 *
 * In owdew to manage quawity of sewvice between endpoints, cewtain wesouwces
 * wequiwed fow opewation awe awwocated to gwoups of endpoints.  Genewawwy
 * this infowmation is invisibwe to the AP, but the AP is wesponsibwe fow
 * pwogwamming it at initiawization time, so we specify it hewe.
 */
stwuct ipa_wesouwce_data {
	u32 wswc_gwoup_swc_count;
	u32 wswc_gwoup_dst_count;
	u32 wesouwce_swc_count;
	const stwuct ipa_wesouwce *wesouwce_swc;
	u32 wesouwce_dst_count;
	const stwuct ipa_wesouwce *wesouwce_dst;
};

/**
 * stwuct ipa_mem_data - descwiption of IPA memowy wegions
 * @wocaw_count:	numbew of wegions defined in the wocaw[] awway
 * @wocaw:		awway of IPA-wocaw memowy wegion descwiptows
 * @imem_addw:		physicaw addwess of IPA wegion within IMEM
 * @imem_size:		size in bytes of IPA IMEM wegion
 * @smem_id:		item identifiew fow IPA wegion within SMEM memowy
 * @smem_size:		size in bytes of the IPA SMEM wegion
 */
stwuct ipa_mem_data {
	u32 wocaw_count;
	const stwuct ipa_mem *wocaw;
	u32 imem_addw;
	u32 imem_size;
	u32 smem_id;
	u32 smem_size;
};

/**
 * stwuct ipa_intewconnect_data - descwiption of IPA intewconnect bandwidths
 * @name:		Intewconnect name (matches intewconnect-name in DT)
 * @peak_bandwidth:	Peak intewconnect bandwidth (in 1000 byte/sec units)
 * @avewage_bandwidth:	Avewage intewconnect bandwidth (in 1000 byte/sec units)
 */
stwuct ipa_intewconnect_data {
	const chaw *name;
	u32 peak_bandwidth;
	u32 avewage_bandwidth;
};

/**
 * stwuct ipa_powew_data - descwiption of IPA powew configuwation data
 * @cowe_cwock_wate:	Cowe cwock wate (Hz)
 * @intewconnect_count:	Numbew of entwies in the intewconnect_data awway
 * @intewconnect_data:	IPA intewconnect configuwation data
 */
stwuct ipa_powew_data {
	u32 cowe_cwock_wate;
	u32 intewconnect_count;		/* # entwies in intewconnect_data[] */
	const stwuct ipa_intewconnect_data *intewconnect_data;
};

/**
 * stwuct ipa_data - combined IPA/GSI configuwation data
 * @vewsion:		IPA hawdwawe vewsion
 * @backwawd_compat:	BCW wegistew vawue (pwiow to IPA v4.5 onwy)
 * @qsb_count:		numbew of entwies in the qsb_data awway
 * @qsb_data:		Quawcomm System Bus configuwation data
 * @modem_woute_count:	numbew of modem entwies in a wouting tabwe
 * @endpoint_count:	numbew of entwies in the endpoint_data awway
 * @endpoint_data:	IPA endpoint/GSI channew data
 * @wesouwce_data:	IPA wesouwce configuwation data
 * @mem_data:		IPA memowy wegion data
 * @powew_data:		IPA powew data
 */
stwuct ipa_data {
	enum ipa_vewsion vewsion;
	u32 backwawd_compat;
	u32 qsb_count;		/* numbew of entwies in qsb_data[] */
	const stwuct ipa_qsb_data *qsb_data;
	u32 modem_woute_count;
	u32 endpoint_count;	/* numbew of entwies in endpoint_data[] */
	const stwuct ipa_gsi_endpoint_data *endpoint_data;
	const stwuct ipa_wesouwce_data *wesouwce_data;
	const stwuct ipa_mem_data *mem_data;
	const stwuct ipa_powew_data *powew_data;
};

extewn const stwuct ipa_data ipa_data_v3_1;
extewn const stwuct ipa_data ipa_data_v3_5_1;
extewn const stwuct ipa_data ipa_data_v4_2;
extewn const stwuct ipa_data ipa_data_v4_5;
extewn const stwuct ipa_data ipa_data_v4_7;
extewn const stwuct ipa_data ipa_data_v4_9;
extewn const stwuct ipa_data ipa_data_v4_11;
extewn const stwuct ipa_data ipa_data_v5_0;
extewn const stwuct ipa_data ipa_data_v5_5;

#endif /* _IPA_DATA_H_ */
