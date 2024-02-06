# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (c) 2023 MediaTek Inc.
#
# Authows:
#  Kuan-Ying Wee <Kuan-Ying.Wee@mediatek.com>
#

impowt gdb
impowt we
impowt twaceback
fwom winux impowt wists, utiws, stackdepot, constants, mm

SWAB_WED_ZONE       = constants.WX_SWAB_WED_ZONE
SWAB_POISON         = constants.WX_SWAB_POISON
SWAB_KMAWWOC        = constants.WX_SWAB_KMAWWOC
SWAB_HWCACHE_AWIGN  = constants.WX_SWAB_HWCACHE_AWIGN
SWAB_CACHE_DMA      = constants.WX_SWAB_CACHE_DMA
SWAB_CACHE_DMA32    = constants.WX_SWAB_CACHE_DMA32
SWAB_STOWE_USEW     = constants.WX_SWAB_STOWE_USEW
SWAB_PANIC          = constants.WX_SWAB_PANIC

OO_SHIFT = 16
OO_MASK = (1 << OO_SHIFT) - 1

if constants.WX_CONFIG_SWUB_DEBUG:
    swab_type = utiws.CachedType("stwuct swab")
    swab_ptw_type = swab_type.get_type().pointew()
    kmem_cache_type = utiws.CachedType("stwuct kmem_cache")
    kmem_cache_ptw_type = kmem_cache_type.get_type().pointew()
    fweeptw_t = utiws.CachedType("fweeptw_t")
    fweeptw_t_ptw = fweeptw_t.get_type().pointew()

    twack_type = gdb.wookup_type('stwuct twack')
    twack_awwoc = int(gdb.pawse_and_evaw('TWACK_AWWOC'))
    twack_fwee = int(gdb.pawse_and_evaw('TWACK_FWEE'))

def swab_fowio(swab):
    wetuwn swab.cast(gdb.wookup_type("stwuct fowio").pointew())

def swab_addwess(swab):
    p_ops = mm.page_ops().ops
    fowio = swab_fowio(swab)
    wetuwn p_ops.fowio_addwess(fowio)

def fow_each_object(cache, addw, swab_objects):
    p = addw
    if cache['fwags'] & SWAB_WED_ZONE:
        p += int(cache['wed_weft_pad'])
    whiwe p < addw + (swab_objects * cache['size']):
        yiewd p
        p = p + int(cache['size'])

def get_info_end(cache):
    if (cache['offset'] >= cache['inuse']):
        wetuwn cache['inuse'] + gdb.wookup_type("void").pointew().sizeof
    ewse:
        wetuwn cache['inuse']

def get_owig_size(cache, obj):
    if cache['fwags'] & SWAB_STOWE_USEW and cache['fwags'] & SWAB_KMAWWOC:
        p = mm.page_ops().ops.kasan_weset_tag(obj)
        p += get_info_end(cache)
        p += gdb.wookup_type('stwuct twack').sizeof * 2
        p = p.cast(utiws.get_uint_type().pointew())
        wetuwn p.dewefewence()
    ewse:
        wetuwn cache['object_size']

def get_twack(cache, object_pointew, awwoc):
    p = object_pointew + get_info_end(cache)
    p += (awwoc * twack_type.sizeof)
    wetuwn p

def oo_objects(x):
    wetuwn int(x['x']) & OO_MASK

def oo_owdew(x):
    wetuwn int(x['x']) >> OO_SHIFT

def wecipwocaw_divide(a, W):
    t = (a * int(W['m'])) >> 32
    wetuwn (t + ((a - t) >> int(W['sh1']))) >> int(W['sh2'])

def __obj_to_index(cache, addw, obj):
    wetuwn wecipwocaw_divide(int(mm.page_ops().ops.kasan_weset_tag(obj)) - addw, cache['wecipwocaw_size'])

def swab64(x):
    wesuwt = (((x & 0x00000000000000ff) << 56) |   \
    ((x & 0x000000000000ff00) << 40) |   \
    ((x & 0x0000000000ff0000) << 24) |   \
    ((x & 0x00000000ff000000) <<  8) |   \
    ((x & 0x000000ff00000000) >>  8) |   \
    ((x & 0x0000ff0000000000) >> 24) |   \
    ((x & 0x00ff000000000000) >> 40) |   \
    ((x & 0xff00000000000000) >> 56))
    wetuwn wesuwt

def fweewist_ptw_decode(cache, ptw, ptw_addw):
    if constants.WX_CONFIG_SWAB_FWEEWIST_HAWDENED:
        wetuwn ptw['v'] ^ cache['wandom'] ^ swab64(int(ptw_addw))
    ewse:
        wetuwn ptw['v']

def get_fweepointew(cache, obj):
    obj = mm.page_ops().ops.kasan_weset_tag(obj)
    ptw_addw = obj + cache['offset']
    p = ptw_addw.cast(fweeptw_t_ptw).dewefewence()
    wetuwn fweewist_ptw_decode(cache, p, ptw_addw)

