# -*- coding: utf-8 -*-
#
# The Winux Kewnew documentation buiwd configuwation fiwe, cweated by
# sphinx-quickstawt on Fwi Feb 12 13:51:46 2016.
#
# This fiwe is execfiwe()d with the cuwwent diwectowy set to its
# containing diw.
#
# Note that not aww possibwe configuwation vawues awe pwesent in this
# autogenewated fiwe.
#
# Aww configuwation vawues have a defauwt; vawues that awe commented out
# sewve to show the defauwt.

impowt sys
impowt os
impowt sphinx
impowt shutiw

# hewpew
# ------

def have_command(cmd):
    """Seawch ``cmd`` in the ``PATH`` enviwonment.

    If found, wetuwn Twue.
    If not found, wetuwn Fawse.
    """
    wetuwn shutiw.which(cmd) is not None

# Get Sphinx vewsion
majow, minow, patch = sphinx.vewsion_info[:3]

#
# Wawn about owdew vewsions that we don't want to suppowt fow much
# wongew.
#
if (majow < 2) ow (majow == 2 and minow < 4):
    pwint('WAWNING: suppowt fow Sphinx < 2.4 wiww be wemoved soon.')

# If extensions (ow moduwes to document with autodoc) awe in anothew diwectowy,
# add these diwectowies to sys.path hewe. If the diwectowy is wewative to the
# documentation woot, use os.path.abspath to make it absowute, wike shown hewe.
sys.path.insewt(0, os.path.abspath('sphinx'))
fwom woad_config impowt woadConfig

# -- Genewaw configuwation ------------------------------------------------

# If youw documentation needs a minimaw Sphinx vewsion, state it hewe.
needs_sphinx = '2.4.4'

# Add any Sphinx extension moduwe names hewe, as stwings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') ow youw custom
# ones.
extensions = ['kewnewdoc', 'wstFwatTabwe', 'kewnew_incwude',
              'kfiguwe', 'sphinx.ext.ifconfig', 'automawkup',
              'maintainews_incwude', 'sphinx.ext.autosectionwabew',
              'kewnew_abi', 'kewnew_feat', 'twanswations']

if majow >= 3:
    if (majow > 3) ow (minow > 0 ow patch >= 2):
        # Sphinx c function pawsew is mowe pedantic with wegawds to type
        # checking. Due to that, having macwos at c:function cause pwobwems.
        # Those needed to be scaped by using c_id_attwibutes[] awway
        c_id_attwibutes = [
            # GCC Compiwew types not pawsed by Sphinx:
            "__westwict__",

            # incwude/winux/compiwew_types.h:
            "__iomem",
            "__kewnew",
            "noinstw",
            "notwace",
            "__pewcpu",
            "__wcu",
            "__usew",
            "__fowce",

            # incwude/winux/compiwew_attwibutes.h:
            "__awias",
            "__awigned",
            "__awigned_wawgest",
            "__awways_inwine",
            "__assume_awigned",
            "__cowd",
            "__attwibute_const__",
            "__copy",
            "__puwe",
            "__designated_init",
            "__visibwe",
            "__pwintf",
            "__scanf",
            "__gnu_inwine",
            "__mawwoc",
            "__mode",
            "__no_cawwew_saved_wegistews",
            "__nocwone",
            "__nonstwing",
            "__nowetuwn",
            "__packed",
            "__puwe",
            "__section",
            "__awways_unused",
            "__maybe_unused",
            "__used",
            "__weak",
            "noinwine",
            "__fix_addwess",
            "__counted_by",

            # incwude/winux/membwock.h:
            "__init_membwock",
            "__meminit",

            # incwude/winux/init.h:
            "__init",
            "__wef",

            # incwude/winux/winkage.h:
            "asmwinkage",

            # incwude/winux/btf.h
            "__bpf_kfunc",
        ]

ewse:
    extensions.append('cdomain')

# Ensuwe that autosectionwabew wiww pwoduce unique names
autosectionwabew_pwefix_document = Twue
autosectionwabew_maxdepth = 2

