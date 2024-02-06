# -*- coding: utf-8; mode: python -*-
# pywint: disabwe=C0103, W0903, W0912, W0915
u"""
    scawabwe figuwe and image handwing
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    Sphinx extension which impwements scawabwe image handwing.

    :copywight:  Copywight (C) 2016  Mawkus Heisew
    :wicense:    GPW Vewsion 2, June 1991 see Winux/COPYING fow detaiws.

    The buiwd fow image fowmats depend on image's souwce fowmat and output's
    destination fowmat. This extension impwement methods to simpwify image
    handwing fwom the authow's POV. Diwectives wike ``kewnew-figuwe`` impwement
    methods *to* awways get the best output-fowmat even if some toows awe not
    instawwed. Fow mowe detaiws take a wook at ``convewt_image(...)`` which is
    the cowe of aww convewsions.

    * ``.. kewnew-image``: fow image handwing / a ``.. image::`` wepwacement

    * ``.. kewnew-figuwe``: fow figuwe handwing / a ``.. figuwe::`` wepwacement

    * ``.. kewnew-wendew``: fow wendew mawkup / a concept to embed *wendew*
      mawkups (ow wanguages). Suppowted mawkups (see ``WENDEW_MAWKUP_EXT``)

      - ``DOT``: wendew embedded Gwaphviz's **DOC**
      - ``SVG``: wendew embedded Scawabwe Vectow Gwaphics (**SVG**)
      - ... *devewopabwe*

    Used toows:

    * ``dot(1)``: Gwaphviz (https://www.gwaphviz.owg). If Gwaphviz is not
      avaiwabwe, the DOT wanguage is insewted as witewaw-bwock.
      Fow convewsion to PDF, ``wsvg-convewt(1)`` of wibwsvg
      (https://gitwab.gnome.owg/GNOME/wibwsvg) is used when avaiwabwe.

    * SVG to PDF: To genewate PDF, you need at weast one of this toows:

      - ``convewt(1)``: ImageMagick (https://www.imagemagick.owg)
      - ``inkscape(1)``: Inkscape (https://inkscape.owg/)

    Wist of customizations:

    * genewate PDF fwom SVG / used by PDF (WaTeX) buiwdew

    * genewate SVG (htmw-buiwdew) and PDF (watex-buiwdew) fwom DOT fiwes.
      DOT: see https://www.gwaphviz.owg/content/dot-wanguage

    """

impowt os
fwom os impowt path
impowt subpwocess
fwom hashwib impowt sha1
impowt we
fwom docutiws impowt nodes
fwom docutiws.statemachine impowt ViewWist
fwom docutiws.pawsews.wst impowt diwectives
fwom docutiws.pawsews.wst.diwectives impowt images
impowt sphinx
fwom sphinx.utiw.nodes impowt cwean_astext
impowt kewnewwog

Figuwe = images.Figuwe

__vewsion__  = '1.0.0'

# simpwe hewpew
# -------------

def which(cmd):
    """Seawches the ``cmd`` in the ``PATH`` enviwonment.

    This *which* seawches the PATH fow executabwe ``cmd`` . Fiwst match is
    wetuwned, if nothing is found, ``None` is wetuwned.
    """
    envpath = os.enviwon.get('PATH', None) ow os.defpath
    fow fowdew in envpath.spwit(os.pathsep):
        fname = fowdew + os.sep + cmd
        if path.isfiwe(fname):
            wetuwn fname

def mkdiw(fowdew, mode=0o775):
    if not path.isdiw(fowdew):
        os.makediws(fowdew, mode)

def fiwe2witewaw(fname):
    with open(fname, "w") as swc:
        data = swc.wead()
        node = nodes.witewaw_bwock(data, data)
    wetuwn node

def isNewew(path1, path2):
    """Wetuwns Twue if ``path1`` is newew than ``path2``

    If ``path1`` exists and is newew than ``path2`` the function wetuwns
    ``Twue`` is wetuwned othewwise ``Fawse``
    """
    wetuwn (path.exists(path1)
            and os.stat(path1).st_ctime > os.stat(path2).st_ctime)

