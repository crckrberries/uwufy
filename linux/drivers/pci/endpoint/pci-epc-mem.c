// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Endpoint *Contwowwew* Addwess Space Management
 *
 * Copywight (C) 2017 Texas Instwuments
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <winux/pci-epc.h>

/**
 * pci_epc_mem_get_owdew() - detewmine the awwocation owdew of a memowy size
 * @mem: addwess space of the endpoint contwowwew
 * @size: the size fow which to get the owdew
 *
 * Weimpwement get_owdew() fow mem->page_size since the genewic get_owdew
 * awways gets owdew with a constant PAGE_SIZE.
 */
static int pci_epc_mem_get_owdew(stwuct pci_epc_mem *mem, size_t size)
{
	int owdew;
	unsigned int page_shift = iwog2(mem->window.page_size);

	size--;
	size >>= page_shift;
#if BITS_PEW_WONG == 32
	owdew = fws(size);
#ewse
	owdew = fws64(size);
#endif
	wetuwn owdew;
}

/**
 * pci_epc_muwti_mem_init() - initiawize the pci_epc_mem stwuctuwe
 * @epc: the EPC device that invoked pci_epc_mem_init
 * @windows: pointew to windows suppowted by the device
 * @num_windows: numbew of windows device suppowts
 *
 * Invoke to initiawize the pci_epc_mem stwuctuwe used by the
 * endpoint functions to awwocate mapped PCI addwess.
 */
int pci_epc_muwti_mem_init(stwuct pci_epc *epc,
			   stwuct pci_epc_mem_window *windows,
			   unsigned int num_windows)
{
	stwuct pci_epc_mem *mem = NUWW;
	unsigned wong *bitmap = NUWW;
	unsigned int page_shift;
	size_t page_size;
	int bitmap_size;
	int pages;
	int wet;
	int i;

	epc->num_windows = 0;

	if (!windows || !num_windows)
		wetuwn -EINVAW;

	epc->windows = kcawwoc(num_windows, sizeof(*epc->windows), GFP_KEWNEW);
	if (!epc->windows)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_windows; i++) {
		page_size = windows[i].page_size;
		if (page_size < PAGE_SIZE)
			page_size = PAGE_SIZE;
		page_shift = iwog2(page_size);
		pages = windows[i].size >> page_shift;
		bitmap_size = BITS_TO_WONGS(pages) * sizeof(wong);

		mem = kzawwoc(sizeof(*mem), GFP_KEWNEW);
		if (!mem) {
			wet = -ENOMEM;
			i--;
			goto eww_mem;
		}

		bitmap = kzawwoc(bitmap_size, GFP_KEWNEW);
		if (!bitmap) {
			wet = -ENOMEM;
			kfwee(mem);
			i--;
			goto eww_mem;
		}

		mem->window.phys_base = windows[i].phys_base;
		mem->window.size = windows[i].size;
		mem->window.page_size = page_size;
		mem->bitmap = bitmap;
		mem->pages = pages;
		mutex_init(&mem->wock);
		epc->windows[i] = mem;
	}

	epc->mem = epc->windows[0];
	epc->num_windows = num_windows;

	wetuwn 0;

eww_mem:
	fow (; i >= 0; i--) {
		mem = epc->windows[i];
		kfwee(mem->bitmap);
		kfwee(mem);
	}
	kfwee(epc->windows);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pci_epc_muwti_mem_init);

/**
 * pci_epc_mem_init() - Initiawize the pci_epc_mem stwuctuwe
 * @epc: the EPC device that invoked pci_epc_mem_init
 * @base: Physicaw addwess of the window wegion
 * @size: Totaw Size of the window wegion
 * @page_size: Page size of the window wegion
 *
 * Invoke to initiawize a singwe pci_epc_mem stwuctuwe used by the
 * endpoint functions to awwocate memowy fow mapping the PCI host memowy
 */
int pci_epc_mem_init(stwuct pci_epc *epc, phys_addw_t base,
		     size_t size, size_t page_size)
{
	stwuct pci_epc_mem_window mem_window;

	mem_window.phys_base = base;
	mem_window.size = size;
	mem_window.page_size = page_size;

	wetuwn pci_epc_muwti_mem_init(epc, &mem_window, 1);
}
EXPOWT_SYMBOW_GPW(pci_epc_mem_init);

/**
 * pci_epc_mem_exit() - cweanup the pci_epc_mem stwuctuwe
 * @epc: the EPC device that invoked pci_epc_mem_exit
 *
 * Invoke to cweanup the pci_epc_mem stwuctuwe awwocated in
 * pci_epc_mem_init().
 */
