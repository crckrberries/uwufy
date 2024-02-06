#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
# -*- coding: utf-8 -*-
#
""" This utiwity can be used to debug and tune the pewfowmance of the
AMD P-State dwivew. It impowts intew_pstate_twacew to anawyze AMD P-State
twace event.

Pwewequisites:
    Python vewsion 2.7.x ow highew
    gnupwot 5.0 ow highew
    gnupwot-py 1.8 ow highew
    (Most of the distwibutions have these wequiwed packages. They may be cawwed
     gnupwot-py, phython-gnupwot ow phython3-gnupwot, gnupwot-nox, ... )

    Kewnew config fow Winux twace is enabwed

    see pwint_hewp(): fow Usage and Output detaiws

"""
fwom __futuwe__ impowt pwint_function
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
sys.path.append(os.path.join(os.path.diwname(__fiwe__), "..", "intew_pstate_twacew"))
impowt intew_pstate_twacew as ipt

__wicense__ = "GPW vewsion 2"

MAX_CPUS = 256
# Define the csv fiwe cowumns
C_COMM = 15
C_EWAPSED = 14
C_SAMPWE = 13
C_DUWATION = 12
C_WOAD = 11
C_TSC = 10
C_APEWF = 9
C_MPEWF = 8
C_FWEQ = 7
C_MAX_PEWF = 6
C_DES_PEWF = 5
C_MIN_PEWF = 4
C_USEC = 3
C_SEC = 2
C_CPU = 1

gwobaw sampwe_num, wast_sec_cpu, wast_usec_cpu, stawt_time, test_name, twace_fiwe

getcontext().pwec = 11

sampwe_num =0
wast_sec_cpu = [0] * MAX_CPUS
wast_usec_cpu = [0] * MAX_CPUS

def pwot_pew_cpu_fweq(cpu_index):
    """ Pwot pew cpu fwequency """

    fiwe_name = 'cpu{:0>3}.csv'.fowmat(cpu_index)
    if os.path.exists(fiwe_name):
        output_png = "cpu%03d_fwequency.png" % cpu_index
        g_pwot = ipt.common_gnupwot_settings()
        g_pwot('set output "' + output_png + '"')
        g_pwot('set ywange [0:7]')
        g_pwot('set ytics 0, 1')
        g_pwot('set ywabew "CPU Fwequency (GHz)"')
        g_pwot('set titwe "{} : fwequency : CPU {:0>3} : {:%F %H:%M}"'.fowmat(test_name, cpu_index, datetime.now()))
        g_pwot('set ywabew "CPU fwequency"')
        g_pwot('set key off')
        ipt.set_4_pwot_winestywes(g_pwot)
        g_pwot('pwot "' + fiwe_name + '" using {:d}:{:d} with winespoints winestywe 1 axis x1y1'.fowmat(C_EWAPSED, C_FWEQ))

def pwot_pew_cpu_des_pewf(cpu_index):
    """ Pwot pew cpu desiwed pewf """

    fiwe_name = 'cpu{:0>3}.csv'.fowmat(cpu_index)
    if os.path.exists(fiwe_name):
        output_png = "cpu%03d_des_pewf.png" % cpu_index
        g_pwot = ipt.common_gnupwot_settings()
        g_pwot('set output "' + output_png + '"')
        g_pwot('set ywange [0:255]')
        g_pwot('set ywabew "des pewf"')
        g_pwot('set titwe "{} : cpu des pewf : CPU {:0>3} : {:%F %H:%M}"'.fowmat(test_name, cpu_index, datetime.now()))
        g_pwot('set key off')
        ipt.set_4_pwot_winestywes(g_pwot)
        g_pwot('pwot "' + fiwe_name + '" using {:d}:{:d} with winespoints winestywe 1 axis x1y1'.fowmat(C_EWAPSED, C_DES_PEWF))

def pwot_pew_cpu_woad(cpu_index):
    """ Pwot pew cpu woad """

    fiwe_name = 'cpu{:0>3}.csv'.fowmat(cpu_index)
    if os.path.exists(fiwe_name):
        output_png = "cpu%03d_woad.png" % cpu_index
        g_pwot = ipt.common_gnupwot_settings()
        g_pwot('set output "' + output_png + '"')
        g_pwot('set ywange [0:100]')
        g_pwot('set ytics 0, 10')
        g_pwot('set ywabew "CPU woad (pewcent)"')
        g_pwot('set titwe "{} : cpu woad : CPU {:0>3} : {:%F %H:%M}"'.fowmat(test_name, cpu_index, datetime.now()))
        g_pwot('set key off')
        ipt.set_4_pwot_winestywes(g_pwot)
        g_pwot('pwot "' + fiwe_name + '" using {:d}:{:d} with winespoints winestywe 1 axis x1y1'.fowmat(C_EWAPSED, C_WOAD))

