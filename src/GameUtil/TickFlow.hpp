#ifndef GAMEUTIL_CTICKFLOW_HPP
#define GAMEUTIL_CTICKFLOW_HPP

#include <revolution/types.h>

#include "List.hpp"

#include "TickFlowDecl.hpp"

class CTickFlow : public CList {
public:
    CTickFlow *getNext(void) const {
        return static_cast<CTickFlow *>(this->CList::getNext());
    }
    CTickFlow *getPrev(void) const {
        return static_cast<CTickFlow *>(this->CList::getPrev());
    }

    virtual ~CTickFlow(void);

    virtual void finalInsert(void);
    virtual void finalDestroy(void);
    virtual void _14(void);
    virtual void _18(CTickFlow *); 
    virtual bool _1C(u32 opcode, u32 arg0, const u32 *args);

    CTickFlow(const TickFlowCode *code, float initRest);

    bool fn_801DD9E8(void);
    
    void fn_801DEF8C(const TickFlowCode *code);
    
    static void fn_801DEF58(u8, u32, u32);
    static u32 fn_801DEF78(u8);

private:
    u32 fn_801DECFC(const TickFlowCode *code, u32 labelId);
    u32 fn_801DEDFC(
        const TickFlowCode *code,
        u32 elseOp, u32 elseArg0,
        u32 defaultOp, u32 defaultArg0,
        u32 endOp, u32 endArg0,
        u32 beginNestedBlockOp, u32 endNestedBlockOp,
        u32 instrOffs,
        bool skipOneInstr
    );

private:
    struct ExecutionFrame {
        const TickFlowCode* code;
        u32 instructionOffset;
    };

    const TickFlowCode *mCode;

    s32 mMyCount;

    s32 mCategory;

    s32 mNextInstructionPos; // Index into mCode for the next instruction.
    f32 mCurrentRest; // In ticks.

    bool mExecPaused;

    s32 mCondvar;
    u32 mCondvarStack[16];
    u8 mCondvarStackPos;

    ExecutionFrame mExecStack[16];
    u8 mExecStackPos;

    bool mButtonPromptIsReleased;
    bool mButtonPromptIsPressed;
    u8 mButtonPromptControllerIdx;
    u32 mButtonPromptButton;
    s32 mButtonPromptPressSfx;
    s32 mButtonPromptReleaseSfx;
};

#endif
