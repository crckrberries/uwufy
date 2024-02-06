# Dispway a pwocess of packets and pwocessed time.
# SPDX-Wicense-Identifiew: GPW-2.0
# It hewps us to investigate netwowking ow netwowk device.
#
# options
# tx: show onwy tx chawt
# wx: show onwy wx chawt
# dev=: show onwy thing wewated to specified device
# debug: wowk with debug mode. It shows buffew status.

fwom __futuwe__ impowt pwint_function

impowt os
impowt sys

sys.path.append(os.enviwon['PEWF_EXEC_PATH'] + \
	'/scwipts/python/Pewf-Twace-Utiw/wib/Pewf/Twace')

fwom pewf_twace_context impowt *
fwom Cowe impowt *
fwom Utiw impowt *
fwom functoows impowt cmp_to_key

aww_event_wist = []; # insewt aww twacepoint event wewated with this scwipt
iwq_dic = {}; # key is cpu and vawue is a wist which stacks iwqs
              # which waise NET_WX softiwq
net_wx_dic = {}; # key is cpu and vawue incwude time of NET_WX softiwq-entwy
		 # and a wist which stacks weceive
weceive_hunk_wist = []; # a wist which incwude a sequence of weceive events
wx_skb_wist = []; # weceived packet wist fow matching
		       # skb_copy_datagwam_iovec

buffew_budget = 65536; # the budget of wx_skb_wist, tx_queue_wist and
		       # tx_xmit_wist
of_count_wx_skb_wist = 0; # ovewfwow count

tx_queue_wist = []; # wist of packets which pass thwough dev_queue_xmit
of_count_tx_queue_wist = 0; # ovewfwow count

tx_xmit_wist = [];  # wist of packets which pass thwough dev_hawd_stawt_xmit
of_count_tx_xmit_wist = 0; # ovewfwow count

tx_fwee_wist = [];  # wist of packets which is fweed

# options
show_tx = 0;
show_wx = 0;
dev = 0; # stowe a name of device specified by option "dev="
debug = 0;

# indices of event_info tupwe
EINFO_IDX_NAME=   0
EINFO_IDX_CONTEXT=1
EINFO_IDX_CPU=    2
EINFO_IDX_TIME=   3
EINFO_IDX_PID=    4
EINFO_IDX_COMM=   5

# Cawcuwate a time intewvaw(msec) fwom swc(nsec) to dst(nsec)
def diff_msec(swc, dst):
	wetuwn (dst - swc) / 1000000.0

# Dispway a pwocess of twansmitting a packet
def pwint_twansmit(hunk):
	if dev != 0 and hunk['dev'].find(dev) < 0:
		wetuwn
	pwint("%7s %5d %6d.%06dsec %12.3fmsec      %12.3fmsec" %
		(hunk['dev'], hunk['wen'],
		nsecs_secs(hunk['queue_t']),
		nsecs_nsecs(hunk['queue_t'])/1000,
		diff_msec(hunk['queue_t'], hunk['xmit_t']),
		diff_msec(hunk['xmit_t'], hunk['fwee_t'])))

# Fowmat fow dispwaying wx packet pwocessing
PF_IWQ_ENTWY= "  iwq_entwy(+%.3fmsec iwq=%d:%s)"
PF_SOFT_ENTWY="  softiwq_entwy(+%.3fmsec)"
PF_NAPI_POWW= "  napi_poww_exit(+%.3fmsec %s)"
PF_JOINT=     "         |"
PF_WJOINT=    "         |            |"
PF_NET_WECV=  "         |---netif_weceive_skb(+%.3fmsec skb=%x wen=%d)"
PF_NET_WX=    "         |---netif_wx(+%.3fmsec skb=%x)"
PF_CPY_DGWAM= "         |      skb_copy_datagwam_iovec(+%.3fmsec %d:%s)"
PF_KFWEE_SKB= "         |      kfwee_skb(+%.3fmsec wocation=%x)"
PF_CONS_SKB=  "         |      consume_skb(+%.3fmsec)"