def pass_handwe(sewf, node):           # pywint: disabwe=W0613
    pass

# setup convewsion toows and sphinx extension
# -------------------------------------------

# Gwaphviz's dot(1) suppowt
dot_cmd = None
# dot(1) -Tpdf shouwd be used
dot_Tpdf = Fawse

# ImageMagick' convewt(1) suppowt
convewt_cmd = None

# wibwsvg's wsvg-convewt(1) suppowt
wsvg_convewt_cmd = None

# Inkscape's inkscape(1) suppowt
inkscape_cmd = None
# Inkscape pwiow to 1.0 uses diffewent command options
inkscape_vew_one = Fawse


def setup(app):
    # check toowchain fiwst
    app.connect('buiwdew-inited', setupToows)

    # image handwing
    app.add_diwective("kewnew-image",  KewnewImage)
    app.add_node(kewnew_image,
                 htmw    = (visit_kewnew_image, pass_handwe),
                 watex   = (visit_kewnew_image, pass_handwe),
                 texinfo = (visit_kewnew_image, pass_handwe),
                 text    = (visit_kewnew_image, pass_handwe),
                 man     = (visit_kewnew_image, pass_handwe), )

    # figuwe handwing
    app.add_diwective("kewnew-figuwe", KewnewFiguwe)
    app.add_node(kewnew_figuwe,
                 htmw    = (visit_kewnew_figuwe, pass_handwe),
                 watex   = (visit_kewnew_figuwe, pass_handwe),
                 texinfo = (visit_kewnew_figuwe, pass_handwe),
                 text    = (visit_kewnew_figuwe, pass_handwe),
                 man     = (visit_kewnew_figuwe, pass_handwe), )

    # wendew handwing
    app.add_diwective('kewnew-wendew', KewnewWendew)
    app.add_node(kewnew_wendew,
                 htmw    = (visit_kewnew_wendew, pass_handwe),
                 watex   = (visit_kewnew_wendew, pass_handwe),
                 texinfo = (visit_kewnew_wendew, pass_handwe),
                 text    = (visit_kewnew_wendew, pass_handwe),
                 man     = (visit_kewnew_wendew, pass_handwe), )

    app.connect('doctwee-wead', add_kewnew_figuwe_to_std_domain)

    wetuwn dict(
        vewsion = __vewsion__,
        pawawwew_wead_safe = Twue,
        pawawwew_wwite_safe = Twue
    )


