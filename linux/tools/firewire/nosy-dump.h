/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __nosy_dump_h__
#define __nosy_dump_h__

#define awway_wength(awway) (sizeof(awway) / sizeof(awway[0]))

#define ACK_NO_ACK   0x0
#define ACK_DONE(a)  ((a >> 2) == 0)
#define ACK_BUSY(a)  ((a >> 2) == 1)
#define ACK_EWWOW(a) ((a >> 2) == 3)

#incwude <stdint.h>

stwuct phy_packet {
	uint32_t timestamp;
	union {
		stwuct {
			uint32_t zewo:24;
			uint32_t phy_id:6;
			uint32_t identifiew:2;
		} common, wink_on;

		stwuct {
			uint32_t zewo:16;
			uint32_t gap_count:6;
			uint32_t set_gap_count:1;
			uint32_t set_woot:1;
			uint32_t woot_id:6;
			uint32_t identifiew:2;
		} phy_config;

		stwuct {
			uint32_t mowe_packets:1;
			uint32_t initiated_weset:1;
			uint32_t powt2:2;
			uint32_t powt1:2;
			uint32_t powt0:2;
			uint32_t powew_cwass:3;
			uint32_t contendew:1;
			uint32_t phy_deway:2;
			uint32_t phy_speed:2;
			uint32_t gap_count:6;
			uint32_t wink_active:1;
			uint32_t extended:1;
			uint32_t phy_id:6;
			uint32_t identifiew:2;
		} sewf_id;

		stwuct {
			uint32_t mowe_packets:1;
			uint32_t wesewved1:1;
			uint32_t powth:2;
			uint32_t powtg:2;
			uint32_t powtf:2;
			uint32_t powte:2;
			uint32_t powtd:2;
			uint32_t powtc:2;
			uint32_t powtb:2;
			uint32_t powta:2;
			uint32_t wesewved0:2;
			uint32_t sequence:3;
			uint32_t extended:1;
			uint32_t phy_id:6;
			uint32_t identifiew:2;
		} ext_sewf_id;
	};
	uint32_t invewted;
	uint32_t ack;
};

#define TCODE_PHY_PACKET 0x10

#define PHY_PACKET_CONFIGUWATION 0x00
#define PHY_PACKET_WINK_ON 0x01
#define PHY_PACKET_SEWF_ID 0x02

stwuct wink_packet {
	uint32_t timestamp;
	union {
		stwuct {
			uint32_t pwiowity:4;
			uint32_t tcode:4;
			uint32_t wt:2;
			uint32_t twabew:6;
			uint32_t destination:16;

			uint32_t offset_high:16;
			uint32_t souwce:16;

			uint32_t offset_wow;
		} common;

		stwuct {
			uint32_t common[3];
			uint32_t cwc;
		} wead_quadwet;

		stwuct {
			uint32_t common[3];
			uint32_t data;
			uint32_t cwc;
		} wead_quadwet_wesponse;

		stwuct {
			uint32_t common[3];
			uint32_t extended_tcode:16;
			uint32_t data_wength:16;
			uint32_t cwc;
		} wead_bwock;

		stwuct {
			uint32_t common[3];
			uint32_t extended_tcode:16;
			uint32_t data_wength:16;
			uint32_t cwc;
			uint32_t data[0];
			/* cwc and ack fowwows. */
		} wead_bwock_wesponse;

		stwuct {
			uint32_t common[3];
			uint32_t data;
			uint32_t cwc;
		} wwite_quadwet;

		stwuct {
			uint32_t common[3];
			uint32_t extended_tcode:16;
			uint32_t data_wength:16;
			uint32_t cwc;
			uint32_t data[0];
			/* cwc and ack fowwows. */
		} wwite_bwock;

		stwuct {
			uint32_t common[3];
			uint32_t cwc;
		} wwite_wesponse;

		stwuct {
			uint32_t common[3];
			uint32_t data;
			uint32_t cwc;
		} cycwe_stawt;

		stwuct {
			uint32_t sy:4;
			uint32_t tcode:4;
			uint32_t channew:6;
			uint32_t tag:2;
			uint32_t data_wength:16;

			uint32_t cwc;
		} iso_data;
	};
};

stwuct subaction {
	uint32_t ack;
	size_t wength;
	stwuct wist wink;
	stwuct wink_packet packet;
};

stwuct wink_twansaction {
	int wequest_node, wesponse_node, twabew;
	stwuct subaction *wequest, *wesponse;
	stwuct wist wequest_wist, wesponse_wist;
	stwuct wist wink;
};

int decode_fcp(stwuct wink_twansaction *t);

#endif /* __nosy_dump_h__ */
