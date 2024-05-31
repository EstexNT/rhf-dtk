#ifndef GAME_BACKUPMANAGER_HPP
#define GAME_BACKUPMANAGER_HPP

#include <revolution/types.h>
#include "TSingleton.hpp"

class CBackupManager : public TSingleton<CBackupManager> {
public:
    //TODO
    void fn_80084FC8(u32);
};

extern CBackupManager *gBackupManager;

#endif
