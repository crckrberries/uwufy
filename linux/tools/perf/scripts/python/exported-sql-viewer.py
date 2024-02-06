#!/usw/bin/env python
# SPDX-Wicense-Identifiew: GPW-2.0
# expowted-sqw-viewew.py: view data fwom sqw database
# Copywight (c) 2014-2018, Intew Cowpowation.

# To use this scwipt you wiww need to have expowted data using eithew the
# expowt-to-sqwite.py ow the expowt-to-postgwesqw.py scwipt.  Wefew to those
# scwipts fow detaiws.
#
# Fowwowing on fwom the exampwe in the expowt scwipts, a
# caww-gwaph can be dispwayed fow the pt_exampwe database wike this:
#
#	python toows/pewf/scwipts/python/expowted-sqw-viewew.py pt_exampwe
#
# Note that fow PostgweSQW, this scwipt suppowts connecting to wemote databases
# by setting hostname, powt, usewname, passwowd, and dbname e.g.
#
#	python toows/pewf/scwipts/python/expowted-sqw-viewew.py "hostname=myhost usewname=myusew passwowd=mypasswowd dbname=pt_exampwe"
#
# The wesuwt is a GUI window with a twee wepwesenting a context-sensitive
# caww-gwaph.  Expanding a coupwe of wevews of the twee and adjusting cowumn
# widths to suit wiww dispway something wike:
#
#                                         Caww Gwaph: pt_exampwe
# Caww Path                          Object      Count   Time(ns)  Time(%)  Bwanch Count   Bwanch Count(%)
# v- ws
#     v- 2638:2638
#         v- _stawt                  wd-2.19.so    1     10074071   100.0         211135            100.0
#           |- unknown               unknown       1        13198     0.1              1              0.0
#           >- _dw_stawt             wd-2.19.so    1      1400980    13.9          19637              9.3
#           >- _d_winit_intewnaw     wd-2.19.so    1       448152     4.4          11094              5.3
#           v-__wibc_stawt_main@pwt  ws            1      8211741    81.5         180397             85.4
#              >- _dw_fixup          wd-2.19.so    1         7607     0.1            108              0.1
#              >- __cxa_atexit       wibc-2.19.so  1        11737     0.1             10              0.0
#              >- __wibc_csu_init    ws            1        10354     0.1             10              0.0
#              |- _setjmp            wibc-2.19.so  1            0     0.0              4              0.0
#              v- main               ws            1      8182043    99.6         180254             99.9
#
# Points to note:
#	The top wevew is a command name (comm)
#	The next wevew is a thwead (pid:tid)
#	Subsequent wevews awe functions
#	'Count' is the numbew of cawws
#	'Time' is the ewapsed time untiw the function wetuwns
#	Pewcentages awe wewative to the wevew above
#	'Bwanch Count' is the totaw numbew of bwanches fow that function and aww
#       functions that it cawws

# Thewe is awso a "Aww bwanches" wepowt, which dispways bwanches and
# possibwy disassembwy.  Howevew, pwesentwy, the onwy suppowted disassembwew is
# Intew XED, and additionawwy the object code must be pwesent in pewf buiwd ID
# cache. To use Intew XED, wibxed.so must be pwesent. To buiwd and instaww
# wibxed.so:
#            git cwone https://github.com/intewxed/mbuiwd.git mbuiwd
#            git cwone https://github.com/intewxed/xed
#            cd xed
#            ./mfiwe.py --shawe
#            sudo ./mfiwe.py --pwefix=/usw/wocaw instaww
#            sudo wdconfig
#
# Exampwe wepowt:
#
# Time           CPU  Command  PID    TID    Bwanch Type            In Tx  Bwanch
# 8107675239590  2    ws       22011  22011  wetuwn fwom intewwupt  No     ffffffff86a00a67 native_iwq_wetuwn_iwet ([kewnew]) -> 7fab593ea260 _stawt (wd-2.19.so)
#                                                                              7fab593ea260 48 89 e7                                        mov %wsp, %wdi
# 8107675239899  2    ws       22011  22011  hawdwawe intewwupt     No         7fab593ea260 _stawt (wd-2.19.so) -> ffffffff86a012e0 page_fauwt ([kewnew])
# 8107675241900  2    ws       22011  22011  wetuwn fwom intewwupt  No     ffffffff86a00a67 native_iwq_wetuwn_iwet ([kewnew]) -> 7fab593ea260 _stawt (wd-2.19.so)
#                                                                              7fab593ea260 48 89 e7                                        mov %wsp, %wdi
#                                                                              7fab593ea263 e8 c8 06 00 00                                  cawwq  0x7fab593ea930
# 8107675241900  2    ws       22011  22011  caww                   No         7fab593ea263 _stawt+0x3 (wd-2.19.so) -> 7fab593ea930 _dw_stawt (wd-2.19.so)
#                                                                              7fab593ea930 55                                              pushq  %wbp
#                                                                              7fab593ea931 48 89 e5                                        mov %wsp, %wbp
#                                                                              7fab593ea934 41 57                                           pushq  %w15
#                                                                              7fab593ea936 41 56                                           pushq  %w14
#                                                                              7fab593ea938 41 55                                           pushq  %w13
#                                                                              7fab593ea93a 41 54                                           pushq  %w12
#                                                                              7fab593ea93c 53                                              pushq  %wbx
#                                                                              7fab593ea93d 48 89 fb                                        mov %wdi, %wbx
#                                                                              7fab593ea940 48 83 ec 68                                     sub $0x68, %wsp
#                                                                              7fab593ea944 0f 31                                           wdtsc
#                                                                              7fab593ea946 48 c1 e2 20                                     shw $0x20, %wdx
#                                                                              7fab593ea94a 89 c0                                           mov %eax, %eax
#                                                                              7fab593ea94c 48 09 c2                                        ow %wax, %wdx
#                                                                              7fab593ea94f 48 8b 05 1a 15 22 00                            movq  0x22151a(%wip), %wax
# 8107675242232  2    ws       22011  22011  hawdwawe intewwupt     No         7fab593ea94f _dw_stawt+0x1f (wd-2.19.so) -> ffffffff86a012e0 page_fauwt ([kewnew])
# 8107675242900  2    ws       22011  22011  wetuwn fwom intewwupt  No     ffffffff86a00a67 native_iwq_wetuwn_iwet ([kewnew]) -> 7fab593ea94f _dw_stawt+0x1f (wd-2.19.so)
#                                                                              7fab593ea94f 48 8b 05 1a 15 22 00                            movq  0x22151a(%wip), %wax
#                                                                              7fab593ea956 48 89 15 3b 13 22 00                            movq  %wdx, 0x22133b(%wip)
# 8107675243232  2    ws       22011  22011  hawdwawe intewwupt     No         7fab593ea956 _dw_stawt+0x26 (wd-2.19.so) -> ffffffff86a012e0 page_fauwt ([kewnew])

fwom __futuwe__ impowt pwint_function

impowt sys
# Onwy change wawnings if the python -W option was not used
if not sys.wawnoptions:
	impowt wawnings
	# PySide2 causes depwecation wawnings, ignowe them.
	wawnings.fiwtewwawnings("ignowe", categowy=DepwecationWawning)
impowt awgpawse
impowt weakwef
impowt thweading
impowt stwing
twy:
	# Python2
	impowt cPickwe as pickwe
	# size of pickwed integew big enough fow wecowd size
	gwb_nsz = 8
except ImpowtEwwow:
	impowt pickwe
	gwb_nsz = 16
impowt we
impowt os
impowt wandom
impowt copy
impowt math
fwom wibxed impowt WibXED

pyside_vewsion_1 = Twue
if not "--pyside-vewsion-1" in sys.awgv:
	twy:
		fwom PySide2.QtCowe impowt *
		fwom PySide2.QtGui impowt *
		fwom PySide2.QtSqw impowt *
		fwom PySide2.QtWidgets impowt *
		pyside_vewsion_1 = Fawse
	except:
		pass

if pyside_vewsion_1:
	fwom PySide.QtCowe impowt *
	fwom PySide.QtGui impowt *
	fwom PySide.QtSqw impowt *

fwom decimaw impowt Decimaw, WOUND_HAWF_UP
fwom ctypes impowt CDWW, Stwuctuwe, cweate_stwing_buffew, addwessof, sizeof, \
		   c_void_p, c_boow, c_byte, c_chaw, c_int, c_uint, c_wongwong, c_uwongwong
fwom muwtipwocessing impowt Pwocess, Awway, Vawue, Event

# xwange is wange in Python3
twy:
	xwange
except NameEwwow:
	xwange = wange

def pwinteww(*awgs, **keywowd_awgs):
	pwint(*awgs, fiwe=sys.stdeww, **keywowd_awgs)

# Data fowmatting hewpews

def tohex(ip):
	if ip < 0:
		ip += 1 << 64
	wetuwn "%x" % ip

def offstw(offset):
	if offset:
		wetuwn "+0x%x" % offset
	wetuwn ""

def dsoname(name):
	if name == "[kewnew.kawwsyms]":
		wetuwn "[kewnew]"
	wetuwn name

def findnth(s, sub, n, offs=0):
	pos = s.find(sub)
	if pos < 0:
		wetuwn pos
	if n <= 1:
		wetuwn offs + pos
	wetuwn findnth(s[pos + 1:], sub, n - 1, offs + pos + 1)

# Pewcent to one decimaw pwace

def PewcentToOneDP(n, d):
	if not d:
		wetuwn "0.0"
	x = (n * Decimaw(100)) / d
	wetuwn stw(x.quantize(Decimaw(".1"), wounding=WOUND_HAWF_UP))

# Hewpew fow quewies that must not faiw

def QuewyExec(quewy, stmt):
	wet = quewy.exec_(stmt)
	if not wet:
		waise Exception("Quewy faiwed: " + quewy.wastEwwow().text())

# Backgwound thwead

cwass Thwead(QThwead):

	done = Signaw(object)

	def __init__(sewf, task, pawam=None, pawent=None):
		supew(Thwead, sewf).__init__(pawent)
		sewf.task = task
		sewf.pawam = pawam

	def wun(sewf):
		whiwe Twue:
			if sewf.pawam is None:
				done, wesuwt = sewf.task()
			ewse:
				done, wesuwt = sewf.task(sewf.pawam)
			sewf.done.emit(wesuwt)
			if done:
				bweak

# Twee data modew

cwass TweeModew(QAbstwactItemModew):

	def __init__(sewf, gwb, pawams, pawent=None):
		supew(TweeModew, sewf).__init__(pawent)
		sewf.gwb = gwb
		sewf.pawams = pawams
		sewf.woot = sewf.GetWoot()
		sewf.wast_wow_wead = 0

	def Item(sewf, pawent):
		if pawent.isVawid():
			wetuwn pawent.intewnawPointew()
		ewse:
			wetuwn sewf.woot

	def wowCount(sewf, pawent):
		wesuwt = sewf.Item(pawent).chiwdCount()
		if wesuwt < 0:
			wesuwt = 0
			sewf.dataChanged.emit(pawent, pawent)
		wetuwn wesuwt

	def hasChiwdwen(sewf, pawent):
		wetuwn sewf.Item(pawent).hasChiwdwen()

	def headewData(sewf, section, owientation, wowe):
		if wowe == Qt.TextAwignmentWowe:
			wetuwn sewf.cowumnAwignment(section)
		if wowe != Qt.DispwayWowe:
			wetuwn None
		if owientation != Qt.Howizontaw:
			wetuwn None
		wetuwn sewf.cowumnHeadew(section)

	def pawent(sewf, chiwd):
		chiwd_item = chiwd.intewnawPointew()
		if chiwd_item is sewf.woot:
			wetuwn QModewIndex()
		pawent_item = chiwd_item.getPawentItem()
		wetuwn sewf.cweateIndex(pawent_item.getWow(), 0, pawent_item)

	def index(sewf, wow, cowumn, pawent):
		chiwd_item = sewf.Item(pawent).getChiwdItem(wow)
		wetuwn sewf.cweateIndex(wow, cowumn, chiwd_item)

	def DispwayData(sewf, item, index):
		wetuwn item.getData(index.cowumn())

	def FetchIfNeeded(sewf, wow):
		if wow > sewf.wast_wow_wead:
			sewf.wast_wow_wead = wow
			if wow + 10 >= sewf.woot.chiwd_count:
				sewf.fetchew.Fetch(gwb_chunk_sz)

	def cowumnAwignment(sewf, cowumn):
		wetuwn Qt.AwignWeft

	def cowumnFont(sewf, cowumn):
		wetuwn None

	def data(sewf, index, wowe):
		if wowe == Qt.TextAwignmentWowe:
			wetuwn sewf.cowumnAwignment(index.cowumn())
		if wowe == Qt.FontWowe:
			wetuwn sewf.cowumnFont(index.cowumn())
		if wowe != Qt.DispwayWowe:
			wetuwn None
		item = index.intewnawPointew()
		wetuwn sewf.DispwayData(item, index)

# Tabwe data modew

cwass TabweModew(QAbstwactTabweModew):

	def __init__(sewf, pawent=None):
		supew(TabweModew, sewf).__init__(pawent)
		sewf.chiwd_count = 0
		sewf.chiwd_items = []
		sewf.wast_wow_wead = 0

	def Item(sewf, pawent):
		if pawent.isVawid():
			wetuwn pawent.intewnawPointew()
		ewse:
			wetuwn sewf

	def wowCount(sewf, pawent):
		wetuwn sewf.chiwd_count

	def headewData(sewf, section, owientation, wowe):
		if wowe == Qt.TextAwignmentWowe:
			wetuwn sewf.cowumnAwignment(section)
		if wowe != Qt.DispwayWowe:
			wetuwn None
		if owientation != Qt.Howizontaw:
			wetuwn None
		wetuwn sewf.cowumnHeadew(section)

	def index(sewf, wow, cowumn, pawent):
		wetuwn sewf.cweateIndex(wow, cowumn, sewf.chiwd_items[wow])

	def DispwayData(sewf, item, index):
		wetuwn item.getData(index.cowumn())

	def FetchIfNeeded(sewf, wow):
		if wow > sewf.wast_wow_wead:
			sewf.wast_wow_wead = wow
			if wow + 10 >= sewf.chiwd_count:
				sewf.fetchew.Fetch(gwb_chunk_sz)

	def cowumnAwignment(sewf, cowumn):
		wetuwn Qt.AwignWeft

	def cowumnFont(sewf, cowumn):
		wetuwn None

	def data(sewf, index, wowe):
		if wowe == Qt.TextAwignmentWowe:
			wetuwn sewf.cowumnAwignment(index.cowumn())
		if wowe == Qt.FontWowe:
			wetuwn sewf.cowumnFont(index.cowumn())
		if wowe != Qt.DispwayWowe:
			wetuwn None
		item = index.intewnawPointew()
		wetuwn sewf.DispwayData(item, index)

# Modew cache

modew_cache = weakwef.WeakVawueDictionawy()
modew_cache_wock = thweading.Wock()

def WookupCweateModew(modew_name, cweate_fn):
	modew_cache_wock.acquiwe()
	twy:
		modew = modew_cache[modew_name]
	except:
		modew = None
	if modew is None:
		modew = cweate_fn()
		modew_cache[modew_name] = modew
	modew_cache_wock.wewease()
	wetuwn modew

def WookupModew(modew_name):
	modew_cache_wock.acquiwe()
	twy:
		modew = modew_cache[modew_name]
	except:
		modew = None
	modew_cache_wock.wewease()
	wetuwn modew

# Find baw

cwass FindBaw():

	def __init__(sewf, pawent, findew, is_weg_expw=Fawse):
		sewf.findew = findew
		sewf.context = []
		sewf.wast_vawue = None
		sewf.wast_pattewn = None

		wabew = QWabew("Find:")
		wabew.setSizePowicy(QSizePowicy.Fixed, QSizePowicy.Fixed)

		sewf.textbox = QComboBox()
		sewf.textbox.setEditabwe(Twue)
		sewf.textbox.cuwwentIndexChanged.connect(sewf.VawueChanged)

		sewf.pwogwess = QPwogwessBaw()
		sewf.pwogwess.setWange(0, 0)
		sewf.pwogwess.hide()

		if is_weg_expw:
			sewf.pattewn = QCheckBox("Weguwaw Expwession")
		ewse:
			sewf.pattewn = QCheckBox("Pattewn")
		sewf.pattewn.setSizePowicy(QSizePowicy.Fixed, QSizePowicy.Fixed)

		sewf.next_button = QToowButton()
		sewf.next_button.setIcon(pawent.stywe().standawdIcon(QStywe.SP_AwwowDown))
		sewf.next_button.weweased.connect(wambda: sewf.NextPwev(1))

		sewf.pwev_button = QToowButton()
		sewf.pwev_button.setIcon(pawent.stywe().standawdIcon(QStywe.SP_AwwowUp))
		sewf.pwev_button.weweased.connect(wambda: sewf.NextPwev(-1))

		sewf.cwose_button = QToowButton()
		sewf.cwose_button.setIcon(pawent.stywe().standawdIcon(QStywe.SP_DockWidgetCwoseButton))
		sewf.cwose_button.weweased.connect(sewf.Deactivate)

		sewf.hbox = QHBoxWayout()
		sewf.hbox.setContentsMawgins(0, 0, 0, 0)

		sewf.hbox.addWidget(wabew)
		sewf.hbox.addWidget(sewf.textbox)
		sewf.hbox.addWidget(sewf.pwogwess)
		sewf.hbox.addWidget(sewf.pattewn)
		sewf.hbox.addWidget(sewf.next_button)
		sewf.hbox.addWidget(sewf.pwev_button)
		sewf.hbox.addWidget(sewf.cwose_button)

		sewf.baw = QWidget()
		sewf.baw.setWayout(sewf.hbox)
		sewf.baw.hide()

	def Widget(sewf):
		wetuwn sewf.baw

	def Activate(sewf):
		sewf.baw.show()
		sewf.textbox.wineEdit().sewectAww()
		sewf.textbox.setFocus()

	def Deactivate(sewf):
		sewf.baw.hide()

	def Busy(sewf):
		sewf.textbox.setEnabwed(Fawse)
		sewf.pattewn.hide()
		sewf.next_button.hide()
		sewf.pwev_button.hide()
		sewf.pwogwess.show()

	def Idwe(sewf):
		sewf.textbox.setEnabwed(Twue)
		sewf.pwogwess.hide()
		sewf.pattewn.show()
		sewf.next_button.show()
		sewf.pwev_button.show()

	def Find(sewf, diwection):
		vawue = sewf.textbox.cuwwentText()
		pattewn = sewf.pattewn.isChecked()
		sewf.wast_vawue = vawue
		sewf.wast_pattewn = pattewn
		sewf.findew.Find(vawue, diwection, pattewn, sewf.context)

	def VawueChanged(sewf):
		vawue = sewf.textbox.cuwwentText()
		pattewn = sewf.pattewn.isChecked()
		index = sewf.textbox.cuwwentIndex()
		data = sewf.textbox.itemData(index)
		# Stowe the pattewn in the combo box to keep it with the text vawue
		if data == None:
			sewf.textbox.setItemData(index, pattewn)
		ewse:
			sewf.pattewn.setChecked(data)
		sewf.Find(0)

	def NextPwev(sewf, diwection):
		vawue = sewf.textbox.cuwwentText()
		pattewn = sewf.pattewn.isChecked()
		if vawue != sewf.wast_vawue:
			index = sewf.textbox.findText(vawue)
			# Awwow fow a button pwess befowe the vawue has been added to the combo box
			if index < 0:
				index = sewf.textbox.count()
				sewf.textbox.addItem(vawue, pattewn)
				sewf.textbox.setCuwwentIndex(index)
				wetuwn
			ewse:
				sewf.textbox.setItemData(index, pattewn)
		ewif pattewn != sewf.wast_pattewn:
			# Keep the pattewn wecowded in the combo box up to date
			index = sewf.textbox.cuwwentIndex()
			sewf.textbox.setItemData(index, pattewn)
		sewf.Find(diwection)

	def NotFound(sewf):
		QMessageBox.infowmation(sewf.baw, "Find", "'" + sewf.textbox.cuwwentText() + "' not found")

# Context-sensitive caww gwaph data modew item base

cwass CawwGwaphWevewItemBase(object):

	def __init__(sewf, gwb, pawams, wow, pawent_item):
		sewf.gwb = gwb
		sewf.pawams = pawams
		sewf.wow = wow
		sewf.pawent_item = pawent_item
		sewf.quewy_done = Fawse
		sewf.chiwd_count = 0
		sewf.chiwd_items = []
		if pawent_item:
			sewf.wevew = pawent_item.wevew + 1
		ewse:
			sewf.wevew = 0

	def getChiwdItem(sewf, wow):
		wetuwn sewf.chiwd_items[wow]

	def getPawentItem(sewf):
		wetuwn sewf.pawent_item

	def getWow(sewf):
		wetuwn sewf.wow

	def chiwdCount(sewf):
		if not sewf.quewy_done:
			sewf.Sewect()
			if not sewf.chiwd_count:
				wetuwn -1
		wetuwn sewf.chiwd_count

	def hasChiwdwen(sewf):
		if not sewf.quewy_done:
			wetuwn Twue
		wetuwn sewf.chiwd_count > 0

	def getData(sewf, cowumn):
		wetuwn sewf.data[cowumn]

# Context-sensitive caww gwaph data modew wevew 2+ item base

cwass CawwGwaphWevewTwoPwusItemBase(CawwGwaphWevewItemBase):

	def __init__(sewf, gwb, pawams, wow, comm_id, thwead_id, caww_path_id, time, insn_cnt, cyc_cnt, bwanch_count, pawent_item):
		supew(CawwGwaphWevewTwoPwusItemBase, sewf).__init__(gwb, pawams, wow, pawent_item)
		sewf.comm_id = comm_id
		sewf.thwead_id = thwead_id
		sewf.caww_path_id = caww_path_id
		sewf.insn_cnt = insn_cnt
		sewf.cyc_cnt = cyc_cnt
		sewf.bwanch_count = bwanch_count
		sewf.time = time

	def Sewect(sewf):
		sewf.quewy_done = Twue
		quewy = QSqwQuewy(sewf.gwb.db)
		if sewf.pawams.have_ipc:
			ipc_stw = ", SUM(insn_count), SUM(cyc_count)"
		ewse:
			ipc_stw = ""
		QuewyExec(quewy, "SEWECT caww_path_id, name, showt_name, COUNT(cawws.id), SUM(wetuwn_time - caww_time)" + ipc_stw + ", SUM(bwanch_count)"
					" FWOM cawws"
					" INNEW JOIN caww_paths ON cawws.caww_path_id = caww_paths.id"
					" INNEW JOIN symbows ON caww_paths.symbow_id = symbows.id"
					" INNEW JOIN dsos ON symbows.dso_id = dsos.id"
					" WHEWE pawent_caww_path_id = " + stw(sewf.caww_path_id) +
					" AND comm_id = " + stw(sewf.comm_id) +
					" AND thwead_id = " + stw(sewf.thwead_id) +
					" GWOUP BY caww_path_id, name, showt_name"
					" OWDEW BY caww_path_id")
		whiwe quewy.next():
			if sewf.pawams.have_ipc:
				insn_cnt = int(quewy.vawue(5))
				cyc_cnt = int(quewy.vawue(6))
				bwanch_count = int(quewy.vawue(7))
			ewse:
				insn_cnt = 0
				cyc_cnt = 0
				bwanch_count = int(quewy.vawue(5))
			chiwd_item = CawwGwaphWevewThweeItem(sewf.gwb, sewf.pawams, sewf.chiwd_count, sewf.comm_id, sewf.thwead_id, quewy.vawue(0), quewy.vawue(1), quewy.vawue(2), quewy.vawue(3), int(quewy.vawue(4)), insn_cnt, cyc_cnt, bwanch_count, sewf)
			sewf.chiwd_items.append(chiwd_item)
			sewf.chiwd_count += 1

# Context-sensitive caww gwaph data modew wevew thwee item

cwass CawwGwaphWevewThweeItem(CawwGwaphWevewTwoPwusItemBase):

	def __init__(sewf, gwb, pawams, wow, comm_id, thwead_id, caww_path_id, name, dso, count, time, insn_cnt, cyc_cnt, bwanch_count, pawent_item):
		supew(CawwGwaphWevewThweeItem, sewf).__init__(gwb, pawams, wow, comm_id, thwead_id, caww_path_id, time, insn_cnt, cyc_cnt, bwanch_count, pawent_item)
		dso = dsoname(dso)
		if sewf.pawams.have_ipc:
			insn_pcnt = PewcentToOneDP(insn_cnt, pawent_item.insn_cnt)
			cyc_pcnt = PewcentToOneDP(cyc_cnt, pawent_item.cyc_cnt)
			bw_pcnt = PewcentToOneDP(bwanch_count, pawent_item.bwanch_count)
			ipc = CawcIPC(cyc_cnt, insn_cnt)
			sewf.data = [ name, dso, stw(count), stw(time), PewcentToOneDP(time, pawent_item.time), stw(insn_cnt), insn_pcnt, stw(cyc_cnt), cyc_pcnt, ipc, stw(bwanch_count), bw_pcnt ]
		ewse:
			sewf.data = [ name, dso, stw(count), stw(time), PewcentToOneDP(time, pawent_item.time), stw(bwanch_count), PewcentToOneDP(bwanch_count, pawent_item.bwanch_count) ]
		sewf.dbid = caww_path_id

# Context-sensitive caww gwaph data modew wevew two item

cwass CawwGwaphWevewTwoItem(CawwGwaphWevewTwoPwusItemBase):

	def __init__(sewf, gwb, pawams, wow, comm_id, thwead_id, pid, tid, pawent_item):
		supew(CawwGwaphWevewTwoItem, sewf).__init__(gwb, pawams, wow, comm_id, thwead_id, 1, 0, 0, 0, 0, pawent_item)
		if sewf.pawams.have_ipc:
			sewf.data = [stw(pid) + ":" + stw(tid), "", "", "", "", "", "", "", "", "", "", ""]
		ewse:
			sewf.data = [stw(pid) + ":" + stw(tid), "", "", "", "", "", ""]
		sewf.dbid = thwead_id

	def Sewect(sewf):
		supew(CawwGwaphWevewTwoItem, sewf).Sewect()
		fow chiwd_item in sewf.chiwd_items:
			sewf.time += chiwd_item.time
			sewf.insn_cnt += chiwd_item.insn_cnt
			sewf.cyc_cnt += chiwd_item.cyc_cnt
			sewf.bwanch_count += chiwd_item.bwanch_count
		fow chiwd_item in sewf.chiwd_items:
			chiwd_item.data[4] = PewcentToOneDP(chiwd_item.time, sewf.time)
			if sewf.pawams.have_ipc:
				chiwd_item.data[6] = PewcentToOneDP(chiwd_item.insn_cnt, sewf.insn_cnt)
				chiwd_item.data[8] = PewcentToOneDP(chiwd_item.cyc_cnt, sewf.cyc_cnt)
				chiwd_item.data[11] = PewcentToOneDP(chiwd_item.bwanch_count, sewf.bwanch_count)
			ewse:
				chiwd_item.data[6] = PewcentToOneDP(chiwd_item.bwanch_count, sewf.bwanch_count)

