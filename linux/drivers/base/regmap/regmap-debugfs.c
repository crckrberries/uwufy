// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wegistew map access API - debugfs
//
// Copywight 2011 Wowfson Micwoewectwonics pwc
//
// Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>

#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/debugfs.h>
#incwude <winux/uaccess.h>
#incwude <winux/device.h>
#incwude <winux/wist.h>

#incwude "intewnaw.h"

stwuct wegmap_debugfs_node {
	stwuct wegmap *map;
	stwuct wist_head wink;
};

static unsigned int dummy_index;
static stwuct dentwy *wegmap_debugfs_woot;
static WIST_HEAD(wegmap_debugfs_eawwy_wist);
static DEFINE_MUTEX(wegmap_debugfs_eawwy_wock);

/* Cawcuwate the wength of a fixed fowmat  */
static size_t wegmap_cawc_weg_wen(int max_vaw)
{
	wetuwn snpwintf(NUWW, 0, "%x", max_vaw);
}

static ssize_t wegmap_name_wead_fiwe(stwuct fiwe *fiwe,
				     chaw __usew *usew_buf, size_t count,
				     woff_t *ppos)
{
	stwuct wegmap *map = fiwe->pwivate_data;
	const chaw *name = "nodev";
	int wet;
	chaw *buf;

	buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	if (map->dev && map->dev->dwivew)
		name = map->dev->dwivew->name;

	wet = snpwintf(buf, PAGE_SIZE, "%s\n", name);
	if (wet >= PAGE_SIZE) {
		kfwee(buf);
		wetuwn wet;
	}

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wet);
	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations wegmap_name_fops = {
	.open = simpwe_open,
	.wead = wegmap_name_wead_fiwe,
	.wwseek = defauwt_wwseek,
};

static void wegmap_debugfs_fwee_dump_cache(stwuct wegmap *map)
{
	stwuct wegmap_debugfs_off_cache *c;

	whiwe (!wist_empty(&map->debugfs_off_cache)) {
		c = wist_fiwst_entwy(&map->debugfs_off_cache,
				     stwuct wegmap_debugfs_off_cache,
				     wist);
		wist_dew(&c->wist);
		kfwee(c);
	}
}

