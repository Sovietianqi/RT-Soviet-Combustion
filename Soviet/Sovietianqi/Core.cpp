#include <RSC.h>
#include <TechnoClass.h>
#include <YRMath.h>
#include <GameOptionsClass.h>
#include <FPSCounter.h>

static UINT g_TimerPeriod = 0;
static HANDLE g_hAvrt = nullptr;
static DWORD g_dwAvrtIdx = 0;
inline int GetFPS() { return FPSCounter::CurrentFrameRate; }

void RSC::UnlockSingleCoreLimit(HANDLE hProcess) {
    DWORD_PTR processMask, systemMask;
    if (GetProcessAffinityMask(hProcess, &processMask, &systemMask)) {
        if ((processMask & (processMask - 1)) == 0) {
            SetProcessAffinityMask(hProcess, systemMask);
        }
    }
 }

void RSC::SetHighResTimer() {
    if (timeBeginPeriod(1) == TIMERR_NOERROR)
        g_TimerPeriod = 1;
}

void RSC::RestoreHighResTimer() {
    if (g_TimerPeriod) {
        timeEndPeriod(g_TimerPeriod);
        g_TimerPeriod = 0;
    }
}

void RSC::ApplyMMCSS() {
    g_hAvrt = AvSetMmThreadCharacteristicsW(L"Pro Audio", &g_dwAvrtIdx);
    if (!g_hAvrt)
        g_hAvrt = AvSetMmThreadCharacteristicsW(L"Audio", &g_dwAvrtIdx);
}

void RSC::RestoreMMCSS() {
    if (g_hAvrt) {
        AvRevertMmThreadCharacteristics(g_hAvrt);
        g_hAvrt = nullptr;
    }
}

DEFINE_HOOK(0x709820, Target_Something_Nearby_Throttle, 0x5)
{
    GET(TechnoClass*, pThis, ECX);

    const DWORD currentFrame = Unsorted::CurrentFrame;
    const DWORD lastScanFrame = pThis->LastFireBulletFrame;
    const AbstractClass* pCurrentTarget = pThis->Target;
    int interval = 8;
    switch (pThis->WhatAmI()) {
    case AbstractType::Infantry: interval = 15; break;
    case AbstractType::Building: interval = 30; break;
    case AbstractType::Aircraft: interval = 4;  break;
    case AbstractType::Unit: interval = 6;  break;
    default: break;
    }

    if (pCurrentTarget != nullptr) interval <<= 1;

    if ((currentFrame - lastScanFrame) < (DWORD)interval) return 0x7099CA;

    pThis->LastFireBulletFrame = currentFrame;
    return 0;
}


DEFINE_HOOK(0x6F8DF0, Greatest_Threat_Cache, 0x9)
{
    GET(TechnoClass*, pThis, ECX);

    auto pWeapon = pThis->GetWeapon(0);
    if (!pWeapon || !pWeapon->WeaponType) {
        return 0;
    }
    double range = pWeapon->WeaponType->Range * 256.0;
    CoordStruct myPos = pThis->GetCoords();
    AbstractClass* pCurrentTarget = pThis->Target;
    if (pCurrentTarget && !pCurrentTarget->IsDead()) {
        CoordStruct targetPos = pCurrentTarget->GetCoords();

        int dx = abs(myPos.X - targetPos.X);
        int dy = abs(myPos.Y - targetPos.Y);
        if (dx <= range && dy <= range) {
            double dist = myPos.DistanceFrom(targetPos);
            if (dist <= range * 1.2) {
                R->EAX(pCurrentTarget);
                return 0x6F9DAC;
            }
        }
    }
    AbstractClass* pLastTarget = pThis->LastTarget;
    if (pLastTarget && !pLastTarget->IsDead()) {
        CoordStruct targetPos = pLastTarget->GetCoords();

        int dx = abs(myPos.X - targetPos.X);
        int dy = abs(myPos.Y - targetPos.Y);
        if (dx <= range && dy <= range) {
            double dist = myPos.DistanceFrom(targetPos);
            if (dist <= range * 1.5) {
                R->EAX(pLastTarget);
                return 0x6F9DAC;
            }
        }
    }
    return 0;
}




