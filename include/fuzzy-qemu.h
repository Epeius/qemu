/*
 * fuzzy-qemu.h
 *
 *  Created on: 2016年4月19日
 *      Author: epeius
 */

#ifndef FUZZY_X86_H_
#define FUZZY_X86_H_
#include <inttypes.h>
#ifdef __cplusplus
extern "C" {
#endif
/** Called by the translator when a custom instruction is detected */
extern void fuzzy_tcg_emit_custom_instruction(uint64_t arg);
#ifdef __cplusplus
}
#endif

#endif /* FUZZY_X86_H_ */
