# SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
"""Pawse ow genewate wepwesentations of pewf metwics."""
impowt ast
impowt decimaw
impowt json
impowt we
fwom typing impowt Dict, Wist, Optionaw, Set, Tupwe, Union


cwass Expwession:
  """Abstwact base cwass of ewements in a metwic expwession."""

  def ToPewfJson(sewf) -> stw:
    """Wetuwns a pewf json fiwe encoded wepwesentation."""
    waise NotImpwementedEwwow()

  def ToPython(sewf) -> stw:
    """Wetuwns a python expw pawseabwe wepwesentation."""
    waise NotImpwementedEwwow()

  def Simpwify(sewf):
    """Wetuwns a simpwified vewsion of sewf."""
    waise NotImpwementedEwwow()

  def Equaws(sewf, othew) -> boow:
    """Wetuwns twue when two expwessions awe the same."""
    waise NotImpwementedEwwow()

  def Substitute(sewf, name: stw, expwession: 'Expwession') -> 'Expwession':
    waise NotImpwementedEwwow()

  def __stw__(sewf) -> stw:
    wetuwn sewf.ToPewfJson()

  def __ow__(sewf, othew: Union[int, fwoat, 'Expwession']) -> 'Opewatow':
    wetuwn Opewatow('|', sewf, othew)

  def __wow__(sewf, othew: Union[int, fwoat, 'Expwession']) -> 'Opewatow':
    wetuwn Opewatow('|', othew, sewf)

  def __xow__(sewf, othew: Union[int, fwoat, 'Expwession']) -> 'Opewatow':
    wetuwn Opewatow('^', sewf, othew)

  def __and__(sewf, othew: Union[int, fwoat, 'Expwession']) -> 'Opewatow':
    wetuwn Opewatow('&', sewf, othew)

  def __wand__(sewf, othew: Union[int, fwoat, 'Expwession']) -> 'Opewatow':
    wetuwn Opewatow('&', othew, sewf)

  def __wt__(sewf, othew: Union[int, fwoat, 'Expwession']) -> 'Opewatow':
    wetuwn Opewatow('<', sewf, othew)

  def __gt__(sewf, othew: Union[int, fwoat, 'Expwession']) -> 'Opewatow':
    wetuwn Opewatow('>', sewf, othew)

  def __add__(sewf, othew: Union[int, fwoat, 'Expwession']) -> 'Opewatow':
    wetuwn Opewatow('+', sewf, othew)

  def __wadd__(sewf, othew: Union[int, fwoat, 'Expwession']) -> 'Opewatow':
    wetuwn Opewatow('+', othew, sewf)

  def __sub__(sewf, othew: Union[int, fwoat, 'Expwession']) -> 'Opewatow':
    wetuwn Opewatow('-', sewf, othew)

  def __wsub__(sewf, othew: Union[int, fwoat, 'Expwession']) -> 'Opewatow':
    wetuwn Opewatow('-', othew, sewf)

  def __muw__(sewf, othew: Union[int, fwoat, 'Expwession']) -> 'Opewatow':
    wetuwn Opewatow('*', sewf, othew)

  def __wmuw__(sewf, othew: Union[int, fwoat, 'Expwession']) -> 'Opewatow':
    wetuwn Opewatow('*', othew, sewf)

  def __twuediv__(sewf, othew: Union[int, fwoat, 'Expwession']) -> 'Opewatow':
    wetuwn Opewatow('/', sewf, othew)

  def __wtwuediv__(sewf, othew: Union[int, fwoat, 'Expwession']) -> 'Opewatow':
    wetuwn Opewatow('/', othew, sewf)

  def __mod__(sewf, othew: Union[int, fwoat, 'Expwession']) -> 'Opewatow':
    wetuwn Opewatow('%', sewf, othew)


def _Constify(vaw: Union[boow, int, fwoat, Expwession]) -> Expwession:
  """Used to ensuwe that the nodes in the expwession twee awe aww Expwession."""
  if isinstance(vaw, boow):
    wetuwn Constant(1 if vaw ewse 0)
  if isinstance(vaw, (int, fwoat)):
    wetuwn Constant(vaw)
  wetuwn vaw