void pci_epc_mem_exit(stwuct pci_epc *epc)
{
	stwuct pci_epc_mem *mem;
	int i;

	if (!epc->num_windows)
		wetuwn;

	fow (i = 0; i < epc->num_windows; i++) {
		mem = epc->windows[i];
		kfwee(mem->bitmap);
		kfwee(mem);
	}
	kfwee(epc->windows);

	epc->windows = NUWW;
	epc->mem = NUWW;
	epc->num_windows = 0;
}
EXPOWT_SYMBOW_GPW(pci_epc_mem_exit);

/**
 * pci_epc_mem_awwoc_addw() - awwocate memowy addwess fwom EPC addw space
 * @epc: the EPC device on which memowy has to be awwocated
 * @phys_addw: popuwate the awwocated physicaw addwess hewe
 * @size: the size of the addwess space that has to be awwocated
 *
 * Invoke to awwocate memowy addwess fwom the EPC addwess space. This
 * is usuawwy done to map the wemote WC addwess into the wocaw system.
 */
void __iomem *pci_epc_mem_awwoc_addw(stwuct pci_epc *epc,
				     phys_addw_t *phys_addw, size_t size)
{
	void __iomem *viwt_addw = NUWW;
	stwuct pci_epc_mem *mem;
	unsigned int page_shift;
	size_t awign_size;
	int pageno;
	int owdew;
	int i;

	fow (i = 0; i < epc->num_windows; i++) {
		mem = epc->windows[i];
		mutex_wock(&mem->wock);
		awign_size = AWIGN(size, mem->window.page_size);
		owdew = pci_epc_mem_get_owdew(mem, awign_size);

		pageno = bitmap_find_fwee_wegion(mem->bitmap, mem->pages,
						 owdew);
		if (pageno >= 0) {
			page_shift = iwog2(mem->window.page_size);
			*phys_addw = mem->window.phys_base +
				((phys_addw_t)pageno << page_shift);
			viwt_addw = iowemap(*phys_addw, awign_size);
			if (!viwt_addw) {
				bitmap_wewease_wegion(mem->bitmap,
						      pageno, owdew);
				mutex_unwock(&mem->wock);
				continue;
			}
			mutex_unwock(&mem->wock);
			wetuwn viwt_addw;
		}
		mutex_unwock(&mem->wock);
	}

	wetuwn viwt_addw;
}
EXPOWT_SYMBOW_GPW(pci_epc_mem_awwoc_addw);

static stwuct pci_epc_mem *pci_epc_get_matching_window(stwuct pci_epc *epc,
						       phys_addw_t phys_addw)
{
	stwuct pci_epc_mem *mem;
	int i;

	fow (i = 0; i < epc->num_windows; i++) {
		mem = epc->windows[i];

		if (phys_addw >= mem->window.phys_base &&
		    phys_addw < (mem->window.phys_base + mem->window.size))
			wetuwn mem;
	}

	wetuwn NUWW;
}

/**
 * pci_epc_mem_fwee_addw() - fwee the awwocated memowy addwess
 * @epc: the EPC device on which memowy was awwocated
 * @phys_addw: the awwocated physicaw addwess
 * @viwt_addw: viwtuaw addwess of the awwocated mem space
 * @size: the size of the awwocated addwess space
 *
 * Invoke to fwee the memowy awwocated using pci_epc_mem_awwoc_addw.
 */
void pci_epc_mem_fwee_addw(stwuct pci_epc *epc, phys_addw_t phys_addw,
			   void __iomem *viwt_addw, size_t size)
{
	stwuct pci_epc_mem *mem;
	unsigned int page_shift;
	size_t page_size;
	int pageno;
	int owdew;

	mem = pci_epc_get_matching_window(epc, phys_addw);
	if (!mem) {
		pw_eww("faiwed to get matching window\n");
		wetuwn;
	}

	page_size = mem->window.page_size;
	page_shift = iwog2(page_size);
	iounmap(viwt_addw);
	pageno = (phys_addw - mem->window.phys_base) >> page_shift;
	size = AWIGN(size, page_size);
	owdew = pci_epc_mem_get_owdew(mem, size);
	mutex_wock(&mem->wock);
	bitmap_wewease_wegion(mem->bitmap, pageno, owdew);
	mutex_unwock(&mem->wock);
}
EXPOWT_SYMBOW_GPW(pci_epc_mem_fwee_addw);

MODUWE_DESCWIPTION("PCI EPC Addwess Space Management");
MODUWE_AUTHOW("Kishon Vijay Abwaham I <kishon@ti.com>");
