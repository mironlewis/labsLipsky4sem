#include <gtest/gtest.h>
#include <webdriverxx/webdriverxx.h>
#include <thread>

using namespace webdriverxx;

class ProductTests : public ::testing::Test {
protected:
    WebDriver driver;

    void SetUp() override {
        driver = Start(Chrome());
        driver.Navigate("https://www.ctrs.com.ua/smartfony/");
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    void TearDown() override {
        // driver.Quit();
    }
};

TEST_F(ProductTests, PriceSorting) {
    driver.Navigate("https://www.ctrs.com.ua/smartfony/");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    auto sortDropdown = driver.FindElement(ByCss(".Sort_trigger__uHunS"));
    sortDropdown.Click();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto cheapFirstOption = driver.FindElement(ByXPath("//li[contains(@class, 'Dropdown-module__option') and contains(., 'за зростанням ціни')]"));
    cheapFirstOption.Click();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    EXPECT_TRUE(driver.GetUrl().find("price") != std::string::npos);
}

TEST_F(ProductTests, ProductComparison) {
    driver.Navigate("https://www.ctrs.com.ua/smartfony/");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    auto compareButton = driver.FindElement(ByXPath("(//button[contains(@class, 'MainProductCard-module__favorite')])[2]"));
    compareButton.SendKeys(webdriverxx::keys::Enter);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto checkmark = driver.FindElement(ByXPath("//*[local-name()='path' and @fill='#57AE00']"));
    EXPECT_EQ(checkmark.GetAttribute("fill"), "#57AE00");
}