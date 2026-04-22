#include <gtest/gtest.h>
#include <webdriverxx/webdriverxx.h>
#include <thread>

using namespace webdriverxx;

class NavigationTests : public ::testing::Test {
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

TEST_F(NavigationTests, EmptySearch) {
    auto searchInput = driver.FindElement(ByCss("input[type='text']"));
    searchInput.SendKeys(webdriverxx::keys::Enter);
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::string currentUrl = driver.GetUrl();
    EXPECT_TRUE(currentUrl == "https://www.ctrs.com.ua/" || currentUrl.find("search") == std::string::npos);
}

TEST_F(NavigationTests, BrandFilter) {
    driver.Navigate("https://www.ctrs.com.ua/smartfony/");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    auto filterButton = driver.FindElement(ByCss(".CategoryFilter_trigger__hHYNd"));
    filterButton.Click();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto appleCheckbox = driver.FindElement(ByXPath("(//a[contains(@href, 'brand-apple')]/ancestor::label)[last()]"));
    appleCheckbox.Click();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    EXPECT_TRUE(driver.GetUrl().find("apple") != std::string::npos);
}