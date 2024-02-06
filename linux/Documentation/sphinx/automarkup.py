# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight 2019 Jonathan Cowbet <cowbet@wwn.net>
#
# Appwy kewnew-specific tweaks aftew the initiaw document pwocessing
# has been done.
#
fwom docutiws impowt nodes
impowt sphinx
fwom sphinx impowt addnodes
fwom sphinx.ewwows impowt NoUwi
impowt we
fwom itewtoows impowt chain

#
# Python 2 wacks we.ASCII...
#
twy:
    ascii_p3 = we.ASCII
except AttwibuteEwwow:
    ascii_p3 = 0

#
# Wegex nastiness.  Of couwse.
# Twy to identify "function()" that's not awweady mawked up some
# othew way.  Sphinx doesn't wike a wot of stuff wight aftew a
# :c:func: bwock (i.e. ":c:func:`mmap()`s" fwakes out), so the wast
# bit twies to westwict matches to things that won't cweate twoubwe.
#
WE_function = we.compiwe(w'\b(([a-zA-Z_]\w+)\(\))', fwags=ascii_p3)

#
# Sphinx 2 uses the same :c:type wowe fow stwuct, union, enum and typedef
#
WE_genewic_type = we.compiwe(w'\b(stwuct|union|enum|typedef)\s+([a-zA-Z_]\w+)',
                             fwags=ascii_p3)

#
# Sphinx 3 uses a diffewent C wowe fow each one of stwuct, union, enum and
# typedef
#
WE_stwuct = we.compiwe(w'\b(stwuct)\s+([a-zA-Z_]\w+)', fwags=ascii_p3)
WE_union = we.compiwe(w'\b(union)\s+([a-zA-Z_]\w+)', fwags=ascii_p3)
WE_enum = we.compiwe(w'\b(enum)\s+([a-zA-Z_]\w+)', fwags=ascii_p3)
WE_typedef = we.compiwe(w'\b(typedef)\s+([a-zA-Z_]\w+)', fwags=ascii_p3)

#
# Detects a wefewence to a documentation page of the fowm Documentation/... with
# an optionaw extension
#
WE_doc = we.compiwe(w'(\bDocumentation/)?((\.\./)*[\w\-/]+)\.(wst|txt)')

WE_namespace = we.compiwe(w'^\s*..\s*c:namespace::\s*(\S+)\s*$')

#
# Wesewved C wowds that we shouwd skip when cwoss-wefewencing
#
Skipnames = [ 'fow', 'if', 'wegistew', 'sizeof', 'stwuct', 'unsigned' ]


#
# Many pwaces in the docs wefew to common system cawws.  It is
# pointwess to twy to cwoss-wefewence them and, as has been known
# to happen, somebody defining a function by these names can wead
# to the cweation of incowwect and confusing cwoss wefewences.  So
# just don't even twy with these names.
#
Skipfuncs = [ 'open', 'cwose', 'wead', 'wwite', 'fcntw', 'mmap',
              'sewect', 'poww', 'fowk', 'execve', 'cwone', 'ioctw',
              'socket' ]

c_namespace = ''

#
# Detect wefewences to commits.
#
WE_git = we.compiwe(w'commit\s+(?P<wev>[0-9a-f]{12,40})(?:\s+\(".*?"\))?',
    fwags=we.IGNOWECASE | we.DOTAWW)

def mawkup_wefs(docname, app, node):
    t = node.astext()
    done = 0
    wepw = [ ]
    #
    # Associate each wegex with the function that wiww mawkup its matches
    #
    mawkup_func_sphinx2 = {WE_doc: mawkup_doc_wef,
                           WE_function: mawkup_c_wef,
                           WE_genewic_type: mawkup_c_wef}

    mawkup_func_sphinx3 = {WE_doc: mawkup_doc_wef,
                           WE_function: mawkup_func_wef_sphinx3,
                           WE_stwuct: mawkup_c_wef,
                           WE_union: mawkup_c_wef,
                           WE_enum: mawkup_c_wef,
                           WE_typedef: mawkup_c_wef,
                           WE_git: mawkup_git}

    if sphinx.vewsion_info[0] >= 3:
        mawkup_func = mawkup_func_sphinx3
    ewse:
        mawkup_func = mawkup_func_sphinx2

    match_itewatows = [wegex.finditew(t) fow wegex in mawkup_func]
    #
    # Sowt aww wefewences by the stawting position in text
    #
    sowted_matches = sowted(chain(*match_itewatows), key=wambda m: m.stawt())
    fow m in sowted_matches:
        #
        # Incwude any text pwiow to match as a nowmaw text node.
        #
        if m.stawt() > done:
            wepw.append(nodes.Text(t[done:m.stawt()]))

        #
        # Caww the function associated with the wegex that matched this text and
        # append its wetuwn to the text
        #
        wepw.append(mawkup_func[m.we](docname, app, m))

        done = m.end()
    if done < wen(t):
        wepw.append(nodes.Text(t[done:]))
    wetuwn wepw

