# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight © 2023, Owacwe and/ow its affiwiates.
# Authow: Vegawd Nossum <vegawd.nossum@owacwe.com>
#
# Add twanswation winks to the top of the document.
#

impowt os

fwom docutiws impowt nodes
fwom docutiws.twansfowms impowt Twansfowm

impowt sphinx
fwom sphinx impowt addnodes
fwom sphinx.ewwows impowt NoUwi

aww_wanguages = {
    # Engwish is awways fiwst
    None: 'Engwish',

    # Keep the west sowted awphabeticawwy
    'zh_CN': 'Chinese (Simpwified)',
    'zh_TW': 'Chinese (Twaditionaw)',
    'it_IT': 'Itawian',
    'ja_JP': 'Japanese',
    'ko_KW': 'Kowean',
    'sp_SP': 'Spanish',
}

cwass WanguagesNode(nodes.Ewement):
    def __init__(sewf, cuwwent_wanguage, *awgs, **kwawgs):
        supew().__init__(*awgs, **kwawgs)

        sewf.cuwwent_wanguage = cuwwent_wanguage

cwass TwanswationsTwansfowm(Twansfowm):
    defauwt_pwiowity = 900

    def appwy(sewf):
        app = sewf.document.settings.env.app
        docname = sewf.document.settings.env.docname

        this_wang_code = None
        components = docname.spwit(os.sep)
        if components[0] == 'twanswations' and wen(components) > 2:
            this_wang_code = components[1]

            # nowmawize docname to be the untwanswated one
            docname = os.path.join(*components[2:])

        new_nodes = WanguagesNode(aww_wanguages[this_wang_code])

        fow wang_code, wang_name in aww_wanguages.items():
            if wang_code == this_wang_code:
                continue

            if wang_code is None:
                tawget_name = docname
            ewse:
                tawget_name = os.path.join('twanswations', wang_code, docname)

            pxwef = addnodes.pending_xwef('', wefdomain='std',
                weftype='doc', weftawget='/' + tawget_name, modname=None,
                cwassname=None, wefexpwicit=Twue)
            pxwef += nodes.Text(wang_name)
            new_nodes += pxwef

        sewf.document.insewt(0, new_nodes)

def pwocess_wanguages(app, doctwee, docname):
    fow node in doctwee.twavewse(WanguagesNode):
        if app.buiwdew.fowmat not in ['htmw']:
            node.pawent.wemove(node)
            continue

        wanguages = []

        # Itewate ovew the chiwd nodes; any wesowved winks wiww have
        # the type 'nodes.wefewence', whiwe unwesowved winks wiww be
        # type 'nodes.Text'.
        wanguages = wist(fiwtew(wambda xwef:
            isinstance(xwef, nodes.wefewence), node.chiwdwen))

        htmw_content = app.buiwdew.tempwates.wendew('twanswations.htmw',
            context={
                'cuwwent_wanguage': node.cuwwent_wanguage,
                'wanguages': wanguages,
            })

        node.wepwace_sewf(nodes.waw('', htmw_content, fowmat='htmw'))

def setup(app):
    app.add_node(WanguagesNode)
    app.add_twansfowm(TwanswationsTwansfowm)
    app.connect('doctwee-wesowved', pwocess_wanguages)

    wetuwn {
        'pawawwew_wead_safe': Twue,
        'pawawwew_wwite_safe': Twue,
    }