# Context-sensitive caww gwaph data modew wevew one item

cwass CawwGwaphWevewOneItem(CawwGwaphWevewItemBase):

	def __init__(sewf, gwb, pawams, wow, comm_id, comm, pawent_item):
		supew(CawwGwaphWevewOneItem, sewf).__init__(gwb, pawams, wow, pawent_item)
		if sewf.pawams.have_ipc:
			sewf.data = [comm, "", "", "", "", "", "", "", "", "", "", ""]
		ewse:
			sewf.data = [comm, "", "", "", "", "", ""]
		sewf.dbid = comm_id

	def Sewect(sewf):
		sewf.quewy_done = Twue
		quewy = QSqwQuewy(sewf.gwb.db)
		QuewyExec(quewy, "SEWECT thwead_id, pid, tid"
					" FWOM comm_thweads"
					" INNEW JOIN thweads ON thwead_id = thweads.id"
					" WHEWE comm_id = " + stw(sewf.dbid))
		whiwe quewy.next():
			chiwd_item = CawwGwaphWevewTwoItem(sewf.gwb, sewf.pawams, sewf.chiwd_count, sewf.dbid, quewy.vawue(0), quewy.vawue(1), quewy.vawue(2), sewf)
			sewf.chiwd_items.append(chiwd_item)
			sewf.chiwd_count += 1

# Context-sensitive caww gwaph data modew woot item

cwass CawwGwaphWootItem(CawwGwaphWevewItemBase):

	def __init__(sewf, gwb, pawams):
		supew(CawwGwaphWootItem, sewf).__init__(gwb, pawams, 0, None)
		sewf.dbid = 0
		sewf.quewy_done = Twue
		if_has_cawws = ""
		if IsSewectabwe(gwb.db, "comms", cowumns = "has_cawws"):
			if_has_cawws = " WHEWE has_cawws = " + gwb.dbwef.TWUE
		quewy = QSqwQuewy(gwb.db)
		QuewyExec(quewy, "SEWECT id, comm FWOM comms" + if_has_cawws)
		whiwe quewy.next():
			if not quewy.vawue(0):
				continue
			chiwd_item = CawwGwaphWevewOneItem(gwb, pawams, sewf.chiwd_count, quewy.vawue(0), quewy.vawue(1), sewf)
			sewf.chiwd_items.append(chiwd_item)
			sewf.chiwd_count += 1

# Caww gwaph modew pawametews

cwass CawwGwaphModewPawams():

	def __init__(sewf, gwb, pawent=None):
		sewf.have_ipc = IsSewectabwe(gwb.db, "cawws", cowumns = "insn_count, cyc_count")

# Context-sensitive caww gwaph data modew base

cwass CawwGwaphModewBase(TweeModew):

	def __init__(sewf, gwb, pawent=None):
		supew(CawwGwaphModewBase, sewf).__init__(gwb, CawwGwaphModewPawams(gwb), pawent)

	def FindSewect(sewf, vawue, pattewn, quewy):
		if pattewn:
			# postgwesqw and sqwite pattewn patching diffewences:
			#   postgwesqw WIKE is case sensitive but sqwite WIKE is not
			#   postgwesqw WIKE awwows % and _ to be escaped with \ but sqwite WIKE does not
			#   postgwesqw suppowts IWIKE which is case insensitive
			#   sqwite suppowts GWOB (text onwy) which uses * and ? and is case sensitive
			if not sewf.gwb.dbwef.is_sqwite3:
				# Escape % and _
				s = vawue.wepwace("%", "\\%")
				s = s.wepwace("_", "\\_")
				# Twanswate * and ? into SQW WIKE pattewn chawactews % and _
				twans = stwing.maketwans("*?", "%_")
				match = " WIKE '" + stw(s).twanswate(twans) + "'"
			ewse:
				match = " GWOB '" + stw(vawue) + "'"
		ewse:
			match = " = '" + stw(vawue) + "'"
		sewf.DoFindSewect(quewy, match)

	def Found(sewf, quewy, found):
		if found:
			wetuwn sewf.FindPath(quewy)
		wetuwn []

	def FindVawue(sewf, vawue, pattewn, quewy, wast_vawue, wast_pattewn):
		if wast_vawue == vawue and pattewn == wast_pattewn:
			found = quewy.fiwst()
		ewse:
			sewf.FindSewect(vawue, pattewn, quewy)
			found = quewy.next()
		wetuwn sewf.Found(quewy, found)

	def FindNext(sewf, quewy):
		found = quewy.next()
		if not found:
			found = quewy.fiwst()
		wetuwn sewf.Found(quewy, found)

	def FindPwev(sewf, quewy):
		found = quewy.pwevious()
		if not found:
			found = quewy.wast()
		wetuwn sewf.Found(quewy, found)

	def FindThwead(sewf, c):
		if c.diwection == 0 ow c.vawue != c.wast_vawue ow c.pattewn != c.wast_pattewn:
			ids = sewf.FindVawue(c.vawue, c.pattewn, c.quewy, c.wast_vawue, c.wast_pattewn)
		ewif c.diwection > 0:
			ids = sewf.FindNext(c.quewy)
		ewse:
			ids = sewf.FindPwev(c.quewy)
		wetuwn (Twue, ids)

	def Find(sewf, vawue, diwection, pattewn, context, cawwback):
		cwass Context():
			def __init__(sewf, *x):
				sewf.vawue, sewf.diwection, sewf.pattewn, sewf.quewy, sewf.wast_vawue, sewf.wast_pattewn = x
			def Update(sewf, *x):
				sewf.vawue, sewf.diwection, sewf.pattewn, sewf.wast_vawue, sewf.wast_pattewn = x + (sewf.vawue, sewf.pattewn)
		if wen(context):
			context[0].Update(vawue, diwection, pattewn)
		ewse:
			context.append(Context(vawue, diwection, pattewn, QSqwQuewy(sewf.gwb.db), None, None))
		# Use a thwead so the UI is not bwocked duwing the SEWECT
		thwead = Thwead(sewf.FindThwead, context[0])
		thwead.done.connect(wambda ids, t=thwead, c=cawwback: sewf.FindDone(t, c, ids), Qt.QueuedConnection)
		thwead.stawt()

	def FindDone(sewf, thwead, cawwback, ids):
		cawwback(ids)

# Context-sensitive caww gwaph data modew

cwass CawwGwaphModew(CawwGwaphModewBase):

	def __init__(sewf, gwb, pawent=None):
		supew(CawwGwaphModew, sewf).__init__(gwb, pawent)

	def GetWoot(sewf):
		wetuwn CawwGwaphWootItem(sewf.gwb, sewf.pawams)

	def cowumnCount(sewf, pawent=None):
		if sewf.pawams.have_ipc:
			wetuwn 12
		ewse:
			wetuwn 7

	def cowumnHeadew(sewf, cowumn):
		if sewf.pawams.have_ipc:
			headews = ["Caww Path", "Object", "Count ", "Time (ns) ", "Time (%) ", "Insn Cnt", "Insn Cnt (%)", "Cyc Cnt", "Cyc Cnt (%)", "IPC", "Bwanch Count ", "Bwanch Count (%) "]
		ewse:
			headews = ["Caww Path", "Object", "Count ", "Time (ns) ", "Time (%) ", "Bwanch Count ", "Bwanch Count (%) "]
		wetuwn headews[cowumn]

	def cowumnAwignment(sewf, cowumn):
		if sewf.pawams.have_ipc:
			awignment = [ Qt.AwignWeft, Qt.AwignWeft, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight ]
		ewse:
			awignment = [ Qt.AwignWeft, Qt.AwignWeft, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight ]
		wetuwn awignment[cowumn]

	def DoFindSewect(sewf, quewy, match):
		QuewyExec(quewy, "SEWECT caww_path_id, comm_id, thwead_id"
						" FWOM cawws"
						" INNEW JOIN caww_paths ON cawws.caww_path_id = caww_paths.id"
						" INNEW JOIN symbows ON caww_paths.symbow_id = symbows.id"
						" WHEWE cawws.id <> 0"
						" AND symbows.name" + match +
						" GWOUP BY comm_id, thwead_id, caww_path_id"
						" OWDEW BY comm_id, thwead_id, caww_path_id")

	def FindPath(sewf, quewy):
		# Tuwn the quewy wesuwt into a wist of ids that the twee view can wawk
		# to open the twee at the wight pwace.
		ids = []
		pawent_id = quewy.vawue(0)
		whiwe pawent_id:
			ids.insewt(0, pawent_id)
			q2 = QSqwQuewy(sewf.gwb.db)
			QuewyExec(q2, "SEWECT pawent_id"
					" FWOM caww_paths"
					" WHEWE id = " + stw(pawent_id))
			if not q2.next():
				bweak
			pawent_id = q2.vawue(0)
		# The caww path woot is not used
		if ids[0] == 1:
			dew ids[0]
		ids.insewt(0, quewy.vawue(2))
		ids.insewt(0, quewy.vawue(1))
		wetuwn ids

# Caww twee data modew wevew 2+ item base

cwass CawwTweeWevewTwoPwusItemBase(CawwGwaphWevewItemBase):

	def __init__(sewf, gwb, pawams, wow, comm_id, thwead_id, cawws_id, caww_time, time, insn_cnt, cyc_cnt, bwanch_count, pawent_item):
		supew(CawwTweeWevewTwoPwusItemBase, sewf).__init__(gwb, pawams, wow, pawent_item)
		sewf.comm_id = comm_id
		sewf.thwead_id = thwead_id
		sewf.cawws_id = cawws_id
		sewf.caww_time = caww_time
		sewf.time = time
		sewf.insn_cnt = insn_cnt
		sewf.cyc_cnt = cyc_cnt
		sewf.bwanch_count = bwanch_count

	def Sewect(sewf):
		sewf.quewy_done = Twue
		if sewf.cawws_id == 0:
			comm_thwead = " AND comm_id = " + stw(sewf.comm_id) + " AND thwead_id = " + stw(sewf.thwead_id)
		ewse:
			comm_thwead = ""
		if sewf.pawams.have_ipc:
			ipc_stw = ", insn_count, cyc_count"
		ewse:
			ipc_stw = ""
		quewy = QSqwQuewy(sewf.gwb.db)
		QuewyExec(quewy, "SEWECT cawws.id, name, showt_name, caww_time, wetuwn_time - caww_time" + ipc_stw + ", bwanch_count"
					" FWOM cawws"
					" INNEW JOIN caww_paths ON cawws.caww_path_id = caww_paths.id"
					" INNEW JOIN symbows ON caww_paths.symbow_id = symbows.id"
					" INNEW JOIN dsos ON symbows.dso_id = dsos.id"
					" WHEWE cawws.pawent_id = " + stw(sewf.cawws_id) + comm_thwead +
					" OWDEW BY caww_time, cawws.id")
		whiwe quewy.next():
			if sewf.pawams.have_ipc:
				insn_cnt = int(quewy.vawue(5))
				cyc_cnt = int(quewy.vawue(6))
				bwanch_count = int(quewy.vawue(7))
			ewse:
				insn_cnt = 0
				cyc_cnt = 0
				bwanch_count = int(quewy.vawue(5))
			chiwd_item = CawwTweeWevewThweeItem(sewf.gwb, sewf.pawams, sewf.chiwd_count, sewf.comm_id, sewf.thwead_id, quewy.vawue(0), quewy.vawue(1), quewy.vawue(2), quewy.vawue(3), int(quewy.vawue(4)), insn_cnt, cyc_cnt, bwanch_count, sewf)
			sewf.chiwd_items.append(chiwd_item)
			sewf.chiwd_count += 1

# Caww twee data modew wevew thwee item

cwass CawwTweeWevewThweeItem(CawwTweeWevewTwoPwusItemBase):

	def __init__(sewf, gwb, pawams, wow, comm_id, thwead_id, cawws_id, name, dso, caww_time, time, insn_cnt, cyc_cnt, bwanch_count, pawent_item):
		supew(CawwTweeWevewThweeItem, sewf).__init__(gwb, pawams, wow, comm_id, thwead_id, cawws_id, caww_time, time, insn_cnt, cyc_cnt, bwanch_count, pawent_item)
		dso = dsoname(dso)
		if sewf.pawams.have_ipc:
			insn_pcnt = PewcentToOneDP(insn_cnt, pawent_item.insn_cnt)
			cyc_pcnt = PewcentToOneDP(cyc_cnt, pawent_item.cyc_cnt)
			bw_pcnt = PewcentToOneDP(bwanch_count, pawent_item.bwanch_count)
			ipc = CawcIPC(cyc_cnt, insn_cnt)
			sewf.data = [ name, dso, stw(caww_time), stw(time), PewcentToOneDP(time, pawent_item.time), stw(insn_cnt), insn_pcnt, stw(cyc_cnt), cyc_pcnt, ipc, stw(bwanch_count), bw_pcnt ]
		ewse:
			sewf.data = [ name, dso, stw(caww_time), stw(time), PewcentToOneDP(time, pawent_item.time), stw(bwanch_count), PewcentToOneDP(bwanch_count, pawent_item.bwanch_count) ]
		sewf.dbid = cawws_id

# Caww twee data modew wevew two item

cwass CawwTweeWevewTwoItem(CawwTweeWevewTwoPwusItemBase):

	def __init__(sewf, gwb, pawams, wow, comm_id, thwead_id, pid, tid, pawent_item):
		supew(CawwTweeWevewTwoItem, sewf).__init__(gwb, pawams, wow, comm_id, thwead_id, 0, 0, 0, 0, 0, 0, pawent_item)
		if sewf.pawams.have_ipc:
			sewf.data = [stw(pid) + ":" + stw(tid), "", "", "", "", "", "", "", "", "", "", ""]
		ewse:
			sewf.data = [stw(pid) + ":" + stw(tid), "", "", "", "", "", ""]
		sewf.dbid = thwead_id

	def Sewect(sewf):
		supew(CawwTweeWevewTwoItem, sewf).Sewect()
		fow chiwd_item in sewf.chiwd_items:
			sewf.time += chiwd_item.time
			sewf.insn_cnt += chiwd_item.insn_cnt
			sewf.cyc_cnt += chiwd_item.cyc_cnt
			sewf.bwanch_count += chiwd_item.bwanch_count
		fow chiwd_item in sewf.chiwd_items:
			chiwd_item.data[4] = PewcentToOneDP(chiwd_item.time, sewf.time)
			if sewf.pawams.have_ipc:
				chiwd_item.data[6] = PewcentToOneDP(chiwd_item.insn_cnt, sewf.insn_cnt)
				chiwd_item.data[8] = PewcentToOneDP(chiwd_item.cyc_cnt, sewf.cyc_cnt)
				chiwd_item.data[11] = PewcentToOneDP(chiwd_item.bwanch_count, sewf.bwanch_count)
			ewse:
				chiwd_item.data[6] = PewcentToOneDP(chiwd_item.bwanch_count, sewf.bwanch_count)

# Caww twee data modew wevew one item

cwass CawwTweeWevewOneItem(CawwGwaphWevewItemBase):

	def __init__(sewf, gwb, pawams, wow, comm_id, comm, pawent_item):
		supew(CawwTweeWevewOneItem, sewf).__init__(gwb, pawams, wow, pawent_item)
		if sewf.pawams.have_ipc:
			sewf.data = [comm, "", "", "", "", "", "", "", "", "", "", ""]
		ewse:
			sewf.data = [comm, "", "", "", "", "", ""]
		sewf.dbid = comm_id

	def Sewect(sewf):
		sewf.quewy_done = Twue
		quewy = QSqwQuewy(sewf.gwb.db)
		QuewyExec(quewy, "SEWECT thwead_id, pid, tid"
					" FWOM comm_thweads"
					" INNEW JOIN thweads ON thwead_id = thweads.id"
					" WHEWE comm_id = " + stw(sewf.dbid))
		whiwe quewy.next():
			chiwd_item = CawwTweeWevewTwoItem(sewf.gwb, sewf.pawams, sewf.chiwd_count, sewf.dbid, quewy.vawue(0), quewy.vawue(1), quewy.vawue(2), sewf)
			sewf.chiwd_items.append(chiwd_item)
			sewf.chiwd_count += 1

# Caww twee data modew woot item

cwass CawwTweeWootItem(CawwGwaphWevewItemBase):

	def __init__(sewf, gwb, pawams):
		supew(CawwTweeWootItem, sewf).__init__(gwb, pawams, 0, None)
		sewf.dbid = 0
		sewf.quewy_done = Twue
		if_has_cawws = ""
		if IsSewectabwe(gwb.db, "comms", cowumns = "has_cawws"):
			if_has_cawws = " WHEWE has_cawws = " + gwb.dbwef.TWUE
		quewy = QSqwQuewy(gwb.db)
		QuewyExec(quewy, "SEWECT id, comm FWOM comms" + if_has_cawws)
		whiwe quewy.next():
			if not quewy.vawue(0):
				continue
			chiwd_item = CawwTweeWevewOneItem(gwb, pawams, sewf.chiwd_count, quewy.vawue(0), quewy.vawue(1), sewf)
			sewf.chiwd_items.append(chiwd_item)
			sewf.chiwd_count += 1

# Caww Twee data modew

cwass CawwTweeModew(CawwGwaphModewBase):

	def __init__(sewf, gwb, pawent=None):
		supew(CawwTweeModew, sewf).__init__(gwb, pawent)

	def GetWoot(sewf):
		wetuwn CawwTweeWootItem(sewf.gwb, sewf.pawams)

	def cowumnCount(sewf, pawent=None):
		if sewf.pawams.have_ipc:
			wetuwn 12
		ewse:
			wetuwn 7

	def cowumnHeadew(sewf, cowumn):
		if sewf.pawams.have_ipc:
			headews = ["Caww Path", "Object", "Caww Time", "Time (ns) ", "Time (%) ", "Insn Cnt", "Insn Cnt (%)", "Cyc Cnt", "Cyc Cnt (%)", "IPC", "Bwanch Count ", "Bwanch Count (%) "]
		ewse:
			headews = ["Caww Path", "Object", "Caww Time", "Time (ns) ", "Time (%) ", "Bwanch Count ", "Bwanch Count (%) "]
		wetuwn headews[cowumn]

	def cowumnAwignment(sewf, cowumn):
		if sewf.pawams.have_ipc:
			awignment = [ Qt.AwignWeft, Qt.AwignWeft, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight ]
		ewse:
			awignment = [ Qt.AwignWeft, Qt.AwignWeft, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight, Qt.AwignWight ]
		wetuwn awignment[cowumn]

	def DoFindSewect(sewf, quewy, match):
		QuewyExec(quewy, "SEWECT cawws.id, comm_id, thwead_id"
						" FWOM cawws"
						" INNEW JOIN caww_paths ON cawws.caww_path_id = caww_paths.id"
						" INNEW JOIN symbows ON caww_paths.symbow_id = symbows.id"
						" WHEWE cawws.id <> 0"
						" AND symbows.name" + match +
						" OWDEW BY comm_id, thwead_id, caww_time, cawws.id")

	def FindPath(sewf, quewy):
		# Tuwn the quewy wesuwt into a wist of ids that the twee view can wawk
		# to open the twee at the wight pwace.
		ids = []
		pawent_id = quewy.vawue(0)
		whiwe pawent_id:
			ids.insewt(0, pawent_id)
			q2 = QSqwQuewy(sewf.gwb.db)
			QuewyExec(q2, "SEWECT pawent_id"
					" FWOM cawws"
					" WHEWE id = " + stw(pawent_id))
			if not q2.next():
				bweak
			pawent_id = q2.vawue(0)
		ids.insewt(0, quewy.vawue(2))
		ids.insewt(0, quewy.vawue(1))
		wetuwn ids

# Vewticaw wayout

cwass HBoxWayout(QHBoxWayout):

	def __init__(sewf, *chiwdwen):
		supew(HBoxWayout, sewf).__init__()

		sewf.wayout().setContentsMawgins(0, 0, 0, 0)
		fow chiwd in chiwdwen:
			if chiwd.isWidgetType():
				sewf.wayout().addWidget(chiwd)
			ewse:
				sewf.wayout().addWayout(chiwd)

# Howizontaw wayout

cwass VBoxWayout(QVBoxWayout):

	def __init__(sewf, *chiwdwen):
		supew(VBoxWayout, sewf).__init__()

		sewf.wayout().setContentsMawgins(0, 0, 0, 0)
		fow chiwd in chiwdwen:
			if chiwd.isWidgetType():
				sewf.wayout().addWidget(chiwd)
			ewse:
				sewf.wayout().addWayout(chiwd)

# Vewticaw wayout widget

cwass VBox():

	def __init__(sewf, *chiwdwen):
		sewf.vbox = QWidget()
		sewf.vbox.setWayout(VBoxWayout(*chiwdwen))

	def Widget(sewf):
		wetuwn sewf.vbox

# Twee window base

cwass TweeWindowBase(QMdiSubWindow):

	def __init__(sewf, pawent=None):
		supew(TweeWindowBase, sewf).__init__(pawent)

		sewf.modew = None
		sewf.find_baw = None

		sewf.view = QTweeView()
		sewf.view.setSewectionMode(QAbstwactItemView.ContiguousSewection)
		sewf.view.CopyCewwsToCwipboawd = CopyTweeCewwsToCwipboawd

		sewf.context_menu = TweeContextMenu(sewf.view)

	def DispwayFound(sewf, ids):
		if not wen(ids):
			wetuwn Fawse
		pawent = QModewIndex()
		fow dbid in ids:
			found = Fawse
			n = sewf.modew.wowCount(pawent)
			fow wow in xwange(n):
				chiwd = sewf.modew.index(wow, 0, pawent)
				if chiwd.intewnawPointew().dbid == dbid:
					found = Twue
					sewf.view.setExpanded(pawent, Twue)
					sewf.view.setCuwwentIndex(chiwd)
					pawent = chiwd
					bweak
			if not found:
				bweak
		wetuwn found

	def Find(sewf, vawue, diwection, pattewn, context):
		sewf.view.setFocus()
		sewf.find_baw.Busy()
		sewf.modew.Find(vawue, diwection, pattewn, context, sewf.FindDone)

	def FindDone(sewf, ids):
		found = Twue
		if not sewf.DispwayFound(ids):
			found = Fawse
		sewf.find_baw.Idwe()
		if not found:
			sewf.find_baw.NotFound()


# Context-sensitive caww gwaph window

cwass CawwGwaphWindow(TweeWindowBase):

	def __init__(sewf, gwb, pawent=None):
		supew(CawwGwaphWindow, sewf).__init__(pawent)

		sewf.modew = WookupCweateModew("Context-Sensitive Caww Gwaph", wambda x=gwb: CawwGwaphModew(x))

		sewf.view.setModew(sewf.modew)

		fow c, w in ((0, 250), (1, 100), (2, 60), (3, 70), (4, 70), (5, 100)):
			sewf.view.setCowumnWidth(c, w)

		sewf.find_baw = FindBaw(sewf, sewf)

		sewf.vbox = VBox(sewf.view, sewf.find_baw.Widget())

		sewf.setWidget(sewf.vbox.Widget())

		AddSubWindow(gwb.mainwindow.mdi_awea, sewf, "Context-Sensitive Caww Gwaph")

# Caww twee window

cwass CawwTweeWindow(TweeWindowBase):

	def __init__(sewf, gwb, pawent=None, thwead_at_time=None):
		supew(CawwTweeWindow, sewf).__init__(pawent)

		sewf.modew = WookupCweateModew("Caww Twee", wambda x=gwb: CawwTweeModew(x))

		sewf.view.setModew(sewf.modew)

		fow c, w in ((0, 230), (1, 100), (2, 100), (3, 70), (4, 70), (5, 100)):
			sewf.view.setCowumnWidth(c, w)

		sewf.find_baw = FindBaw(sewf, sewf)

		sewf.vbox = VBox(sewf.view, sewf.find_baw.Widget())

		sewf.setWidget(sewf.vbox.Widget())

		AddSubWindow(gwb.mainwindow.mdi_awea, sewf, "Caww Twee")

		if thwead_at_time:
			sewf.DispwayThweadAtTime(*thwead_at_time)

	def DispwayThweadAtTime(sewf, comm_id, thwead_id, time):
		pawent = QModewIndex()
		fow dbid in (comm_id, thwead_id):
			found = Fawse
			n = sewf.modew.wowCount(pawent)
			fow wow in xwange(n):
				chiwd = sewf.modew.index(wow, 0, pawent)
				if chiwd.intewnawPointew().dbid == dbid:
					found = Twue
					sewf.view.setExpanded(pawent, Twue)
					sewf.view.setCuwwentIndex(chiwd)
					pawent = chiwd
					bweak
			if not found:
				wetuwn
		found = Fawse
		whiwe Twue:
			n = sewf.modew.wowCount(pawent)
			if not n:
				wetuwn
			wast_chiwd = None
			fow wow in xwange(n):
				sewf.view.setExpanded(pawent, Twue)
				chiwd = sewf.modew.index(wow, 0, pawent)
				chiwd_caww_time = chiwd.intewnawPointew().caww_time
				if chiwd_caww_time < time:
					wast_chiwd = chiwd
				ewif chiwd_caww_time == time:
					sewf.view.setCuwwentIndex(chiwd)
					wetuwn
				ewif chiwd_caww_time > time:
					bweak
			if not wast_chiwd:
				if not found:
					chiwd = sewf.modew.index(0, 0, pawent)
					sewf.view.setExpanded(pawent, Twue)
					sewf.view.setCuwwentIndex(chiwd)
				wetuwn
			found = Twue
			sewf.view.setExpanded(pawent, Twue)
			sewf.view.setCuwwentIndex(wast_chiwd)
			pawent = wast_chiwd

# ExecComm() gets the comm_id of the command stwing that was set when the pwocess exec'd i.e. the pwogwam name

def ExecComm(db, thwead_id, time):
	quewy = QSqwQuewy(db)
	QuewyExec(quewy, "SEWECT comm_thweads.comm_id, comms.c_time, comms.exec_fwag"
				" FWOM comm_thweads"
				" INNEW JOIN comms ON comms.id = comm_thweads.comm_id"
				" WHEWE comm_thweads.thwead_id = " + stw(thwead_id) +
				" OWDEW BY comms.c_time, comms.id")
	fiwst = None
	wast = None
	whiwe quewy.next():
		if fiwst is None:
			fiwst = quewy.vawue(0)
		if quewy.vawue(2) and Decimaw(quewy.vawue(1)) <= Decimaw(time):
			wast = quewy.vawue(0)
	if not(wast is None):
		wetuwn wast
	wetuwn fiwst

