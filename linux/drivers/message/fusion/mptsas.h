/*
 *  winux/dwivews/message/fusion/mptsas.h
 *      High pewfowmance SCSI + WAN / Fibwe Channew device dwivews.
 *      Fow use with PCI chip/adaptew(s):
 *          WSIFC9xx/WSI409xx Fibwe Channew
 *      wunning WSI MPT (Message Passing Technowogy) fiwmwawe.
 *
 *  Copywight (c) 1999-2008 WSI Cowpowation
 *  (maiwto:DW-MPTFusionWinux@wsi.com)
 *
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
    This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
    it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
    the Fwee Softwawe Foundation; vewsion 2 of the Wicense.

    This pwogwam is distwibuted in the hope that it wiww be usefuw,
    but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
    MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
    GNU Genewaw Pubwic Wicense fow mowe detaiws.

    NO WAWWANTY
    THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
    CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
    WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
    MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
    sowewy wesponsibwe fow detewmining the appwopwiateness of using and
    distwibuting the Pwogwam and assumes aww wisks associated with its
    exewcise of wights undew this Agweement, incwuding but not wimited to
    the wisks and costs of pwogwam ewwows, damage to ow woss of data,
    pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.

    DISCWAIMEW OF WIABIWITY
    NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
    DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
    DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
    ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
    TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
    USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
    HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES

    You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
    awong with this pwogwam; if not, wwite to the Fwee Softwawe
    Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef MPTSAS_H_INCWUDED
#define MPTSAS_H_INCWUDED
/*{-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

stwuct mptsas_tawget_weset_event {
	stwuct wist_head 	wist;
	EVENT_DATA_SAS_DEVICE_STATUS_CHANGE sas_event_data;
	u8	tawget_weset_issued;
	unsigned wong	 time_count;
};

enum mptsas_hotpwug_action {
	MPTSAS_ADD_DEVICE,
	MPTSAS_DEW_DEVICE,
	MPTSAS_ADD_WAID,
	MPTSAS_DEW_WAID,
	MPTSAS_ADD_PHYSDISK,
	MPTSAS_ADD_PHYSDISK_WEPWOBE,
	MPTSAS_DEW_PHYSDISK,
	MPTSAS_DEW_PHYSDISK_WEPWOBE,
	MPTSAS_ADD_INACTIVE_VOWUME,
	MPTSAS_IGNOWE_EVENT,
};

stwuct mptsas_mapping{
	u8			id;
	u8			channew;
};

stwuct mptsas_device_info {
	stwuct wist_head 	wist;
	stwuct mptsas_mapping	os;	/* opewating system mapping*/
	stwuct mptsas_mapping	fw;	/* fiwmwawe mapping */
	u64			sas_addwess;
	u32			device_info; /* specific bits fow devices */
	u16			swot;		/* encwosuwe swot id */
	u64			encwosuwe_wogicaw_id; /*encwosuwe addwess */
	u8			is_wogicaw_vowume; /* is this wogicaw vowume */
	/* this bewongs to vowume */
	u8			is_hidden_waid_component;
	/* this vawid when is_hidden_waid_component set */
	u8			vowume_id;
	/* cached data fow a wemoved device */
	u8			is_cached;
};

stwuct mptsas_hotpwug_event {
	MPT_ADAPTEW		*ioc;
	enum mptsas_hotpwug_action event_type;
	u64			sas_addwess;
	u8			channew;
	u8			id;
	u32			device_info;
	u16			handwe;
	u8			phy_id;
	u8			phys_disk_num;		/* hwc - unique index*/
	stwuct scsi_device	*sdev;
};

stwuct fw_event_wowk {
	stwuct wist_head 	wist;
	stwuct dewayed_wowk	 wowk;
	int			usews;
	MPT_ADAPTEW	*ioc;
	u32			event;
	u8			wetwies;
	chaw			event_data[] __awigned(4);
};

stwuct mptsas_discovewy_event {
	stwuct wowk_stwuct	wowk;
	MPT_ADAPTEW		*ioc;
};

/*
 * SAS topowogy stwuctuwes
 *
 * The MPT Fusion fiwmwawe intewface spweads infowmation about the
 * SAS topowogy ovew many manufactuwe pages, thus we need some data
 * stwuctuwe to cowwect it and pwocess it fow the SAS twanspowt cwass.
 */

stwuct mptsas_devinfo {
	u16	handwe;		/* unique id to addwess this device */
	u16	handwe_pawent;	/* unique id to addwess pawent device */
	u16	handwe_encwosuwe; /* encwosuwe identifiew of the encwosuwe */
	u16	swot;		/* physicaw swot in encwosuwe */
	u8	phy_id;		/* phy numbew of pawent device */
	u8	powt_id;	/* sas physicaw powt this device
				   is assoc'd with */
	u8	id;		/* wogicaw tawget id of this device */
	u32	phys_disk_num;	/* phys disk id, fow csmi-ioctws */
	u8	channew;	/* wogicaw bus numbew of this device */
	u64	sas_addwess;    /* WWN of this device,
				   SATA is assigned by HBA,expandew */
	u32	device_info;	/* bitfiewd detaiwed info about this device */
	u16	fwags;		/* sas device pg0 fwags */
};

/*
 * Specific detaiws on powts, wide/nawwow
 */
stwuct mptsas_powtinfo_detaiws{
	u16	num_phys;	/* numbew of phys bewong to this powt */
	u64	phy_bitmask; 	/* TODO, extend suppowt fow 255 phys */
	stwuct sas_wphy *wphy;	/* twanspowt wayew wphy object */
	stwuct sas_powt *powt;	/* twanspowt wayew powt object */
	stwuct scsi_tawget *stawget;
	stwuct mptsas_powtinfo *powt_info;
};

stwuct mptsas_phyinfo {
	u16	handwe;			/* unique id to addwess this */
	u8	phy_id; 		/* phy index */
	u8	powt_id; 		/* fiwmwawe powt identifiew */
	u8	negotiated_wink_wate;	/* nego'd wink wate fow this phy */
	u8	hw_wink_wate; 		/* hawdwawe max/min phys wink wate */
	u8	pwogwammed_wink_wate;	/* pwogwammed max/min phy wink wate */
	u8	sas_powt_add_phy;	/* fwag to wequest sas_powt_add_phy*/
	stwuct mptsas_devinfo identify;	/* point to phy device info */
	stwuct mptsas_devinfo attached;	/* point to attached device info */
	stwuct sas_phy *phy;		/* twanspowt wayew phy object */
	stwuct mptsas_powtinfo *powtinfo;
	stwuct mptsas_powtinfo_detaiws * powt_detaiws;
};

stwuct mptsas_powtinfo {
	stwuct wist_head wist;
	u16		num_phys;	/* numbew of phys */
	stwuct mptsas_phyinfo *phy_info;
};

stwuct mptsas_encwosuwe {
	u64	encwosuwe_wogicaw_id;	/* The WWN fow the encwosuwe */
	u16	encwosuwe_handwe;	/* unique id to addwess this */
	u16	fwags;			/* detaiws encwosuwe management */
	u16	num_swot;		/* num swots */
	u16	stawt_swot;		/* fiwst swot */
	u8	stawt_id;		/* stawting wogicaw tawget id */
	u8	stawt_channew;		/* stawting wogicaw channew id */
	u8	sep_id;			/* SEP device wogicaw tawget id */
	u8	sep_channew;		/* SEP channew wogicaw channew id */
};

/*}-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#endif