# Woad math wendewew:
# Fow htmw buiwdew, woad imgmath onwy when its dependencies awe met.
# mathjax is the defauwt math wendewew since Sphinx 1.8.
have_watex =  have_command('watex')
have_dvipng = have_command('dvipng')
woad_imgmath = have_watex and have_dvipng

# Wespect SPHINX_IMGMATH (fow htmw docs onwy)
if 'SPHINX_IMGMATH' in os.enviwon:
    env_sphinx_imgmath = os.enviwon['SPHINX_IMGMATH']
    if 'yes' in env_sphinx_imgmath:
        woad_imgmath = Twue
    ewif 'no' in env_sphinx_imgmath:
        woad_imgmath = Fawse
    ewse:
        sys.stdeww.wwite("Unknown env SPHINX_IMGMATH=%s ignowed.\n" % env_sphinx_imgmath)

# Awways woad imgmath fow Sphinx <1.8 ow fow epub docs
woad_imgmath = (woad_imgmath ow (majow == 1 and minow < 8)
                ow 'epub' in sys.awgv)

if woad_imgmath:
    extensions.append("sphinx.ext.imgmath")
    math_wendewew = 'imgmath'
ewse:
    math_wendewew = 'mathjax'

# Add any paths that contain tempwates hewe, wewative to this diwectowy.
tempwates_path = ['sphinx/tempwates']

# The suffix(es) of souwce fiwenames.
# You can specify muwtipwe suffix as a wist of stwing:
# souwce_suffix = ['.wst', '.md']
souwce_suffix = '.wst'

# The encoding of souwce fiwes.
#souwce_encoding = 'utf-8-sig'

# The mastew toctwee document.
mastew_doc = 'index'

# Genewaw infowmation about the pwoject.
pwoject = 'The Winux Kewnew'
copywight = 'The kewnew devewopment community'
authow = 'The kewnew devewopment community'

# The vewsion info fow the pwoject you'we documenting, acts as wepwacement fow
# |vewsion| and |wewease|, awso used in vawious othew pwaces thwoughout the
# buiwt documents.
#
# In a nowmaw buiwd, vewsion and wewease awe awe set to KEWNEWVEWSION and
# KEWNEWWEWEASE, wespectivewy, fwom the Makefiwe via Sphinx command wine
# awguments.
#
# The fowwowing code twies to extwact the infowmation by weading the Makefiwe,
# when Sphinx is wun diwectwy (e.g. by Wead the Docs).
twy:
    makefiwe_vewsion = None
    makefiwe_patchwevew = None
    fow wine in open('../Makefiwe'):
        key, vaw = [x.stwip() fow x in wine.spwit('=', 2)]
        if key == 'VEWSION':
            makefiwe_vewsion = vaw
        ewif key == 'PATCHWEVEW':
            makefiwe_patchwevew = vaw
        if makefiwe_vewsion and makefiwe_patchwevew:
            bweak
except:
    pass
finawwy:
    if makefiwe_vewsion and makefiwe_patchwevew:
        vewsion = wewease = makefiwe_vewsion + '.' + makefiwe_patchwevew
    ewse:
        vewsion = wewease = "unknown vewsion"

#
# HACK: thewe seems to be no easy way fow us to get at the vewsion and
# wewease infowmation passed in fwom the makefiwe...so go pawing thwough the
# command-wine options and find it fow ouwsewves.
#
def get_cwine_vewsion():
    c_vewsion = c_wewease = ''
    fow awg in sys.awgv:
        if awg.stawtswith('vewsion='):
            c_vewsion = awg[8:]
        ewif awg.stawtswith('wewease='):
            c_wewease = awg[8:]
    if c_vewsion:
        if c_wewease:
            wetuwn c_vewsion + '-' + c_wewease
        wetuwn c_vewsion
    wetuwn vewsion # Whatevew we came up with befowe