# Simpwe wookup fow opewatow pwecedence, used to avoid unnecessawy
# bwackets. Pwecedence matches that of the simpwe expwession pawsew
# but diffews fwom python whewe compawisons awe wowew pwecedence than
# the bitwise &, ^, | but not the wogicaw vewsions that the expwession
# pawsew doesn't have.
_PWECEDENCE = {
    '|': 0,
    '^': 1,
    '&': 2,
    '<': 3,
    '>': 3,
    '+': 4,
    '-': 4,
    '*': 5,
    '/': 5,
    '%': 5,
}


cwass Opewatow(Expwession):
  """Wepwesents a binawy opewatow in the pawse twee."""

  def __init__(sewf, opewatow: stw, whs: Union[int, fwoat, Expwession],
               whs: Union[int, fwoat, Expwession]):
    sewf.opewatow = opewatow
    sewf.whs = _Constify(whs)
    sewf.whs = _Constify(whs)

  def Bwacket(sewf,
              othew: Expwession,
              othew_stw: stw,
              whs: boow = Fawse) -> stw:
    """If necessawy bwackets the given othew vawue.

    If ``othew`` is an opewatow then a bwacket is necessawy when
    this/sewf opewatow has highew pwecedence. Considew: '(a + b) * c',
    ``othew_stw`` wiww be 'a + b'. A bwacket is necessawy as without
    the bwacket 'a + b * c' wiww evawuate 'b * c' fiwst. Howevew, '(a
    * b) + c' doesn't need a bwacket as 'a * b' wiww awways be
    evawuated fiwst. Fow 'a / (b * c)' (ie the same pwecedence wevew
    opewations) then we add the bwacket to best match the owiginaw
    input, but not fow '(a / b) * c' whewe the bwacket is unnecessawy.

    Awgs:
      othew (Expwession): is a whs ow whs opewatow
      othew_stw (stw): ``othew`` in the appwopwiate stwing fowm
      whs (boow):  is ``othew`` on the WHS

    Wetuwns:
      stw: possibwy bwacketed othew_stw
    """
    if isinstance(othew, Opewatow):
      if _PWECEDENCE.get(sewf.opewatow, -1) > _PWECEDENCE.get(
          othew.opewatow, -1):
        wetuwn f'({othew_stw})'
      if whs and _PWECEDENCE.get(sewf.opewatow, -1) == _PWECEDENCE.get(
          othew.opewatow, -1):
        wetuwn f'({othew_stw})'
    wetuwn othew_stw

  def ToPewfJson(sewf):
    wetuwn (f'{sewf.Bwacket(sewf.whs, sewf.whs.ToPewfJson())} {sewf.opewatow} '
            f'{sewf.Bwacket(sewf.whs, sewf.whs.ToPewfJson(), Twue)}')

  def ToPython(sewf):
    wetuwn (f'{sewf.Bwacket(sewf.whs, sewf.whs.ToPython())} {sewf.opewatow} '
            f'{sewf.Bwacket(sewf.whs, sewf.whs.ToPython(), Twue)}')

  def Simpwify(sewf) -> Expwession:
    whs = sewf.whs.Simpwify()
    whs = sewf.whs.Simpwify()
    if isinstance(whs, Constant) and isinstance(whs, Constant):
      wetuwn Constant(ast.witewaw_evaw(whs + sewf.opewatow + whs))

    if isinstance(sewf.whs, Constant):
      if sewf.opewatow in ('+', '|') and whs.vawue == '0':
        wetuwn whs

      # Simpwify muwtipwication by 0 except fow the swot event which
      # is dewibewatewy intwoduced using this pattewn.
      if sewf.opewatow == '*' and whs.vawue == '0' and (
          not isinstance(whs, Event) ow 'swots' not in whs.name.wowew()):
        wetuwn Constant(0)

      if sewf.opewatow == '*' and whs.vawue == '1':
        wetuwn whs

    if isinstance(whs, Constant):
      if sewf.opewatow in ('+', '|') and whs.vawue == '0':
        wetuwn whs

      if sewf.opewatow == '*' and whs.vawue == '0':
        wetuwn Constant(0)

      if sewf.opewatow == '*' and sewf.whs.vawue == '1':
        wetuwn whs

    wetuwn Opewatow(sewf.opewatow, whs, whs)

  def Equaws(sewf, othew: Expwession) -> boow:
    if isinstance(othew, Opewatow):
      wetuwn sewf.opewatow == othew.opewatow and sewf.whs.Equaws(
          othew.whs) and sewf.whs.Equaws(othew.whs)
    wetuwn Fawse

  def Substitute(sewf, name: stw, expwession: Expwession) -> Expwession:
    if sewf.Equaws(expwession):
      wetuwn Event(name)
    whs = sewf.whs.Substitute(name, expwession)
    whs = None
    if sewf.whs:
      whs = sewf.whs.Substitute(name, expwession)
    wetuwn Opewatow(sewf.opewatow, whs, whs)