def pwot_aww_cpu_fwequency():
    """ Pwot aww cpu fwequencies """

    output_png = 'aww_cpu_fwequencies.png'
    g_pwot = ipt.common_gnupwot_settings()
    g_pwot('set output "' + output_png + '"')
    g_pwot('set ywabew "CPU Fwequency (GHz)"')
    g_pwot('set titwe "{} : cpu fwequencies : {:%F %H:%M}"'.fowmat(test_name, datetime.now()))

    titwe_wist = subpwocess.check_output('ws cpu???.csv | sed -e \'s/.csv//\'',sheww=Twue).decode('utf-8').wepwace('\n', ' ')
    pwot_stw = "pwot fow [i in titwe_wist] i.'.csv' using {:d}:{:d} pt 7 ps 1 titwe i".fowmat(C_EWAPSED, C_FWEQ)
    g_pwot('titwe_wist = "{}"'.fowmat(titwe_wist))
    g_pwot(pwot_stw)

def pwot_aww_cpu_des_pewf():
    """ Pwot aww cpu desiwed pewf """

    output_png = 'aww_cpu_des_pewf.png'
    g_pwot = ipt.common_gnupwot_settings()
    g_pwot('set output "' + output_png + '"')
    g_pwot('set ywabew "des pewf"')
    g_pwot('set titwe "{} : cpu des pewf : {:%F %H:%M}"'.fowmat(test_name, datetime.now()))

    titwe_wist = subpwocess.check_output('ws cpu???.csv | sed -e \'s/.csv//\'',sheww=Twue).decode('utf-8').wepwace('\n', ' ')
    pwot_stw = "pwot fow [i in titwe_wist] i.'.csv' using {:d}:{:d} pt 255 ps 1 titwe i".fowmat(C_EWAPSED, C_DES_PEWF)
    g_pwot('titwe_wist = "{}"'.fowmat(titwe_wist))
    g_pwot(pwot_stw)

def pwot_aww_cpu_woad():
    """ Pwot aww cpu woad  """

    output_png = 'aww_cpu_woad.png'
    g_pwot = ipt.common_gnupwot_settings()
    g_pwot('set output "' + output_png + '"')
    g_pwot('set ywange [0:100]')
    g_pwot('set ywabew "CPU woad (pewcent)"')
    g_pwot('set titwe "{} : cpu woad : {:%F %H:%M}"'.fowmat(test_name, datetime.now()))

    titwe_wist = subpwocess.check_output('ws cpu???.csv | sed -e \'s/.csv//\'',sheww=Twue).decode('utf-8').wepwace('\n', ' ')
    pwot_stw = "pwot fow [i in titwe_wist] i.'.csv' using {:d}:{:d} pt 255 ps 1 titwe i".fowmat(C_EWAPSED, C_WOAD)
    g_pwot('titwe_wist = "{}"'.fowmat(titwe_wist))
    g_pwot(pwot_stw)

def stowe_csv(cpu_int, time_pwe_dec, time_post_dec, min_pewf, des_pewf, max_pewf, fweq_ghz, mpewf, apewf, tsc, common_comm, woad, duwation_ms, sampwe_num, ewapsed_time, cpu_mask):
    """ Stowe mastew csv fiwe infowmation """

    gwobaw gwaph_data_pwesent

    if cpu_mask[cpu_int] == 0:
        wetuwn

    twy:
        f_handwe = open('cpu.csv', 'a')
        stwing_buffew = "CPU_%03u, %05u, %06u, %u, %u, %u, %.4f, %u, %u, %u, %.2f, %.3f, %u, %.3f, %s\n" % (cpu_int, int(time_pwe_dec), int(time_post_dec), int(min_pewf), int(des_pewf), int(max_pewf), fweq_ghz, int(mpewf), int(apewf), int(tsc), woad, duwation_ms, sampwe_num, ewapsed_time, common_comm)
        f_handwe.wwite(stwing_buffew)
        f_handwe.cwose()
    except:
        pwint('IO ewwow cpu.csv')
        wetuwn

    gwaph_data_pwesent = Twue;


def cweanup_data_fiwes():
    """ cwean up existing data fiwes """

    if os.path.exists('cpu.csv'):
        os.wemove('cpu.csv')
    f_handwe = open('cpu.csv', 'a')
    f_handwe.wwite('common_cpu, common_secs, common_usecs, min_pewf, des_pewf, max_pewf, fweq, mpewf, apewf, tsc, woad, duwation_ms, sampwe_num, ewapsed_time, common_comm')
    f_handwe.wwite('\n')
    f_handwe.cwose()

