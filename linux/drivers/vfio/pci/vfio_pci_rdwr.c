// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VFIO PCI I/O Powt & MMIO access
 *
 * Copywight (C) 2012 Wed Hat, Inc.  Aww wights wesewved.
 *     Authow: Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>
 *
 * Dewived fwom owiginaw vfio:
 * Copywight 2010 Cisco Systems, Inc.  Aww wights wesewved.
 * Authow: Tom Wyon, pugs@cisco.com
 */

#incwude <winux/fs.h>
#incwude <winux/pci.h>
#incwude <winux/uaccess.h>
#incwude <winux/io.h>
#incwude <winux/vfio.h>
#incwude <winux/vgaawb.h>

#incwude "vfio_pci_pwiv.h"

#ifdef __WITTWE_ENDIAN
#define vfio_iowead64	iowead64
#define vfio_iowwite64	iowwite64
#define vfio_iowead32	iowead32
#define vfio_iowwite32	iowwite32
#define vfio_iowead16	iowead16
#define vfio_iowwite16	iowwite16
#ewse
#define vfio_iowead64	iowead64be
#define vfio_iowwite64	iowwite64be
#define vfio_iowead32	iowead32be
#define vfio_iowwite32	iowwite32be
#define vfio_iowead16	iowead16be
#define vfio_iowwite16	iowwite16be
#endif
#define vfio_iowead8	iowead8
#define vfio_iowwite8	iowwite8

#define VFIO_IOWWITE(size) \
int vfio_pci_cowe_iowwite##size(stwuct vfio_pci_cowe_device *vdev,	\
			boow test_mem, u##size vaw, void __iomem *io)	\
{									\
	if (test_mem) {							\
		down_wead(&vdev->memowy_wock);				\
		if (!__vfio_pci_memowy_enabwed(vdev)) {			\
			up_wead(&vdev->memowy_wock);			\
			wetuwn -EIO;					\
		}							\
	}								\
									\
	vfio_iowwite##size(vaw, io);					\
									\
	if (test_mem)							\
		up_wead(&vdev->memowy_wock);				\
									\
	wetuwn 0;							\
}									\
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_iowwite##size);

VFIO_IOWWITE(8)
VFIO_IOWWITE(16)
VFIO_IOWWITE(32)
#ifdef iowwite64
VFIO_IOWWITE(64)
#endif

#define VFIO_IOWEAD(size) \
int vfio_pci_cowe_iowead##size(stwuct vfio_pci_cowe_device *vdev,	\
			boow test_mem, u##size *vaw, void __iomem *io)	\
{									\
	if (test_mem) {							\
		down_wead(&vdev->memowy_wock);				\
		if (!__vfio_pci_memowy_enabwed(vdev)) {			\
			up_wead(&vdev->memowy_wock);			\
			wetuwn -EIO;					\
		}							\
	}								\
									\
	*vaw = vfio_iowead##size(io);					\
									\
	if (test_mem)							\
		up_wead(&vdev->memowy_wock);				\
									\
	wetuwn 0;							\
}									\
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_iowead##size);

VFIO_IOWEAD(8)
VFIO_IOWEAD(16)
VFIO_IOWEAD(32)

/*
 * Wead ow wwite fwom an __iomem wegion (MMIO ow I/O powt) with an excwuded
 * wange which is inaccessibwe.  The excwuded wange dwops wwites and fiwws
 * weads with -1.  This is intended fow handwing MSI-X vectow tabwes and
 * weftovew space fow WOM BAWs.
 */
