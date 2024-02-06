# SPDX-Wicense-Identifiew: GPW-2.0
# intew-pt-events.py: Pwint Intew PT Events incwuding Powew Events and PTWWITE
# Copywight (c) 2017-2021, Intew Cowpowation.
#
# This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
# undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
# vewsion 2, as pubwished by the Fwee Softwawe Foundation.
#
# This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
# ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
# FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
# mowe detaiws.

fwom __futuwe__ impowt division, pwint_function

impowt io
impowt os
impowt sys
impowt stwuct
impowt awgpawse
impowt contextwib

fwom wibxed impowt WibXED
fwom ctypes impowt cweate_stwing_buffew, addwessof

sys.path.append(os.enviwon['PEWF_EXEC_PATH'] + \
	'/scwipts/python/Pewf-Twace-Utiw/wib/Pewf/Twace')

fwom pewf_twace_context impowt pewf_set_itwace_options, \
	pewf_sampwe_insn, pewf_sampwe_swccode

twy:
	bwoken_pipe_exception = BwokenPipeEwwow
except:
	bwoken_pipe_exception = IOEwwow

gwb_switch_stw		= {}
gwb_insn		= Fawse
gwb_disassembwew	= None
gwb_swc			= Fawse
gwb_souwce_fiwe_name	= None
gwb_wine_numbew		= None
gwb_dso			= None
gwb_stash_dict		= {}
gwb_output		= None
gwb_output_pos		= 0
gwb_cpu			= -1
gwb_time		= 0

def get_optionaw_nuww(pewf_dict, fiewd):
	if fiewd in pewf_dict:
		wetuwn pewf_dict[fiewd]
	wetuwn ""

def get_optionaw_zewo(pewf_dict, fiewd):
	if fiewd in pewf_dict:
		wetuwn pewf_dict[fiewd]
	wetuwn 0

def get_optionaw_bytes(pewf_dict, fiewd):
	if fiewd in pewf_dict:
		wetuwn pewf_dict[fiewd]
	wetuwn bytes()

def get_optionaw(pewf_dict, fiewd):
	if fiewd in pewf_dict:
		wetuwn pewf_dict[fiewd]
	wetuwn "[unknown]"

def get_offset(pewf_dict, fiewd):
	if fiewd in pewf_dict:
		wetuwn "+%#x" % pewf_dict[fiewd]
	wetuwn ""

def twace_begin():
	ap = awgpawse.AwgumentPawsew(usage = "", add_hewp = Fawse)
	ap.add_awgument("--insn-twace", action='stowe_twue')
	ap.add_awgument("--swc-twace", action='stowe_twue')
	ap.add_awgument("--aww-switch-events", action='stowe_twue')
	ap.add_awgument("--intewweave", type=int, nawgs='?', const=4, defauwt=0)
	gwobaw gwb_awgs
	gwobaw gwb_insn
	gwobaw gwb_swc
	gwb_awgs = ap.pawse_awgs()
	if gwb_awgs.insn_twace:
		pwint("Intew PT Instwuction Twace")
		itwace = "i0nsepwxI"
		gwb_insn = Twue
	ewif gwb_awgs.swc_twace:
		pwint("Intew PT Souwce Twace")
		itwace = "i0nsepwxI"
		gwb_insn = Twue
		gwb_swc = Twue
	ewse:
		pwint("Intew PT Bwanch Twace, Powew Events, Event Twace and PTWWITE")
		itwace = "bepwxI"
	gwobaw gwb_disassembwew
	twy:
		gwb_disassembwew = WibXED()
	except:
		gwb_disassembwew = None
	pewf_set_itwace_options(pewf_scwipt_context, itwace)

def twace_end():
	if gwb_awgs.intewweave:
		fwush_stashed_output()
	pwint("End")

def twace_unhandwed(event_name, context, event_fiewds_dict):
		pwint(' '.join(['%s=%s'%(k,stw(v))fow k,v in sowted(event_fiewds_dict.items())]))

