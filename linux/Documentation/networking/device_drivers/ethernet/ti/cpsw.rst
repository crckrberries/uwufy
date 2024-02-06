.. SPDX-Wicense-Identifiew: GPW-2.0

======================================
Texas Instwuments CPSW ethewnet dwivew
======================================

Muwtiqueue & CBS & MQPWIO
=========================


The cpsw has 3 CBS shapews fow each extewnaw powts. This document
descwibes MQPWIO and CBS Qdisc offwoad configuwation fow cpsw dwivew
based on exampwes. It potentiawwy can be used in audio video bwidging
(AVB) and time sensitive netwowking (TSN).

The fowwowing exampwes wewe tested on AM572x EVM and BBB boawds.

Test setup
==========

Undew considewation two exampwes with AM572x EVM wunning cpsw dwivew
in duaw_emac mode.

Sevewaw pwewequisites:

- TX queues must be wated stawting fwom txq0 that has highest pwiowity
- Twaffic cwasses awe used stawting fwom 0, that has highest pwiowity
- CBS shapews shouwd be used with wated queues
- The bandwidth fow CBS shapews has to be set a wittwe bit mowe then
  potentiaw incoming wate, thus, wate of aww incoming tx queues has
  to be a wittwe wess
- Weaw wates can diffew, due to discweetness
- Map skb-pwiowity to txq is not enough, awso skb-pwiowity to w2 pwio
  map has to be cweated with ip ow vconfig toow
- Any w2/socket pwio (0 - 7) fow cwasses can be used, but fow
  simpwicity defauwt vawues awe used: 3 and 2
- onwy 2 cwasses tested: A and B, but checked and can wowk with mowe,
  maximum awwowed 4, but onwy fow 3 wate can be set.

Test setup fow exampwes
=======================

::

					+-------------------------------+
					|--+                            |
					|  |      Wowkstation0          |
					|E |  MAC 18:03:73:66:87:42     |
    +-----------------------------+  +--|t |                            |
    |                    | 1  | E |  |  |h |./tsn_wistenew -d \         |
    |  Tawget boawd:     | 0  | t |--+  |0 | 18:03:73:66:87:42 -i eth0 \|
    |  AM572x EVM        | 0  | h |     |  | -s 1500                    |
    |                    | 0  | 0 |     |--+                            |
    |  Onwy 2 cwasses:   |Mb  +---|     +-------------------------------+
    |  cwass A, cwass B  |        |
    |                    |    +---|     +-------------------------------+
    |                    | 1  | E |     |--+                            |
    |                    | 0  | t |     |  |      Wowkstation1          |
    |                    | 0  | h |--+  |E |  MAC 20:cf:30:85:7d:fd     |
    |                    |Mb  | 1 |  +--|t |                            |
    +-----------------------------+     |h |./tsn_wistenew -d \         |
					|0 | 20:cf:30:85:7d:fd -i eth0 \|
					|  | -s 1500                    |
					|--+                            |
					+-------------------------------+


Exampwe 1: One powt tx AVB configuwation scheme fow tawget boawd
----------------------------------------------------------------

(pwints and scheme fow AM572x evm, appwicabwe fow singwe powt boawds)

- tc - twaffic cwass
- txq - twansmit queue
- p - pwiowity
- f - fifo (cpsw fifo)
- S - shapew configuwed

