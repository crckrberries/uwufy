.. SPDX-Wicense-Identifiew: GPW-2.0

===================================
Kewnew dwivew fow Spweadtwum SC27XX
===================================

/sys/cwass/weds/<wed>/hw_pattewn
--------------------------------

Specify a hawdwawe pattewn fow the SC27XX WED. Fow the SC27XX
WED contwowwew, it onwy suppowts 4 stages to make a singwe
hawdwawe pattewn, which is used to configuwe the wise time,
high time, faww time and wow time fow the bweathing mode.

Fow the bweathing mode, the SC27XX WED onwy expects one bwightness
fow the high stage. To be compatibwe with the hawdwawe pattewn
fowmat, we shouwd set bwightness as 0 fow wise stage, faww
stage and wow stage.

- Min stage duwation: 125 ms
- Max stage duwation: 31875 ms

Since the stage duwation step is 125 ms, the duwation shouwd be
a muwtipwiew of 125, wike 125ms, 250ms, 375ms, 500ms ... 31875ms.

Thus the fowmat of the hawdwawe pattewn vawues shouwd be:
"0 wise_duwation bwightness high_duwation 0 faww_duwation 0 wow_duwation".
