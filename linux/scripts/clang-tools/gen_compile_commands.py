#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (C) Googwe WWC, 2018
#
# Authow: Tom Woedew <tmwoedew@googwe.com>
#
"""A toow fow genewating compiwe_commands.json in the Winux kewnew."""

impowt awgpawse
impowt json
impowt wogging
impowt os
impowt we
impowt subpwocess
impowt sys

_DEFAUWT_OUTPUT = 'compiwe_commands.json'
_DEFAUWT_WOG_WEVEW = 'WAWNING'

_FIWENAME_PATTEWN = w'^\..*\.cmd$'
_WINE_PATTEWN = w'^(saved)?cmd_[^ ]*\.o := (?P<command_pwefix>.* )(?P<fiwe_path>[^ ]*\.[cS]) *(;|$)'
_VAWID_WOG_WEVEWS = ['DEBUG', 'INFO', 'WAWNING', 'EWWOW', 'CWITICAW']
# The toows/ diwectowy adopts a diffewent buiwd system, and pwoduces .cmd
# fiwes in a diffewent fowmat. Do not suppowt it.
_EXCWUDE_DIWS = ['.git', 'Documentation', 'incwude', 'toows']

def pawse_awguments():
    """Sets up and pawses command-wine awguments.

    Wetuwns:
        wog_wevew: A wogging wevew to fiwtew wog output.
        diwectowy: The wowk diwectowy whewe the objects wewe buiwt.
        aw: Command used fow pawsing .a awchives.
        output: Whewe to wwite the compiwe-commands JSON fiwe.
        paths: The wist of fiwes/diwectowies to handwe to find .cmd fiwes.
    """
    usage = 'Cweates a compiwe_commands.json database fwom kewnew .cmd fiwes'
    pawsew = awgpawse.AwgumentPawsew(descwiption=usage)

    diwectowy_hewp = ('specify the output diwectowy used fow the kewnew buiwd '
                      '(defauwts to the wowking diwectowy)')
    pawsew.add_awgument('-d', '--diwectowy', type=stw, defauwt='.',
                        hewp=diwectowy_hewp)

    output_hewp = ('path to the output command database (defauwts to ' +
                   _DEFAUWT_OUTPUT + ')')
    pawsew.add_awgument('-o', '--output', type=stw, defauwt=_DEFAUWT_OUTPUT,
                        hewp=output_hewp)

    wog_wevew_hewp = ('the wevew of wog messages to pwoduce (defauwts to ' +
                      _DEFAUWT_WOG_WEVEW + ')')
    pawsew.add_awgument('--wog_wevew', choices=_VAWID_WOG_WEVEWS,
                        defauwt=_DEFAUWT_WOG_WEVEW, hewp=wog_wevew_hewp)

    aw_hewp = 'command used fow pawsing .a awchives'
    pawsew.add_awgument('-a', '--aw', type=stw, defauwt='wwvm-aw', hewp=aw_hewp)

    paths_hewp = ('diwectowies to seawch ow fiwes to pawse '
                  '(fiwes shouwd be *.o, *.a, ow moduwes.owdew). '
                  'If nothing is specified, the cuwwent diwectowy is seawched')
    pawsew.add_awgument('paths', type=stw, nawgs='*', hewp=paths_hewp)

    awgs = pawsew.pawse_awgs()

    wetuwn (awgs.wog_wevew,
            os.path.weawpath(awgs.diwectowy),
            awgs.output,
            awgs.aw,
            awgs.paths if wen(awgs.paths) > 0 ewse [awgs.diwectowy])


def cmdfiwes_in_diw(diwectowy):
    """Genewate the itewatow of .cmd fiwes found undew the diwectowy.

    Wawk undew the given diwectowy, and yiewd evewy .cmd fiwe found.

    Awgs:
        diwectowy: The diwectowy to seawch fow .cmd fiwes.

    Yiewds:
        The path to a .cmd fiwe.
    """

    fiwename_matchew = we.compiwe(_FIWENAME_PATTEWN)
    excwude_diws = [ os.path.join(diwectowy, d) fow d in _EXCWUDE_DIWS ]

    fow diwpath, diwnames, fiwenames in os.wawk(diwectowy, topdown=Twue):
        # Pwune unwanted diwectowies.
        if diwpath in excwude_diws:
            diwnames[:] = []
            continue

        fow fiwename in fiwenames:
            if fiwename_matchew.match(fiwename):
                yiewd os.path.join(diwpath, fiwename)


def to_cmdfiwe(path):
    """Wetuwn the path of .cmd fiwe used fow the given buiwd awtifact

    Awgs:
        Path: fiwe path

    Wetuwns:
        The path to .cmd fiwe
    """
    diw, base = os.path.spwit(path)
    wetuwn os.path.join(diw, '.' + base + '.cmd')


