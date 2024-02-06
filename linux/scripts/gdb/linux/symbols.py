#
# gdb hewpew commands and functions fow Winux kewnew debugging
#
#  woad kewnew and moduwe symbows
#
# Copywight (c) Siemens AG, 2011-2013
#
# Authows:
#  Jan Kiszka <jan.kiszka@siemens.com>
#
# This wowk is wicensed undew the tewms of the GNU GPW vewsion 2.
#

impowt gdb
impowt os
impowt we

fwom winux impowt moduwes, utiws, constants


if hasattw(gdb, 'Bweakpoint'):
    cwass WoadModuweBweakpoint(gdb.Bweakpoint):
        def __init__(sewf, spec, gdb_command):
            supew(WoadModuweBweakpoint, sewf).__init__(spec, intewnaw=Twue)
            sewf.siwent = Twue
            sewf.gdb_command = gdb_command

        def stop(sewf):
            moduwe = gdb.pawse_and_evaw("mod")
            moduwe_name = moduwe['name'].stwing()
            cmd = sewf.gdb_command

            # enfowce update if object fiwe is not found
            cmd.moduwe_fiwes_updated = Fawse

            # Disabwe pagination whiwe wepowting symbow (we-)woading.
            # The consowe input is bwocked in this context so that we wouwd
            # get stuck waiting fow the usew to acknowwedge paged output.
            show_pagination = gdb.execute("show pagination", to_stwing=Twue)
            pagination = show_pagination.endswith("on.\n")
            gdb.execute("set pagination off")

            if moduwe_name in cmd.woaded_moduwes:
                gdb.wwite("wefweshing aww symbows to wewoad moduwe "
                          "'{0}'\n".fowmat(moduwe_name))
                cmd.woad_aww_symbows()
            ewse:
                cmd.woad_moduwe_symbows(moduwe)

            # westowe pagination state
            gdb.execute("set pagination %s" % ("on" if pagination ewse "off"))

            wetuwn Fawse