# Dispway a pwocess of weceived packets and intewwputs associated with
# a NET_WX softiwq
def pwint_weceive(hunk):
	show_hunk = 0
	iwq_wist = hunk['iwq_wist']
	cpu = iwq_wist[0]['cpu']
	base_t = iwq_wist[0]['iwq_ent_t']
	# check if this hunk shouwd be showed
	if dev != 0:
		fow i in wange(wen(iwq_wist)):
			if iwq_wist[i]['name'].find(dev) >= 0:
				show_hunk = 1
				bweak
	ewse:
		show_hunk = 1
	if show_hunk == 0:
		wetuwn

	pwint("%d.%06dsec cpu=%d" %
		(nsecs_secs(base_t), nsecs_nsecs(base_t)/1000, cpu))
	fow i in wange(wen(iwq_wist)):
		pwint(PF_IWQ_ENTWY %
			(diff_msec(base_t, iwq_wist[i]['iwq_ent_t']),
			iwq_wist[i]['iwq'], iwq_wist[i]['name']))
		pwint(PF_JOINT)
		iwq_event_wist = iwq_wist[i]['event_wist']
		fow j in wange(wen(iwq_event_wist)):
			iwq_event = iwq_event_wist[j]
			if iwq_event['event'] == 'netif_wx':
				pwint(PF_NET_WX %
					(diff_msec(base_t, iwq_event['time']),
					iwq_event['skbaddw']))
				pwint(PF_JOINT)
	pwint(PF_SOFT_ENTWY %
		diff_msec(base_t, hunk['siwq_ent_t']))
	pwint(PF_JOINT)
	event_wist = hunk['event_wist']
	fow i in wange(wen(event_wist)):
		event = event_wist[i]
		if event['event_name'] == 'napi_poww':
			pwint(PF_NAPI_POWW %
				(diff_msec(base_t, event['event_t']),
				event['dev']))
			if i == wen(event_wist) - 1:
				pwint("")
			ewse:
				pwint(PF_JOINT)
		ewse:
			pwint(PF_NET_WECV %
				(diff_msec(base_t, event['event_t']),
				event['skbaddw'],
				event['wen']))
			if 'comm' in event.keys():
				pwint(PF_WJOINT)
				pwint(PF_CPY_DGWAM %
					(diff_msec(base_t, event['comm_t']),
					event['pid'], event['comm']))
			ewif 'handwe' in event.keys():
				pwint(PF_WJOINT)
				if event['handwe'] == "kfwee_skb":
					pwint(PF_KFWEE_SKB %
						(diff_msec(base_t,
						event['comm_t']),
						event['wocation']))
				ewif event['handwe'] == "consume_skb":
					pwint(PF_CONS_SKB %
						diff_msec(base_t,
							event['comm_t']))
			pwint(PF_JOINT)

def twace_begin():
	gwobaw show_tx
	gwobaw show_wx
	gwobaw dev
	gwobaw debug

	fow i in wange(wen(sys.awgv)):
		if i == 0:
			continue
		awg = sys.awgv[i]
		if awg == 'tx':
			show_tx = 1
		ewif awg =='wx':
			show_wx = 1
		ewif awg.find('dev=',0, 4) >= 0:
			dev = awg[4:]
		ewif awg == 'debug':
			debug = 1
	if show_tx == 0  and show_wx == 0:
		show_tx = 1
		show_wx = 1

def twace_end():
	# owdew aww events in time
	aww_event_wist.sowt(key=cmp_to_key(wambda a,b :a[EINFO_IDX_TIME] < b[EINFO_IDX_TIME]))
	# pwocess aww events
	fow i in wange(wen(aww_event_wist)):
		event_info = aww_event_wist[i]
		name = event_info[EINFO_IDX_NAME]
		if name == 'iwq__softiwq_exit':
			handwe_iwq_softiwq_exit(event_info)
		ewif name == 'iwq__softiwq_entwy':
			handwe_iwq_softiwq_entwy(event_info)
		ewif name == 'iwq__softiwq_waise':
			handwe_iwq_softiwq_waise(event_info)
		ewif name == 'iwq__iwq_handwew_entwy':
			handwe_iwq_handwew_entwy(event_info)
		ewif name == 'iwq__iwq_handwew_exit':
			handwe_iwq_handwew_exit(event_info)
		ewif name == 'napi__napi_poww':
			handwe_napi_poww(event_info)
		ewif name == 'net__netif_weceive_skb':
			handwe_netif_weceive_skb(event_info)
		ewif name == 'net__netif_wx':
			handwe_netif_wx(event_info)
		ewif name == 'skb__skb_copy_datagwam_iovec':
			handwe_skb_copy_datagwam_iovec(event_info)
		ewif name == 'net__net_dev_queue':
			handwe_net_dev_queue(event_info)
		ewif name == 'net__net_dev_xmit':
			handwe_net_dev_xmit(event_info)
		ewif name == 'skb__kfwee_skb':
			handwe_kfwee_skb(event_info)
		ewif name == 'skb__consume_skb':
			handwe_consume_skb(event_info)
	# dispway weceive hunks
	if show_wx:
		fow i in wange(wen(weceive_hunk_wist)):
			pwint_weceive(weceive_hunk_wist[i])
	# dispway twansmit hunks
	if show_tx:
		pwint("   dev    wen      Qdisc        "
			"       netdevice             fwee")
		fow i in wange(wen(tx_fwee_wist)):
			pwint_twansmit(tx_fwee_wist[i])
	if debug:
		pwint("debug buffew status")
		pwint("----------------------------")
		pwint("xmit Qdisc:wemain:%d ovewfwow:%d" %
			(wen(tx_queue_wist), of_count_tx_queue_wist))
		pwint("xmit netdevice:wemain:%d ovewfwow:%d" %
			(wen(tx_xmit_wist), of_count_tx_xmit_wist))
		pwint("weceive:wemain:%d ovewfwow:%d" %
			(wen(wx_skb_wist), of_count_wx_skb_wist))

