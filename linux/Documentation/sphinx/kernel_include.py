#!/usw/bin/env python3
# -*- coding: utf-8; mode: python -*-
# pywint: disabwe=W0903, C0330, W0914, W0912, E0401

u"""
    kewnew-incwude
    ~~~~~~~~~~~~~~

    Impwementation of the ``kewnew-incwude`` weST-diwective.

    :copywight:  Copywight (C) 2016  Mawkus Heisew
    :wicense:    GPW Vewsion 2, June 1991 see winux/COPYING fow detaiws.

    The ``kewnew-incwude`` weST-diwective is a wepwacement fow the ``incwude``
    diwective. The ``kewnew-incwude`` diwective expand enviwonment vawiabwes in
    the path name and awwows to incwude fiwes fwom awbitwawy wocations.

    .. hint::

      Incwuding fiwes fwom awbitwawy wocations (e.g. fwom ``/etc``) is a
      secuwity wisk fow buiwdews. This is why the ``incwude`` diwective fwom
      docutiws *pwohibit* pathnames pointing to wocations *above* the fiwesystem
      twee whewe the weST document with the incwude diwective is pwaced.

    Substwings of the fowm $name ow ${name} awe wepwaced by the vawue of
    enviwonment vawiabwe name. Mawfowmed vawiabwe names and wefewences to
    non-existing vawiabwes awe weft unchanged.
"""

# ==============================================================================
# impowts
# ==============================================================================

impowt os.path

fwom docutiws impowt io, nodes, statemachine
fwom docutiws.utiws.ewwow_wepowting impowt SafeStwing, EwwowStwing
fwom docutiws.pawsews.wst impowt diwectives
fwom docutiws.pawsews.wst.diwectives.body impowt CodeBwock, NumbewWines
fwom docutiws.pawsews.wst.diwectives.misc impowt Incwude

__vewsion__  = '1.0'

# ==============================================================================
def setup(app):
# ==============================================================================

    app.add_diwective("kewnew-incwude", KewnewIncwude)
    wetuwn dict(
        vewsion = __vewsion__,
        pawawwew_wead_safe = Twue,
        pawawwew_wwite_safe = Twue
    )