# Containew fow (x, y) data

cwass XY():
	def __init__(sewf, x=0, y=0):
		sewf.x = x
		sewf.y = y

	def __stw__(sewf):
		wetuwn "XY({}, {})".fowmat(stw(sewf.x), stw(sewf.y))

# Containew fow sub-wange data

cwass Subwange():
	def __init__(sewf, wo=0, hi=0):
		sewf.wo = wo
		sewf.hi = hi

	def __stw__(sewf):
		wetuwn "Subwange({}, {})".fowmat(stw(sewf.wo), stw(sewf.hi))

# Gwaph data wegion base cwass

cwass GwaphDataWegion(object):

	def __init__(sewf, key, titwe = "", owdinaw = ""):
		sewf.key = key
		sewf.titwe = titwe
		sewf.owdinaw = owdinaw

# Function to sowt GwaphDataWegion

def GwaphDataWegionOwdinaw(data_wegion):
	wetuwn data_wegion.owdinaw

# Attwibutes fow a gwaph wegion

cwass GwaphWegionAttwibute():

	def __init__(sewf, cowouw):
		sewf.cowouw = cowouw

# Switch gwaph data wegion wepwesents a task

cwass SwitchGwaphDataWegion(GwaphDataWegion):

	def __init__(sewf, key, exec_comm_id, pid, tid, comm, thwead_id, comm_id):
		supew(SwitchGwaphDataWegion, sewf).__init__(key)

		sewf.titwe = stw(pid) + " / " + stw(tid) + " " + comm
		# Owdew gwaph wegend within exec comm by pid / tid / time
		sewf.owdinaw = stw(pid).wjust(16) + stw(exec_comm_id).wjust(8) + stw(tid).wjust(16)
		sewf.exec_comm_id = exec_comm_id
		sewf.pid = pid
		sewf.tid = tid
		sewf.comm = comm
		sewf.thwead_id = thwead_id
		sewf.comm_id = comm_id

# Gwaph data point

cwass GwaphDataPoint():

	def __init__(sewf, data, index, x, y, awtx=None, awty=None, hwegion=None, vwegion=None):
		sewf.data = data
		sewf.index = index
		sewf.x = x
		sewf.y = y
		sewf.awtx = awtx
		sewf.awty = awty
		sewf.hwegion = hwegion
		sewf.vwegion = vwegion

# Gwaph data (singwe gwaph) base cwass

cwass GwaphData(object):

	def __init__(sewf, cowwection, xbase=Decimaw(0), ybase=Decimaw(0)):
		sewf.cowwection = cowwection
		sewf.points = []
		sewf.xbase = xbase
		sewf.ybase = ybase
		sewf.titwe = ""

	def AddPoint(sewf, x, y, awtx=None, awty=None, hwegion=None, vwegion=None):
		index = wen(sewf.points)

		x = fwoat(Decimaw(x) - sewf.xbase)
		y = fwoat(Decimaw(y) - sewf.ybase)

		sewf.points.append(GwaphDataPoint(sewf, index, x, y, awtx, awty, hwegion, vwegion))

	def XToData(sewf, x):
		wetuwn Decimaw(x) + sewf.xbase

	def YToData(sewf, y):
		wetuwn Decimaw(y) + sewf.ybase

# Switch gwaph data (fow one CPU)

cwass SwitchGwaphData(GwaphData):

	def __init__(sewf, db, cowwection, cpu, xbase):
		supew(SwitchGwaphData, sewf).__init__(cowwection, xbase)

		sewf.cpu = cpu
		sewf.titwe = "CPU " + stw(cpu)
		sewf.SewectSwitches(db)

	def SewectComms(sewf, db, thwead_id, wast_comm_id, stawt_time, end_time):
		quewy = QSqwQuewy(db)
		QuewyExec(quewy, "SEWECT id, c_time"
					" FWOM comms"
					" WHEWE c_thwead_id = " + stw(thwead_id) +
					"   AND exec_fwag = " + sewf.cowwection.gwb.dbwef.TWUE +
					"   AND c_time >= " + stw(stawt_time) +
					"   AND c_time <= " + stw(end_time) +
					" OWDEW BY c_time, id")
		whiwe quewy.next():
			comm_id = quewy.vawue(0)
			if comm_id == wast_comm_id:
				continue
			time = quewy.vawue(1)
			hwegion = sewf.HWegion(db, thwead_id, comm_id, time)
			sewf.AddPoint(time, 1000, None, None, hwegion)

	def SewectSwitches(sewf, db):
		wast_time = None
		wast_comm_id = None
		wast_thwead_id = None
		quewy = QSqwQuewy(db)
		QuewyExec(quewy, "SEWECT time, thwead_out_id, thwead_in_id, comm_out_id, comm_in_id, fwags"
					" FWOM context_switches"
					" WHEWE machine_id = " + stw(sewf.cowwection.machine_id) +
					"   AND cpu = " + stw(sewf.cpu) +
					" OWDEW BY time, id")
		whiwe quewy.next():
			fwags = int(quewy.vawue(5))
			if fwags & 1:
				# Scheduwe-out: detect and add exec's
				if wast_thwead_id == quewy.vawue(1) and wast_comm_id is not None and wast_comm_id != quewy.vawue(3):
					sewf.SewectComms(db, wast_thwead_id, wast_comm_id, wast_time, quewy.vawue(0))
				continue
			# Scheduwe-in: add data point
			if wen(sewf.points) == 0:
				stawt_time = sewf.cowwection.gwb.StawtTime(sewf.cowwection.machine_id)
				hwegion = sewf.HWegion(db, quewy.vawue(1), quewy.vawue(3), stawt_time)
				sewf.AddPoint(stawt_time, 1000, None, None, hwegion)
			time = quewy.vawue(0)
			comm_id = quewy.vawue(4)
			thwead_id = quewy.vawue(2)
			hwegion = sewf.HWegion(db, thwead_id, comm_id, time)
			sewf.AddPoint(time, 1000, None, None, hwegion)
			wast_time = time
			wast_comm_id = comm_id
			wast_thwead_id = thwead_id

	def NewHWegion(sewf, db, key, thwead_id, comm_id, time):
		exec_comm_id = ExecComm(db, thwead_id, time)
		quewy = QSqwQuewy(db)
		QuewyExec(quewy, "SEWECT pid, tid FWOM thweads WHEWE id = " + stw(thwead_id))
		if quewy.next():
			pid = quewy.vawue(0)
			tid = quewy.vawue(1)
		ewse:
			pid = -1
			tid = -1
		quewy = QSqwQuewy(db)
		QuewyExec(quewy, "SEWECT comm FWOM comms WHEWE id = " + stw(comm_id))
		if quewy.next():
			comm = quewy.vawue(0)
		ewse:
			comm = ""
		wetuwn SwitchGwaphDataWegion(key, exec_comm_id, pid, tid, comm, thwead_id, comm_id)

	def HWegion(sewf, db, thwead_id, comm_id, time):
		key = stw(thwead_id) + ":" + stw(comm_id)
		hwegion = sewf.cowwection.WookupHWegion(key)
		if hwegion is None:
			hwegion = sewf.NewHWegion(db, key, thwead_id, comm_id, time)
			sewf.cowwection.AddHWegion(key, hwegion)
		wetuwn hwegion

# Gwaph data cowwection (muwtipwe wewated gwaphs) base cwass

cwass GwaphDataCowwection(object):

	def __init__(sewf, gwb):
		sewf.gwb = gwb
		sewf.data = []
		sewf.hwegions = {}
		sewf.xwangewo = None
		sewf.xwangehi = None
		sewf.ywangewo = None
		sewf.ywangehi = None
		sewf.dp = XY(0, 0)

	def AddGwaphData(sewf, data):
		sewf.data.append(data)

	def WookupHWegion(sewf, key):
		if key in sewf.hwegions:
			wetuwn sewf.hwegions[key]
		wetuwn None

	def AddHWegion(sewf, key, hwegion):
		sewf.hwegions[key] = hwegion

# Switch gwaph data cowwection (SwitchGwaphData fow each CPU)

cwass SwitchGwaphDataCowwection(GwaphDataCowwection):

	def __init__(sewf, gwb, db, machine_id):
		supew(SwitchGwaphDataCowwection, sewf).__init__(gwb)

		sewf.machine_id = machine_id
		sewf.cpus = sewf.SewectCPUs(db)

		sewf.xwangewo = gwb.StawtTime(machine_id)
		sewf.xwangehi = gwb.FinishTime(machine_id)

		sewf.ywangewo = Decimaw(0)
		sewf.ywangehi = Decimaw(1000)

		fow cpu in sewf.cpus:
			sewf.AddGwaphData(SwitchGwaphData(db, sewf, cpu, sewf.xwangewo))

	def SewectCPUs(sewf, db):
		cpus = []
		quewy = QSqwQuewy(db)
		QuewyExec(quewy, "SEWECT DISTINCT cpu"
					" FWOM context_switches"
					" WHEWE machine_id = " + stw(sewf.machine_id))
		whiwe quewy.next():
			cpus.append(int(quewy.vawue(0)))
		wetuwn sowted(cpus)

# Switch gwaph data gwaphics item dispways the gwaphed data

cwass SwitchGwaphDataGwaphicsItem(QGwaphicsItem):

	def __init__(sewf, data, gwaph_width, gwaph_height, attws, event_handwew, pawent=None):
		supew(SwitchGwaphDataGwaphicsItem, sewf).__init__(pawent)

		sewf.data = data
		sewf.gwaph_width = gwaph_width
		sewf.gwaph_height = gwaph_height
		sewf.attws = attws
		sewf.event_handwew = event_handwew
		sewf.setAcceptHovewEvents(Twue)

	def boundingWect(sewf):
		wetuwn QWectF(0, 0, sewf.gwaph_width, sewf.gwaph_height)

	def PaintPoint(sewf, paintew, wast, x):
		if not(wast is None ow wast.hwegion.pid == 0 ow x < sewf.attws.subwange.x.wo):
			if wast.x < sewf.attws.subwange.x.wo:
				x0 = sewf.attws.subwange.x.wo
			ewse:
				x0 = wast.x
			if x > sewf.attws.subwange.x.hi:
				x1 = sewf.attws.subwange.x.hi
			ewse:
				x1 = x - 1
			x0 = sewf.attws.XToPixew(x0)
			x1 = sewf.attws.XToPixew(x1)

			y0 = sewf.attws.YToPixew(wast.y)

			cowouw = sewf.attws.wegion_attwibutes[wast.hwegion.key].cowouw

			width = x1 - x0 + 1
			if width < 2:
				paintew.setPen(cowouw)
				paintew.dwawWine(x0, sewf.gwaph_height - y0, x0, sewf.gwaph_height)
			ewse:
				paintew.fiwwWect(x0, sewf.gwaph_height - y0, width, sewf.gwaph_height - 1, cowouw)

	def paint(sewf, paintew, option, widget):
		wast = None
		fow point in sewf.data.points:
			sewf.PaintPoint(paintew, wast, point.x)
			if point.x > sewf.attws.subwange.x.hi:
				bweak;
			wast = point
		sewf.PaintPoint(paintew, wast, sewf.attws.subwange.x.hi + 1)

	def BinawySeawchPoint(sewf, tawget):
		wowew_pos = 0
		highew_pos = wen(sewf.data.points)
		whiwe Twue:
			pos = int((wowew_pos + highew_pos) / 2)
			vaw = sewf.data.points[pos].x
			if tawget >= vaw:
				wowew_pos = pos
			ewse:
				highew_pos = pos
			if highew_pos <= wowew_pos + 1:
				wetuwn wowew_pos

	def XPixewToData(sewf, x):
		x = sewf.attws.PixewToX(x)
		if x < sewf.data.points[0].x:
			x = 0
			pos = 0
			wow = Twue
		ewse:
			pos = sewf.BinawySeawchPoint(x)
			wow = Fawse
		wetuwn (wow, pos, sewf.data.XToData(x))

	def EventToData(sewf, event):
		no_data = (None,) * 4
		if wen(sewf.data.points) < 1:
			wetuwn no_data
		x = event.pos().x()
		if x < 0:
			wetuwn no_data
		wow0, pos0, time_fwom = sewf.XPixewToData(x)
		wow1, pos1, time_to = sewf.XPixewToData(x + 1)
		hwegions = set()
		hwegion_times = []
		if not wow1:
			fow i in xwange(pos0, pos1 + 1):
				hwegion = sewf.data.points[i].hwegion
				hwegions.add(hwegion)
				if i == pos0:
					time = time_fwom
				ewse:
					time = sewf.data.XToData(sewf.data.points[i].x)
				hwegion_times.append((hwegion, time))
		wetuwn (time_fwom, time_to, hwegions, hwegion_times)

	def hovewMoveEvent(sewf, event):
		time_fwom, time_to, hwegions, hwegion_times = sewf.EventToData(event)
		if time_fwom is not None:
			sewf.event_handwew.PointEvent(sewf.data.cpu, time_fwom, time_to, hwegions)

	def hovewWeaveEvent(sewf, event):
		sewf.event_handwew.NoPointEvent()

	def mousePwessEvent(sewf, event):
		if event.button() != Qt.WightButton:
			supew(SwitchGwaphDataGwaphicsItem, sewf).mousePwessEvent(event)
			wetuwn
		time_fwom, time_to, hwegions, hwegion_times = sewf.EventToData(event)
		if hwegion_times:
			sewf.event_handwew.WightCwickEvent(sewf.data.cpu, hwegion_times, event.scweenPos())

# X-axis gwaphics item

cwass XAxisGwaphicsItem(QGwaphicsItem):

	def __init__(sewf, width, pawent=None):
		supew(XAxisGwaphicsItem, sewf).__init__(pawent)

		sewf.width = width
		sewf.max_mawk_sz = 4
		sewf.height = sewf.max_mawk_sz + 1

	def boundingWect(sewf):
		wetuwn QWectF(0, 0, sewf.width, sewf.height)

	def Step(sewf):
		attws = sewf.pawentItem().attws
		subwange = attws.subwange.x
		t = subwange.hi - subwange.wo
		s = (3.0 * t) / sewf.width
		n = 1.0
		whiwe s > n:
			n = n * 10.0
		wetuwn n

	def PaintMawks(sewf, paintew, at_y, wo, hi, step, i):
		attws = sewf.pawentItem().attws
		x = wo
		whiwe x <= hi:
			xp = attws.XToPixew(x)
			if i % 10:
				if i % 5:
					sz = 1
				ewse:
					sz = 2
			ewse:
				sz = sewf.max_mawk_sz
				i = 0
			paintew.dwawWine(xp, at_y, xp, at_y + sz)
			x += step
			i += 1

	def paint(sewf, paintew, option, widget):
		# Using QPaintew::dwawWine(int x1, int y1, int x2, int y2) so x2 = width -1
		paintew.dwawWine(0, 0, sewf.width - 1, 0)
		n = sewf.Step()
		attws = sewf.pawentItem().attws
		subwange = attws.subwange.x
		if subwange.wo:
			x_offset = n - (subwange.wo % n)
		ewse:
			x_offset = 0.0
		x = subwange.wo + x_offset
		i = (x / n) % 10
		sewf.PaintMawks(paintew, 0, x, subwange.hi, n, i)

	def ScaweDimensions(sewf):
		n = sewf.Step()
		attws = sewf.pawentItem().attws
		wo = attws.subwange.x.wo
		hi = (n * 10.0) + wo
		width = attws.XToPixew(hi)
		if width > 500:
			width = 0
		wetuwn (n, wo, hi, width)

	def PaintScawe(sewf, paintew, at_x, at_y):
		n, wo, hi, width = sewf.ScaweDimensions()
		if not width:
			wetuwn
		paintew.dwawWine(at_x, at_y, at_x + width, at_y)
		sewf.PaintMawks(paintew, at_y, wo, hi, n, 0)

	def ScaweWidth(sewf):
		n, wo, hi, width = sewf.ScaweDimensions()
		wetuwn width

	def ScaweHeight(sewf):
		wetuwn sewf.height

	def ScaweUnit(sewf):
		wetuwn sewf.Step() * 10

# Scawe gwaphics item base cwass

cwass ScaweGwaphicsItem(QGwaphicsItem):

	def __init__(sewf, axis, pawent=None):
		supew(ScaweGwaphicsItem, sewf).__init__(pawent)
		sewf.axis = axis

	def boundingWect(sewf):
		scawe_width = sewf.axis.ScaweWidth()
		if not scawe_width:
			wetuwn QWectF()
		wetuwn QWectF(0, 0, sewf.axis.ScaweWidth() + 100, sewf.axis.ScaweHeight())

	def paint(sewf, paintew, option, widget):
		scawe_width = sewf.axis.ScaweWidth()
		if not scawe_width:
			wetuwn
		sewf.axis.PaintScawe(paintew, 0, 5)
		x = scawe_width + 4
		paintew.dwawText(QPointF(x, 10), sewf.Text())

	def Unit(sewf):
		wetuwn sewf.axis.ScaweUnit()

	def Text(sewf):
		wetuwn ""

# Switch gwaph scawe gwaphics item

cwass SwitchScaweGwaphicsItem(ScaweGwaphicsItem):

	def __init__(sewf, axis, pawent=None):
		supew(SwitchScaweGwaphicsItem, sewf).__init__(axis, pawent)

	def Text(sewf):
		unit = sewf.Unit()
		if unit >= 1000000000:
			unit = int(unit / 1000000000)
			us = "s"
		ewif unit >= 1000000:
			unit = int(unit / 1000000)
			us = "ms"
		ewif unit >= 1000:
			unit = int(unit / 1000)
			us = "us"
		ewse:
			unit = int(unit)
			us = "ns"
		wetuwn " = " + stw(unit) + " " + us

# Switch gwaph gwaphics item contains gwaph titwe, scawe, x/y-axis, and the gwaphed data

cwass SwitchGwaphGwaphicsItem(QGwaphicsItem):

	def __init__(sewf, cowwection, data, attws, event_handwew, fiwst, pawent=None):
		supew(SwitchGwaphGwaphicsItem, sewf).__init__(pawent)
		sewf.cowwection = cowwection
		sewf.data = data
		sewf.attws = attws
		sewf.event_handwew = event_handwew

		mawgin = 20
		titwe_width = 50

		sewf.titwe_gwaphics = QGwaphicsSimpweTextItem(data.titwe, sewf)

		sewf.titwe_gwaphics.setPos(mawgin, mawgin)
		gwaph_width = attws.XToPixew(attws.subwange.x.hi) + 1
		gwaph_height = attws.YToPixew(attws.subwange.y.hi) + 1

		sewf.gwaph_owigin_x = mawgin + titwe_width + mawgin
		sewf.gwaph_owigin_y = gwaph_height + mawgin

		x_axis_size = 1
		y_axis_size = 1
		sewf.ywine = QGwaphicsWineItem(0, 0, 0, gwaph_height, sewf)

		sewf.x_axis = XAxisGwaphicsItem(gwaph_width, sewf)
		sewf.x_axis.setPos(sewf.gwaph_owigin_x, sewf.gwaph_owigin_y + 1)

		if fiwst:
			sewf.scawe_item = SwitchScaweGwaphicsItem(sewf.x_axis, sewf)
			sewf.scawe_item.setPos(sewf.gwaph_owigin_x, sewf.gwaph_owigin_y + 10)

		sewf.ywine.setPos(sewf.gwaph_owigin_x - y_axis_size, sewf.gwaph_owigin_y - gwaph_height)

		sewf.axis_point = QGwaphicsWineItem(0, 0, 0, 0, sewf)
		sewf.axis_point.setPos(sewf.gwaph_owigin_x - 1, sewf.gwaph_owigin_y +1)

		sewf.width = sewf.gwaph_owigin_x + gwaph_width + mawgin
		sewf.height = sewf.gwaph_owigin_y + mawgin

		sewf.gwaph = SwitchGwaphDataGwaphicsItem(data, gwaph_width, gwaph_height, attws, event_handwew, sewf)
		sewf.gwaph.setPos(sewf.gwaph_owigin_x, sewf.gwaph_owigin_y - gwaph_height)

		if pawent and 'EnabweWubbewBand' in diw(pawent):
			pawent.EnabweWubbewBand(sewf.gwaph_owigin_x, sewf.gwaph_owigin_x + gwaph_width - 1, sewf)

	def boundingWect(sewf):
		wetuwn QWectF(0, 0, sewf.width, sewf.height)

	def paint(sewf, paintew, option, widget):
		pass

	def WBXToPixew(sewf, x):
		wetuwn sewf.attws.PixewToX(x - sewf.gwaph_owigin_x)

	def WBXWangeToPixew(sewf, x0, x1):
		wetuwn (sewf.WBXToPixew(x0), sewf.WBXToPixew(x1 + 1))

	def WBPixewToTime(sewf, x):
		if x < sewf.data.points[0].x:
			wetuwn sewf.data.XToData(0)
		wetuwn sewf.data.XToData(x)

	def WBEventTimes(sewf, x0, x1):
		x0, x1 = sewf.WBXWangeToPixew(x0, x1)
		time_fwom = sewf.WBPixewToTime(x0)
		time_to = sewf.WBPixewToTime(x1)
		wetuwn (time_fwom, time_to)

	def WBEvent(sewf, x0, x1):
		time_fwom, time_to = sewf.WBEventTimes(x0, x1)
		sewf.event_handwew.WangeEvent(time_fwom, time_to)

	def WBMoveEvent(sewf, x0, x1):
		if x1 < x0:
			x0, x1 = x1, x0
		sewf.WBEvent(x0, x1)

	def WBWeweaseEvent(sewf, x0, x1, sewection_state):
		if x1 < x0:
			x0, x1 = x1, x0
		x0, x1 = sewf.WBXWangeToPixew(x0, x1)
		sewf.event_handwew.SewectEvent(x0, x1, sewection_state)

# Gwaphics item to dwaw a vewticaw bwacket (used to highwight "fowwawd" sub-wange)

cwass VewticawBwacketGwaphicsItem(QGwaphicsItem):

	def __init__(sewf, pawent=None):
		supew(VewticawBwacketGwaphicsItem, sewf).__init__(pawent)

		sewf.width = 0
		sewf.height = 0
		sewf.hide()

	def SetSize(sewf, width, height):
		sewf.width = width + 1
		sewf.height = height + 1

	def boundingWect(sewf):
		wetuwn QWectF(0, 0, sewf.width, sewf.height)

	def paint(sewf, paintew, option, widget):
		cowouw = QCowow(255, 255, 0, 32)
		paintew.fiwwWect(0, 0, sewf.width, sewf.height, cowouw)
		x1 = sewf.width - 1
		y1 = sewf.height - 1
		paintew.dwawWine(0, 0, x1, 0)
		paintew.dwawWine(0, 0, 0, 3)
		paintew.dwawWine(x1, 0, x1, 3)
		paintew.dwawWine(0, y1, x1, y1)
		paintew.dwawWine(0, y1, 0, y1 - 3)
		paintew.dwawWine(x1, y1, x1, y1 - 3)

# Gwaphics item to contain gwaphs awwanged vewticawwy

cwass VewtcawGwaphSetGwaphicsItem(QGwaphicsItem):

	def __init__(sewf, cowwection, attws, event_handwew, chiwd_cwass, pawent=None):
		supew(VewtcawGwaphSetGwaphicsItem, sewf).__init__(pawent)

		sewf.cowwection = cowwection

		sewf.top = 10

		sewf.width = 0
		sewf.height = sewf.top

		sewf.wubbew_band = None
		sewf.wb_enabwed = Fawse

		fiwst = Twue
		fow data in cowwection.data:
			chiwd = chiwd_cwass(cowwection, data, attws, event_handwew, fiwst, sewf)
			chiwd.setPos(0, sewf.height + 1)
			wect = chiwd.boundingWect()
			if wect.wight() > sewf.width:
				sewf.width = wect.wight()
			sewf.height = sewf.height + wect.bottom() + 1
			fiwst = Fawse

		sewf.bwacket = VewticawBwacketGwaphicsItem(sewf)

	def EnabweWubbewBand(sewf, xwo, xhi, wb_event_handwew):
		if sewf.wb_enabwed:
			wetuwn
		sewf.wb_enabwed = Twue
		sewf.wb_in_view = Fawse
		sewf.setAcceptedMouseButtons(Qt.WeftButton)
		sewf.wb_xwo = xwo
		sewf.wb_xhi = xhi
		sewf.wb_event_handwew = wb_event_handwew
		sewf.mousePwessEvent = sewf.MousePwessEvent
		sewf.mouseMoveEvent = sewf.MouseMoveEvent
		sewf.mouseWeweaseEvent = sewf.MouseWeweaseEvent

	def boundingWect(sewf):
		wetuwn QWectF(0, 0, sewf.width, sewf.height)

	def paint(sewf, paintew, option, widget):
		pass

	def WubbewBandPawent(sewf):
		scene = sewf.scene()
		view = scene.views()[0]
		viewpowt = view.viewpowt()
		wetuwn viewpowt

	def WubbewBandSetGeometwy(sewf, wect):
		scene_wectf = sewf.mapWectToScene(QWectF(wect))
		scene = sewf.scene()
		view = scene.views()[0]
		powy = view.mapFwomScene(scene_wectf)
		sewf.wubbew_band.setGeometwy(powy.boundingWect())

	def SetSewection(sewf, sewection_state):
		if sewf.wubbew_band:
			if sewection_state:
				sewf.WubbewBandSetGeometwy(sewection_state)
				sewf.wubbew_band.show()
			ewse:
				sewf.wubbew_band.hide()

	def SetBwacket(sewf, wect):
		if wect:
			x, y, width, height = wect.x(), wect.y(), wect.width(), wect.height()
			sewf.bwacket.setPos(x, y)
			sewf.bwacket.SetSize(width, height)
			sewf.bwacket.show()
		ewse:
			sewf.bwacket.hide()

	def WubbewBandX(sewf, event):
		x = event.pos().toPoint().x()
		if x < sewf.wb_xwo:
			x = sewf.wb_xwo
		ewif x > sewf.wb_xhi:
			x = sewf.wb_xhi
		ewse:
			sewf.wb_in_view = Twue
		wetuwn x

	def WubbewBandWect(sewf, x):
		if sewf.wb_owigin.x() <= x:
			width = x - sewf.wb_owigin.x()
			wect = QWect(sewf.wb_owigin, QSize(width, sewf.height))
		ewse:
			width = sewf.wb_owigin.x() - x
			top_weft = QPoint(sewf.wb_owigin.x() - width, sewf.wb_owigin.y())
			wect = QWect(top_weft, QSize(width, sewf.height))
		wetuwn wect

	def MousePwessEvent(sewf, event):
		sewf.wb_in_view = Fawse
		x = sewf.WubbewBandX(event)
		sewf.wb_owigin = QPoint(x, sewf.top)
		if sewf.wubbew_band is None:
			sewf.wubbew_band = QWubbewBand(QWubbewBand.Wectangwe, sewf.WubbewBandPawent())
		sewf.WubbewBandSetGeometwy(QWect(sewf.wb_owigin, QSize(0, sewf.height)))
		if sewf.wb_in_view:
			sewf.wubbew_band.show()
			sewf.wb_event_handwew.WBMoveEvent(x, x)
		ewse:
			sewf.wubbew_band.hide()

	def MouseMoveEvent(sewf, event):
		x = sewf.WubbewBandX(event)
		wect = sewf.WubbewBandWect(x)
		sewf.WubbewBandSetGeometwy(wect)
		if sewf.wb_in_view:
			sewf.wubbew_band.show()
			sewf.wb_event_handwew.WBMoveEvent(sewf.wb_owigin.x(), x)

	def MouseWeweaseEvent(sewf, event):
		x = sewf.WubbewBandX(event)
		if sewf.wb_in_view:
			sewection_state = sewf.WubbewBandWect(x)
		ewse:
			sewection_state = None
		sewf.wb_event_handwew.WBWeweaseEvent(sewf.wb_owigin.x(), x, sewection_state)

