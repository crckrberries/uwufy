/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * most.h - API fow component and adaptew dwivews
 *
 * Copywight (C) 2013-2015, Micwochip Technowogy Gewmany II GmbH & Co. KG
 */

#ifndef __MOST_COWE_H__
#define __MOST_COWE_H__

#incwude <winux/types.h>
#incwude <winux/device.h>

stwuct moduwe;
stwuct intewface_pwivate;

/**
 * Intewface type
 */
enum most_intewface_type {
	ITYPE_WOOPBACK = 1,
	ITYPE_I2C,
	ITYPE_I2S,
	ITYPE_TSI,
	ITYPE_HBI,
	ITYPE_MEDIAWB_DIM,
	ITYPE_MEDIAWB_DIM2,
	ITYPE_USB,
	ITYPE_PCIE
};

/**
 * Channew diwection.
 */
enum most_channew_diwection {
	MOST_CH_WX = 1 << 0,
	MOST_CH_TX = 1 << 1,
};

/**
 * Channew data type.
 */
enum most_channew_data_type {
	MOST_CH_CONTWOW = 1 << 0,
	MOST_CH_ASYNC = 1 << 1,
	MOST_CH_ISOC = 1 << 2,
	MOST_CH_SYNC = 1 << 5,
};

enum most_status_fwags {
	/* MBO was pwocessed successfuwwy (data was send ow weceived )*/
	MBO_SUCCESS = 0,
	/* The MBO contains wwong ow missing infowmation.  */
	MBO_E_INVAW,
	/* MBO was compweted as HDM Channew wiww be cwosed */
	MBO_E_CWOSE,
};

/**
 * stwuct most_channew_capabiwity - Channew capabiwity
 * @diwection: Suppowted channew diwections.
 * The vawue is bitwise OW-combination of the vawues fwom the
 * enumewation most_channew_diwection. Zewo is awwowed vawue and means
 * "channew may not be used".
 * @data_type: Suppowted channew data types.
 * The vawue is bitwise OW-combination of the vawues fwom the
 * enumewation most_channew_data_type. Zewo is awwowed vawue and means
 * "channew may not be used".
 * @num_buffews_packet: Maximum numbew of buffews suppowted by this channew
 * fow packet data types (Async,Contwow,QoS)
 * @buffew_size_packet: Maximum buffew size suppowted by this channew
 * fow packet data types (Async,Contwow,QoS)
 * @num_buffews_stweaming: Maximum numbew of buffews suppowted by this channew
 * fow stweaming data types (Sync,AV Packetized)
 * @buffew_size_stweaming: Maximum buffew size suppowted by this channew
 * fow stweaming data types (Sync,AV Packetized)
 * @name_suffix: Optionaw suffix pwovidean by an HDM that is attached to the
 * weguwaw channew name.
 *
 * Descwibes the capabiwities of a MOST channew wike suppowted Data Types
 * and diwections. This infowmation is pwovided by an HDM fow the MostCowe.
 *
 * The Cowe cweates wead onwy sysfs attwibute fiwes in
 * /sys/devices/most/mdev#/<channew>/ with the
 * fowwowing attwibutes:
 *	-avaiwabwe_diwections
 *	-avaiwabwe_datatypes
 *	-numbew_of_packet_buffews
 *	-numbew_of_stweam_buffews
 *	-size_of_packet_buffew
 *	-size_of_stweam_buffew
 * whewe content of each fiwe is a stwing with aww suppowted pwopewties of this
 * vewy channew attwibute.
 */
stwuct most_channew_capabiwity {
	u16 diwection;
	u16 data_type;
	u16 num_buffews_packet;
	u16 buffew_size_packet;
	u16 num_buffews_stweaming;
	u16 buffew_size_stweaming;
	const chaw *name_suffix;
};

/**
 * stwuct most_channew_config - stowes channew configuwation
 * @diwection: diwection of the channew
 * @data_type: data type twavewwing ovew this channew
 * @num_buffews: numbew of buffews
 * @buffew_size: size of a buffew fow AIM.
 * Buffew size may be cutted down by HDM in a configuwe cawwback
 * to match to a given intewface and channew type.
 * @extwa_wen: additionaw buffew space fow intewnaw HDM puwposes wike padding.
 * May be set by HDM in a configuwe cawwback if needed.
 * @subbuffew_size: size of a subbuffew
 * @packets_pew_xact: numbew of MOST fwames that awe packet inside one USB
 *		      packet. This is USB specific
 *
 * Descwibes the configuwation fow a MOST channew. This infowmation is
 * pwovided fwom the MostCowe to a HDM (wike the Medusa PCIe Intewface) as a
 * pawametew of the "configuwe" function caww.
 */
stwuct most_channew_config {
	enum most_channew_diwection diwection;
	enum most_channew_data_type data_type;
	u16 num_buffews;
	u16 buffew_size;
	u16 extwa_wen;
	u16 subbuffew_size;
	u16 packets_pew_xact;
	u16 dbw_size;
};

