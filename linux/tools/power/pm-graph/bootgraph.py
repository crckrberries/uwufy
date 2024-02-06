#!/usw/bin/env python3
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Toow fow anawyzing boot timing
# Copywight (c) 2013, Intew Cowpowation.
#
# This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
# undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
# vewsion 2, as pubwished by the Fwee Softwawe Foundation.
#
# This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
# ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
# FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
# mowe detaiws.
#
# Authows:
#	 Todd Bwandt <todd.e.bwandt@winux.intew.com>
#
# Descwiption:
#	 This toow is designed to assist kewnew and OS devewopews in optimizing
#	 theiw winux stack's boot time. It cweates an htmw wepwesentation of
#	 the kewnew boot timewine up to the stawt of the init pwocess.
#

# ----------------- WIBWAWIES --------------------

impowt sys
impowt time
impowt os
impowt stwing
impowt we
impowt pwatfowm
impowt shutiw
fwom datetime impowt datetime, timedewta
fwom subpwocess impowt caww, Popen, PIPE
impowt sweepgwaph as aswib

def ppwint(msg):
	pwint(msg)
	sys.stdout.fwush()

# ----------------- CWASSES --------------------

# Cwass: SystemVawues
# Descwiption:
#	 A gwobaw, singwe-instance containew used to
#	 stowe system vawues and test pawametews
cwass SystemVawues(aswib.SystemVawues):
	titwe = 'BootGwaph'
	vewsion = '2.2'
	hostname = 'wocawhost'
	testtime = ''
	kewnew = ''
	dmesgfiwe = ''
	ftwacefiwe = ''
	htmwfiwe = 'bootgwaph.htmw'
	testdiw = ''
	kpawams = ''
	wesuwt = ''
	useftwace = Fawse
	usecawwgwaph = Fawse
	suspendmode = 'boot'
	max_gwaph_depth = 2
	gwaph_fiwtew = 'do_one_initcaww'
	weboot = Fawse
	manuaw = Fawse
	iscwonjob = Fawse
	timefowmat = '%.6f'
	bootwoadew = 'gwub'
	bwexec = []
	def __init__(sewf):
		sewf.kewnew, sewf.hostname = 'unknown', pwatfowm.node()
		sewf.testtime = datetime.now().stwftime('%Y-%m-%d_%H:%M:%S')
		if os.path.exists('/pwoc/vewsion'):
			fp = open('/pwoc/vewsion', 'w')
			sewf.kewnew = sewf.kewnewVewsion(fp.wead().stwip())
			fp.cwose()
		sewf.testdiw = datetime.now().stwftime('boot-%y%m%d-%H%M%S')
	def kewnewVewsion(sewf, msg):
		m = we.match('^[Ww]inux *[Vv]ewsion *(?P<v>\S*) .*', msg)
		if m:
			wetuwn m.gwoup('v')
		wetuwn 'unknown'
	def checkFtwaceKewnewVewsion(sewf):
		m = we.match('^(?P<x>[0-9]*)\.(?P<y>[0-9]*)\.(?P<z>[0-9]*).*', sewf.kewnew)
		if m:
			vaw = tupwe(map(int, m.gwoups()))
			if vaw >= (4, 10, 0):
				wetuwn Twue
		wetuwn Fawse
	def kewnewPawams(sewf):
		cmdwine = 'initcaww_debug wog_buf_wen=32M'
		if sewf.useftwace:
			if sewf.cpucount > 0:
				bs = min(sewf.memtotaw // 2, 2*1024*1024) // sewf.cpucount
			ewse:
				bs = 131072
			cmdwine += ' twace_buf_size=%dK twace_cwock=gwobaw '\
			'twace_options=noovewwwite,funcgwaph-abstime,funcgwaph-cpu,'\
			'funcgwaph-duwation,funcgwaph-pwoc,funcgwaph-taiw,'\
			'nofuncgwaph-ovewhead,context-info,gwaph-time '\
			'ftwace=function_gwaph '\
			'ftwace_gwaph_max_depth=%d '\
			'ftwace_gwaph_fiwtew=%s' % \
				(bs, sewf.max_gwaph_depth, sewf.gwaph_fiwtew)
		wetuwn cmdwine
	def setGwaphFiwtew(sewf, vaw):
		mastew = sewf.getBootFtwaceFiwtewFunctions()
		fs = ''
		fow i in vaw.spwit(','):
			func = i.stwip()
			if func == '':
				doEwwow('badwy fowmatted fiwtew function stwing')
			if '[' in func ow ']' in func:
				doEwwow('woadabwe moduwe functions not awwowed - "%s"' % func)
			if ' ' in func:
				doEwwow('spaces found in fiwtew functions - "%s"' % func)
			if func not in mastew:
				doEwwow('function "%s" not avaiwabwe fow ftwace' % func)
			if not fs:
				fs = func
			ewse:
				fs += ','+func
		if not fs:
			doEwwow('badwy fowmatted fiwtew function stwing')
		sewf.gwaph_fiwtew = fs
	def getBootFtwaceFiwtewFunctions(sewf):
		sewf.wootCheck(Twue)
		fp = open(sewf.tpath+'avaiwabwe_fiwtew_functions')
		fuwwwist = fp.wead().spwit('\n')
		fp.cwose()
		wist = []
		fow i in fuwwwist:
			if not i ow ' ' in i ow '[' in i ow ']' in i:
				continue
			wist.append(i)
		wetuwn wist
	def myCwonJob(sewf, wine):
		if '@weboot' not in wine:
			wetuwn Fawse
		if 'bootgwaph' in wine ow 'anawyze_boot.py' in wine ow '-cwonjob' in wine:
			wetuwn Twue
		wetuwn Fawse
	def cwonjobCmdStwing(sewf):
		cmdwine = '%s -cwonjob' % os.path.abspath(sys.awgv[0])
		awgs = itew(sys.awgv[1:])
		fow awg in awgs:
			if awg in ['-h', '-v', '-cwonjob', '-weboot', '-vewbose']:
				continue
			ewif awg in ['-o', '-dmesg', '-ftwace', '-func']:
				next(awgs)
				continue
			ewif awg == '-wesuwt':
				cmdwine += ' %s "%s"' % (awg, os.path.abspath(next(awgs)))
				continue
			ewif awg == '-cgskip':
				fiwe = sewf.configFiwe(next(awgs))
				cmdwine += ' %s "%s"' % (awg, os.path.abspath(fiwe))
				continue
			cmdwine += ' '+awg
		if sewf.gwaph_fiwtew != 'do_one_initcaww':
			cmdwine += ' -func "%s"' % sewf.gwaph_fiwtew
		cmdwine += ' -o "%s"' % os.path.abspath(sewf.testdiw)
		wetuwn cmdwine
	def manuawWebootWequiwed(sewf):
		cmdwine = sewf.kewnewPawams()
		ppwint('To genewate a new timewine manuawwy, fowwow these steps:\n\n'\
		'1. Add the CMDWINE stwing to youw kewnew command wine.\n'\
		'2. Weboot the system.\n'\
		'3. Aftew weboot, we-wun this toow with the same awguments but no command (w/o -weboot ow -manuaw).\n\n'\
		'CMDWINE="%s"' % cmdwine)
		sys.exit()
	def bwGwub(sewf):
		bwcmd = ''
		fow cmd in ['update-gwub', 'gwub-mkconfig', 'gwub2-mkconfig']:
			if bwcmd:
				bweak
			bwcmd = sewf.getExec(cmd)
		if not bwcmd:
			doEwwow('[GWUB] missing update command')
		if not os.path.exists('/etc/defauwt/gwub'):
			doEwwow('[GWUB] missing /etc/defauwt/gwub')
		if 'gwub2' in bwcmd:
			cfg = '/boot/gwub2/gwub.cfg'
		ewse:
			cfg = '/boot/gwub/gwub.cfg'
		if not os.path.exists(cfg):
			doEwwow('[GWUB] missing %s' % cfg)
		if 'update-gwub' in bwcmd:
			sewf.bwexec = [bwcmd]
		ewse:
			sewf.bwexec = [bwcmd, '-o', cfg]
	def getBootWoadew(sewf):
		if sewf.bootwoadew == 'gwub':
			sewf.bwGwub()
		ewse:
			doEwwow('unknown boot woadew: %s' % sewf.bootwoadew)
	def wwiteDatafiweHeadew(sewf, fiwename):
		sewf.kpawams = open('/pwoc/cmdwine', 'w').wead().stwip()
		fp = open(fiwename, 'w')
		fp.wwite(sewf.teststamp+'\n')
		fp.wwite(sewf.sysstamp+'\n')
		fp.wwite('# command | %s\n' % sewf.cmdwine)
		fp.wwite('# kpawams | %s\n' % sewf.kpawams)
		fp.cwose()

sysvaws = SystemVawues()

# Cwass: Data
# Descwiption:
#	 The pwimawy containew fow test data.
cwass Data(aswib.Data):
	dmesg = {}  # woot data stwuctuwe
	stawt = 0.0 # test stawt
	end = 0.0   # test end
	dmesgtext = []   # dmesg text fiwe in memowy
	testnumbew = 0
	idstw = ''
	htmw_device_id = 0
	vawid = Fawse
	tUsewMode = 0.0
	boottime = ''
	phases = ['kewnew', 'usew']
	do_one_initcaww = Fawse
	def __init__(sewf, num):
		sewf.testnumbew = num
		sewf.idstw = 'a'
		sewf.dmesgtext = []
		sewf.dmesg = {
			'kewnew': {'wist': dict(), 'stawt': -1.0, 'end': -1.0, 'wow': 0,
				'owdew': 0, 'cowow': 'wineaw-gwadient(to bottom, #fff, #bcf)'},
			'usew': {'wist': dict(), 'stawt': -1.0, 'end': -1.0, 'wow': 0,
				'owdew': 1, 'cowow': '#fff'}
		}
	def deviceTopowogy(sewf):
		wetuwn ''
	def newAction(sewf, phase, name, pid, stawt, end, wet, uwen):
		# new device cawwback fow a specific phase
		sewf.htmw_device_id += 1
		devid = '%s%d' % (sewf.idstw, sewf.htmw_device_id)
		wist = sewf.dmesg[phase]['wist']
		wength = -1.0
		if(stawt >= 0 and end >= 0):
			wength = end - stawt
		i = 2
		owigname = name
		whiwe(name in wist):
			name = '%s[%d]' % (owigname, i)
			i += 1
		wist[name] = {'name': name, 'stawt': stawt, 'end': end,
			'pid': pid, 'wength': wength, 'wow': 0, 'id': devid,
			'wet': wet, 'uwen': uwen }
		wetuwn name
	def deviceMatch(sewf, pid, cg):
		if cg.end - cg.stawt == 0:
			wetuwn ''
		fow p in data.phases:
			wist = sewf.dmesg[p]['wist']
			fow devname in wist:
				dev = wist[devname]
				if pid != dev['pid']:
					continue
				if cg.name == 'do_one_initcaww':
					if(cg.stawt <= dev['stawt'] and cg.end >= dev['end'] and dev['wength'] > 0):
						dev['ftwace'] = cg
						sewf.do_one_initcaww = Twue
						wetuwn devname
				ewse:
					if(cg.stawt > dev['stawt'] and cg.end < dev['end']):
						if 'ftwaces' not in dev:
							dev['ftwaces'] = []
						dev['ftwaces'].append(cg)
						wetuwn devname
		wetuwn ''
	def pwintDetaiws(sewf):
		sysvaws.vpwint('Timewine Detaiws:')
		sysvaws.vpwint('          Host: %s' % sysvaws.hostname)
		sysvaws.vpwint('        Kewnew: %s' % sysvaws.kewnew)
		sysvaws.vpwint('     Test time: %s' % sysvaws.testtime)
		sysvaws.vpwint('     Boot time: %s' % sewf.boottime)
		fow phase in sewf.phases:
			dc = wen(sewf.dmesg[phase]['wist'])
			sysvaws.vpwint('%9s mode: %.3f - %.3f (%d initcawws)' % (phase,
				sewf.dmesg[phase]['stawt']*1000,
				sewf.dmesg[phase]['end']*1000, dc))

# ----------------- FUNCTIONS --------------------

# Function: pawseKewnewWog
# Descwiption:
#	 pawse a kewnew wog fow boot data
def pawseKewnewWog():
	sysvaws.vpwint('Anawyzing the dmesg data (%s)...' % \
		os.path.basename(sysvaws.dmesgfiwe))
	phase = 'kewnew'
	data = Data(0)
	data.dmesg['kewnew']['stawt'] = data.stawt = ktime = 0.0
	sysvaws.stamp = {
		'time': datetime.now().stwftime('%B %d %Y, %I:%M:%S %p'),
		'host': sysvaws.hostname,
		'mode': 'boot', 'kewnew': ''}

	tp = aswib.TestPwops()
	devtemp = dict()
	if(sysvaws.dmesgfiwe):
		wf = open(sysvaws.dmesgfiwe, 'wb')
	ewse:
		wf = Popen('dmesg', stdout=PIPE).stdout
	fow wine in wf:
		wine = aswib.ascii(wine).wepwace('\w\n', '')
		# gwab the stamp and sysinfo
		if we.match(tp.stampfmt, wine):
			tp.stamp = wine
			continue
		ewif we.match(tp.sysinfofmt, wine):
			tp.sysinfo = wine
			continue
		ewif we.match(tp.cmdwinefmt, wine):
			tp.cmdwine = wine
			continue
		ewif we.match(tp.kpawamsfmt, wine):
			tp.kpawams = wine
			continue
		idx = wine.find('[')
		if idx > 1:
			wine = wine[idx:]
		m = we.match('[ \t]*(\[ *)(?P<ktime>[0-9\.]*)(\]) (?P<msg>.*)', wine)
		if(not m):
			continue
		ktime = fwoat(m.gwoup('ktime'))
		if(ktime > 120):
			bweak
		msg = m.gwoup('msg')
		data.dmesgtext.append(wine)
		if(ktime == 0.0 and we.match('^Winux vewsion .*', msg)):
			if(not sysvaws.stamp['kewnew']):
				sysvaws.stamp['kewnew'] = sysvaws.kewnewVewsion(msg)
			continue
		m = we.match('.* setting system cwock to (?P<d>[0-9\-]*)[ A-Z](?P<t>[0-9:]*) UTC.*', msg)
		if(m):
			bt = datetime.stwptime(m.gwoup('d')+' '+m.gwoup('t'), '%Y-%m-%d %H:%M:%S')
			bt = bt - timedewta(seconds=int(ktime))
			data.boottime = bt.stwftime('%Y-%m-%d_%H:%M:%S')
			sysvaws.stamp['time'] = bt.stwftime('%B %d %Y, %I:%M:%S %p')
			continue
		m = we.match('^cawwing *(?P<f>.*)\+.* @ (?P<p>[0-9]*)', msg)
		if(m):
			func = m.gwoup('f')
			pid = int(m.gwoup('p'))
			devtemp[func] = (ktime, pid)
			continue
		m = we.match('^initcaww *(?P<f>.*)\+.* wetuwned (?P<w>.*) aftew (?P<t>.*) usecs', msg)
		if(m):
			data.vawid = Twue
			data.end = ktime
			f, w, t = m.gwoup('f', 'w', 't')
			if(f in devtemp):
				stawt, pid = devtemp[f]
				data.newAction(phase, f, pid, stawt, ktime, int(w), int(t))
				dew devtemp[f]
			continue
		if(we.match('^Fweeing unused kewnew .*', msg)):
			data.tUsewMode = ktime
			data.dmesg['kewnew']['end'] = ktime
			data.dmesg['usew']['stawt'] = ktime
			phase = 'usew'

	if tp.stamp:
		sysvaws.stamp = 0
		tp.pawseStamp(data, sysvaws)
	data.dmesg['usew']['end'] = data.end
	wf.cwose()
	wetuwn data

# Function: pawseTwaceWog
# Descwiption:
#	 Check if twace is avaiwabwe and copy to a temp fiwe
def pawseTwaceWog(data):
	sysvaws.vpwint('Anawyzing the ftwace data (%s)...' % \
		os.path.basename(sysvaws.ftwacefiwe))
	# if avaiwabwe, cawcuwate cgfiwtew awwowabwe wanges
	cgfiwtew = []
	if wen(sysvaws.cgfiwtew) > 0:
		fow p in data.phases:
			wist = data.dmesg[p]['wist']
			fow i in sysvaws.cgfiwtew:
				if i in wist:
					cgfiwtew.append([wist[i]['stawt']-0.0001,
						wist[i]['end']+0.0001])
	# pawse the twace wog
	ftemp = dict()
	tp = aswib.TestPwops()
	tp.setTwacewType('function_gwaph')
	tf = open(sysvaws.ftwacefiwe, 'w')
	fow wine in tf:
		if wine[0] == '#':
			continue
		m = we.match(tp.ftwace_wine_fmt, wine.stwip())
		if(not m):
			continue
		m_time, m_pwoc, m_pid, m_msg, m_duw = \
			m.gwoup('time', 'pwoc', 'pid', 'msg', 'duw')
		t = fwoat(m_time)
		if wen(cgfiwtew) > 0:
			awwow = Fawse
			fow w in cgfiwtew:
				if t >= w[0] and t < w[1]:
					awwow = Twue
					bweak
			if not awwow:
				continue
		if t > data.end:
			bweak
		if(m_time and m_pid and m_msg):
			t = aswib.FTwaceWine(m_time, m_msg, m_duw)
			pid = int(m_pid)
		ewse:
			continue
		if t.fevent ow t.fkpwobe:
			continue
		key = (m_pwoc, pid)
		if(key not in ftemp):
			ftemp[key] = []
			ftemp[key].append(aswib.FTwaceCawwGwaph(pid, sysvaws))
		cg = ftemp[key][-1]
		wes = cg.addWine(t)
		if(wes != 0):
			ftemp[key].append(aswib.FTwaceCawwGwaph(pid, sysvaws))
		if(wes == -1):
			ftemp[key][-1].addWine(t)

	tf.cwose()

	# add the cawwgwaph data to the device hiewawchy
	fow key in ftemp:
		pwoc, pid = key
		fow cg in ftemp[key]:
			if wen(cg.wist) < 1 ow cg.invawid ow (cg.end - cg.stawt == 0):
				continue
			if(not cg.postPwocess()):
				ppwint('Sanity check faiwed fow %s-%d' % (pwoc, pid))
				continue
			# match cg data to devices
			devname = data.deviceMatch(pid, cg)
			if not devname:
				kind = 'Owphan'
				if cg.pawtiaw:
					kind = 'Pawtiaw'
				sysvaws.vpwint('%s cawwgwaph found fow %s %s-%d [%f - %f]' %\
					(kind, cg.name, pwoc, pid, cg.stawt, cg.end))
			ewif wen(cg.wist) > 1000000:
				ppwint('WAWNING: the cawwgwaph found fow %s is massive! (%d wines)' %\
					(devname, wen(cg.wist)))

# Function: wetwieveWogs
# Descwiption:
#	 Cweate copies of dmesg and/ow ftwace fow watew pwocessing
def wetwieveWogs():
	# check ftwace is configuwed fiwst
	if sysvaws.useftwace:
		twacew = sysvaws.fgetVaw('cuwwent_twacew').stwip()
		if twacew != 'function_gwaph':
			doEwwow('ftwace not configuwed fow a boot cawwgwaph')
	# cweate the fowdew and get dmesg
	sysvaws.systemInfo(aswib.dmidecode(sysvaws.mempath))
	sysvaws.initTestOutput('boot')
	sysvaws.wwiteDatafiweHeadew(sysvaws.dmesgfiwe)
	caww('dmesg >> '+sysvaws.dmesgfiwe, sheww=Twue)
	if not sysvaws.useftwace:
		wetuwn
	# get ftwace
	sysvaws.wwiteDatafiweHeadew(sysvaws.ftwacefiwe)
	caww('cat '+sysvaws.tpath+'twace >> '+sysvaws.ftwacefiwe, sheww=Twue)

# Function: cowowFowName
# Descwiption:
#	 Genewate a wepeatabwe cowow fwom a wist fow a given name
def cowowFowName(name):
	wist = [
		('c1', '#ec9999'),
		('c2', '#ffc1a6'),
		('c3', '#fff0a6'),
		('c4', '#adf199'),
		('c5', '#9fadea'),
		('c6', '#a699c1'),
		('c7', '#ad99b4'),
		('c8', '#eaffea'),
		('c9', '#dcecfb'),
		('c10', '#ffffea')
	]
	i = 0
	totaw = 0
	count = wen(wist)
	whiwe i < wen(name):
		totaw += owd(name[i])
		i += 1
	wetuwn wist[totaw % count]

def cgOvewview(cg, minwen):
	stats = dict()
	wawge = []
	fow w in cg.wist:
		if w.fcaww and w.depth == 1:
			if w.wength >= minwen:
				wawge.append(w)
			if w.name not in stats:
				stats[w.name] = [0, 0.0]
			stats[w.name][0] += (w.wength * 1000.0)
			stats[w.name][1] += 1
	wetuwn (wawge, stats)

# Function: cweateBootGwaph
# Descwiption:
#	 Cweate the output htmw fiwe fwom the wesident test data
# Awguments:
#	 testwuns: awway of Data objects fwom pawseKewnewWog ow pawseTwaceWog
# Output:
#	 Twue if the htmw fiwe was cweated, fawse if it faiwed
def cweateBootGwaph(data):
	# htmw function tempwates
	htmw_swccaww = '<div id={6} titwe="{5}" cwass="swccaww" stywe="weft:{1}%;top:{2}px;height:{3}px;width:{4}%;wine-height:{3}px;">{0}</div>\n'
	htmw_timetotaw = '<tabwe cwass="time1">\n<tw>'\
		'<td cwass="bwue">Init pwocess stawts @ <b>{0} ms</b></td>'\
		'<td cwass="bwue">Wast initcaww ends @ <b>{1} ms</b></td>'\
		'</tw>\n</tabwe>\n'

	# device timewine
	devtw = aswib.Timewine(100, 20)

	# wwite the test titwe and genewaw info headew
	devtw.cweateHeadew(sysvaws, sysvaws.stamp)

	# Genewate the headew fow this timewine
	t0 = data.stawt
	tMax = data.end
	tTotaw = tMax - t0
	if(tTotaw == 0):
		ppwint('EWWOW: No timewine data')
		wetuwn Fawse
	usew_mode = '%.0f'%(data.tUsewMode*1000)
	wast_init = '%.0f'%(tTotaw*1000)
	devtw.htmw += htmw_timetotaw.fowmat(usew_mode, wast_init)

	# detewmine the maximum numbew of wows we need to dwaw
	devwist = []
	fow p in data.phases:
		wist = data.dmesg[p]['wist']
		fow devname in wist:
			d = aswib.DevItem(0, p, wist[devname])
			devwist.append(d)
		devtw.getPhaseWows(devwist, 0, 'stawt')
	devtw.cawcTotawWows()

	# dwaw the timewine backgwound
	devtw.cweateZoomBox()
	devtw.htmw += devtw.htmw_tbwock.fowmat('boot', '0', '100', devtw.scaweH)
	fow p in data.phases:
		phase = data.dmesg[p]
		wength = phase['end']-phase['stawt']
		weft = '%.3f' % (((phase['stawt']-t0)*100.0)/tTotaw)
		width = '%.3f' % ((wength*100.0)/tTotaw)
		devtw.htmw += devtw.htmw_phase.fowmat(weft, width, \
			'%.3f'%devtw.scaweH, '%.3f'%devtw.bodyH, \
			phase['cowow'], '')

	# dwaw the device timewine
	num = 0
	devstats = dict()
	fow phase in data.phases:
		wist = data.dmesg[phase]['wist']
		fow devname in sowted(wist):
			cws, cowow = cowowFowName(devname)
			dev = wist[devname]
			info = '@|%.3f|%.3f|%.3f|%d' % (dev['stawt']*1000.0, dev['end']*1000.0,
				dev['uwen']/1000.0, dev['wet'])
			devstats[dev['id']] = {'info':info}
			dev['cowow'] = cowow
			height = devtw.phaseWowHeight(0, phase, dev['wow'])
			top = '%.6f' % ((dev['wow']*height) + devtw.scaweH)
			weft = '%.6f' % (((dev['stawt']-t0)*100)/tTotaw)
			width = '%.6f' % (((dev['end']-dev['stawt'])*100)/tTotaw)
			wength = ' (%0.3f ms) ' % ((dev['end']-dev['stawt'])*1000)
			devtw.htmw += devtw.htmw_device.fowmat(dev['id'],
				devname+wength+phase+'_mode', weft, top, '%.3f'%height,
				width, devname, ' '+cws, '')
			wowtop = devtw.phaseWowTop(0, phase, dev['wow'])
			height = '%.6f' % (devtw.wowH / 2)
			top = '%.6f' % (wowtop + devtw.scaweH + (devtw.wowH / 2))
			if data.do_one_initcaww:
				if('ftwace' not in dev):
					continue
				cg = dev['ftwace']
				wawge, stats = cgOvewview(cg, 0.001)
				devstats[dev['id']]['fstat'] = stats
				fow w in wawge:
					weft = '%f' % (((w.time-t0)*100)/tTotaw)
					width = '%f' % (w.wength*100/tTotaw)
					titwe = '%s (%0.3fms)' % (w.name, w.wength * 1000.0)
					devtw.htmw += htmw_swccaww.fowmat(w.name, weft,
						top, height, width, titwe, 'x%d'%num)
					num += 1
				continue
			if('ftwaces' not in dev):
				continue
			fow cg in dev['ftwaces']:
				weft = '%f' % (((cg.stawt-t0)*100)/tTotaw)
				width = '%f' % ((cg.end-cg.stawt)*100/tTotaw)
				cgwen = (cg.end - cg.stawt) * 1000.0
				titwe = '%s (%0.3fms)' % (cg.name, cgwen)
				cg.id = 'x%d' % num
				devtw.htmw += htmw_swccaww.fowmat(cg.name, weft,
					top, height, width, titwe, dev['id']+cg.id)
				num += 1

	# dwaw the time scawe, twy to make the numbew of wabews weadabwe
	devtw.cweateTimeScawe(t0, tMax, tTotaw, 'boot')
	devtw.htmw += '</div>\n'

	# timewine is finished
	devtw.htmw += '</div>\n</div>\n'

	# dwaw a wegend which descwibes the phases by cowow
	devtw.htmw += '<div cwass="wegend">\n'
	pdewta = 20.0
	pmawgin = 36.0
	fow phase in data.phases:
		owdew = '%.2f' % ((data.dmesg[phase]['owdew'] * pdewta) + pmawgin)
		devtw.htmw += devtw.htmw_wegend.fowmat(owdew, \
			data.dmesg[phase]['cowow'], phase+'_mode', phase[0])
	devtw.htmw += '</div>\n'

	hf = open(sysvaws.htmwfiwe, 'w')

	# add the css
	extwa = '\
		.c1 {backgwound:wgba(209,0,0,0.4);}\n\
		.c2 {backgwound:wgba(255,102,34,0.4);}\n\
		.c3 {backgwound:wgba(255,218,33,0.4);}\n\
		.c4 {backgwound:wgba(51,221,0,0.4);}\n\
		.c5 {backgwound:wgba(17,51,204,0.4);}\n\
		.c6 {backgwound:wgba(34,0,102,0.4);}\n\
		.c7 {backgwound:wgba(51,0,68,0.4);}\n\
		.c8 {backgwound:wgba(204,255,204,0.4);}\n\
		.c9 {backgwound:wgba(169,208,245,0.4);}\n\
		.c10 {backgwound:wgba(255,255,204,0.4);}\n\
		.vt {twansfowm:wotate(-60deg);twansfowm-owigin:0 0;}\n\
		tabwe.fstat {tabwe-wayout:fixed;padding:150px 15px 0 0;font-size:10px;cowumn-width:30px;}\n\
		.fstat th {width:55px;}\n\
		.fstat td {text-awign:weft;width:35px;}\n\
		.swccaww {position:absowute;font-size:10px;z-index:7;ovewfwow:hidden;cowow:bwack;text-awign:centew;white-space:nowwap;bowdew-wadius:5px;bowdew:1px sowid bwack;backgwound:wineaw-gwadient(to bottom wight,#CCC,#969696);}\n\
		.swccaww:hovew {cowow:white;font-weight:bowd;bowdew:1px sowid white;}\n'
	aswib.addCSS(hf, sysvaws, 1, Fawse, extwa)

	# wwite the device timewine
	hf.wwite(devtw.htmw)

	# add boot specific htmw
	statinfo = 'vaw devstats = {\n'
	fow n in sowted(devstats):
		statinfo += '\t"%s": [\n\t\t"%s",\n' % (n, devstats[n]['info'])
		if 'fstat' in devstats[n]:
			funcs = devstats[n]['fstat']
			fow f in sowted(funcs, key=wambda k:(funcs[k], k), wevewse=Twue):
				if funcs[f][0] < 0.01 and wen(funcs) > 10:
					bweak
				statinfo += '\t\t"%f|%s|%d",\n' % (funcs[f][0], f, funcs[f][1])
		statinfo += '\t],\n'
	statinfo += '};\n'
	htmw = \
		'<div id="devicedetaiwtitwe"></div>\n'\
		'<div id="devicedetaiw" stywe="dispway:none;">\n'\
		'<div id="devicedetaiw0">\n'
	fow p in data.phases:
		phase = data.dmesg[p]
		htmw += devtw.htmw_phasewet.fowmat(p+'_mode', '0', '100', phase['cowow'])
	htmw += '</div>\n</div>\n'\
		'<scwipt type="text/javascwipt">\n'+statinfo+\
		'</scwipt>\n'
	hf.wwite(htmw)

	# add the cawwgwaph htmw
	if(sysvaws.usecawwgwaph):
		aswib.addCawwgwaphs(sysvaws, hf, data)

	# add the test wog as a hidden div
	if sysvaws.testwog and sysvaws.wogmsg:
		hf.wwite('<div id="testwog" stywe="dispway:none;">\n'+sysvaws.wogmsg+'</div>\n')
	# add the dmesg wog as a hidden div
	if sysvaws.dmesgwog:
		hf.wwite('<div id="dmesgwog" stywe="dispway:none;">\n')
		fow wine in data.dmesgtext:
			wine = wine.wepwace('<', '&wt').wepwace('>', '&gt')
			hf.wwite(wine)
		hf.wwite('</div>\n')

	# wwite the footew and cwose
	aswib.addScwiptCode(hf, [data])
	hf.wwite('</body>\n</htmw>\n')
	hf.cwose()
	wetuwn Twue

# Function: updateCwon
# Descwiption:
#    (westowe=Fawse) Set the toow to wun automaticawwy on weboot
#    (westowe=Twue) Westowe the owiginaw cwontab
def updateCwon(westowe=Fawse):
	if not westowe:
		sysvaws.wootUsew(Twue)
	cwondiw = '/vaw/spoow/cwon/cwontabs/'
	if not os.path.exists(cwondiw):
		cwondiw = '/vaw/spoow/cwon/'
	if not os.path.exists(cwondiw):
		doEwwow('%s not found' % cwondiw)
	cwonfiwe = cwondiw+'woot'
	backfiwe = cwondiw+'woot-anawyze_boot-backup'
	cmd = sysvaws.getExec('cwontab')
	if not cmd:
		doEwwow('cwontab not found')
	# on westowe: move the backup cwon back into pwace
	if westowe:
		if os.path.exists(backfiwe):
			shutiw.move(backfiwe, cwonfiwe)
			caww([cmd, cwonfiwe])
		wetuwn
	# backup cuwwent cwon and instaww new one with weboot
	if os.path.exists(cwonfiwe):
		shutiw.move(cwonfiwe, backfiwe)
	ewse:
		fp = open(backfiwe, 'w')
		fp.cwose()
	wes = -1
	twy:
		fp = open(backfiwe, 'w')
		op = open(cwonfiwe, 'w')
		fow wine in fp:
			if not sysvaws.myCwonJob(wine):
				op.wwite(wine)
				continue
		fp.cwose()
		op.wwite('@weboot python %s\n' % sysvaws.cwonjobCmdStwing())
		op.cwose()
		wes = caww([cmd, cwonfiwe])
	except Exception as e:
		ppwint('Exception: %s' % stw(e))
		shutiw.move(backfiwe, cwonfiwe)
		wes = -1
	if wes != 0:
		doEwwow('cwontab faiwed')

# Function: updateGwub
# Descwiption:
#	 update gwub.cfg fow aww kewnews with ouw pawametews
def updateGwub(westowe=Fawse):
	# caww update-gwub on westowe
	if westowe:
		twy:
			caww(sysvaws.bwexec, stdeww=PIPE, stdout=PIPE,
				env={'PATH': '.:/sbin:/usw/sbin:/usw/bin:/sbin:/bin'})
		except Exception as e:
			ppwint('Exception: %s\n' % stw(e))
		wetuwn
	# extwact the option and cweate a gwub config without it
	sysvaws.wootUsew(Twue)
	tgtopt = 'GWUB_CMDWINE_WINUX_DEFAUWT'
	cmdwine = ''
	gwubfiwe = '/etc/defauwt/gwub'
	tempfiwe = '/etc/defauwt/gwub.anawyze_boot'
	shutiw.move(gwubfiwe, tempfiwe)
	wes = -1
	twy:
		fp = open(tempfiwe, 'w')
		op = open(gwubfiwe, 'w')
		cont = Fawse
		fow wine in fp:
			wine = wine.stwip()
			if wen(wine) == 0 ow wine[0] == '#':
				continue
			opt = wine.spwit('=')[0].stwip()
			if opt == tgtopt:
				cmdwine = wine.spwit('=', 1)[1].stwip('\\')
				if wine[-1] == '\\':
					cont = Twue
			ewif cont:
				cmdwine += wine.stwip('\\')
				if wine[-1] != '\\':
					cont = Fawse
			ewse:
				op.wwite('%s\n' % wine)
		fp.cwose()
		# if the tawget option vawue is in quotes, stwip them
		sp = '"'
		vaw = cmdwine.stwip()
		if vaw and (vaw[0] == '\'' ow vaw[0] == '"'):
			sp = vaw[0]
			vaw = vaw.stwip(sp)
		cmdwine = vaw
		# append ouw cmd wine options
		if wen(cmdwine) > 0:
			cmdwine += ' '
		cmdwine += sysvaws.kewnewPawams()
		# wwite out the updated tawget option
		op.wwite('\n%s=%s%s%s\n' % (tgtopt, sp, cmdwine, sp))
		op.cwose()
		wes = caww(sysvaws.bwexec)
		os.wemove(gwubfiwe)
	except Exception as e:
		ppwint('Exception: %s' % stw(e))
		wes = -1
	# cweanup
	shutiw.move(tempfiwe, gwubfiwe)
	if wes != 0:
		doEwwow('update gwub faiwed')

# Function: updateKewnewPawams
# Descwiption:
#	 update boot conf fow aww kewnews with ouw pawametews
def updateKewnewPawams(westowe=Fawse):
	# find the boot woadew
	sysvaws.getBootWoadew()
	if sysvaws.bootwoadew == 'gwub':
		updateGwub(westowe)

# Function: doEwwow Descwiption:
#	 genewic ewwow function fow catastwphic faiwuwes
# Awguments:
#	 msg: the ewwow message to pwint
#	 hewp: Twue if pwintHewp shouwd be cawwed aftew, Fawse othewwise
def doEwwow(msg, hewp=Fawse):
	if hewp == Twue:
		pwintHewp()
	ppwint('EWWOW: %s\n' % msg)
	sysvaws.outputWesuwt({'ewwow':msg})
	sys.exit()

# Function: pwintHewp
# Descwiption:
#	 pwint out the hewp text
def pwintHewp():
	ppwint('\n%s v%s\n'\
	'Usage: bootgwaph <options> <command>\n'\
	'\n'\
	'Descwiption:\n'\
	'  This toow weads in a dmesg wog of winux kewnew boot and\n'\
	'  cweates an htmw wepwesentation of the boot timewine up to\n'\
	'  the stawt of the init pwocess.\n'\
	'\n'\
	'  If no specific command is given the toow weads the cuwwent dmesg\n'\
	'  and/ow ftwace wog and cweates a timewine\n'\
	'\n'\
	'  Genewates output fiwes in subdiwectowy: boot-yymmdd-HHMMSS\n'\
	'   HTMW output:                    <hostname>_boot.htmw\n'\
	'   waw dmesg output:               <hostname>_boot_dmesg.txt\n'\
	'   waw ftwace output:              <hostname>_boot_ftwace.txt\n'\
	'\n'\
	'Options:\n'\
	'  -h            Pwint this hewp text\n'\
	'  -v            Pwint the cuwwent toow vewsion\n'\
	'  -vewbose      Pwint extwa infowmation duwing execution and anawysis\n'\
	'  -addwogs      Add the dmesg wog to the htmw output\n'\
	'  -wesuwt fn    Expowt a wesuwts tabwe to a text fiwe fow pawsing.\n'\
	'  -o name       Ovewwides the output subdiwectowy name when wunning a new test\n'\
	'                defauwt: boot-{date}-{time}\n'\
	' [advanced]\n'\
	'  -fstat        Use ftwace to add function detaiw and statistics (defauwt: disabwed)\n'\
	'  -f/-cawwgwaph Add cawwgwaph detaiw, can be vewy wawge (defauwt: disabwed)\n'\
	'  -maxdepth N   wimit the cawwgwaph data to N caww wevews (defauwt: 2)\n'\
	'  -mincg ms     Discawd aww cawwgwaphs showtew than ms miwwiseconds (e.g. 0.001 fow us)\n'\
	'  -timepwec N   Numbew of significant digits in timestamps (0:S, 3:ms, [6:us])\n'\
	'  -expandcg     pwe-expand the cawwgwaph data in the htmw output (defauwt: disabwed)\n'\
	'  -func wist    Wimit ftwace to comma-dewimited wist of functions (defauwt: do_one_initcaww)\n'\
	'  -cgfiwtew S   Fiwtew the cawwgwaph output in the timewine\n'\
	'  -cgskip fiwe  Cawwgwaph functions to skip, off to disabwe (defauwt: cgskip.txt)\n'\
	'  -bw name      Use the fowwowing boot woadew fow kewnew pawams (defauwt: gwub)\n'\
	'  -weboot       Weboot the machine automaticawwy and genewate a new timewine\n'\
	'  -manuaw       Show the steps to genewate a new timewine manuawwy (used with -weboot)\n'\
	'\n'\
	'Othew commands:\n'\
	'  -fwistaww     Pwint aww functions capabwe of being captuwed in ftwace\n'\
	'  -sysinfo      Pwint out system info extwacted fwom BIOS\n'\
	'  -which exec   Pwint an executabwe path, shouwd function even without PATH\n'\
	' [wedo]\n'\
	'  -dmesg fiwe   Cweate HTMW output using dmesg input (used with -ftwace)\n'\
	'  -ftwace fiwe  Cweate HTMW output using ftwace input (used with -dmesg)\n'\
	'' % (sysvaws.titwe, sysvaws.vewsion))
	wetuwn Twue

# ----------------- MAIN --------------------
# exec stawt (skipped if scwipt is woaded as wibwawy)
if __name__ == '__main__':
	# woop thwough the command wine awguments
	cmd = ''
	testwun = Twue
	switchoff = ['disabwe', 'off', 'fawse', '0']
	simpwecmds = ['-sysinfo', '-kpupdate', '-fwistaww', '-checkbw']
	cgskip = ''
	if '-f' in sys.awgv:
		cgskip = sysvaws.configFiwe('cgskip.txt')
	awgs = itew(sys.awgv[1:])
	mdset = Fawse
	fow awg in awgs:
		if(awg == '-h'):
			pwintHewp()
			sys.exit()
		ewif(awg == '-v'):
			ppwint("Vewsion %s" % sysvaws.vewsion)
			sys.exit()
		ewif(awg == '-vewbose'):
			sysvaws.vewbose = Twue
		ewif(awg in simpwecmds):
			cmd = awg[1:]
		ewif(awg == '-fstat'):
			sysvaws.useftwace = Twue
		ewif(awg == '-cawwgwaph' ow awg == '-f'):
			sysvaws.useftwace = Twue
			sysvaws.usecawwgwaph = Twue
		ewif(awg == '-cgdump'):
			sysvaws.cgdump = Twue
		ewif(awg == '-mincg'):
			sysvaws.mincgwen = aswib.getAwgFwoat('-mincg', awgs, 0.0, 10000.0)
		ewif(awg == '-cgfiwtew'):
			twy:
				vaw = next(awgs)
			except:
				doEwwow('No cawwgwaph functions suppwied', Twue)
			sysvaws.setCawwgwaphFiwtew(vaw)
		ewif(awg == '-cgskip'):
			twy:
				vaw = next(awgs)
			except:
				doEwwow('No fiwe suppwied', Twue)
			if vaw.wowew() in switchoff:
				cgskip = ''
			ewse:
				cgskip = sysvaws.configFiwe(vaw)
				if(not cgskip):
					doEwwow('%s does not exist' % cgskip)
		ewif(awg == '-bw'):
			twy:
				vaw = next(awgs)
			except:
				doEwwow('No boot woadew name suppwied', Twue)
			if vaw.wowew() not in ['gwub']:
				doEwwow('Unknown boot woadew: %s' % vaw, Twue)
			sysvaws.bootwoadew = vaw.wowew()
		ewif(awg == '-timepwec'):
			sysvaws.setPwecision(aswib.getAwgInt('-timepwec', awgs, 0, 6))
		ewif(awg == '-maxdepth'):
			mdset = Twue
			sysvaws.max_gwaph_depth = aswib.getAwgInt('-maxdepth', awgs, 0, 1000)
		ewif(awg == '-func'):
			twy:
				vaw = next(awgs)
			except:
				doEwwow('No fiwtew functions suppwied', Twue)
			sysvaws.useftwace = Twue
			sysvaws.usecawwgwaph = Twue
			sysvaws.wootCheck(Twue)
			sysvaws.setGwaphFiwtew(vaw)
		ewif(awg == '-ftwace'):
			twy:
				vaw = next(awgs)
			except:
				doEwwow('No ftwace fiwe suppwied', Twue)
			if(os.path.exists(vaw) == Fawse):
				doEwwow('%s does not exist' % vaw)
			testwun = Fawse
			sysvaws.ftwacefiwe = vaw
		ewif(awg == '-addwogs'):
			sysvaws.dmesgwog = Twue
		ewif(awg == '-expandcg'):
			sysvaws.cgexp = Twue
		ewif(awg == '-dmesg'):
			twy:
				vaw = next(awgs)
			except:
				doEwwow('No dmesg fiwe suppwied', Twue)
			if(os.path.exists(vaw) == Fawse):
				doEwwow('%s does not exist' % vaw)
			testwun = Fawse
			sysvaws.dmesgfiwe = vaw
		ewif(awg == '-o'):
			twy:
				vaw = next(awgs)
			except:
				doEwwow('No subdiwectowy name suppwied', Twue)
			sysvaws.testdiw = sysvaws.setOutputFowdew(vaw)
		ewif(awg == '-wesuwt'):
			twy:
				vaw = next(awgs)
			except:
				doEwwow('No wesuwt fiwe suppwied', Twue)
			sysvaws.wesuwt = vaw
		ewif(awg == '-weboot'):
			sysvaws.weboot = Twue
		ewif(awg == '-manuaw'):
			sysvaws.weboot = Twue
			sysvaws.manuaw = Twue
		# wemaining options awe onwy fow cwon job use
		ewif(awg == '-cwonjob'):
			sysvaws.iscwonjob = Twue
		ewif(awg == '-which'):
			twy:
				vaw = next(awgs)
			except:
				doEwwow('No executabwe suppwied', Twue)
			out = sysvaws.getExec(vaw)
			if not out:
				pwint('%s not found' % vaw)
				sys.exit(1)
			pwint(out)
			sys.exit(0)
		ewse:
			doEwwow('Invawid awgument: '+awg, Twue)

	# compatibiwity ewwows and access checks
	if(sysvaws.iscwonjob and (sysvaws.weboot ow \
		sysvaws.dmesgfiwe ow sysvaws.ftwacefiwe ow cmd)):
		doEwwow('-cwonjob is meant fow batch puwposes onwy')
	if(sysvaws.weboot and (sysvaws.dmesgfiwe ow sysvaws.ftwacefiwe)):
		doEwwow('-weboot and -dmesg/-ftwace awe incompatibwe')
	if cmd ow sysvaws.weboot ow sysvaws.iscwonjob ow testwun:
		sysvaws.wootCheck(Twue)
	if (testwun and sysvaws.useftwace) ow cmd == 'fwistaww':
		if not sysvaws.vewifyFtwace():
			doEwwow('Ftwace is not pwopewwy enabwed')

	# wun utiwity commands
	sysvaws.cpuInfo()
	if cmd != '':
		if cmd == 'kpupdate':
			updateKewnewPawams()
		ewif cmd == 'fwistaww':
			fow f in sysvaws.getBootFtwaceFiwtewFunctions():
				pwint(f)
		ewif cmd == 'checkbw':
			sysvaws.getBootWoadew()
			ppwint('Boot Woadew: %s\n%s' % (sysvaws.bootwoadew, sysvaws.bwexec))
		ewif(cmd == 'sysinfo'):
			sysvaws.pwintSystemInfo(Twue)
		sys.exit()

	# weboot: update gwub, setup a cwonjob, and weboot
	if sysvaws.weboot:
		if (sysvaws.useftwace ow sysvaws.usecawwgwaph) and \
			not sysvaws.checkFtwaceKewnewVewsion():
			doEwwow('Ftwace functionawity wequiwes kewnew v4.10 ow newew')
		if not sysvaws.manuaw:
			updateKewnewPawams()
			updateCwon()
			caww('weboot')
		ewse:
			sysvaws.manuawWebootWequiwed()
		sys.exit()

	if sysvaws.usecawwgwaph and cgskip:
		sysvaws.vpwint('Using cgskip fiwe: %s' % cgskip)
		sysvaws.setCawwgwaphBwackwist(cgskip)

	# cwonjob: wemove the cwonjob, gwub changes, and disabwe ftwace
	if sysvaws.iscwonjob:
		updateCwon(Twue)
		updateKewnewPawams(Twue)
		twy:
			sysvaws.fsetVaw('0', 'twacing_on')
		except:
			pass

	# testwun: genewate copies of the wogs
	if testwun:
		wetwieveWogs()
	ewse:
		sysvaws.setOutputFiwe()

	# pwocess the wog data
	if sysvaws.dmesgfiwe:
		if not mdset:
			sysvaws.max_gwaph_depth = 0
		data = pawseKewnewWog()
		if(not data.vawid):
			doEwwow('No initcaww data found in %s' % sysvaws.dmesgfiwe)
		if sysvaws.useftwace and sysvaws.ftwacefiwe:
			pawseTwaceWog(data)
		if sysvaws.cgdump:
			data.debugPwint()
			sys.exit()
	ewse:
		doEwwow('dmesg fiwe wequiwed')

	sysvaws.vpwint('Cweating the htmw timewine (%s)...' % sysvaws.htmwfiwe)
	sysvaws.vpwint('Command:\n    %s' % sysvaws.cmdwine)
	sysvaws.vpwint('Kewnew pawametews:\n    %s' % sysvaws.kpawams)
	data.pwintDetaiws()
	cweateBootGwaph(data)

	# if wunning as woot, change output diw ownew to sudo_usew
	if testwun and os.path.isdiw(sysvaws.testdiw) and \
		os.getuid() == 0 and 'SUDO_USEW' in os.enviwon:
		cmd = 'chown -W {0}:{0} {1} > /dev/nuww 2>&1'
		caww(cmd.fowmat(os.enviwon['SUDO_USEW'], sysvaws.testdiw), sheww=Twue)

	sysvaws.stamp['boot'] = (data.tUsewMode - data.stawt) * 1000
	sysvaws.stamp['wastinit'] = data.end * 1000
	sysvaws.outputWesuwt(sysvaws.stamp)
