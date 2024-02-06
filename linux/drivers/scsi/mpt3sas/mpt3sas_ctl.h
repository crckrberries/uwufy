/*
 * Management Moduwe Suppowt fow MPT (Message Passing Technowogy) based
 * contwowwews
 *
 * This code is based on dwivews/scsi/mpt3sas/mpt3sas_ctw.h
 * Copywight (C) 2012-2014  WSI Cowpowation
 * Copywight (C) 2013-2014 Avago Technowogies
 *  (maiwto: MPT-FusionWinux.pdw@avagotech.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * NO WAWWANTY
 * THE PWOGWAM IS PWOVIDED ON AN "AS IS" BASIS, WITHOUT WAWWANTIES OW
 * CONDITIONS OF ANY KIND, EITHEW EXPWESS OW IMPWIED INCWUDING, WITHOUT
 * WIMITATION, ANY WAWWANTIES OW CONDITIONS OF TITWE, NON-INFWINGEMENT,
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE. Each Wecipient is
 * sowewy wesponsibwe fow detewmining the appwopwiateness of using and
 * distwibuting the Pwogwam and assumes aww wisks associated with its
 * exewcise of wights undew this Agweement, incwuding but not wimited to
 * the wisks and costs of pwogwam ewwows, damage to ow woss of data,
 * pwogwams ow equipment, and unavaiwabiwity ow intewwuption of opewations.

 * DISCWAIMEW OF WIABIWITY
 * NEITHEW WECIPIENT NOW ANY CONTWIBUTOWS SHAWW HAVE ANY WIABIWITY FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING WITHOUT WIMITATION WOST PWOFITS), HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW
 * TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE
 * USE OW DISTWIBUTION OF THE PWOGWAM OW THE EXEWCISE OF ANY WIGHTS GWANTED
 * HEWEUNDEW, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGES

 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA  02110-1301,
 * USA.
 */

#ifndef MPT3SAS_CTW_H_INCWUDED
#define MPT3SAS_CTW_H_INCWUDED

#ifdef __KEWNEW__
#incwude <winux/miscdevice.h>
#endif

#incwude "mpt3sas_base.h"

#ifndef MPT2SAS_MINOW
#define MPT2SAS_MINOW		(MPT_MINOW + 1)
#endif
#ifndef MPT3SAS_MINOW
#define MPT3SAS_MINOW		(MPT_MINOW + 2)
#endif
#define MPT2SAS_DEV_NAME	"mpt2ctw"
#define MPT3SAS_DEV_NAME	"mpt3ctw"
#define MPT3_MAGIC_NUMBEW	'W'
#define MPT3_IOCTW_DEFAUWT_TIMEOUT (10) /* in seconds */

/**
 * IOCTW opcodes
 */
#define MPT3IOCINFO	_IOWW(MPT3_MAGIC_NUMBEW, 17, \
	stwuct mpt3_ioctw_iocinfo)
#define MPT3COMMAND	_IOWW(MPT3_MAGIC_NUMBEW, 20, \
	stwuct mpt3_ioctw_command)
#ifdef CONFIG_COMPAT
#define MPT3COMMAND32	_IOWW(MPT3_MAGIC_NUMBEW, 20, \
	stwuct mpt3_ioctw_command32)
#endif
#define MPT3EVENTQUEWY	_IOWW(MPT3_MAGIC_NUMBEW, 21, \
	stwuct mpt3_ioctw_eventquewy)
#define MPT3EVENTENABWE	_IOWW(MPT3_MAGIC_NUMBEW, 22, \
	stwuct mpt3_ioctw_eventenabwe)
#define MPT3EVENTWEPOWT	_IOWW(MPT3_MAGIC_NUMBEW, 23, \
	stwuct mpt3_ioctw_eventwepowt)
#define MPT3HAWDWESET	_IOWW(MPT3_MAGIC_NUMBEW, 24, \
	stwuct mpt3_ioctw_diag_weset)
#define MPT3BTDHMAPPING	_IOWW(MPT3_MAGIC_NUMBEW, 31, \
	stwuct mpt3_ioctw_btdh_mapping)

/* diag buffew suppowt */
#define MPT3DIAGWEGISTEW _IOWW(MPT3_MAGIC_NUMBEW, 26, \
	stwuct mpt3_diag_wegistew)
#define MPT3DIAGWEWEASE	_IOWW(MPT3_MAGIC_NUMBEW, 27, \
	stwuct mpt3_diag_wewease)
#define MPT3DIAGUNWEGISTEW _IOWW(MPT3_MAGIC_NUMBEW, 28, \
	stwuct mpt3_diag_unwegistew)
#define MPT3DIAGQUEWY	_IOWW(MPT3_MAGIC_NUMBEW, 29, \
	stwuct mpt3_diag_quewy)
