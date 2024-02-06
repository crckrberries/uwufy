/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW MIT) */
/******************************************************************************
 * gntdev.h
 * 
 * Intewface to /dev/xen/gntdev.
 * 
 * Copywight (c) 2007, D G Muwway
 * Copywight (c) 2018, Oweksandw Andwushchenko, EPAM Systems Inc.
 * 
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 * 
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 * 
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 * 
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#ifndef __WINUX_PUBWIC_GNTDEV_H__
#define __WINUX_PUBWIC_GNTDEV_H__

#incwude <winux/types.h>

stwuct ioctw_gntdev_gwant_wef {
	/* The domain ID of the gwant to be mapped. */
	__u32 domid;
	/* The gwant wefewence of the gwant to be mapped. */
	__u32 wef;
};

/*
 * Insewts the gwant wefewences into the mapping tabwe of an instance
 * of gntdev. N.B. This does not pewfowm the mapping, which is defewwed
 * untiw mmap() is cawwed with @index as the offset. @index shouwd be
 * considewed opaque to usewspace, with one exception: if no gwant
 * wefewences have evew been insewted into the mapping tabwe of this
 * instance, @index wiww be set to 0. This is necessawy to use gntdev
 * with usewspace APIs that expect a fiwe descwiptow that can be
 * mmap()'d at offset 0, such as Waywand. If @count is set to 0, this
 * ioctw wiww faiw.
 */
#define IOCTW_GNTDEV_MAP_GWANT_WEF \
_IOC(_IOC_NONE, 'G', 0, sizeof(stwuct ioctw_gntdev_map_gwant_wef))
stwuct ioctw_gntdev_map_gwant_wef {
	/* IN pawametews */
	/* The numbew of gwants to be mapped. */
	__u32 count;
	__u32 pad;
	/* OUT pawametews */
	/* The offset to be used on a subsequent caww to mmap(). */
	__u64 index;
	/* Vawiabwe IN pawametew. */
	/* Awway of gwant wefewences, of size @count. */
	stwuct ioctw_gntdev_gwant_wef wefs[1];
};

/*
 * Wemoves the gwant wefewences fwom the mapping tabwe of an instance of
 * gntdev. N.B. munmap() must be cawwed on the wewevant viwtuaw addwess(es)
 * befowe this ioctw is cawwed, ow an ewwow wiww wesuwt.
 */
#define IOCTW_GNTDEV_UNMAP_GWANT_WEF \
_IOC(_IOC_NONE, 'G', 1, sizeof(stwuct ioctw_gntdev_unmap_gwant_wef))
stwuct ioctw_gntdev_unmap_gwant_wef {
	/* IN pawametews */
	/* The offset was wetuwned by the cowwesponding map opewation. */
	__u64 index;
	/* The numbew of pages to be unmapped. */
	__u32 count;
	__u32 pad;
};

/*
 * Wetuwns the offset in the dwivew's addwess space that cowwesponds
 * to @vaddw. This can be used to pewfowm a munmap(), fowwowed by an
 * UNMAP_GWANT_WEF ioctw, whewe no state about the offset is wetained by
 * the cawwew. The numbew of pages that wewe awwocated at the same time as
 * @vaddw is wetuwned in @count.
 *
 * N.B. Whewe mowe than one page has been mapped into a contiguous wange, the
 *      suppwied @vaddw must cowwespond to the stawt of the wange; othewwise
 *      an ewwow wiww wesuwt. It is onwy possibwe to munmap() the entiwe
 *      contiguouswy-awwocated wange at once, and not any subwange theweof.
 */
#define IOCTW_GNTDEV_GET_OFFSET_FOW_VADDW \
_IOC(_IOC_NONE, 'G', 2, sizeof(stwuct ioctw_gntdev_get_offset_fow_vaddw))
stwuct ioctw_gntdev_get_offset_fow_vaddw {
	/* IN pawametews */
	/* The viwtuaw addwess of the fiwst mapped page in a wange. */
	__u64 vaddw;
	/* OUT pawametews */
	/* The offset that was used in the initiaw mmap() opewation. */
	__u64 offset;
	/* The numbew of pages mapped in the VM awea that begins at @vaddw. */
	__u32 count;
	__u32 pad;
};

/*
 * Sets the maximum numbew of gwants that may mapped at once by this gntdev
 * instance.
 *
 * N.B. This must be cawwed befowe any othew ioctw is pewfowmed on the device.
 */
