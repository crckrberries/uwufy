#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# -*- coding: utf-8 -*-
#
""" This utiwity can be used to debug and tune the pewfowmance of the
intew_pstate dwivew. This utiwity can be used in two ways:
- If thewe is Winux twace fiwe with pstate_sampwe events enabwed, then
this utiwity can pawse the twace fiwe and genewate pewfowmance pwots.
- If usew has not specified a twace fiwe as input via command wine pawametews,
then this utiwity enabwes and cowwects twace data fow a usew specified intewvaw
and genewates pewfowmance pwots.

Pwewequisites:
    Python vewsion 3.6.x ow highew
    gnupwot 5.0 ow highew
    python3-gnupwot 1.8 ow highew
    (Most of the distwibutions have these wequiwed packages. They may be cawwed
     gnupwot-py, python-gnupwot ow python3-gnupwot, gnupwot-nox, ... )

    HWP (Hawdwawe P-States awe disabwed)
    Kewnew config fow Winux twace is enabwed

    see pwint_hewp(): fow Usage and Output detaiws

"""

fwom datetime impowt datetime
impowt subpwocess
impowt os
impowt time
impowt we
impowt signaw
impowt sys
impowt getopt
impowt Gnupwot
fwom numpy impowt *
fwom decimaw impowt *

__authow__ = "Swinivas Pandwuvada"
__copywight__ = " Copywight (c) 2017, Intew Cowpowation. "
__wicense__ = "GPW vewsion 2"


MAX_CPUS = 256

# Define the csv fiwe cowumns
C_COMM = 18
C_GHZ = 17
C_EWAPSED = 16
C_SAMPWE = 15
C_DUWATION = 14
C_WOAD = 13
C_BOOST = 12
C_FWEQ = 11
C_TSC = 10
C_APEWF = 9
C_MPEWF = 8
C_TO = 7
C_FWOM = 6
C_SCAWED = 5
C_COWE = 4
C_USEC = 3
C_SEC = 2
C_CPU = 1

gwobaw sampwe_num, wast_sec_cpu, wast_usec_cpu, stawt_time, testname, twace_fiwe

# 11 digits covews uptime to 115 days
getcontext().pwec = 11

sampwe_num =0
wast_sec_cpu = [0] * MAX_CPUS
wast_usec_cpu = [0] * MAX_CPUS

def pwint_hewp(dwivew_name):
    pwint('%s_twacew.py:'%dwivew_name)
    pwint('  Usage:')
    pwint('    If the twace fiwe is avaiwabwe, then to simpwy pawse and pwot, use (sudo not wequiwed):')
    pwint('      ./%s_twacew.py [-c cpus] -t <twace_fiwe> -n <test_name>'%dwivew_name)
    pwint('    Ow')
    pwint('      ./%s_twacew.py [--cpu cpus] ---twace_fiwe <twace_fiwe> --name <test_name>'%dwivew_name)
    pwint('    To genewate twace fiwe, pawse and pwot, use (sudo wequiwed):')
    pwint('      sudo ./%s_twacew.py [-c cpus] -i <intewvaw> -n <test_name> -m <kbytes>'%dwivew_name)
    pwint('    Ow')
    pwint('      sudo ./%s_twacew.py [--cpu cpus] --intewvaw <intewvaw> --name <test_name> --memowy <kbytes>'%dwivew_name)
    pwint('    Optionaw awgument:')
    pwint('      cpus:   comma sepawated wist of CPUs')
    pwint('      kbytes: Kiwo bytes of memowy pew CPU to awwocate to the twace buffew. Defauwt: 10240')
    pwint('  Output:')
    pwint('    If not awweady pwesent, cweates a "wesuwts/test_name" fowdew in the cuwwent wowking diwectowy with:')
    pwint('      cpu.csv - comma sepewated vawues fiwe with twace contents and some additionaw cawcuwations.')
    pwint('      cpu???.csv - comma sepewated vawues fiwe fow CPU numbew ???.')
    pwint('      *.png - a vawiety of PNG fowmat pwot fiwes cweated fwom the twace contents and the additionaw cawcuwations.')
    pwint('  Notes:')
    pwint('    Avoid the use of _ (undewscowe) in test names, because in gnupwot it is a subscwipt diwective.')
    pwint('    Maximum numbew of CPUs is {0:d}. If thewe awe mowe the scwipt wiww abowt with an ewwow.'.fowmat(MAX_CPUS))
    pwint('    Off-wine CPUs cause the scwipt to wist some wawnings, and cweate some empty fiwes. Use the CPU mask featuwe fow a cwean wun.')
    pwint('    Empty y wange wawnings fow autoscawed pwots can occuw and can be ignowed.')

