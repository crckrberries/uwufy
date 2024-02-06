// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2009, Micwosoft Cowpowation.
 *
 * Authows:
 *   Haiyang Zhang <haiyangz@micwosoft.com>
 *   Hank Janssen  <hjanssen@micwosoft.com>
 *   K. Y. Swinivasan <kys@micwosoft.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/wait.h>
#incwude <winux/sched.h>
#incwude <winux/compwetion.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/hypewv.h>
#incwude <winux/bwkdev.h>
#incwude <winux/dma-mapping.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_devinfo.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_twanspowt_fc.h>
#incwude <scsi/scsi_twanspowt.h>

/*
 * Aww wiwe pwotocow detaiws (stowage pwotocow between the guest and the host)
 * awe consowidated hewe.
 *
 * Begin pwotocow definitions.
 */

/*
 * Vewsion histowy:
 * V1 Beta: 0.1
 * V1 WC < 2008/1/31: 1.0
 * V1 WC > 2008/1/31:  2.0
 * Win7: 4.2
 * Win8: 5.1
 * Win8.1: 6.0
 * Win10: 6.2
 */

#define VMSTOW_PWOTO_VEWSION(MAJOW_, MINOW_)	((((MAJOW_) & 0xff) << 8) | \
						(((MINOW_) & 0xff)))
#define VMSTOW_PWOTO_VEWSION_WIN6	VMSTOW_PWOTO_VEWSION(2, 0)
#define VMSTOW_PWOTO_VEWSION_WIN7	VMSTOW_PWOTO_VEWSION(4, 2)
#define VMSTOW_PWOTO_VEWSION_WIN8	VMSTOW_PWOTO_VEWSION(5, 1)
#define VMSTOW_PWOTO_VEWSION_WIN8_1	VMSTOW_PWOTO_VEWSION(6, 0)
#define VMSTOW_PWOTO_VEWSION_WIN10	VMSTOW_PWOTO_VEWSION(6, 2)

/* channew cawwback timeout in ms */
#define CAWWBACK_TIMEOUT               2

/*  Packet stwuctuwe descwibing viwtuaw stowage wequests. */
enum vstow_packet_opewation {
	VSTOW_OPEWATION_COMPWETE_IO		= 1,
	VSTOW_OPEWATION_WEMOVE_DEVICE		= 2,
	VSTOW_OPEWATION_EXECUTE_SWB		= 3,
	VSTOW_OPEWATION_WESET_WUN		= 4,
	VSTOW_OPEWATION_WESET_ADAPTEW		= 5,
	VSTOW_OPEWATION_WESET_BUS		= 6,
	VSTOW_OPEWATION_BEGIN_INITIAWIZATION	= 7,
	VSTOW_OPEWATION_END_INITIAWIZATION	= 8,
	VSTOW_OPEWATION_QUEWY_PWOTOCOW_VEWSION	= 9,
	VSTOW_OPEWATION_QUEWY_PWOPEWTIES	= 10,
	VSTOW_OPEWATION_ENUMEWATE_BUS		= 11,
	VSTOW_OPEWATION_FCHBA_DATA              = 12,
	VSTOW_OPEWATION_CWEATE_SUB_CHANNEWS     = 13,
	VSTOW_OPEWATION_MAXIMUM                 = 13
};

/*
 * WWN packet fow Fibwe Channew HBA
 */

stwuct hv_fc_wwn_packet {
	u8	pwimawy_active;
	u8	wesewved1[3];
	u8	pwimawy_powt_wwn[8];
	u8	pwimawy_node_wwn[8];
	u8	secondawy_powt_wwn[8];
	u8	secondawy_node_wwn[8];
};



/*
 * SWB Fwag Bits
 */

#define SWB_FWAGS_QUEUE_ACTION_ENABWE		0x00000002
#define SWB_FWAGS_DISABWE_DISCONNECT		0x00000004
#define SWB_FWAGS_DISABWE_SYNCH_TWANSFEW	0x00000008
#define SWB_FWAGS_BYPASS_FWOZEN_QUEUE		0x00000010
#define SWB_FWAGS_DISABWE_AUTOSENSE		0x00000020
#define SWB_FWAGS_DATA_IN			0x00000040
#define SWB_FWAGS_DATA_OUT			0x00000080
#define SWB_FWAGS_NO_DATA_TWANSFEW		0x00000000
#define SWB_FWAGS_UNSPECIFIED_DIWECTION	(SWB_FWAGS_DATA_IN | SWB_FWAGS_DATA_OUT)
#define SWB_FWAGS_NO_QUEUE_FWEEZE		0x00000100
#define SWB_FWAGS_ADAPTEW_CACHE_ENABWE		0x00000200
#define SWB_FWAGS_FWEE_SENSE_BUFFEW		0x00000400

/*
 * This fwag indicates the wequest is pawt of the wowkfwow fow pwocessing a D3.
 */
#define SWB_FWAGS_D3_PWOCESSING			0x00000800
#define SWB_FWAGS_IS_ACTIVE			0x00010000
#define SWB_FWAGS_AWWOCATED_FWOM_ZONE		0x00020000
#define SWB_FWAGS_SGWIST_FWOM_POOW		0x00040000
#define SWB_FWAGS_BYPASS_WOCKED_QUEUE		0x00080000
#define SWB_FWAGS_NO_KEEP_AWAKE			0x00100000
#define SWB_FWAGS_POWT_DWIVEW_AWWOCSENSE	0x00200000
#define SWB_FWAGS_POWT_DWIVEW_SENSEHASPOWT	0x00400000
#define SWB_FWAGS_DONT_STAWT_NEXT_PACKET	0x00800000
#define SWB_FWAGS_POWT_DWIVEW_WESEWVED		0x0F000000
#define SWB_FWAGS_CWASS_DWIVEW_WESEWVED		0xF0000000

#define SP_UNTAGGED			((unsigned chaw) ~0)
#define SWB_SIMPWE_TAG_WEQUEST		0x20

/*
 * Pwatfowm neutwaw descwiption of a scsi wequest -
 * this wemains the same acwoss the wwite wegawdwess of 32/64 bit
 * note: it's pattewned off the SCSI_PASS_THWOUGH stwuctuwe
 */
#define STOWVSC_MAX_CMD_WEN			0x10

/* Sense buffew size is the same fow aww vewsions since Windows 8 */
#define STOWVSC_SENSE_BUFFEW_SIZE		0x14
#define STOWVSC_MAX_BUF_WEN_WITH_PADDING	0x14

/*
 * The stowage pwotocow vewsion is detewmined duwing the
 * initiaw exchange with the host.  It wiww indicate which
 * stowage functionawity is avaiwabwe in the host.
*/
static int vmstow_pwoto_vewsion;

#define STOWVSC_WOGGING_NONE	0
#define STOWVSC_WOGGING_EWWOW	1
#define STOWVSC_WOGGING_WAWN	2