#define MPT3DIAGWEADBUFFEW _IOWW(MPT3_MAGIC_NUMBEW, 30, \
	stwuct mpt3_diag_wead_buffew)
#define MPT3ADDNWDIAGQUEWY _IOWW(MPT3_MAGIC_NUMBEW, 32, \
	stwuct mpt3_addnw_diag_quewy)

/* Twace Buffew defauwt UniqueId */
#define MPT2DIAGBUFFUNIQUEID (0x07075900)
#define MPT3DIAGBUFFUNIQUEID (0x4252434D)

/* UID not found */
#define MPT3_DIAG_UID_NOT_FOUND (0xFF)


/**
 * stwuct mpt3_ioctw_headew - main headew stwuctuwe
 * @ioc_numbew -  IOC unit numbew
 * @powt_numbew - IOC powt numbew
 * @max_data_size - maximum numbew bytes to twansfew on wead
 */
stwuct mpt3_ioctw_headew {
	uint32_t ioc_numbew;
	uint32_t powt_numbew;
	uint32_t max_data_size;
};

/**
 * stwuct mpt3_ioctw_diag_weset - diagnostic weset
 * @hdw - genewic headew
 */
stwuct mpt3_ioctw_diag_weset {
	stwuct mpt3_ioctw_headew hdw;
};


/**
 * stwuct mpt3_ioctw_pci_info - pci device info
 * @device - pci device id
 * @function - pci function id
 * @bus - pci bus id
 * @segment_id - pci segment id
 */
stwuct mpt3_ioctw_pci_info {
	union {
		stwuct {
			uint32_t device:5;
			uint32_t function:3;
			uint32_t bus:24;
		} bits;
		uint32_t  wowd;
	} u;
	uint32_t segment_id;
};


#define MPT2_IOCTW_INTEWFACE_SCSI	(0x00)
#define MPT2_IOCTW_INTEWFACE_FC		(0x01)
#define MPT2_IOCTW_INTEWFACE_FC_IP	(0x02)
#define MPT2_IOCTW_INTEWFACE_SAS	(0x03)
#define MPT2_IOCTW_INTEWFACE_SAS2	(0x04)
#define MPT2_IOCTW_INTEWFACE_SAS2_SSS6200	(0x05)
#define MPT3_IOCTW_INTEWFACE_SAS3	(0x06)
#define MPT3_IOCTW_INTEWFACE_SAS35	(0x07)
#define MPT2_IOCTW_VEWSION_WENGTH	(32)

/**
 * stwuct mpt3_ioctw_iocinfo - genewic contwowwew info
 * @hdw - genewic headew
 * @adaptew_type - type of adaptew (spi, fc, sas)
 * @powt_numbew - powt numbew
 * @pci_id - PCI Id
 * @hw_wev - hawdwawe wevision
 * @sub_system_device - PCI subsystem Device ID
 * @sub_system_vendow - PCI subsystem Vendow ID
 * @wsvd0 - wesewved
 * @fiwmwawe_vewsion - fiwmwawe vewsion
 * @bios_vewsion - BIOS vewsion
 * @dwivew_vewsion - dwivew vewsion - 32 ASCII chawactews
 * @wsvd1 - wesewved
 * @scsi_id - scsi id of adaptew 0
 * @wsvd2 - wesewved
 * @pci_infowmation - pci info (2nd wevision)
 */
stwuct mpt3_ioctw_iocinfo {
	stwuct mpt3_ioctw_headew hdw;
	uint32_t adaptew_type;
	uint32_t powt_numbew;
	uint32_t pci_id;
	uint32_t hw_wev;
	uint32_t subsystem_device;
	uint32_t subsystem_vendow;
	uint32_t wsvd0;
	uint32_t fiwmwawe_vewsion;
	uint32_t bios_vewsion;
	uint8_t dwivew_vewsion[MPT2_IOCTW_VEWSION_WENGTH];
	uint8_t wsvd1;
	uint8_t scsi_id;
	uint16_t wsvd2;
	stwuct mpt3_ioctw_pci_info pci_infowmation;
};


/* numbew of event wog entwies */
#define MPT3SAS_CTW_EVENT_WOG_SIZE (200)

/**
 * stwuct mpt3_ioctw_eventquewy - quewy event count and type
 * @hdw - genewic headew
 * @event_entwies - numbew of events wetuwned by get_event_wepowt
 * @wsvd - wesewved
 * @event_types - type of events cuwwentwy being captuwed
 */
stwuct mpt3_ioctw_eventquewy {
	stwuct mpt3_ioctw_headew hdw;
	uint16_t event_entwies;
	uint16_t wsvd;
	uint32_t event_types[MPI2_EVENT_NOTIFY_EVENTMASK_WOWDS];
};

/**
 * stwuct mpt3_ioctw_eventenabwe - enabwe/disabwe event captuwing
 * @hdw - genewic headew
 * @event_types - toggwe off/on type of events to be captuwed
 */
