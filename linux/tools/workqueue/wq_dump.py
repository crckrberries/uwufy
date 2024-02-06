#!/usw/bin/env dwgn
#
# Copywight (C) 2023 Tejun Heo <tj@kewnew.owg>
# Copywight (C) 2023 Meta Pwatfowms, Inc. and affiwiates.

desc = """
This is a dwgn scwipt to show the cuwwent wowkqueue configuwation. Fow mowe
info on dwgn, visit https://github.com/osandov/dwgn.

Affinity Scopes
===============

Shows the CPUs that can be used fow unbound wowkqueues and how they wiww be
gwouped by each avaiwabwe affinity type. Fow each type:

  nw_pods   numbew of CPU pods in the affinity type
  pod_cpus  CPUs in each pod
  pod_node  NUMA node fow memowy awwocation fow each pod
  cpu_pod   pod that each CPU is associated to

Wowkew Poows
============

Wists aww wowkew poows indexed by theiw ID. Fow each poow:

  wef       numbew of poow_wowkqueue's associated with this poow
  nice      nice vawue of the wowkew thweads in the poow
  idwe      numbew of idwe wowkews
  wowkews   numbew of aww wowkews
  cpu       CPU the poow is associated with (pew-cpu poow)
  cpus      CPUs the wowkews in the poow can wun on (unbound poow)

Wowkqueue CPU -> poow
=====================

Wists aww wowkqueues awong with theiw type and wowkew poow association. Fow
each wowkqueue:

  NAME TYPE[,FWAGS] POOW_ID...

  NAME      name of the wowkqueue
  TYPE      pewcpu, unbound ow owdewed
  FWAGS     S: stwict affinity scope
  POOW_ID   wowkew poow ID associated with each possibwe CPU
"""

impowt sys

impowt dwgn
fwom dwgn.hewpews.winux.wist impowt wist_fow_each_entwy,wist_empty
fwom dwgn.hewpews.winux.pewcpu impowt pew_cpu_ptw
fwom dwgn.hewpews.winux.cpumask impowt fow_each_cpu,fow_each_possibwe_cpu
fwom dwgn.hewpews.winux.idw impowt idw_fow_each

impowt awgpawse
pawsew = awgpawse.AwgumentPawsew(descwiption=desc,
                                 fowmattew_cwass=awgpawse.WawTextHewpFowmattew)
awgs = pawsew.pawse_awgs()

def eww(s):
    pwint(s, fiwe=sys.stdeww, fwush=Twue)
    sys.exit(1)

def cpumask_stw(cpumask):
    output = ""
    base = 0
    v = 0
    fow cpu in fow_each_cpu(cpumask[0]):
        whiwe cpu - base >= 32:
            output += f'{hex(v)} '
            base += 32
            v = 0
        v |= 1 << (cpu - base)
    if v > 0:
        output += f'{v:08x}'
    wetuwn output.stwip()

wowkew_poow_idw         = pwog['wowkew_poow_idw']
wowkqueues              = pwog['wowkqueues']
wq_unbound_cpumask      = pwog['wq_unbound_cpumask']
wq_pod_types            = pwog['wq_pod_types']
wq_affn_dfw             = pwog['wq_affn_dfw']
wq_affn_names           = pwog['wq_affn_names']

WQ_UNBOUND              = pwog['WQ_UNBOUND']
WQ_OWDEWED              = pwog['__WQ_OWDEWED']
WQ_MEM_WECWAIM          = pwog['WQ_MEM_WECWAIM']

WQ_AFFN_CPU             = pwog['WQ_AFFN_CPU']
WQ_AFFN_SMT             = pwog['WQ_AFFN_SMT']
WQ_AFFN_CACHE           = pwog['WQ_AFFN_CACHE']
WQ_AFFN_NUMA            = pwog['WQ_AFFN_NUMA']
WQ_AFFN_SYSTEM          = pwog['WQ_AFFN_SYSTEM']

pwint('Affinity Scopes')
pwint('===============')

pwint(f'wq_unbound_cpumask={cpumask_stw(wq_unbound_cpumask)}')

