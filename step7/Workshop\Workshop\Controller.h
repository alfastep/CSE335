/**
 * \file Controller.h
 *
 * \author Stephen Alfa 
 *
 * 
 */

#include "WorkshopController.h"

#pragma once


/**
 * The controller for the workshop.
 */
class CController :
    public CWorkshopController
{
public:
    CController();
    virtual ~CController();
    
    virtual void Initialize() override;

    virtual void OnNextPressed() override;
    virtual void OnNaughtyPressed() override;
    virtual void OnShipPressed() override;
    virtual void OnGiftSelected(int col, int row) override;
    virtual void Service() override;
	
	/// The state machine states
	enum States { Initial, Idle, BagComingOn, BagInPosition, Naughty, Ship, MoveToBin, GiftSelcted, MoveToBag, DumpGift };

private:
	States mState = Idle;   ///< The current state
	double mStateTime = 0;  ///< The time in a current state
	int mRow = 0;		///< The row
	int mColumn = 0;		///< The column
	double mSpeedX = 0;		///< The speed in the x direction
	double mSpeedY = 0;		///< The speed in the y direction
	
	void SetState(States state);
	
};