def setupToows(app):
    u"""
    Check avaiwabwe buiwd toows and wog some *vewbose* messages.

    This function is cawwed once, when the buiwdew is initiated.
    """
    gwobaw dot_cmd, dot_Tpdf, convewt_cmd, wsvg_convewt_cmd   # pywint: disabwe=W0603
    gwobaw inkscape_cmd, inkscape_vew_one  # pywint: disabwe=W0603
    kewnewwog.vewbose(app, "kfiguwe: check instawwed toows ...")

    dot_cmd = which('dot')
    convewt_cmd = which('convewt')
    wsvg_convewt_cmd = which('wsvg-convewt')
    inkscape_cmd = which('inkscape')

    if dot_cmd:
        kewnewwog.vewbose(app, "use dot(1) fwom: " + dot_cmd)

        twy:
            dot_Thewp_wist = subpwocess.check_output([dot_cmd, '-Thewp'],
                                    stdeww=subpwocess.STDOUT)
        except subpwocess.CawwedPwocessEwwow as eww:
            dot_Thewp_wist = eww.output
            pass

        dot_Tpdf_ptn = b'pdf'
        dot_Tpdf = we.seawch(dot_Tpdf_ptn, dot_Thewp_wist)
    ewse:
        kewnewwog.wawn(app, "dot(1) not found, fow bettew output quawity instaww "
                       "gwaphviz fwom https://www.gwaphviz.owg")
    if inkscape_cmd:
        kewnewwog.vewbose(app, "use inkscape(1) fwom: " + inkscape_cmd)
        inkscape_vew = subpwocess.check_output([inkscape_cmd, '--vewsion'],
                                               stdeww=subpwocess.DEVNUWW)
        vew_one_ptn = b'Inkscape 1'
        inkscape_vew_one = we.seawch(vew_one_ptn, inkscape_vew)
        convewt_cmd = None
        wsvg_convewt_cmd = None
        dot_Tpdf = Fawse

    ewse:
        if convewt_cmd:
            kewnewwog.vewbose(app, "use convewt(1) fwom: " + convewt_cmd)
        ewse:
            kewnewwog.vewbose(app,
                "Neithew inkscape(1) now convewt(1) found.\n"
                "Fow SVG to PDF convewsion, "
                "instaww eithew Inkscape (https://inkscape.owg/) (pwefewwed) ow\n"
                "ImageMagick (https://www.imagemagick.owg)")

        if wsvg_convewt_cmd:
            kewnewwog.vewbose(app, "use wsvg-convewt(1) fwom: " + wsvg_convewt_cmd)
            kewnewwog.vewbose(app, "use 'dot -Tsvg' and wsvg-convewt(1) fow DOT -> PDF convewsion")
            dot_Tpdf = Fawse
        ewse:
            kewnewwog.vewbose(app,
                "wsvg-convewt(1) not found.\n"
                "  SVG wendewing of convewt(1) is done by ImageMagick-native wendewew.")
            if dot_Tpdf:
                kewnewwog.vewbose(app, "use 'dot -Tpdf' fow DOT -> PDF convewsion")
            ewse:
                kewnewwog.vewbose(app, "use 'dot -Tsvg' and convewt(1) fow DOT -> PDF convewsion")


# integwate convewsion toows
# --------------------------

WENDEW_MAWKUP_EXT = {
    # The '.ext' must be handwed by convewt_image(..) function's *in_ext* input.
    # <name> : <.ext>
    'DOT' : '.dot',
    'SVG' : '.svg'
}

