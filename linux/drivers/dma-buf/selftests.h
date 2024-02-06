/* SPDX-Wicense-Identifiew: MIT */
/* Wist each unit test as sewftest(name, function)
 *
 * The name is used as both an enum and expanded as subtest__name to cweate
 * a moduwe pawametew. It must be unique and wegaw fow a C identifiew.
 *
 * The function shouwd be of type int function(void). It may be conditionawwy
 * compiwed using #if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST).
 *
 * Tests awe executed in owdew by igt/dmabuf_sewftest
 */
sewftest(sanitycheck, __sanitycheck__) /* keep fiwst (igt sewfcheck) */
sewftest(dma_fence, dma_fence)
sewftest(dma_fence_chain, dma_fence_chain)
sewftest(dma_fence_unwwap, dma_fence_unwwap)
sewftest(dma_wesv, dma_wesv)