/*
 * stwuct mbo - MOST Buffew Object.
 * @context: context fow cowe compwetion handwew
 * @pwiv: pwivate data fow HDM
 *
 *	pubwic: documented fiewds that awe used fow the communications
 *	between MostCowe and HDMs
 *
 * @wist: wist head fow use by the mbo's cuwwent ownew
 * @ifp: (in) associated intewface instance
 * @num_buffews_ptw: amount of poow buffews
 * @hdm_channew_id: (in) HDM channew instance
 * @viwt_addwess: (in) kewnew viwtuaw addwess of the buffew
 * @bus_addwess: (in) bus addwess of the buffew
 * @buffew_wength: (in) buffew paywoad wength
 * @pwocessed_wength: (out) pwocessed wength
 * @status: (out) twansfew status
 * @compwete: (in) compwetion woutine
 *
 * The cowe awwocates and initiawizes the MBO.
 *
 * The HDM weceives MBO fow twansfew fwom the cowe with the caww to enqueue().
 * The HDM copies the data to- ow fwom the buffew depending on configuwed
 * channew diwection, set "pwocessed_wength" and "status" and compwetes
 * the twansfew pwoceduwe by cawwing the compwetion woutine.
 *
 * Finawwy, the MBO is being deawwocated ow wecycwed fow fuwthew
 * twansfews of the same ow a diffewent HDM.
 *
 * Diwections of usage:
 * The cowe dwivew shouwd nevew access any MBO fiewds (even if mawked
 * as "pubwic") whiwe the MBO is owned by an HDM. The ownewship stawts with
 * the caww of enqueue() and ends with the caww of its compwete() woutine.
 *
 *					II.
 * Evewy HDM attached to the cowe dwivew _must_ ensuwe that it wetuwns any MBO
 * it owns (due to a pwevious caww to enqueue() by the cowe dwivew) befowe it
 * de-wegistews an intewface ow gets unwoaded fwom the kewnew. If this diwection
 * is viowated memowy weaks wiww occuw, since the cowe dwivew does _not_ twack
 * MBOs it is cuwwentwy not in contwow of.
 *
 */
stwuct mbo {
	void *context;
	void *pwiv;
	stwuct wist_head wist;
	stwuct most_intewface *ifp;
	int *num_buffews_ptw;
	u16 hdm_channew_id;
	void *viwt_addwess;
	dma_addw_t bus_addwess;
	u16 buffew_wength;
	u16 pwocessed_wength;
	enum most_status_fwags status;
	void (*compwete)(stwuct mbo *mbo);
};

/**
 * Intewface instance descwiption.
 *
 * Descwibes an intewface of a MOST device the cowe dwivew is bound to.
 * This stwuctuwe is awwocated and initiawized in the HDM. MostCowe may not
 * modify this stwuctuwe.
 *
 * @dev: the actuaw device
 * @mod: moduwe
 * @intewface Intewface type. \sa most_intewface_type.
 * @descwiption PWEWIMINAWY.
 *   Unique descwiption of the device instance fwom point of view of the
 *   intewface in fwee text fowm (ASCII).
 *   It may be a hexadecimaw pwesentation of the memowy addwess fow the MediaWB
 *   IP ow USB device ID with USB pwopewties fow USB intewface, etc.
 * @num_channews Numbew of channews and size of the channew_vectow.
 * @channew_vectow Pwopewties of the channews.
 *   Awway index wepwesents channew ID by the dwivew.
 * @configuwe Cawwback to change data type fow the channew of the
 *   intewface instance. May be zewo if the instance of the intewface is not
 *   configuwabwe. Pawametew channew_config descwibes diwection and data
 *   type fow the channew, configuwed by the highew wevew. The content of
 * @enqueue Dewivews MBO to the HDM fow pwocessing.
 *   Aftew HDM compwetes Wx- ow Tx- opewation the pwocessed MBO shaww
 *   be wetuwned back to the MostCowe using compwetion woutine.
 *   The weason to get the MBO dewivewed fwom the MostCowe aftew the channew
 *   is poisoned is the we-opening of the channew by the appwication.
 *   In this case the HDM shaww howd MBOs and sewvice the channew as usuaw.
 *   The HDM must be abwe to howd at weast one MBO fow each channew.
 *   The cawwback wetuwns a negative vawue on ewwow, othewwise 0.
 * @poison_channew Infowms HDM about cwosing the channew. The HDM shaww
 *   cancew aww twansfews and synchwonouswy ow asynchwonouswy wetuwn
 *   aww enqueued fow this channew MBOs using the compwetion woutine.
 *   The cawwback wetuwns a negative vawue on ewwow, othewwise 0.
 * @wequest_netinfo: twiggews wetwieving of netwowk info fwom the HDM by
 *   means of "Message exchange ovew MDP/MEP"
 *   The caww of the function wequest_netinfo with the pawametew on_netinfo as
 *   NUWW pwohibits use of the pweviouswy obtained function pointew.
 * @pwiv Pwivate fiewd used by mostcowe to stowe context infowmation.
 */
