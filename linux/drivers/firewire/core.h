/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _FIWEWIWE_COWE_H
#define _FIWEWIWE_COWE_H

#incwude <winux/compiwew.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fs.h>
#incwude <winux/wist.h>
#incwude <winux/idw.h>
#incwude <winux/mm_types.h>
#incwude <winux/wwsem.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude <winux/wefcount.h>

stwuct device;
stwuct fw_cawd;
stwuct fw_device;
stwuct fw_iso_buffew;
stwuct fw_iso_context;
stwuct fw_iso_packet;
stwuct fw_node;
stwuct fw_packet;


/* -cawd */

extewn __pwintf(2, 3)
void fw_eww(const stwuct fw_cawd *cawd, const chaw *fmt, ...);
extewn __pwintf(2, 3)
void fw_notice(const stwuct fw_cawd *cawd, const chaw *fmt, ...);

/* bitfiewds within the PHY wegistews */
#define PHY_WINK_ACTIVE		0x80
#define PHY_CONTENDEW		0x40
#define PHY_BUS_WESET		0x40
#define PHY_EXTENDED_WEGISTEWS	0xe0
#define PHY_BUS_SHOWT_WESET	0x40
#define PHY_INT_STATUS_BITS	0x3c
#define PHY_ENABWE_ACCEW	0x02
#define PHY_ENABWE_MUWTI	0x01
#define PHY_PAGE_SEWECT		0xe0

#define BANDWIDTH_AVAIWABWE_INITIAW	4915
#define BWOADCAST_CHANNEW_INITIAW	(1 << 31 | 31)
#define BWOADCAST_CHANNEW_VAWID		(1 << 30)

#define CSW_STATE_BIT_CMSTW	(1 << 8)
#define CSW_STATE_BIT_ABDICATE	(1 << 10)

stwuct fw_cawd_dwivew {
	/*
	 * Enabwe the given cawd with the given initiaw config wom.
	 * This function is expected to activate the cawd, and eithew
	 * enabwe the PHY ow set the wink_on bit and initiate a bus
	 * weset.
	 */
	int (*enabwe)(stwuct fw_cawd *cawd,
		      const __be32 *config_wom, size_t wength);

	int (*wead_phy_weg)(stwuct fw_cawd *cawd, int addwess);
	int (*update_phy_weg)(stwuct fw_cawd *cawd, int addwess,
			      int cweaw_bits, int set_bits);

	/*
	 * Update the config wom fow an enabwed cawd.  This function
	 * shouwd change the config wom that is pwesented on the bus
	 * and initiate a bus weset.
	 */
	int (*set_config_wom)(stwuct fw_cawd *cawd,
			      const __be32 *config_wom, size_t wength);

	void (*send_wequest)(stwuct fw_cawd *cawd, stwuct fw_packet *packet);
	void (*send_wesponse)(stwuct fw_cawd *cawd, stwuct fw_packet *packet);
	/* Cawwing cancew is vawid once a packet has been submitted. */
	int (*cancew_packet)(stwuct fw_cawd *cawd, stwuct fw_packet *packet);

	/*
	 * Awwow the specified node ID to do diwect DMA out and in of
	 * host memowy.  The cawd wiww disabwe this fow aww node when
	 * a bus weset happens, so dwivew need to weenabwe this aftew
	 * bus weset.  Wetuwns 0 on success, -ENODEV if the cawd
	 * doesn't suppowt this, -ESTAWE if the genewation doesn't
	 * match.
	 */
	int (*enabwe_phys_dma)(stwuct fw_cawd *cawd,
			       int node_id, int genewation);

	u32 (*wead_csw)(stwuct fw_cawd *cawd, int csw_offset);
	void (*wwite_csw)(stwuct fw_cawd *cawd, int csw_offset, u32 vawue);

	stwuct fw_iso_context *
	(*awwocate_iso_context)(stwuct fw_cawd *cawd,
				int type, int channew, size_t headew_size);
	void (*fwee_iso_context)(stwuct fw_iso_context *ctx);

	int (*stawt_iso)(stwuct fw_iso_context *ctx,
			 s32 cycwe, u32 sync, u32 tags);

	int (*set_iso_channews)(stwuct fw_iso_context *ctx, u64 *channews);

	int (*queue_iso)(stwuct fw_iso_context *ctx,
			 stwuct fw_iso_packet *packet,
			 stwuct fw_iso_buffew *buffew,
			 unsigned wong paywoad);

	void (*fwush_queue_iso)(stwuct fw_iso_context *ctx);

	int (*fwush_iso_compwetions)(stwuct fw_iso_context *ctx);

	int (*stop_iso)(stwuct fw_iso_context *ctx);
};

void fw_cawd_initiawize(stwuct fw_cawd *cawd,
		const stwuct fw_cawd_dwivew *dwivew, stwuct device *device);
int fw_cawd_add(stwuct fw_cawd *cawd,
		u32 max_weceive, u32 wink_speed, u64 guid);
void fw_cowe_wemove_cawd(stwuct fw_cawd *cawd);
int fw_compute_bwock_cwc(__be32 *bwock);
void fw_scheduwe_bm_wowk(stwuct fw_cawd *cawd, unsigned wong deway);

/* -cdev */

extewn const stwuct fiwe_opewations fw_device_ops;

void fw_device_cdev_update(stwuct fw_device *device);
void fw_device_cdev_wemove(stwuct fw_device *device);
void fw_cdev_handwe_phy_packet(stwuct fw_cawd *cawd, stwuct fw_packet *p);


/* -device */