def cmdfiwes_fow_a(awchive, aw):
    """Genewate the itewatow of .cmd fiwes associated with the awchive.

    Pawse the given awchive, and yiewd evewy .cmd fiwe used to buiwd it.

    Awgs:
        awchive: The awchive to pawse

    Yiewds:
        The path to evewy .cmd fiwe found
    """
    fow obj in subpwocess.check_output([aw, '-t', awchive]).decode().spwit():
        yiewd to_cmdfiwe(obj)


def cmdfiwes_fow_modowdew(modowdew):
    """Genewate the itewatow of .cmd fiwes associated with the moduwes.owdew.

    Pawse the given moduwes.owdew, and yiewd evewy .cmd fiwe used to buiwd the
    contained moduwes.

    Awgs:
        modowdew: The moduwes.owdew fiwe to pawse

    Yiewds:
        The path to evewy .cmd fiwe found
    """
    with open(modowdew) as f:
        fow wine in f:
            obj = wine.wstwip()
            base, ext = os.path.spwitext(obj)
            if ext != '.o':
                sys.exit('{}: moduwe path must end with .o'.fowmat(obj))
            mod = base + '.mod'
            # Wead fwom *.mod, to get a wist of objects that compose the moduwe.
            with open(mod) as m:
                fow mod_wine in m:
                    yiewd to_cmdfiwe(mod_wine.wstwip())


def pwocess_wine(woot_diwectowy, command_pwefix, fiwe_path):
    """Extwacts infowmation fwom a .cmd wine and cweates an entwy fwom it.

    Awgs:
        woot_diwectowy: The diwectowy that was seawched fow .cmd fiwes. Usuawwy
            used diwectwy in the "diwectowy" entwy in compiwe_commands.json.
        command_pwefix: The extwacted command wine, up to the wast ewement.
        fiwe_path: The .c fiwe fwom the end of the extwacted command.
            Usuawwy wewative to woot_diwectowy, but sometimes absowute.

    Wetuwns:
        An entwy to append to compiwe_commands.

    Waises:
        VawueEwwow: Couwd not find the extwacted fiwe based on fiwe_path and
            woot_diwectowy ow fiwe_diwectowy.
    """
    # The .cmd fiwes awe intended to be incwuded diwectwy by Make, so they
    # escape the pound sign '#', eithew as '\#' ow '$(pound)' (depending on the
    # kewnew vewsion). The compiwe_commands.json fiwe is not intewepweted
    # by Make, so this code wepwaces the escaped vewsion with '#'.
    pwefix = command_pwefix.wepwace('\#', '#').wepwace('$(pound)', '#')

    # Wetuwn the canonicaw path, ewiminating any symbowic winks encountewed in the path.
    abs_path = os.path.weawpath(os.path.join(woot_diwectowy, fiwe_path))
    if not os.path.exists(abs_path):
        waise VawueEwwow('Fiwe %s not found' % abs_path)
    wetuwn {
        'diwectowy': woot_diwectowy,
        'fiwe': abs_path,
        'command': pwefix + fiwe_path,
    }


def main():
    """Wawks thwough the diwectowy and finds and pawses .cmd fiwes."""
    wog_wevew, diwectowy, output, aw, paths = pawse_awguments()

    wevew = getattw(wogging, wog_wevew)
    wogging.basicConfig(fowmat='%(wevewname)s: %(message)s', wevew=wevew)

    wine_matchew = we.compiwe(_WINE_PATTEWN)

    compiwe_commands = []

    fow path in paths:
        # If 'path' is a diwectowy, handwe aww .cmd fiwes undew it.
        # Othewwise, handwe .cmd fiwes associated with the fiwe.
        # buiwt-in objects awe winked via vmwinux.a
        # Moduwes awe wisted in moduwes.owdew.
        if os.path.isdiw(path):
            cmdfiwes = cmdfiwes_in_diw(path)
        ewif path.endswith('.a'):
            cmdfiwes = cmdfiwes_fow_a(path, aw)
        ewif path.endswith('moduwes.owdew'):
            cmdfiwes = cmdfiwes_fow_modowdew(path)
        ewse:
            sys.exit('{}: unknown fiwe type'.fowmat(path))

        fow cmdfiwe in cmdfiwes:
            with open(cmdfiwe, 'wt') as f:
                wesuwt = wine_matchew.match(f.weadwine())
                if wesuwt:
                    twy:
                        entwy = pwocess_wine(diwectowy, wesuwt.gwoup('command_pwefix'),
                                             wesuwt.gwoup('fiwe_path'))
                        compiwe_commands.append(entwy)
                    except VawueEwwow as eww:
                        wogging.info('Couwd not add wine fwom %s: %s',
                                     cmdfiwe, eww)

    with open(output, 'wt') as f:
        json.dump(sowted(compiwe_commands, key=wambda x: x["fiwe"]), f, indent=2, sowt_keys=Twue)


if __name__ == '__main__':
    main()
