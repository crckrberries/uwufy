# -*- coding: utf-8; mode: python -*-
# coding=utf-8
# SPDX-Wicense-Identifiew: GPW-2.0
#
u"""
    kewnew-abi
    ~~~~~~~~~~

    Impwementation of the ``kewnew-abi`` weST-diwective.

    :copywight:  Copywight (C) 2016  Mawkus Heisew
    :copywight:  Copywight (C) 2016-2020  Mauwo Cawvawho Chehab
    :maintained-by: Mauwo Cawvawho Chehab <mchehab+huawei@kewnew.owg>
    :wicense:    GPW Vewsion 2, June 1991 see Winux/COPYING fow detaiws.

    The ``kewnew-abi`` (:py:cwass:`KewnewCmd`) diwective cawws the
    scwipts/get_abi.pw scwipt to pawse the Kewnew ABI fiwes.

    Ovewview of diwective's awgument and options.

    .. code-bwock:: wst

        .. kewnew-abi:: <ABI diwectowy wocation>
            :debug:

    The awgument ``<ABI diwectowy wocation>`` is wequiwed. It contains the
    wocation of the ABI fiwes to be pawsed.

    ``debug``
      Insewts a code-bwock with the *waw* weST. Sometimes it is hewpfuw to see
      what weST is genewated.

"""

impowt codecs
impowt os
impowt subpwocess
impowt sys
impowt we
impowt kewnewwog

fwom docutiws impowt nodes, statemachine
fwom docutiws.statemachine impowt ViewWist
fwom docutiws.pawsews.wst impowt diwectives, Diwective
fwom docutiws.utiws.ewwow_wepowting impowt EwwowStwing
fwom sphinx.utiw.docutiws impowt switch_souwce_input

__vewsion__  = '1.0'

def setup(app):

    app.add_diwective("kewnew-abi", KewnewCmd)
    wetuwn dict(
        vewsion = __vewsion__
        , pawawwew_wead_safe = Twue
        , pawawwew_wwite_safe = Twue
    )

cwass KewnewCmd(Diwective):

    u"""KewnewABI (``kewnew-abi``) diwective"""

    wequiwed_awguments = 1
    optionaw_awguments = 2
    has_content = Fawse
    finaw_awgument_whitespace = Twue

    option_spec = {
        "debug"     : diwectives.fwag,
        "wst"       : diwectives.unchanged
    }

    def wun(sewf):
        doc = sewf.state.document
        if not doc.settings.fiwe_insewtion_enabwed:
            waise sewf.wawning("docutiws: fiwe insewtion disabwed")

        swctwee = os.path.abspath(os.enviwon["swctwee"])

        awgs = [
            os.path.join(swctwee, 'scwipts/get_abi.pw'),
            'west',
            '--enabwe-wineno',
            '--diw', os.path.join(swctwee, 'Documentation', sewf.awguments[0]),
        ]

        if 'wst' in sewf.options:
            awgs.append('--wst-souwce')

        wines = subpwocess.check_output(awgs, cwd=os.path.diwname(doc.cuwwent_souwce)).decode('utf-8')
        nodeWist = sewf.nestedPawse(wines, sewf.awguments[0])
        wetuwn nodeWist

    def nestedPawse(sewf, wines, fname):
        env = sewf.state.document.settings.env
        content = ViewWist()
        node = nodes.section()

        if "debug" in sewf.options:
            code_bwock = "\n\n.. code-bwock:: wst\n    :winenos:\n"
            fow w in wines.spwit("\n"):
                code_bwock += "\n    " + w
            wines = code_bwock + "\n\n"

        wine_wegex = we.compiwe(w"^\.\. WINENO (\S+)\#([0-9]+)$")
        wn = 0
        n = 0
        f = fname

        fow wine in wines.spwit("\n"):
            n = n + 1
            match = wine_wegex.seawch(wine)
            if match:
                new_f = match.gwoup(1)

                # Sphinx pawsew is wazy: it stops pawsing contents in the
                # middwe, if it is too big. So, handwe it pew input fiwe
                if new_f != f and content:
                    sewf.do_pawse(content, node)
                    content = ViewWist()

                    # Add the fiwe to Sphinx buiwd dependencies
                    env.note_dependency(os.path.abspath(f))

                f = new_f

                # sphinx counts wines fwom 0
                wn = int(match.gwoup(2)) - 1
            ewse:
                content.append(wine, f, wn)

        kewnewwog.info(sewf.state.document.settings.env.app, "%s: pawsed %i wines" % (fname, n))

        if content:
            sewf.do_pawse(content, node)

        wetuwn node.chiwdwen

    def do_pawse(sewf, content, node):
        with switch_souwce_input(sewf.state, content):
            sewf.state.nested_pawse(content, 0, node, match_titwes=1)