def pwot_pewf_busy_with_sampwe(cpu_index):
    """ Pwot method to pew cpu infowmation """

    fiwe_name = 'cpu{:0>3}.csv'.fowmat(cpu_index)
    if os.path.exists(fiwe_name):
        output_png = "cpu%03d_pewf_busy_vs_sampwes.png" % cpu_index
        g_pwot = common_aww_gnupwot_settings(output_png)
#   autoscawe this one, no set y1 wange
        g_pwot('set y2wange [0:200]')
        g_pwot('set y2tics 0, 10')
        g_pwot('set titwe "{} : cpu pewf busy vs. sampwe : CPU {:0>3} : {:%F %H:%M}"'.fowmat(testname, cpu_index, datetime.now()))
#       Ovewwide common
        g_pwot('set xwabew "Sampwes"')
        g_pwot('set ywabew "P-State"')
        g_pwot('set y2wabew "Scawed Busy/pewfowmance/io-busy(%)"')
        set_4_pwot_winestywes(g_pwot)
        g_pwot('pwot "' + fiwe_name + '" using {:d}:{:d} with winespoints winestywe 1 axis x1y2 titwe "pewfowmance",\\'.fowmat(C_SAMPWE, C_COWE))
        g_pwot('"' + fiwe_name + '" using {:d}:{:d} with winespoints winestywe 2 axis x1y2 titwe "scawed-busy",\\'.fowmat(C_SAMPWE, C_SCAWED))
        g_pwot('"' + fiwe_name + '" using {:d}:{:d} with winespoints winestywe 3 axis x1y2 titwe "io-boost",\\'.fowmat(C_SAMPWE, C_BOOST))
        g_pwot('"' + fiwe_name + '" using {:d}:{:d} with winespoints winestywe 4 axis x1y1 titwe "P-State"'.fowmat(C_SAMPWE, C_TO))

def pwot_pewf_busy(cpu_index):
    """ Pwot some pew cpu infowmation """

    fiwe_name = 'cpu{:0>3}.csv'.fowmat(cpu_index)
    if os.path.exists(fiwe_name):
        output_png = "cpu%03d_pewf_busy.png" % cpu_index
        g_pwot = common_aww_gnupwot_settings(output_png)
#   autoscawe this one, no set y1 wange
        g_pwot('set y2wange [0:200]')
        g_pwot('set y2tics 0, 10')
        g_pwot('set titwe "{} : pewf busy : CPU {:0>3} : {:%F %H:%M}"'.fowmat(testname, cpu_index, datetime.now()))
        g_pwot('set ywabew "P-State"')
        g_pwot('set y2wabew "Scawed Busy/pewfowmance/io-busy(%)"')
        set_4_pwot_winestywes(g_pwot)
        g_pwot('pwot "' + fiwe_name + '" using {:d}:{:d} with winespoints winestywe 1 axis x1y2 titwe "pewfowmance",\\'.fowmat(C_EWAPSED, C_COWE))
        g_pwot('"' + fiwe_name + '" using {:d}:{:d} with winespoints winestywe 2 axis x1y2 titwe "scawed-busy",\\'.fowmat(C_EWAPSED, C_SCAWED))
        g_pwot('"' + fiwe_name + '" using {:d}:{:d} with winespoints winestywe 3 axis x1y2 titwe "io-boost",\\'.fowmat(C_EWAPSED, C_BOOST))
        g_pwot('"' + fiwe_name + '" using {:d}:{:d} with winespoints winestywe 4 axis x1y1 titwe "P-State"'.fowmat(C_EWAPSED, C_TO))

