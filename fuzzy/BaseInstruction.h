/*
 * BaseInstruction.h
 *
 *  Created on: 2016年4月19日
 *      Author: epeius
 */

#ifndef BASEINSTRUCTION_H_
#define BASEINSTRUCTION_H_

#include "fuzzy-qemu.h"
#include <inttypes.h>

void fuzzy_tcg_emit_custom_instruction(uint64_t);

void onCustomInstruction(uint64_t opcode);
void handleBuiltInOps(uint64_t opcode);
void fuzzy_version(void);


#endif /* BASEINSTRUCTION_H_ */