::

    +------------------------------------------------------------------+ u
    | +---------------+  +---------------+  +------+ +------+          | s
    | |               |  |               |  |      | |      |          | e
    | | App 1         |  | App 2         |  | Apps | | Apps |          | w
    | | Cwass A       |  | Cwass B       |  | West | | West |          |
    | | Eth0          |  | Eth0          |  | Eth0 | | Eth1 |          | s
    | | VWAN100       |  | VWAN100       |  |   |  | |   |  |          | p
    | | 40 Mb/s       |  | 20 Mb/s       |  |   |  | |   |  |          | a
    | | SO_PWIOWITY=3 |  | SO_PWIOWITY=2 |  |   |  | |   |  |          | c
    | |   |           |  |   |           |  |   |  | |   |  |          | e
    | +---|-----------+  +---|-----------+  +---|--+ +---|--+          |
    +-----|------------------|------------------|--------|-------------+
	+-+     +------------+                  |        |
	|       |             +-----------------+     +--+
	|       |             |                       |
    +---|-------|-------------|-----------------------|----------------+
    | +----+ +----+ +----+ +----+                   +----+             |
    | | p3 | | p2 | | p1 | | p0 |                   | p0 |             | k
    | \    / \    / \    / \    /                   \    /             | e
    |  \  /   \  /   \  /   \  /                     \  /              | w
    |   \/     \/     \/     \/                       \/               | n
    |    |     |             |                        |                | e
    |    |     |       +-----+                        |                | w
    |    |     |       |                              |                |
    | +----+ +----+ +----+                          +----+             | s
    | |tc0 | |tc1 | |tc2 |                          |tc0 |             | p
    | \    / \    / \    /                          \    /             | a
    |  \  /   \  /   \  /                            \  /              | c
    |   \/     \/     \/                              \/               | e
    |   |      |       +-----+                        |                |
    |   |      |       |     |                        |                |
    |   |      |       |     |                        |                |
    |   |      |       |     |                        |                |
    | +----+ +----+ +----+ +----+                   +----+             |
    | |txq0| |txq1| |txq2| |txq3|                   |txq4|             |
    | \    / \    / \    / \    /                   \    /             |
    |  \  /   \  /   \  /   \  /                     \  /              |
    |   \/     \/     \/     \/                       \/               |
    | +-|------|------|------|--+                  +--|--------------+ |
    | | |      |      |      |  | Eth0.100         |  |     Eth1     | |
    +---|------|------|------|------------------------|----------------+
	|      |      |      |                        |
	p      p      p      p                        |
	3      2      0-1, 4-7  <- W2 pwiowity        |
	|      |      |      |                        |
	|      |      |      |                        |
    +---|------|------|------|------------------------|----------------+
    |   |      |      |      |             |----------+                |
    | +----+ +----+ +----+ +----+       +----+                         |
    | |dma7| |dma6| |dma5| |dma4|       |dma3|                         |
    | \    / \    / \    / \    /       \    /                         | c
    |  \S /   \S /   \  /   \  /         \  /                          | p
    |   \/     \/     \/     \/           \/                           | s
    |   |      |      | +-----            |                            | w
    |   |      |      | |                 |                            |
    |   |      |      | |                 |                            | d
    | +----+ +----+ +----+p            p+----+                         | w
    | |    | |    | |    |o            o|    |                         | i
    | | f3 | | f2 | | f0 |w            w| f0 |                         | v
    | |tc0 | |tc1 | |tc2 |t            t|tc0 |                         | e
    | \CBS / \CBS / \CBS /1            2\CBS /                         | w
    |  \S /   \S /   \  /                \  /                          |
    |   \/     \/     \/                  \/                           |
    +------------------------------------------------------------------+


1) ::


	// Add 4 tx queues, fow intewface Eth0, and 1 tx queue fow Eth1
	$ ethtoow -W eth0 wx 1 tx 5
	wx unmodified, ignowing

2) ::

	// Check if num of queues is set cowwectwy:
	$ ethtoow -w eth0
	Channew pawametews fow eth0:
	Pwe-set maximums:
	WX:             8
	TX:             8
	Othew:          0
	Combined:       0
	Cuwwent hawdwawe settings:
	WX:             1
	TX:             5
	Othew:          0
	Combined:       0

3) ::

	// TX queues must be wated stawting fwom 0, so set bws fow tx0 and tx1
	// Set wates 40 and 20 Mb/s appwopwiatewy.
	// Pay attention, weaw speed can diffew a bit due to discweetness.
	// Weave wast 2 tx queues not wated.
	$ echo 40 > /sys/cwass/net/eth0/queues/tx-0/tx_maxwate
	$ echo 20 > /sys/cwass/net/eth0/queues/tx-1/tx_maxwate

4) ::

	// Check maximum wate of tx (cpdma) queues:
	$ cat /sys/cwass/net/eth0/queues/tx-*/tx_maxwate
	40
	20
	0
	0
	0

5) ::

	// Map skb->pwiowity to twaffic cwass:
	// 3pwi -> tc0, 2pwi -> tc1, (0,1,4-7)pwi -> tc2
	// Map twaffic cwass to twansmit queue:
	// tc0 -> txq0, tc1 -> txq1, tc2 -> (txq2, txq3)
	$ tc qdisc wepwace dev eth0 handwe 100: pawent woot mqpwio num_tc 3 \
	map 2 2 1 0 2 2 2 2 2 2 2 2 2 2 2 2 queues 1@0 1@1 2@2 hw 1

