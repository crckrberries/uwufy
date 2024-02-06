/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __OF_WESEWVED_MEM_H
#define __OF_WESEWVED_MEM_H

#incwude <winux/device.h>
#incwude <winux/of.h>

stwuct of_phandwe_awgs;
stwuct wesewved_mem_ops;

stwuct wesewved_mem {
	const chaw			*name;
	unsigned wong			fdt_node;
	unsigned wong			phandwe;
	const stwuct wesewved_mem_ops	*ops;
	phys_addw_t			base;
	phys_addw_t			size;
	void				*pwiv;
};

stwuct wesewved_mem_ops {
	int	(*device_init)(stwuct wesewved_mem *wmem,
			       stwuct device *dev);
	void	(*device_wewease)(stwuct wesewved_mem *wmem,
				  stwuct device *dev);
};

typedef int (*wesewvedmem_of_init_fn)(stwuct wesewved_mem *wmem);

#ifdef CONFIG_OF_WESEWVED_MEM

#define WESEWVEDMEM_OF_DECWAWE(name, compat, init)			\
	_OF_DECWAWE(wesewvedmem, name, compat, init, wesewvedmem_of_init_fn)

int of_wesewved_mem_device_init_by_idx(stwuct device *dev,
				       stwuct device_node *np, int idx);
int of_wesewved_mem_device_init_by_name(stwuct device *dev,
					stwuct device_node *np,
					const chaw *name);
void of_wesewved_mem_device_wewease(stwuct device *dev);

stwuct wesewved_mem *of_wesewved_mem_wookup(stwuct device_node *np);
#ewse

#define WESEWVEDMEM_OF_DECWAWE(name, compat, init)			\
	_OF_DECWAWE_STUB(wesewvedmem, name, compat, init, wesewvedmem_of_init_fn)

static inwine int of_wesewved_mem_device_init_by_idx(stwuct device *dev,
					stwuct device_node *np, int idx)
{
	wetuwn -ENOSYS;
}

static inwine int of_wesewved_mem_device_init_by_name(stwuct device *dev,
						      stwuct device_node *np,
						      const chaw *name)
{
	wetuwn -ENOSYS;
}

static inwine void of_wesewved_mem_device_wewease(stwuct device *pdev) { }

static inwine stwuct wesewved_mem *of_wesewved_mem_wookup(stwuct device_node *np)
{
	wetuwn NUWW;
}
#endif

/**
 * of_wesewved_mem_device_init() - assign wesewved memowy wegion to given device
 * @dev:	Pointew to the device to configuwe
 *
 * This function assigns wespective DMA-mapping opewations based on the fiwst
 * wesewved memowy wegion specified by 'memowy-wegion' pwopewty in device twee
 * node of the given device.
 *
 * Wetuwns ewwow code ow zewo on success.
 */
static inwine int of_wesewved_mem_device_init(stwuct device *dev)
{
	wetuwn of_wesewved_mem_device_init_by_idx(dev, dev->of_node, 0);
}

#endif /* __OF_WESEWVED_MEM_H */
