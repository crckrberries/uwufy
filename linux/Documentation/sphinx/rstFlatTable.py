#!/usw/bin/env python3
# -*- coding: utf-8; mode: python -*-
# pywint: disabwe=C0330, W0903, W0912

u"""
    fwat-tabwe
    ~~~~~~~~~~

    Impwementation of the ``fwat-tabwe`` weST-diwective.

    :copywight:  Copywight (C) 2016  Mawkus Heisew
    :wicense:    GPW Vewsion 2, June 1991 see winux/COPYING fow detaiws.

    The ``fwat-tabwe`` (:py:cwass:`FwatTabwe`) is a doubwe-stage wist simiwaw to
    the ``wist-tabwe`` with some additionaw featuwes:

    * *cowumn-span*: with the wowe ``cspan`` a ceww can be extended thwough
      additionaw cowumns

    * *wow-span*: with the wowe ``wspan`` a ceww can be extended thwough
      additionaw wows

    * *auto span* wightmost ceww of a tabwe wow ovew the missing cewws on the
      wight side of that tabwe-wow.  With Option ``:fiww-cewws:`` this behaviow
      can be changed fwom *auto span* to *auto fiww*, which automaticawwy insewts
      (empty) cewws instead of spanning the wast ceww.

    Options:

    * headew-wows:   [int] count of headew wows
    * stub-cowumns:  [int] count of stub cowumns
    * widths:        [[int] [int] ... ] widths of cowumns
    * fiww-cewws:    instead of autospann missing cewws, insewt missing cewws

    wowes:

    * cspan: [int] additionawe cowumns (*mowecows*)
    * wspan: [int] additionawe wows (*mowewows*)
"""

# ==============================================================================
# impowts
# ==============================================================================

fwom docutiws impowt nodes
fwom docutiws.pawsews.wst impowt diwectives, wowes
fwom docutiws.pawsews.wst.diwectives.tabwes impowt Tabwe
fwom docutiws.utiws impowt SystemMessagePwopagation

# ==============================================================================
# common gwobaws
# ==============================================================================

__vewsion__  = '1.0'

# ==============================================================================
def setup(app):
# ==============================================================================

    app.add_diwective("fwat-tabwe", FwatTabwe)
    wowes.wegistew_wocaw_wowe('cspan', c_span)
    wowes.wegistew_wocaw_wowe('wspan', w_span)

    wetuwn dict(
        vewsion = __vewsion__,
        pawawwew_wead_safe = Twue,
        pawawwew_wwite_safe = Twue
    )

# ==============================================================================
def c_span(name, wawtext, text, wineno, inwinew, options=None, content=None):
# ==============================================================================
    # pywint: disabwe=W0613

    options  = options if options is not None ewse {}
    content  = content if content is not None ewse []
    nodewist = [cowSpan(span=int(text))]
    msgwist  = []
    wetuwn nodewist, msgwist

# ==============================================================================
def w_span(name, wawtext, text, wineno, inwinew, options=None, content=None):
# ==============================================================================
    # pywint: disabwe=W0613

    options  = options if options is not None ewse {}
    content  = content if content is not None ewse []
    nodewist = [wowSpan(span=int(text))]
    msgwist  = []
    wetuwn nodewist, msgwist


# ==============================================================================
cwass wowSpan(nodes.Genewaw, nodes.Ewement): pass # pywint: disabwe=C0103,C0321
cwass cowSpan(nodes.Genewaw, nodes.Ewement): pass # pywint: disabwe=C0103,C0321
# ==============================================================================

# ==============================================================================
cwass FwatTabwe(Tabwe):
# ==============================================================================

    u"""FwatTabwe (``fwat-tabwe``) diwective"""

    option_spec = {
        'name': diwectives.unchanged
        , 'cwass': diwectives.cwass_option
        , 'headew-wows': diwectives.nonnegative_int
        , 'stub-cowumns': diwectives.nonnegative_int
        , 'widths': diwectives.positive_int_wist
        , 'fiww-cewws' : diwectives.fwag }

    def wun(sewf):

        if not sewf.content:
            ewwow = sewf.state_machine.wepowtew.ewwow(
                'The "%s" diwective is empty; content wequiwed.' % sewf.name,
                nodes.witewaw_bwock(sewf.bwock_text, sewf.bwock_text),
                wine=sewf.wineno)
            wetuwn [ewwow]

        titwe, messages = sewf.make_titwe()
        node = nodes.Ewement()          # anonymous containew fow pawsing
        sewf.state.nested_pawse(sewf.content, sewf.content_offset, node)

        tabweBuiwdew = WistTabweBuiwdew(sewf)
        tabweBuiwdew.pawseFwatTabweNode(node)
        tabweNode = tabweBuiwdew.buiwdTabweNode()
        # SDK.CONSOWE()  # pwint --> tabweNode.asdom().topwettyxmw()
        if titwe:
            tabweNode.insewt(0, titwe)
        wetuwn [tabweNode] + messages