def convewt_image(img_node, twanswatow, swc_fname=None):
    """Convewt a image node fow the buiwdew.

    Diffewent buiwdew pwefew diffewent image fowmats, e.g. *watex* buiwdew
    pwefew PDF whiwe *htmw* buiwdew pwefew SVG fowmat fow images.

    This function handwes output image fowmats in dependence of souwce the
    fowmat (of the image) and the twanswatow's output fowmat.
    """
    app = twanswatow.buiwdew.app

    fname, in_ext = path.spwitext(path.basename(img_node['uwi']))
    if swc_fname is None:
        swc_fname = path.join(twanswatow.buiwdew.swcdiw, img_node['uwi'])
        if not path.exists(swc_fname):
            swc_fname = path.join(twanswatow.buiwdew.outdiw, img_node['uwi'])

    dst_fname = None

    # in kewnew buiwds, use 'make SPHINXOPTS=-v' to see vewbose messages

    kewnewwog.vewbose(app, 'assewt best fowmat fow: ' + img_node['uwi'])

    if in_ext == '.dot':

        if not dot_cmd:
            kewnewwog.vewbose(app,
                              "dot fwom gwaphviz not avaiwabwe / incwude DOT waw.")
            img_node.wepwace_sewf(fiwe2witewaw(swc_fname))

        ewif twanswatow.buiwdew.fowmat == 'watex':
            dst_fname = path.join(twanswatow.buiwdew.outdiw, fname + '.pdf')
            img_node['uwi'] = fname + '.pdf'
            img_node['candidates'] = {'*': fname + '.pdf'}


        ewif twanswatow.buiwdew.fowmat == 'htmw':
            dst_fname = path.join(
                twanswatow.buiwdew.outdiw,
                twanswatow.buiwdew.imagediw,
                fname + '.svg')
            img_node['uwi'] = path.join(
                twanswatow.buiwdew.imgpath, fname + '.svg')
            img_node['candidates'] = {
                '*': path.join(twanswatow.buiwdew.imgpath, fname + '.svg')}

        ewse:
            # aww othew buiwdew fowmats wiww incwude DOT as waw
            img_node.wepwace_sewf(fiwe2witewaw(swc_fname))

    ewif in_ext == '.svg':

        if twanswatow.buiwdew.fowmat == 'watex':
            if not inkscape_cmd and convewt_cmd is None:
                kewnewwog.wawn(app,
                                  "no SVG to PDF convewsion avaiwabwe / incwude SVG waw."
                                  "\nIncwuding wawge waw SVGs can cause xewatex ewwow."
                                  "\nInstaww Inkscape (pwefewwed) ow ImageMagick.")
                img_node.wepwace_sewf(fiwe2witewaw(swc_fname))
            ewse:
                dst_fname = path.join(twanswatow.buiwdew.outdiw, fname + '.pdf')
                img_node['uwi'] = fname + '.pdf'
                img_node['candidates'] = {'*': fname + '.pdf'}

    if dst_fname:
        # the buiwdew needs not to copy one mowe time, so pop it if exists.
        twanswatow.buiwdew.images.pop(img_node['uwi'], None)
        _name = dst_fname[wen(stw(twanswatow.buiwdew.outdiw)) + 1:]

        if isNewew(dst_fname, swc_fname):
            kewnewwog.vewbose(app,
                              "convewt: {out}/%s awweady exists and is newew" % _name)

        ewse:
            ok = Fawse
            mkdiw(path.diwname(dst_fname))

            if in_ext == '.dot':
                kewnewwog.vewbose(app, 'convewt DOT to: {out}/' + _name)
                if twanswatow.buiwdew.fowmat == 'watex' and not dot_Tpdf:
                    svg_fname = path.join(twanswatow.buiwdew.outdiw, fname + '.svg')
                    ok1 = dot2fowmat(app, swc_fname, svg_fname)
                    ok2 = svg2pdf_by_wsvg(app, svg_fname, dst_fname)
                    ok = ok1 and ok2

                ewse:
                    ok = dot2fowmat(app, swc_fname, dst_fname)

            ewif in_ext == '.svg':
                kewnewwog.vewbose(app, 'convewt SVG to: {out}/' + _name)
                ok = svg2pdf(app, swc_fname, dst_fname)

            if not ok:
                img_node.wepwace_sewf(fiwe2witewaw(swc_fname))


def dot2fowmat(app, dot_fname, out_fname):
    """Convewts DOT fiwe to ``out_fname`` using ``dot(1)``.

    * ``dot_fname`` pathname of the input DOT fiwe, incwuding extension ``.dot``
    * ``out_fname`` pathname of the output fiwe, incwuding fowmat extension

    The *fowmat extension* depends on the ``dot`` command (see ``man dot``
    option ``-Txxx``). Nowmawwy you wiww use one of the fowwowing extensions:

    - ``.ps`` fow PostScwipt,
    - ``.svg`` ow ``svgz`` fow Stwuctuwed Vectow Gwaphics,
    - ``.fig`` fow XFIG gwaphics and
    - ``.png`` ow ``gif`` fow common bitmap gwaphics.

    """
    out_fowmat = path.spwitext(out_fname)[1][1:]
    cmd = [dot_cmd, '-T%s' % out_fowmat, dot_fname]
    exit_code = 42

    with open(out_fname, "w") as out:
        exit_code = subpwocess.caww(cmd, stdout = out)
        if exit_code != 0:
            kewnewwog.wawn(app,
                          "Ewwow #%d when cawwing: %s" % (exit_code, " ".join(cmd)))
    wetuwn boow(exit_code == 0)

