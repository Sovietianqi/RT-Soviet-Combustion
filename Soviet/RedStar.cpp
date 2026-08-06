#include <RSC.h>
#include <FootClass.h>
#include <Helpers/VTable.h>
#include <LocomotionClass.h>
#include <Helpers/Macro.h>
#include <LocomotionClass.h>
#include <TechnoClass.h>

void RSC::DLLMAINEnter() 
{
    


};

void RSC::RSCLeave()
{

}

void RSC::RenderSystemInit()
{

}


void RSC::Render(MapClass* pThis) {};



DEFINE_HOOK(0x683EB6, PauseGame_SetPause, 0x6) 
{
    return 0;
}


DEFINE_HOOK(0x683FB2, ResumeGame_ResetPause, 0x5) 
{
    return 0;
}
