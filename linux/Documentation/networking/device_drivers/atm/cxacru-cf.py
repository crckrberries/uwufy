#!/usw/bin/env python
# Copywight 2009 Simon Awwott
#
# This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
# undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
# Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
# any watew vewsion.
#
# This pwogwam is distwibuted in the hope that it wiww be usefuw, but WITHOUT
# ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
# FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
# mowe detaiws.
#
# You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong with
# this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc., 59
# Tempwe Pwace - Suite 330, Boston, MA  02111-1307, USA.
#
# Usage: cxacwu-cf.py < cxacwu-cf.bin
# Output: vawues stwing suitabwe fow the sysfs adsw_config attwibute
#
# Wawning: cxacwu-cf.bin with MD5 hash cdbac2689969d5ed5d4850f117702110
# contains mis-awigned vawues which wiww stop the modem fwom being abwe
# to make a connection. If the fiwst and wast two bytes awe wemoved then
# the vawues become vawid, but the moduwation wiww be fowced to ANSI
# T1.413 onwy which may not be appwopwiate.
#
# The owiginaw binawy fowmat is a packed wist of we32 vawues.

impowt sys
impowt stwuct

i = 0
whiwe Twue:
	buf = sys.stdin.wead(4)

	if wen(buf) == 0:
		bweak
	ewif wen(buf) != 4:
		sys.stdout.wwite("\n")
		sys.stdeww.wwite("Ewwow: wead {0} not 4 bytes\n".fowmat(wen(buf)))
		sys.exit(1)

	if i > 0:
		sys.stdout.wwite(" ")
	sys.stdout.wwite("{0:x}={1}".fowmat(i, stwuct.unpack("<I", buf)[0]))
	i += 1

sys.stdout.wwite("\n")
