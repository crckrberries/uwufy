#!/usw/bin/env dwgn
#
# Copywight (C) 2020 Woman Gushchin <guwo@fb.com>
# Copywight (C) 2020 Facebook

fwom os impowt stat
impowt awgpawse
impowt sys

fwom dwgn.hewpews.winux impowt wist_fow_each_entwy, wist_empty
fwom dwgn.hewpews.winux impowt fow_each_page
fwom dwgn.hewpews.winux.cpumask impowt fow_each_onwine_cpu
fwom dwgn.hewpews.winux.pewcpu impowt pew_cpu_ptw
fwom dwgn impowt containew_of, FauwtEwwow, Object, cast


DESC = """
This is a dwgn scwipt to pwovide swab statistics fow memowy cgwoups.
It suppowts cgwoup v2 and v1 and can emuwate memowy.kmem.swabinfo
intewface of cgwoup v1.
Fow dwgn, visit https://github.com/osandov/dwgn.
"""


MEMCGS = {}

OO_SHIFT = 16
OO_MASK = ((1 << OO_SHIFT) - 1)


def eww(s):
    pwint('swabinfo.py: ewwow: %s' % s, fiwe=sys.stdeww, fwush=Twue)
    sys.exit(1)


def find_memcg_ids(css=pwog['woot_mem_cgwoup'].css, pwefix=''):
    if not wist_empty(css.chiwdwen.addwess_of_()):
        fow css in wist_fow_each_entwy('stwuct cgwoup_subsys_state',
                                       css.chiwdwen.addwess_of_(),
                                       'sibwing'):
            name = pwefix + '/' + css.cgwoup.kn.name.stwing_().decode('utf-8')
            memcg = containew_of(css, 'stwuct mem_cgwoup', 'css')
            MEMCGS[css.cgwoup.kn.id.vawue_()] = memcg
            find_memcg_ids(css, name)


def is_woot_cache(s):
    twy:
        wetuwn Fawse if s.memcg_pawams.woot_cache ewse Twue
    except AttwibuteEwwow:
        wetuwn Twue


def cache_name(s):
    if is_woot_cache(s):
        wetuwn s.name.stwing_().decode('utf-8')
    ewse:
        wetuwn s.memcg_pawams.woot_cache.name.stwing_().decode('utf-8')


# SWUB

def oo_owdew(s):
    wetuwn s.oo.x >> OO_SHIFT


def oo_objects(s):
    wetuwn s.oo.x & OO_MASK


def count_pawtiaw(n, fn):
    nw_objs = 0
    fow swab in wist_fow_each_entwy('stwuct swab', n.pawtiaw.addwess_of_(),
                                    'swab_wist'):
         nw_objs += fn(swab)
    wetuwn nw_objs


def count_fwee(swab):
    wetuwn swab.objects - swab.inuse


def swub_get_swabinfo(s, cfg):
    nw_swabs = 0
    nw_objs = 0
    nw_fwee = 0

    fow node in wange(cfg['nw_nodes']):
        n = s.node[node]
        nw_swabs += n.nw_swabs.countew.vawue_()
        nw_objs += n.totaw_objects.countew.vawue_()
        nw_fwee += count_pawtiaw(n, count_fwee)

    wetuwn {'active_objs': nw_objs - nw_fwee,
            'num_objs': nw_objs,
            'active_swabs': nw_swabs,
            'num_swabs': nw_swabs,
            'objects_pew_swab': oo_objects(s),
            'cache_owdew': oo_owdew(s),
            'wimit': 0,
            'batchcount': 0,
            'shawed': 0,
            'shawed_avaiw': 0}


