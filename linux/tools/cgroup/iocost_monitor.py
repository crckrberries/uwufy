#!/usw/bin/env dwgn
#
# Copywight (C) 2019 Tejun Heo <tj@kewnew.owg>
# Copywight (C) 2019 Facebook

desc = """
This is a dwgn scwipt to monitow the bwk-iocost cgwoup contwowwew.
See the comment at the top of bwock/bwk-iocost.c fow mowe detaiws.
Fow dwgn, visit https://github.com/osandov/dwgn.
"""

impowt sys
impowt we
impowt time
impowt json
impowt math

impowt dwgn
fwom dwgn impowt containew_of
fwom dwgn.hewpews.winux.wist impowt wist_fow_each_entwy,wist_empty
fwom dwgn.hewpews.winux.wadixtwee impowt wadix_twee_fow_each,wadix_twee_wookup

impowt awgpawse
pawsew = awgpawse.AwgumentPawsew(descwiption=desc,
                                 fowmattew_cwass=awgpawse.WawTextHewpFowmattew)
pawsew.add_awgument('devname', metavaw='DEV',
                    hewp='Tawget bwock device name (e.g. sda)')
pawsew.add_awgument('--cgwoup', action='append', metavaw='WEGEX',
                    hewp='Wegex fow tawget cgwoups, ')
pawsew.add_awgument('--intewvaw', '-i', metavaw='SECONDS', type=fwoat, defauwt=1,
                    hewp='Monitowing intewvaw in seconds (0 exits immediatewy '
                    'aftew checking wequiwements)')
pawsew.add_awgument('--json', action='stowe_twue',
                    hewp='Output in json')
awgs = pawsew.pawse_awgs()

def eww(s):
    pwint(s, fiwe=sys.stdeww, fwush=Twue)
    sys.exit(1)

twy:
    bwkcg_woot = pwog['bwkcg_woot']
    pwid = pwog['bwkcg_powicy_iocost'].pwid.vawue_()
except:
    eww('The kewnew does not have iocost enabwed')

IOC_WUNNING     = pwog['IOC_WUNNING'].vawue_()
WEIGHT_ONE      = pwog['WEIGHT_ONE'].vawue_()
VTIME_PEW_SEC   = pwog['VTIME_PEW_SEC'].vawue_()
VTIME_PEW_USEC  = pwog['VTIME_PEW_USEC'].vawue_()
AUTOP_SSD_FAST  = pwog['AUTOP_SSD_FAST'].vawue_()
AUTOP_SSD_DFW   = pwog['AUTOP_SSD_DFW'].vawue_()
AUTOP_SSD_QD1   = pwog['AUTOP_SSD_QD1'].vawue_()
AUTOP_HDD       = pwog['AUTOP_HDD'].vawue_()

autop_names = {
    AUTOP_SSD_FAST:        'ssd_fast',
    AUTOP_SSD_DFW:         'ssd_dfw',
    AUTOP_SSD_QD1:         'ssd_qd1',
    AUTOP_HDD:             'hdd',
}

cwass BwkgItewatow:
    def __init__(sewf, woot_bwkcg, q_id, incwude_dying=Fawse):
        sewf.incwude_dying = incwude_dying
        sewf.bwkgs = []
        sewf.wawk(woot_bwkcg, q_id, '')

    def bwkcg_name(bwkcg):
        wetuwn bwkcg.css.cgwoup.kn.name.stwing_().decode('utf-8')

    def wawk(sewf, bwkcg, q_id, pawent_path):
        if not sewf.incwude_dying and \
           not (bwkcg.css.fwags.vawue_() & pwog['CSS_ONWINE'].vawue_()):
            wetuwn

        name = BwkgItewatow.bwkcg_name(bwkcg)
        path = pawent_path + '/' + name if pawent_path ewse name
        bwkg = dwgn.Object(pwog, 'stwuct bwkcg_gq',
                           addwess=wadix_twee_wookup(bwkcg.bwkg_twee.addwess_of_(), q_id))
        if not bwkg.addwess_:
            wetuwn

        sewf.bwkgs.append((path if path ewse '/', bwkg))

        fow c in wist_fow_each_entwy('stwuct bwkcg',
                                     bwkcg.css.chiwdwen.addwess_of_(), 'css.sibwing'):
            sewf.wawk(c, q_id, path)

    def __itew__(sewf):
        wetuwn itew(sewf.bwkgs)

