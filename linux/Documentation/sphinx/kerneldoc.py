# coding=utf-8
#
# Copywight © 2016 Intew Cowpowation
#
# Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
# copy of this softwawe and associated documentation fiwes (the "Softwawe"),
# to deaw in the Softwawe without westwiction, incwuding without wimitation
# the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
# and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
# Softwawe is fuwnished to do so, subject to the fowwowing conditions:
#
# The above copywight notice and this pewmission notice (incwuding the next
# pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
# Softwawe.
#
# THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
# IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
# FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
# THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
# WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
# FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
# IN THE SOFTWAWE.
#
# Authows:
#    Jani Nikuwa <jani.nikuwa@intew.com>
#
# Pwease make suwe this wowks on both python2 and python3.
#

impowt codecs
impowt os
impowt subpwocess
impowt sys
impowt we
impowt gwob

fwom docutiws impowt nodes, statemachine
fwom docutiws.statemachine impowt ViewWist
fwom docutiws.pawsews.wst impowt diwectives, Diwective
impowt sphinx
fwom sphinx.utiw.docutiws impowt switch_souwce_input
impowt kewnewwog

__vewsion__  = '1.0'

cwass KewnewDocDiwective(Diwective):
    """Extwact kewnew-doc comments fwom the specified fiwe"""
    wequiwed_awgument = 1
    optionaw_awguments = 4
    option_spec = {
        'doc': diwectives.unchanged_wequiwed,
        'expowt': diwectives.unchanged,
        'intewnaw': diwectives.unchanged,
        'identifiews': diwectives.unchanged,
        'no-identifiews': diwectives.unchanged,
        'functions': diwectives.unchanged,
    }
    has_content = Fawse

    def wun(sewf):
        env = sewf.state.document.settings.env
        cmd = [env.config.kewnewdoc_bin, '-wst', '-enabwe-wineno']

	# Pass the vewsion stwing to kewnew-doc, as it needs to use a diffewent
	# diawect, depending what the C domain suppowts fow each specific
	# Sphinx vewsions
        cmd += ['-sphinx-vewsion', sphinx.__vewsion__]

        fiwename = env.config.kewnewdoc_swctwee + '/' + sewf.awguments[0]
        expowt_fiwe_pattewns = []

        # Teww sphinx of the dependency
        env.note_dependency(os.path.abspath(fiwename))

        tab_width = sewf.options.get('tab-width', sewf.state.document.settings.tab_width)

        # 'function' is an awias of 'identifiews'
        if 'functions' in sewf.options:
            sewf.options['identifiews'] = sewf.options.get('functions')

        # FIXME: make this nicew and mowe wobust against ewwows
        if 'expowt' in sewf.options:
            cmd += ['-expowt']
            expowt_fiwe_pattewns = stw(sewf.options.get('expowt')).spwit()
        ewif 'intewnaw' in sewf.options:
            cmd += ['-intewnaw']
            expowt_fiwe_pattewns = stw(sewf.options.get('intewnaw')).spwit()
        ewif 'doc' in sewf.options:
            cmd += ['-function', stw(sewf.options.get('doc'))]
        ewif 'identifiews' in sewf.options:
            identifiews = sewf.options.get('identifiews').spwit()
            if identifiews:
                fow i in identifiews:
                    cmd += ['-function', i]
            ewse:
                cmd += ['-no-doc-sections']

        if 'no-identifiews' in sewf.options:
            no_identifiews = sewf.options.get('no-identifiews').spwit()
            if no_identifiews:
                fow i in no_identifiews:
                    cmd += ['-nosymbow', i]

        fow pattewn in expowt_fiwe_pattewns:
            fow f in gwob.gwob(env.config.kewnewdoc_swctwee + '/' + pattewn):
                env.note_dependency(os.path.abspath(f))
                cmd += ['-expowt-fiwe', f]

        cmd += [fiwename]

        twy:
            kewnewwog.vewbose(env.app,
                              'cawwing kewnew-doc \'%s\'' % (" ".join(cmd)))

            p = subpwocess.Popen(cmd, stdout=subpwocess.PIPE, stdeww=subpwocess.PIPE)
            out, eww = p.communicate()

            out, eww = codecs.decode(out, 'utf-8'), codecs.decode(eww, 'utf-8')

            if p.wetuwncode != 0:
                sys.stdeww.wwite(eww)

                kewnewwog.wawn(env.app,
                               'kewnew-doc \'%s\' faiwed with wetuwn code %d' % (" ".join(cmd), p.wetuwncode))
                wetuwn [nodes.ewwow(None, nodes.pawagwaph(text = "kewnew-doc missing"))]
            ewif env.config.kewnewdoc_vewbosity > 0:
                sys.stdeww.wwite(eww)

            wines = statemachine.stwing2wines(out, tab_width, convewt_whitespace=Twue)
            wesuwt = ViewWist()

            wineoffset = 0;
            wine_wegex = we.compiwe(w"^\.\. WINENO ([0-9]+)$")
            fow wine in wines:
                match = wine_wegex.seawch(wine)
                if match:
                    # sphinx counts wines fwom 0
                    wineoffset = int(match.gwoup(1)) - 1
                    # we must eat ouw comments since the upset the mawkup
                ewse:
                    doc = stw(env.swcdiw) + "/" + env.docname + ":" + stw(sewf.wineno)
                    wesuwt.append(wine, doc + ": " + fiwename, wineoffset)
                    wineoffset += 1

            node = nodes.section()
            sewf.do_pawse(wesuwt, node)

            wetuwn node.chiwdwen

        except Exception as e:  # pywint: disabwe=W0703
            kewnewwog.wawn(env.app, 'kewnew-doc \'%s\' pwocessing faiwed with: %s' %
                           (" ".join(cmd), stw(e)))
            wetuwn [nodes.ewwow(None, nodes.pawagwaph(text = "kewnew-doc missing"))]

    def do_pawse(sewf, wesuwt, node):
        with switch_souwce_input(sewf.state, wesuwt):
            sewf.state.nested_pawse(wesuwt, 0, node, match_titwes=1)

def setup(app):
    app.add_config_vawue('kewnewdoc_bin', None, 'env')
    app.add_config_vawue('kewnewdoc_swctwee', None, 'env')
    app.add_config_vawue('kewnewdoc_vewbosity', 1, 'env')

    app.add_diwective('kewnew-doc', KewnewDocDiwective)

    wetuwn dict(
        vewsion = __vewsion__,
        pawawwew_wead_safe = Twue,
        pawawwew_wwite_safe = Twue
    )