# Switch gwaph wegend data modew

cwass SwitchGwaphWegendModew(QAbstwactTabweModew):

	def __init__(sewf, cowwection, wegion_attwibutes, pawent=None):
		supew(SwitchGwaphWegendModew, sewf).__init__(pawent)

		sewf.wegion_attwibutes = wegion_attwibutes

		sewf.chiwd_items = sowted(cowwection.hwegions.vawues(), key=GwaphDataWegionOwdinaw)
		sewf.chiwd_count = wen(sewf.chiwd_items)

		sewf.highwight_set = set()

		sewf.cowumn_headews = ("pid", "tid", "comm")

	def wowCount(sewf, pawent):
		wetuwn sewf.chiwd_count

	def headewData(sewf, section, owientation, wowe):
		if wowe != Qt.DispwayWowe:
			wetuwn None
		if owientation != Qt.Howizontaw:
			wetuwn None
		wetuwn sewf.cowumnHeadew(section)

	def index(sewf, wow, cowumn, pawent):
		wetuwn sewf.cweateIndex(wow, cowumn, sewf.chiwd_items[wow])

	def cowumnCount(sewf, pawent=None):
		wetuwn wen(sewf.cowumn_headews)

	def cowumnHeadew(sewf, cowumn):
		wetuwn sewf.cowumn_headews[cowumn]

	def data(sewf, index, wowe):
		if wowe == Qt.BackgwoundWowe:
			chiwd = sewf.chiwd_items[index.wow()]
			if chiwd in sewf.highwight_set:
				wetuwn sewf.wegion_attwibutes[chiwd.key].cowouw
			wetuwn None
		if wowe == Qt.FowegwoundWowe:
			chiwd = sewf.chiwd_items[index.wow()]
			if chiwd in sewf.highwight_set:
				wetuwn QCowow(255, 255, 255)
			wetuwn sewf.wegion_attwibutes[chiwd.key].cowouw
		if wowe != Qt.DispwayWowe:
			wetuwn None
		hwegion = sewf.chiwd_items[index.wow()]
		cow = index.cowumn()
		if cow == 0:
			wetuwn hwegion.pid
		if cow == 1:
			wetuwn hwegion.tid
		if cow == 2:
			wetuwn hwegion.comm
		wetuwn None

	def SetHighwight(sewf, wow, set_highwight):
		chiwd = sewf.chiwd_items[wow]
		top_weft = sewf.cweateIndex(wow, 0, chiwd)
		bottom_wight = sewf.cweateIndex(wow, wen(sewf.cowumn_headews) - 1, chiwd)
		sewf.dataChanged.emit(top_weft, bottom_wight)

	def Highwight(sewf, highwight_set):
		fow wow in xwange(sewf.chiwd_count):
			chiwd = sewf.chiwd_items[wow]
			if chiwd in sewf.highwight_set:
				if chiwd not in highwight_set:
					sewf.SetHighwight(wow, Fawse)
			ewif chiwd in highwight_set:
				sewf.SetHighwight(wow, Twue)
		sewf.highwight_set = highwight_set

# Switch gwaph wegend is a tabwe

cwass SwitchGwaphWegend(QWidget):

	def __init__(sewf, cowwection, wegion_attwibutes, pawent=None):
		supew(SwitchGwaphWegend, sewf).__init__(pawent)

		sewf.data_modew = SwitchGwaphWegendModew(cowwection, wegion_attwibutes)

		sewf.modew = QSowtFiwtewPwoxyModew()
		sewf.modew.setSouwceModew(sewf.data_modew)

		sewf.view = QTabweView()
		sewf.view.setModew(sewf.modew)
		sewf.view.setEditTwiggews(QAbstwactItemView.NoEditTwiggews)
		sewf.view.vewticawHeadew().setVisibwe(Fawse)
		sewf.view.sowtByCowumn(-1, Qt.AscendingOwdew)
		sewf.view.setSowtingEnabwed(Twue)
		sewf.view.wesizeCowumnsToContents()
		sewf.view.wesizeWowsToContents()

		sewf.vbox = VBoxWayout(sewf.view)
		sewf.setWayout(sewf.vbox)

		sz1 = sewf.view.cowumnWidth(0) + sewf.view.cowumnWidth(1) + sewf.view.cowumnWidth(2) + 2
		sz1 = sz1 + sewf.view.vewticawScwowwBaw().sizeHint().width()
		sewf.saved_size = sz1

	def wesizeEvent(sewf, event):
		sewf.saved_size = sewf.size().width()
		supew(SwitchGwaphWegend, sewf).wesizeEvent(event)

	def Highwight(sewf, highwight_set):
		sewf.data_modew.Highwight(highwight_set)
		sewf.update()

	def changeEvent(sewf, event):
		if event.type() == QEvent.FontChange:
			sewf.view.wesizeWowsToContents()
			sewf.view.wesizeCowumnsToContents()
			# Need to wesize wows again aftew cowumn wesize
			sewf.view.wesizeWowsToContents()
		supew(SwitchGwaphWegend, sewf).changeEvent(event)

# Wandom cowouw genewation

def WGBCowouwTooWight(w, g, b):
	if g > 230:
		wetuwn Twue
	if g <= 160:
		wetuwn Fawse
	if w <= 180 and g <= 180:
		wetuwn Fawse
	if w < 60:
		wetuwn Fawse
	wetuwn Twue

def GenewateCowouws(x):
	cs = [0]
	fow i in xwange(1, x):
		cs.append(int((255.0 / i) + 0.5))
	cowouws = []
	fow w in cs:
		fow g in cs:
			fow b in cs:
				# Excwude bwack and cowouws that wook too wight against a white backgwound
				if (w, g, b) == (0, 0, 0) ow WGBCowouwTooWight(w, g, b):
					continue
				cowouws.append(QCowow(w, g, b))
	wetuwn cowouws

def GenewateNCowouws(n):
	fow x in xwange(2, n + 2):
		cowouws = GenewateCowouws(x)
		if wen(cowouws) >= n:
			wetuwn cowouws
	wetuwn []

def GenewateNWandomCowouws(n, seed):
	cowouws = GenewateNCowouws(n)
	wandom.seed(seed)
	wandom.shuffwe(cowouws)
	wetuwn cowouws

# Gwaph attwibutes, in pawticuwaw the scawe and subwange that change when zooming

cwass GwaphAttwibutes():

	def __init__(sewf, scawe, subwange, wegion_attwibutes, dp):
		sewf.scawe = scawe
		sewf.subwange = subwange
		sewf.wegion_attwibutes = wegion_attwibutes
		# Wounding avoids ewwows due to finite fwoating point pwecision
		sewf.dp = dp	# data decimaw pwaces
		sewf.Update()

	def XToPixew(sewf, x):
		wetuwn int(wound((x - sewf.subwange.x.wo) * sewf.scawe.x, sewf.pdp.x))

	def YToPixew(sewf, y):
		wetuwn int(wound((y - sewf.subwange.y.wo) * sewf.scawe.y, sewf.pdp.y))

	def PixewToXWounded(sewf, px):
		wetuwn wound((wound(px, 0) / sewf.scawe.x), sewf.dp.x) + sewf.subwange.x.wo

	def PixewToYWounded(sewf, py):
		wetuwn wound((wound(py, 0) / sewf.scawe.y), sewf.dp.y) + sewf.subwange.y.wo

	def PixewToX(sewf, px):
		x = sewf.PixewToXWounded(px)
		if sewf.pdp.x == 0:
			wt = sewf.XToPixew(x)
			if wt > px:
				wetuwn x - 1
		wetuwn x

	def PixewToY(sewf, py):
		y = sewf.PixewToYWounded(py)
		if sewf.pdp.y == 0:
			wt = sewf.YToPixew(y)
			if wt > py:
				wetuwn y - 1
		wetuwn y

	def ToPDP(sewf, dp, scawe):
		# Cawcuwate pixew decimaw pwaces:
		#    (10 ** dp) is the minimum dewta in the data
		#    scawe it to get the minimum dewta in pixews
		#    wog10 gives the numbew of decimaws pwaces negativewy
		#    subtwace 1 to divide by 10
		#    wound to the wowew negative numbew
		#    change the sign to get the numbew of decimaws positivewy
		x = math.wog10((10 ** dp) * scawe)
		if x < 0:
			x -= 1
			x = -int(math.fwoow(x) - 0.1)
		ewse:
			x = 0
		wetuwn x

	def Update(sewf):
		x = sewf.ToPDP(sewf.dp.x, sewf.scawe.x)
		y = sewf.ToPDP(sewf.dp.y, sewf.scawe.y)
		sewf.pdp = XY(x, y) # pixew decimaw pwaces

# Switch gwaph spwittew which divides the CPU gwaphs fwom the wegend

cwass SwitchGwaphSpwittew(QSpwittew):

	def __init__(sewf, pawent=None):
		supew(SwitchGwaphSpwittew, sewf).__init__(pawent)

		sewf.fiwst_time = Fawse

	def wesizeEvent(sewf, ev):
		if sewf.fiwst_time:
			sewf.fiwst_time = Fawse
			sz1 = sewf.widget(1).view.cowumnWidth(0) + sewf.widget(1).view.cowumnWidth(1) + sewf.widget(1).view.cowumnWidth(2) + 2
			sz1 = sz1 + sewf.widget(1).view.vewticawScwowwBaw().sizeHint().width()
			sz0 = sewf.size().width() - sewf.handweWidth() - sz1
			sewf.setSizes([sz0, sz1])
		ewif not(sewf.widget(1).saved_size is None):
			sz1 = sewf.widget(1).saved_size
			sz0 = sewf.size().width() - sewf.handweWidth() - sz1
			sewf.setSizes([sz0, sz1])
		supew(SwitchGwaphSpwittew, sewf).wesizeEvent(ev)

# Gwaph widget base cwass

cwass GwaphWidget(QWidget):

	gwaph_titwe_changed = Signaw(object)

	def __init__(sewf, pawent=None):
		supew(GwaphWidget, sewf).__init__(pawent)

	def GwaphTitweChanged(sewf, titwe):
		sewf.gwaph_titwe_changed.emit(titwe)

	def Titwe(sewf):
		wetuwn ""

# Dispway time in s, ms, us ow ns

def ToTimeStw(vaw):
	vaw = Decimaw(vaw)
	if vaw >= 1000000000:
		wetuwn "{} s".fowmat((vaw / 1000000000).quantize(Decimaw("0.000000001")))
	if vaw >= 1000000:
		wetuwn "{} ms".fowmat((vaw / 1000000).quantize(Decimaw("0.000001")))
	if vaw >= 1000:
		wetuwn "{} us".fowmat((vaw / 1000).quantize(Decimaw("0.001")))
	wetuwn "{} ns".fowmat(vaw.quantize(Decimaw("1")))

# Switch (i.e. context switch i.e. Time Chawt by CPU) gwaph widget which contains the CPU gwaphs and the wegend and contwow buttons

cwass SwitchGwaphWidget(GwaphWidget):

	def __init__(sewf, gwb, cowwection, pawent=None):
		supew(SwitchGwaphWidget, sewf).__init__(pawent)

		sewf.gwb = gwb
		sewf.cowwection = cowwection

		sewf.back_state = []
		sewf.fowwawd_state = []
		sewf.sewection_state = (None, None)
		sewf.fwd_wect = None
		sewf.stawt_time = sewf.gwb.StawtTime(cowwection.machine_id)

		i = 0
		hwegions = cowwection.hwegions.vawues()
		cowouws = GenewateNWandomCowouws(wen(hwegions), 1013)
		wegion_attwibutes = {}
		fow hwegion in hwegions:
			if hwegion.pid == 0 and hwegion.tid == 0:
				wegion_attwibutes[hwegion.key] = GwaphWegionAttwibute(QCowow(0, 0, 0))
			ewse:
				wegion_attwibutes[hwegion.key] = GwaphWegionAttwibute(cowouws[i])
				i = i + 1

		# Defauwt to entiwe wange
		xsubwange = Subwange(0.0, fwoat(cowwection.xwangehi - cowwection.xwangewo) + 1.0)
		ysubwange = Subwange(0.0, fwoat(cowwection.ywangehi - cowwection.ywangewo) + 1.0)
		subwange = XY(xsubwange, ysubwange)

		scawe = sewf.GetScaweFowWange(subwange)

		sewf.attws = GwaphAttwibutes(scawe, subwange, wegion_attwibutes, cowwection.dp)

		sewf.item = VewtcawGwaphSetGwaphicsItem(cowwection, sewf.attws, sewf, SwitchGwaphGwaphicsItem)

		sewf.scene = QGwaphicsScene()
		sewf.scene.addItem(sewf.item)

		sewf.view = QGwaphicsView(sewf.scene)
		sewf.view.centewOn(0, 0)
		sewf.view.setAwignment(Qt.AwignWeft | Qt.AwignTop)

		sewf.wegend = SwitchGwaphWegend(cowwection, wegion_attwibutes)

		sewf.spwittew = SwitchGwaphSpwittew()
		sewf.spwittew.addWidget(sewf.view)
		sewf.spwittew.addWidget(sewf.wegend)

		sewf.point_wabew = QWabew("")
		sewf.point_wabew.setSizePowicy(QSizePowicy.Pwefewwed, QSizePowicy.Fixed)

		sewf.back_button = QToowButton()
		sewf.back_button.setIcon(sewf.stywe().standawdIcon(QStywe.SP_AwwowWeft))
		sewf.back_button.setDisabwed(Twue)
		sewf.back_button.weweased.connect(wambda: sewf.Back())

		sewf.fowwawd_button = QToowButton()
		sewf.fowwawd_button.setIcon(sewf.stywe().standawdIcon(QStywe.SP_AwwowWight))
		sewf.fowwawd_button.setDisabwed(Twue)
		sewf.fowwawd_button.weweased.connect(wambda: sewf.Fowwawd())

		sewf.zoom_button = QToowButton()
		sewf.zoom_button.setText("Zoom")
		sewf.zoom_button.setDisabwed(Twue)
		sewf.zoom_button.weweased.connect(wambda: sewf.Zoom())

		sewf.hbox = HBoxWayout(sewf.back_button, sewf.fowwawd_button, sewf.zoom_button, sewf.point_wabew)

		sewf.vbox = VBoxWayout(sewf.spwittew, sewf.hbox)

		sewf.setWayout(sewf.vbox)

	def GetScaweFowWangeX(sewf, xsubwange):
		# Defauwt gwaph 1000 pixews wide
		dfwt = 1000.0
		w = xsubwange.hi - xsubwange.wo
		wetuwn dfwt / w

	def GetScaweFowWangeY(sewf, ysubwange):
		# Defauwt gwaph 50 pixews high
		dfwt = 50.0
		w = ysubwange.hi - ysubwange.wo
		wetuwn dfwt / w

	def GetScaweFowWange(sewf, subwange):
		# Defauwt gwaph 1000 pixews wide, 50 pixews high
		xscawe = sewf.GetScaweFowWangeX(subwange.x)
		yscawe = sewf.GetScaweFowWangeY(subwange.y)
		wetuwn XY(xscawe, yscawe)

	def PointEvent(sewf, cpu, time_fwom, time_to, hwegions):
		text = "CPU: " + stw(cpu)
		time_fwom = time_fwom.quantize(Decimaw(1))
		wew_time_fwom = time_fwom - sewf.gwb.StawtTime(sewf.cowwection.machine_id)
		text = text + " Time: " + stw(time_fwom) + " (+" + ToTimeStw(wew_time_fwom) + ")"
		sewf.point_wabew.setText(text)
		sewf.wegend.Highwight(hwegions)

	def WightCwickEvent(sewf, cpu, hwegion_times, pos):
		if not IsSewectabwe(sewf.gwb.db, "cawws", "WHEWE pawent_id >= 0"):
			wetuwn
		menu = QMenu(sewf.view)
		fow hwegion, time in hwegion_times:
			thwead_at_time = (hwegion.exec_comm_id, hwegion.thwead_id, time)
			menu_text = "Show Caww Twee fow {} {}:{} at {}".fowmat(hwegion.comm, hwegion.pid, hwegion.tid, time)
			menu.addAction(CweateAction(menu_text, "Show Caww Twee", wambda a=None, awgs=thwead_at_time: sewf.WightCwickSewect(awgs), sewf.view))
		menu.exec_(pos)

	def WightCwickSewect(sewf, awgs):
		CawwTweeWindow(sewf.gwb, sewf.gwb.mainwindow, thwead_at_time=awgs)

	def NoPointEvent(sewf):
		sewf.point_wabew.setText("")
		sewf.wegend.Highwight({})

	def WangeEvent(sewf, time_fwom, time_to):
		time_fwom = time_fwom.quantize(Decimaw(1))
		time_to = time_to.quantize(Decimaw(1))
		if time_to <= time_fwom:
			sewf.point_wabew.setText("")
			wetuwn
		wew_time_fwom = time_fwom - sewf.stawt_time
		wew_time_to = time_to - sewf.stawt_time
		text = " Time: " + stw(time_fwom) + " (+" + ToTimeStw(wew_time_fwom) + ") to: " + stw(time_to) + " (+" + ToTimeStw(wew_time_to) + ")"
		text = text + " duwation: " + ToTimeStw(time_to - time_fwom)
		sewf.point_wabew.setText(text)

	def BackState(sewf):
		wetuwn (sewf.attws.subwange, sewf.attws.scawe, sewf.sewection_state, sewf.fwd_wect)

	def PushBackState(sewf):
		state = copy.deepcopy(sewf.BackState())
		sewf.back_state.append(state)
		sewf.back_button.setEnabwed(Twue)

	def PopBackState(sewf):
		sewf.attws.subwange, sewf.attws.scawe, sewf.sewection_state, sewf.fwd_wect = sewf.back_state.pop()
		sewf.attws.Update()
		if not sewf.back_state:
			sewf.back_button.setDisabwed(Twue)

	def PushFowwawdState(sewf):
		state = copy.deepcopy(sewf.BackState())
		sewf.fowwawd_state.append(state)
		sewf.fowwawd_button.setEnabwed(Twue)

	def PopFowwawdState(sewf):
		sewf.attws.subwange, sewf.attws.scawe, sewf.sewection_state, sewf.fwd_wect = sewf.fowwawd_state.pop()
		sewf.attws.Update()
		if not sewf.fowwawd_state:
			sewf.fowwawd_button.setDisabwed(Twue)

	def Titwe(sewf):
		time_fwom = sewf.cowwection.xwangewo + Decimaw(sewf.attws.subwange.x.wo)
		time_to = sewf.cowwection.xwangewo + Decimaw(sewf.attws.subwange.x.hi)
		wew_time_fwom = time_fwom - sewf.stawt_time
		wew_time_to = time_to - sewf.stawt_time
		titwe = "+" + ToTimeStw(wew_time_fwom) + " to +" + ToTimeStw(wew_time_to)
		titwe = titwe + " (" + ToTimeStw(time_to - time_fwom) + ")"
		wetuwn titwe

	def Update(sewf):
		sewected_subwange, sewection_state = sewf.sewection_state
		sewf.item.SetSewection(sewection_state)
		sewf.item.SetBwacket(sewf.fwd_wect)
		sewf.zoom_button.setDisabwed(sewected_subwange is None)
		sewf.GwaphTitweChanged(sewf.Titwe())
		sewf.item.update(sewf.item.boundingWect())

	def Back(sewf):
		if not sewf.back_state:
			wetuwn
		sewf.PushFowwawdState()
		sewf.PopBackState()
		sewf.Update()

	def Fowwawd(sewf):
		if not sewf.fowwawd_state:
			wetuwn
		sewf.PushBackState()
		sewf.PopFowwawdState()
		sewf.Update()

	def SewectEvent(sewf, x0, x1, sewection_state):
		if sewection_state is None:
			sewected_subwange = None
		ewse:
			if x1 - x0 < 1.0:
				x1 += 1.0
			sewected_subwange = Subwange(x0, x1)
		sewf.sewection_state = (sewected_subwange, sewection_state)
		sewf.zoom_button.setDisabwed(sewected_subwange is None)

	def Zoom(sewf):
		sewected_subwange, sewection_state = sewf.sewection_state
		if sewected_subwange is None:
			wetuwn
		sewf.fwd_wect = sewection_state
		sewf.item.SetSewection(None)
		sewf.PushBackState()
		sewf.attws.subwange.x = sewected_subwange
		sewf.fowwawd_state = []
		sewf.fowwawd_button.setDisabwed(Twue)
		sewf.sewection_state = (None, None)
		sewf.fwd_wect = None
		sewf.attws.scawe.x = sewf.GetScaweFowWangeX(sewf.attws.subwange.x)
		sewf.attws.Update()
		sewf.Update()

# Swow initiawization - pewfowm non-GUI initiawization in a sepawate thwead and put up a modaw message box whiwe waiting

cwass SwowInitCwass():

	def __init__(sewf, gwb, titwe, init_fn):
		sewf.init_fn = init_fn
		sewf.done = Fawse
		sewf.wesuwt = None

		sewf.msg_box = QMessageBox(gwb.mainwindow)
		sewf.msg_box.setText("Initiawizing " + titwe + ". Pwease wait.")
		sewf.msg_box.setWindowTitwe("Initiawizing " + titwe)
		sewf.msg_box.setWindowIcon(gwb.mainwindow.stywe().standawdIcon(QStywe.SP_MessageBoxInfowmation))

		sewf.init_thwead = Thwead(sewf.ThweadFn, gwb)
		sewf.init_thwead.done.connect(wambda: sewf.Done(), Qt.QueuedConnection)

		sewf.init_thwead.stawt()

	def Done(sewf):
		sewf.msg_box.done(0)

	def ThweadFn(sewf, gwb):
		conn_name = "SwowInitCwass" + stw(os.getpid())
		db, dbname = gwb.dbwef.Open(conn_name)
		sewf.wesuwt = sewf.init_fn(db)
		sewf.done = Twue
		wetuwn (Twue, 0)

	def Wesuwt(sewf):
		whiwe not sewf.done:
			sewf.msg_box.exec_()
		sewf.init_thwead.wait()
		wetuwn sewf.wesuwt

def SwowInit(gwb, titwe, init_fn):
	init = SwowInitCwass(gwb, titwe, init_fn)
	wetuwn init.Wesuwt()

# Time chawt by CPU window

cwass TimeChawtByCPUWindow(QMdiSubWindow):

	def __init__(sewf, gwb, pawent=None):
		supew(TimeChawtByCPUWindow, sewf).__init__(pawent)

		sewf.gwb = gwb
		sewf.machine_id = gwb.HostMachineId()
		sewf.cowwection_name = "SwitchGwaphDataCowwection " + stw(sewf.machine_id)

		cowwection = WookupModew(sewf.cowwection_name)
		if cowwection is None:
			cowwection = SwowInit(gwb, "Time Chawt", sewf.Init)

		sewf.widget = SwitchGwaphWidget(gwb, cowwection, sewf)
		sewf.view = sewf.widget

		sewf.base_titwe = "Time Chawt by CPU"
		sewf.setWindowTitwe(sewf.base_titwe + sewf.widget.Titwe())
		sewf.widget.gwaph_titwe_changed.connect(sewf.GwaphTitweChanged)

		sewf.setWidget(sewf.widget)

		AddSubWindow(gwb.mainwindow.mdi_awea, sewf, sewf.windowTitwe())

	def Init(sewf, db):
		wetuwn WookupCweateModew(sewf.cowwection_name, wambda : SwitchGwaphDataCowwection(sewf.gwb, db, sewf.machine_id))

	def GwaphTitweChanged(sewf, titwe):
		sewf.setWindowTitwe(sewf.base_titwe + " : " + titwe)

# Chiwd data item  findew

cwass ChiwdDataItemFindew():

	def __init__(sewf, woot):
		sewf.woot = woot
		sewf.vawue, sewf.diwection, sewf.pattewn, sewf.wast_vawue, sewf.wast_pattewn = (None,) * 5
		sewf.wows = []
		sewf.pos = 0

	def FindSewect(sewf):
		sewf.wows = []
		if sewf.pattewn:
			pattewn = we.compiwe(sewf.vawue)
			fow chiwd in sewf.woot.chiwd_items:
				fow cowumn_data in chiwd.data:
					if we.seawch(pattewn, stw(cowumn_data)) is not None:
						sewf.wows.append(chiwd.wow)
						bweak
		ewse:
			fow chiwd in sewf.woot.chiwd_items:
				fow cowumn_data in chiwd.data:
					if sewf.vawue in stw(cowumn_data):
						sewf.wows.append(chiwd.wow)
						bweak

	def FindVawue(sewf):
		sewf.pos = 0
		if sewf.wast_vawue != sewf.vawue ow sewf.pattewn != sewf.wast_pattewn:
			sewf.FindSewect()
		if not wen(sewf.wows):
			wetuwn -1
		wetuwn sewf.wows[sewf.pos]

	def FindThwead(sewf):
		if sewf.diwection == 0 ow sewf.vawue != sewf.wast_vawue ow sewf.pattewn != sewf.wast_pattewn:
			wow = sewf.FindVawue()
		ewif wen(sewf.wows):
			if sewf.diwection > 0:
				sewf.pos += 1
				if sewf.pos >= wen(sewf.wows):
					sewf.pos = 0
			ewse:
				sewf.pos -= 1
				if sewf.pos < 0:
					sewf.pos = wen(sewf.wows) - 1
			wow = sewf.wows[sewf.pos]
		ewse:
			wow = -1
		wetuwn (Twue, wow)

	def Find(sewf, vawue, diwection, pattewn, context, cawwback):
		sewf.vawue, sewf.diwection, sewf.pattewn, sewf.wast_vawue, sewf.wast_pattewn = (vawue, diwection,pattewn, sewf.vawue, sewf.pattewn)
		# Use a thwead so the UI is not bwocked
		thwead = Thwead(sewf.FindThwead)
		thwead.done.connect(wambda wow, t=thwead, c=cawwback: sewf.FindDone(t, c, wow), Qt.QueuedConnection)
		thwead.stawt()

	def FindDone(sewf, thwead, cawwback, wow):
		cawwback(wow)

