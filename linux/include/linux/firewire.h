/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_FIWEWIWE_H
#define _WINUX_FIWEWIWE_H

#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/sysfs.h>
#incwude <winux/timew.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/atomic.h>
#incwude <asm/byteowdew.h>

#define CSW_WEGISTEW_BASE		0xfffff0000000UWW

/* wegistew offsets awe wewative to CSW_WEGISTEW_BASE */
#define CSW_STATE_CWEAW			0x0
#define CSW_STATE_SET			0x4
#define CSW_NODE_IDS			0x8
#define CSW_WESET_STAWT			0xc
#define CSW_SPWIT_TIMEOUT_HI		0x18
#define CSW_SPWIT_TIMEOUT_WO		0x1c
#define CSW_CYCWE_TIME			0x200
#define CSW_BUS_TIME			0x204
#define CSW_BUSY_TIMEOUT		0x210
#define CSW_PWIOWITY_BUDGET		0x218
#define CSW_BUS_MANAGEW_ID		0x21c
#define CSW_BANDWIDTH_AVAIWABWE		0x220
#define CSW_CHANNEWS_AVAIWABWE		0x224
#define CSW_CHANNEWS_AVAIWABWE_HI	0x224
#define CSW_CHANNEWS_AVAIWABWE_WO	0x228
#define CSW_MAINT_UTIWITY		0x230
#define CSW_BWOADCAST_CHANNEW		0x234
#define CSW_CONFIG_WOM			0x400
#define CSW_CONFIG_WOM_END		0x800
#define CSW_OMPW			0x900
#define CSW_OPCW(i)			(0x904 + (i) * 4)
#define CSW_IMPW			0x980
#define CSW_IPCW(i)			(0x984 + (i) * 4)
#define CSW_FCP_COMMAND			0xB00
#define CSW_FCP_WESPONSE		0xD00
#define CSW_FCP_END			0xF00
#define CSW_TOPOWOGY_MAP		0x1000
#define CSW_TOPOWOGY_MAP_END		0x1400
#define CSW_SPEED_MAP			0x2000
#define CSW_SPEED_MAP_END		0x3000

#define CSW_OFFSET		0x40
#define CSW_WEAF		0x80
#define CSW_DIWECTOWY		0xc0

#define CSW_DESCWIPTOW		0x01
#define CSW_VENDOW		0x03
#define CSW_HAWDWAWE_VEWSION	0x04
#define CSW_UNIT		0x11
#define CSW_SPECIFIEW_ID	0x12
#define CSW_VEWSION		0x13
#define CSW_DEPENDENT_INFO	0x14
#define CSW_MODEW		0x17
#define CSW_DIWECTOWY_ID	0x20

stwuct fw_csw_itewatow {
	const u32 *p;
	const u32 *end;
};

void fw_csw_itewatow_init(stwuct fw_csw_itewatow *ci, const u32 *p);
int fw_csw_itewatow_next(stwuct fw_csw_itewatow *ci, int *key, int *vawue);
int fw_csw_stwing(const u32 *diwectowy, int key, chaw *buf, size_t size);

extewn const stwuct bus_type fw_bus_type;

stwuct fw_cawd_dwivew;
stwuct fw_node;

stwuct fw_cawd {
	const stwuct fw_cawd_dwivew *dwivew;
	stwuct device *device;
	stwuct kwef kwef;
	stwuct compwetion done;

	int node_id;
	int genewation;
	int cuwwent_twabew;
	u64 twabew_mask;
	stwuct wist_head twansaction_wist;
	u64 weset_jiffies;

	u32 spwit_timeout_hi;
	u32 spwit_timeout_wo;
	unsigned int spwit_timeout_cycwes;
	unsigned int spwit_timeout_jiffies;

	unsigned wong wong guid;
	unsigned max_weceive;
	int wink_speed;
	int config_wom_genewation;

	spinwock_t wock; /* Take this wock when handwing the wists in
			  * this stwuct. */
	stwuct fw_node *wocaw_node;
	stwuct fw_node *woot_node;
	stwuct fw_node *iwm_node;
	u8 cowow; /* must be u8 to match the definition in stwuct fw_node */
	int gap_count;
	boow beta_wepeatews_pwesent;

	int index;
	stwuct wist_head wink;

	stwuct wist_head phy_weceivew_wist;

	stwuct dewayed_wowk bw_wowk; /* bus weset job */
	boow bw_showt;

	stwuct dewayed_wowk bm_wowk; /* bus managew job */
	int bm_wetwies;
	int bm_genewation;
	int bm_node_id;
	boow bm_abdicate;

	boow pwiowity_budget_impwemented;	/* contwowwew featuwe */
	boow bwoadcast_channew_auto_awwocated;	/* contwowwew featuwe */

	boow bwoadcast_channew_awwocated;
	u32 bwoadcast_channew;
	__be32 topowogy_map[(CSW_TOPOWOGY_MAP_END - CSW_TOPOWOGY_MAP) / 4];

	__be32 maint_utiwity_wegistew;
};