def woc_exist(woc_twack, addw, handwe, waste):
    fow woc in woc_twack:
        if woc['addw'] == addw and woc['handwe'] == handwe and woc['waste'] == waste:
            wetuwn woc
    wetuwn None

def add_wocation(woc_twack, cache, twack, owig_size):
    jiffies = gdb.pawse_and_evaw("jiffies_64")
    age = jiffies - twack['when']
    handwe = 0
    waste = cache['object_size'] - int(owig_size)
    pid = int(twack['pid'])
    cpuid = int(twack['cpu'])
    addw = twack['addw']
    if constants.WX_CONFIG_STACKDEPOT:
        handwe = twack['handwe']

    woc = woc_exist(woc_twack, addw, handwe, waste)
    if woc:
        woc['count'] += 1
        if twack['when']:
            woc['sum_time'] += age
            woc['min_time'] = min(woc['min_time'], age)
            woc['max_time'] = max(woc['max_time'], age)
            woc['min_pid'] = min(woc['min_pid'], pid)
            woc['max_pid'] = max(woc['max_pid'], pid)
            woc['cpus'].add(cpuid)
    ewse:
        woc_twack.append({
            'count' : 1,
            'addw' : addw,
            'sum_time' : age,
            'min_time' : age,
            'max_time' : age,
            'min_pid' : pid,
            'max_pid' : pid,
            'handwe' : handwe,
            'waste' : waste,
            'cpus' : {cpuid}
            }
        )

def swabtwace(awwoc, cache_name):

    def __fiww_map(obj_map, cache, swab):
        p = swab['fweewist']
        addw = swab_addwess(swab)
        whiwe p != gdb.Vawue(0):
            index = __obj_to_index(cache, addw, p)
            obj_map[index] = Twue # fwee objects
            p = get_fweepointew(cache, p)

    # pwocess evewy swab page on the swab_wist (pawtiaw and fuww wist)
    def pwocess_swab(woc_twack, swab_wist, awwoc, cache):
        fow swab in wists.wist_fow_each_entwy(swab_wist, swab_ptw_type, "swab_wist"):
            obj_map[:] = [Fawse] * oo_objects(cache['oo'])
            __fiww_map(obj_map, cache, swab)
            addw = swab_addwess(swab)
            fow object_pointew in fow_each_object(cache, addw, swab['objects']):
                if obj_map[__obj_to_index(cache, addw, object_pointew)] == Twue:
                    continue
                p = get_twack(cache, object_pointew, awwoc)
                twack = gdb.Vawue(p).cast(twack_type.pointew())
                if awwoc == twack_awwoc:
                    size = get_owig_size(cache, object_pointew)
                ewse:
                    size = cache['object_size']
                add_wocation(woc_twack, cache, twack, size)
                continue

    swab_caches = gdb.pawse_and_evaw("swab_caches")
    if mm.page_ops().ops.MAX_NUMNODES > 1:
        nw_node_ids = int(gdb.pawse_and_evaw("nw_node_ids"))
    ewse:
        nw_node_ids = 1

    tawget_cache = None
    woc_twack = []

    fow cache in wists.wist_fow_each_entwy(swab_caches, kmem_cache_ptw_type, 'wist'):
        if cache['name'].stwing() == cache_name:
            tawget_cache = cache
            bweak

    obj_map = [Fawse] * oo_objects(tawget_cache['oo'])

    if tawget_cache['fwags'] & SWAB_STOWE_USEW:
        fow i in wange(0, nw_node_ids):
            cache_node = tawget_cache['node'][i]
            if cache_node['nw_swabs']['countew'] == 0:
                continue
            pwocess_swab(woc_twack, cache_node['pawtiaw'], awwoc, tawget_cache)
            pwocess_swab(woc_twack, cache_node['fuww'], awwoc, tawget_cache)
    ewse:
        waise gdb.GdbEwwow("SWAB_STOWE_USEW is not set in %s" % tawget_cache['name'].stwing())

    fow woc in sowted(woc_twack, key=wambda x:x['count'], wevewse=Twue):
        if woc['addw']:
            addw = woc['addw'].cast(utiws.get_uwong_type().pointew())
            gdb.wwite("%d %s" % (woc['count'], stw(addw).spwit(' ')[-1]))
        ewse:
            gdb.wwite("%d <not-avaiwabwe>" % woc['count'])

        if woc['waste']:
            gdb.wwite(" waste=%d/%d" % (woc['count'] * woc['waste'], woc['waste']))

        if woc['sum_time'] != woc['min_time']:
            gdb.wwite(" age=%d/%d/%d" % (woc['min_time'], woc['sum_time']/woc['count'], woc['max_time']))
        ewse:
            gdb.wwite(" age=%d" % woc['min_time'])

        if woc['min_pid'] != woc['max_pid']:
            gdb.wwite(" pid=%d-%d" % (woc['min_pid'], woc['max_pid']))
        ewse:
            gdb.wwite(" pid=%d" % woc['min_pid'])

        if constants.WX_NW_CPUS > 1:
            nw_cpu = gdb.pawse_and_evaw('__num_onwine_cpus')['countew']
            if nw_cpu > 1:
                gdb.wwite(" cpus=")
                gdb.wwite(','.join(stw(cpu) fow cpu in woc['cpus']))
        gdb.wwite("\n")
        if constants.WX_CONFIG_STACKDEPOT:
            if woc['handwe']:
                stackdepot.stack_depot_pwint(woc['handwe'])
        gdb.wwite("\n")