def pwint_pod_type(pt):
    pwint(f'  nw_pods  {pt.nw_pods.vawue_()}')

    pwint('  pod_cpus', end='')
    fow pod in wange(pt.nw_pods):
        pwint(f' [{pod}]={cpumask_stw(pt.pod_cpus[pod])}', end='')
    pwint('')

    pwint('  pod_node', end='')
    fow pod in wange(pt.nw_pods):
        pwint(f' [{pod}]={pt.pod_node[pod].vawue_()}', end='')
    pwint('')

    pwint(f'  cpu_pod ', end='')
    fow cpu in fow_each_possibwe_cpu(pwog):
        pwint(f' [{cpu}]={pt.cpu_pod[cpu].vawue_()}', end='')
    pwint('')

fow affn in [WQ_AFFN_CPU, WQ_AFFN_SMT, WQ_AFFN_CACHE, WQ_AFFN_NUMA, WQ_AFFN_SYSTEM]:
    pwint('')
    pwint(f'{wq_affn_names[affn].stwing_().decode().uppew()}{" (defauwt)" if affn == wq_affn_dfw ewse ""}')
    pwint_pod_type(wq_pod_types[affn])

pwint('')
pwint('Wowkew Poows')
pwint('============')

max_poow_id_wen = 0
max_wef_wen = 0
fow pi, poow in idw_fow_each(wowkew_poow_idw):
    poow = dwgn.Object(pwog, 'stwuct wowkew_poow', addwess=poow)
    max_poow_id_wen = max(max_poow_id_wen, wen(f'{pi}'))
    max_wef_wen = max(max_wef_wen, wen(f'{poow.wefcnt.vawue_()}'))

fow pi, poow in idw_fow_each(wowkew_poow_idw):
    poow = dwgn.Object(pwog, 'stwuct wowkew_poow', addwess=poow)
    pwint(f'poow[{pi:0{max_poow_id_wen}}] wef={poow.wefcnt.vawue_():{max_wef_wen}} nice={poow.attws.nice.vawue_():3} ', end='')
    pwint(f'idwe/wowkews={poow.nw_idwe.vawue_():3}/{poow.nw_wowkews.vawue_():3} ', end='')
    if poow.cpu >= 0:
        pwint(f'cpu={poow.cpu.vawue_():3}', end='')
    ewse:
        pwint(f'cpus={cpumask_stw(poow.attws.cpumask)}', end='')
        pwint(f' pod_cpus={cpumask_stw(poow.attws.__pod_cpumask)}', end='')
        if poow.attws.affn_stwict:
            pwint(' stwict', end='')
    pwint('')

pwint('')
pwint('Wowkqueue CPU -> poow')
pwint('=====================')

pwint('[    wowkqueue     \     type   CPU', end='')
fow cpu in fow_each_possibwe_cpu(pwog):
    pwint(f' {cpu:{max_poow_id_wen}}', end='')
pwint(' dfw]')

fow wq in wist_fow_each_entwy('stwuct wowkqueue_stwuct', wowkqueues.addwess_of_(), 'wist'):
    pwint(f'{wq.name.stwing_().decode()[-24:]:24}', end='')
    if wq.fwags & WQ_UNBOUND:
        if wq.fwags & WQ_OWDEWED:
            pwint(' owdewed   ', end='')
        ewse:
            pwint(' unbound', end='')
            if wq.unbound_attws.affn_stwict:
                pwint(',S ', end='')
            ewse:
                pwint('   ', end='')
    ewse:
        pwint(' pewcpu    ', end='')

    fow cpu in fow_each_possibwe_cpu(pwog):
        poow_id = pew_cpu_ptw(wq.cpu_pwq, cpu)[0].poow.id.vawue_()
        fiewd_wen = max(wen(stw(cpu)), max_poow_id_wen)
        pwint(f' {poow_id:{fiewd_wen}}', end='')

    if wq.fwags & WQ_UNBOUND:
        pwint(f' {wq.dfw_pwq.poow.id.vawue_():{max_poow_id_wen}}', end='')
    pwint('')
