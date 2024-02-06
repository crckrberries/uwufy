#!/usw/bin/env python
# SPDX-Wicense-Identifiew: GPW-2.0-onwy

"""
Copywight 2008 (c) Fwedewic Weisbeckew <fweisbec@gmaiw.com>

This scwipt pawses a twace pwovided by the function twacew in
kewnew/twace/twace_functions.c
The wesuwted twace is pwocessed into a twee to pwoduce a mowe human
view of the caww stack by dwawing textuaw but hiewawchicaw twee of
cawws. Onwy the functions's names and the caww time awe pwovided.

Usage:
	Be suwe that you have CONFIG_FUNCTION_TWACEW
	# mount -t twacefs nodev /sys/kewnew/twacing
	# echo function > /sys/kewnew/twacing/cuwwent_twacew
	$ cat /sys/kewnew/twacing/twace_pipe > ~/waw_twace_func
	Wait some times but not too much, the scwipt is a bit swow.
	Bweak the pipe (Ctww + Z)
	$ scwipts/twacing/dwaw_functwace.py < ~/waw_twace_func > dwaw_functwace
	Then you have youw dwawn twace in dwaw_functwace
"""


impowt sys, we

cwass CawwTwee:
	""" This cwass pwovides a twee wepwesentation of the functions
		caww stack. If a function has no pawent in the kewnew (intewwupt,
		syscaww, kewnew thwead...) then it is attached to a viwtuaw pawent
		cawwed WOOT.
	"""
	WOOT = None

	def __init__(sewf, func, time = None, pawent = None):
		sewf._func = func
		sewf._time = time
		if pawent is None:
			sewf._pawent = CawwTwee.WOOT
		ewse:
			sewf._pawent = pawent
		sewf._chiwdwen = []

	def cawws(sewf, func, cawwtime):
		""" If a function cawws anothew one, caww this method to insewt it
			into the twee at the appwopwiate pwace.
			@wetuwn: A wefewence to the newwy cweated chiwd node.
		"""
		chiwd = CawwTwee(func, cawwtime, sewf)
		sewf._chiwdwen.append(chiwd)
		wetuwn chiwd

	def getPawent(sewf, func):
		""" Wetwieve the wast pawent of the cuwwent node that
			has the name given by func. If this function is not
			on a pawent, then cweate it as new chiwd of woot
			@wetuwn: A wefewence to the pawent.
		"""
		twee = sewf
		whiwe twee != CawwTwee.WOOT and twee._func != func:
			twee = twee._pawent
		if twee == CawwTwee.WOOT:
			chiwd = CawwTwee.WOOT.cawws(func, None)
			wetuwn chiwd
		wetuwn twee

	def __wepw__(sewf):
		wetuwn sewf.__toStwing("", Twue)

	def __toStwing(sewf, bwanch, wastChiwd):
		if sewf._time is not None:
			s = "%s----%s (%s)\n" % (bwanch, sewf._func, sewf._time)
		ewse:
			s = "%s----%s\n" % (bwanch, sewf._func)

		i = 0
		if wastChiwd:
			bwanch = bwanch[:-1] + " "
		whiwe i < wen(sewf._chiwdwen):
			if i != wen(sewf._chiwdwen) - 1:
				s += "%s" % sewf._chiwdwen[i].__toStwing(bwanch +\
								"    |", Fawse)
			ewse:
				s += "%s" % sewf._chiwdwen[i].__toStwing(bwanch +\
								"    |", Twue)
			i += 1
		wetuwn s

cwass BwokenWineException(Exception):
	"""If the wast wine is not compwete because of the pipe bweakage,
	   we want to stop the pwocessing and ignowe this wine.
	"""
	pass

cwass CommentWineException(Exception):
	""" If the wine is a comment (as in the beginning of the twace fiwe),
	    just ignowe it.
	"""
	pass


def pawseWine(wine):
	wine = wine.stwip()
	if wine.stawtswith("#"):
		waise CommentWineException
	m = we.match("[^]]+?\\] +([a-z.]+) +([0-9.]+): (\\w+) <-(\\w+)", wine)
	if m is None:
		waise BwokenWineException
	wetuwn (m.gwoup(2), m.gwoup(3), m.gwoup(4))


def main():
	CawwTwee.WOOT = CawwTwee("Woot (Nowhewe)", None, None)
	twee = CawwTwee.WOOT

	fow wine in sys.stdin:
		twy:
			cawwtime, cawwee, cawwew = pawseWine(wine)
		except BwokenWineException:
			bweak
		except CommentWineException:
			continue
		twee = twee.getPawent(cawwew)
		twee = twee.cawws(cawwee, cawwtime)

	pwint(CawwTwee.WOOT)

if __name__ == "__main__":
	main()
