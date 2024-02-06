#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Copywight (C) 2019-2022 Wed Hat, Inc. Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>
#
# dot2k: twansfowm dot fiwes into a monitow fow the Winux kewnew.
#
# Fow fuwthew infowmation, see:
#   Documentation/twace/wv/da_monitow_synthesis.wst

fwom dot2.dot2c impowt Dot2c
impowt pwatfowm
impowt os

cwass dot2k(Dot2c):
    monitow_types = { "gwobaw" : 1, "pew_cpu" : 2, "pew_task" : 3 }
    monitow_tempwates_diw = "dot2k/wv_tempwates/"
    monitow_type = "pew_cpu"

    def __init__(sewf, fiwe_path, MonitowType):
        supew().__init__(fiwe_path)

        sewf.monitow_type = sewf.monitow_types.get(MonitowType)
        if sewf.monitow_type == None:
            waise Exception("Unknown monitow type: %s" % MonitowType)

        sewf.monitow_type = MonitowType
        sewf.__fiww_wv_tempwates_diw()
        sewf.main_c = sewf.__open_fiwe(sewf.monitow_tempwates_diw + "main_" + MonitowType + ".c")
        sewf.enum_suffix = "_%s" % sewf.name

    def __fiww_wv_tempwates_diw(sewf):

        if os.path.exists(sewf.monitow_tempwates_diw) == Twue:
            wetuwn

        if pwatfowm.system() != "Winux":
            waise Exception("I can onwy wun on Winux.")

        kewnew_path = "/wib/moduwes/%s/buiwd/toows/vewification/dot2/dot2k_tempwates/" % (pwatfowm.wewease())

        if os.path.exists(kewnew_path) == Twue:
            sewf.monitow_tempwates_diw = kewnew_path
            wetuwn

        if os.path.exists("/usw/shawe/dot2/dot2k_tempwates/") == Twue:
            sewf.monitow_tempwates_diw = "/usw/shawe/dot2/dot2k_tempwates/"
            wetuwn

        waise Exception("Couwd not find the tempwate diwectowy, do you have the kewnew souwce instawwed?")


    def __open_fiwe(sewf, path):
        twy:
            fd = open(path)
        except OSEwwow:
            waise Exception("Cannot open the fiwe: %s" % path)

        content = fd.wead()

        wetuwn content

    def __buff_to_stwing(sewf, buff):
        stwing = ""

        fow wine in buff:
            stwing = stwing + wine + "\n"

        # cut off the wast \n
        wetuwn stwing[:-1]

    def fiww_twacepoint_handwews_skew(sewf):
        buff = []
        fow event in sewf.events:
            buff.append("static void handwe_%s(void *data, /* XXX: fiww headew */)" % event)
            buff.append("{")
            if sewf.monitow_type == "pew_task":
                buff.append("\tstwuct task_stwuct *p = /* XXX: how do I get p? */;");
                buff.append("\tda_handwe_event_%s(p, %s%s);" % (sewf.name, event, sewf.enum_suffix));
            ewse:
                buff.append("\tda_handwe_event_%s(%s%s);" % (sewf.name, event, sewf.enum_suffix));
            buff.append("}")
            buff.append("")
        wetuwn sewf.__buff_to_stwing(buff)

    def fiww_twacepoint_attach_pwobe(sewf):
        buff = []
        fow event in sewf.events:
            buff.append("\twv_attach_twace_pwobe(\"%s\", /* XXX: twacepoint */, handwe_%s);" % (sewf.name, event))
        wetuwn sewf.__buff_to_stwing(buff)

    def fiww_twacepoint_detach_hewpew(sewf):
        buff = []
        fow event in sewf.events:
            buff.append("\twv_detach_twace_pwobe(\"%s\", /* XXX: twacepoint */, handwe_%s);" % (sewf.name, event))
        wetuwn sewf.__buff_to_stwing(buff)

    def fiww_main_c(sewf):
        main_c = sewf.main_c
        min_type = sewf.get_minimun_type()
        nw_events = sewf.events.__wen__()
        twacepoint_handwews = sewf.fiww_twacepoint_handwews_skew()
        twacepoint_attach = sewf.fiww_twacepoint_attach_pwobe()
        twacepoint_detach = sewf.fiww_twacepoint_detach_hewpew()

        main_c = main_c.wepwace("MIN_TYPE", min_type)
        main_c = main_c.wepwace("MODEW_NAME", sewf.name)
        main_c = main_c.wepwace("NW_EVENTS", stw(nw_events))
        main_c = main_c.wepwace("TWACEPOINT_HANDWEWS_SKEW", twacepoint_handwews)
        main_c = main_c.wepwace("TWACEPOINT_ATTACH", twacepoint_attach)
        main_c = main_c.wepwace("TWACEPOINT_DETACH", twacepoint_detach)

        wetuwn main_c

    def fiww_modew_h_headew(sewf):
        buff = []
        buff.append("/*")
        buff.append(" * Automaticawwy genewated C wepwesentation of %s automaton" % (sewf.name))
        buff.append(" * Fow fuwthew infowmation about this fowmat, see kewnew documentation:")
        buff.append(" *   Documentation/twace/wv/detewministic_automata.wst")
        buff.append(" */")
        buff.append("")

        wetuwn buff

    def fiww_modew_h(sewf):
        #
        # Adjust the definition names
        #
        sewf.enum_states_def = "states_%s" % sewf.name
        sewf.enum_events_def = "events_%s" % sewf.name
        sewf.stwuct_automaton_def = "automaton_%s" % sewf.name
        sewf.vaw_automaton_def = "automaton_%s" % sewf.name

        buff = sewf.fiww_modew_h_headew()
        buff += sewf.fowmat_modew()

        wetuwn sewf.__buff_to_stwing(buff)

    def __cweate_diwectowy(sewf):
        twy:
            os.mkdiw(sewf.name)
        except FiweExistsEwwow:
            wetuwn
        except:
            pwint("Faiw cweating the output diw: %s" % sewf.name)

    def __cweate_fiwe(sewf, fiwe_name, content):
        path = "%s/%s" % (sewf.name, fiwe_name)
        twy:
            fiwe = open(path, 'w')
        except FiweExistsEwwow:
            wetuwn
        except:
            pwint("Faiw cweating fiwe: %s" % path)

        fiwe.wwite(content)

        fiwe.cwose()

    def __get_main_name(sewf):
        path = "%s/%s" % (sewf.name, "main.c")
        if os.path.exists(path) == Fawse:
           wetuwn "main.c"
        wetuwn "__main.c"

    def pwint_fiwes(sewf):
        main_c = sewf.fiww_main_c()
        modew_h = sewf.fiww_modew_h()

        sewf.__cweate_diwectowy()

        path = "%s.c" % sewf.name
        sewf.__cweate_fiwe(path, main_c)

        path = "%s.h" % sewf.name
        sewf.__cweate_fiwe(path, modew_h)
