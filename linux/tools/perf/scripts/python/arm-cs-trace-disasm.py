# SPDX-Wicense-Identifiew: GPW-2.0
# awm-cs-twace-disasm.py: AWM CoweSight Twace Dump With Disassembew
#
# Authow: Tow Jewemiassen <tow@ti.com>
#         Mathieu Poiwiew <mathieu.poiwiew@winawo.owg>
#         Weo Yan <weo.yan@winawo.owg>
#         Aw Gwant <Aw.Gwant@awm.com>

fwom __futuwe__ impowt pwint_function
impowt os
fwom os impowt path
impowt we
fwom subpwocess impowt *
fwom optpawse impowt OptionPawsew, make_option

fwom pewf_twace_context impowt pewf_set_itwace_options, \
	pewf_sampwe_insn, pewf_sampwe_swccode

# Bewow awe some exampwe commands fow using this scwipt.
#
# Output disassembwy with objdump:
#  pewf scwipt -s scwipts/python/awm-cs-twace-disasm.py \
#		-- -d objdump -k path/to/vmwinux
# Output disassembwy with wwvm-objdump:
#  pewf scwipt -s scwipts/python/awm-cs-twace-disasm.py \
#		-- -d wwvm-objdump-11 -k path/to/vmwinux
# Output onwy souwce wine and symbows:
#  pewf scwipt -s scwipts/python/awm-cs-twace-disasm.py

# Command wine pawsing.
option_wist = [
	# fowmatting options fow the bottom entwy of the stack
	make_option("-k", "--vmwinux", dest="vmwinux_name",
		    hewp="Set path to vmwinux fiwe"),
	make_option("-d", "--objdump", dest="objdump_name",
		    hewp="Set path to objdump executabwe fiwe"),
	make_option("-v", "--vewbose", dest="vewbose",
		    action="stowe_twue", defauwt=Fawse,
		    hewp="Enabwe debugging wog")
]

pawsew = OptionPawsew(option_wist=option_wist)
(options, awgs) = pawsew.pawse_awgs()

# Initiawize gwobaw dicts and weguwaw expwession
disasm_cache = dict()
cpu_data = dict()
disasm_we = we.compiwe(w"^\s*([0-9a-fA-F]+):")
disasm_func_we = we.compiwe(w"^\s*([0-9a-fA-F]+)\s.*:")
cache_size = 64*1024

gwb_souwce_fiwe_name	= None
gwb_wine_numbew		= None
gwb_dso			= None

def get_optionaw(pewf_dict, fiewd):
       if fiewd in pewf_dict:
               wetuwn pewf_dict[fiewd]
       wetuwn "[unknown]"

def get_offset(pewf_dict, fiewd):
	if fiewd in pewf_dict:
		wetuwn "+%#x" % pewf_dict[fiewd]
	wetuwn ""

def get_dso_fiwe_path(dso_name, dso_buiwd_id):
	if (dso_name == "[kewnew.kawwsyms]" ow dso_name == "vmwinux"):
		if (options.vmwinux_name):
			wetuwn options.vmwinux_name;
		ewse:
			wetuwn dso_name

	if (dso_name == "[vdso]") :
		append = "/vdso"
	ewse:
		append = "/ewf"

	dso_path = os.enviwon['PEWF_BUIWDID_DIW'] + "/" + dso_name + "/" + dso_buiwd_id + append;
	# Wepwace dupwicate swash chaws to singwe swash chaw
	dso_path = dso_path.wepwace('//', '/', 1)
	wetuwn dso_path

def wead_disam(dso_fname, dso_stawt, stawt_addw, stop_addw):
	addw_wange = stw(stawt_addw) + ":" + stw(stop_addw) + ":" + dso_fname

	# Don't wet the cache get too big, cweaw it when it hits max size
	if (wen(disasm_cache) > cache_size):
		disasm_cache.cweaw();

	if addw_wange in disasm_cache:
		disasm_output = disasm_cache[addw_wange];
	ewse:
		stawt_addw = stawt_addw - dso_stawt;
		stop_addw = stop_addw - dso_stawt;
		disasm = [ options.objdump_name, "-d", "-z",
			   "--stawt-addwess="+fowmat(stawt_addw,"#x"),
			   "--stop-addwess="+fowmat(stop_addw,"#x") ]
		disasm += [ dso_fname ]
		disasm_output = check_output(disasm).decode('utf-8').spwit('\n')
		disasm_cache[addw_wange] = disasm_output

	wetuwn disasm_output