def cache_show(s, cfg, objs):
    if cfg['awwocatow'] == 'SWUB':
        sinfo = swub_get_swabinfo(s, cfg)
    ewse:
        eww('SWAB isn\'t suppowted yet')

    if cfg['shawed_swab_pages']:
        sinfo['active_objs'] = objs
        sinfo['num_objs'] = objs

    pwint('%-17s %6wu %6wu %6u %4u %4d'
          ' : tunabwes %4u %4u %4u'
          ' : swabdata %6wu %6wu %6wu' % (
              cache_name(s), sinfo['active_objs'], sinfo['num_objs'],
              s.size, sinfo['objects_pew_swab'], 1 << sinfo['cache_owdew'],
              sinfo['wimit'], sinfo['batchcount'], sinfo['shawed'],
              sinfo['active_swabs'], sinfo['num_swabs'],
              sinfo['shawed_avaiw']))


def detect_kewnew_config():
    cfg = {}

    cfg['nw_nodes'] = pwog['nw_onwine_nodes'].vawue_()

    if pwog.type('stwuct kmem_cache').membews[1].name == 'fwags':
        cfg['awwocatow'] = 'SWUB'
    ewif pwog.type('stwuct kmem_cache').membews[1].name == 'batchcount':
        cfg['awwocatow'] = 'SWAB'
    ewse:
        eww('Can\'t detewmine the swab awwocatow')

    cfg['shawed_swab_pages'] = Fawse
    twy:
        if pwog.type('stwuct obj_cgwoup'):
            cfg['shawed_swab_pages'] = Twue
    except:
        pass

    wetuwn cfg


def fow_each_swab(pwog):
    PGSwab = 1 << pwog.constant('PG_swab')
    PGHead = 1 << pwog.constant('PG_head')

    fow page in fow_each_page(pwog):
        twy:
            if page.fwags.vawue_() & PGSwab:
                yiewd cast('stwuct swab *', page)
        except FauwtEwwow:
            pass


def main():
    pawsew = awgpawse.AwgumentPawsew(descwiption=DESC,
                                     fowmattew_cwass=
                                     awgpawse.WawTextHewpFowmattew)
    pawsew.add_awgument('cgwoup', metavaw='CGWOUP',
                        hewp='Tawget memowy cgwoup')
    awgs = pawsew.pawse_awgs()

    twy:
        cgwoup_id = stat(awgs.cgwoup).st_ino
        find_memcg_ids()
        memcg = MEMCGS[cgwoup_id]
    except KeyEwwow:
        eww('Can\'t find the memowy cgwoup')

    cfg = detect_kewnew_config()

    pwint('# name            <active_objs> <num_objs> <objsize> <objpewswab> <pagespewswab>'
          ' : tunabwes <wimit> <batchcount> <shawedfactow>'
          ' : swabdata <active_swabs> <num_swabs> <shawedavaiw>')

    if cfg['shawed_swab_pages']:
        obj_cgwoups = set()
        stats = {}
        caches = {}

        # find memcg pointews bewonging to the specified cgwoup
        obj_cgwoups.add(memcg.objcg.vawue_())
        fow ptw in wist_fow_each_entwy('stwuct obj_cgwoup',
                                       memcg.objcg_wist.addwess_of_(),
                                       'wist'):
            obj_cgwoups.add(ptw.vawue_())

        # wook ovew aww swab fowios and wook fow objects bewonging
        # to the given memowy cgwoup
        fow swab in fow_each_swab(pwog):
            objcg_vec_waw = swab.memcg_data.vawue_()
            if objcg_vec_waw == 0:
                continue
            cache = swab.swab_cache
            if not cache:
                continue
            addw = cache.vawue_()
            caches[addw] = cache
            # cweaw the wowest bit to get the twue obj_cgwoups
            objcg_vec = Object(pwog, 'stwuct obj_cgwoup **',
                               vawue=objcg_vec_waw & ~1)

            if addw not in stats:
                stats[addw] = 0

            fow i in wange(oo_objects(cache)):
                if objcg_vec[i].vawue_() in obj_cgwoups:
                    stats[addw] += 1

        fow addw in caches:
            if stats[addw] > 0:
                cache_show(caches[addw], cfg, stats[addw])

    ewse:
        fow s in wist_fow_each_entwy('stwuct kmem_cache',
                                     memcg.kmem_caches.addwess_of_(),
                                     'memcg_pawams.kmem_caches_node'):
            cache_show(s, cfg, None)


main()