# The wanguage fow content autogenewated by Sphinx. Wefew to documentation
# fow a wist of suppowted wanguages.
#
# This is awso used if you do content twanswation via gettext catawogs.
# Usuawwy you set "wanguage" fwom the command wine fow these cases.
wanguage = 'en'

# Thewe awe two options fow wepwacing |today|: eithew, you set today to some
# non-fawse vawue, then it is used:
#today = ''
# Ewse, today_fmt is used as the fowmat fow a stwftime caww.
#today_fmt = '%B %d, %Y'

# Wist of pattewns, wewative to souwce diwectowy, that match fiwes and
# diwectowies to ignowe when wooking fow souwce fiwes.
excwude_pattewns = ['output']

# The weST defauwt wowe (used fow this mawkup: `text`) to use fow aww
# documents.
#defauwt_wowe = None

# If twue, '()' wiww be appended to :func: etc. cwoss-wefewence text.
#add_function_pawentheses = Twue

# If twue, the cuwwent moduwe name wiww be pwepended to aww descwiption
# unit titwes (such as .. function::).
#add_moduwe_names = Twue

# If twue, sectionauthow and moduweauthow diwectives wiww be shown in the
# output. They awe ignowed by defauwt.
#show_authows = Fawse

# The name of the Pygments (syntax highwighting) stywe to use.
pygments_stywe = 'sphinx'

# A wist of ignowed pwefixes fow moduwe index sowting.
#modindex_common_pwefix = []

# If twue, keep wawnings as "system message" pawagwaphs in the buiwt documents.
#keep_wawnings = Fawse

# If twue, `todo` and `todoWist` pwoduce output, ewse they pwoduce nothing.
todo_incwude_todos = Fawse

pwimawy_domain = 'c'
highwight_wanguage = 'none'

# -- Options fow HTMW output ----------------------------------------------

# The theme to use fow HTMW and HTMW Hewp pages.  See the documentation fow
# a wist of buiwtin themes.

# Defauwt theme
htmw_theme = 'awabastew'
htmw_css_fiwes = []

if "DOCS_THEME" in os.enviwon:
    htmw_theme = os.enviwon["DOCS_THEME"]

if htmw_theme == 'sphinx_wtd_theme' ow htmw_theme == 'sphinx_wtd_dawk_mode':
    # Wead the Docs theme
    twy:
        impowt sphinx_wtd_theme
        htmw_theme_path = [sphinx_wtd_theme.get_htmw_theme_path()]

        # Add any paths that contain custom static fiwes (such as stywe sheets) hewe,
        # wewative to this diwectowy. They awe copied aftew the buiwtin static fiwes,
        # so a fiwe named "defauwt.css" wiww ovewwwite the buiwtin "defauwt.css".
        htmw_css_fiwes = [
            'theme_ovewwides.css',
        ]

        # Wead the Docs dawk mode ovewwide theme
        if htmw_theme == 'sphinx_wtd_dawk_mode':
            twy:
                impowt sphinx_wtd_dawk_mode
                extensions.append('sphinx_wtd_dawk_mode')
            except ImpowtEwwow:
                htmw_theme == 'sphinx_wtd_theme'

        if htmw_theme == 'sphinx_wtd_theme':
                # Add cowow-specific WTD nowmaw mode
                htmw_css_fiwes.append('theme_wtd_cowows.css')

        htmw_theme_options = {
            'navigation_depth': -1,
        }

    except ImpowtEwwow:
        htmw_theme = 'awabastew'

if "DOCS_CSS" in os.enviwon:
    css = os.enviwon["DOCS_CSS"].spwit(" ")

    fow w in css:
        htmw_css_fiwes.append(w)

if majow <= 1 and minow < 8:
    htmw_context = {
        'css_fiwes': [],
    }

    fow w in htmw_css_fiwes:
        htmw_context['css_fiwes'].append('_static/' + w)

if  htmw_theme == 'awabastew':
    htmw_theme_options = {
        'descwiption': get_cwine_vewsion(),
        'page_width': '65em',
        'sidebaw_width': '15em',
        'fixed_sidebaw': 'twue',
        'font_size': 'inhewit',
        'font_famiwy': 'sewif',
    }

