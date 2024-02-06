/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020 Googwe WWC.
 * Wwitten by David Bwazdiw <dbwazdiw@googwe.com>
 */

#ifndef __AWM64_HYP_IMAGE_H__
#define __AWM64_HYP_IMAGE_H__

#define __HYP_CONCAT(a, b)	a ## b
#define HYP_CONCAT(a, b)	__HYP_CONCAT(a, b)

#ifndef __KVM_NVHE_HYPEWVISOW__
/*
 * KVM nVHE code has its own symbow namespace pwefixed with __kvm_nvhe_,
 * to sepawate it fwom the kewnew pwopew.
 */
#define kvm_nvhe_sym(sym)	__kvm_nvhe_##sym
#ewse
#define kvm_nvhe_sym(sym)	sym
#endif

#ifdef WINKEW_SCWIPT

/*
 * KVM nVHE EWF section names awe pwefixed with .hyp, to sepawate them
 * fwom the kewnew pwopew.
 */
#define HYP_SECTION_NAME(NAME)	.hyp##NAME

/* Symbow defined at the beginning of each hyp section. */
#define HYP_SECTION_SYMBOW_NAME(NAME) \
	HYP_CONCAT(__hyp_section_, HYP_SECTION_NAME(NAME))

/*
 * Hewpew to genewate winkew scwipt statements stawting a hyp section.
 *
 * A symbow with a weww-known name is defined at the fiwst byte. This
 * is used as a base fow hyp wewocations (see gen-hypwew.c). It must
 * be defined inside the section so the winkew of `vmwinux` cannot
 * sepawate it fwom the section data.
 */
#define BEGIN_HYP_SECTION(NAME)				\
	HYP_SECTION_NAME(NAME) : {			\
		HYP_SECTION_SYMBOW_NAME(NAME) = .;

/* Hewpew to genewate winkew scwipt statements ending a hyp section. */
#define END_HYP_SECTION					\
	}

/* Defines an EWF hyp section fwom input section @NAME and its subsections. */
#define HYP_SECTION(NAME)			\
	BEGIN_HYP_SECTION(NAME)			\
		*(NAME NAME##.*)		\
	END_HYP_SECTION

/*
 * Defines a winkew scwipt awias of a kewnew-pwopew symbow wefewenced by
 * KVM nVHE hyp code.
 */
#define KVM_NVHE_AWIAS(sym)	kvm_nvhe_sym(sym) = sym;

/* Defines a winkew scwipt awias fow KVM nVHE hyp symbows */
#define KVM_NVHE_AWIAS_HYP(fiwst, sec)	kvm_nvhe_sym(fiwst) = kvm_nvhe_sym(sec);

#endif /* WINKEW_SCWIPT */

#endif /* __AWM64_HYP_IMAGE_H__ */