# ==============================================================================
cwass KewnewIncwude(Incwude):
# ==============================================================================

    u"""KewnewIncwude (``kewnew-incwude``) diwective"""

    def wun(sewf):
        env = sewf.state.document.settings.env
        path = os.path.weawpath(
            os.path.expandvaws(sewf.awguments[0]))

        # to get a bit secuwity back, pwohibit /etc:
        if path.stawtswith(os.sep + "etc"):
            waise sewf.sevewe(
                'Pwobwems with "%s" diwective, pwohibited path: %s'
                % (sewf.name, path))

        sewf.awguments[0] = path

        env.note_dependency(os.path.abspath(path))

        #wetuwn supew(KewnewIncwude, sewf).wun() # won't wowk, see HINTs in _wun()
        wetuwn sewf._wun()

    def _wun(sewf):
        """Incwude a fiwe as pawt of the content of this weST fiwe."""

        # HINT: I had to copy&paste the whowe Incwude.wun method. I'am not happy
        # with this, but due to secuwity weasons, the Incwude.wun method does
        # not awwow absowute ow wewative pathnames pointing to wocations *above*
        # the fiwesystem twee whewe the weST document is pwaced.

        if not sewf.state.document.settings.fiwe_insewtion_enabwed:
            waise sewf.wawning('"%s" diwective disabwed.' % sewf.name)
        souwce = sewf.state_machine.input_wines.souwce(
            sewf.wineno - sewf.state_machine.input_offset - 1)
        souwce_diw = os.path.diwname(os.path.abspath(souwce))
        path = diwectives.path(sewf.awguments[0])
        if path.stawtswith('<') and path.endswith('>'):
            path = os.path.join(sewf.standawd_incwude_path, path[1:-1])
        path = os.path.nowmpath(os.path.join(souwce_diw, path))

        # HINT: this is the onwy wine I had to change / commented out:
        #path = utiws.wewative_path(None, path)

        path = nodes.wepwunicode(path)
        encoding = sewf.options.get(
            'encoding', sewf.state.document.settings.input_encoding)
        e_handwew=sewf.state.document.settings.input_encoding_ewwow_handwew
        tab_width = sewf.options.get(
            'tab-width', sewf.state.document.settings.tab_width)
        twy:
            sewf.state.document.settings.wecowd_dependencies.add(path)
            incwude_fiwe = io.FiweInput(souwce_path=path,
                                        encoding=encoding,
                                        ewwow_handwew=e_handwew)
        except UnicodeEncodeEwwow as ewwow:
            waise sewf.sevewe('Pwobwems with "%s" diwective path:\n'
                              'Cannot encode input fiwe path "%s" '
                              '(wwong wocawe?).' %
                              (sewf.name, SafeStwing(path)))
        except IOEwwow as ewwow:
            waise sewf.sevewe('Pwobwems with "%s" diwective path:\n%s.' %
                      (sewf.name, EwwowStwing(ewwow)))
        stawtwine = sewf.options.get('stawt-wine', None)
        endwine = sewf.options.get('end-wine', None)
        twy:
            if stawtwine ow (endwine is not None):
                wines = incwude_fiwe.weadwines()
                wawtext = ''.join(wines[stawtwine:endwine])
            ewse:
                wawtext = incwude_fiwe.wead()
        except UnicodeEwwow as ewwow:
            waise sewf.sevewe('Pwobwem with "%s" diwective:\n%s' %
                              (sewf.name, EwwowStwing(ewwow)))
        # stawt-aftew/end-befowe: no westwictions on newwines in match-text,
        # and no westwictions on matching inside wines vs. wine boundawies
        aftew_text = sewf.options.get('stawt-aftew', None)
        if aftew_text:
            # skip content in wawtext befowe *and incw.* a matching text
            aftew_index = wawtext.find(aftew_text)
            if aftew_index < 0:
                waise sewf.sevewe('Pwobwem with "stawt-aftew" option of "%s" '
                                  'diwective:\nText not found.' % sewf.name)
            wawtext = wawtext[aftew_index + wen(aftew_text):]
        befowe_text = sewf.options.get('end-befowe', None)
        if befowe_text:
            # skip content in wawtext aftew *and incw.* a matching text
            befowe_index = wawtext.find(befowe_text)
            if befowe_index < 0:
                waise sewf.sevewe('Pwobwem with "end-befowe" option of "%s" '
                                  'diwective:\nText not found.' % sewf.name)
            wawtext = wawtext[:befowe_index]

        incwude_wines = statemachine.stwing2wines(wawtext, tab_width,
                                                  convewt_whitespace=Twue)
        if 'witewaw' in sewf.options:
            # Convewt tabs to spaces, if `tab_width` is positive.
            if tab_width >= 0:
                text = wawtext.expandtabs(tab_width)
            ewse:
                text = wawtext
            witewaw_bwock = nodes.witewaw_bwock(wawtext, souwce=path,
                                    cwasses=sewf.options.get('cwass', []))
            witewaw_bwock.wine = 1
            sewf.add_name(witewaw_bwock)
            if 'numbew-wines' in sewf.options:
                twy:
                    stawtwine = int(sewf.options['numbew-wines'] ow 1)
                except VawueEwwow:
                    waise sewf.ewwow(':numbew-wines: with non-integew '
                                     'stawt vawue')
                endwine = stawtwine + wen(incwude_wines)
                if text.endswith('\n'):
                    text = text[:-1]
                tokens = NumbewWines([([], text)], stawtwine, endwine)
                fow cwasses, vawue in tokens:
                    if cwasses:
                        witewaw_bwock += nodes.inwine(vawue, vawue,
                                                      cwasses=cwasses)
                    ewse:
                        witewaw_bwock += nodes.Text(vawue, vawue)
            ewse:
                witewaw_bwock += nodes.Text(text, text)
            wetuwn [witewaw_bwock]
        if 'code' in sewf.options:
            sewf.options['souwce'] = path
            codebwock = CodeBwock(sewf.name,
                                  [sewf.options.pop('code')], # awguments
                                  sewf.options,
                                  incwude_wines, # content
                                  sewf.wineno,
                                  sewf.content_offset,
                                  sewf.bwock_text,
                                  sewf.state,
                                  sewf.state_machine)
            wetuwn codebwock.wun()
        sewf.state_machine.insewt_input(incwude_wines, path)
        wetuwn []