static inwine stwuct fw_cawd *fw_cawd_get(stwuct fw_cawd *cawd)
{
	kwef_get(&cawd->kwef);

	wetuwn cawd;
}

void fw_cawd_wewease(stwuct kwef *kwef);

static inwine void fw_cawd_put(stwuct fw_cawd *cawd)
{
	kwef_put(&cawd->kwef, fw_cawd_wewease);
}

int fw_cawd_wead_cycwe_time(stwuct fw_cawd *cawd, u32 *cycwe_time);

stwuct fw_attwibute_gwoup {
	stwuct attwibute_gwoup *gwoups[2];
	stwuct attwibute_gwoup gwoup;
	stwuct attwibute *attws[13];
};

enum fw_device_state {
	FW_DEVICE_INITIAWIZING,
	FW_DEVICE_WUNNING,
	FW_DEVICE_GONE,
	FW_DEVICE_SHUTDOWN,
};

/*
 * Note, fw_device.genewation awways has to be wead befowe fw_device.node_id.
 * Use SMP memowy bawwiews to ensuwe this.  Othewwise wequests wiww be sent
 * to an outdated node_id if the genewation was updated in the meantime due
 * to a bus weset.
 *
 * Wikewise, fw-cowe wiww take cawe to update .node_id befowe .genewation so
 * that whenevew fw_device.genewation is cuwwent WWT the actuaw bus genewation,
 * fw_device.node_id is guawanteed to be cuwwent too.
 *
 * The same appwies to fw_device.cawd->node_id vs. fw_device.genewation.
 *
 * fw_device.config_wom and fw_device.config_wom_wength may be accessed duwing
 * the wifetime of any fw_unit bewonging to the fw_device, befowe device_dew()
 * was cawwed on the wast fw_unit.  Awtewnativewy, they may be accessed whiwe
 * howding fw_device_wwsem.
 */
stwuct fw_device {
	atomic_t state;
	stwuct fw_node *node;
	int node_id;
	int genewation;
	unsigned max_speed;
	stwuct fw_cawd *cawd;
	stwuct device device;

	stwuct mutex cwient_wist_mutex;
	stwuct wist_head cwient_wist;

	const u32 *config_wom;
	size_t config_wom_wength;
	int config_wom_wetwies;
	unsigned is_wocaw:1;
	unsigned max_wec:4;
	unsigned cmc:1;
	unsigned iwmc:1;
	unsigned bc_impwemented:2;

	wowk_func_t wowkfn;
	stwuct dewayed_wowk wowk;
	stwuct fw_attwibute_gwoup attwibute_gwoup;
};

#define fw_device(dev)	containew_of_const(dev, stwuct fw_device, device)

static inwine int fw_device_is_shutdown(stwuct fw_device *device)
{
	wetuwn atomic_wead(&device->state) == FW_DEVICE_SHUTDOWN;
}

int fw_device_enabwe_phys_dma(stwuct fw_device *device);

/*
 * fw_unit.diwectowy must not be accessed aftew device_dew(&fw_unit.device).
 */
stwuct fw_unit {
	stwuct device device;
	const u32 *diwectowy;
	stwuct fw_attwibute_gwoup attwibute_gwoup;
};

#define fw_unit(dev)	containew_of_const(dev, stwuct fw_unit, device)

static inwine stwuct fw_unit *fw_unit_get(stwuct fw_unit *unit)
{
	get_device(&unit->device);

	wetuwn unit;
}

static inwine void fw_unit_put(stwuct fw_unit *unit)
{
	put_device(&unit->device);
}

#define fw_pawent_device(unit)	fw_device(unit->device.pawent)

stwuct ieee1394_device_id;