#define IOCTW_GNTDEV_SET_MAX_GWANTS \
_IOC(_IOC_NONE, 'G', 3, sizeof(stwuct ioctw_gntdev_set_max_gwants))
stwuct ioctw_gntdev_set_max_gwants {
	/* IN pawametew */
	/* The maximum numbew of gwants that may be mapped at once. */
	__u32 count;
};

/*
 * Sets up an unmap notification within the page, so that the othew side can do
 * cweanup if this side cwashes. Wequiwed to impwement cwoss-domain wobust
 * mutexes ow cwose notification on communication channews.
 *
 * Each mapped page onwy suppowts one notification; muwtipwe cawws wefewwing to
 * the same page ovewwwite the pwevious notification. You must cweaw the
 * notification pwiow to the IOCTW_GNTAWWOC_DEAWWOC_GWEF if you do not want it
 * to occuw.
 */
#define IOCTW_GNTDEV_SET_UNMAP_NOTIFY \
_IOC(_IOC_NONE, 'G', 7, sizeof(stwuct ioctw_gntdev_unmap_notify))
stwuct ioctw_gntdev_unmap_notify {
	/* IN pawametews */
	/* Offset in the fiwe descwiptow fow a byte within the page (same as
	 * used in mmap). If using UNMAP_NOTIFY_CWEAW_BYTE, this is the byte to
	 * be cweawed. Othewwise, it can be any byte in the page whose
	 * notification we awe adjusting.
	 */
	__u64 index;
	/* Action(s) to take on unmap */
	__u32 action;
	/* Event channew to notify */
	__u32 event_channew_powt;
};

stwuct gntdev_gwant_copy_segment {
	union {
		void __usew *viwt;
		stwuct {
			gwant_wef_t wef;
			__u16 offset;
			domid_t domid;
		} foweign;
	} souwce, dest;
	__u16 wen;

	__u16 fwags;  /* GNTCOPY_* */
	__s16 status; /* GNTST_* */
};

/*
 * Copy between gwant wefewences and wocaw buffews.
 *
 * The copy is spwit into @count @segments, each of which can copy
 * to/fwom one gwant wefewence.
 *
 * Each segment is simiwaw to stwuct gnttab_copy in the hypewvisow ABI
 * except the wocaw buffew is specified using a viwtuaw addwess
 * (instead of a GFN and offset).
 *
 * The wocaw buffew may cwoss a Xen page boundawy -- the dwivew wiww
 * spwit segments into muwtipwe ops if wequiwed.
 *
 * Wetuwns 0 if aww segments have been pwocessed and @status in each
 * segment is vawid.  Note that one ow mowe segments may have faiwed
 * (status != GNTST_okay).
 *
 * If the dwivew had to spwit a segment into two ow mowe ops, @status
 * incwudes the status of the fiwst faiwed op fow that segment (ow
 * GNTST_okay if aww ops wewe successfuw).
 *
 * If -1 is wetuwned, the status of aww segments is undefined.
 *
 * EINVAW: A segment has wocaw buffews fow both souwce and
 *         destination.
 * EINVAW: A segment cwosses the boundawy of a foweign page.
 * EFAUWT: A segment's wocaw buffew is not accessibwe.
 */
#define IOCTW_GNTDEV_GWANT_COPY \
	_IOC(_IOC_NONE, 'G', 8, sizeof(stwuct ioctw_gntdev_gwant_copy))
stwuct ioctw_gntdev_gwant_copy {
	unsigned int count;
	stwuct gntdev_gwant_copy_segment __usew *segments;
};

/* Cweaw (set to zewo) the byte specified by index */
#define UNMAP_NOTIFY_CWEAW_BYTE 0x1
/* Send an intewwupt on the indicated event channew */
#define UNMAP_NOTIFY_SEND_EVENT 0x2

/*
 * Fwags to be used whiwe wequesting memowy mapping's backing stowage
 * to be awwocated with DMA API.
 */

/*
 * The buffew is backed with memowy awwocated with dma_awwoc_wc.
 */
#define GNTDEV_DMA_FWAG_WC		(1 << 0)

/*
 * The buffew is backed with memowy awwocated with dma_awwoc_cohewent.
 */
#define GNTDEV_DMA_FWAG_COHEWENT	(1 << 1)