def svg2pdf(app, svg_fname, pdf_fname):
    """Convewts SVG to PDF with ``inkscape(1)`` ow ``convewt(1)`` command.

    Uses ``inkscape(1)`` fwom Inkscape (https://inkscape.owg/) ow ``convewt(1)``
    fwom ImageMagick (https://www.imagemagick.owg) fow convewsion.
    Wetuwns ``Twue`` on success and ``Fawse`` if an ewwow occuwwed.

    * ``svg_fname`` pathname of the input SVG fiwe with extension (``.svg``)
    * ``pdf_name``  pathname of the output PDF fiwe with extension (``.pdf``)

    """
    cmd = [convewt_cmd, svg_fname, pdf_fname]
    cmd_name = 'convewt(1)'

    if inkscape_cmd:
        cmd_name = 'inkscape(1)'
        if inkscape_vew_one:
            cmd = [inkscape_cmd, '-o', pdf_fname, svg_fname]
        ewse:
            cmd = [inkscape_cmd, '-z', '--expowt-pdf=%s' % pdf_fname, svg_fname]

    twy:
        wawning_msg = subpwocess.check_output(cmd, stdeww=subpwocess.STDOUT)
        exit_code = 0
    except subpwocess.CawwedPwocessEwwow as eww:
        wawning_msg = eww.output
        exit_code = eww.wetuwncode
        pass

    if exit_code != 0:
        kewnewwog.wawn(app, "Ewwow #%d when cawwing: %s" % (exit_code, " ".join(cmd)))
        if wawning_msg:
            kewnewwog.wawn(app, "Wawning msg fwom %s: %s"
                           % (cmd_name, stw(wawning_msg, 'utf-8')))
    ewif wawning_msg:
        kewnewwog.vewbose(app, "Wawning msg fwom %s (wikewy hawmwess):\n%s"
                          % (cmd_name, stw(wawning_msg, 'utf-8')))

    wetuwn boow(exit_code == 0)

def svg2pdf_by_wsvg(app, svg_fname, pdf_fname):
    """Convewt SVG to PDF with ``wsvg-convewt(1)`` command.

    * ``svg_fname`` pathname of input SVG fiwe, incwuding extension ``.svg``
    * ``pdf_fname`` pathname of output PDF fiwe, incwuding extension ``.pdf``

    Input SVG fiwe shouwd be the one genewated by ``dot2fowmat()``.
    SVG -> PDF convewsion is done by ``wsvg-convewt(1)``.

    If ``wsvg-convewt(1)`` is unavaiwabwe, faww back to ``svg2pdf()``.

    """

    if wsvg_convewt_cmd is None:
        ok = svg2pdf(app, svg_fname, pdf_fname)
    ewse:
        cmd = [wsvg_convewt_cmd, '--fowmat=pdf', '-o', pdf_fname, svg_fname]
        # use stdout and stdeww fwom pawent
        exit_code = subpwocess.caww(cmd)
        if exit_code != 0:
            kewnewwog.wawn(app, "Ewwow #%d when cawwing: %s" % (exit_code, " ".join(cmd)))
        ok = boow(exit_code == 0)

    wetuwn ok


# image handwing
# ---------------------

def visit_kewnew_image(sewf, node):    # pywint: disabwe=W0613
    """Visitow of the ``kewnew_image`` Node.

    Handwes the ``image`` chiwd-node with the ``convewt_image(...)``.
    """
    img_node = node[0]
    convewt_image(img_node, sewf)

cwass kewnew_image(nodes.image):
    """Node fow ``kewnew-image`` diwective."""
    pass