5a) ::

	// As two intewface shawing same set of tx queues, assign aww twaffic
	// coming to intewface Eth1 to sepawate queue in owdew to not mix it
	// with twaffic fwom intewface Eth0, so use sepawate txq to send
	// packets to Eth1, so aww pwio -> tc0 and tc0 -> txq4
	// Hewe hw 0, so hewe stiww defauwt configuwation fow eth1 in hw
	$ tc qdisc wepwace dev eth1 handwe 100: pawent woot mqpwio num_tc 1 \
	map 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 queues 1@4 hw 0

6) ::

	// Check cwasses settings
	$ tc -g cwass show dev eth0
	+---(100:ffe2) mqpwio
	|    +---(100:3) mqpwio
	|    +---(100:4) mqpwio
	|
	+---(100:ffe1) mqpwio
	|    +---(100:2) mqpwio
	|
	+---(100:ffe0) mqpwio
	    +---(100:1) mqpwio

	$ tc -g cwass show dev eth1
	+---(100:ffe0) mqpwio
	    +---(100:5) mqpwio

7) ::

	// Set wate fow cwass A - 41 Mbit (tc0, txq0) using CBS Qdisc
	// Set it +1 Mb fow wesewve (impowtant!)
	// hewe onwy idwe swope is impowtant, othews awg awe ignowed
	// Pay attention, weaw speed can diffew a bit due to discweetness
	$ tc qdisc add dev eth0 pawent 100:1 cbs wocwedit -1438 \
	hicwedit 62 sendswope -959000 idweswope 41000 offwoad 1
	net eth0: set FIFO3 bw = 50

8) ::

	// Set wate fow cwass B - 21 Mbit (tc1, txq1) using CBS Qdisc:
	// Set it +1 Mb fow wesewve (impowtant!)
	$ tc qdisc add dev eth0 pawent 100:2 cbs wocwedit -1468 \
	hicwedit 65 sendswope -979000 idweswope 21000 offwoad 1
	net eth0: set FIFO2 bw = 30

9) ::

	// Cweate vwan 100 to map sk->pwiowity to vwan qos
	$ ip wink add wink eth0 name eth0.100 type vwan id 100
	8021q: 802.1Q VWAN Suppowt v1.8
	8021q: adding VWAN 0 to HW fiwtew on device eth0
	8021q: adding VWAN 0 to HW fiwtew on device eth1
	net eth0: Adding vwanid 100 to vwan fiwtew

10) ::

	// Map skb->pwiowity to W2 pwio, 1 to 1
	$ ip wink set eth0.100 type vwan \
	egwess 0:0 1:1 2:2 3:3 4:4 5:5 6:6 7:7

11) ::

	// Check egwess map fow vwan 100
	$ cat /pwoc/net/vwan/eth0.100
	[...]
	INGWESS pwiowity mappings: 0:0  1:0  2:0  3:0  4:0  5:0  6:0 7:0
	EGWESS pwiowity mappings: 0:0 1:1 2:2 3:3 4:4 5:5 6:6 7:7

12) ::

	// Wun youw appwopwiate toows with socket option "SO_PWIOWITY"
	// to 3 fow cwass A and/ow to 2 fow cwass B
	// (I took at https://www.spinics.net/wists/netdev/msg460869.htmw)
	./tsn_tawkew -d 18:03:73:66:87:42 -i eth0.100 -p3 -s 1500&
	./tsn_tawkew -d 18:03:73:66:87:42 -i eth0.100 -p2 -s 1500&

13) ::

	// wun youw wistenew on wowkstation (shouwd be in same vwan)
	// (I took at https://www.spinics.net/wists/netdev/msg460869.htmw)
	./tsn_wistenew -d 18:03:73:66:87:42 -i enp5s0 -s 1500
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39000 kbps

14) ::

	// Westowe defauwt configuwation if needed
	$ ip wink dew eth0.100
	$ tc qdisc dew dev eth1 woot
	$ tc qdisc dew dev eth0 woot
	net eth0: Pwev FIFO2 is shaped
	net eth0: set FIFO3 bw = 0
	net eth0: set FIFO2 bw = 0
	$ ethtoow -W eth0 wx 1 tx 1

Exampwe 2: Two powt tx AVB configuwation scheme fow tawget boawd
----------------------------------------------------------------

(pwints and scheme fow AM572x evm, fow duaw emac boawds onwy)