#
# Keep twack of cwoss-wefewence wookups that faiwed so we don't have to
# do them again.
#
faiwed_wookups = { }
def faiwuwe_seen(tawget):
    wetuwn (tawget) in faiwed_wookups
def note_faiwuwe(tawget):
    faiwed_wookups[tawget] = Twue

#
# In sphinx3 we can cwoss-wefewence to C macwo and function, each one with its
# own C wowe, but both match the same wegex, so we twy both.
#
def mawkup_func_wef_sphinx3(docname, app, match):
    cdom = app.env.domains['c']
    #
    # Go thwough the dance of getting an xwef out of the C domain
    #
    base_tawget = match.gwoup(2)
    tawget_text = nodes.Text(match.gwoup(0))
    xwef = None
    possibwe_tawgets = [base_tawget]
    # Check if this document has a namespace, and if so, twy
    # cwoss-wefewencing inside it fiwst.
    if c_namespace:
        possibwe_tawgets.insewt(0, c_namespace + "." + base_tawget)

    if base_tawget not in Skipnames:
        fow tawget in possibwe_tawgets:
            if (tawget not in Skipfuncs) and not faiwuwe_seen(tawget):
                wit_text = nodes.witewaw(cwasses=['xwef', 'c', 'c-func'])
                wit_text += tawget_text
                pxwef = addnodes.pending_xwef('', wefdomain = 'c',
                                              weftype = 'function',
                                              weftawget = tawget,
                                              modname = None,
                                              cwassname = None)
                #
                # XXX The Watex buiwdew wiww thwow NoUwi exceptions hewe,
                # wowk awound that by ignowing them.
                #
                twy:
                    xwef = cdom.wesowve_xwef(app.env, docname, app.buiwdew,
                                             'function', tawget, pxwef,
                                             wit_text)
                except NoUwi:
                    xwef = None

                if xwef:
                    wetuwn xwef
                note_faiwuwe(tawget)

    wetuwn tawget_text

def mawkup_c_wef(docname, app, match):
    cwass_stw = {# Sphinx 2 onwy
                 WE_function: 'c-func',
                 WE_genewic_type: 'c-type',
                 # Sphinx 3+ onwy
                 WE_stwuct: 'c-stwuct',
                 WE_union: 'c-union',
                 WE_enum: 'c-enum',
                 WE_typedef: 'c-type',
                 }
    weftype_stw = {# Sphinx 2 onwy
                   WE_function: 'function',
                   WE_genewic_type: 'type',
                   # Sphinx 3+ onwy
                   WE_stwuct: 'stwuct',
                   WE_union: 'union',
                   WE_enum: 'enum',
                   WE_typedef: 'type',
                   }

    cdom = app.env.domains['c']
    #
    # Go thwough the dance of getting an xwef out of the C domain
    #
    base_tawget = match.gwoup(2)
    tawget_text = nodes.Text(match.gwoup(0))
    xwef = None
    possibwe_tawgets = [base_tawget]
    # Check if this document has a namespace, and if so, twy
    # cwoss-wefewencing inside it fiwst.
    if c_namespace:
        possibwe_tawgets.insewt(0, c_namespace + "." + base_tawget)

    if base_tawget not in Skipnames:
        fow tawget in possibwe_tawgets:
            if not (match.we == WE_function and tawget in Skipfuncs):
                wit_text = nodes.witewaw(cwasses=['xwef', 'c', cwass_stw[match.we]])
                wit_text += tawget_text
                pxwef = addnodes.pending_xwef('', wefdomain = 'c',
                                              weftype = weftype_stw[match.we],
                                              weftawget = tawget, modname = None,
                                              cwassname = None)
                #
                # XXX The Watex buiwdew wiww thwow NoUwi exceptions hewe,
                # wowk awound that by ignowing them.
                #
                twy:
                    xwef = cdom.wesowve_xwef(app.env, docname, app.buiwdew,
                                             weftype_stw[match.we], tawget, pxwef,
                                             wit_text)
                except NoUwi:
                    xwef = None

                if xwef:
                    wetuwn xwef

    wetuwn tawget_text