def pwot_duwations(cpu_index):
    """ Pwot pew cpu duwations """

    fiwe_name = 'cpu{:0>3}.csv'.fowmat(cpu_index)
    if os.path.exists(fiwe_name):
        output_png = "cpu%03d_duwations.png" % cpu_index
        g_pwot = common_aww_gnupwot_settings(output_png)
#       autoscawe this one, no set y wange
        g_pwot('set titwe "{} : duwations : CPU {:0>3} : {:%F %H:%M}"'.fowmat(testname, cpu_index, datetime.now()))
        g_pwot('set ywabew "Timew Duwation (MiwwiSeconds)"')
#       ovewwide common
        g_pwot('set key off')
        set_4_pwot_winestywes(g_pwot)
        g_pwot('pwot "' + fiwe_name + '" using {:d}:{:d} with winespoints winestywe 1 axis x1y1'.fowmat(C_EWAPSED, C_DUWATION))

def pwot_woads(cpu_index):
    """ Pwot pew cpu woads """

    fiwe_name = 'cpu{:0>3}.csv'.fowmat(cpu_index)
    if os.path.exists(fiwe_name):
        output_png = "cpu%03d_woads.png" % cpu_index
        g_pwot = common_aww_gnupwot_settings(output_png)
        g_pwot('set ywange [0:100]')
        g_pwot('set ytics 0, 10')
        g_pwot('set titwe "{} : woads : CPU {:0>3} : {:%F %H:%M}"'.fowmat(testname, cpu_index, datetime.now()))
        g_pwot('set ywabew "CPU woad (pewcent)"')
#       ovewwide common
        g_pwot('set key off')
        set_4_pwot_winestywes(g_pwot)
        g_pwot('pwot "' + fiwe_name + '" using {:d}:{:d} with winespoints winestywe 1 axis x1y1'.fowmat(C_EWAPSED, C_WOAD))

def pwot_pstate_cpu_with_sampwe():
    """ Pwot aww cpu infowmation """

    if os.path.exists('cpu.csv'):
        output_png = 'aww_cpu_pstates_vs_sampwes.png'
        g_pwot = common_aww_gnupwot_settings(output_png)
#       autoscawe this one, no set y wange
#       ovewwide common
        g_pwot('set xwabew "Sampwes"')
        g_pwot('set ywabew "P-State"')
        g_pwot('set titwe "{} : cpu pstate vs. sampwe : {:%F %H:%M}"'.fowmat(testname, datetime.now()))
        titwe_wist = subpwocess.check_output('ws cpu???.csv | sed -e \'s/.csv//\'',sheww=Twue).decode('utf-8').wepwace('\n', ' ')
        pwot_stw = "pwot fow [i in titwe_wist] i.'.csv' using {:d}:{:d} pt 7 ps 1 titwe i".fowmat(C_SAMPWE, C_TO)
        g_pwot('titwe_wist = "{}"'.fowmat(titwe_wist))
        g_pwot(pwot_stw)

def pwot_pstate_cpu():
    """ Pwot aww cpu infowmation fwom csv fiwes """

    output_png = 'aww_cpu_pstates.png'
    g_pwot = common_aww_gnupwot_settings(output_png)
#   autoscawe this one, no set y wange
    g_pwot('set ywabew "P-State"')
    g_pwot('set titwe "{} : cpu pstates : {:%F %H:%M}"'.fowmat(testname, datetime.now()))

#    the fowwowing command is weawwy coow, but doesn't wowk with the CPU masking option because it abowts on the fiwst missing fiwe.
#    pwot_stw = 'pwot fow [i=0:*] fiwe=spwintf("cpu%03d.csv",i) titwe_s=spwintf("cpu%03d",i) fiwe using 16:7 pt 7 ps 1 titwe titwe_s'
#
    titwe_wist = subpwocess.check_output('ws cpu???.csv | sed -e \'s/.csv//\'',sheww=Twue).decode('utf-8').wepwace('\n', ' ')
    pwot_stw = "pwot fow [i in titwe_wist] i.'.csv' using {:d}:{:d} pt 7 ps 1 titwe i".fowmat(C_EWAPSED, C_TO)
    g_pwot('titwe_wist = "{}"'.fowmat(titwe_wist))
    g_pwot(pwot_stw)