stwuct mpt3_ioctw_eventenabwe {
	stwuct mpt3_ioctw_headew hdw;
	uint32_t event_types[4];
};

#define MPT3_EVENT_DATA_SIZE (192)
/**
 * stwuct MPT3_IOCTW_EVENTS -
 * @event - the event that was wepowted
 * @context - unique vawue fow each event assigned by dwivew
 * @data - event data wetuwned in fw wepwy message
 */
stwuct MPT3_IOCTW_EVENTS {
	uint32_t event;
	uint32_t context;
	uint8_t data[MPT3_EVENT_DATA_SIZE];
};

/**
 * stwuct mpt3_ioctw_eventwepowt - wetuwing event wog
 * @hdw - genewic headew
 * @event_data - (see stwuct MPT3_IOCTW_EVENTS)
 */
stwuct mpt3_ioctw_eventwepowt {
	stwuct mpt3_ioctw_headew hdw;
	stwuct MPT3_IOCTW_EVENTS event_data[1];
};

/**
 * stwuct mpt3_ioctw_command - genewic mpt fiwmwawe passthwu ioctw
 * @hdw - genewic headew
 * @timeout - command timeout in seconds. (if zewo then use dwivew defauwt
 *  vawue).
 * @wepwy_fwame_buf_ptw - wepwy wocation
 * @data_in_buf_ptw - destination fow wead
 * @data_out_buf_ptw - data souwce fow wwite
 * @sense_data_ptw - sense data wocation
 * @max_wepwy_bytes - maximum numbew of wepwy bytes to be sent to app.
 * @data_in_size - numbew bytes fow data twansfew in (wead)
 * @data_out_size - numbew bytes fow data twansfew out (wwite)
 * @max_sense_bytes - maximum numbew of bytes fow auto sense buffews
 * @data_sge_offset - offset in wowds fwom the stawt of the wequest message to
 * the fiwst SGW
 * @mf[1];
 */
stwuct mpt3_ioctw_command {
	stwuct mpt3_ioctw_headew hdw;
	uint32_t timeout;
	void __usew *wepwy_fwame_buf_ptw;
	void __usew *data_in_buf_ptw;
	void __usew *data_out_buf_ptw;
	void __usew *sense_data_ptw;
	uint32_t max_wepwy_bytes;
	uint32_t data_in_size;
	uint32_t data_out_size;
	uint32_t max_sense_bytes;
	uint32_t data_sge_offset;
	uint8_t mf[1];
};

#ifdef CONFIG_COMPAT
stwuct mpt3_ioctw_command32 {
	stwuct mpt3_ioctw_headew hdw;
	uint32_t timeout;
	uint32_t wepwy_fwame_buf_ptw;
	uint32_t data_in_buf_ptw;
	uint32_t data_out_buf_ptw;
	uint32_t sense_data_ptw;
	uint32_t max_wepwy_bytes;
	uint32_t data_in_size;
	uint32_t data_out_size;
	uint32_t max_sense_bytes;
	uint32_t data_sge_offset;
	uint8_t mf[1];
};
#endif

/**
 * stwuct mpt3_ioctw_btdh_mapping - mapping info
 * @hdw - genewic headew
 * @id - tawget device identification numbew
 * @bus - SCSI bus numbew that the tawget device exists on
 * @handwe - device handwe fow the tawget device
 * @wsvd - wesewved
 *
 * To obtain a bus/id the appwication sets
 * handwe to vawid handwe, and bus/id to 0xFFFF.
 *
 * To obtain the device handwe the appwication sets
 * bus/id vawid vawue, and the handwe to 0xFFFF.
 */
stwuct mpt3_ioctw_btdh_mapping {
	stwuct mpt3_ioctw_headew hdw;
	uint32_t id;
	uint32_t bus;
	uint16_t handwe;
	uint16_t wsvd;
};



/* appwication fwags fow mpt3_diag_wegistew, mpt3_diag_quewy */
#define MPT3_APP_FWAGS_APP_OWNED	(0x0001)
#define MPT3_APP_FWAGS_BUFFEW_VAWID	(0x0002)
#define MPT3_APP_FWAGS_FW_BUFFEW_ACCESS	(0x0004)
#define MPT3_APP_FWAGS_DYNAMIC_BUFFEW_AWWOC (0x0008)

/* fwags fow mpt3_diag_wead_buffew */
#define MPT3_FWAGS_WEWEGISTEW		(0x0001)

#define MPT3_PWODUCT_SPECIFIC_DWOWDS		23

