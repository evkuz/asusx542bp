# <input id="restartB" value="Перезагрузка" class="button button-blank" type="button">
# Работает, только если дважды кликать, строки 56, 57

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC


def login2router():
    driver = webdriver.Chrome('/home/evkuz/PycharmProjects/chromedriver')
    driver.get('http://192.168.1.1')
    assert "S1500" in driver.title
    username = driver.find_element_by_xpath("//input[@value='Username']")
    username.clear()
    username.send_keys("admin")
    #
    passwd = driver.find_element_by_xpath("//input[@value='Password']")
    passwd.clear()
    passwd.send_keys("p9C8madU")
    button = driver.find_element_by_xpath("//input[@id='start']")
    button.click()
    print("\'Login\' passed")
    try:
        element = WebDriverWait(driver, 10).until(EC.element_to_be_clickable((By.XPATH, \
                                                                "//a[@href='status-and-support.html#sub=1']"))).click()
        print("\'Status and support\' ckicked")
        import time
        time.sleep(2)
        try:
# <a href="#sub=41" onclick="page_data_load('status-and-support');"><span id="lang906007">Перезагрузка</span></a>
# <span id="lang906007">Перезагрузка</span>
             element = WebDriverWait(driver, 10).until(EC.element_to_be_clickable((By.XPATH, \
                                                                                   "//a[@href='#sub=41']"))).click()
             print("\'Reboot\' in left pannel clicked")
             import time
             time.sleep(2)
             #assert "S1500" in driver.title
             # Now final reboot button pressing!!!
             try:
                 # first = WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.ID('restartB'))))
                 #WebDriver _driver = new WebDriver();
#                  _wait = WebDriverWait(driver, 10)
#                  _wait.until(EC.FindElement(By.Id("restartB")))
#                  WebDriverWait(driver, 10).until(lambda d: d.execute_script('return document.readyState') \
#                                                            == 'complete')
                  #element = WebDriverWait(getDriver(), 10)).until(ExpectedConditions.visibilityOfElementLocated(By.cssSelector("input#houseName")));
        #          first = WebDriverWait(driver, 10).until(EC.visibility_of_element_located((By.CSS_SELECTOR("//input[@id='restartB']")\
        #                                                                                   )))
        #         RenderedWebElement resultsDiv = (RenderedWebElement)
        #         driver.findElement(By.className("gac_m"));
                  #element = WebDriverWait(driver, 10).until(EC.visibility_of_all_elements_located((By.XPATH, \
                  #                                               "//input[@id='restartB']")))


                  element = WebDriverWait(driver, 20).until(EC.element_to_be_clickable((By.ID, 'restartB'))).click()
                  element = WebDriverWait(driver, 10).until(EC.element_to_be_clickable((By.XPATH, \
                                                                 "//input[@id='restartB']"))).click()
                  print("\'restartB\' clicked ?")
                  print("Done")
             finally:
                driver.quit()
        finally:
            driver.quit()
    finally:
        driver.quit()


def main():
    login2router()


if __name__ == '__main__':
    main()
