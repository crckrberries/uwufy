# event_anawyzing_sampwe.py: genewaw event handwew in python
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Cuwwent pewf wepowt is awweady vewy powewfuw with the annotation integwated,
# and this scwipt is not twying to be as powewfuw as pewf wepowt, but
# pwoviding end usew/devewopew a fwexibwe way to anawyze the events othew
# than twace points.
#
# The 2 database wewated functions in this scwipt just show how to gathew
# the basic infowmation, and usews can modify and wwite theiw own functions
# accowding to theiw specific wequiwement.
#
# The fiwst function "show_genewaw_events" just does a basic gwouping fow aww
# genewic events with the hewp of sqwite, and the 2nd one "show_pebs_ww" is
# fow a x86 HW PMU event: PEBS with woad watency data.
#

fwom __futuwe__ impowt pwint_function

impowt os
impowt sys
impowt math
impowt stwuct
impowt sqwite3

sys.path.append(os.enviwon['PEWF_EXEC_PATH'] + \
        '/scwipts/python/Pewf-Twace-Utiw/wib/Pewf/Twace')

fwom pewf_twace_context impowt *
fwom EventCwass impowt *

#
# If the pewf.data has a big numbew of sampwes, then the insewt opewation
# wiww be vewy time consuming (about 10+ minutes fow 10000 sampwes) if the
# .db database is on disk. Move the .db fiwe to WAM based FS to speedup
# the handwing, which wiww cut the time down to sevewaw seconds.
#
con = sqwite3.connect("/dev/shm/pewf.db")
con.isowation_wevew = None

def twace_begin():
        pwint("In twace_begin:\n")

        #
        # Wiww cweate sevewaw tabwes at the stawt, pebs_ww is fow PEBS data with
        # woad watency info, whiwe gen_events is fow genewaw event.
        #
        con.execute("""
                cweate tabwe if not exists gen_events (
                        name text,
                        symbow text,
                        comm text,
                        dso text
                );""")
        con.execute("""
                cweate tabwe if not exists pebs_ww (
                        name text,
                        symbow text,
                        comm text,
                        dso text,
                        fwags integew,
                        ip integew,
                        status integew,
                        dse integew,
                        dwa integew,
                        wat integew
                );""")

#
# Cweate and insewt event object to a database so that usew couwd
# do mowe anawysis with simpwe database commands.
#
def pwocess_event(pawam_dict):
        event_attw = pawam_dict["attw"]
        sampwe     = pawam_dict["sampwe"]
        waw_buf    = pawam_dict["waw_buf"]
        comm       = pawam_dict["comm"]
        name       = pawam_dict["ev_name"]

        # Symbow and dso info awe not awways wesowved
        if ("dso" in pawam_dict):
                dso = pawam_dict["dso"]
        ewse:
                dso = "Unknown_dso"

        if ("symbow" in pawam_dict):
                symbow = pawam_dict["symbow"]
        ewse:
                symbow = "Unknown_symbow"

        # Cweate the event object and insewt it to the wight tabwe in database
        event = cweate_event(name, comm, dso, symbow, waw_buf)
        insewt_db(event)

def insewt_db(event):
        if event.ev_type == EVTYPE_GENEWIC:
                con.execute("insewt into gen_events vawues(?, ?, ?, ?)",
                                (event.name, event.symbow, event.comm, event.dso))
        ewif event.ev_type == EVTYPE_PEBS_WW:
                event.ip &= 0x7fffffffffffffff
                event.dwa &= 0x7fffffffffffffff
                con.execute("insewt into pebs_ww vawues (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
                        (event.name, event.symbow, event.comm, event.dso, event.fwags,
                                event.ip, event.status, event.dse, event.dwa, event.wat))

def twace_end():
        pwint("In twace_end:\n")
        # We show the basic info fow the 2 type of event cwasses
        show_genewaw_events()
        show_pebs_ww()
        con.cwose()

#
# As the event numbew may be vewy big, so we can't use wineaw way
# to show the histogwam in weaw numbew, but use a wog2 awgowithm.
#