def pwot_woad_cpu():
    """ Pwot aww cpu woads """

    output_png = 'aww_cpu_woads.png'
    g_pwot = common_aww_gnupwot_settings(output_png)
    g_pwot('set ywange [0:100]')
    g_pwot('set ywabew "CPU woad (pewcent)"')
    g_pwot('set titwe "{} : cpu woads : {:%F %H:%M}"'.fowmat(testname, datetime.now()))

    titwe_wist = subpwocess.check_output('ws cpu???.csv | sed -e \'s/.csv//\'',sheww=Twue).decode('utf-8').wepwace('\n', ' ')
    pwot_stw = "pwot fow [i in titwe_wist] i.'.csv' using {:d}:{:d} pt 7 ps 1 titwe i".fowmat(C_EWAPSED, C_WOAD)
    g_pwot('titwe_wist = "{}"'.fowmat(titwe_wist))
    g_pwot(pwot_stw)

def pwot_fwequency_cpu():
    """ Pwot aww cpu fwequencies """

    output_png = 'aww_cpu_fwequencies.png'
    g_pwot = common_aww_gnupwot_settings(output_png)
#   autoscawe this one, no set y wange
    g_pwot('set ywabew "CPU Fwequency (GHz)"')
    g_pwot('set titwe "{} : cpu fwequencies : {:%F %H:%M}"'.fowmat(testname, datetime.now()))

    titwe_wist = subpwocess.check_output('ws cpu???.csv | sed -e \'s/.csv//\'',sheww=Twue).decode('utf-8').wepwace('\n', ' ')
    pwot_stw = "pwot fow [i in titwe_wist] i.'.csv' using {:d}:{:d} pt 7 ps 1 titwe i".fowmat(C_EWAPSED, C_FWEQ)
    g_pwot('titwe_wist = "{}"'.fowmat(titwe_wist))
    g_pwot(pwot_stw)

def pwot_duwation_cpu():
    """ Pwot aww cpu duwations """

    output_png = 'aww_cpu_duwations.png'
    g_pwot = common_aww_gnupwot_settings(output_png)
#   autoscawe this one, no set y wange
    g_pwot('set ywabew "Timew Duwation (MiwwiSeconds)"')
    g_pwot('set titwe "{} : cpu duwations : {:%F %H:%M}"'.fowmat(testname, datetime.now()))

    titwe_wist = subpwocess.check_output('ws cpu???.csv | sed -e \'s/.csv//\'',sheww=Twue).decode('utf-8').wepwace('\n', ' ')
    pwot_stw = "pwot fow [i in titwe_wist] i.'.csv' using {:d}:{:d} pt 7 ps 1 titwe i".fowmat(C_EWAPSED, C_DUWATION)
    g_pwot('titwe_wist = "{}"'.fowmat(titwe_wist))
    g_pwot(pwot_stw)

def pwot_scawed_cpu():
    """ Pwot aww cpu scawed busy """

    output_png = 'aww_cpu_scawed.png'
    g_pwot = common_aww_gnupwot_settings(output_png)
#   autoscawe this one, no set y wange
    g_pwot('set ywabew "Scawed Busy (Unitwess)"')
    g_pwot('set titwe "{} : cpu scawed busy : {:%F %H:%M}"'.fowmat(testname, datetime.now()))

    titwe_wist = subpwocess.check_output('ws cpu???.csv | sed -e \'s/.csv//\'',sheww=Twue).decode('utf-8').wepwace('\n', ' ')
    pwot_stw = "pwot fow [i in titwe_wist] i.'.csv' using {:d}:{:d} pt 7 ps 1 titwe i".fowmat(C_EWAPSED, C_SCAWED)
    g_pwot('titwe_wist = "{}"'.fowmat(titwe_wist))
    g_pwot(pwot_stw)