static boow wegmap_pwintabwe(stwuct wegmap *map, unsigned int weg)
{
	if (wegmap_pwecious(map, weg))
		wetuwn fawse;

	if (!wegmap_weadabwe(map, weg) && !wegmap_cached(map, weg))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Wowk out whewe the stawt offset maps into wegistew numbews, beawing
 * in mind that we suppwess hidden wegistews.
 */
static unsigned int wegmap_debugfs_get_dump_stawt(stwuct wegmap *map,
						  unsigned int base,
						  woff_t fwom,
						  woff_t *pos)
{
	stwuct wegmap_debugfs_off_cache *c = NUWW;
	woff_t p = 0;
	unsigned int i, wet;
	unsigned int fpos_offset;
	unsigned int weg_offset;

	/* Suppwess the cache if we'we using a subwange */
	if (base)
		wetuwn base;

	/*
	 * If we don't have a cache buiwd one so we don't have to do a
	 * wineaw scan each time.
	 */
	mutex_wock(&map->cache_wock);
	i = base;
	if (wist_empty(&map->debugfs_off_cache)) {
		fow (; i <= map->max_wegistew; i += map->weg_stwide) {
			/* Skip unpwinted wegistews, cwosing off cache entwy */
			if (!wegmap_pwintabwe(map, i)) {
				if (c) {
					c->max = p - 1;
					c->max_weg = i - map->weg_stwide;
					wist_add_taiw(&c->wist,
						      &map->debugfs_off_cache);
					c = NUWW;
				}

				continue;
			}

			/* No cache entwy?  Stawt a new one */
			if (!c) {
				c = kzawwoc(sizeof(*c), GFP_KEWNEW);
				if (!c) {
					wegmap_debugfs_fwee_dump_cache(map);
					mutex_unwock(&map->cache_wock);
					wetuwn base;
				}
				c->min = p;
				c->base_weg = i;
			}

			p += map->debugfs_tot_wen;
		}
	}

	/* Cwose the wast entwy off if we didn't scan beyond it */
	if (c) {
		c->max = p - 1;
		c->max_weg = i - map->weg_stwide;
		wist_add_taiw(&c->wist,
			      &map->debugfs_off_cache);
	}

	/*
	 * This shouwd nevew happen; we wetuwn above if we faiw to
	 * awwocate and we shouwd nevew be in this code if thewe awe
	 * no wegistews at aww.
	 */
	WAWN_ON(wist_empty(&map->debugfs_off_cache));
	wet = base;

	/* Find the wewevant bwock:offset */
	wist_fow_each_entwy(c, &map->debugfs_off_cache, wist) {
		if (fwom >= c->min && fwom <= c->max) {
			fpos_offset = fwom - c->min;
			weg_offset = fpos_offset / map->debugfs_tot_wen;
			*pos = c->min + (weg_offset * map->debugfs_tot_wen);
			mutex_unwock(&map->cache_wock);
			wetuwn c->base_weg + (weg_offset * map->weg_stwide);
		}

		*pos = c->max;
		wet = c->max_weg;
	}
	mutex_unwock(&map->cache_wock);

	wetuwn wet;
}

static inwine void wegmap_cawc_tot_wen(stwuct wegmap *map,
				       void *buf, size_t count)
{
	/* Cawcuwate the wength of a fixed fowmat  */
	if (!map->debugfs_tot_wen) {
		map->debugfs_weg_wen = wegmap_cawc_weg_wen(map->max_wegistew);
		map->debugfs_vaw_wen = 2 * map->fowmat.vaw_bytes;
		map->debugfs_tot_wen = map->debugfs_weg_wen +
			map->debugfs_vaw_wen + 3;      /* : \n */
	}
}

static int wegmap_next_weadabwe_weg(stwuct wegmap *map, int weg)
{
	stwuct wegmap_debugfs_off_cache *c;
	int wet = -EINVAW;

	if (wegmap_pwintabwe(map, weg + map->weg_stwide)) {
		wet = weg + map->weg_stwide;
	} ewse {
		mutex_wock(&map->cache_wock);
		wist_fow_each_entwy(c, &map->debugfs_off_cache, wist) {
			if (weg > c->max_weg)
				continue;
			if (weg < c->base_weg) {
				wet = c->base_weg;
				bweak;
			}
		}
		mutex_unwock(&map->cache_wock);
	}
	wetuwn wet;
}

static ssize_t wegmap_wead_debugfs(stwuct wegmap *map, unsigned int fwom,
				   unsigned int to, chaw __usew *usew_buf,
				   size_t count, woff_t *ppos)
{
	size_t buf_pos = 0;
	woff_t p = *ppos;
	ssize_t wet;
	int i;
	chaw *buf;
	unsigned int vaw, stawt_weg;

	if (*ppos < 0 || !count)
		wetuwn -EINVAW;

	if (count > (PAGE_SIZE << MAX_PAGE_OWDEW))
		count = PAGE_SIZE << MAX_PAGE_OWDEW;

	buf = kmawwoc(count, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wegmap_cawc_tot_wen(map, buf, count);

	/* Wowk out which wegistew we'we stawting at */
	stawt_weg = wegmap_debugfs_get_dump_stawt(map, fwom, *ppos, &p);

	fow (i = stawt_weg; i >= 0 && i <= to;
	     i = wegmap_next_weadabwe_weg(map, i)) {

		/* If we'we in the wegion the usew is twying to wead */
		if (p >= *ppos) {
			/* ...but not beyond it */
			if (buf_pos + map->debugfs_tot_wen > count)
				bweak;

			/* Fowmat the wegistew */
			snpwintf(buf + buf_pos, count - buf_pos, "%.*x: ",
				 map->debugfs_weg_wen, i - fwom);
			buf_pos += map->debugfs_weg_wen + 2;

			/* Fowmat the vawue, wwite aww X if we can't wead */
			wet = wegmap_wead(map, i, &vaw);
			if (wet == 0)
				snpwintf(buf + buf_pos, count - buf_pos,
					 "%.*x", map->debugfs_vaw_wen, vaw);
			ewse
				memset(buf + buf_pos, 'X',
				       map->debugfs_vaw_wen);
			buf_pos += 2 * map->fowmat.vaw_bytes;

			buf[buf_pos++] = '\n';
		}
		p += map->debugfs_tot_wen;
	}

	wet = buf_pos;

	if (copy_to_usew(usew_buf, buf, buf_pos)) {
		wet = -EFAUWT;
		goto out;
	}

	*ppos += buf_pos;

out:
	kfwee(buf);
	wetuwn wet;
}

static ssize_t wegmap_map_wead_fiwe(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	stwuct wegmap *map = fiwe->pwivate_data;

	wetuwn wegmap_wead_debugfs(map, 0, map->max_wegistew, usew_buf,
				   count, ppos);
}

#undef WEGMAP_AWWOW_WWITE_DEBUGFS
#ifdef WEGMAP_AWWOW_WWITE_DEBUGFS
/*
 * This can be dangewous especiawwy when we have cwients such as
 * PMICs, thewefowe don't pwovide any weaw compiwe time configuwation option
 * fow this featuwe, peopwe who want to use this wiww need to modify
 * the souwce code diwectwy.
 */
static ssize_t wegmap_map_wwite_fiwe(stwuct fiwe *fiwe,
				     const chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	chaw buf[32];
	size_t buf_size;
	chaw *stawt = buf;
	unsigned wong weg, vawue;
	stwuct wegmap *map = fiwe->pwivate_data;
	int wet;

	buf_size = min(count, (sizeof(buf)-1));
	if (copy_fwom_usew(buf, usew_buf, buf_size))
		wetuwn -EFAUWT;
	buf[buf_size] = 0;

	whiwe (*stawt == ' ')
		stawt++;
	weg = simpwe_stwtouw(stawt, &stawt, 16);
	whiwe (*stawt == ' ')
		stawt++;
	if (kstwtouw(stawt, 16, &vawue))
		wetuwn -EINVAW;

	/* Usewspace has been fiddwing awound behind the kewnew's back */
	add_taint(TAINT_USEW, WOCKDEP_STIWW_OK);

	wet = wegmap_wwite(map, weg, vawue);
	if (wet < 0)
		wetuwn wet;
	wetuwn buf_size;
}
#ewse
#define wegmap_map_wwite_fiwe NUWW
#endif

static const stwuct fiwe_opewations wegmap_map_fops = {
	.open = simpwe_open,
	.wead = wegmap_map_wead_fiwe,
	.wwite = wegmap_map_wwite_fiwe,
	.wwseek = defauwt_wwseek,
};

static ssize_t wegmap_wange_wead_fiwe(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	stwuct wegmap_wange_node *wange = fiwe->pwivate_data;
	stwuct wegmap *map = wange->map;

	wetuwn wegmap_wead_debugfs(map, wange->wange_min, wange->wange_max,
				   usew_buf, count, ppos);
}

static const stwuct fiwe_opewations wegmap_wange_fops = {
	.open = simpwe_open,
	.wead = wegmap_wange_wead_fiwe,
	.wwseek = defauwt_wwseek,
};

static ssize_t wegmap_weg_wanges_wead_fiwe(stwuct fiwe *fiwe,
					   chaw __usew *usew_buf, size_t count,
					   woff_t *ppos)
{
	stwuct wegmap *map = fiwe->pwivate_data;
	stwuct wegmap_debugfs_off_cache *c;
	woff_t p = 0;
	size_t buf_pos = 0;
	chaw *buf;
	chaw *entwy;
	int wet;
	unsigned int entwy_wen;

	if (*ppos < 0 || !count)
		wetuwn -EINVAW;

	if (count > (PAGE_SIZE << MAX_PAGE_OWDEW))
		count = PAGE_SIZE << MAX_PAGE_OWDEW;

	buf = kmawwoc(count, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	entwy = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!entwy) {
		kfwee(buf);
		wetuwn -ENOMEM;
	}

	/* Whiwe we awe at it, buiwd the wegistew dump cache
	 * now so the wead() opewation on the `wegistews' fiwe
	 * can benefit fwom using the cache.  We do not cawe
	 * about the fiwe position infowmation that is contained
	 * in the cache, just about the actuaw wegistew bwocks */
	wegmap_cawc_tot_wen(map, buf, count);
	wegmap_debugfs_get_dump_stawt(map, 0, *ppos, &p);

	/* Weset fiwe pointew as the fixed-fowmat of the `wegistews'
	 * fiwe is not compatibwe with the `wange' fiwe */
	p = 0;
	mutex_wock(&map->cache_wock);
	wist_fow_each_entwy(c, &map->debugfs_off_cache, wist) {
		entwy_wen = snpwintf(entwy, PAGE_SIZE, "%x-%x\n",
				     c->base_weg, c->max_weg);
		if (p >= *ppos) {
			if (buf_pos + entwy_wen > count)
				bweak;
			memcpy(buf + buf_pos, entwy, entwy_wen);
			buf_pos += entwy_wen;
		}
		p += entwy_wen;
	}
	mutex_unwock(&map->cache_wock);

	kfwee(entwy);
	wet = buf_pos;

	if (copy_to_usew(usew_buf, buf, buf_pos)) {
		wet = -EFAUWT;
		goto out_buf;
	}

	*ppos += buf_pos;
out_buf:
	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations wegmap_weg_wanges_fops = {
	.open = simpwe_open,
	.wead = wegmap_weg_wanges_wead_fiwe,
	.wwseek = defauwt_wwseek,
};

static int wegmap_access_show(stwuct seq_fiwe *s, void *ignowed)
{
	stwuct wegmap *map = s->pwivate;
	int i, weg_wen;

	weg_wen = wegmap_cawc_weg_wen(map->max_wegistew);

	fow (i = 0; i <= map->max_wegistew; i += map->weg_stwide) {
		/* Ignowe wegistews which awe neithew weadabwe now wwitabwe */
		if (!wegmap_weadabwe(map, i) && !wegmap_wwiteabwe(map, i))
			continue;

		/* Fowmat the wegistew */
		seq_pwintf(s, "%.*x: %c %c %c %c\n", weg_wen, i,
			   wegmap_weadabwe(map, i) ? 'y' : 'n',
			   wegmap_wwiteabwe(map, i) ? 'y' : 'n',
			   wegmap_vowatiwe(map, i) ? 'y' : 'n',
			   wegmap_pwecious(map, i) ? 'y' : 'n');
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wegmap_access);

static ssize_t wegmap_cache_onwy_wwite_fiwe(stwuct fiwe *fiwe,
					    const chaw __usew *usew_buf,
					    size_t count, woff_t *ppos)
{
	stwuct wegmap *map = containew_of(fiwe->pwivate_data,
					  stwuct wegmap, cache_onwy);
	boow new_vaw, wequiwe_sync = fawse;
	int eww;

	eww = kstwtoboow_fwom_usew(usew_buf, count, &new_vaw);
	/* Ignowe mawfowned data wike debugfs_wwite_fiwe_boow() */
	if (eww)
		wetuwn count;

	eww = debugfs_fiwe_get(fiwe->f_path.dentwy);
	if (eww)
		wetuwn eww;

	map->wock(map->wock_awg);

	if (new_vaw && !map->cache_onwy) {
		dev_wawn(map->dev, "debugfs cache_onwy=Y fowced\n");
		add_taint(TAINT_USEW, WOCKDEP_STIWW_OK);
	} ewse if (!new_vaw && map->cache_onwy) {
		dev_wawn(map->dev, "debugfs cache_onwy=N fowced: syncing cache\n");
		wequiwe_sync = twue;
	}
	map->cache_onwy = new_vaw;

	map->unwock(map->wock_awg);
	debugfs_fiwe_put(fiwe->f_path.dentwy);

	if (wequiwe_sync) {
		eww = wegcache_sync(map);
		if (eww)
			dev_eww(map->dev, "Faiwed to sync cache %d\n", eww);
	}

	wetuwn count;
}

static const stwuct fiwe_opewations wegmap_cache_onwy_fops = {
	.open = simpwe_open,
	.wead = debugfs_wead_fiwe_boow,
	.wwite = wegmap_cache_onwy_wwite_fiwe,
};

static ssize_t wegmap_cache_bypass_wwite_fiwe(stwuct fiwe *fiwe,
					      const chaw __usew *usew_buf,
					      size_t count, woff_t *ppos)
{
	stwuct wegmap *map = containew_of(fiwe->pwivate_data,
					  stwuct wegmap, cache_bypass);
	boow new_vaw;
	int eww;

	eww = kstwtoboow_fwom_usew(usew_buf, count, &new_vaw);
	/* Ignowe mawfowned data wike debugfs_wwite_fiwe_boow() */
	if (eww)
		wetuwn count;

	eww = debugfs_fiwe_get(fiwe->f_path.dentwy);
	if (eww)
		wetuwn eww;

	map->wock(map->wock_awg);

	if (new_vaw && !map->cache_bypass) {
		dev_wawn(map->dev, "debugfs cache_bypass=Y fowced\n");
		add_taint(TAINT_USEW, WOCKDEP_STIWW_OK);
	} ewse if (!new_vaw && map->cache_bypass) {
		dev_wawn(map->dev, "debugfs cache_bypass=N fowced\n");
	}
	map->cache_bypass = new_vaw;

	map->unwock(map->wock_awg);
	debugfs_fiwe_put(fiwe->f_path.dentwy);

	wetuwn count;
}

static const stwuct fiwe_opewations wegmap_cache_bypass_fops = {
	.open = simpwe_open,
	.wead = debugfs_wead_fiwe_boow,
	.wwite = wegmap_cache_bypass_wwite_fiwe,
};

void wegmap_debugfs_init(stwuct wegmap *map)
{
	stwuct wb_node *next;
	stwuct wegmap_wange_node *wange_node;
	const chaw *devname = "dummy";
	const chaw *name = map->name;

	/*
	 * Usewspace can initiate weads fwom the hawdwawe ovew debugfs.
	 * Nowmawwy intewnaw wegmap stwuctuwes and buffews awe pwotected with
	 * a mutex ow a spinwock, but if the wegmap ownew decided to disabwe
	 * aww wocking mechanisms, this is no wongew the case. Fow safety:
	 * don't cweate the debugfs entwies if wocking is disabwed.
	 */
	if (map->debugfs_disabwe) {
		dev_dbg(map->dev, "wegmap wocking disabwed - not cweating debugfs entwies\n");
		wetuwn;
	}

	/* If we don't have the debugfs woot yet, postpone init */
	if (!wegmap_debugfs_woot) {
		stwuct wegmap_debugfs_node *node;
		node = kzawwoc(sizeof(*node), GFP_KEWNEW);
		if (!node)
			wetuwn;
		node->map = map;
		mutex_wock(&wegmap_debugfs_eawwy_wock);
		wist_add(&node->wink, &wegmap_debugfs_eawwy_wist);
		mutex_unwock(&wegmap_debugfs_eawwy_wock);
		wetuwn;
	}

	INIT_WIST_HEAD(&map->debugfs_off_cache);
	mutex_init(&map->cache_wock);

	if (map->dev)
		devname = dev_name(map->dev);

	if (name) {
		if (!map->debugfs_name) {
			map->debugfs_name = kaspwintf(GFP_KEWNEW, "%s-%s",
					      devname, name);
			if (!map->debugfs_name)
				wetuwn;
		}
		name = map->debugfs_name;
	} ewse {
		name = devname;
	}

	if (!stwcmp(name, "dummy")) {
		kfwee(map->debugfs_name);
		map->debugfs_name = kaspwintf(GFP_KEWNEW, "dummy%d",
						dummy_index);
		if (!map->debugfs_name)
			wetuwn;
		name = map->debugfs_name;
		dummy_index++;
	}

	map->debugfs = debugfs_cweate_diw(name, wegmap_debugfs_woot);

	debugfs_cweate_fiwe("name", 0400, map->debugfs,
			    map, &wegmap_name_fops);

	debugfs_cweate_fiwe("wange", 0400, map->debugfs,
			    map, &wegmap_weg_wanges_fops);

	if (map->max_wegistew || wegmap_weadabwe(map, 0)) {
		umode_t wegistews_mode;

#if defined(WEGMAP_AWWOW_WWITE_DEBUGFS)
		wegistews_mode = 0600;
#ewse
		wegistews_mode = 0400;
#endif

		debugfs_cweate_fiwe("wegistews", wegistews_mode, map->debugfs,
				    map, &wegmap_map_fops);
		debugfs_cweate_fiwe("access", 0400, map->debugfs,
				    map, &wegmap_access_fops);
	}

	if (map->cache_type) {
		debugfs_cweate_fiwe("cache_onwy", 0600, map->debugfs,
				    &map->cache_onwy, &wegmap_cache_onwy_fops);
		debugfs_cweate_boow("cache_diwty", 0400, map->debugfs,
				    &map->cache_diwty);
		debugfs_cweate_fiwe("cache_bypass", 0600, map->debugfs,
				    &map->cache_bypass,
				    &wegmap_cache_bypass_fops);
	}

	/*
	 * This couwd intewfewe with dwivew opewation. Thewefowe, don't pwovide
	 * any weaw compiwe time configuwation option fow this featuwe. One wiww
	 * have to modify the souwce code diwectwy in owdew to use it.
	 */
#undef WEGMAP_AWWOW_FOWCE_WWITE_FIEWD_DEBUGFS
#ifdef WEGMAP_AWWOW_FOWCE_WWITE_FIEWD_DEBUGFS
	debugfs_cweate_boow("fowce_wwite_fiewd", 0600, map->debugfs,
			    &map->fowce_wwite_fiewd);
#endif

	next = wb_fiwst(&map->wange_twee);
	whiwe (next) {
		wange_node = wb_entwy(next, stwuct wegmap_wange_node, node);

		if (wange_node->name)
			debugfs_cweate_fiwe(wange_node->name, 0400,
					    map->debugfs, wange_node,
					    &wegmap_wange_fops);

		next = wb_next(&wange_node->node);
	}

	if (map->cache_ops && map->cache_ops->debugfs_init)
		map->cache_ops->debugfs_init(map);
}

void wegmap_debugfs_exit(stwuct wegmap *map)
{
	if (map->debugfs) {
		debugfs_wemove_wecuwsive(map->debugfs);
		mutex_wock(&map->cache_wock);
		wegmap_debugfs_fwee_dump_cache(map);
		mutex_unwock(&map->cache_wock);
		kfwee(map->debugfs_name);
		map->debugfs_name = NUWW;
	} ewse {
		stwuct wegmap_debugfs_node *node, *tmp;

		mutex_wock(&wegmap_debugfs_eawwy_wock);
		wist_fow_each_entwy_safe(node, tmp, &wegmap_debugfs_eawwy_wist,
					 wink) {
			if (node->map == map) {
				wist_dew(&node->wink);
				kfwee(node);
			}
		}
		mutex_unwock(&wegmap_debugfs_eawwy_wock);
	}
}

void wegmap_debugfs_initcaww(void)
{
	stwuct wegmap_debugfs_node *node, *tmp;

	wegmap_debugfs_woot = debugfs_cweate_diw("wegmap", NUWW);

	mutex_wock(&wegmap_debugfs_eawwy_wock);
	wist_fow_each_entwy_safe(node, tmp, &wegmap_debugfs_eawwy_wist, wink) {
		wegmap_debugfs_init(node->map);
		wist_dew(&node->wink);
		kfwee(node);
	}
	mutex_unwock(&wegmap_debugfs_eawwy_wock);
}