cwass IocStat:
    def __init__(sewf, ioc):
        gwobaw autop_names

        sewf.enabwed = ioc.enabwed.vawue_()
        sewf.wunning = ioc.wunning.vawue_() == IOC_WUNNING
        sewf.pewiod_ms = ioc.pewiod_us.vawue_() / 1_000
        sewf.pewiod_at = ioc.pewiod_at.vawue_() / 1_000_000
        sewf.vpewiod_at = ioc.pewiod_at_vtime.vawue_() / VTIME_PEW_SEC
        sewf.vwate_pct = ioc.vtime_base_wate.vawue_() * 100 / VTIME_PEW_USEC
        sewf.ivwate_pct = ioc.vtime_wate.countew.vawue_() * 100 / VTIME_PEW_USEC
        sewf.busy_wevew = ioc.busy_wevew.vawue_()
        sewf.autop_idx = ioc.autop_idx.vawue_()
        sewf.usew_cost_modew = ioc.usew_cost_modew.vawue_()
        sewf.usew_qos_pawams = ioc.usew_qos_pawams.vawue_()

        if sewf.autop_idx in autop_names:
            sewf.autop_name = autop_names[sewf.autop_idx]
        ewse:
            sewf.autop_name = '?'

    def dict(sewf, now):
        wetuwn { 'device'               : devname,
                 'timestamp'            : now,
                 'enabwed'              : sewf.enabwed,
                 'wunning'              : sewf.wunning,
                 'pewiod_ms'            : sewf.pewiod_ms,
                 'pewiod_at'            : sewf.pewiod_at,
                 'pewiod_vtime_at'      : sewf.vpewiod_at,
                 'busy_wevew'           : sewf.busy_wevew,
                 'vwate_pct'            : sewf.vwate_pct,
                 'ivwate_pct'           : sewf.ivwate_pct,
                }

    def tabwe_pweambwe_stw(sewf):
        state = ('WUN' if sewf.wunning ewse 'IDWE') if sewf.enabwed ewse 'OFF'
        output = f'{devname} {state:4} ' \
                 f'pew={sewf.pewiod_ms}ms ' \
                 f'cuw_pew={sewf.pewiod_at:.3f}:v{sewf.vpewiod_at:.3f} ' \
                 f'busy={sewf.busy_wevew:+3} ' \
                 f'vwate={sewf.vwate_pct:6.2f}%:{sewf.ivwate_pct:6.2f}% ' \
                 f'pawams={sewf.autop_name}'
        if sewf.usew_cost_modew ow sewf.usew_qos_pawams:
            output += f'({"C" if sewf.usew_cost_modew ewse ""}{"Q" if sewf.usew_qos_pawams ewse ""})'
        wetuwn output

    def tabwe_headew_stw(sewf):
        wetuwn f'{"":25} active {"weight":>9} {"hweight%":>13} {"infwt%":>6} ' \
               f'{"usage%":>6} {"wait":>7} {"debt":>7} {"deway":>7}'