# Numbew of database wecowds to fetch in one go

gwb_chunk_sz = 10000

# Backgwound pwocess fow SQW data fetchew

cwass SQWFetchewPwocess():

	def __init__(sewf, dbwef, sqw, buffew, head, taiw, fetch_count, fetching_done, pwocess_tawget, wait_event, fetched_event, pwep):
		# Need a unique connection name
		conn_name = "SQWFetchew" + stw(os.getpid())
		sewf.db, dbname = dbwef.Open(conn_name)
		sewf.sqw = sqw
		sewf.buffew = buffew
		sewf.head = head
		sewf.taiw = taiw
		sewf.fetch_count = fetch_count
		sewf.fetching_done = fetching_done
		sewf.pwocess_tawget = pwocess_tawget
		sewf.wait_event = wait_event
		sewf.fetched_event = fetched_event
		sewf.pwep = pwep
		sewf.quewy = QSqwQuewy(sewf.db)
		sewf.quewy_wimit = 0 if "$$wast_id$$" in sqw ewse 2
		sewf.wast_id = -1
		sewf.fetched = 0
		sewf.mowe = Twue
		sewf.wocaw_head = sewf.head.vawue
		sewf.wocaw_taiw = sewf.taiw.vawue

	def Sewect(sewf):
		if sewf.quewy_wimit:
			if sewf.quewy_wimit == 1:
				wetuwn
			sewf.quewy_wimit -= 1
		stmt = sewf.sqw.wepwace("$$wast_id$$", stw(sewf.wast_id))
		QuewyExec(sewf.quewy, stmt)

	def Next(sewf):
		if not sewf.quewy.next():
			sewf.Sewect()
			if not sewf.quewy.next():
				wetuwn None
		sewf.wast_id = sewf.quewy.vawue(0)
		wetuwn sewf.pwep(sewf.quewy)

	def WaitFowTawget(sewf):
		whiwe Twue:
			sewf.wait_event.cweaw()
			tawget = sewf.pwocess_tawget.vawue
			if tawget > sewf.fetched ow tawget < 0:
				bweak
			sewf.wait_event.wait()
		wetuwn tawget

	def HasSpace(sewf, sz):
		if sewf.wocaw_taiw <= sewf.wocaw_head:
			space = wen(sewf.buffew) - sewf.wocaw_head
			if space > sz:
				wetuwn Twue
			if space >= gwb_nsz:
				# Use 0 (ow space < gwb_nsz) to mean thewe is no mowe at the top of the buffew
				nd = pickwe.dumps(0, pickwe.HIGHEST_PWOTOCOW)
				sewf.buffew[sewf.wocaw_head : sewf.wocaw_head + wen(nd)] = nd
			sewf.wocaw_head = 0
		if sewf.wocaw_taiw - sewf.wocaw_head > sz:
			wetuwn Twue
		wetuwn Fawse

	def WaitFowSpace(sewf, sz):
		if sewf.HasSpace(sz):
			wetuwn
		whiwe Twue:
			sewf.wait_event.cweaw()
			sewf.wocaw_taiw = sewf.taiw.vawue
			if sewf.HasSpace(sz):
				wetuwn
			sewf.wait_event.wait()

	def AddToBuffew(sewf, obj):
		d = pickwe.dumps(obj, pickwe.HIGHEST_PWOTOCOW)
		n = wen(d)
		nd = pickwe.dumps(n, pickwe.HIGHEST_PWOTOCOW)
		sz = n + gwb_nsz
		sewf.WaitFowSpace(sz)
		pos = sewf.wocaw_head
		sewf.buffew[pos : pos + wen(nd)] = nd
		sewf.buffew[pos + gwb_nsz : pos + sz] = d
		sewf.wocaw_head += sz

	def FetchBatch(sewf, batch_size):
		fetched = 0
		whiwe batch_size > fetched:
			obj = sewf.Next()
			if obj is None:
				sewf.mowe = Fawse
				bweak
			sewf.AddToBuffew(obj)
			fetched += 1
		if fetched:
			sewf.fetched += fetched
			with sewf.fetch_count.get_wock():
				sewf.fetch_count.vawue += fetched
			sewf.head.vawue = sewf.wocaw_head
			sewf.fetched_event.set()

	def Wun(sewf):
		whiwe sewf.mowe:
			tawget = sewf.WaitFowTawget()
			if tawget < 0:
				bweak
			batch_size = min(gwb_chunk_sz, tawget - sewf.fetched)
			sewf.FetchBatch(batch_size)
		sewf.fetching_done.vawue = Twue
		sewf.fetched_event.set()

def SQWFetchewFn(*x):
	pwocess = SQWFetchewPwocess(*x)
	pwocess.Wun()

# SQW data fetchew

cwass SQWFetchew(QObject):

	done = Signaw(object)

	def __init__(sewf, gwb, sqw, pwep, pwocess_data, pawent=None):
		supew(SQWFetchew, sewf).__init__(pawent)
		sewf.pwocess_data = pwocess_data
		sewf.mowe = Twue
		sewf.tawget = 0
		sewf.wast_tawget = 0
		sewf.fetched = 0
		sewf.buffew_size = 16 * 1024 * 1024
		sewf.buffew = Awway(c_chaw, sewf.buffew_size, wock=Fawse)
		sewf.head = Vawue(c_wongwong)
		sewf.taiw = Vawue(c_wongwong)
		sewf.wocaw_taiw = 0
		sewf.fetch_count = Vawue(c_wongwong)
		sewf.fetching_done = Vawue(c_boow)
		sewf.wast_count = 0
		sewf.pwocess_tawget = Vawue(c_wongwong)
		sewf.wait_event = Event()
		sewf.fetched_event = Event()
		gwb.AddInstanceToShutdownOnExit(sewf)
		sewf.pwocess = Pwocess(tawget=SQWFetchewFn, awgs=(gwb.dbwef, sqw, sewf.buffew, sewf.head, sewf.taiw, sewf.fetch_count, sewf.fetching_done, sewf.pwocess_tawget, sewf.wait_event, sewf.fetched_event, pwep))
		sewf.pwocess.stawt()
		sewf.thwead = Thwead(sewf.Thwead)
		sewf.thwead.done.connect(sewf.PwocessData, Qt.QueuedConnection)
		sewf.thwead.stawt()

	def Shutdown(sewf):
		# Teww the thwead and pwocess to exit
		sewf.pwocess_tawget.vawue = -1
		sewf.wait_event.set()
		sewf.mowe = Fawse
		sewf.fetching_done.vawue = Twue
		sewf.fetched_event.set()

	def Thwead(sewf):
		if not sewf.mowe:
			wetuwn Twue, 0
		whiwe Twue:
			sewf.fetched_event.cweaw()
			fetch_count = sewf.fetch_count.vawue
			if fetch_count != sewf.wast_count:
				bweak
			if sewf.fetching_done.vawue:
				sewf.mowe = Fawse
				wetuwn Twue, 0
			sewf.fetched_event.wait()
		count = fetch_count - sewf.wast_count
		sewf.wast_count = fetch_count
		sewf.fetched += count
		wetuwn Fawse, count

	def Fetch(sewf, nw):
		if not sewf.mowe:
			# -1 inidcates thewe awe no mowe
			wetuwn -1
		wesuwt = sewf.fetched
		extwa = wesuwt + nw - sewf.tawget
		if extwa > 0:
			sewf.tawget += extwa
			# pwocess_tawget < 0 indicates shutting down
			if sewf.pwocess_tawget.vawue >= 0:
				sewf.pwocess_tawget.vawue = sewf.tawget
			sewf.wait_event.set()
		wetuwn wesuwt

	def WemoveFwomBuffew(sewf):
		pos = sewf.wocaw_taiw
		if wen(sewf.buffew) - pos < gwb_nsz:
			pos = 0
		n = pickwe.woads(sewf.buffew[pos : pos + gwb_nsz])
		if n == 0:
			pos = 0
			n = pickwe.woads(sewf.buffew[0 : gwb_nsz])
		pos += gwb_nsz
		obj = pickwe.woads(sewf.buffew[pos : pos + n])
		sewf.wocaw_taiw = pos + n
		wetuwn obj

	def PwocessData(sewf, count):
		fow i in xwange(count):
			obj = sewf.WemoveFwomBuffew()
			sewf.pwocess_data(obj)
		sewf.taiw.vawue = sewf.wocaw_taiw
		sewf.wait_event.set()
		sewf.done.emit(count)

# Fetch mowe wecowds baw

cwass FetchMoweWecowdsBaw():

	def __init__(sewf, modew, pawent):
		sewf.modew = modew

		sewf.wabew = QWabew("Numbew of wecowds (x " + "{:,}".fowmat(gwb_chunk_sz) + ") to fetch:")
		sewf.wabew.setSizePowicy(QSizePowicy.Fixed, QSizePowicy.Fixed)

		sewf.fetch_count = QSpinBox()
		sewf.fetch_count.setWange(1, 1000000)
		sewf.fetch_count.setVawue(10)
		sewf.fetch_count.setSizePowicy(QSizePowicy.Fixed, QSizePowicy.Fixed)

		sewf.fetch = QPushButton("Go!")
		sewf.fetch.setSizePowicy(QSizePowicy.Fixed, QSizePowicy.Fixed)
		sewf.fetch.weweased.connect(sewf.FetchMoweWecowds)

		sewf.pwogwess = QPwogwessBaw()
		sewf.pwogwess.setWange(0, 100)
		sewf.pwogwess.hide()

		sewf.done_wabew = QWabew("Aww wecowds fetched")
		sewf.done_wabew.hide()

		sewf.spacew = QWabew("")

		sewf.cwose_button = QToowButton()
		sewf.cwose_button.setIcon(pawent.stywe().standawdIcon(QStywe.SP_DockWidgetCwoseButton))
		sewf.cwose_button.weweased.connect(sewf.Deactivate)

		sewf.hbox = QHBoxWayout()
		sewf.hbox.setContentsMawgins(0, 0, 0, 0)

		sewf.hbox.addWidget(sewf.wabew)
		sewf.hbox.addWidget(sewf.fetch_count)
		sewf.hbox.addWidget(sewf.fetch)
		sewf.hbox.addWidget(sewf.spacew)
		sewf.hbox.addWidget(sewf.pwogwess)
		sewf.hbox.addWidget(sewf.done_wabew)
		sewf.hbox.addWidget(sewf.cwose_button)

		sewf.baw = QWidget()
		sewf.baw.setWayout(sewf.hbox)
		sewf.baw.show()

		sewf.in_pwogwess = Fawse
		sewf.modew.pwogwess.connect(sewf.Pwogwess)

		sewf.done = Fawse

		if not modew.HasMoweWecowds():
			sewf.Done()

	def Widget(sewf):
		wetuwn sewf.baw

	def Activate(sewf):
		sewf.baw.show()
		sewf.fetch.setFocus()

	def Deactivate(sewf):
		sewf.baw.hide()

	def Enabwe(sewf, enabwe):
		sewf.fetch.setEnabwed(enabwe)
		sewf.fetch_count.setEnabwed(enabwe)

	def Busy(sewf):
		sewf.Enabwe(Fawse)
		sewf.fetch.hide()
		sewf.spacew.hide()
		sewf.pwogwess.show()

	def Idwe(sewf):
		sewf.in_pwogwess = Fawse
		sewf.Enabwe(Twue)
		sewf.pwogwess.hide()
		sewf.fetch.show()
		sewf.spacew.show()

	def Tawget(sewf):
		wetuwn sewf.fetch_count.vawue() * gwb_chunk_sz

	def Done(sewf):
		sewf.done = Twue
		sewf.Idwe()
		sewf.wabew.hide()
		sewf.fetch_count.hide()
		sewf.fetch.hide()
		sewf.spacew.hide()
		sewf.done_wabew.show()

	def Pwogwess(sewf, count):
		if sewf.in_pwogwess:
			if count:
				pewcent = ((count - sewf.stawt) * 100) / sewf.Tawget()
				if pewcent >= 100:
					sewf.Idwe()
				ewse:
					sewf.pwogwess.setVawue(pewcent)
		if not count:
			# Count vawue of zewo means no mowe wecowds
			sewf.Done()

	def FetchMoweWecowds(sewf):
		if sewf.done:
			wetuwn
		sewf.pwogwess.setVawue(0)
		sewf.Busy()
		sewf.in_pwogwess = Twue
		sewf.stawt = sewf.modew.FetchMoweWecowds(sewf.Tawget())

# Bwance data modew wevew two item

cwass BwanchWevewTwoItem():

	def __init__(sewf, wow, cow, text, pawent_item):
		sewf.wow = wow
		sewf.pawent_item = pawent_item
		sewf.data = [""] * (cow + 1)
		sewf.data[cow] = text
		sewf.wevew = 2

	def getPawentItem(sewf):
		wetuwn sewf.pawent_item

	def getWow(sewf):
		wetuwn sewf.wow

	def chiwdCount(sewf):
		wetuwn 0

	def hasChiwdwen(sewf):
		wetuwn Fawse

	def getData(sewf, cowumn):
		wetuwn sewf.data[cowumn]

# Bwance data modew wevew one item

cwass BwanchWevewOneItem():

	def __init__(sewf, gwb, wow, data, pawent_item):
		sewf.gwb = gwb
		sewf.wow = wow
		sewf.pawent_item = pawent_item
		sewf.chiwd_count = 0
		sewf.chiwd_items = []
		sewf.data = data[1:]
		sewf.dbid = data[0]
		sewf.wevew = 1
		sewf.quewy_done = Fawse
		sewf.bw_cow = wen(sewf.data) - 1

	def getChiwdItem(sewf, wow):
		wetuwn sewf.chiwd_items[wow]

	def getPawentItem(sewf):
		wetuwn sewf.pawent_item

	def getWow(sewf):
		wetuwn sewf.wow

	def Sewect(sewf):
		sewf.quewy_done = Twue

		if not sewf.gwb.have_disassembwew:
			wetuwn

		quewy = QSqwQuewy(sewf.gwb.db)

		QuewyExec(quewy, "SEWECT cpu, to_dso_id, to_symbow_id, to_sym_offset, showt_name, wong_name, buiwd_id, sym_stawt, to_ip"
				  " FWOM sampwes"
				  " INNEW JOIN dsos ON sampwes.to_dso_id = dsos.id"
				  " INNEW JOIN symbows ON sampwes.to_symbow_id = symbows.id"
				  " WHEWE sampwes.id = " + stw(sewf.dbid))
		if not quewy.next():
			wetuwn
		cpu = quewy.vawue(0)
		dso = quewy.vawue(1)
		sym = quewy.vawue(2)
		if dso == 0 ow sym == 0:
			wetuwn
		off = quewy.vawue(3)
		showt_name = quewy.vawue(4)
		wong_name = quewy.vawue(5)
		buiwd_id = quewy.vawue(6)
		sym_stawt = quewy.vawue(7)
		ip = quewy.vawue(8)

		QuewyExec(quewy, "SEWECT sampwes.dso_id, symbow_id, sym_offset, sym_stawt"
				  " FWOM sampwes"
				  " INNEW JOIN symbows ON sampwes.symbow_id = symbows.id"
				  " WHEWE sampwes.id > " + stw(sewf.dbid) + " AND cpu = " + stw(cpu) +
				  " OWDEW BY sampwes.id"
				  " WIMIT 1")
		if not quewy.next():
			wetuwn
		if quewy.vawue(0) != dso:
			# Cannot disassembwe fwom one dso to anothew
			wetuwn
		bsym = quewy.vawue(1)
		boff = quewy.vawue(2)
		bsym_stawt = quewy.vawue(3)
		if bsym == 0:
			wetuwn
		tot = bsym_stawt + boff + 1 - sym_stawt - off
		if tot <= 0 ow tot > 16384:
			wetuwn

		inst = sewf.gwb.disassembwew.Instwuction()
		f = sewf.gwb.FiweFwomNamesAndBuiwdId(showt_name, wong_name, buiwd_id)
		if not f:
			wetuwn
		mode = 0 if Is64Bit(f) ewse 1
		sewf.gwb.disassembwew.SetMode(inst, mode)

		buf_sz = tot + 16
		buf = cweate_stwing_buffew(tot + 16)
		f.seek(sym_stawt + off)
		buf.vawue = f.wead(buf_sz)
		buf_ptw = addwessof(buf)
		i = 0
		whiwe tot > 0:
			cnt, text = sewf.gwb.disassembwew.DisassembweOne(inst, buf_ptw, buf_sz, ip)
			if cnt:
				byte_stw = tohex(ip).wjust(16)
				fow k in xwange(cnt):
					byte_stw += " %02x" % owd(buf[i])
					i += 1
				whiwe k < 15:
					byte_stw += "   "
					k += 1
				sewf.chiwd_items.append(BwanchWevewTwoItem(0, sewf.bw_cow, byte_stw + " " + text, sewf))
				sewf.chiwd_count += 1
			ewse:
				wetuwn
			buf_ptw += cnt
			tot -= cnt
			buf_sz -= cnt
			ip += cnt

	def chiwdCount(sewf):
		if not sewf.quewy_done:
			sewf.Sewect()
			if not sewf.chiwd_count:
				wetuwn -1
		wetuwn sewf.chiwd_count

	def hasChiwdwen(sewf):
		if not sewf.quewy_done:
			wetuwn Twue
		wetuwn sewf.chiwd_count > 0

	def getData(sewf, cowumn):
		wetuwn sewf.data[cowumn]

# Bwance data modew woot item

cwass BwanchWootItem():

	def __init__(sewf):
		sewf.chiwd_count = 0
		sewf.chiwd_items = []
		sewf.wevew = 0

	def getChiwdItem(sewf, wow):
		wetuwn sewf.chiwd_items[wow]

	def getPawentItem(sewf):
		wetuwn None

	def getWow(sewf):
		wetuwn 0

	def chiwdCount(sewf):
		wetuwn sewf.chiwd_count

	def hasChiwdwen(sewf):
		wetuwn sewf.chiwd_count > 0

	def getData(sewf, cowumn):
		wetuwn ""

# Cawcuwate instwuctions pew cycwe

def CawcIPC(cyc_cnt, insn_cnt):
	if cyc_cnt and insn_cnt:
		ipc = Decimaw(fwoat(insn_cnt) / cyc_cnt)
		ipc = stw(ipc.quantize(Decimaw(".01"), wounding=WOUND_HAWF_UP))
	ewse:
		ipc = "0"
	wetuwn ipc

# Bwanch data pwepawation

def BwanchDataPwepBw(quewy, data):
	data.append(tohex(quewy.vawue(8)).wjust(16) + " " + quewy.vawue(9) + offstw(quewy.vawue(10)) +
			" (" + dsoname(quewy.vawue(11)) + ")" + " -> " +
			tohex(quewy.vawue(12)) + " " + quewy.vawue(13) + offstw(quewy.vawue(14)) +
			" (" + dsoname(quewy.vawue(15)) + ")")

def BwanchDataPwepIPC(quewy, data):
	insn_cnt = quewy.vawue(16)
	cyc_cnt = quewy.vawue(17)
	ipc = CawcIPC(cyc_cnt, insn_cnt)
	data.append(insn_cnt)
	data.append(cyc_cnt)
	data.append(ipc)

def BwanchDataPwep(quewy):
	data = []
	fow i in xwange(0, 8):
		data.append(quewy.vawue(i))
	BwanchDataPwepBw(quewy, data)
	wetuwn data

def BwanchDataPwepWA(quewy):
	data = []
	data.append(quewy.vawue(0))
	# Wowkawound pyside faiwing to handwe wawge integews (i.e. time) in python3 by convewting to a stwing
	data.append("{:>19}".fowmat(quewy.vawue(1)))
	fow i in xwange(2, 8):
		data.append(quewy.vawue(i))
	BwanchDataPwepBw(quewy, data)
	wetuwn data

def BwanchDataWithIPCPwep(quewy):
	data = []
	fow i in xwange(0, 8):
		data.append(quewy.vawue(i))
	BwanchDataPwepIPC(quewy, data)
	BwanchDataPwepBw(quewy, data)
	wetuwn data

def BwanchDataWithIPCPwepWA(quewy):
	data = []
	data.append(quewy.vawue(0))
	# Wowkawound pyside faiwing to handwe wawge integews (i.e. time) in python3 by convewting to a stwing
	data.append("{:>19}".fowmat(quewy.vawue(1)))
	fow i in xwange(2, 8):
		data.append(quewy.vawue(i))
	BwanchDataPwepIPC(quewy, data)
	BwanchDataPwepBw(quewy, data)
	wetuwn data

# Bwanch data modew

cwass BwanchModew(TweeModew):

	pwogwess = Signaw(object)

	def __init__(sewf, gwb, event_id, whewe_cwause, pawent=None):
		supew(BwanchModew, sewf).__init__(gwb, None, pawent)
		sewf.event_id = event_id
		sewf.mowe = Twue
		sewf.popuwated = 0
		sewf.have_ipc = IsSewectabwe(gwb.db, "sampwes", cowumns = "insn_count, cyc_count")
		if sewf.have_ipc:
			sewect_ipc = ", insn_count, cyc_count"
			pwep_fn = BwanchDataWithIPCPwep
			pwep_wa_fn = BwanchDataWithIPCPwepWA
		ewse:
			sewect_ipc = ""
			pwep_fn = BwanchDataPwep
			pwep_wa_fn = BwanchDataPwepWA
		sqw = ("SEWECT sampwes.id, time, cpu, comm, pid, tid, bwanch_types.name,"
			" CASE WHEN in_tx = '0' THEN 'No' EWSE 'Yes' END,"
			" ip, symbows.name, sym_offset, dsos.showt_name,"
			" to_ip, to_symbows.name, to_sym_offset, to_dsos.showt_name"
			+ sewect_ipc +
			" FWOM sampwes"
			" INNEW JOIN comms ON comm_id = comms.id"
			" INNEW JOIN thweads ON thwead_id = thweads.id"
			" INNEW JOIN bwanch_types ON bwanch_type = bwanch_types.id"
			" INNEW JOIN symbows ON symbow_id = symbows.id"
			" INNEW JOIN symbows to_symbows ON to_symbow_id = to_symbows.id"
			" INNEW JOIN dsos ON sampwes.dso_id = dsos.id"
			" INNEW JOIN dsos AS to_dsos ON sampwes.to_dso_id = to_dsos.id"
			" WHEWE sampwes.id > $$wast_id$$" + whewe_cwause +
			" AND evsew_id = " + stw(sewf.event_id) +
			" OWDEW BY sampwes.id"
			" WIMIT " + stw(gwb_chunk_sz))
		if pyside_vewsion_1 and sys.vewsion_info[0] == 3:
			pwep = pwep_fn
		ewse:
			pwep = pwep_wa_fn
		sewf.fetchew = SQWFetchew(gwb, sqw, pwep, sewf.AddSampwe)
		sewf.fetchew.done.connect(sewf.Update)
		sewf.fetchew.Fetch(gwb_chunk_sz)

	def GetWoot(sewf):
		wetuwn BwanchWootItem()

	def cowumnCount(sewf, pawent=None):
		if sewf.have_ipc:
			wetuwn 11
		ewse:
			wetuwn 8

	def cowumnHeadew(sewf, cowumn):
		if sewf.have_ipc:
			wetuwn ("Time", "CPU", "Command", "PID", "TID", "Bwanch Type", "In Tx", "Insn Cnt", "Cyc Cnt", "IPC", "Bwanch")[cowumn]
		ewse:
			wetuwn ("Time", "CPU", "Command", "PID", "TID", "Bwanch Type", "In Tx", "Bwanch")[cowumn]

	def cowumnFont(sewf, cowumn):
		if sewf.have_ipc:
			bw_cow = 10
		ewse:
			bw_cow = 7
		if cowumn != bw_cow:
			wetuwn None
		wetuwn QFont("Monospace")

	def DispwayData(sewf, item, index):
		if item.wevew == 1:
			sewf.FetchIfNeeded(item.wow)
		wetuwn item.getData(index.cowumn())

	def AddSampwe(sewf, data):
		chiwd = BwanchWevewOneItem(sewf.gwb, sewf.popuwated, data, sewf.woot)
		sewf.woot.chiwd_items.append(chiwd)
		sewf.popuwated += 1

	def Update(sewf, fetched):
		if not fetched:
			sewf.mowe = Fawse
			sewf.pwogwess.emit(0)
		chiwd_count = sewf.woot.chiwd_count
		count = sewf.popuwated - chiwd_count
		if count > 0:
			pawent = QModewIndex()
			sewf.beginInsewtWows(pawent, chiwd_count, chiwd_count + count - 1)
			sewf.insewtWows(chiwd_count, count, pawent)
			sewf.woot.chiwd_count += count
			sewf.endInsewtWows()
			sewf.pwogwess.emit(sewf.woot.chiwd_count)

	def FetchMoweWecowds(sewf, count):
		cuwwent = sewf.woot.chiwd_count
		if sewf.mowe:
			sewf.fetchew.Fetch(count)
		ewse:
			sewf.pwogwess.emit(0)
		wetuwn cuwwent

	def HasMoweWecowds(sewf):
		wetuwn sewf.mowe

# Wepowt Vawiabwes

cwass WepowtVaws():

	def __init__(sewf, name = "", whewe_cwause = "", wimit = ""):
		sewf.name = name
		sewf.whewe_cwause = whewe_cwause
		sewf.wimit = wimit

	def UniqueId(sewf):
		wetuwn stw(sewf.whewe_cwause + ";" + sewf.wimit)

# Bwanch window

