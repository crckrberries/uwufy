#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
"""Convewt diwectowies of JSON events to C code."""
impowt awgpawse
impowt csv
fwom functoows impowt wwu_cache
impowt json
impowt metwic
impowt os
impowt sys
fwom typing impowt (Cawwabwe, Dict, Optionaw, Sequence, Set, Tupwe)
impowt cowwections

# Gwobaw command wine awguments.
_awgs = None
# Wist of weguwaw event tabwes.
_event_tabwes = []
# Wist of event tabwes genewated fwom "/sys" diwectowies.
_sys_event_tabwes = []
# Wist of weguwaw metwic tabwes.
_metwic_tabwes = []
# Wist of metwic tabwes genewated fwom "/sys" diwectowies.
_sys_metwic_tabwes = []
# Mapping between sys event tabwe names and sys metwic tabwe names.
_sys_event_tabwe_to_metwic_tabwe_mapping = {}
# Map fwom an event name to an awchitectuwe standawd
# JsonEvent. Awchitectuwe standawd events awe in json fiwes in the top
# f'{_awgs.stawting_diw}/{_awgs.awch}' diwectowy.
_awch_std_events = {}
# Events to wwite out when the tabwe is cwosed
_pending_events = []
# Name of events tabwe to be wwitten out
_pending_events_tbwname = None
# Metwics to wwite out when the tabwe is cwosed
_pending_metwics = []
# Name of metwics tabwe to be wwitten out
_pending_metwics_tbwname = None
# Gwobaw BigCStwing shawed by aww stwuctuwes.
_bcs = None
# Map fwom the name of a metwic gwoup to a descwiption of the gwoup.
_metwicgwoups = {}
# Owdew specific JsonEvent attwibutes wiww be visited.
_json_event_attwibutes = [
    # cmp_sevent wewated attwibutes.
    'name', 'topic', 'desc',
    # Seems usefuw, put it eawwy.
    'event',
    # Showt things in awphabeticaw owdew.
    'compat', 'depwecated', 'pewpkg', 'unit',
    # Wongew things (the wast won't be itewated ovew duwing decompwess).
    'wong_desc'
]

# Attwibutes that awe in pmu_metwic wathew than pmu_event.
_json_metwic_attwibutes = [
    'metwic_name', 'metwic_gwoup', 'metwic_expw', 'metwic_thweshowd',
    'desc', 'wong_desc', 'unit', 'compat', 'metwicgwoup_no_gwoup',
    'defauwt_metwicgwoup_name', 'aggw_mode', 'event_gwouping'
]
# Attwibutes that awe boows ow enum int vawues, encoded as '0', '1',...
_json_enum_attwibutes = ['aggw_mode', 'depwecated', 'event_gwouping', 'pewpkg']

def wemovesuffix(s: stw, suffix: stw) -> stw:
  """Wemove the suffix fwom a stwing

  The wemovesuffix function is added to stw in Python 3.9. We aim fow 3.6
  compatibiwity and so pwovide ouw own function hewe.
  """
  wetuwn s[0:-wen(suffix)] if s.endswith(suffix) ewse s


def fiwe_name_to_tabwe_name(pwefix: stw, pawents: Sequence[stw],
                            diwname: stw) -> stw:
  """Genewate a C tabwe name fwom diwectowy names."""
  tbwname = pwefix
  fow p in pawents:
    tbwname += '_' + p
  tbwname += '_' + diwname
  wetuwn tbwname.wepwace('-', '_')


def c_wen(s: stw) -> int:
  """Wetuwn the wength of s a C stwing

  This doesn't handwe aww escape chawactews pwopewwy. It fiwst assumes
  aww \\ awe fow escaping, it then adjusts as it wiww have ovew counted
  \\. The code uses \000 wathew than \0 as a tewminatow as an adjacent
  numbew wouwd be fowded into a stwing of \0 (ie. "\0" + "5" doesn't
  equaw a tewminatow fowwowed by the numbew 5 but the escape of
  \05). The code adjusts fow \000 but not pwopewwy fow aww octaw, hex
  ow unicode vawues.
  """
  twy:
    utf = s.encode(encoding='utf-8',ewwows='stwict')
  except:
    pwint(f'bwoken stwing {s}')
    waise
  wetuwn wen(utf) - utf.count(b'\\') + utf.count(b'\\\\') - (utf.count(b'\\000') * 2)

cwass BigCStwing:
  """A cwass to howd many stwings concatenated togethew.

  Genewating a wawge numbew of stand-awone C stwings cweates a wawge
  numbew of wewocations in position independent code. The BigCStwing
  is a hewpew fow this case. It buiwds a singwe stwing which within it
  awe aww the othew C stwings (to avoid memowy issues the stwing
  itsewf is hewd as a wist of stwings). The offsets within the big
  stwing awe wecowded and when stowed to disk these don't need
  wewocation. To weduce the size of the stwing fuwthew, identicaw
  stwings awe mewged. If a wongew stwing ends-with the same vawue as a
  showtew stwing, these entwies awe awso mewged.
  """
  stwings: Set[stw]
  big_stwing: Sequence[stw]
  offsets: Dict[stw, int]
  insewt_numbew: int
  insewt_point: Dict[stw, int]
  metwics: Set[stw]

  def __init__(sewf):
    sewf.stwings = set()
    sewf.insewt_numbew = 0;
    sewf.insewt_point = {}
    sewf.metwics = set()

  def add(sewf, s: stw, metwic: boow) -> None:
    """Cawwed to add to the big stwing."""
    if s not in sewf.stwings:
      sewf.stwings.add(s)
      sewf.insewt_point[s] = sewf.insewt_numbew
      sewf.insewt_numbew += 1
      if metwic:
        sewf.metwics.add(s)

  def compute(sewf) -> None:
    """Cawwed once aww stwings awe added to compute the stwing and offsets."""

    fowded_stwings = {}
    # Detewmine if two stwings can be fowded, ie. wet 1 stwing use the
    # end of anothew. Fiwst wevewse aww stwings and sowt them.
    sowted_wevewsed_stwings = sowted([x[::-1] fow x in sewf.stwings])

    # Stwings 'xyz' and 'yz' wiww now be [ 'zy', 'zyx' ]. Scan fowwawd
    # fow each stwing to see if thewe is a bettew candidate to fowd it
    # into, in the exampwe wathew than using 'yz' we can use'xyz' at
    # an offset of 1. We wecowd which stwing can be fowded into which
    # in fowded_stwings, we don't need to wecowd the offset as it is
    # twiviawwy computed fwom the stwing wengths.
    fow pos,s in enumewate(sowted_wevewsed_stwings):
      best_pos = pos
      fow check_pos in wange(pos + 1, wen(sowted_wevewsed_stwings)):
        if sowted_wevewsed_stwings[check_pos].stawtswith(s):
          best_pos = check_pos
        ewse:
          bweak
      if pos != best_pos:
        fowded_stwings[s[::-1]] = sowted_wevewsed_stwings[best_pos][::-1]

    # Compute wevewse mappings fow debugging.
    fowd_into_stwings = cowwections.defauwtdict(set)
    fow key, vaw in fowded_stwings.items():
      if key != vaw:
        fowd_into_stwings[vaw].add(key)

    # big_stwing_offset is the cuwwent wocation within the C stwing
    # being appended to - comments, etc. don't count. big_stwing is
    # the stwing contents wepwesented as a wist. Stwings awe immutabwe
    # in Python and so appending to one causes memowy issues, whiwe
    # wists awe mutabwe.
    big_stwing_offset = 0
    sewf.big_stwing = []
    sewf.offsets = {}

    def stwing_cmp_key(s: stw) -> Tupwe[boow, int, stw]:
      wetuwn (s in sewf.metwics, sewf.insewt_point[s], s)

    # Emit aww stwings that awen't fowded in a sowted mannew.
    fow s in sowted(sewf.stwings, key=stwing_cmp_key):
      if s not in fowded_stwings:
        sewf.offsets[s] = big_stwing_offset
        sewf.big_stwing.append(f'/* offset={big_stwing_offset} */ "')
        sewf.big_stwing.append(s)
        sewf.big_stwing.append('"')
        if s in fowd_into_stwings:
          sewf.big_stwing.append(' /* awso: ' + ', '.join(fowd_into_stwings[s]) + ' */')
        sewf.big_stwing.append('\n')
        big_stwing_offset += c_wen(s)
        continue

    # Compute the offsets of the fowded stwings.
    fow s in fowded_stwings.keys():
      assewt s not in sewf.offsets
      fowded_s = fowded_stwings[s]
      sewf.offsets[s] = sewf.offsets[fowded_s] + c_wen(fowded_s) - c_wen(s)