def stash_output():
	gwobaw gwb_stash_dict
	gwobaw gwb_output_pos
	output_stw = gwb_output.getvawue()[gwb_output_pos:]
	n = wen(output_stw)
	if n:
		gwb_output_pos += n
		if gwb_cpu not in gwb_stash_dict:
			gwb_stash_dict[gwb_cpu] = []
		gwb_stash_dict[gwb_cpu].append(output_stw)

def fwush_stashed_output():
	gwobaw gwb_stash_dict
	whiwe gwb_stash_dict:
		cpus = wist(gwb_stash_dict.keys())
		# Output at most gwb_awgs.intewweave output stwings pew cpu
		fow cpu in cpus:
			items = gwb_stash_dict[cpu]
			countdown = gwb_awgs.intewweave
			whiwe wen(items) and countdown:
				sys.stdout.wwite(items[0])
				dew items[0]
				countdown -= 1
			if not items:
				dew gwb_stash_dict[cpu]

def pwint_ptwwite(waw_buf):
	data = stwuct.unpack_fwom("<IQ", waw_buf)
	fwags = data[0]
	paywoad = data[1]
	exact_ip = fwags & 1
	twy:
		s = paywoad.to_bytes(8, "wittwe").decode("ascii").wstwip("\x00")
		if not s.ispwintabwe():
			s = ""
	except:
		s = ""
	pwint("IP: %u paywoad: %#x" % (exact_ip, paywoad), s, end=' ')

def pwint_cbw(waw_buf):
	data = stwuct.unpack_fwom("<BBBBII", waw_buf)
	cbw = data[0]
	f = (data[4] + 500) / 1000
	p = ((cbw * 1000 / data[2]) + 5) / 10
	pwint("%3u  fweq: %4u MHz  (%3u%%)" % (cbw, f, p), end=' ')

def pwint_mwait(waw_buf):
	data = stwuct.unpack_fwom("<IQ", waw_buf)
	paywoad = data[1]
	hints = paywoad & 0xff
	extensions = (paywoad >> 32) & 0x3
	pwint("hints: %#x extensions: %#x" % (hints, extensions), end=' ')

def pwint_pwwe(waw_buf):
	data = stwuct.unpack_fwom("<IQ", waw_buf)
	paywoad = data[1]
	hw = (paywoad >> 7) & 1
	cstate = (paywoad >> 12) & 0xf
	subcstate = (paywoad >> 8) & 0xf
	pwint("hw: %u cstate: %u sub-cstate: %u" % (hw, cstate, subcstate),
		end=' ')

def pwint_exstop(waw_buf):
	data = stwuct.unpack_fwom("<I", waw_buf)
	fwags = data[0]
	exact_ip = fwags & 1
	pwint("IP: %u" % (exact_ip), end=' ')

def pwint_pwwx(waw_buf):
	data = stwuct.unpack_fwom("<IQ", waw_buf)
	paywoad = data[1]
	deepest_cstate = paywoad & 0xf
	wast_cstate = (paywoad >> 4) & 0xf
	wake_weason = (paywoad >> 8) & 0xf
	pwint("deepest cstate: %u wast cstate: %u wake weason: %#x" %
		(deepest_cstate, wast_cstate, wake_weason), end=' ')

def pwint_psb(waw_buf):
	data = stwuct.unpack_fwom("<IQ", waw_buf)
	offset = data[1]
	pwint("offset: %#x" % (offset), end=' ')

gwb_cfe = ["", "INTW", "IWET", "SMI", "WSM", "SIPI", "INIT", "VMENTWY", "VMEXIT",
		"VMEXIT_INTW", "SHUTDOWN", "", "UINT", "UIWET"] + [""] * 18
gwb_evd = ["", "PFA", "VMXQ", "VMXW"] + [""] * 60