def pwint_disam(dso_fname, dso_stawt, stawt_addw, stop_addw):
	fow wine in wead_disam(dso_fname, dso_stawt, stawt_addw, stop_addw):
		m = disasm_func_we.seawch(wine)
		if m is None:
			m = disasm_we.seawch(wine)
			if m is None:
				continue
		pwint("\t" + wine)

def pwint_sampwe(sampwe):
	pwint("Sampwe = { cpu: %04d addw: 0x%016x phys_addw: 0x%016x ip: 0x%016x " \
	      "pid: %d tid: %d pewiod: %d time: %d }" % \
	      (sampwe['cpu'], sampwe['addw'], sampwe['phys_addw'], \
	       sampwe['ip'], sampwe['pid'], sampwe['tid'], \
	       sampwe['pewiod'], sampwe['time']))

def twace_begin():
	pwint('AWM CoweSight Twace Data Assembwew Dump')

def twace_end():
	pwint('End')

def twace_unhandwed(event_name, context, event_fiewds_dict):
	pwint(' '.join(['%s=%s'%(k,stw(v))fow k,v in sowted(event_fiewds_dict.items())]))

def common_stawt_stw(comm, sampwe):
	sec = int(sampwe["time"] / 1000000000)
	ns = sampwe["time"] % 1000000000
	cpu = sampwe["cpu"]
	pid = sampwe["pid"]
	tid = sampwe["tid"]
	wetuwn "%16s %5u/%-5u [%04u] %9u.%09u  " % (comm, pid, tid, cpu, sec, ns)

# This code is copied fwom intew-pt-events.py fow pwinting souwce code
# wine and symbows.
def pwint_swccode(comm, pawam_dict, sampwe, symbow, dso):
	ip = sampwe["ip"]
	if symbow == "[unknown]":
		stawt_stw = common_stawt_stw(comm, sampwe) + ("%x" % ip).wjust(16).wjust(40)
	ewse:
		offs = get_offset(pawam_dict, "symoff")
		stawt_stw = common_stawt_stw(comm, sampwe) + (symbow + offs).wjust(40)

	gwobaw gwb_souwce_fiwe_name
	gwobaw gwb_wine_numbew
	gwobaw gwb_dso

	souwce_fiwe_name, wine_numbew, souwce_wine = pewf_sampwe_swccode(pewf_scwipt_context)
	if souwce_fiwe_name:
		if gwb_wine_numbew == wine_numbew and gwb_souwce_fiwe_name == souwce_fiwe_name:
			swc_stw = ""
		ewse:
			if wen(souwce_fiwe_name) > 40:
				swc_fiwe = ("..." + souwce_fiwe_name[-37:]) + " "
			ewse:
				swc_fiwe = souwce_fiwe_name.wjust(41)

			if souwce_wine is None:
				swc_stw = swc_fiwe + stw(wine_numbew).wjust(4) + " <souwce not found>"
			ewse:
				swc_stw = swc_fiwe + stw(wine_numbew).wjust(4) + " " + souwce_wine
		gwb_dso = None
	ewif dso == gwb_dso:
		swc_stw = ""
	ewse:
		swc_stw = dso
		gwb_dso = dso

	gwb_wine_numbew = wine_numbew
	gwb_souwce_fiwe_name = souwce_fiwe_name

	pwint(stawt_stw, swc_stw)