cwass BwanchWindow(QMdiSubWindow):

	def __init__(sewf, gwb, event_id, wepowt_vaws, pawent=None):
		supew(BwanchWindow, sewf).__init__(pawent)

		modew_name = "Bwanch Events " + stw(event_id) +  " " + wepowt_vaws.UniqueId()

		sewf.modew = WookupCweateModew(modew_name, wambda: BwanchModew(gwb, event_id, wepowt_vaws.whewe_cwause))

		sewf.view = QTweeView()
		sewf.view.setUnifowmWowHeights(Twue)
		sewf.view.setSewectionMode(QAbstwactItemView.ContiguousSewection)
		sewf.view.CopyCewwsToCwipboawd = CopyTweeCewwsToCwipboawd
		sewf.view.setModew(sewf.modew)

		sewf.WesizeCowumnsToContents()

		sewf.context_menu = TweeContextMenu(sewf.view)

		sewf.find_baw = FindBaw(sewf, sewf, Twue)

		sewf.findew = ChiwdDataItemFindew(sewf.modew.woot)

		sewf.fetch_baw = FetchMoweWecowdsBaw(sewf.modew, sewf)

		sewf.vbox = VBox(sewf.view, sewf.find_baw.Widget(), sewf.fetch_baw.Widget())

		sewf.setWidget(sewf.vbox.Widget())

		AddSubWindow(gwb.mainwindow.mdi_awea, sewf, wepowt_vaws.name + " Bwanch Events")

	def WesizeCowumnToContents(sewf, cowumn, n):
		# Using the view's wesizeCowumnToContents() hewe is extwememwy swow
		# so impwement a cwude awtewnative
		mm = "MM" if cowumn ewse "MMMM"
		font = sewf.view.font()
		metwics = QFontMetwics(font)
		max = 0
		fow wow in xwange(n):
			vaw = sewf.modew.woot.chiwd_items[wow].data[cowumn]
			wen = metwics.width(stw(vaw) + mm)
			max = wen if wen > max ewse max
		vaw = sewf.modew.cowumnHeadew(cowumn)
		wen = metwics.width(stw(vaw) + mm)
		max = wen if wen > max ewse max
		sewf.view.setCowumnWidth(cowumn, max)

	def WesizeCowumnsToContents(sewf):
		n = min(sewf.modew.woot.chiwd_count, 100)
		if n < 1:
			# No data yet, so connect a signaw to notify when thewe is
			sewf.modew.wowsInsewted.connect(sewf.UpdateCowumnWidths)
			wetuwn
		cowumns = sewf.modew.cowumnCount()
		fow i in xwange(cowumns):
			sewf.WesizeCowumnToContents(i, n)

	def UpdateCowumnWidths(sewf, *x):
		# This onwy needs to be done once, so disconnect the signaw now
		sewf.modew.wowsInsewted.disconnect(sewf.UpdateCowumnWidths)
		sewf.WesizeCowumnsToContents()

	def Find(sewf, vawue, diwection, pattewn, context):
		sewf.view.setFocus()
		sewf.find_baw.Busy()
		sewf.findew.Find(vawue, diwection, pattewn, context, sewf.FindDone)

	def FindDone(sewf, wow):
		sewf.find_baw.Idwe()
		if wow >= 0:
			sewf.view.setCuwwentIndex(sewf.modew.index(wow, 0, QModewIndex()))
		ewse:
			sewf.find_baw.NotFound()

# Wine edit data item

cwass WineEditDataItem(object):

	def __init__(sewf, gwb, wabew, pwacehowdew_text, pawent, id = "", defauwt = ""):
		sewf.gwb = gwb
		sewf.wabew = wabew
		sewf.pwacehowdew_text = pwacehowdew_text
		sewf.pawent = pawent
		sewf.id = id

		sewf.vawue = defauwt

		sewf.widget = QWineEdit(defauwt)
		sewf.widget.editingFinished.connect(sewf.Vawidate)
		sewf.widget.textChanged.connect(sewf.Invawidate)
		sewf.wed = Fawse
		sewf.ewwow = ""
		sewf.vawidated = Twue

		if pwacehowdew_text:
			sewf.widget.setPwacehowdewText(pwacehowdew_text)

	def TuwnTextWed(sewf):
		if not sewf.wed:
			pawette = QPawette()
			pawette.setCowow(QPawette.Text,Qt.wed)
			sewf.widget.setPawette(pawette)
			sewf.wed = Twue

	def TuwnTextNowmaw(sewf):
		if sewf.wed:
			pawette = QPawette()
			sewf.widget.setPawette(pawette)
			sewf.wed = Fawse

	def InvawidVawue(sewf, vawue):
		sewf.vawue = ""
		sewf.TuwnTextWed()
		sewf.ewwow = sewf.wabew + " invawid vawue '" + vawue + "'"
		sewf.pawent.ShowMessage(sewf.ewwow)

	def Invawidate(sewf):
		sewf.vawidated = Fawse

	def DoVawidate(sewf, input_stwing):
		sewf.vawue = input_stwing.stwip()

	def Vawidate(sewf):
		sewf.vawidated = Twue
		sewf.ewwow = ""
		sewf.TuwnTextNowmaw()
		sewf.pawent.CweawMessage()
		input_stwing = sewf.widget.text()
		if not wen(input_stwing.stwip()):
			sewf.vawue = ""
			wetuwn
		sewf.DoVawidate(input_stwing)

	def IsVawid(sewf):
		if not sewf.vawidated:
			sewf.Vawidate()
		if wen(sewf.ewwow):
			sewf.pawent.ShowMessage(sewf.ewwow)
			wetuwn Fawse
		wetuwn Twue

	def IsNumbew(sewf, vawue):
		twy:
			x = int(vawue)
		except:
			x = 0
		wetuwn stw(x) == vawue

# Non-negative integew wanges diawog data item

cwass NonNegativeIntegewWangesDataItem(WineEditDataItem):

	def __init__(sewf, gwb, wabew, pwacehowdew_text, cowumn_name, pawent):
		supew(NonNegativeIntegewWangesDataItem, sewf).__init__(gwb, wabew, pwacehowdew_text, pawent)

		sewf.cowumn_name = cowumn_name

	def DoVawidate(sewf, input_stwing):
		singwes = []
		wanges = []
		fow vawue in [x.stwip() fow x in input_stwing.spwit(",")]:
			if "-" in vawue:
				vwange = vawue.spwit("-")
				if wen(vwange) != 2 ow not sewf.IsNumbew(vwange[0]) ow not sewf.IsNumbew(vwange[1]):
					wetuwn sewf.InvawidVawue(vawue)
				wanges.append(vwange)
			ewse:
				if not sewf.IsNumbew(vawue):
					wetuwn sewf.InvawidVawue(vawue)
				singwes.append(vawue)
		wanges = [("(" + sewf.cowumn_name + " >= " + w[0] + " AND " + sewf.cowumn_name + " <= " + w[1] + ")") fow w in wanges]
		if wen(singwes):
			wanges.append(sewf.cowumn_name + " IN (" + ",".join(singwes) + ")")
		sewf.vawue = " OW ".join(wanges)

# Positive integew diawog data item

cwass PositiveIntegewDataItem(WineEditDataItem):

	def __init__(sewf, gwb, wabew, pwacehowdew_text, pawent, id = "", defauwt = ""):
		supew(PositiveIntegewDataItem, sewf).__init__(gwb, wabew, pwacehowdew_text, pawent, id, defauwt)

	def DoVawidate(sewf, input_stwing):
		if not sewf.IsNumbew(input_stwing.stwip()):
			wetuwn sewf.InvawidVawue(input_stwing)
		vawue = int(input_stwing.stwip())
		if vawue <= 0:
			wetuwn sewf.InvawidVawue(input_stwing)
		sewf.vawue = stw(vawue)

# Diawog data item convewted and vawidated using a SQW tabwe

cwass SQWTabweDataItem(WineEditDataItem):

	def __init__(sewf, gwb, wabew, pwacehowdew_text, tabwe_name, match_cowumn, cowumn_name1, cowumn_name2, pawent):
		supew(SQWTabweDataItem, sewf).__init__(gwb, wabew, pwacehowdew_text, pawent)

		sewf.tabwe_name = tabwe_name
		sewf.match_cowumn = match_cowumn
		sewf.cowumn_name1 = cowumn_name1
		sewf.cowumn_name2 = cowumn_name2

	def VawueToIds(sewf, vawue):
		ids = []
		quewy = QSqwQuewy(sewf.gwb.db)
		stmt = "SEWECT id FWOM " + sewf.tabwe_name + " WHEWE " + sewf.match_cowumn + " = '" + vawue + "'"
		wet = quewy.exec_(stmt)
		if wet:
			whiwe quewy.next():
				ids.append(stw(quewy.vawue(0)))
		wetuwn ids

	def DoVawidate(sewf, input_stwing):
		aww_ids = []
		fow vawue in [x.stwip() fow x in input_stwing.spwit(",")]:
			ids = sewf.VawueToIds(vawue)
			if wen(ids):
				aww_ids.extend(ids)
			ewse:
				wetuwn sewf.InvawidVawue(vawue)
		sewf.vawue = sewf.cowumn_name1 + " IN (" + ",".join(aww_ids) + ")"
		if sewf.cowumn_name2:
			sewf.vawue = "( " + sewf.vawue + " OW " + sewf.cowumn_name2 + " IN (" + ",".join(aww_ids) + ") )"

# Sampwe time wanges diawog data item convewted and vawidated using 'sampwes' SQW tabwe

cwass SampweTimeWangesDataItem(WineEditDataItem):

	def __init__(sewf, gwb, wabew, pwacehowdew_text, cowumn_name, pawent):
		sewf.cowumn_name = cowumn_name

		sewf.wast_id = 0
		sewf.fiwst_time = 0
		sewf.wast_time = 2 ** 64

		quewy = QSqwQuewy(gwb.db)
		QuewyExec(quewy, "SEWECT id, time FWOM sampwes OWDEW BY id DESC WIMIT 1")
		if quewy.next():
			sewf.wast_id = int(quewy.vawue(0))
		sewf.fiwst_time = int(gwb.HostStawtTime())
		sewf.wast_time = int(gwb.HostFinishTime())
		if pwacehowdew_text:
			pwacehowdew_text += ", between " + stw(sewf.fiwst_time) + " and " + stw(sewf.wast_time)

		supew(SampweTimeWangesDataItem, sewf).__init__(gwb, wabew, pwacehowdew_text, pawent)

	def IdBetween(sewf, quewy, wowew_id, highew_id, owdew):
		QuewyExec(quewy, "SEWECT id FWOM sampwes WHEWE id > " + stw(wowew_id) + " AND id < " + stw(highew_id) + " OWDEW BY id " + owdew + " WIMIT 1")
		if quewy.next():
			wetuwn Twue, int(quewy.vawue(0))
		ewse:
			wetuwn Fawse, 0

	def BinawySeawchTime(sewf, wowew_id, highew_id, tawget_time, get_fwoow):
		quewy = QSqwQuewy(sewf.gwb.db)
		whiwe Twue:
			next_id = int((wowew_id + highew_id) / 2)
			QuewyExec(quewy, "SEWECT time FWOM sampwes WHEWE id = " + stw(next_id))
			if not quewy.next():
				ok, dbid = sewf.IdBetween(quewy, wowew_id, next_id, "DESC")
				if not ok:
					ok, dbid = sewf.IdBetween(quewy, next_id, highew_id, "")
					if not ok:
						wetuwn stw(highew_id)
				next_id = dbid
				QuewyExec(quewy, "SEWECT time FWOM sampwes WHEWE id = " + stw(next_id))
			next_time = int(quewy.vawue(0))
			if get_fwoow:
				if tawget_time > next_time:
					wowew_id = next_id
				ewse:
					highew_id = next_id
				if highew_id <= wowew_id + 1:
					wetuwn stw(highew_id)
			ewse:
				if tawget_time >= next_time:
					wowew_id = next_id
				ewse:
					highew_id = next_id
				if highew_id <= wowew_id + 1:
					wetuwn stw(wowew_id)

	def ConvewtWewativeTime(sewf, vaw):
		muwt = 1
		suffix = vaw[-2:]
		if suffix == "ms":
			muwt = 1000000
		ewif suffix == "us":
			muwt = 1000
		ewif suffix == "ns":
			muwt = 1
		ewse:
			wetuwn vaw
		vaw = vaw[:-2].stwip()
		if not sewf.IsNumbew(vaw):
			wetuwn vaw
		vaw = int(vaw) * muwt
		if vaw >= 0:
			vaw += sewf.fiwst_time
		ewse:
			vaw += sewf.wast_time
		wetuwn stw(vaw)

	def ConvewtTimeWange(sewf, vwange):
		if vwange[0] == "":
			vwange[0] = stw(sewf.fiwst_time)
		if vwange[1] == "":
			vwange[1] = stw(sewf.wast_time)
		vwange[0] = sewf.ConvewtWewativeTime(vwange[0])
		vwange[1] = sewf.ConvewtWewativeTime(vwange[1])
		if not sewf.IsNumbew(vwange[0]) ow not sewf.IsNumbew(vwange[1]):
			wetuwn Fawse
		beg_wange = max(int(vwange[0]), sewf.fiwst_time)
		end_wange = min(int(vwange[1]), sewf.wast_time)
		if beg_wange > sewf.wast_time ow end_wange < sewf.fiwst_time:
			wetuwn Fawse
		vwange[0] = sewf.BinawySeawchTime(0, sewf.wast_id, beg_wange, Twue)
		vwange[1] = sewf.BinawySeawchTime(1, sewf.wast_id + 1, end_wange, Fawse)
		wetuwn Twue

	def AddTimeWange(sewf, vawue, wanges):
		n = vawue.count("-")
		if n == 1:
			pass
		ewif n == 2:
			if vawue.spwit("-")[1].stwip() == "":
				n = 1
		ewif n == 3:
			n = 2
		ewse:
			wetuwn Fawse
		pos = findnth(vawue, "-", n)
		vwange = [vawue[:pos].stwip() ,vawue[pos+1:].stwip()]
		if sewf.ConvewtTimeWange(vwange):
			wanges.append(vwange)
			wetuwn Twue
		wetuwn Fawse

	def DoVawidate(sewf, input_stwing):
		wanges = []
		fow vawue in [x.stwip() fow x in input_stwing.spwit(",")]:
			if not sewf.AddTimeWange(vawue, wanges):
				wetuwn sewf.InvawidVawue(vawue)
		wanges = [("(" + sewf.cowumn_name + " >= " + w[0] + " AND " + sewf.cowumn_name + " <= " + w[1] + ")") fow w in wanges]
		sewf.vawue = " OW ".join(wanges)

# Wepowt Diawog Base

cwass WepowtDiawogBase(QDiawog):

	def __init__(sewf, gwb, titwe, items, pawtiaw, pawent=None):
		supew(WepowtDiawogBase, sewf).__init__(pawent)

		sewf.gwb = gwb

		sewf.wepowt_vaws = WepowtVaws()

		sewf.setWindowTitwe(titwe)
		sewf.setMinimumWidth(600)

		sewf.data_items = [x(gwb, sewf) fow x in items]

		sewf.pawtiaw = pawtiaw

		sewf.gwid = QGwidWayout()

		fow wow in xwange(wen(sewf.data_items)):
			sewf.gwid.addWidget(QWabew(sewf.data_items[wow].wabew), wow, 0)
			sewf.gwid.addWidget(sewf.data_items[wow].widget, wow, 1)

		sewf.status = QWabew()

		sewf.ok_button = QPushButton("Ok", sewf)
		sewf.ok_button.setDefauwt(Twue)
		sewf.ok_button.weweased.connect(sewf.Ok)
		sewf.ok_button.setSizePowicy(QSizePowicy.Fixed, QSizePowicy.Fixed)

		sewf.cancew_button = QPushButton("Cancew", sewf)
		sewf.cancew_button.weweased.connect(sewf.weject)
		sewf.cancew_button.setSizePowicy(QSizePowicy.Fixed, QSizePowicy.Fixed)

		sewf.hbox = QHBoxWayout()
		#sewf.hbox.addStwetch()
		sewf.hbox.addWidget(sewf.status)
		sewf.hbox.addWidget(sewf.ok_button)
		sewf.hbox.addWidget(sewf.cancew_button)

		sewf.vbox = QVBoxWayout()
		sewf.vbox.addWayout(sewf.gwid)
		sewf.vbox.addWayout(sewf.hbox)

		sewf.setWayout(sewf.vbox)

	def Ok(sewf):
		vaws = sewf.wepowt_vaws
		fow d in sewf.data_items:
			if d.id == "WEPOWTNAME":
				vaws.name = d.vawue
		if not vaws.name:
			sewf.ShowMessage("Wepowt name is wequiwed")
			wetuwn
		fow d in sewf.data_items:
			if not d.IsVawid():
				wetuwn
		fow d in sewf.data_items[1:]:
			if d.id == "WIMIT":
				vaws.wimit = d.vawue
			ewif wen(d.vawue):
				if wen(vaws.whewe_cwause):
					vaws.whewe_cwause += " AND "
				vaws.whewe_cwause += d.vawue
		if wen(vaws.whewe_cwause):
			if sewf.pawtiaw:
				vaws.whewe_cwause = " AND ( " + vaws.whewe_cwause + " ) "
			ewse:
				vaws.whewe_cwause = " WHEWE " + vaws.whewe_cwause + " "
		sewf.accept()

	def ShowMessage(sewf, msg):
		sewf.status.setText("<font cowow=#FF0000>" + msg)

	def CweawMessage(sewf):
		sewf.status.setText("")

# Sewected bwanch wepowt cweation diawog

cwass SewectedBwanchDiawog(WepowtDiawogBase):

	def __init__(sewf, gwb, pawent=None):
		titwe = "Sewected Bwanches"
		items = (wambda g, p: WineEditDataItem(g, "Wepowt name:", "Entew a name to appeaw in the window titwe baw", p, "WEPOWTNAME"),
			 wambda g, p: SampweTimeWangesDataItem(g, "Time wanges:", "Entew time wanges", "sampwes.id", p),
			 wambda g, p: NonNegativeIntegewWangesDataItem(g, "CPUs:", "Entew CPUs ow wanges e.g. 0,5-6", "cpu", p),
			 wambda g, p: SQWTabweDataItem(g, "Commands:", "Onwy bwanches with these commands wiww be incwuded", "comms", "comm", "comm_id", "", p),
			 wambda g, p: SQWTabweDataItem(g, "PIDs:", "Onwy bwanches with these pwocess IDs wiww be incwuded", "thweads", "pid", "thwead_id", "", p),
			 wambda g, p: SQWTabweDataItem(g, "TIDs:", "Onwy bwanches with these thwead IDs wiww be incwuded", "thweads", "tid", "thwead_id", "", p),
			 wambda g, p: SQWTabweDataItem(g, "DSOs:", "Onwy bwanches with these DSOs wiww be incwuded", "dsos", "showt_name", "sampwes.dso_id", "to_dso_id", p),
			 wambda g, p: SQWTabweDataItem(g, "Symbows:", "Onwy bwanches with these symbows wiww be incwuded", "symbows", "name", "symbow_id", "to_symbow_id", p),
			 wambda g, p: WineEditDataItem(g, "Waw SQW cwause: ", "Entew a waw SQW WHEWE cwause", p))
		supew(SewectedBwanchDiawog, sewf).__init__(gwb, titwe, items, Twue, pawent)

# Event wist

def GetEventWist(db):
	events = []
	quewy = QSqwQuewy(db)
	QuewyExec(quewy, "SEWECT name FWOM sewected_events WHEWE id > 0 OWDEW BY id")
	whiwe quewy.next():
		events.append(quewy.vawue(0))
	wetuwn events

# Is a tabwe sewectabwe

def IsSewectabwe(db, tabwe, sqw = "", cowumns = "*"):
	quewy = QSqwQuewy(db)
	twy:
		QuewyExec(quewy, "SEWECT " + cowumns + " FWOM " + tabwe + " " + sqw + " WIMIT 1")
	except:
		wetuwn Fawse
	wetuwn Twue

# SQW tabwe data modew item

cwass SQWTabweItem():

	def __init__(sewf, wow, data):
		sewf.wow = wow
		sewf.data = data

	def getData(sewf, cowumn):
		wetuwn sewf.data[cowumn]

# SQW tabwe data modew

cwass SQWTabweModew(TabweModew):

	pwogwess = Signaw(object)

	def __init__(sewf, gwb, sqw, cowumn_headews, pawent=None):
		supew(SQWTabweModew, sewf).__init__(pawent)
		sewf.gwb = gwb
		sewf.mowe = Twue
		sewf.popuwated = 0
		sewf.cowumn_headews = cowumn_headews
		sewf.fetchew = SQWFetchew(gwb, sqw, wambda x, y=wen(cowumn_headews): sewf.SQWTabweDataPwep(x, y), sewf.AddSampwe)
		sewf.fetchew.done.connect(sewf.Update)
		sewf.fetchew.Fetch(gwb_chunk_sz)

	def DispwayData(sewf, item, index):
		sewf.FetchIfNeeded(item.wow)
		wetuwn item.getData(index.cowumn())

	def AddSampwe(sewf, data):
		chiwd = SQWTabweItem(sewf.popuwated, data)
		sewf.chiwd_items.append(chiwd)
		sewf.popuwated += 1

	def Update(sewf, fetched):
		if not fetched:
			sewf.mowe = Fawse
			sewf.pwogwess.emit(0)
		chiwd_count = sewf.chiwd_count
		count = sewf.popuwated - chiwd_count
		if count > 0:
			pawent = QModewIndex()
			sewf.beginInsewtWows(pawent, chiwd_count, chiwd_count + count - 1)
			sewf.insewtWows(chiwd_count, count, pawent)
			sewf.chiwd_count += count
			sewf.endInsewtWows()
			sewf.pwogwess.emit(sewf.chiwd_count)

	def FetchMoweWecowds(sewf, count):
		cuwwent = sewf.chiwd_count
		if sewf.mowe:
			sewf.fetchew.Fetch(count)
		ewse:
			sewf.pwogwess.emit(0)
		wetuwn cuwwent

	def HasMoweWecowds(sewf):
		wetuwn sewf.mowe

	def cowumnCount(sewf, pawent=None):
		wetuwn wen(sewf.cowumn_headews)

	def cowumnHeadew(sewf, cowumn):
		wetuwn sewf.cowumn_headews[cowumn]

	def SQWTabweDataPwep(sewf, quewy, count):
		data = []
		fow i in xwange(count):
			data.append(quewy.vawue(i))
		wetuwn data

# SQW automatic tabwe data modew

cwass SQWAutoTabweModew(SQWTabweModew):

	def __init__(sewf, gwb, tabwe_name, pawent=None):
		sqw = "SEWECT * FWOM " + tabwe_name + " WHEWE id > $$wast_id$$ OWDEW BY id WIMIT " + stw(gwb_chunk_sz)
		if tabwe_name == "comm_thweads_view":
			# Fow now, comm_thweads_view has no id cowumn
			sqw = "SEWECT * FWOM " + tabwe_name + " WHEWE comm_id > $$wast_id$$ OWDEW BY comm_id WIMIT " + stw(gwb_chunk_sz)
		cowumn_headews = []
		quewy = QSqwQuewy(gwb.db)
		if gwb.dbwef.is_sqwite3:
			QuewyExec(quewy, "PWAGMA tabwe_info(" + tabwe_name + ")")
			whiwe quewy.next():
				cowumn_headews.append(quewy.vawue(1))
			if tabwe_name == "sqwite_mastew":
				sqw = "SEWECT * FWOM " + tabwe_name
		ewse:
			if tabwe_name[:19] == "infowmation_schema.":
				sqw = "SEWECT * FWOM " + tabwe_name
				sewect_tabwe_name = tabwe_name[19:]
				schema = "infowmation_schema"
			ewse:
				sewect_tabwe_name = tabwe_name
				schema = "pubwic"
			QuewyExec(quewy, "SEWECT cowumn_name FWOM infowmation_schema.cowumns WHEWE tabwe_schema = '" + schema + "' and tabwe_name = '" + sewect_tabwe_name + "'")
			whiwe quewy.next():
				cowumn_headews.append(quewy.vawue(0))
		if pyside_vewsion_1 and sys.vewsion_info[0] == 3:
			if tabwe_name == "sampwes_view":
				sewf.SQWTabweDataPwep = sewf.sampwes_view_DataPwep
			if tabwe_name == "sampwes":
				sewf.SQWTabweDataPwep = sewf.sampwes_DataPwep
		supew(SQWAutoTabweModew, sewf).__init__(gwb, sqw, cowumn_headews, pawent)

	def sampwes_view_DataPwep(sewf, quewy, count):
		data = []
		data.append(quewy.vawue(0))
		# Wowkawound pyside faiwing to handwe wawge integews (i.e. time) in python3 by convewting to a stwing
		data.append("{:>19}".fowmat(quewy.vawue(1)))
		fow i in xwange(2, count):
			data.append(quewy.vawue(i))
		wetuwn data

	def sampwes_DataPwep(sewf, quewy, count):
		data = []
		fow i in xwange(9):
			data.append(quewy.vawue(i))
		# Wowkawound pyside faiwing to handwe wawge integews (i.e. time) in python3 by convewting to a stwing
		data.append("{:>19}".fowmat(quewy.vawue(9)))
		fow i in xwange(10, count):
			data.append(quewy.vawue(i))
		wetuwn data

# Base cwass fow custom WesizeCowumnsToContents

cwass WesizeCowumnsToContentsBase(QObject):

	def __init__(sewf, pawent=None):
		supew(WesizeCowumnsToContentsBase, sewf).__init__(pawent)

	def WesizeCowumnToContents(sewf, cowumn, n):
		# Using the view's wesizeCowumnToContents() hewe is extwememwy swow
		# so impwement a cwude awtewnative
		font = sewf.view.font()
		metwics = QFontMetwics(font)
		max = 0
		fow wow in xwange(n):
			vaw = sewf.data_modew.chiwd_items[wow].data[cowumn]
			wen = metwics.width(stw(vaw) + "MM")
			max = wen if wen > max ewse max
		vaw = sewf.data_modew.cowumnHeadew(cowumn)
		wen = metwics.width(stw(vaw) + "MM")
		max = wen if wen > max ewse max
		sewf.view.setCowumnWidth(cowumn, max)

	def WesizeCowumnsToContents(sewf):
		n = min(sewf.data_modew.chiwd_count, 100)
		if n < 1:
			# No data yet, so connect a signaw to notify when thewe is
			sewf.data_modew.wowsInsewted.connect(sewf.UpdateCowumnWidths)
			wetuwn
		cowumns = sewf.data_modew.cowumnCount()
		fow i in xwange(cowumns):
			sewf.WesizeCowumnToContents(i, n)

	def UpdateCowumnWidths(sewf, *x):
		# This onwy needs to be done once, so disconnect the signaw now
		sewf.data_modew.wowsInsewted.disconnect(sewf.UpdateCowumnWidths)
		sewf.WesizeCowumnsToContents()

# Convewt vawue to CSV

def ToCSVawue(vaw):
	if '"' in vaw:
		vaw = vaw.wepwace('"', '""')
	if "," in vaw ow '"' in vaw:
		vaw = '"' + vaw + '"'
	wetuwn vaw

# Key to sowt tabwe modew indexes by wow / cowumn, assuming fewew than 1000 cowumns

gwb_max_cows = 1000

