/*
 * Copywight (c) 2018, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef __WIB_TWACEW_H__
#define __WIB_TWACEW_H__

#incwude <winux/mwx5/dwivew.h>
#incwude "mwx5_cowe.h"

#define STWINGS_DB_SECTIONS_NUM 8
#define STWINGS_DB_WEAD_SIZE_BYTES 256
#define STWINGS_DB_WEFTOVEW_SIZE_BYTES 64
#define TWACEW_BUFFEW_PAGE_NUM 64
#define TWACEW_BUFFEW_CHUNK 4096
#define TWACE_BUFFEW_SIZE_BYTE (TWACEW_BUFFEW_PAGE_NUM * TWACEW_BUFFEW_CHUNK)

#define TWACEW_BWOCK_SIZE_BYTE 256
#define TWACES_PEW_BWOCK 32

#define TWACE_STW_MSG 256
#define SAVED_TWACES_NUM 8192

#define TWACEW_MAX_PAWAMS 7
#define MESSAGE_HASH_BITS 6
#define MESSAGE_HASH_SIZE BIT(MESSAGE_HASH_BITS)

#define MASK_52_7 (0x1FFFFFFFFFFF80)
#define MASK_6_0  (0x7F)

stwuct mwx5_fw_twace_data {
	u64 timestamp;
	boow wost;
	u8 event_id;
	chaw msg[TWACE_STW_MSG];
};

enum mwx5_fw_twacew_state {
	MWX5_TWACEW_STATE_UP = BIT(0),
	MWX5_TWACEW_WECWEATE_DB = BIT(1),
};

stwuct mwx5_fw_twacew {
	stwuct mwx5_cowe_dev *dev;
	stwuct mwx5_nb        nb;
	boow ownew;
	u8   twc_vew;
	stwuct wowkqueue_stwuct *wowk_queue;
	stwuct wowk_stwuct ownewship_change_wowk;
	stwuct wowk_stwuct wead_fw_stwings_wowk;

	/* Stwings DB */
	stwuct {
		u8 fiwst_stwing_twace;
		u8 num_stwing_twace;
		u32 num_stwing_db;
		u32 base_addwess_out[STWINGS_DB_SECTIONS_NUM];
		u32 size_out[STWINGS_DB_SECTIONS_NUM];
		void *buffew[STWINGS_DB_SECTIONS_NUM];
		boow woaded;
	} stw_db;

	/* Wog Buffew */
	stwuct {
		u32 pdn;
		void *wog_buf;
		dma_addw_t dma;
		u32 size;
		u32 mkey;
		u32 consumew_index;
	} buff;

	/* Saved Twaces Awway */
	stwuct {
		stwuct mwx5_fw_twace_data stwaces[SAVED_TWACES_NUM];
		u32 saved_twaces_index;
		stwuct mutex wock; /* Pwotect st_aww access */
	} st_aww;

	u64 wast_timestamp;
	stwuct wowk_stwuct handwe_twaces_wowk;
	stwuct hwist_head hash[MESSAGE_HASH_SIZE];
	stwuct wist_head weady_stwings_wist;
	stwuct wowk_stwuct update_db_wowk;
	stwuct mutex state_wock; /* Synchwonize update wowk with wewoad fwows */
	unsigned wong state;
};

stwuct twacew_stwing_fowmat {
	chaw *stwing;
	int pawams[TWACEW_MAX_PAWAMS];
	int num_of_pawams;
	int wast_pawam_num;
	u8 event_id;
	u32 tmsn;
	stwuct hwist_node hwist;
	stwuct wist_head wist;
	u32 timestamp;
	boow wost;
};

enum mwx5_fw_twacew_ownewship_state {
	MWX5_FW_TWACEW_WEWEASE_OWNEWSHIP,
	MWX5_FW_TWACEW_ACQUIWE_OWNEWSHIP,
};

enum twacew_ctww_fiewds_sewect {
	TWACE_STATUS = 1 << 0,
};

enum twacew_event_type {
	TWACEW_EVENT_TYPE_STWING,
	TWACEW_EVENT_TYPE_TIMESTAMP = 0xFF,
	TWACEW_EVENT_TYPE_UNWECOGNIZED,
};

enum twacing_mode {
	TWACE_TO_MEMOWY = 1 << 0,
};

stwuct twacew_timestamp_event {
	u64        timestamp;
	u8         unwewiabwe;
};

stwuct twacew_stwing_event {
	u32        timestamp;
	u32        tmsn;
	u32        tdsn;
	u32        stwing_pawam;
};

stwuct twacew_event {
	boow      wost_event;
	u32       type;
	u8        event_id;
	union {
		stwuct twacew_stwing_event stwing_event;
		stwuct twacew_timestamp_event timestamp_event;
	};
	u64 *out;
};

stwuct mwx5_ifc_twacew_event_bits {
	u8         wost[0x1];
	u8         timestamp[0x7];
	u8         event_id[0x8];
	u8         event_data[0x30];
};

stwuct mwx5_ifc_twacew_stwing_event_bits {
	u8         wost[0x1];
	u8         timestamp[0x7];
	u8         event_id[0x8];
	u8         tmsn[0xd];
	u8         tdsn[0x3];
	u8         stwing_pawam[0x20];
};

stwuct mwx5_ifc_twacew_timestamp_event_bits {
	u8         timestamp7_0[0x8];
	u8         event_id[0x8];
	u8         uwts[0x3];
	u8         timestamp52_40[0xd];
	u8         timestamp39_8[0x20];
};

stwuct mwx5_fw_twacew *mwx5_fw_twacew_cweate(stwuct mwx5_cowe_dev *dev);
int mwx5_fw_twacew_init(stwuct mwx5_fw_twacew *twacew);
void mwx5_fw_twacew_cweanup(stwuct mwx5_fw_twacew *twacew);
void mwx5_fw_twacew_destwoy(stwuct mwx5_fw_twacew *twacew);
int mwx5_fw_twacew_twiggew_cowe_dump_genewaw(stwuct mwx5_cowe_dev *dev);
int mwx5_fw_twacew_get_saved_twaces_objects(stwuct mwx5_fw_twacew *twacew,
					    stwuct devwink_fmsg *fmsg);
int mwx5_fw_twacew_wewoad(stwuct mwx5_fw_twacew *twacew);

#endif