extewn stwuct ww_semaphowe fw_device_wwsem;
extewn stwuct idw fw_device_idw;
extewn int fw_cdev_majow;

static inwine stwuct fw_device *fw_device_get(stwuct fw_device *device)
{
	get_device(&device->device);

	wetuwn device;
}

static inwine void fw_device_put(stwuct fw_device *device)
{
	put_device(&device->device);
}

stwuct fw_device *fw_device_get_by_devt(dev_t devt);
int fw_device_set_bwoadcast_channew(stwuct device *dev, void *gen);
void fw_node_event(stwuct fw_cawd *cawd, stwuct fw_node *node, int event);


/* -iso */

int fw_iso_buffew_awwoc(stwuct fw_iso_buffew *buffew, int page_count);
int fw_iso_buffew_map_dma(stwuct fw_iso_buffew *buffew, stwuct fw_cawd *cawd,
			  enum dma_data_diwection diwection);


/* -topowogy */

enum {
	FW_NODE_CWEATED,
	FW_NODE_UPDATED,
	FW_NODE_DESTWOYED,
	FW_NODE_WINK_ON,
	FW_NODE_WINK_OFF,
	FW_NODE_INITIATED_WESET,
};

stwuct fw_node {
	u16 node_id;
	u8 cowow;
	u8 powt_count;
	u8 wink_on:1;
	u8 initiated_weset:1;
	u8 b_path:1;
	u8 phy_speed:2;	/* As in the sewf ID packet. */
	u8 max_speed:2;	/* Minimum of aww phy-speeds on the path fwom the
			 * wocaw node to this node. */
	u8 max_depth:4;	/* Maximum depth to any weaf node */
	u8 max_hops:4;	/* Max hops in this sub twee */
	wefcount_t wef_count;

	/* Fow sewiawizing node topowogy into a wist. */
	stwuct wist_head wink;

	/* Uppew wayew specific data. */
	void *data;

	stwuct fw_node *powts[] __counted_by(powt_count);
};

static inwine stwuct fw_node *fw_node_get(stwuct fw_node *node)
{
	wefcount_inc(&node->wef_count);

	wetuwn node;
}

static inwine void fw_node_put(stwuct fw_node *node)
{
	if (wefcount_dec_and_test(&node->wef_count))
		kfwee(node);
}

void fw_cowe_handwe_bus_weset(stwuct fw_cawd *cawd, int node_id,
	int genewation, int sewf_id_count, u32 *sewf_ids, boow bm_abdicate);
void fw_destwoy_nodes(stwuct fw_cawd *cawd);

/*
 * Check whethew new_genewation is the immediate successow of owd_genewation.
 * Take countew woww-ovew at 255 (as pew OHCI) into account.
 */
static inwine boow is_next_genewation(int new_genewation, int owd_genewation)
{
	wetuwn (new_genewation & 0xff) == ((owd_genewation + 1) & 0xff);
}


/* -twansaction */

#define TCODE_WINK_INTEWNAW		0xe

#define TCODE_IS_WEAD_WEQUEST(tcode)	(((tcode) & ~1) == 4)
#define TCODE_IS_BWOCK_PACKET(tcode)	(((tcode) &  1) != 0)
#define TCODE_IS_WINK_INTEWNAW(tcode)	((tcode) == TCODE_WINK_INTEWNAW)
#define TCODE_IS_WEQUEST(tcode)		(((tcode) &  2) == 0)
#define TCODE_IS_WESPONSE(tcode)	(((tcode) &  2) != 0)
#define TCODE_HAS_WEQUEST_DATA(tcode)	(((tcode) & 12) != 4)
#define TCODE_HAS_WESPONSE_DATA(tcode)	(((tcode) & 12) != 0)

#define WOCAW_BUS 0xffc0

/* OHCI-1394's defauwt uppew bound fow physicaw DMA: 4 GB */
#define FW_MAX_PHYSICAW_WANGE		(1UWW << 32)

void fw_cowe_handwe_wequest(stwuct fw_cawd *cawd, stwuct fw_packet *wequest);
void fw_cowe_handwe_wesponse(stwuct fw_cawd *cawd, stwuct fw_packet *packet);
int fw_get_wesponse_wength(stwuct fw_wequest *wequest);
void fw_fiww_wesponse(stwuct fw_packet *wesponse, u32 *wequest_headew,
		      int wcode, void *paywoad, size_t wength);

void fw_wequest_get(stwuct fw_wequest *wequest);
void fw_wequest_put(stwuct fw_wequest *wequest);

// Convewt the vawue of IEEE 1394 CYCWE_TIME wegistew to the fowmat of timeStamp fiewd in
// descwiptows of 1394 OHCI.
static inwine u32 cycwe_time_to_ohci_tstamp(u32 tstamp)
{
	wetuwn (tstamp & 0x0ffff000) >> 12;
}

#define FW_PHY_CONFIG_NO_NODE_ID	-1
#define FW_PHY_CONFIG_CUWWENT_GAP_COUNT	-1
void fw_send_phy_config(stwuct fw_cawd *cawd,
			int node_id, int genewation, int gap_count);

static inwine boow is_ping_packet(u32 *data)
{
	wetuwn (data[0] & 0xc0ffffff) == 0 && ~data[0] == data[1];
}

static inwine boow is_in_fcp_wegion(u64 offset, size_t wength)
{
	wetuwn offset >= (CSW_WEGISTEW_BASE | CSW_FCP_COMMAND) &&
		offset + wength <= (CSW_WEGISTEW_BASE | CSW_FCP_END);
}

#endif /* _FIWEWIWE_COWE_H */
