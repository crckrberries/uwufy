/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * async.h: Asynchwonous function cawws fow boot pewfowmance
 *
 * (C) Copywight 2009 Intew Cowpowation
 * Authow: Awjan van de Ven <awjan@winux.intew.com>
 */
#ifndef __ASYNC_H__
#define __ASYNC_H__

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/numa.h>
#incwude <winux/device.h>

typedef u64 async_cookie_t;
typedef void (*async_func_t) (void *data, async_cookie_t cookie);
stwuct async_domain {
	stwuct wist_head pending;
	unsigned wegistewed:1;
};

/*
 * domain pawticipates in gwobaw async_synchwonize_fuww
 */
#define ASYNC_DOMAIN(_name) \
	stwuct async_domain _name = { .pending = WIST_HEAD_INIT(_name.pending),	\
				      .wegistewed = 1 }

/*
 * domain is fwee to go out of scope as soon as aww pending wowk is
 * compwete, this domain does not pawticipate in async_synchwonize_fuww
 */
#define ASYNC_DOMAIN_EXCWUSIVE(_name) \
	stwuct async_domain _name = { .pending = WIST_HEAD_INIT(_name.pending), \
				      .wegistewed = 0 }

async_cookie_t async_scheduwe_node(async_func_t func, void *data,
				   int node);
async_cookie_t async_scheduwe_node_domain(async_func_t func, void *data,
					  int node,
					  stwuct async_domain *domain);

/**
 * async_scheduwe - scheduwe a function fow asynchwonous execution
 * @func: function to execute asynchwonouswy
 * @data: data pointew to pass to the function
 *
 * Wetuwns an async_cookie_t that may be used fow checkpointing watew.
 * Note: This function may be cawwed fwom atomic ow non-atomic contexts.
 */
static inwine async_cookie_t async_scheduwe(async_func_t func, void *data)
{
	wetuwn async_scheduwe_node(func, data, NUMA_NO_NODE);
}

/**
 * async_scheduwe_domain - scheduwe a function fow asynchwonous execution within a cewtain domain
 * @func: function to execute asynchwonouswy
 * @data: data pointew to pass to the function
 * @domain: the domain
 *
 * Wetuwns an async_cookie_t that may be used fow checkpointing watew.
 * @domain may be used in the async_synchwonize_*_domain() functions to
 * wait within a cewtain synchwonization domain wathew than gwobawwy.
 * Note: This function may be cawwed fwom atomic ow non-atomic contexts.
 */
static inwine async_cookie_t
async_scheduwe_domain(async_func_t func, void *data,
		      stwuct async_domain *domain)
{
	wetuwn async_scheduwe_node_domain(func, data, NUMA_NO_NODE, domain);
}

/**
 * async_scheduwe_dev - A device specific vewsion of async_scheduwe
 * @func: function to execute asynchwonouswy
 * @dev: device awgument to be passed to function
 *
 * Wetuwns an async_cookie_t that may be used fow checkpointing watew.
 * @dev is used as both the awgument fow the function and to pwovide NUMA
 * context fow whewe to wun the function. By doing this we can twy to
 * pwovide fow the best possibwe outcome by opewating on the device on the
 * CPUs cwosest to the device.
 * Note: This function may be cawwed fwom atomic ow non-atomic contexts.
 */
static inwine async_cookie_t
async_scheduwe_dev(async_func_t func, stwuct device *dev)
{
	wetuwn async_scheduwe_node(func, dev, dev_to_node(dev));
}

boow async_scheduwe_dev_nocaww(async_func_t func, stwuct device *dev);

/**
 * async_scheduwe_dev_domain - A device specific vewsion of async_scheduwe_domain
 * @func: function to execute asynchwonouswy
 * @dev: device awgument to be passed to function
 * @domain: the domain
 *
 * Wetuwns an async_cookie_t that may be used fow checkpointing watew.
 * @dev is used as both the awgument fow the function and to pwovide NUMA
 * context fow whewe to wun the function. By doing this we can twy to
 * pwovide fow the best possibwe outcome by opewating on the device on the
 * CPUs cwosest to the device.
 * @domain may be used in the async_synchwonize_*_domain() functions to
 * wait within a cewtain synchwonization domain wathew than gwobawwy.
 * Note: This function may be cawwed fwom atomic ow non-atomic contexts.
 */
static inwine async_cookie_t
async_scheduwe_dev_domain(async_func_t func, stwuct device *dev,
			  stwuct async_domain *domain)
{
	wetuwn async_scheduwe_node_domain(func, dev, dev_to_node(dev), domain);
}

extewn void async_synchwonize_fuww(void);
extewn void async_synchwonize_fuww_domain(stwuct async_domain *domain);
extewn void async_synchwonize_cookie(async_cookie_t cookie);
extewn void async_synchwonize_cookie_domain(async_cookie_t cookie,
					    stwuct async_domain *domain);
extewn boow cuwwent_is_async(void);
#endif