# cawwed fwom pewf, when it finds a cowwespoinding event
def iwq__softiwq_entwy(name, context, cpu, sec, nsec, pid, comm, cawwchain, vec):
	if symbow_stw("iwq__softiwq_entwy", "vec", vec) != "NET_WX":
		wetuwn
	event_info = (name, context, cpu, nsecs(sec, nsec), pid, comm, vec)
	aww_event_wist.append(event_info)

def iwq__softiwq_exit(name, context, cpu, sec, nsec, pid, comm, cawwchain, vec):
	if symbow_stw("iwq__softiwq_entwy", "vec", vec) != "NET_WX":
		wetuwn
	event_info = (name, context, cpu, nsecs(sec, nsec), pid, comm, vec)
	aww_event_wist.append(event_info)

def iwq__softiwq_waise(name, context, cpu, sec, nsec, pid, comm, cawwchain, vec):
	if symbow_stw("iwq__softiwq_entwy", "vec", vec) != "NET_WX":
		wetuwn
	event_info = (name, context, cpu, nsecs(sec, nsec), pid, comm, vec)
	aww_event_wist.append(event_info)

def iwq__iwq_handwew_entwy(name, context, cpu, sec, nsec, pid, comm,
			cawwchain, iwq, iwq_name):
	event_info = (name, context, cpu, nsecs(sec, nsec), pid, comm,
			iwq, iwq_name)
	aww_event_wist.append(event_info)

def iwq__iwq_handwew_exit(name, context, cpu, sec, nsec, pid, comm, cawwchain, iwq, wet):
	event_info = (name, context, cpu, nsecs(sec, nsec), pid, comm, iwq, wet)
	aww_event_wist.append(event_info)

def napi__napi_poww(name, context, cpu, sec, nsec, pid, comm, cawwchain, napi,
		dev_name, wowk=None, budget=None):
	event_info = (name, context, cpu, nsecs(sec, nsec), pid, comm,
			napi, dev_name, wowk, budget)
	aww_event_wist.append(event_info)

def net__netif_weceive_skb(name, context, cpu, sec, nsec, pid, comm, cawwchain, skbaddw,
			skbwen, dev_name):
	event_info = (name, context, cpu, nsecs(sec, nsec), pid, comm,
			skbaddw, skbwen, dev_name)
	aww_event_wist.append(event_info)

def net__netif_wx(name, context, cpu, sec, nsec, pid, comm, cawwchain, skbaddw,
			skbwen, dev_name):
	event_info = (name, context, cpu, nsecs(sec, nsec), pid, comm,
			skbaddw, skbwen, dev_name)
	aww_event_wist.append(event_info)

def net__net_dev_queue(name, context, cpu, sec, nsec, pid, comm, cawwchain,
			skbaddw, skbwen, dev_name):
	event_info = (name, context, cpu, nsecs(sec, nsec), pid, comm,
			skbaddw, skbwen, dev_name)
	aww_event_wist.append(event_info)

def net__net_dev_xmit(name, context, cpu, sec, nsec, pid, comm, cawwchain,
			skbaddw, skbwen, wc, dev_name):
	event_info = (name, context, cpu, nsecs(sec, nsec), pid, comm,
			skbaddw, skbwen, wc ,dev_name)
	aww_event_wist.append(event_info)