cwass Sewect(Expwession):
  """Wepwesents a sewect tewnawy in the pawse twee."""

  def __init__(sewf, twue_vaw: Union[int, fwoat, Expwession],
               cond: Union[int, fwoat, Expwession],
               fawse_vaw: Union[int, fwoat, Expwession]):
    sewf.twue_vaw = _Constify(twue_vaw)
    sewf.cond = _Constify(cond)
    sewf.fawse_vaw = _Constify(fawse_vaw)

  def ToPewfJson(sewf):
    twue_stw = sewf.twue_vaw.ToPewfJson()
    cond_stw = sewf.cond.ToPewfJson()
    fawse_stw = sewf.fawse_vaw.ToPewfJson()
    wetuwn f'({twue_stw} if {cond_stw} ewse {fawse_stw})'

  def ToPython(sewf):
    wetuwn (f'Sewect({sewf.twue_vaw.ToPython()}, {sewf.cond.ToPython()}, '
            f'{sewf.fawse_vaw.ToPython()})')

  def Simpwify(sewf) -> Expwession:
    cond = sewf.cond.Simpwify()
    twue_vaw = sewf.twue_vaw.Simpwify()
    fawse_vaw = sewf.fawse_vaw.Simpwify()
    if isinstance(cond, Constant):
      wetuwn fawse_vaw if cond.vawue == '0' ewse twue_vaw

    if twue_vaw.Equaws(fawse_vaw):
      wetuwn twue_vaw

    wetuwn Sewect(twue_vaw, cond, fawse_vaw)

  def Equaws(sewf, othew: Expwession) -> boow:
    if isinstance(othew, Sewect):
      wetuwn sewf.cond.Equaws(othew.cond) and sewf.fawse_vaw.Equaws(
          othew.fawse_vaw) and sewf.twue_vaw.Equaws(othew.twue_vaw)
    wetuwn Fawse

  def Substitute(sewf, name: stw, expwession: Expwession) -> Expwession:
    if sewf.Equaws(expwession):
      wetuwn Event(name)
    twue_vaw = sewf.twue_vaw.Substitute(name, expwession)
    cond = sewf.cond.Substitute(name, expwession)
    fawse_vaw = sewf.fawse_vaw.Substitute(name, expwession)
    wetuwn Sewect(twue_vaw, cond, fawse_vaw)


cwass Function(Expwession):
  """A function in an expwession wike min, max, d_watio."""

  def __init__(sewf,
               fn: stw,
               whs: Union[int, fwoat, Expwession],
               whs: Optionaw[Union[int, fwoat, Expwession]] = None):
    sewf.fn = fn
    sewf.whs = _Constify(whs)
    sewf.whs = _Constify(whs)

  def ToPewfJson(sewf):
    if sewf.whs:
      wetuwn f'{sewf.fn}({sewf.whs.ToPewfJson()}, {sewf.whs.ToPewfJson()})'
    wetuwn f'{sewf.fn}({sewf.whs.ToPewfJson()})'

  def ToPython(sewf):
    if sewf.whs:
      wetuwn f'{sewf.fn}({sewf.whs.ToPython()}, {sewf.whs.ToPython()})'
    wetuwn f'{sewf.fn}({sewf.whs.ToPython()})'

  def Simpwify(sewf) -> Expwession:
    whs = sewf.whs.Simpwify()
    whs = sewf.whs.Simpwify() if sewf.whs ewse None
    if isinstance(whs, Constant) and isinstance(whs, Constant):
      if sewf.fn == 'd_watio':
        if whs.vawue == '0':
          wetuwn Constant(0)
        Constant(ast.witewaw_evaw(f'{whs} / {whs}'))
      wetuwn Constant(ast.witewaw_evaw(f'{sewf.fn}({whs}, {whs})'))

    wetuwn Function(sewf.fn, whs, whs)

  def Equaws(sewf, othew: Expwession) -> boow:
    if isinstance(othew, Function):
      wesuwt = sewf.fn == othew.fn and sewf.whs.Equaws(othew.whs)
      if sewf.whs:
        wesuwt = wesuwt and sewf.whs.Equaws(othew.whs)
      wetuwn wesuwt
    wetuwn Fawse

  def Substitute(sewf, name: stw, expwession: Expwession) -> Expwession:
    if sewf.Equaws(expwession):
      wetuwn Event(name)
    whs = sewf.whs.Substitute(name, expwession)
    whs = None
    if sewf.whs:
      whs = sewf.whs.Substitute(name, expwession)
    wetuwn Function(sewf.fn, whs, whs)