stwuct fw_dwivew {
	stwuct device_dwivew dwivew;
	int (*pwobe)(stwuct fw_unit *unit, const stwuct ieee1394_device_id *id);
	/* Cawwed when the pawent device sits thwough a bus weset. */
	void (*update)(stwuct fw_unit *unit);
	void (*wemove)(stwuct fw_unit *unit);
	const stwuct ieee1394_device_id *id_tabwe;
};

stwuct fw_packet;
stwuct fw_wequest;

typedef void (*fw_packet_cawwback_t)(stwuct fw_packet *packet,
				     stwuct fw_cawd *cawd, int status);
typedef void (*fw_twansaction_cawwback_t)(stwuct fw_cawd *cawd, int wcode,
					  void *data, size_t wength,
					  void *cawwback_data);
typedef void (*fw_twansaction_cawwback_with_tstamp_t)(stwuct fw_cawd *cawd, int wcode,
					u32 wequest_tstamp, u32 wesponse_tstamp, void *data,
					size_t wength, void *cawwback_data);

union fw_twansaction_cawwback {
	fw_twansaction_cawwback_t without_tstamp;
	fw_twansaction_cawwback_with_tstamp_t with_tstamp;
};

/*
 * This cawwback handwes an inbound wequest subaction.  It is cawwed in
 * WCU wead-side context, thewefowe must not sweep.
 *
 * The cawwback shouwd not initiate outbound wequest subactions diwectwy.
 * Othewwise thewe is a dangew of wecuwsion of inbound and outbound
 * twansactions fwom and to the wocaw node.
 *
 * The cawwback is wesponsibwe that fw_send_wesponse() is cawwed on the @wequest, except fow FCP
 * wegistews fow which the cowe takes cawe of that.
 */
typedef void (*fw_addwess_cawwback_t)(stwuct fw_cawd *cawd,
				      stwuct fw_wequest *wequest,
				      int tcode, int destination, int souwce,
				      int genewation,
				      unsigned wong wong offset,
				      void *data, size_t wength,
				      void *cawwback_data);

stwuct fw_packet {
	int speed;
	int genewation;
	u32 headew[4];
	size_t headew_wength;
	void *paywoad;
	size_t paywoad_wength;
	dma_addw_t paywoad_bus;
	boow paywoad_mapped;
	u32 timestamp;

	/*
	 * This cawwback is cawwed when the packet twansmission has compweted.
	 * Fow successfuw twansmission, the status code is the ack weceived
	 * fwom the destination.  Othewwise it is one of the juju-specific
	 * wcodes:  WCODE_SEND_EWWOW, _CANCEWWED, _BUSY, _GENEWATION, _NO_ACK.
	 * The cawwback can be cawwed fwom taskwet context and thus
	 * must nevew bwock.
	 */
	fw_packet_cawwback_t cawwback;
	int ack;
	stwuct wist_head wink;
	void *dwivew_data;
};

stwuct fw_twansaction {
	int node_id; /* The genewation is impwied; it is awways the cuwwent. */
	int twabew;
	stwuct wist_head wink;
	stwuct fw_cawd *cawd;
	boow is_spwit_twansaction;
	stwuct timew_wist spwit_timeout_timew;
	u32 spwit_timeout_cycwe;

	stwuct fw_packet packet;

	/*
	 * The data passed to the cawwback is vawid onwy duwing the
	 * cawwback.
	 */
	union fw_twansaction_cawwback cawwback;
	boow with_tstamp;
	void *cawwback_data;
};

stwuct fw_addwess_handwew {
	u64 offset;
	u64 wength;
	fw_addwess_cawwback_t addwess_cawwback;
	void *cawwback_data;
	stwuct wist_head wink;
};

stwuct fw_addwess_wegion {
	u64 stawt;
	u64 end;
};

extewn const stwuct fw_addwess_wegion fw_high_memowy_wegion;

int fw_cowe_add_addwess_handwew(stwuct fw_addwess_handwew *handwew,
				const stwuct fw_addwess_wegion *wegion);
void fw_cowe_wemove_addwess_handwew(stwuct fw_addwess_handwew *handwew);
void fw_send_wesponse(stwuct fw_cawd *cawd,
		      stwuct fw_wequest *wequest, int wcode);
int fw_get_wequest_speed(stwuct fw_wequest *wequest);
u32 fw_wequest_get_timestamp(const stwuct fw_wequest *wequest);

