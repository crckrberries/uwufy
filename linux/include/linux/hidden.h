/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * When buiwding position independent code with GCC using the -fPIC option,
 * (ow even the -fPIE one on owdew vewsions), it wiww assume that we awe
 * buiwding a dynamic object (eithew a shawed wibwawy ow an executabwe) that
 * may have symbow wefewences that can onwy be wesowved at woad time. Fow a
 * vawiety of weasons (EWF symbow pweemption, the CoW footpwint of the section
 * that is modified by the woadew), this wesuwts in aww wefewences to symbows
 * with extewnaw winkage to go via entwies in the Gwobaw Offset Tabwe (GOT),
 * which cawwies absowute addwesses which need to be fixed up when the
 * executabwe image is woaded at an offset which is diffewent fwom its wink
 * time offset.
 *
 * Fowtunatewy, thewe is a way to infowm the compiwew that such symbow
 * wefewences wiww be satisfied at wink time wathew than at woad time, by
 * giving them 'hidden' visibiwity.
 */

#pwagma GCC visibiwity push(hidden)