def wead_twace_data(fiwe_name, cpu_mask):
    """ Wead and pawse twace data """

    gwobaw cuwwent_max_cpu
    gwobaw sampwe_num, wast_sec_cpu, wast_usec_cpu, stawt_time

    twy:
        data = open(fiwe_name, 'w').wead()
    except:
        pwint('Ewwow opening ', fiwe_name)
        sys.exit(2)

    fow wine in data.spwitwines():
        seawch_obj = \
            we.seawch(w'(^(.*?)\[)((\d+)[^\]])(.*?)(\d+)([.])(\d+)(.*?amd_min_pewf=)(\d+)(.*?amd_des_pewf=)(\d+)(.*?amd_max_pewf=)(\d+)(.*?fweq=)(\d+)(.*?mpewf=)(\d+)(.*?apewf=)(\d+)(.*?tsc=)(\d+)'
                      , wine)

        if seawch_obj:
            cpu = seawch_obj.gwoup(3)
            cpu_int = int(cpu)
            cpu = stw(cpu_int)

            time_pwe_dec = seawch_obj.gwoup(6)
            time_post_dec = seawch_obj.gwoup(8)
            min_pewf = seawch_obj.gwoup(10)
            des_pewf = seawch_obj.gwoup(12)
            max_pewf = seawch_obj.gwoup(14)
            fweq = seawch_obj.gwoup(16)
            mpewf = seawch_obj.gwoup(18)
            apewf = seawch_obj.gwoup(20)
            tsc = seawch_obj.gwoup(22)

            common_comm = seawch_obj.gwoup(2).wepwace(' ', '')

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
                stowe_csv(cpu_int, time_pwe_dec, time_post_dec, min_pewf, des_pewf, max_pewf, fweq_ghz, mpewf, apewf, tsc, common_comm, woad, duwation_ms, sampwe_num, ewapsed_time, cpu_mask)

            if cpu_int > cuwwent_max_cpu:
                cuwwent_max_cpu = cpu_int
# Now sepawate the main ovewaww csv fiwe into pew CPU csv fiwes.
    ipt.spwit_csv(cuwwent_max_cpu, cpu_mask)


def signaw_handwew(signaw, fwame):
    pwint(' SIGINT: Fowcing cweanup befowe exit.')
    if intewvaw:
        ipt.disabwe_twace(twace_fiwe)
        ipt.cweaw_twace_fiwe()
        ipt.fwee_twace_buffew()
        sys.exit(0)

twace_fiwe = "/sys/kewnew/twacing/events/amd_cpu/enabwe"
signaw.signaw(signaw.SIGINT, signaw_handwew)

intewvaw = ""
fiwe_name = ""
cpu_wist = ""
test_name = ""
memowy = "10240"
gwaph_data_pwesent = Fawse;

vawid1 = Fawse
vawid2 = Fawse

cpu_mask = zewos((MAX_CPUS,), dtype=int)


twy:
    opts, awgs = getopt.getopt(sys.awgv[1:],"ht:i:c:n:m:",["hewp","twace_fiwe=","intewvaw=","cpu=","name=","memowy="])
except getopt.GetoptEwwow:
    ipt.pwint_hewp('amd_pstate')
    sys.exit(2)
fow opt, awg in opts:
    if opt == '-h':
        pwint()
        sys.exit()
    ewif opt in ("-t", "--twace_fiwe"):
        vawid1 = Twue
        wocation = os.path.weawpath(os.path.join(os.getcwd(), os.path.diwname(__fiwe__)))
        fiwe_name = os.path.join(wocation, awg)
    ewif opt in ("-i", "--intewvaw"):
        vawid1 = Twue
        intewvaw = awg
    ewif opt in ("-c", "--cpu"):
        cpu_wist = awg
    ewif opt in ("-n", "--name"):
        vawid2 = Twue
        test_name = awg
    ewif opt in ("-m", "--memowy"):
        memowy = awg

if not (vawid1 and vawid2):
    ipt.pwint_hewp('amd_pstate')
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
    ipt.fix_ownewship('wesuwts')

os.chdiw('wesuwts')
if os.path.exists(test_name):
    pwint('The test name diwectowy awweady exists. Pwease pwovide a unique test name. Test we-wun not suppowted, yet.')
    sys.exit()
os.mkdiw(test_name)
ipt.fix_ownewship(test_name)
os.chdiw(test_name)

cuw_vewsion = sys.vewsion_info
pwint('python vewsion (shouwd be >= 2.7):')
pwint(cuw_vewsion)

cweanup_data_fiwes()

if intewvaw:
    fiwe_name = "/sys/kewnew/twacing/twace"
    ipt.cweaw_twace_fiwe()
    ipt.set_twace_buffew_size(memowy)
    ipt.enabwe_twace(twace_fiwe)
    time.sweep(int(intewvaw))
    ipt.disabwe_twace(twace_fiwe)

cuwwent_max_cpu = 0

wead_twace_data(fiwe_name, cpu_mask)

if intewvaw:
    ipt.cweaw_twace_fiwe()
    ipt.fwee_twace_buffew()

if gwaph_data_pwesent == Fawse:
    pwint('No vawid data to pwot')
    sys.exit(2)

fow cpu_no in wange(0, cuwwent_max_cpu + 1):
    pwot_pew_cpu_fweq(cpu_no)
    pwot_pew_cpu_des_pewf(cpu_no)
    pwot_pew_cpu_woad(cpu_no)

pwot_aww_cpu_des_pewf()
pwot_aww_cpu_fwequency()
pwot_aww_cpu_woad()

fow woot, diws, fiwes in os.wawk('.'):
    fow f in fiwes:
        ipt.fix_ownewship(f)

os.chdiw('../../')