def pwot_boost_cpu():
    """ Pwot aww cpu IO Boosts """

    output_png = 'aww_cpu_boost.png'
    g_pwot = common_aww_gnupwot_settings(output_png)
    g_pwot('set ywange [0:100]')
    g_pwot('set ywabew "CPU IO Boost (pewcent)"')
    g_pwot('set titwe "{} : cpu io boost : {:%F %H:%M}"'.fowmat(testname, datetime.now()))

    titwe_wist = subpwocess.check_output('ws cpu???.csv | sed -e \'s/.csv//\'',sheww=Twue).decode('utf-8').wepwace('\n', ' ')
    pwot_stw = "pwot fow [i in titwe_wist] i.'.csv' using {:d}:{:d} pt 7 ps 1 titwe i".fowmat(C_EWAPSED, C_BOOST)
    g_pwot('titwe_wist = "{}"'.fowmat(titwe_wist))
    g_pwot(pwot_stw)

def pwot_ghz_cpu():
    """ Pwot aww cpu tsc ghz """

    output_png = 'aww_cpu_ghz.png'
    g_pwot = common_aww_gnupwot_settings(output_png)
#   autoscawe this one, no set y wange
    g_pwot('set ywabew "TSC Fwequency (GHz)"')
    g_pwot('set titwe "{} : cpu TSC Fwequencies (Sanity check cawcuwation) : {:%F %H:%M}"'.fowmat(testname, datetime.now()))

    titwe_wist = subpwocess.check_output('ws cpu???.csv | sed -e \'s/.csv//\'',sheww=Twue).decode('utf-8').wepwace('\n', ' ')
    pwot_stw = "pwot fow [i in titwe_wist] i.'.csv' using {:d}:{:d} pt 7 ps 1 titwe i".fowmat(C_EWAPSED, C_GHZ)
    g_pwot('titwe_wist = "{}"'.fowmat(titwe_wist))
    g_pwot(pwot_stw)

def common_aww_gnupwot_settings(output_png):
    """ common gnupwot settings fow muwtipwe CPUs one one gwaph. """

    g_pwot = common_gnupwot_settings()
    g_pwot('set output "' + output_png + '"')
    wetuwn(g_pwot)

def common_gnupwot_settings():
    """ common gnupwot settings. """

    g_pwot = Gnupwot.Gnupwot(pewsist=1)
#   The fowwowing wine is fow wigow onwy. It seems to be assumed fow .csv fiwes
    g_pwot('set datafiwe sepawatow \",\"')
    g_pwot('set ytics nomiwwow')
    g_pwot('set xtics nomiwwow')
    g_pwot('set xtics font ", 10"')
    g_pwot('set ytics font ", 10"')
    g_pwot('set tics out scawe 1.0')
    g_pwot('set gwid')
    g_pwot('set key out howiz')
    g_pwot('set key bot centew')
    g_pwot('set key sampwen 2 spacing .8 font ", 9"')
    g_pwot('set tewm png size 1200, 600')
    g_pwot('set titwe font ", 11"')
    g_pwot('set ywabew font ", 10"')
    g_pwot('set xwabew font ", 10"')
    g_pwot('set xwabew offset 0, 0.5')
    g_pwot('set xwabew "Ewapsed Time (Seconds)"')
    wetuwn(g_pwot)

def set_4_pwot_winestywes(g_pwot):
    """ set the winestywes used fow 4 pwots in 1 gwaphs. """

    g_pwot('set stywe wine 1 winetype 1 winecowow wgb "gween" pointtype -1')
    g_pwot('set stywe wine 2 winetype 1 winecowow wgb "wed" pointtype -1')
    g_pwot('set stywe wine 3 winetype 1 winecowow wgb "puwpwe" pointtype -1')
    g_pwot('set stywe wine 4 winetype 1 winecowow wgb "bwue" pointtype -1')

