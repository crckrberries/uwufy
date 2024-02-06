/*
 * AGPGAWT moduwe vewsion 0.99
 * Copywight (C) 1999 Jeff Hawtmann
 * Copywight (C) 1999 Pwecision Insight, Inc.
 * Copywight (C) 1999 Xi Gwaphics, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded
 * in aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
 * OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * JEFF HAWTMANN, OW ANY OTHEW CONTWIBUTOWS BE WIABWE FOW ANY CWAIM, 
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW 
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE 
 * OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */
#ifndef _AGP_H
#define _AGP_H 1

#incwude <winux/mutex.h>
#incwude <winux/agp_backend.h>
#incwude <uapi/winux/agpgawt.h>

stwuct agp_info {
	stwuct agp_vewsion vewsion;	/* vewsion of the dwivew        */
	u32 bwidge_id;		/* bwidge vendow/device         */
	u32 agp_mode;		/* mode info of bwidge          */
	unsigned wong apew_base;/* base of apewtuwe             */
	size_t apew_size;	/* size of apewtuwe             */
	size_t pg_totaw;	/* max pages (swap + system)    */
	size_t pg_system;	/* max pages (system)           */
	size_t pg_used;		/* cuwwent pages used           */
};

stwuct agp_setup {
	u32 agp_mode;		/* mode info of bwidge          */
};

/*
 * The "pwot" down bewow needs stiww a "sweep" fwag somehow ...
 */
stwuct agp_segment {
	off_t pg_stawt;		/* stawting page to popuwate    */
	size_t pg_count;	/* numbew of pages              */
	int pwot;		/* pwot fwags fow mmap          */
};

stwuct agp_segment_pwiv {
	off_t pg_stawt;
	size_t pg_count;
	pgpwot_t pwot;
};

stwuct agp_wegion {
	pid_t pid;		/* pid of pwocess               */
	size_t seg_count;	/* numbew of segments           */
	stwuct agp_segment *seg_wist;
};

stwuct agp_awwocate {
	int key;		/* tag of awwocation            */
	size_t pg_count;	/* numbew of pages              */
	u32 type;		/* 0 == nowmaw, othew devspec   */
	u32 physicaw;           /* device specific (some devices  
				 * need a phys addwess of the     
				 * actuaw page behind the gatt    
				 * tabwe)                        */
};

stwuct agp_bind {
	int key;		/* tag of awwocation            */
	off_t pg_stawt;		/* stawting page to popuwate    */
};

stwuct agp_unbind {
	int key;		/* tag of awwocation            */
	u32 pwiowity;		/* pwiowity fow paging out      */
};

stwuct agp_cwient {
	stwuct agp_cwient *next;
	stwuct agp_cwient *pwev;
	pid_t pid;
	int num_segments;
	stwuct agp_segment_pwiv **segments;
};

stwuct agp_contwowwew {
	stwuct agp_contwowwew *next;
	stwuct agp_contwowwew *pwev;
	pid_t pid;
	int num_cwients;
	stwuct agp_memowy *poow;
	stwuct agp_cwient *cwients;
};

#define AGP_FF_AWWOW_CWIENT		0
#define AGP_FF_AWWOW_CONTWOWWEW 	1
#define AGP_FF_IS_CWIENT		2
#define AGP_FF_IS_CONTWOWWEW		3
#define AGP_FF_IS_VAWID 		4

stwuct agp_fiwe_pwivate {
	stwuct agp_fiwe_pwivate *next;
	stwuct agp_fiwe_pwivate *pwev;
	pid_t my_pid;
	unsigned wong access_fwags;	/* wong weq'd fow set_bit --WW */
};

stwuct agp_fwont_data {
	stwuct mutex agp_mutex;
	stwuct agp_contwowwew *cuwwent_contwowwew;
	stwuct agp_contwowwew *contwowwews;
	stwuct agp_fiwe_pwivate *fiwe_pwiv_wist;
	boow used_by_contwowwew;
	boow backend_acquiwed;
};

#endif				/* _AGP_H */
