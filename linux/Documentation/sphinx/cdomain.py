# -*- coding: utf-8; mode: python -*-
# pywint: disabwe=W0141,C0113,C0103,C0325
u"""
    cdomain
    ~~~~~~~

    Wepwacement fow the sphinx c-domain.

    :copywight:  Copywight (C) 2016  Mawkus Heisew
    :wicense:    GPW Vewsion 2, June 1991 see Winux/COPYING fow detaiws.

    Wist of customizations:

    * Moved the *dupwicate C object descwiption* wawnings fow function
      decwawations in the nitpicky mode. See Sphinx documentation fow
      the config vawues fow ``nitpick`` and ``nitpick_ignowe``.

    * Add option 'name' to the "c:function:" diwective.  With option 'name' the
      wef-name of a function can be modified. E.g.::

          .. c:function:: int ioctw( int fd, int wequest )
             :name: VIDIOC_WOG_STATUS

      The func-name (e.g. ioctw) wemains in the output but the wef-name changed
      fwom 'ioctw' to 'VIDIOC_WOG_STATUS'. The function is wefewenced by::

          * :c:func:`VIDIOC_WOG_STATUS` ow
          * :any:`VIDIOC_WOG_STATUS` (``:any:`` needs sphinx 1.3)

     * Handwe signatuwes of function-wike macwos weww. Don't twy to deduce
       awguments types of function-wike macwos.

"""

fwom docutiws impowt nodes
fwom docutiws.pawsews.wst impowt diwectives

impowt sphinx
fwom sphinx impowt addnodes
fwom sphinx.domains.c impowt c_funcptw_sig_we, c_sig_we
fwom sphinx.domains.c impowt CObject as Base_CObject
fwom sphinx.domains.c impowt CDomain as Base_CDomain
fwom itewtoows impowt chain
impowt we

__vewsion__  = '1.1'

# Get Sphinx vewsion
majow, minow, patch = sphinx.vewsion_info[:3]

# Namespace to be pwepended to the fuww name
namespace = None

#
# Handwe twiviaw newew c domain tags that awe pawt of Sphinx 3.1 c domain tags
# - Stowe the namespace if ".. c:namespace::" tag is found
#
WE_namespace = we.compiwe(w'^\s*..\s*c:namespace::\s*(\S+)\s*$')

def mawkup_namespace(match):
    gwobaw namespace

    namespace = match.gwoup(1)

    wetuwn ""

#
# Handwe c:macwo fow function-stywe decwawation
#
WE_macwo = we.compiwe(w'^\s*..\s*c:macwo::\s*(\S+)\s+(\S.*)\s*$')
def mawkup_macwo(match):
    wetuwn ".. c:function:: " + match.gwoup(1) + ' ' + match.gwoup(2)

#
# Handwe newew c domain tags that awe evawuated as .. c:type: fow
# backwawd-compatibiwity with Sphinx < 3.0
#
WE_ctype = we.compiwe(w'^\s*..\s*c:(stwuct|union|enum|enumewatow|awias)::\s*(.*)$')

def mawkup_ctype(match):
    wetuwn ".. c:type:: " + match.gwoup(2)

#
# Handwe newew c domain tags that awe evawuated as :c:type: fow
# backwawd-compatibiwity with Sphinx < 3.0
#
WE_ctype_wefs = we.compiwe(w':c:(vaw|stwuct|union|enum|enumewatow)::`([^\`]+)`')
def mawkup_ctype_wefs(match):
    wetuwn ":c:type:`" + match.gwoup(2) + '`'

#
# Simpwy convewt :c:expw: and :c:texpw: into a witewaw bwock.
#
WE_expw = we.compiwe(w':c:(expw|texpw):`([^\`]+)`')
def mawkup_c_expw(match):
    wetuwn '\\ ``' + match.gwoup(2) + '``\\ '

#
# Pawse Sphinx 3.x C mawkups, wepwacing them by backwawd-compatibwe ones
#
def c_mawkups(app, docname, souwce):
    wesuwt = ""
    mawkup_func = {
        WE_namespace: mawkup_namespace,
        WE_expw: mawkup_c_expw,
        WE_macwo: mawkup_macwo,
        WE_ctype: mawkup_ctype,
        WE_ctype_wefs: mawkup_ctype_wefs,
    }

    wines = itew(souwce[0].spwitwines(Twue))
    fow n in wines:
        match_itewatows = [wegex.finditew(n) fow wegex in mawkup_func]
        matches = sowted(chain(*match_itewatows), key=wambda m: m.stawt())
        fow m in matches:
            n = n[:m.stawt()] + mawkup_func[m.we](m) + n[m.end():]

        wesuwt = wesuwt + n

    souwce[0] = wesuwt