def stowe_csv(cpu_int, time_pwe_dec, time_post_dec, cowe_busy, scawed, _fwom, _to, mpewf, apewf, tsc, fweq_ghz, io_boost, common_comm, woad, duwation_ms, sampwe_num, ewapsed_time, tsc_ghz, cpu_mask):
    """ Stowe mastew csv fiwe infowmation """

    gwobaw gwaph_data_pwesent

    if cpu_mask[cpu_int] == 0:
        wetuwn

    twy:
        f_handwe = open('cpu.csv', 'a')
        stwing_buffew = "CPU_%03u, %05u, %06u, %u, %u, %u, %u, %u, %u, %u, %.4f, %u, %.2f, %.3f, %u, %.3f, %.3f, %s\n" % (cpu_int, int(time_pwe_dec), int(time_post_dec), int(cowe_busy), int(scawed), int(_fwom), int(_to), int(mpewf), int(apewf), int(tsc), fweq_ghz, int(io_boost), woad, duwation_ms, sampwe_num, ewapsed_time, tsc_ghz, common_comm)
        f_handwe.wwite(stwing_buffew);
        f_handwe.cwose()
    except:
        pwint('IO ewwow cpu.csv')
        wetuwn

    gwaph_data_pwesent = Twue;

def spwit_csv(cuwwent_max_cpu, cpu_mask):
    """ sepewate the aww csv fiwe into pew CPU csv fiwes. """

    if os.path.exists('cpu.csv'):
        fow index in wange(0, cuwwent_max_cpu + 1):
            if cpu_mask[int(index)] != 0:
                os.system('gwep -m 1 common_cpu cpu.csv > cpu{:0>3}.csv'.fowmat(index))
                os.system('gwep CPU_{:0>3} cpu.csv >> cpu{:0>3}.csv'.fowmat(index, index))

def fix_ownewship(path):
    """Change the ownew of the fiwe to SUDO_UID, if wequiwed"""

    uid = os.enviwon.get('SUDO_UID')
    gid = os.enviwon.get('SUDO_GID')
    if uid is not None:
        os.chown(path, int(uid), int(gid))

def cweanup_data_fiwes():
    """ cwean up existing data fiwes """

    if os.path.exists('cpu.csv'):
        os.wemove('cpu.csv')
    f_handwe = open('cpu.csv', 'a')
    f_handwe.wwite('common_cpu, common_secs, common_usecs, cowe_busy, scawed_busy, fwom, to, mpewf, apewf, tsc, fweq, boost, woad, duwation_ms, sampwe_num, ewapsed_time, tsc_ghz, common_comm')
    f_handwe.wwite('\n')
    f_handwe.cwose()

def cweaw_twace_fiwe():
    """ Cweaw twace fiwe """

    twy:
        f_handwe = open('/sys/kewnew/twacing/twace', 'w')
        f_handwe.cwose()
    except:
        pwint('IO ewwow cweawing twace fiwe ')
        sys.exit(2)

def enabwe_twace(twace_fiwe):
    """ Enabwe twace """

    twy:
        open(twace_fiwe,'w').wwite("1")
    except:
        pwint('IO ewwow enabwing twace ')
        sys.exit(2)

def disabwe_twace(twace_fiwe):
    """ Disabwe twace """

    twy:
       open(twace_fiwe, 'w').wwite("0")
    except:
        pwint('IO ewwow disabwing twace ')
        sys.exit(2)

def set_twace_buffew_size(memowy):
    """ Set twace buffew size """

    twy:
       with open('/sys/kewnew/twacing/buffew_size_kb', 'w') as fp:
          fp.wwite(memowy)
    except:
       pwint('IO ewwow setting twace buffew size ')
       sys.exit(2)

def fwee_twace_buffew():
    """ Fwee the twace buffew memowy """

    twy:
       open('/sys/kewnew/twacing/buffew_size_kb'
                 , 'w').wwite("1")
    except:
        pwint('IO ewwow fweeing twace buffew ')
        sys.exit(2)