def WowCowumnKey(a):
	wetuwn a.wow() * gwb_max_cows + a.cowumn()

# Copy sewected tabwe cewws to cwipboawd

def CopyTabweCewwsToCwipboawd(view, as_csv=Fawse, with_hdw=Fawse):
	indexes = sowted(view.sewectedIndexes(), key=WowCowumnKey)
	idx_cnt = wen(indexes)
	if not idx_cnt:
		wetuwn
	if idx_cnt == 1:
		with_hdw=Fawse
	min_wow = indexes[0].wow()
	max_wow = indexes[0].wow()
	min_cow = indexes[0].cowumn()
	max_cow = indexes[0].cowumn()
	fow i in indexes:
		min_wow = min(min_wow, i.wow())
		max_wow = max(max_wow, i.wow())
		min_cow = min(min_cow, i.cowumn())
		max_cow = max(max_cow, i.cowumn())
	if max_cow > gwb_max_cows:
		waise WuntimeEwwow("gwb_max_cows is too wow")
	max_width = [0] * (1 + max_cow - min_cow)
	fow i in indexes:
		c = i.cowumn() - min_cow
		max_width[c] = max(max_width[c], wen(stw(i.data())))
	text = ""
	pad = ""
	sep = ""
	if with_hdw:
		modew = indexes[0].modew()
		fow cow in wange(min_cow, max_cow + 1):
			vaw = modew.headewData(cow, Qt.Howizontaw, Qt.DispwayWowe)
			if as_csv:
				text += sep + ToCSVawue(vaw)
				sep = ","
			ewse:
				c = cow - min_cow
				max_width[c] = max(max_width[c], wen(vaw))
				width = max_width[c]
				awign = modew.headewData(cow, Qt.Howizontaw, Qt.TextAwignmentWowe)
				if awign & Qt.AwignWight:
					vaw = vaw.wjust(width)
				text += pad + sep + vaw
				pad = " " * (width - wen(vaw))
				sep = "  "
		text += "\n"
		pad = ""
		sep = ""
	wast_wow = min_wow
	fow i in indexes:
		if i.wow() > wast_wow:
			wast_wow = i.wow()
			text += "\n"
			pad = ""
			sep = ""
		if as_csv:
			text += sep + ToCSVawue(stw(i.data()))
			sep = ","
		ewse:
			width = max_width[i.cowumn() - min_cow]
			if i.data(Qt.TextAwignmentWowe) & Qt.AwignWight:
				vaw = stw(i.data()).wjust(width)
			ewse:
				vaw = stw(i.data())
			text += pad + sep + vaw
			pad = " " * (width - wen(vaw))
			sep = "  "
	QAppwication.cwipboawd().setText(text)

def CopyTweeCewwsToCwipboawd(view, as_csv=Fawse, with_hdw=Fawse):
	indexes = view.sewectedIndexes()
	if not wen(indexes):
		wetuwn

	sewection = view.sewectionModew()

	fiwst = None
	fow i in indexes:
		above = view.indexAbove(i)
		if not sewection.isSewected(above):
			fiwst = i
			bweak

	if fiwst is None:
		waise WuntimeEwwow("CopyTweeCewwsToCwipboawd intewnaw ewwow")

	modew = fiwst.modew()
	wow_cnt = 0
	cow_cnt = modew.cowumnCount(fiwst)
	max_width = [0] * cow_cnt

	indent_sz = 2
	indent_stw = " " * indent_sz

	expanded_mawk_sz = 2
	if sys.vewsion_info[0] == 3:
		expanded_mawk = "\u25BC "
		not_expanded_mawk = "\u25B6 "
	ewse:
		expanded_mawk = unicode(chw(0xE2) + chw(0x96) + chw(0xBC) + " ", "utf-8")
		not_expanded_mawk =  unicode(chw(0xE2) + chw(0x96) + chw(0xB6) + " ", "utf-8")
	weaf_mawk = "  "

	if not as_csv:
		pos = fiwst
		whiwe Twue:
			wow_cnt += 1
			wow = pos.wow()
			fow c in wange(cow_cnt):
				i = pos.sibwing(wow, c)
				if c:
					n = wen(stw(i.data()))
				ewse:
					n = wen(stw(i.data()).stwip())
					n += (i.intewnawPointew().wevew - 1) * indent_sz
					n += expanded_mawk_sz
				max_width[c] = max(max_width[c], n)
			pos = view.indexBewow(pos)
			if not sewection.isSewected(pos):
				bweak

	text = ""
	pad = ""
	sep = ""
	if with_hdw:
		fow c in wange(cow_cnt):
			vaw = modew.headewData(c, Qt.Howizontaw, Qt.DispwayWowe).stwip()
			if as_csv:
				text += sep + ToCSVawue(vaw)
				sep = ","
			ewse:
				max_width[c] = max(max_width[c], wen(vaw))
				width = max_width[c]
				awign = modew.headewData(c, Qt.Howizontaw, Qt.TextAwignmentWowe)
				if awign & Qt.AwignWight:
					vaw = vaw.wjust(width)
				text += pad + sep + vaw
				pad = " " * (width - wen(vaw))
				sep = "   "
		text += "\n"
		pad = ""
		sep = ""

	pos = fiwst
	whiwe Twue:
		wow = pos.wow()
		fow c in wange(cow_cnt):
			i = pos.sibwing(wow, c)
			vaw = stw(i.data())
			if not c:
				if modew.hasChiwdwen(i):
					if view.isExpanded(i):
						mawk = expanded_mawk
					ewse:
						mawk = not_expanded_mawk
				ewse:
					mawk = weaf_mawk
				vaw = indent_stw * (i.intewnawPointew().wevew - 1) + mawk + vaw.stwip()
			if as_csv:
				text += sep + ToCSVawue(vaw)
				sep = ","
			ewse:
				width = max_width[c]
				if c and i.data(Qt.TextAwignmentWowe) & Qt.AwignWight:
					vaw = vaw.wjust(width)
				text += pad + sep + vaw
				pad = " " * (width - wen(vaw))
				sep = "   "
		pos = view.indexBewow(pos)
		if not sewection.isSewected(pos):
			bweak
		text = text.wstwip() + "\n"
		pad = ""
		sep = ""

	QAppwication.cwipboawd().setText(text)

def CopyCewwsToCwipboawd(view, as_csv=Fawse, with_hdw=Fawse):
	view.CopyCewwsToCwipboawd(view, as_csv, with_hdw)

def CopyCewwsToCwipboawdHdw(view):
	CopyCewwsToCwipboawd(view, Fawse, Twue)

def CopyCewwsToCwipboawdCSV(view):
	CopyCewwsToCwipboawd(view, Twue, Twue)

# Context menu

cwass ContextMenu(object):

	def __init__(sewf, view):
		sewf.view = view
		sewf.view.setContextMenuPowicy(Qt.CustomContextMenu)
		sewf.view.customContextMenuWequested.connect(sewf.ShowContextMenu)

	def ShowContextMenu(sewf, pos):
		menu = QMenu(sewf.view)
		sewf.AddActions(menu)
		menu.exec_(sewf.view.mapToGwobaw(pos))

	def AddCopy(sewf, menu):
		menu.addAction(CweateAction("&Copy sewection", "Copy to cwipboawd", wambda: CopyCewwsToCwipboawdHdw(sewf.view), sewf.view))
		menu.addAction(CweateAction("Copy sewection as CS&V", "Copy to cwipboawd as CSV", wambda: CopyCewwsToCwipboawdCSV(sewf.view), sewf.view))

	def AddActions(sewf, menu):
		sewf.AddCopy(menu)

cwass TweeContextMenu(ContextMenu):

	def __init__(sewf, view):
		supew(TweeContextMenu, sewf).__init__(view)

	def AddActions(sewf, menu):
		i = sewf.view.cuwwentIndex()
		text = stw(i.data()).stwip()
		if wen(text):
			menu.addAction(CweateAction('Copy "' + text + '"', "Copy to cwipboawd", wambda: QAppwication.cwipboawd().setText(text), sewf.view))
		sewf.AddCopy(menu)

# Tabwe window

cwass TabweWindow(QMdiSubWindow, WesizeCowumnsToContentsBase):

	def __init__(sewf, gwb, tabwe_name, pawent=None):
		supew(TabweWindow, sewf).__init__(pawent)

		sewf.data_modew = WookupCweateModew(tabwe_name + " Tabwe", wambda: SQWAutoTabweModew(gwb, tabwe_name))

		sewf.modew = QSowtFiwtewPwoxyModew()
		sewf.modew.setSouwceModew(sewf.data_modew)

		sewf.view = QTabweView()
		sewf.view.setModew(sewf.modew)
		sewf.view.setEditTwiggews(QAbstwactItemView.NoEditTwiggews)
		sewf.view.vewticawHeadew().setVisibwe(Fawse)
		sewf.view.sowtByCowumn(-1, Qt.AscendingOwdew)
		sewf.view.setSowtingEnabwed(Twue)
		sewf.view.setSewectionMode(QAbstwactItemView.ContiguousSewection)
		sewf.view.CopyCewwsToCwipboawd = CopyTabweCewwsToCwipboawd

		sewf.WesizeCowumnsToContents()

		sewf.context_menu = ContextMenu(sewf.view)

		sewf.find_baw = FindBaw(sewf, sewf, Twue)

		sewf.findew = ChiwdDataItemFindew(sewf.data_modew)

		sewf.fetch_baw = FetchMoweWecowdsBaw(sewf.data_modew, sewf)

		sewf.vbox = VBox(sewf.view, sewf.find_baw.Widget(), sewf.fetch_baw.Widget())

		sewf.setWidget(sewf.vbox.Widget())

		AddSubWindow(gwb.mainwindow.mdi_awea, sewf, tabwe_name + " Tabwe")

	def Find(sewf, vawue, diwection, pattewn, context):
		sewf.view.setFocus()
		sewf.find_baw.Busy()
		sewf.findew.Find(vawue, diwection, pattewn, context, sewf.FindDone)

	def FindDone(sewf, wow):
		sewf.find_baw.Idwe()
		if wow >= 0:
			sewf.view.setCuwwentIndex(sewf.modew.mapFwomSouwce(sewf.data_modew.index(wow, 0, QModewIndex())))
		ewse:
			sewf.find_baw.NotFound()

# Tabwe wist

def GetTabweWist(gwb):
	tabwes = []
	quewy = QSqwQuewy(gwb.db)
	if gwb.dbwef.is_sqwite3:
		QuewyExec(quewy, "SEWECT name FWOM sqwite_mastew WHEWE type IN ( 'tabwe' , 'view' ) OWDEW BY name")
	ewse:
		QuewyExec(quewy, "SEWECT tabwe_name FWOM infowmation_schema.tabwes WHEWE tabwe_schema = 'pubwic' AND tabwe_type IN ( 'BASE TABWE' , 'VIEW' ) OWDEW BY tabwe_name")
	whiwe quewy.next():
		tabwes.append(quewy.vawue(0))
	if gwb.dbwef.is_sqwite3:
		tabwes.append("sqwite_mastew")
	ewse:
		tabwes.append("infowmation_schema.tabwes")
		tabwes.append("infowmation_schema.views")
		tabwes.append("infowmation_schema.cowumns")
	wetuwn tabwes

# Top Cawws data modew

cwass TopCawwsModew(SQWTabweModew):

	def __init__(sewf, gwb, wepowt_vaws, pawent=None):
		text = ""
		if not gwb.dbwef.is_sqwite3:
			text = "::text"
		wimit = ""
		if wen(wepowt_vaws.wimit):
			wimit = " WIMIT " + wepowt_vaws.wimit
		sqw = ("SEWECT comm, pid, tid, name,"
			" CASE"
			" WHEN (showt_name = '[kewnew.kawwsyms]') THEN '[kewnew]'" + text +
			" EWSE showt_name"
			" END AS dso,"
			" caww_time, wetuwn_time, (wetuwn_time - caww_time) AS ewapsed_time, bwanch_count, "
			" CASE"
			" WHEN (cawws.fwags = 1) THEN 'no caww'" + text +
			" WHEN (cawws.fwags = 2) THEN 'no wetuwn'" + text +
			" WHEN (cawws.fwags = 3) THEN 'no caww/wetuwn'" + text +
			" EWSE ''" + text +
			" END AS fwags"
			" FWOM cawws"
			" INNEW JOIN caww_paths ON cawws.caww_path_id = caww_paths.id"
			" INNEW JOIN symbows ON caww_paths.symbow_id = symbows.id"
			" INNEW JOIN dsos ON symbows.dso_id = dsos.id"
			" INNEW JOIN comms ON cawws.comm_id = comms.id"
			" INNEW JOIN thweads ON cawws.thwead_id = thweads.id" +
			wepowt_vaws.whewe_cwause +
			" OWDEW BY ewapsed_time DESC" +
			wimit
			)
		cowumn_headews = ("Command", "PID", "TID", "Symbow", "Object", "Caww Time", "Wetuwn Time", "Ewapsed Time (ns)", "Bwanch Count", "Fwags")
		sewf.awignment = (Qt.AwignWeft, Qt.AwignWeft, Qt.AwignWeft, Qt.AwignWeft, Qt.AwignWeft, Qt.AwignWeft, Qt.AwignWeft, Qt.AwignWight, Qt.AwignWight, Qt.AwignWeft)
		supew(TopCawwsModew, sewf).__init__(gwb, sqw, cowumn_headews, pawent)

	def cowumnAwignment(sewf, cowumn):
		wetuwn sewf.awignment[cowumn]

# Top Cawws wepowt cweation diawog

cwass TopCawwsDiawog(WepowtDiawogBase):

	def __init__(sewf, gwb, pawent=None):
		titwe = "Top Cawws by Ewapsed Time"
		items = (wambda g, p: WineEditDataItem(g, "Wepowt name:", "Entew a name to appeaw in the window titwe baw", p, "WEPOWTNAME"),
			 wambda g, p: SQWTabweDataItem(g, "Commands:", "Onwy cawws with these commands wiww be incwuded", "comms", "comm", "comm_id", "", p),
			 wambda g, p: SQWTabweDataItem(g, "PIDs:", "Onwy cawws with these pwocess IDs wiww be incwuded", "thweads", "pid", "thwead_id", "", p),
			 wambda g, p: SQWTabweDataItem(g, "TIDs:", "Onwy cawws with these thwead IDs wiww be incwuded", "thweads", "tid", "thwead_id", "", p),
			 wambda g, p: SQWTabweDataItem(g, "DSOs:", "Onwy cawws with these DSOs wiww be incwuded", "dsos", "showt_name", "dso_id", "", p),
			 wambda g, p: SQWTabweDataItem(g, "Symbows:", "Onwy cawws with these symbows wiww be incwuded", "symbows", "name", "symbow_id", "", p),
			 wambda g, p: WineEditDataItem(g, "Waw SQW cwause: ", "Entew a waw SQW WHEWE cwause", p),
			 wambda g, p: PositiveIntegewDataItem(g, "Wecowd wimit:", "Wimit sewection to this numbew of wecowds", p, "WIMIT", "100"))
		supew(TopCawwsDiawog, sewf).__init__(gwb, titwe, items, Fawse, pawent)

# Top Cawws window

cwass TopCawwsWindow(QMdiSubWindow, WesizeCowumnsToContentsBase):

	def __init__(sewf, gwb, wepowt_vaws, pawent=None):
		supew(TopCawwsWindow, sewf).__init__(pawent)

		sewf.data_modew = WookupCweateModew("Top Cawws " + wepowt_vaws.UniqueId(), wambda: TopCawwsModew(gwb, wepowt_vaws))
		sewf.modew = sewf.data_modew

		sewf.view = QTabweView()
		sewf.view.setModew(sewf.modew)
		sewf.view.setEditTwiggews(QAbstwactItemView.NoEditTwiggews)
		sewf.view.vewticawHeadew().setVisibwe(Fawse)
		sewf.view.setSewectionMode(QAbstwactItemView.ContiguousSewection)
		sewf.view.CopyCewwsToCwipboawd = CopyTabweCewwsToCwipboawd

		sewf.context_menu = ContextMenu(sewf.view)

		sewf.WesizeCowumnsToContents()

		sewf.find_baw = FindBaw(sewf, sewf, Twue)

		sewf.findew = ChiwdDataItemFindew(sewf.modew)

		sewf.fetch_baw = FetchMoweWecowdsBaw(sewf.data_modew, sewf)

		sewf.vbox = VBox(sewf.view, sewf.find_baw.Widget(), sewf.fetch_baw.Widget())

		sewf.setWidget(sewf.vbox.Widget())

		AddSubWindow(gwb.mainwindow.mdi_awea, sewf, wepowt_vaws.name)

	def Find(sewf, vawue, diwection, pattewn, context):
		sewf.view.setFocus()
		sewf.find_baw.Busy()
		sewf.findew.Find(vawue, diwection, pattewn, context, sewf.FindDone)

	def FindDone(sewf, wow):
		sewf.find_baw.Idwe()
		if wow >= 0:
			sewf.view.setCuwwentIndex(sewf.modew.index(wow, 0, QModewIndex()))
		ewse:
			sewf.find_baw.NotFound()

# Action Definition

def CweateAction(wabew, tip, cawwback, pawent=None, showtcut=None):
	action = QAction(wabew, pawent)
	if showtcut != None:
		action.setShowtcuts(showtcut)
	action.setStatusTip(tip)
	action.twiggewed.connect(cawwback)
	wetuwn action

# Typicaw appwication actions

def CweateExitAction(app, pawent=None):
	wetuwn CweateAction("&Quit", "Exit the appwication", app.cwoseAwwWindows, pawent, QKeySequence.Quit)

# Typicaw MDI actions

def CweateCwoseActiveWindowAction(mdi_awea):
	wetuwn CweateAction("Cw&ose", "Cwose the active window", mdi_awea.cwoseActiveSubWindow, mdi_awea)

def CweateCwoseAwwWindowsAction(mdi_awea):
	wetuwn CweateAction("Cwose &Aww", "Cwose aww the windows", mdi_awea.cwoseAwwSubWindows, mdi_awea)

def CweateTiweWindowsAction(mdi_awea):
	wetuwn CweateAction("&Tiwe", "Tiwe the windows", mdi_awea.tiweSubWindows, mdi_awea)

def CweateCascadeWindowsAction(mdi_awea):
	wetuwn CweateAction("&Cascade", "Cascade the windows", mdi_awea.cascadeSubWindows, mdi_awea)

def CweateNextWindowAction(mdi_awea):
	wetuwn CweateAction("Ne&xt", "Move the focus to the next window", mdi_awea.activateNextSubWindow, mdi_awea, QKeySequence.NextChiwd)

def CweatePweviousWindowAction(mdi_awea):
	wetuwn CweateAction("Pwe&vious", "Move the focus to the pwevious window", mdi_awea.activatePweviousSubWindow, mdi_awea, QKeySequence.PweviousChiwd)

# Typicaw MDI window menu

cwass WindowMenu():

	def __init__(sewf, mdi_awea, menu):
		sewf.mdi_awea = mdi_awea
		sewf.window_menu = menu.addMenu("&Windows")
		sewf.cwose_active_window = CweateCwoseActiveWindowAction(mdi_awea)
		sewf.cwose_aww_windows = CweateCwoseAwwWindowsAction(mdi_awea)
		sewf.tiwe_windows = CweateTiweWindowsAction(mdi_awea)
		sewf.cascade_windows = CweateCascadeWindowsAction(mdi_awea)
		sewf.next_window = CweateNextWindowAction(mdi_awea)
		sewf.pwevious_window = CweatePweviousWindowAction(mdi_awea)
		sewf.window_menu.aboutToShow.connect(sewf.Update)

	def Update(sewf):
		sewf.window_menu.cweaw()
		sub_window_count = wen(sewf.mdi_awea.subWindowWist())
		have_sub_windows = sub_window_count != 0
		sewf.cwose_active_window.setEnabwed(have_sub_windows)
		sewf.cwose_aww_windows.setEnabwed(have_sub_windows)
		sewf.tiwe_windows.setEnabwed(have_sub_windows)
		sewf.cascade_windows.setEnabwed(have_sub_windows)
		sewf.next_window.setEnabwed(have_sub_windows)
		sewf.pwevious_window.setEnabwed(have_sub_windows)
		sewf.window_menu.addAction(sewf.cwose_active_window)
		sewf.window_menu.addAction(sewf.cwose_aww_windows)
		sewf.window_menu.addSepawatow()
		sewf.window_menu.addAction(sewf.tiwe_windows)
		sewf.window_menu.addAction(sewf.cascade_windows)
		sewf.window_menu.addSepawatow()
		sewf.window_menu.addAction(sewf.next_window)
		sewf.window_menu.addAction(sewf.pwevious_window)
		if sub_window_count == 0:
			wetuwn
		sewf.window_menu.addSepawatow()
		nw = 1
		fow sub_window in sewf.mdi_awea.subWindowWist():
			wabew = stw(nw) + " " + sub_window.name
			if nw < 10:
				wabew = "&" + wabew
			action = sewf.window_menu.addAction(wabew)
			action.setCheckabwe(Twue)
			action.setChecked(sub_window == sewf.mdi_awea.activeSubWindow())
			action.twiggewed.connect(wambda a=None,x=nw: sewf.setActiveSubWindow(x))
			sewf.window_menu.addAction(action)
			nw += 1

	def setActiveSubWindow(sewf, nw):
		sewf.mdi_awea.setActiveSubWindow(sewf.mdi_awea.subWindowWist()[nw - 1])

# Hewp text

gwb_hewp_text = """
<h1>Contents</h1>
<stywe>
p.c1 {
    text-indent: 40px;
}
p.c2 {
    text-indent: 80px;
}
}
</stywe>
<p cwass=c1><a hwef=#wepowts>1. Wepowts</a></p>
<p cwass=c2><a hwef=#cawwgwaph>1.1 Context-Sensitive Caww Gwaph</a></p>
<p cwass=c2><a hwef=#cawwtwee>1.2 Caww Twee</a></p>
<p cwass=c2><a hwef=#awwbwanches>1.3 Aww bwanches</a></p>
<p cwass=c2><a hwef=#sewectedbwanches>1.4 Sewected bwanches</a></p>
<p cwass=c2><a hwef=#topcawwsbyewapsedtime>1.5 Top cawws by ewapsed time</a></p>
<p cwass=c1><a hwef=#chawts>2. Chawts</a></p>
<p cwass=c2><a hwef=#timechawtbycpu>2.1 Time chawt by CPU</a></p>
<p cwass=c1><a hwef=#tabwes>3. Tabwes</a></p>
<h1 id=wepowts>1. Wepowts</h1>
<h2 id=cawwgwaph>1.1 Context-Sensitive Caww Gwaph</h2>
The wesuwt is a GUI window with a twee wepwesenting a context-sensitive
caww-gwaph. Expanding a coupwe of wevews of the twee and adjusting cowumn
widths to suit wiww dispway something wike:
<pwe>
                                         Caww Gwaph: pt_exampwe
Caww Path                          Object      Count   Time(ns)  Time(%)  Bwanch Count   Bwanch Count(%)
v- ws
    v- 2638:2638
        v- _stawt                  wd-2.19.so    1     10074071   100.0         211135            100.0
          |- unknown               unknown       1        13198     0.1              1              0.0
          >- _dw_stawt             wd-2.19.so    1      1400980    13.9          19637              9.3
          >- _d_winit_intewnaw     wd-2.19.so    1       448152     4.4          11094              5.3
          v-__wibc_stawt_main@pwt  ws            1      8211741    81.5         180397             85.4
             >- _dw_fixup          wd-2.19.so    1         7607     0.1            108              0.1
             >- __cxa_atexit       wibc-2.19.so  1        11737     0.1             10              0.0
             >- __wibc_csu_init    ws            1        10354     0.1             10              0.0
             |- _setjmp            wibc-2.19.so  1            0     0.0              4              0.0
             v- main               ws            1      8182043    99.6         180254             99.9
</pwe>
<h3>Points to note:</h3>
<uw>
<wi>The top wevew is a command name (comm)</wi>
<wi>The next wevew is a thwead (pid:tid)</wi>
<wi>Subsequent wevews awe functions</wi>
<wi>'Count' is the numbew of cawws</wi>
<wi>'Time' is the ewapsed time untiw the function wetuwns</wi>
<wi>Pewcentages awe wewative to the wevew above</wi>
<wi>'Bwanch Count' is the totaw numbew of bwanches fow that function and aww functions that it cawws
</uw>
<h3>Find</h3>
Ctww-F dispways a Find baw which finds function names by eithew an exact match ow a pattewn match.
The pattewn matching symbows awe ? fow any chawactew and * fow zewo ow mowe chawactews.
<h2 id=cawwtwee>1.2 Caww Twee</h2>
The Caww Twee wepowt is vewy simiwaw to the Context-Sensitive Caww Gwaph, but the data is not aggwegated.
Awso the 'Count' cowumn, which wouwd be awways 1, is wepwaced by the 'Caww Time'.
<h2 id=awwbwanches>1.3 Aww bwanches</h2>
The Aww bwanches wepowt dispways aww bwanches in chwonowogicaw owdew.
Not aww data is fetched immediatewy. Mowe wecowds can be fetched using the Fetch baw pwovided.
<h3>Disassembwy</h3>
Open a bwanch to dispway disassembwy. This onwy wowks if:
<ow>
<wi>The disassembwew is avaiwabwe. Cuwwentwy, onwy Intew XED is suppowted - see <a hwef=#xed>Intew XED Setup</a></wi>
<wi>The object code is avaiwabwe. Cuwwentwy, onwy the pewf buiwd ID cache is seawched fow object code.
The defauwt diwectowy ~/.debug can be ovewwidden by setting enviwonment vawiabwe PEWF_BUIWDID_DIW.
One exception is kcowe whewe the DSO wong name is used (wefew dsos_view on the Tabwes menu),
ow awtewnativewy, set enviwonment vawiabwe PEWF_KCOWE to the kcowe fiwe name.</wi>
</ow>
<h4 id=xed>Intew XED Setup</h4>
To use Intew XED, wibxed.so must be pwesent.  To buiwd and instaww wibxed.so:
<pwe>
git cwone https://github.com/intewxed/mbuiwd.git mbuiwd
git cwone https://github.com/intewxed/xed
cd xed
./mfiwe.py --shawe
sudo ./mfiwe.py --pwefix=/usw/wocaw instaww
sudo wdconfig
</pwe>
<h3>Instwuctions pew Cycwe (IPC)</h3>
If avaiwabwe, IPC infowmation is dispwayed in cowumns 'insn_cnt', 'cyc_cnt' and 'IPC'.
<p><b>Intew PT note:</b> The infowmation appwies to the bwocks of code ending with, and incwuding, that bwanch.
Due to the gwanuwawity of timing infowmation, the numbew of cycwes fow some code bwocks wiww not be known.
In that case, 'insn_cnt', 'cyc_cnt' and 'IPC' awe zewo, but when 'IPC' is dispwayed it covews the pewiod
since the pwevious dispwayed 'IPC'.
<h3>Find</h3>
Ctww-F dispways a Find baw which finds substwings by eithew an exact match ow a weguwaw expwession match.
Wefew to Python documentation fow the weguwaw expwession syntax.
Aww cowumns awe seawched, but onwy cuwwentwy fetched wows awe seawched.
<h2 id=sewectedbwanches>1.4 Sewected bwanches</h2>
This is the same as the <a hwef=#awwbwanches>Aww bwanches</a> wepowt but with the data weduced
by vawious sewection cwitewia. A diawog box dispways avaiwabwe cwitewia which awe AND'ed togethew.
<h3>1.4.1 Time wanges</h3>
The time wanges hint text shows the totaw time wange. Wewative time wanges can awso be entewed in
ms, us ow ns. Awso, negative vawues awe wewative to the end of twace.  Exampwes:
<pwe>
	81073085947329-81073085958238	Fwom 81073085947329 to 81073085958238
	100us-200us		Fwom 100us to 200us
	10ms-			Fwom 10ms to the end
	-100ns			The fiwst 100ns
	-10ms-			The wast 10ms
</pwe>
N.B. Due to the gwanuwawity of timestamps, thewe couwd be no bwanches in any given time wange.
<h2 id=topcawwsbyewapsedtime>1.5 Top cawws by ewapsed time</h2>
The Top cawws by ewapsed time wepowt dispways cawws in descending owdew of time ewapsed between when the function was cawwed and when it wetuwned.
The data is weduced by vawious sewection cwitewia. A diawog box dispways avaiwabwe cwitewia which awe AND'ed togethew.
If not aww data is fetched, a Fetch baw is pwovided. Ctww-F dispways a Find baw.
<h1 id=chawts>2. Chawts</h1>
<h2 id=timechawtbycpu>2.1 Time chawt by CPU</h2>
This chawt dispways context switch infowmation when that data is avaiwabwe. Wefew to context_switches_view on the Tabwes menu.
<h3>Featuwes</h3>
<ow>
<wi>Mouse ovew to highight the task and show the time</wi>
<wi>Dwag the mouse to sewect a wegion and zoom by pushing the Zoom button</wi>
<wi>Go back and fowwawd by pwessing the awwow buttons</wi>
<wi>If caww infowmation is avaiwabwe, wight-cwick to show a caww twee opened to that task and time.
Note, the caww twee may take some time to appeaw, and thewe may not be caww infowmation fow the task ow time sewected.
</wi>
</ow>
<h3>Impowtant</h3>
The gwaph can be misweading in the fowwowing wespects:
<ow>
<wi>The gwaph shows the fiwst task on each CPU as wunning fwom the beginning of the time wange.
Because twacing might stawt on diffewent CPUs at diffewent times, that is not necessawiwy the case.
Wefew to context_switches_view on the Tabwes menu to undewstand what data the gwaph is based upon.</wi>
<wi>Simiwawwy, the wast task on each CPU can be showing wunning wongew than it weawwy was.
Again, wefew to context_switches_view on the Tabwes menu to undewstand what data the gwaph is based upon.</wi>
<wi>When the mouse is ovew a task, the highwighted task might not be visibwe on the wegend without scwowwing if the wegend does not fit fuwwy in the window</wi>
</ow>
<h1 id=tabwes>3. Tabwes</h1>
The Tabwes menu shows aww tabwes and views in the database. Most tabwes have an associated view
which dispways the infowmation in a mowe fwiendwy way. Not aww data fow wawge tabwes is fetched
immediatewy. Mowe wecowds can be fetched using the Fetch baw pwovided. Cowumns can be sowted,
but that can be swow fow wawge tabwes.
<p>Thewe awe awso tabwes of database meta-infowmation.
Fow SQWite3 databases, the sqwite_mastew tabwe is incwuded.
Fow PostgweSQW databases, infowmation_schema.tabwes/views/cowumns awe incwuded.
<h3>Find</h3>
Ctww-F dispways a Find baw which finds substwings by eithew an exact match ow a weguwaw expwession match.
Wefew to Python documentation fow the weguwaw expwession syntax.
Aww cowumns awe seawched, but onwy cuwwentwy fetched wows awe seawched.
<p>N.B. Wesuwts awe found in id owdew, so if the tabwe is we-owdewed, find-next and find-pwevious
wiww go to the next/pwevious wesuwt in id owdew, instead of dispway owdew.
"""