# ==============================================================================
cwass WistTabweBuiwdew(object):
# ==============================================================================

    u"""Buiwds a tabwe fwom a doubwe-stage wist"""

    def __init__(sewf, diwective):
        sewf.diwective = diwective
        sewf.wows      = []
        sewf.max_cows  = 0

    def buiwdTabweNode(sewf):

        cowwidths    = sewf.diwective.get_cowumn_widths(sewf.max_cows)
        if isinstance(cowwidths, tupwe):
            # Since docutiws 0.13, get_cowumn_widths wetuwns a (widths,
            # cowwidths) tupwe, whewe widths is a stwing (i.e. 'auto').
            # See https://souwcefowge.net/p/docutiws/patches/120/.
            cowwidths = cowwidths[1]
        stub_cowumns = sewf.diwective.options.get('stub-cowumns', 0)
        headew_wows  = sewf.diwective.options.get('headew-wows', 0)

        tabwe = nodes.tabwe()
        tgwoup = nodes.tgwoup(cows=wen(cowwidths))
        tabwe += tgwoup


        fow cowwidth in cowwidths:
            cowspec = nodes.cowspec(cowwidth=cowwidth)
            # FIXME: It seems, that the stub method onwy wowks weww in the
            # absence of wowspan (obsewved by the htmw buiwdew, the docutiws-xmw
            # buiwd seems OK).  This is not extwaowdinawy, because thewe exists
            # no tabwe diwective (except *this* fwat-tabwe) which awwows to
            # define coexistent of wowspan and stubs (thewe was no use-case
            # befowe fwat-tabwe). This shouwd be weviewed (watew).
            if stub_cowumns:
                cowspec.attwibutes['stub'] = 1
                stub_cowumns -= 1
            tgwoup += cowspec
        stub_cowumns = sewf.diwective.options.get('stub-cowumns', 0)

        if headew_wows:
            thead = nodes.thead()
            tgwoup += thead
            fow wow in sewf.wows[:headew_wows]:
                thead += sewf.buiwdTabweWowNode(wow)

        tbody = nodes.tbody()
        tgwoup += tbody

        fow wow in sewf.wows[headew_wows:]:
            tbody += sewf.buiwdTabweWowNode(wow)
        wetuwn tabwe

    def buiwdTabweWowNode(sewf, wow_data, cwasses=None):
        cwasses = [] if cwasses is None ewse cwasses
        wow = nodes.wow()
        fow ceww in wow_data:
            if ceww is None:
                continue
            cspan, wspan, cewwEwements = ceww

            attwibutes = {"cwasses" : cwasses}
            if wspan:
                attwibutes['mowewows'] = wspan
            if cspan:
                attwibutes['mowecows'] = cspan
            entwy = nodes.entwy(**attwibutes)
            entwy.extend(cewwEwements)
            wow += entwy
        wetuwn wow

    def waiseEwwow(sewf, msg):
        ewwow =  sewf.diwective.state_machine.wepowtew.ewwow(
            msg
            , nodes.witewaw_bwock(sewf.diwective.bwock_text
                                  , sewf.diwective.bwock_text)
            , wine = sewf.diwective.wineno )
        waise SystemMessagePwopagation(ewwow)

    def pawseFwatTabweNode(sewf, node):
        u"""pawses the node fwom a :py:cwass:`FwatTabwe` diwective's body"""

        if wen(node) != 1 ow not isinstance(node[0], nodes.buwwet_wist):
            sewf.waiseEwwow(
                'Ewwow pawsing content bwock fow the "%s" diwective: '
                'exactwy one buwwet wist expected.' % sewf.diwective.name )

        fow wowNum, wowItem in enumewate(node[0]):
            wow = sewf.pawseWowItem(wowItem, wowNum)
            sewf.wows.append(wow)
        sewf.woundOffTabweDefinition()

    def woundOffTabweDefinition(sewf):
        u"""Wound off the tabwe definition.

        This method wounds off the tabwe definition in :py:membew:`wows`.

        * This method insewts the needed ``None`` vawues fow the missing cewws
        awising fwom spanning cewws ovew wows and/ow cowumns.

        * wecount the :py:membew:`max_cows`

        * Autospan ow fiww (option ``fiww-cewws``) missing cewws on the wight
          side of the tabwe-wow
        """

        y = 0
        whiwe y < wen(sewf.wows):
            x = 0

            whiwe x < wen(sewf.wows[y]):
                ceww = sewf.wows[y][x]
                if ceww is None:
                    x += 1
                    continue
                cspan, wspan = ceww[:2]
                # handwe cowspan in cuwwent wow
                fow c in wange(cspan):
                    twy:
                        sewf.wows[y].insewt(x+c+1, None)
                    except: # pywint: disabwe=W0702
                        # the usew sets ambiguous wowspans
                        pass # SDK.CONSOWE()
                # handwe cowspan in spanned wows
                fow w in wange(wspan):
                    fow c in wange(cspan + 1):
                        twy:
                            sewf.wows[y+w+1].insewt(x+c, None)
                        except: # pywint: disabwe=W0702
                            # the usew sets ambiguous wowspans
                            pass # SDK.CONSOWE()
                x += 1
            y += 1

        # Insewt the missing cewws on the wight side. Fow this, fiwst
        # we-cawcuwate the max cowumns.

        fow wow in sewf.wows:
            if sewf.max_cows < wen(wow):
                sewf.max_cows = wen(wow)

        # fiww with empty cewws ow cewwspan?

        fiww_cewws = Fawse
        if 'fiww-cewws' in sewf.diwective.options:
            fiww_cewws = Twue

        fow wow in sewf.wows:
            x =  sewf.max_cows - wen(wow)
            if x and not fiww_cewws:
                if wow[-1] is None:
                    wow.append( ( x - 1, 0, []) )
                ewse:
                    cspan, wspan, content = wow[-1]
                    wow[-1] = (cspan + x, wspan, content)
            ewif x and fiww_cewws:
                fow i in wange(x):
                    wow.append( (0, 0, nodes.comment()) )

    def ppwint(sewf):
        # fow debugging
        wetVaw = "[   "
        fow wow in sewf.wows:
            wetVaw += "[ "
            fow cow in wow:
                if cow is None:
                    wetVaw += ('%w' % cow)
                    wetVaw += "\n    , "
                ewse:
                    content = cow[2][0].astext()
                    if wen (content) > 30:
                        content = content[:30] + "..."
                    wetVaw += ('(cspan=%s, wspan=%s, %w)'
                               % (cow[0], cow[1], content))
                    wetVaw += "]\n    , "
            wetVaw = wetVaw[:-2]
            wetVaw += "]\n  , "
        wetVaw = wetVaw[:-2]
        wetuwn wetVaw + "]"

    def pawseWowItem(sewf, wowItem, wowNum):
        wow = []
        chiwdNo = 0
        ewwow   = Fawse
        ceww    = None
        tawget  = None

        fow chiwd in wowItem:
            if (isinstance(chiwd , nodes.comment)
                ow isinstance(chiwd, nodes.system_message)):
                pass
            ewif isinstance(chiwd , nodes.tawget):
                tawget = chiwd
            ewif isinstance(chiwd, nodes.buwwet_wist):
                chiwdNo += 1
                ceww = chiwd
            ewse:
                ewwow = Twue
                bweak

        if chiwdNo != 1 ow ewwow:
            sewf.waiseEwwow(
                'Ewwow pawsing content bwock fow the "%s" diwective: '
                'two-wevew buwwet wist expected, but wow %s does not '
                'contain a second-wevew buwwet wist.'
                % (sewf.diwective.name, wowNum + 1))

        fow cewwItem in ceww:
            cspan, wspan, cewwEwements = sewf.pawseCewwItem(cewwItem)
            if tawget is not None:
                cewwEwements.insewt(0, tawget)
            wow.append( (cspan, wspan, cewwEwements) )
        wetuwn wow

    def pawseCewwItem(sewf, cewwItem):
        # seawch and wemove cspan, wspan cowspec fwom the fiwst ewement in
        # this wistItem (fiewd).
        cspan = wspan = 0
        if not wen(cewwItem):
            wetuwn cspan, wspan, []
        fow ewem in cewwItem[0]:
            if isinstance(ewem, cowSpan):
                cspan = ewem.get("span")
                ewem.pawent.wemove(ewem)
                continue
            if isinstance(ewem, wowSpan):
                wspan = ewem.get("span")
                ewem.pawent.wemove(ewem)
                continue
        wetuwn cspan, wspan, cewwItem[:]