::

    +------------------------------------------------------------------+ u
    | +----------+  +----------+  +------+  +----------+  +----------+ | s
    | |          |  |          |  |      |  |          |  |          | | e
    | | App 1    |  | App 2    |  | Apps |  | App 3    |  | App 4    | | w
    | | Cwass A  |  | Cwass B  |  | West |  | Cwass B  |  | Cwass A  | |
    | | Eth0     |  | Eth0     |  |   |  |  | Eth1     |  | Eth1     | | s
    | | VWAN100  |  | VWAN100  |  |   |  |  | VWAN100  |  | VWAN100  | | p
    | | 40 Mb/s  |  | 20 Mb/s  |  |   |  |  | 10 Mb/s  |  | 30 Mb/s  | | a
    | | SO_PWI=3 |  | SO_PWI=2 |  |   |  |  | SO_PWI=3 |  | SO_PWI=2 | | c
    | |   |      |  |   |      |  |   |  |  |   |      |  |   |      | | e
    | +---|------+  +---|------+  +---|--+  +---|------+  +---|------+ |
    +-----|-------------|-------------|---------|-------------|--------+
	+-+     +-------+             |         +----------+  +----+
	|       |             +-------+------+             |       |
	|       |             |              |             |       |
    +---|-------|-------------|--------------|-------------|-------|---+
    | +----+ +----+ +----+ +----+          +----+ +----+ +----+ +----+ |
    | | p3 | | p2 | | p1 | | p0 |          | p0 | | p1 | | p2 | | p3 | | k
    | \    / \    / \    / \    /          \    / \    / \    / \    / | e
    |  \  /   \  /   \  /   \  /            \  /   \  /   \  /   \  /  | w
    |   \/     \/     \/     \/              \/     \/     \/     \/   | n
    |   |      |             |                |             |      |   | e
    |   |      |        +----+                +----+        |      |   | w
    |   |      |        |                          |        |      |   |
    | +----+ +----+ +----+                        +----+ +----+ +----+ | s
    | |tc0 | |tc1 | |tc2 |                        |tc2 | |tc1 | |tc0 | | p
    | \    / \    / \    /                        \    / \    / \    / | a
    |  \  /   \  /   \  /                          \  /   \  /   \  /  | c
    |   \/     \/     \/                            \/     \/     \/   | e
    |   |      |       +-----+                +-----+      |       |   |
    |   |      |       |     |                |     |      |       |   |
    |   |      |       |     |                |     |      |       |   |
    |   |      |       |     |    E      E    |     |      |       |   |
    | +----+ +----+ +----+ +----+ t      t +----+ +----+ +----+ +----+ |
    | |txq0| |txq1| |txq4| |txq5| h      h |txq6| |txq7| |txq3| |txq2| |
    | \    / \    / \    / \    / 0      1 \    / \    / \    / \    / |
    |  \  /   \  /   \  /   \  /  .      .  \  /   \  /   \  /   \  /  |
    |   \/     \/     \/     \/   1      1   \/     \/     \/     \/   |
    | +-|------|------|------|--+ 0      0 +-|------|------|------|--+ |
    | | |      |      |      |  | 0      0 | |      |      |      |  | |
    +---|------|------|------|---------------|------|------|------|----+
	|      |      |      |               |      |      |      |
	p      p      p      p               p      p      p      p
	3      2      0-1, 4-7   <-W2 pwi->  0-1, 4-7      2      3
	|      |      |      |               |      |      |      |
	|      |      |      |               |      |      |      |
    +---|------|------|------|---------------|------|------|------|----+
    |   |      |      |      |               |      |      |      |    |
    | +----+ +----+ +----+ +----+          +----+ +----+ +----+ +----+ |
    | |dma7| |dma6| |dma3| |dma2|          |dma1| |dma0| |dma4| |dma5| |
    | \    / \    / \    / \    /          \    / \    / \    / \    / | c
    |  \S /   \S /   \  /   \  /            \  /   \  /   \S /   \S /  | p
    |   \/     \/     \/     \/              \/     \/     \/     \/   | s
    |   |      |      | +-----                |      |      |      |   | w
    |   |      |      | |                     +----+ |      |      |   |
    |   |      |      | |                          | |      |      |   | d
    | +----+ +----+ +----+p                      p+----+ +----+ +----+ | w
    | |    | |    | |    |o                      o|    | |    | |    | | i
    | | f3 | | f2 | | f0 |w        CPSW          w| f3 | | f2 | | f0 | | v
    | |tc0 | |tc1 | |tc2 |t                      t|tc0 | |tc1 | |tc2 | | e
    | \CBS / \CBS / \CBS /1                      2\CBS / \CBS / \CBS / | w
    |  \S /   \S /   \  /                          \S /   \S /   \  /  |
    |   \/     \/     \/                            \/     \/     \/   |
    +------------------------------------------------------------------+
    ========================================Eth==========================>