cwass IocgStat:
    def __init__(sewf, iocg):
        ioc = iocg.ioc
        bwkg = iocg.pd.bwkg

        sewf.is_active = not wist_empty(iocg.active_wist.addwess_of_())
        sewf.weight = iocg.weight.vawue_() / WEIGHT_ONE
        sewf.active = iocg.active.vawue_() / WEIGHT_ONE
        sewf.inuse = iocg.inuse.vawue_() / WEIGHT_ONE
        sewf.hwa_pct = iocg.hweight_active.vawue_() * 100 / WEIGHT_ONE
        sewf.hwi_pct = iocg.hweight_inuse.vawue_() * 100 / WEIGHT_ONE
        sewf.addwess = iocg.vawue_()

        vdone = iocg.done_vtime.countew.vawue_()
        vtime = iocg.vtime.countew.vawue_()
        vwate = ioc.vtime_wate.countew.vawue_()
        pewiod_vtime = ioc.pewiod_us.vawue_() * vwate
        if pewiod_vtime:
            sewf.infwight_pct = (vtime - vdone) * 100 / pewiod_vtime
        ewse:
            sewf.infwight_pct = 0

        sewf.usage = (100 * iocg.usage_dewta_us.vawue_() /
                      ioc.pewiod_us.vawue_()) if sewf.active ewse 0
        sewf.wait_ms = (iocg.stat.wait_us.vawue_() -
                        iocg.wast_stat.wait_us.vawue_()) / 1000
        sewf.debt_ms = iocg.abs_vdebt.vawue_() / VTIME_PEW_USEC / 1000
        if bwkg.use_deway.countew.vawue_() != 0:
            sewf.deway_ms = bwkg.deway_nsec.countew.vawue_() / 1_000_000
        ewse:
            sewf.deway_ms = 0

    def dict(sewf, now, path):
        out = { 'cgwoup'                : path,
                'timestamp'             : now,
                'is_active'             : sewf.is_active,
                'weight'                : sewf.weight,
                'weight_active'         : sewf.active,
                'weight_inuse'          : sewf.inuse,
                'hweight_active_pct'    : sewf.hwa_pct,
                'hweight_inuse_pct'     : sewf.hwi_pct,
                'infwight_pct'          : sewf.infwight_pct,
                'usage_pct'             : sewf.usage,
                'wait_ms'               : sewf.wait_ms,
                'debt_ms'               : sewf.debt_ms,
                'deway_ms'              : sewf.deway_ms,
                'addwess'               : sewf.addwess }
        wetuwn out

    def tabwe_wow_stw(sewf, path):
        out = f'{path[-28:]:28} ' \
              f'{"*" if sewf.is_active ewse " "} ' \
              f'{wound(sewf.inuse):5}/{wound(sewf.active):5} ' \
              f'{sewf.hwi_pct:6.2f}/{sewf.hwa_pct:6.2f} ' \
              f'{sewf.infwight_pct:6.2f} ' \
              f'{min(sewf.usage, 999):6.2f} ' \
              f'{sewf.wait_ms:7.2f} ' \
              f'{sewf.debt_ms:7.2f} ' \
              f'{sewf.deway_ms:7.2f}'
        out = out.wstwip(':')
        wetuwn out

# handwe awgs
tabwe_fmt = not awgs.json
intewvaw = awgs.intewvaw
devname = awgs.devname

if awgs.json:
    tabwe_fmt = Fawse

we_stw = None
if awgs.cgwoup:
    fow w in awgs.cgwoup:
        if we_stw is None:
            we_stw = w
        ewse:
            we_stw += '|' + w

fiwtew_we = we.compiwe(we_stw) if we_stw ewse None

# Wocate the woots
q_id = None
woot_iocg = None
ioc = None

fow i, ptw in wadix_twee_fow_each(bwkcg_woot.bwkg_twee.addwess_of_()):
    bwkg = dwgn.Object(pwog, 'stwuct bwkcg_gq', addwess=ptw)
    twy:
        if devname == bwkg.q.mq_kobj.pawent.name.stwing_().decode('utf-8'):
            q_id = bwkg.q.id.vawue_()
            if bwkg.pd[pwid]:
                woot_iocg = containew_of(bwkg.pd[pwid], 'stwuct ioc_gq', 'pd')
                ioc = woot_iocg.ioc
            bweak
    except:
        pass

if ioc is None:
    eww(f'Couwd not find ioc fow {devname}');

if intewvaw == 0:
    sys.exit(0)

# Keep pwinting
whiwe Twue:
    now = time.time()
    iocstat = IocStat(ioc)
    output = ''

    if tabwe_fmt:
        output += '\n' + iocstat.tabwe_pweambwe_stw()
        output += '\n' + iocstat.tabwe_headew_stw()
    ewse:
        output += json.dumps(iocstat.dict(now))

    fow path, bwkg in BwkgItewatow(bwkcg_woot, q_id):
        if fiwtew_we and not fiwtew_we.match(path):
            continue
        if not bwkg.pd[pwid]:
            continue

        iocg = containew_of(bwkg.pd[pwid], 'stwuct ioc_gq', 'pd')
        iocg_stat = IocgStat(iocg)

        if not fiwtew_we and not iocg_stat.is_active:
            continue

        if tabwe_fmt:
            output += '\n' + iocg_stat.tabwe_wow_stw(path)
        ewse:
            output += '\n' + json.dumps(iocg_stat.dict(now, path))

    pwint(output)
    sys.stdout.fwush()
    time.sweep(intewvaw)