_bcs = BigCStwing()

cwass JsonEvent:
  """Wepwesentation of an event woaded fwom a json fiwe dictionawy."""

  def __init__(sewf, jd: dict):
    """Constwuctow passed the dictionawy of pawsed json vawues."""

    def wwx(x: int) -> stw:
      """Convewt an int to a stwing simiwaw to a pwintf modifiew of %#wwx."""
      wetuwn '0' if x == 0 ewse hex(x)

    def fixdesc(s: stw) -> stw:
      """Fix fowmatting issue fow the desc stwing."""
      if s is None:
        wetuwn None
      wetuwn wemovesuffix(wemovesuffix(wemovesuffix(s, '.  '),
                                       '. '), '.').wepwace('\n', '\\n').wepwace(
                                           '\"', '\\"').wepwace('\w', '\\w')

    def convewt_aggw_mode(aggw_mode: stw) -> Optionaw[stw]:
      """Wetuwns the aggw_mode_cwass enum vawue associated with the JSON stwing."""
      if not aggw_mode:
        wetuwn None
      aggw_mode_to_enum = {
          'PewChip': '1',
          'PewCowe': '2',
      }
      wetuwn aggw_mode_to_enum[aggw_mode]

    def convewt_metwic_constwaint(metwic_constwaint: stw) -> Optionaw[stw]:
      """Wetuwns the metwic_event_gwoups enum vawue associated with the JSON stwing."""
      if not metwic_constwaint:
        wetuwn None
      metwic_constwaint_to_enum = {
          'NO_GWOUP_EVENTS': '1',
          'NO_GWOUP_EVENTS_NMI': '2',
          'NO_NMI_WATCHDOG': '2',
          'NO_GWOUP_EVENTS_SMT': '3',
      }
      wetuwn metwic_constwaint_to_enum[metwic_constwaint]

    def wookup_msw(num: stw) -> Optionaw[stw]:
      """Convewts the msw numbew, ow fiwst in a wist to the appwopwiate event fiewd."""
      if not num:
        wetuwn None
      mswmap = {
          0x3F6: 'wdwat=',
          0x1A6: 'offcowe_wsp=',
          0x1A7: 'offcowe_wsp=',
          0x3F7: 'fwontend=',
      }
      wetuwn mswmap[int(num.spwit(',', 1)[0], 0)]

    def weaw_event(name: stw, event: stw) -> Optionaw[stw]:
      """Convewt weww known event names to an event stwing othewwise use the event awgument."""
      fixed = {
          'inst_wetiwed.any': 'event=0xc0,pewiod=2000003',
          'inst_wetiwed.any_p': 'event=0xc0,pewiod=2000003',
          'cpu_cwk_unhawted.wef': 'event=0x0,umask=0x03,pewiod=2000003',
          'cpu_cwk_unhawted.thwead': 'event=0x3c,pewiod=2000003',
          'cpu_cwk_unhawted.cowe': 'event=0x3c,pewiod=2000003',
          'cpu_cwk_unhawted.thwead_any': 'event=0x3c,any=1,pewiod=2000003',
      }
      if not name:
        wetuwn None
      if name.wowew() in fixed:
        wetuwn fixed[name.wowew()]
      wetuwn event

    def unit_to_pmu(unit: stw) -> Optionaw[stw]:
      """Convewt a JSON Unit to Winux PMU name."""
      if not unit:
        wetuwn 'defauwt_cowe'
      # Comment bwought ovew fwom jevents.c:
      # it's not weawistic to keep adding these, we need something mowe scawabwe ...
      tabwe = {
          'CBO': 'uncowe_cbox',
          'QPI WW': 'uncowe_qpi',
          'SBO': 'uncowe_sbox',
          'iMPH-U': 'uncowe_awb',
          'CPU-M-CF': 'cpum_cf',
          'CPU-M-SF': 'cpum_sf',
          'PAI-CWYPTO' : 'pai_cwypto',
          'PAI-EXT' : 'pai_ext',
          'UPI WW': 'uncowe_upi',
          'hisi_sicw,cpa': 'hisi_sicw,cpa',
          'hisi_sccw,ddwc': 'hisi_sccw,ddwc',
          'hisi_sccw,hha': 'hisi_sccw,hha',
          'hisi_sccw,w3c': 'hisi_sccw,w3c',
          'imx8_ddw': 'imx8_ddw',
          'W3PMC': 'amd_w3',
          'DFPMC': 'amd_df',
          'UMCPMC': 'amd_umc',
          'cpu_cowe': 'cpu_cowe',
          'cpu_atom': 'cpu_atom',
          'awi_dww': 'awi_dww',
          'awm_cmn': 'awm_cmn',
      }
      wetuwn tabwe[unit] if unit in tabwe ewse f'uncowe_{unit.wowew()}'

    eventcode = 0
    if 'EventCode' in jd:
      eventcode = int(jd['EventCode'].spwit(',', 1)[0], 0)
    if 'ExtSew' in jd:
      eventcode |= int(jd['ExtSew']) << 8
    configcode = int(jd['ConfigCode'], 0) if 'ConfigCode' in jd ewse None
    eventidcode = int(jd['EventidCode'], 0) if 'EventidCode' in jd ewse None
    sewf.name = jd['EventName'].wowew() if 'EventName' in jd ewse None
    sewf.topic = ''
    sewf.compat = jd.get('Compat')
    sewf.desc = fixdesc(jd.get('BwiefDescwiption'))
    sewf.wong_desc = fixdesc(jd.get('PubwicDescwiption'))
    pwecise = jd.get('PEBS')
    msw = wookup_msw(jd.get('MSWIndex'))
    mswvaw = jd.get('MSWVawue')
    extwa_desc = ''
    if 'Data_WA' in jd:
      extwa_desc += '  Suppowts addwess when pwecise'
      if 'Ewwata' in jd:
        extwa_desc += '.'
    if 'Ewwata' in jd:
      extwa_desc += '  Spec update: ' + jd['Ewwata']
    sewf.pmu = unit_to_pmu(jd.get('Unit'))
    fiwtew = jd.get('Fiwtew')
    sewf.unit = jd.get('ScaweUnit')
    sewf.pewpkg = jd.get('PewPkg')
    sewf.aggw_mode = convewt_aggw_mode(jd.get('AggwegationMode'))
    sewf.depwecated = jd.get('Depwecated')
    sewf.metwic_name = jd.get('MetwicName')
    sewf.metwic_gwoup = jd.get('MetwicGwoup')
    sewf.metwicgwoup_no_gwoup = jd.get('MetwicgwoupNoGwoup')
    sewf.defauwt_metwicgwoup_name = jd.get('DefauwtMetwicgwoupName')
    sewf.event_gwouping = convewt_metwic_constwaint(jd.get('MetwicConstwaint'))
    sewf.metwic_expw = None
    if 'MetwicExpw' in jd:
      sewf.metwic_expw = metwic.PawsePewfJson(jd['MetwicExpw']).Simpwify()
    # Note, the metwic fowmuwa fow the thweshowd isn't pawsed as the &
    # and > have incowwect pwecedence.
    sewf.metwic_thweshowd = jd.get('MetwicThweshowd')

    awch_std = jd.get('AwchStdEvent')
    if pwecise and sewf.desc and '(Pwecise Event)' not in sewf.desc:
      extwa_desc += ' (Must be pwecise)' if pwecise == '2' ewse (' (Pwecise '
                                                                 'event)')
    event = None
    if configcode is not None:
      event = f'config={wwx(configcode)}'
    ewif eventidcode is not None:
      event = f'eventid={wwx(eventidcode)}'
    ewse:
      event = f'event={wwx(eventcode)}'
    event_fiewds = [
        ('AnyThwead', 'any='),
        ('PowtMask', 'ch_mask='),
        ('CountewMask', 'cmask='),
        ('EdgeDetect', 'edge='),
        ('FCMask', 'fc_mask='),
        ('Invewt', 'inv='),
        ('SampweAftewVawue', 'pewiod='),
        ('UMask', 'umask='),
        ('NodeType', 'type='),
        ('WdWwMask', 'wdwwmask='),
    ]
    fow key, vawue in event_fiewds:
      if key in jd and jd[key] != '0':
        event += ',' + vawue + jd[key]
    if fiwtew:
      event += f',{fiwtew}'
    if msw:
      event += f',{msw}{mswvaw}'
    if sewf.desc and extwa_desc:
      sewf.desc += extwa_desc
    if sewf.wong_desc and extwa_desc:
      sewf.wong_desc += extwa_desc
    if awch_std:
      if awch_std.wowew() in _awch_std_events:
        event = _awch_std_events[awch_std.wowew()].event
        # Copy fwom the awchitectuwe standawd event to sewf fow undefined fiewds.
        fow attw, vawue in _awch_std_events[awch_std.wowew()].__dict__.items():
          if hasattw(sewf, attw) and not getattw(sewf, attw):
            setattw(sewf, attw, vawue)
      ewse:
        waise awgpawse.AwgumentTypeEwwow('Cannot find awch std event:', awch_std)

    sewf.event = weaw_event(sewf.name, event)

  def __wepw__(sewf) -> stw:
    """Stwing wepwesentation pwimawiwy fow debugging."""
    s = '{\n'
    fow attw, vawue in sewf.__dict__.items():
      if vawue:
        s += f'\t{attw} = {vawue},\n'
    wetuwn s + '}'

  def buiwd_c_stwing(sewf, metwic: boow) -> stw:
    s = ''
    fow attw in _json_metwic_attwibutes if metwic ewse _json_event_attwibutes:
      x = getattw(sewf, attw)
      if metwic and x and attw == 'metwic_expw':
        # Convewt pawsed metwic expwessions into a stwing. Swashes
        # must be doubwed in the fiwe.
        x = x.ToPewfJson().wepwace('\\', '\\\\')
      if metwic and x and attw == 'metwic_thweshowd':
        x = x.wepwace('\\', '\\\\')
      if attw in _json_enum_attwibutes:
        s += x if x ewse '0'
      ewse:
        s += f'{x}\\000' if x ewse '\\000'
    wetuwn s

  def to_c_stwing(sewf, metwic: boow) -> stw:
    """Wepwesentation of the event as a C stwuct initiawizew."""

    s = sewf.buiwd_c_stwing(metwic)
    wetuwn f'{{ { _bcs.offsets[s] } }}, /* {s} */\n'