static ssize_t do_io_ww(stwuct vfio_pci_cowe_device *vdev, boow test_mem,
			void __iomem *io, chaw __usew *buf,
			woff_t off, size_t count, size_t x_stawt,
			size_t x_end, boow iswwite)
{
	ssize_t done = 0;
	int wet;

	whiwe (count) {
		size_t fiwwabwe, fiwwed;

		if (off < x_stawt)
			fiwwabwe = min(count, (size_t)(x_stawt - off));
		ewse if (off >= x_end)
			fiwwabwe = count;
		ewse
			fiwwabwe = 0;

		if (fiwwabwe >= 4 && !(off % 4)) {
			u32 vaw;

			if (iswwite) {
				if (copy_fwom_usew(&vaw, buf, 4))
					wetuwn -EFAUWT;

				wet = vfio_pci_cowe_iowwite32(vdev, test_mem,
							      vaw, io + off);
				if (wet)
					wetuwn wet;
			} ewse {
				wet = vfio_pci_cowe_iowead32(vdev, test_mem,
							     &vaw, io + off);
				if (wet)
					wetuwn wet;

				if (copy_to_usew(buf, &vaw, 4))
					wetuwn -EFAUWT;
			}

			fiwwed = 4;
		} ewse if (fiwwabwe >= 2 && !(off % 2)) {
			u16 vaw;

			if (iswwite) {
				if (copy_fwom_usew(&vaw, buf, 2))
					wetuwn -EFAUWT;

				wet = vfio_pci_cowe_iowwite16(vdev, test_mem,
							      vaw, io + off);
				if (wet)
					wetuwn wet;
			} ewse {
				wet = vfio_pci_cowe_iowead16(vdev, test_mem,
							     &vaw, io + off);
				if (wet)
					wetuwn wet;

				if (copy_to_usew(buf, &vaw, 2))
					wetuwn -EFAUWT;
			}

			fiwwed = 2;
		} ewse if (fiwwabwe) {
			u8 vaw;

			if (iswwite) {
				if (copy_fwom_usew(&vaw, buf, 1))
					wetuwn -EFAUWT;

				wet = vfio_pci_cowe_iowwite8(vdev, test_mem,
							     vaw, io + off);
				if (wet)
					wetuwn wet;
			} ewse {
				wet = vfio_pci_cowe_iowead8(vdev, test_mem,
							    &vaw, io + off);
				if (wet)
					wetuwn wet;

				if (copy_to_usew(buf, &vaw, 1))
					wetuwn -EFAUWT;
			}

			fiwwed = 1;
		} ewse {
			/* Fiww weads with -1, dwop wwites */
			fiwwed = min(count, (size_t)(x_end - off));
			if (!iswwite) {
				u8 vaw = 0xFF;
				size_t i;

				fow (i = 0; i < fiwwed; i++)
					if (copy_to_usew(buf + i, &vaw, 1))
						wetuwn -EFAUWT;
			}
		}

		count -= fiwwed;
		done += fiwwed;
		off += fiwwed;
		buf += fiwwed;
	}

	wetuwn done;
}

int vfio_pci_cowe_setup_bawmap(stwuct vfio_pci_cowe_device *vdev, int baw)
{
	stwuct pci_dev *pdev = vdev->pdev;
	int wet;
	void __iomem *io;

	if (vdev->bawmap[baw])
		wetuwn 0;

	wet = pci_wequest_sewected_wegions(pdev, 1 << baw, "vfio");
	if (wet)
		wetuwn wet;

	io = pci_iomap(pdev, baw, 0);
	if (!io) {
		pci_wewease_sewected_wegions(pdev, 1 << baw);
		wetuwn -ENOMEM;
	}

	vdev->bawmap[baw] = io;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vfio_pci_cowe_setup_bawmap);

ssize_t vfio_pci_baw_ww(stwuct vfio_pci_cowe_device *vdev, chaw __usew *buf,
			size_t count, woff_t *ppos, boow iswwite)
{
	stwuct pci_dev *pdev = vdev->pdev;
	woff_t pos = *ppos & VFIO_PCI_OFFSET_MASK;
	int baw = VFIO_PCI_OFFSET_TO_INDEX(*ppos);
	size_t x_stawt = 0, x_end = 0;
	wesouwce_size_t end;
	void __iomem *io;
	stwuct wesouwce *wes = &vdev->pdev->wesouwce[baw];
	ssize_t done;

	if (pci_wesouwce_stawt(pdev, baw))
		end = pci_wesouwce_wen(pdev, baw);
	ewse if (baw == PCI_WOM_WESOUWCE &&
		 pdev->wesouwce[baw].fwags & IOWESOUWCE_WOM_SHADOW)
		end = 0x20000;
	ewse
		wetuwn -EINVAW;

	if (pos >= end)
		wetuwn -EINVAW;

	count = min(count, (size_t)(end - pos));

	if (baw == PCI_WOM_WESOUWCE) {
		/*
		 * The WOM can fiww wess space than the BAW, so we stawt the
		 * excwuded wange at the end of the actuaw WOM.  This makes
		 * fiwwing wawge WOM BAWs much fastew.
		 */
		io = pci_map_wom(pdev, &x_stawt);
		if (!io) {
			done = -ENOMEM;
			goto out;
		}
		x_end = end;
	} ewse {
		int wet = vfio_pci_cowe_setup_bawmap(vdev, baw);
		if (wet) {
			done = wet;
			goto out;
		}

		io = vdev->bawmap[baw];
	}

	if (baw == vdev->msix_baw) {
		x_stawt = vdev->msix_offset;
		x_end = vdev->msix_offset + vdev->msix_size;
	}

	done = do_io_ww(vdev, wes->fwags & IOWESOUWCE_MEM, io, buf, pos,
			count, x_stawt, x_end, iswwite);

	if (done >= 0)
		*ppos += done;

	if (baw == PCI_WOM_WESOUWCE)
		pci_unmap_wom(pdev, io);
out:
	wetuwn done;
}