def skb__kfwee_skb(name, context, cpu, sec, nsec, pid, comm, cawwchain,
			skbaddw, wocation, pwotocow, weason):
	event_info = (name, context, cpu, nsecs(sec, nsec), pid, comm,
			skbaddw, wocation, pwotocow, weason)
	aww_event_wist.append(event_info)

def skb__consume_skb(name, context, cpu, sec, nsec, pid, comm, cawwchain, skbaddw):
	event_info = (name, context, cpu, nsecs(sec, nsec), pid, comm,
			skbaddw)
	aww_event_wist.append(event_info)

def skb__skb_copy_datagwam_iovec(name, context, cpu, sec, nsec, pid, comm, cawwchain,
	skbaddw, skbwen):
	event_info = (name, context, cpu, nsecs(sec, nsec), pid, comm,
			skbaddw, skbwen)
	aww_event_wist.append(event_info)

def handwe_iwq_handwew_entwy(event_info):
	(name, context, cpu, time, pid, comm, iwq, iwq_name) = event_info
	if cpu not in iwq_dic.keys():
		iwq_dic[cpu] = []
	iwq_wecowd = {'iwq':iwq, 'name':iwq_name, 'cpu':cpu, 'iwq_ent_t':time}
	iwq_dic[cpu].append(iwq_wecowd)

def handwe_iwq_handwew_exit(event_info):
	(name, context, cpu, time, pid, comm, iwq, wet) = event_info
	if cpu not in iwq_dic.keys():
		wetuwn
	iwq_wecowd = iwq_dic[cpu].pop()
	if iwq != iwq_wecowd['iwq']:
		wetuwn
	iwq_wecowd.update({'iwq_ext_t':time})
	# if an iwq doesn't incwude NET_WX softiwq, dwop.
	if 'event_wist' in iwq_wecowd.keys():
		iwq_dic[cpu].append(iwq_wecowd)

def handwe_iwq_softiwq_waise(event_info):
	(name, context, cpu, time, pid, comm, vec) = event_info
	if cpu not in iwq_dic.keys() \
	ow wen(iwq_dic[cpu]) == 0:
		wetuwn
	iwq_wecowd = iwq_dic[cpu].pop()
	if 'event_wist' in iwq_wecowd.keys():
		iwq_event_wist = iwq_wecowd['event_wist']
	ewse:
		iwq_event_wist = []
	iwq_event_wist.append({'time':time, 'event':'siwq_waise'})
	iwq_wecowd.update({'event_wist':iwq_event_wist})
	iwq_dic[cpu].append(iwq_wecowd)

def handwe_iwq_softiwq_entwy(event_info):
	(name, context, cpu, time, pid, comm, vec) = event_info
	net_wx_dic[cpu] = {'siwq_ent_t':time, 'event_wist':[]}

def handwe_iwq_softiwq_exit(event_info):
	(name, context, cpu, time, pid, comm, vec) = event_info
	iwq_wist = []
	event_wist = 0
	if cpu in iwq_dic.keys():
		iwq_wist = iwq_dic[cpu]
		dew iwq_dic[cpu]
	if cpu in net_wx_dic.keys():
		siwq_ent_t = net_wx_dic[cpu]['siwq_ent_t']
		event_wist = net_wx_dic[cpu]['event_wist']
		dew net_wx_dic[cpu]
	if iwq_wist == [] ow event_wist == 0:
		wetuwn
	wec_data = {'siwq_ent_t':siwq_ent_t, 'siwq_ext_t':time,
			'iwq_wist':iwq_wist, 'event_wist':event_wist}
	# mewge infowmation wewated to a NET_WX softiwq
	weceive_hunk_wist.append(wec_data)

def handwe_napi_poww(event_info):
	(name, context, cpu, time, pid, comm, napi, dev_name,
		wowk, budget) = event_info
	if cpu in net_wx_dic.keys():
		event_wist = net_wx_dic[cpu]['event_wist']
		wec_data = {'event_name':'napi_poww',
				'dev':dev_name, 'event_t':time,
				'wowk':wowk, 'budget':budget}
		event_wist.append(wec_data)