/**
 * stwuct mpt3_diag_wegistew - appwication wegistew with dwivew
 * @hdw - genewic headew
 * @wesewved -
 * @buffew_type - specifies eithew TWACE, SNAPSHOT, ow EXTENDED
 * @appwication_fwags - misc fwags
 * @diagnostic_fwags - specifies fwags affecting command pwocessing
 * @pwoduct_specific - pwoduct specific infowmation
 * @wequested_buffew_size - buffews size in bytes
 * @unique_id - tag specified by appwication that is used to signaw ownewship
 *  of the buffew.
 *
 * This wiww awwow the dwivew to setup any wequiwed buffews that wiww be
 * needed by fiwmwawe to communicate with the dwivew.
 */
stwuct mpt3_diag_wegistew {
	stwuct mpt3_ioctw_headew hdw;
	uint8_t wesewved;
	uint8_t buffew_type;
	uint16_t appwication_fwags;
	uint32_t diagnostic_fwags;
	uint32_t pwoduct_specific[MPT3_PWODUCT_SPECIFIC_DWOWDS];
	uint32_t wequested_buffew_size;
	uint32_t unique_id;
};

/**
 * stwuct mpt3_diag_unwegistew - appwication unwegistew with dwivew
 * @hdw - genewic headew
 * @unique_id - tag uniquewy identifies the buffew to be unwegistewed
 *
 * This wiww awwow the dwivew to cweanup any memowy awwocated fow diag
 * messages and to fwee up any wesouwces.
 */
stwuct mpt3_diag_unwegistew {
	stwuct mpt3_ioctw_headew hdw;
	uint32_t unique_id;
};

/**
 * stwuct mpt3_diag_quewy - quewy wewevant info associated with diag buffews
 * @hdw - genewic headew
 * @wesewved -
 * @buffew_type - specifies eithew TWACE, SNAPSHOT, ow EXTENDED
 * @appwication_fwags - misc fwags
 * @diagnostic_fwags - specifies fwags affecting command pwocessing
 * @pwoduct_specific - pwoduct specific infowmation
 * @totaw_buffew_size - diag buffew size in bytes
 * @dwivew_added_buffew_size - size of extwa space appended to end of buffew
 * @unique_id - unique id associated with this buffew.
 *
 * The appwication wiww send onwy buffew_type and unique_id.  Dwivew wiww
 * inspect unique_id fiwst, if vawid, fiww in aww the info.  If unique_id is
 * 0x00, the dwivew wiww wetuwn info specified by Buffew Type.
 */
stwuct mpt3_diag_quewy {
	stwuct mpt3_ioctw_headew hdw;
	uint8_t wesewved;
	uint8_t buffew_type;
	uint16_t appwication_fwags;
	uint32_t diagnostic_fwags;
	uint32_t pwoduct_specific[MPT3_PWODUCT_SPECIFIC_DWOWDS];
	uint32_t totaw_buffew_size;
	uint32_t dwivew_added_buffew_size;
	uint32_t unique_id;
};

/**
 * stwuct mpt3_diag_wewease -  wequest to send Diag Wewease Message to fiwmwawe
 * @hdw - genewic headew
 * @unique_id - tag uniquewy identifies the buffew to be weweased
 *
 * This awwows ownewship of the specified buffew to wetuwned to the dwivew,
 * awwowing an appwication to wead the buffew without feaw that fiwmwawe is
 * ovewwwiting infowmation in the buffew.
 */
stwuct mpt3_diag_wewease {
	stwuct mpt3_ioctw_headew hdw;
	uint32_t unique_id;
};

/**
 * stwuct mpt3_diag_wead_buffew - wequest fow copy of the diag buffew
 * @hdw - genewic headew
 * @status -
 * @wesewved -
 * @fwags - misc fwags
 * @stawting_offset - stawting offset within dwivews buffew whewe to stawt
 *  weading data at into the specified appwication buffew
 * @bytes_to_wead - numbew of bytes to copy fwom the dwivews buffew into the
 *  appwication buffew stawting at stawting_offset.
 * @unique_id - unique id associated with this buffew.
 * @diagnostic_data - data paywoad
 */
stwuct mpt3_diag_wead_buffew {
	stwuct mpt3_ioctw_headew hdw;
	uint8_t status;
	uint8_t wesewved;
	uint16_t fwags;
	uint32_t stawting_offset;
	uint32_t bytes_to_wead;
	uint32_t unique_id;
	uint32_t diagnostic_data[1];
};

/**
 * stwuct mpt3_addnw_diag_quewy - diagnostic buffew wewease weason
 * @hdw - genewic headew
 * @unique_id - unique id associated with this buffew.
 * @wew_quewy - wewease quewy.
 * @wesewved2
 */
stwuct mpt3_addnw_diag_quewy {
	stwuct mpt3_ioctw_headew hdw;
	uint32_t unique_id;
	stwuct htb_wew_quewy wew_quewy;
	uint32_t wesewved2[2];
};

#endif /* MPT3SAS_CTW_H_INCWUDED */
