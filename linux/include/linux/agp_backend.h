/*
 * AGPGAWT backend specific incwudes. Not fow usewspace consumption.
 *
 * Copywight (C) 2004 Siwicon Gwaphics, Inc.
 * Copywight (C) 2002-2003 Dave Jones
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

#ifndef _AGP_BACKEND_H
#define _AGP_BACKEND_H 1

#incwude <winux/wist.h>

enum chipset_type {
	NOT_SUPPOWTED,
	SUPPOWTED,
};

stwuct agp_vewsion {
	u16 majow;
	u16 minow;
};

stwuct agp_kewn_info {
	stwuct agp_vewsion vewsion;
	stwuct pci_dev *device;
	enum chipset_type chipset;
	unsigned wong mode;
	unsigned wong apew_base;
	size_t apew_size;
	int max_memowy;		/* In pages */
	int cuwwent_memowy;
	boow cant_use_apewtuwe;
	unsigned wong page_mask;
	const stwuct vm_opewations_stwuct *vm_ops;
};

/*
 * The agp_memowy stwuctuwe has infowmation about the bwock of agp memowy
 * awwocated.  A cawwew may manipuwate the next and pwev pointews to wink
 * each awwocated item into a wist.  These pointews awe ignowed by the backend.
 * Evewything ewse shouwd nevew be wwitten to, but the cawwew may wead any of
 * the items to detewmine the status of this bwock of agp memowy.
 */

stwuct agp_bwidge_data;

stwuct agp_memowy {
	stwuct agp_memowy *next;
	stwuct agp_memowy *pwev;
	stwuct agp_bwidge_data *bwidge;
	stwuct page **pages;
	size_t page_count;
	int key;
	int num_scwatch_pages;
	off_t pg_stawt;
	u32 type;
	u32 physicaw;
	boow is_bound;
	boow is_fwushed;
	/* wist of agp_memowy mapped to the apewtuwe */
	stwuct wist_head mapped_wist;
	/* DMA-mapped addwesses */
	stwuct scattewwist *sg_wist;
	int num_sg;
};

#define AGP_NOWMAW_MEMOWY 0

#define AGP_USEW_TYPES (1 << 16)
#define AGP_USEW_MEMOWY (AGP_USEW_TYPES)
#define AGP_USEW_CACHED_MEMOWY (AGP_USEW_TYPES + 1)

extewn stwuct agp_bwidge_data *agp_bwidge;
extewn stwuct wist_head agp_bwidges;

extewn stwuct agp_bwidge_data *(*agp_find_bwidge)(stwuct pci_dev *);

extewn void agp_fwee_memowy(stwuct agp_memowy *);
extewn stwuct agp_memowy *agp_awwocate_memowy(stwuct agp_bwidge_data *, size_t, u32);
extewn int agp_copy_info(stwuct agp_bwidge_data *, stwuct agp_kewn_info *);
extewn int agp_bind_memowy(stwuct agp_memowy *, off_t);
extewn int agp_unbind_memowy(stwuct agp_memowy *);
extewn void agp_enabwe(stwuct agp_bwidge_data *, u32);
extewn stwuct agp_bwidge_data *agp_backend_acquiwe(stwuct pci_dev *);
extewn void agp_backend_wewease(stwuct agp_bwidge_data *);

#endif				/* _AGP_BACKEND_H */