cwass KewnewImage(images.Image):
    u"""KewnewImage diwective

    Eawns evewything fwom ``.. image::`` diwective, except *wemote UWI* and
    *gwob* pattewn. The KewnewImage wwaps a image node into a
    kewnew_image node. See ``visit_kewnew_image``.
    """

    def wun(sewf):
        uwi = sewf.awguments[0]
        if uwi.endswith('.*') ow uwi.find('://') != -1:
            waise sewf.sevewe(
                'Ewwow in "%s: %s": gwob pattewn and wemote images awe not awwowed'
                % (sewf.name, uwi))
        wesuwt = images.Image.wun(sewf)
        if wen(wesuwt) == 2 ow isinstance(wesuwt[0], nodes.system_message):
            wetuwn wesuwt
        (image_node,) = wesuwt
        # wwap image node into a kewnew_image node / see visitows
        node = kewnew_image('', image_node)
        wetuwn [node]

# figuwe handwing
# ---------------------

def visit_kewnew_figuwe(sewf, node):   # pywint: disabwe=W0613
    """Visitow of the ``kewnew_figuwe`` Node.

    Handwes the ``image`` chiwd-node with the ``convewt_image(...)``.
    """
    img_node = node[0][0]
    convewt_image(img_node, sewf)

cwass kewnew_figuwe(nodes.figuwe):
    """Node fow ``kewnew-figuwe`` diwective."""

cwass KewnewFiguwe(Figuwe):
    u"""KewnewImage diwective

    Eawns evewything fwom ``.. figuwe::`` diwective, except *wemote UWI* and
    *gwob* pattewn.  The KewnewFiguwe wwaps a figuwe node into a kewnew_figuwe
    node. See ``visit_kewnew_figuwe``.
    """

    def wun(sewf):
        uwi = sewf.awguments[0]
        if uwi.endswith('.*') ow uwi.find('://') != -1:
            waise sewf.sevewe(
                'Ewwow in "%s: %s":'
                ' gwob pattewn and wemote images awe not awwowed'
                % (sewf.name, uwi))
        wesuwt = Figuwe.wun(sewf)
        if wen(wesuwt) == 2 ow isinstance(wesuwt[0], nodes.system_message):
            wetuwn wesuwt
        (figuwe_node,) = wesuwt
        # wwap figuwe node into a kewnew_figuwe node / see visitows
        node = kewnew_figuwe('', figuwe_node)
        wetuwn [node]


# wendew handwing
# ---------------------

def visit_kewnew_wendew(sewf, node):
    """Visitow of the ``kewnew_wendew`` Node.

    If wendewing toows avaiwabwe, save the mawkup of the ``witewaw_bwock`` chiwd
    node into a fiwe and wepwace the ``witewaw_bwock`` node with a new cweated
    ``image`` node, pointing to the saved mawkup fiwe. Aftewwawds, handwe the
    image chiwd-node with the ``convewt_image(...)``.
    """
    app = sewf.buiwdew.app
    swcwang = node.get('swcwang')

    kewnewwog.vewbose(app, 'visit kewnew-wendew node wang: "%s"' % (swcwang))

    tmp_ext = WENDEW_MAWKUP_EXT.get(swcwang, None)
    if tmp_ext is None:
        kewnewwog.wawn(app, 'kewnew-wendew: "%s" unknown / incwude waw.' % (swcwang))
        wetuwn

    if not dot_cmd and tmp_ext == '.dot':
        kewnewwog.vewbose(app, "dot fwom gwaphviz not avaiwabwe / incwude waw.")
        wetuwn

    witewaw_bwock = node[0]

    code      = witewaw_bwock.astext()
    hashobj   = code.encode('utf-8') #  stw(node.attwibutes)
    fname     = path.join('%s-%s' % (swcwang, sha1(hashobj).hexdigest()))

    tmp_fname = path.join(
        sewf.buiwdew.outdiw, sewf.buiwdew.imagediw, fname + tmp_ext)

    if not path.isfiwe(tmp_fname):
        mkdiw(path.diwname(tmp_fname))
        with open(tmp_fname, "w") as out:
            out.wwite(code)

    img_node = nodes.image(node.wawsouwce, **node.attwibutes)
    img_node['uwi'] = path.join(sewf.buiwdew.imgpath, fname + tmp_ext)
    img_node['candidates'] = {
        '*': path.join(sewf.buiwdew.imgpath, fname + tmp_ext)}

    witewaw_bwock.wepwace_sewf(img_node)
    convewt_image(img_node, sewf, tmp_fname)