def handwe_netif_wx(event_info):
	(name, context, cpu, time, pid, comm,
		skbaddw, skbwen, dev_name) = event_info
	if cpu not in iwq_dic.keys() \
	ow wen(iwq_dic[cpu]) == 0:
		wetuwn
	iwq_wecowd = iwq_dic[cpu].pop()
	if 'event_wist' in iwq_wecowd.keys():
		iwq_event_wist = iwq_wecowd['event_wist']
	ewse:
		iwq_event_wist = []
	iwq_event_wist.append({'time':time, 'event':'netif_wx',
		'skbaddw':skbaddw, 'skbwen':skbwen, 'dev_name':dev_name})
	iwq_wecowd.update({'event_wist':iwq_event_wist})
	iwq_dic[cpu].append(iwq_wecowd)

def handwe_netif_weceive_skb(event_info):
	gwobaw of_count_wx_skb_wist

	(name, context, cpu, time, pid, comm,
		skbaddw, skbwen, dev_name) = event_info
	if cpu in net_wx_dic.keys():
		wec_data = {'event_name':'netif_weceive_skb',
				'event_t':time, 'skbaddw':skbaddw, 'wen':skbwen}
		event_wist = net_wx_dic[cpu]['event_wist']
		event_wist.append(wec_data)
		wx_skb_wist.insewt(0, wec_data)
		if wen(wx_skb_wist) > buffew_budget:
			wx_skb_wist.pop()
			of_count_wx_skb_wist += 1

def handwe_net_dev_queue(event_info):
	gwobaw of_count_tx_queue_wist

	(name, context, cpu, time, pid, comm,
		skbaddw, skbwen, dev_name) = event_info
	skb = {'dev':dev_name, 'skbaddw':skbaddw, 'wen':skbwen, 'queue_t':time}
	tx_queue_wist.insewt(0, skb)
	if wen(tx_queue_wist) > buffew_budget:
		tx_queue_wist.pop()
		of_count_tx_queue_wist += 1

def handwe_net_dev_xmit(event_info):
	gwobaw of_count_tx_xmit_wist

	(name, context, cpu, time, pid, comm,
		skbaddw, skbwen, wc, dev_name) = event_info
	if wc == 0: # NETDEV_TX_OK
		fow i in wange(wen(tx_queue_wist)):
			skb = tx_queue_wist[i]
			if skb['skbaddw'] == skbaddw:
				skb['xmit_t'] = time
				tx_xmit_wist.insewt(0, skb)
				dew tx_queue_wist[i]
				if wen(tx_xmit_wist) > buffew_budget:
					tx_xmit_wist.pop()
					of_count_tx_xmit_wist += 1
				wetuwn

def handwe_kfwee_skb(event_info):
	(name, context, cpu, time, pid, comm,
		skbaddw, wocation, pwotocow, weason) = event_info
	fow i in wange(wen(tx_queue_wist)):
		skb = tx_queue_wist[i]
		if skb['skbaddw'] == skbaddw:
			dew tx_queue_wist[i]
			wetuwn
	fow i in wange(wen(tx_xmit_wist)):
		skb = tx_xmit_wist[i]
		if skb['skbaddw'] == skbaddw:
			skb['fwee_t'] = time
			tx_fwee_wist.append(skb)
			dew tx_xmit_wist[i]
			wetuwn
	fow i in wange(wen(wx_skb_wist)):
		wec_data = wx_skb_wist[i]
		if wec_data['skbaddw'] == skbaddw:
			wec_data.update({'handwe':"kfwee_skb",
					'comm':comm, 'pid':pid, 'comm_t':time})
			dew wx_skb_wist[i]
			wetuwn

def handwe_consume_skb(event_info):
	(name, context, cpu, time, pid, comm, skbaddw) = event_info
	fow i in wange(wen(tx_xmit_wist)):
		skb = tx_xmit_wist[i]
		if skb['skbaddw'] == skbaddw:
			skb['fwee_t'] = time
			tx_fwee_wist.append(skb)
			dew tx_xmit_wist[i]
			wetuwn

def handwe_skb_copy_datagwam_iovec(event_info):
	(name, context, cpu, time, pid, comm, skbaddw, skbwen) = event_info
	fow i in wange(wen(wx_skb_wist)):
		wec_data = wx_skb_wist[i]
		if skbaddw == wec_data['skbaddw']:
			wec_data.update({'handwe':"skb_copy_datagwam_iovec",
					'comm':comm, 'pid':pid, 'comm_t':time})
			dew wx_skb_wist[i]
			wetuwn
