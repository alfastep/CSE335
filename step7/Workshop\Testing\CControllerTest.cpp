#include "stdafx.h"
#include "CppUnitTest.h"
#include "WorkshopWnd.h"
#include "Controller.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	TEST_CLASS(CControllerTest)
	{
	public:
        /**
         * Initialization so image loading will work
         */
        TEST_METHOD_INITIALIZE(methodName)
        {
            extern wchar_t g_dir[];
            ::SetCurrentDirectory(g_dir);
        }

        /**
         * Test that we can simply set a controller
         */
        TEST_METHOD(TestCControllerSetController)
        {
            // Create a test object
            CWorkshopWnd workshop;
            workshop.Load();

            // Create a mock controller and install it
            auto controller = std::make_shared<CController>();

            workshop.SetController(controller);
            Assert::IsTrue(controller->GetWorkshop() == &workshop);
        }

        /**
         * This tests that you can press Next On List and get a bag
         * loaded onto the conveyer belt. This should be the first
         * test you try to pass.
         */
        TEST_METHOD(TestCControllerNextOnList)
        {
            // Create a test object
            CWorkshopWnd workshop;
            workshop.Load();

            // Create a mock controller and install it
            auto controller = std::make_shared<CController>();

            workshop.SetController(controller);

            Assert::AreEqual(1, controller->GetBagPosition(), 0.01);

            // Press the Next On List button
            workshop.PressNextOnList();

            // It takes one second for the bag to move in and stop.
            // Run the workshop for a bit more than that.
            workshop.Update(1.1);

            // Is the bag in place?
            Assert::AreEqual(0, controller->GetBagPosition(), 0.01);
        }

        /**
         * This tests the entire process of loading one object
         * onto the platform, moving it to the bag, dumping it,
         * then shipping 
         */
        TEST_METHOD(TestCControllerLoadOneObject)
        {
            // Create a test object and load the images
            CWorkshopWnd workshop;
            workshop.Load();

            // Create a mock controller and install it
            auto controller = std::make_shared<CController>();

            workshop.SetController(controller);

            //
            // This test runs the system though the entire 
            // process of selecting one item, bagging it, 
            // and shipping. To be sure everything works, we
            // do the test twice, since it should just as 
            // well a second time.
            //
            for (int test = 1; test <= 2; test++) {
                //
                // Test moving a bag onto the loading position on the conveyer belt
                //

                // Ensure the bag starts off-screen like it should
                Assert::AreEqual(1, controller->GetBagPosition(), 0.01);

                // Is the platform at the right place?
                Assert::AreEqual(CWorkshopController::BaggingColumn, controller->GetPlatformX(), 0.01);
                Assert::AreEqual(CWorkshopController::BaggingRow, controller->GetPlatformY(), 0.01);

                // Press the Next On List button
                workshop.PressNextOnList();

                // All buttons should be disabled
                Assert::IsFalse(workshop.IsButtonNextEnabled());
                Assert::IsFalse(workshop.IsButtonNaughtyEnabled());
                Assert::IsFalse(workshop.IsButtonShipEnabled());

                // It takes one second for the bag to move in and stop.
                // Run the workshop for a bit more than that to ensure it stops.
                workshop.Update(1.5);

                // Naughty button should be on
                Assert::IsTrue(workshop.IsButtonNaughtyEnabled());

                // Is the bag in place?
                Assert::AreEqual(0, controller->GetBagPosition(), 0.01);

                //
                // Test the process of fetching the Elsa gift and 
                // moving it to the bag
                //
                GiftingTest(&workshop, controller, 0, 3);

                //
                // Test the process of shipping the bag
                //

                // Press Ship
                workshop.PressShip();

                // All buttons should be off again
                Assert::IsFalse(workshop.IsButtonNextEnabled());
                Assert::IsFalse(workshop.IsButtonNaughtyEnabled());
                Assert::IsFalse(workshop.IsButtonShipEnabled());

                // Should take about one second. I left a little extra
                workshop.Update(1.5);

                Assert::AreEqual(1, controller->GetBagPosition(), 0.01); 

            }
        }

        /**
        * This tests the entire process of choosing from the list
        * and deciding they are naughty!
        */
        TEST_METHOD(TestCControllerNaughty)
        {
            // Create a test object and load the images
            CWorkshopWnd workshop;
            workshop.Load();

            // Create a mock controller and install it
            auto controller = std::make_shared<CController>();

            workshop.SetController(controller);

            //
            // This test runs the system though the entire 
            // process of selecting coal! To be sure everything works, we
            // do the test twice, since it should just as 
            // well a second time.
            //
            for (int test = 1; test <= 2; test++) {
                // Ensure the bag starts off screen like it should
                Assert::AreEqual(1, controller->GetBagPosition(), 0.01);

                // Is the platform at the right place?
                Assert::AreEqual(CWorkshopController::BaggingColumn, controller->GetPlatformX(), 0.01);
                Assert::AreEqual(CWorkshopController::BaggingRow, controller->GetPlatformY(), 0.01);

                // Press the Next On List button
                workshop.PressNextOnList();

                // All buttons should be disabled
                Assert::IsFalse(workshop.IsButtonNextEnabled());
                Assert::IsFalse(workshop.IsButtonNaughtyEnabled());
                Assert::IsFalse(workshop.IsButtonShipEnabled());

                // It takes one second for the bag to move in and stop.
                // Run the workshop for a bit more than that.
                workshop.Update(1.1);

                // Naughty button should be on
                Assert::IsTrue(workshop.IsButtonNaughtyEnabled());

                // Is the bag in place?
                Assert::AreEqual(0, controller->GetBagPosition(), 0.01);

                workshop.PressNaughty();

                // Takes about 4 seconds
                workshop.Update(4);

                Assert::AreEqual(test, workshop.GetCoalCount());

                // Back to initial state
                Assert::IsTrue(workshop.IsButtonNextEnabled());
                Assert::IsFalse(workshop.IsButtonNaughtyEnabled());
                Assert::IsFalse(workshop.IsButtonShipEnabled());
            }
        }

        /**
        * This tests the entire process of loading all of the 
        * different objects onto the platform, moving them 
        * to the bag, dumping them, then shipping
        */
        TEST_METHOD(TestCControllerLoadAllObjects)
        {
            // Create a test object and load the images
            CWorkshopWnd workshop;
            workshop.Load();

            // Create a mock controller and install it
            auto controller = std::make_shared<CController>();

            workshop.SetController(controller);

            //
            // This test runs the system though the entire 
            // process of selecting one item, bagging it, 
            // and shipping. To be sure everything works, we
            // do the test twice, since it should just as 
            // well a second time.
            //
            for (int test = 1; test <= 2; test++) {
                //
                // Test moving a bag onto the loading position on the conveyer belt
                //

                // Ensure the bag starts off-screen like it should
                Assert::AreEqual(1, controller->GetBagPosition(), 0.01);

                // Is the platform at the right place?
                Assert::AreEqual(CWorkshopController::BaggingColumn, controller->GetPlatformX(), 0.01);
                Assert::AreEqual(CWorkshopController::BaggingRow, controller->GetPlatformY(), 0.01);

                // Press the Next On List button
                workshop.PressNextOnList();

                // All buttons should be disabled
                Assert::IsFalse(workshop.IsButtonNextEnabled());
                Assert::IsFalse(workshop.IsButtonNaughtyEnabled());
                Assert::IsFalse(workshop.IsButtonShipEnabled());

                // It takes one second for the bag to move in and stop.
                // Run the workshop for a bit more than that to ensure it stops.
                workshop.Update(1.5);

                // Naughty button should be on
                Assert::IsTrue(workshop.IsButtonNaughtyEnabled());

                // Is the bag in place?
                Assert::AreEqual(0, controller->GetBagPosition(), 0.01);

                //
                // Test the process of fetching all of the gifts
                //
                for (int r = 0; r < 4; r++) 
                {
                    for (int c = 0; c < 4; c++)
                    {
                        GiftingTest(&workshop, controller, c, r);
                    }
                }

                //
                // Test the process of shipping the bag
                //

                // Press Ship
                workshop.PressShip();

                // All buttons should be off again
                Assert::IsFalse(workshop.IsButtonNextEnabled());
                Assert::IsFalse(workshop.IsButtonNaughtyEnabled());
                Assert::IsFalse(workshop.IsButtonShipEnabled());

                // Should take about one second. I left a little extra
                workshop.Update(1.5);

                Assert::AreEqual(1, controller->GetBagPosition(), 0.01);

            }
        }

        /**
         * Test the process of selecting a gift, platform moving to
         * the gift, acquiring the gift, then moving the platform
         * to the bag and dumping the gift into the bag.
        */
        void GiftingTest(CWorkshopWnd *workshop, 
            std::shared_ptr<CController> controller,
            int giftColumn, int giftRow)
        {
            // We are ready to choose a gift,
            // Next On List should be disabled.
            Assert::IsFalse(workshop->IsButtonNextEnabled());

            // Is the bag in place?
            Assert::AreEqual(0, controller->GetBagPosition(), 0.01);

            // Click on Gift
            workshop->ClickOnGift(giftColumn, giftRow);

            //
            // Determine the time it should take for the platform
            // to move from the loading position to/from a gift. That
            // will be the farthest distance in either dimension. 
            //
            double moveTime = max(abs(CWorkshopController::BaggingColumn - giftColumn),
                abs(CWorkshopController::BaggingRow - giftRow));

            // Wait for the platform to move to the gift.
            workshop->Update(moveTime);

            // Is the platform at the right place?
            Assert::AreEqual(giftColumn, controller->GetPlatformX(), 0.01);
            Assert::AreEqual(giftRow, controller->GetPlatformY(), 0.01);

            // It should stay at this location for one second
            workshop->Update(1);

            // Is the platform at the right place?
            Assert::AreEqual(giftColumn, controller->GetPlatformX(), 0.01);
            Assert::AreEqual(giftRow, controller->GetPlatformY(), 0.01);

            // Do we hold the right gift on the platform?
            auto heldGift = workshop->GetPlatformGift();
            auto expectedGift = workshop->GetGift(giftColumn, giftRow);
            Assert::IsTrue(heldGift == expectedGift);

            // Wait for the platform to move from the gift.
            workshop->Update(moveTime);

            Assert::AreEqual(CWorkshopController::BaggingColumn, controller->GetPlatformX(), 0.01);
            Assert::AreEqual(CWorkshopController::BaggingRow, controller->GetPlatformY(), 0.01);

            // It should take 5 seconds for the bagging process to complete
            // I'm allowing a bit of extra time for everything to complete
            workshop->Update(5.1);

            // Should have dumped the gift
            heldGift = workshop->GetPlatformGift();
            Assert::IsTrue(heldGift == nullptr);

            // Only Ship should be enabled at this time
            Assert::IsFalse(workshop->IsButtonNextEnabled());
            Assert::IsFalse(workshop->IsButtonNaughtyEnabled());
            Assert::IsTrue(workshop->IsButtonShipEnabled());
        }

	};
}