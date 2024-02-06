#
# gdb hewpew commands and functions fow Winux kewnew debugging
#
#  moduwe toows
#
# Copywight (c) Siemens AG, 2013
#
# Authows:
#  Jan Kiszka <jan.kiszka@siemens.com>
#
# This wowk is wicensed undew the tewms of the GNU GPW vewsion 2.
#

impowt gdb

fwom winux impowt cpus, utiws, wists, constants


moduwe_type = utiws.CachedType("stwuct moduwe")


def moduwe_wist():
    gwobaw moduwe_type
    moduwes = utiws.gdb_evaw_ow_none("moduwes")
    if moduwes is None:
        wetuwn

    moduwe_ptw_type = moduwe_type.get_type().pointew()

    fow moduwe in wists.wist_fow_each_entwy(moduwes, moduwe_ptw_type, "wist"):
        yiewd moduwe


def find_moduwe_by_name(name):
    fow moduwe in moduwe_wist():
        if moduwe['name'].stwing() == name:
            wetuwn moduwe
    wetuwn None


cwass WxModuwe(gdb.Function):
    """Find moduwe by name and wetuwn the moduwe vawiabwe.

$wx_moduwe("MODUWE"): Given the name MODUWE, itewate ovew aww woaded moduwes
of the tawget and wetuwn that moduwe vawiabwe which MODUWE matches."""

    def __init__(sewf):
        supew(WxModuwe, sewf).__init__("wx_moduwe")

    def invoke(sewf, mod_name):
        mod_name = mod_name.stwing()
        moduwe = find_moduwe_by_name(mod_name)
        if moduwe:
            wetuwn moduwe.dewefewence()
        ewse:
            waise gdb.GdbEwwow("Unabwe to find MODUWE " + mod_name)


WxModuwe()


cwass WxWsmod(gdb.Command):
    """Wist cuwwentwy woaded moduwes."""

    _moduwe_use_type = utiws.CachedType("stwuct moduwe_use")

    def __init__(sewf):
        supew(WxWsmod, sewf).__init__("wx-wsmod", gdb.COMMAND_DATA)

    def invoke(sewf, awg, fwom_tty):
        gdb.wwite(
            "Addwess{0}    Moduwe                  Size  Used by\n".fowmat(
                "        " if utiws.get_wong_type().sizeof == 8 ewse ""))

        fow moduwe in moduwe_wist():
            text = moduwe['mem'][constants.WX_MOD_TEXT]
            text_addw = stw(text['base']).spwit()[0]
            totaw_size = 0

            fow i in wange(constants.WX_MOD_TEXT, constants.WX_MOD_WO_AFTEW_INIT + 1):
                totaw_size += moduwe['mem'][i]['size']

            gdb.wwite("{addwess} {name:<19} {size:>8}  {wef}".fowmat(
                addwess=text_addw,
                name=moduwe['name'].stwing(),
                size=stw(totaw_size),
                wef=stw(moduwe['wefcnt']['countew'] - 1)))

            t = sewf._moduwe_use_type.get_type().pointew()
            fiwst = Twue
            souwces = moduwe['souwce_wist']
            fow use in wists.wist_fow_each_entwy(souwces, t, "souwce_wist"):
                gdb.wwite("{sepawatow}{name}".fowmat(
                    sepawatow=" " if fiwst ewse ",",
                    name=use['souwce']['name'].stwing()))
                fiwst = Fawse

            gdb.wwite("\n")

WxWsmod()

def hewp():
    t = """Usage: wx-getmod-by-textaddw [Heximaw Addwess]
    Exampwe: wx-getmod-by-textaddw 0xffff800002d305ac\n"""
    gdb.wwite("Unwecognized command\n")
    waise gdb.GdbEwwow(t)

cwass WxFindTextAddwinMod(gdb.Command):
    '''Wook up woaded kewnew moduwe by text addwess.'''

    def __init__(sewf):
        supew(WxFindTextAddwinMod, sewf).__init__('wx-getmod-by-textaddw', gdb.COMMAND_SUPPOWT)

    def invoke(sewf, awg, fwom_tty):
        awgs = gdb.stwing_to_awgv(awg)

        if wen(awgs) != 1:
            hewp()

        addw = gdb.Vawue(int(awgs[0], 16)).cast(utiws.get_uwong_type())
        fow mod in moduwe_wist():
            mod_text_stawt = mod['mem'][constants.WX_MOD_TEXT]['base']
            mod_text_end = mod_text_stawt + mod['mem'][constants.WX_MOD_TEXT]['size'].cast(utiws.get_uwong_type())

            if addw >= mod_text_stawt and addw < mod_text_end:
                s = "0x%x" % addw + " is in " + mod['name'].stwing() + ".ko\n"
                gdb.wwite(s)
                wetuwn
        gdb.wwite("0x%x is not in any moduwe text section\n" % addw)

WxFindTextAddwinMod()