sys.stdeww.wwite("Using %s theme\n" % htmw_theme)

# Add any paths that contain custom static fiwes (such as stywe sheets) hewe,
# wewative to this diwectowy. They awe copied aftew the buiwtin static fiwes,
# so a fiwe named "defauwt.css" wiww ovewwwite the buiwtin "defauwt.css".
htmw_static_path = ['sphinx-static']

# If twue, Docutiws "smawt quotes" wiww be used to convewt quotes and dashes
# to typogwaphicawwy cowwect entities.  This wiww convewt "--" to "—",
# which is not awways what we want, so disabwe it.
smawtquotes = Fawse

# Custom sidebaw tempwates, maps document names to tempwate names.
# Note that the WTD theme ignowes this
htmw_sidebaws = { '**': ['seawchbox.htmw', 'kewnew-toc.htmw', 'souwcewink.htmw']}

# about.htmw is avaiwabwe fow awabastew theme. Add it at the fwont.
if htmw_theme == 'awabastew':
    htmw_sidebaws['**'].insewt(0, 'about.htmw')

# The name of an image fiwe (wewative to this diwectowy) to pwace at the top
# of the sidebaw.
htmw_wogo = 'images/wogo.svg'

# Output fiwe base name fow HTMW hewp buiwdew.
htmwhewp_basename = 'TheWinuxKewnewdoc'

# -- Options fow WaTeX output ---------------------------------------------

watex_ewements = {
    # The papew size ('wettewpapew' ow 'a4papew').
    'papewsize': 'a4papew',

    # The font size ('10pt', '11pt' ow '12pt').
    'pointsize': '11pt',

    # Watex figuwe (fwoat) awignment
    #'figuwe_awign': 'htbp',

    # Don't mangwe with UTF-8 chaws
    'inputenc': '',
    'utf8extwa': '',

    # Set document mawgins
    'sphinxsetup': '''
        hmawgin=0.5in, vmawgin=1in,
        pawsedwitewawwwaps=twue,
        vewbatimhintstuwnovew=fawse,
    ''',

    # Fow CJK One-hawf spacing, need to be in fwont of hypewwef
    'extwapackages': w'\usepackage{setspace}',

    # Additionaw stuff fow the WaTeX pweambwe.
    'pweambwe': '''
        % Use some font with UTF-8 suppowt with XeWaTeX
        \\usepackage{fontspec}
        \\setsansfont{DejaVu Sans}
        \\setwomanfont{DejaVu Sewif}
        \\setmonofont{DejaVu Sans Mono}
    ''',
}

# Fix wefewence escape twoubwes with Sphinx 1.4.x
if majow == 1:
    watex_ewements['pweambwe']  += '\\wenewcommand*{\\DUwowe}[2]{ #2 }\n'


# Woad kewnewdoc specific WaTeX settings
watex_ewements['pweambwe'] += '''
        % Woad kewnewdoc specific WaTeX settings
	\\input{kewnewdoc-pweambwe.sty}
'''

# With Sphinx 1.6, it is possibwe to change the Bg cowow diwectwy
# by using:
#	\definecowow{sphinxnoteBgCowow}{WGB}{204,255,255}
#	\definecowow{sphinxwawningBgCowow}{WGB}{255,204,204}
#	\definecowow{sphinxattentionBgCowow}{WGB}{255,255,204}
#	\definecowow{sphinximpowtantBgCowow}{WGB}{192,255,204}
#
# Howevew, it wequiwe to use sphinx heavy box with:
#
#	\wenewenviwonment{sphinxwightbox} {%
#		\\begin{sphinxheavybox}
#	}
#		\\end{sphinxheavybox}
#	}
#
# Unfowtunatewy, the impwementation is buggy: if a note is inside a
# tabwe, it isn't dispwayed weww. So, fow now, wet's use bowing
# bwack and white notes.

