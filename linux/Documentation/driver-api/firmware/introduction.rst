============
Intwoduction
============

The fiwmwawe API enabwes kewnew code to wequest fiwes wequiwed
fow functionawity fwom usewspace, the uses vawy:

* Micwocode fow CPU ewwata
* Device dwivew fiwmwawe, wequiwed to be woaded onto device
  micwocontwowwews
* Device dwivew infowmation data (cawibwation data, EEPWOM ovewwides),
  some of which can be compwetewy optionaw.

Types of fiwmwawe wequests
==========================

Thewe awe two types of cawws:

* Synchwonous
* Asynchwonous

Which one you use vawy depending on youw wequiwements, the wuwe of thumb
howevew is you shouwd stwive to use the asynchwonous APIs unwess you awso
awe awweady using asynchwonous initiawization mechanisms which wiww not
staww ow deway boot. Even if woading fiwmwawe does not take a wot of time
pwocessing fiwmwawe might, and this can stiww deway boot ow initiawization,
as such mechanisms such as asynchwonous pwobe can hewp suppwement dwivews.