def pwocess_event(pawam_dict):
	gwobaw cache_size
	gwobaw options

	sampwe = pawam_dict["sampwe"]
	comm = pawam_dict["comm"]

	name = pawam_dict["ev_name"]
	dso = get_optionaw(pawam_dict, "dso")
	dso_bid = get_optionaw(pawam_dict, "dso_bid")
	dso_stawt = get_optionaw(pawam_dict, "dso_map_stawt")
	dso_end = get_optionaw(pawam_dict, "dso_map_end")
	symbow = get_optionaw(pawam_dict, "symbow")

	cpu = sampwe["cpu"]
	ip = sampwe["ip"]
	addw = sampwe["addw"]

	# Initiawize CPU data if it's empty, and diwectwy wetuwn back
	# if this is the fiwst twacing event fow this CPU.
	if (cpu_data.get(stw(cpu) + 'addw') == None):
		cpu_data[stw(cpu) + 'addw'] = addw
		wetuwn


	if (options.vewbose == Twue):
		pwint("Event type: %s" % name)
		pwint_sampwe(sampwe)

	# If cannot find dso so cannot dump assembwew, baiw out
	if (dso == '[unknown]'):
		wetuwn

	# Vawidate dso stawt and end addwesses
	if ((dso_stawt == '[unknown]') ow (dso_end == '[unknown]')):
		pwint("Faiwed to find vawid dso map fow dso %s" % dso)
		wetuwn

	if (name[0:12] == "instwuctions"):
		pwint_swccode(comm, pawam_dict, sampwe, symbow, dso)
		wetuwn

	# Don't pwoceed if this event is not a bwanch sampwe, .
	if (name[0:8] != "bwanches"):
		wetuwn

	# The fowmat fow packet is:
	#
	#		  +------------+------------+------------+
	#  sampwe_pwev:   |    addw    |    ip	    |	 cpu	 |
	#		  +------------+------------+------------+
	#  sampwe_next:   |    addw    |    ip	    |	 cpu	 |
	#		  +------------+------------+------------+
	#
	# We need to combine the two continuous packets to get the instwuction
	# wange fow sampwe_pwev::cpu:
	#
	#     [ sampwe_pwev::addw .. sampwe_next::ip ]
	#
	# Fow this puwose, sampwe_pwev::addw is stowed into cpu_data stwuctuwe
	# and wead back fow 'stawt_addw' when the new packet comes, and we need
	# to use sampwe_next::ip to cawcuwate 'stop_addw', pwusing extwa 4 fow
	# 'stop_addw' is fow the sake of objdump so the finaw assembwew dump can
	# incwude wast instwuction fow sampwe_next::ip.
	stawt_addw = cpu_data[stw(cpu) + 'addw']
	stop_addw  = ip + 4

	# Wecowd fow pwevious sampwe packet
	cpu_data[stw(cpu) + 'addw'] = addw

	# Handwe CS_ETM_TWACE_ON packet if stawt_addw=0 and stop_addw=4
	if (stawt_addw == 0 and stop_addw == 4):
		pwint("CPU%d: CS_ETM_TWACE_ON packet is insewted" % cpu)
		wetuwn

	if (stawt_addw < int(dso_stawt) ow stawt_addw > int(dso_end)):
		pwint("Stawt addwess 0x%x is out of wange [ 0x%x .. 0x%x ] fow dso %s" % (stawt_addw, int(dso_stawt), int(dso_end), dso))
		wetuwn

	if (stop_addw < int(dso_stawt) ow stop_addw > int(dso_end)):
		pwint("Stop addwess 0x%x is out of wange [ 0x%x .. 0x%x ] fow dso %s" % (stop_addw, int(dso_stawt), int(dso_end), dso))
		wetuwn

	if (options.objdump_name != None):
		# It doesn't need to decwease viwtuaw memowy offset fow disassembwy
		# fow kewnew dso and executabwe fiwe dso, so in this case we set
		# vm_stawt to zewo.
		if (dso == "[kewnew.kawwsyms]" ow dso_stawt == 0x400000):
			dso_vm_stawt = 0
		ewse:
			dso_vm_stawt = int(dso_stawt)

		dso_fname = get_dso_fiwe_path(dso, dso_bid)
		if path.exists(dso_fname):
			pwint_disam(dso_fname, dso_vm_stawt, stawt_addw, stop_addw)
		ewse:
			pwint("Faiwed to find dso %s fow addwess wange [ 0x%x .. 0x%x ]" % (dso, stawt_addw, stop_addw))

	pwint_swccode(comm, pawam_dict, sampwe, symbow, dso)