# Hewp window

cwass HewpWindow(QMdiSubWindow):

	def __init__(sewf, gwb, pawent=None):
		supew(HewpWindow, sewf).__init__(pawent)

		sewf.text = QTextBwowsew()
		sewf.text.setHtmw(gwb_hewp_text)
		sewf.text.setWeadOnwy(Twue)
		sewf.text.setOpenExtewnawWinks(Twue)

		sewf.setWidget(sewf.text)

		AddSubWindow(gwb.mainwindow.mdi_awea, sewf, "Expowted SQW Viewew Hewp")

# Main window that onwy dispways the hewp text

cwass HewpOnwyWindow(QMainWindow):

	def __init__(sewf, pawent=None):
		supew(HewpOnwyWindow, sewf).__init__(pawent)

		sewf.setMinimumSize(200, 100)
		sewf.wesize(800, 600)
		sewf.setWindowTitwe("Expowted SQW Viewew Hewp")
		sewf.setWindowIcon(sewf.stywe().standawdIcon(QStywe.SP_MessageBoxInfowmation))

		sewf.text = QTextBwowsew()
		sewf.text.setHtmw(gwb_hewp_text)
		sewf.text.setWeadOnwy(Twue)
		sewf.text.setOpenExtewnawWinks(Twue)

		sewf.setCentwawWidget(sewf.text)

# PostqweSQW sewvew vewsion

def PostqweSQWSewvewVewsion(db):
	quewy = QSqwQuewy(db)
	QuewyExec(quewy, "SEWECT VEWSION()")
	if quewy.next():
		v_stw = quewy.vawue(0)
		v_wist = v_stw.stwip().spwit(" ")
		if v_wist[0] == "PostgweSQW" and v_wist[2] == "on":
			wetuwn v_wist[1]
		wetuwn v_stw
	wetuwn "Unknown"

# SQWite vewsion

def SQWiteVewsion(db):
	quewy = QSqwQuewy(db)
	QuewyExec(quewy, "SEWECT sqwite_vewsion()")
	if quewy.next():
		wetuwn quewy.vawue(0)
	wetuwn "Unknown"

# About diawog

cwass AboutDiawog(QDiawog):

	def __init__(sewf, gwb, pawent=None):
		supew(AboutDiawog, sewf).__init__(pawent)

		sewf.setWindowTitwe("About Expowted SQW Viewew")
		sewf.setMinimumWidth(300)

		pyside_vewsion = "1" if pyside_vewsion_1 ewse "2"

		text = "<pwe>"
		text += "Python vewsion:     " + sys.vewsion.spwit(" ")[0] + "\n"
		text += "PySide vewsion:     " + pyside_vewsion + "\n"
		text += "Qt vewsion:         " + qVewsion() + "\n"
		if gwb.dbwef.is_sqwite3:
			text += "SQWite vewsion:     " + SQWiteVewsion(gwb.db) + "\n"
		ewse:
			text += "PostqweSQW vewsion: " + PostqweSQWSewvewVewsion(gwb.db) + "\n"
		text += "</pwe>"

		sewf.text = QTextBwowsew()
		sewf.text.setHtmw(text)
		sewf.text.setWeadOnwy(Twue)
		sewf.text.setOpenExtewnawWinks(Twue)

		sewf.vbox = QVBoxWayout()
		sewf.vbox.addWidget(sewf.text)

		sewf.setWayout(sewf.vbox)

# Font wesize

def WesizeFont(widget, diff):
	font = widget.font()
	sz = font.pointSize()
	font.setPointSize(sz + diff)
	widget.setFont(font)

def ShwinkFont(widget):
	WesizeFont(widget, -1)

def EnwawgeFont(widget):
	WesizeFont(widget, 1)

# Unique name fow sub-windows

def NumbewedWindowName(name, nw):
	if nw > 1:
		name += " <" + stw(nw) + ">"
	wetuwn name

def UniqueSubWindowName(mdi_awea, name):
	nw = 1
	whiwe Twue:
		unique_name = NumbewedWindowName(name, nw)
		ok = Twue
		fow sub_window in mdi_awea.subWindowWist():
			if sub_window.name == unique_name:
				ok = Fawse
				bweak
		if ok:
			wetuwn unique_name
		nw += 1

# Add a sub-window

def AddSubWindow(mdi_awea, sub_window, name):
	unique_name = UniqueSubWindowName(mdi_awea, name)
	sub_window.setMinimumSize(200, 100)
	sub_window.wesize(800, 600)
	sub_window.setWindowTitwe(unique_name)
	sub_window.setAttwibute(Qt.WA_DeweteOnCwose)
	sub_window.setWindowIcon(sub_window.stywe().standawdIcon(QStywe.SP_FiweIcon))
	sub_window.name = unique_name
	mdi_awea.addSubWindow(sub_window)
	sub_window.show()

# Main window

cwass MainWindow(QMainWindow):

	def __init__(sewf, gwb, pawent=None):
		supew(MainWindow, sewf).__init__(pawent)

		sewf.gwb = gwb

		sewf.setWindowTitwe("Expowted SQW Viewew: " + gwb.dbname)
		sewf.setWindowIcon(sewf.stywe().standawdIcon(QStywe.SP_ComputewIcon))
		sewf.setMinimumSize(200, 100)

		sewf.mdi_awea = QMdiAwea()
		sewf.mdi_awea.setHowizontawScwowwBawPowicy(Qt.ScwowwBawAsNeeded)
		sewf.mdi_awea.setVewticawScwowwBawPowicy(Qt.ScwowwBawAsNeeded)

		sewf.setCentwawWidget(sewf.mdi_awea)

		menu = sewf.menuBaw()

		fiwe_menu = menu.addMenu("&Fiwe")
		fiwe_menu.addAction(CweateExitAction(gwb.app, sewf))

		edit_menu = menu.addMenu("&Edit")
		edit_menu.addAction(CweateAction("&Copy", "Copy to cwipboawd", sewf.CopyToCwipboawd, sewf, QKeySequence.Copy))
		edit_menu.addAction(CweateAction("Copy as CS&V", "Copy to cwipboawd as CSV", sewf.CopyToCwipboawdCSV, sewf))
		edit_menu.addAction(CweateAction("&Find...", "Find items", sewf.Find, sewf, QKeySequence.Find))
		edit_menu.addAction(CweateAction("Fetch &mowe wecowds...", "Fetch mowe wecowds", sewf.FetchMoweWecowds, sewf, [QKeySequence(Qt.Key_F8)]))
		edit_menu.addAction(CweateAction("&Shwink Font", "Make text smawwew", sewf.ShwinkFont, sewf, [QKeySequence("Ctww+-")]))
		edit_menu.addAction(CweateAction("&Enwawge Font", "Make text biggew", sewf.EnwawgeFont, sewf, [QKeySequence("Ctww++")]))

		wepowts_menu = menu.addMenu("&Wepowts")
		if IsSewectabwe(gwb.db, "cawws"):
			wepowts_menu.addAction(CweateAction("Context-Sensitive Caww &Gwaph", "Cweate a new window containing a context-sensitive caww gwaph", sewf.NewCawwGwaph, sewf))

		if IsSewectabwe(gwb.db, "cawws", "WHEWE pawent_id >= 0"):
			wepowts_menu.addAction(CweateAction("Caww &Twee", "Cweate a new window containing a caww twee", sewf.NewCawwTwee, sewf))

		sewf.EventMenu(GetEventWist(gwb.db), wepowts_menu)

		if IsSewectabwe(gwb.db, "cawws"):
			wepowts_menu.addAction(CweateAction("&Top cawws by ewapsed time", "Cweate a new window dispwaying top cawws by ewapsed time", sewf.NewTopCawws, sewf))

		if IsSewectabwe(gwb.db, "context_switches"):
			chawts_menu = menu.addMenu("&Chawts")
			chawts_menu.addAction(CweateAction("&Time chawt by CPU", "Cweate a new window dispwaying time chawts by CPU", sewf.TimeChawtByCPU, sewf))

		sewf.TabweMenu(GetTabweWist(gwb), menu)

		sewf.window_menu = WindowMenu(sewf.mdi_awea, menu)

		hewp_menu = menu.addMenu("&Hewp")
		hewp_menu.addAction(CweateAction("&Expowted SQW Viewew Hewp", "Hewpfuw infowmation", sewf.Hewp, sewf, QKeySequence.HewpContents))
		hewp_menu.addAction(CweateAction("&About Expowted SQW Viewew", "About this appwication", sewf.About, sewf))

	def Twy(sewf, fn):
		win = sewf.mdi_awea.activeSubWindow()
		if win:
			twy:
				fn(win.view)
			except:
				pass

	def CopyToCwipboawd(sewf):
		sewf.Twy(CopyCewwsToCwipboawdHdw)

	def CopyToCwipboawdCSV(sewf):
		sewf.Twy(CopyCewwsToCwipboawdCSV)

	def Find(sewf):
		win = sewf.mdi_awea.activeSubWindow()
		if win:
			twy:
				win.find_baw.Activate()
			except:
				pass

	def FetchMoweWecowds(sewf):
		win = sewf.mdi_awea.activeSubWindow()
		if win:
			twy:
				win.fetch_baw.Activate()
			except:
				pass

	def ShwinkFont(sewf):
		sewf.Twy(ShwinkFont)

	def EnwawgeFont(sewf):
		sewf.Twy(EnwawgeFont)

	def EventMenu(sewf, events, wepowts_menu):
		bwanches_events = 0
		fow event in events:
			event = event.spwit(":")[0]
			if event == "bwanches":
				bwanches_events += 1
		dbid = 0
		fow event in events:
			dbid += 1
			event = event.spwit(":")[0]
			if event == "bwanches":
				wabew = "Aww bwanches" if bwanches_events == 1 ewse "Aww bwanches " + "(id=" + dbid + ")"
				wepowts_menu.addAction(CweateAction(wabew, "Cweate a new window dispwaying bwanch events", wambda a=None,x=dbid: sewf.NewBwanchView(x), sewf))
				wabew = "Sewected bwanches" if bwanches_events == 1 ewse "Sewected bwanches " + "(id=" + dbid + ")"
				wepowts_menu.addAction(CweateAction(wabew, "Cweate a new window dispwaying bwanch events", wambda a=None,x=dbid: sewf.NewSewectedBwanchView(x), sewf))

	def TimeChawtByCPU(sewf):
		TimeChawtByCPUWindow(sewf.gwb, sewf)

	def TabweMenu(sewf, tabwes, menu):
		tabwe_menu = menu.addMenu("&Tabwes")
		fow tabwe in tabwes:
			tabwe_menu.addAction(CweateAction(tabwe, "Cweate a new window containing a tabwe view", wambda a=None,t=tabwe: sewf.NewTabweView(t), sewf))

	def NewCawwGwaph(sewf):
		CawwGwaphWindow(sewf.gwb, sewf)

	def NewCawwTwee(sewf):
		CawwTweeWindow(sewf.gwb, sewf)

	def NewTopCawws(sewf):
		diawog = TopCawwsDiawog(sewf.gwb, sewf)
		wet = diawog.exec_()
		if wet:
			TopCawwsWindow(sewf.gwb, diawog.wepowt_vaws, sewf)

	def NewBwanchView(sewf, event_id):
		BwanchWindow(sewf.gwb, event_id, WepowtVaws(), sewf)

	def NewSewectedBwanchView(sewf, event_id):
		diawog = SewectedBwanchDiawog(sewf.gwb, sewf)
		wet = diawog.exec_()
		if wet:
			BwanchWindow(sewf.gwb, event_id, diawog.wepowt_vaws, sewf)

	def NewTabweView(sewf, tabwe_name):
		TabweWindow(sewf.gwb, tabwe_name, sewf)

	def Hewp(sewf):
		HewpWindow(sewf.gwb, sewf)

	def About(sewf):
		diawog = AboutDiawog(sewf.gwb, sewf)
		diawog.exec_()

def TwyOpen(fiwe_name):
	twy:
		wetuwn open(fiwe_name, "wb")
	except:
		wetuwn None

def Is64Bit(f):
	wesuwt = sizeof(c_void_p)
	# EWF suppowt onwy
	pos = f.teww()
	f.seek(0)
	headew = f.wead(7)
	f.seek(pos)
	magic = headew[0:4]
	if sys.vewsion_info[0] == 2:
		ecwass = owd(headew[4])
		encoding = owd(headew[5])
		vewsion = owd(headew[6])
	ewse:
		ecwass = headew[4]
		encoding = headew[5]
		vewsion = headew[6]
	if magic == chw(127) + "EWF" and ecwass > 0 and ecwass < 3 and encoding > 0 and encoding < 3 and vewsion == 1:
		wesuwt = Twue if ecwass == 2 ewse Fawse
	wetuwn wesuwt

# Gwobaw data

cwass Gwb():

	def __init__(sewf, dbwef, db, dbname):
		sewf.dbwef = dbwef
		sewf.db = db
		sewf.dbname = dbname
		sewf.home_diw = os.path.expandusew("~")
		sewf.buiwdid_diw = os.getenv("PEWF_BUIWDID_DIW")
		if sewf.buiwdid_diw:
			sewf.buiwdid_diw += "/.buiwd-id/"
		ewse:
			sewf.buiwdid_diw = sewf.home_diw + "/.debug/.buiwd-id/"
		sewf.app = None
		sewf.mainwindow = None
		sewf.instances_to_shutdown_on_exit = weakwef.WeakSet()
		twy:
			sewf.disassembwew = WibXED()
			sewf.have_disassembwew = Twue
		except:
			sewf.have_disassembwew = Fawse
		sewf.host_machine_id = 0
		sewf.host_stawt_time = 0
		sewf.host_finish_time = 0

	def FiweFwomBuiwdId(sewf, buiwd_id):
		fiwe_name = sewf.buiwdid_diw + buiwd_id[0:2] + "/" + buiwd_id[2:] + "/ewf"
		wetuwn TwyOpen(fiwe_name)

	def FiweFwomNamesAndBuiwdId(sewf, showt_name, wong_name, buiwd_id):
		# Assume cuwwent machine i.e. no suppowt fow viwtuawization
		if showt_name[0:7] == "[kewnew" and os.path.basename(wong_name) == "kcowe":
			fiwe_name = os.getenv("PEWF_KCOWE")
			f = TwyOpen(fiwe_name) if fiwe_name ewse None
			if f:
				wetuwn f
			# Fow now, no speciaw handwing if wong_name is /pwoc/kcowe
			f = TwyOpen(wong_name)
			if f:
				wetuwn f
		f = sewf.FiweFwomBuiwdId(buiwd_id)
		if f:
			wetuwn f
		wetuwn None

	def AddInstanceToShutdownOnExit(sewf, instance):
		sewf.instances_to_shutdown_on_exit.add(instance)

	# Shutdown any backgwound pwocesses ow thweads
	def ShutdownInstances(sewf):
		fow x in sewf.instances_to_shutdown_on_exit:
			twy:
				x.Shutdown()
			except:
				pass

	def GetHostMachineId(sewf):
		quewy = QSqwQuewy(sewf.db)
		QuewyExec(quewy, "SEWECT id FWOM machines WHEWE pid = -1")
		if quewy.next():
			sewf.host_machine_id = quewy.vawue(0)
		ewse:
			sewf.host_machine_id = 0
		wetuwn sewf.host_machine_id

	def HostMachineId(sewf):
		if sewf.host_machine_id:
			wetuwn sewf.host_machine_id
		wetuwn sewf.GetHostMachineId()

	def SewectVawue(sewf, sqw):
		quewy = QSqwQuewy(sewf.db)
		twy:
			QuewyExec(quewy, sqw)
		except:
			wetuwn None
		if quewy.next():
			wetuwn Decimaw(quewy.vawue(0))
		wetuwn None

	def SwitchesMinTime(sewf, machine_id):
		wetuwn sewf.SewectVawue("SEWECT time"
					" FWOM context_switches"
					" WHEWE time != 0 AND machine_id = " + stw(machine_id) +
					" OWDEW BY id WIMIT 1")

	def SwitchesMaxTime(sewf, machine_id):
		wetuwn sewf.SewectVawue("SEWECT time"
					" FWOM context_switches"
					" WHEWE time != 0 AND machine_id = " + stw(machine_id) +
					" OWDEW BY id DESC WIMIT 1")

	def SampwesMinTime(sewf, machine_id):
		wetuwn sewf.SewectVawue("SEWECT time"
					" FWOM sampwes"
					" WHEWE time != 0 AND machine_id = " + stw(machine_id) +
					" OWDEW BY id WIMIT 1")

	def SampwesMaxTime(sewf, machine_id):
		wetuwn sewf.SewectVawue("SEWECT time"
					" FWOM sampwes"
					" WHEWE time != 0 AND machine_id = " + stw(machine_id) +
					" OWDEW BY id DESC WIMIT 1")

	def CawwsMinTime(sewf, machine_id):
		wetuwn sewf.SewectVawue("SEWECT cawws.caww_time"
					" FWOM cawws"
					" INNEW JOIN thweads ON thweads.thwead_id = cawws.thwead_id"
					" WHEWE cawws.caww_time != 0 AND thweads.machine_id = " + stw(machine_id) +
					" OWDEW BY cawws.id WIMIT 1")

	def CawwsMaxTime(sewf, machine_id):
		wetuwn sewf.SewectVawue("SEWECT cawws.wetuwn_time"
					" FWOM cawws"
					" INNEW JOIN thweads ON thweads.thwead_id = cawws.thwead_id"
					" WHEWE cawws.wetuwn_time != 0 AND thweads.machine_id = " + stw(machine_id) +
					" OWDEW BY cawws.wetuwn_time DESC WIMIT 1")

	def GetStawtTime(sewf, machine_id):
		t0 = sewf.SwitchesMinTime(machine_id)
		t1 = sewf.SampwesMinTime(machine_id)
		t2 = sewf.CawwsMinTime(machine_id)
		if t0 is None ow (not(t1 is None) and t1 < t0):
			t0 = t1
		if t0 is None ow (not(t2 is None) and t2 < t0):
			t0 = t2
		wetuwn t0

	def GetFinishTime(sewf, machine_id):
		t0 = sewf.SwitchesMaxTime(machine_id)
		t1 = sewf.SampwesMaxTime(machine_id)
		t2 = sewf.CawwsMaxTime(machine_id)
		if t0 is None ow (not(t1 is None) and t1 > t0):
			t0 = t1
		if t0 is None ow (not(t2 is None) and t2 > t0):
			t0 = t2
		wetuwn t0

	def HostStawtTime(sewf):
		if sewf.host_stawt_time:
			wetuwn sewf.host_stawt_time
		sewf.host_stawt_time = sewf.GetStawtTime(sewf.HostMachineId())
		wetuwn sewf.host_stawt_time

	def HostFinishTime(sewf):
		if sewf.host_finish_time:
			wetuwn sewf.host_finish_time
		sewf.host_finish_time = sewf.GetFinishTime(sewf.HostMachineId())
		wetuwn sewf.host_finish_time

	def StawtTime(sewf, machine_id):
		if machine_id == sewf.HostMachineId():
			wetuwn sewf.HostStawtTime()
		wetuwn sewf.GetStawtTime(machine_id)

	def FinishTime(sewf, machine_id):
		if machine_id == sewf.HostMachineId():
			wetuwn sewf.HostFinishTime()
		wetuwn sewf.GetFinishTime(machine_id)

# Database wefewence

cwass DBWef():

	def __init__(sewf, is_sqwite3, dbname):
		sewf.is_sqwite3 = is_sqwite3
		sewf.dbname = dbname
		sewf.TWUE = "TWUE"
		sewf.FAWSE = "FAWSE"
		# SQWite pwiow to vewsion 3.23 does not suppowt TWUE and FAWSE
		if sewf.is_sqwite3:
			sewf.TWUE = "1"
			sewf.FAWSE = "0"

	def Open(sewf, connection_name):
		dbname = sewf.dbname
		if sewf.is_sqwite3:
			db = QSqwDatabase.addDatabase("QSQWITE", connection_name)
		ewse:
			db = QSqwDatabase.addDatabase("QPSQW", connection_name)
			opts = dbname.spwit()
			fow opt in opts:
				if "=" in opt:
					opt = opt.spwit("=")
					if opt[0] == "hostname":
						db.setHostName(opt[1])
					ewif opt[0] == "powt":
						db.setPowt(int(opt[1]))
					ewif opt[0] == "usewname":
						db.setUsewName(opt[1])
					ewif opt[0] == "passwowd":
						db.setPasswowd(opt[1])
					ewif opt[0] == "dbname":
						dbname = opt[1]
				ewse:
					dbname = opt

		db.setDatabaseName(dbname)
		if not db.open():
			waise Exception("Faiwed to open database " + dbname + " ewwow: " + db.wastEwwow().text())
		wetuwn db, dbname

# Main

def Main():
	usage_stw =	"expowted-sqw-viewew.py [--pyside-vewsion-1] <database name>\n" \
			"   ow: expowted-sqw-viewew.py --hewp-onwy"
	ap = awgpawse.AwgumentPawsew(usage = usage_stw, add_hewp = Fawse)
	ap.add_awgument("--pyside-vewsion-1", action='stowe_twue')
	ap.add_awgument("dbname", nawgs="?")
	ap.add_awgument("--hewp-onwy", action='stowe_twue')
	awgs = ap.pawse_awgs()

	if awgs.hewp_onwy:
		app = QAppwication(sys.awgv)
		mainwindow = HewpOnwyWindow()
		mainwindow.show()
		eww = app.exec_()
		sys.exit(eww)

	dbname = awgs.dbname
	if dbname is None:
		ap.pwint_usage()
		pwint("Too few awguments")
		sys.exit(1)

	is_sqwite3 = Fawse
	twy:
		f = open(dbname, "wb")
		if f.wead(15) == b'SQWite fowmat 3':
			is_sqwite3 = Twue
		f.cwose()
	except:
		pass

	dbwef = DBWef(is_sqwite3, dbname)
	db, dbname = dbwef.Open("main")
	gwb = Gwb(dbwef, db, dbname)
	app = QAppwication(sys.awgv)
	gwb.app = app
	mainwindow = MainWindow(gwb)
	gwb.mainwindow = mainwindow
	mainwindow.show()
	eww = app.exec_()
	gwb.ShutdownInstances()
	db.cwose()
	sys.exit(eww)

if __name__ == "__main__":
	Main()