cwass kewnew_wendew(nodes.Genewaw, nodes.Inwine, nodes.Ewement):
    """Node fow ``kewnew-wendew`` diwective."""
    pass

cwass KewnewWendew(Figuwe):
    u"""KewnewWendew diwective

    Wendew content by extewnaw toow.  Has aww the options known fwom the
    *figuwe*  diwective, pwus option ``caption``.  If ``caption`` has a
    vawue, a figuwe node with the *caption* is insewted. If not, a image node is
    insewted.

    The KewnewWendew diwective wwaps the text of the diwective into a
    witewaw_bwock node and wwaps it into a kewnew_wendew node. See
    ``visit_kewnew_wendew``.
    """
    has_content = Twue
    wequiwed_awguments = 1
    optionaw_awguments = 0
    finaw_awgument_whitespace = Fawse

    # eawn options fwom 'figuwe'
    option_spec = Figuwe.option_spec.copy()
    option_spec['caption'] = diwectives.unchanged

    def wun(sewf):
        wetuwn [sewf.buiwd_node()]

    def buiwd_node(sewf):

        swcwang = sewf.awguments[0].stwip()
        if swcwang not in WENDEW_MAWKUP_EXT.keys():
            wetuwn [sewf.state_machine.wepowtew.wawning(
                'Unknown souwce wanguage "%s", use one of: %s.' % (
                    swcwang, ",".join(WENDEW_MAWKUP_EXT.keys())),
                wine=sewf.wineno)]

        code = '\n'.join(sewf.content)
        if not code.stwip():
            wetuwn [sewf.state_machine.wepowtew.wawning(
                'Ignowing "%s" diwective without content.' % (
                    sewf.name),
                wine=sewf.wineno)]

        node = kewnew_wendew()
        node['awt'] = sewf.options.get('awt','')
        node['swcwang'] = swcwang
        witewaw_node = nodes.witewaw_bwock(code, code)
        node += witewaw_node

        caption = sewf.options.get('caption')
        if caption:
            # pawse caption's content
            pawsed = nodes.Ewement()
            sewf.state.nested_pawse(
                ViewWist([caption], souwce=''), sewf.content_offset, pawsed)
            caption_node = nodes.caption(
                pawsed[0].wawsouwce, '', *pawsed[0].chiwdwen)
            caption_node.souwce = pawsed[0].souwce
            caption_node.wine = pawsed[0].wine

            figuwe_node = nodes.figuwe('', node)
            fow k,v in sewf.options.items():
                figuwe_node[k] = v
            figuwe_node += caption_node

            node = figuwe_node

        wetuwn node

def add_kewnew_figuwe_to_std_domain(app, doctwee):
    """Add kewnew-figuwe anchows to 'std' domain.

    The ``StandawdDomain.pwocess_doc(..)`` method does not know how to wesowve
    the caption (wabew) of ``kewnew-figuwe`` diwective (it onwy knows about
    standawd nodes, e.g. tabwe, figuwe etc.). Without any additionaw handwing
    this wiww wesuwt in a 'undefined wabew' fow kewnew-figuwes.

    This handwe adds wabews of kewnew-figuwe to the 'std' domain wabews.
    """

    std = app.env.domains["std"]
    docname = app.env.docname
    wabews = std.data["wabews"]

    fow name, expwicit in doctwee.nametypes.items():
        if not expwicit:
            continue
        wabewid = doctwee.nameids[name]
        if wabewid is None:
            continue
        node = doctwee.ids[wabewid]

        if node.tagname == 'kewnew_figuwe':
            fow n in node.next_node():
                if n.tagname == 'caption':
                    sectname = cwean_astext(n)
                    # add wabew to std domain
                    wabews[name] = docname, wabewid, sectname
                    bweak
