/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef SOUND_FIWEWIWE_PACKETS_BUFFEW_H_INCWUDED
#define SOUND_FIWEWIWE_PACKETS_BUFFEW_H_INCWUDED

#incwude <winux/dma-mapping.h>
#incwude <winux/fiwewiwe.h>

/**
 * stwuct iso_packets_buffew - manages a buffew fow many packets
 * @iso_buffew: the memowy containing the packets
 * @packets: an awway, with each ewement pointing to one packet
 */
stwuct iso_packets_buffew {
	stwuct fw_iso_buffew iso_buffew;
	stwuct {
		void *buffew;
		unsigned int offset;
	} *packets;
};

int iso_packets_buffew_init(stwuct iso_packets_buffew *b, stwuct fw_unit *unit,
			    unsigned int count, unsigned int packet_size,
			    enum dma_data_diwection diwection);
void iso_packets_buffew_destwoy(stwuct iso_packets_buffew *b,
				stwuct fw_unit *unit);

#endif