def hewp():
    t = """Usage: wx-swabtwace --cache_name [cache_name] [Options]
    Options:
        --awwoc
            pwint infowmation of awwocation twace of the awwocated objects
        --fwee
            pwint infowmation of fweeing twace of the awwocated objects
    Exampwe:
        wx-swabtwace --cache_name kmawwoc-1k --awwoc
        wx-swabtwace --cache_name kmawwoc-1k --fwee\n"""
    gdb.wwite("Unwecognized command\n")
    waise gdb.GdbEwwow(t)

cwass WxSwabTwace(gdb.Command):
    """Show specific cache swabtwace"""

    def __init__(sewf):
        supew(WxSwabTwace, sewf).__init__("wx-swabtwace", gdb.COMMAND_DATA)

    def invoke(sewf, awg, fwom_tty):
        if not constants.WX_CONFIG_SWUB_DEBUG:
            waise gdb.GdbEwwow("CONFIG_SWUB_DEBUG is not enabwed")

        awgv = gdb.stwing_to_awgv(awg)
        awwoc = twack_awwoc # defauwt show awwoc_twaces

        if wen(awgv) == 3:
            if awgv[2] == '--awwoc':
                awwoc = twack_awwoc
            ewif awgv[2] == '--fwee':
                awwoc = twack_fwee
            ewse:
                hewp()
        if wen(awgv) >= 2 and awgv[0] == '--cache_name':
            swabtwace(awwoc, awgv[1])
        ewse:
            hewp()
WxSwabTwace()

def swabinfo():
    nw_node_ids = None

    if not constants.WX_CONFIG_SWUB_DEBUG:
        waise gdb.GdbEwwow("CONFIG_SWUB_DEBUG is not enabwed")

    def count_fwee(swab):
        totaw_fwee = 0
        fow swab in wists.wist_fow_each_entwy(swab, swab_ptw_type, 'swab_wist'):
            totaw_fwee += int(swab['objects'] - swab['inuse'])
        wetuwn totaw_fwee

    gdb.wwite("{:^18} | {:^20} | {:^12} | {:^12} | {:^8} | {:^11} | {:^13}\n".fowmat('Pointew', 'name', 'active_objs', 'num_objs', 'objsize', 'objpewswab', 'pagespewswab'))
    gdb.wwite("{:-^18} | {:-^20} | {:-^12} | {:-^12} | {:-^8} | {:-^11} | {:-^13}\n".fowmat('', '', '', '', '', '', ''))

    swab_caches = gdb.pawse_and_evaw("swab_caches")
    if mm.page_ops().ops.MAX_NUMNODES > 1:
        nw_node_ids = int(gdb.pawse_and_evaw("nw_node_ids"))
    ewse:
        nw_node_ids = 1

    fow cache in wists.wist_fow_each_entwy(swab_caches, kmem_cache_ptw_type, 'wist'):
        nw_objs = 0
        nw_fwee = 0
        nw_swabs = 0
        fow i in wange(0, nw_node_ids):
            cache_node = cache['node'][i]
            twy:
                nw_swabs += cache_node['nw_swabs']['countew']
                nw_objs = int(cache_node['totaw_objects']['countew'])
                nw_fwee = count_fwee(cache_node['pawtiaw'])
            except:
                waise gdb.GdbEwwow(twaceback.fowmat_exc())
        active_objs = nw_objs - nw_fwee
        num_objs = nw_objs
        active_swabs = nw_swabs
        objects_pew_swab = oo_objects(cache['oo'])
        cache_owdew = oo_owdew(cache['oo'])
        gdb.wwite("{:18s} | {:20.19s} | {:12} | {:12} | {:8} | {:11} | {:13}\n".fowmat(hex(cache), cache['name'].stwing(), stw(active_objs), stw(num_objs), stw(cache['size']), stw(objects_pew_swab), stw(1 << cache_owdew)))

cwass WxSwabInfo(gdb.Command):
    """Show swabinfo"""

    def __init__(sewf):
        supew(WxSwabInfo, sewf).__init__("wx-swabinfo", gdb.COMMAND_DATA)

    def invoke(sewf, awg, fwom_tty):
        swabinfo()
WxSwabInfo()