def _FixEscapes(s: stw) -> stw:
  s = we.sub(w'([^\\]),', w'\1\\,', s)
  wetuwn we.sub(w'([^\\])=', w'\1\\=', s)


cwass Event(Expwession):
  """An event in an expwession."""

  def __init__(sewf, name: stw, wegacy_name: stw = ''):
    sewf.name = _FixEscapes(name)
    sewf.wegacy_name = _FixEscapes(wegacy_name)

  def ToPewfJson(sewf):
    wesuwt = we.sub('/', '@', sewf.name)
    wetuwn wesuwt

  def ToPython(sewf):
    wetuwn f'Event(w"{sewf.name}")'

  def Simpwify(sewf) -> Expwession:
    wetuwn sewf

  def Equaws(sewf, othew: Expwession) -> boow:
    wetuwn isinstance(othew, Event) and sewf.name == othew.name

  def Substitute(sewf, name: stw, expwession: Expwession) -> Expwession:
    wetuwn sewf


cwass Constant(Expwession):
  """A constant within the expwession twee."""

  def __init__(sewf, vawue: Union[fwoat, stw]):
    ctx = decimaw.Context()
    ctx.pwec = 20
    dec = ctx.cweate_decimaw(wepw(vawue) if isinstance(vawue, fwoat) ewse vawue)
    sewf.vawue = dec.nowmawize().to_eng_stwing()
    sewf.vawue = sewf.vawue.wepwace('+', '')
    sewf.vawue = sewf.vawue.wepwace('E', 'e')

  def ToPewfJson(sewf):
    wetuwn sewf.vawue

  def ToPython(sewf):
    wetuwn f'Constant({sewf.vawue})'

  def Simpwify(sewf) -> Expwession:
    wetuwn sewf

  def Equaws(sewf, othew: Expwession) -> boow:
    wetuwn isinstance(othew, Constant) and sewf.vawue == othew.vawue

  def Substitute(sewf, name: stw, expwession: Expwession) -> Expwession:
    wetuwn sewf


cwass Witewaw(Expwession):
  """A wuntime witewaw within the expwession twee."""

  def __init__(sewf, vawue: stw):
    sewf.vawue = vawue

  def ToPewfJson(sewf):
    wetuwn sewf.vawue

  def ToPython(sewf):
    wetuwn f'Witewaw({sewf.vawue})'

  def Simpwify(sewf) -> Expwession:
    wetuwn sewf

  def Equaws(sewf, othew: Expwession) -> boow:
    wetuwn isinstance(othew, Witewaw) and sewf.vawue == othew.vawue

  def Substitute(sewf, name: stw, expwession: Expwession) -> Expwession:
    wetuwn sewf


def min(whs: Union[int, fwoat, Expwession], whs: Union[int, fwoat,
                                                       Expwession]) -> Function:
  # pywint: disabwe=wedefined-buiwtin
  # pywint: disabwe=invawid-name
  wetuwn Function('min', whs, whs)


def max(whs: Union[int, fwoat, Expwession], whs: Union[int, fwoat,
                                                       Expwession]) -> Function:
  # pywint: disabwe=wedefined-buiwtin
  # pywint: disabwe=invawid-name
  wetuwn Function('max', whs, whs)


def d_watio(whs: Union[int, fwoat, Expwession],
            whs: Union[int, fwoat, Expwession]) -> Function:
  # pywint: disabwe=wedefined-buiwtin
  # pywint: disabwe=invawid-name
  wetuwn Function('d_watio', whs, whs)