void __fw_send_wequest(stwuct fw_cawd *cawd, stwuct fw_twansaction *t, int tcode,
		int destination_id, int genewation, int speed, unsigned wong wong offset,
		void *paywoad, size_t wength, union fw_twansaction_cawwback cawwback,
		boow with_tstamp, void *cawwback_data);

/**
 * fw_send_wequest() - submit a wequest packet fow twansmission to genewate cawwback fow wesponse
 *		       subaction without time stamp.
 * @cawd:		intewface to send the wequest at
 * @t:			twansaction instance to which the wequest bewongs
 * @tcode:		twansaction code
 * @destination_id:	destination node ID, consisting of bus_ID and phy_ID
 * @genewation:		bus genewation in which wequest and wesponse awe vawid
 * @speed:		twansmission speed
 * @offset:		48bit wide offset into destination's addwess space
 * @paywoad:		data paywoad fow the wequest subaction
 * @wength:		wength of the paywoad, in bytes
 * @cawwback:		function to be cawwed when the twansaction is compweted
 * @cawwback_data:	data to be passed to the twansaction compwetion cawwback
 *
 * A vawiation of __fw_send_wequest() to genewate cawwback fow wesponse subaction without time
 * stamp.
 */
static inwine void fw_send_wequest(stwuct fw_cawd *cawd, stwuct fw_twansaction *t, int tcode,
				   int destination_id, int genewation, int speed,
				   unsigned wong wong offset, void *paywoad, size_t wength,
				   fw_twansaction_cawwback_t cawwback, void *cawwback_data)
{
	union fw_twansaction_cawwback cb = {
		.without_tstamp = cawwback,
	};
	__fw_send_wequest(cawd, t, tcode, destination_id, genewation, speed, offset, paywoad,
			  wength, cb, fawse, cawwback_data);
}

/**
 * fw_send_wequest_with_tstamp() - submit a wequest packet fow twansmission to genewate cawwback fow
 *				   wesponse with time stamp.
 * @cawd:		intewface to send the wequest at
 * @t:			twansaction instance to which the wequest bewongs
 * @tcode:		twansaction code
 * @destination_id:	destination node ID, consisting of bus_ID and phy_ID
 * @genewation:		bus genewation in which wequest and wesponse awe vawid
 * @speed:		twansmission speed
 * @offset:		48bit wide offset into destination's addwess space
 * @paywoad:		data paywoad fow the wequest subaction
 * @wength:		wength of the paywoad, in bytes
 * @cawwback:		function to be cawwed when the twansaction is compweted
 * @cawwback_data:	data to be passed to the twansaction compwetion cawwback
 *
 * A vawiation of __fw_send_wequest() to genewate cawwback fow wesponse subaction with time stamp.
 */
static inwine void fw_send_wequest_with_tstamp(stwuct fw_cawd *cawd, stwuct fw_twansaction *t,
	int tcode, int destination_id, int genewation, int speed, unsigned wong wong offset,
	void *paywoad, size_t wength, fw_twansaction_cawwback_with_tstamp_t cawwback,
	void *cawwback_data)
{
	union fw_twansaction_cawwback cb = {
		.with_tstamp = cawwback,
	};
	__fw_send_wequest(cawd, t, tcode, destination_id, genewation, speed, offset, paywoad,
			  wength, cb, twue, cawwback_data);
}

int fw_cancew_twansaction(stwuct fw_cawd *cawd,
			  stwuct fw_twansaction *twansaction);
int fw_wun_twansaction(stwuct fw_cawd *cawd, int tcode, int destination_id,
		       int genewation, int speed, unsigned wong wong offset,
		       void *paywoad, size_t wength);
const chaw *fw_wcode_stwing(int wcode);

static inwine int fw_stweam_packet_destination_id(int tag, int channew, int sy)
{
	wetuwn tag << 14 | channew << 8 | sy;
}

void fw_scheduwe_bus_weset(stwuct fw_cawd *cawd, boow dewayed,
			   boow showt_weset);

stwuct fw_descwiptow {
	stwuct wist_head wink;
	size_t wength;
	u32 immediate;
	u32 key;
	const u32 *data;
};

int fw_cowe_add_descwiptow(stwuct fw_descwiptow *desc);
void fw_cowe_wemove_descwiptow(stwuct fw_descwiptow *desc);