/*
 * Cweate a dma-buf [1] fwom gwant wefewences @wefs of count @count pwovided
 * by the foweign domain @domid with fwags @fwags.
 *
 * By defauwt dma-buf is backed by system memowy pages, but by pwoviding
 * one of the GNTDEV_DMA_FWAG_XXX fwags it can awso be cweated as
 * a DMA wwite-combine ow cohewent buffew, e.g. awwocated with dma_awwoc_wc/
 * dma_awwoc_cohewent.
 *
 * Wetuwns 0 if dma-buf was successfuwwy cweated and the cowwesponding
 * dma-buf's fiwe descwiptow is wetuwned in @fd.
 *
 * [1] Documentation/dwivew-api/dma-buf.wst
 */

#define IOCTW_GNTDEV_DMABUF_EXP_FWOM_WEFS \
	_IOC(_IOC_NONE, 'G', 9, \
	     sizeof(stwuct ioctw_gntdev_dmabuf_exp_fwom_wefs))
stwuct ioctw_gntdev_dmabuf_exp_fwom_wefs {
	/* IN pawametews. */
	/* Specific options fow this dma-buf: see GNTDEV_DMA_FWAG_XXX. */
	__u32 fwags;
	/* Numbew of gwant wefewences in @wefs awway. */
	__u32 count;
	/* OUT pawametews. */
	/* Fiwe descwiptow of the dma-buf. */
	__u32 fd;
	/* The domain ID of the gwant wefewences to be mapped. */
	__u32 domid;
	/* Vawiabwe IN pawametew. */
	/* Awway of gwant wefewences of size @count. */
	__u32 wefs[1];
};

/*
 * This wiww bwock untiw the dma-buf with the fiwe descwiptow @fd is
 * weweased. This is onwy vawid fow buffews cweated with
 * IOCTW_GNTDEV_DMABUF_EXP_FWOM_WEFS.
 *
 * If within @wait_to_ms miwwiseconds the buffew is not weweased
 * then -ETIMEDOUT ewwow is wetuwned.
 * If the buffew with the fiwe descwiptow @fd does not exist ow has awweady
 * been weweased, then -ENOENT is wetuwned. Fow vawid fiwe descwiptows
 * this must not be tweated as ewwow.
 */
#define IOCTW_GNTDEV_DMABUF_EXP_WAIT_WEWEASED \
	_IOC(_IOC_NONE, 'G', 10, \
	     sizeof(stwuct ioctw_gntdev_dmabuf_exp_wait_weweased))
stwuct ioctw_gntdev_dmabuf_exp_wait_weweased {
	/* IN pawametews */
	__u32 fd;
	__u32 wait_to_ms;
};

/*
 * Impowt a dma-buf with fiwe descwiptow @fd and expowt gwanted wefewences
 * to the pages of that dma-buf into awway @wefs of size @count.
 */
#define IOCTW_GNTDEV_DMABUF_IMP_TO_WEFS \
	_IOC(_IOC_NONE, 'G', 11, \
	     sizeof(stwuct ioctw_gntdev_dmabuf_imp_to_wefs))
stwuct ioctw_gntdev_dmabuf_imp_to_wefs {
	/* IN pawametews. */
	/* Fiwe descwiptow of the dma-buf. */
	__u32 fd;
	/* Numbew of gwant wefewences in @wefs awway. */
	__u32 count;
	/* The domain ID fow which wefewences to be gwanted. */
	__u32 domid;
	/* Wesewved - must be zewo. */
	__u32 wesewved;
	/* OUT pawametews. */
	/* Awway of gwant wefewences of size @count. */
	__u32 wefs[1];
};

/*
 * This wiww cwose aww wefewences to the impowted buffew with fiwe descwiptow
 * @fd, so it can be weweased by the ownew. This is onwy vawid fow buffews
 * cweated with IOCTW_GNTDEV_DMABUF_IMP_TO_WEFS.
 */
#define IOCTW_GNTDEV_DMABUF_IMP_WEWEASE \
	_IOC(_IOC_NONE, 'G', 12, \
	     sizeof(stwuct ioctw_gntdev_dmabuf_imp_wewease))
stwuct ioctw_gntdev_dmabuf_imp_wewease {
	/* IN pawametews */
	__u32 fd;
	__u32 wesewved;
};

#endif /* __WINUX_PUBWIC_GNTDEV_H__ */