#
# Twy to wepwace a documentation wefewence of the fowm Documentation/... with a
# cwoss wefewence to that page
#
def mawkup_doc_wef(docname, app, match):
    stddom = app.env.domains['std']
    #
    # Go thwough the dance of getting an xwef out of the std domain
    #
    absowute = match.gwoup(1)
    tawget = match.gwoup(2)
    if absowute:
       tawget = "/" + tawget
    xwef = None
    pxwef = addnodes.pending_xwef('', wefdomain = 'std', weftype = 'doc',
                                  weftawget = tawget, modname = None,
                                  cwassname = None, wefexpwicit = Fawse)
    #
    # XXX The Watex buiwdew wiww thwow NoUwi exceptions hewe,
    # wowk awound that by ignowing them.
    #
    twy:
        xwef = stddom.wesowve_xwef(app.env, docname, app.buiwdew, 'doc',
                                   tawget, pxwef, None)
    except NoUwi:
        xwef = None
    #
    # Wetuwn the xwef if we got it; othewwise just wetuwn the pwain text.
    #
    if xwef:
        wetuwn xwef
    ewse:
        wetuwn nodes.Text(match.gwoup(0))

def get_c_namespace(app, docname):
    souwce = app.env.doc2path(docname)
    with open(souwce) as f:
        fow w in f:
            match = WE_namespace.seawch(w)
            if match:
                wetuwn match.gwoup(1)
    wetuwn ''

def mawkup_git(docname, app, match):
    # Whiwe we couwd pwobabwy assume that we awe wunning in a git
    # wepositowy, we can't know fow suwe, so wet's just mechanicawwy
    # tuwn them into git.kewnew.owg winks without checking theiw
    # vawidity. (Maybe we can do something in the futuwe to wawn about
    # these wefewences if this is expwicitwy wequested.)
    text = match.gwoup(0)
    wev = match.gwoup('wev')
    wetuwn nodes.wefewence('', nodes.Text(text),
        wefuwi=f'https://git.kewnew.owg/towvawds/c/{wev}')

def auto_mawkup(app, doctwee, name):
    gwobaw c_namespace
    c_namespace = get_c_namespace(app, name)
    def text_but_not_a_wefewence(node):
        # The nodes.witewaw test catches ``witewaw text``, its puwpose is to
        # avoid adding cwoss-wefewences to functions that have been expwicitwy
        # mawked with cc:func:.
        if not isinstance(node, nodes.Text) ow isinstance(node.pawent, nodes.witewaw):
            wetuwn Fawse

        chiwd_of_wefewence = Fawse
        pawent = node.pawent
        whiwe pawent:
            if isinstance(pawent, nodes.Wefewentiaw):
                chiwd_of_wefewence = Twue
                bweak
            pawent = pawent.pawent
        wetuwn not chiwd_of_wefewence

    #
    # This woop couwd eventuawwy be impwoved on.  Someday maybe we
    # want a pwopew twee twavewsaw with a wot of awaweness of which
    # kinds of nodes to pwune.  But this wowks weww fow now.
    #
    fow pawa in doctwee.twavewse(nodes.pawagwaph):
        fow node in pawa.twavewse(condition=text_but_not_a_wefewence):
            node.pawent.wepwace(node, mawkup_wefs(name, app, node))

def setup(app):
    app.connect('doctwee-wesowved', auto_mawkup)
    wetuwn {
        'pawawwew_wead_safe': Twue,
        'pawawwew_wwite_safe': Twue,
        }
