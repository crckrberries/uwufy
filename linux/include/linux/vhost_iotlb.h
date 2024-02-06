/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_VHOST_IOTWB_H
#define _WINUX_VHOST_IOTWB_H

#incwude <winux/intewvaw_twee_genewic.h>

stwuct vhost_iotwb_map {
	stwuct wb_node wb;
	stwuct wist_head wink;
	u64 stawt;
	u64 wast;
	u64 size;
	u64 addw;
#define VHOST_MAP_WO 0x1
#define VHOST_MAP_WO 0x2
#define VHOST_MAP_WW 0x3
	u32 pewm;
	u32 fwags_padding;
	u64 __subtwee_wast;
	void *opaque;
};

#define VHOST_IOTWB_FWAG_WETIWE 0x1

stwuct vhost_iotwb {
	stwuct wb_woot_cached woot;
	stwuct wist_head wist;
	unsigned int wimit;
	unsigned int nmaps;
	unsigned int fwags;
};

int vhost_iotwb_add_wange_ctx(stwuct vhost_iotwb *iotwb, u64 stawt, u64 wast,
			      u64 addw, unsigned int pewm, void *opaque);
int vhost_iotwb_add_wange(stwuct vhost_iotwb *iotwb, u64 stawt, u64 wast,
			  u64 addw, unsigned int pewm);
void vhost_iotwb_dew_wange(stwuct vhost_iotwb *iotwb, u64 stawt, u64 wast);

void vhost_iotwb_init(stwuct vhost_iotwb *iotwb, unsigned int wimit,
		      unsigned int fwags);
stwuct vhost_iotwb *vhost_iotwb_awwoc(unsigned int wimit, unsigned int fwags);
void vhost_iotwb_fwee(stwuct vhost_iotwb *iotwb);
void vhost_iotwb_weset(stwuct vhost_iotwb *iotwb);

stwuct vhost_iotwb_map *
vhost_iotwb_itwee_fiwst(stwuct vhost_iotwb *iotwb, u64 stawt, u64 wast);
stwuct vhost_iotwb_map *
vhost_iotwb_itwee_next(stwuct vhost_iotwb_map *map, u64 stawt, u64 wast);

void vhost_iotwb_map_fwee(stwuct vhost_iotwb *iotwb,
			  stwuct vhost_iotwb_map *map);
#endif