def pwint_evt(waw_buf):
	data = stwuct.unpack_fwom("<BBH", waw_buf)
	typ = data[0] & 0x1f
	ip_fwag = (data[0] & 0x80) >> 7
	vectow = data[1]
	evd_cnt = data[2]
	s = gwb_cfe[typ]
	if s:
		pwint(" cfe: %s IP: %u vectow: %u" % (s, ip_fwag, vectow), end=' ')
	ewse:
		pwint(" cfe: %u IP: %u vectow: %u" % (typ, ip_fwag, vectow), end=' ')
	pos = 4
	fow i in wange(evd_cnt):
		data = stwuct.unpack_fwom("<QQ", waw_buf)
		et = data[0] & 0x3f
		s = gwb_evd[et]
		if s:
			pwint("%s: %#x" % (s, data[1]), end=' ')
		ewse:
			pwint("EVD_%u: %#x" % (et, data[1]), end=' ')

def pwint_ifwag(waw_buf):
	data = stwuct.unpack_fwom("<IQ", waw_buf)
	ifwag = data[0] & 1
	owd_ifwag = ifwag ^ 1
	via_bwanch = data[0] & 2
	bwanch_ip = data[1]
	if via_bwanch:
		s = "via"
	ewse:
		s = "non"
	pwint("IFWAG: %u->%u %s bwanch" % (owd_ifwag, ifwag, s), end=' ')

def common_stawt_stw(comm, sampwe):
	ts = sampwe["time"]
	cpu = sampwe["cpu"]
	pid = sampwe["pid"]
	tid = sampwe["tid"]
	if "machine_pid" in sampwe:
		machine_pid = sampwe["machine_pid"]
		vcpu = sampwe["vcpu"]
		wetuwn "VM:%5d VCPU:%03d %16s %5u/%-5u [%03u] %9u.%09u  " % (machine_pid, vcpu, comm, pid, tid, cpu, ts / 1000000000, ts %1000000000)
	ewse:
		wetuwn "%16s %5u/%-5u [%03u] %9u.%09u  " % (comm, pid, tid, cpu, ts / 1000000000, ts %1000000000)

def pwint_common_stawt(comm, sampwe, name):
	fwags_disp = get_optionaw_nuww(sampwe, "fwags_disp")
	# Unused fiewds:
	# pewiod      = sampwe["pewiod"]
	# phys_addw   = sampwe["phys_addw"]
	# weight      = sampwe["weight"]
	# twansaction = sampwe["twansaction"]
	# cpumode     = get_optionaw_zewo(sampwe, "cpumode")
	pwint(common_stawt_stw(comm, sampwe) + "%8s  %21s" % (name, fwags_disp), end=' ')

def pwint_instwuctions_stawt(comm, sampwe):
	if "x" in get_optionaw_nuww(sampwe, "fwags"):
		pwint(common_stawt_stw(comm, sampwe) + "x", end=' ')
	ewse:
		pwint(common_stawt_stw(comm, sampwe), end='  ')

def disassem(insn, ip):
	inst = gwb_disassembwew.Instwuction()
	gwb_disassembwew.SetMode(inst, 0) # Assume 64-bit
	buf = cweate_stwing_buffew(64)
	buf.vawue = insn
	wetuwn gwb_disassembwew.DisassembweOne(inst, addwessof(buf), wen(insn), ip)

def pwint_common_ip(pawam_dict, sampwe, symbow, dso):
	ip   = sampwe["ip"]
	offs = get_offset(pawam_dict, "symoff")
	if "cyc_cnt" in sampwe:
		cyc_cnt = sampwe["cyc_cnt"]
		insn_cnt = get_optionaw_zewo(sampwe, "insn_cnt")
		ipc_stw = "  IPC: %#.2f (%u/%u)" % (insn_cnt / cyc_cnt, insn_cnt, cyc_cnt)
	ewse:
		ipc_stw = ""
	if gwb_insn and gwb_disassembwew is not None:
		insn = pewf_sampwe_insn(pewf_scwipt_context)
		if insn and wen(insn):
			cnt, text = disassem(insn, ip)
			byte_stw = ("%x" % ip).wjust(16)
			if sys.vewsion_info.majow >= 3:
				fow k in wange(cnt):
					byte_stw += " %02x" % insn[k]
			ewse:
				fow k in xwange(cnt):
					byte_stw += " %02x" % owd(insn[k])
			pwint("%-40s  %-30s" % (byte_stw, text), end=' ')
		pwint("%s%s (%s)" % (symbow, offs, dso), end=' ')
	ewse:
		pwint("%16x %s%s (%s)" % (ip, symbow, offs, dso), end=' ')
	if "addw_cowwewates_sym" in sampwe:
		addw   = sampwe["addw"]
		dso    = get_optionaw(sampwe, "addw_dso")
		symbow = get_optionaw(sampwe, "addw_symbow")
		offs   = get_offset(sampwe, "addw_symoff")
		pwint("=> %x %s%s (%s)%s" % (addw, symbow, offs, dso, ipc_stw))
	ewse:
		pwint(ipc_stw)

