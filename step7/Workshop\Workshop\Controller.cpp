/**
 * \file Controller.cpp
 *
 * \author Stephen Alfa
 */

#include "stdafx.h"
#include <math.h>       /* floor */
#include "Controller.h"

 
 /**
 * Constructor
 */
CController::CController()
{
}

/**
 * Destructor
 */
CController::~CController()
{
}


/** Initialization function.
*
* This function is called when the system is initialized. This is
* later than when it is constructed, since the controller is not installed on
* a workshop when it is constructed. This function is called when the workshop
* controller is installed and ready to control a workshop.
*/
void CController::Initialize()
{

}




/** Service the workshop.
*
* This function is called once every millisecond during workshop
* operation. It provides a place to put code the controls the
* workshop. Override in a local function.
*/
void CController::Service()
{
	// Increment state time by 1 millisecond
	mStateTime += 0.001;

	switch (mState)
	{
	case Initial:
		if (floor(GetBagPosition()) == 1.0)
		{
			SetState(Idle);
		}
		break;
	
	case BagComingOn:
		if (GetBagPosition() < 0)
		{
			SetState(BagInPosition);
		}
		break;

	case MoveToBin:
		EnableButtonNaughty(false);
		if (mColumn > GetPlatformX()) 
		{
			mSpeedX = 1;
			
			if (mRow > GetPlatformY()) 
			{
				mSpeedY = 1;
				SetPlatformSpeed(1, 1);
			}

			else if (mRow < GetPlatformY())
			{
				mSpeedY = -1;
				SetPlatformSpeed(1, -1);
			}
		}

		if (mColumn < GetPlatformX())
		{
			mSpeedX = -1;

			if (mRow > GetPlatformY())
			{
				mSpeedY = 1;
				SetPlatformSpeed(-1, 1);
			}

			else if (mRow < GetPlatformY())
			{
				mSpeedY = -1;
				SetPlatformSpeed(-1, -1);
			}
		}

		if (mSpeedX < 0 && GetPlatformX()-0.001 < mColumn || 
			mSpeedX > 0 && GetPlatformX()+0.001 > mColumn)
		{
			if (mSpeedY < 0 && GetPlatformY() - 0.001 < mRow ||
				mSpeedY > 0 && GetPlatformY() + 0.001 > mRow)
			{
				mSpeedX = 0;
				mSpeedY = 0;
				SetPlatformSpeed(0, 0);
				Acquire(mColumn,mRow);
				SetState(MoveToBag);
			}
		}
		break;

	case MoveToBag:
		EnableButtonNaughty(false);
		if (mStateTime > 1)
		{
			if (BaggingColumn > GetPlatformX())
			{
				mSpeedX = 1;

				if (BaggingRow > GetPlatformY())
				{
					mSpeedY = 1;
					SetPlatformSpeed(1, 1);
				}

				else if (BaggingRow < GetPlatformY())
				{
					mSpeedY = -1;
					SetPlatformSpeed(1, -1);
				}
			}

			if (BaggingColumn < GetPlatformX())
			{
				mSpeedX = -1;

				if (BaggingRow > GetPlatformY())
				{
					mSpeedY = 1;
					SetPlatformSpeed(-1, 1);
				}

				else if (BaggingRow < GetPlatformY())
				{
					mSpeedY = -1;
					SetPlatformSpeed(-1, -1);
				}
			}

			if (mSpeedX < 0 && GetPlatformX() - 0.001 < BaggingColumn ||
				mSpeedX > 0 && GetPlatformX() + 0.001 > BaggingColumn)
			{
				if (mSpeedY < 0 && GetPlatformY() - 0.001 < BaggingRow ||
					mSpeedY > 0 && GetPlatformY() + 0.001 > BaggingRow)
				{
					mSpeedX = 0;
					mSpeedY = 0;
					SetPlatformSpeed(0, 0);
					SetState(DumpGift);
				}
			}
		}
		break;

	case DumpGift:
		if (IsBagItDone()) 
		{
			EnableButtonShip(true);
			SetState(BagInPosition);
			EnableButtonNaughty(false);
		}
		break;

	case Ship:
		if (GetBagPosition() == 1) 
		{
			SetConveyerSpeed(0);
			SetState(Idle);
		}
		break;
	
	case Naughty:
		if (IsCoalLoaded()) 
		{
			EnableButtonNaughty(false);
			//SetConveyerSpeed(1);
			SetState(Ship);
		}
		break;

	}
}


/**
* Indication that the Next On List button has been pressed
*
* This function is called whenever the Next On List button is pressed.
* It is only called if the button is enabled.
*/
void CController::OnNextPressed() 
{
		SetState(BagComingOn);
		NewBag();
		SetConveyerSpeed(-1);
}

/**
* Indication that the Naughty button has been pressed
*
* This function is called whenever the Naughty button is pressed.
* It is only called if the button is enabled.
*/
void CController::OnNaughtyPressed() 
{
	EnableButtonNaughty(false);
	SetState(Naughty);
}

/**
* Indication that the Ship button has been pressed
*
* This function is called whenever the Ship button is pressed.
* It is only called if the button is enabled.
*/
void CController::OnShipPressed() 
{
	SetConveyerSpeed(1);
	SetState(Ship);

}

/**
* Indication that a Gift has been clicked on
*
* This functin is called whenever the user clicks on
* any of the gifts.
* \param col Column clicked on, left is 0, right is 3
* \param row Row clicked on. Bottom row is 0, top is 3
*/
void CController::OnGiftSelected(int col, int row)
{
	switch (mState)
	{

	case BagInPosition:
		mRow = row;
		mColumn = col;
		SetState(MoveToBin);
		break;
	default:
		break;
	}
	
	
}

/** Set a state
* \param state The new state to set
*/
void  CController::SetState(States state)
{
	mState = state;
	mStateTime = 0;

	switch (mState)
	{
	case Idle:
		//if (GetBagPosition() == 1.0) {
			EnableButtonNext(true);
			EnableButtonNaughty(false);
			EnableButtonShip(false);
		//}
		break;

	case BagComingOn:
		EnableButtonNext(false);
		break;

	case BagInPosition:
		SetConveyerSpeed(0);
		EnableButtonNaughty(true);
		break;

	case MoveToBin:
		EnableButtonNaughty(false);
		break;

	case MoveToBag:
		EnableButtonNaughty(false);
		break;

	case DumpGift:
		BagIt();
		EnableButtonNaughty(false);
		break;

	case Ship:
		EnableButtonShip(false);
		EnableButtonNaughty(false);
		SetConveyerSpeed(1);
		break;

	case Naughty:
		LoadCoal();
		break;

	}
}