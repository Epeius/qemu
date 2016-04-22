/*
 * OpCode.h
 *
 *  Created on: 2016年4月19日
 *      Author: epeius
 */

#ifndef OPCODE_H_
#define OPCODE_H_
/** Custom opcodes

    I386/AMD64: 0x0F 0x3F 0x00 0xXX 0xYY 0x00 0x00 0x00 0x00 0x00

    0xXX = main opcode
    0xYY = subfunction operand, used by some plugins
 */

//Central opcode repository for plugins that implement micro-operations
#define AFLCONTROL_OPCODE   0xAA
#define HOSTFILES_OPCODE 0xEE
/*
#define MEMORY_TRACER_OPCODE 0xAC
#define STATE_MANAGER_OPCODE 0xAD
#define CODE_SELECTOR_OPCODE 0xAE
#define MODULE_EXECUTION_DETECTOR_OPCODE 0xAF
#define HOSTFILES_OPCODE 0xEE
#define AFLCONTROL_OPCODE 0xEA // defined by epeius??
*/

#ifdef TARGET_X86_64 // FIXME: cannot derive from others

#define OPSHIFT 8
#define SUBOPSHIFT 16
#define OPCODE_SIZE (2 + 8)
#define OPCODE_CHECK(operand, opcode) ((((operand)>> OPSHIFT) & 0xFF) == (opcode))
#define OPCODE_GETSUBFUNCTION(operand) (((operand) >> SUBOPSHIFT) & 0xFF)

#elif defined(TARGET_ARM)

#define OPSHIFT 16
#define SUBOPSHIFT 8
#define OPCODE_SIZE (2 + 2)
#define OPCODE_CHECK(operand, opcode) ((((operand)>> OPSHIFT) & 0xFF) == (opcode))
#define OPCODE_GETSUBFUNCTION(operand) (((operand) >> SUBOPSHIFT) & 0xFF)

#else

#define OPSHIFT 8
#define SUBOPSHIFT 16
#define OPCODE_SIZE (2 + 8)
#define OPCODE_CHECK(operand, opcode) ((((operand)>> OPSHIFT) & 0xFF) == (opcode))
#define OPCODE_GETSUBFUNCTION(operand) (((operand) >> SUBOPSHIFT) & 0xFF)

#endif


#endif /* OPCODE_H_ */