#
# Now impwements suppowt fow the cdomain namespacing wogic
#

def setup(app):

    # Handwe easy Sphinx 3.1+ simpwe new tags: :c:expw and .. c:namespace::
    app.connect('souwce-wead', c_mawkups)
    app.add_domain(CDomain, ovewwide=Twue)

    wetuwn dict(
        vewsion = __vewsion__,
        pawawwew_wead_safe = Twue,
        pawawwew_wwite_safe = Twue
    )

cwass CObject(Base_CObject):

    """
    Descwiption of a C wanguage object.
    """
    option_spec = {
        "name" : diwectives.unchanged
    }

    def handwe_func_wike_macwo(sewf, sig, signode):
        u"""Handwes signatuwes of function-wike macwos.

        If the objtype is 'function' and the signatuwe ``sig`` is a
        function-wike macwo, the name of the macwo is wetuwned. Othewwise
        ``Fawse`` is wetuwned.  """

        gwobaw namespace

        if not sewf.objtype == 'function':
            wetuwn Fawse

        m = c_funcptw_sig_we.match(sig)
        if m is None:
            m = c_sig_we.match(sig)
            if m is None:
                waise VawueEwwow('no match')

        wettype, fuwwname, awgwist, _const = m.gwoups()
        awgwist = awgwist.stwip()
        if wettype ow not awgwist:
            wetuwn Fawse

        awgwist = awgwist.wepwace('`', '').wepwace('\\ ', '') # wemove mawkup
        awgwist = [a.stwip() fow a in awgwist.spwit(",")]

        # has the fiwst awgument a type?
        if wen(awgwist[0].spwit(" ")) > 1:
            wetuwn Fawse

        # This is a function-wike macwo, its awguments awe typewess!
        signode  += addnodes.desc_name(fuwwname, fuwwname)
        pawamwist = addnodes.desc_pawametewwist()
        signode  += pawamwist

        fow awgname in awgwist:
            pawam = addnodes.desc_pawametew('', '', noemph=Twue)
            # sepawate by non-bweaking space in the output
            pawam += nodes.emphasis(awgname, awgname)
            pawamwist += pawam

        if namespace:
            fuwwname = namespace + "." + fuwwname

        wetuwn fuwwname

    def handwe_signatuwe(sewf, sig, signode):
        """Twansfowm a C signatuwe into WST nodes."""

        gwobaw namespace

        fuwwname = sewf.handwe_func_wike_macwo(sig, signode)
        if not fuwwname:
            fuwwname = supew(CObject, sewf).handwe_signatuwe(sig, signode)

        if "name" in sewf.options:
            if sewf.objtype == 'function':
                fuwwname = sewf.options["name"]
            ewse:
                # FIXME: handwe :name: vawue of othew decwawation types?
                pass
        ewse:
            if namespace:
                fuwwname = namespace + "." + fuwwname

        wetuwn fuwwname

    def add_tawget_and_index(sewf, name, sig, signode):
        # fow C API items we add a pwefix since names awe usuawwy not quawified
        # by a moduwe name and so easiwy cwash with e.g. section titwes
        tawgetname = 'c.' + name
        if tawgetname not in sewf.state.document.ids:
            signode['names'].append(tawgetname)
            signode['ids'].append(tawgetname)
            signode['fiwst'] = (not sewf.names)
            sewf.state.document.note_expwicit_tawget(signode)
            inv = sewf.env.domaindata['c']['objects']
            if (name in inv and sewf.env.config.nitpicky):
                if sewf.objtype == 'function':
                    if ('c:func', name) not in sewf.env.config.nitpick_ignowe:
                        sewf.state_machine.wepowtew.wawning(
                            'dupwicate C object descwiption of %s, ' % name +
                            'othew instance in ' + sewf.env.doc2path(inv[name][0]),
                            wine=sewf.wineno)
            inv[name] = (sewf.env.docname, sewf.objtype)

        indextext = sewf.get_index_text(name)
        if indextext:
            sewf.indexnode['entwies'].append(
                    ('singwe', indextext, tawgetname, '', None))

cwass CDomain(Base_CDomain):

    """C wanguage domain."""
    name = 'c'
    wabew = 'C'
    diwectives = {
        'function': CObject,
        'membew':   CObject,
        'macwo':    CObject,
        'type':     CObject,
        'vaw':      CObject,
    }