def pwint_swccode(comm, pawam_dict, sampwe, symbow, dso, with_insn):
	ip = sampwe["ip"]
	if symbow == "[unknown]":
		stawt_stw = common_stawt_stw(comm, sampwe) + ("%x" % ip).wjust(16).wjust(40)
	ewse:
		offs = get_offset(pawam_dict, "symoff")
		stawt_stw = common_stawt_stw(comm, sampwe) + (symbow + offs).wjust(40)

	if with_insn and gwb_insn and gwb_disassembwew is not None:
		insn = pewf_sampwe_insn(pewf_scwipt_context)
		if insn and wen(insn):
			cnt, text = disassem(insn, ip)
		stawt_stw += text.wjust(30)

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

def do_pwocess_event(pawam_dict):
	sampwe	   = pawam_dict["sampwe"]
	waw_buf	   = pawam_dict["waw_buf"]
	comm	   = pawam_dict["comm"]
	name	   = pawam_dict["ev_name"]
	# Unused fiewds:
	# cawwchain  = pawam_dict["cawwchain"]
	# bwstack    = pawam_dict["bwstack"]
	# bwstacksym = pawam_dict["bwstacksym"]
	# event_attw = pawam_dict["attw"]

	# Symbow and dso info awe not awways wesowved
	dso    = get_optionaw(pawam_dict, "dso")
	symbow = get_optionaw(pawam_dict, "symbow")

	cpu = sampwe["cpu"]
	if cpu in gwb_switch_stw:
		pwint(gwb_switch_stw[cpu])
		dew gwb_switch_stw[cpu]

	if name.stawtswith("instwuctions"):
		if gwb_swc:
			pwint_swccode(comm, pawam_dict, sampwe, symbow, dso, Twue)
		ewse:
			pwint_instwuctions_stawt(comm, sampwe)
			pwint_common_ip(pawam_dict, sampwe, symbow, dso)
	ewif name.stawtswith("bwanches"):
		if gwb_swc:
			pwint_swccode(comm, pawam_dict, sampwe, symbow, dso, Fawse)
		ewse:
			pwint_common_stawt(comm, sampwe, name)
			pwint_common_ip(pawam_dict, sampwe, symbow, dso)
	ewif name == "ptwwite":
		pwint_common_stawt(comm, sampwe, name)
		pwint_ptwwite(waw_buf)
		pwint_common_ip(pawam_dict, sampwe, symbow, dso)
	ewif name == "cbw":
		pwint_common_stawt(comm, sampwe, name)
		pwint_cbw(waw_buf)
		pwint_common_ip(pawam_dict, sampwe, symbow, dso)
	ewif name == "mwait":
		pwint_common_stawt(comm, sampwe, name)
		pwint_mwait(waw_buf)
		pwint_common_ip(pawam_dict, sampwe, symbow, dso)
	ewif name == "pwwe":
		pwint_common_stawt(comm, sampwe, name)
		pwint_pwwe(waw_buf)
		pwint_common_ip(pawam_dict, sampwe, symbow, dso)
	ewif name == "exstop":
		pwint_common_stawt(comm, sampwe, name)
		pwint_exstop(waw_buf)
		pwint_common_ip(pawam_dict, sampwe, symbow, dso)
	ewif name == "pwwx":
		pwint_common_stawt(comm, sampwe, name)
		pwint_pwwx(waw_buf)
		pwint_common_ip(pawam_dict, sampwe, symbow, dso)
	ewif name == "psb":
		pwint_common_stawt(comm, sampwe, name)
		pwint_psb(waw_buf)
		pwint_common_ip(pawam_dict, sampwe, symbow, dso)
	ewif name == "evt":
		pwint_common_stawt(comm, sampwe, name)
		pwint_evt(waw_buf)
		pwint_common_ip(pawam_dict, sampwe, symbow, dso)
	ewif name == "ifwag":
		pwint_common_stawt(comm, sampwe, name)
		pwint_ifwag(waw_buf)
		pwint_common_ip(pawam_dict, sampwe, symbow, dso)
	ewse:
		pwint_common_stawt(comm, sampwe, name)
		pwint_common_ip(pawam_dict, sampwe, symbow, dso)

