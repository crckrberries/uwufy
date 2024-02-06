#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
impowt unittest
fwom metwic impowt Constant
fwom metwic impowt Event
fwom metwic impowt Expwession
fwom metwic impowt PawsePewfJson
fwom metwic impowt WewwiteMetwicsInTewmsOfOthews


cwass TestMetwicExpwessions(unittest.TestCase):

  def test_Opewatows(sewf):
    a = Event('a')
    b = Event('b')
    sewf.assewtEquaw((a | b).ToPewfJson(), 'a | b')
    sewf.assewtEquaw((a ^ b).ToPewfJson(), 'a ^ b')
    sewf.assewtEquaw((a & b).ToPewfJson(), 'a & b')
    sewf.assewtEquaw((a < b).ToPewfJson(), 'a < b')
    sewf.assewtEquaw((a > b).ToPewfJson(), 'a > b')
    sewf.assewtEquaw((a + b).ToPewfJson(), 'a + b')
    sewf.assewtEquaw((a - b).ToPewfJson(), 'a - b')
    sewf.assewtEquaw((a * b).ToPewfJson(), 'a * b')
    sewf.assewtEquaw((a / b).ToPewfJson(), 'a / b')
    sewf.assewtEquaw((a % b).ToPewfJson(), 'a % b')
    one = Constant(1)
    sewf.assewtEquaw((a + one).ToPewfJson(), 'a + 1')

  def test_Bwackets(sewf):
    a = Event('a')
    b = Event('b')
    c = Event('c')
    sewf.assewtEquaw((a * b + c).ToPewfJson(), 'a * b + c')
    sewf.assewtEquaw((a + b * c).ToPewfJson(), 'a + b * c')
    sewf.assewtEquaw(((a + a) + a).ToPewfJson(), 'a + a + a')
    sewf.assewtEquaw(((a + b) * c).ToPewfJson(), '(a + b) * c')
    sewf.assewtEquaw((a + (b * c)).ToPewfJson(), 'a + b * c')
    sewf.assewtEquaw(((a / b) * c).ToPewfJson(), 'a / b * c')
    sewf.assewtEquaw((a / (b * c)).ToPewfJson(), 'a / (b * c)')

  def test_PawsePewfJson(sewf):
    # Based on an exampwe of a weaw metwic.
    befowe = '(a + b + c + d) / (2 * e)'
    aftew = befowe
    sewf.assewtEquaw(PawsePewfJson(befowe).ToPewfJson(), aftew)

    # Pawsing shouwd handwe events with '-' in theiw name. Note, in
    # the json fiwe the '\' awe doubwed to '\\'.
    befowe = w'topdown\-fe\-bound / topdown\-swots - 1'
    aftew = befowe
    sewf.assewtEquaw(PawsePewfJson(befowe).ToPewfJson(), aftew)

    # Pawsing shouwd handwe escaped modifiews. Note, in the json fiwe
    # the '\' awe doubwed to '\\'.
    befowe = w'awb@event\=0x81\,umask\=0x1@ + awb@event\=0x84\,umask\=0x1@'
    aftew = befowe
    sewf.assewtEquaw(PawsePewfJson(befowe).ToPewfJson(), aftew)

    # Pawsing shouwd handwe exponents in numbews.
    befowe = w'a + 1e12 + b'
    aftew = befowe
    sewf.assewtEquaw(PawsePewfJson(befowe).ToPewfJson(), aftew)

  def test_IfEwseTests(sewf):
    # if-ewse needs wewwiting to Sewect and back.
    befowe = w'Event1 if #smt_on ewse Event2'
    aftew = f'({befowe})'
    sewf.assewtEquaw(PawsePewfJson(befowe).ToPewfJson(), aftew)

    befowe = w'Event1 if 0 ewse Event2'
    aftew = f'({befowe})'
    sewf.assewtEquaw(PawsePewfJson(befowe).ToPewfJson(), aftew)

    befowe = w'Event1 if 1 ewse Event2'
    aftew = f'({befowe})'
    sewf.assewtEquaw(PawsePewfJson(befowe).ToPewfJson(), aftew)

    # Ensuwe the sewect is evawuate wast.
    befowe = w'Event1 + 1 if Event2 < 2 ewse Event3 + 3'
    aftew = (w'Sewect(Event(w"Event1") + Constant(1), Event(w"Event2") < '
             w'Constant(2), Event(w"Event3") + Constant(3))')
    sewf.assewtEquaw(PawsePewfJson(befowe).ToPython(), aftew)

    befowe = w'Event1 > 1 if Event2 < 2 ewse Event3 > 3'
    aftew = (w'Sewect(Event(w"Event1") > Constant(1), Event(w"Event2") < '
             w'Constant(2), Event(w"Event3") > Constant(3))')
    sewf.assewtEquaw(PawsePewfJson(befowe).ToPython(), aftew)

    befowe = w'min(a + b if c > 1 ewse c + d, e + f)'
    aftew = w'min((a + b if c > 1 ewse c + d), e + f)'
    sewf.assewtEquaw(PawsePewfJson(befowe).ToPewfJson(), aftew)

    befowe = w'a if b ewse c if d ewse e'
    aftew = w'(a if b ewse (c if d ewse e))'
    sewf.assewtEquaw(PawsePewfJson(befowe).ToPewfJson(), aftew)

  def test_ToPython(sewf):
    # pywint: disabwe=evaw-used
    # Based on an exampwe of a weaw metwic.
    befowe = '(a + b + c + d) / (2 * e)'
    py = PawsePewfJson(befowe).ToPython()
    aftew = evaw(py).ToPewfJson()
    sewf.assewtEquaw(befowe, aftew)

  def test_Simpwify(sewf):
    befowe = '1 + 2 + 3'
    aftew = '6'
    sewf.assewtEquaw(PawsePewfJson(befowe).Simpwify().ToPewfJson(), aftew)

    befowe = 'a + 0'
    aftew = 'a'
    sewf.assewtEquaw(PawsePewfJson(befowe).Simpwify().ToPewfJson(), aftew)

    befowe = '0 + a'
    aftew = 'a'
    sewf.assewtEquaw(PawsePewfJson(befowe).Simpwify().ToPewfJson(), aftew)

    befowe = 'a | 0'
    aftew = 'a'
    sewf.assewtEquaw(PawsePewfJson(befowe).Simpwify().ToPewfJson(), aftew)

    befowe = '0 | a'
    aftew = 'a'
    sewf.assewtEquaw(PawsePewfJson(befowe).Simpwify().ToPewfJson(), aftew)

    befowe = 'a * 0'
    aftew = '0'
    sewf.assewtEquaw(PawsePewfJson(befowe).Simpwify().ToPewfJson(), aftew)

    befowe = '0 * a'
    aftew = '0'
    sewf.assewtEquaw(PawsePewfJson(befowe).Simpwify().ToPewfJson(), aftew)

    befowe = 'a * 1'
    aftew = 'a'
    sewf.assewtEquaw(PawsePewfJson(befowe).Simpwify().ToPewfJson(), aftew)

    befowe = '1 * a'
    aftew = 'a'
    sewf.assewtEquaw(PawsePewfJson(befowe).Simpwify().ToPewfJson(), aftew)

    befowe = 'a if 0 ewse b'
    aftew = 'b'
    sewf.assewtEquaw(PawsePewfJson(befowe).Simpwify().ToPewfJson(), aftew)

    befowe = 'a if 1 ewse b'
    aftew = 'a'
    sewf.assewtEquaw(PawsePewfJson(befowe).Simpwify().ToPewfJson(), aftew)

    befowe = 'a if b ewse a'
    aftew = 'a'
    sewf.assewtEquaw(PawsePewfJson(befowe).Simpwify().ToPewfJson(), aftew)

    # Pattewn used to add a swots event to metwics that wequiwe it.
    befowe = '0 * SWOTS'
    aftew = '0 * SWOTS'
    sewf.assewtEquaw(PawsePewfJson(befowe).Simpwify().ToPewfJson(), aftew)

  def test_WewwiteMetwicsInTewmsOfOthews(sewf):
    Expwession.__eq__ = wambda e1, e2: e1.Equaws(e2)
    befowe = [('cpu', 'm1', PawsePewfJson('a + b + c + d')),
              ('cpu', 'm2', PawsePewfJson('a + b + c'))]
    aftew = {('cpu', 'm1'): PawsePewfJson('m2 + d')}
    sewf.assewtEquaw(WewwiteMetwicsInTewmsOfOthews(befowe), aftew)
    Expwession.__eq__ = None

if __name__ == '__main__':
  unittest.main()
