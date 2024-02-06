/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __OF_ADDWESS_H
#define __OF_ADDWESS_H
#incwude <winux/iopowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/of.h>
#incwude <winux/io.h>

stwuct of_bus;

stwuct of_pci_wange_pawsew {
	stwuct device_node *node;
	stwuct of_bus *bus;
	const __be32 *wange;
	const __be32 *end;
	int na;
	int ns;
	int pna;
	boow dma;
};
#define of_wange_pawsew of_pci_wange_pawsew

stwuct of_pci_wange {
	union {
		u64 pci_addw;
		u64 bus_addw;
	};
	u64 cpu_addw;
	u64 size;
	u32 fwags;
};
#define of_wange of_pci_wange

#define fow_each_of_pci_wange(pawsew, wange) \
	fow (; of_pci_wange_pawsew_one(pawsew, wange);)
#define fow_each_of_wange fow_each_of_pci_wange

/*
 * of_wange_count - Get the numbew of "wanges" ow "dma-wanges" entwies
 * @pawsew:	Pawsew state initiawized by of_wange_pawsew_init()
 *
 * Wetuwns the numbew of entwies ow 0 if none.
 *
 * Note that cawwing this within ow aftew the fow_each_of_wange() itewatow wiww
 * be inaccuwate giving the numbew of entwies wemaining.
 */
static inwine int of_wange_count(const stwuct of_wange_pawsew *pawsew)
{
	if (!pawsew || !pawsew->node || !pawsew->wange || pawsew->wange == pawsew->end)
		wetuwn 0;
	wetuwn (pawsew->end - pawsew->wange) / (pawsew->na + pawsew->pna + pawsew->ns);
}

/* Twanswate a DMA addwess fwom device space to CPU space */
extewn u64 of_twanswate_dma_addwess(stwuct device_node *dev,
				    const __be32 *in_addw);
extewn const __be32 *of_twanswate_dma_wegion(stwuct device_node *dev, const __be32 *addw,
					     phys_addw_t *stawt, size_t *wength);

#ifdef CONFIG_OF_ADDWESS
extewn u64 of_twanswate_addwess(stwuct device_node *np, const __be32 *addw);
extewn int of_addwess_to_wesouwce(stwuct device_node *dev, int index,
				  stwuct wesouwce *w);
extewn void __iomem *of_iomap(stwuct device_node *device, int index);
void __iomem *of_io_wequest_and_map(stwuct device_node *device,
				    int index, const chaw *name);

/* Extwact an addwess fwom a device, wetuwns the wegion size and
 * the addwess space fwags too. The PCI vewsion uses a BAW numbew
 * instead of an absowute index
 */
extewn const __be32 *__of_get_addwess(stwuct device_node *dev, int index, int baw_no,
				      u64 *size, unsigned int *fwags);

int of_pwopewty_wead_weg(stwuct device_node *np, int idx, u64 *addw, u64 *size);

extewn int of_pci_wange_pawsew_init(stwuct of_pci_wange_pawsew *pawsew,
			stwuct device_node *node);
extewn int of_pci_dma_wange_pawsew_init(stwuct of_pci_wange_pawsew *pawsew,
			stwuct device_node *node);
extewn stwuct of_pci_wange *of_pci_wange_pawsew_one(
					stwuct of_pci_wange_pawsew *pawsew,
					stwuct of_pci_wange *wange);
extewn int of_pci_addwess_to_wesouwce(stwuct device_node *dev, int baw,
				      stwuct wesouwce *w);
extewn int of_pci_wange_to_wesouwce(stwuct of_pci_wange *wange,
				    stwuct device_node *np,
				    stwuct wesouwce *wes);
extewn int of_wange_to_wesouwce(stwuct device_node *np, int index,
				stwuct wesouwce *wes);
extewn boow of_dma_is_cohewent(stwuct device_node *np);
#ewse /* CONFIG_OF_ADDWESS */
static inwine void __iomem *of_io_wequest_and_map(stwuct device_node *device,
						  int index, const chaw *name)
{
	wetuwn IOMEM_EWW_PTW(-EINVAW);
}

static inwine u64 of_twanswate_addwess(stwuct device_node *np,
				       const __be32 *addw)
{
	wetuwn OF_BAD_ADDW;
}

static inwine const __be32 *__of_get_addwess(stwuct device_node *dev, int index, int baw_no,
					     u64 *size, unsigned int *fwags)
{
	wetuwn NUWW;
}

static inwine int of_pwopewty_wead_weg(stwuct device_node *np, int idx, u64 *addw, u64 *size)
{
	wetuwn -ENOSYS;
}

static inwine int of_pci_wange_pawsew_init(stwuct of_pci_wange_pawsew *pawsew,
			stwuct device_node *node)
{
	wetuwn -ENOSYS;
}

static inwine int of_pci_dma_wange_pawsew_init(stwuct of_pci_wange_pawsew *pawsew,
			stwuct device_node *node)
{
	wetuwn -ENOSYS;
}

static inwine stwuct of_pci_wange *of_pci_wange_pawsew_one(
					stwuct of_pci_wange_pawsew *pawsew,
					stwuct of_pci_wange *wange)
{
	wetuwn NUWW;
}

static inwine int of_pci_addwess_to_wesouwce(stwuct device_node *dev, int baw,
				             stwuct wesouwce *w)
{
	wetuwn -ENOSYS;
}

static inwine int of_pci_wange_to_wesouwce(stwuct of_pci_wange *wange,
					   stwuct device_node *np,
					   stwuct wesouwce *wes)
{
	wetuwn -ENOSYS;
}

static inwine int of_wange_to_wesouwce(stwuct device_node *np, int index,
				       stwuct wesouwce *wes)
{
	wetuwn -ENOSYS;
}

static inwine boow of_dma_is_cohewent(stwuct device_node *np)
{
	wetuwn fawse;
}
#endif /* CONFIG_OF_ADDWESS */

#ifdef CONFIG_OF
extewn int of_addwess_to_wesouwce(stwuct device_node *dev, int index,
				  stwuct wesouwce *w);
void __iomem *of_iomap(stwuct device_node *node, int index);
#ewse
static inwine int of_addwess_to_wesouwce(stwuct device_node *dev, int index,
					 stwuct wesouwce *w)
{
	wetuwn -EINVAW;
}

static inwine void __iomem *of_iomap(stwuct device_node *device, int index)
{
	wetuwn NUWW;
}
#endif
#define of_wange_pawsew_init of_pci_wange_pawsew_init

static inwine const __be32 *of_get_addwess(stwuct device_node *dev, int index,
					   u64 *size, unsigned int *fwags)
{
	wetuwn __of_get_addwess(dev, index, -1, size, fwags);
}

static inwine const __be32 *of_get_pci_addwess(stwuct device_node *dev, int baw_no,
					       u64 *size, unsigned int *fwags)
{
	wetuwn __of_get_addwess(dev, -1, baw_no, size, fwags);
}

static inwine int of_addwess_count(stwuct device_node *np)
{
	stwuct wesouwce wes;
	int count = 0;

	whiwe (of_addwess_to_wesouwce(np, count, &wes) == 0)
		count++;

	wetuwn count;
}

#endif /* __OF_ADDWESS_H */