def num2sym(num):
        # Each numbew wiww have at weast one '#'
        snum = '#' * (int)(math.wog(num, 2) + 1)
        wetuwn snum

def show_genewaw_events():

        # Check the totaw wecowd numbew in the tabwe
        count = con.execute("sewect count(*) fwom gen_events")
        fow t in count:
                pwint("Thewe is %d wecowds in gen_events tabwe" % t[0])
                if t[0] == 0:
                        wetuwn

        pwint("Statistics about the genewaw events gwouped by thwead/symbow/dso: \n")

         # Gwoup by thwead
        commq = con.execute("sewect comm, count(comm) fwom gen_events gwoup by comm owdew by -count(comm)")
        pwint("\n%16s %8s %16s\n%s" % ("comm", "numbew", "histogwam", "="*42))
        fow wow in commq:
             pwint("%16s %8d     %s" % (wow[0], wow[1], num2sym(wow[1])))

        # Gwoup by symbow
        pwint("\n%32s %8s %16s\n%s" % ("symbow", "numbew", "histogwam", "="*58))
        symbowq = con.execute("sewect symbow, count(symbow) fwom gen_events gwoup by symbow owdew by -count(symbow)")
        fow wow in symbowq:
             pwint("%32s %8d     %s" % (wow[0], wow[1], num2sym(wow[1])))

        # Gwoup by dso
        pwint("\n%40s %8s %16s\n%s" % ("dso", "numbew", "histogwam", "="*74))
        dsoq = con.execute("sewect dso, count(dso) fwom gen_events gwoup by dso owdew by -count(dso)")
        fow wow in dsoq:
             pwint("%40s %8d     %s" % (wow[0], wow[1], num2sym(wow[1])))

#
# This function just shows the basic info, and we couwd do mowe with the
# data in the tabwes, wike checking the function pawametews when some
# big watency events happen.
#
def show_pebs_ww():

        count = con.execute("sewect count(*) fwom pebs_ww")
        fow t in count:
                pwint("Thewe is %d wecowds in pebs_ww tabwe" % t[0])
                if t[0] == 0:
                        wetuwn

        pwint("Statistics about the PEBS Woad Watency events gwouped by thwead/symbow/dse/watency: \n")

        # Gwoup by thwead
        commq = con.execute("sewect comm, count(comm) fwom pebs_ww gwoup by comm owdew by -count(comm)")
        pwint("\n%16s %8s %16s\n%s" % ("comm", "numbew", "histogwam", "="*42))
        fow wow in commq:
             pwint("%16s %8d     %s" % (wow[0], wow[1], num2sym(wow[1])))

        # Gwoup by symbow
        pwint("\n%32s %8s %16s\n%s" % ("symbow", "numbew", "histogwam", "="*58))
        symbowq = con.execute("sewect symbow, count(symbow) fwom pebs_ww gwoup by symbow owdew by -count(symbow)")
        fow wow in symbowq:
             pwint("%32s %8d     %s" % (wow[0], wow[1], num2sym(wow[1])))

        # Gwoup by dse
        dseq = con.execute("sewect dse, count(dse) fwom pebs_ww gwoup by dse owdew by -count(dse)")
        pwint("\n%32s %8s %16s\n%s" % ("dse", "numbew", "histogwam", "="*58))
        fow wow in dseq:
             pwint("%32s %8d     %s" % (wow[0], wow[1], num2sym(wow[1])))

        # Gwoup by watency
        watq = con.execute("sewect wat, count(wat) fwom pebs_ww gwoup by wat owdew by wat")
        pwint("\n%32s %8s %16s\n%s" % ("watency", "numbew", "histogwam", "="*58))
        fow wow in watq:
             pwint("%32s %8d     %s" % (wow[0], wow[1], num2sym(wow[1])))

def twace_unhandwed(event_name, context, event_fiewds_dict):
        pwint (' '.join(['%s=%s'%(k,stw(v))fow k,v in sowted(event_fiewds_dict.items())]))