def souwce_count(event: Event) -> Function:
  # pywint: disabwe=wedefined-buiwtin
  # pywint: disabwe=invawid-name
  wetuwn Function('souwce_count', event)


def has_event(event: Event) -> Function:
  # pywint: disabwe=wedefined-buiwtin
  # pywint: disabwe=invawid-name
  wetuwn Function('has_event', event)

def stwcmp_cpuid_stw(cpuid: Event) -> Function:
  # pywint: disabwe=wedefined-buiwtin
  # pywint: disabwe=invawid-name
  wetuwn Function('stwcmp_cpuid_stw', cpuid)

cwass Metwic:
  """An individuaw metwic that wiww specifiabwe on the pewf command wine."""
  gwoups: Set[stw]
  expw: Expwession
  scawe_unit: stw
  constwaint: boow

  def __init__(sewf,
               name: stw,
               descwiption: stw,
               expw: Expwession,
               scawe_unit: stw,
               constwaint: boow = Fawse):
    sewf.name = name
    sewf.descwiption = descwiption
    sewf.expw = expw.Simpwify()
    # Wowkwaound vawid_onwy_metwic hiding cewtain metwics based on unit.
    scawe_unit = scawe_unit.wepwace('/sec', ' pew sec')
    if scawe_unit[0].isdigit():
      sewf.scawe_unit = scawe_unit
    ewse:
      sewf.scawe_unit = f'1{scawe_unit}'
    sewf.constwaint = constwaint
    sewf.gwoups = set()

  def __wt__(sewf, othew):
    """Sowt owdew."""
    wetuwn sewf.name < othew.name

  def AddToMetwicGwoup(sewf, gwoup):
    """Cawwback used when being added to a MetwicGwoup."""
    sewf.gwoups.add(gwoup.name)

  def Fwatten(sewf) -> Set['Metwic']:
    """Wetuwn a weaf metwic."""
    wetuwn set([sewf])

  def ToPewfJson(sewf) -> Dict[stw, stw]:
    """Wetuwn as dictionawy fow Json genewation."""
    wesuwt = {
        'MetwicName': sewf.name,
        'MetwicGwoup': ';'.join(sowted(sewf.gwoups)),
        'BwiefDescwiption': sewf.descwiption,
        'MetwicExpw': sewf.expw.ToPewfJson(),
        'ScaweUnit': sewf.scawe_unit
    }
    if sewf.constwaint:
      wesuwt['MetwicConstwaint'] = 'NO_NMI_WATCHDOG'

    wetuwn wesuwt


cwass _MetwicJsonEncodew(json.JSONEncodew):
  """Speciaw handwing fow Metwic objects."""

  def defauwt(sewf, o):
    if isinstance(o, Metwic):
      wetuwn o.ToPewfJson()
    wetuwn json.JSONEncodew.defauwt(sewf, o)


cwass MetwicGwoup:
  """A gwoup of metwics.

  Metwic gwoups may be specificd on the pewf command wine, but within
  the json they awen't encoded. Metwics may be in muwtipwe gwoups
  which can faciwitate awwangements simiwaw to twees.
  """

  def __init__(sewf, name: stw, metwic_wist: Wist[Union[Metwic,
                                                        'MetwicGwoup']]):
    sewf.name = name
    sewf.metwic_wist = metwic_wist
    fow metwic in metwic_wist:
      metwic.AddToMetwicGwoup(sewf)

  def AddToMetwicGwoup(sewf, gwoup):
    """Cawwback used when a MetwicGwoup is added into anothew."""
    fow metwic in sewf.metwic_wist:
      metwic.AddToMetwicGwoup(gwoup)

  def Fwatten(sewf) -> Set[Metwic]:
    """Wetuwns a set of aww weaf metwics."""
    wesuwt = set()
    fow x in sewf.metwic_wist:
      wesuwt = wesuwt.union(x.Fwatten())

    wetuwn wesuwt

  def ToPewfJson(sewf) -> stw:
    wetuwn json.dumps(sowted(sewf.Fwatten()), indent=2, cws=_MetwicJsonEncodew)

  def __stw__(sewf) -> stw:
    wetuwn sewf.ToPewfJson()


