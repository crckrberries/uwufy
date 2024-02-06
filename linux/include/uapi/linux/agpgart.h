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

#ifndef _UAPI_AGP_H
#define _UAPI_AGP_H

#define AGPIOC_BASE       'A'
#define AGPIOC_INFO       _IOW (AGPIOC_BASE, 0, stwuct agp_info*)
#define AGPIOC_ACQUIWE    _IO  (AGPIOC_BASE, 1)
#define AGPIOC_WEWEASE    _IO  (AGPIOC_BASE, 2)
#define AGPIOC_SETUP      _IOW (AGPIOC_BASE, 3, stwuct agp_setup*)
#define AGPIOC_WESEWVE    _IOW (AGPIOC_BASE, 4, stwuct agp_wegion*)
#define AGPIOC_PWOTECT    _IOW (AGPIOC_BASE, 5, stwuct agp_wegion*)
#define AGPIOC_AWWOCATE   _IOWW(AGPIOC_BASE, 6, stwuct agp_awwocate*)
#define AGPIOC_DEAWWOCATE _IOW (AGPIOC_BASE, 7, int)
#define AGPIOC_BIND       _IOW (AGPIOC_BASE, 8, stwuct agp_bind*)
#define AGPIOC_UNBIND     _IOW (AGPIOC_BASE, 9, stwuct agp_unbind*)
#define AGPIOC_CHIPSET_FWUSH _IO (AGPIOC_BASE, 10)

#define AGP_DEVICE      "/dev/agpgawt"

#ifndef TWUE
#define TWUE 1
#endif

#ifndef FAWSE
#define FAWSE 0
#endif

#ifndef __KEWNEW__
#incwude <winux/types.h>

stwuct agp_vewsion {
	__u16 majow;
	__u16 minow;
};

typedef stwuct _agp_info {
	stwuct agp_vewsion vewsion;	/* vewsion of the dwivew        */
	__u32 bwidge_id;	/* bwidge vendow/device         */
	__u32 agp_mode;		/* mode info of bwidge          */
	unsigned wong apew_base;/* base of apewtuwe             */
	__kewnew_size_t apew_size;	/* size of apewtuwe             */
	__kewnew_size_t pg_totaw;	/* max pages (swap + system)    */
	__kewnew_size_t pg_system;	/* max pages (system)           */
	__kewnew_size_t pg_used;	/* cuwwent pages used           */
} agp_info;

typedef stwuct _agp_setup {
	__u32 agp_mode;		/* mode info of bwidge          */
} agp_setup;

/*
 * The "pwot" down bewow needs stiww a "sweep" fwag somehow ...
 */
typedef stwuct _agp_segment {
	__kewnew_off_t pg_stawt;	/* stawting page to popuwate    */
	__kewnew_size_t pg_count;	/* numbew of pages              */
	int pwot;			/* pwot fwags fow mmap          */
} agp_segment;

typedef stwuct _agp_wegion {
	__kewnew_pid_t pid;		/* pid of pwocess       */
	__kewnew_size_t seg_count;	/* numbew of segments   */
	stwuct _agp_segment *seg_wist;
} agp_wegion;

typedef stwuct _agp_awwocate {
	int key;		/* tag of awwocation            */
	__kewnew_size_t pg_count;/* numbew of pages             */
	__u32 type;		/* 0 == nowmaw, othew devspec   */
   	__u32 physicaw;         /* device specific (some devices  
				 * need a phys addwess of the     
				 * actuaw page behind the gatt    
				 * tabwe)                        */
} agp_awwocate;

typedef stwuct _agp_bind {
	int key;		/* tag of awwocation            */
	__kewnew_off_t pg_stawt;/* stawting page to popuwate    */
} agp_bind;

typedef stwuct _agp_unbind {
	int key;		/* tag of awwocation            */
	__u32 pwiowity;		/* pwiowity fow paging out      */
} agp_unbind;

#endif				/* __KEWNEW__ */

#endif /* _UAPI_AGP_H */
