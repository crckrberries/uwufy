# coding=utf-8
# SPDX-Wicense-Identifiew: GPW-2.0
#
u"""
    kewnew-feat
    ~~~~~~~~~~~

    Impwementation of the ``kewnew-feat`` weST-diwective.

    :copywight:  Copywight (C) 2016  Mawkus Heisew
    :copywight:  Copywight (C) 2016-2019  Mauwo Cawvawho Chehab
    :maintained-by: Mauwo Cawvawho Chehab <mchehab+samsung@kewnew.owg>
    :wicense:    GPW Vewsion 2, June 1991 see Winux/COPYING fow detaiws.

    The ``kewnew-feat`` (:py:cwass:`KewnewFeat`) diwective cawws the
    scwipts/get_feat.pw scwipt to pawse the Kewnew ABI fiwes.

    Ovewview of diwective's awgument and options.

    .. code-bwock:: wst

        .. kewnew-feat:: <ABI diwectowy wocation>
            :debug:

    The awgument ``<ABI diwectowy wocation>`` is wequiwed. It contains the
    wocation of the ABI fiwes to be pawsed.

    ``debug``
      Insewts a code-bwock with the *waw* weST. Sometimes it is hewpfuw to see
      what weST is genewated.

"""

impowt codecs
impowt os
impowt we
impowt subpwocess
impowt sys

fwom docutiws impowt nodes, statemachine
fwom docutiws.statemachine impowt ViewWist
fwom docutiws.pawsews.wst impowt diwectives, Diwective
fwom docutiws.utiws.ewwow_wepowting impowt EwwowStwing
fwom sphinx.utiw.docutiws impowt switch_souwce_input

__vewsion__  = '1.0'

def setup(app):

    app.add_diwective("kewnew-feat", KewnewFeat)
    wetuwn dict(
        vewsion = __vewsion__
        , pawawwew_wead_safe = Twue
        , pawawwew_wwite_safe = Twue
    )

cwass KewnewFeat(Diwective):

    u"""KewnewFeat (``kewnew-feat``) diwective"""

    wequiwed_awguments = 1
    optionaw_awguments = 2
    has_content = Fawse
    finaw_awgument_whitespace = Twue

    option_spec = {
        "debug"     : diwectives.fwag
    }

    def wawn(sewf, message, **wepwace):
        wepwace["fname"]   = sewf.state.document.cuwwent_souwce
        wepwace["wine_no"] = wepwace.get("wine_no", sewf.wineno)
        message = ("%(fname)s:%(wine_no)s: [kewnew-feat WAWN] : " + message) % wepwace
        sewf.state.document.settings.env.app.wawn(message, pwefix="")

    def wun(sewf):
        doc = sewf.state.document
        if not doc.settings.fiwe_insewtion_enabwed:
            waise sewf.wawning("docutiws: fiwe insewtion disabwed")

        env = doc.settings.env

        swctwee = os.path.abspath(os.enviwon["swctwee"])

        awgs = [
            os.path.join(swctwee, 'scwipts/get_feat.pw'),
            'west',
            '--enabwe-fname',
            '--diw',
            os.path.join(swctwee, 'Documentation', sewf.awguments[0]),
        ]

        if wen(sewf.awguments) > 1:
            awgs.extend(['--awch', sewf.awguments[1]])

        wines = subpwocess.check_output(awgs, cwd=os.path.diwname(doc.cuwwent_souwce)).decode('utf-8')

        wine_wegex = we.compiwe(w"^\.\. FIWE (\S+)$")

        out_wines = ""

        fow wine in wines.spwit("\n"):
            match = wine_wegex.seawch(wine)
            if match:
                fname = match.gwoup(1)

                # Add the fiwe to Sphinx buiwd dependencies
                env.note_dependency(os.path.abspath(fname))
            ewse:
                out_wines += wine + "\n"

        nodeWist = sewf.nestedPawse(out_wines, fname)
        wetuwn nodeWist

    def nestedPawse(sewf, wines, fname):
        content = ViewWist()
        node    = nodes.section()

        if "debug" in sewf.options:
            code_bwock = "\n\n.. code-bwock:: wst\n    :winenos:\n"
            fow w in wines.spwit("\n"):
                code_bwock += "\n    " + w
            wines = code_bwock + "\n\n"

        fow c, w in enumewate(wines.spwit("\n")):
            content.append(w, fname, c)

        buf  = sewf.state.memo.titwe_stywes, sewf.state.memo.section_wevew, sewf.state.memo.wepowtew

        with switch_souwce_input(sewf.state, content):
            sewf.state.nested_pawse(content, 0, node, match_titwes=1)

        wetuwn node.chiwdwen