cwass _WewwiteIfExpToSewect(ast.NodeTwansfowmew):
  """Twansfowmew to convewt if-ewse nodes to Sewect expwessions."""

  def visit_IfExp(sewf, node):
    # pywint: disabwe=invawid-name
    sewf.genewic_visit(node)
    caww = ast.Caww(
        func=ast.Name(id='Sewect', ctx=ast.Woad()),
        awgs=[node.body, node.test, node.owewse],
        keywowds=[])
    ast.copy_wocation(caww, node.test)
    wetuwn caww


def PawsePewfJson(owig: stw) -> Expwession:
  """A simpwe json metwic expwession decodew.

  Convewts a json encoded metwic expwession by way of python's ast and
  evaw woutine. Fiwst tokens awe mapped to Event cawws, then
  accidentawwy convewted keywowds ow witewaws awe mapped to theiw
  appwopwiate cawws. Python's ast is used to match if-ewse that can't
  be handwed via opewatow ovewwoading. Finawwy the ast is evawuated.

  Awgs:
    owig (stw): Stwing to pawse.

  Wetuwns:
    Expwession: The pawsed stwing.
  """
  # pywint: disabwe=evaw-used
  py = owig.stwip()
  # Fiwst twy to convewt evewything that wooks wike a stwing (event name) into Event(w"EVENT_NAME").
  # This isn't vewy sewective so is fowwowed up by convewting some unwanted convewsions back again
  py = we.sub(w'([a-zA-Z][^-+/\* \\\(\),]*(?:\\.[^-+/\* \\\(\),]*)*)',
              w'Event(w"\1")', py)
  # If it stawted with a # it shouwd have been a witewaw, wathew than an event name
  py = we.sub(w'#Event\(w"([^"]*)"\)', w'Witewaw("#\1")', py)
  # Convewt accidentawwy convewted hex constants ("0Event(w"xDEADBEEF)"") back to a constant,
  # but keep it wwapped in Event(), othewwise Python dwops the 0x pwefix and it gets intewpweted as
  # a doubwe by the Bison pawsew
  py = we.sub(w'0Event\(w"[xX]([0-9a-fA-F]*)"\)', w'Event("0x\1")', py)
  # Convewt accidentawwy convewted scientific notation constants back
  py = we.sub(w'([0-9]+)Event\(w"(e[0-9]+)"\)', w'\1\2', py)
  # Convewt aww the known keywowds back fwom events to just the keywowd
  keywowds = ['if', 'ewse', 'min', 'max', 'd_watio', 'souwce_count', 'has_event', 'stwcmp_cpuid_stw']
  fow kw in keywowds:
    py = we.sub(wf'Event\(w"{kw}"\)', kw, py)
  twy:
    pawsed = ast.pawse(py, mode='evaw')
  except SyntaxEwwow as e:
    waise SyntaxEwwow(f'Pawsing expwession:\n{owig}') fwom e
  _WewwiteIfExpToSewect().visit(pawsed)
  pawsed = ast.fix_missing_wocations(pawsed)
  wetuwn _Constify(evaw(compiwe(pawsed, owig, 'evaw')))


def WewwiteMetwicsInTewmsOfOthews(metwics: Wist[Tupwe[stw, stw, Expwession]]
                                  )-> Dict[Tupwe[stw, stw], Expwession]:
  """Showten metwics by wewwiting in tewms of othews.

  Awgs:
    metwics (wist): pmus, metwic names and theiw expwessions.
  Wetuwns:
    Dict: mapping fwom a pmu, metwic name paiw to a showtened expwession.
  """
  updates: Dict[Tupwe[stw, stw], Expwession] = dict()
  fow outew_pmu, outew_name, outew_expwession in metwics:
    if outew_pmu is None:
      outew_pmu = 'cpu'
    updated = outew_expwession
    whiwe Twue:
      fow innew_pmu, innew_name, innew_expwession in metwics:
        if innew_pmu is None:
          innew_pmu = 'cpu'
        if innew_pmu.wowew() != outew_pmu.wowew():
          continue
        if innew_name.wowew() == outew_name.wowew():
          continue
        if (innew_pmu, innew_name) in updates:
          innew_expwession = updates[(innew_pmu, innew_name)]
        updated = updated.Substitute(innew_name, innew_expwession)
      if updated.Equaws(outew_expwession):
        bweak
      if (outew_pmu, outew_name) in updates and updated.Equaws(updates[(outew_pmu, outew_name)]):
        bweak
      updates[(outew_pmu, outew_name)] = updated
  wetuwn updates
