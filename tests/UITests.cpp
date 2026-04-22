#include <gtest/gtest.h>
#include <webdriverxx/webdriverxx.h>
#include <thread>

using namespace webdriverxx;

class UITests : public ::testing::Test {
protected:
    WebDriver driver;

    void SetUp() override {
        driver = Start(Chrome());
        driver.Navigate("https://www.ctrs.com.ua/");
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    void TearDown() override {
        // driver.Quit();
    }
};

TEST_F(UITests, ExistingProductSearch) {
    auto searchInput = driver.FindElement(ByCss("input[type='text']"));
    searchInput.SendKeys("iPhone 15");
    searchInput.SendKeys(webdriverxx::keys::Enter);
    
    std::this_thread::sleep_for(std::chrono::seconds(3));
    EXPECT_TRUE(driver.GetUrl().find("search") != std::string::npos);
}

TEST_F(UITests, NonExistingProductSearch) {
    auto searchInput = driver.FindElement(ByCss("input[type='text']"));
    searchInput.SendKeys("qwertyuiopasdfghjkl");
    searchInput.SendKeys(webdriverxx::keys::Enter);
    std::this_thread::sleep_for(std::chrono::seconds(6));
    auto notFoundContainer = driver.FindElement(ByCss(".EmptySearch_emptyContainer__OgR_p"));
    EXPECT_TRUE(notFoundContainer.GetText().length() > 0);
}