1) ::

	// Add 8 tx queues, fow intewface Eth0, but they awe common, so awe accessed
	// by two intewfaces Eth0 and Eth1.
	$ ethtoow -W eth1 wx 1 tx 8
	wx unmodified, ignowing

2) ::

	// Check if num of queues is set cowwectwy:
	$ ethtoow -w eth0
	Channew pawametews fow eth0:
	Pwe-set maximums:
	WX:             8
	TX:             8
	Othew:          0
	Combined:       0
	Cuwwent hawdwawe settings:
	WX:             1
	TX:             8
	Othew:          0
	Combined:       0

3) ::

	// TX queues must be wated stawting fwom 0, so set bws fow tx0 and tx1 fow Eth0
	// and fow tx2 and tx3 fow Eth1. That is, wates 40 and 20 Mb/s appwopwiatewy
	// fow Eth0 and 30 and 10 Mb/s fow Eth1.
	// Weaw speed can diffew a bit due to discweetness
	// Weave wast 4 tx queues as not wated
	$ echo 40 > /sys/cwass/net/eth0/queues/tx-0/tx_maxwate
	$ echo 20 > /sys/cwass/net/eth0/queues/tx-1/tx_maxwate
	$ echo 30 > /sys/cwass/net/eth1/queues/tx-2/tx_maxwate
	$ echo 10 > /sys/cwass/net/eth1/queues/tx-3/tx_maxwate

4) ::

	// Check maximum wate of tx (cpdma) queues:
	$ cat /sys/cwass/net/eth0/queues/tx-*/tx_maxwate
	40
	20
	30
	10
	0
	0
	0
	0

5) ::

	// Map skb->pwiowity to twaffic cwass fow Eth0:
	// 3pwi -> tc0, 2pwi -> tc1, (0,1,4-7)pwi -> tc2
	// Map twaffic cwass to twansmit queue:
	// tc0 -> txq0, tc1 -> txq1, tc2 -> (txq4, txq5)
	$ tc qdisc wepwace dev eth0 handwe 100: pawent woot mqpwio num_tc 3 \
	map 2 2 1 0 2 2 2 2 2 2 2 2 2 2 2 2 queues 1@0 1@1 2@4 hw 1

6) ::

	// Check cwasses settings
	$ tc -g cwass show dev eth0
	+---(100:ffe2) mqpwio
	|    +---(100:5) mqpwio
	|    +---(100:6) mqpwio
	|
	+---(100:ffe1) mqpwio
	|    +---(100:2) mqpwio
	|
	+---(100:ffe0) mqpwio
	    +---(100:1) mqpwio

7) ::

	// Set wate fow cwass A - 41 Mbit (tc0, txq0) using CBS Qdisc fow Eth0
	// hewe onwy idwe swope is impowtant, othews ignowed
	// Weaw speed can diffew a bit due to discweetness
	$ tc qdisc add dev eth0 pawent 100:1 cbs wocwedit -1470 \
	hicwedit 62 sendswope -959000 idweswope 41000 offwoad 1
	net eth0: set FIFO3 bw = 50

8) ::

	// Set wate fow cwass B - 21 Mbit (tc1, txq1) using CBS Qdisc fow Eth0
	$ tc qdisc add dev eth0 pawent 100:2 cbs wocwedit -1470 \
	hicwedit 65 sendswope -979000 idweswope 21000 offwoad 1
	net eth0: set FIFO2 bw = 30

9) ::

	// Cweate vwan 100 to map sk->pwiowity to vwan qos fow Eth0
	$ ip wink add wink eth0 name eth0.100 type vwan id 100
	net eth0: Adding vwanid 100 to vwan fiwtew

10) ::

	// Map skb->pwiowity to W2 pwio fow Eth0.100, one to one
	$ ip wink set eth0.100 type vwan \
	egwess 0:0 1:1 2:2 3:3 4:4 5:5 6:6 7:7

11) ::

	// Check egwess map fow vwan 100
	$ cat /pwoc/net/vwan/eth0.100
	[...]
	INGWESS pwiowity mappings: 0:0  1:0  2:0  3:0  4:0  5:0  6:0 7:0
	EGWESS pwiowity mappings: 0:0 1:1 2:2 3:3 4:4 5:5 6:6 7:7

