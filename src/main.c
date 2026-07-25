#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "core/engine.h"
#include "graphics/renderer.h"
#include "world/world.h"
#include "entities/player.h"

PSP_MODULE_INFO("Minecraft PSP", PSP_MODULE_USER, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

int exit_callback(int arg1, int arg2, void *common) {
    sceKernelExitGame();
    return 0;
}

int CallbackThread(SceSize args, void *argp) {
    int cbid;
    cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

int SetupCallbacks(void) {
    int thid = 0;
    thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, PSP_THREAD_ATTR_USER, NULL);
    if (thid >= 0) {
        sceKernelStartThread(thid, 0, NULL);
    }
    return thid;
}

void pspDebugScreenPrintf(const char *format, ...) {
    va_list list;
    char str[512];
    va_start(list, format);
    vsprintf(str, format, list);
    va_end(list);
    pspDebugScreenSetXY(0, 0);
    pspDebugScreenPuts(str);
}

int main() {
    SetupCallbacks();
    
    pspDebugScreenInit();
    pspDebugScreenSetBackColor(0x00000000);
    pspDebugScreenSetTextColor(0xFFFFFFFF);
    
    // Inicializar motor
    engine_t *engine = engine_init();
    if (!engine) {
        pspDebugScreenPrintf("Error: Failed to initialize engine\n");
        sceKernelDelayThread(3000000);
        sceKernelExitGame();
        return 1;
    }
    
    // Inicializar renderer
    if (renderer_init() != 0) {
        pspDebugScreenPrintf("Error: Failed to initialize renderer\n");
        sceKernelDelayThread(3000000);
        sceKernelExitGame();
        return 1;
    }
    
    // Inicializar mundo
    world_t *world = world_create(12345);
    if (!world) {
        pspDebugScreenPrintf("Error: Failed to create world\n");
        sceKernelDelayThread(3000000);
        sceKernelExitGame();
        return 1;
    }
    
    // Inicializar jugador
    player_t *player = player_create(0.0f, 64.0f, 0.0f);
    if (!player) {
        pspDebugScreenPrintf("Error: Failed to create player\n");
        sceKernelDelayThread(3000000);
        sceKernelExitGame();
        return 1;
    }
    
    pspDebugScreenPrintf("Minecraft PSP - Initialization complete!\n");
    sceKernelDelayThread(1000000);
    
    // Main loop
    while (1) {
        SceCtrlData pad;
        sceCtrlReadBufferPositive(&pad, 1);
        
        if (pad.Buttons != 0) {
            if (pad.Buttons & PSP_CTRL_START) break;
            player_handle_input(player, &pad);
        }
        
        // Update
        player_update(player, world);
        
        // Render
        renderer_begin_frame();
        world_render(world, player);
        player_render(player);
        renderer_end_frame();
        
        sceDisplayWaitVblankStart();
    }
    
    // Cleanup
    player_destroy(player);
    world_destroy(world);
    renderer_shutdown();
    engine_shutdown(engine);
    
    sceKernelExitGame();
    return 0;
}