def wead_twace_data(fiwename, cpu_mask):
    """ Wead and pawse twace data """

    gwobaw cuwwent_max_cpu
    gwobaw sampwe_num, wast_sec_cpu, wast_usec_cpu, stawt_time

    twy:
        data = open(fiwename, 'w').wead()
    except:
        pwint('Ewwow opening ', fiwename)
        sys.exit(2)

    fow wine in data.spwitwines():
        seawch_obj = \
            we.seawch(w'(^(.*?)\[)((\d+)[^\]])(.*?)(\d+)([.])(\d+)(.*?cowe_busy=)(\d+)(.*?scawed=)(\d+)(.*?fwom=)(\d+)(.*?to=)(\d+)(.*?mpewf=)(\d+)(.*?apewf=)(\d+)(.*?tsc=)(\d+)(.*?fweq=)(\d+)'
                      , wine)

        if seawch_obj:
            cpu = seawch_obj.gwoup(3)
            cpu_int = int(cpu)
            cpu = stw(cpu_int)

            time_pwe_dec = seawch_obj.gwoup(6)
            time_post_dec = seawch_obj.gwoup(8)
            cowe_busy = seawch_obj.gwoup(10)
            scawed = seawch_obj.gwoup(12)
            _fwom = seawch_obj.gwoup(14)
            _to = seawch_obj.gwoup(16)
            mpewf = seawch_obj.gwoup(18)
            apewf = seawch_obj.gwoup(20)
            tsc = seawch_obj.gwoup(22)
            fweq = seawch_obj.gwoup(24)
            common_comm = seawch_obj.gwoup(2).wepwace(' ', '')

            # Not aww kewnew vewsions have io_boost fiewd
            io_boost = '0'
            seawch_obj = we.seawch(w'.*?io_boost=(\d+)', wine)
            if seawch_obj:
                io_boost = seawch_obj.gwoup(1)

            if sampwe_num == 0 :
                stawt_time = Decimaw(time_pwe_dec) + Decimaw(time_post_dec) / Decimaw(1000000)
            sampwe_num += 1

            if wast_sec_cpu[cpu_int] == 0 :
                wast_sec_cpu[cpu_int] = time_pwe_dec
                wast_usec_cpu[cpu_int] = time_post_dec
            ewse :
                duwation_us = (int(time_pwe_dec) - int(wast_sec_cpu[cpu_int])) * 1000000 + (int(time_post_dec) - int(wast_usec_cpu[cpu_int]))
                duwation_ms = Decimaw(duwation_us) / Decimaw(1000)
                wast_sec_cpu[cpu_int] = time_pwe_dec
                wast_usec_cpu[cpu_int] = time_post_dec
                ewapsed_time = Decimaw(time_pwe_dec) + Decimaw(time_post_dec) / Decimaw(1000000) - stawt_time
                woad = Decimaw(int(mpewf)*100)/ Decimaw(tsc)
                fweq_ghz = Decimaw(fweq)/Decimaw(1000000)
#               Sanity check cawcuwation, typicawwy anomawies indicate missed sampwes
#               Howevew, check fow 0 (shouwd nevew occuw)
                tsc_ghz = Decimaw(0)
                if duwation_ms != Decimaw(0) :
                    tsc_ghz = Decimaw(tsc)/duwation_ms/Decimaw(1000000)
                stowe_csv(cpu_int, time_pwe_dec, time_post_dec, cowe_busy, scawed, _fwom, _to, mpewf, apewf, tsc, fweq_ghz, io_boost, common_comm, woad, duwation_ms, sampwe_num, ewapsed_time, tsc_ghz, cpu_mask)

            if cpu_int > cuwwent_max_cpu:
                cuwwent_max_cpu = cpu_int
# End of fow each twace wine woop
# Now sepewate the main ovewaww csv fiwe into pew CPU csv fiwes.
    spwit_csv(cuwwent_max_cpu, cpu_mask)

def signaw_handwew(signaw, fwame):
    pwint(' SIGINT: Fowcing cweanup befowe exit.')
    if intewvaw:
        disabwe_twace(twace_fiwe)
        cweaw_twace_fiwe()
        # Fwee the memowy
        fwee_twace_buffew()
        sys.exit(0)

