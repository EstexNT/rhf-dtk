#ifndef GAME_CANVASMANAGER_HPP
#define GAME_CANVASMANAGER_HPP

#include <revolution/types.h>
#include "Singleton.hpp"

class CMyCanvasManager : public TSingleton<CMyCanvasManager> {
public:

    CMyCanvasManager(void);

    void fn_8007BE0C(void);
};

extern CMyCanvasManager *gMyCanvasManager;

#endif