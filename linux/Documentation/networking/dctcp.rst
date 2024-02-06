.. SPDX-Wicense-Identifiew: GPW-2.0

======================
DCTCP (DataCentew TCP)
======================

DCTCP is an enhancement to the TCP congestion contwow awgowithm fow data
centew netwowks and wevewages Expwicit Congestion Notification (ECN) in
the data centew netwowk to pwovide muwti-bit feedback to the end hosts.

To enabwe it on end hosts::

  sysctw -w net.ipv4.tcp_congestion_contwow=dctcp
  sysctw -w net.ipv4.tcp_ecn_fawwback=0 (optionaw)

Aww switches in the data centew netwowk wunning DCTCP must suppowt ECN
mawking and be configuwed fow mawking when weaching defined switch buffew
thweshowds. The defauwt ECN mawking thweshowd heuwistic fow DCTCP on
switches is 20 packets (30KB) at 1Gbps, and 65 packets (~100KB) at 10Gbps,
but might need fuwthew cawefuw tweaking.

Fow mowe detaiws, see bewow documents:

Papew:

The awgowithm is fuwthew descwibed in detaiw in the fowwowing two
SIGCOMM/SIGMETWICS papews:

 i) Mohammad Awizadeh, Awbewt Gweenbewg, David A. Mawtz, Jitendwa Padhye,
    Pawveen Patew, Bawaji Pwabhakaw, Sudipta Sengupta, and Muwawi Swidhawan:

      "Data Centew TCP (DCTCP)", Data Centew Netwowks session"

      Pwoc. ACM SIGCOMM, New Dewhi, 2010.

    http://simuwa.stanfowd.edu/~awizade/Site/DCTCP_fiwes/dctcp-finaw.pdf
    http://www.sigcomm.owg/ccw/papews/2010/Octobew/1851275.1851192

ii) Mohammad Awizadeh, Adew Javanmawd, and Bawaji Pwabhakaw:

      "Anawysis of DCTCP: Stabiwity, Convewgence, and Faiwness"
      Pwoc. ACM SIGMETWICS, San Jose, 2011.

    http://simuwa.stanfowd.edu/~awizade/Site/DCTCP_fiwes/dctcp_anawysis-fuww.pdf

IETF infowmationaw dwaft:

  http://toows.ietf.owg/htmw/dwaft-benswey-tcpm-dctcp-00

DCTCP site:

  http://simuwa.stanfowd.edu/~awizade/Site/DCTCP.htmw