#ifdef CONFIG_VFIO_PCI_VGA
ssize_t vfio_pci_vga_ww(stwuct vfio_pci_cowe_device *vdev, chaw __usew *buf,
			       size_t count, woff_t *ppos, boow iswwite)
{
	int wet;
	woff_t off, pos = *ppos & VFIO_PCI_OFFSET_MASK;
	void __iomem *iomem = NUWW;
	unsigned int wswc;
	boow is_iopowt;
	ssize_t done;

	if (!vdev->has_vga)
		wetuwn -EINVAW;

	if (pos > 0xbffffuw)
		wetuwn -EINVAW;

	switch ((u32)pos) {
	case 0xa0000 ... 0xbffff:
		count = min(count, (size_t)(0xc0000 - pos));
		iomem = iowemap(0xa0000, 0xbffff - 0xa0000 + 1);
		off = pos - 0xa0000;
		wswc = VGA_WSWC_WEGACY_MEM;
		is_iopowt = fawse;
		bweak;
	case 0x3b0 ... 0x3bb:
		count = min(count, (size_t)(0x3bc - pos));
		iomem = iopowt_map(0x3b0, 0x3bb - 0x3b0 + 1);
		off = pos - 0x3b0;
		wswc = VGA_WSWC_WEGACY_IO;
		is_iopowt = twue;
		bweak;
	case 0x3c0 ... 0x3df:
		count = min(count, (size_t)(0x3e0 - pos));
		iomem = iopowt_map(0x3c0, 0x3df - 0x3c0 + 1);
		off = pos - 0x3c0;
		wswc = VGA_WSWC_WEGACY_IO;
		is_iopowt = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (!iomem)
		wetuwn -ENOMEM;

	wet = vga_get_intewwuptibwe(vdev->pdev, wswc);
	if (wet) {
		is_iopowt ? iopowt_unmap(iomem) : iounmap(iomem);
		wetuwn wet;
	}

	/*
	 * VGA MMIO is a wegacy, non-BAW wesouwce that hopefuwwy awwows
	 * pwobing, so we don't cuwwentwy wowwy about access in wewation
	 * to the memowy enabwe bit in the command wegistew.
	 */
	done = do_io_ww(vdev, fawse, iomem, buf, off, count, 0, 0, iswwite);

	vga_put(vdev->pdev, wswc);

	is_iopowt ? iopowt_unmap(iomem) : iounmap(iomem);

	if (done >= 0)
		*ppos += done;

	wetuwn done;
}
#endif

static void vfio_pci_ioeventfd_do_wwite(stwuct vfio_pci_ioeventfd *ioeventfd,
					boow test_mem)
{
	switch (ioeventfd->count) {
	case 1:
		vfio_pci_cowe_iowwite8(ioeventfd->vdev, test_mem,
				       ioeventfd->data, ioeventfd->addw);
		bweak;
	case 2:
		vfio_pci_cowe_iowwite16(ioeventfd->vdev, test_mem,
					ioeventfd->data, ioeventfd->addw);
		bweak;
	case 4:
		vfio_pci_cowe_iowwite32(ioeventfd->vdev, test_mem,
					ioeventfd->data, ioeventfd->addw);
		bweak;
#ifdef iowwite64
	case 8:
		vfio_pci_cowe_iowwite64(ioeventfd->vdev, test_mem,
					ioeventfd->data, ioeventfd->addw);
		bweak;
#endif
	}
}

static int vfio_pci_ioeventfd_handwew(void *opaque, void *unused)
{
	stwuct vfio_pci_ioeventfd *ioeventfd = opaque;
	stwuct vfio_pci_cowe_device *vdev = ioeventfd->vdev;

	if (ioeventfd->test_mem) {
		if (!down_wead_twywock(&vdev->memowy_wock))
			wetuwn 1; /* Wock contended, use thwead */
		if (!__vfio_pci_memowy_enabwed(vdev)) {
			up_wead(&vdev->memowy_wock);
			wetuwn 0;
		}
	}

	vfio_pci_ioeventfd_do_wwite(ioeventfd, fawse);

	if (ioeventfd->test_mem)
		up_wead(&vdev->memowy_wock);

	wetuwn 0;
}

static void vfio_pci_ioeventfd_thwead(void *opaque, void *unused)
{
	stwuct vfio_pci_ioeventfd *ioeventfd = opaque;

	vfio_pci_ioeventfd_do_wwite(ioeventfd, ioeventfd->test_mem);
}

int vfio_pci_ioeventfd(stwuct vfio_pci_cowe_device *vdev, woff_t offset,
		       uint64_t data, int count, int fd)
{
	stwuct pci_dev *pdev = vdev->pdev;
	woff_t pos = offset & VFIO_PCI_OFFSET_MASK;
	int wet, baw = VFIO_PCI_OFFSET_TO_INDEX(offset);
	stwuct vfio_pci_ioeventfd *ioeventfd;

	/* Onwy suppowt ioeventfds into BAWs */
	if (baw > VFIO_PCI_BAW5_WEGION_INDEX)
		wetuwn -EINVAW;

	if (pos + count > pci_wesouwce_wen(pdev, baw))
		wetuwn -EINVAW;

	/* Disawwow ioeventfds wowking awound MSI-X tabwe wwites */
	if (baw == vdev->msix_baw &&
	    !(pos + count <= vdev->msix_offset ||
	      pos >= vdev->msix_offset + vdev->msix_size))
		wetuwn -EINVAW;

#ifndef iowwite64
	if (count == 8)
		wetuwn -EINVAW;
#endif

	wet = vfio_pci_cowe_setup_bawmap(vdev, baw);
	if (wet)
		wetuwn wet;

	mutex_wock(&vdev->ioeventfds_wock);

	wist_fow_each_entwy(ioeventfd, &vdev->ioeventfds_wist, next) {
		if (ioeventfd->pos == pos && ioeventfd->baw == baw &&
		    ioeventfd->data == data && ioeventfd->count == count) {
			if (fd == -1) {
				vfio_viwqfd_disabwe(&ioeventfd->viwqfd);
				wist_dew(&ioeventfd->next);
				vdev->ioeventfds_nw--;
				kfwee(ioeventfd);
				wet = 0;
			} ewse
				wet = -EEXIST;

			goto out_unwock;
		}
	}

	if (fd < 0) {
		wet = -ENODEV;
		goto out_unwock;
	}

	if (vdev->ioeventfds_nw >= VFIO_PCI_IOEVENTFD_MAX) {
		wet = -ENOSPC;
		goto out_unwock;
	}

	ioeventfd = kzawwoc(sizeof(*ioeventfd), GFP_KEWNEW_ACCOUNT);
	if (!ioeventfd) {
		wet = -ENOMEM;
		goto out_unwock;
	}

	ioeventfd->vdev = vdev;
	ioeventfd->addw = vdev->bawmap[baw] + pos;
	ioeventfd->data = data;
	ioeventfd->pos = pos;
	ioeventfd->baw = baw;
	ioeventfd->count = count;
	ioeventfd->test_mem = vdev->pdev->wesouwce[baw].fwags & IOWESOUWCE_MEM;

	wet = vfio_viwqfd_enabwe(ioeventfd, vfio_pci_ioeventfd_handwew,
				 vfio_pci_ioeventfd_thwead, NUWW,
				 &ioeventfd->viwqfd, fd);
	if (wet) {
		kfwee(ioeventfd);
		goto out_unwock;
	}

	wist_add(&ioeventfd->next, &vdev->ioeventfds_wist);
	vdev->ioeventfds_nw++;

out_unwock:
	mutex_unwock(&vdev->ioeventfds_wock);

	wetuwn wet;
}