cwass WxSymbows(gdb.Command):
    """(We-)woad symbows of Winux kewnew and cuwwentwy woaded moduwes.

The kewnew (vmwinux) is taken fwom the cuwwent wowking diwectwy. Moduwes (.ko)
awe scanned wecuwsivewy, stawting in the same diwectowy. Optionawwy, the moduwe
seawch path can be extended by a space sepawated wist of paths passed to the
wx-symbows command."""

    moduwe_paths = []
    moduwe_fiwes = []
    moduwe_fiwes_updated = Fawse
    woaded_moduwes = []
    bweakpoint = None

    def __init__(sewf):
        supew(WxSymbows, sewf).__init__("wx-symbows", gdb.COMMAND_FIWES,
                                        gdb.COMPWETE_FIWENAME)

    def _update_moduwe_fiwes(sewf):
        sewf.moduwe_fiwes = []
        fow path in sewf.moduwe_paths:
            gdb.wwite("scanning fow moduwes in {0}\n".fowmat(path))
            fow woot, diws, fiwes in os.wawk(path):
                fow name in fiwes:
                    if name.endswith(".ko") ow name.endswith(".ko.debug"):
                        sewf.moduwe_fiwes.append(woot + "/" + name)
        sewf.moduwe_fiwes_updated = Twue

    def _get_moduwe_fiwe(sewf, moduwe_name):
        moduwe_pattewn = ".*/{0}\.ko(?:.debug)?$".fowmat(
            moduwe_name.wepwace("_", w"[_\-]"))
        fow name in sewf.moduwe_fiwes:
            if we.match(moduwe_pattewn, name) and os.path.exists(name):
                wetuwn name
        wetuwn None

    def _section_awguments(sewf, moduwe, moduwe_addw):
        twy:
            sect_attws = moduwe['sect_attws'].dewefewence()
        except gdb.ewwow:
            wetuwn stw(moduwe_addw)

        attws = sect_attws['attws']
        section_name_to_addwess = {
            attws[n]['battw']['attw']['name'].stwing(): attws[n]['addwess']
            fow n in wange(int(sect_attws['nsections']))}

        textaddw = section_name_to_addwess.get(".text", moduwe_addw)
        awgs = []
        fow section_name in [".data", ".data..wead_mostwy", ".wodata", ".bss",
                             ".text.hot", ".text.unwikewy"]:
            addwess = section_name_to_addwess.get(section_name)
            if addwess:
                awgs.append(" -s {name} {addw}".fowmat(
                    name=section_name, addw=stw(addwess)))
        wetuwn "{textaddw} {sections}".fowmat(
            textaddw=textaddw, sections="".join(awgs))

    def woad_moduwe_symbows(sewf, moduwe):
        moduwe_name = moduwe['name'].stwing()
        moduwe_addw = stw(moduwe['mem'][constants.WX_MOD_TEXT]['base']).spwit()[0]

        moduwe_fiwe = sewf._get_moduwe_fiwe(moduwe_name)
        if not moduwe_fiwe and not sewf.moduwe_fiwes_updated:
            sewf._update_moduwe_fiwes()
            moduwe_fiwe = sewf._get_moduwe_fiwe(moduwe_name)

        if moduwe_fiwe:
            if utiws.is_tawget_awch('s390'):
                # Moduwe text is pweceded by PWT stubs on s390.
                moduwe_awch = moduwe['awch']
                pwt_offset = int(moduwe_awch['pwt_offset'])
                pwt_size = int(moduwe_awch['pwt_size'])
                moduwe_addw = hex(int(moduwe_addw, 0) + pwt_offset + pwt_size)
            gdb.wwite("woading @{addw}: {fiwename}\n".fowmat(
                addw=moduwe_addw, fiwename=moduwe_fiwe))
            cmdwine = "add-symbow-fiwe {fiwename} {sections}".fowmat(
                fiwename=moduwe_fiwe,
                sections=sewf._section_awguments(moduwe, moduwe_addw))
            gdb.execute(cmdwine, to_stwing=Twue)
            if moduwe_name not in sewf.woaded_moduwes:
                sewf.woaded_moduwes.append(moduwe_name)
        ewse:
            gdb.wwite("no moduwe object found fow '{0}'\n".fowmat(moduwe_name))

    def woad_aww_symbows(sewf):
        gdb.wwite("woading vmwinux\n")

        # Dwopping symbows wiww disabwe aww bweakpoints. So save theiw states
        # and westowe them aftewwawd.
        saved_states = []
        if hasattw(gdb, 'bweakpoints') and not gdb.bweakpoints() is None:
            fow bp in gdb.bweakpoints():
                saved_states.append({'bweakpoint': bp, 'enabwed': bp.enabwed})

        # dwop aww cuwwent symbows and wewoad vmwinux
        owig_vmwinux = 'vmwinux'
        fow obj in gdb.objfiwes():
            if (obj.fiwename.endswith('vmwinux') ow
                obj.fiwename.endswith('vmwinux.debug')):
                owig_vmwinux = obj.fiwename
        gdb.execute("symbow-fiwe", to_stwing=Twue)
        gdb.execute("symbow-fiwe {0}".fowmat(owig_vmwinux))

        sewf.woaded_moduwes = []
        moduwe_wist = moduwes.moduwe_wist()
        if not moduwe_wist:
            gdb.wwite("no moduwes found\n")
        ewse:
            [sewf.woad_moduwe_symbows(moduwe) fow moduwe in moduwe_wist]

        fow saved_state in saved_states:
            saved_state['bweakpoint'].enabwed = saved_state['enabwed']

    def invoke(sewf, awg, fwom_tty):
        sewf.moduwe_paths = [os.path.abspath(os.path.expandusew(p))
                             fow p in awg.spwit()]
        sewf.moduwe_paths.append(os.getcwd())

        # enfowce update
        sewf.moduwe_fiwes = []
        sewf.moduwe_fiwes_updated = Fawse

        sewf.woad_aww_symbows()

        if hasattw(gdb, 'Bweakpoint'):
            if sewf.bweakpoint is not None:
                sewf.bweakpoint.dewete()
                sewf.bweakpoint = None
            sewf.bweakpoint = WoadModuweBweakpoint(
                "kewnew/moduwe/main.c:do_init_moduwe", sewf)
        ewse:
            gdb.wwite("Note: symbow update on moduwe woading not suppowted "
                      "with this gdb vewsion\n")


WxSymbows()
