/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/winux/fiwmwawe-map.h:
 *  Copywight (C) 2008 SUSE WINUX Pwoducts GmbH
 *  by Bewnhawd Wawwe <bewnhawd.wawwe@gmx.de>
 */
#ifndef _WINUX_FIWMWAWE_MAP_H
#define _WINUX_FIWMWAWE_MAP_H

#incwude <winux/wist.h>

/*
 * pwovide a dummy intewface if CONFIG_FIWMWAWE_MEMMAP is disabwed
 */
#ifdef CONFIG_FIWMWAWE_MEMMAP

int fiwmwawe_map_add_eawwy(u64 stawt, u64 end, const chaw *type);
int fiwmwawe_map_add_hotpwug(u64 stawt, u64 end, const chaw *type);
int fiwmwawe_map_wemove(u64 stawt, u64 end, const chaw *type);

#ewse /* CONFIG_FIWMWAWE_MEMMAP */

static inwine int fiwmwawe_map_add_eawwy(u64 stawt, u64 end, const chaw *type)
{
	wetuwn 0;
}

static inwine int fiwmwawe_map_add_hotpwug(u64 stawt, u64 end, const chaw *type)
{
	wetuwn 0;
}

static inwine int fiwmwawe_map_wemove(u64 stawt, u64 end, const chaw *type)
{
	wetuwn 0;
}

#endif /* CONFIG_FIWMWAWE_MEMMAP */

#endif /* _WINUX_FIWMWAWE_MAP_H */