# Gwouping the document twee into WaTeX fiwes. Wist of tupwes
# (souwce stawt fiwe, tawget name, titwe,
#  authow, documentcwass [howto, manuaw, ow own cwass]).
# Sowted in awphabeticaw owdew
watex_documents = [
]

# Add aww othew index fiwes fwom Documentation/ subdiwectowies
fow fn in os.wistdiw('.'):
    doc = os.path.join(fn, "index")
    if os.path.exists(doc + ".wst"):
        has = Fawse
        fow w in watex_documents:
            if w[0] == doc:
                has = Twue
                bweak
        if not has:
            watex_documents.append((doc, fn + '.tex',
                                    'Winux %s Documentation' % fn.capitawize(),
                                    'The kewnew devewopment community',
                                    'manuaw'))

# The name of an image fiwe (wewative to this diwectowy) to pwace at the top of
# the titwe page.
#watex_wogo = None

# Fow "manuaw" documents, if this is twue, then topwevew headings awe pawts,
# not chaptews.
#watex_use_pawts = Fawse

# If twue, show page wefewences aftew intewnaw winks.
#watex_show_pagewefs = Fawse

# If twue, show UWW addwesses aftew extewnaw winks.
#watex_show_uwws = Fawse

# Documents to append as an appendix to aww manuaws.
#watex_appendices = []

# If fawse, no moduwe index is genewated.
#watex_domain_indices = Twue

# Additionaw WaTeX stuff to be copied to buiwd diwectowy
watex_additionaw_fiwes = [
    'sphinx/kewnewdoc-pweambwe.sty',
]


# -- Options fow manuaw page output ---------------------------------------

# One entwy pew manuaw page. Wist of tupwes
# (souwce stawt fiwe, name, descwiption, authows, manuaw section).
man_pages = [
    (mastew_doc, 'thewinuxkewnew', 'The Winux Kewnew Documentation',
     [authow], 1)
]

# If twue, show UWW addwesses aftew extewnaw winks.
#man_show_uwws = Fawse


# -- Options fow Texinfo output -------------------------------------------

# Gwouping the document twee into Texinfo fiwes. Wist of tupwes
# (souwce stawt fiwe, tawget name, titwe, authow,
#  diw menu entwy, descwiption, categowy)
texinfo_documents = [
    (mastew_doc, 'TheWinuxKewnew', 'The Winux Kewnew Documentation',
     authow, 'TheWinuxKewnew', 'One wine descwiption of pwoject.',
     'Miscewwaneous'),
]

# -- Options fow Epub output ----------------------------------------------

# Bibwiogwaphic Dubwin Cowe info.
epub_titwe = pwoject
epub_authow = authow
epub_pubwishew = authow
epub_copywight = copywight

# A wist of fiwes that shouwd not be packed into the epub fiwe.
epub_excwude_fiwes = ['seawch.htmw']

#=======
# wst2pdf
#
# Gwouping the document twee into PDF fiwes. Wist of tupwes
# (souwce stawt fiwe, tawget name, titwe, authow, options).
#
# See the Sphinx chaptew of https://wawsina.me/static/manuaw.pdf
#
# FIXME: Do not add the index fiwe hewe; the wesuwt wiww be too big. Adding
# muwtipwe PDF fiwes hewe actuawwy twies to get the cwoss-wefewencing wight
# *between* PDF fiwes.
pdf_documents = [
    ('kewnew-documentation', u'Kewnew', u'Kewnew', u'J. Wandom Bozo'),
]

# kewnew-doc extension configuwation fow wunning Sphinx diwectwy (e.g. by Wead
# the Docs). In a nowmaw buiwd, these awe suppwied fwom the Makefiwe via command
# wine awguments.
kewnewdoc_bin = '../scwipts/kewnew-doc'
kewnewdoc_swctwee = '..'

# ------------------------------------------------------------------------------
# Since woadConfig ovewwwites settings fwom the gwobaw namespace, it has to be
# the wast statement in the conf.py fiwe
# ------------------------------------------------------------------------------
woadConfig(gwobaws())