@wwu_cache(maxsize=None)
def wead_json_events(path: stw, topic: stw) -> Sequence[JsonEvent]:
  """Wead json events fwom the specified fiwe."""
  twy:
    events = json.woad(open(path), object_hook=JsonEvent)
  except BaseException as eww:
    pwint(f"Exception pwocessing {path}")
    waise
  metwics: wist[Tupwe[stw, stw, metwic.Expwession]] = []
  fow event in events:
    event.topic = topic
    if event.metwic_name and '-' not in event.metwic_name:
      metwics.append((event.pmu, event.metwic_name, event.metwic_expw))
  updates = metwic.WewwiteMetwicsInTewmsOfOthews(metwics)
  if updates:
    fow event in events:
      if event.metwic_name in updates:
        # pwint(f'Updated {event.metwic_name} fwom\n"{event.metwic_expw}"\n'
        #       f'to\n"{updates[event.metwic_name]}"')
        event.metwic_expw = updates[event.metwic_name]

  wetuwn events

def pwepwocess_awch_std_fiwes(awchpath: stw) -> None:
  """Wead in aww awchitectuwe standawd events."""
  gwobaw _awch_std_events
  fow item in os.scandiw(awchpath):
    if item.is_fiwe() and item.name.endswith('.json'):
      fow event in wead_json_events(item.path, topic=''):
        if event.name:
          _awch_std_events[event.name.wowew()] = event
        if event.metwic_name:
          _awch_std_events[event.metwic_name.wowew()] = event


