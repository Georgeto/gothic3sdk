#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include "AsmjitUtil.h"
#include "Debug.h"

#include "SharedBase/ge_types.h"

#define COMBINE1(X,Y) X##Y  // helper macro
#define COMBINE(X,Y) COMBINE1(X,Y)

#define JMP(jmpDest, jmpType)    __asm COMBINE(jmpType lbl_skip, __LINE__)    \
                                __asm jmp    jmpDest                            \
                                __asm COMBINE(COMBINE(lbl_skip,__LINE__), :)

#define JNZ(jmpDest) JMP(jmpDest, jz)

#define JZ(jmpDest) JMP(jmpDest, jnz)

#define JBE(jmpDest) JMP(jmpDest, ja)

#define JA(jmpDest) JMP(jmpDest, jbe)



#define USE_X86_ASSEMBLER(message) USE_X86_ASSEMBLER_N(a, message)

#define USE_X86_ASSEMBLER_N(asm, message) using namespace asmjit;            \
                                    using namespace asmjit::x86;    \
                                    X86CodeAsm asm;  \
                                    asm.GetCode().setLogger(&GetAsmjitLogger()); \
                                    GetAsmjitLogger().logf("\n\n%s\n", message);

#define USE_X86_ASSEMBLER_ADR(baseAddress, message) USE_X86_ASSEMBLER_ADR_N(a, baseAddress, message)

#define USE_X86_ASSEMBLER_ADR_N(asm, baseAddress, message) USE_X86_ASSEMBLER_N(asm, message) \
                                                asm.setBaseAddress(baseAddress);

GELPVoid LoadModule(GELPCChar a_strModule);
GELPVoid GetProcAddress(GELPCChar a_strModule, GELPCChar a_strProc);

inline GEU32 RVA_ScriptGame(GEU32 offset) { return reinterpret_cast<GEU32>(LoadModule("Script_Game.dll")) + offset; };
inline GEU32 RVA_Script(GEU32 offset) { return reinterpret_cast<GEU32>(LoadModule("Script.dll")) + offset; };
inline GEU32 RVA_Game(GEU32 offset)       { return reinterpret_cast<GEU32>(LoadModule("Game.dll")) + offset; };
inline GEU32 RVA_Engine(GEU32 offset)     { return reinterpret_cast<GEU32>(LoadModule("Engine.dll")) + offset; };
inline GEU32 RVA_Importer(GEU32 offset)   { return reinterpret_cast<GEU32>(LoadModule("Importer.dll")) + offset; };
inline GEU32 RVA_SharedBase(GEU32 offset) { return reinterpret_cast<GEU32>(LoadModule("SharedBase.dll")) + offset; };
inline GEU32 RVA_Gui(GEU32 offset)        { return reinterpret_cast<GEU32>(LoadModule("GUI.dll")) + offset; };
inline GEU32 RVA_Executable(GEU32 offset)       { return reinterpret_cast<GEU32>(LoadModule(0)) + offset; };

#endif