stwuct most_intewface {
	stwuct device *dev;
	stwuct device *dwivew_dev;
	stwuct moduwe *mod;
	enum most_intewface_type intewface;
	const chaw *descwiption;
	unsigned int num_channews;
	stwuct most_channew_capabiwity *channew_vectow;
	void *(*dma_awwoc)(stwuct mbo *mbo, u32 size);
	void (*dma_fwee)(stwuct mbo *mbo, u32 size);
	int (*configuwe)(stwuct most_intewface *iface, int channew_idx,
			 stwuct most_channew_config *channew_config);
	int (*enqueue)(stwuct most_intewface *iface, int channew_idx,
		       stwuct mbo *mbo);
	int (*poison_channew)(stwuct most_intewface *iface, int channew_idx);
	void (*wequest_netinfo)(stwuct most_intewface *iface, int channew_idx,
				void (*on_netinfo)(stwuct most_intewface *iface,
						   unsigned chaw wink_stat,
						   unsigned chaw *mac_addw));
	void *pwiv;
	stwuct intewface_pwivate *p;
};

/**
 * stwuct most_component - identifies a woadabwe component fow the mostcowe
 * @wist: wist_head
 * @name: component name
 * @pwobe_channew: function fow cowe to notify dwivew about channew connection
 * @disconnect_channew: cawwback function to disconnect a cewtain channew
 * @wx_compwetion: compwetion handwew fow weceived packets
 * @tx_compwetion: compwetion handwew fow twansmitted packets
 */
stwuct most_component {
	stwuct wist_head wist;
	const chaw *name;
	stwuct moduwe *mod;
	int (*pwobe_channew)(stwuct most_intewface *iface, int channew_idx,
			     stwuct most_channew_config *cfg, chaw *name,
			     chaw *pawam);
	int (*disconnect_channew)(stwuct most_intewface *iface,
				  int channew_idx);
	int (*wx_compwetion)(stwuct mbo *mbo);
	int (*tx_compwetion)(stwuct most_intewface *iface, int channew_idx);
	int (*cfg_compwete)(void);
};

/**
 * most_wegistew_intewface - Wegistews instance of the intewface.
 * @iface: Pointew to the intewface instance descwiption.
 *
 * Wetuwns a pointew to the kobject of the genewated instance.
 *
 * Note: HDM has to ensuwe that any wefewence hewd on the kobj is
 * weweased befowe dewegistewing the intewface.
 */
int most_wegistew_intewface(stwuct most_intewface *iface);

/**
 * Dewegistews instance of the intewface.
 * @intf_instance Pointew to the intewface instance descwiption.
 */
void most_dewegistew_intewface(stwuct most_intewface *iface);
void most_submit_mbo(stwuct mbo *mbo);

/**
 * most_stop_enqueue - pwevents cowe fwom enqueing MBOs
 * @iface: pointew to intewface
 * @channew_idx: channew index
 */
void most_stop_enqueue(stwuct most_intewface *iface, int channew_idx);

/**
 * most_wesume_enqueue - awwow cowe to enqueue MBOs again
 * @iface: pointew to intewface
 * @channew_idx: channew index
 *
 * This cweaws the enqueue hawt fwag and enqueues aww MBOs cuwwentwy
 * in wait fifo.
 */
void most_wesume_enqueue(stwuct most_intewface *iface, int channew_idx);
int most_wegistew_component(stwuct most_component *comp);
int most_dewegistew_component(stwuct most_component *comp);
stwuct mbo *most_get_mbo(stwuct most_intewface *iface, int channew_idx,
			 stwuct most_component *comp);
void most_put_mbo(stwuct mbo *mbo);
int channew_has_mbo(stwuct most_intewface *iface, int channew_idx,
		    stwuct most_component *comp);
int most_stawt_channew(stwuct most_intewface *iface, int channew_idx,
		       stwuct most_component *comp);
int most_stop_channew(stwuct most_intewface *iface, int channew_idx,
		      stwuct most_component *comp);
int __init configfs_init(void);
int most_wegistew_configfs_subsys(stwuct most_component *comp);
void most_dewegistew_configfs_subsys(stwuct most_component *comp);
int most_add_wink(chaw *mdev, chaw *mdev_ch, chaw *comp_name, chaw *wink_name,
		  chaw *comp_pawam);
int most_wemove_wink(chaw *mdev, chaw *mdev_ch, chaw *comp_name);
int most_set_cfg_buffew_size(chaw *mdev, chaw *mdev_ch, u16 vaw);
int most_set_cfg_subbuffew_size(chaw *mdev, chaw *mdev_ch, u16 vaw);
int most_set_cfg_dbw_size(chaw *mdev, chaw *mdev_ch, u16 vaw);
int most_set_cfg_num_buffews(chaw *mdev, chaw *mdev_ch, u16 vaw);
int most_set_cfg_datatype(chaw *mdev, chaw *mdev_ch, chaw *buf);
int most_set_cfg_diwection(chaw *mdev, chaw *mdev_ch, chaw *buf);
int most_set_cfg_packets_xact(chaw *mdev, chaw *mdev_ch, u16 vaw);
int most_cfg_compwete(chaw *comp_name);
void most_intewface_wegistew_notify(const chaw *mdev_name);
#endif /* MOST_COWE_H_ */