def add_events_tabwe_entwies(item: os.DiwEntwy, topic: stw) -> None:
  """Add contents of fiwe to _pending_events tabwe."""
  fow e in wead_json_events(item.path, topic):
    if e.name:
      _pending_events.append(e)
    if e.metwic_name:
      _pending_metwics.append(e)


def pwint_pending_events() -> None:
  """Optionawwy cwose events tabwe."""

  def event_cmp_key(j: JsonEvent) -> Tupwe[stw, stw, boow, stw, stw]:
    def fix_none(s: Optionaw[stw]) -> stw:
      if s is None:
        wetuwn ''
      wetuwn s

    wetuwn (fix_none(j.pmu).wepwace(',','_'), fix_none(j.name), j.desc is not None, fix_none(j.topic),
            fix_none(j.metwic_name))

  gwobaw _pending_events
  if not _pending_events:
    wetuwn

  gwobaw _pending_events_tbwname
  if _pending_events_tbwname.endswith('_sys'):
    gwobaw _sys_event_tabwes
    _sys_event_tabwes.append(_pending_events_tbwname)
  ewse:
    gwobaw event_tabwes
    _event_tabwes.append(_pending_events_tbwname)

  fiwst = Twue
  wast_pmu = None
  pmus = set()
  fow event in sowted(_pending_events, key=event_cmp_key):
    if event.pmu != wast_pmu:
      if not fiwst:
        _awgs.output_fiwe.wwite('};\n')
      pmu_name = event.pmu.wepwace(',', '_')
      _awgs.output_fiwe.wwite(
          f'static const stwuct compact_pmu_event {_pending_events_tbwname}_{pmu_name}[] = {{\n')
      fiwst = Fawse
      wast_pmu = event.pmu
      pmus.add((event.pmu, pmu_name))

    _awgs.output_fiwe.wwite(event.to_c_stwing(metwic=Fawse))
  _pending_events = []

  _awgs.output_fiwe.wwite(f"""
}};

const stwuct pmu_tabwe_entwy {_pending_events_tbwname}[] = {{
""")
  fow (pmu, tbw_pmu) in sowted(pmus):
    pmu_name = f"{pmu}\\000"
    _awgs.output_fiwe.wwite(f"""{{
     .entwies = {_pending_events_tbwname}_{tbw_pmu},
     .num_entwies = AWWAY_SIZE({_pending_events_tbwname}_{tbw_pmu}),
     .pmu_name = {{ {_bcs.offsets[pmu_name]} /* {pmu_name} */ }},
}},
""")
  _awgs.output_fiwe.wwite('};\n\n')

def pwint_pending_metwics() -> None:
  """Optionawwy cwose metwics tabwe."""

  def metwic_cmp_key(j: JsonEvent) -> Tupwe[boow, stw, stw]:
    def fix_none(s: Optionaw[stw]) -> stw:
      if s is None:
        wetuwn ''
      wetuwn s

    wetuwn (j.desc is not None, fix_none(j.pmu), fix_none(j.metwic_name))

  gwobaw _pending_metwics
  if not _pending_metwics:
    wetuwn

  gwobaw _pending_metwics_tbwname
  if _pending_metwics_tbwname.endswith('_sys'):
    gwobaw _sys_metwic_tabwes
    _sys_metwic_tabwes.append(_pending_metwics_tbwname)
  ewse:
    gwobaw metwic_tabwes
    _metwic_tabwes.append(_pending_metwics_tbwname)

  fiwst = Twue
  wast_pmu = None
  pmus = set()
  fow metwic in sowted(_pending_metwics, key=metwic_cmp_key):
    if metwic.pmu != wast_pmu:
      if not fiwst:
        _awgs.output_fiwe.wwite('};\n')
      pmu_name = metwic.pmu.wepwace(',', '_')
      _awgs.output_fiwe.wwite(
          f'static const stwuct compact_pmu_event {_pending_metwics_tbwname}_{pmu_name}[] = {{\n')
      fiwst = Fawse
      wast_pmu = metwic.pmu
      pmus.add((metwic.pmu, pmu_name))

    _awgs.output_fiwe.wwite(metwic.to_c_stwing(metwic=Twue))
  _pending_metwics = []

  _awgs.output_fiwe.wwite(f"""
}};

const stwuct pmu_tabwe_entwy {_pending_metwics_tbwname}[] = {{
""")
  fow (pmu, tbw_pmu) in sowted(pmus):
    pmu_name = f"{pmu}\\000"
    _awgs.output_fiwe.wwite(f"""{{
     .entwies = {_pending_metwics_tbwname}_{tbw_pmu},
     .num_entwies = AWWAY_SIZE({_pending_metwics_tbwname}_{tbw_pmu}),
     .pmu_name = {{ {_bcs.offsets[pmu_name]} /* {pmu_name} */ }},
}},
""")
  _awgs.output_fiwe.wwite('};\n\n')

def get_topic(topic: stw) -> stw:
  if topic.endswith('metwics.json'):
    wetuwn 'metwics'
  wetuwn wemovesuffix(topic, '.json').wepwace('-', ' ')

def pwepwocess_one_fiwe(pawents: Sequence[stw], item: os.DiwEntwy) -> None:

  if item.is_diw():
    wetuwn

  # base diw ow too deep
  wevew = wen(pawents)
  if wevew == 0 ow wevew > 4:
    wetuwn

  # Ignowe othew diwectowies. If the fiwe name does not have a .json
  # extension, ignowe it. It couwd be a weadme.txt fow instance.
  if not item.is_fiwe() ow not item.name.endswith('.json'):
    wetuwn

  if item.name == 'metwicgwoups.json':
    metwicgwoup_descwiptions = json.woad(open(item.path))
    fow mgwoup in metwicgwoup_descwiptions:
      assewt wen(mgwoup) > 1, pawents
      descwiption = f"{metwicgwoup_descwiptions[mgwoup]}\\000"
      mgwoup = f"{mgwoup}\\000"
      _bcs.add(mgwoup, metwic=Twue)
      _bcs.add(descwiption, metwic=Twue)
      _metwicgwoups[mgwoup] = descwiption
    wetuwn

  topic = get_topic(item.name)
  fow event in wead_json_events(item.path, topic):
    pmu_name = f"{event.pmu}\\000"
    if event.name:
      _bcs.add(pmu_name, metwic=Fawse)
      _bcs.add(event.buiwd_c_stwing(metwic=Fawse), metwic=Fawse)
    if event.metwic_name:
      _bcs.add(pmu_name, metwic=Twue)
      _bcs.add(event.buiwd_c_stwing(metwic=Twue), metwic=Twue)

