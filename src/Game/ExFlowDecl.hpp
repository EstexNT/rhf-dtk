#ifndef GAME_EXFLOWDECL_HPP
#define GAME_EXFLOWDECL_HPP

#include <revolution/types.h>

#include "TickFlowDecl.hpp"

enum {
    /*   ExFlow opcodes (0x100 to 0x141)  */

    TF_SET_SCENE = 0x100, ///< Set the current scene. Args: scene ID, tickflow *
    TF_SET_SCENE_VER, ///< Set a scene's version. Args: scene ID, version
    TF_SCENE_DATA, ///< (Un)load a scene's data (cellanim data & layouts). Arg0: 0 for load, 1 for unload; Args: scene ID
    TF_103,
    TF_104,
    TF_SET_PROLOGUE, ///< Set the prologue. Arg0: is 2P; Args: name, version
    TF_SET_EPILOGUE, ///< Set the epilogue. Args: name, version
    TF_SET_EPILOGUE_MSG, ///< Set a epilogue message. Arg0: type: 0 for OK, 1 for Try Again, 2 for Superb; Args: string containing BMG message ID
    TF_108,
    TF_109,
    TF_FADE, ///< Fade the screen in/out. Arg0: 0 for fade out, 1 for fade in; Args: time is in frames, time (in ticks or frames).
    TF_10B,
    TF_10C,
    TF_10D,
    TF_UI_PAUSE, ///< Show/hide the "(-) Pause" graphic. Arg0: 0 for show, 1 for hide
    TF_10F,
    TF_110,
    TF_111,
    TF_112,
    TF_113,
    TF_114,
    TF_115,
    TF_116,
    TF_117,
    TF_118,
    TF_119,
    TF_11A,
    TF_11B,
    TF_11C,
    TF_11D,
    TF_11E,
    TF_11F,
    TF_120,
    TF_121,
    TF_122,
    TF_123,
    TF_124,
    TF_125,
    TF_126,
    TF_127,
    TF_128,
    TF_129,
    TF_12A,
    TF_12B,
    TF_LOAD_GROUP, ///< Start loading a sound group. Arg0: type (1 for music, 2 for sfx); Args: RSID of group
    TF_UNLOAD_GROUPS, ///< Unload all groups of a specific type. Arg0: type (1 for music, 2 for sfx)
    TF_12E,
    TF_12F,
    TF_130,
    TF_131,
    TF_132,
    TF_133,
    TF_134,
    TF_135,
    TF_136,
    TF_137,
    TF_138,
    TF_139,
    TF_13A,
    TF_13B,
    TF_13C,
    TF_13D,
    TF_13E,
    TF_REMIX8_MASK_MANAGE, ///< Manage the Remix 8 mask. Arg0: operation (0: load, 1: unload, 2: enquire ready (sets condvar), 3: init, 4: set visible, 5: set layer); Args: is visible / layer
    TF_ENDLESS_MANAGE, ///< Manage Endless Remix. Arg0: operation (0: load, 1: unload, 2: enquire ready (sets condvar), 3: init, 4: get random scene ID (sets condvar))
    TF_141
};

// command macros

#define TFC_SET_SCENE(scene_id, tf_label) TFD_CMD(TF_SET_SCENE, 2, 0), (u32)(scene_id), TFD_PTR(tf_label),
#define TFC_100_1() TFD_CMD(0x100, 0, 1), // TODO: rename

#define TFC_SET_SCENE_VER(scene_id, ver) TFD_CMD(TF_SET_SCENE_VER, 2, 0), (u32)(scene_id), (u32)(ver),

#define TFC_SET_EPILOGUE(name_str, ver) TFD_CMD(TF_SET_EPILOGUE, 2, 0), TFD_PTR(name_str), (u32)(ver),

#define TFC_SET_EPILOGUE_MSG_OK(msgid_str) TFD_CMD(TF_SET_EPILOGUE_MSG, 1, 0), TFD_PTR(msgid_str),
#define TFC_SET_EPILOGUE_MSG_TRYAGAIN(msgid_str) TFD_CMD(TF_SET_EPILOGUE_MSG, 1, 1), TFD_PTR(msgid_str),
#define TFC_SET_EPILOGUE_MSG_SUPERB(msgid_str) TFD_CMD(TF_SET_EPILOGUE_MSG, 1, 2), TFD_PTR(msgid_str),

#endif