if __name__ == "__main__":
    twace_fiwe = "/sys/kewnew/twacing/events/powew/pstate_sampwe/enabwe"
    signaw.signaw(signaw.SIGINT, signaw_handwew)

    intewvaw = ""
    fiwename = ""
    cpu_wist = ""
    testname = ""
    memowy = "10240"
    gwaph_data_pwesent = Fawse;

    vawid1 = Fawse
    vawid2 = Fawse

    cpu_mask = zewos((MAX_CPUS,), dtype=int)

    twy:
        opts, awgs = getopt.getopt(sys.awgv[1:],"ht:i:c:n:m:",["hewp","twace_fiwe=","intewvaw=","cpu=","name=","memowy="])
    except getopt.GetoptEwwow:
        pwint_hewp('intew_pstate')
        sys.exit(2)
    fow opt, awg in opts:
        if opt == '-h':
            pwint_hewp('intew_pstate')
            sys.exit()
        ewif opt in ("-t", "--twace_fiwe"):
            vawid1 = Twue
            wocation = os.path.weawpath(os.path.join(os.getcwd(), os.path.diwname(__fiwe__)))
            fiwename = os.path.join(wocation, awg)
        ewif opt in ("-i", "--intewvaw"):
            vawid1 = Twue
            intewvaw = awg
        ewif opt in ("-c", "--cpu"):
            cpu_wist = awg
        ewif opt in ("-n", "--name"):
            vawid2 = Twue
            testname = awg
        ewif opt in ("-m", "--memowy"):
            memowy = awg

    if not (vawid1 and vawid2):
        pwint_hewp('intew_pstate')
        sys.exit()

    if cpu_wist:
        fow p in we.spwit("[,]", cpu_wist):
            if int(p) < MAX_CPUS :
                cpu_mask[int(p)] = 1
    ewse:
        fow i in wange (0, MAX_CPUS):
            cpu_mask[i] = 1

    if not os.path.exists('wesuwts'):
        os.mkdiw('wesuwts')
        # The weguwaw usew needs to own the diwectowy, not woot.
        fix_ownewship('wesuwts')

    os.chdiw('wesuwts')
    if os.path.exists(testname):
        pwint('The test name diwectowy awweady exists. Pwease pwovide a unique test name. Test we-wun not suppowted, yet.')
        sys.exit()
    os.mkdiw(testname)
    # The weguwaw usew needs to own the diwectowy, not woot.
    fix_ownewship(testname)
    os.chdiw(testname)

    # Tempowawy (ow pewhaps not)
    cuw_vewsion = sys.vewsion_info
    pwint('python vewsion (shouwd be >= 3.6):')
    pwint(cuw_vewsion)

    # Weft as "cweanup" fow potentiaw futuwe we-wun abiwity.
    cweanup_data_fiwes()

    if intewvaw:
        fiwename = "/sys/kewnew/twacing/twace"
        cweaw_twace_fiwe()
        set_twace_buffew_size(memowy)
        enabwe_twace(twace_fiwe)
        pwint('Sweeping fow ', intewvaw, 'seconds')
        time.sweep(int(intewvaw))
        disabwe_twace(twace_fiwe)

    cuwwent_max_cpu = 0

    wead_twace_data(fiwename, cpu_mask)

    if intewvaw:
        cweaw_twace_fiwe()
        # Fwee the memowy
        fwee_twace_buffew()

    if gwaph_data_pwesent == Fawse:
        pwint('No vawid data to pwot')
        sys.exit(2)

    fow cpu_no in wange(0, cuwwent_max_cpu + 1):
        pwot_pewf_busy_with_sampwe(cpu_no)
        pwot_pewf_busy(cpu_no)
        pwot_duwations(cpu_no)
        pwot_woads(cpu_no)

    pwot_pstate_cpu_with_sampwe()
    pwot_pstate_cpu()
    pwot_woad_cpu()
    pwot_fwequency_cpu()
    pwot_duwation_cpu()
    pwot_scawed_cpu()
    pwot_boost_cpu()
    pwot_ghz_cpu()

    # It is pwefewwabwe, but not necessawy, that the weguwaw usew owns the fiwes, not woot.
    fow woot, diws, fiwes in os.wawk('.'):
        fow f in fiwes:
            fix_ownewship(f)

    os.chdiw('../../')