DEFINE_HOOK(0x7360C0, UnitUpdate_Tier, 0x9)
{
    GET(UnitClass*, pThis, ECX);

    BOOL bLowFPSMode = false;
    int fps = GetFPS();
    int interval = 1;
    if (fps < 18) bLowFPSMode = true;
    if (fps > 25) bLowFPSMode = false;

    if (bLowFPSMode) {
        interval = (fps < 15) ? 4 : 2;
    } else {
        auto pTactical = TacticalClass::Instance;
        if (pTactical) {
            auto [screenPos, isVisible] = pTactical->CoordsToClient(pThis->GetCoords());
            auto pscreen = GameOptionsClass::Instance;
            int centerX = pscreen.ScreenWidth / 2;
            int centerY = pscreen.ScreenHeight / 2;
            int dist = abs(screenPos.X - centerX) + abs(screenPos.Y - centerY);

            if (dist < 500)        interval = 1;
            else if (dist < 1500)  interval = 2;
            else if (dist < 3000)  interval = 4;
            else                   interval = 8;
        }
    }

    const DWORD currentFrame = Unsorted::CurrentFrame;
    if ((currentFrame + pThis->GetArrayIndex()) % interval != 0) {
        return 0x736988;
    }
    return 0;
}

DEFINE_HOOK(0x62FD60, ParticleSystem_Update_Hybrid, 0x9)
{
    GET(ParticleSystemClass*, pThis, ECX);
    int interval = 1;
    int fps = GetFPS();
    bool bLowFPSMode = false;
    if (fps < 18) bLowFPSMode = true;
    if (fps > 25) bLowFPSMode = false;

    if (bLowFPSMode) {
        interval = (fps < 15) ? 6 : 3;
    }
    else {
        auto pTactical = TacticalClass::Instance;
        if (pTactical) {
            auto [screenPos, isVisible] = pTactical->CoordsToClient(pThis->GetCoords());
            auto pscreen = GameOptionsClass::Instance;
            int centerX = pscreen.ScreenWidth / 2;
            int centerY = pscreen.ScreenHeight / 2;
            int dist = abs(screenPos.X - centerX) + abs(screenPos.Y - centerY);

            if (dist < 500)        interval = 2;
            else if (dist < 1500)  interval = 3;
            else if (dist < 3000)  interval = 6;
            else                   interval = 12;
        }
    }

    const DWORD currentFrame = Unsorted::CurrentFrame;
    if ((currentFrame + pThis->GetArrayIndex()) % interval != 0) {
        return 0x62FE43;
    }
    return 0;
}


DEFINE_HOOK(0x423AC0, AnimClass_Update_Hybrid, 0x6)
{
    GET(AnimClass*, pThis, ECX);
    BOOL bLowFPSMode = false;
    int fps = GetFPS();
    int interval = 1;
    if (fps < 18) bLowFPSMode = true;
    if (fps > 25) bLowFPSMode = false;

    if (bLowFPSMode) {
        interval = (fps < 15) ? 8 : 4;
    }
    else {
        auto pTactical = TacticalClass::Instance;
        if (pTactical) {
            auto [screenPos, isVisible] = pTactical->CoordsToClient(pThis->GetCoords());
            auto pscreen = GameOptionsClass::Instance;
            int centerX = pscreen.ScreenWidth / 2;
            int centerY = pscreen.ScreenHeight / 2;
            int dist = abs(screenPos.X - centerX) + abs(screenPos.Y - centerY);

            if (dist < 500)        interval = 2;
            else if (dist < 1500)  interval = 4;
            else                   interval = 8;
        }
    }
    const DWORD currentFrame = Unsorted::CurrentFrame;
    if ((currentFrame + pThis->GetArrayIndex()) % interval != 0) {
        return 0x424B49;
    }
    return 0;
}



DEFINE_HOOK(0x422CA0, AnimClass_Draw_EmergencySkip, 0x5)
{
    BOOL bLowFPSMode = false;
    int fps = GetFPS();
    if (fps < 18) bLowFPSMode = true;
    if (fps > 25) bLowFPSMode = false;
    if (bLowFPSMode) {
        return 0x4238AD;
    }

    return 0;
}




DEFINE_HOOK(0x5FD970, OverlayClass_Draw_EmergencySkip, 0x5)
{
    BOOL bLowFPSMode = false;
    int fps = GetFPS();
    if (fps < 10) bLowFPSMode = true;
    if (fps > 11) bLowFPSMode = false;
    if (bLowFPSMode) {
        return 0x5FDCB6;
    }
    return 0;
}