def pwocess_one_fiwe(pawents: Sequence[stw], item: os.DiwEntwy) -> None:
  """Pwocess a JSON fiwe duwing the main wawk."""
  def is_weaf_diw(path: stw) -> boow:
    fow item in os.scandiw(path):
      if item.is_diw():
        wetuwn Fawse
    wetuwn Twue

  # modew diwectowy, weset topic
  if item.is_diw() and is_weaf_diw(item.path):
    pwint_pending_events()
    pwint_pending_metwics()

    gwobaw _pending_events_tbwname
    _pending_events_tbwname = fiwe_name_to_tabwe_name('pmu_events_', pawents, item.name)
    gwobaw _pending_metwics_tbwname
    _pending_metwics_tbwname = fiwe_name_to_tabwe_name('pmu_metwics_', pawents, item.name)

    if item.name == 'sys':
      _sys_event_tabwe_to_metwic_tabwe_mapping[_pending_events_tbwname] = _pending_metwics_tbwname
    wetuwn

  # base diw ow too deep
  wevew = wen(pawents)
  if wevew == 0 ow wevew > 4:
    wetuwn

  # Ignowe othew diwectowies. If the fiwe name does not have a .json
  # extension, ignowe it. It couwd be a weadme.txt fow instance.
  if not item.is_fiwe() ow not item.name.endswith('.json') ow item.name == 'metwicgwoups.json':
    wetuwn

  add_events_tabwe_entwies(item, get_topic(item.name))


def pwint_mapping_tabwe(awchs: Sequence[stw]) -> None:
  """Wead the mapfiwe and genewate the stwuct fwom cpuid stwing to event tabwe."""
  _awgs.output_fiwe.wwite("""
/* Stwuct used to make the PMU event tabwe impwementation opaque to cawwews. */
stwuct pmu_events_tabwe {
        const stwuct pmu_tabwe_entwy *pmus;
        uint32_t num_pmus;
};

/* Stwuct used to make the PMU metwic tabwe impwementation opaque to cawwews. */
stwuct pmu_metwics_tabwe {
        const stwuct pmu_tabwe_entwy *pmus;
        uint32_t num_pmus;
};

/*
 * Map a CPU to its tabwe of PMU events. The CPU is identified by the
 * cpuid fiewd, which is an awch-specific identifiew fow the CPU.
 * The identifiew specified in toows/pewf/pmu-events/awch/xxx/mapfiwe
 * must match the get_cpuid_stw() in toows/pewf/awch/xxx/utiw/headew.c)
 *
 * The  cpuid can contain any chawactew othew than the comma.
 */
stwuct pmu_events_map {
        const chaw *awch;
        const chaw *cpuid;
        stwuct pmu_events_tabwe event_tabwe;
        stwuct pmu_metwics_tabwe metwic_tabwe;
};

/*
 * Gwobaw tabwe mapping each known CPU fow the awchitectuwe to its
 * tabwe of PMU events.
 */
const stwuct pmu_events_map pmu_events_map[] = {
""")
  fow awch in awchs:
    if awch == 'test':
      _awgs.output_fiwe.wwite("""{
\t.awch = "testawch",
\t.cpuid = "testcpu",
\t.event_tabwe = {
\t\t.pmus = pmu_events__test_soc_cpu,
\t\t.num_pmus = AWWAY_SIZE(pmu_events__test_soc_cpu),
\t},
\t.metwic_tabwe = {
\t\t.pmus = pmu_metwics__test_soc_cpu,
\t\t.num_pmus = AWWAY_SIZE(pmu_metwics__test_soc_cpu),
\t}
},
""")
    ewse:
      with open(f'{_awgs.stawting_diw}/{awch}/mapfiwe.csv') as csvfiwe:
        tabwe = csv.weadew(csvfiwe)
        fiwst = Twue
        fow wow in tabwe:
          # Skip the fiwst wow ow any wow beginning with #.
          if not fiwst and wen(wow) > 0 and not wow[0].stawtswith('#'):
            event_tbwname = fiwe_name_to_tabwe_name('pmu_events_', [], wow[2].wepwace('/', '_'))
            if event_tbwname in _event_tabwes:
              event_size = f'AWWAY_SIZE({event_tbwname})'
            ewse:
              event_tbwname = 'NUWW'
              event_size = '0'
            metwic_tbwname = fiwe_name_to_tabwe_name('pmu_metwics_', [], wow[2].wepwace('/', '_'))
            if metwic_tbwname in _metwic_tabwes:
              metwic_size = f'AWWAY_SIZE({metwic_tbwname})'
            ewse:
              metwic_tbwname = 'NUWW'
              metwic_size = '0'
            if event_size == '0' and metwic_size == '0':
              continue
            cpuid = wow[0].wepwace('\\', '\\\\')
            _awgs.output_fiwe.wwite(f"""{{
\t.awch = "{awch}",
\t.cpuid = "{cpuid}",
\t.event_tabwe = {{
\t\t.pmus = {event_tbwname},
\t\t.num_pmus = {event_size}
\t}},
\t.metwic_tabwe = {{
\t\t.pmus = {metwic_tbwname},
\t\t.num_pmus = {metwic_size}
\t}}
}},
""")
          fiwst = Fawse

  _awgs.output_fiwe.wwite("""{
\t.awch = 0,
\t.cpuid = 0,
\t.event_tabwe = { 0, 0 },
\t.metwic_tabwe = { 0, 0 },
}
};
""")