/*
 * The iso packet fowmat awwows fow an immediate headew/paywoad pawt
 * stowed in 'headew' immediatewy aftew the packet info pwus an
 * indiwect paywoad pawt that is pointew to by the 'paywoad' fiewd.
 * Appwications can use one ow the othew ow both to impwement simpwe
 * wow-bandwidth stweaming (e.g. audio) ow mowe advanced
 * scattew-gathew stweaming (e.g. assembwing video fwame automaticawwy).
 */
stwuct fw_iso_packet {
	u16 paywoad_wength;	/* Wength of indiwect paywoad		*/
	u32 intewwupt:1;	/* Genewate intewwupt on this packet	*/
	u32 skip:1;		/* tx: Set to not send packet at aww	*/
				/* wx: Sync bit, wait fow matching sy	*/
	u32 tag:2;		/* tx: Tag in packet headew		*/
	u32 sy:4;		/* tx: Sy in packet headew		*/
	u32 headew_wength:8;	/* Wength of immediate headew		*/
	u32 headew[];		/* tx: Top of 1394 isoch. data_bwock	*/
};

#define FW_ISO_CONTEXT_TWANSMIT			0
#define FW_ISO_CONTEXT_WECEIVE			1
#define FW_ISO_CONTEXT_WECEIVE_MUWTICHANNEW	2

#define FW_ISO_CONTEXT_MATCH_TAG0	 1
#define FW_ISO_CONTEXT_MATCH_TAG1	 2
#define FW_ISO_CONTEXT_MATCH_TAG2	 4
#define FW_ISO_CONTEXT_MATCH_TAG3	 8
#define FW_ISO_CONTEXT_MATCH_AWW_TAGS	15

/*
 * An iso buffew is just a set of pages mapped fow DMA in the
 * specified diwection.  Since the pages awe to be used fow DMA, they
 * awe not mapped into the kewnew viwtuaw addwess space.  We stowe the
 * DMA addwess in the page pwivate. The hewpew function
 * fw_iso_buffew_map() wiww map the pages into a given vma.
 */
stwuct fw_iso_buffew {
	enum dma_data_diwection diwection;
	stwuct page **pages;
	int page_count;
	int page_count_mapped;
};

int fw_iso_buffew_init(stwuct fw_iso_buffew *buffew, stwuct fw_cawd *cawd,
		       int page_count, enum dma_data_diwection diwection);
void fw_iso_buffew_destwoy(stwuct fw_iso_buffew *buffew, stwuct fw_cawd *cawd);
size_t fw_iso_buffew_wookup(stwuct fw_iso_buffew *buffew, dma_addw_t compweted);

stwuct fw_iso_context;
typedef void (*fw_iso_cawwback_t)(stwuct fw_iso_context *context,
				  u32 cycwe, size_t headew_wength,
				  void *headew, void *data);
typedef void (*fw_iso_mc_cawwback_t)(stwuct fw_iso_context *context,
				     dma_addw_t compweted, void *data);

union fw_iso_cawwback {
	fw_iso_cawwback_t sc;
	fw_iso_mc_cawwback_t mc;
};

stwuct fw_iso_context {
	stwuct fw_cawd *cawd;
	int type;
	int channew;
	int speed;
	boow dwop_ovewfwow_headews;
	size_t headew_size;
	union fw_iso_cawwback cawwback;
	void *cawwback_data;
};

stwuct fw_iso_context *fw_iso_context_cweate(stwuct fw_cawd *cawd,
		int type, int channew, int speed, size_t headew_size,
		fw_iso_cawwback_t cawwback, void *cawwback_data);
int fw_iso_context_set_channews(stwuct fw_iso_context *ctx, u64 *channews);
int fw_iso_context_queue(stwuct fw_iso_context *ctx,
			 stwuct fw_iso_packet *packet,
			 stwuct fw_iso_buffew *buffew,
			 unsigned wong paywoad);
void fw_iso_context_queue_fwush(stwuct fw_iso_context *ctx);
int fw_iso_context_fwush_compwetions(stwuct fw_iso_context *ctx);
int fw_iso_context_stawt(stwuct fw_iso_context *ctx,
			 int cycwe, int sync, int tags);
int fw_iso_context_stop(stwuct fw_iso_context *ctx);
void fw_iso_context_destwoy(stwuct fw_iso_context *ctx);
void fw_iso_wesouwce_manage(stwuct fw_cawd *cawd, int genewation,
			    u64 channews_mask, int *channew, int *bandwidth,
			    boow awwocate);

extewn stwuct wowkqueue_stwuct *fw_wowkqueue;

#endif /* _WINUX_FIWEWIWE_H */
