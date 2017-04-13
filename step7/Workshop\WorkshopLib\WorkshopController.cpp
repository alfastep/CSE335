#include "stdafx.h"
#include "WorkshopController.h"
#include "WorkshopWnd.h"

#include <cassert>

const double CWorkshopController::BaggingColumn = 4;
const double CWorkshopController::BaggingRow = 1.35;


/** \cond */
CWorkshopController::CWorkshopController()
{
}


CWorkshopController::~CWorkshopController()
{
}


void CWorkshopController::SetWorkshop(CWorkshopWnd *workshop)
{
    mWorkshop = workshop;
}
/** \endcond */


void CWorkshopController::EnableButtonNext(bool enable)
{
    assert(mWorkshop != NULL);
    mWorkshop->EnableButtonNext(enable);
}

void CWorkshopController::EnableButtonNaughty(bool enable)
{
    assert(mWorkshop != NULL);
    mWorkshop->EnableButtonNaughty(enable);

}

void CWorkshopController::EnableButtonShip(bool enable)
{
    assert(mWorkshop != NULL);
    mWorkshop->EnableButtonShip(enable);
}

void CWorkshopController::SetConveyerSpeed(double speed)
{
    assert(mWorkshop != NULL);
    mWorkshop->SetConveyerSpeed(speed);
}


double CWorkshopController::GetBagPosition()
{
    assert(mWorkshop != NULL);
    return mWorkshop->GetBagPosition();
}


void CWorkshopController::NewBag()
{
    assert(mWorkshop != NULL);
    mWorkshop->NewBag();
}

void CWorkshopController::SetPlatformSpeed(double speedX, double speedY)
{
    assert(mWorkshop != NULL);

    mWorkshop->GetPlatform()->SetSpeed(speedX, speedY);
}

double CWorkshopController::GetPlatformX()
{
    assert(mWorkshop != NULL);
    return mWorkshop->GetPlatform()->GetPositionX();
}

double CWorkshopController::GetPlatformY()
{
    assert(mWorkshop != NULL);
    return mWorkshop->GetPlatform()->GetPositionY();
}

void CWorkshopController::Acquire(int col, int row)
{
    assert(mWorkshop != NULL);
    mWorkshop->Acquire(col, row);
}

void CWorkshopController::BagIt()
{
    assert(mWorkshop != NULL);
    mWorkshop->GetPlatform()->BagIt();
}


bool CWorkshopController::IsBagItDone()
{
    assert(mWorkshop != NULL);
    return mWorkshop->GetPlatform()->IsBagItDone();
}



void CWorkshopController::LoadCoal()
{
    assert(mWorkshop != NULL);
    mWorkshop->GetCoal()->LoadCoal();
}


bool CWorkshopController::IsCoalLoaded()
{
    assert(mWorkshop != NULL);
    return mWorkshop->GetCoal()->IsCoalLoaded();
}