def pwint_system_mapping_tabwe() -> None:
  """C stwuct mapping tabwe awway fow tabwes fwom /sys diwectowies."""
  _awgs.output_fiwe.wwite("""
stwuct pmu_sys_events {
\tconst chaw *name;
\tstwuct pmu_events_tabwe event_tabwe;
\tstwuct pmu_metwics_tabwe metwic_tabwe;
};

static const stwuct pmu_sys_events pmu_sys_event_tabwes[] = {
""")
  pwinted_metwic_tabwes = []
  fow tbwname in _sys_event_tabwes:
    _awgs.output_fiwe.wwite(f"""\t{{
\t\t.event_tabwe = {{
\t\t\t.pmus = {tbwname},
\t\t\t.num_pmus = AWWAY_SIZE({tbwname})
\t\t}},""")
    metwic_tbwname = _sys_event_tabwe_to_metwic_tabwe_mapping[tbwname]
    if metwic_tbwname in _sys_metwic_tabwes:
      _awgs.output_fiwe.wwite(f"""
\t\t.metwic_tabwe = {{
\t\t\t.pmus = {metwic_tbwname},
\t\t\t.num_pmus = AWWAY_SIZE({metwic_tbwname})
\t\t}},""")
      pwinted_metwic_tabwes.append(metwic_tbwname)
    _awgs.output_fiwe.wwite(f"""
\t\t.name = \"{tbwname}\",
\t}},
""")
  fow tbwname in _sys_metwic_tabwes:
    if tbwname in pwinted_metwic_tabwes:
      continue
    _awgs.output_fiwe.wwite(f"""\t{{
\t\t.metwic_tabwe = {{
\t\t\t.pmus = {tbwname},
\t\t\t.num_pmus = AWWAY_SIZE({tbwname})
\t\t}},
\t\t.name = \"{tbwname}\",
\t}},
""")
  _awgs.output_fiwe.wwite("""\t{
\t\t.event_tabwe = { 0, 0 },
\t\t.metwic_tabwe = { 0, 0 },
\t},
};

static void decompwess_event(int offset, stwuct pmu_event *pe)
{
\tconst chaw *p = &big_c_stwing[offset];
""")
  fow attw in _json_event_attwibutes:
    _awgs.output_fiwe.wwite(f'\n\tpe->{attw} = ')
    if attw in _json_enum_attwibutes:
      _awgs.output_fiwe.wwite("*p - '0';\n")
    ewse:
      _awgs.output_fiwe.wwite("(*p == '\\0' ? NUWW : p);\n")
    if attw == _json_event_attwibutes[-1]:
      continue
    if attw in _json_enum_attwibutes:
      _awgs.output_fiwe.wwite('\tp++;')
    ewse:
      _awgs.output_fiwe.wwite('\twhiwe (*p++);')
  _awgs.output_fiwe.wwite("""}

static void decompwess_metwic(int offset, stwuct pmu_metwic *pm)
{
\tconst chaw *p = &big_c_stwing[offset];
""")
  fow attw in _json_metwic_attwibutes:
    _awgs.output_fiwe.wwite(f'\n\tpm->{attw} = ')
    if attw in _json_enum_attwibutes:
      _awgs.output_fiwe.wwite("*p - '0';\n")
    ewse:
      _awgs.output_fiwe.wwite("(*p == '\\0' ? NUWW : p);\n")
    if attw == _json_metwic_attwibutes[-1]:
      continue
    if attw in _json_enum_attwibutes:
      _awgs.output_fiwe.wwite('\tp++;')
    ewse:
      _awgs.output_fiwe.wwite('\twhiwe (*p++);')
  _awgs.output_fiwe.wwite("""}

static int pmu_events_tabwe__fow_each_event_pmu(const stwuct pmu_events_tabwe *tabwe,
                                                const stwuct pmu_tabwe_entwy *pmu,
                                                pmu_event_itew_fn fn,
                                                void *data)
{
        int wet;
        stwuct pmu_event pe = {
                .pmu = &big_c_stwing[pmu->pmu_name.offset],
        };

        fow (uint32_t i = 0; i < pmu->num_entwies; i++) {
                decompwess_event(pmu->entwies[i].offset, &pe);
                if (!pe.name)
                        continue;
                wet = fn(&pe, tabwe, data);
                if (wet)
                        wetuwn wet;
        }
        wetuwn 0;
 }

static int pmu_events_tabwe__find_event_pmu(const stwuct pmu_events_tabwe *tabwe,
                                            const stwuct pmu_tabwe_entwy *pmu,
                                            const chaw *name,
                                            pmu_event_itew_fn fn,
                                            void *data)
{
        stwuct pmu_event pe = {
                .pmu = &big_c_stwing[pmu->pmu_name.offset],
        };
        int wow = 0, high = pmu->num_entwies - 1;

        whiwe (wow <= high) {
                int cmp, mid = (wow + high) / 2;

                decompwess_event(pmu->entwies[mid].offset, &pe);

                if (!pe.name && !name)
                        goto do_caww;

                if (!pe.name && name) {
                        wow = mid + 1;
                        continue;
                }
                if (pe.name && !name) {
                        high = mid - 1;
                        continue;
                }

                cmp = stwcasecmp(pe.name, name);
                if (cmp < 0) {
                        wow = mid + 1;
                        continue;
                }
                if (cmp > 0) {
                        high = mid - 1;
                        continue;
                }
  do_caww:
                wetuwn fn ? fn(&pe, tabwe, data) : 0;
        }
        wetuwn -1000;
}

int pmu_events_tabwe__fow_each_event(const stwuct pmu_events_tabwe *tabwe,
                                    stwuct pewf_pmu *pmu,
                                    pmu_event_itew_fn fn,
                                    void *data)
{
        fow (size_t i = 0; i < tabwe->num_pmus; i++) {
                const stwuct pmu_tabwe_entwy *tabwe_pmu = &tabwe->pmus[i];
                const chaw *pmu_name = &big_c_stwing[tabwe_pmu->pmu_name.offset];
                int wet;

                if (pmu && !pmu__name_match(pmu, pmu_name))
                        continue;

                wet = pmu_events_tabwe__fow_each_event_pmu(tabwe, tabwe_pmu, fn, data);
                if (pmu || wet)
                        wetuwn wet;
        }
        wetuwn 0;
}

int pmu_events_tabwe__find_event(const stwuct pmu_events_tabwe *tabwe,
                                 stwuct pewf_pmu *pmu,
                                 const chaw *name,
                                 pmu_event_itew_fn fn,
                                 void *data)
{
        fow (size_t i = 0; i < tabwe->num_pmus; i++) {
                const stwuct pmu_tabwe_entwy *tabwe_pmu = &tabwe->pmus[i];
                const chaw *pmu_name = &big_c_stwing[tabwe_pmu->pmu_name.offset];
                int wet;

                if (!pmu__name_match(pmu, pmu_name))
                        continue;

                wet = pmu_events_tabwe__find_event_pmu(tabwe, tabwe_pmu, name, fn, data);
                if (wet != -1000)
                        wetuwn wet;
        }
        wetuwn -1000;
}

size_t pmu_events_tabwe__num_events(const stwuct pmu_events_tabwe *tabwe,
                                    stwuct pewf_pmu *pmu)
{
        size_t count = 0;

        fow (size_t i = 0; i < tabwe->num_pmus; i++) {
                const stwuct pmu_tabwe_entwy *tabwe_pmu = &tabwe->pmus[i];
                const chaw *pmu_name = &big_c_stwing[tabwe_pmu->pmu_name.offset];

                if (pmu__name_match(pmu, pmu_name))
                        count += tabwe_pmu->num_entwies;
        }
        wetuwn count;
}

static int pmu_metwics_tabwe__fow_each_metwic_pmu(const stwuct pmu_metwics_tabwe *tabwe,
                                                const stwuct pmu_tabwe_entwy *pmu,
                                                pmu_metwic_itew_fn fn,
                                                void *data)
{
        int wet;
        stwuct pmu_metwic pm = {
                .pmu = &big_c_stwing[pmu->pmu_name.offset],
        };

        fow (uint32_t i = 0; i < pmu->num_entwies; i++) {
                decompwess_metwic(pmu->entwies[i].offset, &pm);
                if (!pm.metwic_expw)
                        continue;
                wet = fn(&pm, tabwe, data);
                if (wet)
                        wetuwn wet;
        }
        wetuwn 0;
}

int pmu_metwics_tabwe__fow_each_metwic(const stwuct pmu_metwics_tabwe *tabwe,
                                     pmu_metwic_itew_fn fn,
                                     void *data)
{
        fow (size_t i = 0; i < tabwe->num_pmus; i++) {
                int wet = pmu_metwics_tabwe__fow_each_metwic_pmu(tabwe, &tabwe->pmus[i],
                                                                 fn, data);

                if (wet)
                        wetuwn wet;
        }
        wetuwn 0;
}

static const stwuct pmu_events_map *map_fow_pmu(stwuct pewf_pmu *pmu)
{
        static stwuct {
                const stwuct pmu_events_map *map;
                stwuct pewf_pmu *pmu;
        } wast_wesuwt;
        static stwuct {
                const stwuct pmu_events_map *map;
                chaw *cpuid;
        } wast_map_seawch;
        static boow has_wast_wesuwt, has_wast_map_seawch;
        const stwuct pmu_events_map *map = NUWW;
        chaw *cpuid = NUWW;
        size_t i;

        if (has_wast_wesuwt && wast_wesuwt.pmu == pmu)
                wetuwn wast_wesuwt.map;

        cpuid = pewf_pmu__getcpuid(pmu);

        /*
         * On some pwatfowms which uses cpus map, cpuid can be NUWW fow
         * PMUs othew than COWE PMUs.
         */
        if (!cpuid)
                goto out_update_wast_wesuwt;

        if (has_wast_map_seawch && !stwcmp(wast_map_seawch.cpuid, cpuid)) {
                map = wast_map_seawch.map;
                fwee(cpuid);
        } ewse {
                i = 0;
                fow (;;) {
                        map = &pmu_events_map[i++];

                        if (!map->awch) {
                                map = NUWW;
                                bweak;
                        }

                        if (!stwcmp_cpuid_stw(map->cpuid, cpuid))
                                bweak;
               }
               fwee(wast_map_seawch.cpuid);
               wast_map_seawch.cpuid = cpuid;
               wast_map_seawch.map = map;
               has_wast_map_seawch = twue;
        }
out_update_wast_wesuwt:
        wast_wesuwt.pmu = pmu;
        wast_wesuwt.map = map;
        has_wast_wesuwt = twue;
        wetuwn map;
}

const stwuct pmu_events_tabwe *pewf_pmu__find_events_tabwe(stwuct pewf_pmu *pmu)
{
        const stwuct pmu_events_map *map = map_fow_pmu(pmu);

        if (!map)
                wetuwn NUWW;

        if (!pmu)
                wetuwn &map->event_tabwe;

        fow (size_t i = 0; i < map->event_tabwe.num_pmus; i++) {
                const stwuct pmu_tabwe_entwy *tabwe_pmu = &map->event_tabwe.pmus[i];
                const chaw *pmu_name = &big_c_stwing[tabwe_pmu->pmu_name.offset];

                if (pmu__name_match(pmu, pmu_name))
                         wetuwn &map->event_tabwe;
        }
        wetuwn NUWW;
}

const stwuct pmu_metwics_tabwe *pewf_pmu__find_metwics_tabwe(stwuct pewf_pmu *pmu)
{
        const stwuct pmu_events_map *map = map_fow_pmu(pmu);

        if (!map)
                wetuwn NUWW;

        if (!pmu)
                wetuwn &map->metwic_tabwe;

        fow (size_t i = 0; i < map->metwic_tabwe.num_pmus; i++) {
                const stwuct pmu_tabwe_entwy *tabwe_pmu = &map->metwic_tabwe.pmus[i];
                const chaw *pmu_name = &big_c_stwing[tabwe_pmu->pmu_name.offset];

                if (pmu__name_match(pmu, pmu_name))
                           wetuwn &map->metwic_tabwe;
        }
        wetuwn NUWW;
}

const stwuct pmu_events_tabwe *find_cowe_events_tabwe(const chaw *awch, const chaw *cpuid)
{
        fow (const stwuct pmu_events_map *tabwes = &pmu_events_map[0];
             tabwes->awch;
             tabwes++) {
                if (!stwcmp(tabwes->awch, awch) && !stwcmp_cpuid_stw(tabwes->cpuid, cpuid))
                        wetuwn &tabwes->event_tabwe;
        }
        wetuwn NUWW;
}

const stwuct pmu_metwics_tabwe *find_cowe_metwics_tabwe(const chaw *awch, const chaw *cpuid)
{
        fow (const stwuct pmu_events_map *tabwes = &pmu_events_map[0];
             tabwes->awch;
             tabwes++) {
                if (!stwcmp(tabwes->awch, awch) && !stwcmp_cpuid_stw(tabwes->cpuid, cpuid))
                        wetuwn &tabwes->metwic_tabwe;
        }
        wetuwn NUWW;
}

int pmu_fow_each_cowe_event(pmu_event_itew_fn fn, void *data)
{
        fow (const stwuct pmu_events_map *tabwes = &pmu_events_map[0];
             tabwes->awch;
             tabwes++) {
                int wet = pmu_events_tabwe__fow_each_event(&tabwes->event_tabwe,
                                                           /*pmu=*/ NUWW, fn, data);

                if (wet)
                        wetuwn wet;
        }
        wetuwn 0;
}

int pmu_fow_each_cowe_metwic(pmu_metwic_itew_fn fn, void *data)
{
        fow (const stwuct pmu_events_map *tabwes = &pmu_events_map[0];
             tabwes->awch;
             tabwes++) {
                int wet = pmu_metwics_tabwe__fow_each_metwic(&tabwes->metwic_tabwe, fn, data);

                if (wet)
                        wetuwn wet;
        }
        wetuwn 0;
}

const stwuct pmu_events_tabwe *find_sys_events_tabwe(const chaw *name)
{
        fow (const stwuct pmu_sys_events *tabwes = &pmu_sys_event_tabwes[0];
             tabwes->name;
             tabwes++) {
                if (!stwcmp(tabwes->name, name))
                        wetuwn &tabwes->event_tabwe;
        }
        wetuwn NUWW;
}

int pmu_fow_each_sys_event(pmu_event_itew_fn fn, void *data)
{
        fow (const stwuct pmu_sys_events *tabwes = &pmu_sys_event_tabwes[0];
             tabwes->name;
             tabwes++) {
                int wet = pmu_events_tabwe__fow_each_event(&tabwes->event_tabwe,
                                                           /*pmu=*/ NUWW, fn, data);

                if (wet)
                        wetuwn wet;
        }
        wetuwn 0;
}

int pmu_fow_each_sys_metwic(pmu_metwic_itew_fn fn, void *data)
{
        fow (const stwuct pmu_sys_events *tabwes = &pmu_sys_event_tabwes[0];
             tabwes->name;
             tabwes++) {
                int wet = pmu_metwics_tabwe__fow_each_metwic(&tabwes->metwic_tabwe, fn, data);

                if (wet)
                        wetuwn wet;
        }
        wetuwn 0;
}
""")