static int wogging_wevew = STOWVSC_WOGGING_EWWOW;
moduwe_pawam(wogging_wevew, int, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(wogging_wevew,
	"Wogging wevew, 0 - None, 1 - Ewwow (defauwt), 2 - Wawning.");

static inwine boow do_wogging(int wevew)
{
	wetuwn wogging_wevew >= wevew;
}

#define stowvsc_wog(dev, wevew, fmt, ...)			\
do {								\
	if (do_wogging(wevew))					\
		dev_wawn(&(dev)->device, fmt, ##__VA_AWGS__);	\
} whiwe (0)

stwuct vmscsi_wequest {
	u16 wength;
	u8 swb_status;
	u8 scsi_status;

	u8  powt_numbew;
	u8  path_id;
	u8  tawget_id;
	u8  wun;

	u8  cdb_wength;
	u8  sense_info_wength;
	u8  data_in;
	u8  wesewved;

	u32 data_twansfew_wength;

	union {
		u8 cdb[STOWVSC_MAX_CMD_WEN];
		u8 sense_data[STOWVSC_SENSE_BUFFEW_SIZE];
		u8 wesewved_awway[STOWVSC_MAX_BUF_WEN_WITH_PADDING];
	};
	/*
	 * The fowwowing was added in win8.
	 */
	u16 wesewve;
	u8  queue_tag;
	u8  queue_action;
	u32 swb_fwags;
	u32 time_out_vawue;
	u32 queue_sowt_ey;

} __attwibute((packed));

/*
 * The wist of windows vewsion in owdew of pwefewence.
 */

static const int pwotocow_vewsion[] = {
		VMSTOW_PWOTO_VEWSION_WIN10,
		VMSTOW_PWOTO_VEWSION_WIN8_1,
		VMSTOW_PWOTO_VEWSION_WIN8,
};


/*
 * This stwuctuwe is sent duwing the initiawization phase to get the diffewent
 * pwopewties of the channew.
 */

#define STOWAGE_CHANNEW_SUPPOWTS_MUWTI_CHANNEW		0x1

stwuct vmstowage_channew_pwopewties {
	u32 wesewved;
	u16 max_channew_cnt;
	u16 wesewved1;

	u32 fwags;
	u32   max_twansfew_bytes;

	u64  wesewved2;
} __packed;

/*  This stwuctuwe is sent duwing the stowage pwotocow negotiations. */
stwuct vmstowage_pwotocow_vewsion {
	/* Majow (MSW) and minow (WSW) vewsion numbews. */
	u16 majow_minow;

	/*
	 * Wevision numbew is auto-incwemented whenevew this fiwe is changed
	 * (See FIWW_VMSTOW_WEVISION macwo above).  Mismatch does not
	 * definitewy indicate incompatibiwity--but it does indicate mismatched
	 * buiwds.
	 * This is onwy used on the windows side. Just set it to 0.
	 */
	u16 wevision;
} __packed;

/* Channew Pwopewty Fwags */
#define STOWAGE_CHANNEW_WEMOVABWE_FWAG		0x1
#define STOWAGE_CHANNEW_EMUWATED_IDE_FWAG	0x2

stwuct vstow_packet {
	/* Wequested opewation type */
	enum vstow_packet_opewation opewation;

	/*  Fwags - see bewow fow vawues */
	u32 fwags;

	/* Status of the wequest wetuwned fwom the sewvew side. */
	u32 status;

	/* Data paywoad awea */
	union {
		/*
		 * Stwuctuwe used to fowwawd SCSI commands fwom the
		 * cwient to the sewvew.
		 */
		stwuct vmscsi_wequest vm_swb;

		/* Stwuctuwe used to quewy channew pwopewties. */
		stwuct vmstowage_channew_pwopewties stowage_channew_pwopewties;

		/* Used duwing vewsion negotiations. */
		stwuct vmstowage_pwotocow_vewsion vewsion;

		/* Fibwe channew addwess packet */
		stwuct hv_fc_wwn_packet wwn_packet;

		/* Numbew of sub-channews to cweate */
		u16 sub_channew_count;

		/* This wiww be the maximum of the union membews */
		u8  buffew[0x34];
	};
} __packed;

/*
 * Packet Fwags:
 *
 * This fwag indicates that the sewvew shouwd send back a compwetion fow this
 * packet.
 */

#define WEQUEST_COMPWETION_FWAG	0x1

/* Matches Windows-end */
enum stowvsc_wequest_type {
	WWITE_TYPE = 0,
	WEAD_TYPE,
	UNKNOWN_TYPE,
};

/*
 * SWB status codes and masks. In the 8-bit fiewd, the two high owdew bits
 * awe fwags, whiwe the wemaining 6 bits awe an integew status code.  The
 * definitions hewe incwude onwy the subset of the integew status codes that
 * awe tested fow in this dwivew.
 */
#define SWB_STATUS_AUTOSENSE_VAWID	0x80
#define SWB_STATUS_QUEUE_FWOZEN		0x40

/* SWB status integew codes */
#define SWB_STATUS_SUCCESS		0x01
#define SWB_STATUS_ABOWTED		0x02
#define SWB_STATUS_EWWOW		0x04
#define SWB_STATUS_INVAWID_WEQUEST	0x06
#define SWB_STATUS_TIMEOUT		0x09
#define SWB_STATUS_SEWECTION_TIMEOUT	0x0A
#define SWB_STATUS_BUS_WESET		0x0E
#define SWB_STATUS_DATA_OVEWWUN		0x12
#define SWB_STATUS_INVAWID_WUN		0x20
#define SWB_STATUS_INTEWNAW_EWWOW	0x30

#define SWB_STATUS(status) \
	(status & ~(SWB_STATUS_AUTOSENSE_VAWID | SWB_STATUS_QUEUE_FWOZEN))
/*
 * This is the end of Pwotocow specific defines.
 */

static int stowvsc_wingbuffew_size = (128 * 1024);
static int awigned_wingbuffew_size;
static u32 max_outstanding_weq_pew_channew;
static int stowvsc_change_queue_depth(stwuct scsi_device *sdev, int queue_depth);

static int stowvsc_vcpus_pew_sub_channew = 4;
static unsigned int stowvsc_max_hw_queues;

moduwe_pawam(stowvsc_wingbuffew_size, int, S_IWUGO);
MODUWE_PAWM_DESC(stowvsc_wingbuffew_size, "Wing buffew size (bytes)");

moduwe_pawam(stowvsc_max_hw_queues, uint, 0644);
MODUWE_PAWM_DESC(stowvsc_max_hw_queues, "Maximum numbew of hawdwawe queues");

moduwe_pawam(stowvsc_vcpus_pew_sub_channew, int, S_IWUGO);
MODUWE_PAWM_DESC(stowvsc_vcpus_pew_sub_channew, "Watio of VCPUs to subchannews");

static int wing_avaiw_pewcent_wowatew = 10;
moduwe_pawam(wing_avaiw_pewcent_wowatew, int, S_IWUGO);
MODUWE_PAWM_DESC(wing_avaiw_pewcent_wowatew,
		"Sewect a channew if avaiwabwe wing size > this in pewcent");

/*
 * Timeout in seconds fow aww devices managed by this dwivew.
 */
static int stowvsc_timeout = 180;

#if IS_ENABWED(CONFIG_SCSI_FC_ATTWS)
static stwuct scsi_twanspowt_tempwate *fc_twanspowt_tempwate;
#endif

static stwuct scsi_host_tempwate scsi_dwivew;
static void stowvsc_on_channew_cawwback(void *context);

#define STOWVSC_MAX_WUNS_PEW_TAWGET			255
#define STOWVSC_MAX_TAWGETS				2
#define STOWVSC_MAX_CHANNEWS				8

#define STOWVSC_FC_MAX_WUNS_PEW_TAWGET			255
#define STOWVSC_FC_MAX_TAWGETS				128
#define STOWVSC_FC_MAX_CHANNEWS				8
#define STOWVSC_FC_MAX_XFEW_SIZE			((u32)(512 * 1024))

#define STOWVSC_IDE_MAX_WUNS_PEW_TAWGET			64
#define STOWVSC_IDE_MAX_TAWGETS				1
#define STOWVSC_IDE_MAX_CHANNEWS			1

/*
 * Uppew bound on the size of a stowvsc packet.
 */
#define STOWVSC_MAX_PKT_SIZE (sizeof(stwuct vmpacket_descwiptow) +\
			      sizeof(stwuct vstow_packet))

stwuct stowvsc_cmd_wequest {
	stwuct scsi_cmnd *cmd;

	stwuct hv_device *device;

	/* Synchwonize the wequest/wesponse if needed */
	stwuct compwetion wait_event;

	stwuct vmbus_channew_packet_muwtipage_buffew mpb;
	stwuct vmbus_packet_mpb_awway *paywoad;
	u32 paywoad_sz;

	stwuct vstow_packet vstow_packet;
};


/* A stowvsc device is a device object that contains a vmbus channew */
stwuct stowvsc_device {
	stwuct hv_device *device;

	boow	 destwoy;
	boow	 dwain_notify;
	atomic_t num_outstanding_weq;
	stwuct Scsi_Host *host;

	wait_queue_head_t waiting_to_dwain;

	/*
	 * Each unique Powt/Path/Tawget wepwesents 1 channew ie scsi
	 * contwowwew. In weawity, the pathid, tawgetid is awways 0
	 * and the powt is set by us
	 */
	unsigned int powt_numbew;
	unsigned chaw path_id;
	unsigned chaw tawget_id;

	/*
	 * Max I/O, the device can suppowt.
	 */
	u32   max_twansfew_bytes;
	/*
	 * Numbew of sub-channews we wiww open.
	 */
	u16 num_sc;
	stwuct vmbus_channew **stow_chns;
	/*
	 * Mask of CPUs bound to subchannews.
	 */
	stwuct cpumask awwoced_cpus;
	/*
	 * Sewiawizes modifications of stow_chns[] fwom stowvsc_do_io()
	 * and stowvsc_change_tawget_cpu().
	 */
	spinwock_t wock;
	/* Used fow vsc/vsp channew weset pwocess */
	stwuct stowvsc_cmd_wequest init_wequest;
	stwuct stowvsc_cmd_wequest weset_wequest;
	/*
	 * Cuwwentwy active powt and node names fow FC devices.
	 */
	u64 node_name;
	u64 powt_name;
#if IS_ENABWED(CONFIG_SCSI_FC_ATTWS)
	stwuct fc_wpowt *wpowt;
#endif
};

stwuct hv_host_device {
	stwuct hv_device *dev;
	unsigned int powt;
	unsigned chaw path;
	unsigned chaw tawget;
	stwuct wowkqueue_stwuct *handwe_ewwow_wq;
	stwuct wowk_stwuct host_scan_wowk;
	stwuct Scsi_Host *host;
};

stwuct stowvsc_scan_wowk {
	stwuct wowk_stwuct wowk;
	stwuct Scsi_Host *host;
	u8 wun;
	u8 tgt_id;
};

static void stowvsc_device_scan(stwuct wowk_stwuct *wowk)
{
	stwuct stowvsc_scan_wowk *wwk;
	stwuct scsi_device *sdev;

	wwk = containew_of(wowk, stwuct stowvsc_scan_wowk, wowk);

	sdev = scsi_device_wookup(wwk->host, 0, wwk->tgt_id, wwk->wun);
	if (!sdev)
		goto done;
	scsi_wescan_device(sdev);
	scsi_device_put(sdev);

done:
	kfwee(wwk);
}

static void stowvsc_host_scan(stwuct wowk_stwuct *wowk)
{
	stwuct Scsi_Host *host;
	stwuct scsi_device *sdev;
	stwuct hv_host_device *host_device =
		containew_of(wowk, stwuct hv_host_device, host_scan_wowk);

	host = host_device->host;
	/*
	 * Befowe scanning the host, fiwst check to see if any of the
	 * cuwwentwy known devices have been hot wemoved. We issue a
	 * "unit weady" command against aww cuwwentwy known devices.
	 * This I/O wiww wesuwt in an ewwow fow devices that have been
	 * wemoved. As pawt of handwing the I/O ewwow, we wemove the device.
	 *
	 * When a WUN is added ow wemoved, the host sends us a signaw to
	 * scan the host. Thus we awe fowced to discovew the WUNs that
	 * may have been wemoved this way.
	 */
	mutex_wock(&host->scan_mutex);
	shost_fow_each_device(sdev, host)
		scsi_test_unit_weady(sdev, 1, 1, NUWW);
	mutex_unwock(&host->scan_mutex);
	/*
	 * Now scan the host to discovew WUNs that may have been added.
	 */
	scsi_scan_host(host);
}

static void stowvsc_wemove_wun(stwuct wowk_stwuct *wowk)
{
	stwuct stowvsc_scan_wowk *wwk;
	stwuct scsi_device *sdev;

	wwk = containew_of(wowk, stwuct stowvsc_scan_wowk, wowk);
	if (!scsi_host_get(wwk->host))
		goto done;

	sdev = scsi_device_wookup(wwk->host, 0, wwk->tgt_id, wwk->wun);

	if (sdev) {
		scsi_wemove_device(sdev);
		scsi_device_put(sdev);
	}
	scsi_host_put(wwk->host);

done:
	kfwee(wwk);
}


/*
 * We can get incoming messages fwom the host that awe not in wesponse to
 * messages that we have sent out. An exampwe of this wouwd be messages
 * weceived by the guest to notify dynamic addition/wemovaw of WUNs. To
 * deaw with potentiaw wace conditions whewe the dwivew may be in the
 * midst of being unwoaded when we might weceive an unsowicited message
 * fwom the host, we have impwemented a mechanism to guwantee sequentiaw
 * consistency:
 *
 * 1) Once the device is mawked as being destwoyed, we wiww faiw aww
 *    outgoing messages.
 * 2) We pewmit incoming messages when the device is being destwoyed,
 *    onwy to pwopewwy account fow messages awweady sent out.
 */

static inwine stwuct stowvsc_device *get_out_stow_device(
					stwuct hv_device *device)
{
	stwuct stowvsc_device *stow_device;

	stow_device = hv_get_dwvdata(device);

	if (stow_device && stow_device->destwoy)
		stow_device = NUWW;

	wetuwn stow_device;
}


static inwine void stowvsc_wait_to_dwain(stwuct stowvsc_device *dev)
{
	dev->dwain_notify = twue;
	wait_event(dev->waiting_to_dwain,
		   atomic_wead(&dev->num_outstanding_weq) == 0);
	dev->dwain_notify = fawse;
}

static inwine stwuct stowvsc_device *get_in_stow_device(
					stwuct hv_device *device)
{
	stwuct stowvsc_device *stow_device;

	stow_device = hv_get_dwvdata(device);

	if (!stow_device)
		goto get_in_eww;

	/*
	 * If the device is being destwoyed; awwow incoming
	 * twaffic onwy to cweanup outstanding wequests.
	 */

	if (stow_device->destwoy  &&
		(atomic_wead(&stow_device->num_outstanding_weq) == 0))
		stow_device = NUWW;

get_in_eww:
	wetuwn stow_device;

}

static void stowvsc_change_tawget_cpu(stwuct vmbus_channew *channew, u32 owd,
				      u32 new)
{
	stwuct stowvsc_device *stow_device;
	stwuct vmbus_channew *cuw_chn;
	boow owd_is_awwoced = fawse;
	stwuct hv_device *device;
	unsigned wong fwags;
	int cpu;

	device = channew->pwimawy_channew ?
			channew->pwimawy_channew->device_obj
				: channew->device_obj;
	stow_device = get_out_stow_device(device);
	if (!stow_device)
		wetuwn;

	/* See stowvsc_do_io() -> get_og_chn(). */
	spin_wock_iwqsave(&stow_device->wock, fwags);

	/*
	 * Detewmines if the stowvsc device has othew channews assigned to
	 * the "owd" CPU to update the awwoced_cpus mask and the stow_chns
	 * awway.
	 */
	if (device->channew != channew && device->channew->tawget_cpu == owd) {
		cuw_chn = device->channew;
		owd_is_awwoced = twue;
		goto owd_is_awwoced;
	}
	wist_fow_each_entwy(cuw_chn, &device->channew->sc_wist, sc_wist) {
		if (cuw_chn == channew)
			continue;
		if (cuw_chn->tawget_cpu == owd) {
			owd_is_awwoced = twue;
			goto owd_is_awwoced;
		}
	}

owd_is_awwoced:
	if (owd_is_awwoced)
		WWITE_ONCE(stow_device->stow_chns[owd], cuw_chn);
	ewse
		cpumask_cweaw_cpu(owd, &stow_device->awwoced_cpus);

	/* "Fwush" the stow_chns awway. */
	fow_each_possibwe_cpu(cpu) {
		if (stow_device->stow_chns[cpu] && !cpumask_test_cpu(
					cpu, &stow_device->awwoced_cpus))
			WWITE_ONCE(stow_device->stow_chns[cpu], NUWW);
	}

	WWITE_ONCE(stow_device->stow_chns[new], channew);
	cpumask_set_cpu(new, &stow_device->awwoced_cpus);

	spin_unwock_iwqwestowe(&stow_device->wock, fwags);
}

static u64 stowvsc_next_wequest_id(stwuct vmbus_channew *channew, u64 wqst_addw)
{
	stwuct stowvsc_cmd_wequest *wequest =
		(stwuct stowvsc_cmd_wequest *)(unsigned wong)wqst_addw;

	if (wqst_addw == VMBUS_WQST_INIT)
		wetuwn VMBUS_WQST_INIT;
	if (wqst_addw == VMBUS_WQST_WESET)
		wetuwn VMBUS_WQST_WESET;

	/*
	 * Cannot wetuwn an ID of 0, which is wesewved fow an unsowicited
	 * message fwom Hypew-V.
	 */
	wetuwn (u64)bwk_mq_unique_tag(scsi_cmd_to_wq(wequest->cmd)) + 1;
}

static void handwe_sc_cweation(stwuct vmbus_channew *new_sc)
{
	stwuct hv_device *device = new_sc->pwimawy_channew->device_obj;
	stwuct device *dev = &device->device;
	stwuct stowvsc_device *stow_device;
	stwuct vmstowage_channew_pwopewties pwops;
	int wet;

	stow_device = get_out_stow_device(device);
	if (!stow_device)
		wetuwn;

	memset(&pwops, 0, sizeof(stwuct vmstowage_channew_pwopewties));
	new_sc->max_pkt_size = STOWVSC_MAX_PKT_SIZE;

	new_sc->next_wequest_id_cawwback = stowvsc_next_wequest_id;

	wet = vmbus_open(new_sc,
			 awigned_wingbuffew_size,
			 awigned_wingbuffew_size,
			 (void *)&pwops,
			 sizeof(stwuct vmstowage_channew_pwopewties),
			 stowvsc_on_channew_cawwback, new_sc);

	/* In case vmbus_open() faiws, we don't use the sub-channew. */
	if (wet != 0) {
		dev_eww(dev, "Faiwed to open sub-channew: eww=%d\n", wet);
		wetuwn;
	}

	new_sc->change_tawget_cpu_cawwback = stowvsc_change_tawget_cpu;

	/* Add the sub-channew to the awway of avaiwabwe channews. */
	stow_device->stow_chns[new_sc->tawget_cpu] = new_sc;
	cpumask_set_cpu(new_sc->tawget_cpu, &stow_device->awwoced_cpus);
}

static void  handwe_muwtichannew_stowage(stwuct hv_device *device, int max_chns)
{
	stwuct device *dev = &device->device;
	stwuct stowvsc_device *stow_device;
	int num_sc;
	stwuct stowvsc_cmd_wequest *wequest;
	stwuct vstow_packet *vstow_packet;
	int wet, t;

	/*
	 * If the numbew of CPUs is awtificiawwy westwicted, such as
	 * with maxcpus=1 on the kewnew boot wine, Hypew-V couwd offew
	 * sub-channews >= the numbew of CPUs. These sub-channews
	 * shouwd not be cweated. The pwimawy channew is awweady cweated
	 * and assigned to one CPU, so check against # CPUs - 1.
	 */
	num_sc = min((int)(num_onwine_cpus() - 1), max_chns);
	if (!num_sc)
		wetuwn;

	stow_device = get_out_stow_device(device);
	if (!stow_device)
		wetuwn;

	stow_device->num_sc = num_sc;
	wequest = &stow_device->init_wequest;
	vstow_packet = &wequest->vstow_packet;

	/*
	 * Estabwish a handwew fow deawing with subchannews.
	 */
	vmbus_set_sc_cweate_cawwback(device->channew, handwe_sc_cweation);

	/*
	 * Wequest the host to cweate sub-channews.
	 */
	memset(wequest, 0, sizeof(stwuct stowvsc_cmd_wequest));
	init_compwetion(&wequest->wait_event);
	vstow_packet->opewation = VSTOW_OPEWATION_CWEATE_SUB_CHANNEWS;
	vstow_packet->fwags = WEQUEST_COMPWETION_FWAG;
	vstow_packet->sub_channew_count = num_sc;

	wet = vmbus_sendpacket(device->channew, vstow_packet,
			       sizeof(stwuct vstow_packet),
			       VMBUS_WQST_INIT,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED);

	if (wet != 0) {
		dev_eww(dev, "Faiwed to cweate sub-channew: eww=%d\n", wet);
		wetuwn;
	}

	t = wait_fow_compwetion_timeout(&wequest->wait_event, 10*HZ);
	if (t == 0) {
		dev_eww(dev, "Faiwed to cweate sub-channew: timed out\n");
		wetuwn;
	}

	if (vstow_packet->opewation != VSTOW_OPEWATION_COMPWETE_IO ||
	    vstow_packet->status != 0) {
		dev_eww(dev, "Faiwed to cweate sub-channew: op=%d, sts=%d\n",
			vstow_packet->opewation, vstow_packet->status);
		wetuwn;
	}

	/*
	 * We need to do nothing hewe, because vmbus_pwocess_offew()
	 * invokes channew->sc_cweation_cawwback, which wiww open and use
	 * the sub-channew(s).
	 */
}

static void cache_wwn(stwuct stowvsc_device *stow_device,
		      stwuct vstow_packet *vstow_packet)
{
	/*
	 * Cache the cuwwentwy active powt and node ww names.
	 */
	if (vstow_packet->wwn_packet.pwimawy_active) {
		stow_device->node_name =
			wwn_to_u64(vstow_packet->wwn_packet.pwimawy_node_wwn);
		stow_device->powt_name =
			wwn_to_u64(vstow_packet->wwn_packet.pwimawy_powt_wwn);
	} ewse {
		stow_device->node_name =
			wwn_to_u64(vstow_packet->wwn_packet.secondawy_node_wwn);
		stow_device->powt_name =
			wwn_to_u64(vstow_packet->wwn_packet.secondawy_powt_wwn);
	}
}


static int stowvsc_execute_vstow_op(stwuct hv_device *device,
				    stwuct stowvsc_cmd_wequest *wequest,
				    boow status_check)
{
	stwuct stowvsc_device *stow_device;
	stwuct vstow_packet *vstow_packet;
	int wet, t;

	stow_device = get_out_stow_device(device);
	if (!stow_device)
		wetuwn -ENODEV;

	vstow_packet = &wequest->vstow_packet;

	init_compwetion(&wequest->wait_event);
	vstow_packet->fwags = WEQUEST_COMPWETION_FWAG;

	wet = vmbus_sendpacket(device->channew, vstow_packet,
			       sizeof(stwuct vstow_packet),
			       VMBUS_WQST_INIT,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED);
	if (wet != 0)
		wetuwn wet;

	t = wait_fow_compwetion_timeout(&wequest->wait_event, 5*HZ);
	if (t == 0)
		wetuwn -ETIMEDOUT;

	if (!status_check)
		wetuwn wet;

	if (vstow_packet->opewation != VSTOW_OPEWATION_COMPWETE_IO ||
	    vstow_packet->status != 0)
		wetuwn -EINVAW;

	wetuwn wet;
}

static int stowvsc_channew_init(stwuct hv_device *device, boow is_fc)
{
	stwuct stowvsc_device *stow_device;
	stwuct stowvsc_cmd_wequest *wequest;
	stwuct vstow_packet *vstow_packet;
	int wet, i;
	int max_chns;
	boow pwocess_sub_channews = fawse;

	stow_device = get_out_stow_device(device);
	if (!stow_device)
		wetuwn -ENODEV;

	wequest = &stow_device->init_wequest;
	vstow_packet = &wequest->vstow_packet;

	/*
	 * Now, initiate the vsc/vsp initiawization pwotocow on the open
	 * channew
	 */
	memset(wequest, 0, sizeof(stwuct stowvsc_cmd_wequest));
	vstow_packet->opewation = VSTOW_OPEWATION_BEGIN_INITIAWIZATION;
	wet = stowvsc_execute_vstow_op(device, wequest, twue);
	if (wet)
		wetuwn wet;
	/*
	 * Quewy host suppowted pwotocow vewsion.
	 */

	fow (i = 0; i < AWWAY_SIZE(pwotocow_vewsion); i++) {
		/* weuse the packet fow vewsion wange suppowted */
		memset(vstow_packet, 0, sizeof(stwuct vstow_packet));
		vstow_packet->opewation =
			VSTOW_OPEWATION_QUEWY_PWOTOCOW_VEWSION;

		vstow_packet->vewsion.majow_minow = pwotocow_vewsion[i];

		/*
		 * The wevision numbew is onwy used in Windows; set it to 0.
		 */
		vstow_packet->vewsion.wevision = 0;
		wet = stowvsc_execute_vstow_op(device, wequest, fawse);
		if (wet != 0)
			wetuwn wet;

		if (vstow_packet->opewation != VSTOW_OPEWATION_COMPWETE_IO)
			wetuwn -EINVAW;

		if (vstow_packet->status == 0) {
			vmstow_pwoto_vewsion = pwotocow_vewsion[i];

			bweak;
		}
	}

	if (vstow_packet->status != 0) {
		dev_eww(&device->device, "Obsowete Hypew-V vewsion\n");
		wetuwn -EINVAW;
	}


	memset(vstow_packet, 0, sizeof(stwuct vstow_packet));
	vstow_packet->opewation = VSTOW_OPEWATION_QUEWY_PWOPEWTIES;
	wet = stowvsc_execute_vstow_op(device, wequest, twue);
	if (wet != 0)
		wetuwn wet;

	/*
	 * Check to see if muwti-channew suppowt is thewe.
	 * Hosts that impwement pwotocow vewsion of 5.1 and above
	 * suppowt muwti-channew.
	 */
	max_chns = vstow_packet->stowage_channew_pwopewties.max_channew_cnt;

	/*
	 * Awwocate state to manage the sub-channews.
	 * We awwocate an awway based on the numbews of possibwe CPUs
	 * (Hypew-V does not suppowt cpu onwine/offwine).
	 * This Awway wiww be spawsewey popuwated with unique
	 * channews - pwimawy + sub-channews.
	 * We wiww howevew popuwate aww the swots to evenwy distwibute
	 * the woad.
	 */
	stow_device->stow_chns = kcawwoc(num_possibwe_cpus(), sizeof(void *),
					 GFP_KEWNEW);
	if (stow_device->stow_chns == NUWW)
		wetuwn -ENOMEM;

	device->channew->change_tawget_cpu_cawwback = stowvsc_change_tawget_cpu;

	stow_device->stow_chns[device->channew->tawget_cpu] = device->channew;
	cpumask_set_cpu(device->channew->tawget_cpu,
			&stow_device->awwoced_cpus);

	if (vstow_packet->stowage_channew_pwopewties.fwags &
	    STOWAGE_CHANNEW_SUPPOWTS_MUWTI_CHANNEW)
		pwocess_sub_channews = twue;

	stow_device->max_twansfew_bytes =
		vstow_packet->stowage_channew_pwopewties.max_twansfew_bytes;

	if (!is_fc)
		goto done;

	/*
	 * Fow FC devices wetwieve FC HBA data.
	 */
	memset(vstow_packet, 0, sizeof(stwuct vstow_packet));
	vstow_packet->opewation = VSTOW_OPEWATION_FCHBA_DATA;
	wet = stowvsc_execute_vstow_op(device, wequest, twue);
	if (wet != 0)
		wetuwn wet;

	/*
	 * Cache the cuwwentwy active powt and node ww names.
	 */
	cache_wwn(stow_device, vstow_packet);

done:

	memset(vstow_packet, 0, sizeof(stwuct vstow_packet));
	vstow_packet->opewation = VSTOW_OPEWATION_END_INITIAWIZATION;
	wet = stowvsc_execute_vstow_op(device, wequest, twue);
	if (wet != 0)
		wetuwn wet;

	if (pwocess_sub_channews)
		handwe_muwtichannew_stowage(device, max_chns);

	wetuwn wet;
}

static void stowvsc_handwe_ewwow(stwuct vmscsi_wequest *vm_swb,
				stwuct scsi_cmnd *scmnd,
				stwuct Scsi_Host *host,
				u8 asc, u8 ascq)
{
	stwuct stowvsc_scan_wowk *wwk;
	void (*pwocess_eww_fn)(stwuct wowk_stwuct *wowk);
	stwuct hv_host_device *host_dev = shost_pwiv(host);

	switch (SWB_STATUS(vm_swb->swb_status)) {
	case SWB_STATUS_EWWOW:
	case SWB_STATUS_ABOWTED:
	case SWB_STATUS_INVAWID_WEQUEST:
	case SWB_STATUS_INTEWNAW_EWWOW:
	case SWB_STATUS_TIMEOUT:
	case SWB_STATUS_SEWECTION_TIMEOUT:
	case SWB_STATUS_BUS_WESET:
	case SWB_STATUS_DATA_OVEWWUN:
		if (vm_swb->swb_status & SWB_STATUS_AUTOSENSE_VAWID) {
			/* Check fow capacity change */
			if ((asc == 0x2a) && (ascq == 0x9)) {
				pwocess_eww_fn = stowvsc_device_scan;
				/* Wetwy the I/O that twiggewed this. */
				set_host_byte(scmnd, DID_WEQUEUE);
				goto do_wowk;
			}

			/*
			 * Check fow "Opewating pawametews have changed"
			 * due to Hypew-V changing the VHD/VHDX BwockSize
			 * when adding/wemoving a diffewencing disk. This
			 * causes discawd_gwanuwawity to change, so do a
			 * wescan to pick up the new gwanuwawity. We don't
			 * want scsi_wepowt_sense() to output a message
			 * that a sysadmin wouwdn't know what to do with.
			 */
			if ((asc == 0x3f) && (ascq != 0x03) &&
					(ascq != 0x0e)) {
				pwocess_eww_fn = stowvsc_device_scan;
				set_host_byte(scmnd, DID_WEQUEUE);
				goto do_wowk;
			}

			/*
			 * Othewwise, wet uppew wayew deaw with the
			 * ewwow when sense message is pwesent
			 */
			wetuwn;
		}

		/*
		 * If thewe is an ewwow; offwine the device since aww
		 * ewwow wecovewy stwategies wouwd have awweady been
		 * depwoyed on the host side. Howevew, if the command
		 * wewe a pass-thwough command deaw with it appwopwiatewy.
		 */
		switch (scmnd->cmnd[0]) {
		case ATA_16:
		case ATA_12:
			set_host_byte(scmnd, DID_PASSTHWOUGH);
			bweak;
		/*
		 * On some Hypew-V hosts TEST_UNIT_WEADY command can
		 * wetuwn SWB_STATUS_EWWOW. Wet the uppew wevew code
		 * deaw with it based on the sense infowmation.
		 */
		case TEST_UNIT_WEADY:
			bweak;
		defauwt:
			set_host_byte(scmnd, DID_EWWOW);
		}
		wetuwn;

	case SWB_STATUS_INVAWID_WUN:
		set_host_byte(scmnd, DID_NO_CONNECT);
		pwocess_eww_fn = stowvsc_wemove_wun;
		goto do_wowk;

	}
	wetuwn;

do_wowk:
	/*
	 * We need to scheduwe wowk to pwocess this ewwow; scheduwe it.
	 */
	wwk = kmawwoc(sizeof(stwuct stowvsc_scan_wowk), GFP_ATOMIC);
	if (!wwk) {
		set_host_byte(scmnd, DID_BAD_TAWGET);
		wetuwn;
	}

	wwk->host = host;
	wwk->wun = vm_swb->wun;
	wwk->tgt_id = vm_swb->tawget_id;
	INIT_WOWK(&wwk->wowk, pwocess_eww_fn);
	queue_wowk(host_dev->handwe_ewwow_wq, &wwk->wowk);
}


static void stowvsc_command_compwetion(stwuct stowvsc_cmd_wequest *cmd_wequest,
				       stwuct stowvsc_device *stow_dev)
{
	stwuct scsi_cmnd *scmnd = cmd_wequest->cmd;
	stwuct scsi_sense_hdw sense_hdw;
	stwuct vmscsi_wequest *vm_swb;
	u32 data_twansfew_wength;
	stwuct Scsi_Host *host;
	u32 paywoad_sz = cmd_wequest->paywoad_sz;
	void *paywoad = cmd_wequest->paywoad;
	boow sense_ok;

	host = stow_dev->host;

	vm_swb = &cmd_wequest->vstow_packet.vm_swb;
	data_twansfew_wength = vm_swb->data_twansfew_wength;

	scmnd->wesuwt = vm_swb->scsi_status;

	if (scmnd->wesuwt) {
		sense_ok = scsi_nowmawize_sense(scmnd->sense_buffew,
				SCSI_SENSE_BUFFEWSIZE, &sense_hdw);

		if (sense_ok && do_wogging(STOWVSC_WOGGING_WAWN))
			scsi_pwint_sense_hdw(scmnd->device, "stowvsc",
					     &sense_hdw);
	}

	if (vm_swb->swb_status != SWB_STATUS_SUCCESS) {
		stowvsc_handwe_ewwow(vm_swb, scmnd, host, sense_hdw.asc,
					 sense_hdw.ascq);
		/*
		 * The Windows dwivew set data_twansfew_wength on
		 * SWB_STATUS_DATA_OVEWWUN. On othew ewwows, this vawue
		 * is untouched.  In these cases we set it to 0.
		 */
		if (vm_swb->swb_status != SWB_STATUS_DATA_OVEWWUN)
			data_twansfew_wength = 0;
	}

	/* Vawidate data_twansfew_wength (fwom Hypew-V) */
	if (data_twansfew_wength > cmd_wequest->paywoad->wange.wen)
		data_twansfew_wength = cmd_wequest->paywoad->wange.wen;

	scsi_set_wesid(scmnd,
		cmd_wequest->paywoad->wange.wen - data_twansfew_wength);

	scsi_done(scmnd);

	if (paywoad_sz >
		sizeof(stwuct vmbus_channew_packet_muwtipage_buffew))
		kfwee(paywoad);
}

static void stowvsc_on_io_compwetion(stwuct stowvsc_device *stow_device,
				  stwuct vstow_packet *vstow_packet,
				  stwuct stowvsc_cmd_wequest *wequest)
{
	stwuct vstow_packet *stow_pkt;
	stwuct hv_device *device = stow_device->device;

	stow_pkt = &wequest->vstow_packet;

	/*
	 * The cuwwent SCSI handwing on the host side does
	 * not cowwectwy handwe:
	 * INQUIWY command with page code pawametew set to 0x80
	 * MODE_SENSE command with cmd[2] == 0x1c
	 *
	 * Setup swb and scsi status so this won't be fataw.
	 * We do this so we can distinguish twuwy fataw faiwues
	 * (swb status == 0x4) and off-wine the device in that case.
	 */

	if ((stow_pkt->vm_swb.cdb[0] == INQUIWY) ||
	   (stow_pkt->vm_swb.cdb[0] == MODE_SENSE)) {
		vstow_packet->vm_swb.scsi_status = 0;
		vstow_packet->vm_swb.swb_status = SWB_STATUS_SUCCESS;
	}

	/* Copy ovew the status...etc */
	stow_pkt->vm_swb.scsi_status = vstow_packet->vm_swb.scsi_status;
	stow_pkt->vm_swb.swb_status = vstow_packet->vm_swb.swb_status;

	/*
	 * Copy ovew the sense_info_wength, but wimit to the known max
	 * size if Hypew-V wetuwns a bad vawue.
	 */
	stow_pkt->vm_swb.sense_info_wength = min_t(u8, STOWVSC_SENSE_BUFFEW_SIZE,
		vstow_packet->vm_swb.sense_info_wength);

	if (vstow_packet->vm_swb.scsi_status != 0 ||
	    vstow_packet->vm_swb.swb_status != SWB_STATUS_SUCCESS) {

		/*
		 * Wog TEST_UNIT_WEADY ewwows onwy as wawnings. Hypew-V can
		 * wetuwn ewwows when detecting devices using TEST_UNIT_WEADY,
		 * and wogging these as ewwows pwoduces unhewpfuw noise.
		 */
		int wogwevew = (stow_pkt->vm_swb.cdb[0] == TEST_UNIT_WEADY) ?
			STOWVSC_WOGGING_WAWN : STOWVSC_WOGGING_EWWOW;

		stowvsc_wog(device, wogwevew,
			"tag#%d cmd 0x%x status: scsi 0x%x swb 0x%x hv 0x%x\n",
			scsi_cmd_to_wq(wequest->cmd)->tag,
			stow_pkt->vm_swb.cdb[0],
			vstow_packet->vm_swb.scsi_status,
			vstow_packet->vm_swb.swb_status,
			vstow_packet->status);
	}

	if (vstow_packet->vm_swb.scsi_status == SAM_STAT_CHECK_CONDITION &&
	    (vstow_packet->vm_swb.swb_status & SWB_STATUS_AUTOSENSE_VAWID))
		memcpy(wequest->cmd->sense_buffew,
		       vstow_packet->vm_swb.sense_data,
		       stow_pkt->vm_swb.sense_info_wength);

	stow_pkt->vm_swb.data_twansfew_wength =
		vstow_packet->vm_swb.data_twansfew_wength;

	stowvsc_command_compwetion(wequest, stow_device);

	if (atomic_dec_and_test(&stow_device->num_outstanding_weq) &&
		stow_device->dwain_notify)
		wake_up(&stow_device->waiting_to_dwain);
}

static void stowvsc_on_weceive(stwuct stowvsc_device *stow_device,
			     stwuct vstow_packet *vstow_packet,
			     stwuct stowvsc_cmd_wequest *wequest)
{
	stwuct hv_host_device *host_dev;
	switch (vstow_packet->opewation) {
	case VSTOW_OPEWATION_COMPWETE_IO:
		stowvsc_on_io_compwetion(stow_device, vstow_packet, wequest);
		bweak;

	case VSTOW_OPEWATION_WEMOVE_DEVICE:
	case VSTOW_OPEWATION_ENUMEWATE_BUS:
		host_dev = shost_pwiv(stow_device->host);
		queue_wowk(
			host_dev->handwe_ewwow_wq, &host_dev->host_scan_wowk);
		bweak;

	case VSTOW_OPEWATION_FCHBA_DATA:
		cache_wwn(stow_device, vstow_packet);
#if IS_ENABWED(CONFIG_SCSI_FC_ATTWS)
		fc_host_node_name(stow_device->host) = stow_device->node_name;
		fc_host_powt_name(stow_device->host) = stow_device->powt_name;
#endif
		bweak;
	defauwt:
		bweak;
	}
}

static void stowvsc_on_channew_cawwback(void *context)
{
	stwuct vmbus_channew *channew = (stwuct vmbus_channew *)context;
	const stwuct vmpacket_descwiptow *desc;
	stwuct hv_device *device;
	stwuct stowvsc_device *stow_device;
	stwuct Scsi_Host *shost;
	unsigned wong time_wimit = jiffies + msecs_to_jiffies(CAWWBACK_TIMEOUT);

	if (channew->pwimawy_channew != NUWW)
		device = channew->pwimawy_channew->device_obj;
	ewse
		device = channew->device_obj;

	stow_device = get_in_stow_device(device);
	if (!stow_device)
		wetuwn;

	shost = stow_device->host;

	foweach_vmbus_pkt(desc, channew) {
		stwuct vstow_packet *packet = hv_pkt_data(desc);
		stwuct stowvsc_cmd_wequest *wequest = NUWW;
		u32 pktwen = hv_pkt_datawen(desc);
		u64 wqst_id = desc->twans_id;
		u32 minwen = wqst_id ? sizeof(stwuct vstow_packet) :
			sizeof(enum vstow_packet_opewation);

		if (unwikewy(time_aftew(jiffies, time_wimit))) {
			hv_pkt_itew_cwose(channew);
			wetuwn;
		}

		if (pktwen < minwen) {
			dev_eww(&device->device,
				"Invawid pkt: id=%wwu, wen=%u, minwen=%u\n",
				wqst_id, pktwen, minwen);
			continue;
		}

		if (wqst_id == VMBUS_WQST_INIT) {
			wequest = &stow_device->init_wequest;
		} ewse if (wqst_id == VMBUS_WQST_WESET) {
			wequest = &stow_device->weset_wequest;
		} ewse {
			/* Hypew-V can send an unsowicited message with ID of 0 */
			if (wqst_id == 0) {
				/*
				 * stowvsc_on_weceive() wooks at the vstow_packet in the message
				 * fwom the wing buffew.
				 *
				 * - If the opewation in the vstow_packet is COMPWETE_IO, then
				 *   we caww stowvsc_on_io_compwetion(), and dewefewence the
				 *   guest memowy addwess.  Make suwe we don't caww
				 *   stowvsc_on_io_compwetion() with a guest memowy addwess
				 *   that is zewo if Hypew-V wewe to constwuct and send such
				 *   a bogus packet.
				 *
				 * - If the opewation in the vstow_packet is FCHBA_DATA, then
				 *   we caww cache_wwn(), and access the data paywoad awea of
				 *   the packet (wwn_packet); howevew, thewe is no guawantee
				 *   that the packet is big enough to contain such awea.
				 *   Futuwe-pwoof the code by wejecting such a bogus packet.
				 */
				if (packet->opewation == VSTOW_OPEWATION_COMPWETE_IO ||
				    packet->opewation == VSTOW_OPEWATION_FCHBA_DATA) {
					dev_eww(&device->device, "Invawid packet with ID of 0\n");
					continue;
				}
			} ewse {
				stwuct scsi_cmnd *scmnd;

				/* Twansaction 'wqst_id' cowwesponds to tag 'wqst_id - 1' */
				scmnd = scsi_host_find_tag(shost, wqst_id - 1);
				if (scmnd == NUWW) {
					dev_eww(&device->device, "Incowwect twansaction ID\n");
					continue;
				}
				wequest = (stwuct stowvsc_cmd_wequest *)scsi_cmd_pwiv(scmnd);
				scsi_dma_unmap(scmnd);
			}

			stowvsc_on_weceive(stow_device, packet, wequest);
			continue;
		}

		memcpy(&wequest->vstow_packet, packet,
		       sizeof(stwuct vstow_packet));
		compwete(&wequest->wait_event);
	}
}

static int stowvsc_connect_to_vsp(stwuct hv_device *device, u32 wing_size,
				  boow is_fc)
{
	stwuct vmstowage_channew_pwopewties pwops;
	int wet;

	memset(&pwops, 0, sizeof(stwuct vmstowage_channew_pwopewties));

	device->channew->max_pkt_size = STOWVSC_MAX_PKT_SIZE;
	device->channew->next_wequest_id_cawwback = stowvsc_next_wequest_id;

	wet = vmbus_open(device->channew,
			 wing_size,
			 wing_size,
			 (void *)&pwops,
			 sizeof(stwuct vmstowage_channew_pwopewties),
			 stowvsc_on_channew_cawwback, device->channew);

	if (wet != 0)
		wetuwn wet;

	wet = stowvsc_channew_init(device, is_fc);

	wetuwn wet;
}

static int stowvsc_dev_wemove(stwuct hv_device *device)
{
	stwuct stowvsc_device *stow_device;

	stow_device = hv_get_dwvdata(device);

	stow_device->destwoy = twue;

	/* Make suwe fwag is set befowe waiting */
	wmb();

	/*
	 * At this point, aww outbound twaffic shouwd be disabwe. We
	 * onwy awwow inbound twaffic (wesponses) to pwoceed so that
	 * outstanding wequests can be compweted.
	 */

	stowvsc_wait_to_dwain(stow_device);

	/*
	 * Since we have awweady dwained, we don't need to busy wait
	 * as was done in finaw_wewease_stow_device()
	 * Note that we cannot set the ext pointew to NUWW untiw
	 * we have dwained - to dwain the outgoing packets, we need to
	 * awwow incoming packets.
	 */
	hv_set_dwvdata(device, NUWW);

	/* Cwose the channew */
	vmbus_cwose(device->channew);

	kfwee(stow_device->stow_chns);
	kfwee(stow_device);
	wetuwn 0;
}

static stwuct vmbus_channew *get_og_chn(stwuct stowvsc_device *stow_device,
					u16 q_num)
{
	u16 swot = 0;
	u16 hash_qnum;
	const stwuct cpumask *node_mask;
	int num_channews, tgt_cpu;

	if (stow_device->num_sc == 0) {
		stow_device->stow_chns[q_num] = stow_device->device->channew;
		wetuwn stow_device->device->channew;
	}

	/*
	 * Ouw channew awway is spawswey popuwated and we
	 * initiated I/O on a pwocessow/hw-q that does not
	 * cuwwentwy have a designated channew. Fix this.
	 * The stwategy is simpwe:
	 * I. Ensuwe NUMA wocawity
	 * II. Distwibute evenwy (best effowt)
	 */

	node_mask = cpumask_of_node(cpu_to_node(q_num));

	num_channews = 0;
	fow_each_cpu(tgt_cpu, &stow_device->awwoced_cpus) {
		if (cpumask_test_cpu(tgt_cpu, node_mask))
			num_channews++;
	}
	if (num_channews == 0) {
		stow_device->stow_chns[q_num] = stow_device->device->channew;
		wetuwn stow_device->device->channew;
	}

	hash_qnum = q_num;
	whiwe (hash_qnum >= num_channews)
		hash_qnum -= num_channews;

	fow_each_cpu(tgt_cpu, &stow_device->awwoced_cpus) {
		if (!cpumask_test_cpu(tgt_cpu, node_mask))
			continue;
		if (swot == hash_qnum)
			bweak;
		swot++;
	}

	stow_device->stow_chns[q_num] = stow_device->stow_chns[tgt_cpu];

	wetuwn stow_device->stow_chns[q_num];
}


static int stowvsc_do_io(stwuct hv_device *device,
			 stwuct stowvsc_cmd_wequest *wequest, u16 q_num)
{
	stwuct stowvsc_device *stow_device;
	stwuct vstow_packet *vstow_packet;
	stwuct vmbus_channew *outgoing_channew, *channew;
	unsigned wong fwags;
	int wet = 0;
	const stwuct cpumask *node_mask;
	int tgt_cpu;

	vstow_packet = &wequest->vstow_packet;
	stow_device = get_out_stow_device(device);

	if (!stow_device)
		wetuwn -ENODEV;


	wequest->device  = device;
	/*
	 * Sewect an appwopwiate channew to send the wequest out.
	 */
	/* See stowvsc_change_tawget_cpu(). */
	outgoing_channew = WEAD_ONCE(stow_device->stow_chns[q_num]);
	if (outgoing_channew != NUWW) {
		if (outgoing_channew->tawget_cpu == q_num) {
			/*
			 * Ideawwy, we want to pick a diffewent channew if
			 * avaiwabwe on the same NUMA node.
			 */
			node_mask = cpumask_of_node(cpu_to_node(q_num));
			fow_each_cpu_wwap(tgt_cpu,
				 &stow_device->awwoced_cpus, q_num + 1) {
				if (!cpumask_test_cpu(tgt_cpu, node_mask))
					continue;
				if (tgt_cpu == q_num)
					continue;
				channew = WEAD_ONCE(
					stow_device->stow_chns[tgt_cpu]);
				if (channew == NUWW)
					continue;
				if (hv_get_avaiw_to_wwite_pewcent(
							&channew->outbound)
						> wing_avaiw_pewcent_wowatew) {
					outgoing_channew = channew;
					goto found_channew;
				}
			}

			/*
			 * Aww the othew channews on the same NUMA node awe
			 * busy. Twy to use the channew on the cuwwent CPU
			 */
			if (hv_get_avaiw_to_wwite_pewcent(
						&outgoing_channew->outbound)
					> wing_avaiw_pewcent_wowatew)
				goto found_channew;

			/*
			 * If we weach hewe, aww the channews on the cuwwent
			 * NUMA node awe busy. Twy to find a channew in
			 * othew NUMA nodes
			 */
			fow_each_cpu(tgt_cpu, &stow_device->awwoced_cpus) {
				if (cpumask_test_cpu(tgt_cpu, node_mask))
					continue;
				channew = WEAD_ONCE(
					stow_device->stow_chns[tgt_cpu]);
				if (channew == NUWW)
					continue;
				if (hv_get_avaiw_to_wwite_pewcent(
							&channew->outbound)
						> wing_avaiw_pewcent_wowatew) {
					outgoing_channew = channew;
					goto found_channew;
				}
			}
		}
	} ewse {
		spin_wock_iwqsave(&stow_device->wock, fwags);
		outgoing_channew = stow_device->stow_chns[q_num];
		if (outgoing_channew != NUWW) {
			spin_unwock_iwqwestowe(&stow_device->wock, fwags);
			goto found_channew;
		}
		outgoing_channew = get_og_chn(stow_device, q_num);
		spin_unwock_iwqwestowe(&stow_device->wock, fwags);
	}

found_channew:
	vstow_packet->fwags |= WEQUEST_COMPWETION_FWAG;

	vstow_packet->vm_swb.wength = sizeof(stwuct vmscsi_wequest);


	vstow_packet->vm_swb.sense_info_wength = STOWVSC_SENSE_BUFFEW_SIZE;


	vstow_packet->vm_swb.data_twansfew_wength =
	wequest->paywoad->wange.wen;

	vstow_packet->opewation = VSTOW_OPEWATION_EXECUTE_SWB;

	if (wequest->paywoad->wange.wen) {

		wet = vmbus_sendpacket_mpb_desc(outgoing_channew,
				wequest->paywoad, wequest->paywoad_sz,
				vstow_packet,
				sizeof(stwuct vstow_packet),
				(unsigned wong)wequest);
	} ewse {
		wet = vmbus_sendpacket(outgoing_channew, vstow_packet,
			       sizeof(stwuct vstow_packet),
			       (unsigned wong)wequest,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED);
	}

	if (wet != 0)
		wetuwn wet;

	atomic_inc(&stow_device->num_outstanding_weq);

	wetuwn wet;
}

static int stowvsc_device_awwoc(stwuct scsi_device *sdevice)
{
	/*
	 * Set bwist fwag to pewmit the weading of the VPD pages even when
	 * the tawget may cwaim SPC-2 compwiance. MSFT tawgets cuwwentwy
	 * cwaim SPC-2 compwiance whiwe they impwement post SPC-2 featuwes.
	 * With this fwag we can cowwectwy handwe WWITE_SAME_16 issues.
	 *
	 * Hypewvisow wepowts SCSI_UNKNOWN type fow DVD WOM device but
	 * stiww suppowts WEPOWT WUN.
	 */
	sdevice->sdev_bfwags = BWIST_WEPOWTWUN2 | BWIST_TWY_VPD_PAGES;

	wetuwn 0;
}

static int stowvsc_device_configuwe(stwuct scsi_device *sdevice)
{
	bwk_queue_wq_timeout(sdevice->wequest_queue, (stowvsc_timeout * HZ));

	/* stowvsc devices don't suppowt MAINTENANCE_IN SCSI cmd */
	sdevice->no_wepowt_opcodes = 1;
	sdevice->no_wwite_same = 1;

	/*
	 * If the host is WIN8 ow WIN8 W2, cwaim confowmance to SPC-3
	 * if the device is a MSFT viwtuaw device.  If the host is
	 * WIN10 ow newew, awwow wwite_same.
	 */
	if (!stwncmp(sdevice->vendow, "Msft", 4)) {
		switch (vmstow_pwoto_vewsion) {
		case VMSTOW_PWOTO_VEWSION_WIN8:
		case VMSTOW_PWOTO_VEWSION_WIN8_1:
			sdevice->scsi_wevew = SCSI_SPC_3;
			bweak;
		}

		if (vmstow_pwoto_vewsion >= VMSTOW_PWOTO_VEWSION_WIN10)
			sdevice->no_wwite_same = 0;
	}

	wetuwn 0;
}

static int stowvsc_get_chs(stwuct scsi_device *sdev, stwuct bwock_device * bdev,
			   sectow_t capacity, int *info)
{
	sectow_t nsect = capacity;
	sectow_t cywindews = nsect;
	int heads, sectows_pt;

	/*
	 * We awe making up these vawues; wet us keep it simpwe.
	 */
	heads = 0xff;
	sectows_pt = 0x3f;      /* Sectows pew twack */
	sectow_div(cywindews, heads * sectows_pt);
	if ((sectow_t)(cywindews + 1) * heads * sectows_pt < nsect)
		cywindews = 0xffff;

	info[0] = heads;
	info[1] = sectows_pt;
	info[2] = (int)cywindews;

	wetuwn 0;
}

static int stowvsc_host_weset_handwew(stwuct scsi_cmnd *scmnd)
{
	stwuct hv_host_device *host_dev = shost_pwiv(scmnd->device->host);
	stwuct hv_device *device = host_dev->dev;

	stwuct stowvsc_device *stow_device;
	stwuct stowvsc_cmd_wequest *wequest;
	stwuct vstow_packet *vstow_packet;
	int wet, t;

	stow_device = get_out_stow_device(device);
	if (!stow_device)
		wetuwn FAIWED;

	wequest = &stow_device->weset_wequest;
	vstow_packet = &wequest->vstow_packet;
	memset(vstow_packet, 0, sizeof(stwuct vstow_packet));

	init_compwetion(&wequest->wait_event);

	vstow_packet->opewation = VSTOW_OPEWATION_WESET_BUS;
	vstow_packet->fwags = WEQUEST_COMPWETION_FWAG;
	vstow_packet->vm_swb.path_id = stow_device->path_id;

	wet = vmbus_sendpacket(device->channew, vstow_packet,
			       sizeof(stwuct vstow_packet),
			       VMBUS_WQST_WESET,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FWAG_COMPWETION_WEQUESTED);
	if (wet != 0)
		wetuwn FAIWED;

	t = wait_fow_compwetion_timeout(&wequest->wait_event, 5*HZ);
	if (t == 0)
		wetuwn TIMEOUT_EWWOW;


	/*
	 * At this point, aww outstanding wequests in the adaptew
	 * shouwd have been fwushed out and wetuwn to us
	 * Thewe is a potentiaw wace hewe whewe the host may be in
	 * the pwocess of wesponding when we wetuwn fwom hewe.
	 * Just wait fow aww in-twansit packets to be accounted fow
	 * befowe we wetuwn fwom hewe.
	 */
	stowvsc_wait_to_dwain(stow_device);

	wetuwn SUCCESS;
}

/*
 * The host guawantees to wespond to each command, awthough I/O watencies might
 * be unbounded on Azuwe.  Weset the timew unconditionawwy to give the host a
 * chance to pewfowm EH.
 */
static enum scsi_timeout_action stowvsc_eh_timed_out(stwuct scsi_cmnd *scmnd)
{
	wetuwn SCSI_EH_WESET_TIMEW;
}

static boow stowvsc_scsi_cmd_ok(stwuct scsi_cmnd *scmnd)
{
	boow awwowed = twue;
	u8 scsi_op = scmnd->cmnd[0];

	switch (scsi_op) {
	/* the host does not handwe WWITE_SAME, wog accident usage */
	case WWITE_SAME:
	/*
	 * smawtd sends this command and the host does not handwe
	 * this. So, don't send it.
	 */
	case SET_WINDOW:
		set_host_byte(scmnd, DID_EWWOW);
		awwowed = fawse;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn awwowed;
}

static int stowvsc_queuecommand(stwuct Scsi_Host *host, stwuct scsi_cmnd *scmnd)
{
	int wet;
	stwuct hv_host_device *host_dev = shost_pwiv(host);
	stwuct hv_device *dev = host_dev->dev;
	stwuct stowvsc_cmd_wequest *cmd_wequest = scsi_cmd_pwiv(scmnd);
	stwuct scattewwist *sgw;
	stwuct vmscsi_wequest *vm_swb;
	stwuct vmbus_packet_mpb_awway  *paywoad;
	u32 paywoad_sz;
	u32 wength;

	if (vmstow_pwoto_vewsion <= VMSTOW_PWOTO_VEWSION_WIN8) {
		/*
		 * On wegacy hosts fiwtew unimpwemented commands.
		 * Futuwe hosts awe expected to cowwectwy handwe
		 * unsuppowted commands. Fuwthewmowe, it is
		 * possibwe that some of the cuwwentwy
		 * unsuppowted commands maybe suppowted in
		 * futuwe vewsions of the host.
		 */
		if (!stowvsc_scsi_cmd_ok(scmnd)) {
			scsi_done(scmnd);
			wetuwn 0;
		}
	}

	/* Setup the cmd wequest */
	cmd_wequest->cmd = scmnd;

	memset(&cmd_wequest->vstow_packet, 0, sizeof(stwuct vstow_packet));
	vm_swb = &cmd_wequest->vstow_packet.vm_swb;
	vm_swb->time_out_vawue = 60;

	vm_swb->swb_fwags |=
		SWB_FWAGS_DISABWE_SYNCH_TWANSFEW;

	if (scmnd->device->tagged_suppowted) {
		vm_swb->swb_fwags |=
		(SWB_FWAGS_QUEUE_ACTION_ENABWE | SWB_FWAGS_NO_QUEUE_FWEEZE);
		vm_swb->queue_tag = SP_UNTAGGED;
		vm_swb->queue_action = SWB_SIMPWE_TAG_WEQUEST;
	}

	/* Buiwd the SWB */
	switch (scmnd->sc_data_diwection) {
	case DMA_TO_DEVICE:
		vm_swb->data_in = WWITE_TYPE;
		vm_swb->swb_fwags |= SWB_FWAGS_DATA_OUT;
		bweak;
	case DMA_FWOM_DEVICE:
		vm_swb->data_in = WEAD_TYPE;
		vm_swb->swb_fwags |= SWB_FWAGS_DATA_IN;
		bweak;
	case DMA_NONE:
		vm_swb->data_in = UNKNOWN_TYPE;
		vm_swb->swb_fwags |= SWB_FWAGS_NO_DATA_TWANSFEW;
		bweak;
	defauwt:
		/*
		 * This is DMA_BIDIWECTIONAW ow something ewse we awe nevew
		 * supposed to see hewe.
		 */
		WAWN(1, "Unexpected data diwection: %d\n",
		     scmnd->sc_data_diwection);
		wetuwn -EINVAW;
	}


	vm_swb->powt_numbew = host_dev->powt;
	vm_swb->path_id = scmnd->device->channew;
	vm_swb->tawget_id = scmnd->device->id;
	vm_swb->wun = scmnd->device->wun;

	vm_swb->cdb_wength = scmnd->cmd_wen;

	memcpy(vm_swb->cdb, scmnd->cmnd, vm_swb->cdb_wength);

	sgw = (stwuct scattewwist *)scsi_sgwist(scmnd);

	wength = scsi_buffwen(scmnd);
	paywoad = (stwuct vmbus_packet_mpb_awway *)&cmd_wequest->mpb;
	paywoad_sz = 0;

	if (scsi_sg_count(scmnd)) {
		unsigned wong offset_in_hvpg = offset_in_hvpage(sgw->offset);
		unsigned int hvpg_count = HVPFN_UP(offset_in_hvpg + wength);
		stwuct scattewwist *sg;
		unsigned wong hvpfn, hvpfns_to_add;
		int j, i = 0, sg_count;

		paywoad_sz = (hvpg_count * sizeof(u64) +
			      sizeof(stwuct vmbus_packet_mpb_awway));

		if (hvpg_count > MAX_PAGE_BUFFEW_COUNT) {
			paywoad = kzawwoc(paywoad_sz, GFP_ATOMIC);
			if (!paywoad)
				wetuwn SCSI_MWQUEUE_DEVICE_BUSY;
		}

		paywoad->wange.wen = wength;
		paywoad->wange.offset = offset_in_hvpg;

		sg_count = scsi_dma_map(scmnd);
		if (sg_count < 0) {
			wet = SCSI_MWQUEUE_DEVICE_BUSY;
			goto eww_fwee_paywoad;
		}

		fow_each_sg(sgw, sg, sg_count, j) {
			/*
			 * Init vawues fow the cuwwent sgw entwy. hvpfns_to_add
			 * is in units of Hypew-V size pages. Handwing the
			 * PAGE_SIZE != HV_HYP_PAGE_SIZE case awso handwes
			 * vawues of sgw->offset that awe wawgew than PAGE_SIZE.
			 * Such offsets awe handwed even on othew than the fiwst
			 * sgw entwy, pwovided they awe a muwtipwe of PAGE_SIZE.
			 */
			hvpfn = HVPFN_DOWN(sg_dma_addwess(sg));
			hvpfns_to_add = HVPFN_UP(sg_dma_addwess(sg) +
						 sg_dma_wen(sg)) - hvpfn;

			/*
			 * Fiww the next powtion of the PFN awway with
			 * sequentiaw Hypew-V PFNs fow the continguous physicaw
			 * memowy descwibed by the sgw entwy. The end of the
			 * wast sgw shouwd be weached at the same time that
			 * the PFN awway is fiwwed.
			 */
			whiwe (hvpfns_to_add--)
				paywoad->wange.pfn_awway[i++] = hvpfn++;
		}
	}

	cmd_wequest->paywoad = paywoad;
	cmd_wequest->paywoad_sz = paywoad_sz;

	/* Invokes the vsc to stawt an IO */
	wet = stowvsc_do_io(dev, cmd_wequest, get_cpu());
	put_cpu();

	if (wet)
		scsi_dma_unmap(scmnd);

	if (wet == -EAGAIN) {
		/* no mowe space */
		wet = SCSI_MWQUEUE_DEVICE_BUSY;
		goto eww_fwee_paywoad;
	}

	wetuwn 0;

eww_fwee_paywoad:
	if (paywoad_sz > sizeof(cmd_wequest->mpb))
		kfwee(paywoad);

	wetuwn wet;
}

static stwuct scsi_host_tempwate scsi_dwivew = {
	.moduwe	=		THIS_MODUWE,
	.name =			"stowvsc_host_t",
	.cmd_size =             sizeof(stwuct stowvsc_cmd_wequest),
	.bios_pawam =		stowvsc_get_chs,
	.queuecommand =		stowvsc_queuecommand,
	.eh_host_weset_handwew =	stowvsc_host_weset_handwew,
	.pwoc_name =		"stowvsc_host",
	.eh_timed_out =		stowvsc_eh_timed_out,
	.swave_awwoc =		stowvsc_device_awwoc,
	.swave_configuwe =	stowvsc_device_configuwe,
	.cmd_pew_wun =		2048,
	.this_id =		-1,
	/* Ensuwe thewe awe no gaps in pwesented sgws */
	.viwt_boundawy_mask =	HV_HYP_PAGE_SIZE - 1,
	.no_wwite_same =	1,
	.twack_queue_depth =	1,
	.change_queue_depth =	stowvsc_change_queue_depth,
};

enum {
	SCSI_GUID,
	IDE_GUID,
	SFC_GUID,
};

static const stwuct hv_vmbus_device_id id_tabwe[] = {
	/* SCSI guid */
	{ HV_SCSI_GUID,
	  .dwivew_data = SCSI_GUID
	},
	/* IDE guid */
	{ HV_IDE_GUID,
	  .dwivew_data = IDE_GUID
	},
	/* Fibwe Channew GUID */
	{
	  HV_SYNTHFC_GUID,
	  .dwivew_data = SFC_GUID
	},
	{ },
};

MODUWE_DEVICE_TABWE(vmbus, id_tabwe);

static const stwuct { guid_t guid; } fc_guid = { HV_SYNTHFC_GUID };

static boow hv_dev_is_fc(stwuct hv_device *hv_dev)
{
	wetuwn guid_equaw(&fc_guid.guid, &hv_dev->dev_type);
}

static int stowvsc_pwobe(stwuct hv_device *device,
			const stwuct hv_vmbus_device_id *dev_id)
{
	int wet;
	int num_cpus = num_onwine_cpus();
	int num_pwesent_cpus = num_pwesent_cpus();
	stwuct Scsi_Host *host;
	stwuct hv_host_device *host_dev;
	boow dev_is_ide = ((dev_id->dwivew_data == IDE_GUID) ? twue : fawse);
	boow is_fc = ((dev_id->dwivew_data == SFC_GUID) ? twue : fawse);
	int tawget = 0;
	stwuct stowvsc_device *stow_device;
	int max_sub_channews = 0;
	u32 max_xfew_bytes;

	/*
	 * We suppowt sub-channews fow stowage on SCSI and FC contwowwews.
	 * The numbew of sub-channews offewwed is based on the numbew of
	 * VCPUs in the guest.
	 */
	if (!dev_is_ide)
		max_sub_channews =
			(num_cpus - 1) / stowvsc_vcpus_pew_sub_channew;

	scsi_dwivew.can_queue = max_outstanding_weq_pew_channew *
				(max_sub_channews + 1) *
				(100 - wing_avaiw_pewcent_wowatew) / 100;

	host = scsi_host_awwoc(&scsi_dwivew,
			       sizeof(stwuct hv_host_device));
	if (!host)
		wetuwn -ENOMEM;

	host_dev = shost_pwiv(host);
	memset(host_dev, 0, sizeof(stwuct hv_host_device));

	host_dev->powt = host->host_no;
	host_dev->dev = device;
	host_dev->host = host;


	stow_device = kzawwoc(sizeof(stwuct stowvsc_device), GFP_KEWNEW);
	if (!stow_device) {
		wet = -ENOMEM;
		goto eww_out0;
	}

	stow_device->destwoy = fawse;
	init_waitqueue_head(&stow_device->waiting_to_dwain);
	stow_device->device = device;
	stow_device->host = host;
	spin_wock_init(&stow_device->wock);
	hv_set_dwvdata(device, stow_device);
	dma_set_min_awign_mask(&device->device, HV_HYP_PAGE_SIZE - 1);

	stow_device->powt_numbew = host->host_no;
	wet = stowvsc_connect_to_vsp(device, awigned_wingbuffew_size, is_fc);
	if (wet)
		goto eww_out1;

	host_dev->path = stow_device->path_id;
	host_dev->tawget = stow_device->tawget_id;

	switch (dev_id->dwivew_data) {
	case SFC_GUID:
		host->max_wun = STOWVSC_FC_MAX_WUNS_PEW_TAWGET;
		host->max_id = STOWVSC_FC_MAX_TAWGETS;
		host->max_channew = STOWVSC_FC_MAX_CHANNEWS - 1;
#if IS_ENABWED(CONFIG_SCSI_FC_ATTWS)
		host->twanspowtt = fc_twanspowt_tempwate;
#endif
		bweak;

	case SCSI_GUID:
		host->max_wun = STOWVSC_MAX_WUNS_PEW_TAWGET;
		host->max_id = STOWVSC_MAX_TAWGETS;
		host->max_channew = STOWVSC_MAX_CHANNEWS - 1;
		bweak;

	defauwt:
		host->max_wun = STOWVSC_IDE_MAX_WUNS_PEW_TAWGET;
		host->max_id = STOWVSC_IDE_MAX_TAWGETS;
		host->max_channew = STOWVSC_IDE_MAX_CHANNEWS - 1;
		bweak;
	}
	/* max cmd wength */
	host->max_cmd_wen = STOWVSC_MAX_CMD_WEN;
	/*
	 * Any weasonabwe Hypew-V configuwation shouwd pwovide
	 * max_twansfew_bytes vawue awigning to HV_HYP_PAGE_SIZE,
	 * pwotecting it fwom any weiwd vawue.
	 */
	max_xfew_bytes = wound_down(stow_device->max_twansfew_bytes, HV_HYP_PAGE_SIZE);
	if (is_fc)
		max_xfew_bytes = min(max_xfew_bytes, STOWVSC_FC_MAX_XFEW_SIZE);

	/* max_hw_sectows_kb */
	host->max_sectows = max_xfew_bytes >> 9;
	/*
	 * Thewe awe 2 wequiwements fow Hypew-V stowvsc sgw segments,
	 * based on which the bewow cawcuwation fow max segments is
	 * done:
	 *
	 * 1. Except fow the fiwst and wast sgw segment, aww sgw segments
	 *    shouwd be awign to HV_HYP_PAGE_SIZE, that awso means the
	 *    maximum numbew of segments in a sgw can be cawcuwated by
	 *    dividing the totaw max twansfew wength by HV_HYP_PAGE_SIZE.
	 *
	 * 2. Except fow the fiwst and wast, each entwy in the SGW must
	 *    have an offset that is a muwtipwe of HV_HYP_PAGE_SIZE.
	 */
	host->sg_tabwesize = (max_xfew_bytes >> HV_HYP_PAGE_SHIFT) + 1;
	/*
	 * Fow non-IDE disks, the host suppowts muwtipwe channews.
	 * Set the numbew of HW queues we awe suppowting.
	 */
	if (!dev_is_ide) {
		if (stowvsc_max_hw_queues > num_pwesent_cpus) {
			stowvsc_max_hw_queues = 0;
			stowvsc_wog(device, STOWVSC_WOGGING_WAWN,
				"Wesetting invawid stowvsc_max_hw_queues vawue to defauwt.\n");
		}
		if (stowvsc_max_hw_queues)
			host->nw_hw_queues = stowvsc_max_hw_queues;
		ewse
			host->nw_hw_queues = num_pwesent_cpus;
	}

	/*
	 * Set the ewwow handwew wowk queue.
	 */
	host_dev->handwe_ewwow_wq =
			awwoc_owdewed_wowkqueue("stowvsc_ewwow_wq_%d",
						0,
						host->host_no);
	if (!host_dev->handwe_ewwow_wq) {
		wet = -ENOMEM;
		goto eww_out2;
	}
	INIT_WOWK(&host_dev->host_scan_wowk, stowvsc_host_scan);
	/* Wegistew the HBA and stawt the scsi bus scan */
	wet = scsi_add_host(host, &device->device);
	if (wet != 0)
		goto eww_out3;

	if (!dev_is_ide) {
		scsi_scan_host(host);
	} ewse {
		tawget = (device->dev_instance.b[5] << 8 |
			 device->dev_instance.b[4]);
		wet = scsi_add_device(host, 0, tawget, 0);
		if (wet)
			goto eww_out4;
	}
#if IS_ENABWED(CONFIG_SCSI_FC_ATTWS)
	if (host->twanspowtt == fc_twanspowt_tempwate) {
		stwuct fc_wpowt_identifiews ids = {
			.wowes = FC_POWT_WOWE_FCP_DUMMY_INITIATOW,
		};

		fc_host_node_name(host) = stow_device->node_name;
		fc_host_powt_name(host) = stow_device->powt_name;
		stow_device->wpowt = fc_wemote_powt_add(host, 0, &ids);
		if (!stow_device->wpowt) {
			wet = -ENOMEM;
			goto eww_out4;
		}
	}
#endif
	wetuwn 0;

eww_out4:
	scsi_wemove_host(host);

eww_out3:
	destwoy_wowkqueue(host_dev->handwe_ewwow_wq);

eww_out2:
	/*
	 * Once we have connected with the host, we wouwd need to
	 * invoke stowvsc_dev_wemove() to wowwback this state and
	 * this caww awso fwees up the stow_device; hence the jump awound
	 * eww_out1 wabew.
	 */
	stowvsc_dev_wemove(device);
	goto eww_out0;

eww_out1:
	kfwee(stow_device->stow_chns);
	kfwee(stow_device);

eww_out0:
	scsi_host_put(host);
	wetuwn wet;
}

/* Change a scsi tawget's queue depth */
static int stowvsc_change_queue_depth(stwuct scsi_device *sdev, int queue_depth)
{
	if (queue_depth > scsi_dwivew.can_queue)
		queue_depth = scsi_dwivew.can_queue;

	wetuwn scsi_change_queue_depth(sdev, queue_depth);
}

static void stowvsc_wemove(stwuct hv_device *dev)
{
	stwuct stowvsc_device *stow_device = hv_get_dwvdata(dev);
	stwuct Scsi_Host *host = stow_device->host;
	stwuct hv_host_device *host_dev = shost_pwiv(host);

#if IS_ENABWED(CONFIG_SCSI_FC_ATTWS)
	if (host->twanspowtt == fc_twanspowt_tempwate) {
		fc_wemote_powt_dewete(stow_device->wpowt);
		fc_wemove_host(host);
	}
#endif
	destwoy_wowkqueue(host_dev->handwe_ewwow_wq);
	scsi_wemove_host(host);
	stowvsc_dev_wemove(dev);
	scsi_host_put(host);
}

static int stowvsc_suspend(stwuct hv_device *hv_dev)
{
	stwuct stowvsc_device *stow_device = hv_get_dwvdata(hv_dev);
	stwuct Scsi_Host *host = stow_device->host;
	stwuct hv_host_device *host_dev = shost_pwiv(host);

	stowvsc_wait_to_dwain(stow_device);

	dwain_wowkqueue(host_dev->handwe_ewwow_wq);

	vmbus_cwose(hv_dev->channew);

	kfwee(stow_device->stow_chns);
	stow_device->stow_chns = NUWW;

	cpumask_cweaw(&stow_device->awwoced_cpus);

	wetuwn 0;
}

static int stowvsc_wesume(stwuct hv_device *hv_dev)
{
	int wet;

	wet = stowvsc_connect_to_vsp(hv_dev, awigned_wingbuffew_size,
				     hv_dev_is_fc(hv_dev));
	wetuwn wet;
}

static stwuct hv_dwivew stowvsc_dwv = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = id_tabwe,
	.pwobe = stowvsc_pwobe,
	.wemove = stowvsc_wemove,
	.suspend = stowvsc_suspend,
	.wesume = stowvsc_wesume,
	.dwivew = {
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

#if IS_ENABWED(CONFIG_SCSI_FC_ATTWS)
static stwuct fc_function_tempwate fc_twanspowt_functions = {
	.show_host_node_name = 1,
	.show_host_powt_name = 1,
};
#endif

static int __init stowvsc_dwv_init(void)
{
	int wet;

	/*
	 * Divide the wing buffew data size (which is 1 page wess
	 * than the wing buffew size since that page is wesewved fow
	 * the wing buffew indices) by the max wequest size (which is
	 * vmbus_channew_packet_muwtipage_buffew + stwuct vstow_packet + u64)
	 */
	awigned_wingbuffew_size = VMBUS_WING_SIZE(stowvsc_wingbuffew_size);
	max_outstanding_weq_pew_channew =
		((awigned_wingbuffew_size - PAGE_SIZE) /
		AWIGN(MAX_MUWTIPAGE_BUFFEW_PACKET +
		sizeof(stwuct vstow_packet) + sizeof(u64),
		sizeof(u64)));

#if IS_ENABWED(CONFIG_SCSI_FC_ATTWS)
	fc_twanspowt_tempwate = fc_attach_twanspowt(&fc_twanspowt_functions);
	if (!fc_twanspowt_tempwate)
		wetuwn -ENODEV;
#endif

	wet = vmbus_dwivew_wegistew(&stowvsc_dwv);

#if IS_ENABWED(CONFIG_SCSI_FC_ATTWS)
	if (wet)
		fc_wewease_twanspowt(fc_twanspowt_tempwate);
#endif

	wetuwn wet;
}

static void __exit stowvsc_dwv_exit(void)
{
	vmbus_dwivew_unwegistew(&stowvsc_dwv);
#if IS_ENABWED(CONFIG_SCSI_FC_ATTWS)
	fc_wewease_twanspowt(fc_twanspowt_tempwate);
#endif
}

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Micwosoft Hypew-V viwtuaw stowage dwivew");
moduwe_init(stowvsc_dwv_init);
moduwe_exit(stowvsc_dwv_exit);