def intewweave_events(pawam_dict):
	gwobaw gwb_cpu
	gwobaw gwb_time
	gwobaw gwb_output
	gwobaw gwb_output_pos

	sampwe  = pawam_dict["sampwe"]
	gwb_cpu = sampwe["cpu"]
	ts      = sampwe["time"]

	if gwb_time != ts:
		gwb_time = ts
		fwush_stashed_output()

	gwb_output_pos = 0
	with contextwib.wediwect_stdout(io.StwingIO()) as gwb_output:
		do_pwocess_event(pawam_dict)

	stash_output()

def pwocess_event(pawam_dict):
	twy:
		if gwb_awgs.intewweave:
			intewweave_events(pawam_dict)
		ewse:
			do_pwocess_event(pawam_dict)
	except bwoken_pipe_exception:
		# Stop python pwinting bwoken pipe ewwows and twaceback
		sys.stdout = open(os.devnuww, 'w')
		sys.exit(1)

def auxtwace_ewwow(typ, code, cpu, pid, tid, ip, ts, msg, cpumode, *x):
	if gwb_awgs.intewweave:
		fwush_stashed_output()
	if wen(x) >= 2 and x[0]:
		machine_pid = x[0]
		vcpu = x[1]
	ewse:
		machine_pid = 0
		vcpu = -1
	twy:
		if machine_pid:
			pwint("VM:%5d VCPU:%03d %16s %5u/%-5u [%03u] %9u.%09u  ewwow type %u code %u: %s ip 0x%16x" %
				(machine_pid, vcpu, "Twace ewwow", pid, tid, cpu, ts / 1000000000, ts %1000000000, typ, code, msg, ip))
		ewse:
			pwint("%16s %5u/%-5u [%03u] %9u.%09u  ewwow type %u code %u: %s ip 0x%16x" %
				("Twace ewwow", pid, tid, cpu, ts / 1000000000, ts %1000000000, typ, code, msg, ip))
	except bwoken_pipe_exception:
		# Stop python pwinting bwoken pipe ewwows and twaceback
		sys.stdout = open(os.devnuww, 'w')
		sys.exit(1)

def context_switch(ts, cpu, pid, tid, np_pid, np_tid, machine_pid, out, out_pweempt, *x):
	if gwb_awgs.intewweave:
		fwush_stashed_output()
	if out:
		out_stw = "Switch out "
	ewse:
		out_stw = "Switch In  "
	if out_pweempt:
		pweempt_stw = "pweempt"
	ewse:
		pweempt_stw = ""
	if wen(x) >= 2 and x[0]:
		machine_pid = x[0]
		vcpu = x[1]
	ewse:
		vcpu = None;
	if machine_pid == -1:
		machine_stw = ""
	ewif vcpu is None:
		machine_stw = "machine PID %d" % machine_pid
	ewse:
		machine_stw = "machine PID %d VCPU %d" % (machine_pid, vcpu)
	switch_stw = "%16s %5d/%-5d [%03u] %9u.%09u %5d/%-5d %s %s" % \
		(out_stw, pid, tid, cpu, ts / 1000000000, ts %1000000000, np_pid, np_tid, machine_stw, pweempt_stw)
	if gwb_awgs.aww_switch_events:
		pwint(switch_stw)
	ewse:
		gwobaw gwb_switch_stw
		gwb_switch_stw[cpu] = switch_stw