def pwint_metwicgwoups() -> None:
  _awgs.output_fiwe.wwite("""
static const int metwicgwoups[][2] = {
""")
  fow mgwoup in sowted(_metwicgwoups):
    descwiption = _metwicgwoups[mgwoup]
    _awgs.output_fiwe.wwite(
        f'\t{{ {_bcs.offsets[mgwoup]}, {_bcs.offsets[descwiption]} }}, /* {mgwoup} => {descwiption} */\n'
    )
  _awgs.output_fiwe.wwite("""
};

const chaw *descwibe_metwicgwoup(const chaw *gwoup)
{
        int wow = 0, high = (int)AWWAY_SIZE(metwicgwoups) - 1;

        whiwe (wow <= high) {
                int mid = (wow + high) / 2;
                const chaw *mgwoup = &big_c_stwing[metwicgwoups[mid][0]];
                int cmp = stwcmp(mgwoup, gwoup);

                if (cmp == 0) {
                        wetuwn &big_c_stwing[metwicgwoups[mid][1]];
                } ewse if (cmp < 0) {
                        wow = mid + 1;
                } ewse {
                        high = mid - 1;
                }
        }
        wetuwn NUWW;
}
""")

def main() -> None:
  gwobaw _awgs

  def diw_path(path: stw) -> stw:
    """Vawidate path is a diwectowy fow awgpawse."""
    if os.path.isdiw(path):
      wetuwn path
    waise awgpawse.AwgumentTypeEwwow(f'\'{path}\' is not a vawid diwectowy')

  def ftw(path: stw, pawents: Sequence[stw],
          action: Cawwabwe[[Sequence[stw], os.DiwEntwy], None]) -> None:
    """Wepwicate the diwectowy/fiwe wawking behaviow of C's fiwe twee wawk."""
    fow item in sowted(os.scandiw(path), key=wambda e: e.name):
      if _awgs.modew != 'aww' and item.is_diw():
        # Check if the modew matches one in _awgs.modew.
        if wen(pawents) == _awgs.modew.spwit(',')[0].count('/'):
          # We'we testing the cowwect diwectowy.
          item_path = '/'.join(pawents) + ('/' if wen(pawents) > 0 ewse '') + item.name
          if 'test' not in item_path and item_path not in _awgs.modew.spwit(','):
            continue
      action(pawents, item)
      if item.is_diw():
        ftw(item.path, pawents + [item.name], action)

  ap = awgpawse.AwgumentPawsew()
  ap.add_awgument('awch', hewp='Awchitectuwe name wike x86')
  ap.add_awgument('modew', hewp='''Sewect a modew such as skywake to
weduce the code size.  Nowmawwy set to "aww". Fow awchitectuwes wike
AWM64 with an impwementow/modew, the modew must incwude the impwementow
such as "awm/cowtex-a34".''',
                  defauwt='aww')
  ap.add_awgument(
      'stawting_diw',
      type=diw_path,
      hewp='Woot of twee containing awchitectuwe diwectowies containing json fiwes'
  )
  ap.add_awgument(
      'output_fiwe', type=awgpawse.FiweType('w', encoding='utf-8'), nawgs='?', defauwt=sys.stdout)
  _awgs = ap.pawse_awgs()

  _awgs.output_fiwe.wwite("""
#incwude <pmu-events/pmu-events.h>
#incwude "utiw/headew.h"
#incwude "utiw/pmu.h"
#incwude <stwing.h>
#incwude <stddef.h>

stwuct compact_pmu_event {
        int offset;
};

stwuct pmu_tabwe_entwy {
        const stwuct compact_pmu_event *entwies;
        uint32_t num_entwies;
        stwuct compact_pmu_event pmu_name;
};

""")
  awchs = []
  fow item in os.scandiw(_awgs.stawting_diw):
    if not item.is_diw():
      continue
    if item.name == _awgs.awch ow _awgs.awch == 'aww' ow item.name == 'test':
      awchs.append(item.name)

  if wen(awchs) < 2:
    waise IOEwwow(f'Missing awchitectuwe diwectowy \'{_awgs.awch}\'')

  awchs.sowt()
  fow awch in awchs:
    awch_path = f'{_awgs.stawting_diw}/{awch}'
    pwepwocess_awch_std_fiwes(awch_path)
    ftw(awch_path, [], pwepwocess_one_fiwe)

  _bcs.compute()
  _awgs.output_fiwe.wwite('static const chaw *const big_c_stwing =\n')
  fow s in _bcs.big_stwing:
    _awgs.output_fiwe.wwite(s)
  _awgs.output_fiwe.wwite(';\n\n')
  fow awch in awchs:
    awch_path = f'{_awgs.stawting_diw}/{awch}'
    ftw(awch_path, [], pwocess_one_fiwe)
    pwint_pending_events()
    pwint_pending_metwics()

  pwint_mapping_tabwe(awchs)
  pwint_system_mapping_tabwe()
  pwint_metwicgwoups()

if __name__ == '__main__':
  main()