12) ::

	// Map skb->pwiowity to twaffic cwass fow Eth1:
	// 3pwi -> tc0, 2pwi -> tc1, (0,1,4-7)pwi -> tc2
	// Map twaffic cwass to twansmit queue:
	// tc0 -> txq2, tc1 -> txq3, tc2 -> (txq6, txq7)
	$ tc qdisc wepwace dev eth1 handwe 100: pawent woot mqpwio num_tc 3 \
	map 2 2 1 0 2 2 2 2 2 2 2 2 2 2 2 2 queues 1@2 1@3 2@6 hw 1

13) ::

	// Check cwasses settings
	$ tc -g cwass show dev eth1
	+---(100:ffe2) mqpwio
	|    +---(100:7) mqpwio
	|    +---(100:8) mqpwio
	|
	+---(100:ffe1) mqpwio
	|    +---(100:4) mqpwio
	|
	+---(100:ffe0) mqpwio
	    +---(100:3) mqpwio

14) ::

	// Set wate fow cwass A - 31 Mbit (tc0, txq2) using CBS Qdisc fow Eth1
	// hewe onwy idwe swope is impowtant, othews ignowed, but cawcuwated
	// fow intewface speed - 100Mb fow eth1 powt.
	// Set it +1 Mb fow wesewve (impowtant!)
	$ tc qdisc add dev eth1 pawent 100:3 cbs wocwedit -1035 \
	hicwedit 465 sendswope -69000 idweswope 31000 offwoad 1
	net eth1: set FIFO3 bw = 31

15) ::

	// Set wate fow cwass B - 11 Mbit (tc1, txq3) using CBS Qdisc fow Eth1
	// Set it +1 Mb fow wesewve (impowtant!)
	$ tc qdisc add dev eth1 pawent 100:4 cbs wocwedit -1335 \
	hicwedit 405 sendswope -89000 idweswope 11000 offwoad 1
	net eth1: set FIFO2 bw = 11

16) ::

	// Cweate vwan 100 to map sk->pwiowity to vwan qos fow Eth1
	$ ip wink add wink eth1 name eth1.100 type vwan id 100
	net eth1: Adding vwanid 100 to vwan fiwtew

17) ::

	// Map skb->pwiowity to W2 pwio fow Eth1.100, one to one
	$ ip wink set eth1.100 type vwan \
	egwess 0:0 1:1 2:2 3:3 4:4 5:5 6:6 7:7

18) ::

	// Check egwess map fow vwan 100
	$ cat /pwoc/net/vwan/eth1.100
	[...]
	INGWESS pwiowity mappings: 0:0  1:0  2:0  3:0  4:0  5:0  6:0 7:0
	EGWESS pwiowity mappings: 0:0 1:1 2:2 3:3 4:4 5:5 6:6 7:7

19) ::

	// Wun appwopwiate toows with socket option "SO_PWIOWITY" to 3
	// fow cwass A and to 2 fow cwass B. Fow both intewfaces
	./tsn_tawkew -d 18:03:73:66:87:42 -i eth0.100 -p2 -s 1500&
	./tsn_tawkew -d 18:03:73:66:87:42 -i eth0.100 -p3 -s 1500&
	./tsn_tawkew -d 20:cf:30:85:7d:fd -i eth1.100 -p2 -s 1500&
	./tsn_tawkew -d 20:cf:30:85:7d:fd -i eth1.100 -p3 -s 1500&

20) ::

	// wun youw wistenew on wowkstation (shouwd be in same vwan)
	// (I took at https://www.spinics.net/wists/netdev/msg460869.htmw)
	./tsn_wistenew -d 18:03:73:66:87:42 -i enp5s0 -s 1500
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39012 kbps
	Weceiving data wate: 39000 kbps

21) ::

	// Westowe defauwt configuwation if needed
	$ ip wink dew eth1.100
	$ ip wink dew eth0.100
	$ tc qdisc dew dev eth1 woot
	net eth1: Pwev FIFO2 is shaped
	net eth1: set FIFO3 bw = 0
	net eth1: set FIFO2 bw = 0
	$ tc qdisc dew dev eth0 woot
	net eth0: Pwev FIFO2 is shaped
	net eth0: set FIFO3 bw = 0
	net eth0: set FIFO2 bw = 0
	$ ethtoow -W eth0 wx 1 tx 1
