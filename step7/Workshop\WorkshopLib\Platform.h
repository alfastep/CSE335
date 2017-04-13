/**
 * \file Platform.h
 *
 * \author Charles Owen
 *
 * \cond
 */


#include <memory>

class CWorkshopWnd;

#pragma once
class AFX_EXT_CLASS CPlatform
{
public:
    CPlatform();
    virtual ~CPlatform();

    void Draw(Gdiplus::Graphics *graphics);
    void Load(CWorkshopWnd *wnd);
    void Update(double elapsed);

    void SetSpeed(double x, double y) { mSpeedX = x; mSpeedY = y; }
    double GetPositionX() { return mPositionX; }
    double GetPositionY() { return mPositionY; }
    void Acquire(std::shared_ptr<Gdiplus::Bitmap> gift) { mGift = gift; mSlide = 0; mSlideRate = 0; }
    void BagIt();
    bool IsBagItDone();

    std::shared_ptr<Gdiplus::Bitmap> GetGift() { return mGift; }

private:
    enum BaggingStates {Tipping, TipDrop, Dropping, Untipping, Done};

    void SetBaggingState(BaggingStates state);
    void ServiceBaggingState();

    std::shared_ptr<Gdiplus::Bitmap>  mPlatform;
    std::shared_ptr<Gdiplus::Bitmap>  mPlatformTop;

    std::shared_ptr<Gdiplus::Bitmap> mGift;

    double mPositionX;
    double mPositionY;

    double mSpeedX = 0;
    double mSpeedY = 0;

    float mTip = 0;         ///< Top tip amount in degrees
    float mTipRate = 0;     ///< Top tip amount in degrees per second

    float mSlide = 0;       ///< Amount we have slide item off platform
    float mSlideRate = 0;   ///< Rate we are sliding the item

    BaggingStates mBaggingState = Untipping;
};

/// \endcond
